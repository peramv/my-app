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
// ^FILE   : MatSweepInstr.cpp
// ^AUTHOR : 
// ^DATE   : 
//
//********************************************************************************
#include "stdafx.h"
#include "matsweepinstr.hpp"

#include "fundmasterlist.hpp"
#include "giainvattriblist.hpp"
#include "matsweepinstrdetails.hpp"
#include "matsweepinstrdetailslist.hpp"
#include "matsweepinstrlist.hpp"
#include "mfaccount.hpp"
#include "mgmtco.hpp"
#include "fundlmtoverride.hpp"
#include "FundLmtOverrideList.hpp"

#include <ifastdataimpl\dse_dstc0427_vwrepeat_record.hpp> 

namespace
{
   const I_CHAR * const CLASSNAME         = I_( "MatSweepInstr" );
   const I_CHAR * const ACCOUNT           = I_( "A" );
   const I_CHAR * const INVESTMENT        = I_( "I" );
   const I_CHAR * const SELECTED_AMT      = I_( "2" );
   const I_CHAR * const SWEEP_INSTR       = I_( "SWP" );
   const I_CHAR * const MATURITY_INSTR    = I_("MAT");
   const I_CHAR * const CASH_SWEEP        = I_( "CS" );
   const I_CHAR * const PERCENT           = I_( "P" );
   const I_CHAR * const ACCTLEVEL         = I_( "Acct" );
   const I_CHAR * const PENDING           = I_( "Pend" );
   const I_CHAR * const PROCESSED         = I_( "Proc" );
   const I_CHAR * const NEW               = I_( "New" );
   const I_CHAR * const ONE               = I_( "1" );
   const I_CHAR * const MATURITYINTEREST  = I_( "GB" );
   const I_CHAR * const INTEREST          = I_( "GI" );
   const I_CHAR * const MONTHLY           = I_( "M" );
   const I_CHAR * const YES               = I_("Y");
   const I_CHAR * const NO                = I_("N");
   const I_CHAR * const CASH_SWP_DIF_RULE = I_("60");
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId MatInstrLevel;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFTextFieldId MatInstrXEdit;
   extern CLASS_IMPORT const BFTextFieldId ProcType;
   extern CLASS_IMPORT const BFIntegerFieldId InvestTerm;
   extern CLASS_IMPORT const BFTextFieldId IntCredFreq;
   extern CLASS_IMPORT const BFTextFieldId FromFundNumber;
   extern CLASS_IMPORT const BFTextFieldId InvHisStatus;
   extern CLASS_IMPORT const BFTextFieldId FromFundClass;
   extern CLASS_IMPORT const BFTextFieldId StopFlagSeverityCode;
}

namespace CND
{  // Conditions used
   extern const long ERR_FUND_MUST_BE_DIFF;
   extern const long ERR_FUND_MUST_BE_GIA;
   extern const long ERR_MATSWP_EFFECTIVE_DATE;
   extern const long ERR_ONLY_WRONG_INSTRUCTIONTYPE;
   extern const long WARN_INVALID_FUND_NUMBER;
   extern const long ERR_DIF_DOES_NOT_ALLOW_CASH_SWEEP;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
   // Field DD Id,                  State Flags,            Group Flags 
   { ifds::MatSwpInstructionType,   BFCBO::REQUIRED,              0 },
   { ifds::AccountNum,              BFCBO::NONE,                  0 },
   { ifds::Fund,                    BFCBO::REQUIRED,              0 },
   { ifds::Class,                   BFCBO::REQUIRED,              0 },
   { ifds::SplitType,               BFCBO::REQUIRED,              0 },
   { ifds::EffectiveDate,           BFCBO::NONE,                  0 },
   { ifds::TransNum,                BFCBO::NONE,                  0 },
   { ifds::CashSweepBal,            BFCBO::REQUIRED,              0 },
   { ifds::SelectedAmt,             BFCBO::NONE,                  0 },
   { ifds::IntInvestId,             BFCBO::NONE,                  0 },
   { ifds::GoodBad,                 BFCBO::NONE,                  0 },
   { ifds::TransSeq,                BFCBO::NONE,                  0 },
   { ifds::MatInstrLevel,           BFCBO::NONE,                  0 },
   { ifds::TransId,                 BFCBO::NONE,                  0 },
   { ifds::ProcType,                BFCBO::NONE,                  0 },
   { ifds::MatInstrXEdit,           BFCBO::IMMEDIATE_VALIDATION,  0 },
   { ifds::FromFundNumber,          BFCBO::NONE,                  0 },
   { ifds::InvHisStatus,            BFCBO::NOT_ON_HOST,           0 },
   { ifds::FromFundClass,			BFCBO::IMMEDIATE_VALIDATION,  0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
MatSweepInstr::MatSweepInstr( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );	

   addCrossEdit (ifds::MatInstrXEdit, ifds::Fund);
   addCrossEdit (ifds::MatInstrXEdit, ifds::Class);
   addCrossEdit (ifds::MatInstrXEdit, ifds::MatSwpInstructionType);

   addCrossEdit (ifds::FromFundClass, ifds::FromFundNumber);
   addCrossEdit (ifds::FromFundClass, ifds::Fund);
   addCrossEdit (ifds::FromFundClass, ifds::Class);
  
}

//******************************************************************************
MatSweepInstr::~MatSweepInstr()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY MatSweepInstr::init (const BFData& data, const DString& matSwp, const DString& level)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );	

   attachDataObject(const_cast<BFData&>(data),  false); 

   m_matSwp = matSwp;
   m_Level = level;

   DString dstrMatInstrLevel;
   DString dstrIntInvestId;

   getField (ifds::IntInvestId, dstrIntInvestId, BF::HOST, false);
   dstrIntInvestId.stripLeading( '0' );

   dstrMatInstrLevel = dstrIntInvestId.empty () ? ACCOUNT : INVESTMENT;

   setFieldNoValidate (ifds::MatInstrLevel, dstrMatInstrLevel, BF::HOST, false, true, true, false); 
   setFieldNoValidate (ifds::ProcType, m_Level, BF::HOST, false, true, true, false); 

   DString dstrFund, dstrClass;
   getField (ifds::Fund, dstrFund, BF::HOST, false);
   getField (ifds::Class, dstrClass, BF::HOST, false);

   if( !dstrFund.empty() && !dstrClass.empty() )
   {
      DString dstrFundNumber;
      getWorkSession().GetFundNumber(dstrFund, dstrClass, dstrFundNumber);
      setFieldNoValidate (ifds::FromFundNumber, dstrFundNumber, BF::HOST, false, true, true, false);
   }

   if (dstrMatInstrLevel == INVESTMENT)
   {
      setFieldReadOnly (ifds::Fund, BF::HOST, true);
      setFieldReadOnly (ifds::Class, BF::HOST, true);
      setFieldReadOnly (ifds::FromFundNumber, BF::HOST, true);
   }

   commInit (BF::HOST);

   return(GETCURRENTHIGHESTSEVERITY());
}

//*********************************************************************************
SEVERITY MatSweepInstr::initClone ( MatSweepInstr* pClone, 
                                    const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initClone" ) );
   
   DString dstrTransId;

   getParent ()->getField (ifds::TransId, dstrTransId, idDataGroup, false);

   for (int i = 0; i < NUM_FIELDS; i++)
   {
      BFCBO::CLASS_FIELD_INFO fieldInfo = classFieldInfo [i];     
      const BFFieldId &fieldId = fieldInfo.getFieldId();

      DString fieldValue;

      pClone->getField (fieldId, fieldValue, idDataGroup, false);
      setFieldNoValidate (fieldId, fieldValue, idDataGroup, false, true, false, false);
   }

   setFieldNoValidate (ifds::MatInstrLevel, INVESTMENT, idDataGroup, false, true, false, false);
   setFieldNoValidate (ifds::TransId, dstrTransId, idDataGroup, false, true, false, false);

   MatSweepInstrDetailsList *pMatSweepInstrDetailsListClone (NULL);
   if ( pClone->getMatSweepDetailsList (pMatSweepInstrDetailsListClone, idDataGroup) <= WARNING && 
        pMatSweepInstrDetailsListClone)
   {
      MatSweepInstrDetailsList * pMatSweepInstrDetailsList = NULL;

      if (getMatSweepDetailsList (pMatSweepInstrDetailsList, idDataGroup) <= WARNING &&
         pMatSweepInstrDetailsList)
      {
         pMatSweepInstrDetailsListClone->clone (pMatSweepInstrDetailsList, idDataGroup);
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//****************************************************************************
SEVERITY MatSweepInstr::initNew ( const DString& accountNum, 
                                  const DString& matSwp, 
                                  const DString& level,
                                  const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initNew" ) );

   m_matSwp = matSwp;
   m_Level = level;
   DString dstrTransId;
   DString dstrCurrBusDate;

   getParent ()->getField (ifds::TransId, dstrTransId, idDataGroup, false);

   getWorkSession ().getOption ( ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false);

   setFieldNoValidate(ifds::EffectiveDate, dstrCurrBusDate, idDataGroup, false, true, true, false);
   setFieldNoValidate (ifds::AccountNum, accountNum, idDataGroup, true, true, true);
   setFieldNoValidate (ifds::GoodBad, I_("Y"), idDataGroup, true, true, true);
   setFieldNoValidate (ifds::TransId, dstrTransId, idDataGroup, true, true, true);
   setFieldNoValidate (ifds::ProcType, m_Level, idDataGroup, false, true, true, false); 

   DString dstrMatInstrLevel;

   if (m_Level == ACCTLEVEL)
   {
      // coming from pressing Add on account level screen:
      dstrMatInstrLevel = ACCOUNT;
   }
   else
   {
      DString dstrFund;
      DString dstrClass;
      DString dstrIntInvestId;

      dstrMatInstrLevel =INVESTMENT;

      getParent ()->getField (ifds::Fund, dstrFund, idDataGroup, false);
      getParent ()->getField (ifds::Class, dstrClass, idDataGroup, false);
      getParent ()->getField (ifds::IntInvestId, dstrIntInvestId, idDataGroup, false);

      setFieldNoValidate (ifds::Fund, dstrFund, idDataGroup, false, true, true, false); 
      setFieldNoValidate (ifds::Class, dstrClass, idDataGroup, false, true, true, false);
      setFieldNoValidate (ifds::IntInvestId, dstrIntInvestId, idDataGroup, false, true, true, false);

      DString dstrFundNumber;
      getWorkSession().GetFundNumber(dstrFund, dstrClass, dstrFundNumber);
      setFieldNoValidate (ifds::FromFundNumber, dstrFundNumber, idDataGroup, false, true, true, false);

      setFieldReadOnly (ifds::Fund, idDataGroup, true);
      setFieldReadOnly (ifds::Class, idDataGroup, true);
      setFieldReadOnly (ifds::FromFundNumber, idDataGroup, true);
   }

   setFieldNoValidate (ifds::MatInstrLevel, dstrMatInstrLevel, idDataGroup, false, true, true, false); 

   commInit (idDataGroup);

   return GETCURRENTHIGHESTSEVERITY();
}

//*********************************************************************************
void MatSweepInstr::doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
{
   DString dstrCurrBusDate;
   getWorkSession ().getOption ( ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false);

   setFieldNoValidate(ifds::EffectiveDate, dstrCurrBusDate, idDataGroup, false, true, true, false);

   if (m_matSwp == SWEEP_INSTR)
   {
      setFieldNoValidate(ifds::MatSwpInstructionType, CASH_SWEEP, idDataGroup, true);
   }

   DString dstrTransId;
   DString dstrTransNum;

   getParent ()->getField (ifds::TransId, dstrTransId, idDataGroup, false);
   getParent ()->getField (ifds::TransNum, dstrTransNum, idDataGroup, false);

   setFieldNoValidate (ifds::TransId, dstrTransId, idDataGroup, false, true, true, false);
   setFieldNoValidate (ifds::TransNum, dstrTransNum, idDataGroup, false, true, true, false);

   DString dstrIntInvestId;

   getField (ifds::IntInvestId, dstrIntInvestId, idDataGroup, false);
   dstrIntInvestId.stripLeading( '0' );

   if (dstrIntInvestId.empty ())
   {
      setFieldNoValidate(ifds::SplitType, PERCENT, idDataGroup, false, true, true, false);
   }
}

//*********************************************************************************
SEVERITY MatSweepInstr::doValidateField( const BFFieldId& idField, 
                                         const DString& dstrValue, 
                                         const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField" ));   

   if (idField == ifds::Fund)
   {
      FundMasterList *pFundMasterList; 

      if (!dstrValue.empty() && getMgmtCo().getFundMasterList (pFundMasterList) && 
         pFundMasterList)
      {
         if (m_matSwp == SWEEP_INSTR && !pFundMasterList->isDIFFund (dstrValue))
         {
            ADDCONDITIONFROMFILE (CND::ERR_FUND_MUST_BE_DIFF)
         }
         else if (m_matSwp == MATURITY_INSTR && !pFundMasterList->isGIAFund (dstrValue))
         {
            ADDCONDITIONFROMFILE (CND::ERR_FUND_MUST_BE_GIA)
         }
      }

      validateFundClass (idDataGroup);
   }
   else if (idField == ifds::Class)
   {
      validateFundClass (idDataGroup);
   }
   else if (idField == ifds::EffectiveDate)
   {
      // cannot be before account eff date
      MFAccount *pMFAccount=NULL;
      DString accountNum;

      getField (ifds::AccountNum, accountNum, idDataGroup);

      if (getWorkSession ().getMFAccount (idDataGroup, accountNum, pMFAccount) <= WARNING &&
         pMFAccount)
      {
         DString dstrAcctEffectiveDate;

         pMFAccount->getField (ifds::EffectiveDate, dstrAcctEffectiveDate, idDataGroup, false);

         if( DSTCommonFunctions::CompareDates( dstrValue, dstrAcctEffectiveDate ) == DSTCommonFunctions::FIRST_EARLIER )
         {
            ADDCONDITIONFROMFILE (CND::ERR_MATSWP_EFFECTIVE_DATE)
         }
      }	
   }
   else if (idField == ifds::MatInstrXEdit)
   {
      // Duplicate check
      if (isUpdatedForDataGroup (idDataGroup, true))
      {
         MatSweepInstrList *pMatSweepInstrList = dynamic_cast<MatSweepInstrList*>( getParent( ) );      

         if (pMatSweepInstrList)
         {
            DString dstrHasDuplicate;

            pMatSweepInstrList->checkDuplicate( this, idDataGroup );
            pMatSweepInstrList->validateMaturityInterestInstr (this, idDataGroup);
         }
      }
   }
   else if (idField == ifds::MatSwpInstructionType)
   {
      validateInstructionType (dstrValue, idDataGroup);
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
   else if (idField == ifds::FromFundClass)
   {      
      if (isUpdatedForDataGroup (idDataGroup, true))
      {         
		 FundMasterList *pFundMasterList; 
		 if (getMgmtCo().getFundMasterList (pFundMasterList) && pFundMasterList) 
		 {
			 DString fundCode, classCode, dstrEWI;
			 getField (ifds::Fund, fundCode, idDataGroup);
			 getField (ifds::Class, classCode, idDataGroup);

			 if (!fundCode.empty() && !classCode.empty())
			 {
				 if (m_matSwp == SWEEP_INSTR && pFundMasterList->isDIFFund (fundCode))
				 {
					 bool bCashSweepNotAllowed = isRuleTypeEnabledForFundClass (fundCode, classCode, CASH_SWP_DIF_RULE, dstrEWI, idDataGroup);

					 dstrEWI.upperCase ();
					 if (bCashSweepNotAllowed && dstrEWI == I_("E"))
					 {
						 ADDCONDITIONFROMFILE (CND::ERR_DIF_DOES_NOT_ALLOW_CASH_SWEEP) // cash sweeps are not permitted for high interest DIF
					 }
				 }
			 }
		 }
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************
SEVERITY MatSweepInstr::commInit (const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "commInit" ) );

   DString dstrMatInstrLevel;
   DString dstrCashSweepBal;

   getField (ifds::MatInstrLevel, dstrMatInstrLevel, idDataGroup, false);

   // percent - account level
   bool bSplitTypeReadOnly = dstrMatInstrLevel == ACCOUNT ? true : false;
   setFieldReadOnly (ifds::SplitType, idDataGroup, bSplitTypeReadOnly);

   // cash sweep balance		
   getField (ifds::CashSweepBal, dstrCashSweepBal, idDataGroup, false);

   bool bReadOnly = dstrCashSweepBal == SELECTED_AMT ? false : true;

   setFieldReadOnly (ifds::SelectedAmt, idDataGroup, bReadOnly);
   setFieldRequired (ifds::SelectedAmt, idDataGroup, !bReadOnly);

   if (m_matSwp == SWEEP_INSTR)
   {
      setFieldReadOnly (ifds::MatSwpInstructionType, idDataGroup, true);
   }
   else
   {
      DString dstrMaturitySubSet;
      BFProperties *pBFProperties = getFieldProperties (ifds::MatSwpInstructionType, idDataGroup);

      pBFProperties->getAllSubstituteValues (dstrMaturitySubSet);

      dstrMaturitySubSet = removeItemFromSubtList (dstrMaturitySubSet, CASH_SWEEP);
      setFieldAllSubstituteValues (ifds::MatSwpInstructionType, idDataGroup, dstrMaturitySubSet);

      setCashSweepBalFeildsReadOnly (idDataGroup);
   }

   // if record is not good set it read only:
   setAllFeildsReadOnly (idDataGroup);

   return GETCURRENTHIGHESTSEVERITY ();
}

//*******************************************************************************
SEVERITY MatSweepInstr::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );

   if (idField == ifds::Fund || idField == ifds::Class)
   {
      FundMasterList *pFundMasterList; 
      DString dstrFund;

      getField (ifds::Fund, dstrFund, idDataGroup, false);

      if ( (getMgmtCo().getFundMasterList (pFundMasterList) && pFundMasterList) && (idField == ifds::Fund) )
      {
         if (m_matSwp == SWEEP_INSTR && pFundMasterList->isDIFFund (dstrFund))
         {
            setFieldReadOnly (ifds::CashSweepBal, idDataGroup, false);
            setFieldReadOnly (ifds::SelectedAmt, idDataGroup, true);
            setFieldRequired (ifds::CashSweepBal, idDataGroup, true);
         }
         else 
         {
            setCashSweepBalFeildsReadOnly (idDataGroup);
         }
      }

      DString dstrClass;
      getField (ifds::Class, dstrClass, idDataGroup, false);

      if(!dstrFund.empty() && !dstrClass.empty() )
      {
         DString dstrFundNumber;
         getWorkSession().GetFundNumber(dstrFund, dstrClass, dstrFundNumber);
         setFieldNoValidate ( ifds::FromFundNumber, dstrFundNumber, idDataGroup, false, 
                              true, 
                              true, //notify
                              false);
      }
   }
   else if (idField == ifds::CashSweepBal)
   {
      DString dstrCashSweepBal;

      getField (ifds::CashSweepBal, dstrCashSweepBal, idDataGroup, false);

      bool bReadOnly = dstrCashSweepBal == SELECTED_AMT ? false : true;

      if (bReadOnly)
      {
         setFieldNoValidate (ifds::SelectedAmt, I_("0"), idDataGroup, true); 
      }

      setFieldReadOnly (ifds::SelectedAmt, idDataGroup, bReadOnly);
      setFieldRequired (ifds::SelectedAmt, idDataGroup, !bReadOnly);
   }
   else if (idField == ifds::SplitType)
   {
      splitTypeRelatedChanges (idDataGroup);
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
            setField (ifds::Fund,   dstrFundCode, idDataGroup, false, true);
            setField (ifds::Class, dstrClassCode, idDataGroup, false, true);

            setFieldValid (ifds::Fund,  idDataGroup, false);
            setFieldValid (ifds::Class, idDataGroup, false);
         }
      }
   }

   else if (idField == ifds::InvHisStatus)
   {
      setAllFeildsReadOnly (idDataGroup);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************
SEVERITY MatSweepInstr::doValidateAll (const BFDataGroupId& idDataGroup, long lValidateGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   // tmp fix:
   DString dstrTransId;

   getParent ()->getField (ifds::TransId, dstrTransId, idDataGroup, false);
   setFieldNoValidate (ifds::TransId, dstrTransId, idDataGroup, true, true, true);
   //
   validateSelectedAmount (idDataGroup);

   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************
SEVERITY MatSweepInstr::getMatSweepDetailsList ( MatSweepInstrDetailsList *&pMatSweepInstrDetailsList, 
                                                 const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getMatSweepDetailsList"));

   DString dstrAccountNum,
      dstrFund,
      dstrClass,
      dstrInstrType,
      dstrEffectiveDate,
      dstrTransNum,
      dstrGBCD,
      dstrInvestId,
      dstrTransSeq;

   getField (ifds::AccountNum, dstrAccountNum, idDataGroup, false);
   getField (ifds::Fund, dstrFund, idDataGroup, false);
   getField (ifds::Class, dstrClass, idDataGroup, false);
   getField (ifds::MatSwpInstructionType, dstrInstrType, idDataGroup, false);
   getField (ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false);
   getField (ifds::TransNum, dstrTransNum, idDataGroup, false);
   getField (ifds::GoodBad, dstrGBCD, idDataGroup, false);
   getField (ifds::IntInvestId, dstrInvestId, idDataGroup, false);
   getField (ifds::TransSeq, dstrTransSeq, idDataGroup, false);

   DString strKey = I_("MatSweepInstrDetailsList");

   pMatSweepInstrDetailsList = dynamic_cast<MatSweepInstrDetailsList*> (getObject (strKey, idDataGroup));

   if (!pMatSweepInstrDetailsList)
   {
      pMatSweepInstrDetailsList = new MatSweepInstrDetailsList (*this);

      if (isNew () || pMatSweepInstrDetailsList->init( dstrAccountNum, 
                                                       dstrFund, 
                                                       dstrClass, 
                                                       dstrInstrType,
                                                       dstrTransNum, 
                                                       dstrEffectiveDate, 
                                                       dstrInvestId, 
                                                       dstrGBCD,
                                                       dstrTransSeq) <= WARNING)
      {
         setObject (pMatSweepInstrDetailsList, strKey, OBJ_ACTIVITY_NONE, idDataGroup);
      }
      else
      {
         delete pMatSweepInstrDetailsList;
         pMatSweepInstrDetailsList = NULL;
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//****************************************************************************** 
SEVERITY MatSweepInstr::validateFundClass (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateFundClass"));

   DString fundCode;
   DString classCode;
   DString accountNum;

   getField (ifds::Fund, fundCode, idDataGroup);
   getField (ifds::Class, classCode, idDataGroup);
   getField (ifds::AccountNum, accountNum, idDataGroup);

   accountNum.stripLeading ('0').strip ();

   if (!accountNum.empty() && !fundCode.empty() && !classCode.empty())
   {
      // validate fund/class in shgrop or portoflio
      MFAccount *pMFAccount=NULL;

      if (getWorkSession ().getMFAccount (idDataGroup, accountNum, pMFAccount) <= WARNING &&
         pMFAccount)
      {
         DString effectiveDate;
         getField (ifds::EffectiveDate, effectiveDate, idDataGroup, false);

         pMFAccount->fundClassInGroup (fundCode, classCode, effectiveDate, idDataGroup);

      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//****************************************************************************** 
SEVERITY MatSweepInstr::validateSelectedAmount (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateSelectedAmount"));

   DString dstrCashSweepBal;
   DString dstrInstrType;

   getField (ifds::CashSweepBal, dstrCashSweepBal, idDataGroup, false);
   getField (ifds::MatSwpInstructionType, dstrInstrType, idDataGroup, false);

   if (dstrCashSweepBal == SELECTED_AMT  && dstrInstrType == CASH_SWEEP)
   {
      DString dstrSelectedAmt;

      getField (ifds::SelectedAmt, dstrSelectedAmt, idDataGroup);
      dstrSelectedAmt.stripLeading ('0').strip ();

      MatSweepInstrDetailsList *pMatSweepInstrDetailsList (NULL);

      if (getMatSweepDetailsList (pMatSweepInstrDetailsList, idDataGroup) <= WARNING && 
         pMatSweepInstrDetailsList)
      {
         double dMinCashSweepAmount = 0; 

         pMatSweepInstrDetailsList->validateFundClassMinAmount (dstrSelectedAmt, idDataGroup);
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//****************************************************************************** 
SEVERITY MatSweepInstr::validateInstructionType (const DString &dstrInstrType, const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateInstructionType"));

   DString dstrSimpleTermList;

   getTermsList (dstrSimpleTermList, idDataGroup);
   dstrSimpleTermList.strip (I_(','));

   if (dstrSimpleTermList == ONE && dstrInstrType != MATURITYINTEREST)
   {
      // note need conditions
      ADDCONDITIONFROMFILE (CND::ERR_ONLY_WRONG_INSTRUCTIONTYPE)
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//****************************************************************************** 
SEVERITY MatSweepInstr::getTermsList (DString &dstrSimpleTermList,
                                      const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getGIFundDefaults"));

   DString dstrFund;
   DString dstrClass;
   DString	dstrEffectiveDate;

   GIAInvAttribList *pGIAInvAttribList = NULL;

   getField (ifds::Fund, dstrFund, idDataGroup, false);
   getField (ifds::Class, dstrClass, idDataGroup, false);
   getField (ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false);

   if (!dstrFund.empty() && !dstrClass.empty())
   {
      DString strKey;

      FundMasterList *pFundMasterList; 

      if (getMgmtCo().getFundMasterList (pFundMasterList) && 
         pFundMasterList)
      {
         if (!pFundMasterList->isGIAFund (dstrFund))
         {
            return GETCURRENTHIGHESTSEVERITY ();
         }
      }

      strKey = I_("GIAInvAttribsList_FundCode=") + dstrFund + I_(";")
                + I_("ClassCode=") + dstrClass + I_(";")
                + I_("TradeDate=") + dstrEffectiveDate;

         pGIAInvAttribList = dynamic_cast <GIAInvAttribList*> (getObject (strKey, idDataGroup));

         if (!pGIAInvAttribList)
         {
            pGIAInvAttribList = new GIAInvAttribList (*this);

            if (pGIAInvAttribList->init (dstrFund, dstrClass, dstrEffectiveDate) <= WARNING)
            {
               setObject (pGIAInvAttribList, strKey, OBJ_ACTIVITY_NONE, idDataGroup);
            }
            else
            {
               delete pGIAInvAttribList;
               pGIAInvAttribList = NULL;
            }
         }

         if (pGIAInvAttribList)
         {
            pGIAInvAttribList->getField(ifds::SimpleTermList, dstrSimpleTermList, idDataGroup, false );
         }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY MatSweepInstr::setCashSweepBalFeildsReadOnly (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("setCashSweepBalFeildsReadOnly"));

   setFieldNoValidate (ifds::CashSweepBal, I_(""), idDataGroup, true); 
   setFieldNoValidate (ifds::SelectedAmt, I_("0"), idDataGroup, true); 
   setFieldReadOnly (ifds::CashSweepBal, idDataGroup, true);
   setFieldReadOnly (ifds::SelectedAmt, idDataGroup, true);
   setFieldRequired (ifds::CashSweepBal, idDataGroup, false);

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY MatSweepInstr::setAllFeildsReadOnly (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("setAllFeildsReadOnly"));

   DString dstrGoodBad;
   DString dstrMatInstrLevel;
   DString dstrProcType;
   bool    bReadOnly = false;

   getField (ifds::GoodBad, dstrGoodBad, idDataGroup, false);
   getField (ifds::MatInstrLevel, dstrMatInstrLevel, idDataGroup, false);
   getField (ifds::ProcType, dstrProcType, idDataGroup, false);

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

         getField (ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false);
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

   setFieldReadOnly (ifds::MatSwpInstructionType, idDataGroup, true);
   setFieldReadOnly (ifds::AccountNum,	idDataGroup, true);
   setFieldReadOnly (ifds::Fund, idDataGroup, true);
   setFieldReadOnly (ifds::Class,idDataGroup, true);
   setFieldReadOnly (ifds::FromFundNumber,idDataGroup, true);
   setFieldReadOnly (ifds::SplitType, idDataGroup, true);
   setFieldReadOnly (ifds::EffectiveDate, idDataGroup, true);
   setFieldReadOnly (ifds::CashSweepBal, idDataGroup, true);
   setFieldReadOnly (ifds::SelectedAmt, idDataGroup, true);

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY MatSweepInstr::splitTypeRelatedChanges (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("splitTypeRelatedChanges"));

   DString dstrSplitType;
   DString dstrMatInstrLevel;

   getField (ifds::SplitType, dstrSplitType, idDataGroup, false);

   MatSweepInstrDetailsList *pMatSweepInstrDetailsList (NULL);

   if (getMatSweepDetailsList (pMatSweepInstrDetailsList, idDataGroup) <= WARNING && 
      pMatSweepInstrDetailsList)
   {
      pMatSweepInstrDetailsList->resetRemainingFlag (dstrSplitType, idDataGroup);
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//*****************************************************************************
SEVERITY MatSweepInstr::setMinimumAmount (const DString &dstrFundCode, 
                                          const DString &dstrClassCode, 
                                          const DString &dstrMinAmount,
                                          const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("setMinimumAmount"));

   setFieldNoValidate (ifds::SelectedAmt, dstrMinAmount, idDataGroup, true); 

   return GETCURRENTHIGHESTSEVERITY ();
}

//*****************************************************************************
SEVERITY MatSweepInstr::checkDuplicateActiveInstr (DString &dstrActiveInstrExists, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("checkDuplicateActiveInstr"));

   MatSweepInstrList *pMatSweepInstrList = dynamic_cast<MatSweepInstrList*>( getParent( ) );

   if (pMatSweepInstrList)
   {
      pMatSweepInstrList->checkActiveDuplicate( this, dstrActiveInstrExists, idDataGroup );
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//****************************************************************************
SEVERITY MatSweepInstr::getFundLmtOverrideList (FundLmtOverrideList *&pFundLmtOverrideList,
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

      if (pFundLmtOverrideList->init (fundCode, classCode, CASH_SWEEP) <= WARNING)
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

//*****************************************************************************
bool MatSweepInstr::isRuleTypeEnabledForFundClass (const DString &dstrFundCode, 
												   const DString &dstrClassCode,														  
												   const DString ruleType,
												   DString &dstrEWI,
												   const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("isRuleTypeEnabledForFundClass"));

   FundLmtOverrideList	*pFundToLmtOverrideList = NULL;
   FundLmtOverride		*pFundLmtOverride = NULL;
   DString dstrAccountNum;

   bool bRuleTypeEnabled = false;

   getParent ()->getParent ()->getField (ifds::AccountNum, dstrAccountNum, idDataGroup, false);

   if (getFundLmtOverrideList (pFundToLmtOverrideList, dstrFundCode, dstrClassCode, idDataGroup) <= WARNING && pFundToLmtOverrideList)
   {
	   if (pFundToLmtOverrideList->getFundLmtOverride (getWorkSession(), dstrAccountNum, ruleType, pFundLmtOverride, idDataGroup) <= WARNING && pFundLmtOverride)
	   {       
		   bRuleTypeEnabled = true;
		   pFundLmtOverride->getField (ifds::StopFlagSeverityCode, dstrEWI, idDataGroup, false);
		   dstrEWI.strip().upperCase();
	   }
   }

   return bRuleTypeEnabled;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/MatSweepInstr.cpp-arc  $
// 
//    Rev 1.26   Jul 17 2012 15:21:52   kitticha
// IN#2932057 - User should not be able to maintain the instruction when investment is matured.
// 
//    Rev 1.25   Jun 08 2012 14:08:58   jankovii
// IN 2957854 - P0186477_FN05_03_Same transno. in distrib-delt to be used & changes to misc-info
// 
//    Rev 1.24   May 15 2012 15:25:04   wp040100
// IN 2886441- Incorporated code review comments
// 
//    Rev 1.23   May 14 2012 18:28:28   wp040100
// IN 2886441 - Included BayCom/Fund Number 
// 1. Cash Sweep Screen.
// 2. Maturity Interest Instructions Screen.
// 3. GI investment Histroy Screen.
// 
//    Rev 1.22   Apr 22 2012 20:35:08   jankovii
// IN 2847670 
// 
//    Rev 1.21   Apr 22 2012 18:47:56   jankovii
// IN 2847670 & 2815937
// 
//    Rev 1.20   Mar 28 2012 15:25:06   jankovii
// IN 2889383 - P0186477_FN05_Maturity Processing Dsktp issues_LIST 1_Seg_intrnl errr_min issues
// 
//    Rev 1.19   Feb 28 2012 11:50:44   jankovii
// IN 2861935 - Maturity_Interest Screen issues
// 
//    Rev 1.18   Feb 06 2012 15:54:38   jankovii
// IN 2835682 - P0186477FN03 -Database error when accessing Maturity/ Interest Screen
// 
//    Rev 1.17   Feb 03 2012 11:22:48   jankovii
// IN 2813743 - P0186477FN03- Can't Access Maturity Instructions thru Investment Hist
// 
//    Rev 1.16   Feb 02 2012 10:49:10   jankovii
// IN 2826242- Maturity/Interest Instruction on Trading Screen
// 
//    Rev 1.15   Jan 31 2012 19:11:34   jankovii
// IN 2826242- Maturity/Interest Instruction on Trading Screen
// 
//    Rev 1.14   Jan 27 2012 10:15:22   jankovii
// IN 2817696 - P0186477FN03-Cash Sweep Configuration Issues
// 
//    Rev 1.13   Jan 26 2012 19:25:58   jankovii
// IN 2817696 - P0186477FN03-Cash Sweep Configuration Issues
// 
//    Rev 1.12   Jan 20 2012 11:17:20   jankovii
// IN 2813487 - P0186477FN03 - Cash Sweep DSK Issues
// 
//    Rev 1.11   Jan 13 2012 11:09:12   jankovii
// P0186477 FN03- GIA Maturity/Cash Sweep Instructions - clone
// 
//    Rev 1.10   Jan 11 2012 15:58:58   jankovii
// P0186477 FN03- GIA Maturity/Cash Sweep Instructions
// 
//    Rev 1.9   Jan 06 2012 12:15:48   jankovii
// P0186477 FN03- GIA Maturity/Cash Sweep Instructions
// 
//    Rev 1.8   Dec 21 2011 15:29:58   jankovii
// P0186477 FN03- GIA Maturity/Cash Sweep Instructions
// 
//    Rev 1.7   Dec 20 2011 17:40:40   popescu
// P0186477 FN03- GIA Maturity/Cash Sweep Instructions
// 
//    Rev 1.6   Dec 19 2011 20:29:14   jankovii
// P0186477 FN03- GIA Maturity/Cash Sweep Instructions
// 
//    Rev 1.5   Dec 19 2011 06:01:28   popescu
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
