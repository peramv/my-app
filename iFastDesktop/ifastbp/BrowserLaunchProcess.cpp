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
// ^FILE   : BrowserLaunchProcess.cpp
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : BrowserLaunchProcess
//    This class sets processes BrowserLaunch.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "browserlaunchprocess.hpp"
#include <ifastcbo\accountentityxref.hpp>
#include <ifastcbo\mfaccount.hpp>

extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_BROWSER_LAUNCH;
extern IFASTBP_LINKAGE const I_CHAR* CMD_GUI_ACCOUNT_DETAILS;

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_BROWSER_LAUNCH;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_PAYMENT_SEARCH;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_TRANS_PAYMENT_SEARCH;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_FUND_CLASS_LIMITATION;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_PAYMENT_BATCH;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_CLONE_ACCOUNT_BROWSER;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_HISTORICAL_PAYMENTS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_MANAGEMENT_FEE_REBATE;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_MANAGEMENT_FEE;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ACCOUNT_BALANCE_OVERRIDE;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_DILUTION_CALCULATOR;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_MANAGEMENT_FEE_REBATE_DETAILS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_MANAGEMENT_FEE_ID;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_AMS_ASSET_INFO;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_DOT_AND_ADDENDUM;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_LIF_GAIN_LOSS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_REGULATORY_STANDARDS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_REGULATORY_DOCUMENTS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_FUND_MASTER;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_FUND_DETAIL;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_RELEASE_FROZEN_ACCOUNT;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_TFSA_CONTRIBUTION_INFO;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_FUND_CLASS_COPY;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ADDRESS_LOOKUP_BROWSER;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ACCOUNT_STATIC_DATA_VERIFY;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_FUND_CLASS_MAINTENANCE;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_TAX_JURIS_HISTORY;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_RESP_ACCOUNT_INFO;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_RESP_NOTIONAL_INFO;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_RESP_GRANTS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_RESP_GRANTS2;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_GRANT_CONTRIB;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_RESP_ACCOUNT_TERMINATION;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ZERO_GRANT_REPAYMENT;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_INTERFACE_FILE;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_RESP_ALLOC_HISTROY;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_TRAILER_FEE_SETUP;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_GOVT_FILING_AMENDMENT;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_SMART_FORM;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_GLOBAL_SEARCH;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_PORTFOLIO_SETUP;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_COMMISSION_REDUCTION;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_INTEREST_MAINTENANCE;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_INTEREST_CONFIGURATION;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_GIA_ATTRIBUTES;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_SEG_ATTRIBUTES;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_SEG_GUARANTEE_RULES;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_RESP_DIPLOMA;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_GUARANTEEINFO_BROWSER;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_SEG_PROCESSING;
extern IFASTBP_LINKAGE const I_CHAR *CMD_BPROC_SHARE_LOT_BROWSER;
extern IFASTBP_LINKAGE const I_CHAR *CMD_BPROC_VALUATION_DETAILS_BROWSER;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_VERSION_FEATURE;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_EVENT_DATE_GEN;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_EVENT_SCH_MAIN;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_TRADE_SCH_MAIN;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_GUARANTEE_FEE;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_FOREIGN_TAX_REVIEW;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ACCT_OWNERSHIP_ALLOCATION;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_REMIT_UNCLM_ACCT;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ACCT_FEE_MODEL_ASSOCIATION;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_SHR_STATEMENT_SCHED;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ACCT_IDENTIFIER;

extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ADDITIONAL_ASSETS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_INVOICE_INSTRUCTION;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_REPORT_GROUP;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ACCOUNT_ASSOCIATION;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_IDENTIFICATION_MAINT;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_FFI_MAINT;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_FUNDGROUP_REGULATORY;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_BROKER_REGULATORY;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_INTERMEDIARY_REGULATORY;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_TRAILER_FEES_INQUIRY;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ACCOUNT_GROUP;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_PRIVATE_WEALTH_INFO;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_PDF_VIEWER;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_TAX_SLIPS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_FATCA_FILING_DETAIL;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ACCOUNT_GROUPING_INFO;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_RESP_NOTIONAL_BALANCE_INFO;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_RESP_NOTIONAL_ACTIVITY;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_FUND_RULES_MAINTENANCE;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_TRANSFER_OF_ACCOUNTS;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_FUND_GROUP;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_FUND_BROKER_LINKAGE;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_SEG_DATES;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_CONTRACT_OVERRIDE;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_INVEST_INFO;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_REGULATORY_AGREEMENT;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_EXTERNAL_TA_FUND_LINKAGE;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_ACCT_DELETION_REVIEW;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_REG_ACCT_EXTR;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_REG_ACCT_INFO_REV;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_WITHHODLDING_TAX_RATES_MAINTANENCE;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_FUND_DISTRIBUTION_SPLIT_MAINTENANCE;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_RDSP_ACCOUNT_INFO;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_RDSP_NOTIONAL_BALANCE;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_RDSP_NOTIONAL_ACTIVITY;
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_RDSP_INTERFACE_TRANSACTIONS;

#include <bfproc\concreteprocesscreator.hpp>
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator1  ( CMD_BPROC_BROWSER_LAUNCH );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator2  ( CMD_BPROC_PAYMENT_SEARCH );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator3  ( CMD_BPROC_TRANS_PAYMENT_SEARCH );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator4  ( CMD_BPROC_FUND_CLASS_LIMITATION );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator5  ( CMD_BPROC_CLONE_ACCOUNT_BROWSER );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator6  ( CMD_BPROC_PAYMENT_BATCH );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator7  ( CMD_BPROC_HISTORICAL_PAYMENTS );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator8  ( CMD_BPROC_MANAGEMENT_FEE_REBATE );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator9  ( CMD_BPROC_MANAGEMENT_FEE );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator10 ( CMD_BPROC_ACCOUNT_BALANCE_OVERRIDE );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator11 ( CMD_BPROC_DILUTION_CALCULATOR );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator12 ( CMD_BPROC_MANAGEMENT_FEE_REBATE_DETAILS );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator13 ( CMD_BPROC_MANAGEMENT_FEE_ID );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator14 ( CMD_BPROC_AMS_ASSET_INFO );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator15 ( CMD_BPROC_DOT_AND_ADDENDUM );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator16 ( CMD_BPROC_LIF_GAIN_LOSS );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator17 ( CMD_BPROC_REGULATORY_STANDARDS );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator18 ( CMD_BPROC_REGULATORY_DOCUMENTS );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator19 ( CMD_BPROC_FUND_MASTER );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator20 ( CMD_BPROC_FUND_DETAIL );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator21 ( CMD_BPROC_RELEASE_FROZEN_ACCOUNT );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator22 ( CMD_BPROC_TFSA_CONTRIBUTION_INFO );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator23 ( CMD_BPROC_FUND_CLASS_COPY );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator24 ( CMD_BPROC_ADDRESS_LOOKUP_BROWSER );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator25 ( CMD_BPROC_ACCOUNT_STATIC_DATA_VERIFY );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator26 ( CMD_BPROC_FUND_CLASS_MAINTENANCE );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator27 ( CMD_BPROC_TAX_JURIS_HISTORY );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator28 ( CMD_BPROC_RESP_ACCOUNT_INFO );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator29 ( CMD_BPROC_RESP_NOTIONAL_INFO );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator30 ( CMD_BPROC_RESP_GRANTS );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator31 ( CMD_BPROC_GRANT_CONTRIB );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator32 ( CMD_BPROC_RESP_ACCOUNT_TERMINATION );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator33 ( CMD_BPROC_ZERO_GRANT_REPAYMENT );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator34 ( CMD_BPROC_INTERFACE_FILE );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator35 ( CMD_BPROC_RESP_ALLOC_HISTROY );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator36 ( CMD_BPROC_TRAILER_FEE_SETUP );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator37 ( CMD_BPROC_GOVT_FILING_AMENDMENT );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator38 ( CMD_BPROC_SMART_FORM );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator39 ( CMD_BPROC_GLOBAL_SEARCH );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator40 ( CMD_BPROC_PORTFOLIO_SETUP );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator41 ( CMD_BPROC_COMMISSION_REDUCTION );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator42 ( CMD_BPROC_INTEREST_MAINTENANCE );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator43 ( CMD_BPROC_INTEREST_CONFIGURATION );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator44 ( CMD_BPROC_GIA_ATTRIBUTES );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator45 ( CMD_BPROC_SEG_ATTRIBUTES );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator46 ( CMD_BPROC_SEG_GUARANTEE_RULES );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator47 ( CMD_BPROC_GUARANTEEINFO_BROWSER );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator48 ( CMD_BPROC_SEG_PROCESSING );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator49 ( CMD_BPROC_SHARE_LOT_BROWSER );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator50 ( CMD_BPROC_VALUATION_DETAILS_BROWSER );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator51 ( CMD_BPROC_VERSION_FEATURE );

static ConcreteProcessCreator< BrowserLaunchProcess > processCreator52 ( CMD_BPROC_EVENT_DATE_GEN ); 
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator53 ( CMD_BPROC_EVENT_SCH_MAIN ); 
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator54 ( CMD_BPROC_TRADE_SCH_MAIN ); 
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator55 ( CMD_BPROC_GUARANTEE_FEE );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator56 ( CMD_BPROC_RESP_DIPLOMA );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator57 ( CMD_BPROC_FOREIGN_TAX_REVIEW );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator58 ( CMD_BPROC_ACCT_OWNERSHIP_ALLOCATION );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator59 ( CMD_BPROC_REMIT_UNCLM_ACCT ); 
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator60 ( CMD_BPROC_ACCT_FEE_MODEL_ASSOCIATION ); 
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator61 ( CMD_BPROC_SHR_STATEMENT_SCHED );

static ConcreteProcessCreator< BrowserLaunchProcess > processCreator62 ( CMD_BPROC_ADDITIONAL_ASSETS);
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator63 ( CMD_BPROC_INVOICE_INSTRUCTION);
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator64 ( CMD_BPROC_REPORT_GROUP);
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator65 ( CMD_BPROC_ACCOUNT_ASSOCIATION);

static ConcreteProcessCreator< BrowserLaunchProcess > processCreator66 ( CMD_BPROC_ACCT_IDENTIFIER );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator67 ( CMD_BPROC_IDENTIFICATION_MAINT );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator68 ( CMD_BPROC_FFI_MAINT );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator69 ( CMD_BPROC_FUNDGROUP_REGULATORY );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator70 ( CMD_BPROC_BROKER_REGULATORY );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator71 ( CMD_BPROC_INTERMEDIARY_REGULATORY );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator72 ( CMD_BPROC_TRAILER_FEES_INQUIRY );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator73 ( CMD_BPROC_ACCOUNT_GROUP);
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator74 ( CMD_BPROC_PRIVATE_WEALTH_INFO);
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator75 ( CMD_BPROC_PDF_VIEWER);
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator76 ( CMD_BPROC_TAX_SLIPS);
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator77 ( CMD_BPROC_FATCA_FILING_DETAIL);
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator78 ( CMD_BPROC_ACCOUNT_GROUPING_INFO);
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator79 ( CMD_BPROC_RESP_NOTIONAL_BALANCE_INFO );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator80 ( CMD_BPROC_RESP_NOTIONAL_ACTIVITY );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator81 ( CMD_BPROC_RESP_GRANTS2 );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator82 ( CMD_BPROC_FUND_RULES_MAINTENANCE );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator83 ( CMD_BPROC_TRANSFER_OF_ACCOUNTS );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator84 ( CMD_BPROC_FUND_GROUP );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator85 ( CMD_BPROC_FUND_BROKER_LINKAGE );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator86 ( CMD_BPROC_SEG_DATES );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator87 ( CMD_BPROC_CONTRACT_OVERRIDE );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator88 ( CMD_BPROC_INVEST_INFO );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator89 ( CMD_BPROC_REGULATORY_AGREEMENT );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator90 ( CMD_BPROC_EXTERNAL_TA_FUND_LINKAGE );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator91 ( CMD_BPROC_ACCT_DELETION_REVIEW );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator92 ( CMD_BPROC_REG_ACCT_EXTR );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator93 ( CMD_BPROC_REG_ACCT_INFO_REV );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator94 ( CMD_BPROC_WITHHODLDING_TAX_RATES_MAINTANENCE );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator95 ( CMD_BPROC_FUND_DISTRIBUTION_SPLIT_MAINTENANCE );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator96 ( CMD_BPROC_RDSP_ACCOUNT_INFO );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator97 ( CMD_BPROC_RDSP_NOTIONAL_BALANCE );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator98 ( CMD_BPROC_RDSP_NOTIONAL_ACTIVITY );
static ConcreteProcessCreator< BrowserLaunchProcess > processCreator99 ( CMD_BPROC_RDSP_INTERFACE_TRANSACTIONS );

#include <bfproc\genericinterfacecontainer.hpp>

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "BrowserLaunchProcess" );
}

namespace CND
{
   extern CLASS_IMPORT const long BP_ERR_UNKNOWN_EXCEPTION;
}

namespace BROWSERLAUNCH
{
   const I_CHAR * const CONFIRMATION      = I_( "LaunchConfirmation" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId LastActiveAccountNum;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

BrowserLaunchProcess::BrowserLaunchProcess( GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: AbstractProcess( pGIC, pGIParent, rCommand )
, _rpChildGI( NULL )
, m_fromScreen( NULL_STRING )
, _bupdateStatus( I_("N") )
, m_acctNum( NULL_STRING )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   addFieldDetails( BROWSERLAUNCH::UPDATE_STATUS, BF::NullContainerId, SUBCLASS_PROCESS );
}

//******************************************************************************

BrowserLaunchProcess::~BrowserLaunchProcess()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   _rpChildGI = NULL;
}

//******************************************************************************
//              Protected Methods
//******************************************************************************
bool BrowserLaunchProcess::doModelessChildComplete(const Command &cmd)
{
   return true;            // All done, ready to be self destructed
}

//******************************************************************************
bool BrowserLaunchProcess::doModelessSetFocus(GenericInterface *rpGICaller)
{  // This is implemented to pass set focus on to child dialog.
   bool bRtn = false;

   if( _rpChildGI && isValidModelessInterface( _rpChildGI ) )
   {
      bRtn = _rpChildGI->modelessSetFocus( rpGICaller );
   }
   return(bRtn);
}

//******************************************************************************
SEVERITY BrowserLaunchProcess::doInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, DOINIT );

   processParameters();

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
E_COMMANDRETURN BrowserLaunchProcess::doProcess()
{  // If we are modal, interaction with the screen will occur before returning
   //  from the invokeCommand, if we are modeless the interactions will occur
   //  between the invokeCommand and when modelessChildComplete is called.
   TRACE_METHOD( CLASSNAME, DOPROCESS );

   setParameter( I_("BrowserTitle"), m_pageName);
   setParameter( I_("from_screen"), m_fromScreen);
   setParameter( I_("UrlParams"), m_urlParams);

   return invokeCommand( this, 
                         CMD_GUI_BROWSER_LAUNCH, 
                         PROC_NO_TYPE,
                         isModal(), 
                         &_rpChildGI );
}

//******************************************************************************
void BrowserLaunchProcess::processParameters()
{
   DString tmparm = NULL_STRING, CurParameter, parameterValue;

   getParameter( I_("BrowserTitle"), m_pageName);
   getParameter( I_("from_screen"), m_fromScreen);
   getParameter( I_("UrlParams"), m_urlParams);
   getParameter( I_("AccountNum"), m_acctNum );
}

//******************************************************************************
SEVERITY BrowserLaunchProcess::doSetField( const GenericInterface *rpGICaller,
                                           const BFContainerId& idContainer,
                                           const BFFieldId& idField,
                                           const BFDataGroupId& idDataGroup,
                                           const DString& strValue,
                                           bool bFormatted)
{
   if (BF::NullContainerId == idContainer && 
       idField == BROWSERLAUNCH::UPDATE_STATUS)
   {
      _bupdateStatus = strValue;
   }
   return NO_CONDITION;
}

//******************************************************************************
bool BrowserLaunchProcess::doSend (GenericInterface * rpGICaller, 
                                   const I_CHAR * szMessage)
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "doSend" ) );

   DString strMessage = szMessage;

   if (strMessage == BROWSERLAUNCH::CONFIRMATION)
   {
      E_COMMANDRETURN eRtn = CMD_FAILURE;

      try
      {
         const BFDataGroupId& idDataGroup = getDataGroupId();
         bool bSuccessFlag = false;

         if (_bupdateStatus == I_("Y"))
         {
            setParameter( I_( "CalledFrom" ), I_("BrowserLaunch") );
            if( CMD_OK != invokeCommand( rpGICaller, CMD_BPROC_CONFIRMATION,
                                         PROC_NO_TYPE, true, NULL))
            {
               DString strOut;

               bSuccessFlag = false;
               PROMOTECONDITIONS();
               getParameter( I_( "TrxnsError" ), strOut );
               if (strOut == I_( "Y" ))
               {
                  rpGICaller->send( this, I_( "TrxnsError" ) );
               }
            }
         }
      }
      catch( ... )
      {
         ADDCONDITIONFROMFILE( CND::BP_ERR_UNKNOWN_EXCEPTION );
         return false;
      }
      if (GETCURRENTHIGHESTSEVERITY() <= WARNING)
      {
        return true;
      }
   }
   return GETCURRENTHIGHESTSEVERITY() <= WARNING;
}

//******************************************************************************
bool BrowserLaunchProcess::confirm (GenericInterface * rpGICaller)
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, I_( "doSend" ) );


   E_COMMANDRETURN eRtn = CMD_FAILURE;
   bool bSuccessFlag = true;
   
   try
   {
      const BFDataGroupId& idDataGroup = getDataGroupId();

      if(_bupdateStatus == I_("Y"))
      {
         setParameter( I_( "CalledFrom" ), I_("BrowserLaunch") );
//in case we have an active account number sent to this page - 
//the account should be reloaded, just in case its data has been impacted by the browser page
         DSTCWorkSession *pDSTCWorkSession = 
            dynamic_cast<DSTCWorkSession *> (getBFWorkSession ());
         assert (pDSTCWorkSession);

         MFAccount* pMFAccount = NULL;

         if ( !m_acctNum.empty() && 
              pDSTCWorkSession->getMFAccount (idDataGroup, m_acctNum, pMFAccount) <= WARNING &&
              pMFAccount)
         {
            pMFAccount->refreshMe (true);
         }
         
         if( CMD_OK != invokeCommand( rpGICaller, CMD_BPROC_CONFIRMATION,
                                     PROC_NO_TYPE, true, NULL ) )
         {
            DString strOut;

            bSuccessFlag = false;
            PROMOTECONDITIONS();
            getParameter( I_( "TrxnsError" ), strOut );
            if( strOut == I_( "Y" ) )
            {
               rpGICaller->send( this, I_( "TrxnsError" ) );
            }
         }
      }
   }
   catch( ... )
   {
      ADDCONDITIONFROMFILE( CND::BP_ERR_UNKNOWN_EXCEPTION );
      return false;
   }
   return bSuccessFlag && GETCURRENTHIGHESTSEVERITY() <= WARNING;
}

//******************************************************************************
void BrowserLaunchProcess::doPostOk ( GenericInterface *rpGICaller,
                                      bool bSuccessFlag)
{
   MAKEFRAMEAUTOPROMOTE2 (CND::BPBASE_CONDITION, CLASSNAME, I_("doPostOk"));
   
   DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *> (getBFWorkSession ());
   BFDataGroupId idDataGroup = getDataGroupId();

   if (bSuccessFlag && getCommand ().getName () == CMD_BPROC_CLONE_ACCOUNT_BROWSER)
   {
      DString newAccountNum;

      getGlobal (WORK_GLOBAL, ifds::LastActiveAccountNum, newAccountNum);
      newAccountNum.strip().stripLeading( '0' );
      if (!newAccountNum.empty())
      {
         AccountEntityXref *pAccountEntityXref (NULL);

         if (pDSTCWorkSession->getAccountEntityXref (idDataGroup, pAccountEntityXref) <= WARNING)
         {
            pAccountEntityXref->PopulateEntitiesList (idDataGroup, newAccountNum);
         }
      }
   }   
}

//******************************************************************************
//              Private Methods
//******************************************************************************

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/BrowserLaunchProcess.cpp-arc  $
// 
//    Rev 1.52   Aug 10 2012 12:17:18   popescu
// IN#3051211 - P0179630 FN01 - FATCA - Acct Ownership Allocation option is not refreshed
// 
//    Rev 1.51   Aug 10 2012 12:13:30   popescu
// IN#3051211 - P0179630 FN01 - FATCA - Acct Ownership Allocation option is not refreshed
// 
//    Rev 1.50   Aug 09 2012 14:14:42   dchatcha
// IN#3051211 - P0179630 FN01 - FATCA - Acct Ownership Allocation option is not refreshed
// 
//    Rev 1.49   Jul 20 2012 23:23:38   dchatcha
// P0179630 FN01 FATCA Project - Foriegn Tax Review, Acct Ownership Allocation
// 
//    Rev 1.48   Feb 15 2012 12:25:10   if991250
// RESP Diploma Desktop Web
// 
//    Rev 1.47   Feb 01 2012 15:33:46   dchatcha
// P0184684 FN02 - Guarantee Fee Screen
// 
//    Rev 1.46   Jan 23 2012 23:57:04   panatcha
// P0188394 - iFast Performance Fee
// 
//    Rev 1.45   Jan 19 2012 12:23:30   dchatcha
// P0186484 - FN 05 - Activate Feature Option button on contract information screen
// 
//    Rev 1.44   Jan 18 2012 17:29:54   wp040027
// P0188394_Performance Fees - Launching valuation dtl/Sharelot Screens
// 
//    Rev 1.43   Jan 16 2012 14:07:34   dchatcha
// P0186484 - FN 05 - SEG Processing Screen
// 
//    Rev 1.42   Nov 17 2011 14:17:34   popescu
// INA - called Guarante Info Browser screen
// 
//    Rev 1.41   Oct 28 2011 19:14:40   dchatcha
// P0181953 FN01 - TFSA Amendment - revise account refreshing logic.
// 
//    Rev 1.40   Oct 19 2011 23:32:24   popescu
// SEG - Configuration  S1 (SEG and Desktop skeleton)
// 
//    Rev 1.39   Sep 16 2011 11:41:38   dchatcha
// P0181953 FN01 - TFSA Amendment - Remove specific interprocess parameter passing.
// 
//    Rev 1.38   Aug 04 2011 11:30:58   dchatcha
// P0186477 FN01 - GIA Enhancements
// 
//    Rev 1.37   Jul 29 2011 11:10:50   dchatcha
// Synch up: P0181953 FN01 - TFSA Amendment- integration test, bring code change in branch to trunk.
// 
//    Rev 1.36   Jul 28 2011 11:34:58   jankovii
// PET186484 FN01- Global Search.
// 
//    Rev 1.35   Mar 16 2011 15:54:42   jankovii
// PET 179563 FN01 - Smart Forms
// 
//    Rev 1.34   Jan 14 2011 16:44:46   dchatcha
// PET0165541 FN03 - QESI Phase3, refresh account detail screen after there is update from Govt Amendment screen.
// 
//    Rev 1.33   Dec 28 2010 00:17:18   dchatcha
// PET0165541 FN03 - QESI Phase3, refresh account detail screen after there is update from Govt Amendment screen.
// 
//    Rev 1.32   Dec 14 2010 00:35:32   dchatcha
// PET0165541 FN03 - QESI Phase3, refresh account detail screen after there is update from Tax jurisdiction history screen.
// 
//    Rev 1.31   Dec 13 2010 04:28:28   dchatcha
// PET0165541 FN03 - QESI Phase3, refresh account detail screen after there is update from Taxh jurisdiction history screen.
// 
//    Rev 1.30   Oct 29 2010 07:15:54   dchatcha
// PET0165541 FN03 - QESI Phase3.
// 
//    Rev 1.29   Sep 30 2010 10:03:18   jankovii
// PET168727 FN22 - Trailer Fee Setup
// 
//    Rev 1.28   Aug 06 2010 13:50:18   jankovii
// PET165541 FN03 SOC14 & SOC6
// 
//    Rev 1.27   Jun 15 2010 11:25:56   jankovii
// PE165541_FN09_QESI Phase 2
// 
//    Rev 1.26   Apr 15 2010 18:09:58   popescu
// PET165541_FN01_QESI - RESP Gap_Dsk_Trading - F4 Browser screen helper...
// 
//    Rev 1.25   Jan 28 2010 17:02:42   jankovii
// PET165541 FN01 - QESI - RESP Gap.
// 
//    Rev 1.24   Jan 26 2010 13:40:50   jankovii
// PET165541 FN01 - QESI - RESP Gap.
// 
//    Rev 1.23   Dec 02 2009 09:53:38   popescu
// P0160872 - Fund Setup Phase II
// 
//    Rev 1.22   Nov 20 2009 11:42:14   popescu
// Static Data - entity verify names -linked the web screen
// 
//    Rev 1.21   08 Jul 2009 17:38:10   walkerro
// PET156681 FN03 - Postal Code Lookup added
// 
//    Rev 1.20   May 14 2009 11:43:32   dchatcha
// PET160872 FN01 Fund Setup-Class Level.
// 
//    Rev 1.19   Mar 09 2009 10:26:42   jankovii
// PET 142007 FN04 - TFSA.
// 
//    Rev 1.18   Nov 03 2008 05:23:56   yaviratp
// PET5517 FN71B2 Unclaimed Property - new browser screen (Release Frozen Account).
// 
//    Rev 1.17   Aug 11 2008 15:03:26   jankovii
// PET0057430 FN01 - Performance Fee.
// 
//    Rev 1.16   Jul 11 2008 16:23:32   jankovii
// PET59888 FN01 - AML Enhancement.
// 
//    Rev 1.15   15 Apr 2008 12:09:20   kovacsro
// PET2255 FN47 - New Ontario LIF
// 
//    Rev 1.14   Feb 20 2008 12:45:52   jankovii
// PET 5517 FN80B -DOT and Addendum.
// 
//    Rev 1.13   06 Dec 2007 15:19:56   popescu
// Incident 1088629 - read the ACL set-up for the web pages URL instead of the using the xml configuration file.
// 
//    Rev 1.12   18 Sep 2007 17:46:36   popescu
// AMS/GAP 2360-6 - integrating the AMS AssetInfo screen with Desktop
// 
//    Rev 1.11   Aug 10 2007 11:18:20   ivespaul
// PET2360 - Web Integration.
//
//    Rev 1.10   Apr 19 2007 17:43:04   smithdav
// Add Historical Payments process.
//
//    Rev 1.9   Mar 15 2007 14:53:46   jankovii
// PET 2302 FN01 - Payment Release.
//
//    Rev 1.8   Feb 27 2007 21:15:26   popescu
// Incident#  831221 - backed the code of Web Account Clone feature for CDN market
//
//    Rev 1.7   Dec 19 2006 16:56:24   fengyong
// PET2282 FN01 - Add Clone Account web page
//
//    Rev 1.6   Dec 06 2006 14:56:26   fengyong
// Incident #763433 - refresh account detail after ok on fund limitation page
//
//    Rev 1.5   Oct 19 2006 09:40:10   fengyong
// Temp check in for PET 2185 - fund limitation
//
//    Rev 1.4   Aug 29 2006 10:44:02   fengyong
// PET2192 FN17 - Add new jobname for transaction payment search
//
//    Rev 1.3   Aug 23 2006 14:56:06   fengyong
// PET2192 - Add Payment search process Id
//
//    Rev 1.2   Jun 19 2006 11:21:10   fengyong
// Handle parameters by configuration file setting
//
//    Rev 1.1   Jun 08 2006 13:53:46   fengyong
// initial - for prompt group
//
//    Rev 1.0   Jun 08 2006 13:47:50   fengyong
// Initial revision.
 */
