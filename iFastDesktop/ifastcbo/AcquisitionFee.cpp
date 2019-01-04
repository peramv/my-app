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
// ^FILE   : AcquisitionFee.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : November 2004
//
// ^CLASS    : AcquisitionFee
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "acquisitionfee.hpp"

#include "acqfeeinquiry.hpp"
#include "funddetail.hpp"
#include "fundtolist.hpp"
#include "fundmaster.hpp"
#include "fundmasterlist.hpp"
#include "mgmtco.hpp"
#include "mfaccount.hpp"
#include "pendingtradedetails.hpp"
#include "trade.hpp"
#include "tradeacctalloc.hpp"
#include "tradeacctalloclist.hpp"
#include "tradefundalloc.hpp"
#include "tradefundalloclist.hpp"
#include "splitcommission.hpp"
#include "splitcommissionlist.hpp"
#include "transfeelist.hpp"

#include <ifastdataimpl\dse_dstc0121_vw.hpp>

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME		= I_("AcquisitionFee");
   const I_CHAR *  FEES_NOT_ALLOWED	= I_("0,2,3");
   const I_CHAR *  FLAT				= I_("0");
   const I_CHAR *  PERCENT			= I_("1");
}

namespace ifds
{
//management co options
   extern CLASS_IMPORT const BFTextFieldId DisableFee4Alloc;
   extern CLASS_IMPORT const BFTextFieldId AcqFeeDefault;
   extern CLASS_IMPORT const BFTextFieldId DefltFeeOption;
//fee fields
   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFIntegerFieldId TransFeeCode;
   extern CLASS_IMPORT const BFDecimalFieldId Rate;
//account fields
   extern CLASS_IMPORT const BFTextFieldId TaxType;
   extern CLASS_IMPORT const BFTextFieldId BrokerCode;
//fund fields
   extern CLASS_IMPORT const BFTextFieldId Currency;
   extern CLASS_IMPORT const BFTextFieldId LoadType;
   extern CLASS_IMPORT const BFTextFieldId ExchInFeeExist;
}

namespace CND
{  // Conditions used
   extern const long ERR_FEE_DIFFER_FROM_DEFAULT;
   extern const long ERR_FEE_TYPE_FLAT_FOR_BEARER_CERTIFICATE;
   extern const long ERR_FEE_RATE_ABOVE_MAX;
   extern const long ERR_FEE_RATE_UNDER_MINIMUM;
   extern const long ERR_FEETYPE_NOT_SUPPORTED;
   extern const long WARN_FEETYPE_NOT_SUPPORTED;
}

namespace FEES
{
   extern const I_CHAR * ACQUISITION;
   extern const I_CHAR * EXCHANGE;
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const REDEMPTION_LIKE;
   extern CLASS_IMPORT I_CHAR * const PURCHASE_LIKE;
   extern CLASS_IMPORT I_CHAR * const EXCHANGE_LIKE;
   extern CLASS_IMPORT I_CHAR * const ROLLOVER;
   extern CLASS_IMPORT I_CHAR * const TRANSFER;
   extern CLASS_IMPORT I_CHAR * const EXCHANGE;
   extern CLASS_IMPORT I_CHAR * const REDEMPTION;
   extern CLASS_IMPORT I_CHAR * const PURCHASE;
   extern CLASS_IMPORT I_CHAR * const INTER_CLASS_SWITCH;
}

//******************************************************************************
AcquisitionFee::AcquisitionFee (BFAbstractCBO &parent) : TransFeeRate (parent, FEES::ACQUISITION),
_acqFeeDefault (NULL_STRING)
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);
   getWorkSession ().getOption ( ifds::AcqFeeDefault,                               
                                 _acqFeeDefault, 
                                 BF::HOST,
                                 false);         
}

//******************************************************************************
AcquisitionFee::AcquisitionFee ( BFAbstractCBO &parent, 
                                 const DString &feeCode) : TransFeeRate (parent, feeCode),
_acqFeeDefault (NULL_STRING)
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);
   getWorkSession ().getOption ( ifds::AcqFeeDefault,                               
                                 _acqFeeDefault, 
                                 BF::HOST,
                                 false);         
}

//******************************************************************************
AcquisitionFee::~AcquisitionFee()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
SEVERITY AcquisitionFee::restore ( BFCBO &rpParent, 
                                   const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("restore"));
   DString feeRate,
      flatPercent;

   rpParent.getField (ifds::Fee, feeRate, idDataGroup);
   getFormattedFee (idDataGroup, feeRate);
   rpParent.getField (ifds::FlatPercent, flatPercent, idDataGroup);
   setFieldNoValidate ( ifds::FeeRate, feeRate, idDataGroup, false, 
                        false, false, false);
   if (flatPercent == Y) //flat
   {
      setFieldNoValidate ( ifds::FeeType, I_("0"), idDataGroup, false, 
                           false, false, false);
   }
   else if (flatPercent == N) //percent
   {
      setFieldNoValidate ( ifds::FeeType, I_("1"), idDataGroup, false, 
                           false, false, false);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void AcquisitionFee::doInitWithDefaultValues (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doInitWithDefaultValues"));
   if (canBeInitialized (idDataGroup))
   {
      TransFeeRate::doInitWithDefaultValues (idDataGroup);
   }
}

//******************************************************************************
SEVERITY AcquisitionFee::setChargeOption (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("setChargeOption"));
   setFieldNoValidate ( ifds::ChargeOption, I_("0"), idDataGroup, false, 
                        true, true, false);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AcquisitionFee::setFeeProperties (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("setFeeProperties"));

   TransFeeRate::setFeeProperties (idDataGroup);

   bool bReadOnly = false;
   
   DString accountNum;

   getContext().getField (ifds::AccountNum, accountNum, idDataGroup);
   if (!accountNum.empty())
   {
      DString feeModelCode;
      //check if there is a fee model code at shareholder level
      if (getFeeModelCode (accountNum, feeModelCode, idDataGroup) <= WARNING)
      {
         bReadOnly |= !feeModelCode.empty();
      }
      if (bReadOnly)
      {
         setField (ifds::TradeFeeOption, I_("1"), idDataGroup, false); //charge per system calculation
      }
   }
   setFieldReadOnly (ifds::FeeRate, idDataGroup, bReadOnly);
   setFieldReadOnly (ifds::FeeType, idDataGroup, bReadOnly); //|| !SplitCommission::isTypeZERO (getWorkSession()));
   setFieldReadOnly (ifds::TradeFeeOption, idDataGroup, bReadOnly);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AcquisitionFee::doValidateField ( const BFFieldId &idField, 
                                           const DString &strValue, 
                                           const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doValidateField"));
   
   bool bCallBaseValidation = true;

   if (idField == ifds::FeeRate)
   {
      AcqFeeInquiry *pAcqFeeInquiry = NULL;

      // full exchange should also invoke view 121 to get the default
      // full redemption are free format
      if (isTradeAllocated (idDataGroup) || isFullRedemption (idDataGroup)) 
      {
         bCallBaseValidation = isFeeTypePercentage (idDataGroup);
      }
      else if ( getAcqFeeDefault (pAcqFeeInquiry, idDataGroup) <= WARNING &&
                pAcqFeeInquiry)
      {
         DString maxFeeActive;

         pAcqFeeInquiry->getField (ifds::MaxFeeActive, maxFeeActive, idDataGroup, false);
         bCallBaseValidation = maxFeeActive == I_("Y"); //skip validation min/max if 'N'
         if (!isAcqFeeSameAsDefault (idDataGroup))
         {
            ADDCONDITIONFROMFILE (CND::ERR_FEE_DIFFER_FROM_DEFAULT);
         }

         double dFeeRate = DSTCommonFunctions::convertToDouble (strValue);

         if (isFeeTypePercentage (idDataGroup) && dFeeRate >= 0)
         {
            DString maxFee, 
               minFee;

            getField (ifds::MaxFee, maxFee, idDataGroup);
            getField (ifds::MinFee, minFee, idDataGroup);

            double dMaxFee = DSTCommonFunctions::convertToDouble (maxFee);
            double dMinFee = DSTCommonFunctions::convertToDouble (minFee);
            
            if (dFeeRate > dMaxFee)
            {
               bCallBaseValidation = false;
               DString idiStr,
                  feeName;

               getField (ifds::TransFeeCode, feeName, idDataGroup, true);
               addIDITagValue (idiStr, I_ ("name"), feeName);
               addIDITagValue (idiStr, I_ ("max"), DSTCommonFunctions::doubleToDString (ifds::MaxFee, dMaxFee));
               ADDCONDITIONFROMFILEIDI (CND::ERR_FEE_RATE_ABOVE_MAX, idiStr);
            }
            else if (dFeeRate < dMinFee)
            {
               bCallBaseValidation = false;
               DString idiStr,
                  feeName;

               getField (ifds::TransFeeCode, feeName, idDataGroup, true);
               addIDITagValue (idiStr, I_ ("name"), feeName);
               addIDITagValue (idiStr, I_ ("min"), DSTCommonFunctions::doubleToDString (ifds::MinFee, dMinFee));
               ADDCONDITIONFROMFILEIDI (CND::ERR_FEE_RATE_UNDER_MINIMUM, idiStr);
            }
         }
      }
      else
      {
         bCallBaseValidation = false;

         SplitCommissionList *pSplitCommissionList = NULL;
         if ( getSplitCommission (pSplitCommissionList, idDataGroup) <= WARNING &&
              pSplitCommissionList)
         {
            DString maxFee,
               acqFee,
               initialTotalRate;
         
            pSplitCommissionList->getField (ifds::Fee, maxFee, idDataGroup, false);
            pSplitCommissionList->getInitialTotalRate (initialTotalRate, idDataGroup);
            getField (ifds::FeeRate, acqFee, idDataGroup, false);
            double dMaxFee = DSTCommonFunctions::convertToDouble (maxFee),
                     dFee = DSTCommonFunctions::convertToDouble (acqFee),
                     dInitialTotalRate = DSTCommonFunctions::convertToDouble (initialTotalRate);
         
            SplitCommissionList::canFeeBeDiscounted ( pSplitCommissionList,
				                                          getWorkSession (), 
                                                      dFee, 
                                                      dInitialTotalRate,//0.0, 
                                                      dMaxFee, 
                                                      idDataGroup);
         }
         else
         {
            DString transType;

            getContext().getField (ifds::TransType, transType, idDataGroup, false);
            bCallBaseValidation = transType == TRADETYPE::REDEMPTION || isFeeTypePercentage (idDataGroup);
         }
      }
   }
   else if (idField == ifds::FeeType)
   {
	    if (DSTCommonFunctions::codeInList (strValue, FEES_NOT_ALLOWED) && !SplitCommission::isTypeZERO (getWorkSession()))
		{
			getErrMsg (I_("1113"), CND::ERR_FEETYPE_NOT_SUPPORTED, CND::WARN_FEETYPE_NOT_SUPPORTED, idDataGroup);
		}

		SplitCommissionList *pSplitCommissionList = NULL;
        if ( getSplitCommission (pSplitCommissionList, idDataGroup) <= WARNING &&
             pSplitCommissionList)
        {
			pSplitCommissionList->setField (ifds::FeeType, strValue, idDataGroup, false, true);
		}
   }

   if (bCallBaseValidation)
   {
      TransFeeRate::doValidateField (idField, strValue, idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AcquisitionFee::doApplyRelatedChanges ( const BFFieldId &idField, 
                                                 const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doApplyRelatedChanges"));
   if (TransFeeRate::doApplyRelatedChanges (idField, idDataGroup) <= WARNING)
   {
      if (idField == ifds::TradeFeeOption)
      {
          if (!SplitCommission::isTypeZERO (getWorkSession()))
          {
            //always read only
            //setFieldReadOnly (ifds::FeeType, idDataGroup, true);
          }
      }
	  else if (idField == ifds::FeeType)
      {
         if (!SplitCommission::isTypeZERO (getWorkSession()))
         {
             DString feeType;
			 getField (ifds::FeeType, feeType, idDataGroup);

			 if (feeType == FLAT) // flat
			 {
			    bool bReadOnly = false;
				setFieldNoValidate (ifds::FeeRate, I_("0"), idDataGroup, false, false, true, false);
			    
				SplitCommissionList *pSplitCommissionList = NULL;

				if (getSplitCommission (pSplitCommissionList, idDataGroup) <= WARNING &&
                    pSplitCommissionList)
				{
					pSplitCommissionList->initDefaultFlatFeeData (idDataGroup);
					bReadOnly = true;
				}

	            setFieldReadOnly (ifds::FeeRate, idDataGroup, bReadOnly);
			}
			else if (feeType == PERCENT)
			{
	            setFieldReadOnly (ifds::FeeRate, idDataGroup, false);

				SplitCommissionList *pSplitCommissionList;
				getSplitCommission (pSplitCommissionList, idDataGroup, true, true); // get defaults

				 //notify the trans fee list of the change
				TransFeeList *pTransFeeList = dynamic_cast <TransFeeList*> (getParent());
   
				if (pTransFeeList)
				{
					pTransFeeList->onNotify (FIELD_NOTIFICATIONS, E_EVENT_VALUE_CHANGE, I_("ForceRefresh"));
				}
			}
		 }
	  }
      else if (idField == ifds::FeeRate)
      {
         propagateFeeRateChangeToFundAlloc(idDataGroup, true);
         if (!SplitCommission::isTypeZERO (getWorkSession()))
         {
            DString feeRate;

            getField (ifds::FeeRate, feeRate, idDataGroup, false);
//set the total rate to the split comm list
            SplitCommissionList *pSplitCommissionList = NULL;
      
            if ( getSplitCommission (pSplitCommissionList, idDataGroup) <= WARNING &&
                 pSplitCommissionList)
            {

               DString dstrSFACRate (NULL_STRING);
               bool baseCommApplicable (false);
               assert (getParent() && getParent()->getParent());
//               Trade *pTrade = dynamic_cast <Trade*> (getParent()->getParent());

               TradeFundAlloc *pTradeFundAlloc = NULL;
               if(getFirstFELTradeFundAlloc(pTradeFundAlloc, idDataGroup) <= WARNING 
                  && pTradeFundAlloc 
                  && pTradeFundAlloc->isBaseCommissionApplicableAndGetSFACRate (baseCommApplicable, dstrSFACRate, idDataGroup)  <= WARNING 
                  && baseCommApplicable)
               {
                  DString baseCommission = SplitCommissionList::calculateBaseCommission (feeRate, dstrSFACRate);

                  if (!baseCommission.empty())
                  {
                     feeRate = baseCommission;
                  }
               }

               DString totalRate;

               pSplitCommissionList->getSplitTotalRate (totalRate, idDataGroup);
               double dblTotalRate = DSTCommonFunctions::convertToDouble (totalRate);
               double dblFeeRate = DSTCommonFunctions::convertToDouble (feeRate);
               if (dblTotalRate != dblFeeRate)
               {
                  pSplitCommissionList->setField ( ifds::Rate, 
                                                   feeRate, 
                                                   idDataGroup, 
                                                   false, 
                                                   true);
               }
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool AcquisitionFee::propagateFeeRateChangeToFundAlloc(const BFDataGroupId &idDataGroup, bool bApplyToSplitComm)
{
   bool retVal = false;
   Trade *pTrade = dynamic_cast <Trade*> (getParent()->getParent());
   TradeAcctAllocList*  pAccountAllocationList = NULL;
   TradeAcctAlloc*      pAccountAllocation = NULL;
   TradeFundAllocList*  pFundAllocationList = NULL;
   TradeFundAlloc*      pFundAllocation = NULL;

   if(pTrade)
   pTrade->getAccountAllocationList(pAccountAllocationList, idDataGroup, false);
   if (pAccountAllocationList)
   {
      BFObjIter iterAccountAllocList(*pAccountAllocationList, idDataGroup);
      
      while (!iterAccountAllocList.end())
      {
         pAccountAllocation = dynamic_cast<TradeAcctAlloc*>(iterAccountAllocList.getObject());
         pAccountAllocation->getFundAllocationList(pFundAllocationList, idDataGroup, false); 
         if(pFundAllocationList)
         {
            BFObjIter iterFundAllocList(*pFundAllocationList, idDataGroup);
            while(!iterFundAllocList.end ())
            {
               pFundAllocation = dynamic_cast<TradeFundAlloc*>(iterFundAllocList.getObject());
               if(pFundAllocation && pFundAllocation->hasPurchExchgFrontEndLoadCommission(idDataGroup))
               {
                  DString dstrFeeRate;
                  getField(ifds::FeeRate, dstrFeeRate, idDataGroup, false);
                  if(!bApplyToSplitComm)
                     pFundAllocation->setFeeRate(dstrFeeRate, idDataGroup);
                  else
                     pFundAllocation->setField(ifds::FeeRate, dstrFeeRate, idDataGroup, true, false, false);

                  retVal = true;
               }
               ++iterFundAllocList;
            }
         }
         ++iterAccountAllocList;
      }
   }
   return retVal;
};

//******************************************************************************
bool AcquisitionFee::hasContextChanged (const BFDataGroupId &idDataGroup)
{
//fee needs to be refreshed if any of the 121 request parameters changed
   bool retVal = false;
   retVal = hasFieldContextChanged (ifds::FromFund, idDataGroup) ||
          hasFieldContextChanged (ifds::FromClass, idDataGroup) ||
          hasFieldContextChanged (ifds::ToFund, idDataGroup) ||
          hasFieldContextChanged (ifds::ToClass, idDataGroup) ||
          hasFieldContextChanged (ifds::Amount, idDataGroup) ||
          hasFieldContextChanged (ifds::AmtType, idDataGroup) ||
          hasFieldContextChanged (ifds::EffectiveDate, idDataGroup) ||
          hasFieldContextChanged (ifds::SettleCurrency, idDataGroup) ||
          hasFieldContextChanged (ifds::AccountTo, idDataGroup) ||
          hasFieldContextChanged (ifds::Broker, idDataGroup) ||
          hasFieldContextChanged (ifds::ExchRate, idDataGroup) ||
         (hasFieldContextChanged (ifds::Branch, idDataGroup) && !SplitCommission::isTypeZERO (getWorkSession())) ||
         (hasFieldContextChanged (ifds::SlsrepCode, idDataGroup) && !SplitCommission::isTypeZERO (getWorkSession())) ||
         hasFieldContextChanged (ifds::AcqFeeOption, idDataGroup) ||
         hasFieldContextChanged (ifds::ROAAmount, idDataGroup) ||
		 hasFieldContextChanged (ifds::TradeInDate, idDataGroup) ;

      if(!retVal)
      {
         TransFeeList *pTransFeeList = dynamic_cast <TransFeeList*> (getParent());
         if(pTransFeeList && pTransFeeList->getForcingRefresh())
         {
            retVal = true;
         }
      }
       
   return retVal;
}

//******************************************************************************
bool AcquisitionFee::isSystemApplicable (const BFDataGroupId &idDataGroup)
{
   return true;
}

//******************************************************************************
bool AcquisitionFee::isContextApplicable (const BFDataGroupId &idDataGroup)
{
   if (TransFee::isContextApplicable(idDataGroup))
   {
	   DString transType,
		   feeCode;

	   getField (ifds::TransFeeCode, feeCode, idDataGroup, false);
	   getContext().getField (ifds::TransType, transType, idDataGroup, false);
	   return ( (//!isTradeAllocated (idDataGroup) && //enable acq fee at trade level (disable updating it at allocation level.) 
				 feeCode == FEES::ACQUISITION && 
				 (DSTCommonFunctions::codeInList (transType, TRADETYPE::PURCHASE_LIKE) ||
				 transType == TRADETYPE::ROLLOVER)) ||
				 (feeCode == FEES::EXCHANGE &&
				 DSTCommonFunctions::codeInList (transType, TRADETYPE::EXCHANGE_LIKE) && 
				 SplitCommission::isTypeZERO (getWorkSession ()))) &&
				 !isFeeWaivedForAccount (idDataGroup) &&
				 isApplicableForFund (idDataGroup) &&
				 isApplicableForAmount (idDataGroup) &&
				 isApplicableForAcqFeeOption (idDataGroup);
   }
   return false;
}

//******************************************************************************
SEVERITY AcquisitionFee::setFeeType (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("setFeeType"));
//find out the type first
   AcqFeeInquiry *pAcqFeeInquiry = NULL;
   DString acqFeeType (I_("1"));

   if (isTradeAllocated (idDataGroup)) //  full exchange should also get invoke view 121
   {
      ; //percent
   }
   else if ( getAcqFeeDefault (pAcqFeeInquiry, idDataGroup) <= WARNING &&
             pAcqFeeInquiry)
   {
      pAcqFeeInquiry->getField (ifds::AcqFeeType, acqFeeType, idDataGroup);
      if (acqFeeType.empty() || isFullExchange (idDataGroup))
      {
         acqFeeType = I_("1"); //percent
      }
   }
   else if (!SplitCommission::isTypeZERO (getWorkSession()))
   {
      ;//percent
   }
   setFieldNoValidate (ifds::FeeType, acqFeeType, idDataGroup, false, false, true, false);
   setFieldNoValidate (ifds::OrigFeeType, acqFeeType, idDataGroup, false, false, true, false);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AcquisitionFee::setFeeDefault (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("setFeeDefault"));
   AcqFeeInquiry *pAcqFeeInquiry = NULL;
   DString acqFee (I_("0")),
      acqFeeOption,
      transType;

   getContext ().getField (ifds::AcqFeeOption, acqFeeOption, idDataGroup, false);
   getContext().getField (ifds::TransType, transType, idDataGroup);
   if (acqFeeOption != I_("2") || transType == TRADETYPE::REDEMPTION) //buy at nav or redemption
   {
      bool limitedByTaxTypeMaxFee = false;
      if ( //isTradeAllocated (idDataGroup) || 
           isFullExchange (idDataGroup) ||
           isExchangeForNotNewMoney (idDataGroup) ||
           isFullRedemption (idDataGroup))
      {
         acqFee = I_("0");
      }
      else if ( getAcqFeeDefault (pAcqFeeInquiry, idDataGroup) <= WARNING &&
                pAcqFeeInquiry)
      {
         if (_acqFeeDefault == Y)
         {
            pAcqFeeInquiry->getField (ifds::AcqFee, acqFee, idDataGroup);
         }
      }
      else //split comm environment
      {
         SplitCommissionList *pSplitCommissionList = NULL;

         if ( getSplitCommission (pSplitCommissionList, idDataGroup) <= WARNING &&
              pSplitCommissionList)
         {
            if (_acqFeeDefault == Y || SplitCommission::isTypeONE (getWorkSession()))
            {
               DString dstrSFACRate (NULL_STRING);
               bool baseCommApplicable (false);
               assert (getParent() && getParent()->getParent());
               Trade *pTrade = dynamic_cast <Trade*> (getParent()->getParent());

               TradeFundAlloc *pTradeFundAlloc = NULL;
               if(getFirstFELTradeFundAlloc(pTradeFundAlloc, idDataGroup) <= WARNING 
                  && pTradeFundAlloc 
                  && pTradeFundAlloc->isBaseCommissionApplicableAndGetSFACRate (baseCommApplicable, dstrSFACRate, idDataGroup)  <= WARNING 
                  && baseCommApplicable)
               {
                  pSplitCommissionList->getField (ifds::Fee, acqFee, idDataGroup, false);
               }
               else
               {
                  pSplitCommissionList->getSplitTotalRate (acqFee, idDataGroup);

                  DString dstrTaxTypeMaxFee = pSplitCommissionList->getTaxTypeMaxFee(idDataGroup);
                  if( !dstrTaxTypeMaxFee.empty() )
                  {
                     BigDecimal bdTotalRate(acqFee);
                     BigDecimal bdTaxTypeMaxFee(dstrTaxTypeMaxFee);

                     if( bdTaxTypeMaxFee < bdTotalRate)
                     {
                        acqFee = dstrTaxTypeMaxFee;
                        pSplitCommissionList->propagateTotalRate(acqFee,idDataGroup);	
                        limitedByTaxTypeMaxFee = true;
                     }
                  }
               }
            }
         }
      }
      getFormattedFee (idDataGroup, acqFee);
      setFieldNoValidate (ifds::FeeRate, acqFee, idDataGroup, true, false, true, !limitedByTaxTypeMaxFee); 
      setFieldNoValidate (ifds::OrigFeeRate, acqFee, idDataGroup, true, false, true, false);

//purchase allocated trades should look at the below GC...
      if ( isTradeAllocated (idDataGroup) && 
           transType == TRADETYPE::PURCHASE)
      {
		   DString disableFee4Alloc,
		      defaultFeeOption;

		   getWorkSession ().getOption (ifds::DisableFee4Alloc, disableFee4Alloc, idDataGroup, true);
		   getWorkSession ().getOption (ifds::DefltFeeOption, defaultFeeOption, idDataGroup, false);
         if (disableFee4Alloc == I_("Y"))
		   {
			   getWorkSession ().getOption (ifds::DefltFeeOption, defaultFeeOption, idDataGroup, false);
            if (!defaultFeeOption.empty())
            {
			      setFieldNoValidate (ifds::TradeFeeOption, defaultFeeOption, idDataGroup, false, true);
            } 
		   }
         else if (defaultFeeOption.strip() == I_("3"))
         {
            setFieldNoValidate (ifds::TradeFeeOption, I_("3"), idDataGroup, false, true);
         }
      }
//set the fee currency      
      if (isTradeAllocated (idDataGroup))
      {
   //get the fund alloc list
         TradeFundAllocList *pTradeFundAllocList = NULL;
         assert (getParent() && getParent()->getParent());
         Trade *pTrade = dynamic_cast <Trade*> (getParent()->getParent());

         if ( pTrade->getFundAllocationList ( pTradeFundAllocList, 
                                              idDataGroup,
                                              false) <= WARNING && 
             pTradeFundAllocList)
         {
            DString allocCurrency;

            pTradeFundAllocList->getAllocCurrency (allocCurrency, idDataGroup);
            setField (ifds::Currency, allocCurrency, idDataGroup, false);
         }
      }
      else
      {
         DString feeCurrency;

         getField (ifds::Currency, feeCurrency, idDataGroup, false);
         if (feeCurrency.empty())
         {
            DString fundCode,
               classCode;

            //find the fund currency
            if ( DSTCommonFunctions::codeInList (transType, TRADETYPE::PURCHASE_LIKE) ||
                 transType == TRADETYPE::REDEMPTION)
            {
               getContext().getField (ifds::FromFund, fundCode, idDataGroup);
               getContext().getField (ifds::FromClass, classCode, idDataGroup);
            }
            else if ( transType == TRADETYPE::ROLLOVER ||
                      DSTCommonFunctions::codeInList (transType, TRADETYPE::EXCHANGE_LIKE))
            {
               getContext().getField (ifds::ToFund, fundCode, idDataGroup);
               getContext().getField (ifds::ToClass, classCode, idDataGroup);
            }
            FundDetail *pFundDetail = NULL; //set the fund currency
            
            if ( !fundCode.empty() &&
                 !classCode.empty() &&
                 getWorkSession().getFundDetail (fundCode, classCode, idDataGroup, pFundDetail) && 
                 pFundDetail)
            {
               DString fundCurrency;

               pFundDetail->getField (ifds::Currency, fundCurrency, idDataGroup, false);
               setField (ifds::Currency, fundCurrency, idDataGroup, false);
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AcquisitionFee::init (const BFData &viewData)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   TransFeeRate::init (viewData);

   //DString dstrFundCode  = viewData.getElementValue (ifds::FundCode); 
   //DString dstrClassCode = viewData.getElementValue (ifds::ClassCode);
   //dstrFundCode.stripAll();
   //dstrClassCode.stripAll();

   Trade *pTrade = dynamic_cast <Trade*> (getParent()->getParent());
   
   if (pTrade) 
   {
      TradeFundAllocList *pFundAllocationList = NULL; 
      if(pTrade->getFundAllocationList (pFundAllocationList, BF::HOST) <= WARNING && pFundAllocationList)
      {
         BFObjIter iter( *pFundAllocationList, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED);
         while(!iter.end())
         {
            TradeFundAlloc* pTradeFundAlloc = dynamic_cast <TradeFundAlloc*>(iter.getObject());
            if(pTradeFundAlloc && pTradeFundAlloc->hasPurchExchgFrontEndLoadCommission(BF::HOST))
            { 
               //DString dstrAllocFundCode;
               //DString dstrAllocClassCode;
               //pTradeFundAlloc->getField(ifds::FundCode, dstrAllocFundCode, BF::HOST, false);
               //pTradeFundAlloc->getField(ifds::ClassCode, dstrAllocClassCode, BF::HOST, false); 
               //dstrAllocFundCode.stripAll();
               //dstrAllocClassCode.stripAll();
               //if(dstrFundCode == dstrAllocFundCode && dstrClassCode == dstrAllocClassCode)
               {
                  DString dstrFeeType = viewData.getElementValue (ifds::FeeType); 
                  dstrFeeType.stripAll();
                  DString dstrFeeRate = viewData.getElementValue (ifds::FeeRate); 
                  dstrFeeRate.stripAll();    
                  pTradeFundAlloc->setField(ifds::FeeType, dstrFeeType, BF::HOST, false);
                  pTradeFundAlloc->setFeeRate(dstrFeeRate, BF::HOST);
                  DString dstrTransFeeRID = viewData.getElementValue (ifds::TransFeeRID); 
                  pTradeFundAlloc->setField(ifds::TransFeeRID, dstrTransFeeRID, BF::HOST, false);
               }
            }
            ++iter;
         }
      }
   }

   //if(pTrade && isTradeAllocated (BF::HOST)) //create the acquisition fee for pending trades
   //{
   //   return SEVERE_ERROR;
   //}

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AcquisitionFee::setFeeMinMax (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("setFeeMinMax "));
   AcqFeeInquiry *pAcqFeeInquiry = NULL;
   DString maxFee,
      minFee;

   if (isTradeAllocated (idDataGroup))  // || isFullExchange (idDataGroup))
   {
      if (isFeeTypePercentage (idDataGroup))
      {
         maxFee = I_("100");
         minFee = I_("0");
      }
   }
   else if ( getAcqFeeDefault (pAcqFeeInquiry, idDataGroup) <= WARNING &&
             pAcqFeeInquiry)
   {
//find the min max from 121
      if (isFeeTypePercentage (idDataGroup))
      {
         pAcqFeeInquiry->getField (ifds::MaxPercent, maxFee, idDataGroup, false);
         pAcqFeeInquiry->getField (ifds::MinPercent, minFee, idDataGroup, false);
      }
      else 
      {
         pAcqFeeInquiry->getField (ifds::MaxFlatFundCurr, maxFee, idDataGroup, false);
         pAcqFeeInquiry->getField (ifds::MinFee, minFee, idDataGroup, false);
      }
   }
   setField (ifds::MinFee, minFee, idDataGroup, false);
   setField (ifds::MaxFee, maxFee, idDataGroup, false);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool AcquisitionFee::isApplicableForFund (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("isApplicableForFund"));
   bool bIsApplicable = false;
   
   DString transType,
      fundCode,
      classCode;

   getContext().getField (ifds::TransType, transType, idDataGroup);

   if ( (DSTCommonFunctions::codeInList (transType, TRADETYPE::PURCHASE_LIKE) ||
         DSTCommonFunctions::codeInList (transType, TRADETYPE::EXCHANGE_LIKE)) &&
        isTradeAllocated (idDataGroup))
   {
      DString disableFee4Alloc;

      getWorkSession ().getOption ( ifds::DisableFee4Alloc, 
                                    disableFee4Alloc, 
                                    BF::HOST,
                                    true);
      bIsApplicable = disableFee4Alloc == I_("N");
   }
   else if ( DSTCommonFunctions::codeInList (transType, TRADETYPE::PURCHASE_LIKE) ||
             transType == TRADETYPE::ROLLOVER)
   {
      if (DSTCommonFunctions::codeInList (transType, TRADETYPE::PURCHASE_LIKE))
      {
         getContext().getField (ifds::FromFund, fundCode, idDataGroup);
         getContext().getField (ifds::FromClass, classCode, idDataGroup);
      }
      else if (transType == TRADETYPE::ROLLOVER)
      {
         getContext().getField (ifds::ToFund, fundCode, idDataGroup);
         getContext().getField (ifds::ToClass, classCode, idDataGroup);
      }

      FundDetail *pFundDetail = NULL;

      if ( !fundCode.empty() &&
           !classCode.empty() &&
           getWorkSession().
               getFundDetail (fundCode, classCode, idDataGroup, pFundDetail) && 
           pFundDetail)
      {
         DString loadType;

         pFundDetail->getField (ifds::LoadType, loadType, idDataGroup, false);
         bIsApplicable = loadType == I_("FEL");
      }
   }
   else if (DSTCommonFunctions::codeInList (transType, TRADETYPE::EXCHANGE_LIKE))
   {
//retrieve the fund fields again
      DString fromFund, 
         fromClass, 
         toFund, 
         toClass;

      getContext().getField (ifds::FromFund, fromFund, idDataGroup);
      getContext().getField (ifds::FromClass, fromClass, idDataGroup);
      getContext().getField (ifds::ToFund, toFund, idDataGroup);   
      getContext().getField (ifds::ToClass, toClass, idDataGroup);
      FundDetail *pToFundDetail = NULL,
         *pFromFundDetail = NULL;

      if ( !toFund.empty() && 
           !toClass.empty() &&
            getWorkSession().
               getFundDetail (toFund, toClass, idDataGroup, pToFundDetail) && 
            pToFundDetail &&
           !fromFund.empty() &&
           !fromClass.empty() &&
            getWorkSession().
               getFundDetail (fromFund, fromClass, idDataGroup, pFromFundDetail) && 
            pFromFundDetail)
      {
         DString exchInFeeExist;
            
         pToFundDetail->getField (ifds::ExchInFeeExist, exchInFeeExist, idDataGroup);
         exchInFeeExist.strip().upperCase();
         
         if ((transType == TRADETYPE::EXCHANGE || transType == TRADETYPE::INTER_CLASS_SWITCH) && exchInFeeExist == Y)
         {
            bIsApplicable = false;
         }
         else 
         {
            bIsApplicable = true;
			 
            DString toLoadType,
               fromLoadType;

            pToFundDetail->getField (ifds::LoadType, toLoadType, idDataGroup, false);
            pFromFundDetail->getField (ifds::LoadType, fromLoadType, idDataGroup, false);
            if (toLoadType == I_("BEL"))
            {
   // default to No
               bIsApplicable = false;
   // if to fund load type is back end load, fee is allowed if one of the follow is true:
   // 1. From Fund and From Class = To fund and To class (within fund exchange fee)
   // 2. From Account is RRSP and To Account is RRIF or PRIF (applies exchange fee)
   // 3. From Fund is also back end load (within class exchange fee)             
               
				
				   bIsApplicable = (fromFund == toFund && fromClass == toClass) || //case 1
                                 fromLoadType == I_("BEL"); //case 3
               if (!bIsApplicable) // case 2
               {
                  DString fromAccount, 
                     toAccount;
               
                  getContext().getField (ifds::AccountNum, fromAccount, idDataGroup);
                  getContext().getField (ifds::AccountTo, toAccount, idDataGroup);
                  MFAccount *pMFAccountFrom = NULL, 
                     *pMFAccountTo = NULL;

                  if ( getWorkSession().getMFAccount ( idDataGroup, 
                                                      fromAccount, 
                                                      pMFAccountFrom) <= WARNING &&
                     pMFAccountFrom &&
                     getWorkSession().getMFAccount ( idDataGroup, 
                                                      toAccount, 
                                                      pMFAccountTo) <= WARNING &&
                     pMFAccountTo)
                  {
                     DString taxTypeFrom, 
                        taxTypeTo;
                  
                     pMFAccountFrom->getField (ifds::TaxType, taxTypeFrom, idDataGroup);
                     pMFAccountTo->getField (ifds::TaxType, taxTypeTo, idDataGroup);
                     bIsApplicable = taxTypeFrom == I_("1") && //RRSP
                                    (taxTypeTo == I_("2") || //RRIF
                                     taxTypeTo == I_("R")); //PRIF
                  }
               }
            }
            else // to load type is not back end load, fee is applicable based on the fund,class and loadtype. Logic will be determine by view 121
            {
               /*FundToList fundToList (*this);
			   
			   // whenever the to fund is not FEL, then Exchange Fee is applicable
			   // it could either be a FEL fee or exchange fee based on the Fund,Class and load type of
			   // both side. Logic all determine by View 121
			
               bool bIsNewMoney = fundToList.isBuySell (fromFund, fromClass, toFund, toClass);
               bIsApplicable = fromLoadType == I_("FEL") && //from side is front end load
                               bIsNewMoney; */
			   
				// Let view 121 to determine the max fee rate and default fee rate based on fund,class, loadtype and buysell flag
				bIsApplicable = true; 
               
            } 
         }
      }
   }
   return bIsApplicable;
}

//******************************************************************************
bool AcquisitionFee::isApplicableForAmount (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("isApplicableAmount"));
   bool bIsApplicable = false;
   DString amount,
      transType;

   getContext().getField (ifds::TransType, transType, idDataGroup);
   getContext().getField (ifds::Amount, amount, idDataGroup, false);
//exchange fee should be applicable even if amount is zero
   if (DSTCommonFunctions::codeInList (transType, TRADETYPE::EXCHANGE_LIKE))
   {
      bIsApplicable = true;
   }
   else
   {
      double dec_amount = DSTCommonFunctions::convertToDouble (amount);
      bIsApplicable = dec_amount != 0;
   }
   return bIsApplicable;
}

//******************************************************************************
bool AcquisitionFee::isApplicableForAcqFeeOption (const BFDataGroupId &idDataGroup)
{
   DString acqFeeOption;
   
   getContext().getField (ifds::AcqFeeOption, acqFeeOption, idDataGroup, false);
   return ( acqFeeOption != I_("2") && acqFeeOption != I_("4") ); //buy at nav
}


//******************************************************************************
SEVERITY AcquisitionFee::getSplitCommission ( SplitCommissionList *&pSplitCommissionList,
                                              const BFDataGroupId &idDataGroup,
											  bool bCreate,
											  bool bGetDefault)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getSplitCommission"));
   assert (getParent() && getParent()->getParent());
   
   TradeFundAlloc *pTradeFundAlloc = NULL;
   if(getFirstFELTradeFundAlloc(pTradeFundAlloc, idDataGroup) <= WARNING && 
      pTradeFundAlloc)
   {                                             
      pTradeFundAlloc->getSplitCommissionList ( pSplitCommissionList, idDataGroup, bCreate, bGetDefault);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AcquisitionFee::getFirstFELTradeFundAlloc( TradeFundAlloc *&pTradeFundAlloc, const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getSplitCommission"));
   assert (getParent() && getParent()->getParent());
   
   Trade *pTrade = dynamic_cast <Trade*> (getParent()->getParent());

   if (pTrade)
   {
      TradeFundAllocList *pFundAllocationList = NULL;

      if (pTrade->getFundAllocationList(pFundAllocationList, idDataGroup) <= WARNING && pFundAllocationList)
      {
         BFObjIter iter ( *pFundAllocationList, idDataGroup, true);
         while(!iter.end ())
         {
            TradeFundAlloc *pLocalTradeFundAlloc = dynamic_cast<TradeFundAlloc*>(iter.getObject());

            if(pLocalTradeFundAlloc)
            {
               DString dstrFundCode;
               DString dstrClassCode;

               pLocalTradeFundAlloc->getField (ifds::FundCode, dstrFundCode, idDataGroup);
               pLocalTradeFundAlloc->getField (ifds::ClassCode, dstrClassCode, idDataGroup);

               FundDetail* pFundDetail = NULL;
               if(getWorkSession().getFundDetail (dstrFundCode, dstrClassCode, idDataGroup, pFundDetail) && pFundDetail)
               {
                  DString dstrLoadType;
                  pFundDetail->getField (ifds::LoadType, dstrLoadType, idDataGroup, false);
                  if(dstrLoadType == I_("FEL"))
                  {
                     pTradeFundAlloc = pLocalTradeFundAlloc;
                     break;
                  }
               }
            }
            ++iter;
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AcquisitionFee::getAcqFeeDefault ( AcqFeeInquiry *&pAcqFeeInquiry,
                                            const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getAcqFeeDefault"));
   
   if (SplitCommission::isTypeZERO (getWorkSession()))
   {
      DString transType,
         accountNum,
         fromFund,
         fromClass,
         toFund,
         toClass,
         fundCode,
         classCode,
			toAccountNum,
			toAcctTaxType,
		tradeIndate;
   
      getContext().getField (ifds::TransType, transType, idDataGroup);
      getContext().getField (ifds::FromFund, fromFund, idDataGroup);
      getContext().getField (ifds::FromClass, fromClass, idDataGroup);
      getContext().getField (ifds::AccountNum, accountNum, idDataGroup);
      
		if (DSTCommonFunctions::codeInList (transType, TRADETYPE::PURCHASE_LIKE))
      {
         fundCode = fromFund;
         classCode = fromClass;	
      }
      else if ( transType == TRADETYPE::ROLLOVER ||
                DSTCommonFunctions::codeInList (transType, TRADETYPE::EXCHANGE_LIKE))
      {
         getContext().getField (ifds::AccountTo, toAccountNum, idDataGroup);
         getContext().getField (ifds::ToFund, toFund, idDataGroup);
         getContext().getField (ifds::ToClass, toClass, idDataGroup);
         fundCode = toFund;
         classCode = toClass;

			if (toAccountNum != accountNum)
			{
				MFAccount *pMFAccountTo = NULL;

				if ( !toAccountNum.empty() &&
						getWorkSession().getMFAccount (idDataGroup, toAccountNum, pMFAccountTo) <= WARNING && 
						pMFAccountTo)
				{
					pMFAccountTo->getField (ifds::TaxType, toAcctTaxType, idDataGroup);

				}
			}
      }

      MFAccount *pMFAccount = NULL;

      if ( !accountNum.empty() &&
           !fromFund.empty() &&
           !fromClass.empty() &&
            getWorkSession().getMFAccount (idDataGroup, accountNum, pMFAccount) <= WARNING && 
            pMFAccount)
      {
         FundDetail *pFundDetail = NULL;
      
         if ( getWorkSession().
                getFundDetail (fundCode, classCode, idDataGroup, pFundDetail) && 
              pFundDetail)
         {
            DString fundCurrency,
               settleCurrency,
               tradeDate,
               amount,
               amtType,
               taxType,
               brokerCode;
         
            pFundDetail->getField (ifds::Currency, fundCurrency, idDataGroup, false);
            getContext().getField (ifds::SettleCurrency, settleCurrency, idDataGroup, false);
            if (settleCurrency.empty())
            {
               settleCurrency = fundCurrency;
            }
            pMFAccount->getField (ifds::TaxType, taxType, idDataGroup);
            taxType.strip ().upperCase ();
            pMFAccount->getField (ifds::BrokerCode, brokerCode, idDataGroup, false);
            getContext().getField (ifds::EffectiveDate, tradeDate, idDataGroup, false);
            getContext().getField (ifds::Amount, amount, idDataGroup, false);
            getContext().getField (ifds::AmtType, amtType, idDataGroup, false);
		    getContext().getField (ifds::TradeInDate, tradeIndate, idDataGroup, false);
            double dec_amount = DSTCommonFunctions::convertToDouble (amount);
            if (dec_amount != 0 || isFullExchange (idDataGroup))
            {
               DString strKey = 
                  I_("AcqFeeInquiry_TransType") + transType +
                  I_(";FundCode=") + fromFund +
                  I_(";ClassCode=") + fromClass +
                  I_(";EffectiveDate=") + tradeDate +
                  I_(";AccountNum=") + accountNum +
                  I_(";BrokerCode=") + brokerCode +
                  I_(";ToFund=") + toFund +
                  I_(";ToClass=") + toClass +
                  I_(";TaxType=") + taxType +
                  I_(";Amount=") + amount +
                  I_(";AmtType=") + amtType +
                  I_(";Currency=") + settleCurrency +
				  I_(";ToAcctTaxType=") + toAcctTaxType+
				  I_(";AcctNumbr=")  +accountNum +
				  I_(";TradeInDate=") +tradeIndate;
   
               pAcqFeeInquiry = 
                     dynamic_cast <AcqFeeInquiry*> (getObject (strKey, idDataGroup));

               if (!pAcqFeeInquiry)
               {
                  pAcqFeeInquiry = new AcqFeeInquiry (*this);
                  pAcqFeeInquiry->setFundCurrency (fundCurrency);
                  if (pAcqFeeInquiry->init ( taxType, 
                                             transType, 
                                             tradeDate,
                                             amount, 
                                             amtType, 
                                             fromFund, 
                                             fromClass, 
                                             settleCurrency,
                                             brokerCode, 
                                             toFund, 
                                             toClass,
															I_("N"),  // flatpercent default
															I_("N"),  // track default
															NULL_STRING ,  // activity default
															toAcctTaxType,
															accountNum,
															tradeIndate) <= WARNING)
                  {
                     setObject ( pAcqFeeInquiry, 
                                 strKey, 
                                 OBJ_ACTIVITY_NONE, 
                                 idDataGroup);
                  }
                  else
                  {
                     delete pAcqFeeInquiry;
                     pAcqFeeInquiry = NULL;
                  }
               }
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool AcquisitionFee::isAcqFeeSameAsDefault (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("isAcqFeeSameAsDefault"));
   bool bSameAsDefault = false;

   // if system feature for set default is turned off, then leave the method
   bSameAsDefault = _acqFeeDefault == N;
   if (!bSameAsDefault)
   {
      AcqFeeInquiry *pAcqFeeInquiry = NULL;

      if ( getAcqFeeDefault (pAcqFeeInquiry, idDataGroup) <= WARNING &&
           pAcqFeeInquiry)
      {
         DString defaultAcqFeeType, 
            defaultAcqFee, 
            acqFeeType, 
            acqFee, 
            amount;

         getField (ifds::OrigFeeType, defaultAcqFeeType, idDataGroup, false);
         getField (ifds::OrigFeeRate, defaultAcqFee, idDataGroup, false);
         getField (ifds::FeeType, acqFeeType, idDataGroup, false);
         getField (ifds::FeeRate, acqFee, idDataGroup, true);
         getContext().getField (ifds::Amount, amount, idDataGroup, false);

         double dec_amount = DSTCommonFunctions::convertToDouble (amount);
         double dec_default_fee = DSTCommonFunctions::convertToDouble (defaultAcqFee);
         double dec_fee = DSTCommonFunctions::convertToDouble (acqFee);

// if default fee is flat and trade fee in percentage, then convert the default fee into percentage 
         if ( defaultAcqFeeType == I_("0") &&  // percentage
              acqFeeType == I_("1")) // flat 
         {
            dec_default_fee = dec_default_fee / dec_amount * 100;
         }
// if the default fee in % or scale and acq fee in flat amount, convert the default to flat amount
         else if ( (defaultAcqFeeType == I_("1") ||  // percentage
                    defaultAcqFeeType == I_("2")) &&  // scale
                   acqFeeType == I_("0")) //flat
         {
            dec_default_fee = dec_default_fee * dec_amount / 100;
         }
         bSameAsDefault = dec_default_fee == dec_fee;
      }
   }
   return bSameAsDefault;
}

//******************************************************************************
bool AcquisitionFee::isTradeAllocated (const BFDataGroupId &idDataGroup)
{
   bool bIsTradeAllocated = false;
   assert (getParent() && getParent()->getParent());

   TradeFundAllocList *pFundAllocationList = NULL;
   Trade *pTrade = dynamic_cast <Trade*> (getParent()->getParent());
   bool bSearchForTradeFundAlloc = false;

   if (pTrade) 
   {
      bSearchForTradeFundAlloc = pTrade->getFundAllocationList (pFundAllocationList, idDataGroup) <= WARNING &&
                                 pFundAllocationList;
   }
   else //maybe parent is a pending trade
   {
      PendingTradeDetails *pPendingTradeDetails = dynamic_cast <PendingTradeDetails*> (getParent()->getParent());
      
      if (pPendingTradeDetails)
      {
         DString accountNum;

         getContext().getField (ifds::AccountNum, accountNum, idDataGroup, false);
         TradeAcctAllocList *pAccountAllocationList = NULL;
         if ( pPendingTradeDetails->getAccountAllocationList (pAccountAllocationList, idDataGroup, accountNum) <= WARNING && 
              pAccountAllocationList)
         {
            TradeAcctAlloc *pAccountAllocation = NULL;

            if ( pAccountAllocationList->getAccountAllocation (accountNum, pAccountAllocation, idDataGroup) <= WARNING && 
                 pAccountAllocation)
            {
               bSearchForTradeFundAlloc = 
                     pAccountAllocation->getFundAllocationList (pFundAllocationList, idDataGroup) <= WARNING && 
                     pFundAllocationList;
            }
         }
      }
   }
   if (bSearchForTradeFundAlloc)
   {
      BFObjIter iter ( *pFundAllocationList, 
                        idDataGroup, 
                        false, 
                        BFObjIter::ITERTYPE::NON_DELETED);
      DString fundCode,
         classCode,
         transType;

      getContext().getField (ifds::TransType, transType, idDataGroup);
      if (DSTCommonFunctions::codeInList (transType, TRADETYPE::EXCHANGE_LIKE))
      {
         //look at the to side
         getContext().getField (ifds::ToFund, fundCode, idDataGroup);
         getContext().getField (ifds::ToClass, classCode, idDataGroup);   
      }
      else
      {
         //look at the from side
         getContext().getField (ifds::FromFund, fundCode, idDataGroup);
         getContext().getField (ifds::FromClass, classCode, idDataGroup);   
      }
      bIsTradeAllocated = 
//the next check is due to the fact that the object gets notified prior to the allocation list being blown away
         fundCode.empty() && classCode.empty() &&  
         iter.getNumberOfItemsInList () > 1; //1 means 100% allocation
   }
   return bIsTradeAllocated;
}

//******************************************************************************
bool AcquisitionFee::isFullRedemption (const BFDataGroupId &idDataGroup)
{
   DString amount,
      transType;

   getContext().getField (ifds::TransType, transType, idDataGroup);
   getContext().getField (ifds::Amount, amount, idDataGroup, false);
   double dec_amount = DSTCommonFunctions::convertToDouble (amount);
//redemption fee should be applicable even if amount is zero
   return DSTCommonFunctions::codeInList (transType, TRADETYPE::REDEMPTION_LIKE) && 
          dec_amount == 0.0; 
}

//******************************************************************************
bool AcquisitionFee::isFullExchange (const BFDataGroupId &idDataGroup)
{
   DString amount,
      transType;

   getContext().getField (ifds::TransType, transType, idDataGroup);
   getContext().getField (ifds::Amount, amount, idDataGroup, false);
   double dec_amount = DSTCommonFunctions::convertToDouble (amount);
//exchange fee should be applicable even if amount is zero
   return DSTCommonFunctions::codeInList (transType, TRADETYPE::EXCHANGE_LIKE) && 
          dec_amount == 0.0; 
}

//******************************************************************************
bool AcquisitionFee::isExchangeForNotNewMoney (const BFDataGroupId &idDataGroup)
{
   bool bIsExchangeForNotNewMoney = false;
   DString transType;

   getContext().getField (ifds::TransType, transType, idDataGroup);
   if (DSTCommonFunctions::codeInList (transType, TRADETYPE::EXCHANGE_LIKE))
   {
      DString fromFund, 
         fromClass, 
         toFund, 
         toClass;

      getContext().getField (ifds::FromFund, fromFund, idDataGroup);
      getContext().getField (ifds::FromClass, fromClass, idDataGroup);
      getContext().getField (ifds::ToFund, toFund, idDataGroup);   
      getContext().getField (ifds::ToClass, toClass, idDataGroup);
      FundDetail *pToFundDetail = NULL,
         *pFromFundDetail = NULL;

      if ( !toFund.empty() && 
           !toClass.empty() &&
            getWorkSession().
               getFundDetail (toFund, toClass, idDataGroup, pToFundDetail) && 
            pToFundDetail &&
            !fromFund.empty() &&
            !fromClass.empty() &&
            getWorkSession().
               getFundDetail (fromFund, fromClass, idDataGroup, pFromFundDetail) && 
            pFromFundDetail)
      {
         FundToList fundToList (*this);

         bIsExchangeForNotNewMoney = 
            !fundToList.isBuySell (fromFund, fromClass, toFund, toClass);
      }
   }
   return bIsExchangeForNotNewMoney;
}

//******************************************************************************
SEVERITY AcquisitionFee::setFeeRate(const DString& dstrFeeRate, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setFeeRate" ) );

   setFieldNoValidate(ifds::FeeRate, dstrFeeRate, idDataGroup, false, true, false, false);

   return(GETCURRENTHIGHESTSEVERITY());
};

//******************************************************************************
SEVERITY AcquisitionFee::applyTransFeeRateToAllocation(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("applyTransFeeRateToAllocation"));

   propagateFeeRateChangeToFundAlloc(idDataGroup, true);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AcquisitionFee.cpp-arc  $
// 
//    Rev 1.55   Jul 31 2012 14:13:14   wp040027
// IN# 3006862-CPF-Enable Fee in PAC/Corrected default Fee in PAC and Trade screen/Max Fee Validation
// 
//    Rev 1.54   Apr 24 2012 20:42:32   wp040039
// PETP0187485-Trade Entry And Processing
// 
//    Rev 1.53   Feb 09 2012 19:34:00   popescu
// 2821238 - Base Commission should be calculated on Overriding the default Acquisition Fee
// 
//    Rev 1.52   Nov 28 2011 23:07:44   popescu
// INA Commission Work
// 
//    Rev 1.51   Nov 27 2011 19:39:44   popescu
// INA Commission Work
// 
//    Rev 1.50   May 26 2011 14:51:58   jankovii
// IN 2539838 - Not able to place Redemption Trade with Redemption if Fee Type is Flat
// 
//    Rev 1.49   Mar 10 2011 15:29:44   jankovii
// IN 2458927 - P0181943 - SWIFT XML - Split Commission Exchanges
// 
//    Rev 1.48   Mar 04 2011 12:07:48   jankovii
// PET181943 FN01 - XMLPhase 2
// 
//    Rev 1.47   Dec 04 2009 11:19:14   popescu
// Incident 1934247 - should not charge acquisition fee for allocated purchases in all envs
// 
//    Rev 1.46   Dec 03 2009 17:14:56   popescu
// Incident 1934247 - should not charge acquisition fee for allocated purchases in non-split envs
// 
//    Rev 1.45   Sep 29 2009 14:50:34   popescu
// Incident 1847231 - Default value of Option and Rate of Fee Type 112, 212, 113 and 213
// 
//    Rev 1.44   Oct 05 2006 17:29:44   AGUILAAM
// IN 721266 - new field ToAcctTaxType to get applicable transfer fees.
// 
//    Rev 1.43   Sep 22 2005 14:39:44   popescu
// Incident# 410516 - show the AcquistionFee for allocated trades.
// 
//    Rev 1.42   Jul 15 2005 16:11:52   ZHANGCEL
// PET 1203 FN04 -- Jumbo Price enhancement
// 
//    Rev 1.41   Jun 28 2005 12:07:36   popescu
// Incident #342270 - refresh acquisition fee if exch rate changes
// 
//    Rev 1.40   Jun 27 2005 12:01:50   popescu
// Incindent 338408: force refreshes on split commission if user changes amount/roa value
// 
//    Rev 1.39   Apr 11 2005 16:10:10   popescu
// Incident #285556 - user is able to charge any flat fee amount for full redemptions. Also, for partial redemption validation is meant to stop the user charge a fee that is more then the redemption amount.
// 
//    Rev 1.38   Apr 05 2005 10:03:36   popescu
// Incident# 279417, default the acquisition fee to split commission total rate for SSB env, commission type one
// 
//    Rev 1.37   Mar 09 2005 09:58:34   popescu
// PET 1117/06, fixed the isTradeAllocated logic, based on the trans type, method should look at either to or from side
// 
//    Rev 1.36   Mar 03 2005 08:55:12   popescu
// PET 1117/56, fixed max validation for redemption fee
// 
//    Rev 1.35   Mar 03 2005 08:13:08   popescu
// PET 1117/06 added restore functionality for fees, when modifying a pending trade, even if the TransFee table is not populated
// 
//    Rev 1.34   Feb 28 2005 18:35:08   winnie
// PET 1117 FN56 : Correct the Exchange and Transfer Fee works the same way as release 58. Full Exchange should get the max fee from back end; Transfer and Exchange should share the same logic for Exchange Fee default and validation
// 
//    Rev 1.33   Feb 28 2005 10:00:36   popescu
// PET 1117/56, acquisition fee should show-up as exchange fee for transfer, when to load fund is FEL and new money
// 
//    Rev 1.32   Feb 22 2005 14:04:40   popescu
// Incident #249310, validation of split commissions should be done against the initial total value, rather then 0 amount
// 
//    Rev 1.31   Feb 17 2005 10:19:48   popescu
// PTS 243445, set charge oprtion to '0'-Charge to save a view call to 197
// 
//    Rev 1.30   Feb 15 2005 11:57:36   popescu
// 237796, exchange fee default should be set to 0 if not a buy and sell exchange/transfer (not new money)
// 
//    Rev 1.29   Feb 04 2005 17:15:50   popescu
// 232973, Exchange Fee validation issue if amount if full exchange
// 
//    Rev 1.28   Feb 01 2005 17:44:38   popescu
// INC 232973, Exchange Fee should be made available even if amount of trade is zero.
// 
//    Rev 1.27   Jan 31 2005 18:19:38   popescu
// PET 1117/06/56, set the acq fee related fields to read only if shareholder has a fee model. Also, set option '1' for TradeFeeOption (Charge per system calculated)
// 
//    Rev 1.26   Jan 23 2005 15:18:42   popescu
// PTS 10037346, fixed simultaneous availablity of acq and exch fee
// 
//    Rev 1.25   Jan 23 2005 13:56:22   popescu
// PTS 10037346, made exchange available for the user
// 
//    Rev 1.24   Jan 20 2005 19:16:22   popescu
// PTS 10037792, set the fee type for split env to read only
// 
//    Rev 1.23   Jan 19 2005 14:20:50   popescu
// PTS 10038083, enabled acquisition fee for split comm type 2 (manulife env.) and calculate the splits if total rate changes
// 
//    Rev 1.22   Jan 14 2005 10:30:50   popescu
// PTS 10037865, charge option field should be 'Charge' and locked for Conditionrate and all other fees, but TrxnFee where user should be allowed to change its value.
// 
//    Rev 1.21   Jan 12 2005 19:06:24   popescu
// PTS 10037792, default fee type in a split comm environment should percentage
// 
//    Rev 1.20   Jan 12 2005 18:51:04   popescu
// PTS 10037339, allowed user to set Redemption Fee up
// 
//    Rev 1.19   Jan 10 2005 10:38:10   popescu
// PTS 10037553, fixed fees properties in pending mode and trade reset of the trans type combo
// 
//    Rev 1.18   Jan 05 2005 12:49:44   popescu
// PTS 10037294, consider AcqFeeDefault system feature when setting the acq fee default value
// 
//    Rev 1.17   Jan 04 2005 16:15:02   popescu
// PTS 10037245, enable acq fee default for user input if trade is allocated and DisableFee4Alloc is turned off
// 
//    Rev 1.16   Dec 31 2004 12:54:46   popescu
// PTS 10037399, AcquistionFee system level applicability should not be dictated by the DisableFee4Alloc system feature
// 
//    Rev 1.15   Dec 20 2004 14:47:48   popescu
// PTS 10037057, corrected the error message for for AcqFee type percent with a rate less then minimum rate 
// 
//    Rev 1.14   Dec 16 2004 15:33:20   popescu
// PTS 10036050, undone the validation not required anymore
// 
//    Rev 1.13   Dec 15 2004 15:55:16   popescu
// PET 1117/06, fixes related to condition rates scale type/ acq fee option defaults
// 
//    Rev 1.12   Dec 11 2004 13:25:24   popescu
// PET 1117/06, more fixes for banking instr in pending mode.
// 
//    Rev 1.11   Dec 10 2004 15:36:42   popescu
// PET 1117/56 set fee type default to percent if view returns empty
// 
//    Rev 1.10   Dec 09 2004 22:30:52   popescu
// PET 11717/06, fees and mod pending trades
// 
//    Rev 1.9   Dec 08 2004 22:08:06   popescu
// PET 1117/06, more fees
// 
//    Rev 1.8   Dec 07 2004 01:37:22   popescu
// PET 1117/56 trades processing/modify trade
// 
//    Rev 1.7   Dec 02 2004 18:22:46   popescu
// PET 1117/06/56, trades processing/fees processing
// 
//    Rev 1.6   Dec 01 2004 11:10:22   popescu
// PTS 10036050, fee cannot be percent for red code 16,17 bearer certificate
// 
//    Rev 1.5   Nov 27 2004 21:18:46   popescu
// PET 1117/06, trades processing
// 
//    Rev 1.4   Nov 24 2004 21:35:32   popescu
// PET 1117/06/56. trade processing, settle location
// 
//    Rev 1.3   Nov 18 2004 13:47:46   YINGBAOL
// PET1117: performance tunning.
// 
//    Rev 1.2   Nov 17 2004 16:14:22   popescu
// PET 1117/06, trade processing, fees
// 
//    Rev 1.1   Nov 15 2004 16:22:08   popescu
// PET 1117/06, more synch to .NET changes
// 
//    Rev 1.0   Nov 15 2004 13:38:46   popescu
// Initial revision.
// 
//    Rev 1.0   Nov 10 2004 09:31:18   popescu
// Initial revision.
// 
//    Rev 1.0   Nov 06 2004 00:35:04   popescu
// Initial revision.
// 
//    Rev 1.0   Nov 04 2004 11:03:16   popescu
// Initial revision.
// 
 */