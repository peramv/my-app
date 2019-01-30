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
//    Copyright 1997 by International Financial Data Services Inc.
//
//******************************************************************************
//
// ^FILE   : COADlg.cpp
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : 03/30/99
//
// ----------------------------------------------------------
//
// ^CLASS    : COADlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for a list selection dialog
//
//******************************************************************************
#include "stdafx.h"

#include "mfdstc.h"
#include "coadlg.h"

#include <bfproc\abstractprocess.hpp>
#include <bfproc\genericinterfacecontainer.hpp>

#include <configmanager.hpp>

#include <ifastbp\coaprocess.hpp>
#include <ifastbp\coaprocessincludes.h>
#include <ifastbp\foreigncontentworksheetprocessincludes.h>
#include <ifastbp\shrfundbrokerprocessincludes.h>
#include <ifastbp\shrfundsponsoragreementprocessincludes.h>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastbp\fundsponsorfeemodelprocessinclude.h>
#include <ifastbp\acctsettlementruleprocessincludes.h>
#include <ifastbp\acctroundingruleprocessincludes.h>

#include <ifastcsi\csisession.h>
#include <ifastcsi\ifastcsi.h>

#include <uibase\dstgridwnd.h>

#include <ifastcbo\dstcworksession.hpp>
#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\mgmtcooptions.hpp>
#include <ifastcbo\entity.hpp>
#include <ifastcbo\accountentityxref.hpp>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_COA;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< COADlg > dlgCreator( CMD_GUI_COA );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_HYPO_RED;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FOREIGN_CONTENT_WORKSHEET;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_SHR_FAMILY;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ACCT_CATEGORY;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_REG_DOCUMENT_LIST;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_BANK_INSTRUCTIONS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_SETTLEMENT_INSTRUCTIONS_ACCTLVL;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_SHR_FUND_SPONSOR_AGREEMENT;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_SHR_FUND_BROKER;
// extern CLASS_IMPORT const I_CHAR* CMD_BPROC_HISTORICAL_ACCOUNT;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_HISTORICAL_INFO;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_TAX_EXEMPT_AUTHORIZATION;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FUNDSPONSOR_FEE_MODEL;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ACCT_LVL_CUT_OFF_TIMES;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FUND_CLASS_LIMITATION;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ACCT_LEVEL_SETTLEMENT_RULE;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_LIF_GAIN_LOSS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_INVESTOR_AUTHORIZATION_INFORMATION;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ACCT_GUARNT_GUARD_OPTN;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_MATSWP_INSTRUCTIONS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ACCT_OWNERSHIP_ALLOCATION;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_VALUE_VARIATION;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ACCT_FEE_MODEL_ASSOCIATION;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_SHR_STATEMENT_SCHED;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ACCT_REGIS_MAINT;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ENT_REG_MAINT;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_TAX_SLIPS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ACCOUNT_GROUP;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_PRIVATE_WEALTH_INFO;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_RESP_GRANTS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_RESP_GRANTS2;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_REG_PLAN_TRANSFER;

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const ADDRESS_BOOK;
   extern CLASS_IMPORT I_CHAR * const DEMOGRAPHICS;
   extern CLASS_IMPORT I_CHAR * const REMARKS;
   extern CLASS_IMPORT I_CHAR * const BANKING_INSTRUCTION;
   extern CLASS_IMPORT I_CHAR * const DEFAULT_ALLOCATION;
   extern CLASS_IMPORT I_CHAR * const DISTRIBUTION;
   extern CLASS_IMPORT I_CHAR * const ENTITY_MAINTANENCE;
   extern CLASS_IMPORT I_CHAR * const AUTOMATIC_TRANSFER;
   extern CLASS_IMPORT I_CHAR * const PAC;
   extern CLASS_IMPORT I_CHAR * const SWP;
   extern CLASS_IMPORT I_CHAR * const SAVING_PLAN;
   extern CLASS_IMPORT I_CHAR * const INTEREST_ACCRUAL;
   extern CLASS_IMPORT I_CHAR * const ACB;
   extern CLASS_IMPORT I_CHAR * const CHEQUE;
   extern CLASS_IMPORT I_CHAR * const HISTORICAL_MARKET_VALUE;
   extern CLASS_IMPORT I_CHAR * const RIF_LIF_LRIF_INFO;
   extern CLASS_IMPORT I_CHAR * const SEG_FUND_CONTRACT;
   extern CLASS_IMPORT I_CHAR * const SEG_FUND_GUARANTEE;
   extern CLASS_IMPORT I_CHAR * const RESP_INFO;
   extern CLASS_IMPORT I_CHAR * const SEG_FUND_MULTI_CONTRACT;
   extern CLASS_IMPORT I_CHAR * const AS_PENSION_PLAN;
   extern CLASS_IMPORT I_CHAR * const ESOP;
   extern CLASS_IMPORT I_CHAR * const YTD;
   extern CLASS_IMPORT I_CHAR * const FEE_PARAMETER;
   extern CLASS_IMPORT I_CHAR * const ACCOUNTREVIEW;
   extern CLASS_IMPORT I_CHAR * const HYPOTHETICAL_REDEMPTION;
   extern CLASS_IMPORT I_CHAR * const SHR_FAMILY;
   extern CLASS_IMPORT I_CHAR * const ACCT_CATEGORY;
   extern CLASS_IMPORT I_CHAR * const DOC_LIST;
   extern CLASS_IMPORT I_CHAR * const ACCOUNT_DETAIL;
   extern CLASS_IMPORT I_CHAR * const DIRECT_TRADING_AGREEMENT;
   extern CLASS_IMPORT I_CHAR * const SETTLE_LOCATION_ACCT_LVL;
   extern CLASS_IMPORT I_CHAR * const FOREIGN_CONTENT;
   extern CLASS_IMPORT I_CHAR * const SHR_FUND_SPONSOR_AGREEMENT;
   extern CLASS_IMPORT I_CHAR * const TAX_EXEMPT_AUTHORIZATION;
   extern CLASS_IMPORT I_CHAR * const ACCOUNT_FEE_MODEL;
   extern CLASS_IMPORT I_CHAR * const SHR_FUND_BROKER;
   extern CLASS_IMPORT I_CHAR * const ACCT_LVL_CUT_OFF_TIME;
   extern CLASS_IMPORT I_CHAR * const ACCOUNT_TRADING_OVERRIDES;
   extern CLASS_IMPORT I_CHAR * const AFFLUENT;
   extern CLASS_IMPORT I_CHAR * const ACCT_LEVEL_SETTLEMENT_RULE;
   extern CLASS_IMPORT I_CHAR * const SYSTEM_STOP_REASON;
   extern CLASS_IMPORT I_CHAR * const INVESTOR_AUTHORIZATION_INFO;
   extern CLASS_IMPORT I_CHAR * const RESP_ACCOUNT_TERMINATION;
   extern CLASS_IMPORT I_CHAR * const RESP_ZERO_GRANT;
   extern CLASS_IMPORT I_CHAR * const RESP_INTERFACE_FILE;
   extern CLASS_IMPORT I_CHAR * const ACCT_GUARNT_GUARD_OPTN;
   extern CLASS_IMPORT I_CHAR * const ACCTLVL_TRAILERFEE_SETUP;
   extern CLASS_IMPORT I_CHAR * const RESP_GOVT_FILING_AMENDMENT;
   extern CLASS_IMPORT I_CHAR * const REL_STOP_RED;
   extern CLASS_IMPORT I_CHAR * const MATURITYSWPEEP_INSTR;
   extern CLASS_IMPORT I_CHAR * const TFSA_AMENDMENT; //IN2747587 - guifn 223 - TFSA Amendment
   extern CLASS_IMPORT I_CHAR * const VALUE_VARIATION;
   extern CLASS_IMPORT I_CHAR * const ACCT_FEE_MODEL_ASSOCIATION;
   extern CLASS_IMPORT I_CHAR * const SHR_STATEMENT_SCHED;
   extern CLASS_IMPORT I_CHAR * const ACCT_REGIS_MAINT;
   extern CLASS_IMPORT I_CHAR * const ENTITY_REGULATORY_MAINT;
   extern CLASS_IMPORT I_CHAR * const ACCT_CATEGORY_PRIVATE_WEALTH_OPT_OUT;
   extern CLASS_IMPORT I_CHAR * const ACCOUNT_GROUPING;
   extern CLASS_IMPORT I_CHAR * const PRIVATE_WEALTH_INFO;
   extern CLASS_IMPORT I_CHAR * const RESP_BENEFICIARY;
   extern CLASS_IMPORT I_CHAR * const RESP_GRANTS;
   extern CLASS_IMPORT I_CHAR * const RESP_NOTIONAL_ACTIVITY;
   extern CLASS_IMPORT I_CHAR * const RESP_GRANT_INFORMATION;
   extern CLASS_IMPORT I_CHAR * const REG_PLAN_TRANSFER;
   extern CLASS_IMPORT I_CHAR * const ACCT_ROUNDING_RULE;
   extern CLASS_IMPORT I_CHAR * const ACCT_DELETION_REVIEW;
   extern CLASS_IMPORT I_CHAR * const RDSP_ACCOUNT_INFORMATION;
   extern CLASS_IMPORT I_CHAR * const RDSP_NOTIONAL_ACTIVITY;
   extern CLASS_IMPORT I_CHAR * const RDSP_NOTIONAL_BALANCE;
}

namespace COADLG
{
   const TCHAR * const CMD_ACCOUNTREVIEW                       = I_( "BPROC_ACCOUNTREVIEW" );
   const TCHAR * const CMD_AMSACCTLVL                          = I_( "BPROC_AMSACCTLVL" );
   const TCHAR * const CMD_REMARK                              = I_( "BPROC_REMARKS" );
   const TCHAR * const CMD_BANK                                = CMD_BPROC_BANK_INSTRUCTIONS;
   const TCHAR * const CMD_DOCLIST                             = CMD_BPROC_REG_DOCUMENT_LIST;
   const TCHAR * const CMD_SYSTR                               = I_( "BPROC_SYSTEMATIC" );
   const TCHAR * const CMD_PAC                                 = I_( "BPROC_SYSTEMATIC" );
   const TCHAR * const CMD_SWP                                 = I_( "BPROC_SYSTEMATIC" );
   const TCHAR * const CMD_SAVING_PLAN                         = I_( "BPROC_SYSTEMATIC" );
   const TCHAR * const CMD_ALLOC                               = I_( "BPROC_ALLOCATIONS" );
   const TCHAR * const CMD_ACB                                 = I_( "BPROC_ACB" );
   const TCHAR * const CMD_ADDR                                = I_( "BPROC_AddressProcess" );
   const TCHAR * const CMD_ENTITY                              = I_( "BPROC_EntityProcess" );
   const TCHAR * const CMD_RRIF                                = I_( "BPROC_RRIF_LIF_LRIF_INFO" );
   const TCHAR * const CMD_ESCROW                              = I_( "ESCROW" );
   //const TCHAR * const CMD_DEFSCH                              = I_( "HLLAPI" );
   const TCHAR * const CMD_INTACR                              = I_( "BPROC_ACCRUALS" );
   const TCHAR * const CMD_BPROC_ACCT_IDENTIFIER		       = I_( "BPROC_ACCT_IDENTIFIER" );
   const TCHAR * const CMD_ACCINF                              = I_( "BPROC_AccountInfoProcess" );
   const TCHAR * const CMD_FEES                                = I_( "HLLAPI" );
   const TCHAR * const CMD_DISTR                               = I_( "BPROC_AccountDistributionProcess" );
   const TCHAR * const CMD_DEMOGR                              = I_( "BPROC_DEMOGRAPHICS" );
   const TCHAR * const CMD_CERTIF                              = I_( "BPROC_CERTIFICATE" );
   const TCHAR * const CMD_CHEQUE                              = I_( "BPROC_CHEQUE" );
   const TCHAR * const CMD_SHR                                 = I_( "BPROC_ShareholderProcess" );
   const TCHAR * const CMD_CONT                                = I_( "BPROC_CONTRACTINFO" );
   const TCHAR * const CMD_GUAR                                = I_( "BPROC_GUARANTEEINFO" );
   const TCHAR * const CMD_RESP                                = I_( "BPROC_RESPINFO" );
   const TCHAR * const CMD_YTD                                 = I_( "BPROC_YTD_CONTRIBUTION" );
   const TCHAR * const CMD_ASPENSION                           = I_( "BPROC_AS_PENSION_PLAN" );
   const TCHAR * const CMD_ESOP                                = I_( "BPROC_ESoPInfo" );
   const TCHAR * const CMD_FEE_PARAMETER                       = I_( "BPROC_FeeParameter" );
   const TCHAR * const CMD_TRAILER_FEE                         = I_( "CMD_BPROC_TRAILER_FEE_SETUP" );
   const TCHAR * const CMD_PENSION_INFO                        = I_( "BPROC_PENSION_INFO" );
   const TCHAR * const CMD_ACCT_SPLIT_COMM                     = I_( "BPROC_ACCT_SPLITCOMM" );
   const TCHAR * const CMD_HYPORED                             = CMD_BPROC_HYPO_RED;
   const TCHAR * const CMD_FOREIGN_CONTENT_WORKSHEET           = CMD_BPROC_FOREIGN_CONTENT_WORKSHEET;
   const TCHAR * const CMD_SHR_FAMILY                          = CMD_BPROC_SHR_FAMILY;
   const TCHAR * const CMD_ACCT_CATEGORY                       = CMD_BPROC_ACCT_CATEGORY;
   const TCHAR * const CMD_ACCT_SETTLE_LOC                     = CMD_BPROC_SETTLEMENT_INSTRUCTIONS_ACCTLVL;
   const TCHAR * const CMD_TAX_EXEMPT_AUTHORIZATION            = I_( "BPROC_TAX_EXEMPT_AUTHORIZATION" );
   const TCHAR * const CMD_BPROC_RESP_ACCOUNT_TERMINATION      = I_( "BPROC_RESP_ACCOUNT_TERMINATION" );
   const TCHAR * const CMD_BPROC_ZERO_GRANT_REPAYMENT          = I_( "BPROC_ZERO_GRANT_REPAYMENT" );
   const TCHAR * const CMD_BPROC_INTERFACE_FILE                = I_( "BPROC_INTERFACE_FILE" );
   const TCHAR * const CMD_BPROC_FUNDSPONSOR_FEE_MODEL         = I_( "BPROC_FundSponsor_FeeModel" );
   const TCHAR * const CMD_BPROC_FUND_CLASS_LIMITATION         = I_( "BPROC_FUND_CLASS_LIMITATION" );
   const TCHAR * const CMD_ACCT_SETTLEMENT_RULE                = I_( "BPROC_ACCT_LEVEL_SETTLEMENT_RULE" );
   const TCHAR * const CMD_BPROC_LIF_GAIN_LOSS                 = I_( "CMD_BPROC_LIF_GAIN_LOSS" );
   const TCHAR * const CMD_INVESTOR_AUTHORIZATION              = CMD_BPROC_INVESTOR_AUTHORIZATION_INFORMATION;
   const TCHAR * const CMD_ACCT_GUARNT_GUARD_OPTN              = CMD_BPROC_ACCT_GUARNT_GUARD_OPTN;
   const TCHAR * const CMD_BPROC_GOVT_FILING_AMENDMENT         = I_( "CMD_BPROC_GOVT_FILING_AMENDMENT" );
   const TCHAR * const CMD_CASH_SWEEP_INSTRUCTIONS             = CMD_BPROC_MATSWP_INSTRUCTIONS;
   const TCHAR * const CMD_MATINTEREST_INSTRUCTIONS            = CMD_BPROC_MATSWP_INSTRUCTIONS;
   const TCHAR * const CMD_VALUE_VARIATION                     = CMD_BPROC_VALUE_VARIATION;
   const TCHAR * const CMD_ACCT_FEE_MODEL_ASSOCIATION          = CMD_BPROC_ACCT_FEE_MODEL_ASSOCIATION;
   const TCHAR * const CMD_DIRECT_TRADING_AGREEMENT            = I_( "BPROC_DirectTradingProcess" );
   const TCHAR * const CMD_SHR_FUND_SPONSOR_AGREEMENT          = CMD_BPROC_SHR_FUND_SPONSOR_AGREEMENT;
   const TCHAR * const CMD_SHR_FUND_BROKER                     = CMD_BPROC_SHR_FUND_BROKER;
   const TCHAR * const CMD_BPROC_ACCT_LVL_CUT_OFF_TIMES        = I_( "BPROC_ACCT_LVL_CUT_OFF_TIMES" );
   const TCHAR * const CMD_ACCT_OWNERSHIP_ALLOCATION           = CMD_BPROC_ACCT_OWNERSHIP_ALLOCATION;
   const TCHAR * const CMD_SHR_STATEMENT_SCHED                 = CMD_BPROC_SHR_STATEMENT_SCHED;
   const TCHAR * const CMD_ACCT_REG_DETAILS                    = CMD_BPROC_ACCT_REGIS_MAINT;
   const TCHAR * const CMD_ENT_REG_DETAILS                     = CMD_BPROC_ENT_REG_MAINT;
   const TCHAR * const CMD_ACCOUNT_GROUP                       = CMD_BPROC_ACCOUNT_GROUP;
   const TCHAR * const CMD_PRIVATE_WEALTH_INFO                 = CMD_BPROC_PRIVATE_WEALTH_INFO;
   const TCHAR * const CMD_TAX_SLIPS                           = CMD_BPROC_TAX_SLIPS;
   const TCHAR * const CMD_REG_PLAN_TRANSFER                   = CMD_BPROC_REG_PLAN_TRANSFER;
   const TCHAR * const CMD_RESP_GRANTS                         = I_( "BPROC_RESP_GRANTS" );
   const TCHAR * const CMD_RESP_GRANTS2                        = I_( "BPROC_RESP_GRANTS2" );
   const TCHAR * const CMD_RESP_NOTIONAL_ACTIVITY              = I_( "BPROC_RESP_NOTIONAL_ACTIVITY" );
   const TCHAR * const CMD_ACCT_ROUNDING_RULE				   = I_( "BPROC_ACCT_ROUNDING_RULE" );
   const TCHAR * const CMD_ACCT_DELETION_REVIEW				   = I_( "BPROC_ACCT_DELETION_REVIEW" );
   const TCHAR * const CMD_RDSP_ACCOUNT_INFO				   = I_( "BPROC_RDSP_ACCOUNT_INFO" );
   const TCHAR * const CMD_RDSP_NOTIONAL_ACTIVITY			   = I_( "BPROC_RDSP_NOTIONAL_ACTIVITY" );
   const TCHAR * const CMD_RDSP_NOTIONAL_BALANCE			   = I_( "BPROC_RDSP_NOTIONAL_BALANCE" );  

   const TCHAR * const STRING_YES_NO = I_( "Yes\nNo" );
   const TCHAR * const STRING_NL     = I_( "\n" );
   const TCHAR * const STRING_YES    = I_( "Yes" );
   const TCHAR * const STRING_NO     = I_( "No" );
   const TCHAR * const STRING_Y      = I_( "Y" );
   const TCHAR * const STRING_N      = I_( "N" );
   // const TCHAR * const STRING_CHANGE = I_( "Change" );
   // const TCHAR * const STRING_VIEW   = I_( "View" );

   const I_CHAR * const KYC_MANUAL                  = I_("01");
   const I_CHAR * const DECEASED_MANUAL             = I_("02");
   const I_CHAR * const KYC_SYSTEM                  = I_("03");
   const I_CHAR * const DECEASED_SYSTEM             = I_("04");
   const I_CHAR * const RESP_TAX_TYPES              = I_("9,M");
   const I_CHAR * const RDSP_TAX_TYPE				= I_("RS");
}

namespace BANKTYPE
{
   extern CLASS_IMPORT I_CHAR * const SHAREHOLDER;
}

namespace
{
   const I_CHAR *COADLG_CLASS              = I_( "COADlg" );
   const I_CHAR *WORKSTATION               = I_( "WORKSTATION" );
   const I_CHAR *DEFAULTWORKSTATION        = I_( "DefaultWorkstation" );
   const I_CHAR *GRID_WINDOW               = I_( "Grid_Window" );
   const I_CHAR *FIELD_SCREEN              = I_( "Field_Screen" );
   const I_CHAR *TYPE                      = I_( "Type" );
   const I_CHAR *VALUE                     = I_( "Value" );
   const I_CHAR * const ESOP_INVESTMENT    = I_( "D" );
   const I_CHAR * const ESOP_PARTICIPATION = I_( "E" ); 
   const I_CHAR * const CALLER             = I_("Caller");
   const I_CHAR * const TFSA_TAX_TYPES     = I_( "V" );
   const I_CHAR * const INSTR_TYPE         = I_( "InstrType" );
   const I_CHAR * const CASH_SWEEP_INSTR   = I_("SWP");
   const I_CHAR * const MATURITY_INSTR     = I_("MAT");
   const I_CHAR * const ACCT_STATUS_ACTIVE = I_("10");
}

namespace CND
{  // Conditions used
    extern CLASS_IMPORT const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId CotClient;
   extern CLASS_IMPORT const BFTextFieldId SegClient;
   extern CLASS_IMPORT const BFTextFieldId ResClient;
   extern CLASS_IMPORT const BFIntegerFieldId CommissionType;
   extern CLASS_IMPORT const BFDateFieldId FirstSettleDate; 
   extern CLASS_IMPORT const BFTextFieldId RegisteredTaxTypes;
   extern CLASS_IMPORT const BFTextFieldId FeeModelCode;
   extern CLASS_IMPORT const BFTextFieldId EUSDParticip;
   extern CLASS_IMPORT const BFTextFieldId SiblingOnly;
   extern CLASS_IMPORT const BFTextFieldId EligExtTrfGainLoss;
   extern CLASS_IMPORT const BFTextFieldId StopReason;
   extern CLASS_IMPORT const BFTextFieldId AdditionalStopReason;
   extern CLASS_IMPORT const BFTextFieldId DocListExists;
   extern CLASS_IMPORT const BFDateFieldId NextMFRProcessDate; 
   extern CLASS_IMPORT const BFTextFieldId IsGWOContractExist;
   extern CLASS_IMPORT const BFTextFieldId NSCCSocialCode;
   extern CLASS_IMPORT const BFTextFieldId OrgType;
   extern CLASS_IMPORT const BFTextFieldId SubOrgType;
   extern CLASS_IMPORT const BFDateFieldId InitialDate;
   extern CLASS_IMPORT const BFTextFieldId AcctFeeModelAssociated;
   extern CLASS_IMPORT const BFTextFieldId ShrOutputType;
   extern CLASS_IMPORT const BFTextFieldId IsTrlFeeAcctLevelApp;
   extern CLASS_IMPORT const BFTextFieldId AcctRegulatoryExist;
   extern CLASS_IMPORT const BFTextFieldId Yes_NO;
   extern CLASS_IMPORT const BFTextFieldId TaxFormsAppl;
   extern CLASS_IMPORT const BFTextFieldId AggregationType;
   extern CLASS_IMPORT const BFNumericFieldId EntityId;
   extern CLASS_IMPORT const BFTextFieldId LastName;
   extern CLASS_IMPORT const BFTextFieldId FirstName;
   extern CLASS_IMPORT const BFTextFieldId RESPTransformation;
   extern CLASS_IMPORT const BFTextFieldId AcctDelState;
}

namespace COMPLY_RULE
{
   extern CLASS_IMPORT const DString AcctRegistration; 
   extern CLASS_IMPORT const DString DeathClaim ;
   extern CLASS_IMPORT const DString TaxCompliant;
   extern CLASS_IMPORT const DString AccountholderRisk;
}

//*****************************************************************************
// Public methods
//*****************************************************************************

COADlg::COADlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( COADlg::IDD, pParent, pGIC, pGIParent, rCommand, COADLG_CLASS )
{
    TRACE_CONSTRUCTOR( COADLG_CLASS, NULL_STRING );

}

//*****************************************************************************
COADlg::~COADlg( )
{
    TRACE_DESTRUCTOR( COADLG_CLASS );
    COAElementMap::iterator coaMapIter = m_ElementMap.begin();
    while( coaMapIter != m_ElementMap.end() )
    {
        delete (*coaMapIter).second;
        coaMapIter = m_ElementMap.erase( coaMapIter );
    }
}

//*****************************************************************************
void COADlg::DoDataExchange( CDataExchange* pDX )
{
    BaseMainDlg::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(COADlg)
    DDX_Control(pDX, IDC_EDT_FIND, m_edtFind);
    DDX_Control(pDX, IDC_CMB_VIEW, m_cmbView);
    //}}AFX_DATA_MAP
}

//*****************************************************************************

SEVERITY COADlg::doInit()
{
   TRACE_METHOD( COADLG_CLASS, DOINIT );

   return(NO_CONDITION);
}

//*****************************************************************************

BEGIN_MESSAGE_MAP(COADlg, BaseMainDlg)
//{{AFX_MSG_MAP(COADlg)
ON_BN_CLICKED(IDC_BTN_COLLAPSE, OnBtnCollapse)
ON_CBN_SELCHANGE(IDC_CMB_VIEW, OnSelchangeCmbView)
ON_BN_CLICKED(IDC_BTN_SEARCH, OnBtnSearch)
ON_EN_CHANGE(IDC_EDT_FIND, OnChangeEdtFind)
ON_BN_CLICKED( IDC_BTN_HISTORICAL, OnBtnHistorical )
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
// Message handlers
//*****************************************************************************

void COADlg::addCOARow( COA_ENTRY_ID   lId, const CString & lDispName, COA_Type lType, const CString & lStrCommand, bool lHasChange, COA_ENTRY_ID lParent, 
                        WORD lControlType, CHOICE_TYPE eChoiceType, bool bAddBlankSubstitution )
{
    COAElement* pCOAElement = new COAElement( lId, lDispName, lType, lStrCommand, lHasChange, lParent, lControlType, eChoiceType );
    m_ElementMap.insert( COAElementMap::value_type( COAElementKey( lParent, lId ), pCOAElement ));
    if( lType != COA_TYPE_TITLE )
        retrieveValue( lId );
    DString strValue(NULL_STRING);
    if( eChoiceType == CHOICE_TYPE_YES_NO )
    {
        getParent()->getField(this,BF::NullContainerId,COAPROC::lYes_no,strValue,true);
    }
    else if( eChoiceType == CHOICE_TYPE_CHANGE )
    {
        DString strValue1,strValue2;
        CString eValue = pCOAElement->getValue();
        if( eValue == _T("") )
            getParent()->getField(this,BF::NullContainerId,COAPROC::lYes,strValue1,true);
        getParent()->getField(this,BF::NullContainerId,COAPROC::lChange,strValue2,true);
        strValue = strValue1 + COADLG::STRING_NL + strValue2;
        if( lId == SCR_ACCT_SETTLE_LOC )
        {
            DString dstrClearingID;
            getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::ClearingID, dstrClearingID );
            if( dstrClearingID.empty() )
            {
               strValue = strValue1 + COADLG::STRING_NL;
            }
            else
            {
               strValue = strValue1 + COADLG::STRING_NL + strValue2;
            }
        }
        else
        {
            strValue = strValue1 + COADLG::STRING_NL + strValue2;
        }
    }
    else if( eChoiceType == CHOICE_TYPE_VIEW )
    {
        DString strValue1,strValue2;
        CString eValue = pCOAElement->getValue();
        if( eValue == _T("") )
            getParent()->getField(this,BF::NullContainerId,COAPROC::lYes,strValue1,true);
        getParent()->getField(this,BF::NullContainerId,COAPROC::lView,strValue2,true);
        strValue = strValue1 + COADLG::STRING_NL + strValue2;
    }
    else if( eChoiceType == CHOICE_TYPE_FIELD_SUBST )
    {
        strValue = getSubstitutionList(lId);
        if( !strValue.empty() && bAddBlankSubstitution )
        {
            strValue = COADLG::STRING_NL + strValue;
        }
    }
    pCOAElement->setComboValue(strValue.c_str() );
    pCOAElement->setChoiceList();
}

//*****************************************************************************

void COADlg::addCOARow( COA_ENTRY_ID lId, const UINT strID, /*const CString & lDispName,*/ COA_Type lType, 
                        const CString & lStrCommand, bool lHasChange, COA_ENTRY_ID lParent, 
                        WORD lControlType, CHOICE_TYPE eChoiceType, bool bAddBlankSubstitution )
{
    CString lDispName;
    lDispName.LoadString( strID );
    addCOARow( lId, lDispName, lType, lStrCommand, lHasChange, lParent, lControlType, eChoiceType, bAddBlankSubstitution );
}

//*****************************************************************************
BOOL COADlg::OnInitDialog() 
{
   TRACE_METHOD( COADLG_CLASS, ONINITDIALOG );
   BaseMainDlg::OnInitDialog();


   GenericInterface* Parent = getParent();
   DString lAccountNbr, lShrNum, lEntityName, lInNASU;
   GetWindowText(m_strTitle) ;

   DString strMarket = DSTCommonFunctions::getMarket();

   Parent->getField( this,  COAPROC::inNASU, lInNASU );
   lInNASU.strip();
   m_lInNASU = lInNASU == I_("Y");

   MFAccount* pMFAccount = dynamic_cast<COAProcess*>(getParent() )->getMFAccount();
   DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());

   if( !m_lInNASU )
   {
      Parent->getField( this,  ifds::AccountNum, lAccountNbr );
      Parent->getField( this,  ifds::ShrNum    , lShrNum     );
      Parent->getField( this,  ifds::Name1     , lEntityName );

      SetShrAcctCaption( lShrNum.strip(), lAccountNbr.strip(), lEntityName.strip() );
   }

   addCOARow( TTL_STOPS_ID,  IDS_TTL_STOPS,     COA_TYPE_TITLE,   _T(""),             false, TTL_STOPS_ID,   GX_IDS_CTRL_STATIC           );
   addCOARow( TTL_SCREENS_ID,IDS_TTL_SCREENS,   COA_TYPE_TITLE,   _T(""),             false, TTL_SCREENS_ID, GX_IDS_CTRL_STATIC           );
   addCOARow( TTL_FEES_ID,   IDS_TTL_FEES,      COA_TYPE_TITLE,   _T(""),             false, TTL_FEES_ID,    GX_IDS_CTRL_STATIC           );
   addCOARow( TTL_SUPRESS_ID,IDS_TTL_SUPRESS,   COA_TYPE_TITLE,   _T(""),             false, TTL_SUPRESS_ID, GX_IDS_CTRL_STATIC           );
   addCOARow( TTL_MISC_ID,   IDS_TTL_MISC,      COA_TYPE_TITLE,   _T(""),             false, TTL_MISC_ID,    GX_IDS_CTRL_STATIC           );
   addCOARow( TTL_NSCC_ID,   IDS_TTL_NSCC,      COA_TYPE_TITLE,   _T(""),             false, TTL_NSCC_ID,    GX_IDS_CTRL_STATIC           );


   addCOARow( STP_PURCH_ID,  IDS_STP_PURCH,     COA_TYPE_CAUTION, _T(""),             false, TTL_STOPS_ID,   GX_IDS_CTRL_CBS_DROPDOWNLIST );
   addCOARow( STP_REDEM_ID,  IDS_STP_REDEM,     COA_TYPE_CAUTION, _T(""),             false, TTL_STOPS_ID,   GX_IDS_CTRL_CBS_DROPDOWNLIST );
   addCOARow( STP_XFERO_ID,  IDS_STP_XFERO,     COA_TYPE_CAUTION, _T(""),             false, TTL_STOPS_ID,   GX_IDS_CTRL_CBS_DROPDOWNLIST );
   addCOARow( STP_XFERI_ID,  IDS_STP_XFERI,     COA_TYPE_CAUTION, _T(""),             false, TTL_STOPS_ID,   GX_IDS_CTRL_CBS_DROPDOWNLIST );
   addCOARow( STP_FRREB_ID,  IDS_STP_FRREB,     COA_TYPE_CAUTION, _T(""),             false, TTL_STOPS_ID,   GX_IDS_CTRL_CBS_DROPDOWNLIST );
   //addCOARow( STP_AMSREBALANCING_ID,  IDS_STP_AMSREBALANCING,     COA_TYPE_CAUTION, _T(""),             false, TTL_STOPS_ID,   GX_IDS_CTRL_CBS_DROPDOWNLIST );

   DString strDivDates;
   dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getOption( ifds::DivDates, 
                                                         strDivDates, getDataGroupId(), false ) ;
   if ( strDivDates.strip() == I_("1") ) 
   {
      addCOARow( HLD_DIV_PAYMENT,  IDS_HLD_DIV_PAYMENT,     COA_TYPE_CAUTION, _T(""),             false, TTL_STOPS_ID,   GX_IDS_CTRL_CBS_DROPDOWNLIST );
   }

   addCOARow( STP_REASON_ID,  IDS_STP_REASON,     COA_TYPE_CAUTION, _T(""),             false, TTL_STOPS_ID, GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_FIELD_SUBST, true );
   addCOARow( STP_ADDITIONAL_REASON_ID,  IDS_STP_ADDITIONAL_REASON,     COA_TYPE_CAUTION, _T(""),  false, TTL_STOPS_ID,   GX_IDS_CTRL_EDIT );
   addCOARow( STP_STOP_NFU,  IDS_STOP_NFU,     COA_TYPE_CAUTION, _T(""),  false, TTL_STOPS_ID, GX_IDS_CTRL_CBS_DROPDOWNLIST);

   addCOARow( SCR_REMARK_ID, IDS_SCR_REMARK,    COA_TYPE_CAUTION, COADLG::CMD_REMARK, true,  TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE );
   addCOARow( SCR_BANK_ID,   IDS_SCR_BANK,      COA_TYPE_OPTION,  COADLG::CMD_BANK,   true,  TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE );
   if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::JAPAN || strMarket == MARKET_IDS::LUXEMBOURG )
      addCOARow( SCR_SYSTR_ID,  IDS_SCR_SYSTR,     COA_TYPE_OPTION,  COADLG::CMD_SYSTR,  true,  TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE );
   addCOARow( SCR_PAC_ID,    IDS_SCR_PAC,       COA_TYPE_OPTION,  COADLG::CMD_PAC,    true,  TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE );
   addCOARow( SCR_SWP_ID,    IDS_SCR_SWP,       COA_TYPE_OPTION,  COADLG::CMD_SWP,    true,  TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE );
   if( strMarket == MARKET_IDS::LUXEMBOURG )
   {
      addCOARow( SCR_SAVING_PLAN_ID,    IDS_SCR_SAVING_PLAN,       COA_TYPE_OPTION,  COADLG::CMD_SAVING_PLAN,    true,  TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE );
   }
   addCOARow( SCR_ALLOC_ID,  IDS_SCR_ALLOC,     COA_TYPE_OPTION,  COADLG::CMD_ALLOC,  true,  TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE );
   addCOARow( SCR_ACB_ID,    IDS_SCR_ACB,       COA_TYPE_ATTRIB,  COADLG::CMD_ACB,    true,  TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_VIEW   );
   addCOARow( SCR_ADDR_ID,   IDS_SCR_ADDR,      COA_TYPE_ATTRIB,  COADLG::CMD_ADDR,   true,  TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE );
   addCOARow( SCR_ENTITY_ID, IDS_SCR_ENTITY,    COA_TYPE_ATTRIB,  COADLG::CMD_ENTITY, true,  TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE );
   addCOARow( SCR_INTACR_ID, IDS_SCR_INTACR,    COA_TYPE_ATTRIB,  COADLG::CMD_INTACR, true,  TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_VIEW   );
   addCOARow( SCR_ACCIDENT_ID, IDS_SCR_ACCIDENT,  COA_TYPE_OPTION,  COADLG::CMD_BPROC_ACCT_IDENTIFIER, true,  TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE );
   addCOARow( SCR_ACCINF_ID, IDS_SCR_ACCINF,    COA_TYPE_ATTRIB,  COADLG::CMD_ACCINF, true,  TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE );
   addCOARow( SCR_DISTR_ID,  IDS_SCR_DISTR,     COA_TYPE_ATTRIB,  COADLG::CMD_DISTR,  true,  TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE );
   addCOARow( SCR_DEMOGR_ID, IDS_SCR_DEMOGR,    COA_TYPE_ATTRIB,  COADLG::CMD_DEMOGR, true,  TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE );
   addCOARow( SCR_CERTIF_ID, IDS_SCR_CERTIF,    COA_TYPE_CAUTION, COADLG::CMD_CERTIF, true,  TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_VIEW   );
   addCOARow( SCR_CHEQUE_ID, IDS_SCR_CHEQUE,    COA_TYPE_ATTRIB,  COADLG::CMD_CHEQUE, true,  TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_VIEW   );   
   //addCOARow( SCR_SHR_ID,    IDS_SCR_SHR,       COA_TYPE_ATTRIB,  COADLG::CMD_SHR,    true,  TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE );
   addCOARow( SCR_ACCT_FEE_ID,    IDS_SCR_ACCT_FEE_SET_UP, COA_TYPE_ATTRIB,  COADLG::CMD_FEE_PARAMETER,    true,  TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE );

   DString dstrTrailerFeeArch;
   dstWorkSession->getOption(ifds::TrailerFeeArch, dstrTrailerFeeArch, getParent()->getDataGroupId(), false);
   dstrTrailerFeeArch.strip ();

   DString IsTrlFeeAcctLevelApp;
   dstWorkSession->getOption(ifds::IsTrlFeeAcctLevelApp, IsTrlFeeAcctLevelApp, getParent()->getDataGroupId(), false);
   if ( IsTrlFeeAcctLevelApp.upperCase() == COADLG::STRING_Y && dstrTrailerFeeArch == COADLG::STRING_Y && hasReadPermission( UAF::ACCTLVL_TRAILERFEE_SETUP ))
   {
      addCOARow( SCR_ACCT_TRAILER_FEE, IDS_SCR_ACCT_TRAILERFEE_SETUP, COA_TYPE_ATTRIB,  COADLG::CMD_TRAILER_FEE,    true,  TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE );
   }

   addCOARow( SCR_HYPORED_ID,IDS_SCR_HYPORED,   COA_TYPE_ATTRIB,  COADLG::CMD_HYPORED,true,  TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_VIEW );

   DString dstrForeignContent(NULL_STRING);
   dstWorkSession->getOption( ifds::ForeignContent, dstrForeignContent, getParent()->getDataGroupId(), false ); 
   bool bAccessForeignCont = dstrForeignContent.strip().upperCase() == COADLG::STRING_Y && hasReadPermission( UAF::FOREIGN_CONTENT );
   if( bAccessForeignCont)
   {
      addCOARow( SCR_FOREIGN_CONTENT_WORKSHEET_ID, IDS_SCR_FOREIGN_CONTENT_WORKSHEET, COA_TYPE_ATTRIB, COADLG::CMD_FOREIGN_CONTENT_WORKSHEET, true,  TTL_SCREENS_ID, GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE );
   }

   if( strMarket == MARKET_IDS::CANADA )
   {
      DString dstrPlanType, dstrTaxType;
      getParent()->getField(this, ifds::PlanType, dstrPlanType, false );
      getParent()->getField(this, ifds::TaxType, dstrTaxType, false );
      dstrPlanType.strip();
      dstrTaxType.strip().upperCase();

      if( dstWorkSession->isLIFLike (dstrTaxType) || dstrTaxType == I_( "R" ) || 
         dstWorkSession->isLIRALike (dstrTaxType) || dstrTaxType == I_( "L" ))
      {
         addCOARow( SCR_PENSION_INFO, IDS_SCR_PENSION_JURIS, COA_TYPE_ATTRIB,  COADLG::CMD_PENSION_INFO,    true,  TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE );
      }

      if( hasReadPermission( UAF::RIF_LIF_LRIF_INFO ) && 
         (dstWorkSession->isLIFLike (dstrTaxType) || dstrTaxType == I_( "L" ) || dstrTaxType == I_( "R" ) ||
         dstrTaxType == I_( "2" ) /*|| dstrTaxType == I_( "5" ) */) )
      {
         addCOARow( SCR_RRIF_ID, IDS_SCR_RRIF,  COA_TYPE_ATTRIB,  COADLG::CMD_RRIF,  true,  TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE );
      }
      if( hasReadPermission( UAF::YTD ) && dstrTaxType == I_( "1" ) ) //RRSP Tax
      {
         addCOARow( SCR_YTD_ID, IDS_SCR_YTD, COA_TYPE_ATTRIB, COADLG::CMD_YTD, true, TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_VIEW );
      }

      
      DString dstrCotClient, dstrSegClient;
      dstWorkSession->getOption( ifds::CotClient, dstrCotClient, Parent->getDataGroupId(), false );
      dstWorkSession->getOption( ifds::SegClient, dstrSegClient, Parent->getDataGroupId(), false );
      if( dstrCotClient == COADLG::STRING_Y && ( hasReadPermission( UAF::SEG_FUND_MULTI_CONTRACT ) || hasReadPermission( UAF::SEG_FUND_CONTRACT ) ) )
      {
         addCOARow( SCR_CONTRACT_ID, IDS_SCR_CONT, COA_TYPE_ATTRIB, COADLG::CMD_CONT, true,  TTL_SCREENS_ID, GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE );
      }

      // next code is commented because CBO dose account number validation and account number
      // is invalide at this moment.
      // DString dstrSegClient;
      // dstWorkSession->getOption( ifds::SegClient, dstrSegClient, Parent->getDataGroupId(), false );
      // if ( dstrSegClient == COADLG::STRING_Y && hasPermission( UAF::SEG_FUND_GUARANTEE, ifds::InqPerm ) )  
      // {
      //    addCOARow( SCR_GUARANTEE_ID, IDS_SCR_GUAR, COA_TYPE_ATTRIB, COADLG::CMD_GUAR, true,  TTL_SCREENS_ID, GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE );
      // }

      DString dstrResClient;
      dstWorkSession->getOption (ifds::ResClient, dstrResClient, Parent->getDataGroupId(), false);
      
      bool bIsRes2 = dstWorkSession->isRES2Client (Parent->getDataGroupId());
      
      if( hasReadPermission( UAF::RESP_INFO ) && 
         ( dstrResClient == COADLG::STRING_Y && ( dstrTaxType == I_( "9" ) || 
                                                  dstrTaxType == I_( "M" ) ) ) && !bIsRes2)
      {
         addCOARow (SCR_RESP_ID, IDS_SCR_RESP, COA_TYPE_ATTRIB, COADLG::CMD_RESP, true,  TTL_SCREENS_ID, GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE);
      }

      addCOARow( GST_EXEMPT_ID, IDS_GST_EXEMPT, COA_TYPE_CAUTION, _T(""), false, TTL_FEES_ID, GX_IDS_CTRL_CBS_DROPDOWNLIST );
      addCOARow( PST_EXEMPT_ID, IDS_PST_EXEMPT, COA_TYPE_CAUTION, _T(""), false, TTL_FEES_ID, GX_IDS_CTRL_CBS_DROPDOWNLIST );

      DString dstrCommissionType;
      dstWorkSession->getOption( ifds::CommissionType, dstrCommissionType, Parent->getDataGroupId(), false );
      if( dstrCommissionType == I_( "2" ) )
      {
         addCOARow( SCR_ACCT_SPLIT_COMM, IDS_SCR_ACCT_SPLIT_COMM, COA_TYPE_ATTRIB,  COADLG::CMD_ACCT_SPLIT_COMM,  true,  TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE );
      }
      // Add pay fee row
      addCOARow( FEE_MGMT_FEE_PAY_OPTN, IDS_MGMT_FEE_PAY_OPTN, COA_TYPE_CAUTION, _T(""), false,  TTL_FEES_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_FIELD_SUBST );

      if( hasReadPermission( UAF::DIRECT_TRADING_AGREEMENT) && pMFAccount->isAcctDTAEligible(Parent->getDataGroupId()) )
      {
         addCOARow( SCR_DIRECT_TRADING, IDS_SCR_DIRECT_TRADING, COA_TYPE_ATTRIB,  COADLG::CMD_DIRECT_TRADING_AGREEMENT,  true,  TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE );
      }

      DString dstrLockedInPlans;
      dstWorkSession->getOption(ifds::IntLockInPlan, dstrLockedInPlans, Parent->getDataGroupId(), false);

      if (DSTCommonFunctions::codeInList (dstrTaxType, dstrLockedInPlans))
      {
         addCOARow (MSC_UNLOCK_DATE,   IDS_MSC_UNLOCK_DATE,   COA_TYPE_CAUTION, _T(""), false, TTL_MISC_ID, GX_IDS_CTRL_STATIC);
         addCOARow (MSC_UNLOCK_AMOUNT, IDS_MSC_UNLOCK_AMOUNT, COA_TYPE_CAUTION, _T(""), false, TTL_MISC_ID, GX_IDS_CTRL_STATIC);
      }

      if (DSTCommonFunctions::codeInList (dstrTaxType, COADLG::RESP_TAX_TYPES)) 
      {
         if (hasReadPermission( UAF::RESP_ACCOUNT_TERMINATION ))
         {
            addCOARow(SCR_RESP_ACCOUNT_TERMINATION, IDS_SCR_ACCOUNT_TERMINATION, COA_TYPE_OPTION, COADLG::CMD_BPROC_RESP_ACCOUNT_TERMINATION, true,  TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE);
         }

         if (hasReadPermission( UAF::RESP_ZERO_GRANT ))
         {
            addCOARow(SCR_RESP_ZERO_GRANT, IDS_SCR_ZERO_GRANT_REPAYMENT, COA_TYPE_OPTION, COADLG::CMD_BPROC_ZERO_GRANT_REPAYMENT, true,  TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE);
         }

         if (hasReadPermission( UAF::RESP_INTERFACE_FILE ))
         {
            addCOARow(SCR_RESP_INTERFACE_FILE, IDS_SCR_INTERFACE_FILE, COA_TYPE_OPTION, COADLG::CMD_BPROC_INTERFACE_FILE, true,  TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE);
         }

         if (hasReadPermission( UAF::RESP_GOVT_FILING_AMENDMENT ))
         {
            addCOARow(SCR_RESP_GOVT_FILING_AMENDMENT, IDS_SCR_RESP_GOVT_FILING_AMENDMENT, COA_TYPE_OPTION, COADLG::CMD_BPROC_GOVT_FILING_AMENDMENT, true,  TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE);
         }

		 if (hasReadPermission( UAF::RESP_BENEFICIARY ) && hasReadPermission( UAF::RESP_GRANTS ))
		 {
			 addCOARow(SCR_RESP_GRANT_INFO, IDS_SCR_RESP_GRANT_INFO, COA_TYPE_OPTION, COADLG::CMD_RESP_GRANTS, true,  TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE);
		 }

		 if (hasReadPermission( UAF::RESP_BENEFICIARY ) && hasReadPermission( UAF::RESP_GRANT_INFORMATION ))
		 {
			 addCOARow(SCR_RESP_GRANT_INFO2, IDS_SCR_RESP_GRANT_INFO2, COA_TYPE_OPTION, COADLG::CMD_RESP_GRANTS2, true,  TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE);
		 }

		 if (hasReadPermission( UAF::RESP_NOTIONAL_ACTIVITY ))
		 {
			 addCOARow(SCR_RESP_NOTIONAL_ACTIVITY, IDS_SCR_RESP_NOTIONAL_ACTIVITY, COA_TYPE_OPTION, COADLG::CMD_RESP_NOTIONAL_ACTIVITY, true,  TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE);
		 }
      }
      else if (dstrTaxType == I_( "V" ))
      {
         if (hasReadPermission( UAF::TFSA_AMENDMENT ))//IN2747587 - guifn 223 - TFSA Amendment
         {
            addCOARow(SCR_RESP_GOVT_FILING_AMENDMENT, IDS_SCR_RESP_GOVT_FILING_AMENDMENT, COA_TYPE_OPTION, COADLG::CMD_BPROC_GOVT_FILING_AMENDMENT, true,  TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE);
         }  
      }

      DString dstrGuaranteeGuardOn, dstrAccountNum;
      dstWorkSession->getOption ( ifds::GuaranteeGuardOn, dstrGuaranteeGuardOn, Parent->getDataGroupId(), false );
      dstrGuaranteeGuardOn.strip().upperCase();

      getParent()->getField(this, ifds::AccountNum, dstrAccountNum);

      if ( dstrCotClient == COADLG::STRING_Y && dstrSegClient == COADLG::STRING_Y && 
           dstrGuaranteeGuardOn == COADLG::STRING_Y && 
           dstWorkSession->isGuarGuardAllowed(dstrAccountNum, Parent->getDataGroupId()) /* View 83 */ &&
           hasReadPermission (UAF::ACCT_GUARNT_GUARD_OPTN))
      {
         addCOARow( SCR_ACCT_GUARNT_GUARD_OPTN, IDS_SCR_ACCT_GUARNT_GUARD_OPTN, COA_TYPE_OPTION, COADLG::CMD_ACCT_GUARNT_GUARD_OPTN, true,  TTL_SCREENS_ID, GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE );
      }

	  if (hasReadPermission( UAF::MATURITYSWPEEP_INSTR ))
      {
			DString dstrCanHaveCashSweep;
			DString dstrCanHaveMatInstr;
					
            getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::CanHaveCashSweep, dstrCanHaveCashSweep, false );
            getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::CanHaveMatInstr, dstrCanHaveMatInstr, false );

			if (dstrCanHaveCashSweep == COADLG::STRING_Y)
			{
				addCOARow(SCR_CASHSWEEP_INSTR, IDS_SCR_CASHSWPEEP_INSTR , COA_TYPE_OPTION, COADLG::CMD_CASH_SWEEP_INSTRUCTIONS, true,  TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE);
			}

			if (dstrCanHaveMatInstr == COADLG::STRING_Y)
			{
				addCOARow(SCR_MATURITYINT_INSTR, IDS_SCR_MATURITYINT_INSTR, COA_TYPE_OPTION, COADLG::CMD_MATINTEREST_INSTRUCTIONS, true,  TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE);
			}
      }

      if(hasReadPermission(UAF::VALUE_VARIATION))
      {
         addCOARow(SCR_VALUE_VARIATION, IDS_SCR_VALUE_VARIATION , COA_TYPE_ATTRIB, COADLG::CMD_VALUE_VARIATION, true,  TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE);
      }
   }

   DString examptDate, dstrTaxType;
   getParent()->getField(this, ifds::TaxType, dstrTaxType, false ); 
   //Parent->getField( this,  ifds::ExemptPeriod, examptDate);
   dstrTaxType.strip().upperCase();

   //if (!examptDate.empty () && dstrTaxType != TFSA_TAX_TYPES)
   //{
   //   addCOARow (MSC_EXEMPT_PERIOD,IDS_EXEMPT_PERIOD, COA_TYPE_CAUTION, _T(""), false, TTL_MISC_ID, GX_IDS_CTRL_STATIC);
   //}

    // Add Tax Exempt Authorization
    DString dstrRegisteredTaxTypes, dstrEUSDParticip;
    dstWorkSession->getOption(ifds::RegisteredTaxTypes, dstrRegisteredTaxTypes, Parent->getDataGroupId(), false);

    dstWorkSession->getOption(ifds::EUSDParticip, dstrEUSDParticip, Parent->getDataGroupId(), false);

    if ( hasReadPermission( UAF::TAX_EXEMPT_AUTHORIZATION) && 
        (DSTCommonFunctions::codeInList (dstrTaxType, dstrRegisteredTaxTypes) || (dstrEUSDParticip == I_( "Y" ))) )
    {
        addCOARow( SCR_TAX_EXEMPT_AUTHORIZATION_ID, IDS_SCR_TAX_EXEMPT_AUTHORIZATION, COA_TYPE_ATTRIB, COADLG::CMD_TAX_EXEMPT_AUTHORIZATION, true, TTL_SCREENS_ID, GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE);
    }

   addCOARow( SCR_DOC_LIST_ID,   IDS_SCR_DOC_LIST,      COA_TYPE_OPTION,  COADLG::CMD_DOCLIST,   true,  TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE );

	if (hasReadPermission(UAF::ACCT_REGIS_MAINT))
	{
		if(!m_lInNASU)        // Currently there is no update mode, so this should not be actived for NASU.	
		addCOARow(SCR_ACCT_REGIS_MAINT, IDS_ACCT_REG_DETAILS,  COA_TYPE_OPTION,  COADLG::CMD_ACCT_REG_DETAILS,  true,  TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE );
		
	}

	if (hasReadPermission(UAF::ENTITY_REGULATORY_MAINT)) 
	{
		if(!m_lInNASU)		// No COA for this during NASU. If users have to setup this, GC has to be actived and screen will be popup during NASU.	
		addCOARow(SCR_ENT_REGIS_MAINT, IDS_ENT_REG_DETAILS,  COA_TYPE_OPTION,  COADLG::CMD_ENT_REG_DETAILS,  true,  TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE );
	}

   if (strMarket == MARKET_IDS::LUXEMBOURG)
   {
      DString dstrTaxType;
      getParent()->getField(this, ifds::TaxType, dstrTaxType, false );
      dstrTaxType.strip().upperCase();

      if( hasReadPermission( UAF::AS_PENSION_PLAN ) && dstrTaxType == I_( "P" ) )
      {
         addCOARow( SCR_AS_PENSION_PLAN_ID, IDS_SCR_AS_PENSION,  COA_TYPE_ATTRIB,  COADLG::CMD_ASPENSION,  true,  TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE );
      }
      else if( (dstrTaxType == ESOP_INVESTMENT || dstrTaxType == ESOP_PARTICIPATION) && hasReadPermission( UAF::ESOP ) )
      {
         addCOARow( SCR_ESOP_ID, IDS_SCR_ESOP,  COA_TYPE_ATTRIB,  COADLG::CMD_ESOP,  true,  TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE );
      }
      addCOARow( STP_REDEM_SETTLE_ID,  IDS_STOP_REDEEMPTION_SETTLE,     COA_TYPE_CAUTION, _T(""),   
                 false, TTL_STOPS_ID,   GX_IDS_CTRL_CBS_DROPDOWNLIST );
   }

   addCOARow( SCR_BENEF_ID,        IDS_SCR_BENEF,        COA_TYPE_OPTION,  COADLG::CMD_ENTITY, true,  TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE );
   addCOARow( FEE_BANK_CHARGE_ID,  IDS_FEE_BANK_CHARGE,  COA_TYPE_CAUTION, _T(""),             false, TTL_FEES_ID,     GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_FIELD_SUBST );
   addCOARow( MSC_CONSOLID_EFT_ID, IDS_MSC_CONSOLID_EFT, COA_TYPE_CAUTION, _T(""),             false, TTL_MISC_ID,     GX_IDS_CTRL_CBS_DROPDOWNLIST );
   addCOARow( MSC_ID_SIBLING_ONLY, IDS_MSC_SIBLING_ONLY, COA_TYPE_CAUTION, _T(""),             false, TTL_MISC_ID,     GX_IDS_CTRL_CBS_DROPDOWNLIST );

   //addCOARow( SCR_ESCROW_ID, IDS_SCR_ESCROW,    COA_TYPE_CAUTION, COADLG::CMD_ESCROW, false, TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE );

   addCOARow( FEE_FEEWVD_ID, IDS_FEE_FEEWVD,    COA_TYPE_CAUTION, _T(""),             false, TTL_FEES_ID,    GX_IDS_CTRL_CBS_DROPDOWNLIST );

   addCOARow( SPR_EMPCNF_ID, IDS_SPR_EMPCNF,    COA_TYPE_CAUTION, _T(""),             false, TTL_SUPRESS_ID, GX_IDS_CTRL_CBS_DROPDOWNLIST );
   addCOARow( SPR_CONFIRM_ID,IDS_SPR_CONFIRM,   COA_TYPE_CAUTION, _T(""),             false, TTL_SUPRESS_ID, GX_IDS_CTRL_CBS_DROPDOWNLIST );

   addCOARow( MSC_EMPL_ID,   IDS_MSC_EMPL,      COA_TYPE_CAUTION, _T(""),             false, TTL_MISC_ID,    GX_IDS_CTRL_EDIT             );
   //addCOARow( MSC_INTRFOR_ID,IDS_MSC_INTRFOR,   COA_TYPE_ATTRIB,  _T(""),             false, TTL_MISC_ID,    GX_IDS_CTRL_CBS_DROPDOWNLIST );
   
   addCOARow( MSC_NONFINANCIAL_CONFIRM,   IDS_NONFINANCIAL_CONFIRM,      COA_TYPE_CAUTION, _T(""),             false, TTL_MISC_ID,    GX_IDS_CTRL_CBS_DROPDOWNLIST             );
   addCOARow( MSC_SETTLEMENT_CURRENCY,    IDS_SETTLEMENT_CURRENCY,       COA_TYPE_CAUTION, _T(""),             false, TTL_MISC_ID,    GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_FIELD_SUBST);
      
   addCOARow( MSC_UNSZBL_ID, IDS_MSC_UNSZBL,    COA_TYPE_CAUTION, _T(""),             false, TTL_MISC_ID,    GX_IDS_CTRL_CBS_DROPDOWNLIST );
   addCOARow( MSC_TELFAX_AGREEMENT_ID, IDS_MSC_TELFAX,    COA_TYPE_CAUTION, _T(""),   false, TTL_MISC_ID,    GX_IDS_CTRL_CBS_DROPDOWNLIST );

   addCOARow( MSC_PW_CONSOL_TYPE_ID, IDS_PW_MSC_CONSOL_TYPE,    COA_TYPE_CAUTION, _T(""),   true, TTL_MISC_ID,    GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_FIELD_SUBST );
   addCOARow( MSC_ID_CONSOL_TYPE_ID, IDS_ID_MSC_CONSOL_TYPE,    COA_TYPE_CAUTION, _T(""),   true, TTL_MISC_ID,    GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_FIELD_SUBST );
   addCOARow( MSC_ED_CONSOL_TYPE_ID, IDS_ED_MSC_CONSOL_TYPE,    COA_TYPE_CAUTION, _T(""),   true, TTL_MISC_ID,    GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_FIELD_SUBST );

   DString dstraggrActiveAtEnv;
   dstWorkSession->getOption( ifds::AggActive, dstraggrActiveAtEnv, Parent->getDataGroupId(), false); 
   dstraggrActiveAtEnv.upperCase();
   if( I_("Y") == dstraggrActiveAtEnv ) 
   {
     addCOARow( MSC_AGGREGATION_TYPE,  TXT_AGGREGATION_TYPE ,   COA_TYPE_CAUTION, _T(""),   true, TTL_MISC_ID,    GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_FIELD_SUBST );
   }
   // Account Review
   DString dstrReviewDateFlag;
   //DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
   MgmtCoOptions *pMgmtCoOptions = dstWorkSession->getMgmtCoOptions();
   if( pMgmtCoOptions )
   {
      pMgmtCoOptions->getField( ifds::ReviewDateFlag, dstrReviewDateFlag, Parent->getDataGroupId(), false );
   }
   if( dstrReviewDateFlag == I_("Y") && hasReadPermission( UAF::ACCOUNTREVIEW ) )
   {
      addCOARow( SCR_ACCOUNTREVIEW_ID, IDS_SCR_ACCOUNTREVIEW, COA_TYPE_ATTRIB, COADLG::CMD_ACCOUNTREVIEW, true,  TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE );
   }

   //*/ AMS Details
   {
      DString dstrAMSAnOption;
      DString dstrAcctStatus, dstrAcctStatusUnFormated;
      getParent()->getField( this, BF::NullContainerId, COAPROC::AMSOption, dstrAMSAnOption );
      getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::AcctStatus, dstrAcctStatus );
      getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::AcctStatus, dstrAcctStatusUnFormated, false );

      //Show AMS option only when account is 'Active'.
      if( dstrAMSAnOption == I_("Y") && dstrAcctStatusUnFormated.strip().upperCase() == ACCT_STATUS_ACTIVE)
      {
         addCOARow( SCR_AMS_ID, IDS_SCR_AMSUPDATE, COA_TYPE_OPTION, COADLG::CMD_AMSACCTLVL, true,  TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE );
      }
   }//*/   

   // Shareholder family
   addCOARow(SCR_SHR_FAMILY_ID, IDS_SHR_FAMILY, COA_TYPE_OPTION, COADLG::CMD_SHR_FAMILY, true,  TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE);

   // Early redemtion fee
   addCOARow(FEE_EARLY_REDEMPTION_FEE_OPT, IDS_EARLY_REDEMPTION_FEE, COA_TYPE_CAUTION, _T(""), false, TTL_FEES_ID, GX_IDS_CTRL_CBS_DROPDOWNLIST );

   // Short term transfer fee
   addCOARow(FEE_SHORT_TERM_TRFER_FEE,    IDS_SHORT_TERM_TRFER,    COA_TYPE_CAUTION, _T(""), false, TTL_FEES_ID, GX_IDS_CTRL_CBS_DROPDOWNLIST );

   // Next MFR Process Date
   DString dstrIsMFRAccount;

   getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::IsMFRAccount, dstrIsMFRAccount, false );

   if (dstrIsMFRAccount == COADLG::STRING_Y)
      addCOARow(FEE_NEXT_MFR_PROCESS_DATE,    IDS_NEXT_MFR_PROCDATE,    COA_TYPE_CAUTION, _T(""), false, TTL_FEES_ID, GX_IDS_CTRL_STATIC );

   if ( hasReadPermission(UAF::ACCT_CATEGORY) || hasReadPermission(UAF::ACCT_CATEGORY_PRIVATE_WEALTH_OPT_OUT))
      addCOARow(SCR_ACCT_CATEGORY_ID, IDS_SCR_ACCT_CATEGORY, COA_TYPE_OPTION, COADLG::CMD_ACCT_CATEGORY, true,  TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE);

   // Settlement Location
   addCOARow(SCR_ACCT_SETTLE_LOC, IDS_ACCT_LVL_SETTLEMENT_LOCATION, COA_TYPE_OPTION, COADLG::CMD_ACCT_SETTLE_LOC, true, TTL_SCREENS_ID, GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE );

   // Fund Sponsor Agreement
   bool blFundSponsorAgreeement = hasReadPermission( UAF::SHR_FUND_SPONSOR_AGREEMENT );
   if( blFundSponsorAgreeement)
   {
      addCOARow( SCR_SHR_FUND_SPONSOR_AGREEMENT, IDS_SCR_SHR_FUND_SPONSOR_AGREEMENT, COA_TYPE_OPTION, COADLG::CMD_SHR_FUND_SPONSOR_AGREEMENT, true, TTL_SCREENS_ID, GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE );
   }

   // Fund Broker
   bool blFundBroker = hasReadPermission( UAF::SHR_FUND_BROKER );
   if( blFundBroker )
   {
      addCOARow( SCR_SHR_FUND_BROKER, IDS_SCR_SHR_FUND_BROKER, COA_TYPE_OPTION, COADLG::CMD_SHR_FUND_BROKER, true, TTL_SCREENS_ID, GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE );
   }

   // Clearing ID
   addCOARow( MSC_CLEARING_ID, IDS_CLEARING_ID, COA_TYPE_CAUTION, _T(""), false,  TTL_MISC_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_FIELD_SUBST, true );

   // Marketing Mailing
   addCOARow( MSC_MARKET_MAIL, IDS_MARKET_MAIL, COA_TYPE_CAUTION, _T(""), false,  TTL_MISC_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_FIELD_SUBST, false );

   // Affluent
   addCOARow (MSC_AFFLUENT, IDS_MSC_AFFLUENT, COA_TYPE_CAUTION, _T(""), false, TTL_MISC_ID, GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_FIELD_SUBST, false);

   //Organisation Type
   addCOARow (MSC_ORGTYPE, IDS_MSC_ORGTYPE, COA_TYPE_CAUTION, _T(""), false, TTL_MISC_ID, GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_FIELD_SUBST, false);
   //Sub Organisation Type
   addCOARow (MSC_SUBORGTYPE, IDS_MSC_SUBORGTYPE, COA_TYPE_CAUTION, _T(""), false, TTL_MISC_ID, GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_FIELD_SUBST, false);

   //Network Order Type
   addCOARow( MSC_NETWORK_ID, IDS_NETWORK_ID, COA_TYPE_CAUTION, _T(""), false,  TTL_MISC_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_FIELD_SUBST, true );

   //Document Print Format
   addCOARow( MSC_DOC_PRINT_FORMAT, IDS_DOC_PRINT_FORMAT, COA_TYPE_CAUTION, _T(""), false,  TTL_MISC_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_FIELD_SUBST, false );

   if ( hasReadPermission(UAF::ACCOUNT_FEE_MODEL) )
   addCOARow(SCR_ACCT_FEE_MODEL, IDS_SCR_ACCT_FEE_MODEL, COA_TYPE_OPTION, COADLG::CMD_BPROC_FUNDSPONSOR_FEE_MODEL, true,  TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE);

   DString dstrNSCCCompliant, dstrBrokerCode;
   pMFAccount->getField ( ifds::BrokerCode, dstrBrokerCode, getParent()->getDataGroupId() );
   dstWorkSession->getOption( ifds::NSCCCompliant, dstrNSCCCompliant, getParent()->getDataGroupId(), false );
   bool NSCCApply = dstrNSCCCompliant == COADLG::STRING_Y && pMFAccount->isBrokerNSCCCompliant(dstrBrokerCode, getParent()->getDataGroupId());
   if( NSCCApply )
   {
      // Networkcontrolind	   
      addCOARow( MSC_NETWORKCONTROLIND, IDS_MSC_NETWORKCONTROLIND, COA_TYPE_CAUTION, _T(""), false,  TTL_NSCC_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_FIELD_SUBST, false );

      // ClearingFirm 
      addCOARow( NSC_CLEARINGFIRM, IDS_NSC_CLEARINGFIRM, COA_TYPE_CAUTION, _T(""), true, TTL_NSCC_ID, GX_IDS_CTRL_EDIT, CHOICE_TYPE_CHANGE );

      // Participant ID
      addCOARow( NSC_PARTICIPANTID,IDS_NSC_PARTICIPANTID, COA_TYPE_CAUTION, _T(""), true,TTL_NSCC_ID, GX_IDS_CTRL_STATIC, CHOICE_TYPE_CHANGE );

      // AgentForFirm
      addCOARow( NSC_AGENTFORFIRM, IDS_NSC_AGENTFORFIRM, COA_TYPE_CAUTION, _T(""), true, TTL_NSCC_ID, GX_IDS_CTRL_EDIT, CHOICE_TYPE_CHANGE );

      // TPA
      addCOARow( NSC_TPA,          IDS_NSC_TPA,          COA_TYPE_CAUTION, _T(""), true, TTL_NSCC_ID, GX_IDS_CTRL_EDIT, CHOICE_TYPE_CHANGE );

      // Social Code
      addCOARow( NSC_SOCIAL_CODE, IDS_NSC_SOCIAL_CODE, COA_TYPE_CAUTION, _T(""), false,  TTL_NSCC_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_FIELD_SUBST, false );
   }

   // Account Cut Off Times
   if( hasReadPermission( UAF::ACCT_LVL_CUT_OFF_TIME ) )
   {
      addCOARow( SCR_ACCT_CUT_OFF_ID, COA_TXT_ACCT_CUT_OFF_TIME, COA_TYPE_OPTION, COADLG::CMD_BPROC_ACCT_LVL_CUT_OFF_TIMES, TRUE,  TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE);
   }

   //if ( hasReadPermission(UAF::FUND_CLASS_LIMITATION) )
      addCOARow(SCR_FUND_CLASS_LIMITATION, COA_TXT_FUND_CLASS_LIMITATION, COA_TYPE_OPTION, COADLG::CMD_BPROC_FUND_CLASS_LIMITATION, true,  TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE);

   // Account level settlement rule screen
   addCOARow(SCR_ACCT_LEVEL_SETTLEMENT_RULE, COA_TXT_ACCT_LEVEL_SETTLEMENT_RULE, COA_TYPE_OPTION, COADLG::CMD_ACCT_SETTLEMENT_RULE, true,  TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE);

   DString strEligible;
   getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::EligExtTrfGainLoss, strEligible, false );
   if( strEligible.strip() == I_("Y") )
   {
      CString cstrLIFGainLoss;
      cstrLIFGainLoss.LoadString( COA_TXT_LIF_GAIN_LOSS );
      DString strTaxTypeDesc;
      getParent()->getField( this, ifds::TaxType, strTaxTypeDesc, true );
      cstrLIFGainLoss = CString("   ") + strTaxTypeDesc.c_str() + CString(" ") + cstrLIFGainLoss.Trim();
      addCOARow( SCR_LIF_GAIN_LOSS_ID, cstrLIFGainLoss, COA_TYPE_ATTRIB,  COADLG::CMD_BPROC_LIF_GAIN_LOSS,  true,  TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE );
   }

   if( strMarket == MARKET_IDS::CANADA )
   {
      DString strIARuleSetup;
      getParent()->getField( this, ifds::IARuleSetup, strIARuleSetup, false );
      strIARuleSetup.strip().upperCase();

      DString dstrDirDepsBnkApplicable;
      dstWorkSession->getOption (ifds::DirectDepositBankApplicable, 
                                 dstrDirDepsBnkApplicable, 
                                 BF::HOST,
                                 false );
      dstrDirDepsBnkApplicable.strip().upperCase();

      //if (strIARuleSetup == I_("Y") && dstrDirDepsBnkApplicable == I_("Y"))
      if ( dstrDirDepsBnkApplicable == I_("Y"))
      {
         addCOARow(SCR_INVESTOR_AUTHORIZATION, 
                   COA_TXT_INVESTOR_AUTHORIZATION, 
                   COA_TYPE_OPTION, 
                   COADLG::CMD_INVESTOR_AUTHORIZATION, 
                   true,  
                   TTL_SCREENS_ID,  
                   GX_IDS_CTRL_CBS_DROPDOWNLIST, 
                   CHOICE_TYPE_CHANGE);
      }
   }

   if(dstWorkSession->isTaxAnniversaryClient(getParent()->getDataGroupId()))
   {
      addCOARow(MSC_T5_ANNIVERSARY_DATE, IDS_T5_ANNIVERSARY_DATE, COA_TYPE_CAUTION, _T(""), false, TTL_MISC_ID, GX_IDS_CTRL_STATIC );  
   }

   //P0186486_FN16_Misc. Enhancements_Stop Adjustment Date
   addCOARow( MSC_STOP_ADJDATE,   IDS_MSC_STOP_ADJDATE, COA_TYPE_CAUTION, _T(""),  false , TTL_MISC_ID, GX_IDS_CTRL_DATETIME );
   // Investor Classification
   addCOARow( MSC_INVESTOR_CLASSIFICATION,    IDS_INVESTOR_CLASSIFICATION,       COA_TYPE_CAUTION, _T(""),             false, TTL_MISC_ID,    GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_FIELD_SUBST, true);
   addCOARow( SCR_ACCT_OWNERSHIP_ALLOC, 
              IDS_SCR_ACCT_OWNERSHIP_ALLOC, 
              COA_TYPE_OPTION, 
              COADLG::CMD_ACCT_OWNERSHIP_ALLOCATION, 
              TRUE,  
              TTL_SCREENS_ID,  
              GX_IDS_CTRL_CBS_DROPDOWNLIST, 
              CHOICE_TYPE_CHANGE);

   //DString dstrIsAcctAssociateExist;
   //getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::AcctFeeModelAssociated, dstrIsAcctAssociateExist, false );
   //dstrIsAcctAssociateExist.strip().upperCase();

   if (hasReadPermission( UAF::ACCT_FEE_MODEL_ASSOCIATION ))
   {              
      addCOARow( SCR_ACCT_FEE_MODEL_ASSOCIATION, 
                 IDS_SCR_FEE_MODEL_ASSOCIATION, 
                 COA_TYPE_OPTION, 
                 COADLG::CMD_ACCT_FEE_MODEL_ASSOCIATION, 
                 TRUE,  
                 TTL_SCREENS_ID,  
                 GX_IDS_CTRL_CBS_DROPDOWNLIST, 
                 CHOICE_TYPE_CHANGE);
   }

   if (hasReadPermission( UAF::SHR_STATEMENT_SCHED ))
   {              
      addCOARow( SCR_SHR_STATEMENT_SCHED, 
                 IDS_SCR_SHR_STATEMENT_SCHED, 
                 COA_TYPE_OPTION, 
                 COADLG::CMD_SHR_STATEMENT_SCHED, 
                 TRUE,  
                 TTL_SCREENS_ID,  
                 GX_IDS_CTRL_CBS_DROPDOWNLIST, 
                 CHOICE_TYPE_VIEW);
   }

   DString dstrTaxFormsAppl;
   pMFAccount->getField(ifds::TaxFormsAppl, dstrTaxFormsAppl, getParent()->getDataGroupId());
   if (dstrTaxFormsAppl.stripAll().upperCase() == I_("Y"))
   {
        addCOARow(SCR_TAX_SLIPS, 
                  IDS_TAX_SLIPS, 
                  COA_TYPE_ATTRIB, 
                  COADLG::CMD_TAX_SLIPS, 
                  TRUE,  
                  TTL_SCREENS_ID,  
                  GX_IDS_CTRL_CBS_DROPDOWNLIST, 
                  CHOICE_TYPE_VIEW);
   }

   if (hasReadPermission(UAF::ACCOUNT_GROUPING))
   {
      CString lDispName;
      lDispName.LoadString( TXT_ACCOUNT_GROUP_TITLE );
      lDispName = _T("   ") + lDispName;

      if(!m_lInNASU)
         addCOARow(SCR_ACCOUNT_GROUP, lDispName,  COA_TYPE_OPTION,  COADLG::CMD_ACCOUNT_GROUP,  true,  TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE );
   }

   if (hasReadPermission(UAF::PRIVATE_WEALTH_INFO))
   {
      CString lDispName;
      lDispName.LoadString( TXT_PRIVATE_WEALTH_INFO_TITLE );
      lDispName = _T("   ") + lDispName;

      if(!m_lInNASU)
         addCOARow(SCR_PRIVATE_WEALTH_INFO, lDispName,  COA_TYPE_OPTION,  COADLG::CMD_PRIVATE_WEALTH_INFO,  true,  TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE );
   }

   if (hasReadPermission(UAF::REG_PLAN_TRANSFER))
   {
      CString lDispName;
      lDispName.LoadString(TXT_REG_PLAN_TRANSFER);
      lDispName = _T("   ") + lDispName;

//      if(!m_lInNASU)
         addCOARow(SCR_REGISTERED_PLAN_TRANSFER, lDispName,  COA_TYPE_OPTION,  COADLG::CMD_REG_PLAN_TRANSFER,  true,  TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE );
   }

   // Account rounding rule screen
   if (hasReadPermission(UAF::ACCT_ROUNDING_RULE))
   {
      CString lDispName;
      lDispName.LoadString( TXT_ACCT_ROUNDING_RULE );
      lDispName = _T("   ") + lDispName;

      //if(!m_lInNASU)
         addCOARow(SCR_ACCT_ROUNDING_RULE, lDispName, COA_TYPE_OPTION, COADLG::CMD_ACCT_ROUNDING_RULE, true, TTL_SCREENS_ID, GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE );
   }

   // Account deletion review screen
   DString strAcctDelState;
   getParent()->getField( this, ifds::AcctDelState, strAcctDelState, false ); 
   strAcctDelState.strip().upperCase();
   if (strAcctDelState == I_("Y") && hasReadPermission(UAF::ACCT_DELETION_REVIEW))
   {
	   CString lDispName;
	   lDispName.LoadString( TXT_ACCT_DEL_REVIEW );
	   lDispName = _T("   ") + lDispName;

	   addCOARow(SCR_ACCT_DELETION_REVIEW, lDispName, COA_TYPE_OPTION, COADLG::CMD_ACCT_DELETION_REVIEW, true, TTL_SCREENS_ID, GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE );
   }

   if (dstrTaxType == COADLG::RDSP_TAX_TYPE) 
   {	   
	   if (hasReadPermission( UAF::RDSP_ACCOUNT_INFORMATION ))
	   {
		   addCOARow(SCR_RDSP_ACCOUNT_INFO, IDS_SCR_RDSP_ACCOUNT_INFO, COA_TYPE_OPTION, COADLG::CMD_RDSP_ACCOUNT_INFO, true,  TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE);
	   }
	   
	   if (hasReadPermission( UAF::RDSP_NOTIONAL_ACTIVITY ))
	   {
		   addCOARow(SCR_RDSP_NOTIONAL_ACTIVITY, IDS_SCR_RDSP_NOTIONAL_ACTIVITY, COA_TYPE_OPTION, COADLG::CMD_RDSP_NOTIONAL_ACTIVITY, true,  TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE);
	   } 

	   if (hasReadPermission( UAF::RDSP_NOTIONAL_BALANCE ))
	   {
		   addCOARow(SCR_RDSP_NOTIONAL_BALANCE, IDS_SCR_RDSP_NOTIONAL_BALANCE, COA_TYPE_OPTION, COADLG::CMD_RDSP_NOTIONAL_BALANCE, true,  TTL_SCREENS_ID,  GX_IDS_CTRL_CBS_DROPDOWNLIST, CHOICE_TYPE_CHANGE);
	   }   
   }

   m_gridWindow.SubclassDlgItem(IDC_COA_GRID, this);
   m_gridWindow.setCOADlg( this );
   m_gridWindow.Initialize();
   m_gridWindow.SetColCount(2);

   CString tmp;
   tmp.LoadString( IDS_CAT_ALL );
   m_cmbView.AddString( tmp );

   tmp.LoadString( IDS_CAT_CAUTIONS );
   m_cmbView.AddString( tmp );

   tmp.LoadString( IDS_CAT_OPTIONS );
   m_cmbView.AddString( tmp  );

   tmp.LoadString( IDS_CAT_ATTRIBS );
   m_cmbView.AddString( tmp  );
   m_cmbView.SetCurSel( 0 );

   CGXGridParam* cgxParam = m_gridWindow.GetParam( );
   cgxParam->EnableMoveRows( FALSE );
   cgxParam->EnableMoveCols( FALSE );
   cgxParam->EnableSelection( GX_SELROW );

   m_gridWindow.SetRowHeight(0,39,20);
/*   m_gridWindow.SetColWidth(0,0,400);
   m_gridWindow.SetColWidth(1,1,120);
   m_gridWindow.SetColWidth(2,2,80);   
*/
   m_gridWindow.LoadSettings();


   m_gridWindow.GetParam( )->EnableTrackRowHeight( 0 ); 

   tmp.LoadString( IDS_FIELD );
   m_gridWindow.SetStyleRange( CGXRange(0,0), CGXStyle().SetEnabled(FALSE).SetHorizontalAlignment( DT_LEFT )
                              .SetValue(tmp));

   tmp.LoadString( IDS_TYPE );
   m_gridWindow.SetStyleRange( CGXRange(0,1), CGXStyle().SetEnabled(FALSE).SetHorizontalAlignment( DT_LEFT )
                              .SetValue(tmp));

   tmp.LoadString( IDS_VALUE );
   m_gridWindow.SetStyleRange( CGXRange(0,2), CGXStyle().SetEnabled(FALSE).SetHorizontalAlignment( DT_LEFT )
                              .SetValue(tmp));

   reDisplayGrid();

   setTitlesButtonCaption( !m_ElementMap.hasExpandedTitles( ) );

   UpdateData(FALSE);

   return(TRUE);   
}

//*****************************************************************************
void COADlg::OnPostInitDialog()
{
    TRACE_METHOD( COADLG_CLASS, ONPOSTINITDIALOG );
/*
    GenericInterface* Parent = getParent();
    DString lAccountNbr, lShrNum, lEntityName, lInNASU;
    GetWindowText(m_strTitle) ;


    Parent->getField( this,  COAPROC::inNASU, lInNASU );
    lInNASU.strip();
    m_lInNASU = lInNASU == I_("Y");

    if( m_lInNASU )
    {
        Parent->getField( this,  ifds::AccountNum, lAccountNbr );
        Parent->getField( this,  ifds::ShrNum    , lShrNum     );
        Parent->getField( this,  ifds::Name1     , lEntityName );

        SetShrAcctCaption( lShrNum.strip(), lAccountNbr.strip(), lEntityName.strip() );
    };
*/
}

//******************************************************************************
void COADlg::selectItemInList( int index, const DString* key )
{
    TRACE_METHOD( COADLG_CLASS, I_("selectItemInList") );
}

//******************************************************************
bool COADlg::PreOk() 
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, COADLG_CLASS, I_( "PreOK" ));

    DString dstrTaxType;
    getParent()->getField(this, ifds::TaxType, dstrTaxType, false );

    DSTCWorkSession *pDSTWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());

    if( m_lInNASU &&  pDSTWorkSession->isIntRIFPlan (dstrTaxType))
		/*(dstrTaxType == I_( "B" ) || dstrTaxType == I_( "R" ) ||
        dstrTaxType == I_( "L" ) || dstrTaxType == I_( "2" ) ) )*/
    {
        AfxMessageBox(TXT_COA_RE_SET_UP, MB_OK);
    }

    bool     retVal = false;
    CGXStyle lCGXSt;
    CString  lChoiceList;
    COAElement * pCOAElem;
    COAElementMap::iterator Iter = m_ElementMap.begin();
    CString lStrValue;
    DString lStrCommand;
    ROWCOL nRow, nCol;

    int noItems = m_ElementMap.itemCount();

//   ROWCOL nEditRow, nEditCol;
//   m_gridWindow.GetCurrentCell(nEditRow, nEditCol)
    CGXControl* pControl = m_gridWindow.GetCurrentCellControl();
//	CGXControl* pControl = m_gridWindow.GetControl(nEditRow, nEditCol);
   if( pControl )
      pControl->OnValidate();

    m_gridWindow.UpdateData();

    // Warning Message if Clearing ID and no Settlement Location
    int ItemCount = m_ElementMap.itemCount();

    CString cstrClearingID, cstrSettleLoc;
    COAElementMap::iterator iter = m_ElementMap.find( COADlg::SCR_ACCT_SETTLE_LOC );
    if( iter != m_ElementMap.end() )
    {
        cstrSettleLoc = (*iter).second->getValue();
    }
    iter = m_ElementMap.find( COADlg::MSC_CLEARING_ID );
    if( iter != m_ElementMap.end() )
    {
        cstrClearingID = (*iter).second->getValue();
    }

    if( cstrClearingID.IsEmpty() == FALSE && cstrSettleLoc == COADLG::STRING_NO )
    {
        AfxMessageBox( TXT_SETTLE_LOC_WARNING, MB_OK);
    }

    // Error message if ClearingFirm is empty

    SetWarningConfirm( false );
    DString strChange,strView;
    getParent()->getField(this,BF::NullContainerId,COAPROC::lChange,strChange,true);
    getParent()->getField(this,BF::NullContainerId,COAPROC::lView,strView,true);   

    // For a Seg environment, don't allow a PAC/SWP/Savings Plan/AT during NASU.
    DString dstrSegClient, dstrCotClient;
    pDSTWorkSession->getOption( ifds::SegClient, dstrSegClient, getParent()->getDataGroupId(), false);
    pDSTWorkSession->getOption( ifds::CotClient, dstrCotClient, getParent()->getDataGroupId(), false);   
    if( m_lInNASU && dstrSegClient == I_( "Y" ) && dstrCotClient == I_( "Y" ) )
    {
        CString cstrTrade;
        iter = m_ElementMap.find( COADlg::SCR_PAC_ID );
        if( iter != m_ElementMap.end() )
        {
            cstrTrade = (*iter).second->getValue();
        }
        if( cstrTrade == strChange.c_str() )
        {
            CString cstrPAC;
			cstrPAC.LoadString(TXT_CREATE_PAC_AFTER_NEW_ACCT_SAVED);
			AfxMessageBox( cstrPAC, MB_OK);
            return false;
        }

        cstrTrade = _T( "" );
        iter = m_ElementMap.find( COADlg::SCR_SWP_ID );
        if( iter != m_ElementMap.end() )
        {
            cstrTrade = (*iter).second->getValue();
        }
        if( cstrTrade == strChange.c_str() )
        {
            CString cstrSWP;
			cstrSWP.LoadString(TXT_CREATE_SWP_AFTER_ACCT_SAVED);
			AfxMessageBox( cstrSWP, MB_OK);
            return false;
        }

        cstrTrade = _T( "" );
        iter = m_ElementMap.find( COADlg::SCR_SAVING_PLAN_ID );
        if( iter != m_ElementMap.end() )
        {
            cstrTrade = (*iter).second->getValue();
        }
        if( cstrTrade == strChange.c_str() )
        {
            CString cstrSavingPlan;
			cstrSavingPlan.LoadString(TXT_CREATE_SAVING_PLAN_AFTER_ACCT_SAVED);
			AfxMessageBox( cstrSavingPlan, MB_OK);
            return false;
        }

        cstrTrade = _T( "" );
        iter = m_ElementMap.find( COADlg::SCR_SYSTR_ID );
        if( iter != m_ElementMap.end() )
        {
            cstrTrade = (*iter).second->getValue();
        }
        if( cstrTrade == strChange.c_str() )
        {
            CString cstrSysTransfer;
			cstrSysTransfer.LoadString(TXT_CREATE_SYS_TRANSFER_AFTER_ACCT_SAVED );
			AfxMessageBox( cstrSysTransfer, MB_OK);
            return false;
        }
    }


    for( int i = 0; i < noItems; i++ )
    {
        pCOAElem = m_ElementMap[i];
        lStrValue = pCOAElem->getValue();
        lStrCommand = DString( pCOAElem->getCommand());



        if( lStrCommand != NULL_STRING && (lStrValue == strChange.c_str() || lStrValue == strView.c_str() ))
        //      ( lStrValue == COADLG::STRING_CHANGE || lStrValue == COADLG::STRING_VIEW ))
        {
            retVal = launchProcess( lStrCommand, pCOAElem->getId()  );
            retrieveValue( pCOAElem->getId() );
            pCOAElem->setChoiceList( );
            m_gridWindow.SetStyleRange(CGXRange( i + 1,2), CGXStyle().SetControl(GX_IDS_CTRL_CBS_DROPDOWNLIST).
                                    SetChoiceList( pCOAElem->getChoiceList()).SetValue(pCOAElem->getValue( )).SetVerticalAlignment(DT_VCENTER) );

            //begin stupid hack Objective grid does not change the choice list on the current cell until it is changed
            m_gridWindow.GetCurrentCell(nRow, nCol);
            if( nRow == i + 1 && nCol == 2 )
            {
                m_gridWindow.SetCurrentCell( 1,    2, GX_SCROLLINVIEW | GX_UPDATENOW );
                m_gridWindow.SetCurrentCell( nRow, nCol, GX_SCROLLINVIEW | GX_UPDATENOW );
            };
            //end stupid hack 

            CString strStyleVal = _T(""); 
            CGXStyle   sty;
            m_gridWindow.GetStyleRowCol(i + 1,2, sty);
            strStyleVal = sty.GetChoiceList();
            if( retVal == false )
                return(false);
        }
    }

    if ( !validateClearingFirm() )
        return (false);

    if ( !validateAffluent() )
        return (false);

	validateSubOrgType();
    /*
    CONDITIONVECTOR conVector;
    SEVERITY sevRtn = getParent()->getErrors( this,IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::NullFieldId,
                                              conVector );

    if( sevRtn >= WARNING )
    {
        ConditionMessageBox(conVector, sevRtn);   
    }*/

    return(true);
}

//******************************************************************
bool COADlg::launchProcess( const DString & procId, COA_ENTRY_ID lId  )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, COADLG_CLASS, I_( "launchProcess" ));

   DString lAcctNum;
   DString lShareholderNum;

   E_COMMANDRETURN eRtn;
   getParent()->getField(this, ifds::AccountNum, lAcctNum );
   getParent()->getField(this, ifds::ShrNum, lShareholderNum );

   lAcctNum.strip().stripLeading('0');
   lShareholderNum.strip().stripLeading('0');

   getParent()->setParameter (I_("FromScreen"), I_("COA"));

   if( procId == COADLG::CMD_REMARK )
   {
      getParent()->setParameter( I_("AccountNum"),lAcctNum); 
      getParent()->setParameter( I_("lShareholderNum"),lShareholderNum); 
   }
    else if( procId == COADLG::CMD_ACCOUNTREVIEW )
    {
        getParent()->setParameter( I_("AccountNum"), lAcctNum);
    }
    else if( procId == COADLG::CMD_AMSACCTLVL )
    {
        getParent()->setParameter( I_("AccountNum"), lAcctNum);
    }
   else if( procId == COADLG::CMD_BANK )
   {
        getParent()->setParameter (MFCAN_IP_PARAM::BANK_TYPE, 
            BANKTYPE::SHAREHOLDER); 
        getParent()->setParameter (MFCAN_IP_PARAM::ACCOUNT_NUM, 
            lAcctNum); 
   } 
   else if( procId == COADLG::CMD_CASH_SWEEP_INSTRUCTIONS ||  procId == COADLG::CMD_MATINTEREST_INSTRUCTIONS)
   {
      getParent()->setParameter (MFCAN_IP_PARAM::ACCOUNT_NUM, lAcctNum);
      getParent()->setParameter (CALLER, I_("AcctCOA"));

      DString InstrType = lId == SCR_CASHSWEEP_INSTR ? CASH_SWEEP_INSTR : MATURITY_INSTR;
      getParent()->setParameter (MFCAN_IP_PARAM::RESET, I_("Y"));

      getParent()->setParameter (INSTR_TYPE, InstrType);
   } 
   else if( procId == COADLG::CMD_DOCLIST )
   {
      getParent()->setParameter (MFCAN_IP_PARAM::ACCOUNT_NUM, lAcctNum); 
      getParent()->setParameter (CALLER, I_("AcctCOA")); 
   }
   else if( procId == COADLG::CMD_PAC )
   {
        getParent()->setParameter( I_("AccountNum"),lAcctNum); 
        if( lId == SCR_PAC_ID )
            getParent()->setParameter( I_("TransType"), I_("P"));
        else if( lId == SCR_SWP_ID )
            getParent()->setParameter( I_("TransType"), I_("S"));
        else if( lId == SCR_SYSTR_ID )
            getParent()->setParameter( I_("TransType"), I_("AT"));
        else if( lId == SCR_SAVING_PLAN_ID )
            getParent()->setParameter( I_("TransType"), I_("V"));
   }
   else if( procId == COADLG::CMD_ALLOC )
   {
        getParent()->setParameter( I_( "Allocation Type" ), I_( "Shareholder Default") );
        getParent()->setParameter( I_("AccountNum"),lAcctNum); 
        getParent()->setParameter( I_( "Caller" ), I_( "Default") );
   }
   else if( procId == COADLG::CMD_ACB )
   {
        getParent()->setParameter( I_("AccountNum"),lAcctNum); 
   }
   else if( procId == COADLG::CMD_ADDR )
   {
        getParent()->setParameter( I_("ShareholderNum"),lShareholderNum); 
        getParent()->setParameter( I_("AccountNum"),lAcctNum); 
   }
   else if( procId == COADLG::CMD_ENTITY )
   {
        getParent()->setParameter( I_("AccountNum"),lAcctNum); 
   }
   else if( procId == COADLG::CMD_INTACR )
   {
        getParent()->setParameter( I_("AccountNum"),lAcctNum); 
    }
    else if( procId == COADLG::CMD_BPROC_ACCT_IDENTIFIER )
    {
       DString urlParamsIDI;

         DString dstrEntityName;
         dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->
            getFirstSequenced01AccountholderEntityName(getDataGroupId(),
                                                       lAcctNum,dstrEntityName);

       addIDITagValue (urlParamsIDI, I_("AccountNum"), lAcctNum);
       addIDITagValue (urlParamsIDI, I_("option"), I_("account"));
       addIDITagValue (urlParamsIDI, I_("screen"), I_("AccountIdentifier"));

       CString cstrAccountNumLabel;
	   CString cstrAccountHolderName;
       cstrAccountNumLabel.LoadString(TXT_ACCOUNT_NUM);
	   cstrAccountHolderName.LoadString(TXT_ACCT_HOLDER_NAME);

       getParent()->setParameter (I_("UrlParams"), urlParamsIDI);
	   CString accountIdentifierStr;
	   accountIdentifierStr.LoadString( ID_STR_ACCOUNT_IDENTIFIER );
 	   accountIdentifierStr += ":";

       DString strBrowserTitle(accountIdentifierStr);
	   strBrowserTitle += cstrAccountNumLabel;
       strBrowserTitle += lAcctNum;
       strBrowserTitle += I_(" ");
       strBrowserTitle += cstrAccountHolderName;
       strBrowserTitle += dstrEntityName;

       getParent()->setParameter (I_("BrowserTitle"), strBrowserTitle);
       getParent()->setParameter (I_("from_screen"), I_("COADlg"));
    }
    else if( procId == COADLG::CMD_ACCINF )
    {
        getParent()->setParameter( I_("AccountNum"),lAcctNum); 
    }
    else if( procId == COADLG::CMD_DISTR )
    {
        getParent()->setParameter( I_("AccountNum"),lAcctNum); 
    }
    else if( procId == COADLG::CMD_DEMOGR )
    {
        getParent()->setParameter( I_("AccountNum"),lAcctNum); 
    }
    else if( procId == COADLG::CMD_CERTIF )
    {
        getParent()->setParameter( I_("InAcctNum"),lAcctNum); 
    }
    else if( procId == COADLG::CMD_CHEQUE )
    {
        getParent()->setParameter( I_("AccountNum"),lAcctNum); 
		getParent()->setParameter( I_("Status"), I_("ALL")); 
    }
    else if( procId == COADLG::CMD_SHR )
    {
        getParent()->setParameter( I_( "CreatingShareholder" ), I_( "N" ) );
        getParent()->setParameter( I_("ShareholderNum"), lShareholderNum); 
        getParent()->setParameter( I_("AccountNum"), lAcctNum); 
    }
    else if( procId == COADLG::CMD_SYSTR )
    {
        getParent()->setParameter( I_("AccountNum"),lAcctNum); 
        getParent()->setParameter( I_("TransType"), I_("AT")); 

/*
        CsiSession& csiSession = CsiSession::getInstance();
        csiSession.setParameter( DcCsiParameters::ACCOUNT_NUMBER, DStringA(lAcctNum));
        csiSession.executeProcess( DcCsiProcesses::AUTOMATIC_TRANSFER_INFO );
        csiSession.clearParameters();
        return true;
*/
    }
    else if( procId == COADLG::CMD_FEES )
    {
        CsiSession& csiSession = CsiSession::getInstance();
        csiSession.setParameter( DcCsiParameters::ACCOUNT_NUMBER, DStringA(lAcctNum).getImp());
        csiSession.executeProcess( DcCsiProcesses::ACCOUNT_INFORMATION );
        csiSession.clearParameters();
        return(true);
    }
/*
    else if ( procId == COADLG::CMD_ESCROW )
    {
        CsiSession& csiSession = CsiSession::getInstance();
        csiSession.setParameter( DcCsiParameters::ACCOUNT_NUMBER, DStringA(lAcctNum));
        csiSession.executeProcess( DcCsiProcesses::LOCKED_IN_INFORMATION );
        csiSession.clearParameters();
        return true;
    }
*/
    else if( procId == COADLG::CMD_RRIF )
    {
        getParent()->setParameter( I_("AccountNum"),lAcctNum); 
    }
    else if( procId == COADLG::CMD_CONT )
    {
        getParent()->setParameter( I_("ShareholderNum"),lShareholderNum); 
        getParent()->setParameter( I_("AccountNum"),lAcctNum); 
    }

    else if( procId == COADLG::CMD_GUAR )
    {
        getParent()->setParameter( I_("ShareholderNum"),lShareholderNum); 
        getParent()->setParameter( I_("AccountNum"),lAcctNum); 
    }

    else if( procId == COADLG::CMD_RESP )
    {
        getParent()->setParameter( I_("ShareholderNum"),lShareholderNum); 
        getParent()->setParameter( I_("AccountNum"),lAcctNum); 
    }
    else if( procId == COADLG::CMD_YTD )
    {
        getParent()->setParameter( I_("ShareholderNum"),lShareholderNum); 
        getParent()->setParameter( I_("AccountNum"),lAcctNum); 
    }
    else if( procId == COADLG::CMD_ASPENSION )
    {
        getParent()->setParameter( I_("ShareholderNum"),lShareholderNum); 
        getParent()->setParameter( I_("AccountNum"),lAcctNum); 
    }
    else if( procId == COADLG::CMD_ESOP )
    {
        getParent()->setParameter( I_("AccountNum"),lAcctNum); 
    }
    else if( procId == COADLG::CMD_FEE_PARAMETER )
    {
        getParent()->setParameter( I_("AccountNum"),lAcctNum); 
    }
    else if (procId == COADLG::CMD_TRAILER_FEE)
    {
       DString urlParamsIDI;

       addIDITagValue (urlParamsIDI, I_("AccountNum"), lAcctNum);
       addIDITagValue (urlParamsIDI, I_("option"), I_("account"));
       addIDITagValue (urlParamsIDI, I_("screen"),I_("TrailerFeeSetup") );

       getParent()->setParameter (I_("UrlParams"), urlParamsIDI);
       CString cstrAcctTerm;
       cstrAcctTerm.LoadString(TXT_ACCT_TERMINATION);
       getParent()->setParameter (I_("BrowserTitle"), DString(cstrAcctTerm) + lAcctNum);
       getParent()->setParameter (I_("from_screen"), I_("COADlg"));
    }
    else if( procId == COADLG::CMD_PENSION_INFO )
    {
        getParent()->setParameter( I_("AccountNum"),lAcctNum);
    }

    else if( procId == COADLG::CMD_ACCT_SPLIT_COMM )
    {
        getParent()->setParameter( I_("AccountNum"),lAcctNum);
    }
    else if( procId == COADLG::CMD_HYPORED )
    {
        getParent()->setParameter( I_("AccountNum"),lAcctNum);
    }
    else if ( procId == COADLG::CMD_FOREIGN_CONTENT_WORKSHEET )
    {
        getParent()->setParameter( FOREIGN_CONTENT_WORKSHEET::ACCOUNT_NUMBER,     lAcctNum );		
        getParent()->setParameter( FOREIGN_CONTENT_WORKSHEET::SHAREHOLDER_NUMBER, lShareholderNum ); 
    }
    else if( procId == COADLG::CMD_SHR_FAMILY )
    {
        getParent()->setParameter( I_("AccountNum"),lAcctNum); 
        getParent()->setParameter( I_("ShareholderNum"),lShareholderNum);
    }
    else if ( procId == COADLG::CMD_ACCT_CATEGORY )
    {
        getParent()->setParameter( I_("AccountNum"),lAcctNum);
    }
    else if( procId == COADLG::CMD_DIRECT_TRADING_AGREEMENT )
    {
        getParent()->setParameter( I_("AccountNum"),lAcctNum);
    }
    else if( procId == COADLG::CMD_ACCT_SETTLE_LOC )
    {
        getParent()->setParameter( I_("AccountNum"),lAcctNum); 
    }
    else if( procId == COADLG::CMD_SHR_FUND_SPONSOR_AGREEMENT )
    {
        getParent()->setParameter( SHR_FUND_SPONSOR_AGREEMENT::ACCOUNT_NUMBER,     lAcctNum );		
        getParent()->setParameter( SHR_FUND_SPONSOR_AGREEMENT::SHAREHOLDER_NUMBER, lShareholderNum ); 
    }
    else if( procId == COADLG::CMD_SHR_FUND_BROKER )
    {
        getParent()->setParameter( SHR_FUND_BROKER::ACCOUNT_NUMBER,     lAcctNum );		
        getParent()->setParameter( SHR_FUND_BROKER::SHAREHOLDER_NUMBER, lShareholderNum ); 
    }
    else if( procId == COADLG::CMD_TAX_EXEMPT_AUTHORIZATION )
    {
        getParent()->setParameter( I_("AccountNum"),lAcctNum);
    }
    else if( procId == COADLG::CMD_BPROC_FUNDSPONSOR_FEE_MODEL )
    {
        getParent()->setParameter( I_( "from_screen" ),I_("Account")); 
        getParent()->setParameter( I_("AccountNum"),lAcctNum);
    }
    else if( procId == COADLG::CMD_BPROC_ACCT_LVL_CUT_OFF_TIMES )
    {
        getParent()->setParameter( I_("AccountNum"), lAcctNum );
    }
    else if (procId == COADLG::CMD_BPROC_FUND_CLASS_LIMITATION)
    {
       DString urlParamsIDI;

       addIDITagValue (urlParamsIDI, I_("AccountNum"), lAcctNum);
       addIDITagValue (urlParamsIDI, I_("option"), I_("account"));
       addIDITagValue (urlParamsIDI, I_("screen"),I_("OvrdLimit") );

       getParent()->setParameter (I_("UrlParams"), urlParamsIDI);
       CString cstrFundLmt;
       cstrFundLmt.LoadString(TXT_FUND_LIMITATION);
       getParent()->setParameter (I_("BrowserTitle"), DString(cstrFundLmt) + lAcctNum);
       getParent()->setParameter (I_("from_screen"), I_("COADlg"));
    }
    else if (procId == COADLG::CMD_BPROC_RESP_ACCOUNT_TERMINATION)
    {
       DString urlParamsIDI;

       addIDITagValue (urlParamsIDI, I_("AccountNum"), lAcctNum);
       addIDITagValue (urlParamsIDI, I_("option"), I_("account"));
       addIDITagValue (urlParamsIDI, I_("screen"), I_("RESPAcctTermInfo"));

       getParent()->setParameter (I_("UrlParams"), urlParamsIDI);
       CString cstrAcctTerm;
       cstrAcctTerm.LoadString(TXT_ACCT_TERMINATION);
       getParent()->setParameter (I_("BrowserTitle"), DString(cstrAcctTerm) + lAcctNum);
       getParent()->setParameter (I_("from_screen"), I_("COADlg"));
    }
    else if (procId == COADLG::CMD_BPROC_ZERO_GRANT_REPAYMENT)
    {
       DString urlParamsIDI;

       addIDITagValue (urlParamsIDI, I_("AccountNum"), lAcctNum);
       addIDITagValue (urlParamsIDI, I_("option"), I_("account"));
       addIDITagValue (urlParamsIDI, I_("screen"), I_("RESPZeroRpymt"));  //DesktopWeb conversion

       getParent()->setParameter (I_("UrlParams"), urlParamsIDI);
       CString cstrZeroGntPay;
       cstrZeroGntPay.LoadString(TXT_ZERO_GRANT_PAYMENT);
       getParent()->setParameter (I_("BrowserTitle"), DString(cstrZeroGntPay) + lAcctNum);
       getParent()->setParameter (I_("from_screen"), I_("COADlg"));
    }
    else if (procId == COADLG::CMD_BPROC_INTERFACE_FILE)
    {
       DString urlParamsIDI;

       addIDITagValue (urlParamsIDI, I_("AccountNum"), lAcctNum);
       addIDITagValue (urlParamsIDI, I_("option"), I_("account"));
       addIDITagValue (urlParamsIDI, I_("screen"), I_("RESPInterfaceFile"));

       getParent()->setParameter (I_("UrlParams"), urlParamsIDI);
       CString cstrIntfFile;
       cstrIntfFile.LoadString(TXT_INTERFACE_FILE);
       getParent()->setParameter (I_("BrowserTitle"), DString(cstrIntfFile) + lAcctNum);
       getParent()->setParameter (I_("from_screen"), I_("COADlg"));
    }
    else if (procId == COADLG::CMD_ACCT_SETTLEMENT_RULE )
    {
       getParent()->setParameter( I_("AccountNum"), lAcctNum );
    }
    else if (procId == COADLG::CMD_BPROC_LIF_GAIN_LOSS )
    {
       DString urlParamsIDI, dstrTaxType;

       addIDITagValue (urlParamsIDI, I_("AccountNum"), lAcctNum);
       addIDITagValue (urlParamsIDI, I_("option"), I_("account"));
       addIDITagValue (urlParamsIDI, I_("screen"), I_("LIFGainLoss")); //DesktopWeb conversion

       getParent()->setParameter (I_("UrlParams"), urlParamsIDI);
       getParent()->getField(this, ifds::TaxType, dstrTaxType, true );
       dstrTaxType.strip();
       CString cstrGnLoss;
       cstrGnLoss.LoadString(TXT_GAIN_LOSS);
       getParent()->setParameter (I_("BrowserTitle"), dstrTaxType+DString(cstrGnLoss) + lAcctNum);
       getParent()->setParameter (I_("from_screen"), I_("COADlg"));		 
    }
   else if (procId == COADLG::CMD_INVESTOR_AUTHORIZATION )
   {
      getParent()->setParameter( I_("AccountNum"), lAcctNum );
   }
   else if (procId == COADLG::CMD_ACCT_GUARNT_GUARD_OPTN )
   {
      getParent()->setParameter( I_("AccountNum"), lAcctNum );
   }
   else if (procId == COADLG::CMD_BPROC_GOVT_FILING_AMENDMENT)
   {
      DString urlParamsIDI,
         strTaxType;

      addIDITagValue (urlParamsIDI, I_("AccountNum"), lAcctNum);
      addIDITagValue (urlParamsIDI, I_("option"), I_("account"));
      addIDITagValue (urlParamsIDI, I_("screen"),I_("GovtAmendment") );

      getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::TaxType, strTaxType, false );
      strTaxType.strip().upperCase();

      getParent()->setParameter (I_("UrlParams"), urlParamsIDI);
      CString cstrGovFillAndAmend;
      cstrGovFillAndAmend.LoadString(TXT_GOV_FILING_AND_AMENDMENT);
      getParent()->setParameter (I_("BrowserTitle"), DString(cstrGovFillAndAmend) + lAcctNum);
      getParent()->setParameter (I_("from_screen"), I_("COADlg"));
   }
   else if( procId == COADLG::CMD_ACCT_OWNERSHIP_ALLOCATION )
   {
      DString urlParamsIDI,
         strTaxType;

      addIDITagValue (urlParamsIDI, I_("AccountNum"), lAcctNum);
      addIDITagValue (urlParamsIDI, I_("option"), I_("account"));
      addIDITagValue (urlParamsIDI, I_("screen"),I_("AcctTaxAlloc") );
      
      getParent()->setParameter (I_("UrlParams"), urlParamsIDI);
      getParent()->setParameter (I_("AccountNum"), lAcctNum);
      CString cstrActTaxAllocTitle, cstrAcctNumTxt;
      cstrAcctNumTxt.LoadString(TXT_ACCT_NUM_TXT);
      cstrActTaxAllocTitle.LoadString(TXT_ACCT_OWNERSHIP_ALLOC_TITLE);
      DString strBrowserTitle = DString(cstrActTaxAllocTitle) + I_(" ") + 
                                DString(cstrAcctNumTxt) + lAcctNum;
      getParent()->setParameter (I_("BrowserTitle"), strBrowserTitle );
      getParent()->setParameter (I_("from_screen"), I_("COADlg"));   
   }
   else if(procId == COADLG::CMD_VALUE_VARIATION)
   {
       getParent()->setParameter (I_("AccountNum"), lAcctNum);
   }
   else if( procId == COADLG::CMD_ACCT_FEE_MODEL_ASSOCIATION )
   {
      DString urlParamsIDI;

      addIDITagValue (urlParamsIDI, I_("AccountNum"), lAcctNum);
      addIDITagValue (urlParamsIDI, I_("option"), I_("account"));
      addIDITagValue (urlParamsIDI, I_("screen"),I_("AcctAssociate") );
      addIDITagValue (urlParamsIDI, I_("from_screen"), I_("COADlg"));

      getParent()->setParameter (I_("UrlParams"), urlParamsIDI);
      getParent()->setParameter (I_("AccountNum"), lAcctNum);
      CString cstrActFeeModelAssociateTitle, cstrAcctNumTxt;
      cstrAcctNumTxt.LoadString(TXT_ACCT_NUM_TXT);
      cstrActFeeModelAssociateTitle.LoadString(TXT_FEE_MODEL_ASSOCIATION_TITLE);
      DString strBrowserTitle = DString(cstrActFeeModelAssociateTitle) + I_(" ") + 
                                DString(cstrAcctNumTxt) + lAcctNum;
      getParent()->setParameter (I_("BrowserTitle"), strBrowserTitle );
      getParent()->setParameter (I_("from_screen"), I_("COADlg"));
   }
   else if( procId == COADLG::CMD_SHR_STATEMENT_SCHED )
   {
      DString urlParamsIDI;

      addIDITagValue (urlParamsIDI, I_("AccountNum"), lAcctNum);
      addIDITagValue (urlParamsIDI, I_("option"), I_("account"));
      addIDITagValue (urlParamsIDI, I_("screen"),I_("ShrStmtSched") );
      addIDITagValue (urlParamsIDI, I_("from_screen"), I_("COADlg"));

      getParent()->setParameter (I_("UrlParams"), urlParamsIDI);
      getParent()->setParameter (I_("AccountNum"), lAcctNum);
      CString cstrShrStatementSchedTitle, cstrAcctNumTxt;
      cstrAcctNumTxt.LoadString(TXT_ACCT_NUM_TXT);
      cstrShrStatementSchedTitle.LoadString(TXT_SCR_SHR_STATEMENT_SCHED_TITLE);
      DString strBrowserTitle = DString(cstrShrStatementSchedTitle) + I_(" ") + 
                                DString(cstrAcctNumTxt) + lAcctNum;
      getParent()->setParameter (I_("BrowserTitle"), strBrowserTitle );
      getParent()->setParameter (I_("from_screen"), I_("COADlg"));
   }
   else if (procId == COADLG::CMD_ACCT_REG_DETAILS)
   {
	   getParent()->setParameter (I_("AccountNum"), lAcctNum);
   }
   else if (procId == COADLG::CMD_ENT_REG_DETAILS)
   {
	   getParent()->setParameter (I_("AccountNum"), lAcctNum);
	   getParent()->setParameter (I_("EntityId"), I_("0"));
	   getParent()->setParameter (I_("Caller"), I_("COA"));
   }
   else if( procId == COADLG::CMD_TAX_SLIPS )
   {
       DString urlParamsIDI, dstrEntityName;
       E_COMMANDRETURN eRtn = CMD_OK;

       setParameter( I_( "AccountNum" ), lAcctNum);
       setParameter( I_( "from_screen" ), I_( "COA" ) );
       
       addIDITagValue (urlParamsIDI, I_("AccountNum"), lAcctNum);
       addIDITagValue (urlParamsIDI, I_("screen"),I_("TaxForms") );

       setParameter (I_("UrlParams"), urlParamsIDI);

       CString cstrTaxSlips;
       cstrTaxSlips.LoadString(ROW_DETAILS_TAX_SLIPS);
       
       dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName(getDataGroupId(), 
                                                                                                       lAcctNum, 
                                                                                                       dstrEntityName);

       setParameter (I_("BrowserTitle"), DString(cstrTaxSlips) + I_(": ") +
                                         GetCaptionShareNumTxt() + I_(" ") + lShareholderNum + I_("; ") + 
                                         GetCaptionAcctNumTxt() + I_(" ") + lAcctNum + I_("; ") + 
                                         dstrEntityName);
   }
   else if (procId == COADLG::CMD_ACCOUNT_GROUP)
   {
      DString urlParamsIDI;

      getParent()->setParameter( I_( "AccountNum" ), lAcctNum );
      getParent()->setParameter (I_("from_screen"), I_("COA"));

      addIDITagValue (urlParamsIDI, I_("AccountNum"), lAcctNum);
      addIDITagValue (urlParamsIDI, I_("screen"), I_("AccountGroup"));

      getParent()->setParameter (I_("UrlParams"), urlParamsIDI);

      DString dstrEntityName;

      CString cstrAccountGroup,
         cstrInfoShr,
         cstrAccountNumLabel,
         cstrAccountHolderName;
      cstrAccountNumLabel.LoadString(TXT_ACCOUNT_NUM);
      cstrAccountHolderName.LoadString(TXT_ACCT_HOLDER_NAME);
      cstrAccountGroup.LoadString(TXT_ACCOUNT_GROUP_TITLE);

      dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName(getDataGroupId(), lAcctNum,dstrEntityName);

      cstrAccountGroup += ":";
      DString strBrowserTitle(cstrAccountGroup);
      strBrowserTitle += cstrAccountNumLabel;
      strBrowserTitle += lAcctNum;
      strBrowserTitle += I_(" ");
      strBrowserTitle += cstrAccountHolderName;
      strBrowserTitle += dstrEntityName;

      getParent()->setParameter( I_("BrowserTitle"), strBrowserTitle);

   }
   else if (procId == COADLG::CMD_PRIVATE_WEALTH_INFO)
   {
      DString urlParamsIDI;

      getParent()->setParameter( I_( "AccountNum" ), lAcctNum );
      getParent()->setParameter (I_("from_screen"), I_("COA"));

      addIDITagValue (urlParamsIDI, I_("AccountNum"), lAcctNum);
      addIDITagValue (urlParamsIDI, I_("screen"), I_("PWInfo"));

      getParent()->setParameter (I_("UrlParams"), urlParamsIDI);

      DString dstrEntityName;

      CString cstrPWEnrollment,
         cstrInfoShr,
         cstrAccountNumLabel,
         cstrAccountHolderName;
      cstrAccountNumLabel.LoadString(TXT_ACCOUNT_NUM);
      cstrAccountHolderName.LoadString(TXT_ACCT_HOLDER_NAME);
      cstrPWEnrollment.LoadString(TXT_PRIVATE_WEALTH_INFO_TITLE);

      dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName(getDataGroupId(), lAcctNum,dstrEntityName);

      cstrPWEnrollment += ":";
      DString strBrowserTitle(cstrPWEnrollment);
      strBrowserTitle += cstrAccountNumLabel;
      strBrowserTitle += lAcctNum;
      strBrowserTitle += I_(" ");
      strBrowserTitle += cstrAccountHolderName;
      strBrowserTitle += dstrEntityName;

      getParent()->setParameter( I_("BrowserTitle"), strBrowserTitle);
   }
   else if (procId == COADLG::CMD_RESP_GRANTS)
   {
	   DString urlParamsIDI, entityId, last_name, first_name, dstrEntityName;

	   addIDITagValue (urlParamsIDI, I_("AccountNum"), lAcctNum);
	   addIDITagValue (urlParamsIDI, I_("screen"), I_("RESPGrantInfo"));

	   MFAccount *pMFAccount;
	   DSTCWorkSession *dstcWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());

	   if( dstcWorkSession->getMFAccount( getDataGroupId(), lAcctNum, pMFAccount ) <= WARNING && pMFAccount)
	   {
		   AccountEntityXref *pAccountEntityXref = NULL;
		   if (dstcWorkSession->getAccountEntityXref (getDataGroupId(), pAccountEntityXref) <= WARNING && pAccountEntityXref)
		   {
			   ENTITIES_VECTOR respBeneficiaryEntities;
			   pAccountEntityXref->getRESPBeneficiaryEntities (respBeneficiaryEntities, lAcctNum, getDataGroupId());

			   for (ENTITIES_VECTOR::size_type i = 0; i < respBeneficiaryEntities.size(); ++i)
			   {
				   entityId = respBeneficiaryEntities [i];
				   Entity *pEntity = NULL;
				   if  (dstcWorkSession->getEntity (getDataGroupId(), entityId, pEntity) <= WARNING && pEntity)
				   {
					   pEntity->getField( ifds::EntityId, entityId, getDataGroupId(), false );
					   if (!entityId.empty())
					   {
						   addIDITagValue (urlParamsIDI, I_("RESPBenefID"), entityId);
						   pEntity->getField( ifds::LastName, last_name, getDataGroupId(), false );
						   pEntity->getField( ifds::FirstName, first_name, getDataGroupId(), false );
						   dstrEntityName = last_name.strip() + I_( ";" ) + first_name.strip();
						   break;
					   }
				   }
			   }
		   }
	   }

	   CString cstrRESPGrantInfo;
	   cstrRESPGrantInfo.LoadString(TXT_GRNT_INFO_SCREEN);
	   DString screenTitle (DString(cstrRESPGrantInfo) + lAcctNum + I_(" ") + dstrEntityName);

	   getParent()->setParameter (I_("AccountNum"), lAcctNum);
	   getParent()->setParameter (I_("UrlParams"), urlParamsIDI);
	   getParent()->setParameter (I_("BrowserTitle"), screenTitle);
	   getParent()->setParameter (I_("from_screen"), I_("COADlg"));
   }
   else if (procId == COADLG::CMD_RESP_GRANTS2)
   {
	   DString urlParamsIDI;

	   addIDITagValue (urlParamsIDI, I_("AccountNum"), lAcctNum);
	   addIDITagValue (urlParamsIDI, I_("screen"), I_("RESPGrantInfo2"));
	   addIDITagValue (urlParamsIDI, I_("RESPBenefID"), I_(" "));

	   CString cstrRESPGrantInfo;
	   cstrRESPGrantInfo.LoadString(TXT_GRNT_INFO_SCREEN);
	   DString screenTitle (DString(cstrRESPGrantInfo) + lAcctNum);

	   getParent()->setParameter (I_("AccountNum"), lAcctNum);
	   getParent()->setParameter (I_("UrlParams"), urlParamsIDI);
	   getParent()->setParameter (I_("BrowserTitle"), screenTitle);
	   getParent()->setParameter (I_("from_screen"), I_("COADlg"));
   }
   else if (procId == COADLG::CMD_RESP_NOTIONAL_ACTIVITY)
   {
	   DString urlParamsIDI;

	   addIDITagValue (urlParamsIDI, I_("AccountNum"), lAcctNum);
	   addIDITagValue (urlParamsIDI, I_("screen"), I_("RESPNotionalActivity"));

	   CString cstrRESPNotlActivity;
	   cstrRESPNotlActivity.LoadString(TXT_RESP_NOTIONAL_ACTIVITY);
	   DString screenTitle (DString(cstrRESPNotlActivity) + lAcctNum);

	   getParent()->setParameter (I_("AccountNum"), lAcctNum);
	   getParent()->setParameter (I_("UrlParams"), urlParamsIDI);
	   getParent()->setParameter (I_("BrowserTitle"), screenTitle);
	   getParent()->setParameter (I_("from_screen"), I_("COADlg"));
   }
   else if (procId == COADLG::CMD_REG_PLAN_TRANSFER)
   {
	   DString urlParamsIDI;

	   addIDITagValue (urlParamsIDI, I_("AccountNum"), lAcctNum);

	   //CString cstrRESPNotlActivity;
	   //cstrRESPNotlActivity.LoadString(TXT_RESP_NOTIONAL_ACTIVITY);
	   getParent()->setParameter (I_("AccountNum"), lAcctNum);
   }
   else if (procId == COADLG::CMD_ACCT_ROUNDING_RULE)
   {	  
	   getParent()->setParameter( I_("AccountNum"), lAcctNum );
   }
   else if (procId == COADLG::CMD_ACCT_DELETION_REVIEW)
   {	  	  	   
	   DString urlParamsIDI;
	   CString cstrBrowserTitle;

	   cstrBrowserTitle.LoadString (TXT_ACCT_DELETION_REVIEW);	   
	   cstrBrowserTitle += I_(" ");

	   addIDITagValue (urlParamsIDI, I_("screen"), I_("AcctDelReview"));
	   addIDITagValue (urlParamsIDI, I_("AccountNum"), lAcctNum);		  		  

	   DString strBrowserTitle(cstrBrowserTitle);		  	  
	   strBrowserTitle += lAcctNum;

	   getParent()->setParameter (I_("UrlParams"), urlParamsIDI);
	   getParent()->setParameter (I_("AccountNum"), lAcctNum);		  
	   getParent()->setParameter (I_("BrowserTitle"), strBrowserTitle);
	   getParent()->setParameter (I_("from_screen"), I_("COADlg"));	   
   }
   else if (procId == COADLG::CMD_RDSP_ACCOUNT_INFO)
   {
	   DString urlParamsIDI;

	   setParameter( I_( "AccountNum" ), lAcctNum );
	   setParameter( I_( "from_screen" ), I_( "Account" ) );

	   addIDITagValue (urlParamsIDI, I_("AccountNum"), lAcctNum);
	   addIDITagValue (urlParamsIDI, I_("screen"), I_("RDSPAccountInfo"));

	   setParameter (I_("UrlParams"), urlParamsIDI);

	   CString cstrRDSP;
	   cstrRDSP.LoadString(TXT_RDSP_ACCT_INFO);
	   setParameter (I_("BrowserTitle"), DString(cstrRDSP) + lAcctNum);
	   setParameter (I_("from_screen"), I_("COADlg"));
   }
   else if (procId == COADLG::CMD_RDSP_NOTIONAL_ACTIVITY)
   {
	   DString urlParamsIDI;

	   setParameter( I_( "AccountNum" ), lAcctNum );
	   setParameter( I_( "TransNum" ), I_( " " ) );
	   setParameter( I_( "from_screen" ), I_( "Account" ) );

	   addIDITagValue (urlParamsIDI, I_("AccountNum"), lAcctNum);
	   addIDITagValue (urlParamsIDI, I_("TransNum"), I_(" "));
	   addIDITagValue (urlParamsIDI, I_("screen"), I_("RDSPNotionalActivity"));

	   setParameter (I_("UrlParams"), urlParamsIDI);

	   CString cstrRDSP;
	   cstrRDSP.LoadString(TXT_RDSP_NOTIONAL_ACTIVITY);
	   setParameter (I_("BrowserTitle"), DString(cstrRDSP) + lAcctNum);
	   setParameter (I_("from_screen"), I_("COADlg"));
   }
   else if (procId == COADLG::CMD_RDSP_NOTIONAL_BALANCE)
   {
	   DString urlParamsIDI;

	   setParameter( I_( "AccountNum" ), lAcctNum );
	   setParameter( I_( "from_screen" ), I_( "Account" ) );

	   addIDITagValue (urlParamsIDI, I_("AccountNum"), lAcctNum);
	   addIDITagValue (urlParamsIDI, I_("screen"), I_("RDSPNotionalBalance"));

	   setParameter (I_("UrlParams"), urlParamsIDI);

	   CString cstrRDSP;
	   cstrRDSP.LoadString(TXT_RDSP_NOTIONAL_BAL);
	   setParameter (I_("BrowserTitle"), DString(cstrRDSP) + lAcctNum);
	   setParameter (I_("from_screen"), I_("COADlg"));
   }
   else
   {
      assert(0);
   }

   eRtn = getParentProcess()->invokeProcessFromChild( this, LPCTSTR( procId.c_str()), PROC_SUPPORT );
   //eRtn = invokeCommand( getParent(), LPCTSTR( procId.c_str() ), PROC_NO_TYPE, true, NULL );

    if( eRtn != CMD_OK && eRtn != CMD_CANCEL && eRtn != CMD_MODELESS_INPROCESS )
    {  // Error processing
        ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
        return(false);
    }
    else if( eRtn == CMD_CANCEL )
        return(false);
    else
        return(true);
}

//******************************************************************************
void COADlg::reDisplayGrid()
{
    int ItemCount = m_ElementMap.itemCount();
    int rowHeight = 20;
    //m_gridWindow.SetRowCount( ItemCount );
    //m_gridWindow.SetRowHeight(0, ItemCount, 20);
    m_gridWindow.SetRowCount( 0 );
    m_gridWindow.SetRowHeight( 0, 0, 20 );
    COAElement * pCOAElem;
    COAElementMap::iterator iter = m_ElementMap.begin();
    bool lEnabled;
    for( int i = 0; i < ItemCount; i++ )
    {
        m_gridWindow.InsertRows( i + 1 , 1, &rowHeight );
        pCOAElem = m_ElementMap[i];
        lEnabled = pCOAElem->isEnabled();
        if( pCOAElem == NULL )
            break;
        WORD lControlType = pCOAElem->getControlType();
        m_gridWindow.SetStyleRange(CGXRange( i + 1,0), CGXStyle().SetVerticalAlignment(DT_VCENTER).SetValue( pCOAElem->getDisplayName()) );
        m_gridWindow.SetStyleRange(CGXRange( i + 1,1), CGXStyle().SetVerticalAlignment(DT_VCENTER).SetEnabled(FALSE).SetValue( pCOAElem->getDispType()));

        if( lControlType == GX_IDS_CTRL_STATIC || lControlType == GX_IDS_CTRL_EDIT )
         {   m_gridWindow.SetStyleRange(CGXRange( i + 1,2), CGXStyle().SetControl( lControlType )
                                    .SetValue( pCOAElem->getValue() ).SetEnabled( lEnabled )
                                    .SetReadOnly( !lEnabled ));
         }
         //P0186486_FN16_Misc. Enhancements_Stop Adjustment Date 
         else if(lControlType == GX_IDS_CTRL_DATETIME)
         {
            m_gridWindow.SetStyleRange(CGXRange( i + 1,2), CGXStyle().SetControl( lControlType )
                                    .SetValue( pCOAElem->getValue() ).SetEnabled( lEnabled )
                                    .SetReadOnly( !lEnabled ));
         }
        else
        {
            m_gridWindow.SetStyleRange( CGXRange( i + 1,2), CGXStyle().SetControl(GX_IDS_CTRL_CBS_DROPDOWNLIST)
                                     .SetChoiceList( pCOAElem->getChoiceList() ).SetValue( pCOAElem->getValue() ).SetEnabled( lEnabled ).SetReadOnly( !lEnabled )
                                     .SetVerticalAlignment(DT_VCENTER));
       }
    }

    // Update Settlement Location
    DString dstrClearingID;
    getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::ClearingID, dstrClearingID);
    updateSettlementLocation( dstrClearingID );
}

//******************************************************************************
void COADlg::retrieveValue( long cellId )
{
    DString fieldValue, dstrNSCCCompliant, dstrNetworkTypeUpd, dstrValidNetworkType;
    bool NSCCApply;

    COAElementMap::iterator iter = m_ElementMap.find( cellId );
    if( iter == m_ElementMap.end() )
        assert(0);

    COAElement & rCOAElem = *(*iter).second;
    bool canRead;

    DString dstrBrokerCode;

    DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
    MFAccount* pMFAccount = dynamic_cast<COAProcess*>(getParent() )->getMFAccount();

    DString stopReason;
    getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::StopReason, stopReason, false );

    bool bKYCStopFlag = stopReason == COADLG::KYC_SYSTEM || stopReason == COADLG::KYC_MANUAL ? false : true;
    bool bDeceasedStopFlag = stopReason == COADLG::DECEASED_SYSTEM || stopReason == COADLG::DECEASED_MANUAL ? false : true;
    
    if( !m_lInNASU && pMFAccount )
    {
         DString dstrEntityID;
         Entity *pEntity = NULL;
         //bool bAccountHolderRiskAppl;
         pMFAccount->GetEntityIdForAcctOwnerSeq1(getDataGroupId(), dstrEntityID);
         if( dstWorkSession->getEntity(getDataGroupId(), dstrEntityID,  pEntity) <= WARNING && 
             pEntity && 
             pEntity->isAccountHolderRiskApplicable(getDataGroupId()))
         {
           if( !pMFAccount->isRegDocumentsOutStanding(dstrEntityID, COMPLY_RULE::AcctRegistration, getDataGroupId()) &&  
               !pMFAccount->isRegDocumentsOutStanding(dstrEntityID, COMPLY_RULE::AccountholderRisk, getDataGroupId()) )
               {
                  bKYCStopFlag = true;
               }
           else
               {
                  bKYCStopFlag = false;
               }

         }
    }

    //Get Yes-No descriptions based on current screen language.
    DString strYes = DSTCommonFunctions::getDescription(I_("Y"), ifds::Yes_NO);
    DString strNo = DSTCommonFunctions::getDescription(I_("N"), ifds::Yes_NO);

    switch( cellId )
    {
        case COADlg::STP_PURCH_ID :
         getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::StopPurchase, fieldValue );
//         rCOAElem.setValue( fieldValue.c_str() );
            //rCOAElem.setEnabledAndValue( hasUpdatePermission(  UAF::ACCOUNT_DETAIL ) || 
            //                             hasCreatePermission(  UAF::ACCOUNT_DETAIL ), fieldValue.c_str() );
            rCOAElem.setEnabled((hasUpdatePermission(  UAF::ACCOUNT_DETAIL ) || 
                                 hasCreatePermission(  UAF::ACCOUNT_DETAIL ))
                                 && bDeceasedStopFlag); 

            rCOAElem.setValue( hasReadPermission(UAF::ACCOUNT_DETAIL )?fieldValue.c_str():I_("") );

            break;

        case COADlg::STP_REASON_ID :
         getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::StopReason, fieldValue, false );
            rCOAElem.setEnabled( hasUpdatePermission(  UAF::ACCOUNT_DETAIL ) || 
                                 hasCreatePermission(  UAF::ACCOUNT_DETAIL )); 

            if (fieldValue == COADLG::KYC_SYSTEM || fieldValue == COADLG::DECEASED_SYSTEM)
            {
               rCOAElem.setEnabled( hasUpdatePermission(  UAF::SYSTEM_STOP_REASON ) || 
                  hasCreatePermission(  UAF::SYSTEM_STOP_REASON )); 

            }

            getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::StopReason, fieldValue );
            rCOAElem.setValue( hasReadPermission(UAF::ACCOUNT_DETAIL )? fieldValue.c_str():I_("") );

            break;

       case COADlg::STP_ADDITIONAL_REASON_ID :
          getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::AdditionalStopReason, fieldValue );
          rCOAElem.setEnabled( hasUpdatePermission(  UAF::ACCOUNT_DETAIL ) || 
                               hasCreatePermission(  UAF::ACCOUNT_DETAIL )); 

          rCOAElem.setValue( hasReadPermission(UAF::ACCOUNT_DETAIL )?fieldValue.c_str():I_("") );

            break;

       case COADlg::STP_STOP_NFU:
            getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::StopNFU, fieldValue );
            rCOAElem.setValue (fieldValue.c_str());
            rCOAElem.setEnabled (false); 
            break;

        case COADlg::STP_REDEM_ID : 
         if(hasUpdatePermission(UAF::REL_STOP_RED))
         {
            // if user has permission to release stop redemption flag
            // Enable the field but still keep some existing logic.
            rCOAElem.setEnabled(bDeceasedStopFlag);
         }
         else
         {
            rCOAElem.setEnabled((hasUpdatePermission(  UAF::ACCOUNT_DETAIL ) ||
                                  hasCreatePermission(  UAF::ACCOUNT_DETAIL )) &&
                                 bDeceasedStopFlag); 
         }
         getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::StopRed, fieldValue );
         rCOAElem.setValue( hasReadPermission(UAF::ACCOUNT_DETAIL )?fieldValue.c_str():I_("") );
         break;
        case COADlg::STP_REDEM_SETTLE_ID:

            getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::StopRedSettle, fieldValue );
            rCOAElem.setEnabled((hasUpdatePermission(  UAF::ACCOUNT_DETAIL )
                                || hasCreatePermission(  UAF::ACCOUNT_DETAIL ))
                                && bKYCStopFlag && bDeceasedStopFlag); 
            rCOAElem.setValue( hasReadPermission(UAF::ACCOUNT_DETAIL )?fieldValue.c_str():I_("") );
            break;

        case COADlg::STP_XFERO_ID : 
         getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::StopXferOut, fieldValue );
//         rCOAElem.setValue( fieldValue.c_str() );
//         rCOAElem.setEnabledAndValue( hasUpdatePermission(  UAF::ACCOUNT_DETAIL )
//                                   || hasCreatePermission(  UAF::ACCOUNT_DETAIL ), fieldValue.c_str() );
         rCOAElem.setEnabled((hasUpdatePermission(  UAF::ACCOUNT_DETAIL )
                           || hasCreatePermission(  UAF::ACCOUNT_DETAIL )) 
                           && bKYCStopFlag && bDeceasedStopFlag); 
         rCOAElem.setValue( hasReadPermission(UAF::ACCOUNT_DETAIL )?fieldValue.c_str():I_("") );

            break;
        case COADlg::STP_XFERI_ID :
         getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::StopXferIn, fieldValue );
//         rCOAElem.setValue( fieldValue.c_str() );
//         rCOAElem.setEnabledAndValue( hasUpdatePermission(  UAF::ACCOUNT_DETAIL )
//                                   || hasCreatePermission(  UAF::ACCOUNT_DETAIL ), fieldValue.c_str() );
         rCOAElem.setEnabled( (hasUpdatePermission(  UAF::ACCOUNT_DETAIL )
                           || hasCreatePermission(  UAF::ACCOUNT_DETAIL )) && bDeceasedStopFlag ); 
         rCOAElem.setValue( hasReadPermission(UAF::ACCOUNT_DETAIL )?fieldValue.c_str():I_("") );

            break;
        case COADlg::STP_FRREB_ID :
         getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::StopFCrebal, fieldValue );
//         rCOAElem.setValue( fieldValue.c_str() );
//         rCOAElem.setEnabledAndValue( hasUpdatePermission(  UAF::ACCOUNT_DETAIL )
//                                   || hasCreatePermission(  UAF::ACCOUNT_DETAIL ), fieldValue.c_str() );
         rCOAElem.setEnabled( hasUpdatePermission(  UAF::ACCOUNT_DETAIL )
                           || hasCreatePermission(  UAF::ACCOUNT_DETAIL )); 
         rCOAElem.setValue( hasReadPermission(UAF::ACCOUNT_DETAIL )?fieldValue.c_str():I_("") );

            break;
        case COADlg::HLD_DIV_PAYMENT :
         getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::HoldDivPymt, fieldValue );
         rCOAElem.setEnabled( hasUpdatePermission(  UAF::ACCOUNT_DETAIL )
                           || hasCreatePermission(  UAF::ACCOUNT_DETAIL )); 

         rCOAElem.setValue( hasReadPermission(UAF::ACCOUNT_DETAIL )?fieldValue.c_str():I_("") );

            break;
        case COADlg::SCR_REMARK_ID :
         getParent()->getField( this, IFASTBP_PROC::COA_SHAREHOLDER_CBO, ifds::Remarks, fieldValue );
         rCOAElem.setEnabledAndValue( hasReadPermission(  UAF::REMARKS ), fieldValue.c_str() );
            break;
        case COADlg::SCR_BANK_ID :
         getParent()->getField( this, IFASTBP_PROC::COA_SHAREHOLDER_CBO, ifds::BankingInstr, fieldValue );
         canRead = hasReadPermission(  UAF::BANKING_INSTRUCTION );
         rCOAElem.setEnabledAndValue( canRead, fieldValue.c_str() );
            break;
        case COADlg::SCR_SYSTR_ID :
         getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::SystemTrsfr, fieldValue );
         canRead = hasReadPermission(  UAF::AUTOMATIC_TRANSFER );  
         rCOAElem.setEnabledAndValue( canRead, fieldValue.c_str() );
         break;
        case COADlg::SCR_PAC_ID :
         getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::PAC, fieldValue );
         canRead = hasReadPermission(  UAF::PAC );
         rCOAElem.setEnabledAndValue( canRead, fieldValue.c_str() );
         break;
        case COADlg::SCR_SWP_ID :
         getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::SWP, fieldValue );
         canRead = hasReadPermission(  UAF::SWP );
         rCOAElem.setEnabledAndValue( canRead, fieldValue.c_str() );
         break;
        case COADlg::SCR_SAVING_PLAN_ID :
         getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::SavePlanExist, fieldValue );
         canRead = hasReadPermission(  UAF::SAVING_PLAN );
         rCOAElem.setEnabledAndValue( canRead, fieldValue.c_str() );
         break;
        case COADlg::SCR_ALLOC_ID :
         getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::AcctAlloc, fieldValue );
         canRead = hasReadPermission(  UAF::DEFAULT_ALLOCATION ); 
         rCOAElem.setEnabledAndValue( canRead, fieldValue.c_str() );
         break;
        case COADlg::SCR_RRIF_ID :
         getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::RIFExist, fieldValue );
         canRead = ( (!m_lInNASU) && hasReadPermission(  UAF::RIF_LIF_LRIF_INFO ) );
         rCOAElem.setEnabledAndValue( canRead, fieldValue.c_str() );
         break;
        case COADlg::SCR_ACB_ID :
        {
            if( m_lInNASU )
            {
                rCOAElem.setEnabledAndValue( false, NULL_STRING );
            }
            else
            {
                getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::ACBExist, fieldValue );
                canRead = hasReadPermission(  UAF::ACB );
                rCOAElem.setEnabledAndValue( canRead, fieldValue.c_str() );
            }
        }
        break;
        case COADlg::SCR_ADDR_ID :
         canRead = hasReadPermission(  UAF::ADDRESS_BOOK );
         rCOAElem.setEnabledAndValue( canRead, strYes.c_str() );
         break;
        case COADlg::SCR_ENTITY_ID :
         canRead = hasReadPermission(  UAF::ENTITY_MAINTANENCE );
         rCOAElem.setEnabledAndValue( canRead, strYes.c_str() );
         break;
        case COADlg::SCR_INTACR_ID :
         if( m_lInNASU )
            rCOAElem.setEnabledAndValue( false, NULL_STRING );
         else
         {
            getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::InterestAccrExist, fieldValue );
            canRead = hasReadPermission(  UAF::INTEREST_ACCRUAL );
            rCOAElem.setEnabledAndValue( canRead, fieldValue.c_str() );
         }
         break;
        case COADlg::SCR_ACCIDENT_ID :
		{
			getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::AcctIdentifierExist, fieldValue );
			DString strYes = I_("Yes");
			if (fieldValue.stricmp(strYes) == 0)
			{
				rCOAElem.setValue( strYes.c_str() );
			}
			else
			{
				rCOAElem.setValue( strNo.c_str() );
			}
		 }
         break;
        case COADlg::SCR_ACCINF_ID :
         rCOAElem.setValue( strYes.c_str() );
         break;
        case COADlg::SCR_DISTR_ID :
         if( m_lInNASU )
            rCOAElem.setValue( strNo.c_str() );
         else
         {
            getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::DistributionExist, fieldValue );
            canRead = hasReadPermission(  UAF::DISTRIBUTION );
            rCOAElem.setEnabledAndValue( canRead, fieldValue.c_str() );
         }
         break;
        case COADlg::SCR_DEMOGR_ID :
         canRead = hasReadPermission(  UAF::DEMOGRAPHICS ); 
         rCOAElem.setEnabledAndValue( canRead, strYes.c_str() );
         break;
        case COADlg::SCR_CERTIF_ID :
         getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::Certificates, fieldValue );
         rCOAElem.setEnabledAndValue( !m_lInNASU, fieldValue.c_str() );
         break;
/*   case COADlg::SCR_CONTRACT_ID :
      getParent()->getField( this, COAPROC::COA_MFACCOUNT_CBO, ifds::ContractExist, fieldValue );
    canRead = hasPermission(  UAF::SEG_FUND_CONTRACT,  ifds::InqPerm ); 
      rCOAElem.setEnabledAndValue( canRead, fieldValue.c_str() );
      break;
      */
        case COADlg::SCR_CONTRACT_ID :
         getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::ContractExist, fieldValue );
         canRead =  hasReadPermission(  UAF::SEG_FUND_MULTI_CONTRACT );
         if( !canRead )
            canRead = hasReadPermission(  UAF::SEG_FUND_CONTRACT );
         rCOAElem.setEnabledAndValue( canRead, fieldValue.c_str() );
         break;
        case COADlg::SCR_CHEQUE_ID :
         if( m_lInNASU )
            rCOAElem.setEnabledAndValue( false, NULL_STRING );
         else
         {
            getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::ChequeExist, fieldValue );
            canRead = hasReadPermission(  UAF::CHEQUE ); 
            rCOAElem.setEnabledAndValue( canRead, fieldValue.c_str() );
         }
         break;
        case COADlg::SCR_SHR_ID :
         rCOAElem.setValue( strYes.c_str() );
         break;
        case COADlg::SCR_BENEF_ID :
         getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::ExistBeneficiary, fieldValue ); 
         canRead = hasReadPermission(  UAF::ENTITY_MAINTANENCE );
         rCOAElem.setEnabledAndValue( canRead, fieldValue.c_str() );
         break;
        case COADlg::SCR_AS_PENSION_PLAN_ID :
         canRead = hasReadPermission(  UAF::AS_PENSION_PLAN );
         rCOAElem.setEnabledAndValue( canRead, strYes.c_str() );
         break;
        case COADlg::SCR_ESOP_ID :
         canRead = hasReadPermission(  UAF::ESOP );
         rCOAElem.setEnabledAndValue( canRead, strYes.c_str() );
         break;

/*
        case COADlg::SCR_ESCROW_ID :
         getParent()->getField( this, COAPROC::COA_MFACCOUNT_CBO , ifds::Escrow, fieldValue );
//       rCOAElem.setValue( fieldValue.c_str() );
         rCOAElem.setEnabledAndValue( !m_lInNASU, fieldValue.c_str() );
//       rCOAElem.setValue( fieldValue ==  I_("Y") ? strYes.c_str() : fieldValue ==  I_("N") ? strNo.c_str() : fieldValue.c_str() );
         break;
*/
// case COADlg::FEE_ADMFEE_ID :
//    rCOAElem.setValue( NULL_STRING );
//    break;
// case COADlg::FEE_WTHDTX_ID :
//    rCOAElem.setValue( NULL_STRING );
//    break;
        case COADlg::FEE_FEEWVD_ID :
        {
            getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::FeeWaived, fieldValue );       
            bool blChargeWDFeePermission = hasUpdatePermission( UAF::ACCOUNT_DETAIL );				
            rCOAElem.setValue( fieldValue.c_str() );
            rCOAElem.setEnabled( blChargeWDFeePermission );  			
            break;
        }

        case COADlg::SCR_ACCT_FEE_ID:
         getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::AcctFeesExist, fieldValue );
         canRead = hasReadPermission(  UAF::FEE_PARAMETER ); 
         rCOAElem.setEnabledAndValue( canRead, fieldValue.c_str() );
         break;

      case COADlg::SCR_ACCT_TRAILER_FEE:
         fieldValue = I_("");
         //getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::AcctFeesExist, fieldValue );
         canRead = hasReadPermission(  UAF::ACCTLVL_TRAILERFEE_SETUP ); 
         rCOAElem.setEnabledAndValue( canRead, fieldValue.c_str() );
         break;

        case COADlg::SPR_EMPCNF_ID :
         getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::SupEmpConf, fieldValue );
            //rCOAElem.setValue( fieldValue.c_str() );
            //rCOAElem.setEnabledAndValue( hasUpdatePermission(  UAF::ACCOUNT_DETAIL )
            //           || hasCreatePermission(  UAF::ACCOUNT_DETAIL ), fieldValue.c_str() );
         rCOAElem.setEnabled( hasUpdatePermission(  UAF::ACCOUNT_DETAIL )
                           || hasCreatePermission(  UAF::ACCOUNT_DETAIL )); 
         rCOAElem.setValue( hasReadPermission(UAF::ACCOUNT_DETAIL )?fieldValue.c_str():I_("") );

         break;
        case COADlg::SPR_CONFIRM_ID :
         getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::SupConf, fieldValue );
//      rCOAElem.setValue( fieldValue ==  I_("Y") ? strYes.c_str() : fieldValue ==  I_("N") ? strNo.c_str() : fieldValue.c_str() );
//         rCOAElem.setValue( fieldValue.c_str() );
//		   rCOAElem.setEnabledAndValue( hasUpdatePermission(  UAF::ACCOUNT_DETAIL )
//				                       || hasCreatePermission(  UAF::ACCOUNT_DETAIL ), fieldValue.c_str() );
         rCOAElem.setEnabled( hasUpdatePermission(  UAF::ACCOUNT_DETAIL )
				             || hasCreatePermission(  UAF::ACCOUNT_DETAIL )); 
		 rCOAElem.setValue( hasReadPermission(UAF::ACCOUNT_DETAIL )?fieldValue.c_str():I_("") );

         break;
        case COADlg::MSC_EMPL_ID :
         getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::Employee, fieldValue );
//         rCOAElem.setValue( fieldValue.c_str() );
//			rCOAElem.setEnabledAndValue( hasUpdatePermission(  UAF::ACCOUNT_DETAIL )
//				                       || hasCreatePermission(  UAF::ACCOUNT_DETAIL ), fieldValue.c_str() );
         rCOAElem.setEnabled( hasUpdatePermission(  UAF::ACCOUNT_DETAIL )
				             || hasCreatePermission(  UAF::ACCOUNT_DETAIL )); 
		 rCOAElem.setValue( hasReadPermission(UAF::ACCOUNT_DETAIL )?fieldValue.c_str():I_("") );

         break;
/*   case COADlg::MSC_INTRFOR_ID :
      getParent()->getField( this, COAPROC::COA_MFACCOUNT_CBO , ifds::InTrustFor, fieldValue );
      rCOAElem.setValue( fieldValue.c_str() );
//    rCOAElem.setValue( fieldValue ==  I_("Y") ? strYes.c_str() : fieldValue ==  I_("N") ? strNo.c_str() : fieldValue.c_str() );
      break;*/
//   case COADlg::MSC_STATUS_ID :
//      getParent()->getField( this, COAPROC::COA_MFACCOUNT_CBO , ifds::AcctStatus, fieldValue );
//      rCOAElem.setValue( fieldValue.c_str() );
         break;
        case COADlg::MSC_UNSZBL_ID :
         getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO , ifds::Unseizable, fieldValue );
//         rCOAElem.setValue( fieldValue.c_str() );
//			rCOAElem.setEnabledAndValue( hasUpdatePermission(  UAF::ACCOUNT_DETAIL )
//				                       || hasCreatePermission(  UAF::ACCOUNT_DETAIL ), fieldValue.c_str() );
//      rCOAElem.setValue( fieldValue ==  I_("Y") ? strYes.c_str() : fieldValue ==  I_("N") ? strNo.c_str() : fieldValue.c_str() );
         rCOAElem.setEnabled( hasUpdatePermission(  UAF::ACCOUNT_DETAIL )
				             || hasCreatePermission(  UAF::ACCOUNT_DETAIL )); 
		 rCOAElem.setValue( hasReadPermission(UAF::ACCOUNT_DETAIL )?fieldValue.c_str():I_("") );

         break;
/*   case COADlg::MSC_RESP_ID :
      getParent()->getField( this, COAPROC::COA_MFACCOUNT_CBO , ifds::CESGEligible, fieldValue );
      rCOAElem.setValue( fieldValue.c_str() );
//      rCOAElem.setValue( fieldValue ==  I_("Y") ? strYes.c_str() : fieldValue ==  I_("N") ? strNo.c_str() : fieldValue.c_str() );
      break; */

         // next case is commented because CBO dose account number validation and account number is invalide
         // at this moment.
         // case COADlg::SCR_GUARANTEE_ID :
         //   rCOAElem.setValue( strYes.c_str() );
         //   break;
        case COADlg::MSC_TELFAX_AGREEMENT_ID:
         getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO , ifds::TelFaxAgreement, fieldValue );
//         rCOAElem.setValue( fieldValue.c_str() );
		 rCOAElem.setEnabled( hasUpdatePermission(  UAF::ACCOUNT_DETAIL )
				             || hasCreatePermission(  UAF::ACCOUNT_DETAIL )); 
		 rCOAElem.setValue( hasReadPermission(UAF::ACCOUNT_DETAIL )?fieldValue.c_str():I_("") );

		 break;
        case COADlg::SCR_YTD_ID :
         if( m_lInNASU )
            rCOAElem.setEnabledAndValue( false, NULL_STRING );
         else
         {
            getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::TaxType, fieldValue, false );
            rCOAElem.setValue ( fieldValue == I_("1")? strYes.c_str() : strNo.c_str() );
         }
         break;
        case COADlg::GST_EXEMPT_ID :
         getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::GSTExempt, fieldValue );
//         rCOAElem.setValue( fieldValue.c_str() );
//			rCOAElem.setEnabledAndValue( hasUpdatePermission(  UAF::ACCOUNT_DETAIL )
//				                       || hasCreatePermission(  UAF::ACCOUNT_DETAIL ), fieldValue.c_str() );
         rCOAElem.setEnabled( hasUpdatePermission(  UAF::ACCOUNT_DETAIL )
				             || hasCreatePermission(  UAF::ACCOUNT_DETAIL )); 
		 rCOAElem.setValue( hasReadPermission(UAF::ACCOUNT_DETAIL )?fieldValue.c_str():I_("") );

         break;
        case COADlg::PST_EXEMPT_ID :
         getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::ApplyPST, fieldValue );
//         rCOAElem.setValue( fieldValue.c_str() );
//			rCOAElem.setEnabledAndValue( hasUpdatePermission(  UAF::ACCOUNT_DETAIL )
//				                       || hasCreatePermission(  UAF::ACCOUNT_DETAIL ), fieldValue.c_str() );
         rCOAElem.setEnabled( hasUpdatePermission(  UAF::ACCOUNT_DETAIL )
				             || hasCreatePermission(  UAF::ACCOUNT_DETAIL )); 
		 rCOAElem.setValue( hasReadPermission(UAF::ACCOUNT_DETAIL )?fieldValue.c_str():I_("") );

         break;

        case COADlg::SCR_PENSION_INFO:
         getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::PensionJurisExists, fieldValue );      
         rCOAElem.setValue( fieldValue.c_str() );
         break;
        case COADlg::SCR_ACCOUNTREVIEW_ID :
         rCOAElem.setEnabledAndValue( hasReadPermission(  UAF::ACCOUNTREVIEW ), strYes.c_str() );
         break;
        case COADlg::FEE_BANK_CHARGE_ID :
         getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::BankChrgs, fieldValue );
//         rCOAElem.setValue( fieldValue.c_str() );
//			rCOAElem.setEnabledAndValue( hasUpdatePermission(  UAF::ACCOUNT_DETAIL )
//				                       || hasCreatePermission(  UAF::ACCOUNT_DETAIL ), fieldValue.c_str() );
         rCOAElem.setEnabled( hasUpdatePermission(  UAF::ACCOUNT_DETAIL )
				             || hasCreatePermission(  UAF::ACCOUNT_DETAIL )); 
		 rCOAElem.setValue( hasReadPermission(UAF::ACCOUNT_DETAIL )?fieldValue.c_str():I_("") );

         break;
        case COADlg::MSC_CONSOLID_EFT_ID :
         getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::ConsolidEFT, fieldValue );
//          rCOAElem.setValue( fieldValue.c_str() );
//          rCOAElem.setEnabledAndValue( hasUpdatePermission(  UAF::ACCOUNT_DETAIL )
//                                     || hasCreatePermission(  UAF::ACCOUNT_DETAIL ), fieldValue.c_str() );
            rCOAElem.setEnabled( hasUpdatePermission(  UAF::ACCOUNT_DETAIL )
                             || hasCreatePermission(  UAF::ACCOUNT_DETAIL )); 
            rCOAElem.setValue( hasReadPermission(UAF::ACCOUNT_DETAIL )?fieldValue.c_str():I_("") );

         break;
          //P0186486_FN16_Misc. Enhancements_Stop Adjustment Date
        case COADlg::MSC_STOP_ADJDATE:
           {
              getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::StopAdjDate, fieldValue );
              
              rCOAElem.setEnabled( hasUpdatePermission(  UAF::ACCOUNT_DETAIL )
                                   || hasCreatePermission(  UAF::ACCOUNT_DETAIL )); 
              rCOAElem.setValue( hasReadPermission(UAF::ACCOUNT_DETAIL )?fieldValue.c_str():I_("") );
           }
        break;
        
        case COADlg::SCR_ACCT_SPLIT_COMM :
         getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::AcctCommExists, fieldValue );      
         rCOAElem.setValue( fieldValue.c_str() );
         break;
        case COADlg::SCR_AMS_ID :
        {
            DString dstrAcctAMSExist;
            getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::AcctAMSExist, fieldValue );
                rCOAElem.setEnabledAndValue( hasUpdatePermission(  UAF::ACCOUNT_DETAIL )
                                            || hasCreatePermission(  UAF::ACCOUNT_DETAIL ), fieldValue.c_str() );
        }
         break;
        case COADlg::SCR_HYPORED_ID :
            retrieveHypoRedValue(rCOAElem);
         break;
        case COADlg::SCR_FOREIGN_CONTENT_WORKSHEET_ID:			
			
		    rCOAElem.setEnabled( hasReadPermission(  UAF::FOREIGN_CONTENT ) );
		    rCOAElem.setValue( strYes.c_str() );				
			break;
        case COADlg::FEE_MGMT_FEE_PAY_OPTN:
            
            getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::MgmtFeePayOption, fieldValue );
//            rCOAElem.setValue(fieldValue.c_str() );
//				rCOAElem.setEnabledAndValue( hasUpdatePermission(  UAF::ACCOUNT_DETAIL )
//				                          || hasCreatePermission(  UAF::ACCOUNT_DETAIL ), fieldValue.c_str() );
         rCOAElem.setEnabled( hasUpdatePermission(  UAF::ACCOUNT_DETAIL )
				             || hasCreatePermission(  UAF::ACCOUNT_DETAIL )); 
		 rCOAElem.setValue( hasReadPermission(UAF::ACCOUNT_DETAIL )?fieldValue.c_str():I_("") );

			break;
        case COADlg::SCR_SHR_FAMILY_ID:
            
            getParent()->getField( this, IFASTBP_PROC::COA_SHAREHOLDER_CBO, ifds::FamilyCodeExist, fieldValue);
            rCOAElem.setEnabledAndValue( hasReadPermission(  UAF::SHR_FAMILY ), fieldValue.c_str() );

         break;
        case COADlg::SCR_ACCT_CATEGORY_ID:
            
            getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::AcctCategoryExist, fieldValue );
            rCOAElem.setEnabledAndValue(hasReadPermission(UAF::ACCT_CATEGORY) || hasReadPermission(UAF::ACCT_CATEGORY_PRIVATE_WEALTH_OPT_OUT), fieldValue.c_str() );
         break;

		case COADlg::SCR_DOC_LIST_ID:
            getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::DocListExists, fieldValue );
            rCOAElem.setEnabledAndValue(hasReadPermission(  UAF::DOC_LIST ), fieldValue.c_str() );
			break;

        case COADlg::SCR_RESP_ID:
         {
            getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, COAPROC::RespExists, fieldValue );
            rCOAElem.setEnabledAndValue( hasReadPermission(  UAF::RESP_INFO ), fieldValue.c_str() );
         }
         break;
        case COADlg::FEE_EARLY_REDEMPTION_FEE_OPT:
            
         getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::ChargeERFee, fieldValue );
//         rCOAElem.setValue( fieldValue.c_str() );
//			rCOAElem.setEnabledAndValue( hasUpdatePermission(  UAF::ACCOUNT_DETAIL )
//			                          || hasCreatePermission(  UAF::ACCOUNT_DETAIL ), fieldValue.c_str() );
         rCOAElem.setEnabled( hasUpdatePermission(  UAF::ACCOUNT_DETAIL )
				             || hasCreatePermission(  UAF::ACCOUNT_DETAIL )); 
		 rCOAElem.setValue( hasReadPermission(UAF::ACCOUNT_DETAIL )?fieldValue.c_str():I_("") );

         break;
        case COADlg::FEE_SHORT_TERM_TRFER_FEE:
            
         getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::ChargeSTTRFee, fieldValue );
//         rCOAElem.setValue( fieldValue.c_str() );
//			rCOAElem.setEnabledAndValue( hasUpdatePermission(  UAF::ACCOUNT_DETAIL )
//				                       || hasCreatePermission(  UAF::ACCOUNT_DETAIL ), fieldValue.c_str() );
         rCOAElem.setEnabled( hasUpdatePermission(  UAF::ACCOUNT_DETAIL )
				             || hasCreatePermission(  UAF::ACCOUNT_DETAIL )); 
		 rCOAElem.setValue( hasReadPermission(UAF::ACCOUNT_DETAIL )?fieldValue.c_str():I_("") );

         break;

        case COADlg::FEE_NEXT_MFR_PROCESS_DATE:
            
         getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::NextMFRProcessDate, fieldValue );
		
         rCOAElem.setEnabled (false); 
		 rCOAElem.setValue(fieldValue.c_str());
         break;

     // case COADlg::STP_AMSREBALANCING_ID :
     //    getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::StopAMSRebalancing, fieldValue );
     //    rCOAElem.setEnabled( hasUpdatePermission(  UAF::ACCOUNT_DETAIL ) || hasCreatePermission(  UAF::ACCOUNT_DETAIL )); 
     //    rCOAElem.setEnabled (false);  //disabled as of release 80 for AIM - incident 1003183
		   //rCOAElem.setValue (hasReadPermission(UAF::ACCOUNT_DETAIL ) ? fieldValue.c_str() : I_(""));

     //    break;
        case COADlg::SCR_DIRECT_TRADING :
         //canRead = hasReadPermission(  UAF::ACCTDTA );
         canRead = true;
         rCOAElem.setEnabledAndValue( canRead, strYes.c_str() );
         break;
        case COADlg::SCR_ACCT_SETTLE_LOC:
         {
            getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::SettleLocExist, fieldValue );
            rCOAElem.setEnabledAndValue( ( hasUpdatePermission( UAF::SETTLE_LOCATION_ACCT_LVL ) || hasCreatePermission( UAF::SETTLE_LOCATION_ACCT_LVL ) ),
                                         fieldValue.c_str() );
         }
         break;
        case COADlg::SCR_SHR_FUND_SPONSOR_AGREEMENT:
         {            
				getParent()->getField( this, IFASTBP_PROC::COA_SHAREHOLDER_CBO, ifds::ShrFndSpAgrExists, fieldValue );				
				rCOAElem.setEnabled( hasUpdatePermission(  UAF::SHR_FUND_SPONSOR_AGREEMENT ) ||
				                     hasCreatePermission(  UAF::SHR_FUND_SPONSOR_AGREEMENT ) ); 
				rCOAElem.setValue( fieldValue.c_str() );
         }
         break;
        case COADlg::SCR_SHR_FUND_BROKER:
         {            
				getParent()->getField( this, IFASTBP_PROC::COA_SHAREHOLDER_CBO, ifds::ShrFndBrkExist, fieldValue );				
				rCOAElem.setEnabled( hasUpdatePermission(  UAF::SHR_FUND_BROKER ) ||
				                     hasCreatePermission(  UAF::SHR_FUND_BROKER ) ); 
				rCOAElem.setValue( fieldValue.c_str() );
         }
         break;
        case COADlg::SCR_TAX_EXEMPT_AUTHORIZATION_ID:
         {
            DString dstrRegisteredTaxTypes, dstrTaxType, dstrEUSDParticip;
            dstWorkSession->getOption( ifds::RegisteredTaxTypes, dstrRegisteredTaxTypes, getParent()->getDataGroupId(), false);
            getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::TaxType, dstrTaxType, false);
            dstWorkSession->getOption(ifds::EUSDParticip, dstrEUSDParticip, getParent()->getDataGroupId(), false);
			 	if ( (DSTCommonFunctions::codeInList(dstrTaxType, dstrRegisteredTaxTypes) || dstrEUSDParticip == I_("Y") ))
				{
					fieldValue = I_("N");
					canRead = hasReadPermission(UAF::TAX_EXEMPT_AUTHORIZATION ) ;  
					rCOAElem.setEnabledAndValue( canRead, fieldValue.c_str()? strYes.c_str() : strNo.c_str() );
				}
			}
         break;
        case COADlg::SCR_ACCT_FEE_MODEL:
         {            
				DString dstrModelCode;
			   getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::FeeModelCode, dstrModelCode, false );		   
            rCOAElem.setEnabled( hasUpdatePermission(  UAF::ACCOUNT_FEE_MODEL ) 
											|| hasCreatePermission(  UAF::ACCOUNT_FEE_MODEL )  ); 
				dstrModelCode.strip();
				fieldValue= dstrModelCode==NULL_STRING?  strNo:strYes; 
			   rCOAElem.setValue( fieldValue.c_str() );
         }
         break;
        case COADlg::MSC_CLEARING_ID:
            getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::ClearingID, fieldValue);
//            rCOAElem.setEnabledAndValue( true, fieldValue.c_str() );
            rCOAElem.setEnabled( hasUpdatePermission(  UAF::ACCOUNT_DETAIL )
				             || hasCreatePermission(  UAF::ACCOUNT_DETAIL )); 
		      rCOAElem.setValue( hasReadPermission(UAF::ACCOUNT_DETAIL )?fieldValue.c_str():I_("") );

         break;

        case COADlg::MSC_MARKET_MAIL:
            getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::MarketMail, fieldValue);
            rCOAElem.setEnabled( hasUpdatePermission(  UAF::ACCOUNT_DETAIL )
                                || hasCreatePermission(  UAF::ACCOUNT_DETAIL )); 
            rCOAElem.setValue( hasReadPermission(UAF::ACCOUNT_DETAIL )?fieldValue.c_str():I_("") );

            break;

        case COADlg::MSC_AFFLUENT:
            // check ACCOUNT_DETAIL for read permission and AFFLUENT for update permission (Winnie Jan 3rd, 2008)
            getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::Affluent, fieldValue);
            rCOAElem.setEnabled( hasUpdatePermission (UAF::AFFLUENT) || hasCreatePermission (UAF::AFFLUENT)); 
            rCOAElem.setValue (hasReadPermission (UAF::ACCOUNT_DETAIL)? fieldValue.c_str() : I_(""));
            break;

        case COADlg::MSC_NETWORKCONTROLIND:
            pMFAccount->getField ( ifds::BrokerCode, dstrBrokerCode, getParent()->getDataGroupId() );
            getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::Networkcontrolind, fieldValue);
            dstWorkSession->getOption( ifds::NSCCCompliant, dstrNSCCCompliant, getParent()->getDataGroupId(), false );
            NSCCApply = dstrNSCCCompliant == COADLG::STRING_Y && pMFAccount->isBrokerNSCCCompliant( dstrBrokerCode, getParent()->getDataGroupId());
            rCOAElem.setEnabled( NSCCApply ); 
            rCOAElem.setValue( fieldValue.c_str() );
            break;

        case COADlg::MSC_NETWORK_ID:

                getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::NetworkID, fieldValue);

                dstWorkSession->getOption ( ifds::NetworkTypeUpd,
                                dstrNetworkTypeUpd,
                                BF::HOST,
                                false);
                dstrNetworkTypeUpd.stripAll().upperCase();


                dstWorkSession->getOption ( ifds::ValidNetworkType,
                                dstrValidNetworkType,
                                BF::HOST,
                                false);

            if (!dstrValidNetworkType.empty())
            {
                rCOAElem.setEnabled( dstrNetworkTypeUpd == I_("Y") );
            }
            else
            {
                rCOAElem.setEnabled (false);
            }
                rCOAElem.setValue( fieldValue.c_str() );

                break;

        case COADlg::NSC_CLEARINGFIRM:
            getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::ClearingFirm, fieldValue);
            rCOAElem.setEnabled( hasUpdatePermission(  UAF::ACCOUNT_DETAIL )
                                || hasCreatePermission(  UAF::ACCOUNT_DETAIL )); 
                rCOAElem.setValue( hasReadPermission(UAF::ACCOUNT_DETAIL )?fieldValue.c_str():I_("") );

                break;
        case COADlg::NSC_AGENTFORFIRM:
            getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::AgentForFirm, fieldValue);
            rCOAElem.setEnabled( hasUpdatePermission(  UAF::ACCOUNT_DETAIL )
                                || hasCreatePermission(  UAF::ACCOUNT_DETAIL )); 
                rCOAElem.setValue( hasReadPermission(UAF::ACCOUNT_DETAIL )?fieldValue.c_str():I_("") );

                break;

        case COADlg::NSC_TPA:
            getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::TPA, fieldValue);
            rCOAElem.setEnabled( hasUpdatePermission(  UAF::ACCOUNT_DETAIL )
                              || hasCreatePermission(  UAF::ACCOUNT_DETAIL )); 
               rCOAElem.setValue( hasReadPermission(UAF::ACCOUNT_DETAIL )?fieldValue.c_str():I_("") );

                break;

        case COADlg::NSC_PARTICIPANTID:
            {
                getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::ParticipantID, fieldValue);		 
                //rCOAElem.setEnabled(false); 
                rCOAElem.setValue( hasReadPermission(UAF::ACCOUNT_DETAIL )?fieldValue.c_str():I_(""));
            }
            break;
        case COADlg::NSC_SOCIAL_CODE:
            getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::NSCCSocialCode, fieldValue);
            rCOAElem.setEnabled( hasUpdatePermission(  UAF::ACCOUNT_DETAIL )
                              || hasCreatePermission(  UAF::ACCOUNT_DETAIL )); 
               rCOAElem.setValue( hasReadPermission(UAF::ACCOUNT_DETAIL )?fieldValue.c_str():I_("") );

           break;
        case COADlg::SCR_ACCT_CUT_OFF_ID:
            {
            getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::AcctCutOffTimeExists, fieldValue );
            rCOAElem.setEnabledAndValue( hasReadPermission(  UAF::ACCT_LVL_CUT_OFF_TIME ), fieldValue.c_str() );
            }
            break;

         case COADlg::MSC_PW_CONSOL_TYPE_ID:
            {
               DString consolTypePW;
               getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::ConsolTypePW, consolTypePW, false);
               getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::ConsolTypePW, fieldValue );

               //bool bReadOnly = pMFAccount->checkPWConsolType( getParent()->getDataGroupId() );
               //rCOAElem.setEnabled( bReadOnly == false );

               rCOAElem.setEnabled( !( pMFAccount->checkPWConsolType( getParent()->getDataGroupId() ) ) );
               rCOAElem.setValue( fieldValue.c_str() );
            }
            break;
         case COADlg::MSC_ID_CONSOL_TYPE_ID:
            {
                DString consolTypeID;
                getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::ConsolTypeID, consolTypeID, false);
                getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::ConsolTypeID, fieldValue );

                // bool bReadOnly = pMFAccount->checkIDConsolType( getParent()->getDataGroupId() );
                //rCOAElem.setEnabled( bReadOnly == false );
                
                rCOAElem.setEnabled( !( pMFAccount->checkIDConsolType( getParent()->getDataGroupId() ) ) );
                rCOAElem.setValue( fieldValue.c_str() );
            }
            break;
         case COADlg::MSC_ED_CONSOL_TYPE_ID:
            {
                DString consolTypeED;
                getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::ConsolTypeED, consolTypeED, false);
                getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::ConsolTypeED, fieldValue );

                // bool bReadOnly = pMFAccount->checkIDConsolType( getParent()->getDataGroupId() );
                //rCOAElem.setEnabled( bReadOnly == false );
                
                rCOAElem.setEnabled( !( pMFAccount->checkEDConsolType( getParent()->getDataGroupId() ) ) );
                rCOAElem.setValue( fieldValue.c_str() );
            }
            break;
         case COADlg::SCR_FUND_CLASS_LIMITATION:
            {
               getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::FundLimitOvrdExist, fieldValue );
               rCOAElem.setEnabledAndValue( hasReadPermission(  UAF::ACCOUNT_TRADING_OVERRIDES ), fieldValue.c_str() );
            }
         break;

         case COADlg::SCR_RESP_ACCOUNT_TERMINATION:
            {
               fieldValue = I_("");
               rCOAElem.setEnabledAndValue( hasReadPermission(  UAF::RESP_ACCOUNT_TERMINATION ), fieldValue.c_str() );
            }
            break;

         case COADlg::SCR_RESP_ZERO_GRANT:
            {
               fieldValue = I_("");
               rCOAElem.setEnabledAndValue( hasReadPermission(  UAF::RESP_ZERO_GRANT ), fieldValue.c_str() );
            }
            break;

         case COADlg::SCR_RESP_INTERFACE_FILE:
            {
               fieldValue = I_("");
               rCOAElem.setEnabledAndValue( hasReadPermission(  UAF::RESP_INTERFACE_FILE ), fieldValue.c_str() );
            }
            break;

         case COADlg::MSC_ID_SIBLING_ONLY:
            {
               getParent()->getField (this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::SiblingOnly, fieldValue);

               if (dstWorkSession->isRES2Client ( getParent()->getDataGroupId() ))
               {
                  rCOAElem.setEnabled (false);
                  rCOAElem.setValue (fieldValue.c_str());
               }
               else
               {
                  rCOAElem.setEnabledAndValue (false, fieldValue.c_str());
               }
            }
            break;
         case COADlg::SCR_ACCT_LEVEL_SETTLEMENT_RULE:
            if( m_lInNASU )
            {
               rCOAElem.setEnabledAndValue( false, I_("") );
            }
            else
            {
               rCOAElem.setEnabled( hasUpdatePermission(  UAF::ACCT_LEVEL_SETTLEMENT_RULE ) || 
                                    hasCreatePermission(  UAF::ACCT_LEVEL_SETTLEMENT_RULE ));
               rCOAElem.setValue(   hasReadPermission( UAF::ACCT_LEVEL_SETTLEMENT_RULE )?strYes.c_str():I_("") );
            }
            break;
         case COADlg::SCR_LIF_GAIN_LOSS_ID:
            {
               DString strEligible;
               getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::EligExtTrfGainLoss, strEligible, false );
               bool blEnable = !m_lInNASU && strEligible.strip() == I_("Y");
               rCOAElem.setEnabledAndValue( blEnable, "Yes" );
            }
            break;
         case COADlg::MSC_UNLOCK_DATE:
            {
               getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds:: UnLockDeff, fieldValue);
               rCOAElem.setEnabled(false); 
               rCOAElem.setValue (hasReadPermission (UAF::ACCOUNT_DETAIL)? fieldValue.c_str() : I_(""));
            }
         break;
         case COADlg::MSC_UNLOCK_AMOUNT:
            {
               getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds:: UnLockGrossAmt, fieldValue);
               rCOAElem.setEnabled(false); 
               rCOAElem.setValue (hasReadPermission (UAF::ACCOUNT_DETAIL)? fieldValue.c_str() : I_(""));
            }
         break;
         //case COADlg::MSC_EXEMPT_PERIOD:
         //{
         //   getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds:: ExemptPeriod, fieldValue);
         //   rCOAElem.setEnabled(false); 
         //   rCOAElem.setValue (hasReadPermission (UAF::ACCOUNT_DETAIL)? fieldValue.c_str() : I_(""));
         //}
         //break;
         case COADlg::SCR_INVESTOR_AUTHORIZATION:
            if( m_lInNASU )
            {
               rCOAElem.setEnabledAndValue( false, I_("") );
            }
            else
            {
               DString dstrDirectDepositBankApplicable;
               DSTCWorkSession *dstWorkSession = 
                  dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
               dstWorkSession->getOption( ifds::DirectDepositBankApplicable, 
                                          dstrDirectDepositBankApplicable, 
                                          BF::HOST, 
                                          false );
               dstrDirectDepositBankApplicable.strip().upperCase();

               getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::IARuleSetup, fieldValue, false );
               rCOAElem.setEnabled( ( hasUpdatePermission(  UAF::INVESTOR_AUTHORIZATION_INFO )    || 
                                    ( hasCreatePermission(  UAF::INVESTOR_AUTHORIZATION_INFO )) ) && 
                                    dstrDirectDepositBankApplicable == I_("Y"));
               if ( fieldValue == I_("Y") )
               {
                  rCOAElem.setValue( strYes.c_str() );
               }
               else if ( fieldValue == I_("N"))
               {
                  rCOAElem.setValue( strNo.c_str() );
               }
               else
               {
                  rCOAElem.setValue( I_("") );
               }
            }
            break;
         case COADlg::SCR_ACCT_GUARNT_GUARD_OPTN :
            {
               getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::AcctGuarGuardExists, fieldValue, false );
               fieldValue.strip().upperCase();

               /*rCOAElem.setEnabled(  hasUpdatePermission(  UAF::ACCT_GUARNT_GUARD_OPTN ) || 
                                    hasCreatePermission(  UAF::ACCT_GUARNT_GUARD_OPTN ) );*/
               rCOAElem.setEnabled(true);
               if ( fieldValue == I_("Y") )
               {
                  rCOAElem.setValue( strYes.c_str() );
               }
               else if ( fieldValue == I_("N"))
               {
                  rCOAElem.setValue( strNo.c_str() );
               }
               else
               {
                  rCOAElem.setValue( I_("") );
               }
            }
            break;
         case COADlg::SCR_RESP_GOVT_FILING_AMENDMENT:
            {
               getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::GovAmendmentExist, fieldValue, false );
               fieldValue.strip().upperCase();

               fieldValue.strip().upperCase();
               rCOAElem.setEnabled(true);
               if ( fieldValue == I_("Y") )
               {
                  rCOAElem.setValue( strYes.c_str() );
               }
               else if ( fieldValue == I_("N"))
               {
                  rCOAElem.setValue( strNo.c_str() );
               }
               else
               {
                  rCOAElem.setValue( I_("") );
               }
            }
            break;
		   case COADlg::SCR_MATURITYINT_INSTR:
            {
               getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::MatIntExists, fieldValue, false );
               fieldValue.strip().upperCase();

   			   rCOAElem.setEnabled( hasUpdatePermission(  UAF::MATURITYSWPEEP_INSTR ) || 
                                    hasCreatePermission(  UAF::MATURITYSWPEEP_INSTR ));

               if ( fieldValue == I_("Y") )
               {
                  rCOAElem.setValue( strYes.c_str() );
               }
               else if ( fieldValue == I_("N"))
               {
                  rCOAElem.setValue( strNo.c_str() );
               }
               else
               {
                  rCOAElem.setValue( I_("") );
               }
            }
            break;
			 case COADlg::SCR_CASHSWEEP_INSTR:
            {
               getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::CashSweepExists, fieldValue, false );
               fieldValue.strip().upperCase();

			   rCOAElem.setEnabled( hasUpdatePermission(  UAF::MATURITYSWPEEP_INSTR ) || 
                                    hasCreatePermission(  UAF::MATURITYSWPEEP_INSTR ));      

               if ( fieldValue == I_("Y") )
               {
                  rCOAElem.setValue( strYes.c_str() );
               }
               else if ( fieldValue == I_("N"))
               {
                  rCOAElem.setValue( strNo.c_str() );
               }
               else
               {
                  rCOAElem.setValue( I_("") );
               }
            }
            break;
           case COADlg::MSC_ORGTYPE:
			   getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::OrgType, fieldValue);
			   rCOAElem.setValue (fieldValue.c_str());		
			   break;

		   case COADlg::MSC_SUBORGTYPE:
			   getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::SubOrgType, fieldValue);
			   rCOAElem.setValue (fieldValue.c_str());	
			   break;
		   case COADlg::MSC_NONFINANCIAL_CONFIRM:
			   getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::NonFinConfirm, fieldValue);
			   rCOAElem.setValue (fieldValue.c_str());	
			   break;
		   case COADlg::MSC_SETTLEMENT_CURRENCY:
			   getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::SettleCurrency, fieldValue);
			   rCOAElem.setValue (fieldValue.c_str());	
			   break;
           case COADlg::MSC_AGGREGATION_TYPE:
			   getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::AggregationType, fieldValue);
			   rCOAElem.setValue (fieldValue.c_str());
               rCOAElem.setEnabled(!fieldValue.stripAll().empty());
			   break;
         case COADlg::MSC_T5_ANNIVERSARY_DATE:
            if(dstWorkSession->isTaxAnniversaryClient(getParent()->getDataGroupId()))
            { 
               getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::T5AnniversaryDate, fieldValue );
               rCOAElem.setEnabled (false); 
               rCOAElem.setValue(fieldValue.c_str());
            }  
            break;
         case COADlg::SCR_ACCT_OWNERSHIP_ALLOC:
            {
               MFAccount* pMFAccount = dynamic_cast<COAProcess*>(getParent() )->getMFAccount();
               bool bHasAcctTaxAlloc = pMFAccount->hasAcctOwnershipAllocationRecord(getParent()->getDataGroupId());
               
               if(m_lInNASU)
               {
                  rCOAElem.setEnabled (false); 
                  rCOAElem.setValue(strNo.c_str());
               }
               else
               {
                  rCOAElem.setEnabled (true);
                  if (bHasAcctTaxAlloc)
                  {
                     rCOAElem.setValue(strYes.c_str());
                  }
                  else
                  {
                     rCOAElem.setValue(strNo.c_str());
                  }
               }
            }
            break;
         case COADlg::SCR_VALUE_VARIATION:
            {
               MFAccount* pMFAccount = dynamic_cast<COAProcess*>(getParent() )->getMFAccount();
               DString dstrInitialDate;
               pMFAccount->getField(ifds::InitialDate, dstrInitialDate, getParent()->getDataGroupId());
               if(dstrInitialDate.empty() || dstrInitialDate == I_("31129999"))
               {
                  rCOAElem.setValue(strNo.c_str());
               }
               else
               {
                  rCOAElem.setValue(strYes.c_str());
               }
            }
            break;
         case COADlg::SCR_ACCT_FEE_MODEL_ASSOCIATION:
            {
               DString dstrIsAcctAssociateExist;
               getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::AcctFeeModelAssociated, dstrIsAcctAssociateExist, false );
               dstrIsAcctAssociateExist.strip().upperCase();

               bool bHasAcctFeeModelAssociated = dstrIsAcctAssociateExist == I_("Y");
               
               if(m_lInNASU)
               {
                  rCOAElem.setEnabled (false); 
                  rCOAElem.setValue(strNo.c_str());
               }
               else
               {
                  rCOAElem.setEnabled( hasUpdatePermission(  UAF::ACCT_FEE_MODEL_ASSOCIATION )
                                    || hasCreatePermission(  UAF::ACCT_FEE_MODEL_ASSOCIATION )); 

                  if (bHasAcctFeeModelAssociated)
                  {
                     rCOAElem.setValue(strYes.c_str());
                  }
                  else
                  {
                     rCOAElem.setValue(strNo.c_str());
                  }
               }
            }
            break;
         case COADlg::MSC_DOC_PRINT_FORMAT:
            {
               getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::ShrOutputType, fieldValue);
               rCOAElem.setValue (fieldValue.c_str());
            }
            break; 
         case COADlg::SCR_SHR_STATEMENT_SCHED:
            {
               if(m_lInNASU)
               {
                  rCOAElem.setEnabled (false); 
                  rCOAElem.setValue(strNo.c_str());
               }
               else
               {
                  rCOAElem.setEnabled( hasReadPermission(  UAF::SHR_STATEMENT_SCHED ) );
                  if (hasReadPermission(  UAF::SHR_STATEMENT_SCHED ))
                  {
                     rCOAElem.setValue(strYes.c_str());
                     rCOAElem.setEnabled (true); 
                  }
                  else
                  {
                     rCOAElem.setValue(strNo.c_str());
                     rCOAElem.setEnabled (false); 
                  }
               }
            }
            break;
		 case COADlg::SCR_ACCT_REGIS_MAINT:
			 {
				 if(!m_lInNASU)
				 {
					 DString dstrAcctRegulatoryExist;
					 getParent()->getField(this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::AcctRegulatoryExist, dstrAcctRegulatoryExist, false);

					 if (hasReadPermission(UAF::ACCT_REGIS_MAINT) && dstrAcctRegulatoryExist == COADLG::STRING_Y)
					 {
                        rCOAElem.setValue(strYes.c_str());
						rCOAElem.setEnabled (true);
					 }
					 else
					 {
						rCOAElem.setValue(strNo.c_str());
						rCOAElem.setEnabled (true);
					 }
				 }
			 }
			 break;
		 case COADlg::SCR_ENT_REGIS_MAINT:
			 {
				 if(!m_lInNASU)
				 {
					 DString dstrEntRegDetlExist;
					 getParent()->getField(this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::EntRegDetlExist, dstrEntRegDetlExist, false);

					 if (hasReadPermission(UAF::ENTITY_REGULATORY_MAINT) && DSTCommonFunctions::codeInList(dstrEntRegDetlExist, I_("1,2")))
					 {
						rCOAElem.setValue(strYes.c_str());
						rCOAElem.setEnabled (true); 
					 }
					 else
					 {
						rCOAElem.setValue(strNo.c_str());
						rCOAElem.setEnabled (true); 
					 }
				 }
			 }
			 break;
         case COADlg::SCR_TAX_SLIPS:
            {
                if(m_lInNASU)
                {
                    rCOAElem.setEnabled (false); 
                    rCOAElem.setValue(strNo.c_str());
                }
                else
                {
                    DString dstrTaxFormsAppl;
                    pMFAccount->getField(ifds::TaxFormsAppl, dstrTaxFormsAppl, getParent()->getDataGroupId());
                    if (dstrTaxFormsAppl.stripAll().upperCase() == I_("Y"))
                    {
                        rCOAElem.setValue(strYes.c_str());
                        rCOAElem.setEnabled (true); 
                    }
                }
            }
            break;
         case COADlg::SCR_ACCOUNT_GROUP:
            {
               if(!m_lInNASU)
               {
                  DString dstrAccountGroupExist;
                  getParent()->getField(this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::AccountGroupExist, dstrAccountGroupExist, false);
                  dstrAccountGroupExist.strip().upperCase();
                  if (hasReadPermission(UAF::ACCOUNT_GROUPING) )
                  {
                     rCOAElem.setEnabled (true); 
                  }
                  else
                  {
                     rCOAElem.setEnabled (false); 
                  }

                  rCOAElem.setValue((dstrAccountGroupExist==I_("Y"))?strYes.c_str():strNo.c_str());
               }
            }
            break;
         case COADlg::SCR_PRIVATE_WEALTH_INFO:
            {
               if(!m_lInNASU)
               {
                  DString dstrPWEnrollment;
                  getParent()->getField(this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::PrivateWealthAcct, dstrPWEnrollment, false);
                  dstrPWEnrollment.strip().upperCase();
                  if (hasReadPermission(UAF::PRIVATE_WEALTH_INFO) )
                  {
                     rCOAElem.setEnabled (true); 
                  }
                  else
                  {
                     rCOAElem.setEnabled (false); 
                  }

                  rCOAElem.setValue((dstrPWEnrollment==I_("Y"))?strYes.c_str():strNo.c_str());
               }
            }
            break;
		 case COADlg::SCR_RESP_GRANT_INFO:
			 {
				 fieldValue = I_("");
				 rCOAElem.setEnabledAndValue( (hasReadPermission( UAF::RESP_BENEFICIARY ) && hasReadPermission( UAF::RESP_GRANTS )), fieldValue.c_str() );
			 }
			 break;
		 case COADlg::SCR_RESP_GRANT_INFO2:
			 {
				 fieldValue = I_("");
				 rCOAElem.setEnabledAndValue( (hasReadPermission( UAF::RESP_BENEFICIARY ) && hasReadPermission( UAF::RESP_GRANT_INFORMATION )), fieldValue.c_str() );
			 }
			 break;
		 case COADlg::SCR_RESP_NOTIONAL_ACTIVITY:
			 {
				 fieldValue = I_("");
				 rCOAElem.setEnabledAndValue( (hasReadPermission( UAF::RESP_NOTIONAL_ACTIVITY )), fieldValue.c_str() );
			 }
			 break;
		 case COADlg::SCR_REGISTERED_PLAN_TRANSFER:
			 {
				 getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::RegisteredTransfers, fieldValue );
				 rCOAElem.setEnabledAndValue( (hasReadPermission( UAF::REG_PLAN_TRANSFER)), fieldValue.c_str() );
			 }
			 break;
		 case COADlg::SCR_ACCT_ROUNDING_RULE:
			 {
				 if ( pMFAccount) 
				 {   
					 if( pMFAccount->hasAcctRoundingRule(getDataGroupId()) )					
						 fieldValue = I_("Y");
					 else
						 fieldValue = I_("");

					 rCOAElem.setEnabledAndValue( (hasReadPermission( UAF::ACCT_ROUNDING_RULE)), ((fieldValue == I_("Y")) ? strYes.c_str() : fieldValue.c_str()) );
				 }
			 }
			 break;
		 case COADlg::SCR_ACCT_DELETION_REVIEW:
			 {				 
				 rCOAElem.setEnabledAndValue( (hasReadPermission( UAF::ACCT_DELETION_REVIEW)), strYes.c_str() );
			 }
			 break;
		 case COADlg::SCR_RDSP_ACCOUNT_INFO:
			 {	
				 fieldValue = I_("");				
				 rCOAElem.setEnabledAndValue( (hasReadPermission( UAF::RDSP_ACCOUNT_INFORMATION)), fieldValue.c_str() );
			 }
			 break;
		 case COADlg::SCR_RDSP_NOTIONAL_ACTIVITY:
			 {	
				 fieldValue = I_("");				
				 rCOAElem.setEnabledAndValue( (hasReadPermission( UAF::RDSP_NOTIONAL_ACTIVITY)), fieldValue.c_str() );
			 }
			 break;
		 case COADlg::SCR_RDSP_NOTIONAL_BALANCE:
			 {	
				 fieldValue = I_("");				
				 rCOAElem.setEnabledAndValue( (hasReadPermission( UAF::RDSP_NOTIONAL_BALANCE)), fieldValue.c_str() );
			 }
			 break;
      case COADlg::MSC_INVESTOR_CLASSIFICATION:
			   getParent()->getField( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::InvestorClassification, fieldValue);
			   rCOAElem.setValue (fieldValue.c_str());	
			   break;
       default :
            assert( 0 );
   }
}

//******************************************************************************
void COADlg::OnChangeEdtFind() 
{
    CString searchCrit;
    m_edtFind.GetWindowText( searchCrit );
    searchCrit.MakeUpper();
    //int len = searchCrit.GetLength();
    //if ( len > 1 )
    //    m_edtFind.SetWindowText( CString(searchCrit[len-1]) );
    //m_edtFind.SetSel( 0, 2 );
}

//******************************************************************************
void COADlg::OnSelchangeCmbView() 
{
    CString comboSelection, tmp1, tmp2, tmp3, tmp4;
    long filtCrit;
    m_cmbView.GetWindowText( comboSelection );

    tmp1.LoadString( IDS_CAT_CAUTIONS );
    tmp2.LoadString( IDS_CAT_OPTIONS );
    tmp3.LoadString( IDS_CAT_ATTRIBS );
    tmp4.LoadString( IDS_CAT_ALL );

    if( comboSelection == tmp1 )
        filtCrit = COA_TYPE_CAUTION;
    else if( comboSelection == tmp2 )
        filtCrit = COA_TYPE_OPTION;
    else if( comboSelection == tmp3 )
        filtCrit = COA_TYPE_ATTRIB;
    else if( comboSelection == tmp4 )
        filtCrit = 0;
    else
        assert(0);

    m_ElementMap.filterCOA( filtCrit );
    reDisplayGrid();
}

//******************************************************************************
bool COADlg::validateGridCells( unsigned long nRow, unsigned long nCol, const CString & value)
{
    COAElement * pCOAElem = m_ElementMap[nRow-1];
    long lId = pCOAElem->getId();
    bool retVal = true;
    switch( lId )
    {
      case COADlg::STP_PURCH_ID :
         retVal = setCOAField( IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::StopPurchase, value );
         break;
      case COADlg::STP_REDEM_ID : 
         retVal = setCOAField( IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::StopRed, value );
         break;
	  case COADlg::STP_REASON_ID :
         retVal = setCOAField( IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::StopReason, value );
         break;    	  
	  case COADlg::STP_ADDITIONAL_REASON_ID :
         retVal = setRemoveUnwantedChars (CString (value));
         break;
 	  case COADlg::STP_STOP_NFU :
         retVal = setCOAField( IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::StopNFU, value );
         break;
      case COADlg::STP_XFERO_ID : 
         retVal = setCOAField( IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::StopXferOut, value );
         break;
      case COADlg::STP_XFERI_ID :
         retVal = setCOAField( IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::StopXferIn, value );
         break;
      case COADlg::STP_FRREB_ID :
         retVal = setCOAField( IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::StopFCrebal, value );
         break;
      case COADlg::STP_REDEM_SETTLE_ID :
         retVal = setCOAField( IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::StopRedSettle, value );
         break;
      case COADlg::HLD_DIV_PAYMENT :
         retVal = setCOAField( IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::HoldDivPymt, value );
         break;


    //  case COADlg::SCR_BENEF_ID :
    //      retVal = setCOAField( COAPROC::COA_MFACCOUNT_CBO, ifds::BeneficialOwner, value );
    //        break;
    //  case COADlg::FEE_ADMFEE_ID :
    //      rCOAElem.setValue( NULL_STRING );
    //  break;
    //  case COADlg::FEE_WTHDTX_ID :
    //      rCOAElem.setValue( NULL_STRING );
    //  break;
      case COADlg::FEE_FEEWVD_ID :
         retVal = setCOAField( IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::FeeWaived, value );
         break;
      case COADlg::SPR_EMPCNF_ID :
         retVal = setCOAField( IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::SupEmpConf, value );
         break;
      case COADlg::SPR_CONFIRM_ID :
         retVal = setCOAField( IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::SupConf, value );
         break;
      case COADlg::MSC_EMPL_ID :
         retVal = setCOAField( IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::Employee, value );
         break;
      case COADlg::MSC_MARKET_MAIL :
         retVal = setCOAField( IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::MarketMail, value );
         break;
      case COADlg::MSC_AFFLUENT :
         retVal = setCOAField (IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::Affluent, value );
         break;

        case COADlg::MSC_NETWORK_ID:
            retVal = setCOAField( IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::NetworkID, value );
         break;

//   case COADlg::SCR_ESCROW_ID :
//      retVal = setCOAField( COAPROC::COA_MFACCOUNT_CBO, ifds::Escrow, value );
//      break;
/*   case COADlg::MSC_INTRFOR_ID :
      retVal = setCOAField( COAPROC::COA_MFACCOUNT_CBO, ifds::InTrustFor, value );
      break;*/
//   case COADlg::MSC_STATUS_ID :
//      retVal = setCOAField( COAPROC::COA_MFACCOUNT_CBO, ifds::AcctStatus, value );
//      break;
      case COADlg::MSC_UNSZBL_ID :
         retVal = setCOAField( IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::Unseizable, value );
         break;
      case COADlg::MSC_TELFAX_AGREEMENT_ID :
         retVal = setCOAField( IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::TelFaxAgreement, value );
         break;
      case COADlg::MSC_STOP_ADJDATE : //P0186486_FN16_Misc. Enhancements_Stop Adjustment Date
         retVal = setCOAField( IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::StopAdjDate, value );
         break;
         
      case COADlg::GST_EXEMPT_ID :
         retVal = setCOAField( IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::GSTExempt, value );
         break;

      case COADlg::PST_EXEMPT_ID :
         retVal = setCOAField( IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::ApplyPST, value );
         break;

      case COADlg::FEE_BANK_CHARGE_ID :
         retVal = setCOAField( IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::BankChrgs, value );
         break;

      case COADlg::MSC_CONSOLID_EFT_ID :
         retVal = setCOAField( IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::ConsolidEFT, value );
         break;

      case COADlg::FEE_MGMT_FEE_PAY_OPTN:
         retVal = setCOAField( IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::MgmtFeePayOption, value );
         break;

      case COADlg::FEE_EARLY_REDEMPTION_FEE_OPT:
         retVal = setCOAField( IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::ChargeERFee, value );
         break;

      case COADlg::FEE_SHORT_TERM_TRFER_FEE:
         retVal = setCOAField( IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::ChargeSTTRFee, value );
         break;

	  case COADlg::FEE_NEXT_MFR_PROCESS_DATE:

         retVal = setCOAField( IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::NextMFRProcessDate, value );
         break;
		 
      //case COADlg::STP_AMSREBALANCING_ID :
      //   retVal = setCOAField( IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::StopAMSRebalancing, value );
      //   break;

      case COADlg::MSC_CLEARING_ID :
         retVal = setCOAField( IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::ClearingID, value );
         if( retVal )
         {
            updateSettlementLocation( DString( value ) );
         }
         break;

      case COADlg::MSC_NETWORKCONTROLIND :
         retVal = setCOAField( IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::Networkcontrolind, value );
         break;

      case COADlg::NSC_CLEARINGFIRM :
         retVal = setCOAField( IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::ClearingFirm, value );
         retrieveValue( NSC_PARTICIPANTID );
         setParticipantID();
            break;

      case COADlg::NSC_AGENTFORFIRM :
         retVal = setCOAField( IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::AgentForFirm, value );
         break;

      case COADlg::NSC_TPA :
         retVal = setCOAField( IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::TPA, value );
         break;

      case COADlg::NSC_SOCIAL_CODE:
         retVal = setCOAField( IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::NSCCSocialCode, value );
         break;

      case COADlg::MSC_PW_CONSOL_TYPE_ID:
         retVal = setCOAField( IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::ConsolTypePW, value );
         break;

      case COADlg::MSC_ID_CONSOL_TYPE_ID:
         retVal = setCOAField( IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::ConsolTypeID, value );
         break;

      case COADlg::MSC_ED_CONSOL_TYPE_ID:
         retVal = setCOAField( IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::ConsolTypeED, value );
         break;
      case COADlg::MSC_ORGTYPE :
         retVal = setCOAField (IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::OrgType, value );
         if( retVal )
         {
            updateSubOrgType(DString( value ));
         }
         break;
      case COADlg::MSC_SUBORGTYPE :
         retVal = setCOAField (IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::SubOrgType, value );
         break;
     case COADlg::MSC_NONFINANCIAL_CONFIRM :
         retVal = setCOAField( IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::NonFinConfirm, value );
         break;
     case COADlg::MSC_SETTLEMENT_CURRENCY :
         retVal = setCOAField( IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::SettleCurrency, value );
         break;
     case COADlg::MSC_AGGREGATION_TYPE :
         retVal = setCOAField( IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::AggregationType, value );
         break;
     case COADlg::MSC_DOC_PRINT_FORMAT:
         retVal = setCOAField( IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::ShrOutputType, value );
         break;
     case COADlg::MSC_INVESTOR_CLASSIFICATION :
       retVal = setCOAField( IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::InvestorClassification, value );
         break;
      
		//xyz -- no sure if we need do this??
		 //case COADlg::NSC_PARTICIPANTID :
         //retVal = setCOAField( IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::ParticipantID, value );
         //break;

/*   case COADlg::MSC_RESP_ID :
      retVal = setCOAField( COAPROC::COA_MFACCOUNT_CBO, ifds::CESGEligible, value );
      break; */
//   default :
//      assert( 0 );
    };  
    if( retVal  == true )
    {
        pCOAElem->setValue( value );
    }
    return(retVal);
}

//******************************************************************************
void COADlg::LButtonDblClkGridCells( unsigned long nRow, unsigned long nCol )
{
    if( nCol == 0 && m_ElementMap[nRow-1]->isTitle() )
    {
        m_ElementMap.changeGroupState( m_ElementMap[nRow-1]->getId(), !m_ElementMap[nRow-1]->isVisible() );
        setTitlesButtonCaption( !m_ElementMap.hasExpandedTitles( ));
        reDisplayGrid();
    }
}

//******************************************************************************
void COADlg::OnBtnSearch() 
{

    CString searchCrit;
    ROWCOL nEditRow, nEditCol;
    m_gridWindow.GetCurrentCell(nEditRow, nEditCol);
    if( nEditRow == 0 )
        nEditRow = 1;

    m_edtFind.GetWindowText( searchCrit );
    searchCrit.MakeUpper();

    if( searchCrit == NULL_STRING )
        return;

    int pos = m_ElementMap.findNextMatch( nEditRow, searchCrit );

    if( pos == -1 && !m_ElementMap.hasExpandedTitles( ) )
    {
        expandCollapseAll( true );
        reDisplayGrid();
        pos = m_ElementMap.findNextMatch( nEditRow, searchCrit );
    }

    if( pos != -1 )
    {
        m_gridWindow.SetFocus();
        m_gridWindow.SetCurrentCell( pos + 1 , 2, GX_SCROLLINVIEW | GX_UPDATENOW );
    }

    m_gridWindow.SelectRange(CGXRange( ).SetTable( ), FALSE );
}

//******************************************************************************
void COADlg::expandCollapseAll( bool bExpandCollapse )
{
    COAElementMap::iterator iter = m_ElementMap.begin();
    while( iter != m_ElementMap.end() )
    {
        if( (*iter).second->isTitle() )
            m_ElementMap.changeGroupState( (*iter).second->getId(), bExpandCollapse );
        ++iter;
    }

    setTitlesButtonCaption( !bExpandCollapse );
}

//******************************************************************************
void COADlg::OnBtnCollapse() 
{
    COAElementMap::iterator iter = m_ElementMap.begin();

    bool currentState = m_ElementMap.hasExpandedTitles( ); //true => has expanded , false => doesn't have expanded
    expandCollapseAll( !currentState );

    if( currentState ) // if collapsing
    {
        m_gridWindow.SetCurrentCell( 1, 2, GX_SCROLLINVIEW | GX_UPDATENOW );
    }

    reDisplayGrid();
}

//******************************************************************************
void COADlg::setTitlesButtonCaption( bool lExpand )
{
    CString lCStrTitlesButtonCaption;
	if( lExpand )
		lCStrTitlesButtonCaption.LoadString(TXT_EXPAND_TITLES);
   
	else		
		lCStrTitlesButtonCaption.LoadString(TXT_COLLAPSE_TITLES);
 

    GetDlgItem(IDC_BTN_COLLAPSE)->SetWindowText( lCStrTitlesButtonCaption );
}


//******************************************************************************
BOOL COADlg::COAGrid::OnDeleteCell(ROWCOL nRow, ROWCOL nCol)
{
    return(FALSE);
}

//******************************************************************************
BOOL COADlg::COAGrid::OnValidateCell( ROWCOL nRow, ROWCOL nCol )
{
    if( nCol == 2 )
    {
        if( m_COADlg != NULL && nRow > 0 )
        {


            CString s, s1;
            //else
            //{
                GetControl(nRow, nCol)->GetCurrentText(s);
                //s1 = GetValueRowCol( nRow, nCol );
                //if( s != GetValueRowCol( nRow, nCol ) )
                    return(m_COADlg->validateGridCells(nRow, nCol, s ));
                //else
                    //return(true);
            //}

        }
    };
    return(false);
}

//******************************************************************************
BOOL COADlg::COAGrid::OnLButtonDblClkRowCol(ROWCOL nRow, ROWCOL nCol, UINT nFlags, CPoint pt)
{
    if( nCol == 0 )
    {
        if( m_COADlg != NULL && nRow > 0 )
            m_COADlg->LButtonDblClkGridCells( nRow, nCol );
    }
    return(true);
}

//******************************************************************************
BOOL COADlg::COAGrid::MoveCurrentCell(int direction, UINT nCell, BOOL bCanSelectRange )
{
    SelectRange(CGXRange( ).SetTable( ), FALSE );
    return(CGXGridCore::MoveCurrentCell( direction, nCell, bCanSelectRange));
}

//********************************************************************************
void COADlg::COAGrid::LoadSettings()
{
    int count = 3;
    bool useDefault=false;
    DString strHold;
    DString title(GRID_WINDOW);
    DString dstrCol[] = {FIELD_SCREEN,TYPE,VALUE};


    ConfigManager *pWorkstation = ConfigManager::getManager( WORKSTATION );
    Configuration workstation = pWorkstation->retrieveConfig( COADLG_CLASS );

    // Get column count
    strHold = title;
    strHold += I_( ".colcount" );
    strHold = workstation.getValueAsString( strHold );
    if( strHold.empty() )
    {
        // try to get the default column setting
        pWorkstation = ConfigManager::getManager( DEFAULTWORKSTATION );
        workstation = pWorkstation->retrieveConfig( COADLG_CLASS );
        strHold = title;
        strHold += I_( ".colcount" );
        strHold = workstation.getValueAsString( strHold );
        if( strHold.empty() )
            useDefault=true;
    }
    else
    {
        count = asInteger( strHold );
        if( count <= 0 )
        {
            useDefault=true;
        }
    }

    int  colWidth = 0;
    for( int icol = 0;icol< count;icol++ )
    {
        strHold = title;
        strHold += I_( "." );
        strHold += dstrCol[icol];
        if( useDefault )
            colWidth = 100;
        else
        {
            strHold = workstation.getValueAsString( strHold );
            colWidth = strHold.asInteger();
        }
        SetColWidth( icol, icol, colWidth );  
    } 
}

//******************************************************************************
void COADlg::COAGrid::SaveSettings()
{
    ConfigManager *pWorkstation = ConfigManager::getManager( WORKSTATION );
    Configuration workstation = pWorkstation->retrieveConfig( COADLG_CLASS );
    DString dstrCol[] = {FIELD_SCREEN,TYPE,VALUE};
    int  colWidth = 0;

    DString title( GRID_WINDOW );
    int count = 3;
    DString strHold( title );
    strHold += I_( ".colcount=" );
    strHold += asString( count );
    workstation.set( strHold );
    for( int icol = 0; icol < count;icol++ )
    {
        colWidth = GetColWidth( icol );
        strHold = title + I_( "." );
        strHold += dstrCol[icol];
        strHold += I_( "=" );
        strHold += asString( colWidth );
        workstation.set( strHold );
    }

    pWorkstation->storeConfig( workstation );
    pWorkstation->persist();   
}

//************************************************************
BOOL COADlg::COAGrid::OnActivateGrid( BOOL bActivate )
{
    if( bActivate == FALSE )
    {
        SaveSettings();
    }
    return(TRUE);
}


//******************************************************************************
COADlg::COAElement::COAElement( COA_ENTRY_ID   lId, const CString & lDispName, COA_Type lType, const CString & lStrCommand, 
                                bool lHasChange, COA_ENTRY_ID lParent, WORD  lControlType, CHOICE_TYPE eChoiceType ) 
: m_Id( lId ), m_DisplayName( lDispName), m_Type( lType ), m_Command( lStrCommand ), 
m_HasChange( lHasChange ), m_Visible( true ), m_Parent(lParent), m_ControlType( lControlType ), m_Enabled(true),
m_ChoiceType( eChoiceType ), m_Filtered ( true )
{
    m_Visible = false;
}

//******************************************************************************
COADlg::COAElement::~COAElement()
{
}

//******************************************************************************
void COADlg::COAElement::setChoiceList( )
{
    CString lValue;
    switch( m_ChoiceType )
    {
        case CHOICE_TYPE_YES_NO:
            m_ChoiceList = getComboValue();
            break;

        case CHOICE_TYPE_CHANGE:
            lValue = getValue();
            m_ChoiceList = lValue + getComboValue(); //COADLG::STRING_NL + COADLG::STRING_CHANGE;

            break;

        case CHOICE_TYPE_VIEW :
            lValue = getValue();
            m_ChoiceList = lValue + getComboValue(); //COADLG::STRING_NL + COADLG::STRING_CHANGE;
            break;

        case CHOICE_TYPE_FIELD_SUBST :
            m_ChoiceList = getComboValue();
            break;

        default :
            m_ChoiceList = _T("");
            break;
    }

   /*
    switch ( m_ChoiceType )
    {
    case CHOICE_TYPE_YES_NO :
       m_ChoiceList = COADLG::STRING_YES_NO;
       break;
    case CHOICE_TYPE_CHANGE :
       lValue = getValue();
       if ( lValue == _T(""))
          lValue = COADLG::STRING_YES;
       m_ChoiceList = lValue + COADLG::STRING_NL + COADLG::STRING_CHANGE;
       break;
    case CHOICE_TYPE_VIEW :
       lValue = getValue();
       if ( lValue == _T(""))
          lValue = COADLG::STRING_YES;
       m_ChoiceList = lValue + COADLG::STRING_NL + COADLG::STRING_VIEW;
       break;
    default :
       m_ChoiceList = _T("");
    }
   */
}

//******************************************************************************
CString COADlg::COAElement::getDispType()
{
    CString tmp;
    switch( m_Type )
    {
        case COADlg::COA_TYPE_TITLE :
            tmp.LoadString( IDS_CAT_TITLE );
            return(tmp);//_T("Title");
        case COADlg::COA_TYPE_CAUTION : 
            tmp.LoadString( IDS_CAT_CAUTIONS );
            return(tmp);//_T("Caution");
        case COADlg::COA_TYPE_OPTION : 
            tmp.LoadString( IDS_CAT_OPTIONS );
            return(tmp);//_T("Option");
        case COADlg::COA_TYPE_ATTRIB :
            tmp.LoadString( IDS_CAT_ATTRIB );
            return(tmp);//_T("Attribute");
        default :
            assert (0);
            return(_T(""));
    }
}

//******************************************************************************
// This is an override to process the key stokes capture within the grid.
//******************************************************************************
BOOL COADlg::COAGrid::ProcessKeys(CWnd* pSender, UINT nMessage, UINT nChar, UINT nRepCnt, UINT flags)
{
    BOOL bShift = GetKeyState(VK_SHIFT) & 0x8000;
    if( nMessage == WM_KEYDOWN )
    {
        switch( nChar )
        {
            case VK_TAB:      // Tab-Key
            {            
                if( bShift )
                    GetParentOwner( )->GetDlgItem ( IDC_BTN_SEARCH )->SetFocus();
                else
                    GetParentOwner( )->GetDlgItem ( IDOK )->SetFocus();
                return(TRUE);
            }
        }
    }
    return(CGXGridWnd::ProcessKeys(pSender, nMessage, nChar, nRepCnt, flags));
}

//******************************************************************************

DString COADlg::getSubstitutionList(COA_ENTRY_ID lId)
{
    DString emptyStr(NULL_STRING);
    AbstractProcess * pProcess = dynamic_cast< AbstractProcess * >( getParent() );
    if( !pProcess )
        return(emptyStr);

    BFFieldId idSubstition = getSubstitutionId(lId);
    const BFProperties * pBFProp = pProcess->getFieldAttributes( this, IFASTBP_PROC::COA_MFACCOUNT_CBO, idSubstition );
    DString *pdstrSubst = NULL;

    if( pBFProp )
        pdstrSubst = pBFProp->getAllSubstituteValues();

    int npos = 0;
    if( pdstrSubst )
    {
        DString dstr(*pdstrSubst);
        return(getDescriptions(dstr));
    }
    else
    {
        DString dstr(NULL_STRING);
        const BFDataFieldProperties* pProps = BFDataFieldProperties::get( idSubstition );
        if( NULL != pProps->getSubstitutionSet( ClientLocaleContext::get() ) )
            pProps->getAllSubstituteValues( dstr, ClientLocaleContext::get(), true );
        return(getDescriptions(dstr));
    }

    return(emptyStr);
}

//******************************************************************************

DString COADlg::getDescriptions(const DString& strSubstList)
{
    DString strCopySubst(strSubstList);
    DString strRetVal(NULL_STRING), strTemp(NULL_STRING);
    int nPos = strCopySubst.find('=');
    while( nPos != DString::npos )
    {
        strCopySubst = strCopySubst.right(strCopySubst.length() -1 - nPos);
        strTemp = strCopySubst;
        nPos = strTemp.find(';');
        if( nPos != DString::npos )
            strTemp = strTemp.left(nPos);
        strRetVal += strTemp;
        strRetVal += COADLG::STRING_NL;
        nPos = strCopySubst.find('=');
    }

    if( !strRetVal.empty() )
        strRetVal = strRetVal.left(strRetVal.length()-1);

    return(strRetVal);
}

//*****************************************************************************
BFFieldId COADlg::getSubstitutionId(COA_ENTRY_ID lId)
{
    BFFieldId idSubst = ifds::NullFieldId;
    switch( lId )
    {
      case FEE_BANK_CHARGE_ID:
         {
            idSubst = ifds::BankChrgs;
         }
         break;
      case FEE_MGMT_FEE_PAY_OPTN:
         {
            idSubst = ifds::MgmtFeePayOption;
         }
         break;
      case MSC_CLEARING_ID:
         {
            idSubst = ifds::ClearingID;
         }
         break;

      case STP_REASON_ID:
         {
            idSubst = ifds::StopReason;
         }
         break;

      case MSC_NETWORKCONTROLIND:
         {
            idSubst = ifds::Networkcontrolind;
         }
         break;

      case MSC_MARKET_MAIL:
         {
            idSubst = ifds::MarketMail;
         }
         break;

      case MSC_AFFLUENT:
         {
            idSubst = ifds::Affluent;
         }
         break;
      case MSC_ORGTYPE:
		  {
			  idSubst = ifds::OrgType;
		  }
		  break;
		 
	  case MSC_SUBORGTYPE:
		  {
			  idSubst = ifds::SubOrgType;
		  }
		  break;
      case MSC_NETWORK_ID:
         {
            idSubst = ifds::NetworkID;
         }
         break;
      case MSC_PW_CONSOL_TYPE_ID:
         {
            idSubst = ifds::ConsolTypePW;
         }
         break;
      case MSC_ID_CONSOL_TYPE_ID:
         {
            idSubst = ifds::ConsolTypeID;
         }
         break;
      case MSC_ED_CONSOL_TYPE_ID:
         {
            idSubst = ifds::ConsolTypeED;
         }
         break;
      case MSC_ID_SIBLING_ONLY:
         {
            idSubst = ifds::SiblingOnly;
         }
         break;
      case NSC_SOCIAL_CODE:
         {
            idSubst = ifds::NSCCSocialCode;
         }
         break;
      case MSC_NONFINANCIAL_CONFIRM:
         {
            idSubst = ifds::NonFinConfirm;
         }
         break;

      case MSC_SETTLEMENT_CURRENCY:
         {
            idSubst = ifds::SettleCurrency;
         }
         break;
      case MSC_DOC_PRINT_FORMAT:
         {
            idSubst = ifds::ShrOutputType;
         }
         break;
      case MSC_AGGREGATION_TYPE:
         {
            idSubst = ifds::AggregationType;
         }
         break;
      case MSC_INVESTOR_CLASSIFICATION:
         {
           idSubst = ifds::InvestorClassification;
         }
         break;
      default:
         assert(0);//why call it for the wrong COA_ENTRY_ID?
    }

    return(idSubst);
}

//******************************************************************************
void COADlg::retrieveHypoRedValue(COAElement &rCOAElem)
{
    DString strFirstSettleDate;

    //Get Yes-No descriptions based on current screen language.
    DString strYes = DSTCommonFunctions::getDescription(I_("Y"), ifds::Yes_NO);
    DString strNo = DSTCommonFunctions::getDescription(I_("N"), ifds::Yes_NO);

    CString strHypoRed = strYes.c_str();
    getParent()->getField(this, IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::FirstSettleDate, strFirstSettleDate, false);
    if (strFirstSettleDate.strip().empty() || strFirstSettleDate == I_("12319999") )
        strHypoRed = strNo.c_str();
    rCOAElem.setEnabled( hasReadPermission(  UAF::HYPOTHETICAL_REDEMPTION ) && 
        strHypoRed == strYes.c_str() );
    rCOAElem.setValue( strHypoRed );
}

//******************************************************************************
/*
void COADlg::OnOK()
{
    DString dstrTaxType;
    getParent()->getField(this, ifds::TaxType, dstrTaxType, false );
    if ( m_lInNASU && ( dstrTaxType == I_( "B" ) || dstrTaxType == I_( "L" ) || dstrTaxType == I_( "2" ) ) )
    {
        if ( AfxMessageBox(CString("Please set up RIF_LIF_LRIF screen after refresh!"), MB_OK) == IDOK )

    }
}
*/

//******************************************************************************
void COADlg::updateSettlementLocation( const DString &dstrValue )
{
    int ItemCount = m_ElementMap.itemCount();

    COAElement * pCOAElem;
    COAElementMap::iterator iter = m_ElementMap.begin();
    for( int i = 0; i < ItemCount; i++ )
    {
        pCOAElem = m_ElementMap[i];
        if( pCOAElem && pCOAElem->getId() == COADlg::SCR_ACCT_SETTLE_LOC )
        {
            bool lEnabled = ( hasUpdatePermission( UAF::SETTLE_LOCATION_ACCT_LVL ) || hasCreatePermission( UAF::SETTLE_LOCATION_ACCT_LVL ) );
            WORD lControlType = pCOAElem->getControlType();
            retrieveValue( COADlg::SCR_ACCT_SETTLE_LOC );   // Set Value
            // Set Combo Value
            DString dstrComboValue(NULL_STRING), strValue1,strValue2;
            CString eValue = pCOAElem->getValue();
            if( eValue == _T("") )
            {
            getParent()->getField(this,BF::NullContainerId,COAPROC::lYes,strValue1,true);
            }
            getParent()->getField(this,BF::NullContainerId,COAPROC::lChange,strValue2,true);
            if( !dstrValue.empty() )
            {
            dstrComboValue = strValue1 + COADLG::STRING_NL + strValue2;
            }
            pCOAElem->setComboValue( dstrComboValue.c_str() );
            pCOAElem->setChoiceList();

            m_gridWindow.SetStyleRange( CGXRange( i + 1,2), CGXStyle().SetControl(GX_IDS_CTRL_CBS_DROPDOWNLIST)
                                        .SetChoiceList( pCOAElem->getChoiceList() ).SetValue( pCOAElem->getValue() ).SetEnabled( lEnabled ).SetReadOnly( !lEnabled )
                                        .SetVerticalAlignment(DT_VCENTER));

            break;
        }
    }

}

/*************************************************************************************/
void COADlg::setParticipantID()
{
    int ItemCount = m_ElementMap.itemCount();

    COAElement * pCOAElem;
    for( int i = 0; i < ItemCount; i++ )
    {
        pCOAElem = m_ElementMap[i];
        if( pCOAElem && pCOAElem->getId() == COADlg::NSC_CLEARINGFIRM )
        {
            pCOAElem = m_ElementMap[i+1];
            CString s = pCOAElem->getValue();	
            m_gridWindow.SetStyleRange(CGXRange( i+2 ,2), CGXStyle()
                                    .SetControl( GX_IDS_CTRL_STATIC )
                                    .SetValue( s ) );
            break;
        }
    }
}

//******************************************************************************
void COADlg::OnBtnHistorical()
{
    MAKEFRAME2( CND::IFASTGUI_CONDITION, COADLG_CLASS, I_("OnBtnHistorical") );
    CWaitCursor cursor;
    E_COMMANDRETURN eRtn;

    DString dstrAccountNum;
    getParent()->getField(this, ifds::AccountNum, dstrAccountNum );
    setParameter( I_( "AccountNum" ), dstrAccountNum );
    setParameter(I_("TYPE"), I_("ACCT") );

    try
    {
        eRtn = getParentProcess()->invokeProcessFromChild( this, CMD_BPROC_HISTORICAL_INFO /*CMD_BPROC_HISTORICAL_ACCOUNT*/, PROC_SUPPORT );
        {
            if( eRtn != CMD_OK && eRtn != CMD_CANCEL && eRtn != CMD_MODELESS_INPROCESS )
                ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
                return;
        }
    }
    catch( ConditionException &ce )
    {
        ConditionMessageBox( ce );
    }
    catch( ... )
    {
        DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
    }

}

//******************************************************************************
bool COADlg::validateClearingFirm()
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, COADLG_CLASS, I_( "validateClearingFirm" ));
    DString dstrNSCCCompliant, dstrBrokerCode;

    DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
    dstWorkSession->getOption( ifds::NSCCCompliant, dstrNSCCCompliant, getParent()->getDataGroupId(), false );

    MFAccount* pMFAccount = dynamic_cast<COAProcess*>(getParent() )->getMFAccount();
    pMFAccount->getField ( ifds::BrokerCode, dstrBrokerCode, getParent()->getDataGroupId() );
    bool NSCCApply = pMFAccount->isBrokerNSCCCompliant(dstrBrokerCode, getParent()->getDataGroupId());
    if( NSCCApply && dstrNSCCCompliant == I_("Y") )
    {
        pMFAccount->validateClearingFirm( getParent()->getDataGroupId() );
        SEVERITY sevRte =  GETCURRENTHIGHESTSEVERITY();
        if ( sevRte  >= WARNING )
        {
            ConditionMessageBox( MYFRAME(), GETCURRENTHIGHESTSEVERITY() );
            return false;
        }
    }
    return true;
}

//******************************************************************************
bool COADlg::validateAffluent()
{
    MFAccount* pMFAccount = dynamic_cast<COAProcess*>(getParent() )->getMFAccount();
	if( pMFAccount )
	{
		int iValid = pMFAccount->validateAffluent( getParent()->getDataGroupId() );
		if ( iValid == 1 )
		{
		   	CString cstrIconError;
			cstrIconError.LoadString(TXT_CANT_SET_AFFLUENT_NOT_APPLICABLE);
			AfxMessageBox( cstrIconError, MB_ICONERROR );
		   return false;
		}
		else if ( iValid == 2 )
		{
		    CString cstrIconError;
			cstrIconError.LoadString(TXT_CANT_SET_AFFLUENT_PREV_AFFLUENT_BAL);
			AfxMessageBox( cstrIconError, MB_ICONERROR );
		   return false;
		}
		else if ( iValid == 3 )
		{
		    CString cstrIconError;
			cstrIconError.LoadString(TXT_CANT_SET_AFFLUENT_PREV_AFFLUENT_BAL_NEWACCT );
			AfxMessageBox( cstrIconError, MB_ICONERROR );
		   return false;
		}
	}
		
	return true;
}
//**********************************************************************
void COADlg::updateSubOrgType( const DString &dstrValue )
{
    int ItemCount = m_ElementMap.itemCount();

    COAElement * pCOAElem;
    COAElementMap::iterator iter = m_ElementMap.begin();
    for( int i = 0; i < ItemCount; i++ )
    {
        pCOAElem = m_ElementMap[i];
        if( pCOAElem && pCOAElem->getId() == COADlg::MSC_SUBORGTYPE )
        {
            retrieveValue( COADlg::MSC_SUBORGTYPE );   // Set Value
            pCOAElem->setChoiceList();

            m_gridWindow.SetStyleRange( CGXRange( i + 1,2), CGXStyle()
										.SetControl(GX_IDS_CTRL_CBS_DROPDOWNLIST)
                                        .SetChoiceList( pCOAElem->getChoiceList() )
										.SetValue( pCOAElem->getValue() )
										.SetEnabled( true )
										.SetReadOnly( false )
                                        .SetVerticalAlignment(DT_VCENTER));
            break;
        }
	}
}
//******************************************************************************
void COADlg::validateSubOrgType()
{
    MFAccount* pMFAccount = dynamic_cast<COAProcess*>(getParent() )->getMFAccount();
	if( pMFAccount )
	{
		bool bValid = pMFAccount->validateSubOrgType( getParent()->getDataGroupId() ); 
		if ( bValid)
		{
		   CString cstrMsg;
		   cstrMsg.LoadString(TXT_ACT_HAS_ERISA_PROHIBITED_FUND);
		   AfxMessageBox( cstrMsg, MB_ICONWARNING );
		}	
	}		
	return;
}
//******************************************************************************
bool COADlg::setRemoveUnwantedChars(CString &value)
{
	value.Replace(_T("\r"), _T(" ")); // replace all <cr> with space
	value.Replace(_T("\n"), _T(" ")); // replace all <lf> with space
	value.Replace(_T("\f"), _T(" ")); // replace all <ff> with space
	value.Replace(_T("\t"), _T(" ")); // replace all <tab> with space
	value.Replace(_T("\""), _T(" ")); // replace all <double quote/inverted commas> with space

	return setCOAField( IFASTBP_PROC::COA_MFACCOUNT_CBO, ifds::AdditionalStopReason, value );	
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/COADlg.cpp-arc  $
 * 
 * History:
 * 07-Mar-2014 Supareuk Sukjaitham P0221545 FN01 DFT0030180 T54906
 *             - Readonly MgmtFeePayOptino field when MgmtFeePayOptOvd is not blank
 *             - Recheck with the new task T54906 to remove logic
 *
 *    Rev 1.243   Jul 24 2012 19:16:38   dchatcha
 * P0179630 FN01 FATCA Project - Acct Ownership Allocation
 * 
 *    Rev 1.242   Jul 12 2012 10:41:00   dchatcha
 * P0191601 FN03 - Manual T3/RL 16/NR4 Slip for Taxable Trusts.
 * 
 *    Rev 1.241   Jul 02 2012 12:20:52   wutipong
 * IN2972829 - TFSA accounts - Government Filing and Amendment
 * 
 *    Rev 1.240   May 14 2012 09:33:48   kitticha
 * P0186477 FN06 - T5 Processing.
 * 
 *    Rev 1.239   May 14 2012 04:25:56   panatcha
 * P0186486_FN16_Misc. Enhancements_Stop Adjustment Date
 * 
 *    Rev 1.238   Apr 16 2012 17:28:34   if991250
 * CPF Account Setup
 * 
 *    Rev 1.237   Feb 21 2012 17:15:48   if991250
 * Mat Sweep Instructions - reset on modless set focus and init
 * 
 *    Rev 1.236   Feb 08 2012 04:53:24   panatcha
 * DesktopWeb conversion
 * 
 *    Rev 1.235   Jan 26 2012 06:10:32   panatcha
 * IN2747587 - guifn 223 - TFSA Amendment
 * 
 *    Rev 1.234   Jan 25 2012 09:01:58   panatcha
 * IN2747587 - guifn 223 - TFSA Amendment
 * 
 *    Rev 1.233   Jan 16 2012 13:43:50   wp040027
 * P0188394_Performance Fees - ERISA Functionality
 * 
 *    Rev 1.232   Dec 21 2011 15:20:00   jankovii
 * P0186477 FN03- GIA Maturity/Cash Sweep Instructions
 * 
 *    Rev 1.231   Dec 08 2011 14:23:12   jankovii
 * P0186477 FN03- GIA Maturity/Cash Sweep Instructions
 * 
 *    Rev 1.230   Nov 28 2011 09:21:36   jankovii
 * P0186477 FN03- GIA Maturity/Cash Sweep Instructions
 * 
 *    Rev 1.229   Nov 25 2011 15:57:42   wp040168
 * P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
 * 
 *    Rev 1.228   Nov 24 2011 15:49:48   wp040168
 * P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
 * 
 *    Rev 1.227   Nov 21 2011 18:41:18   wp040168
 * P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
 * 
 *    Rev 1.226   Nov 19 2011 01:25:12   wp040143
 * P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
 * 
 *    Rev 1.225   Nov 15 2011 15:36:40   popescu
 * P0186477 FN03- GIA Maturity/Cash Sweep Instructions
 * 
 *    Rev 1.224   Nov 15 2011 13:18:22   jankovii
 * P0186477 FN03- GIA Maturity/Cash Sweep Instructions
 * 
 *    Rev 1.223   Oct 25 2011 15:51:42   dchatcha
 * IN# 2646991 - P0181953- Amendment not generated when  using clone functionality.
 * 
 *    Rev 1.222   Oct 07 2011 14:48:30   dchatcha
 * P0191592 FN01 - NSCC Social Code
 * 
 *    Rev 1.221   Sep 16 2011 12:12:58   dchatcha
 * P0181953 FN01 - TFSA Amendment - Remove specific interprocess parameter passing.
 * 
 *    Rev 1.220   Jul 18 2011 20:14:24   dchatcha
 * P0180786 FN01 - TFSA Estate and Right of Rescission Tax Reporting.
 * 
 *    Rev 1.219   Jul 12 2011 12:17:36   dchatcha
 * P0181953 FN01 - TFSA Amendment- integration test, wrong container.....
 * 
 *    Rev 1.218   Jul 11 2011 07:47:58   dchatcha
 * P0181953 FN01 - TFSA Amendment- integration test.
 * 
 *    Rev 1.217   Jul 07 2011 18:48:40   dchatcha
 * P0181953 FN01 - TFSA Amendment.
 * 
 *    Rev 1.216   Apr 20 2011 22:58:34   kitticha
 * PETP0183105 FN01 - Unclaimed Property for Alberta.
 * 
 *    Rev 1.215   Apr 15 2011 09:46:10   popescu
 * Restore 1.213 - since 1.214 is only a temporary fix to show the old FundLimitation screen for non-GT clients
 * 
 *    Rev 1.213   Feb 01 2011 09:56:20   dchatcha
 * Add one more screen parameter for 'Fund Limit Override' screen
 * 
 *    Rev 1.212   Feb 01 2011 09:50:32   dchatcha
 * P0179308 FN01 - Multi Manager Subscription and Direct Debit Payment.
 * 
 *    Rev 1.211   Nov 23 2010 01:36:46   dchatcha
 * PET0165541 FN03 - QESI Phase3, allow screen pop-up for authorized user.
 * 
 *    Rev 1.210   Nov 16 2010 04:43:20   dchatcha
 * PET0165541 FN03 - QESI Phase3. still missing screen name parameter, should be shame!
 * 
 *    Rev 1.209   Nov 16 2010 04:36:42   dchatcha
 * PET0165541 FN03 - QESI Phase3. Web screen calling parmeter is not correct and missing break statement.
 * 
 *    Rev 1.208   Nov 08 2010 11:03:06   kitticha
 * IN#2313085 - P0173756FN02- Don't bust the rules - Add Button not disabled.
 * 
 *    Rev 1.207   Nov 04 2010 11:17:30   kitticha
 * IN#2313085 - P0173756FN02- Don't bust the rules - Add Button not disabled.
 * 
 *    Rev 1.206   Oct 29 2010 07:13:06   dchatcha
 * PET0165541 FN03 - QESI Phase3.
 * 
 *    Rev 1.205   Sep 30 2010 10:09:20   jankovii
 * PET168727 FN22 - Trailer Fee Setup
 * 
 *    Rev 1.204   Sep 17 2010 06:31:36   kitticha
 * PETP0173756 FN02 Don't Bust the Rules.
 * 
 *    Rev 1.203   Jun 15 2010 11:27:56   jankovii
 * PET165541_FN09_QESI Phase 2
 * 
 *    Rev 1.202   Mar 29 2010 03:13:06   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU, not display value.
 * 
 *    Rev 1.201   Mar 26 2010 13:39:28   popescu
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU - the checks should be agains res2 client
 * 
 *    Rev 1.200   Mar 26 2010 09:10:32   dchatcha
 * PET165541_FN01_QESI - RESP Gap_Dsk_NASU
 * 
 *    Rev 1.199   Jan 28 2010 17:06:22   jankovii
 * PET165541 FN01 - QESI - RESP Gap.
 * 
 *    Rev 1.198   Jul 16 2009 18:53:36   dchatcha
 * PET156681 FN14 H36 Investor Authorization, Integration issues.
 * 
 *    Rev 1.197   Jul 09 2009 13:08:34   dchatcha
 * PET156681 FN14 H36 Investor Authorization.
 * 
 *    Rev 1.196   Apr 24 2009 11:37:18   jankovii
 * PET 157825 FN18 - MF and MFR Day 2.
 * 
 *    Rev 1.195   Apr 07 2009 10:31:06   jankovii
 * PET 157825 FN18 - MF and MFR Day 2.
 * 
 *    Rev 1.194   Dec 24 2008 10:15:14   jankovii
 * PET 142007 FN03 TFSA Phase 2.
 * 
 *    Rev 1.193   Dec 08 2008 11:09:12   jankovii
 * Sync up: IN 1499980 - KYC-manually update ""Deceased(System)" to N/A, some stop flag s/b No
 * 
 *    Rev 1.192   Dec 02 2008 13:07:12   jankovii
 * Sync up: IN 1502585 - Cheque Inquiry - View 21
 * 
 *    Rev 1.191   Nov 28 2008 13:48:36   jankovii
 * PET 142196 FN01 Federal Restricted LIF and LIRA.
 * 
 *    Rev 1.190   Nov 25 2008 11:32:02   jankovii
 * PET 142196 FN01 Federal Restricted LIF and LIRA.
 * 
 *    Rev 1.189   Nov 05 2008 14:39:40   jankovii
 * PET 5517 FN71 Unclaimed Property Phase 2.
 * 
 *    Rev 1.188   Sep 26 2008 10:52:40   jankovii
 * IN 1423029 - Stop flags should be read only if Stop reason is set to Missing KYC
 * 
 *    Rev 1.187   Sep 18 2008 10:21:54   jankovii
 * IN 1417689 - security of KYC document update and stop reason update not working.
 * 
 *    Rev 1.186   17 Sep 2008 14:56:56   kovacsro
 * IN#1414186 - show unlocking amount for TaxTypes C and U
 * 
 *    Rev 1.185   28 Aug 2008 11:43:40   kovacsro
 * PET142196FN01 Federal LockedIn RRSP - short term solution
 * 
 *    Rev 1.184   Aug 01 2008 11:48:44   jankovii
 * Put code back.
 * 
 *    Rev 1.183   Jul 30 2008 16:32:40   jankovii
 * Commente out code for Teresa's testing.
 * 
 *    Rev 1.182   Jul 25 2008 14:31:52   jankovii
 * PET 59888 - AML Enhancement.
 * 
 *    Rev 1.181   Jul 16 2008 10:24:34   jankovii
 * PET 59888 - AML Enhancemement.
 * 
 *    Rev 1.180   Jun 23 2008 14:39:38   jankovii
 * PET 59888 FN01 - AML Enhancement.
 * 
 *    Rev 1.179   06 May 2008 09:58:18   kovacsro
 * PET2255-FN47 New LIF - prepend the tax type to 'Gain/Loss'
 * 
 *    Rev 1.178   05 May 2008 16:33:34   kovacsro
 * PET2255-FN47 - Disabled Gain/Loss for NASU
 * 
 *    Rev 1.177   05 May 2008 14:51:20   kovacsro
 * PET2255-FN47 New LIF - moved 'Gain/Loss' from RIF screen into COA
 * 
 *    Rev 1.176   Apr 16 2008 18:35:44   daechach
 * PET2385 FN02&07 - Modified code regarding code review.
 * 
 *    Rev 1.175   Mar 11 2008 19:55:06   daechach
 * PET2385FN02&07 - Account Level Settlement Periods and Currency Holiday - Check in for Build.
 * 
 *    Rev 1.174   03 Jan 2008 13:22:42   kovacsro
 * IN#1065012 check in for Winnie (read ACCOUNT_DETAIL for AFFLUENT read permission, rather than AFFLUENT)
 * 
 *    Rev 1.173   06 Dec 2007 15:20:20   popescu
 * Incident 1088629 - read the ACL set-up for the web pages URL instead of the using the xml configuration file.
 * 
 *    Rev 1.172   06 Dec 2007 09:30:06   kovacsro
 * IN#1039915 - sync-up from rel82 branch
 * 
 *    Rev 1.171   Dec 06 2007 19:42:08   smithdav
 * PET1200 FN02 - Dividend Processing enhancement.
 * 
 *    Rev 1.170   Dec 05 2007 15:04:02   jankovii
 * IN 1098016 - Desktop Account Level AMS screen 'Status' Field.
 * 
 *    Rev 1.169   31 Oct 2007 11:32:38   kovacsro
 * IN#1039915 - Affluent field controlled now by AFFLUENT(158) user access code
 * 
 *    Rev 1.168   29 Oct 2007 15:56:28   kovacsro
 * IN#1039915 - added one more business rule (cannot set to 'Not applicable')
 * 
 *    Rev 1.167   26 Oct 2007 16:32:38   kovacsro
 * IN# 1039915 - added validation for Affluent field
 * 
 *    Rev 1.166   12 Oct 2007 10:08:46   popescu
 * Incident 1003180 - Cosmetic-Error message for AMS setup on inactive account
 * 
 *    Rev 1.165   Oct 08 2007 12:17:50   smithdav
 * IN  1005517,1020252 - LRSP logic
 * 
 *    Rev 1.164   11 Sep 2007 10:52:44   popescu
 * Incident 1003183 - disabled stop AMS rebalancing
 * 
 *    Rev 1.163   Sep 07 2007 14:14:40   smithdav
 * IN 978610 - add logic to look t the AcctAMSExist flag on the account ro COA display.
 * 
 *    Rev 1.162   Aug 14 2007 17:45:46   popescu
 * Incident# 962948 - made the afluent flag available in the COA dialog box
 * 
 *    Rev 1.161   Aug 08 2007 17:49:28   kovacsro
 * PET 2360 FN 29 - RESP
 * 
 *    Rev 1.160   Jan 24 2007 16:52:38   ZHANGCEL
 * PET2306 FN02 -- Add logic for the enhancement
 * 
 *    Rev 1.159   Dec 06 2006 14:57:06   fengyong
 * Incident #763433 - refresh account detail after ok on fund limitation page
 * 
 *    Rev 1.158   Oct 30 2006 16:14:46   fengyong
 * PET2185 FN02 - add field FundLimitOvrdExist
 * 
 *    Rev 1.157   Oct 19 2006 09:37:08   fengyong
 * Temp check in for PET 2185 - Fund limitation
 * 
 *    Rev 1.156   Sep 20 2006 16:35:58   popescu
 * STP 2217/13 fixes
 * 
 *    Rev 1.155   Sep 05 2006 11:14:36   popescu
 * PET2212 FN10 -- Add logic for new row Consolidation type
 * 
 *    Rev 1.154   Aug 31 2006 13:48:16   ZHANGCEL
 * PET2212 FN10 -- Add logic for new row Consolidation type
 * 
 *    Rev 1.153   Feb 23 2006 11:38:00   zhengcon
 * PET 2017_FN02--Partnerworld MT515 and Acct Level Default: remove temp Code
 * 
 *    Rev 1.152   Feb 21 2006 10:44:06   zhengcon
 * PET 2017_FN02--Partnerworld MT515 and Acct Level Default
 * 
 *    Rev 1.151   Jan 26 2006 12:04:42   popescu
 * Disable the COA button on the AccInfo screen if this is invoked from the  COA dialog
 * 
 *    Rev 1.150   Nov 02 2005 12:16:18   porteanm
 * Incident 440591 - For a Seg/Cot product, don't allow a PAC/SWP/SV/AT during NASU.
 * 
 *    Rev 1.149   Sep 15 2005 15:11:02   popescu
 * Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
 * 
 *    Rev 1.148   Jul 27 2005 17:33:38   ZHANGCEL
 * PET1141 - FN05 -- Fix problem which cause error incorrectly showing up.
 * 
 *    Rev 1.147   Jul 22 2005 17:11:00   Yingbaol
 * PET1141,FN05:code clean up
 * 
 *    Rev 1.146   Jul 22 2005 16:18:48   Yingbaol
 * PET1141,FN05: when user change clearingFirm, change ParticipantID accordingly.
 * 
 *    Rev 1.145   Jul 15 2005 13:52:38   ZHANGCEL
 * minor change
 * 
 *    Rev 1.144   Jul 07 2005 16:12:42   ZHANGCEL
 * PET1141-FN05 -- Code clean up and add a new function validateClearingFirm()
 * 
 *    Rev 1.142   Jul 06 2005 11:02:18   ZHANGCEL
 * PET1141 - FN05 -- NSCC Broker enhancement
 * 
 *    Rev 1.141   Jun 17 2005 19:36:12   popescu
 * IN 243458 - replace Fee_Waived with Account_Detail.
 * 
 *    Rev 1.140   Jun 17 2005 17:42:10   AGUILAAM
 * IN 243458 - replace Fee_Waived with Account_Detail.
 * 
 *    Rev 1.139   Apr 21 2005 10:27:32   ZHANGCEL
 * Incident #292340 -- Add a new ExemptAuthoriztion should be allowed during the NASU flow
 * 
 *    Rev 1.138   Mar 04 2005 16:44:38   georgeet
 * PET1171 FN01 - EU Savings Directive Tax Exemption.  Modified the existing screen to include four new fields with appropriate business logic.
 * 
 *    Rev 1.137   Dec 21 2004 17:31:40   aguilaam
 * PTS 10037090 - add Market Mailing under Misc/COA Screen
 * 
 *    Rev 1.136   Dec 20 2004 14:13:06   hernando
 * PTS10036234 - Modified Clearing ID check in PreOk.
 * 
 *    Rev 1.135   Dec 03 2004 10:56:30   vadeanum
 * PET1117 FN08 - Shareholder Fund Broker support.
 * 
 *    Rev 1.134   Nov 11 2004 16:29:26   vadeanum
 * PET1117 FN08 - Shareholder Fund Broker support.
 * 
 *    Rev 1.133   Nov 04 2004 10:50:04   VADEANUM
 * PET1117 FN21 - Settlement Instr, renamed from SettLoc to SettlementInstr
 * 
 *    Rev 1.132   Oct 20 2004 18:11:26   YINGBAOL
 * PTS10034800: change display issue for FeeModel at account level.
 * 
 *    Rev 1.131   Oct 20 2004 18:00:14   VADEANUM
 * PET1117 FN21 - Backed out - Renamed from SettleLoc to SettlementInstr
 * 
 *    Rev 1.130   Oct 13 2004 16:18:38   VADEANUM
 * PET1117 FN21 - Renamed from SettleLoc to SettlementInstr
 * 
 *    Rev 1.129   Sep 16 2004 17:16:48   YINGBAOL
 * PET1124:fix diplay stop flag issue
 * 
 *    Rev 1.128   Aug 31 2004 17:25:56   FENGYONG
 * change field name
 * 
 *    Rev 1.127   Aug 11 2004 18:41:32   FENGYONG
 * PET 1117 FN5 syncup after get resource
 * 
 *    Rev 1.126   Aug 10 2004 11:27:52   FENGYONG
 * PET 1117 FN5 - Client Condition Fee
 * 
 *    Rev 1.125   Aug 06 2004 17:51:22   ZHANGCEL
 * PET 1082 FNrlc - Tax Exempt Authorization support
 * 
 *    Rev 1.124   Jul 29 2004 16:03:26   YINGBAOL
 * PET1124:Add Stop RedemptionSettlement  flag
 * 
 *    Rev 1.123   Jul 29 2004 10:07:48   VADEANUM
 * PET1117 FN01 - Shareholder Static Data support.
 * 
 *    Rev 1.122   Jul 28 2004 14:58:42   ZHANGCEL
 * PET1082 FNrlc -- New Quebec withholding Tax
 * 
 *    Rev 1.121   Jul 26 2004 10:43:24   VADEANUM
 * PET1117 FN01 - Shareholder Static Data support.
 * 
 *    Rev 1.120   21 Jun 2004 14:54:34   YINGBAOL
 * PTS10031481:change permissionIF for foreign content screen.
 * 
 *    Rev 1.119   May 26 2004 18:15:52   YINGBAOL
 * PET985: Add read permission check for foreign content.
 * 
 *    Rev 1.118   May 12 2004 11:54:56   HERNANDO
 * PTS10029732 - Changed the getErrors call in PreOk to retrieve for all conditions in the CBO.
 * 
 *    Rev 1.117   Apr 26 2004 13:33:40   VADEANUM
 * PET985 FN01 - Foreign Content - work in progress.
 * 
 *    Rev 1.116   Apr 07 2004 18:40:42   FENGYONG
 * PET944FN01 Rel56.1 NSCC Broker
 * 
 *    Rev 1.115   Apr 05 2004 17:37:54   FENGYONG
 * PET944FN01 release 56.1 NSCC Broker
 * 
 *    Rev 1.114   Mar 04 2004 11:10:18   HERNANDO
 * PET965 FN11 - Switched Historical Account to Historical Info.
 * 
 *    Rev 1.113   Feb 24 2004 11:09:50   VADEANUM
 * PTS10027338 - Replaced Charge WD Fee fucntion with new one for Fees Waived.
 * 
 *    Rev 1.112   Feb 18 2004 16:15:18   YINGBAOL
 * PTS10027208: syc. 1.110.1.0 to R56
 * 
 *    Rev 1.111   Feb 18 2004 16:06:18   HERNANDO
 * PET965 FN11 - Added OnBtnHistorical.
 * 
 *    Rev 1.110   Jan 13 2004 09:05:46   HERNANDO
 * PTS 10025863 - On OK, display warning message if Clearing ID is defined and Settlement Location is 'No'.
 * 
 *    Rev 1.109   Dec 11 2003 11:23:52   linmay
 * modified retrievevalue() for PTS Ticket #10024900
 * 
 *    Rev 1.108   Dec 10 2003 15:42:36   HERNANDO
 * PET892 FN1 - Updates the Settlement Location after the Grid has been redisplayed.
 * 
 *    Rev 1.107   Nov 27 2003 10:34:40   HERNANDO
 * PET892 FN1 - Added Settlement Location. 
 * 
 *    Rev 1.106   Oct 23 2003 18:02:06   FENGYONG
 * PET809 FN08 Direct trading enhancement
 * 
 *    Rev 1.105   Oct 19 2003 18:35:44   popescu
 * CIBC PET 809, FN 13
 * 
 *    Rev 1.104   Oct 16 2003 12:34:48   FENGYONG
 * PET809 FN08 Direct Trading enhancement
 * 
 *    Rev 1.103   Sep 10 2003 16:18:50   HERNANDO
 * Sync'd up to 1.99.1.1; PTS 10019044.
 * 
 *    Rev 1.102   Sep 03 2003 17:16:08   popescu
 * fixes regarding calling the allocation screen, seems that more places that originally thought are using the allocation screen
 * 
 *    Rev 1.101   Aug 21 2003 09:22:58   linmay
 * added TelFaxAgreement field
 * 
 *    Rev 1.100   Jul 22 2003 10:59:24   VADEANUM
 * PET 809 F05 - Fee Waived security support.
 * 
 *    Rev 1.99   May 23 2003 12:16:06   popescu
 * Fixed COA Banking launching crash
 * 
 *    Rev 1.98   May 23 2003 10:04:32   popescu
 * Part of bank instructions cleaning up process, moved the bank types into the ifastids project
 * 
 *    Rev 1.97   May 13 2003 16:09:56   HERNANDO
 * PET792.FN04.3 - Added StopAMSRebalancing.
 * 
 *    Rev 1.96   May 02 2003 16:23:34   sanchez
 * In retrieveValue() read ChargeERFee and ChargeSTTRFee instead of ShortTermTRFeeElig amd EarlyPWFeeElig fields
 * 
 *    Rev 1.95.1.1   May 02 2003 16:11:48   sanchez
 * In retrieveValue() read ChargeERFee and ChargeSTTRFee instead of ShortTermTRFeeElig amd EarlyPWFeeElig fields
 * 
 *    Rev 1.95.1.0   Apr 30 2003 11:07:28   sanchez
 * No user access function security for ShortTermTRFeeElig amd EarlyPWFeeElig
 * 
 *    Rev 1.95   Apr 15 2003 12:13:14   sanchez
 * Sync up with version 1.87.10.  Also, for field "Fee Waived remove check for NASU when setting the value for field.
 * 
 *    Rev 1.94   Apr 07 2003 16:15:54   sanchez
 * Use BF::NullContainerId when getting EarlyPWFeeElig
 * and ShortTermTRFeeElig fields.
 * 
 *    Rev 1.93   Apr 04 2003 13:23:56   sanchez
 * setCOAFields for ChargeERFee and ChargeSTTRFee
 * 
 *    Rev 1.92   Apr 02 2003 11:50:02   sanchez
 * Changed IFASTBP_PROC::COA_PROC_GEN_LIST to BF::NullContainerId.  Original (preconversion) code specified that this constant was 0.
 * 
 *    Rev 1.91   Mar 31 2003 16:18:34   sanchez
 * Logic for new fields:EarlyPWFeeElig and ShortTermTRFeeElig
 * 
 *    Rev 1.90   Mar 21 2003 18:34:26   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.89   Mar 14 2003 08:58:08   sanchez
 * Changes for Early Redemption Fee and Short Term Transfer Fee
 * 
 *    Rev 1.88   Feb 26 2003 11:45:54   linmay
 * clean up message
 * 
 *    Rev 1.87   Jan 29 2003 13:59:58   sanchez
 *  addCOARow for AMS only if AMS is an option      }
 * 
 *    Rev 1.86   Jan 25 2003 17:06:04   KOVACSRO
 * Added AccountCategory
 * 
 *    Rev 1.85   Jan 15 2003 16:55:26   sanchez
 * set account number field for shareholder family
 * 
 *    Rev 1.84   Jan 13 2003 18:04:54   sanchez
 * Changes for Shareholer
 * 
 *    Rev 1.83   Jan 08 2003 12:21:04   sanchez
 * Target Asset Mix implementation.  Added check for AMSROCode.
 * 
 *    Rev 1.82   Dec 30 2002 10:14:54   sanchez
 * ifastgui:  COADlg.cpp
 *   -OnInitDialog() add option MgmtFeePayOption category of the COA dialog
 *   -RetrieveValue() when the cell id is FEE_MGMT_FEE_PAY_OPTN ask MFAccount for the 
 *    MgmtFeePayOptionSet value
 *   -BFFieldId COADlg::getSubstitutionId(COA_ENTRY_ID lId)
 *   -added      case FEE_MGMT_FEE_PAY_OPTN:
 * 
 *    Rev 1.81   Dec 06 2002 10:59:54   YINGBAOL
 * PRIF Enhancement
 * 
 *    Rev 1.80   Nov 26 2002 17:38:00   HERNANDO
 * Changed AMS Acct Lvl implementation.  Displays yes or no depending on whether value exists.
 * 
 *    Rev 1.79   Nov 22 2002 15:28:02   KOVACSRO
 * Added retrieveHypoRedValue( ). changed logic for Hypo redemption : if HypoRed is not applicable, show No and disable.
 * 
 *    Rev 1.78   Nov 21 2002 13:12:34   KOVACSRO
 * Added HypoRed.
 * 
 *    Rev 1.77   Nov 18 2002 14:02:34   PURDYECH
 * AMS_GLOBAL becomes AMS_ACCTLVL
 * 
 *    Rev 1.76   Nov 06 2002 16:59:06   HERNANDO
 * Added AMS Option.
 * 
 *    Rev 1.75   Oct 09 2002 23:55:34   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.74   Aug 29 2002 12:57:18   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.73   Jul 11 2002 16:54:08   HSUCHIN
 * added account level split commission option
 * 
 *    Rev 1.72   Jul 05 2002 10:41:06   PURDYECH
 * Include file cleanup.
 * 
 *    Rev 1.71   Jun 15 2002 12:45:18   HSUCHIN
 * removed hardcoded PensionJurisexists
 * 
 *    Rev 1.70   Jun 14 2002 17:33:06   ZHANGCEL
 * Added logic to pop up a message window to warn user of RRIF screen setup
 * 
 *    Rev 1.69   Jun 11 2002 21:33:12   HSUCHIN
 * pension juris now only appears for certain tax types.   Value is still hardcode to Y until view 4
 * 
 *    Rev 1.68   Jun 10 2002 17:05:10   KOVACSRO
 * Support for Field substitution list.
 * 
 *    Rev 1.67   07 Jun 2002 16:58:22   HERNANDO
 * Modified inclusion of Account Review based on ReviewDateFlag.
 * 
 *    Rev 1.66   Jun 07 2002 15:23:50   KOVACSRO
 * BankCharges and EFT Consolidation.
 * 
 *    Rev 1.65   31 May 2002 16:33:18   HERNANDO
 * Added Account Review.
 * 
 *    Rev 1.64   May 31 2002 15:39:44   HSUCHIN
 * added pension info
 * 
 *    Rev 1.63   Apr 26 2002 15:39:16   YINGBAOL
 * Pass TransType for SavingPlan
 * 
 *    Rev 1.62   Apr 25 2002 13:48:14   YINGBAOL
 * fix ApplyPST issue
 * 
 *    Rev 1.61.1.0   Apr 25 2002 13:46:10   YINGBAOL
 * Fix AppyPST Issue
 * 
 *    Rev 1.61   27 Mar 2002 20:01:02   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.60   20 Mar 2002 17:14:20   HSUCHIN
 * bug fix to accruals dialog
 * 
 *    Rev 1.59   Mar 18 2002 14:35:22   YINGBAOL
 * add PST Exempty
 * 
 *    Rev 1.58   Feb 26 2002 15:22:08   YINGBAOL
 * add Fee Parameter
 * 
 *    Rev 1.57   Feb 04 2002 15:47:54   JANKAREN
 * Added GSTExempt and syn up 1.55
 * 
 *    Rev 1.56   Jan 28 2002 11:27:30   YINGBAOL
 * HLLAPI Change
 *  
 *    Rev 1.55   Jan 25 2002 16:28:48   ZHANGCEL
 * Let COA Screen list containing "Systematic Transfer"
 *	
 *    Rev 1.54   19 Dec 2001 13:04:20   KOVACSRO
 * Removed AT for Lux market.
 * 
 *    Rev 1.53   20 Nov 2001 11:12:00   HSUCHIN
 * sync up with 1.51.1.0
 * 
 *    Rev 1.52   Nov 07 2001 17:57:24   ZHANGCEL
 * Haspermission changes
 * 
 *    Rev 1.51   Oct 31 2001 13:51:20   ZHANGCEL
 * Fixed the crash on opening YTD Contributions from the COA window in the NASU flow
 * 
 *    Rev 1.50   Oct 25 2001 10:55:54   YINGBAOL
 * small fix
 * 
 *    Rev 1.49   24 Oct 2001 15:11:04   HSUCHIN
 * undo last changes.  YTD now only shows up for TaxType 1 with permission check
 * 
 *    Rev 1.48   22 Oct 2001 13:09:14   HSUCHIN
 * change YTD attribute to be displayed for TaxType 1,3,4,C,H
 * 
 *    Rev 1.47   19 Oct 2001 11:17:42   HSUCHIN
 * added permission check for YTD
 * 
 *    Rev 1.46   Sep 19 2001 14:55:42   JANKAREN
 * convert taxtype to upper case
 * 
 *    Rev 1.45   Sep 19 2001 14:43:58   JANKAREN
 * Added permission for As Pension
 * 
 *    Rev 1.44   19 Sep 2001 10:27:48   KOVACSRO
 * Added ESoP.
 * 
 *    Rev 1.43   Aug 23 2001 13:25:04   JANKAREN
 * Added As Pension Plan
 * 
 *    Rev 1.42   Aug 22 2001 10:45:04   YINGBAOL
 * sync. up version 1.40.1.0
 * 
 *    Rev 1.41   18 Aug 2001 11:07:24   HSUCHIN
 * added YTD to Screen selection
 * 
 *    Rev 1.40   15 Aug 2001 17:19:24   WINNIE
 * sycn back to truck
 * 
 *    Rev 1.39.1.0   15 Aug 2001 17:01:24   HSUCHIN
 * removed savings plan from all markets except lux
 * 
 *    Rev 1.39   05 Aug 2001 15:28:58   HSUCHIN
 * removed External RRSP from COA List
 * 
 *    Rev 1.38   Aug 02 2001 22:08:06   YINGBAOL
 * fix stop flag for Japan
 * 
 *    Rev 1.37   Jul 16 2001 18:51:40   OLTEANCR
 * added access to multicontract screen
 * 
 *    Rev 1.36   Jul 09 2001 11:55:06   ZHANGCEL
 * Fixed crash when application added new row for GuarateeInfo.
 * 
 *    Rev 1.35   14 Jun 2001 11:58:24   SMITHDAV
 * Removed references to UserAccessProcess.
 * 
 *    Rev 1.34   05 Jun 2001 16:06:44   YINGZ
 * for others to compile
 * 
 *    Rev 1.33   Jun 05 2001 14:11:26   ZHANGCEL
 * Session management restructuring
 * 
 *    Rev 1.32   Jun 04 2001 10:50:40   ZHANGCEL
 * Added logic for the RESP, Contract, Guarantee and RRIP screen showing up under the Screen column.
 * 
 *    Rev 1.31   03 May 2001 14:07:30   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.30   Mar 30 2001 18:12:04   DINACORN
 * Used DSTCommonFunctions MARKET_IDS constants
 * 
 *    Rev 1.29   22 Mar 2001 10:18:54   BUZILAMI
 * fix crash when launching bank
 * 
 *    Rev 1.28   Mar 20 2001 13:13:58   YINGZ
 * link to new bank screen
 * 
 *    Rev 1.27   Mar 20 2001 11:32:00   YINGZ
 * fix id problem
 * 
 *    Rev 1.26   16 Mar 2001 16:26:04   BUZILAMI
 * fix storing the grid cell value on Ok
 * 
 *    Rev 1.25   Feb 16 2001 15:27:46   YINGBAOL
 * implement save and load stingery settings and put some hard copy string into DD
 * 
 *    Rev 1.24   Feb 09 2001 10:26:48   YINGBAOL
 * M3 sync.
 * 
 *    Rev 1.23   Jan 18 2001 14:20:20   KOVACSRO
 * Disabled RRIF_LIF... for NASU.
 * 
 *    Rev 1.22   Dec 18 2000 11:43:18   WINNIE
 * RRIF not for External RRIF account (taxtype == 5)
 * 
 *    Rev 1.21   Dec 15 2000 16:52:38   WINNIE
 * change AT to Automatic_Transfer
 * 
 *    Rev 1.20   Dec 15 2000 14:52:04   ZHANGCEL
 * Remove the comment for SetWarningConfirm( false )
 * 
 *    Rev 1.19   Dec 15 2000 14:46:34   ZHANGCEL
 * Fixed the Sysematic Tansfer, RRIF_LIF_LRIF value showing problems
 * 
 *    Rev 1.18   Nov 22 2000 17:18:16   HUANGSHA
 * surpress the Waring Messagebox popup
 * 
 *    Rev 1.17   Nov 08 2000 16:58:16   ZHANGCEL
 * Added logic for checking ContractExist
 * 
 *    Rev 1.16   Oct 27 2000 17:34:26   ZHANGCEL
 * Fixed bugs for  ContractInfo, SystematicTransfer, SupEmpConf and Beneficial. 
 * 
 *    Rev 1.15   Oct 18 2000 13:57:32   ZHANGCEL
 * Fixed the Destribution, Cheque, ACB and InterAccrual value problem
 * 
 *    Rev 1.14   Oct 05 2000 13:42:56   YINGBAOL
 * check PlanType instead of TaxTye and Permistion for RRIF_LIF_LRIF screen
 * 
 *    Rev 1.13   Sep 25 2000 11:25:54   ZHANGCEL
 * Bug fixed
 * 
 *    Rev 1.12   Sep 22 2000 14:59:42   ZHANGCEL
 * Bug fixed
 * 
 *    Rev 1.11   Sep 20 2000 14:23:56   ZHANGCEL
 * Debug
 * 
 *    Rev 1.10   Aug 04 2000 09:45:10   PETOLESC
 * Added FRREB stop field and RRIF screen.
 * 
 *    Rev 1.9   Jun 23 2000 16:17:00   BUZILA
 * changed to launch Systematics for AT
 * 
 *    Rev 1.8   Apr 05 2000 10:49:32   DT24433
 * changed to use hasPermission, removed unused worksession variable
 * 
 *    Rev 1.7   Apr 03 2000 10:11:00   YINGZ
 * code sync
 * 
 *    Rev 1.6   Mar 31 2000 13:24:14   YINGZ
 * code sync
 * 
 *    Rev 1.5   Mar 29 2000 16:50:44   YINGZ
 * code sync
 * 
 *    Rev 1.4   Mar 10 2000 12:00:46   YINGZ
 * change labels
 * 
 *    Rev 1.3   Mar 10 2000 11:42:42   YINGZ
 * disable SCR_CERTIF_ID in nasu flow
 * 
 *    Rev 1.2   Feb 28 2000 14:50:10   DT24433
 * removed Cancel
 * 
 *    Rev 1.1   Feb 17 2000 15:25:10   YINGZ
 * no hllapi in nasu for escow
 * 
 *    Rev 1.0   Feb 15 2000 11:01:10   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.28   Feb 09 2000 12:10:20   HUANGSHA
 * Added TransType for invoking the systematic screen
 * 
 *    Rev 1.27   Feb 04 2000 10:59:04   VASILEAD
 * Added HLLAPI
 * 
 *    Rev 1.26   Feb 01 2000 13:06:52   BUZILA
 * some fixes
 * 
 *    Rev 1.25   Jan 31 2000 14:27:16   BUZILA
 * hllapi changes
 * 
 *    Rev 1.24   Jan 28 2000 14:15:12   VASILEAD
 * fix expand
 * 
 *    Rev 1.23   Jan 24 2000 10:13:50   BUZILA
 * disabling HLLAPI for nasu
 * 
 *    Rev 1.22   Jan 22 2000 15:18:58   BUZILA
 * fixes
 * 
 *    Rev 1.21   Jan 21 2000 17:40:48   BUZILA
 * some fixes
 * 
 *    Rev 1.20   Jan 19 2000 10:10:54   BUZILA
 * bug fix
 * 
 *    Rev 1.19   Jan 11 2000 10:01:32   BUZILA
 * cosmetic changes
 * 
 *    Rev 1.18   Jan 11 2000 09:08:48   BUZILA
 * changed search algorithm and collapse/expand button
 * 
 *    Rev 1.17   Dec 23 1999 15:20:40   BUZILA
 * changed launch to use symbols instead of strings
 * 
 *    Rev 1.16   Dec 23 1999 15:03:24   BUZILA
 * Allocations proc cmd  was changed to BPROC_ALLOCATIONS
 * 
 *    Rev 1.15   Dec 23 1999 14:14:00   BUZILA
 * added setCOAField
 * 
 *    Rev 1.14   Dec 22 1999 18:12:32   BUZILA
 * fix
 * 
 *    Rev 1.13   Dec 22 1999 18:01:50   BUZILA
 * changes due to COA flags movament
 * 
 *    Rev 1.12   Dec 10 1999 18:47:44   BUZILA
 * implemented collapse, search, filtering
 * 
 *    Rev 1.11   Nov 25 1999 15:42:14   BUZILA
 * added HLLAPI points
 * 
 *    Rev 1.10   Nov 25 1999 15:12:54   BUZILA
 * fixes
 * 
 *    Rev 1.9   Nov 20 1999 19:39:18   BUZILA
 * fixes
 * 
 *    Rev 1.8   Nov 15 1999 14:46:18   BUZILA
 * fix
 * 
 *    Rev 1.7   Aug 12 1999 15:40:46   BUZILA
 * ch
 * 
 *    Rev 1.6.1.0   Aug 12 1999 15:27:32   BUZILA
 * Branch for Increment 2
 * 
 *    Rev 1.6   Aug 05 1999 11:52:52   BUZILA
 * 1
 * 
 *    Rev 1.5   Jul 29 1999 17:41:06   BUZILA
 * 1
 * 
 *    Rev 1.4   Jul 28 1999 12:03:40   BUZILA
 * moved gxall.h include at dialog level
 * 
 *    Rev 1.3   Jul 27 1999 16:06:20   BUZILA
 * Increment M2
 * 
 *    Rev 1.2   Jul 20 1999 11:18:30   VASILEAD
 * New conditions update
 * 
 *    Rev 1.1   Jul 08 1999 10:04:48   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */



