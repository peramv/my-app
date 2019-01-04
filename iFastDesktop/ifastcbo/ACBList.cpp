//******************************************************************************
//	TESTING ... PLEASE IGNORE THIS COPY ... MAR 14, 2005 ... PATRICK LI / SCM
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1999 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : ACBList.cpp
// ^AUTHOR : Zijian Ying
// ^DATE   : 04/19/99
//
// ^CLASS    : ACBList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"

#include "acblist.hpp"
#include "acbrecord.hpp"
#include "accountholdingsbycurrencylist.hpp"
#include "currencyclass.hpp"
#include <ifastdataimpl\dse_dstc0015_req.hpp>
#include <ifastdataimpl\dse_dstc0015_vw.hpp>
#include "mfaccount.hpp"

namespace
{
   //Trace literals
   const I_CHAR *  CLASSNAME = I_( "ACBList" );
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ACB;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId IsNewOrUpdate;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const ACB;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
//  Field DD Id,                       State Flags,            Group Flags 
   { ifds::AccountNum,                BFCBO::NOT_ON_HOST,           0 },
   { ifds::FundCode,                  BFCBO::NOT_ON_HOST,           0 },
   { ifds::ClassCode,                 BFCBO::NOT_ON_HOST,           0 },
   { ifds::rxFundCode,                BFCBO::NONE,                  0 },
   { ifds::rxClassCode,               BFCBO::NONE,                  0 }, 
   { ifds::ACBPlugAmt,                BFCBO::NONE,                  0 },
   { ifds::ACBPlugDate,               BFCBO::NONE,                  0 },
   { ifds::IsNewOrUpdate,             BFCBO::NOT_ON_HOST,           0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
ACBList::ACBList( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent ),
_requestData(ifds::DSTC0015_REQ)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );

   registerMemberData( NUM_FIELDS, 
                      (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0, 
                       NULL );
}

//******************************************************************************
ACBList::~ACBList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY ACBList::init( const DString& AccountNum, 
                        const DString& FundCode, 
                        const DString& ClassCode,
                        const DString& dstrTrack,
                        const DString& dstrPageName)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   _accountNum = AccountNum;
   _accountNum.strip();

   DString mgmtCoIdOut;
   _requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   _requestData.setElementValue( ifds::AccountNum,  AccountNum  );
   _requestData.setElementValue( ifds::FundCode,    FundCode    );
   _requestData.setElementValue( ifds::ClassCode,   ClassCode   );
   
   DString fundCode(FundCode), classCode(ClassCode);

   if( fundCode.strip() == NULL_STRING && classCode.strip() == NULL_STRING )
      _requestData.setElementValue( ifds::AllFundMode, I_("Y")     );
   else
   {
      _requestData.setElementValue( ifds::AllFundMode, I_("N")     );
   }

   _requestData.setElementValue( ifds::NextKey,     NULL_STRING );
   _requestData.setElementValue( ifds::Track, dstrTrack );
   _requestData.setElementValue( ifds::Activity, dstrPageName );

   ReceiveData(DSTC_REQUEST::ACB, 
               _requestData, 
               ifds::DSTC0015_VW, 
               DSTCRequestor(getSecurity(), false) );

   setFieldNoValidate( ifds::AccountNum, AccountNum, BF::HOST, false );
   if( !fundCode.strip().empty() && !classCode.strip().empty() )
   {
      setFieldNoValidate( ifds::FundCode, fundCode, BF::HOST, false );
      setFieldNoValidate( ifds::ClassCode, classCode, BF::HOST, false );
      setFieldNoValidate( ifds::rxFundCode, fundCode, BF::HOST, false );
      setFieldNoValidate( ifds::rxClassCode, classCode, BF::HOST, false );
   }

   bool bUpdateACBPlug = getWorkSession().hasUpdatePermission( UAF::ACB );
   setFieldReadOnly (ifds::ACBPlugAmt, BF::HOST, !bUpdateACBPlug );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY ACBList::getMore()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );

   if( doMoreRecordsExist() )
   {
      const DSTCSecurity* security = dynamic_cast<const DSTCSecurity *> ( getSecurity() );
      ReceiveData(DSTC_REQUEST::ACB, _requestData, ifds::DSTC0015_VW, DSTCRequestor(getSecurity(), false) );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY ACBList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   pObjOut = new ACBRecord( *this );
   ((ACBRecord*)( pObjOut ))->init ( const_cast<BFData&>(data) );

   MFAccount *pMFAcc;
   DString dump( _accountNum );
   SEVERITY sevRtn = getWorkSession().getMFAccount( BF::HOST, dump, pMFAcc );
   if( WARNING > sevRtn )
   {
      AccountHoldingsByCurrencyList *pAccountHoldingsByCurrencyList;
      pMFAcc->getAccountHoldingsByCurrencyList( pAccountHoldingsByCurrencyList, BF::HOST );
      pAccountHoldingsByCurrencyList->createCurrencyObject( data, BF::HOST );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY ACBList::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );

   if ( idField == ifds::ACBPlugAmt )
   {
      setFieldNoValidate(ifds::IsNewOrUpdate,  I_("Y"), BF::HOST, false, true);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ACBList.cpp-arc  $
 * 
 *    Rev 1.15   Mar 14 2005 15:00:30   LIPATRI
 * TESTING  PVCS V8 ...
 * 
 *    Rev 1.14   Mar 21 2003 17:53:46   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.13   Oct 09 2002 23:53:50   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.12   Aug 29 2002 12:54:48   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.11   22 May 2002 18:26:00   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.10   03 May 2001 14:05:48   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.9   Mar 12 2001 12:58:44   VASILEAD
 * Modified for FUNDcom release
 * 
 *    Rev 1.8   Feb 13 2001 16:36:52   HSUCHIN
 * Async recieved used
 * 
 *    Rev 1.7   Jan 18 2001 16:03:22   YINGBAOL
 * add eTracker
 * 
 *    Rev 1.6   Dec 17 2000 20:24:54   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.5   15 Nov 2000 15:29:46   SMITHDAV
 * Use new ReceiveData and do some cleanup.
 * 
 *    Rev 1.4   31 Oct 2000 15:32:30   SMITHDAV
 * Change getMore to create response on the heap.
 * 
 *    Rev 1.3   30 Oct 2000 11:24:22   SMITHDAV
 * Changed to use the new data brokering system.
 * 
 *    Rev 1.2   Sep 01 2000 15:24:44   HUANGSHA
 * added pClientLocale in getField(..)
 * 
 *    Rev 1.1   May 04 2000 16:56:10   WINNIE
 * change CURRENCY_HPP to CURRENCYCLASS_HPP
 * 
 *    Rev 1.0   Feb 15 2000 10:59:46   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.10   Jan 05 2000 20:10:36   BUZILA
 * adding list flag
 * 
 *    Rev 1.9   Dec 12 1999 16:25:04   POPESCUS
 * Xchgdata issue; create and delete the object in the CBO
// 
*/