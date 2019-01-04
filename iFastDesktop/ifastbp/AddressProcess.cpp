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
//    Copyright 2005 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : AddressProcess.cpp
// ^AUTHOR : Yingbao  Li
// ^DATE   : 11/05/1999
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : AddressProcess
//    This class manages the address book process.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "addressprocess.hpp"
#include <ifastcbo\accountentityxref.hpp>
#include <ifastcbo\accountmailinginfo.hpp>
#include <ifastcbo\accountmailinglist.hpp>
#include <ifastcbo\addressentitylist.hpp>
#include <ifastcbo\entityaddress.hpp>
#include <ifastcbo\AcctMailingOverrideList.hpp>
#include <ifastcbo\addresslist.hpp>
#include <ifastcbo\provincelist.hpp>
#include "addressprocessincludes.h"
#include <ifastcbo\entity.hpp>
#include <ifastcbo\entitylist.hpp>
#include <ifastcbo\FundCommGroupList.hpp>
#include <ifastdataimpl\dse_dstcglob_vw.hpp>
#include <ifastcbo\mfaccount.hpp>
#include "searchprocessincludes.h"
#include <ifastcbo\shareholder.hpp>
#include <ifastdataimpl\dse_dstc0043_vw.hpp>
#include <ifastdataimpl\dse_dstc0042_vw.hpp>
#include <ifastdataimpl\dse_dstc0050_vw.hpp>
#include <ifastdataimpl\dse_dstc0071_vw.hpp>
#include <ifastdataimpl\dse_dstc0069_vw.hpp>
#include <ifastdataimpl\dse_dstc0072_req.hpp>
#include <ifastdataimpl\dse_dstc0080_req.hpp>
#include <ifastdataimpl\dse_dstc0113_vw.hpp>
#include <ifastdataimpl\dse_dstc0214_vw.hpp>
#include <ifastdataimpl\dse_dstc0214_req.hpp>
#include <ifastdataimpl\dse_dstc0149_vw.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\MgmtCoOptions.hpp>

#include "nasuprocessincludes.h"
#include <ifastcbo\address.hpp>
#include <ifastcbo\EntityAddressMailingList.hpp>
#include <ifastcbo\accountentityxrefobject.hpp>
#include <ifastcbo\WorkSessionEntityList.hpp>

#include "mfcaninterprocparam.hpp"

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_ADDRESSES;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ADDRESSES;
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_ADDRESS_SELECTION; 
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< AddressProcess > processCreator( CMD_BPROC_ADDRESSES );
//CP20020416

namespace
{
   // Trace literals
   const I_CHAR *CLASSNAME = I_( "AddressProcess" );
   const I_CHAR *LIST_KEY  = I_( "ListKey" );
   const I_CHAR *Y_STRING  = I_( "Y" );
   const I_CHAR *N_STRING  = I_( "N" );
   const I_CHAR *EntityId  = I_( "EntityId" );

   const I_CHAR *SPACE_STRING  = I_( " " ); 
   const DString EMPTY_STRING;
   const I_CHAR *pINQUIRYONLY  = I_( "InquiryOnly" );

}

namespace ADDRLIT
{
   const I_CHAR * const ACCOUNT_NUM          = I_( "AccountNum" );
   const I_CHAR * const SHAREHOLDER_NUM      = I_( "ShareholderNum" );
   const I_CHAR * const SETTLEMENT           = I_( "Settlement" );
   const I_CHAR * const ADDRESS_KEY          = I_( "AddressKey" );   
   const I_CHAR * const ENTITY_ID            = I_( "EntityID" );

   const I_CHAR * const ENTITY_TYPE          = I_( "EntityType" );
   const I_CHAR * const SEQ_NUMBER           = I_( "EntitySeqNumber" );

   const I_CHAR * const ADDRESS_CODE         = I_( "AddressCode" );
   const I_CHAR * const SEARCH_SHAREHOLDER   = I_( "SearchShareholder" );
   const I_CHAR * const FROM_ENTITY          = I_( "FromEntity" );
   const I_CHAR * const RETMAIL_TAB          = I_( "ReturnMailTab" );

   const I_CHAR * const UPDATE_TAX_JURIS     = I_( "UpdShrTaxJuris" );
   const I_CHAR * const UPDATE_PROV_RES      = I_( "UpdShrProvRes" );
   
   const BFFieldId REG_ADDR_READ_ONLY(101);
   const BFTextFieldId RetMailTab(190000L, I_("RetMailTab"));
}

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
   extern const long BP_ERR_ENTITY_ADDRESS_LIST_INVALID;

}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId AcctMailingOverrideHeading;
   extern CLASS_IMPORT const BFTextFieldId Mail;
   extern CLASS_IMPORT const BFTextFieldId LEmail;
   extern CLASS_IMPORT const BFTextFieldId Fax;
   extern CLASS_IMPORT const BFTextFieldId CD;
   extern CLASS_IMPORT const BFTextFieldId OnHold;
   extern CLASS_IMPORT const BFTextFieldId ContributionOnHold;
   extern CLASS_IMPORT const BFTextFieldId UnclmRetMailStage;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   
   extern CLASS_IMPORT const BFTextFieldId UpdShrProvRes;
   extern CLASS_IMPORT const BFTextFieldId UpdShrTaxJuris;
   extern CLASS_IMPORT const BFTextFieldId IsNewOrUpdate;
   extern CLASS_IMPORT const BFTextFieldId TaxJurisUpdateOpt;
   extern CLASS_IMPORT const BFTextFieldId VerifyStat;
   extern CLASS_IMPORT const BFTextFieldId GoodBad;
   extern CLASS_IMPORT const BFTextFieldId StmtFrequency;
   extern CLASS_IMPORT const BFTextFieldId StmtFreqDefault;
   extern CLASS_IMPORT const BFTextFieldId StmtFreqList;
   extern CLASS_IMPORT const BFTextFieldId StmtFrequencyDisabled;
   extern CLASS_IMPORT const BFTextFieldId DocumentMail; 
   extern CLASS_IMPORT const BFTextFieldId DocTypeMailMapping;
   extern CLASS_IMPORT const BFTextFieldId ListDocType;
   extern CLASS_IMPORT const BFTextFieldId MailHouseholdID;
}

namespace AUDITTYPE
{
   extern CLASS_IMPORT I_CHAR * const SHADDR;
}

const BFFieldId fieldsUncliamedProperty[]=
{
   ifds::RetMailFlag,
   ifds::RetMailDate,
   ifds::RetMailReasonCode,
   ifds::UnclmStmtDate,
   ifds::UnclmRemitDate,
   ifds::UnclmComment,
   ifds::StageStampDate,
   ifds::UnclmRetMailStage,
   ifds::StageAssignBy,
};

const BFFieldId fieldsRegAddr[]=
{
   ifds::RegAddrCode,
};

static const int numFieldsUncliamedProperty = sizeof (fieldsUncliamedProperty) / sizeof (BFFieldId);
static const int numFieldsRegAddr = sizeof (fieldsRegAddr) / sizeof (BFFieldId);

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ADDR_TAX_JURIS_UPDATE;
//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319AddressProcess::AddressProcess() : 
AddressProcess::AddressProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _rpChildGI( NULL )
, _pAccountEntityXref( NULL )
, _pAddressList( NULL )
, _pAccountMailingList( NULL )
, _pAddressEntityList( NULL )
, _pWorkSessionEntityList( NULL )
, _pProvinceList( NULL )
, _strFromSearch( NULL_STRING )
{
   TRACE_CONSTRUCTOR( CLASSNAME, I_( "AddressProcess" ) );

   addContainer( IFASTBP_PROC::ENTITY_LIST,                true, 
                  BF::NullContainerId,       true );   // not updatable for currently we use HLLAPI

   addContainer( IFASTBP_PROC::ADDRESSES_LIST,             true, BF::NullContainerId,
                  true,  I_( "Address" ) );   
   addContainer( IFASTBP_PROC::ENTITY_ADDRESS_LIST,        true, BF::NullContainerId,       
                  true,  I_("Entity_Address") );   
   addContainer( IFASTBP_PROC::PROVINCE_LIST,              true, IFASTBP_PROC::ENTITY_ADDRESS_LIST, 
                  false, I_( "ProvinceList" ) );
   addContainer( IFASTBP_PROC::SHAREHOLDER_LIST,          false, BF::NullContainerId,       
                  true );   
   addContainer( IFASTBP_PROC::ACCOUNT_MAILING_LIST,       true, BF::NullContainerId,       
                  true,  I_("Mailing") );
   addContainer( IFASTBP_PROC::ACCT_MAILING_OVERRIDE_LIST, true, BF::NullContainerId,       
                  true,  I_("MailingOverride") );
   addContainer( IFASTBP_PROC::ENTITY_MAILING_LIST,        true, IFASTBP_PROC::ENTITY_LIST, 
                  true,  I_( "EntityMailing" ) ); 

   // Used for grid titles
   addSubstituteList(ifds::AddressMailingHeadingSet);  
   // Used for grid combo
   addSubstituteList(ifds::HoldMail);
   addSubstituteList(ifds::AcctMailingOverrideHeading);  
   addSubstituteList(ifds::StmtFrequency);

   addFieldDetails( ifds::AddrCode,             IFASTBP_PROC::ADDRESSES_LIST );
   addFieldDetails( ifds::AddrCodeDesc,         IFASTBP_PROC::ADDRESSES_LIST );
   addFieldDetails( ifds::Name1,                IFASTBP_PROC::ADDRESSES_LIST );
   addFieldDetails( ifds::Name2,                IFASTBP_PROC::ADDRESSES_LIST );
   addFieldDetails( ifds::AddrLine1,            IFASTBP_PROC::ADDRESSES_LIST );
   addFieldDetails( ifds::kAddrLine1,           IFASTBP_PROC::ADDRESSES_LIST );
   addFieldDetails( ifds::kAddrLine2,           IFASTBP_PROC::ADDRESSES_LIST );
   addFieldDetails( ifds::kAddrLine3,           IFASTBP_PROC::ADDRESSES_LIST );
   addFieldDetails( ifds::kAddrLine4,           IFASTBP_PROC::ADDRESSES_LIST );
   addFieldDetails( ifds::kAddrLine5,           IFASTBP_PROC::ADDRESSES_LIST );
   addFieldDetails( ifds::AddrLine2,            IFASTBP_PROC::ADDRESSES_LIST );
   addFieldDetails( ifds::AddrLine3,            IFASTBP_PROC::ADDRESSES_LIST );
   addFieldDetails( ifds::AddrLine4,            IFASTBP_PROC::ADDRESSES_LIST );
   addFieldDetails( ifds::AddrLine5,            IFASTBP_PROC::ADDRESSES_LIST );
   addFieldDetails( ifds::PostalCode,           IFASTBP_PROC::ADDRESSES_LIST );
   addFieldDetails( ifds::CountryCode,          IFASTBP_PROC::ADDRESSES_LIST );
   addFieldDetails( ifds::City,                 IFASTBP_PROC::ADDRESSES_LIST );
   addFieldDetails( ifds::CountryName,          IFASTBP_PROC::ADDRESSES_LIST );
   addFieldDetails( ifds::AddrStatus,           IFASTBP_PROC::ADDRESSES_LIST );
   addFieldDetails( ifds::Province,             IFASTBP_PROC::ADDRESSES_LIST );
   addFieldDetails( ifds::RegAddrCode,          IFASTBP_PROC::ADDRESSES_LIST );
   addFieldDetails( ifds::RetMailFlag,          IFASTBP_PROC::ADDRESSES_LIST );
   addFieldDetails( ifds::RetMailDate,          IFASTBP_PROC::ADDRESSES_LIST );
   addFieldDetails( ifds::AddressFileRid,       IFASTBP_PROC::ADDRESSES_LIST );
   addFieldDetails( ifds::SkipValidate,         IFASTBP_PROC::ADDRESSES_LIST );
   addFieldDetails( ifds::DskPCLookEnb,         IFASTBP_PROC::ADDRESSES_LIST );
   addFieldDetails( ifds::PCLookupEnabled,      IFASTBP_PROC::ADDRESSES_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::VerifyStat,           IFASTBP_PROC::ADDRESSES_LIST );

   addFieldDetails( ifds::RegAddr,     IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails( ifds::DivConfAddr,   IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails( ifds::DivChqAddr,    IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails( ifds::TxnConfAddr,   IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails( ifds::DupConfAddr,   IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails( ifds::StmtAddr,    IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails( ifds::DupStmtAddr,   IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails( ifds::CertAddr,    IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails( ifds::TaxAddr,     IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails( ifds::LetAddr,     IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails( ifds::BenAddr,     IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails( ifds::NFCAddr,     IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails( ifds::AccountNum,    IFASTBP_PROC::ACCOUNT_MAILING_LIST );

   addFieldDetails( ifds::RegOnHold,   IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails( ifds::DivConfOnHold, IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails( ifds::DivChqOnHold,  IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails( ifds::TxnConfOnHold, IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails( ifds::DupConfOnHold, IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails( ifds::StmtOnHold,    IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails( ifds::DupStmtOnHold, IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails( ifds::CertOnHold,    IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails( ifds::TaxOnHold,   IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails( ifds::LetOnHold,   IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails( ifds::BenOnHold,   IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails( ifds::NFConHold,   IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails( ifds::ContrAddr,   IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails( ifds::ContrHold,   IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails( ifds::AnnlRptsAddr,  IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails( ifds::AnnlRptsHold,  IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails( ifds::ProspAddr,   IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails( ifds::ProspHold,   IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails( ifds::SemiAnnualAddr,  IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails( ifds::SemiAnnualOnHold,IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails( ifds::SATxnConfCode, IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails( ifds::SATxnConfDesc,   IFASTBP_PROC::ACCOUNT_MAILING_LIST ); 
   addFieldDetails( ifds::SADivConfCode,   IFASTBP_PROC::ACCOUNT_MAILING_LIST ); 
   addFieldDetails( ifds::SADivConfDesc,   IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails( ifds::SALettersCode,   IFASTBP_PROC::ACCOUNT_MAILING_LIST ); 
   addFieldDetails( ifds::SALettersDesc,   IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails( ifds::DupConfCopies,   IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails( ifds::DupStmtCopies,   IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails( ifds::Yes_NO,      IFASTBP_PROC::ACCOUNT_MAILING_LIST );   
   addFieldDetails(ifds::TaxSuppress,    IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::TaxWaive,     IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::TaxMail,      IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::TaxFax,     IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::TaxCD,      IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::TaxEmail,     IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::LetSuppress,    IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::LetWaive,     IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::LetMail,      IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::LetFax,     IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::LetCD,      IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::LetEmail,     IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::CertSuppress,   IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::CertWaive,    IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::CertMail,     IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::CertFax,      IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::CertCD,     IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::CertEmail,    IFASTBP_PROC::ACCOUNT_MAILING_LIST );

   addFieldDetails( ifds::DivConfSuppress, IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails( ifds::DivConfWaive,  IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails( ifds::DivConfMail,   IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails( ifds::DivConfFax,    IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails( ifds::DivConfCD,   IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails( ifds::DivConfEmail,  IFASTBP_PROC::ACCOUNT_MAILING_LIST );

   addFieldDetails(ifds::DivChqSuppress, IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::DivChqWaive,    IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::DivChqMail,   IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::DivChqFax,    IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::DivChqCD,     IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::DivChqEmail,    IFASTBP_PROC::ACCOUNT_MAILING_LIST );

   addFieldDetails( ifds::ContrSuppress,   IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails( ifds::ContrWaive,    IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails( ifds::ContrMail,   IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails( ifds::ContrFax,    IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails( ifds::ContrCD,     IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails( ifds::ContrEmail,    IFASTBP_PROC::ACCOUNT_MAILING_LIST );

   addFieldDetails(ifds::RegSuppress,    IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::RegWaive,     IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::RegMail,      IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::RegFax,     IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::RegCD,      IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::RegEmail,     IFASTBP_PROC::ACCOUNT_MAILING_LIST );

   addFieldDetails(ifds::AnnlRptsSuppress, IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::AnnlRptsWaive,  IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::AnnlRptsMail,   IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::AnnlRptsFax,    IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::AnnlRptsCD,   IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::AnnlRptsEmail,  IFASTBP_PROC::ACCOUNT_MAILING_LIST );

   addFieldDetails(ifds::ProspSuppress,  IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::ProspWaive,   IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::ProspMail,    IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::ProspFax,     IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::ProspCD,      IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::ProspEmail,   IFASTBP_PROC::ACCOUNT_MAILING_LIST );

   addFieldDetails(ifds::BenSuppress,     IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::BenWaive,        IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::BenMail,         IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::BenFax,          IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::BenCD,           IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::BenEmail,        IFASTBP_PROC::ACCOUNT_MAILING_LIST );

   addFieldDetails(ifds::StmtSuppress,    IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::StmtWaive,       IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::StmtMail,        IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::StmtFax,         IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::StmtCD,          IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::StmtEmail,       IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::StmtFrequency,			IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::StmtFreqDefault,		IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::StmtFreqList,			IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::StmtFrequencyDisabled, IFASTBP_PROC::ACCOUNT_MAILING_LIST );

   addFieldDetails(ifds::DupStmtSuppress, IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::DupStmtWaive,    IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::DupStmtMail,     IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::DupStmtFax,      IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::DupStmtCD,       IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::DupStmtEmail,    IFASTBP_PROC::ACCOUNT_MAILING_LIST );

   addFieldDetails(ifds::NFConfSuppress,  IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::NFConfWaive,     IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::NFConfMail,      IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::NFConfFax,       IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::NFConfCD,        IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::NFConfEmail,     IFASTBP_PROC::ACCOUNT_MAILING_LIST );

   addFieldDetails(ifds::TxnConfSuppress, IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::TxnConfWaive,    IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::TxnConfMail,     IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::TxnConfFax,      IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::TxnConfCD,       IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::TxnConfEmail,    IFASTBP_PROC::ACCOUNT_MAILING_LIST );

   addFieldDetails(ifds::DupConfSuppress, IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::DupConfWaive,    IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::DupConfMail,     IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::DupConfFax,      IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::DupConfCD,       IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::DupConfEmail,    IFASTBP_PROC::ACCOUNT_MAILING_LIST );

   addFieldDetails(ifds::SemiAnnualSuppress, IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::SemiAnnualWaive,    IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::SemiAnnualMail,     IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::SemiAnnualFax,      IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::SemiAnnualCD,       IFASTBP_PROC::ACCOUNT_MAILING_LIST );
   addFieldDetails(ifds::SemiAnnualEmail,    IFASTBP_PROC::ACCOUNT_MAILING_LIST );

   addFieldDetails(ifds::DocumentMail,     IFASTBP_PROC::ACCOUNT_MAILING_LIST );

   addFieldDetails(ifds::TaxEpost,                     IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::LetEpost,                     IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::CertEpost,                     IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::DivConfEpost,                  IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::DivChqEpost,                  IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::ContrEPost,                  IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::RegEpost,                     IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::AnnlRptsEpost,               IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::ProspEpost,                  IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::BenEpost,                     IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::StmtEpost,                     IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::DupStmtEpost,                  IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::NFConfEpost,                  IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::TxnConfEpost,                  IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::DupConfEpost,                  IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::SemiAnnualEpost,               IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::ContributionSuppress,         IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::ContributionWaive,            IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::ContributionMail,            IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::ContributionFax,               IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::ContributionCD,               IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::ContributionEmail,            IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::ContributionEpost,            IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::ContributionAddr,            IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::ContributionOnHold,            IFASTBP_PROC::ACCOUNT_MAILING_LIST);

   addFieldDetails(ifds::SmAnnlMRFPAddr,        IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::AnnlMRFPAddr,          IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::AnnlMRFPHold,          IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::SmAnnlMRFPHold,        IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::RegAuth,               IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::DivConfAuth,           IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::DivChqAuth,            IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::TxnConfAuth,           IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::DupConfAuth,           IFASTBP_PROC::ACCOUNT_MAILING_LIST);
   addFieldDetails(ifds::StmtAuth,              IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::DupStmtAuth,           IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::CertAuth,              IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::TaxAuth,               IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::LetAuth,               IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::BenAuth,               IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::NFConAuth,             IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::SmAnnlRptsAuth,        IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::ProspAuth,             IFASTBP_PROC::ACCOUNT_MAILING_LIST);
   addFieldDetails(ifds::ContrAuth,             IFASTBP_PROC::ACCOUNT_MAILING_LIST);
   addFieldDetails(ifds::ContributionAuth,      IFASTBP_PROC::ACCOUNT_MAILING_LIST);   
   addFieldDetails(ifds::AnnlRptsAuth,          IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::AnnlMRFPAuth,          IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::SmAnnlMRFPAuth,        IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::AnnlMRFPSuppress,      IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::AnnlMRFPWaive,         IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::AnnlMRFPMail,          IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::AnnlMRFPFax,           IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::AnnlMRFPCD,            IFASTBP_PROC::ACCOUNT_MAILING_LIST);
   addFieldDetails(ifds::AnnlMRFPEmail,         IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::AnnlMRFPEpost,         IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::SmAnnlMRFPSuppress,    IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::SmAnnlMRFPWaive,       IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::SmAnnlMRFPMail,        IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::SmAnnlMRFPFax,         IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::SmAnnlMRFPCD,          IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::SmAnnlMRFPEmail,       IFASTBP_PROC::ACCOUNT_MAILING_LIST); 
   addFieldDetails(ifds::SmAnnlMRFPEpost,       IFASTBP_PROC::ACCOUNT_MAILING_LIST);

   // use as look up table for rowkey for mail column
   addFieldDetails(ifds::DocTypeMailMapping,    IFASTBP_PROC::ACCOUNT_MAILING_LIST);
   addFieldDetails(ifds::ListDocType,           IFASTBP_PROC::ACCOUNT_MAILING_LIST, SUBCLASS_PROCESS );

   addFieldDetails( ifds::Confirm,              IFASTBP_PROC::ADDRESSES_LIST );
   addFieldDetails( ifds::EffectiveDate,        IFASTBP_PROC::ADDRESSES_LIST );
   addFieldDetails( ifds::StopDate,             IFASTBP_PROC::ADDRESSES_LIST );
   addFieldDetails( ifds::ModDate,              IFASTBP_PROC::ADDRESSES_LIST );
   addFieldDetails( ifds::ProcessDate,          IFASTBP_PROC::ADDRESSES_LIST );
   addFieldDetails( ifds::Username,             IFASTBP_PROC::ADDRESSES_LIST );
   addFieldDetails( ifds::ModUser,              IFASTBP_PROC::ADDRESSES_LIST );
   addFieldDetails( ifds::Salutation,           IFASTBP_PROC::ADDRESSES_LIST );
   addFieldDetails( ifds::ProvinceCanadaUS,     IFASTBP_PROC::ADDRESSES_LIST );

   addFieldDetails( ifds::Name1,                IFASTBP_PROC::SHAREHOLDER_LIST    );
   addFieldDetails( ifds::Name2,                IFASTBP_PROC::SHAREHOLDER_LIST    );
   addFieldDetails( ifds::MailHouseholdID,      IFASTBP_PROC::SHAREHOLDER_LIST, SUBCLASS_PROCESS );

   addFieldDetails( ifds::EffectiveDate, IFASTBP_PROC::ENTITY_ADDRESS_LIST ); 
   addFieldDetails( ifds::ProcessDate,   IFASTBP_PROC::ENTITY_ADDRESS_LIST );
   addFieldDetails( ifds::Username,      IFASTBP_PROC::ENTITY_ADDRESS_LIST );
   addFieldDetails( ifds::ModUser,       IFASTBP_PROC::ENTITY_ADDRESS_LIST );
   addFieldDetails( ifds::ModDate,       IFASTBP_PROC::ENTITY_ADDRESS_LIST );
   addFieldDetails( ifds::AddrCode,      IFASTBP_PROC::ENTITY_ADDRESS_LIST );
   addFieldDetails( ifds::AddrDesc,      IFASTBP_PROC::ENTITY_ADDRESS_LIST );
   addFieldDetails( ifds::AddrId,        IFASTBP_PROC::ENTITY_ADDRESS_LIST );
   addFieldDetails( ifds::AddrLine1,     IFASTBP_PROC::ENTITY_ADDRESS_LIST );
   addFieldDetails( ifds::AddrLine2,     IFASTBP_PROC::ENTITY_ADDRESS_LIST );
   addFieldDetails( ifds::AddrLine3,     IFASTBP_PROC::ENTITY_ADDRESS_LIST );
   addFieldDetails( ifds::City,          IFASTBP_PROC::ENTITY_ADDRESS_LIST );
   addFieldDetails( ifds::Province,      IFASTBP_PROC::ENTITY_ADDRESS_LIST );
   addFieldDetails( ifds::ProvinceName,  IFASTBP_PROC::ENTITY_ADDRESS_LIST );
   addFieldDetails( ifds::Country,       IFASTBP_PROC::ENTITY_ADDRESS_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::CountryName,   IFASTBP_PROC::ENTITY_ADDRESS_LIST ); 
   addFieldDetails( ifds::PostalCode,    IFASTBP_PROC::ENTITY_ADDRESS_LIST );
   addFieldDetails( ifds::HoldMail,      IFASTBP_PROC::ENTITY_ADDRESS_LIST );
   addFieldDetails( ifds::RetMailFlag,          IFASTBP_PROC::ENTITY_ADDRESS_LIST );
   addFieldDetails( ifds::RetMailDate,          IFASTBP_PROC::ENTITY_ADDRESS_LIST );
   addFieldDetails( ifds::RetMailReasonCode,    IFASTBP_PROC::ENTITY_ADDRESS_LIST );
   addFieldDetails( ifds::UnclmComment,         IFASTBP_PROC::ENTITY_ADDRESS_LIST );

   addFieldDetails( ifds::LastName,      IFASTBP_PROC::ENTITY_LIST ); 
   addFieldDetails( ifds::FirstName,     IFASTBP_PROC::ENTITY_LIST ); 
   addFieldDetails( ifds::Salutation,    IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::EntityType,    IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::SeqNumber,     IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::AccountNum,    IFASTBP_PROC::ENTITY_LIST );

   addFieldDetails( ifds::EntityId,       IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::EntityTypeDesc, IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::AddrCode,       IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::AcctEntityRid,  IFASTBP_PROC::ENTITY_LIST );
   addFieldDetails( ifds::DocumentType,   IFASTBP_PROC::ENTITY_MAILING_LIST );
   addFieldDetails( ifds::EntityAddrCode, IFASTBP_PROC::ENTITY_MAILING_LIST );
   addFieldDetails( ifds::Suppress,       IFASTBP_PROC::ENTITY_MAILING_LIST );
   //addFieldDetails( ifds::DeliveryOption, IFASTBP_PROC::ENTITY_MAILING_LIST );
   addFieldDetails( ifds::Yes_NO,         IFASTBP_PROC::ENTITY_MAILING_LIST );
   addFieldDetails( ifds::EntityType,     IFASTBP_PROC::ENTITY_MAILING_LIST );
   addFieldDetails( ifds::EntityTypeSeq,  IFASTBP_PROC::ENTITY_MAILING_LIST );
   addFieldDetails( ifds::Consent,        IFASTBP_PROC::ENTITY_MAILING_LIST );
   addFieldDetails( ifds::Mail,           IFASTBP_PROC::ENTITY_MAILING_LIST );
   addFieldDetails( ifds::LEmail,         IFASTBP_PROC::ENTITY_MAILING_LIST );
   addFieldDetails( ifds::Fax,            IFASTBP_PROC::ENTITY_MAILING_LIST );
   addFieldDetails( ifds::CD,             IFASTBP_PROC::ENTITY_MAILING_LIST );
   addFieldDetails( ifds::EPost,          IFASTBP_PROC::ENTITY_MAILING_LIST );
   addFieldDetails( ifds::OnHold,         IFASTBP_PROC::ENTITY_MAILING_LIST );
   addFieldDetails( ifds::AuthCode,       IFASTBP_PROC::ENTITY_MAILING_LIST );
   addFieldDetails( ifds::DeliveryOption, IFASTBP_PROC::ENTITY_MAILING_LIST );
   addFieldDetails( ifds::DelOptnRecId,   IFASTBP_PROC::ENTITY_MAILING_LIST );
//the dummy field
   addFieldDetails( ADDRLIT::REG_ADDR_READ_ONLY, BF::NullContainerId, SUBCLASS_PROCESS, I_( "MailRegAddr" ) );
   addFieldDetails( ifds::OPDeliveryOption, BF::NullContainerId, SUBCLASS_PROCESS  );
   addFieldDetails( ifds::OPDeliveryMethods, BF::NullContainerId, SUBCLASS_PROCESS  );
   addFieldDetails( ifds::CnsntToWaive, BF::NullContainerId, SUBCLASS_PROCESS  );
   addFieldDetails( ifds::ShrAddressFormat, BF::NullContainerId, SUBCLASS_PROCESS  );
//   addFieldDetails( ifds::DeliveryOption, IFASTBP_PROC::ACCT_MAILING_OVERRIDE_LIST );
   addFieldDetails( ifds::DocumentType,IFASTBP_PROC::ACCT_MAILING_OVERRIDE_LIST );
   addFieldDetails( ifds::EntityAddrCode,IFASTBP_PROC::ACCT_MAILING_OVERRIDE_LIST );
   addFieldDetails( ifds::FundGroup,IFASTBP_PROC::ACCT_MAILING_OVERRIDE_LIST );   
   addFieldDetails( ifds::Suppress,IFASTBP_PROC::ACCT_MAILING_OVERRIDE_LIST );
   addFieldDetails( ifds::Consent,IFASTBP_PROC::ACCT_MAILING_OVERRIDE_LIST );
   addFieldDetails( ifds::Mail,IFASTBP_PROC::ACCT_MAILING_OVERRIDE_LIST );
   addFieldDetails( ifds::LEmail,IFASTBP_PROC::ACCT_MAILING_OVERRIDE_LIST );
   addFieldDetails( ifds::Fax,IFASTBP_PROC::ACCT_MAILING_OVERRIDE_LIST );
   addFieldDetails( ifds::CD,IFASTBP_PROC::ACCT_MAILING_OVERRIDE_LIST );
   addFieldDetails( ifds::EPost,IFASTBP_PROC::ACCT_MAILING_OVERRIDE_LIST );
   addFieldDetails( ifds::OnHold,          IFASTBP_PROC::ACCT_MAILING_OVERRIDE_LIST );
   addFieldDetails( ifds::AuthCode,   IFASTBP_PROC::ACCT_MAILING_OVERRIDE_LIST );
   addFieldDetails( ifds::DeliveryOption,   IFASTBP_PROC::ACCT_MAILING_OVERRIDE_LIST );
   addFieldDetails( ifds::DelOptnRecId,     IFASTBP_PROC::ACCT_MAILING_OVERRIDE_LIST );
//   addFieldDetails( ifds::OnHold,IFASTBP_PROC::ACCT_MAILING_OVERRIDE_LIST, SUBCLASS_PROCESS );
   addFieldDetails( ifds::MailingByFundGroup,BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( ADDRLIT::SALUTATION_EDIT, BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( ifds::AcctMstrRid, BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( ADDRLIT::CREATE_MAIL_OVERRIDE,IFASTBP_PROC::ACCT_MAILING_OVERRIDE_LIST,
                              SUBCLASS_PROCESS ); 
   addFieldDetails( ifds::RetMailReasonCode, IFASTBP_PROC::ADDRESSES_LIST );
   addFieldDetails( ifds::UnclmStmtDate,     IFASTBP_PROC::ADDRESSES_LIST );
   addFieldDetails( ifds::UnclmRemitDate,    IFASTBP_PROC::ADDRESSES_LIST );
   addFieldDetails( ifds::UnclmComment,      IFASTBP_PROC::ADDRESSES_LIST );
   addFieldDetails( ifds::StageStampDate,    IFASTBP_PROC::ADDRESSES_LIST );
   addFieldDetails( ifds::UnclmRetMailStage, IFASTBP_PROC::ADDRESSES_LIST  );
   addFieldDetails( ifds::StageAssignBy,     IFASTBP_PROC::ADDRESSES_LIST  );

   addFieldDetails( ADDRLIT::RetMailTab,     BF::NullContainerId, SUBCLASS_PROCESS );

   addFieldDetails( ifds::UpdShrProvRes,     IFASTBP_PROC::ADDRESSES_LIST );
   addFieldDetails( ifds::UpdShrTaxJuris,    IFASTBP_PROC::ADDRESSES_LIST );
   addFieldDetails( ifds::IsNewOrUpdate,     BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( ifds::AcctDesignation,   BF::NullContainerId, SUBCLASS_PROCESS );
}

//******************************************************************************
AddressProcess::~AddressProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   if ( NULL != _pProvinceList )
   {
      delete _pProvinceList;
      _pProvinceList = NULL;
   }
}

//******************************************************************************
SEVERITY AddressProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOINIT );

   DString strEntityID;
   try
   {
      getParent()->getParameter( NASULIT::CREATING_ACCOUNT, _strNASUFlag );

      getParent()->getParameter( SRCHLIT::FROM_SEARCH,     _strFromSearch );
      getParent()->getParameter( ADDRLIT::ACCOUNT_NUM,     _accountNum );
      getParent()->getParameter( ADDRLIT::ADDRESS_CODE,    _addrCode );
      getParent()->getParameter( ADDRLIT::SHAREHOLDER_NUM, _shrNum );
      getParent()->getParameter( ADDRLIT::SETTLEMENT,      _FromSettlement );

      getParameter( pINQUIRYONLY,         _InquiryOnly ); 
      getParameter( ADDRLIT::ENTITY_ID,   m_dstrEntityId );
      getParameter( ADDRLIT::FROM_ENTITY, m_dstrFromEntity );
      getParameter( ADDRLIT::ENTITY_TYPE, m_dstrEntityType );
      getParameter( ADDRLIT::SEQ_NUMBER,  m_dstrSeqNum );

      getParameter( I_("ENTITY_ALONE") ,  m_dstrFromEntityAlone );

      getParameter( ADDRLIT::RETMAIL_TAB, m_dstrRetMailTab );
      if( isXMLAPIContext() )
      {
         getParent()->getParameter( EntityId, strEntityID );
         if( strEntityID!=NULL_STRING )
            setGlobal( WORK_GLOBAL, ifds::LastActiveEntityId, strEntityID );
      }
      _FromSettlement.strip();

      _accountNum.stripLeading( '0' ).strip();
      _shrNum.stripLeading( '0' ).strip();

      if( (_shrNum != NULL_STRING) && (_accountNum == NULL_STRING) )
         _searchShareholder = Y_STRING;
      else
         _searchShareholder = NULL_STRING;     

      setFreshList(NULL);
   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION( ce );
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void AddressProcess::setCurrentListItem( const GenericInterface *rpGICaller,
                                         const BFContainerId& idList,
                                         const DString& strListItemKey
                                       )
{  
   TRACE_METHOD( CLASSNAME, I_( "setCurrentListItem" ) );
   DString strEntityID; 
   DString key = strListItemKey;

   if( strListItemKey == SPACE_STRING )
   {
      if( idList == IFASTBP_PROC::ENTITY_LIST )
      {
         Entity* pEntity = NULL;

         getParent()->getParameter( ADDRLIT::ENTITY_ID, strEntityID );
         getParent()->getParameter( LIST_KEY, _strKey );
         if ( !strEntityID.empty() )
         {
            key = _strKey;  
            if( dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getEntity( getDataGroupId(), 
               strEntityID, 
               pEntity ) <= WARNING )
            {            
               if( pEntity->getAddressEntityList( _pAddressEntityList, getDataGroupId() ) <= WARNING )
               {
				   AccountEntityXrefObject *pAccountEntityXrefObject = dynamic_cast<AccountEntityXrefObject *>(getCBOItem(IFASTBP_PROC::ENTITY_LIST, getDataGroupId()));
				   DString dstrEntityType, dstrSeqNumber;
				   if(pAccountEntityXrefObject)
				   {
				       pAccountEntityXrefObject->getField(ifds::EntityType, dstrEntityType, getDataGroupId());
				       pAccountEntityXrefObject->getField(ifds::SeqNumber, dstrSeqNumber, getDataGroupId());
				       _pAddressEntityList->setField(ifds::EntityType, dstrEntityType, getDataGroupId());
				       _pAddressEntityList->setField(ifds::SeqNumber, dstrSeqNumber, getDataGroupId());
				   }

				   setContainer( IFASTBP_PROC::ENTITY_ADDRESS_LIST, _pAddressEntityList );
               }
            }
         }
      }
   }
   else
   {
      if( idList == IFASTBP_PROC::ACCOUNT_MAILING_LIST )
      {
         const BFDataGroupId& idDataGroup = getDataGroupId();
         AccountMailingInfo* pAccountMailingInfo =  dynamic_cast<AccountMailingInfo*>( getCBOItem( idList, idDataGroup ) );
         if( pAccountMailingInfo ) pAccountMailingInfo->setWorkingFlag( true );
      }
   }
   AbstractProcess::setCurrentListItem( rpGICaller, idList, key );
}

//******************************************************************************
// Default implementation
SEVERITY AddressProcess::doValidateAll( BFAbstractCBO *rpWSD,  
                               const BFDataGroupId& idDataGroup )
{
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, DOVALIDATEALL );

   SEVERITY  sev0 = NO_CONDITION, sev1,sev2;
   if( _strNASUFlag == I_("Y") )
   {
      Address* pAddress = dynamic_cast<Address*>( getCBOItem( IFASTBP_PROC::ADDRESSES_LIST, idDataGroup ) );
      if( pAddress )  sev0 = pAddress->validateAll( idDataGroup );
   }

   if( _accountNum != NULL_STRING )
   {
     DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());   

      sev1 = _pAccountMailingList->validateAll(idDataGroup);
      PROMOTECONDITIONS();
      sev1 = sev1>sev0 ? sev1:sev0;
      sev2 = _pAddressList->validateAll(idDataGroup);
      PROMOTECONDITIONS();
      sev1 = sev1>sev2?sev1:sev2;
      BFObjIter iter( *_pAccountEntityXref, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );
      while( !iter.end() )
      {
         AccountEntityXrefObject *pAccountEntityXrefObject = dynamic_cast< AccountEntityXrefObject * >( iter.getObject()  );         
       if ( NULL != pAccountEntityXrefObject )
       {         
         DString dstrEntityId;
         pAccountEntityXrefObject->getField( ifds::EntityId, dstrEntityId, idDataGroup );
         Entity *pEntity = NULL;
         if ( dstcWorkSession->getEntity( idDataGroup, dstrEntityId, pEntity ) &&
              NULL != pEntity )
         {
            AddressEntityList *pAddressEntityList = NULL;
            if( pEntity->getAddressEntityList( pAddressEntityList, getDataGroupId() ) <= WARNING &&
               NULL != pAddressEntityList )
            {               
               SEVERITY sevEntityAddress = pAddressEntityList->validateAll( idDataGroup );
               if( sevEntityAddress > WARNING )
               {
                  PROMOTECONDITIONS();
                  return sevEntityAddress;
               }
            }
         }

         EntityAddressMailingList* pEntityAddressMailingList = NULL;
         pAccountEntityXrefObject->getEntityMailingList(pEntityAddressMailingList,idDataGroup);
         if( pEntityAddressMailingList )
         {
            if( pEntityAddressMailingList->isUpdatedForDataGroup(idDataGroup) )
            {
            sev2 = pEntityAddressMailingList->validateAll(idDataGroup);
            if(sev2 > WARNING)
            {
               PROMOTECONDITIONS();
               break;
            }
            }
         }
       }
       ++iter;
      }

      sev1 = sev1>sev2 ? sev1:sev2;   
      MFAccount* pMFAccount = NULL;
      if( dstcWorkSession->getMFAccount( idDataGroup, _accountNum, pMFAccount, I_("N"), NULL_STRING, true, true) <= WARNING )
      {     
           AcctMailingOverrideList* pAcctMailingOverrideList = NULL;
           if(pMFAccount->getAcctMailingOverrideList(pAcctMailingOverrideList, idDataGroup)<=WARNING )
           {
              if( pAcctMailingOverrideList )
              {
                  sev2 = pAcctMailingOverrideList->validateAll(idDataGroup);
              }
           }
      }

      sev1 = sev1>sev2?sev1:sev2;
      return sev1;
   }
   else if ( _accountNum.empty() && !m_dstrEntityId.empty() && !m_dstrFromEntity.empty() )
   {
      if ( NULL != _pAddressEntityList )
      {         
         SEVERITY sevEntityAddress = _pAddressEntityList->validateAll( idDataGroup );               
         if( sevEntityAddress > WARNING )
         {
            PROMOTECONDITIONS();
         }
         
         return sevEntityAddress;         
      }
      else
      {
         ADDCONDITIONFROMFILE( CND::BP_ERR_ENTITY_ADDRESS_LIST_INVALID );         
         return GETCURRENTHIGHESTSEVERITY ();
      }
   }
   else   
      return rpWSD->validateAll( idDataGroup );
}

//******************************************************************************
E_COMMANDRETURN AddressProcess::doProcess()
{  
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOPROCESS );
   E_COMMANDRETURN rtn = CMD_FAILURE;

   try
   {
      setParameter( NASULIT::CREATING_ACCOUNT,   _strNASUFlag );
      setParameter( ADDRLIT::ACCOUNT_NUM,        _accountNum );
      setParameter( ADDRLIT::ADDRESS_CODE,       _addrCode );
      setParameter( ADDRLIT::SHAREHOLDER_NUM,    _shrNum );  //get parameter from parent screen
      setParameter( ADDRLIT::SEARCH_SHAREHOLDER, _searchShareholder );
      setParameter( pINQUIRYONLY,                _InquiryOnly);
      setParameter( ADDRLIT::ENTITY_ID,          m_dstrEntityId);
      setParameter( ADDRLIT::FROM_ENTITY,        m_dstrFromEntity);
      setParameter( ADDRLIT::ENTITY_TYPE,        m_dstrEntityType );
      setParameter( ADDRLIT::SEQ_NUMBER,         m_dstrSeqNum );

      setParameter( I_("ENTITY_ALONE") ,  m_dstrFromEntityAlone );

      if( _FromSettlement.strip() == I_("YES") )
      {
         rtn = invokeCommand( this, CMD_GUI_ADDRESS_SELECTION, getProcessType(), isModal(), &_rpChildGI );
      }
      else
      {

         if( !isXMLAPIContext() )
         {
            rtn = invokeCommand( this, CMD_GUI_ADDRESSES, getProcessType(), isModal(), &_rpChildGI );
         }
         else
         {
            rtn = CMD_MODELESS_INPROCESS;
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
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOPROCESS, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(rtn);
}

//******************************************************************************
bool  AddressProcess::doModelessSetFocus( GenericInterface *rpGICaller )
{  
   // This is implemented to pass set focus on to child dialog.
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, DOMODELESSSETFOCUS );
   bool bRtn = false;

   try
   {
      DString strAccountNum,strShrNum;
      getParent()->getParameter( ADDRLIT::ACCOUNT_NUM, strAccountNum );
      getParent()->getParameter( ADDRLIT::ADDRESS_CODE, _addrCode );
      MFAccount* pMFAccount = NULL;
      strAccountNum.stripLeading( '0' ).strip();
      //if(strAccountNum != _accountNum){

      if( dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getMFAccount( getDataGroupId(), 
                                                                             strAccountNum, 
                                                                             pMFAccount ) <= WARNING )
      {
         pMFAccount->getField( ifds::ShrNum, strShrNum, getDataGroupId(), false );
         _shrNum = strShrNum; _accountNum=strAccountNum;
         setFreshList( rpGICaller );

         setGlobal( WORK_GLOBAL, ifds::LastActiveAccountNum, _accountNum );
         setGlobal( WORK_GLOBAL, ifds::LastActiveShrNum, _shrNum );

         if( !( bRtn = _rpChildGI->refresh( this, NULL ) ) )
         {
            return(bRtn);  // false
         }
         bRtn = _rpChildGI->modelessSetFocus( rpGICaller );
      }
      //}
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
bool  AddressProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return( cmd.getKey() == CMD_GUI_ADDRESSES );
}

//******************************************************************************
const DString& AddressProcess::getFirstListItemKey( const GenericInterface *rpGICaller, 
                                        const BFContainerId& idList )
{  
   TRACE_METHOD( CLASSNAME, GETFIRSTLISTITEMKEY );

   DString key;
   try
   {
      if( idList == IFASTBP_PROC::ENTITY_LIST )
      {
         if ( NULL != _pAccountEntityXref && !_accountNum.empty() )
         {
            DString searchKey;
            BFObjIter iterAccountEntityXref( *_pAccountEntityXref, getDataGroupId(), true, BFObjIter::ITERTYPE::NON_DELETED );
            AccountEntityXref::buildPartialKeyForAccount( searchKey, _accountNum );

            if( !iterAccountEntityXref.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey ) )
            {
               return(EMPTY_STRING);
            }

            key = iterAccountEntityXref.getStringKey();
            AbstractProcess::setCurrentListItem( rpGICaller, idList, key );
            return(iterAccountEntityXref.getStringKey());
         }
         else if ( _accountNum.empty() && _shrNum.empty() && !m_dstrEntityId.empty() && m_dstrFromEntity == I_( "Y" ) )
         {
            DString searchKey;
            BFObjIter iterEntityList( *_pWorkSessionEntityList,
               getDataGroupId(), 
               true, 
               BFObjIter::ITERTYPE::NON_DELETED );


            while( !iterEntityList.end() )
            {
               Entity* pEntity = dynamic_cast<Entity*>( iterEntityList.getObject() );

               if ( NULL != pEntity )
               {
                  DString dstrEntityId;
                  pEntity->getField( ifds::EntityId, dstrEntityId, getDataGroupId() );
                  if ( dstrEntityId.strip() == m_dstrEntityId )
                  {
                     key = iterEntityList.getStringKey();
                     AbstractProcess::setCurrentListItem( rpGICaller, idList, key );
                     return(iterEntityList.getStringKey());
                  }
               }
               ++iterEntityList;
            }
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
const DString& AddressProcess::getNextListItemKey( const GenericInterface *rpGICaller, 
                                       const BFContainerId& idList )
{  
   TRACE_METHOD( CLASSNAME, GETNEXTLISTITEMKEY );

   DString key;

   try
   {
      if( idList == IFASTBP_PROC::ENTITY_LIST )
      {
         if ( NULL != _pAccountEntityXref && !_accountNum.empty() )
         {
            BFObjIter iterAccountEntityXrefOut( *_pAccountEntityXref, getDataGroupId(), true, BFObjIter::ITERTYPE::NON_DELETED );
            DString searchKey;
            AccountEntityXref::buildPartialKeyForAccount( searchKey, _accountNum );

            iterAccountEntityXrefOut.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey );

            DString entityListCurrentItemKey = getCurrentListItemKey( rpGICaller, idList );
            iterAccountEntityXrefOut.positionByKey( entityListCurrentItemKey );
            if( !++iterAccountEntityXrefOut )
               return(EMPTY_STRING);

            DString key = iterAccountEntityXrefOut.getStringKey();
            AbstractProcess::setCurrentListItem( rpGICaller, idList, key );
            return(iterAccountEntityXrefOut.getStringKey());
         }
         else if ( _accountNum.empty() && _shrNum.empty() && !m_dstrEntityId.empty() && m_dstrFromEntity == I_( "Y" ) )
         {
            // We should have only one Entity in this case
            return EMPTY_STRING;
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
const DString& AddressProcess::getKeyForNewListItem( const GenericInterface *rpGICaller,
                                                     const BFContainerId& idList )
{
   const DString& strKey = AbstractProcess::getKeyForNewListItem( rpGICaller, idList );

   if( idList == IFASTBP_PROC::ACCOUNT_MAILING_LIST )
   {
      const BFDataGroupId& idDataGroup = getDataGroupId();

      AccountMailingInfo* pAccountMailingInfo = 
      dynamic_cast<AccountMailingInfo*>( getCBOItem( idList, idDataGroup ) );
      if( pAccountMailingInfo )
      {
         pAccountMailingInfo->setField( ifds::AccountNum, _accountNum, idDataGroup );
         pAccountMailingInfo->setWorkingFlag( true );
      }
   }
   return(strKey);
}

//******************************************************************************
void* AddressProcess::getPtrForContainer( const BFContainerId& idContainer, const BFDataGroupId& idDataGroup )
{
   void *ptr = NULL;
   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   try
   {
      if( IFASTBP_PROC::ADDRESSES_LIST == idContainer )
      {        
         if ( _accountNum.empty() && _shrNum.empty() && !m_dstrEntityId.empty() && m_dstrFromEntity == I_( "Y" ) )
         {
            Entity* pEntity = NULL;
            if( dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getEntity( getDataGroupId(), 
               m_dstrEntityId, 
               pEntity ) <= WARNING )
            {
               AddressEntityList *pAddressEntityList = NULL;

               if( pEntity->getAddressEntityList( pAddressEntityList, getDataGroupId() ) <= WARNING )
                  ptr = pAddressEntityList;
            }
         }
         else 
         {
            Shareholder *pShareholder = NULL;

            if( dstcWorkSession->getShareholder( idDataGroup, _shrNum, pShareholder ) <= WARNING )
            {
               _pAddressList = NULL;

               //if we are comming from search we do not want to ignore data not found
               if( pShareholder->getAddressList( _pAddressList, idDataGroup, 
                                                 _strFromSearch != I_( "Y" ) ) <= WARNING )
               {
                  ptr = _pAddressList;
               }
            }
         }
      }
      else if( IFASTBP_PROC::ACCOUNT_MAILING_LIST == idContainer )
      {
         {
            Shareholder *pShareholder = NULL;

            if( dstcWorkSession->getShareholder( idDataGroup, _shrNum, pShareholder ) <= WARNING )
            {
               _pAccountMailingList = NULL;

               if( pShareholder->getAccountMailingList( _pAccountMailingList, idDataGroup ) <= WARNING )
               {
                  ptr = _pAccountMailingList;
               }
            }
         }
      }
      else if( IFASTBP_PROC::SHAREHOLDER_LIST == idContainer )
      {
         {
            Shareholder *pShareholder = NULL;

            if( dstcWorkSession->getShareholder( idDataGroup, _shrNum, pShareholder ) <= WARNING )
            {
               ptr = pShareholder;
            }
         }
      }
      else if( IFASTBP_PROC::ENTITY_LIST == idContainer )
      {
         if ( NULL != _pAccountEntityXref && !_accountNum.empty() )
         {
            ptr = _pAccountEntityXref;
         }
         else if ( _accountNum.empty() && _shrNum.empty() && !m_dstrEntityId.empty() && m_dstrFromEntity == I_( "Y" ) )
         {            
            ptr = _pWorkSessionEntityList;
         }
      }
      else if( IFASTBP_PROC::ENTITY_ADDRESS_LIST == idContainer )
      {
         if( isXMLAPIContext() )
         {
            Entity* pEntity = NULL;
            DString strEntityID;
            getGlobal( WORK_GLOBAL, ifds::LastActiveEntityId, strEntityID );

            if( dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getEntity( getDataGroupId(), 
               strEntityID, 
               pEntity ) <= WARNING )
            {
               AddressEntityList *pAddressEntityList = NULL;

               if( pEntity->getAddressEntityList( pAddressEntityList, getDataGroupId() ) <= WARNING )
                  ptr = pAddressEntityList;
            }
         }
         else if ( _accountNum.empty() && _shrNum.empty() && !m_dstrEntityId.empty() && m_dstrFromEntity == I_( "Y" ) )
         {         
            ptr = _pAddressEntityList;
         }
         else
            ptr = _pAddressEntityList;
      }
      else if( IFASTBP_PROC::ENTITY_MAILING_LIST == idContainer )
      {
         {
            AccountEntityXrefObject *pAccountEntityXrefObject = dynamic_cast< AccountEntityXrefObject * >( getCBOItem(IFASTBP_PROC::ENTITY_LIST, idDataGroup ) );
            EntityAddressMailingList* pEntityAddressMailingList = NULL;
            if( pAccountEntityXrefObject && pAccountEntityXrefObject->getEntityMailingList(pEntityAddressMailingList,idDataGroup) <= WARNING )
            {
               ptr = pEntityAddressMailingList;
            }
         }
      }
     else if ( IFASTBP_PROC::PROVINCE_LIST == idContainer )
     {
         EntityAddress* pEntityAddress = dynamic_cast<EntityAddress*>( getCBOItem( IFASTBP_PROC::ENTITY_ADDRESS_LIST, idDataGroup ) );
         if ( NULL != pEntityAddress )
         {
            DString dstrCountryCode;
            pEntityAddress->getField( ifds::Country, dstrCountryCode, idDataGroup );
   
            if ( !dstrCountryCode.empty() )
            {
               ProvinceList *pProvinceList = NULL;
               if ( NULL != dstcWorkSession &&
                  dstcWorkSession->getMgmtCo().getProvinceList( dstrCountryCode, pProvinceList ) <= WARNING &&
                  NULL != pProvinceList )
               {
                  ptr = pProvinceList;
               }
            }
            else
            {
               if ( NULL == _pProvinceList )
               {
                  _pProvinceList = new ProvinceList(*dstcWorkSession);   
                  _pProvinceList->init( idDataGroup );
               }
               
               ptr = _pProvinceList;
            }
         }
      }
      else
      {

      }
   }
   catch( ConditionException & )
   {
      throw;
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, I_("getPtrForContainer"),
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(ptr);
}

//******************************************************************************
SEVERITY AddressProcess::setFreshList( GenericInterface *rpGI )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTBP_CONDITION, CLASSNAME, I_("setFreshList") );
   SEVERITY sevRtn = SEVERE_ERROR, sevRtn1 = SEVERE_ERROR;

   const BFDataGroupId& idDataGroup = getDataGroupId();

   _accountNum.stripLeading( '0' ).strip();
   _shrNum.stripLeading( '0' ).strip();
   try
   {
      DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      if( _accountNum != NULL_STRING )
      {
         MFAccount* pMFAccount = NULL;

         if( dstcWorkSession->getMFAccount( idDataGroup, _accountNum, pMFAccount, I_("N"), NULL_STRING, true, true) <= WARNING )
         {

            AcctMailingOverrideList* pAcctMailingOverrideList;
            if(pMFAccount->getAcctMailingOverrideList(pAcctMailingOverrideList, idDataGroup)<=WARNING )
            {
               // add set field and initialize
               setContainer(IFASTBP_PROC::ACCT_MAILING_OVERRIDE_LIST, pAcctMailingOverrideList);
            }

            pMFAccount->getField( ifds::ShrNum, _shrNum, idDataGroup, false );

            //shareholder cbo
            Shareholder* pShareholder = NULL;

            if( dstcWorkSession->getShareholder( idDataGroup, _shrNum, pShareholder ) <= WARNING )
            {
               //entity list, it is a logical singleton
               if( dstcWorkSession->getAccountEntityXref( idDataGroup, _pAccountEntityXref ) < WARNING )
               {
                  if( _strNASUFlag != I_("Y") && _pAccountEntityXref)
                     _pAccountEntityXref->PopulateEntitiesList( idDataGroup, _accountNum );

                  //address list
                  _pAddressList = NULL;

                  if( pShareholder->getAddressList (_pAddressList, idDataGroup,
                     _strFromSearch != I_( "Y" ) ) <= WARNING)
                  {
                     _pAddressList->setField ( ifds::AccountNum, 
                                               _accountNum, 
                                               idDataGroup,
                                               false);

                     //acount mailing list
                     _pAccountMailingList = NULL;

                     if (pShareholder->getAccountMailingList (_pAccountMailingList, idDataGroup ) <= WARNING )
                     {
                        //refresh address mailing list if it is not NASU
                        if( _strNASUFlag != I_("Y") )
                           _pAccountMailingList->init(_shrNum);
                        _pAccountMailingList->setNewAccountNumber (_accountNum);

                        setGlobal( WORK_GLOBAL, ifds::LastActiveAccountNum, _accountNum );
                        setContainer( IFASTBP_PROC::SHAREHOLDER_LIST, pShareholder );
                        setContainer( IFASTBP_PROC::ENTITY_LIST, _pAccountEntityXref );
                        setContainer( IFASTBP_PROC::ADDRESSES_LIST, _pAddressList );
                        setContainer( IFASTBP_PROC::ACCOUNT_MAILING_LIST, _pAccountMailingList );
                     }
                  }
               }
            }
         }
      }
      else if( (_shrNum != NULL_STRING) && _strFromSearch == I_("Y") )  // search from shareholder number
      {
         //shareholder cbo
         Shareholder* pShareholder = NULL;

         if( dstcWorkSession->getShareholder( idDataGroup, _shrNum, pShareholder ) <= WARNING )
         {
            //address list
            _pAddressList = NULL;
            if( pShareholder->getAddressList( _pAddressList,idDataGroup,_strFromSearch != I_( "Y" ) ) <= WARNING )
            {
              
               setContainer( IFASTBP_PROC::SHAREHOLDER_LIST, pShareholder );
               setContainer( IFASTBP_PROC::ADDRESSES_LIST, _pAddressList );
            }
         }
      }
      else if ( _accountNum.empty() && _shrNum.empty() && !m_dstrEntityId.empty() && m_dstrFromEntity == I_( "Y" ) )
      {               
         if ( NULL != dstcWorkSession &&
            dstcWorkSession->getWorkSessionEntityList( _pWorkSessionEntityList, idDataGroup ) <= WARNING &&         
            NULL != _pWorkSessionEntityList )
         {
            Entity *pEntity = NULL;
            if ( _pWorkSessionEntityList->getEntity( getDataGroupId(), 
                                                   m_dstrEntityId, 
                                                      pEntity ) <= WARNING &&
               NULL != pEntity )
            {   
               setContainer( IFASTBP_PROC::ENTITY_LIST, _pWorkSessionEntityList );    

               //if( pEntity->getAddressEntityList( _pAddressEntityList, getDataGroupId() ) <= WARNING &&
               //   NULL != _pAddressEntityList )
               //{
               //   setContainer( IFASTBP_PROC::ENTITY_ADDRESS_LIST, _pAddressEntityList );
               //}
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
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}
//************************************************************************************************************
void AddressProcess::doGetField(
                               const GenericInterface *rpGICaller,
                               const BFContainerId& idContainer,
                               const BFFieldId& idField,
                               const BFDataGroupId& idDataGroup,
                               DString &strValueOut,
                               bool bFormatted
                               ) const
{  
   // Make non const pointer for calls to non-const methods

   if( idField == ADDRLIT::REG_ADDR_READ_ONLY )
   {
      //get the shareholder
      Shareholder* pShareholder;
      DString shrNum( _shrNum );
      DString strAcctDes;
      strValueOut = I_("NO");
      if( dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getShareholder( idDataGroup,
                                                                               shrNum, 
                                                                               pShareholder ) <= WARNING )
      {
         pShareholder->getField( ifds::AcctDesignation, strAcctDes, idDataGroup );
         if( (strAcctDes.strip() == I_("2")) || (strAcctDes == I_("3")) )
         {
            strValueOut = Y_STRING;
         }
      }
   }
   else if( idField == ifds::OPDeliveryOption  || idField == ifds::OPDeliveryMethods || idField == ifds::CnsntToWaive
      || idField == ifds::ShrAddressFormat || idField == ifds::MailingByFundGroup )
   {
      DSTCWorkSession* pWorkSession =  dynamic_cast<DSTCWorkSession *>(getBFWorkSession() );
      if( pWorkSession )
      {
         pWorkSession->getOption( idField, strValueOut, idDataGroup,bFormatted );    
      }
   }
   else if( idField == ADDRLIT::SALUTATION_EDIT )
   {
      // Return Yes for Salutation Edit is used or NO for Combo box.
      DString dstrValue;
      DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      dstcWorkSession->getMgmtCoOptions()->getField( ifds::SalutationFormat, dstrValue, idDataGroup, false);
      dstrValue.upperCase().stripAll();
      strValueOut = ( dstrValue.substr( 0, 1 ) == I_("Y") ) ? I_("Y") : I_("N");
   }
   else if( idField == ifds::AcctMstrRid || 
            idField == ifds::AcctDesignation )
   {
      MFAccount* pMFAccount = NULL;
      if( dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getMFAccount( idDataGroup, _accountNum, pMFAccount, I_("N"), NULL_STRING, true, true) <= WARNING )
      {
         pMFAccount->getField( idField, strValueOut, idDataGroup, false );
      }
   }
   else if ( idField == ifds::Country )
   {      
      EntityAddress *pEntityAddress = dynamic_cast<EntityAddress*>(
                              const_cast <AddressProcess*>(this)->
                              getCBOItem (IFASTBP_PROC::ENTITY_ADDRESS_LIST, idDataGroup));
            
      if ( NULL != pEntityAddress )
      {         
         pEntityAddress->getField( ifds::Country, strValueOut, idDataGroup );      
      }
   }
   else if ( idField == ADDRLIT::CREATE_MAIL_OVERRIDE  )
   {
      strValueOut = N_STRING;
      DString mailByFundGroup;
      DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      dstcWorkSession->getMgmtCoOptions()->getField( ifds::MailingByFundGroup, mailByFundGroup, idDataGroup, false);
      mailByFundGroup.strip().upperCase();
      if( mailByFundGroup == Y_STRING )
      {
         if( _accountNum != NULL_STRING )
         {
            MFAccount* pMFAccount = NULL;

            if( dstcWorkSession->getMFAccount( idDataGroup, _accountNum, pMFAccount, I_("N"), NULL_STRING, true, true) <= WARNING )
            {
               AcctMailingOverrideList* pAcctMailingOverrideList = NULL;
               SEVERITY sev = pMFAccount->getAcctMailingOverrideList(pAcctMailingOverrideList, idDataGroup);
               if( sev<=WARNING && pAcctMailingOverrideList )
               {
                  BFObjIter iter( *pAcctMailingOverrideList, idDataGroup, true, 
                           BFObjIter::ITERTYPE::NON_DELETED ); 
                  strValueOut = iter.getNumberOfItemsInList() >= 1? N_STRING:Y_STRING;
               }
            }
         }
      }
   }
   else if (idField == ADDRLIT::RetMailTab )
   {
     strValueOut = m_dstrRetMailTab;
   }  
   else if (idField == ifds::PCLookupEnabled)
   {
      BFProperties * pBFProperties = NULL;
      Address* pAddress = dynamic_cast<Address*>( const_cast <AddressProcess*>(this)->getCBOItem( IFASTBP_PROC::ADDRESSES_LIST, idDataGroup ) );

      pBFProperties = pAddress->getFieldProperties( ifds::PostalCode, idDataGroup );

      DString pcLookupEnb;
      DSTCWorkSession* pDSTCWorkSession =  dynamic_cast<DSTCWorkSession *> (getBFWorkSession ());

      pDSTCWorkSession->getOption(ifds::DskPCLookEnb, pcLookupEnb, idDataGroup, false);

      if ( pcLookupEnb == I_("N") )
      {
         strValueOut = I_("N");
      }
      else if( pBFProperties )
      {
         strValueOut = pBFProperties->isReadOnly() ? I_("N") : I_("Y");
      }
   }
   else if(idField == ifds::ListDocType)
   {
      DString strListDocType;
      DSTCWorkSession* pDSTCWorkSession =  dynamic_cast<DSTCWorkSession *> (getBFWorkSession ());
      pDSTCWorkSession->getOption(ifds::ListDocType, strListDocType, idDataGroup, false);
      strValueOut = strListDocType.strip().upperCase();
   }
   else if (idField == ifds::MailHouseholdID &&
      idContainer == IFASTBP_PROC::SHAREHOLDER_LIST)
   {
      DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      if( _accountNum != NULL_STRING )
      {
         MFAccount* pMFAccount = NULL;

         if( dstcWorkSession->getMFAccount( idDataGroup, _accountNum, pMFAccount, I_("N"), NULL_STRING, true, true) <= WARNING &&
            pMFAccount != NULL)
         {
            DString strMailHouseholdID;
            pMFAccount->getField( ifds::MailHouseholdID, strMailHouseholdID, idDataGroup, false );
            strMailHouseholdID.strip().upperCase();
            strValueOut = strMailHouseholdID;
         }
      }
   }

}
//******************************************************************************
SEVERITY AddressProcess::doSetField( const GenericInterface* rpGICaller,
                                     const BFContainerId& idContainer,
                                     const BFFieldId &fieldID,
                                     const BFDataGroupId& idDataGroup,
                                     const DString &strValue,
                                     bool bFormatted )
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, DOSETFIELD);

   if ( fieldID == ifds::Country )
   {
      BFAbstractCBO *rpPtr = getCBOItem (idContainer, idDataGroup);
      if (rpPtr)
      {
         rpPtr->setField ( ifds::Country, strValue, idDataGroup, bFormatted, false );
      }

      //reset the container, to pick up new items
      setContainer( IFASTBP_PROC::PROVINCE_LIST, NULL );
   }
   else if ( fieldID == ADDRLIT::CREATE_MAIL_OVERRIDE  )
   {
      DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      if( _accountNum != NULL_STRING )
      {
         MFAccount* pMFAccount = NULL;

         if( dstcWorkSession->getMFAccount( idDataGroup, _accountNum, pMFAccount, I_("N"), NULL_STRING, true, true) <= WARNING )
         {
            AcctMailingOverrideList* pAcctMailingOverrideList;
            if(pMFAccount->getAcctMailingOverrideList(pAcctMailingOverrideList, idDataGroup)<=WARNING )
            {
               pAcctMailingOverrideList->createAllPossibleRecordsInNasu( idDataGroup );
            }
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
bool AddressProcess::doRefresh( GenericInterface *rpGICaller,
                                const I_CHAR *szOriginalCommand )
{
   setParameter( ADDRLIT::ACCOUNT_NUM,        _accountNum );
   setParameter( ADDRLIT::ADDRESS_CODE,       _addrCode );
   setParameter( ADDRLIT::SHAREHOLDER_NUM,    _shrNum );  //get parameter from parent screen
   setParameter( ADDRLIT::SEARCH_SHAREHOLDER, _searchShareholder );
   setParameter( ADDRLIT::ENTITY_ID,          m_dstrEntityId );
   setParameter( ADDRLIT::FROM_ENTITY,        m_dstrFromEntity );
   setParameter( ADDRLIT::ENTITY_TYPE,        m_dstrEntityType );
   setParameter( ADDRLIT::SEQ_NUMBER,         m_dstrSeqNum );

   return(_rpChildGI->refresh( this, NULL ));
}
//*******************************************************************************
void AddressProcess::doPostOk( GenericInterface *rpGICaller, bool bSuccessFlag )
{

   if( bfutil::isServerContext() )return;

   if ( _accountNum.empty() && !m_dstrEntityId.empty() && !m_dstrFromEntity.empty() ) return;

   DString dstrAddrCode;
   DString dstrCurrentKey = getCurrentListItemKey( rpGICaller, IFASTBP_PROC::ADDRESSES_LIST );

   if(dstrCurrentKey != NULL_STRING )
   {
      getField( this, IFASTBP_PROC::ADDRESSES_LIST, ifds::AddrCode, dstrAddrCode, false );
      setParameter( ADDRLIT::ADDRESS_CODE, dstrAddrCode );
   }
   if( bSuccessFlag && _FromSettlement == I_("YES") )
   {
      setParameter( ADDRLIT::ADDRESS_KEY, dstrCurrentKey );   
   }
}

//******************************************************************************
bool AddressProcess::doOk (GenericInterface* rpGICaller)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, DOOK);
   
   if ( _accountNum.empty() && !m_dstrEntityId.empty() && !m_dstrFromEntity.empty() ) return true;

   //get the account
   BFDataGroupId idDataGroup = getDataGroupId();
   MFAccount *pMFAccount = NULL;
   DSTCWorkSession* pDSTCWorkSession = 
      dynamic_cast<DSTCWorkSession *> (getBFWorkSession ());

   if(pDSTCWorkSession->getMFAccount (idDataGroup, 
         _accountNum, pMFAccount) &&
         pMFAccount)
   {
      // AccountMailingList may have non host updates
      // because after update return mail flag which effect to unclaimed property
      // related field, need to refresh account after share holder is refreshed.
      pMFAccount->refreshMe (true); //refresh mfaccount
   }


   /*********************************************************************
    * PRB0042589 - Unable to modify Entity, version numbers are different
    * "Entity-Identity Version" may have non host updates.
    * deed to refresh entity after share holder is refreshed.
    **********************************************************************/
   AccountEntityXref *pAccountEntityXref (NULL);		
   WorkSessionEntityList *pWorkSessionEntityList = NULL;
   ENTITIES_VECTOR acctOwnerEntities;
   if (pDSTCWorkSession->getAccountEntityXref (idDataGroup, pAccountEntityXref) <= WARNING && pAccountEntityXref)
   {         
	   if (pDSTCWorkSession->getWorkSessionEntityList (pWorkSessionEntityList) <= WARNING && pWorkSessionEntityList)
	   {
		   pAccountEntityXref->getAcctOwnerEntities(acctOwnerEntities, _accountNum, idDataGroup);

		   if( !acctOwnerEntities.size() )
			   return GETHIGHESTSEVERITY();

		   for( ENTITIES_VECTOR::size_type i = 0; i < acctOwnerEntities.size(); ++i )
		   {
			   DString dstrEntityId;
			   Entity *pEntityOut;
			   dstrEntityId = acctOwnerEntities[i];

			   if( pWorkSessionEntityList->getEntity( idDataGroup, dstrEntityId, pEntityOut ) <= WARNING )
			   {
				   pEntityOut->refreshMe(true);
			   }

		   }
	   }
   }

   Shareholder *pShareholder = NULL;
   if( pDSTCWorkSession->getShareholder( idDataGroup, _shrNum, pShareholder ) <= WARNING )
   {
      if( pShareholder)
      {
         pShareholder->refreshMe (true);  // refresh shareholder
	     if( pShareholder->getAddressList( _pAddressList,idDataGroup ) <= WARNING )
	     {
		     // to not trig the validation about tax juris update as 
			 // users haven't check the checkbox to sych the tax juris to shareholder.
		     _pAddressList->setAfterPopupTaxJurisUpdate(false);
	     }      
      }
   }

   DString dstrTaxJurisUpdateOpt;

   SEVERITY severity =  doValidateAll(pDSTCWorkSession, idDataGroup);
   //If there are errors, do not show the dialog.
   if(severity > WARNING)
      return true;

   if ( _FromSettlement != I_("YES") )
   {
      pDSTCWorkSession->getOption(ifds::TaxJurisUpdateOpt, dstrTaxJurisUpdateOpt, 
                                  getDataGroupId(), false);

      bool bShowUpdate = false;

      DString dstrUpdTaxJuris = I_("Y");
      DString dstrUpdProvRes = I_("Y");

      if(dstrTaxJurisUpdateOpt == I_("Y"))
      {
         DString dstrMailingInfoAddrCode;
         DString dstrUpdateAddrCode;
         DString dstrResProvCode;
         DString dstrCountryCode;

         BFObjIter iterMailingList(*_pAccountMailingList,getDataGroupId() ,true,BFObjIter::ITERTYPE::NON_DELETED);

         iterMailingList.begin();

         if(!iterMailingList.end())
         {
            DString dstrAcctDesig;
            Shareholder *pShareholder;
            if(pDSTCWorkSession->getShareholder( idDataGroup, _shrNum, pShareholder )
                     <=WARNING)
            {
               pShareholder->getField (ifds::AcctDesignation, dstrAcctDesig, BF::HOST);
               dstrAcctDesig.strip();

               //Client
               if(dstrAcctDesig == I_("1"))
               {
                  iterMailingList.getObject()->getField(ifds::RegAddr, 
                        dstrMailingInfoAddrCode, idDataGroup);   
               }
               //Nominee or Intermediary
               else
               {
                  iterMailingList.getObject()->getField(ifds::BenAddr, 
                        dstrMailingInfoAddrCode, idDataGroup);   
               }
            }

            pShareholder->getField(ifds::ResProvCode, dstrResProvCode, BF::HOST);
         }

         BFObjIter iter(*_pAddressList, getDataGroupId());
         while(!iter.end())
         {
            iter.getObject()->getField(ifds::AddrCode, dstrUpdateAddrCode, 
                  idDataGroup, false);
            iter.getObject()->getField(ifds::CountryCode, dstrCountryCode, 
                  idDataGroup, false);

            if( (iter.getObject()->isNew() || iter.getObject()->isUpdated()) && 
                  (dstrMailingInfoAddrCode == dstrUpdateAddrCode)&&
                  (dstrResProvCode != dstrCountryCode) )
            {
               bShowUpdate = true;
               break;
            }
            ++iter;
         }
      }

      if(bShowUpdate)
      {
         E_COMMANDRETURN eRtn = CMD_CANCEL;
         setParameter(ADDRLIT::SHAREHOLDER_NUM, _shrNum);
         setParameter(ADDRLIT::ACCOUNT_NUM, _accountNum);

         eRtn = invokeCommand(getParent(), CMD_BPROC_ADDR_TAX_JURIS_UPDATE, PROC_SUPPORT, true, NULL);

         if(eRtn == CMD_CANCEL)
         {
			_pAddressList->setAfterPopupTaxJurisUpdate(false);
            return false;
         }
         else
         {
            getParameter( ADDRLIT::UPDATE_TAX_JURIS, dstrUpdTaxJuris);
            getParameter( ADDRLIT::UPDATE_PROV_RES,  dstrUpdProvRes );
			_pAddressList->setAfterPopupTaxJurisUpdate(true);
         }
      }

      BFObjIter iter(*_pAddressList, idDataGroup);
      while(!iter.end())
      {
         if( iter.getObject()->isNew() || iter.getObject()->isUpdated() )
         {
            iter.getObject()->setField( 
                  ifds::UpdShrTaxJuris, dstrUpdTaxJuris, idDataGroup, false);
            iter.getObject()->setField( 
                  ifds::UpdShrProvRes, dstrUpdProvRes, idDataGroup, false);
         }
         ++iter;
      }
   }

   return true;//always, go ahead with processing   
}

//******************************************************************************

SEVERITY AddressProcess::getHistoricalParameters (
   const BFContainerId &idContainer, 
   BFFieldId &recordIdField, 
   DString &tableId, 
   DString &dstrKeys)
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS);

   DString keyStringIDI, dstrAddrCode, dstrEffectiveDate, dstrAccountNum;
   
   if ( idContainer == IFASTBP_PROC::ADDRESSES_LIST )               // Shareholder Address
   {
      recordIdField = ifds::AddressFileRid;
      tableId = AUDITTYPE::SHADDR;
      // Shareholder Number, Address Code, Effective Date
      getField( this, IFASTBP_PROC::ADDRESSES_LIST, ifds::AddrCode, dstrAddrCode, false );
      getField( this, IFASTBP_PROC::ADDRESSES_LIST, ifds::EffectiveDate, dstrEffectiveDate, false );
      addIDITagValue( keyStringIDI, MFCAN_IP_PARAM::SHR_NUM, _shrNum );
      addIDITagValue( keyStringIDI, MFCAN_IP_PARAM::ADDRESS_CODE, dstrAddrCode );
      addIDITagValue( keyStringIDI, MFCAN_IP_PARAM::EFFECTIVE_DATE, dstrEffectiveDate );
      dstrKeys = keyStringIDI;
   }
   else if ( idContainer == IFASTBP_PROC::ACCOUNT_MAILING_LIST ) 
   {
      recordIdField == ifds::AcctMstrRid;
      tableId = AUDITTYPE::SHADDR;

   }
   /*
   else if ( idContainer == IFASTBP_PROC::ENTITY_MAILING_LIST ) 
   {
      DString docType,entityType,sequence,option;
      recordIdField = ifds::DelOptnRecId;
      tableId = I_("DELOPN");
      getField(this,IFASTBP_PROC::ENTITY_MAILING_LIST,ifds::EntityType,
                     entityType,false );
      getField(this,IFASTBP_PROC::ENTITY_MAILING_LIST,ifds::EntityTypeSeq,
                     sequence,false );

      getField(this,IFASTBP_PROC::ENTITY_MAILING_LIST,ifds::DocumentType,
                     docType,false );
      getField(this,IFASTBP_PROC::ENTITY_MAILING_LIST,ifds::DeliveryOption,
                     option,false );
      addIDITagValue( keyStringIDI, MFCAN_IP_PARAM::ACCOUNT_NUM, _accountNum );
      addIDITagValue( keyStringIDI, MFCAN_IP_PARAM::ENTITY_TYPE, entityType );
      addIDITagValue( keyStringIDI, MFCAN_IP_PARAM::SEQNUMBER, sequence );
      addIDITagValue( keyStringIDI, MFCAN_IP_PARAM::DOCUMENT_TYPE, docType );
      addIDITagValue( keyStringIDI, MFCAN_IP_PARAM::DELIVERY_OPTION, option );
      dstrKeys = keyStringIDI;   
   }
   else if ( idContainer == IFASTBP_PROC::ACCT_MAILING_OVERRIDE_LIST ) 
   {
      DString docType,entityType,sequence,option;
      recordIdField = ifds::DelOptnRecId;
      tableId = I_("DELOPN");
      getField(this,IFASTBP_PROC::ENTITY_MAILING_LIST,ifds::EntityType,
                     entityType,false );
      getField(this,IFASTBP_PROC::ENTITY_MAILING_LIST,ifds::EntityTypeSeq,
                     sequence,false );

      getField(this,IFASTBP_PROC::ENTITY_MAILING_LIST,ifds::DocumentType,
                     docType,false );
      getField(this,IFASTBP_PROC::ENTITY_MAILING_LIST,ifds::DeliveryOption,
                     option,false );
      addIDITagValue( keyStringIDI, MFCAN_IP_PARAM::ACCOUNT_NUM, _accountNum );
      addIDITagValue( keyStringIDI, MFCAN_IP_PARAM::ENTITY_TYPE, entityType );
      addIDITagValue( keyStringIDI, MFCAN_IP_PARAM::SEQNUMBER, sequence );
      addIDITagValue( keyStringIDI, MFCAN_IP_PARAM::DOCUMENT_TYPE, docType );
      addIDITagValue( keyStringIDI, MFCAN_IP_PARAM::DELIVERY_OPTION, option );
      dstrKeys = keyStringIDI;   
   }
   else 
   {
      assert(0);
   }
*/
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************

SEVERITY AddressProcess::getHistoricalParameters( const BFContainerId& idContainer,
                                                 HISTORICAL_VECTOR &vectorHistorical )
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AddressProcess::doGetErrors ( const GenericInterface *rpGICaller,
                                       const BFContainerId &idContainer,
                                       const BFFieldId &idField,
                                       const BFDataGroupId &idDataGroup,
                                       CONDITIONVECTOR &conditions) const
{
   SEVERITY sevRtn = NO_CONDITION;

   if ( idContainer == IFASTBP_PROC::ENTITY_ADDRESS_LIST )       
   {
      BFAbstractCBO *rpPtr = const_cast<AddressProcess*> (this)->getCBOItem ( idContainer, idDataGroup);
      if (rpPtr)
      {
         if ( idField == ifds::Country )
         {               
            sevRtn = rpPtr->getErrors ( ifds::Country, 
                                        idDataGroup, 
                                        conditions );
         }
      }
   }

   return sevRtn;
}

//******************************************************************************
const BFProperties *AddressProcess::doGetFieldAttributes ( const GenericInterface *rpGICaller, 
                                                           const BFContainerId &idContainer, 
                                                           const BFFieldId &idField, 
                                                           const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::BPBASE_CONDITION, 
                           CLASSNAME, 
                           DOGETFIELDATTRIBUTES);

   const BFProperties *pBFProperties = NULL;

   if ( idContainer == IFASTBP_PROC::ENTITY_ADDRESS_LIST &&
        idField == ifds::Country )
   {
      BFAbstractCBO *rpPtr = getCBOItem ( idContainer, 
                                          idDataGroup);
      if (rpPtr)
      {
         pBFProperties = rpPtr->getFieldProperties ( idField, 
                                                     idDataGroup);
      }
   }

   return pBFProperties;
}

//******************************************************************************
void AddressProcess::refreshUnclaimedFields( const BFDataGroupId &idDataGroup )
{
   Address* pAddress = 
      dynamic_cast<Address*>( getCBOItem( IFASTBP_PROC::ADDRESSES_LIST, idDataGroup ) );

   if ( pAddress )
   {
      pAddress->refreshFields(fieldsUncliamedProperty,
                              numFieldsUncliamedProperty,
                              idDataGroup);
   }
}

//******************************************************************************
void AddressProcess::refreshRegAddrForNominee( const BFDataGroupId &idDataGroup )
{
   Address* pAddress = 
      dynamic_cast<Address*>( getCBOItem( IFASTBP_PROC::ADDRESSES_LIST, idDataGroup ) );

   if ( pAddress )
   {
      pAddress->refreshFields(fieldsRegAddr,
                              numFieldsRegAddr,
                              idDataGroup);
   }
}

//******************************************************************************
void AddressProcess::getMailOptionSubstitutionByDocKey(const DString &strDocKey, 
                                                       BFFieldId &fieldID)
{
   AccountMailingInfo* pAccountMailingInfo = 
      dynamic_cast<AccountMailingInfo*>( getCBOItem( IFASTBP_PROC::ACCOUNT_MAILING_LIST, getDataGroupId() ) );

   if ( pAccountMailingInfo )
   {
      pAccountMailingInfo->getMailOptionSubstitutionByDocKey (strDocKey,
                                                              getDataGroupId(),
                                                              fieldID);
   }
   else
   {
      fieldID = ifds::Yes_NO;
   }
}

//******************************************************************************
//              Private Methods
//******************************************************************************

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/AddressProcess.cpp-arc  $
 * 
 *    Rev 1.87   Jan 19 2012 12:09:32   wp040132
 * Minerva ISF Code changes..
 * 
 *    Rev 1.86   Dec 01 2010 04:17:26   dchatcha
 * P0175716 FN02 - Client Name Redemption - EPA Auto Settlement.
 * 
 *    Rev 1.85   Jan 25 2010 22:46:40   dchatcha
 * IN# 1983880 - Rel 97 Static Data - Status of Nom (01 Reg address) is set to Unverified.
 * 
 *    Rev 1.84   Dec 03 2009 02:41:10   dchatcha
 * PET0166583 FN02 FN03 - Static Verification Phase 2.
 * 
 *    Rev 1.83   17 Jul 2009 14:06:44   walkerro
 * PET156681 FN03 - Postal Code lookup on address screen
 * 
 *    Rev 1.82   Dec 15 2008 12:04:00   wongsakw
 * IN 1483427 -- Tax Jurisdiction Update modifying address
 * 
 *    Rev 1.81   Nov 11 2008 23:44:36   daechach
 * IN 1434870 - User s/b be able to flagged '01' address of Nom/Intermediary w/ ret. mail=yes, Code Review. Synch up from R89.
 * 
 *    Rev 1.80   Nov 11 2008 08:20:40   daechach
 * PET0096390 FN01 Tax Jurisdiction Update - check in for Noom.
 * 
 *    Rev 1.79   Nov 06 2008 02:04:08   daechach
 * PET5517 FN71 Unclaimed Property Phase 2
 * 
 *    Rev 1.78   Oct 29 2008 21:05:46   wongsakw
 * PET0096390 FN01 Tax Jurisdiction Update
 * 
 *    Rev 1.77   Oct 28 2008 00:01:58   daechach
 * IN 1434870 - User s/b be able to flagged '01' address of Nom/Intermediary w/ ret. mail=yes
 * 
 *    Rev 1.76   Oct 05 2008 23:29:30   wongsakw
 * PET5517 FN71 Unclaimed Property - Return Mail
 * 
 * Mailing Assign Panel does not update after the return mail flag is set to no.
 * 
 *    Rev 1.75   Sep 29 2008 07:56:16   wongsakw
 * PET5517 FN71 Unclaimed Property - Return Mail
 * 
 *    Rev 1.74   Sep 22 2008 08:45:14   wongsakw
 * PET5517 FN71 Unclaimed Property
 * 
 *    Rev 1.73   Sep 29 2005 10:54:32   yingbaol
 * PET1277,FN09: Add Default mailing option for override in NASU flow
 * 
 *    Rev 1.72   Sep 21 2005 16:50:50   yingbaol
 * PET1277,FN09 Investment Fund Continious Disclosure
 * 
 *    Rev 1.71   Mar 16 2005 13:42:56   yingbaol
 * Incident#252121: sync. to Rel 61
 * 
 *    Rev 1.70   Mar 16 2005 10:29:12   porteanm
 * PET 1171 FN01 - EUSD Entity Address Update support.
 * 
 *    Rev 1.69   Mar 16 2005 10:03:28   porteanm
 * PET 1171 FN01 - EUSD Entity Address Update support.
 * 
 *    Rev 1.68   Mar 15 2005 10:49:34   porteanm
 * PET 1171 FN01 - EUSD Entity Address Update support - work in progress.
 * 
 *    Rev 1.67   Mar 14 2005 17:21:20   porteanm
 * PET 1171 FN01 - EUSD Entity Address Update support - work in progress.
 * 
 *    Rev 1.66   Mar 14 2005 16:30:50   porteanm
 * PET 1171 FN01 - EUSD Entity Address Update support.
 * 
 *    Rev 1.65   Mar 11 2005 15:02:14   porteanm
 * PET 1171 FN01 - EUSD Entity Address Update - work in progress.
 * 
 *    Rev 1.64   Mar 08 2005 17:06:02   porteanm
 * PET 1171 FN01 - EUSD Entity Address Update support - work in progress.
 * 
 *    Rev 1.63   Mar 08 2005 10:29:52   porteanm
 * PET 1171 FN01 - EUSD Entity Address Update support - work in progress.
 * 
 *    Rev 1.62   Mar 02 2005 17:09:14   porteanm
 * PET 1171 FN01 - EUSD Entity Address Search - work in progress.
 * 
 *    Rev 1.61   Feb 25 2005 13:20:52   porteanm
 * PET 1171 FN01 - EUSD Entity Address Search - work in progress.
 * 
 *    Rev 1.60   Dec 03 2004 17:19:28   yingbaol
 * PET1137,FN01: validate alll should also include AccountMailing override
 * 
 *    Rev 1.59   Dec 02 2004 17:14:28   yingbaol
 * PET1137,FN01, adjust the code
 * 
 *    Rev 1.58   Dec 02 2004 11:37:46   yingbaol
 * PET1137,FN01: Add Epost functionality
 * 
 *    Rev 1.57   Nov 29 2004 11:08:54   yingbaol
 * PTS10031225: When user changes register address, shareholder CBO need to be refreshed( there is logic at back end change Tax Juridiction and resident province.
 * 
 *    Rev 1.56   Oct 04 2004 14:37:46   YINGBAOL
 * PET1145 FN01: sync Ver 1.53.10
 * 
 *    Rev 1.55   May 25 2004 22:38:54   popescu
 * PTS 10026123, address 01, for nominee and intermediary accounts by tax type and reg address code
 * 
 *    Rev 1.54   May 25 2004 20:32:06   popescu
 * PTS 10026123, address 01, for nominee and intermediary accounts by tax type and reg address code
 * 
 *    Rev 1.53   Mar 10 2004 11:31:58   HERNANDO
 * PET965 FN11 - Added getHistoricalParameters.
 * 
 *    Rev 1.52   Mar 05 2004 09:51:10   HERNANDO
 * PET965 FN11 - Changed Delivery Options.
 * 
 *    Rev 1.51   Mar 03 2004 16:21:14   popescu
 * PTS 10027578, refresh the account information after updating the mailing address info and demographics info; changed the name of the refreshMe method, to be consistent with the shareholder object
 * 
 *    Rev 1.50   Mar 02 2004 16:23:38   HERNANDO
 * PET965 FN11 - Added Historical functionality; added getHistoricalParameters.
 * 
 *    Rev 1.49   Oct 14 2003 13:17:18   HERNANDO
 * PET893 FN08 - Salutation enhancement.
 * 
 *    Rev 1.48   Jul 30 2003 11:26:56   FENGYONG
 * CIBC enhancement PET809_FN46
 * 
 *    Rev 1.47   May 29 2003 15:44:58   HERNANDO
 * Setting Address Code Parameter on Post Okay.  
 * 
 *    Rev 1.46   May 16 2003 18:22:00   YINGBAOL
 * don't validate EntityAddressMailing if there is no change
 * 
 *    Rev 1.45   Apr 11 2003 11:11:20   YINGBAOL
 * put Name1 back to Shareholder list
 * 
 *    Rev 1.44   Apr 04 2003 16:48:36   YINGBAOL
 * small fix
 * 
 *    Rev 1.43   Apr 03 2003 09:37:26   YINGBAOL
 * add RegAddrCode
 * 
 *    Rev 1.42   Apr 02 2003 12:03:20   linmay
 * modified setFreshList()
 * 
 *    Rev 1.41   Apr 01 2003 16:52:28   FENGYONG
 * Add AcctMailingOverride list
 * 
 *    Rev 1.40   Mar 21 2003 17:35:14   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.39   Mar 03 2003 11:59:32   KOVACSRO
 * Added InquiryOnly parameter
 * 
 *    Rev 1.38   Feb 14 2003 16:25:36   linmay
 * added semiannualreport for addressprocess
 * 
 *    Rev 1.37   Feb 06 2003 10:18:18   linmay
 * modified doGetField()
 * 
 *    Rev 1.36   Dec 12 2002 13:48:00   FENGYONG
 * change MFCANBP to BPBASE
 * 
 *    Rev 1.35   Dec 12 2002 11:34:32   FENGYONG
 * fix lost condition problem
 * 
 *    Rev 1.34   Nov 13 2002 14:43:56   YINGBAOL
 * change parameter for iterator
 * 
 *    Rev 1.33   Nov 13 2002 14:14:28   YINGBAOL
 * avoid to validate AccountEntityXref
 * 
 *    Rev 1.32   Oct 30 2002 10:31:12   YINGBAOL
 * sync. up from old PVCS
 * 
 *    Rev 1.32   Oct 11 2002 11:40:38   YINGBAOL
 * change AddrCode to EntityAddrCode for entity mailing
 * 
 *    Rev 1.31   Oct 10 2002 12:52:36   HUANGSHA
 * added fields in delivery method
 * 
 *    Rev 1.30   Oct 08 2002 11:50:02   YINGBAOL
 * view change 
 * 
 *    Rev 1.29   Sep 24 2002 10:48:18   YINGBAOL
 * validate EntityMailing
 * 
 *    Rev 1.28   Sep 23 2002 15:24:18   YINGBAOL
 * more fields and company options added
 * 
 *    Rev 1.27   Sep 19 2002 16:57:06   YINGBAOL
 * add addressCode to Entitylist
 * 
 *    Rev 1.26   Sep 13 2002 15:53:22   YINGBAOL
 * release 49
 * 
 *    Rev 1.25   Aug 29 2002 16:42:34   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.24   Aug 29 2002 12:54:10   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.23   Aug 13 2002 10:33:08   YINGBAOL
 * roll back Name2 for shareholder
 * 
 *    Rev 1.22   Jul 29 2002 16:29:52   YINGBAOL
 * make shareholder not updatebale
 * 
 *    Rev 1.21   Jul 16 2002 12:46:34   FENGYONG
 * Add EntityId leave EntityID
 * 
 *    Rev 1.20   Jul 12 2002 15:21:28   FENGYONG
 * Fix for address entity list
 * 
 *    Rev 1.19   Jun 14 2002 14:42:06   YINGBAOL
 * Add Name2 to shareholder
 * 
 *    Rev 1.18   Jun 11 2002 11:44:26   YINGBAOL
 * create AddressListDialoge for Settlement
 * 
 *    Rev 1.17   Jun 03 2002 16:55:16   HSUCHIN
 * bug fix to doValidateAll to use BFAbstractCBO rather than BFCBO
 * 
 *    Rev 1.16   Jun 03 2002 13:51:12   FENGYONG
 * add name for API
 * 
 *    Rev 1.15   22 May 2002 18:23:48   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.14   27 Mar 2002 19:54:30   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.13   Jun 04 2001 15:25:18   YINGBAOL
 * add doRefresh method
 * 
 *    Rev 1.12   04 Jun 2001 15:06:04   YINGZ
 * fix nasu flow for ssb
 * 
 *    Rev 1.11   15 May 2001 15:38:04   YINGZ
 * data group id clean up
 * 
 *    Rev 1.10   03 May 2001 14:05:14   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.9   Feb 21 2001 11:33:54   YINGZ
 * make api nasu work
 * 
 *    Rev 1.8   Feb 06 2001 14:03:40   YINGZ
 * make changes for api update address to work
 * 
 *    Rev 1.7   15 Dec 2000 12:43:18   PURDYECH
 * Use precompiled header MFCANBPIncludeFirst.hpp.
 * Removed unnecessary header files.
 * 
 *    Rev 1.6   Aug 15 2000 10:28:48   YINGBAOL
 * fix Nasu  and other bugs for C2
 * 
 *    Rev 1.5   Aug 10 2000 17:17:54   KOVACSRO
 * passed AccNum to AddressList.
 * 
 *    Rev 1.4   Aug 02 2000 15:31:58   BUZILA
 * "locale" changes
 * 
 *    Rev 1.3   Jul 17 2000 17:07:30   KOVACSRO
 * Added RegAddress not updatable for Acc. Des. = 2 OR 3
 * 
 *    Rev 1.2   Jun 02 2000 16:52:12   YINGZ
 * fix nasu close problem
 * 
 *    Rev 1.1   Mar 21 2000 11:18:34   HSUCHIN
 * added addrstatus
 * 
 *    Rev 1.0   Feb 15 2000 10:59:30   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.45   Feb 02 2000 18:09:28   BUZILA
 * changes
 * 
 *    Rev 1.44   Feb 02 2000 16:17:56   YINGBAOL
 * ?
 * 
 *    Rev 1.43   Jan 31 2000 18:13:36   YINGBAOL
 * overide validate all
 * 
 *    Rev 1.42   Jan 27 2000 14:45:58   YINGBAOL
 * refresh
 * 
 *    Rev 1.41   Jan 25 2000 18:04:00   YINGBAOL
 * fix
 * 
 *    Rev 1.40   Jan 24 2000 11:57:20   YINGBAOL
 * fix
 * 
 *    Rev 1.39   Jan 23 2000 16:59:26   POPESCUS
 * fixes related to accessing the lists and rolling back a cloned account
 * 
 *    Rev 1.38   Jan 21 2000 16:41:50   YINGBAOL
 * fix
 * 
 *    Rev 1.37   Jan 20 2000 10:41:52   POPESCUS
 * fixes for cloning an address mailing
 * 
 *    Rev 1.36   Jan 19 2000 14:31:14   YINGBAOL
 * getnewitemkey
 * 
 *    Rev 1.35   Jan 17 2000 17:43:00   YINGBAOL
 * fix refresh
 * 
 *    Rev 1.34   Jan 17 2000 11:59:08   YINGBAOL
 * change getGroupId
 * 
 *    Rev 1.33   Jan 14 2000 18:08:50   POPESCUS
 * set the last active account num
 * 
 *    Rev 1.32   Jan 14 2000 16:30:24   YINGBAOL
 * pass accountNum instead of sharehole num and accountNum
 * 
 *    Rev 1.31   Jan 08 2000 14:32:54   POPESCUS
 * added the datagroupid when quering for children lists
 * 
 *    Rev 1.30   Jan 06 2000 12:51:34   POPESCUS
 * init should get the current group id
 * 
 *    Rev 1.29   Jan 04 2000 18:01:26   DT24433
 * removed substitute lists except for grid related ones
 * 
 *    Rev 1.28   Dec 30 1999 10:38:10   YINGBAOL
 * added NFCAddr field etc
 * 
 *    Rev 1.27   Dec 13 1999 10:41:44   YINGBAOL
 * check in for release
 * 
 *    Rev 1.26   Dec 12 1999 11:12:46   YINGBAOL
 * fix Nasu problem
 * 
 *    Rev 1.25   Dec 03 1999 16:27:24   YINGBAOL
 * fix
 * 
 *    Rev 1.24   Dec 03 1999 14:08:34   VASILEAD
 * fixes
 * 
 *    Rev 1.23   Dec 02 1999 17:56:46   POPESCUS
 * Fixed crashes in search
 * 
 *    Rev 1.22   Dec 01 1999 14:18:48   POPESCUS
 * Nasu fixes
 * 
 *    Rev 1.21   Dec 01 1999 09:23:38   VASILEAD
 * NASU fixes
 * 
 *    Rev 1.20   Nov 30 1999 19:41:22   YINGBAOL
 * change entityAddress sync
 * 
 *    Rev 1.19   Nov 30 1999 15:24:24   YINGBAOL
 * modify account entity cross ref.
 * 
 *    Rev 1.18   Nov 25 1999 12:02:28   YINGBAOL
 * check in for M2 release
 * 
 *    Rev 1.17   Nov 24 1999 14:12:44   YINGBAOL
 * ckeck in for sync
 * 
 *    Rev 1.16   Nov 18 1999 16:13:24   YINGBAOL
 * Split view 43 sync
 * 
 *    Rev 1.15   Nov 12 1999 15:24:58   VASILEAD
 * Changed dramatically view43
 * 
 *    Rev 1.14   Nov 03 1999 11:57:28   YINGBAOL
 * check in for sync
 * 
 *    Rev 1.13   Nov 02 1999 15:58:26   YINGBAOL
 * fix
 * 
 *    Rev 1.11   Oct 29 1999 11:30:12   BUZILA
 * changing WorkSessionDetails into a BFBase descendant
 * 
 *    Rev 1.10   Oct 29 1999 09:38:38   YINGBAOL
 * new CBO support
 * 
 *    Rev 1.9   24 Sep 1999 18:25:30   HUANGSHA
 * Fixed bug
 * 
 *    Rev 1.8   Aug 26 1999 10:48:06   DT24433
 * changed setList to setContainer
 * 
 *    Rev 1.7   Aug 25 1999 13:48:26   DT24433
 * finished removing fielddetails array
 * 
 *    Rev 1.6   Aug 25 1999 14:24:24   YINGBAOL
 * check in for Jerry
 * 
 *    Rev 1.5   Aug 18 1999 11:17:02   YINGBAOL
 * Modify for test  inc2
 * 
 *    Rev 1.4   Jul 27 1999 16:32:48   VASILEAD
 * The address selected on entities screen is also selected on address book screen
 * 
 *    Rev 1.3   Jul 20 1999 11:13:30   VASILEAD
 * New conditions update
 * 
 *    Rev 1.2   Jul 12 1999 18:34:24   POPESCUS
 * Removed all the ddincludes
 * 
 *    Rev 1.1   Jul 08 1999 10:01:48   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
