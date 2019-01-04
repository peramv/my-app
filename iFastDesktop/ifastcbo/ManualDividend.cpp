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
//    Copyright 2003
//
//
//******************************************************************************
//
// ^FILE   : ManualDividend.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : ManualDividend
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "manualdividend.hpp"

#include "dstcommonfunction.hpp"
#include "mfaccount.hpp"
#include "mfaccountholdinglist.hpp"
#include "AMSMstrList.hpp"
#include "amsmstrinfo.hpp"
#include "funddetail.hpp"

namespace CND
{
   extern const long ERR_FUND_UNIT_PRICE_NOT_AVAILABLE;
   extern const long ERR_AMOUNT_MUST_BE_GREATER_THAN_ZERO;
   extern const long ERR_MANUAL_DIVIDEND_NOT_ALLOWED;
   extern const long ERR_ACCT_TERMINATED;
   extern const long ERR_TOFUND_SAME_OR_CASH;
   extern const long ERR_ACCT_INACTIVE;
   extern const long ERR_TRADE_DATE_FUTURE_DATED;
   extern const long ERR_ACCT_NO_HOLDINGS;
   extern const long ERR_ACCT_NO_HOLDINGS_FOR_FUND;
   extern const long ERR_ADDRESS_CODE_INVALID;
   extern const long WARN_INVALID_FUND_NUMBER;
   extern const long ERR_EXCLUDE_IS_NOT_ALLOWED;
   extern const long ERR_RECEIVING_ACCT_AMS_MODEL_NOT_CONTAIN_THIS_FUND_CLASS_AS_CHILD;
   extern const long WARN_RECEIVING_ACCT_AMS_MODEL_NOT_CONTAIN_THIS_FUND_CLASS_AS_CHILD;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId ManualDividendPayType;
   extern CLASS_IMPORT const BFTextFieldId ProcessDiv;
   extern CLASS_IMPORT const BFTextFieldId AcctStatus;
   extern CLASS_IMPORT const BFTextFieldId MinToFundAmount;
   extern CLASS_IMPORT const BFTextFieldId MinFromFundAmount;
   extern CLASS_IMPORT const BFTextFieldId DuplicateTrade;
   extern CLASS_IMPORT const BFTextFieldId AmountPrecision;
   extern CLASS_IMPORT const BFTextFieldId AcctableTradeDate;
   extern CLASS_IMPORT const BFTextFieldId FromFundClass;
   extern CLASS_IMPORT const BFTextFieldId ToFundClass;
   extern CLASS_IMPORT const BFTextFieldId FromToFundClass;
   extern CLASS_IMPORT const BFTextFieldId ToFundNumber;
   extern CLASS_IMPORT const BFTextFieldId FromFundNumber;
   extern CLASS_IMPORT const BFTextFieldId ESGSettle;
   extern CLASS_IMPORT const BFTextFieldId ManualTradesTransType;
   extern CLASS_IMPORT const BFTextFieldId AMSCode;
   extern CLASS_IMPORT const BFTextFieldId TradeFileProcessorDefault;
}

namespace UAF
{
/*
   extern CLASS_IMPORT I_CHAR * const MANUAL_DIVIDEND;
*/
}
namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME = I_( "ManualDividend" );
   const I_CHAR * const FUND_CODE_CASH = I_("CASH");
   const I_CHAR * const ACCT_STATUS_CODE_TERMINATED = I_("30");
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const DIVIDEND;
   extern CLASS_IMPORT I_CHAR * const MANUAL_MGMT_FEE_REBATE;
} 

namespace PAYTYPE
{
   extern CLASS_IMPORT I_CHAR * const SYSTEM_CHEQUE;
   extern CLASS_IMPORT I_CHAR * const SUPPRESS;
   extern CLASS_IMPORT I_CHAR * const MANUAL_CHEQUE;
   extern CLASS_IMPORT I_CHAR * const EFT;
} 

namespace IFASTERR
{
    extern CLASS_IMPORT I_CHAR * const RECEIVING_ACCT_AMS_MODEL_NOT_CONTAIN_THIS_FUND_CLASS_AS_CHILD;
}


//******************************************************************************
ManualDividend::ManualDividend (BFAbstractCBO &parent) : Trade (parent)
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
}

//******************************************************************************
ManualDividend::~ManualDividend()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}     

//******************************************************************************
SEVERITY ManualDividend::doInit (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doInit"));

   setFieldSubstituteValues (ifds::TradesTransType, idDataGroup, ifds::ManualTradesTransType);
   setFieldNoValidate ( ifds::TradesTransType, 
                        TRADETYPE::DIVIDEND, 
                        idDataGroup, 
                        false);
   return GETCURRENTHIGHESTSEVERITY ();
}

//based on the transaction type set in the previous method, reads various defaults
//******************************************************************************
SEVERITY ManualDividend::transTypeRelatedChanges (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("transTypeRelatedChanges"));
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY ManualDividend::payMethodPropertyChanges (const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("payMethodPropertyChanges"));
	if(DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA)
	{
		setFieldNoValidate (ifds::PayMethod, I_("EFT"), idDataGroup, false, 
							true, 
							true, //notify
							false); //no related changes

		DString fileProcessorList;
		getWorkSession().getOption (ifds::TradeFileProcessorDefault, 
									fileProcessorList, 
									BF::HOST, 
									false);
		setFieldNoValidate (ifds::ACHProcessor, fileProcessorList, idDataGroup, false, 
							true, 
							true, //notify
							false); //no related changes
	}
	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void ManualDividend::getFundAndClassFieldIds ( BFFieldId &fundCodeFieldId, 
                                               BFFieldId &classCodeFieldId)
{
   fundCodeFieldId = ifds::FromFund;
   classCodeFieldId = ifds::FromClass;
}

//******************************************************************************
void ManualDividend::getAccountFieldId (BFFieldId &accountFieldId)
{
   accountFieldId = ifds::AccountNum;
}

//******************************************************************************
bool ManualDividend::supportsAllocations (const BFDataGroupId &idDataGroup)
{
   return false;
}

//******************************************************************************
bool ManualDividend::supportsFromAllocations (const BFDataGroupId &idDataGroup)
{
   return false;
}

//******************************************************************************
inline bool ManualDividend::isWireSupported (const BFDataGroupId &idDataGroup)
{
	return false;
}

//******************************************************************************
SEVERITY ManualDividend::canAccountTrade ( MFAccount *pMFAccount, 
                                           const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("canTradeAccount"));
//calls base class   
   if (Trade::canAccountTrade (pMFAccount, idDataGroup) <= WARNING)
   {
// check if terminated or inactive
      DString acctStatus;

      pMFAccount->getField (ifds::AcctStatus, acctStatus, idDataGroup, false);
      if (acctStatus == ACCT_STATUS_CODE_TERMINATED)
      {
         ADDCONDITIONFROMFILE (CND::ERR_ACCT_TERMINATED);
      }
      else if (acctStatus > ACCT_STATUS_CODE_TERMINATED)
      {
         ADDCONDITIONFROMFILE (CND::ERR_ACCT_INACTIVE);
      }
      else
      {
         // Check for holdings
         MFAccountHoldingList *pAccountHoldingList = NULL;

         if ( getAccountHoldings ( pAccountHoldingList,
                                  idDataGroup) <= WARNING &&
              pAccountHoldingList)
         {
            BFObjIter iter (*pAccountHoldingList, idDataGroup, false);

            if (iter.getNumberOfItemsInList() == 0)
            {
// Account has no holdings.
               ADDCONDITIONFROMFILE (CND::ERR_ACCT_NO_HOLDINGS); 
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void ManualDividend::doInitWithDefaultValues (const BFDataGroupId& idDataGroup)
{
   Trade::doInitWithDefaultValues (idDataGroup);

//certain fields are not required...
   setFieldRequired (ifds::TradesPayType, idDataGroup, false);
   setFieldRequired (ifds::Broker, idDataGroup, false);
   setFieldRequired (ifds::Branch, idDataGroup, false);
   setFieldRequired (ifds::SlsrepCode, idDataGroup, false);
//certain fields are required
   setFieldRequired (ifds::Amount, idDataGroup, true);
   setFieldValid (ifds::Amount, idDataGroup, false); //invalid
   setFieldRequired (ifds::FromFund, idDataGroup, true);
   setFieldRequired (ifds::FromClass, idDataGroup, true);
   setFieldRequired (ifds::ToFund, idDataGroup, true);
   setFieldRequired (ifds::ToClass, idDataGroup, true);
   
   setFieldNoValidate (ifds::AmtType, I_("D"), idDataGroup, false);
   setFieldReadOnly (ifds::AmtType, idDataGroup, true);
   setFieldNoValidate (ifds::OrderType, I_("N"), idDataGroup, false); //direct  
   setFieldValid (ifds::SettleDate, idDataGroup, false); //invalid
   setFieldValid (ifds::SettleCurrency, idDataGroup, false); //invalid
	setFieldNoValidate (ifds::ESGSettle, I_("In"), idDataGroup, false);
	payMethodPropertyChanges (idDataGroup);
    DString dstrTradesTransType;
    getField(ifds::TradesTransType, dstrTradesTransType, idDataGroup);

    if (dstrTradesTransType == TRADETYPE::MANUAL_MGMT_FEE_REBATE)
    {
        setFieldSubstituteValues (ifds::TradesPayType, idDataGroup, ifds::ManualDividendPayType);
    }
    else
    {
        DString subListTradesPayType;

        subListTradesPayType = removeItemFromSubtList(ifds::ManualDividendPayType, PAYTYPE::EFT, idDataGroup);
        subListTradesPayType = removeItemFromSubtList(subListTradesPayType, PAYTYPE::MANUAL_CHEQUE);
        setFieldAllSubstituteValues(ifds::TradesPayType, idDataGroup, subListTradesPayType);
    }
}


//******************************************************************************
SEVERITY ManualDividend::doApplyRelatedChanges ( const BFFieldId &idField, 
                                                 const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doApplyRelatedChanges"));
   if (idField == ifds::AccountNum)
   {
		setFieldReadOnly (ifds::TradesTransType, idDataGroup, true);
		setFieldReadOnly (ifds::AccountNum, idDataGroup, true);
		setFieldReadOnly (ifds::ToFund, idDataGroup, false);
		setFieldReadOnly (ifds::ToClass, idDataGroup, false);
		setFieldReadOnly (ifds::ToFundNumber, idDataGroup, false);
	    //certain fields cannot be modified
		setFieldReadOnly (ifds::SettleCurrency, idDataGroup, true);
	}
   else if (idField == ifds::TradesTransType)
   {
   		setFieldRequired (ifds::MFPayment, idDataGroup, false);
		setFieldValid (ifds::MFPayment, idDataGroup, true);
   }
   else if (idField == ifds::TradesPayType)
   {
      Trade::doApplyRelatedChanges (idField, idDataGroup);

// ESG Settlement
		bool bUpdateESGSettle = false;
		DString toFund, 
         payType;

      getField (ifds::ToFund, toFund, idDataGroup, false);
		getField (ifds::TradesPayType, payType, idDataGroup, false);
		bool bIsToFundCash = const_cast <DString&> (toFund).stripAll().upperCase() == FUND_CODE_CASH;
		bUpdateESGSettle = payType == I_("S") && bIsToFundCash && Trade::isCASHSettleESGElig (idDataGroup);

		setFieldReadOnly (ifds::ESGSettle, idDataGroup, !bUpdateESGSettle);
		setFieldValid (ifds::ESGSettle, idDataGroup, false );
		payMethodPropertyChanges(idDataGroup);
   }
	else if (idField == ifds::AddrCode)
   {
		setFieldValid (ifds::ESGSettle, idDataGroup, false);
	}
   else if ( idField == ifds::FromFund || 
             idField == ifds::FromClass ||
				 idField == ifds::FromFundNumber)
   {
      DString fundCode,
         classCode,
			fundNumber;

		if (idField == ifds::FromFundNumber)
		{
			getField (ifds::FromFundNumber, fundNumber, idDataGroup, false);

			if (!fundNumber.empty())
			{
				if (!getWorkSession ().GetFundClassCode (fundNumber, fundCode, classCode))
				{
					ADDCONDITIONFROMFILE (CND::WARN_INVALID_FUND_NUMBER);
				}
				else
				{
					DString fundCurrency;

					setFieldNoValidate ( ifds::FromFund, fundCode, idDataGroup, false, false, true, false);
					setFieldNoValidate ( ifds::FromClass, classCode, idDataGroup, false, false, true, false);
					
					Trade::fromFundClassRelatedChanges (fundCode, classCode, idDataGroup);

					if ( !fundCode.empty() &&
							!classCode.empty() )
					{
						getFundField (fundCode, classCode, ifds::Currency, fundCurrency);
						setFieldNoValidate ( ifds::SettleCurrency, fundCurrency, idDataGroup, false, 
													false, //not valid
													true);  //side effect

					}
				}
			}      
      }	
		else
		{
			getField (ifds::FromFund, fundCode, idDataGroup, false);
			getField (ifds::FromClass, classCode, idDataGroup, false);

			Trade::fromFundClassRelatedChanges (fundCode, classCode, idDataGroup);
			if ( !fundCode.empty() &&
				!classCode.empty())
			{
				DString fundCurrency;

				getFundField (fundCode, classCode, ifds::Currency, fundCurrency);
				setFieldNoValidate ( ifds::SettleCurrency, fundCurrency, idDataGroup, false, 
											false, //not valid
											true);  //side effect
				getWorkSession ().GetFundNumber (fundCode, classCode, fundNumber);
				setFieldNoValidate ( ifds::FromFundNumber, fundNumber, idDataGroup, false, true, true, false);

			}
		}
      setFieldValid (ifds::MinFromFundAmount, idDataGroup, false);  // to force validation
      setFieldValid (ifds::EffectiveDate, idDataGroup, false);      // to force validation  
	  payMethodPropertyChanges(idDataGroup);
   }

   else if ( idField == ifds::ToFund || 
             idField == ifds::ToClass ||
				 idField == ifds::ToFundNumber )
   {
      setFieldValid (ifds::MinToFundAmount, idDataGroup, false);    // to force validation
      setFieldValid (ifds::EffectiveDate, idDataGroup, false);      // to force validation  

		DString toFundNumber, toFund, toClass;

		if (idField == ifds::ToFundNumber)
		{		
			getField (ifds::ToFundNumber, toFundNumber, idDataGroup, false);

			if (!toFundNumber.empty())
			{
				if (!getWorkSession ().GetFundClassCode (toFundNumber, toFund, toClass))
				{
					ADDCONDITIONFROMFILE (CND::WARN_INVALID_FUND_NUMBER);
				}
				else
				{
					setField(ifds::ToFund, toFund, idDataGroup, false, true);
                    setField(ifds::ToClass, toClass, idDataGroup, false, true);

	                Trade::toFundClassRelatedChanges (toFund, toClass, idDataGroup);

					// disable pay type field
					setFieldNoValidate (ifds::TradesPayType, NULL_STRING, idDataGroup, false, false, false);
					setFieldNoValidate (ifds::SuppressCode, NULL_STRING, idDataGroup, false);
					setFieldNoValidate (ifds::AddrCode, NULL_STRING, idDataGroup, false);
					setFieldRequired (ifds::SuppressCode, idDataGroup, false);
					setFieldRequired (ifds::AddrCode, idDataGroup, false);
					setFieldValid (ifds::SuppressCode, idDataGroup, true);
					setFieldValid (ifds::AddrCode, idDataGroup, true);
				}
			}
		}

		else 
      {
         
         getField (ifds::ToFund, toFund, idDataGroup, false);
         bool bIsToFundCash = toFund.stripAll().upperCase() == FUND_CODE_CASH;

         setFieldRequired (ifds::ToClass, idDataGroup, !bIsToFundCash);
         setFieldValid (ifds::ToClass, idDataGroup, bIsToFundCash);
         setFieldReadOnly (ifds::ToClass, idDataGroup, bIsToFundCash);
         setFieldRequired (ifds::TradesPayType, idDataGroup, bIsToFundCash);
         setFieldValid (ifds::TradesPayType, idDataGroup, !bIsToFundCash);
			//setFieldReadOnly (ifds::ESGSettle, idDataGroup, !bIsToFundCash);
         if (bIsToFundCash)
         {
            // Clear Class field
            setFieldNoValidate (ifds::ToClass, NULL_STRING, idDataGroup, false, true, true, false);
            setFieldNoValidate (ifds::ToFundNumber, NULL_STRING, idDataGroup, false, true, true, false);
         }
         else
         {
            getField (ifds::ToFund, toFund, idDataGroup, false);
            getField (ifds::ToClass, toClass, idDataGroup, false);
            Trade::toFundClassRelatedChanges (toFund, toClass, idDataGroup);
            // disable pay type field
            setFieldNoValidate (ifds::TradesPayType, NULL_STRING, idDataGroup, false, false, false);
            setFieldNoValidate (ifds::SuppressCode, NULL_STRING, idDataGroup, false);
            setFieldNoValidate (ifds::AddrCode, NULL_STRING, idDataGroup, false);
            setFieldRequired (ifds::SuppressCode, idDataGroup, false);
            setFieldRequired (ifds::AddrCode, idDataGroup, false);
            setFieldValid (ifds::SuppressCode, idDataGroup, true);
            setFieldValid (ifds::AddrCode, idDataGroup, true);

		      getWorkSession ().GetFundNumber (toFund, toClass, toFundNumber);
		      setFieldNoValidate ( ifds::ToFundNumber, toFundNumber, idDataGroup, false, true, true, false);

         }
      }
		payMethodPropertyChanges(idDataGroup);
   }

 
   else if (idField == ifds::OrderType)
   {
      Trade::orderTypeRelatedChanges (idDataGroup);
   }
   else if ( idField == ifds::EffectiveDate ||
             idField == ifds::SettleCurrency || 
             idField == ifds::AmtType || 
             idField == ifds::MinFromFundAmount ||
             idField == ifds::Accountable || 
             idField == ifds::BackDatedReason)
   {
      Trade::doApplyRelatedChanges (idField, idDataGroup);
	  payMethodPropertyChanges(idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ManualDividend::doValidateField ( const BFFieldId &idField, 
                                           const DString &strValue, 
                                           const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_( "doValidateField"));

   if (idField == ifds::EffectiveDate)
   {
      if ( DSTCommonFunctions::CompareDates (strValue, _currentBusinessDate) == 
           DSTCommonFunctions::SECOND_EARLIER)
      {
         ADDCONDITIONFROMFILE (CND::ERR_TRADE_DATE_FUTURE_DATED);
      }
	  else
	  {
		 /* 
			DSK needs to call 135 when users modify trade date but we don't have to validate trade date 
			of Manual Dividend same as trade entry, we just need to call 135 to get the correct values 
			before calling 135 in mode 2 (settlement date). 
		 */
		 validateDate ( I_("4"),		       /* Trade date validation type */
						ifds::EffectiveDate, 
						strValue, 
						idDataGroup );
	  }
   }
   else if ( idField == ifds::AccountNum        ||
             idField == ifds::FromClass         ||
             idField == ifds::ToClass           ||
             idField == ifds::AmountPrecision   ||
             idField == ifds::AddrCode          ||
             idField == ifds::MinToFundAmount   ||
             idField == ifds::MinFromFundAmount ||
             idField == ifds::DuplicateTrade    ||
             idField == ifds::Accountable       ||
             idField == ifds::BackDatedReason   ||
             idField == ifds::AcctableTradeDate ||
             idField == ifds::SettleCurrency    ||
             idField == ifds::FromFundClass     ||
             idField == ifds::ToFundClass       ||
             idField == ifds::FromToFundClass   ||
             idField == ifds::ESGSettle         ||
             idField == ifds::Amount)
   {
      Trade::doValidateField (idField, strValue, idDataGroup);
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************** 
SEVERITY ManualDividend::validateMasterActAMS(const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateMasterActAMS"));

    DString dstrAccountNum, dstrTradeDate;
    MFAccount *pMFAccount = NULL;
    FundDetail *pFundDetailTo = NULL;
    AMSMstrList *pAMSMstrList = NULL;
    AmsMstrInfo *pAMSMstrInfo = NULL;

    getField(ifds::AccountNum, dstrAccountNum, idDataGroup);
    getField(ifds::EffectiveDate, dstrTradeDate, idDataGroup, false);

    if (getWorkSession().getMFAccount(idDataGroup, dstrAccountNum, pMFAccount) <= WARNING && pMFAccount &&
        pMFAccount->isAMSAccount(idDataGroup) &&
        pMFAccount->getAMSMstrList(pAMSMstrList, idDataGroup,  dstrTradeDate) <= WARNING && pAMSMstrList)
    {
        DString dstrAcctFromAMSCode, dstrAcctToAMSCode, dstrTradeDate/*, dstrFromFund, dstrFromClass*/;
        DString dstrToFund, dstrToClass;

        pMFAccount->getField(ifds::AMSCode, dstrAcctToAMSCode, idDataGroup);

        getField(ifds::ToFund, dstrToFund, idDataGroup);
        getField(ifds::ToClass, dstrToClass, idDataGroup);

        pAMSMstrList->getAMSMstrInfo(I_("RB"), dstrAcctToAMSCode, dstrTradeDate, pAMSMstrInfo, idDataGroup);

        if (getWorkSession().getFundDetail(dstrToFund, dstrToClass, idDataGroup, pFundDetailTo) && pFundDetailTo)
        {
            if (pFundDetailTo->isAMSChildFund(idDataGroup) &&
                !pAMSMstrInfo->isFundInAMS(dstrToFund, dstrToClass, idDataGroup))
            {
                getErrMsg(IFASTERR::RECEIVING_ACCT_AMS_MODEL_NOT_CONTAIN_THIS_FUND_CLASS_AS_CHILD,
                          CND::ERR_RECEIVING_ACCT_AMS_MODEL_NOT_CONTAIN_THIS_FUND_CLASS_AS_CHILD,
                          CND::WARN_RECEIVING_ACCT_AMS_MODEL_NOT_CONTAIN_THIS_FUND_CLASS_AS_CHILD,
                          idDataGroup);
            }
        }
    }

    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool ManualDividend::isManualDividendAllowed ( const DString &fundCode, 
                                               const DString &classCode, 
                                               const BFDataGroupId &idDataGroup)
{
   DString allowManDiv;
   
   getFundField (fundCode, classCode, ifds::ProcessDiv, allowManDiv);
   return allowManDiv == I_("2") || allowManDiv == I_("3");
}

//******************************************************************************
bool ManualDividend::isShareholderAddressNeeded (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("isShareholderAddressNeeded"));
   DString payType;

   getField (ifds::TradesPayType, payType, idDataGroup, false);
   return payType == PAYTYPE::SYSTEM_CHEQUE || payType == PAYTYPE::MANUAL_CHEQUE;
}

//****************************************************************************** 
SEVERITY ManualDividend::validateFundClass ( const DString &fundCode, 
                                             const DString &classCode, 
                                             const DString &accountNum, 
                                             const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateFundClass"));

   if (!fundCode.empty() && !classCode.empty())
   {
      if (isManualDividendAllowed (fundCode, classCode, idDataGroup))
      {
         validateEUSDBackdates( fundCode,
                                classCode,
                                accountNum,
                                idDataGroup ); 

         MFAccountHoldingList *pMFAccountHoldingList = NULL;
         if ( getAccountHoldings (pMFAccountHoldingList, idDataGroup) <= WARNING &&
              pMFAccountHoldingList)
         {
            if (pMFAccountHoldingList->isFundInHoldings ( const_cast <DString&>(fundCode), 
                                                          const_cast <DString&>(classCode), 
                                                          idDataGroup))
            {
               DString tradeDate;
               
               getField (ifds::EffectiveDate, tradeDate, idDataGroup, false);
               double dUnitPrice = getUnitPrice ( fundCode, 
                                                  classCode, 
                                                  tradeDate, 
                                                  tradeDate, 
                                                  idDataGroup,
                                                  I_(""),   //  transType
                                                  I_("N"),  //  PrevDatePressed
                                                  I_("N")); //  NextDatePresed

               if (dUnitPrice == 0.0)
               {
// Unit price is not available for this fund.
                  ADDCONDITIONFROMFILE (CND::ERR_FUND_UNIT_PRICE_NOT_AVAILABLE);
               }
            }
            else
            {
// Account has no holdings for this fund.
               ADDCONDITIONFROMFILE (CND::ERR_ACCT_NO_HOLDINGS_FOR_FUND); 
            }
         }
      }
      else
      {
// Manual dividend posting for this fund is not allowed.
         ADDCONDITIONFROMFILE (CND::ERR_MANUAL_DIVIDEND_NOT_ALLOWED);
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY ManualDividend::validateToFundClass ( const DString &toFund, 
                                               const DString &toClass, 
                                               const DString &accountNum, 
                                               const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateToFundClass"));

   bool bIsToFundCash = const_cast <DString&> (toFund).stripAll().upperCase() == FUND_CODE_CASH;

   if (!bIsToFundCash)
   {  
      if (!toFund.empty() && !toClass.empty())
      {
         DString tradeDate;

         getField (ifds::EffectiveDate, tradeDate, idDataGroup, false);
         double dUnitPrice = getUnitPrice ( toFund, 
                                            toClass, 
                                            tradeDate, 
                                            tradeDate, 
                                            idDataGroup, 
                                            I_(""),   // transType
                                            I_("N"),  //PrevDatePressed
                                            I_("N")); //NextDatePresed

         if (dUnitPrice == 0.0)
         {
// Unit price is not available for this fund.
            ADDCONDITIONFROMFILE (CND::ERR_FUND_UNIT_PRICE_NOT_AVAILABLE);
         }
      }
   }

   validateMasterActAMS(idDataGroup);
   validateToFundClassAgainstFundEligible(toFund, toClass, idDataGroup);
   

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY ManualDividend::validateToFundClassAgainstFundEligible(const DString &fundCode,
                                                                const DString &classCode,
                                                                const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateToFundClassAgainstFundEligible"));

    DString dstrAccountNum;
    MFAccount *pMFAccount = NULL;
    getField(ifds::AccountNum, dstrAccountNum, idDataGroup);

    if (getWorkSession().getMFAccount(idDataGroup, dstrAccountNum, pMFAccount) <= WARNING && pMFAccount)
    {
        pMFAccount->validateToFundClassAgainstFundEligible(fundCode, classCode, idDataGroup);
    }

    return GETHIGHESTSEVERITY();
}


//******************************************************************************
SEVERITY ManualDividend::validateFromToFundClass ( const DString &fromFund,
                                                   const DString &fromClass,
                                                   const DString &toFund,
                                                   const DString &toClass,
                                                   const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateFromToFundClass"));

   bool bIsToFundCash = const_cast <DString&> (toFund).stripAll().upperCase() == FUND_CODE_CASH;

   // Check to make sure that To Fund/Class is the same as From Fund/Class since it's not CASH
   if (!bIsToFundCash)
   {
      if (fromFund != toFund || fromClass != toClass)
      {
   //To Fund must be the same as From Fund or CASH.
         ADDCONDITIONFROMFILE (CND::ERR_TOFUND_SAME_OR_CASH);
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//****************************************************************************** 
SEVERITY ManualDividend::validateESGSettle (const DString &strValue, const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateESGSettle")); 

   if (strValue == I_("Ex"))
   {
      DString dstrPayType, dstrToFund, dstrAddressCode;

      getField (ifds::TradesPayType, dstrPayType, idDataGroup, false);
      getField (ifds::AddrCode, dstrAddressCode, idDataGroup, false);
      getField (ifds::ToFund, dstrToFund, idDataGroup, false);
      if ( !( ( allowESGSettleForNominee (idDataGroup )  || 
            allowESGSettleForIntermediary (idDataGroup)) &&
            dstrPayType     == I_("S")  &&
            dstrAddressCode == I_("01") &&
            dstrToFund      == I_("CASH")))
      {
         ADDCONDITIONFROMFILE ( CND::ERR_EXCLUDE_IS_NOT_ALLOWED);
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ManualDividend.cpp-arc  $
// 
//    Rev 1.47   17 Aug 2009 10:38:12   popescu
// IN#1686644 - R92_PET5517_FN94D - cannot save manual FC in Desktop - revised the code a little bit
// 
//    Rev 1.46   Aug 17 2009 08:35:10   dchatcha
// IN#1686644 - R92_PET5517_FN94D - cannot save manual FC in Desktop.
// 
//    Rev 1.45   Jan 21 2009 12:01:30   jankovii
// PET5517_FN94_Foreign Exchange Allocated Capital Gains
// 
//    Rev 1.44   Sep 16 2007 15:40:56   jankovii
// IN #990336 - User is unable to process manual/adhoc MFR trades.
// 
//    Rev 1.43   Sep 06 2007 17:21:06   popescu
// GAP 18 - added manual management fee rebate to manual dividend screen
// 
//    Rev 1.42   Nov 16 2006 11:11:36   popescu
// PET 2252. FN01 - mgmt fee rebate
// 
//    Rev 1.41   Mar 06 2006 14:28:26   popescu
// PET1334 - FN01 -- Added logic for ESGSettle enhancement - beautify during code review
// 
//    Rev 1.40   Mar 01 2006 13:59:06   ZHANGCEL
// PET1334 - FN01 -- Added logic for ESGSettle enhancement
// 
//    Rev 1.39   Dec 13 2005 16:59:14   zhengcon
// Incident #491607 -- fixed problem for inputting the fund number
// 
//    Rev 1.38   Oct 07 2005 16:13:02   AGUILAAM
// IN 399479: subsequent fix, set currency when user inputs fund number (instead of fund/class)
// 
//    Rev 1.37   Sep 13 2005 17:36:56   AGUILAAM
// IN 399479 - get fund number for manual dividend
// 
//    Rev 1.36   Aug 18 2005 16:49:38   popescu
// Incident 383839 - fixed 'Unable to post backdated manual dividend'
// 
//    Rev 1.35   Jul 07 2005 11:34:42   porteanm
// PET1171 EUSD 1B - Call validateEUSDBackDates().
// 
//    Rev 1.34   May 27 2005 10:17:16   popescu
// Incident # 319459 - fixed the Manual Dividend reset issue - also used WorkSessionTradesList for manual dividends; use the TradesProcess instead of ManualDividendProcess
// 
//    Rev 1.33   May 20 2005 17:25:22   popescu
// PET 1117/08 - called init rather the doinit - in reset
// 
//    Rev 1.32   May 20 2005 16:02:22   popescu
// PET 1117/08 - called the base class - to keep existing functionality 
// 
//    Rev 1.31   May 20 2005 14:09:36   popescu
// PET 1117/08 fixed reset of the trans type to 'ED'
// 
//    Rev 1.30   Feb 15 2005 21:06:46   hernando
// MAGIC 234429 - Ensure ToFund is CASH besides System Cheque in validating the Address Code.
// 
//    Rev 1.29   Feb 15 2005 16:30:20   hernando
// PTS 10038693 (MAGIC 243429) - Ensure TradePayType is a System Cheque when validating Address Code.
// 
//    Rev 1.28   Jan 26 2005 17:42:10   hernando
// PTS10034582 - Set TradesPayType to required when ToFund is Cash and not required otherwise.
// 
//    Rev 1.27   Jan 26 2005 11:49:22   hernando
// PTS10034582 - Changed TradesPayType, Branch, SlsrepCode, and Broker to NOT Required.
// 
//    Rev 1.26   Dec 14 2004 15:01:48   popescu
// some of the cross-edits have been renamed
// 
//    Rev 1.25   Dec 09 2004 17:33:38   hernando
// PET910 - Returned validateFundCodeCash.
// 
//    Rev 1.24   Nov 29 2004 20:30:18   popescu
// PET 1117/06/56 fees/trades processing
// 
//    Rev 1.23   Nov 22 2004 13:09:04   popescu
// PET 1117/56. fees processing
// 
//    Rev 1.22   Nov 14 2004 14:49:18   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.21   Nov 06 2004 00:41:40   popescu
// PET 1117/06, synch changes
// 
//    Rev 1.20   Aug 24 2004 17:21:44   popescu
// PTS 10033378, call stack loop, during manual post dividend entry
// 
//    Rev 1.19   May 26 2004 22:58:34   popescu
// PET 985, FN 01, LSIF trade entry
// 
//    Rev 1.18   May 20 2004 14:16:58   popescu
// PTS 10026123, address 01, for nominee and intermediary accounts by tax type and reg address code
// 
//    Rev 1.17   May 13 2004 21:06:12   popescu
// PET 985, FN 01, LSIF Trade entry
// 
//    Rev 1.16   May 10 2004 20:28:06   popescu
// PET 985, FN 01, LSIF Trade Entry
// 
//    Rev 1.15   May 09 2004 20:10:10   popescu
// PET 985, FN 01, LSIF Trade Entry
// 
//    Rev 1.14   Apr 12 2004 13:44:02   HERNANDO
// PTS10029071 - Check for Unit Price for From Fund.
// 
//    Rev 1.13   Jan 16 2004 15:00:12   HERNANDO
// PTS10025436 - Modified getUnitPrice in Trade so that PrevDatePressed and NextDatePressed is passed.  Added message as a pre-confirmation on 'OK' and before validation.
// 
//    Rev 1.12   Oct 16 2003 10:22:16   YINGBAOL
// check field "ProcessDiv" instead of "AllowManDiv"
// 
//    Rev 1.11   Oct 07 2003 17:30:34   HERNANDO
// PET859 FN12 - Expecting '1', '2', or '3' for AllowManDiv.  Changed from Yes/No.
// 
//    Rev 1.10   Jul 21 2003 16:37:52   HERNANDO
// Changed call to retrieve MFAccount -- no longer creates invalid accounts.  Refreshed AddrCode and Suppress Code when Pay Type changes.
// 
//    Rev 1.9   Jul 16 2003 15:21:42   HERNANDO
// Another change regarding the AddrCode flag.
// 
//    Rev 1.8   Jul 16 2003 14:47:12   HERNANDO
// 3 Changes - AddrCode/Suppress Code flags change, Trade Date/AddrCode validation changed (will ignore if To Fund is Cash), and To Fund call to Trade moved (will only call if Fund, not CASH).
// 
//    Rev 1.7   Jul 11 2003 13:50:02   YINGBAOL
// PTS10019497 add changeSettleCurrencyByFundClass
// 
//    Rev 1.6   Jul 10 2003 16:45:32   HERNANDO
// Added ValidateAddressCodeEffectiveDate.  Switched fn. block from ValidateAddressCode to ValidateAddressCodeEffectiveDate.  Set Currency to read only. 
// 
//    Rev 1.5   Jul 10 2003 10:54:26   HERNANDO
// PTS 10019516 - Set Settlement Date to Read Only.
// 
//    Rev 1.4   Jul 08 2003 17:08:50   HERNANDO
// PTS 10018768 - Check Account for holdings and check Account holdings for from Fund and Class.
// 
//    Rev 1.3   Jun 30 2003 16:31:32   popescu
// moved the ifast_fields include in the .cpp file
// 
//    Rev 1.2   Jun 26 2003 17:47:36   HERNANDO
// PTS 10018774/10018739/10018741/10018742/10018763/10018773/10018738/10018856.
// 
//    Rev 1.1   May 30 2003 17:36:46   HERNANDO
// Several changes affecting the behaviour and relationship between fields.
// 
//    Rev 1.0   May 22 2003 16:51:00   HERNANDO
// Initial revision.
// 
// 
*/
