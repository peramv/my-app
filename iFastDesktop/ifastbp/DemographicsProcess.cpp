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
//    Copyright 1999 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : DemographicsProcess.cpp
// ^AUTHOR : 
// ^DATE   : 03/09/1999
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : DemographicsProcess
//    This class manages the demographics information.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "demographicsprocess.hpp"
#include <ifastcbo\demographics.hpp>
#include "demographicsprocessincludes.h"
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\shareholder.hpp>
#include <ifastcbo\Entity.hpp>
#include <ifastcbo\errmsgruleslist.hpp>
#include <ifastcbo\mgmtco.hpp>


extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_DEMOGRAPHICS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_DEMOGRAPHICS;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< DemographicsProcess > processCreator( CMD_BPROC_DEMOGRAPHICS );

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME            = I_( "DemographicsProcess" );
   const I_CHAR * const SHAREHOLDER_NUM      = I_( "ShrNum" );
   const I_CHAR * const ACCOUNT_NUM          = I_( "AccountNum" );
   const I_CHAR * const FULL_REFRESH         = I_( "FullRefresh" );
   const I_CHAR * const PARTIAL_REFRESH      = I_( "PartialRefresh" );
   const I_CHAR * const YES                  = I_( "Y" );
   const I_CHAR * const NO                   = I_( "N" );
   const I_CHAR * const CALLER               = I_( "Caller" );
   const I_CHAR * const ENTITY               = I_( "Entity" );
   const I_CHAR * const ACCT                 = I_( "Acct" );
   const I_CHAR * const ENTITY_ID            = I_( "EntityId");
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
   extern CLASS_IMPORT const long BP_ERR_INVALID_METHOD_CALL;
   extern const long BP_ERR_DEMOGRAPHICS_DATA_REQUIRED;
   extern const long BP_WARN_DEMOGRAPHICS_DATA_REQUIRED;
}

namespace ifds
{
   extern CLASS_IMPORT const BFDecimalFieldId TotPercentage;
   extern CLASS_IMPORT const BFTextFieldId HouseBroker;
   extern CLASS_IMPORT const BFTextFieldId AgentCode;

   extern CLASS_IMPORT const BFTextFieldId TypeOfInvestor;
   extern CLASS_IMPORT const BFTextFieldId InvestingOnBehalf;
   extern CLASS_IMPORT const BFTextFieldId SourceOfIncome;
   extern CLASS_IMPORT const BFTextFieldId InitialPayment;
   extern CLASS_IMPORT const BFTextFieldId PowerOfAttorney;
   extern CLASS_IMPORT const BFTextFieldId ComplianceCode;
   extern CLASS_IMPORT const BFTextFieldId CountryCode;
   extern CLASS_IMPORT const BFTextFieldId RegStandardName;
   extern CLASS_IMPORT const BFTextFieldId RegStandardId;

   extern CLASS_IMPORT const BFTextFieldId LastName;
   extern CLASS_IMPORT const BFTextFieldId FirstName;

   extern CLASS_IMPORT const BFTextFieldId SrcOfPymtSalary;
   extern CLASS_IMPORT const BFTextFieldId SrcOfPymtBusinessIncome;
   extern CLASS_IMPORT const BFTextFieldId SrcOfPymtBorrowedFunds;
   extern CLASS_IMPORT const BFTextFieldId SrcOfPymtGiftedFunds;
   extern CLASS_IMPORT const BFTextFieldId SrcOfPymtPrcdsFrmDeathBenefEstate;
   extern CLASS_IMPORT const BFTextFieldId SrcOfPymtSocialBenefits;
   extern CLASS_IMPORT const BFTextFieldId SrcOfPymtOther;
   extern CLASS_IMPORT const BFTextFieldId SrcOfPymtOtherReason;
   extern CLASS_IMPORT const BFTextFieldId SrcOfPymtExistingInvstAccount;
   extern CLASS_IMPORT const BFTextFieldId SrcOfPymtOwnerSavings;
   extern CLASS_IMPORT const BFTextFieldId SrcOfPymtSaleOfProperty;
   extern CLASS_IMPORT const BFTextFieldId SrcOfPymtPensionIncome;
   extern CLASS_IMPORT const BFTextFieldId SrcOfPymtInheritedFunds;
   extern CLASS_IMPORT const BFTextFieldId SolicitPublicContrib;
   extern CLASS_IMPORT const BFTextFieldId KYCBusinessType;
   extern CLASS_IMPORT const BFTextFieldId KYCLegalForm;
}

namespace AUDITTYPE
{
   extern CLASS_IMPORT I_CHAR * const KYC;
}

namespace NASULIT //nasu literals
{
   extern const I_CHAR * const CREATING_ACCOUNT;
   extern const I_CHAR * const CREATING_SHAREHOLDER;
}

namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const DEMOGRAPHICS_DATA_REQUIRED;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319DemographicsProcess::DemographicsProcess() : _rpChildGI( 0 )
DemographicsProcess::DemographicsProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _dstrEntityId( NULL_STRING )
, _dstrNewShareholder( NULL_STRING )
, _dstrNewAccount( NULL_STRING )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::MFACCOUNT_CBO, false, BF::NullContainerId, true  );
   addContainer( IFASTBP_PROC::DEMOGRAPHICS_CBO, false, IFASTBP_PROC::MFACCOUNT_CBO, true, I_("Demographics") );
   addContainer( IFASTBP_PROC::REGULATORY_STANDARD_LIST, false, IFASTBP_PROC::MFACCOUNT_CBO, true, I_("RegulatoryStandards") );

   //addFieldDetails( SHAREHOLDER_NUM_, DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::BirthDate,               IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::Gender,                  IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::MaritalCode,             IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::MaritalDesc,             IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::Employer,                IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::EmployedYrs,             IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::IndustryCode,            IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::IndustryDesc,            IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::OccupationCode,          IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::OccupationDesc,          IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::AnnualIncomeCode,        IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::AnnualIncomeDesc,        IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::NetWorthCode,            IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::NetWorthDesc,            IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::InvObjCode,              IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::InvObjDesc,              IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::InvKnowledgeCode,        IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::InvKnowledgeDesc,        IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::InvHorizonCode,          IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::InvHorizonDesc,          IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::RiskToleranceCode,       IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::RiskToleranceDesc,       IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::OtherInvestments,        IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::AdvisorCode,             IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::AdvisorDesc,             IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::WitnessName,             IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::WitnessAddr1,            IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::WitnessAddr2,            IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::EffectiveDate,           IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::ProcessDate,             IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::PersonalSecCode,         IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::PrimMstrVer,             IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::PrimMstrRid,             IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::ModUser,                 IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::ModDate,                 IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::Username,                IFASTBP_PROC::DEMOGRAPHICS_CBO );

   addFieldDetails( ifds::InvestPhilosophyCode,    IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::OccupationFreeFormat,    IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::GrowthPercent,           IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::SafetyPercent,           IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::IncomePercent,           IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::SAMFinHealthCode,        IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::TypeOfBusFreeFormat,     IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::MemorablePlace,          IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::MemorableWord,           IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::MemorableDate,           IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::BranchCode,              IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::AgentCode,               IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::BranchName,              IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::SlsrepName,              IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::KYCComment,              IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::EmploymentType,          IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::ResidenceType,           IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::ResAmount,               IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::KYCMailedDate,           IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::AnnualIncomeAmount,      IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::IncomeLevelDate,         IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::NetWorthAmount,          IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::NetWorthDate,            IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::RefferalCode,            IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::ReferenceName,           IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::SpecialtyCode,           IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::TolerancePrcnt,          IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::ShortTermPrcnt,          IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::AggressivePrcnt,         IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::PrcntDate,               IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::KYCRID,                  IFASTBP_PROC::DEMOGRAPHICS_CBO );

   addFieldDetails (ifds::TypeOfInvestor,          IFASTBP_PROC::DEMOGRAPHICS_CBO);
   addFieldDetails (ifds::InvestingOnBehalf,       IFASTBP_PROC::DEMOGRAPHICS_CBO);
   addFieldDetails (ifds::SourceOfIncome,          IFASTBP_PROC::DEMOGRAPHICS_CBO);
   addFieldDetails (ifds::InitialPayment,          IFASTBP_PROC::DEMOGRAPHICS_CBO);
   addFieldDetails (ifds::PowerOfAttorney,         IFASTBP_PROC::DEMOGRAPHICS_CBO);
   addFieldDetails (ifds::ComplianceCode,          IFASTBP_PROC::DEMOGRAPHICS_CBO);
   addFieldDetails (ifds::RegulatoryStandard,      IFASTBP_PROC::DEMOGRAPHICS_CBO);
   addFieldDetails (ifds::RegStandardName,         IFASTBP_PROC::DEMOGRAPHICS_CBO);
   addFieldDetails (ifds::CountryCode,             IFASTBP_PROC::DEMOGRAPHICS_CBO);
   addFieldDetails (ifds::RegulatoryCountryCode,   IFASTBP_PROC::DEMOGRAPHICS_CBO);

   addFieldDetails( ifds::RegStandardName,         IFASTBP_PROC::REGULATORY_STANDARD_LIST);
   addFieldDetails( ifds::RegStandardId,           IFASTBP_PROC::REGULATORY_STANDARD_LIST);

   addFieldDetails (ifds::SuppressKYCLetter,       IFASTBP_PROC::DEMOGRAPHICS_CBO);
   addFieldDetails (ifds::NumOfDependents,         IFASTBP_PROC::DEMOGRAPHICS_CBO);
   addFieldDetails (ifds::AssociateCorpName1,      IFASTBP_PROC::DEMOGRAPHICS_CBO);
   addFieldDetails (ifds::AssociateCorpName2,      IFASTBP_PROC::DEMOGRAPHICS_CBO);
   addFieldDetails (ifds::AssociateCorpName3,      IFASTBP_PROC::DEMOGRAPHICS_CBO);
   addFieldDetails (ifds::AssociateCorpName4,      IFASTBP_PROC::DEMOGRAPHICS_CBO);
   addFieldDetails (ifds::AssociateCorpName5,      IFASTBP_PROC::DEMOGRAPHICS_CBO);
   addFieldDetails (ifds::AssociateCorpName6,      IFASTBP_PROC::DEMOGRAPHICS_CBO);
   addFieldDetails (ifds::AssociateCorpName7,      IFASTBP_PROC::DEMOGRAPHICS_CBO);
   addFieldDetails (ifds::AssociateCorpName8,      IFASTBP_PROC::DEMOGRAPHICS_CBO);
   addFieldDetails (ifds::AssociateCorpName9,      IFASTBP_PROC::DEMOGRAPHICS_CBO);
   addFieldDetails (ifds::AssociateCorpName10,     IFASTBP_PROC::DEMOGRAPHICS_CBO);

   addFieldDetails (ifds::RoleInCorp1,             IFASTBP_PROC::DEMOGRAPHICS_CBO);
   addFieldDetails (ifds::RoleInCorp2,             IFASTBP_PROC::DEMOGRAPHICS_CBO);
   addFieldDetails (ifds::RoleInCorp3,             IFASTBP_PROC::DEMOGRAPHICS_CBO);
   addFieldDetails (ifds::RoleInCorp4,             IFASTBP_PROC::DEMOGRAPHICS_CBO);
   addFieldDetails (ifds::RoleInCorp5,             IFASTBP_PROC::DEMOGRAPHICS_CBO);
   addFieldDetails (ifds::RoleInCorp6,             IFASTBP_PROC::DEMOGRAPHICS_CBO);
   addFieldDetails (ifds::RoleInCorp7,             IFASTBP_PROC::DEMOGRAPHICS_CBO);
   addFieldDetails (ifds::RoleInCorp8,             IFASTBP_PROC::DEMOGRAPHICS_CBO);
   addFieldDetails (ifds::RoleInCorp9,             IFASTBP_PROC::DEMOGRAPHICS_CBO);
   addFieldDetails (ifds::RoleInCorp10,            IFASTBP_PROC::DEMOGRAPHICS_CBO);
   
   addFieldDetails( ifds::KYCInfoFormat,           IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::ProfileNum,              IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::RefNum,                  IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::ProfileValue,            IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::LastReviewDate,          IFASTBP_PROC::DEMOGRAPHICS_CBO );            

   addFieldDetails( ifds::SolicitPublicContrib,                      IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::SrcOfPymtSalary,                     IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::SrcOfPymtBusinessIncome,             IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::SrcOfPymtBorrowedFunds,              IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::SrcOfPymtGiftedFunds,                IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::SrcOfPymtPrcdsFrmDeathBenefEstate,   IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::SrcOfPymtSocialBenefits,             IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::SrcOfPymtExistingInvstAccount,       IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::SrcOfPymtOwnerSavings,               IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::SrcOfPymtSaleOfProperty,             IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::SrcOfPymtPensionIncome,              IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::SrcOfPymtInheritedFunds,             IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::SrcOfPymtOther,                      IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::SrcOfPymtOtherReason,                IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::KYCBusinessType,                     IFASTBP_PROC::DEMOGRAPHICS_CBO );
   addFieldDetails( ifds::KYCLegalForm,                        IFASTBP_PROC::DEMOGRAPHICS_CBO );

   addFieldDetails( ifds::HouseBroker,             BF::NullContainerId, SUBCLASS_PROCESS );

   addFieldDetails( ifds::AccountNum,              IFASTBP_PROC::MFACCOUNT_CBO );

   addFieldDetails( ifds::ShrNum,                  BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( PRIMARY_ACCOUNT_OWNER,         BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( ifds::TotPercentage,           BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( ifds::BrokerCode,              BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( ifds::RepByBranch,             BF::NullContainerId, SUBCLASS_PROCESS );

   addFieldDetails( ENTITY_LAST_NAME,              BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( ENTITY_FIRST_NAME,             BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( DEMO_ENTITY_ID,                BF::NullContainerId, SUBCLASS_PROCESS );
}

//******************************************************************************

DemographicsProcess::~DemographicsProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************

void DemographicsProcess::doGetField(
                                    const GenericInterface *rpGICaller,
                                    const BFContainerId& idContainer,
                                    const BFFieldId& idField,
                                    const BFDataGroupId& idDataGroup,
                                    DString &strValueOut,
                                    bool bFormatted
                                    ) const
{
   if( idField == ifds::ShrNum )
   {
      strValueOut = _dstrShrNum;
   }
   else if( idField == PRIMARY_ACCOUNT_OWNER )
   {
      strValueOut = _dstrPrimaryShareholer;
   }
   else if ( idField == ENTITY_LAST_NAME || idField == ENTITY_FIRST_NAME )
   {
      strValueOut = NULL_STRING;

      DString strEntityId;
      strEntityId = _dstrEntityId;

      Entity *pEntity = NULL;
      dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getEntity( idDataGroup, strEntityId, pEntity );

      if ( pEntity )
      {
         DString strFieldValue;
         if ( idField == ENTITY_LAST_NAME )
         {
            pEntity->getField ( ifds::LastName, strFieldValue, idDataGroup, true );
         }
         else // idField == ENTITY_FIRST_NAME
         {
            pEntity->getField ( ifds::FirstName, strFieldValue, idDataGroup, true );
         }

         strValueOut = strFieldValue;
      }
   }
   else if( idField == ifds::TotPercentage )
   {

      DString dstrGrowthPcnt, dstrIncomePcnt, dstrSafetyPcnt, dstrShortTermPrcnt, dstrAggressivePrcnt;

      const_cast <DemographicsProcess*> (this)->getField( this, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::GrowthPercent, dstrGrowthPcnt );
      const_cast <DemographicsProcess*> (this)->getField( this, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::IncomePercent, dstrIncomePcnt );
      const_cast <DemographicsProcess*> (this)->getField( this, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::SafetyPercent, dstrSafetyPcnt );
      const_cast <DemographicsProcess*> (this)->getField( this, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::ShortTermPrcnt, dstrShortTermPrcnt );
      const_cast <DemographicsProcess*> (this)->getField( this, IFASTBP_PROC::DEMOGRAPHICS_CBO, ifds::AggressivePrcnt, dstrAggressivePrcnt );

      double dGrowthPcnt      = DSTCommonFunctions::convertToDouble(dstrGrowthPcnt);
      double dIncomePcnt      = DSTCommonFunctions::convertToDouble(dstrIncomePcnt);
      double dSafetyPcnt      = DSTCommonFunctions::convertToDouble(dstrSafetyPcnt);
      double dShortTermPrcnt  = DSTCommonFunctions::convertToDouble(dstrShortTermPrcnt);
      double dAggressivePrcnt = DSTCommonFunctions::convertToDouble(dstrAggressivePrcnt);

      double dTotalPcnt  = dGrowthPcnt + dIncomePcnt + dSafetyPcnt + dShortTermPrcnt + dAggressivePrcnt;

      strValueOut = DSTCommonFunctions::doubleToDString(ifds::TotPercentage, dTotalPcnt);
   } else if (idField == ifds::HouseBroker) {
      DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      MFAccount* pMFAccount = NULL;
      if ( dstcWorkSession ) {
         dstcWorkSession->getMFAccount( getDataGroupId( ), _dstrAcctNum, pMFAccount );
         if ( pMFAccount ) {
            strValueOut = pMFAccount->isHouseBroker ( idDataGroup )?YES:NO;
         }
      }
   } else if ( idField == ifds::BrokerCode ) {
      MFAccount* pMFAccount = NULL;
      DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      if ( dstcWorkSession ) {
         dstcWorkSession->getMFAccount( idDataGroup, _dstrAcctNum, pMFAccount );
         if ( pMFAccount ) {
            pMFAccount->getField ( ifds::BrokerCode, strValueOut, idDataGroup );
         }
      }
   } else if ( idField == ifds::RepByBranch ) {
      DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      if ( dstcWorkSession ) {
         DString dstrRepByBranch;
         dstcWorkSession->getOption( ifds::RepByBranch, strValueOut, idDataGroup, false );      
      }
   }
   else
   {
      assert( 0 );   
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETFIELD,
                      CND::BP_ERR_INVALID_METHOD_CALL );
   }
}

//******************************************************************************
SEVERITY DemographicsProcess::doSetField(
                                          const GenericInterface *rpGICaller, 
                                          const BFContainerId& idContainer,
                                          const BFFieldId& idField, 
                                          const BFDataGroupId& idDataGroup, 
                                          const DString& strValueOut, 
                                          bool bFormatted
                                         )
{  
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOSETFIELD );

   if ( idContainer == BF::NullContainerId )
   {
      if ( idField == DEMO_ENTITY_ID ) 
      {
         _dstrEntityId = strValueOut;
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

SEVERITY DemographicsProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );

   DString strCaller;

   getParameter( ACCOUNT_NUM, _dstrAcctNum );
   getParameter( ENTITY_ID, _dstrEntityId );
   getParameter( CALLER, strCaller );

   getParameter (NASULIT::CREATING_SHAREHOLDER, _dstrNewShareholder);
   getParameter (NASULIT::CREATING_ACCOUNT, _dstrNewAccount);

   SEVERITY sevRtn;

   try
   {
      DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

      Demographics* pDemographics = NULL;
      MFAccount* pMFAccount = NULL;

      if ( _dstrEntityId != NULL_STRING && _dstrEntityId != I_( "0" ) )
      {
         Entity *pEntity = NULL;

         if ( dstcWorkSession->getEntity( getDataGroupId( ), _dstrEntityId, pEntity ) < WARNING && 
            pEntity != NULL )
         {
            sevRtn = pEntity->getDemographicsList( pDemographics, getDataGroupId( ) );

            if( sevRtn > WARNING )
               return(GETCURRENTHIGHESTSEVERITY());
         }

         setContainer( IFASTBP_PROC::DEMOGRAPHICS_CBO,  pDemographics );
      }
      else
      {
         sevRtn = dstcWorkSession->getMFAccount( getDataGroupId( ), _dstrAcctNum, pMFAccount );
         if( sevRtn > WARNING )
            return(GETCURRENTHIGHESTSEVERITY());

         pMFAccount->getField( ifds::ShrNum, _dstrShrNum, getDataGroupId(), false);
         _dstrShrNum.strip().stripLeading( I_CHAR( '0' ) );

         Shareholder* pShareholder = NULL;
         sevRtn = dstcWorkSession->getShareholder( getDataGroupId(), _dstrShrNum, pShareholder );
         if( sevRtn > WARNING )
            return(GETCURRENTHIGHESTSEVERITY());

         Demographics* pDemographics = NULL;
         sevRtn = pMFAccount->getDemographicsList( pDemographics, getDataGroupId() );
         if( sevRtn > WARNING )
            return(GETCURRENTHIGHESTSEVERITY());

         setContainer( IFASTBP_PROC::MFACCOUNT_CBO,     pMFAccount );
         setContainer( IFASTBP_PROC::DEMOGRAPHICS_CBO,  pDemographics );

         getEntityName(getDataGroupId(), _dstrAcctNum, _dstrPrimaryShareholer);
      }
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool DemographicsProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_DEMOGRAPHICS );
}

//******************************************************************************
bool DemographicsProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );
   DString strNewAccountNumber;

   try
   {
      assert( _rpChildGI && isValidModelessInterface( _rpChildGI ) );
      getParameter( ACCOUNT_NUM, strNewAccountNumber );

      if( strNewAccountNumber != _dstrAcctNum )
      {
// TODO - need check for changes in progress ??
         _dstrAcctNum = strNewAccountNumber;
         setContainer( IFASTBP_PROC::MFACCOUNT_CBO, NULL );
         setContainer( IFASTBP_PROC::DEMOGRAPHICS_CBO, NULL );
         _rpChildGI->refresh( this, FULL_REFRESH );
      }
      return(_rpChildGI->modelessSetFocus( rpGICaller ));
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOMODELESSSETFOCUS,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(false);
}

//******************************************************************************
E_COMMANDRETURN DemographicsProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      if( isXMLAPIContext() )
      {
         rtn = CMD_MODELESS_INPROCESS;
      }
      else
      {
         if ( _dstrEntityId == NULL_STRING || _dstrEntityId == I_( "0" ) )
         {
            setParameter( CALLER, ACCT );
         }
         else
         {
            setParameter( CALLER, ENTITY );
            setParameter( ENTITY_ID, _dstrEntityId );
         }

         rtn = invokeCommand( this, CMD_GUI_DEMOGRAPHICS, getProcessType(),
                              isModal(), &_rpChildGI );
      }
   }
   catch( ConditionException &ce )
   {
      assert( 0 );
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return(rtn);
}

//******************************************************************************
SEVERITY DemographicsProcess::doValidateAll ( BFAbstractCBO *rpWSD,
                                              const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, 
                           CLASSNAME, 
                           I_("doValidateAll"));

   DSTCWorkSession *pDSTCWorkSession = 
      dynamic_cast<DSTCWorkSession *> (getBFWorkSession ());

   BFAbstractCBO * pDemographics = getCBOItem ( IFASTBP_PROC::DEMOGRAPHICS_CBO, 
                                                idDataGroup);
   if (pDemographics)
   {
      pDemographics->validateAll (idDataGroup);
   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
void *DemographicsProcess::getPtrForContainer (const BFContainerId& idContainer,
   const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("getPtrForContainer") );

   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   if( idContainer == IFASTBP_PROC::DEMOGRAPHICS_CBO )
   {
      MFAccount  *pMFAccount = NULL;
      Demographics *rpDemographics = NULL;

      if( dstcWorkSession->getMFAccount( getDataGroupId( ), _dstrAcctNum, pMFAccount ) <= WARNING )
      {
         pMFAccount->getDemographicsList( rpDemographics, idDataGroup );
      }
      // rpDemographics will be NULL if any failure
      return(rpDemographics);
   }
   else if( idContainer == IFASTBP_PROC::MFACCOUNT_CBO )
   {
      MFAccount *rpMFAccount = NULL;

      dstcWorkSession->getMFAccount( idDataGroup, _dstrAcctNum, rpMFAccount );
      if( rpMFAccount != NULL )
      {  // Save share holder number
         rpMFAccount->getField( ifds::ShrNum, _dstrShrNum, BF::HOST );
         _dstrShrNum.strip().stripLeading( I_CHAR( '0' ) );
      }
      // rpMFAccount will be NULL if failed
      return(rpMFAccount);
   }
   return(NULL);
}

//******************************************************************************
void DemographicsProcess::getEntityName( const BFDataGroupId& idDataGroup, 
                                         DString& dstrAcctNum, DString &_dstrPrimaryShareholer)
{
   dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->
      getFirstSequenced01AccountholderEntityName(idDataGroup, dstrAcctNum, 
      _dstrPrimaryShareholer);
}

//******************************************************************************
bool DemographicsProcess::doOk (GenericInterface* rpGICaller)
{

   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, I_( "doOk" ) );
   
   //if demographics object was updated and to force a refresh on the 
   //shareholder and account object, 
   //we should dirty the shareholder object at the host level,
   //
   //this is due to the fact that Demographcis object doesn't belong to Shareholder, 
   //and the Demographics view updates the Shareholder table on the back-end

   //get the shareholder
   BFDataGroupId idDataGroup = getDataGroupId();
   Shareholder* pShareholder = NULL;
   MFAccount *pMFAccount = NULL;
   DSTCWorkSession* pDSTCWorkSession = 
      dynamic_cast<DSTCWorkSession *> (getBFWorkSession ());
   
   if (pDSTCWorkSession &&
       pDSTCWorkSession->getShareholder (idDataGroup, 
         _dstrShrNum, pShareholder) <= WARNING && 
      pShareholder &&
      pDSTCWorkSession->getMFAccount (idDataGroup, 
      _dstrAcctNum, pMFAccount) &&
      pMFAccount)
   {
      BFAbstractCBO *rpPtr = getCBOItem (IFASTBP_PROC::DEMOGRAPHICS_CBO, idDataGroup);

      if (rpPtr->hasNonHostUpdates())
      {
         pShareholder->refreshMe (true); //refresh shareholder
         pMFAccount->refreshMe (true); //refresh mfaccount
      }
      else
      {
         if( _dstrNewShareholder.stripAll().upperCase() == I_("Y") || 
             _dstrNewAccount.stripAll().upperCase()     == I_("Y") )
         {
            DString strErrValue;
            ErrMsgRulesList* pErrMsgRulesList = NULL;
            pDSTCWorkSession->getMgmtCo().getErrMsgRulesList( pErrMsgRulesList );
            
            if( pErrMsgRulesList )
            {
               pErrMsgRulesList->getEWIValue( IFASTERR::DEMOGRAPHICS_DATA_REQUIRED , 
                                              idDataGroup, 
                                              strErrValue );

               strErrValue.strip().upperCase();
               if( strErrValue == I_("E") )
               {
                  ADDCONDITIONFROMFILE (CND::BP_ERR_DEMOGRAPHICS_DATA_REQUIRED);
               }
               else if ( strErrValue == I_("W") )
               {
                  ADDCONDITIONFROMFILE (CND::BP_WARN_DEMOGRAPHICS_DATA_REQUIRED);
               }
            }
            else
            {
               assert(0);
            }
         }
      }
   }
   //return true;//always, go ahead with processing   
   return GETCURRENTHIGHESTSEVERITY () <= WARNING;
}

//******************************************************************************
SEVERITY DemographicsProcess::getHistoricalParameters(
   const BFContainerId &idContainer, 
   BFFieldId &recordIdField, 
   DString &tableId, 
   DString &dstrKeys) 
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS);
   
   if (idContainer == IFASTBP_PROC::DEMOGRAPHICS_CBO)
   {
      recordIdField = ifds::KYCRID;
      tableId = AUDITTYPE::KYC;
      getField( this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::AccountNum, dstrKeys, false );
   }
   else 
   {
      assert(0);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************

SEVERITY DemographicsProcess::getHistoricalParameters( 
   const BFContainerId& idContainer, 
   HISTORICAL_VECTOR &vectorHistorical )
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Private Methods
//******************************************************************************

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/DemographicsProcess.cpp-arc  $
 * 
 *    Rev 1.36   Sep 16 2011 06:31:32   kitticha
 * PETP0186486 - KYC Risk Tolerance.
 * 
 *    Rev 1.35   Apr 24 2009 04:27:54   dchatcha
 * IN 1653090 - The KYC screen need to made mandatory in the NASU process.
 * 
 *    Rev 1.34   12 Nov 2008 17:09:32   popescu
 * Incident#  1476692 - fixed object required issue in shareholder
 * 
 *    Rev 1.33   Sep 16 2008 22:45:20   daechach
 * Restore rev. 1.31, 
 * 
 *    Rev 1.32   Sep 15 2008 07:09:50   daechach
 * PET0128026 - KYC Phase 2 - Fix crashing after close Demographics screen.
 * 
 *    Rev 1.31   Sep 12 2008 06:57:24   daechach
 * PET0128026 - KYC Phase 2
 * 
 *    Rev 1.30   Aug 22 2008 16:05:52   jankovii
 * IN 1386917 PET59888FN01-Add KYCCountryCode that will be used by AWD.
 * 
 *    Rev 1.29   Jul 16 2008 16:00:22   jankovii
 * PET 59888 - AML Enhancement.
 * 
 *    Rev 1.28   Aug 06 2007 16:24:40   kovacsro
 * PET2372 FN02 FDP-AIM KYC - look into KYC table instead of TRG
 * 
 *    Rev 1.27   Jul 27 2007 16:34:36   kovacsro
 * PET 2372 FN02 FDP-AIM KYC
 * 
 *    Rev 1.26   Mar 10 2004 11:30:48   HERNANDO
 * PET965 FN11 - Added getHistoricalParameters.
 * 
 *    Rev 1.25   Mar 03 2004 16:21:16   popescu
 * PTS 10027578, refresh the account information after updating the mailing address info and demographics info; changed the name of the refreshMe method, to be consistent with the shareholder object
 * 
 *    Rev 1.24   Dec 31 2003 11:54:02   popescu
 * PTS 10025659, force a refresh of the Sahreholder object at host level if we have Demographics updates
 * 
 *    Rev 1.23   Nov 20 2003 10:05:02   HSUCHIN
 * PTS 10024105 - Enable branch search for house brokers.
 * 
 *    Rev 1.22   Aug 19 2003 15:55:46   HSUCHIN
 * added support for branch / agent code input
 * 
 *    Rev 1.21   Aug 19 2003 14:40:02   HERNANDO
 * Changed container from MFAccount to Demographics for Memorable Data fields.
 * 
 *    Rev 1.20   Aug 18 2003 16:08:52   HERNANDO
 * Added keys to getHistoricalParameters.
 * 
 *    Rev 1.19   Jul 31 2003 13:26:24   FENGYONG
 * Add Historical logic
 * 
 *    Rev 1.18   Jul 28 2003 14:19:08   HERNANDO
 * Added MemorablePlace, MemorableWord, and MemorableDate fields.
 * 
 *    Rev 1.17   Jul 11 2003 16:39:40   FENGYONG
 * Add admin date relate fields
 * 
 *    Rev 1.16   Jul 11 2003 16:10:52   FENGYONG
 * move KYC from sharholder to MFAccount
 * 
 *    Rev 1.15   Mar 21 2003 17:38:24   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.14   Oct 09 2002 23:53:10   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.13   Aug 29 2002 16:44:52   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.12   Aug 29 2002 12:54:18   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.11   Jun 03 2002 16:42:24   FENGYONG
 * Add name for API
 * 
 *    Rev 1.10   Jun 03 2002 15:47:34   FENGYONG
 * Add name for API
 * 
 *    Rev 1.9   22 May 2002 18:24:12   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.8   27 Mar 2002 19:54:46   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.7   03 May 2001 14:05:22   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.6   15 Dec 2000 12:43:24   PURDYECH
 * Use precompiled header stdafx.h.
 * Removed unnecessary header files.
 * 
 *    Rev 1.5   Nov 30 2000 11:07:20   ZHANGCEL
 * Code clean up
 * 
 *    Rev 1.4   Nov 30 2000 10:12:56   ZHANGCEL
 * added " const " for variables in the namespace
 * 
 *    Rev 1.3   Aug 02 2000 15:32:00   BUZILA
 * "locale" changes
 * 
 *    Rev 1.2   Jul 20 2000 16:55:16   HUANGSHA
 * fixed the crash problem when lauching from NASU
 * 
 *    Rev 1.1   Mar 24 2000 09:36:38   DT24433
 * removed substitute lists, combined CBO initialization logic in getPtrForContainer
 * 
 *    Rev 1.0   Feb 15 2000 10:59:32   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.14   Jan 19 2000 10:11:58   BUZILA
 * refresh stuf
 * 
 *    Rev 1.13   Jan 08 2000 14:32:58   POPESCUS
 * added the datagroupid when quering for children lists
 * 
 *    Rev 1.12   Dec 14 1999 17:35:14   DT24433
 * removed doOk/doCancel
 * 
 *    Rev 1.11   Nov 30 1999 12:22:14   ZHANGCEL
 * Delete doCancel() method
 * 
 *    Rev 1.10   Nov 22 1999 10:40:34   ZHANGCEL
 * fine tune
 * 
 *    Rev 1.9   Nov 11 1999 09:46:12   ZHANGCEL
 * Implement for M2
 * 
 *    Rev 1.8   Nov 06 1999 15:25:10   VASILEAD
 * Took out VersionNum from view 11
 * 
 *    Rev 1.7   Oct 29 1999 11:30:14   BUZILA
 * changing WorkSessionDetails into a BFBase descendant
 * 
 *    Rev 1.6   Oct 18 1999 11:37:32   BUZILA
 * Update transaction stuff
 * 
 *    Rev 1.5   01 Sep 1999 16:40:18   HUANGSHA
 * Add OtherInvestment substitute list
 * 
 *    Rev 1.4   Aug 25 1999 15:37:04   DT24433
 * removed static fielddetails array
 * 
 *    Rev 1.3   25 Aug 1999 16:00:34   HUANGSHA
 * Check in temperorily
 * 
 *    Rev 1.2   Jul 20 1999 11:14:02   VASILEAD
 * New conditions update
 * 
 *    Rev 1.1   Jul 08 1999 10:02:00   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
