//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1997 by DST Systems, Inc.
//
//*****************************************************************************
//
// ^FILE   : SysAllocation.cpp
// ^AUTHOR : Chin Hsu
// ^DATE   : Feburary 25, 1999
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : SysAllocation
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include "currencylist.hpp"
#include "currencyclass.hpp"
#include <ifastdataimpl\dse_dstc0004_vw.hpp>
#include <ifastdataimpl\dse_dstc0006_vw.hpp>
#include <ifastdataimpl\dse_dstc0007_vw.hpp>
#include <ifastdataimpl\dse_dstc0084_req.hpp>
#include <ifastdataimpl\dse_dstc0095_req.hpp>
#include <ifastdataimpl\dse_dstc0098_vwrepeat_record.hpp>
#include "dstcommonfunction.hpp"
#include "funddetaillist.hpp"
#include "funddetail.hpp"
#include "fundmasterlist.hpp"
#include "groupfundlist.hpp"
#include "grouplist.hpp"
#include "mfaccount.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "shareholder.hpp"
#include "splitcommission.hpp"
#include "splitcommissionlist.hpp"
#include "sysallocation.hpp"
#include "sysallocationlist.hpp"
#include "systematic.hpp"
#include "SeqFundValidation.hpp"

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME               = I_("SysAllocation");
   const I_CHAR * const SPLITCOM_LIST           = I_("SplitCommissionList");
   const I_CHAR * const DECIMALS                = I_("DECIMALS");
   const I_CHAR * const YES                     = I_("Y");
   const I_CHAR * const NO                      = I_("N");
   const I_CHAR * const PURCHASE_CODE           = I_("ED");      // trade trans type Purchase
   const I_CHAR * const REDEMPTION_CODE         = I_("PW");      // trade trans type Redemption
   const I_CHAR * const EX_FER_IN_CODE          = I_("XFIN");    // trade trans type Exchange In 
   const I_CHAR * const EX_FER_OUT_CODE         = I_("XFOUT");   // trade trans type Exchange Out  
   const I_CHAR * const COMMISSION_TYPE_ZERO    = I_("0");
   const I_CHAR * const SAVING_PLAN             = I_("V");
   const I_CHAR * const FROMFUND                = I_("FROMFUND"); // PAC, SWP, saving plan use from fund
   const I_CHAR * const TOFUND                  = I_("TOFUND");   // AT Automatic transfer use to fund
   const I_CHAR * const FUND                    = I_("FUND");
   const I_CHAR * const CLASS                   = I_("CLASS");
   const I_CHAR * const PAC                     = I_("P");
   const I_CHAR * const AUTO_TRFER              = I_("AT");
   const I_CHAR * const GWLWA_OPTIONS           = I_( "G,L" );
}

namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const INVALID_AMOUNT_TYPE_BY_SEG_RULES;
   extern CLASS_IMPORT I_CHAR * const PLAN_CANNOT_BE_MANUALLY_CREATED;
}

namespace AMT_TYPE
{
    extern CLASS_IMPORT I_CHAR * const CUSTOM;
    extern CLASS_IMPORT I_CHAR * const PORTFOLIO;
}

namespace CND
{  // Conditions used
   extern const long ERR_ENTRY_EMPTY_OR_CONTAINS_ONLY_SPACE;
   extern const long ERR_INVALID_CHAR;
   extern const long ERR_ENTRY_BOTH_FIELDS;
   extern const long ERR_ACCT_INVALID_FOR_THIS_SHR;
   extern const long ERR_ALLOC_FOR_INACTIVE_ACCT;
   extern const long ERR_ALLOC_FOR_ACCT_TYPE06;
   extern const long ERR_PURCH_STOPPED_FOR_PAC;
   extern const long ERR_REDEMP_STOPPED_FOR_SWP;
   extern const long ERR_TRANSFER_EXCH_STOPPED_FOR_AT;
   extern const long ERR_INVALID_TAXTYPE_FOR_PAC_ALLOC;
   extern const long ERR_FUND_NOT_EFFECTIVE;
   extern const long ERR_FUND_CLASS_NOT_EFFECTIVE;
   extern const long ERR_INVALID_FUND_CLASS_CODES;
   extern const long ERR_BLANK_FUND;
   extern const long ERR_BLANK_CLASS;
   extern const long ERR_VALUE_BETWEEN_0_AND_100;
   extern const long ERR_VALUE_CANNOT_BE_ZERO;

   extern const long ERR_INVALID_NEGATIVE_AMOUNT;
   extern const long ERR_AMOUNT_EXCEED_MAX_LIMIT;
   extern const long ERR_INCORRECT_PRECISION;
   extern const long ERR_INVALID_FUND_CLASS_CODES;
   extern const long ERR_INVALID_FUND_NUMBER;
   extern const long ERR_FUND_CURRENCY_DIFFERENT;
   extern const long ERR_FUND_CLASS_PURCHASE_STOP_FLAG_ON;
   extern const long ERR_FUND_CLASS_REDEMPTION_STOP_FLAG_ON;
   extern const long ERR_FUND_CLASS_EXCHANGEOUT_STOP_FLAG_ON;
   extern const long ERR_FUND_CLASS_NOT_AVAILABLE_FOR_BROKER;
   extern const long ERR_FUND_CLASS_NOT_AVAILABLE_FOR_SALESREP;
   extern const long ERR_TAX_TYPE_CANNOT_TRADE_IN_THE_CURRENCY;
   extern const long WARN_DATA_UPDATE_IMPACTS_EXTERNAL_ENV_SICAV;
   extern const long WARN_DATA_UPDATE_IMPACTS_EXTERNAL_ENV_OEIC;
   extern const long ERR_INVALID_AMOUNT_TYPE_BY_SEG_RULES;
   extern const long WARN_INVALID_AMOUNT_TYPE_BY_SEG_RULES;
   extern const long ERR_PLAN_CANNOT_BE_MANUALLY_CREATED;
   extern const long WARN_PLAN_CANNOT_BE_MANUALLY_CREATED;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId TaxTypeByCurrChk;
   extern CLASS_IMPORT const BFTextFieldId InvalidCurr;
   extern CLASS_IMPORT const BFTextFieldId BusRounding;
   extern CLASS_IMPORT const BFNumericFieldId Precision;
   extern CLASS_IMPORT const BFTextFieldId ToFundNumber;
   extern CLASS_IMPORT const BFTextFieldId FundClass;
   extern CLASS_IMPORT const BFTextFieldId SplitCommSWP;
   extern CLASS_IMPORT const BFTextFieldId SplitCommPAC;
   extern CLASS_IMPORT const BFTextFieldId SplitCommTrfln;
   extern CLASS_IMPORT const BFTextFieldId Default;
   extern CLASS_IMPORT const BFDataId DSTC0084_REQRepeat_Record;
   extern CLASS_IMPORT const BFTextFieldId MultiCurrency;
   extern CLASS_IMPORT const BFIntegerFieldId CommissionType;

   extern CLASS_IMPORT const BFTextFieldId SegClient;
   extern CLASS_IMPORT const BFTextFieldId CotClient;
   extern CLASS_IMPORT const BFTextFieldId CurrChkByTaxType;

   extern CLASS_IMPORT const BFTextFieldId CompoundDate;
   extern CLASS_IMPORT const BFTextFieldId FundClassTradeDate;
   extern CLASS_IMPORT const BFNumericFieldId TransSeq;
   extern CLASS_IMPORT const BFTextFieldId RDRAdvice;
   extern CLASS_IMPORT const BFTextFieldId SoftCapCheck;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,            State Flags,             Group Flags 
   {ifds::RunMode,         BFCBO::INIT_TO_DEFAULT,      0}, 
   {ifds::TransType,       BFCBO::INIT_TO_DEFAULT,      0}, 
   {ifds::PACSWPId,        BFCBO::INIT_TO_DEFAULT,      0}, 
   {ifds::FundCode,        BFCBO::INIT_TO_DEFAULT,      0}, 
   {ifds::ClassCode,       BFCBO::INIT_TO_DEFAULT,      0}, 
   {ifds::Percentage,      BFCBO::INIT_TO_DEFAULT,      0}, 
   {ifds::AllocAmount,     BFCBO::INIT_TO_DEFAULT,      0}, 
   {ifds::SettleCurrency,  BFCBO::INIT_TO_DEFAULT,      0}, 
   {ifds::DistribDetlVer,  BFCBO::INIT_TO_DEFAULT,      0}, 
   {ifds::DistribDetlRid,  BFCBO::INIT_TO_DEFAULT,      0}, 
   {ifds::Level,           BFCBO::INIT_TO_DEFAULT,      0}, 
   {ifds::AllocAccountNum, BFCBO::INIT_TO_DEFAULT,      0}, 
   {ifds::ToFundNumber,    BFCBO::INIT_TO_DEFAULT,      0}, 
   {ifds::Default,         BFCBO::NONE,                 0}, 

   {ifds::SplitComm,       BFCBO::NONE,                 0},
   {ifds::TransSeq,        BFCBO::INIT_TO_DEFAULT,      0},
   //cross-edit
   {ifds::FundClass,       BFCBO::IMMEDIATE_VALIDATION, 0}, 
   {ifds::SoftCapCheck,    BFCBO::IMMEDIATE_VALIDATION, 0}, 
	{ifds::FundClassTradeDate, BFCBO::NONE,              0}, 
};

const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = {
//  Object Label,                  State Flags,      Group Flags 
   { I_("SplitCommissionList"),           BFCBO::NONE,     0},
};

static const int NUM_FIELDS = sizeof(classFieldInfo) / sizeof(BFCBO::CLASS_FIELD_INFO);
static const int NUM_OBJECTS = sizeof(classObjectInfo) / sizeof(BFCBO::CLASS_OBJECT_INFO);

//******************************************************************************
SysAllocation::SysAllocation(BFAbstractCBO &parent) :
MFCanBFCbo(parent),
_bInitialSplitComm (false)
{
   TRACE_CONSTRUCTOR(CLASSNAME , NULL_STRING);

   registerMemberData(NUM_FIELDS,(const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL);

   addCrossEdit(ifds::FundClass, ifds::FundCode);
   addCrossEdit(ifds::FundClass, ifds::ClassCode);

   addCrossEdit(ifds::SoftCapCheck, ifds::FundCode);
   addCrossEdit(ifds::SoftCapCheck, ifds::ClassCode);

	 //cross edit for Fund, Class, AccountNum and EffectiveDate
   addCrossEdit(ifds::FundClassTradeDate, ifds::FundCode);
   addCrossEdit(ifds::FundClassTradeDate, ifds::ClassCode);
   addCrossEdit(ifds::FundClassTradeDate, ifds::AccountNum);
   addCrossEdit(ifds::FundClassTradeDate, ifds::EffectiveDate);
}

//******************************************************************************
SysAllocation::~SysAllocation()
{
   TRACE_DESTRUCTOR(CLASSNAME);
}

//******************************************************************************
SEVERITY SysAllocation::init()
{
   MAKEFRAME2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY SysAllocation::init(const BFData &viewData)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));

   //attach the data object
   attachDataObject(const_cast<BFData&>(viewData), false, true);

   //set the fund number
   DString fundCode, classCode, fundNumber;

   fundCode = viewData.getElementValue(ifds::FundCode);
   classCode = viewData.getElementValue(ifds::ClassCode);
   getWorkSession().GetFundNumber(fundCode.strip().upperCase(), 
      classCode.strip().upperCase(), fundNumber);
   setFieldNoValidate(ifds::ToFundNumber, fundNumber, BF::HOST);
   _bInitialSplitComm = YES == viewData.getElementValue(ifds::SplitComm);

   // Init the getDefaultSplit field to No
   setFieldNoValidate(ifds::Default, NO, BF::HOST);
   if (SplitCommission::isTypeZERO(getWorkSession()))
   {
      setFieldNoValidate(ifds::SplitComm, NO, BF::HOST);
   }
   clearUpdatedFlags(BF::HOST);
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void SysAllocation::getField(const BFFieldId& idField, DString &dstrFieldValue, 
                              const BFDataGroupId& idDataGroup, bool formattedReturn) const
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getField"));
   BFCBO::getField(idField, dstrFieldValue, idDataGroup, formattedReturn);
   if(idField == ifds::AllocAmount && formattedReturn)
   {
      BFCBO::getField(idField, dstrFieldValue, idDataGroup, false);
      const Systematic *pSystematic = 
         dynamic_cast< const Systematic * >(getParent()->getParent());
      pSystematic->getFormattedAmount(idDataGroup, dstrFieldValue);
   }
   else
   {
      if (idField == ifds::FundCode || idField == ifds::ClassCode)
         dstrFieldValue.strip().upperCase();
   }
}

//******************************************************************************
SEVERITY SysAllocation::doValidateField(const BFFieldId& idField,
                                         const DString& strValue,
                                         const BFDataGroupId& idDataGroup)

{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField"));

   //ticket 2404299 (REG_RL11.2/101 - PAC set up and delete issues)
   //if Systematic is dummy, no need to validate fields for allocation
   Systematic *pSystematic = dynamic_cast< Systematic * >(getParent()->getParent());

   if(pSystematic->isSystematicListDummy(idDataGroup))
   {
      setFieldValid( idField, idDataGroup, true );
      return(GETCURRENTHIGHESTSEVERITY());
   }


   DString dstr;
   if (idField == ifds::FundCode)
   {
      validateFundCode (strValue, idDataGroup);
      //ticket 2404299 (REG_RL11.2/101 - PAC set up and delete issues) 
      //force validation in case switching no changed fund/class records
      setValidFlag(ifds::FundClass, idDataGroup, false); 
      setValidFlag(ifds::SoftCapCheck, idDataGroup, false); 
   }
   else if(idField == ifds::ClassCode)
   {
      DString dstrFundCode;
      getField(ifds::FundCode, dstrFundCode, idDataGroup, false);
      validateClassCode(dstrFundCode, strValue, idDataGroup);
      //ticket 2404299 (REG_RL11.2/101 - PAC set up and delete issues) 
      //force validation in case switching no changed fund/class records
      setValidFlag(ifds::FundClass, idDataGroup, false);
      setValidFlag(ifds::SoftCapCheck, idDataGroup, false);
   }
   else if (idField == ifds::FundClass)
   {
      validateFundClass(idDataGroup);
      validateFundClassPayout(idDataGroup);
   }
   else if (idField == ifds::SoftCapCheck)
   {
      validateFundClassSoftCapped(idDataGroup);
   }
   else if (idField == ifds::AllocAmount)
   {
      validateAmount(strValue, idDataGroup);
   }
   else if (idField == ifds::Percentage)
   {
      validatePercentage (strValue, idDataGroup);
   }
   else if (idField == ifds::ToFundNumber)
   {
      DString dstrFundCode,dstrClassCode;

      if (!getWorkSession().GetFundClassCode(strValue, dstrFundCode, dstrClassCode))
      {
         ADDCONDITIONFROMFILE(CND::ERR_INVALID_FUND_NUMBER);
      }
   }
   else if (idField == ifds::FundClassTradeDate)
   {
      validateFundClassAccNumDate ( idDataGroup );
   }

   return (GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY SysAllocation::validateFundClassPayout(const BFDataGroupId& idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateFundClassPayout"));

    DString dstrFundCode, dstrClassCode, dstrAmtTypeOvrd, dstrTransType;
    FundDetail *pFundDetail = NULL;
    Systematic *pSystematic = dynamic_cast<Systematic*>(getParent()->getParent());

    if (pSystematic)
    {
        getField(ifds::FundCode, dstrFundCode, idDataGroup, false);
        getField(ifds::ClassCode, dstrClassCode, idDataGroup, false);
        pSystematic->getField(ifds::AmtTypeOvrd, dstrAmtTypeOvrd, idDataGroup, false);
        pSystematic->getField(ifds::TransType, dstrTransType, idDataGroup, false);;

        dstrFundCode.strip().upperCase();
        dstrClassCode.strip().upperCase();
        dstrAmtTypeOvrd.strip().upperCase();
        dstrTransType.strip().upperCase();

        if (dstrTransType == I_("S") && //SWP
            dstrAmtTypeOvrd != AMT_TYPE::PORTFOLIO && 
            !dstrFundCode.empty() && 
            !dstrClassCode.empty() &&
            getWorkSession().getFundDetail(dstrFundCode, dstrClassCode, idDataGroup, pFundDetail) &&  pFundDetail &&
            pFundDetail->isPortfolioPayoutFund(idDataGroup))
        {
            getErrMsg(IFASTERR::PLAN_CANNOT_BE_MANUALLY_CREATED, 
                      CND::ERR_PLAN_CANNOT_BE_MANUALLY_CREATED,
                      CND::WARN_PLAN_CANNOT_BE_MANUALLY_CREATED,
                      idDataGroup);
        }
    }

    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY SysAllocation::validateFundClassSoftCapped(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateFundClassSoftCapped"));

   DString dstrFundCode, dstrClassCode,dstrEffectiveDate, dstrAccountNum;
   Systematic *pSystematic = dynamic_cast<Systematic*>(getParent()->getParent());

   getField(ifds::FundCode, dstrFundCode, idDataGroup, false);
   getField(ifds::ClassCode, dstrClassCode, idDataGroup, false);
   dstrFundCode.strip().upperCase();
   dstrClassCode.strip().upperCase();

   if (pSystematic)
   {
       pSystematic->getField(ifds::EffectiveDate, dstrEffectiveDate, idDataGroup);
       pSystematic->getField(ifds::AccountNum, dstrAccountNum, idDataGroup);
   }

   getWorkSession().fundClassSoftCappedCheck(dstrAccountNum, dstrFundCode, dstrClassCode, I_("ED"), dstrEffectiveDate, idDataGroup);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void SysAllocation::validateFundClass(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("ValidateFundClass"));

   DString dstrFundCode, dstrClassCode, strKey;
   ////////////////////////////////////////////
   getField(ifds::FundCode, dstrFundCode, idDataGroup, false);
   getField(ifds::ClassCode, dstrClassCode, idDataGroup, false);
   dstrFundCode.strip().upperCase();
   dstrClassCode.strip().upperCase();

   if(dstrClassCode.empty())
   {
      setFieldNoValidate(ifds::ToFundNumber, NULL_STRING, idDataGroup, false);
      ADDCONDITIONFROMFILE(CND::ERR_BLANK_CLASS);
      return;
   }
   if(dstrFundCode.empty())
   {
      setFieldNoValidate(ifds::ToFundNumber, NULL_STRING, idDataGroup, false);
      ADDCONDITIONFROMFILE(CND::ERR_BLANK_FUND);
      return;
   }

   DString dstrEffectiveDate;
   getParent()->getParent()->getField(ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false);
   dstrEffectiveDate.strip();

   DString dstrTransType, dstrTransTypeParam;
   getField(ifds::TransType, dstrTransType, idDataGroup, false);
   if(dstrTransType.strip().upperCase() == I_("AT"))
      dstrTransTypeParam = I_("ATI");
   else if(dstrTransType.strip().upperCase() == I_("P"))
      dstrTransTypeParam = I_("ED");
   else dstrTransTypeParam = dstrTransType;

   Systematic *pSystematic = dynamic_cast< Systematic * >(getParent()->getParent());
   MFAccount *pMFAccount = dynamic_cast< MFAccount *>(getParent()->getParent()->getParent()->getParent());

   if(!dstrFundCode.empty() && !dstrClassCode.empty())
   {
      SEVERITY sevRtn = pMFAccount->canTradeFundClass (dstrFundCode, dstrClassCode, dstrTransTypeParam, dstrEffectiveDate, idDataGroup);
      if(sevRtn <= WARNING)
      {
         if (pSystematic)
         {
            if ( dstrTransTypeParam == I_("ED")) dstrTransTypeParam = I_("P");
            sevRtn= pSystematic->stopFlagCheck(dstrFundCode, dstrClassCode, dstrTransTypeParam, idDataGroup);
         }
         /********************************************
         if(dstrTransTypeParam == PURCHASE_CODE && pFundDetail && pFundDetail->stopPurchase (idDataGroup))
         {
            ADDCONDITIONFROMFILEIDI(CND::ERR_FUND_CLASS_PURCHASE_STOP_FLAG_ON, idiStr);
         }

         // SWP 
         if(dstrTransTypeParam == REDEMPTION_CODE && pFundDetail && pFundDetail->stopRedemption (idDataGroup))
         {
            ADDCONDITIONFROMFILEIDI(CND::ERR_FUND_CLASS_REDEMPTION_STOP_FLAG_ON, idiStr);
         }

         /* Auto Transfer : should be added to AutoTranAlloc.cpp and should add condition for exchange in
         if(dstrTransTypeParam == EX_FER_IN_CODE && pFundDetail && pFundDetail->stopXferIn(idDataGroup))
         {
            ADDCONDITIONFROMFILEIDI(CND::ERR_FUND_CLASS_EXCHANGEOUT_STOP_FLAG_ON, idiStr);
         }*/

         
         // broker fund logic for ticket 10009829 : check broker fund validation against the ToFund/ToClass using the broker of AccountTO as per E&P's request
         if (pSystematic)
         {   
            bool bBrokerFundOk (false), bSlsrepFundOk (false) ;
            if (dstrTransTypeParam == EX_FER_IN_CODE)
            {
               bBrokerFundOk = pSystematic->validBrokerFund (TOFUND, dstrFundCode, dstrClassCode, idDataGroup);
               bSlsrepFundOk = pSystematic->validSalesrepFund (TOFUND, dstrFundCode, dstrClassCode, idDataGroup);
            }
            else 
            {
               bBrokerFundOk = pSystematic->validBrokerFund (FROMFUND, dstrFundCode, dstrClassCode, idDataGroup);
               bSlsrepFundOk = pSystematic->validSalesrepFund (FROMFUND, dstrFundCode, dstrClassCode, idDataGroup);
            }

            pSystematic->setFieldValidFlag( ifds::CompoundDate, idDataGroup, false );
         }
      }
   }

   DString dstrSegClient, dstrCotClient;
   getWorkSession().getOption(ifds::SegClient, dstrSegClient, BF::HOST);
   getWorkSession().getOption(ifds::CotClient, dstrCotClient, BF::HOST);

// if SegClient and CotClient do the SegFundValidation, for PAC and SWP only
   if(dstrSegClient == YES     && dstrCotClient == YES && 
       (dstrTransType == I_("P") || dstrTransType == I_("S")))
   {
      if(pSystematic)
      {
         FundMasterList *pFundMasterList (NULL);
         bool isSegFund = false;


         if ( getMgmtCo().getFundMasterList (pFundMasterList) <= WARNING && 
            pFundMasterList)
         {
            isSegFund = pFundMasterList->isSegregatedFund(dstrFundCode);
         }
         
         if(isSegFund)
         {
            pSystematic->ValidateSegFund(dstrFundCode, dstrClassCode, dstrEffectiveDate, idDataGroup);
         }
      }
   }

   validateAllocCurrency(idDataGroup);

   if (pSystematic)
   {
      pSystematic->validateGMWB (dstrFundCode, dstrClassCode, idDataGroup);
   }

   if(dstrSegClient == YES && dstrCotClient == YES && pSystematic &&
      !dstrFundCode.empty() && !dstrClassCode.empty())
   {
      DString dstrListAmtTypeByFund;
      pSystematic->getValidListAmountTypeByFund(dstrFundCode,dstrClassCode,dstrListAmtTypeByFund,idDataGroup);
      dstrListAmtTypeByFund.strip().upperCase();

      if (!dstrListAmtTypeByFund.empty())
      {
         DString strListAmttype,
            dstrAmountType,
            dstrTransTypeFmt;
         pSystematic->getField (ifds::AmountType, dstrAmountType, idDataGroup, false);
         pSystematic->getField (ifds::TransType, dstrTransTypeFmt, idDataGroup, true);

         dstrAmountType.strip().upperCase();

         //if (DSTCommonFunctions::codeInList (dstrAmountType, GWLWA_OPTIONS))
         {
            // if amount type is not in the list of valid amount type by fund class
            // then raise up an error
            // assume that back-end would return all of valid amount type
            if (!DSTCommonFunctions::codeInList (dstrAmountType, dstrListAmtTypeByFund))
            {
               DString dstrTemp;
               addIDITagValue( dstrTemp, I_("TRANS_TYPE"), dstrTransTypeFmt);
               getErrMsg(IFASTERR::INVALID_AMOUNT_TYPE_BY_SEG_RULES, 
                         CND::ERR_INVALID_AMOUNT_TYPE_BY_SEG_RULES, 
                         CND::WARN_INVALID_AMOUNT_TYPE_BY_SEG_RULES,
                         idDataGroup,
                         dstrTemp);
            }
         }
      }
   }
}

//******************************************************************************
SEVERITY SysAllocation::validateFundClassAccNumDate ( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFundClassAccNumDate" ) );

   // if SegClient and CotClient do the SegFundValidation
   DString strSegClient, strCotClient;
   getWorkSession().getOption(ifds::SegClient, strSegClient, BF::HOST );
   getWorkSession().getOption(ifds::CotClient, strCotClient, BF::HOST );

   if( (strSegClient.strip() == YES && strCotClient.strip() == YES))
   {

      DString dstrAcctNum, dstrFundCode, dstrClassCode, dstrEffectiveDate, dstrTransType;
      getField( ifds::TransType, dstrTransType, idDataGroup, false );
      dstrTransType.strip().upperCase();

      if( dstrTransType == I_("P") )
      {
         Systematic *pSystematic = 
            dynamic_cast< Systematic * >(getParent()->getParent());
         pSystematic->getField (ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false);
         getField (ifds::FundCode, dstrFundCode, idDataGroup, false);
         getField (ifds::ClassCode, dstrClassCode, idDataGroup, false);

         pSystematic->getField(ifds::AccountNum, dstrAcctNum, idDataGroup, true);

         SeqFundValidation *pSeqFundValidation = NULL;

         if( pSystematic->getSeqFundValidation( pSeqFundValidation, idDataGroup, dstrFundCode, dstrClassCode, dstrAcctNum, dstrEffectiveDate ) 
            <= WARNING && pSeqFundValidation )
         {
            pSeqFundValidation->addSegFundValidationWarnings( idDataGroup );
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void SysAllocation::validatePercentage(const DString& strValue,const BFDataGroupId& idDataGroup) const
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("ValidatePercentage"));

   DString dstrPercentage(strValue);
   dstrPercentage.strip();
   if(dstrPercentage.empty())
   {
      ADDCONDITIONFROMFILE(CND::ERR_ENTRY_EMPTY_OR_CONTAINS_ONLY_SPACE);
      return;
   }

   I_CHAR *stopstring;
   double dPercent = wcstod(dstrPercentage.c_str(), &stopstring);

   if(dPercent > 100)
   {
      ADDCONDITIONFROMFILE(CND::ERR_VALUE_BETWEEN_0_AND_100);
      return;
   }

   DString dstrPercentageMask = DSTCommonFunctions::getRawMask(ifds::Percentage);
   dstrPercentageMask.strip();
   int iMaskNumDigitsAfterDecimalPoint = dstrPercentageMask.length() - dstrPercentageMask.find(I_(".")) - 1;

   double dMinValue = pow(10.0, -iMaskNumDigitsAfterDecimalPoint);

   if(dPercent < dMinValue)
      ADDCONDITIONFROMFILE(CND::ERR_VALUE_CANNOT_BE_ZERO);
}

//******************************************************************************

void SysAllocation::validateAmount(const DString& Amount, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("ValidateAmount"));

   DString dstrAmount(Amount);
   dstrAmount.stripAll(I_(','));
   double dAmount = DSTCommonFunctions::convertToDouble(dstrAmount);
   DString dstrFundCode, dstrClassCode, dstrTotalAmount;
   Systematic *pSystematic = 
      dynamic_cast< Systematic * >(getParent()->getParent());

   getField(ifds::FundCode, dstrFundCode, idDataGroup, false);
   getField(ifds::ClassCode, dstrClassCode, idDataGroup, false);
   dstrFundCode.strip().upperCase();
   dstrClassCode.strip().upperCase();
   pSystematic ->getField(ifds::Amount, dstrTotalAmount, idDataGroup, false);
   dstrTotalAmount.stripAll(I_(','));

   double dTotalAmount = DSTCommonFunctions::convertToDouble(dstrTotalAmount);

   if(dTotalAmount == 0 && dAmount == 0)
      return;
   pSystematic->ValidateAmountLimit(dAmount, dstrFundCode, dstrClassCode, idDataGroup);
   if(pSystematic ->findTransType(idDataGroup, PAC) || pSystematic->findTransType(idDataGroup, AUTO_TRFER))
   {
		pSystematic ->ValidateAmountInitPur(dAmount, dstrFundCode, dstrClassCode, idDataGroup);
   }
   if ( pSystematic->isCappedFund ( dstrFundCode, idDataGroup ) ){
      DString dstrOriAmount,dstrOriFund;
      getField( ifds::AllocAmount, dstrOriAmount, BF::HOST );
		getField( ifds::FundCode, dstrOriFund,BF::HOST,false );
		dstrOriFund.strip().upperCase();
		if(dstrOriFund == dstrFundCode )
		{
			pSystematic->ValidateCappedAmt ( dstrOriAmount, Amount, idDataGroup );
		}
   }
//   pSystematic->ValidateAmountInitPur(dAmount, dstrFundCode, dstrClassCode, idDataGroup);
}

//******************************************************************************
void SysAllocation::doInitWithDefaultValues(const BFDataGroupId& idDataGroup)
{
   DString str;
   const Systematic *pSystematic = 
      dynamic_cast< const Systematic * >(getParent()->getParent());

   pSystematic->getField(ifds::BankAcctCurrency, str, idDataGroup, false);
   setFieldNoValidate(ifds::SettleCurrency, str, idDataGroup, false);
   pSystematic->getField(ifds::TransType, str,    idDataGroup, false);
   setFieldNoValidate(ifds::TransType, str, idDataGroup, false);
   pSystematic->getField(ifds::PACSWPId, str, idDataGroup, false);
   str.strip().stripLeading('0');                                                   
   setFieldNoValidate(ifds::PACSWPId, str, idDataGroup, false);
   setFieldNoValidate(ifds::Level, I_("3"), idDataGroup, false);
}

//******************************************************************************
SEVERITY SysAllocation::doApplyRelatedChanges(const BFFieldId& idField, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges"));
   
   if (idField == ifds::AllocAmount) 
   {
      //we should look if this systematic allocation has split commission list,
      //and if it has we should change the commission amounts and rates;
      //do not create the split commission list if it doesn't exist
      SplitCommissionList* pSplitCommissionList = NULL;

      if (getSplitCommissionList(pSplitCommissionList, idDataGroup) <= WARNING && 
            pSplitCommissionList)
      {
         DString dstrAmount;

         getField(idField, dstrAmount, idDataGroup);
         pSplitCommissionList->setField(ifds::Amount, dstrAmount, idDataGroup);
      }
   }
   else if(idField == ifds::FundCode || idField == ifds::ClassCode)
   {
         setFundNumber(idField,idDataGroup);
			if( idField == ifds::FundCode )
			{
				DString dstrFundCode;
				getField(ifds::FundCode,dstrFundCode,idDataGroup,false );
				Systematic *pSystematic = dynamic_cast< Systematic * >(getParent()->getParent() );
				if( !dstrFundCode.empty() )
				{
					if( pSystematic->isCappedFund( dstrFundCode, idDataGroup ) )
					{
						setValidFlag( ifds::AllocAmount,idDataGroup,false );				
					}		
				}
			}
   }
   else if(idField == ifds::ToFundNumber)
   {
      setFundClassCode(idField,idDataGroup);
   }
   if(idField == ifds::Percentage || idField == ifds::AllocAmount)
   {  // force validation if the fund/class is invalid to begin with
      //setValidFlag(ifds::FundCode, idDataGroup, false);  validation of the capped fund got trigger when user decrease the amount 10021181
      //setValidFlag(ifds::ClassCode, idDataGroup, false);
      setValidFlag(ifds::FundClass, idDataGroup, false);
      setValidFlag(ifds::SoftCapCheck, idDataGroup, false);
      //getField (ifds::AllocAmount, dstrAmount, idDataGroup, false);
   }

   //If any fields are changed, fund/class must be revalidated against soft capped.
   SysAllocationList *pSysAllocationList = dynamic_cast<SysAllocationList*>(getParent());
   if (pSysAllocationList && isFieldUpdated(idField, idDataGroup))
       pSysAllocationList->setAllAllocsFndClsValidFlag(false, idDataGroup);

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY SysAllocation::setField(const BFFieldId& idField, 
                                  const DString& dstrValue,
                                  const BFDataGroupId& idDataGroup, 
                                  bool bFormatted, 
                                  bool bSideEffect,
                                  bool  bCheckCurrentValue)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("setField"));

   const Systematic *pSystematic = 
      dynamic_cast< const Systematic * >(getParent()->getParent());
   
   if(idField == ifds::Percentage || idField == ifds::AllocAmount)
   {
      DString dstrOrgValue;
      getField(idField, dstrOrgValue, idDataGroup, bFormatted);
      dstrOrgValue.strip().stripAll(I_CHAR(','));

      DString dstrSetValue(dstrValue);
      dstrSetValue.strip().stripAll(I_CHAR(','));
      if(idField == ifds::AllocAmount)
      {
         //Format the value based on the Currency and the system defined Precisition
         pSystematic->getFormattedAmount(idDataGroup, dstrSetValue);
         dstrSetValue.strip().stripAll(I_CHAR(','));
      }
      SEVERITY  sevRtn = BFCBO::setField(idField, dstrSetValue, idDataGroup, bFormatted, bSideEffect);
      if(dstrSetValue != dstrOrgValue)
      {
         //get the Total Allocation Amount from the Trade record
         DString dstrTotalAmount;

         pSystematic->getField(ifds::Amount, dstrTotalAmount, idDataGroup, false);
         dstrTotalAmount.strip().stripAll(I_CHAR(','));

         double dTotalAmount = DSTCommonFunctions::convertToDouble(dstrTotalAmount);

         if(dTotalAmount > 0)
         {
            double dTotalAllocAmount, dTotalAllocPercent;
            SysAllocationList *pSysAllocationList = dynamic_cast<SysAllocationList *>(getParent());
            pSysAllocationList->getTotalAllocAmountPercent(idDataGroup, dTotalAllocAmount, dTotalAllocPercent);

            double dPercentage, dAmount;
//            char szBuffer[50]; 
            if(idField == ifds::Percentage)                    //Percentage
            {
               dPercentage = DSTCommonFunctions::convertToDouble(dstrSetValue);
               if(dPercentage == 0)
               {
                  dAmount = 0;
               }
               else if(fabs(dTotalAllocPercent - 100) < 0.0000000001)
               {
                  DString dstrOrgAmount;
                  getField(ifds::AllocAmount, dstrOrgAmount, idDataGroup, false);
                  dstrOrgAmount.strip().stripAll(I_CHAR(','));
                  dAmount = dTotalAmount - (dTotalAllocAmount - DSTCommonFunctions::convertToDouble(dstrOrgAmount));
               }
               else
               {
                  dAmount = dTotalAmount * dPercentage / 100;
               }
               //DString dstrAmount(DStringA(_gcvt(dAmount, 40, szBuffer)));
               DString dstrAmount = DSTCommonFunctions::doubleToDString(ifds::AllocAmount, dAmount);

               pSystematic->getFormattedAmount(idDataGroup, dstrAmount);
               dstrAmount.strip().stripAll(I_CHAR(','));
               BFCBO::setField(ifds::AllocAmount, dstrAmount, idDataGroup, false, true);
            }
            else                                                    //Amount
            {
               dAmount = DSTCommonFunctions::convertToDouble(dstrSetValue);
               if(dAmount == 0)
               {
                  dPercentage = 0;
               }
               else if(fabs(dTotalAllocAmount - dTotalAmount) < 0.0000000001)
               {
                  DString dstrOrgPercent;
                  getField(ifds::Percentage, dstrOrgPercent, idDataGroup, false);
                  dstrOrgPercent.strip().stripAll(I_CHAR(','));
                  dPercentage = 100 - (dTotalAllocPercent - DSTCommonFunctions::convertToDouble(dstrOrgPercent));
               }
               else
               {
                  dPercentage   =   dAmount   /   dTotalAmount   *   100;     
               }
               DString dstrPercentage = DSTCommonFunctions::doubleToDString(ifds::Percentage, dPercentage);
               dstrPercentage.strip().stripAll(I_CHAR(','));

               BFCBO::setField(ifds::Percentage, dstrPercentage, idDataGroup, false, true);
            }
         }
      }
      return(GETCURRENTHIGHESTSEVERITY());
   }

   SEVERITY  sevRtn = BFCBO::setField(idField, dstrValue, idDataGroup, bFormatted, bSideEffect);
   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
// we are in the target item
void SysAllocation::ModelOffer(SysAllocation *Model, const BFDataGroupId& idDataGroup)
{
   BFData *tmp = new BFData(ifds::DSTC0007_VWRepeat_Record);


   BFDataFieldIter dIter(*tmp);
   DString str;

   for(;dIter; ++dIter)
   {
      const BFFieldId& idField = dIter().getId();
      
      //DistribDetlRid should not be copied over.
      if( idField == ifds::DistribDetlRid)
      {
         setField(idField, I_("0"), idDataGroup, false);
      }
      else
      {
      	Model->getField(idField, str, idDataGroup, false);
      	setField(idField, str, idDataGroup, false);
      }
   };

   delete tmp;
}

//*******************************************************************************
void SysAllocation::setFundClassCode(const BFFieldId& idField,const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("setFundClassCode"))
   DString dstrFundNumber,dstrFundCode,dstrClassCode;

   getField(ifds::ToFundNumber, dstrFundNumber, idDataGroup,false);

   if(dstrFundNumber.strip() != NULL_STRING)
   {
      if(getWorkSession().GetFundClassCode(dstrFundNumber, dstrFundCode, dstrClassCode))
      {
         DString oldFundCode, oldClassCode;
         getField(ifds::FundCode, oldFundCode, idDataGroup, false);
         getField(ifds::ClassCode, oldClassCode, idDataGroup, false);
         if(oldFundCode != dstrFundCode)
            setField(ifds::FundCode, dstrFundCode, idDataGroup, false,true);
         if(oldClassCode != dstrClassCode)
            setField(ifds::ClassCode, dstrClassCode, idDataGroup, false,true);
//         validateAllocCurrency(idDataGroup);
      }
   }
}

//*****************************************************************************
void SysAllocation::setFundNumber(const BFFieldId& idField,const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("setFundNumber"))
   DString dstrFundNumber, dstrFundCode, dstrClassCode, dstrSplitComm, dstrTransType;

   getField(ifds::FundCode, dstrFundCode, idDataGroup, false);
   getField(ifds::ClassCode, dstrClassCode, idDataGroup, false);
   dstrFundCode.strip().upperCase();
   dstrClassCode.strip().upperCase();
   if(dstrFundCode.empty() || dstrClassCode.empty())
      return;

   getWorkSession().GetFundNumber(dstrFundCode, dstrClassCode, dstrFundNumber);
   DString oldFundNumber;

   getField(ifds::ToFundNumber, oldFundNumber, idDataGroup, false);
   if(oldFundNumber.strip() != dstrFundNumber)
   {
      setFieldNoValidate(ifds::ToFundNumber, dstrFundNumber, idDataGroup, false,true,true);      
   }
   // Split Commission flag is set here because Fund Code and Class Code should exists before 
   // fund number can be retrieved
   if(splitCommActive (idDataGroup))
   {
      setFieldNoValidate(ifds::SplitComm, YES, idDataGroup, false,true,true);  
      GetDefaultSplitComm (idDataGroup);
   }
   else
   {
      setFieldNoValidate(ifds::SplitComm, NO, idDataGroup, false,true,true);
      setFieldNoValidate(ifds::Default, NO, idDataGroup, false);
   }
}

//******************************************************************************
SEVERITY SysAllocation::validateFundCode(const DString& dstrfundCode, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateFundCode"));

   DString dstrClassCode;
   getField(ifds::ClassCode, dstrClassCode, idDataGroup, false);
   if(dstrClassCode.strip().upperCase() == NULL_STRING)
   {
      setValidFlag(ifds::ClassCode, idDataGroup,  false);
   }
   Systematic *pSystematic = 
      dynamic_cast< Systematic * >(getParent()->getParent());

   pSystematic->validateFundCode(dstrfundCode, idDataGroup);
   return(GETCURRENTHIGHESTSEVERITY());  
}

//******************************************************************************
SEVERITY SysAllocation::validateClassCode(const DString& dstrfundCode, const DString& dstrClassCode, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateClassCode"));

   Systematic *pSystematic = 
      dynamic_cast< Systematic * >(getParent()->getParent());
   pSystematic->validateClassCode(dstrfundCode, dstrClassCode, idDataGroup);
   return(GETCURRENTHIGHESTSEVERITY());  
}

//******************************************************************************
SEVERITY SysAllocation::getSplitCommissionList(SplitCommissionList *&rpSplitCommissionList,
   const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getSplitCommissionList"));

   rpSplitCommissionList = dynamic_cast<SplitCommissionList*> (BFCBO::getObject(SPLITCOM_LIST, idDataGroup));
   //If the Commission Type is 0, then there is no split commission
   if (SplitCommission::isTypeZERO(getWorkSession()))
   {
      // The delete is necessary to prevent the transaction builder from calling hasTransactionUpdate() check 
      if (rpSplitCommissionList)
      {
         delete rpSplitCommissionList;
      }
      rpSplitCommissionList = NULL;
   }
   else
   {
      SEVERITY severity = NO_CONDITION;
      const Systematic *pSystematic = 
         dynamic_cast< const Systematic * >(getParent()->getParent());
         //always fetch the split list if it was suppose to be there in the beginning
      if (!rpSplitCommissionList && _bInitialSplitComm)
      {
         severity = fetchSplitCommisionListUsingSystematicParent(rpSplitCommissionList, idDataGroup);
      }
      if (severity <= WARNING) //if okay, process further
      {
         DString dstrSplitComm, dstrDefault;

         getField(ifds::SplitComm, dstrSplitComm, idDataGroup, false);
         getField(ifds::Default, dstrDefault, idDataGroup);
         if (dstrSplitComm != YES) //split comm flag set to No
         {
            if (_bInitialSplitComm)
            {
               //if the fund had split commission but changed to a fund with no split commission, 
               //we need to send the deleted split commission in the transaction builder
               rpSplitCommissionList->deleteSplitCommList(idDataGroup);
            }
         }
         else //the split comm flag is set to Yes
         {
            if (!rpSplitCommissionList)
            {
               if (dstrDefault == NO) //there is no default split commission list
               {
                  fetchSplitCommisionListUsingSystematicParent(rpSplitCommissionList, idDataGroup);
               }
               else if (dstrDefault == YES) //in addition, call the default split commission view, 158
               {
                  DString AccountNum, AccountTo, Fund, FundTo, Class, ClassTo;
                  DString PUD, FlatPrcnt, InPayType, IAmount, InTransType, EffectiveDate,rdrAdvice;
                  DString InGrossNet, BrokerCode, BranchCode, SlsRepCode, SettleCurrency;
                  MFAccount *pMFAccount = dynamic_cast<MFAccount*>(
                     getParent()->getParent()->getParent()->getParent());

                  pSystematic->getField (ifds::AccountTo, AccountTo, idDataGroup, false);//This should never occur.
                  pSystematic->getField (ifds::AmountType, PUD, idDataGroup, false);
                  pSystematic->getField (ifds::FlatPercent, FlatPrcnt, idDataGroup, false);
                  pSystematic->getField (ifds::PayType, InPayType, idDataGroup, false);
                  pSystematic->getField (ifds::EffectiveDate, EffectiveDate, idDataGroup, false);
                  pSystematic->getField (ifds::GrossOrNet, InGrossNet, idDataGroup, false);
				  pSystematic->getField (ifds::RDRAdvice, rdrAdvice, idDataGroup, false);
                  pMFAccount->getField (ifds::AccountNum, AccountNum, idDataGroup, false);
                  pMFAccount->getField (ifds::BrokerCode, BrokerCode, idDataGroup, false);
                  pMFAccount->getField (ifds::BranchCode, BranchCode, idDataGroup, false);
                  pMFAccount->getField (ifds::Slsrep, SlsRepCode, idDataGroup, false);
                  getField (ifds::SettleCurrency, SettleCurrency, idDataGroup, false);
                  getField (ifds::FundCode, Fund, idDataGroup, false);
                  getField (ifds::ClassCode, Class, idDataGroup, false);
                  getField (ifds::AllocAmount, IAmount, idDataGroup, false);
                  getField (ifds::TransType, InTransType, idDataGroup, false);
                  rpSplitCommissionList = new SplitCommissionList(*this);
                  //call the default split commission view
                  if (rpSplitCommissionList->init(AccountNum, AccountTo, Fund, 
                        FundTo, Class, ClassTo, PUD, FlatPrcnt, InPayType, 
                        IAmount, InTransType, EffectiveDate, InGrossNet, 
                        BrokerCode, BranchCode, SlsRepCode, 
                        SettleCurrency, NULL_STRING, //record type 
                        I_("0.0"), // exchange rate for systematic should be zero,
                        NULL_STRING,rdrAdvice,NULL_STRING,
                        idDataGroup) <= WARNING)
                  {
                     //set the split list object
                     setObject(rpSplitCommissionList, SPLITCOM_LIST, OBJ_ACTIVITY_NONE, idDataGroup);
                     //clear the default flag
                     setFieldNoValidate(ifds::Default, NO, idDataGroup, false);
                  }
                  else
                  {
                     delete rpSplitCommissionList;
                     rpSplitCommissionList = NULL;
                  }
               }
            }
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY SysAllocation::fetchSplitCommisionListUsingSystematicParent(
   SplitCommissionList *&rpSplitCommissionList, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("initSplitCommisionList"));

   DString dstrTransNum, dstrTransSeq, dstrAccountNum, dstrTransType, dstrFund, 
      dstrClass, dstrBrokerCode, dstrBranchCode, dstrSalesRepCode, dstrEffectiveDate,dstrRDRAdvice;
   Systematic *pSystematic = 
      dynamic_cast< Systematic * >(getParent()->getParent());

   // If the split has never been downloaded.
   if(!rpSplitCommissionList && pSystematic)
   {
      pSystematic->getField(ifds::TransNum, dstrTransNum, idDataGroup, true);
      pSystematic->getField(ifds::TransType, dstrTransType, idDataGroup, true);
      pSystematic->getField(ifds::AccountNum, dstrAccountNum, idDataGroup, true);
      pSystematic->getField(ifds::FundCode, dstrFund, idDataGroup, true);
      pSystematic->getField(ifds::ClassCode, dstrClass, idDataGroup, true);
      /*pSystematic->getField(ifds::BrokerCode, dstrBrokerCode, idDataGroup, true); 
      pSystematic->getField(ifds::BranchCode, dstrBranchCode, idDataGroup, true);
      pSystematic->getField(ifds::SalesRepCode, dstrSalesRepCode, idDataGroup, true);*/
      pSystematic->getField(ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, true);
      MFAccount *pMFAccount=NULL;
	  if (getWorkSession().getMFAccount ( idDataGroup, dstrAccountNum, pMFAccount) <= WARNING && 
									   pMFAccount)
	  {
		  pMFAccount->getField(ifds::BrokerCode, dstrBrokerCode, idDataGroup, true);
		  pMFAccount->getField(ifds::BranchCode, dstrBranchCode, idDataGroup, true);
          pMFAccount->getField(ifds::SalesRepCode, dstrSalesRepCode, idDataGroup, true);
	  }
	  pSystematic->getField(ifds::RDRAdvice, dstrRDRAdvice, idDataGroup, false);
      getField(ifds::TransSeq, dstrTransSeq, idDataGroup, true);
      rpSplitCommissionList = new SplitCommissionList(*this);
      //calls view 151
      if (rpSplitCommissionList->init(dstrTransNum, dstrTransSeq, dstrTransType, dstrAccountNum,
         dstrFund, dstrClass, dstrBrokerCode, dstrBranchCode, dstrSalesRepCode, dstrEffectiveDate,
         NULL_STRING,dstrRDRAdvice) <= WARNING)
      {
         setObject(rpSplitCommissionList, SPLITCOM_LIST, OBJ_ACTIVITY_NONE, idDataGroup); 
     
         DString maxFeeRate;
		 getMaxFeeRate(rpSplitCommissionList, idDataGroup);
      }
      else
      {
         delete rpSplitCommissionList;
         rpSplitCommissionList = NULL;
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************************************************
SEVERITY SysAllocation::getMaxFeeRate(SplitCommissionList *&rpSplitCommissionList,const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getMaxFeeRate"));
   
   Systematic *pSystematic = dynamic_cast< Systematic * >(getParent()->getParent());

   DString AccountNum;
   DString AccountTo; 
   DString Fund; 
   DString FundTo; 
   DString Class;
   DString ClassTo;
   DString PUD; 
   DString FlatPrcnt;
   DString InPayType; 
   DString IAmount; 
   DString InTransType; 
   DString EffectiveDate;
   DString InGrossNet;
   DString BrokerCode; 
   DString BranchCode; 
   DString SlsRepCode; 
   DString SettleCurrency;

   MFAccount *pMFAccount = dynamic_cast<MFAccount*>(getParent()->getParent()->getParent()->getParent());
   if( pMFAccount )
   {
	   pMFAccount->getField (ifds::AccountNum, AccountNum, idDataGroup, false);
	   pMFAccount->getField (ifds::BrokerCode, BrokerCode, idDataGroup, false);
       pMFAccount->getField (ifds::BranchCode, BranchCode, idDataGroup, false);
       pMFAccount->getField (ifds::Slsrep, SlsRepCode, idDataGroup, false);
   }
   pSystematic->getField (ifds::AccountTo, AccountTo, idDataGroup, false);//This should never occur.
   pSystematic->getField (ifds::AmountType, PUD, idDataGroup, false);
   pSystematic->getField (ifds::FlatPercent, FlatPrcnt, idDataGroup, false);
   pSystematic->getField (ifds::PayType, InPayType, idDataGroup, false);
   pSystematic->getField (ifds::EffectiveDate, EffectiveDate, idDataGroup, false);
   pSystematic->getField (ifds::GrossOrNet, InGrossNet, idDataGroup, false);
   
   getField (ifds::SettleCurrency, SettleCurrency, idDataGroup, false);
   getField (ifds::FundCode, Fund, idDataGroup, false);
   getField (ifds::ClassCode, Class, idDataGroup, false);
   getField (ifds::AllocAmount, IAmount, idDataGroup, false);
   getField (ifds::TransType, InTransType, idDataGroup, false);

   SplitCommissionList lpSplitCommissionList(*this);
   //call the default split commission view
   if (lpSplitCommissionList.init(	AccountNum,
									AccountTo,
									Fund,
									FundTo,
									Class,
									ClassTo,
									PUD,
									FlatPrcnt,
									InPayType,
									IAmount,
									InTransType,
									EffectiveDate,
									InGrossNet, 
									BrokerCode,
									BranchCode,
									SlsRepCode,
									SettleCurrency,
									NULL_STRING, //record type 
									I_("0.0"), // exchange rate for systematic should be zero,
									NULL_STRING,NULL_STRING,NULL_STRING,idDataGroup) <= WARNING)
   {
	   DString maxFeeRate;
	   lpSplitCommissionList.getField(ifds::MaxFeeRate, maxFeeRate, idDataGroup, false);		
	   rpSplitCommissionList->setField(ifds::MaxFeeRate, maxFeeRate, idDataGroup);
   }
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
void SysAllocation::GetDefaultSplitComm (const BFDataGroupId& idDataGroup)
{   
   setFieldNoValidate(ifds::Default, YES, idDataGroup, false);
}

//******************************************************************************
SEVERITY SysAllocation::validateAllocCurrency(const BFDataGroupId& idDataGroup) 
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateAllocCurrency"));

  /* DString dstrmultiCurrency;
   getWorkSession().getOption(ifds::MultiCurrency, dstrmultiCurrency, idDataGroup, false);

   if(dstrmultiCurrency == NO)
   {
      int nNbrOfItemsInList = 0;
      SysAllocationList *pParent = dynamic_cast<SysAllocationList *>(getParent());
      if(pParent)
         nNbrOfItemsInList = pParent->getNbrOfAllocInList(idDataGroup);
      else
      {
         assert(0);
         return(GETCURRENTHIGHESTSEVERITY());
      }


      FundDetail *pFundDetail = NULL;
      DString dstrfundCode, dstrclassCode;
      getField(ifds::FundCode, dstrfundCode, idDataGroup);
      getField(ifds::ClassCode, dstrclassCode, idDataGroup);

      if(getWorkSession().getFundDetail(dstrfundCode, dstrclassCode, idDataGroup, pFundDetail))
      {

         DString dstrCurrency, dstrsettleCurrency;

         pFundDetail->getField(ifds::Currency, dstrCurrency, idDataGroup, false);
         if(dstrCurrency.strip().upperCase().empty())
         {
            assert(0);
            return(GETCURRENTHIGHESTSEVERITY());
         }

         if(nNbrOfItemsInList == 1)
            pParent->setField(ifds::SettleCurrency, dstrCurrency, idDataGroup, false);

         else
         {
            pParent->getField(ifds::SettleCurrency, dstrsettleCurrency, idDataGroup, false); 

            if(dstrsettleCurrency != dstrCurrency)
               ADDCONDITIONFROMFILE(CND::ERR_FUND_CURRENCY_DIFFERENT);
         }
      }
      else
         assert(0);
   }
*/

   DString currChkByTaxType,
      fundCode, classCode;
   FundDetail *pFundDetail = NULL;

   getField (ifds::FundCode, fundCode, idDataGroup, false);
   getField (ifds::ClassCode, classCode, idDataGroup, false);
   if (getWorkSession().getFundDetail (fundCode, classCode, idDataGroup, pFundDetail)  &&
      pFundDetail)
   {
      DString fundCurrency;

      pFundDetail->getField(ifds::Currency, fundCurrency, idDataGroup, false);
      getWorkSession().getOption (ifds::CurrChkByTaxType, 
         currChkByTaxType, idDataGroup, false);
      if  (currChkByTaxType == I_("Y") && !fundCurrency.empty())
      { 
         DString taxType,
            invalidCurr,
            taxTypeByCurrChk;
    
         MFAccount *pMFAccount = 
            dynamic_cast< MFAccount *>(getParent()->getParent()->getParent()->getParent());
       
         pMFAccount->getField (ifds::TaxType, taxType, idDataGroup);
         taxType.strip().upperCase();
         getWorkSession().getOption ( ifds::TaxTypeByCurrChk,
                                      taxTypeByCurrChk,
                                      idDataGroup,
                                      false
                                    );
         getWorkSession().getOption ( ifds::InvalidCurr,
                                      invalidCurr,
                                      idDataGroup,
                                      false
                                    );
         if ( DSTCommonFunctions::codeInList (taxType, taxTypeByCurrChk) &&
              DSTCommonFunctions::codeInList (fundCurrency, invalidCurr)
            )
         {
            ADDCONDITIONFROMFILE (CND::ERR_TAX_TYPE_CANNOT_TRADE_IN_THE_CURRENCY);
         }
      }
   }      
   return GETCURRENTHIGHESTSEVERITY();

}

//******************************************************************************
bool SysAllocation::splitCommActive(const BFDataGroupId& idDataGroup)
{
   bool bSplitCommActive = false;

   if(!SplitCommission::isTypeZERO(getWorkSession()))
   {
      FundDetail *pFundDetail = NULL;
      DString dstrfundCode, dstrclassCode;

      getField(ifds::FundCode, dstrfundCode, idDataGroup);
      getField(ifds::ClassCode, dstrclassCode, idDataGroup);
      dstrfundCode.strip().upperCase();
      dstrclassCode.strip().upperCase();

      if((!dstrfundCode.empty() && !dstrclassCode.empty())
          && getWorkSession().getFundDetail(dstrfundCode, dstrclassCode, idDataGroup, pFundDetail))
      {
         DString dstrTransType;

         getField(ifds::TransType, dstrTransType, idDataGroup, false);
         bSplitCommActive = pFundDetail->splitCommActive(getWorkSession(), dstrTransType, idDataGroup) ;      
      }
   }
   return bSplitCommActive;
}

//*********************************************************************************
SEVERITY SysAllocation::setTransTypePACIdFromSystematic(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("setTransTypePACIdFromSystematic"));
   const Systematic *pSystematic = 
      dynamic_cast< const Systematic * >(getParent()->getParent());
   DString strValue;

   pSystematic->getField(ifds::TransType,strValue,idDataGroup,false);
   setFieldNoValidate(ifds::TransType,strValue,idDataGroup,false,true,false,false);
   pSystematic->getField(ifds::PACSWPId,strValue,idDataGroup,false);
   setFieldNoValidate(ifds::PACSWPId,strValue,idDataGroup,false,true,false,false);
   setFieldNoValidate(ifds::Level,I_("3"),idDataGroup,false,true,false,false);
   setUpdatedFlag(ifds::TransType,  idDataGroup, false);
   setUpdatedFlag(ifds::PACSWPId,  idDataGroup, false);
   setUpdatedFlag(ifds::Level,  idDataGroup, false);
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/SysAllocation.cpp-arc  $
 * 
 *    Rev 1.89   Jul 31 2012 16:42:42   wp040027
 * Sync up: IN# 3006862-CPF-Enable Fee in PAC/Corrected default Fee in PAC and Trade screen/Max Fee Validation
 * 
 *    Rev 1.88   Jul 26 2012 10:51:36   wp040027
 * P0198518 - RDR Functionality
 * 
 *    Rev 1.87   May 11 2012 13:53:04   jankovii
 * P0186481 FN07 - GWA LWA Payment Options for SWP RRIF
 * 
 *    Rev 1.86   Jan 26 2012 14:34:08   if991250
 * P0186477- GIA trading Screen Issue - Seg fund validation needs to be executed only if the fund category is segregated ('S').
 * 
 *    Rev 1.85   Jan 11 2012 15:25:28   dchatcha
 * IN# 2796443 - Validation rule for Allocated Auto Transfer
 * 
 *    Rev 1.84   Nov 27 2011 19:43:00   popescu
 * INA Commission Work
 * 
 *    Rev 1.83   Feb 27 2011 20:56:30   panatcha
 * ticket 2404299 (REG_RL11.2/101 - PAC set up and delete issues)
 * 
 *    Rev 1.82   Nov 19 2009 22:28:10   wutipong
 * IN1845806 - more modification based on Zijian's comments.
 * 
 *    Rev 1.81   Nov 06 2009 23:43:08   wutipong
 * IN1845806 - Unable to set up a  SWP - PIN - (Ifast Desktop)
 * 
 *    Rev 1.80   13 Nov 2008 14:53:18   kovacsro
 * IN#1384346 - Edits on Allocation screen for Stopped Funds
 * 
 *    Rev 1.79   Sep 29 2005 15:08:08   ZHANGCEL
 * PET1244 - FN01 -- Code clean up
 * 
 *    Rev 1.78   Sep 28 2005 16:21:58   ZHANGCEL
 * PET1244 - FN01 - Seg Fund Evolution enhancement
 * 
 *    Rev 1.77   May 18 2005 09:03:36   yingbaol
 * PET1203,FN01 Commission-Class A enhancement
 * 
 *    Rev 1.76   Mar 30 2005 14:37:46   popescu
 * Incident# 275373, added an extra parameter to view 151 (TransId), split commission trans history/pending trades inquiry
 * 
 *    Rev 1.75   Mar 17 2005 15:13:16   porteanm
 * Incident 262660 - PAC Eff Date validation for single fund and alloc.
 * 
 *    Rev 1.74   Dec 10 2004 17:35:04   hernando
 * PET910 - Changed pow call.
 * 
 *    Rev 1.73   Nov 27 2004 19:44:58   popescu
 * PET 1117/56, removed two validation methods from MgmtCoOptions. Either we have all of them here or none. Moved the methods to the CBO's that require 'em.
 * 
 *    Rev 1.72   Nov 14 2004 14:56:16   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.71   May 13 2004 10:45:48   AGUILAAM
 * PTS 10029479 - purchase/PAC on US funds not allowed for RRSP accounts, applies to both single-fund and allocated transactions
 * 
 *    Rev 1.70   Apr 23 2004 18:12:12   WINNIE
 * Ticket 10021181 : do not force the validation since the capped fund logic will be trigger when it is not applicable to existing data
 * 
 *    Rev 1.69   Feb 10 2004 16:00:08   YINGBAOL
 * 10021181:Validate Amount for Cap fund
 * 
 *    Rev 1.68   Dec 12 2003 13:25:34   AGUILAAM
 * PTS 10024124, split comm, re-work
 * 
 *    Rev 1.67   Dec 08 2003 15:28:30   popescu
 * PTS 10023645, split commission re-work
 * 
 *    Rev 1.66   Sep 04 2003 17:15:26   HSUCHIN
 * PTS 10021181 - bug fix for capped fund rule for normal Allocations
 * 
 *    Rev 1.65   May 13 2003 19:36:52   popescu
 * PTS 10016228 & 10016241
 * 
 *    Rev 1.64   May 13 2003 17:07:16   popescu
 * Split commission re-work, part II
 * 
 *    Rev 1.63   May 13 2003 10:06:18   popescu
 * Split commission re-work
 * 
 *    Rev 1.62   May 06 2003 13:54:52   popescu
 * Fixed call to 158 for default split commission, the fund and fundto fields were sent empty
 * 
 *    Rev 1.61   Apr 29 2003 17:13:50   popescu
 * PTS 10016204
 * 
 *    Rev 1.60   Apr 29 2003 10:53:14   sanchez
 * Sync. up with v1.56.1.1 PTS# 10016291
 * 
 *    Rev 1.59   Apr 14 2003 16:27:38   popescu
 * PTS 10011081- split commision amount is being calculated by the view side
 * 
 *    Rev 1.58   Apr 11 2003 10:11:22   FENGYONG
 * call amount initminimum pur check
 * 
 *    Rev 1.57   Mar 21 2003 18:25:22   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.56   Jan 12 2003 16:01:18   WINNIE
 * New logic for stop flag checking at funddetail level, it now allow user to issue error or warning based on the set up in the database; It allow allow override based on the tax type, account type, acct designation, tax juris and prov of resident value of the MFaccount and Shareholder; New logic for fund/class validation against salesrep
 * 
 *    Rev 1.55   Jan 08 2003 18:32:34   WINNIE
 * Sync up Release 49  Rev 1.52   Oct 13 2002 18:12:54   broker fund logic for ticket 10009829 : edit check of fund/class against broker code; same logic also added to AutoTransAllocation; 
 * 
 *    Rev 1.54   Dec 04 2002 16:20:14   KOVACSRO
 * more rxTransType changes.
 * 
 *    Rev 1.53   Nov 29 2002 10:25:36   KOVACSRO
 * rxTransType changes
 * 
 *    Rev 1.52   Oct 09 2002 23:55:02   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.51   Sep 09 2002 13:39:36   HERNANDO
 * PTS 10009499 - Sync w/rel 47 of Stop purchase and capped fund logic.
 * 
 *    Rev 1.50   Aug 29 2002 12:56:42   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.49   Jun 19 2002 14:10:14   KOVACSRO
 * formatted versus unformatted.
 * 
 *    Rev 1.48   Jun 04 2002 17:34:04   ZHANGCEL
 * PTS 10008333: bug fix for the persentage and AllocAmount calculate problem -- added a override  function: setField() and changed the logic in doApplyRelatedChanges()
 * 
 *    Rev 1.47   22 May 2002 18:29:54   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.46   Dec 21 2001 17:42:12   ZHANGCEL
 * Added code in ValidateFundClass() in order to  trigger seg fund validation
 * 
 *    Rev 1.45   09 Nov 2001 09:15:10   HSUCHIN
 * transaction builder bug fix
 * 
 *    Rev 1.44   05 Nov 2001 10:55:48   HSUCHIN
 * bug fix for getSplitCommissionList.   CommissionType check is insert, if 0 - no Split Commission will be returned.   bug fix to scenario where a fund with split is modified to a fund with no split.
 * 
 *    Rev 1.43   01 Nov 2001 13:57:16   HSUCHIN
 * prevent Split Commission from being downloaded
 * 
 *    Rev 1.42   26 Sep 2001 17:01:22   HSUCHIN
 * changed SplitComm check to Commission Type check
 * 
 *    Rev 1.41   26 Sep 2001 13:58:50   HSUCHIN
 * added function to retrieve systematic effective date and bus rule to active/deactive split commission
 * 
 *    Rev 1.40   Aug 15 2001 19:09:30   YINGBAOL
 * fix bug
 * 
 *    Rev 1.39   Jul 29 2001 14:56:22   YINGBAOL
 * change condition--- version sync. up
 * 
 *    Rev 1.38   18 Jul 2001 16:06:00   HSUCHIN
 * bug fix for default split commission
 * 
 *    Rev 1.37   17 Jul 2001 15:34:10   HSUCHIN
 * added transtype translation for saving plans
 * 
 *    Rev 1.36   Jun 26 2001 12:55:10   PURDYECH
 * Infrastructure Release 1.9 Integration.
 * 
 *    Rev 1.35   Jun 22 2001 16:59:42   HERNANDO
 * Removed validateAllocCurrency call.
 * 
 *    Rev 1.34   18 Jun 2001 13:53:30   KOVACSRO
 * quick fix for multicurrency bug.
 * 
 *    Rev 1.33   18 Jun 2001 11:53:12   KOVACSRO
 * some modifications for multicurrency.
 * 
 *    Rev 1.32   17 May 2001 10:43:32   HSUCHIN
 * added dstcworksession point to splitcommactive function call
 * 
 *    Rev 1.31   11 May 2001 09:24:14   HSUCHIN
 * Session management restructuring
 * 
 *    Rev 1.30   02 May 2001 16:44:08   HSUCHIN
 * set Default to NO when SplitComm flag is set to NO
 * 
 *    Rev 1.29   02 May 2001 16:40:38   HSUCHIN
 * bug fix to enable split comm 
 * 
 *    Rev 1.28   02 May 2001 13:00:52   HSUCHIN
 * added severity check after init
 * 
 *    Rev 1.27   01 May 2001 10:12:18   HSUCHIN
 * changed DBR::Default to be initialized with setFieldNoValidate rather than setElement Value
 * 
 *    Rev 1.26   28 Apr 2001 15:14:14   HSUCHIN
 * removed recalculate split com and ensure split commission exists before getting default
 * 
 *    Rev 1.25   27 Apr 2001 14:34:32   HSUCHIN
 * changed GetSplitCommList to delete an existing split when the new fund has no split commission
 * 
 *    Rev 1.24   Apr 26 2001 13:01:52   JANKAREN
 * Modify logic for validateAllocCurrency
 * 
 *    Rev 1.23   Apr 26 2001 10:12:22   WINNIE
 * new method for split flag; clean up
 * 
 *    Rev 1.22   25 Apr 2001 13:39:50   HSUCHIN
 * minor code clean up and extra validation on getSplitcommissionList to ensure split comm exists
 * 
 *    Rev 1.21   24 Apr 2001 13:20:22   HSUCHIN
 * Logic to retrieve the original split commission before downloading the default split commission.
 * 
 *    Rev 1.20   17 Apr 2001 10:35:46   HSUCHIN
 * minor bug fix for Default flag for split commissions
 * 
 *    Rev 1.19   14 Apr 2001 10:30:46   HSUCHIN
 * Removed setField and moved code to doapplyreleated changes.   Default SplitCommission implementation and changes.
 * 
 *    Rev 1.18   04 Apr 2001 14:00:36   HSUCHIN
 * added validateAllocCurrency function
 * 
 *    Rev 1.17   03 Apr 2001 20:15:42   HSUCHIN
 * implemented split commissions
 * 
 *    Rev 1.16   01 Apr 2001 12:50:30   HSUCHIN
 * added default split commission and code cleanup
 * 
 *    Rev 1.15   Mar 20 2001 15:42:02   HSUCHIN
 * Make sure there is a split commission before view call is issued.
 * 
 *    Rev 1.14   Mar 18 2001 12:26:48   HSUCHIN
 * Split Commissions Hook up
 * 
 *    Rev 1.13   Dec 17 2000 20:24:30   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.12   Sep 25 2000 16:10:46   HUANGSHA
 * no validate for amount if Systematic total amount is zero
 * 
 *    Rev 1.11   Sep 15 2000 11:55:58   WINNIE
 * Add logic to validate fund and class for existance of the code. Fix cross edit for fund and class
 * 
 *    Rev 1.10   Sep 11 2000 14:01:20   YINGBAOL
 * fix effective date
 * 
 *    Rev 1.9   Sep 01 2000 15:27:24   HUANGSHA
 * sync with M3
 * 
 *    Rev 1.8   Aug 28 2000 09:59:56   ZHANGCEL
 * Fund number problems
 * 
 *    Rev 1.7   Jul 25 2000 17:11:14   WINNIE
 * Edit check for Fund, Class, FundTo, ClassTo by calling MFAccount method
 * 
 *    Rev 1.6   Jun 13 2000 18:22:08   DT24433
 * new Infra interfaces use ClientLocale
 // 
*/