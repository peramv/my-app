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
// ^FILE   : XferInFee.cpp
// ^AUTHOR : Serban Popescu
// ^DATE   : November 2004
//
// ^CLASS    : XferInFee
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "xferinfee.hpp"

#include "funddetail.hpp"
#include "fundtolist.hpp"
#include "mfaccount.hpp"
#include "trade.hpp"
#include "tradefundalloc.hpp"
#include "tradefundalloclist.hpp"
#include "splitcommission.hpp"
#include "splitcommissionlist.hpp"
#include "transfeelist.hpp"
#include "tradeacctalloclist.hpp"
#include "tradeacctalloc.hpp"
#include "pendingtradedetails.hpp"

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME		= I_("XferInFee");
   const I_CHAR *  SCALE			= I_("2");
   const I_CHAR *  TIER				= I_("3");
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

   extern CLASS_IMPORT const BFTextFieldId TransType;
   extern CLASS_IMPORT const BFIntegerFieldId TransFeeCode;
   //acount fields
   extern CLASS_IMPORT const BFTextFieldId TaxType;
   //fund fields
   extern CLASS_IMPORT const BFTextFieldId ExchInFeeExist;
   extern CLASS_IMPORT const BFTextFieldId LoadType;
   extern CLASS_IMPORT const BFTextFieldId CombinedLoadType; 
//fee fields
   extern CLASS_IMPORT const BFDecimalFieldId Rate;
}

namespace CND
{  // Conditions used
	extern const long ERR_INVALID_FEE_TYPE;
	extern const long ERR_FEETYPE_NOT_SUPPORTED;
	extern const long WARN_FEETYPE_NOT_SUPPORTED;
}

namespace FEES
{
   //this fee deals with the IFeeTo field value in trade
   extern const I_CHAR * XFER_IN;
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const EXCHANGE;
   extern CLASS_IMPORT I_CHAR * const TRANSFER;
   extern CLASS_IMPORT I_CHAR * const PURCHASE_LIKE;
   extern CLASS_IMPORT I_CHAR * const EXCHANGE_LIKE;
   extern CLASS_IMPORT I_CHAR * const INTER_CLASS_SWITCH;
}

//******************************************************************************
XferInFee::XferInFee (BFAbstractCBO &parent) : TransFeeRate (parent, FEES::XFER_IN),
_acqFeeDefault (NULL_STRING)
{
   TRACE_CONSTRUCTOR (CLASSNAME, NULL_STRING);
   getWorkSession ().getOption ( ifds::AcqFeeDefault,                               
                                 _acqFeeDefault, 
                                 BF::HOST,
                                 false);         
}

//******************************************************************************
XferInFee::~XferInFee()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}

//******************************************************************************
SEVERITY XferInFee::restore ( BFCBO &rpParent, 
                              const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("restore"));
   DString feeRate;

   rpParent.getField (ifds::FeeTo, feeRate, idDataGroup);
   getFormattedFee (idDataGroup, feeRate);
   setFieldNoValidate ( ifds::FeeRate, feeRate, idDataGroup, false, 
                        false, false, false);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool XferInFee::isSystemApplicable (const BFDataGroupId &idDataGroup)
{
   return !SplitCommission::isTypeZERO (getWorkSession ());
}

//******************************************************************************
bool XferInFee::isContextApplicable (const BFDataGroupId &idDataGroup)
{
   if (TransFee::isContextApplicable(idDataGroup))
   {
	   DString transType;

	   getContext().getField (ifds::TransType, transType, idDataGroup, false);
       return (transType == TRADETYPE::EXCHANGE || transType == TRADETYPE::INTER_CLASS_SWITCH || transType == TRADETYPE::TRANSFER) &&
			  !isFeeWaivedForAccount (idDataGroup) &&
			  isApplicableForFund (idDataGroup);
   }
   return false;
}

//******************************************************************************
bool XferInFee::hasContextChanged (const BFDataGroupId &idDataGroup)
{
//fee needs to be refreshed if any of the 158 related fields changed
   bool retVal = false;
   retVal = hasFieldContextChanged (ifds::FromFund, idDataGroup) ||
          hasFieldContextChanged (ifds::FromClass, idDataGroup) ||
          hasFieldContextChanged (ifds::ToFund, idDataGroup) ||
          hasFieldContextChanged (ifds::ToClass, idDataGroup) ||
          hasFieldContextChanged (ifds::AmtType, idDataGroup) ||
          hasFieldContextChanged (ifds::EffectiveDate, idDataGroup) ||
          hasFieldContextChanged (ifds::SettleCurrency, idDataGroup) ||
          hasFieldContextChanged (ifds::AccountTo, idDataGroup) ||
          hasFieldContextChanged (ifds::Broker, idDataGroup) ||
          hasFieldContextChanged (ifds::Branch, idDataGroup) ||
          hasFieldContextChanged (ifds::SlsrepCode, idDataGroup) ||
          hasFieldContextChanged (ifds::ROAAmount, idDataGroup) ||
          hasFieldContextChanged (ifds::Amount, idDataGroup) ;
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
SEVERITY XferInFee::init (const BFData &viewData)
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
            if(pTradeFundAlloc)
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

   //if(pTrade && !isApplicableForFund (BF::HOST)) //create the acquisition fee for pending trades
   //{
   //   return SEVERE_ERROR;
   //} 

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY XferInFee::doValidateField ( const BFFieldId &idField, 
                                      const DString &strValue, 
                                      const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doValidateField"));
   
   if (idField == ifds::FeeRate) //the maximum should be validated against the split commission list
   {
      SplitCommissionList *pSplitCommissionList = NULL;
      
      //get the split commission from trade....
      assert (getParent() && getParent()->getParent());
      
      Trade *pTrade = dynamic_cast <Trade*> (getParent()->getParent());

      if (pTrade)
      {
         pTrade->getSplitCommissionList (pSplitCommissionList, idDataGroup);
      }
      if (GETCURRENTHIGHESTSEVERITY () <= WARNING && pSplitCommissionList)
      {
         DString maxFee,
            feeRate,
            initialTotalRate;

         pSplitCommissionList->getField (ifds::Fee, maxFee, idDataGroup, false);
         pSplitCommissionList->getInitialTotalRate (initialTotalRate, idDataGroup);
         getField (ifds::FeeRate, feeRate, idDataGroup, false);
         double dMaxFee = DSTCommonFunctions::convertToDouble (maxFee),
                  dFee = DSTCommonFunctions::convertToDouble (feeRate),
                  dInitialTotalRate = DSTCommonFunctions::convertToDouble (initialTotalRate);
      
         SplitCommissionList::canFeeBeDiscounted ( pSplitCommissionList,
			                                       getWorkSession (), 
                                                   dFee, 
                                                   dInitialTotalRate, 
                                                   dMaxFee, 
                                                   idDataGroup);
      }
   }
   else if (idField == ifds::FeeType)
   {
	    if (DSTCommonFunctions::codeInList (strValue, FEES_NOT_ALLOWED) && !SplitCommission::isTypeZERO (getWorkSession()))
		{
			getErrMsg (I_("1113"), CND::ERR_FEETYPE_NOT_SUPPORTED, CND::WARN_FEETYPE_NOT_SUPPORTED, idDataGroup);
		}

	    if (strValue == SCALE || strValue == TIER)
		{
            ADDCONDITIONFROMFILE (CND::ERR_INVALID_FEE_TYPE);
		}
		else
		{
			Trade *pTrade = dynamic_cast <Trade*> (getParent()->getParent());

			if (pTrade)
			{
				SplitCommissionList *pSplitCommissionList = NULL;

				if ( pTrade->getSplitCommissionList (pSplitCommissionList, idDataGroup) <= WARNING &&
					pSplitCommissionList)
				{
					pSplitCommissionList->setField (ifds::FeeType, strValue, idDataGroup, false, true);
				}   
			}
		}
   }
   else
   {
      TransFeeRate::doValidateField (idField, strValue, idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY XferInFee::doApplyRelatedChanges ( const BFFieldId &idField, 
                                            const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doApplyRelatedChanges"));
   if (TransFeeRate::doApplyRelatedChanges (idField, idDataGroup) <= WARNING)
   {
      if (idField == ifds::FeeRate)
      {
         assert (getParent() && getParent()->getParent());
         propagateFeeRateChangeToFundAlloc(idDataGroup, true);

         Trade *pTrade = dynamic_cast <Trade*> (getParent()->getParent());
         SplitCommissionList *pSplitCommissionList = NULL;
         if (pTrade)
         {
            pTrade->getSplitCommissionList (pSplitCommissionList, idDataGroup);
         }
         if (GETCURRENTHIGHESTSEVERITY () <= WARNING && pSplitCommissionList)
         {
            DString feeRate;

            getField (ifds::FeeRate, feeRate, idDataGroup, false);

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
               TradeFundAlloc* pTradeFundAlloc = dynamic_cast<TradeFundAlloc*>(pSplitCommissionList->getParent());
               if(pTradeFundAlloc && pTradeFundAlloc->isFELFundClass(idDataGroup))
               {
                  pSplitCommissionList->setField ( ifds::Rate, feeRate, idDataGroup, false, true);
               }
            }
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
			    
				Trade *pTrade = dynamic_cast <Trade*> (getParent()->getParent());

				if (pTrade)
				{
					SplitCommissionList *pSplitCommissionList = NULL;

					if ( pTrade->getSplitCommissionList(pSplitCommissionList, idDataGroup) <= WARNING &&
						pSplitCommissionList)
					{
						pSplitCommissionList->initDefaultFlatFeeData (idDataGroup);
						bReadOnly = true;
					}

					setFieldReadOnly (ifds::FeeRate, idDataGroup, true);
				}
			}
			else if (feeType == PERCENT)
			{
	            setFieldReadOnly (ifds::FeeRate, idDataGroup, false);

				Trade *pTrade = dynamic_cast <Trade*> (getParent()->getParent());

				if (pTrade)
				{
					SplitCommissionList *pSplitCommissionList = NULL;
					// get default data:
					pTrade->getSplitCommissionList(pSplitCommissionList, idDataGroup);
				}

				//notify the trans fee list of the change
				TransFeeList *pTransFeeList = dynamic_cast <TransFeeList*> (getParent());
   
				if (pTransFeeList)
				{
					pTransFeeList->onNotify (FIELD_NOTIFICATIONS, E_EVENT_VALUE_CHANGE, I_("ForceRefresh"));
				}
			}
		 }
	  }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY XferInFee::setFeeType (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("setFeeType"));
   DString feeType (I_("1")); //percent

   setFieldReadOnly (ifds::FeeType, idDataGroup, false);
   setFieldNoValidate (ifds::FeeType, feeType, idDataGroup, false, false, true, false);
   setFieldNoValidate (ifds::OrigFeeType, feeType, idDataGroup, false, false, true, false);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY XferInFee::setFeeDefault (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("setFeeDefault"));
//set the fee currency
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
      DString toLoadType,
         fromLoadType;

      pToFundDetail->getField (ifds::LoadType, toLoadType, idDataGroup, false);
      pFromFundDetail->getField (ifds::LoadType, fromLoadType, idDataGroup, false);
      FundToList fundToList( *this );

      DString feeRate (I_("0"));

      bool bReadOnly = SplitCommission::isTypeONE (getWorkSession ()) ||
                      (SplitCommission::isTypeTWO (getWorkSession ()) && toLoadType == I_("BEL"));
      //get the split commission from trade....
      assert (getParent() && getParent()->getParent());
      
      Trade *pTrade = dynamic_cast <Trade*> (getParent()->getParent());

      bool limitedByTaxTypeMaxFee = false;
      if (pTrade)
      {
         SplitCommissionList *pSplitCommissionList = NULL;

         if ( getSplitCommission (pSplitCommissionList, idDataGroup) <= WARNING &&
              pSplitCommissionList)
         {
            DString dstrSFACRate (NULL_STRING);
            bool baseCommApplicable (false);
            assert (getParent() && getParent()->getParent());
            Trade *pTrade = dynamic_cast <Trade*> (getParent()->getParent());

            TradeFundAlloc *pTradeFundAlloc = NULL;
            if(getFirstFELTradeFundAlloc(pTradeFundAlloc, idDataGroup) <= WARNING 
               && pTradeFundAlloc 
               && pTradeFundAlloc->isBaseCommissionApplicableAndGetSFACRate(baseCommApplicable, dstrSFACRate, idDataGroup)  <= WARNING 
               && baseCommApplicable)
            {
               pSplitCommissionList->getField (ifds::Fee, feeRate, idDataGroup, true);
            }
            else
            {
               pSplitCommissionList->getSplitTotalRate (feeRate, idDataGroup);
               DString dstrTaxTypeMaxFee = pSplitCommissionList->getTaxTypeMaxFee(idDataGroup);
			   if( !dstrTaxTypeMaxFee.empty() )
			   {
				   BigDecimal bdTotalRate(feeRate);
				   BigDecimal bdTaxTypeMaxFee(dstrTaxTypeMaxFee);

				   if( bdTaxTypeMaxFee < bdTotalRate)
				   {
					   feeRate = dstrTaxTypeMaxFee;
					   pSplitCommissionList->propagateTotalRate(feeRate,idDataGroup);	
                  limitedByTaxTypeMaxFee = true;
				   }
			   }
            }
            if (_acqFeeDefault == N && toLoadType == I_("FEL") && SplitCommission::isTypeTWO (getWorkSession ()))
            {
               feeRate = I_("0");
            }
         }
      }
      setFieldReadOnly (ifds::FeeRate, idDataGroup, bReadOnly);
   //do not allow change based on the conditions dictated by read only flag
      setFieldReadOnly (ifds::TradeFeeOption, idDataGroup, bReadOnly); 
   //set the fee rate
      getFormattedFee (idDataGroup, feeRate);
      setFieldNoValidate (ifds::FeeRate, feeRate, idDataGroup, false, false, true, !limitedByTaxTypeMaxFee);
      setFieldNoValidate (ifds::OrigFeeRate, feeRate, idDataGroup, false, false, true, false);
   }
   else
   {
      setFieldNoValidate (ifds::FeeRate, I_("0"), idDataGroup, false, false, true, true);
   }
//set fee currency
   DString fundCurrency;
   if(pToFundDetail)
      pToFundDetail->getField (ifds::Currency, fundCurrency, idDataGroup, false);
   setField (ifds::Currency, fundCurrency, idDataGroup, false);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY XferInFee::setFeeMinMax (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("setFeeMinMax"));
//nothing to do here, min max are validated against split commission list
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool XferInFee::isApplicableForFund (const BFDataGroupId &idDataGroup)
{
   bool bIsApplicable = false;
   DString transType;

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
   else
   {
      DString fromFund;
      DString fromClass;
      DString toFund; 
      DString toClass;

      getContext().getField (ifds::FromFund, fromFund, idDataGroup);
      getContext().getField (ifds::FromClass, fromClass, idDataGroup);
      getContext().getField (ifds::ToFund, toFund, idDataGroup);   
      getContext().getField (ifds::ToClass, toClass, idDataGroup);
      FundDetail *pToFundDetail = NULL;
      FundDetail *pFromFundDetail = NULL;
      FundToList fundToList (*this);


      bIsApplicable = !toFund.empty() &&  
                     !toClass.empty() &&
                     getWorkSession().getFundDetail (toFund, toClass, idDataGroup, pToFundDetail) && 
                     pToFundDetail &&
                     !fromFund.empty() &&
                     !fromClass.empty() &&
                     getWorkSession().getFundDetail (fromFund, fromClass, idDataGroup, pFromFundDetail) && 
                     pFromFundDetail &&
                     (fundToList.isBuySell (fromFund, fromClass, toFund, toClass) ||  //new money
                     isROAApplicable (idDataGroup));
   }
   return bIsApplicable;
}

//******************************************************************************
SEVERITY XferInFee::setFeeProperties (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("setFeeProperties"));
   TransFeeRate::setFeeProperties (idDataGroup);
   setFieldReadOnly (ifds::ChargeOption, idDataGroup, true);
   return GETCURRENTHIGHESTSEVERITY();
}

//**********************************************************************************
bool XferInFee::isROAApplicable (const BFDataGroupId &idDataGroup) 
{
    bool bRet = true;
    Trade *pTrade = dynamic_cast <Trade*> (getParent()->getParent());

    if (pTrade)
    {
      if (pTrade->isROAApplicable (idDataGroup))
      {
         DString roaAmount;
      
         getContext().getField (ifds::ROAAmount, roaAmount, idDataGroup);
         bRet = DSTCommonFunctions::convertToDouble (roaAmount) > 0;
      }
    }
    return bRet;
}

//******************************************************************************
bool XferInFee::propagateFeeRateChangeToFundAlloc(const BFDataGroupId &idDataGroup, bool bApplyToSplitComm)
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
                  {
                     pFundAllocation->setField(ifds::FeeRate, dstrFeeRate, idDataGroup, true, false, false);
                  }
                  retVal = true;
               }
               ++iterFundAllocList;
            }
         }
         ++iterAccountAllocList;
      }
   }
   return retVal;
}

//******************************************************************************
SEVERITY XferInFee::setFeeRate(const DString& dstrFeeRate, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setFeeRate" ) );

   setFieldNoValidate(ifds::FeeRate, dstrFeeRate, idDataGroup, false, true, false, false);

   return(GETCURRENTHIGHESTSEVERITY());
};

//******************************************************************************
SEVERITY XferInFee::applyTransFeeRateToAllocation(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("applyTransFeeRateToAllocation"));
   propagateFeeRateChangeToFundAlloc(idDataGroup, true);
   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
bool XferInFee::isTradeAllocated (const BFDataGroupId &idDataGroup)
{
   bool bIsTradeAllocated = false;
   assert (getParent() && getParent()->getParent());

   TradeFundAllocList *pFundAllocationList = NULL;
   Trade *pTrade = dynamic_cast <Trade*> (getParent()->getParent());
   bool bSearchForTradeFundAlloc = false;

   if (pTrade) 
   {
      DString strKey = I_("AccountAllocationList");

      TradeAcctAllocList *pAccountAllocationList = dynamic_cast <TradeAcctAllocList *> (pTrade->getObject(strKey, idDataGroup));
      if(pAccountAllocationList)
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
SEVERITY XferInFee::getSplitCommission ( SplitCommissionList *&pSplitCommissionList,
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
SEVERITY XferInFee::getFirstFELTradeFundAlloc( TradeFundAlloc *&pTradeFundAlloc, const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getSplitCommission"));
   assert (getParent() && getParent()->getParent());
   
   Trade *pTrade = dynamic_cast <Trade*> (getParent()->getParent());
   TradeFundAlloc* pNonFELTradeFundAlloc = NULL;
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
                  else if(pNonFELTradeFundAlloc == NULL)
                  {
                     pNonFELTradeFundAlloc = pLocalTradeFundAlloc;
                  }

               }
            }
            ++iter;
         }
      }
   }

   if(SplitCommission::isTypeTWO (getWorkSession ()) && !pTradeFundAlloc)
      pTradeFundAlloc = pNonFELTradeFundAlloc;
   return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/XferInFee.cpp-arc  $
// 
//    Rev 1.19   Jul 31 2012 15:01:52   wp040027
// Sync up: IN# 3006862-CPF-Enable Fee in PAC/Corrected default Fee in PAC and Trade screen/Max Fee Validation
// 
//    Rev 1.18   Jul 03 2012 06:41:40   popescu
// 2991448 - Exchange to FEL - Default FEL rate
// 
//    Rev 1.17   Jun 28 2012 19:47:46   popescu
// IN# 2984281 - iFeeTo is not populated
// 
//    Rev 1.16   Jun 19 2012 21:21:58   popescu
// 2991448 - Exchange to FEL - Default FEL rate
// 
//    Rev 1.15   Jun 06 2012 11:38:50   popescu
// 2947575 - Applying base commission (SFAC) for exchanges
// 
//    Rev 1.14   May 15 2012 22:12:06   popescu
// 2947575 - Applying base commission (SFAC) for exchanges
// 
//    Rev 1.13   May 26 2011 14:52:58   jankovii
// IN 2539838 - Not able to place Redemption Trade with Redemption if Fee Type is Flat
// 
//    Rev 1.12   Mar 10 2011 15:30:32   jankovii
// IN 2458927 - P0181943 - SWIFT XML - Split Commission Exchanges
// 
//    Rev 1.11   Mar 04 2011 12:10:04   jankovii
// PET181943 FN01 - XMLPhase 2
// 
//    Rev 1.10   Jul 07 2005 17:52:54   popescu
// Incident# 350901 - removed split commissions when not needed, do not call split commissions when trade is roa applicable, trans type is transfer and side of the splits is To
// 
//    Rev 1.9   Jul 04 2005 19:05:26   popescu
// Incident # 347073 - split commission is charged on the To side for environments where ROA is applicable.
// 
//    Rev 1.8   Mar 03 2005 08:13:52   popescu
// PET 1117/06 added restore functionality for fees, when modifying a pending trade, even if the TransFee table is not populated
// 
//    Rev 1.7   Feb 22 2005 14:05:00   popescu
// Incident #249310, validation of split commissions should be done against the initial total value, rather then 0 amount
// 
//    Rev 1.6   Jan 31 2005 10:05:22   popescu
// PTS 10038324, set charge option field to read only, there is no set-up for it.
// 
//    Rev 1.5   Jan 28 2005 11:07:28   popescu
// PTS 10038324, fees display issues
// 
//    Rev 1.4   Jan 28 2005 06:57:46   aguilaam
// PTS 10038324, fees display issues
// 
//    Rev 1.3   Jan 21 2005 16:55:40   popescu
// PTS 10038132, not show the fees if from fund/ and class are not entered
// 
//    Rev 1.2   Dec 08 2004 22:08:38   popescu
// PET 1117/06, more fees
// 
//    Rev 1.1   Nov 18 2004 13:44:48   YINGBAOL
// PET1117:  performance tunning 
// 
//    Rev 1.0   Nov 17 2004 15:55:54   popescu
// Initial revision.
// 
//    Rev 1.2   Nov 15 2004 16:22:30   popescu
// PET 1117/06, more synch to .NET changes
// 
//    Rev 1.0   Nov 10 2004 09:31:14   popescu
// Initial revision.
// 
//    Rev 1.0   Nov 06 2004 00:35:04   popescu
// Initial revision.
// 
//    Rev 1.0   Nov 04 2004 11:03:16   popescu
// Initial revision.
// 
 */