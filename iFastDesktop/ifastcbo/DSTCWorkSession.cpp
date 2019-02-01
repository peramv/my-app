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
//    Copyright 2000 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : DSTCWorkSession.cpp
// ^AUTHOR : Bunch of cool dudes
// ^DATE   : Jan, 2001
//
//******************************************************************************

#include "stdafx.h"
#include <bfutil\bfguard.hpp>
#include <ifastdbrkr\dstcpersistentrequestor.hpp>
#include "dstcworksession.hpp"
#include "dstcusersession.hpp"
#include "dstcglobalsession.hpp"
#include "hostsubstitutionvalueslist.hpp"
#include "accountentityxref.hpp"
#include "brokerlist.hpp"
#include "clientBankInstructionsList.hpp"
#include "advisorlist.hpp"
#include "confirmation.hpp"
#include "entity.hpp"
#include "cloneaccount.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "mgmtcooptions2.hpp"
#include "shareholder.hpp"
#include "funddetaillist.hpp"
#include "funddetail.hpp"
#include "worksessiontradeslist.hpp"
#include "distributorrepository.hpp"
#include "fundbankinstructionslistrepository.hpp"
#include "agentbankinstructionslistrepository.hpp"
#include "financialinstitutionlistrepository.hpp"
#include "bankinstructionslist.hpp"
#include "FundMaster.hpp"
#include "FundMasterList.hpp"
#include "Settlement.hpp"
#include "FeeParamSysSearchCriteria.hpp"
//#include "FeeModelCopyToGroupList.hpp"
#include "exchratelist.hpp"
#include "AmsMstrList.hpp"
#include "ifastcommonreportcriteria.hpp"
#include "protectedfundlist.hpp"
#include "MktIndexMasterList.hpp"
#include "MktIndexValuesList.hpp"
#include "tradesearchcriteria.hpp"
#include "neqdetailslist.hpp"
#include "BrokerAMSsearch.hpp"
#include "ManualDividendList.hpp"
#include "SysLvlSettlementInstrList.hpp"
#include "dailytransactionsfeesrepository.hpp"
#include "WhereUsedList.hpp"
#include "FeeModelList.hpp"
#include "FundSponsorFeeModelList.hpp"
#include "MsgProcessCBOList.hpp"
#include "MsgDetailList.hpp"
#include "MessageEnvelopeList.hpp"
#include "FileSearchCriteria.hpp"
#include "TransCancellist.hpp"
#include "opcconfirmreprint.hpp"
#include "CancelInstrSearchCriteria.hpp"
#include "BulkCancellist.hpp"
#include "savingsdirective.hpp"
#include "dilutionalloclist.hpp"
#include "chequelist.hpp"
#include "residency.hpp"
#include "systemverificationdetailslist.hpp"
#include "systemverificationdetails.hpp"
#include "familycodelist.hpp"
#include "familycode.hpp"
#include "translationtable.hpp" 
#include "holdingcomplist.hpp" 
#include "FinInstRegDetlList.hpp"
#include "FATCAMasterList.hpp"
#include "BatchInfoList.hpp"
#include "InvestmentHistoryList.hpp"
#include "ProgressiveIntRateList.hpp"
#include "InterestSegmentList.hpp"
#include "TransactionList.hpp"
#include "TradeVerificationSearch.hpp"
#include "TradeVerificationList.hpp"
#include "TradeOverideRuleWarningsList.hpp"
#include "AcctGrpConfigList.hpp"
#include "RESPRegMstrList.hpp"
#include "SoftCappedValidation.h"
#include "ExternalInstitutionList.hpp"
#include "FundRuleList.hpp"
#include "FundGroupTypeList.hpp"
#include "AcctCutOffTimesList.hpp"
#include "RESPRegRuleList.hpp"

// Transaction Builders
#include "dstcmfaccounttrxnbuilder.hpp"
#include "dstcmfshareholdertrxnbuilder.hpp"
#include "dstcaccountentitytrxnbuilder.hpp"
#include "dstcdistributorrepositorytrxnbuilder.hpp"
#include "dstcentitytrxnbuilder.hpp"
#include "dstctradestrxnbuilder.hpp"
#include "dstcbankinstructionstrxnbuilder.hpp"
#include "dstcadvisortrxnbuilder.hpp"
#include "dstcfinancialinstitutiontrxnbuilder.hpp"
#include "dstcsettlementtrxnbuilder.hpp"
#include "dstcamstrxnbuilder.hpp"
#include "dstcreporttrxnbuilder.hpp"
#include "dstcprotectedfundtrxnbuilder.hpp"
#include "dstcmktindexmastertrxnbuilder.hpp"
#include "dstcmktindexvaluestrxnbuilder.hpp"
#include "dstcresetinstrtrxnbuilder.hpp"
#include "dstcbrokeramstrxnbuilder.hpp"
#include "dstcmanualdividendtrxnbuilder.hpp"
#include "dstcSysLvlSettlementInstrtrxnbuilder.hpp"
#include "dstcdailytransactionsfeestrxnbuilder.hpp"
#include "dstcconfirmreprinttrxnbuilder.hpp"
#include "dstcbulkcanceltrxnbuilder.hpp"
#include "dstcsavingsdirectivetrxnbuilder.hpp"
#include "dstctranshistdilutionalloclisttrxnbuilder.hpp"
#include "dstccloneaccounttrxnbuilder.hpp"
#include "DSTCAcctSettlementRuleTrxnBuilder.hpp"
#include "DSTCChequeTxnbuilder.hpp"
#include "DSTCAcctRegDetailsTrxnBuilder.hpp"
#include "DSTCEntityRegDetailsTrxnBuilder.hpp"
#include "dstcholdingcomptrxnbuilder.hpp"
#include "DSTCTradeVerificationTrxnBuilder.hpp"
#include "DSTCEntityRiskTrxnBuilder.hpp"
#include "DSTCAcctRoundingRuleTrxnBuilder.hpp"
#include "AcctCutOffTimesTrxnBuilder.hpp"


// Required DataSets                       
#include <ifastdataimpl\dse_dstc0004_vw.hpp>
#include <ifastdataimpl\dse_dstc0050_vw.hpp>
#include <ifastdataimpl\dse_dstc0056_vw.hpp>
#include <ifastdataimpl\dse_dstc0074_vw.hpp>
#include <ifastdataimpl\dse_dstc0083_vw.hpp>
#include <ifastdataimpl\dse_dstc0161_vw.hpp>
#include <ifastdataimpl\dse_dstc0467_vw.hpp>
#include <ifastdataimpl\dse_dstcglob_vw.hpp>

#include "worksessionentitylist.hpp"
#include "DSTCFeeParamSysTxnBuilder.hpp"
#include "resetinstrlist.hpp"

#include "ifasthosttransactioncontainer.hpp"

#include "DSTCFundSponsorFeeModelTxnBuilder.hpp"
#include "DSTCFeeModelTxnBuilder.hpp"
#include "DSTCBrokerRemarkTxnBuilder.hpp"
#include "RemarkContainer.hpp"
#include "FundBrokerList.hpp"
#include "DSTCFundBrokerTxnBuilder.hpp"
#include "AggregatedOrderList.hpp"
#include "DSTCAggregateOrderTrxnBuilder.hpp"
#include "DSTCTransCancelTrxnBuilder.hpp"

#include "grouplist.hpp"
#include "group.hpp"

namespace CND
{	
   extern const long ERR_CBO_WARNING_NOT_DEFINED;   

   // returned by persistent view 74
   extern const long WARN_SETTLEMENT_NOT_ALL_TRADES_SETTLED;   
   extern const long WARN_TRADE_UNIT_ADJ_REQ_FOR_ACCOUNT;

   // returned by non-persistant, update view - 338
   extern const long WARN_CANCEL_GUAR_ADJ_EXIST_FOR_ACCT_CONTRACT_AFTR_TRADE_DATE;   

   extern const long WARN_PLEASE_CANCEL_MONEY_OUT_TRANSACTION;
   extern const long WARN_TRANS_NOT_ALLOWED_DURING_SETTLMENTPHASE;
   extern const long WARN_SEG_MANUAL_EVENTS_SINCE_ORIGINAL_TRADE_DATE;

   extern const long WARN_PURCHASE_ANNUITANT_OLDER_THAN_LATEST_AGE;
   extern const long WARN_FUND_CLASS_NOT_AVAILABLE_FOR_PURCHASE;
}

namespace
{
   const I_CHAR * const CLASSNAME             = I_( "DSTCWorkSession" );
   const I_CHAR * const COMMIT                = I_( "commit" );
   const I_CHAR * const BUILDTRANSACTIONS     = I_( "buildTransactions" );
   const I_CHAR * const ORDERTRXN             = I_( "orderTrxn" );
   const I_CHAR * const REFRESHDATA           = I_( "refreshData" );
   const I_CHAR * const GETVALUEFORTAG        = I_( "getValueForTag" );
   const I_CHAR * const ADDTAG                = I_( "addTag" );
   const I_CHAR * const GETHOSTACCOUNTNUM     = I_( "getHostAccountNum" );
   const I_CHAR * const GETHOSTSHAREHOLDERNUM = I_( "getHostShareholderNum" );
   const I_CHAR * const GETHOSTENTITYID       = I_( "getHostEntityId" );

   const I_CHAR * const NEW_PRFX              = I_( "999" );

   BFCritSec g_newKeyLock;

   const long hostConditionArray[][2] = 
   { 
      { CND::ERR_CBO_WARNING_NOT_DEFINED                                 , -1 },       
      { CND::WARN_SETTLEMENT_NOT_ALL_TRADES_SETTLED                      , 700 },
      { CND::WARN_TRADE_UNIT_ADJ_REQ_FOR_ACCOUNT                         , 677 },    
      { CND::WARN_CANCEL_GUAR_ADJ_EXIST_FOR_ACCT_CONTRACT_AFTR_TRADE_DATE, 674 },  
      { CND::WARN_PLEASE_CANCEL_MONEY_OUT_TRANSACTION                    , 685 }, 
      { CND::WARN_TRANS_NOT_ALLOWED_DURING_SETTLMENTPHASE                , 483 },  // it should be an ACL error here, not rej-error
      { CND::WARN_SEG_MANUAL_EVENTS_SINCE_ORIGINAL_TRADE_DATE            , 719 }, 
      { CND::WARN_PURCHASE_ANNUITANT_OLDER_THAN_LATEST_AGE               , 468 }, 	
      { CND::WARN_FUND_CLASS_NOT_AVAILABLE_FOR_PURCHASE                  , 469 }, 	       	   
      { -1L, -1L}
   };

}

extern BF_OBJ_TYPE OBJ_TYPE_MFACCOUNT;
extern BF_OBJ_TYPE OBJ_TYPE_ACCOUNTENTITY;
extern BF_OBJ_TYPE OBJ_TYPE_ENTITY;
extern BF_OBJ_TYPE OBJ_TYPE_SHAREHOLDER;
extern BF_OBJ_TYPE OBJ_TYPE_TRADES_LIST;
extern BF_OBJ_TYPE OBJ_TYPE_AGENT;
extern BF_OBJ_TYPE OBJ_TYPE_DISTRIBUTOR_REPOSITORY;
extern BF_OBJ_TYPE OBJ_TYPE_FUND_BANK_LIST;
extern BF_OBJ_TYPE OBJ_TYPE_CLIENT_BANK_INSTRUCTIONS_LIST;
extern BF_OBJ_TYPE OBJ_TYPE_SETTLEMENT_SEARCH;
extern BF_OBJ_TYPE OBJ_TYPE_BROKER;
extern BF_OBJ_TYPE OBJ_TYPE_AMS_GLOBAL;
extern BF_OBJ_TYPE OBJ_TYPE_REPORT;
extern BF_OBJ_TYPE OBJ_TYPE_FEEPARAM_SYSTEM;
extern BF_OBJ_TYPE OBJ_TYPE_PROTECTED_FUND_LIST;
extern BF_OBJ_TYPE OBJ_TYPE_MKT_INDEX_MASTER;
extern BF_OBJ_TYPE OBJ_TYPE_RESET_INSTR;
extern BF_OBJ_TYPE OBJ_TYPE_MKT_INDEX_VALUES;
extern BF_OBJ_TYPE OBJ_TYPE_BROKER_AMS_SEARCH;
extern BF_OBJ_TYPE OBJ_TYPE_MANUAL_DIVIDEND_LIST;
extern BF_OBJ_TYPE OBJ_TYPE_FINANCIAL_INSTITUTION_REPOSITORY;
extern BF_OBJ_TYPE OBJ_TYPE_FUND_BANK_INSTRUCTIONS_LIST_REPOSITORY;
extern BF_OBJ_TYPE OBJ_TYPE_DISTRIBUTOR_BANK_INSTR;
extern BF_OBJ_TYPE OBJ_TYPE_SETTLEMENT_LOCATION_SYSLVL_LIST;
extern BF_OBJ_TYPE OBJ_TYPE_DAILY_TRANSACTIONS_FEES_REPOSITORY;
extern BF_OBJ_TYPE OBJ_TYPE_FEE_MODEL_LIST;
extern BF_OBJ_TYPE OBJ_TYPE_FUND_SPONSOR_FEE_MODEL_LIST;
extern BF_OBJ_TYPE OBJ_TYPE_REMARK_CONTAINER;
extern BF_OBJ_TYPE OBJ_TYPE_FUND_BROKER_LIST;
extern BF_OBJ_TYPE OBJ_TYPE_AGGREGATED_ORDER_LIST;
extern BF_OBJ_TYPE OBJ_TYPE_MSG_PROCESS_LIST;
extern BF_OBJ_TYPE OBJ_TYPE_MSG_DETAIL_LIST;
extern BF_OBJ_TYPE OBJ_TYPE_MSG_ENVELOPE_LIST;
extern BF_OBJ_TYPE OBJ_TYPE_FILE_SEARCH;
extern BF_OBJ_TYPE OBJ_TYPE_TRANS_CANCEL;
extern BF_OBJ_TYPE OBJ_TYPE_CONFIRM_REPRINT;
extern BF_OBJ_TYPE OBJ_TYPE_BULK_CANCEL;
extern BF_OBJ_TYPE OBJ_TYPE_SAVINGS_DIRECTIVE;
extern BF_OBJ_TYPE OBJ_TYPE_TRANS_HIST_DILUTION_ALLOC_LIST;
extern BF_OBJ_TYPE OBJ_TYPE_CLONE_ACCOUNT;
extern BF_OBJ_TYPE OBJ_TYPE_ACCT_SETTLEMENT_RULE;
extern BF_OBJ_TYPE OBJ_TYPE_CHEQUE_LIST;
extern BF_OBJ_TYPE OBJ_TYPE_INVESTMENT_HISTORY;
extern BF_OBJ_TYPE OBJ_TYPE_AGENT_BANK_INSTRUCTIONS_LIST_REPOSITORY;
extern BF_OBJ_TYPE OBJ_TYPE_HOLDING_COMP;
extern BF_OBJ_TYPE OBJ_TYPE_FIN_INST_REG_DETL_LIST;
extern BF_OBJ_TYPE OBJ_TYPE_ACCT_REG_DETAILS_LIST;
extern BF_OBJ_TYPE OBJ_TYPE_TRANSACTION_DETAILS;
extern BF_OBJ_TYPE OBJ_TYPE_TRADEVERIFICATION_LIST;
extern BF_OBJ_TYPE OBJ_TYPE_TRADEVERIFICATION_ERROR_LIST;
extern BF_OBJ_TYPE OBJ_TYPE_ACCT_ROUNDING_RULE_LIST;
extern BF_OBJ_TYPE OBJ_TYPE_BROKERCUTOFF_LIST;

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId EntityId;
   extern CLASS_IMPORT const BFTextFieldId    RunMode;
   extern CLASS_IMPORT const BFTextFieldId    BirthFirstName;
   extern CLASS_IMPORT const BFTextFieldId    BirthLastName;
   extern CLASS_IMPORT const BFTextFieldId    AcctNumCtrl;
   extern CLASS_IMPORT const BFTextFieldId    ShrNumCtrl;
   extern CLASS_IMPORT const BFTextFieldId    CompanyId;
   extern CLASS_IMPORT const BFTextFieldId    ClientID;
   extern CLASS_IMPORT const BFNumericFieldId Contact1EntityID;
   extern CLASS_IMPORT const BFNumericFieldId Contact2EntityID;  
   extern CLASS_IMPORT const BFTextFieldId    UpdAllNonFin;
   extern CLASS_IMPORT const BFTextFieldId    WorkType;
   extern CLASS_IMPORT const BFTextFieldId    AWDObjectId;
   extern CLASS_IMPORT const BFTextFieldId    AWDCrda;
   extern CLASS_IMPORT const BFTextFieldId    BusinessArea;
   extern CLASS_IMPORT const BFTextFieldId    NonregLike;
   extern CLASS_IMPORT const BFTextFieldId    VerifyCategory;
   extern CLASS_IMPORT const BFTextFieldId    QESIClient;
   extern CLASS_IMPORT const BFTextFieldId    GroupCode;
   extern CLASS_IMPORT const BFTextFieldId    HasGWOContract;
   extern CLASS_IMPORT const BFTextFieldId IsNonTrustee;
   extern CLASS_IMPORT const BFTextFieldId NEQ1;
   extern CLASS_IMPORT const BFNumericFieldId TransNum;
   extern CLASS_IMPORT const BFTextFieldId IsSoftCapped;
}

namespace TRXNTAG
{
    const I_CHAR* SHRTAG                 = I_( "ShrNum" );
    const I_CHAR* ACCTTAG                = I_( "AccountNum" );
    const I_CHAR* ADDRESSTAG             = I_( "Address" );
    const I_CHAR* ENTITYIDTAG            = I_( "EntityId" );
    const I_CHAR* ENTITYIDSTAG           = I_( "EntityIds" );
    const I_CHAR* ACCTENTITYTAG          = I_( "AccountEntity" );
    const I_CHAR* DEMOGRAPHICSTAG        = I_( "DemoShrNum" );
    const I_CHAR* DISTRIBUTIONTAG        = I_( "DistributionAcctNum" );
    const I_CHAR* SYSACCTNUMTAG          = I_( "SystematicAcctNum" );
    const I_CHAR* TRADEACCTNUMTAG        = I_( "TradeAcctNum" );
    const I_CHAR* SHRBANKTAG             = I_( "BankingShrNum" );
    const I_CHAR* TRANSTYPETAG           = I_( "TransType" );
    const I_CHAR* PAYTYPETAG             = I_( "PayType" );
    const I_CHAR* FUNDTAG                = I_( "FundCode" );
    const I_CHAR* CLASSTAG               = I_( "ClassCode" );
    const I_CHAR* EFFDATETAG             = I_( "EffectiveDate" );
    const I_CHAR* STATUSTAG              = I_( "StatusCode" );
    const I_CHAR* ADDRCODETAG            = I_( "AddrCode" );
    const I_CHAR* ACCTMAILINGTAG         = I_( "AcctMailing" );
    const I_CHAR* REMARKSTAG             = I_( "Remarks" );
    const I_CHAR* ENTADDRTAG             = I_( "EntityAddress" );
    const I_CHAR* ALLOCTAG               = I_( "AllocShrNum" );
    const I_CHAR* TRANSNUMTAG            = I_( "TransNum" );
    const I_CHAR* RRIFINFOTAG            = I_( "RRIF_LIF_LRIFInfoList" );
    const I_CHAR* RIFIDTAG               = I_( "RIFId" );
    const I_CHAR* CONTRACTTAG            = I_( "ContractAcctNum" );
    const I_CHAR* CONTRACTTYPETAG        = I_( "ContractType" );
    const I_CHAR* ISSUEDATETAG           = I_( "IssueDate" );
    const I_CHAR* ASPENSIONTAG           = I_( "AsPensionAcctNum" );
    const I_CHAR* ACCTSPLITCOMMTAG       = I_( "AcctSplitCommNum" );
    const I_CHAR* ESOPTAG                = I_( "ESoPAcctNum" );
    const I_CHAR* FEEPARAMTAG            = I_( "FeeParaAccountNum" );
    const I_CHAR* PENSIONINFOPARAMTAG    = I_( "PensionInfo" );
    const I_CHAR* SETTLEMENTTAG          = I_( "SettlementTrades" );
    const I_CHAR* ACCTENTITYADDRMAILTAG  = I_( "AccountEntityAddressMailingInfo" );
    const I_CHAR* AMSCODETAG             = I_( "AMSCODE" );
    const I_CHAR* AMSMSTRINFOTAG         = I_( "AMSMstrInfo" );
    const I_CHAR* REPORTIDTAG            = I_( "Report" );
    const I_CHAR* SHRFAMILYTAG           = I_( "ShareholderFamily" );
    const I_CHAR* FEEPARAMSYSTAG         = I_( "FeeParamSys" );
    const I_CHAR* FEETAG                 = I_( "FeeCode" );
    const I_CHAR* FEEMODELTAG            = I_( "FeeModelCode" );
    const I_CHAR* FUNDSPONSORTAG         = I_( "FundSponsorCode" );
    const I_CHAR* WHEREUSEDTAG           = I_( "WhereUsedTag" );
    const I_CHAR* CLIENTBANK             = I_( "ClientBank" );
    const I_CHAR* FUNDBANK               = I_( "FundBank" );
    const I_CHAR* AMSLMTTAG              = I_( "AMSLmtOverride" );
    const I_CHAR* RULETYPETAG            = I_( "RuleType" );
    const I_CHAR* DIRECTTRADINGTAG       = I_( "DirectTradingAgreement" );
    const I_CHAR* COMMGROUPTAG           = I_( "CommGroupCode" );
    const I_CHAR* ACCTCATEGORYTAG        = I_( "AccountCategory" );
    const I_CHAR* AMSBROKERTAG           = I_( "BrokerAMSsearch" );
    const I_CHAR* ACCTMAILINGOVERRIDETAG = I_( "MailingOverride" );
    const I_CHAR* FUNDBROKERTAG          = I_( "FundBroker" );
    const I_CHAR* FUNDBROKERCODETAG      = I_( "FundBrokerCode" );
    const I_CHAR* EXEMPTTAG              = I_( "TaxExemptAuthorization" );
    const I_CHAR* BULKCANCELTAG          = I_( "BulkCancellation" );
    const I_CHAR* SAVDIRECTIVETAG        = I_( "SavingsDirective" );
    const I_CHAR* AMSACCTLVLTAG          = I_( "AMSAcctLevel" );
    const I_CHAR* ACCTSETTLEMENTRULETAG  = I_( "AcctLevelSettlementRule" );
    const I_CHAR* TRADEAUTHORIZATIONTAG  = I_( "TradeAuthorization" );
    const I_CHAR* TRADESOURCEOFFUNDTAG   = I_( "SourceofFundsChecked" );
    const I_CHAR* ACCTGUARNTGUARDOPTNTAG = I_( "AcctGuarntGuardOptn" );
    const I_CHAR* CONTRACTMATINSTRTAG    = I_( "ContractMatInstr" );
    const I_CHAR* ACCTCOMMTAG            = I_( "AccountCommitment" );
    const I_CHAR* ACCTREGDETAILS         = I_( "AcctRegDetails" );
    const I_CHAR* ENTITYREGDETAILS       = I_( "EntityRegDetails" );
    const I_CHAR* ENTITYREGJURISDETAILS  = I_( "EntityRegJurisDetails" );
    const I_CHAR* TRADEVERIFICATION      = I_( "TradeVerification" );
    const I_CHAR* DEMOGRAPHICS_CHILD_TAG = I_( "KYCAttrib" );
	const I_CHAR* PENDINGTRADEERRORTAG   = I_( "PEndingTradeError" );
    const I_CHAR* ENTITYRISKTAG          = I_( "EntityRisk" );
	const I_CHAR* ACCTROUNDINGRULETAG	 = I_( "AcctRoundingRule" );

    //not visible to the outside world
    const I_CHAR* TRXGRPID  = I_( "TrxnGrpId" );
    const I_CHAR* EQ        = I_( "=" );
    const I_CHAR* SEMICOLON = I_( ";" );   
}

namespace SHRACCGROUPING
{
   //this constants shouldn't be modified;
   //they will define the order of the trxns 
   //in a persistent group
   const long SHR               = 1;    //view 75
   const long ACCT              = 2;    //view 76
   const long MAILING           = 3;    //view 114
   const long MAILING_OVERRIDE  = 4;    //view 216
   const long ADDRESS           = 5;    //view 72
   const long ENTITY            = 6;    //view 78
   const long ENTITYIDS         = 7;    //view 79
   const long ACCTENTITY        = 8;    //view 77
   const long OTHER             = 9;
}

namespace KEYTYPES
{
   extern CLASS_IMPORT I_CHAR * const ENTITYID;
   extern CLASS_IMPORT I_CHAR * const SHRNUM;
   extern CLASS_IMPORT I_CHAR * const ACCOUNTNUM;
   extern CLASS_IMPORT I_CHAR * const TRANSID;
}

namespace RUNMODE 
{
   const I_CHAR* ADDED     = I_( "A" );
   const I_CHAR* MODIFIED  = I_( "M" );
   const I_CHAR* DELETED   = I_( "D" );
   const I_CHAR* UNCHANGED = I_( "U" );
}

namespace FUND_RULE_TYPE
{
   extern CLASS_IMPORT I_CHAR * const SOFT_CAPPED;
}


//******************************************************************************
const DSTCWorkSession::HostConditionMap DSTCWorkSession::_hostConditions ( hostConditionArray );


MutexSemaphore DSTCWorkSession::_trxnGroupSemaphore;
long DSTCWorkSession::_maxTrxnGroup = 1;


//*****************************************************************
DSTCWorkSession::DSTCWorkSession( const DString& mgmtCoId, DSTCUserSession &userSession)
: BFWorkSession( userSession, ifds::DSTCGLOB_VW ),
_currentMgmtCo (NULL),
_lKey(0),
_hostSubstitutionList (NULL),
m_commitParams (NULL)
{

   // ManagementCompany need not be refreshed every time a WorkSession is created.
   // If the aquire fails, there is a problem somewhere else....
   // dynamic_cast<DSTCGlobalSession *>(getGlobalSession())->refreshMgmtCo( mgmtCoId );

   try
   {
      _currentMgmtCo = dynamic_cast<DSTCGlobalSession &>(getGlobalSession()).aquireMgmtCo( mgmtCoId );

   }
   catch( ConditionException &/*ce*/ )
   {
      throw;
   }
   catch( ... )
   {
      throw;
   }

   try
   {
      DString clientId;
      _currentMgmtCo->getField( ifds::ClientID, clientId, BF::HOST );
      clientId.lowerCase ();
      setClient( clientId );
   }
   catch( ... )
   {
      dynamic_cast<DSTCGlobalSession &>(getGlobalSession()).freeMgmtCo( _currentMgmtCo );
      throw;
   }

   _commitConditions = new CONDITIONVECTOR;
}
//*****************************************************************
DSTCWorkSession::~DSTCWorkSession()
{
   dynamic_cast<DSTCGlobalSession &>(getGlobalSession()).freeMgmtCo( _currentMgmtCo );

   delete _hostSubstitutionList;
   delete _commitConditions;
}

//******************************************************************************
const MgmtCo &
DSTCWorkSession::getMgmtCo() const
{
   return(*_currentMgmtCo);
}

//******************************************************************************
MgmtCo &
DSTCWorkSession::getMgmtCo()
{
   return(*_currentMgmtCo);
}

//******************************************************************************
// Please do not use this setMgmtCo function -- unless your very careful and it's absolutely necessary...
// 
// This function has the potential of creating inconsistent data if the _currentMgmtCo
// is changed while there are still child objects that have data derived from other mgmtCo's.
//
// I hope to try to remove this function in the near future...
//
void 
DSTCWorkSession::setMgmtCo( const DString& mgmtCoId )
{
   DSTCGlobalSession &gs = dynamic_cast<DSTCGlobalSession &>(getGlobalSession());

   BFCBO::cleanBFPropertyRepository();
   gs.freeMgmtCo( _currentMgmtCo );
   _currentMgmtCo = gs.aquireMgmtCo( mgmtCoId );

   DString clientId;
   _currentMgmtCo->getField( ifds::ClientID, clientId, BF::HOST );
   clientId.lowerCase ();
   setClient( clientId );
}

MgmtCoOptions *
DSTCWorkSession::getMgmtCoOptions() const
{
   MgmtCoOptions *pMgmtCoOptions;
   if( _currentMgmtCo->getMgmtCoOptions( pMgmtCoOptions ) > WARNING )
   {
      // TODO: throw something
      assert(0);
      throw;
   }

   return(pMgmtCoOptions);
}

MgmtCoOptions2 *
DSTCWorkSession::getMgmtCoOptions2() const
{
   MgmtCoOptions2 *pMgmtCoOptions;
   if( _currentMgmtCo->getMgmtCoOptions2( pMgmtCoOptions ) > WARNING )
   {
      // TODO: throw something
      assert(0);
      throw;
   }

   return(pMgmtCoOptions);
}

//******************************************************************************
SEVERITY
DSTCWorkSession::getOption( const BFFieldId& idField, DString &strValueOut, const BFDataGroupId& idDataGroup, bool formatted /*= true*/ ) const
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getOption" ) );

   MgmtCoOptions *pMgmtCoOptions = NULL;
/*this is for testing only:
    if (idField == ifds::AcctNumCtrl)
   {
      ConfigManager *pDSTCMgr = ConfigManager::getManager(I_("MFDSTC") );
      Configuration cfgAcctCtrl = pDSTCMgr->retrieveConfig( I_("AcctNumCtrl"));
      strValueOut = cfgAcctCtrl.getValueAsString( I_("AcctNumCtrl") );
      return NO_CONDITION;
   }
   if (idField == ifds::ShrNumCtrl)
   {
      ConfigManager *pDSTCMgr = ConfigManager::getManager(I_("MFDSTC") );
      Configuration cfgAcctCtrl = pDSTCMgr->retrieveConfig( I_("AcctNumCtrl"));
      strValueOut = cfgAcctCtrl.getValueAsString( I_("ShrNumCtrl") );
      return NO_CONDITION;
   }
*/
   if( _currentMgmtCo->getMgmtCoOptions( pMgmtCoOptions ) <= WARNING )
   {
      pMgmtCoOptions->getField( idField, strValueOut, idDataGroup, formatted );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY 
DSTCWorkSession::getOption2( const BFFieldId& idField, DString &strValueOut, const BFDataGroupId& idDataGroup, bool formatted /*= true*/ ) const
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getOption" ) );

   MgmtCoOptions2 *pMgmtCoOptions = NULL;
   if( _currentMgmtCo->getMgmtCoOptions2( pMgmtCoOptions ) <= WARNING )
   {
      pMgmtCoOptions->getField( idField, strValueOut, idDataGroup, formatted );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void 
DSTCWorkSession::getFirstSequenced01AccountholderEntityName( const BFDataGroupId& idDataGroup, DString& AcctNum, DString &EntityName, bool kanji /*=true*/ )
{
   EntityName = NULL_STRING;

   // get account owner name:
   DString EntityType;
   AccountEntityXref *_pAccountEntityXref;

   if( getAccountEntityXref( idDataGroup, _pAccountEntityXref ) <= WARNING )
   {
      if( _pAccountEntityXref->PopulateAccountOwner( idDataGroup, NULL_STRING, AcctNum, NULL_STRING, NULL_STRING ) <= WARNING )
      {
         BFObjIter iterAccountEntityXrefOut( *_pAccountEntityXref, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );
         DString searchKey;
         AccountEntityXref::buildPartialKeyForRetrievingEntity( searchKey, AcctNum, I_( "01" ), I_( "1" ) );

         if( iterAccountEntityXrefOut.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey ) )
         {
            DString LastName(I_("")), FirstName(I_(""));
            if( kanji ) //kanji
            {
               iterAccountEntityXrefOut.getObject()->getField( ifds::LastName, LastName, idDataGroup, false );
               iterAccountEntityXrefOut.getObject()->getField( ifds::FirstName, FirstName, idDataGroup, false );
            }
            else //kana
            {
               DString dstrEntityId;
               iterAccountEntityXrefOut.getObject()->getField( ifds::EntityId, dstrEntityId, idDataGroup, false );

               Entity *pEntity;
               getEntity( idDataGroup, dstrEntityId, pEntity );
               if( pEntity )
               {
                  pEntity->getField( ifds::BirthLastName, LastName, idDataGroup, false );
                  pEntity->getField( ifds::BirthFirstName, FirstName, idDataGroup, false );
               }
            }


            if( DSTCommonFunctions::getMarket() == MARKET_IDS::JAPAN )
            {
               EntityName = LastName.strip() + I_( " " ) + FirstName.strip(); // for japan
            }
            else // for Canada and any other market
            {
               if( LastName.strip() != NULL_STRING || FirstName.strip() != NULL_STRING )
                  EntityName = LastName.strip() + I_( ";" ) + FirstName.strip(); // for canada
            }
         }
      }
   }
}

//******************************************************************************
void 
DSTCWorkSession::getAccountholder01EntityName( const BFDataGroupId& idDataGroup, DString& AcctNum, DString &EntityName, bool kanji /*=true*/ )
{
   EntityName = NULL_STRING;

   // get account owner name:
   DString EntityType;
   AccountEntityXref *_pAccountEntityXref = new AccountEntityXref( *this );
   if( _pAccountEntityXref->init() > WARNING ) return;

   if( _pAccountEntityXref->PopulateAccountOwner( idDataGroup, NULL_STRING, AcctNum, NULL_STRING, NULL_STRING ) <= WARNING )
   {
         BFObjIter iterAccountEntityXrefOut( *_pAccountEntityXref, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );
         DString searchKey;
         AccountEntityXref::buildPartialKeyForRetrievingEntity( searchKey, AcctNum, I_( "01" ), I_( "1" ) );

         if( iterAccountEntityXrefOut.begin( OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE, searchKey ) )
         {
            DString LastName(I_("")), FirstName(I_(""));
            if( kanji ) //kanji
            {
               iterAccountEntityXrefOut.getObject()->getField( ifds::LastName, LastName, idDataGroup, false );
               iterAccountEntityXrefOut.getObject()->getField( ifds::FirstName, FirstName, idDataGroup, false );
            }
            else //kana
            {
               DString dstrEntityId;
               iterAccountEntityXrefOut.getObject()->getField( ifds::EntityId, dstrEntityId, idDataGroup, false );

               Entity *pEntity;
               getEntity( idDataGroup, dstrEntityId, pEntity );
               if( pEntity )
               {
                  pEntity->getField( ifds::BirthLastName, LastName, idDataGroup, false );
                  pEntity->getField( ifds::BirthFirstName, FirstName, idDataGroup, false );
               }
            }


            if( DSTCommonFunctions::getMarket() == MARKET_IDS::JAPAN )
            {
               EntityName = LastName.strip() + I_( " " ) + FirstName.strip(); // for japan
            }
            else // for Canada and any other market
            {
               if( LastName.strip() != NULL_STRING || FirstName.strip() != NULL_STRING )
                  EntityName = LastName.strip() + I_( ";" ) + FirstName.strip(); // for canada
            }
         }
   }
   delete _pAccountEntityXref;
   _pAccountEntityXref = NULL;
   
}
//******************************************************************************
bool 
DSTCWorkSession::getFundDetail(const DString& fundCode, const DString& classCode, 
   const BFDataGroupId& idDataGroup, FundDetail *&pFundDetail)
{
   bool found = false;
   FundDetailList *_pFundDetailList;

   if( _currentMgmtCo->getFundDetailList(_pFundDetailList) <= WARNING )
   {
      if( _pFundDetailList )
      {
         found = _pFundDetailList->getFundDetail(fundCode, classCode, idDataGroup, pFundDetail);
      }
   }
   return(found);
}


//******************************************************************************
void DSTCWorkSession::getFundName ( const DString &fundCode, 
                                    DString &fundName)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_( "getFundName" ));

   FundMasterList *_pFundMasterList;
   fundName = NULL_STRING;

   if ( getMgmtCo().getFundMasterList (_pFundMasterList) <= WARNING &&
       _pFundMasterList)
   {
      _pFundMasterList->getFundName (fundCode, fundName);
   }
}

//******************************************************************************
void DSTCWorkSession::GetFundNumber ( const DString &fundCode, 
                                      const DString &classCode, 
                                      DString &fundNumber
                                    )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("GetFundNumber")
                         );
   fundNumber = NULL_STRING;
   FundDetailList *pFundDetailList;

   if (_currentMgmtCo->getFundDetailList(pFundDetailList) <= WARNING)
   {
      if( pFundDetailList )
      {
         FundDetail *pFundDetail = NULL;
         if( pFundDetailList->getFundDetail( fundCode, classCode, BF::HOST, pFundDetail ) )
         {
            pFundDetail->getField( ifds::Baycom, fundNumber, BF::HOST );
            fundNumber.strip();
         }
      }
   }
}

//******************************************************************************
void DSTCWorkSession::GetISINNumber ( const DString &fundCode, 
												 const DString &classCode, 
                                      DString &isinNumber
                                    )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("GetISINNumber")
                         );
   isinNumber = NULL_STRING;
   FundDetailList *pFundDetailList;

   if (_currentMgmtCo->getFundDetailList(pFundDetailList) <= WARNING)
   {
      if( pFundDetailList )
      {
         FundDetail *pFundDetail;
         if( pFundDetailList->getFundDetail( fundCode, classCode, BF::HOST, pFundDetail ) )
         {
            pFundDetail->getField( ifds::FundISIN, isinNumber, BF::HOST );
            isinNumber.strip();
         }
      }
   }
}

//******************************************************************************
void DSTCWorkSession::GetWKNNumber ( const DString &fundCode, 
                                     const DString &classCode, 
                                     DString &wknNumber
                                   )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("GetWKNNumber")
                         );
   wknNumber = NULL_STRING;
   FundDetailList *pFundDetailList;

   if (_currentMgmtCo->getFundDetailList(pFundDetailList) <= WARNING)
   {
      if( pFundDetailList )
      {
         FundDetail *pFundDetail;
         if( pFundDetailList->getFundDetail( fundCode, classCode, BF::HOST, pFundDetail ) )
         {
            pFundDetail->getField( ifds::FundWKN, wknNumber, BF::HOST );
            wknNumber.strip();
         }
      }
   }
}

//******************************************************************************
void DSTCWorkSession::GetLFCNumber ( const DString &fundCode, 
                                     const DString &classCode, 
                                     DString &lfcNumber
                                   )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("GetLFCNumber")
                         );
   lfcNumber = NULL_STRING;
   FundDetailList *pFundDetailList;

   if (_currentMgmtCo->getFundDetailList(pFundDetailList) <= WARNING)
   {
      if( pFundDetailList )
      {
         FundDetail *pFundDetail;
         if( pFundDetailList->getFundDetail( fundCode, classCode, BF::HOST, pFundDetail ) )
         {
            pFundDetail->getField( ifds::FundLFC, lfcNumber, BF::HOST );
            lfcNumber.strip();
         }
      }
   }
}

//**********************************************************************************
void DSTCWorkSession::GetCUSIPNumber ( const DString &fundCode, 
                                       const DString &classCode, 
                                       DString &cusipNumber
									 )
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("GetCUSIPNumber")
                          );
	cusipNumber = NULL_STRING;
	FundDetailList *pFundDetailList;

	if (_currentMgmtCo->getFundDetailList(pFundDetailList) <= WARNING)
	{
		if( pFundDetailList )
		{
			FundDetail *pFundDetail;
			if( pFundDetailList->getFundDetail( fundCode, classCode, BF::HOST, pFundDetail ) )
			{
				pFundDetail->getField( ifds::CusipNum, cusipNumber, BF::HOST );
				cusipNumber.strip();
			}
		}
	}
}

//**********************************************************************************
bool DSTCWorkSession::GetFundClassCode ( const DString &fundNumber, 
                                         DString &fundCode, 
                                         DString &classCode
                                       )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("GetFundClassCode")
                         );

   bool bRet = false;
   FundDetailList *pFundDetailList;

   DString fundNumber_ (fundNumber);

   fundNumber_.strip().upperCase();
   fundCode = NULL_STRING;
   classCode = NULL_STRING;

   if (_currentMgmtCo->getFundDetailList (pFundDetailList) <= WARNING) 
   {
      if( pFundDetailList )
      {
         FundDetail *pFundDetail = NULL;
         pFundDetail = pFundDetailList->getFundDetailByFundNumber( fundNumber );
         if( pFundDetail )
         {
            pFundDetail->getField( ifds::FundCode, fundCode, BF::HOST );
            pFundDetail->getField( ifds::ClassCode, classCode, BF::HOST );
            fundCode.strip();
            classCode.strip();
            bRet = true;
         }
      }
   }
   return bRet;
}

//**********************************************************************************
bool DSTCWorkSession::GetFundClassCodeByISIN ( const DString &isinNumber, 
                                               DString &fundCode, 
                                               DString &classCode
                                             )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("GetFundClassCodeByISIN")
                         );
   bool bRet = false;
   FundDetailList *pFundDetailList;

   DString isinNumber_ (isinNumber);

   isinNumber_.strip().upperCase();
   fundCode = NULL_STRING;
   classCode = NULL_STRING;

   if (_currentMgmtCo->getFundDetailList (pFundDetailList) <= WARNING) 
   {
      if( pFundDetailList )
      {
         FundDetail *pFundDetail = NULL;
         pFundDetail = pFundDetailList->getFundDetailByISIN( isinNumber_ );
         if( pFundDetail )
         {
            pFundDetail->getField( ifds::FundCode, fundCode, BF::HOST );
            pFundDetail->getField( ifds::ClassCode, classCode, BF::HOST );
            fundCode.strip();
            classCode.strip();
            bRet = true;
         }
      }
   }
   return bRet;
}

//**********************************************************************************
bool DSTCWorkSession::GetFundClassCodeByWKN ( const DString &wknNumber, 
                                              DString &fundCode, 
                                              DString &classCode)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("GetFundClassCodeByWKN"));
   bool bRet = false;
   FundDetailList *pFundDetailList;

   DString wknNumber_ (wknNumber);

   wknNumber_.strip().upperCase();
   fundCode = NULL_STRING;
   classCode = NULL_STRING;

   if (_currentMgmtCo->getFundDetailList (pFundDetailList) <= WARNING) 
   {
      if( pFundDetailList )
      {
         FundDetail *pFundDetail = NULL;
         pFundDetail = pFundDetailList->getFundDetailByWKN( wknNumber_ );
         if( pFundDetail )
         {
            pFundDetail->getField( ifds::FundCode, fundCode, BF::HOST );
            pFundDetail->getField( ifds::ClassCode, classCode, BF::HOST );
            fundCode.strip();
            classCode.strip();
            bRet = true;
         }
      }      
   }
   return bRet;
}

//**********************************************************************************
bool DSTCWorkSession::GetFundClassCodeByLFC ( const DString &lfcNumber, 
                                              DString &fundCode, 
                                              DString &classCode)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("GetFundClassCodeByLFC"));
   bool bRet = false;
   FundDetailList *pFundDetailList;

   DString lfcNumber_ (lfcNumber);

   lfcNumber_.strip().upperCase();
   fundCode = NULL_STRING;
   classCode = NULL_STRING;

   if (_currentMgmtCo->getFundDetailList (pFundDetailList) <= WARNING) 
   {
      if( pFundDetailList )
      {
         FundDetail *pFundDetail = NULL;
         pFundDetail = pFundDetailList->getFundDetailByLFC( lfcNumber_ );
         if( pFundDetail )
         {
            pFundDetail->getField( ifds::FundCode, fundCode, BF::HOST );
            pFundDetail->getField( ifds::ClassCode, classCode, BF::HOST );
            fundCode.strip();
            classCode.strip();
            bRet = true;
         }
      }      
   }
   return bRet;
}
//******************************************************************************
bool DSTCWorkSession::GetFundClassCodeByCUSIP ( const DString &cusipNumber, 
                                              DString &fundCode, 
                                              DString &classCode)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("GetFundClassCodeByCUSIP"));
   bool bRet = false;
   FundDetailList *pFundDetailList;

   DString cusipNumber_ (cusipNumber);

   cusipNumber_.strip().upperCase();
   fundCode = NULL_STRING;
   classCode = NULL_STRING;

   if (_currentMgmtCo->getFundDetailList (pFundDetailList) <= WARNING) 
   {
      if( pFundDetailList )
      {
         FundDetail *pFundDetail = NULL;
         pFundDetail = pFundDetailList->getFundDetailByCUSIP( cusipNumber_ );
         if( pFundDetail )
         {
            pFundDetail->getField( ifds::FundCode, fundCode, BF::HOST );
            pFundDetail->getField( ifds::ClassCode, classCode, BF::HOST );
            fundCode.strip();
            classCode.strip();
            bRet = true;
         }
      }      
   }
   return bRet;
}
//******************************************************************************
void 
DSTCWorkSession::getDateInHostFormat(DString &Date, int DateRequired, const BFDataGroupId& idDataGroup) const
{
   switch( DateRequired )
   {
      case CURRENT_BUSINESS_DAY:
         getOption( ifds::CurrBusDate, Date, idDataGroup, false );
         break;
      case CURRENT_SYSTEM_DAY:
         getOption( ifds::CurrSysDate, Date, idDataGroup, false );
         break;
      case DAY12319999:
         {
            //  look in the registry for the date format mask
            DString dstrConfiguration( I_( "HostMasks" ) );
            DString dstrKey( I_("D") );

            Date = GetConfigValueAsString( I_( "LocaleFormats" ), 
                                           dstrConfiguration,
                                           dstrKey );

            Date.replace(Date.find(I_("MM")), 2, I_("12"));
            Date.replace(Date.find(I_("dd")), 2, I_("31"));
            Date.replace(Date.find(I_("yyyy")), 4, I_("9999"));
         }
         break;
   }
}

//******************************************************************************

SEVERITY 
DSTCWorkSession::isVerificationEnabled (const BFDataGroupId& idDataGroup, 
                                        const DString &dstrVerifyCategory, 
                                        const DString &dstrVerifyLevel,
                                        bool &bEnabled,
										DString &dstrVerifyFilter)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("isVerificationEnabled()"));

   DString dstrEnabled;

   bEnabled = false;

   SystemVerificationDetailsList *pSystemVerificationDetailsList = NULL;

   if (getMgmtCo().getSystemVerificationDetailsList (pSystemVerificationDetailsList) <WARNING && 
      pSystemVerificationDetailsList != NULL)
   {
      // does environemnt supports verificaiton process:
      pSystemVerificationDetailsList->canVerify (idDataGroup, dstrVerifyCategory, dstrVerifyLevel, dstrEnabled,dstrVerifyFilter);

      bEnabled = dstrEnabled == I_("Y") ? true : false;
   }

   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************

SEVERITY 
DSTCWorkSession::canVerify (const BFDataGroupId& idDataGroup, 
                            const DString &functionCode,
                            const DString &dstrVerifyCategory, 
                            const DString &dstrVerifyLevel,
                            const DString &dstrLastUser,
                            bool &bCanVerify)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("canVerify()"));

   bool bEnabled = false;

   // is verification enabled on environment level:
   isVerificationEnabled (idDataGroup, dstrVerifyCategory, dstrVerifyLevel, bEnabled);

   if (!bEnabled)
   {
      bCanVerify = false;
      return(GETCURRENTHIGHESTSEVERITY());
   }

   // does user have permission:
   bool bHasPermission = hasUpdatePermission (functionCode);

   // last mod user and current user must be different:
   DString dstrCurrentUser = dynamic_cast<const DSTCSecurity *> (getSecurity(DSTCHost::getPrimaryHost()))->getUserId();
   DString dstrLastModUser = dstrLastUser;
   dstrLastModUser.strip().upperCase();
   dstrCurrentUser.strip().upperCase();
   bool bDifferentUser = false;

   if ( dstrLastModUser != dstrCurrentUser )
   {
      bDifferentUser = true;
   }
   else
   {
      bDifferentUser = false;
   }

   bCanVerify = bEnabled && bHasPermission &&  bDifferentUser;

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY 
DSTCWorkSession::getNewMFAccount( const BFDataGroupId& idDataGroup, const DString& shrNum, MFAccount *&pAcctOut, const DString& strAccNum /*=NULL_STRING*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getNewMFAccount()" ) );

   DString newAccountNum;

   pAcctOut = new MFAccount( *this );
   //set the object as being new
   pAcctOut->setObjectNew();
   if( strAccNum == NULL_STRING )
      getNewKey( newAccountNum );
   else
      newAccountNum = strAccNum;


   if( pAcctOut->init( idDataGroup, newAccountNum, shrNum ) <= WARNING )
   {
      //the init method might modify the account num;
      DString accountNum;
      pAcctOut->getField( ifds::AccountNum, accountNum, idDataGroup );

      BFObjectKey objKey( accountNum, idDataGroup, OBJ_ACTIVITY_ADDED, OBJ_TYPE_MFACCOUNT );
      setObject( objKey, pAcctOut );
   }
   else
   {
      delete pAcctOut;
      pAcctOut = NULL;
   }
   return(GETCURRENTHIGHESTSEVERITY());

}

//******************************************************************************
SEVERITY 
DSTCWorkSession::getMFAccount( const BFDataGroupId& idDataGroup,  
                               const DString& strAcctNum, 
                               MFAccount *&pAcctOut,
                               const DString& dstrTrack,
                               const DString& dstrPageName, 
                               bool bCreate /*= true*/,
                               bool bValidateAccNum /*= false*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMFAccount()" ) );

   pAcctOut = NULL;

  DString strAccountNumTemp( strAcctNum );
  if (strAccountNumTemp.strip().stripLeading( '0' ).empty())
		return GETCURRENTHIGHESTSEVERITY();

   BFObjectKey objKey( strAccountNumTemp, idDataGroup, OBJ_ACTIVITY_NONE, OBJ_TYPE_MFACCOUNT );
   pAcctOut = dynamic_cast<MFAccount *>( findObject( objKey ) );

	if ( !pAcctOut && bCreate )
   {
      if( bValidateAccNum )
         if( MFAccount::validateAccountNum(strAccountNumTemp, *this) > WARNING )
            return(GETCURRENTHIGHESTSEVERITY());

      pAcctOut = new MFAccount( *this );
      //start with an empty account
      BFObjectKey objKey1( strAccountNumTemp, BF::HOST, OBJ_ACTIVITY_NONE, OBJ_TYPE_MFACCOUNT ); 
      setObject( objKey1, pAcctOut );
      pAcctOut->setField(ifds::AccountNum, strAccountNumTemp, BF::HOST, false, false, false);
      pAcctOut->clearUpdatedFlags(BF::HOST);
   }
   
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
SEVERITY DSTCWorkSession::getBatchList (BatchInfoList* &pBatchInfoList, 
										const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getBatchList"));

	DString strKey = I_("BatchInfoList");
   
    pBatchInfoList = dynamic_cast <BatchInfoList *> (getObject (strKey, idDataGroup));

	if (!pBatchInfoList)
	{
		pBatchInfoList = new BatchInfoList (*this);

		if (pBatchInfoList->init () <= WARNING)
		{
			setObject (pBatchInfoList, strKey, OBJ_ACTIVITY_NONE, idDataGroup);
		}
		else
		{
			delete pBatchInfoList;
			pBatchInfoList = NULL;
		}
	}
	else
	{
		pBatchInfoList->init ();
	}

	return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY DSTCWorkSession::getHoldingCompList(HoldingCompList* &pHoldingCompList, const BFDataGroupId &idDataGroup, 
                                             const DString& dstrHoldingCompCode, const DString& dstrHoldingCompName, 
                                             const DString& dstrAll, const DString& dstrEffDate, bool doViewCall, bool isProcSupport)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getHoldingCompList"));

   DString strKey = isProcSupport ? I_("HoldingCompListSupport") : I_("HoldingCompList");
   
   pHoldingCompList = dynamic_cast <HoldingCompList*> (getObject (strKey, idDataGroup));

	if (doViewCall || isProcSupport)
	{
		pHoldingCompList = new HoldingCompList(*this, dstrHoldingCompCode, dstrHoldingCompName, 
         dstrAll, dstrEffDate);

//		if (
         pHoldingCompList->init(idDataGroup);// <= WARNING) 
		{
         setObject (pHoldingCompList, strKey, OBJ_ACTIVITY_NONE, BF::HOST, OBJ_TYPE_HOLDING_COMP);
		}
		//else
		//{
		//	delete pHoldingCompList ;
		//	pHoldingCompList  = NULL;
		//}
	}

	return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
bool DSTCWorkSession::haveAccount(const DString& dstrAccountNumber) 
{
   AccountEntityXref *_pAccountEntityXref;

   if( getAccountEntityXref( BF::HOST, _pAccountEntityXref ) <= WARNING )
   {
         BFObjIter iterAccountEntityXrefOut( *_pAccountEntityXref, BF::HOST, true, BFObjIter::ITERTYPE::NON_DELETED );

         while( !iterAccountEntityXrefOut.end() )
         {
               DString dstrAcctNum, dstrEntityType;
               iterAccountEntityXrefOut.getObject()->getField( ifds::AccountNum, dstrAcctNum, BF::HOST, false );
               iterAccountEntityXrefOut.getObject()->getField( ifds::EntityType, dstrEntityType, BF::HOST, false );
               //account detail page only show account which have 01 entity type 
               if( dstrAcctNum == dstrAccountNumber && dstrEntityType ==I_("01") ) return true;
               ++iterAccountEntityXrefOut;
         }
   }
	return (false);
}
//******************************************************************************
SEVERITY 
DSTCWorkSession::PopulateMFAccount( const BFDataGroupId& idDataGroup, const BFData &accountData, MFAccount *&pAcctOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION,
                          CLASSNAME,
                          I_( "PopulateMFAccount( int, const BFData &, MFAccount *& )" ) );

   DString strAcctNum = accountData.getElementValue( ifds::AccountNum, 2 /*DataElement::USE_MASK*/ );
   strAcctNum.strip().stripLeading( I_CHAR( '0' ) );

   BFObjectKey objKey( strAcctNum, idDataGroup, OBJ_ACTIVITY_NONE, OBJ_TYPE_MFACCOUNT );
   MFAccount *pMFAccount = dynamic_cast<MFAccount*>( findObject( objKey ) );

   if( !pMFAccount )
   {
      pAcctOut = new MFAccount( *this );
      if( pAcctOut->init( accountData ) > SEVERE_ERROR )
      {
         delete pAcctOut;
         pAcctOut = NULL;
      }
      else
      {
         setObject( objKey, pAcctOut );
      }
   }
   else //get the account from the repository
   {
      pAcctOut = pMFAccount;
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY  
DSTCWorkSession::getAccountEntityXref( const BFDataGroupId& idDataGroup, AccountEntityXref *&pAccountEntityXrefOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getAccountEntityXref" ) );

   BFObjectKey objKey( I_( "AccountEntityXref" ), idDataGroup, OBJ_ACTIVITY_NONE, OBJ_TYPE_ACCOUNTENTITY );
   AccountEntityXref *pAccountEntityXref = dynamic_cast<AccountEntityXref*>( findObject( objKey ) );

   if( !pAccountEntityXref )
   {

      pAccountEntityXrefOut = new AccountEntityXref( *this );
      if( pAccountEntityXrefOut->init() > WARNING )
      {
         delete pAccountEntityXrefOut;
         pAccountEntityXrefOut = NULL;
      }
      else
      {
         BFObjectKey objKey1( I_( "AccountEntityXref" ), BF::HOST, OBJ_ACTIVITY_NONE, OBJ_TYPE_ACCOUNTENTITY );
         setObject( objKey1, pAccountEntityXrefOut );
      }
   }
   else
   {
      pAccountEntityXrefOut = pAccountEntityXref;
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************************************
SEVERITY 
DSTCWorkSession::getNewEntity (const BFDataGroupId& idDataGroup, 
   Entity *&pEntityOut)
{
   //delegate this to WorkSessionEntityList
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getNewEntity"));

   WorkSessionEntityList *pWorkSessionEntityList = NULL;

   if (getWorkSessionEntityList (pWorkSessionEntityList) <= WARNING &&
      pWorkSessionEntityList)
   {
      pWorkSessionEntityList->getNewEntity (idDataGroup, pEntityOut);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//********************************************************************************************************
SEVERITY 
DSTCWorkSession::getEntity (const BFDataGroupId& idDataGroup, 
   const DString& strEntityNum, 
   Entity *&pEntityOut)
{
   //delegate this to WorkSessionEntityList
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getEntity"));
   WorkSessionEntityList *pWorkSessionEntityList = NULL;

   if (getWorkSessionEntityList (pWorkSessionEntityList) <= WARNING &&
      pWorkSessionEntityList)
   {
      pWorkSessionEntityList->getEntity (idDataGroup, strEntityNum, pEntityOut);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY 
DSTCWorkSession::PopulateEntity (const BFDataGroupId& idDataGroup, 
   const BFData &entityData, 
   Entity *&pEntityOut)
{
   //delegate this to WorkSessionEntityList
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("PopulateEntity"));
   WorkSessionEntityList *pWorkSessionEntityList = NULL;

   if (getWorkSessionEntityList (pWorkSessionEntityList) <= WARNING &&
      pWorkSessionEntityList)
   {
      pWorkSessionEntityList->PopulateEntity (idDataGroup, entityData, pEntityOut);
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//***********************************************************************************************
SEVERITY 
DSTCWorkSession::getNewShareholder( const BFDataGroupId& idDataGroup, Shareholder *&pShrhldrOut, DString & dstrNewShrNum )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getNewShareholder" ) );

   DString newShareholdeNum;

   pShrhldrOut = new Shareholder( *this );
   //set the object as being new
   pShrhldrOut->setObjectNew();

   if( dstrNewShrNum == NULL_STRING )
      getNewKey( newShareholdeNum );
   else
      newShareholdeNum = dstrNewShrNum;


   if( pShrhldrOut->init( idDataGroup, newShareholdeNum ) <= WARNING )
   {
      BFObjectKey objKey( newShareholdeNum, idDataGroup, OBJ_ACTIVITY_ADDED, OBJ_TYPE_SHAREHOLDER );
      setObject( objKey, pShrhldrOut );
      //dstrNewShrNum = newShareholdeNum;
   }
   else
   {
      delete pShrhldrOut;
      pShrhldrOut = NULL;
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY 
DSTCWorkSession::getShareholder( const BFDataGroupId& idDataGroup, const DString& shrNum, Shareholder *&pShrhldrOut,
                                 bool bValidateShrNum /*= false*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getShareholder" ) );

   DString dstrShrNum = shrNum;
   dstrShrNum.strip().stripLeading( I_CHAR( '0' ) );

   BFObjectKey objKey( dstrShrNum, idDataGroup, OBJ_ACTIVITY_NONE, OBJ_TYPE_SHAREHOLDER );
   Shareholder* pShareholder = dynamic_cast< Shareholder * >( findObject( objKey ) );

   if( !pShareholder )
   {
      if (bValidateShrNum)
      {
         if (Shareholder::validateShrNum(*this, dstrShrNum, idDataGroup) > WARNING )
         {
            return(GETCURRENTHIGHESTSEVERITY());
         }
      }
   //start with an empty shareholder
      pShrhldrOut = new Shareholder( *this );
      BFObjectKey objKey1( dstrShrNum, BF::HOST, OBJ_ACTIVITY_NONE, OBJ_TYPE_SHAREHOLDER );  
      setObject( objKey1, pShrhldrOut );
      pShrhldrOut->setField(ifds::ShrNum, dstrShrNum, BF::HOST, false, false, false);
      pShrhldrOut->clearUpdatedFlags(BF::HOST);
   }
   else //get the shareholder from the repository
   {
      pShrhldrOut = pShareholder;
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY 
DSTCWorkSession::getAdvisorList( const BFDataGroupId& idDataGroup, 
                                 AdvisorList *&pAdvisorListOut, 
                                 const DString& strBrokerCode,
                                 const DString& strBranchCode,
                                 const DString& strSlsRep,
                                 DString AllResult,
                                 const DString& dstrTrack /*= I_("N")*/,
                                 const DString& dstrPageName /*= NULL_STRING*/,
                                 bool bCreate /*= true*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getAdvisorList" ) );
   BFObjectKey objKey( I_("AdvisorList"), BF::HOST, OBJ_ACTIVITY_NONE, OBJ_TYPE_AGENT );
   AdvisorList * pAdvisorList = dynamic_cast<AdvisorList*>( findObject( objKey ) );
   if( !pAdvisorList && bCreate )
   {
      pAdvisorListOut = new AdvisorList( *this );
      //do a database inquiry
      if( pAdvisorListOut->init( strBrokerCode, strBranchCode, strSlsRep, AllResult, dstrTrack, dstrPageName ) > WARNING )
      {
         delete pAdvisorListOut;
         pAdvisorListOut = NULL;
      }
      else
      {
         setObject( objKey, pAdvisorListOut );
      }
   }
   else //get the account from the repository
   {
      pAdvisorListOut = pAdvisorList;
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void 
DSTCWorkSession::getNewKey( DString& newKey )
{
   BFGuard g( g_newKeyLock );
   //the reason we padded left to only 4(zeros) is that for MORGAN(Japan),
   //the account number can have only 7 digits.
   newKey = NEW_PRFX + DString::asString( ++_lKey ).padLeft( 4, '0' );
}

//******************************************************************************
void DSTCWorkSession::setCommitParams (BFData &commitParams)
{
   m_commitParams = &commitParams;
}

//******************************************************************************
SEVERITY DSTCWorkSession::buildTransactions ()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS );

#define BUILD_TRANSACTIONS(OBJ_TYPE, BUILDER) \
   if (objType == OBJ_TYPE) \
   { \
      severity = ##BUILDER:: \
                  buildTransactions (*this, \
                                     pObject, \
                                     &getHostTransactionContainer(), \
                                     lObjActivity); \
   } \
   else
   
   BFObjIter bfIter (*this, BF::HOST);
   SEVERITY severity = SEVERE_ERROR;

   while (!bfIter.end())
   {
      BFAbstractCBO* pObject = bfIter.getObject();
      BF_OBJ_ACTIVITY lObjActivity = bfIter.getKey().getActivity();

      if ( lObjActivity == OBJ_ACTIVITY_ADDED || 
           lObjActivity == OBJ_ACTIVITY_DELETED || 
           pObject->hasTransactionUpdates(true)) 
      {
         const BF_OBJ_TYPE& objType = bfIter.getKey().getType();

         BUILD_TRANSACTIONS (OBJ_TYPE_MFACCOUNT, DSTCMFAccountTrxnBuilder)
         BUILD_TRANSACTIONS (OBJ_TYPE_SHAREHOLDER, DSTCMFShareholderTrxnBuilder)
         BUILD_TRANSACTIONS (OBJ_TYPE_ENTITY, DSTCEntityTrxnBuilder)
         BUILD_TRANSACTIONS (OBJ_TYPE_ACCOUNTENTITY, DSTCAccountEntityTrxnBuilder)
         BUILD_TRANSACTIONS (OBJ_TYPE_TRADES_LIST, DSTCTradesTrxnBuilder)
         BUILD_TRANSACTIONS (OBJ_TYPE_MANUAL_DIVIDEND_LIST, DSTCManualDividendTrxnBuilder)
         BUILD_TRANSACTIONS (OBJ_TYPE_DISTRIBUTOR_REPOSITORY, DSTCDistributorRepositoryTrxnBuilder)
         BUILD_TRANSACTIONS (OBJ_TYPE_FUND_BANK_INSTRUCTIONS_LIST_REPOSITORY , DSTCBankInstructionsTrxnBuilder)
         BUILD_TRANSACTIONS (OBJ_TYPE_CLIENT_BANK_INSTRUCTIONS_LIST, DSTCBankInstructionsTrxnBuilder)
         BUILD_TRANSACTIONS (OBJ_TYPE_AGENT, DSTCAdvisorTrxnBuilder)
         BUILD_TRANSACTIONS (OBJ_TYPE_SETTLEMENT_SEARCH, DSTCSettlementTrxnBuilder)
         BUILD_TRANSACTIONS (OBJ_TYPE_BROKER_AMS_SEARCH, DSTCBrokerAMSTrxnBuilder)
         BUILD_TRANSACTIONS (OBJ_TYPE_AMS_GLOBAL, DSTCAMSTrxnBuilder)
         BUILD_TRANSACTIONS (OBJ_TYPE_REPORT, DSTCReportTrxnBuilder)
         BUILD_TRANSACTIONS (OBJ_TYPE_PROTECTED_FUND_LIST, DSTCProtectedFundTrxnBuilder)
         BUILD_TRANSACTIONS (OBJ_TYPE_FEEPARAM_SYSTEM, DSTCFeeParamSysTxnBuilder)
         BUILD_TRANSACTIONS (OBJ_TYPE_MKT_INDEX_MASTER, DSTCMktIndexMasterTrxnBuilder)
         BUILD_TRANSACTIONS (OBJ_TYPE_MKT_INDEX_VALUES, DSTCMktIndexValuesTrxnBuilder)
         BUILD_TRANSACTIONS (OBJ_TYPE_RESET_INSTR, DSTCResetInstrTrxnBuilder)
         BUILD_TRANSACTIONS (OBJ_TYPE_FINANCIAL_INSTITUTION_REPOSITORY, DSTCFinancialInstitutionTrxnBuilder)
         BUILD_TRANSACTIONS (OBJ_TYPE_SETTLEMENT_LOCATION_SYSLVL_LIST, DSTCSysLvlSettlementInstrTrxnBuilder)
         BUILD_TRANSACTIONS (OBJ_TYPE_DAILY_TRANSACTIONS_FEES_REPOSITORY, DSTCDailyTransactionsFeesTrxnBuilder)
         BUILD_TRANSACTIONS (OBJ_TYPE_FEE_MODEL_LIST, DSTCFeeModelTxnBuilder)
         BUILD_TRANSACTIONS (OBJ_TYPE_FUND_SPONSOR_FEE_MODEL_LIST, DSTCFundSponsorFeeModelTxnBuilder)
         BUILD_TRANSACTIONS (OBJ_TYPE_REMARK_CONTAINER, DSTCBrokerRemarkTrxnBuilder)
         BUILD_TRANSACTIONS (OBJ_TYPE_FUND_BROKER_LIST, DSTCFundBrokerTrxnBuilder)
         BUILD_TRANSACTIONS (OBJ_TYPE_AGGREGATED_ORDER_LIST, DSTCAggregateOrderTrxnBuilder)
         BUILD_TRANSACTIONS (OBJ_TYPE_TRANS_CANCEL, DSTCTransCancelTrxnBuilder)
         BUILD_TRANSACTIONS (OBJ_TYPE_CONFIRM_REPRINT, DSTCConfirmReprintTrxnBuilder)
         BUILD_TRANSACTIONS (OBJ_TYPE_BULK_CANCEL, DSTCBulkCancelTrxnBuilder)
         BUILD_TRANSACTIONS (OBJ_TYPE_SAVINGS_DIRECTIVE, DSTCSavingsDirectiveTrxnBuilder)
         BUILD_TRANSACTIONS (OBJ_TYPE_TRANS_HIST_DILUTION_ALLOC_LIST, DSTCTransHistDilutionAllocListTrxnBuilder)
         BUILD_TRANSACTIONS (OBJ_TYPE_CLONE_ACCOUNT, DSTCCloneAccountTrxnBuilder)
		 BUILD_TRANSACTIONS (OBJ_TYPE_CHEQUE_LIST, DSTCChequeTxnBuilder)
		 BUILD_TRANSACTIONS (OBJ_TYPE_AGENT_BANK_INSTRUCTIONS_LIST_REPOSITORY, DSTCBankInstructionsTrxnBuilder)
		 BUILD_TRANSACTIONS (OBJ_TYPE_HOLDING_COMP, DSTCHoldingCompTrxnBuilder) 
         BUILD_TRANSACTIONS (OBJ_TYPE_TRADEVERIFICATION_LIST, DSTCTradeVerificationTrxnBuilder)
		 BUILD_TRANSACTIONS (OBJ_TYPE_ACCT_ROUNDING_RULE_LIST, DSTCAcctRoundingRuleTrxnBuilder)
		 BUILD_TRANSACTIONS (OBJ_TYPE_BROKERCUTOFF_LIST, AcctCutOffTimesTrxnBuilder)
         {
            assert( 0 );
         }
         //add the condition to the vector of conditions 
         //these should be displayed by the GUI
         if (severity > WARNING)
         {
            pushCommitConditions (MYFRAME());
         }
      }
      ++bfIter;
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY DSTCWorkSession::commit ()
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, COMMIT);

   SEVERITY severity = SEVERE_ERROR;

   DSTCPersistentRequestor *persistentRequestor = NULL;

   const DSTCSecurity *pSecurity = dynamic_cast<const DSTCSecurity *>( getSecurity(DSTCHost::getPrimaryHost()) );

   //this map will hold on to the group commit info structures which are used to
   //keep track of the persitence groups that failed; the purpose of storing this information
   //is to have a way to decide if non-persistent transactions related to persistent groups
   //should be sent to the host
   //usually if the creation of new account, new shareholder or new entity fails, non-persistent
   //transactions related to the the above shouldn't be sent
   typedef std::map< long, struct PersitentGroupCommitInfo* > TRXN_PERISTENT_GROUPS_MAP;
   TRXN_PERISTENT_GROUPS_MAP trxnPersistentMap;

   if (_hostSubstitutionList)
   {
      delete _hostSubstitutionList;
      _hostSubstitutionList = NULL;
   }

   _hostSubstitutionList = new HostSubstitutionValuesList( *this );
   _hostSubstitutionList->init ();

   orderTrxn ();

   //build an iterator for the transaction container
   HostTransactionContainerIterator htcIter (&getHostTransactionContainer());
   //set the current group to 0
   long crtTrxnGrp = 0;
   //set the persistence flag to false
   bool startPersistence = false; 

   htcIter.begin();//start the iteration
   while( !htcIter.end() )
   {
      long iterTrxnGrp = htcIter.trxnGroup();
      TRXN_TYPE iterTrxnType = htcIter.trxnType();
      DString iterKeyTypes = htcIter.keyTypes();

      //check first if the current pair response/request has been commited
      if (!htcIter.isCommited())
      {
         //if the trxn group has changed
         //and a persistence trxns sequence has been started, then we must stop it
         if (crtTrxnGrp != iterTrxnGrp && startPersistence && NULL != persistentRequestor)
         {
            //make sure we close the old persistence trxn group
            BFData *persistStopResponse = new BFData (ifds::DSTC0074_VW);

            persistentRequestor->setCommitParams (*m_commitParams);
            severity = persistentRequestor->commit (*persistStopResponse);
            if (severity > WARNING) //if an error when closing the persistence
            {
               delete persistStopResponse;
               persistStopResponse = NULL;

               //add conditions to the conditions vector
               pushCommitConditions (MYFRAME());

               //if any troubles closing the persistence trxn, set the trxns belonging to
               //this persistent trxn group as not beeing commited
               //define a new iterator for the container
               HostTransactionContainerIterator tempHtcIter (&getHostTransactionContainer());
               //set filters
               tempHtcIter.walkTrxnGroup (crtTrxnGrp);
               //walk the container
               for (tempHtcIter.begin(); !tempHtcIter.end(); ++tempHtcIter)
               {
                  tempHtcIter.setCommited (false);
               }
               //there is an error after stopping the group of persistent transaction
               //look for the current trxn group in the map of persistent trxns,
               //here there is no need to create a new entry in the map, since we've already
               //walked all the trxns part of the group
               TRXN_PERISTENT_GROUPS_MAP::iterator trxnPersIter = trxnPersistentMap.find (crtTrxnGrp);

               if (trxnPersIter != trxnPersistentMap.end())
               {
                  //this group failed to go further
                  (*trxnPersIter).second->_failed = true;
               }
            }
            //either error or OK, 
            //signal that this persistence group has ended
            if (persistStopResponse)
            {
               _hostSubstitutionList->addSubstitutionData (persistStopResponse);		

			      checkPersistentViewWarnings (persistStopResponse);
			   
               delete persistentRequestor;
               persistentRequestor = NULL;
            }
            startPersistence = false;
         }
         if (iterTrxnType == NOT_PERSISTENT || iterTrxnType == CLONE_ACCOUNT)
         {
           // in case there is persistant transaction close it.
           if (startPersistence && NULL != persistentRequestor)
           {
               BFData *persistStopResponse = new BFData (ifds::DSTC0074_VW);
                
               persistentRequestor->setCommitParams (*m_commitParams);
               severity = persistentRequestor->commit (*persistStopResponse);
               if (severity > WARNING) //if an error when closing the persistence
               {
                  delete persistStopResponse;
                  persistStopResponse = NULL;

                //add conditions to the conditions vector
                pushCommitConditions (MYFRAME());

                //if any troubles closing the persistence trxn, set the trxns belonging to
                //this persistent trxn group as not beeing commited
                //define a new iterator for the container
                HostTransactionContainerIterator tempHtcIter (&getHostTransactionContainer());
                //set filters
                tempHtcIter.walkTrxnGroup (crtTrxnGrp);
                //walk the container
                for( tempHtcIter.begin(); !tempHtcIter.end(); ++tempHtcIter )
                {
                    tempHtcIter.setCommited (false);
                }
                //there is an error after stopping the group of persistent transaction
                //look for the current trxn group in the map of persistent trxns,
                //here there is no need to create a new entry in the map, since we've already
                //walked all the trxns part of the group
                TRXN_PERISTENT_GROUPS_MAP::iterator trxnPersIter = trxnPersistentMap.find( crtTrxnGrp );

                if (trxnPersIter != trxnPersistentMap.end())
                {
                    //this group failed to go further
                    (*trxnPersIter).second->_failed = true;
                }
                }
                //either error or OK, 
                //signal that this persistence group has ended
                if (persistStopResponse)
                {
					   _hostSubstitutionList->addSubstitutionData (persistStopResponse);	

					   checkPersistentViewWarnings (persistStopResponse);
	    			   
					   delete persistentRequestor;
					   persistentRequestor = NULL;
                }
                startPersistence = false;
  
           }
		   //set the current trxn group if is not a persistent trxn
            crtTrxnGrp = iterTrxnGrp;
            //see if the current group has any interests in previous persistent groups
            //that might have failed
            bool bHasInterest = false;

            for( TRXN_PERISTENT_GROUPS_MAP::iterator trxnPersIter = trxnPersistentMap.begin();
                 trxnPersIter != trxnPersistentMap.end(); 
                 ++trxnPersIter )
            {
               //get the keytypes of the current non-persistent group;
               DString dump = htcIter.keyTypes();
               DString keyType;
               DString tempValue;

               I_CHAR *temp = const_cast < I_CHAR* > ( dump.c_str() );

               do
               {
                  temp = parseIdiString( temp, keyType, tempValue );

                  //check if the current keyType, tempValue combination
                  //exists in the persistent group transactions already being processed
                  DString crtKeyTypeTempValue;

                  addIDITagValue (crtKeyTypeTempValue, keyType, tempValue);
                  if( (*trxnPersIter).second->_keyType.find( crtKeyTypeTempValue ) != DString::npos &&
                      (*trxnPersIter).second->_failed )
                  { //means that this non-persisten transaction is linked to a persistent group and
                    //we need to fail it
                     bHasInterest = true;
                     break;
                  }
               } while( temp && temp != NULL_STRING && *temp );
               if (bHasInterest)
               {
                  break;
               }
            }
            if (bHasInterest) //we should continue with a new transaction
            {
               //move to the next element in the container, continue the loop,
               //this will skip this non-persisistent transaction
               ++htcIter;
               continue;
            }
         }
//this is a persistent trxn but not yet started
         if (crtTrxnGrp != iterTrxnGrp && !startPersistence)
         {
            try
            {
               DString mgmtCoId, 
                  ppType;
               getMgmtCo().getField (ifds::CompanyId, mgmtCoId, BF::HOST);

               if (iterTrxnType == UPDATE_SETTLEMENT)
               {
                  ppType = I_( "SETL" );
               }
               else
               {
                  ppType = I_( "NASU" );
               }
               persistentRequestor = new DSTCPersistentRequestor (pSecurity, mgmtCoId, ppType);
            }
            catch (ConditionException &ce)
            {
               SETCONDITIONFROMEXCEPTION (ce);

               //add conditions to the conditions vector
               pushCommitConditions (MYFRAME());

               //if any troubles when starting the persistent trxn
               //abort sending this group of persistent trxns over
               //skip the group iterTrxnGrp in the HTC
               //no need to reset this filter, because the container
               //is ordered and another group with the same id 
               //will not appear
               htcIter.skipTrxnGroup( iterTrxnGrp );
               //move to the next element in the container, continue the loop
               ++htcIter;

               //create an entry in the persistence map with the this group of persistence
               //that failed when starting
               HostTransactionContainerIterator tempHtcIter( &getHostTransactionContainer() );
               struct PersitentGroupCommitInfo *persitentGroupCommitInfo = NULL;

               persitentGroupCommitInfo = new PersitentGroupCommitInfo;
               //this group failed to even start
               persitentGroupCommitInfo->_failed = true;
               trxnPersistentMap.insert( std::make_pair( iterTrxnGrp, persitentGroupCommitInfo ) );
               tempHtcIter.walkTrxnGroup( iterTrxnGrp );
               for( tempHtcIter.begin(); !tempHtcIter.end(); ++tempHtcIter )
               {
                  TRXN_TYPE tempIterTrxnType = tempHtcIter.trxnType();
                  DString tempIterKeyType = tempHtcIter.keyTypes();

                  if (tempIterTrxnType == NEW_SHAREHOLDER)
                  {
                     DString shrNum;

                     getValueForTag( tempIterKeyType, KEYTYPES::SHRNUM, shrNum );
                     addIDITagValue( persitentGroupCommitInfo->_keyType, KEYTYPES::SHRNUM, shrNum );
                  }
                  else if (tempIterTrxnType == NEW_ACCOUNT)
                  {
                     DString accountNum;

                     getValueForTag( tempIterKeyType, KEYTYPES::ACCOUNTNUM, accountNum );
                     addIDITagValue( persitentGroupCommitInfo->_keyType, KEYTYPES::ACCOUNTNUM, accountNum );
                  }
                  else if (tempIterTrxnType == NEW_ENTITY)
                  {
                     DString entityId;

                     getValueForTag( tempIterKeyType, KEYTYPES::ENTITYID, entityId );
                     addIDITagValue( persitentGroupCommitInfo->_keyType, KEYTYPES::ENTITYID, entityId );
                  }
                  else if (tempIterTrxnType == UPDATE_SETTLEMENT)
                  {
                     addIDITagValue( persitentGroupCommitInfo->_keyType, TRXNTAG::SETTLEMENTTAG, TRXNTAG::SETTLEMENTTAG );
                  }
               }
               //no need to set the startPersistence flag to false,
               continue;
            }
            startPersistence = true;
            crtTrxnGrp = iterTrxnGrp;
         }

         //update the temporary id's with id's comming from the host
         DString dump = htcIter.keyTypes();
         DString keyType;
         DString tempValue;

         I_CHAR *temp = const_cast < I_CHAR* > ( dump.c_str() );
         do
         {
            temp = parseIdiString( temp, keyType, tempValue );
            checkSubstitutionsValues (keyType, tempValue, *htcIter.getRequest());
         } while (temp && temp != NULL_STRING && *temp);

         //if we have this type of transactions we need to create an entry in the
         //TRXN_PERISTENT_GROUPS_MAP, to be prepared to store that this transaction 
         //failed
         if( iterTrxnType == NEW_SHAREHOLDER || 
             iterTrxnType == NEW_ACCOUNT ||
             iterTrxnType == NEW_ENTITY || 
             iterTrxnType == UPDATE_SETTLEMENT)
         {
            TRXN_PERISTENT_GROUPS_MAP::iterator trxnPersIter = trxnPersistentMap.find( crtTrxnGrp );

            struct PersitentGroupCommitInfo *persitentGroupCommitInfo = NULL;
            if (trxnPersIter == trxnPersistentMap.end())
            {
               persitentGroupCommitInfo = new PersitentGroupCommitInfo;
               trxnPersistentMap.insert( std::make_pair( crtTrxnGrp, persitentGroupCommitInfo ) );
            }
            else
            {
               persitentGroupCommitInfo = (*trxnPersIter).second;
            }
            if (iterTrxnType == NEW_SHAREHOLDER)
            {
               DString shrNum;

               getValueForTag (iterKeyTypes, KEYTYPES::SHRNUM, shrNum);
               addIDITagValue (persitentGroupCommitInfo->_keyType, KEYTYPES::SHRNUM, shrNum);
            }
            else if (iterTrxnType == NEW_ACCOUNT)
            {
               DString accountNum;

               getValueForTag (iterKeyTypes, KEYTYPES::ACCOUNTNUM, accountNum);
               addIDITagValue (persitentGroupCommitInfo->_keyType, KEYTYPES::ACCOUNTNUM, accountNum);
            }
            else if (iterTrxnType == NEW_ENTITY)
            {
               DString entityId;

               getValueForTag (iterKeyTypes, KEYTYPES::ENTITYID, entityId);
               addIDITagValue (persitentGroupCommitInfo->_keyType, KEYTYPES::ENTITYID, entityId);
            }
            else if (iterTrxnType == UPDATE_SETTLEMENT)
            {
               addIDITagValue (persitentGroupCommitInfo->_keyType, TRXNTAG::SETTLEMENTTAG, TRXNTAG::SETTLEMENTTAG);
            } 
         }
//for all transactions check if we commit params
         saveCommitParams (*htcIter.getRequest(), ifds::UpdAllNonFin);
         saveCommitParams (*htcIter.getRequest(), ifds::AWDObjectId);
         saveCommitParams (*htcIter.getRequest(), ifds::WorkType);
         saveCommitParams (*htcIter.getRequest(), ifds::BusinessArea);
         saveCommitParams (*htcIter.getRequest(), ifds::AWDCrda);
         if (startPersistence && NULL != persistentRequestor)
         {            
            
            severity = BFDataBroker::getInstance()->receive( htcIter.request(),
                                                             *htcIter.getRequest(), 
                                                             *htcIter.getResponse(), 
                                                             *persistentRequestor);
         }
         else
         {
            DSTCRequestor requestor (pSecurity);
            try 
            {
               const DSTCRequest& request = dynamic_cast< const DSTCRequest& >(htcIter.request());
               requestor.setRecycleOnReceive (request.isQueryRequest());
            } 
            catch( ... ) 
            {
            }

            severity = BFDataBroker::getInstance()->receive( htcIter.request(),
                                                             *htcIter.getRequest(), 
                                                             *htcIter.getResponse(), 
                                                             requestor /*DSTCRequestor(pSecurity)*/ );
         }		 
            if (severity <= WARNING)
            {
               //set the current pair response/request data as commited
               //we are going to set the commit flag to true here, although it
               //might seem too early; we assume that errors will happen
               //less frequently so, only in case of an error we are going
               //to walk the HTC and reset the commit flag to false for the
               //current trxn group
               htcIter.setCommited (true);

			   if (htcIter.getResponse()->exists (ifds::UpdateStatus)) 
			   {
				   DString dstrUpdateStatus; 
				   dstrUpdateStatus = htcIter.getResponse()->getElementValue (ifds::UpdateStatus);
   								   
				   if (Y == dstrUpdateStatus)
				   {
					   if (iterTrxnType == CLONE_ACCOUNT)
                  {
                     BFData *clonedShareholder = new BFData (ifds::DSTC0074_VWRepeat_Record),
                        *clonedAccount = new BFData (ifds::DSTC0074_VWRepeat_Record);
                     BFData *cloneResponse = new BFData (ifds::DSTC0074_VW);

                     DString shrNumToBeCloned,
                        acctNumToBeCloned;

                     getValueForTag (iterKeyTypes, KEYTYPES::SHRNUM, shrNumToBeCloned);
                     clonedShareholder->setElementValue (ifds::KeyType, I_("ShrNum"));
                     clonedShareholder->setElementValue (ifds::TempValue, shrNumToBeCloned);
                     clonedShareholder->setElementValue (ifds::PermValue, htcIter.getResponse()->getElementValue (ifds::ShrNum));
                     cloneResponse->addRepeat (*clonedShareholder);
                     getValueForTag (iterKeyTypes, KEYTYPES::ACCOUNTNUM, acctNumToBeCloned);
                     clonedAccount->setElementValue (ifds::KeyType, I_("AccountNum"));
                     clonedAccount->setElementValue (ifds::TempValue, acctNumToBeCloned);
                     clonedAccount->setElementValue (ifds::PermValue, htcIter.getResponse()->getElementValue (ifds::AccountNum));
                     cloneResponse->addRepeat (*clonedAccount);
                     cloneResponse->setElementValue (ifds::RepeatCount, I_("2"));
                     _hostSubstitutionList->addSubstitutionData (cloneResponse);
                  }
                  
                  if ( htcIter.getResponse()->exists( ifds::WarnCode1 ) )
					   {
                        DString dstrWarnCode = htcIter.getResponse()->getElementValue( ifds::WarnCode1 );
                        DString dstrWarnParam;

                        if ( htcIter.getResponse()->exists( ifds::WarnParam1 ) )
                           dstrWarnParam = htcIter.getResponse()->getElementValue( ifds::WarnParam1 );
	      				   dstrWarnParam.strip();
                        addWarningForUpdateView( dstrWarnCode, dstrWarnParam ); 						
					   }
					   if ( htcIter.getResponse()->exists( ifds::WarnCode2 ) )
					   {
                     DString dstrWarnCode = htcIter.getResponse()->getElementValue( ifds::WarnCode2 );
                     DString dstrWarnParam;

                     if ( htcIter.getResponse()->exists( ifds::WarnParam2 ) )
                        dstrWarnParam = htcIter.getResponse()->getElementValue( ifds::WarnParam2 );

                     dstrWarnParam.strip();
                     addWarningForUpdateView( dstrWarnCode, dstrWarnParam ); 	
					   }
					   if ( htcIter.getResponse()->exists( ifds::WarnCode3 ) )
					   {
                     DString dstrWarnCode = htcIter.getResponse()->getElementValue( ifds::WarnCode3 );
                     DString dstrWarnParam;
                     
                     if ( htcIter.getResponse()->exists( ifds::WarnParam3 ) ) 
                        dstrWarnParam = htcIter.getResponse()->getElementValue( ifds::WarnParam3 );

                     dstrWarnParam.strip();
                     addWarningForUpdateView( dstrWarnCode, dstrWarnParam ); 
					   }
					   if ( htcIter.getResponse()->exists( ifds::WarnCode4 ) )
					   {
                     DString dstrWarnCode = htcIter.getResponse()->getElementValue( ifds::WarnCode4 );
						   DString dstrWarnParam;
                     
                     if ( htcIter.getResponse()->exists( ifds::WarnParam4 ) ) 
							   dstrWarnParam = htcIter.getResponse()->getElementValue( ifds::WarnParam4 );

						   dstrWarnParam.strip();
                     addWarningForUpdateView( dstrWarnCode, dstrWarnParam ); 	
					   }
					   if ( htcIter.getResponse()->exists( ifds::WarnCode5 ) )
					   {
                     DString dstrWarnCode = htcIter.getResponse()->getElementValue( ifds::WarnCode5 );
                     DString dstrWarnParam;
      
                     if ( htcIter.getResponse()->exists( ifds::WarnParam5 ) )
                        dstrWarnParam = htcIter.getResponse()->getElementValue( ifds::WarnParam5 );

                     dstrWarnParam.strip();
                     addWarningForUpdateView( dstrWarnCode, dstrWarnParam ); 	
					   }
					   pushCommitConditions( MYFRAME() );      					
				   }
			   }
         }
         else
         {
            //add conditions to the conditions vector
            pushCommitConditions( MYFRAME() );

            //and then deal with the persistence issues
            if (startPersistence)
            {
               //skip the whole group if one trxn from the group fails
               htcIter.skipTrxnGroup( crtTrxnGrp );
               //and close the group by reseting the startPersistence flag
               startPersistence = false;
               //stop the persistence at all levels
               //and do not commit anything

               if( persistentRequestor->rollback() > WARNING )
               {
                  //add conditions to the conditions vector
                  pushCommitConditions( MYFRAME() );
               }

               //look for the current group of persistence in the map
               bool newGroup = false;//whether is a new group in the map
               TRXN_PERISTENT_GROUPS_MAP::iterator trxnPersIter = trxnPersistentMap.find( crtTrxnGrp );

               struct PersitentGroupCommitInfo *persitentGroupCommitInfo = NULL;
               if (trxnPersIter == trxnPersistentMap.end())
               {
                  //insert one if it doesn't exist
                  persitentGroupCommitInfo = new PersitentGroupCommitInfo;
                  trxnPersistentMap.insert( std::make_pair( crtTrxnGrp, persitentGroupCommitInfo ) );
                  newGroup = true;
               }
               else
               {
                  persitentGroupCommitInfo = (*trxnPersIter).second;
               }
               //this group failed to go further
               persitentGroupCommitInfo->_failed = true;

               //for the current group reset the commited flag to false
               //and also build the key type needed to be put, in the 
               //persistence map, so further non-persistence groups with
               //interests in the persist-group that just failed will not
               //be sent
               HostTransactionContainerIterator tempHtcIter( &getHostTransactionContainer() );

               tempHtcIter.walkTrxnGroup( crtTrxnGrp );
               for( tempHtcIter.begin(); !tempHtcIter.end(); ++tempHtcIter )
               {
                  TRXN_TYPE tempIterTrxnType = tempHtcIter.trxnType();
                  DString tempIterKeyType = tempHtcIter.keyTypes();

                  tempHtcIter.setCommited( false );
                  if( newGroup )
                  {
                     if( tempIterTrxnType == NEW_SHAREHOLDER )
                     {
                        DString shrNum;

                        getValueForTag( tempIterKeyType, KEYTYPES::SHRNUM, shrNum );
                        addIDITagValue( persitentGroupCommitInfo->_keyType, KEYTYPES::SHRNUM, shrNum );
                     }
                     else if (tempIterTrxnType == NEW_ACCOUNT)
                     {
                        DString accountNum;

                        getValueForTag( tempIterKeyType, KEYTYPES::ACCOUNTNUM, accountNum );
                        addIDITagValue( persitentGroupCommitInfo->_keyType, KEYTYPES::ACCOUNTNUM, accountNum );
                     }
                     else if (tempIterTrxnType == NEW_ENTITY)
                     {
                        DString entityId;

                        getValueForTag( tempIterKeyType, KEYTYPES::ENTITYID, entityId );
                        addIDITagValue( persitentGroupCommitInfo->_keyType, KEYTYPES::ENTITYID, entityId );
                     }
                     else if( tempIterTrxnType == UPDATE_SETTLEMENT )
                     {
                        addIDITagValue( persitentGroupCommitInfo->_keyType, TRXNTAG::SETTLEMENTTAG, TRXNTAG::SETTLEMENTTAG );
                     }
                  }
               }
               //move to the next element in the container, continue the loop
            }//start persistence
         }
      }
      //move to the next element in HTC
      ++htcIter;
   }      

   if (startPersistence  && NULL != persistentRequestor) //make sure we close the persistence trxn if we had one open
   {
      BFData *persistStopResponse = new BFData (ifds::DSTC0074_VW);

      persistentRequestor->setCommitParams (*m_commitParams);
      if (persistentRequestor->commit (*persistStopResponse) > WARNING)
      {
         delete persistStopResponse;
         //add conditions to the conditions vector
         pushCommitConditions (MYFRAME());

         //and,
         //for the current group reset the commited flag to false
         HostTransactionContainerIterator tempHtcIter( &getHostTransactionContainer() );

         tempHtcIter.walkTrxnGroup( crtTrxnGrp );
         for( tempHtcIter.begin(); !tempHtcIter.end(); ++tempHtcIter )
         {
            tempHtcIter.setCommited( false );
         }
      }
      else
	   {
         _hostSubstitutionList->addSubstitutionData (persistStopResponse);		 		  
		   checkPersistentViewWarnings( persistStopResponse );		
	   }	  	  
      delete persistentRequestor;
      persistentRequestor = NULL;
      startPersistence = false;
   }   

   //clean the map of persistent transactions
   for( TRXN_PERISTENT_GROUPS_MAP::iterator trxnPersIter = trxnPersistentMap.begin();
        trxnPersIter != trxnPersistentMap.end(); )
   {
      delete (*trxnPersIter).second;
      trxnPersIter = trxnPersistentMap.erase( trxnPersIter );
   }
   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY 
DSTCWorkSession::refreshData ()
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, REFRESHDATA);

   BFObjIter wsIter (*this, BF::HOST);
   BFCBO *pAccEntXRef = NULL;

   //walk the repository
   wsIter.begin (OBJ_TYPE_NONE, OBJ_ACTIVITY_NONE) ;

   while (!wsIter.end())
   {
      BFCBO *pObj = dynamic_cast< BFCBO* >(wsIter.getObject());
      const BFObjectKey &pKey = wsIter.getKey();

      //if it is the cross reference object save it for now,
      //and continue the loop
      if (pKey.getType() == OBJ_TYPE_ACCOUNTENTITY)
      {
         pAccEntXRef = pObj;
         ++wsIter;
         continue;
      }
//if it is Setttlement
      if (pKey.getType() == OBJ_TYPE_SETTLEMENT_SEARCH)
      {
          wsIter.removeObjectFromMap (true);
          continue;
      }
//if it is shareholder cleanup the repository and exit the method 
      if ( pKey.getType() == OBJ_TYPE_SHAREHOLDER && 
           pKey.getActivity() == OBJ_ACTIVITY_ADDED)
      {
         cleanupWorkSession ();
         return GETCURRENTHIGHESTSEVERITY();
      }
      //if it is WorksessionTradesList, delete it
      if (pKey.getType() == OBJ_TYPE_TRADES_LIST)
      {
         wsIter.removeObjectFromMap (true);
         continue;
      }
      //if it is ProtectedFundList, delete it
      if (pKey.getType() == OBJ_TYPE_PROTECTED_FUND_LIST)
      {
         wsIter.removeObjectFromMap (true);
         continue;
      }
      //if it is trans cancellation list, delete it, on refresh
      if (pKey.getType() == OBJ_TYPE_TRANS_CANCEL)
      {
         wsIter.removeObjectFromMap (true);
         continue;
      }

	  //if it is bulk cancellation list, delete it, on refresh
      if (pKey.getType() == OBJ_TYPE_BULK_CANCEL)
      {
         wsIter.removeObjectFromMap (true);
         continue;
      }

      //if it is an object that has been added remove it from map,
      //only entities and accounts can fall in this category,
      //and continue the loop;
      //the remove will move the iterator
      if (pKey.getActivity() == OBJ_ACTIVITY_ADDED)
      {
         wsIter.removeObjectFromMap();
         continue;
      }

      //if it is an object that has been deleted, also remove it from map,
      //only entities can be deleted
      //the remove will move the iterator
      if (pKey.getActivity() == OBJ_ACTIVITY_DELETED)
      {
         wsIter.removeObjectFromMap();
         continue;
      }
      if (pKey.getType() == OBJ_TYPE_SAVINGS_DIRECTIVE)
      {
         wsIter.removeObjectFromMap (true);
         continue;
      }
	   if (pKey.getType() == OBJ_TYPE_TRANS_HIST_DILUTION_ALLOC_LIST )
      {
         wsIter.removeObjectFromMap (true);
         continue;
      }
		if (pKey.getType() == OBJ_TYPE_CHEQUE_LIST )
      {
         wsIter.removeObjectFromMap (true);
         continue;
      }

      if (pKey.getType() == OBJ_TYPE_TRANSACTION_DETAILS )
      {
         wsIter.removeObjectFromMap (true);
         continue;
      }

// Entity
	  if (pKey.getType() == OBJ_TYPE_ENTITY )
      {
		 WorkSessionEntityList * pWorkSessionEntityList = dynamic_cast<WorkSessionEntityList*>( wsIter.getObject() );
		 pWorkSessionEntityList->refreshEntity(BF::HOST);
		 //wsIter.removeObjectFromMap (true);
		 ++wsIter;
         continue;
      }

      //if the object has been updated call refresh on it, or
      //if it is a shareholder/account object it might need to be 
      //refreshed due to  mailinginfo/demographics updates
      bool bIsAccountOrShareholder = 
         pKey.getType() == OBJ_TYPE_SHAREHOLDER ||
         pKey.getType() == OBJ_TYPE_MFACCOUNT;

      if (pObj->isUpdated() || 
         (bIsAccountOrShareholder && 
         pKey.getActivity() == OBJ_ACTIVITY_NONE))
      {
         if (pObj->refresh (false) > WARNING)
         {
            break; //if errors from refresh break
         }
      }
      ++wsIter;
   }
   if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
   {
      //in the end call refresh on the cross reference
      if (pAccEntXRef)
      {
         pAccEntXRef->refresh( false );
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//this method will walk the current trxn container and create an ordered one
//used to send trxn's to the host
//we should all keep our fingers crossed that this will work!!!!!(SP)
//******************************************************************************
void 
DSTCWorkSession::orderTrxn()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, ORDERTRXN );

   //flags for indentifying if a persistent trxn group has been filled
#define NO_TRXNS           0x0000
#define TRXN_SHR           0x0001
#define TRXN_ACCT          0x0002
#define TRXN_ADDRESS       0x0004
#define TRXN_MAILING             0x0008
#define TRXN_ENTITY              0x0010
#define TRXN_ENTITYIDS           0x0020
#define TRXN_ACCTENTITY          0x0040
#define TRXN_MAILINGOVERRIDE     0x0080
#define TRXN_ACCTGUARNTGUARDOPT  0x0100
#define TRXN_ACCTREGDETAILS      0x0200
#define TRXN_ENTITYREGDETAILS    0x0300
#define TRXN_ENTITYREGJURISDETAILS    0x0400
#define TRXN_ENTITYRISK    0x0500

   //iterator to walk the container
   HostTransactionContainerIterator htcIter( &getHostTransactionContainer() );
   //temporary vector that holds the key strings of the trxns that must 
   //be added at the end
   typedef std::vector< DString > TRXN_TEMP_VECTOR;
   TRXN_TEMP_VECTOR v_HTCTemp;
   //a map keyed by ShrNum, AccNum and trxn group id, that holds a pointer 
   //to a trxngroupinfo;
   //a key in this map should look: ShrNum=xxx;AccNum=xxx;TrxnGrpId=xxx;
   typedef std::map< const DString, struct TrxnGroupInfo* > TRXN_GROUP_MAP;
   TRXN_GROUP_MAP trxnGrpMap;
   //used to check if the container iterator should be reset
   bool resetIter = false;
   //set fiters to walk the host transaction container

   //the trxn hasn't been handled yet, no group and sub type set,
   htcIter.walkTrxnGroup( NO_GROUP );
   htcIter.walkTrxnSubType( 0 );
   htcIter.begin(); //start the iteration
   while( !htcIter.end() )
   {
      //the iterator's string key hasn't been saved in the temporary vector
      bool found = false;
      for( TRXN_TEMP_VECTOR::iterator v_iter = v_HTCTemp.begin(); v_iter != v_HTCTemp.end(); ++v_iter )
      {
         if( *v_iter == htcIter.strKey() )
         {
            found = true;
            break;
         }
      }
      if( !found )
      {
         //check first if the current pair response/request has been commited,
         if( !htcIter.isCommited() )
         {
            //we will try to determine the trxn group and trxn subtype of the 
            //transaction; this will be based on the rules set in the string key
            //of the host transaction key
            long trxnGroup = NO_GROUP;
            long trxnSubType = 0;
            TRXN_TYPE trxnType = htcIter.trxnType();
            DString strKey = htcIter.strKey();
            TrxnGroupInfo* groupInfo = NULL;

            //check if the trxn represents a shareholder/account update
            //that needs to be grouped into a persistent transaction
            if( 
              trxnType == NEW_SHAREHOLDER || trxnType == UPDATE_SHAREHOLDER ||
              trxnType == NEW_ACCOUNT || trxnType == UPDATE_ACCOUNT ||
              trxnType == NEW_ENTITY || trxnType == UPDATE_ENTITY || 
              trxnType == NEW_ACCOUNT_ENTITY || trxnType == UPDATE_ACCOUNT_ENTITY ||
              trxnType == NEW_ENTITY_IDS || trxnType == UPDATE_ENTITY_IDS ||
              trxnType == NEW_ADDRESS || trxnType == UPDATE_ADDRESS ||
              trxnType == NEW_MAILING || trxnType == UPDATE_MAILING ||
			  trxnType == NEW_MAILING_OVERRIDE || trxnType == UPDATE_MAILING_OVERRIDE ||
              trxnType == NEW_AS_PENSION || trxnType == UPDATE_AS_PENSION ||
              trxnType == NEW_ESOP || trxnType == UPDATE_ESOP ||
              trxnType == NEW_ACCOUNT_GUARNT_GUARD_OPTN || trxnType == UPDATE_ACCOUNT_GUARNT_GUARD_OPTN ||
			  trxnType == NEW_ACCOUNT_REGULATORY_DETAILS || trxnType == UPDATE_ACCOUNT_REGULATORY_DETAILS ||
			  trxnType == NEW_ENTITY_REGULATORY_DETAILS || trxnType == UPDATE_ENTITY_REGULATORY_DETAILS ||
			  trxnType == NEW_ENTITY_REGULATORY_JURIS_DETAILS || trxnType == UPDATE_ENTITY_REGULATORY_JURIS_DETAILS ||
              trxnType == NEW_ENTITY_RISK || trxnType == UPDATE_ENTITY_RISK
              )
            {
               DString trxnGrpMapKey;
               //this partial key is formed only by the account numer and shareholder number
               DString partialTrxnGrpMapKey;
               //in the next block the key for the trxn grp map will be built
               {
                  //get the value of the shareholder number
                  DString strValue;

                  //build the key for the trxnGroups, so we can find out the trxn group id
                  if( getValueForTag( strKey, TRXNTAG::SHRTAG, strValue ) )
                  {
                     //we do not want an empty shareholder number
                     if( strValue != NULL_STRING )
                     {
                        //build the key for the trxnGrpMap
                        addTag( trxnGrpMapKey, TRXNTAG::SHRTAG, strValue.c_str() );
                        addTag( partialTrxnGrpMapKey, TRXNTAG::SHRTAG, strValue.c_str() );
                     }
                     else
                     {
                        assert( 0 );
                        throw;
                     }
                  }
                  //check if the strKey has the account tag in it
                  if( getValueForTag( strKey, TRXNTAG::ACCTTAG, strValue ) )
                  {
                     //we do not want an empty account number
                     if( strValue != NULL_STRING )
                     {
                        //build the key for the trxnGrpMap
                        addTag( trxnGrpMapKey, TRXNTAG::ACCTTAG, strValue.c_str() );
                        addTag( partialTrxnGrpMapKey, TRXNTAG::ACCTTAG, strValue.c_str() );
                     }
                     else
                     {
                        assert( 0 );
                        throw;
                     }
                  }
                  //add the tag for the current transaction number
                  I_CHAR  i_trxnGroup[ 5 ];

                  //the trxn group will be built like this "0001",...
                  //padded, so we can order the map based on trxn group number
                  //(if we need two trxn groups for the same top level object)
                  i_sprintf( i_trxnGroup, I_( "%04d" ), DSTCWorkSession::_maxTrxnGroup );
                  addTag( trxnGrpMapKey, TRXNTAG::TRXGRPID, i_trxnGroup );
               }

               bool foundTrxnGroup = false;
               DString dump = partialTrxnGrpMapKey;
               int pos = DString::npos;
               //look for the partial key in the map, so we can get the trxn group number
               //and the group info, but split this partial key in components

               while( (pos = dump.find( ';' )) != DString::npos )
               {
                  DString partOfDump = dump.substr( 0, pos );

                  //walk the map and look if a group that will satisfy this
                  //transaction already exists
                  for( TRXN_GROUP_MAP::iterator iter = trxnGrpMap.begin(); iter != trxnGrpMap.end(); iter++ )
                  {
                     DString crtKey = (*iter).first;

                     if( crtKey.find( partOfDump ) != DString::npos )
                     {  //here we have an entry of this persistence group in the map
                        DString strTrxnGroup;

                        //get the group number
                        getValueForTag( crtKey, TRXNTAG::TRXGRPID, strTrxnGroup );
                        trxnGroup = strTrxnGroup.asInteger();
                        //get the information about this group
                        groupInfo = (*iter).second;
                        //if the account number is part of the partial key but not 
                        //yet part of the key in the group map, and the shareholder
                        //number is the same then add the account number as part of the 
                        //key of the trxn group map; this means delete the item in the
                        //map and reinsert it with a modified key
                        DString newKey;
                        DString accountNumInPartialKey;
                        DString accountNumInCrtKey;
                        DString shrNumInPartialKey;
                        DString shrNumInCrtKey;

                        if( ( crtKey.find( TRXNTAG::ACCTTAG ) == DString::npos && //acct not part of the current key
                              getValueForTag( partialTrxnGrpMapKey, TRXNTAG::ACCTTAG, accountNumInPartialKey ) && //account part of the partial key
                              getValueForTag( partialTrxnGrpMapKey, TRXNTAG::SHRTAG, shrNumInPartialKey ) &&  //shrnum part of the partial key
                              getValueForTag( crtKey, TRXNTAG::SHRTAG, shrNumInCrtKey ) && //shareholder number part of the crt key
                              shrNumInPartialKey == shrNumInCrtKey //the above shareholder numbers are equal
                            ) || //or it could be the other way around, from the perspective of shareholder
                            ( crtKey.find( TRXNTAG::SHRTAG ) == DString::npos && //shr not part of the current key
                              getValueForTag( partialTrxnGrpMapKey, TRXNTAG::SHRTAG, shrNumInPartialKey ) && //shrnum part of the partial key
                              getValueForTag( partialTrxnGrpMapKey, TRXNTAG::ACCTTAG, accountNumInPartialKey ) && //account number part of the partial key
                              getValueForTag( crtKey, TRXNTAG::ACCTTAG, accountNumInCrtKey ) && //account number part of the crt key
                              accountNumInPartialKey == accountNumInCrtKey //the above account numbers are the same
                            )
                          )
                        { //now we can say that this is the same group

                          //build the new key
                           if( !shrNumInCrtKey.empty() ) //the shareholder number is in the crt key
                           {
                              addTag( newKey, TRXNTAG::SHRTAG, shrNumInCrtKey.c_str() );
                           }
                           else //the shareholder number is only in the partial key
                           {
                              addTag( newKey, TRXNTAG::SHRTAG, shrNumInPartialKey.c_str() );
                           }
                           if( accountNumInCrtKey != NULL_STRING ) //the account number is in the crt key
                           {
                              addTag( newKey, TRXNTAG::ACCTTAG, accountNumInCrtKey.c_str() );
                           }
                           else //the account number is only in the partial key
                           {
                              addTag( newKey, TRXNTAG::ACCTTAG, accountNumInPartialKey.c_str() );
                           }
                           addTag( newKey, TRXNTAG::TRXGRPID, strTrxnGroup.c_str() );
                           //delete the old element from the map
                           trxnGrpMap.erase( crtKey );
                           //insert the new one
                           trxnGrpMap.insert( std::make_pair( newKey.c_str(), groupInfo ) );
                        }
                        foundTrxnGroup = true;
                        break;
                     }
                  }//end of for loop
                  if( foundTrxnGroup ) //exit the for loop if we found a group
                  {
                     break;
                  }
                  dump = dump.substr( pos + 1 );
               }//end of while  loop
               if( !foundTrxnGroup )
               {
                  //insert the groupInfo in the map, since this a new trxn grp id
                  groupInfo = new TrxnGroupInfo;
                  trxnGrpMap.insert( std::make_pair( trxnGrpMapKey.c_str(), groupInfo ) );
                  //increase the group number, as well
                  _trxnGroupSemaphore.wait();
                  trxnGroup = DSTCWorkSession::_maxTrxnGroup++;
                  _trxnGroupSemaphore.post();
               }

               //based on the type of the transaction we will determine if the current
               //persistent group has been filled or not
               long typeOfTrxn = NO_TRXNS;
               //look for the type of the object in the key, so we can determine
               //the transaction subtype and if a new trxn group id is needed
               if( strKey.find( TRXNTAG::ADDRESSTAG ) != DString::npos )
               {
                  trxnSubType = SHRACCGROUPING::ADDRESS;
                  typeOfTrxn = TRXN_ADDRESS;
               }
               else if( strKey.find( TRXNTAG::ACCTMAILINGTAG ) != DString::npos )
               {
                  trxnSubType = SHRACCGROUPING::MAILING;
                  typeOfTrxn = TRXN_MAILING;
               }
               else if( strKey.find( TRXNTAG::ACCTMAILINGOVERRIDETAG ) != DString::npos )
               {
                  trxnSubType = SHRACCGROUPING::MAILING_OVERRIDE;
                  typeOfTrxn = TRXN_MAILINGOVERRIDE;
               }
               else if( strKey.find( TRXNTAG::ENTITYIDTAG ) != DString::npos && 
                        strKey.find( TRXNTAG::ENTITYIDSTAG ) == DString::npos )
               {
                  trxnSubType = SHRACCGROUPING::ENTITY;
                  typeOfTrxn = TRXN_ENTITY;
               }
               else if( strKey.find( TRXNTAG::ENTITYIDSTAG ) != DString::npos )
               {
                  trxnSubType = SHRACCGROUPING::ENTITYIDS;
                  typeOfTrxn = TRXN_ENTITYIDS;
               }
               else if( strKey.find( TRXNTAG::ACCTENTITYTAG ) != DString::npos )
               {
                  trxnSubType = SHRACCGROUPING::ACCTENTITY;
                  typeOfTrxn = TRXN_ACCTENTITY;
               }
               //if there is only the ShrNum in the key string then this is a 
               //shareholder object
               else if( (strKey.find( TRXNTAG::SHRTAG ) != DString::npos ) &&
                        (strKey.find_first_of( TRXNTAG::EQ ) ==
                         strKey.find_last_of( TRXNTAG::EQ )) )
               {
                  trxnSubType = SHRACCGROUPING::SHR;
                  typeOfTrxn = TRXN_SHR;
               }
               //if the shareholder num and the account num are in the key
               //then the object is an account
               else if( strKey.find( TRXNTAG::ACCTTAG ) != DString::npos && 
                        strKey.find( TRXNTAG::SHRTAG ) != DString::npos )
               {
                  trxnSubType = SHRACCGROUPING::ACCT;
                  typeOfTrxn = TRXN_ACCT;
               }
               else if( strKey.find( TRXNTAG::ACCTGUARNTGUARDOPTNTAG ) != DString::npos )
               {
			      trxnSubType = SHRACCGROUPING::ACCT;
                  typeOfTrxn = TRXN_ACCTGUARNTGUARDOPT;
                  //typeOfTrxn = TRXN_ACCT;
			   }
			   else if ( strKey.find( TRXNTAG::ACCTREGDETAILS ) != DString::npos )
			   {
				   trxnSubType = SHRACCGROUPING::ACCT;
				   typeOfTrxn = TRXN_ACCTREGDETAILS;
			   }
			   else if ( strKey.find( TRXNTAG::ENTITYREGDETAILS ) != DString::npos )
			   {
				   trxnSubType = SHRACCGROUPING::ACCT;
				   typeOfTrxn = TRXN_ENTITYREGDETAILS;
			   }
			   else if ( strKey.find( TRXNTAG::ENTITYREGJURISDETAILS ) != DString::npos )
			   {
				   trxnSubType = SHRACCGROUPING::ACCT;
				   typeOfTrxn = TRXN_ENTITYREGJURISDETAILS;
			   }
               else if ( strKey.find( TRXNTAG::ENTITYRISKTAG ) != DString::npos )
			   {
				   trxnSubType = SHRACCGROUPING::ACCT;
				   typeOfTrxn = TRXN_ENTITYRISK;
			   }

               //check if the trxngrp is filled
               while( groupInfo->_trxns & typeOfTrxn )
               {
                  //if it is filled check if there is another group that can
                  //accommodate the current transaction;if not create a new one
                  //change the key
                  addTag( trxnGrpMapKey, TRXNTAG::TRXGRPID, DString::asString( groupInfo->_nxtTrxnGrpId ).c_str() );
                  //look for this new key in the map
                  TRXN_GROUP_MAP::iterator grpIter = trxnGrpMap.find( trxnGrpMapKey );
                  //not found
                  if( grpIter == trxnGrpMap.end() )
                  {
                     //increment the current grp id
                     _trxnGroupSemaphore.wait();
                     trxnGroup = DSTCWorkSession::_maxTrxnGroup++;
                     _trxnGroupSemaphore.post();
                     //set the next group id for the current group info
                     groupInfo->_nxtTrxnGrpId = trxnGroup;
                     //build a new struct to be added to the map
                     TrxnGroupInfo* newgroupInfo = new TrxnGroupInfo;
                     //insert the grptrxns in the map, since this a new trxn grp id
                     //change the key again with the updated data,
                     //add the tag for the current transaction number
                     I_CHAR  i_trxnGroup[ 5 ];

                     //the trxn group will be built like this "0001",...
                     //padded, so we can order the map based on trxn group number
                     i_sprintf( i_trxnGroup, I_( "%04d" ), DSTCWorkSession::_maxTrxnGroup );
                     addTag( trxnGrpMapKey, TRXNTAG::TRXGRPID, i_trxnGroup );
                     trxnGrpMap.insert( std::make_pair( trxnGrpMapKey.c_str(), newgroupInfo ) );
                     //set the curent pointer of the struct to the new one
                     groupInfo = newgroupInfo;
                     break;
                  }
                  else
                  {
                     DString strTrxnGroup;

                     //get the group number
                     getValueForTag( trxnGrpMapKey, TRXNTAG::TRXGRPID, strTrxnGroup );
                     trxnGroup = strTrxnGroup.asInteger();
                     //get the information about this group
                     groupInfo = (*grpIter).second;
                  }
               }
               //set the transaction type to the current struct of trxns
               groupInfo->_trxns |= typeOfTrxn;
            }
            else if( trxnType == UPDATE_SETTLEMENT )
            {
               bool foundTrxnGroup = false;
               DString trxnGrpMapKey;
               for( TRXN_GROUP_MAP::iterator iter = trxnGrpMap.begin(); iter != trxnGrpMap.end(); iter++ )
               {
                  DString crtKey = (*iter).first;
                  if( crtKey.find( TRXNTAG::SETTLEMENTTAG ) != DString::npos )
                  {
                     DString strTrxnGroup;

                     //get the group number
                     strTrxnGroup = (*iter).first;
                     getValueForTag( crtKey, TRXNTAG::TRXGRPID, strTrxnGroup );
                     trxnGroup = strTrxnGroup.asInteger();
                     foundTrxnGroup = true;
                  }
               }

               if( !foundTrxnGroup )
               {
                  //insert the groupInfo in the map, since this a new trxn grp id
                  groupInfo = new TrxnGroupInfo;
                  I_CHAR  i_trxnGroup[ 5 ];
                  //the trxn group will be built like this "0001",...
                  //padded, so we can order the map based on trxn group number
                  i_sprintf( i_trxnGroup, I_( "%04d" ), DSTCWorkSession::_maxTrxnGroup );
                  addTag( trxnGrpMapKey, TRXNTAG::SETTLEMENTTAG , TRXNTAG::SETTLEMENTTAG );
                  addTag( trxnGrpMapKey, TRXNTAG::TRXGRPID, i_trxnGroup );
                  trxnGrpMap.insert( std::make_pair( trxnGrpMapKey.c_str(), groupInfo ) );
                  //increase the group number, as well
                  _trxnGroupSemaphore.wait();
                  trxnGroup = DSTCWorkSession::_maxTrxnGroup++;
                  _trxnGroupSemaphore.post();
               }
            }
            else
            {
               //if the object is added and is not one of the objects
               //used in a shareholder/account trxn it has to be saved
               //temporary so trxns that need to be commited before this one,
               //will have a chance to get a trxn group number
               if( htcIter.objActivity() == OBJ_ACTIVITY_ADDED )
               {
                  //save it for now
                  v_HTCTemp.push_back( strKey );
                  //continue with another transaction
                  ++htcIter;
                  continue;
               }
               else //in all other cases increment the trxn number
               {
                  _trxnGroupSemaphore.wait();
                  trxnGroup = DSTCWorkSession::_maxTrxnGroup++;
                  _trxnGroupSemaphore.post();
                  trxnSubType = SHRACCGROUPING::OTHER;
               }
            }
            //add the same transaction but with the new key
            getHostTransactionContainer().addTransaction( strKey, 
                                                          *htcIter, 
                                                          htcIter.objActivity(), 
                                                          trxnType, 
                                                          htcIter.keyTypes(), 
                                                          trxnGroup, 
                                                          trxnSubType );

            //erase the old entry in the map
            htcIter.erase();
            //set the boolean to reset the iterator
            resetIter = true;
         } // !htcIter.isCommited
      } //end if (htcIter.trxnGroup() == NO_GROUP && htcIter.trxnSubType() == NO_TRXN)
      //We are not sure if there is a need for reseting the iterator after inserting
      //and erasing something in the map. However, to be safe we do that. Further testing will
      //prove what is the best way to handle this case.
      if( resetIter )
      {
         htcIter.begin();
         resetIter = false;
      }
      else
      {
         ++htcIter;
      }
   }
   //clean and/or save the maps
   for( TRXN_GROUP_MAP::iterator trIter = trxnGrpMap.begin(); trIter != trxnGrpMap.end(); )
   {
      delete (*trIter).second;
      trIter = trxnGrpMap.erase( trIter );
   }
   //save the temporary map
   for( TRXN_TEMP_VECTOR::iterator v_iter = v_HTCTemp.begin(); v_iter != v_HTCTemp.end(); 
      v_iter = v_HTCTemp.erase( v_iter ) )
   {
      DString strKey = *v_iter;
      HostTransactionContainerIterator htcIter( &getHostTransactionContainer() );

      //filter the HTC
      htcIter.walkStrKey( strKey );
      htcIter.walkTrxnGroup( NO_GROUP );
      htcIter.walkTrxnSubType( 0 );
      htcIter.begin();//start the iteration
      while( !htcIter.end() )
      {
         //add the same transaction but with the new key
         _trxnGroupSemaphore.wait();
         //increment the groups
         DSTCWorkSession::_maxTrxnGroup++;
         _trxnGroupSemaphore.post();
         getHostTransactionContainer().addTransaction( htcIter.strKey(), 
                                                       *htcIter, 
                                                       htcIter.objActivity(),
                                                       htcIter.trxnType(), 
                                                       htcIter.keyTypes(), 
                                                       DSTCWorkSession::_maxTrxnGroup, 
                                                       SHRACCGROUPING::OTHER );

         //erase the old entry in the map
         htcIter.erase();
         //reset the iterator
         //We are not sure if there is a need for reseting the iterator after inserting
         //and erasing something in the map. However, to be safe we do that. Further testing will
         //prove what is the best way to handle this case.
         htcIter.begin();
      }
   }
}

//******************************************************************************
void 
DSTCWorkSession::popCommitConditions( Frame* pFrame )
{
   MAKEFRAME2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("popConditions") );

   for( CONDITIONVECTOR::iterator iter = _commitConditions->begin();
      iter != _commitConditions->end(); iter = _commitConditions->erase( iter ) )
   {
      Condition* c = new Condition( **iter );

      pFrame->addCondition( c );
   }
   //clear the vector of conditions
   clearCommitConditions();
}

//******************************************************************************
void 
DSTCWorkSession::pushCommitConditions( Frame* pFrame )
{
   MAKEFRAME2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("pushConditions") );

   //add conditions to the conditions vector
   int count = pFrame->getCount();

   for( int i = 0; i < count; i++ )
   {
      Condition* c = new Condition( *pFrame->getCondition( i ) );
      _commitConditions->push_back( c );
   }
   pFrame->clearConditions( true );
}

//******************************************************************************
void 
DSTCWorkSession::clearCommitConditions()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("clearCommitConditions") );

   for( CONDITIONVECTOR::iterator iter = _commitConditions->begin();
      iter != _commitConditions->end(); iter = _commitConditions->erase( iter ) )
   {
      delete *iter;
   }
}

//******************************************************************************
bool 
DSTCWorkSession::hasCreatePermission( const DString& functionCode ) const
{
   DString mgmtCoId;
   getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);

   return(dynamic_cast<const DSTCUserSession &>(getUserSession()).hasCreatePermission( mgmtCoId, functionCode ));
}

//******************************************************************************
bool 
DSTCWorkSession::hasReadPermission( const DString& functionCode ) const
{
   DString mgmtCoId;
   getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);

   return(dynamic_cast<const DSTCUserSession &>(getUserSession()).hasReadPermission( mgmtCoId, functionCode ));
}

//******************************************************************************
bool 
DSTCWorkSession::hasUpdatePermission( const DString& functionCode ) const
{
   DString mgmtCoId;
   getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);

   return(dynamic_cast<const DSTCUserSession &>(getUserSession()).hasUpdatePermission( mgmtCoId, functionCode ));
}

//******************************************************************************
bool 
DSTCWorkSession::hasDeletePermission( const DString& functionCode ) const
{
   DString mgmtCoId;
   getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);

   return(dynamic_cast<const DSTCUserSession &>(getUserSession()).hasDeletePermission( mgmtCoId, functionCode ));
}

//******************************************************************************
bool 
DSTCWorkSession::isFunctionActivated( const DString& functionCode ) const
{
   DString mgmtCoId;
   getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);

   return dynamic_cast<const DSTCUserSession &>(getUserSession()).isFunctionActivated(mgmtCoId,functionCode);
}

//******************************************************************************
bool 
DSTCWorkSession::getValueForTag( DString &strBuffer, const I_CHAR* szTag, DString &strValue )
{
   TRACE_METHOD( CLASSNAME, GETVALUEFORTAG );

   //if tag found - remove value and insert new value
   DString strTag( szTag );
   strTag += TRXNTAG::EQ;

   DString::size_type iPos = strBuffer.find( szTag );

   if( iPos != std::string::npos )
   {
      //tag exists
      DString::size_type iTagLen = strTag.size();
      DString::size_type iSemicolon = strBuffer.find( ';', iPos + iTagLen );
      if( iSemicolon == std::string::npos )
      {
         assert(0);
         return(false);
      }
      strValue = strBuffer.substr( iPos + iTagLen, iSemicolon - (iPos + iTagLen) );
      return(true);
   }
   return(false);
}

//******************************************************************************
//for building the attribute list
//this method will change the value for a tag if the tag already exists
bool 
DSTCWorkSession::addTag( DString& strBuffer, const I_CHAR* szTag, const I_CHAR* szValue )
{
   TRACE_METHOD( CLASSNAME, ADDTAG );

   //if tag found - remove value and insert new value
   DString strTag( TRXNTAG::SEMICOLON );
   strTag += szTag;
   strTag += TRXNTAG::EQ;

   std::string::size_type iPos = strBuffer.find( strTag );
   //if not found remove leading semicolon and try again (first tag)
   if( iPos == std::string::npos )
   {
      strTag.erase( 0, 1 );
      iPos = strBuffer.find( strTag );
   }

   if( iPos != std::string::npos )
   {
      //tag exists
      std::string::size_type iTagLen = strTag.size();
      std::string::size_type iSemicolon = strBuffer.find( ';', iPos + iTagLen );
      if( iSemicolon == std::string::npos )
      {
         assert(0);
         return(false);
      }

      std::string::size_type iValStart = iPos + iTagLen;
      strBuffer.erase( iValStart, iSemicolon - iValStart );
      strBuffer.insert( iValStart, szValue );
   }
   else
   {
      strBuffer += szTag;
      strBuffer += TRXNTAG::EQ;
      //strBuffer += I_( "\"" );
      strBuffer += szValue;
      //strBuffer +=  I_( "\"" );
      strBuffer += TRXNTAG::SEMICOLON;
   }
   return(true);
}

//******************************************************************************
void 
DSTCWorkSession::checkSubstitutionsValues( const DString& keyType, const DString& tempValue, BFData &request )
{
   DString strKey, permValue, origValue ;


   // is a new value
   if( tempValue.find( NEW_PRFX ) != DString::npos &&
       _hostSubstitutionList != NULL )
   {
      //build the exact key for the host substitutions list

      if (keyType == I_("RESPPCGId"))
      {
         HostSubstitutionValuesList::buildHostSubstValueKey( strKey, KEYTYPES::ENTITYID, tempValue );
      }
      else if(keyType == I_("ASSOCENTITYId"))
      {
         HostSubstitutionValuesList::buildHostSubstValueKey( strKey, KEYTYPES::ENTITYID, tempValue );
      }
      else
      {
         HostSubstitutionValuesList::buildHostSubstValueKey( strKey, keyType, tempValue );
      }

      //define an iterator on this list
      BFObjIter substIter( *_hostSubstitutionList, BF::HOST );
      //if the element exists
      if( substIter.positionByKey( strKey ) )
      {
         BFFieldId idField = ifds::NullFieldId;

         //get the permanent value for it
         substIter.getObject()->getField( ifds::PermValue, permValue, BF::HOST );
         //determine the field id needed to be changed, based on the key type
         if( keyType == KEYTYPES::ACCOUNTNUM )
         {
            idField = ifds::AccountNum;
         }
         else if( keyType == KEYTYPES::ENTITYID )
         {
            idField = ifds::EntityId;
         }
         else if( keyType == KEYTYPES::SHRNUM )
         {
            idField = ifds::ShrNum;
         }
         else if (keyType == I_("RESPPCGId"))
         {
            idField = ifds::RESPPCGId;
         }
         else if (keyType == I_("ASSOCENTITYId"))
         {
             idField = ifds::AssocEntityId;
         }
         else
         {
            assert( 0 );
            throw;
            return;
         }

         //check first the fixed area
         if( request.exists( idField ) )
         {
            origValue = request.getElementValue( idField );
            origValue.stripLeading( '0' );
            origValue.strip();
            if( origValue == tempValue )
            {
               //set the permanent value for the fixed area
               request.setElementValue( idField, permValue, false, false );
            }
         }
         //check if this data has repeats
         if( request.exists( ifds::RepeatCount ) )
         {
            unsigned long cRepeats = request.getRepeatCount();

            for( unsigned long iRepeat = 0; iRepeat < cRepeats; ++iRepeat )
            {
               BFData& repeat = const_cast<BFData&>(request.getRepeat( iRepeat ) );

               if( repeat.exists( idField ) )
               {
                  origValue = repeat.getElementValue( idField );
                  origValue.stripLeading( '0' );
                  origValue.strip();
                  if( origValue == tempValue )
                  {
                     //set the permanent value for each repeat
                     repeat.setElementValue( idField, permValue, false, false );
                  }
               }
               
               if( keyType == KEYTYPES::ENTITYID && repeat.exists( ifds::Contact1EntityID))
               {
                  origValue = repeat.getElementValue( ifds::Contact1EntityID );
                  origValue.stripLeading( '0' );
                  origValue.strip();
                  if( origValue == tempValue )
                  {
                     //set the permanent value for each repeat
                     repeat.setElementValue( ifds::Contact1EntityID, permValue, false, false );
                  }
               }

               if( keyType == KEYTYPES::ENTITYID && repeat.exists( ifds::Contact2EntityID))
               {
                  origValue = repeat.getElementValue( ifds::Contact2EntityID );
                  origValue.stripLeading( '0' );
                  origValue.strip();
                  if( origValue == tempValue )
                  {
                     //set the permanent value for each repeat
                     repeat.setElementValue( ifds::Contact2EntityID, permValue, false, false );
                  }
               }
            }
         }
      }
   }
}

//******************************************************************************
SEVERITY 
DSTCWorkSession::getHostAccountNum( const DString& tempAccountNum, DString &hostAccountNum )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, GETHOSTACCOUNTNUM );

   DString strKey;

   if( _hostSubstitutionList != NULL )
   {
      //build the exact key for the host substitutions list
      HostSubstitutionValuesList::buildHostSubstValueKeyForTempAccount( strKey, tempAccountNum );
      //define an iterator on this list
      BFObjIter substIter( *_hostSubstitutionList, BF::HOST );

      //if the element exists
      if( substIter.positionByKey( strKey ) )
      {
         if( !substIter.end() )
         {
            //get the permanent value for it
            substIter.getObject()->getField( ifds::PermValue, hostAccountNum, BF::HOST );
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY 
DSTCWorkSession::getHostShareholderNum( const DString& tempShrNum, DString &hostShrNum )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, GETHOSTSHAREHOLDERNUM );

   DString strKey;

   if( _hostSubstitutionList != NULL )
   {
      //build the exact key for the host substitutions list
      HostSubstitutionValuesList::buildHostSubstValueKeyForTempShareholder( strKey, tempShrNum );
      //define an iterator on this list
      BFObjIter substIter( *_hostSubstitutionList, BF::HOST );

      //if the element exists
      if( substIter.positionByKey( strKey ) )
      {
         if( !substIter.end() )
         {
            //get the permanent value for it
            substIter.getObject()->getField( ifds::PermValue, hostShrNum, BF::HOST );
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY 
DSTCWorkSession::getHostEntityId( const DString& tempEntityId, DString &hostEntityId )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, GETHOSTENTITYID );

   DString strKey;

   if( _hostSubstitutionList != NULL )
   {
      //build the exact key for the host substitutions list
      HostSubstitutionValuesList::buildHostSubstValueKeyForTempEntity( strKey, tempEntityId );
      //define an iterator on this list
      BFObjIter substIter( *_hostSubstitutionList, BF::HOST );

      //if the element exists
      if( substIter.positionByKey( strKey ) )
      {
         if( !substIter.end() )
         {
            //get the permanent value for it
            substIter.getObject()->getField( ifds::PermValue, hostEntityId, BF::HOST );
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void 
DSTCWorkSession::setRunMode (BFData* request, BF_OBJ_ACTIVITY objActivity)
{
   if (objActivity == OBJ_ACTIVITY_NONE || 
       objActivity == OBJ_ACTIVITY_MODIFIED)
   {
      request->setElementValue (ifds::RunMode, RUNMODE::MODIFIED);
   }
   else if (objActivity == OBJ_ACTIVITY_ADDED)
   {
      request->setElementValue (ifds::RunMode, RUNMODE::ADDED);
   }
   else if (objActivity == OBJ_ACTIVITY_DELETED)
   {
      request->setElementValue (ifds::RunMode, RUNMODE::DELETED);
   }
   else
   {
      //shouldn't get here
      assert (0);
      throw;
   }
}

//******************************************************************************
const DString 
DSTCWorkSession::getRunMode( BF_OBJ_ACTIVITY Activity, bool objUpdated )
{
   if( Activity == OBJ_ACTIVITY_ADDED )
      return(RUNMODE::ADDED );
   else if( Activity == OBJ_ACTIVITY_DELETED )
      return(RUNMODE::DELETED );
   else if( Activity == OBJ_ACTIVITY_NONE && objUpdated )
      return(RUNMODE::MODIFIED );
   else
      return(RUNMODE::UNCHANGED);
}

//*******************************************************************************************
SEVERITY DSTCWorkSession::getAMSMstrList(AMSMstrList *&pAmsMstrList 
									  , const DString& dstrAmsType
									  , const DString& dstrAmsCode
									  , const DString& dstrEffectiveDate
									  , const BFDataGroupId& idDataGroup /*= BF::HOST*/
									  , bool bCreate /*= true*/
									  , bool bDel /*= false*/
									  , bool ignoreDataNotFound /*= true*/ 
									  , bool bDupCheck /*= false*/
									  )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getAMSMstrList") );
   const DString dstrAmsStringKey = dstrAmsType + dstrAmsCode + dstrEffectiveDate;
   BFObjectKey objKey(dstrAmsStringKey, idDataGroup, OBJ_ACTIVITY_NONE, 
      OBJ_TYPE_AMS_GLOBAL);

   pAmsMstrList = NULL;
   pAmsMstrList = dynamic_cast<AMSMstrList* >(findObject( objKey ));
	if (bDel && pAmsMstrList != NULL) // client wants to delete the list
	{
      //BFCBO::deleteObject does not remove object from map unless
      //the data group is the same.  In this case SetObject below 
      //should remove the old list and replace with new one so delete
      //is not necessary.  This fixes PTS 10021894

      //BFCBO::deleteObject(dstrAmsStringKey, idDataGroup, true, true);
      pAmsMstrList = NULL;
	}
   if (!pAmsMstrList && bCreate)
   {
      pAmsMstrList = new AMSMstrList(*this);
      if(pAmsMstrList)
      {
         if (pAmsMstrList->init(dstrAmsType, dstrAmsCode, dstrEffectiveDate, idDataGroup, bDupCheck, ignoreDataNotFound) <= WARNING)
         {
            setObject(objKey, pAmsMstrList);
         }
         else
         {
            delete pAmsMstrList;
            pAmsMstrList = NULL;
         }
      }
   }
	return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
double DSTCWorkSession::getExchRate( const DString& dstrToCurrency, 
   DString &AsofDate, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getExchRateRate" ) );

   DString dstrCurrency;
   double dec_ExchRate = 1;

   getField( ifds::Currency, dstrCurrency, idDataGroup );
   dstrCurrency.strip();

   ExchRateList exchRateList( *this );
   exchRateList.init();

   return(exchRateList.getExchRate( dstrCurrency, dstrToCurrency, AsofDate, idDataGroup ));
}

/*
SEVERITY DSTCWorkSession::getReportStatusCriteria ( ReportStatusCriteria*& pReportStatusCriteria, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getReportStatusCriteria" ) );

   BFObjectKey objKey( I_("Reports"), idDataGroup, OBJ_ACTIVITY_NONE, OBJ_TYPE_REPORT );
   pReportStatusCriteria = dynamic_cast<ReportStatusCriteria* >( findObject( objKey ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

SEVERITY DSTCWorkSession::createReportStatusCriteria ( ReportStatusCriteria*& pReportStatusCriteria, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "createReportStatusCriteria" ) );

   BFObjectKey objKey( I_("ReportStatusCriteria"), idDataGroup, OBJ_ACTIVITY_NONE, OBJ_TYPE_REPORT );
   pReportStatusCriteria = new ReportStatusCriteria ( *this );
   pReportStatusCriteria->init( idDataGroup );
   setObject ( objKey, pReportStatusCriteria );

   return(GETCURRENTHIGHESTSEVERITY());
}
*/

//******************************************************************************

SEVERITY DSTCWorkSession::getBrokerCutOff(const DString& dstrBrokerCode, AcctCutOffTimesList*& pBrokerCutOff, const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getBrokerCutOff") );

	BFObjectKey objKey(I_("BROKERCUTOFF;BrokerCode=") + dstrBrokerCode, idDataGroup, OBJ_ACTIVITY_NONE, OBJ_TYPE_BROKERCUTOFF_LIST);

	pBrokerCutOff = NULL;
	pBrokerCutOff = dynamic_cast<AcctCutOffTimesList*>(findObject (objKey));
	if(!pBrokerCutOff && true)
	{
		pBrokerCutOff = new AcctCutOffTimesList(*this);
		if(pBrokerCutOff)
		{
			if(pBrokerCutOff->init(NULL_STRING, NULL_STRING, dstrBrokerCode) <= WARNING)
			{
				setObject(objKey, pBrokerCutOff);
			}
			else
			{
				delete pBrokerCutOff;
				pBrokerCutOff = NULL;
			}
		}
	}
	
	return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************************
SEVERITY DSTCWorkSession::getWorkSessionEntityList (WorkSessionEntityList *&pWorkSessionEntityList, 
   const BFDataGroupId& idDataGroup /*=BF::HOST*/, bool bCreate /*= true*/)
{
   return getObject_X (I_("WorkSessionEntityList"), pWorkSessionEntityList, BF::HOST, 
      OBJ_TYPE_ENTITY, bCreate);
}

//******************************************************************************
SEVERITY DSTCWorkSession::getBrokerList(BrokerList *&pBrokerList, 
   const BFDataGroupId& idDataGroup /*=BF::HOST*/, bool bCreate /*= true*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getBrokerList") );

   //always use BF::HOST
   return getObject_X(I_("BrokerList"), pBrokerList, BF::HOST, 
      OBJ_TYPE_BROKER, bCreate);
}

//******************************************************************************
SEVERITY DSTCWorkSession::getTradesList(WorksessionTradesList *&pTradesList,
   const BFDataGroupId& idDataGroup /*=BF::HOST*/, bool bCreate /*= true*/,
   const DString& dstrTrack /*= I_("N")*/, const DString& dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getTradesList"));

   return getObject_X(I_("WorksessionTradesList"), pTradesList, idDataGroup, 
      OBJ_TYPE_TRADES_LIST, bCreate, dstrTrack, dstrPageName);
}

//******************************************************************************
SEVERITY DSTCWorkSession::getProtectedFundList(ProtectedFundList *&pProtectedFundList, 
   const BFDataGroupId& idDataGroup /*= BF::HOST*/, bool bCreate /*=true*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getProtectedFundList"));

   //always use BF::HOST
   return getObject_X(I_("ProtectedFundList"), pProtectedFundList, BF::HOST, 
      OBJ_TYPE_PROTECTED_FUND_LIST, bCreate);
}

//******************************************************************************************
SEVERITY DSTCWorkSession::getMktIndexMasterList(MktIndexMasterList *&pMktIndexMasterList, 
   const BFDataGroupId& idDataGroup /*= BF::HOST*/, bool bCreate /*=true*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getMktIndexMasterList"));

   return getObject_X(I_("MktIndexMasterList"), pMktIndexMasterList, idDataGroup, 
      OBJ_TYPE_MKT_INDEX_MASTER, bCreate);
}

//******************************************************************************************
SEVERITY DSTCWorkSession::getMktIndexValuesList(MktIndexValuesList *&pMktIndexValuesList, 
   const BFDataGroupId& idDataGroup /*= BF::HOST*/, bool bCreate)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getMktIndexValuesList") );

   return getObject_X(I_("MktIndexValuesList"), pMktIndexValuesList, idDataGroup, 
      OBJ_TYPE_MKT_INDEX_VALUES, bCreate);
}
//******************************************************************************************
SEVERITY DSTCWorkSession::setMktIndexValuesList(MktIndexValuesList *&pMktIndexValuesList)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("setMktIndexValuesList") );

   if( pMktIndexValuesList )
   {
	   setObject( pMktIndexValuesList, I_("MktIndexValuesList"), OBJ_ACTIVITY_NONE, BF::HOST );
   }
   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************************
SEVERITY DSTCWorkSession::getMktIndexValuesList(	MktIndexValuesList *&pMktIndexValuesList,
													const BFDataGroupId& idDataGroup,													
													const DString& dstrIndexCode,
													const DString& dstrFromDate,
													const DString& dstrSearchType,
													const DString& dstrToDate)
													
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMktIndexValuesList" ) );

	pMktIndexValuesList = NULL;
	DString strKey = I_("MktIndexValuesList;SearchType=") + dstrSearchType + 
					 I_(";IndexCode=")		+ dstrIndexCode +
					 I_(";FromDate=")		+ dstrFromDate  + 
					 I_(";ToDate=")			+ dstrToDate;

	BFObjectKey objKey(strKey , idDataGroup, OBJ_ACTIVITY_NONE, OBJ_TYPE_MKT_INDEX_VALUES );
	pMktIndexValuesList = dynamic_cast<MktIndexValuesList*>( findObject( objKey ) );

	if( !pMktIndexValuesList)
	{
		pMktIndexValuesList = new MktIndexValuesList( *this );

		//Do a database inquiry
		if( pMktIndexValuesList->init (	idDataGroup,I_("N"),NULL_STRING,dstrSearchType,dstrIndexCode, dstrFromDate, 
											dstrToDate ) > WARNING )
		{
			delete pMktIndexValuesList;
			pMktIndexValuesList = NULL;
		}
		else
		{
    		setObject( objKey, pMktIndexValuesList );
		}
	}

	return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************************
SEVERITY DSTCWorkSession::getSettlementLocationSysLvlList(SysLvlSettlementInstrList *&pSysLvlSettlementInstrList, 
   const BFDataGroupId& idDataGroup /*= BF::HOST*/, bool bCreate)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getSettlementLocationSysLvlList") );

   return getObject_X(I_("SysLvlSettlementInstrList"), pSysLvlSettlementInstrList, idDataGroup, 
      OBJ_TYPE_SETTLEMENT_LOCATION_SYSLVL_LIST, bCreate);
}

//******************************************************************************
SEVERITY DSTCWorkSession::getTradeSearchCriteria(TradeSearchCriteria *&pTradeSearchCriteria, 
   const BFDataGroupId& idDataGroup /*= BF::HOST*/, bool bCreate /*=true*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getTradeSearchCriteria" ) );
   
   //always use BF::HOST
   return getObject_X(I_("TradeSearchCriteria"), pTradeSearchCriteria, BF::HOST, 
      OBJ_TYPE_NONE, bCreate);
}
//******************************************************************************
SEVERITY DSTCWorkSession::getTradeVerificationSearchCriteria(TradeVerificationSearch *&pTradeVerifcationSearchCriteria, 
                                                            const BFDataGroupId& idDataGroup /*= BF::HOST*/, bool bCreate /*=true*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "TradeVerificationSearch" ) );
   
   //always use BF::HOST
   return getObject_X(I_("TradeVerificationSearch"), pTradeVerifcationSearchCriteria, BF::HOST, 
      OBJ_TYPE_TRADEVERIFICATION_LIST, bCreate);
}
////******************************************************************************
SEVERITY DSTCWorkSession::getTradeOverideRuleWarningsList( TradeOverideRuleWarningsList *&pTradeOverideRuleWarningsList, 
                                                           const BFDataGroupId& idDataGroup /*= BF::HOST*/, bool bCreate /*=true*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "TradeVerificationSearch" ) );
   
   //always use BF::HOST
   return getObject_X(I_("TradeOverideRuleWarningsList"), pTradeOverideRuleWarningsList, BF::HOST, 
      OBJ_TYPE_NONE, bCreate);
}
//******************************************************************************
SEVERITY DSTCWorkSession::getCancelInstrSearchCriteria ( CancelInstrSearchCriteria *&pCancelInstrSearchCriteria, 
   const BFDataGroupId& idDataGroup/*=BF::HOST*/, bool bCreate /*=true*/)

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getCancelInstrSearchCriteria" ) );
   
   //always use BF::HOST
   return getObject_X(I_("CancelInstrSearchCriteria"), pCancelInstrSearchCriteria, BF::HOST, 
      OBJ_TYPE_NONE, bCreate);
}
//******************************************************************************************
SEVERITY DSTCWorkSession::getSettlement(Settlement *&pSettlement,
   const BFDataGroupId& idDataGroup /*= BF::HOST*/, bool bCreate /*=true*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getSettlementSearch") );

   return getObject_X(I_("Settlement"), pSettlement, idDataGroup, 
      OBJ_TYPE_SETTLEMENT_SEARCH, bCreate);
}

//******************************************************************************************
SEVERITY DSTCWorkSession::getBrokerAMSsearch(BrokerAMSsearch *&pBrokerAMSsearch,
   const BFDataGroupId& idDataGroup/*= BF::HOST*/, bool bCreate /*=true*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getBrokerAMSSearch") );

   return getObject_X(I_("BrokerAMSsearch"), pBrokerAMSsearch, idDataGroup, 
      OBJ_TYPE_BROKER_AMS_SEARCH, bCreate);
}

//******************************************************************************************
SEVERITY DSTCWorkSession::getFeeParamSysSearchCriteria(
   FeeParamSysSearchCriteria *&pFeeParamSysSearchCriteria,
   const BFDataGroupId& idDataGroup /*= BF::HOST*/, bool bCreate /*=true*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getFeeParamSysSearchCriteria") );

   return getObject_X(I_("FeeParamSysSearchCriteria"), pFeeParamSysSearchCriteria, 
      idDataGroup, OBJ_TYPE_FEEPARAM_SYSTEM, bCreate);
}

//******************************************************************************
SEVERITY DSTCWorkSession::getManualDividendList(ManualDividendList *&pManualDividendList, 
   const BFDataGroupId& idDataGroup /*= BF::HOST*/, bool bCreate /*= true*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getManualDividendList") );

   //always use BF::HOST
   return getObject_X(I_("ManualDividendList"), pManualDividendList, 
      BF::HOST, OBJ_TYPE_MANUAL_DIVIDEND_LIST, bCreate);
}

//******************************************************************************
SEVERITY DSTCWorkSession::getFundBankInstructionsListRepository(
   FundBankInstructionsListRepository *&pFundBankInstructionsListRepository, 
   const BFDataGroupId& idDataGroup /*= BF::HOST*/, bool bCreate /*= true*/)
{
   //always use BF::HOST
   return getObject_X(I_("FundBankInstructionsListRepository"), 
      pFundBankInstructionsListRepository, 
      BF::HOST, OBJ_TYPE_FUND_BANK_INSTRUCTIONS_LIST_REPOSITORY, bCreate);
}
/******************************************************************************
Input:Default==>BFDataGroupId   = BF::HOST,
	  bool create = true
OutPut: FundBankInstructionsListRepository object
Return:	SEVERITY
Functionality:Gets and sets the AgentbankInstruction list and attach it with the 
worksession object
******************************************************************************/
SEVERITY DSTCWorkSession::getAgentBankInstructionsListRepository(
	AgentBankInstructionsListRepository *&pAgentBankInstructionsListRepository, 
	const BFDataGroupId& idDataGroup /*= BF::HOST*/, bool bCreate /*= true*/)
{
	//always use BF::HOST
	return getObject_X(I_("AgentBankInstructionsListRepository"), 
		pAgentBankInstructionsListRepository, 
		BF::HOST, OBJ_TYPE_AGENT_BANK_INSTRUCTIONS_LIST_REPOSITORY, bCreate);	
}

//******************************************************************************
SEVERITY DSTCWorkSession::getDistributorRepository(
   DistributorRepository *&pDistributorRepository,
   const BFDataGroupId& idDataGroup /*= BF::HOST*/, bool bCreate /*= true*/)
{
   //always use BF::HOST
   return getObject_X(I_("DistributorRepository"), 
      pDistributorRepository, 
      BF::HOST, OBJ_TYPE_DISTRIBUTOR_REPOSITORY, bCreate);
}

//******************************************************************************
SEVERITY DSTCWorkSession::getFinancialInstitutionListRepository(
   FinancialInstitutionListRepository *&pFinancialInstitutionListRepository,
   const BFDataGroupId& idDataGroup /*= BF::HOST*/, bool bCreate /*= true*/)
{
   //always use BF::HOST
   return getObject_X(I_("FinancialInstitutionListRepository"), 
      pFinancialInstitutionListRepository, 
      BF::HOST, OBJ_TYPE_FINANCIAL_INSTITUTION_REPOSITORY, bCreate);
}

//******************************************************************************
SEVERITY DSTCWorkSession::getDailyTransactionsFeesRepository (
   DailyTransactionsFeesRepository *&pDailyTransactionsFeesRepository,
   const BFDataGroupId &idDataGroup /*= BF::HOST*/, bool bCreate /*= true*/)
{
   //always use BF::HOST
   return getObject_X(I_("DailyTransactionsFeesRepository"), 
      pDailyTransactionsFeesRepository, 
      BF::HOST, OBJ_TYPE_DAILY_TRANSACTIONS_FEES_REPOSITORY, bCreate);
}

//******************************************************************************
SEVERITY DSTCWorkSession::getClientBankInstructionsList(
   ClientBankInstructionsList *&pClientBankInstructionsList, 
   const BFDataGroupId& idDataGroup /*=BF::HOST*/, bool bCreate /*=true*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getClientBankInstructionsList"));

   //always use BF::HOST
   return getObject_X(I_("ClientBankInstructionsList"), 
      pClientBankInstructionsList, BF::HOST, OBJ_TYPE_CLIENT_BANK_INSTRUCTIONS_LIST, bCreate);
}

//******************************************************************************
/*SEVERITY DSTCWorkSession::getReports(
   ifastCommonReportCriteria*& pifastCommonReportCriteria, 
   const BFDataGroupId& idDataGroup, bool bCreate )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getReports" ) );

   return getObject_X(I_("Reports"), pifastCommonReportCriteria, 
      idDataGroup, OBJ_TYPE_REPORT, bCreate);
}

//******************************************************************************
SEVERITY DSTCWorkSession::getResetInstrList(ResetInstrList*& pResetInstrList, 
   const BFDataGroupId& idDataGroup, bool bCreate )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getResetInstrList" ) );

   return getObject_X(I_("ResetInstrList"), pResetInstrList, 
      idDataGroup, OBJ_TYPE_RESET_INSTR, bCreate);
}*/
//******************************************************************************
SEVERITY DSTCWorkSession::getFeeModelList(FeeModelList *&pFeeModelList, 
                  const BFDataGroupId& idDataGroup , 
                  const DString& dstrHoldingCompCode,
                  const DString& dstrHoldingCompName,
                  const DString& dstrFeeModelCode,
                  const DString& dstrFeeModelDesc,
                  const DString& dstrSearchAll,
                  const DString& dstrAsofDate,
                  bool bCreate,
                  bool bRetrieveAll)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getFeeModelList"));

   DString dstrTrack = I_("N");
   DString dstrPageName = NULL_STRING;
   bool isAllFeeModels = bRetrieveAll &&
                         dstrHoldingCompCode == NULL_STRING && 
                         dstrHoldingCompName == NULL_STRING && 
                         dstrFeeModelCode == NULL_STRING && 
                         dstrFeeModelDesc == NULL_STRING && 
                         dstrSearchAll == I_("Y") &&
                         dstrAsofDate == I_("12319999") ;

   BFObjectKey objKey(I_("FeeModelList"), BF::HOST, OBJ_ACTIVITY_NONE, OBJ_TYPE_FEE_MODEL_LIST);
   if(isAllFeeModels)
   {
      objKey.setStringKey(I_("FeeModelList-all"));
   }

   pFeeModelList = NULL;
   pFeeModelList = dynamic_cast<FeeModelList*>(findObject (objKey));
   if (!pFeeModelList 
      || !(isAllFeeModels && pFeeModelList->isAllFeeModels()) //all cases except when we have the full list and we are asking for the full list
      && bCreate)
   { 
      pFeeModelList = new FeeModelList(*this);
      if (pFeeModelList)
      {
            pFeeModelList->init (idDataGroup, dstrTrack, dstrPageName, dstrHoldingCompCode, dstrHoldingCompName, dstrFeeModelCode, dstrFeeModelDesc, dstrSearchAll, dstrAsofDate, bRetrieveAll); 
            setObject(objKey, pFeeModelList);
            pFeeModelList->setAllFeeModels(isAllFeeModels);
      }
   }
   return GETCURRENTHIGHESTSEVERITY();

}




//******************************************************************************
SEVERITY DSTCWorkSession::getChequeList(ChequeList *&pChequeList, 
                                        const BFDataGroupId& idDataGroup, 
										bool bCreate, 
										DString& TransId, 
										DString& AccountNum, 
										DString& InCheqNum, 
										DString& Broker, 
										DString& Status, 
										bool bIgnoreDataNotFound,
										bool bIgnoreUnknAcct)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMsgProcessList" ) );

	DString dstrkey = I_("ChequeList");
	dstrkey += I_("_");
	dstrkey += TransId.strip();
	dstrkey += I_("_");
	dstrkey += AccountNum.strip().stripLeading('0');
	dstrkey += I_("_");
	dstrkey += InCheqNum.strip();
	dstrkey += I_("_");
	dstrkey += Broker.strip();
	dstrkey += I_("_");
	dstrkey += Status.strip();
	dstrkey += I_("_");
	dstrkey += bIgnoreDataNotFound ? I_("Y") : I_("N");
    dstrkey += I_("_");
    dstrkey += bIgnoreUnknAcct ? I_("Y") : I_("N");

	BFObjectKey objKey(dstrkey , idDataGroup, OBJ_ACTIVITY_NONE, OBJ_TYPE_CHEQUE_LIST );
	pChequeList = dynamic_cast<ChequeList*>( findObject( objKey ) );

	if( !pChequeList && bCreate )
	{
		pChequeList = new ChequeList( *this );
		
		//do a database inquiry
		if( pChequeList->init (TransId, AccountNum, InCheqNum, Broker, 
                                Status, bIgnoreDataNotFound,bIgnoreUnknAcct) > WARNING )
		{
			delete pChequeList;
			pChequeList = NULL;
		}
		else
		{
			setObject( objKey, pChequeList );
		}
	}

	return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY DSTCWorkSession::getInterestSegmentList(	InterestSegmentList *&pInterestSegmentList,
													const DString& dstrAccountNum,
													const DString& dstrIntInvestID,
													const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getProgressiveIntRateList" ) );

	pInterestSegmentList = NULL;
	DString strKey = I_("InterestSegmentList;AccountNum=") + dstrAccountNum +
					 I_(";InvestId=")	+ dstrIntInvestID;
	
    pInterestSegmentList = 
        dynamic_cast<InterestSegmentList*> (BFCBO::getObject (strKey, idDataGroup));
	
	if( !pInterestSegmentList)
	{
		pInterestSegmentList = new InterestSegmentList(*this );

		//Do a database inquiry
		if( pInterestSegmentList->init (dstrAccountNum,
										dstrIntInvestID,
										idDataGroup) > WARNING )
		{
			delete pInterestSegmentList;
			pInterestSegmentList = NULL;
		}
		else
		{
            setObject ( pInterestSegmentList, 
                        strKey, 
                        OBJ_ACTIVITY_NONE, 
						idDataGroup);
		}
	}

	return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
SEVERITY DSTCWorkSession::getProgressiveIntRateList(	ProgressiveIntRateList *&pProgressiveIntRateList,
														const DString& dstrAccountNum,
														const DString& dstrIntInvestID,
														const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getProgressiveIntRateList" ) );

	pProgressiveIntRateList = NULL;
	DString strKey = I_("ProgressiveIntRateList;AccountNum=") + dstrAccountNum +
					 I_(";InvestId=")	+ dstrIntInvestID;
	
    pProgressiveIntRateList = 
        dynamic_cast<ProgressiveIntRateList*> (BFCBO::getObject (strKey, idDataGroup));
	
	if( !pProgressiveIntRateList)
	{
		pProgressiveIntRateList = new ProgressiveIntRateList( *this );

		//Do a database inquiry
		if( pProgressiveIntRateList->init (	dstrAccountNum,
											dstrIntInvestID,
										    idDataGroup) > WARNING )
		{
			delete pProgressiveIntRateList;
			pProgressiveIntRateList = NULL;
		}
		else
		{
            setObject ( pProgressiveIntRateList, 
                        strKey, 
                        OBJ_ACTIVITY_NONE, 
						idDataGroup);
		}
	}

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY DSTCWorkSession::getInvestmentHistoryList(	InvestmentHistoryList *&pInvestmentHistoryList,
													const DString& dstrAccountNum,
													const DString& dstrTranId,
													const DString& dstrFund,
													const DString& dstrClass,
													const DString& dstrInvestmentNo,
													const DString& dstrStatus,
													const DString& dstrSearchBy,
													const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getInvestmentHistoryList" ) );

	pInvestmentHistoryList = NULL;
	DString strKey = I_("InvestmentHistoryList;AccountNum=") + dstrAccountNum + 
					 I_(";TranId=")		+ dstrTranId +
					 I_(";Fund=")		+ dstrFund   +
					 I_(";Class=")		+ dstrClass  + 
					 I_(";InvestmentNo=")+ dstrInvestmentNo +
					 I_(";Status=")		+ dstrStatus +
					 I_(";SearchBy=")	+ dstrSearchBy;
	
    pInvestmentHistoryList = 
        dynamic_cast<InvestmentHistoryList*> (BFCBO::getObject (strKey, idDataGroup));
	
	if( !pInvestmentHistoryList)
	{
		pInvestmentHistoryList = new InvestmentHistoryList( *this );

		//Do a database inquiry
		if( pInvestmentHistoryList->init (	dstrAccountNum, dstrTranId, dstrFund, 
											dstrClass, dstrInvestmentNo, dstrStatus, dstrSearchBy,
											idDataGroup) > WARNING )
		{
			delete pInvestmentHistoryList;
			pInvestmentHistoryList = NULL;
		}
		else
		{
            setObject ( pInvestmentHistoryList, 
                        strKey, 
                        OBJ_ACTIVITY_NONE, 
						idDataGroup);
		}
	}

	return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
SEVERITY DSTCWorkSession::getFundSponsorFeeModelList ( FundSponsorFeeModelList *&pFundSponsorFeeModelList, 
                                                       const BFDataGroupId &idDataGroup,
                                                       bool bCreate, /*=true*/
                                                       const DString &feeModelCode,    /*=NULL_STRING*/
                                                       const DString &fundSponsorCode  /*=NULL_STRING*/,
                                                       bool allResults /*=false*/) 
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("getFundSponsorFeeModelList"));

   DString dstrkey = I_("FundSponsorFeeModelList");
   BFObjectKey objKey (dstrkey, BF::HOST, OBJ_ACTIVITY_NONE, OBJ_TYPE_FUND_SPONSOR_FEE_MODEL_LIST);
   FundSponsorFeeModelList *pFundSponsorFeeModelList_ = dynamic_cast <FundSponsorFeeModelList*> (findObject (objKey));
   
   if (!pFundSponsorFeeModelList_ && bCreate)
   {
      pFundSponsorFeeModelList_ = new FundSponsorFeeModelList (*this);
//do a database inquiry
	  if (pFundSponsorFeeModelList_->init (BF::HOST, I_("N"), NULL_STRING, feeModelCode, fundSponsorCode, allResults) > WARNING)
      {
         delete pFundSponsorFeeModelList_;
         pFundSponsorFeeModelList_ = NULL;
      }
      else
      {
         setObject (objKey, pFundSponsorFeeModelList_);
      }
   }
   else if (pFundSponsorFeeModelList_ && bCreate)
   {
	   pFundSponsorFeeModelList_->init (BF::HOST, I_("N"), NULL_STRING, feeModelCode, fundSponsorCode, allResults);
   }
   pFundSponsorFeeModelList = pFundSponsorFeeModelList_;
   return GETCURRENTHIGHESTSEVERITY();

}

//******************************************************************************

SEVERITY DSTCWorkSession::getFundBrokerList(FundBrokerList *&pFundBrokerList, 
   const BFDataGroupId& idDataGroup, bool bCreate, const DString& dstrFBCode, const DString& dstrFBname, 
   const bool noDataIsErrorCondition/*false*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "createResetInstrList" ) );
   DString dstrkey = I_("FundBrokerList ");
   BFObjectKey objKey(dstrkey , idDataGroup, OBJ_ACTIVITY_NONE, OBJ_TYPE_FUND_BROKER_LIST );
   FundBrokerList * _pFundBrokerList = dynamic_cast<FundBrokerList*>( findObject( objKey ) );

   if( !_pFundBrokerList && bCreate )
   {
      _pFundBrokerList = new FundBrokerList( *this );
      //do a database inquiry
	  if( _pFundBrokerList->init (dstrFBCode,dstrFBname, idDataGroup,I_("N"),NULL_STRING, noDataIsErrorCondition ) > WARNING )
      {
         delete _pFundBrokerList;
         _pFundBrokerList = NULL;
      }
      else
      {
         setObject( objKey, _pFundBrokerList );
      }
   }
   else if (_pFundBrokerList && bCreate )
   {
	   _pFundBrokerList->init (dstrFBCode,dstrFBname, idDataGroup,I_("N"),NULL_STRING );
   }

   pFundBrokerList = _pFundBrokerList;
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY DSTCWorkSession::getTransCancellist( TransCancellist *&pTransCancellist, 
                                              const DString& _TransNum,
											  const DString& cashDivPaidAfter,
                                              const BFDataGroupId& idDataGroup,
											  const DString &dstrTradeDate,
											  const DString &dstrFundCode,
										      const DString &dstrClassCode,
											  const DString &dstrSearchType,
											  const DString &dstrTranStatus,
										      const DString &dstrAdjustType,
											  const DString &dstrTradeAdjustId,
											  const DString &dstrSettleDate,
											  const DString &dstrTransType )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getTransCancellist" ) );

   DString dstrkey = I_("TransNum ")   + _TransNum 
	               + I_( "TradeDate" ) + dstrTradeDate
				   + I_( "FundCode" )  + dstrFundCode
				   + I_( "ClassCode" ) + dstrClassCode
	               + I_("SearchType")  + dstrSearchType 
				   + I_("Value" )      + dstrTranStatus + dstrAdjustType +
				   + I_( "TransType" ) + dstrTransType;
   BFObjectKey objKey(dstrkey , idDataGroup, OBJ_ACTIVITY_NONE, OBJ_TYPE_TRANS_CANCEL );

   TransCancellist * _pTransCancellist = dynamic_cast<TransCancellist*>( findObject( objKey ) );

   if( !_pTransCancellist  )
   {
      _pTransCancellist = new TransCancellist( *this );
      //do a database inquiry
	  if( _pTransCancellist->init( _TransNum, 
		                           cashDivPaidAfter,
								   idDataGroup, 
								   dstrTradeDate,
		                           dstrFundCode, 
								   dstrClassCode, 
								   dstrSearchType,
								   dstrTranStatus, 
								   dstrAdjustType,
								   dstrTradeAdjustId,
								   dstrSettleDate,
								   dstrTransType,
								   I_("N"),
								   NULL_STRING ) > WARNING )
      {
         delete _pTransCancellist;
         _pTransCancellist = NULL;
      }
      else
      {
         setObject( objKey, _pTransCancellist );
      }
   }

   pTransCancellist = _pTransCancellist;
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY DSTCWorkSession::getBulkCancellist( BulkCancellist *&pBulkCancellist,
											 const BFDataGroupId& idDataGroup, 
											 const DString &dstrTradeDate,
											 const DString &dstrFundCode,
											 const DString &dstrClassCode,
											 const DString &dstrTransNum,
											 const DString &dstrTradeAdjustId )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getBulkCancellist" ) );

	pBulkCancellist = NULL;
	DString dstrkey = I_("BulkCancelList") + dstrTradeDate + dstrFundCode + dstrClassCode;
    BFObjectKey objKey( dstrkey, idDataGroup, OBJ_ACTIVITY_NONE, OBJ_TYPE_BULK_CANCEL );
    pBulkCancellist = dynamic_cast<BulkCancellist*>( findObject( objKey ) );

    if( NULL == pBulkCancellist )
    {
      pBulkCancellist = new BulkCancellist( *this );
	  
	  if( pBulkCancellist->init( dstrTransNum,       //_TransNum, 
		                         I_( "" ),           // cashDivPaidAfter,
								 idDataGroup, 
								 dstrTradeDate,
		                   dstrFundCode, 
								 dstrClassCode, 
								 I_( "" ),           // dstrSearchType,
								 I_( "" ),           // dstrTranStatus, 
								 I_( "" ),           // dstrAdjustType,
								 dstrTradeAdjustId,  // TradeAdjustID
                         I_( "" ),           // settle date
                         NULL_STRING,
								 I_("N"),
								 NULL_STRING ) > WARNING )
      {
         delete pBulkCancellist;
         pBulkCancellist = NULL;
      }
      else
      {
         setObject( objKey, pBulkCancellist );
      }	  
    }    

    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************

SEVERITY DSTCWorkSession::getWhereUsedList(WhereUsedList *&pWhereUsedList, 
   const BFDataGroupId& idDataGroup, bool bCreate, const DString& dstrEntityId )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "createResetInstrList" ) );
   DString dstrkey = I_("WhereUsedList ") + dstrEntityId;
   BFObjectKey objKey(dstrkey , BF::HOST, OBJ_ACTIVITY_NONE, OBJ_TYPE_FUND_BROKER_LIST );
   WhereUsedList * _pWhereUsedList = dynamic_cast<WhereUsedList*>( findObject( objKey ) );

   if( !_pWhereUsedList && bCreate )
   {
      _pWhereUsedList = new WhereUsedList( *this );
      //do a database inquiry
	  if( _pWhereUsedList->init(dstrEntityId, I_("N"), NULL_STRING ) > WARNING )
      {
         delete _pWhereUsedList;
         _pWhereUsedList = NULL;
      }
      else
      {
         setObject( objKey, _pWhereUsedList );
      }
   }
   pWhereUsedList = _pWhereUsedList;
   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
//******************************************************************************
SEVERITY DSTCWorkSession::getAggregatedOrderList( const DString& dstrFromDate,
								                          const DString& dstrToDate,
								                          const DString& dstrStatus,
								                          const DString& dstrBrokerCode,
								                          const DString& dstrFundCode,
								                          const DString& dstrAggrOrderNum,
								                          const DString& dstrRoutingRefNum,
								                          const DString& dstrSearchType,
								                          AggregatedOrderList *&pAggregatedOrderListOut, 
								                          const BFDataGroupId& idDataGroup ,
                                                  const DString& dstrTrack /*= I_("N")*/,
                                                  const DString& dstrPageName /*= NULL_STRING*/,
                                                  bool bCreate, /*= true*/
								                          const DString& dstrFundKvBrkKvNum,
								                          const DString& dstrFundIDType,
								                          const DString& dstrFundIDValue,
								                          const DString& dstrAmountType,
								                          const DString& dstrAmount,
								                          const DString& dstrTransType)
{
   /*
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getAggregatedOrderList"));
	DString dstrkey = I_("AggregatedOrderList") + dstrAggrOrderNum;
   BFObjectKey objKey( dstrkey, BF::HOST, OBJ_ACTIVITY_NONE, OBJ_TYPE_AGGREGATED_ORDER_LIST );
   AggregatedOrderList * pAggregatedOrderList = dynamic_cast<AggregatedOrderList*>( findObject( objKey ) );
   if( !pAggregatedOrderList && bCreate )
   {
      pAggregatedOrderListOut = new AggregatedOrderList( *this );
      //do a database inquiry
      if( pAggregatedOrderListOut->init( dstrFromDate, dstrToDate, dstrStatus, dstrBrokerCode,
										 dstrFundCode, dstrAggrOrderNum, dstrRoutingRefNum,
										 dstrSearchType,
                               dstrTrack, dstrPageName,
                              dstrFundKvBrkKvNum,
                              dstrFundIDType,
                              dstrFundIDValue,
                              dstrAmountType,
                              dstrAmount,
                              dstrTransType                              
                               ) > WARNING )
      {


         delete pAggregatedOrderListOut;
         pAggregatedOrderListOut = NULL;
      }
      else
      {
         setObject( objKey, pAggregatedOrderListOut );
      }
   }
   else //get the account from the repository
   {
      pAggregatedOrderListOut = pAggregatedOrderList;
   }*/

   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("getAggregatedOrderList"));
   DString dstrKey = I_("AggregatedOrderList");
   BFObjectKey objKey (dstrKey, BF::HOST, OBJ_ACTIVITY_NONE, OBJ_TYPE_AGGREGATED_ORDER_LIST);
   AggregatedOrderList *pAggregatedOrderList = dynamic_cast <AggregatedOrderList*> (findObject(objKey));

   if (!pAggregatedOrderList && bCreate)
   {
      pAggregatedOrderList = new AggregatedOrderList (*this);
      //do a database inquiry
	  if (pAggregatedOrderList->init ( dstrFromDate, dstrToDate, dstrStatus, dstrBrokerCode,
										        dstrFundCode, dstrAggrOrderNum, dstrRoutingRefNum,
										        dstrSearchType, dstrTrack, dstrPageName,
                                      dstrFundKvBrkKvNum,
                                      dstrFundIDType,
                                      dstrFundIDValue,
                                      dstrAmountType,
                                      dstrAmount,
                                      dstrTransType) > WARNING)
      {
         delete pAggregatedOrderList;
         pAggregatedOrderList = NULL;
      }
      else
      {
         setObject (objKey, pAggregatedOrderList);
      }
   }
   else if (pAggregatedOrderList && bCreate)
   {
	  pAggregatedOrderList->init ( dstrFromDate, dstrToDate, dstrStatus, dstrBrokerCode,
										    dstrFundCode, dstrAggrOrderNum, dstrRoutingRefNum,
										    dstrSearchType, dstrTrack, dstrPageName,
                                  dstrFundKvBrkKvNum,
                                  dstrFundIDType,
                                  dstrFundIDValue,
                                  dstrAmountType,
                                  dstrAmount,
                                  dstrTransType);
   }
   pAggregatedOrderListOut = pAggregatedOrderList;
   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
template <class _X> 
   SEVERITY DSTCWorkSession::getObject_X(const I_CHAR* i_charname, _X*& pListOut, 
      const BFDataGroupId& idDataGroup, BF_OBJ_TYPE bfObjType, bool bCreate, 
      const DString& dstrTrack /*= I_("N")*/, const DString& dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getObject_X"));

   BFObjectKey objKey(i_charname, idDataGroup, OBJ_ACTIVITY_NONE, bfObjType);

   pListOut = NULL;
   pListOut = dynamic_cast<_X*>(findObject (objKey));
   if (!pListOut && bCreate)
   {
      pListOut = new _X(*this);
      if (pListOut)
      {
         if (pListOut->init (idDataGroup, dstrTrack, dstrPageName) <= WARNING)
         {
            setObject(objKey, pListOut);
         }
         else
         {
            delete pListOut;
            pListOut = NULL;
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//the below four methods need to cleaned-up a little bit
//to much redundacy (SP)
//they should be made to use the getObject_X template method
//******************************************************************************
SEVERITY DSTCWorkSession::getReports ( ifastCommonReportCriteria*& pifastCommonReportCriteria, 
   const BFDataGroupId& idDataGroup, bool bCreate /*= true*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getReports" ) );

   BFObjectKey objKey( I_("Reports"), idDataGroup, OBJ_ACTIVITY_NONE, OBJ_TYPE_REPORT );
   pifastCommonReportCriteria = dynamic_cast<ifastCommonReportCriteria* >( findObject( objKey ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY DSTCWorkSession::createReports (ifastCommonReportCriteria*& pifastCommonReportCriteria, 
   const BFDataGroupId& idDataGroup, bool bCreate /*= true*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "createReports" ) );

   BFObjectKey objKey( I_("Reports"), idDataGroup, OBJ_ACTIVITY_ADDED, OBJ_TYPE_REPORT );
   pifastCommonReportCriteria = new ifastCommonReportCriteria ( *this );
   pifastCommonReportCriteria->doInitWithDefaultValues(idDataGroup);
   setObject (objKey, pifastCommonReportCriteria);

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY DSTCWorkSession::createReports (ifastCommonReportCriteria*& pifastCommonReportCriteria, 
   DString dstrRptName, const BFDataGroupId& idDataGroup, bool bCreate /*= true*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "createReports" ) );

   BFObjectKey objKey( I_("Reports"), idDataGroup, OBJ_ACTIVITY_ADDED, OBJ_TYPE_REPORT );
   pifastCommonReportCriteria = new ifastCommonReportCriteria ( *this );
   pifastCommonReportCriteria->init(dstrRptName);
   setObject (objKey, pifastCommonReportCriteria);

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY DSTCWorkSession::getResetInstrList(ResetInstrList*& pResetInstrList, 
   const BFDataGroupId& idDataGroup, bool bCreate /*= true*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getResetInstrList" ) );

   BFObjectKey objKey( I_("ResetInstrList"), idDataGroup, OBJ_ACTIVITY_NONE  );
   pResetInstrList = dynamic_cast<ResetInstrList* >( findObject( objKey ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY DSTCWorkSession::createResetInstrList(ResetInstrList*& pResetInstrList, 
   const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "createResetInstrList" ) );

   BFObjectKey objKey( I_("ResetInstrList"), idDataGroup, OBJ_ACTIVITY_NONE, OBJ_TYPE_RESET_INSTR );
   pResetInstrList = new ResetInstrList (*this);
   setObject (objKey, pResetInstrList);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************************
SEVERITY DSTCWorkSession::getRemarkContainer(RemarkContainer*&  pRemarkContainer,
							const DString& dstrBrokerCode, 
							const DString& dstrBranchCode,
						   const DString& dstrAgentCode, 
							const DString& date,
							const BFDataGroupId& idDataGroup /*= BF::HOST */,
							bool  bCreate /*=true*/,
							const DString& dstrTrack,
							const DString& dstrPageName  														
							)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "createResetInstrList" ) );
   BFObjectKey objKey( I_("RemarkContainer"), BF::HOST, OBJ_ACTIVITY_NONE, OBJ_TYPE_REMARK_CONTAINER );
   RemarkContainer * pRemark = dynamic_cast<RemarkContainer*>( findObject( objKey ) );
   if( !pRemark && bCreate )
   {
      pRemark = new RemarkContainer( *this );
      //do a database inquiry
      if( pRemark->init(dstrBrokerCode,dstrBranchCode,dstrAgentCode,
								date,idDataGroup,dstrTrack,dstrPageName
								
								) > WARNING )
      {
         delete pRemark;
         pRemark = NULL;
      }
      else
      {
         setObject( objKey, pRemark );
      }
   }
   pRemarkContainer = pRemark;
   return GETCURRENTHIGHESTSEVERITY();

}

SEVERITY DSTCWorkSession::getMsgProcessList(MsgProcessCBOList *&pMsgProcessList, 
   const BFDataGroupId& idDataGroup, bool bCreate, const DString& EnvelopeID,
   const DString& TransNum, const DString& AggrOrderNum, const DString& ActivityID,
   const DString& SenderRefNum, const DString& NetworkID, const DString& StartDate,
   const DString& EndDate, const DString ProcessType, const DString& ProcessCategory,
   const DString& ProcessStatus, const DString& MsgSearchType )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMsgProcessList" ) );

   // Key
   DString dstrkey = I_("MsgProcessList:"); // + ;
   DString envelopeID( EnvelopeID ), transNum( TransNum ), aggrOrderNum( AggrOrderNum );
   DString activityID( ActivityID ), senderRefNum( SenderRefNum ), networkID( NetworkID );
   DString startDate( StartDate ), endDate( EndDate ), processType( ProcessType );
   DString processCategory( ProcessCategory ), processStatus( ProcessStatus );
   DString msgSearchType( MsgSearchType );
   envelopeID.stripAll(); transNum.stripAll(); aggrOrderNum.stripAll();
   activityID.stripAll(); senderRefNum.stripAll(); networkID.stripAll();
   startDate.stripAll(); endDate.stripAll(); processType.stripAll();
   processCategory.stripAll(); processStatus.stripAll(); msgSearchType.stripAll();
   dstrkey += I_("SRCH") + msgSearchType;
   dstrkey += I_("ENV") + envelopeID + I_("TRA") + transNum + I_("AGG") + aggrOrderNum;
   dstrkey += I_("ACT") + activityID + I_("SEN") + senderRefNum + I_("NET") + networkID;
   dstrkey += I_("STA") + startDate + I_("END") + endDate + I_("PTY") + processType;
   dstrkey += I_("PCA") + processCategory + I_("PST") + processStatus;
   dstrkey.upperCase();

   BFObjectKey objKey(dstrkey, BF::HOST, OBJ_ACTIVITY_NONE, OBJ_TYPE_MSG_PROCESS_LIST );

   MsgProcessCBOList * _pMsgProcessList = dynamic_cast<MsgProcessCBOList*>( findObject( objKey ) );

   if( !_pMsgProcessList && bCreate )
   {
      _pMsgProcessList = new MsgProcessCBOList( *this );

	  if( _pMsgProcessList->init( I_("N"), NULL_STRING, EnvelopeID, TransNum, AggrOrderNum, ActivityID,
        SenderRefNum, NetworkID, StartDate, EndDate, ProcessType, ProcessCategory, ProcessStatus, MsgSearchType ) > WARNING )
      {
         delete _pMsgProcessList;
         _pMsgProcessList = NULL;
      }
      else
      {
         setObject( objKey, _pMsgProcessList );
      }
   }
   pMsgProcessList = _pMsgProcessList;
   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY DSTCWorkSession::getMsgDetailList(MsgDetailList *&pMsgDetailList, 
   const BFDataGroupId& idDataGroup, bool bCreate, const DString& ActivityID )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMsgDetailList" ) );
   DString dstrkey = I_("MsgDetailList") + ActivityID;
   BFObjectKey objKey(dstrkey, BF::HOST, OBJ_ACTIVITY_NONE, OBJ_TYPE_MSG_DETAIL_LIST );
   MsgDetailList *_pMsgDetailList = dynamic_cast<MsgDetailList*>( findObject( objKey ) );

   if( !_pMsgDetailList && bCreate )
   {
      _pMsgDetailList = new MsgDetailList( *this );

	  if( _pMsgDetailList->initExisting( I_("N"), NULL_STRING, ActivityID ) > WARNING )
      {
         delete _pMsgDetailList;
         _pMsgDetailList = NULL;
      }
      else
      {
         setObject( objKey, _pMsgDetailList );
      }
   }
   pMsgDetailList = _pMsgDetailList;
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY DSTCWorkSession::getMessageEnvelopeList(const DString& NetworkID,
																 const DString& FileName,
																 const DString& StartDate,
																 const DString& EndDate,
																 MessageEnvelopeList *&pMessageEnvelopeList, 
																 const BFDataGroupId& idDataGroup,
																 bool bCreate /*= true*/,
																 const DString& dstrTrack /*= I_("N")*/,
																 const DString& dstrPageName /*= NULL_STRING*/) 
														
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMessageEnvelopeList" ) );
   DString dstrkey = I_("MessageEnvelopeList");

	DString dstrNetworkID(NetworkID), dstrFileName(FileName),  dstrStartDate(StartDate), dstrEndDate(EndDate);
	dstrNetworkID.strip().upperCase();
	dstrFileName.stripAll().upperCase();
	dstrStartDate.strip();
	dstrEndDate.strip();
	dstrkey +=I_(",") + dstrNetworkID + I_(",") + dstrFileName + I_(",") + dstrStartDate + I_(",") + dstrEndDate;

   BFObjectKey objKey(dstrkey, BF::HOST, OBJ_ACTIVITY_NONE, OBJ_TYPE_MSG_ENVELOPE_LIST );
   MessageEnvelopeList *_pMessageEnvelopeList = dynamic_cast<MessageEnvelopeList*>( findObject( objKey ) );

   if( !_pMessageEnvelopeList && bCreate )
   {
      _pMessageEnvelopeList = new MessageEnvelopeList( *this );

	  if( _pMessageEnvelopeList->init( NetworkID, FileName, StartDate, EndDate ) > WARNING )
      {
         delete _pMessageEnvelopeList;
         _pMessageEnvelopeList = NULL;
      }
      else
      {
         setObject( objKey, _pMessageEnvelopeList );
      }
   }
   pMessageEnvelopeList = _pMessageEnvelopeList;
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY DSTCWorkSession::getFileSearchCriteria( FileSearchCriteria *&pFileSearchCriteria, 
																 const BFDataGroupId& idDataGroup,
																 bool bCreate /*= true*/,
																 const DString& dstrTrack /*= I_("N")*/,
																 const DString& dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getFileSearchCriteria" ) );

	DString dstrkey = I_("FileSearchCriteria");
   BFObjectKey objKey(dstrkey, BF::HOST, OBJ_ACTIVITY_NONE, OBJ_TYPE_FILE_SEARCH );
   FileSearchCriteria *_pFileSearchCriteria = dynamic_cast<FileSearchCriteria*>( findObject( objKey ) );

   if( !_pFileSearchCriteria && bCreate )
   {
      _pFileSearchCriteria = new FileSearchCriteria( *this );

	  if( _pFileSearchCriteria->init( idDataGroup, dstrTrack, dstrPageName ) > WARNING )
      {
         delete _pFileSearchCriteria;
         _pFileSearchCriteria = NULL;
      }
      else
      {
         setObject( objKey, _pFileSearchCriteria );
      }
   }
   pFileSearchCriteria = _pFileSearchCriteria;
   return GETCURRENTHIGHESTSEVERITY();

}

//******************************************************************************
SEVERITY DSTCWorkSession::getOPCConfirmReprint( const DString &dstrTransId,
			  								    const DString &dstrAccountNum,
											    OPCConfirmReprint *&pOPCConfirmReprint, 
											    const BFDataGroupId& idDataGroup,
											    const DString& dstrTrack ,
											    const DString& dstrPageName )										 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getOPCConfirmReprint" ) );   

   pOPCConfirmReprint = NULL;
   bool bError = false;
   
   pOPCConfirmReprint = new OPCConfirmReprint( *this );
   BF_OBJ_ACTIVITY objActivity = OBJ_ACTIVITY_NONE;
      
   if ( pOPCConfirmReprint->init( dstrTransId, dstrAccountNum, idDataGroup ) > WARNING )
   {
		int count = CONDITIONCOUNT();
		Condition *c = NULL;
		for (int i = 0; i < count; i++)
		{
			c = GETCONDITION( i );
			int condCode = c->getCode();
			CLEARCONDITION( i );			
		}				
			
		if ( pOPCConfirmReprint->initNew( dstrTransId, dstrAccountNum, idDataGroup ) > WARNING )
		{
			bError = true;
		}					
   }		
   
   if ( NULL != pOPCConfirmReprint &&
        false == bError )
   {	    
	    BFObjectKey objKey( I_( "OPCConfirmReprint" ), idDataGroup, objActivity, OBJ_TYPE_CONFIRM_REPRINT  );	
		setObject( objKey, pOPCConfirmReprint );
   }
   else
   {   
         delete pOPCConfirmReprint;
         pOPCConfirmReprint = NULL;
   } 
   
   return GETCURRENTHIGHESTSEVERITY();

}
//******************************************************************************

SEVERITY DSTCWorkSession::deleteOPCConfirmReprint()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "deleteOPCConfirmReprint" ) );   

   BFAbstractCBO *pOPCConfirmReprint = getObject( I_( "OPCConfirmReprint" ), BF::HOST, OBJ_TYPE_CONFIRM_REPRINT );
   if( pOPCConfirmReprint )
   {
	   deleteObject( I_( "OPCConfirmReprint" ), BF::HOST, true, true );
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY DSTCWorkSession::getTransHistDilutionAllocList( const DString &dstrTransId,
                                                         DilutionAllocList *&pDilutionAllocList, 
                                                         const BFDataGroupId& idDataGroup,
                                                         const DString &dstrTradeDate,
                                                         const DString &dstrSettleDate,
                                                         const DString &dstrTransNum,
                                                         const DString& dstrTrack,
                                                         const DString& dstrPageName )										 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getTransHistDilutionAllocList" ) );   

   pDilutionAllocList = NULL;
   DString dstrkey = I_("TransHistDilutionAllocList") + dstrTransId;
   BFObjectKey objKey( dstrkey, idDataGroup, OBJ_ACTIVITY_NONE, OBJ_TYPE_TRANS_HIST_DILUTION_ALLOC_LIST );
   pDilutionAllocList = dynamic_cast<DilutionAllocList*>( findObject( objKey ) );

   if( NULL == pDilutionAllocList )
   {
      pDilutionAllocList = new DilutionAllocList( *this );
	  
	  if( pDilutionAllocList->init( dstrTransId, idDataGroup, dstrTradeDate, dstrSettleDate, dstrTransNum ) > WARNING )
      {
         delete pDilutionAllocList;
         pDilutionAllocList = NULL;
      }
      else
      {
         setObject( objKey, pDilutionAllocList );
      }	  
   }    

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY DSTCWorkSession::getCloneAccount ( const DString &accountNum,
                                            CloneAccount *&pCloneAccount, 
                                            const BFDataGroupId &idDataGroup, 
                                            bool bCreate)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_( "getCloneAccount"));

   DString dstrkey = I_("CloneAccount_AccountNum=") + accountNum;
   BFObjectKey objKey (dstrkey, idDataGroup, OBJ_ACTIVITY_ADDED, OBJ_TYPE_CLONE_ACCOUNT);

   CloneAccount *_pCloneAccount = dynamic_cast <CloneAccount *> (findObject (objKey));

   if (!_pCloneAccount && bCreate)
   {
      _pCloneAccount = new CloneAccount (*this);
	  if (_pCloneAccount->init (accountNum, idDataGroup) > WARNING)
      {
         delete _pCloneAccount;
         _pCloneAccount = NULL;
      }
      else
      {
         setObject (objKey, _pCloneAccount);
      }
   }
   pCloneAccount = _pCloneAccount;
   return GETCURRENTHIGHESTSEVERITY ();
}


//******************************************************************************
void DSTCWorkSession::filterHostCondition(long condition)
{
   _hostConditionFilter.insert(condition);
}

//******************************************************************************
void DSTCWorkSession::clearHostConditionFilter()
{
   _hostConditionFilter.clear();
}

//******************************************************************************
DSTCWorkSession::HostConditionMap::HostConditionMap(const long hostConditionArray[][2])
{
   for( int index=0; hostConditionArray[index][0] != -1; index++ )
      addCondition(hostConditionArray[index][1], hostConditionArray[index][0]);
}


//******************************************************************************
long 
DSTCWorkSession::HostConditionMap::getCondition(long hostErrorCode) const
{
   const_iterator iter = find(hostErrorCode);

   if( end() == iter )
   {
      assert(0);
      return(CND::ERR_CBO_WARNING_NOT_DEFINED);
   }

   return(*iter).second;
}

//******************************************************************************
void 
DSTCWorkSession::HostConditionMap::addCondition(long hostErrorCode, long condition)
{
   const value_type value(hostErrorCode, condition);
   std::pair<iterator, bool> result = insert(value);

   assert ( result.second );

}

//******************************************************************************
bool 
DSTCWorkSession::HostConditionFilter::contains(long condition)
{
   return( end() != find(condition) );
}

//******************************************************************************
SEVERITY DSTCWorkSession::addWarningForUpdateView( const DString &dstrWarnCode, const DString &dstrWarnParam )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "addWarningForUpdateView" ) );

	if ( I_( "0" ) != dstrWarnCode )
	{
		long lConditionCode  = _hostConditions.getCondition( dstrWarnCode.asInteger() ); 
		if( !_hostConditionFilter.contains( lConditionCode ) )
		{
			DString dstrIDIParam;
			int iWarnCode = dstrWarnCode.asInteger ();
			switch( iWarnCode )
			{
				case 468:
				{
					DString idiStr;
					addIDITagValue (idiStr, I_( "CONTRACTAGE" ), dstrWarnParam );
					ADDCONDITIONFROMFILEIDI( CND::WARN_PURCHASE_ANNUITANT_OLDER_THAN_LATEST_AGE, idiStr );										
					break;
				}
				case 469:
				{
					DString idiStr, warnParam;
					addIDITagValue (idiStr, I_( "PARAM" ), dstrWarnParam );
					ADDCONDITIONFROMFILEIDI (CND::WARN_FUND_CLASS_NOT_AVAILABLE_FOR_PURCHASE, idiStr);
					break;
				}
				default:
				{
                    ADDCONDITIONFROMFILE ( lConditionCode );
					break;
				}	
			}
		}
	}

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY DSTCWorkSession::checkPersistentViewWarnings( BFData *persistStopResponse )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "checkPersistentViewWarnings" ) );

	if ( persistStopResponse->exists( ifds::UpdateStatus ) ) 
	{
		DString dstrUpdateStatus; 
		dstrUpdateStatus = persistStopResponse->getElementValue( ifds::UpdateStatus );
								   
		if ( I_( "Y" ) == dstrUpdateStatus )
		{				 
			 if ( persistStopResponse->exists( ifds::WarnCode1 ) )
			 {					                         
			    DString dstrWarnCode  = persistStopResponse->getElementValue( ifds::WarnCode1 );
				addWarningForUpdateView( dstrWarnCode, I_( "" ) ); 		
			 }
			 if ( persistStopResponse->exists( ifds::WarnCode2 ) )
			 {
			    DString dstrWarnCode  = persistStopResponse->getElementValue( ifds::WarnCode2 );
				addWarningForUpdateView( dstrWarnCode,I_( "" ) ); 
			 }
			 if ( persistStopResponse->exists( ifds::WarnCode3 ) )
			 {
			    DString dstrWarnCode  = persistStopResponse->getElementValue( ifds::WarnCode3 );
				addWarningForUpdateView( dstrWarnCode, I_( "" ) ); 
			 }
			 if ( persistStopResponse->exists( ifds::WarnCode4 ) )
			 {
			    DString dstrWarnCode  = persistStopResponse->getElementValue( ifds::WarnCode4 );
				addWarningForUpdateView( dstrWarnCode, I_( "" ) ); 
			 } 
			 if ( persistStopResponse->exists( ifds::WarnCode5 ) )
			 {
			    DString dstrWarnCode  = persistStopResponse->getElementValue( ifds::WarnCode5 );
				addWarningForUpdateView( dstrWarnCode,I_( "" ) ); 
			 }						
		}
	}

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY DSTCWorkSession::saveCommitParams (BFData &request, const BFFieldId &idField)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::IFASTCBO_CONDITION, CLASSNAME, I_("saveCommitParams"));
   
   if (m_commitParams)
   {
      if (request.exists (idField))
      {
         DString idFieldValue;

         idFieldValue = m_commitParams->getElementValue (idField);
         idFieldValue.stripAll ();
         request.setElementValue (idField, idFieldValue);
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY DSTCWorkSession::getSavingsDirective( const DString &dstrTransId,
			  												const DString &dstrAccountNum,
															const DString &dstrFund,
															const DString &dstrClass,
															const DString &dstrTradeDate,
															const DString &dstrTISType,
															const DString &dstrTIS,
															const DString &dstrCostType,
															const DString &dstrCost,
															const DString &dstrVersion,
															SavingsDirective *&pSavingsDirective,
															const BFDataGroupId& idDataGroup,
															const DString& dstrTrack ,
															const DString& dstrPageName )										 
{

   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getSavingsDirective" ) );   

   DString dstrkey = I_("AccountNum=") + dstrAccountNum 
							+ I_(";TransID=" ) + dstrTransId;

   BFObjectKey objKey(dstrkey , idDataGroup, OBJ_ACTIVITY_NONE, OBJ_TYPE_SAVINGS_DIRECTIVE );

   SavingsDirective * _pSavingsDirective = dynamic_cast<SavingsDirective*>( findObject( objKey ) );

   if( !_pSavingsDirective  )
   {
      _pSavingsDirective = new SavingsDirective( *this );
      //do a database inquiry

	  if( _pSavingsDirective->init(	dstrTransId,
												dstrAccountNum, 
												dstrFund,
												dstrClass,
												dstrTradeDate,
												dstrTISType,
												dstrTIS,
												dstrCostType,
												dstrCost,
												dstrVersion,
												idDataGroup ) > WARNING )
      {
         delete _pSavingsDirective;
         _pSavingsDirective = NULL;
      }
      else
      {
         setObject( objKey, _pSavingsDirective );
      }
   }

   pSavingsDirective = _pSavingsDirective;
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************

SEVERITY DSTCWorkSession::getResidency( Residency*& pResidency, const DString& dstrTaxType, const DString& dstrJurisd, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getResidency" ) );

   pResidency = NULL;
   DString strTaxType = dstrTaxType;
   DString strJurisd = dstrJurisd;


   if( strTaxType.strip().empty() || strJurisd.strip().empty() )
   {
      return(GETCURRENTHIGHESTSEVERITY());
   }

   DString strKey = I_("Residency") + strTaxType.upperCase() + I_("_") + strJurisd.upperCase();
   pResidency = dynamic_cast <Residency*> (getObject (strKey, idDataGroup));
   if (!pResidency)
   {                        
      pResidency = new Residency (*this);
      if ( pResidency->init (strTaxType, strJurisd) <= WARNING )
      {
         setObject ( pResidency, 
                     strKey, 
                     OBJ_ACTIVITY_NONE, 
                     idDataGroup);
      }
      else
      {
         delete pResidency;
         pResidency = NULL;
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY DSTCWorkSession::getResidencyForShareholder( Residency*& pResidency, const DString& dstrShrNum, 
	                                                  const DString& dstrJurisd, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getResidencyForShareholder" ) );

   pResidency = NULL;
   DString strShrNum = dstrShrNum;
   DString strJurisd = dstrJurisd;


   if( strShrNum.strip().empty() || strJurisd.strip().empty() )
   {
      return(GETCURRENTHIGHESTSEVERITY());
   }

   DString strKey = I_("ResidencyShr") + dstrShrNum + I_("_") + strJurisd.upperCase();
   pResidency = dynamic_cast <Residency*> (getObject (strKey, idDataGroup));
   if (!pResidency)
   {                        
      pResidency = new Residency (*this);
      if ( pResidency->initForShr (dstrShrNum, strJurisd) <= WARNING )
      {
         setObject ( pResidency, 
                     strKey, 
                     OBJ_ACTIVITY_NONE, 
                     idDataGroup);
      }
      else
      {
         delete pResidency;
         pResidency = NULL;
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY DSTCWorkSession::getResidency( Residency*& pResidency, const DString& dstrAccountNum, 
	                      const DString& dstrAsOfDate, const DString& dstrDepositType, 
						  const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getResidency" ) );

   pResidency = NULL;
   DString strAccountNum = dstrAccountNum;
   DString strAsOfDate = dstrAsOfDate;
   DString strDepositType = dstrDepositType;


   if( strAccountNum.strip().empty() || strAccountNum == I_("0") ||
	   strAsOfDate.strip().empty() || strDepositType.strip().empty() )
   {
      return(GETCURRENTHIGHESTSEVERITY());
   }

   DString strKey = I_("Residency") + strAccountNum + I_("_") + strAsOfDate + I_("_") + strDepositType;
   pResidency = dynamic_cast <Residency*> (getObject (strKey, idDataGroup));
   if (!pResidency)
   {                        
      pResidency = new Residency (*this);
      if ( pResidency->init (strAccountNum, dstrAsOfDate, dstrDepositType) <= WARNING )
      {
         setObject ( pResidency, 
                     strKey, 
                     OBJ_ACTIVITY_NONE, 
                     idDataGroup);
      }
      else
      {
         delete pResidency;
         pResidency = NULL;
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool DSTCWorkSession::isNonRegLike( const DString& dstrTaxType )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "isNonRegLike" ) );

   bool bRetVal = false;
   DString strTaxType = dstrTaxType;
   DString strTaxTypeList = NULL_STRING;

   /*the following code can be usedfor NonRegLike if view 149 fails - instead of reading NonregLike field
   strTaxTypeList = I_("0,V");
   */

   MgmtCoOptions *pMgmtCoOptions = NULL;
   if( getMgmtCo().getMgmtCoOptions( pMgmtCoOptions ) <= WARNING && pMgmtCoOptions )
   {
      pMgmtCoOptions->getField( ifds::NonregLike, strTaxTypeList, BF::HOST, false );
   }

   if( DSTCommonFunctions::codeInList( strTaxType.strip().upperCase(), strTaxTypeList ) )
   { 
	   bRetVal = true;
   }

   return bRetVal;
}

//******************************************************************************
bool DSTCWorkSession::isLIFLike( const DString& dstrTaxType )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "isLIFLike" ) );

   bool bRetVal = false;
   DString strTaxType = dstrTaxType;
   DString strTaxTypeList = NULL_STRING;

   // B, BR
   MgmtCoOptions *pMgmtCoOptions = NULL;
   if( getMgmtCo().getMgmtCoOptions( pMgmtCoOptions ) <= WARNING && pMgmtCoOptions )
   {
      pMgmtCoOptions->getField( ifds::LIFLike, strTaxTypeList, BF::HOST, false );
   }

   bRetVal = DSTCommonFunctions::codeInList( strTaxType.strip().upperCase(), strTaxTypeList );

   return bRetVal;
}

//******************************************************************************
bool DSTCWorkSession::isLIRALike( const DString& dstrTaxType )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "isLIRALike" ) );

   bool bRetVal = false;
   DString strTaxType = dstrTaxType;
   DString strTaxTypeList = NULL_STRING;

   // C, CR, U
   MgmtCoOptions *pMgmtCoOptions = NULL;
   if( getMgmtCo().getMgmtCoOptions( pMgmtCoOptions ) <= WARNING && pMgmtCoOptions )
   {
      pMgmtCoOptions->getField( ifds::IntLIRAPlan, strTaxTypeList, BF::HOST, false );
   }

   bRetVal = DSTCommonFunctions::codeInList( strTaxType.strip().upperCase(), strTaxTypeList );

   return bRetVal;
}

//******************************************************************************
bool DSTCWorkSession::isIntRIFPlan( const DString& dstrTaxType )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "isIntRIFPlan" ) );

   bool bRetVal = false;
   DString strTaxType = dstrTaxType;
   DString strTaxTypeList = NULL_STRING;

   // 2, B, BR, L, R
   MgmtCoOptions *pMgmtCoOptions = NULL;
   if( getMgmtCo().getMgmtCoOptions( pMgmtCoOptions ) <= WARNING && pMgmtCoOptions )
   {
      pMgmtCoOptions->getField( ifds::IntRIFPlan, strTaxTypeList, BF::HOST, false );
   }

   bRetVal = DSTCommonFunctions::codeInList( strTaxType.strip().upperCase(), strTaxTypeList );

   return bRetVal;
}

//******************************************************************************
void DSTCWorkSession::getVerificationCategoryList(DString& dstrVerificationCategoryList)
{
   dstrVerificationCategoryList = NULL_STRING;
   // static data verification
   SystemVerificationDetailsList* pSystemVerificationDetailsList = NULL;
   if ( getMgmtCo().getSystemVerificationDetailsList( pSystemVerificationDetailsList ) <= WARNING && 
         NULL != pSystemVerificationDetailsList )
   {
      BFObjIter iter( *pSystemVerificationDetailsList, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED );
      while( !iter.end() )
      {
         SystemVerificationDetails* pSystemVerificationDetails = NULL;

         pSystemVerificationDetails = 
            dynamic_cast<SystemVerificationDetails*>(iter.getObject());
         if( pSystemVerificationDetails )
         {
            DString strVerifyCategory;
            pSystemVerificationDetails->getField( ifds::VerifyCategory, strVerifyCategory, BF::HOST, false );
            if ( !DSTCommonFunctions::codeInList (strVerifyCategory, dstrVerificationCategoryList) )
            {
               dstrVerificationCategoryList = dstrVerificationCategoryList + strVerifyCategory;
               dstrVerificationCategoryList = dstrVerificationCategoryList + I_(",");
            }
         }
         ++iter;
      }

      // trim the last comma
      dstrVerificationCategoryList = dstrVerificationCategoryList.left( dstrVerificationCategoryList.size() - 1 );
   }
   else
   {
      dstrVerificationCategoryList = NULL_STRING;
   }
}

//******************************************************************************
SEVERITY DSTCWorkSession::getAcctGrpConfigList(AcctGrpConfigList *&pAcctGrpConfigList,
                                               const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getAcctGrpConfigList" ) );

   DString dstrKey = I_("AcctGrpConfig");

   pAcctGrpConfigList = dynamic_cast <AcctGrpConfigList*>(getObject(dstrKey, idDataGroup));

   if( !pAcctGrpConfigList )
   {
      pAcctGrpConfigList = new AcctGrpConfigList( *this );

      pAcctGrpConfigList->init();

      if( pAcctGrpConfigList )
      {
         if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
         {
            setObject( pAcctGrpConfigList, dstrKey, OBJ_ACTIVITY_NONE, idDataGroup );
         }
         else
         {
            delete pAcctGrpConfigList;
            pAcctGrpConfigList = NULL;
         }
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool DSTCWorkSession::isQESIClient( const BFDataGroupId& idDataGroup )
{
   bool bIsQESIClient = false;

   DString strMarket = DSTCommonFunctions::getMarket();
   DString strCanMarket = MARKET_IDS::CANADA;
   DString strMarketCapLetter = strMarket;
   strMarketCapLetter.strip().upperCase();
   strCanMarket.strip().upperCase();

   DString strQESIClient;
   getOption( ifds::QESIClient, strQESIClient, idDataGroup, false );
   strQESIClient.strip().upperCase();

   if (isRESPTransformationClient(idDataGroup))
   {
	   RESPRegMstrList *pRESPRegMstrList = NULL;
	   getRESPRegMstrList(pRESPRegMstrList, idDataGroup); 

	   bool bIsQESIBasicClient = false, bIsQESIIncreaseClient = false;
	   bIsQESIBasicClient = pRESPRegMstrList->isGrantTypeActive( NULL_STRING, I_("QESIB"), idDataGroup );
	   bIsQESIIncreaseClient = pRESPRegMstrList->isGrantTypeActive( NULL_STRING, I_("QESII"), idDataGroup );

	   bIsQESIClient = 	bIsQESIBasicClient && bIsQESIIncreaseClient;
   }
   else
   {
	   bIsQESIClient = strQESIClient == I_("Y") && strMarketCapLetter == strCanMarket;
   }

   return bIsQESIClient;
}

//******************************************************************************
bool DSTCWorkSession::isRES2Client( const BFDataGroupId& idDataGroup )
{
   bool bIsRes2Client = false;

   DString strMarket = DSTCommonFunctions::getMarket();
   DString strCanMarket = MARKET_IDS::CANADA;
   DString strMarketCapLetter = strMarket;
   strMarketCapLetter.strip().upperCase();
   strCanMarket.strip().upperCase();

   DString strRes2Client;
   getOption( ifds::RES2Client, strRes2Client, idDataGroup, false );
   strRes2Client.strip().upperCase();

   bIsRes2Client = strRes2Client == I_("Y") && strMarketCapLetter == strCanMarket;

   return bIsRes2Client;
}

//******************************************************************************
SEVERITY DSTCWorkSession::getNEQList ( DString &dstrNEQList, 
									            const DString dstrWhereUse, 
									            const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getNEQList"));

	NEQDetailsList* pNEQDetailsList = NULL;

	if (getMgmtCo().getNEQDetailsList( pNEQDetailsList ) <= WARNING && pNEQDetailsList != NULL)
	{
		pNEQDetailsList->getNEQList (dstrNEQList,dstrWhereUse, idDataGroup);
	}
   
	return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************

SEVERITY DSTCWorkSession::getNEQId (DString &dstrNEQId, 
									const DString dstrWhereUse, 
									const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getNEQId"));

	NEQDetailsList* pNEQDetailsList = NULL;

	if (getMgmtCo().getNEQDetailsList( pNEQDetailsList ) <= WARNING && pNEQDetailsList != NULL)
	{
		pNEQDetailsList->getNEQId (dstrNEQId,dstrWhereUse, idDataGroup);
	}
   
	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool DSTCWorkSession::isGuarGuardAllowed (const DString& dstrAccountNum,
                                          const BFDataGroupId &idDataGroup)
{
   TRACE_METHOD (CLASSNAME, I_ ("isGuarGuardAllowed"));

   DString strSegClient, strCotClient, strGuaranteeGuardOn;

   getOption (ifds::SegClient, strSegClient, BF::HOST, false);
   getOption (ifds::CotClient, strCotClient, BF::HOST, false);
   getOption (ifds::GuaranteeGuardOn, strGuaranteeGuardOn, BF::HOST, false);
   strSegClient.strip().upperCase();
   strCotClient.strip().upperCase();
   strGuaranteeGuardOn.strip().upperCase();

   bool bIsAllowed = false;

   // checking Guarantee Guard control on, view149 and 
   // SegClient and CotClient view-83
   if (strSegClient == I_("Y") && strCotClient == I_("Y") && strGuaranteeGuardOn == I_("Y") )
   {
      MFAccount *pMFAccount = NULL;
      if( getMFAccount (idDataGroup, dstrAccountNum, pMFAccount) <= WARNING &&
          pMFAccount )
      {
         DString strShrNum;
         Shareholder *pShareholder = NULL ;
         pMFAccount->getField( ifds::ShrNum, strShrNum, idDataGroup,false );

         if( getShareholder ( idDataGroup, strShrNum, pShareholder, false ) <= WARNING &&
             pShareholder )
         {
            // get Account shareholder object
            DString dstrGroupCode;
            pShareholder->getField( ifds::GroupCode, dstrGroupCode, idDataGroup, false);
            dstrGroupCode.strip().upperCase();

            // check with HasGWOContract from view 88
            GroupList* pGroupList;
            if( getMgmtCo().getGroupList( pGroupList ) <= WARNING && pGroupList )
            {
               BFObjIter glIter( *pGroupList, idDataGroup );
               if( glIter.positionByKey( dstrGroupCode ) )
               {
                  Group* pGroup;
                  pGroup = dynamic_cast<Group*>( glIter.getObject() );

                  if( pGroup )
                  {
                     DString dstrHasGWOContract;
                     pGroup->getField(ifds::HasGWOContract, dstrHasGWOContract, idDataGroup, false);
                     dstrHasGWOContract.strip().upperCase();

                     if(dstrHasGWOContract == I_("Y")) 
                        bIsAllowed = true;
                  }
               }
            }
         }
      }
   }

   return bIsAllowed;
}

//******************************************************************************
bool DSTCWorkSession::isHistTxfr( const BFDataGroupId& idDataGroup )
{
   bool bIsHistTxfr(false);

   DString strIsHistTxfr(NULL_STRING);
   getOption( ifds::IsNonTrustee, strIsHistTxfr, idDataGroup, false );
   strIsHistTxfr.strip().upperCase();

   bIsHistTxfr = strIsHistTxfr == I_("Y");

   return bIsHistTxfr;
}

//******************************************************************************
bool DSTCWorkSession::isIWTClient( const BFDataGroupId& idDataGroup )
{
   DString strIWTClient;
   getOption( ifds::IWTEnable, strIWTClient, idDataGroup, false );
   strIWTClient.strip().upperCase(); 

   return strIWTClient == I_("Y");
}

//******************************************************************************
bool DSTCWorkSession::getLastNameFormat()
{
   MgmtCoOptions *pMgmtCoOptions = NULL; 
   DString dstrLastNameFormat (NULL_STRING);

   if (getMgmtCo().getMgmtCoOptions (pMgmtCoOptions) <= WARNING && pMgmtCoOptions)
   {
      pMgmtCoOptions->getField (ifds::LastNameFormat, dstrLastNameFormat, BF::HOST, false); 
	  dstrLastNameFormat.upperCase();
      return (dstrLastNameFormat == I_("DOUBLE")) ? true : false;
   }
   return false;
}

//******************************************************************************
SEVERITY DSTCWorkSession::getFamilyCodeList( FamilyCodeList*& pFamilyCodeList,
                                             const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getFamilyCodeList"));

   pFamilyCodeList = NULL;
   DString strKey = I_("FamilyCodeList");
   FamilyCodeList* pLocalFamilyCodeList = dynamic_cast <FamilyCodeList*> (getObject (strKey, idDataGroup));
   if (!pLocalFamilyCodeList)
   {                        
      pLocalFamilyCodeList = new FamilyCodeList(*this);
      
      if( pLocalFamilyCodeList->init(NULL_STRING, NULL_STRING, I_("N"), idDataGroup) <= WARNING )
      {
         setObject ( pLocalFamilyCodeList, 
                     strKey, 
                     OBJ_ACTIVITY_NONE, 
                     idDataGroup);
      }
      else
      {
         delete pLocalFamilyCodeList;
         pLocalFamilyCodeList = NULL;
      }
   }
   else
   {
      const FamilyCodeList* pCachedFamilyCodeList = const_cast<FamilyCodeList*>(pLocalFamilyCodeList);
      
      if(pCachedFamilyCodeList)
      {
         bool bRequiredRefresh = pCachedFamilyCodeList->needsRefresh(idDataGroup);
         
         if(bRequiredRefresh)
         {
            setObject ( NULL, 
                        strKey, 
                        OBJ_ACTIVITY_NONE, 
                        idDataGroup);
                        
            pLocalFamilyCodeList = new FamilyCodeList(*this);
            
            if( pLocalFamilyCodeList->init(NULL_STRING, NULL_STRING, I_("N"), idDataGroup) <= WARNING )
            {
               setObject ( pLocalFamilyCodeList, 
                           strKey, 
                           OBJ_ACTIVITY_NONE, 
                           idDataGroup);
            }
            else
            {
               delete pLocalFamilyCodeList;
               pLocalFamilyCodeList = NULL;
            }
         }
      }
   }

   pFamilyCodeList = pLocalFamilyCodeList;

   return GETCURRENTHIGHESTSEVERITY();
}
//**************************************************************************************************************************
bool DSTCWorkSession ::isPerfFeeFund(const DString &fundCode, const DString &classCode,const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("isPerfFeeFund"));

	DString dstrFundSubCat;
	FundDetailList *pFundDetailList = NULL;

	if (getMgmtCo ().getFundDetailList (pFundDetailList) <= WARNING && pFundDetailList)
	{	
		FundDetail *pFundDetail = NULL;
		pFundDetailList->getFundDetail(fundCode, classCode, idDataGroup, pFundDetail);
		
		if( pFundDetail )
		{
			pFundDetail->getField (ifds::FundSubCat, dstrFundSubCat, BF::HOST, false);
			dstrFundSubCat.strip ();
		}
	}
	return (dstrFundSubCat == I_("08"));
}
//*********************************************************************************************************
bool DSTCWorkSession ::isSrcOfFundRequired(const DString &srcOfFund,const BFDataGroupId& idDataGroup)
{//P0186486_FN15_The Source of Funds
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_("isSrcOfFundRequired"));

   bool ret(false);
   DString sourceOfFundApp, 
           srcOfFunds_IA_Required,
           sourceOfFund (srcOfFund);

   MgmtCoOptions *pMgmtCoOptions = NULL;
   if( getMgmtCo().getMgmtCoOptions( pMgmtCoOptions ) <= WARNING && pMgmtCoOptions )
   {
      pMgmtCoOptions->getField( ifds::SourceOfFundApp, sourceOfFundApp, BF::HOST, false );
      pMgmtCoOptions->getField( ifds::SrcOfFunds_IA_Required, srcOfFunds_IA_Required, BF::HOST, false );
   }
   sourceOfFundApp.strip().upperCase();
   srcOfFunds_IA_Required.strip().upperCase();
   sourceOfFund.strip().upperCase();
   
   if(sourceOfFundApp == I_("Y") && !sourceOfFund.empty() && !srcOfFunds_IA_Required.empty())
   {
         if(DSTCommonFunctions::codeInList (sourceOfFund.strip().upperCase(), srcOfFunds_IA_Required))
         {
            ret = true; 
         }
   }

   return ret;
}

//******************************************************************************
bool DSTCWorkSession::isTaxAnniversaryClient( const BFDataGroupId& idDataGroup )
{
   bool bIsTaxAnniversary = false;

   DString strTaxAnniversaryClient;
   getOption( ifds::TaxAnniversary, strTaxAnniversaryClient, idDataGroup, false );
   strTaxAnniversaryClient.strip().upperCase();

   bIsTaxAnniversary = strTaxAnniversaryClient == I_("Y");

   return bIsTaxAnniversary;
}
//******************************************************************************
SEVERITY DSTCWorkSession::getFATCAMasterList(FATCAMasterList *&pFATCAMasterList,   
										     const BFDataGroupId &idDataGroup /* BF::HOST */)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getFATCAMasterList")); 

	DString dstrKey = I_("FATCAMasterList");
	pFATCAMasterList = dynamic_cast <FATCAMasterList*>(getObject(dstrKey, idDataGroup));

	if( !pFATCAMasterList )
	{
		pFATCAMasterList = new FATCAMasterList( *this );

			pFATCAMasterList->init();

		if( pFATCAMasterList )
		{
			if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
			{				
				setObject( pFATCAMasterList, dstrKey, OBJ_ACTIVITY_NONE, idDataGroup );
			}
			else
			{
				delete pFATCAMasterList;
				pFATCAMasterList = NULL;
			}
		}
	}

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool DSTCWorkSession::isSAGESClient( const BFDataGroupId& idDataGroup )
{
   bool bIsSAGESClient = false;

   DString strMarket = DSTCommonFunctions::getMarket();
   DString strCanMarket = MARKET_IDS::CANADA;
   DString strMarketCapLetter = strMarket;
   strMarketCapLetter.strip().upperCase();
   strCanMarket.strip().upperCase();

   DString strSAGESActive;
   getOption( ifds::SAGESActive, strSAGESActive, idDataGroup, false );
   strSAGESActive.strip().upperCase();

   if (isRESPTransformationClient(idDataGroup))
   {
	   RESPRegMstrList *pRESPRegMstrList = NULL;
	   getRESPRegMstrList(pRESPRegMstrList, idDataGroup); 

	   bIsSAGESClient = pRESPRegMstrList->isGrantTypeActive( NULL_STRING, I_("SAGES"), idDataGroup );
   }
   else
   {
	   bIsSAGESClient = strSAGESActive == I_("YES") && strMarketCapLetter == strCanMarket;
   }

   return bIsSAGESClient;
}

SEVERITY DSTCWorkSession::getTransactionList(TransactionList *&pTransactionList,
						       const DString& transNum,
							   const BFDataGroupId &idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE(CLASSNAME, I_("getTransactoinList"));

	DString dstrTransNum = transNum;
	if(dstrTransNum.stripLeading(I_('0')).stripAll().empty()) 
	{
		pTransactionList = NULL;
		return GETHIGHESTSEVERITY();
	}

	DString dstrkey = I_("TransNum=") + transNum;
	BFObjectKey objKey(dstrkey , idDataGroup, OBJ_ACTIVITY_NONE, OBJ_TYPE_TRANSACTION_DETAILS);

	pTransactionList = dynamic_cast<TransactionList*>(findObject(objKey));
	if(pTransactionList == NULL)
	{
		TradeSearchCriteria *pTradeSearchCriteria = NULL;
		//getTradeSearchCriteria(pTradeSearchCriteria, idDataGroup);
		pTradeSearchCriteria = new TradeSearchCriteria(*this);
		pTradeSearchCriteria->init(idDataGroup);
		pTradeSearchCriteria->setField(ifds::TransNum, transNum, idDataGroup);
		SEVERITY severity = pTradeSearchCriteria->getTransactionList(pTransactionList, idDataGroup);
		if(severity >WARNING)
		{
			pTransactionList = NULL;
		}
		else 
		{
			setObject(objKey, pTransactionList);
		}
	}

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool DSTCWorkSession::isRESPTransformationClient( const BFDataGroupId& idDataGroup )
{
   bool bIsRESPTransformation = false;

   DString strMarket = DSTCommonFunctions::getMarket();
   DString strCanMarket = MARKET_IDS::CANADA;
   DString strMarketCapLetter = strMarket;
   strMarketCapLetter.strip().upperCase();
   strCanMarket.strip().upperCase();

   DString strRESPTransformation;
   getOption( ifds::IsRESPTransform, strRESPTransformation, idDataGroup, false );
   strRESPTransformation.strip().upperCase();

   bIsRESPTransformation = strRESPTransformation == I_("Y") && strMarketCapLetter == strCanMarket;

   return bIsRESPTransformation;
}

//******************************************************************************
SEVERITY DSTCWorkSession::getRESPRegMstrList(RESPRegMstrList *&pRESPRegMstrList, const BFDataGroupId &idDataGroup /* BF::HOST */)
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("RESPRegMstrList")); 

	DString dstrKey = I_("RESPRegMstrList");
	pRESPRegMstrList = dynamic_cast <RESPRegMstrList*>(getObject(dstrKey, idDataGroup));

	if( !pRESPRegMstrList )
	{
		pRESPRegMstrList = new RESPRegMstrList( *this );

		pRESPRegMstrList->init();

		if( pRESPRegMstrList )
		{
			if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
			{				
				setObject( pRESPRegMstrList, dstrKey, OBJ_ACTIVITY_NONE, idDataGroup );
			}
			else
			{
				delete pRESPRegMstrList;
				pRESPRegMstrList = NULL;
			}
		}
	}

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool DSTCWorkSession::isBCTESGClient( const BFDataGroupId& idDataGroup )
{
	bool bIsBCTESGClient = false;

	RESPRegMstrList *pRESPRegMstrList = NULL;
	getRESPRegMstrList(pRESPRegMstrList, idDataGroup); 

	bIsBCTESGClient = pRESPRegMstrList->isGrantTypeActive( NULL_STRING, I_("BCTESG"), idDataGroup );

	return bIsBCTESGClient;
}


//******************************************************************************
bool DSTCWorkSession::isACESClient( const DString &dstrTradeDate, const BFDataGroupId& idDataGroup )
{
	bool bIsACESClient = false;

	RESPRegMstrList *pRESPRegMstrList = NULL;
	getRESPRegMstrList(pRESPRegMstrList, idDataGroup); 

	bIsACESClient = pRESPRegMstrList->isGrantTypeActive( dstrTradeDate, I_("ACES"), idDataGroup );

	return bIsACESClient;
}

//******************************************************************************
bool DSTCWorkSession::isMasterActWithOneChild(const BFDataGroupId& idDataGroup )
{
   bool bReturnValue = false;

   DString strMstrActAttrbName, strMstrActAttrbValue, strIsMasterActWithOneChild;
   getOption( ifds::MstrActAttrbName, strMstrActAttrbName, idDataGroup, false );
   getOption( ifds::MstrActAttrbValue, strMstrActAttrbValue, idDataGroup, false );

   do
   {
      DString::size_type pos = 0;
      DString tmpMstrActAttrbName;

      EXTRACT_VALUE(strMstrActAttrbName, tmpMstrActAttrbName)
      if (tmpMstrActAttrbName == I_("SingleChild")) //found the transaction type
      {
         EXTRACT_VALUE (strMstrActAttrbValue, strIsMasterActWithOneChild)
         strIsMasterActWithOneChild.strip().upperCase();

         bReturnValue = strIsMasterActWithOneChild == I_("Y");
         break;
      }
      else //cut the strings
      {
         CHOP_STRING (strMstrActAttrbName)
         CHOP_STRING (strMstrActAttrbValue)
      }
   }
   while (strMstrActAttrbName != NULL_STRING);

   return bReturnValue;
}

//******************************************************************************
bool DSTCWorkSession::isAMSFundClass(const DString& dstrFundCode, 
                                     const DString& dstrClassCode, 
                                     const BFDataGroupId& idDataGroup)
{
    bool retVal = false;
    FundDetail *pFundDetail = NULL;

    if (getFundDetail(dstrFundCode, dstrClassCode, idDataGroup, pFundDetail) && pFundDetail)
    {
        if (isMasterActWithOneChild(idDataGroup))
        {
            retVal = pFundDetail->isAMSParentFund(idDataGroup) ||
                     pFundDetail->isAMSChildFund(idDataGroup);
        }
        else
        {
            DString dstrAMSFund;
            pFundDetail->getField(ifds::AMSEligible, dstrAMSFund, idDataGroup);

            retVal = dstrAMSFund.stripAll().upperCase() == I_("Y");
        }
    }

    return retVal;
}

//******************************************************************************
SEVERITY DSTCWorkSession::fundClassSoftCappedCheck(const DString &dstrAccountNum, 
                                                   const DString &dstrFundCode, 
                                                   const DString &dstrClassCode, 
                                                   const DString &dstrTransType,
                                                   const DString &dstrEffectiveDate,
                                                   const BFDataGroupId &idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("fundClassSoftCappedCheck")); 

    DString currBusDate, tmpFundCode(dstrFundCode), tmpClassCode(dstrClassCode), tmpTransType(dstrTransType);
    FundDetailList *pFundDetailList = NULL;
    FundDetail *pFundDetail = NULL;

    getOption(ifds::CurrBusDate, currBusDate, idDataGroup, false);
    
    if (!dstrFundCode.empty() && !dstrClassCode.empty() && 
        !dstrAccountNum.empty() && !dstrTransType.empty() && 
        !dstrEffectiveDate.empty() && 
        _currentMgmtCo->getFundDetailList(pFundDetailList) <= WARNING && pFundDetailList &&
        pFundDetailList->getFundDetail(dstrFundCode, dstrClassCode, idDataGroup, pFundDetail) && pFundDetail &&
        pFundDetail->isSoftCapped(dstrEffectiveDate, idDataGroup))
    {
        SoftCappedValidation *pSoftCappedValidation = NULL;

        DString objKey = I_("SoftCappedValidation;") + 
                         dstrAccountNum + I_(";") + 
                         tmpFundCode.upperCase() + I_(";") + 
                         tmpClassCode.upperCase() + I_(";") + 
                         tmpTransType.upperCase() + I_(";") + 
                         dstrEffectiveDate + I_(";");

        pSoftCappedValidation = dynamic_cast <SoftCappedValidation*>(getObject(objKey, idDataGroup));

	    if (!pSoftCappedValidation)
        {
            pSoftCappedValidation = new SoftCappedValidation(*this);

            if (pSoftCappedValidation->init(dstrAccountNum, dstrFundCode, dstrClassCode, dstrTransType, dstrEffectiveDate) <= WARNING &&
                pSoftCappedValidation)
            {
                setObject(pSoftCappedValidation, objKey, OBJ_ACTIVITY_NONE, idDataGroup);
            }
            else 
            {
                delete pSoftCappedValidation;
                pSoftCappedValidation = NULL;
            }
        }

        if (pSoftCappedValidation) 
        {
            pSoftCappedValidation->addConditions();
        }
    }

    return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY DSTCWorkSession::getExternalInstitutionList(ExternalInstitutionList*& pExternalInstitutionList, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getExternalInstitutionList")); 

   DString strKey = I_("ExternalInstitutionList");

   pExternalInstitutionList = nullptr;

   ExternalInstitutionList* _pExternalInstitutionList = dynamic_cast<ExternalInstitutionList*> (BFCBO::getObject (strKey, idDataGroup));

   if( !_pExternalInstitutionList )
   {
      _pExternalInstitutionList = new ExternalInstitutionList(*this);

      if( _pExternalInstitutionList->init(idDataGroup) > WARNING )
      {
         delete _pExternalInstitutionList;
         _pExternalInstitutionList = nullptr;
      }

      if (_pExternalInstitutionList)
      {
         setObject ( _pExternalInstitutionList, strKey, OBJ_ACTIVITY_NONE, idDataGroup);
      }
   }

   pExternalInstitutionList = _pExternalInstitutionList;

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool DSTCWorkSession::multipleRiskEnv()
{
    DString dstrMultipleRisk;
    getOption(ifds::MultipleRisk, dstrMultipleRisk, BF::HOST, false);

    return dstrMultipleRisk == Y;
}
//******************************************************************************
SEVERITY DSTCWorkSession::getRESPRegRuleList( RESPRegRuleList *&pRESPRegRuleList, const BFDataGroupId &idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("getRESPRegRuleList")); 

	DString dstrKey = I_("RESPRegRuleList");
	pRESPRegRuleList = dynamic_cast <RESPRegRuleList*>(getObject(dstrKey, idDataGroup));

	if( !pRESPRegRuleList )
	{
		pRESPRegRuleList = new RESPRegRuleList( *this );

		pRESPRegRuleList->init();

		if( pRESPRegRuleList )
		{
			if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
			{				
				setObject( pRESPRegRuleList, dstrKey, OBJ_ACTIVITY_NONE, idDataGroup );
			}
			else
			{
				delete pRESPRegRuleList;
				pRESPRegRuleList = NULL;
			}
		}
	}

	return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
bool DSTCWorkSession::isNetBalTransfer( const DString& respNotlType, const BFDataGroupId& idDataGroup )
{
	bool bNetBalTransfer = false;

	RESPRegRuleList *pRESPRegRuleList = NULL;
	getRESPRegRuleList(pRESPRegRuleList, idDataGroup); 
	
	bNetBalTransfer = pRESPRegRuleList->isNetBalTransferRule( I_("TRANSFERSPLIT"), respNotlType, idDataGroup );

	return bNetBalTransfer;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCWorkSession.cpp-arc  $
// 
//    Rev 1.227   May 14 2012 10:12:56   kitticha
// P0186477 FN06 - T5 Processing.
// 
//    Rev 1.226   May 04 2012 10:55:50   panatcha
// P0186486_FN15_The Source of Funds
// 
//    Rev 1.225   Apr 20 2012 03:30:02   panatcha
// P0186486_FN15_The Source of Funds
// 
//    Rev 1.224   Apr 03 2012 21:40:16   wp040039
// PETP0187485-Registartion Agent  Banking
// 
//    Rev 1.223   Feb 22 2012 17:01:14   if991250
// Account Commitment
// 
//    Rev 1.222   Feb 21 2012 15:44:30   wp040100
// P0186484 FN05 - Contract Maturity Instruction Changes
// 
//    Rev 1.221   Jan 26 2012 10:54:06   wp040027
// P0188394_Performance Fees - Benchmark Upload (Modifying Search Functionality)
// 
//    Rev 1.220   Jan 16 2012 13:55:02   wp040027
// P0188394_Performance Fees - Benchmark Upload
// 
//    Rev 1.219   Dec 12 2011 11:57:46   wp040100
// P0186477/FN03 - GIA - Investment History Changes
// 
//    Rev 1.218   Dec 02 2011 19:15:06   wp040100
// P0186477/FN03 - GIA - Investment History Changes
// 
//    Rev 1.217   Dec 01 2011 19:10:56   wp040100
// P0186477/FN03 - GIA - Investment History Changes
// 
//    Rev 1.216   Nov 27 2011 21:36:02   wp040100
// P0186477/FN03 - GIA - Investment History Changes
// 
//    Rev 1.215   Nov 25 2011 17:40:24   wp040100
// P0186477/FN03 - GIA - Investment History Changes
// 
//    Rev 1.214   Nov 18 2011 18:58:18   wp040100
// P0186477/FN03 - GIA - Investment History Changes
// 
//    Rev 1.213   Nov 18 2011 08:47:22   dchatcha
// P0188902 FN02 - DYN Household Project, refreshing family code list
// 
//    Rev 1.212   Nov 17 2011 15:50:12   wp040100
// P0186477/FN03 - GIA - Investment History Changes
// 
//    Rev 1.211   Nov 11 2011 10:17:04   wp040100
// Added getInvestmentHistoryList method
// 
//    Rev 1.210   Nov 08 2011 12:01:46   dchatcha
// P0188902 FN02 - DYN Household Project
// 
//    Rev 1.209   Oct 21 2011 09:27:16   kitticha
// PETP0188150 FN01 - Irish Withholding Tax Functionality.
// 
//    Rev 1.208   Oct 04 2011 18:17:26   dchatcha
// P0186477 FN01 - GIA Enhancements, display validate portfolio fields based on environment functionality(UAF).
// 
//    Rev 1.207   Jun 29 2011 14:38:04   wutipong
// IN#2556973 Unable to change shareholder group
// 
//    Rev 1.206   Jun 28 2011 10:28:34   panatcha
// P0184541_FN01_InvescoQESItrans
// 
//    Rev 1.205   Jan 20 2011 07:09:04   wichian
// IN#2319580 - Updated code according to code review 579300 w/o
// 
//    Rev 1.203   Sep 19 2010 23:49:54   dchatcha
// Compile error.
// 
//    Rev 1.202   Sep 17 2010 07:49:00   kitticha
// PETP0173756 FN02 Don't Bust the Rules.
// 
//    Rev 1.201   Jul 05 2010 15:34:08   popescu
// Noticed that isQESI method is empty and redundant - took it out
// 
//    Rev 1.200   Apr 30 2010 16:05:20   popescu
// PET165541_FN01_QESI - RESP Gap_Dsk_Trading - synch-up  with 1.196.1.3
// 
//    Rev 1.199   Apr 22 2010 13:17:58   popescu
// PET165541_FN01_QESI - RESP Gap_Dsk_NASU - synch-up 1.198.1.2
// 
//    Rev 1.198   Mar 26 2010 16:11:42   popescu
// PET165541_FN01_QESI - RESP Gap_Dsk_NASU - synch-up
// 
//    Rev 1.197   Jan 29 2010 05:45:10   wichian
// IN1977129 - Refresh button does not work-changed remittance date
// 
//    Rev 1.196   Jan 28 2010 17:04:02   jankovii
// PET165541 FN01 - QESI - RESP Gap.
// 
//    Rev 1.195   Dec 03 2009 02:53:46   dchatcha
// PET0166583 FN02 FN03 - Static Verification Phase 2.
// 
//    Rev 1.194   Nov 24 2009 13:06:24   popescu
// Incident 1924022 - client id should in lower cases for Desktop to pick the overrides from Data Dictionary
// Incident 1923860 - same key should be used for retrieving the batch infor list 
// 
// synch-up
// 
//    Rev 1.193   Nov 17 2009 15:18:24   jankovii
// PET0166583 FN01 Static Data Changes Banking 
// 
//    Rev 1.192   Nov 16 2009 06:44:50   dchatcha
// P0166583 - Static Data Change Phase 2 - FN02-03-04
// 
//    Rev 1.191   May 19 2009 14:13:54   jankovii
// PET 159770 FN05 Auto Batching.
// 
//    Rev 1.190   May 12 2009 13:49:34   jankovii
// PET 159770 FN05 Auto Batching.
// 
//    Rev 1.189   04 Mar 2009 15:53:58   kovacsro
// IN#1608629 - Aimprod RTS error 9
// 
//    Rev 1.188   Mar 02 2009 09:58:16   jankovii
// PET0159508 FN03 ESG In Cash Transfer 
// 
//    Rev 1.187   08 Jan 2009 16:14:42   kovacsro
// sync-up from rev. 1.184.1.0 : IN#1521695 - GL #1541 - Users received an internal problem error msg from Desktop
// 
//    Rev 1.186   Nov 28 2008 13:50:42   jankovii
// PET 142196 FN01 Federal Restricted LIF and LIRA.
// 
//    Rev 1.185   Nov 25 2008 11:16:54   jankovii
// PET 142196 FN01 Federal Restricted LIF and LIRA.
// 
//    Rev 1.184   Nov 12 2008 16:26:52   jankovii
// IN 1482694 - cheque info.
// 
//    Rev 1.183   23 Oct 2008 15:11:26   popescu
// Incident 1154478 - AMS back-date fix
// 
//    Rev 1.182   06 Oct 2008 13:16:48   kovacsro
// PET142007  FN01 TFSA
// 
//    Rev 1.181   Sep 08 2008 16:09:38   jankovii
// PET 5517 FN71 - Stale Cheque.
// 
//    Rev 1.180   Mar 11 2008 20:08:38   daechach
// PET2385FN02&07 - Account Level Settlement Periods and Currency Holiday - Check in for Build.
// 
//    Rev 1.179   15 Nov 2007 17:45:08   popescu
// PET 5636/01 Internal audit tracking
// 
//    Rev 1.178   12 Nov 2007 23:44:14   popescu
// PET 5653/01 - Internal Audit project
// 
//    Rev 1.177   02 Nov 2007 17:01:44   popescu
// Internal Audit Project passed in AWDObjectId to views that have the field
// 
//    Rev 1.176   01 Aug 2007 09:45:36   popescu
// GAP 6 - CIF - also added UpdateAllCIF for vew 85
// 
//    Rev 1.175   18 Jul 2007 16:53:26   popescu
// GAP 6 CIF - AIM
// 
//    Rev 1.174   17 Jul 2007 15:18:58   popescu
// GAP 6 CIF - AIM
// 
//    Rev 1.173   Jul 11 2007 16:21:42   smithdav
// PET 2360 FN02 - AMS - Interim changes
// 
//    Rev 1.172   Mar 12 2007 12:04:04   purdyech
// Merged changes from 1.170.1.0.
// 
//    Rev 1.171   Mar 06 2007 16:02:02   popescu
// Incident# 837216 - Error in Bulk Cancellation
// 
//    Rev 1.170   Nov 14 2006 16:47:30   porteanm
// Incident 676881 - Pass TransType to 338 (TransCancel).
// 
//    Rev 1.169   Nov 08 2006 17:29:06   popescu
// PET 2281/FN 01- copy account for TA 
// 
//    Rev 1.168   Sep 25 2006 13:58:38   porteanm
// Incident 693185 - Warn support for view 161.
// 
//    Rev 1.167   Sep 11 2006 13:54:58   porteanm
// Incident 693185 - Warn support for view 161.
// 
//    Rev 1.166   Jun 29 2006 09:52:00   porteanm
// PET2003 FN03 - Added support for rej-error 491/ACL 719.
// 
//    Rev 1.165   May 24 2006 13:46:42   jankovii
// PET 2102 FN02 - Manulife Flex - Trade/Systematic Entry.
// 
//    Rev 1.164   Mar 28 2006 12:42:48   popescu
// Incident 563764 - TradeDate/SettleDate validation support for a cancelled transaction - fixed params
// 
//    Rev 1.163   Mar 10 2006 13:56:32   porteanm
// Incident 563764 - TradeDate/SettleDate validation support for a cancelled transaction.
// 
//    Rev 1.162   Dec 29 2005 13:10:06   porteanm
// Incident 501804 - Allow multiple Bulk Cancellation Instructions for the same Trade Date/Fund/Class.
// 
//    Rev 1.161   Dec 21 2005 12:24:30   porteanm
// Incident# 494407 - added suport for warning msg 685 - please cancel out money out.
// 
//    Rev 1.160   Dec 16 2005 20:45:50   porteanm
// Incident 421704 - gap - TranshistDilutionAlloc update support.
// 
//    Rev 1.159   Dec 14 2005 09:46:28   porteanm
// Incident 421704 - gap - TranshistDilutionAlloc update support.
// 
//    Rev 1.158   Dec 13 2005 19:31:16   porteanm
// Incident 421704 - gap - TranshistDilutionAlloc update support.
// 
//    Rev 1.157   Nov 29 2005 17:28:20   AGUILAAM
// PET1228_FN02_EUSD Phase 2
// 
//    Rev 1.156   Nov 12 2005 11:54:48   porteanm
// PET 1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.155   Nov 11 2005 16:59:22   ZHANGCEL
// PET 1286 FN01 - Change key in the function getTransCancellist()
// 
//    Rev 1.154   Nov 08 2005 19:18:20   porteanm
// PET 1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.153   Nov 06 2005 15:07:06   porteanm
// PET 1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.152   Nov 04 2005 10:46:16   ZHANGCEL
// PET 1286  FN01 -- Add Cancellation Instruction related issue
// 
//    Rev 1.151   Oct 04 2005 14:55:32   AGUILAAM
// PET1250_FN09: display warning 'not all trades settled' when appropriate
// 
//    Rev 1.150   Sep 29 2005 11:11:10   yingbaol
// PET1277,FN09: Fix issue mailing override transaction.
// 
//    Rev 1.149   Sep 20 2005 12:15:12   AGUILAAM
// PET1250_FN09_Custody Client Accounts and Negative Balances; also fixed Refresh functionality for Settlements.
// 
//    Rev 1.148   Aug 17 2005 11:37:12   popescu
// Incident 377523 - fixed the refresh error 'Dilution Records already exist' after user cancels and rebooks a transaction. Correctly removed the trans cancelation update data at the worksession level.
// 
//    Rev 1.147   Aug 09 2005 10:22:48   porteanm
// Incident 361254 - syncup from 1.144.2.1 - Added checkPersistentViewWarnings() and call it each time when the persistant view is closed in commit().
// 
//    Rev 1.146   Jul 13 2005 17:53:06   popescu
// Incident 352435 - improved performance on the fund sponsor fee model screen - synch-up from release 63.0.0
// 
//    Rev 1.145   Jul 08 2005 09:29:20   Yingbaol
// PET1235,FN01: transaction cancellation rebook
// 
//    Rev 1.144   Jun 20 2005 03:49:40   popescu
// PET 1024/40 - fixed comp warnings
// 
//    Rev 1.143   Jun 16 2005 15:39:10   porteanm
// PET1024 FN40 - Guarantee Adjustments.
// 
//    Rev 1.142   Jun 16 2005 10:58:24   porteanm
// PET1024 FN40 - Guarantee Adjustments.
// 
//    Rev 1.141   May 31 2005 15:58:48   porteanm
// PET OPC Confirm Reprint - Commit and Reset.
// 
//    Rev 1.140   May 27 2005 10:02:44   popescu
// Incident #297240 - backed the fix out
// 
//    Rev 1.139   May 25 2005 15:03:42   porteanm
// PET OPC Confirm Reprint - Commit and Reset.
// 
//    Rev 1.138   May 09 2005 12:26:12   porteanm
// Incident 243414: Restored - close persistant transaction before seding non persistant transaction.
// 
//    Rev 1.137   May 09 2005 12:17:36   porteanm
// Incident 297240 - Added SearchType and AggrOrderNum to key for retrieving Aggr Order List.
// 
//    Rev 1.136   May 09 2005 12:05:14   porteanm
// Incident 292892 - Additional caution when checking persistent response fields.
// 
//    Rev 1.135   May 06 2005 14:20:02   yingbaol
// Incident 243414: close persistant transaction before seding non persistant transaction.
// 
//    Rev 1.134   May 02 2005 08:58:56   hernando
// Incident 297240 - Added SearchType and AggrOrderNum to key for retrieving Aggr Order List.
// 
//    Rev 1.133   Apr 27 2005 17:48:50   porteanm
// Incident 292892 - Fixed crash when persistent view returned error.
// 
//    Rev 1.132   Apr 21 2005 10:23:50   ZHANGCEL
// Incident #292340 -- Added EXEMPTTAG in namespace TRXNTAG
// 
//    Rev 1.131   Apr 12 2005 10:32:58   porteanm
// PET1190 FN14 - Wire order redemption against unsettled units.
// 
//    Rev 1.130   Mar 31 2005 18:06:08   hernando
// Incident #275837 - Added ActivityID to the key for retrieving the Message Detail List.
// 
//    Rev 1.129   Mar 16 2005 15:34:06   Fengyong
// PET1190 FN05 - change view 337 to repeatable
// 
//    Rev 1.128   Mar 08 2005 15:56:24   Fengyong
// PET1190 FN04 - Add transnum to get cancellation function
// 
//    Rev 1.127   Mar 06 2005 15:40:48   yingbaol
// PET1171,FN01: EU Saving add where use transaction builder
// 
//    Rev 1.126   Mar 03 2005 18:52:18   Fengyong
// PET1190 FN05 - Transaction cancellation and dilution
// 
//    Rev 1.125   Feb 28 2005 16:55:46   ZHANGCEL
// PET1117 FN66-68 - Build ObjKey for MessageEnvelopeList
// 
//    Rev 1.124   Feb 25 2005 17:53:50   hernando
// PET1117 FN66-68 - Defined a key in getMsgProcessList.
// 
//    Rev 1.123   Feb 24 2005 17:26:54   ZHANGCEL
// PET1117- FN66-68 - Added getMsgEnvelopeList
// 
//    Rev 1.122   Feb 17 2005 15:59:46   hernando
// PET1117 FN66-68 - Added getMsgProcessList and getMsgDetailList.
// 
//    Rev 1.121   Jan 28 2005 13:45:06   popescu
// PTS 10038381, synch-up from release 59.0.1
// 
//    Rev 1.120   Jan 26 2005 11:01:24   yingbaol
// PET1117 FN67 enhance Aggregate order for API
// 
//    Rev 1.119   Jan 25 2005 10:02:50   popescu
// PTS 10038286, called the method in fund master list to retrieve the fund name, rather then doing 'positionOnNextMatch' since this method requires versionable flag set.
// 
//    Rev 1.118   Dec 09 2004 18:42:48   popescu
// PET 1117/56 fixed trxn builder issue
// 
//    Rev 1.117   Dec 09 2004 18:26:12   Fengyong
// PET1117FN54 - reinit fund brokerlist only when create flag set to on.
// 
//    Rev 1.116   Dec 09 2004 16:54:04   Fengyong
// reinit key for get fundbrokerlist
// 
//    Rev 1.115   Dec 09 2004 14:45:12   zhangcel
// PET1117 FN8 -- Added logic to build AggregatedOrder transaction
// 
//    Rev 1.114   Dec 02 2004 15:06:04   Fengyong
// PET1117 FN54 - Fund Broker static
// 
//    Rev 1.113   Nov 30 2004 16:34:52   hernando
// PET1117 - Tuning Project.  Revised use of FundDetailList.
// 
//    Rev 1.112   Nov 25 2004 12:57:54   Fengyong
// fix getfundbrokerlist fundction
// 
//    Rev 1.111   Nov 23 2004 17:45:18   Fengyong
// PET1117FN54 - adjustment after firstday intergration test
// 
//    Rev 1.110   Nov 19 2004 10:08:16   zhangcel
// PET1117 FN8 -- Added getAggregatedOrderList function 
// 
//    Rev 1.109   Nov 15 2004 15:41:48   Fengyong
// Syncup - after .net conversion
// 
//    Rev 1.108   Nov 14 2004 14:34:02   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.107   Nov 07 2004 16:11:38   popescu
// PET 1117/56, getters for wkn/isin numbers fund/class by isin and wkn
// 
//    Rev 1.106   Nov 04 2004 11:01:10   FENGYONG
// PET1117 FN54 - Fund broker static temp check in for 59 build
// 
//    Rev 1.105   Oct 19 2004 14:54:18   FENGYONG
// PET1117 FN54 - Fund Broker Static
// 
//    Rev 1.104   Oct 13 2004 13:51:06   VADEANUM
// PET 1117 FN21 - Replaced SysLvlSettleLoc with SettlementInstr...
// 
//    Rev 1.103   Oct 07 2004 15:37:36   YINGBAOL
// PET1145 sync. up version 100.1.0
// 
//    Rev 1.102   Sep 07 2004 14:10:52   YINGBAOL
// PET1117: add Fee model transaction builder 
// 
//    Rev 1.101   Aug 10 2004 11:23:00   FENGYONG
// PET 1117 FN 5 - Client condition Fee
// 
//    Rev 1.100   May 18 2004 17:15:02   popescu
// PET 985, FN 01, Shareholder Tax Jurisdiction Warning
// 
//    Rev 1.99   May 11 2004 14:27:42   FENGYONG
// PET1046 FN1 - transfer-switch -Rel57
// 
//    Rev 1.98   Mar 03 2004 16:21:20   popescu
// PTS 10027578, refresh the account information after updating the mailing address info and demographics info; changed the name of the refreshMe method, to be consistent with the shareholder object
// 
//    Rev 1.97   Jan 28 2004 14:04:54   popescu
// PET 859, FN23, Added DailyTransactionsFees corresponding files and ids:
// DailyTransactionsFeeList.cpp +hpp
// DailyTransactionsFee.cpp +hpp
// DailyTransactionsFeesRepository.cpp +hpp
// DSTCDailyTransactionsFeesTrxnBuilder.cpp +hpp
// 
//    Rev 1.96   Jan 02 2004 15:11:56   popescu
// PTS 10025696, NASU flow crash 
// 
//    Rev 1.95   Dec 31 2003 11:54:14   popescu
// PTS 10025659, force a refresh of the Sahreholder object at host level if we have Demographics updates
// 
//    Rev 1.94   Dec 12 2003 14:09:38   linmay
// modified getTradeList( ) for PTS#10024566
// 
//    Rev 1.93   Nov 24 2003 18:10:10   HERNANDO
// PET859 FN1 - Added getSettlementLocationSysLvlList.
// 
//    Rev 1.92   Oct 16 2003 12:19:48   FENGYONG
// PET809 FN08 Direct Trading enhancement
// 
//    Rev 1.91   Oct 06 2003 15:36:56   popescu
// CIBC PET809. FN13 added the initial version of the required trxn builder
// 
//    Rev 1.90   Oct 04 2003 17:17:00   popescu
// CIBC PET809, Fn13, added the financialinstitutionlistrepository getter
// 
//    Rev 1.89   Oct 02 2003 10:30:18   HSUCHIN
// PTS 10021894 - bug fix with Account level AMS crash when setting WRAP defaults.
// 
//    Rev 1.88   Jul 23 2003 11:02:46   linmay
// modified getamsmstrlist
// 
//    Rev 1.87   Jul 18 2003 11:32:56   linmay
// modified for CIBC AMS
// 
//    Rev 1.86   Jul 01 2003 18:09:28   popescu
// Added the payment instruction dialog, process and CBO's, as well as the DistributorRepository builder
// 
//    Rev 1.85   Jun 19 2003 12:20:20   popescu
// Fix for the getAMSMstrList crash
// 
//    Rev 1.84   May 31 2003 11:55:04   popescu
// RRIF bank work
// 
//    Rev 1.83   May 28 2003 10:52:12   popescu
// Part of the cleaning of DSTCWorksession, not finalized yet, more to come....
// 
//    Rev 1.82   May 27 2003 18:29:34   popescu
// due to several memory leaks found in some list getters at the DSTCWorkSession level caused by copy/paste, I've created a common template function to retrieve the dependent objects
// 
//    Rev 1.81   May 27 2003 16:37:54   popescu
// NASU flow AMS :data not found issue fix and removed some memory leaks 
// 
//    Rev 1.80   May 27 2003 14:30:16   popescu
// For refresh
// 
//    Rev 1.79   May 23 2003 14:44:36   HERNANDO
// Added getManualDividendList. and builder call.
// 
//    Rev 1.78   May 22 2003 15:00:48   popescu
// name change 'left overs'
// 
//    Rev 1.77   May 22 2003 14:12:34   popescu
// Replaced name 'BankInstr' with 'BankInstructions'; 
// simplified child lists getters for the Shareholder object
// 
//    Rev 1.76   May 02 2003 14:43:34   linmay
// added FeeTag
// 
//    Rev 1.75   Apr 29 2003 17:09:10   popescu
// added new convenience method getFundDetail(),
// 
//    Rev 1.74   Apr 21 2003 09:46:42   YINGBAOL
// change key for getAMS....
// 
//    Rev 1.73   Apr 15 2003 10:46:52   linmay
// Sync up with 1.66.1.1
// 
//    Rev 1.72   Apr 02 2003 13:22:38   FENGYONG
// Add mailing override to persistent group
// 
//    Rev 1.71   Apr 02 2003 11:32:34   FENGYONG
// Add keytag for mailing override
// 
//    Rev 1.70   Mar 21 2003 18:07:34   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.69   Mar 07 2003 16:46:14   FENGYONG
// groupid fix
// 
//    Rev 1.68   Mar 03 2003 17:23:56   FENGYONG
// Add brokerlevel AMS
// 
//    Rev 1.67   Mar 03 2003 09:42:18   KOVACSRO
// Added getTradeSearchCriteria.
// 
//    Rev 1.66   Feb 11 2003 14:41:42   popescu
// changes related to the Historical information for Broker and Sales rep, as well as displaying the names for them in the Historical Info Search dialog
// 
//    Rev 1.65   Feb 07 2003 16:31:48   HSUCHIN
// settlement persistance bug fix
// 
//    Rev 1.64   Feb 03 2003 11:51:52   popescu
// When refreshing the work session the ProtectedFundList needs to be removed
// 
//    Rev 1.63   Jan 29 2003 12:16:38   HERNANDO
// Added getMktIndexValuesList. and builder call.
// 
//    Rev 1.62   Jan 27 2003 07:40:22   HSUCHIN
// removed resetinstrcriteria and added resetinstrlist
// 
//    Rev 1.61   Jan 26 2003 15:53:46   HSUCHIN
// added reset instruction
// 
//    Rev 1.60   Jan 25 2003 20:16:06   HERNANDO
// Added Market Index Master builder.
// 
//    Rev 1.59   Jan 25 2003 18:36:04   HERNANDO
// Added getMktIndexMasterList.
// 
//    Rev 1.58   Jan 25 2003 16:31:52   HSUCHIN
// added methods get get reset instruction criteria
// 
//    Rev 1.57   Jan 21 2003 12:53:50   KOVACSRO
// Added ACCTCATEGORYTAG
// 
//    Rev 1.56   Jan 20 2003 14:51:00   YINGBAOL
// add FeeParamSysTransactionBuilder
// 
//    Rev 1.55   Jan 18 2003 17:22:44   YINGBAOL
// add FeeParamSysTag
// 
//    Rev 1.54   Jan 13 2003 18:00:36   sanchez
// Changes for Shareholer
// 
//    Rev 1.53   Jan 09 2003 14:38:26   popescu
// Second revision, make things compilable
// 
//    Rev 1.52   Jan 09 2003 10:08:54   YINGBAOL
// Add getFeeParamSysSearchCriteria
// 
//    Rev 1.51   Dec 27 2002 11:27:48   linmay
// modified getAMSMstrList signature, added AMSType as input parameter
// 
//    Rev 1.50   Dec 08 2002 22:04:00   HSUCHIN
// removed reportstatuscriteria cbo
// 
//    Rev 1.49   Nov 29 2002 13:13:58   HSUCHIN
// added report status 
// 
//    Rev 1.48   Nov 27 2002 11:43:34   HSUCHIN
// added reports
// 
//    Rev 1.47   Nov 19 2002 16:19:56   YINGBAOL
// added getAMS.....
// 
//    Rev 1.46   Oct 16 2002 15:23:00   KOVACSRO
// synced up ver. 1.45
// 
//    Rev 1.45   Oct 09 2002 23:54:24   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.44   Sep 19 2002 11:07:36   KOVACSRO
// PTS 10009838, PTS 10009328 - there is no need to refresh the trades list; just delete it.
// 
//    Rev 1.43   Sep 17 2002 10:09:12   HSUCHIN
// added account entity mailing tag
// 
//    Rev 1.42   Aug 29 2002 12:55:40   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.41   Jul 10 2002 10:59:50   YINGBAOL
// fix refresh problem for settlement
// 
//    Rev 1.40   Jun 14 2002 16:51:38   VASILEAD
// set the ppType for DSTCPersistantRequestor
// 
//    Rev 1.39   Jun 14 2002 12:44:24   VASILEAD
// Fixed crashing when closing persistance ( view 74 ) fails.
// 
//    Rev 1.38   Jun 13 2002 09:49:26   VASILEAD
// Modified orderTrxn and commit to support persistance for settle transactions
// 
//    Rev 1.37   Jun 02 2002 17:53:00   HSUCHIN
// added pension info
// 
//    Rev 1.36   May 30 2002 11:08:58   YINGBAOL
// Add Settlement
// 
//    Rev 1.35   24 May 2002 15:44:56   KOVACSRO
// Fund and Client bank.
// 
//    Rev 1.34   22 May 2002 18:28:02   PURDYECH
// BFData Implementation
// 
//    Rev 1.33   Feb 25 2002 18:55:40   PURDYECH
// Phase 1 of BFData Rollout - Base Component Compatibility
// 
//    Rev 1.32   08 Feb 2002 17:27:38   KOVACSRO
// Force validation for MFAccount and Shareholder.
// 
//    Rev 1.31   01 Feb 2002 18:13:56   WINNIE
// PTS 10006987 : not calling bank builder, failed to set up banking records for broker, branch and salserep
// 
//    Rev 1.30   Jan 31 2002 14:51:28   YINGBAOL
// add FEEPARAMTAG
// 
//    Rev 1.29   Jan 04 2002 12:13:48   FENGYONG
// Add getadvisorlist and add trxnbuilder for slsrep update
// 
//    Rev 1.28   13 Dec 2001 17:18:10   KOVACSRO
// Only call the builders if something is changed.
// 
//    Rev 1.27   25 Oct 2001 14:02:48   SMITHDAV
// hasPermission changes...
// 
//    Rev 1.26   Oct 17 2001 15:11:00   FENGYONG
// fix system gone when company id not correct 
// 
//    Rev 1.25   15 Oct 2001 12:08:14   KOVACSRO
// 1.Added getBrokerList()
// 2.getMFAccount returns an empty object.
// 3.getShareholder returns an empty object
// do PopulateField() will make the view calls, for account and shareholder.
// 
//    Rev 1.24   Oct 03 2001 13:50:14   YINGBAOL
// add WorkSessionEntityList
// 
//    Rev 1.23   19 Sep 2001 14:56:50   KOVACSRO
// Added ESOP.
// 
//    Rev 1.22   30 Aug 2001 16:35:46   HSUCHIN
// added acct split comm tag 
// 
//    Rev 1.21   Aug 23 2001 14:01:30   JANKAREN
// fix error
// 
//    Rev 1.20   Aug 23 2001 12:26:46   JANKAREN
// Added As Pension Plan
// 
//    Rev 1.19   14 Aug 2001 11:18:26   SMITHDAV
// Set client based on MgmtCo's ClientID instead of MgmtCo's CompanyId.
// 
//    Rev 1.18   08 Aug 2001 10:56:48   SMITHDAV
// Made extensive fixes to ClientLocale management.
// 
//    Rev 1.17   04 Aug 2001 14:35:28   KOVACSRO
// Some data group changes.
// 
//    Rev 1.16   Aug 02 2001 01:21:26   YINGBAOL
// fix data group Id issue for get shareholder
// 
//    Rev 1.15   27 Jul 2001 14:45:22   SMITHDAV
// Refresh fixes.
// 
//    Rev 1.14   Jul 19 2001 18:26:24   OLTEANCR
//  bug fix for Commit(.. ) 
// 
//    Rev 1.13   Jul 18 2001 10:42:52   OLTEANCR
// disabled code used for testing manual creation of account/shareholder
// 
//    Rev 1.12   17 Jul 2001 15:23:18   HSUCHIN
// bug fix
// 
//    Rev 1.11   17 Jul 2001 15:12:20   HSUCHIN
// parameter bug fix for getTrade
// 
//    Rev 1.10   Jul 16 2001 18:54:44   OLTEANCR
// added new  TRXNTAG; modified constructor
// 
//    Rev 1.9   09 Jul 2001 15:25:10   SMITHDAV
// Mgmt company refresh related changes.
// 
//    Rev 1.8   14 Jun 2001 11:56:32   SMITHDAV
// Re-worked user access list and permission checking code.
// 
//    Rev 1.7   12 Jun 2001 13:48:56   SMITHDAV
// Fix bug -- set mgmtCoId for start and end persist views.
// 
//    Rev 1.6   Jun 12 2001 11:21:02   OLTEANCR
// sync up: getNewMFAccount(...),  getNewShareh(...)
// 
//    Rev 1.5   Jun 11 2001 14:40:20   HERNANDO
// Added setMgmtCo(MgmtCo *).
// 
//    Rev 1.4   04 Jun 2001 15:28:28   KOVACSRO
// DataGroupId bug fixes.
// 
//    Rev 1.3   25 May 2001 15:09:56   SMITHDAV
// Fix setObject bug in other maint functions.
// 
//    Rev 1.2   23 May 2001 14:37:50   SMITHDAV
// Fixed bug in getShareholder().
// 
//    Rev 1.1   10 May 2001 11:37:38   HSUCHIN
// Sync up with SSB
// 
//    Rev 1.0   03 May 2001 14:48:56   SMITHDAV
// Initial revision.
 *
 */