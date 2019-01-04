//********************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2004 By International Financial Data Services.
//
//
//********************************************************************************
//
// ^FILE   : MatSweepInstrDetails.cpp
// ^AUTHOR : 
// ^DATE   : 
//
//********************************************************************************
#include "stdafx.h"
#include "MatSweepInstrDetails.hpp"
#include "MatSweepInstrDetailsList.hpp"
#include "matsweepinstrbanklist.hpp"
#include "FundLmtOverrideList.hpp"
#include "shareholder.hpp"
#include "fundlmtoverride.hpp"
#include "giainvattriblist.hpp"
#include "fundmasterlist.hpp"
#include "addresslist.hpp"
#include "mgmtco.hpp"
#include "funddetail.hpp"
#include "funddetaillist.hpp"
#include "accshrnumcheck.hpp"
#include "mfaccount.hpp"
#include "dynamicsublistholder.hpp"

#include <ifastdataimpl\dse_dstc0149_vw.hpp> //P0186486_FN15_The Source of Funds
#include <ifastdataimpl\dse_dstc0428_vwrepeat_record.hpp> 


namespace
{
   const I_CHAR * const CLASSNAME            = I_( "MatSweepInstrDetails" );
   const I_CHAR * const ACCOUNT              = I_( "A" );
   const I_CHAR * const INVESTMENT           = I_( "I" );
   const I_CHAR * const CASH_SWEEP           = I_( "CS" );
   const I_CHAR * const MATURITY_INTEREST    = I_( "GI,GM,GB" );
   const I_CHAR * const INTEREST             = I_( "GI" );
   const I_CHAR * const ACCTLEVEL            = I_( "Acct" );
   const I_CHAR * const FRONTENDLOAD         = I_("FEL");
   const I_CHAR * const CASH                 = I_("CS");
   const I_CHAR * const REINVEST             = I_("RI");
   const I_CHAR * const REDIRECT             = I_("RD");
   const I_CHAR * const EFT                  = I_("E");
   const I_CHAR * const CHEQUE               = I_("S");
   const I_CHAR * const SUPPRESS             = I_("X");
   const I_CHAR * const CASH_FUND            = I_("CASH");
   const I_CHAR * const PERCENT              = I_("P");
   const I_CHAR * const YES                  = I_("Y");
   const I_CHAR * const YES1                 = I_("1");
   const I_CHAR * const NO                   = I_("0");
   const I_CHAR * const FORCED_RATE          = I_("2");
   const I_CHAR * const DERIVED_FROM_CONF    = I_("1");
   const I_CHAR * const PURCHASE             = I_("ED");
   const I_CHAR * const SEG_CASH_SWP_RULE    = I_("44");
   const I_CHAR * const EMPLOYEE             = I_("08");
   const I_CHAR * const AGENT                = I_("09");

}

namespace ifds
{
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFTextFieldId MatSwpInstructionType;
   extern CLASS_IMPORT const BFTextFieldId LoadType;
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFDecimalFieldId Amount;
   extern CLASS_IMPORT const BFDecimalFieldId MinInitAmt;
   extern CLASS_IMPORT const BFTextFieldId DataFound;
   extern CLASS_IMPORT const BFTextFieldId Fund;
   extern CLASS_IMPORT const BFTextFieldId Class;
   extern CLASS_IMPORT const BFTextFieldId MaturityInstructionsPayType;
   extern CLASS_IMPORT const BFTextFieldId SplitType;
   extern CLASS_IMPORT const BFTextFieldId MatInstrDetailXEdit;
   extern CLASS_IMPORT const BFTextFieldId MultiCurrency;
   extern CLASS_IMPORT const BFTextFieldId MatInstrLevel;
   extern CLASS_IMPORT const BFTextFieldId GoodBad;
   extern CLASS_IMPORT const BFTextFieldId MinInitAmtSeverityCode;
   extern CLASS_IMPORT const BFTextFieldId ProcType;
   extern CLASS_IMPORT const BFNumericFieldId ShrNum;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFTextFieldId MatInstrAddress;
   extern CLASS_IMPORT const BFTextFieldId MatInstrFundClassXEdit;
   extern CLASS_IMPORT const BFTextFieldId TaxType;
   extern CLASS_IMPORT const BFIntegerFieldId InvestTerm;
   extern CLASS_IMPORT const BFTextFieldId CommRedRate;
   extern CLASS_IMPORT const BFDecimalFieldId IntRate;
   extern CLASS_IMPORT const BFTextFieldId FromFundNumber;
   extern CLASS_IMPORT const BFTextFieldId SrcOfFunds_IA_GIC; //P0186486_FN15_The Source of Funds
   extern CLASS_IMPORT const BFTextFieldId SrcOfFunds_IA; //P0186486_FN15_The Source of Funds
   extern CLASS_IMPORT const BFTextFieldId InvHisStatus;
   extern CLASS_IMPORT const BFTextFieldId AcctDesignation;
   extern CLASS_IMPORT const BFTextFieldId IntCalcMthdList;
   extern CLASS_IMPORT const BFTextFieldId FundRelnCode;
}

namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const REFERENCE_NO_IS_MANDATORY_FOR_SOURCE_OF_FUND;
   extern CLASS_IMPORT I_CHAR * const SUPPRESS_PAYTYPE_REQUIRED_FOR_FUND_SOURCE; //P0186486_FN15_The Source of Funds
   extern CLASS_IMPORT I_CHAR * const CASH_INSTR_NOT_ALLOWED_FOR_REG_ACC;
}

namespace CND
{  // Conditions used
   extern const long ERR_FUND_CANNOTBE_DIF;
   extern const long ERR_INVALID_ACCOUNT_NUMBER;
   extern const long ERR_INVALID_ROLLOVER_TYPE;
   extern const long ERR_VALUE_BETWEEN_0_AND_100;
   extern const long ERR_WRONG_INTCREDFREQ;
   extern const long ERR_MATURITYBANK_IS_MISSING;
   extern const long WARN_INVALID_FUND_NUMBER;
   extern const long ERR_REFERENCE_NO_IS_MANDATORY_FOR_SOURCE_OF_FUND;//P0186486_FN15_The Source of Funds
   extern const long WARN_REFERENCE_NO_IS_MANDATORY_FOR_SOURCE_OF_FUND;
   extern const long ERR_SUPPRESS_PAYTYPE_REQUIRED_FOR_FUND_SOURCE; //P0186486_FN15_The Source of Funds
   extern const long WARN_SUPPRESS_PAYTYPE_REQUIRED_FOR_FUND_SOURCE; 
   extern const long ERR_CASH_INSTR_NOT_ALLOWED_FOR_REG_ACC; 
   extern const long WARN_CASH_INSTR_NOT_ALLOWED_FOR_REG_ACC;
}

namespace ACCT_DESIGNATION
{
   const I_CHAR * const CLIENT         = I_("1");
}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const REDEMPTION;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
   // Field DD Id,                  State Flags,   Group Flags 
   { ifds::DistribDetlUUID,         BFCBO::NONE,		0 },
   { ifds::IntInvestId,             BFCBO::NONE,		0 },
   { ifds::RolloverType,            BFCBO::REQUIRED,	0 },
   { ifds::AccountTo,               BFCBO::REQUIRED,	0 },
   { ifds::FundTo,                  BFCBO::REQUIRED,	0 },
   { ifds::ClassTo,                 BFCBO::REQUIRED,	0 },
   { ifds::RemainingFleg,           BFCBO::REQUIRED,	0 },
   { ifds::Currency,                BFCBO::NONE,		0 },
   { ifds::Percentage,              BFCBO::REQUIRED,	0 },
   { ifds::PayType,                 BFCBO::NONE,		0 },
   { ifds::PayTypeDesc,             BFCBO::NONE,		0 },
   { ifds::CommReduction,           BFCBO::NONE,		0 },
   { ifds::IntInvestType,           BFCBO::NONE,		0 },
   { ifds::FELAmt,                  BFCBO::NONE,		0 },
   { ifds::IntInvestTerm,           BFCBO::NONE,		0 },
   { ifds::IntCalcMthd,             BFCBO::NONE,		0 },
   { ifds::ForcedRate,              BFCBO::NONE,		0 },
   { ifds::ForcedRateAmt,           BFCBO::NONE,		0 },
   { ifds::IntCredFreq,             BFCBO::NONE,		0 },
   { ifds::BusinessType,            BFCBO::NONE,		0 },
   { ifds::RefNum,                  BFCBO::NONE,		0 },
   { ifds::AddlAmt,                 BFCBO::NONE,		0 },
   { ifds::BankAcctId,              BFCBO::NONE,		0 },
   { ifds::BankAcctUse,             BFCBO::NONE,		0 },
   { ifds::BankIdType,              BFCBO::NONE,		0 },
   { ifds::BankIdValue,             BFCBO::NONE,		0 },
   { ifds::BankTransitNo,           BFCBO::NONE,		0 },
   { ifds::BankSwiftCode,           BFCBO::NONE,		0 },
   { ifds::BankRefNumber,           BFCBO::NONE,		0 },
   { ifds::InstName,                BFCBO::NONE,		0 },
   { ifds::BankAddr1,               BFCBO::NONE,		0 },
   { ifds::BankAddr2,               BFCBO::NONE,		0 },
   { ifds::BankAddr3,               BFCBO::NONE,		0 },
   { ifds::BankAddr4,               BFCBO::NONE,		0 },
   { ifds::BankAddr5,               BFCBO::NONE,		0 },
   { ifds::BankPostal,              BFCBO::NONE,		0 },
   { ifds::BankCountry,             BFCBO::NONE,		0 },
   { ifds::BankAcctType,            BFCBO::NONE,		0 },
   { ifds::BankAcctTypeDesc,        BFCBO::NONE,		0 },
   { ifds::BankAcctCurrency,        BFCBO::NONE,		0 },
   { ifds::BankAcctCurrDesc,        BFCBO::NONE,		0 },
   { ifds::BankEffectiveDate,       BFCBO::NONE,		0 },
   { ifds::BankStopDate,            BFCBO::NONE,		0 },
   { ifds::PayMethod,               BFCBO::NONE,		0 },
   { ifds::ACHProcessor,            BFCBO::NONE,		0 },
   { ifds::BankContact,             BFCBO::NONE,		0 },
   { ifds::BankCorrespondent,       BFCBO::NONE,		0 },
   { ifds::MatInstrAddrCode,        BFCBO::NONE,		0 },
   { ifds::BankId,                  BFCBO::NONE,		0 },
   { ifds::BankAcctNum,             BFCBO::NONE,		0 },
   { ifds::BankAcctName,            BFCBO::NONE,		0 },
   { ifds::IntInvestUUID,           BFCBO::NONE,		0 },
   { ifds::DistribDetlVersion,      BFCBO::NONE,		0 },
   { ifds::BankAcctVersion,         BFCBO::NONE,		0 },
   { ifds::IntInvestVer,            BFCBO::NONE,		0 },
   { ifds::Amount,                  BFCBO::NONE,		0 },
   { ifds::MatInstrDetailXEdit,     BFCBO::IMMEDIATE_VALIDATION, 0 },
   { ifds::MatInstrFundClassXEdit,  BFCBO::IMMEDIATE_VALIDATION, 0 },	
   { ifds::FromFundNumber,          BFCBO::NONE,         0 },
   { ifds::SrcOfFunds_IA,           BFCBO::NONE,         0 }, //P0186486_FN15_The Source of Funds
   { ifds::InvHisStatus,            BFCBO::NOT_ON_HOST,  0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
MatSweepInstrDetails::MatSweepInstrDetails( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
, m_multiCurrency (NULL_STRING)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );

   addCrossEdit (ifds::MatInstrDetailXEdit, ifds::FundTo);
   addCrossEdit (ifds::MatInstrDetailXEdit, ifds::RolloverType);
   addCrossEdit (ifds::MatInstrDetailXEdit, ifds::PayType);

   addCrossEdit (ifds::MatInstrFundClassXEdit, ifds::FundTo);
   addCrossEdit (ifds::MatInstrFundClassXEdit, ifds::ClassTo);

   getWorkSession ().getOption (ifds::MultiCurrency, m_multiCurrency, BF::HOST, false);
}

//******************************************************************************
MatSweepInstrDetails::~MatSweepInstrDetails()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}  

//*******************************************************************************
SEVERITY MatSweepInstrDetails::init(const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   commInit (idDataGroup);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY MatSweepInstrDetails::init(const BFData& data )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );	

   attachDataObject(const_cast<BFData&>(data), false); 

   setFundClassMinAmount (BF::HOST);

   commInit (BF::HOST);

   return(GETCURRENTHIGHESTSEVERITY());
}

//*********************************************************************************
SEVERITY MatSweepInstrDetails::doValidateField( const BFFieldId& idField, 
                                               const DString& dstrValue, 
                                               const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField" ));   

   if (idField == ifds::FundTo)
   {
      FundMasterList	*pFundMasterList; 

      if (!dstrValue.empty() && getMgmtCo().getFundMasterList (pFundMasterList) && 
         pFundMasterList)
      {
         DString dstrInstrType;

         getParent ()->getParent ()->getField (ifds::MatSwpInstructionType, dstrInstrType, idDataGroup, false);

         if (dstrInstrType == CASH_SWEEP && pFundMasterList->isDIFFund (dstrValue))
         {
            ADDCONDITIONFROMFILE (CND::ERR_FUND_CANNOTBE_DIF)
         }
      }
   }
   else if (idField == ifds::MatInstrFundClassXEdit)
   {
      validateFundClass (idDataGroup);
   }
   else if (idField == ifds::AccountTo)
   {
      // validate if account exists in the system.
      validateAssociatedNum (dstrValue, idDataGroup);
   }
   else if (idField == ifds::MatInstrDetailXEdit)
   {
      // Duplicate check
      if (isUpdatedForDataGroup (idDataGroup, true))
      {
         MatSweepInstrDetailsList *pMatSweepInstrDetailsList = dynamic_cast<MatSweepInstrDetailsList*>( getParent( ) );      

         if (pMatSweepInstrDetailsList)
         {
            DString dstrRolloverType;
            getField (ifds::RolloverType, dstrRolloverType, idDataGroup, false);
            pMatSweepInstrDetailsList->checkDuplicate( dstrRolloverType, idDataGroup );
         }
      }
   }
   else if (idField == ifds::RolloverType)
   {
      validateRolloverType (dstrValue, idDataGroup);
   }
   else if (idField == ifds::Percentage)
   {
      validatePercent (dstrValue, idDataGroup);
   }
   else if (idField == ifds::MatInstrAddrCode)
   {
      validateAddressCode (dstrValue, idDataGroup);
   }
   else if (idField == ifds::FromFundNumber )
   {
      if (!dstrValue.empty())
      {
         DString dstrFundCode, dstrClassCode;
         if ( !getWorkSession().GetFundClassCode(dstrValue, dstrFundCode, dstrClassCode) )
         {
            ADDCONDITIONFROMFILE (CND::WARN_INVALID_FUND_NUMBER);
         }
      }
   }
   else if (idField == ifds::PayType)
   {
      DString dstrInstructionType;

      getParent ()->getParent ()->getField (ifds::MatSwpInstructionType, dstrInstructionType, idDataGroup, false);

      if (dstrInstructionType == INTEREST && dstrValue == SUPPRESS )
      {
         MatSweepInstrDetailsList *pMatSweepInstrDetailsList = dynamic_cast<MatSweepInstrDetailsList*>( getParent( ) );      

         if (pMatSweepInstrDetailsList)
         {
            pMatSweepInstrDetailsList->validateInterestInstruction (idDataGroup);
         }
      }
   }
   // else if(idField ==ifds::RefNum)
   //	{//P0186486_FN15_The Source of Funds
   //   ValidateRefNum(idDataGroup);
   //	}

   return GETCURRENTHIGHESTSEVERITY();
}

//*********************************************************************************
void MatSweepInstrDetails::doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
{
   cashSweepDefaults (idDataGroup);

   DString dstrInstructionLevel, dstrIntInvestId;

   getParent ()->getParent ()->getField (ifds::MatInstrLevel, dstrInstructionLevel, idDataGroup, false);
   getParent ()->getParent ()->getField (ifds::IntInvestId, dstrIntInvestId, idDataGroup, false);
   dstrIntInvestId.stripLeading( '0' );
   if (!dstrIntInvestId.empty ())
   {
      setFieldNoValidate (ifds::IntInvestId, dstrIntInvestId, idDataGroup, false, true, true, false);
   }

   bool bRemainingReadOnly = dstrInstructionLevel == ACCOUNT ? true : false;

   setFieldNoValidate(ifds::RemainingFleg, NO, idDataGroup, bRemainingReadOnly); 
}

//****************************************************************************
SEVERITY MatSweepInstrDetails::initNew(const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initNew" ) );

   commInit(idDataGroup);

   return(GETCURRENTHIGHESTSEVERITY());
}

//*******************************************************************************
SEVERITY MatSweepInstrDetails::commInit(const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "commInit" ) );

   DString dstrEffectiveDate;
   DString dstrFundTo;
   DString dstrClassTo;
   MFAccount *pMFAccount = NULL;

   getParent ()->getParent ()->getField (ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false);
   getField (ifds::FundTo, dstrFundTo, idDataGroup, false);
   getField (ifds::ClassTo, dstrClassTo, idDataGroup, false);

   GIAInvAttribList *pGIAInvAttribList = NULL;

   getGIFundDefaults (pGIAInvAttribList, dstrFundTo, dstrClassTo, dstrEffectiveDate, idDataGroup);

   // when commission reduciton has decimal value eg. 33.3 it gets back as 33.3300 and this cannot be found
   // in substitution list this is the reason for the code bellow
   DString dstrCommReduction;
   getField (ifds::CommReduction, dstrCommReduction, idDataGroup, false);


   int pos = dstrCommReduction.find ( I_(".") ); 

   if (pos > 0)
   {
      dstrCommReduction.stripTrailing(I_CHAR('0'));
      setFieldNoValidate (ifds::CommReduction, dstrCommReduction, idDataGroup, false, true, true, false); 
   }

   intCalcMthdRelatedChanges(idDataGroup, true);
   //intAdditionalAmtRelatedChanges(idDataGroup, true);

   setRollOverFieldsReadOnly (idDataGroup);
   setRemainingFlagFieldsReadOnly (idDataGroup);
   setCASHDIFSEGFieldsReadOnly (idDataGroup, true);
   setGIAFieldsReadOnly (idDataGroup, true);

   //currency:
   bool bCurrencyReadOnly = m_multiCurrency == YES ? false : true; 
   setFieldReadOnly (ifds::Currency, idDataGroup, bCurrencyReadOnly);

   // pay type set:
   setFieldAllSubstituteValues (ifds::PayType, idDataGroup, ifds::MaturityInstructionsPayType);

   DString dstrAccountNum;

   getParent ()->getParent ()->getField (ifds::AccountNum, dstrAccountNum, idDataGroup, false);

   if (getWorkSession ().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING &&
      pMFAccount)
   {
      DString dstrNonRegNonResident;

      pMFAccount->isNonRegNonResident(dstrNonRegNonResident, idDataGroup);

      bool bReadOnly = dstrNonRegNonResident == YES ? true : false;

      setFieldReadOnly (ifds::PayType, idDataGroup, bReadOnly); 

   }

   //P0186486_FN15_The Source of Funds
   {
      DString dstrInstructionType;

      getParent ()->getParent ()->getField (ifds::MatSwpInstructionType, dstrInstructionType, idDataGroup, false);

      if(dstrInstructionType != CASH_SWEEP)
      {
         loadBusinessTypeSubslist(idDataGroup);
      }
   }

   // if record is bad set all feilds read only
   setAllFeildsReadOnly (idDataGroup);

   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************
SEVERITY MatSweepInstrDetails::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );

   if (idField == ifds::FundTo || idField == ifds::ClassTo)
   {
      fundClassRelatedChanges (idDataGroup);
   }
   else if (idField == ifds::RolloverType)
   {
      DString dstrRolloverType;

      getField (ifds::RolloverType, dstrRolloverType, idDataGroup, false);

      redirectRelatedChanges (dstrRolloverType, idDataGroup);
      reinvestRelatedChanges (dstrRolloverType, idDataGroup);
      cashRelatedChanges (dstrRolloverType, idDataGroup);
   }
   else if (idField == ifds::PayType)
   {
      DString dstrPayType;

      getField (ifds::PayType, dstrPayType, idDataGroup, false);

      payTypeRelatedChanges (dstrPayType, idDataGroup);
   }
   else if (idField == ifds::ForcedRate)
   {
      DString dstrFrocedRate;
      bool	bReadOnly = false;

      getField (ifds::ForcedRate, dstrFrocedRate, idDataGroup, false);

      if (dstrFrocedRate != FORCED_RATE)
      {
         bReadOnly = true;
         setFieldNoValidate (ifds::ForcedRateAmt, I_("0"), idDataGroup, true); 
      }

      setFieldReadOnly (ifds::ForcedRateAmt, idDataGroup, bReadOnly);
      //intAdditionalAmtRelatedChanges(idDataGroup);
   }
   else if (idField == ifds::IntCalcMthd)
   {
      intCalcMthdRelatedChanges(idDataGroup);
   }
   else if (idField == ifds::RemainingFleg)
   {
      remainingFlagRelatedChanges (idDataGroup);
   }
   else if (idField == ifds::MatInstrAddrCode)
   {
      setFieldValid (ifds::MatInstrAddress, idDataGroup, false);
   }
   else if (idField == ifds::FromFundNumber)
   {
      DString dstrFundNumber;
      getField (ifds::FromFundNumber, dstrFundNumber, idDataGroup, false);

      if (!dstrFundNumber.empty())
      {
         DString dstrFundCode, dstrClassCode;
         if (getWorkSession ().GetFundClassCode (dstrFundNumber, dstrFundCode, dstrClassCode))
         {
            setField (ifds::FundTo,   dstrFundCode, idDataGroup, false, true);
            setField (ifds::ClassTo, dstrClassCode, idDataGroup, false, true);
         }
      }
   }

   else if(idField == ifds::BusinessType)
   {  //P0186486_FN15_The Source of Funds
      businessTypeRelatedChanges( idDataGroup );
   }
   else if (idField == ifds::InvHisStatus)
   {
      setAllFeildsReadOnly (idDataGroup);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}
//*******************************************************************************
SEVERITY MatSweepInstrDetails::doValidateAll (const BFDataGroupId& idDataGroup, long lValidateGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   validateMaturityBank (idDataGroup);
   ValidateRefNum(idDataGroup); //P0186486_FN15_The Source of Funds

   DString dstrRollOverType;
   getField (ifds::RolloverType, dstrRollOverType, idDataGroup, false);

   if (dstrRollOverType == CASH)
      validateRolloverForInstrType (idDataGroup);

   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************
SEVERITY MatSweepInstrDetails::getGIFundDefaults ( GIAInvAttribList *&pGIAInvAttribList,
                                                   const DString &fundCode,
                                                   const DString &classCode,
                                                   const DString &effectiveDate,
                                                   const BFDataGroupId &idDataGroup,
                                                   bool doSideEffects)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getGIFundDefaults"));

   pGIAInvAttribList = NULL;
   bool bIsGIAFund = false;

   isGIAFund (fundCode, bIsGIAFund, idDataGroup);

   if (!fundCode.empty() && !classCode.empty() && bIsGIAFund)
   {
      DString strKey;

      strKey = I_("GIAInvAttribsList_FundCode=") + fundCode + I_(";")
         + I_("ClassCode=") + classCode + I_(";")
         + I_("TradeDate=") + effectiveDate;

      pGIAInvAttribList = dynamic_cast <GIAInvAttribList*> (getObject (strKey, idDataGroup));

      if (!pGIAInvAttribList)
      {
         pGIAInvAttribList = new GIAInvAttribList (*this);

         if (pGIAInvAttribList->init (fundCode, classCode, effectiveDate) <= WARNING)
         {
            setObject (pGIAInvAttribList, strKey, OBJ_ACTIVITY_NONE, idDataGroup);
         }
         else
         {
            delete pGIAInvAttribList;
            pGIAInvAttribList = NULL;
         }
      }

      if (doSideEffects && pGIAInvAttribList)
      {
         DString	intCalcMthd (NULL_STRING),
            dstrIntCalcMthdSubst (NULL_STRING);

         pGIAInvAttribList->getField (ifds::IntCalcMthd, intCalcMthd, idDataGroup, false);

         if (intCalcMthd == I_("S")) //simple
         {
            DString	simpleTermList,
               simpleCredFreqList;

            BFProperties *pBFPropertiesIntCalcMthd = getFieldProperties (ifds::IntCalcMthd, idDataGroup);
            BFProperties *pBFPropertiesIntCalcMthdOrig = getFieldProperties (ifds::IntCalcMthdList, BF::HOST);

            assert (pBFPropertiesIntCalcMthd);

            if (pBFPropertiesIntCalcMthd)
            {
               pBFPropertiesIntCalcMthdOrig->getAllSubstituteValues (dstrIntCalcMthdSubst);

               dstrIntCalcMthdSubst = removeItemFromSubtList (dstrIntCalcMthdSubst, I_("B"));
               dstrIntCalcMthdSubst = removeItemFromSubtList (dstrIntCalcMthdSubst, I_("C"));

               setFieldAllSubstituteValues (ifds::IntCalcMthd, idDataGroup, dstrIntCalcMthdSubst);
               pBFPropertiesIntCalcMthd->setSubstituteValues(NULL);
               intCalcMthdRelatedChanges(idDataGroup, true);

            }
         }
         else if (intCalcMthd == I_("C")) //compound
         {
            DString compoundTermList,
               compoundCredFreqList;

            BFProperties *pBFPropertiesIntCalcMthd = getFieldProperties (ifds::IntCalcMthd, idDataGroup);
            BFProperties *pBFPropertiesIntCalcMthdOrig = getFieldProperties (ifds::IntCalcMthdList, BF::HOST);

            assert (pBFPropertiesIntCalcMthd);

            if (pBFPropertiesIntCalcMthd)
            {
               pBFPropertiesIntCalcMthdOrig->getAllSubstituteValues (dstrIntCalcMthdSubst);

               dstrIntCalcMthdSubst = removeItemFromSubtList (dstrIntCalcMthdSubst, I_("B"));
               dstrIntCalcMthdSubst = removeItemFromSubtList (dstrIntCalcMthdSubst, I_("S"));

               setFieldAllSubstituteValues (ifds::IntCalcMthd, idDataGroup, dstrIntCalcMthdSubst);
               pBFPropertiesIntCalcMthd->setSubstituteValues(NULL);
               intCalcMthdRelatedChanges(idDataGroup, true);
            }
         }
         else if (intCalcMthd == I_("B"))
         {
            BFProperties *pBFPropertiesIntCalcMthd = getFieldProperties (ifds::IntCalcMthd, idDataGroup);
            BFProperties *pBFPropertiesIntCalcMthdOrig = getFieldProperties (ifds::IntCalcMthdList, BF::HOST);

            assert (pBFPropertiesIntCalcMthd);

            if (pBFPropertiesIntCalcMthd)
            {
               pBFPropertiesIntCalcMthdOrig->getAllSubstituteValues (dstrIntCalcMthdSubst);

               dstrIntCalcMthdSubst = removeItemFromSubtList (dstrIntCalcMthdSubst, I_("B"));

               setFieldAllSubstituteValues (ifds::IntCalcMthd, idDataGroup, dstrIntCalcMthdSubst);
               pBFPropertiesIntCalcMthd->setSubstituteValues(NULL);
               intCalcMthdRelatedChanges(idDataGroup, true);
            }
         }

         DString	commRedRateList,
            commRedRateListSubSt(NULL_STRING);

         pGIAInvAttribList->getField (ifds::CommRedRateList, commRedRateList, idDataGroup, false);

         if(!commRedRateList.empty())
         {
            DString::size_type pos = 0;
            DString dstrItem_;

            do
            {
               EXTRACT_VALUE(commRedRateList, dstrItem_);
               commRedRateListSubSt  += dstrItem_ + I_("=") + dstrItem_ + I_(";");
               CHOP_STRING (commRedRateList);
            }
            while (commRedRateList != NULL_STRING);

            BFProperties *pBFPropertiesCommRedRate = getFieldProperties (ifds::CommReduction, idDataGroup);

            assert (pBFPropertiesCommRedRate);

            if (pBFPropertiesCommRedRate)
            {
               int pos = commRedRateListSubSt.find ( I_("0=0;") ); 
               
               if(pos < 0)
               {   
                  commRedRateListSubSt = I_("0=0;") + commRedRateListSubSt;
               }
               
               setCommReductionEditable(idDataGroup);
               
               setFieldAllSubstituteValues (ifds::CommReduction, idDataGroup, commRedRateListSubSt);
               pBFPropertiesCommRedRate->setSubstituteValues(NULL);
            }
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//*******************************************************************************
SEVERITY MatSweepInstrDetails::setCommReductionEditable(const BFDataGroupId& idDataGroup) 
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setCommReductionEditable" ) );
	Shareholder *pShareholder = NULL;
	DString dstrShrNum;
	bool bReadOnly = false;
               
	if (getWorkSession().getShareholder (idDataGroup, dstrShrNum, pShareholder) <= WARNING)
	{
		DString dstrFundRelCode;
		pShareholder->getField (ifds::FundRelnCode, dstrFundRelCode, idDataGroup, false);
		bReadOnly = dstrFundRelCode == AGENT || dstrFundRelCode == EMPLOYEE ? true : false; 
	}
               
	setFieldReadOnly (ifds::CommReduction, idDataGroup, bReadOnly);

	return GETCURRENTHIGHESTSEVERITY ();
}

//*******************************************************************************
SEVERITY MatSweepInstrDetails::isDIFFund ( const DString& dstrFund, bool &bIsDIFFund, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "isDIFFund" ) );

   FundMasterList *pFundMasterList; 

   bIsDIFFund = false;

   if (!dstrFund.empty() && getMgmtCo().getFundMasterList (pFundMasterList) && 
      pFundMasterList)
   {
      bIsDIFFund = pFundMasterList->isDIFFund (dstrFund);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//*******************************************************************************
SEVERITY MatSweepInstrDetails::isGIAFund ( const DString& dstrFund, bool &bIsGIAFund, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "isGIAFund" ) );

   FundMasterList *pFundMasterList; 

   bIsGIAFund = false;

   if (!dstrFund.empty() && getMgmtCo().getFundMasterList (pFundMasterList) && 
      pFundMasterList)
   {
      bIsGIAFund = pFundMasterList->isGIAFund (dstrFund);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//*******************************************************************************
SEVERITY MatSweepInstrDetails::isSEGFund ( const DString& dstrFund, bool &bIsSEGFund, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "isSEGFund" ) );

   FundMasterList *pFundMasterList; 

   bIsSEGFund = false;

   if (!dstrFund.empty() && getMgmtCo().getFundMasterList (pFundMasterList) && 
      pFundMasterList)
   {
      bIsSEGFund = pFundMasterList->isSegregatedFund (dstrFund);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************** 
SEVERITY MatSweepInstrDetails::validateFundClass (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateFundClass"));

   DString fundCode;
   DString classCode;
   DString accountNum;

   getField (ifds::FundTo, fundCode, idDataGroup);
   getField (ifds::ClassTo, classCode, idDataGroup);
   getField (ifds::AccountTo, accountNum, idDataGroup);

   accountNum.stripLeading ('0').strip ();

   if (fundCode.upperCase () == CASH_FUND)
      return GETCURRENTHIGHESTSEVERITY ();

   if (!accountNum.empty() && !fundCode.empty())
   {
      MatSweepInstrDetailsList *pMatSweepInstrDetailsList = dynamic_cast<MatSweepInstrDetailsList*>( getParent( ) );      

      if (pMatSweepInstrDetailsList)
      {
         pMatSweepInstrDetailsList->validateCashSweepDetails (idDataGroup);
         pMatSweepInstrDetailsList->validateMaturityInterstDetails (idDataGroup);
      }

      if (!classCode.empty())
      {
         // validate fund/class in shgrop or portoflio
         MFAccount *pMFAccount=NULL;

         if (getWorkSession ().getMFAccount (idDataGroup, accountNum, pMFAccount) <= WARNING &&
            pMFAccount)
         {
            DString effectiveDate;
            getParent ()->getParent ()->getField (ifds::EffectiveDate, effectiveDate, idDataGroup, false);

            pMFAccount->fundClassInGroup (fundCode, classCode, effectiveDate, idDataGroup);
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//********************************************************************************
SEVERITY MatSweepInstrDetails::validatePercent (const DString &dstrPercent, const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("validatePercent"));

   DString dstrPercentage = dstrPercent;
   DString dstrSplitType;
   
   getParent ()->getParent ()->getField (ifds::SplitType, dstrSplitType, idDataGroup, false);
   dstrSplitType.strip().stripAll();

   if (dstrSplitType != PERCENT)
      return GETCURRENTHIGHESTSEVERITY();

   dstrPercentage.strip().stripAll(I_CHAR(','));

   I_CHAR *stopstring;
   double dPercent = wcstod (dstrPercentage.c_str(), &stopstring);

   if (dPercent > 100)
   {
      ADDCONDITIONFROMFILE (CND::ERR_VALUE_BETWEEN_0_AND_100);      
   }

   return GETCURRENTHIGHESTSEVERITY();
}
//****************************************************************************** 
SEVERITY MatSweepInstrDetails::fundClassRelatedChanges (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("fundClassRelatedChanges"));

   DString dstrFundCode;
   DString dstrClassCode;
   DString dstrEffectiveDate;

   getField (ifds::FundTo, dstrFundCode, idDataGroup);
   getField (ifds::ClassTo, dstrClassCode, idDataGroup);
   getParent ()->getParent ()->getField (ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false);

   if (!dstrFundCode.empty())
   {
      DString dstrInstructionType;
      bool bIsGIAFund;

      isGIAFund (dstrFundCode, bIsGIAFund, idDataGroup);
      setCASHDIFSEGFieldsReadOnly (idDataGroup);
      setGIAFieldsReadOnly (idDataGroup);

      getParent ()->getParent ()->getField (ifds::MatSwpInstructionType, dstrInstructionType, idDataGroup, false);


      if (dstrInstructionType == CASH_SWEEP)
      {
         DString dstrPercent;

         dstrPercent = bIsGIAFund ? I_("100") : I_("0"); 

         setFieldNoValidate (ifds::Percentage, dstrPercent, idDataGroup, false, true, true, false); 
      }
   }

   if (!dstrFundCode.empty() && !dstrClassCode.empty())
   {
      DString dstrFundNumber;
      getWorkSession().GetFundNumber(dstrFundCode, dstrClassCode, dstrFundNumber);
      //setField (ifds::FromFundNumber, dstrFundNumber, idDataGroup, false);
      setFieldNoValidate ( ifds::FromFundNumber, dstrFundNumber, idDataGroup, false, 
                           true, 
                           true, //notify
                           false);
      GIAInvAttribList *pGIAInvAttribList = NULL;

      getGIFundDefaults (pGIAInvAttribList, dstrFundCode, dstrClassCode, dstrEffectiveDate, idDataGroup);

      setFundClassMinAmount (idDataGroup);
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//****************************************************************************** 
SEVERITY MatSweepInstrDetails::setRollOverFieldsReadOnly (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("setRollOverFieldsReadOnly"));

   bool	bPayTypeReadOnly = true;
   bool	bAccountReadOnly = true;
   bool	bFundReadOnly = false;
   bool	bClassReadOnly = false;
   bool	bFundNumberOnly = false;
   bool	bRollOverReadOnly = true;
   bool	bPayTypeFieldsReadOnly = false;

   DString dstrRolloverType;
   DString dstrInstructionType;

   getField (ifds::RolloverType, dstrRolloverType, idDataGroup, false);

   if (dstrRolloverType == CASH)
   {
      bPayTypeReadOnly = false;
      bAccountReadOnly = true;
      bFundReadOnly = true;
      bClassReadOnly = true;
      bFundNumberOnly = true;
   }
   else if (dstrRolloverType == REINVEST)
   {
      bPayTypeReadOnly = true;
      bAccountReadOnly = true;
      bFundReadOnly = true;
      bClassReadOnly = true;
      bFundNumberOnly = true;
      bPayTypeFieldsReadOnly = true;
   }
   else if (dstrRolloverType == REDIRECT)
   {
      bPayTypeReadOnly = true;
      bAccountReadOnly = false;
      bPayTypeFieldsReadOnly = true;
   }

   getParent ()->getParent ()->getField (ifds::MatSwpInstructionType, dstrInstructionType, idDataGroup, false);

   bRollOverReadOnly = dstrInstructionType == CASH_SWEEP ? true : false;

   setFieldReadOnly (ifds::PayType, idDataGroup, bPayTypeReadOnly);
   setFieldRequired (ifds::PayType, idDataGroup, !bPayTypeReadOnly);
   setFieldReadOnly (ifds::AccountTo, idDataGroup, bAccountReadOnly);	
   setFieldReadOnly (ifds::FundTo, idDataGroup, bFundReadOnly);
   setFieldReadOnly (ifds::ClassTo, idDataGroup, bClassReadOnly);
   setFieldReadOnly (ifds::FromFundNumber, idDataGroup, bFundNumberOnly);
   setFieldReadOnly (ifds::RolloverType, idDataGroup, bRollOverReadOnly);

   setBusinessTypeFieldsReadOnly (idDataGroup);

   return GETCURRENTHIGHESTSEVERITY ();
}

//****************************************************************************** 
SEVERITY MatSweepInstrDetails::setRemainingFlagFieldsReadOnly (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("setRemainingFlagFieldsReadOnly"));

   DString dstrSplitType;
   DString dstrRemainingFleg;

   getParent ()->getParent ()->getField (ifds::SplitType, dstrSplitType, idDataGroup, false);
   getField (ifds::RemainingFleg, dstrRemainingFleg, idDataGroup, false);

   bool bRemFlegReadOnly = dstrSplitType == PERCENT ? true : false;
   bool bPercentageReadOnly = dstrRemainingFleg == YES1 ? true : false;

   setFieldReadOnly (ifds::RemainingFleg, idDataGroup, bRemFlegReadOnly);
   setFieldReadOnly (ifds::Percentage, idDataGroup, bPercentageReadOnly);

   return GETCURRENTHIGHESTSEVERITY ();
}

//****************************************************************************** 
SEVERITY MatSweepInstrDetails::resetRemainingFlag (const DString &dstrSplitType, const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("resetRemainingFlag"));

   bool bReadOnly = dstrSplitType == PERCENT ? true : false;

   setFieldNoValidate(ifds::RemainingFleg, NO, idDataGroup, true); 
   setFieldReadOnly (ifds::RemainingFleg, idDataGroup, bReadOnly);

   return GETCURRENTHIGHESTSEVERITY ();
}

//****************************************************************************** 
SEVERITY MatSweepInstrDetails::setBusinessTypeFieldsReadOnly (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("setBusinessTypeFieldsReadOnly"));

   bool	bReadOnly = true;
   DString dstrPayType;

   getField (ifds::PayType, dstrPayType, idDataGroup, false);
   bReadOnly = dstrPayType == SUPPRESS ? false : true;

   if (bReadOnly)
   {
      setFieldNoValidate (ifds::BusinessType, NULL_STRING, idDataGroup, true); 
      setFieldNoValidate (ifds::RefNum, NULL_STRING, idDataGroup, true); 
   }
   else
   {
      //P0186486_FN15_The Source of Funds
      DString dstrInstructionType;

      getParent ()->getParent ()->getField (ifds::MatSwpInstructionType, dstrInstructionType, idDataGroup, false);

      if(dstrInstructionType != CASH_SWEEP)
      {
         loadBusinessTypeSubslist(idDataGroup);
      }
   }

   setFieldReadOnly (ifds::BusinessType, idDataGroup, bReadOnly);			
   //setFieldReadOnly (ifds::RefNum, idDataGroup, bReadOnly);

   setFieldRequired (ifds::BusinessType, idDataGroup, !bReadOnly);
   setFieldRequired (ifds::RefNum, idDataGroup, !bReadOnly);
   setFieldValid (ifds::BusinessType, idDataGroup, false);
   return GETCURRENTHIGHESTSEVERITY ();
}

//****************************************************************************** 
SEVERITY MatSweepInstrDetails::setCASHDIFSEGFieldsReadOnly (const BFDataGroupId &idDataGroup, bool bInit)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("setCashSweepFieldsReadOnly"));

   DString dstrFund;
   DString dstrClass;
   bool bIsDIFFund = false;
   bool bIsSEGFund = false;
   bool bIsCASHFund = false;

   getField (ifds::FundTo, dstrFund, idDataGroup, false);
   getField (ifds::ClassTo, dstrClass, idDataGroup, false);

   isDIFFund (dstrFund, bIsDIFFund, idDataGroup);
   isSEGFund (dstrFund, bIsSEGFund, idDataGroup);
   bIsCASHFund = dstrFund.strip ().upperCase () == I_("CASH") ? true : false;

   if (bIsDIFFund || bIsSEGFund || bIsCASHFund)
   {
      FundDetailList *pFundDetailList = NULL;
      DString dstrLoadType = NULL_STRING;

      if (getWorkSession ().getMgmtCo().getFundDetailList (pFundDetailList) <= WARNING &&
         pFundDetailList && !dstrFund.empty() &&!dstrClass.empty())
      {
         pFundDetailList->getField (dstrFund, dstrClass, ifds::LoadType, dstrLoadType, idDataGroup, false);
         dstrLoadType.strip().upperCase();
      }

      bool bFrontEndSEGFund = dstrLoadType == FRONTENDLOAD && bIsSEGFund ? true : false;

      if (!bInit)
      {
         setFieldNoValidate (ifds::PayType, NULL_STRING, idDataGroup, true); 
         setFieldNoValidate (ifds::CommReduction, NULL_STRING, idDataGroup, true); 
         setFieldNoValidate (ifds::IntInvestType, NULL_STRING, idDataGroup, true); 

         if (!bFrontEndSEGFund)
         {
            setFieldNoValidate (ifds::FELAmt, NULL_STRING, idDataGroup, true); 
         }

         setFieldNoValidate (ifds::IntInvestTerm, NULL_STRING, idDataGroup, true); 
         setFieldNoValidate (ifds::IntCalcMthd, NULL_STRING, idDataGroup, true); 
         setFieldNoValidate (ifds::ForcedRate, I_(""), idDataGroup, true); 
         setFieldNoValidate (ifds::ForcedRateAmt, NULL_STRING, idDataGroup, true); 
         setFieldNoValidate (ifds::IntCredFreq, NULL_STRING, idDataGroup, true); 
         setFieldNoValidate (ifds::BusinessType, NULL_STRING, idDataGroup, true); 
         setFieldNoValidate (ifds::RefNum, NULL_STRING, idDataGroup, true); 
         setFieldNoValidate (ifds::AddlAmt, NULL_STRING, idDataGroup, true); 
      }


      setFieldReadOnly (ifds::PayType, idDataGroup, !bIsCASHFund);
      setFieldReadOnly (ifds::CommReduction, idDataGroup, true);
      setFieldReadOnly (ifds::IntInvestType, idDataGroup, true);
      setFieldReadOnly (ifds::FELAmt, idDataGroup, !bFrontEndSEGFund);
      setFieldReadOnly (ifds::IntInvestTerm, idDataGroup, true);
      setFieldReadOnly (ifds::IntCalcMthd, idDataGroup, true);
      setFieldReadOnly (ifds::ForcedRate, idDataGroup, true);
      setFieldReadOnly (ifds::ForcedRateAmt, idDataGroup, true);
      setFieldReadOnly (ifds::IntCredFreq, idDataGroup, true);
      //setFieldReadOnly (ifds::BusinessType, idDataGroup, true);
      //setFieldReadOnly (ifds::RefNum, idDataGroup, true);
      setFieldReadOnly (ifds::AddlAmt, idDataGroup, true);

      setBusinessTypeFieldsReadOnly (idDataGroup);

      // set required fields:
      setFieldRequired (ifds::IntInvestType, idDataGroup, false);
      setFieldRequired (ifds::IntInvestTerm, idDataGroup, false);
      setFieldRequired (ifds::IntCredFreq, idDataGroup, false);
      setFieldRequired (ifds::IntCalcMthd, idDataGroup, false);	
      setFieldRequired (ifds::AccountTo, idDataGroup, false);	
      setFieldRequired (ifds::ClassTo, idDataGroup, false);	

      setFieldValid (ifds::IntInvestType, idDataGroup, true);
      setFieldValid (ifds::IntInvestTerm, idDataGroup, true);
      setFieldValid (ifds::IntCredFreq, idDataGroup, true);
      setFieldValid (ifds::IntCalcMthd, idDataGroup, true);
      setFieldValid (ifds::AccountTo, idDataGroup, true);	
      setFieldValid (ifds::ClassTo, idDataGroup, true);	
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//****************************************************************************** 
SEVERITY MatSweepInstrDetails::setGIAFieldsReadOnly (const BFDataGroupId &idDataGroup, bool bInit)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("setGIAFieldsReadOnly"));

   DString dstrFund;
   DString dstrClass;
   bool bIsGIAFund = false;

   getField (ifds::FundTo, dstrFund, idDataGroup, false);
   getField (ifds::ClassTo, dstrClass, idDataGroup, false);

   isGIAFund (dstrFund, bIsGIAFund, idDataGroup);

   if (bIsGIAFund)
   {

      setFieldNoValidate (ifds::FELAmt, NULL_STRING, idDataGroup, true); 
      setFieldReadOnly (ifds::FELAmt, idDataGroup, true);				

      //setFieldAllSubstituteValues (ifds::PayType, idDataGroup, ifds::MaturityInstructionsPayType);

      setFieldNoValidate (ifds::FELAmt, NULL_STRING, idDataGroup, true); 
      setFieldReadOnly (ifds::FELAmt, idDataGroup, true);				

      DString dstrLevel;
      bool bForcedRateAmtReadOnly = true;
      bool bForcedRateReadOnly = true;

      getParent ()->getParent ()->getField (ifds::MatInstrLevel, dstrLevel, idDataGroup, false);

      if (dstrLevel == INVESTMENT)
      {
         DString dstrForcedRate;

         getField (ifds::ForcedRate, dstrForcedRate, idDataGroup, false);

         bForcedRateReadOnly = false;
         bForcedRateAmtReadOnly = dstrForcedRate == FORCED_RATE ? false : true;

         if (bForcedRateAmtReadOnly)
         {
            setFieldNoValidate (ifds::ForcedRateAmt, I_("0"), idDataGroup, true); 
         }
      }
      else 
      {
         if (bInit)
         {
            setFieldNoValidate (ifds::ForcedRate, DERIVED_FROM_CONF, idDataGroup, true); 
         }
      }

      setFieldReadOnly (ifds::ForcedRateAmt, idDataGroup, bForcedRateAmtReadOnly); 
      setFieldReadOnly (ifds::ForcedRate, idDataGroup, bForcedRateReadOnly);	

      DString	dstrRolloverType;
      bool bReadOnly = false;
      bool bAddAmtReadOnly = false;

      getField (ifds::RolloverType, dstrRolloverType, idDataGroup, false);

      if (dstrRolloverType == REINVEST)
      {

         bReadOnly = true;
      }
      else if (dstrRolloverType == REDIRECT)
      {
         DString	dstrInstrType;

         getParent ()->getParent ()->getField (ifds::MatSwpInstructionType, dstrInstrType, idDataGroup, false);

         if (dstrInstrType == CASH_SWEEP)
         {
            bAddAmtReadOnly = true;
         }

         bReadOnly = false;
      }

      setFieldReadOnly (ifds::AddlAmt, idDataGroup, bAddAmtReadOnly); 
      setCommReductionEditable(idDataGroup);		
      setFieldReadOnly (ifds::IntInvestType, idDataGroup, bReadOnly);	
      setFieldReadOnly (ifds::IntInvestTerm, idDataGroup, bReadOnly);		
      setFieldReadOnly (ifds::IntCalcMthd, idDataGroup, bReadOnly);	
      setFieldReadOnly (ifds::IntCredFreq, idDataGroup, bReadOnly);			

      bool bRequired = dstrRolloverType == REDIRECT || dstrLevel == INVESTMENT ? true : false;

      setFieldRequired (ifds::IntInvestType, idDataGroup, bRequired);
      setFieldRequired (ifds::IntInvestTerm, idDataGroup, bRequired);
      setFieldRequired (ifds::IntCredFreq, idDataGroup, bRequired);
      setFieldRequired (ifds::IntCalcMthd, idDataGroup, bRequired);	

      setFieldValid (ifds::IntInvestType, idDataGroup, !bRequired);
      setFieldValid (ifds::IntInvestTerm, idDataGroup, !bRequired);
      setFieldValid (ifds::IntCredFreq, idDataGroup, !bRequired);
      setFieldValid (ifds::IntCalcMthd, idDataGroup, !bRequired);
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//*******************************************************************************
SEVERITY MatSweepInstrDetails::redirectRelatedChanges (const DString &dstrRolloverType, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "redirectRelatedChanges" ) );

   DString dstrAccountNum;
   DString	dstrFund, dstrFundNumber;
   DString dstrClass;
   DString dstrInstructionType;
   DString dstrEffectiveDate;

   getParent ()->getParent ()->getField (ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false);
   getParent ()->getParent ()->getField (ifds::MatSwpInstructionType, dstrInstructionType, idDataGroup, false);

   if (dstrRolloverType == REDIRECT && !(dstrInstructionType == CASH_SWEEP))
   {
      getParent ()->getParent ()->getField (ifds::AccountNum, dstrAccountNum, idDataGroup, false);
      getParent ()->getParent ()->getField (ifds::Fund, dstrFund, idDataGroup, false);
      getParent ()->getParent ()->getField (ifds::Class, dstrClass, idDataGroup, false);
      getField (ifds::FromFundNumber, dstrFundNumber, idDataGroup, false);

      GIAInvAttribList *pGIAInvAttribList = NULL;

      getGIFundDefaults (pGIAInvAttribList, dstrFund, dstrClass, dstrEffectiveDate, idDataGroup);

      setFieldNoValidate (ifds::AccountTo, dstrAccountNum, idDataGroup, true); 
      setFieldNoValidate (ifds::FundTo, dstrFund, idDataGroup, true); 
      setFieldNoValidate (ifds::ClassTo, dstrClass, idDataGroup, true); 
      setFieldNoValidate (ifds::FromFundNumber, dstrFundNumber, idDataGroup, true); 
      setFieldNoValidate (ifds::Currency, NULL_STRING, idDataGroup, true); 

      setFieldNoValidate (ifds::IntInvestType, NULL_STRING, idDataGroup, false, true, true, false); 
      setFieldNoValidate (ifds::IntInvestTerm, NULL_STRING, idDataGroup, false, true, true, false); 
      setFieldNoValidate (ifds::IntCalcMthd, NULL_STRING, idDataGroup, false, true, true, false); 
      setFieldNoValidate (ifds::ForcedRateAmt, NULL_STRING, idDataGroup, false, true, true, false);  
      setFieldNoValidate (ifds::IntCredFreq, NULL_STRING, idDataGroup, false, true, true, false); 
      setFieldNoValidate (ifds::CommReduction, NULL_STRING, idDataGroup, false, true, true, false); 
      setFieldNoValidate (ifds::AddlAmt, NULL_STRING, idDataGroup, false, true, true, false); 

      setFieldNoValidate (ifds::PayType, NULL_STRING, idDataGroup, false, true, true, false); 
      setFieldNoValidate (ifds::ForcedRate, DERIVED_FROM_CONF, idDataGroup, false, true, true, false); 
      setFieldNoValidate (ifds::BusinessType, NULL_STRING, idDataGroup, false, true, true, false); 
      setFieldNoValidate (ifds::RefNum, NULL_STRING, idDataGroup, false, true, true, false); 

      currencyRelatedChanges (idDataGroup);

      //setGIFundFields (idDataGroup);
   }

   setRollOverFieldsReadOnly (idDataGroup);

   return(GETCURRENTHIGHESTSEVERITY());
}

//*******************************************************************************
SEVERITY MatSweepInstrDetails::reinvestRelatedChanges (const DString &dstrRolloverType, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "reinvestRelatedChanges" ) );

   DString dstrAccountNum;
   DString dstrFund, dstrFundNumber;
   DString dstrClass;
   DString dstrEffectiveDate;

   getParent ()->getParent ()->getField (ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false);

   if (dstrRolloverType == REINVEST)
   {
      getParent ()->getParent ()->getField (ifds::AccountNum, dstrAccountNum, idDataGroup, false);
      getParent ()->getParent ()->getField (ifds::Fund, dstrFund, idDataGroup, false);
      getParent ()->getParent ()->getField (ifds::Class, dstrClass, idDataGroup, false);
      getWorkSession().GetFundNumber(dstrFund, dstrClass, dstrFundNumber);

      GIAInvAttribList *pGIAInvAttribList = NULL;

      getGIFundDefaults (pGIAInvAttribList, dstrFund, dstrClass, dstrEffectiveDate, idDataGroup);

      setFieldNoValidate (ifds::AccountTo, dstrAccountNum, idDataGroup, true); 
      setFieldNoValidate (ifds::FundTo, dstrFund, idDataGroup, true); 
      setFieldNoValidate (ifds::ClassTo, dstrClass, idDataGroup, true); 
      setFieldNoValidate (ifds::FromFundNumber, dstrFundNumber, idDataGroup, true); 

      setFieldNoValidate (ifds::PayType, NULL_STRING, idDataGroup, false, true, true, false); 
      setFieldNoValidate (ifds::Currency, NULL_STRING, idDataGroup, true); 
      setFieldNoValidate (ifds::ForcedRate, DERIVED_FROM_CONF, idDataGroup, false, true, true, false); 
      setFieldNoValidate (ifds::BusinessType, NULL_STRING, idDataGroup, false, true, true, false); 
      setFieldNoValidate (ifds::RefNum, NULL_STRING, idDataGroup, false, true, true, false); 

      setFieldNoValidate (ifds::IntInvestType, NULL_STRING, idDataGroup, false, true, true, false); 
      setFieldNoValidate (ifds::IntCalcMthd, NULL_STRING, idDataGroup, false, true, true, false);  
      setFieldNoValidate (ifds::IntInvestTerm, NULL_STRING, idDataGroup, false, true, true, false); 
      setFieldNoValidate (ifds::IntCredFreq, NULL_STRING, idDataGroup, false, true, true, false); 
      setFieldNoValidate (ifds::CommReduction, NULL_STRING, idDataGroup, false, true, true, false); 
      setFieldNoValidate (ifds::AddlAmt, NULL_STRING, idDataGroup, false, true, true, false); 

      setGIFundFields (idDataGroup);

      currencyRelatedChanges (idDataGroup);
   }

   setRollOverFieldsReadOnly (idDataGroup);

   return(GETCURRENTHIGHESTSEVERITY());
}

//*******************************************************************************
SEVERITY MatSweepInstrDetails::cashRelatedChanges (const DString &dstrRolloverType, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "redirectRelatedChanges" ) );

   if (dstrRolloverType == CASH)
   {
      MFAccount *pMFAccount = NULL;
      DString dstrAccountNum;

      getParent ()->getParent ()->getField (ifds::AccountNum, dstrAccountNum, idDataGroup, false);

      setFieldNoValidate (ifds::AccountTo, NULL_STRING, idDataGroup, true); 
      setFieldNoValidate (ifds::FundTo, I_("CASH"), idDataGroup, true); 
      setFieldNoValidate (ifds::ClassTo, NULL_STRING, idDataGroup, true); 
      setFieldNoValidate (ifds::FromFundNumber, NULL_STRING, idDataGroup, true); 

	  setFieldValid (ifds::PayType, idDataGroup, false);
      currencyRelatedChanges (idDataGroup);

      setRollOverFieldsReadOnly (idDataGroup);

      if (getWorkSession ().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING &&
         pMFAccount)
      {
         DString dstrNonRegNonResident;

         pMFAccount->isNonRegNonResident(dstrNonRegNonResident, idDataGroup);

         if (dstrNonRegNonResident == YES)
         {
            setFieldAllSubstituteValues (ifds::PayType, idDataGroup, ifds::MaturityInstructionsPayType);
            setFieldNoValidate (ifds::PayType, SUPPRESS, idDataGroup, false, true, true, false); 
            setFieldReadOnly (ifds::PayType, idDataGroup, true); 

            payTypeRelatedChanges (SUPPRESS, idDataGroup);
         }
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//*******************************************************************************
SEVERITY MatSweepInstrDetails::payTypeRelatedChanges (const DString &dstrPayType, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "payTypeRelatedChanges" ) );
/*
   bool bRequired = dstrPayType == SUPPRESS ? true : false;

   setFieldRequired (ifds::BusinessType, idDataGroup, bRequired);
   setFieldRequired (ifds::RefNum, idDataGroup, bRequired);

    setFieldValid (ifds::BusinessType, idDataGroup, !bRequired);
    setFieldValid (ifds::RefNum, idDataGroup, !bRequired);
*/
   bankAddressRelatedChanges (dstrPayType, idDataGroup);
   currencyRelatedChanges (idDataGroup);
   setBusinessTypeFieldsReadOnly (idDataGroup);

   return(GETCURRENTHIGHESTSEVERITY());
}

//*******************************************************************************
SEVERITY MatSweepInstrDetails::bankAddressRelatedChanges (const DString &dstrPayType, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "bankAddressRelatedChanges" ) );

   bool bBankRequired = dstrPayType == EFT ? true : false;
   bool bAddressRequired = dstrPayType == CHEQUE ? true : false;
   DString dstrAddrCode = bAddressRequired ? I_("01") : NULL_STRING;

   if (!bBankRequired)
   {
      setFieldNoValidate(ifds::BankAcctId,		   NULL_STRING, idDataGroup, true); 
      setFieldNoValidate(ifds::BankIdType,		   NULL_STRING, idDataGroup, true); 
      setFieldNoValidate(ifds::BankIdValue,		   NULL_STRING, idDataGroup, true); 
      setFieldNoValidate(ifds::BankTransitNo,		NULL_STRING, idDataGroup, true); 
      setFieldNoValidate(ifds::BankSwiftCode,		NULL_STRING, idDataGroup, true); 
      setFieldNoValidate(ifds::BankRefNumber,		NULL_STRING, idDataGroup, true); 
      setFieldNoValidate(ifds::InstName,		      NULL_STRING, idDataGroup, true); 
      setFieldNoValidate(ifds::BankAddr1,		      NULL_STRING, idDataGroup, true); 
      setFieldNoValidate(ifds::BankAddr2,		      NULL_STRING, idDataGroup, true); 
      setFieldNoValidate(ifds::BankAddr3,		      NULL_STRING, idDataGroup, true); 
      setFieldNoValidate(ifds::BankAddr4,		      NULL_STRING, idDataGroup, true); 
      setFieldNoValidate(ifds::BankAddr5,		      NULL_STRING, idDataGroup, true); 
      setFieldNoValidate(ifds::BankPostal,		   NULL_STRING, idDataGroup, true); 
      setFieldNoValidate(ifds::BankCountry,		   NULL_STRING, idDataGroup, true); 
      setFieldNoValidate(ifds::BankAcctType,		   NULL_STRING, idDataGroup, true); 
      setFieldNoValidate(ifds::BankAcctTypeDesc,	NULL_STRING, idDataGroup, true); 
      setFieldNoValidate(ifds::BankAcctCurrency,	NULL_STRING, idDataGroup, true); 
      setFieldNoValidate(ifds::BankEffectiveDate,	NULL_STRING, idDataGroup, true); 
      setFieldNoValidate(ifds::BankStopDate,		   NULL_STRING, idDataGroup, true); 
      setFieldNoValidate(ifds::ACHProcessor,		   NULL_STRING, idDataGroup, true); 
      setFieldNoValidate(ifds::BankContact,		   NULL_STRING, idDataGroup, true); 
      setFieldNoValidate(ifds::BankId,		         NULL_STRING, idDataGroup, true); 
      setFieldNoValidate(ifds::BankAcctNum,		   NULL_STRING, idDataGroup, true); 
      setFieldNoValidate(ifds::BankAcctName,		   NULL_STRING, idDataGroup, true); 
      setFieldNoValidate(ifds::BankAcctUse,        NULL_STRING, idDataGroup, true); 
      setFieldNoValidate(ifds::PayMethod,          NULL_STRING, idDataGroup, true); 
      setFieldNoValidate(ifds::BankCorrespondent,  NULL_STRING, idDataGroup, true); 
   }
   else
   {
	   fileProcessorRelateChanges(idDataGroup);
   }

   setFieldNoValidate (ifds::MatInstrAddrCode, dstrAddrCode, idDataGroup, false, false, true);  

   return(GETCURRENTHIGHESTSEVERITY());
}

//*******************************************************************************
SEVERITY MatSweepInstrDetails::fileProcessorRelateChanges (const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "fileProcessorRelateChanges" ) );
	DString dstrPayType, dstrAchControl;

	getField(ifds::PayType, dstrPayType, idDataGroup, false);
	getWorkSession().getOption(ifds::ACHRedemption, dstrAchControl, idDataGroup, false);

	if(dstrPayType == EFT && dstrAchControl == YES)
	{
		DynamicSubListHolder* pDynamicSubListHolder = getMgmtCo().getDynamicSubListHolder();     
		   
		DString dstrPayMethod, dstrCurrency, dstrSubsList;
		   
		if(DSTCommonFunctions::getMarket() == MARKET_IDS::CANADA)
			dstrPayMethod = I_("EFT");

		getField (ifds::Currency, dstrCurrency, idDataGroup, false);
		dstrCurrency.strip();

		dstrSubsList = pDynamicSubListHolder->getFileProcSubList(TRADETYPE::REDEMPTION, dstrPayMethod, dstrCurrency);
		setFieldAllSubstituteValues (ifds::ACHProcessor, idDataGroup, dstrSubsList);
	}
	return(GETCURRENTHIGHESTSEVERITY());	   
}

//*******************************************************************************
SEVERITY MatSweepInstrDetails::remainingFlagRelatedChanges (const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "remainingFlagRelatedChanges" ) );

   bool	bReadOnly = false;
   DString	dstrRemainingFlag;

   getField (ifds::RemainingFleg, dstrRemainingFlag, idDataGroup, false);

   if (dstrRemainingFlag == YES1)
   {
      setFieldNoValidate (ifds::Percentage,	I_("0"), idDataGroup, true); 
      bReadOnly = true;
   }

   setFieldReadOnly (ifds::Percentage,	idDataGroup, bReadOnly); 

   return(GETCURRENTHIGHESTSEVERITY());
}

//*******************************************************************************
SEVERITY MatSweepInstrDetails::currencyRelatedChanges (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "currencyRelatedChanges" ) );

   bool bReadOnly = true; 
   DString dstrRolloverType;

   getField (ifds::RolloverType, dstrRolloverType, idDataGroup, false);

   if (dstrRolloverType == REINVEST|| dstrRolloverType == REDIRECT)
   {
      bReadOnly = true;

      setFieldNoValidate (ifds::Currency,	NULL_STRING, idDataGroup, true); 
   }
   else if (dstrRolloverType == CASH)
   {
      DString dstrPayType;

      getField (ifds::PayType, dstrPayType, idDataGroup, false);

      if (dstrPayType == SUPPRESS)
      {
         bReadOnly = true;

         setFieldNoValidate (ifds::Currency,	NULL_STRING, idDataGroup, true); 
      }
      else if (dstrPayType == CHEQUE || dstrPayType == EFT)
      {
         DString dstrFund;
         DString dstrClass;
         DString dstrCurrency;

         getParent ()->getParent ()->getField (ifds::Fund, dstrFund, idDataGroup, false);
         getParent ()->getParent ()->getField (ifds::Class, dstrClass, idDataGroup, false);

         getFundCurrency (dstrFund, dstrClass, dstrCurrency, idDataGroup);

         setFieldNoValidate (ifds::Currency,	dstrCurrency, idDataGroup, true); 

         bReadOnly = m_multiCurrency == YES ? false : true; 
      }
   }

   setFieldReadOnly (ifds::Currency, idDataGroup, bReadOnly);

   return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************
SEVERITY MatSweepInstrDetails::validateAssociatedNum (const DString &dstrAcctountNum, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateAssociatedNum" ) );

   AccShrNumCheck *pAccShrNumCheck = NULL;
   DString			strKey (I_("AccShrNumCheck=") + dstrAcctountNum);
   DString			dstrRolloverType;

   getField (ifds::RolloverType, dstrRolloverType, idDataGroup, false);

   if (dstrRolloverType == CASH)
      return GETCURRENTHIGHESTSEVERITY();

   pAccShrNumCheck = dynamic_cast <AccShrNumCheck*> (getObject ( strKey, idDataGroup));

   if (!pAccShrNumCheck && dstrAcctountNum != NULL_STRING) //make view call
   {
      pAccShrNumCheck = new AccShrNumCheck (*this);

      if (pAccShrNumCheck->initAccNum (dstrAcctountNum) <= WARNING)
      {
         setObject ( pAccShrNumCheck, strKey, OBJ_ACTIVITY_NONE, idDataGroup);
      }
      else 
      {
         delete pAccShrNumCheck;
         pAccShrNumCheck = NULL;
      }

      DString dataFound;

      if(pAccShrNumCheck)
      pAccShrNumCheck->getField (ifds::DataFound, dataFound, BF::HOST, false);

      if (dataFound.strip() != Y)
      {
         ADDCONDITIONFROMFILE (CND::ERR_INVALID_ACCOUNT_NUMBER);
      }
   }
   else
      ADDCONDITIONFROMFILE (CND::ERR_INVALID_ACCOUNT_NUMBER);

   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************************
SEVERITY MatSweepInstrDetails::validateRolloverType (const DString &dstrRollOverType, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateRolloverType" ) );

   DString dstrInstructionType;

   getParent ()->getParent ()->getField (ifds::MatSwpInstructionType, dstrInstructionType, idDataGroup, false);

   if (dstrInstructionType == CASH_SWEEP && dstrRollOverType != REDIRECT)
   {
      ADDCONDITIONFROMFILE (CND::ERR_INVALID_ROLLOVER_TYPE);
   }
   else if (DSTCommonFunctions::codeInList (dstrInstructionType, MATURITY_INTEREST) && dstrRollOverType == CASH)
   {
      validateRolloverForInstrType (idDataGroup);

      // check interest instruction...
      if (dstrInstructionType == INTEREST && dstrRollOverType != CASH)
      {
         MatSweepInstrDetailsList *pMatSweepInstrDetailsList = dynamic_cast<MatSweepInstrDetailsList*>( getParent( ) );      

         if (pMatSweepInstrDetailsList)
         {
            pMatSweepInstrDetailsList->validateInterestInstruction (idDataGroup);
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************************
SEVERITY MatSweepInstrDetails::validateRolloverForInstrType(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateRolloverForInstrType"));

   DString	dstrInstrType;		
   getParent ()->getParent ()->getField (ifds::MatSwpInstructionType, dstrInstrType, idDataGroup, false);

   if(dstrInstrType == INTEREST)
   {
      MFAccount *pMFAccount = NULL;
      DString dstrAccountNum, dstrFundCode;

      getParent()->getParent()->getField (ifds::AccountNum, dstrAccountNum, idDataGroup, false);

      bool bIsGIAFund = false, bIsDIFFund=false;
      getParent()->getParent()->getField (ifds::Fund, dstrFundCode, idDataGroup, false);

      if (!dstrFundCode.empty())
      {
         isGIAFund (dstrFundCode, bIsGIAFund, idDataGroup);
         isDIFFund (dstrFundCode, bIsDIFFund, idDataGroup);
      }

      if (getWorkSession ().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING &&
         pMFAccount && (bIsGIAFund || bIsDIFFund))
      {
         DString dstrTaxType, dstrAcctDesignation;

         pMFAccount->getField (ifds::TaxType, dstrTaxType, idDataGroup, false);
         pMFAccount->getField (ifds::AcctDesignation,  dstrAcctDesignation, idDataGroup);   

         if (!getWorkSession().isNonRegLike(dstrTaxType.stripAll()) && dstrAcctDesignation == ACCT_DESIGNATION::CLIENT)
         {
            getErrMsg (IFASTERR::CASH_INSTR_NOT_ALLOWED_FOR_REG_ACC, 
                       CND::ERR_CASH_INSTR_NOT_ALLOWED_FOR_REG_ACC, 
                       CND::WARN_CASH_INSTR_NOT_ALLOWED_FOR_REG_ACC, 
                       idDataGroup);
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************************
SEVERITY MatSweepInstrDetails::cashSweepDefaults (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "cashSweepDefaults" ) );

   DString dstrInstructionType;

   getParent ()->getParent ()->getField (ifds::MatSwpInstructionType, dstrInstructionType, idDataGroup, false);

   if (dstrInstructionType == CASH_SWEEP)
   {
      DString dstrAccount;

      getParent ()->getParent ()->getField (ifds::AccountNum, dstrAccount, idDataGroup, false);

      setFieldNoValidate(ifds::RolloverType, REDIRECT, idDataGroup, true);
      setFieldNoValidate(ifds::AccountTo, dstrAccount, idDataGroup, true); 

      setFieldReadOnly (ifds::RolloverType, idDataGroup, true);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
SEVERITY MatSweepInstrDetails::getFundCurrency (const DString &dstrFundCode, 
                                                const DString &dstrClassCode, 
                                                DString &dstrCurrency,
                                                const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getFundCurrency"));

   FundDetail *pFundDetail = NULL;

   if (getWorkSession().getFundDetail (dstrFundCode, dstrClassCode, idDataGroup, pFundDetail) &&
      pFundDetail)
   {
      pFundDetail->getField (ifds::Currency, dstrCurrency, idDataGroup, false);
      dstrCurrency.strip ().upperCase ();
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//*****************************************************************************
SEVERITY MatSweepInstrDetails::getFundClassMinAmount (const DString &dstrFundCode, 
                                                      const DString &dstrClassCode, 
                                                      DString &dstrMinCashSweepAmount,
                                                      DString &dstrEWI,
                                                      const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getFundClassMinAmount"));

   FundLmtOverrideList	*pFundToLmtOverrideList = NULL;
   FundLmtOverride		*pFundLmtOverride = NULL;
   DString dstrAccountNum;

   getParent ()->getParent ()->getField (ifds::AccountNum, dstrAccountNum, idDataGroup, false);

   if (getFundLmtOverrideList (pFundToLmtOverrideList, dstrFundCode, dstrClassCode, idDataGroup) <= WARNING &&
      pFundToLmtOverrideList)
   {
      if (pFundToLmtOverrideList->getFundLmtOverride (getWorkSession(), dstrAccountNum, SEG_CASH_SWP_RULE, pFundLmtOverride, idDataGroup) 
         <= WARNING && pFundLmtOverride)
      {
         pFundLmtOverride->getField (ifds::MinInitAmt, dstrMinCashSweepAmount, idDataGroup, false);
         pFundLmtOverride->getField (ifds::MinInitAmtSeverityCode, dstrEWI, idDataGroup, false);
         dstrEWI.strip().upperCase();
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//*****************************************************************************
SEVERITY MatSweepInstrDetails::setFundClassMinAmount (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("setFundClassMinAmount"));

   DString dstrFund;
   DString dstrClass;
   DString dstrMinAmount = I_("0");
   DString dstrEWI;

   getField (ifds::FundTo, dstrFund, idDataGroup, false);
   getField (ifds::ClassTo, dstrClass, idDataGroup, false);

   if (!dstrFund.empty () && !dstrClass.empty ())
   {
      DString  dstrInstrType;

      getParent ()->getParent ()->getField (ifds::MatSwpInstructionType, dstrInstrType, idDataGroup, false);

      // only applicable for cash sweep
      if (dstrInstrType == CASH_SWEEP)
      {
         getFundClassMinAmount (dstrFund, dstrClass, dstrMinAmount, dstrEWI, idDataGroup);
      }

      setFieldNoValidate (ifds::Amount, dstrMinAmount, idDataGroup, true); 
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY MatSweepInstrDetails::intAdditionalAmtRelatedChanges(const BFDataGroupId &idDataGroup, bool bInit)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("intAdditionalAmtRelatedChanges"));

   DString dstrFrocedRate;
   DString dstrLevel;
   bool	bAddlAmt = true;

   getParent ()->getParent ()->getField (ifds::MatInstrLevel, dstrLevel, idDataGroup, false);
   getField (ifds::ForcedRate, dstrFrocedRate, idDataGroup, false);

   if (dstrFrocedRate != FORCED_RATE && dstrLevel == INVESTMENT )
   {
      bAddlAmt = false;

      if (!bInit)
      {
         setFieldNoValidate (ifds::AddlAmt, I_("0"), idDataGroup, true); 
      }
   }

   setFieldReadOnly (ifds::AddlAmt, idDataGroup, bAddlAmt);

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY MatSweepInstrDetails::intCalcMthdRelatedChanges(const BFDataGroupId &idDataGroup, bool bInit)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("intCalcMthdRelatedChanges"));

   DString dstrIntCalcMthd;

   getField(ifds::IntCalcMthd, dstrIntCalcMthd, idDataGroup, false);

   GIAInvAttribList* pGIAInvAttribList = NULL;

   DString dstrEffectiveDate;
   DString dstrFundTo;
   DString dstrClassTo;

   getParent ()->getParent ()->getField (ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false);
   getField (ifds::FundTo, dstrFundTo, idDataGroup, false);
   getField (ifds::ClassTo, dstrClassTo, idDataGroup, false);


   if (getGIFundDefaults (pGIAInvAttribList, dstrFundTo, dstrClassTo, dstrEffectiveDate, idDataGroup, false) <= WARNING &&
      pGIAInvAttribList)
   {
      if(dstrIntCalcMthd == I_("S"))
      {
         DString dstrSimpleTermList,
            dstrSimpleCredFreqList;

         pGIAInvAttribList->getField(ifds::SimpleTermList, dstrSimpleTermList, idDataGroup, false );
         pGIAInvAttribList->getField(ifds::SimpleCredFreqList, dstrSimpleCredFreqList, idDataGroup, false );
         dstrSimpleTermList.strip();
         dstrSimpleCredFreqList.strip();

         if(!dstrSimpleTermList.empty())
         {
            DString::size_type pos = 0;
            DString dstrItem_, investTermListSubSt;

            do
            {
               EXTRACT_VALUE(dstrSimpleTermList, dstrItem_);
               investTermListSubSt  += dstrItem_ + I_("=") + dstrItem_ + I_(";");

               CHOP_STRING (dstrSimpleTermList);
            }
            while (dstrSimpleTermList != NULL_STRING);

            BFProperties *pBFPropertiesInvestTerm = getFieldProperties (ifds::IntInvestTerm, idDataGroup);

            assert (pBFPropertiesInvestTerm);

            if (pBFPropertiesInvestTerm)
            {
               setFieldAllSubstituteValues (ifds::IntInvestTerm, idDataGroup, investTermListSubSt);            
               pBFPropertiesInvestTerm->setSubstituteValues(NULL);


               if (!bInit)
               {
                  setFieldNoValidate (ifds::IntInvestTerm, NULL_STRING, idDataGroup, false, false, true, false); 
               }
            }
         }

         loadSubstitutionList (ifds::IntCredFreq, idDataGroup, dstrSimpleCredFreqList);

         if (!bInit)
         {
            setFieldNoValidate (ifds::IntCredFreq, NULL_STRING, idDataGroup, false, false, true, false);
         }
      }
      else if (dstrIntCalcMthd == I_("C"))
      {
         DString dstrCompoundTermList,
            dstrCompoundCredFreqList;

         pGIAInvAttribList->getField(ifds::CompoundTermList, dstrCompoundTermList, idDataGroup, false );
         pGIAInvAttribList->getField(ifds::CompoundCredFreqList, dstrCompoundCredFreqList, idDataGroup, false );
         dstrCompoundTermList.strip();
         dstrCompoundCredFreqList.strip();

         if(!dstrCompoundTermList.empty())
         {
            DString::size_type pos = 0;
            DString dstrItem_,
               investTermListSubSt;

            do
            {
               EXTRACT_VALUE(dstrCompoundTermList, dstrItem_);
               investTermListSubSt  += dstrItem_ + I_("=") + dstrItem_ + I_(";");

               CHOP_STRING (dstrCompoundTermList);
            }
            while (dstrCompoundTermList != NULL_STRING);

            BFProperties *pBFPropertiesInvestTerm = getFieldProperties (ifds::IntInvestTerm, idDataGroup);

            assert (pBFPropertiesInvestTerm);

            if (pBFPropertiesInvestTerm)
            {
               setFieldAllSubstituteValues (ifds::IntInvestTerm, idDataGroup, investTermListSubSt);            
               pBFPropertiesInvestTerm->setSubstituteValues(NULL);

               if (!bInit)
               {
                  setFieldNoValidate ( ifds::IntInvestTerm, NULL_STRING, idDataGroup, false, false, true, false); //no related changes
               }
            }
         }

         loadSubstitutionList (ifds::IntCredFreq, idDataGroup, dstrCompoundCredFreqList);

         if (!bInit)
         {
            setFieldNoValidate (ifds::IntCredFreq, NULL_STRING, idDataGroup, false, false, true, false); //no related changes
         }
      }

      if (!dstrIntCalcMthd.empty())
      {
         /* 
         Whenever user does select the Cal method that means the instruction requires investment.
         Therefore, the IntCredFreq and IntInvestTerm are always required for GI fund.			   
         */
         setFieldValid (ifds::IntCredFreq, idDataGroup, false);
         setFieldRequired (ifds::IntCredFreq, idDataGroup, true);

         setFieldValid (ifds::IntInvestTerm, idDataGroup, false);
         setFieldRequired (ifds::IntInvestTerm, idDataGroup, true);
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY MatSweepInstrDetails::setAllFeildsReadOnly (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("setAllFeildsReadOnly"));

   DString dstrGoodBad;
   DString dstrMatInstrLevel;
   DString dstrProcType;
   bool    bReadOnly = false;

   getParent ()->getParent ()->getField (ifds::GoodBad, dstrGoodBad, idDataGroup, false);
   getParent ()->getParent ()->getField (ifds::MatInstrLevel, dstrMatInstrLevel, idDataGroup, false);
   getParent ()->getParent ()->getField (ifds::ProcType, dstrProcType, idDataGroup, false);

   if (dstrGoodBad == I_("N"))
   {
      bReadOnly = true;
   }
   else
   {
      if (dstrProcType != ACCTLEVEL && dstrMatInstrLevel == ACCOUNT)
      {
         bReadOnly = true;
      }
      else
      {
         DString dstrEffectiveDate, dstrCurrentBusinessDate, dstrInvHisStatus;

         getParent ()->getParent ()->getField (ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false);
         getWorkSession ().getOption (ifds::CurrBusDate,  dstrCurrentBusinessDate, idDataGroup, false);
         getField (ifds::InvHisStatus, dstrInvHisStatus, idDataGroup, false);
         dstrInvHisStatus.strip().upperCase();

         if (DSTCommonFunctions::CompareDates (dstrEffectiveDate, dstrCurrentBusinessDate) == DSTCommonFunctions::FIRST_EARLIER)
         {
            bReadOnly = true;
         }
         if (dstrInvHisStatus == I_("M"))
         {
            // will fall into this when doApplyRelatedChanges
            bReadOnly = true;
         }
      }
   }

   // disable fields if record is bad or account record if it is invoked 
   // on trade or investment history screens.
   // disable instruciton if effective date is before current business day for both account and investment instrucitons.
   if (!bReadOnly)
   {		
      return GETCURRENTHIGHESTSEVERITY ();
   }

   setFieldReadOnly (ifds::RolloverType, idDataGroup, true);
   setFieldReadOnly (ifds::AccountTo, idDataGroup, true);
   setFieldReadOnly (ifds::FundTo,	 idDataGroup, true);
   setFieldReadOnly (ifds::ClassTo, idDataGroup, true);
   setFieldReadOnly (ifds::FromFundNumber, idDataGroup, true);
   setFieldReadOnly (ifds::RemainingFleg, idDataGroup, true);
   setFieldReadOnly (ifds::Currency, idDataGroup, true);
   setFieldReadOnly (ifds::Percentage,	 idDataGroup, true);
   setFieldReadOnly (ifds::PayType, idDataGroup, true);
   setFieldReadOnly (ifds::CommReduction, idDataGroup, true);
   setFieldReadOnly (ifds::IntInvestType, idDataGroup, true);
   setFieldReadOnly (ifds::FELAmt, idDataGroup, true);
   setFieldReadOnly (ifds::IntInvestTerm, idDataGroup, true);
   setFieldReadOnly (ifds::IntCalcMthd, idDataGroup, true);
   setFieldReadOnly (ifds::ForcedRate,	 idDataGroup, true);
   setFieldReadOnly (ifds::ForcedRateAmt, idDataGroup, true);
   setFieldReadOnly (ifds::IntCredFreq, idDataGroup, true);
   setFieldReadOnly (ifds::BusinessType, idDataGroup, true);
   setFieldReadOnly (ifds::RefNum,	 idDataGroup, true);
   setFieldReadOnly (ifds::AddlAmt, idDataGroup, true);
   setFieldReadOnly (ifds::MatInstrAddrCode, idDataGroup, true);

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY MatSweepInstrDetails::initClone ( const MatSweepInstrDetails* pClone, 
                                           const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initClone" ) );

   for (int i = 0; i < NUM_FIELDS; i++)
   {
      BFCBO::CLASS_FIELD_INFO fieldInfo = classFieldInfo [i];     
      const BFFieldId &fieldId = fieldInfo.getFieldId();

      DString fieldValue;

      pClone->getField (fieldId, fieldValue, idDataGroup, false);
      if (fieldId == ifds::CommReduction)
      {
         setFieldNoValidate (fieldId, NULL_STRING, idDataGroup, false, true, false, false);
      }
      else if (fieldId == ifds::AddlAmt)
      {
         setFieldNoValidate (fieldId, NULL_STRING, idDataGroup, false, true, false, false);
      }
      else
      {
         setFieldNoValidate (fieldId, fieldValue, idDataGroup, false, true, false, false);
      }
   }

   // reset this field so that new is created:
   setFieldNoValidate (ifds::IntInvestUUID, I_(""), idDataGroup, false, true, false, false);
   setFieldNoValidate (ifds::DistribDetlVersion, I_(""), idDataGroup, false, true, false, false);

   DString	dstrRolloverType;

   getField (ifds::RolloverType, dstrRolloverType, idDataGroup, false);

   commInit (idDataGroup);

   if (dstrRolloverType == REINVEST) //|| dstrRolloverType == REDIRECT)
   {
      setGIFundFields (idDataGroup);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//****************************************************************************
SEVERITY MatSweepInstrDetails::getFundLmtOverrideList (FundLmtOverrideList *&pFundLmtOverrideList,
                                                       const DString& fundCode,
                                                       const DString& classCode,
                                                       const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getFundLmtOverrideList"));

   pFundLmtOverrideList = NULL;

   DString strKey = I_("FundLmtOverrideList");
   strKey += I_(";FundCode=") + fundCode + I_(";ClassCode=") + classCode;   

   pFundLmtOverrideList = dynamic_cast<FundLmtOverrideList *>(BFCBO::getObject(strKey, idDataGroup));

   if (!pFundLmtOverrideList )
   {
      pFundLmtOverrideList = new FundLmtOverrideList (*this);

      if (pFundLmtOverrideList->init (fundCode, classCode, PURCHASE) <= WARNING)
      {
         setObject (pFundLmtOverrideList, strKey, OBJ_ACTIVITY_NONE, idDataGroup); 
      }
      else
      {
         delete pFundLmtOverrideList;
         pFundLmtOverrideList = NULL;
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY MatSweepInstrDetails::getBankInstructionsList(
   MatSweepInstrBankList *&pMatSweepInstrBankList, 
   const BFDataGroupId& idDataGroup, bool bCreate /*= true*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getBankInstructionsList"));
   DString dstrPayType;
   getField( ifds::PayType, dstrPayType, idDataGroup);

   //check whether PayType is EFT, only in this case we have banking
   if (dstrPayType == EFT)
   {
      BFObjectKey objKey(I_("MatSweepInstrBankList"), idDataGroup, OBJ_ACTIVITY_NONE, OBJ_TYPE_NONE);

      pMatSweepInstrBankList = NULL;
      pMatSweepInstrBankList = dynamic_cast<MatSweepInstrBankList*>(findObject(objKey));
      if (!pMatSweepInstrBankList && bCreate)
      {
         pMatSweepInstrBankList = new MatSweepInstrBankList(*this);
         if (pMatSweepInstrBankList)
         {
            DString dstrAccountNum;

            getField(ifds::AccountNum, dstrAccountNum, idDataGroup, false);

            SEVERITY severity = isNew() ? 
               pMatSweepInstrBankList->initNew(dstrAccountNum, idDataGroup) : 
               pMatSweepInstrBankList->init(dstrAccountNum, idDataGroup);

            if (severity <= WARNING)
            {
               setObject(objKey, pMatSweepInstrBankList);
            }
            else
            {
               delete pMatSweepInstrBankList;
               pMatSweepInstrBankList = NULL;
            }
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************************************
SEVERITY MatSweepInstrDetails::validateAddressCode (const DString &dstrAddressCode,
                                                    const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateAddressCode"));

   DString dstrShrNum;
   DString dstrAccountNum;
   DString dstrEffectiveDate;
   DString dstrCurrentBusinessDate;
   DString dstrPayType;
   MFAccount *pMFAccount = NULL;

   getField (ifds::PayType, dstrPayType, idDataGroup, false);

   if (!(dstrPayType == CHEQUE))
      return GETCURRENTHIGHESTSEVERITY();

   getParent ()->getParent ()->getField (ifds::AccountNum, dstrAccountNum, idDataGroup, false);
   getParent ()->getParent ()->getField (ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false);

   getWorkSession ().getOption (ifds::CurrBusDate,  dstrCurrentBusinessDate, idDataGroup, false);

   if (getWorkSession ().getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING &&
      pMFAccount)
   {

      pMFAccount->getField (ifds::ShrNum, dstrShrNum, idDataGroup, false);

      if (!dstrShrNum.empty())
      {
         Shareholder *pShareholder = NULL;

         if (getWorkSession().getShareholder (idDataGroup, dstrShrNum, pShareholder) <= WARNING)
         {
            AddressList *pAddressList = NULL;

            if (pShareholder->getAddressList (pAddressList, idDataGroup) <= WARNING)
            {

               if (DSTCommonFunctions::CompareDates (dstrEffectiveDate, dstrCurrentBusinessDate) == DSTCommonFunctions::FIRST_EARLIER)
               {
                  dstrEffectiveDate = dstrCurrentBusinessDate;
               }

               pAddressList->validateAddressCode (dstrAddressCode, idDataGroup, dstrEffectiveDate);
            }
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************************************
SEVERITY MatSweepInstrDetails::validateMaturityBank (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateMaturityBank"));

   DString dstrPayType;

   getField (ifds::PayType, dstrPayType, idDataGroup, false);

   if (dstrPayType == EFT)
   {
      DString bankIdValue;

      getField (ifds::BankIdValue, bankIdValue, idDataGroup, false);

      if (bankIdValue.empty())
      {
         ADDCONDITIONFROMFILE (CND::ERR_MATURITYBANK_IS_MISSING);
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//*******************************************************************************************************
SEVERITY MatSweepInstrDetails::setGIFundFields (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("setGIFundFields"));

   DString dstrLevel;

   getParent ()->getParent ()->getField (ifds::MatInstrLevel, dstrLevel, idDataGroup, false);


   if (dstrLevel == INVESTMENT)
   {
      DString dstrIntInvestType, dstrIntCalcMthd, dstrInvestTerm, dstrIntCredFreq;

      getParent ()->getParent ()->getParent ()->getField (ifds::IntInvestType, dstrIntInvestType, idDataGroup, false);
      getParent ()->getParent ()->getParent ()->getField (ifds::IntCalcMthd, dstrIntCalcMthd, idDataGroup, false);
      getParent ()->getParent ()->getParent ()->getField (ifds::InvestTerm, dstrInvestTerm, idDataGroup, false);
      getParent ()->getParent ()->getParent ()->getField (ifds::IntCredFreq, dstrIntCredFreq, idDataGroup, false);

      setFieldNoValidate (ifds::IntInvestType, dstrIntInvestType, idDataGroup, false, true, true, false); 
      setFieldNoValidate (ifds::IntCalcMthd, dstrIntCalcMthd, idDataGroup, false, true, true, false);  

      intCalcMthdRelatedChanges(idDataGroup);

      setFieldNoValidate (ifds::IntInvestTerm, dstrInvestTerm, idDataGroup, false, true, true, false); 
      setFieldNoValidate (ifds::IntCredFreq, dstrIntCredFreq, idDataGroup, false, true, true, false); 

   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY MatSweepInstrDetails::loadBusinessTypeSubslist( const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION,CLASSNAME, I_("loadBusinessTypeSubslist"));
   //P0186486_FN15_The Source of Funds
   DString sourceOfFundApp;

   getWorkSession().getOption(ifds::SourceOfFundApp, sourceOfFundApp, idDataGroup, false);
   sourceOfFundApp.strip().upperCase();

   if(sourceOfFundApp == I_("Y")) 
   {
      DString SrcOfFunds_IA_GIC_List; 
      getWorkSession().getOption(ifds::SrcOfFunds_IA_GIC, SrcOfFunds_IA_GIC_List, idDataGroup, false);
      SrcOfFunds_IA_GIC_List.strip().upperCase();
      if(!SrcOfFunds_IA_GIC_List.empty())
      {
         replaceSubstitutionList(SrcOfFunds_IA_GIC_List,
            ifds::SrcOfFunds_IA, 
            ifds::BusinessType, idDataGroup);
      }
   }

   return GETCURRENTHIGHESTSEVERITY(); 
}

//*******************************************************************************************************
SEVERITY MatSweepInstrDetails::businessTypeRelatedChanges (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION,CLASSNAME, I_("businessTypeRelatedChanges"));
   //P0186486_FN15_The Source of Funds

   DString businessType;
   getField(ifds::BusinessType, businessType, idDataGroup, false); 
   businessType.stripAll().upperCase();

   if(!businessType.empty())
   {
      if(getWorkSession ().isSrcOfFundRequired(businessType, idDataGroup))
      {
		  setFieldReadOnly (ifds::RefNum, idDataGroup, false);
         setFieldRequired (ifds::RefNum, idDataGroup, true);
         setValidFlag ( ifds::RefNum, idDataGroup, false ); 
      }
      else
      {
         setFieldRequired (ifds::RefNum, idDataGroup, false);
         setValidFlag ( ifds::RefNum, idDataGroup, true ); 
		  setFieldReadOnly (ifds::RefNum, idDataGroup, true);
      }
   }
   else
   {
      setFieldRequired (ifds::BusinessType, idDataGroup, false);
      setFieldRequired (ifds::RefNum, idDataGroup, false);
      setValidFlag ( ifds::BusinessType, idDataGroup, true ); 
      setValidFlag ( ifds::RefNum, idDataGroup, true ); 
	   setFieldReadOnly (ifds::RefNum, idDataGroup, true);
   }

   return GETCURRENTHIGHESTSEVERITY(); 
}

//****************************************************
void MatSweepInstrDetails::ValidateRefNum(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateRefNum" ) );

   //P0186486_FN15_The Source of Funds
   DString businessType;
   getField(ifds::BusinessType, businessType, idDataGroup, false); 
   businessType.stripAll().upperCase();

   if(!businessType.empty())
   {
      if(getWorkSession ().isSrcOfFundRequired(businessType, idDataGroup))
      {
         DString refNum;
         getField(ifds::RefNum, refNum, idDataGroup, false); 
         if(refNum.empty())
         {
            getErrMsg (IFASTERR::REFERENCE_NO_IS_MANDATORY_FOR_SOURCE_OF_FUND, 
                       CND::ERR_REFERENCE_NO_IS_MANDATORY_FOR_SOURCE_OF_FUND, 
                       CND::WARN_REFERENCE_NO_IS_MANDATORY_FOR_SOURCE_OF_FUND, 
                       idDataGroup);
         }
      }
   }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/MatSweepInstrDetails.cpp-arc  $
// 
//    Rev 1.39   Aug 03 2012 20:20:04   wp040240
// IN3014673 - P0181067 Added Error condition to avoid cash instructions  to registered client accounts
// 
//    Rev 1.38   Jul 25 2012 15:57:18   wp040240
// IN3014673 - P0181067 Added Error condition to avoid cash instructions  to registered client accounts
// 
//    Rev 1.37   Jul 17 2012 17:25:32   kitticha
// IN#3019010 - Reinvest instructions should not be allowed to different fund/class from the source fund/class.
// 
//    Rev 1.36   Jul 17 2012 15:24:32   kitticha
// IN#2932057 - User should not be able to maintain the instruction when investment is matured.
// 
//    Rev 1.35   Jun 08 2012 14:09:42   jankovii
// IN 2957854 - P0186477_FN05_03_Same transno. in distrib-delt to be used & changes to misc-info
// 
//    Rev 1.34   May 31 2012 05:11:50   panatcha
// IN2959727 - P0186486FN15 Source of Funds
// 
//    Rev 1.33   May 24 2012 06:28:18   panatcha
// P0186486_FN15_The Source of Funds
// 
//    Rev 1.32   May 17 2012 14:57:00   jankovii
// IN 2949731 - MaturityInterest Screen Issue
// 
//    Rev 1.31   May 04 2012 11:50:04   panatcha
// P0186486_FN15_The Source of Funds
// 
//    Rev 1.30   May 01 2012 09:14:04   popescu
// Incident
// 
//    Rev 1.29   Apr 22 2012 20:36:12   jankovii
// IN 2847670 
// 
//    Rev 1.28   Apr 22 2012 18:50:20   jankovii
// IN 2847670 & 2815937
//
//    Rev 1.27   Apr 12 2012 12:01:00   wp040100
// IN 2886441 - BayCom number display implementation
//
//    Rev 1.26   Apr 05 2012 14:14:18   jankovii
// IN 2904085 - Automatin Instructions - For reinvestment, the destination fileds s/s pre-popula
// 
//    Rev 1.25   Apr 02 2012 12:05:46   wp040100
// IN 2889096 - Term of Deposit and Comm. Reduction fields sort fix.
// 
//    Rev 1.24   Mar 30 2012 11:30:02   jankovii
// IN 2898233 - R12.3-P0186477-Enable manual tax calculation of money out transactions for NR
// 
//    Rev 1.23   Mar 27 2012 14:55:20   jankovii
// IN 2895832 - P0186477_FN05_Maturity Processing CASH instruction for a registered tax type
// 
//    Rev 1.22   Mar 26 2012 14:42:48   jankovii
// IN 2891879 - GIA Automatic Instructions Display
// 
//    Rev 1.21   Mar 21 2012 13:23:04   jankovii
// IN 2889348 - Maturity Processing _ Desktop Issues_List 1_EFT issues
// 
//    Rev 1.20   Feb 28 2012 11:54:14   jankovii
// IN 2861935 - Maturity_Interest Screen issues
// 
//    Rev 1.19   Feb 16 2012 11:39:28   jankovii
// Commented out duplicate check.
// 
//    Rev 1.18   Feb 09 2012 13:11:48   jankovii
// IN 2835682 - P0186477FN03 -Database error when accessing Maturity/ Interest Screen
// 
//    Rev 1.17   Feb 06 2012 15:55:26   jankovii
// IN 2835682 - P0186477FN03 -Database error when accessing Maturity/ Interest Screen
// 
//    Rev 1.16   Feb 02 2012 15:05:40   if991250
// Maturity/Interest Instructions banking
// 
//    Rev 1.15   Feb 02 2012 10:49:52   jankovii
// IN 2826242- Maturity/Interest Instruction on Trading Screen
// 
//    Rev 1.14   Feb 01 2012 16:51:24   jankovii
// IN 2826242- Maturity/Interest Instruction on Trading Screen
// 
//    Rev 1.13   Feb 01 2012 15:04:52   if991250
// retrieve the bank list
// 
//    Rev 1.12   Jan 31 2012 19:16:40   jankovii
// IN 2826242- Maturity/Interest Instruction on Trading Screen
// 
//    Rev 1.11   Jan 27 2012 10:16:04   jankovii
// IN 2817696 - P0186477FN03-Cash Sweep Configuration Issues
// 
//    Rev 1.10   Jan 26 2012 19:38:20   jankovii
// IN 2817696 - P0186477FN03-Cash Sweep Configuration Issues
// 
//    Rev 1.9   Jan 20 2012 11:16:18   jankovii
// IN 2813487 - P0186477FN03 - Cash Sweep DSK Issues
// 
//    Rev 1.8   Jan 13 2012 11:09:52   jankovii
// P0186477 FN03- GIA Maturity/Cash Sweep Instructions - clone
// 
//    Rev 1.7   Jan 11 2012 16:01:48   jankovii
// P0186477 FN03- GIA Maturity/Cash Sweep Instructions
// 
//    Rev 1.6   Jan 06 2012 12:21:40   jankovii
// P0186477 FN03- GIA Maturity/Cash Sweep Instructions
// 
//    Rev 1.5   Dec 21 2011 15:31:04   jankovii
// P0186477 FN03- GIA Maturity/Cash Sweep Instructions
// 
//    Rev 1.4   Dec 19 2011 20:31:36   jankovii
// P0186477 FN03- GIA Maturity/Cash Sweep Instructions
// 
//    Rev 1.3   Dec 16 2011 15:59:08   jankovii
// P0186477 FN03- GIA Maturity/Cash Sweep Instructions
// 
//    Rev 1.4   Dec 16 2011 15:54:18   jankovii
// P0186477 FN03- GIA Maturity/Cash Sweep Instructions
// 
//    Rev 1.3   Dec 15 2011 10:24:44   jankovii
// P0186477 FN03- GIA Maturity/Cash Sweep Instructions
// 
//    Rev 1.2   Dec 14 2011 16:55:42   popescu
// P0186477 FN03- GIA Maturity/Cash Sweep Instructions
 * 
 * 
 */