#include "stdafx.h"
#include "demographics.hpp"

#include "agent.hpp"
#include "agentlist.hpp"
#include "branch.hpp"
#include "branchlist.hpp"
#include "broker.hpp"
#include "brokerlist.hpp"
#include "defaultregulatorystandard.hpp"
#include "demographicschildlist.hpp"
#include "entity.hpp"
#include "errmsgruleslist.hpp"
#include "mfaccount.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "regulatorystandardlist.hpp"
#include "regdocumentlist.hpp"
#include "shareholder.hpp"
#include "TranslationTable.hpp"

#include <ifastdataimpl\dse_dstc0011_req.hpp>
#include <ifastdataimpl\dse_dstc0011_vw.hpp>
#include <ifastdataimpl\dse_dstc0081_req.hpp>
#include <ifastdataimpl\dse_dstc0465_vwrepeat_record.hpp>

#define EXTRACT_VALUE(s, val, delimiter) \
      pos = s.find (delimiter); \
      val = s.substr (0, pos);

#define CHOP_STRING(s, delimiter) \
         pos = s.find (delimiter); \
         pos = pos != DString::npos && pos + 1 <= s.length() ? pos + 1 : DString::npos; \
         if (pos != DString::npos) \
            s = s.substr (pos); \
         else \
            s = NULL_STRING;

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest DEMOGRAPHICS;
}

namespace
{
   const I_CHAR * const CLASSNAME           = I_( "Demographics" );
   const I_CHAR * const YES                 = I_( "Y" );
   const I_CHAR * const NO                  = I_( "N" );
   const I_CHAR * const KNOWLEDGE           = I_( "Knowledge" );
   const I_CHAR * const INCOMELEVEL         = I_( "Income Level" );
   const I_CHAR * const NETWORTH            = I_( "Net Worth" );
   const I_CHAR * const MARITIALSTATUS      = I_( "Maritial Status" );
   const I_CHAR * const RESIDENCETYPE       = I_( "Residence Type" );
   const I_CHAR * const RESIDENCEAMOUNT     = I_( "Residence Amount" );
   const I_CHAR * const EMPLOYERNAME        = I_( "Employer Name" );
   const I_CHAR * const OCCUPATIONS         = I_( "Occupation" );
   const I_CHAR * const EMPLOYMENTTYPE      = I_( "Employment Type" );
   const I_CHAR * const YEARSEMPLOYED       = I_( "Years Employed" );
   const I_CHAR * const OBJECTIVE           = I_( "Objective" );
   const I_CHAR * const HORIZON             = I_( "Horizon" );
   const I_CHAR * const COMMENTS            = I_( "Comments" );
   const I_CHAR * const ANNUALKYCMAILED     = I_( "Annual KYC Mailed." );
   const I_CHAR * const OCCUPATION_OTHER    = I_( "08" );
   const I_CHAR * const EFFECTIVEDATE       = I_( "Effective Date" );
   const I_CHAR * const SHARE_HOLDER_LEVEL_KYC  = I_( "1" );
   const I_CHAR * const INDIRECT_INVESTOR       = I_( "2" );
   const I_CHAR * const INDIVIDUAL_ACCOUNT_TYPE_LIST  = I_( "0,1,2" );
}

namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const ENTITY_NATIONALITY;        // Error # to entity nationlity field
   extern CLASS_IMPORT I_CHAR * const FIELD_IS_BLANK;
   extern CLASS_IMPORT I_CHAR * const BLANK_REG_STANDARD;
}

namespace KYC_MISC_INFO
{
    const I_CHAR * const OCCUPATION                 = I_("OC");
    const I_CHAR * const INDUSTRY                   = I_("JC");
    const I_CHAR * const LEGAL_FORM                 = I_("LGF");
    const I_CHAR * const BUSSINESS_TYPE             = I_("BU");
    const I_CHAR * const INDUSTRY_LINK_OCCUPATION   = I_("MH");

}

namespace SOURCE_OF_PAYMENT
{
   const I_CHAR * const SALARY                     = I_("01");
   const I_CHAR * const BORROWEDFUNDS              = I_("02");
   const I_CHAR * const PRCDSFRMDEATHBENEFESTATE   = I_("03");
   const I_CHAR * const OWNERSAVINGS               = I_("04");
   const I_CHAR * const PENSIONINCOME              = I_("05");
   const I_CHAR * const BUSINESSINCOME             = I_("06");
   const I_CHAR * const GIFTEDFUNDS                = I_("07");
   const I_CHAR * const SOCIALBENEFITS             = I_("08");
   const I_CHAR * const EXISTINGINVSTACCOUNT       = I_("09");
   const I_CHAR * const SALEOFPROPERTY             = I_("10");
   const I_CHAR * const INHERITEDFUNDS             = I_("11");
   const I_CHAR * const OTHER                      = I_("99");
}

namespace ifds
{  // Conditions used
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFNumericFieldId ShrNum;
   extern CLASS_IMPORT const BFNumericFieldId EntityId;
   extern CLASS_IMPORT const BFTextFieldId KYCLevel;
   extern CLASS_IMPORT const BFTextFieldId BrokerCode;
   extern CLASS_IMPORT const BFTextFieldId KYCRequired;
   extern CLASS_IMPORT const BFTextFieldId BranchName;
   extern CLASS_IMPORT const BFTextFieldId SlsrepName;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFTextFieldId ResProvCode;
   extern CLASS_IMPORT const BFTextFieldId RegDocsExist;
   extern CLASS_IMPORT const BFTextFieldId AutoDocTracking;
   extern CLASS_IMPORT const BFTextFieldId RegStandardId;
   extern CLASS_IMPORT const BFTextFieldId TypeOfInvestor;
   extern CLASS_IMPORT const BFTextFieldId InvestingOnBehalf;
   extern CLASS_IMPORT const BFTextFieldId AcctType;
   extern CLASS_IMPORT const BFTextFieldId TaxType;
   extern CLASS_IMPORT const BFTextFieldId AcctDesignation;
   extern CLASS_IMPORT const BFTextFieldId TaxJurisCode;
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
   extern CLASS_IMPORT const BFTextFieldId MiscCategory;
   extern CLASS_IMPORT const BFTextFieldId MiscCode;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,                   State Flags, Group Flags 
   { ifds::ShrNum,                 BFCBO::NONE,     0 }, 
   { ifds::AccountNum,             BFCBO::NONE,     0 }, 
   { ifds::MaritalCode,            BFCBO::NONE,     0 }, 
   { ifds::Employer,               BFCBO::NONE,     0 }, 
   { ifds::EmployedYrs,            BFCBO::NONE,     0 }, 
   { ifds::IndustryCode,           BFCBO::NONE,     0 }, 
   { ifds::OccupationCode,         BFCBO::NONE,     0 }, 
   { ifds::AnnualIncomeCode,       BFCBO::NONE,     0 }, 
   { ifds::NetWorthCode,           BFCBO::NONE,     0 }, 
   { ifds::InvObjCode,             BFCBO::NONE,     0 }, 
   { ifds::InvKnowledgeCode,       BFCBO::NONE,     0 }, 
   { ifds::InvHorizonCode,         BFCBO::NONE,     0 }, 
   { ifds::RiskToleranceCode,      BFCBO::NONE,     0 }, 
   { ifds::OtherInvestments,       BFCBO::NONE,     0 }, 
   { ifds::AdvisorCode,            BFCBO::NONE,     0 }, 
   { ifds::WitnessName,            BFCBO::NONE,     0 }, 
   { ifds::WitnessAddr1,           BFCBO::NONE,     0 }, 
   { ifds::WitnessAddr2,           BFCBO::NONE,     0 }, 
   { ifds::EffectiveDate,          BFCBO::NONE,     0 }, 
   { ifds::PersonalSecCode,        BFCBO::NONE,     0 }, 
   { ifds::PrimMstrVer,            BFCBO::NONE,     0 }, 
   { ifds::ProcessDate,            BFCBO::NONE,     0 }, 
   { ifds::RunMode,                BFCBO::NONE,     0 }, 
   { ifds::InvestPhilosophyCode,   BFCBO::NONE,     0 }, 
   { ifds::OccupationFreeFormat,   BFCBO::NONE,     0 }, 
   { ifds::GrowthPercent,          BFCBO::NONE,     0 }, 
   { ifds::SafetyPercent,          BFCBO::NONE,     0 }, 
   { ifds::IncomePercent,          BFCBO::NONE,     0 }, 
   { ifds::SAMFinHealthCode,       BFCBO::NONE,     0 }, 
   { ifds::TypeOfBusFreeFormat,    BFCBO::NONE,     0 }, 
   { ifds::MemorableWord,          BFCBO::NONE,     0 }, 
   { ifds::MemorablePlace,         BFCBO::NONE,     0 }, 
   { ifds::MemorableDate,          BFCBO::NONE,     0 }, 
   { ifds::ModUser,                BFCBO::NONE,     0 }, 
   { ifds::KYCBusinessType,        BFCBO::NONE,     0 }, 
   { ifds::KYCLegalForm,           BFCBO::NONE,     0 }, 

   // history
   { ifds::ModDate,                BFCBO::NONE,     0 }, 
   { ifds::Username,               BFCBO::NONE,     0 }, 

   // house broker
   { ifds::BrokerCode,             BFCBO::NONE,     0 }, 
   { ifds::BranchCode,             BFCBO::NONE,     0 }, 
   { ifds::BranchName,             BFCBO::NONE,     0 }, 
   { ifds::AgentCode,              BFCBO::NONE,     0 }, 
   { ifds::SlsrepName,             BFCBO::NONE,     0 }, 

   // misc
   { ifds::KYCComment,             BFCBO::NONE,     0 }, 

   { ifds::EmploymentType,         BFCBO::NONE,     0 }, 
   { ifds::ResidenceType,          BFCBO::NONE,     0 }, 
   { ifds::ResAmount,              BFCBO::NONE,     0 }, 
   { ifds::KYCMailedDate,          BFCBO::NONE,     0 }, 
   { ifds::AnnualIncomeAmount,     BFCBO::NONE,     0 }, 
   { ifds::IncomeLevelDate,        BFCBO::NONE,     0 }, 
   { ifds::NetWorthAmount,         BFCBO::NONE,     0 }, 
   { ifds::NetWorthDate,           BFCBO::NONE,     0 }, 
   { ifds::RefferalCode,           BFCBO::NONE,     0 }, 
   { ifds::ReferenceName,          BFCBO::NONE,     0 }, 
   { ifds::SpecialtyCode,          BFCBO::NONE,     0 }, 
   { ifds::TolerancePrcnt,         BFCBO::NONE,     0 }, 
   { ifds::ShortTermPrcnt,         BFCBO::NONE,     0 }, 
   { ifds::AggressivePrcnt,        BFCBO::NONE,     0 }, 
   { ifds::PrcntDate,              BFCBO::NONE,     0 }, 
   { ifds::TypeOfInvestor,         BFCBO::NONE,     0 }, 
   { ifds::InvestingOnBehalf,      BFCBO::NONE,     0 }, 
   { ifds::SourceOfIncome,         BFCBO::NONE,     0 }, 
   { ifds::InitialPayment,         BFCBO::NONE,     0 }, 
   { ifds::PowerOfAttorney,        BFCBO::NONE,     0 }, 
   { ifds::ComplianceCode,         BFCBO::NONE,     0 }, 
   { ifds::SolicitPublicContrib,   BFCBO::NONE,     0 }, 
   { ifds::RegulatoryStandard,     BFCBO::NONE,     0 }, 
   { ifds::CountryCode,            BFCBO::NONE,     0 }, 
   { ifds::RegulatoryCountryCode,  BFCBO::NONE,     0 }, 

   // associate comp
   { ifds::SuppressKYCLetter,      BFCBO::NONE,     0 }, 
   { ifds::NumOfDependents,        BFCBO::NONE,     0 }, 
   { ifds::AssociateCorpName1,     BFCBO::NONE,     0 }, 
   { ifds::AssociateCorpName2,     BFCBO::NONE,     0 }, 
   { ifds::AssociateCorpName3,     BFCBO::NONE,     0 }, 
   { ifds::AssociateCorpName4,     BFCBO::NONE,     0 }, 
   { ifds::AssociateCorpName5,     BFCBO::NONE,     0 }, 
   { ifds::AssociateCorpName6,     BFCBO::NONE,     0 }, 
   { ifds::AssociateCorpName7,     BFCBO::NONE,     0 }, 
   { ifds::AssociateCorpName8,     BFCBO::NONE,     0 }, 
   { ifds::AssociateCorpName9,     BFCBO::NONE,     0 }, 
   { ifds::AssociateCorpName10,    BFCBO::NONE,     0 }, 

   { ifds::RoleInCorp1,            BFCBO::NONE,     0 }, 
   { ifds::RoleInCorp2,            BFCBO::NONE,     0 }, 
   { ifds::RoleInCorp3,            BFCBO::NONE,     0 }, 
   { ifds::RoleInCorp4,            BFCBO::NONE,     0 }, 
   { ifds::RoleInCorp5,            BFCBO::NONE,     0 }, 
   { ifds::RoleInCorp6,            BFCBO::NONE,     0 }, 
   { ifds::RoleInCorp7,            BFCBO::NONE,     0 }, 
   { ifds::RoleInCorp8,            BFCBO::NONE,     0 }, 
   { ifds::RoleInCorp9,            BFCBO::NONE,     0 }, 
   { ifds::RoleInCorp10,           BFCBO::NONE,     0 }, 

   { ifds::KYCInfoFormat,          BFCBO::NONE,     0 }, 
   { ifds::ProfileNum,             BFCBO::NONE,     0 },       
   { ifds::RefNum,                 BFCBO::NONE,     0 }, 
   { ifds::ProfileValue,           BFCBO::NONE,     0 }, 
   { ifds::LastReviewDate,         BFCBO::NONE,     0 },

   // source of payment
   { ifds::SrcOfPymtSalary,                     BFCBO::NONE,     0 },
   { ifds::SrcOfPymtBusinessIncome,             BFCBO::NONE,     0 },
   { ifds::SrcOfPymtBorrowedFunds,              BFCBO::NONE,     0 },
   { ifds::SrcOfPymtGiftedFunds,                BFCBO::NONE,     0 },
   { ifds::SrcOfPymtPrcdsFrmDeathBenefEstate,   BFCBO::NONE,     0 },
   { ifds::SrcOfPymtSocialBenefits,             BFCBO::NONE,     0 },
   { ifds::SrcOfPymtOther,                      BFCBO::NONE,     0 },
   { ifds::SrcOfPymtOtherReason,                BFCBO::NONE,     0 },
   { ifds::SrcOfPymtExistingInvstAccount,       BFCBO::NONE,     0 },
   { ifds::SrcOfPymtOwnerSavings,               BFCBO::NONE,     0 },
   { ifds::SrcOfPymtSaleOfProperty,             BFCBO::NONE,     0 },
   { ifds::SrcOfPymtPensionIncome,              BFCBO::NONE,     0 },
   { ifds::SrcOfPymtInheritedFunds,             BFCBO::NONE,     0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );


namespace CND
{  // Conditions used
   extern const long ERR_EFFECTIVE_DATE_BACKWARD;
   extern const long ERR_TOTAL_KYC_PRCNT_MUST_BE_0_OR_100;
   extern const long ERR_FIELD_REQUIRED_PLS_SELECT;
   extern const long WARN_FIELD_REQUIRED_PLS_SELECT;
   extern const long ERR_FIELD_IS_BLANK;
   extern const long WARN_FIELD_IS_BLANK;
   extern const long ERR_BLANK_REG_STANDARD;
   extern const long WARN_BLANK_REG_STANDARD;
   extern const long WARN_REG_STANDARD_CHANGED;
   extern const long ERR_DOC_STATUS_BLANK;
   extern const long WARN_DATA_UPDATE_IMPACTS_EXTERNAL_ENV_SICAV;
   extern const long WARN_DATA_UPDATE_IMPACTS_EXTERNAL_ENV_OEIC;
}

//******************************************************************************
Demographics::Demographics( BFAbstractCBO &parent )
: MFCanBFCbo( parent ),
_initEffectiveDate(NULL_STRING),
_pErrMsgRulesList(NULL),
_dstrAccountNum (NULL_STRING),
_bRegStandardExist (false)
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );

   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
   _dstrAccountNum = NULL_STRING;
   _dstrResidenceCode = NULL_STRING;

   _fieldRecordMap.insert(std::pair<BFFieldId,DString>(ifds::SrcOfPymtSalary,SOURCE_OF_PAYMENT::SALARY));
   _fieldRecordMap.insert(std::pair<BFFieldId,DString>(ifds::SrcOfPymtBorrowedFunds,SOURCE_OF_PAYMENT::BORROWEDFUNDS));
   _fieldRecordMap.insert(std::pair<BFFieldId,DString>(ifds::SrcOfPymtPrcdsFrmDeathBenefEstate,SOURCE_OF_PAYMENT::PRCDSFRMDEATHBENEFESTATE));
   _fieldRecordMap.insert(std::pair<BFFieldId,DString>(ifds::SrcOfPymtOwnerSavings,SOURCE_OF_PAYMENT::OWNERSAVINGS));
   _fieldRecordMap.insert(std::pair<BFFieldId,DString>(ifds::SrcOfPymtPensionIncome,SOURCE_OF_PAYMENT::PENSIONINCOME));
   _fieldRecordMap.insert(std::pair<BFFieldId,DString>(ifds::SrcOfPymtBusinessIncome,SOURCE_OF_PAYMENT::BUSINESSINCOME));
   _fieldRecordMap.insert(std::pair<BFFieldId,DString>(ifds::SrcOfPymtGiftedFunds,SOURCE_OF_PAYMENT::GIFTEDFUNDS));
   _fieldRecordMap.insert(std::pair<BFFieldId,DString>(ifds::SrcOfPymtSocialBenefits,SOURCE_OF_PAYMENT::SOCIALBENEFITS));
   _fieldRecordMap.insert(std::pair<BFFieldId,DString>(ifds::SrcOfPymtExistingInvstAccount,SOURCE_OF_PAYMENT::EXISTINGINVSTACCOUNT));
   _fieldRecordMap.insert(std::pair<BFFieldId,DString>(ifds::SrcOfPymtSaleOfProperty,SOURCE_OF_PAYMENT::SALEOFPROPERTY));
   _fieldRecordMap.insert(std::pair<BFFieldId,DString>(ifds::SrcOfPymtInheritedFunds,SOURCE_OF_PAYMENT::INHERITEDFUNDS));
   _fieldRecordMap.insert(std::pair<BFFieldId,DString>(ifds::SrcOfPymtOther,SOURCE_OF_PAYMENT::OTHER));

}

//******************************************************************************
Demographics::~Demographics()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY Demographics::initNew (const DString& accountNum, 
   const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   MFAccount* pMFAccount = NULL; 
   DString shrNum;
   _dstrAccountNum = accountNum;
   if( getWorkSession().getMFAccount( idDataGroup, accountNum, pMFAccount ) <= WARNING &&
	   pMFAccount != NULL )
   {
      pMFAccount->getField(ifds::ShrNum,shrNum,idDataGroup, false);
   }

   //get the shareholder
   Shareholder* pShareholder = NULL;
   if (getWorkSession().getShareholder(idDataGroup, shrNum, pShareholder) <= WARNING && 
         pShareholder)
   {
      //init the effective date from the shareholder
      DString effectiveDate;

      pShareholder->getField(ifds::ResProvCode, _dstrResidenceCode, idDataGroup, false);	  
      pShareholder->getField(ifds::EffectiveDate, effectiveDate, idDataGroup, false);
      setFieldNoValidate(ifds::EffectiveDate, effectiveDate, idDataGroup, false, false, true);	  
      _initEffectiveDate = effectiveDate;
      //init the shareholder number
      setFieldNoValidate(ifds::ShrNum, shrNum, idDataGroup);	  
   }
   
   setObjectNew();	
   clearUpdatedFlags(idDataGroup, false);
   initWithDefaultValues(idDataGroup); 
   setFieldsForValidation(idDataGroup); 
   setFieldsReadOnlyForShrLevel(idDataGroup); 

//   getWorkSession().getOption(ifds::KYCAccountLevel, dstrKYCAccountLevel, BF::HOST, false);
//   if(dstrKYCRequired == YES && dstrKYCAccountLevel == YES)

   setupHouseBroker ( idDataGroup );

   DString suppressKYCLetter;

   getField( ifds::SuppressKYCLetter, suppressKYCLetter, idDataGroup );

   if ( suppressKYCLetter == NULL_STRING || suppressKYCLetter.empty() )
   {
      setFieldNoValidate( ifds::SuppressKYCLetter, I_( "N" ), idDataGroup, true );
   }

   DString strNumOfDependents;
   getField( ifds::NumOfDependents, strNumOfDependents, idDataGroup );

   if ( strNumOfDependents.empty() )
   {
      setField( ifds::NumOfDependents, I_( "0" ), idDataGroup );
   }
   
   DString dstrCurrentBusinessDate;
   if (getWorkSession().getOption( ifds::CurrBusDate, dstrCurrentBusinessDate, idDataGroup, false ))
   {
      setFieldNoValidate( ifds::LastReviewDate, dstrCurrentBusinessDate, idDataGroup, false, true, true );      
   }

   DString dstrAutoDocTracking;
   bool bIsEntityLevelKYC = (_dstrAccountNum == I_("0"))? true : false;
   DString dstrKYCLevel;
   getWorkSession().getOption(ifds::KYCLevel, dstrKYCLevel, idDataGroup);

   getWorkSession().getOption(ifds::AutoDocTracking, dstrAutoDocTracking, idDataGroup);
   if (dstrAutoDocTracking == YES && (!bIsEntityLevelKYC || dstrKYCLevel == I_("04")))
   {
      DString dstrTypeOfInvestor, dstrInvestingOnBehalf;
      RegulatoryStandardList *pRegulatoryStandardList = NULL;
      DefaultRegulatoryStandard *pDefaultRegulatoryStandard = NULL;

      getField(ifds::TypeOfInvestor, dstrTypeOfInvestor, idDataGroup);
      getField(ifds::InvestingOnBehalf, dstrInvestingOnBehalf, idDataGroup);

      DString dstrAcctEffDate = NULL_STRING;
      if(pMFAccount)
         pMFAccount->getField(ifds::EffectiveDate , dstrAcctEffDate ,idDataGroup , false);

      if (getRegulatoryStandardsList(pRegulatoryStandardList, dstrTypeOfInvestor, dstrInvestingOnBehalf, dstrAcctEffDate, idDataGroup) <= WARNING && 
         pRegulatoryStandardList && 
         getDefaultRegulatoryStandard(pDefaultRegulatoryStandard, idDataGroup) <= WARNING && 
         pDefaultRegulatoryStandard)
      {
         DString dstrSubList(I_(" = ;")), dstrRegStandardId;

         pRegulatoryStandardList->getSubstitionList(dstrSubList, idDataGroup);
         setFieldAllSubstituteValues(ifds::RegulatoryStandard, idDataGroup, dstrSubList); 

         pDefaultRegulatoryStandard->getField(ifds::RegStandardId, dstrRegStandardId, idDataGroup);

         setField(ifds::RegulatoryStandard, dstrRegStandardId, idDataGroup);
         setUpdatedFlag(ifds::RegulatoryStandard, idDataGroup, true);
      }
   }

   commonInit(idDataGroup);

   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
void Demographics::doInitWithDefaultValues(const BFDataGroupId& idDataGroup)
{
   SetMandatoryField(idDataGroup);
}

//******************************************************************************
SEVERITY Demographics::init(const DString& accountNum, 
                            const DString& entityId, 
                            const BFDataGroupId& idDataGroup, 
                            const DString& dstrTrack, 
                            const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   _dstrAccountNum = accountNum;

   MFAccount* pMFAccount = NULL; 
   DString shrNum;
   if( getWorkSession().getMFAccount( idDataGroup, accountNum, pMFAccount ) <= WARNING )
   {
      if ( pMFAccount != NULL )
      {
         DString entityIds;
         pMFAccount->getField(ifds::ShrNum,shrNum,idDataGroup, false);

         std::set < DString > entityIdList;

         for (int i = 1; i < 5; i++)
         {
            DString entityId = NULL_STRING;
            DString seqNum;

            convertIntToString(i, seqNum);

            //pMFAccount->GetEntityIdForAcctOwner(idDataGroup, seqNum,entityId );

            if (entityId.empty ())
               continue;

            entityIdList.insert (entityId);
         }

         for (std::set< DString >::iterator iter = entityIdList.begin();    
            iter != entityIdList.end(); iter++) 
         {   
            DString temp = *iter;
            int i = 0;
         }

      }
   }

   BFData queryData(ifds::DSTC0011_REQ);
   BFData *receivedData = new BFData(ifds::DSTC0011_VW);

   DString mgmtCoIdOut;
   queryData.setElementValue(ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ));
   if( ( pMFAccount != NULL ) && !pMFAccount->isNew() ) 
   {
      queryData.setElementValue(ifds::AccountNum, _dstrAccountNum);
   }
   else if ( _dstrAccountNum == I_( "0" ) )
   {
      queryData.setElementValue(ifds::AccountNum, _dstrAccountNum);
   }

   queryData.setElementValue(ifds::ShrNum, shrNum );
   queryData.setElementValue(ifds::EntityId, entityId );

   queryData.setElementValue(ifds::Track, dstrTrack);
   queryData.setElementValue(ifds::Activity, dstrPageName);

   //call the back-end
   if (ReceiveData(DSTC_REQUEST::DEMOGRAPHICS, queryData, *receivedData, 
      DSTCRequestor(getSecurity(), false)) <= WARNING)
   {
      receivedData->getElementValue(ifds::EffectiveDate, _initEffectiveDate);
      //For some reason the view is sending 'y' & 'n' which makes the field 
      //in BF::HOST to be updated.Due to complexity in DSTC0011VW changing in Desktop
      DString dstrInvestingOnBehalf = NULL_STRING;
      receivedData->getElementValue(ifds::InvestingOnBehalf, dstrInvestingOnBehalf);
      if(!dstrInvestingOnBehalf.stripAll().empty())
         receivedData->setElementValue(ifds::InvestingOnBehalf, dstrInvestingOnBehalf.upperCase());
   }

   if ( pMFAccount != NULL )
   {
      if( pMFAccount->isNew() )
         setupHouseBroker ( idDataGroup );
      else
         setupHouseBroker ( BF::HOST );
   }

   clearUpdatedFlags(BF::HOST, false);
   SetMandatoryField(idDataGroup);
   setFieldsForValidation(idDataGroup); 
   setFieldsReadOnlyForShrLevel(idDataGroup); 

   DString typeOfInvestor, investingOnBehalf, regulatoryStandard, dstrRegStandardName; 
   RegulatoryStandardList *pRegulatoryStandardList = NULL;

   getField (ifds::TypeOfInvestor, typeOfInvestor, idDataGroup);
   getField (ifds::InvestingOnBehalf, investingOnBehalf, idDataGroup);
   getField (ifds::RegulatoryStandard, regulatoryStandard, idDataGroup);
   getField (ifds::RegStandardName, dstrRegStandardName, idDataGroup);

   //get the shareholder & province of residence
   Shareholder* pShareholder = NULL;
   DString dstrAutoDocTracking;

   getWorkSession().getOption(ifds::AutoDocTracking, dstrAutoDocTracking, idDataGroup);

   if (( pMFAccount != NULL ) && 
         getWorkSession().getShareholder(idDataGroup, shrNum, pShareholder) <= WARNING && 
         pShareholder)
   {

      pShareholder->getField(ifds::ResProvCode, _dstrResidenceCode, idDataGroup, false);	  
   }
   DString dstrAcctEffDate = NULL_STRING;
   if(pMFAccount)
         pMFAccount->getField(ifds::EffectiveDate , dstrAcctEffDate ,idDataGroup , false);
   if (dstrAutoDocTracking == NO && typeOfInvestor != NULL_STRING && investingOnBehalf != NULL_STRING)
   {
      getRegulatoryStandards(typeOfInvestor, investingOnBehalf, dstrAcctEffDate, BF::HOST);
   }
   else if (dstrAutoDocTracking == YES &&
           getRegulatoryStandardsList(pRegulatoryStandardList, typeOfInvestor, investingOnBehalf, dstrAcctEffDate, idDataGroup) <= WARNING && 
           pRegulatoryStandardList)
   {
      DString dstrSubList(I_(" = ;")), dstrRegStandardId;
      pRegulatoryStandardList->getSubstitionList(dstrSubList, idDataGroup);
      //setFieldAllSubstituteValues(ifds::RegulatoryStandard, idDataGroup, dstrSubList); 
      //special treatment for displaying the reg stand of an account which had a regulatory std that has been stop-dated as of today.
      //with the chnages for P0247899 _SSBL_1792 _Scroll Down Menu project , the vew 388 will send you only the list of Reg std which are not stopped as of today.
      int nPos = dstrSubList.find(regulatoryStandard);   
      if (nPos == -1 && !regulatoryStandard.stripAll().empty())
          dstrSubList+= regulatoryStandard + I_("=") + dstrRegStandardName + I_(";");
      setFieldAllSubstituteValues(ifds::RegulatoryStandard, idDataGroup, dstrSubList); 
   }
   setFieldNoValidate (ifds::RegulatoryStandard, regulatoryStandard, idDataGroup, true, true, false, false); 

   DString suppressKYCLetter;

   getField( ifds::SuppressKYCLetter, suppressKYCLetter, idDataGroup );

   if ( suppressKYCLetter == NULL_STRING || suppressKYCLetter.empty() )
   {
      setFieldNoValidate( ifds::SuppressKYCLetter, I_( "N" ), idDataGroup, true );
   }

   DString strNumOfDependents;
   getField( ifds::NumOfDependents, strNumOfDependents, idDataGroup );

   if ( strNumOfDependents.empty() )
   {
      setField( ifds::NumOfDependents, I_( "0" ), idDataGroup );
   }

   // initial LastReviewDate if it is null or 12319999
   DString dstrLastReviewDate, dstrCurrentBusinessDate;
   getField( ifds::LastReviewDate, dstrLastReviewDate, idDataGroup, false);
   if ( dstrLastReviewDate.empty() || 
        (DSTCommonFunctions::CompareDates (dstrLastReviewDate, I_("12319999")) == DSTCommonFunctions::EQUAL) )
   {
      if (getWorkSession().getOption( ifds::CurrBusDate, dstrCurrentBusinessDate, idDataGroup, false ))
      {
         setFieldNoValidate( ifds::LastReviewDate, dstrCurrentBusinessDate, idDataGroup, false, true, true );
      }
   }

   // Load KYC child
   loadSourceOfPayment(idDataGroup);

   commonInit(idDataGroup);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Demographics::doValidateField( const BFFieldId& idField, 
                                        const DString& strValue, 
                                        const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );
   //DString dstrKYCLevel = NULL_STRING;
   //getWorkSession().getOption( ifds::KYCLevel, dstrKYCLevel, idDataGroup, false );

   DString dstrValue = strValue;
   dstrValue.strip();

   bool bIsShareHolderLevelKYC = isShareHolderLevelKYC(idDataGroup);

   // assume that when account number is equal '0' mean entity level KYC
   bool bIsEntityLevelKYC = ( _dstrAccountNum == I_( "0" ) )? true : false;

   if( idField == ifds::EffectiveDate )
   {
      int ret;

      if ( _initEffectiveDate.strip() != NULL_STRING &&
           ( ret = DSTCommonFunctions::CompareDates(strValue, _initEffectiveDate)) == 
             DSTCommonFunctions::FIRST_EARLIER )
      {
         ADDCONDITIONFROMFILE(CND::ERR_EFFECTIVE_DATE_BACKWARD);
      }
   }
   else if( idField == ifds::RiskToleranceCode)
   {
      if( strValue == NULL_STRING )
         getErrMsg( I_("366"), CND::ERR_FIELD_REQUIRED_PLS_SELECT, CND::WARN_FIELD_REQUIRED_PLS_SELECT, idDataGroup, NULL_STRING );
   }
   else if( idField == ifds::InvKnowledgeCode)
   {
      if( dstrValue == NULL_STRING )
      {
         if ( fieldIsBlank(KNOWLEDGE,idDataGroup) == NO_CONDITION )
         {
            getErrMsg( I_("367"), 
                       CND::ERR_FIELD_REQUIRED_PLS_SELECT, 
                       CND::WARN_FIELD_REQUIRED_PLS_SELECT, 
                       idDataGroup, 
                       NULL_STRING );
         }
      }
   }
   else if( idField == ifds::NetWorthCode)
   {
      if( dstrValue == NULL_STRING )
      {
         if ( fieldIsBlank(NETWORTH ,idDataGroup) == NO_CONDITION )
         {
            getErrMsg( I_("365"), 
                       CND::ERR_FIELD_REQUIRED_PLS_SELECT, 
                       CND::WARN_FIELD_REQUIRED_PLS_SELECT, 
                       idDataGroup, 
                       NULL_STRING );
         }
      }
   }
   else if( idField == ifds::AnnualIncomeCode)
   {
      if( dstrValue == NULL_STRING )
      {
         if ( fieldIsBlank(INCOMELEVEL ,idDataGroup) == NO_CONDITION )
         {
            getErrMsg( I_("364"), 
                       CND::ERR_FIELD_REQUIRED_PLS_SELECT, 
                       CND::WARN_FIELD_REQUIRED_PLS_SELECT, 
                       idDataGroup, 
                       NULL_STRING );
         }
      }
   } else if ( idField == ifds::BranchCode ) {
      validateBranch ( strValue, idDataGroup );
   } else if ( idField == ifds::AgentCode ) {
      validateSlsRep ( strValue, idDataGroup );
   }
   else if ( idField == ifds::KYCComment ) 
   {
      if ( dstrValue == NULL_STRING && 
           !bIsShareHolderLevelKYC  && 
           !bIsEntityLevelKYC
           //dstrKYCLevel != I_( "01" ) 
         )
      {
         fieldIsBlank (COMMENTS, idDataGroup);
      }
   }
   else if ( idField == ifds::EmploymentType ) 
   {
      if ( dstrValue == NULL_STRING && !bIsShareHolderLevelKYC
           //dstrKYCLevel != I_( "01" ) 
           )
      {
         fieldIsBlank (EMPLOYMENTTYPE , idDataGroup);
      }
   }
   else if ( idField == ifds::ResidenceType ) 
   {
      if ( dstrValue == NULL_STRING && !bIsShareHolderLevelKYC
           //dstrKYCLevel != I_( "01" ) 
           )
      {
         fieldIsBlank (RESIDENCETYPE , idDataGroup);
      }
   }
   else if ( idField == ifds::ResAmount ) 
   {
      if ( dstrValue == NULL_STRING && !bIsShareHolderLevelKYC
           //dstrKYCLevel != I_( "01" ) 
           )
      {
         fieldIsBlank (RESIDENCEAMOUNT , idDataGroup);
      }
   }
   //else if ( idField == ifds::KYCMailedDate ) 
   //{
   //    if ( dstrValue == NULL_STRING && !bIsShareHolderLevelKYC
   //        //dstrKYCLevel != I_( "01" ) 
   //        )
   //    {
   //        fieldIsBlank (ANNUALKYCMAILED , idDataGroup);
   //    }
   //}
   else if ( idField == ifds::EffectiveDate ) 
   {
      if ( dstrValue == NULL_STRING && !bIsShareHolderLevelKYC
           //dstrKYCLevel != I_( "01" ) 
           )
      {
         fieldIsBlank (EFFECTIVEDATE , idDataGroup);
      }
   }
   else if ( idField == ifds::MaritalCode ) 
   {
      if ( dstrValue == NULL_STRING )
      {
         fieldIsBlank (MARITIALSTATUS , idDataGroup);
      }
   }
   else if ( idField == ifds::Employer ) 
   {
      if ( dstrValue == NULL_STRING )
      {
         fieldIsBlank (EMPLOYERNAME , idDataGroup);
      }
   }
   else if ( idField == ifds::OccupationCode ) 
   {
      if ( dstrValue == NULL_STRING )
      {
         fieldIsBlank (OCCUPATIONS  , idDataGroup);
      }
   }
   else if ( idField == ifds::OccupationFreeFormat ) 
   {
      if ( dstrValue == NULL_STRING )
      {
         DString strOccupation;
         getField (ifds::OccupationCode, strOccupation, idDataGroup, false);
         if( strOccupation.strip() == OCCUPATION_OTHER )
         {
            fieldIsBlank (OCCUPATIONS , idDataGroup);
         }
      }
   }
   else if ( idField == ifds::EmployedYrs ) 
   {
      if ( dstrValue == NULL_STRING )
      {
         fieldIsBlank (YEARSEMPLOYED , idDataGroup);
      }
   }
   else if ( idField == ifds::InvObjCode ) 
   {
      if ( dstrValue == NULL_STRING && !bIsEntityLevelKYC )
      {
         fieldIsBlank (OBJECTIVE , idDataGroup);
      }
   }
   else if ( idField == ifds::InvHorizonCode ) 
   {
      if ( dstrValue == NULL_STRING && !bIsEntityLevelKYC )
      {
         fieldIsBlank (HORIZON , idDataGroup);
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Demographics::setFieldsReadOnlyForShrLevel( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateRiskTolerance" ) );

   //DString dstrKYCLevel = NULL_STRING;
   //getWorkSession().getOption( ifds::KYCLevel, dstrKYCLevel, idDataGroup, false );
   //if( dstrKYCLevel == I_( "01" ) )
   if ( isShareHolderLevelKYC(idDataGroup) )
   {
      setFieldReadOnly ( ifds::KYCComment,         idDataGroup, true );
      setFieldReadOnly ( ifds::EmploymentType,     idDataGroup, true );
      setFieldReadOnly ( ifds::ResidenceType,      idDataGroup, true );
      setFieldReadOnly ( ifds::ResAmount,          idDataGroup, true );
      setFieldReadOnly ( ifds::AnnualIncomeAmount, idDataGroup, true );
      setFieldReadOnly ( ifds::IncomeLevelDate,    idDataGroup, true );
      setFieldReadOnly ( ifds::NetWorthAmount,     idDataGroup, true );
      setFieldReadOnly ( ifds::NetWorthDate,       idDataGroup, true );
      setFieldReadOnly ( ifds::RefferalCode,       idDataGroup, true );
      setFieldReadOnly ( ifds::ReferenceName,      idDataGroup, true );
      setFieldReadOnly ( ifds::SpecialtyCode,      idDataGroup, true );
      setFieldReadOnly ( ifds::TolerancePrcnt,     idDataGroup, true );
      setFieldReadOnly ( ifds::ShortTermPrcnt,     idDataGroup, true );
      setFieldReadOnly ( ifds::AggressivePrcnt,    idDataGroup, true );
      setFieldReadOnly ( ifds::PrcntDate,          idDataGroup, true );

      //for reset purposes, also use BF::HOST
      setFieldReadOnly ( ifds::KYCComment,         BF::HOST, true );
      setFieldReadOnly ( ifds::EmploymentType,     BF::HOST, true );
      setFieldReadOnly ( ifds::ResidenceType,      BF::HOST, true );
      setFieldReadOnly ( ifds::ResAmount,          BF::HOST, true );
      setFieldReadOnly ( ifds::AnnualIncomeAmount, BF::HOST, true );
      setFieldReadOnly ( ifds::IncomeLevelDate,    BF::HOST, true );
      setFieldReadOnly ( ifds::NetWorthAmount,     BF::HOST, true );
      setFieldReadOnly ( ifds::NetWorthDate,       BF::HOST, true );
      setFieldReadOnly ( ifds::RefferalCode,       BF::HOST, true );
      setFieldReadOnly ( ifds::ReferenceName,      BF::HOST, true );
      setFieldReadOnly ( ifds::SpecialtyCode,      BF::HOST, true );
      setFieldReadOnly ( ifds::TolerancePrcnt,     BF::HOST, true );
      setFieldReadOnly ( ifds::ShortTermPrcnt,     BF::HOST, true );
      setFieldReadOnly ( ifds::AggressivePrcnt,    BF::HOST, true );
      setFieldReadOnly ( ifds::PrcntDate,          BF::HOST, true );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY Demographics::setFieldsForValidation( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateRiskTolerance" ) );
   // Default condition
   SEVERITY sevRtn = NO_CONDITION;
   DString strErrValue;

   setFieldReadOnly ( ifds::KYCMailedDate, BF::HOST, true );
   setFieldReadOnly ( ifds::KYCMailedDate, idDataGroup, true );

   if( _pErrMsgRulesList == NULL )
   {
      getMgmtCo().getErrMsgRulesList( _pErrMsgRulesList );
   }

   if( _pErrMsgRulesList )
   {
      _pErrMsgRulesList->getEWIValue(I_("967"), idDataGroup, strErrValue );
      if( strErrValue == I_("E") || strErrValue == I_("W") )
      {
         setValidFlag ( ifds::InvKnowledgeCode, idDataGroup, false );
         setValidFlag ( ifds::NetWorthCode, idDataGroup, false );
         setValidFlag ( ifds::AnnualIncomeCode, idDataGroup, false );
         setValidFlag ( ifds::KYCComment, idDataGroup, false );
         setValidFlag ( ifds::EmploymentType, idDataGroup, false );
         setValidFlag ( ifds::ResidenceType, idDataGroup, false );
         setValidFlag ( ifds::ResAmount, idDataGroup, false );         
         setValidFlag ( ifds::MaritalCode, idDataGroup, false );
         setValidFlag ( ifds::Employer, idDataGroup, false );
         setValidFlag ( ifds::OccupationCode, idDataGroup, false );
         setValidFlag ( ifds::OccupationFreeFormat, idDataGroup, false );
         setValidFlag ( ifds::EmployedYrs, idDataGroup, false );
         setValidFlag ( ifds::InvObjCode, idDataGroup, false );
         setValidFlag ( ifds::InvHorizonCode, idDataGroup, false );
         setValidFlag ( ifds::EffectiveDate, idDataGroup, false );
         if( isNew() )
         {
            setUpdatedFlag( ifds::EffectiveDate, idDataGroup, true );
         }
         if( strErrValue == I_("E") )
         {
            setFieldRequired( ifds::InvKnowledgeCode, idDataGroup,true );
            setFieldRequired( ifds::NetWorthCode, idDataGroup,true );
            setFieldRequired( ifds::AnnualIncomeCode, idDataGroup,true );
            setFieldRequired( ifds::KYCComment, idDataGroup,true );
            setFieldRequired( ifds::EmploymentType, idDataGroup,true );
            setFieldRequired( ifds::ResidenceType, idDataGroup,true );
            setFieldRequired( ifds::ResAmount, idDataGroup,true );
            setFieldRequired( ifds::MaritalCode, idDataGroup,true );
            setFieldRequired( ifds::Employer, idDataGroup,true );
            setFieldRequired( ifds::OccupationCode, idDataGroup,true );
            //setFieldRequired( ifds::OccupationFreeFormat, idDataGroup,true );
            setFieldRequired( ifds::EmployedYrs, idDataGroup,true );
            setFieldRequired( ifds::InvObjCode, idDataGroup,true );
            setFieldRequired( ifds::InvHorizonCode, idDataGroup,true );
            setFieldRequired( ifds::EffectiveDate, idDataGroup,true );
         }
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY Demographics::SetMandatoryField(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateRiskTolerance" ) );

   long  errEntityID  (CND::ERR_FIELD_REQUIRED_PLS_SELECT);
   long  warnEntityID (CND::WARN_FIELD_REQUIRED_PLS_SELECT);
   bool  havemandatoryfield = false;
   // Default condition
   SEVERITY sevRtn = NO_CONDITION;
   DString strErrValue;

   if( _pErrMsgRulesList == NULL )
   {
      SEVERITY sevRtn = getMgmtCo().getErrMsgRulesList( _pErrMsgRulesList );
   }

   if( _pErrMsgRulesList )
   {
      _pErrMsgRulesList->getEWIValue(I_("366"), idDataGroup, strErrValue );
      if( strErrValue == I_("E") || strErrValue == I_("W") )
      {
         setFieldRequired( ifds::RiskToleranceCode, idDataGroup,true );
         setValidFlag ( ifds::RiskToleranceCode, idDataGroup, false );
         havemandatoryfield = true;
      }

      _pErrMsgRulesList->getEWIValue(I_("367"), idDataGroup, strErrValue );
      if( strErrValue == I_("E") || strErrValue == I_("W") )
      {
         setFieldRequired( ifds::InvKnowledgeCode, idDataGroup,true );
         setValidFlag ( ifds::InvKnowledgeCode, idDataGroup, false );
         havemandatoryfield = true;
      }

      _pErrMsgRulesList->getEWIValue(I_("365"), idDataGroup, strErrValue );
      if( strErrValue == I_("E") || strErrValue == I_("W") )
      {
         setFieldRequired( ifds::NetWorthCode, idDataGroup,true );
         setValidFlag ( ifds::NetWorthCode, idDataGroup, false );
         havemandatoryfield = true;
      }

      _pErrMsgRulesList->getEWIValue(I_("364"), idDataGroup, strErrValue );
      if( strErrValue == I_("E") || strErrValue == I_("W") )
      {
         setFieldRequired( ifds::AnnualIncomeCode, idDataGroup,true );
         setValidFlag ( ifds::AnnualIncomeCode, idDataGroup, false );
         havemandatoryfield = true;
      }

      if(havemandatoryfield)
      {
         setUpdatedFlag( ifds::EffectiveDate, idDataGroup, true );
      }
   }
   
   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
SEVERITY Demographics::getErrMsg( DString dstrErrNum, long lErrConditionId, 
                               long lWarnConditionId, const BFDataGroupId& idDataGroup, DString idiStr )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getErrMsg" ) );

   if( _pErrMsgRulesList == NULL )
   {
      SEVERITY sevRtn = getMgmtCo().getErrMsgRulesList( _pErrMsgRulesList );
   }

   if( _pErrMsgRulesList )
      _pErrMsgRulesList->getEWI( dstrErrNum, lErrConditionId, lWarnConditionId, idDataGroup, idiStr );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY Demographics::doValidateAll (const BFDataGroupId& idDataGroup, 
   long lValidateGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   if (isFieldUpdated (ifds::GrowthPercent,   idDataGroup) || 
       isFieldUpdated (ifds::IncomePercent,   idDataGroup) || 
       isFieldUpdated (ifds::SafetyPercent,   idDataGroup) ||
       isFieldUpdated (ifds::AggressivePrcnt, idDataGroup) || 
       isFieldUpdated (ifds::ShortTermPrcnt,  idDataGroup) )
   {
       DString dstrGrowthPcnt, 
               dstrIncomePcnt, 
               dstrSafetyPcnt,
               dstrShortTermPrcnt,
               dstrAggressivePrcnt;

        getField (ifds::GrowthPercent, dstrGrowthPcnt, idDataGroup, false);
        getField (ifds::IncomePercent, dstrIncomePcnt, idDataGroup, false); 
        getField (ifds::SafetyPercent, dstrSafetyPcnt, idDataGroup, false);
        getField (ifds::ShortTermPrcnt, dstrShortTermPrcnt, idDataGroup, false);
        getField (ifds::AggressivePrcnt, dstrAggressivePrcnt, idDataGroup, false);

        double dGrowthPcnt      = DSTCommonFunctions::convertToDouble (dstrGrowthPcnt);
        double dIncomePcnt      = DSTCommonFunctions::convertToDouble (dstrIncomePcnt);
        double dSafetyPcnt      = DSTCommonFunctions::convertToDouble (dstrSafetyPcnt);
        double dShortTermPrcnt  = DSTCommonFunctions::convertToDouble (dstrShortTermPrcnt);
        double dAggressivePrcnt = DSTCommonFunctions::convertToDouble (dstrAggressivePrcnt);

        double dTotalPcnt  = dGrowthPcnt + dIncomePcnt + dSafetyPcnt + dShortTermPrcnt + dAggressivePrcnt;

        if (dTotalPcnt != 100 && dTotalPcnt != 0)
        {
            ADDCONDITIONFROMFILE (CND::ERR_TOTAL_KYC_PRCNT_MUST_BE_0_OR_100);
        }
   }

   DString dstrRegulatoryStandard, investorType, investOnBehalf;
   getField (ifds::RegulatoryStandard, dstrRegulatoryStandard, idDataGroup, false);
   getField (ifds::TypeOfInvestor, investorType, idDataGroup, false);
   getField (ifds::InvestingOnBehalf, investOnBehalf, idDataGroup, false);

   if (isNew () && (dstrRegulatoryStandard == NULL_STRING || dstrRegulatoryStandard.empty ()))
   {
         getErrMsg ( IFASTERR::BLANK_REG_STANDARD,
                     CND::ERR_BLANK_REG_STANDARD, 
                     CND::WARN_BLANK_REG_STANDARD, 
                     idDataGroup);
   }
   else if (!investorType.empty () || !investOnBehalf.empty ())
   {
      if (dstrRegulatoryStandard.empty ())
      {
         getErrMsg ( IFASTERR::BLANK_REG_STANDARD,
                     CND::ERR_BLANK_REG_STANDARD, 
                     CND::WARN_BLANK_REG_STANDARD, 
                     idDataGroup);
      }
   }

   validateRegDocsStatus (idDataGroup);
   MFAccount *pMFAccount = NULL;
   if ( !isNew() && isUpdatedForDataGroup (idDataGroup)&& 
	   getWorkSession().getMFAccount( idDataGroup, _dstrAccountNum, pMFAccount ) <= WARNING
	   && pMFAccount )
   {	
	   bool bDisplyWarnSICAV ,bDisplyWarnOEIC;
	   pMFAccount->displayEnvXrefWarningOnUpdate(idDataGroup, bDisplyWarnSICAV, bDisplyWarnOEIC);
	   if(bDisplyWarnSICAV)
		   ADDCONDITIONFROMFILE (CND::WARN_DATA_UPDATE_IMPACTS_EXTERNAL_ENV_SICAV);
	   if(bDisplyWarnOEIC)
		   ADDCONDITIONFROMFILE (CND::WARN_DATA_UPDATE_IMPACTS_EXTERNAL_ENV_OEIC);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Demographics::validateBranch( const DString& dstrBranchCode, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateBranch" ) );

   BranchList branchList( *this );
   DString dstrBrokerCode, dstrBranchName;
   MFAccount* pMFAccount = NULL;
   getWorkSession().getMFAccount( idDataGroup, _dstrAccountNum, pMFAccount );
   if ( pMFAccount ) {
      pMFAccount->getField ( ifds::BrokerCode, dstrBrokerCode, idDataGroup );
      if( dstrBranchCode != NULL_STRING && 
          branchList.init( dstrBrokerCode, dstrBranchCode ) <= WARNING )
      {
         BFObjIter bfIter( branchList, idDataGroup );
         DString branchName;

         bfIter.begin();
         if( !bfIter.end() )
         {
            Branch* pBranch = dynamic_cast <Branch*> ( bfIter.getObject() );
            pBranch->getField( ifds::BranchName, dstrBranchName, idDataGroup );            
            DString dstrCurrBusDate;
            getWorkSession().getOption( ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false ); 
            pBranch->checkEffective ( dstrCurrBusDate, idDataGroup );
            setFieldNoValidate( ifds::BranchName, dstrBranchName, idDataGroup, true, true, true, false);
         }
      }      
   }   
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
SEVERITY Demographics::validateSlsRep( const DString& dstrSlsRepCode, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateSlsRep" ) );

   MFAccount* pMFAccount = NULL;
   getWorkSession().getMFAccount( idDataGroup, _dstrAccountNum, pMFAccount );
   if ( pMFAccount ) {
      AgentList agentList( *this );
      Agent* pAgent = NULL;      
      DString dstrBrokerCode, dstrBranchCode;
      pMFAccount->getField ( ifds::BrokerCode, dstrBrokerCode, idDataGroup );
      getField( ifds::BranchCode, dstrBranchCode, idDataGroup );
      SEVERITY sevRtn;
      if ( pMFAccount->isNew () ) {
         sevRtn = agentList.init2( dstrBrokerCode, dstrBranchCode, dstrSlsRepCode, NULL_STRING, NULL_STRING, _dstrAccountNum, I_("Trade") );
      } else {
         sevRtn = agentList.init2( dstrBrokerCode, dstrBranchCode, dstrSlsRepCode, NULL_STRING, NULL_STRING, _dstrAccountNum, I_("Acct") );
      }
      if( dstrSlsRepCode != NULL_STRING && sevRtn <= WARNING )
      {
         BFObjIter bfIter( agentList, idDataGroup );
         int iNumItems = bfIter.getNumberOfItemsInList ();
         bool bNewAgent = iNumItems > 0  ? false : true;

         bfIter.begin();
         if( !bfIter.end() )
         {
            DString dstrCurrBusDate, dstrBranchName, dstrSlsrepName;
            pAgent = dynamic_cast <Agent*> ( bfIter.getObject() );
            pAgent->getField( ifds::SlsrepName, dstrSlsrepName, idDataGroup );
            pAgent->getField( ifds::BranchCode, dstrBranchCode, idDataGroup );
            pAgent->getField( ifds::BranchName, dstrBranchName, idDataGroup );
            getWorkSession().getOption( ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false ); 
            pAgent->checkEffective ( dstrCurrBusDate, idDataGroup );
            setFieldNoValidate( ifds::BrokerCode, dstrBrokerCode, idDataGroup, true, true, true, false );
            setFieldNoValidate( ifds::BranchCode, dstrBranchCode, idDataGroup, true, true, true, false );
            setFieldNoValidate( ifds::SlsrepName, dstrSlsrepName, idDataGroup, true, true, true, false );
            setFieldNoValidate( ifds::BranchName, dstrBranchName, idDataGroup, true, true, true, false );
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void Demographics::setupHouseBroker( const BFDataGroupId& idDataGroup )
{
   MFAccount* pMFAccount = NULL;       
   if (getWorkSession().getMFAccount( idDataGroup, _dstrAccountNum, pMFAccount ) <= WARNING )
   {
      if ( pMFAccount != NULL && pMFAccount->isHouseBroker ( idDataGroup ) ) 
      {
            DString dstrRepByBranch;
            getWorkSession().getOption( ifds::RepByBranch, dstrRepByBranch, idDataGroup, false );

            setFieldReadOnly ( ifds::BranchCode, idDataGroup, dstrRepByBranch != YES  );
            setFieldReadOnly ( ifds::AgentCode, idDataGroup, false );
            setFieldRequired( ifds::BranchCode, idDataGroup,true );
            setValidFlag ( ifds::BranchCode, idDataGroup, false );
            setFieldRequired( ifds::AgentCode, idDataGroup,true );
            setValidFlag ( ifds::AgentCode, idDataGroup, false );
      } 
      else 
      {
            setFieldReadOnly ( ifds::BranchCode, idDataGroup, true );
            setFieldReadOnly ( ifds::AgentCode, idDataGroup, true );
            setFieldRequired( ifds::BranchCode, idDataGroup,false );
            setValidFlag ( ifds::BranchCode, idDataGroup, true );
            setFieldRequired( ifds::AgentCode, idDataGroup,false );
            setValidFlag ( ifds::AgentCode, idDataGroup, true );
      }      
   }
}

//******************************************************************************
SEVERITY Demographics::fieldIsBlank( DString fieldName, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "fieldIsBlank" ) );

   DString idiStr;
   addIDITagValue (idiStr, I_("BLANK_FIELD"), fieldName);

   getErrMsg ( IFASTERR::FIELD_IS_BLANK,
               CND::ERR_FIELD_IS_BLANK,
               CND::WARN_FIELD_IS_BLANK,
               idDataGroup,
               idiStr);

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool Demographics::isShareHolderLevelKYC(const BFDataGroupId& idDataGroup)
{
   DString dstrKYCLevel = NULL_STRING;
   getWorkSession().getOption( ifds::KYCLevel, dstrKYCLevel, idDataGroup, false );

   dstrKYCLevel.stripLeading( '0' );

   return ( dstrKYCLevel == SHARE_HOLDER_LEVEL_KYC );
}

//******************************************************************************
SEVERITY Demographics::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );

   if (idField == ifds::TypeOfInvestor || idField == ifds::InvestingOnBehalf || ifds::RegulatoryStandard == idField )
   {
      DString typeOfInvestor, investingOnBehalf;
      bool bReadOnly = false;	  

      getField (ifds::TypeOfInvestor, typeOfInvestor, idDataGroup );
      getField (ifds::InvestingOnBehalf, investingOnBehalf, idDataGroup );

      bool bGetStandard = typeOfInvestor.empty () || investingOnBehalf.empty () ? false : true;
      DString dstrAcctEffDate = NULL_STRING;
      MFAccount* pMFAccount = NULL; 
      if( getWorkSession().getMFAccount( idDataGroup, _dstrAccountNum, pMFAccount ) <= WARNING &&
	       pMFAccount  )
            pMFAccount->getField(ifds::EffectiveDate , dstrAcctEffDate ,idDataGroup , false);

      if (bGetStandard)
      {
         getRegulatoryStandards (typeOfInvestor, investingOnBehalf, dstrAcctEffDate, idDataGroup);
      }
   }
   else if (   idField == ifds::SrcOfPymtSalary 
            || idField == ifds::SrcOfPymtBusinessIncome
            || idField == ifds::SrcOfPymtBorrowedFunds
            || idField == ifds::SrcOfPymtGiftedFunds
            || idField == ifds::SrcOfPymtPrcdsFrmDeathBenefEstate
            || idField == ifds::SrcOfPymtSocialBenefits
            || idField == ifds::SrcOfPymtOther
            //|| idField == ifds::SrcOfPymtOtherReason
            || idField == ifds::SrcOfPymtExistingInvstAccount
            || idField == ifds::SrcOfPymtOwnerSavings
            || idField == ifds::SrcOfPymtSaleOfProperty
            || idField == ifds::SrcOfPymtPensionIncome
            || idField == ifds::SrcOfPymtInheritedFunds )
   {
      std::map<BFFieldId,DString>::iterator itFieldRecord = _fieldRecordMap.find(idField);

      if (itFieldRecord != _fieldRecordMap.end())
      {
         DString fieldValue;
         getField (idField, fieldValue, idDataGroup, false);
         fieldValue.strip().upperCase();
         if (idField == ifds::SrcOfPymtOther)
         {
            if (fieldValue == I_("Y"))
            {
               setFieldReadOnly ( ifds::SrcOfPymtOtherReason, idDataGroup, false );
            }
            else
            {
               setFieldReadOnly ( ifds::SrcOfPymtOtherReason, idDataGroup, true );
               setFieldNoValidate (ifds::SrcOfPymtOtherReason, NULL_STRING, idDataGroup, false,true,true,false);
            }
         }

         updateSourceOfPayment(itFieldRecord->second,fieldValue,NULL_STRING,idDataGroup);
      }
   }
   else if (idField == ifds::SrcOfPymtOtherReason)
   {
      std::map<BFFieldId,DString>::iterator itFieldRecord = _fieldRecordMap.find(ifds::SrcOfPymtOther);

      if (itFieldRecord != _fieldRecordMap.end())
      {
         DString fieldValue;
         getField (idField, fieldValue, idDataGroup, false);
         fieldValue.strip();
         updateSourceOfPayment(itFieldRecord->second,I_("Y"),fieldValue,idDataGroup);
      }
   }
   else if (idField == ifds::IndustryCode)
   {
       setFieldNoValidate(ifds::OccupationCode, NULL_STRING, idDataGroup, false, true, true);

       initKYCOccupationSubstitutionList(idDataGroup);

       setFieldNoValidate(ifds::KYCBusinessType, NULL_STRING, idDataGroup, false, true, true);
       initKYCBusinessTypeSubstitutionList(idDataGroup);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY Demographics::getRegulatoryStandards( const DString& typeOfInvestor, 
                                               const DString & investingOnBehalf,
                                               const DString& dstrAcctEffDate,
                                               const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getRegulatoryStandards" ) );

   pRegulatoryStandardList = NULL;
   DString substList = NULL_STRING;
   BFDataGroupId dataGroup;

   // it used not to work, and now works ?!?
   //if (_bRegStandardExist) 
   //   dataGroup = BF::HOST; // record existed
   //else 
      dataGroup = idDataGroup; // NASU or setting of new record

   if (!typeOfInvestor.empty () && !investingOnBehalf.empty ())
   {
      if( getRegulatoryStandardsList (pRegulatoryStandardList, typeOfInvestor, investingOnBehalf, dstrAcctEffDate, 
                                       dataGroup) <= WARNING )
      {
         pRegulatoryStandardList->getSubstitionList (substList, dataGroup);

         DString dstrRegStandard;
         getField (ifds::RegulatoryStandard, dstrRegStandard, idDataGroup);

         int nPos = substList.find(dstrRegStandard);
         if (nPos == -1)
         {
            setFieldNoValidate (ifds::RegulatoryStandard, I_(""), idDataGroup, true, true, false, false); 
            //special treatment for displaying the reg stand of an account which had a regulatory std that has been stop-dated as of today.
            //with the chnages for P0247899 _SSBL_1792 _Scroll Down Menu project , the vew 388 will send you only the list of Reg std which are not stopped as of today.
            if(!isNew() &&  !dstrRegStandard.stripAll().empty() )
            {
              DString dstrRegStandardName;//, dstrTempSubList;              
              getField(ifds::RegStandardName, dstrRegStandardName, idDataGroup, false);
              substList += dstrRegStandard + I_("=") + dstrRegStandardName + I_(";");              
              setFieldNoValidate (ifds::RegulatoryStandard, dstrRegStandard, idDataGroup, true, true, false, false);
            }
         }
         // this is stupid solution but no other way.
      }
   }

   setFieldAllSubstituteValues( ifds::RegulatoryStandard, dataGroup, substList ); 

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY Demographics::getRegulatoryStandardsList (RegulatoryStandardList*& pRegulatoryStandardList, 
                                                   const DString& dstrTypeOfInvestor,
                                                   const DString& dstrInvsetOnBehalf,
                                                   const DString& dstrAcctEffDate,
                                                   const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getRegulatoryStandardList"));

   DString strKey;

   strKey =  I_("TypeOfInvestor=") + dstrTypeOfInvestor;
   strKey += I_("InvestOnBehalf=") + dstrInvsetOnBehalf;
   pRegulatoryStandardList = dynamic_cast< RegulatoryStandardList* > (getObject (strKey, idDataGroup));

   if (!pRegulatoryStandardList)
   {
      pRegulatoryStandardList = new RegulatoryStandardList (*this);
      if (pRegulatoryStandardList->init (dstrTypeOfInvestor, dstrInvsetOnBehalf, _dstrResidenceCode, dstrAcctEffDate) <= WARNING)
      {
         setObject ( pRegulatoryStandardList, 
                     strKey, 
                     OBJ_ACTIVITY_NONE, 
                     idDataGroup);
      }
      else
      {
         delete pRegulatoryStandardList;
         pRegulatoryStandardList = NULL;
      }

   }
   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Demographics::getDemographicsChildList(DemographicsChildList*& pDemographicsChildList,
                                                //const DString& dstrAccountNum,
                                                //const DString& dstrEntityId,
                                                const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getDemographicsChildList"));

   DString strKey = I_("KYCAttrib;");

   BFCBO *pParent = getParent();

   DString strValue, strAccountNum = I_("0"),strEntityId = I_("0");
   if (dynamic_cast<MFAccount*>(pParent))
   {
      pParent->getField( ifds::AccountNum,strValue,idDataGroup,false);
      strValue.strip().upperCase();
      strKey += I_("AccountNum=");
      strKey += strValue;
      strAccountNum = strValue;
   }
   else if (dynamic_cast<Entity*>(pParent))
   {
      pParent->getField( ifds::EntityId,strValue,idDataGroup,false);
      strValue.strip().upperCase();
      strKey += I_("EntityId=");
      strKey += strValue;
      strEntityId = strValue;
   }

   pDemographicsChildList = dynamic_cast<DemographicsChildList*>(getObject(strKey, idDataGroup));
   if (!pDemographicsChildList)
   {
       MFAccount *pMFAccount = NULL;
       bool bNewAccount = (_dstrAccountNum != I_("0") &&
                            getWorkSession().getMFAccount(idDataGroup, _dstrAccountNum, pMFAccount) <= WARNING && 
                            pMFAccount &&
                            pMFAccount->isNew());

      if (isNew() || bNewAccount)
      {
         //new empty list
         pDemographicsChildList = new DemographicsChildList(*this);
         pDemographicsChildList->init(strAccountNum,strEntityId,idDataGroup);
      }
      else
      {
         pDemographicsChildList = new DemographicsChildList(*this);
         pDemographicsChildList->init(strAccountNum, strEntityId);
      }

      if (pDemographicsChildList)
      {
         if (GETCURRENTHIGHESTSEVERITY() <= WARNING)
         {
            setObject(pDemographicsChildList, strKey, OBJ_ACTIVITY_NONE, idDataGroup);
         }
         else
         {
            delete pDemographicsChildList;
            pDemographicsChildList = NULL;
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
SEVERITY Demographics::validateRegDocsStatus (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateRegDocsStatus"));

   DString  dstrRegDocExist;
   getWorkSession ().getOption (ifds::RegDocsExist, dstrRegDocExist, idDataGroup, false);

   // env supports reg docs
   if (dstrRegDocExist == Y)
   {
      RegDocumentList *pRegDocumentList = NULL;
      MFAccount* pMFAccount = NULL;

      if ( getWorkSession().getMFAccount (idDataGroup, _dstrAccountNum, pMFAccount) <= WARNING && 
           pMFAccount && 
           !pMFAccount->isNew ()) 
      {
         ENTITIES_VECTOR acctOwnerEntities;

         pMFAccount->getAcctOwnerEntities (acctOwnerEntities, idDataGroup);

         int iNumOfEntities = acctOwnerEntities.size ();

         for (int i = 0; i < iNumOfEntities; ++i)
         {
            if ( pMFAccount->getRegDocumentsList(pRegDocumentList, acctOwnerEntities[i], idDataGroup, true) <= WARNING &&
                 pRegDocumentList)
            {
               if (pRegDocumentList->isAnyStatusBlank (idDataGroup))
               {
                  ADDCONDITIONFROMFILE (CND::ERR_DOC_STATUS_BLANK);
               }
            }
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY ();
}

//******************************************************************************
void Demographics::doReset( const BFDataGroupId& idDataGroup )
{
   DString dstrCurrentBusinessDate;
   if (getWorkSession().getOption( ifds::CurrBusDate, dstrCurrentBusinessDate, idDataGroup, false ))
   {
      setFieldNoValidate( ifds::LastReviewDate, dstrCurrentBusinessDate, idDataGroup, false, true, true );      
   }  

   commonInit(idDataGroup);
}

//******************************************************************************
SEVERITY Demographics::getDefaultRegulatoryStandard(DefaultRegulatoryStandard *&pDefaultRegulatoryStandard, 
                                                    const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getDefaultRegulatoryStandard"));

   MFAccount *pMFAccount = NULL;
   Shareholder *pShareholder = NULL;
   DString strKey, dstrTypeOfInvestor, dstrInvestingOnBehalf, dstrAcctType, 
      dstrTaxType, dstrAcctDesignation, dstrTaxJurisCode, dstrShrNum;

   getField(ifds::TypeOfInvestor, dstrTypeOfInvestor, idDataGroup);
   getField(ifds::InvestingOnBehalf, dstrInvestingOnBehalf, idDataGroup);

   getParent()->getField(ifds::AcctType, dstrAcctType, idDataGroup);
   getParent()->getField(ifds::TaxType, dstrTaxType, idDataGroup);
   getParent()->getField(ifds::AcctDesignation, dstrAcctDesignation, idDataGroup);
   getParent()->getField(ifds::ShrNum, dstrShrNum, idDataGroup);

   if (getWorkSession().getShareholder(idDataGroup, dstrShrNum, pShareholder) <= WARNING && pShareholder)
   {
      pShareholder->getField(ifds::TaxJurisCode, dstrTaxJurisCode, idDataGroup);
   }

   strKey =  I_("TypeOfInvestor=")		+ dstrTypeOfInvestor;
   strKey += I_(",InvestOnBehalf=")	+ dstrInvestingOnBehalf;
   strKey += I_(",AcctType=")			+ dstrAcctType;
   strKey += I_(",TaxType=")			+ dstrTaxType;
   strKey += I_(",AcctDesignation=")	+ dstrAcctDesignation;
   strKey += I_(",TaxJurisCode=")		+ dstrTaxJurisCode;

   pDefaultRegulatoryStandard = NULL;
   pDefaultRegulatoryStandard = dynamic_cast<DefaultRegulatoryStandard*> (getObject(strKey, idDataGroup));

   if (!pDefaultRegulatoryStandard)
   {
      pDefaultRegulatoryStandard = new DefaultRegulatoryStandard (*this);
      SEVERITY serv = pDefaultRegulatoryStandard->init(idDataGroup, 
                                                       dstrAcctType, 
                                                       dstrTaxType, 
                                                       dstrAcctDesignation, 
                                                       dstrTaxJurisCode, 
                                                       dstrTypeOfInvestor, 
                                                       dstrInvestingOnBehalf);

      if (serv <= WARNING && pDefaultRegulatoryStandard)
      {
         setObject(pDefaultRegulatoryStandard, strKey, OBJ_ACTIVITY_NONE, idDataGroup);
      }
      else
      {
         delete pDefaultRegulatoryStandard;
         pDefaultRegulatoryStandard = NULL;
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Demographics::loadSourceOfPayment(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("loadSourceOfPayment"));

   std::map<DString,BFFieldId> recordFieldMap;

   recordFieldMap.insert(std::pair<DString,BFFieldId>(SOURCE_OF_PAYMENT::SALARY,ifds::SrcOfPymtSalary));
   recordFieldMap.insert(std::pair<DString,BFFieldId>(SOURCE_OF_PAYMENT::BORROWEDFUNDS,ifds::SrcOfPymtBorrowedFunds));
   recordFieldMap.insert(std::pair<DString,BFFieldId>(SOURCE_OF_PAYMENT::PRCDSFRMDEATHBENEFESTATE,ifds::SrcOfPymtPrcdsFrmDeathBenefEstate));
   recordFieldMap.insert(std::pair<DString,BFFieldId>(SOURCE_OF_PAYMENT::OWNERSAVINGS,ifds::SrcOfPymtOwnerSavings));
   recordFieldMap.insert(std::pair<DString,BFFieldId>(SOURCE_OF_PAYMENT::PENSIONINCOME,ifds::SrcOfPymtPensionIncome));
   recordFieldMap.insert(std::pair<DString,BFFieldId>(SOURCE_OF_PAYMENT::BUSINESSINCOME,ifds::SrcOfPymtBusinessIncome));
   recordFieldMap.insert(std::pair<DString,BFFieldId>(SOURCE_OF_PAYMENT::GIFTEDFUNDS,ifds::SrcOfPymtGiftedFunds));
   recordFieldMap.insert(std::pair<DString,BFFieldId>(SOURCE_OF_PAYMENT::SOCIALBENEFITS,ifds::SrcOfPymtSocialBenefits));
   recordFieldMap.insert(std::pair<DString,BFFieldId>(SOURCE_OF_PAYMENT::EXISTINGINVSTACCOUNT,ifds::SrcOfPymtExistingInvstAccount));
   recordFieldMap.insert(std::pair<DString,BFFieldId>(SOURCE_OF_PAYMENT::SALEOFPROPERTY,ifds::SrcOfPymtSaleOfProperty));
   recordFieldMap.insert(std::pair<DString,BFFieldId>(SOURCE_OF_PAYMENT::INHERITEDFUNDS,ifds::SrcOfPymtInheritedFunds));
   recordFieldMap.insert(std::pair<DString,BFFieldId>(SOURCE_OF_PAYMENT::OTHER,ifds::SrcOfPymtOther));

   DemographicsChildList* pDemographicsChildList = NULL;
   
   if (getDemographicsChildList(pDemographicsChildList,idDataGroup) <= WARNING && pDemographicsChildList)
   {
       BFObjIter iterDemographicsChildList(*pDemographicsChildList,
           idDataGroup,
           false,
           BFObjIter::NON_DELETED);

       iterDemographicsChildList.begin();

       while(!iterDemographicsChildList.end())
       {
           DString kycAttribCode, kycAttribStat;

           iterDemographicsChildList.getObject()->getField(ifds::KYCAttribCode,kycAttribCode,idDataGroup,false);
           iterDemographicsChildList.getObject()->getField(ifds::KYCAttribStat,kycAttribStat,idDataGroup,false);
           kycAttribCode.strip().upperCase(); 
           kycAttribStat.strip().upperCase();

           std::map<DString,BFFieldId>::iterator itKYCAttrib = recordFieldMap.find(kycAttribCode);

           if (itKYCAttrib != recordFieldMap.end())
           {
               setFieldNoValidate(itKYCAttrib->second,kycAttribStat,idDataGroup,false,true,true,false);

               if (itKYCAttrib->second == ifds::SrcOfPymtOther)
               {
                   DString kycAttribDesc;
                   iterDemographicsChildList.getObject()->getField(ifds::KYCAttribDesc,kycAttribDesc,idDataGroup,false);
                   kycAttribDesc.strip();
                   setFieldNoValidate(ifds::SrcOfPymtOtherReason,kycAttribDesc,idDataGroup,false,true,true,false);

                   if (kycAttribStat != I_("Y"))
                   {
                       setFieldReadOnly (ifds::SrcOfPymtOtherReason, idDataGroup, true);
                   }
                   else
                   {
                       setFieldReadOnly (ifds::SrcOfPymtOtherReason, idDataGroup, false);
                   }
               }
           }

           ++iterDemographicsChildList;
       }
   }

   recordFieldMap.clear();

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Demographics::updateSourceOfPayment(const DString& code, 
                                             const DString& status, 
                                             const DString& desc, 
                                             const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("updateSourceOfPayment"));

   DemographicsChildList* pDemographicsChildList = NULL;
   getDemographicsChildList(pDemographicsChildList,idDataGroup);

   if (pDemographicsChildList)
   {
      BFObjIter iter ( *pDemographicsChildList, 
                        idDataGroup, 
                        false, 
                        BFObjIter::ITERTYPE::NON_DELETED);

      DString dstrAccountable, dstrBackDatedReason;

      if (iter.getNumberOfItemsInList () == 0)
      {
         pDemographicsChildList->addNewKYCAttribRecord(code,status,idDataGroup);
      }
      else
      {
         bool bFoundExistingRecord = false;
         iter.begin();

         BFCBO *pObj = NULL;
         DString kycAttribCode;
         while (!iter.end())
         {
            iter.getObject()->getField (ifds::KYCAttribCode, kycAttribCode, idDataGroup,false);
            kycAttribCode.strip().upperCase();

            if (kycAttribCode == code)
            {
               pObj = dynamic_cast<BFCBO *>(iter.getObject());
               bFoundExistingRecord = true;
               break;
            }

            ++iter;
         }

         if (bFoundExistingRecord && pObj != NULL)
         {
            pObj->setField (ifds::KYCAttribStat,status,idDataGroup,false);
            if (kycAttribCode == SOURCE_OF_PAYMENT::OTHER)
            {
               pObj->setField (ifds::KYCAttribDesc,desc,idDataGroup,false);
            }
         }
         else
         {
            pDemographicsChildList->addNewKYCAttribRecord(code,status,idDataGroup);
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//****************************************************************************
SEVERITY Demographics::commonInit(const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("commonInit"));

   initKYCIndustrySubstitutionList(idDataGroup);
   initKYCOccupationSubstitutionList(idDataGroup);
   initKYCBusinessTypeSubstitutionList(idDataGroup);
   initKYCLegalFormSubstitutionList(idDataGroup);

   MFAccount* pMFAccount = nullptr; 
   DString strAccountType;
   if( getWorkSession().getMFAccount( idDataGroup, _dstrAccountNum, pMFAccount ) <= WARNING &&
      pMFAccount != nullptr )
   {
      pMFAccount->getField( ifds::AcctType, strAccountType, idDataGroup, false );
      strAccountType.strip().upperCase();

      bool bAllowToChange = DSTCommonFunctions::codeInList( strAccountType, INDIVIDUAL_ACCOUNT_TYPE_LIST );

      setFieldReadOnly(ifds::KYCLegalForm,idDataGroup, bAllowToChange);
      setFieldReadOnly(ifds::KYCBusinessType,idDataGroup,bAllowToChange);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Demographics::initKYCIndustrySubstitutionList(const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("initKYCIndustrySubstitutionList"));

    DString dstrIndustryCodeSubsList;
    BFProperties *pProperties = NULL;
    TranslationTable *pActiveIndustryCodeMisc = NULL;
    pProperties = getFieldProperties(ifds::IndustryCode, idDataGroup);

     if (pProperties)
        pProperties->getAllSubstituteValues(dstrIndustryCodeSubsList);

     if (getMgmtCo().getTranslationTable(KYC_MISC_INFO::INDUSTRY, pActiveIndustryCodeMisc) <= WARNING && pActiveIndustryCodeMisc)
     {
         DString dstrActiveIndustryCodeList;
         DString tmpIndustryCodeList = dstrIndustryCodeSubsList;

         pActiveIndustryCodeMisc->getCodeList(dstrActiveIndustryCodeList);

         while (tmpIndustryCodeList != NULL_STRING)
         {
            DString::size_type pos = 0;
            DString dstrIndustryCodeDesc, dstrIndustryCode;

            EXTRACT_VALUE(tmpIndustryCodeList, dstrIndustryCodeDesc, I_(";"));
            CHOP_STRING(tmpIndustryCodeList, I_(";"));

            EXTRACT_VALUE(dstrIndustryCodeDesc, dstrIndustryCode, I_("="));
            
            if (!DSTCommonFunctions::codeInList(dstrIndustryCode, dstrActiveIndustryCodeList))
            {
                dstrIndustryCodeSubsList = removeItemFromSubtList(dstrIndustryCodeSubsList, dstrIndustryCode);
            }
         }
     }

    setFieldAllSubstituteValues(ifds::IndustryCode, idDataGroup, dstrIndustryCodeSubsList);

    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY Demographics::initKYCLegalFormSubstitutionList(const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("initKYCIndustrySubstitutionList"));

    DString dstrLegalFormSubsList;
    BFProperties *pProperties = NULL;
    TranslationTable *pActiveLegalFormMisc = NULL;
    pProperties = getFieldProperties(ifds::KYCLegalForm, idDataGroup);

     if (pProperties)
        pProperties->getAllSubstituteValues(dstrLegalFormSubsList);

     if (getMgmtCo().getTranslationTable(KYC_MISC_INFO::LEGAL_FORM, pActiveLegalFormMisc) <= WARNING && pActiveLegalFormMisc)
     {
         DString dstrActiveLegalFormList;
         DString tmpLegalFormSubsList = dstrLegalFormSubsList;

         pActiveLegalFormMisc->getCodeList(dstrActiveLegalFormList);

         while (tmpLegalFormSubsList != NULL_STRING)
         {
            DString::size_type pos = 0;
            DString dstrLegalFormDesc, dstrLegalForm;

            EXTRACT_VALUE(tmpLegalFormSubsList, dstrLegalFormDesc, I_(";"));
            CHOP_STRING(tmpLegalFormSubsList, I_(";"));

            EXTRACT_VALUE(dstrLegalFormDesc, dstrLegalForm, I_("="));
            dstrLegalForm.stripLeading(I_('0'));

            if (!DSTCommonFunctions::codeInList(dstrLegalForm, dstrActiveLegalFormList))
            {
                dstrLegalFormSubsList = removeItemFromSubtList(dstrLegalFormSubsList, dstrLegalForm);
            }
         }
     }

     setFieldAllSubstituteValues(ifds::KYCLegalForm, idDataGroup, dstrLegalFormSubsList);

     return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void Demographics::removeInactiveBusinessTypeFromSublist(const BFDataGroupId &idDataGroup)
{
    DString dstrBusinessTypeSubsList;
    BFProperties *pProperties = NULL;
    TranslationTable *pActiveBusinessTypeMisc = NULL;
    pProperties = getFieldProperties(ifds::KYCBusinessType, idDataGroup);

     if (pProperties)
        pProperties->getAllSubstituteValues(dstrBusinessTypeSubsList);

     if (getMgmtCo().getTranslationTable(KYC_MISC_INFO::BUSSINESS_TYPE, pActiveBusinessTypeMisc) <= WARNING && pActiveBusinessTypeMisc)
     {
         DString dstrActiveBusinessTypeList;
         DString tmpBusinessTypeSubsList = dstrBusinessTypeSubsList;

         pActiveBusinessTypeMisc->getCodeList(dstrActiveBusinessTypeList);

         while (tmpBusinessTypeSubsList != NULL_STRING)
         {
            DString::size_type pos = 0;
            DString dstrBusinessTypeDesc, dstrBusinessType;

            EXTRACT_VALUE(tmpBusinessTypeSubsList, dstrBusinessTypeDesc, I_(";"));
            CHOP_STRING(tmpBusinessTypeSubsList, I_(";"));

            EXTRACT_VALUE(dstrBusinessTypeDesc, dstrBusinessType, I_("="));
            dstrBusinessType.stripLeading(I_('0'));
            
            if (!DSTCommonFunctions::codeInList(dstrBusinessType, dstrActiveBusinessTypeList))
            {
                dstrBusinessTypeSubsList = removeItemFromSubtList(dstrBusinessTypeSubsList, dstrBusinessType);
            }
         }
     }

     setFieldAllSubstituteValues(ifds::KYCBusinessType, idDataGroup, dstrBusinessTypeSubsList);
}

//******************************************************************************
SEVERITY Demographics::initKYCBusinessTypeSubstitutionList(const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("initKYCBusinessTypeSubstitutionList"));

    DString dstrBusinessTypeSubsList, dstrIndustryCode, indtLnkBusTypeList;
    BFProperties *pProperties = NULL;
    TranslationTable *pActiveBusinessTypeMisc = NULL;
    TranslationTable *pIndtLnkBusinessTypeMisc = NULL;
    pProperties = getFieldProperties(ifds::KYCBusinessType, idDataGroup);

    getField(ifds::IndustryCode, dstrIndustryCode, idDataGroup);

     if (pProperties)
     {
        pProperties->reinitAllSubstValues();
        removeInactiveBusinessTypeFromSublist(idDataGroup);
        pProperties->getAllSubstituteValues(dstrBusinessTypeSubsList);
     }

     if (dstrIndustryCode != NULL_STRING &&
        getMgmtCo().getTranslationTable(KYC_MISC_INFO::INDUSTRY_LINK_OCCUPATION, pIndtLnkBusinessTypeMisc) <= WARNING && pIndtLnkBusinessTypeMisc &&
        getMgmtCo().getTranslationTable(KYC_MISC_INFO::BUSSINESS_TYPE, pActiveBusinessTypeMisc) <= WARNING && pActiveBusinessTypeMisc)
     {
        DString indtLnkBusinessTypeList, businessTypeMiscCodeList, lnkToBusinessTypeGroupCode;
        DString indtLnkBusinessTypeValue;

        pIndtLnkBusinessTypeMisc->getDescByCode(KYC_MISC_INFO::BUSSINESS_TYPE + dstrIndustryCode, indtLnkBusinessTypeList);

        BFObjIter iterBusinessTypeMisc(*pActiveBusinessTypeMisc, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
        while(!iterBusinessTypeMisc.end())
        {
           DString dstrBusinessTypeCategoryList, dstrBusinessTypeCode;
           bool removeCodeFromSubsList = true;
           iterBusinessTypeMisc.getObject()->getField(ifds::MiscCategory, dstrBusinessTypeCategoryList, idDataGroup);
           iterBusinessTypeMisc.getObject()->getField(ifds::MiscCode, dstrBusinessTypeCode, idDataGroup);

           while (dstrBusinessTypeCategoryList != NULL_STRING)
           {
              DString dstrBusinessTypeCategory;
              DString::size_type pos = 0;

              EXTRACT_VALUE(dstrBusinessTypeCategoryList, dstrBusinessTypeCategory, I_(","))
              CHOP_STRING(dstrBusinessTypeCategoryList, I_(","))

              if (DSTCommonFunctions::codeInList(dstrBusinessTypeCategory, indtLnkBusinessTypeList))
              {
                 removeCodeFromSubsList = false;
                 break;
              }
           }

           if (removeCodeFromSubsList)
              dstrBusinessTypeSubsList = removeItemFromSubtList(dstrBusinessTypeSubsList, dstrBusinessTypeCode);

           ++iterBusinessTypeMisc;
        }
     }
     else // Industry isn't selected yet.
     {
        dstrBusinessTypeSubsList = NULL_STRING;
     }

     setFieldAllSubstituteValues(ifds::KYCBusinessType, idDataGroup, dstrBusinessTypeSubsList);

     return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void Demographics::removeInactiveOccupationsFromSublist(const BFDataGroupId &idDataGroup)
{
    DString dstrOccupationSubsList;
    BFProperties *pProperties = NULL;
    TranslationTable *pActiveOccupationMisc = NULL;
    pProperties = getFieldProperties(ifds::OccupationCode, idDataGroup);

     if (pProperties)
        pProperties->getAllSubstituteValues(dstrOccupationSubsList);

     if (getMgmtCo().getTranslationTable(KYC_MISC_INFO::OCCUPATION, pActiveOccupationMisc) <= WARNING && pActiveOccupationMisc)
     {
         DString dstrActiveOccupationList;
         DString tmpOccupationSubsList = dstrOccupationSubsList;

         pActiveOccupationMisc->getCodeList(dstrActiveOccupationList);

         while (tmpOccupationSubsList != NULL_STRING)
         {
            DString::size_type pos = 0;
            DString dstrOccupationDesc, dstrOccupation;

            EXTRACT_VALUE(tmpOccupationSubsList, dstrOccupationDesc, I_(";"));
            CHOP_STRING(tmpOccupationSubsList, I_(";"));

            EXTRACT_VALUE(dstrOccupationDesc, dstrOccupation, I_("="));
            
            if (!DSTCommonFunctions::codeInList(dstrOccupation, dstrActiveOccupationList))
            {
                dstrOccupationSubsList = removeItemFromSubtList(dstrOccupationSubsList, dstrOccupation);
            }
         }
     }

     setFieldAllSubstituteValues(ifds::OccupationCode, idDataGroup, dstrOccupationSubsList);
}

//******************************************************************************
SEVERITY Demographics::initKYCOccupationSubstitutionList(const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("initKYCOccupationSubstitutionList"));

    DString dstrOccptSubsList, dstrIndustryCode;
    BFProperties *pProperties = NULL;
    TranslationTable *pOccupationMisc = NULL;
    TranslationTable *pIndtLnkOccptMisc = NULL;

    getField(ifds::IndustryCode, dstrIndustryCode, idDataGroup);
    pProperties = getFieldProperties(ifds::OccupationCode, idDataGroup);

    if (pProperties)
    {
        pProperties->reinitAllSubstValues();
        removeInactiveOccupationsFromSublist(idDataGroup);
        pProperties->getAllSubstituteValues(dstrOccptSubsList);
    }

    if (dstrIndustryCode != NULL_STRING &&
        getMgmtCo().getTranslationTable(KYC_MISC_INFO::INDUSTRY_LINK_OCCUPATION, pIndtLnkOccptMisc) <= WARNING && pIndtLnkOccptMisc &&
        getMgmtCo().getTranslationTable(KYC_MISC_INFO::OCCUPATION, pOccupationMisc) <= WARNING && pOccupationMisc) 
    {
        DString indtLnkOccptList, occptMiscCodeList, lnkToOccptGroupCode;
        DString indtLnkOccptValue;

        pIndtLnkOccptMisc->getDescByCode(KYC_MISC_INFO::INDUSTRY + dstrIndustryCode, indtLnkOccptList);

        BFObjIter iterOccupationMisc(*pOccupationMisc, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
        while(!iterOccupationMisc.end())
        {
            DString dstrOccptCategoryList, dstrOccptCode;
            bool removeCodeFromSubsList = true;
            iterOccupationMisc.getObject()->getField(ifds::MiscCategory, dstrOccptCategoryList, idDataGroup);
            iterOccupationMisc.getObject()->getField(ifds::MiscCode, dstrOccptCode, idDataGroup);

            while (dstrOccptCategoryList != NULL_STRING)
            {
                DString dstrOccptCategory;
                DString::size_type pos = 0;

                EXTRACT_VALUE(dstrOccptCategoryList, dstrOccptCategory, I_(","))
                CHOP_STRING(dstrOccptCategoryList, I_(","))

                if (DSTCommonFunctions::codeInList(dstrOccptCategory, indtLnkOccptList))
                {
                    removeCodeFromSubsList = false;
                    break;
                }
            }

            if (removeCodeFromSubsList)
                dstrOccptSubsList = removeItemFromSubtList(dstrOccptSubsList, dstrOccptCode);

            ++iterOccupationMisc;
        }
    }
    else // Industry isn't selected yet.
    {
        dstrOccptSubsList = NULL_STRING;
    }

    setFieldAllSubstituteValues(ifds::OccupationCode, idDataGroup, dstrOccptSubsList);

    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/Demographics.cpp-arc  $
 * 
 *    Rev 1.52   Oct 17 2011 03:22:56   kitticha
 * PETP0186486 FN14 IN2698689 - KYC Risk Tolerance issues.
 * 
 *    Rev 1.51   Sep 16 2011 06:34:52   kitticha
 * PETP0186486 - KYC Risk Tolerance.
 * 
 *    Rev 1.50   Mar 31 2009 11:12:02   jankovii
 * IN 1632334 - No option to use Indirect Yes in KYC screen
 * 
 *    Rev 1.49   03 Nov 2008 17:32:32   popescu
 * KYC/AML - Joint accounts feature - after System Integrated Testing
 * 
 *    Rev 1.48   31 Oct 2008 16:18:00   popescu
 * KYC/AML - joint accounts feature
 * 
 *    Rev 1.47   Oct 28 2008 08:29:56   jankovii
 * PET 59888 FN03 AML KYC.
 * 
 *    Rev 1.46   Oct 15 2008 11:23:06   jankovii
 * IN 1433670 & 1429036.
 * 
 *    Rev 1.45   Oct 10 2008 02:42:46   daechach
 * in# 1441510 - KYC Desktop: Demographics screen - save issue - , Additional bypass logic in case that Entity level KYC is updated.
 * 
 *    Rev 1.44   Oct 10 2008 02:34:44   daechach
 * in# 1438406 - KYC Desktop - Number of Dependents Field Issue, more preventive logic to ensure default value of fields. 
 * 
 *    Rev 1.43   Oct 10 2008 02:31:20   daechach
 * PET0128026 - KYC Phase 2 - More preventive logic to ensure default value of 'SuppressKYCLetter' fields. 
 * 
 *    Rev 1.42   Sep 26 2008 12:18:26   jankovii
 * Sunc up: IN 1420802.
 * 
 *    Rev 1.41   Sep 18 2008 14:24:40   jankovii
 * Sync up IN 1415669 - Error message prevents User from saving any changes made under Demographics scre
 * 
 *    Rev 1.40   Sep 17 2008 11:29:58   jankovii
 * 1416410 - Desktop error- unable to open account
 * 
 *    Rev 1.39   Sep 12 2008 10:48:48   jankovii
 * Sync up: IN 1403130 - On behalf of 3rd party, R.S not disp.correctly
 * 
 *    Rev 1.38   Sep 12 2008 06:16:40   daechach
 * PET0128026 - KYC Phase 2
 * 
 *    Rev 1.37   Aug 28 2008 14:30:48   jankovii
 * IN 1388930 - NASU flow does not update document list unless at least one document.
 * 
 *    Rev 1.36   Aug 22 2008 16:05:02   jankovii
 * IN 1386917 PET59888FN01-Add KYCCountryCode that will be used by AWD.
 * 
 *    Rev 1.35   Jul 25 2008 14:31:14   jankovii
 * PET 59888 - AML Enhancement.
 * 
 *    Rev 1.34   Jul 17 2008 14:36:22   jankovii
 * PET 59888 AML Enhancement.
 * 
 *    Rev 1.33   Jul 16 2008 16:04:24   jankovii
 * PET 59888 - AML Enhancement.
 * 
 *    Rev 1.32   Feb 08 2008 10:35:44   daechach
 * in# 1148522 - No value on Specialty Code in iFast - Strip leading zero of KYCLevel.
 * 
 *    Rev 1.31   Aug 22 2007 13:19:08   kovacsro
 * IN977835 - KYCMailedDate read-only; Effective Date not a required field
 * 
 *    Rev 1.30   Aug 10 2007 14:56:40   kovacsro
 * PET2372 FN02 - KYC fixed read only fields
 * 
 *    Rev 1.29   Aug 08 2007 17:23:28   kovacsro
 * PET2372 FN02 - KYC fix for EffectiveDate
 * 
 *    Rev 1.28   Aug 06 2007 16:13:50   kovacsro
 * PET2372 FN02 - FDP-AIM KYC new KYC fields read-only for shareholder level
 * 
 *    Rev 1.27   Jul 27 2007 16:51:24   kovacsro
 * PET 2372 FN02 FDP-AIM KYC
 * 
 *    Rev 1.26   Nov 14 2004 14:30:36   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.25   Jan 19 2004 13:53:26   FENGYONG
 * Add dovalidateall override
 * 
 *    Rev 1.24   Dec 31 2003 11:54:12   popescu
 * PTS 10025659, force a refresh of the Sahreholder object at host level if we have Demographics updates
 * 
 *    Rev 1.23   Dec 01 2003 10:05:58   FENGYONG
 * PTS 10024375 , Setmandatory field for newaccount existing shareholder
 * 
 *    Rev 1.22   Sep 18 2003 14:16:24   FENGYONG
 * Add shrNum to the request
 * 
 *    Rev 1.21   Aug 25 2003 10:03:06   HSUCHIN
 * bug fix for NASU where the sales rep check view call was incorrect.
 * 
 *    Rev 1.20   Aug 21 2003 17:14:02   WINNIE
 * Add new condition to cover the Demographic validation against Growth, Safety and Income total percentage
 * 
 *    Rev 1.19   Aug 19 2003 15:55:14   HSUCHIN
 * added branchcode/agent code fields/validation
 * 
 *    Rev 1.18   Aug 19 2003 11:05:40   HERNANDO
 * Added MemorablePlace, MemorableWord, and MemorableDate.
 * 
 *    Rev 1.17   Jul 31 2003 15:45:38   FENGYONG
 * control required field by error Number
 * 
 *    Rev 1.16   Jul 31 2003 13:25:04   FENGYONG
 * Add Historical logic
 * 
 *    Rev 1.15   Jul 21 2003 10:56:44   FENGYONG
 * set KYC mandatory field based on error num
 * 
 *    Rev 1.14   Jul 11 2003 16:40:00   FENGYONG
 * Add admin date relate fields
 * 
 *    Rev 1.13   Jul 11 2003 16:03:22   FENGYONG
 * move demographic from shareholder to MFAccount
 * 
 *    Rev 1.12   May 22 2003 14:12:18   popescu
 * Replaced name 'BankInstr' with 'BankInstructions'; 
 * simplified child lists getters for the Shareholder object
 * 
 *    Rev 1.11   Mar 21 2003 18:03:06   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.10   Oct 09 2002 23:54:12   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.9   Aug 29 2002 12:55:16   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.8   Aug 06 2002 14:59:08   HERNANDO
 * PTS 10009268 - Clean up.  Removed ERR_DATE_FUNCTIONS from Namespace.
 * 
 *    Rev 1.7   22 May 2002 18:26:46   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.6   03 May 2001 14:06:08   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.5   Jan 18 2001 16:04:48   YINGBAOL
 * add eTracker
 * 
 *    Rev 1.4   Dec 17 2000 20:22:54   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.3   Nov 07 2000 17:26:32   OLTEANCR
 * bug fix
 * 
 *    Rev 1.2   Nov 02 2000 15:03:24   OLTEANCR
 * new data brokering
 * 
 *    Rev 1.1   Jun 23 2000 15:38:04   HUANGSHA
 * put Required flag on EffectiveDate
 * 
 *    Rev 1.0   Feb 15 2000 10:59:52   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.8   Jan 30 2000 17:56:50   POPESCUS
 * SIT fixes
 * 
 *    Rev 1.7   Jan 25 2000 17:13:08   POPESCUS
 * fixes for updates
 * 
 *    Rev 1.6   Dec 12 1999 16:25:16   POPESCUS
 * Xchgdata issue; create and delete the object in the CBO
// 
*/
