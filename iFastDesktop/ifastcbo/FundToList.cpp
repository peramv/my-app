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
//    Copyright 2000 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : FundToList.cpp
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : Mar 31, 2000
//
// ^CLASS    : FundToList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "fundtolist.hpp"
#include <ifastdataimpl\dse_dstc0099_vw.hpp>
#include <ifastdataimpl\dse_dstc0099_req.hpp>
#include "funddetaillist.hpp"
#include "mgmtcooptions.hpp"
#include "mgmtco.hpp"

namespace CORFAX
{
   extern CLASS_IMPORT const DSTCHost HOST;
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest FUND_TO;
}


namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME         = I_( "FundToList" );
   const I_CHAR * const YES               = I_( "Y" );
   const I_CHAR * const NO                = I_( "N" );

}

namespace CND
{
   extern CLASS_IMPORT const long ERR_DATA_NOT_FOUND;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId TradeDateLagExch;
   extern CLASS_IMPORT const BFTextFieldId ReinvInOtherFundAllowed;
}

//******************************************************************************
FundToList::FundToList( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent )
,frFund_(NULL_STRING)
,frClass_(NULL_STRING)
,toFund_(NULL_STRING)
,toClass_(NULL_STRING)
,track_(NO)
,pageName_(NULL_STRING)
,buySell_(NULL_STRING)
,fullPartial_(NULL_STRING)
,tradeAllowed_(NULL_STRING)
,applySrcOfFund_(NULL_STRING)
,bHasRecord_(false)
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   setObjectAsList( );
   setVersionable( false );
}

//******************************************************************************
FundToList::~FundToList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
// The data object will be deleted after retrieve the value, so this class will 
// be very light.
SEVERITY FundToList::init( )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   BFData requestData(ifds::DSTC0099_REQ);
   bHasRecord_ = false;
   DString mgmtCoIdOut;
   requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   requestData.setElementValue( ifds::FromFund, frFund_ );
   requestData.setElementValue( ifds::FromClass, frClass_ );
   requestData.setElementValue( ifds::FundSponsor, NULL_STRING );
   requestData.setElementValue( ifds::ToFund, toFund_ );
   requestData.setElementValue( ifds::ToClass, toClass_ );

   requestData.setElementValue( ifds::Track, track_ );
   requestData.setElementValue( ifds::Activity, pageName_ );

   BFData *response = new BFData(ifds::DSTC0099_VW);
   DSTCRequestor requestor (getSecurity(), true, true );

   if (BFDataBroker::getInstance()->receive (DSTC_REQUEST::FUND_TO, 
                                             requestData, 
                                             *response, 
                                             requestor) > WARNING)
   {
      delete response;
      response = NULL;
   }

   fullPartial_ = NULL_STRING;
   buySell_ = NULL_STRING;
   shortTernFee_ = NULL_STRING;
   applySrcOfFund_ = NULL_STRING;

   if ( response )
   {
      int nNumRepeats = response->getRepeatCount();
      if (nNumRepeats > 0)
      {
		const BFData dataObj( response->getRepeat(0) );
        
		fullPartial_ = dataObj.getElementValue(ifds::FullorPartial );	
        buySell_ = dataObj.getElementValue(ifds::BuySell );
        buySell_.strip().upperCase();
        fullPartial_.strip();
        shortTernFee_ = dataObj.getElementValue(ifds::ShortTermFee );
        shortTernFee_.strip().upperCase();
		tradeAllowed_ = dataObj.getElementValue(ifds::TransFundTradeAllowed);
		applySrcOfFund_ = dataObj.getElementValue(ifds::ApplySrcOfFund);
		applySrcOfFund_.strip();

        bHasRecord_ = true;
      }
      delete response;
      response = NULL;
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//*******************************************************************************
bool  FundToList::isTransferAllowed(DString& frFund,
                                    DString& frClass,
                                    DString& toFund,
                                    DString& toClass, 
                                    const DString& dstrTrack,
                                    const DString& dstrPageName)
{

   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "isTransferAllowed" ) );

   track_=dstrTrack;
   pageName_=dstrPageName;
   bool bAllowTransfer = false;
   if( isSameFundClass( frFund, frClass, toFund,toClass) || !bHasRecord_)
   {
      if( init( ) > WARNING ) // there is an error, transfer is not allowed.
      {
         CLEARCONDITIONS ();
         return  bAllowTransfer;
      }
   }
   bAllowTransfer = true;

   DString strTradeDateLag;

   MgmtCoOptions* pMgmtCoOptions=NULL;
   if( getMgmtCo().getMgmtCoOptions( pMgmtCoOptions ) <= WARNING )
   {
      pMgmtCoOptions->getField( ifds::TradeDateLagExch, strTradeDateLag, BF::HOST, false );
   }
   bool bCheckTradeLag = (strTradeDateLag.strip().upperCase() == YES);
   if (bCheckTradeLag )
   {
      FundDetailList *pFundDetailList = NULL;
      if( getMgmtCo().getFundDetailList(pFundDetailList) <= WARNING )
         if( pFundDetailList ){
            bAllowTransfer = pFundDetailList->isSameTradeDateLag(frFund_, frClass, toFund, toClass);
         }
   }
   return bAllowTransfer;
}

//*******************************************************************************
bool  FundToList::isTransferAllowed(DString& frFund,
                                    DString& frClass,
                                    DString& toFund,
                                    DString& toClass, 
                                    DString& dstrFullPartial,
                                    const DString& dstrTrack,
                                    const DString& dstrPageName)
{
   track_=dstrTrack;
   pageName_=dstrPageName;
   bool bAllowTransfer = isTransferAllowed( frFund, frClass, toFund,toClass );
   dstrFullPartial = fullPartial_;

   return bAllowTransfer;
}

//*******************************************************************************
bool FundToList::isBuySell (DString& frFund,
                            DString& frClass,
                            DString& toFund,
                            DString& toClass,
                            const DString& dstrTrack,
                            const DString& dstrPageName)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "isBuySell" ) );

   track_=dstrTrack;
   pageName_=dstrPageName;
   bool bBuySel = false;
   if( isSameFundClass( frFund, frClass, toFund,toClass) || !bHasRecord_)
   {
      if( init( ) > WARNING ) // there is an error, transfer is not allowed.
      {
         CLEARCONDITIONS ();
         return  bBuySel;	  
      }
   }

   bBuySel = buySell_ == YES;

   return bBuySel;
}

//**************************************************************************
// check if the paramter come in is the same as the previous one.
// if not, replace the older one with the new one
//
bool FundToList::isSameFundClass(DString& frFund,
                                 DString& frClass, 
                                 DString& toFund,
                                 DString& toClass)
{
   frFund.strip().upperCase();
   frClass.strip().upperCase();
   toFund.strip().upperCase();
   toClass.strip().upperCase();
   bool bRet = frFund != frFund_ || frClass != frClass_ || toFund != toFund_ || toClass != toClass_ ;
   if( bRet )
   { 
      frFund_ = frFund;
      frClass_= frClass;
      toFund_ = toFund;
      toClass_ = toClass;
   }
   return bRet;
}

//******************************************************************************
DString FundToList::getShortTermFee(DString& frFund, 
                                    DString& frClass,
                                    DString& toFund,
                                    DString& toClass,
                                    const DString& dstrTrack,
                                    const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getShotTermFee" ) );

   track_=dstrTrack;
   pageName_=dstrPageName;
   bool bBuySel = false;
   if( isSameFundClass( frFund, frClass, toFund,toClass) || !bHasRecord_)
   {
      if( init( ) > WARNING ) // there is an error, transfer is not allowed.
      {
         CLEARCONDITIONS ();	  
      }
   }

   return shortTernFee_;
}

//*******************************************************************************
bool  FundToList::isExchangeAllowed(const DString& frFund,
                                    const DString& frClass,
                                    const DString& toFund,
                                    const DString& toClass, 
                                    const DString& dstrTrack,
                                    const DString& dstrPageName)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "isExchangeAllowed" ) );

   track_=dstrTrack;
   pageName_=dstrPageName;
   DString fundFrom(frFund), classFrom(frClass), fundTo(toFund), classTo(toClass); 
   if( isSameFundClass( fundFrom, classFrom, fundTo, classTo) || !bHasRecord_)
   {
      if( init( ) > WARNING ) // there is an error, exchange is not allowed.
      {
         CLEARCONDITIONS ();	  
      }
   }

   return tradeAllowed_ != I_("2");
}

//*******************************************************************************
DString FundToList::getApplySrcOfFund(const DString& frFund,
									  const DString& frClass,
									  const DString& toFund,
									  const DString& toClass, 
									  const DString& dstrTrack,
									  const DString& dstrPageName)
{

	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getApplySrcOfFund" ) );

	track_ = dstrTrack;
	pageName_ = dstrPageName;
	DString fundFrom(frFund), classFrom(frClass), fundTo(toFund), classTo(toClass); 

	if (!fundFrom.empty() && !classFrom.empty() && (isSameFundClass (fundFrom, classFrom, fundTo, classTo) || !bHasRecord_))
	{
		if( init( ) > WARNING ) // there is an error, exchange is not allowed.
		{
			CLEARCONDITIONS ();	  
		}
	}

	return applySrcOfFund_;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FundToList.cpp-arc  $
 // 
 //    Rev 1.31   Nov 24 2004 17:28:14   yingbaol
 // PET1117:fix isSameFundClass
 // 
 //    Rev 1.30   Nov 24 2004 14:15:58   popescu
 // PET 1117, passed the correct request object to Receive, and fixed typo
 // 
 //    Rev 1.29   Nov 18 2004 14:58:24   YINGBAOL
 // PET1117: performance tunning, add getShotTermFee method
 // 
 //    Rev 1.28   Nov 18 2004 13:28:12   YINGBAOL
 // PET1117: Perfermance Tunning
 // 
 //    Rev 1.27   Nov 14 2004 14:43:18   purdyech
 // PET910 - .NET Conversion
 // 
 //    Rev 1.26   Oct 17 2003 14:58:26   FENGYONG
 // PTS 10022774, eadvisor exchange not allowed transfer between funds
 // 
 //    Rev 1.25   Mar 21 2003 18:12:12   PURDYECH
 // BFDataGroupId/BFContainerId changeover
 // 
 //    Rev 1.24   Jan 16 2003 18:55:32   WINNIE
 // Add new method to take parameter to check if partial or full exchange is allowed. Enhancement for DCAF fund
 // 
 //    Rev 1.23   Jan 03 2003 10:40:20   HERNANDO
 // Undid changes.
 // 
 //    Rev 1.22   Jan 02 2003 18:49:48   HERNANDO
 // Check flag to determine whether reinvestment to different funds is allowed.
 // 
 //    Rev 1.21   Oct 09 2002 23:54:34   PURDYECH
 // PVCS Database Conversion
 // 
 //    Rev 1.20   Aug 29 2002 12:55:58   SMITHDAV
 // ClientLocale and typed field changes.
 // 
 //    Rev 1.19   22 May 2002 18:28:46   PURDYECH
 // BFData Implementation
 // 
 //    Rev 1.18   Feb 25 2002 18:55:44   PURDYECH
 // Phase 1 of BFData Rollout - Base Component Compatibility
 // 
 //    Rev 1.17   12 Dec 2001 16:29:34   KOVACSRO
 // Added TradeDateLag logic.
 // 
 //    Rev 1.16   20 Nov 2001 19:47:52   WINNIE
 // new method isBuySell for NFEL enhancement : fee only charge when BuySell = Y
 // 
 //    Rev 1.15   03 May 2001 14:06:38   SMITHDAV
 // Session management restructuring.
 // 
 //    Rev 1.14   Mar 21 2001 15:06:50   YINGZ
 // delete one of the init 
 // 
 //    Rev 1.13   Mar 21 2001 12:27:44   FENGYONG
 // get fundtolist by from fund , fromclass or sponsorcode
 // 
 //    Rev 1.12   Mar 12 2001 15:00:12   FENGYONG
 // get list by from sponsorcode
 // 
 //    Rev 1.11   Mar 10 2001 15:13:28   WINNIE
 // pass in the fromfund and fromclass to get the list of valid tofund/toclass
 // 
 //    Rev 1.10   Jan 18 2001 16:05:12   YINGBAOL
 // add eTracker
 // 
 //    Rev 1.9   Dec 17 2000 20:23:30   OLTEANCR
 // changed to use a precompiled header
 // 
 //    Rev 1.8   Dec 06 2000 11:35:18   OLTEANCR
 // modif. ReceiveData
 // 
 //    Rev 1.7   Dec 04 2000 13:23:04   VASILEAD
 // Modified building of the key
 // 
 //    Rev 1.6   Nov 02 2000 13:23:06   YINGBAOL
 // use new databroker
 // 
 //    Rev 1.5   May 31 2000 16:15:46   YINGBAOL
 // more validation added
 // 
 //    Rev 1.4   Apr 20 2000 16:38:44   BUZILA
 // changed to MgmtCoId
 // 
 //    Rev 1.3   Apr 15 2000 15:28:26   WINNIE
 // fix for index set up in funtolist; fix allowable exchange edit chk; fix account balance ;
 // 
 //    Rev 1.2   Apr 14 2000 17:55:40   WINNIE
 // Move validation to Groupfund and MFAccount CBO to allow other CBO to use the same method. Bug fix for NumOfDecimals function
 // 
 //    Rev 1.1   Apr 07 2000 18:24:16   WINNIE
 // add index
 // 
 //    Rev 1.0   Apr 03 2000 08:49:54   BUZILA
 // Initial revision.
 * 
*/