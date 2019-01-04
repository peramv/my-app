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
// ^FILE   : Exchange.cpp
// ^AUTHOR : Serban Popescu   
// ^DATE   : September, 2004
//
// ^CLASS    : Exchange - 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "exchange.hpp"

#include "accountentityxref.hpp"
#include "funddetail.hpp"
#include "fundmasterlist.hpp"
#include "fundtolist.hpp"
#include "mfaccount.hpp"
#include "mgmtco.hpp"
#include "redemptionvalidation.hpp"
#include "taxtyperule.hpp"
#include "seqfundvalidation.hpp"
#include "shareholder.hpp"
#include "AMSMstrList.hpp"
#include "amsmstrinfo.hpp"

namespace ifds
{
//management company options
   extern CLASS_IMPORT const BFTextFieldId DefaultAllocOverride;
   extern CLASS_IMPORT const BFTextFieldId TitleRestrict;
   extern CLASS_IMPORT const BFTextFieldId DftOrdTypeDSK;
   extern CLASS_IMPORT const BFIntegerFieldId DftOrdTypeEX;
//subst sets
//account fields
   extern CLASS_IMPORT const BFTextFieldId AMSCode;
   extern CLASS_IMPORT const BFTextFieldId BrokerCode;
   extern CLASS_IMPORT const BFTextFieldId BranchCode;
   extern CLASS_IMPORT const BFTextFieldId Slsrep;
   extern CLASS_IMPORT const BFTextFieldId TaxType;
   extern CLASS_IMPORT const BFTextFieldId MaxApplies;
//fund fields
   extern CLASS_IMPORT const BFTextFieldId LoadType;
//unrelated
   extern CLASS_IMPORT const BFTextFieldId MaximumApplies;
   extern CLASS_IMPORT const BFTextFieldId AmntOverMax;
   extern CLASS_IMPORT const BFTextFieldId FromCurrency;
   extern CLASS_IMPORT const BFTextFieldId DftOrdType;
   extern CLASS_IMPORT const BFTextFieldId DepAllowed;
   extern CLASS_IMPORT const BFTextFieldId PFCrystalisation;
   extern CLASS_IMPORT const BFTextFieldId ToCurrency;
   extern CLASS_IMPORT const BFTextFieldId GIRedemOrder;
   extern CLASS_IMPORT const BFTextFieldId GIRedemAmountType;

   extern CLASS_IMPORT const BFTextFieldId AmtTypeRedemption;
   extern CLASS_IMPORT const BFTextFieldId AmtTypeMultiCurrency;
   extern CLASS_IMPORT const BFNumericFieldId ShrNum;
   extern CLASS_IMPORT const BFTextFieldId FundRelnCode;
   extern CLASS_IMPORT const BFTextFieldId AMSCode;
   extern CLASS_IMPORT const BFTextFieldId ToSoftCapCheck;
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const EXCHANGE;
   extern CLASS_IMPORT I_CHAR * const EXCHANGE_OUT;
   extern CLASS_IMPORT I_CHAR * const EXCHANGE_IN;
}

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME = I_ ("Exchange");
   const I_CHAR * const WIRE        = I_( "Y" );
   const I_CHAR * const DIRECT      = I_( "N" );
   const I_CHAR * const DEFAULT_REDEMPTION_ORDER   = I_("FM");
   const I_CHAR * const EMPLOYEE                   = I_("08");
   const I_CHAR * const AGENT                      = I_("09");
   const I_CHAR * const YES                        = I_("Y");
   const I_CHAR * const REDEMPTION_CODE_UC		   = I_("UC");	
   const I_CHAR * const DEPOSIT_CODE_UC		       = I_("90");
}

namespace CND
{
   extern const long AMS_ERR_EXCHANGE_NOT_ALLOWED;
   extern const long ERR_FUND_CLASS_EXCHANGEOUT_STOP_FLAG_ON;
   extern const long ERR_WARN_FUND_CLASS_EXCHANGEOUT_STOP_FLAG_ON;
   extern const long ERR_FUND_CLASS_EXCHANGEIN_STOP_FLAG_ON;
   extern const long ERR_WARN_FUND_CLASS_EXCHANGEIN_STOP_FLAG_ON;
   extern const long ERR_SAME_FROM_TO_FUND_CLASS_NOT_ALLOW;
   extern const long ERR_MAX_PAYMENT_EXCEED;
   extern const long WARN_MAX_PAYMENT_EXCEED;
   extern const long ERR_AT_COST_ALLOCATION_NOT_ALLOWED;
   extern const long ERR_CLOSED_COUNTRY_RESIDENT_FOR_MONEY_IN; 
   extern const long ERR_DEPOSITS_NOT_ALLOWED;
   extern const long ERR_FROM_TO_CLASSES_NOT_BELONG_TO_SAME_FUND;
   extern const long WARN_FROM_TO_CLASSES_NOT_BELONG_TO_SAME_FUND;
   extern const long ERR_FX_RATE_IS_EMPTY;
   extern const long WARN_FX_RATE_IS_EMPTY;
   extern const long ERR_NONRES_EXCHANGE_NOT_ALLOWED;
   extern const long ERR_FUND_CLASS_NOT_ALLOWED_TO_EXCHANGE;
   extern const long WARN_FUND_CLASS_NOT_ALLOWED_TO_EXCHANGE;
   extern const long ERR_RECEIVING_ACCT_AMS_MODEL_NOT_CONTAIN_THIS_FUND_CLASS_AS_CHILD;
   extern const long WARN_RECEIVING_ACCT_AMS_MODEL_NOT_CONTAIN_THIS_FUND_CLASS_AS_CHILD;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const AMS_MIX_OVERRIDE;
}

namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const MAXIMUM_PAYOUT_AMOUNT_IS_EXCEEDED;
   extern CLASS_IMPORT I_CHAR * const FROM_TO_CLASSES_NOT_BELONG_TO_SAME_FUND;
   extern CLASS_IMPORT I_CHAR * const FX_RATE_IS_EMPTY;
   extern CLASS_IMPORT I_CHAR * const FUND_CLASS_NOT_ALLOWED_TO_EXCHANGE;
   extern CLASS_IMPORT I_CHAR * const RECEIVING_ACCT_AMS_MODEL_NOT_CONTAIN_THIS_FUND_CLASS_AS_CHILD;
}

//******************************************************************************
Exchange::Exchange (BFAbstractCBO &parent) : Transfer (parent)
{
   TRACE_CONSTRUCTOR ( CLASSNAME, 
                       NULL_STRING
                     );
}

//******************************************************************************
Exchange::~Exchange ()
{
   TRACE_DESTRUCTOR (CLASSNAME);
}     

SEVERITY Exchange::doInit (const BFData &data)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doInit"));

   Transfer::doInit (data);

   giAttribRelatedChanges (BF::HOST);
   setFieldReadOnly (ifds::SDRTExemptCode,BF::HOST, true); 
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Exchange::doInit (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doInit"));

   setFieldNoValidate ( ifds::TradesTransType, 
                        TRADETYPE::EXCHANGE, 
                        idDataGroup, 
                        false);

   setFieldReadOnly (ifds::GrossOrNet, idDataGroup, true);

   setFieldSubstituteValues(ifds::RedemOrder, idDataGroup, ifds::GIRedemOrder);

   if(isGIInvestmentListApplicable(idDataGroup))
   {
      setFieldReadOnly( ifds::RedemOrder, idDataGroup, false);
      setFieldSubstituteValues(ifds::AmtType, idDataGroup, ifds::GIRedemAmountType);
      DString redemOrder;
      getField( ifds::RedemOrder, redemOrder, idDataGroup, false);
      if(isNew())
         setFieldNoValidate ( ifds::RedemOrder, DEFAULT_REDEMPTION_ORDER, idDataGroup, false);
   }
   else
   {
      setFieldNoValidate ( ifds::RedemOrder, I_(""), idDataGroup, false);
      setFieldReadOnly( ifds::RedemOrder, idDataGroup, true);
      setFieldSubstituteValues ( ifds::AmtType, idDataGroup, _multiCurrency == Y ? ifds::AmtTypeMultiCurrency : ifds::AmtTypeRedemption);

   }

   setFieldReadOnly (ifds::SDRTExemptCode, idDataGroup, true);  
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
bool Exchange::isAccountCloningAllowed (const BFDataGroupId &idDataGroup)
{
   return false;
}

//******************************************************************************
SEVERITY Exchange::preInitWithDefaultValues (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("preInitWithDefaultValues"));
   Transfer::preInitWithDefaultValues (idDataGroup);
//account to is a required and read only field
   setFieldRequired (ifds::AccountTo, idDataGroup, true);
   setFieldValid (ifds::AccountTo, idDataGroup, false); //force validation
   setFieldReadOnly (ifds::AccountTo, idDataGroup, true);
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
void Exchange::doInitWithDefaultValues (const BFDataGroupId &idDataGroup)
{
   Transfer::doInitWithDefaultValues (idDataGroup);
   setFieldNoValidate ( ifds::SDRTExemptCode, NULL_STRING, idDataGroup, false, 
                        true, true);
   setFieldReadOnly (ifds::SDRTExemptCode, idDataGroup, true);

   addBlankToSubSet (ifds::Deconversion, idDataGroup);
   setFieldNoValidate (ifds::Deconversion, I_("N"), idDataGroup, false);
   if (isNew())
   {
	   setFieldReadOnly( ifds::Deconversion, idDataGroup, false );
   }
}

//***************************************************************************************************
SEVERITY Exchange::doApplyRelatedChanges ( const BFFieldId &idField, 
                                           const BFDataGroupId &idDataGroup) 
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doApplyRelatedChanges"));

   if (Transfer::doApplyRelatedChanges (idField, idDataGroup) <= WARNING)
   {
      if (idField == ifds::AccountNum)
      {
         DString accountNum;

         getField (ifds::AccountNum, accountNum, idDataGroup, false);
         setFieldNoValidate ( ifds::AccountTo, accountNum, idDataGroup, false,
                              false,
                              true); //notify observers
      }
	  if (idField == ifds::DepositType || idField == ifds::RedCode)
	  {
		  DString dstrDepositType, dstrRedCode;
		  
		  getField (ifds::DepositType, dstrDepositType, idDataGroup, false);
		  getField (ifds::RedCode, dstrRedCode, idDataGroup, false);

	     if ( REDEMPTION_CODE_UC == dstrRedCode  &&  DEPOSIT_CODE_UC != dstrDepositType )
	     {
	        setFieldNoValidate(ifds::DepositType, DEPOSIT_CODE_UC , idDataGroup, false, false,true);
	     }
	  }

   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Exchange::doValidateField ( const BFFieldId &idField, 
                                     const DString &strValue, 
                                     const BFDataGroupId &idDataGroup) 
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("doValidateField"));
   if (Transfer::doValidateField (idField, strValue, idDataGroup) <= WARNING)
   {
      if (idField == ifds::FromFund || idField == ifds::ToFund)
      {
         validateGIAToDIFExchange (idDataGroup);
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//***************************************************************************************************
SEVERITY Exchange::validateOrderType ( const DString &orderType,
                                       const BFDataGroupId &idDataGroup
                                     )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateOrderType"));

   return GETCURRENTHIGHESTSEVERITY();
} 

//******************************************************************************
SEVERITY Exchange::validateAccount ( MFAccount *pMFAccount, 
                                     const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateAccount"));
   if (Transfer::validateAccount (pMFAccount, idDataGroup) <= WARNING)
   {
      DString amsCode;

      pMFAccount->getField (ifds::AMSCode, amsCode, idDataGroup);
      // The account is an AMS account if the AMS Code is not NULL
      if (amsCode != NULL_STRING) 
      {
         //Check User security band.
         DString amsCode,
            defAllocOverride;

         getWorkSession ().getOption ( ifds::DefaultAllocOverride, 
                                       defAllocOverride, 
                                       idDataGroup, 
                                       false); 
         if (defAllocOverride == I_("Y") && 
               !getWorkSession ().hasUpdatePermission (UAF::AMS_MIX_OVERRIDE)) 
         {
            ADDCONDITIONFROMFILE (CND::AMS_ERR_EXCHANGE_NOT_ALLOWED);
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Exchange::canAccountToTrade ( MFAccount *pMFAccountTo, 
                                       const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("canAccountToTrade"));
//calls base class, skip transfer logic,
   if (Trade::canAccountToTrade (pMFAccountTo, idDataGroup) <= WARNING)
   {
      DString tradeDate;

      getField (ifds::EffectiveDate, tradeDate, idDataGroup);
      pMFAccountTo->canTrfExchIn (tradeDate, idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Exchange::validateAccountTo ( MFAccount *pMFAccountTo, 
                                       const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateAccountTo"));
//calls base class, skip transfer logic, no need to be executed
   if (Trade::validateAccountTo (pMFAccountTo, idDataGroup) <= WARNING)
   {
      validateTransferToLIRA (idDataGroup);
      validateTransferToLRSP (idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//****************************************************************************** 
SEVERITY Exchange::validateFundClass ( const DString &fundCode, 
                                       const DString &classCode, 
                                       const DString &accountNum, 
                                       const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateFundClass"));

   if (Trade::validateFundClass ( fundCode, 
                                  classCode, 
                                  accountNum, 
                                  idDataGroup) <= WARNING)
   {
//get the values of broker/branch/sales rep from trade (the 'from side')
      DString broker,
         branch,
         agent;

      getField (ifds::Broker, broker, idDataGroup);
      getField (ifds::Branch, branch, idDataGroup);
      getField (ifds::SlsrepCode, agent, idDataGroup);
      canFundTrade ( broker,
                     branch,
                     agent,
                     TRADETYPE::EXCHANGE_OUT,
                     accountNum,
                     fundCode,
                     classCode,
                     CND::ERR_FUND_CLASS_EXCHANGEOUT_STOP_FLAG_ON,
                     CND::ERR_WARN_FUND_CLASS_EXCHANGEOUT_STOP_FLAG_ON,
                     idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//****************************************************************************** 
SEVERITY Exchange::validateToFundClass ( const DString &fundCode, 
                                         const DString &classCode, 
                                         const DString &accountNum, 
                                         const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateToFundClass"));

   if (Trade::validateToFundClass ( fundCode, 
                                    classCode, 
                                    accountNum, 
                                    idDataGroup) <= WARNING)
   {
      if (GETCURRENTHIGHESTSEVERITY() <= WARNING)
      {
   //get the values of broker/branch/sales rep to account (the 'to side')
         MFAccount *pMFAccountTo = NULL;
         if ( getWorkSession().getMFAccount ( idDataGroup, 
                                              accountNum, 
                                              pMFAccountTo) <= WARNING &&
              pMFAccountTo)
         {
            DString broker,
               branch,
               agent;
//exchange broker gets taken from trade
            getField (ifds::Broker, broker, idDataGroup);
            getField (ifds::Branch, branch, idDataGroup);
            getField (ifds::SlsrepCode, agent, idDataGroup);
            if (canFundTrade ( broker,
                               branch,
                               agent,
                               TRADETYPE::EXCHANGE_IN,
                               accountNum,
                               fundCode,
                               classCode,
                               CND::ERR_FUND_CLASS_EXCHANGEIN_STOP_FLAG_ON,
                               CND::ERR_WARN_FUND_CLASS_EXCHANGEIN_STOP_FLAG_ON,
                               idDataGroup) <= WARNING)
            {
               bool bEmpty = fundCode.empty () && classCode.empty () ? true : false;

               if (!bEmpty && !isHypo())
               {
                  // PET 1334: View will check if to/from funds are the same for Transfers.  
                  // If funds are the same then view will check if there was existing EUSD Override on the In-Fund transaction, 
                  // if yes, then trade is subject to EUSD and error 464 will be raised.  

                  validateEUSDBackdates( fundCode, classCode, accountNum, idDataGroup );
               }

               moreValidateToFundClass (fundCode, classCode, idDataGroup);
            }
         }

         validateFundToWithSegValidation(idDataGroup) ;
         revalidateField(ifds::ToSoftCapCheck, idDataGroup);
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************************************
SEVERITY Exchange::validateFromToFundClass ( const DString &fromFund,
                                             const DString &fromClass,
                                             const DString &toFund,
                                             const DString &toClass,
                                             const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateFromToFundClass"));

// do not allow if exchange to same fund and same class
   if (toFund == fromFund && toClass == fromClass)
   {
      ADDCONDITIONFROMFILE (CND::ERR_SAME_FROM_TO_FUND_CLASS_NOT_ALLOW);
   }

   Transfer::validateFromToFundClass ( fromFund,
                                       fromClass,
                                       toFund,
                                       toClass,
                                       idDataGroup);

   FundToList fundToList (*this );

   if( !fundToList.isExchangeAllowed( fromFund,
                                      fromClass,
                                      toFund,
                                      toClass) )
   {
      // raise up reject error here
      DString dstrIDI;
      addIDITagValue( dstrIDI, I_("FRMFUND"), fromFund );
      addIDITagValue( dstrIDI, I_("FRMCLASS"), fromClass );
      addIDITagValue( dstrIDI, I_("TOFUND"), toFund );
      addIDITagValue( dstrIDI, I_("TOCLASS"), toClass );
      getErrMsg ( IFASTERR::FUND_CLASS_NOT_ALLOWED_TO_EXCHANGE, 
                  CND::ERR_FUND_CLASS_NOT_ALLOWED_TO_EXCHANGE, 
                  CND::WARN_FUND_CLASS_NOT_ALLOWED_TO_EXCHANGE, 
                  idDataGroup,
                  dstrIDI);
   }

   return GETCURRENTHIGHESTSEVERITY(); 
}

//****************************************************************************** 
SEVERITY Exchange::validateMasterActAMS(const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateMasterActAMS"));

    DString dstrFundCode, dstrClassCode, dstrAccountTo, dstrTradeDate;
    MFAccount *pMFAccountTo = NULL;
    FundDetail *pFundDetailTo = NULL;
    AMSMstrList *pAMSMstrListTo = NULL;
    AmsMstrInfo *pAMSMstrInfoTo = NULL;

    getField(ifds::AccountTo, dstrAccountTo, idDataGroup);
    getField(ifds::EffectiveDate, dstrTradeDate, idDataGroup, false);

    if (getWorkSession().getMFAccount(idDataGroup, dstrAccountTo, pMFAccountTo) <= WARNING && pMFAccountTo &&
        pMFAccountTo->isAMSAccount(idDataGroup) &&
        pMFAccountTo->getAMSMstrList(pAMSMstrListTo, idDataGroup,  dstrTradeDate) <= WARNING && pAMSMstrListTo)
    {
        DString dstrAcctFromAMSCode, dstrAcctToAMSCode, dstrTradeDate/*, dstrFromFund, dstrFromClass*/;
        DString dstrToFund, dstrToClass;

        pMFAccountTo->getField(ifds::AMSCode, dstrAcctToAMSCode, idDataGroup);

        getField(ifds::ToFund, dstrToFund, idDataGroup);
        getField(ifds::ToClass, dstrToClass, idDataGroup);

        pAMSMstrListTo->getAMSMstrInfo(I_("RB"), dstrAcctToAMSCode, dstrTradeDate, pAMSMstrInfoTo, idDataGroup);

        if (getWorkSession().getFundDetail(dstrToFund, dstrToClass, idDataGroup, pFundDetailTo) && pFundDetailTo)
        {
            if (pFundDetailTo->isAMSChildFund(idDataGroup) &&
                !pAMSMstrInfoTo->isFundInAMS(dstrToFund, dstrToClass, idDataGroup))
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

//***********************************************************************************
SEVERITY Exchange::validateMinFromFundAmount ( const DString &accountNum,
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
   DString currency, 
           dstrDepositType, //in1419539
           initPurch,
		   tradeDate;

//the 'from side'
   getField (ifds::FromCurrency, currency, idDataGroup);
   getField (ifds::EffectiveDate, tradeDate, idDataGroup,false);

   DString dstrToFund, dstrToClass;
   bool isFullExchgParentToParent;

   getField(ifds::ToFund, dstrToFund, idDataGroup);
   getField(ifds::ToClass, dstrToClass, idDataGroup);
   isFullExchgParentToParent = isFullExchgParentFndClsToParentFndCls(idDataGroup, fundCode, classCode, dstrToFund, dstrToClass);

   fundClassTradeMinimumAmtCheck ( TRADETYPE::EXCHANGE_OUT,
                                   accountNum,
                                   fundCode,
                                   classCode,
                                   amtType,
                                   amount,
                                   currency,
                                   initPurch,
                                   broker,
                                   branch,
                                   slsrep,
                                   depositType, //in1419539
								   tradeDate,
                                   idDataGroup,
                                   isFullExchgParentToParent);
   return GETCURRENTHIGHESTSEVERITY();
}

//***********************************************************************************
SEVERITY Exchange::validateMinToFundAmount ( const DString &accountNum,
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
   
   DString currency,
           initPurch,tradeDate;

   getField (ifds::FromCurrency, currency, idDataGroup);
   getField (ifds::TradeInDate, tradeDate, idDataGroup, false);

   bool bOverrideFundLevelCheck = false;
//first check ams
   amsMinAmtCheck ( TRADETYPE::EXCHANGE_IN,
                    accountNum,
                    fundCode, 
                    classCode,
                    amtType, 
                    amount, 
                    currency,
                    broker,
                    branch,
                    slsrep,
                    depositType, //in1419539
                    bOverrideFundLevelCheck,
					tradeDate,
                    idDataGroup);

   if (!bOverrideFundLevelCheck && GETCURRENTHIGHESTSEVERITY () <= WARNING)
   {
      double dec_amount = DSTCommonFunctions::convertToDouble (amount);
      DString dstrFromFund, dstrFromClass;
      bool isFullExchgParentToParent = false;

      getField(ifds::FromFund, dstrFromFund, idDataGroup);
      getField(ifds::FromClass, dstrFromClass, idDataGroup);
      isFullExchgParentToParent = isFullExchgParentFndClsToParentFndCls(idDataGroup, dstrFromFund, dstrFromClass, fundCode, classCode);

      if (dec_amount != 0)
      {
         fundClassTradeMinimumAmtCheck ( TRADETYPE::EXCHANGE_IN,
                                         accountNum,
                                         fundCode,
                                         classCode,
                                         amtType,
                                         amount,
                                         currency,
                                         initPurch,
                                         broker,
                                         branch,
                                         slsrep,
                                         depositType, //in1419539
										 tradeDate,
                                         idDataGroup,
                                         isFullExchgParentToParent);
      }
   }
   return GETCURRENTHIGHESTSEVERITY ();
}


//******************************************************************************
SEVERITY Exchange::getAtCostTIKStatus ( const BFDataGroupId& idDataGroup, 
								                const DString& dstrFundCodeIn, 
					            		       const DString& dstrClassCodeIn,
											       bool  blInAllocation,
			                               bool &blIsAtCostTIK )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "getAtCostTIKStatus" ) );
	bool blAtCostTIKAllowed = true;

   DString dstrFromFund, 
      dstrToFund( dstrFundCodeIn), 
      dstrFromClass, 
      dstrToClass( dstrClassCodeIn );

   getField( ifds::FromFund,  dstrFromFund,  idDataGroup, false);   
   if( dstrToFund.strip().upperCase().empty() )
   {
      getField( ifds::ToFund,    dstrToFund,    idDataGroup, false);  	
   }
   getField( ifds::FromClass, dstrFromClass, idDataGroup, false);
   if( dstrToClass.strip().upperCase().empty() )
   {
      getField( ifds::ToClass,   dstrToClass,   idDataGroup, false);
   }

   if ( dstrFromFund.stripAll()  == dstrToFund.stripAll() )
   {
	   DString dstrFromLoad, 
         dstrToLoad;
	   FundDetail *pFundDetail = NULL;
   	
      if (getWorkSession().getFundDetail (
            dstrFromFund, dstrFromClass, idDataGroup, pFundDetail) && 
			   pFundDetail)
	   {  
		   pFundDetail->getField (ifds::LoadType, dstrFromLoad, BF::HOST, false);
	   }

      pFundDetail=NULL;

      if( getWorkSession().getFundDetail (
            dstrToFund, dstrToClass, idDataGroup, pFundDetail) && 
			   pFundDetail )
	   { 
		   pFundDetail->getField (ifds::LoadType, dstrToLoad, BF::HOST, false);
	   }
	   if( dstrFromLoad.strip().upperCase() == dstrToLoad.strip().upperCase() )
	   {
			   if ( blInAllocation )
            {
				   blAtCostTIKAllowed = false;
            }
			   else
            {
				   blIsAtCostTIK = true; 
            }
	   }
   }
   if ( !blAtCostTIKAllowed )
   {
      ADDCONDITIONFROMFILE( CND::ERR_AT_COST_ALLOCATION_NOT_ALLOWED );
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Exchange::validateTIKRedCodes ( const DString &redCode,
                                         const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_( "validateTIKRedCodes" ) );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Exchange::validateAmountAmtType (const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateAmountAmtType"));
   if (Transfer::validateAmountAmtType (idDataGroup) <= WARNING)
   {
		RedemptionValidation *pRedemptionValidation = NULL;
      MFAccount *pMFAccount = NULL;


      if ( getRedemptionValidation (pRedemptionValidation, idDataGroup) <= WARNING &&
           getAccount (pMFAccount, idDataGroup) <= WARNING &&
           pMFAccount)
      {
         DString amntOverMax,
            maxApplies,
            taxType;

         pRedemptionValidation->getField (ifds::AmntOverMax, amntOverMax, idDataGroup);
         pMFAccount->getField (ifds::MaxApplies, maxApplies, idDataGroup);
         pMFAccount->getField (ifds::TaxType, taxType, idDataGroup);

			if ( amntOverMax == I_("Y") && 
              ( getWorkSession ().isLIFLike (taxType) ||  //LIF
                taxType == I_("L")     //LRIF
              ) && 
              maxApplies == I_("Y"))
			{
             getErrMsg ( IFASTERR::MAXIMUM_PAYOUT_AMOUNT_IS_EXCEEDED, 
                         CND::ERR_MAX_PAYMENT_EXCEED, 
                         CND::WARN_MAX_PAYMENT_EXCEED, 
                         idDataGroup);
			}
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************************************
bool Exchange::isEscrowTaxTypeRIFTransferApplicable (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("isEscrowTaxTypeRIFTransferApplicable"));
   return getEscrowFundClassState (idDataGroup) == 1;
}

//******************************************************************************
SEVERITY Exchange::canAccountTrade ( MFAccount *pMFAccount, 
                                     const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("canAccountTrade"));
//calls base class, 
   if (Trade::canAccountTrade (pMFAccount, idDataGroup) <= WARNING)
   {
      DString tradeDate;

      getField (ifds::EffectiveDate, tradeDate, idDataGroup);
      if (pMFAccount->canTrfExchOut (tradeDate, idDataGroup) <= WARNING)
      {
         pMFAccount->exchEscrow (tradeDate, idDataGroup);
      }
      
      DString accountNum;

      pMFAccount->getField (ifds::AccountNum, accountNum, idDataGroup, false);
      validateClosedCountry (accountNum, idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
bool Exchange::isWireSupported (const BFDataGroupId &idDataGroup)
{
	DString	dftOrdTypeDSK;

	getWorkSession ().getOption ( ifds::DftOrdTypeDSK, dftOrdTypeDSK, idDataGroup, false);
	bool supported = dftOrdTypeDSK == I_("Y");

	if (supported)
	{
		DString dftOrdTypeTREX;

		getWorkSession ().getOption (ifds::DftOrdTypeEX, dftOrdTypeTREX, idDataGroup, false);
		supported = dftOrdTypeTREX != I_("0");

	}
	return supported;
}

//******************************************************************************
SEVERITY Exchange::setDefaultOrderType (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("setDefaultOrderType"));

   DString fromFund, 
      toFund, 
      fromClass, 
      toClass;

   getField (ifds::FromFund, fromFund,   idDataGroup, false );
   getField (ifds::FromClass, fromClass,  idDataGroup, false );
   getField (ifds::ToFund, toFund, idDataGroup);
   getField (ifds::ToClass, toClass, idDataGroup);

   if ( !fromFund.empty () && !fromClass.empty () &&
        !toFund.empty () && !toClass.empty ())
   {
      DString fromDefaultOrderType,
         toDefaultOrderType;
      FundDetail	*pFundDetail  (NULL),
         *pFundToDetail (NULL);
      if ( getWorkSession().getFundDetail (fromFund, fromClass, idDataGroup, pFundDetail) && 
           pFundDetail)
      {
         pFundDetail->getField (ifds::DftOrdType, fromDefaultOrderType, idDataGroup);
      }
      if ( getWorkSession().getFundDetail (toFund, toClass, idDataGroup, pFundToDetail) &&
           pFundToDetail)
      {
         pFundToDetail->getField (ifds::DftOrdType, toDefaultOrderType, idDataGroup);
      }

      DString orderType;

      if (!fromDefaultOrderType.empty () && !toDefaultOrderType.empty ())
      {

         if (fromDefaultOrderType == toDefaultOrderType)
         {
            orderType = fromDefaultOrderType == I_("D") ? I_("N") : I_("Y");
         }
         else 
         {
            orderType = I_("N"); //direct
         }
      }
      else
      {
         orderType = batchOrderType;
      }

     setFieldNoValidate ( ifds::OrderType, orderType, idDataGroup, false, 
        false, true, //notify
        true);
     //at this point, orderType may be blank (batchOrderType is always blank for pending trade)
     setFieldRequired( ifds::OrderType, idDataGroup, true );
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Exchange::validateToSoftCapCheck (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateToSoftCapCheck "));

   DString accountTo,
      toFund,
      toClass;

   getField (ifds::AccountTo, accountTo, idDataGroup, false);
   getField (ifds::ToFund, toFund, idDataGroup, false);
   getField (ifds::ToClass, toClass, idDataGroup, false);
   fundClassSoftCapCheck (TRADETYPE::EXCHANGE_IN, accountTo, toFund, toClass, idDataGroup);   

   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY Exchange::validateGIAToDIFExchange (const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateGIAToDIFExchange "));

	DString dstrAccountFrom;
	DString dstrFromFund;
	DString dstrToFund;

	getField (ifds::AccountNum, dstrAccountFrom, idDataGroup, false);
	getField (ifds::FromFund, dstrFromFund, idDataGroup, false);
	getField (ifds::ToFund, dstrToFund, idDataGroup, false);

	if (!dstrFromFund.empty () && !dstrToFund.empty ())
	{
		bool bFromFundGIA = isGIAFund (dstrFromFund);
		bool bToFundDIF = isDIFFund (dstrToFund);

		if (bFromFundGIA && bToFundDIF)
		{
			MFAccount *pMFAccount = NULL;

			if (getWorkSession().getMFAccount (idDataGroup, dstrAccountFrom, pMFAccount)  <= WARNING  && pMFAccount) 
			{
				DString dstrNonRegNonResident;

				pMFAccount->isNonRegNonResident(dstrNonRegNonResident, idDataGroup);

				if (dstrNonRegNonResident == YES)
				{
					ADDCONDITIONFROMFILE (CND::ERR_NONRES_EXCHANGE_NOT_ALLOWED);
				}
			}
		}
	}

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Exchange::validateClosedCountryForPendingTrades (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateClosedCountryForPendingTrades"));

   DString accountNum;

   getField (ifds::AccountNum, accountNum, idDataGroup);
   validateClosedCountry (accountNum, idDataGroup);

   return GETCURRENTHIGHESTSEVERITY ();
}
//******************************************************************************
bool Exchange::areRESPBenefAllocationsAllowed (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("areRESPBenefAllocationsAllowed"));

   return false;
}
//******************************************************************************
bool Exchange::isRESPTransferAllowed (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("isRESPTransferAllowed"));

   return false;
}
//******************************************************************************
bool Exchange::isRDSPTransferAllowed (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("isRDSPTransferAllowed"));

   return false;
}

//******************************************************************************
SEVERITY Exchange::validateRESPtoRESPTransfer(const DString& strDepType, 
                                              const DString& strRedCode, 
                                              const DString& strTaxTypeFrom, 
                                              const DString& strTaxTypeTo, 
                                              const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_("validateRESPtoRESPTransfer"));

   if (strDepType != I_("1") && strRedCode != I_("01") )
   {
      Transfer::validateRESPtoRESPTransfer(strDepType,
                                          strRedCode,
                                          strTaxTypeFrom,
                                          strTaxTypeTo,
                                          idDataGroup);
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Exchange::validateLinkedEntity(const DString& strValue, const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateLinkedEntity"));

   return GETCURRENTHIGHESTSEVERITY ();
}


SEVERITY Exchange::validateMoneyMktFund(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validateMoneyMktFund"));

   DString dstrFromFund, dstrFromClass, dstrToFund, dstrToClass;
   bool bFullExchPrntToPrnt;

   getField(ifds::FromFund, dstrFromFund, idDataGroup);
   getField(ifds::FromClass, dstrFromClass, idDataGroup);
   getField(ifds::ToFund, dstrToFund, idDataGroup);
   getField(ifds::ToClass, dstrToClass, idDataGroup);
   bFullExchPrntToPrnt = isFullExchgParentFndClsToParentFndCls(idDataGroup, dstrFromFund, dstrFromClass, dstrToFund, dstrToClass);
     	
   editCheckOnMMF( TRADETYPE::EXCHANGE_OUT, bFullExchPrntToPrnt, idDataGroup);

   return GETCURRENTHIGHESTSEVERITY ();		
}
//******************************************************************************
SEVERITY Exchange::PFCrystalisationRelatedChanges (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("PFCrystalisationRelatedChanges "));

   DString dstrFromFund = NULL_STRING, 
		   dstrToFund	= NULL_STRING, 
		   dstrFromClass= NULL_STRING,
		   dstrToClass	= NULL_STRING;
   
   getField (ifds::FromFund, dstrFromFund, idDataGroup, false);
   getField (ifds::FromClass, dstrFromClass, idDataGroup, false);
   getField (ifds::ToFund, dstrToFund, idDataGroup, false);
   getField (ifds::ToClass, dstrToClass, idDataGroup, false);

   bool bFromIsPF = getWorkSession ().isPerfFeeFund(dstrFromFund,dstrFromClass,idDataGroup);
   bool bToIsPF   = getWorkSession ().isPerfFeeFund(dstrToFund,dstrToClass,idDataGroup);
   bool bEnable   = bFromIsPF && bToIsPF;
   

   if( (bFromIsPF && bToIsPF) || (bFromIsPF && !bToIsPF) )
   {
	   setFieldNoValidate (ifds::PFCrystalisation, I_("03"), idDataGroup, false, false, false);
   }
   else
   {
	   setFieldNoValidate (ifds::PFCrystalisation, I_("01"), idDataGroup, false, false, false);
   }
   setFieldReadOnly (ifds::PFCrystalisation, idDataGroup, !bEnable);
            
   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY Exchange::validatePerfFeeFromToClassesWithFund (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validatePerfFeeFromToClassesWithFund"));
   
   DString dstrFromFund = NULL_STRING, 
		   dstrToFund	= NULL_STRING, 
		   dstrFromClass= NULL_STRING,
		   dstrToClass	= NULL_STRING;
   
   getField (ifds::FromFund, dstrFromFund, idDataGroup, false);
   getField (ifds::FromClass, dstrFromClass, idDataGroup, false);
   getField (ifds::ToFund, dstrToFund, idDataGroup, false);
   getField (ifds::ToClass, dstrToClass, idDataGroup, false);

   bool bFromIsPF = getWorkSession ().isPerfFeeFund(dstrFromFund,dstrFromClass,idDataGroup);
   bool bToIsPF   = getWorkSession ().isPerfFeeFund(dstrToFund,dstrToClass,idDataGroup);

   if( bFromIsPF && bToIsPF )
   {
	   DString dstrRedCode, dstrPFCrystalisation;
	   getField (ifds::RedCode, dstrRedCode, idDataGroup, false);
	   getField (ifds::PFCrystalisation, dstrPFCrystalisation, idDataGroup, false);

	   if( (dstrRedCode == I_("25") || dstrRedCode == I_("27")) && (dstrPFCrystalisation==I_("02")) )
	   {
		   if ( dstrFromFund != dstrToFund)
		   {
			    getErrMsg ( IFASTERR::FROM_TO_CLASSES_NOT_BELONG_TO_SAME_FUND,
						CND::ERR_FROM_TO_CLASSES_NOT_BELONG_TO_SAME_FUND,
						CND::WARN_FROM_TO_CLASSES_NOT_BELONG_TO_SAME_FUND,
						idDataGroup );
		   }
	   }
   }
   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY Exchange::validatePerfFeeFXRate (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("validatePerfFeeFXRate"));

   DString dstrFromFund = NULL_STRING, 
		   dstrToFund	= NULL_STRING, 
		   dstrFromClass= NULL_STRING,
		   dstrToClass	= NULL_STRING;
   
   getField (ifds::FromFund, dstrFromFund, idDataGroup, false);
   getField (ifds::FromClass, dstrFromClass, idDataGroup, false);
   getField (ifds::ToFund, dstrToFund, idDataGroup, false);
   getField (ifds::ToClass, dstrToClass, idDataGroup, false);

   bool bFromIsPF = getWorkSession ().isPerfFeeFund(dstrFromFund,dstrFromClass,idDataGroup);
   bool bToIsPF   = getWorkSession ().isPerfFeeFund(dstrToFund,dstrToClass,idDataGroup);

   if( bFromIsPF && bToIsPF )
   {
	   DString dstrRedCode, dstrPFCrystalisation;
	   getField (ifds::RedCode, dstrRedCode, idDataGroup, false);
	   getField (ifds::PFCrystalisation, dstrPFCrystalisation, idDataGroup, false);

	   if( dstrRedCode != I_("01") && dstrPFCrystalisation==I_("02") )
	   {
		   DString dstrFromCurrency, dstrToCurrency;
		   getField (ifds::FromCurrency, dstrFromCurrency, idDataGroup, false);
	       getField (ifds::ToCurrency, dstrToCurrency, idDataGroup, false);
		   
		   if ( dstrFromCurrency != dstrToCurrency)
		   {
			   DString dstrExchRate;
			   getField (ifds::ExchRate, dstrExchRate, idDataGroup, false);
			   double dec_exchRate = DSTCommonFunctions::convertToDouble (dstrExchRate);
			   if( dstrExchRate == 0 )
			   {
				   getErrMsg ( IFASTERR::FX_RATE_IS_EMPTY,
								CND::ERR_FX_RATE_IS_EMPTY,
								CND::WARN_FX_RATE_IS_EMPTY,
								idDataGroup );
			   }
		   }
	   }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//GIA-INA
//******************************************************************************
bool Exchange::isGIAAttribAllowed (const BFDataGroupId &idDataGroup)
{
   bool isGIAAttribAllowed = false;
   DString fundCode;
   getField (ifds::ToFund, fundCode, idDataGroup, false);

   if (!fundCode.empty())
   {
      FundMasterList *pFundMasterList (NULL);

      if ( getMgmtCo().getFundMasterList (pFundMasterList) <= WARNING && 
           pFundMasterList)
      {
         isGIAAttribAllowed = pFundMasterList->isGIAFund (fundCode);
      }
   }
   return isGIAAttribAllowed;
}

//******************************************************************************
bool Exchange::allowToFndClsBeParentAMS(const BFDataGroupId &idDataGroup)
{
    // Allow FundTo/ClassTo to be AMS Parent Fund/Class if an environment is MasterActWithOneChild

    DString dstrToFundCode, dstrToClassCode;
    FundDetail *pToFundDetail = NULL;
    bool isParentAMS = false;

    getField(ifds::ToFund, dstrToFundCode, idDataGroup);
    getField(ifds::ToClass, dstrToClassCode, idDataGroup);

    if (getWorkSession().getFundDetail(dstrToFundCode, dstrToClassCode, idDataGroup, pToFundDetail) && pToFundDetail)
    {
        isParentAMS = pToFundDetail->isAMSParentFund(idDataGroup);
    }

    return isParentAMS && getWorkSession().isMasterActWithOneChild(idDataGroup);
}

//******************************************************************************
SEVERITY Exchange::giAttribRelatedChanges (const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("giAttribRelatedChanges"));
                      
   if( isGIAAttribAllowed (idDataGroup))
   {
	    Shareholder *pShareholder = NULL;
        DString shrNum;
		DString accountNum;
		MFAccount *pMFAccount = NULL;

		getField (ifds::AccountNum, accountNum, idDataGroup, false);
		accountNum.stripLeading ('0').strip();

		if (getWorkSession().getMFAccount (idDataGroup, accountNum, pMFAccount) <= WARNING && pMFAccount)
		{
			pMFAccount->getField (ifds::ShrNum, shrNum, idDataGroup);
        
			if (getWorkSession ().getShareholder (idDataGroup, shrNum, pShareholder) <= WARNING && pShareholder)
			{
               DString dstrFundRelCode;

               pShareholder->getField (ifds::FundRelnCode, dstrFundRelCode, idDataGroup, false);

			   bool bReadOnly = dstrFundRelCode == AGENT || dstrFundRelCode == EMPLOYEE ? true : false;

		   		setFieldReadOnly (ifds::CommRedRate, idDataGroup, bReadOnly); 
			}
		}

	   if (!_bInitPending)
	   {
			setFieldNoValidate ( ifds::OrderType, I_("N"), idDataGroup, false, true, true, false); //no related changes
			setFieldNoValidate ( ifds::WireOrdNum, NULL_STRING, idDataGroup, false);
			setFieldNoValidate ( ifds::AmtType, I_("D"), idDataGroup, false, true, true, false); //no related changes   
	   }

      setFieldReadOnly (ifds::OrderType, idDataGroup, true);
	  // need to confirm this with Philip:
      //setFieldReadOnly (ifds::DepositDate, idDataGroup, true);
      setFieldValid (ifds::DepositDate, idDataGroup, true);
      setFieldRequired (ifds::DepositDate, idDataGroup, false);
      setFieldRequired (ifds::WireOrdNum, idDataGroup, false);
      setFieldValid (ifds::WireOrdNum, idDataGroup, true);

	  // making GI fields mandatory:
	  setFieldRequired (ifds::IntInvestType, idDataGroup, true);
      setFieldValid (ifds::IntInvestType, idDataGroup, false);
      setFieldRequired (ifds::IntCalcMthd, idDataGroup, true);
	  setFieldValid (ifds::IntCalcMthd, idDataGroup, false);
      setFieldRequired (ifds::InvestTerm, idDataGroup, true);
      setFieldValid (ifds::InvestTerm, idDataGroup, false);
      setFieldRequired (ifds::IntCredFreq, idDataGroup, true);
      setFieldValid (ifds::IntCredFreq, idDataGroup, false);

	  setFieldRequired (ifds::ForcedRate, idDataGroup, true);
      setFieldValid (ifds::ForcedRate, idDataGroup, false);
   }  
   else
   {
		setFieldNoValidate ( ifds::IntInvestType, I_(""), idDataGroup, false, true, true, false); 
		setFieldNoValidate ( ifds::IntCalcMthd, I_(""), idDataGroup, false, true, true, false); 
		setFieldNoValidate ( ifds::InvestTerm, I_(""), idDataGroup, false, true, true, false); 
		setFieldNoValidate ( ifds::GIMaturityDate, I_(""), idDataGroup, false, true, true, false); 
		setFieldNoValidate ( ifds::IntCredFreq, I_(""), idDataGroup, false, true, true, false); 
		setFieldNoValidate ( ifds::NextIntCredDate, I_(""), idDataGroup, false, true, true, false); 
		setFieldNoValidate ( ifds::CommRedRate, I_(""), idDataGroup, false, true, true, false); 
		setFieldNoValidate ( ifds::AddlAmt, I_(""), idDataGroup, false, true, true, false); 
		setFieldNoValidate ( ifds::ForcedRate, I_(""), idDataGroup, false, true, true, false); 
		setFieldNoValidate ( ifds::IntRate, I_(""), idDataGroup, false, true, true, false); 
		//setFieldNoValidate ( ifds::InvestStatus, I_(""), idDataGroup, false, true, true, false); 

	    setFieldRequired (ifds::IntInvestType, idDataGroup, false);
        setFieldValid (ifds::IntInvestType, idDataGroup, true);
        setFieldRequired (ifds::IntCalcMthd, idDataGroup, false);
        setFieldValid (ifds::IntCalcMthd, idDataGroup, true);
        setFieldRequired (ifds::InvestTerm, idDataGroup, false);
        setFieldValid (ifds::InvestTerm, idDataGroup, true);
        setFieldRequired (ifds::IntCredFreq, idDataGroup, false);
        setFieldValid (ifds::IntCredFreq, idDataGroup, true);
		setFieldRequired (ifds::ForcedRate, idDataGroup, false);
        setFieldValid (ifds::ForcedRate, idDataGroup, true);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************************************
SEVERITY Exchange::toFundClassRelatedChanges ( const DString &fundCode, 
                                               const DString &classCode, 
                                               const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("toFundClassRelatedChanges"));
   Transfer::toFundClassRelatedChanges (fundCode, classCode, idDataGroup);

   GIAInvAttribList *pGIAInvAttribList (NULL);
   
   getGIFundDefaults (pGIAInvAttribList, idDataGroup);
   giAttribRelatedChanges (idDataGroup);

   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY Exchange::RDRAdviceRelatedChanges (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("RDRAdviceRelatedChanges"));
   
   DString accountTo, toFund, toClass,tradeInDate;
   getField (ifds::AccountTo, accountTo, idDataGroup, false);
   getField (ifds::ToFund, toFund, idDataGroup, false);
   getField (ifds::ToClass, toClass, idDataGroup, false);
   getField (ifds::TradeInDate,tradeInDate,idDataGroup,false);
   
   setRDRAdviceFlag( TRADETYPE::EXCHANGE_IN,
					 accountTo,
					 toFund,
					 toClass,
					 tradeInDate,
					 idDataGroup);
   
   return GETCURRENTHIGHESTSEVERITY();
}
//**********************
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/Exchange.cpp-arc  $
// 
//    Rev 1.44   Jul 26 2012 10:46:14   wp040027
// P0198518 - RDR Functionality
// 
//    Rev 1.43   Jun 08 2012 14:06:58   jankovii
// IN 2957854 - P0186477_FN05_03_Same transno. in distrib-delt to be used & changes to misc-info
// 
//    Rev 1.42   Apr 04 2012 14:43:06   jankovii
// IN 2898233 - R12.3-P0186477-Enable manual tax calculation of money out transactions for NR
// 
//    Rev 1.41   Mar 19 2012 12:51:38   if991250
// RedemOrder default value
// 
//    Rev 1.40   Mar 15 2012 17:56:32   if991250
// IN 2879297: Money Out
// 
//    Rev 1.39   Mar 13 2012 17:34:08   if991250
// IN 2879297: Money Out
// 
//    Rev 1.38   Jan 20 2012 15:47:30   wp040027
// P0188394_Performance Fees - Order Entry
// 
//    Rev 1.37   Dec 08 2011 21:44:30   wp040032
// P0183989 - Money Market Non Receipt
// 
//    Rev 1.36   Aug 02 2010 07:57:24   dchatcha
// IN# 2196483 - QESI phase 1 - PET165541 - cannot process exchanges.
// 
//    Rev 1.35   May 13 2010 15:28:04   jankovii
// PET165541_FN01_QESI - RESP Gap_Dsk_TRADING 
// 
//    Rev 1.34   Mar 08 2010 13:17:14   jankovii
// PET165541_FN01_QESI - RESP Gap_Dsk_TRADING 
// 
//    Rev 1.33   Oct 26 2009 18:11:28   wutipong
// #1412263 - code refactor as per Zijian's suggestion
// 
//    Rev 1.32   Oct 22 2009 15:40:32   wutipong
// Inc#1412263 - GL-1287 (Pending Trades)A/C 15443175 & 15979446 Seg fund transfer error message.
// 
//    Rev 1.31   Jun 26 2009 06:13:24   kitticha
// IN#1738640 - R94 - Country Schedule - Cannot modify TX even when FundFrom and FundTo are same
// 
//    Rev 1.30   15 Jun 2009 08:35:36   popescu
// PET157837 FN02 - Country Schedule Daily Non Resident Schedule A - revised the code
// 
//    Rev 1.29   10 Jun 2009 18:34:44   popescu
// PET157837 FN02 - Country Schedule Daily Non Resident Schedule A - revised the code
// 
//    Rev 1.28   Jun 09 2009 05:42:38   kitticha
// PET157837 FN02 - Country Schedule Daily Non Resident Schedule A
// 
//    Rev 1.27   Apr 17 2009 10:42:42   jankovii
// PET 157825 FN04 Manual RRIF Redemption
// 
//    Rev 1.26   19 Mar 2009 13:42:38   kovacsro
// IN#1628727 - Configuration Issue with iFAST Desktop
// 
//    Rev 1.25   Nov 28 2008 14:39:58   jankovii
// PET 142196 FN01 Federal Restricted LIF and LIRA.
// 
//    Rev 1.24   01 Oct 2008 11:53:26   popescu
// Check in for incident 1419539
// 
//    Rev 1.23   Oct 24 2007 15:00:28   jankovii
// IN #1047594 - Fund Level Override not working for manual exchanges.
// 
//    Rev 1.22   Oct 08 2007 12:16:12   smithdav
// IN  1005517,1020252 - LRSP logic
// 
//    Rev 1.21   01 Aug 2007 15:58:50   popescu
// Incident # 956780 - mgfeerebate should always be direct
// 
//    Rev 1.20   23 Jul 2007 16:49:36   popescu
// PET 2360 - FN 20 - GAP 20 Soft cap functionality
// 
//    Rev 1.19   May 09 2007 16:20:48   jankovii
// MT54X PET2321 FN03 -Participant Transfer.
// 
//    Rev 1.18   Mar 30 2007 14:05:46   jankovii
// PET 2292 FN01 - Switch Settlement.
// 
//    Rev 1.16   Mar 26 2007 11:08:54   jankovii
// PET 2292 FN01 - Switch Settlement.
// 
//    Rev 1.15   Nov 09 2006 00:07:26   popescu
// PET 2281/Fn01 - cloning account - TA  synch-up from rel 73
// 
//    Rev 1.14   Oct 30 2006 17:02:02   jankovii
// PET 2185 FN04 - Trade restrictions.
// 
//    Rev 1.13   Apr 27 2006 10:45:04   jankovii
// Incident #605993 - EUSD backdated edit in Exchange trade is missing hard error at Fund Class fields.
// 
//    Rev 1.12   Mar 22 2006 16:20:52   jankovii
// EUSD Backdated trade validation.
// 
//    Rev 1.11   Jul 07 2005 11:37:06   porteanm
// PET1171 EUSD 1B - Call validateEUSDBackDates().
// 
//    Rev 1.10   Mar 09 2005 10:02:12   popescu
// Incident# 260164, moved the init of AccountTo to 'doApplyRelated' rather then 'doInitWithDefaultValues' -- this caused a reset of the allocation list
// 
//    Rev 1.9   Feb 20 2005 11:52:52   porteanm
// Incident 244225/WO 19920 - Missing escrow account validation for Exchange.
// 
//    Rev 1.8   Jan 04 2005 11:06:34   popescu
// PTS 10037407, corrected field names for exchange fund broker eligibility. also, corrected the error message.
// 
//    Rev 1.7   Dec 15 2004 10:41:24   popescu
// PET 1117/06, delay the full transfer/exchange not allowed errror
// 
//    Rev 1.6   Dec 07 2004 01:37:32   popescu
// PET 1117/56 trades processing/modify trade
// 
//    Rev 1.5   Nov 30 2004 20:09:54   popescu
// PET 1117/06
// 
//    Rev 1.4   Nov 29 2004 20:30:12   popescu
// PET 1117/06/56 fees/trades processing
// 
//    Rev 1.3   Nov 14 2004 14:36:56   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.2   Nov 06 2004 00:40:44   popescu
// PET 1117/06, synch changes
// 
//    Rev 1.2   Nov 04 2004 17:37:26   popescu
// PET 1117/06, Trade processing
// 
//    Rev 1.1   Nov 02 2004 19:19:22   popescu
// PET 1117/06 Trade processing...
// 
//    Rev 1.0   Oct 29 2004 20:27:38   popescu
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
