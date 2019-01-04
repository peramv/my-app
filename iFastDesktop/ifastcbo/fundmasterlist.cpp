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
//    Copyright 1998 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : FundMasterList.cpp
// ^AUTHOR : Mike Metzger
// ^DATE   : Mar 5, 1999
//
// ^CLASS    : FundMasterList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "fundmasterlist.hpp"
#include "fundmaster.hpp"
#include "mgmtco.hpp"
#include <ifastdataimpl\dse_dstc0063_vw.hpp>
#include <ifastdataimpl\dse_dstc0063_req.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest FUND_MASTER;
}

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME = I_( "FundMasterList" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId FundCode;
}

namespace FUND_TYPE
{
   extern const I_CHAR * const MONEY_MARKET  = I_("I");
   extern const I_CHAR * const GIC           = I_( "GIC" );
   extern const I_CHAR * const MPS           = I_( "MPS" );
}

namespace FUND_CATEGORY
{
   const I_CHAR * const MUTUAL               = I_("M");
   const I_CHAR * const HEDGE                = I_("H");
   const I_CHAR * const WRAP                 = I_("W");
   const I_CHAR * const SEGREGATED           = I_("S");
   const I_CHAR * const LSIF                 = I_("L");
   const I_CHAR * const GIA                  = I_("G");
   const I_CHAR * const DIF                  = I_("D");
}

namespace OTHER_FUND_TYPE
{
   const I_CHAR * const DEPOT = I_("01");
   const I_CHAR * const THIRD_PARTY = I_("02");
   const I_CHAR * const UP_TO_CERTIFICATE = I_("03");
   const I_CHAR * const GLOBAL_CERTIFICATE = I_("04");
}

//******************************************************************************
FundMasterList::FundMasterList( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   setVersionable( false );

   setObjectAsList( );
}

//******************************************************************************
FundMasterList::~FundMasterList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY FundMasterList::init (const DString& dstrTrack,const DString& dstrPageName)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   BFData queryData (ifds::DSTC0063_REQ);
   BFData *receivedData = new BFData (ifds::DSTC0063_VW);

   
   DString mgmtCoIdOut;
   queryData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
   queryData.setElementValue (ifds::Track, dstrTrack );
   queryData.setElementValue (ifds::Activity, dstrPageName);
   AsyncReceiveData ( DSTC_REQUEST::FUND_MASTER, 
                      queryData, 
                      *receivedData, 
                      DSTCRequestor (getSecurity(), true));
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void FundMasterList::buildKey (const DString &strFund, DString &strKey)
{
   strKey = strFund;
   strKey.strip();
   strKey.upperCase();
}

//******************************************************************************
void FundMasterList::getStrKey (DString &strKey, const BFData *data)
{
   TRACE_METHOD( CLASSNAME, I_("getStrKey"));

   if( data )
   {
      buildKey (data->getElementValue (ifds::FundCode), strKey);
   }
   else
   {
      BFCBO::getStrKey (strKey, NULL);
   }
}

//*****************************************************************************
bool FundMasterList::isMoneyMarketFund (const DString &fundCode)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("isMoneyMarketFund"));
   return fundType (fundCode) == FUND_TYPE::MONEY_MARKET;
}

//*****************************************************************************
bool FundMasterList::isGICFund (const DString &fundCode) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("isGICFund"));
   FundMaster *pFundMaster = NULL;
   DString fundType_ = fundType (fundCode),
      investProd;

   fundType_.upperCase();
   if (getFundMaster (fundCode, BF::HOST, pFundMaster))
   {
      pFundMaster->getField (ifds::InvestProd, investProd, BF::HOST, false );
      investProd.upperCase();
   }
   return DSTCommonFunctions::codeInList (fundType_, I_("S,C")) || investProd == FUND_TYPE::GIC;
}

//*****************************************************************************
bool FundMasterList::isMPSFund (const DString &fundCode) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("isMPSFund"));
   FundMaster *pFundMaster = NULL;
   DString investProd;

   if (getFundMaster (fundCode, BF::HOST, pFundMaster))
   {
      pFundMaster->getField (ifds::InvestProd, investProd, BF::HOST, false );
      investProd.upperCase();
   }
   return investProd == FUND_TYPE::MPS;
}

//*****************************************************************************
bool FundMasterList::isLSIFFund (const DString &fundCode)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("isLSIFFund"));

   return fundCategory (fundCode) == FUND_CATEGORY::LSIF;
}

//*****************************************************************************
bool FundMasterList::isMutualFund (const DString &fundCode)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("isMutualFund"));

   return fundCategory (fundCode) == FUND_CATEGORY::MUTUAL;
}

//*****************************************************************************
bool FundMasterList::isHedgeFund (const DString &fundCode)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("isHedgeFund"));

   return fundCategory (fundCode) == FUND_CATEGORY::HEDGE;
}

//*****************************************************************************
bool FundMasterList::isWrapFund (const DString &fundCode)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("isWrapFund"));

   return fundCategory (fundCode) == FUND_CATEGORY::WRAP;
}

//*****************************************************************************
bool FundMasterList::isSegregatedFund (const DString &fundCode)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("isSegregatedFund"));

   return fundCategory (fundCode) == FUND_CATEGORY::SEGREGATED;
}

//******************************************************************************
bool FundMasterList::isDepotFund (const DString &fundCode)
{
   return otherFundType (fundCode) == OTHER_FUND_TYPE::DEPOT;
}

//******************************************************************************
bool FundMasterList::is3rdPartyFund (const DString &fundCode)
{
   return otherFundType (fundCode) == OTHER_FUND_TYPE::THIRD_PARTY;
}

//******************************************************************************
bool FundMasterList::isUpToCertificateSpecialFund (const DString &fundCode)
{
   return otherFundType (fundCode) == OTHER_FUND_TYPE::UP_TO_CERTIFICATE;
}

//******************************************************************************
bool FundMasterList::isGlobalCertificateSpecialFund (const DString &fundCode)
{
   return otherFundType (fundCode) == OTHER_FUND_TYPE::GLOBAL_CERTIFICATE;
}

//*****************************************************************************
bool FundMasterList::isGIAFund (const DString &fundCode)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("isGIAFund"));

   return fundCategory (fundCode) == FUND_CATEGORY::GIA;
}

//*****************************************************************************
bool FundMasterList::isDIFFund (const DString &fundCode)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("isDIFFund"));

   return fundCategory (fundCode) == FUND_CATEGORY::DIF;
}

//*****************************************************************************
bool FundMasterList::isSEGFund (const DString &fundCode)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("isSEGFund"));

   return fundCategory (fundCode) == FUND_CATEGORY::SEGREGATED;
}

//******************************************************************************
bool FundMasterList::isPUEVCapableFund (const DString &fundCode)
{
   FundMaster *pFundMaster = NULL;
   bool bIsPUEVCapable = false;

   if (getFundMaster (fundCode, BF::HOST, pFundMaster))
   {
      DString puevCapable;
      
      pFundMaster->getField (ifds::PUEVCapable, puevCapable, BF::HOST, false);
      puevCapable.upperCase();
      bIsPUEVCapable = puevCapable == I_("Y");
   }
   return bIsPUEVCapable;
}

//******************************************************************************
bool FundMasterList::isInvestroCapableFund (const DString &fundCode)
{
   FundMaster *pFundMaster = NULL;
   bool bInvestroCapable = false;

   if (getFundMaster (fundCode, BF::HOST, pFundMaster))
   {
      DString investroCapable;
      
      pFundMaster->getField (ifds::InvestroCapable, investroCapable, BF::HOST, false);
      investroCapable.upperCase();
      bInvestroCapable = investroCapable == I_("Y");
   }
   return bInvestroCapable;
}

//******************************************************************************
SEVERITY FundMasterList::getFundName ( const DString &fundCode,
                                       DString &fundName)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_( "getFundName" ));
   return getFundName ( fundCode,
                        ifds::ElongName1,
                        fundName);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY FundMasterList::getFundName ( const DString &fundCode,
                                       const BFFieldId &nameFieldId,
                                       DString &fundName)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_( "getFundName" ));
   assert ( nameFieldId == ifds::ElongName1 ||
            nameFieldId == ifds::ElongName2 ||
            nameFieldId == ifds::EShortName ||
            nameFieldId == ifds::FLongName ||
            nameFieldId == ifds::FLongName2 ||
            nameFieldId == ifds::FShortName);
   FundMaster *pFundMaster = NULL;

   if (getFundMaster (fundCode, BF::HOST, pFundMaster))
   {
      pFundMaster->getField (nameFieldId, fundName, BF::HOST, false);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool FundMasterList::getFundMaster ( const DString &fundCode, 
                                     const BFDataGroupId &idDataGroup, 
                                     FundMaster *&pFundMaster) 
{  
   pFundMaster = NULL;
   if (!fundCode.empty())
   {
      DString strKey;
      BFObjIter iter (*this, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED);

      buildKey (fundCode, strKey); 
      if (iter.positionByKey (strKey))
      {
         pFundMaster = dynamic_cast<FundMaster *>(iter.getObject());
      }
   }
   return !!pFundMaster;
}

//******************************************************************************
SEVERITY FundMasterList::doCreateObject ( const BFData &data, 
                                          BFCBO *&pObjOut) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   FundMaster * pFundMaster = new FundMaster (*this);
   pFundMaster->init (data);
   pObjOut = pFundMaster;

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool FundMasterList::IsFundExist ( const DString& dstrFundCode, 
                                   const BFDataGroupId& idDataGroup) 
{
   BFData data;
   data.setElementValue( ifds::FundCode, dstrFundCode, true, false );
   DString dstrKey;
   getStrKey( dstrKey, &data );
   BFObjIter iterList( *this, BF::HOST, 0, BFObjIter::ITERTYPE::NON_DELETED );
   return(iterList.positionByKey( dstrKey ));

}
//*****************************************************************************
bool FundMasterList::IsFundValidAtDate( const DString& dstrFundCode, 
                                        const DString& dstrEffectiveDate, 
                                        const BFDataGroupId& idDataGroup) 
{
   DString dstrFundEffectiveDate, dstrFundStopDate;
   BFData data;
   data.setElementValue( ifds::FundCode, dstrFundCode, true, false );
   DString dstrKey;
   getStrKey( dstrKey, &data );
   BFObjIter iterList( *this, BF::HOST, 0, BFObjIter::ITERTYPE::NON_DELETED );
   if( iterList.positionByKey( dstrKey ) )
   {
      iterList.getObject()->getField( ifds::EffectiveDate, 
                                      dstrFundEffectiveDate, idDataGroup );
      dstrFundEffectiveDate.strip();

      iterList.getObject()->getField( ifds::StopDate, 
                                      dstrFundStopDate, idDataGroup );
      dstrFundStopDate.strip();
      if (DSTCommonFunctions::IsDateBetween (dstrFundEffectiveDate, dstrFundStopDate,dstrEffectiveDate))
         return(true);
   }

   return(false);
}

//*****************************************************************************
DString FundMasterList::otherFundType (const DString &fundCode)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("otherFundType"));

   FundMaster *pFundMaster = NULL;
   DString otherFundType;

   if (getFundMaster (fundCode, BF::HOST, pFundMaster))
   {
      pFundMaster->getField (ifds::OtherFundType, otherFundType, BF::HOST, false);
      otherFundType.upperCase();
   }
   return otherFundType;
}

//*****************************************************************************
DString FundMasterList::fundType (const DString &fundCode)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("fundType"));

   FundMaster *pFundMaster = NULL;
   DString fundType;

   if (getFundMaster (fundCode, BF::HOST, pFundMaster))
   {
      pFundMaster->getField (ifds::FundType, fundType, BF::HOST, false);
      fundType.upperCase();
   }
   return fundType;
}

//*****************************************************************************
DString FundMasterList::getTaxType (const DString &fundCode)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("taxType"));

   FundMaster *pFundMaster = NULL;
   DString taxType;

   if (getFundMaster (fundCode, BF::HOST, pFundMaster))
   {
      pFundMaster->getField (ifds::TaxType, taxType, BF::HOST, false);
      taxType.upperCase();
   }
   return taxType;
}
//*****************************************************************************
DString FundMasterList::fundCategory (const DString &fundCode)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("fundType"));

   FundMaster *pFundMaster = NULL;
   DString fundCategory;

   if (getFundMaster (fundCode, BF::HOST, pFundMaster))
   {
      pFundMaster->getField (ifds::FundCategory, fundCategory, BF::HOST, false);
      fundCategory.upperCase();
   }
   return fundCategory;
}
//******************************************************************************
DString FundMasterList::getPendTrdContractList ( const DString &fundCode )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_( "getPendTrdContractList" ));
   DString dstrPendTrdContrTransList = NULL_STRING;
   
   FundMaster *pFundMaster = NULL;   
   if (getFundMaster (fundCode, BF::HOST, pFundMaster))
   {
      if( pFundMaster )
      {
         pFundMaster->getField (ifds::PendTrdContrTransList, dstrPendTrdContrTransList, BF::HOST, false);
      }
   }
   return dstrPendTrdContrTransList;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/fundmasterlist.cpp-arc  $
 * 
 *    Rev 1.38   Mar 05 2012 11:50:36   dchatcha
 * P0186484 FN05 - SEG Trade Processing.
 * 
 *    Rev 1.37   Jan 20 2012 15:41:20   wp040027
 * P0188394_Performance Fees - Order Entry
 * 
 *    Rev 1.36   Dec 14 2011 15:44:58   jankovii
 * P0186477 FN03- GIA Maturity/Cash Sweep Instructions
 * 
 *    Rev 1.35   Oct 19 2011 22:22:00   popescu
 * P0186477/03 - GIA Trading Money In - prep work
 * 
 *    Rev 1.34   24 Jul 2008 12:00:56   popescu
 * Incident - 1190617 - set all the data init calls to be asynch
 * 
 *    Rev 1.33   Sep 16 2007 15:39:14   jankovii
 * IN #990336 - User is unable to process manual/adhoc MFR trades.
 * 
 *    Rev 1.32   Feb 24 2005 19:07:00   popescu
 * Incident# 243353, added boolean to flag if list has been fully loaded
 * 
 *    Rev 1.31   Dec 10 2004 14:35:54   hernando
 * PET1117 - Recovered version feature.
 * 
 *    Rev 1.30   Nov 24 2004 10:18:34   yingbaol
 * PET1117:temperary take out version features
 * 
 *    Rev 1.29   Nov 17 2004 16:15:06   popescu
 * PET 1117/06, Trade processing fees
 * 
 *    Rev 1.28   Nov 17 2004 15:20:08   popescu
 * PET 1117/56, removed 'getField' method at the fund master list level, added handy methods to determine if a fund is PUEV/Investro capabele, and getters for fund names
 * 
 *    Rev 1.27   Nov 14 2004 14:42:48   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.26   Nov 04 2004 17:37:44   popescu
 * PET 1117/06, Trade processing
 * 
 *    Rev 1.25   Aug 30 2004 14:52:58   YINGBAOL
 * PTS10032768: speed up list  for non updateable CBO.
 * 
 *    Rev 1.24   May 19 2004 14:24:30   popescu
 * PET 985, FN 01, added convenient methods to check for fund category and type
 * 
 *    Rev 1.23   May 11 2004 15:49:24   popescu
 * PET 985, FN 01, LSIF Trade Entry, added handy methods to fund master list, to check whether a fund is LSIF/Money Market, GIC
 * 
 *    Rev 1.22   Apr 14 2004 14:55:56   VADEANUM
 * PTS 10029064/10028846 - Cash Date.
 * 
 *    Rev 1.21   Oct 14 2003 17:12:00   HSUCHIN
 * PTS 10022556 - added new method isMPSFund and additional logic to isGICFund.
 * 
 *    Rev 1.20   Mar 21 2003 18:12:00   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.19   Oct 09 2002 23:54:34   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.18   Aug 29 2002 12:55:56   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.17   22 May 2002 18:28:44   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.16   20 Feb 2002 17:56:10   WINNIE
 * add getfundmaster object method
 * 
 *    Rev 1.15   03 May 2001 14:06:36   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.14   09 Feb 2001 14:56:12   SMITHDAV
 * Do Async Requests...
 * 
 *    Rev 1.13   Jan 18 2001 16:04:52   YINGBAOL
 * add eTracker
 * 
 *    Rev 1.12   Jan 10 2001 18:01:58   WINNIE
 * add isGICFund method
 * 
 *    Rev 1.11   Dec 17 2000 20:23:28   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.10   Nov 22 2000 10:28:46   JANKAREN
 * Add isCashDateUpdatable method
 * 
 *    Rev 1.9   Nov 20 2000 15:48:28   VASILEAD
 * Changed to return all funds not only the first 25
 * 
 *    Rev 1.8   Nov 07 2000 17:34:40   OLTEANCR
 * bug fix
 * 
 *    Rev 1.7   Nov 02 2000 10:25:52   OLTEANCR
 * new data brokering
 * 
 *    Rev 1.6   Sep 11 2000 10:43:28   YINGBAOL
 * add IsFundExist and IsFundValidAtDate method
 * 
 *    Rev 1.5   Aug 15 2000 10:13:44   WINNIE
 * Add Getfield method
 * 
 *    Rev 1.4   Aug 03 2000 16:41:22   BUZILA
 * locale stuff
 * 
 *    Rev 1.3   Apr 20 2000 16:38:44   BUZILA
 * changed to MgmtCoId
 * 
 *    Rev 1.2   Apr 13 2000 11:42:02   YINGBAOL
 * added isFundMoneyMarket
 * 
 *    Rev 1.1   Mar 10 2000 11:30:10   YINGZ
 * remove stripLeading('0') from key
 * 
 *    Rev 1.0   Feb 15 2000 11:00:00   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.7   Jan 05 2000 20:10:48   BUZILA
 * adding list flag
 * 
 *    Rev 1.6   Dec 12 1999 16:25:24   POPESCUS
 * Xchgdata issue; create and delete the object in the CBO
// 
*/