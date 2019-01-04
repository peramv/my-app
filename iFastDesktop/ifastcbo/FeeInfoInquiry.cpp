//******************************************************************************
//
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
// ^FILE   : FeeInfoInquiry.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : FeeInfoInquiry
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "feeinfoinquiry.hpp"
#include "feeinfo.hpp"
#include "currencyclass.hpp"
#include <ifastdataimpl\dse_dstc0107_req.hpp>
#include <ifastdataimpl\dse_dstc0107_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest FEEINFOINQUIRY;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME   = I_( "FeeInfoInquiry" );
}

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long ERR_DATA_NOT_FOUND;
}


//******************************************************************************
FeeInfoInquiry::FeeInfoInquiry( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
, _requestData(ifds::DSTC0107_REQ)
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   setObjectAsList( );
}

//******************************************************************************
FeeInfoInquiry::~FeeInfoInquiry()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************

SEVERITY FeeInfoInquiry::init( const DString& dstrFundCode,
                               const DString& dstrClassCode,
                               const DString& FundSponsor,
                               const DString& dstrTrack,
                               const DString& dstrPageName )

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   DString mgmtCoIdOut;
   _requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   _requestData.setElementValue( ifds::FundCode, dstrFundCode );
   _requestData.setElementValue( ifds::ClassCode, dstrClassCode );
   _requestData.setElementValue( ifds::FundSponsor, FundSponsor );
   _requestData.setElementValue( ifds::Track, dstrTrack );
   _requestData.setElementValue( ifds::Activity, dstrPageName );

   ReceiveData(DSTC_REQUEST::FEEINFOINQUIRY, _requestData, ifds::DSTC0107_VW, DSTCRequestor( getSecurity(), true) );
   DString dstrFundCodeCopy(dstrFundCode);
   DString dstrClassCodeCopy(dstrClassCode);
   DString FundSponsorCopy(FundSponsor);

   m_strFundCode = dstrFundCodeCopy.strip();
   m_strClassCode = dstrClassCodeCopy.strip();
   m_strFundSponsor = FundSponsorCopy.strip();
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void FeeInfoInquiry::buildKey( const DString& strFund, const DString& strClass, DString &strKey )
{
   strKey = strFund;
   strKey.strip().upperCase();
   strKey += I_("  ");
   strKey += strClass;
   strKey.strip().upperCase();
}

//******************************************************************************
void FeeInfoInquiry::getStrKey (DString &strKey, const BFData *data)
{
   TRACE_METHOD( CLASSNAME, I_( "getStrKey" ) );

   if( data )
   {
      DString strFund = data->getElementValue( ifds::FundCode );
      DString strClass = data->getElementValue( ifds::ClassCode ) ;
      strKey = strFund.strip().upperCase();
      strKey += I_("  ");
      strKey += strClass.strip().upperCase();
   }
   else
   {
      BFCBO::getStrKey( strKey , NULL );
   }

}
//******************************************************************************

void FeeInfoInquiry::getField( const BFFieldId& idField, DString& strFieldValue, 
                               const BFDataGroupId& idDataGroup, bool formattedReturn ) const
{

   BFCBO::getField(idField, strFieldValue, idDataGroup, formattedReturn );
}
//******************************************************************************

SEVERITY FeeInfoInquiry::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   FeeInfo * pFeeInfo = new FeeInfo( *this );
   pFeeInfo->init( data );
   pObjOut = pFeeInfo;

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
bool FeeInfoInquiry::isChanged(const DString strFundCode, const DString strClassCode, 
                               const DString strFundSponsor)
{
   TRACE_METHOD( CLASSNAME, I_( "isChanged" ) );
   DString copyFundCode(strFundCode);
   DString copyClassCode(strClassCode);
   DString copyFundSponsor(strFundSponsor);

   if( copyFundCode.strip() != m_strFundCode )
      return(true);
   if( copyClassCode.strip() != m_strClassCode )
      return(true);
   if( copyFundSponsor.strip() != m_strFundSponsor )
      return(true);
   return(false);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FeeInfoInquiry.cpp-arc  $
// 
//    Rev 1.10   Nov 14 2004 14:40:00   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.9   Mar 21 2003 18:08:58   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.8   Oct 09 2002 23:54:28   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.7   Aug 29 2002 12:55:48   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.6   22 May 2002 18:28:36   PURDYECH
// BFData Implementation
// 
//    Rev 1.5   Oct 30 2001 17:59:58   ZHANGCEL
// Minor changes
// 
//    Rev 1.4   08 Aug 2001 17:06:56   KOVACSRO
// Added isChanged().
// 
//    Rev 1.3   03 May 2001 14:06:28   SMITHDAV
// Session management restructuring.
// 
//    Rev 1.2   Mar 29 2001 14:00:18   FENGYONG
// Add creatobject
// 
//    Rev 1.1   Mar 22 2001 09:54:20   FENGYONG
// change to get the whole list
// 
//    Rev 1.0   Mar 21 2001 12:18:18   FENGYONG
// Initial revision.
 // 
 //    Rev 1.9   Jan 18 2001 16:03:26   YINGBAOL
 // add eTracker
 // 
 //    Rev 1.8   Dec 17 2000 20:22:24   OLTEANCR
 // changed to use a precompiled header
 // 
 //    Rev 1.7   15 Nov 2000 15:30:14   SMITHDAV
 // Use new ReceiveData and do some cleanup.
 // 
 //    Rev 1.6   Nov 07 2000 15:52:38   OLTEANCR
 // new data brokering
 // 
 //    Rev 1.5   Nov 02 2000 16:30:14   HUANGSHA
 // change in getField
 // 
 //    Rev 1.4   Sep 01 2000 15:25:22   HUANGSHA
 // added pClientLocale in setField(...)
 // 
 //    Rev 1.3   Jun 13 2000 17:55:50   DT24433
 // new Infra interfaces use ClientLocale
 * 
 */