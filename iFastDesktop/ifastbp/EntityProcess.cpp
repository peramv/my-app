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
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : EntityProcess.cpp
// ^AUTHOR : Adrian & Serban
// ^DATE   : 23/04/1999
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : EntityProcess
//    This class manages the management company and profile selection.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include <bfproc\bpglobal.h>
#include <bfcbo\bfobjiter.hpp>
#include <bfdata\bfdatafielditer.hpp>
#include "entityprocess.hpp"
#include <ifastcbo\accountentityxref.hpp>
#include <ifastcbo\accountentityxrefobject.hpp>
#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastcbo\entity.hpp>
#include <ifastcbo\entityidslist.hpp>
#include <ifastcbo\entityids.hpp>
#include <ifastcbo\entitylist.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\shareholder.hpp>
#include <ifastcbo\whereusedlist.hpp>
#include <ifastcbo\MgmtCoOptions.hpp>
#include <ifastcbo\worksessionentitylist.hpp>
#include <ifastcbo\EntityRisk.hpp>
#include "entityprocessincludes.h"
#include "entitysearchprocessincludes.h"
#include "fillsearchcriteriaprocessincludes.h"
#include "nasuprocessincludes.h"
#include "mfcaninterprocparam.hpp"
#include <ifastcbo\EntitySearchIDValueValidation.hpp>
#define INCLUDED_ASSERT_H
#include <assert.h>
#include <ifastdataimpl\dse_dstc0004_vw.hpp>
#include <ifastdataimpl\dse_dstc0050_vw.hpp>
#include <ifastdataimpl\dse_dstc0051_vw.hpp>
#include <ifastdataimpl\dse_dstc0490_req.hpp>
#include <ifastdataimpl\dse_dstc0490_vw.hpp>
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_ENTITY_MAINTENANCE;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_SEARCH;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ENTITY;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< EntityProcess > processCreator( CMD_BPROC_ENTITY );

#include <core\bfcbo\bfcbo.hpp>
#include <ifastcbo\mfcancbo.hpp>

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME                     = I_( "EntityProcess" );
   const DString  EMPTY_STRING;
   const I_CHAR * const YES                           = I_( "Y" );
   const I_CHAR * const NO                            = I_( "N" );
   const I_CHAR * const PERFORMSEARCH                 = I_( "PerformSearch" );
   const I_CHAR * ENTITY_TYPE_ACC_OWNER               = I_( "01" );
   const I_CHAR * ENTITY_TYPE_OWNER_SPOUSE            = I_( "98" );
   const I_CHAR * RESP_BENEFICIARY                    = I_( "50" );
   const I_CHAR * PARENT_GUARDIAN_ENTITY_TYPE         = I_( "51" );
   const I_CHAR * RESP_DESIGNATED_INSTIT_ENTITY_TYPE  = I_( "52" );
   const I_CHAR * RESP_PCG_INDIV_ENTITY_TYPE          = I_( "55" );
   const I_CHAR * RESP_PCG_INST_ENTITY_TYPE           = I_( "56" );
   const I_CHAR * REGISTRATION_AGENT_ENTITY_TYPE      = I_( "64" );

   const I_CHAR * ENTITY_TYPE_PRIMARY_BENEF           = I_( "07" );
   const I_CHAR * ENTITY_TYPE_SECONDARY_BENEF         = I_( "08" );
   const I_CHAR * SUCCESSOR                           = I_( "09" );
   const I_CHAR * REGISTRATION_AGENT_WHERE_USED_CODE  = I_( "14" );

}

extern CLASS_IMPORT BF_OBJ_TYPE OBJ_TYPE_ENTITY;

namespace CND
{
   extern const long BP_ERR_NOT_ALLOW_SETFOCUS;
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
   extern CLASS_IMPORT const long BP_ERR_INVALID_METHOD_CALL;
   extern const long BP_ERR_NO_SEARCH_CRITERIA;
}

namespace ENTPROC
{
   const I_CHAR * const ACCOUNT_NUM       = I_( "AccountNum" );
   const I_CHAR * const ENTITY_ID         = I_( "EntityId" );
   const I_CHAR * const CURRENT_KEY       = I_( "CurrentKey" );
   const I_CHAR * const KEY               = I_( "Key" );
   const I_CHAR * const EXIST_ACCOUNT     = I_( "ExistAccount" );
   const I_CHAR * const MODEL_ACCOUNT_NUM = I_( "ModelAccountNum" );

}

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFTextFieldId FrFundNumber;
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate2;
   extern CLASS_IMPORT const BFTextFieldId CountryCode;
   extern CLASS_IMPORT const BFTextFieldId CountryName;
   extern CLASS_IMPORT const BFTextFieldId BeneficiaryTitleDisplay;
   extern CLASS_IMPORT const BFNumericFieldId LastActiveEntityId;
   extern CLASS_IMPORT const BFTextFieldId OwnerSpouseName;
   extern CLASS_IMPORT const BFTextFieldId NAME_LENGTH;
   extern CLASS_IMPORT const BFTextFieldId SalutationFormat;
   extern CLASS_IMPORT const BFTextFieldId AcctType;
   extern CLASS_IMPORT const BFTextFieldId EUSDParticip;
   extern CLASS_IMPORT const BFTextFieldId UpdShrTaxJuris;
   extern CLASS_IMPORT const BFTextFieldId CountryOfBirth;
   extern CLASS_IMPORT const BFTextFieldId ContactName;
   extern CLASS_IMPORT const BFTextFieldId OnLineEntExcept;
   extern CLASS_IMPORT const BFTextFieldId DeathClaimDocExist;
   extern CLASS_IMPORT const BFDecimalFieldId AllocationPercent; 
   extern CLASS_IMPORT const BFTextFieldId GrantRequest; 
   extern CLASS_IMPORT const BFTextFieldId Tainted; 
   extern CLASS_IMPORT const BFDateFieldId TaintEndDate; 
   extern CLASS_IMPORT const BFTextFieldId CreateRec511;
   extern CLASS_IMPORT const BFDateFieldId Rec511CutOffDate;
   extern CLASS_IMPORT const BFTextFieldId RES2ParentLglList;
   extern CLASS_IMPORT const BFTextFieldId RES2DesInstList;
   extern CLASS_IMPORT const BFTextFieldId RES2PCGList;
   extern CLASS_IMPORT const BFTextFieldId LetterReq;
   extern CLASS_IMPORT const BFDateFieldId LetterDate;
   extern CLASS_IMPORT const BFTextFieldId CLBExists;
   extern CLASS_IMPORT const BFTextFieldId GrantExists;
   extern CLASS_IMPORT const BFTextFieldId TradeExists;
   extern CLASS_IMPORT const BFDecimalFieldId RESPPCGId;
   extern CLASS_IMPORT const BFTextFieldId PCGChange;
   extern CLASS_IMPORT const BFTextFieldId Rec400Sent;
   extern CLASS_IMPORT const BFTextFieldId PCGLinkBenef;
   extern CLASS_IMPORT const BFDateFieldId IdExpireDate;
   extern CLASS_IMPORT const BFTextFieldId FATCAFFI;
   extern CLASS_IMPORT const BFDecimalFieldId PercentOwner;
   extern CLASS_IMPORT const BFDecimalFieldId AssocEntityId;
   extern CLASS_IMPORT const BFTextFieldId CurrentSelectedEntityType;
   extern CLASS_IMPORT const BFDateFieldId StopDate;
   extern CLASS_IMPORT const BFTextFieldId RDSPRelntoBene;
   extern CLASS_IMPORT const BFTextFieldId RDSPConsent;
   extern CLASS_IMPORT const BFDateFieldId RDSPConsentDeff;
   extern CLASS_IMPORT const BFTextFieldId VerifyStat;
   extern CLASS_IMPORT const BFTextFieldId Active;
   extern CLASS_IMPORT const BFTextFieldId VerifyStatDetails;
}

namespace ENTSRCHLIT //entity search literals
{
   //this parameter should be set to Y if we are doing an entity search during adding a new entity to the system
   const I_CHAR * const ENTITY_BACKGROUNG_SEARCH = I_( "BackgroundSearch" );
   const I_CHAR * const SEARCH_CRITERIA_CODE = I_( "SearchCriteriaCode" );
   const I_CHAR * const SEARCH_USING_CODE  = I_( "SearchUsingCode" );
}

namespace AUDITTYPE
{
   extern CLASS_IMPORT I_CHAR * const ENTIDT;
   extern CLASS_IMPORT I_CHAR * const SHENTA;
   extern CLASS_IMPORT I_CHAR * const SHENTB;
   extern CLASS_IMPORT I_CHAR * const SHENTJ;
   extern CLASS_IMPORT I_CHAR * const ASDETL;
   extern CLASS_IMPORT I_CHAR * const ENTIDS;
   extern CLASS_IMPORT I_CHAR * const ENTITY_RISK;
}

namespace IDS
{
   extern CLASS_IMPORT const I_CHAR * const CIF;
   extern CLASS_IMPORT const I_CHAR * const ACCESS_ID;
   extern CLASS_IMPORT const I_CHAR * const DRIVERS_LICENSE;
   extern CLASS_IMPORT const I_CHAR * const PASSPORT;
   extern CLASS_IMPORT const I_CHAR * const NATIONAL_ID;
   extern CLASS_IMPORT const I_CHAR * const SIN;
   extern CLASS_IMPORT const I_CHAR * const BIC_CODE;
   extern CLASS_IMPORT const I_CHAR * const CREDIT_CARD;
   extern CLASS_IMPORT const I_CHAR * const BIRTH_CERTIFICATE;
   extern CLASS_IMPORT const I_CHAR * const CLEARING_PLATFORM; //MT535/MT536
   extern CLASS_IMPORT const I_CHAR * const OTHER;
   extern CLASS_IMPORT const I_CHAR * const CPFB_ACCNUM;
   extern CLASS_IMPORT const I_CHAR * const TAX_FILE_NUMBER;        
   extern CLASS_IMPORT const I_CHAR * const AUSTRALIAN_BUSINESS_NUMBER;  
}


//******************************************************************************
//              Public Methods
//******************************************************************************

EntityProcess::EntityProcess ( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _pAccountEntityXref( NULL ),
_rpChildGI(NULL)

{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   addContainer( IFASTBP_PROC::ENTITY_LIST, true, BF::NullContainerId, true, I_("Entity") );
   addContainer( IFASTBP_PROC::ENTITY_IDS_LIST, true, IFASTBP_PROC::ENTITY_LIST, true, I_("EntityIds") );
   addContainer( IFASTBP_PROC::RISK_LIST, true, IFASTBP_PROC::ENTITY_LIST, true, I_("RiskList") );

   addFieldDetails( ifds::AccountNum,         IFASTBP_PROC::ENTITY_LIST,              SUBCLASS_PROCESS );
   addFieldDetails( ifds::LastName,           IFASTBP_PROC::ENTITY_LIST,              SUBCLASS_PROCESS );
   addFieldDetails( ifds::FirstName,          IFASTBP_PROC::ENTITY_LIST,              SUBCLASS_PROCESS );
   addFieldDetails( ifds::Salutation,         IFASTBP_PROC::ENTITY_LIST,              SUBCLASS_PROCESS );
   addFieldDetails( ifds::BirthLastName,      IFASTBP_PROC::ENTITY_LIST,              SUBCLASS_PROCESS );
   addFieldDetails( ifds::BirthFirstName,     IFASTBP_PROC::ENTITY_LIST,              SUBCLASS_PROCESS );
   addFieldDetails( ifds::DofBirth,           IFASTBP_PROC::ENTITY_LIST,              SUBCLASS_PROCESS );
   addFieldDetails( ifds::BirthPlace,         IFASTBP_PROC::ENTITY_LIST,              SUBCLASS_PROCESS );
   addFieldDetails( ifds::CountryOfBirth,     IFASTBP_PROC::ENTITY_LIST,              SUBCLASS_PROCESS );
   addFieldDetails( ifds::Gender,             IFASTBP_PROC::ENTITY_LIST,              SUBCLASS_PROCESS );
   addFieldDetails( ifds::EmployeeClass,      IFASTBP_PROC::ENTITY_LIST,              SUBCLASS_PROCESS );
   addFieldDetails( ifds::SIN,                IFASTBP_PROC::ENTITY_LIST,              SUBCLASS_PROCESS );
   addFieldDetails( ifds::OccupationCode,     IFASTBP_PROC::ENTITY_LIST,              SUBCLASS_PROCESS );
   addFieldDetails( ifds::OccupationDesc,     IFASTBP_PROC::ENTITY_LIST,              SUBCLASS_PROCESS );
   addFieldDetails( ifds::OtherOccupation,    IFASTBP_PROC::ENTITY_LIST,              SUBCLASS_PROCESS );
   addFieldDetails( ifds::Nationality,        IFASTBP_PROC::ENTITY_LIST,              SUBCLASS_PROCESS );  
   addFieldDetails( ifds::Language,           IFASTBP_PROC::ENTITY_LIST,              SUBCLASS_PROCESS );  
   addFieldDetails( ifds::LanguageCode,       IFASTBP_PROC::ENTITY_LIST,              SUBCLASS_PROCESS );
   addFieldDetails( ifds::HomePhone,          IFASTBP_PROC::ENTITY_LIST,              SUBCLASS_PROCESS );
   addFieldDetails( ifds::BusinessPhone,      IFASTBP_PROC::ENTITY_LIST,              SUBCLASS_PROCESS );
   addFieldDetails( ifds::BusinessExt,        IFASTBP_PROC::ENTITY_LIST,              SUBCLASS_PROCESS );
   addFieldDetails( ifds::BusinessFax,        IFASTBP_PROC::ENTITY_LIST,              SUBCLASS_PROCESS );
   addFieldDetails( ifds::Telex,              IFASTBP_PROC::ENTITY_LIST,              SUBCLASS_PROCESS );
   addFieldDetails( ifds::Email,              IFASTBP_PROC::ENTITY_LIST,              SUBCLASS_PROCESS );
   addFieldDetails( ifds::ContactName,        IFASTBP_PROC::ENTITY_LIST,              SUBCLASS_PROCESS );
   addFieldDetails( ifds::DofDeath,           IFASTBP_PROC::ENTITY_LIST,              SUBCLASS_PROCESS );
   addFieldDetails( ifds::DofDeathNotice,     IFASTBP_PROC::ENTITY_LIST,              SUBCLASS_PROCESS );
   addFieldDetails( ifds::EffectiveDate,      IFASTBP_PROC::ENTITY_LIST,              SUBCLASS_PROCESS );
   addFieldDetails( ifds::HomeFax,            IFASTBP_PROC::ENTITY_LIST,              SUBCLASS_PROCESS );
   addFieldDetails( ifds::ModDate,            IFASTBP_PROC::ENTITY_LIST,              SUBCLASS_PROCESS );
   addFieldDetails( ifds::Username,           IFASTBP_PROC::ENTITY_LIST,              SUBCLASS_PROCESS );
   addFieldDetails( ifds::ModUser,            IFASTBP_PROC::ENTITY_LIST,              SUBCLASS_PROCESS );
   addFieldDetails( ifds::EffectiveDate2,     IFASTBP_PROC::ENTITY_LIST,              SUBCLASS_PROCESS );   
   addFieldDetails( ifds::TaxJurisDeff,       IFASTBP_PROC::ENTITY_LIST,              SUBCLASS_PROCESS );
   addFieldDetails( ifds::TaxJuris,           IFASTBP_PROC::ENTITY_LIST,              SUBCLASS_PROCESS );
   addFieldDetails( ifds::EUSDTaxOption,      IFASTBP_PROC::ENTITY_LIST,              SUBCLASS_PROCESS );
   //addFieldDetails( ifds::FATCAFFI,           IFASTBP_PROC::ENTITY_LIST,              SUBCLASS_PROCESS );
   addFieldDetails( ifds::UpdShrTaxJuris,     IFASTBP_PROC::ENTITY_LIST,              SUBCLASS_PROCESS );
   addFieldDetails( ifds::DeathSettlementDate,IFASTBP_PROC::ENTITY_LIST                                );
   addFieldDetails( ifds::CountryOfExposure,  IFASTBP_PROC::ENTITY_LIST,              SUBCLASS_PROCESS );

   addFieldDetails( ifds::HomePhoneArea,      IFASTBP_PROC::ENTITY_LIST,              SUBCLASS_PROCESS );
   addFieldDetails( ifds::BusinessPhoneArea,  IFASTBP_PROC::ENTITY_LIST,              SUBCLASS_PROCESS );
   addFieldDetails( ifds::HomeFaxArea,        IFASTBP_PROC::ENTITY_LIST,              SUBCLASS_PROCESS );
   addFieldDetails( ifds::BusFaxArea,         IFASTBP_PROC::ENTITY_LIST,              SUBCLASS_PROCESS );
   addFieldDetails( ifds::NAME_LENGTH,        IFASTBP_PROC::ENTITY_LIST,              SUBCLASS_PROCESS );
   addFieldDetails( ifds::Email2,             IFASTBP_PROC::ENTITY_LIST,              SUBCLASS_PROCESS );
   addFieldDetails( ifds::SecondPhoneNum,     IFASTBP_PROC::ENTITY_LIST,              SUBCLASS_PROCESS );
   addFieldDetails( ifds::SecondPhoneNumExt,  IFASTBP_PROC::ENTITY_LIST,              SUBCLASS_PROCESS );

   addFieldDetails( ifds::EntityType,         IFASTBP_PROC::ENTITY_LIST                                );
   addFieldDetails( ifds::AuthorizedToTrade,  IFASTBP_PROC::ENTITY_LIST                                );
   addFieldDetails( ifds::EntityId,           IFASTBP_PROC::ENTITY_LIST                                );
   addFieldDetails( ifds::EntityTypeDesc,     IFASTBP_PROC::ENTITY_LIST                                );
   addFieldDetails( ifds::BenPercentage,      IFASTBP_PROC::ENTITY_LIST                                );
   addFieldDetails( ifds::CountryName,        IFASTBP_PROC::ENTITY_LIST,              SUBCLASS_PROCESS );//dummy - for TaxJurisCode
   addFieldDetails( ifds::CountryCode,        IFASTBP_PROC::ENTITY_LIST,              SUBCLASS_PROCESS );//dummy - for TaxJurisCode (RESP)
   addFieldDetails( ifds::TaxJurisCode,       IFASTBP_PROC::ENTITY_LIST                                );
   addFieldDetails( ifds::LetterDate,         IFASTBP_PROC::ENTITY_LIST                                );
   addFieldDetails( ifds::LetterReq,          IFASTBP_PROC::ENTITY_LIST                                );

   addFieldDetails( ifds::EscrowFund,         IFASTBP_PROC::ENTITY_LIST                                );
   addFieldDetails( ifds::EscrowClass,        IFASTBP_PROC::ENTITY_LIST                                );
   addFieldDetails( ifds::FrFundNumber,       IFASTBP_PROC::ENTITY_LIST                                );
   addFieldDetails( ifds::HRDCRelateCode,     IFASTBP_PROC::ENTITY_LIST                                );

   addFieldDetails( ifds::AmtAssigned,        IFASTBP_PROC::ENTITY_LIST                                );
   addFieldDetails( ifds::AmountType,         IFASTBP_PROC::ENTITY_LIST                                );
   addFieldDetails( ifds::ReasonCode,         IFASTBP_PROC::ENTITY_LIST                                );
   addFieldDetails( ifds::RESPReasonCode,     IFASTBP_PROC::ENTITY_LIST                                );

   addFieldDetails( ifds::EscrowStopDate,     IFASTBP_PROC::ENTITY_LIST                                );
   addFieldDetails( ifds::EscrowDeff,         IFASTBP_PROC::ENTITY_LIST                                );
   //IN2780013 - SOC Loan Number and Loan Type
   addFieldDetails( ifds::LoanType,     IFASTBP_PROC::ENTITY_LIST                                );
   addFieldDetails( ifds::LoanNumber,         IFASTBP_PROC::ENTITY_LIST                                );

   addFieldDetails( ifds::Irrevocable,        IFASTBP_PROC::ENTITY_LIST                                );
   addFieldDetails( ifds::ProcessDate,        IFASTBP_PROC::ENTITY_LIST,              SUBCLASS_PROCESS );
   addFieldDetails( ifds::RelateCode,         IFASTBP_PROC::ENTITY_LIST                                );
   addFieldDetails( ifds::SeqNumber,          IFASTBP_PROC::ENTITY_LIST                                );
   addFieldDetails( ifds::DepositionCode,     IFASTBP_PROC::ENTITY_LIST                                );
   addFieldDetails( ifds::JointType,          IFASTBP_PROC::ENTITY_LIST                                );
   addFieldDetails( ifds::GoodBad,            IFASTBP_PROC::ENTITY_LIST                                );

   addFieldDetails( ifds::BeneficiaryTitleDisplay,IFASTBP_PROC::ENTITY_LIST                            );
   addFieldDetails( ifds::OwnerSpouseName,    IFASTBP_PROC::ENTITY_LIST                                );
   addFieldDetails( ifds::SpouseEntityID,     IFASTBP_PROC::ENTITY_LIST,              SUBCLASS_PROCESS );

   addFieldDetails( ifds::IdType,             IFASTBP_PROC::ENTITY_IDS_LIST                            );
   addFieldDetails( ifds::IdValue,            IFASTBP_PROC::ENTITY_IDS_LIST                            );
   addFieldDetails( ifds::IdDate,             IFASTBP_PROC::ENTITY_IDS_LIST                            );
   addFieldDetails( ifds::IdTypeDesc,         IFASTBP_PROC::ENTITY_IDS_LIST                            );
   addFieldDetails( ifds::IdStatus,           IFASTBP_PROC::ENTITY_IDS_LIST                            );
   addFieldDetails( ifds::IdExpireDate,       IFASTBP_PROC::ENTITY_IDS_LIST                            );
   addFieldDetails( ifds::CountryOfIssue,     IFASTBP_PROC::ENTITY_IDS_LIST                            );
   addFieldDetails( ifds::DuplicateSINcheck,  IFASTBP_PROC::ENTITY_IDS_LIST                            );
   addFieldDetails( ifds::VerifyStat,         IFASTBP_PROC::ENTITY_IDS_LIST                            );

   addFieldDetails( ENTPROC::ACCOUNT_NUMBER_FIELD,         BF::NullContainerId,       SUBCLASS_PROCESS );
   addFieldDetails( ENTPROC::PROC_CREATING_ACCOUNT,        BF::NullContainerId,       SUBCLASS_PROCESS );
   addFieldDetails( ENTPROC::PROC_CREATING_SHAREHOLDER,    BF::NullContainerId,       SUBCLASS_PROCESS );
   addFieldDetails( ENTPROC::SELECTION_KEY,                BF::NullContainerId,       SUBCLASS_PROCESS );
   addFieldDetails( ENTPROC::HAS_NON_DUMMY_RECORDS,        BF::NullContainerId,       SUBCLASS_PROCESS );
   addFieldDetails( ENTPROC::ACCOUNT_TYPE_FIELD,           BF::NullContainerId,       SUBCLASS_PROCESS );
   addFieldDetails( ENTPROC::PERCENT_AVAILABLE,            BF::NullContainerId,       SUBCLASS_PROCESS );
//   addFieldDetails( ENTPROC::DO_ENTITY_RESET,              BF::NullContainerId,       SUBCLASS_PROCESS );
   addFieldDetails( ENTPROC::AGE_YEARS,                    BF::NullContainerId,       SUBCLASS_PROCESS );
   addFieldDetails( ENTPROC::AGE_MONTHS,                   BF::NullContainerId,       SUBCLASS_PROCESS );
   addFieldDetails( ENTPROC::SHR_NUM,                      BF::NullContainerId,       SUBCLASS_PROCESS );
   addFieldDetails( ENTPROC::NEW_ITEM,                     BF::NullContainerId,       SUBCLASS_PROCESS );
   addFieldDetails( ENTPROC::NEW_ACCOUNT,                  BF::NullContainerId,       SUBCLASS_PROCESS );
   addFieldDetails( ENTPROC::ORG_KEY,                      BF::NullContainerId,       SUBCLASS_PROCESS );
   addFieldDetails( ENTPROC::DEST_KEY,                     BF::NullContainerId,       SUBCLASS_PROCESS );
   addFieldDetails( ENTPROC::SALUTATION_EDIT,              BF::NullContainerId,       SUBCLASS_PROCESS );
   addFieldDetails( ENTPROC::ACCOUNT_TYPE,                 BF::NullContainerId,       SUBCLASS_PROCESS );
   addFieldDetails( ENTPROC::UPDATE_SHAREHOLDER,           BF::NullContainerId,       SUBCLASS_PROCESS );
   addFieldDetails( ENTPROC::IS_RESPBENE_DELETED,          BF::NullContainerId,       SUBCLASS_PROCESS );
   addFieldDetails( ENTPROC::LETTER_REQUIRED,              BF::NullContainerId,       SUBCLASS_PROCESS );
   addFieldDetails( ENTPROC::ACCOUNT_TAX_TYPE,	           BF::NullContainerId,       SUBCLASS_PROCESS );


   addFieldDetails( ifds::EUSDParticip,                    BF::NullContainerId,       SUBCLASS_PROCESS );
   addFieldDetails( ifds::EntityIdentityRid,   IFASTBP_PROC::ENTITY_LIST,             SUBCLASS_PROCESS );
   addFieldDetails( ifds::AcctEntityRid,       IFASTBP_PROC::ENTITY_LIST                               );
   addFieldDetails( ifds::AcctEntityJointRid,  IFASTBP_PROC::ENTITY_LIST                               );
   addFieldDetails( ifds::AcctEntityBenefRid,  IFASTBP_PROC::ENTITY_LIST                               );
   addFieldDetails( ifds::AssignDetlRid,       IFASTBP_PROC::ENTITY_LIST                               );
   addFieldDetails( ifds::RiskLevel,           IFASTBP_PROC::ENTITY_LIST,             SUBCLASS_PROCESS );

   //addFieldDetails( ifds::AllocationPercent,   IFASTBP_PROC::ENTITY_LIST                               );
   addFieldDetails( ifds::GrantRequest,        IFASTBP_PROC::ENTITY_LIST                               );
   addFieldDetails( ifds::Tainted,             IFASTBP_PROC::ENTITY_LIST                               );
   addFieldDetails( ifds::TaintEndDate,        IFASTBP_PROC::ENTITY_LIST                               );
   addFieldDetails( ifds::CreateRec511,        IFASTBP_PROC::ENTITY_LIST                               );
   addFieldDetails( ifds::Rec511CutOffDate,    IFASTBP_PROC::ENTITY_LIST                               );
   addFieldDetails( ifds::RESPParentSeq,       IFASTBP_PROC::ENTITY_LIST                               );
   addFieldDetails( ifds::RESPDesInstSeq,      IFASTBP_PROC::ENTITY_LIST                               );

   addFieldDetails( ifds::RES2ParentLglList,   IFASTBP_PROC::ENTITY_LIST                               );
   addFieldDetails( ifds::RES2DesInstList,     IFASTBP_PROC::ENTITY_LIST                               );
   addFieldDetails( ifds::RES2PCGList,         IFASTBP_PROC::ENTITY_LIST                               );
   //addFieldDetails( ifds::LetterReq,           IFASTBP_PROC::ENTITY_LIST                               );
   //addFieldDetails( ifds::LetterDate,          IFASTBP_PROC::ENTITY_LIST                               );
   addFieldDetails( ifds::CLBExists,           IFASTBP_PROC::ENTITY_LIST                               );
   addFieldDetails( ifds::GrantExists,         IFASTBP_PROC::ENTITY_LIST                               );
   addFieldDetails( ifds::TradeExists,         IFASTBP_PROC::ENTITY_LIST                               );
   addFieldDetails( ifds::PCGChange,           IFASTBP_PROC::ENTITY_LIST                               );
   addFieldDetails( ifds::Rec400Sent,          IFASTBP_PROC::ENTITY_LIST                               );
   addFieldDetails( ifds::PCGLinkBenef,        IFASTBP_PROC::ENTITY_LIST,             SUBCLASS_PROCESS );
   addFieldDetails( ifds::RefCode,             IFASTBP_PROC::ENTITY_LIST                               );
   addFieldDetails( ifds::RefType,             IFASTBP_PROC::ENTITY_LIST                               );
   addFieldDetails( ifds::AssocEntityId,       IFASTBP_PROC::ENTITY_LIST                               );
   addFieldDetails( ifds::PercentOwner,        IFASTBP_PROC::ENTITY_LIST                               );
   addFieldDetails( ifds::EntityAssociation,   IFASTBP_PROC::ENTITY_LIST                               );
   addFieldDetails( ifds::RDSPRelntoBene,	   IFASTBP_PROC::ENTITY_LIST                               );
   addFieldDetails( ifds::RDSPConsent,		   IFASTBP_PROC::ENTITY_LIST                               );
   addFieldDetails( ifds::RDSPConsentDeff,	   IFASTBP_PROC::ENTITY_LIST                               );
   addFieldDetails( ifds::VerifyStat,          IFASTBP_PROC::ENTITY_LIST                               );
   addFieldDetails( ifds::Active,              IFASTBP_PROC::ENTITY_LIST                              );
   addFieldDetails( ifds::VerifyStatDetails,   IFASTBP_PROC::ENTITY_LIST, SUBCLASS_PROCESS             );

   //Risk List
   addFieldDetails( ifds::RiskLevel,           IFASTBP_PROC::RISK_LIST                               );
   addFieldDetails( ifds::CountryOfExposure,   IFASTBP_PROC::RISK_LIST                               );
   addFieldDetails( ifds::EffectiveDate,       IFASTBP_PROC::RISK_LIST                               );
   addFieldDetails( ifds::StopDate,            IFASTBP_PROC::RISK_LIST                               );
   addFieldDetails( ENTPROC::RISK_DEFF_DATE_APPL, IFASTBP_PROC::RISK_LIST,           SUBCLASS_PROCESS);

   // AcctMainenance LastNameFormat = Double
   addFieldDetails( ifds::PaternalLastName,           IFASTBP_PROC::ENTITY_LIST,              SUBCLASS_PROCESS );
   addFieldDetails( ifds::MaternalLastName,          IFASTBP_PROC::ENTITY_LIST,              SUBCLASS_PROCESS );
}

//******************************************************************************
EntityProcess::~EntityProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY EntityProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );
   try
   {
      DSTCWorkSession *pDSTCWorkSession = 
         dynamic_cast<DSTCWorkSession*>(getBFWorkSession());

      if (pDSTCWorkSession->getAccountEntityXref (BF::HOST, _pAccountEntityXref) <= WARNING)
      {
         SEVERITY sevRtn = SEVERE_ERROR;
         DString dstrCommandReturn;

         getParameter (NASULIT::CREATING_SHAREHOLDER, _dstrCreatingShareholder);
         getParameter (NASULIT::CREATING_ACCOUNT, _dstrCreatingAccount);
         getParameter (NASULIT::COMMANDRETURN, dstrCommandReturn);
         getParameter (ENTPROC::ACCOUNT_NUM, _accNum);
         getParameter (ENTPROC::MODEL_ACCOUNT_NUM, _modelAcctNum);
         flg_copy_entity = false;
         Entity::bUsedByEntityAlone =  false;
         if (_accNum != NULL_STRING)
         {
            // COMMANDRETURN is Null except during NASU.  We do not want to clone the AcctEntiytXrefFromModel when a cancel has
            // occurred during NASU.  This fixes duplicate entries in the entity list on a cancel command from the next screen of
            // NASU (COA/Address/As Pension Plan).
            if (dstrCommandReturn != NASULIT::COMMANDCANCEL && 
               _modelAcctNum  != NULL_STRING && 
               _dstrCreatingShareholder == NO && _dstrCreatingAccount == YES)
            {
               _pAccountEntityXref->cloneAcctEntityXrefFromModel (_modelAcctNum, _accNum, getDataGroupId());
            }
            _accNum.stripLeading ('0');
            _pAccountEntityXref->setCurrentAccounNum (_accNum); 
            flg_no_account = false;
         }
         else
         {
            flg_no_account = true;
         }
         getParameter (I_( "Key" ), strKey);
         getParameter (ENTPROC::ENTITY_ID, _entityId);
         _entityId.stripLeading ('0');

         if (_dstrCreatingAccount != YES)
         {
            if (_accNum != NULL_STRING)
            {
               sevRtn = _pAccountEntityXref->PopulateEntitiesList (getDataGroupId(), _accNum);

            }
            else
            {
               sevRtn = _pAccountEntityXref->PopulateWhereUsed (_entityId);
            }
         }
         if (sevRtn <= WARNING && _pAccountEntityXref)
         {
            setContainer (IFASTBP_PROC::ENTITY_LIST, _pAccountEntityXref);

            BFObjIter bfIter (*_pAccountEntityXref, getDataGroupId());
            for( ; !bfIter.end(); ++bfIter )
            {
               BFAbstractCBO * pAcctXRef =  bfIter.getObject();

               if (pAcctXRef)
               {
                  DString entityId;
                  
                  pAcctXRef->getField (ifds::EntityId, entityId, getDataGroupId());

                  if (!entityId.empty())
                  {
                     Entity *pEntity = NULL;
                     dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getEntity (getDataGroupId(), entityId, pEntity);
                     if (pEntity)
                     {
                         pEntity->getField (ifds::DofDeath, _originalDeathDate, getDataGroupId());
                         pEntity->getField (ifds::DofDeathNotice, _originalDeathOfNotifDate, getDataGroupId());
                         pEntity->initEUSDRelatedFields (getDataGroupId());
                     }
                  }
               }
            }
         }
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
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************

bool EntityProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_ENTITY_MAINTENANCE );
}

//******************************************************************************

bool EntityProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );

   bool bRtn = false;
   try
   {
      DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

      if( ( getDataGroupId() != BF::HOST ) && ( dstcWorkSession->isUpdatedForDataGroup( getDataGroupId() ) ) )
      {
         setParameter( ENTPROC::ACCOUNT_NUM, _accNum );
         _rpChildGI->modelessSetFocus( rpGICaller );
         ADDCONDITIONFROMFILE( CND::BP_ERR_NOT_ALLOW_SETFOCUS );
         return(false);
      }

      getParameter( ENTPROC::ACCOUNT_NUM, _accNum );
      if( _accNum != NULL_STRING )
      {
         _accNum.stripLeading( '0' );
         //_accNum = _accNum.padLeft( 20, '0' );
         _pAccountEntityXref->setCurrentAccounNum( _accNum ); 
         flg_no_account = false;
      }
      else
         flg_no_account = true;
      getParameter( I_( "Key" ), strKey );
      getParameter( ENTPROC::ENTITY_ID, _entityId );
      _entityId.stripLeading( '0' );

      if( !( bRtn = _rpChildGI->refresh( this, NULL ) ) )
         return(bRtn);// false
      bRtn = _rpChildGI->modelessSetFocus( rpGICaller );
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
   return(bRtn);
}

//******************************************************************************

E_COMMANDRETURN EntityProcess::doProcess()
{  
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      setParameter( ENTPROC::ACCOUNT_NUM, _accNum );
      setParameter( I_( "Key" ), strKey );
      setParameter( ENTPROC::ENTITY_ID, _entityId );
      setParameter( I_( "ExistAccount" ), flg_no_account ? NO : YES );
	  setParameter(NASULIT::CREATING_SHAREHOLDER, _dstrCreatingShareholder);
	  setParameter(NASULIT::CREATING_ACCOUNT, _dstrCreatingAccount);
	  setParameter(ENTPROC::MODEL_ACCOUNT_NUM, _modelAcctNum);

      if( !isXMLAPIContext() )
         rtn = invokeCommand( this, CMD_GUI_ENTITY_MAINTENANCE, getProcessType(),
                              isModal(), &_rpChildGI );
      else
         rtn = CMD_MODELESS_INPROCESS;
   }
   catch( ConditionException &ce )
   {
      assert( 0 );
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return(rtn);
}

//******************************************************************************

const DString& EntityProcess::getFirstListItemKey( const GenericInterface *rpGICaller, const BFContainerId& idList )
{  
   TRACE_METHOD( CLASSNAME, GETFIRSTLISTITEMKEY );

   try
   {
      if( idList == IFASTBP_PROC::ENTITY_LIST )
      {
         _pAccountEntityXref->SetChildrenSpousalNameSubSet( getDataGroupId() );

         BFObjIter iterAccountEntityXrefOut( *_pAccountEntityXref, getDataGroupId(), true, BFObjIter::ITERTYPE::NON_DELETED, false, true );
         DString searchKey;
         if( _accNum != NULL_STRING )
         {
            AccountEntityXref::buildPartialKeyForAccount( searchKey, _accNum );
            if( !iterAccountEntityXrefOut.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey ) )
               return(EMPTY_STRING);

            DString key = iterAccountEntityXrefOut.getStringKey();
            AbstractProcess::setCurrentListItem( rpGICaller, idList, key );

            DString strEntityType;
            iterAccountEntityXrefOut.getObject()->getField( ifds::EntityType,
               strEntityType, getDataGroupId(), false );
            strEntityType.strip().upperCase();

            if ( strEntityType == PARENT_GUARDIAN_ENTITY_TYPE ||
                 strEntityType == RESP_DESIGNATED_INSTIT_ENTITY_TYPE ||
                 strEntityType == RESP_PCG_INDIV_ENTITY_TYPE || 
                 strEntityType == RESP_PCG_INST_ENTITY_TYPE )
            {
               _pAccountEntityXref->setRESPSelectableFieldSubSet(strEntityType, NULL_STRING, getDataGroupId());
            }

            return(iterAccountEntityXrefOut.getStringKey());
         }
         else if( _entityId != NULL_STRING )
         {
            AccountEntityXref::buildPartialKeyForEntityId( searchKey, _entityId );
            iterAccountEntityXrefOut.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey );
            DString key = iterAccountEntityXrefOut.getStringKey();
            AbstractProcess::setCurrentListItem( rpGICaller, idList, key );
            return(iterAccountEntityXrefOut.getStringKey());
         }
      }
   }
   catch( ConditionException & )
   {
      throw;
   }
   catch( ... )
   {  // Just to catch at earliest point
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETFIRSTLISTITEMKEY,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return(AbstractProcess::getFirstListItemKey( rpGICaller, idList ));
}

//******************************************************************************

const DString& EntityProcess::getNextListItemKey( const GenericInterface *rpGICaller, const BFContainerId& idList )
{  
   TRACE_METHOD( CLASSNAME, GETNEXTLISTITEMKEY );

   try
   {
      if( idList == IFASTBP_PROC::ENTITY_LIST )
      {
         BFObjIter iterAccountEntityXrefOut( *_pAccountEntityXref, getDataGroupId(), true, BFObjIter::ITERTYPE::NON_DELETED, false, true );
         DString searchKey;
         DString key;
         bool flg_new_element_in_list = false;
         if( _accNum != NULL_STRING )
         {
            DString entityListCurrentItemKey = getCurrentListItemKey( rpGICaller, idList );

            AccountEntityXref::buildPartialKeyForAccount( searchKey, _accNum );
            iterAccountEntityXrefOut.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey );
            iterAccountEntityXrefOut.positionByKey( entityListCurrentItemKey );
            if( !++iterAccountEntityXrefOut )
               return(EMPTY_STRING);

            key = iterAccountEntityXrefOut.getStringKey();
            AbstractProcess::setCurrentListItem( rpGICaller, idList, key );

            DString strEntityType;
            iterAccountEntityXrefOut.getObject()->getField( ifds::EntityType,
               strEntityType, getDataGroupId(), false );
            strEntityType.strip().upperCase();

            if ( strEntityType == PARENT_GUARDIAN_ENTITY_TYPE ||
                 strEntityType == RESP_DESIGNATED_INSTIT_ENTITY_TYPE ||
                 strEntityType == RESP_PCG_INDIV_ENTITY_TYPE || 
                 strEntityType == RESP_PCG_INST_ENTITY_TYPE )
            {
               _pAccountEntityXref->setRESPSelectableFieldSubSet(strEntityType,NULL_STRING,getDataGroupId());
            }

            return(iterAccountEntityXrefOut.getStringKey());
         }
         else if( _entityId != NULL_STRING )
         {
            //this is happening only when we search for an Entity
            AccountEntityXref::buildPartialKeyForEntityId( searchKey, _entityId );
            if( iterAccountEntityXrefOut.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey ) )
               while( ++iterAccountEntityXrefOut ); //go to the end
            return(EMPTY_STRING);
         }
      }
   }
   catch( ConditionException & )
   {
      throw;
   }
   catch( ... )
   {  // Just to catch at earliest point
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETNEXTLISTITEMKEY,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   return(AbstractProcess::getNextListItemKey( rpGICaller, idList ));
}

//******************************************************************************

const DString& EntityProcess::getKeyForNewListItem( const GenericInterface *rpGICaller, const BFContainerId& idList )
{
   assert (!flg_no_account);
   
   const BFDataGroupId& idDataGroup = getDataGroupId();
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   if (IFASTBP_PROC::ENTITY_LIST == idList)
   {
      DString accountNum (_accNum), 
         seqNumber, 
         entityType, 
         entityId,
         shrNum;


      Entity *pEntity (NULL);
      if (flg_copy_entity)
      {
         const_cast<EntityProcess *>(this)->getField (rpGICaller, IFASTBP_PROC::ENTITY_LIST, ifds::EntityType, entityType, false);
         const_cast<EntityProcess *>(this)->getField (rpGICaller, IFASTBP_PROC::ENTITY_LIST, ifds::EntityId, entityId, false);
         seqNumber = NULL_STRING;
      }
      else
      {
         dstcWorkSession->getNewEntity (idDataGroup, pEntity); //create a new entity
         if (pEntity)
         {
            MFAccount* pMFAccount (NULL);

            pEntity->getEntityId (entityId);            
            dstcWorkSession->getMFAccount (idDataGroup, _accNum, pMFAccount);
            if (pMFAccount)
            {
               pMFAccount->getField (ifds::ShrNum, shrNum, idDataGroup, false);
            }
            pEntity->saveShareNum (shrNum);
         }
         if (isXMLAPIContext())
         {
            setGlobal (WORK_GLOBAL, ifds::LastActiveEntityId, entityId);
            getParent()->setParameter (ENTPROC::ENTITY_ID, entityId); 
         }
      }
      AccountEntityXrefObject* pAccountEntityXrefObject;

      accountNum.stripLeading( '0' );
      DString dstrCount = _pAccountEntityXref->getNextCount();
      _pAccountEntityXref->LinkEntity( accountNum, 
                                       entityType, 
                                       seqNumber, 
                                       entityId, 
                                       idDataGroup, 
                                       pAccountEntityXrefObject, 
                                       flg_copy_entity);
      assert (pAccountEntityXrefObject);
      pAccountEntityXrefObject->setObjectNew();
      const DString& newKey = *(pAccountEntityXrefObject->getInitialStrKey());

      if (newKey != NULL_STRING)
      {
         setContainer( IFASTBP_PROC::ENTITY_LIST, NULL );
         setContainer( IFASTBP_PROC::ENTITY_LIST, _pAccountEntityXref );
         setCurrentListItem( rpGICaller, IFASTBP_PROC::ENTITY_LIST, newKey );
         selectionKey = newKey;
         return newKey;
      }
      else
         return EMPTY_STRING;
   }
   else
   {
      return AbstractProcess::getKeyForNewListItem (rpGICaller, idList);
   }
}

//******************************************************************************
void EntityProcess::doGetField( const GenericInterface *rpGICaller, 
                                const BFContainerId& idContainer,
                                const BFFieldId& idField, 
                                const BFDataGroupId& idDataGroup, 
                                DString &strValueOut, 
                                bool bFormatted) const
{
   if (IFASTBP_PROC::ENTITY_LIST == idContainer)
   {
      EntityProcess *pEntityProcess = const_cast<EntityProcess *>(this);

      if (idField  ==  ifds::EffectiveDate2)
      {
         BFAbstractCBO *rpPtr = pEntityProcess->getCBOItem (IFASTBP_PROC::ENTITY_LIST, idDataGroup);
         if (rpPtr)
         {
            rpPtr->getField (ifds::EffectiveDate,strValueOut,idDataGroup,bFormatted);
         }
      }
      else if (idField  ==  ifds::CountryName ||
               idField  ==  ifds::CountryCode)
      {
         pEntityProcess->getField (rpGICaller, IFASTBP_PROC::ENTITY_LIST, ifds::TaxJurisCode, strValueOut, bFormatted );
      }
      else if (idField == ifds::PCGLinkBenef)
      {
         DString strEntityType, strEntityId;
         pEntityProcess->getField (rpGICaller, IFASTBP_PROC::ENTITY_LIST, ifds::EntityType, strEntityType, false );
         pEntityProcess->getField (rpGICaller, IFASTBP_PROC::ENTITY_LIST, ifds::EntityId, strEntityId, false );
         strEntityType.strip().upperCase();

         if ( strEntityType == RESP_PCG_INDIV_ENTITY_TYPE || 
              strEntityType == RESP_PCG_INST_ENTITY_TYPE)
         {
            BFAbstractCBO *rpPtr = 
               ( const_cast < EntityProcess *> ( this ) )->getCBOItem( IFASTBP_PROC::ENTITY_LIST, idDataGroup );
            AccountEntityXrefObject *pAcctEntityXrefObject = 
               dynamic_cast < AccountEntityXrefObject* > ( rpPtr );

            if ( pAcctEntityXrefObject )
            {
               bool bResult = 
                  pAcctEntityXrefObject->isLinkedToRESPBenef(strEntityId, idDataGroup);
                  
               if ( bResult )
               {
                  strValueOut = I_("Y");
               }
               else
               {
                  strValueOut = I_("N");
               }
            }
            else
            {
               strValueOut = I_("N");
            }
         }
      }
      else
      {
         DString entityListCurrentItemKey = pEntityProcess->getCurrentListItemKey (rpGICaller, idContainer); 
         DString entityId,
            entityTag;
         if (!AccountEntityXref::getValueForTag (entityListCurrentItemKey, ENTPROC::ENTITY_ID, entityId))
            entityId = entityListCurrentItemKey;

         Entity *pEntity (NULL);
         dynamic_cast<DSTCWorkSession *> (getBFWorkSession())->getEntity (idDataGroup, entityId, pEntity);
         pEntity->getField (idField, strValueOut, idDataGroup, bFormatted);

      }
   }
   else if (BF::NullContainerId == idContainer)
   {
      if (idField == ENTPROC::ACCOUNT_NUMBER_FIELD)
      {
         strValueOut = _accNum;
      }
      else if (idField == ENTPROC::PROC_CREATING_ACCOUNT)
      {
         strValueOut = _dstrCreatingAccount;
      }
      else if (idField == ENTPROC::PROC_CREATING_SHAREHOLDER)
      {
         strValueOut = _dstrCreatingShareholder;
      }
      else if (idField == ENTPROC::SELECTION_KEY)
      {
         strValueOut = selectionKey;
      }
      else if (idField == ENTPROC::HAS_NON_DUMMY_RECORDS)
      {
         if( _pAccountEntityXref->hasNonDummyEntries (getDataGroupId()))
         {
            strValueOut = YES;
         }
      }
      else if (idField == ENTPROC::ACCOUNT_TYPE_FIELD)
      {
         DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
         MFAccount *pMFAccount;
         BFAbstractCBO *rpPtr = ( const_cast < EntityProcess *> ( this ) )->getCBOItem( IFASTBP_PROC::ENTITY_LIST, idDataGroup );
         DString account;
         rpPtr->getField( ifds::AccountNum, account, idDataGroup, true );
         account.stripLeading( '0' );
         if (!account.empty())
         {
            dstcWorkSession->getMFAccount( idDataGroup, account, pMFAccount );
            pMFAccount->getField( ifds::AcctType, strValueOut, idDataGroup, bFormatted );
         }
      }
      else if (idField == ENTPROC::PERCENT_AVAILABLE)
      {
         DString str;
         ( const_cast < EntityProcess *> ( this ) )->getField( rpGICaller, IFASTBP_PROC::ENTITY_LIST, ifds::EntityType, str, false );
         if( str == ENTITY_TYPE_PRIMARY_BENEF || str == ENTITY_TYPE_SECONDARY_BENEF || str == SUCCESSOR )
            _pAccountEntityXref->getAvailablePercentForBenef( str, strValueOut, getDataGroupId() );
      }
      else if (idField == ENTPROC::NEW_ACCOUNT)
      {
         DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
         MFAccount *pMFAccount = NULL;
         BFAbstractCBO *rpPtr = ( const_cast < EntityProcess *> ( this ) )->getCBOItem( IFASTBP_PROC::ENTITY_LIST, idDataGroup );
         DString account;
         rpPtr->getField( ifds::AccountNum, account, idDataGroup, true );
         account.stripLeading( '0' );
         dstcWorkSession->getMFAccount( idDataGroup, account, pMFAccount );
         if( pMFAccount->isNew() )
            strValueOut = YES;
         else
            strValueOut = NO;

      }
      else if (idField == ENTPROC::AGE_YEARS)
      {
         DString entityId;
         BFAbstractCBO *rpPtr = ( const_cast < EntityProcess *> ( this ) )->getCBOItem( IFASTBP_PROC::ENTITY_LIST, idDataGroup );
         rpPtr->getField( ifds::EntityId, entityId, idDataGroup );
         entityId.stripLeading( '0' );

         if( entityId != NULL_STRING )
         {
            DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
            Entity *pEntity;
            DString DateOfBirth, CurrentDate, months;
            dstcWorkSession->getEntity( idDataGroup, entityId, pEntity );
            pEntity->getField( ifds::DofBirth, DateOfBirth, idDataGroup );
            dstcWorkSession->getDateInHostFormat( CurrentDate, DSTCWorkSession::CURRENT_SYSTEM_DAY, idDataGroup );
            if( DSTCommonFunctions::BuildAge( DateOfBirth, CurrentDate, strValueOut, months ) )
               strValueOut = I_( "" );
         }
      }
      else if (idField == ENTPROC::AGE_MONTHS)
      {
         DString entityId;
         BFAbstractCBO *rpPtr = ( const_cast < EntityProcess *> ( this ) )->getCBOItem( IFASTBP_PROC::ENTITY_LIST, idDataGroup );
         rpPtr->getField( ifds::EntityId, entityId, idDataGroup );
         entityId.stripLeading( '0' );

         if (entityId != NULL_STRING)
         {
            DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
            Entity *pEntity;
            DString DateOfBirth, CurrentDate, years;
            dstcWorkSession->getEntity( idDataGroup, entityId, pEntity );
            pEntity->getField( ifds::DofBirth, DateOfBirth, idDataGroup );
            dstcWorkSession->getDateInHostFormat( CurrentDate, DSTCWorkSession::CURRENT_SYSTEM_DAY, idDataGroup );
            if( DSTCommonFunctions::BuildAge( DateOfBirth, CurrentDate, years, strValueOut ) )
               strValueOut = I_( "" );
         }
      }
      else if (idField == ENTPROC::SHR_NUM)
      {
         DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
         MFAccount *pMFAccount;
         BFAbstractCBO *rpPtr = ( const_cast < EntityProcess *> ( this ) )->getCBOItem( IFASTBP_PROC::ENTITY_LIST, idDataGroup );
         DString account;
         rpPtr->getField( ifds::AccountNum, account, idDataGroup, true );
         account.stripLeading( '0' );
         dstcWorkSession->getMFAccount( idDataGroup, account, pMFAccount );
         pMFAccount->getField( ifds::ShrNum, strValueOut, idDataGroup, bFormatted );

      }
      else if (idField == ENTPROC::NEW_ITEM)
      {
         BFAbstractCBO *rpPtr = ( const_cast < EntityProcess *> ( this ) )->getCBOItem( IFASTBP_PROC::ENTITY_LIST, idDataGroup );
         if( rpPtr->isNew() )  strValueOut = YES;
         else  strValueOut = NO;
      }
      else if (idField == ENTPROC::SALUTATION_EDIT)
      {
         // Return Yes for Salutation Edit is used or NO for Combo box.
         DString dstrValue;
         DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
         dstcWorkSession->getMgmtCoOptions()->getField( ifds::SalutationFormat, dstrValue, idDataGroup, false);
         dstrValue.upperCase().stripAll();
         strValueOut = ( dstrValue.substr( 0, 1 ) == I_("Y") ) ? I_("Y") : I_("N");
      }
      else if (idField == ENTPROC::ACCOUNT_TYPE)
      {
         DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
         MFAccount *pMFAccount;
         BFAbstractCBO *rpPtr = ( const_cast < EntityProcess *> ( this ) )->getCBOItem( IFASTBP_PROC::ENTITY_LIST, idDataGroup );
         DString account;
         rpPtr->getField( ifds::AccountNum, account, idDataGroup, true );
         account.stripLeading( '0' );
         dstcWorkSession->getMFAccount( idDataGroup, account, pMFAccount );
         pMFAccount->getField( ifds::AcctType, strValueOut, idDataGroup, bFormatted );
      }
      else if (idField ==  ifds::EUSDParticip)
      {
         DSTCWorkSession* pWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

         pWorkSession->getOption2( ifds::EUSDParticip, strValueOut, idDataGroup, false);
      }
      else if (idField ==  ENTPROC::UPDATE_SHAREHOLDER)
      {
         DString entityListCurrentItemKey = (const_cast < EntityProcess *> ( this ))->getCurrentListItemKey( rpGICaller, IFASTBP_PROC::ENTITY_LIST ); 
         DString entityId;
         DString entityTag;
         if( !AccountEntityXref::getValueForTag( entityListCurrentItemKey, ENTPROC::ENTITY_ID, entityId ) )
            entityId = entityListCurrentItemKey;

         Entity *pEntity = NULL;
         dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getEntity( idDataGroup, entityId, pEntity );
         if (pEntity)
         {
            strValueOut = pEntity->shouldUpdateShareholder(idDataGroup)? YES:NO;            
         }
      }
      else if (idField == ENTPROC::LETTER_REQUIRED)
      {
         if (_pAccountEntityXref)
         {
            BFObjIter iter (*_pAccountEntityXref, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
            
            while (!iter.end())
            {
               DString entityType;
               AccountEntityXrefObject* pXrefObj = dynamic_cast<AccountEntityXrefObject*> (iter.getObject());
               pXrefObj->getField (ifds::EntityType, entityType, idDataGroup);
               if (entityType == RESP_BENEFICIARY)
               {
                  pXrefObj->getField (ifds::LetterReq, strValueOut, idDataGroup, false);
                  break;
               }
               ++iter;
            }
         }
      }
      else if (idField == ENTPROC::IS_RESPBENE_DELETED)   
      {
         strValueOut = I_("N");
         if (_pAccountEntityXref && !_accNum.empty())
         {
            strValueOut = _pAccountEntityXref->isRESPBeneficiaryDeleted (_accNum, idDataGroup) ? I_("Y") : I_("N");
         }
      }
	  else if (idField == ENTPROC::ACCOUNT_TAX_TYPE)
      {
         DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
         MFAccount *pMFAccount;
         BFAbstractCBO *rpPtr = ( const_cast < EntityProcess *> ( this ) )->getCBOItem( IFASTBP_PROC::ENTITY_LIST, idDataGroup );
         DString account;
         rpPtr->getField( ifds::AccountNum, account, idDataGroup, true );
         account.stripLeading( '0' );
         if (!account.empty())
         {
            dstcWorkSession->getMFAccount( idDataGroup, account, pMFAccount );
            pMFAccount->getField( ifds::TaxType, strValueOut, idDataGroup, false );
         }
      }
      else
      {
         assert( 0 );
         THROWFROMFILE2( CND::BPBASE_CONDITION, 
                           CLASSNAME, GETFIELD, CND::BP_ERR_INVALID_METHOD_CALL );
      }
   }
   else if (idContainer == IFASTBP_PROC::RISK_LIST)
   {
       if (idField == ENTPROC::RISK_DEFF_DATE_APPL)
       {
           strValueOut = I_("N");
            
           if (const_cast<EntityProcess*>(this)->isContainerValid(IFASTBP_PROC::RISK_LIST))
           {
               EntityRisk *pEntityRisk = dynamic_cast<EntityRisk*>(const_cast<EntityProcess*>(this)->getCBOItem(IFASTBP_PROC::RISK_LIST, idDataGroup));
               if (pEntityRisk)
                   strValueOut = pEntityRisk->effectiveDateApplicable(idDataGroup) ? YES:NO;
           }
       }
   }
   else
   {
      assert( 0 );   
      THROWFROMFILE2( CND::BPBASE_CONDITION, 
                      CLASSNAME, GETFIELD, CND::BP_ERR_INVALID_METHOD_CALL );
   }
}

//******************************************************************************
SEVERITY EntityProcess::doSetField( const GenericInterface *rpGICaller, 
                                    const BFContainerId& idContainer,
                                    const BFFieldId& idField, 
                                    const BFDataGroupId& idDataGroup, 
                                    const DString& strValueOut, 
                                    bool bFormatted)
{  
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOSETFIELD );
   if (idContainer == IFASTBP_PROC::ENTITY_LIST)
   {
      DString entityType;

      getField (rpGICaller, IFASTBP_PROC::ENTITY_LIST, ifds::EntityType, entityType, false);
      if (idField == ifds::CountryName)
      {
         if ( entityType == ENTITY_TYPE_PRIMARY_BENEF || 
              entityType == ENTITY_TYPE_SECONDARY_BENEF)
         {
            setField (rpGICaller, IFASTBP_PROC::ENTITY_LIST, ifds::TaxJurisCode, strValueOut, bFormatted);
         }
      }
      else if (idField == ifds::CountryCode)
      {
         if (entityType == RESP_BENEFICIARY)
         {
            setField (rpGICaller, IFASTBP_PROC::ENTITY_LIST, ifds::TaxJuris, strValueOut, bFormatted);
         }
      }
      else
      {

         DString entityListCurrentItemKey = getCurrentListItemKey( rpGICaller, idContainer ); 
         DString entityId;
         DString entityTag;

         if( !AccountEntityXref::getValueForTag( entityListCurrentItemKey, ENTPROC::ENTITY_ID, entityId ) )
            entityId = entityListCurrentItemKey;

         DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

         Entity *pEntity;
         dstcWorkSession->getEntity( idDataGroup, entityId, pEntity );

		 if( idField != ifds::PaternalLastName && idField != ifds::MaternalLastName)
	         pEntity->setField( idField, strValueOut, idDataGroup, bFormatted, false, true );

         if( pEntity != NULL )
            pEntity->setFlagsUpdated( getDataGroupId() );
         BFAbstractCBO *rpPtr = getCBOItem( IFASTBP_PROC::ENTITY_LIST, idDataGroup );
         AccountEntityXrefObject *pAcctEntityXrefObject = dynamic_cast < AccountEntityXrefObject* > ( rpPtr );
         /*if( pAcctEntityXrefObject != NULL )
            pAcctEntityXrefObject->setFlagsUpdated( idDataGroup ); // this will update the new account-entity reference object*/

         if( idField == ifds::LastName       || 
             idField == ifds::FirstName      || 
             idField == ifds::Salutation     || 
             idField == ifds::EmployeeClass  ||
             idField == ifds::DofBirth )
         {
            rpPtr->setField (idField, strValueOut, idDataGroup);
         }

		 if (idField == ifds::PaternalLastName || idField == ifds::MaternalLastName) 
		 {
			 rpPtr->setField (idField, strValueOut, idDataGroup,  bFormatted, false, false );
			 pEntity->setField (idField, strValueOut, idDataGroup,  bFormatted, false, false );

			 if (idField == ifds::PaternalLastName)
				_paternalLastName = strValueOut;
			 else {
				getField (rpGICaller, IFASTBP_PROC::ENTITY_LIST, ifds::PaternalLastName, _paternalLastName, false);
			 }

			 if (idField == ifds::MaternalLastName)
				_maternalLastName = strValueOut;
			 else {
				getField (rpGICaller, IFASTBP_PROC::ENTITY_LIST, ifds::MaternalLastName, _maternalLastName, false);
			 }

			 DString dstrCompundName;
			 _paternalLastName.strip ();
			 _maternalLastName.strip ();
			 dstrCompundName = _paternalLastName + I_(" ") + _maternalLastName;
			 dstrCompundName.strip();

			 if (dstrCompundName.length() > 40) 
				 dstrCompundName = dstrCompundName.substr(0, 40);

			 pEntity->setField (ifds::LastName, dstrCompundName, idDataGroup,  bFormatted, true, false );
		 }

         if( idField == ifds::AccountNum )
         {
            DString temp( _accNum );
            temp.stripLeading( '0' );
            rpPtr->setField( idField, temp, idDataGroup );
         }

         if (idField == ifds::RiskLevel) //account needs to be refreshed
         {
            // Update Entity ID Set
            setEntityIds.insert( entityId );
         }
         //for account owners or nominee account owners, should refresh shareholder
         if ( entityType == I_("01") ||
              entityType == I_("21"))
         {
            setEntityOwnerIds.insert (entityId);
         }
         if( idField == ifds::TaxJuris )
         {
            DString entityId;
            getField (rpGICaller, IFASTBP_PROC::ENTITY_LIST, ifds::EntityId, entityId, false);

            DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
            Entity *pEntity;
            dstcWorkSession->getEntity( idDataGroup, entityId, pEntity );
            pEntity->setField(ifds::TaxJuris, strValueOut, idDataGroup, bFormatted);

            if (entityType == RESP_BENEFICIARY || 
                entityType == ENTITY_TYPE_PRIMARY_BENEF || 
                entityType == ENTITY_TYPE_SECONDARY_BENEF)
            {
               rpPtr->setField( ifds::TaxJurisCode, strValueOut, idDataGroup, false, true );
            }
         }
      }
   }
   else if (BF::NullContainerId == idContainer)
   {
      if (idField == ENTPROC::ORG_KEY)
      {
         _dstrOrgKey = strValueOut;
         flg_copy_entity = true;
      }
      else if (idField == ENTPROC::DEST_KEY)
      {
         _dstrDestKey = strValueOut;
         _pAccountEntityXref->AddCopy (_dstrOrgKey, _dstrDestKey, idDataGroup);
         flg_copy_entity = false;
      }
      else if (idField == ENTPROC::LETTER_REQUIRED)
      {
         if (_pAccountEntityXref)
         {
            BFObjIter iter (*_pAccountEntityXref, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
            
            while (!iter.end())
            {
               DString entityType;
               AccountEntityXrefObject* pXrefObj = dynamic_cast<AccountEntityXrefObject*> (iter.getObject());
               pXrefObj->getField (ifds::EntityType, entityType, idDataGroup);
               if (entityType == RESP_BENEFICIARY)
               {
                  pXrefObj->setField (ifds::LetterReq, strValueOut, idDataGroup, false);
                  break;
               }
               ++iter;
            }
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY EntityProcess::doGetErrors( const GenericInterface *rpGICaller, 
                                     const BFContainerId& idContainer,
                                     const BFFieldId& idField, 
                                     const BFDataGroupId& idDataGroup, 
                                     CONDITIONVECTOR &conditions ) const
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "doGetErrors" ) );

   SEVERITY sevRtn = SEVERE_ERROR;
   if( idContainer == IFASTBP_PROC::ENTITY_LIST )
   {
      if( idDataGroup != BF::HOST )
      {  // Assuming only non-host group fields can not be in error

         DString entityId;
         ( const_cast < EntityProcess *> ( this ) )->getField( rpGICaller, IFASTBP_PROC::ENTITY_LIST, ifds::EntityId, entityId, false );

         if( idField == ifds::LastName || idField == ifds::FirstName || idField == ifds::Salutation )
         {
            // ugly code but I have to do that to make the ugly thing work
            BFAbstractCBO *rpPtr = (const_cast<EntityProcess *>(this))->getCBOItem( IFASTBP_PROC::ENTITY_LIST, idDataGroup );
            AccountEntityXrefObject *pAcctEntityXrefObject = dynamic_cast < AccountEntityXrefObject* > ( rpPtr );
            if( pAcctEntityXrefObject != NULL )
               sevRtn = pAcctEntityXrefObject->getErrors( idField, idDataGroup, conditions );
         }
         else
         {
            Entity *pEntity;
            dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getEntity( idDataGroup, entityId, pEntity );
            sevRtn = pEntity->getErrors( idField, idDataGroup, conditions );
         }
      }
      else
      {  // Host group, no errors so don't bother with call
         sevRtn = NO_CONDITION;
      }
   }
   return(sevRtn);
}

//******************************************************************************
void *EntityProcess::getPtrForContainer ( const BFContainerId &idContainer, 
                                          const BFDataGroupId &idDataGroup)
{
   void *ptr = NULL;

   try
   {
      if (IFASTBP_PROC::ENTITY_LIST == idContainer)
      {
         ptr = _pAccountEntityXref;
      }
      else if (IFASTBP_PROC::ENTITY_IDS_LIST == idContainer)
      {
         DString entityId;
         BFAbstractCBO *rpPtr = getCBOItem (IFASTBP_PROC::ENTITY_LIST, idDataGroup);

         _pEntityIdsList = NULL;
         if (rpPtr)
         {
            rpPtr->getField (ifds::EntityId, entityId, idDataGroup);
            entityId.stripLeading ('0');

            if (!entityId.empty())
            {
               Entity *pEntity;
               dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getEntity( idDataGroup, entityId, pEntity );

               if (pEntity)
               {
                  pEntity->getEntityIdsList (_pEntityIdsList, idDataGroup, true);
               }
               ptr = _pEntityIdsList;
            }
         }
      }
      else if (IFASTBP_PROC::RISK_LIST == idContainer)
      {
          BFAbstractCBO *rpPtr = getCBOItem (IFASTBP_PROC::ENTITY_LIST, idDataGroup);
          Entity *pEntity = NULL;
          EntityRiskList *pEntityRiskList = NULL;
          DString entityId;

          if (rpPtr)
          {
              rpPtr->getField(ifds::EntityId, entityId, idDataGroup);
              entityId.stripLeading('0');
          }

          if (!entityId.empty() && 
              dynamic_cast<DSTCWorkSession*>(getBFWorkSession())->getEntity( idDataGroup, entityId, pEntity) <= WARNING&& pEntity && 
              pEntity->getEntityRiskList(pEntityRiskList, idDataGroup) <= WARNING && pEntityRiskList)
          {
              ptr = pEntityRiskList;
          }
      }
      else
      {
      }
   }
   catch (ConditionException &)
   {
      throw;
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return ptr;
}

//*****************************************************************************
SEVERITY EntityProcess::performSearch ( GenericInterface *rpGICaller, 
                                        const BFContainerId &idSearch, 
                                        E_SEARCHACTION eSearchAction)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTBP_CONDITION, CLASSNAME, PERFORMSEARCH);
   E_COMMANDRETURN rtn = CMD_FAILURE;
   const BFDataGroupId& idDataGroup = getDataGroupId();
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   bool flg_do_search, 
      flg_at_least_one_search (false);
   DString accountNum (_accNum), 
      seqNumber, 
      entityType,
      temporaryEntityType;
   DString dstrValidRATaxType;
   DString strMarket = DSTCommonFunctions::getMarket();

   assert (!flg_no_account);

   if (IFASTBP_PROC::BACKGROUND_ON_BTN_SEARCH == idSearch)
   {
      bool flg_search_successful = false;
      DString lastName, 
         firstName, 
         birthLastName, 
         birthFirstName, 
         homeTel, 
         businessTel,
         currentEntityType,
         currentEntityId;
      
      getField (rpGICaller, IFASTBP_PROC::ENTITY_LIST, ifds::LastName, lastName, false);
      getField (rpGICaller, IFASTBP_PROC::ENTITY_LIST, ifds::FirstName, firstName, false);
      getField (rpGICaller, IFASTBP_PROC::ENTITY_LIST, ifds::BirthLastName, birthLastName, false);
      getField (rpGICaller, IFASTBP_PROC::ENTITY_LIST, ifds::BirthFirstName, birthFirstName, false);
      getField (rpGICaller, IFASTBP_PROC::ENTITY_LIST, ifds::HomePhone, homeTel, false);
      getField (rpGICaller, IFASTBP_PROC::ENTITY_LIST, ifds::BusinessPhone, businessTel, false);
//selected entity type in entity maintainance screen, get the type and the id                 
      getField (rpGICaller, IFASTBP_PROC::ENTITY_LIST, ifds::EntityType, currentEntityType, false);
      getField (rpGICaller, IFASTBP_PROC::ENTITY_LIST, ifds::EntityId, currentEntityId, false);

      const int LAST_FIRST_NAME = 0, 
            BIRTH_LAST_FIRST_NAME = 1, 
            HOME_TELEPHONE = 2, 
            BUSINESS_TELEPHONE = 3, 
            ID_VALUE = 4, 
            MAX_CRITERIA = 5;

      for (int criteria = LAST_FIRST_NAME; criteria < MAX_CRITERIA && !flg_search_successful; criteria++)
      {
         setParameter (ENTSRCHLIT::ENTITY_BACKGROUNG_SEARCH, YES);
         flg_do_search = false;         
         
         if (LAST_FIRST_NAME == criteria)
         {
            if (!lastName.empty() || !firstName.empty())
            {
               setParameter (ENTSRCHLIT::SEARCH_CRITERIA_CODE, SEARCHCRITERIA::ENTITY_SEARCH);
               setParameter (ENTSRCHLIT::SEARCH_USING_CODE, SEARCHENTITYUSING::NAME);
               if (strMarket == MARKET_IDS::JAPAN)
               {
                  setParameter (ENTSRCHLIT::FIRST_VALUE, lastName);
                  setParameter (ENTSRCHLIT::SECOND_VALUE, firstName);  
               }
               else
               {
                  setParameter (ENTSRCHLIT::FIRST_VALUE, firstName);
                  setParameter (ENTSRCHLIT::SECOND_VALUE, lastName);
               }
               if (currentEntityType == I_("58"))
               {
                  //see the comment below - under //MT353/MT536
                  setParameter (ENTSRCHLIT::ALLENTITY, I_("Y"));
               }
               else if (currentEntityType == REGISTRATION_AGENT_ENTITY_TYPE)
               {
                  setParameter (ENTSRCHLIT::ALLENTITY, I_("Y"));
                  setParameter (ENTSRCHLIT::WHERE_USED_CODE, REGISTRATION_AGENT_WHERE_USED_CODE);
               }
               flg_do_search = true;
            }
         }
         else if (BIRTH_LAST_FIRST_NAME == criteria)
         {
            if (!birthLastName.empty() || !birthFirstName.empty())
            {
               setParameter (ENTSRCHLIT::SEARCH_CRITERIA_CODE, SEARCHCRITERIA::ACCOUNT_SEARCH);
               setParameter (ENTSRCHLIT::SEARCH_USING_CODE, SEARCHACCOUNTUSING::BIRTH_NAME);
               if (strMarket == MARKET_IDS::JAPAN)
               {
                  setParameter (ENTSRCHLIT::FIRST_VALUE, birthLastName);
                  setParameter (ENTSRCHLIT::SECOND_VALUE, birthFirstName);                     
               }
               else
               {
                  setParameter (ENTSRCHLIT::FIRST_VALUE, birthFirstName);
                  setParameter (ENTSRCHLIT::SECOND_VALUE, birthLastName);
               }
               flg_do_search = true;
            }
         }
         else if (HOME_TELEPHONE == criteria)
         {
            if (!homeTel.empty())
            {
               setParameter (ENTSRCHLIT::SEARCH_CRITERIA_CODE, SEARCHCRITERIA::ACCOUNT_SEARCH);
               setParameter (ENTSRCHLIT::SEARCH_USING_CODE, SEARCHACCOUNTUSING::TELEPHONE);
               setParameter (ENTSRCHLIT::FIRST_VALUE, homeTel);
               flg_do_search = true;
            }
         }
         else if (BUSINESS_TELEPHONE == criteria)
         {
            if (!businessTel.empty())
            {
               setParameter( ENTSRCHLIT::SEARCH_CRITERIA_CODE, SEARCHCRITERIA::ACCOUNT_SEARCH );
               setParameter( ENTSRCHLIT::SEARCH_USING_CODE, SEARCHACCOUNTUSING::TELEPHONE );
               setParameter( ENTSRCHLIT::FIRST_VALUE, businessTel );
               flg_do_search = true;
            }
         }
         else if (ID_VALUE == criteria)
         {
            DString idType, 
               idValue,
               allEntity (I_("N"));
            
            getField (rpGICaller, IFASTBP_PROC::ENTITY_IDS_LIST, ifds::IdType, idType, false);
            getField (rpGICaller, IFASTBP_PROC::ENTITY_IDS_LIST, ifds::IdValue, idValue, false);
            if (!idType.empty() && 
                !idValue.empty())
            {
               if (idType == IDS::DRIVERS_LICENSE)
               {
                  idType = SEARCHACCOUNTUSING::DRIVER_LICENSE;
               }
               else if (idType == IDS::PASSPORT)
               {
                  idType = SEARCHACCOUNTUSING::PASSPORT;
               }
               else if (idType == IDS::BIRTH_CERTIFICATE)
               {
                  idType = SEARCHACCOUNTUSING::BIRTH_CERTIFICATE;
               }
               else if( idType == IDS::CREDIT_CARD)
               {
                  idType = SEARCHACCOUNTUSING::CREDIT_CARD;
               }
               else if (idType == IDS::NATIONAL_ID)
               {
                  idType = SEARCHACCOUNTUSING::NATIONAL_ID;
               }
               else if (idType == IDS::SIN)
               {
                  idType = SEARCHACCOUNTUSING::SOCIAL_INSURANCE_NUMBER;
               }
               else if (idType == IDS::CIF)
               {
                  idType = SEARCHACCOUNTUSING::CIF;
               }
               else if (idType == IDS::ACCESS_ID)
               {
                  idType = SEARCHACCOUNTUSING::ACCESS_ID;
               }
               //MT353/MT536
               else if (idType == IDS::CLEARING_PLATFORM)
               {
                  idType = SEARCHACCOUNTUSING::CLEARING_ID;
//this is due to the fact that we can look for entities that are not linked to an account
//we have to modify the search - if any entity is found - then the type should clearing platform = 58
//this is not how the functionality of this search works - we needed an adjustment.
//if users search by a different criteria this piece of code will not be exercised. 
//the assumption here can be easily broken - (SP)
                  allEntity = I_("Y");
                  temporaryEntityType = I_("58");
               }
               else if (idType == IDS::OTHER)
               {
                  idType = SEARCHACCOUNTUSING::ID_OTHER;

                  if (currentEntityType == REGISTRATION_AGENT_ENTITY_TYPE)
                  {
                     allEntity = I_("Y");
                     setParameter (ENTSRCHLIT::WHERE_USED_CODE, REGISTRATION_AGENT_WHERE_USED_CODE);
                  }

               }
               setParameter (ENTSRCHLIT::SEARCH_CRITERIA_CODE, SEARCHCRITERIA::ACCOUNT_SEARCH);
               setParameter (ENTSRCHLIT::SEARCH_USING_CODE, idType);
               setParameter (ENTSRCHLIT::FIRST_VALUE, idValue);
               setParameter (ENTSRCHLIT::ALLENTITY, allEntity);
               flg_do_search = true;
            }
            else
            {
               flg_do_search = false;
            }
         }
         else
         {
            flg_do_search = false;
         }

         if (flg_do_search)
         {
            DString entityId, 
               dstrSpouseEntityID (NULL_STRING),
               lastName (NULL_STRING);

            flg_at_least_one_search = true;
            rtn = invokeProcessFromChild (this, CMD_BPROC_SEARCH, PROC_SUPPORT);     
            if (rtn == CMD_OK)
            {
               getParameter (I_("EntityId" ), entityId);
               getParameter (I_("EntityType" ), entityType);
               getParameter (I_("ValidRATaxType" ), dstrValidRATaxType);
               setParameter (ENTPROC::ACCOUNT_NUM, _accNum);
//do not re-link if we searched for the same entity...
               if (currentEntityId != entityId)
               {
                  if (entityType.empty())
                  {
                     entityType = temporaryEntityType;
                  }
                  if (!entityId.empty())
                  {
                     Entity *pEntity (NULL);
                     DString lastName;

                     dstcWorkSession->getEntity (idDataGroup, entityId, pEntity);

                     if (pEntity)
                     {
                        pEntity->getField (ifds::SpouseEntityID, dstrSpouseEntityID, idDataGroup, false);
                        pEntity->getField (ifds::LastName, lastName, idDataGroup, false);
                        dstrSpouseEntityID.strip();
                     }
                     if (entityType == currentEntityType)
                     {
                        //Sequence Number is already calculated fot current entity type.
                        getField (rpGICaller, IFASTBP_PROC::ENTITY_LIST, ifds::SeqNumber, seqNumber, false);
                     }
                     else
                     {
                        //Calculate the new one.
                        _pAccountEntityXref->GetNextSeqNumber(idDataGroup, accountNum, entityType, seqNumber);
                     }

                     DString cssstopSINMatch;
                     dstcWorkSession->getOption (ifds::CSSStopSINMatch, cssstopSINMatch, BF::HOST, false);  

                     // new logic to fix in#1062864 
                     DString dstrEntityTypeExceptionList;

                     dstcWorkSession->getOption (ifds::OnLineEntExcept, dstrEntityTypeExceptionList, BF::HOST, false);

                     bool bIsEntityInException = DSTCommonFunctions::codeInList (entityType, dstrEntityTypeExceptionList);
                     bool bCreateNewEntity = cssstopSINMatch == I_("Y") && bIsEntityInException == false; 

                     AccountEntityXrefObject* pAccountEntityXrefObject (NULL);
                     
                     if (bCreateNewEntity)
                     {
                        Entity* pNewEntity (NULL);

                        if ( dstcWorkSession->getNewEntity (idDataGroup, pNewEntity) <= WARNING &&
                             pEntity) //create a new entity
                        {
                           if (pNewEntity)
                           {
                              pNewEntity->getEntityId (entityId);
                              //clone the found entity...
                              BFData bfData51 (ifds::DSTC0051_VW);

                              BFDataFieldIter dIter (bfData51);
                              DString str;
                              for ( ;dIter; ++dIter)
                              {
                                 BFDataField& idField = dIter();

                                 if ( idField.getId() == ifds::ModDate ||
                                      idField.getId() == ifds::ModUser ||
                                      idField.getId() == ifds::GoodBad ||
                                      idField.getId() == ifds::RepeatCount ||
                                      idField.getId() == ifds::Username ||
                                      idField.getId() == ifds::TaxJurisDeff ||
                                      idField.getId() == ifds::Language)                                 {
                                    continue;
                                 }
                                 pEntity->getField (idField.getId(), str, idDataGroup);
                                 pNewEntity->setField (idField.getId(), str, idDataGroup);
                              }
                              //copy the ids...
                              EntityIdsList *pEntityIdsList (NULL),
                                 *pNewEntityIdsList (NULL);

                              if ( pEntity->getEntityIdsList (pEntityIdsList, idDataGroup, false) <= WARNING &&
                                   pEntityIdsList &&
                                   pNewEntity->getEntityIdsList (pNewEntityIdsList, idDataGroup, true) <= WARNING &&
                                   pNewEntityIdsList)
                              {
                                 BFObjIter iter ( *pEntityIdsList, 
                                                   BF::HOST, 
                                                   true);
                                 while (!iter.end())
                                 {
                                    EntityIds *pEntityIds = dynamic_cast <EntityIds *> (iter.getObject());

                                    DString entityIdsIdType;

                                    pEntityIds->getField (ifds::IdType, entityIdsIdType, idDataGroup, false);

                                    //skip CIF and AccessID - those are system generated..
                                    if (entityIdsIdType != IDS::ACCESS_ID && entityIdsIdType != IDS::CIF)
                                    {
                                       DString newEntityIdsKey (NULL_STRING);
                                       DString entityType = pNewEntity->getEntityType ();

                                       EntityIds *pNewEntityIds = 
                                          dynamic_cast <EntityIds *> (pNewEntityIdsList->getObject (newEntityIdsKey, idDataGroup));

                                       if (pNewEntityIds)
                                       {
                                          pNewEntityIds->init (idDataGroup, entityId, entityType);

                                          BFData bfData51_repeat (ifds::DSTC0051_VWRepeat_Record);

                                          BFDataFieldIter dIter (bfData51_repeat);
                                          DString str;
                                          for ( ;dIter; ++dIter)
                                          {
                                             BFDataField& idField = dIter();

                                             if (idField.getId() == ifds::IdTypeDesc)
                                             {
                                                continue;
                                             }

                                             pEntityIds->getField (idField.getId(), str, idDataGroup);
                                             pNewEntityIds->setField (idField.getId(), str, idDataGroup);
                                          }
                                       }
                                    }
                                    ++iter;
                                 }
                              }
                           }
                        }
                     }
                     if (_pAccountEntityXref->LinkEntity( accountNum, 
                                                          entityType, 
                                                          seqNumber, 
                                                          entityId, 
                                                          idDataGroup, 
                                                          pAccountEntityXrefObject,
                                                          false) <= WARNING &&
                        pAccountEntityXrefObject)
                     {
                        AccountEntityXref::buildKey ( selectionKey, 
                                                      _accNum, 
                                                      entityType, 
                                                      seqNumber, 
                                                      entityId, 
                                                      _pAccountEntityXref->getStrCurrentCount());

                        //set the last name on the xref object since this is required
                        pAccountEntityXrefObject->setField (ifds::LastName, lastName, idDataGroup);
                        if(dstrValidRATaxType != I_(""))
                           pAccountEntityXrefObject->setField(ifds::ValidRATaxType, dstrValidRATaxType, idDataGroup, false);

                        bool refreshflag = _pAccountEntityXref->getrefreshflag();
                        
                        _pAccountEntityXref->setrefreshflag (true);
                        deleteItemFromList (rpGICaller, IFASTBP_PROC::ENTITY_LIST); //erase the old tem in the list
                        _pAccountEntityXref->setrefreshflag (refreshflag);
                        setContainer (IFASTBP_PROC::ENTITY_LIST, NULL);
                        setContainer (IFASTBP_PROC::ENTITY_LIST, _pAccountEntityXref);
						pAccountEntityXrefObject->updateVerifyStatFlag(idDataGroup);
						pAccountEntityXrefObject->setFieldReadOnly(ifds::VerifyStat,idDataGroup,true);
                     }                     
                     if (GETCURRENTHIGHESTSEVERITY () <= WARNING)
                     {
                        if ( entityType == I_("01") &&  //account owner
                             !dstrSpouseEntityID.empty () && 
                             dstrSpouseEntityID != I_("0"))
                        {
                           dstcWorkSession->getEntity (BF::HOST, dstrSpouseEntityID, pEntity);
                           getField (rpGICaller, IFASTBP_PROC::ENTITY_LIST, ifds::SeqNumber, seqNumber, false);

                           _pAccountEntityXref->LinkEntity ( accountNum, 
                                                             ENTITY_TYPE_OWNER_SPOUSE, 
                                                             NULL_STRING, 
                                                             dstrSpouseEntityID, 
                                                             idDataGroup, 
                                                             pAccountEntityXrefObject, 
                                                             true);
                        }
                     }
                  }
               }
               return  GETCURRENTHIGHESTSEVERITY ();
            }
            else if (rtn == CMD_CANCEL)
            {
               return NO_CONDITION; // no condition added to the frame
            }
         }
         flg_search_successful = !( rtn != CMD_OK );
      }
      if (!flg_at_least_one_search)
      {
         ADDCONDITIONFROMFILE (CND::BP_ERR_NO_SEARCH_CRITERIA);
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
SEVERITY EntityProcess::deleteItemFromList (const GenericInterface *rpGICaller, 
   const BFContainerId &idList)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTBP_CONDITION, CLASSNAME, I_("deleteItemFromList"));

   assert (!flg_no_account );
   const BFDataGroupId& idDataGroup = getDataGroupId();

   DSTCWorkSession *pDSTCWorkSession = 
      dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   const DString& dstrKey = getCurrentListItemKey (rpGICaller, idList);

   DString strDelEntityID, strDelEntityType;

   if (IFASTBP_PROC::ENTITY_LIST == idList)
   {
      if (_pAccountEntityXref->IsDeleteAllowed (dstrKey, getDataGroupId(), false))
      {
         if (isCurrentListItemNew (const_cast <GenericInterface*> (rpGICaller),idList))
         {
            DString entityId;

            getField (rpGICaller, IFASTBP_PROC::ENTITY_LIST, 
               ifds::EntityId, entityId, false);
            entityId.stripLeading ('0');

            int canDelEntity = 0;
            BFObjIter iterXRef( *_pAccountEntityXref, getDataGroupId(), true, BFObjIter::ITERTYPE::NON_DELETED, false, true );
            iterXRef.begin();
            while(!iterXRef.end ())
            {
               DString TmpentityId;
               iterXRef.getObject()->getField(ifds::EntityId, TmpentityId, idDataGroup);				
               if(  entityId == TmpentityId.stripLeading ('0') )
               {
                  canDelEntity ++;
               }
               ++iterXRef;
            }

            WorkSessionEntityList *pWorkSessionEntityList = NULL;

            if (canDelEntity <= 1 && pDSTCWorkSession->getWorkSessionEntityList (
                  pWorkSessionEntityList) <= WARNING &&
               pWorkSessionEntityList)
            {
               BFObjIter iter (*pWorkSessionEntityList, getDataGroupId(), 
                  false, BFObjIter::ITERTYPE::NON_DELETED);

               iter.positionByKey (entityId);
               if (!iter.end ())
               {
                  strDelEntityID = entityId;
                  iter.getObject()->getField(ifds::EntityType, strDelEntityType, 
                     getDataGroupId(), false );
                  iter.removeObjectFromMap ();//deletes the object instance, as well
               }
            }
         }
      }
   }
   if (AbstractProcess::deleteItemFromList (rpGICaller, idList) <= WARNING)
   {
      if (IFASTBP_PROC::ENTITY_LIST == idList)
      {
         _pAccountEntityXref->SetChildrenSpousalNameSubSet(getDataGroupId());

         //strDelEntityType.strip().upperCase();
         //if ( strDelEntityType == PARENT_GUARDIAN_ENTITY_TYPE ||
         //     strDelEntityType == RESP_DESIGNATED_INSTIT_ENTITY_TYPE ||
         //     strDelEntityType == RESP_PCG_INDIV_ENTITY_TYPE || 
         //     strDelEntityType == RESP_PCG_INST_ENTITY_TYPE )
         //{
         //   _pAccountEntityXref->setRESPSelectableFieldSubSet(strDelEntityType,getDataGroupId());
         //}
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************

const BFProperties *EntityProcess::doGetFieldAttributes ( const GenericInterface *rpGICaller, 
                                                          const BFContainerId &idContainer, 
                                                          const BFFieldId &idField, 
                                                          const BFDataGroupId &idDataGroup)
{
   if (IFASTBP_PROC::ENTITY_LIST == idContainer)
   {
      {
         // this is for Entity fields
         BFAbstractCBO *rpPtr = getCBOItem( IFASTBP_PROC::ENTITY_LIST, idDataGroup );
         AccountEntityXrefObject *pAcctEntityXrefObject = dynamic_cast < AccountEntityXrefObject* > ( rpPtr );
         
         if (pAcctEntityXrefObject != NULL)
         {
            DString entityId;
            pAcctEntityXrefObject->getField (ifds::EntityId, entityId, idDataGroup);
            Entity *pEntity (NULL);
            dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getEntity (idDataGroup, entityId, pEntity);
            return pEntity->getFieldProperties (idField, idDataGroup);
         }
         assert(0) ;
      }
   }
   return NULL;
}

//*****************************************************************************
bool EntityProcess::doRegisterObserver ( const GenericInterface *rpGICaller,
                                            const BFContainerId &idContainer,
                                            const BFFieldId &idField,
                                            const BFDataGroupId &idDataGroup,
                                            BFObserver &rpObserver) 
{
   bool bRegistered = false;

   if (idContainer == IFASTBP_PROC::ENTITY_LIST)
   {
      if ( idField == ifds::VerifyStatDetails)
      {
        
		  BFAbstractCBO *rpPtr = getCBOItem( IFASTBP_PROC::ENTITY_LIST, idDataGroup );
		  AccountEntityXrefObject *pAcctEntityXrefObject = dynamic_cast < AccountEntityXrefObject* > ( rpPtr );
		  if( pAcctEntityXrefObject != NULL )
		  {
			 DString entityId;
			 pAcctEntityXrefObject->getField( ifds::EntityId, entityId, idDataGroup );

			 Entity *pEntity;
			 dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getEntity( idDataGroup, entityId, pEntity );
			 bRegistered = pEntity->registerObserver ( idField, 
														idDataGroup, 
														&rpObserver, 
														FIELD_NOTIFICATIONS, 
														E_EVENT_ALL);

		  }
      }
   }
   return bRegistered;
}
//*****************************************************************************

SEVERITY EntityProcess::setData( GenericInterface *rpGICaller, const BFContainerId& idContainer, const BFData *rpData )
{
   TRACE_METHOD( CLASSNAME, SETDATA );
   SEVERITY sevRtn = SEVERE_ERROR;

   if( idContainer == IFASTBP_PROC::ENTITY_LIST )
   {
      const BFDataGroupId& idDataGroup = getDataGroupId();

      BFAbstractCBO *rpPtr = getCBOItem( IFASTBP_PROC::ENTITY_LIST, idDataGroup );
      AccountEntityXrefObject *pAcctEntityXrefObject = dynamic_cast < AccountEntityXrefObject* > ( rpPtr );
      if( pAcctEntityXrefObject != NULL )
      {
         DString entityId;
         pAcctEntityXrefObject->getField( ifds::EntityId, entityId, idDataGroup );

         Entity *pEntity;
         dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getEntity( idDataGroup, entityId, pEntity );
         pEntity->setData( *rpData, idDataGroup );

      }
   }

   return(AbstractProcess::setData( rpGICaller, idContainer, rpData ));
}

//*****************************************************************************

bool EntityProcess::doRefresh( GenericInterface *rpGICaller,
                               const I_CHAR *szOriginalCommand)
{


   setParameter( ENTPROC::ACCOUNT_NUM, _accNum );
   setParameter( ENTPROC::KEY, strKey );
   setParameter( ENTPROC::EXIST_ACCOUNT, flg_no_account ? NO : YES );  

   return(_rpChildGI->refresh( this, NULL ));
}

//******************************************************************************
bool EntityProcess::doOk( GenericInterface *rpGICaller )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doOk") );
   bool bRetVal (true),
      bIgnoreWarningsOnOk2 (getIgnoreWarningsOnOk2());
   SEVERITY sevRtn (NO_CONDITION);
   const BFDataGroupId& idDataGroup = getDataGroupId();
   DString accountNum;

   if (_pAccountEntityXref != NULL)
   {
      //if it is updated, ok2 will call validateAll on it
      if (!_pAccountEntityXref->isUpdatedForDataGroup (idDataGroup))
      {
         sevRtn = _pAccountEntityXref->validateAll (idDataGroup);
         if (sevRtn == WARNING)
         {
            setIgnoreWarningsOnOk2 (false);
         }
      }
   }   
   if (sevRtn == WARNING && !getIgnoreWarningsOnOk2())
   {
//      bRetVal = rpGICaller->send (this, I_("WarningConfirm"));
      setIgnoreWarningsOnOk2 (bIgnoreWarningsOnOk2);
   }
   else if (sevRtn > WARNING)
   {
      bRetVal = false;
   }
   if (bRetVal && _pAccountEntityXref)
   {
// refresh account list if the entity risk level flag has been changed
      std::set< DString >::iterator iter = setEntityIds.begin();
      while (iter != setEntityIds.end())
      {
         DString searchEntityKey;
         BFObjIter iterXRef (
            *_pAccountEntityXref, 
            getDataGroupId(), 
            true, 
            BFObjIter::ITERTYPE::NON_DELETED, 
            false, 
            true);

         AccountEntityXref::buildPartialKeyForEntityId (searchEntityKey, *iter);
         iterXRef.begin (OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchEntityKey);
         while (!iterXRef.end())
         {
            DString accountNum,
               xRefKey = iterXRef.getStringKey();
            
            if (AccountEntityXref::getValueForTag (xRefKey, I_("AccountNum"), 
                  accountNum))
            {
               MFAccount *pMFAccount = NULL;

               if (dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->
                     getMFAccount (idDataGroup, accountNum, pMFAccount, false) <= WARNING && 
                  pMFAccount)
               {
                  pMFAccount->refreshMe (true);
               }
            }
            ++iterXRef;
         }
         ++iter;
      }
//refresh shareholder if information on the entity owner(s) has been changed
      iter = setEntityOwnerIds.begin();
      while (iter != setEntityOwnerIds.end())
      {
         DString searchEntityKey;
         BFObjIter iterXRef (
            *_pAccountEntityXref, 
            getDataGroupId(), 
            true, 
            BFObjIter::ITERTYPE::NON_DELETED, 
            false, 
            true);

         AccountEntityXref::buildPartialKeyForEntityId (searchEntityKey, *iter);
         iterXRef.begin (OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchEntityKey);
         while (!iterXRef.end())
         {
            DString xRefKey = iterXRef.getStringKey();
            
            if (AccountEntityXref::getValueForTag (xRefKey, I_("AccountNum"), 
                  accountNum))
            {
               MFAccount *pMFAccount = NULL;

               if (dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->
                     getMFAccount (idDataGroup, accountNum, pMFAccount, false) <= WARNING && 
                  pMFAccount)
               {
                  DString shrNum;

                  pMFAccount->getField (ifds::ShrNum, shrNum, idDataGroup, false);
                  
                  Shareholder *pShareholder = NULL;

                  if (dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->
                     getShareholder (idDataGroup, shrNum, pShareholder, false) <= WARNING && 
                  pShareholder)
                  {
                     pShareholder->refreshMe (true);
                  }
               }
            }
            ++iterXRef;
         }
         ++iter;
      }

      // Refresh MFAccount if there is any update on entity(s).
      BFObjIter iterAccountEntityXref(*_pAccountEntityXref, getDataGroupId(), true, BFObjIter::ITERTYPE::NON_DELETED);

      while (!iterAccountEntityXref.end())
      {
          DString iterEntityId;
          Entity *pEntity = NULL;
          MFAccount *pMFAccount = NULL;

          iterAccountEntityXref.getObject()->getField(ifds::EntityId, iterEntityId, getDataGroupId());

          if (dynamic_cast<DSTCWorkSession*>(getBFWorkSession())->getEntity(getDataGroupId(), iterEntityId, pEntity) <= WARNING &&
              pEntity &&
              pEntity->isUpdated() &&
              !_accNum.empty() &&
              dynamic_cast<DSTCWorkSession*>(getBFWorkSession())->getMFAccount(idDataGroup, _accNum, pMFAccount, false) <= WARNING &&
              pMFAccount)
          {
              pMFAccount->refreshMe(true);
              break;
          }

          ++iterAccountEntityXref;
      }
   }
	
	
	DString dstrDeathDate, dstrDeathNotifDate;
	getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::DofDeath, dstrDeathDate, false );
	getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::DofDeathNotice, dstrDeathNotifDate, false );
				
	// this is if death dates got changed back to 12/31/9999
	bool bDeathDatesChanged = _originalDeathDate.empty () && _originalDeathOfNotifDate.empty () ? false : true;
	
	if (!dstrDeathDate.empty () || !dstrDeathNotifDate.empty () || bDeathDatesChanged)
	{
		   MFAccount *pMFAccount = NULL;

           if (dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getMFAccount (idDataGroup, _accNum, pMFAccount, false) <= WARNING && 
               pMFAccount)
           {
				pMFAccount->refreshMe (true);
		   }
	}

   return bRetVal;
}

//*******************************************************************************
void EntityProcess::doPostOk (GenericInterface *rpGICaller, bool bSuccessFlag)
{

}

//*******************************************************************************

SEVERITY EntityProcess::getHistoricalParameters( const BFContainerId& idContainer, HISTORICAL_VECTOR &vectorHistorical )
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS);
   
   if ( idContainer == IFASTBP_PROC::ENTITY_LIST )
   {
      DString keyStringIDI, dstrRecord;
      DString dstrEntityType, dstrAccountNum, dstrSeqNumber, dstrAccountType;
      // Entity Identity
      // Key - EntityID
      DString dstrEntityId;
      getField( this, BF::NullContainerId, ifds::EntityIdentityRid, dstrRecord, false );
      getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::EntityId, dstrEntityId, false );
      addIDITagValue( keyStringIDI, MFCAN_IP_PARAM::ENTITY_ID, dstrEntityId );
      HistoricalElement heEntityIdentity( dstrRecord, AUDITTYPE::ENTIDT, keyStringIDI );
      vectorHistorical.push_back( heEntityIdentity );

      // Account Entity
      // Key - Account Number, EntityType, SeqNumber
      // AcctEntityRid
      getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::AcctEntityRid, dstrRecord, false );
      getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::EntityType, dstrEntityType, false );
      getField( this, BF::NullContainerId, ENTPROC::ACCOUNT_NUMBER_FIELD, dstrAccountNum, false );
      getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::SeqNumber, dstrSeqNumber, false );
      keyStringIDI = NULL_STRING;
      addIDITagValue( keyStringIDI, MFCAN_IP_PARAM::ACCOUNT_NUM, dstrAccountNum );
      addIDITagValue( keyStringIDI, MFCAN_IP_PARAM::ENTITY_TYPE, dstrEntityType );
      addIDITagValue( keyStringIDI, MFCAN_IP_PARAM::SEQNUMBER, dstrSeqNumber );
      HistoricalElement heAccountEntity( dstrRecord, AUDITTYPE::SHENTA, keyStringIDI );
      vectorHistorical.push_back( heAccountEntity );

      // Entity ID Historical Data
      getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::EntityIdentityRid, dstrRecord, false );
      keyStringIDI = NULL_STRING;
      addIDITagValue( keyStringIDI, MFCAN_IP_PARAM::ENTITY_ID, dstrEntityId );
      HistoricalElement heEntityIDs( dstrRecord, AUDITTYPE::ENTIDS, keyStringIDI );
      vectorHistorical.push_back( heEntityIDs );

      // Entity Risk
      keyStringIDI = NULL_STRING;
      addIDITagValue( keyStringIDI, MFCAN_IP_PARAM::ENTITY_ID, dstrRecord );
      HistoricalElement heEntityRISK( dstrRecord, AUDITTYPE::ENTITY_RISK, keyStringIDI );
      vectorHistorical.push_back( heEntityRISK );

      // (Possibly) Joint Information
      // Check if EntityType is Account Owner ('01') and AccountType is Joint ('02')
      // AccEntityJointRid as AuditRecId
      // Key - Account Number, EntityType, and SeqNumber
      if( dstrEntityType.stripAll().stripLeading('0') == I_("1") )
      {
         getField( this, BF::NullContainerId, ENTPROC::ACCOUNT_TYPE, dstrAccountType, false );
         if( dstrAccountType.stripAll().stripLeading('0') == I_("2") )
         {
            getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::AcctEntityJointRid, dstrRecord, false );
            keyStringIDI = NULL_STRING;
            addIDITagValue( keyStringIDI, MFCAN_IP_PARAM::ACCOUNT_NUM, dstrAccountNum );
            addIDITagValue( keyStringIDI, MFCAN_IP_PARAM::ENTITY_TYPE, dstrEntityType );
            addIDITagValue( keyStringIDI, MFCAN_IP_PARAM::SEQNUMBER, dstrSeqNumber );
            HistoricalElement heJointInformation( dstrRecord, AUDITTYPE::SHENTJ, keyStringIDI );
            vectorHistorical.push_back( heJointInformation );
         }
      }

      // (Possibly) Beneficiary and RESP Information
      // Check if EntityType is beneficiary ('07', '08', '50')
      // AcctEntityBenfRid
      // Key - Account Number ,EntityType, and SeqNumber
      else if( dstrEntityType.stripAll().stripLeading('0') == I_("7") 
               || dstrEntityType.stripAll().stripLeading('0') == I_("8") 
               || dstrEntityType.stripAll().stripLeading('0') == I_("50") )
      {
         getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::AcctEntityBenefRid, dstrRecord, false );
         keyStringIDI = NULL_STRING;
         addIDITagValue( keyStringIDI, MFCAN_IP_PARAM::ACCOUNT_NUM, dstrAccountNum );
         addIDITagValue( keyStringIDI, MFCAN_IP_PARAM::ENTITY_TYPE, dstrEntityType );
         addIDITagValue( keyStringIDI, MFCAN_IP_PARAM::SEQNUMBER, dstrSeqNumber );
         HistoricalElement heBeneficiaryInformation( dstrRecord, AUDITTYPE::SHENTB, keyStringIDI );
         vectorHistorical.push_back( heBeneficiaryInformation );
      }

      // (Possibly) Escrow
      // Check if EntityType is Escrow Representative ('11')
      // AssignDetlRid as AuditRecId
      // Key - Account Number, EntityType, and EntityTypeSequence
      else if( dstrEntityType.stripAll().stripLeading('0') == I_("11") )
      {
         getField( this, IFASTBP_PROC::ENTITY_LIST, ifds::AssignDetlRid, dstrRecord, false );
         keyStringIDI = NULL_STRING;
         addIDITagValue( keyStringIDI, MFCAN_IP_PARAM::ACCOUNT_NUM, dstrAccountNum );
         addIDITagValue( keyStringIDI, MFCAN_IP_PARAM::ENTITY_TYPE, dstrEntityType );
         addIDITagValue( keyStringIDI, MFCAN_IP_PARAM::SEQNUMBER, dstrSeqNumber );
         HistoricalElement heEscrowInformation( dstrRecord, AUDITTYPE::ASDETL, keyStringIDI );
         vectorHistorical.push_back( heEscrowInformation );
      }
   }
   else 
   {
      assert(0);
   }
   return GETCURRENTHIGHESTSEVERITY();
}



//******************************************************************************
void EntityProcess::setCurrentListItem(const GenericInterface *rpGICaller,
                                       const BFContainerId& idList, 
                                       const DString& strListItemKey)
{  
    TRACE_METHOD(CLASSNAME, I_("setCurrentListItem"));

    const BFDataGroupId &idDataGroup = getDataGroupId();
    AbstractProcess::setCurrentListItem(rpGICaller, idList, strListItemKey);

    if (idList == IFASTBP_PROC::ENTITY_LIST)
    {
        DString dstrEntityType, dstrEntityId;
        Entity *pEntity = NULL;
        BFAbstractCBO *rpPtr = getCBOItem(IFASTBP_PROC::ENTITY_LIST, idDataGroup);
        bool isDummyItem = isCurrentListItemDummy(const_cast < GenericInterface* >(rpGICaller), IFASTBP_PROC::ENTITY_LIST);

        rpPtr->getField(ifds::EntityType, dstrEntityType, idDataGroup);
        rpPtr->getField(ifds::EntityId, dstrEntityId, idDataGroup);

        dynamic_cast<DSTCWorkSession*>(getBFWorkSession())->getEntity(idDataGroup, dstrEntityId, pEntity);


        if (pEntity)
        {
            pEntity->setField(ifds::CurrentSelectedEntityType, dstrEntityType, idDataGroup);

            if (!isDummyItem)
            {
                pEntity->revalidateField(ifds::EmployeeClass, idDataGroup);
            }
        }
    }
}

//******************************************************************************
bool EntityProcess::doSend( GenericInterface* rpGICaller,const I_CHAR* szMessage )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_("doSend") );
   DString dstr (szMessage);

   if (dstr == I_("CallView490"))
   {
		const BFDataGroupId &idDataGroup = getDataGroupId();
		BFAbstractCBO *rpPtr = ( const_cast < EntityProcess *> ( this ) )->getCBOItem( IFASTBP_PROC::ENTITY_LIST, idDataGroup );
		EntitySearchIDValueValidation pEntitySearchIDValueValidation(*rpPtr);
		DString entityId, strEntityTypeFmt;
		Entity *pEntity = NULL;
		rpPtr->getField (ifds::EntityId, entityId, idDataGroup, false);
		dynamic_cast<DSTCWorkSession*>(getBFWorkSession())->getEntity (idDataGroup, entityId, pEntity);
		if(pEntity)
			strEntityTypeFmt= pEntity->getEntityType ();

		DString SrchEntType,
			SrchIdType,
			dstrErrDesc,
			dstrErrorCode,
			dstrEwi;     
		BFAbstractCBO *rpIdListPtr = ( const_cast < EntityProcess *> ( this ) )->getCBOItem( IFASTBP_PROC::ENTITY_IDS_LIST, idDataGroup );
		rpIdListPtr->getField (ifds::IdType, SrchIdType, idDataGroup, false); 

		if( pEntitySearchIDValueValidation.init( strEntityTypeFmt,
												 SrchIdType,
									             entityId
								               ) <= WARNING )
		{
			pEntitySearchIDValueValidation.getField(ifds::ErrorCode,dstrErrorCode,idDataGroup,false);
			pEntitySearchIDValueValidation.getField(ifds::EWI,dstrEwi,idDataGroup,false);     
		}

		if((dstrErrorCode == "2222") && (dstrEwi.stripAll().upperCase() == I_( "E" ) || dstrEwi.stripAll().upperCase() == I_( "W" )))
		{
			return true;
		}
	}
   return false; 

}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/EntityProcess.cpp-arc  $
 * 
 *    Rev 1.115   Jul 16 2012 12:21:28   dchatcha
 * P0179630 FN01 FATCA Project - Entity level.
 * 
 *    Rev 1.114   Jun 11 2012 15:04:18   if991250
 * INA: do not copy the laguage in cloning entities (we already have LanguageCode)
 * 
 *    Rev 1.113   May 01 2012 09:25:06   if991250
 * CPF - validating that the Registration agent has the appropriate tax type for the CPF account
 * 
 *    Rev 1.112   Apr 27 2012 16:35:04   if991250
 * CPF search for Reg agents
 * 
 *    Rev 1.111   Apr 27 2012 09:51:28   if991250
 * CPF - Account Setup & Settlement 
 * 
 *    Rev 1.110   Apr 16 2012 17:25:14   if991250
 * CPF Account Setup
 * 
 *    Rev 1.109   Apr 04 2012 20:32:46   wp040039
 * PETP0187485-Entity Maintenance
 * 
 *    Rev 1.108   Feb 06 2012 03:00:30   panatcha
 * IN2780013 - SOC Loan Number and Loan Type
 * 
 *    Rev 1.107   Jul 20 2011 17:51:48   dchatcha
 * P0180786 FN01 - TFSA Estate and Right of Rescission Tax Reporting.
 * 
 *    Rev 1.106   Jan 10 2011 03:52:46   wutipong
 * IN2311277 - Unable to access FDP accounts in Desktop
 * 
 *    Rev 1.105   May 06 2010 23:34:28   popescu
 * RESP/QESI fixes
 * 
 *    Rev 1.104   Mar 31 2010 08:19:02   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU
 * 
 *    Rev 1.103   Mar 29 2010 07:00:48   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU
 * 
 *    Rev 1.102   Mar 26 2010 09:30:22   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU
 * 
 *    Rev 1.101   Mar 23 2010 13:35:24   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU
 * 
 *    Rev 1.100   Mar 17 2010 06:27:00   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU
 * 
 *    Rev 1.99   Mar 12 2010 14:23:42   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU
 * 
 *    Rev 1.98   Oct 26 2009 18:22:26   popescu
 * Incident 1759954 - Entity Regression - clicking more then once on the Search button will not produce an error message - subsequent fix.
 * 
 *    Rev 1.97   30 Jul 2009 18:17:06   popescu
 * Incident 1759954 - Entity Regression - clicking more then once on the Search button will not produce an error message
 * 
 *    Rev 1.96   09 Mar 2009 11:51:38   popescu
 * Incident #1619677 - language field needs to be mandatory
 * 
 *    Rev 1.95   26 Jan 2009 12:07:36   popescu
 * Incident 1559745 - find clearing platform entities whether they were linked or not to an account - 
 * 
 *    Rev 1.94   23 Jan 2009 16:31:52   popescu
 * Incident 	1548019 - reset button on entitymaintenance dlg, BIC Code can be valid/invalid for entitytype 58
 * 
 *    Rev 1.93   16 Jan 2009 17:22:44   popescu
 * Incident 1544134 - various fixes
 * 
 *    Rev 1.92   Jan 12 2009 11:14:00   jankovii
 * IN 1549377 Estate and Death of Notification acct category can only be added by the system
 * 
 *    Rev 1.91   Dec 24 2008 10:14:22   jankovii
 * PET 142007 FN03 TFSA Phase 2.
 * 
 *    Rev 1.90   Dec 15 2008 02:19:58   phiwponp
 * PET0007773_FN01_MT535-MT536 Enhancement.
 * 
 *    Rev 1.89   24 Oct 2008 15:53:08   popescu
 * Incident 1447569 - do not copy Tax Jurisdiction Effective Date when cloning an entity
 * 
 *    Rev 1.88   Oct 14 2008 13:28:50   jankovii
 * IN 1431819 - When changing the death claim with the documents received and waive
 * 
 *    Rev 1.87   Sep 18 2008 15:57:28   jankovii
 * IN 1403772 - Acc status didn't change to Death after enter death date, etc.
 * 
 *    Rev 1.86   Aug 29 2008 14:29:42   jankovii
 * IN 1388930
 * 
 *    Rev 1.85   Jun 09 2008 07:44:04   daechach
 * IN # 1062864 - Allow nominee owner to be set up for client account
 * 
 *    Rev 1.84   Mar 13 2008 15:22:30   wongsakw
 * #INC 1175923 R83 Entity Sequence number for new nominee accounts.
 * 
 *    Rev 1.83   21 Aug 2007 11:07:14   popescu
 * GAP 6 - CIF allowed search by CIF/Access ID in the entity maintenance screen
 * 
 *    Rev 1.82   20 Aug 2007 16:33:58   popescu
 * Incident 981600  - skip copying CIF and AccessID if entity exists and is split
 * 
 *    Rev 1.81   Jul 27 2007 16:46:20   kovacsro
 * PET 2372 FN02 FDP-AIM KYC
 * 
 *    Rev 1.80   06 Jul 2007 14:43:04   popescu
 * PET 2363 GAP 6 CIF
 * 
 *    Rev 1.79   Jul 05 2007 16:50:14   popescu
 * Incident# 929895 - create a new entity if search by SIN is used
 * 
 *    Rev 1.78   27 Jun 2007 16:47:08   popescu
 * Incident# 929895 - enable search button and create a new entity if this is used.
 * 
 *    Rev 1.77   Jun 28 2006 17:32:46   popescu
 * Incident# 642164 - trigger validation for already exiting entities without a tax jurisd
 * 
 *    Rev 1.76   Nov 28 2005 09:57:34   zhengcon
 * Incident #457932
 * 
 *    Rev 1.75   Nov 24 2005 09:04:22   jankovii
 * PET1228_FN02 EU Saving Directive Phase 2
 * 
 *    Rev 1.74   Jun 09 2005 10:58:46   Fengyong
 * #Incident 285146 - fix error for copy and delete entity problem.
 * 
 *    Rev 1.73   Apr 18 2005 09:20:42   yingbaol
 * Incident 288575: add new search type:where use
 * 
 *    Rev 1.72   Apr 08 2005 11:49:18   yingbaol
 * Incident284670: fix effective date issue in NASA flow
 * 
 *    Rev 1.71   Mar 04 2005 17:12:56   yingbaol
 * PET1171,FN01:EUSD add Tax Jurisdiction
 * 
 *    Rev 1.70   Jun 03 2004 15:35:34   popescu
 * PTS 10030936, refreshed Shareholder if entity account owner or nominee account owner gets updated
 * 
 *    Rev 1.69   May 19 2004 11:49:48   popescu
 * PET1027 FN02 - Added Risk Level.  On doOk, refresh the accounts related to the updated Entities.
 * 
 *    Rev 1.68   Apr 23 2004 17:32:12   HERNANDO
 * PET1027 FN02 - Added Risk Level.  On doOk, refresh the accounts related to the updated Entities.
 * 
 *    Rev 1.67   Apr 19 2004 15:01:26   HERNANDO
 * PTS10028962 - Added Entity IDs.
 * 
 *    Rev 1.66   Feb 28 2004 16:06:26   HERNANDO
 * PET965 FN11 - Additional historical enhancement.
 * 
 *    Rev 1.65   Jan 02 2004 15:11:46   popescu
 * PTS 10025696, NASU flow crash 
 * 
 *    Rev 1.64   Nov 19 2003 11:04:08   popescu
 * Now, the warning dialog shows-up when user activates the EntityMaintenanceDialog from AccountDetails dialog,  if there are no updates, and if obviously the validation of the AcctEntityXRef object returns WARNING
 * 
 *    Rev 1.63   Nov 19 2003 10:19:36   linmay
 * added BirthPlace for SSB
 * 
 *    Rev 1.62   Oct 22 2003 11:45:50   YINGBAOL
 * PTS10022062
 * 
 *    Rev 1.61   Oct 14 2003 11:47:24   HERNANDO
 * PET859 FN08 / PET893 FN08 - Account name field enhancement and Salutation enhancement.
 * 
 *    Rev 1.60   Aug 28 2003 10:25:32   FENGYONG
 * set copy flag to link entity 
 * 
 *    Rev 1.59   Aug 25 2003 17:27:02   FENGYONG
 * set refresh flag to control if need to check can delete or not
 * 
 *    Rev 1.58   Aug 22 2003 14:51:28   FENGYONG
 * refresh spouse combox when open the xref dlg
 * 
 *    Rev 1.57   Aug 22 2003 11:29:38   FENGYONG
 * Perform search will copy owner and it's spouse two entity if the owner have a have spouse
 * 
 *    Rev 1.56   Aug 21 2003 19:52:06   FENGYONG
 * KYC Joint info enhancement
 * 
 *    Rev 1.55   Aug 01 2003 11:43:04   HERNANDO
 * Occupation Field enhancments.  Added OtherOccupation field.
 * 
 *    Rev 1.54   Apr 07 2003 18:02:34   ZHANGCEL
 * PTS Ticket 10010187: Bug fix to assure EntityIds can be deleted
 * 
 *    Rev 1.53   Mar 21 2003 17:38:50   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.52   Mar 12 2003 09:16:52   sanchez
 * Added addFieldDetails( ifds::Nationality, ..);  
 * 
 *    Rev 1.51   Dec 12 2002 12:01:56   FENGYONG
 * check ignore warning on ok2
 * 
 *    Rev 1.50   Nov 18 2002 10:55:28   PURDYECH
 * BFObjectKey changes.
 * 
 *    Rev 1.49   Oct 09 2002 23:53:10   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.48   Oct 08 2002 11:52:16   HSUCHIN
 * PTS 10010112 - condition frame fix
 * 
 *    Rev 1.47   Sep 04 2002 15:45:44   PURDYECH
 * Condition, comment and formatting cleanup
 * 
 *    Rev 1.46   Aug 29 2002 16:44:52   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.45   Aug 29 2002 12:54:18   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.44   Jul 16 2002 12:47:12   FENGYONG
 * Set EntityId to global
 * 
 *    Rev 1.43   Jul 12 2002 15:19:58   FENGYONG
 * add doPostOk
 * 
 *    Rev 1.42   Jun 14 2002 17:31:06   ZHANGCEL
 * PTS 10008207 bug fix
 * 
 *    Rev 1.41   Jun 02 2002 18:26:04   HSUCHIN
 * fix for birth date set field to pass in client locale.
 * 
 *    Rev 1.40   22 May 2002 18:24:12   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.39   30 Apr 2002 16:29:26   HERNANDO
 * Added addFieldDetails for EmployeeClass.
 * 
 *    Rev 1.38   27 Mar 2002 19:54:48   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.37   06 Dec 2001 16:24:24   KOVACSRO
 * In doOk() force the validation of AccountEntityList.
 * 
 *    Rev 1.36   21 Nov 2001 10:09:26   HSUCHIN
 * bug fix for duplicate entities during a cancel in NASU process
 * 
 *    Rev 1.35   Sep 12 2001 10:53:04   ZHANGCEL
 * Added logic for clone AccountEntityXref.
 * 
 *    Rev 1.34   09 Aug 2001 13:21:10   HSUCHIN
 * added support for Area code for the Canadian market
 * 
 *    Rev 1.33   07 Aug 2001 16:25:14   HSUCHIN
 * no change, just beautified
 * 
 *    Rev 1.32   03 Aug 2001 15:24:42   YINGZ
 * fix delete problem
 * 
 *    Rev 1.31   Jul 29 2001 15:07:56   YINGBAOL
 * move reset entity to CBO
 * 
 *    Rev 1.30   Jun 12 2001 14:15:34   DINACORN
 * Sync. up with SSB (1.24.1.0)
 * 
 *    Rev 1.29   Jun 04 2001 16:18:54   YINGBAOL
 * minor change
 * 
 *    Rev 1.28   Jun 04 2001 15:26:48   YINGBAOL
 * add doRefresh method
 * 
 *    Rev 1.27   18 May 2001 12:44:04   HSUCHIN
 * removed REPOSITORY_LIST (not used)
 * 
 *    Rev 1.26   15 May 2001 15:38:42   YINGZ
 * data group id clean up
 * 
 *    Rev 1.25   03 May 2001 14:05:22   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.24   Mar 29 2001 15:44:46   DINACORN
 * Used DSTCommonFunctions MARKET_IDS constants
 * 
 *    Rev 1.23   Feb 28 2001 15:44:02   YINGZ
 * support entityids
 * 
 *    Rev 1.22   Feb 21 2001 11:33:56   YINGZ
 * make api nasu work
 * 
 *    Rev 1.21   Feb 15 2001 16:08:02   DINACORN
 * EffectiveDate taken from AcctInfo in NASU
 * 
 *    Rev 1.20   Feb 12 2001 17:16:56   DINACORN
 * Change "MSDW - Japan" to "Japan"
 * 
 *    Rev 1.19   Feb 12 2001 15:50:12   YINGZ
 * add apinasu
 * 
 *    Rev 1.18   Jan 04 2001 11:55:44   ZHANGCEL
 * Remove getField for seqNumber in the getKeyForNewListItem()
 * 
 *    Rev 1.17   Dec 20 2000 10:05:22   ZHANGCEL
 * Added logic for CopyEntity requirement ( many changes in getKeyForNewListItem() and doSetField() )
 * 
 *    Rev 1.16   Dec 01 2000 14:49:52   ZHANGCEL
 * _acctnum was overriden when verifysearch screen is being called. do setparameter when entity search using IdValue and IdType  to ensure the next screen get the correct account number
 * 
 *    Rev 1.15   Dec 01 2000 11:50:32   KOVACSRO
 * Bug fixed for TaxJurisCode.
 * 
 *    Rev 1.14   Nov 29 2000 09:22:38   WINNIE
 * _acctnum was overriden when verifysearch screen is being called. do setparameter again to ensure the next screen get the correct account number
 * 
 *    Rev 1.13   Nov 13 2000 10:18:42   KOVACSRO
 * Added DuplicateSINcheck and fixed search for ID_VALUE.
 * 
 *    Rev 1.12   Oct 19 2000 19:32:06   WINNIE
 * search for SIN using Entity if EntityIDType =  '06' for Canaidan Market
 * 
 *    Rev 1.11   Oct 19 2000 14:35:32   VASILEAD
 * Implemented setData
 * 
 *    Rev 1.10   Oct 03 2000 17:04:32   YINGBAOL
 * fix new object problem
 * 
 *    Rev 1.9   Sep 26 2000 11:10:08   OLTEANCR
 * removed display of shr. nr. & acc. nr. for  NASU
 * 
 *    Rev 1.8   Aug 11 2000 15:57:58   YINGBAOL
 * change Effective date
 * 
 *    Rev 1.7   Aug 08 2000 13:32:12   YINGBAOL
 * fix RESP and Primary Beneficiary issues
 * 
 *    Rev 1.6   Aug 02 2000 15:32:00   BUZILA
 * "locale" changes
 * 
 *    Rev 1.5   Aug 01 2000 09:35:00   YINGBAOL
 * add delete logic
 * 
 *    Rev 1.4   Jul 28 2000 14:52:36   YINGBAOL
 * add new item logic
 * 
 *    Rev 1.3   Jul 26 2000 11:12:40   YINGBAOL
 * first version for C2
 * 
 *    Rev 1.2   Jun 08 2000 11:17:32   YINGZ
 * fix NASU dlg can close without lastname... problem
 * 
 *    Rev 1.1   Mar 09 2000 14:30:52   VASILEAD
 * Updated Entity screen for C2
 * 
 *    Rev 1.0   Feb 15 2000 10:59:34   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.48   Feb 02 2000 18:09:30   BUZILA
 * changes
 * 
 *    Rev 1.47   Feb 02 2000 10:32:00   BUZILA
 * xxx
 * 
 *    Rev 1.46   Jan 30 2000 17:53:12   VASILEAD
 * Limited the maximum number of characters allowed to input
 * 
 *    Rev 1.45   Jan 28 2000 15:08:06   VASILEAD
 * Fixed diplaying Kana addresses
 * 
 *    Rev 1.44   Jan 27 2000 14:13:28   VASILEAD
 * Fixes for final release
 * 
 *    Rev 1.43   Jan 23 2000 19:34:22   VASILEAD
 * Reset functionality
 * 
 *    Rev 1.42   Jan 23 2000 16:44:42   VASILEAD
 * Reset functionality
 * 
 *    Rev 1.41   Jan 21 2000 10:33:12   VASILEAD
 * implemented doGetFieldAttributes
 * 
 *    Rev 1.40   Jan 18 2000 18:38:12   VASILEAD
 * Updates fix
 * 
 *    Rev 1.39   Jan 13 2000 17:39:32   VASILEAD
 * Added support for catching errors
 * 
 *    Rev 1.38   Jan 12 2000 11:39:06   VASILEAD
 * Fixed compilation error 
 * 
 *    Rev 1.37   Jan 11 2000 14:35:42   VASILEAD
 * Fixed entity background search
 * 
 *    Rev 1.36   Jan 10 2000 16:15:06   VASILEAD
 * Added Joint information in Entity screen
 * 
 *    Rev 1.35   Jan 09 2000 14:58:26   VASILEAD
 * Corrected entity screen in the NASU
 * 
 *    Rev 1.34   Jan 06 2000 16:21:02   VASILEAD
 * Business edits for Entity screen
 * 
 *    Rev 1.33   Jan 03 2000 13:31:24   DT24433
 * removed addSubstitutes
 * 
 *    Rev 1.32   Dec 24 1999 10:31:04   VASILEAD
 * Fixed NASU flow
 * 
 *    Rev 1.31   Dec 23 1999 14:17:40   VASILEAD
 * Added validation for ids
 * 
 *    Rev 1.30   Dec 21 1999 10:42:10   VASILEAD
 * Added Entity list iteration based on the string keys and not on the ObjectKey, added background search support
 * 
 *    Rev 1.29   Dec 15 1999 10:44:06   VASILEAD
 * Implemented background search for Entity screen
 * 
 *    Rev 1.28   Dec 08 1999 14:00:22   POPESCUS
 *  the entity ids list is now a child list of entity being set in the object map
 * 
 *    Rev 1.27   Dec 06 1999 16:35:02   VASILEAD
 * Biult the keys at the CBO level
 * 
 *    Rev 1.26   Dec 01 1999 19:54:28   VASILEAD
 * Stuff
 * 
 *    Rev 1.25   Dec 01 1999 09:23:40   VASILEAD
 * NASU fixes
 * 
 *    Rev 1.24   Nov 29 1999 09:53:48   VASILEAD
 * Added business/edits for Entity screen
 * 
 *    Rev 1.23   Nov 25 1999 15:56:20   VASILEAD
 * Edits
 * 
 *    Rev 1.22   Nov 25 1999 09:27:58   VASILEAD
 * Entity business/screen edits
 * 
 *    Rev 1.21   Nov 23 1999 18:05:38   POPESCUS
 * NASU flow
 * 
 *    Rev 1.20   Nov 23 1999 15:35:14   VASILEAD
 * Added AuthorizedToTrade
 * 
 *    Rev 1.19   Nov 22 1999 15:20:08   BUZILA
 * added IDS substitution
 * 
 *    Rev 1.18   Nov 22 1999 14:25:50   VASILEAD
 * fixed getPtrForContainer
 * 
 *    Rev 1.17   Nov 21 1999 17:44:26   VASILEAD
 * Built key for Host Substitutes Values
 * 
 *    Rev 1.16   Nov 21 1999 14:58:12   VASILEAD
 * Z
 * 
 *    Rev 1.15   Nov 21 1999 13:35:54   VASILEAD
 * Added support for creating a new entity
 * 
 *    Rev 1.14   Nov 20 1999 13:14:42   VASILEAD
 * Worked on entity - account relationship
 * 
 *    Rev 1.13   Nov 07 1999 14:56:50   BUZILA
 * Changes
 * 
 *    Rev 1.12   Nov 02 1999 14:03:58   BUZILA
 * removed doOk and doCancel methods
 * 
 *    Rev 1.11   Oct 29 1999 11:30:14   BUZILA
 * changing WorkSessionDetails into a BFBase descendant
 * 
 *    Rev 1.10   27 Oct 1999 13:21:44   ZARKHINE
 * Nested List Functionality added
 * 
 *    Rev 1.9   Aug 31 1999 14:23:30   DT24433
 * changed doGetField parms
 * 
 *    Rev 1.8   Aug 31 1999 14:41:48   YINGBAOL
 * addSubstituteList
 * 
 *    Rev 1.7   Aug 25 1999 08:21:50   DT24433
 * Finished FieldDetails changes
 * 
 *    Rev 1.6   Aug 12 1999 14:18:10   DT24433
 * changes for inc2 field & CBO management
 * 
 *    Rev 1.5   Jul 28 1999 12:04:36   BUZILA
 * added to EntityProcess the getField(...) method 
 * 
 *    Rev 1.4   Jul 27 1999 15:03:00   BUZILA
 * First M2 revision
 * 
 *    Rev 1.3   Jul 20 1999 11:14:02   VASILEAD
 * New conditions update
 * 
 *    Rev 1.2   Jul 16 1999 09:36:08   YINGBAOL
 * Add Home Fax  Field
 * 
 *    Rev 1.1   Jul 08 1999 10:02:00   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
