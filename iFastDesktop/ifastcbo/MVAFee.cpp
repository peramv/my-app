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
// ^FILE   : MVAFee.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : November 2004
//
// ^CLASS    : MVAFee
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "mvafee.hpp"

#include "lsifcodeslist.hpp"
#include "mgmtco.hpp"
#include "funddetail.hpp"
#include "fundmasterlist.hpp"
#include "supportedproductslist.hpp"
#include "trade.hpp"
#include "transfeelist.hpp"
#include "giinvestmentdetailslist.hpp"

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME  = I_("MVAFee");
}

namespace ifds
{
//mgmtco fields
   extern CLASS_IMPORT const BFTextFieldId DSCOverride;
//fees fields
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFIntegerFieldId TransFeeCode;
   extern CLASS_IMPORT const BFDecimalFieldId MaxFee;
   extern CLASS_IMPORT const BFDecimalFieldId MinFee;
//fund fields
   extern CLASS_IMPORT const BFTextFieldId OverrideDSCAllow;
   extern CLASS_IMPORT const BFTextFieldId FeeCharge;
   extern CLASS_IMPORT const BFTextFieldId SuppressMVA;
   extern CLASS_IMPORT const BFTextFieldId DeathRedCode;
}

namespace CND
{  // Conditions used
}

namespace FEES
{
   extern const I_CHAR * MVA;
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const REDEMPTION;
   extern CLASS_IMPORT I_CHAR * const ROLLOVER;
   extern CLASS_IMPORT I_CHAR * const TRANSFER;
}

//******************************************************************************
MVAFee::MVAFee (BFAbstractCBO &parent, const DString &feeCode) : TransFeeCharge (parent, feeCode)
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);
}

//******************************************************************************
MVAFee::MVAFee (BFAbstractCBO &parent) : TransFeeCharge (parent, FEES::MVA)
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);
}

//******************************************************************************
MVAFee::~MVAFee()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
SEVERITY MVAFee::restore ( BFCBO &rpParent, 
                           const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("restore"));
   DString chargeFee = I_("Y");

   setFieldNoValidate ( ifds::FeeCharge, chargeFee, idDataGroup, false, 
                        false, true, false
                        );
   setFieldNoValidate ( ifds::FeeRate, charge2Rate (chargeFee), idDataGroup, false, 
                        false, true, false
                     );
   setFieldNoValidate ( ifds::OrigFeeRate, charge2Rate (chargeFee), idDataGroup, false, 
                        false, true, false
                         );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool MVAFee::isSystemApplicable (const BFDataGroupId &idDataGroup)
{
   return true;
}

//******************************************************************************
bool MVAFee::isContextApplicable (const BFDataGroupId &idDataGroup)
{
   if (TransFee::isContextApplicable(idDataGroup))
   {
	   DString fundCode;
	   DString classCode;

	   getContext().getField (ifds::FromFund,    fundCode, idDataGroup);
	   getContext().getField (ifds::FromClass,   classCode, idDataGroup);

	   DString dstrRedCode;
	   getContext().getField (ifds::RedCode, dstrRedCode, idDataGroup);
	   dstrRedCode.stripAll();
	   dstrRedCode += I_(",");

	   DString dstrDeathRedCodes;
	   getWorkSession().getOption ( ifds::DeathRedCode, dstrDeathRedCodes, BF::HOST, false);
	   dstrDeathRedCodes.stripAll();
	   dstrDeathRedCodes += I_(",");

	   return hasFeeParams(fundCode, classCode, idDataGroup) && 
		      isApplicableForFund (idDataGroup) && dstrDeathRedCodes.find(dstrRedCode) == DString::npos;
	   //return hasFeeParams(fundCode, classCode, idDataGroup) && 
	   //   isApplicableForFund (idDataGroup);
   }
   return false;
}

//******************************************************************************
bool MVAFee::hasContextChanged (const BFDataGroupId &idDataGroup)
{
//fee needs to be refreshed if any of these parameters change
   return hasFieldContextChanged (ifds::LSIFCode, idDataGroup) ||
          hasFieldContextChanged (ifds::FromFund, idDataGroup) ||
          hasFieldContextChanged (ifds::FromClass, idDataGroup) ||
          hasFieldContextChanged (ifds::Amount, idDataGroup);
}

//******************************************************************************
bool MVAFee::isApplicableForFund (const BFDataGroupId &idDataGroup)
{
   bool bIsApplicable = false;

   DString fundCode;
   FundMasterList *pFundMasterList = NULL;
   FundMaster *pFundMaster = NULL;
   
   getContext().getField (ifds::FromFund, fundCode, idDataGroup);
   
   if ( !fundCode.empty() && 
         getWorkSession().getMgmtCo().getFundMasterList(pFundMasterList) &&
         pFundMasterList &&
         pFundMasterList->getFundMaster(fundCode, idDataGroup, pFundMaster) &&
         pFundMaster)
   {
      bIsApplicable = pFundMasterList->isGIAFund (fundCode);
   }
   return bIsApplicable;
}

//******************************************************************************
SEVERITY MVAFee::setFeeDefault (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("setFeeDefaults"));
   DString chargeFee = I_("Y");
   DString tradeFeeOption = I_("0");
   
   DString transType;
   getContext().getField(ifds::TransType, transType, idDataGroup, false);
   if(transType == TRADETYPE::TRANSFER)
   {
      chargeFee = I_("N");
      tradeFeeOption = I_("3");

      setFieldReadOnly(ifds::FeeCharge, idDataGroup, true);
      setFieldReadOnly(ifds::TradeFeeOption, idDataGroup, true);
   }

   setFieldNoValidate ( ifds::TradeFeeOption, tradeFeeOption, idDataGroup, false, false, true, false);
   setFieldNoValidate ( ifds::FeeCharge, chargeFee, idDataGroup, false, false, true, false);
   setFieldNoValidate ( ifds::FeeRate, charge2Rate (chargeFee), idDataGroup, false, false, true, false);
   setFieldNoValidate ( ifds::OrigFeeRate, charge2Rate (chargeFee), idDataGroup, false, false, true, false);

   return GETCURRENTHIGHESTSEVERITY();
}

SEVERITY MVAFee::init (const BFDataGroupId &idDataGroup, bool bDelayInit /*= false*/ )
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));
   
   TransFee::init(idDataGroup, bDelayInit);
   //DString transType;
   //getContext().getField(ifds::TransType, transType, idDataGroup, false);
   //
   //if(transType == TRADETYPE::TRANSFER)
   //{
   //   setFieldReadOnly(ifds::FeeCharge, idDataGroup, true);
   //   setField(ifds::FeeCharge, I_("N"), idDataGroup, false);
   //   setFieldReadOnly(ifds::TradeFeeOption, idDataGroup, true);
   //   setField(ifds::TradeFeeOption, I_("2"), idDataGroup, false);
   //}

   return GETCURRENTHIGHESTSEVERITY();

}

SEVERITY MVAFee::doApplyRelatedChanges ( const BFFieldId &idField, const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges"));

   TransFeeCharge::doApplyRelatedChanges (idField, idDataGroup);

   if (idField == ifds::TradeFeeOption)
   {
      DString transType;
      getContext().getField(ifds::TransType, transType, idDataGroup, false);
      if(transType == TRADETYPE::TRANSFER)
      {
         setFieldReadOnly (ifds::FeeCharge, idDataGroup, true);
      }
   }
   
   if (idField == ifds::TradeFeeOption ||
       idField == ifds::FeeRate)
   {
      TransFeeList* pTransFeeList = (TransFeeList*)getParent();
      if(pTransFeeList)
      {
         Trade* pTrade = (Trade*)(pTransFeeList->getParent());
         if(pTrade)
         {
            GIInvestmentDetailsList* pGIInvestmentDetailsList = NULL;
            if(pTrade->getGIInvestmentDetails (pGIInvestmentDetailsList, idDataGroup, false) <= WARNING &&
               pGIInvestmentDetailsList)
            {
               DString dstrFeeCharge;
               getField(ifds::FeeCharge, dstrFeeCharge, idDataGroup);
               DString dstrSuppressFee = dstrFeeCharge == I_("N") ? I_("Y") : I_("N");
               pGIInvestmentDetailsList->setField(ifds::SuppressMVA, dstrSuppressFee, idDataGroup, false);
               pGIInvestmentDetailsList->recalculateAll(idDataGroup);
            };
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY();

}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/MVAFee.cpp-arc  $
// 
//    Rev 1.5   May 16 2012 11:19:46   if991250
// IN2951488 - GI Money out
// 
//    Rev 1.4   Apr 26 2012 15:48:50   if991250
// Money out refresh fees on supress changes
// 
//    Rev 1.3   Apr 25 2012 18:12:00   if991250
// Money Out - sending SuppressMVA and Suppress Admin fee for investment inquiry and pending trade
// 
//    Rev 1.2   Mar 14 2012 13:15:40   if991250
// IN 2879297: Money Out
// 
//    Rev 1.1   Mar 13 2012 17:38:12   if991250
// IN 2879297: Money Out
// 
//    Rev 1.0   Mar 08 2012 15:09:08   if991250
// Initial revision.
// 
// 
 */