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
//    Copyright 2004 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : SystematicProcess.cpp
// ^AUTHOR : Chin Hsu
// ^DATE   : March 11, 1999
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : SystematicProcess
//    
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include <ifastcbo\accountentityxref.hpp>
#include <ifastcbo\addresslist.hpp>
#include <ifastcbo\coanavig.hpp>
#include <ifastdataimpl\dse_dstcglob_vw.hpp>
#include <ifastcbo\funddetaillist.hpp>
#include <ifastcbo\fundmasterlist.hpp>
#include <ifastcbo\grouplist.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\mgmtcooptions.hpp>
#include <ifastcbo\shareholder.hpp>
#include <ifastcbo\sysallocationlist.hpp>
#include <ifastcbo\systematic.hpp>
#include <ifastcbo\systematiclist.hpp>
#include "systematicprocess.hpp"
#include "systematicprocessincludes.h"
#include <ifastcbo\acqfeeinquiry.hpp>
#include <ifastcbo\autotransallocationlist.hpp>
#include <ifastcbo\autoaccttransallocationlist.hpp>
#include <ifastcbo\autoaccttransallocation.hpp>
#include <ifastcbo\savingplanmasterlist.hpp>
#include <xutility>
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_SYSTEMATIC;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_SYSTEMATIC;
#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< SystematicProcess > processCreator( CMD_BPROC_SYSTEMATIC );

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
   extern CLASS_IMPORT const long BP_ERR_INVALID_METHOD_CALL;
}

namespace
{
   // Trace literals
   const I_CHAR *       CLASSNAME            = I_("SystematicProcess");
   const I_CHAR * const PERFORMSEARCH        = I_("performSearch");
   const I_CHAR * const INDICATOR_MONTHLY    = I_( "YYYYYYYYYYYY" );
   const I_CHAR * const INDICATOR_QUARTERLY  = I_( "YNNYNNYNNYNN" );
   const I_CHAR * const INDICATOR_OTHER      = I_( "NNNNNNNNNNNN" );
   const I_CHAR * const CFDS                 = I_("Canada");
   const I_CHAR * const YES                  = I_( "Y" );
   const I_CHAR * const NO                   = I_( "N" );
   const I_CHAR * const CALLER               = I_( "Caller" );
   const I_CHAR * const WORK_TYPE            = I_( "WORKTYPE" );
   const I_CHAR * const MODIFY_PAC           = I_( "MODPAC" );
   const I_CHAR * const MODIFY_SWP           = I_( "MODSWP" );
   const I_CHAR * const BANKRUPTCY           = I_( "43" );
}

namespace SYSTEMATICLIT
{
   const I_CHAR * const ACCOUNT_NUM        = I_( "AccountNum");
   const I_CHAR * const ENTITY_ID          = I_( "EntityID" );
   const I_CHAR * const ENTITY_NAME        = I_( "EntityName" );
   const I_CHAR * const TRANS_TYPE         = I_( "TransType" );
   const I_CHAR * const MULTI_ALLOCATION   = I_( "FromMultiallocation" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId AtFrequency;
   extern CLASS_IMPORT const BFTextFieldId PACSWPFrequency;
   extern CLASS_IMPORT const BFTextFieldId FrFundNumber;
   extern CLASS_IMPORT const BFTextFieldId ToFundNumber;
   extern CLASS_IMPORT const BFTextFieldId SystematicPayType;
   extern CLASS_IMPORT const BFTextFieldId BankIdType;
   extern CLASS_IMPORT const BFTextFieldId BankIdTypeDisplay;
   extern CLASS_IMPORT const BFTextFieldId VUBFee;
   extern CLASS_IMPORT const BFDecimalFieldId VUBFeeFrac1;
   extern CLASS_IMPORT const BFDecimalFieldId VUBFeeFrac2;
   extern CLASS_IMPORT const BFDecimalFieldId VUBFeeRate;
   extern CLASS_IMPORT const BFTextFieldId RxPlanCode;
   extern CLASS_IMPORT const BFDecimalFieldId AnnualFeeAmt;
   extern CLASS_IMPORT const BFTextFieldId VUBFeeType;
   extern CLASS_IMPORT const BFDecimalFieldId VUBFeeFrac1;
   extern CLASS_IMPORT const BFDecimalFieldId VUBFeeFrac2;
   extern CLASS_IMPORT const BFDecimalFieldId VUBFeeRate;
   extern CLASS_IMPORT const BFTextFieldId BankInformation;
   extern CLASS_IMPORT const BFTextFieldId BatchName;
   extern CLASS_IMPORT const BFTextFieldId ReplaceAsDefault;
   extern CLASS_IMPORT const BFTextFieldId LSIFPAC;
	
	extern CLASS_IMPORT const BFTextFieldId SystematicGridHeading;
	extern CLASS_IMPORT const BFTextFieldId SystematicGridLeftHeading;		

   extern CLASS_IMPORT const BFTextFieldId VerifyStat;
   extern CLASS_IMPORT const BFTextFieldId NonFinConfirms;
   extern CLASS_IMPORT const BFTextFieldId FundAlloc;
   extern CLASS_IMPORT const BFTextFieldId RDRAdvice;

}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const PAC;
   extern CLASS_IMPORT I_CHAR * const SWP;
   extern CLASS_IMPORT I_CHAR * const AUTO_TRANSFER_IN;
   extern CLASS_IMPORT I_CHAR * const AUTO_TRANSFER_OUT;
   extern CLASS_IMPORT I_CHAR * const AUTO_TRANSFER;
   extern CLASS_IMPORT I_CHAR * const SAVING_PLAN;
}

const I_CHAR * const LIST_KEY           = I_( "ListKey" );

namespace AUDITTYPE
{
   extern CLASS_IMPORT I_CHAR * const BKD;
   extern CLASS_IMPORT I_CHAR * const ATF;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

//CP20030319SystematicProcess::SystematicProcess() 
SystematicProcess::SystematicProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
,  _pMFAccount( NULL )
, _pSystematicList( NULL )
, _rpChildGI( NULL )
, _pFundMasterList( NULL )
, _pFundDetailList( NULL )
, _pAtAcctTransAllocationList(NULL)
, _pSystematic(NULL)
, _pAcqFeeInquiry( NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   _dstrListKey         = NULL_STRING;
   _dstrShrNum          = NULL_STRING;
   _dstrEntityName      = NULL_STRING;
   _dstrAccountNum      = NULL_STRING;

   addContainer(IFASTBP_PROC::SYSTEMATIC_LIST, true, BF::NullContainerId, true, I_("Systematic"));
   addContainer(IFASTBP_PROC::SAVINGPLAN_MASTER_LIST, true);
   addContainer(IFASTBP_PROC::SYSALLOCATION_LIST, true, BF::NullContainerId, true);
   addContainer(IFASTBP_PROC::FUND_MASTER_LIST,   true);
   addContainer(IFASTBP_PROC::FUND_DETAIL_LIST,   true);
   addContainer(IFASTBP_PROC::ADDRESS_LIST,       true);
   addContainer(IFASTBP_PROC::MFACCOUNT_CBO,      false, BF::NullContainerId, false);
   addContainer(IFASTBP_PROC::ACQFEEINQUIRY_CBO,  true);

   addContainer(IFASTBP_PROC::AT_ACCOUNT_ALLOCATIONLIST,  true,
                IFASTBP_PROC::SYSTEMATIC_LIST,true);
   addContainer(IFASTBP_PROC::AT_FUND_ALLOCATIONLIST,  true,
                IFASTBP_PROC::AT_ACCOUNT_ALLOCATIONLIST,true);

   addContainer( IFASTBP_PROC::ACCOUNT_LIST, true );

   addSubstituteList(ifds::SystematicListHeading);
   addSubstituteList(ifds::SysAllocListHeading);
   addSubstituteList(ifds::SystematicPayType);


   addSubstituteList(ifds::PayType);
   addSubstituteList(ifds::BankAcctCurrency);
   addSubstituteList(ifds::AmountType);
   addSubstituteList(ifds::EndOfMonth);
   addSubstituteList(ifds::AddrCode);
   addSubstituteList(ifds::SrcOfFund);
   addSubstituteList(ifds::BankAcctType);
   addSubstituteList(ifds::GrossOrNet);
   addSubstituteList(ifds::StatusCode);
   addSubstituteList(ifds::Frequency);
   addSubstituteList(ifds::AtFrequency);
   addSubstituteList(ifds::PACSWPFrequency);

   addSubstituteList(ifds::DayOfWeek);

   addSubstituteList(ifds::FeeCurrency);
   addSubstituteList(ifds::AdminFeeCurr);
   addSubstituteList(ifds::FlatPercent);

   addSubstituteList(ifds::VUBPayOption);

//###
   addSubstituteList(ifds::BankIdTypeDisplay);

   addFieldDetails( ifds::AllocAccountNum, IFASTBP_PROC::ACCOUNT_LIST, SUBCLASS_PROCESS);

   //Account Detail
   addFieldDetails(ifds::AccountNum, BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails(ifds::ShrNum,     BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails(ifds::FeeWaived,  BF::NullContainerId, SUBCLASS_PROCESS);

   //COANavig
   addFieldDetails(ifds::CurrBusDate,      BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails(ifds::DisableFee4Alloc, BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails(ifds::AcqFeeDefault,   BF::NullContainerId, SUBCLASS_PROCESS);

   //Parameters
   addFieldDetails(SYSTEMATICLIT::PRIMARY_ACCOUNT_OWNER, BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails(SYSTEMATICLIT::LISTKEY,               BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails(SYSTEMATICLIT::TRANS_TYPE_PARAM,      BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails(SYSTEMATICLIT::FEE_DISABLE_FLAG,      BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails(SYSTEMATICLIT::FEE_UPDATE_FLAG,       BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails(SYSTEMATICLIT::DEFAULT_ACQFEE,        BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails(SYSTEMATICLIT::NEW_SYSTEMATIC,        BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails(SYSTEMATICLIT::AreAllSytematicRecordsInactive, BF::NullContainerId, SUBCLASS_PROCESS);
   


   addFieldDetails(ifds::AcqFee,        BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails(ifds::AcqFeeType,    BF::NullContainerId, SUBCLASS_PROCESS);


   addFieldDetails(SYSTEMATICLIT::TRANSACTION_TYPE,    BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails(SYSTEMATICLIT::IS_XREF_WARN_APPL,   BF::NullContainerId, SUBCLASS_PROCESS);

   addFieldDetails(IsSWPCustomPayoutPlan,   BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails(IsSWPPortfolioPayoutPlan,   BF::NullContainerId, SUBCLASS_PROCESS);
		   
   //Acquisition Fee Calculation Inquiry
/**
   idList = ACQFEEINQUIRY_CBO;
   addFieldDetails(DBR::AcqFee,        idList);
   addFieldDetails(DBR::AcqFeeType,    idList);
   addFieldDetails(DBR::MaxFeeActive,  idList);
   addFieldDetails(DBR::MaxFee,        idList);
   addFieldDetails(DBR::MaxFeeType,    idList);
   addFieldDetails(DBR::MaxPercent,    idList);
   addFieldDetails(DBR::MaxFlatFundCurr,idList);
*/
   //Saving Plan Master
//CP20030309   idList = SYSTEMATICLIT::SAVINGPLAN_MASTER_LIST;
   addFieldDetails(ifds::RxPlanCode,  IFASTBP_PROC::SAVINGPLAN_MASTER_LIST);
   addFieldDetails(ifds::AnnualFeeAmt,  IFASTBP_PROC::SAVINGPLAN_MASTER_LIST);
   addFieldDetails(ifds::VUBFeeType,  IFASTBP_PROC::SAVINGPLAN_MASTER_LIST);
   addFieldDetails(ifds::VUBFeeFrac1,  IFASTBP_PROC::SAVINGPLAN_MASTER_LIST);
   addFieldDetails(ifds::VUBFeeFrac2,  IFASTBP_PROC::SAVINGPLAN_MASTER_LIST);
   addFieldDetails(ifds::VUBFeeRate,  IFASTBP_PROC::SAVINGPLAN_MASTER_LIST);

   //Fund Master
//CP20030309   idList = FUND_MASTER_LIST;
   addFieldDetails(ifds::FundCode,  IFASTBP_PROC::FUND_MASTER_LIST);
   addFieldDetails(ifds::ElongName1,IFASTBP_PROC::FUND_MASTER_LIST);
   addFieldDetails(ifds::FundType,  IFASTBP_PROC::FUND_MASTER_LIST);

   //Fund Detail List
//CP20030309   idList = FUND_DETAIL_LIST;
   addFieldDetails(ifds::FundCode,  IFASTBP_PROC::FUND_DETAIL_LIST);
   addFieldDetails(ifds::ClassCode, IFASTBP_PROC::FUND_DETAIL_LIST);
   addFieldDetails(ifds::Currency,  IFASTBP_PROC::FUND_DETAIL_LIST);
   addFieldDetails(ifds::LoadType,  IFASTBP_PROC::FUND_DETAIL_LIST);

   //System Allocation List
//CP20030309   idList = SYSALLOCATION_LIST;
   addFieldDetails(ifds::TransType,        IFASTBP_PROC::SYSALLOCATION_LIST);
   addFieldDetails(ifds::PACSWPId,         IFASTBP_PROC::SYSALLOCATION_LIST);
   addFieldDetails(ifds::FundCode,         IFASTBP_PROC::SYSALLOCATION_LIST);
   addFieldDetails(ifds::ClassCode,        IFASTBP_PROC::SYSALLOCATION_LIST);
   addFieldDetails(ifds::Percentage,       IFASTBP_PROC::SYSALLOCATION_LIST);
   addFieldDetails(ifds::AllocAmount,      IFASTBP_PROC::SYSALLOCATION_LIST);
   addFieldDetails(ifds::SettleCurrency,   IFASTBP_PROC::SYSALLOCATION_LIST);
   addFieldDetails(ifds::Level,            IFASTBP_PROC::SYSALLOCATION_LIST);
   addFieldDetails(ifds::AllocAccountNum,  IFASTBP_PROC::SYSALLOCATION_LIST);

   //Automatic Account Allocation List
//CP20030309   idList = SYSTEMATICLIT::AT_ACCOUNT_ALLOCATIONLIST;
   addFieldDetails(ifds::TransType,        IFASTBP_PROC::AT_ACCOUNT_ALLOCATIONLIST);
   addFieldDetails(ifds::PACSWPId,         IFASTBP_PROC::AT_ACCOUNT_ALLOCATIONLIST);
   addFieldDetails(ifds::FundCode,         IFASTBP_PROC::AT_ACCOUNT_ALLOCATIONLIST);
   addFieldDetails(ifds::ClassCode,        IFASTBP_PROC::AT_ACCOUNT_ALLOCATIONLIST);
   addFieldDetails(ifds::Percentage,       IFASTBP_PROC::AT_ACCOUNT_ALLOCATIONLIST);
   addFieldDetails(ifds::AllocAmount,      IFASTBP_PROC::AT_ACCOUNT_ALLOCATIONLIST);
   addFieldDetails(ifds::SettleCurrency,   IFASTBP_PROC::AT_ACCOUNT_ALLOCATIONLIST);
   addFieldDetails(ifds::Level,            IFASTBP_PROC::AT_ACCOUNT_ALLOCATIONLIST);
   addFieldDetails(ifds::AllocAccountNum,  IFASTBP_PROC::AT_ACCOUNT_ALLOCATIONLIST);

   //Automatic Fund Allocation List
//CP20030309   idList = SYSTEMATICLIT::AT_FUND_ALLOCATIONLIST;
   addFieldDetails(ifds::TransType,        IFASTBP_PROC::AT_FUND_ALLOCATIONLIST);
   addFieldDetails(ifds::PACSWPId,         IFASTBP_PROC::AT_FUND_ALLOCATIONLIST);
   addFieldDetails(ifds::FundCode,         IFASTBP_PROC::AT_FUND_ALLOCATIONLIST);
   addFieldDetails(ifds::ClassCode,        IFASTBP_PROC::AT_FUND_ALLOCATIONLIST);
   addFieldDetails(ifds::Percentage,       IFASTBP_PROC::AT_FUND_ALLOCATIONLIST);
   addFieldDetails(ifds::AllocAmount,      IFASTBP_PROC::AT_FUND_ALLOCATIONLIST);
   addFieldDetails(ifds::SettleCurrency,   IFASTBP_PROC::AT_FUND_ALLOCATIONLIST);
   addFieldDetails(ifds::Level,            IFASTBP_PROC::AT_FUND_ALLOCATIONLIST);
   addFieldDetails(ifds::AllocAccountNum,  IFASTBP_PROC::AT_FUND_ALLOCATIONLIST);

   //Systematic List
//CP20030309   idList = SYSTEMATICLIT::SYSTEMATIC_LIST;
   addFieldDetails( ifds::TransType,       IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::PACSWPId,        IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::BankDetlVer,     IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::BrokerCode,      IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::BranchCode,      IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::SalesRepCode,    IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::BrokerName,      IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::BranchName,      IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::SlsrepName,      IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::Amount,          IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::AmountType,      IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::AmountTypeDesc,  IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::GrossOrNet,      IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::Fee,             IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::FlatPercent,     IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::FeeCurrency,     IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::FeeCurrDesc,     IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::AdminFeeAmt,     IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::AdminFeeCurr,    IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::AdminFeeCurrDesc,IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::PayType,         IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::PayTypeDesc,     IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::BankIdValue,     IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::SwiftCode,       IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::RefNumber,       IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::TransitNo,       IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::BankAcctNum,     IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::BankAcctName,    IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::SourceOfBankAcct,IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::BankAcctCurrency,IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::BankCurrDesc,    IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::BankAcctType,    IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::BankAcctTypeDesc,IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::SrcOfFund,       IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::SrcOFundDesc,    IFASTBP_PROC::SYSTEMATIC_LIST );
   //addFieldDetails( DBR::January,         SYSTEMATICLIT::SYSTEMATIC_LIST );
   //addFieldDetails( DBR::February,        SYSTEMATICLIT::SYSTEMATIC_LIST );
   //addFieldDetails( DBR::March,           SYSTEMATICLIT::SYSTEMATIC_LIST );
   //addFieldDetails( DBR::April,           SYSTEMATICLIT::SYSTEMATIC_LIST );
   //addFieldDetails( DBR::May,             SYSTEMATICLIT::SYSTEMATIC_LIST );
   //addFieldDetails( DBR::June,            SYSTEMATICLIT::SYSTEMATIC_LIST );
   //addFieldDetails( DBR::July,            SYSTEMATICLIT::SYSTEMATIC_LIST );
   //addFieldDetails( DBR::August,          SYSTEMATICLIT::SYSTEMATIC_LIST );
   //addFieldDetails( DBR::September,       SYSTEMATICLIT::SYSTEMATIC_LIST );
   //addFieldDetails( DBR::October,         SYSTEMATICLIT::SYSTEMATIC_LIST );
   //addFieldDetails( DBR::November,        SYSTEMATICLIT::SYSTEMATIC_LIST );
   //addFieldDetails( DBR::December,        SYSTEMATICLIT::SYSTEMATIC_LIST );
   addFieldDetails( ifds::EndOfMonth,      IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::DayOfWeek,       IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::LastProcessDate, IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::NextProcessDate, IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::AddrCode,        IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::StatusCode,      IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::EffectiveDate,   IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::ProcessDate,     IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::ModDate,         IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::StopDate,        IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::Username,        IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::ModUser,         IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::AddrLine1,       IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::AddrLine2,       IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::AddrLine3,       IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::AddrLine4,       IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::AddrLine5,       IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::PostalCode,      IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::InstName,        IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::SlsrepAltName,   IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::FundCode,        IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::ClassCode,       IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::PayReason1,      IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::PayReason2,      IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::FundToCode,      IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::ClassToCode,     IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::AccountTo,       IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::BELFee,          IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::BatchUser,       IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::BatchName,       IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::BatchTrace,      IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::BatchDate,       IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::TransferType,    IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::Frequency,       IFASTBP_PROC::SYSTEMATIC_LIST );
   //addFieldDetails( DBR::FlatPercentDesc, SYSTEMATICLIT::SYSTEMATIC_LIST );
   addFieldDetails( ifds::FrequencyDesc,   IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::TransTypeDesc,   IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::FrFundNumber,    IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::ToFundNumber,    IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::SystematicPayType, IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::TransNum,          IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::SplitComm,         IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::BankIdType,        IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::BankIdTypeDisplay, IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::ExchInFee,         IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::ExchInFlatPercent, IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::ExchOutFee,         IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::ExchOutFlatPrcnt, IFASTBP_PROC::SYSTEMATIC_LIST );

   addFieldDetails( ifds::AnnualMaint,IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::InitialAmt,IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::VUBExpectedAmt,IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::VUBCollectedAmt,IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::VUBFeeType,IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::VUBFee,IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::PlanCode,IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::IndexExist,IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::VUBFeeFrac1,IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::VUBFeeFrac2,IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::VUBFeeRate,IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::BankInformation,IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::VUBPayOption,IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::AnnualFeeDate,IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::MonthIndicator,IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::ModPerm,IFASTBP_PROC::SYSTEMATIC_LIST );

   addFieldDetails( ifds::PayMethod,                 IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::ACHProcessor,              IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::SystematicGridHeading,     IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::SystematicGridLeftHeading, IFASTBP_PROC::SYSTEMATIC_LIST );

   addFieldDetails( ifds::FedTaxPUDOverride,         IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::FedRate,                   IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::ProvTaxPUDOverride,        IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::ProvRate,                  IFASTBP_PROC::SYSTEMATIC_LIST );

   addFieldDetails( ifds::VerifyStat,                IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::NonFinConfirms,             IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::RDRAdvice,                 IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::EventReceiptDate,			 IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails( ifds::EventReceiptTime,			 IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails ( ifds::SourceOfTrade,			 IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails ( ifds::ChannelOfTrade,           IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails ( ifds::Platform,				 IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails ( ifds::PSDAdvice,			     IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails ( ifds::SignatureDate,			 IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails ( ifds::YearlyAmount,			 IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails ( ifds::CPIRate,			         IFASTBP_PROC::SYSTEMATIC_LIST );
   addFieldDetails ( ifds::PayoutFactorRate,		 IFASTBP_PROC::SYSTEMATIC_LIST );
    addFieldDetails( ifds::AmtTypeOvrd,               IFASTBP_PROC::SYSTEMATIC_LIST); 

   //Address List
//CP20030309   idList = ADDRESS_LIST;
   addFieldDetails( ifds::AddrCode,        IFASTBP_PROC::ADDRESS_LIST );
   addFieldDetails( ifds::AddrCodeDesc,    IFASTBP_PROC::ADDRESS_LIST );
   addFieldDetails( ifds::AddrLine1,       IFASTBP_PROC::ADDRESS_LIST );
   addFieldDetails( ifds::AddrLine2,       IFASTBP_PROC::ADDRESS_LIST );
   addFieldDetails( ifds::AddrLine3,       IFASTBP_PROC::ADDRESS_LIST );
   addFieldDetails( ifds::AddrLine4,       IFASTBP_PROC::ADDRESS_LIST );
   addFieldDetails( ifds::AddrLine5,       IFASTBP_PROC::ADDRESS_LIST );
   addFieldDetails( ifds::PostalCode,      IFASTBP_PROC::ADDRESS_LIST );
   addFieldDetails( ifds::CountryCode,     IFASTBP_PROC::ADDRESS_LIST );
   addFieldDetails( ifds::EffectiveDate,   IFASTBP_PROC::ADDRESS_LIST );
   addFieldDetails( ifds::StopDate,        IFASTBP_PROC::ADDRESS_LIST );
   addFieldDetails( ifds::AddrStatus,      IFASTBP_PROC::ADDRESS_LIST );

   addFieldDetails( ifds::StopReasonPAC,      IFASTBP_PROC::SYSTEMATIC_LIST );

//   addFieldDetails( DBR::Frequency, BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( SYSTEMATICLIT::ORG_KEY, BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( SYSTEMATICLIT::DEST_KEY, BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( ifds::Name, BF::NullContainerId, SUBCLASS_PROCESS );//AccountTo accountholder name
   addFieldDetails( SYSTEMATICLIT::WHTaxApply, BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( SYSTEMATICLIT::FileProcessorApply, BF::NullContainerId, SUBCLASS_PROCESS );
   addFieldDetails( SYSTEMATICLIT::IsFundLimitedByBankuptcy, BF::NullContainerId, SUBCLASS_PROCESS );

   addFieldDetails(ifds::FundAlloc, BF::NullContainerId, SUBCLASS_PROCESS);
   addFieldDetails(ifds::TaxType, IFASTBP_PROC::MFACCOUNT_CBO);
}

//******************************************************************************

SystematicProcess::~SystematicProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   _rpChildGI = NULL;
   //delete _pSystematicList;
   //_pSystematicList = NULL;
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

void SystematicProcess::doGetField(
                                  const GenericInterface *rpGICaller,
                                  const BFContainerId& idContainer,
                                  const BFFieldId& idField,
                                  const BFDataGroupId& idDataGroup,
                                  DString &strValueOut,
                                  bool bFormatted
                                  ) const
{
   if( idField == ifds::AccountNum )
   {
      strValueOut = _dstrAccountNum;
   }
   else if( idField == SYSTEMATICLIT::TRANSACTION_TYPE )
   {
      assert(_pSystematic);
      strValueOut = _pSystematic->getTransactionTypeValue(idDataGroup);
   }
   else if( idField == SYSTEMATICLIT::NEW_SYSTEMATIC )
   {
      strValueOut = (_pSystematic->isNewObject()) ? YES : NO;
   }

   else if( idField == ifds::ShrNum )
   {
      strValueOut = _dstrShrNum;
   }
   else if( idField == ifds::FeeWaived )
   {
      _pMFAccount->getField(idField, strValueOut, getDataGroupId(), bFormatted);
   }
   else if( idField == ifds::CurrBusDate || idField == ifds::DisableFee4Alloc || idField == ifds::AcqFeeDefault 
      || idField == ifds::FundAlloc)
   {
      _pMgmtCoOption->getField(idField, strValueOut, getDataGroupId(), bFormatted);
   }
   else if( idField == SYSTEMATICLIT::PRIMARY_ACCOUNT_OWNER )
   {
      strValueOut = _dstrEntityName;
   }
   else if( idField == SYSTEMATICLIT::LISTKEY )
   {
      strValueOut = _dstrListKey;
   }
   else if( idField == SYSTEMATICLIT::TRANS_TYPE_PARAM )
   {
      strValueOut = _dstrTransType;
   }
   else if( idField == SYSTEMATICLIT::FEE_DISABLE_FLAG )
   {
      strValueOut = _pSystematic->getFeeDisableFlag();
   }
   else if( idField == SYSTEMATICLIT::FEE_UPDATE_FLAG )
   {
      strValueOut = _pSystematic->getFeeUpdateFlag();
   }
   else if( idField == SYSTEMATICLIT::DEFAULT_ACQFEE )
   {
      strValueOut = _pSystematic->getDefaultAcqFee();
   }
   else if( idField == ifds::AcqFee )
   {
      if( _pAcqFeeInquiry )
         _pAcqFeeInquiry->getField(idField, strValueOut, getDataGroupId(), bFormatted);
      else
         strValueOut = NULL_STRING;
   }
   else if( idField == ifds::AcqFeeType )
   {
      if( _pAcqFeeInquiry )
         _pAcqFeeInquiry->getField(idField, strValueOut, getDataGroupId(), bFormatted);
      else
         strValueOut = NULL_STRING;
   }
   else if( idField == ifds::AllocAccountNum &&  idContainer == IFASTBP_PROC::ACCOUNT_LIST )
   {
      BFAbstractCBO* pBase = ( const_cast < SystematicProcess *> ( this ) )->getCBOItem(IFASTBP_PROC::ACCOUNT_LIST,idDataGroup);
      if( pBase )
         pBase->getField(ifds::AccountNum,strValueOut,idDataGroup,bFormatted);
   }
   else if( idField == ifds::Name )//account to acc. holder name
   {
      strValueOut = NULL_STRING;
      DString strAccountTo;
      SystematicProcess * pThis = const_cast < SystematicProcess *> ( this );
      pThis->getField(this, ifds::AccountTo, strAccountTo, false);
      if( !strAccountTo.strip().empty() )
         pThis->getEntityName( getDataGroupId(), strAccountTo, strValueOut);
   }
   else if( idField==SYSTEMATICLIT::WHTaxApply )
   {
      strValueOut = _pSystematic->isWHTaxApplicable( getDataGroupId() )?YES:NO;
   }
   else if(idField ==SYSTEMATICLIT::FileProcessorApply )
   {   
      strValueOut = _pSystematic->isFileProcessorApplicable( getDataGroupId() )?YES:NO;
   }
   else if ( idField == SYSTEMATICLIT::IsFundLimitedByBankuptcy )
   {
      strValueOut = _pSystematic->isFieldsDisabledBaseOnRuleType( BANKRUPTCY, getDataGroupId() )?YES:NO;
   }
   else if( idField == SYSTEMATICLIT::IS_XREF_WARN_APPL )
   {
      MFAccount *pMFAccount = NULL;
	  bool bDisplyWarnSICAV = false;
	  bool bDisplyWarnOEIC  = false;
	  DSTCWorkSession* pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
	  if (pDSTCWorkSession->getMFAccount (idDataGroup, 
      _dstrAccountNum, pMFAccount) <= WARNING && pMFAccount)
	  { 		 
		  pMFAccount->displayEnvXrefWarningOnUpdate(idDataGroup, bDisplyWarnSICAV, bDisplyWarnOEIC);
	  }
	  strValueOut = ( bDisplyWarnSICAV || bDisplyWarnOEIC) ? I_("Y") : I_("N");
   }
   else if (idField == SYSTEMATICLIT::AreAllSytematicRecordsInactive)
   {
	   SystematicList *pSystematicList =  dynamic_cast < SystematicList*> (( const_cast < SystematicProcess *> ( this ) )->getCBOList (IFASTBP_PROC::SYSTEMATIC_LIST, idDataGroup));
	   if (pSystematicList)
	   {
		   strValueOut = pSystematicList->areAllSytematicRecordsInactive (idDataGroup) ? I_("Y"): I_("N");
	   }
   }
   else if (idField == IsSWPCustomPayoutPlan)
   {
       strValueOut = _pSystematic->isSWPCustomPayoutPlan(idDataGroup) ? YES:NO;
   }
   else if (idField == IsSWPPortfolioPayoutPlan)
   {
       strValueOut = _pSystematic->isSWPPortfolioPayoutPlan(idDataGroup) ? YES:NO;
   }
   else
   {
      assert( 0 );   
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETFIELD,
                      CND::BP_ERR_INVALID_METHOD_CALL );
   }
}
//*****************************************************************************

//******************************************************************************

SEVERITY SystematicProcess::doSetField(
                                      const GenericInterface *rpGICaller,
                                      const BFContainerId& idContainer,
                                      const BFFieldId& idField,
                                      const BFDataGroupId& idDataGroup,
                                      const DString& strValue,
                                      bool bFormatted
                                      )
{  
   if( BF::NullContainerId == idContainer && idField == SYSTEMATICLIT::ORG_KEY )
   {
      _dstrOrgKey = strValue;
   }
   else if( BF::NullContainerId == idContainer && idField == SYSTEMATICLIT::DEST_KEY )
   {
      _dstrDestKey = strValue;

      MFAccount*                 pMFAccount;
      SystematicList*            pSystematicList;
      DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      dstcWorkSession->getMFAccount( idDataGroup, _dstrAccountNum, pMFAccount); 
      pMFAccount->getSystematicList( pSystematicList, idDataGroup );

      pSystematicList->AddCopy(_dstrOrgKey, _dstrDestKey, idDataGroup);
   }
   else if( BF::NullContainerId == idContainer && idField == ifds::Frequency )
   {
   }
   else if( BF::NullContainerId == idContainer && idField == SYSTEMATICLIT::FEE_UPDATE_FLAG )
   {
      _pSystematic->setConfirmedFee(idDataGroup, strValue);
   }
   else if( idField == SYSTEMATICLIT::NEW_SYSTEMATIC )
   {
      _pSystematic->setObjectAsNew( strValue == YES );
   }

   return(NO_CONDITION);
}


//******************************************************************************

SEVERITY SystematicProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );

   const BFDataGroupId& idDataGroup = getDataGroupId();
//  setMyGroupID( idDataGroup ); //setting a idDataGroup for the process

   SEVERITY sevRtn  = SEVERE_ERROR, sevRtn1 = SEVERE_ERROR;
   try
   {
      DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      MgmtCo &mgmtCoOut = dstcWorkSession->getMgmtCo();

      sevRtn = mgmtCoOut.getFundMasterList(_pFundMasterList);
      if( sevRtn > WARNING )
         return(sevRtn);
      setContainer(IFASTBP_PROC::FUND_MASTER_LIST, _pFundMasterList);

      sevRtn = mgmtCoOut.getFundDetailList(_pFundDetailList);
      if( sevRtn > WARNING )
         return(sevRtn);
      setContainer(IFASTBP_PROC::FUND_DETAIL_LIST, _pFundDetailList);

      sevRtn = mgmtCoOut.getGroupList(_pGroupList);
      if( sevRtn > WARNING )
         return(sevRtn);

      sevRtn = mgmtCoOut.getMgmtCoOptions( _pMgmtCoOption);
      if( sevRtn > WARNING )
         return(sevRtn);

      //get the account number passed from the parent screen
      getParameter( SYSTEMATICLIT::ACCOUNT_NUM, _dstrAccountNum );
      getParameter( SYSTEMATICLIT::TRANS_TYPE, _dstrTransType );
      getParameter( CALLER, _dstrCaller );
	  getParameter (WORK_TYPE, _dstrWorkType);

      sevRtn1 = performSearch( this, BF::AllContainerIds, SEARCH_START );
      if( sevRtn1  > WARNING )
         return(sevRtn1);
      sevRtn = max( sevRtn1, sevRtn );
      if( WARNING >= sevRtn )
      {
         _dstrAccountNum.stripLeading( '0' );
         _dstrAccountNum.strip();
         if( !_dstrAccountNum.empty() )
         {
            setGlobal( WORK_GLOBAL, ifds::LastActiveAccountNum, _dstrAccountNum );
         }
      }

      //if( dstcWorkSession->getMFAccount( idDataGroup, _dstrAccountNum, _pMFAccount ) <= WARNING )
      if( dstcWorkSession->getMFAccount( idDataGroup, _dstrAccountNum, _pMFAccount, I_("N"), NULL_STRING, true, true  ) <= WARNING )
      {
         DString dstrShrNum;
         _pMFAccount->getField ( ifds::ShrNum, dstrShrNum, idDataGroup );
         setGlobal( WORK_GLOBAL, ifds::LastActiveShrNum, dstrShrNum );
      }

      DString dstrShareholderNum;
      _pMFAccount->getField( ifds::ShrNum, dstrShareholderNum, idDataGroup );
      dstrShareholderNum.strip().stripLeading( I_CHAR( '0' ) );
      Shareholder*  pShareholder;
      sevRtn = dstcWorkSession->getShareholder( idDataGroup, dstrShareholderNum, pShareholder );
      if( sevRtn > WARNING )
         return(sevRtn);

      MFAccountList *pMFAccountList;
      sevRtn = pShareholder->getMFAccountList( pMFAccountList, idDataGroup );
      if( sevRtn > WARNING )
         return(sevRtn);
      setContainer( IFASTBP_PROC::ACCOUNT_LIST, pMFAccountList );



      sevRtn = mgmtCoOut.getSavingPlanMasterList(_pSavingPlanMasterList);
      if( sevRtn > WARNING )
         return(sevRtn);
      setContainer(IFASTBP_PROC::SAVINGPLAN_MASTER_LIST, _pSavingPlanMasterList);

   }
   catch( ConditionException &ce )
   {
      SETCONDITIONFROMEXCEPTION(ce);
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2(CND::BPBASE_CONDITION, CLASSNAME, DOINIT, CND::BP_ERR_UNKNOWN_EXCEPTION);
   }
   return(sevRtn);
}

//******************************************************************************

bool SystematicProcess::doModelessChildComplete( const Command &cmd )
{
   // End when GUI ends
   return(cmd.getKey() == CMD_GUI_SYSTEMATIC);
}

//******************************************************************************

bool SystematicProcess::doModelessSetFocus(GenericInterface *rpGICaller)
{  
   // This is implemented to pass set focus on to child dialog.
   bool bRtn = false;
   DString dstrAccountNum, dstrTransType;

   getParameter(SYSTEMATICLIT::ACCOUNT_NUM, dstrAccountNum);
   getParameter(SYSTEMATICLIT::TRANS_TYPE,  _dstrTransType);
   getParameter(LIST_KEY,    _dstrListKey);
   if( dstrAccountNum != _dstrAccountNum )
   {
      _dstrAccountNum = dstrAccountNum;
      setGlobal( WORK_GLOBAL, ifds::LastActiveAccountNum, _dstrAccountNum );
      performSearch(this, BF::AllContainerIds, SEARCH_START);
   }

   if( _rpChildGI && isValidModelessInterface( _rpChildGI ) )
   {
      setParameter(SYSTEMATICLIT::ACCOUNT_NUM, _dstrAccountNum);
      bRtn = _rpChildGI->refresh(this, NULL);
      bRtn = _rpChildGI->modelessSetFocus(rpGICaller);
   }
   return(bRtn);
}

//******************************************************************************

E_COMMANDRETURN SystematicProcess::doProcess()
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
         setParameter(SYSTEMATICLIT::ACCOUNT_NUM, _dstrAccountNum);
		 setParameter( CALLER, _dstrCaller );
	   	 setParameter (WORK_TYPE, _dstrWorkType);
         
		 rtn = invokeCommand(this, CMD_GUI_SYSTEMATIC, getProcessType(), isModal(), &_rpChildGI);
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

SEVERITY SystematicProcess::performSearch( GenericInterface *rpGI, const BFContainerId& idSearch, 
                                           E_SEARCHACTION eSearchAction )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, PERFORMSEARCH);
   SEVERITY sevRtn = SEVERE_ERROR, sevRtn1 = SEVERE_ERROR;

   const BFDataGroupId& idDataGroup = getDataGroupId();

//CP20030311   This code appears to be obsolete.  I can't find any block of code which
//CP20030311   invokes performSearch for a idSearch of -9999
//CP20030311   /**
//CP20030311     * called from the GUI dialog to check the Default Fee Value
//CP20030311     */
//CP20030311   if( idSearch == -9999 )
//CP20030311   {
//CP20030311      requestAcqFee(idDataGroup);
//CP20030311      return(NO_CONDITION);
//CP20030311   }

   try
   {
	   
	   bool bAWD = _dstrCaller == I_("FromAWD") ? true : false;
	   DString payType = NULL_STRING;
	   DString amount = NULL_STRING;
	   DString amtType = NULL_STRING;
	   
	   if (bAWD)
       { 				
			if (!(_dstrWorkType == MODIFY_PAC || _dstrWorkType == MODIFY_SWP))
			{
				getParameter (I_("Amount"), amount);
				getParameter (I_("AmtType"), amtType);
				payType = I_("E");
			}
	   } 

      DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
      sevRtn = dstcWorkSession->getMFAccount( idDataGroup, _dstrAccountNum, _pMFAccount, I_("N"), NULL_STRING, true, true); 
      if( sevRtn > WARNING )
         return(sevRtn);
      setContainer(IFASTBP_PROC::MFACCOUNT_CBO, _pMFAccount);

      /**
       * Address List
      */
      _pMFAccount->getField(ifds::ShrNum, _dstrShrNum, idDataGroup, false);
      _dstrShrNum.strip();
      setGlobal( WORK_GLOBAL, ifds::LastActiveShrNum, _dstrShrNum );

      //shareholder cbo
      sevRtn = dstcWorkSession->getShareholder( idDataGroup, _dstrShrNum, _pShareholder);
      if( sevRtn > WARNING )
         return(sevRtn);

      //entity list
      sevRtn = dstcWorkSession->getAccountEntityXref(  idDataGroup, _pAccountEntityXref );
      if( sevRtn > WARNING )
         return(sevRtn);

      getEntityName( getDataGroupId(), _dstrAccountNum, _dstrEntityName);

      //address list
      sevRtn = _pShareholder->getAddressList( _pAddressList, idDataGroup );
      if( sevRtn > WARNING )
         return(sevRtn);

      setContainer(IFASTBP_PROC::ADDRESS_LIST, _pAddressList);

      /**
       * TODO register CBO with base - This code was not used
       *         setCBOInstance( MFACCOUNT_CBO, _pMFAccount );
       *      else 
       */
      sevRtn = _pMFAccount->getSystematicList( _pSystematicList, idDataGroup, true, payType, amount, amtType );
      if( sevRtn <= WARNING )
      {

         setContainer(IFASTBP_PROC::SYSTEMATIC_LIST, _pSystematicList);

         /**
           * In order to set the Default TransType for the newly created record
           */
         if( _pSystematicList )
            _pSystematicList->setTransType(_dstrTransType);

         BFObjIter iter(*_pSystematicList, idDataGroup);
         _pSystematic = NULL;
         if( iter.getNumberOfItemsInList() > 0 )
         {
            _pSystematic = static_cast <Systematic *>(iter.getObject());

            SysAllocationList *pSysAllocList;
            sevRtn1 = _pSystematic->getSysAllocationList(pSysAllocList);

            sevRtn = max(sevRtn, sevRtn1);
            if( sevRtn < WARNING )
               setContainer(IFASTBP_PROC::SYSALLOCATION_LIST, pSysAllocList);

            /*initialize all systematic cbo     // Already done by SysetmaticList
            BFObjIter iter1(*_pSystematicList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
            while ( !iter1.end() )
            {
               if ( !iter1.isDummy() )
               {
                  Systematic* pSystematic = dynamic_cast<Systematic *>(iter1.getObject());
                  pSystematic->init2( idDataGroup, _pSystematicList);
               };
               ++iter1;
            }*/
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
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, PERFORMSEARCH, CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
   return(sevRtn); 
}

//******************************************************************************

void SystematicProcess::setCurrentListItem(const GenericInterface *rpGICaller,
                                           const BFContainerId& idList, const DString& strListItemKey)
{  
   TRACE_METHOD( CLASSNAME, I_( "setCurrentListItem" ) );

   SysAllocationList *pAllocationList;

//CP20030319   switch( idList )
//CP20030319   {
//CP20030319      case SYSTEMATICLIT::SYSTEMATIC_LIST:
   if( IFASTBP_PROC::SYSTEMATIC_LIST == idList )
   {
      {
         _pSystematic = static_cast<Systematic *>(_pSystematicList->getObject(strListItemKey, getDataGroupId()));


         _pSystematic->getSysAllocationList(pAllocationList);
         //if ( pAllocationList )
         setContainer(IFASTBP_PROC::SYSALLOCATION_LIST, pAllocationList );
         //else
         //assert(0);

         _pSystematic->getAtAcctAllocationList(_pAtAcctTransAllocationList);
         //if ( _pAtAcctTransAllocationList )
         //{
         //BFObjIter iter(*_pAtAcctTransAllocationList,BF::HOST);
         //int jj = iter.getNumberOfItemsInList();
         setContainer(IFASTBP_PROC::AT_ACCOUNT_ALLOCATIONLIST, _pAtAcctTransAllocationList );
         /*} else
         {
            assert(0);
         }*/

         /*DString strTransType;
   
         _pSystematic->getField(DBR::TransType, strTransType, getDataGroupId(), false);
         strTransType.strip().upperCase();
            
         if ( strTransType != I_( "AT" ) )
         {
           _pSystematic->getSysAllocationList(pAllocationList);
           if (pAllocationList)
             setContainer(SYSALLOCATION_LIST, pAllocationList );
           else
             assert(0);
         }
         else
         {
           _pSystematic->getAtAcctAllocationList(_pAtAcctTransAllocationList);
           if (_pAtAcctTransAllocationList)
           {
             BFObjIter iter(*_pAtAcctTransAllocationList,BF::HOST);
             int jj = iter.getNumberOfItemsInList();
             setContainer(SYSTEMATICLIT::AT_ACCOUNT_ALLOCATIONLIST, _pAtAcctTransAllocationList );
           }
           else
           {
             assert(0);
           }
         }*/
      }
//CP20030319         break;

//CP20030319      case SYSTEMATICLIT::AT_ACCOUNT_ALLOCATIONLIST:
   }
   else if( IFASTBP_PROC::AT_ACCOUNT_ALLOCATIONLIST == idList )
   {
      {
         Systematic *pSystematic = dynamic_cast< Systematic * >( getCBOItem(
                                                                           IFASTBP_PROC::SYSTEMATIC_LIST, getDataGroupId()) );
         pSystematic->getAtAcctAllocationList(_pAtAcctTransAllocationList);
         BFObjIter iter(*_pAtAcctTransAllocationList,getDataGroupId());
         int jj = iter.getNumberOfItemsInList();

         AutoAcctTransAllocation*   _pAcctTransAllocation;
         _pAcctTransAllocation =  static_cast<AutoAcctTransAllocation *>(_pAtAcctTransAllocationList->getObject(strListItemKey, getDataGroupId()));
         if( _pAcctTransAllocation )
         {
            _pAcctTransAllocation->getAtAllocationList(_pAutoTransAllocationList);
            if( _pAutoTransAllocationList )
               setContainer(IFASTBP_PROC::AT_FUND_ALLOCATIONLIST, _pAutoTransAllocationList );
            else
               assert(0);
         }
      }
//CP20030319         break;

//CP20030319      case SYSALLOCATION_LIST:
   }
   else if( IFASTBP_PROC::SYSALLOCATION_LIST == idList )
   {
//CP20030319         break;
//CP20030319   }
   }
   AbstractProcess::setCurrentListItem(rpGICaller, idList, strListItemKey);
   return;
}

//******************************************************************************

void SystematicProcess::requestAcqFee(const BFDataGroupId& idDataGroup)
{
   MAKEFRAME2( CND::BPBASE_CONDITION, CLASSNAME, I_("confirmAcqFee") );

   if( !_pSystematic )
      return;

   SEVERITY sevRtn = _pSystematic->getAcqFeeInquiry(_pAcqFeeInquiry, idDataGroup);
   DString dstrFeeDisableFlag = _pSystematic->getFeeDisableFlag();
   if( dstrFeeDisableFlag == YES )
   {
      DString tmp;
      _pSystematic->getField(ifds::Fee, tmp, idDataGroup, false);

      if( atof(tmp.asA().c_str()) != 0 && !_pAcqFeeInquiry )
         _pSystematic->setField(ifds::Fee, I_("0"), idDataGroup);
      return;
   }
}


//******************************************************************************
bool SystematicProcess::doOk (GenericInterface *rpGICaller)
{
   DString dstrPAC (NO),
      dstrSWP (NO), 
      dstrAT (NO), 
      dstrSavingPlan (NO),
      defaultSAcctAlloc (NO),
      defaultATAcctAlloc (NO),
      lsifPAC (NO);
   const BFDataGroupId &idDataGroup = getDataGroupId();
   DSTCWorkSession* pDSTCWorkSession = 
      dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   
   if (_pSystematicList != NULL)
   {
      BFObjIter iter (*_pSystematicList, idDataGroup, 
         false, BFObjIter::ITERTYPE::NON_DELETED);
      SysAllocationList *pSysAllocationList = NULL;
      AutoAcctTransAllocationList *pAtAcctTransAllocationList = NULL;


      while (!iter.end())
      {
         if (!iter.isDummy())
         {
            Systematic *pSystematic = 
               dynamic_cast<Systematic *>(iter.getObject());
            DString transType;

            pSystematic->getField (ifds::TransType, transType, 
               idDataGroup, false);
            transType.strip();      
            if (transType == TRADETYPE::AUTO_TRANSFER)
            {
               dstrAT = YES;
            }
            else if (transType == TRADETYPE::PAC)
            {
               dstrPAC = YES;

               DString fundCode, 
                  classCode;

//only if the lsif pac flag is no, check whether the current PAC is an LSIF one
               if (lsifPAC == NO) 
               {
                  pSystematic->getField (ifds::FundCode, fundCode, 
                     idDataGroup, false);
                  pSystematic->getField (ifds::ClassCode, classCode, 
                     idDataGroup, false);
                  if (!fundCode.empty() && !classCode.empty() &&
                     _pFundMasterList->isLSIFFund (fundCode))
                  {
                     lsifPAC = YES;
                  }
                  else if (fundCode.empty() &&
                     classCode.empty())
                  {
                     //check if there is allocated LSIF fund
                     if (pSystematic->getSysAllocationList (pSysAllocationList) <= WARNING && 
                        pSysAllocationList)
                     {
                        BFObjIter iter (*pSysAllocationList, idDataGroup);

                        while (!iter.end())
                        {
                           DString _fundCode;

                           iter.getObject()->getField (ifds::FundCode, fundCode, 
                              idDataGroup, false);
                           if (_pFundMasterList->isLSIFFund (fundCode))
                           {
                              lsifPAC = YES;
                              break;
                           }
                           ++iter;
                        }
                     }
                  }
//check whether the PAC is either bad or inactive
                  if (lsifPAC == YES)
                  {
                     DString stopDate,
                        curBusDate,
                        goodBad;

                     pSystematic->getField (ifds::StopDate, stopDate, idDataGroup, false);
                     pSystematic->getField (ifds::StatusCode, goodBad, idDataGroup, false);
                     goodBad.strip().upperCase();
                     pDSTCWorkSession->getDateInHostFormat (
                        curBusDate,
                        DSTCWorkSession::DATE_TYPE::CURRENT_BUSINESS_DAY, 
                        idDataGroup);
                     lsifPAC = 
                        goodBad == YES &&
//stop date should be greater then current business date for the PAC to be inactive
                        (DSTCommonFunctions::CompareDates (curBusDate, stopDate) == 
                              DSTCommonFunctions::FIRST_EARLIER ||
                         DSTCommonFunctions::CompareDates (curBusDate, stopDate) == 
                              DSTCommonFunctions::EQUAL) ? YES : NO;
                  }
               }
            }
            else if (transType == TRADETYPE::SWP)
            {
               dstrSWP = YES;
            }
            else if (transType == TRADETYPE::SAVING_PLAN)
            {
               dstrSavingPlan = YES;
            }
            if (pSystematic->getSysAllocationList (pSysAllocationList) <= WARNING && 
               pSysAllocationList)
            {
               pSysAllocationList->GetSplitCommList (idDataGroup);
               if (transType == TRADETYPE::PAC || 
                  transType == TRADETYPE::SWP)
               {
                  pSysAllocationList->getField (ifds::ReplaceAsDefault, 
                     defaultSAcctAlloc, idDataGroup, false);
               }
            }
            if (transType == TRADETYPE::AUTO_TRANSFER)
            {
               if (pSystematic->getAtAcctAllocationList (pAtAcctTransAllocationList) <= WARNING && 
                  pAtAcctTransAllocationList)
               {
                  pAtAcctTransAllocationList->getField (ifds::ReplaceAsDefault, 
                     defaultATAcctAlloc, idDataGroup, false);
               }
            }
         }
         ++iter;
      }
   }

   MFAccount *pMFAccount = NULL;
   if (pDSTCWorkSession->getMFAccount (idDataGroup, 
      _dstrAccountNum, pMFAccount) <= WARNING && pMFAccount)
   {
      pMFAccount->setField (ifds::PAC, dstrPAC, idDataGroup, false);
      pMFAccount->setField (ifds::SWP, dstrSWP, idDataGroup, false);
      pMFAccount->setField (ifds::SystemTrsfr, dstrAT, idDataGroup, false);
      pMFAccount->setField (ifds::SavePlanExist, dstrSavingPlan, idDataGroup, false);
      pMFAccount->setField (ifds::LSIFPAC, lsifPAC, idDataGroup, false);
      if (defaultSAcctAlloc == YES || defaultATAcctAlloc == YES)
      {
         pMFAccount->setField (ifds::AcctAlloc, YES, idDataGroup, false);
         //remove the default allocation list from the shareholder to force a view call
         DString shrNum;
         Shareholder *pShareholder = NULL;

         pMFAccount->getField (ifds::ShrNum, shrNum, idDataGroup, false);
         //retrieve the shareholder pointer
         if (pDSTCWorkSession->getShareholder (idDataGroup, 
            shrNum, pShareholder) <= WARNING && pShareholder)
         {
            //blow the default allocation list, this will force at refresh a view call
            BFObjIter iter (*pShareholder, idDataGroup);

            iter.positionByKey (I_ ("AllocationList"));
            if (!iter.end ())
            {
               iter.removeObjectFromMap (true);
			}
		 }
	  }
   }

   //ticket 2404299 (REG_RL11.2/101 - PAC set up and delete issues)
   SEVERITY sevRtn = NO_CONDITION;

   if (_pSystematicList)
   {
	   SysAllocationList *pSysAllocList;
	   // getSysAllocationList does not raised any error although the 
	   // transtype is AT, which the SysAllocationList is not applicable.
	   // Instead it assigns the NULL value to the input object.
	   if( _pSystematic->getSysAllocationList(pSysAllocList) <= WARNING &&
		   pSysAllocList )
	   {
		   sevRtn = pSysAllocList->validateAll(idDataGroup);
		   //throw all errors
		   if( sevRtn > WARNING && !bfutil::isServerContext() )
		   {	  
			   rpGICaller->send( rpGICaller, I_( "ListAllErrors" ) );
		   }
	   }
   }
	  
   return true;
}

//******************************************************************************

void SystematicProcess::getEntityName( const BFDataGroupId& idDataGroup, DString& AcctNum, DString &EntityName)
{
   DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());
   dstcWorkSession->getFirstSequenced01AccountholderEntityName( idDataGroup, AcctNum, EntityName);
}

//******************************************************************************

void *SystematicProcess::getPtrForContainer(
                                           const BFContainerId& idContainer,
                                           const BFDataGroupId& idDataGroup
                                           )
{
   void *ptr = NULL;

   SEVERITY sevRtn = NO_CONDITION;
   DSTCWorkSession* dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());

   MgmtCo &mgmtCoOut = dstcWorkSession->getMgmtCo( );
   try
   {
//CP20030319      switch( idContainer )
//CP20030319      {
//CP20030319         case FUND_MASTER_LIST:
      if( IFASTBP_PROC::FUND_MASTER_LIST == idContainer )
      {
         {  
            sevRtn = mgmtCoOut.getFundMasterList(_pFundMasterList);
            if( sevRtn <= WARNING )
               ptr = _pFundMasterList;
         }
//CP20030319            break;

//CP20030319         case FUND_DETAIL_LIST:
      }
      else if( IFASTBP_PROC::FUND_DETAIL_LIST == idContainer )
      {
         {  
            sevRtn = mgmtCoOut.getFundDetailList(_pFundDetailList);
            if( sevRtn <= WARNING )
               ptr = _pFundDetailList;
         }
//CP20030319            break;

//CP20030319         case MFACCOUNT_CBO:
      }
      else if( IFASTBP_PROC::MFACCOUNT_CBO == idContainer )
      {
         {  
            sevRtn = dstcWorkSession->getMFAccount(
                                                  idDataGroup, _dstrAccountNum, _pMFAccount );
            if( sevRtn <= WARNING )
            {
               ptr = _pMFAccount;
               //setting the last active account number as global
               setGlobal( WORK_GLOBAL, ifds::LastActiveAccountNum, _dstrAccountNum );
               // get shrholder num for later use
               _pMFAccount->getField(ifds::ShrNum, _dstrShrNum, idDataGroup);
               _dstrShrNum.strip().stripLeading( I_CHAR( '0' ) );
               setGlobal( WORK_GLOBAL, ifds::LastActiveShrNum, _dstrShrNum );
            }
         }
//CP20030319            break;

//CP20030319         case SYSTEMATICLIT::SYSTEMATIC_LIST:
      }
      else if( IFASTBP_PROC::SYSTEMATIC_LIST == idContainer )
      {
         {
            sevRtn = _pMFAccount->getSystematicList( _pSystematicList, idDataGroup );
            if( sevRtn <= WARNING )
               ptr = _pSystematicList;
         }
//CP20030319            break;

//CP20030319         case SYSALLOCATION_LIST:
      }
      else if( IFASTBP_PROC::SYSALLOCATION_LIST == idContainer )
      {
         {
            if( _pSystematic )
            {
               SysAllocationList *pSysAllocList;
               sevRtn = _pSystematic->getSysAllocationList(pSysAllocList);
               if( sevRtn <= WARNING )
                  ptr = pSysAllocList;
            }
         }
//CP20030319            break;
//CP20030319         case SYSTEMATICLIT::AT_ACCOUNT_ALLOCATIONLIST:
      }
      else if( IFASTBP_PROC::AT_ACCOUNT_ALLOCATIONLIST == idContainer )
      {
         {
            Systematic *pSystematic = dynamic_cast< Systematic * >( getCBOItem(
                                                                              IFASTBP_PROC::SYSTEMATIC_LIST, idDataGroup ) );
            if( !pSystematic )
               assert( 0 );

            pSystematic->getAtAcctAllocationList( _pAtAcctTransAllocationList );
            if( !_pAtAcctTransAllocationList )
               assert( 0 );
            ptr = _pAtAcctTransAllocationList;
         }
//CP20030319            break;
//CP20030319         case SYSTEMATICLIT::AT_FUND_ALLOCATIONLIST:
      }
      else if( IFASTBP_PROC::AT_FUND_ALLOCATIONLIST == idContainer )
      {
         {
            AutoAcctTransAllocation *pAcAcctTrans = dynamic_cast< AutoAcctTransAllocation * >( getCBOItem(
                                                                                                         IFASTBP_PROC::AT_ACCOUNT_ALLOCATIONLIST, idDataGroup ) );
            if( !pAcAcctTrans )
               assert( 0 );

            pAcAcctTrans->getAtAllocationList( _pAutoTransAllocationList );
            if( !_pAutoTransAllocationList )
               assert( 0 );
            ptr = _pAutoTransAllocationList;
         }

//CP20030319            break;

//CP20030319         case ADDRESS_LIST:
      }
      else if( IFASTBP_PROC::ADDRESS_LIST == idContainer )
      {
         {  
            sevRtn = dstcWorkSession->getShareholder( idDataGroup, _dstrShrNum, _pShareholder);
            if( _pShareholder )
            {
               sevRtn = _pShareholder->getAddressList( _pAddressList, idDataGroup );
               if( sevRtn <= WARNING )
                  ptr = _pAddressList;
            }
         }
//CP20030319            break;
//CP20030319      }
      }
   }
   catch( ConditionException & )
   {
      throw;
   }
   catch( ... )
   {
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
// TODO  If severity > warning, throw error returned from above
   return(ptr);
}
//**********************************************************************
SEVERITY SystematicProcess::doValidateAll(BFAbstractCBO *rpWSD, 
   const BFDataGroupId& idDataGroup)
{
   SEVERITY severity = NO_CONDITION;

   if (_pSystematicList)
   {
      //validate the systematic list
      severity = _pSystematicList->validateAll(idDataGroup);
   }
   return severity;
}

//******************************************************************************************
bool SystematicProcess::doSend( GenericInterface *rpGICaller, const I_CHAR * szMessage )
{
   bool valRtn = true;
   DString dstr(szMessage);
   if( SYSTEMATICLIT::MULTI_ALLOCATION == dstr )
   {

      Systematic *pSystematic = dynamic_cast< Systematic * >( getCBOItem(
                                                                        IFASTBP_PROC::SYSTEMATIC_LIST, getDataGroupId()) );

      pSystematic->CheckAmountTypeForPACSWPMultiAllocation(getDataGroupId() );
   }
   else
   {
      valRtn = AbstractProcess::doSend( rpGICaller, szMessage );
   }

   return(valRtn);



}

//******************************************************************************
SEVERITY SystematicProcess::getHistoricalParameters(const BFContainerId& idContainer, 
                                                    BFFieldId &recordIdField, DString& tableId,
                                                    DString& dstrKeys) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS );

   if( idContainer == IFASTBP_PROC::SYSTEMATIC_LIST )
   {
      DString dstrSystematicPayType;
	  _pSystematic->getField(ifds::SystematicPayType, dstrSystematicPayType, getDataGroupId(), false);

	  tableId = (dstrSystematicPayType.strip() == I_("AT") )? 
				AUDITTYPE::ATF: 
				AUDITTYPE::BKD;

	  recordIdField = ifds::PACSWPId;
      dstrKeys = NULL_STRING;
   }
   else
   {
      assert(0);
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY SystematicProcess::getHistoricalParameters( 
   const BFContainerId& idContainer, 
   HISTORICAL_VECTOR &vectorHistorical )
{
   MAKEFRAMEAUTOPROMOTE2(CND::BPBASE_CONDITION, CLASSNAME, GETHISTORICALPARAMETERS);
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/SystematicProcess.cpp-arc  $
 * 
 *    Rev 1.91   Jul 26 2012 10:33:48   wp040027
 * P0198518 - RDR Functionality
 * 
 *    Rev 1.90   May 13 2012 16:56:50   if991250
 * CPF - PAC
 * 
 *    Rev 1.89   May 11 2012 09:42:12   if991250
 * added VerifyStat and NonFinConfirms attributes
 * 
 *    Rev 1.88   Mar 23 2012 10:44:44   if991250
 * IN  2885402 - PAC-EFT Systematic readonly for active commitments, Added Insured and Policy number
 * 
 *    Rev 1.87   Jan 11 2012 15:28:52   dchatcha
 * IN# 2796443 - Validation rule for Allocated Auto Transfer
 * 
 *    Rev 1.86   May 23 2011 02:34:52   wutipong
 * IN2375406 - Unknown error when modifying an Auto Transfer setup.
 * 
 *    Rev 1.85   Feb 27 2011 20:48:56   panatcha
 * ticket 2404299 (REG_RL11.2/101 - PAC set up and delete issues)
 * 
 *    Rev 1.84   Jan 12 2011 02:33:12   wutipong
 * IN2310764 - Historical screen with wrong display in PAC and Auto Transfer
 * 
 *    Rev 1.83   Nov 25 2010 13:56:22   jankovii
 * PET175778FN01 - Upstreaming Phase 2
 * 
 *    Rev 1.82   Nov 06 2008 01:59:08   daechach
 * PET5517 FN71 Unclaimed Property Phase 2
 * 
 *    Rev 1.81   Feb 14 2006 14:10:00   porteanm
 * Incident 543959 - Two lines of instructions (Pay Reason).
 * 
 *    Rev 1.80   Jan 04 2005 11:13:34   yingbaol
 * PTS10036915:Add Field WHTaxApply and FileProcessorApply
 * 
 *    Rev 1.79   Nov 14 2004 14:22:54   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.78   Oct 27 2004 10:36:32   VADEANUM
 * PET 1010 FN02 CCB 1383 - WHTax for Registered Accts on SWPs.
 * 
 *    Rev 1.77   Sep 07 2004 15:10:52   VADEANUM
 * PET 1094 FN4 - Activest Bank File Interface.
 * 
 *    Rev 1.76   Jun 24 2004 10:45:44   popescu
 * PTS 10031689, LSIFPAC field on the account should be set to N (No) if the PAC with LSIF is marked as 'bad' or is not active. (stop date is greater then current business date).
 * 
 *    Rev 1.75   May 25 2004 20:31:22   popescu
 * PET 985, fn 01, check the allocation list to see whether an allocated PAC with LSIF exists
 * 
 *    Rev 1.74   May 25 2004 18:09:42   popescu
 * PET 985, fn01, Shareholder tax jurisdiction refresh
 * 
 *    Rev 1.73   Mar 10 2004 13:20:52   HERNANDO
 * PET965 FN11 - Added getHistoricalParameters.
 * 
 *    Rev 1.72   Mar 09 2004 13:27:24   popescu
 * PTS 10027315, refresh the default allocation flag after adding a PAC/SWP with 'replace as default' check box set
 * 
 *    Rev 1.71   Aug 18 2003 16:10:44   HERNANDO
 * Added keys to getHistoricalParameters.
 * 
 *    Rev 1.70   Jun 11 2003 13:18:00   popescu
 * Removed unecessary GEtSplitCommissionList from the AutAccTransAllocationList level
 * 
 *    Rev 1.69   May 06 2003 14:51:36   popescu
 * validation was called twice for a child list of the systematic list
 * 
 *    Rev 1.68   Apr 03 2003 13:46:16   linmay
 * clean up for sec
 * 
 *    Rev 1.67   Mar 21 2003 19:32:24   PURDYECH
 * Sync 1.65.1.0 back to trunk
 * 
 *    Rev 1.65.1.0   Mar 21 2003 17:48:52   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.65   Mar 11 2003 13:49:56   PURDYECH
 * Fixes to help the DataGroupId source code converters work more smoothly.
 * 
 *    Rev 1.64   Mar 09 2003 15:56:46   PURDYECH
 * Small fixes around DataGroupIds and ContainerIds.
 * 
 *    Rev 1.63   Mar 05 2003 11:22:58   PURDYECH
 * IFastBaseProcess no longer exists.  Classes now derive from AbstractProcess (again) and the Protocol class IFastHistoricalParameters.
 * 
 *    Rev 1.62   Feb 05 2003 12:06:56   popescu
 * Changes related to adding a new audit type id, for PAC/SWP and testing the FeeParam/Sys Historical button
 * 
 *    Rev 1.61   Jan 29 2003 18:50:26   WINNIE
 * Disable delete button for DCAF automatic Transfer
 * 
 *    Rev 1.60   Jan 29 2003 14:57:04   popescu
 * Added Historical button for Systematic
 * 
 *    Rev 1.59   Jan 18 2003 17:13:48   WINNIE
 * Correct field name for batch: sync up update and inquiry view. Add display of BatchName and BatchTrace for Systematic
 * 
 *    Rev 1.58   Jan 09 2003 10:45:54   FENGYONG
 * validate account number when get mfaccount
 * 
 *    Rev 1.57   Oct 09 2002 23:53:40   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.56   Aug 29 2002 16:45:16   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.55   Aug 29 2002 12:54:42   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.54   Jul 18 2002 16:05:14   YINGBAOL
 * make MFCAN_CBO not updateable
 * 
 *    Rev 1.53   Jul 17 2002 14:26:26   KOVACSRO
 * Added Name field, to use for TO accountholder name.
 * 
 *    Rev 1.52   Jun 03 2002 16:55:38   HSUCHIN
 * bug fix to doValidateAll to use BFAbstractCBO rather than BFCBO
 * 
 *    Rev 1.51   Jun 03 2002 16:42:26   FENGYONG
 * Add name for API
 * 
 *    Rev 1.50   22 May 2002 18:25:06   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.49   27 Mar 2002 19:55:44   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.48   11 Feb 2002 16:09:38   KOVACSRO
 * PTS 10007115. Allocations were not working fine when changing between AT and other trans. types.
 * 
 *    Rev 1.47   Aug 27 2001 09:50:12   YINGBAOL
 * fix paytype issue
 * 
 *    Rev 1.46   Aug 23 2001 09:36:58   YINGBAOL
 * check acquisition fee default
 * 
 *    Rev 1.45   22 Aug 2001 11:47:32   WINNIE
 * Code clean up
 * 
 *    Rev 1.44   Aug 17 2001 10:33:38   YINGBAOL
 * fix bug
 * 
 *    Rev 1.43   Aug 09 2001 10:26:08   YINGBAOL
 * transfer enhancement
 * 
 *    Rev 1.42   07 Aug 2001 14:03:24   HSUCHIN
 * Beautified source and set LastActiveShr Num bug fix for Indexing and other sub dialogs from systematic.
 * 
 *    Rev 1.41   Jul 29 2001 15:09:48   YINGBAOL
 * fix validateall issue( validateall should only be done for those nondelete items.)
 * 
 *    Rev 1.40   16 Jul 2001 15:01:38   YINGZ
 * add substitution PACSWPFrequency
 * 
 *    Rev 1.39   04 Jul 2001 18:42:22   WINNIE
 * add saving plan flag
 * 
 *    Rev 1.38   28 Jun 2001 13:41:30   YINGZ
 * not delete all sysalloc when changing from multiple to single fund alloc
 * 
 *    Rev 1.37   21 Jun 2001 11:08:26   KOVACSRO
 * moved logic for month indicator into CBO
 * 
 *    Rev 1.36   Jun 15 2001 13:37:10   ZHANGCEL
 * Added two new field: ExchInFee and ExchInFlatPercent
 * 
 *    Rev 1.35   05 Jun 2001 16:06:02   YINGZ
 * for others to compile
 * 
 *    Rev 1.34   31 May 2001 11:15:18   YINGZ
 * check in for Chin
 * 
 *    Rev 1.33   25 May 2001 15:07:58   YINGZ
 * just save a copy
 * 
 *    Rev 1.32   17 May 2001 09:42:20   YINGZ
 * paytype fix
 * 
 *    Rev 1.31   15 May 2001 15:38:56   YINGZ
 * data group id clean up
 * 
 *    Rev 1.30   14 May 2001 13:58:14   YINGZ
 * code sync up
 * 
 *    Rev 1.29   May 14 2001 11:15:54   DINACORN
 * Added DBR::BankIdTypeDisplay dummy field
 * 
 *    Rev 1.28   Apr 23 2001 15:10:26   HERNANDO
 * Added NextProcessDate.
 * 
 *    Rev 1.27   19 Apr 2001 12:11:00   KOVACSRO
 * Changed InstCode with BankIdValue.
 * 
 *    Rev 1.26   14 Apr 2001 11:07:06   HSUCHIN
 * force the retrieval of Split Commission List on OK so validate of the list can occur
 * 
 *    Rev 1.25   06 Apr 2001 18:58:12   BUZILAMI
 * fix
 * 
 *    Rev 1.24   Apr 06 2001 17:16:50   YINGZ
 * make group id work
 * 
 *    Rev 1.23   04 Apr 2001 11:17:20   BUZILAMI
 * Systematic Bank fixes
 * 
 *    Rev 1.22   Mar 20 2001 15:42:36   HSUCHIN
 * added SplitComm flag to field details
 * 
 *    Rev 1.21   Feb 23 2001 13:47:38   YINGBAOL
 * introduce systematicPayType
 * 
 *    Rev 1.20   Jan 17 2001 12:08:12   VASILEAD
 * Added workSessionId param for MgmtCo::getMgmtCoOptions()
 * 
 *    Rev 1.19   15 Dec 2000 12:43:54   PURDYECH
 * Use precompiled header stdafx.h.
 * Removed unnecessary header files.
 * 
 *    Rev 1.18   Nov 02 2000 14:11:34   VASILEAD
 * Added workSeesionId parameter for Mgmtco based CBOs
 * 
 *    Rev 1.17   Sep 29 2000 13:26:06   YINGZ
 * change market from cfds - canada to canada
 * 
 *    Rev 1.16   Sep 26 2000 16:15:46   WINNIE
 * Bug fix for not able to get out of systematic screen, initization is missing
 * 
 *    Rev 1.15   Sep 24 2000 10:38:26   HUANGSHA
 * changed GetMyDatagroup() to getReadOnlyGroupID(..) in performsearch
 * 
 *    Rev 1.14   Sep 11 2000 10:39:30   YINGBAOL
 * change validate all
 * 
 *    Rev 1.13   Aug 02 2000 15:32:04   BUZILA
 * "locale" changes
 * 
 *    Rev 1.12   Jul 11 2000 13:42:42   YINGBAOL
 * add Fund Number logic
 * 
 *    Rev 1.11   Jun 30 2000 14:31:16   HUANGSHA
 * validate all only for non-dummy record
 * 
 *    Rev 1.10   Jun 30 2000 10:23:20   YINGBAOL
 * fix addcopy bugs
 * 
 *    Rev 1.9   Jun 27 2000 09:54:34   YINGBAOL
 * change frequency logic
 * 
 *    Rev 1.8   May 19 2000 17:12:40   HUANGSHA
 * Removed the Market Conditions for AT
 * 
 *    Rev 1.7   May 01 2000 09:42:32   YINGBAOL
 * add automatic transfer
 * 
 *    Rev 1.6   Apr 17 2000 17:16:06   YINGZ
 * add AddCopy function for systematic
 * 
 *    Rev 1.5   Apr 17 2000 11:24:22   YINGBAOL
 * fix M3 crash problem
 * 
 *    Rev 1.4   Apr 05 2000 14:17:14   HSUCHIN
 * more M2 sync up
 * 
 *    Rev 1.3   Apr 04 2000 10:47:40   YINGBAOL
 * M2 Sync.
 * 
 *    Rev 1.2   Mar 19 2000 10:36:04   HSUCHIN
 * C2 sync up
 * 
 *    Rev 1.1   Mar 06 2000 15:35:14   DT24433
 * removed substitute lists
 * 
 *    Rev 1.0   Feb 15 2000 10:59:38   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.37   Feb 09 2000 12:13:34   HUANGSHA
 * check in for release
 * 
 *    Rev 1.36   Feb 02 2000 18:09:40   BUZILA
 * changes
 * 
 *    Rev 1.35   Feb 02 2000 17:22:38   HUANGSHA
 * added getPrtForContainer()
 * 
 *    Rev 1.34   Feb 02 2000 14:00:10   BUZILA
 * default dataGroup for BFBase::getObject taken out
 * 
 *    Rev 1.33   Feb 01 2000 11:35:12   BUZILA
 * fix COA flag
 * 
 *    Rev 1.32   Jan 27 2000 15:19:02   HSUCHIN
 * fix for coa flag
 * 
 *    Rev 1.31   Jan 25 2000 10:52:36   BUZILA
 * fix coa flags
 * 
 *    Rev 1.30   Jan 21 2000 14:40:00   BUZILA
 * took out doRefresh
 * 
 *    Rev 1.29   Jan 18 2000 17:45:22   HUANGSHA
 * check in for release
 * 
 *    Rev 1.28   Jan 17 2000 12:03:18   HSUCHIN
 * set last active account on refresh.
 * 
 *    Rev 1.27   Jan 17 2000 11:34:34   HSUCHIN
 * set last active account number
 * 
 *    Rev 1.26   Jan 08 2000 14:33:00   POPESCUS
 * added the datagroupid when quering for children lists
 * 
 *    Rev 1.25   Jan 06 2000 14:56:36   HUANGSHA
 * COA changed
 * 
 *    Rev 1.24   Dec 31 1999 14:57:48   WINNIE
 * change field versionnum to bankdetlver in view#6; change set up for AccountTo
 * 
 *    Rev 1.23   Dec 24 1999 12:10:36   HUANGSHA
 * change the GroupID to getDataGroupId()
 * 
 *    Rev 1.22   Dec 23 1999 12:15:16   HUANGSHA
 * check in for testing
 * 
 *    Rev 1.21   Dec 21 1999 16:48:04   HUANGSHA
 * for testing
 * 
 *    Rev 1.20   Dec 17 1999 18:16:28   HUANGSHA
 * removed the set lists
 * 
 *    Rev 1.19   Dec 16 1999 18:29:42   HUANGSHA
 * Check in for testing
 * 
 *    Rev 1.18   Dec 14 1999 15:34:08   HUANGSHA
 * check in for compiling
 * 
 *    Rev 1.17   Dec 02 1999 17:56:48   POPESCUS
 * Fixed crashes in search
 * 
 *    Rev 1.16   Dec 01 1999 12:56:20   HUANGSHA
 * check in for 2nd release
 * 
 *    Rev 1.15   Nov 27 1999 16:24:36   HUANGSHA
 * check in
 * 
 *    Rev 1.14   Nov 25 1999 15:11:48   HUANGSHA
 * No change.
 * 
 *    Rev 1.13   Nov 25 1999 10:26:00   HUANGSHA
 * check in for test
 * 
 *    Rev 1.12   Nov 24 1999 09:27:42   HUANGSHA
 * check in for test
 * 
 *    Rev 1.11   Nov 15 1999 14:44:00   HUANGSHA
 * temporary check in
 * 
 *    Rev 1.10   Nov 06 1999 15:18:56   VASILEAD
 * Modified view 5,6,11,16,51 and 85
 * 
 *    Rev 1.9   Nov 02 1999 14:15:54   DT24433
 * removed doOk and doCancel
 * 
 *    Rev 1.8   Oct 29 1999 11:30:18   BUZILA
 * changing WorkSessionDetails into a BFBase descendant
 * 
 *    Rev 1.7   Oct 17 1999 11:30:34   POPESCUS
 * added namespace for search
 * 
 *    Rev 1.6   Oct 13 1999 17:30:42   VASILEAD
 * modified PacSwpId tp PACSWPId and SalesrepCode to SalesRepCode
 * 
 *    Rev 1.5   Aug 31 1999 12:05:14   DT24433
 * changed dogetfield parms
 * 
 *    Rev 1.4   Aug 20 1999 09:19:08   DT24433
 * finished removing FieldDetails array
 * 
 *    Rev 1.3   Aug 03 1999 15:05:14   DT24433
 * container changes
 * 
 *    Rev 1.2   Jul 20 1999 11:14:16   VASILEAD
 * New conditions update
 * 
 *    Rev 1.1   Jul 08 1999 10:02:12   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
