//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2000 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : Rollover.cpp
// ^AUTHOR : Serban Popescu   
// ^DATE   : September, 2004
//
// ^CLASS    : Rollover - 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "rollover.hpp"

#include "amsmstrinfo.hpp"
#include "fundmasterlist.hpp"
#include "lsifrolloverruleslist.hpp"
#include "mfaccount.hpp"
#include "mgmtco.hpp"
#include "taxtyperule.hpp"

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME = I_ ("Rollover");
}

namespace ifds
{
//account fields
   extern CLASS_IMPORT const BFTextFieldId TaxType;
   extern CLASS_IMPORT const BFTextFieldId BrokerCode;
   extern CLASS_IMPORT const BFTextFieldId BranchCode;
   extern CLASS_IMPORT const BFTextFieldId Slsrep;
//fund fields
   extern CLASS_IMPORT const BFTextFieldId ToFundNumber;
   extern CLASS_IMPORT const BFTextFieldId Currency;
//attributes grid
   extern CLASS_IMPORT const BFTextFieldId TradeAttributesFields;
   extern CLASS_IMPORT const BFTextFieldId TransferAttributes;
//substitution sets
   extern CLASS_IMPORT const BFTextFieldId AmountTypeRollover;
//cross-edits
   extern CLASS_IMPORT const BFTextFieldId NetOrdType;
   extern CLASS_IMPORT const BFTextFieldId ToFundClass;
}

namespace CND
{
   extern const long ERR_ROLLOVER_NOT_SAME_ACCOUNT_OWNER;
   extern const long ERR_FUND_NOT_LSIF;
   extern const long ERR_ROLLOVER_SAME_CURRENCY_FUNDS;
   extern const long ERR_ROLLOVER_NOT_ALLOWED;
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const ROLLOVER;
   extern CLASS_IMPORT I_CHAR * const PURCHASE;
   extern CLASS_IMPORT I_CHAR * const REDEMPTION;
}

namespace PAYTYPE
{
   extern CLASS_IMPORT I_CHAR * const SUPPRESS;
} 


//******************************************************************************
Rollover::Rollover (BFAbstractCBO &parent) : Redemption (parent), Purchase (parent), Trade (parent)
{
   TRACE_CONSTRUCTOR ( CLASSNAME, 
                       NULL_STRING);
}


//******************************************************************************
Rollover::~Rollover ()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}     

//******************************************************************************
SEVERITY Rollover::doInit (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doInit"));
   setFieldNoValidate ( ifds::TradesTransType, 
                        TRADETYPE::ROLLOVER, 
                        idDataGroup, 
                        false);
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
bool Rollover::supportsAllocations (const BFDataGroupId &idDataGroup)
{
   return false;
}

//******************************************************************************
bool Rollover::supportsFromAllocations (const BFDataGroupId &idDataGroup)
{
   return false;
}

//******************************************************************************
bool Rollover::isSplitCommissionAllowed (const BFDataGroupId &idDataGroup)
{
   return false; 
}

//******************************************************************************
bool Rollover::isAssociationToOriginalContribAllowed (const BFDataGroupId &idDataGroup)
{
   return false;
}

//******************************************************************************
void Rollover::getFundAndClassFieldIds ( BFFieldId &fundCodeFieldId, 
                                         BFFieldId &classCodeFieldId)
{
   fundCodeFieldId = ifds::FromFund;
   classCodeFieldId = ifds::FromClass;
}

//******************************************************************************
void Rollover::getPurchaseFundAndClassFieldIds ( BFFieldId &fundCodeFieldId, 
                                                 BFFieldId &classCodeFieldId)
{
   fundCodeFieldId = ifds::ToFund;
   classCodeFieldId = ifds::ToClass;
}

//******************************************************************************
void Rollover::getAccountFieldId (BFFieldId &accountFieldId)
{
   accountFieldId = ifds::AccountNum;
}

//******************************************************************************
void Rollover::getPurchaseAccountFieldId (BFFieldId &accountFieldId)
{
   accountFieldId = ifds::AccountTo;
}

//******************************************************************************
inline bool Rollover::areTaxRatesAllowed (const BFDataGroupId &idDataGroup)
{
   return false;
}

//******************************************************************************
inline bool Rollover::isSettleLocAllowed (const BFDataGroupId &idDataGroup)
{
   return false;
}

//******************************************************************************
bool Rollover::isAccountCloningAllowed (const BFDataGroupId &idDataGroup)
{
   return true;
}

//multiple settle location
//******************************************************************************
bool Rollover::areMultipleSettleLocAllowed (const BFDataGroupId &idDataGroup)
{
   return false;
}
//****************************************************************************** 
SEVERITY Rollover::orderTypeRelatedChanges ( const BFDataGroupId &idDataGroup, 
                                   bool bValidateDate /* = true*/)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("orderTypeRelatedChanges"));

	return GETCURRENTHIGHESTSEVERITY ();
}
//******************************************************************************
SEVERITY Rollover::preInitWithDefaultValues (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("preInitWithDefaultValues"));
//base class call   
   Redemption::preInitWithDefaultValues (idDataGroup);

   setFieldSubstituteValues (ifds::AmtType, idDataGroup, ifds::AmountTypeRollover);
   setFieldRequired (ifds::AccountTo, idDataGroup, true); //account to is required
   setFieldReadOnly (ifds::AccountTo, idDataGroup, false);
   setFieldReadOnly (ifds::TradesPayType, idDataGroup, true);
   setFieldReadOnly (ifds::OrderType, idDataGroup, true);
   setFieldReadOnly (ifds::SuppressCode, idDataGroup, true);
   setFieldReadOnly (ifds::LSIFCode, idDataGroup, true);
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
void Rollover::doInitWithDefaultValues (const BFDataGroupId &idDataGroup)
{
   Redemption::doInitWithDefaultValues (idDataGroup);
   setFieldValid (ifds::AccountTo, idDataGroup, false); //to force validation
   setFieldNoValidate ( ifds::LSIFCode, I_("99"), idDataGroup, false, //rollovers
                        true,  //valid, since is a locked field 
                        true);
//the default for Redemption Code is already set to '01' by the Redemption CBO
   setFieldNoValidate ( ifds::DepositType, I_("1"), idDataGroup, false, //cash
                        false, false);
   setFieldNoValidate ( ifds::OrderType, I_("N"), idDataGroup, false, //direct
                        false, true);
//suppressed cheque
   setFieldNoValidate ( ifds::SuppressCode, I_("99"), idDataGroup, false, 
                        false, true);
//deposit type and redemption code defaults, based on from account tax type,
//retrieve the account to find out the tax type
   MFAccount *pMFAccount = NULL;
   DString accountNum;

   getField (ifds::AccountNum, accountNum, idDataGroup);
   accountNum.stripLeading ('0');
   if( !accountNum.empty() &&
       getWorkSession().getMFAccount (idDataGroup, accountNum, pMFAccount) <= WARNING && 
       pMFAccount)
   {
      DString taxType;

      pMFAccount->getField (ifds::TaxType, taxType, idDataGroup, false);
      if (!getWorkSession().isNonRegLike( taxType )) //not an open plan
      {
         setFieldNoValidate (ifds::RedCode, I_("03"), idDataGroup, false);
         setFieldNoValidate (ifds::DepositType, I_("4"), idDataGroup, false);
      }
   }
}

//******************************************************************************
SEVERITY Rollover::transTypeRelatedChanges (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("transTypeRelatedChanges"));
//attributes grid
   DString transferAttributeSubstList;
   BFProperties *pBFProperties = 
      getFieldProperties (ifds::TransferAttributes, idDataGroup);
   pBFProperties->getAllSubstituteValues (transferAttributeSubstList);
//remove fields that are not needed
   transferAttributeSubstList = 
         removeItemFromSubtList ( transferAttributeSubstList, 
                                  I_("ROAAmount"));      
   transferAttributeSubstList = 
         removeItemFromSubtList ( transferAttributeSubstList, 
                                  I_("MCHFileIndicator"));   
   transferAttributeSubstList = 
         removeItemFromSubtList ( transferAttributeSubstList, 
                                  I_("SecRecFileIndicator"));   
   transferAttributeSubstList = 
         removeItemFromSubtList ( transferAttributeSubstList, 
                                  I_("CloneAcctAMS"));   
   setFieldAllSubstituteValues ( ifds::TradeAttributesFields, 
                                 idDataGroup, 
                                 transferAttributeSubstList);

//pay type substitution
   if (!_bInitPending)
   {
      setFieldNoValidate ( ifds::TradesPayType, PAYTYPE::SUPPRESS, idDataGroup, 
                           false, false, true, 
                           false);  //no related changes
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//***************************************************************************************************
SEVERITY Rollover::doInit (const BFData &data)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doInit"));
   
   Redemption::doInit (data);
   setFieldReadOnly (ifds::ToFund, BF::HOST, false);
   setFieldReadOnly (ifds::ToClass, BF::HOST, false);
   setFieldReadOnly (ifds::ToFundNumber, BF::HOST, false);
   setFieldRequired (ifds::ToFund, BF::HOST, true);
   setFieldRequired (ifds::ToClass, BF::HOST, true);

   DString accountTo;

   getField (ifds::AccountNum, accountTo, BF::HOST, false);
	loadDepRedCodeSubstList ( accountTo, 
                             I_("D"),  //deposit type
                             BF::HOST);
   setFieldValid (ifds::LSIFCode, BF::HOST, true);
   return GETCURRENTHIGHESTSEVERITY ();
}

//***************************************************************************************************
SEVERITY Rollover::doApplyRelatedChanges ( const BFFieldId &idField, 
                                           const BFDataGroupId &idDataGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doApplyRelatedChanges"));

   if (Redemption::doApplyRelatedChanges (idField, idDataGroup) <= WARNING)
   {
      if (idField == ifds::AccountNum)
      {
         DString accountNum;

         getField (ifds::AccountNum, accountNum, idDataGroup, false);
         setField (ifds::AccountTo, accountNum, idDataGroup, false);
//deposit type and redemption code defaults, based on from account tax type,
//retrieve the account to find out the tax type
         MFAccount *pMFAccount = NULL;

         if ( getWorkSession().getMFAccount (idDataGroup, accountNum, pMFAccount) <= WARNING && 
              pMFAccount)
         {
            DString taxType;

            pMFAccount->getField (ifds::TaxType, taxType, idDataGroup, false);
            if (!getWorkSession().isNonRegLike( taxType )) //not an open plan
            {
               setFieldNoValidate (ifds::RedCode, I_("03"), idDataGroup, false);
               setFieldNoValidate (ifds::DepositType, I_("4"), idDataGroup, false);
            }
         }
      }
      else if (idField == ifds::AccountTo)
      {
         setFieldReadOnly (ifds::ToFund, idDataGroup, false);
         setFieldReadOnly (ifds::ToClass, idDataGroup, false);
         setFieldReadOnly (ifds::ToFundNumber, idDataGroup, false);
         setFieldRequired (ifds::ToFund, idDataGroup, true);
         setFieldRequired (ifds::ToClass, idDataGroup, true);
         setFieldNoValidate ( ifds::ToFund, NULL_STRING, idDataGroup, false, 
                              true, 
                              true, 
                              false
                            );
         setFieldNoValidate ( ifds::ToClass, NULL_STRING, idDataGroup, false, 
                              true, 
                              true, 
                              false
                            );
         setFieldNoValidate ( ifds::ToFundNumber, NULL_STRING, idDataGroup, false, 
                              true, 
                              true, 
                              false
                            );
//to force validation
         setFieldValid (ifds::ToFund, idDataGroup, false);
         setFieldValid (ifds::ToClass, idDataGroup, false);

         DString accountTo;

         getField (ifds::AccountNum, accountTo, idDataGroup, false);
	      loadDepRedCodeSubstList ( accountTo, 
                                   I_("D"),  //deposit type
                                   idDataGroup
                                 );         
      }
      else if (idField == ifds::EffectiveDate)
      {
         // to force validation (can Fund still trade?)
         setFieldValid (ifds::ToFundClass, idDataGroup, false);  
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Rollover::doValidateField ( const BFFieldId &idField, 
                                     const DString &strValue, 
                                     const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doValidateField"));
   if (Redemption::doValidateField (idField, strValue, idDataGroup) <= WARNING)
   {
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Rollover::canAccountTrade ( MFAccount *pMFAccount, 
                                     const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("canAccountTrade"));
//calls base class, from side is a redemption
   Redemption::canAccountTrade (pMFAccount, idDataGroup);
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Rollover::canAccountToTrade ( MFAccount *pMFAccount, 
                                       const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("canAccountToTrade"));
//calls base class, to side is a purchase
   Purchase::canAccountTrade (pMFAccount, idDataGroup);
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Rollover::validateAccountTo ( MFAccount *pMFAccountTo, 
                                       const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateAccountTo"));
//calls base class, to side is a purchase
   if (Purchase::validateAccount (pMFAccountTo, idDataGroup) <= WARNING)
   {
      if (!isSameAccountOwner (idDataGroup))
      {
         ADDCONDITIONFROMFILE (CND::ERR_ROLLOVER_NOT_SAME_ACCOUNT_OWNER);
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Rollover::validateFundCode ( const DString &fundCode, 
                                      const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_( "validateFundCode"));
   if (Redemption::validateFundCode (fundCode, idDataGroup) <= WARNING)
   {
      validateLSIFFund (fundCode, idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Rollover::validateToFundCode ( const DString &fundCode, 
                                        const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_( "validateFundCode"));
   if (Purchase::validateFundCode (fundCode, idDataGroup) <= WARNING)
   {
      validateLSIFFund (fundCode, idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//****************************************************************************** 
SEVERITY Rollover::validateMasterActAMS(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateMasterActAMS"));

   return GETCURRENTHIGHESTSEVERITY ();
}

//****************************************************************************** 
SEVERITY Rollover::validateFundClass ( const DString &fundCode, 
                                       const DString &classCode, 
                                       const DString &accountNum, 
                                       const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateFundClass"));
   Redemption::validateFundClass (fundCode, classCode, accountNum, idDataGroup);
   return GETCURRENTHIGHESTSEVERITY();
}

//****************************************************************************** 
SEVERITY Rollover::validateToFundClass ( const DString &fundCode, 
                                         const DString &classCode, 
                                         const DString &accountNum, 
                                         const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateToFundClass"));
   Purchase::validateFundClass (fundCode, classCode, accountNum, idDataGroup);
   return GETCURRENTHIGHESTSEVERITY();
}

//***********************************************************************************
SEVERITY Rollover::getPurchaseRepInfoFields ( DString &broker, 
                                              DString &branch, 
                                              DString &agent, 
                                              const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getPurchaseRepInfoField"));

   DString accountTo;

   getField (ifds::AccountTo, accountTo, idDataGroup, false);

   MFAccount *pMFAccount = NULL;

   if ( getWorkSession().getMFAccount (idDataGroup, accountTo, pMFAccount) <= WARNING && 
        pMFAccount)
   {
//get the values of broker/branch/sales rep from the 'to account'
      pMFAccount->getField (ifds::BrokerCode, broker, idDataGroup);
      pMFAccount->getField (ifds::BranchCode, branch, idDataGroup);
      pMFAccount->getField (ifds::Slsrep, agent, idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//********************************************************************************************
SEVERITY Rollover::validateFromToFundClass ( const DString &fromFund,
                                             const DString &fromClass,
                                             const DString &toFund,
                                             const DString &toClass,
                                             const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateFromToFundClass"));
//check whether the funds have the same currency
   DString fromCurrency,
      toCurrency;

   getFundField (fromFund, fromClass, ifds::Currency, fromCurrency);
   getFundField (toFund, toClass, ifds::Currency, toCurrency);
   if (fromCurrency != toCurrency)
   {
      ADDCONDITIONFROMFILE (CND::ERR_ROLLOVER_SAME_CURRENCY_FUNDS);
   }
   if (GETCURRENTHIGHESTSEVERITY() <= WARNING)
   {
//check whether the rollover is allowed
      LSIFRolloverRulesList *pLSIFRolloverRulesList = NULL;

      if ( getMgmtCo().getLSIFRolloverRulesList ( fromFund, 
                                                  fromClass, 
                                                  pLSIFRolloverRulesList) <= WARNING && 
           pLSIFRolloverRulesList)
      {
         if (!pLSIFRolloverRulesList->isRolloverAllowed (toFund, toClass))
         {
            DString idiStr;

            addIDITagValue (idiStr, I_ ("FROMFUND"), fromFund);
            addIDITagValue (idiStr, I_ ("FROMCLASS"), fromClass);
            addIDITagValue (idiStr, I_ ("TOFUND"), toFund);
            addIDITagValue (idiStr, I_ ("TOCLASS"), toClass);
            ADDCONDITIONFROMFILEIDI (CND::ERR_ROLLOVER_NOT_ALLOWED, idiStr);
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Rollover::fromFundClassRelatedChanges ( const DString &fundCode, 
                                                 const DString &classCode, 
                                                 const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("fromFundClassRelatedChanges"));
   if (Redemption::fromFundClassRelatedChanges (fundCode, classCode, idDataGroup) <= WARNING)
   {
//override this because redemption's implementation changes the 'lsif code' default
      setFieldNoValidate ( ifds::LSIFCode, I_("99"), // 'rollover'
                           idDataGroup, false, 
                           true,  //valid, since is a locked field
                           true);
      setFieldReadOnly (ifds::LSIFCode, idDataGroup, true);
   }
   return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
SEVERITY Rollover::toFundClassRelatedChanges ( const DString &fundCode, 
                                               const DString &classCode, 
                                               const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("fromFundClassRelatedChanges"));
//call direct trade, purchases will act on the 'from side'
   if (Trade::toFundClassRelatedChanges (fundCode, classCode, idDataGroup) <= WARNING)
   {
      setSettleCurrencyFromFund (fundCode, classCode, idDataGroup);
      setFieldValid (ifds::NetOrdType, idDataGroup, false); //net orders are not allowed for bel funds
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************************************
SEVERITY Rollover::validateLSIFFund ( const DString &fundCode, 
                                      const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_( "validateLSIFFund"));

   FundMasterList *pFundMasterList; 

   if ( !fundCode.empty() && 
        getMgmtCo().getFundMasterList (pFundMasterList) && 
        pFundMasterList)
   {
      if (!pFundMasterList->isLSIFFund (fundCode))
      {
         ADDCONDITIONFROMFILE (CND::ERR_FUND_NOT_LSIF);
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Rollover::validateTradeDate ( const DString &tradeDate, 
                                       const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_( "validateTradeDate"));

   Purchase::validateTradeDate ( tradeDate,
                                 idDataGroup);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
inline bool Rollover::isACHApplicable (const BFDataGroupId &idDataGroup)
{
   return false;
}

//******************************************************************************
inline SEVERITY Rollover::getDefaultBankInstructions ( BankInstructions *&pBankInstructions, 
                                                       const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getDefaultBankInstructions"));
   pBankInstructions = NULL;
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Rollover::validateAmtType ( const DString &amtType,
                                     const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateAmtType"));
   if (Redemption::validateAmtType (amtType, idDataGroup) <= WARNING)
   {
      Purchase::validateAmtType (amtType, idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Rollover::validateAmount ( const DString &amount,
                                    const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateAmount"));
   Redemption::validateAmount (amount, idDataGroup);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Rollover::validateAmtTypeGrossNet (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateAmtTypeGrossNet"));
   if (Redemption::validateAmtTypeGrossNet (idDataGroup) <= WARNING)
   {
      Purchase::validateAmtTypeGrossNet (idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//***********************************************************************************
SEVERITY Rollover::validateMinFromFundAmount ( const DString &accountNum,
                                               const DString &fundCode,
                                               const DString &classCode,
                                               const DString &amtType,
                                               const DString &amount,
											              const DString &broker,
											              const DString &branch,
										                 const DString &slsrep,
                                               const DString &depositType, //in1419539
                                               const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateMinFromFundAmount"));
   Redemption::validateMinFromFundAmount ( accountNum, 
                                           fundCode, 
                                           classCode, 
                                           amtType, 
                                           amount, 
										             broker,
										             branch,
										             slsrep,
                                           depositType, //in1419539
                                           idDataGroup);
   return GETCURRENTHIGHESTSEVERITY();
}

//***********************************************************************************
SEVERITY Rollover::validateMinToFundAmount ( const DString &accountNum,
                                             const DString &fundCode,
                                             const DString &classCode,
                                             const DString &amtType,
                                             const DString &amount,
											            const DString &broker,
											            const DString &branch,
										               const DString &slsrep,
                                             const DString &depositType, //in1419539
                                             const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateMinToFundAmount"));
//what's comming in should be the 'to side'
   Purchase::validateMinFromFundAmount ( accountNum, 
                                         fundCode, 
                                         classCode, 
                                         amtType, 
                                         amount,
										           broker,
										           branch,
										           slsrep,
                                         depositType, //in1419539
                                         idDataGroup);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Rollover::validateCurrency ( const DString &currency,
                                      const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateCurrency"));
   Purchase::validateCurrency (currency, idDataGroup);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Rollover::filterSettleCurrencyForFund ( const DString &inCurrSubstList,
                                                 DString &currSubstList,
                                                 const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("filterSettleCurrencyForFund"));
   Purchase::filterSettleCurrencyForFund (inCurrSubstList, currSubstList, idDataGroup);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool Rollover::isCashDateUpdatable ( FundMaster *pFundMaster,
                                     const BFDataGroupId &idDataGroup)
{
	return Redemption::isCashDateUpdatable (pFundMaster, idDataGroup);
}

//******************************************************************************        
SEVERITY Rollover::amsFundClassTradeMinAmtCheck ( const DString &transType,
                                                  const DString &accountNum,
                                                  const DString &fundCode, 
                                                  const DString &classCode,
                                                  const DString &amtType, 
                                                  const DString &amount, 
                                                  const DString &currency, 
                                                  const DString &exchRate, 
                                                  const DString &tradeDate, 
												  const DString &broker,
							                      const DString &branch,
							                      const DString &slsrep,
                                                  const DString &depositType, //in1419539
                                                  //ams   
                                                  const DString &amsCode,
                                                  AmsMstrInfo *pAMSMstrInfo,
                                                  const DString &taxJuris,
                                                  const DString &provResid,
                                                  const DString &accountType,
                                                  const DString &taxType,
                                                  const DString &acctDesign,
                                                  bool &bOverrideFundLevelCheck,
                                                  const BFDataGroupId &idDataGroup,
                                                  bool bFullExchPrntToPrnt)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("amsFundClassTradeMinAmtCheck"));
//not very nice, it's a compromise
   if (transType == TRADETYPE::PURCHASE)
   {
      Purchase::amsFundClassTradeMinAmtCheck ( transType, 
                                               accountNum,
                                               fundCode, 
                                               classCode,
                                               amtType, 
                                               amount, 
                                               currency, 
                                               exchRate, 
                                               tradeDate, 
											   broker,
											   branch,
											   slsrep,
                                               depositType, //in1419539
                                               //ams   
                                               amsCode, 
                                               pAMSMstrInfo,
                                               taxJuris,
                                               provResid,
                                               accountType,
                                               taxType,
                                               acctDesign,
                                               bOverrideFundLevelCheck,
                                               idDataGroup,
                                               bFullExchPrntToPrnt);
   }
   else if (transType == TRADETYPE::REDEMPTION)
   {
      Redemption::amsFundClassTradeMinAmtCheck ( transType, 
                                                 accountNum,
                                                 fundCode, 
                                                 classCode,
                                                 amtType, 
                                                 amount, 
                                                 currency, 
                                                 exchRate, 
                                                 tradeDate, 
												 broker,
												 branch,
												 slsrep,
                                                 depositType, //in1419539
                                                 //ams   
                                                 amsCode,
                                                 pAMSMstrInfo,
                                                 taxJuris,
                                                 provResid,
                                                 accountType,
                                                 taxType,
                                                 acctDesign,
                                                 bOverrideFundLevelCheck,
                                                 idDataGroup,
                                                 bFullExchPrntToPrnt);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Rollover::payTypeRelatedChanges (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("payTypeRelatedChanges"));

   //skip the base class Redemption 'logic'
   return Trade::payTypeRelatedChanges (idDataGroup);
}

//*****************************************************************************************
SEVERITY Rollover::validateSettleSource ( const DString &settleSource, 
                                        const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateSettleSource") );

	Redemption::validateSettleSource (settleSource, idDataGroup);

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Rollover::validateEUSDBackdates( const DString &dstrFund,
	                                       const DString &dstrClass,
									               const DString &dstrAccountNum,
	                                       const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateEUSDBackdates"));	
   
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
void Rollover::setDefaultPayType (const DString dstrAccountNum, 
								  DString &payType,
								  const BFDataGroupId &idDataGroup)
{
	setClearingAccDefaultPayType (dstrAccountNum, payType, idDataGroup);
}

//******************************************************************************

SEVERITY Rollover::getFormerSpouseList( DString& strFormerSpouses, const BFDataGroupId &idDataGroup )
{
	return Trade::getFormerSpouseList( strFormerSpouses, idDataGroup );

}

//******************************************************************************
SEVERITY Rollover::doValidateAll ( const BFDataGroupId& idDataGroup, 
                                   long lValidateGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_ ("doValidateAll"));

   if (Trade::doValidateAll( idDataGroup, true ) <= WARNING )
   {
   }

   return GETCURRENTHIGHESTSEVERITY ();
}
//******************************************************************************
bool Rollover::isRESPTransferAllowed (const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("isRESPTransferAllowed"));
   
	return false;
}

//******************************************************************************
bool Rollover::isRDSPTransferAllowed (const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("isRDSPTransferAllowed"));
   
	return false;
}

//******************************************************************************
SEVERITY Rollover::validateLinkedEntity(const DString& strValue, const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_("validateLinkedEntity"));

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Rollover::validateAmtTypeRedCode (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateAmtTypeRedCode"));

   
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Rollover::validateAmountRedCode (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateAmtTypeRedCode"));

   
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Rollover::validateRESPTradeResidency(const DString &redcode, 
                                              const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateRESPTradeResidency"));


   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Rollover::validateTradePayTypeFundClass( const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateTradePayTypeFundClass"));

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
bool Rollover::isExternalInstitutionTrackingEnable(const BFDataGroupId& idDataGroup)
{
   // overridden in purchase\redemtion CBO

   return Trade::isExternalInstitutionTrackingEnable(idDataGroup);
}
//**************************************************************************************************
SEVERITY Rollover::initPriceTypesList(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("initPriceTypesList"));

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Rollover::validateRDSPTrade (const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateRDSPTrade"));

	Redemption::validateRDSPTrade (idDataGroup);

	return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/Rollover.cpp-arc  $
// 
//    Rev 1.50   Apr 20 2012 15:22:08   wp040027
// R12.3P0188394_Value date incorrect in ED & PW Non PF fund class
// 
//    Rev 1.49   Feb 07 2011 18:32:40   dchatcha
// P0179308 FN01 - Multi Manager Subscription and Direct Debit Payment.
// 
//    Rev 1.48   Apr 22 2010 07:33:00   kitticha
// PET0165541 FN01 QESI RESP Trading.
// 
//    Rev 1.47   Apr 22 2010 05:30:22   kitticha
// PET0165541 FN01 QESI RESP Trading.
// 
//    Rev 1.46   Apr 21 2010 01:22:08   popescu
// RESP-QESI Resp transfer screen
// 
//    Rev 1.45   Apr 14 2010 23:59:06   popescu
// PET165541_FN01_QESI - RESP Gap_Dsk_Trading
// 
//    Rev 1.44   Apr 14 2010 09:43:36   jankovii
// PET165541_FN01_QESI - RESP Gap_Dsk_Trading
// 
//    Rev 1.43   Aug 11 2009 13:57:26   jankovii
// PET0164824 FN01 - Eiger iShares Orders and ETF Fields
// 
//    Rev 1.42   27 Jul 2009 15:14:40   popescu
// Project Eiger - P0147738 FN36 - Adding a field to figure out when the multiple settle locations should show up
// 
//    Rev 1.41   06 Oct 2008 13:19:46   kovacsro
// PET142007  FN01 TFSA
// 
//    Rev 1.40   01 Oct 2008 12:00:44   popescu
// Check in for incident  1419539
// 
//    Rev 1.39   12 Sep 2008 15:41:06   kovacsro
// PET142007.FN01 Tax Free Saving Account - code cleanup for taxType=0
// 
//    Rev 1.38   12 Jul 2007 17:10:04   popescu
// AIM GAP 2 AMS - added an extra field to trading CloneAcctAMS - used in AllTransfer to copy AMS to the to acct.
// 
//    Rev 1.37   May 04 2007 13:59:14   jankovii
// PET 2321 FN01 - MT54X Default Pay Type.
// 
//    Rev 1.36   Nov 09 2006 00:08:14   popescu
// PET 2281/Fn01 - cloning account - TA  synch-up from rel 73
// 
//    Rev 1.35   Oct 30 2006 17:05:24   jankovii
// PET 2185 FN04 - Trade restrictions.
// 
//    Rev 1.34   Jan 12 2006 13:48:14   AGUILAAM
// PET1295_FN01: Trade Suppress Indicator for MCH and SR Files - Trade Entry/Rebook/Trans History
// 
//    Rev 1.33   Jan 03 2006 15:36:14   popescu
// Incident# 502420
// 
// The default for Rollovers for Registered Plans are:
// Redemption Code	03  RSP Transfer
// Deposit Type		04  Transfer In RSP
// 
// For Open Plans
// Redemption Code	01  Cash
// Deposit Type		01
// 
// 
//    Rev 1.32   Jul 07 2005 11:41:10   porteanm
// PET1171 EUSD 1B - Added validateEUSDBackDates().
// 
//    Rev 1.31   Jun 28 2005 14:39:46   Yingbaol
// PTS344581: remove ROAAmount from rollover attribute field
// 
//    Rev 1.30   Mar 10 2005 11:00:44   porteanm
// Incident 243157/243387 - SettleSource validation.
// 
//    Rev 1.29   Mar 03 2005 15:04:28   popescu
// Incident # 257544, should consider LSIFCode a valid field for Rollovers, even when a pending rollover is modified, this is due to the fact that the field is not displayed on the trade entry screen and it should always be set to 99, behind the scenes
// 
//    Rev 1.28   Jan 09 2005 16:01:38   popescu
// PTS 10037643, LSIFCode should be set to the valid value of '99', for rollovers
// 
//    Rev 1.27   Dec 29 2004 11:22:16   popescu
// PTS 10037302, do not validate amount precision for amount type units
// 
//    Rev 1.26   Dec 14 2004 15:01:50   popescu
// some of the cross-edits have been renamed
// 
//    Rev 1.25   Dec 07 2004 01:37:48   popescu
// PET 1117/56 trades processing/modify trade
// 
//    Rev 1.24   Dec 01 2004 15:44:58   popescu
// PET 1117/56 fees processing, calculate the discount rate
// 
//    Rev 1.23   Nov 30 2004 20:10:06   popescu
// PET 1117/06
// 
//    Rev 1.22   Nov 29 2004 20:30:38   popescu
// PET 1117/06/56 fees/trades processing
// 
//    Rev 1.21   Nov 24 2004 21:36:10   popescu
// PET 1117/06/56. trade processing, settle location
// 
//    Rev 1.20   Nov 14 2004 14:52:28   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.19   Nov 08 2004 12:31:04   popescu
// PET 1117/06 trade processing
// 
//    Rev 1.18   Nov 06 2004 00:42:28   popescu
// PET 1117/06, synch changes
// 
//    Rev 1.6   Nov 04 2004 17:38:44   popescu
// PET 1117/06, Trade processing
// 
//    Rev 1.5   Nov 02 2004 19:19:34   popescu
// PET 1117/06 Trade processing...
// 
//    Rev 1.4   Oct 28 2004 18:23:54   popescu
// PET 1117/06
// 
//    Rev 1.3   Oct 27 2004 11:27:02   popescu
// PET 1117/06
// 
//    Rev 1.2   Oct 22 2004 19:58:52   popescu
// PET 1117/06, work in progress...
// 
//    Rev 1.1   Oct 21 2004 06:29:18   popescu
// PET 1117/06 - Trade processing work in progress..
// 
//    Rev 1.0   Oct 01 2004 19:29:58   popescu
// Initial revision.
 * 
 *    Rev 1.566   Sep 21 2004 16:02:32   popescu
  * Initial revision.
// 
// 
*/
