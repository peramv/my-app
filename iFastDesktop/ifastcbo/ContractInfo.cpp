//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2005 by International Financial Data Services
//
//*****************************************************************************
//
// ^FILE   : ContractInfo.cpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 29/02/2000
//
// ^CLASS    : ContractInfo
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "accountentityxrefobject.hpp"
#include "AccountEntityXref.hpp"
#include "agentlist.hpp"
#include <bfutil\bfdate.hpp>
#include "contractinfo.hpp"
#include "contractinfolist.hpp"
#include "CotLegalAge.hpp"
#include "dstcommonfunction.hpp"
#include "entitylist.hpp"
#include "entity.hpp"
#include "mastercontractlist.hpp"
#include "mfaccount.hpp"
#include "mfaccountholdinglist.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "respinfo.hpp"
#include "seqfundvalidation.hpp"
#include "shareholder.hpp"
#include "taxtyperule.hpp"
#include "taxtyperulelist.hpp"

#include <bfutil\bfdate.hpp>

#include <ifastdataimpl\dse_dstc0004_vw.hpp>
#include <ifastdataimpl\dse_dstc0083_vw.hpp>
#include <ifastdataimpl\dse_dstc0367_vw.hpp>
#include <ifastdataimpl\dse_dstc0092_vw.hpp>
#include <ifastdataimpl\dse_dstc0105_vw.hpp>
#include <ifastdataimpl\dse_dstc0133_vw.hpp>

namespace
{
   const I_CHAR * const ACCT_STATUS_ACTIVE                     = I_( "10" );
   const I_CHAR * const ACCT_STATUS_DEATH                      = I_( "40" );
   const I_CHAR * const ACCT_STATUS_DEATHTRANSFER              = I_( "41" );
   const I_CHAR * const BLANK_SUBSTITUTION                     = I_( " = ;" );    // substitution with only one element with tag = value = " " 
   const I_CHAR * const CLASSNAME                              = I_( "ContractInfo" );

   const I_CHAR * const CONTRACT_STATUS_ACTIVE                 = I_( "01" );
   const I_CHAR * const CONTRACT_STATUS_PENDINGDEATH           = I_( "02" );
   const I_CHAR * const CONTRACT_STATUS_DEATH                  = I_( "03" );
   const I_CHAR * const CONTRACT_STATUS_SETTLEMENT             = I_( "04" );

   const I_CHAR * const CRITICALAGE                            = I_( "01" );
   const I_CHAR * const USERDEFINED                            = I_( "02" );
   const I_CHAR * const CMD_BASED_ON_MAX_AGE                   = I_( "01" );
   const I_CHAR * const CMD_BASED_ON_MIN_TERM                  = I_( "02" );
   const I_CHAR * const CMD_BASED_ON_LCMD                      = I_( "03" );
   const I_CHAR * const CMD_BASED_ON_USERDEFINED               = I_( "04" );   
   const I_CHAR * const CMD_BASED_ON_USERDEFINED_TRANSFER      = I_( "07" );

   const I_CHAR * const YES                                    = I_ ( "Y" );
   const I_CHAR * const NO                                     = I_ ( "N" );
}

namespace ifds
{  
   extern CLASS_IMPORT const BFTextFieldId CreateRep;   
   extern CLASS_IMPORT const BFTextFieldId StatusActive;
   extern CLASS_IMPORT const BFTextFieldId StatusActiveDeath;
   extern CLASS_IMPORT const BFTextFieldId StatusBlank;  
   extern CLASS_IMPORT const BFTextFieldId StatusDeath;

   extern CLASS_IMPORT const BFDecimalFieldId SettledUnits;
   extern CLASS_IMPORT const BFDecimalFieldId UnsettledUnits;    

   extern CLASS_IMPORT const BFDateFieldId PrevEffectiveDate;
   extern CLASS_IMPORT const BFTextFieldId ContractEffectiveDate;
   extern CLASS_IMPORT const BFTextFieldId EffectiveStopDate;
   
   // Take these out as soon as we have them in the view
   extern CLASS_IMPORT const BFDateFieldId GWOCotAnnivDate;
   extern CLASS_IMPORT const BFTextFieldId GWOSupported;
   extern CLASS_IMPORT const BFDateFieldId DofBirth;
   extern CLASS_IMPORT const BFNumericFieldId EntityId;
   extern CLASS_IMPORT const BFTextFieldId EntityType;
   extern CLASS_IMPORT const BFNumericFieldId SeqNumber;
   extern CLASS_IMPORT const BFNumericFieldId ShrNum;
   extern CLASS_IMPORT const BFTextFieldId ResProvCode;
   extern CLASS_IMPORT const BFDateFieldId UserDefinedMaturityDate;
   extern CLASS_IMPORT const BFDateFieldId DateOfReg;
   extern CLASS_IMPORT const BFDateFieldId FirstEffective;
   extern CLASS_IMPORT const BFTextFieldId AcctStatus;
   extern CLASS_IMPORT const BFTextFieldId PorfolioIsRequried;
   extern CLASS_IMPORT const BFTextFieldId IsDuringNASU;
   extern CLASS_IMPORT const BFTextFieldId GuaranteeCalcByRules;
   extern CLASS_IMPORT const BFTextFieldId ContractMaturDateCrossEdit;
   extern CLASS_IMPORT const BFTextFieldId FieldCrossEdit1;
   extern CLASS_IMPORT const BFTextFieldId FieldCrossEdit2;
   extern CLASS_IMPORT const BFTextFieldId InsurAgeType;
   extern CLASS_IMPORT const BFTextFieldId ContractMatBasedOnOrig;
   extern CLASS_IMPORT const BFTextFieldId TaxJurisCode;
   extern CLASS_IMPORT const BFIntegerFieldId NumOfYears;
   extern CLASS_IMPORT const BFIntegerFieldId AltNumOfYears;
   extern CLASS_IMPORT const BFTextFieldId RESPClassify;
   extern CLASS_IMPORT const BFTextFieldId MoneyInExist;
}

namespace CND
{  // Conditions used
   extern const long ERR_CHANGE_STATUS_TO_DEATH;
   extern const long ERR_DUPLICATE_RECORD;
   extern const long ERR_EFFECTIVE_DATE_CONTRACT_EARLIER_THAN_EFFECTIVE_DATE_MFACCOUNT;
   extern const long ERR_EFF_DATE_LATE_THAN_STOP_DATE;
   extern const long ERR_INACTIVE_SALES_REP;
   extern const long ERR_INVALID_CONTRACT_TERM;
   extern const long ERR_INVALID_MATURITY_TYPE;
   extern const long WARN_INVALID_PROVINCE;
   extern const long ERR_LEGAL_MATURITY_DATE_EARLY_THAN_TODAY;
   extern const long ERR_STATUS_CHANGED;
   extern const long ERR_STATUS_IS_BLANK;
   extern const long ERR_STOP_DATE_LESS_THAN_DEFF;
   extern const long ERR_USER_MATURITY_DATE_EMPTY;  
   extern const long ERR_CONTRACT_EFF_DATE_AFTER_ISSUE_DATE;
   extern const long ERR_ACCT_CONT_NON_ACTIVE_STATUS_SELECTED;
   extern const long ERR_ACCT_CONT_SETTL_STATUS_CANNOT_BE_SELECTED;
   extern const long ERR_OLDEST_LEGAL_DATE_CANNOT_BE_IN_THE_PAST;
   extern const long ERR_NO_DATE_OF_BIRTH;   
   extern const long ERR_USER_DEFINED_MATURITY_DATE_CANNOT_BE_BLANK;
   extern const long WARN_USER_DEFINED_MATURITY_DATE_CANNOT_BE_BLANK;
   extern const long ERR_ACCT_STATUS_DEATH_OR_DEATH_TRANSFER;
   extern const long ERR_STATUS_NOT_ALLOWED_FOR_ACCT_DEATH_OR_DEATH_TRANSFER;
   extern const long ERR_EFFECTIVEDATE_MUST_BE_EARLIER_STOPDATE;
   extern const long ERR_CMD_AFTER_LCMD;
   extern const long ERR_STOP_DATE_EARLIER_EFFDATE;
   extern const long ERR_EFFDATE_AFTER_STOP_DATE;
   extern const long ERR_INVALID_PENSION;
   extern const long ERR_INVALID_TAX_TYPE;
   extern const long ERR_USER_DEFINED_MATURITY_DATE_SHOULD_BE_BETWEEN_MIN_MAX_AGE;
   extern const long WARN_USER_DEFINED_MATURITY_DATE_SHOULD_BE_BETWEEN_MIN_MAX_AGE;
   extern const long ERR_USER_DEFINED_MATURITY_DATE_SHOULD_BE_GREATER_THAN_MIN_TERM;
   extern const long WARN_USER_DEFINED_MATURITY_DATE_SHOULD_BE_GREATER_THAN_MIN_TERM;
   extern const long ERR_USER_DEFINED_MATURITY_DATE_LESS_THAN_MATURITY_DATE;
   extern const long WARN_USER_DEFINED_MATURITY_DATE_LESS_THAN_MATURITY_DATE;
   extern const long ERR_GENDER_CANNOT_BE_BLANK_FOR_NMCR_SINGLE_LIFE_CONTRACT;
   extern const long WARN_GENDER_CANNOT_BE_BLANK_FOR_NMCR_SINGLE_LIFE_CONTRACT;

}

namespace IFASTERR
{ 
   extern CLASS_IMPORT I_CHAR * const USER_DEF_MAT_LESS;	
   extern CLASS_IMPORT I_CHAR * const USER_DEFINED_MATURITY_DATE_CANNOT_BE_BLANK;   
   extern CLASS_IMPORT I_CHAR * const USER_DEFINED_MATURITY_DATE_SHOULD_BE_BETWEEN_MIN_MAX_AGE;
   extern CLASS_IMPORT I_CHAR * const USER_DEFINED_MATURITY_DATE_SHOULD_BE_GREATER_THAN_MIN_TERM;
   extern CLASS_IMPORT I_CHAR * const USER_DEFINED_MATURITY_DATE_LESS_THAN_MATURITY_DATE;
   extern CLASS_IMPORT I_CHAR * const GENDER_CANNOT_BE_BLANK_FOR_NMCR_SINGLE_LIFE_CONTRACT;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const SEG_FUND_MULTI_CONTRACT;
   extern CLASS_IMPORT I_CHAR * const SEG_GUAR_ADJ_BAND;	
   extern CLASS_IMPORT I_CHAR * const SETTLEMENT_PHASE_STATUS_CHANGE;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,                       State Flags,         Group Flags 
   { ifds::EffectiveDate,              BFCBO::REQUIRED,     0 }, 
   { ifds::StopDate,                   BFCBO::NONE,         0 }, 
   { ifds::Status,                     BFCBO::REQUIRED,     0 }, 
   { ifds::StatusDesc,                 BFCBO::NONE,         0 }, 
   { ifds::ContractTerm,               BFCBO::REQUIRED,     0 }, 
   { ifds::ProvinceCanada,             BFCBO::REQUIRED,     0 }, 
   //{ ifds::MaturityType,             BFCBO::REQUIRED,     0 }, 
   //{ ifds::MaturityTypeDesc,         BFCBO::NONE,         0 }, 
   //{ ifds::PrevEffectiveDate,        BFCBO::NONE,         0 }, 
   { ifds::ContractTermDesc,           BFCBO::NONE,         0 }, 
   //{ ifds::UserMaturityDate,         BFCBO::NONE,         0 }, 
   { ifds::Username,                   BFCBO::NONE,         0 }, 
   { ifds::ProcessDate,                BFCBO::NONE,         0 }, 
   { ifds::ContractType,               BFCBO::NONE,         0 }, 
   { ifds::ContractTypeId,             BFCBO::NONE,         0 }, 
   { ifds::ModUser,                    BFCBO::NONE,         0 }, 
   { ifds::PolicyNum,                  BFCBO::NONE,         0 }, 
   { ifds::IssueDate,                  BFCBO::NONE,         0 }, 
   { ifds::AnnivMonth,                 BFCBO::NONE,         0 }, 
   { ifds::AnnivDay,                   BFCBO::NONE,         0 }, 
   { ifds::LastResetDate,              BFCBO::NONE,         0 }, 
   { ifds::ProvinceName,               BFCBO::NONE,         0 }, 
   { ifds::AgeBasedOn,                 BFCBO::NONE,         0 }, 
   { ifds::AgeBasedOnDesc,             BFCBO::NONE,         0 }, 
   { ifds::LegalMaturityDate,          BFCBO::NONE,         0 }, 
   { ifds::BailMaturityDate,           BFCBO::NONE,         0 }, 
   { ifds::CotAcctVer,                 BFCBO::NONE,         0 }, 
   { ifds::CotAcctRid,                 BFCBO::NONE,         0 }, 
   { ifds::ModDate,                    BFCBO::NONE,         0 }, 
   { ifds::PrevEffectiveDate,          BFCBO::NONE,         0 }, 

   //filters for substitutions values
   { ifds::StatusDeath,                BFCBO::NONE,         0 }, 
   { ifds::StatusActive,               BFCBO::NONE,         0 }, 
   { ifds::StatusActiveDeath,          BFCBO::NONE,         0 }, 
   { ifds::StatusBlank,                BFCBO::NONE,         0 }, 
   { ifds::PolicyYear,                 BFCBO::NONE,         0 }, 

   { ifds::ContractMaturityDate,       BFCBO::NONE,         0 }, 
   { ifds::CDStartDate,                BFCBO::NONE,         0 }, 
   { ifds::SegTransExist,              BFCBO::NONE,         0 }, 
   { ifds::RedAgeDate,                 BFCBO::NONE,         0 }, 

   { ifds::SuspectGuarType,            BFCBO::NONE,         0 }, 
   { ifds::RequiresGuarUnitAdjust,     BFCBO::NONE,         0 },
   { ifds::ContractEffectiveDate,      BFCBO::IMMEDIATE_VALIDATION,   0 },
   { ifds::ModPerm,                    BFCBO::NONE,         0 },  

   { ifds::GWOCotAnnivDate,            BFCBO::NONE,         0 }, 
   { ifds::SettleDate,                 BFCBO::NONE,         0 }, 
   
   { ifds::LWAAgeUsed,                 BFCBO::NONE,         0 },
   { ifds::LWARateApplied,             BFCBO::NONE,         0 },
   { ifds::LWAStartDate,               BFCBO::NONE,         0 },
   { ifds::ReqUnitAdj,                 BFCBO::NONE,         0 },
   { ifds::RefMatDate,                 BFCBO::NONE,         0 },
   { ifds::ContractMatBasedOn,         BFCBO::NONE,         0 },
   { ifds::ContractVer,                BFCBO::NONE,         0 },
   { ifds::UserDefinedMaturityDate,    BFCBO::NONE,         0 },
   { ifds::MaturityID,                 BFCBO::NONE,         0 },

   { ifds::ClsPerTerm,                 BFCBO::NONE,         0 },
   { ifds::LWAElectDate,               BFCBO::NONE,         0 },

   { ifds::IsDuringNASU,               BFCBO::NOT_ON_HOST,  0 },
   { ifds::ContractMaturDateCrossEdit, BFCBO::IMMEDIATE_VALIDATION,   0 },
   { ifds::EffectiveStopDate,          BFCBO::IMMEDIATE_VALIDATION,   0 },
   { ifds::FieldCrossEdit1,            BFCBO::NONE,   0 },
   { ifds::InsurAgeType,               BFCBO::NOT_ON_HOST,  0 },
   //{ ifds::NMCRContract,			   BFCBO::NONE,         0 },
   { ifds::GuaranteePayOption,		   BFCBO::NONE,         0 },
   { ifds::IsElected ,				   BFCBO::NONE,         0 },

};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

const BFFieldId _twinCompareFieldsList[] = 
{
   ifds::EffectiveDate,  ifds::StopDate,             ifds::ContractMatBasedOn, ifds::Status,         
   ifds::ClsPerTerm,     ifds::PolicyNum,
   ifds::ContractTerm,   
   ifds::ProvinceCanada, ifds::ContractMaturityDate, ifds::LegalMaturityDate,ifds::BailMaturityDate,
   ifds::CDStartDate,    ifds::RedAgeDate,           ifds::RefMatDate,       ifds::LWAStartDate,
   ifds::LWAAgeUsed,     ifds::LWARateApplied,       ifds::LWAElectDate,     ifds::ReqUnitAdj
};

static const int iNumTwinFieldsToCompare = sizeof(_twinCompareFieldsList)/sizeof(BFFieldId);


//****************************************************************************
ContractInfo::ContractInfo( BFAbstractCBO &parent ) :
MFCanBFCbo( parent ),
_pMgmtCoOptions(NULL),
_pTaxTypeRuleList(NULL),
_pMasterContractList(NULL),
_pMFAccount(NULL),
_pAccountHoldingList(NULL),
_bMultiContract( false )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );

   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );

   addCrossEdit(ifds::ContractEffectiveDate, ifds::ContractType);   
   addCrossEdit(ifds::ContractEffectiveDate, ifds::EffectiveDate);  

   addCrossEdit(ifds::ContractMaturDateCrossEdit, ifds::ContractMatBasedOn);   
   addCrossEdit(ifds::ContractMaturDateCrossEdit, ifds::ContractMaturityDate);
   
   addCrossEdit(ifds::EffectiveStopDate, ifds::EffectiveDate);
   addCrossEdit(ifds::EffectiveStopDate, ifds::StopDate);
   
   addCrossEdit(ifds::FieldCrossEdit1, ifds::ContractMaturityDate);
   addCrossEdit(ifds::FieldCrossEdit1, ifds::LegalMaturityDate);
   addCrossEdit(ifds::FieldCrossEdit1, ifds::ContractMatBasedOn);

   bDefaultValuesAlreadySet = false;
   _bMultiContract = getWorkSession().hasReadPermission( UAF::SEG_FUND_MULTI_CONTRACT );

   getWorkSession().getDateInHostFormat (_dstr12319999, DSTCWorkSession::DATE_TYPE::DAY12319999, BF::HOST);
   DString dstrGuaranteeCalcByRules;
   getWorkSession().getOption(ifds::GuaranteeCalcByRules, dstrGuaranteeCalcByRules, BF::HOST, false);
   _bGuaranteeCalcByRules = dstrGuaranteeCalcByRules.strip().upperCase() == I_("Y");


   _pList              = (ContractInfoList*)getParent();

   _pMgmtCoOptions     = _pList->getMgmtCoOptions();
   _pTaxTypeRuleList   = _pList->getTaxTypeRuleList();
   _pMFAccount         = _pList->getMFAccount();
   _pAccountHoldingList = _pList->getAccountHoldingList(); // for checking
   _dstrAcctNum         = _pList->getAcctNum();

}

//****************************************************************************
ContractInfo::~ContractInfo()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//****************************************************************************
SEVERITY ContractInfo::init( const BFData& data )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   attachDataObject( const_cast<BFData&>(data), false, true );

   getMasterContractList(_pMasterContractList, BF::HOST);

   if( _bMultiContract )
   {
      loadContractTypeSubstitutionList( BF::HOST ); 
   }

   loadAgeBasedOnSubstitutionList(BF::HOST);

   DString dstrEffectiveDate;

   getField ( ifds::EffectiveDate, dstrEffectiveDate, BF::HOST );
   setFieldNoValidate( ifds::PrevEffectiveDate, dstrEffectiveDate, BF::HOST, false, true, true, false );

   setFieldReadOnly( ifds::SuspectGuarType, BF::HOST, !getWorkSession().hasUpdatePermission( UAF::SEG_GUAR_ADJ_BAND ));
   setFieldNoValidate( ifds::UserDefinedMaturityDate, _dstr12319999, BF::HOST,false, true, false, false);   

   if(isNew())
     contractTypeRelatedChanges(BF::HOST);

   DString dstrIssueDate;
   getField ( ifds::IssueDate, dstrIssueDate, BF::HOST, false);
   dstrIssueDate.stripAll();
   if(dstrIssueDate != I_("") && dstrIssueDate != _dstr12319999)
   {
      setFieldReadOnly( ifds::ContractMatBasedOn, BF::HOST, true);
   }

   updateContractMatBasedOnSubst(BF::HOST);
   //initCMDBasedON(BF::HOST);

   defaultReadonlyFields(BF::HOST);

   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************
void ContractInfo::init2( ContractInfoList *pContractInfoList, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init2" ) );  

   getMasterContractList(_pMasterContractList, idDataGroup);

   DString dstrIssueDate;

   getField(ifds::IssueDate, dstrIssueDate, idDataGroup);
   if(!checkFieldStateFlag(ifds::ContractMatBasedOn, idDataGroup, BFCBO::STATE_FLAGS::READ_ONLY))
      setFieldReadOnly(ifds::ContractMatBasedOn, idDataGroup, dstrIssueDate != _dstr12319999);

   updateContractMatBasedOnSubst(BF::HOST);

}

//****************************************************************************
void ContractInfo::doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
{
 
   getMasterContractList(_pMasterContractList, idDataGroup);
   if( _bMultiContract )
   {
      loadContractTypeSubstitutionList( idDataGroup );
   }

   setFieldNoValidate( ifds::Status, I_("01"), idDataGroup, false);
   loadAgeBasedOnSubstitutionList(idDataGroup);

   DString dstrDateOfBirth = NULL_STRING;
   bool bGetDateOfBirth = getDofBirth( idDataGroup, dstrDateOfBirth );
   //bool bGetDateOfBirth = static_cast<ContractInfoList*>(getParent())->getDofBirth( idDataGroup, dstrDateOfBirth );
   if( bGetDateOfBirth )
   {
      SetDefaultValues( dstrDateOfBirth, idDataGroup ); 
   }
   DString curDate;
   _pMgmtCoOptions->getField(ifds::CurrBusDate,curDate,BF::HOST, false);
   setFieldNoValidate( ifds::PrevEffectiveDate, curDate, idDataGroup, false, true, true, false );

   setFieldNoValidate( ifds::StopDate, _dstr12319999, idDataGroup, false, true, true );   
//   setFieldNoValidate( ifds::UserMaturityDate, dstrStopDate, idDataGroup, false, true, true ); 

   // Set field to "None"
   setFieldNoValidate( ifds::SuspectGuarType,        I_( "00" ), idDataGroup, false, true, true );   
   //setFieldNoValidate( ifds::RequiresGuarUnitAdjust, I_( "N" ),  idDataGroup, false, true, true );  
   setFieldNoValidate( ifds::ReqUnitAdj, I_( "N" ),  idDataGroup, false, true, true );  

   // For a new contract, User Defined Maturity Date should be modifiable if Contract Master allows.
   // ModDate is used only to determine is an existing contract can be modified i.e. based on  
   // the existence of certain trades ohn the account
   setFieldNoValidate( ifds::ModPerm, I_( "Y" ), idDataGroup, false, true, true );
   setFieldReadOnly( ifds::SettleDate, idDataGroup, true );

   DString strShrNum;
   DString strResProvCode;

   _pMFAccount->getField( ifds::ShrNum, strShrNum, idDataGroup, false );

   Shareholder *pShareholder = NULL;
   getWorkSession ().getShareholder (idDataGroup, strShrNum, pShareholder);

   if(isNew())
   {
      pShareholder->getField (ifds::ResProvCode, strResProvCode, idDataGroup, false);
   }
   else
   {
      _pMFAccount->getField( ifds::PensionJuris, strResProvCode, idDataGroup, false);

      if(strResProvCode.strip().upperCase().empty())
      {
         pShareholder->getField (ifds::ResProvCode, strResProvCode, idDataGroup, false);
      }
   }
   setFieldNoValidate( ifds::ProvinceCanada, strResProvCode, idDataGroup, false);
   setFieldNoValidate( ifds::UserDefinedMaturityDate, _dstr12319999, idDataGroup, false, true, false, false);   

   updateContractMatBasedOnSubst(idDataGroup);
//   initCMDBasedON(idDataGroup);


   setFieldReadOnly( ifds::IssueDate,              idDataGroup, true );
   setFieldReadOnly( ifds::ContractMaturityDate,   idDataGroup, true);    
   setFieldReadOnly( ifds::BailMaturityDate,       idDataGroup, true);    
   setFieldReadOnly( ifds::RedAgeDate,             idDataGroup, true);    
   setFieldReadOnly( ifds::LWAElectDate,           idDataGroup, true);    
   setFieldReadOnly( ifds::LWAStartDate,           idDataGroup, true);
   setFieldReadOnly( ifds::LastResetDate,          idDataGroup, true);    
   setFieldReadOnly( ifds::LegalMaturityDate,      idDataGroup, true);
   setFieldReadOnly( ifds::CDStartDate,            idDataGroup, true);
   setFieldReadOnly( ifds::RefMatDate,             idDataGroup, true);
   setFieldReadOnly( ifds::GWOCotAnnivDate,        idDataGroup, true);
}

//*****************************************************************************
void ContractInfo::SetFieldProperties(const BFDataGroupId& idDataGroup, bool bReadOnly )
{
   DString strShouldAskForDofBirth;
   DString dstrStatus;

   if( _bMultiContract )
   {
      setFieldReadOnly( ifds::EffectiveDate, idDataGroup, false );
      setFieldReadOnly( ifds::StopDate, idDataGroup, false );

      // PET 2102 - If the contract is in "Settlement" status and user does not have permission, Settlement Date should 
      // be readonly
      getField ( ifds::Status, dstrStatus, BF::HOST );

      if ( !(getWorkSession().hasUpdatePermission (UAF::SETTLEMENT_PHASE_STATUS_CHANGE)) && 
         dstrStatus == CONTRACT_STATUS_SETTLEMENT && !isNew() ) 
      {
         setFieldReadOnly( ifds::Status,	BF::HOST , true );
      }
      else
      {
         setFieldReadOnly( ifds::Status,	BF::HOST , false );
      }

      setFieldReadOnly( ifds::ContractTerm, idDataGroup, !isNew() );
      setFieldReadOnly( ifds::ProvinceCanada, idDataGroup, !isNew() );
      setFieldReadOnly( ifds::ContractType, idDataGroup, !isNew() );

      // Initialized by both new and existing objects
      setFieldReadOnly( ifds::ContractMaturityDate, idDataGroup, true );
      setFieldReadOnly( ifds::LegalMaturityDate, idDataGroup, true );
      setFieldReadOnly( ifds::CDStartDate, idDataGroup, true );
      setFieldReadOnly( ifds::RedAgeDate, idDataGroup, true );
   }
}

//****************************************************************************
void ContractInfo::SetDefaultValues( DString &DofBirth, const BFDataGroupId& idDataGroup )
{
   // Get data from MFAccount
   DString dstrAcctGroup;
   _pMFAccount->getField(ifds::AcctGroup, dstrAcctGroup, idDataGroup);
   dstrAcctGroup.stripAll().stripLeading('0');

   if( !bDefaultValuesAlreadySet )
   {
      // Set default value for EffectiveDate
      DString date;
      _pMgmtCoOptions->getField(ifds::CurrBusDate, date, idDataGroup, false);
      setFieldNoValidate( ifds::EffectiveDate, date, idDataGroup, false, true, true);
      if( !_bMultiContract )
      {
         //setFieldNoValidate( ifds::IssueDate, date, idDataGroup, true, true );
         //potential bug fix, date should not be formatted since the getField above for CurrBusDate is unformatted.
         setFieldNoValidate( ifds::IssueDate, date, idDataGroup, false, true );
      }
      else
      {
         setFieldNoValidate( ifds::IssueDate, NULL_STRING, idDataGroup, true, true );
         setFieldNoValidate( ifds::LastResetDate, NULL_STRING, idDataGroup, false, true );
      }
      // Set default value for StopDate
      setFieldNoValidate( ifds::StopDate, _dstr12319999, idDataGroup, false, true, true );

      // Get Info from MarstContract and set them into ContractType and ContractTypeId
      DString dstrContractType;
      DString dstrContractTypeId;
      DString dstrGroupCode;
      
      BFAbstractCBO* pMasterContract = NULL;
      getMasterContract(pMasterContract, idDataGroup);
      if(pMasterContract)
      {
         pMasterContract->getField(ifds::ContractType,   dstrContractType, idDataGroup, true );
         pMasterContract->getField(ifds::ContractTypeId, dstrContractTypeId, idDataGroup, true );
      }


      // Set default value for PolicyNum
      setFieldNoValidate( ifds::PolicyNum, _dstrAcctNum, idDataGroup, true, true );

      // Set default value for AgeBasedOnDesc
      DString strAgeBasedOnFmt;
      getField(ifds::AgeBasedOn, strAgeBasedOnFmt, idDataGroup,true);
      setFieldNoValidate( ifds::AgeBasedOnDesc,strAgeBasedOnFmt, idDataGroup,true, true);

      // Set default value for ProvinceCanada
      setFieldNoValidate( ifds::ProvinceCanada, NULL_STRING, idDataGroup, true, true );

      // Set default value for IssueDate
      if( _bMultiContract )
      {
         setFieldNoValidate( ifds::ContractTypeId, NULL_STRING, idDataGroup, true, true );
         setFieldNoValidate( ifds::ContractType, NULL_STRING, idDataGroup, true, true );
         setFieldNoValidate( ifds::IssueDate, NULL_STRING, idDataGroup, false, true );
      }
      else
      {
         setFieldNoValidate( ifds::ContractType, dstrContractType, idDataGroup, true, true );
         setFieldNoValidate( ifds::ContractTypeId, dstrContractTypeId, idDataGroup, true, true );
         setLegalAge( idDataGroup );
      }
      // Set default value for LastResetDate
      setFieldNoValidate( ifds::LastResetDate, NULL_STRING, idDataGroup, false, true );
      // Set default value for AnnivMonth
      setFieldNoValidate( ifds::AnnivMonth, NULL_STRING, idDataGroup, true, true );
      // Set default value for AnnivDay
      setFieldNoValidate( ifds::AnnivDay, NULL_STRING, idDataGroup, true, true );
//      setFieldNoValidate( ifds::MaturityType, CRITICALAGE, idDataGroup, true, true );

      bDefaultValuesAlreadySet = true;
   }
}

//***************************************************************************************************
void ContractInfo::setLegalAge( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setLegalAge" ) );
   // Get data from MFAccount
   DString dstrTaxType;
   DString dstrAcctDesignation;
   _pMFAccount->getField(ifds::AcctDesignation, dstrAcctDesignation, idDataGroup);

   // Get BailOutAge# and CriticalAge#
   DString str;
   DString dstrBailOutAge;
   DString dstrCriticalAge;
   int iAcctDesignation = dstrAcctDesignation.stripAll().asInteger();

   CotLegalAge *pCotLegalAge = NULL;
   getCotLegalAge( pCotLegalAge, idDataGroup );
   if( pCotLegalAge )
   {
      if( iAcctDesignation == 1 )
      {
         pCotLegalAge->getField(ifds::BailOutAge1, dstrBailOutAge, idDataGroup, true );
         pCotLegalAge->getField(ifds::CriticalAge1, dstrCriticalAge, idDataGroup, true );
      }
      if( iAcctDesignation == 2 )
      {
         pCotLegalAge->getField(ifds::BailOutAge2, dstrBailOutAge, idDataGroup, true );
         pCotLegalAge->getField(ifds::CriticalAge2, dstrCriticalAge, idDataGroup, true );
      }
      if( iAcctDesignation == 3 )
      {
         pCotLegalAge->getField(ifds::BailOutAge3, dstrBailOutAge, idDataGroup, true );
         pCotLegalAge->getField(ifds::CriticalAge3, dstrCriticalAge, idDataGroup, true );
      }

      DString dstrLegalAgeCalcType;
      pCotLegalAge->getField( ifds::LegalAgeCalcType, dstrLegalAgeCalcType,idDataGroup, false );
      dstrLegalAgeCalcType.strip().upperCase();

      // Set default value for BailMaturityDate 
      DString dstrBailMaturityDate = NULL_STRING;
      DString DofBirth;
      int iBailOutAge = dstrBailOutAge.asInteger();
      bool bIsBailOutAge = true;

      if (dstrLegalAgeCalcType.asInteger() == 4)
      {
         DString strNumOfYrs, strRESPClassify;


         DString strBaseDate;
         if(_pMFAccount->isNew())
         {
            _pMFAccount->getField( ifds::EffectiveDate, strBaseDate, idDataGroup, false );
            // during NASU, assume default value of RESP Classify as '00'
            strRESPClassify = I_("00");
         }
         else
         {
            _pMFAccount->getField( ifds::InceptionDate, strBaseDate, idDataGroup, false );
            // non NASU, would be populate from RESPAccInfo(66)

            RESPInfo* respInfo = NULL;
            _pMFAccount->getRESPInfo(respInfo, idDataGroup);

            if(respInfo)
            {
               respInfo->getField(ifds::RESPClassify, strRESPClassify, idDataGroup, false);
            }
         }

         if(strRESPClassify == I_("00"))
         {
            pCotLegalAge->getField( ifds::NumOfYears, strNumOfYrs,idDataGroup, false );
         }
         else
         {
            pCotLegalAge->getField( ifds::AltNumOfYears, strNumOfYrs,idDataGroup, false );
         }

         strBaseDate.strip().upperCase();

         if(_bGuaranteeCalcByRules)
         {
            if( CalcBailOrLeaglDate(strBaseDate, strNumOfYrs.asInteger(), bIsBailOutAge, dstrBailMaturityDate) )
            {
               setFieldNoValidate( ifds::LegalMaturityDate, dstrBailMaturityDate, idDataGroup, false, true, true );
               setFieldNoValidate( ifds::BailMaturityDate, NULL_STRING, idDataGroup, false, true, true );
               _dstrLegalMaturityDate = dstrBailMaturityDate ;
            }
         }
         else
         {
            bIsBailOutAge = true;
            if( CalcBailOrLeaglDate(strBaseDate, dstrBailOutAge.asInteger(), bIsBailOutAge, dstrBailMaturityDate) )
            {
               DString dstrTaxType;
               _pMFAccount->getField(ifds::TaxType, dstrTaxType, idDataGroup, false);

               if( getWorkSession().isNonRegLike( dstrTaxType.strip().upperCase() ) )
               {
                  setFieldNoValidate( ifds::BailMaturityDate, NULL_STRING, idDataGroup, false, true, true );                  
               }
               else
               {
                  setFieldNoValidate( ifds::BailMaturityDate, dstrBailMaturityDate, idDataGroup, false, true, true );
               }
            }

            bIsBailOutAge = false;
            if( CalcBailOrLeaglDate(strBaseDate, strNumOfYrs.asInteger(), bIsBailOutAge, dstrBailMaturityDate) )
            {
               setFieldNoValidate( ifds::LegalMaturityDate, dstrBailMaturityDate, idDataGroup, false, true, true );
            }

            _dstrLegalMaturityDate = dstrBailMaturityDate ;
         }
      }
      else
      {
         bool bGetDateOfBirth = getDofBirth( idDataGroup, DofBirth );
         //bool bGetDateOfBirth = static_cast<ContractInfoList*>(getParent())->getDofBirth( idDataGroup, dstrDateOfBirth );
         if( bGetDateOfBirth )
         {
            //if( CalcBailOrLeaglDate(DofBirth, dstrCriticalAge.asInteger(), bIsBailOutAge, dstrBailMaturityDate) )
            //{

            if(_bGuaranteeCalcByRules)
            {
               if( CalcBailOrLeaglDate(DofBirth, dstrCriticalAge.asInteger(), bIsBailOutAge, dstrBailMaturityDate) )
               {
                  setFieldNoValidate( ifds::LegalMaturityDate, dstrBailMaturityDate, idDataGroup, false, true, true );
                  setFieldNoValidate( ifds::BailMaturityDate, NULL_STRING, idDataGroup, false, true, true );
                  _dstrLegalMaturityDate = dstrBailMaturityDate ;
               }
            }
            else
            {
               bIsBailOutAge = true;
               if( CalcBailOrLeaglDate(DofBirth, dstrBailOutAge.asInteger(), bIsBailOutAge, dstrBailMaturityDate) )
               {
                  DString dstrTaxType;
                  _pMFAccount->getField(ifds::TaxType, dstrTaxType, idDataGroup, false);

                  if( getWorkSession().isNonRegLike( dstrTaxType.strip().upperCase() ) )
                  {
                     setFieldNoValidate( ifds::BailMaturityDate, NULL_STRING, idDataGroup, false, true, true );                  
                  }
                  else
                  {
                     setFieldNoValidate( ifds::BailMaturityDate, dstrBailMaturityDate, idDataGroup, false, true, true );
                  }
               }

               bIsBailOutAge = false;
               if( CalcBailOrLeaglDate(DofBirth, dstrCriticalAge.asInteger(), bIsBailOutAge, dstrBailMaturityDate) )
               {
                  setFieldNoValidate( ifds::LegalMaturityDate, dstrBailMaturityDate, idDataGroup, false, true, true );
               }

               _dstrLegalMaturityDate = dstrBailMaturityDate ;
            }
            //}

            //// Get value for _dstrLegalMatutityDate which will be used for the ValidateUserMaturityDate()
            //int iLeagalAge = dstrCriticalAge.asInteger();
            //bIsBailOutAge = false;
            //DString dstrLegalMaturityDate = NULL_STRING;
            //if( CalcBailOrLeaglDate(DofBirth, iLeagalAge, bIsBailOutAge, idDataGroup, dstrLegalMaturityDate) )
            //{
            //   // Set default value for LegalMaturityDate 
            //   setFieldNoValidate( ifds::LegalMaturityDate, dstrLegalMaturityDate, idDataGroup, false, true, true );
            //   _dstrLegalMaturityDate = dstrLegalMaturityDate ;
            //}
         }
      }
   }
}

//***************************************************************************************************
SEVERITY ContractInfo::initStatusSubst( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initStatusSubst" ) );

   DString dstrAcctStaus;
   DString dstrAcctBalance = NULL_STRING;
   DString dstrSetUnits = NULL_STRING;
   DString dstrUnsetUnits = NULL_STRING;
   _pMFAccount->getField(ifds::AcctStatus, dstrAcctStaus, idDataGroup);
   _pMFAccount->getField(ifds::AccountBalance, dstrAcctBalance, idDataGroup);
   if( dstrAcctBalance.asInteger() <= 0 )
   {
      BFObjIter iterAcctHold ( *_pAccountHoldingList, idDataGroup );
      iterAcctHold.begin();
      double dec_SettledUnits;
      double dec_UnsettledUnits;
      while( !iterAcctHold.end() )
      {
         iterAcctHold.getObject( )->getField(ifds::SettledUnits, dstrSetUnits, idDataGroup, false );
         dec_SettledUnits = DSTCommonFunctions::convertToDouble( dstrSetUnits ) ;

         iterAcctHold.getObject( )->getField(ifds::UnsettledUnits, dstrUnsetUnits, idDataGroup, false );
         dec_UnsettledUnits = DSTCommonFunctions::convertToDouble( dstrUnsetUnits ) ;

         if( dec_SettledUnits > 0 || dec_UnsettledUnits > 0 )
            break;
         else
            ++iterAcctHold;
      }
   }

   dstrAcctStaus.stripAll();
   int iAccountBalance = dstrAcctBalance.asInteger();
   int iSetUnits = dstrSetUnits.asInteger();
   int iUnsetUnits = dstrUnsetUnits.asInteger();
   if( (dstrAcctStaus != ACCT_STATUS_ACTIVE ) && 
       ( dstrAcctStaus  != ACCT_STATUS_DEATH )  && 
       ( dstrAcctStaus  != ACCT_STATUS_DEATHTRANSFER ) )
   {
      if( (iAccountBalance > 0) || (iSetUnits > 0) || (iUnsetUnits > 0) )
         setFieldSubstituteValues( ifds::Status, idDataGroup, ifds::StatusActive );
      else
         setFieldSubstituteValues( ifds::Status, idDataGroup, ifds::StatusActiveDeath );
   }
   if( ( dstrAcctStaus == ACCT_STATUS_DEATH ) || ( dstrAcctStaus == ACCT_STATUS_DEATHTRANSFER ) )
   {
      if( (iAccountBalance > 0) || (iSetUnits > 0) || (iUnsetUnits > 0) )
      {
         setFieldSubstituteValues( ifds::Status, idDataGroup, ifds::StatusBlank );
         SetFieldProperties( idDataGroup, false );
      }
      else
         setFieldSubstituteValues( ifds::Status, idDataGroup, ifds::StatusDeath );
   }

   // Initialized by both new and existing objects
   setFieldReadOnly( ifds::ContractMaturityDate, idDataGroup, true );
   setFieldReadOnly( ifds::LegalMaturityDate, idDataGroup, true );
   setFieldReadOnly( ifds::CDStartDate, idDataGroup, true );
   setFieldReadOnly( ifds::RedAgeDate, idDataGroup, true );

   return(GETCURRENTHIGHESTSEVERITY());
}

//***************************************************************************************************
bool ContractInfo::CalcBailOrLeaglDate(DString& dstrDofBirth, 
                                       int iInputAge,
                                       bool bIsBailOutAge,
                                       DString& dstrOutDate)
{
   int yr1;
   DString date1;
   DString years;
   DString month;
   DString day;
   bool flgGoodDate = false;

   // look in the registry for the date format mask
   // birth date and current date should be in host format
   DString dstrConfiguration( I_( "HostMasks" ) );
   DString dstrKey( I_("D") );

   dstrOutDate = GetConfigValueAsString( I_( "LocaleFormats" ), 
                                         dstrConfiguration,
                                         dstrKey );

   if( dstrDofBirth == NULL_STRING )
   {
      flgGoodDate = false;
      return(false);
   }

   int month_pos = dstrOutDate.find( I_( "MM" ) );
   int day_pos   = dstrOutDate.find( I_( "dd" ) );
   int year_pos  = dstrOutDate.find( I_( "yyyy" ) );
   if( DString::npos != year_pos )
   {
      date1.assign( dstrDofBirth, year_pos, 4);
      yr1 = convertToULong( date1 );

      month.assign( dstrDofBirth, month_pos, 2);
      day.assign( dstrDofBirth, day_pos, 2);

      if( yr1 == 0 )
         flgGoodDate = false;
      else
      {
         yr1 = yr1 + iInputAge;
         convertIntToString( yr1, years );
         dstrOutDate.replace(dstrOutDate.find(I_("yyyy")), 4, years);
         if( bIsBailOutAge )
         {
            dstrOutDate.replace(dstrOutDate.find(I_("MM")), 2, I_("12"));
            dstrOutDate.replace(dstrOutDate.find(I_("dd")), 2, I_("31"));
         }
         else
         {
            // check leap year
            if( !( BFDate::isLeapYear( yr1 ) ) && ( month == I_( "02" )) && ( day == I_( "29" )) )
            {
               month = I_( "03" );
               day = I_( "01" );
            }
            dstrOutDate.replace(dstrOutDate.find(I_("MM")), 2, month);
            dstrOutDate.replace(dstrOutDate.find(I_("dd")), 2, day);

         }

         flgGoodDate = true;
      }
   }

   else
      flgGoodDate = false;
   return(flgGoodDate);
}

//********************************************************************************************
SEVERITY ContractInfo::doValidateField( const BFFieldId& idField,
                                        const DString& strValue,
                                        const BFDataGroupId& idDataGroup )

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );

   if( idField == ifds::LegalMaturityDate )
   {
      ValidateLegalMaturityDate( strValue, idDataGroup );
   }
   else if( idField == ifds::EffectiveDate )
   {
      ValidateEffectiveDate( strValue, idDataGroup );
   }
   else if( idField == ifds::StopDate )
   {
      ValidateStopDate( strValue, idDataGroup );
   }
   //else if( idField == ifds::EffectiveStopDate )
   //{
   //   DString effectiveDate, stopDate;

   //   getField (ifds::StopDate, stopDate, idDataGroup, false);
   //   getField (ifds::EffectiveDate, effectiveDate, idDataGroup, false);

   //   if (DSTCommonFunctions::CompareDates (stopDate, effectiveDate) == DSTCommonFunctions::FIRST_EARLIER)
   //   {
   //      ADDCONDITIONFROMFILE (CND::ERR_EFFECTIVEDATE_MUST_BE_EARLIER_STOPDATE);
   //   }
   //}
   else if( idField == ifds::Status )
   {
      ValidateStatus( strValue, idDataGroup );
   }
   else if( idField == ifds::ContractTerm )
   {
      ValidateContractTerm( strValue, idDataGroup );
   }
   else if( idField == ifds::ContractType )
   {
      ValidateContractType( strValue, idDataGroup );
   }
   else if( idField == ifds::ProvinceCanada )
   {
      ValidateProvince( strValue, idDataGroup );
   }
   else if( idField == ifds::ContractEffectiveDate )
   {
      ValidateContractEffectiveDate( idDataGroup );

   }
   //else if( idField == ifds::ContractMaturityDate )
   //{
   //   DString dstrContMatDateBasedOn;
   //   getField(ifds::ContractMatBasedOn, dstrContMatDateBasedOn, idDataGroup,false);
   //   dstrContMatDateBasedOn.strip().upperCase();

   //   if ( dstrContMatDateBasedOn ==  CMD_BASED_ON_USERDEFINED)
   //   {
   //      DString dstrContractMaturityDate(strValue);
   //      dstrContractMaturityDate.strip();

   //      if ( dstrContractMaturityDate.empty() )
   //      {
   //         getErrMsg( IFASTERR::USER_DEFINED_MATURITY_DATE_CANNOT_BE_BLANK, 
   //                    CND::ERR_USER_DEFINED_MATURITY_DATE_CANNOT_BE_BLANK, 
   //                    CND::WARN_USER_DEFINED_MATURITY_DATE_CANNOT_BE_BLANK, 
   //                    idDataGroup );
   //      }
   //   }
   //}
   else if( idField == ifds::ContractMaturDateCrossEdit )
   {
      DString dstrContMatDateBasedOn;
      DString dstrContractMaturityDate;

      getField(ifds::ContractMatBasedOn, dstrContMatDateBasedOn, idDataGroup,false);
      getField(ifds::ContractMaturityDate, dstrContractMaturityDate, idDataGroup,false);
      dstrContMatDateBasedOn.strip().upperCase();
      dstrContractMaturityDate.strip();

      if ( dstrContMatDateBasedOn == CMD_BASED_ON_USERDEFINED || dstrContMatDateBasedOn == CMD_BASED_ON_USERDEFINED_TRANSFER)
      {
         ValidateUserDefinedMaturityDateBetweenMinMaxAge(idDataGroup);
         ValidateUserDefinedMaturityDateGreaterThanMinTerm(idDataGroup);

         if ( dstrContractMaturityDate.empty() || dstrContractMaturityDate == _dstr12319999)
         {
            getErrMsg( IFASTERR::USER_DEFINED_MATURITY_DATE_CANNOT_BE_BLANK, 
                       CND::ERR_USER_DEFINED_MATURITY_DATE_CANNOT_BE_BLANK, 
                       CND::WARN_USER_DEFINED_MATURITY_DATE_CANNOT_BE_BLANK, 
                       idDataGroup );
         }
      }
   }
   else if( idField == ifds::FieldCrossEdit1 )
   {
      ValidateUserDefinedMaturityDateLessThanMaturityDate(idDataGroup);

      DString strContractMaturityDate, strLegalMaturityDate, strCMDBasedON;

      getField (ifds::ContractMaturityDate, strContractMaturityDate, idDataGroup, false);
      getField (ifds::LegalMaturityDate, strLegalMaturityDate, idDataGroup, false);
      getField (ifds::ContractMatBasedOn, strCMDBasedON, idDataGroup, false);
      strContractMaturityDate.strip();
      strLegalMaturityDate.strip();
      strCMDBasedON.strip().upperCase();

      if( !strLegalMaturityDate.empty() && !strContractMaturityDate.empty() && !strCMDBasedON.empty())
      {
         if (DSTCommonFunctions::CompareDates (strLegalMaturityDate, strContractMaturityDate) == DSTCommonFunctions::FIRST_EARLIER)
         {
            ADDCONDITIONFROMFILE (CND::ERR_CMD_AFTER_LCMD);
         }
      }   
   }
/*
   else

      if( idField == ifds::MaturityType )
   {
      if( strValue == I_("02") )
      {
         setFieldReadOnly( ifds::UserMaturityDate, idDataGroup, false );

//CP20030319         long lFlag;
//CP20030319         lFlag = getFieldStateFlags(ifds::UserMaturityDate, idDataGroup);
//CP20030319         setFieldStateFlags(ifds::UserMaturityDate, idDataGroup, lFlag | BFCBO::STATE_FLAGS::REQUIRED);
         setFieldRequired( ifds::UserMaturityDate, idDataGroup, true );
      }
      else
         setFieldReadOnly( ifds::UserMaturityDate, idDataGroup, true );
      ValidateMaturityType( strValue );
   }
   else

      if( idField == ifds::UserMaturityDate )
   {
      DString str;
      getField(ifds::MaturityType, str, idDataGroup);
      if( str.stripAll() == I_("02") )
      {
         if( strValue != NULL_STRING )
            ValidateUserMaturityDate( strValue, idDataGroup );
         else
            ADDCONDITIONFROMFILE( CND::ERR_USER_MATURITY_DATE_EMPTY);
      }
   }
*/
   return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************************
SEVERITY ContractInfo::ValidateContractType( const DString& valContractType, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateContractType" ) );
   if( _bMultiContract )
   {
      DString dstrContractType;
      DString dstrStatus;
      ContractInfoList *pContractInfoList = static_cast<ContractInfoList*>(getParent());

      BFObjIter iterContractInfoList( *pContractInfoList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
      iterContractInfoList.begin();
	  //couldn't check the current object for duplicate
      while( !iterContractInfoList.end() && iterContractInfoList.getObject() != this )
      {
         iterContractInfoList.getObject()->getField(ifds::Status, dstrStatus, idDataGroup);
         iterContractInfoList.getObject()->getField(ifds::ContractType, dstrContractType, idDataGroup);
         dstrContractType.strip().upperCase();
         if( valContractType == dstrContractType && dstrStatus.strip() == I_("01") )
         {
            ADDCONDITIONFROMFILE( CND::ERR_DUPLICATE_RECORD );
            return(GETCURRENTHIGHESTSEVERITY());
         }

         ++iterContractInfoList;
      } 
   }
	
   return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************************
bool ContractInfo::ValidateLegalMaturityDate( const DString& LegalMaturityDate, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateLegalMaturityDate" ) );

   DString curDate;
   _pMgmtCoOptions->getField(ifds::CurrBusDate,curDate,idDataGroup, false);
   if( DSTCommonFunctions::CompareDates( LegalMaturityDate, curDate ) 
       == DSTCommonFunctions::FIRST_EARLIER )
   {
      ADDCONDITIONFROMFILE( CND::ERR_LEGAL_MATURITY_DATE_EARLY_THAN_TODAY );
      return(false);
   }
   return(true);
}

//********************************************************************************************
SEVERITY ContractInfo::ValidateEffectiveDate( const DString& EffectiveDateContract, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateEffectiveDate" ) );
   DString EffectiveDateAcct;

   _pMFAccount->getField( ifds::FirstEffective, EffectiveDateAcct, idDataGroup );

   if( EffectiveDateAcct != NULL_STRING )
   {
      if( DSTCommonFunctions::CompareDates( EffectiveDateContract, EffectiveDateAcct ) 
          == DSTCommonFunctions::FIRST_EARLIER )
      {
         ADDCONDITIONFROMFILE( CND::ERR_EFFECTIVE_DATE_CONTRACT_EARLIER_THAN_EFFECTIVE_DATE_MFACCOUNT );
      }
   }

   DString dstrStopDate;
   getField(ifds::StopDate, dstrStopDate, idDataGroup);
   if( DSTCommonFunctions::CompareDates( dstrStopDate, EffectiveDateContract ) 
       == DSTCommonFunctions::FIRST_EARLIER )
   {
      ADDCONDITIONFROMFILE( CND::ERR_EFFECTIVEDATE_MUST_BE_EARLIER_STOPDATE);
   }

   DString dstrIssueDate;
   getField(ifds::IssueDate, dstrIssueDate, idDataGroup);
   if( DSTCommonFunctions::CompareDates( dstrIssueDate, EffectiveDateContract ) 
       == DSTCommonFunctions::FIRST_EARLIER )
   {
      //  Effective Date must precede Issue Date.
      ADDCONDITIONFROMFILE( CND::ERR_CONTRACT_EFF_DATE_AFTER_ISSUE_DATE );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************************
SEVERITY ContractInfo::ValidateStopDate( const DString& StopDate, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateStopDate" ) );
   DString dstrEffectiveDate;

   getField(ifds::EffectiveDate, dstrEffectiveDate, idDataGroup);

   if( DSTCommonFunctions::CompareDates( StopDate, dstrEffectiveDate ) 
       == DSTCommonFunctions::FIRST_EARLIER )
   {
      ADDCONDITIONFROMFILE( CND::ERR_STOP_DATE_EARLIER_EFFDATE );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************************
SEVERITY ContractInfo::ValidateStatus( const DString& Status, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateStatus" ) );
   if( Status == NULL_STRING )
      ADDCONDITIONFROMFILE( CND::ERR_STATUS_IS_BLANK );

   DString dstrStatus(Status);
   dstrStatus.strip().upperCase();
   if( dstrStatus == CONTRACT_STATUS_PENDINGDEATH )
   {
      DString dstrPendingTrade;
      _pMFAccount->getField(ifds::PendingTrade, dstrPendingTrade, idDataGroup, false);
      if( dstrPendingTrade.stripAll().upperCase() == I_( "Y" ) )
      {
         ADDCONDITIONFROMFILE( CND::ERR_STATUS_CHANGED );
      }
   }

   if( dstrStatus.stripAll() == CONTRACT_STATUS_DEATH )
   {
      DString dstrAcctBalance;
      DString dstrAcctStatus;

      _pMFAccount->getField(ifds::AccountBalance, dstrAcctBalance, idDataGroup, false);
      dstrAcctBalance.strip().upperCase();
      if( dstrAcctBalance.asInteger() != 0 )
      {
         ADDCONDITIONFROMFILE( CND::ERR_CHANGE_STATUS_TO_DEATH );
      }

      _pMFAccount->getField(ifds::AcctStatus,dstrAcctStatus, idDataGroup, false );
      dstrAcctStatus.strip().upperCase();
      if( dstrAcctStatus != ACCT_STATUS_DEATH && 
          dstrAcctStatus != ACCT_STATUS_DEATHTRANSFER)
      {
         ADDCONDITIONFROMFILE( CND::ERR_ACCT_STATUS_DEATH_OR_DEATH_TRANSFER );
      }

      return(GETCURRENTHIGHESTSEVERITY());
   }

   if ( dstrStatus.stripAll() == CONTRACT_STATUS_ACTIVE || 
        dstrStatus.stripAll() == CONTRACT_STATUS_PENDINGDEATH )
   {
      DString dstrAcctStatus;
      _pMFAccount->getField(ifds::AcctStatus,dstrAcctStatus, idDataGroup, false );
      dstrAcctStatus.strip().upperCase();
      if( dstrAcctStatus == ACCT_STATUS_DEATH || 
          dstrAcctStatus == ACCT_STATUS_DEATHTRANSFER)
      {
         ADDCONDITIONFROMFILE( CND::ERR_STATUS_NOT_ALLOWED_FOR_ACCT_DEATH_OR_DEATH_TRANSFER );
      }

      return(GETCURRENTHIGHESTSEVERITY());
   }

   DString dstrStatusHost;
   getField(ifds::Status, dstrStatusHost, BF::HOST, false );
   dstrStatusHost.strip().upperCase();
   if( dstrStatusHost!= CONTRACT_STATUS_SETTLEMENT && dstrStatus.stripAll() == CONTRACT_STATUS_SETTLEMENT )
   {
      ADDCONDITIONFROMFILE( CND::ERR_ACCT_CONT_SETTL_STATUS_CANNOT_BE_SELECTED );
      return(GETCURRENTHIGHESTSEVERITY());     
   }

   if(dstrStatusHost == CONTRACT_STATUS_SETTLEMENT && dstrStatus.strip() != CONTRACT_STATUS_ACTIVE )
   {
      ADDCONDITIONFROMFILE( CND::ERR_ACCT_CONT_NON_ACTIVE_STATUS_SELECTED );
      return(GETCURRENTHIGHESTSEVERITY());  
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************************
SEVERITY ContractInfo::ValidateContractTerm( const DString& ContractTerm, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateContractTerm" ) );

   DString dstr1;
   DString dstr2;
   DString dstrMinTerm;
   DString dstrMaxTerm;
   DString dstrContractTerm;

   getField(ifds::ContractType, dstr1, idDataGroup, false);

   BFAbstractCBO* pMasterContract = NULL;
   getMasterContract(pMasterContract, idDataGroup);
   if(pMasterContract)
   {
      pMasterContract->getField(ifds::MinTerm, dstrMinTerm, idDataGroup );
      pMasterContract->getField(ifds::MaxTerm, dstrMaxTerm, idDataGroup );
   }

   if( (ContractTerm.asInteger() < dstrMinTerm.asInteger()) ||
       (ContractTerm.asInteger() > dstrMaxTerm.asInteger()) )
   {
      ADDCONDITIONFROMFILE( CND::ERR_INVALID_CONTRACT_TERM );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************************
SEVERITY ContractInfo::ValidateProvince( const DString& Province, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateProvince" ) );

   DString dstrCreateRep;
   _pMFAccount->getField(ifds::CreateRep,dstrCreateRep,idDataGroup,false);
   dstrCreateRep.strip();
   if( _pMFAccount->isNew() && dstrCreateRep == I_( "Y" ) ) return(GETCURRENTHIGHESTSEVERITY());

   if( Province != NULL_STRING )
   {
      SEVERITY sevRtn = SEVERE_ERROR;
      AgentList *pAgentList;

      //checks for the validity of the agent code. by making a view call, and raising a condition
      //we do not want to make the view call when the slslrep code is NULL, because the view will
      //return us all the agents for this broker and branch
      sevRtn = getAgentList( idDataGroup, pAgentList );
      DString   dstrSegLicense;
      if( sevRtn <= WARNING )
      {
         BFObjIter iterAgentList( *pAgentList, idDataGroup );
         if( !iterAgentList.end() )
         {
            iterAgentList.getObject()->getField( ifds::SegLicenseProvList, dstrSegLicense, idDataGroup );
         }
      }
      else
      {
         ADDCONDITIONFROMFILE( CND::ERR_INACTIVE_SALES_REP );
         return(GETCURRENTHIGHESTSEVERITY());
      }

      DString dstrProvince = Province;
      if( dstrSegLicense.find( dstrProvince.strip() ) == -1 )
         ADDCONDITIONFROMFILE( CND::WARN_INVALID_PROVINCE );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************************
SEVERITY ContractInfo::ValidateContractEffectiveDate( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateContractEffectiveDate" ) );

   
   ValidateUserDefinedMaturityDateGreaterThanMinTerm(idDataGroup);

   DString dstrContractType;
   DString dstrEffectiveDate;

   if (_dstrAcctNum == NULL_STRING)
   {
      getParent()->getParent()->getField( ifds::AccountNum, _dstrAcctNum, idDataGroup );
   }

   getField( ifds::ContractType, dstrContractType, idDataGroup);
   getField( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup);

   if( (!_dstrAcctNum.empty()) && (!dstrContractType.empty()) && (!dstrEffectiveDate.empty()) )
   {
      SeqFundValidation *pSeqFundValidation = NULL;

      DString dstrKey = I_("SeqFundValidation_AccountNum=") + _dstrAcctNum 
                      + I_(";ContractType =")               + dstrContractType 
                      + I_(";EffectiveDate=")               + dstrEffectiveDate;

      pSeqFundValidation = 
         dynamic_cast<SeqFundValidation *> (BFCBO::getObject (dstrKey, idDataGroup));
      if( !pSeqFundValidation )
      {
         pSeqFundValidation = new SeqFundValidation ( *this );
         if( pSeqFundValidation->init354( _dstrAcctNum, 
                                          dstrContractType, 
                                          dstrEffectiveDate ) <= WARNING )
         {
            setObject( pSeqFundValidation, dstrKey, OBJ_ACTIVITY_NONE, idDataGroup ); 
         }
         else
         {
            delete pSeqFundValidation;
            pSeqFundValidation = NULL;
         }
      }

      if( pSeqFundValidation )
      {
         pSeqFundValidation->SegFundValidationWarnings( idDataGroup );
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());

}

//********************************************************************************************
void ContractInfo::ModelOffer(ContractInfo *Model, const BFDataGroupId& idDataGroup)
{
   BFData *tmp = new BFData(ifds::DSTC0105_VWRepeat_Record);

   BFDataFieldIter dIter( *tmp );
   DString str;
   for( ;dIter; ++dIter )
   {
      BFDataField& idField = dIter();
      Model->getField( idField.getId(), str, idDataGroup );
      setField(idField.getId(), str, idDataGroup);
   };

   delete tmp;

   // send original record's EffectiveDate to new record's PrevEffectiveDate in order to view
   // can use it as a process key

   getField( ifds::EffectiveDate, str, idDataGroup );
   setFieldNoValidate( ifds::PrevEffectiveDate, str, idDataGroup, false, true, true, false );   

   // set new record's StopDate to be 31/12/9999. User can change it in the GUI
   setFieldNoValidate(ifds::StopDate, _dstr12319999, idDataGroup, false, true, true);

}

//******************************************************************************
SEVERITY ContractInfo::loadProvinceSubstitutionList( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "loadProvinceSubstitutionList" ) );

   DString dstrCreateRep;
   _pMFAccount->getField(ifds::CreateRep,dstrCreateRep,idDataGroup,false);
   dstrCreateRep.strip();
   if( _pMFAccount->isNew() && dstrCreateRep == I_( "Y" ) ) 
   {
      return(GETCURRENTHIGHESTSEVERITY());
   }

   DString strSegLicense;
   bool bLoadedSubstList;

   AgentList *pAgentList;
   SEVERITY sevRtn = getAgentList( idDataGroup, pAgentList );
   if( pAgentList != NULL && sevRtn <= WARNING )
   {
      BFObjIter iterAgentList( *pAgentList, idDataGroup );
      iterAgentList.begin();
      if( !iterAgentList.end() )
      {
         iterAgentList.getObject()->getField( ifds::SegLicenseProvList, strSegLicense, idDataGroup );
      }

      if( strSegLicense.empty() )
      {
         bLoadedSubstList = false;
      }
      else
      {
         BFCBO *pBFCBO = dynamic_cast<BFCBO *> (this);
         bLoadedSubstList = loadSubstitutionList( ifds::ProvinceCanada, 
                                                  idDataGroup, 
                                                  strSegLicense );
      }

      if( bLoadedSubstList == false )
      {
         setFieldAllSubstituteValues( ifds::ProvinceCanada, idDataGroup, BLANK_SUBSTITUTION );
         setFieldNoValidate( ifds::ProvinceCanada, NULL_STRING, idDataGroup );
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY ContractInfo::getAgentList( const BFDataGroupId& idDataGroup, AgentList *&pAgentList )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getAgentList" ) );

   pAgentList = NULL;
   DString strBrokerCode;
   DString strBranchCode;
   DString strSlsrep;

   _pMFAccount->getField( ifds::BrokerCode, strBrokerCode, idDataGroup );
   _pMFAccount->getField( ifds::BranchCode, strBranchCode, idDataGroup );
   _pMFAccount->getField( ifds::Slsrep,     strSlsrep,     idDataGroup );

   //check cbobase to see if we've already built it
   //if not built, create and store with base
   DString strTag = I_( "getAgentList" );
   pAgentList = dynamic_cast<AgentList *>( BFCBO::getObject( strTag, idDataGroup ) );
   if( !pAgentList )
   {
      pAgentList = new AgentList( *this );
      if( pAgentList->init( strBrokerCode, strBranchCode, strSlsrep ) <= WARNING )
      {
         setObject( pAgentList, strTag, OBJ_ACTIVITY_NONE, idDataGroup ); 
      }
      else
      {
         delete pAgentList;
         pAgentList = NULL;
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}
//****************************************************************************
SEVERITY ContractInfo::getMasterMinTermAndMinMaxAge( DString& dstrMinTerm, DString& dstrMinAge, 
                                                    DString& dstrMaxAge, const BFDataGroupId& idDataGroup )
{
   MAKEFRAME2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMasterMinTermAndMinMaxAge" ) );

   BFAbstractCBO* pMasterContract = NULL;
   getMasterContract(pMasterContract, idDataGroup);
   if(pMasterContract)
   {
      pMasterContract->getField(ifds::MinAge,  dstrMinAge,  idDataGroup );
      pMasterContract->getField(ifds::MaxAge,  dstrMaxAge,  idDataGroup );
      pMasterContract->getField(ifds::MinTerm, dstrMinTerm, idDataGroup );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}



//****************************************************************************
SEVERITY ContractInfo::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAME2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );
   SEVERITY  sevRtn = NO_CONDITION;

   if( _bMultiContract )
   {
      if( idField == ifds::ContractType  )
      {
         contractTypeRelatedChanges(idDataGroup);

//         initCMDBasedON(idDataGroup);
         updateContractMatBasedOnSubst(idDataGroup);
      }
      else if( idField == ifds::Status)
      {
         DString dstrStatusHOST, dstrStatus;
         getField( ifds::Status, dstrStatusHOST, BF::HOST );
         getField( ifds::Status, dstrStatus, idDataGroup );
         if ( dstrStatusHOST == CONTRACT_STATUS_SETTLEMENT && dstrStatus == CONTRACT_STATUS_ACTIVE)
         {
            setFieldNoValidate(ifds::SettleDate, NULL_STRING, idDataGroup, false, true, true, true );
         }
      }
/*
      else if( idField == ifds::MaturityType )
      {
         DString dstrMaturityType;
         getField( ifds::MaturityType, dstrMaturityType, idDataGroup );
         if( dstrMaturityType.strip() == CRITICALAGE )
            setFieldReadOnly( ifds::UserMaturityDate, idDataGroup, true );
         else
            setFieldReadOnly( ifds::UserMaturityDate, idDataGroup, false );
      }
*/
      else if ( idField == ifds::ContractMatBasedOn )
      {
         DString strContractMatBasedOn;

         getField(ifds::ContractMatBasedOn, strContractMatBasedOn, idDataGroup, false);
         strContractMatBasedOn.strip().upperCase();

//         setFieldReadOnly(ifds::ContractMaturityDate, idDataGroup, strContractMatBasedOn != CMD_BASED_ON_USERDEFINED);
         setFieldValid(ifds::ContractMaturityDate, idDataGroup, strContractMatBasedOn != CMD_BASED_ON_USERDEFINED && strContractMatBasedOn != CMD_BASED_ON_USERDEFINED_TRANSFER);

         if( isNew())
         {
            setFieldNoValidate(ifds::AgeBasedOn,I_("01"), idDataGroup,false);
            setFieldValid(ifds::AgeBasedOn, idDataGroup, true);
         }

         DString strContractType, dstrMoneyInExist;
         DString strMinTerm;
         DString strMinAge;
         DString strMaxTerm;

         getField(ifds::ContractType, strContractType, idDataGroup, false);
         strContractType.strip().upperCase();

         getMasterMinTermAndMinMaxAge( strMinTerm, strMinAge, strMaxTerm, idDataGroup );

         if (_pMFAccount)
            _pMFAccount->getField(ifds::MoneyInExist, dstrMoneyInExist, idDataGroup);

         if(strContractMatBasedOn == CMD_BASED_ON_MAX_AGE)
         {
            DString dstrDofBirth;
            DString dstrNewDate;
            getDofBirth(idDataGroup,dstrDofBirth);

            if(!dstrDofBirth.empty() && dstrDofBirth != _dstr12319999 && (dstrMoneyInExist == NO || isNew()))
            {
               addYearToDate(dstrDofBirth,dstrNewDate,strMaxTerm.asInteger());
               setFieldNoValidate(ifds::ContractMaturityDate,dstrNewDate, idDataGroup,false);
            }
         }
         else if(strContractMatBasedOn == CMD_BASED_ON_MIN_TERM)
         {
            DString dstrCurrbusDate;
            DString dstrNewDate;
            DString dstrEffectiveDate;

            getField(ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false);

            if(!dstrEffectiveDate.empty() && dstrEffectiveDate != _dstr12319999 && (dstrMoneyInExist == NO || isNew()))
            {
               addYearToDate(dstrEffectiveDate,dstrNewDate,strMinTerm.asInteger());
               setFieldNoValidate(ifds::ContractMaturityDate, dstrNewDate, idDataGroup,false);
            }
         }
         else if(strContractMatBasedOn == CMD_BASED_ON_LCMD)
         {
            DString dstrLegalMaturityDate;
            DString dstrNewDate;
            setLegalAge(idDataGroup);
            getField(ifds::LegalMaturityDate, dstrLegalMaturityDate, idDataGroup, false);

            if(!dstrLegalMaturityDate.empty() && dstrLegalMaturityDate != _dstr12319999 && (dstrMoneyInExist == NO || isNew()))
            {
               setFieldNoValidate(ifds::ContractMaturityDate,dstrLegalMaturityDate, idDataGroup,false);
            }
         }
         else if (strContractMatBasedOn == CMD_BASED_ON_USERDEFINED || strContractMatBasedOn == CMD_BASED_ON_USERDEFINED_TRANSFER)
         {
            DString strUserDefinedCMD;
            getField(ifds::UserDefinedMaturityDate,strUserDefinedCMD,idDataGroup,false);

            if (!strUserDefinedCMD.empty())
            {
                if (dstrMoneyInExist == NO || isNew())
                    setFieldNoValidate(ifds::ContractMaturityDate,strUserDefinedCMD, idDataGroup,false);
            }
            else
            {
               contractMaturityDateRelatedChanges(idDataGroup);
            }
         }
         else // blank
         {
            DString dstrAcctGroup;
            DString dstrContractType;
            DString dstrMstrContMatDateBasedOn;

            _pMFAccount->getField(ifds::AcctGroup, dstrAcctGroup, idDataGroup);

            getField( ifds::ContractType, dstrContractType, idDataGroup, false );
            dstrContractType.strip().upperCase();


            if(_pMasterContractList)
            {
               _pMasterContractList->getFieldByGroupAndContractType ( dstrAcctGroup, 
                                                                      dstrContractType, 
                                                                      ifds::ContMatDateBasedOn, 
                                                                      dstrMstrContMatDateBasedOn, 
                                                                      idDataGroup, 
                                                                      false );
               dstrMstrContMatDateBasedOn.strip().upperCase();

               if( !_bGuaranteeCalcByRules)
               {
                  setFieldRequired( ifds::ContractMatBasedOn, idDataGroup, false);
                  setFieldValid( ifds::ContractMatBasedOn, idDataGroup, true);
               }
            }
         }
		 cdStartDateRelatedChanges(idDataGroup);
      }
      else if ( idField == ifds::UserDefinedMaturityDate )
      {
         DString strUserDefinedCMD;
         getField(ifds::UserDefinedMaturityDate, strUserDefinedCMD, idDataGroup, false);
         setField(ifds::ContractMaturityDate,    strUserDefinedCMD, idDataGroup, false);
      }
      else if ( idField == ifds::ContractMaturityDate )
      {
         contractMaturityDateRelatedChanges(idDataGroup);
      }
      else if( idField == ifds::AgeBasedOn)
      {
         DString strAgeBasedOnFmt;
         getField(ifds::AgeBasedOn,strAgeBasedOnFmt,idDataGroup,true);
         setFieldNoValidate(ifds::AgeBasedOnDesc,strAgeBasedOnFmt, idDataGroup,false, true);
      }
      else if( idField == ifds::EffectiveDate)
      {
         updateContractMatBasedOnSubst(idDataGroup);
         DString strContractMatBasedOn;
         getField(ifds::ContractMatBasedOn, strContractMatBasedOn, idDataGroup, false);
         strContractMatBasedOn.strip().upperCase();

         DString dstrNewDate;
         DString dstrEffectiveDate;
         getField(ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false);

         DString dstrMaxAge;
         DString dstrMinTerm;
         DString dstrMinAge;
         getMasterMinTermAndMinMaxAge( dstrMinTerm, dstrMinAge, dstrMaxAge, idDataGroup );

         if(strContractMatBasedOn == CMD_BASED_ON_MIN_TERM && !dstrEffectiveDate.empty())
         {
            addYearToDate(dstrEffectiveDate, dstrNewDate, dstrMinTerm.asInteger());
            setFieldNoValidate(ifds::ContractMaturityDate, dstrNewDate, idDataGroup, false, false, true);
         }
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************
void ContractInfo::createContractTypesList(DString &strCodesList, 
                                           const BFDataGroupId& idDataGroup )
{
   strCodesList = NULL_STRING;
   DString dstrContractTypeId;
   DString dstrAcctGroup;
   DString dstrMstrContractType;
   DString dstrMstrGroupCode;

   ContractInfoList*pContractInfoList = static_cast<ContractInfoList*>(getParent());
   _dstrAcctNum  = pContractInfoList->getAcctNum();

   _pMFAccount->getField(ifds::AcctGroup, dstrAcctGroup, idDataGroup);

   if (_pMasterContractList)
   {
      BFObjIter iterMasterContract( *_pMasterContractList, idDataGroup);
      iterMasterContract.begin();
      
      BFAbstractCBO* pMasterContract = NULL;

      while( !iterMasterContract.end() )
      {
         pMasterContract = iterMasterContract.getObject();
         pMasterContract->getField(ifds::GroupCode, dstrMstrGroupCode, idDataGroup);
         dstrMstrGroupCode.strip();

         if(dstrAcctGroup == dstrMstrGroupCode)
         {
            DString dstrMstrDefaultVer;
            pMasterContract->getField(ifds::ContractType, dstrMstrContractType,  idDataGroup, false);
            pMasterContract->getField(ifds::DefaultVer,   dstrMstrDefaultVer,    idDataGroup, false );
            dstrMstrContractType.strip().upperCase();
            dstrMstrDefaultVer.strip().upperCase();

            if(dstrMstrDefaultVer == I_("Y"))
            {
               strCodesList += dstrMstrContractType+I_("=")+dstrMstrContractType + I_(";");
            }
         }
         ++iterMasterContract;
      }
   }
}

//**************************************************************************
SEVERITY ContractInfo::loadContractTypeSubstitutionList( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "loadContractTypeSubstitutionList" ) );

   DString dstrCodesList = NULL_STRING;     
   BFProperties * pBFProperties = getFieldProperties( ifds::ContractType, idDataGroup );
   createContractTypesList( dstrCodesList, idDataGroup ); 

   if( dstrCodesList != NULL_STRING )
   {
      dstrCodesList.upperCase();
      setFieldAllSubstituteValues( ifds::ContractType, idDataGroup, dstrCodesList );   
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//**************************************************************************
bool ContractInfo::isGWOContract( const BFDataGroupId& idDataGroup )
{
   bool bIsGWOContract = false;

   DString dstrGWOSupported;
   getWorkSession ().getOption ( ifds::GWOSupported, 
                                 dstrGWOSupported, 
                                 idDataGroup,
                                 false);
   dstrGWOSupported.stripAll().upperCase();

   if (_pMasterContractList && dstrGWOSupported  == I_( "Y" ))
   {
      DString dstrAcctGroup;
      DString dstrGWOContract; 
      DString dstrContractType;

      getField(ifds::ContractType, dstrContractType, idDataGroup);

      ContractInfoList* pContractInfoList = static_cast<ContractInfoList*>(getParent());
      
      _pMFAccount->getField(ifds::AcctGroup, dstrAcctGroup, idDataGroup);
      
      _pMasterContractList->getFieldByGroupAndContractType ( dstrAcctGroup, dstrContractType, ifds::IsGWOContract, 
                                                            dstrGWOContract, idDataGroup, false );
      if ( dstrGWOSupported.upperCase() == I_("Y") && dstrGWOContract.upperCase() == I_("Y") )
         bIsGWOContract = true;
   }

   return bIsGWOContract;
}

//**************************************************************************
bool ContractInfo::isNewContract( const BFDataGroupId& idDataGroup )
{
   return isNew();
}

//********************************************************************************************
SEVERITY ContractInfo::ValidateTaxTypeAndTaxJurisdiction( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateTaxTypeAndTaxJurisdiction" ) );
   BFAbstractCBO* pMasterContract = NULL;
   getMasterContract(pMasterContract, idDataGroup);
   if(pMasterContract && _pMFAccount)
   {
      DString dstrTaxTypeList;
      DString dstrPensionJurisdictionList;

      pMasterContract->getField(ifds::TaxTypeList, dstrTaxTypeList, idDataGroup, false);
      pMasterContract->getField(ifds::PensionJurisdictionList, dstrPensionJurisdictionList, idDataGroup, false);
      dstrTaxTypeList.stripAll().upperCase();
      dstrPensionJurisdictionList.stripAll().upperCase();
      
      DString dstrTaxType;
      _pMFAccount->getField(ifds::TaxType, dstrTaxType, idDataGroup, false);
      dstrTaxType.stripAll().upperCase();

      if(dstrTaxTypeList != NULL_STRING && dstrTaxTypeList.find(dstrTaxType) == DString::npos)
      {
         ADDCONDITIONFROMFILE(CND::ERR_INVALID_TAX_TYPE);
      }

      DString dstrPensionJurisdiction;
      Shareholder* pShareholder = NULL;

      DString shrNum;
      _pMFAccount->getField( ifds::ShrNum, shrNum, idDataGroup );

      SEVERITY sevRtn = getWorkSession().getShareholder( idDataGroup, shrNum, pShareholder ) ;

      if( sevRtn <= WARNING && pShareholder)
      {
         pShareholder->getField( ifds::TaxJurisCode, dstrPensionJurisdiction, idDataGroup );
         dstrPensionJurisdiction.stripAll().upperCase();
         if(dstrPensionJurisdictionList != NULL_STRING && dstrPensionJurisdictionList.find(dstrPensionJurisdiction) == DString::npos)
         {
            ADDCONDITIONFROMFILE( CND::ERR_INVALID_PENSION );
         }
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
SEVERITY ContractInfo::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );
   DString dstrGender;

   ValidateTaxTypeAndTaxJurisdiction( idDataGroup );
   
   if ( isNew() ) // Follow the way that base does.  
   {
      DString dstrDateOfBirth = NULL_STRING;
      getDofBirth( idDataGroup, dstrDateOfBirth );
      ValidateOldestLegalDate( dstrDateOfBirth, idDataGroup );
   }

   if (hasSingleLifeNMCRMaster(idDataGroup)) 
   {
      if (!validateAnnuitantGender (idDataGroup, dstrGender))
      {
         getErrMsg (IFASTERR::GENDER_CANNOT_BE_BLANK_FOR_NMCR_SINGLE_LIFE_CONTRACT,
                    CND::ERR_GENDER_CANNOT_BE_BLANK_FOR_NMCR_SINGLE_LIFE_CONTRACT,
                    CND::WARN_GENDER_CANNOT_BE_BLANK_FOR_NMCR_SINGLE_LIFE_CONTRACT,
                    idDataGroup);
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool ContractInfo::getDofBirth( const BFDataGroupId& idDataGroup, DString &dstrDofBirth )
{
   DString strAccountNum;
   DString dstrAcctType;
   DString dstrTaxType;
   DString dstrEntityType;
   DString dstrSeqNumber;
   DString dstrEntityId; 

   bool bRtn = false;

   SEVERITY sevRtn = SEVERE_ERROR;
   _pMFAccount->getField( ifds::AccountNum, strAccountNum, idDataGroup );  
   _pMFAccount->getField( ifds::AcctType, dstrAcctType, idDataGroup, false );
   _pMFAccount->getField( ifds::TaxType, dstrTaxType, idDataGroup, false );

   AccountEntityXref *pAccountEntityXref;
   sevRtn = getWorkSession().getAccountEntityXref( BF::HOST, pAccountEntityXref );
   sevRtn = pAccountEntityXref->PopulateEntitiesList(  idDataGroup, strAccountNum );
   if( sevRtn >= WARNING || !pAccountEntityXref )
      return(false);

   BFObjIter iterAcctEntXRef( *pAccountEntityXref, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );
   DString searchKey;
   pAccountEntityXref->buildPartialKeyForAccount( searchKey, strAccountNum );

   //  For the non-registered tax type ( TaxType_4 == "0" ), the annuitant entity type ( EntityType_50 = "05" )
   //  with the smallest sequence number, this entity must have valid DOfBirth_51 and use it for BaiMaturityDate
   //  and LegalMaturityDate calculations

//IN3014990 - Kevin Li Yim -  LCMD based on annuitant all the time.
//   if( getWorkSession().isNonRegLike( dstrTaxType.stripAll() ) )
//   {  // non-registered account
      for( iterAcctEntXRef.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey ); !iterAcctEntXRef.end(); ++iterAcctEntXRef )
      {
         iterAcctEntXRef.getObject( )->getField(ifds::EntityType, dstrEntityType, idDataGroup, false );
         iterAcctEntXRef.getObject( )->getField(ifds::SeqNumber, dstrSeqNumber, idDataGroup, false );
         // EntityType = "05" means an annuitant entity. The program should check annuitant's DofBirth.
         // We want the first Entity with EntityType = 05 by looking at the Entity sequence number.
         // The sequence number does not always start with one.
         // Since Entities are indexed by AccountNum, EntityType, EntitySequence, EntityId
         // The first object in the iteration that matches entity type 05 should be 
         // the entity with the smallest sequence number.
         if( dstrEntityType.stripAll() ==  I_("05") )
         {
            // get annuitant's entityId
            iterAcctEntXRef.getObject( )->getField(ifds::EntityId, dstrEntityId, idDataGroup, false );
            break;
         }
      }
   //}
   //else
   //{   // registered account
   //   for( iterAcctEntXRef.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey ); !iterAcctEntXRef.end(); ++iterAcctEntXRef )
   //   {
   //      iterAcctEntXRef.getObject( )->getField(ifds::EntityType, dstrEntityType, idDataGroup, false );
   //      iterAcctEntXRef.getObject( )->getField(ifds::SeqNumber, dstrSeqNumber, idDataGroup, false );
   //      // EntityType = "01" means Owner . The program should get owner's DofBirth
   //      // Refer to above comment, same concept.
   //      if( dstrEntityType.stripAll() ==  I_("01") )
   //      {
   //         // get owner's entityId
   //         iterAcctEntXRef.getObject( )->getField(ifds::EntityId, dstrEntityId, idDataGroup, false );
   //         break;
   //      }
   //   }
   //}

   if( dstrEntityId != NULL_STRING )
   {
      Entity *pEntity;
      sevRtn = getWorkSession().getEntity(  idDataGroup, dstrEntityId, pEntity );
      if( sevRtn <= WARNING && pEntity )
      {
         pEntity->getField( ifds::DofBirth, dstrDofBirth, idDataGroup, false );
         if( dstrDofBirth != NULL_STRING )
            bRtn = true;
         else
            bRtn = false;

      }
   }
   return(bRtn);  
}


//*****************************************************************************
SEVERITY ContractInfo::ValidateOldestLegalDate( DString &dsDofBirth, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "CheckOldestLegalDate" ) );
   DString dstrTaxTypeAcct;
   DString dstrTaxType;
   DString dstrLegalAgeCalcType;
   DString dstrLegalMaxAge;
   DString dstrNumOfYears;
   DString dstrCurrBusDate;

   CotLegalAge *pCotLegalAge = NULL;
   getCotLegalAge( pCotLegalAge, idDataGroup );

   if (pCotLegalAge)
   {
      pCotLegalAge->getField( ifds::LegalAgeCalcType, dstrLegalAgeCalcType,idDataGroup, false );
      pCotLegalAge->getField( ifds::LegalMaxAge, dstrLegalMaxAge, idDataGroup, false);
      pCotLegalAge->getField( ifds::NumOfYears, dstrNumOfYears, idDataGroup, false);
   }

   int iLegalAgeCalcType = dstrLegalAgeCalcType.asInteger();
   if( dsDofBirth == NULL_STRING && dstrLegalAgeCalcType != 4)
   {
      ADDCONDITIONFROMFILE( CND::ERR_NO_DATE_OF_BIRTH );
      return(GETCURRENTHIGHESTSEVERITY());
   }
   int yr1;
   DString date1;
   DString years;
   DString month;
   DString day;
   DString inceptionDate;

   DString dstrConfiguration( I_( "HostMasks" ) );
   DString dstrKey( I_("D") );
   DString OldestLegalDate = GetConfigValueAsString( I_( "LocaleFormats" ), 
                                                     dstrConfiguration,
                                                     dstrKey );
   int month_pos = OldestLegalDate.find( I_( "MM" ) );
   int day_pos   = OldestLegalDate.find( I_( "dd" ) );
   int year_pos  = OldestLegalDate.find( I_( "yyyy" ) );
   bool bIssueErr = false;
   if( DString::npos != year_pos )
   {
      if(iLegalAgeCalcType != 4)
      {
         date1.assign( dsDofBirth, year_pos, 4);
         yr1 = convertToULong( date1 );
         month.assign( dsDofBirth, month_pos, 2);
         day.assign( dsDofBirth, day_pos, 2);

         if( yr1 == 0 )
         {
            ADDCONDITIONFROMFILE( CND::ERR_NO_DATE_OF_BIRTH );
         }
         else
         {
            switch( iLegalAgeCalcType )
            {
            case 1: // birthday
               yr1 = yr1 + dstrLegalMaxAge.asInteger();
               convertIntToString( yr1, years );
               OldestLegalDate.replace(OldestLegalDate.find(I_("yyyy")), 4, years);
               // check leap year
               if( !( BFDate::isLeapYear( yr1 ) ) && ( month == I_( "02" )) && ( day == I_( "29" )) )
               {
                  month = I_( "02" );
                  day = I_( "28" );
               }
               OldestLegalDate.replace(OldestLegalDate.find(I_("dd")), 2, day);
               OldestLegalDate.replace(OldestLegalDate.find(I_("MM")), 2, month);

               break;

            case 2: // next birthday
               yr1 = yr1 + dstrLegalMaxAge.asInteger() + 1;
               convertIntToString( yr1, years );
               OldestLegalDate.replace(OldestLegalDate.find(I_("yyyy")), 4, years);
               // check leap year
               if( !( BFDate::isLeapYear( yr1 ) ) && ( month == I_( "02" )) && ( day == I_( "29" )) )
               {
                  month = I_( "02" );
                  day = I_( "28" );
               }
               OldestLegalDate.replace(OldestLegalDate.find(I_("dd")), 2, day);
               OldestLegalDate.replace(OldestLegalDate.find(I_("MM")), 2, month);

               break;

            case 3: // january first
               OldestLegalDate.replace(OldestLegalDate.find(I_("dd")), 2, I_("01"));
               OldestLegalDate.replace(OldestLegalDate.find(I_("MM")), 2, I_("01"));
               convertIntToString( yr1 + dstrLegalMaxAge.asInteger() , years );
               OldestLegalDate.replace(OldestLegalDate.find(I_("yyyy")), 4, years);
               break;

            default://wrong tax type
               bIssueErr = true;
               break;
            }
         }
      }
      else
      {
         DString strRESPClassify;

         if(_pMFAccount->isNew())
         {
            _pMFAccount->getField( ifds::EffectiveDate, inceptionDate, idDataGroup, false );  
			strRESPClassify = I_("00");
         }
         else
         {
            _pMFAccount->getField( ifds::InceptionDate, inceptionDate, idDataGroup, false );  
            RESPInfo* respInfo = NULL;
            _pMFAccount->getRESPInfo(respInfo, idDataGroup);

            if(respInfo)
            {
               respInfo->getField(ifds::RESPClassify, strRESPClassify, idDataGroup, false);
            }
         }

         if(strRESPClassify == I_("00"))
         {
            pCotLegalAge->getField( ifds::NumOfYears, dstrNumOfYears,idDataGroup, false );
         }
         else
         {
            pCotLegalAge->getField( ifds::AltNumOfYears, dstrNumOfYears,idDataGroup, false );
         }

         inceptionDate.strip().upperCase();
         date1.assign( inceptionDate, year_pos, 4);
         yr1 = convertToULong( date1 );
         OldestLegalDate.replace(OldestLegalDate.find(I_("dd")), 2, I_("31"));
         OldestLegalDate.replace(OldestLegalDate.find(I_("MM")), 2, I_("12"));
         convertIntToString( yr1 + dstrNumOfYears.asInteger() , years );
         OldestLegalDate.replace(OldestLegalDate.find(I_("yyyy")), 4, years);
      }
   }

   _pMgmtCoOptions->getField( ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false );
   if( DSTCommonFunctions::CompareDates( OldestLegalDate, dstrCurrBusDate ) 
       == DSTCommonFunctions::FIRST_EARLIER || bIssueErr )
   {
      //Oldest legal date cannot be in the past.
      ADDCONDITIONFROMFILE( CND::ERR_OLDEST_LEGAL_DATE_CANNOT_BE_IN_THE_PAST ); 
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************
SEVERITY ContractInfo::getCotLegalAge( CotLegalAge *&pCotLegalAge, const BFDataGroupId& idDataGroup, bool inquireDatabase )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getCotLegalAge" ) );

   DString dstrContractType;
   DString dstrTaxType;
   DString dstrProvReg;
   DString dstrEffectiveDate;

   getField( ifds::ContractType, dstrContractType, idDataGroup, false );	
   getField( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false );

   _pMFAccount->getField( ifds::TaxType,      dstrTaxType, idDataGroup, false );	
   _pMFAccount->getField( ifds::PensionJuris, dstrProvReg, idDataGroup, false );

   //if(dstrProvReg.strip().upperCase().empty())
   //{
   //   getField( ifds::ProvinceCanada, dstrProvReg, idDataGroup, false);
   //   dstrProvReg.strip().upperCase();
   //}

   if ( dstrContractType != NULL_STRING && 
      dstrTaxType != NULL_STRING &&
      dstrEffectiveDate != NULL_STRING )
   {
      DString dstrKey = I_( "CotLegalAge" ) 
         + dstrContractType  
         + dstrProvReg 
         + dstrTaxType 
         + dstrEffectiveDate;

      pCotLegalAge = dynamic_cast<CotLegalAge*> (getObject (dstrKey, idDataGroup));

      if (!pCotLegalAge)
      {
         pCotLegalAge = new CotLegalAge (*this);

         if (pCotLegalAge->init (dstrContractType, dstrTaxType, dstrProvReg, dstrEffectiveDate) <=WARNING)
         {
            setObject (pCotLegalAge, dstrKey, OBJ_ACTIVITY_NONE, idDataGroup);
         }
         else
         {
            delete pCotLegalAge;
            pCotLegalAge = NULL;
         }
      } 
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY ContractInfo::initCMDBasedON(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initCMDBasedON" ) );
   
   if( !_bGuaranteeCalcByRules )
   {
      setFieldNoValidate( ifds::ContractMatBasedOn, NULL_STRING, idDataGroup, false, true);
      setFieldReadOnly( ifds::ContractMatBasedOn, idDataGroup, true );
      setFieldValid( ifds::ContractMatBasedOn, idDataGroup, true );

      return(GETCURRENTHIGHESTSEVERITY());
   }
   else if(_pMasterContractList)
   {
      DString dstrIssueDate;
      getField ( ifds::IssueDate, dstrIssueDate, idDataGroup, false);
      dstrIssueDate.stripAll();

      DString dstrAcctGroup;
      DString dstrContractType;
      DString dstrMstrContMatDateBasedOn;

      getField( ifds::ContractType, dstrContractType, idDataGroup, false );
      dstrContractType.strip().upperCase();
      
      ContractInfoList* pContractInfoList = static_cast<ContractInfoList*>(getParent());
      
      _pMFAccount->getField(ifds::AcctGroup, dstrAcctGroup, idDataGroup);

      _pMasterContractList->getFieldByGroupAndContractType ( dstrAcctGroup, 
                                                             dstrContractType, 
                                                             ifds::ContMatDateBasedOn, 
                                                             dstrMstrContMatDateBasedOn, 
                                                             idDataGroup, 
                                                             false );
      dstrMstrContMatDateBasedOn.strip().upperCase();

      if( dstrMstrContMatDateBasedOn == I_("05") || dstrMstrContMatDateBasedOn == I_("06"))
      {
         DString strContMatDateBasedOnSubstList;
         BFProperties *pBFPropertiesHost = getFieldProperties( ifds::ContractMatBasedOn, BF::HOST );
         pBFPropertiesHost->getAllSubstituteValues (strContMatDateBasedOnSubstList);

         strContMatDateBasedOnSubstList = removeItemFromSubtList ( strContMatDateBasedOnSubstList, CMD_BASED_ON_LCMD);
         
         if( dstrMstrContMatDateBasedOn == I_("06"))
            strContMatDateBasedOnSubstList = removeItemFromSubtList ( strContMatDateBasedOnSubstList, CMD_BASED_ON_MAX_AGE);

         strContMatDateBasedOnSubstList = strContMatDateBasedOnSubstList;

         BFProperties *pBFPropertiesLocal = getFieldProperties( ifds::ContractMatBasedOn, idDataGroup );
         setFieldAllSubstituteValues (ifds::ContractMatBasedOn, idDataGroup, strContMatDateBasedOnSubstList);
         pBFPropertiesLocal->setSubstituteValues(NULL);
         
         setFieldRequired( ifds::ContractMatBasedOn, idDataGroup, true );

         //DString dstrIssueDate;
         //getField ( ifds::IssueDate, dstrIssueDate, idDataGroup, false);
         //dstrIssueDate.stripAll();
         setFieldReadOnly( ifds::ContractMatBasedOn, idDataGroup, dstrIssueDate != I_("") && dstrIssueDate != _dstr12319999);

         setFieldValid( ifds::ContractMatBasedOn, idDataGroup, false );
      }
      else if( dstrMstrContMatDateBasedOn == CMD_BASED_ON_MAX_AGE || 
               dstrMstrContMatDateBasedOn == CMD_BASED_ON_MIN_TERM || 
               dstrMstrContMatDateBasedOn == CMD_BASED_ON_LCMD || 
               dstrMstrContMatDateBasedOn == CMD_BASED_ON_USERDEFINED || 
               dstrMstrContMatDateBasedOn == CMD_BASED_ON_USERDEFINED_TRANSFER)
      {
         DString strContMatDateBasedOnSubstList;
         BFProperties *pBFPropertiesHost = getFieldProperties( ifds::ContractMatBasedOnOrig, BF::HOST );
         pBFPropertiesHost->getAllSubstituteValues (strContMatDateBasedOnSubstList);

         if(dstrMstrContMatDateBasedOn != CMD_BASED_ON_MAX_AGE)
            strContMatDateBasedOnSubstList = removeItemFromSubtList ( strContMatDateBasedOnSubstList, CMD_BASED_ON_MAX_AGE);
         if(dstrMstrContMatDateBasedOn != CMD_BASED_ON_MIN_TERM)
            strContMatDateBasedOnSubstList = removeItemFromSubtList ( strContMatDateBasedOnSubstList, CMD_BASED_ON_MIN_TERM);
         if(dstrMstrContMatDateBasedOn != CMD_BASED_ON_LCMD)
            strContMatDateBasedOnSubstList = removeItemFromSubtList ( strContMatDateBasedOnSubstList, CMD_BASED_ON_LCMD);
         if(dstrMstrContMatDateBasedOn != CMD_BASED_ON_USERDEFINED)
            strContMatDateBasedOnSubstList = removeItemFromSubtList ( strContMatDateBasedOnSubstList, CMD_BASED_ON_USERDEFINED);

         setFieldAllSubstituteValues (ifds::ContractMatBasedOn, idDataGroup, strContMatDateBasedOnSubstList);
   
         DString dstrCurrContMatDateBasedOn;
         getField(ifds::ContractMatBasedOn, dstrCurrContMatDateBasedOn, idDataGroup);
         if(dstrCurrContMatDateBasedOn != CMD_BASED_ON_USERDEFINED_TRANSFER)
            setFieldNoValidate(ifds::ContractMatBasedOn, dstrMstrContMatDateBasedOn, idDataGroup, false, false, true);
      }
      else
      {
         setFieldNoValidate( ifds::ContractMatBasedOn, dstrMstrContMatDateBasedOn, idDataGroup, false );
         setFieldReadOnly( ifds::ContractMatBasedOn, idDataGroup, true );
         setFieldValid( ifds::ContractMatBasedOn, idDataGroup, true );
      }
      setFieldReadOnly( ifds::ContractMatBasedOn, idDataGroup, dstrIssueDate != I_("") && dstrIssueDate != _dstr12319999);
//   setFieldReadOnly(ifds::ContractMatBasedOn, idDataGroup, !isNew());
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//**************************************************************************
SEVERITY ContractInfo::loadAgeBasedOnSubstitutionList( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "loadAgeBasedOnSubstitutionList" ) );

   DString strCodesList = NULL_STRING;
   DString strInsurAgeTypeSubstList;
   BFProperties * pBFProperties = getFieldProperties( ifds::AgeBasedOn, idDataGroup );
   BFProperties * pBFPropInsurAgeType = getFieldProperties( ifds::InsurAgeType, idDataGroup );

   pBFPropInsurAgeType->getAllSubstituteValues(strInsurAgeTypeSubstList);
   strCodesList = I_(" = ;");
   strCodesList += strInsurAgeTypeSubstList;

   setFieldAllSubstituteValues( ifds::AgeBasedOn, idDataGroup, strCodesList );   
   pBFProperties->setSubstituteValues(NULL);

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY ContractInfo::defaultReadonlyFields( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "defaultReadonlyFields" ) );
   
   BFFieldId _readOnlyList[] = 
   {
      //ifds::ContractType,   ifds::EffectiveDate,        ifds::StopDate,         ifds::ContractMatBasedOn,
      //ifds::Status,         ifds::AgeBasedOn,           ifds::SuspectGuarType,  
      ifds::ContractVer,    ifds::ClsPerTerm,           ifds::PolicyNum,
      ifds::ContractTerm,   ifds::IssueDate,            ifds::AnnivMonth,       ifds::AnnivDay,
      ifds::ProvinceCanada, ifds::ContractMaturityDate, ifds::LegalMaturityDate,ifds::BailMaturityDate,
      ifds::CDStartDate,    ifds::RedAgeDate,           ifds::RefMatDate,       ifds::LWAStartDate,
      ifds::LWAAgeUsed,     ifds::LWARateApplied,       ifds::LWAElectDate,     ifds::ReqUnitAdj, 
      ifds::ContractTypeId, ifds::LastResetDate
   };

   int iNumField = sizeof(_readOnlyList)/sizeof(BFFieldId);
   
   for(int i=0;i<iNumField;i++)
   {
      setFieldReadOnly(_readOnlyList[i], idDataGroup, true);
   }
   
   return(GETCURRENTHIGHESTSEVERITY());   
}

//********************************************************************************************
void ContractInfo::addYearToDate( DString& dstrInDate, DString& dstrOutDate, int numYear )
{
   BFDate bfInDate(dstrInDate, BFDate::DATE_FORMAT::DF_HOST);
   bfInDate.addYears(numYear);
   dstrOutDate = bfInDate.get(BFDate::DATE_FORMAT::DF_HOST);
}

//******************************************************************************
SEVERITY ContractInfo::contractMaturityDateRelatedChanges(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "contractMaturityDateRelatedChanges" ) );

   if( _bGuaranteeCalcByRules )
   {
	  cdStartDateRelatedChanges(idDataGroup);
   }
   else
   {
      setFieldNoValidate(ifds::CDStartDate,NULL_STRING, idDataGroup,false);
   }
   
   setValidFlag (ifds::ContractMaturDateCrossEdit, idDataGroup, false);   

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY ContractInfo::getAcctCreationDate(DString& strValue, const BFDataGroupId& idDataGroup, bool bFormatted)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getAcctCreationDate" ) );
   

   if ( isNew() )
   {
      _pMFAccount->getField(ifds::DateOfReg, strValue, idDataGroup, bFormatted);
   }
   else
   {
      _pList->getField(ifds::FirstEffective,strValue, idDataGroup, false);

      if(strValue.strip().upperCase().empty())
      {
         _pMFAccount->getField(ifds::DateOfReg, strValue, idDataGroup, bFormatted);
      }
      else
      {
         _pList->getField(ifds::FirstEffective,strValue, idDataGroup, bFormatted);
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY ContractInfo::getMasterContractList(MasterContractList*& lpMasterContractList, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMasterContractList" ) );
   
   DString dstrPorfolioIsRequried;
   getWorkSession().getOption( ifds::PorfolioIsRequried, dstrPorfolioIsRequried, idDataGroup, false );      
   bool bPortfolioIsRequired = dstrPorfolioIsRequried.strip().upperCase() == I_("Y");

   if(bPortfolioIsRequired)
   {
      _pMFAccount->getMasterContractListByPortfolio(lpMasterContractList,idDataGroup);
   }
   else
   {
      getMgmtCo().getMasterContractList( lpMasterContractList );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY ContractInfo::getMasterContract(BFAbstractCBO*& _pMasterContract, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMasterContract" ) );

   _pMasterContract = NULL;
   if ( _pList )
   {
      DString dstrAcctGroup;
      DString dstrContractType;

      getField( ifds::ContractType, dstrContractType, idDataGroup );

      _pMFAccount->getField(ifds::AcctGroup, dstrAcctGroup, idDataGroup);
      dstrAcctGroup.strip().upperCase();

	  _pMasterContractList = NULL;
	  getMasterContractList(_pMasterContractList, idDataGroup);

      if (_pMasterContractList)
      {
         BFObjIter iterMasterContract( *_pMasterContractList, idDataGroup);
         iterMasterContract.begin();
         BFAbstractCBO* pMasterContract = NULL;

         while( !iterMasterContract.end() )
         {
            DString dstrMstrCntrTypeId;
            DString dstrMstrType;
            DString dstrMstrDefaultVer;
            DString dstrMstrCntrGroup;
               
            pMasterContract = iterMasterContract.getObject();
            pMasterContract->getField(ifds::ContractTypeId, dstrMstrCntrTypeId,  idDataGroup, false); 
            pMasterContract->getField(ifds::ContractType,   dstrMstrType,        idDataGroup, false);
            pMasterContract->getField(ifds::DefaultVer,     dstrMstrDefaultVer,  idDataGroup, false);
            pMasterContract->getField(ifds::GroupCode,      dstrMstrCntrGroup,   idDataGroup, false); 

            dstrMstrCntrTypeId.strip().upperCase();
            dstrMstrType.strip().upperCase();
            dstrMstrDefaultVer.strip().upperCase();
            dstrMstrCntrGroup.strip().upperCase();

            if( dstrContractType == dstrMstrType && dstrMstrDefaultVer == I_("Y") && dstrMstrCntrGroup == dstrAcctGroup)
            {
//               setFieldNoValidate( ifds::ContractTypeId, dstrMstrCntrTypeId, idDataGroup, false, true, true );
               _pMasterContract = pMasterContract;
               break;
            }
            ++iterMasterContract;
         }
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY ContractInfo::contractTypeRelatedChanges(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "contractTypeRelatedChanges" ) );

   setLegalAge( idDataGroup );
   
   BFAbstractCBO* pMasterContract = NULL;
   SEVERITY sevRtn = getMasterContract(pMasterContract, idDataGroup);
   if(pMasterContract)
   {
      DString dstrMstrCntrTypeId;
      pMasterContract->getField(ifds::ContractTypeId, dstrMstrCntrTypeId,  idDataGroup, false); 
      setFieldNoValidate( ifds::ContractTypeId, dstrMstrCntrTypeId, idDataGroup, false, true, true );
   }

   DString dstrClosingPrdTerm;
   DString dstrContractMinTerm;
   DString dstrContractVer;

   if(sevRtn <= WARNING && pMasterContract)
   {
      pMasterContract->getField(ifds::MinTerm,     dstrContractMinTerm, idDataGroup, false);
      pMasterContract->getField(ifds::ClsPerTerm,  dstrClosingPrdTerm,  idDataGroup, false);
      pMasterContract->getField(ifds::ContractVer, dstrContractVer,     idDataGroup, false);

      setFieldNoValidate( ifds::ContractTerm,   dstrContractMinTerm, idDataGroup, false, false, true );
      setFieldNoValidate( ifds::ClsPerTerm,     dstrClosingPrdTerm,  idDataGroup, false, false, true );
      setFieldNoValidate( ifds::ContractVer,    dstrContractVer,     idDataGroup, false, false, true );
   }

   DString dstrClsPerTerm = I_("0");
   
   if(_bGuaranteeCalcByRules)
   {
      setFieldNoValidate( ifds::RefMatDate,        NULL_STRING, idDataGroup, false, true, true, false  );
      setFieldNoValidate( ifds::RedAgeDate,        NULL_STRING, idDataGroup, false, true, true, false  );
      setFieldNoValidate( ifds::BailMaturityDate,  NULL_STRING, idDataGroup, false );

      if (isNew ())
      {
         setFieldNoValidate( ifds::ContractTerm, dstrContractMinTerm, idDataGroup, false, true, true, false );

         if (dstrClosingPrdTerm == I_("1")) // applicable
            dstrClsPerTerm = dstrContractMinTerm;

      }
      setFieldReadOnly (ifds::ClsPerTerm, idDataGroup, true);
      setFieldReadOnly (ifds::ContractTerm, idDataGroup, true);
   }

   setFieldNoValidate( ifds::ClsPerTerm, dstrClsPerTerm, idDataGroup, false, true, true, false );
   
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY ContractInfo::cdStartDateRelatedChanges(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "cdStartDateRelatedChanges" ) );
  

   DString dstrClosingPrdTerm;
   DString dstrContractMinTerm;

   if( _bGuaranteeCalcByRules && isNew ())
   {
	  DString dstrClosingPrdTerm;
	  DString dstrClosingDate;

	  getField (ifds::ClsPerTerm, dstrClosingPrdTerm, idDataGroup, false );

	  int iClosingPrdTerm = dstrClosingPrdTerm.asInteger ();

	  if (iClosingPrdTerm == 0)
	  {
  		  dstrClosingDate = _dstr12319999;
	  }
	  else
	  {
		  DString dstrContractMaturityDate;
		  DString dstrCMDateMinusTerm;

		  int iClosingPrdTerm= dstrClosingPrdTerm.asInteger ();

		  iClosingPrdTerm = iClosingPrdTerm * -1;

		  getField(ifds::ContractMaturityDate, dstrContractMaturityDate, idDataGroup, false);

		  if (!dstrContractMaturityDate.empty ())
		  {
			addYearToDate (dstrContractMaturityDate, dstrCMDateMinusTerm, iClosingPrdTerm);
			DSTCommonFunctions::addDays (dstrCMDateMinusTerm, dstrClosingDate, 1);
		  }
	  }

  	  setFieldNoValidate( ifds::CDStartDate, dstrClosingDate, idDataGroup, false, true, true, false );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

SEVERITY ContractInfo::updateContractMatBasedOnSubst(const BFDataGroupId& idDataGroup, bool hasLinkedContractWithIssueDate )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "updateContractMatBasedOnSubst" ) );

   if( !_bGuaranteeCalcByRules )
   {
      setFieldNoValidate( ifds::ContractMatBasedOn, NULL_STRING, idDataGroup, false, true);
      setFieldReadOnly( ifds::ContractMatBasedOn, idDataGroup, true );
      setFieldValid( ifds::ContractMatBasedOn, idDataGroup, true );

      return(GETCURRENTHIGHESTSEVERITY());
   }
   else if(_pMasterContractList)
   {
      DString dstrAcctGroup;
      DString dstrContractType;
      DString dstrMstrContMatDateBasedOn;

      getField( ifds::ContractType, dstrContractType, idDataGroup, false );
      dstrContractType.strip().upperCase();

      ContractInfoList *pContractInfoList = static_cast<ContractInfoList*>(getParent());
      
      _pMFAccount->getField(ifds::AcctGroup, dstrAcctGroup, idDataGroup);


      _pMasterContractList->getFieldByGroupAndContractType ( dstrAcctGroup, 
                                                             dstrContractType, 
                                                             ifds::ContMatDateBasedOn, 
                                                             dstrMstrContMatDateBasedOn, 
                                                             idDataGroup, 
                                                             false );
      dstrMstrContMatDateBasedOn.strip().upperCase();

      DString dstrIssueDate;
      getField ( ifds::IssueDate, dstrIssueDate, idDataGroup, false);
      dstrIssueDate.stripAll();
      if( dstrMstrContMatDateBasedOn == I_("05") || dstrMstrContMatDateBasedOn == I_("06"))
      {
//         if(isNew())
         DString strContMatDateBasedOnSubstList;
         BFProperties *pBFPropertiesHost = getFieldProperties( ifds::ContractMatBasedOnOrig, BF::HOST );
         pBFPropertiesHost->getAllSubstituteValues (strContMatDateBasedOnSubstList);

         if(!hasLinkedContractWithIssueDate && (dstrIssueDate == I_("") || dstrIssueDate == _dstr12319999))
         {
            DString dstrMaxAge;
            DString dstrMinTerm;
            DString dstrMinAge;
            getMasterMinTermAndMinMaxAge( dstrMinTerm, dstrMinAge, dstrMaxAge, idDataGroup );

            int intMinTerm = dstrMinTerm.asInteger();
            int intMaxAge  = dstrMaxAge.asInteger();
            int intMinAge  = dstrMinAge.asInteger();
            
            int minAgeDiff = intMinTerm - intMinAge;
            int maxAgeDiff = intMinTerm - intMaxAge;

            DString dstrDofBirth;
            getDofBirth(idDataGroup, dstrDofBirth );
            BFDate fbdDofBirth(dstrDofBirth, BFDate::DATE_FORMAT::DF_HOST);
            
            DString dstrEffectiveDate;
            getField(ifds::EffectiveDate, dstrEffectiveDate, idDataGroup, false);
            BFDate fbdEffectiveDate(dstrEffectiveDate, BFDate::DATE_FORMAT::DF_HOST);

            BFDate fbdMinEffectiveDate = fbdDofBirth;
            fbdMinEffectiveDate.addYears(intMinAge - intMinTerm);

            BFDate fbdMaxEffectiveDate  = fbdDofBirth;
            fbdMaxEffectiveDate.addYears(intMaxAge - intMinTerm);


            //BFDate fbdMinEffectiveDate(dstrEffectiveDate, BFDate::DATE_FORMAT::DF_HOST);
            //BFDate fbdMaxEffectiveDate(dstrEffectiveDate, BFDate::DATE_FORMAT::DF_HOST);
            //
            //fbdMinEffectiveDate.addYears(minAgeDiff);
            //fbdMaxEffectiveDate.addYears(maxAgeDiff);


            strContMatDateBasedOnSubstList = removeItemFromSubtList ( strContMatDateBasedOnSubstList, CMD_BASED_ON_LCMD);
            if( dstrMstrContMatDateBasedOn == I_("06"))
            {
               strContMatDateBasedOnSubstList = removeItemFromSubtList ( strContMatDateBasedOnSubstList, CMD_BASED_ON_MAX_AGE);
            }

            if(fbdEffectiveDate > fbdMaxEffectiveDate )
            {
               strContMatDateBasedOnSubstList = removeItemFromSubtList ( strContMatDateBasedOnSubstList, CMD_BASED_ON_MAX_AGE);
               strContMatDateBasedOnSubstList = removeItemFromSubtList ( strContMatDateBasedOnSubstList, CMD_BASED_ON_USERDEFINED);
            }
            
            if(fbdEffectiveDate < fbdMinEffectiveDate)
            {
               strContMatDateBasedOnSubstList = removeItemFromSubtList ( strContMatDateBasedOnSubstList, CMD_BASED_ON_MIN_TERM);
            }

            BFProperties *pBFPropertiesLocal = getFieldProperties( ifds::ContractMatBasedOn, idDataGroup );
            pBFPropertiesLocal->setSubstituteValues(NULL);
         }

         setFieldAllSubstituteValues (ifds::ContractMatBasedOn, idDataGroup, strContMatDateBasedOnSubstList);

         //DString dstrIssueDate;
         //getField ( ifds::IssueDate, dstrIssueDate, idDataGroup, false);
         //dstrIssueDate.stripAll();
         setFieldReadOnly( ifds::ContractMatBasedOn, idDataGroup, dstrIssueDate != I_("") && dstrIssueDate != _dstr12319999);
         
         setFieldValid(ifds::ContractMatBasedOn, idDataGroup, false);
         setFieldRequired(ifds::ContractMatBasedOn, idDataGroup, true);
         DString dstrContractMatBasedOn;
         getField(ifds::ContractMatBasedOn, dstrContractMatBasedOn, idDataGroup, false);
         {
            MAKEFRAME(CND::IFASTCBO_CONDITION, I_( "local" ));
            if(validateField(ifds::ContractMatBasedOn, dstrContractMatBasedOn, idDataGroup) > WARNING)
            {
               setField(ifds::ContractMatBasedOn, NULL_STRING, idDataGroup, false);
            }
         }
      }
      else if( dstrMstrContMatDateBasedOn == CMD_BASED_ON_MAX_AGE || 
               dstrMstrContMatDateBasedOn == CMD_BASED_ON_MIN_TERM || 
               dstrMstrContMatDateBasedOn == CMD_BASED_ON_LCMD || 
               dstrMstrContMatDateBasedOn == CMD_BASED_ON_USERDEFINED || 
               dstrMstrContMatDateBasedOn == CMD_BASED_ON_USERDEFINED_TRANSFER)
      {
         DString strContMatDateBasedOnSubstList;
         BFProperties *pBFPropertiesHost = getFieldProperties( ifds::ContractMatBasedOnOrig, BF::HOST );
         pBFPropertiesHost->getAllSubstituteValues (strContMatDateBasedOnSubstList);

         if(dstrMstrContMatDateBasedOn != CMD_BASED_ON_MAX_AGE)
            strContMatDateBasedOnSubstList = removeItemFromSubtList ( strContMatDateBasedOnSubstList, CMD_BASED_ON_MAX_AGE);
         if(dstrMstrContMatDateBasedOn != CMD_BASED_ON_MIN_TERM)
            strContMatDateBasedOnSubstList = removeItemFromSubtList ( strContMatDateBasedOnSubstList, CMD_BASED_ON_MIN_TERM);
         if(dstrMstrContMatDateBasedOn != CMD_BASED_ON_LCMD)
            strContMatDateBasedOnSubstList = removeItemFromSubtList ( strContMatDateBasedOnSubstList, CMD_BASED_ON_LCMD);
         if(dstrMstrContMatDateBasedOn != CMD_BASED_ON_USERDEFINED)
            strContMatDateBasedOnSubstList = removeItemFromSubtList ( strContMatDateBasedOnSubstList, CMD_BASED_ON_USERDEFINED);

         setFieldAllSubstituteValues (ifds::ContractMatBasedOn, idDataGroup, strContMatDateBasedOnSubstList);

         DString dstrCurrContMatDateBasedOn;
         getField(ifds::ContractMatBasedOn, dstrCurrContMatDateBasedOn, idDataGroup);
         if(dstrCurrContMatDateBasedOn != CMD_BASED_ON_USERDEFINED_TRANSFER)
            setFieldNoValidate(ifds::ContractMatBasedOn, dstrMstrContMatDateBasedOn, idDataGroup, false, false, true);
      }
      else 
      {
         DString strContMatDateBasedOnSubstList;
         BFProperties *pBFPropertiesHost = getFieldProperties( ifds::ContractMatBasedOnOrig, BF::HOST );
         pBFPropertiesHost->getAllSubstituteValues (strContMatDateBasedOnSubstList);
         setFieldAllSubstituteValues (ifds::ContractMatBasedOn, idDataGroup, strContMatDateBasedOnSubstList);
         setFieldReadOnly(ifds::ContractMatBasedOn, idDataGroup, true);
         setFieldNoValidate(ifds::ContractMatBasedOn, dstrMstrContMatDateBasedOn, idDataGroup, false, false, true);

      }

      setFieldReadOnly( ifds::ContractMatBasedOn, idDataGroup, hasLinkedContractWithIssueDate || dstrIssueDate != I_("") && dstrIssueDate != _dstr12319999);
//      setFieldReadOnly(ifds::ContractMatBasedOn, idDataGroup, !isNew());

   }
  
   return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************************
bool ContractInfo::CompareTwinContracts(const ContractInfo* pCompareTo, const BFDataGroupId& idDataGroup)
{
   bool retVal = true;

   
   if(pCompareTo)
   {
      for(int i = 0; i < iNumTwinFieldsToCompare; i++)
      {
         DString myValue;
         DString otherValue;
         getField(_twinCompareFieldsList[i], myValue, idDataGroup, false);
         pCompareTo->getField(_twinCompareFieldsList[i], otherValue, idDataGroup, false);
         if(myValue != otherValue)
         {
            retVal = false;
            break;
         }
      }
   }  
   else
      retVal = false;

   return retVal;
}

//********************************************************************************************
SEVERITY ContractInfo::ValidateUserDefinedMaturityDateBetweenMinMaxAge(const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateUserDefinedMaturityDateBetweenMinMaxAge" ) );
//DofB + MinAge   <=  User Defined CMD   <= DofB  + MaxAge  : ContractMaturDateCrossEdit

   DString dstrContMatDateBasedOn;
   DString dstrContractMaturityDate;

   getField(ifds::ContractMatBasedOn, dstrContMatDateBasedOn, idDataGroup,false);
   dstrContMatDateBasedOn.strip().upperCase();

   DString dstrTaxType;
   _pMFAccount->getField(ifds::TaxType, dstrTaxType, idDataGroup, false);
   dstrTaxType.strip().upperCase();

   if ( dstrContMatDateBasedOn == CMD_BASED_ON_USERDEFINED && dstrTaxType != I_("9") && dstrTaxType != I_("M"))//NO RESP
   {
      getField(ifds::ContractMaturityDate, dstrContractMaturityDate, idDataGroup,false);
      dstrContractMaturityDate.strip();

      DString dstrMinTerm;
      DString dstrMinAge;
      DString dstrMaxAge;

      getMasterMinTermAndMinMaxAge( dstrMinTerm, dstrMinAge, dstrMaxAge, idDataGroup);
      int intMaxAge  = dstrMaxAge.asInteger();
      int intMinAge  = dstrMinAge.asInteger();

      DString dstrDofBirth;
      getDofBirth(idDataGroup, dstrDofBirth);

      BFDate bfdDOB(dstrDofBirth, BFDate::DATE_FORMAT::DF_HOST);
      BFDate bfdMinCMD = bfdDOB;
      bfdMinCMD.addYears(intMinAge);

      BFDate bfdMaxCMD = bfdDOB;
      bfdMaxCMD.addYears(intMaxAge);

      BFDate bfdCMD(dstrContractMaturityDate, BFDate::DATE_FORMAT::DF_HOST);
      
      if(bfdCMD < bfdMinCMD || bfdCMD > bfdMaxCMD)
      {
         getErrMsg( IFASTERR::USER_DEFINED_MATURITY_DATE_SHOULD_BE_BETWEEN_MIN_MAX_AGE, 
            CND::ERR_USER_DEFINED_MATURITY_DATE_SHOULD_BE_BETWEEN_MIN_MAX_AGE, 
            CND::WARN_USER_DEFINED_MATURITY_DATE_SHOULD_BE_BETWEEN_MIN_MAX_AGE, 
            idDataGroup );
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************************
SEVERITY ContractInfo::ValidateUserDefinedMaturityDateGreaterThanMinTerm(const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateUserDefinedMaturityDateGreaterThanMinTerm" ) );
//User Defined CMD >= Contract Deff  + Min Term
   DString dstrContMatDateBasedOn;
   DString dstrContractMaturityDate;

   getField(ifds::ContractMatBasedOn, dstrContMatDateBasedOn, idDataGroup,false);
   dstrContMatDateBasedOn.strip().upperCase();

   if ( dstrContMatDateBasedOn == CMD_BASED_ON_USERDEFINED)
   {
      getField(ifds::ContractMaturityDate, dstrContractMaturityDate, idDataGroup,false);
      dstrContractMaturityDate.strip();

      DString dstrMinTerm;
      DString dstrMinAge;
      DString dstrMaxAge;

      getMasterMinTermAndMinMaxAge( dstrMinTerm, dstrMinAge, dstrMaxAge, idDataGroup);
      int intMinTerm  = dstrMinTerm.asInteger();

      DString dstrEffectiveDate;
      getField(ifds::EffectiveDate, dstrEffectiveDate, idDataGroup,false);
      dstrEffectiveDate.strip();

      BFDate bfdMinCMD(dstrEffectiveDate, BFDate::DATE_FORMAT::DF_HOST);
      bfdMinCMD.addYears(intMinTerm);

      BFDate bfdCMD(dstrContractMaturityDate, BFDate::DATE_FORMAT::DF_HOST);
      if(bfdCMD < bfdMinCMD)
      {
         getErrMsg( IFASTERR::USER_DEFINED_MATURITY_DATE_SHOULD_BE_GREATER_THAN_MIN_TERM, 
            CND::ERR_USER_DEFINED_MATURITY_DATE_SHOULD_BE_GREATER_THAN_MIN_TERM, 
            CND::WARN_USER_DEFINED_MATURITY_DATE_SHOULD_BE_GREATER_THAN_MIN_TERM, 
            idDataGroup );
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************************
SEVERITY ContractInfo::ValidateUserDefinedMaturityDateLessThanMaturityDate(const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "ValidateUserDefinedMaturityDateLessThanMaturityDate" ) );
//User Defined CMD <= LCMD

   DString dstrContMatDateBasedOn;
   DString dstrContractMaturityDate;

   getField(ifds::ContractMatBasedOn, dstrContMatDateBasedOn, idDataGroup,false);
   dstrContMatDateBasedOn.strip().upperCase();

   if ( dstrContMatDateBasedOn == CMD_BASED_ON_USERDEFINED)
   {
      getField(ifds::ContractMaturityDate, dstrContractMaturityDate, idDataGroup,false);
      dstrContractMaturityDate.strip();

      DString dstrLegalMaturityDate;
      getField(ifds::LegalMaturityDate, dstrLegalMaturityDate, idDataGroup,false);
      dstrLegalMaturityDate.strip();

      BFDate bfdMaxCMD(dstrLegalMaturityDate, BFDate::DATE_FORMAT::DF_HOST);

      BFDate bfdCMD(dstrContractMaturityDate, BFDate::DATE_FORMAT::DF_HOST);
      if(bfdCMD > bfdMaxCMD)
      {
         getErrMsg( IFASTERR::USER_DEFINED_MATURITY_DATE_LESS_THAN_MATURITY_DATE, 
            CND::ERR_USER_DEFINED_MATURITY_DATE_LESS_THAN_MATURITY_DATE, 
            CND::WARN_USER_DEFINED_MATURITY_DATE_LESS_THAN_MATURITY_DATE, 
            idDataGroup );
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY ContractInfo::getContractTypeAndVersion ( DString &dstrContractType, 
												   DString &dstrContractVer, 
												   const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
							CLASSNAME, 
							I_("getContractTypeAndVersion"));

	getField(ifds::ContractType, dstrContractType, idDataGroup);
	dstrContractType.stripAll().upperCase();

	getField(ifds::ContractVer, dstrContractVer, idDataGroup);
	dstrContractVer.stripAll();

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ContractInfo::getNMCRContract ( DString &dstrNMCRContract, 				
										 const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
							CLASSNAME, 
							I_("getNMCRContract"));

	//getField(ifds::NMCRContract, dstrNMCRContract, idDataGroup);

	BFAbstractCBO* pMasterContract = NULL;
	getMasterContract(pMasterContract, idDataGroup);

	if(pMasterContract)	{    
		pMasterContract->getField(ifds::NMCRContract, dstrNMCRContract, idDataGroup, false);
	}

	return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************************************
bool ContractInfo::isSingleLifeNMCR (const BFDataGroupId& idDataGroup)
{
	DString dstrNMCRContract, dstrGuaranteePayOption;

	getNMCRContract(dstrNMCRContract, idDataGroup);
	dstrNMCRContract.strip();

	//GuaranteePayOption: "" = Not NMCR, "05" = Single Female OR Single No Gender, "06" = Single Male, "07" = Joint
	getField(ifds::GuaranteePayOption , dstrGuaranteePayOption, idDataGroup); 
	dstrGuaranteePayOption.strip();

	if (dstrNMCRContract == YES && (dstrGuaranteePayOption == "05" || dstrGuaranteePayOption == "06")) 
	{
		return (true);
	}

	return (false);
}

//********************************************************************************************
bool ContractInfo::isElectedSingleLifeNMCR (const BFDataGroupId& idDataGroup)
{
	DString dstrIsElected;	

	bool bSingleLifeNMCR = isSingleLifeNMCR (idDataGroup);

	getField(ifds::IsElected, dstrIsElected, idDataGroup);
	dstrIsElected.strip();

	if (bSingleLifeNMCR && dstrIsElected == YES)
	{
		return (true);
	}

	return (false);
}

//********************************************************************************************
bool ContractInfo::hasSingleLifeNMCRMaster (const BFDataGroupId& idDataGroup)
{
	DString dstrNMCRContract, dstrGuaranteePayOption;
	BFAbstractCBO* pMasterContract = NULL;

	getMasterContract(pMasterContract, idDataGroup);

	if(pMasterContract)
	{    
		pMasterContract->getField(ifds::NMCRContract, dstrNMCRContract, idDataGroup, false);
		dstrNMCRContract.strip();

		pMasterContract->getField(ifds::GuaranteePayOption, dstrGuaranteePayOption, idDataGroup, false);	
		dstrGuaranteePayOption.strip();

		if (dstrNMCRContract == YES && (dstrGuaranteePayOption == "05" || dstrGuaranteePayOption == "06")) {
			return (true);
		}
	}

	return (false);     
}

//******************************************************************************
bool ContractInfo::validateAnnuitantGender (const BFDataGroupId& idDataGroup, DString &dstrGender)
{
	DString strAccountNum; 
	DString dstrEntityType;
	DString dstrEntityId; 
	bool bRtn = false;

	SEVERITY sevRtn = SEVERE_ERROR;
	_pMFAccount->getField( ifds::AccountNum, strAccountNum, idDataGroup );  

	AccountEntityXref *pAccountEntityXref;
	sevRtn = getWorkSession().getAccountEntityXref( BF::HOST, pAccountEntityXref );
	sevRtn = pAccountEntityXref->PopulateEntitiesList(  idDataGroup, strAccountNum );
	if( sevRtn >= WARNING || !pAccountEntityXref )
		return (false);

	BFObjIter iterAcctEntXRef( *pAccountEntityXref, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );
	DString searchKey;
	pAccountEntityXref->buildPartialKeyForAccount( searchKey, strAccountNum );

	for( iterAcctEntXRef.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey ); !iterAcctEntXRef.end(); ++iterAcctEntXRef )
	{
		iterAcctEntXRef.getObject( )->getField(ifds::EntityType, dstrEntityType, idDataGroup, false );     
		if( dstrEntityType.stripAll() ==  I_("05") )
		{
			// get annuitant's entityId
			iterAcctEntXRef.getObject( )->getField(ifds::EntityId, dstrEntityId, idDataGroup, false );
			break;
		}
	}

	if( dstrEntityId != NULL_STRING )
	{
		Entity *pEntity;
		sevRtn = getWorkSession().getEntity(  idDataGroup, dstrEntityId, pEntity );
		if( sevRtn <= WARNING && pEntity )
		{
			pEntity->getGender(dstrGender, idDataGroup);
			if( dstrGender != NULL_STRING)
				bRtn = true;
			else
				bRtn = false;
		}
	}

	return (bRtn);  
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ContractInfo.cpp-arc  $
 * 
 *    Rev 1.116   07 Aug 2012 17:51:48   if991250
 * IN3020460: Stopped overriding the ContractTypeId with the master one - Fix set ContractTypeId on contract type change
 * 
 *    Rev 1.115   03 Aug 2012 14:38:52   if991250
 * IN3020460: Stopped overriding the ContractTypeId with the master one
 * 
 *    Rev 1.114   Jul 04 2012 13:37:52   if991250
 * IN3013252 made ifds::FieldCrossEdit1with no IMMEDIATE_VALIDATION
 * 
 *    Rev 1.113   Jun 18 2012 17:35:26   if991250
 * IN2937065: new CMD Based on: User Defined Mat - Transfer
 * 
 *    Rev 1.112   May 25 2012 19:13:38   if991250
 * IN#2938847 Contract Information - User defined Maturity Date validation
 * 
 *    Rev 1.111   May 24 2012 12:03:22   dchatcha
 * IN#2883926 - Date format is not the same in UAT environment.
 * 
 *    Rev 1.110   Apr 20 2012 13:30:34   if991250
 * IN 2921758 filtering the CMD based on function of MinAge
 * 
 *    Rev 1.109   Apr 19 2012 14:31:10   if991250
 * Contract Info - CMD Based on is readonly if valid issue date, Type id ignored in linked contracts comparison
 * 
 *    Rev 1.108   Apr 18 2012 15:34:56   if991250
 * IN 2900126 - change error message when the linked contract is missing
 * 
 *    Rev 1.107   Apr 17 2012 21:40:06   popescu
 * Fixed bening crash when account does not have a portfolio attached in a portfolio active environment
 * 
 *    Rev 1.106   Apr 10 2012 16:19:48   if991250
 * IN 2900207 Contract Information
 * 
 *    Rev 1.105   Apr 02 2012 11:45:32   if991250
 * IN 2858958 - Contract info
 * 
 *    Rev 1.104   Apr 02 2012 10:25:08   if991250
 * IN 2858958 - Contract info
 * 
 *    Rev 1.103   Mar 30 2012 17:29:18   if991250
 * IN 2858958 - Contract info
 * 
 *    Rev 1.102   Mar 29 2012 13:56:50   if991250
 * IN 2858958 - Contract info
 * 
 *    Rev 1.101   Mar 27 2012 16:50:12   if991250
 * IN 2858958 - Contract info
 * 
 *    Rev 1.100   Mar 23 2012 17:11:30   if991250
 * IN 2894154 - filling in the contract term
 * 
 *    Rev 1.99   Mar 20 2012 14:14:10   jankovii
 * Sync up: IN 2845942 - Closing Period Term
 * 
 *    Rev 1.98   Mar 15 2012 20:18:24   jankovii
 * Sync up: IN 2845942 - Closing Period Term
 * 
 *    Rev 1.97   Feb 21 2012 13:43:24   dchatcha
 * Synch up: IN# 2848252 - P0186484 FN02 Seg Desktop - Contract Info Screen issues for non-IA
 * 
 *    Rev 1.96   Feb 20 2012 12:18:48   dchatcha
 * Synch up : IN# 2848252 - P0186484 FN02 Seg Desktop - Contract Info Screen issues for non-IA
 * 
 *    Rev 1.95   Feb 16 2012 13:57:30   dchatcha
 * Synch up: IN# 2848252 - P0186484 FN02 Seg Desktop - Contract Info Screen issues for non-IA
 * 
 *    Rev 1.94   Feb 15 2012 17:38:12   dchatcha
 * Synch up: IN# 2848252 - P0186484 FN02 Seg Desktop - Contract Info Screen issues for non-IA
 * 
 *    Rev 1.93   Feb 10 2012 18:16:24   dchatcha
 * Synch up: IN# 2837678 - REL12.2-PET0186484- New INA Contract Information screen issues as on 6 Feb 2012
 * 
 *    Rev 1.92   Feb 07 2012 18:43:44   dchatcha
 * Synch up: IN# 2837678 - REL12.2-PET0186484- New INA Contract Information screen issues as on 6 Feb 2012
 * 
 *    Rev 1.91   Feb 03 2012 19:20:06   dchatcha
 * Synch up: IN# 2799812 - Contract Screen Issues.
 * 
 *    Rev 1.90   Jan 30 2012 15:01:52   dchatcha
 * Synch up: IN# 2799812 - Contract Screen Issues.
 * 
 *    Rev 1.89   Jan 24 2012 16:32:56   dchatcha
 * Synch up : IN# 2799812 - Contract Screen issues.
 * 
 *    Rev 1.88   Jan 21 2012 09:26:44   dchatcha
 * IN# 2799812 - Contract Screen issues.
 * 
 *    Rev 1.87   Jan 18 2012 16:28:14   dchatcha
 * Synch up: IN# 2799812 - Contract Screen issues. Fix crashing during load contract infromation screen. caused by blank date fields.
 * 
 *    Rev 1.86   Jan 17 2012 17:53:20   dchatcha
 * Synch up : IN# 2799812 - Contract Screen issues. Fix crashing during load contract infromation screen. 
 * 
 *    Rev 1.85   Jan 16 2012 20:28:06   dchatcha
 * P0186484 - FN 05 - SEG Processing Screen
 * 
 *    Rev 1.84   Jan 16 2012 20:10:00   dchatcha
 * IN# 2799812 - Contract Screen issues.
 * 
 *    Rev 1.83   Dec 27 2011 00:55:26   dchatcha
 * P0186484 - FN 05 - work on Contract Information Screen
 * 
 *    Rev 1.82   May 14 2010 12:04:52   wichian
 * IN#2089234 - show all provinces in Province of Registration\After fixed
 * 
 *    Rev 1.81   06 Oct 2008 13:16:42   kovacsro
 * PET142007  FN01 TFSA
 * 
 *    Rev 1.80   12 Sep 2008 16:20:42   kovacsro
 * PET142007 FN01 - Tax Free Savings Account
 * 
 *    Rev 1.79   12 Sep 2008 15:40:52   kovacsro
 * PET142007.FN01 Tax Free Saving Account - code cleanup for taxType=0
 * 
 *    Rev 1.78   Jun 07 2006 09:48:10   porteanm
 * Incident 638453 - Error 450 for new CMD contract when no CMD.
 * 
 *    Rev 1.77   May 30 2006 18:00:18   ZHANGCEL
 * PET2102 FN01 -- Legal age related changes
 * 
 *    Rev 1.76   May 25 2006 17:47:50   ZHANGCEL
 * PET 2102 FN01 -- Legal age related changes with new view367
 * 
 *    Rev 1.75   May 02 2006 14:39:32   jankovii
 * PET 2102 Manulife Flex - User Defined Maturity Dates.
 * 
 *    Rev 1.74   Apr 20 2006 16:27:20   porteanm
 * PET2102 FN02 - For 71 - isGWOContract() returns false for R70.
 * 
 *    Rev 1.73   Apr 20 2006 16:15:34   porteanm
 * PET2102 FN02 - For 71 - Added isGWOContract() and isNewContract().
 * 
 *    Rev 1.72   Apr 03 2006 16:56:22   porteanm
 * Incident 528284 - Set ModPerm to Y for new contract.
 * 
 *    Rev 1.71   Feb 14 2006 14:11:42   zhengcon
 * Incident #528284 - add one field ModPerm for updatable permission of User Defined Maturity Date of converted account
 * 
 *    Rev 1.70   Nov 03 2005 15:34:32   porteanm
 * Incident 442910 - Contract Term - for a new record, reload Contract Term when Contract Type changed.
 * 
 *    Rev 1.69   Sep 29 2005 15:13:38   ZHANGCEL
 * PET1244 - FN01 -- Seg Fund Evolution Enhancement
 * 
 *    Rev 1.68   Sep 23 2005 18:23:00   ZHANGCEL
 * PET1244 FN01 -- Seg Func Evolution enhancement
 * 
 *    Rev 1.67   Sep 06 2005 11:07:36   porteanm
 * Incident 395858 - Misleading error message on the Contract Info screen.
 * 
 *    Rev 1.66   Aug 17 2005 16:26:06   porteanm
 * Incident 351033 - Removed view 131.
 * 
 *    Rev 1.65   Jun 14 2005 15:31:06   porteanm
 * PET1024 FN40 - Guarantee Adjustments.
 * 
 *    Rev 1.64   Mar 30 2005 15:19:10   hernando
 * PET1024 FN02 - Set Contract Maturity Date, Legal Maturity Date, Closing Decade Start Date, and Reduction Age Date to read only.
 * 
 *    Rev 1.63   Mar 16 2005 14:27:24   hernando
 * PET1024 FN02 - Removed MaturityType and UserMaturityDate.  Added ContractMaturityDate, CDStartDate, SegTransExist, and RedAgeDate.
 * 
 *    Rev 1.62   Nov 14 2004 14:29:54   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.61   Mar 21 2003 18:01:56   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.60   Jan 03 2003 14:51:50   FENGYONG
 * fix validation of duplicate record.
 * 
 *    Rev 1.59   Oct 09 2002 23:54:08   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.58   Aug 29 2002 12:55:12   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.57   Aug 13 2002 15:09:46   HSUCHIN
 * removed condition from loadProvin...
 * 
 *    Rev 1.56   Jul 17 2002 14:44:58   HSUCHIN
 * some code cleanup and doinitwithdefaultvalues now initializes the stop date and user maturity date
 * 
 *    Rev 1.55   Jul 15 2002 16:19:32   HSUCHIN
 * code clean up - got rid of unused code and commented out code
 * 
 *    Rev 1.54   Jul 15 2002 16:08:42   HSUCHIN
 * no change - beautify source
 * 
 *    Rev 1.53   Jun 20 2002 14:42:54   HSUCHIN
 * potential date bug fix
 * 
 *    Rev 1.52   May 30 2002 16:12:28   ZHANGCEL
 * Syn up to 1.49.1.0
 * 
 *    Rev 1.51   May 28 2002 12:18:38   PURDYECH
 * BFData Implementation - Phase II
 * 
 *    Rev 1.50   22 May 2002 18:26:40   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.49   Apr 26 2002 13:21:18   YINGBAOL
 * fix creating SlsRep issue --PTS70007963
 * 
 *    Rev 1.48   Mar 14 2002 16:40:00   ZHANGCEL
 * minor changes
 * 
 *    Rev 1.47   Nov 20 2001 15:22:40   ZHANGCEL
 * reverse change haspermission 
 * 
 *    Rev 1.46   Nov 20 2001 14:56:58   ZHANGCEL
 * Many changes for Multple Contract
 * 
 *    Rev 1.45   Nov 15 2001 10:05:32   ZHANGCEL
 * Milestone check in
 * 
 *    Rev 1.44   Nov 14 2001 11:46:42   ZHANGCEL
 * Many changes for Multiple Contracts
 * 
 *    Rev 1.43   Nov 07 2001 14:35:00   ZHANGCEL
 * Many changes for multiple Contracts
 * 
 *    Rev 1.42   26 Oct 2001 11:07:38   SMITHDAV
 * hasPermission changes
 * 
 *    Rev 1.41   24 Oct 2001 15:44:56   HSUCHIN
 * bug fix to save the Effective date on init to the data field PrevEffectiveDate so that the original effective date can be extracted in the transaction builder
 * 
 *    Rev 1.40   Oct 19 2001 11:44:04   ZHANGCEL
 * Fixed the bug in the ValidateEffectiveDate()
 * 
 *    Rev 1.39   18 Oct 2001 13:58:10   HSUCHIN
 * removed duplicate validation.  The list will now perform this check
 * 
 *    Rev 1.38   Aug 10 2001 11:42:26   OLTEANCR
 * added new validation for EffectiveDate
 * 
 *    Rev 1.37   05 Aug 2001 18:20:10   WINNIE
 * correct contracttypeid assignment
 * 
 *    Rev 1.36   05 Aug 2001 11:36:16   YINGZ
 * fix delete bug
 * 
 *    Rev 1.35   Aug 03 2001 13:57:50   OLTEANCR
 * temporary fix for birth date validation
 * 
 *    Rev 1.34   Jul 30 2001 14:22:16   OLTEANCR
 * modif. setDefault( )
 * 
 *    Rev 1.33   Jul 30 2001 09:34:00   OLTEANCR
 * added ValidateContractType( )
 * 
 *    Rev 1.32   Jul 20 2001 09:09:16   JANKAREN
 * Bug fix for gettting the account effective date
 * 
 *    Rev 1.31   Jul 16 2001 19:12:16   OLTEANCR
 * added logic for multi-contract
 * 
 *    Rev 1.30   Jul 09 2001 11:49:46   ZHANGCEL
 * Fixed the crash in LoadProvinceSubstitutionList()
 * 
 *    Rev 1.29   Jun 26 2001 12:55:02   PURDYECH
 * Infrastructure Release 1.9 Integration.
 * 
 *    Rev 1.28   10 May 2001 11:37:08   HSUCHIN
 * Session Management restructuring and SSB Sync up
 * 
 *    Rev 1.27   May 04 2001 14:08:32   DINACORN
 * Modified loadProvinceSubstitutionList(); removed getDescription(), getSubstList() for using DSTCommonFunctions methods
 * 
 *    Rev 1.26   May 02 2001 15:55:18   OLTEANCR
 * no change
 * 
 *    Rev 1.25   Dec 17 2000 20:22:48   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.24   Dec 07 2000 10:02:50   ZHANGCEL
 * Added "  if (getAgentList( idDataGroup, pAgentList ) <= WARNING ) " logic  into LoadProvinceSubstitutionList()  in order to avoid crashing when the getAgentList() returns severity error.
 * 
 *    Rev 1.23   Nov 09 2000 11:08:34   ZHANGCEL
 * Added MaturityTypeDesc and StatusDesc into classFieldInfo[].
 * 
 *    Rev 1.22   Nov 06 2000 15:45:48   ZHANGCEL
 * Change the setDefault Value to fixed the bug about salesrep problem.
 * 
 *    Rev 1.21   Oct 31 2000 10:16:18   DINACORN
 * Substitution list for"ProvinceCanada" based on "SegLicenceProvList"
 * 
 *    Rev 1.20   Oct 24 2000 11:08:56   KOVACSRO
 * Handled TaxTypes for which legal age cannot be calculated.
 * 
 *    Rev 1.19   Oct 22 2000 15:13:58   WINNIE
 * Assign PrevEffectiveDate
 * 
 *    Rev 1.18   Oct 20 2000 13:58:06   KOVACSRO
 * Enabled fields for new ContractInfo (so that the user can change them in NASU)
 * 
 *    Rev 1.17   Oct 19 2000 17:23:16   KOVACSRO
 * Bug fixed.
 * 
 *    Rev 1.16   Oct 17 2000 14:38:32   KOVACSRO
 * Modified CheckOldestLegalDate() in order to use lDataGroup.
 * 
 *    Rev 1.15   Oct 13 2000 13:46:00   ZHANGCEL
 * Debug fixed
 * 
 *    Rev 1.14   Oct 02 2000 12:06:28   ZHANGCEL
 * Added a condition for Province validation
 * 
 *    Rev 1.13   Sep 21 2000 14:42:08   ZHANGCEL
 * Bug fixed
 * 
 *    Rev 1.12   Sep 20 2000 14:23:06   ZHANGCEL
 * Debug
 * 
 *    Rev 1.11   Aug 22 2000 11:14:32   ZHANGCEL
 * fine tune
 * 
 *    Rev 1.10   Jul 28 2000 16:43:40   ZHANGCEL
 * Add a new error conditon
 * 
 *    Rev 1.9   Jul 26 2000 11:06:28   ZHANGCEL
 * Added some code for EffectivaDate and StopDate validation
 * 
 *    Rev 1.8   Jun 26 2000 14:13:32   ZHANGCEL
 * Leap Year stuffs
 * 
 *    Rev 1.7   May 18 2000 15:44:28   ZHANGCEL
 * Date culculate stuffs
 * 
 *    Rev 1.6   May 12 2000 17:47:16   ZHANGCEL
 * Move CheckDofBirth function from GUI to CBO
 *
 */
