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
// ^FILE   : AllTransfer.cpp
// ^AUTHOR : Serban Popescu   
// ^DATE   : September, 2004
//
// ^CLASS    : AllTransfer - 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "alltransfer.hpp"

#include "mfaccount.hpp"
#include "mfaccountholdinglist.hpp"
#include "supportedproductslist.hpp"
#include "FundMasterList.hpp"
#include "mgmtco.hpp"
#include "seqfundvalidation.hpp"

#include <conditions\iFastLayer\iFast\ifastcbo\IFast_IFast_ifastcbo_warn_receiving_acct_and_relinquishing_acct_linked_to_diff_ams_model.h>
#include <conditions\iFastLayer\iFast\ifastcbo\IFast_IFast_ifastcbo_err_receiving_acct_and_relinquishing_acct_linked_to_diff_ams_model.h>
#include <conditions\iFastLayer\iFast\ifastcbo\IFast_IFast_ifastcbo_warn_trading_on_global_ams_parent_fnd_cls_not_allowed_acct_not_linked_to_any_ams.h>
#include <conditions\iFastLayer\iFast\ifastcbo\IFast_IFast_ifastcbo_err_trading_on_global_ams_parent_fnd_cls_not_allowed_acct_not_linked_to_any_ams.h>


namespace ifds
{
//management company options
//attributes grid
//fund fields
   extern CLASS_IMPORT const BFTextFieldId ToFundNumber;
   extern CLASS_IMPORT const BFTextFieldId FromFundNumber;
   extern CLASS_IMPORT const BFTextFieldId FundISIN;
   extern CLASS_IMPORT const BFTextFieldId FundWKN;
   extern CLASS_IMPORT const BFTextFieldId FundToISIN;
   extern CLASS_IMPORT const BFTextFieldId FundToWKN;
   extern CLASS_IMPORT const BFTextFieldId FundCurrency;
   extern CLASS_IMPORT const BFTextFieldId rxFundCode;
   extern CLASS_IMPORT const BFTextFieldId rxClassCode;
   extern CLASS_IMPORT const BFTextFieldId AMSCode;
//unrelated fields
   extern CLASS_IMPORT const BFDecimalFieldId SettledUnits;
//subst sets
//cross edits
   extern CLASS_IMPORT const BFTextFieldId AllFundTransfer;
// seg data
   extern CLASS_IMPORT const BFTextFieldId TransType;
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const ALL_FUND_TRANSFER;
}

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME	= I_ ("AllTransfer");
   const I_CHAR * const YES         = I_( "Y" );
}

namespace CND
{
   extern const long ERR_FROMFUND_TOFUND_MUST_BE_BLANK_FOR_ALLFUND_TRANSFER;
   extern const long ERR_TAXTYPE_IS_NOT_ALLOWED_TRADING;
   extern const long WARN_AMS_ACCT_SHOULD_CLONE;
}

namespace IFASTERR
{         
    extern CLASS_IMPORT I_CHAR * const RECEIVING_ACCT_AND_RELINQUISHING_ACCT_LINKED_TO_DIFF_AMS_MODEL;
    extern CLASS_IMPORT I_CHAR * const TRADING_ON_GLOBAL_AMS_PARENT_FND_CLS_NOT_ALLOWED_ACCT_NOT_LINKED_TO_ANY_AMS;
}

namespace UAF
{
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,              State Flags,      Group Flags 
//general trade fields
   {ifds::AllFundTransfer, BFCBO::NONE, 0}, 
   {ifds::CloneAcctAMS,    BFCBO::NONE, 0}, 
};

static const int NUM_FIELDS = sizeof (classFieldInfo) / sizeof (BFCBO::CLASS_FIELD_INFO);

//******************************************************************************
AllTransfer::AllTransfer (BFAbstractCBO &parent) : Transfer (parent)
{
   TRACE_CONSTRUCTOR ( CLASSNAME, 
                       NULL_STRING);
   registerMemberData ( NUM_FIELDS,
                        (const CLASS_FIELD_INFO *)&classFieldInfo,
                        0, 
                        NULL);

   addCrossEdit (ifds::AllFundTransfer, ifds::FromFund); 
}


//******************************************************************************
AllTransfer::~AllTransfer ()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}     

//******************************************************************************
SEVERITY AllTransfer::doInit (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doInit"));

   setFieldNoValidate ( ifds::TradesTransType, 
                        TRADETYPE::ALL_FUND_TRANSFER, 
                        idDataGroup, 
                        false);
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
bool AllTransfer::supportsAllocations (const BFDataGroupId &idDataGroup)
{
   return false;
}

//******************************************************************************
bool AllTransfer::supportsFromAllocations (const BFDataGroupId &idDataGroup)
{
   return false;
}

//******************************************************************************
SEVERITY AllTransfer::preInitWithDefaultValues (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("preInitWithDefaultValues"));
//base class call   
   Transfer::preInitWithDefaultValues (idDataGroup);
   allFundsRelatedChanges (idDataGroup);
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
void AllTransfer::doInitWithDefaultValues (const BFDataGroupId &idDataGroup)
{
   Transfer::doInitWithDefaultValues (idDataGroup);
//amount
   setFieldNoValidate ( ifds::Amount, I_("0.0"), idDataGroup, false,
                        true,
                        true);

}

//***************************************************************************************************
SEVERITY AllTransfer::doInit (const BFData &data)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doInit"));
   Transfer::doInit (data);
   allFundsRelatedChanges (BF::HOST);
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY AllTransfer::doValidateField ( const BFFieldId &idField, 
                                        const DString &strValue, 
                                        const BFDataGroupId &idDataGroup) 
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doValidateField"));
   if ( idField == ifds::FromFund ||
        idField == ifds::FromClass ||
        idField == ifds::ToFund ||
        idField == ifds::ToClass)
   {
      ;//skip validation
   }
   else if (Transfer::doValidateField (idField, strValue, idDataGroup) <= WARNING)
   {
      if (idField == ifds::AllFundTransfer)
      {
         validateAllFundTransfer (idDataGroup);
      }
      else if (idField == ifds::CloneAcctAMS)
      {
//need the from account
         DString accountNum;
         MFAccount *pMFAccount (NULL);

         getField (ifds::AccountNum, accountNum, idDataGroup, false);
         if ( getWorkSession().getMFAccount ( idDataGroup, 
                                              accountNum, 
                                              pMFAccount) <= WARNING && 
              pMFAccount)
         {
            if (strValue == N && pMFAccount->isAMSAccount (idDataGroup))
            {
               DString idiStr;

               addIDITagValue (idiStr, I_("ACCT"), accountNum);

               ADDCONDITIONFROMFILEIDI (CND::WARN_AMS_ACCT_SHOULD_CLONE, idiStr)
            }
         }
      }
      else if (idField == ifds::AccountTo)
      {
         validateMasterActAMS(idDataGroup);
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//***************************************************************************************************
SEVERITY AllTransfer::doApplyRelatedChanges ( const BFFieldId &idField, 
                                              const BFDataGroupId &idDataGroup) 
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doApplyRelatedChanges"));

   if (idField == ifds::AccountTo)
   {
      DString accountNum;

      getField (ifds::AccountTo, accountNum, idDataGroup);
      loadDepRedCodeSubstList (accountNum, I_("D"), idDataGroup);
      setValidFlag (ifds::AllFundTransfer, idDataGroup, false); //to trigger validations
      clearingRelatedChanges (idDataGroup, false); //to side
//check whether there are LSIF holdings for the account from
	   SupportedProductsList *pSupportedProductsList = NULL;

      if ( getMgmtCo ().getSupportedProductsList (pSupportedProductsList) <= WARNING && 
           pSupportedProductsList)
      {
         if (pSupportedProductsList->isLSIFProductActive ())
	      {
			   FundMasterList *pFundMasterList; 

			   if ( getMgmtCo().getFundMasterList (pFundMasterList) <= WARNING &&
                 pFundMasterList)
            {
               MFAccountHoldingList *pAccountHoldingList = NULL;
      
               if ( getAccountHoldings (pAccountHoldingList, idDataGroup) <= WARNING &&
                    pAccountHoldingList)
			      {
				      for( BFObjIter iter( *pAccountHoldingList, 
                                       idDataGroup, 
                                       true, 
                                       BFObjIter::ITERTYPE::NON_DELETED); 
					        !iter.end(); 
                       ++iter)
				      {
					      DString fundCode;

                     iter.getObject()->getField (ifds::rxFundCode, fundCode, idDataGroup);
					      if (pFundMasterList->isLSIFFund (fundCode))
					      {
						      setFieldNoValidate ( ifds::LSIFCode, I_("0"), // 'as charged'
                                             idDataGroup, false, true, true);
						      break;
					      }
				      }
			      }
            }
		   }
	   }	
//need the from account
      DString accountFrom;
      MFAccount *pMFAccount (NULL);

      getField (ifds::AccountNum, accountFrom, idDataGroup, false);
      if ( getWorkSession().getMFAccount ( idDataGroup, 
                                           accountFrom, 
                                           pMFAccount) <= WARNING && 
           pMFAccount)
      {
         bool bIsAMSAccount = pMFAccount->isAMSAccount (idDataGroup);

         setFieldReadOnly (ifds::CloneAcctAMS, idDataGroup, !bIsAMSAccount);
         setFieldValid (ifds::CloneAcctAMS, idDataGroup, !bIsAMSAccount);
      }
      updateGuaranteeFeeOverride (idDataGroup);
   }
   else
   {
      Transfer::doApplyRelatedChanges (idField, idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//****************************************************************************** 
SEVERITY AllTransfer::validateMasterActAMS(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateMasterActAMS"));

   DString dstrFundCode, dstrClassCode, dstrAccountTo, dstrAccountFrom;
   MFAccount *pMFAccountTo = NULL;
   MFAccount *pMFAccountFrom = NULL;

   getField(ifds::AccountNum, dstrAccountFrom, idDataGroup);
   getField(ifds::AccountTo, dstrAccountTo, idDataGroup);

   if (getWorkSession().getMFAccount(idDataGroup, dstrAccountFrom, pMFAccountFrom) <= WARNING && pMFAccountFrom &&
       getWorkSession().getMFAccount(idDataGroup, dstrAccountTo, pMFAccountTo) <= WARNING && pMFAccountTo &&
       ((pMFAccountFrom->isAMSAccount(idDataGroup) && pMFAccountTo->isAMSAccount(idDataGroup)) ||
        (pMFAccountFrom->isAMSAccount(idDataGroup) && !pMFAccountTo->isAMSAccount(idDataGroup)))
       )
   {
      DString dstrAcctFromAMSCode, dstrAcctToAMSCode, dstrTradeDate;

      pMFAccountFrom->getField(ifds::AMSCode, dstrAcctFromAMSCode, idDataGroup);
      pMFAccountTo->getField(ifds::AMSCode, dstrAcctToAMSCode, idDataGroup);

      if (dstrAcctFromAMSCode != dstrAcctToAMSCode && !dstrAcctToAMSCode.strip().empty()) 
      {
         CND::CIFast_IFast_ifastcbo_warn_receiving_acct_and_relinquishing_acct_linked_to_diff_ams_model warnCond;
         CND::CIFast_IFast_ifastcbo_err_receiving_acct_and_relinquishing_acct_linked_to_diff_ams_model errCond;

         MFCanBFCbo::getErrMsg (IFASTERR::RECEIVING_ACCT_AND_RELINQUISHING_ACCT_LINKED_TO_DIFF_AMS_MODEL,
                                 errCond,
                                 warnCond,
                                 idDataGroup);
      }
      else if ( dstrAcctFromAMSCode != dstrAcctToAMSCode && dstrAcctToAMSCode.strip().empty())
      {
         CND::CIFast_IFast_ifastcbo_warn_trading_on_global_ams_parent_fnd_cls_not_allowed_acct_not_linked_to_any_ams warnCond;
         CND::CIFast_IFast_ifastcbo_err_trading_on_global_ams_parent_fnd_cls_not_allowed_acct_not_linked_to_any_ams errCond;

         MFCanBFCbo::getErrMsg (IFASTERR::TRADING_ON_GLOBAL_AMS_PARENT_FND_CLS_NOT_ALLOWED_ACCT_NOT_LINKED_TO_ANY_AMS,
                                 errCond,
                                 warnCond,
                                 idDataGroup);
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//****************************************************************************** 
SEVERITY AllTransfer::validateSegBackdates (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateSeqBackdates"));

   if (isSegEnvironment (idDataGroup) && isBackdatedTrade (idDataGroup))
   {
      SeqFundValidation *pSeqFundValidation = NULL;
      DString dstrAccount,
         dstrAccountTo,
         dstrEffectiveDate,
         transType;

      getField (ifds::AccountNum, dstrAccount, idDataGroup);
      getField (ifds::AccountTo, dstrAccountTo, idDataGroup);
      getField (ifds::EffectiveDate, dstrEffectiveDate, idDataGroup);
      getField (ifds::TradesTransType, transType, idDataGroup);

      if( getSegFundValidation( pSeqFundValidation, 
                                NULL_STRING, 
                                NULL_STRING, 
                                dstrAccount, 
                                dstrEffectiveDate, 
                                idDataGroup, 
                                NULL_STRING,
                                transType, 
                                NULL_STRING, 
                                NULL_STRING, 
                                dstrAccountTo) <= WARNING && 
          pSeqFundValidation)
      {
         pSeqFundValidation->checkBackdatedAllowed (dstrEffectiveDate, idDataGroup);
      }	
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//****************************************************************************** 
SEVERITY AllTransfer::validateFundClass ( const DString &fundCode, 
                                          const DString &classCode, 
                                          const DString &accountNum, 
                                          const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateFundClass"));

   if ( !fundCode.empty() ||
        !classCode.empty())
   {
      ADDCONDITIONFROMFILE (CND::ERR_FROMFUND_TOFUND_MUST_BE_BLANK_FOR_ALLFUND_TRANSFER);
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//****************************************************************************** 
SEVERITY AllTransfer::validateToFundClass ( const DString &fundCode, 
                                            const DString &classCode, 
                                            const DString &accountNum, 
                                            const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateToFundClass"));

   if ( !fundCode.empty() ||
        !classCode.empty())
   {
      ADDCONDITIONFROMFILE (CND::ERR_FROMFUND_TOFUND_MUST_BE_BLANK_FOR_ALLFUND_TRANSFER);
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY AllTransfer::validateAllFundTransfer (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateAllFundTransfer"));

   DString fromFund, 
      toFund, 
      amount;

   getField (ifds::FromFund, fromFund, idDataGroup);
   getField (ifds::ToFund, toFund, idDataGroup);
   getField (ifds::Amount, amount, idDataGroup);

   double dec_amount = DSTCommonFunctions::convertToDouble (amount); 

   if ( fromFund.empty() &&
        toFund.empty() && 
        dec_amount == 0)
   {
      DString accountTo;
      MFAccount *pMFAccountTo = NULL;

      getField (ifds::AccountTo, accountTo, idDataGroup);
      accountTo.strip().stripLeading ('0');
      if (!accountTo.empty())
      {
         MFAccountHoldingList *pAccountHoldingList = NULL;

         if ( getAccountHoldings (pAccountHoldingList, idDataGroup) <= WARNING &&
              pAccountHoldingList &&
              getAccount (pMFAccountTo, idDataGroup) <= WARNING &&
              pMFAccountTo) //just to make sure it's valid
         {            
            BFObjIter iter (*pAccountHoldingList, idDataGroup);
          
            for (iter.begin(); !iter.end(); ++iter)
            {
               DString settledUnits, 
                  fundCurrency;

               iter.getObject()->getField (ifds::SettledUnits, settledUnits, idDataGroup);
               if (DSTCommonFunctions::convertToDouble (settledUnits) > 0)
               {
                  iter.getObject()->getField (ifds::FundCurrency, fundCurrency, idDataGroup);
                  if (validateCurrencyTaxType (accountTo, fundCurrency, idDataGroup) > WARNING)
                  {
                     ADDCONDITIONFROMFILE (CND::ERR_TAXTYPE_IS_NOT_ALLOWED_TRADING);
                     break;
                  }
               }
            }
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY AllTransfer::validateRedCodeExclCodes ( const DString &redCode,
                                                 const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "validateRedCodeExclCodes" ));
//empty implementation...
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AllTransfer::validateTIKRedCodes ( const DString &redCode,
                                            const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_( "validateTIKRedCodes" ));

//empty implementation...
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AllTransfer::getAtCostTIKStatus ( const BFDataGroupId &idDataGroup, 
                                           const DString &dstrFundCodeIn, 
                                           const DString &dstrClassCodeIn,
                                           bool blInAllocation,
                                           bool &blIsAtCostTIK)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "getAtCostTIKStatus" ));
//empty implementation...
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AllTransfer::allFundsRelatedChanges (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "allFundsRelatedChanges" ));

   setFieldReadOnly (ifds::Amount, idDataGroup, true);
   setFieldReadOnly (ifds::AmtType, idDataGroup, true);
   setFieldReadOnly (ifds::FromFund, idDataGroup, true);
   setFieldReadOnly (ifds::FromClass, idDataGroup, true);
   setFieldRequired (ifds::FromFund, idDataGroup, false);
   setFieldRequired (ifds::FromClass, idDataGroup, false);
   setFieldReadOnly (ifds::FromFundNumber, idDataGroup, true);
   setFieldReadOnly (ifds::FundISIN, idDataGroup, true);
   setFieldReadOnly (ifds::FundWKN, idDataGroup, true);
   setFieldReadOnly (ifds::ToFund, idDataGroup, true);
   setFieldReadOnly (ifds::ToClass, idDataGroup, true);
   setFieldRequired (ifds::ToFund, idDataGroup, false);
   setFieldRequired (ifds::ToClass, idDataGroup, false);
   setFieldReadOnly (ifds::ToFundNumber, idDataGroup, true);
   setFieldReadOnly (ifds::FundToISIN, idDataGroup, true);
   setFieldReadOnly (ifds::FundToWKN, idDataGroup, true);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool AllTransfer::isWireSupported (const BFDataGroupId &idDataGroup)
{
   return false;
}

//******************************************************************************
SEVERITY AllTransfer::doValidateAll ( const BFDataGroupId& idDataGroup, long lValidateGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_ ("doValidateAll"));

   if (Transfer::doValidateAll (idDataGroup, lValidateGroup) <= WARNING)
   {
      if (isSegEnvironment (idDataGroup) && isSEGPortfolio(idDataGroup))
      {
         SeqFundValidation *pSeqFundValidation = NULL;
         DString dstrAccount,
            dstrAccountTo,
            dstrEffectiveDate,
            transType;

         getField (ifds::AccountNum, dstrAccount, idDataGroup);
         getField (ifds::AccountTo, dstrAccountTo, idDataGroup);
         getField (ifds::EffectiveDate, dstrEffectiveDate, idDataGroup);
         getField (ifds::TradesTransType, transType, idDataGroup);

         if( getSegFundValidation( pSeqFundValidation, 
                                   NULL_STRING, 
                                   NULL_STRING, 
                                   dstrAccount, 
                                   dstrEffectiveDate, 
                                   idDataGroup, 
                                   NULL_STRING,
                                   transType, 
                                   NULL_STRING, 
                                   NULL_STRING, 
                                   dstrAccountTo) <= WARNING && 
            pSeqFundValidation)
         {
            pSeqFundValidation->checkBackdatedAllowed (dstrEffectiveDate, idDataGroup);
            pSeqFundValidation->addSegFundValidationWarnings( idDataGroup );
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AllTransfer::validateAnnuitantGender (const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
							CLASSNAME, 
							I_("validateAnnuitantGender"));

	DString dstrAccountFrom, dstrAccountTo,  dstrGuaranteesOverride, fundCode, classCode, contractType, contractVer;
	MFAccount *pMFAccountFrom = NULL, *pMFAccountTo = NULL;

	getField (ifds::AccountNum, dstrAccountFrom, idDataGroup);
	getField (ifds::AccountTo, dstrAccountTo, idDataGroup); 
	getField (ifds::GuaranteesOverride, dstrGuaranteesOverride, idDataGroup); 

	if ( (!dstrGuaranteesOverride.empty() && dstrGuaranteesOverride == I_("Y")) && 
		  getWorkSession().getMFAccount (idDataGroup, dstrAccountFrom, pMFAccountFrom) <= WARNING  && 
		  getWorkSession().getMFAccount (idDataGroup, dstrAccountTo, pMFAccountTo) <= WARNING)
	{
		if (pMFAccountTo->hasBlankAnnuitantGender(idDataGroup))
		{
			MFAccountHoldingList *pAccountHoldingList = NULL;
			if ( getAccountHoldings (pAccountHoldingList, idDataGroup) <= WARNING && pAccountHoldingList )
			{
				BFObjIter iter (*pAccountHoldingList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
				while (!iter.end ()) 
				{
					iter.getObject()->getField (ifds::rxFundCode, fundCode, idDataGroup);
					iter.getObject()->getField (ifds::rxClassCode, classCode, idDataGroup);
					if ( Trade::validateNMCRContract( pMFAccountFrom, fundCode, classCode, contractType, contractVer, idDataGroup) > WARNING )
						break;
					++iter;
				}
			}
		}
	}

	return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
bool AllTransfer::getContractTypeAndVersion ( const BFDataGroupId &idDataGroup,
											  const DString &dstrAccountNum,	
											  DString &contractType, 
											  DString &contractVer)
{	
	MFAccount *pMFAccount = NULL;
	ContractInfoList* pContractInfoList = NULL;
	DString fundCode, classCode;
	bool bNMCRContract = false;	

	if (getWorkSession().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING)
	{
		MFAccountHoldingList *pAccountHoldingList = NULL;
		if ( getAccountHoldings (pAccountHoldingList, idDataGroup) <= WARNING && pAccountHoldingList )
		{
			BFObjIter iter (*pAccountHoldingList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
			while (!iter.end ()) 
			{
				iter.getObject()->getField (ifds::rxFundCode, fundCode, idDataGroup);
				iter.getObject()->getField (ifds::rxClassCode, classCode, idDataGroup);
				bNMCRContract = hasNMCRContract( pMFAccount, fundCode, classCode, contractType, contractVer, idDataGroup);
				if ( bNMCRContract )
					break;
				++iter;
			}
		}
	}

	return (bNMCRContract);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AllTransfer.cpp-arc  $
// 
//    Rev 1.29   Apr 16 2012 23:18:34   popescu
// 2901148 - Gurantee Flag Override
// 
//    Rev 1.28   20 Aug 2007 17:22:22   popescu
// Incident 972357 - pop a warning message if users do not choose to clone the AMS model
// 
//    Rev 1.27   26 Jul 2007 18:40:14   popescu
// GAP 2 AMS - use isAMSAccount method at the account level
// 
//    Rev 1.26   12 Jul 2007 17:10:04   popescu
// AIM GAP 2 AMS - added an extra field to trading CloneAcctAMS - used in AllTransfer to copy AMS to the to acct.
// 
//    Rev 1.25   Mar 30 2007 14:12:26   jankovii
// PET 2292 FN01 - Switch Settlement.
// 
//    Rev 1.24   Nov 22 2006 09:49:18   popescu
// Simple fix where when modifying a pending trade will set the Amount and AmtType field to read only
// 
//    Rev 1.23   Jun 14 2006 16:19:32   popescu
// PET 2102.FN02 Flex 
// 
//    Rev 1.22   Jun 14 2006 10:52:36   jankovii
// PET2102 FN02 - Manulife Flex  Trade/Systematic Entry.
// 
//    Rev 1.21   May 25 2006 09:42:40   jankovii
// PET 2102 FN02 - Manulife Flex Trade/Systematic Entry.
// 
//    Rev 1.20   Mar 28 2005 10:22:32   popescu
// Incident #270672 -- moved the set of LSIF Code to 'doApplyRelatedChanges' rather then 'doInitWithDefaultValues' - to avoid the call on 'Cancel(s)'
// 
//    Rev 1.19   Mar 24 2005 17:30:10   ZHANGCEL
// Incident #270672 -- Set the default value for LSIF code to "0" for all funds transfers
// 
//    Rev 1.18   Mar 23 2005 16:52:18   ZHANGCEL
// Incident #270672 -- Set the default value for LSIFCode to "0" for all fund trasnsfer
// 
//    Rev 1.17   Dec 17 2004 16:45:04   popescu
// PET 1117/06, fixed: user blocked to book an alltransfer due to to fund/class being set as required
// 
//    Rev 1.16   Dec 07 2004 01:37:28   popescu
// PET 1117/56 trades processing/modify trade
// 
//    Rev 1.15   Dec 03 2004 10:45:58   popescu
// PET 1117/06, fees processing
// 
//    Rev 1.14   Nov 30 2004 20:09:50   popescu
// PET 1117/06
// 
//    Rev 1.13   Nov 14 2004 14:25:46   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.12   Nov 06 2004 00:39:52   popescu
// PET 1117/06, synch changes
// 
//    Rev 1.2   Nov 04 2004 17:37:06   popescu
// PET 1117/06, Trade processing
// 
//    Rev 1.1   Nov 02 2004 19:19:20   popescu
// PET 1117/06 Trade processing...
// 
//    Rev 1.0   Oct 29 2004 20:27:42   popescu
// Initial revision.
// 
//    Rev 1.0   Oct 01 2004 19:30:04   popescu
// Initial revision.
 * 
 *    Rev 1.566   Sep 21 2004 16:02:32   popescu
  * Initial revision.
// 
// 
*/
