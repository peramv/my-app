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
//    Copyright 1999 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : AccountMailingInfo.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : 10/06/99
//
// ^CLASS    : AccountMailingInfo
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "accountmailinginfo.hpp"
#include "accountmailinglist.hpp"
#include "addresslist.hpp"

#include <ifastdataimpl\dse_dstc0043_vw.hpp>
#include <ifastdataimpl\dse_dstc0042_vw.hpp>
#include <ifastdataimpl\dse_dstc0113_vw.hpp>
#include <ifastdataimpl\dse_dstc0071_vw.hpp>
#include <ifastdataimpl\dse_dstc0114_req.hpp>
#include "mfaccount.hpp"
#include "shareholder.hpp"
#include "DocumentTypeList.hpp"
#include "mgmtco.hpp"
#include "entity.hpp"
#include "accountentityxref.hpp"
#include "DefaultMailOptionList.hpp"
#include "DocumentType.hpp"
#include "taxtyperule.hpp"

namespace  
{
   const I_CHAR * const ADDRESS_CODE_K    = I_( "K0123456789" );
   const I_CHAR * const YES               = I_( "Y" );
   const I_CHAR * const NO                = I_( "N" );
   const I_CHAR * const DEFAULT           = I_( "D" );
   const I_CHAR * const ALLOWED_DEFAULT_DOC  = I_( "02,13" );
}

namespace AUTHORIZATION_CODE
{
   extern const I_CHAR * const DEFAULT;
   extern const I_CHAR * const AUTHORIZATION;
   extern const I_CHAR * const PERMANENT;
   extern const I_CHAR * const RET_MAIL;
   extern const I_CHAR * const UNCLAIMED_PROPERTY;
}

namespace CND
{
   extern const long ERR_NO_EMAIL_ADDRESS;
   extern const long ERR_NO_FAX_AVAILABLE;
   extern const long ERR_NO_MAIL_TO_SUPPRESS;
   extern const long ERR_WAIVE_PAPER_CANNOT_BE_YES;
   extern const long ERR_MAIL_OPTION_CANNOT_BE_ALL_NO;
   extern const long ERR_MAIL_CANNOT_BE_NO_FOR_NO_WAIVE;
   extern const long ERR_MAIL_CANNOT_BE_YES_FOR_YES_WAIVE;
   extern const long WARNING_DOCUMENT_TYPE_IS_ONHOLD;
   extern const long ERR_NO_HOLD_FOR_RETURN_MAIL;
   extern const long WARN_DATA_UPDATE_IMPACTS_EXTERNAL_ENV_SICAV;
   extern const long WARN_DATA_UPDATE_IMPACTS_EXTERNAL_ENV_OEIC;
   extern const long WARN_WAIVE_PAPER_CANNOT_BE_YES;
   extern const long WARN_MAIL_OPTION_CANNOT_BE_ALL_NO;
   extern const long WARN_MAIL_CANNOT_BE_NO_FOR_NO_WAIVE;
   extern const long WARN_NO_MAIL_TO_SUPPRESS;
}

namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const WAIVE_PAPER_CANNOT_BE_YES;
   extern CLASS_IMPORT I_CHAR * const MAIL_OPTION_CANNOT_BE_ALL_NO;
   extern CLASS_IMPORT I_CHAR * const MAIL_CANNOT_BE_NO_FOR_NO_WAIVE;
   extern CLASS_IMPORT I_CHAR * const NO_MAIL_TO_SUPPRESS;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId AcctDesignation;
   extern CLASS_IMPORT const BFTextFieldId TaxType;
   extern CLASS_IMPORT const BFNumericFieldId EntityId;
   extern CLASS_IMPORT const BFTextFieldId Email;
   extern CLASS_IMPORT const BFTextFieldId HomeFax;
   extern CLASS_IMPORT const BFTextFieldId BusinessFax;
   extern CLASS_IMPORT const BFTextFieldId OPDeliveryOption;
   extern CLASS_IMPORT const BFTextFieldId OPDeliveryMethods;
   extern CLASS_IMPORT const BFTextFieldId CnsntToWaive;   
   extern CLASS_IMPORT const BFTextFieldId ContributionOnHold;
   extern CLASS_IMPORT const BFTextFieldId Authority;
   extern CLASS_IMPORT const BFTextFieldId Authorization;  
   extern CLASS_IMPORT const BFTextFieldId StmtFrequency;
   extern CLASS_IMPORT const BFTextFieldId StmtFreqDefault;
   extern CLASS_IMPORT const BFTextFieldId StmtFreqList;
   extern CLASS_IMPORT const BFTextFieldId StmtFrequencyDisabled;
   extern CLASS_IMPORT const BFTextFieldId ListDocType;
   extern CLASS_IMPORT const BFTextFieldId DocumentMail;
   extern CLASS_IMPORT const BFTextFieldId Yes_NO;
   extern CLASS_IMPORT const BFTextFieldId DocTypeMailMapping;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
//    Field DD Id,                           State Flags,      Group Flags 
   { ifds::RunMode,                          BFCBO::NONE,         0 }, 

   { ifds::RegAddr,                          BFCBO::REQUIRED,     0 }, 
   { ifds::DivConfAddr,                      BFCBO::REQUIRED,     0 }, 
   { ifds::DivChqAddr,                       BFCBO::NONE,         0 }, 
   { ifds::TxnConfAddr,                      BFCBO::REQUIRED,     0 }, 
   { ifds::DupConfAddr,                      BFCBO::NONE,         0 }, 
   { ifds::StmtAddr,                         BFCBO::REQUIRED,     0 }, 
   { ifds::DupStmtAddr,                      BFCBO::NONE,         0 }, 
   { ifds::CertAddr,                         BFCBO::NONE,         0 }, 
   { ifds::TaxAddr,                          BFCBO::NONE,         0 }, 
   { ifds::LetAddr,                          BFCBO::NONE,         0 }, 
   { ifds::BenAddr,                          BFCBO::REQUIRED,     0 }, 
   { ifds::NFCAddr,                          BFCBO::NONE,         0 }, 
   { ifds::ContrAddr,                        BFCBO::NONE,         0 }, 
   { ifds::AnnlRptsAddr,                     BFCBO::NONE,         0 }, 
   { ifds::ProspAddr,                        BFCBO::NONE,         0 }, 
   { ifds::ContributionAddr,                 BFCBO::NONE,         0 }, 
   { ifds::SmAnnlMRFPAddr,                   BFCBO::NONE,         0 }, 
   { ifds::AnnlMRFPAddr,                     BFCBO::NONE,         0 }, 

//hold
   { ifds::RegOnHold,                        BFCBO::NONE,         0 }, 
   { ifds::DivConfOnHold,                    BFCBO::NONE,         0 }, 
   { ifds::DivChqOnHold,                     BFCBO::NONE,         0 }, 
   { ifds::TxnConfOnHold,                    BFCBO::NONE,         0 }, 
   { ifds::DupConfOnHold,                    BFCBO::NONE,         0 }, 
   { ifds::StmtOnHold,                       BFCBO::NONE,         0 }, 
   { ifds::DupStmtOnHold,                    BFCBO::NONE,         0 }, 
   { ifds::CertOnHold,                       BFCBO::NONE,         0 }, 
   { ifds::TaxOnHold,                        BFCBO::NONE,         0 }, 
   { ifds::LetOnHold,                        BFCBO::NONE,         0 }, 
   { ifds::BenOnHold,                        BFCBO::NONE,         0 },
   { ifds::NFConHold,                        BFCBO::NONE,         0 }, 
   { ifds::SemiAnnualOnHold,                 BFCBO::NONE,         0 },
   { ifds::ProspHold,                        BFCBO::NONE,         0 },
   { ifds::ContrHold,                        BFCBO::NONE,         0 }, 
   { ifds::AnnlRptsHold,                     BFCBO::NONE,         0 }, 
   { ifds::AnnlMRFPHold,                     BFCBO::NONE,         0 }, 
   { ifds::SmAnnlMRFPHold,                   BFCBO::NONE,         0 }, 
   { ifds::ContributionOnHold,               BFCBO::NONE,         0 }, 

// Authorization
   { ifds::RegAuth,                          BFCBO::REQUIRED,     0 }, 
   { ifds::DivConfAuth,                      BFCBO::REQUIRED,     0 }, 
   { ifds::DivChqAuth,                       BFCBO::REQUIRED,     0 }, 
   { ifds::TxnConfAuth,                      BFCBO::REQUIRED,     0 }, 
   { ifds::DupConfAuth,                      BFCBO::REQUIRED,     0 }, 
   { ifds::StmtAuth,                         BFCBO::REQUIRED,     0 }, 
   { ifds::DupStmtAuth,                      BFCBO::REQUIRED,     0 }, 
   { ifds::CertAuth,                         BFCBO::REQUIRED,     0 }, 
   { ifds::TaxAuth,                          BFCBO::REQUIRED,     0 }, 
   { ifds::LetAuth,                          BFCBO::REQUIRED,     0 }, 
   { ifds::BenAuth,                          BFCBO::REQUIRED,     0 },
   { ifds::NFConAuth,                        BFCBO::REQUIRED,     0 }, 
   { ifds::SmAnnlRptsAuth,                   BFCBO::REQUIRED,     0 },
   { ifds::ProspAuth,                        BFCBO::REQUIRED,     0 },
   { ifds::ContrAuth,                        BFCBO::REQUIRED,     0 }, 
   { ifds::AnnlRptsAuth,                     BFCBO::REQUIRED,     0 }, 
   { ifds::AnnlMRFPAuth,                     BFCBO::REQUIRED,     0 }, 
   { ifds::SmAnnlMRFPAuth,                   BFCBO::REQUIRED,     0 }, 
   { ifds::Authorization,                    BFCBO::REQUIRED,     0 }, 
   { ifds::ContributionAuth,                 BFCBO::REQUIRED,     0 }, 
   { ifds::StmtFrequency,                    BFCBO::NONE,         0 },
   { ifds::StmtFreqDefault,                  BFCBO::NONE,         0 },
   { ifds::StmtFreqList,                     BFCBO::NONE,         0 },
   { ifds::StmtFrequencyDisabled,            BFCBO::NONE,         0 },

   { ifds::DupConfCopies,                    BFCBO::NONE,     0 }, 
   { ifds::DupStmtCopies,                    BFCBO::NONE,     0 }, 
   { ifds::SATxnConfCode,                    BFCBO::NONE,     0 }, 
   { ifds::SADivConfCode,                    BFCBO::NONE,     0 }, 
   { ifds::SALettersCode,                    BFCBO::NONE,     0 }, 

   { ifds::AcctMstrVer,                      BFCBO::NONE,     0 }, 
   { ifds::AccountNum,                       BFCBO::NONE,     0 }, 
   { ifds::AcctMstrRid,                      BFCBO::NONE,     0 }, 

   { ifds::TaxSuppress,                      BFCBO::NONE,     0 }, 
   { ifds::TaxWaive,                         BFCBO::NONE,     0 }, 
   { ifds::TaxMail,                          BFCBO::NONE,     0 }, 
   { ifds::TaxFax,                           BFCBO::NONE,     0 },
   { ifds::TaxCD,                            BFCBO::NONE,     0 }, 
   { ifds::TaxEmail,                         BFCBO::NONE,     0 }, 
   { ifds::LetSuppress,                      BFCBO::NONE,     0 }, 
   { ifds::LetWaive,                         BFCBO::NONE,     0 }, 
   { ifds::LetMail,                          BFCBO::NONE,     0 }, 
   { ifds::LetFax,                           BFCBO::NONE,     0 },
   { ifds::LetCD,                            BFCBO::NONE,     0 }, 
   { ifds::LetEmail,                         BFCBO::NONE,     0 }, 
   { ifds::CertSuppress,                     BFCBO::NONE,     0 }, 
   { ifds::CertWaive,                        BFCBO::NONE,     0 }, 
   { ifds::CertMail,                         BFCBO::NONE,     0 }, 
   { ifds::CertFax,                          BFCBO::NONE,     0 },
   { ifds::CertCD,                           BFCBO::NONE,     0 }, 
   { ifds::CertEmail,                        BFCBO::NONE,     0 }, 
   { ifds::DivConfSuppress,                  BFCBO::NONE,     0 }, 
   { ifds::DivConfWaive,                     BFCBO::NONE,     0 }, 
   { ifds::DivConfMail,                      BFCBO::NONE,     0 }, 
   { ifds::DivConfFax,                       BFCBO::NONE,     0 },
   { ifds::DivConfCD,                        BFCBO::NONE,     0 }, 
   { ifds::DivConfEmail,                     BFCBO::NONE,     0 }, 

   { ifds::DivChqSuppress,                   BFCBO::NONE,     0 }, 
   { ifds::DivChqWaive,                      BFCBO::NONE,     0 }, 
   { ifds::DivChqMail,                       BFCBO::NONE,     0 }, 
   { ifds::DivChqFax,                        BFCBO::NONE,     0 },
   { ifds::DivChqCD,                         BFCBO::NONE,     0 }, 
   { ifds::DivChqEmail,                      BFCBO::NONE,     0 }, 
   { ifds::ContrSuppress,                    BFCBO::NONE,     0 }, 
   { ifds::ContrWaive,                       BFCBO::NONE,     0 }, 
   { ifds::ContrMail,                        BFCBO::NONE,     0 }, 
   { ifds::ContrFax,                         BFCBO::NONE,     0 },
   { ifds::ContrCD,                          BFCBO::NONE,     0 }, 
   { ifds::ContrEmail,                       BFCBO::NONE,     0 }, 
   { ifds::RegSuppress,                      BFCBO::NONE,     0 }, 
   { ifds::RegWaive,                         BFCBO::NONE,     0 }, 
   { ifds::RegMail,                          BFCBO::NONE,     0 }, 
   { ifds::RegFax,                           BFCBO::NONE,     0 },
   { ifds::RegCD,                            BFCBO::NONE,     0 }, 
   { ifds::RegEmail,                         BFCBO::NONE,     0 }, 

   { ifds::AnnlRptsSuppress,                 BFCBO::NONE,     0 }, 
   { ifds::AnnlRptsWaive,                    BFCBO::NONE,     0 }, 
   { ifds::AnnlRptsMail,                     BFCBO::NONE,     0 }, 
   { ifds::AnnlRptsFax,                      BFCBO::NONE,     0 },
   { ifds::AnnlRptsCD,                       BFCBO::NONE,     0 }, 
   { ifds::AnnlRptsEmail,                    BFCBO::NONE,     0 }, 
   { ifds::ProspSuppress,                    BFCBO::NONE,     0 }, 
   { ifds::ProspWaive,                       BFCBO::NONE,     0 }, 
   { ifds::ProspMail,                        BFCBO::NONE,     0 }, 
   { ifds::ProspFax,                         BFCBO::NONE,     0 },
   { ifds::ProspCD,                          BFCBO::NONE,     0 }, 
   { ifds::ProspEmail,                       BFCBO::NONE,     0 }, 
   { ifds::BenSuppress,                      BFCBO::NONE,     0 }, 
   { ifds::BenWaive,                         BFCBO::NONE,     0 }, 
   { ifds::BenMail,                          BFCBO::NONE,     0 }, 
   { ifds::BenFax,                           BFCBO::NONE,     0 },
   { ifds::BenCD,                            BFCBO::NONE,     0 }, 
   { ifds::BenEmail,                         BFCBO::NONE,     0 }, 

   { ifds::StmtSuppress,                     BFCBO::NONE,     0 }, 
   { ifds::StmtWaive,                        BFCBO::NONE,     0 }, 
   { ifds::StmtMail,                         BFCBO::NONE,     0 }, 
   { ifds::StmtFax,                          BFCBO::NONE,     0 },
   { ifds::StmtCD,                           BFCBO::NONE,     0 }, 
   { ifds::StmtEmail,                        BFCBO::NONE,     0 }, 
   { ifds::DupStmtSuppress,                  BFCBO::NONE,     0 }, 
   { ifds::DupStmtWaive,                     BFCBO::NONE,     0 }, 
   { ifds::DupStmtMail,                      BFCBO::NONE,     0 }, 
   { ifds::DupStmtFax,                       BFCBO::NONE,     0 },
   { ifds::DupStmtCD,                        BFCBO::NONE,     0 }, 
   { ifds::DupStmtEmail,                     BFCBO::NONE,     0 }, 

   { ifds::NFConfSuppress,                   BFCBO::NONE,     0 }, 
   { ifds::NFConfWaive,                      BFCBO::NONE,     0 }, 
   { ifds::NFConfMail,                       BFCBO::NONE,     0 }, 
   { ifds::NFConfFax,                        BFCBO::NONE,     0 },
   { ifds::NFConfCD,                         BFCBO::NONE,     0 }, 
   { ifds::NFConfEmail,                      BFCBO::NONE,     0 }, 
   { ifds::TxnConfSuppress,                  BFCBO::NONE,     0 }, 
   { ifds::TxnConfWaive,                     BFCBO::NONE,     0 }, 
   { ifds::TxnConfMail,                      BFCBO::NONE,     0 }, 
   { ifds::TxnConfFax,                       BFCBO::NONE,     0 },
   { ifds::TxnConfCD,                        BFCBO::NONE,     0 }, 
   { ifds::TxnConfEmail,                     BFCBO::NONE,     0 }, 

   { ifds::DupConfSuppress,                  BFCBO::NONE,     0 }, 
   { ifds::DupConfWaive,                     BFCBO::NONE,     0 }, 
   { ifds::DupConfMail,                      BFCBO::NONE,     0 }, 
   { ifds::DupConfFax,                       BFCBO::NONE,     0 },
   { ifds::DupConfCD,                        BFCBO::NONE,     0 }, 
   { ifds::DupConfEmail,                     BFCBO::NONE,     0 },

   { ifds::SemiAnnualSuppress,               BFCBO::NONE,     0 }, 
   { ifds::SemiAnnualWaive,                  BFCBO::NONE,     0 }, 
   { ifds::SemiAnnualMail,                   BFCBO::NONE,     0 }, 
   { ifds::SemiAnnualFax,                    BFCBO::NONE,     0 },
   { ifds::SemiAnnualCD,                     BFCBO::NONE,     0 }, 
   { ifds::SemiAnnualEmail,                  BFCBO::NONE,     0 }, 
   { ifds::SemiAnnualAddr,                   BFCBO::NONE,     0 }, 
   { ifds::TaxEpost,                         BFCBO::NONE,     0 }, 
   { ifds::LetEpost,                         BFCBO::NONE,     0 }, 
   { ifds::CertEpost,                        BFCBO::NONE,     0 }, 
   { ifds::DivConfEpost,                     BFCBO::NONE,     0 }, 
   { ifds::DivChqEpost,                      BFCBO::NONE,     0 }, 
   { ifds::ContrEPost,                       BFCBO::NONE,     0 }, 
   { ifds::RegEpost,                         BFCBO::NONE,     0 }, 
   { ifds::AnnlRptsEpost,                    BFCBO::NONE,     0 }, 
   { ifds::ProspEpost,                       BFCBO::NONE,     0 }, 
   { ifds::BenEpost,                         BFCBO::NONE,     0 }, 
   { ifds::StmtEpost,                        BFCBO::NONE,     0 }, 
   { ifds::DupStmtEpost,                     BFCBO::NONE,     0 }, 
   { ifds::NFConfEpost,                      BFCBO::NONE,     0 }, 
   { ifds::TxnConfEpost,                     BFCBO::NONE,     0 }, 
   { ifds::DupConfEpost,                     BFCBO::NONE,     0 }, 
   { ifds::SemiAnnualEpost,                  BFCBO::NONE,     0 },
   { ifds::ContributionSuppress,             BFCBO::NONE,     0 }, 
   { ifds::ContributionWaive,                BFCBO::NONE,     0 }, 
   { ifds::ContributionMail,                 BFCBO::NONE,     0 }, 
   { ifds::ContributionFax,                  BFCBO::NONE,     0 }, 
   { ifds::ContributionCD,                   BFCBO::NONE,     0 }, 
   { ifds::ContributionEmail,                BFCBO::NONE,     0 }, 
   { ifds::ContributionEpost,                BFCBO::NONE,     0 }, 
   { ifds::AnnlMRFPSuppress,                 BFCBO::NONE,     0 }, 
   { ifds::AnnlMRFPWaive,                    BFCBO::NONE,     0 }, 
   { ifds::AnnlMRFPMail,                     BFCBO::NONE,     0 }, 
   { ifds::AnnlMRFPFax,                      BFCBO::NONE,     0 }, 
   { ifds::AnnlMRFPCD,                       BFCBO::NONE,     0 }, 
   { ifds::AnnlMRFPEmail,                    BFCBO::NONE,     0 }, 
   { ifds::AnnlMRFPEpost,                    BFCBO::NONE,     0 }, 
   { ifds::SmAnnlMRFPSuppress,               BFCBO::NONE,     0 }, 
   { ifds::SmAnnlMRFPWaive,                  BFCBO::NONE,     0 }, 
   { ifds::SmAnnlMRFPMail,                   BFCBO::NONE,     0 }, 
   { ifds::SmAnnlMRFPFax,                    BFCBO::NONE,     0 }, 
   { ifds::SmAnnlMRFPCD,                     BFCBO::NONE,     0 }, 
   { ifds::SmAnnlMRFPEmail,                  BFCBO::NONE,     0 }, 
   { ifds::SmAnnlMRFPEpost,                  BFCBO::NONE,     0 }, 
   
   // for use in on-the fly substitution set replacement only
   { ifds::Yes_NO,                           BFCBO::NOT_ON_HOST,     0 },
   { ifds::DocumentMail,                     BFCBO::NOT_ON_HOST,     0 },

   // use as look up table for rowkey for mail column at GUI level
   { ifds::DocTypeMailMapping,               BFCBO::NOT_ON_HOST,     0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME = I_( "AccountMailingInfo" );
}

//******************************************************************************
AccountMailingInfo::AccountMailingInfo( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
, _bWorkingFlag( false )      // ??? is this correct?
, _shrNum( I_( "" ) )
, objectKey_( I_( "" ) )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL );

   setupMailing();
}

//******************************************************************************
AccountMailingInfo::~AccountMailingInfo()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   clearMailmap();
}

//******************************************************************************
SEVERITY AccountMailingInfo::init( const BFDataGroupId& idDataGroup, const DString& shrNum )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   _shrNum = shrNum;
   initWithDefaultValues(idDataGroup);
   setDefaultValue( idDataGroup );
   setDefaultStatementfrequency(idDataGroup);
   setMailingFieldsReadonly(idDataGroup );
   setNonDataBaseFields( idDataGroup );
   setupSubstitutionList( idDataGroup);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AccountMailingInfo::init( const BFData &InstData, const DString& shrNum )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   _shrNum = shrNum;

   DString locDump;
   InstData.getAllValues( locDump, true, true );
   attachDataObject( const_cast<BFData&>(InstData), false, true );  //true
   setUpMailingSubstitute( BF::HOST );
   setMailingFieldsReadonly(BF::HOST);
   setNonDataBaseFields( BF::HOST);
   setStatementfrequency( BF::HOST); 
   setupSubstitutionList( BF::HOST);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool AccountMailingInfo::isAllDigit( const DString& strValue )
{
   return strValue.isAllDigits();
}

//******************************************************************************
void AccountMailingInfo::setWorkingFlag( bool Flag )
{
   _bWorkingFlag = Flag;
}

//******************************************************************************
bool AccountMailingInfo::isWorking()
{
   return _bWorkingFlag;
}

//******************************************************************************
void AccountMailingInfo::setInitialStrKey( const DString& strKey )
{
   objectKey_ = strKey;
}

//******************************************************************************
const DString *AccountMailingInfo::getInitialStrKey()
{
   return &objectKey_;
}

//******************************************************************************
SEVERITY AccountMailingInfo::doValidateField( const BFFieldId& idField,
                                              const DString& strValue, 
                                              const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );

   setWorkingFlag( true );
   validateFax(idField,strValue, idDataGroup);
   validateEmail(idField,strValue, idDataGroup);
   validateMail( idField,strValue, idDataGroup);
   validateAccountHold( idField, idDataGroup );

   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************
SEVERITY AccountMailingInfo::validateAccountHold( const BFFieldId& idField,const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateAccountHolde" ) );

   MAIL_MAP_ITER iter = _mailmap.begin();
   while( iter != _mailmap.end() )
   {
      bool bFind =  (*iter).second->getFax()      == idField || 
                    (*iter).second->getMail()     == idField ||
                    (*iter).second->getCD()       == idField || 
                    (*iter).second->getEmail()    == idField ||
                    (*iter).second->getSuppress() == idField;
      if(bFind )
      {
         DString dstrHold;
         getField((*iter).second->getHold(),dstrHold,idDataGroup,false);
         dstrHold.strip();
         if(dstrHold == YES )
         {
            DString idiStr;
            addIDITagValue( idiStr, I_("DOCTYPE"), (*iter).first );
            ADDCONDITIONFROMFILEIDI( CND::WARNING_DOCUMENT_TYPE_IS_ONHOLD, idiStr.c_str() );
         }
      }
      ++iter;
   }

   return GETCURRENTHIGHESTSEVERITY();
}
//***********************************************************************************
//public method, it is called by entitymailingInfo
bool AccountMailingInfo::isDocumentTypeOnHold(const DString& docType,const BFDataGroupId& idDataGroup)
{
   bool bRet = false;
   MAIL_MAP_ITER iter = _mailmap.begin();
   while( iter != _mailmap.end() )
   {
      if( (*iter).second->getCode() == docType  )
      {
         DString dstrHold;
         getField((*iter).second->getHold(),dstrHold,idDataGroup,false);
         dstrHold.strip();
         if(dstrHold == YES ){
            bRet = true;
            break;
         }
      }
      ++iter;
   }
   return bRet;
}

//******************************************************************************
SEVERITY AccountMailingInfo::setDefaultValue( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setDefaultValue" ) );

   DString dstrDefaultValue[12] = { I_("01"), I_("01"), I_("01"), I_("01"), I_("01"), I_("01"), I_("01"), I_("01"), I_("01"), I_("01"), I_("01"), I_("01")};

   DString strAddrCode( I_( "02" ) );
   Shareholder* pShareholder;
   if ( getWorkSession().getShareholder( idDataGroup, _shrNum, pShareholder ) <= WARNING )
   {
      AddressList* pAddressList = NULL;
      bool bValid = false;

      if ( pShareholder->getAddressList( pAddressList, idDataGroup ) <= WARNING )
      {
         DString strAcctDes, dstrTaxType, dstrAccountNum;

         pShareholder->getField( ifds::AcctDesignation, strAcctDes, idDataGroup );
         dstrAccountNum = ( dynamic_cast <AccountMailingList*> ( getParent() ) )->getAccountNum ( );
         MFAccount *pMFAccount = NULL;
         getWorkSession().getMFAccount ( idDataGroup, dstrAccountNum, pMFAccount,NO,NULL_STRING,false );
         strAcctDes.strip().stripLeading( '0' );
         if ( pMFAccount )
            pMFAccount->getField( ifds::TaxType, dstrTaxType, idDataGroup );
         if ( (strAcctDes == I_("2") || strAcctDes == I_("3")) && pAddressList->IsValidateAddressCode( strAddrCode, idDataGroup, bValid ) )
         {
            if ( !getWorkSession().isNonRegLike( dstrTaxType ) )
               dstrDefaultValue [1] = dstrDefaultValue [3] = dstrDefaultValue [5] = dstrDefaultValue [9] = dstrDefaultValue [10] = I_( "02 " );
            else
               dstrDefaultValue [1] = dstrDefaultValue [3] = dstrDefaultValue [5] = dstrDefaultValue [8] = dstrDefaultValue [9] = dstrDefaultValue [10] = I_( "02 " );

            dstrDefaultValue [11] = I_( "02 " );
         }
      }
   }

   setFieldNoValidate( ifds::RegAddr, dstrDefaultValue[0], idDataGroup,false,true,false,false );
   setFieldNoValidate( ifds::DivConfAddr, dstrDefaultValue[1], idDataGroup,false,true,false,false );
   setFieldNoValidate( ifds::DivChqAddr, dstrDefaultValue[2], idDataGroup,false,true,false,false );
   setFieldNoValidate( ifds::TxnConfAddr, dstrDefaultValue[3], idDataGroup,false,true,false,false );
   setFieldNoValidate( ifds::DupConfAddr, dstrDefaultValue[4], idDataGroup,false,true,false,false );
   setFieldNoValidate( ifds::StmtAddr, dstrDefaultValue[5], idDataGroup ,false,true,false,false);
   setFieldNoValidate( ifds::DupStmtAddr, dstrDefaultValue[6], idDataGroup ,false,true,false,false);
   setFieldNoValidate( ifds::CertAddr, dstrDefaultValue[7], idDataGroup,false,true,false,false );
   setFieldNoValidate( ifds::TaxAddr, dstrDefaultValue[8], idDataGroup,false,true,false,false );
   setFieldNoValidate( ifds::LetAddr, dstrDefaultValue[9], idDataGroup ,false,true,false,false);
   setFieldNoValidate( ifds::BenAddr, dstrDefaultValue[10], idDataGroup ,false,true,false,false);
   setFieldNoValidate( ifds::ContributionAddr, dstrDefaultValue[0], idDataGroup ,false,true,false,false);

   setFieldNoValidate( ifds::ContrAddr, dstrDefaultValue[3], idDataGroup ,false,true,false,false); // contract notes default to confirmation

   setFieldNoValidate( ifds::AnnlRptsAddr, dstrDefaultValue[5], idDataGroup,false,true,false,false ); // Annual Reports default to statement
   setFieldNoValidate( ifds::ProspAddr, dstrDefaultValue[5], idDataGroup,false,true,false,false ); // Prospects default to statement
   setFieldNoValidate( ifds::SemiAnnualAddr, dstrDefaultValue[5], idDataGroup ,false,true,false,false); //SemiAnnualAddr default to statement address

   setFieldNoValidate( ifds::AnnlMRFPAddr, dstrDefaultValue[5], idDataGroup,false,true,false,false ); // Prospects default to statement
   setFieldNoValidate( ifds::SmAnnlMRFPAddr, dstrDefaultValue[5], idDataGroup ,false,true,false,false); //SemiAnnualAddr default to statement address

   setFieldNoValidate( ifds::NFCAddr, dstrDefaultValue[11], idDataGroup ,false,true,false,false); //Non Fin Confirm Addr default to statement address
   bool bFindDefHold = false;
   DefaultMailOptionList* pDefaultMailOptionList = NULL;
   if( getMgmtCo().getDefaultMailOptionList( pDefaultMailOptionList ) <= WARNING )
   {
      bFindDefHold = true;
   }

   MAIL_MAP_ITER iter =  _mailmap.begin();
   while( iter != _mailmap.end() )
   {
      DString strDefDeliveryOption;
      pDefaultMailOptionList->getDefaultDeliveryOptionFlags(strDefDeliveryOption ,(*iter).second->getCode() ); 

      if(strDefDeliveryOption.strip().upperCase().empty())
      {
         // env that not support(DefDeliveryOption is blank) still use hardcode as original logic
         setFieldNoValidate((*iter).second->getEmail(),NO,idDataGroup,false,true,false,false); 
         setFieldNoValidate((*iter).second->getFax(),NO,idDataGroup,false,true,false,false); 
         setFieldNoValidate((*iter).second->getCD(),NO,idDataGroup,false,true,false,false); 
         setFieldNoValidate((*iter).second->getEpost(),NO,idDataGroup,false,true,false,false); 
         setFieldNoValidate((*iter).second->getMail(),YES,idDataGroup,false,true,false,false); 
      }
      else
      {
         DString strPos1 =  strDefDeliveryOption.substr (0, 1); // mail
         DString strPos2 =  strDefDeliveryOption.substr (1, 1); // email
         DString strPos3 =  strDefDeliveryOption.substr (2, 1); // fax
         DString strPos4 =  strDefDeliveryOption.substr (3, 1); // cd
         DString strPos5 =  strDefDeliveryOption.substr (4, 1); // epost
               
         setFieldNoValidate((*iter).second->getEmail(),strPos2,idDataGroup,false,true,false,false); 
         setFieldNoValidate((*iter).second->getFax(),strPos3,idDataGroup,false,true,false,false); 
         setFieldNoValidate((*iter).second->getCD(),strPos4,idDataGroup,false,true,false,false); 
         setFieldNoValidate((*iter).second->getEpost(),strPos5,idDataGroup,false,true,false,false); 
         setFieldNoValidate((*iter).second->getMail(),strPos1,idDataGroup,false,true,false,false); 
      }

      setFieldNoValidate((*iter).second->getWaive(),NO,idDataGroup,false,true,false,false); 
      setFieldNoValidate((*iter).second->getSuppress(),NO,idDataGroup,false,true,false,false); 
      setFieldNoValidate((*iter).second->getAuthorize(),I_("D"),idDataGroup,false,true,false,false); 

      if( bFindDefHold )
      {
         DString hold = pDefaultMailOptionList->getDefaultHoldFlag ( (*iter).second->getCode() );  // we may need to supply fund group here
         setFieldNoValidate((*iter).second->getHold(),hold,idDataGroup,false,true,false,false);       
      }
      ++ iter;
   }
//   setFieldNoValidate(ifds::ContrHold,NO,idDataGroup,false,true,false,false); 
//   setFieldNoValidate(ifds::AnnlRptsHold,NO,idDataGroup,false,true,false,false); 
//   setFieldNoValidate(ifds::ProspHold,NO,idDataGroup,false,true,false,false); 
//setFieldNoValidate(ifds::SemiAnnualSuppress,YES,idDataGroup,false,true,false,false);
//   setFieldNoValidate(ifds::SemiAnnualOnHold,NO,idDataGroup,false,true,false,false);
//   setFieldNoValidate(ifds::ContributionOnHold,NO,idDataGroup,false,true,false,false);

   setUpdatedFlag( ifds::RegAddr, idDataGroup, true );

   CLEARCONDITIONSFRAMECURRENT();

   return GETCURRENTHIGHESTSEVERITY();
}

//***************************************************************************
SEVERITY AccountMailingInfo::authorizRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "authorizRelatedChanges" ) );   

   MAIL_MAP_ITER iter = _mailmap.begin();
   while( iter != _mailmap.end() )
   {
      if( (*iter).second->getAuthorize() == idField  && idField != ifds::ContrAuth )
      {
         DString authorize;
         getField(idField,authorize,idDataGroup,false);
         authorize.strip().upperCase();
         if( idField == ifds::TxnConfAuth )
         {
            setFieldNoValidate(ifds::ContrAuth,authorize,idDataGroup,false,true,true,false);
         }
         DefaultMailOptionList* pDefaultMailOptionList = NULL;
         if( getMgmtCo().getDefaultMailOptionList( pDefaultMailOptionList ) <= WARNING )
         {
            if( authorize == I_("D") ) //default
            {
               DString hold = pDefaultMailOptionList->getDefaultHoldFlag( (*iter).second->getCode() ); // we may need to supply fund group here
               hold.strip().upperCase();
               setFieldNoValidate((*iter).second->getHold(),hold,idDataGroup,false,true,true,false);
               if( idField == ifds::TxnConfAuth )// contract notes follows confirmation
               {
                  setFieldNoValidate(ifds::ContrHold,hold,idDataGroup,false,true,true,false);
               }
            }
            else if ( authorize == I_("R") ) // return mail, set hold flag to YES;
            {
               setFieldNoValidate((*iter).second->getHold(),YES,idDataGroup,false,true,true,false);
               if( idField == ifds::TxnConfAuth )
               {
                  setFieldNoValidate(ifds::ContrHold,YES,idDataGroup,false,true,true,false);
               }
            }
         }
         break;
      }
      ++iter;
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//****************************************************************************
void AccountMailingInfo::setObjectUpdated(const BFDataGroupId& idDataGroup)
{
   setUpdatedFlag(ifds::RegAddr,idDataGroup,true);
}

//****************************************************************************
void AccountMailingInfo::setUpMailingSubstitute(const BFDataGroupId& idDataGroup )
{
   DocumentTypeList* pDocumentTypeList = NULL;

   if( getMgmtCo().getDocumentTypeList( pDocumentTypeList ) <= WARNING )
   {
      DString dstrDocType,dstrList;
      pDocumentTypeList->getDocumentTypeSubstitute(dstrList);  
   }
}

//*********************************************************************************
SEVERITY AccountMailingInfo::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   if( isDeliveryOptionApply( idDataGroup ) )
   {
      validateWaive( idDataGroup );
      validateSuppress( idDataGroup );
      validateMailingOption( idDataGroup );
   }

   validateAuthHold( idDataGroup );

   DString dstrAccountNum;
   MFAccount *pMFAccount = NULL;
   if(!isNew()&& isUpdatedForDataGroup (idDataGroup) && getParent())
   {
      dstrAccountNum = ( dynamic_cast <AccountMailingList*> ( getParent() ) )->getAccountNum ( );
      dstrAccountNum.strip ().stripLeading ('0');
      if (getWorkSession().getMFAccount ( idDataGroup, dstrAccountNum, pMFAccount ) <= WARNING &&
         pMFAccount)
      {
         bool bDisplyWarnSICAV ,bDisplyWarnOEIC;
         pMFAccount->displayEnvXrefWarningOnUpdate(idDataGroup, bDisplyWarnSICAV, bDisplyWarnOEIC);
         if(bDisplyWarnSICAV)
            ADDCONDITIONFROMFILE (CND::WARN_DATA_UPDATE_IMPACTS_EXTERNAL_ENV_SICAV);
         if(bDisplyWarnOEIC)
            ADDCONDITIONFROMFILE (CND::WARN_DATA_UPDATE_IMPACTS_EXTERNAL_ENV_OEIC);
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//**********************************************************************************
SEVERITY AccountMailingInfo::validateMailingOption( const BFDataGroupId& idDataGroup ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateMailingOption" ) );

   DString strListDocType;

   getWorkSession().getOption( ifds::ListDocType, strListDocType, idDataGroup, false);
   strListDocType.strip().upperCase();      

   MAIL_MAP_ITER iter = _mailmap.begin();
   while( iter != _mailmap.end() )
   {
      DString strSuppress,strWaive,strMail;
      getField( (*iter).second->getSuppress(),strSuppress,idDataGroup,false );
      getField( (*iter).second->getWaive(),strWaive,idDataGroup,false );
      getField( (*iter).second->getMail(),strMail,idDataGroup,false );
      strMail.strip().upperCase();
      strWaive.strip().upperCase();strSuppress.strip().upperCase();
      if(strSuppress == NO ||  strWaive == NO)  
      {
         DString dstrMail(NULL_STRING),dstrValue;
         getField((*iter).second->getMail(),dstrValue,idDataGroup,false);
         dstrValue.strip();
         dstrMail += dstrValue;
         getField((*iter).second->getFax(),dstrValue,idDataGroup,false);
         dstrValue.strip();
         dstrMail += dstrValue;
         getField((*iter).second->getCD(),dstrValue,idDataGroup,false);
         dstrValue.strip();
         dstrMail += dstrValue;
         getField((*iter).second->getEmail(),dstrValue,idDataGroup,false);
         dstrValue.strip();
         dstrMail += dstrValue;
         getField((*iter).second->getEpost(),dstrValue,idDataGroup,false);
         dstrValue.strip();
         dstrMail += dstrValue;

         bool bRaiseCondition = false;
         if(strListDocType.strip().upperCase().empty() )
         {
            // environment not support 'Default' for mail column
            if(dstrMail.find(YES) == DString::npos )
            {
               bRaiseCondition = true;
            }
         }
         else
         {
            DString strDocTypeRaw = (*iter).second->getCode();

            if(DSTCommonFunctions::codeInList(strDocTypeRaw,strListDocType ) &&
               DSTCommonFunctions::codeInList(strDocTypeRaw,ALLOWED_DEFAULT_DOC))
            {
               if( dstrMail.find(YES) == DString::npos )
               {
                  if(dstrMail.find(I_("D")) == DString::npos )
                  {
                     bRaiseCondition = true;
                  }
               }
            }
            else
            {
               if(dstrMail.find(YES) == DString::npos )
               {
                  bRaiseCondition = true;
               }
            }
         }

         if(bRaiseCondition)
         {
            DString idiStr;
            addIDITagValue( idiStr, I_("DOCTYPE"), (*iter).first );
            getErrMsg( IFASTERR::MAIL_OPTION_CANNOT_BE_ALL_NO,
                       CND::ERR_MAIL_OPTION_CANNOT_BE_ALL_NO,
                       CND::WARN_MAIL_OPTION_CANNOT_BE_ALL_NO,
                       idDataGroup,
                       idiStr.c_str());
            //ADDCONDITIONFROMFILEIDI( CND::ERR_MAIL_OPTION_CANNOT_BE_ALL_NO, idiStr.c_str() );
         }
      }
      ++iter;
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//*********************************************************************************
void  AccountMailingInfo::setupMailing()
{
   _mailmap.insert( MAIL_MAP_VALUE_TYPE( I_("Register"),
                                         new Mailing(DocType::REGISTER,
                                                     BFFieldId(ifds::RegSuppress),
                                                     BFFieldId(ifds::RegWaive),
                                                     BFFieldId(ifds::RegMail), // Y,N 
                                                     BFFieldId(ifds::RegFax),
                                                     BFFieldId(ifds::RegCD),
                                                     BFFieldId(ifds::RegEmail),
                                                     BFFieldId(ifds::RegOnHold), 
                                                     BFFieldId(ifds::RegEpost),
                                                     BFFieldId(ifds::RegAuth), 
                                                     BFFieldId(ifds::RegAddr),
                                                     BFFieldId(ifds::StmtFrequencyDisabled))));

   _mailmap.insert( MAIL_MAP_VALUE_TYPE( I_("DividendConfirmation"),
                                         new Mailing(DocType::DIVIDEND_CONFIRM,       
                                                     BFFieldId(ifds::DivConfSuppress),
                                                     BFFieldId(ifds::DivConfWaive),
                                                     BFFieldId(ifds::DivConfMail), // Y,N 
                                                     BFFieldId(ifds::DivConfFax),
                                                     BFFieldId(ifds::DivConfCD),
                                                     BFFieldId(ifds::DivConfEmail),
                                                     BFFieldId(ifds::DivConfOnHold), 
                                                     BFFieldId(ifds::DivConfEpost),
                                                     BFFieldId(ifds::DivConfAuth), 
                                                     BFFieldId(ifds::DivConfAddr),
                                                     BFFieldId(ifds::StmtFrequencyDisabled)   )));
                                                     
   _mailmap.insert( MAIL_MAP_VALUE_TYPE( I_("DividendCheque"),
                                         new Mailing(DocType::DIVIDEND_CHEQUE,        
                                                     BFFieldId(ifds::DivChqSuppress),
                                                     BFFieldId(ifds::DivChqWaive),
                                                     BFFieldId(ifds::DivChqMail), // Y,N 
                                                     BFFieldId(ifds::DivChqFax),
                                                     BFFieldId(ifds::DivChqCD),
                                                     BFFieldId(ifds::DivChqEmail),
                                                     BFFieldId(ifds::DivChqOnHold), 
                                                     BFFieldId(ifds::DivChqEpost),
                                                     BFFieldId(ifds::DivChqAuth), 
                                                     BFFieldId(ifds::DivChqAddr),
                                                     BFFieldId(ifds::StmtFrequencyDisabled)    )));
                                                     
   _mailmap.insert( MAIL_MAP_VALUE_TYPE( I_("Confirmation"),
                                         new Mailing(DocType::CONFIRMATION,           
                                                     BFFieldId(ifds::TxnConfSuppress),
                                                     BFFieldId(ifds::TxnConfWaive),
                                                     BFFieldId(ifds::TxnConfMail), // Y,N 
                                                     BFFieldId(ifds::TxnConfFax),
                                                     BFFieldId(ifds::TxnConfCD),
                                                     BFFieldId(ifds::TxnConfEmail),
                                                     BFFieldId(ifds::TxnConfOnHold), 
                                                     BFFieldId(ifds::TxnConfEpost),
                                                     BFFieldId(ifds::TxnConfAuth), 
                                                     BFFieldId(ifds::TxnConfAddr),
                                                     BFFieldId(ifds::StmtFrequencyDisabled)   )));
                                                     
   _mailmap.insert( MAIL_MAP_VALUE_TYPE( I_("AdditionalConfirmation"),
                                         new Mailing(DocType::ADDITIONAL_CONFIRM,     
                                                     BFFieldId(ifds::DupConfSuppress),      
                                                     BFFieldId(ifds::DupConfWaive),      
                                                     BFFieldId(ifds::DupConfMail),   // Y,N
                                                     BFFieldId(ifds::DupConfFax),   
                                                     BFFieldId(ifds::DupConfCD),      
                                                     BFFieldId(ifds::DupConfEmail),      
                                                     BFFieldId(ifds::DupConfOnHold), 
                                                     BFFieldId(ifds::DupConfEpost),
                                                     BFFieldId(ifds::DupConfAuth), 
                                                     BFFieldId(ifds::DupConfAddr),
                                                     BFFieldId(ifds::StmtFrequencyDisabled)   )));
                                                     
   _mailmap.insert( MAIL_MAP_VALUE_TYPE( I_("Statements"),
                                         new Mailing(DocType::STATEMENT,              
                                                     BFFieldId(ifds::StmtSuppress),         
                                                     BFFieldId(ifds::StmtWaive),         
                                                     BFFieldId(ifds::StmtMail),   // Y,N and D   
                                                     BFFieldId(ifds::StmtFax),      
                                                     BFFieldId(ifds::StmtCD),      
                                                     BFFieldId(ifds::StmtEmail),         
                                                     BFFieldId(ifds::StmtOnHold), 
                                                     BFFieldId(ifds::StmtEpost),
                                                     BFFieldId(ifds::StmtAuth), 
                                                     BFFieldId(ifds::StmtAddr),
                                                     BFFieldId(ifds::StmtFrequency)       )));
                                                     
   _mailmap.insert( MAIL_MAP_VALUE_TYPE( I_("AdditionalStatement"),
                                         new Mailing(DocType::ADDITIONAL_STATEMENT,   
                                                     BFFieldId(ifds::DupStmtSuppress),      
                                                     BFFieldId(ifds::DupStmtWaive),      
                                                     BFFieldId(ifds::DupStmtMail),   // Y,N and D
                                                     BFFieldId(ifds::DupStmtFax),   
                                                     BFFieldId(ifds::DupStmtCD),      
                                                     BFFieldId(ifds::DupStmtEmail),      
                                                     BFFieldId(ifds::DupStmtOnHold), 
                                                     BFFieldId(ifds::DupStmtEpost),
                                                     BFFieldId(ifds::DupStmtAuth), 
                                                     BFFieldId(ifds::DupStmtAddr),
                                                     BFFieldId(ifds::StmtFrequencyDisabled)   )));
                                                     
   _mailmap.insert( MAIL_MAP_VALUE_TYPE( I_("Certificate"),
                                         new Mailing(DocType::CERTIFICATE,            
                                                     BFFieldId(ifds::CertSuppress),         
                                                     BFFieldId(ifds::CertWaive),         
                                                     BFFieldId(ifds::CertMail),   // Y,N
                                                     BFFieldId(ifds::CertFax),      
                                                     BFFieldId(ifds::CertCD),      
                                                     BFFieldId(ifds::CertEmail),         
                                                     BFFieldId(ifds::CertOnHold), 
                                                     BFFieldId(ifds::CertEpost),
                                                     BFFieldId(ifds::CertAuth), 
                                                     BFFieldId(ifds::CertAddr),
                                                     BFFieldId(ifds::StmtFrequencyDisabled) )));
                                                     
   _mailmap.insert( MAIL_MAP_VALUE_TYPE( I_("TaxReceipt"),
                                         new Mailing(DocType::TAX_RECEIPT,            
                                                     BFFieldId(ifds::TaxSuppress),         
                                                     BFFieldId(ifds::TaxWaive),         
                                                     BFFieldId(ifds::TaxMail),   // Y,N    
                                                     BFFieldId(ifds::TaxFax),      
                                                     BFFieldId(ifds::TaxCD),         
                                                     BFFieldId(ifds::TaxEmail),         
                                                     BFFieldId(ifds::TaxOnHold), 
                                                     BFFieldId(ifds::TaxEpost),
                                                     BFFieldId(ifds::TaxAuth), 
                                                     BFFieldId(ifds::TaxAddr),
                                                     BFFieldId(ifds::StmtFrequencyDisabled)      )));
                                                     
   _mailmap.insert( MAIL_MAP_VALUE_TYPE( I_("Letters"),
                                         new Mailing(DocType::LETTERS,                
                                                     BFFieldId(ifds::LetSuppress),         
                                                     BFFieldId(ifds::LetWaive),         
                                                     BFFieldId(ifds::LetMail),   // Y,N
                                                     BFFieldId(ifds::LetFax),      
                                                     BFFieldId(ifds::LetCD),         
                                                     BFFieldId(ifds::LetEmail),         
                                                     BFFieldId(ifds::LetOnHold), 
                                                     BFFieldId(ifds::LetEpost),
                                                     BFFieldId(ifds::LetAuth), 
                                                     BFFieldId(ifds::LetAddr),
                                                     BFFieldId(ifds::StmtFrequencyDisabled)      )));
                                                     
   _mailmap.insert( MAIL_MAP_VALUE_TYPE( I_("BeneficialOwner"),
                                         new Mailing(DocType::BENEFICIAL_OWNER,       
                                                     BFFieldId(ifds::BenSuppress),         
                                                     BFFieldId(ifds::BenWaive),         
                                                     BFFieldId(ifds::BenMail),   // Y,N
                                                     BFFieldId(ifds::BenFax),      
                                                     BFFieldId(ifds::BenCD),         
                                                     BFFieldId(ifds::BenEmail),         
                                                     BFFieldId(ifds::BenOnHold), 
                                                     BFFieldId(ifds::BenEpost),
                                                     BFFieldId(ifds::BenAuth), 
                                                     BFFieldId(ifds::BenAddr),
                                                     BFFieldId(ifds::StmtFrequencyDisabled)      )));
                                                     
   _mailmap.insert( MAIL_MAP_VALUE_TYPE( I_("NonFinancialConfirm"),
                                         new Mailing(DocType::NON_FINANCIAL_CONFIRM,  
                                                     BFFieldId(ifds::NFConfSuppress),      
                                                     BFFieldId(ifds::NFConfWaive),      
                                                     BFFieldId(ifds::NFConfMail), // Y,N
                                                     BFFieldId(ifds::NFConfFax),      
                                                     BFFieldId(ifds::NFConfCD),      
                                                     BFFieldId(ifds::NFConfEmail),      
                                                     BFFieldId(ifds::NFConHold), 
                                                     BFFieldId(ifds::NFConfEpost),
                                                     BFFieldId(ifds::NFConAuth), 
                                                     BFFieldId(ifds::NFCAddr),
                                                     BFFieldId(ifds::StmtFrequencyDisabled)      )));
                                                     
   _mailmap.insert( MAIL_MAP_VALUE_TYPE( I_("ContractNotes"),
                                         new Mailing(DocType::CONTRACT_NOTES,         
                                                     BFFieldId(ifds::ContrSuppress),      
                                                     BFFieldId(ifds::ContrWaive),      
                                                     BFFieldId(ifds::ContrMail), // Y,N
                                                     BFFieldId(ifds::ContrFax),      
                                                     BFFieldId(ifds::ContrCD),      
                                                     BFFieldId(ifds::ContrEmail),      
                                                     BFFieldId(ifds::ContrHold), 
                                                     BFFieldId(ifds::ContrEPost),
                                                     BFFieldId(ifds::ContrAuth), 
                                                     BFFieldId(ifds::ContrAddr),
                                                     BFFieldId(ifds::StmtFrequencyDisabled)   )));
                                                     
   _mailmap.insert( MAIL_MAP_VALUE_TYPE( I_("AnnualReports"),
                                         new Mailing(DocType::ANNUAL_REPORT,          
                                                     BFFieldId(ifds::AnnlRptsSuppress),      
                                                     BFFieldId(ifds::AnnlRptsWaive),      
                                                     BFFieldId(ifds::AnnlRptsMail), // Y,N
                                                     BFFieldId(ifds::AnnlRptsFax),   
                                                     BFFieldId(ifds::AnnlRptsCD),   
                                                     BFFieldId(ifds::AnnlRptsEmail),      
                                                     BFFieldId(ifds::AnnlRptsHold), 
                                                     BFFieldId(ifds::AnnlRptsEpost),
                                                     BFFieldId(ifds::AnnlRptsAuth), 
                                                     BFFieldId(ifds::AnnlRptsAddr),
                                                     BFFieldId(ifds::StmtFrequencyDisabled)   )));
                                                     
   _mailmap.insert( MAIL_MAP_VALUE_TYPE( I_("Prospectuses"),
                                         new Mailing(DocType::PROSPECTUSES,           
                                                     BFFieldId(ifds::ProspSuppress),      
                                                     BFFieldId(ifds::ProspWaive),      
                                                     BFFieldId(ifds::ProspMail), // Y,N
                                                     BFFieldId(ifds::ProspFax),      
                                                     BFFieldId(ifds::ProspCD),      
                                                     BFFieldId(ifds::ProspEmail),      
                                                     BFFieldId(ifds::ProspHold), 
                                                     BFFieldId(ifds::ProspEpost),
                                                     BFFieldId(ifds::ProspAuth), 
                                                     BFFieldId(ifds::ProspAddr),
                                                     BFFieldId(ifds::StmtFrequencyDisabled)    )));
                                                     
   _mailmap.insert( MAIL_MAP_VALUE_TYPE( I_("SemiAnnualReport"),
                                         new Mailing(DocType::SEMI_ANNUAL_REPORT,     
                                                     BFFieldId(ifds::SemiAnnualSuppress),   
                                                     BFFieldId(ifds::SemiAnnualWaive),   
                                                     BFFieldId(ifds::SemiAnnualMail), // Y,N
                                                     BFFieldId(ifds::SemiAnnualFax),   
                                                     BFFieldId(ifds::SemiAnnualCD),   
                                                     BFFieldId(ifds::SemiAnnualEmail),   
                                                     BFFieldId(ifds::SemiAnnualOnHold), 
                                                     BFFieldId(ifds::SemiAnnualEpost),
                                                     BFFieldId(ifds::SmAnnlRptsAuth), 
                                                     BFFieldId(ifds::SemiAnnualAddr),
                                                     BFFieldId(ifds::StmtFrequencyDisabled)      )));
                                                     
   _mailmap.insert( MAIL_MAP_VALUE_TYPE( I_("ContributionReceipt"),
                                         new Mailing(DocType::CONTRIBUTION_RECEIPT,   
                                                     BFFieldId(ifds::ContributionSuppress),
                                                     BFFieldId(ifds::ContributionWaive   ),   
                                                     BFFieldId(ifds::ContributionMail), // Y,N 
                                                     BFFieldId(ifds::ContributionFax),   
                                                     BFFieldId(ifds::ContributionCD),
                                                     BFFieldId(ifds::ContributionEmail),   
                                                     BFFieldId(ifds::ContributionOnHold), 
                                                     BFFieldId(ifds::ContributionEpost),
                                                     BFFieldId(ifds::ContributionAuth), 
                                                     BFFieldId(ifds::ContributionAddr),
                                                     BFFieldId(ifds::StmtFrequencyDisabled)      )));
                                                     
   _mailmap.insert( MAIL_MAP_VALUE_TYPE( I_("AnnlMRFP"),
                                         new Mailing(DocType::ANNUAL_MRFP,            
                                                     BFFieldId(ifds::AnnlMRFPSuppress),
                                                     BFFieldId(ifds::AnnlMRFPWaive),   
                                                     BFFieldId(ifds::AnnlMRFPMail), // Y,N
                                                     BFFieldId(ifds::AnnlMRFPFax),   
                                                     BFFieldId(ifds::AnnlMRFPCD),
                                                     BFFieldId(ifds::AnnlMRFPEmail),   
                                                     BFFieldId(ifds::AnnlMRFPHold), 
                                                     BFFieldId(ifds::AnnlMRFPEpost),
                                                     BFFieldId(ifds::AnnlMRFPAuth), 
                                                     BFFieldId(ifds::AnnlMRFPAddr),
                                                     BFFieldId(ifds::StmtFrequencyDisabled)      )));
                                                     
   _mailmap.insert( MAIL_MAP_VALUE_TYPE( I_("SmAnnlMRFP"),              
                                         new Mailing(DocType::SEMI_ANNUAL_MRFP,       
                                                     BFFieldId(ifds::SmAnnlMRFPSuppress),
                                                     BFFieldId(ifds::SmAnnlMRFPWaive   ),   
                                                     BFFieldId(ifds::SmAnnlMRFPMail), // Y,N
                                                     BFFieldId(ifds::SmAnnlMRFPFax),   
                                                     BFFieldId(ifds::SmAnnlMRFPCD),
                                                     BFFieldId(ifds::SmAnnlMRFPEmail),   
                                                     BFFieldId(ifds::SmAnnlMRFPHold), 
                                                     BFFieldId(ifds::SmAnnlMRFPEpost),
                                                     BFFieldId(ifds::SmAnnlMRFPAuth), 
                                                     BFFieldId(ifds::SmAnnlMRFPAddr),
                                                     BFFieldId(ifds::StmtFrequencyDisabled)      )));
}

//**********************************************************************************
void AccountMailingInfo::clearMailmap()
{
   MAIL_MAP_ITER iter = _mailmap.begin();
   while( iter != _mailmap.end() )
   {
      delete (*iter).second;
      ++iter;
   }
   _mailmap.clear();
}

//************************************************************************************
SEVERITY AccountMailingInfo::validateMail(const BFFieldId& idField, 
                                          DString strValue, 
                                          const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateMail" ) );

   MAIL_MAP_ITER iter = _mailmap.begin();
   while( iter != _mailmap.end() )
   {
      if( (*iter).second->getMail() == idField  )
      {
         DString dstrWaive,dstrDocType;
         getField( (*iter).second->getWaive(),dstrWaive,idDataGroup,false);
         dstrWaive.strip();
         if (strValue == NO && dstrWaive == NO )
         {
            DString idiStr;
            addIDITagValue( idiStr, I_("DOCTYPE"), (*iter).first );
            getErrMsg( IFASTERR::MAIL_CANNOT_BE_NO_FOR_NO_WAIVE,
                       CND::ERR_MAIL_CANNOT_BE_NO_FOR_NO_WAIVE,
                       CND::WARN_MAIL_CANNOT_BE_NO_FOR_NO_WAIVE,
                       idDataGroup,
                       idiStr.c_str());
            //ADDCONDITIONFROMFILEIDI( CND::ERR_MAIL_CANNOT_BE_NO_FOR_NO_WAIVE, idiStr.c_str() );  
            break;
         }
      }
      ++iter;
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//************************************************************************************
SEVERITY AccountMailingInfo::validateEmail(const BFFieldId& idField, 
                                           DString strValue, 
                                           const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateEmail" ) );

   MAIL_MAP_ITER iter = _mailmap.begin();
   while( iter != _mailmap.end() )
   {
      if( (*iter).second->getEmail() == idField  )
      {
         if(strValue == YES )  // Email set to YES
         {
            if( !isEmailExist(idDataGroup) )
               ADDCONDITIONFROMFILE( CND::ERR_NO_EMAIL_ADDRESS );
         }
      }
      ++iter;
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************************
SEVERITY AccountMailingInfo::validateFax(const BFFieldId& idField, 
                                         DString strValue, 
                                         const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFax" ) );

   MAIL_MAP_ITER iter = _mailmap.begin();
   while( iter != _mailmap.end() )
   {
      if( (*iter).second->getFax() == idField  )
      {
         if(strValue == YES )  // Fax set to YES
         {
            if( !isFaxExist(idDataGroup) )
               ADDCONDITIONFROMFILE( CND::ERR_NO_FAX_AVAILABLE );
         }
      }
      ++iter;
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AccountMailingInfo::getFirstSequenced01AccountholderObject( const BFDataGroupId& idDataGroup, 
                                                                     DString& AcctNum,
                                                                     Entity *&pEntityOut   )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, 
                          CLASSNAME, 
                          I_( "getFirstSequenced01AccountholderObject" ) );   

   // get account owner name:
   AccountEntityXref *_pAccountEntityXref;

   if ( getWorkSession().getAccountEntityXref( idDataGroup, _pAccountEntityXref ) <= WARNING )
   {
      if ( _pAccountEntityXref->PopulateAccountOwner( idDataGroup, NULL_STRING, AcctNum, NULL_STRING, NULL_STRING ) <= WARNING )
      {
         BFObjIter iterAccountEntityXrefOut( *_pAccountEntityXref, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );
         DString searchKey;
         AccountEntityXref::buildPartialKeyForRetrievingEntity( searchKey, AcctNum, I_( "01" ), I_( "1" ) );

         if ( iterAccountEntityXrefOut.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey ) )
         {
            DString dstrEntityId;
            iterAccountEntityXrefOut.getObject()->getField( ifds::EntityId, dstrEntityId, idDataGroup, false );      
            getWorkSession().getEntity( idDataGroup, dstrEntityId, pEntityOut );
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//**************************************************************************************************
bool AccountMailingInfo::isEmailExist(const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "isEmailExist" ) );

   DString dstrAcctNum;
   bool bExist = false;
   getField(ifds::AccountNum,dstrAcctNum,idDataGroup,false);
   Entity* pEntity = NULL;
   SEVERITY sev = getFirstSequenced01AccountholderObject(idDataGroup,dstrAcctNum,pEntity);
   if(pEntity && sev <= WARNING )
   {
      DString dstrEmail;
      pEntity->getField(ifds::Email,dstrEmail,idDataGroup,false);
      dstrEmail.stripAll();
      bExist = dstrEmail != NULL_STRING;

   }
   return bExist;
}

//**************************************************************************************************
bool AccountMailingInfo::isFaxExist(const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "isFaxExist" ) );   

   DString dstrAcctNum;
   bool bExist = false;
   getField(ifds::AccountNum,dstrAcctNum,idDataGroup,false);
   Entity* pEntity = NULL;
   SEVERITY sev = getFirstSequenced01AccountholderObject(idDataGroup,dstrAcctNum,pEntity);
   if(pEntity && sev <= WARNING )
   {
      DString dstrBusFax,dstrHomFax;
      pEntity->getField(ifds::HomeFax,dstrHomFax,idDataGroup,false);
      pEntity->getField(ifds::BusinessFax,dstrBusFax,idDataGroup,false);
      dstrHomFax.stripAll();
      dstrBusFax.stripAll();
      bExist = dstrBusFax != NULL_STRING  || dstrHomFax != NULL_STRING;
   }

   return bExist;
}

//************************************************************************************
bool AccountMailingInfo::isDeliveryOptionApply( const BFDataGroupId& idDataGroup )
{
   DString dstrDeliveryOption;
   getWorkSession().getOption2( ifds::OPDeliveryOption, dstrDeliveryOption, idDataGroup, false);
   dstrDeliveryOption.strip();
   return dstrDeliveryOption == YES;
}

//************************************************************************************
SEVERITY AccountMailingInfo::validateSuppress( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateSuppress" ) );

   DString strListDocType;

   getWorkSession().getOption( ifds::ListDocType, strListDocType, idDataGroup, false);
   strListDocType.strip().upperCase();

   DString strValue;
   MAIL_MAP_ITER iter = _mailmap.begin();
   while( iter != _mailmap.end() )
   {   
      getField( (*iter).second->getSuppress(),strValue,idDataGroup,false );
      strValue.strip().upperCase();
      if(strValue == YES )  // Suppress set to YES
      {
         DString dstrMail(NULL_STRING),dstrValue;
         getField((*iter).second->getMail(),dstrValue,idDataGroup,false);
         dstrValue.strip();
         dstrMail += dstrValue;
         getField((*iter).second->getFax(),dstrValue,idDataGroup,false);
         dstrValue.strip();
         dstrMail += dstrValue;
         getField((*iter).second->getCD(),dstrValue,idDataGroup,false);
         dstrValue.strip();
         dstrMail += dstrValue;
         getField((*iter).second->getEmail(),dstrValue,idDataGroup,false);
         dstrValue.strip();
         dstrMail += dstrValue;
         getField((*iter).second->getEpost(),dstrValue,idDataGroup,false);
         dstrValue.strip();
         dstrMail += dstrValue;

         bool bRaiseCondition = false;
         if(strListDocType.strip().upperCase().empty() )
         {
            // environment not support 'Default' for mail column
            if(dstrMail.find(YES) == DString::npos )
            {
               bRaiseCondition = true;
            }
         }
         else
         {
            DString strDocTypeRaw = (*iter).second->getCode();

            if(DSTCommonFunctions::codeInList(strDocTypeRaw,strListDocType )&&
               DSTCommonFunctions::codeInList(strDocTypeRaw,ALLOWED_DEFAULT_DOC))
            {
               if( dstrMail.find(YES) == DString::npos )
               {
                  if(dstrMail.find(I_("D")) == DString::npos )
                  {
                     bRaiseCondition = true;
                  }
               }
            }
            else
            {
               if(dstrMail.find(YES) == DString::npos )
               {
                  bRaiseCondition = true;
               }
            }
         }

         if(bRaiseCondition)
         {
            DString idiStr;
            addIDITagValue( idiStr, I_("DOCTYPE"), (*iter).first );
            getErrMsg( IFASTERR::NO_MAIL_TO_SUPPRESS,
                       CND::ERR_NO_MAIL_TO_SUPPRESS,
                       CND::WARN_NO_MAIL_TO_SUPPRESS,
                       idDataGroup,
                       idiStr.c_str());
            //ADDCONDITIONFROMFILEIDI( CND::ERR_NO_MAIL_TO_SUPPRESS, idiStr.c_str() );
         }
      }
      ++iter;
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************************
SEVERITY AccountMailingInfo::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );

   WaivePaperRelatedChange(idField,idDataGroup);

   authorizRelatedChanges( idField, idDataGroup );
   if ( !bfutil::isServerContext() )
   {
      holdRelatedChanges( idField, idDataGroup );
   }

   if( idField == ifds::TxnConfAddr || idField == ifds::TxnConfOnHold )
   {
      setNonDataBaseFields(idDataGroup );
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//*******************************************************************************************
SEVERITY AccountMailingInfo::WaivePaperRelatedChange(const BFFieldId& idField, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "WaivePaperRelatedChange" ) );   

   MAIL_MAP_ITER iter = _mailmap.begin();
   while( iter != _mailmap.end() )
   {
      if( (*iter).second->getWaive() == idField  )
      {
         DString dstrWaive;
         getField(idField,dstrWaive,idDataGroup,false);
         dstrWaive.strip().upperCase();
         DString dstrValue = dstrWaive == YES? NO:YES; // default mail to blank if consent is yes
         setFieldNoValidate((*iter).second->getMail(),dstrValue,idDataGroup,false,true,true,false);
         break;
      }
/*      else if((*iter).second->getMail() == idField )
      {
         DString dstrMail;
         getField(idField,dstrMail,idDataGroup,false);
         dstrMail.strip().upperCase();
         DString dstrValue = dstrMail == YES? NO:YES;
         setFieldNoValidate((*iter).second->getWaive(),dstrValue,idDataGroup,false,true,true,false);      
      }*/
      ++iter;
   }
   
   setMailingFieldsReadonly(idDataGroup); 

   return GETCURRENTHIGHESTSEVERITY();
}

//***********************************************************************************************
SEVERITY AccountMailingInfo::validateWaive( const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateWaive" ) );

   DString strListDocType;

   getWorkSession().getOption( ifds::ListDocType, strListDocType, idDataGroup, false);
   strListDocType.strip().upperCase();   

   MAIL_MAP_ITER iter = _mailmap.begin();
   while( iter != _mailmap.end() )
   {
      DString strValue;
      getField( (*iter).second->getWaive(),strValue,idDataGroup,false );
      strValue.strip().upperCase();
      if(strValue == YES )  // WAIVE Paper is yes
      {
         DString dstrMail(NULL_STRING),dstrValue;
         getField((*iter).second->getFax(),dstrValue,idDataGroup,false);
         dstrValue.strip();
         dstrMail += dstrValue;
         getField((*iter).second->getCD(),dstrValue,idDataGroup,false);
         dstrValue.strip();
         dstrMail += dstrValue;
         getField((*iter).second->getEmail(),dstrValue,idDataGroup,false);
         dstrValue.strip();
         dstrMail += dstrValue;
         getField((*iter).second->getEpost(),dstrValue,idDataGroup,false);
         dstrValue.strip();
         dstrMail += dstrValue;

         bool bRaiseCondition = false;
         if(strListDocType.strip().upperCase().empty() )
         {
            // environment not support 'Default' for mail column
            if(dstrMail.find(YES) == DString::npos )
            {
               bRaiseCondition = true;
            }
         }
         else
         {
            DString strDocTypeRaw = (*iter).second->getCode();

            if(DSTCommonFunctions::codeInList(strDocTypeRaw,strListDocType )&&
               DSTCommonFunctions::codeInList(strDocTypeRaw,ALLOWED_DEFAULT_DOC))
            {
               if( dstrMail.find(YES) == DString::npos )
               {
                  if(dstrMail.find(I_("D")) == DString::npos )
                  {
                     bRaiseCondition = true;
                  }
               }
            }
            else
            {
               if(dstrMail.find(YES) == DString::npos )
               {
                  bRaiseCondition = true;
               }
            }
         }

         if(bRaiseCondition)
         {
            DString idiStr;
            addIDITagValue( idiStr, I_("DOCTYPE"), (*iter).first );
            getErrMsg( IFASTERR::WAIVE_PAPER_CANNOT_BE_YES,
                       CND::ERR_WAIVE_PAPER_CANNOT_BE_YES,
                       CND::WARN_WAIVE_PAPER_CANNOT_BE_YES,
                       idDataGroup,
                       idiStr.c_str());
            //ADDCONDITIONFROMFILEIDI( CND::ERR_WAIVE_PAPER_CANNOT_BE_YES, idiStr.c_str() );  
         }
      }
      ++iter;
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//*************************************************************************************************
void AccountMailingInfo::setMailingFieldsReadonly(const BFDataGroupId& idDataGroup)
{
   DString dstrDeliveryMethod,dstrDeliveryOption,dstrCnsntToWaive;
   getWorkSession().getOption2( ifds::OPDeliveryOption, dstrDeliveryOption, BF::HOST, false);
   getWorkSession().getOption2( ifds::OPDeliveryMethods, dstrDeliveryMethod, BF::HOST, false);
   getWorkSession().getOption2( ifds::CnsntToWaive, dstrCnsntToWaive, BF::HOST, false);
   dstrCnsntToWaive.strip();   
   dstrDeliveryMethod.strip();
   dstrDeliveryOption.strip();
   bool bSuppressReadonly = dstrDeliveryOption == NO;
   bool bWaiveReadOnly = dstrCnsntToWaive == NO;

   DocumentTypeList* pDocumentTypeList = NULL;
   getMgmtCo().getDocumentTypeList( pDocumentTypeList ); 
   MAIL_MAP_ITER iter = _mailmap.begin();
   while( iter != _mailmap.end() )
   {
      bool bFindDocMail = false;
      bool bFindDocFax = false;
      bool bFindDocEmail = false;
      bool bFindDocCD = false;
      bool bFindDocEpost = false;

      if(pDocumentTypeList)
      {
         DString dstrSubstList;
         pDocumentTypeList->getDeliverySubstitute((*iter).second->getCode(),dstrSubstList,dstrDeliveryMethod);
         bFindDocMail = (dstrSubstList.find(DELIVER_OPTION::MAIL ) != DString::npos );
         bFindDocEmail = (dstrSubstList.find(DELIVER_OPTION::EMAIL ) != DString::npos );
         bFindDocFax = (dstrSubstList.find( DELIVER_OPTION::FAX ) != DString::npos );
         bFindDocCD = (dstrSubstList.find( DELIVER_OPTION::CD ) != DString::npos );
         bFindDocEpost = (dstrSubstList.find( DELIVER_OPTION::EPOST ) != DString::npos );
      }

      DString dstrWaive;
      getField((*iter).second->getWaive(),dstrWaive,idDataGroup,false); // consent
      dstrWaive.strip().upperCase();
      //bool bUpdate = (dstrDeliveryOption == YES  && bFindDocMail && dstrWaive == YES  );
      bool bUpdate = (dstrDeliveryOption == YES  && bFindDocMail );
      setFieldReadOnly( (*iter).second->getMail(), idDataGroup, !bUpdate );

      bUpdate = (dstrDeliveryOption == YES  && bFindDocFax );
      setFieldReadOnly( (*iter).second->getFax(), idDataGroup, !bUpdate );

      bUpdate = (dstrDeliveryOption == YES  && bFindDocCD );
      setFieldReadOnly( (*iter).second->getCD(), idDataGroup, !bUpdate );

      bUpdate = (dstrDeliveryOption == YES  && bFindDocEmail );
      setFieldReadOnly( (*iter).second->getEmail(), idDataGroup, !bUpdate );   

      setFieldReadOnly( (*iter).second->getSuppress(), idDataGroup, bSuppressReadonly );   
      setFieldReadOnly( (*iter).second->getWaive(), idDataGroup, bWaiveReadOnly );

      bUpdate =  (dstrDeliveryOption == YES  && bFindDocEpost );
      setFieldReadOnly( (*iter).second->getEpost(), idDataGroup, !bUpdate );   

      //PET1277, set all suppress flag as read only if it is not following 5 document type
      DString docCode  = (*iter).second->getCode();
      if( docCode != DocType::CONFIRMATION  && 
          docCode != DocType::STATEMENT && 
          docCode != DocType::ADDITIONAL_CONFIRM && 
          docCode != DocType::ADDITIONAL_STATEMENT && 
          docCode != DocType::CONTRACT_NOTES )
      {
         setFieldReadOnly( (*iter).second->getSuppress(), idDataGroup, true );
      }

	  if( docCode == DocType::CONTRACT_NOTES )
	      setFieldReadOnly( (*iter).second->getAddr(), idDataGroup, true );

      ++iter;
   }
/* Incident# 513604 - delinked ContrHold/Address
   setFieldReadOnly( ifds::ContrHold,      idDataGroup, true );
   setFieldReadOnly( ifds::ContrAddr,      idDataGroup, true );
*/

//delink annual semi annual---PET1277
// setFieldReadOnly( ifds::ContributionOnHold,      idDataGroup, true );
// setFieldReadOnly( ifds::AnnlRptsHold,   idDataGroup, true );
// setFieldReadOnly( ifds::AnnlRptsAddr,   idDataGroup, true );
// setFieldReadOnly( ifds::ProspHold,      idDataGroup, true );
// setFieldReadOnly( ifds::ProspAddr,      idDataGroup, true );
// setFieldReadOnly( ifds::SemiAnnualOnHold,idDataGroup, true );
// setFieldReadOnly( ifds::SemiAnnualAddr,   idDataGroup, true );

// setFieldReadOnly( ifds::AnnlRptsHold, idDataGroup, true );
// setFieldReadOnly( ifds::SemiAnnualOnHold, idDataGroup, true );
// setFieldReadOnly( ifds::ProspHold, idDataGroup, true );
}

//*******************************************************************************
SEVERITY AccountMailingInfo::setNonDataBaseFields( const BFDataGroupId& idDataGroup)
{ 
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setNonDataBaseFields" ) );   
   DString dstrConfAddr,dstrStmtAddr,hold;
//   getField(ifds::StmtAddr,dstrStmtAddr,idDataGroup,false);
//   dstrStmtAddr.strip();
   getField(ifds::TxnConfAddr,dstrConfAddr,idDataGroup,false);
   dstrConfAddr.strip();
   setFieldNoValidate(ifds::ContrAddr,dstrConfAddr,idDataGroup,false,true,true,false);

   
   /* ----PET 1277: delink annl semi annual and prosp
   setFieldNoValidate(ifds::ProspAddr,dstrStmtAddr,idDataGroup,false,true,true,false);
   setFieldNoValidate(ifds::AnnlRptsAddr,dstrStmtAddr,idDataGroup,false,true,true,false);
   setFieldNoValidate(ifds::SemiAnnualAddr,dstrStmtAddr,idDataGroup,false,true,true,false);


   getField(ifds::StmtOnHold,hold,idDataGroup,false);
   hold.strip().upperCase();
   setFieldNoValidate(ifds::ProspHold,hold,idDataGroup,false,true,true,false);
   setFieldNoValidate(ifds::AnnlRptsHold,hold,idDataGroup,false,true,true,false);
   setFieldNoValidate(ifds::SemiAnnualOnHold,hold,idDataGroup,false,true,true,false);
*/
/*   Incident# 513604 - delinked ContrHold
   getField(ifds::TxnConfOnHold,hold,idDataGroup,false);
   hold.strip().upperCase();
   setFieldNoValidate(ifds::ContrHold,hold,idDataGroup,false,true,true,false);
*/
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************  
SEVERITY AccountMailingInfo::setDefaultStatementfrequency( const BFDataGroupId& idDataGroup)
{ 
   //Setting statement frequency values for new customers/shareholders
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setDefaultStatementfrequency" ) );

   DString StmtFreqdefault,StmtFreqlist;
   getWorkSession().getOption2 (ifds::StmtFreqList,StmtFreqlist, idDataGroup, false );
   if( !StmtFreqlist.empty() ) 
   {
      getWorkSession().getOption2 (ifds::StmtFreqDefault,StmtFreqdefault, idDataGroup, false );
      StmtFreqdefault.strip();
      loadSubstitutionList (ifds::StmtFrequency, idDataGroup, StmtFreqlist);
      setFieldNoValidate(ifds::StmtFrequency, StmtFreqdefault,idDataGroup,false,true,true,false);  
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************  
SEVERITY AccountMailingInfo::setStatementfrequency( const BFDataGroupId& idDataGroup)
{ 
   //Setting statement frequency values for existing customers/shareholders 
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setStatementfrequency" ) );

   DString StmtFreq,StmtFreqlist;
   getWorkSession().getOption2 (ifds::StmtFreqList,StmtFreqlist, idDataGroup, false );
   if( !StmtFreqlist.empty() ) 
   {
      getField(ifds::StmtFrequency, StmtFreq,idDataGroup,false);
      StmtFreq.strip();
      loadSubstitutionList (ifds::StmtFrequency, idDataGroup, StmtFreqlist);
      setFieldNoValidate(ifds::StmtFrequency, StmtFreq,idDataGroup,false,true,true,false);
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void AccountMailingInfo::setupSubstitutionList( const BFDataGroupId& idDataGroup)
{
   DString substList1,substList2;
   BFProperties *pProperties = getFieldProperties (ifds::Authorization, idDataGroup);
   if( pProperties )
   {
      pProperties->getAllSubstituteValues (substList1);
   }
   substList2 = substList1;

   substList1 = removeItemFromSubtList( substList1,I_("A") );
  // substList2 = removeItemFromSubtList( substList2,I_("P") );
   MAIL_MAP_ITER iter = _mailmap.begin();
   while( iter != _mailmap.end() )
   {
      if( (*iter).second->getCode() == DocType::ANNUAL_MRFP || 
          (*iter).second->getCode() == DocType::SEMI_ANNUAL_MRFP ||
          (*iter).second->getCode() == DocType::ANNUAL_REPORT ||
          (*iter).second->getCode() == DocType::SEMI_ANNUAL_REPORT  )
      {
         setFieldAllSubstituteValues( (*iter).second->getAuthorize(), 
                                      idDataGroup, 
                                      substList2 );
      }
      else 
      {
         setFieldAllSubstituteValues( (*iter).second->getAuthorize(), 
                                      idDataGroup, 
                                      substList1 );
      }
      ++iter;
   }

   initMailColSubstitutionSet(idDataGroup);
}

//***************************************************************************
SEVERITY AccountMailingInfo::holdRelatedChanges( const BFFieldId& idField, 
                                                 const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "holdRelatedChanges" ) );

   MAIL_MAP_ITER iter = _mailmap.begin();
   while( iter != _mailmap.end() )
   {
      if( (*iter).second->getHold() == idField  )
      {
         setFieldNoValidate((*iter).second->getAuthorize(),NULL_STRING,idDataGroup,false,false,true,false);               
         break;
      }
      ++iter;
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//**********************************************************************************
SEVERITY AccountMailingInfo::validateAuthHold( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateAuthHold" ) );

   DString authorize, hold;
   MAIL_MAP_ITER iter = _mailmap.begin();
   while( iter != _mailmap.end() )
   {
      getField( (*iter).second->getAuthorize(),authorize,idDataGroup,false );
      getField( (*iter).second->getHold(),hold,idDataGroup,false );
      authorize.strip();
      hold.strip().upperCase();
      if( authorize == I_("R") && hold == NO  )
      {
         DString docDes = (*iter).first;
         DString idiStr;
         addIDITagValue( idiStr, I_("TYPE"), docDes );
         ADDCONDITIONFROMFILEIDI( CND::ERR_NO_HOLD_FOR_RETURN_MAIL, idiStr.c_str() );
      }

      ++iter;
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AccountMailingInfo::setDefaultValueforReturnMail( const DString& strAddrCode, 
                                                           const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setDefaultValue" ) );

   bool bFindDefHold = false;
   DefaultMailOptionList* pDefaultMailOptionList = NULL;
   if( getMgmtCo().getDefaultMailOptionList( pDefaultMailOptionList ) <= WARNING )
   {
      bFindDefHold = true;
   }

   MAIL_MAP_ITER iter =  _mailmap.begin();
   while( iter != _mailmap.end() )
   {
      BFFieldId idField = (*iter).second->getAuthorize();
      DString authorize;
      getField(idField,authorize,idDataGroup,false);
      authorize.strip().upperCase();

      idField = (*iter).second->getAddr();
      DString addressCode;
      getField(idField,addressCode,idDataGroup,false);
      addressCode.strip().upperCase();

      if( addressCode == strAddrCode && authorize == I_("R") )
      {
         DString strDefDeliveryOption;
         pDefaultMailOptionList->getDefaultDeliveryOptionFlags(strDefDeliveryOption ,(*iter).second->getCode() ); 

         if(strDefDeliveryOption.strip().upperCase().empty())
         {
            // env that not support(DefDeliveryOption is blank) still use hardcode as original logic
            setFieldNoValidate((*iter).second->getEmail(),NO,idDataGroup,false,true,false,false); 
            setFieldNoValidate((*iter).second->getFax(),NO,idDataGroup,false,true,false,false); 
            setFieldNoValidate((*iter).second->getCD(),NO,idDataGroup,false,true,false,false); 
            setFieldNoValidate((*iter).second->getEpost(),NO,idDataGroup,false,true,false,false); 
            setFieldNoValidate((*iter).second->getMail(),YES,idDataGroup,false,true,false,false); 
         }
         else
         {
            DString strPos1 =  strDefDeliveryOption.substr (0, 1); // mail
            DString strPos2 =  strDefDeliveryOption.substr (1, 1); // email
            DString strPos3 =  strDefDeliveryOption.substr (2, 1); // fax
            DString strPos4 =  strDefDeliveryOption.substr (3, 1); // cd
            DString strPos5 =  strDefDeliveryOption.substr (4, 1); // epost
                  
            setFieldNoValidate((*iter).second->getEmail(),strPos2,idDataGroup,false,true,false,false); 
            setFieldNoValidate((*iter).second->getFax(),strPos3,idDataGroup,false,true,false,false); 
            setFieldNoValidate((*iter).second->getCD(),strPos4,idDataGroup,false,true,false,false); 
            setFieldNoValidate((*iter).second->getEpost(),strPos5,idDataGroup,false,true,false,false); 
            setFieldNoValidate((*iter).second->getMail(),strPos1,idDataGroup,false,true,false,false); 
         }

         setFieldNoValidate((*iter).second->getWaive(),NO,idDataGroup,false,true,false,false); 
         setFieldNoValidate((*iter).second->getSuppress(),NO,idDataGroup,false,true,false,false); 
         setFieldNoValidate((*iter).second->getAuthorize(),I_("D"),idDataGroup,false,true,false,false); 
         
         if( bFindDefHold )
         {
            DString hold = pDefaultMailOptionList->getDefaultHoldFlag ( (*iter).second->getCode() ); // we may need to supply fund group here
            setFieldNoValidate((*iter).second->getHold(),hold,idDataGroup,false,true,false,false);
         }
      }
      ++ iter;
   }

   setUpdatedFlag( ifds::RegAddr, idDataGroup, true );

   CLEARCONDITIONSFRAMECURRENT();

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AccountMailingInfo::initMailColSubstitutionSet(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initMailColSubstitutionSet" ) );

   DString strListDocType;

   getWorkSession().getOption( ifds::ListDocType, strListDocType, idDataGroup, false);
   strListDocType.strip().upperCase();   

   DString strDocumentMailSubstList, 
      strYesNOSubstList;

   BFProperties *pBFPropDocumentMail = getFieldProperties( ifds::DocumentMail, idDataGroup );
   BFProperties *pBFPropYesNo = getFieldProperties( ifds::Yes_NO, idDataGroup );
   pBFPropDocumentMail->getAllSubstituteValues (strDocumentMailSubstList);
   pBFPropYesNo->getAllSubstituteValues (strYesNOSubstList);
   
   MAIL_MAP_ITER iter = _mailmap.begin();
   while( iter != _mailmap.end() )
   {
      DString strDocType = (*iter).second->getCode();
      strDocType.strip().upperCase();

      if( DSTCommonFunctions::codeInList(strDocType,strListDocType) &&
          DSTCommonFunctions::codeInList(strDocType,ALLOWED_DEFAULT_DOC))
      {
         setFieldAllSubstituteValues( (*iter).second->getMail(), 
                                      idDataGroup, 
                                      strDocumentMailSubstList );
      }
      else 
      {
         setFieldAllSubstituteValues( (*iter).second->getMail(), 
                                      idDataGroup, 
                                      strYesNOSubstList );
      }

      ++iter;
   }   
   
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AccountMailingInfo::getMailOptionSubstitutionByDocKey(const DString &strDocKey, 
                                                               const BFDataGroupId &idDataGroup, 
                                                               BFFieldId &fieldID)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMailOptionSubstitutionByDocKey" ) );

   MAIL_MAP_ITER iter = _mailmap.find(strDocKey);

   if( iter != _mailmap.end() )
   {
      DString strListDocType;

      getWorkSession().getOption( ifds::ListDocType, strListDocType, idDataGroup, false);
      strListDocType.strip().upperCase();

      DString strDocType = (*iter).second->getCode();
      strDocType.strip().upperCase();

      if( DSTCommonFunctions::codeInList(strDocType,strListDocType) &&
          DSTCommonFunctions::codeInList(strDocType,ALLOWED_DEFAULT_DOC))
      {
         fieldID = ifds::DocumentMail;
      }
      else
      {
         fieldID = ifds::Yes_NO;
      }
   }
   else
   {
      fieldID = ifds::Yes_NO;
   }

   return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
SEVERITY AccountMailingInfo::setAuthorizedFlagForAddrCode(const DString &dstrAddrCode, const DString &dstrAuthorization, const DString &dstrRetMailFlag, const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("setAuthorizedFlagForAddrCode"));

	DString iterAddrCode, iterAuthorization, iterHoldFlag;
	MAIL_MAP_ITER iter =  _mailmap.begin();

	while(iter != _mailmap.end())
	{
		getField((*iter).second->getAddr(), iterAddrCode, idDataGroup);
		getField((*iter).second->getAuthorize(), iterAuthorization, idDataGroup);
        getFieldBeforeImage((*iter).second->getHold(), iterHoldFlag);

        iterHoldFlag.strip().upperCase();
        iterAuthorization.strip().upperCase();
        iterAddrCode.strip().upperCase();

        /*Only change Authorize flag when 
          1. Changing Return Mail from NO to YES and Hold Mail flag is NO.
          2. Changing Return Mail from YES to NO and Authorization is not Default/Permanent/Unclamed Property.
        */
		if ( iterAddrCode == dstrAddrCode && 
			 ((dstrRetMailFlag == YES && iterHoldFlag == NO) ||
              (dstrRetMailFlag == NO && iterAuthorization != AUTHORIZATION_CODE::DEFAULT && 
			                            iterAuthorization != AUTHORIZATION_CODE::PERMANENT && 
									    iterAuthorization != AUTHORIZATION_CODE::UNCLAIMED_PROPERTY)))
		{
			setFieldNoValidate((*iter).second->getAuthorize(), dstrAuthorization, idDataGroup,false,true,false,false);
		}

		++iter;
	}

	setObjectUpdated(idDataGroup);

	return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
SEVERITY AccountMailingInfo::setHoldFlagForAddrCode(const DString &dstrAddrCode, const DString &dstrHoldFlag, const DString &dstrRetMailFlag, const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("setHoldFlagForAddrCode"));

	DString iterAddrCode, iterAuthorization, iterHoldFlag;
	MAIL_MAP_ITER iter =  _mailmap.begin();

	while(iter != _mailmap.end())
	{
		getField((*iter).second->getAddr(), iterAddrCode, idDataGroup);
		getField((*iter).second->getAuthorize(), iterAuthorization, idDataGroup);
        getField((*iter).second->getHold(), iterHoldFlag, idDataGroup);

        iterHoldFlag.strip().upperCase();
        iterAuthorization.strip().upperCase();
        iterAddrCode.strip().upperCase();

		/*Only change Hold Mail flag when 
          1. Changing Return Mail from NO to YES and Hold Mail flag is NO.
          2. Changing Return Mail from YES to NO and Authorization is not Default/Permanent.
        */
		if ( iterAddrCode == dstrAddrCode && 
			 ((dstrRetMailFlag == YES && iterHoldFlag == NO) || 
              (dstrRetMailFlag == NO && iterAuthorization != AUTHORIZATION_CODE::DEFAULT && 
                                        iterAuthorization != AUTHORIZATION_CODE::PERMANENT)))
		{
			setFieldNoValidate((*iter).second->getHold(), dstrHoldFlag, idDataGroup,false,true,false,false);
		}

		++iter;
	}

	setObjectUpdated(idDataGroup);

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AccountMailingInfo.cpp-arc  $
 * 
 *    Rev 1.44   Jan 19 2012 12:10:26   wp040132
 * Minerva ISF Code changes..
 * 
 *    Rev 1.43   06 Oct 2008 13:16:32   kovacsro
 * PET142007  FN01 TFSA
 * 
 *    Rev 1.42   12 Sep 2008 15:40:40   kovacsro
 * PET142007.FN01 Tax Free Saving Account - code cleanup for taxType=0
 * 
 *    Rev 1.41   Jul 28 2006 10:44:08   fengyong
 * Incident #672869 - Ret mail flag refresh
 * 
 *    Rev 1.40   Jan 10 2006 16:45:48   popescu
 * Incident#  513604 - delinked ContractNotes doc type; the defaults will be based on the values read from view 352.
 * 
 *    Rev 1.39   Sep 29 2005 17:03:30   yingbaol
 * PET1277,FN09: validate hold authorization at the end.
 * 
 *    Rev 1.38   Sep 21 2005 16:44:40   yingbaol
 * PEt1277,FN09: Investment Fund Continuous Disclosure
 * 
 *    Rev 1.37   Apr 14 2005 13:13:48   Fengyong
 * Incident #250821 - default the Non Financial Confirm address code to '02' for Nominee or Intermediary account during NASU flow.
 * 
 *    Rev 1.36   Jan 11 2005 16:53:46   yingbaol
 * PTS10037681: Change code for Contribution receipt from 17 to 
 * 19( base code has use code 17 and 18 for something else).
 * 
 *    Rev 1.35   Dec 07 2004 16:29:00   hernando
 * PET1137 FN01 - Additional Epost changes.
 * 
 *    Rev 1.34   Dec 02 2004 11:36:42   yingbaol
 * PET1137,FN01: Add Epost functionality.
 * 
 *    Rev 1.33   Nov 14 2004 14:24:42   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.32   Dec 17 2003 10:35:26   linmay
 * PTS #10025277, set ContrHold to readonly, etc.
 * 
 *    Rev 1.31   Aug 27 2003 18:27:46   YINGBAOL
 * temporarily fix PTS10021218 
 * 
 *    Rev 1.30   Jul 31 2003 15:32:24   HERNANDO
 * PTS 10020238 - Set Annual Report Hold, Semi-Annual Report Hold, and Prospectus Hold to Read Only.
 * 
 *    Rev 1.29   Jul 24 2003 16:26:22   YINGBAOL
 * PTS10019989
 * 
 *    Rev 1.28   Apr 15 2003 10:24:12   YINGBAOL
 * sync. version 1.25.1.0
 * 
 *    Rev 1.27   Apr 01 2003 16:43:34   FENGYONG
 * Comment out some readonly fields
 * 
 *    Rev 1.26   Mar 21 2003 17:54:54   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.25   Feb 27 2003 15:30:40   YINGBAOL
 * this change is help view Jacelin to fix the issue at view side( They need update Account mailing to change effective date at shareholder level)
 * 
 *    Rev 1.24   Feb 14 2003 16:24:46   linmay
 * added semiannualreport to the class
 * 
 *    Rev 1.23   Nov 07 2002 10:32:10   YINGBAOL
 * do not do related changes in the init
 * 
 *    Rev 1.22   Oct 30 2002 10:12:16   YINGBAOL
 * sync. up from old PVCS database
 * 
 *    Rev 1.22   Oct 21 2002 11:18:52   YINGBAOL
 * more business rules added
 * 
 *    Rev 1.21   Oct 11 2002 11:39:34   YINGBAOL
 * change doWaiveRelatedChange
 * 
 *    Rev 1.20   Oct 09 2002 14:35:38   YINGBAOL
 * add validateMailingOption
 * 
 *    Rev 1.19   Oct 08 2002 11:45:32   YINGBAOL
 * split list to mailing fields ---view change
 * 
 *    Rev 1.18   Oct 01 2002 14:19:44   YINGBAOL
 * set default value
 * 
 *    Rev 1.17   Sep 26 2002 09:55:50   YINGBAOL
 * tuning
 * 
 *    Rev 1.16   Sep 24 2002 10:48:54   YINGBAOL
 * small fix
 * 
 *    Rev 1.15   Sep 23 2002 15:21:28   YINGBAOL
 * more business rules added
 * 
 *    Rev 1.14   Aug 29 2002 12:54:54   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.13   Jul 17 2002 10:32:40   HSUCHIN
 * bug fix in setDefault where default mailing values were incorrect.  This is due to wrong data extraction.
 * 
 *    Rev 1.12   Jul 15 2002 10:15:22   HSUCHIN
 * no change - beautify source
 * 
 *    Rev 1.11   22 May 2002 18:26:12   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.10   24 May 2001 15:47:26   HSUCHIN
 * bug fix
 * 
 *    Rev 1.9   23 May 2001 16:17:50   SMITHDAV
 * Sync-up fixes.
 * 
 *    Rev 1.8   23 May 2001 14:34:46   HSUCHIN
 * sync up with 1.6.1.0 with logic for default mailing info
 * 
 *    Rev 1.7   03 May 2001 14:05:52   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.6   Dec 18 2000 14:20:44   HSUCHIN
 * minor optimization
 * 
 *    Rev 1.5   Dec 17 2000 20:22:20   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.4   Aug 15 2000 10:27:38   YINGBAOL
 * fix Nasu and other bugs for C2
 * 
 *    Rev 1.3   Aug 02 2000 11:07:52   KOVACSRO
 * fixes
 * 
 *    Rev 1.1   Feb 15 2000 18:57:22   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:59:48   SMITHDAV
 * Initial revision.
// 
//    Rev 1.14   Jan 25 2000 14:29:14   POPESCUS
// took out a redundant method in Shareholder
// 
//    Rev 1.13   Jan 23 2000 16:59:30   POPESCUS
// fixes related to accessing the lists and rolling back a cloned account
// 
//    Rev 1.12   Jan 21 2000 16:44:30   YINGBAOL
// change the way access other list
// 
//    Rev 1.11   Jan 21 2000 11:11:44   POPESCUS
// the user can change the account number and the shareholder number
// 
//    Rev 1.10   Jan 21 2000 09:08:06   YINGBAOL
// set a field no validate
// 
//    Rev 1.9   Jan 18 2000 18:18:06   POPESCUS
// check in for point release
// 
//    Rev 1.8   Jan 14 2000 15:07:50   YINGBAOL
// modify validation and setdefault values
// 
//    Rev 1.7   Jan 07 2000 10:41:56   BUZILA
// same
// 
//    Rev 1.6   Jan 07 2000 10:40:06   BUZILA
// ClassObjectInfo taken out
// 
//    Rev 1.5   Jan 06 2000 13:37:12   YINGBAOL
// change
// 
//    Rev 1.4   Dec 21 1999 10:13:36   YINGBAOL
// add validation
// 
//    Rev 1.3   Dec 17 1999 18:00:58   YINGBAOL
// added validation
// 
//    Rev 1.2   Dec 10 1999 17:31:14   WINNIE
// Add fields in field info section for view 114 update mailing info
// 
//    Rev 1.1   Dec 08 1999 09:48:30   YINGBAOL
// fix Nasu bug
*/



