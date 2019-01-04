//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1999 by DST Systems, Inc.
//
//*****************************************************************************
//
// ^FILE   : FreeUnitList.cpp
// ^AUTHOR : Chin Hsu
// ^DATE   : July 26, 1999
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : FreeUnitList
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS : Canadian Increment 1
//
//*****************************************************************************
#include "stdafx.h"
#include "accountholdingsbycurrencylist.hpp"
#include "currencyclass.hpp"
#include "freeunitlist.hpp"
#include <ifastdataimpl\dse_dstc0019_vw.hpp>
#include <ifastdataimpl\dse_dstc0019_req.hpp>
#include "mfaccount.hpp"


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest FREE_UNIT;
}

namespace
{
   const I_CHAR * const CLASSNAME = I_( "FreeUnitList" );
   const I_CHAR * const RECORDTYPE = I_( "Record Type" );
}


//******************************************************************************
FreeUnitList::FreeUnitList( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
   requestData =  new BFData(ifds::DSTC0019_REQ); 
}

//******************************************************************************
FreeUnitList::~FreeUnitList()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   if( requestData )
   {
      delete requestData; requestData = NULL;
   }

}

//
// Initialization from the Fund Code and Account Number
//
//******************************************************************************
SEVERITY FreeUnitList::init( const DString& AccountNum,
                             const DString& AcctLvlDSCFund,
                             const DString& AllFundMode,
                             const DString& AllFundGroupMode,
                             const DString& dstrTrack,
                             const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );

   DString mgmtCoIdOut;
   requestData->setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   requestData->setElementValue( ifds::AccountNum, AccountNum );
   _accountNum = AccountNum;
   _accountNum.strip();
   requestData->setElementValue( ifds::AcctLvlDSCFund, AcctLvlDSCFund );
   requestData->setElementValue( ifds::AllFundMode, AllFundMode );
   requestData->setElementValue( ifds::AllFundGroupMode, AllFundGroupMode );
   requestData->setElementValue( ifds::Track, dstrTrack );
   requestData->setElementValue( ifds::Activity, dstrPageName );

   ReceiveData(DSTC_REQUEST::FREE_UNIT, *requestData, ifds::DSTC0019_VW, DSTCRequestor( getSecurity(), false) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY FreeUnitList::init( const BFData& data )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   attachDataObject( const_cast<BFData&>(data), false, true );


   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
SEVERITY FreeUnitList::search( bool bClearPreviousSearch )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "search" ) );

   if( bClearPreviousSearch )
   {
      eraseDataObjectContainers();
      eraseObjectContainer();

      requestData->setElementValue( ifds::NextKey, NULL_STRING );
   };

   ReceiveData(DSTC_REQUEST::FREE_UNIT, *requestData, ifds::DSTC0019_VW, DSTCRequestor( getSecurity(), false) );
   return(GETCURRENTHIGHESTSEVERITY());


}

//******************************************************************************
void FreeUnitList::setParameter( const DString& elementName, const DString& value )
{
   TRACE_METHOD( CLASSNAME, I_( "setParameter" ) );

   requestData->setElementValue( elementName, value, false, false );
}

//******************************************************************************
void FreeUnitList::getStrKey( DString &strKey, const BFData* data )
{
   TRACE_METHOD( CLASSNAME, I_( "getStrKey" ) );
   DString strRT, tempKey;
   BFCBO::getStrKey( tempKey, data );
   if( data )
   {
      data->getElementValue( ifds::RecordType, strRT );
      strKey = tempKey + I_( " " ) + strRT.strip();
   }
   else
   {
      strKey = tempKey;
   }
}

//******************************************************************************
SEVERITY FreeUnitList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   pObjOut = new FreeUnitList((BFAbstractCBO&)(*this));
   ( ( FreeUnitList* ) ( pObjOut ) )->init( const_cast<BFData&>(data) );

   MFAccount *pMFAcc;
   DString dump( _accountNum );
   SEVERITY sevRtn = getWorkSession().getMFAccount( BF::HOST, dump, pMFAcc );
   if( WARNING > sevRtn )
   {
      DString recType;
      data.getElementValue( ifds::RecordType, recType, false );
      recType.strip();

      if( recType == I_( "Total" ) ) // Store only the total for a fund-class pair
      {
         AccountHoldingsByCurrencyList *pAccountHoldingsByCurrencyList;
         pMFAcc->getAccountHoldingsByCurrencyList( pAccountHoldingsByCurrencyList, BF::HOST );
         pAccountHoldingsByCurrencyList->createCurrencyObject( data, BF::HOST );
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY FreeUnitList::init2( const DString& AccountNum,
							  const DString& FundCode,
							  const DString& ClassCode,
                              const DString& FundGroup,
                              const DString& dstrTrack,
                              const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init2") );

   DString mgmtCoIdOut;
   requestData->setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   requestData->setElementValue( ifds::AccountNum, AccountNum );
   requestData->setElementValue( ifds::FundCode, FundCode );
   requestData->setElementValue( ifds::ClassCode, ClassCode );
   requestData->setElementValue( ifds::FundGroup, FundGroup );
   _accountNum = AccountNum;
   _accountNum.strip();
   requestData->setElementValue( ifds::AllFundMode, I_("N") );
   requestData->setElementValue( ifds::AllFundGroupMode, I_("N") );
   requestData->setElementValue( ifds::Track, dstrTrack );
   requestData->setElementValue( ifds::Activity, dstrPageName );

   ReceiveData(DSTC_REQUEST::FREE_UNIT, *requestData, ifds::DSTC0019_VW, DSTCRequestor( getSecurity(), true) );

   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FreeUnitList.cpp-arc  $
 * 
 *    Rev 1.16   May 02 2005 08:39:10   hernando
 * PET1024 FN10 - Acct Level/Fund Level DSC Enhancement.
 * 
 *    Rev 1.15   Nov 14 2004 14:41:08   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.14   Nov 05 2003 16:24:44   linmay
 * P843_FN251
 * 
 *    Rev 1.13   Mar 21 2003 18:10:20   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.12   Oct 09 2002 23:54:30   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.11   Aug 29 2002 12:55:52   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.10   22 May 2002 18:28:40   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.9   03 May 2001 14:06:28   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.8   Mar 28 2001 14:47:14   VASILEAD
 * Attach only the totals for the free units
 * 
 *    Rev 1.7   Mar 12 2001 12:58:46   VASILEAD
 * Modified for FUNDcom release
 * 
 *    Rev 1.6   Jan 18 2001 16:04:50   YINGBAOL
 * add eTracker
 * 
 *    Rev 1.5   Dec 17 2000 20:23:26   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.4   Dec 06 2000 11:27:28   OLTEANCR
 * modif. ReceiveData
 * 
 *    Rev 1.3   Dec 06 2000 11:25:46   OLTEANCR
 * modif ReceiveData
 * 
 *    Rev 1.2   Dec 06 2000 11:24:12   OLTEANCR
 * changed ReceiveData
 * 
 *    Rev 1.1   Nov 02 2000 13:23:20   YINGBAOL
 * use new databroker
 * 
 *    Rev 1.0   Feb 15 2000 10:59:58   SMITHDAV
 * Initial revision.
// 
//    Rev 1.7   Jan 05 2000 20:10:44   BUZILA
// adding list flag
// 
//    Rev 1.6   Dec 12 1999 16:25:22   POPESCUS
// Xchgdata issue; create and delete the object in the CBO
// 
*/