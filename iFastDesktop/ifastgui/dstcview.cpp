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
//    Copyright 1997 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : DSTCView.cpp
// ^AUTHOR : Jerry Leenerts
// ^DATE   : 02/99
//
// ----------------------------------------------------------
//
// ^CLASS    : CDSTCView
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#include "stdafx.h"

#include "mfdstc.h"
#include "dstcview.h"
#include <htmlhelp.h>
#include <ifastcsi\csisession.h>
#include <ifastcsi\ifastcsi.h>

#include <bfawdi\bfawddata.hpp>
#include <bfawdi\bfawdinterface.hpp>
#include <bfawdi\bfawdkey.hpp>
#include <bfsessn\bfawdsession.hpp>

#include "accountdetailsdlg.h"
#include <ifastbp\accdetailsprocessincludes.h>
#include <ifastcbo\accountentityxref.hpp>
#include <ifastcbo\dstcusersession.hpp>
#include <ifastcbo\fundmasterlist.hpp>
#include <ifastcbo\funddetaillist.hpp>
#include <bfproc\bpsessiontags.h>
#include <bfproc\commanddispatcher.hpp>
#include <configmacro.h>
#include <configmanager.hpp>
#include "configurationconstants.h"
#include "discardmsgdlg.h"
#include <uibase\dstcdoc.h>
#include <ifastdbrkr\dstchost.hpp>
#include <ifastdbrkr\dstcsecurity.hpp>
#include "encorrmgr.hpp"
#include <ifastbp\fundinfoprocessincludes.h>
#include <ifastbp\fillsearchcriteriaprocessincludes.h>
#include <ifastbp\featuressearchprocessincludes.h>
#include "formsmgr.hpp"
#include <bfproc\genericinterfacecontainer.hpp>
#include <bfproc\abstractprocess.hpp>
#include <ifastcbo\dstcworksession.hpp>
#include <idistring.hpp>
#include "mainfrm.h"
#include "mfdstcsetup.hpp"
#include <ifastbp\nasuprocessincludes.h>
#include <ifastbp\remarksprocessincludes.h>
#include <ifastbp\searchprocessincludes.h>
#include <ifastbp\usersessionprocessincludes.h>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastawd\DSTCAWDSession.hpp>
#include <ifastcsi\CsiSession.h>
#include <BrowserLaunch.h>
#include "workeventagent.h"
#include "workevent.h"
#include <conditions\alliFastConditionHeaders.h>



// Dataset includes
#include <ifastdataimpl\dse_dstcglob_vw.hpp>

#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastbp\tradesprocessincludes.h>
#include <ifastcbo\mgmtco.hpp>
#include <ifastcbo\dstcglobalsession.hpp>
#include <direct.h>

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CLASS_IMPORT const I_CHAR* CMD_GUI_BUSINFO;
extern CLASS_IMPORT const I_CHAR* CMD_GUI_ACCOUNT_DETAILS;
extern CLASS_IMPORT const I_CHAR* CMD_GUI_LIST_SELECTION;
extern CLASS_IMPORT const I_CHAR* CMD_GUI_ENTITY_SEARCH;

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_NASU;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_REMARKS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_TRADES;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_IDCALLER;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_CLEANUP;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FUNDINFO;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_SEARCH;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ACC_DETAILS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_MANAGEMENT_COMPANY;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FILL_SEARCH_CRITERIA;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_USER_ACCESS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_TAXRATES;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FUNDCLASS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_SETTLEMENT;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_REPORT;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_REPORT_STATUS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_PROTECTED_FUND;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_MKT_INDEX_MASTER;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_MKT_INDEX_VALUES;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FEE_PARAMETER_SYSTEM;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_HISTORICAL_INFO_SRCH;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_TRADE_SEARCH;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_AMSBROKER;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_AMS_GLOBAL;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_MANUAL_DIVIDEND;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FEATURES_SEARCH;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_BANK_INSTRUCTIONS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_SETTLEMENT_INSTRUCTIONS_SYSLVL;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FEE_MODEL;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FUNDSPONSOR_FEE_MODEL;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FUNDGROUP;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FUND_BROKER;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_AGGREGATED_ORDER;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_MSG_SEARCH;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FILE_SEARCH;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_CANCELLATION_INSTR;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_CONFIRMATION;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_PAY_TO_ENTITY;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_PAYMENT_INSTRUCTIONS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_PAYMENT_SEARCH;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FUND_CLASS_LIMITATION;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_PAYMENT_BATCH;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_MANAGEMENT_FEE_REBATE;    // PMI
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ACCOUNT_BALANCE_OVERRIDE; // PMI
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_DILUTION_CALCULATOR;      // PMI
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ACTIVE_BATCH;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_REGULATORY_STANDARDS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_REGULATORY_DOCUMENTS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_PROGRESS_CTRL;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FUND_MASTER;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_RELEASE_FROZEN_ACCOUNT;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FUND_CLASS_COPY;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FUND_CLASS_MAINTENANCE;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_INTERFACE_FILE;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_TRAILER_FEE_SETUP;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_SYSTEMATIC;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_RRIF_LIF_LRIF_INFO;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_AMSACCTLVL;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_DISTRIBUTION;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_TRANS_HISTORY;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_SMART_FORM;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_DEMOGRAPHICS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_GLOBAL_SEARCH;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_PORTFOLIO_SETUP;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_COMMISSION_REDUCTION;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_INTEREST_MAINTENANCE;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_INTEREST_CONFIGURATION;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_SEG_ATTRIBUTES;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_SEG_GUARANTEE_RULES;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_EVENT_DATE_GEN; 
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_EVENT_SCH_MAIN;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_TRADE_SCH_MAIN;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_RESP_DIPLOMA;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FOREIGN_TAX_REVIEW;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_REMIT_UNCLM_ACCT; 
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ACCT_FEE_MODEL_ASSOCIATION;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_HOLDING_COMP;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ADDITIONAL_ASSETS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_INVOICE_INSTRUCTION;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_REPORT_GROUP;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_IDENTIFICATION_MAINT;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FFI_MAINT;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FUNDGROUP_REGULATORY;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_TRAILER_FEES_INQUIRY;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ACCOUNT_GROUP;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_PRIVATE_WEALTH_INFO;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_TRADE_VERIFICATION_SEARCH; 
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FATCA_FILING_DETAIL;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ACCOUNT_GROUPING_INFO;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FUND_RULES_MAINTENANCE;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_TRANSFER_OF_ACCOUNTS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FUND_GROUP;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FUND_BROKER_LINKAGE;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_REG_PLAN_TRANSFER_SEARCH;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_REGULATORY_AGREEMENT;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ACCT_ROUNDING_RULE;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ACCT_LVL_CUT_OFF_TIMES;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_EXTERNAL_TA_FUND_LINKAGE;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_REG_ACCT_EXTR;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_REG_ACCT_INFO_REV;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_WITHHODLDING_TAX_RATES_MAINTANENCE;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FUND_DISTRIBUTION_SPLIT_MAINTENANCE;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_RDSP_INTERFACE_TRANSACTIONS;

namespace SessionTags
{
   extern const I_CHAR *SESSION;
   const I_CHAR *MGMCO = I_("MGMCO");
}

namespace ConfigTags
{
   const I_CHAR *AUTOMATIC_IDCALLER = I_( "Automatic ID Caller" );
   const I_CHAR *IDCALLER_END       = I_( "End" );
   const I_CHAR *IDCALLER_SEARCH    = I_( "Search" );
}

namespace FORMS
{
   const I_CHAR *FORM_NAME = I_( "Form_Name" );
}

namespace ENCORR
{
   const I_CHAR *ENCORR_NAME = I_( "Encorr_Name" );
}

namespace AWD
{
   // Common
   const I_CHAR *Amount             = I_( "Amount" );
   const I_CHAR *Business_Area      = I_( "Business_Area" );
   const I_CHAR *Currency           = I_( "Currency" );
   const I_CHAR *Fund               = I_( "Fund" );
   const I_CHAR *Account_Num        = I_( "Account_Number" ); // Added to Lux
   const I_CHAR *PurchWorkTypes     = I_( "PurchWorkTypes" );
   const I_CHAR *RedeemWorkTypes    = I_( "RedeemWorkTypes" );
   const I_CHAR *ExchWorkTypes      = I_( "ExchWorkTypes" );
   const I_CHAR *TransWorkTypes     = I_( "TransWorkTypes" );
   const I_CHAR *PACWorkTypes       = I_( "PACWorkTypes" );
   const I_CHAR *SWPWorkTypes       = I_( "SWPWorkTypes" );
   const I_CHAR *RIFWorkTypes       = I_( "RIFWorkTypes" );
   const I_CHAR *AMSWorkTypes       = I_( "AMSWorkTypes" );
   const I_CHAR *DistribWorkTypes   = I_( "DistribWorkTypes" );
   const I_CHAR *SettlementWorkTypes= I_("SettlementWorkTypes");
   const I_CHAR *TransHistoryWorkTypes= I_("TransHistoryWorkTypes");
   const I_CHAR *LookupOrder        = I_( "LookupOrder" );
   const I_CHAR *Ascending          = I_( "Ascending" );
   const I_CHAR *Descending         = I_( "Descending" );

   // Canadian
   const I_CHAR *Shareholder_Num    = I_( "Shareholder_Number" );
   const I_CHAR *Entity_ID          = I_( "Entity_ID" );
   const I_CHAR *Phone_Num          = I_( "Phone_Number" );
   const I_CHAR *Passport_Num       = I_( "Passport_Number" );
   const I_CHAR *Social_Num         = I_( "Social_Number" );
   const I_CHAR *DL_Num             = I_( "DL_Number" );
   const I_CHAR *SIN_Num            = I_( "SIN_Number" );
   const I_CHAR *Birth_Cert         = I_( "Birth_Cert" );
   const I_CHAR *Credit_Card        = I_( "Credit_Card" );
   const I_CHAR *National_ID        = I_( "National_ID" );
   const I_CHAR *Other              = I_( "Other" );
   const I_CHAR *Broker_Code        = I_( "Dealer_Number" );
   const I_CHAR *Broker_Name        = I_( "Dealer_Name" );
   const I_CHAR *RepresentativeName = I_( "Rep_Name" );
   const I_CHAR *RepresentativeCode = I_( "Rep_Code" );
   const I_CHAR *Branch_Code        = I_( "Branch_Code" );
   const I_CHAR *Group_Code         = I_( "Group_Code" );
   const I_CHAR *Address1           = I_( "Address1" );
   const I_CHAR *Address2           = I_( "Address2" );
   const I_CHAR *Address3           = I_( "Address3" );
   const I_CHAR *Address4           = I_( "Address4" );
   const I_CHAR *Address5           = I_( "Address5" );
   const I_CHAR *Batch_Num          = I_( "Batch_Number" );
   const I_CHAR *CSR_Phone          = I_( "CSR_Phone" );
   const I_CHAR *Caller_Name        = I_( "Caller_Name" );
   const I_CHAR *Caller_Phone       = I_( "Caller_Phone_Number" );
   const I_CHAR *Postal             = I_( "Postal" );
   const I_CHAR *Country            = I_( "Country" );
   const I_CHAR *To_Account         = I_( "To_Account" );
   const I_CHAR *From_Account       = I_( "From_Account" );
   const I_CHAR *Entity_FName       = I_( "Entity_F_Name" );
   const I_CHAR *Entity_LName       = I_( "Entity_L_Name" );
   const I_CHAR *System_ID          = I_( "System_ID" );

   // Lux
   const I_CHAR *Trade_Date         = I_( "Trade_Date" );
   const I_CHAR *Settlement_Date    = I_( "Settlement_Date" );
   const I_CHAR *Reference_Number   = I_( "Reference_Number" );
   const I_CHAR *Order_Number       = I_( "Order_Number" );
   const I_CHAR *Participant_Number = I_( "Participant_Number" );
   const I_CHAR *Phoenix_Account    = I_( "Phoenix_Account" );
   const I_CHAR *VIP_Flag           = I_( "VIP_Flag" );
   const I_CHAR *FX                 = I_( "FX" );
   const I_CHAR *Payment_Method     = I_( "Payment_Method" );
   const I_CHAR *Amount_Type        = I_( "Amount_Type" );
   const I_CHAR *Originator         = I_( "Originator" );
   const I_CHAR *Plan_Number        = I_( "Plan_Number" );
   const I_CHAR *Payment_Reference  = I_( "Payment_Reference" );
   const I_CHAR *Bank_Account       = I_( "Bank_Account" );
   const I_CHAR *Value_Date         = I_( "Value_Date" );
   const I_CHAR *Free_Text          = I_( "Free_Text" );
   const I_CHAR *Cusip_Code         = I_( "Cusip_Code" );
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME               = I_( "CDSTCView" );
   const I_CHAR * const CLEARSCREEN             = I_( "clearScreen" );
   const I_CHAR * const DISPLAYID               = I_( "displayIdData" );
   const I_CHAR * const ENABLEFYI               = I_( "enableFYI" );
   const I_CHAR * const EXPANDCASE              = I_( "expandCase" );
   const I_CHAR * const FUNCTIONKEYPRESSED      = I_( "functionKeyPressed" );
   const I_CHAR * const GETREGISTRY             = I_( "getRegistry" );
   const I_CHAR * const GETSIGNON               = I_( "getSignOn" );
   const I_CHAR * const GETWORKDATA             = I_( "getWorkData" );
   const I_CHAR * const ONSELCHANGECMBSEARCH    = I_( "OnSelchangeCmbSearch" );
   const I_CHAR * const ONSELCHANGECMBUSING     = I_( "OnSelchangeCmbUsing" );
   const I_CHAR * const ONSELCHANGESEARCH       = I_( "OnSelChangeSearch1" );
   const I_CHAR * const MOVEDIALOG              = I_( "moveDialog" );
// const I_CHAR * const ONBTNNEW                = I_( "OnBtnNew" );
   const I_CHAR * const DONASU                  = I_( "doNASU" );
   const I_CHAR * const ONBTNCLOSE              = I_( "OnBtnClose" );
   const I_CHAR * const ONBTNDETAILS            = I_( "OnBtnDetails" );
   const I_CHAR * const ONBTNEND                = I_( "OnBtnEndCall" );
   const I_CHAR * const ONBTNFINANCIAL          = I_( "OnBtnFinancial" );
   const I_CHAR * const ONBTNREMARKS            = I_( "OnBtnRemarks" );
   const I_CHAR * const ONBTNFUND               = I_( "OnBtnFund" );
   const I_CHAR * const ONBTNFYI                = I_( "OnBtnFYI" );
   const I_CHAR * const ONBTNGETWORK            = I_( "OnBtnGetwork" );
   const I_CHAR * const ONBTNIDCALLER           = I_( "OnBtnIdcaller" );
   const I_CHAR * const ONBTNSEARCH             = I_( "OnBtnSearch" );
   const I_CHAR * const ONCHANGE                = I_( "OnChange" );
   const I_CHAR * const ONDESTROY               = I_( "OnDestroy" );
   const I_CHAR * const ONENCORR                = I_( "OnEncorr" );
   const I_CHAR * const ONFORMS                 = I_( "OnForms" );
   const I_CHAR * const ONAWDHISTORY            = I_( "OnAwdHistory" );
   const I_CHAR * const ONINITIALUPDATE         = I_( "OnInitialUpdate" );
   const I_CHAR * const ONKEYPRESSEDTSEARCH     = I_( "OnKeyPressEdtSearch" );
   const I_CHAR * const ONDSTC                  = I_( "OnDSTC" );
   const I_CHAR * const PROFILEINITIALIZATION   = I_( "profileInitialization" );
   const I_CHAR * const READY                   = I_( "ready" );
   const I_CHAR * const RESETROADDATA           = I_( "resetRoadData" );
   const I_CHAR * const SETROADDATA             = I_( "setRoadData" );
   const I_CHAR * const STARTCALL               = I_( "startCall" );
   const I_CHAR * const VALIDATETIME            = I_( "validateTime" );
   const I_CHAR * const FILLALLCHECKINGSECURITY = I_( "fillAllCheckingSecurity" );
   const I_CHAR * const CREATING_SHAREHOLDER    = I_( "CreatingShareholder" );
   const I_CHAR * const DIFFMGMCO               = I_( "DiffMgmCo" );
   const I_CHAR * const SETMGMCO                = I_( "SetMgmCo" );
   const I_CHAR * const SETUSINGLIST            = I_( "SetUsingList" );
   const I_CHAR * const ALLOWSEARCH             = I_( "AllowSearch" );
   const I_CHAR * const LAUNCHACCOUNTDETAILS    = I_( "launchAccountDetails" );
   const I_CHAR * const CANPERFORMSEARCH        = I_( "CanPerformSearch" );
   const I_CHAR * const REG_USER                = I_( "User" );
   const I_CHAR * const REG_MANAGEMENTCOMPANY   = I_( "ManagementCompany" );
   const I_CHAR * const ONBTNSETTLEMENT         = I_( "OnBtnSettlement" );
   const I_CHAR * const ONAWDEVENT         = I_( "OnAwdEvent" );
   const I_CHAR * const CREATEWORK         = I_( "CreateWork" );
   

   const I_CHAR * const AWD_MSG = I_( "An AWD item has been received. \n" )
                                  I_( "Your current process will be ended in order " )
                                  I_( "to process this new AWD item. \n" )
                                  I_( "Do you wish to process this new item?" );

   const I_CHAR * const CHANGE_MSG = I_( "Your current process will be ended in order " )
                                     I_( "to select a new System / Management Company.\n" )
                                     I_( "Do you wish to continue?" );
   const I_CHAR * const NUMERIC_INPUT = I_( "Account Nbr  Social Insurance Nbr  Shareholder Nbr  Certificate Nbr" );

   const char * const config_FYI_htm  = "\\config\\FYI.htm";

   const I_CHAR * const IDI_LABEL1    = I_( "LABEL1" );
   const I_CHAR * const IDI_LABEL2    = I_( "LABEL2" );
   const I_CHAR * const IDI_LABEL3    = I_( "LABEL3" );

   const I_CHAR * const YES           = I_( "Y" );
   const I_CHAR * const NO            = I_( "N" );
   // Other literals for the status bar
   const int SB_MESSAGE               = 0;
   const int SB_PROFILE               = 1;
   const int SB_SYSTEM                = 2;
   const int SB_MANAGEMENTCODE        = 3;
   const int SB_CONNECTION            = 4;
   const int INDICATOR_COUNT          = 5;
   const I_CHAR * IDI_MSG             = I_("MSG");
   const I_CHAR * IDI_MSG2            = I_("MSGA");
   const I_CHAR * ACCOUNT             = I_("Account");
   const I_CHAR * const FUND_CODE     = I_( "FundCode" );
   const I_CHAR * const CLASS_CODE    = I_( "ClassCode" );
   const I_CHAR *AccountNbr           = I_( "Account Nbr" );
   const I_CHAR *WORKSTATION          = I_( "WORKSTATION" );
   const I_CHAR *WORK_TYPE            = I_( "WORKTYPE" );
   const I_CHAR * const FROM_SCR      = I_( "FromScr" );
   const I_CHAR * const MFS           = I_( "ME,MFS" );
   const I_CHAR * const IS_WORK_EVENT = I_("IsWorkEvent");
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
   extern const long GUI_SEARCH_CRITERIAS_NOT_DEFINED1;
   extern const long GUI_SEARCH_CRITERIAS_NOT_DEFINED2;
   extern const long GUI_SEARCH_CRITERIAS_NOT_DEFINED3;
   extern const long GUI_AWD_NOT_LOGGED_ON;
   extern const long GUI_AWD_SYSTEM_ERROR;
   extern const long GUI_AWD_SYSTEM_CHANGED;
   extern const long GUI_SECURITY_VIOLATION;
// extern CLASS_IMPORT const long GUI_AWD_NODATA;
   extern const long GUI_AWD_MGMCO_TABLE_MISSING;
   extern const long GUI_AWD_MGMCO_ENTRY_MISSING;
   extern const long GUI_AWD_SEARCH_CRITERIA_INVALID;
   extern const long GUI_AWD_LOOKUP_ERROR;
   extern const long GUI_AWD_EXCEPTION;
   extern const long GUI_AWD_INVALID_MAPPED_EVENT;
   extern const long GUI_AWD_NO_SESSION;
   extern const long GUI_AWD_FAILED_UPDATE_OR_CREATE;
}

//user access function codes
namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const FUND_NAV;
   extern CLASS_IMPORT I_CHAR * const SEARCH_FOR_ACCOUNT_OR_ENTITY;
   extern CLASS_IMPORT I_CHAR * const SEARCH_FOR_CHEQUE;
   extern CLASS_IMPORT I_CHAR * const SEARCH_FOR_CERTIFICATE;
   extern CLASS_IMPORT I_CHAR * const SEARCH_FOR_SHR_INFO;
   extern CLASS_IMPORT I_CHAR * const SEARCH_FOR_ACCT_INFO;
   extern CLASS_IMPORT I_CHAR * const SEARCH_FOR_ADDRESS;
   extern CLASS_IMPORT I_CHAR * const ADDRESS_BOOK;
   extern CLASS_IMPORT I_CHAR * const BANKING_INSTRUCTION;
   extern CLASS_IMPORT I_CHAR * const DISTRIBUTION;
   extern CLASS_IMPORT I_CHAR * const DEFAULT_ALLOCATION;
   extern CLASS_IMPORT I_CHAR * const ACCOUNT_CERTIFICATE_INFO;
   extern CLASS_IMPORT I_CHAR * const REMARKS;
   extern CLASS_IMPORT I_CHAR * const TRADING_PURCHASE;
   extern CLASS_IMPORT I_CHAR * const TRADING_EXCHANGE;
   extern CLASS_IMPORT I_CHAR * const TAX_RATES;
   extern CLASS_IMPORT I_CHAR * const TRADING_REDEMPTION;
   extern CLASS_IMPORT I_CHAR * const BANKING_BROKER_CODE;
   extern CLASS_IMPORT I_CHAR * const BANKING_BRANCH_CODE;
   extern CLASS_IMPORT I_CHAR * const BANKING_REP_CODE;
   extern CLASS_IMPORT I_CHAR * const BANKING_CLIENT;
   extern CLASS_IMPORT I_CHAR * const BANKING_FUND;
   extern CLASS_IMPORT I_CHAR * const SETTLE_ALL_TRADE;
   extern CLASS_IMPORT I_CHAR * const SETTLE_ACCOUNT;
   extern CLASS_IMPORT I_CHAR * const SETTLE_WIRE_ORDER;
   extern CLASS_IMPORT I_CHAR * const SETTLE_BROKER;
   extern CLASS_IMPORT I_CHAR * const AMS_GLOBAL;
   extern CLASS_IMPORT I_CHAR * const PROTECTED_FUND_SETUP;
   extern CLASS_IMPORT I_CHAR * const MKT_INDEX_MASTER;
   extern CLASS_IMPORT I_CHAR * const MKT_INDEX_VALUES;
   extern CLASS_IMPORT I_CHAR * const AMS_REPORT;
   extern CLASS_IMPORT I_CHAR * const TRADE_SEARCH;
   extern CLASS_IMPORT I_CHAR * const BROKER_AMS_RESTRICT;
   extern CLASS_IMPORT I_CHAR * const MANUAL_DIVIDEND;
   extern CLASS_IMPORT I_CHAR * const PAYMENT_INSTRUCTIONS;
   extern CLASS_IMPORT I_CHAR * const PAY_TO_ENTITY;
   extern CLASS_IMPORT I_CHAR * const INSTITUTION_MAINTENANCE;
   extern CLASS_IMPORT I_CHAR * const SETTLE_LOCATION_SYS_LVL;
   extern CLASS_IMPORT I_CHAR * const DAILY_TRANSACTIONS_FEES;
   extern CLASS_IMPORT I_CHAR * const FEE_MODEL;
   extern CLASS_IMPORT I_CHAR * const FUNDSPONSOR_FEE_MODEL;
   extern CLASS_IMPORT I_CHAR * const FUND_BROKER_MAINTENANCE;
   extern CLASS_IMPORT I_CHAR * const AGGREGATED_ORDER_INFORMATION;
   extern CLASS_IMPORT I_CHAR * const MSG_SEARCH;
   extern CLASS_IMPORT I_CHAR * const FILE_SEARCH;
   extern CLASS_IMPORT I_CHAR * const CANCELLATION_INSTRUCTION;
   extern CLASS_IMPORT I_CHAR * const MGMTCO_PAYMENT_INSTRUCTION;
   extern CLASS_IMPORT I_CHAR * const PAYMENT_SEARCH;
   extern CLASS_IMPORT I_CHAR * const PAYMENT_BATCH;
   extern CLASS_IMPORT I_CHAR * const BROKER_TRADING_OVERRIDES;
   extern CLASS_IMPORT I_CHAR * const ACCOUNT_BALANCE_OVERRIDE;
   extern CLASS_IMPORT I_CHAR * const DILUTION_CALCULATOR;
   extern CLASS_IMPORT I_CHAR * const REGULATORY_STANDARDS;
   extern CLASS_IMPORT I_CHAR * const REGULATORY_DOCUMENTS;
   extern CLASS_IMPORT I_CHAR * const FUND_MASTER;
   extern CLASS_IMPORT I_CHAR * const FUND_DETAIL;
   extern CLASS_IMPORT I_CHAR * const RELEASE_FROZEN_ACCOUNT;
   extern CLASS_IMPORT I_CHAR * const FUND_CLASS_COPY;
   extern CLASS_IMPORT I_CHAR * const FUND_CLASS_MAINTENANCE;
   extern CLASS_IMPORT I_CHAR * const RESP_INTERFACE_FILE;
   extern CLASS_IMPORT I_CHAR * const SYSTEMLVL_TRAILER_FEE_SETUP;
   extern CLASS_IMPORT I_CHAR * const SMART_FORM;
   extern CLASS_IMPORT I_CHAR * const COMMISSION_REDUCTION;
   extern CLASS_IMPORT I_CHAR * const PORTFOLIO_SETUP;
   extern CLASS_IMPORT I_CHAR * const GLOBAL_SEARCH;
   extern CLASS_IMPORT I_CHAR * const INTEREST_CONFIGURATION;
   extern CLASS_IMPORT I_CHAR * const INTEREST_MAINTENANCE;
   extern CLASS_IMPORT I_CHAR * const SEG_ATTRIBUTES;
   extern CLASS_IMPORT I_CHAR * const GUARANTEE_RULES;
   extern CLASS_IMPORT I_CHAR * const LANGUAGE_TOGGLE;
   extern CLASS_IMPORT I_CHAR * const EVENT_DATE_GEN;
   extern CLASS_IMPORT I_CHAR * const EVENT_SCH_MAIN;
   extern CLASS_IMPORT I_CHAR * const TRADE_SCH_MAIN;
   extern CLASS_IMPORT I_CHAR * const RESP_DIPLOMA;
   extern CLASS_IMPORT I_CHAR * const REG_AGENT;
   extern CLASS_IMPORT I_CHAR * const REMIT_UNCLM_ACCT;
   extern CLASS_IMPORT I_CHAR * const ACCT_FEE_MODEL_ASSOCIATION;
   extern CLASS_IMPORT I_CHAR * const INVOICE_INSTRUCTION;
   extern CLASS_IMPORT I_CHAR * const REPORT_GROUP;
   extern CLASS_IMPORT I_CHAR * const ADDITIONAL_ASSETS;
   extern CLASS_IMPORT I_CHAR * const HOLDING_COMP_MAINT;
   extern CLASS_IMPORT I_CHAR * const FEE_PARAMETER_SYSTEM;
   extern CLASS_IMPORT I_CHAR * const FFI_MAINT; 
   extern CLASS_IMPORT I_CHAR * const BROKER_IDENT_MAINT; 
   extern CLASS_IMPORT I_CHAR * const FUND_IDENT_MAINT; 
   extern CLASS_IMPORT I_CHAR * const FUNDGROUP_REGULATORY; 
   extern CLASS_IMPORT I_CHAR * const TRAILER_FEES_INQUIRY;
   extern CLASS_IMPORT I_CHAR * const ACCOUNT_GROUPING;
   extern CLASS_IMPORT I_CHAR * const PRIVATE_WEALTH_INFO;
   extern CLASS_IMPORT I_CHAR * const TRADE_VERIFICATION;
   extern CLASS_IMPORT I_CHAR * const FATCA_FILING_DETAIL;
   extern CLASS_IMPORT I_CHAR * const ACCOUNT_GROUPING_INFO;
   extern CLASS_IMPORT I_CHAR * const FUND_RULES_MAINTENANCE;
   extern CLASS_IMPORT I_CHAR * const TRANSFER_OF_ACCOUNTS;
   extern CLASS_IMPORT I_CHAR * const FUND_GROUP;
   extern CLASS_IMPORT I_CHAR * const FUND_BROKER_LINKAGE;
   extern CLASS_IMPORT I_CHAR * const REG_PLAN_TRANSFER;
   extern CLASS_IMPORT I_CHAR * const REGULATORY_AGREEMENT;
   extern CLASS_IMPORT I_CHAR * const BROKER_CUT_OFF;
   extern CLASS_IMPORT I_CHAR * const EXTERNAL_TA_FUND_LINKAGE;
   extern CLASS_IMPORT I_CHAR * const REG_ACCT_EXTR;
   extern CLASS_IMPORT I_CHAR * const REG_ACCT_INFO_REV;
   extern CLASS_IMPORT I_CHAR * const WITHHODLDING_TAX_RATES_MAINTANENCE;
   extern CLASS_IMPORT I_CHAR * const FUND_DISTRIBUTION_SPLIT_MAINTENANCE;
   extern CLASS_IMPORT I_CHAR * const RDSP_INTERFACE_TRANSACTIONS;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId CallerName;
   extern CLASS_IMPORT const BFTextFieldId RelationShip;
   extern CLASS_IMPORT const BFTextFieldId BusinessPhone;
   extern CLASS_IMPORT const BFTextFieldId BusinessExt;
   extern CLASS_IMPORT const BFTextFieldId HomePhone;
   extern CLASS_IMPORT const BFTextFieldId CallStartTime;
   extern CLASS_IMPORT const BFTextFieldId CallEndTime;
   extern CLASS_IMPORT const BFTextFieldId MgmtCoPayReq;
   extern CLASS_IMPORT const BFTextFieldId ChqStatus;
   extern CLASS_IMPORT const BFTextFieldId BusinessArea;
   extern CLASS_IMPORT const BFTextFieldId FATCAApplicable;
   extern CLASS_IMPORT const BFTextFieldId InvApplicable;
   extern CLASS_IMPORT const BFTextFieldId RptGrpApplicable;
   extern CLASS_IMPORT const BFTextFieldId    AWDObjectId;
   extern CLASS_IMPORT const BFTextFieldId    AWDCrda;
}

CDSTCView* CDSTCView::GetView()
{
   CFrameWnd* pFrame = (CFrameWnd*)(AfxGetApp()->m_pMainWnd);
   CView* pView = pFrame->GetActiveView();
   if( !pView) {
      return( NULL );
   }
   if( ! pView->IsKindOf( RUNTIME_CLASS(CDSTCView) ) ) {
      return(NULL);
   }
   return( (CDSTCView*)pView );
}

#include <ifsupp/ifsuppext.hpp>
#include <ifastcbo/mgmtcooptions.hpp>


BOOL __stdcall getMgmtCoInfo(
                    DSTCUserSession*& pUserSession,
                    MgmtCo*& pMgmtCo,
                    CString& strClientID,
                    CString& strCompanyID,
                    CString& strName,
                    CString& strURL )
{
   CDSTCView* pView = CDSTCView::GetView();
   if( NULL != pView ) {
      // get the UserSession
      try {
         GenericInterface* pGI = const_cast<GenericInterface*>(pView->getUserSession());
         if( NULL != pGI ) {
            DString dstrMgmtCo;
            pGI->getField( NULL, SYSTMGMTS, dstrMgmtCo );
            pUserSession = dynamic_cast<DSTCUserSession *>(pGI->getBFSession());
            if( NULL != pUserSession ) {
               DSTCGlobalSession& gs = dynamic_cast<DSTCGlobalSession&>(pUserSession->getGlobalSession());
               gs.findMgmtCo( dstrMgmtCo, pMgmtCo );
               DString dstrCompanyId, dstrClientId, dstrCompanyName, dstrURL;
               pMgmtCo->getField( ifds::CompanyId, dstrCompanyId, BF::HOST );
               strCompanyID = dstrCompanyId.c_str();
               pMgmtCo->getField( ifds::ClientID, dstrClientId, BF::HOST );
               strClientID = dstrClientId.c_str();
               pMgmtCo->getField( ifds::CompanyName, dstrCompanyName, BF::HOST );
               strName = dstrCompanyName.c_str();

               MgmtCoOptions* pOptions = NULL;
               pMgmtCo->getMgmtCoOptions( pOptions );
               if( NULL != pOptions ) {
                  pOptions->getField( ifds::CompanyUrl, dstrURL, BF::HOST );
                  strURL = dstrURL.c_str();
               }
            }
         }
      } catch (const std::bad_cast& /*e*/) {
         return( FALSE );
      }
   }
   return( TRUE );
}

void __stdcall kickStatusBar( void ) {
   CDSTCView* pView = CDSTCView::GetView();
   if( NULL != pView ) {
      pView->NotifyStatusBarOnRegistryChange();
   }
}


//******************************************************************************
// CDSTCView

UINT WM_WORK_EVENT = RegisterWindowMessage( I_( "WM_WORK_EVENT" ) );

IMPLEMENT_DYNCREATE(CDSTCView, CFormView)

BEGIN_MESSAGE_MAP(CDSTCView, CFormView)
//{{AFX_MSG_MAP(CDSTCView)
ON_BN_CLICKED(IDC_BTN_FINANCIAL, OnBtnFinancial)
ON_BN_CLICKED(IDC_BTN_REMARKS, OnBtnRemarks)
ON_BN_CLICKED(IDC_BTN_DETAILS, OnBtnDetails)
ON_BN_CLICKED(IDC_BTN_FUND, OnBtnFund)
ON_BN_CLICKED(IDC_BTN_FYI, OnBtnFYI)
ON_BN_CLICKED(IDC_BTN_GETWORK, OnBtnGetwork)
ON_BN_CLICKED(IDC_BTN_IDCALLER, OnBtnIdcaller)
ON_BN_CLICKED(IDC_BTN_END, OnBtnEndCallV)
ON_BN_CLICKED(IDC_BTN_SEARCH, OnBtnSearch)
ON_BN_CLICKED(IDC_BTN_GLOBAL_SEARCH, OnBtnGlobalSearch)
ON_WM_DESTROY()
ON_CBN_SELCHANGE(IDC_CMB_SEARCH, OnSelchangeCmbSearch)
ON_CBN_SELCHANGE(IDC_CMB_USING, OnSelchangeCmbUsing)
ON_CBN_SELCHANGE(IDC_CMB_SEARCH1, OnSelChangeSearch1)
ON_BN_CLICKED(IDC_BTN_NEW, OnBtnNew)
ON_BN_CLICKED(IDC_BTN_HARNESS, OnBtnHarness)
ON_MESSAGE(UM_IDDATA, displayIdData)
ON_MESSAGE(UM_FUNCTIONKEYPRESSED, functionKeyPressed)
ON_MESSAGE(UM_READY, ready)
ON_MESSAGE(UM_ENDSESSION, OnEndSession)
ON_MESSAGE(UM_EXPANDCASE, expandCase)
ON_MESSAGE(UM_LAUNCHDETAILS, launchAccountDetails)
ON_MESSAGE(UM_HOLDING_COMP, launchHoldingComp)
ON_MESSAGE(UM_LAUNCHTRADING,launchTrading)
ON_MESSAGE(UM_NEWSEARCH, newSearch)
ON_MESSAGE(UM_ENDCURRENTSESSION, OnEndCurrSession)
ON_EN_CHANGE(IDC_EDT_AREA_CODE, OnChangeEdtAreaCode)
ON_BN_CLICKED(IDC_BTN_STLMENT, OnBtnSettlement)
ON_COMMAND(IDM_CHANGE, OnChange)
ON_COMMAND(IDM_DSTC, OnDSTC)
ON_COMMAND(IDM_AWDCOMMENTS, OnAWDComment)
ON_UPDATE_COMMAND_UI(IDM_AWDCOMMENTS, OnUpdateAWDComment )
ON_COMMAND(IDM_FORMS, OnForms)
ON_COMMAND(IDM_ENCORR, OnEncorr)
ON_COMMAND(ID_MENU_DEFSETTING, OnDefaultSetting)
ON_COMMAND(IDM_AWD, OnAwdHistory)
ON_COMMAND(IDM_TAXRATES, OnTaxrates)
ON_COMMAND(ID_HELP, OnHelp1)
ON_COMMAND(ID_HELP1, OnHelp1)
ON_COMMAND(ID_HELP2, OnHelp2)
ON_COMMAND(ID_HELP3, OnHelp3)
ON_COMMAND(IDM_SYSTEMLEVELSETUP_PROTECTEDFUNDSSETUP, OnProtectedfundsetup)
ON_UPDATE_COMMAND_UI(IDM_SYSTEMLEVELSETUP_PROTECTEDFUNDSSETUP, OnUpdateProtectedfundsetup )
ON_COMMAND(IDM_MENU_TRADE_ENTRY, OnBtnFinancial)
ON_UPDATE_COMMAND_UI(IDM_MENU_TRADE_ENTRY, OnUpdateFinancial)
ON_COMMAND(IDM_MENU_SETTLEMENT, OnBtnSettlement)
ON_UPDATE_COMMAND_UI(IDM_MENU_SETTLEMENT, OnUpdateSettlement)
ON_COMMAND(IDM_HISTORICAL_INFO_SRCH, OnHistoricalInfoSrch)
ON_UPDATE_COMMAND_UI(IDM_HISTORICAL_INFO_SRCH, OnUpdateHistoricalInfoSrch )
ON_COMMAND(IDM_AMS_REPORTS, OnAMSReports )
ON_UPDATE_COMMAND_UI(IDM_AMS_REPORTS, OnUpdateAmsReports )
ON_COMMAND(IDM_BROKER_AMS, OnBrokerAMS)
ON_UPDATE_COMMAND_UI(IDM_BROKER_AMS, OnUpdateBrokerAMS)
ON_COMMAND(IDM_MKT_INDEX_MASTER, OnMktIndexMaster)
ON_UPDATE_COMMAND_UI(IDM_MKT_INDEX_MASTER, OnUpdateMktIndexMaster)
ON_COMMAND(IDM_MKT_INDEX_VALUES, OnMktIndexValues)
ON_UPDATE_COMMAND_UI(IDM_MKT_INDEX_VALUES, OnUpdateMktIndexValues)
ON_COMMAND(ID_INTERFACE_MESSAGE_INQUIRY, OnMsgInquirySearch)
ON_UPDATE_COMMAND_UI(ID_INTERFACE_MESSAGE_INQUIRY, OnUpdateMsgInquirySearch)
ON_COMMAND(ID_INTERFACE_FILE_INQUIRY, OnFileInquirySearch)
ON_UPDATE_COMMAND_UI(ID_INTERFACE_FILE_INQUIRY, OnUpdateFileInquirySearch)
ON_COMMAND(ID_SYSTEMLEVELSETUP_SYSTEMLEVELFEE, OnSystemLevelFee)
ON_UPDATE_COMMAND_UI(ID_SYSTEMLEVELSETUP_SYSTEMLEVELFEE, OnUpdateSystemLevelFee)
ON_COMMAND(IDM_REPORT_STATUS, OnReportStatus )
ON_COMMAND(IDM_TRANSACTIONS_TRADESEARCH, OnTradeSearch )
ON_COMMAND(IDM_GLOBAL_AMS,OnGlobalAMS )
ON_UPDATE_COMMAND_UI(IDM_GLOBAL_AMS, OnUpdateGlobalAMS )
ON_UPDATE_COMMAND_UI(IDM_TRANSACTIONS_TRADESEARCH, OnUpdateTradeSearch )
ON_COMMAND(IDM_MANUAL_DIVIDEND, OnManualDividend)
ON_UPDATE_COMMAND_UI(IDM_MANUAL_DIVIDEND, OnUpdateManualDividend)
ON_COMMAND(IDM_SETTLEMENT_LOCATION, OnSettlementLocation)
ON_UPDATE_COMMAND_UI(IDM_SETTLEMENT_LOCATION, OnUpdateSettlementLocation)
ON_COMMAND(ID_MENU_SYSTEMMAINTENANCE_INSTITUTIONSTRANSITMAINTENANCE, OnFinancialInstitutions)
ON_UPDATE_COMMAND_UI(ID_MENU_SYSTEMMAINTENANCE_INSTITUTIONSTRANSITMAINTENANCE, OnUpdateFinancialInstitutions)

ON_COMMAND(ID_MENU_BROKERLEVELMAINTENANCE_PAYMENTINSTRUCTIONS, OnPaymentInstructions)
ON_UPDATE_COMMAND_UI(ID_MENU_BROKERLEVELMAINTENANCE_PAYMENTINSTRUCTIONS, OnUpdatePaymentInstructions)

ON_COMMAND(ID_MENU_BROKERLEVELMAINTENANCE_FEATURES_PAYTOENTITY, OnPayToEntity)
ON_UPDATE_COMMAND_UI(ID_MENU_BROKERLEVELMAINTENANCE_FEATURES_PAYTOENTITY, OnUpdatePayToEntity)
ON_COMMAND(ID_MENU_PAYMENTSEARCH, OnPaymentSearch)
ON_UPDATE_COMMAND_UI(ID_MENU_PAYMENTSEARCH, OnUpdatePaymentSearch)
ON_COMMAND(ID_MENU_GENERATEBAFFFILE, OnPaymentBatch)
ON_UPDATE_COMMAND_UI(ID_MENU_GENERATEBAFFFILE, OnUpdatePaymentBatch)
ON_COMMAND(ID_MENU_FUND_LIMITATION, OnFundLimitation)
ON_UPDATE_COMMAND_UI(ID_MENU_FUND_LIMITATION, OnUpdateFundLimitation)
ON_COMMAND(ID_MENU_BROKERLEVELMAINTENANCE_BANKING, OnBrokerBanking)
ON_UPDATE_COMMAND_UI(ID_MENU_BROKERLEVELMAINTENANCE_BANKING, OnUpdateBrokerBanking)
ON_COMMAND(ID_MENU_FUNDLEVELMAINTENANCE_DAILYTRANSACTIONSFEES, OnDailyTransactionsFees)
ON_UPDATE_COMMAND_UI(ID_MENU_FUNDLEVELMAINTENANCE_DAILYTRANSACTIONSFEES, OnUpdateDailyTransactionsFees)
ON_COMMAND(IDM_CLIENT_FEEMODEL, OnFeeModel)
ON_UPDATE_COMMAND_UI(IDM_CLIENT_FEEMODEL, OnUpdateFeeModel)
ON_COMMAND(IDM_FUNDSPONSOR_FEEMODEL, OnFundSponsorFeeModel)
ON_UPDATE_COMMAND_UI(IDM_FUNDSPONSOR_FEEMODEL, OnUpdateFundSponsorFeeModel)
ON_COMMAND(IDM_FUND_BROKER, OnFundBroker)
ON_UPDATE_COMMAND_UI(IDM_FUND_BROKER, OnUpdateFundBroker)
ON_COMMAND(IDM_AGGREGATE_ORDER, OnAggregateOrder)
ON_UPDATE_COMMAND_UI(IDM_AGGREGATE_ORDER, OnUpdateAggregateOrder)
ON_COMMAND(ID_TRANSACTIONS_CANCELLATIONINSTRUCTION, OnCancellationInstr )
ON_UPDATE_COMMAND_UI(ID_TRANSACTIONS_CANCELLATIONINSTRUCTION, OnUpdateCancellationInstr )
ON_COMMAND(ID_SYSMENU_PAYTOENTITY, OnMgmtCoPayToEntity)
ON_UPDATE_COMMAND_UI(ID_SYSMENU_PAYTOENTITY, OnUpdateMgmtCoPayToEntity)
ON_COMMAND(ID_SYSMENU_PAYMENTINSTRUCTIONS, OnMgmtCoPaymentInstr )
ON_UPDATE_COMMAND_UI(ID_SYSMENU_PAYMENTINSTRUCTIONS, OnUpdateMgmtCoPaymentInstr )
ON_COMMAND(ID_SYSTEMMAINTENANCE_HOLDINGCOMPANY, OnHoldingCompany )
ON_UPDATE_COMMAND_UI(ID_SYSTEMMAINTENANCE_HOLDINGCOMPANY, OnUpdateHoldingCompany )


// PMI - Aug 2nd 2007
ON_COMMAND(ID_ACCOUNTINFORMATION_ACCOUNTBALANCEOVERRIDE, OnAccountBalanceOverride )
ON_UPDATE_COMMAND_UI(ID_ACCOUNTINFORMATION_ACCOUNTBALANCEOVERRIDE, OnUpdateAccountBalanceOverride )

ON_COMMAND(ID_ACCOUNTINFORMATION_DILUTIONCALCULATOR, OnDilutionCalculator )
ON_UPDATE_COMMAND_UI(ID_ACCOUNTINFORMATION_DILUTIONCALCULATOR, OnUpdateDilutionCalculator )
// -

ON_COMMAND(ID_SYSTEMMAINTENANCE_REGULATORYSTANDARDS, OnRegulatoryStandards)
ON_UPDATE_COMMAND_UI(ID_SYSTEMMAINTENANCE_REGULATORYSTANDARDS, OnUpdateRegulatoryStandards)
ON_COMMAND(ID_SYSTEMMAINTENANCE_REGULATORYDOCUMENTS, OnRegulatoryDocuments)
ON_UPDATE_COMMAND_UI(ID_SYSTEMMAINTENANCE_REGULATORYDOCUMENTS, OnUpdateRegulatoryDocuments)
ON_COMMAND(ID_FUNDLEVELMAINTENANCE_FUNDMASTERINQUIRY, OnFundMaster)
ON_UPDATE_COMMAND_UI(ID_FUNDLEVELMAINTENANCE_FUNDMASTERINQUIRY, OnUpdateFundMaster)
ON_COMMAND(ID_ACCOUNTINFORMATION_RELEASEFROZENACCOUNT, OnReleaseFrozenAccount)
ON_UPDATE_COMMAND_UI(ID_ACCOUNTINFORMATION_RELEASEFROZENACCOUNT, OnUpdateReleaseFrozenAccount)

ON_COMMAND(ID_FUNDLEVELMAINTENANCE_FUNDCLASSCOPY, OnFundClassCopy)
ON_UPDATE_COMMAND_UI(ID_FUNDLEVELMAINTENANCE_FUNDCLASSCOPY, OnUpdateFundClassCopy)

ON_COMMAND(ID_FUNDLEVELMAINTENANCE_FUNDCLASSMAINTENANCE, OnFundClassMaintenance)
ON_UPDATE_COMMAND_UI(ID_FUNDLEVELMAINTENANCE_FUNDCLASSMAINTENANCE, OnUpdateFundClassMaintenance)

ON_COMMAND(ID_SYSTEMMAINTENANCE_INTERFACEFILE, OnInterfaceFile)
ON_UPDATE_COMMAND_UI(ID_SYSTEMMAINTENANCE_INTERFACEFILE, OnUpdateInterfaceFile)

ON_COMMAND(ID_SYSTEMMAINTENANCE_TRAILERFEESETUP, OnTrailerFeeSetup)
ON_UPDATE_COMMAND_UI(ID_SYSTEMMAINTENANCE_TRAILERFEESETUP, OnUpdateTrailerFeeSetup)

ON_COMMAND(ID_APPLICATION_SMARTFORMS, OnSmartForms)
ON_UPDATE_COMMAND_UI(ID_APPLICATION_SMARTFORMS, OnUpdateSmartForms)

ON_COMMAND(ID_SYSTEMMAINTENANCE_PORTFOLIOSETUP , OnPortfolioSetup)
ON_UPDATE_COMMAND_UI(ID_SYSTEMMAINTENANCE_PORTFOLIOSETUP , OnUpdatePortfolioSetup)
ON_COMMAND(ID_GIASETUP_COMMISSIONCUT, OnCommisionReduction)
ON_UPDATE_COMMAND_UI(ID_GIASETUP_COMMISSIONCUT, OnUpdateCommisionReduction)
ON_COMMAND(ID_GIASETUP_INTERESTRATECONFIGURATION, OnInterestRateConfiguration)
ON_UPDATE_COMMAND_UI(ID_GIASETUP_INTERESTRATECONFIGURATION, OnUpdateInterestRateConfiguration)
ON_COMMAND(ID_GIASETUP_INTERESTRATE_MAINTENANCE, OnInterestRateMaintenance)
ON_UPDATE_COMMAND_UI(ID_GIASETUP_INTERESTRATE_MAINTENANCE, OnUpdateInterestRateMaintenance)
ON_COMMAND(ID_LANGUAGE_ENGLISH, OnLanguageEnglish)
ON_COMMAND(ID_LANGUAGE_FRENCH, OnLanguageFrench)
ON_UPDATE_COMMAND_UI(ID_LANGUAGE_ENGLISH, OnUpdateLanguageEnglish)
ON_UPDATE_COMMAND_UI(ID_LANGUAGE_FRENCH, OnUpdateLanguageFrench)

ON_COMMAND(ID_SYSTEMMAINTENANCE_RESPDIPLOMA, OnRESPDiplomaMenuItem)
ON_UPDATE_COMMAND_UI(ID_SYSTEMMAINTENANCE_RESPDIPLOMA, OnUpdateRESPDiplomaMenuItem)

ON_COMMAND(ID_SEGMAINTENANCE_GUARANTEERULES, OnSegMaintenanceGuaranteeRules)
ON_UPDATE_COMMAND_UI(ID_SEGMAINTENANCE_GUARANTEERULES, OnUpdateMaintenanceGuaranteeRules)
ON_COMMAND(ID_SEGMAINTENANCE_SEGATTRIBUTES, OnSegMaintenanceSegAttributes)
ON_UPDATE_COMMAND_UI(ID_SEGMAINTENANCE_SEGATTRIBUTES, OnUpdateSegMaintenanceSegAttributes)

ON_COMMAND(ID_FUNDLEVELMAINTENANCE_EVENT_DATE_GEN, OnEventDateGen)
ON_UPDATE_COMMAND_UI(ID_FUNDLEVELMAINTENANCE_EVENT_DATE_GEN, OnUpdateEventDateGen)

ON_COMMAND(ID_FUNDLEVELMAINTENANCE_EVENTSCHEDULEMAINTENANCE, OnEventSchduleMain)
ON_UPDATE_COMMAND_UI(ID_FUNDLEVELMAINTENANCE_EVENTSCHEDULEMAINTENANCE, OnUpdateEventSchduleMain)

ON_COMMAND(ID_FUNDLEVELMAINTENANCE_TRADESCHEDULEMAINTENANCE, OnTradeSchduleMain)
ON_UPDATE_COMMAND_UI(ID_FUNDLEVELMAINTENANCE_TRADESCHEDULEMAINTENANCE, OnUpdateTradeSchduleMain)

ON_COMMAND(ID_ACCOUNTLEVELMAINTENANCE_FOREIGNTAXREVIEW, OnAccountForeignTaxReview)
ON_UPDATE_COMMAND_UI(ID_ACCOUNTLEVELMAINTENANCE_FOREIGNTAXREVIEW, OnUpdateAccountForeignTaxReview)

ON_COMMAND(ID_TRANSACTIONS_REMIT_UNCLM_ACCT, OnRemitUnclmAcct )
ON_UPDATE_COMMAND_UI(ID_TRANSACTIONS_REMIT_UNCLM_ACCT, OnUpdateRemitUnclmAcct )

ON_COMMAND(ID_ACCOUNTLEVELMAINTENANCE_FEE_MODEL_ASSOCIATION, OnAccountFeeModelAssociation)
ON_UPDATE_COMMAND_UI(ID_ACCOUNTLEVELMAINTENANCE_FEE_MODEL_ASSOCIATION, OnUpdateAccountFeeModelAssociation)

ON_COMMAND(ID_MFANDMFRMAINTENANCE_INVOICEINSTRUCTION, OnMFAndMFRInvoiceInstruction)
ON_UPDATE_COMMAND_UI(ID_MFANDMFRMAINTENANCE_INVOICEINSTRUCTION, OnUpdateMFAndMFRInvoiceInstruction)

ON_COMMAND(ID_MFANDMFRMAINTENANCE_REPORTGROUP, OnMFAndMFRReportGroup)
ON_UPDATE_COMMAND_UI(ID_MFANDMFRMAINTENANCE_REPORTGROUP, OnUpdateMFAndMFRReportGroup)

ON_COMMAND(ID_MFANDMFRMAINTENANCE_ADDITIONALASSETS, OnMFAndMFRAdditionalAssets)
ON_UPDATE_COMMAND_UI(ID_MFANDMFRMAINTENANCE_ADDITIONALASSETS, OnUpdateMFAndMFRAdditionalAssets)

ON_COMMAND(ID_SYSTEMMAINTENANCE_FOREIGNFINANCIALINSTITUTION_MAINTENANCE, OnForeignFinancialInstitutionMaintenance)
ON_UPDATE_COMMAND_UI(ID_SYSTEMMAINTENANCE_FOREIGNFINANCIALINSTITUTION_MAINTENANCE, OnUpdateForeignFinancialInstitutionMaintenance)

ON_COMMAND(ID_SYSTEMLEVELMAINTENANCE_IDENTIFICATIONMAINTENANCE, OnSystemIdentificationMaintenance)
ON_UPDATE_COMMAND_UI(ID_SYSTEMLEVELMAINTENANCE_IDENTIFICATIONMAINTENANCE, OnUpdateSystemIdentificationMaintenance)

ON_COMMAND(ID_SYSTEMLEVELMAINTENANCE_FUNDGRPOUPREGULATORY, OnFundGroupRegulatory)
ON_UPDATE_COMMAND_UI(ID_SYSTEMLEVELMAINTENANCE_FUNDGRPOUPREGULATORY, OnUpdateFundGroupRegulatory)

ON_COMMAND(ID_SYSTEMMAINTENANCE_TRAILERFEESINQUIRY, OnTrailerFeesInquiry)
ON_UPDATE_COMMAND_UI(ID_SYSTEMMAINTENANCE_TRAILERFEESINQUIRY, OnUpdateTrailerFeesInquiry)

ON_COMMAND(ID_SYSTEMMAINTENANCE_ACCOUNTGROUP, OnAccountGroup)
ON_UPDATE_COMMAND_UI(ID_SYSTEMMAINTENANCE_ACCOUNTGROUP, OnUpdateAccountGroup)

ON_COMMAND(ID_SYSTEMMAINTENANCE_PRIVATEWEALTHINFORMATION, OnPrivateWealthInformation)
ON_UPDATE_COMMAND_UI(ID_SYSTEMMAINTENANCE_PRIVATEWEALTHINFORMATION, OnUpdatePrivateWealthInformation)

ON_COMMAND(IDM_TRANSACTIONS_TRADE_VERIFY, OnTradeVerification)
ON_UPDATE_COMMAND_UI(IDM_TRANSACTIONS_TRADE_VERIFY, OnUpdateTradeVerification)

ON_COMMAND(ID_SYSTEMMAINTENANCE_FATCAFILINGDETAIL, OnFATCAFilingDetail)
ON_UPDATE_COMMAND_UI(ID_SYSTEMMAINTENANCE_FATCAFILINGDETAIL, OnUpdateFATCAFilingDetail)

ON_COMMAND(ID_ACCOUNTLEVELMAINTENANCE_GROUPINGINFORMATION, OnAccountHouseholdInfo)
ON_UPDATE_COMMAND_UI(ID_ACCOUNTLEVELMAINTENANCE_GROUPINGINFORMATION, OnUpdateAccountHouseholdInfo)

ON_COMMAND(ID_FUNDLEVELMAINTENANCE_FUND_RULES_MAINTENANCE, OnFundRulesMaintenance)
ON_UPDATE_COMMAND_UI(ID_FUNDLEVELMAINTENANCE_FUND_RULES_MAINTENANCE, OnUpdateFundRulesMaintenance)

ON_COMMAND(ID_BROKERLEVELMAINTENANCE_TRANSFEROFACCOUNTS, OnTransferAccounts)
ON_UPDATE_COMMAND_UI(ID_BROKERLEVELMAINTENANCE_TRANSFEROFACCOUNTS, OnUpdateTransferAccounts)

ON_COMMAND(ID_SYSTEMMAINTENANCE_FUND_GROUP, OnFundGroup)
ON_UPDATE_COMMAND_UI(ID_SYSTEMMAINTENANCE_FUND_GROUP, OnUpdateFundGroup)

ON_COMMAND(ID_SYSTEMMAINTENANCE_FUND_BROKER_LINKAGE, OnFundBrokerLinkage)
ON_UPDATE_COMMAND_UI(ID_SYSTEMMAINTENANCE_FUND_BROKER_LINKAGE, OnUpdateFundBrokerLinkage)

ON_COMMAND(IDM_REGLAN_REGPLAN, OnRegPlanTransfer )
ON_UPDATE_COMMAND_UI(IDM_REGLAN_REGPLAN, OnUpdateRegPlanTransfer)

ON_COMMAND(ID_BROKERLEVELMAINTENANCE_REGULATORY_AGREEMENT_MAINTENANCE, OnRegulatoryAgreement)
ON_UPDATE_COMMAND_UI(ID_BROKERLEVELMAINTENANCE_REGULATORY_AGREEMENT_MAINTENANCE, OnUpdateRegulatoryAgreement)

ON_COMMAND(ID_BROKERLEVELMAINTENANCE_BROKERLEVELCUT, OnBrokerCutOff)
ON_UPDATE_COMMAND_UI(ID_BROKERLEVELMAINTENANCE_BROKERLEVELCUT, OnUpdateBrokerCutOff)

ON_COMMAND(ID_SYSTEMMAINTENANCE_EXTERNALTAFUNDLINKA, OnExternalTAFundLinkage)
ON_UPDATE_COMMAND_UI(ID_SYSTEMMAINTENANCE_EXTERNALTAFUNDLINKA, OnUpdateExternalTAFundLinkage)

ON_COMMAND(ID_SYSTEMMAINTENANCE_REPORTABLEACCOUNTSEXTRACT, OnRegAcctExtr)
ON_UPDATE_COMMAND_UI(ID_SYSTEMMAINTENANCE_REPORTABLEACCOUNTSEXTRACT, OnUpdateRegAcctExtr)

ON_COMMAND(ID_ACCOUNTLEVELMAINTENANCE_REPORTABLEINFORMATIONREVIEW, OnRegAcctInfoRev)
ON_UPDATE_COMMAND_UI(ID_ACCOUNTLEVELMAINTENANCE_REPORTABLEINFORMATIONREVIEW, OnUpdateRegAcctInfoRev)

ON_COMMAND(ID_SYSTEMMAINTENANCE_WITHHOLDINGTAXRATESMAINTENANCE, OnWithholdingTaxRatesMaintenance)
ON_UPDATE_COMMAND_UI(ID_SYSTEMMAINTENANCE_WITHHOLDINGTAXRATESMAINTENANCE, OnUpdateWithholdingTaxRatesMaintenance)

ON_COMMAND(ID_SYSTEMMAINTENANCE_FUNDDISTRIBUTIONSPLITMAINTENANCE, OnFundDistributionSplitMaintenance)
ON_UPDATE_COMMAND_UI(ID_SYSTEMMAINTENANCE_FUNDDISTRIBUTIONSPLITMAINTENANCE, OnUpdateFundDistributionSplitMaintenance)

ON_COMMAND(ID_INTERFACE_RDSPINTERFACETRANSACTIONS, OnRDSPInterfaceTransactions)
ON_UPDATE_COMMAND_UI(ID_INTERFACE_RDSPINTERFACETRANSACTIONS, OnUpdateRDSPInterfaceTransactions)

//}}AFX_MSG_MAP WM_KEYDOWN
ON_REGISTERED_MESSAGE(WM_WORK_EVENT, onWorkEvent)
END_MESSAGE_MAP()


//****************************************************************
class LEdit: public  CEdit
{
public:
   LEdit(){};
   ~LEdit(){};
   LEdit(CWnd* pParent,  UINT uControl )
   {
      _pParent = pParent;
      SubclassDlgItem( uControl, _pParent);

   }
   void SetAllowedChars( LPCTSTR strAllowedChars );
protected:
   //{{AFX_MSG(LEdit)
   afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
   afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()

   private:
   CString  _strAllowedChars;
   CWnd* _pParent;
};
//**********************************************************
BEGIN_MESSAGE_MAP(LEdit, CEdit)
//{{AFX_MSG_MAP(LEdit)
ON_WM_CHAR()
ON_WM_KEYDOWN()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//********************************************************************************
void LEdit::SetAllowedChars( LPCTSTR strAllowedChars )
{
   _strAllowedChars = strAllowedChars;

}

//**********************************************************************************
void LEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{


   CEdit::OnKeyDown( nChar, nRepCnt, nFlags);
}
//*********************************************************************************

void LEdit::OnChar( UINT nChar, UINT nRepCnt, UINT nFlags )
{
   if( nChar != VK_BACK && nChar != 3 && nChar != 22 )
   {
      //if the character is not allowed, return
      if( !_strAllowedChars.IsEmpty() && _strAllowedChars.Find( nChar ) == -1 )
         return;
   }
   CEdit::OnChar( nChar, nRepCnt, nFlags );
}

//******************************************************************************
// CDSTCView construction/destruction

CDSTCView::CDSTCView()
: CFormView(CDSTCView::IDD), // GenericInterface( NULL, NULL, cmd, false ),
m_pGIC( NULL ),
m_rpGIUserSession( NULL ),
m_rpGIWorkSession( NULL ),
m_rpGIFiller( NULL ),
m_bNotReady( true ),
m_bFormsContinue( true ),
m_bGetWork( false ),
m_bIdCaller( false ),
m_bIdCallerEnd( false ),
m_bIdCallerSearch( false ),
m_bClose( false ),
m_bAWD( false ),
m_bSkipAWD( false ), // PATCH
m_iNumFieldsUsedOnSearch( 0 ),
//    m_bOneSearchUsing( true ),
m_bForceAwdUpdate( false ),
m_hAccel(0),
m_ucSession( 0 ),
m_bDiscard( true ),
m_LEdit(NULL),
m_dwHtmlHelpCookie( 0 ),
m_bCallStart(false),
m_mfdstcDDEServer (0),
m_bManualSmartForm (false),
m_bDskNasu (false),
m_workEventAgent()

{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   //{{AFX_DATA_INIT(CDSTCView)
   //}}AFX_DATA_INIT
//
// Disables memory tracking when in debug mode so the application will close
// faster
//
   AfxEnableMemoryTracking( FALSE );
   ::HtmlHelp(NULL, NULL, HH_INITIALIZE, (DWORD)&m_dwHtmlHelpCookie);
   ifsupp::SetMgmtCoInfoCallback(getMgmtCoInfo);
   ifsupp::SetStatusBarKicker(kickStatusBar);
}

//******************************************************************************

CDSTCView::~CDSTCView()
{
   TRACE_DESTRUCTOR( CLASSNAME );

   delete m_pGIC;
   delete m_LEdit;
   m_pGIC = NULL;
   if (m_mfdstcDDEServer)
   {
      delete m_mfdstcDDEServer;
      m_mfdstcDDEServer = NULL;
   }
   ::HtmlHelp(NULL, NULL, HH_CLOSE_ALL, 0);
   ::HtmlHelp(NULL, NULL, HH_UNINITIALIZE, (DWORD)m_dwHtmlHelpCookie);
}

//******************************************************************************

void CDSTCView::DoDataExchange(CDataExchange* pDX)
{
   CFormView::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(CDSTCView)
   DDX_Control(pDX, IDC_LBL_AREA_CODE, m_lblAreaCode);
   DDX_Control(pDX, IDC_EDT_AREA_CODE, m_edtAreaCode);
   DDX_Control(pDX, IDC_BTN_REMARKS, m_btnRemarks);
   DDX_Control(pDX, IDC_BTN_HARNESS, m_btnHarness);
   DDX_Control(pDX, IDC_BTN_DETAILS, m_btnDetails);
   DDX_Control(pDX, IDC_BTN_FINANCIAL, m_btnFinancial);
   DDX_Control(pDX, IDC_BTN_FUND, m_btnFund);
   DDX_Control(pDX, IDC_BTN_FYI, m_btnFYI);
   DDX_Control(pDX, IDC_BTN_END, m_btnEnd);
   DDX_Control(pDX, IDC_BTN_GETWORK, m_btnGetWork);
   DDX_Control(pDX, IDC_BTN_IDCALLER, m_btnIdCaller);
   DDX_Control(pDX, IDC_BTN_SEARCH, m_btnSearch);
   DDX_Control(pDX, IDC_TXT_NAME, m_txtName);
   DDX_Control(pDX, IDC_TXT_RELATIONSHIP, m_txtRelation);
   DDX_Control(pDX, IDC_TXT_PHONE, m_txtPhone);
   DDX_Control(pDX, IDC_TXT_PHONE2, m_txtPhone2);
   DDX_Control(pDX, IDC_TXT_TIMEOFCALL, m_txtTime);
   DDX_Control(pDX, IDC_CMB_USING, m_cmbUsing);
   DDX_Control(pDX, IDC_CMB_SEARCH, m_cmbSearch);
// DDX_Control(pDX, IDC_EDT_SEARCH3, m_edtSearch3);
   DDX_Control(pDX, IDC_EDT_SEARCH2, m_edtSearch2);
   DDX_Control(pDX, IDC_EDT_SEARCH1, m_edtSearch1);
   DDX_Control(pDX, IDC_LBL_SEARCH3, m_lblSearch3);
   DDX_Control(pDX, IDC_LBL_SEARCH2, m_lblSearch2);
   DDX_Control(pDX, IDC_LBL_SEARCH1, m_lblSearch1);
   DDX_Control(pDX, IDC_BTN_NEW, m_btnNew);
   DDX_Control(pDX, IDC_TXT_EXT, m_txtExt);
   DDX_Control(pDX, IDC_BTN_STLMENT, m_btnSettlement);
   DDX_Control(pDX, IDC_BTN_GLOBAL_SEARCH, m_btnGlobalSearch);
   //}}AFX_DATA_MAP
}

//******************************************************************************
// CDSTCView diagnostics

#ifdef _DEBUG
void CDSTCView::AssertValid() const
{
   CFormView::AssertValid();
}

void CDSTCView::Dump(CDumpContext& dc) const
{
   CFormView::Dump(dc);
}

DSTCDoc* CDSTCView::GetDocument() // non-debug version is inline
{
   ASSERT( m_pDocument->IsKindOf( RUNTIME_CLASS( DSTCDoc ) ) );
   return( DSTCDoc * )m_pDocument;
}
#endif //_DEBUG

//******************************************************************************
// Message handlers
//******************************************************************************

void CDSTCView::moveDialog( void )
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, MOVEDIALOG );
   CWnd                *pCWDesk = GetDesktopWindow( ); // Desktop window
   CWnd                *pParent;           // Our parent
   WINDOWPLACEMENT     wpDesk;             // Desktop location
   WINDOWPLACEMENT     wpRoad;             // Our location
   long                lWidth;
   long                lHeight;

   // Get the coordinates for both the Desktop and us
   pParent = GetParent();
   pCWDesk->GetWindowPlacement( &wpDesk );
   pParent->GetWindowPlacement( &wpRoad );

   // Set the window 10 from top, 10 from right side
   lWidth = wpRoad.rcNormalPosition.right - wpRoad.rcNormalPosition.left;
   lHeight = wpRoad.rcNormalPosition.bottom - wpRoad.rcNormalPosition.top;

   wpRoad.rcNormalPosition.right = wpDesk.rcNormalPosition.right - 10;
   wpRoad.rcNormalPosition.left = wpRoad.rcNormalPosition.right - lWidth;

   wpRoad.rcNormalPosition.top = 10;
   wpRoad.rcNormalPosition.bottom = lHeight + 10;

   // We know where we're supposed to be, put 'er there
   pParent->SetWindowPlacement( &wpRoad );
}

//*****************************************************************************

bool CDSTCView::getSignOn( void )
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, GETSIGNON );
   bool bRtn = false;
   E_COMMANDRETURN eRtn;

   CWaitCursor wait;

   try
   {
      // We control the lifetime of this process and use it as parent for
      //  worksession processes who are in turn parents for most other processes
      //  we might kick off.  Note we keep the pointer to this process around for
      //  later reference, but it gets cleaned up automatically by the
      //  GuiInterfaceContainer when the user shuts down.  If we allow other users
      //  to logon in midstream this would have to change.

      m_pGIC = new GenericInterfaceContainer(  );

      eRtn = CommandDispatcher::getInstance()->invokeCommand( m_pGIC,
                                                              NULL,
                                                              CMD_BPROC_USER_SESSION,
                                                              PROC_NO_TYPE,
                                                              false,
                                                              &m_rpGIUserSession );

      switch( eRtn )
      {
         case CMD_MODELESS_INPROCESS:
            // Successful
            profileInitialization();
            bRtn = true;
            break;
         case CMD_CANCEL:
            // User cancelled
            break;
         default:
            // Display error
            ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
            break;
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

   return(bRtn);
}

//*****************************************************************************

void CDSTCView::getRegistry( void )
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, GETREGISTRY );

   // Get and save the Registry location
   m_strFileDir = GetConfigValueAsString( CONFIGURATION_CONSTANTS::MFDSTC,
                                          CONFIGURATION_CONSTANTS::DataPath, CONFIGURATION_CONSTANTS::Path );
   m_rpGIUserSession->setGlobal( USER_GLOBAL, ifds::Registry_Directory, m_strFileDir );
}

//******************************************************************************

void CDSTCView::profileInitialization( void )
{
   TRACE_METHOD( CLASSNAME, PROFILEINITIALIZATION )

   ConfigManager *pSessionMgr = ConfigManager::getManager( SessionTags::Session );
   Configuration cfgRoadOptions = pSessionMgr->retrieveConfig( SessionTags::DSTCMFOptions );

   DString dstrUserID;
   DString dstrProfile;
   DString dstrExt;

   m_rpGIUserSession->getField( NULL, USERID, dstrUserID );

   m_rpGIUserSession->getGlobal( USER_GLOBAL, ifds::Profile, dstrProfile );
   // Initialization based on session
   m_rpGIUserSession->getGlobal( USER_GLOBAL, ifds::Operator_Extension, dstrExt );
   m_rpGIUserSession->getSession()->setGlobalSessionData( SessionTags::OperatorExtension, dstrExt );
   //TODO - This session tag is road runner specific - why does infrastructure define it?
   m_rpGIUserSession->getSession()->setGlobalSessionData( SessionTags::TA2K_ID, m_strOPID );
   m_rpGIUserSession->getSession()->setGlobalSessionData(  SessionTags::System, LPCTSTR( m_csSystem ) );

   // Are they using AWD?  Enable/disable Forms and EnCorr menu options, and
   // "GetWork" button based on whether AWD is being used
   Configuration cfgAWD = pSessionMgr->retrieveConfig( SessionTags::USE_AWD );
   DString dstrUseAwd = cfgAWD.getValueAsString( SessionTags::USE_AWD ).stripAll( I_CHAR('\t') );

   m_bAWD = ( !dstrUseAwd.empty() ) && ( dstrUseAwd[0] == 'Y' );
   m_rpGIUserSession->setGlobal( USER_GLOBAL, ifds::Using_AWD, ( m_bAWD ? I_( "1" ) : I_( "0" ) ) );

   DString dstrUseAwdPortal = cfgAWD.getValueAsString( SessionTags::USE_AWD_PORTAL ).stripAll( I_CHAR('\t') );
   bool bAWDPortal = ( !dstrUseAwdPortal.empty() ) && ( dstrUseAwdPortal[0] == 'Y' );
//   m_rpGIUserSession->setGlobal( USER_GLOBAL, ifds::Using_AWD_Portal, ( bAWDPortal ? I_( "1" ) : I_( "0" ) ) );

   Configuration cfgCC = pSessionMgr->retrieveConfig( SessionTags::USE_CALL_CENTRE );
   DString dstrUseCallCentre = cfgCC.getValueAsString( SessionTags::USE_CALL_CENTRE ).stripAll( I_CHAR('\t') );
   bool bCallCentre = ( !dstrUseCallCentre.empty() ) && ( dstrUseCallCentre[0] == 'Y' );

   WorkEventAgent::setUserId(dstrUserID);
   if (!m_workEventAgent && bAWDPortal) 
   {
	  DString strAWDPortalTopic = GetAWDPortalTopic();
	  m_workEventAgent.reset(WorkEventAgent::createInstance(dstrUserID, strAWDPortalTopic));
   } 
   else if (!m_workEventAgent && bCallCentre) 
   {
	  DString strCallCentreTopic = GetCallCentreTopic();
	  m_workEventAgent.reset(WorkEventAgent::createInstance(dstrUserID,  strCallCentreTopic));
   } 
   else if (m_workEventAgent && !bAWDPortal) 
   {
      m_workEventAgent.reset();
   }


   m_bGetWork = m_bAWD;

   m_btnGetWork.EnableWindow( m_bAWD );
#ifdef _HARNESS
   m_btnHarness.EnableWindow( m_bAWD );
#endif

   CMainFrame *pFrame = ( CMainFrame * )GetParent();
   pFrame->resetDynamicMenuList();
   pFrame->setAwdActive( m_bAWD );
   pFrame->setMgmCo( dynamic_cast<DSTCUserSession *>(m_rpGIUserSession->getBFSession()) );

   // Check for Automatic ID Caller
   DString dstrIDCaller = cfgRoadOptions.getValueAsString( ConfigTags::AUTOMATIC_IDCALLER ).stripAll( I_CHAR('\t') );

   int iEnd = dstrIDCaller.find( ConfigTags::IDCALLER_END );
   int iSearch = dstrIDCaller.find( ConfigTags::IDCALLER_SEARCH );

   m_bIdCallerEnd = ( DString::npos != iEnd );
   m_bIdCallerSearch = ( DString::npos != iSearch );
}

DString CDSTCView::GetAWDPortalTopic()
{
	DString strAWDPortalTopic = I_("");

	ConfigManager* pDSTCMgr = ConfigManager::getManager( CONFIGURATION_CONSTANTS::MFDSTC );
	if (pDSTCMgr != NULL)
	{
		Configuration cfgPath = pDSTCMgr->retrieveConfig( I_("Session") );
		strAWDPortalTopic = cfgPath.getValueAsString( I_("UsePortalIntegration_AWD_Topic") );
	}

	// set default topic value when there is no session node in xml configuration file
	if (strAWDPortalTopic == I_(""))
	{
		strAWDPortalTopic = I_("DTopWorkEvent_");
	}

	return strAWDPortalTopic;
}

DString CDSTCView::GetCallCentreTopic()
{
	DString strCallCentreTopic = I_("");

	ConfigManager* pDSTCMgr = ConfigManager::getManager( CONFIGURATION_CONSTANTS::MFDSTC );
	if (pDSTCMgr != NULL)
	{
		Configuration cfgPath = pDSTCMgr->retrieveConfig( I_("Session") );
		strCallCentreTopic = cfgPath.getValueAsString( I_("CallCentreIntegration_Topic") );
	}

	return strCallCentreTopic;
}


//*****************************************************************************

bool CDSTCView::enableFYI()
{
   TRACE_METHOD( CLASSNAME, ENABLEFYI );

   ConfigManager *pSessionMgr = ConfigManager::getManager( SessionTags::SESSION );
   Configuration cfgDefaults = pSessionMgr->retrieveConfig( I_("Defaults") );
   DString dstrEnableFYI = cfgDefaults.getValueAsString( I_("FYI on start") ).stripAll( I_CHAR('\t') );
   DString dstrFYIfile = GetConfigValueAsString( CONFIGURATION_CONSTANTS::MFDSTC,
                                         CONFIGURATION_CONSTANTS::DataPath,
                                         CONFIGURATION_CONSTANTS::FYIfile ).stripAll();

   return !(dstrEnableFYI == I_("N")||dstrFYIfile == I_("N"));

}

//*****************************************************************************
void CDSTCView::OnInitialUpdate()
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, ONINITIALUPDATE );
   CWaitCursor cursor;

   try
   {
      CFormView::OnInitialUpdate();

      //==>>Aug 3, 1999 beg
      LOGFONT logfont;
      CFont* pFont = GetFont();
      pFont->GetLogFont(&logfont);

      TCHAR lang[100];
      GetLocaleInfo(LOCALE_SYSTEM_DEFAULT,LOCALE_SENGCOUNTRY,lang,40);
      if( DString(lang) == I_("Japan") || DString(lang) == I_("JAN") )
      {
         pFont = new CFont();
         // create the font object
         if( !( pFont->CreateFontIndirect(&logfont) ) )
         {
            delete pFont;
            pFont = NULL;
         }
         ( (MFDSTCApp*)( AfxGetApp() ) )->SetNewFont( pFont );
      }
      //<<==Aug 3, 1999 end

      //instantiate the dstc host data manager;ilsFac
//      MFDSTCSetup::init();

//      unsigned array[ INDICATOR_COUNT ] =
//      { GUI_STATUSBAR_1, GUI_STATUSBAR_2, GUI_STATUSBAR_3, GUI_STATUSBAR_4, GUI_STATUSBAR_5 };
      if( m_statusBar.Create( GetParent() ) )
      {
/*
         m_statusBar.SetIndicators( array, INDICATOR_COUNT );
         m_statusBar.SetPaneInfo( SB_MESSAGE, m_statusBar.GetItemID( SB_MESSAGE ),
                                  SBPS_STRETCH, NULL );
         m_statusBar.SetPaneInfo( SB_PROFILE, m_statusBar.GetItemID( SB_PROFILE ),
                                  SBPS_NORMAL, 150 );
         m_statusBar.SetPaneInfo( SB_SYSTEM, m_statusBar.GetItemID( SB_SYSTEM ),
                                  SBPS_NORMAL, 55 );
         m_statusBar.SetPaneInfo( SB_MANAGEMENTCODE,
                                  m_statusBar.GetItemID( SB_MANAGEMENTCODE ), SBPS_NORMAL, 80 );
         m_statusBar.SetPaneInfo( SB_CONNECTION,
                                  m_statusBar.GetItemID( SB_CONNECTION ), SBPS_OWNERDRAW, 80 );
*/
      }
      RepositionBars( AFX_IDW_STATUS_BAR, AFX_IDW_STATUS_BAR, 0 );
      m_btnNew.EnableWindow( FALSE );    // Moved to here at request of IWS ?!?

      // Signon to mainframe
      if( !getSignOn() || m_rpGIUserSession == NULL )
      {
         sendExitMsg();
         AfxGetMainWnd()->PostMessage( WM_CLOSE );
         return;
      }

      DString dstrUserID;
      DString dstrAWDProfile;
      DString dstrMgmtCoName;
      DString dstrClientName;
      DString dstrCompanyID;

      // Get the path of the Register variable
      getRegistry();
      m_rpGIUserSession->getField( NULL, USERID, dstrUserID );
      m_rpGIUserSession->getField( NULL, AWDPROFILE, dstrAWDProfile );
      m_rpGIUserSession->getField( NULL, MGMTCONAME, dstrMgmtCoName );
      m_rpGIUserSession->getField( NULL, CLIENTNAME, dstrClientName );
      m_rpGIUserSession->getField( NULL, SYSTMGMTS, dstrCompanyID );

      DSTCUserSession* pUserSession = dynamic_cast<DSTCUserSession*>(m_rpGIUserSession->getBFSession());
      DString dstrCompanyCode = NULL_STRING;
      if( pUserSession != NULL )
      {
         DSTCGlobalSession& gs = dynamic_cast<DSTCGlobalSession&>(pUserSession->getGlobalSession());
         MgmtCo* pMgmtCo = NULL;
         MgmtCoOptions* pOptions = NULL;
         gs.findMgmtCo( dstrCompanyID, pMgmtCo );

         if(pMgmtCo && pMgmtCo->getMgmtCoOptions(pOptions) <= WARNING && 
            pOptions){
               pOptions->getField( ifds::CompanyCode, dstrCompanyCode, BF::HOST, false );
         }
         dstrCompanyCode.stripAll ().upperCase ();
      }

      m_statusBar.SetProfileStatusBar( dstrAWDProfile.c_str() );
      m_statusBar.SetManagementCodeStatusBar( dstrMgmtCoName.c_str() );
      m_statusBar.SetSystemStatusBar( dstrUserID.c_str() );
      m_statusBar.SetCompanyCodeStatusBar( dstrCompanyCode.c_str() );
      m_statusBar.SetClientNameStatusBar( dstrClientName.c_str() );

      m_LEdit =  new LEdit(this,IDC_EDT_SEARCH3);

      //fill the search criterias based on the security access
      fillAllCheckingSecurity();
      // Set the size of the Frame to match the dialog
      GetParentFrame()->RecalcLayout();
      ResizeParentToFit( FALSE );
      ResizeParentToFit( TRUE );

      moveDialog( );
      m_txtTime.SetWindowText( NULL_STRING );
      m_btnDetails.EnableWindow( FALSE );
      m_btnRemarks.EnableWindow( FALSE );
      if( enableFYI() )
      {  // Create business information dialog
         E_COMMANDRETURN eRtn = CMD_FAILURE;

         eRtn = CommandDispatcher::getInstance()->invokeCommand( m_rpGIUserSession,
                                                                 CMD_GUI_BUSINFO, PROC_NO_TYPE, false, NULL );
         if( eRtn != CMD_OK && eRtn != CMD_MODELESS_INPROCESS )
         {  // Doesn't work
            m_btnFYI.EnableWindow( FALSE );
         }
      }
      else
      {
         m_btnFYI.EnableWindow( FALSE );
      }

      // set CsiSession config path
      {
         ConfigManager *pDSTCMgr = ConfigManager::getManager( CONFIGURATION_CONSTANTS::MFDSTC );
         Configuration cfgPath = pDSTCMgr->retrieveConfig( CONFIGURATION_CONSTANTS::Csi );
         DString dstrCSIHostIP = cfgPath.getValueAsString( CONFIGURATION_CONSTANTS::Host );
         // If the CSI Host registry key is not defined, use the RTS Host IP.
         if ( dstrCSIHostIP == NULL_STRING ) {
            Configuration cfgRTSHostIP = pDSTCMgr->retrieveConfig( CONFIGURATION_CONSTANTS::RTSHost );
            dstrCSIHostIP = cfgRTSHostIP.getValueAsString( CONFIGURATION_CONSTANTS::RTSHostIP );
         }
         CsiSession::getInstance().setSessionConfig( m_hWnd,
                                                     cfgPath.getValueAsString( CONFIGURATION_CONSTANTS::Type ).asA().c_str(),
                                                     cfgPath.getValueAsString( CONFIGURATION_CONSTANTS::Param ).asA().c_str(),
                                                     dstrCSIHostIP.asA().c_str());
         DstcCsi::RegisterProcesses();
         DstcCsi::RegisterScreens();
      }

#ifdef _HARNESS
      m_btnHarness.EnableWindow( true );
      m_btnHarness.ShowWindow( SW_SHOW );
#endif
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
      sendExitMsg();
      AfxGetMainWnd()->PostMessage( WM_CLOSE );
      return;
   }
   catch( ... )
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
      AfxGetMainWnd()->PostMessage( WM_CLOSE );
      throw;
   }


   if( !m_hAccel )
      m_hAccel = LoadAccelerators( NULL, MAKEINTRESOURCE( IDR_ACCEL_MAINFRAME ) );

   // Tell them we're ready to go
   m_btnGetWork.EnableWindow( BFCPSession::usingAwd() );

   // Session
   DString dstrTitle;
   CWnd  *pWindow = NULL;
   // Set AWD Container Text if exists
   pWindow = CWnd::FindWindow( NULL, L"AWD Container" );
   if( pWindow != NULL )
   {
      CString cstrAWD;
     cstrAWD.LoadString(TXT_AWD_CONTAINER);
     dstrTitle = DString(cstrAWD);
      dstrTitle.appendInt( m_ucSession );
      pWindow->SetWindowText( CString(dstrTitle.c_str()) );
   }
   if (!m_mfdstcDDEServer)
   {
      m_mfdstcDDEServer = new MFDSTCDDEServer (m_rpGIUserSession);
   }
//start the iFastDesktop dde server...
   if (!m_mfdstcDDEServer->Create(AfxGetAppName())) {
      wchar_t buf [128];
      swprintf( buf,
                L"DDE service failed to start. Error: %d",
                m_mfdstcDDEServer->GetLastError());
      AfxMessageBox ((LPCTSTR)buf);
   }
   PostMessage( UM_READY );
}

//*****************************************************************************

LRESULT CDSTCView::ready( WPARAM wParam, LPARAM lParam )
{
   TRACE_METHOD( CLASSNAME, READY );

   // Create the Master Session - in the SYST / MGMT dialog - dmum
   if( m_bNotReady )
   {
// These lines are used to enable a com interface into this program.  Enable
// if we want to allow outside apps to drive our app.
//      OleGlobal *pOle = OleGlobal::getInstance();
//      pOle->setSearchScreenReady( this );
      m_bNotReady = FALSE;
   }

   SetForegroundWindow();

   return( TRUE );
}

//*****************************************************************************

void CDSTCView::clearScreen( void )
{
   CWaitCursor wait;
   // Clear the ID Caller stuff
/*
   m_txtTime.SetWindowText( NULL_STRING );
   CString temp;
   temp.LoadString( TXT_NAME );
   m_txtName.SetWindowText( ( LPCTSTR ) temp );
   temp.LoadString( TXT_PHONE );
   m_txtPhone.SetWindowText( ( LPCTSTR ) temp );
   temp.LoadString( TXT_EXT );
   m_txtExt.SetWindowText( ( LPCTSTR ) temp );
   temp.LoadString( TXT_RELATIONSHIP );
   m_txtRelation.SetWindowText( ( LPCTSTR ) temp );
*/
   m_btnDetails.EnableWindow( FALSE );
   m_btnRemarks.EnableWindow( FALSE );
   m_bIdCaller = FALSE;

   if( m_btnSearch.IsWindowEnabled() )
   {
      // Select the 'first' search category, and the 'first' using criteria
      if( m_cmbSearch.GetCount() > 0 &&
          m_cmbUsing.GetCount() > 0 )
      {
         m_cmbUsing.SetCurSel( 0 );
         OnSelchangeCmbUsing();
         m_cmbSearch.SetCurSel( 0 );
         OnSelchangeCmbSearch();
         resetRoadData();
      }
   }
}

//*****************************************************************************
void CDSTCView::startCall( bool bCreateCase /* = TRUE */ )
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, STARTCALL );
   //CWaitCursor wait;//there is one in the calling methods

   try
   {
      // Deactivate Remarks and Details Buttons on new search.
//      m_btnRemarks.EnableWindow (FALSE);
//      m_btnDetails.EnableWindow (FALSE);

      // If the Subsession does not exist yet, we need to get it(hence beginning the call)
//      if (( !m_rpGIWorkSession ) || (m_rpGIWorkSession && m_rpGIWorkSession->getSession() == NULL) )
      if( !m_rpGIWorkSession )
      {
         if( CommandDispatcher::getInstance()->invokeCommand( m_rpGIUserSession,
                                                              CMD_BPROC_WORK_SESSION, PROC_NO_TYPE, false, &m_rpGIWorkSession )
             != CMD_MODELESS_INPROCESS )
         {  // Error handling
            ASSERT( 0 );
            return;
         }

         m_rpGIWorkSession->setProcessObserver(this);
         m_WorkOutData = std::make_pair(Json::Value(Json::objectValue), Json::Value(Json::nullValue));

//         validateTime();

         // Create the Case - probably do this through process ?
         if( bCreateCase )
         {
            BFAwdSession *pAwdSession = NULL;
            if( m_rpGIWorkSession->getSession() != NULL )
            {
               pAwdSession = m_rpGIWorkSession->getSession()->getAwdSession();
            }

            if( pAwdSession != NULL )
            {
               BFData empty;
#ifdef AWD_BFDATA
               pAwdSession->createAwdCase( empty );
#endif
            }
         }
      }
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
      throw;
   }
}

//*****************************************************************************

void CDSTCView::OnBtnNew()
{
   CWaitCursor wait;
   if( !CanPerformSearch() ) return;

   wait.Restore();

   if( clearWorksession(m_bDiscard) )
   {
      UpdateWindow();
   }

   startCall();
   destroyBusInfo();

   doNASU();
}

//*****************************************************************************

void CDSTCView::doNASU()
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, DONASU );

   E_COMMANDRETURN eRtn = CMD_FAILURE;
   try
   {
     m_bDskNasu = true;
      m_rpGIWorkSession->setParameter( NASULIT::CREATING_SHAREHOLDER, YES );
      m_rpGIWorkSession->setParameter( NASULIT::CREATING_ACCOUNT, YES );

      eRtn = CommandDispatcher::getInstance()->invokeCommand( m_rpGIWorkSession,
                                                              CMD_BPROC_NASU, PROC_NO_TYPE, true, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
          break;
         case CMD_CANCEL:
         m_bDskNasu = false;
            break;
         default:
            ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
            break;
      }
   }
   catch( ConditionException& ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }
}

//*****************************************************************************

void CDSTCView::OnBtnDetails()
{
   TRACE_METHOD( CLASSNAME, ONBTNDETAILS );
   CWaitCursor cursor;

   // Close FYI screen
   destroyBusInfo();

   if( m_rpGIWorkSession )
   {
      GenericInterface* pGIAcctDetails = m_rpGIUserSession->getGIContainer()->findGI( m_rpGIWorkSession->getBFWorkSession(),
                                                                                      CMD_GUI_ACCOUNT_DETAILS );
      if( pGIAcctDetails )
      {
         pGIAcctDetails->modelessSetFocus( NULL );
      }
   }
}

//*****************************************************************************
void CDSTCView::OnBtnRemarks()
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, ONBTNREMARKS );
   CWaitCursor cursor;

   if( !m_btnRemarks.IsWindowEnabled() )
   {
      return;
   }
   DString dstrLastAccountNum=NULL_STRING, dstrName=NULL_STRING;
   if( m_rpGIWorkSession )
   {
      m_rpGIWorkSession->getGlobal( WORK_GLOBAL, ifds::LastActiveAccountNum, dstrLastAccountNum );
      m_rpGIWorkSession->getGlobal( WORK_GLOBAL, ifds::CallerName, dstrName );
      dstrLastAccountNum.strip();
      dstrLastAccountNum.stripLeading( '0' );
   }
   m_statusBar.SetMessageStatusBar( TXT_LOAD_REMARKS );
   if( m_rpGIWorkSession && dstrLastAccountNum != NULL_STRING )
   {
      m_rpGIWorkSession->setParameter( REMARKSLIT::ACCOUNT_NUM, dstrLastAccountNum );
      m_rpGIWorkSession->setParameter( REMARKSLIT::NAME, dstrName );
      if( CMD_MODELESS_INPROCESS != CommandDispatcher::getInstance()->invokeCommand(
                                                                                   m_rpGIWorkSession, CMD_BPROC_REMARKS, PROC_NO_TYPE, false, NULL ) )
      {  // Error processing
         ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
         m_statusBar.SetMessageStatusBar( NULL_STRING );
         return;
      }
   }
   m_statusBar.SetMessageStatusBar( NULL_STRING );
}

//*****************************************************************************

void CDSTCView::OnBtnFinancial()
{
   MAKEFRAME2 ( CND::IFASTGUI_CONDITION,
                CLASSNAME,
                ONBTNFINANCIAL
              );
   CWaitCursor cursor;

   if (m_btnFinancial.IsWindowEnabled())
   {
      startCall();
      m_statusBar.SetMessageStatusBar (TXT_LOAD_TRADES);

      DString lastAccountNum;

      if (m_rpGIWorkSession)
      {
         m_rpGIWorkSession->getGlobal (WORK_GLOBAL, ifds::LastActiveAccountNum, lastAccountNum);
         lastAccountNum.strip();
         lastAccountNum.stripLeading ('0');
         m_rpGIWorkSession->setParameter (MFCAN_IP_PARAM::ACCOUNT_NUM, lastAccountNum);
         if (CMD_MODELESS_INPROCESS !=
               CommandDispatcher::getInstance()->invokeCommand ( m_rpGIWorkSession,
                                                                 CMD_BPROC_TRADES,
                                                                 PROC_NO_TYPE,
                                                                 false,
                                                                 NULL
                                                               )
            )
         {  // Error processing
            ConditionMessageBox (FRAMEBELOW(), GETHIGHESTSEVERITY());
         }
      }
      m_statusBar.SetMessageStatusBar (NULL_STRING);
   }
}

//*****************************************************************************

void CDSTCView::onWorkType (const DString &workType)
{
   MAKEFRAME2 ( CND::IFASTGUI_CONDITION, CLASSNAME, ONBTNFINANCIAL );

   CWaitCursor    cursor;
    E_COMMANDRETURN eRtn = CMD_OK;
    DString       lastAccountNum;

    startCall();

    if (m_rpGIWorkSession)
    {
      m_rpGIWorkSession->getGlobal (WORK_GLOBAL, ifds::LastActiveAccountNum, lastAccountNum);
        lastAccountNum.strip();
        lastAccountNum.stripLeading ('0');

      m_rpGIWorkSession->setParameter (MFCAN_IP_PARAM::ACCOUNT_NUM, lastAccountNum);

      if (workType == AWD::PACWorkTypes || workType == AWD::SWPWorkTypes)
      {
         eRtn =CommandDispatcher::getInstance()->invokeCommand (m_rpGIWorkSession, CMD_BPROC_SYSTEMATIC,
                                                                   PROC_NO_TYPE, false, NULL);
      }
      else if (workType == AWD::RIFWorkTypes)
      {
         eRtn =CommandDispatcher::getInstance()->invokeCommand (m_rpGIWorkSession, CMD_BPROC_RRIF_LIF_LRIF_INFO,
                                                                 PROC_NO_TYPE, false, NULL);
      }
      else if (workType == AWD::AMSWorkTypes)
      {
         eRtn =CommandDispatcher::getInstance()->invokeCommand (m_rpGIWorkSession, CMD_BPROC_AMSACCTLVL,
                                                                   PROC_NO_TYPE, false, NULL);
      }
      else if (workType == AWD::DistribWorkTypes)
      {
         eRtn =CommandDispatcher::getInstance()->invokeCommand (m_rpGIWorkSession, CMD_BPROC_DISTRIBUTION,
                                                                   PROC_NO_TYPE, false, NULL);
      }
      else if (workType ==AWD::SettlementWorkTypes)
      {
          m_rpGIWorkSession->setParameter (FROM_SCR, I_("FromAWD"));
         eRtn =CommandDispatcher::getInstance()->invokeCommand (m_rpGIWorkSession, CMD_BPROC_SETTLEMENT,
                                                                   PROC_NO_TYPE, false, NULL);
      }
       else if (workType == AWD::TransHistoryWorkTypes)
      {
          m_rpGIWorkSession->setParameter (I_("CalledFrom"), I_("FromAWD"));
         eRtn =CommandDispatcher::getInstance()->invokeCommand (m_rpGIWorkSession, CMD_BPROC_TRANS_HISTORY,
                                                                   PROC_NO_TYPE, false, NULL);

      }

      switch (eRtn)
      {
         case CMD_OK:
         case CMD_CANCEL:
         case CMD_MODELESS_INPROCESS:
            break;

         default:
            // Display error
            ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
            break;
      }
   }
}

//*****************************************************************************
// This method can be used to avoid using a specific resource ID (IDC_BTN_END)
//  from base classes.
LRESULT CDSTCView::OnEndSession( WPARAM, LPARAM )
{
   OnBtnEndCall();
   return(FALSE);
}

//*****************************************************************************
void CDSTCView::OnBtnEndCallV()
{
   OnBtnEndCall1();
   return;
}

//*****************************************************************************
bool CDSTCView::OnBtnEndCall1()
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnEndCall1") );

   DSTCAWDSession* pSession =NULL;
   if(m_rpGIWorkSession)
   {
      pSession = dynamic_cast<DSTCAWDSession* >( m_rpGIWorkSession->getSession() );
      if( pSession )
      {
         if( !(pSession->isOrgWorkUpdated() ) && pSession->canClone() )
         {
            //display errormessage give user a choice.
               DiscardMsgDlg discardDlg(NULL, TXT_DISCARD_AWD_MSGA, TXT_DISCARD_AWD_MSGB, TXT_DISCARD,TXT_CANCELED);
            if( discardDlg.DoModal() == IDCANCEL )
               {
             return false;
            }

         }
      }
   }
   
   if (m_workEvent) {
      DiscardMsgDlg discardDlg(NULL, TXT_DISCARD_AWD_MSGA, TXT_DISCARD_AWD_MSGB, TXT_DISCARD,TXT_CANCELED);
      if( discardDlg.DoModal() == IDCANCEL )
      {
         return false;
      }
      m_workEvent->replyDone();
      m_workEvent.reset();
   }

   if( OnBtnEndCall() && pSession )
   {
      pSession->cleanupAWDObject();
   }
   return true;
 }


//*****************************************************************************

bool CDSTCView::OnBtnEndCall()
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, ONBTNEND );
   TRACE_METHOD( CLASSNAME, ONBTNEND );
   CWaitCursor cursor;

#ifdef _HARNESS
   m_btnHarness.EnableWindow( FALSE );
#endif

   try
   {
      if( m_bIdCallerEnd && !m_bIdCaller )
      {
         CommandDispatcher::getInstance()->invokeCommand( m_rpGIWorkSession,
                                                          CMD_BPROC_IDCALLER, PROC_NO_TYPE, false, NULL );
      }


      RoadComMgr::callEndOnAllActiveObjects();

      clearWorksession(true, m_bSkipAWD);
      // Close FYI screen
      destroyBusInfo();

      clearScreen( );
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
      throw;
   }

   m_btnGetWork.EnableWindow( m_bAWD && !m_bCallStart );
   m_btnIdCaller.EnableWindow( TRUE );

#ifdef _HARNESS
   m_btnHarness.EnableWindow( TRUE );
#endif

   m_bForceAwdUpdate = false;
   return(true);
}

//*****************************************************************************

void CDSTCView::sendExitMsg()
{
// Pointless message box
// I suspect that it causes the application to hang as the dialog can "get hidden" as it is not on the taskbar
// and not in the Application List.  CP 21Aug2009
//   AfxMessageBox( TXT_EXISTING_APPLICATION, MB_OK | MB_ICONSTOP );
}

//*****************************************************************************

void CDSTCView::OnBtnClose()
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, ONBTNCLOSE );
   CWaitCursor cursor;

   m_cmbSearch.ResetContent();
   m_cmbUsing.ResetContent();

   m_workEvent.reset();
   m_workEventAgent.reset();

   //destroy the worksession process
   clearWorksession();
   //destroy the usersession process
   if( m_rpGIUserSession )
   {

      if( CMD_OK != CommandDispatcher::getInstance()->invokeCommand( m_rpGIUserSession,
                                                                     CMD_BPROC_CLEANUP, PROC_NO_TYPE, true, NULL ) )
      {
         throw;
      }
      m_rpGIUserSession->getGIContainer()->destroy( m_rpGIUserSession );
      m_rpGIUserSession = NULL;
   }

   CsiSession& session = CsiSession::getInstance();
   session.closeTerminalSession();
   session.cleanup();

   RoadComMgr::releaseAllDispatches();
   // Remove the singletons
   MFDSTCSetup::exit();

   //Aug 3, 1999
   CFont *pFont = ((MFDSTCApp*)(AfxGetApp()))->GetNewFont();
   if( pFont )
   {
      pFont->DeleteObject();
      delete pFont;
      ((MFDSTCApp*)(AfxGetApp()))->SetNewFont(NULL);
   }
}

//*****************************************************************************

void CDSTCView::OnBtnFund()
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, ONBTNFUND );
   CWaitCursor wait;

   //reject the call if the button is disabled
   if( !m_btnFund.IsWindowEnabled() )
   {
      return;
   }
   startCall();
   // Close FYI screen
   destroyBusInfo();

   m_rpGIWorkSession->setParameter( FUND_CODE_VALUE, NULL_STRING );
   m_rpGIWorkSession->setParameter( CLASS_CODE_VALUE, NULL_STRING );
   m_rpGIWorkSession->setParameter( FROM_DATE_VALUE, NULL_STRING );
   m_rpGIWorkSession->setParameter( TO_DATE_VALUE, NULL_STRING );
   m_rpGIWorkSession->setParameter( PREV_DATE_PRESSED_VALUE, YES );
   m_rpGIWorkSession->setParameter( NEXT_DATE_PRESSED_VALUE, NO );
   m_statusBar.SetMessageStatusBar( TXT_LOAD_FUND_INFO );
   // Create the Fund Info dialog
   if( CMD_MODELESS_INPROCESS != CommandDispatcher::getInstance()->invokeCommand(
                                                                                m_rpGIWorkSession, CMD_BPROC_FUNDINFO, PROC_NO_TYPE, false, NULL ) )
   {  // Error processing
      ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
      m_statusBar.SetMessageStatusBar( NULL_STRING );
      return;
   }
   m_statusBar.SetMessageStatusBar( NULL_STRING );
}

//*****************************************************************************

void CDSTCView::OnBtnFYI()
{
   TRACE_METHOD( CLASSNAME, ONBTNFYI );
   CWaitCursor cursor;

   CommandDispatcher::getInstance()->invokeCommand( m_rpGIUserSession,
                                                    CMD_GUI_BUSINFO, PROC_NO_TYPE, false, NULL );
}

//*****************************************************************************

bool CDSTCView::SetUsingList( const I_CHAR * searchCriteria, const I_CHAR * selection)
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, SETUSINGLIST );
   int i, maxItems;
   DString dstrSearchItem;

   for( i = 0, maxItems = m_cmbSearch.GetCount(); i < maxItems; i++ )
   {
      dstrSearchItem = *(DString*)m_cmbSearch.GetItemData( i );
      if( dstrSearchItem.compare(searchCriteria) == 0 )
      {
         m_cmbSearch.SetCurSel(i);
         OnSelchangeCmbSearch();
         break;
      }
   }
   for( i = 0, maxItems = m_cmbUsing.GetCount(); i < maxItems; i++ )
   {
      dstrSearchItem = *(DString*)m_cmbUsing.GetItemData( i );
      if( dstrSearchItem.compare(selection) == 0 )
      {
         m_cmbUsing.SetCurSel(i);
         return(true);
      }
   }

   DString dstrLabel1;
   DString dstrLabel2;
   DString dstrErrorMsg;
   DString dstrSearchUsingList;

   m_rpGIFiller->setCurrentListItem(NULL, BFContainerId( ifds::SearchCriteria.getId() ), searchCriteria);
   m_rpGIFiller->getField( NULL, BFContainerId( ifds::SearchCriteria.getId() ), ifds::Substitute_Description, dstrSearchUsingList);
   dstrLabel1 = dstrSearchUsingList;
   m_rpGIFiller->getField( NULL, SEARCHCRITERIA::CURRENT_USING_LIST, dstrSearchUsingList);
   BFContainerId lSearchUsingList( dstrSearchUsingList.convertToULong() );
   m_rpGIFiller->setCurrentListItem(NULL, lSearchUsingList, selection);
   m_rpGIFiller->getField( NULL, lSearchUsingList, ifds::Substitute_Description, dstrLabel2);
   addIDITagValue( dstrErrorMsg, IDI_MSG,  dstrLabel1.strip() );
   addIDITagValue( dstrErrorMsg, IDI_MSG2, dstrLabel2.strip() );
   throw EXCEPTIONFROMFILEIDI( CND::GUI_SECURITY_VIOLATION, dstrErrorMsg );
}

//*****************************************************************************

void CDSTCView::getWorkDataForAccountSearch( const BFAwdData *pAwdData )
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, GETWORKDATA );
   DString  dstrBuffer, dstrValue;
   DString  dstrSystem;

   const unsigned short *apnAWDFields[] = {
      reinterpret_cast<const unsigned short *>(AWD::Account_Num),     // + Luxembourg
      reinterpret_cast<const unsigned short *>(AWD::Phoenix_Account), // Luxembourg
      reinterpret_cast<const unsigned short *>(AWD::Account_Num),
      reinterpret_cast<const unsigned short *>(AWD::Shareholder_Num),
      reinterpret_cast<const unsigned short *>(AWD::Passport_Num),
      reinterpret_cast<const unsigned short *>(AWD::Social_Num),
      reinterpret_cast<const unsigned short *>(AWD::DL_Num),
      reinterpret_cast<const unsigned short *>(AWD::SIN_Num),
      reinterpret_cast<const unsigned short *>(AWD::Birth_Cert),
      reinterpret_cast<const unsigned short *>(AWD::Credit_Card),
      reinterpret_cast<const unsigned short *>(AWD::National_ID),
      reinterpret_cast<const unsigned short *>(AWD::Other)
   };

   const unsigned short *WorkTypesField[] = {
      reinterpret_cast<const unsigned short *>(AWD::PurchWorkTypes),
      reinterpret_cast<const unsigned short *>(AWD::RedeemWorkTypes),
      reinterpret_cast<const unsigned short *>(AWD::ExchWorkTypes),
      reinterpret_cast<const unsigned short *>(AWD::TransWorkTypes),
      reinterpret_cast<const unsigned short *>(AWD::PACWorkTypes),
      reinterpret_cast<const unsigned short *>(AWD::SWPWorkTypes),
      reinterpret_cast<const unsigned short *>(AWD::RIFWorkTypes),
      reinterpret_cast<const unsigned short *>(AWD::AMSWorkTypes),
      reinterpret_cast<const unsigned short *>(AWD::DistribWorkTypes),
      reinterpret_cast<const unsigned short *>(AWD::SettlementWorkTypes),
      reinterpret_cast<const unsigned short *>(AWD::TransHistoryWorkTypes)
   };

   const unsigned short *apnSearchAccountUsing[] = {
      reinterpret_cast<const unsigned short *>(SEARCHACCOUNTUSING::ACCOUNT_NUMBER),       // + Luxembourg
      reinterpret_cast<const unsigned short *>(SEARCHACCOUNTUSING::OTHER_REFERENCE_NUMBER), // Luxembourg
      reinterpret_cast<const unsigned short *>(SEARCHACCOUNTUSING::ACCOUNT_NUMBER),
      reinterpret_cast<const unsigned short *>(SEARCHACCOUNTUSING::SHAREHOLDER_NUMBER),
      reinterpret_cast<const unsigned short *>(SEARCHACCOUNTUSING::PASSPORT),
      reinterpret_cast<const unsigned short *>(SEARCHACCOUNTUSING::SOCIAL_SECURITY_INSURANCE_CARD),
      reinterpret_cast<const unsigned short *>(SEARCHACCOUNTUSING::DRIVER_LICENSE),
      reinterpret_cast<const unsigned short *>(SEARCHACCOUNTUSING::SOCIAL_INSURANCE_NUMBER),
      reinterpret_cast<const unsigned short *>(SEARCHACCOUNTUSING::BIRTH_CERTIFICATE),
      reinterpret_cast<const unsigned short *>(SEARCHACCOUNTUSING::CREDIT_CARD),
      reinterpret_cast<const unsigned short *>(SEARCHACCOUNTUSING::NATIONAL_ID),
      reinterpret_cast<const unsigned short *>(SEARCHACCOUNTUSING::ID_OTHER)
   };

   ConfigManager *pSession = ConfigManager::getManager( SessionTags::Session );
   Configuration sysTable = pSession->retrieveConfig( SessionTags::MGMCO);
   if( sysTable.isEmpty() )
   { // MGMCO table is missing
      DISPLAYCONDITIONFROMFILE( CND::GUI_AWD_MGMCO_TABLE_MISSING );
      return;
   }
   Configuration cfgTable = pSession->retrieveConfig( SessionTags::WORK_TABLE );

   dstrBuffer = pAwdData->getUnit( );
   dstrBuffer.strip();
   dstrSystem = sysTable.getValueAsString( dstrBuffer ).stripAll( I_CHAR('\t') );

   if( dstrSystem.empty() )
   {
      DString dstrParmMsg;
      addIDITagValue( dstrParmMsg, IDI_LABEL1, dstrBuffer );
      DISPLAYCONDITIONFROMFILEIDI( CND::GUI_AWD_MGMCO_ENTRY_MISSING, dstrParmMsg );
      return;
   }
   if( DiffMgmCo( dstrSystem ) )
   {
      if( !SetMgmCo( dstrSystem ) )
      {
         DString dstrErrorMsg;
         addIDITagValue( dstrErrorMsg, IDI_MSG, dstrSystem );
         DISPLAYCONDITIONFROMFILEIDI( CND::GUI_AWD_SYSTEM_ERROR, dstrErrorMsg );
         return;
      }
   }

   // new smart form stuff:
   DString   smartForm = pAwdData->getLobValue (I_("SMRT"));
   DString    crdaValue = pAwdData->getLobValue (I_("CRDA"));

   smartForm.stripAll ().upperCase ();

   m_cmbSearch.SetCurSel( 0 );
   OnSelchangeCmbSearch();
   try
   {
      bool  bFound = false;
      short nNumberOfFields = sizeof(apnAWDFields) / sizeof(short *);
      DString dstrMarket = DSTCommonFunctions::getMarket();
      short nBeginAt = (dstrMarket == MARKET_IDS::LUXEMBOURG) ? 0 : 2;    // By Market
      short nEndAt = (dstrMarket == MARKET_IDS::LUXEMBOURG) ? 2 : nNumberOfFields;  // By Market
      for( short nCtr = nBeginAt; (nCtr < nEndAt) && !bFound; ++nCtr )
      {
         // Get the data
         DString key(reinterpret_cast<const I_CHAR*>(apnAWDFields[nCtr]));
         dstrBuffer = cfgTable.getValueAsString( key ).stripAll( I_CHAR('\t') );
         dstrValue = pAwdData->getLobValue( dstrBuffer );
         stripLeading(dstrValue, '0');

         if( !dstrValue.empty() )
         {
            if( SetUsingList(reinterpret_cast<const I_CHAR*>(SEARCHCRITERIA::ACCOUNT_SEARCH), 
                reinterpret_cast<const I_CHAR*>(apnSearchAccountUsing[nCtr])) )
            {
               OnSelchangeCmbUsing();
               GetDlgItem(IDC_EDT_SEARCH3)->SetWindowText( dstrValue.c_str() );
               bFound = true;
               break;
            }
         }
      }

      if( !bFound && !(smartForm == I_("Y")))
      {
         return;
      }

     if (smartForm == I_("Y"))
     {
      // Get Company ID
      DSTCWorkSession *dstWorkSession = NULL;
      MgmtCo *mgmtCo = NULL;
      DString dstrAccountNum;

      DSTCAWDSession* pAWDSession = NULL;
        pAWDSession = dynamic_cast<DSTCAWDSession* >( m_rpGIWorkSession->getSession() );

      onSmartForms (crdaValue);

      if (pAWDSession != NULL)
      {
         pAWDSession->getAwdField(ifds::AccountNum, dstrAccountNum);
         dstrAccountNum.stripLeading ('0');
            GetDlgItem(IDC_EDT_SEARCH3)->SetWindowText( dstrAccountNum.c_str () );
      }

      return;
     }

      CWaitCursor wait;
      DString workType;

      if (Search())
      {
        short nNumberOfFields = sizeof (WorkTypesField) / sizeof (short *);
        bool  bFound = false;

        for (short nCtr = 0; (nCtr < nNumberOfFields) && !bFound; ++nCtr)
        {
            DString workTypes = cfgTable.getValueAsString( reinterpret_cast<const I_CHAR*>(WorkTypesField [nCtr]) );

            if (!workTypes.empty())
            {
             if (m_rpGIWorkSession && m_rpGIWorkSession->getSession())
             {
                  DSTCAWDSession* pDSTCAWDSession =
                     dynamic_cast<DSTCAWDSession* >(m_rpGIWorkSession->getSession() );

                  if (pDSTCAWDSession)
                  {
                    bool bIsTrading = false;

                     workType = pAwdData->getLobValue (I_("WRKT"));

                     workType.stripAll ();
                     if (DSTCommonFunctions::codeInList (workType, workTypes))
                     {
                        bFound = true;

                        BaseAccountDetailsDlg* pAcctDetails = dynamic_cast <BaseAccountDetailsDlg*>
                           (m_rpGIUserSession->getGIContainer()->findGI (m_rpGIWorkSession->getBFWorkSession(),
                                    CMD_GUI_ACCOUNT_DETAILS));

                        if (pAcctDetails)
                        {
                           DString lastAcctNumber;
                           pAcctDetails->getParent ()->getField (m_rpGIWorkSession, IFASTBP_PROC::ACCOUNT_DETAILS_LIST,
                              ifds::AccountNum, lastAcctNumber);

                           pAcctDetails->setGlobal (WORK_GLOBAL, ifds::LastActiveAccountNum, lastAcctNumber);
                           m_rpGIWorkSession->setParameter (MFCAN_IP_PARAM::CALLER, I_("FromAWD"));

                           DString amount,
                              amtType;

                     Configuration configTable;


                           if (WorkTypesField [nCtr] == reinterpret_cast<const unsigned short *>(AWD::PurchWorkTypes))
                           {
                       configTable = pSession->retrieveConfig (I_("TRADE_TABLE"));
                              m_rpGIWorkSession->setParameter (I_("TradesTransType"), TRADETYPE::PURCHASE);
                       bIsTrading = true;
                           }
                           else if (WorkTypesField [nCtr] == reinterpret_cast<const unsigned short *>(AWD::RedeemWorkTypes))
                           {
                       configTable = pSession->retrieveConfig (I_("TRADE_TABLE"));
                              m_rpGIWorkSession->setParameter (I_("TradesTransType"), TRADETYPE::REDEMPTION);
                       bIsTrading = true;
                           }
                     else if (WorkTypesField [nCtr] == reinterpret_cast<const unsigned short *>(AWD::ExchWorkTypes))
                           {
                        configTable = pSession->retrieveConfig (I_("TRADE_TABLE"));
                        m_rpGIWorkSession->setParameter (I_("TradesTransType"), TRADETYPE::EXCHANGE);
                           bIsTrading = true;
                           }
                     else if (WorkTypesField [nCtr] == reinterpret_cast<const unsigned short *>(AWD::TransWorkTypes))
                           {
                        configTable = pSession->retrieveConfig (I_("TRADE_TABLE"));
                        m_rpGIWorkSession->setParameter (I_("TradesTransType"), TRADETYPE::TRANSFER);
                           bIsTrading = true;
                           }
                     else if (WorkTypesField [nCtr] == reinterpret_cast<const unsigned short *>(AWD::PACWorkTypes))
                     {
                        configTable = pSession->retrieveConfig (I_("SYSTEMATIC_TABLE"));
                        m_rpGIWorkSession->setParameter (I_("TransType"), I_("P")); // PAC EFT
                              m_rpGIWorkSession->setParameter (WORK_TYPE, workType);
                     }
                     else if (WorkTypesField [nCtr] == reinterpret_cast<const unsigned short *>(AWD::SWPWorkTypes))
                     {
                        configTable = pSession->retrieveConfig (I_("SYSTEMATIC_TABLE"));
                        m_rpGIWorkSession->setParameter (I_("TransType"), I_("S")); // SWP EFT
                              m_rpGIWorkSession->setParameter (WORK_TYPE, workType);
                     }
                     else if (WorkTypesField [nCtr] == reinterpret_cast<const unsigned short *>(AWD::RIFWorkTypes))
                     {
                        configTable = pSession->retrieveConfig (I_("[RIF_TABLE]"));
                        m_rpGIWorkSession->setParameter (I_("TransType"), I_("P"));
                     }
                     else if (WorkTypesField [nCtr] == reinterpret_cast<const unsigned short *>(AWD::AMSWorkTypes))
                     {
                        configTable = pSession->retrieveConfig (I_("AMS_TABLE"));
                        m_rpGIWorkSession->setParameter (I_("TransType"), I_("RB"));
                     }
                     else if (WorkTypesField [nCtr] == reinterpret_cast<const unsigned short *>(AWD::DistribWorkTypes))
                     {
                        m_rpGIWorkSession->setParameter (I_("TransType"), I_("ID"));
                     }
                     else if (WorkTypesField [nCtr] ==  reinterpret_cast<const unsigned short *>(AWD::SettlementWorkTypes) ||
                             WorkTypesField [nCtr] ==  reinterpret_cast<const unsigned short *>(AWD::TransHistoryWorkTypes))
                     {
                        configTable = pSession->retrieveConfig (I_("SETTLE_TABLE"));
                     }


                           /*Configuration tradeTableCfg = pSession->retrieveConfig (I_("TRADE_TABLE"));*/
                           Configuration lobFieldsMappingCfg = pSession->retrieveConfig (I_("UPDATE_AWD_TABLE"));
                           Configuration::iterator iter = configTable.begin();

                           DString cboFieldName,
                              awdFieldId,
                              lobValue,
                              lobFieldName;

                           while (iter != configTable.end())
                           {
                              awdFieldId = (*iter).getKey();
                              cboFieldName = configTable.getValueAsString (awdFieldId);

                              Configuration::iterator lobIter = lobFieldsMappingCfg.begin();

                              while (lobIter != lobFieldsMappingCfg.end ())
                              {
                                 if (awdFieldId == (*lobIter).getKey())
                                 {
                                    lobFieldName = lobFieldsMappingCfg.getValueAsString (awdFieldId);
                                    break;
                                 }
                                 ++lobIter;
                              }

                              if (!lobFieldName.empty())
                              {
                                 lobValue = pAwdData->getLobValue (lobFieldName);
                                 lobValue.stripLeading ('0');
                                 lobValue.strip ();
                                 if (!lobValue.empty())
                                 {
                                    if (cboFieldName == I_("Amount"))
                                    {
                                       lobValue = lobValue.left (lobValue.length () - 4) + I_(".") + lobValue.right (4);
                                    }
                                    m_rpGIWorkSession->setParameter (cboFieldName, lobValue);
                                 }
                              }
                              ++iter;
                           }

                     if (bIsTrading)
                     {
                        OnBtnFinancial ();
                     }
                     else
                     {
                        onWorkType (reinterpret_cast<const I_CHAR*>(WorkTypesField [nCtr]));
                     }

                     pAcctDetails->MoveDlg ();
                     pAcctDetails->SetForegroundWindow ();
                        }
                     }
                  }
               }
            }
        }
     }
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
      return;
   }
}

//*****************************************************************************

void CDSTCView::OnBtnGetwork()
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, ONBTNGETWORK );
   CWaitCursor cursor;

   m_btnGetWork.EnableWindow( FALSE );
   m_btnIdCaller.EnableWindow( FALSE );
#ifdef _HARNESS
   m_btnHarness.EnableWindow( FALSE );
#endif

   // If we're in the Middle of a call, end the call.
   if( m_rpGIWorkSession )
   {
      if( !OnBtnEndCall1() )
      {
         m_btnGetWork.EnableWindow( TRUE );
         return;
      }
//      cursor.Restore();
      //m_btnGetWork.EnableWindow( FALSE );
#ifdef _HARNESS
      m_btnHarness.EnableWindow( FALSE );
#endif
   }

   // Start the call and make sure it's a valid fund.  If invalid, don't do anything
   startCall( false );

   // Close FYI screen
   destroyBusInfo();

   // Get the AWD Data stuff
   if( m_rpGIWorkSession )
   {
      BFAwdSession *pAwdSession = NULL;
      if( m_rpGIWorkSession->getSession() != NULL )
      {
         pAwdSession = m_rpGIWorkSession->getSession()->getAwdSession();
      }

      if( BFAwdInterface::isLoggedOn() )
      {
         if( pAwdSession == NULL )
         {
            // We probably shouldn't get this.
            DISPLAYCONDITIONFROMFILE( CND::GUI_AWD_NO_SESSION );
            return;
         }
         try
         {
            if( pAwdSession->getAwdWork() )
            {
               // Extract and store the OBJI (Object ID) in the Session
             DSTCAWDSession* pDSTCAWDSession = dynamic_cast<DSTCAWDSession* >(m_rpGIWorkSession->getSession() );
               // Create the Case now
               BFData empty;
///#ifdef AWD_BFDATA
               pAwdSession->createAwdCase( empty );
               const BFAwdData *pAwdData = pAwdSession->getProcessWork();

               if( pDSTCAWDSession && pAwdData )
            {
               pDSTCAWDSession->retrieveObjectId();
               pDSTCAWDSession->saveCurrentObject();
            DString dstrBusArea = pAwdData->getUnit();
            pDSTCAWDSession->setAwdField ( ifds::BusinessArea, dstrBusArea.strip() );
            pDSTCAWDSession->setSessionData( I_( "BusinessArea" ), dstrBusArea );
         }
               // Get data from AWD Work Object and proceed
               getWorkDataForAccountSearch( pAwdData );
///#endif
         }
            else
            {
               m_btnIdCaller.EnableWindow( TRUE );
            }
         }
         catch( ConditionException &ce )
         {
            ConditionMessageBox( ce );
            throw;
         }
      }
      else
      {
         DISPLAYCONDITIONFROMFILE( CND::GUI_AWD_NOT_LOGGED_ON );
      }
   }
   m_btnGetWork.EnableWindow( TRUE );
   cursor.Restore();
}

//*****************************************************************************

void CDSTCView::OnBtnIdcaller()
{

   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, ONBTNIDCALLER );
   CWaitCursor cursor;

   try
   {
      // First we need to start the call and make sure it's a valid fund.
      //  If invalid, don't do anything
      startCall();

      // Close FYI screen
      destroyBusInfo();

      // Create the ID Caller dialog
      if( CMD_MODELESS_INPROCESS != CommandDispatcher::getInstance()->invokeCommand(
                                                                                   m_rpGIWorkSession, CMD_BPROC_IDCALLER, PROC_NO_TYPE, false, NULL ) )

      {  // Error processing
         ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
         return;
      }
      m_bCallStart = true;
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

//*****************************************************************************

void CDSTCView::resetRoadData( void )
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, RESETROADDATA );
   DString dstrExt;
   DString dstrProfile;

   m_rpGIUserSession->getGlobal( USER_GLOBAL, ifds::Operator_Extension, dstrExt );
   m_rpGIUserSession->getGlobal( USER_GLOBAL, ifds::Profile, dstrProfile );

   if( m_rpGIWorkSession )
   {
      m_rpGIWorkSession->clearGlobals( WORK_GLOBAL );
   }

   // TODO - after globals are really split out into separate sections in InterProcessData,
   //  the following lines should no longer be needed.
   m_rpGIUserSession->setGlobal( USER_GLOBAL, ifds::Operator_Extension, dstrExt );
   m_rpGIUserSession->setGlobal( USER_GLOBAL, ifds::Profile, dstrProfile );
   m_rpGIUserSession->setGlobal( USER_GLOBAL, ifds::Registry_Directory, m_strFileDir );
   m_rpGIUserSession->setGlobal( USER_GLOBAL, ifds::Using_AWD, ( m_bAWD ? I_( "1" ) : I_( "0" ) ) );

   if( m_rpGIWorkSession )
   {
      m_rpGIWorkSession->setGlobal( WORK_GLOBAL, ifds::Management_Co, LPCTSTR( m_csMgmt ) );
   }
}

//*****************************************************************************

void CDSTCView::OnBtnSearch( void )
{
   GetDlgItem( IDC_BTN_SEARCH )->EnableWindow( FALSE );
   CWaitCursor wait;

   if( !CanPerformSearch() )
   {
      GetDlgItem( IDC_BTN_SEARCH )->EnableWindow( TRUE );
      return;
   }


   if( clearWorksession(m_bDiscard, true, true ) )
   {
      UpdateWindow();
   }

   m_btnRemarks.EnableWindow( FALSE );
   m_btnDetails.EnableWindow( FALSE );
   wait.Restore();
   startCall();
   // Enable the Get Work if need be

   if( m_bAWD )
   {
      m_btnGetWork.EnableWindow( !m_bCallStart );
   }


#ifdef _HARNESS
   m_btnHarness.EnableWindow( TRUE );
#endif

   try
   {
      wait.Restore();
      Search();
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }

   GetDlgItem( IDC_BTN_SEARCH )->EnableWindow( TRUE );
}

//*****************************************************************************
void CDSTCView::OnBtnGlobalSearch (void)
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBtnGlobalSearch" ));
   CWaitCursor wait;

   GetDlgItem (IDC_BTN_GLOBAL_SEARCH)->EnableWindow( FALSE );

   if( !CanPerformSearch() )
   {
      GetDlgItem (IDC_BTN_GLOBAL_SEARCH)->EnableWindow (TRUE);
      return;
   }

   if (clearWorksession (m_bDiscard, true, true))
   {
      UpdateWindow();
   }

   m_btnRemarks.EnableWindow (FALSE);
   m_btnDetails.EnableWindow (FALSE);
   startCall();
   // Enable the Get Work if need be

   if (m_bAWD)
   {
      m_btnGetWork.EnableWindow( !m_bCallStart );
   }

#ifdef _HARNESS
   m_btnHarness.EnableWindow( TRUE );
#endif

   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;
      if( !m_rpGIWorkSession )//have to create a worksession
      {
         if( CommandDispatcher::getInstance()->invokeCommand( m_rpGIUserSession,
                                                              CMD_BPROC_WORK_SESSION,
                                                              PROC_NO_TYPE, false, &m_rpGIWorkSession )
               != CMD_MODELESS_INPROCESS )
            {  // Error handling
               ASSERT( 0 );
               return;
            }
      }

      DString urlParamsIDI;

      addIDITagValue (urlParamsIDI, I_("screen"),I_("GlobalSearch") );

      m_rpGIWorkSession->setParameter (I_("UrlParams"), urlParamsIDI);
     CString cstrEnvSearch;
     cstrEnvSearch.LoadString(TXT_CROSS_ENV_SEARCH);
      m_rpGIWorkSession->setParameter (I_("BrowserTitle"), DString(cstrEnvSearch));

      GenericInterface *rpGIBrowser (NULL);
      eRtn = CommandDispatcher::getInstance()->invokeCommand (m_rpGIWorkSession,
                                                              CMD_BPROC_GLOBAL_SEARCH,
                                                              PROC_NO_TYPE,
                                                              true,
                                                              NULL);
      switch (eRtn)
      {
         case CMD_OK:
            {
               DString browserResults,
                  mgmcoId,
                  accountNum;


               m_rpGIWorkSession->getParameter (I_("BrowserResults"), browserResults);
               I_CHAR *temp = const_cast<I_CHAR*> (browserResults.c_str ());

               do
               {
                  DString tag,
                     value;

                  temp = parseIdiString (temp, tag, value);
                  if (I_("Env") == tag)
                  {
                     mgmcoId = value;
                  }
                  else if (I_("AccountNum") == tag)
                  {
                     accountNum = value;
                  }
               } while (temp && temp != NULL_STRING && *temp);

               if (!mgmcoId.empty() && !accountNum.empty())
               {
                  DString crtCompanyId (NULL_STRING);

                  m_rpGIUserSession->getField (NULL, SYSTMGMTS, crtCompanyId);
                  //change management company...or the same company..
                  if (SetMgmCo (mgmcoId) || crtCompanyId == mgmcoId)
                  {
                     //search for account...
                     m_cmbUsing.SetCurSel (0);
                     OnSelchangeCmbUsing ();
                     m_cmbSearch.SetCurSel (0);
                     OnSelchangeCmbSearch ();
                     m_iNumFieldsUsedOnSearch = 1;
                     GetDlgItem (IDC_EDT_SEARCH3)->SetWindowText (accountNum.c_str());
                     OnBtnSearch ();
                  }
               }
            }
            break;
         case CMD_MODELESS_INPROCESS:
            break;
         case CMD_CANCEL:
            break;
         default:
            // Display error
            ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
            break;
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

   GetDlgItem (IDC_BTN_GLOBAL_SEARCH)->EnableWindow( TRUE );
}

//*****************************************************************************
bool CDSTCView::Search( void )
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, ONBTNSEARCH );

   E_COMMANDRETURN eRtn = CMD_FAILURE;

   // Close FYI screent
   destroyBusInfo();

   // Clear the Road Data, then put back in some essentials
   resetRoadData();
   if( m_rpGIWorkSession != NULL && m_rpGIFiller != NULL )
   {
      int searchComboNdx = m_cmbSearch.GetCurSel();
      int searchUsingNdx = m_cmbUsing.GetCurSel();

      if( searchComboNdx == CB_ERR || searchComboNdx == CB_ERRSPACE ||
          searchComboNdx >= m_cmbSearch.GetCount() ) return false;
      if( searchUsingNdx == CB_ERR || searchUsingNdx == CB_ERRSPACE ||
          searchUsingNdx >= m_cmbUsing.GetCount() ) return false;

      //read the search criterias and using keys
      DString searchCriteriaKey = *(DString*)m_cmbSearch.GetItemData( searchComboNdx );
      DString searchUsingKey = *(DString*)m_cmbUsing.GetItemData( searchUsingNdx );
      DString searchCriteriaCode;
      DString searchUsingCode;
      DString searchUsingList;

      //setting the current item for the SearchCriteria list,
      //this will set the CURRENT_USING_LIST field to the correspondent search using list
      m_rpGIFiller->setCurrentListItem( NULL, BFContainerId( ifds::SearchCriteria.getId() ), searchCriteriaKey );
      //retrive the search criteria code
      m_rpGIFiller->getField( NULL, BFContainerId( ifds::SearchCriteria.getId() ), ifds::Substitute_Code, searchCriteriaCode );
      //get the using list correspondent to the search criteria
      m_rpGIFiller->getField( NULL, SEARCHCRITERIA::CURRENT_USING_LIST, searchUsingList );
      BFContainerId lSearchUsingList( searchUsingList.convertToULong() );
      //set the current item into the using list
      m_rpGIFiller->setCurrentListItem( NULL, lSearchUsingList, searchUsingKey );
      //get the current using code for the using item
      m_rpGIFiller->getField( NULL, lSearchUsingList, ifds::Substitute_Code, searchUsingCode );
      //set the params to the search business process
      m_rpGIWorkSession->setParameter( SRCHLIT::SEARCH_CRITERIA_CODE, searchCriteriaCode );
      m_rpGIWorkSession->setParameter( SRCHLIT::SEARCH_USING_CODE, searchUsingCode );
//      if ( m_bOneSearchUsing )
      if( m_iNumFieldsUsedOnSearch == 1 )
      {
         CString firstValue, tmp1;

         GetDlgItem(IDC_EDT_SEARCH3)->GetWindowText( firstValue );
         //m_edtSearch3.GetWindowText( firstValue );
         tmp1 = firstValue;
         tmp1.TrimLeft();
         if( firstValue != NULL_STRING && tmp1 != NULL_STRING )
         {
            m_rpGIWorkSession->setParameter( SRCHLIT::FIRST_VALUE, (LPCTSTR)(firstValue) );
            m_rpGIWorkSession->setParameter( SRCHLIT::SECOND_VALUE, NULL_STRING );
            m_rpGIWorkSession->setParameter( SRCHLIT::THIRD_VALUE,  NULL_STRING );
         }
         else
         {
            DString idiStr;
            DString label1;

            m_rpGIFiller->getField( NULL, SEARCHCRITERIA::LABEL1, label1 );
            addIDITagValue( idiStr, IDI_LABEL1, label1 );
            throw EXCEPTIONFROMFILEIDI( CND::GUI_SEARCH_CRITERIAS_NOT_DEFINED1, idiStr );
            return false;
         }
      }
      else if( m_iNumFieldsUsedOnSearch == 2 )
      {
         CString firstValue, secondValue, tmp2, tmp3;
         bool wrong = false;

         if( searchUsingCode ==  SEARCHALLENTITYUSING::WHEREUSE )
         {

            DString strIdi, strTag,strValue;

            const BFDataFieldProperties*   pProp = BFDataFieldProperties::get( ifds::WhereUse );
            if (pProp)
            {
               pProp->getAllSubstituteValues (strIdi, ClientLocaleContext::get() );
               CComboBox* cb = (CComboBox* )( GetDlgItem( IDC_CMB_SEARCH1 ) );
               int iSel = cb->GetCurSel( );
               if( cb )
               {
                  I_CHAR *rpStr = const_cast< I_CHAR * >( strIdi.c_str() );
                  while( *rpStr != '\0' )
                  {
                     rpStr = parseIdiString( rpStr, strTag, strValue );
                     if( strTag != NULL_STRING  )
                     {
                        int iIndex = cb->FindString( 0,strValue.c_str() );
                        if( iIndex == iSel )
                        {
                           firstValue = strTag.c_str();
                           break;
                        }
                     }
                   }// end while
                }
             }
         }

         if( m_bAreaCodeRequired )
         {
            GetDlgItem(IDC_EDT_SEARCH3)->GetWindowText( firstValue );
            //m_edtSearch3.GetWindowText( firstValue );     // first value for number
            m_edtAreaCode.GetWindowText( secondValue ); // second value for area code
         }
       else if (searchUsingCode ==  SEARCHALLENTITYUSING::WHEREUSE)
       {
         CString cstrSearch1;
         GetDlgItem( IDC_CMB_SEARCH1 )->GetWindowText (cstrSearch1);
         DString dstrSearch1 = cstrSearch1;

         if ( dstrSearch1.stripAll ().upperCase () == I_("FUND") ||
             dstrSearch1.stripAll ().upperCase () == I_("FUNDSPONSOR"))
         {
            CString fundCode;
            GetDlgItem(IDC_EDT_SEARCH2)->GetWindowText ( fundCode );
            GetDlgItem(IDC_EDT_SEARCH2)->GetWindowText ( secondValue );
         }
		   else if( dstrSearch1.stripAll ().upperCase () == I_("REGISTRATIONAGENT"))
		   {
			   CString agentCode;
		      GetDlgItem(IDC_EDT_SEARCH2)->GetWindowText ( agentCode );
			   GetDlgItem(IDC_EDT_SEARCH2)->GetWindowText ( secondValue );
		   }
      }
      else if (searchUsingCode ==  SEARCHACCOUNTUSING::REGISTRATION_AGENT)
      {
         m_edtSearch1.GetWindowText( firstValue );
         m_edtSearch2.GetWindowText( secondValue );
         secondValue.TrimLeft();
         if(secondValue == NULL_STRING)
         {
            DString idiStr;
            DString label;

            m_rpGIFiller->getField( NULL, SEARCHCRITERIA::LABEL2, label );
            addIDITagValue( idiStr, IDI_LABEL1, label );
            throw EXCEPTIONFROMFILEIDI( CND::GUI_SEARCH_CRITERIAS_NOT_DEFINED1 , idiStr );
            return false;
         }

      }
      else if ( searchUsingKey ==  SEARCHCHEQUEUSING::ACCOUNT_NUMBER || searchUsingKey ==  SEARCHCHEQUEUSING::BROKER )
       {
         m_edtSearch1.GetWindowText( firstValue );
         DString strIdi, strTag,strValue;

            const BFDataFieldProperties*   pProp = BFDataFieldProperties::get( ifds::ChqStatus );
            if (pProp)
            {
               pProp->getAllSubstituteValues (strIdi, ClientLocaleContext::get() );
               CComboBox* cb = (CComboBox* )( GetDlgItem( IDC_CMB_SEARCH2 ) );
               int iSel = cb->GetCurSel( );
               if( cb )
               {
                  I_CHAR *rpStr = const_cast< I_CHAR * >( strIdi.c_str() );
                  while( *rpStr != '\0' )
                  {
                     rpStr = parseIdiString( rpStr, strTag, strValue );
                     if( strTag != NULL_STRING  )
                     {
                        int iIndex = cb->FindString( 0,strValue.c_str() );
                        if( iIndex == iSel )
                        {
                           secondValue = strTag.c_str();
                           break;
                        }
                     }
                   }// end while
                }
             }
      }
       else
       {
         m_edtSearch1.GetWindowText( firstValue );
         m_edtSearch2.GetWindowText( secondValue );
       }

         tmp2 = firstValue;
         tmp3 = secondValue;
         tmp2.TrimLeft();
         tmp3.TrimLeft();

         if( ( firstValue != NULL_STRING || secondValue != NULL_STRING ) &&
             ( tmp2 != NULL_STRING || tmp3 != NULL_STRING ) )
         {
            if(
              !( searchCriteriaCode == SEARCHCRITERIA::CERTIFICATE_SEARCH &&
                 ( tmp2 == NULL_STRING || tmp3 == NULL_STRING ) )
              /*&&
                 !( m_bAreaCodeRequired &&
                     ( tmp2 == NULL_STRING || tmp3 == NULL_STRING ) )//just in case we don't want to allow empty area code */
              )
            {
               m_rpGIWorkSession->setParameter( SRCHLIT::FIRST_VALUE, (LPCTSTR)(firstValue) );
               m_rpGIWorkSession->setParameter( SRCHLIT::SECOND_VALUE, (LPCTSTR)(secondValue) );
               m_rpGIWorkSession->setParameter( SRCHLIT::THIRD_VALUE,  NULL_STRING );
            }
            else
            {
               wrong = true;
            }
         }
         else
         {
            wrong = true;
         }
         if( wrong )
         {
            DString idiStr;
            DString label1;
            DString label2;

            m_rpGIFiller->getField( NULL, SEARCHCRITERIA::LABEL1, label1 );
            /*if (m_bAreaCodeRequired)
               label2 = I_("Area Code");//just in case we don't want to allow empty area code
            else*/
            m_rpGIFiller->getField( NULL, SEARCHCRITERIA::LABEL2, label2 );
            addIDITagValue( idiStr, IDI_LABEL1, label1 );
            addIDITagValue( idiStr, IDI_LABEL2, label2 );
            throw EXCEPTIONFROMFILEIDI( label2.empty() ? CND::GUI_SEARCH_CRITERIAS_NOT_DEFINED1 : CND::GUI_SEARCH_CRITERIAS_NOT_DEFINED2, idiStr );
            return false;
         }
      }
      else if( m_iNumFieldsUsedOnSearch == 3 )
      {
         CString cstrValue1, cstrValue2, cstrValue3, tmp2, tmp3;
         GetDlgItemText( IDC_EDT_SEARCH31, cstrValue1 );
         GetDlgItemText( IDC_EDT_SEARCH32, cstrValue2 );
         GetDlgItemText( IDC_EDT_SEARCH33, cstrValue3 );

         cstrValue1.TrimLeft();
         cstrValue2.TrimLeft();
         cstrValue3.TrimLeft();

         if( cstrValue1 != NULL_STRING || cstrValue2 != NULL_STRING || cstrValue3 != NULL_STRING )
         {
            m_rpGIWorkSession->setParameter( SRCHLIT::FIRST_VALUE,  (LPCTSTR)(cstrValue1 ) );
            m_rpGIWorkSession->setParameter( SRCHLIT::SECOND_VALUE, (LPCTSTR)(cstrValue2 ) );
            m_rpGIWorkSession->setParameter( SRCHLIT::THIRD_VALUE,  (LPCTSTR)(cstrValue3 ) );
         }
         else
         {
            DString idiStr;
            DString label1;
            DString label2;
            DString label3;

            m_rpGIFiller->getField( NULL, SEARCHCRITERIA::LABEL1, label1 );
            m_rpGIFiller->getField( NULL, SEARCHCRITERIA::LABEL2, label2 );
            m_rpGIFiller->getField( NULL, SEARCHCRITERIA::LABEL3, label3 );
            addIDITagValue( idiStr, IDI_LABEL1, label1 );
            addIDITagValue( idiStr, IDI_LABEL2, label2 );
            addIDITagValue( idiStr, IDI_LABEL3, label3 );
            throw EXCEPTIONFROMFILEIDI( label3.empty() ? ( label2.empty() ? CND::GUI_SEARCH_CRITERIAS_NOT_DEFINED1 : CND::GUI_SEARCH_CRITERIAS_NOT_DEFINED2 ) : CND::GUI_SEARCH_CRITERIAS_NOT_DEFINED3, idiStr );
            //throw EXCEPTIONFROMFILEIDI( CND::GUI_SEARCH_CRITERIAS_NOT_DEFINED3, idiStr );
            return false;
         }
      }

      try
      {
         //invoke the search process and set status bar message
         CString csSearchCriteria;
         DString strStatusBarMsg;

         if( m_rpGIFiller != NULL )
         {
            DString searchCriteriaDescription;

            m_rpGIFiller->setCurrentListItem( NULL, BFContainerId( ifds::SearchCriteria.getId() ), searchCriteriaCode );
            m_rpGIFiller->getField( NULL, BFContainerId( ifds::SearchCriteria.getId() ), ifds::Substitute_Description,
                                    searchCriteriaDescription );
            csSearchCriteria.Format( TXT_SEARCH_FOR_CRITERIA, searchCriteriaDescription.c_str() );
         }
         strStatusBarMsg = (LPCTSTR)csSearchCriteria;
         m_statusBar.SetMessageStatusBar( strStatusBarMsg.c_str() );
         eRtn = CommandDispatcher::getInstance()->invokeCommand(
                                                               m_rpGIWorkSession, CMD_BPROC_SEARCH, PROC_NO_TYPE, true, NULL );
         m_statusBar.SetMessageStatusBar( NULL_STRING );
         switch( eRtn )
         {
            case CMD_OK:
               //the search process can't be modeless
            case CMD_MODELESS_INPROCESS:
            case CMD_CANCEL:
               break;
            default:
               // Display error
               ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
               break;
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
   return eRtn == CMD_OK || eRtn == CMD_MODELESS_INPROCESS;
}

//*****************************************************************************

BOOL CDSTCView::PreTranslateMessage(MSG* pMsg)
{
   BOOL isTranslated = FALSE;

   if( WM_KEYDOWN == pMsg->message )
   {  // Handle the "Fx" keys for the buttons and some others - should be at app level
      switch( pMsg->wParam )
      {
         case VK_F2:
            OnBtnIdcaller();
            return(TRUE);
         case VK_F3:
            OnBtnFinancial();
            return(TRUE);
         case VK_F4:
            F4pressed();
            return(TRUE);
         case VK_F5:
            OnBtnFund();
            return(TRUE);
         case VK_F6:
            if( m_bGetWork )
            {
               OnBtnGetwork();
            }
            return(TRUE);
         case VK_F7:
            OnBtnSettlement();
            return(TRUE);
         case VK_F8:
            OnBtnRemarks();
            return(TRUE);
         case VK_F11:
            OnBtnEndCall1();
            return(TRUE);
         case VK_F12:
            OnBtnDetails();
            return(TRUE);
      }
   }

   // make certain accelerator keys are processed correctly
   if( m_hAccel )
   {
      isTranslated = ::TranslateAccelerator( m_hWnd, m_hAccel, pMsg );
   }

   return(isTranslated ? TRUE : CFormView::PreTranslateMessage(pMsg) );
}

//*****************************************************************************

void CDSTCView::OnSelchangeCmbSearch()
{
   TRACE_METHOD( CLASSNAME, ONSELCHANGECMBSEARCH );

   int searchComboNdx = m_cmbSearch.GetCurSel();
   if( searchComboNdx == CB_ERR || searchComboNdx == CB_ERRSPACE ||
       searchComboNdx >= m_cmbSearch.GetCount() ) return;

   m_cmbUsing.ResetContent();
   if( m_rpGIFiller != NULL )
   {
      DString searchCriteriaKey = *(DString*)m_cmbSearch.GetItemData( searchComboNdx );
      DString searchUsingList;
      //setting the current list item will set the CURRENT_USING_LIST field to the
      //using list that must be used
      m_rpGIFiller->setCurrentListItem( NULL, BFContainerId( ifds::SearchCriteria.getId() ), searchCriteriaKey );
      m_rpGIFiller->getField( NULL, SEARCHCRITERIA::CURRENT_USING_LIST, searchUsingList );

      BFContainerId lSearchUsingList( searchUsingList.convertToULong() );
      const DString *searchUsingKey = &m_rpGIFiller->getFirstListItemKey( NULL, lSearchUsingList );

      {
         int   iComboNdx;
         DString dstrSearchUsingDescription;
         do
         {
            m_rpGIFiller->getField( NULL, lSearchUsingList, ifds::Substitute_Description,
                                    dstrSearchUsingDescription );
            if( !(dstrSearchUsingDescription.strip() == I_("EntityID")) )
            {
               if( searchCriteriaKey == SEARCHCRITERIA::BANKING_SEARCH )
               {
                  DString dstrAccessFunctionCode( NULL_STRING ), dstrMgmtCoId;
                  DSTCUserSession *dstcUserSession = dynamic_cast<DSTCUserSession *>(m_rpGIUserSession->getBFSession());
                  m_rpGIUserSession->getField( NULL, SYSTMGMTS, dstrMgmtCoId );
                  iComboNdx = CB_ERRSPACE;
                  if( *searchUsingKey == SEARCHBANKINGUSING::BROKER_CODE )
                  {
                     dstrAccessFunctionCode = UAF::BANKING_BROKER_CODE;
                  }
                  else if( *searchUsingKey == SEARCHBANKINGUSING::BRANCH_CODE )
                  {
                     dstrAccessFunctionCode = UAF::BANKING_BRANCH_CODE;
                  }
                  else if( *searchUsingKey == SEARCHBANKINGUSING::REP_CODE )
                  {
                     dstrAccessFunctionCode = UAF::BANKING_REP_CODE;
                  }
                  else if( *searchUsingKey == SEARCHBANKINGUSING::CLIENT )
                  {
                     dstrAccessFunctionCode = UAF::BANKING_CLIENT;
                  }
                  else if( *searchUsingKey == SEARCHBANKINGUSING::FUND )
                  {
                     dstrAccessFunctionCode = UAF::BANKING_FUND;
                  }
                  /*else if (*searchUsingKey == SEARCHBANKINGUSING::FUND_CLASS)
                  {
                   dstrAccessFunctionCode = UAF::BANKING_FUND_CLASS;
                  }*/
                  if( dstrAccessFunctionCode.empty() || dstcUserSession->hasReadPermission( dstrMgmtCoId, dstrAccessFunctionCode ) )
                  {
                     iComboNdx = m_cmbUsing.AddString( dstrSearchUsingDescription.c_str() );
                  }
               }
               else
               {
                  iComboNdx = m_cmbUsing.AddString( dstrSearchUsingDescription.c_str() );
               }

               if( iComboNdx != CB_ERR && iComboNdx != CB_ERRSPACE )
               {
                  //            DString* saveKey = new DString( searchUsingKey );

                  m_cmbUsing.SetItemData( iComboNdx, (DWORD)searchUsingKey );
               }
            }
         }
         while( *( searchUsingKey = &m_rpGIFiller->getNextListItemKey( NULL, lSearchUsingList ) ) != NULL_STRING );
      }
      m_cmbUsing.SetCurSel( 0 );
      OnSelchangeCmbUsing();
   }
}
//*****************************************************************************

void  CDSTCView::checkForTelefonNo(const DString &searchCriteriaKey)
{
   TRACE_METHOD( CLASSNAME, I_("checkForTelefonNo") );
   DString strMarket = DSTCommonFunctions::getMarket();
   if( (searchCriteriaKey == SEARCHACCOUNTUSING::TELEPHONE)
       && ( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG ) )
   {
      GetDlgItem( IDC_EDT_AREA_CODE )->ShowWindow( SW_SHOW );
      GetDlgItem( IDC_LBL_AREA_CODE )->ShowWindow( SW_SHOW );
      m_bAreaCodeRequired = true;
   }
   else
   {
      GetDlgItem( IDC_EDT_AREA_CODE )->ShowWindow( SW_HIDE );
      GetDlgItem( IDC_LBL_AREA_CODE )->ShowWindow( SW_HIDE );
      m_bAreaCodeRequired = false;
   }
}

//*****************************************************************************
void CDSTCView::OnSelChangeSearch1()
{
   CString  cstrSearch1;

   GetDlgItem( IDC_CMB_SEARCH1 )->GetWindowText (cstrSearch1);
   DString dstrSearch1 = cstrSearch1;

   DString dstrLabel2;
   bool bShowSecondSearchCriteria = false;

   if ( dstrSearch1.stripAll ().upperCase () == I_("FUND"))
   {
      m_rpGIFiller->getField ( NULL, SEARCHCRITERIA::LABEL2, dstrLabel2);
      bShowSecondSearchCriteria = true;
   }
   else if ( dstrSearch1.stripAll ().upperCase () == I_("FUNDSPONSOR"))
   {
      cstrSearch1.LoadString(TXT_FUND_SPONSER);
	  dstrLabel2 = cstrSearch1;
      bShowSecondSearchCriteria = true;
   }
   else if( dstrSearch1.stripAll().upperCase () == I_("REGISTRATIONAGENT"))
   {
	  cstrSearch1.LoadString(TXT_REG_AGENT2);
	  dstrLabel2 = cstrSearch1;
	  bShowSecondSearchCriteria = true;
   }

   GetDlgItem( IDC_EDT_SEARCH2 )->ShowWindow (bShowSecondSearchCriteria);
   m_lblSearch2.SetWindowText ( dstrLabel2.c_str ());
}

//*****************************************************************************
void CDSTCView::OnSelchangeCmbUsing()
{
   TRACE_METHOD( CLASSNAME, ONSELCHANGECMBUSING );

   int searchComboNdx = m_cmbSearch.GetCurSel();
   if( searchComboNdx == CB_ERR || searchComboNdx == CB_ERRSPACE ||
       searchComboNdx >= m_cmbSearch.GetCount() ) return;

   int usingComboNdx = m_cmbUsing.GetCurSel();
   if( usingComboNdx == CB_ERR || usingComboNdx == CB_ERRSPACE ||
       usingComboNdx >= m_cmbUsing.GetCount() ) return;

   DString searchCriteriaKey = *(DString*)m_cmbSearch.GetItemData( searchComboNdx );
   DString searchUsingList;

   //
   //setting the current list item will set the CURRENT_USING_LIST field to the
   //using list that must be used
   m_rpGIFiller->setCurrentListItem( NULL, BFContainerId( ifds::SearchCriteria.getId() ), searchCriteriaKey );
   m_rpGIFiller->getField( NULL, SEARCHCRITERIA::CURRENT_USING_LIST, searchUsingList );

   BFContainerId lSearchUsingList( searchUsingList.convertToULong() );
   DString searchUsingKey = *(DString*)m_cmbUsing.GetItemData( usingComboNdx );
   //check for telephoneNo - if Canada show the Area code
   checkForTelefonNo(searchUsingKey);
   //setting the current list item will set the labels
   m_rpGIFiller->setCurrentListItem( NULL, lSearchUsingList, searchUsingKey );

   DString dstrLabel1;
   DString dstrLabel2;
   DString dstrLabel3;
   CString strColon;
   strColon.LoadString(TXT_COLON);

   m_rpGIFiller->getField( NULL, SEARCHCRITERIA::LABEL1, dstrLabel1 );
   m_rpGIFiller->getField( NULL, SEARCHCRITERIA::LABEL2, dstrLabel2 );
   m_rpGIFiller->getField( NULL, SEARCHCRITERIA::LABEL3, dstrLabel3 );

   if( searchUsingKey ==  SEARCHALLENTITYUSING::WHEREUSE )
   {
      DString strIdi, strTag,strValue;

      const BFDataFieldProperties*   pProp = BFDataFieldProperties::get( ifds::WhereUse );
      if (pProp)
       {
          pProp->getAllSubstituteValues (strIdi, ClientLocaleContext::get() );
          CComboBox* cb = (CComboBox* )( GetDlgItem( IDC_CMB_SEARCH1 ) );
          if( cb )
          {
               cb->ResetContent();
               I_CHAR *rpStr = const_cast< I_CHAR * >( strIdi.c_str() );
               while( *rpStr != '\0' )
               {
                  rpStr = parseIdiString( rpStr, strTag, strValue );
                  if( strTag != NULL_STRING && strTag != I_("02") ) // filter account here
                  {
                     cb->AddString( strValue.c_str() );
                  }
                }

            cb->SetCurSel( 0 );
          }
      }
      showSearchEditFields(2);

     m_iNumFieldsUsedOnSearch = 2;
     m_lblSearch1.SetWindowText( dstrLabel1.c_str() );
     m_lblSearch2.SetWindowText( I_("") );
   }
   else if ( searchUsingKey ==  SEARCHCHEQUEUSING::ACCOUNT_NUMBER || searchUsingKey ==  SEARCHCHEQUEUSING::BROKER )
   {
     DString strIdi, strTag,strValue;

      const BFDataFieldProperties*   pProp = BFDataFieldProperties::get( ifds::ChqStatus );
      if (pProp)
       {
          pProp->getAllSubstituteValues (strIdi, ClientLocaleContext::get() );
          CComboBox* cb = (CComboBox* )( GetDlgItem( IDC_CMB_SEARCH2 ) );
          if( cb )
          {
               cb->ResetContent();
               I_CHAR *rpStr = const_cast< I_CHAR * >( strIdi.c_str() );
               while( *rpStr != '\0' )
               {
                  rpStr = parseIdiString( rpStr, strTag, strValue );
                  cb->AddString( strValue.c_str() );
                }

            cb->SetCurSel( 0 );
          }
      }
    showSearchEditFields(2);

     m_iNumFieldsUsedOnSearch = 2;
    if (searchUsingKey ==  SEARCHCHEQUEUSING::BROKER)
      dstrLabel1 = I_("Broker Code");

    dstrLabel1 = dstrLabel1 + I_(":");
    dstrLabel2 = dstrLabel2 + I_(":");

    m_lblSearch1.SetWindowText( dstrLabel1.c_str());
    m_lblSearch2.SetWindowText( dstrLabel2.c_str());
   }
   else if( !dstrLabel3.empty() )
   {
      showSearchEditFields(3);
      dstrLabel2 += strColon;
      dstrLabel3 += strColon;

      SetDlgItemText( IDC_LBL_SEARCH31, dstrLabel1.c_str() );
      SetDlgItemText( IDC_LBL_SEARCH32, dstrLabel2.c_str() );
      SetDlgItemText( IDC_LBL_SEARCH33, dstrLabel3.c_str() );
      m_iNumFieldsUsedOnSearch = 3;
//      m_bOneSearchUsing = false;
   }
   else if( !dstrLabel2.empty() )
   {
      showSearchEditFields(2);
      dstrLabel1 += strColon;
      dstrLabel2 += strColon;
      m_lblSearch1.SetWindowText( dstrLabel1.c_str() );
      m_lblSearch2.SetWindowText( dstrLabel2.c_str() );
      m_iNumFieldsUsedOnSearch = 2;
//      m_bOneSearchUsing = false;
   }
   else if( searchUsingKey == SEARCHBANKINGUSING::CLIENT )
   {
      showSearchEditFields( 0 );
      m_lblSearch3.SetWindowText( dstrLabel1.c_str() );
      m_iNumFieldsUsedOnSearch = 0;
   }

   else
   {
      showSearchEditFields( 1 );
      DString dstrLebel;
      m_rpGIFiller->getField( NULL, SEARCHCRITERIA::LABEL1, dstrLebel,false );
      DString dstrNumber = NUMERIC_INPUT;
      if( dstrNumber.find(dstrLebel) != DString::npos && !(searchUsingKey == SEARCHENTITYUSING::CPFB_ACCT_NUM))
      //if(  dstrLebel ==  AccountNbr)
      {
         if( m_LEdit )
            m_LEdit->SetAllowedChars(_T("1234567890"));
      }
      else
      {
         if( m_LEdit )
            m_LEdit->SetAllowedChars(_T(""));
      }
      if( dstrLabel1.strip().empty() )                 //Fix temprarily for AccountNum label display
      {
         CString strAccountNum;
         strAccountNum.LoadString(TXT_ACCOUNT_NBR);
         dstrLabel1 = strAccountNum;
      }
      dstrLabel1 += strColon;
      m_lblSearch3.SetWindowText( dstrLabel1.c_str() );
      m_iNumFieldsUsedOnSearch = m_bAreaCodeRequired ? 2 : 1;
//    m_bOneSearchUsing = !m_bAreaCodeRequired;
   }
}

//*****************************************************************************
LRESULT CDSTCView::displayIdData( WPARAM wType, LPARAM lParam )
{  // Display data from IDCALLER screen  - this should be invoked through the process
   // layer somehow ??
   TRACE_METHOD( CLASSNAME, DISPLAYID );
  // CString cstrTemp, cstrCallerFullName;
  // DString dstrTemp;

   m_bIdCaller = true;
   DSTCAWDSession* pAwdSession = dynamic_cast< DSTCAWDSession* >(m_rpGIWorkSession->getSession() );
   if( pAwdSession )
   {
         DString dstrValue;
      pAwdSession->getAwdField(ifds::CallerName,dstrValue );
      m_txtName.SetWindowText( dstrValue.strip().c_str() );

      pAwdSession->getAwdField(ifds::HomePhone,dstrValue );
      m_txtPhone.SetWindowText( dstrValue.strip().c_str() );

      pAwdSession->getAwdField(ifds::BusinessPhone,dstrValue );
      m_txtPhone2.SetWindowText( dstrValue.strip().c_str() );

      pAwdSession->getAwdField(ifds::BusinessExt,dstrValue );
      m_txtExt.SetWindowText( dstrValue.strip().c_str() );

      pAwdSession->getAwdField(ifds::RelationShip,dstrValue );
      m_txtRelation.SetWindowText( dstrValue.strip().c_str() );

      pAwdSession->getAwdField(ifds::CallStartTime,dstrValue );
      m_txtTime.SetWindowText(  dstrValue.strip().c_str() );
      m_bCallStart = pAwdSession->isCallStarted();
      m_bGetWork = !m_bCallStart;
      m_btnGetWork.EnableWindow(  m_bGetWork   );


   }



 /*  // Caller Full Name
   cstrCallerFullName = ( m_rpGIWorkSession->getSession()->getSessionData( I_("CallerFullName") ) ).c_str();
   m_txtName.SetWindowText( cstrCallerFullName );

   // Caller Phone Number
   dstrTemp = m_rpGIWorkSession->getSession()->getSessionData( I_("CallerHomeNumber") );
   dstrTemp.stripTrailing().stripLeading();
   m_txtPhone.SetWindowText( dstrTemp.c_str() );

   // Caller Business Phone Number
   dstrTemp = m_rpGIWorkSession->getSession()->getSessionData( I_("CallerBusinessNumber") );
   dstrTemp.stripTrailing().stripLeading();
   m_txtPhone2.SetWindowText( dstrTemp.c_str() );

   // Caller Extension
   cstrTemp = ( m_rpGIWorkSession->getSession()->getSessionData( I_("CallerBusinessExtension") ) ).c_str();
   cstrTemp.TrimRight();
   m_txtExt.SetWindowText( cstrTemp );

   // Call Time
   dstrTemp = m_rpGIWorkSession->getSession()->getSessionData( I_("CallStartDateTime") );
   m_txtTime.SetWindowText( dstrTemp.c_str() );

   // Caller Relationship - Displayed if Caller Full Name defined.
   cstrTemp.Empty();
   if( cstrCallerFullName.IsEmpty() == FALSE )
   {
      cstrTemp = ( m_rpGIWorkSession->getSession()->getSessionData( SessionTags::CallerRelationship ) ).c_str();
   }
   m_txtRelation.SetWindowText( cstrTemp );
*/
   return(0);
}

//*****************************************************************************
LRESULT CDSTCView::launchTrading (WPARAM,LPARAM)
{
   MAKEFRAME2 ( CND::IFASTGUI_CONDITION,
                CLASSNAME,
                I_("launchTrading")
              );

   CWaitCursor wait;
   try
   {

      DString lastActiveAccountNum;
//kill the work session
      if (m_rpGIWorkSession)
      {
         m_rpGIWorkSession->getGlobal (WORK_GLOBAL, ifds::LastActiveAccountNum, lastActiveAccountNum);
         lastActiveAccountNum.stripLeading ('0');
         m_rpGIWorkSession->ok (NULL);
         m_rpGIUserSession->getGIContainer()->destroy (m_rpGIWorkSession);
         m_rpGIWorkSession = NULL;
      }
      //start a new call
      startCall();

      E_COMMANDRETURN eRtn = CMD_FAILURE;

      m_statusBar.SetMessageStatusBar (TXT_LOAD_TRADES);
      if (m_rpGIWorkSession)
      {
         m_rpGIWorkSession->setParameter (MFCAN_IP_PARAM::ACCOUNT_NUM, lastActiveAccountNum);
         switch (CommandDispatcher::getInstance()->
                     invokeCommand ( m_rpGIWorkSession,
                                     CMD_BPROC_TRADES,
                                     PROC_NO_TYPE,
                                     false,
                                     NULL
                                   )
                ) 
         {
            case CMD_OK:
            case CMD_MODELESS_INPROCESS:
            case CMD_CANCEL:
               break;
            default:
               // Display error
               ConditionMessageBox (FRAMEBELOW(), GETHIGHESTSEVERITY());
               break;
         }
      }
      else
      {
         // Display error
         ConditionMessageBox (FRAMEBELOW(), GETHIGHESTSEVERITY());
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
   m_statusBar.SetMessageStatusBar (NULL_STRING);
   return 0;
}

LRESULT CDSTCView::launchHoldingComp( WPARAM, LPARAM )
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, LAUNCHACCOUNTDETAILS );

   CWaitCursor wait;
   
   OnHoldingCompany();

   return(FALSE);
}
//*******************************************************************************
LRESULT CDSTCView::launchAccountDetails( WPARAM, LPARAM )
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, LAUNCHACCOUNTDETAILS );

   CWaitCursor wait;
   try
   {
      DString accountNum = NULL_STRING;
           DString businessArea = NULL_STRING;
     DString smartForm = I_("N");

     DSTCAWDSession  *pAwdSession = dynamic_cast< DSTCAWDSession* >(m_rpGIWorkSession->getSession() );

     if (pAwdSession && !m_bManualSmartForm && !m_bDskNasu)
     {
         pAwdSession->getAwdField(ifds::AccountNum,accountNum );
       pAwdSession->getAwdField(ifds::BusinessArea, businessArea);

       smartForm = I_("Y");
        businessArea.stripAll ().upperCase ();
     }
      else
      {
        if (m_bManualSmartForm)
        {
           smartForm = I_("Y");
        }

        m_bManualSmartForm = false;
          m_bDskNasu = false;

        if( m_rpGIWorkSession )
        {
         m_rpGIWorkSession->getGlobal( WORK_GLOBAL, ifds::LastActiveAccountNum, accountNum );
         m_rpGIWorkSession->ok( NULL );

         if (m_rpGIWorkSession != NULL)
         {
            DSTCWorkSession *dstWorkSession = NULL;
            dstWorkSession = dynamic_cast<DSTCWorkSession *>(m_rpGIWorkSession->getBFWorkSession());

            if( dstWorkSession != NULL )
            {
               dstWorkSession->getOption( ifds::CompanyCode, businessArea, BF::HOST, false);
               businessArea.stripAll ().upperCase ();
            }
         }

         //kill the work session
         m_rpGIUserSession->getGIContainer()->destroy( m_rpGIWorkSession );
         m_rpGIWorkSession = NULL;
        }
      }
      //start a new call
      startCall();

      E_COMMANDRETURN eRtn = CMD_FAILURE;

      DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(m_rpGIWorkSession->getBFWorkSession());
      AccountEntityXref *pAccountEntityXref;
      if( dstWorkSession->getAccountEntityXref( BF::HOST, pAccountEntityXref ) <= WARNING )
      {
         DString entityId;
         //get the entity id which is the account holder with sequence 1
         if( pAccountEntityXref->PopulateAccountOwner( BF::HOST, NULL_STRING, accountNum ) <= WARNING &&
             pAccountEntityXref->GetEntityIdForAccountOwnerSequence1( accountNum, BF::HOST, entityId ) <= WARNING )
         {
            m_rpGIWorkSession->setParameter( ACCDETLIT::ACCOUNT_NUMBER_FIELD, accountNum );
            m_rpGIWorkSession->setParameter( ACCDETLIT::ENTITY_ID_FIELD, entityId );
            //set the worksession process as a parent for AccDetails
            eRtn = CommandDispatcher::getInstance()->invokeCommand( m_rpGIWorkSession,
                                                                    CMD_BPROC_ACC_DETAILS, PROC_NO_TYPE, false, NULL );
            switch( eRtn )
            {
               case CMD_OK:
               case CMD_MODELESS_INPROCESS:
               if (pAwdSession)
               {
                     pAwdSession->setSessionData (I_("SMRT"), I_("N"));
               }
               OpenKYC (accountNum, businessArea, smartForm);
               break;
               case CMD_CANCEL:
                   break;
               default:
                  // Display error
                  ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
                  break;
            }
         }
         else
         {
            // Display error
            ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
         }
      }
      else
      {
         // Display error
         ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
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
   return(FALSE);
}

//******************************************************************************

LRESULT CDSTCView::newSearch( WPARAM, LPARAM )
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("newSearch") );
   try
   {
      clearWorksession();
      clearScreen( );
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }
   m_statusBar.SetMessageStatusBar( NULL_STRING );
   return(FALSE);
}

//******************************************************************************
LRESULT CDSTCView::expandCase( WPARAM wParam, LPARAM lParam )
{  // Get the case and tell it to expand itself
   TRACE_METHOD( CLASSNAME, EXPANDCASE );

   if( m_rpGIWorkSession )
   {
      BFAwdSession *pAwdSession = NULL;
      if( m_rpGIWorkSession->getSession() != NULL )
      {
         pAwdSession = m_rpGIWorkSession->getSession()->getAwdSession();
      }

      if( pAwdSession != NULL )
      {
         const BFAwdKey *pCase = pAwdSession->getAwdCase();

         if( pCase )
         {
            BFAwdInterface awd;
//                awd.expandContainerItemDown( pCase );
         }
      }
   }
   return(FALSE);
}

//*****************************************************************************
LRESULT CDSTCView::functionKeyPressed( WPARAM wParam, LPARAM lParam )
{
// This should be consolidated with PretranslateMessage stuff
   TRACE_METHOD( CLASSNAME, FUNCTIONKEYPRESSED );
   switch( wParam )
   {
      case 2:                 // F2
         OnBtnIdcaller();
         return(0);
      case 3:                 // F3
         OnBtnFinancial();
         return(0);
      case 5:                 // F5
         OnBtnFund();
         return(FALSE);
      case 6:                 // F6
         if( m_bGetWork )
         {
            OnBtnGetwork();
         }
         return(FALSE);
      case 7:
         OnBtnSettlement();      // F7
         return(FALSE);
      case 8:
         OnBtnRemarks();      // F8
         return(FALSE);
      case 10:                // F10: Set focus to us
         SetFocus();
         return(FALSE);
      case 11:                // F11
         OnBtnEndCall1();
         return(FALSE);
      case 12:                // F12
         OnBtnDetails();
         return(FALSE);
   }

   return(0);
}

//*****************************************************************************

void CDSTCView::validateTime()
{
   TRACE_METHOD( CLASSNAME, VALIDATETIME );
   CString csTime;

   // If we are initializing RoadRunner, don't do this
   if( m_bNotReady )
   {
      return;
   }

   m_txtTime.GetWindowText( csTime );

   if( !csTime.IsEmpty() )
   {
      return;
   }

   // No entered time.  Get the session time
   csTime = m_rpGIWorkSession->getSession()->getSessionData(
                                                           SessionTags::CALL_END ).c_str();

   m_txtTime.SetWindowText( csTime );
}

//*****************************************************************************

void CDSTCView::OnDestroy()
{
   TRACE_METHOD( CLASSNAME, ONDESTROY );
   CFormView::OnDestroy();
// Just want to clean up our mess   - ??????

   // From OnBtnEndCall()
   RoadComMgr::callEndOnAllActiveObjects();
   clearWorksession();
   destroyBusInfo();
   clearScreen( );
   OnBtnClose();
   if (m_mfdstcDDEServer)
   {
      m_mfdstcDDEServer-> Shutdown();
   }
}

//*****************************************************************************

void CDSTCView::OnChange( void )
{  // Change syst/mgmt
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, ONCHANGE );
   CWaitCursor cursor;
   bool bGetWork = m_rpGIWorkSession ? true : false;

   // If we are ready and we have a subsession,
   // let the operator know that we will hit the End Call button.

   if( m_rpGIWorkSession != NULL )
   {
      //check if there are screens up
      if( m_rpGIUserSession->getGIContainer()->getChildCount( m_rpGIWorkSession ) > 0 )
      {
         if( IDYES == AfxMessageBox( TXT_ACTIVE_GUI, MB_YESNO ) )
         {
            if( !OnBtnEndCall() )
               return;
         }
         else
         {
            //here we should exit because the user doesn't want
            //to close all screens
            return;
         }
      }
      else
      { //just clean up anyways.

//         AwdSession *pAwdSession = m_rpGIWorkSession->getSession()->getAwdSession();
//         if (pAwdSession)
//            if (pAwdSession->getProcessWork())
         if( !OnBtnEndCall() )
            return;
      }
   }
   if( !m_bNotReady && m_rpGIWorkSession )
   {
      //If we are getting work, just clear the screen
      if( bGetWork )
      {
         m_rpGIUserSession->getGIContainer()->destroyAll( 0 );
      }
      else
      {
// Change for internationalization ???
         if( IDNO == AfxMessageBox(TXT_DSTCVIEW_CHANGE_MSG, MB_YESNO ) )
         {
            return;
         }
         if( !OnBtnEndCall() )
            return;
      }
   }

   E_COMMANDRETURN eRtn = CommandDispatcher::getInstance()->invokeCommand(
                                                                         m_rpGIUserSession->getGIContainer(), m_rpGIUserSession, CMD_BPROC_MANAGEMENT_COMPANY, PROC_NO_TYPE, true, NULL );

   profileInitialization();
   switch( eRtn )
   {
      case CMD_MODELESS_INPROCESS:
      case CMD_OK:
         {
            DString dstrMgmtCoName;
            DString dstrAwdProfile;
            DString dstrClientName;
            DString dstrCompanyID;

            m_rpGIUserSession->getField( NULL, MGMTCONAME, dstrMgmtCoName );
            m_rpGIUserSession->getField( NULL, AWDPROFILE, dstrAwdProfile );
            m_rpGIUserSession->getField( NULL, CLIENTNAME, dstrClientName );
            m_rpGIUserSession->getField( NULL, SYSTMGMTS, dstrCompanyID );

            DSTCUserSession* pUserSession = dynamic_cast<DSTCUserSession*>(m_rpGIUserSession->getBFSession());
            DString dstrCompanyCode = NULL_STRING;
            if( pUserSession != NULL )
            {
               DSTCGlobalSession& gs = dynamic_cast<DSTCGlobalSession&>(pUserSession->getGlobalSession());
               MgmtCo* pMgmtCo = NULL;
               MgmtCoOptions* pOptions = NULL;
               gs.findMgmtCo( dstrCompanyID, pMgmtCo );

               if(pMgmtCo && pMgmtCo->getMgmtCoOptions(pOptions) <= WARNING && 
                  pOptions){
                     pOptions->getField( ifds::CompanyCode, dstrCompanyCode, BF::HOST, false );
               }
               dstrCompanyCode.stripAll ().upperCase ();
            }

            m_statusBar.SetProfileStatusBar( dstrAwdProfile.c_str() );
            m_statusBar.SetManagementCodeStatusBar( dstrMgmtCoName.c_str() );
            m_statusBar.SetCompanyCodeStatusBar( dstrCompanyCode.c_str() );
            m_statusBar.SetClientNameStatusBar( dstrClientName.c_str() );

            cursor.Restore();
            CsiSession& csiSession = CsiSession::getInstance();
            if( csiSession.IsReflectionStart() )
            {
               csiSession.executeProcess(DcCsiProcesses::CHOOSE_MANAGE_COMP);
               csiSession.clearParameters();
            }

            // Set AWD Container Text if exists
            {
               CWnd *pWindow = CWnd::FindWindow( NULL, L"AWD Container");
               DString dstrTitle;
               if( pWindow != NULL )
               {
                  dstrTitle = I_("AWD Container - ");
                  dstrTitle.appendInt( m_ucSession );
                  pWindow->SetWindowText( CString(dstrTitle.c_str()) );
               }
            }

         }
         break;
      case CMD_CANCEL:
         // User cancelled
         break;
      default:
         // Display error
         ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
         break;
   }
}

//*****************************************************************************

void CDSTCView::OnDSTC()
{
   TRACE_METHOD( CLASSNAME, ONDSTC );
   CWaitCursor cursor;

   startCall();
   CsiSession::getInstance().executeProcess( DcCsiProcesses::MASTER_MENU );

}

//*****************************************************************************
void CDSTCView::showSearchEditFields(int numFields)
{
   int show1 = numFields == 1 ? SW_SHOW : SW_HIDE;
   int show2 = numFields == 2 ? SW_SHOW : SW_HIDE;
   int show3 = numFields == 3 ? SW_SHOW : SW_HIDE;
   int show4 = numFields == 4 ? SW_SHOW : SW_HIDE;
   int usingComboNdx = m_cmbUsing.GetCurSel();

   DString searchUsingKey = *(DString*)m_cmbUsing.GetItemData( usingComboNdx );

   GetDlgItem( IDC_EDT_SEARCH3 )->ShowWindow( show1 );
   GetDlgItem( IDC_LBL_SEARCH3 )->ShowWindow( show1 );

   if( searchUsingKey ==  SEARCHALLENTITYUSING::WHEREUSE )
   {
       CString cstrWhereUse;
      bool bShow = false;

       GetDlgItem( IDC_CMB_SEARCH1 )->GetWindowText (cstrWhereUse);

      DString dstrSearch1 = cstrWhereUse;
	  if ( dstrSearch1.stripAll ().upperCase () == I_("FUND") ||
		   dstrSearch1.stripAll ().upperCase () == I_("REGISTRATIONAGENT"))
         bShow= true;

      GetDlgItem( IDC_EDT_SEARCH2 )->ShowWindow( bShow );
         GetDlgItem( IDC_EDT_SEARCH1 )->ShowWindow( false );
      GetDlgItem( IDC_CMB_SEARCH1 )->ShowWindow( show2 );
   }
   else if ( searchUsingKey ==  SEARCHCHEQUEUSING::ACCOUNT_NUMBER || searchUsingKey == SEARCHCHEQUEUSING::BROKER )
   {
      GetDlgItem( IDC_CMB_SEARCH1 )->ShowWindow( false );
      GetDlgItem( IDC_CMB_SEARCH2 )->ShowWindow( show2 );
      GetDlgItem( IDC_EDT_SEARCH1 )->ShowWindow( show2 );
      GetDlgItem( IDC_EDT_SEARCH2 )->ShowWindow( false );

   }
   else
   {
      GetDlgItem( IDC_CMB_SEARCH1 )->ShowWindow( false );
      GetDlgItem( IDC_CMB_SEARCH2 )->ShowWindow( false );
      GetDlgItem( IDC_EDT_SEARCH1 )->ShowWindow( show2 );
      GetDlgItem( IDC_EDT_SEARCH2 )->ShowWindow( show2 );
   }

   GetDlgItem( IDC_LBL_SEARCH1 )->ShowWindow( show2 );
   GetDlgItem( IDC_LBL_SEARCH2 )->ShowWindow( show2 );


   GetDlgItem( IDC_EDT_SEARCH31 )->ShowWindow( show3 );
   GetDlgItem( IDC_LBL_SEARCH31 )->ShowWindow( show3 );
   GetDlgItem( IDC_EDT_SEARCH32 )->ShowWindow( show3 );
   GetDlgItem( IDC_LBL_SEARCH32 )->ShowWindow( show3 );
   GetDlgItem( IDC_EDT_SEARCH33 )->ShowWindow( show3 );
   GetDlgItem( IDC_LBL_SEARCH33 )->ShowWindow( show3 );

   // GetDlgItem( IDC_CMB_SEARCH1 )->ShowWindow( show4 );

   SetDlgItemText( IDC_EDT_SEARCH1,    NULL_STRING );
   SetDlgItemText( IDC_EDT_SEARCH2,    NULL_STRING );
   SetDlgItemText( IDC_EDT_SEARCH3,    NULL_STRING );
   SetDlgItemText( IDC_EDT_SEARCH31,   NULL_STRING );
   SetDlgItemText( IDC_EDT_SEARCH32,   NULL_STRING );
   SetDlgItemText( IDC_EDT_SEARCH33,   NULL_STRING );
   SetDlgItemText( IDC_EDT_AREA_CODE,  NULL_STRING );

}



//*****************************************************************************

void CDSTCView::hide2EditFields()
{
   GetDlgItem( IDC_EDT_SEARCH1 )->ShowWindow( SW_HIDE );
   GetDlgItem( IDC_EDT_SEARCH2 )->ShowWindow( SW_HIDE );
   GetDlgItem( IDC_LBL_SEARCH1 )->ShowWindow( SW_HIDE );
   GetDlgItem( IDC_LBL_SEARCH2 )->ShowWindow( SW_HIDE );
   GetDlgItem( IDC_EDT_SEARCH3 )->ShowWindow( SW_SHOW );
   GetDlgItem( IDC_LBL_SEARCH3 )->ShowWindow( SW_SHOW );
   m_edtSearch1.SetWindowText( NULL_STRING );
   m_edtSearch2.SetWindowText( NULL_STRING );
   GetDlgItem(IDC_EDT_SEARCH3)->SetWindowText( NULL_STRING );
   //m_edtSearch3.SetWindowText( NULL_STRING );
   m_edtAreaCode.SetWindowText( NULL_STRING );
}

//******************************************************************************

void CDSTCView::hide1EditField()
{
   GetDlgItem( IDC_EDT_SEARCH3 )->ShowWindow( SW_HIDE );
   GetDlgItem( IDC_LBL_SEARCH3 )->ShowWindow( SW_HIDE );
   GetDlgItem( IDC_EDT_SEARCH1 )->ShowWindow( SW_SHOW );
   GetDlgItem( IDC_EDT_SEARCH2 )->ShowWindow( SW_SHOW );
   GetDlgItem( IDC_LBL_SEARCH1 )->ShowWindow( SW_SHOW );
   GetDlgItem( IDC_LBL_SEARCH2 )->ShowWindow( SW_SHOW );
   m_edtSearch1.SetWindowText( NULL_STRING );
   m_edtSearch2.SetWindowText( NULL_STRING );
   GetDlgItem(IDC_EDT_SEARCH3)->SetWindowText( NULL_STRING );
   //m_edtSearch3.SetWindowText( NULL_STRING );
   m_edtAreaCode.SetWindowText( NULL_STRING );
}

//******************************************************************************
//
// ^PRIVATE METHOD      : CDSTCView::OnCmdMsg
//
// ^DESCRIPTION :  Used for handling Dynamic Menu Items
//
// ^PARAMETERS  :
//   ^^ UINT nID -
//   ^^ int nCode -
//   ^^ void* pExtra -
//   ^^ AFX_CMDHANDLERINFO* pHandlerInfo -
//
// ^RETURNS     : BOOL -
//
// ^THROWS      : none
//
//******************************************************************************
BOOL CDSTCView::OnCmdMsg( UINT nID, int nCode, void* pExtra,
                          AFX_CMDHANDLERINFO* pHandlerInfo )
{
   // If pHandlerInfo is NULL, then handle the message
   if( pHandlerInfo == NULL )
   {
      DString strID;
      DString tmpcompanyID, tmpcompanyName;

      CMainFrame *pFrame = ( CMainFrame * )GetParent();
      CMainFrame::MenuType mt = pFrame->findDynamicMenuItem( nID, strID );

      if( CMainFrame::Undefined != mt )
      {
         if( nCode == CN_COMMAND )
         {
            CWaitCursor wait;
            startCall();
            ConfigManager *pSession = ConfigManager::getManager( SessionTags::Session );
            Configuration cfgTable = pSession->retrieveConfig( strID );
            // Handle WM_COMMAND message
            switch( mt )
            {
               case CMainFrame::TA2000:
               case CMainFrame::Forms:
                  {
                     FormsMgr *pMgr = FormsMgr::getInstance();
                     m_rpGIUserSession->getSession()->setSessionData(I_("NT Event Form"), cfgTable.getValueAsString(FORMS::FORM_NAME).stripAll( I_CHAR('\t') ) + I_( ".frm" ));
                     pMgr->start(m_hWnd, m_rpGIUserSession);
                  }
                  break;
               case CMainFrame::EnCorr:
                  {
                     EnCorrMgr *pMgr = EnCorrMgr::getInstance();
                     m_rpGIUserSession->getSession()->setSessionData(I_( "NtEnCorrEvent" ), strID);
                     pMgr->start( m_rpGIUserSession );
                  }
                  break;
               case CMainFrame::System:
                  {
                     if( DiffMgmCo(strID) )
                     {
                        if( m_rpGIWorkSession != NULL )
                        {
                           //check if there are screens up
                           if( m_rpGIUserSession->getGIContainer()->getChildCount( m_rpGIWorkSession ) > 0 )
                           {
                              if( IDYES == AfxMessageBox( TXT_ACTIVE_GUI, MB_YESNO ) )
                              {
                                 m_bSkipAWD = true;
                                 if( !OnBtnEndCall() )
                                    return(TRUE);
                                 m_bSkipAWD = false;
                                 wait.Restore();
                                 startCall();
                              }
                              else
                              {
                                 //here we should exit because the user doesn't want
                                 //to close all screens
                                 return(TRUE);
                              }
                           }
                           else
                           { //clean up anyways.
                              //                                     AwdSession *pAwdSession = m_rpGIWorkSession->getSession()->getAwdSession();
                              m_bSkipAWD = true;
                              if( !OnBtnEndCall() )
                                 return(TRUE);
                              m_bSkipAWD = false;
                              wait.Restore();
                              startCall();
                           }
                        }
                        SetMgmCo (strID);
//                               MFCommonBusinessManager *pMFCommonBM = MFCommonBusinessManager::getInstance();
//                            pMFCommonBM->EnquiryBankAtBackgroud(m_rpGIUserSession->getUserSessionID());

                     }
                  }
                  break;
            }
         }
         else if( nCode == CN_UPDATE_COMMAND_UI )
         {
            // Update UI element state
            ( (CCmdUI*)pExtra )->Enable(TRUE);
         }
         return(TRUE);
      }
   }
   if( nCode == CN_UPDATE_COMMAND_UI )
   {
      DString strMarket = DSTCommonFunctions::getMarket();
      if( nID == IDM_TAXRATES && (strMarket == MARKET_IDS::JAPAN || strMarket == MARKET_IDS::LUXEMBOURG) )
      {
         ( (CCmdUI*)pExtra )->Enable(FALSE);
         return(TRUE);
      }
   }
   return(CFormView::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo));
}

//******************************************************************************

// ying
void CDSTCView::UpdateLabels()
{
   CString cstrLabel;
   CWnd  *pWindow = NULL;

   // Session
   DString dstrTitle;
   cstrLabel.LoadString( AFX_IDS_APP_TITLE );
   if( m_ucSession )
   {
      dstrTitle = DString( cstrLabel ) + I_(" - ");
      dstrTitle.appendInt( m_ucSession );
   }
   else
   {
      do
      {
         ++m_ucSession;
         dstrTitle = DString( cstrLabel ) + I_(" - ");
         dstrTitle.appendInt( m_ucSession );
         pWindow = CWnd::FindWindow( NULL, CString(dstrTitle.c_str()) );
      } while( pWindow != NULL );
   }
   SetWindowText( CString(dstrTitle.c_str()) );

   //Aug 3, 1999
   ((CMainFrame*)AfxGetMainWnd())->SetWindowText(CString(dstrTitle.c_str()));

   cstrLabel.LoadString(BTN_IDCALLER);
   m_btnIdCaller.SetWindowText(cstrLabel);

   cstrLabel.LoadString(BTN_FINANCIAL);
   m_btnFinancial.SetWindowText(cstrLabel);

   cstrLabel.LoadString(BTN_FUND_INFO);
   m_btnFund.SetWindowText(cstrLabel);

   cstrLabel.LoadString(BTN_GET_WORK);
   m_btnGetWork.SetWindowText(cstrLabel);

   cstrLabel.LoadString(BTN_FYI);
   m_btnFYI.SetWindowText(cstrLabel);

   cstrLabel.LoadString(BTN_END);
   m_btnEnd.SetWindowText(cstrLabel);

   cstrLabel.LoadString(BTN_DETAILS);
   m_btnDetails.SetWindowText(cstrLabel);

   cstrLabel.LoadString(BTN_SEARCH);
   m_btnSearch.SetWindowText(cstrLabel);

   cstrLabel.LoadString(BTN_NEW);
   m_btnNew.SetWindowText(cstrLabel);

   cstrLabel.LoadString(BTN_REMARKS);
   m_btnRemarks.SetWindowText(cstrLabel);

   pWindow = GetDlgItem(IDC_GRP_CALLINFO);
   cstrLabel.LoadString(TXT_CALLER_INFO);
   pWindow->SetWindowText(cstrLabel);

   pWindow = GetDlgItem(IDC_GRP_SEARCH);
   cstrLabel.LoadString(TXT_SEARCH);
   pWindow->SetWindowText(cstrLabel);
/*
   pWindow = GetDlgItem(IDC_TXT_NAME);
   cstrLabel.LoadString(TXT_NAME);
   pWindow->SetWindowText(cstrLabel);

   pWindow = GetDlgItem(IDC_TXT_PHONE);
   cstrLabel.LoadString(TXT_PHONE);
   pWindow->SetWindowText(cstrLabel);

   pWindow = GetDlgItem(IDC_TXT_EXT);
   cstrLabel.LoadString(TXT_EXT);
   pWindow->SetWindowText(cstrLabel);

   pWindow = GetDlgItem(IDC_TXT_RELATIONSHIP);
   cstrLabel.LoadString(TXT_RELATIONSHIP);
   pWindow->SetWindowText(cstrLabel);

   pWindow = GetDlgItem(IDC_TXT_TIMEOFCALL);
   cstrLabel.LoadString(TXT_TIMEOFCALL);
   pWindow->SetWindowText(cstrLabel);
*/
   pWindow = GetDlgItem(IDC_TXT_SEARCH_FOR);
   cstrLabel.LoadString(TXT_SEARCH_FOR);
   pWindow->SetWindowText(cstrLabel);

   pWindow = GetDlgItem(IDC_LBL_SEARCH1);
   cstrLabel.LoadString(TXT_SEARCH1);
   pWindow->SetWindowText(cstrLabel);

   pWindow = GetDlgItem(IDC_TXT_USING);
   cstrLabel.LoadString(TXT_USING);
   pWindow->SetWindowText(cstrLabel);
}

//******************************************************************************

void CDSTCView::OnBtnHarness()
{
   CWaitCursor cursor;

   m_btnGetWork.EnableWindow( FALSE );
#ifdef _HARNESS
   m_btnHarness.EnableWindow( FALSE );
#endif

   // If we're in the Middle of a call, end the call.
   if( m_rpGIWorkSession )
   {
      OnBtnEndCall();
      cursor.Restore();
      m_btnGetWork.EnableWindow( FALSE );
#ifdef _HARNESS
      m_btnHarness.EnableWindow( FALSE );
#endif
   }

   // Start the call and make sure it's a valid fund.  If invalid, don't do anything
   startCall( false );

   // Close FYI screen
   destroyBusInfo();

   CommandDispatcher::getInstance()->invokeCommand(
                                                  m_rpGIWorkSession, CMD_GUI_LIST_SELECTION, PROC_NO_TYPE, false, NULL );
}

//******************************************************************************
/*
void CDSTCView::SetConnectionStatusBar( )
{
//   m_statusBar.setPaneInfo( SB_CONNECTION, );
   m_statusBar.UpdateWindow();
}
*/

//******************************************************************************
/*
void CDSTCView::SetManagementCodeStatusBar( const I_CHAR *mgmtCd )
{
   m_statusBar.SetPaneText( SB_MANAGEMENTCODE, mgmtCd );
   m_statusBar.UpdateWindow();
}
*/

//******************************************************************************
/*
void CDSTCView::SetMessageStatusBar( const int nID )
{
   CString cstrMsg;
   DString dstrMsg;

   cstrMsg.LoadString( nID );
   dstrMsg = (LPCTSTR)cstrMsg;
   m_statusBar.SetPaneText( SB_MESSAGE, dstrMsg.c_str() );
   m_statusBar.UpdateWindow();
}
*/
//******************************************************************************
/*
void CDSTCView::SetMessageStatusBar( const I_CHAR *msg )
{
   m_statusBar.SetPaneText( SB_MESSAGE, msg );
   m_statusBar.UpdateWindow();
}
*/
//******************************************************************************
/*
void CDSTCView::SetSystemStatusBar( const I_CHAR *sys )
{
   m_statusBar.SetPaneText( SB_SYSTEM, sys );
   m_statusBar.UpdateWindow();
}
*/
//******************************************************************************
/*
void CDSTCView::SetProfileStatusBar( const I_CHAR *profile )
{
   m_statusBar.SetPaneText( SB_PROFILE, profile );
   m_statusBar.UpdateWindow();
}
*/
//******************************************************************************

void CDSTCView::OnEncorr()
{
   CWaitCursor wait;
   startCall();
   if( BFAwdInterface::isLoggedOn() )
   {
      EnCorrMgr *pMgr = EnCorrMgr::getInstance();
      m_rpGIUserSession->getSession()->setSessionData(I_( "NtEnCorrEvent" ), NULL_STRING);
      pMgr->start( m_rpGIUserSession );
   }
}
//******************************************************************************

void CDSTCView::OnDefaultSetting()
{
   CWaitCursor wait;
   OnBtnEndCall1();
   ConfigManager *pWorkstation = ConfigManager::getManager (WORKSTATION);

   string_vector configs;
   configs = pWorkstation->configList();
   string_vector_const_iterator iter = configs.begin();
   while( iter != configs.end() )
   {
        DString dialogname = ( *iter ).c_str();
        pWorkstation->RemoveConfig( dialogname );
        iter++;
   }
}
//******************************************************************************

void CDSTCView::OnAwdHistory()
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, ONAWDHISTORY );

   if( !BFAwdInterface::isLoggedOn() || !m_bAWD )
   { // In case user is no longer logged into AWD
      m_bAWD = false;
      return;
   }

   const unsigned short *apnAWDFields[] = {
      reinterpret_cast<const unsigned short *>(AWD::Account_Num),
      reinterpret_cast<const unsigned short *>(AWD::Shareholder_Num),
      reinterpret_cast<const unsigned short *>(AWD::Passport_Num),
      reinterpret_cast<const unsigned short *>(AWD::Social_Num),
      reinterpret_cast<const unsigned short *>(AWD::DL_Num),
      reinterpret_cast<const unsigned short *>(AWD::SIN_Num),
      reinterpret_cast<const unsigned short *>(AWD::Birth_Cert),
      reinterpret_cast<const unsigned short *>(AWD::Credit_Card),
      reinterpret_cast<const unsigned short *>(AWD::National_ID),
      reinterpret_cast<const unsigned short *>(AWD::Other),
      reinterpret_cast<const unsigned short *>(AWD::Phoenix_Account)      // Luxembourg
   };

   int iSearchUsingNdx = m_cmbUsing.GetCurSel();

   if( iSearchUsingNdx == CB_ERR || iSearchUsingNdx == CB_ERRSPACE ||
       iSearchUsingNdx >= m_cmbUsing.GetCount() ) return;

   if( m_rpGIWorkSession == NULL )
   {
      CWaitCursor wait;
      startCall();
   }

   DString dstrSearchUsingCode = *(DString*) m_cmbUsing.GetItemData( iSearchUsingNdx );

   short nLookUpBy = -1;
   DString dstrMarket = DSTCommonFunctions::getMarket();
   if( dstrMarket == MARKET_IDS::LUXEMBOURG )
   {
      if( (dstrSearchUsingCode.compare(SEARCHACCOUNTUSING::ACCOUNT_NUMBER) == 0) ||
          (dstrSearchUsingCode.compare(SEARCHCHEQUEUSING::ACCOUNT_NUMBER) == 0) ||
          (dstrSearchUsingCode.compare(SEARCHCERTIFICATEUSING::ACCOUNT_NUMBER) == 0) ||
          (dstrSearchUsingCode.compare(SEARCHSYSTEMATICSUSING::ACCOUNT_NUMBER) == 0) ||
          (dstrSearchUsingCode.compare(SEARCHBANKINGUSING::ACCOUNT_NUMBER) == 0) ||
          (dstrSearchUsingCode.compare(SEARCHENTITYUSING::ACCOUNT_NUMBER) == 0) ||
          (dstrSearchUsingCode.compare(SEARCHADDRESSUSING::ACCOUNT_NUMBER) == 0) ||
          (dstrSearchUsingCode.compare(SEARCHCOAUSING::ACCOUNT_NUMBER) == 0) ||
          (dstrSearchUsingCode.compare(SEARCHDISTRIBUTIONSUSING::ACCOUNT_NUMBER) == 0) ||
          (dstrSearchUsingCode.compare(SEARCHALLOCATIONSUSING::ACCOUNT_NUMBER) == 0) ||
          (dstrSearchUsingCode.compare(SEARCHSHAREHOLDERUSING::ACCOUNT_NUMBER) == 0) ||
          (dstrSearchUsingCode.compare(SEARCHACCOUNTINFOUSING::ACCOUNT_NUMBER) == 0) )
      {
         nLookUpBy = 0;      // Added Account_Number to Lux
      }
      else if( dstrSearchUsingCode.compare(SEARCHACCOUNTUSING::OTHER_REFERENCE_NUMBER) == 0 )
      {
         nLookUpBy = 10;
      }
   }
   else
   {
      if( (dstrSearchUsingCode.compare(SEARCHACCOUNTUSING::ACCOUNT_NUMBER) == 0) ||
          (dstrSearchUsingCode.compare(SEARCHCHEQUEUSING::ACCOUNT_NUMBER) == 0) ||
          (dstrSearchUsingCode.compare(SEARCHCERTIFICATEUSING::ACCOUNT_NUMBER) == 0) ||
          (dstrSearchUsingCode.compare(SEARCHSYSTEMATICSUSING::ACCOUNT_NUMBER) == 0) ||
          (dstrSearchUsingCode.compare(SEARCHBANKINGUSING::ACCOUNT_NUMBER) == 0) ||
          (dstrSearchUsingCode.compare(SEARCHENTITYUSING::ACCOUNT_NUMBER) == 0) ||
          (dstrSearchUsingCode.compare(SEARCHADDRESSUSING::ACCOUNT_NUMBER) == 0) ||
          (dstrSearchUsingCode.compare(SEARCHCOAUSING::ACCOUNT_NUMBER) == 0) ||
          (dstrSearchUsingCode.compare(SEARCHDISTRIBUTIONSUSING::ACCOUNT_NUMBER) == 0) ||
          (dstrSearchUsingCode.compare(SEARCHALLOCATIONSUSING::ACCOUNT_NUMBER) == 0) ||
          (dstrSearchUsingCode.compare(SEARCHSHAREHOLDERUSING::ACCOUNT_NUMBER) == 0) ||
          (dstrSearchUsingCode.compare(SEARCHACCOUNTINFOUSING::ACCOUNT_NUMBER) == 0) )
      {
         nLookUpBy = 0;
      }
      else if( (dstrSearchUsingCode.compare(SEARCHACCOUNTUSING::SHAREHOLDER_NUMBER) == 0) ||
               (dstrSearchUsingCode.compare(SEARCHADDRESSUSING::SHAREHOLDER_NUMBER) == 0) ||
               (dstrSearchUsingCode.compare(SEARCHSHAREHOLDERUSING::SHAREHOLDER_NUMBER) == 0) ||
               (dstrSearchUsingCode.compare(SEARCHTRADEUSING::SHAREHOLDER_NUMBER) == 0) )
      {
         nLookUpBy = 1;
      }
      else if( (dstrSearchUsingCode.compare(SEARCHACCOUNTUSING::PASSPORT) == 0) ||
               (dstrSearchUsingCode.compare(SEARCHENTITYUSING::PASSPORT) == 0) )
      {
         nLookUpBy = 2;
      }
      else if( (dstrSearchUsingCode.compare(SEARCHACCOUNTUSING::SOCIAL_SECURITY_INSURANCE_CARD) == 0) ||
               (dstrSearchUsingCode.compare(SEARCHENTITYUSING::SOCIAL_SECURITY_INSURANCE_CARD) == 0) )
      {
         nLookUpBy = 3;
      }
      else if( (dstrSearchUsingCode.compare(SEARCHACCOUNTUSING::DRIVER_LICENSE) == 0) ||
               (dstrSearchUsingCode.compare(SEARCHENTITYUSING::DRIVER_LICENSE) == 0) )
      {
         nLookUpBy = 4;
      }
      else if( (dstrSearchUsingCode.compare(SEARCHACCOUNTUSING::SOCIAL_INSURANCE_NUMBER) == 0) ||
               (dstrSearchUsingCode.compare(SEARCHENTITYUSING::SOCIAL_INSURANCE_NUMBER) == 0) )
      {
         nLookUpBy = 5;
      }
      else if( (dstrSearchUsingCode.compare(SEARCHACCOUNTUSING::BIRTH_CERTIFICATE) == 0) ||
               (dstrSearchUsingCode.compare(SEARCHENTITYUSING::BIRTH_CERTIFICATE) == 0) )
      {
         nLookUpBy = 6;
      }
      else if( (dstrSearchUsingCode.compare(SEARCHACCOUNTUSING::CREDIT_CARD) == 0) ||
               (dstrSearchUsingCode.compare(SEARCHENTITYUSING::CREDIT_CARD) == 0) )
      {
         nLookUpBy = 7;
      }
      else if( (dstrSearchUsingCode.compare(SEARCHACCOUNTUSING::NATIONAL_ID) == 0) ||
               (dstrSearchUsingCode.compare(SEARCHENTITYUSING::NATIONAL_ID) == 0) )
      {
         nLookUpBy = 8;
      }
      else if( dstrSearchUsingCode.compare(SEARCHACCOUNTUSING::ID_OTHER) == 0 )
      {
         nLookUpBy = 9;
      }
   }
   if( nLookUpBy == -1 )
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_AWD_SEARCH_CRITERIA_INVALID );
      return;
   }

   CString cstrTemp;
   GetDlgItem(IDC_EDT_SEARCH3)->GetWindowText( cstrTemp );
   DString dstrFieldValue( cstrTemp );
   dstrFieldValue.stripAll();
   if( dstrFieldValue.empty() )
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_AWD_SEARCH_CRITERIA_INVALID );
      return;
   }

   ConfigManager *pMgr = ConfigManager::getManager( SessionTags::SESSION );
   Configuration cfgWorkTable = pMgr->retrieveConfig( SessionTags::WORK_TABLE );

   DString dstrAwdSourcePtr = m_rpGIUserSession->getSession()->getSessionData( I_("_AwdInterface_Ptr_") );
   BFAwdInterface *pAwdInterface = (BFAwdInterface *)dstrAwdSourcePtr.asInteger();

   // Determine AWD Business Area
   DString dstrCompanyId( NULL_STRING );
   DString dstrBusinessArea( NULL_STRING );

   // Get Company ID
   DSTCWorkSession *dstWorkSession = NULL;
   MgmtCo *mgmtCo = NULL;
   if( m_rpGIWorkSession != NULL )
   {
      dstWorkSession = dynamic_cast<DSTCWorkSession *>(m_rpGIWorkSession->getBFWorkSession());
   }
   if( dstWorkSession != NULL )
   {
      dstWorkSession->getMgmtCo().getField( ifds::CompanyId, dstrCompanyId, BF::HOST);
   }

   // Iterate AWD Business Area list in MGMCO to find matching ID
   short nFound = 0;
   if( !dstrCompanyId.empty() )
   {
      ConfigManager *pConfigManager = ConfigManager::getManager( SessionTags::Session );
      Configuration cfgMGMCOTable = pConfigManager->retrieveConfig( SessionTags::MGMCO );

      DString dstrTempSystemID( NULL_STRING );
      Configuration::iterator iter = cfgMGMCOTable.begin();
      while( iter != cfgMGMCOTable.end() )
      {
         dstrTempSystemID = ( *iter ).getValueAsString();
         dstrTempSystemID.strip().stripAll( I_CHAR('\t') );

         if( dstrTempSystemID == dstrCompanyId )
         {
            ++nFound;
            dstrBusinessArea = ( *iter ).getKey();
            dstrBusinessArea.strip().stripAll( I_CHAR('\t') );
         }
         ++iter;
      }
      if( nFound > 1 )
      {
         dstrBusinessArea = NULL_STRING;
      }
   }

   CriteriaVector  criteriaList;

   // Set Business Area Criteria
   BFAwdLookupCriteria criteriaBusinessArea( cfgWorkTable.getValueAsString( AWD::Business_Area ).stripAll( I_CHAR('\t') ), BFAwdLookupCriteria::EQUAL_TO, dstrBusinessArea );
   if( !dstrBusinessArea.empty() && !cfgWorkTable.getValueAsString( AWD::Business_Area ).stripAll( I_CHAR('\t') ).empty() )
   {
      criteriaList.push_back( criteriaBusinessArea );
   }

   // Set Criteria
   DString key = reinterpret_cast<const I_CHAR*>(apnAWDFields[ nLookUpBy ]);
   DString dstrLookUpBy = cfgWorkTable.getValueAsString( key ).stripAll( I_CHAR('\t') );
   BFAwdLookupCriteria criteria1( dstrLookUpBy, BFAwdLookupCriteria::EQUAL_TO, dstrFieldValue );
   criteriaList.push_back( criteria1 );

   //Add the lookup order for CRDA in
   DString lookupOrder = cfgWorkTable.getValueAsString( AWD::LookupOrder ).stripAll( I_CHAR('\t') );

   if (!lookupOrder.empty())
   {
      BFAwdLookupCriteria::Order iLookupOrder = BFAwdLookupCriteria::Order::NO_ORDER;

      if (lookupOrder == AWD::Ascending)
      {
         iLookupOrder = BFAwdLookupCriteria::Order::ASCENDING;
      }
      else if (lookupOrder == AWD::Descending)
      {
         iLookupOrder = BFAwdLookupCriteria::Order::DESCENDING;
      }

      BFAwdLookupCriteria criteriaLookupOrder ( I_("CRDA"), iLookupOrder);
      criteriaList.push_back( criteriaLookupOrder );
   }

   // Set SystemID Criteria
   BFAwdLookupCriteria criteriaSystemID( cfgWorkTable.getValueAsString( AWD::System_ID ).stripAll( I_CHAR('\t') ), BFAwdLookupCriteria::EQUAL_TO, I_( "COR" ) );
   if (dstrMarket == MARKET_IDS::CANADA) {
      criteriaList.push_back( criteriaSystemID );
   }

   try
   {
      if( !pAwdInterface->lookupWork( criteriaList ) )
      {
         DISPLAYCONDITIONFROMFILE( CND::GUI_AWD_LOOKUP_ERROR );
      }
   }
   catch( ... )
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_AWD_EXCEPTION );
   }
}


//******************************************************************************
void CDSTCView::OnAWDComment()
{
   CWaitCursor wait;

   startCall();
   //destroyBusInfo(); // Close FYI screen - why?

   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnAWDComment" ) );

   E_COMMANDRETURN eRtn = CMD_FAILURE;
   try
   {
      assert (m_rpGIWorkSession);
      m_rpGIWorkSession->setParameter (I_("CalledFrom"), I_("AWDComments"));
      eRtn = CommandDispatcher::getInstance()->invokeCommand( m_rpGIWorkSession,
                                                              CMD_BPROC_CONFIRMATION,
                                                              PROC_NO_TYPE,
                                                              false,
                                                              NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
         case CMD_CANCEL:
            break;
         default:
            ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
            break;
      }
   }
   catch( ConditionException& ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }
}

//******************************************************************************
void CDSTCView::OnUpdateAWDComment( CCmdUI* pCmdUI )
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateAWDComment") );
   CWaitCursor wait;
   startCall();

   bool blEnableAWDComments = false;

   DSTCAWDSession* pAwdSession =NULL;
   if( m_rpGIWorkSession )
   {
      pAwdSession = dynamic_cast<DSTCAWDSession* >( m_rpGIWorkSession->getSession() );
   }
   if( NULL != pAwdSession )
   {
      if ( pAwdSession->isAWDWorking() &&
           !pAwdSession->isContainerEmpty() &&
           pAwdSession->hasWorkObject() &&
           !pAwdSession->isCallStarted() )
      {
         blEnableAWDComments = true;
      }
   }

   pCmdUI->Enable( blEnableAWDComments );
}

//******************************************************************************

void CDSTCView::OnForms()
{
   CWaitCursor wait;
   startCall();
   if( BFAwdInterface::isLoggedOn() )
   {
      FormsMgr *pMgr = FormsMgr::getInstance();
      m_rpGIUserSession->getSession()->setSessionData(I_("NT Event Form"), NULL_STRING);
      pMgr->start( m_hWnd, m_rpGIUserSession );
   }
}

//******************************************************************************

bool CDSTCView::OKToSetCallerInfo()
{
   CString tmp;
   GetDlgItem( IDC_TXT_EXT )->GetWindowText( tmp );
   CString cstrHold=tmp.Right( tmp.GetLength() - 1 );
   tmp=cstrHold.SpanIncluding( _T("0123456789") );
   return(!( tmp == cstrHold ));
}

//******************************************************************************

void CDSTCView::setCallerName( const I_CHAR* name )
{
   if( OKToSetCallerInfo() )
      GetDlgItem( IDC_TXT_NAME )->SetWindowText( name );
}

//******************************************************************************

void CDSTCView::setCallerRelationship( const I_CHAR* relationship )
{
   if( OKToSetCallerInfo() )
      GetDlgItem( IDC_TXT_RELATIONSHIP )->SetWindowText( relationship );
}

//******************************************************************************

void CDSTCView::setCallerPhoneNum( const I_CHAR* phoneNum )
{
   if( OKToSetCallerInfo() )
      GetDlgItem( IDC_TXT_PHONE )->SetWindowText( phoneNum );
}

//******************************************************************************

void CDSTCView::setCallerExt( const I_CHAR* ext )
{
   if( OKToSetCallerInfo() )
      GetDlgItem( IDC_TXT_EXT )->SetWindowText( ext );
}

//******************************************************************************

void CDSTCView::setCallerTimeOfCall( const I_CHAR* timeOfCall )
{
   if( OKToSetCallerInfo() )
      GetDlgItem( IDC_TXT_TIMEOFCALL )->SetWindowText( timeOfCall );
}

//******************************************************************************

void CDSTCView::enableDetailsButton( bool enable )
{
   m_btnDetails.EnableWindow( enable );
}

//******************************************************************************

void CDSTCView::enableRemarksButton( bool enable )
{
   m_btnRemarks.EnableWindow( enable );
}

//******************************************************************************

void CDSTCView::fillAllCheckingSecurity()
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, FILLALLCHECKINGSECURITY );

   if( m_rpGIUserSession )
   {
      m_cmbSearch.ResetContent();
      m_cmbUsing.ResetContent();

      DSTCUserSession *dstcUserSession = dynamic_cast<DSTCUserSession *>(m_rpGIUserSession->getBFSession());

      DString mgmtCoId;
      m_rpGIUserSession->getField( NULL, SYSTMGMTS, mgmtCoId );

      // if the user doesn't have access to see the fund nav info
      // disable the fund info button
      m_btnFund.EnableWindow( dstcUserSession->hasReadPermission( mgmtCoId, UAF::FUND_NAV ) );//, DBR::InqPerm ) );
      // if the user doesn't have access to see the remarks info
      // disable the remarks info button
      m_btnRemarks.EnableWindow( dstcUserSession->hasReadPermission( mgmtCoId, UAF::REMARKS ) ); //, DBR::InqPerm ) );
      //fill the search criterias
      E_COMMANDRETURN eFillerRtn = CMD_FAILURE;
      if( m_rpGIFiller == NULL )
      {
         //invoke the process if it hasn't been invoked, so far
         eFillerRtn = CommandDispatcher::getInstance()->invokeCommand( m_rpGIUserSession,
                                                                       CMD_BPROC_FILL_SEARCH_CRITERIA, PROC_NO_TYPE, false, &m_rpGIFiller );
      }
      else
      {
         eFillerRtn = CMD_MODELESS_INPROCESS;
      }
      if( eFillerRtn = CMD_MODELESS_INPROCESS )
      {
         const DString *searchCriteriaKey = &m_rpGIFiller->getFirstListItemKey( NULL, BFContainerId( ifds::SearchCriteria.getId() ) );
         const I_CHAR *strAccessFunctionCode;

         do
         {
            bool bTradePermit = false;
            if( *searchCriteriaKey == SEARCHCRITERIA::ACCOUNT_SEARCH )
            {
               strAccessFunctionCode = UAF::SEARCH_FOR_ACCOUNT_OR_ENTITY;
            }
            else if( *searchCriteriaKey == SEARCHCRITERIA::CHEQUE_SEARCH )
            {
               strAccessFunctionCode = UAF::SEARCH_FOR_CHEQUE;
            }
            else if( *searchCriteriaKey == SEARCHCRITERIA::CERTIFICATE_SEARCH )
            {
               strAccessFunctionCode = UAF::SEARCH_FOR_CERTIFICATE;
            }
            else if( *searchCriteriaKey == SEARCHCRITERIA::SYSTEMATICS_SEARCH )
            {
               //;unknown UAF code
            }
            else if( *searchCriteriaKey == SEARCHCRITERIA::BANKING_SEARCH )
            {
               strAccessFunctionCode = UAF::BANKING_INSTRUCTION;
            }
            else if( *searchCriteriaKey == SEARCHCRITERIA::ENTITY_SEARCH )
            {
               strAccessFunctionCode = UAF::SEARCH_FOR_ACCOUNT_OR_ENTITY;
            }
            else if( *searchCriteriaKey == SEARCHCRITERIA::ADDRESS_SEARCH )
            {
               strAccessFunctionCode = UAF::ADDRESS_BOOK;
            }
            else if( *searchCriteriaKey == SEARCHCRITERIA::COA_SEARCH )
            {
               //;unknown UAF code
            }
            else if( *searchCriteriaKey == SEARCHCRITERIA::DISTRIBUTIONS_SEARCH )
            {
               strAccessFunctionCode = UAF::DISTRIBUTION;
            }
            else if( *searchCriteriaKey == SEARCHCRITERIA::ALLOCATIONS_SEARCH )
            {
               strAccessFunctionCode = UAF::DEFAULT_ALLOCATION;
            }
            else if( *searchCriteriaKey == SEARCHCRITERIA::SHAREHOLDER_INFO_SEARCH )
            {
               //;unknown UAF code
            }
            else if( *searchCriteriaKey == SEARCHCRITERIA::ACCOUNT_INFO_SEARCH )
            {
               strAccessFunctionCode = UAF::ACCOUNT_CERTIFICATE_INFO;
            }
            else if( *searchCriteriaKey == SEARCHCRITERIA::TRADE_SEARCH )
            {
               bTradePermit = dstcUserSession->hasCreatePermission( mgmtCoId, UAF::TRADING_EXCHANGE ) //, DBR::AddPerm )
                              || dstcUserSession->hasCreatePermission( mgmtCoId, UAF::TRADING_PURCHASE ) //, DBR::AddPerm )
                              || dstcUserSession->hasCreatePermission( mgmtCoId, UAF::TRADING_REDEMPTION ); //, DBR::AddPerm );
            }
            else if( *searchCriteriaKey == SEARCHCRITERIA::AMSGLOBAL_SEARCH)
            {
               strAccessFunctionCode = UAF::ACCOUNT_CERTIFICATE_INFO;
            }

            else if( *searchCriteriaKey == SEARCHCRITERIA::ALLENTITY_SEARCH)
            {
               strAccessFunctionCode = UAF::SEARCH_FOR_ACCOUNT_OR_ENTITY;
            }
            else if( *searchCriteriaKey == SEARCHCRITERIA::ACCOUNT_REGULATORY_SEARCH)
            {
               strAccessFunctionCode = UAF::SEARCH_FOR_ACCOUNT_OR_ENTITY;
            }
            else
            {
               ASSERT( 0 );
               DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
               return;
            }
            if( dstcUserSession->hasReadPermission( mgmtCoId, strAccessFunctionCode ) || bTradePermit )
            {
               DString searchCriteriaDescription;

               m_rpGIFiller->getField( NULL, BFContainerId( ifds::SearchCriteria.getId() ), ifds::Substitute_Description,
                                       searchCriteriaDescription );
               int comboNdx = m_cmbSearch.AddString( searchCriteriaDescription.c_str() );
               if( comboNdx != CB_ERR && comboNdx != CB_ERRSPACE )
               {
                  m_cmbSearch.SetItemData( comboNdx, (DWORD)searchCriteriaKey );
               }
            }
         }
         while( *( searchCriteriaKey = &m_rpGIFiller->getNextListItemKey( NULL, BFContainerId( ifds::SearchCriteria.getId() ) ) ) != NULL_STRING );
      }
      if( m_cmbSearch.GetCount() > 0 )
      {
         //enable everything if the user has access
         m_cmbSearch.EnableWindow( TRUE );
         m_cmbUsing.EnableWindow( TRUE );
         m_btnSearch.EnableWindow( TRUE );
         m_btnIdCaller.EnableWindow( TRUE );

//         m_btnFinancial.EnableWindow( TRUE );

       DString dstrLastAccountNum=NULL_STRING;
       if( m_rpGIWorkSession )
       {
         m_rpGIWorkSession->getGlobal( WORK_GLOBAL, ifds::LastActiveAccountNum, dstrLastAccountNum );
         dstrLastAccountNum.strip();
         dstrLastAccountNum.stripLeading( '0' );
       }
       m_btnRemarks.EnableWindow( (dstrLastAccountNum != NULL_STRING ) && dstcUserSession->hasReadPermission( mgmtCoId, UAF::REMARKS ));

         //select the first search criteria
         m_cmbSearch.SetCurSel( 0 );
         OnSelchangeCmbSearch();
         m_cmbUsing.SetCurSel( 0 );
         OnSelchangeCmbUsing();
      }
      else
      {
         //disabling everything if the user doesn't have access
         m_cmbSearch.EnableWindow( FALSE );
         m_cmbUsing.EnableWindow( FALSE );
         GetDlgItem( IDC_EDT_SEARCH1 )->ShowWindow( SW_HIDE );
         GetDlgItem( IDC_EDT_SEARCH2 )->ShowWindow( SW_HIDE );
         GetDlgItem( IDC_EDT_SEARCH3 )->ShowWindow( SW_HIDE );
         GetDlgItem( IDC_LBL_SEARCH1 )->ShowWindow( SW_HIDE );
         GetDlgItem( IDC_LBL_SEARCH2 )->ShowWindow( SW_HIDE );
         GetDlgItem( IDC_LBL_SEARCH3 )->ShowWindow( SW_HIDE );
         m_edtSearch1.SetWindowText( NULL_STRING );
         m_edtSearch2.SetWindowText( NULL_STRING );
         GetDlgItem(IDC_EDT_SEARCH3)->SetWindowText( NULL_STRING );

         //m_edtSearch3.SetWindowText( NULL_STRING );
         m_btnSearch.EnableWindow( FALSE );
//         m_btnFinancial.EnableWindow( FALSE );
         m_btnIdCaller.EnableWindow( FALSE );
         m_btnRemarks.EnableWindow( FALSE );
      }
      m_btnFinancial.EnableWindow( dstcUserSession->hasCreatePermission( mgmtCoId, UAF::TRADING_PURCHASE ) ||
                                   dstcUserSession->hasCreatePermission( mgmtCoId, UAF::TRADING_EXCHANGE ) ||
                                   dstcUserSession->hasCreatePermission( mgmtCoId, UAF::TRADING_REDEMPTION ) );
      m_btnNew.EnableWindow(dstcUserSession->hasCreatePermission( mgmtCoId, UAF::SEARCH_FOR_ACCOUNT_OR_ENTITY ) );
      bool bEnable = dstcUserSession->hasReadPermission( mgmtCoId, UAF::SETTLE_ALL_TRADE ) ||
                     dstcUserSession->hasReadPermission( mgmtCoId, UAF::SETTLE_ACCOUNT ) ||
                     dstcUserSession->hasReadPermission( mgmtCoId, UAF::SETTLE_WIRE_ORDER ) ||
                     dstcUserSession->hasReadPermission( mgmtCoId, UAF::SETTLE_BROKER );

      m_btnSettlement.EnableWindow ( bEnable );

      m_btnGlobalSearch.EnableWindow ( dstcUserSession->hasReadPermission( mgmtCoId, UAF::GLOBAL_SEARCH ) &&
                                       dstcUserSession->hasReadPermission( mgmtCoId, UAF::SEARCH_FOR_ACCOUNT_OR_ENTITY ));
   }
}

bool CDSTCView::DiffMgmCo (DString newcompanyID)
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, DIFFMGMCO );
   DString dstCompanyId( NULL_STRING );
   DString dstCompanyName( NULL_STRING );
   DString dstErrorMsg( NULL_STRING );
   DString dstNewCompanyId( newcompanyID );
   dstNewCompanyId.strip();

   try
   {
      m_rpGIUserSession->getField( NULL, SYSTMGMTS, dstCompanyId );
      m_rpGIUserSession->getField( NULL, MGMTCONAME, dstCompanyName );

      return(!( dstCompanyId == dstNewCompanyId ));
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      addIDITagValue( dstErrorMsg, IDI_MSG, dstNewCompanyId );
      DISPLAYCONDITIONFROMFILEIDI( CND::GUI_AWD_SYSTEM_ERROR, dstErrorMsg );
   }
   return(false);
}

//******************************************************************************
bool CDSTCView::SetMgmCo (DString newcompanyID)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, SETMGMCO );

   DString dstCompanyId (NULL_STRING),
      dstCompanyName (NULL_STRING),
      dstClientId (NULL_STRING),
      dstrClientName (NULL_STRING),
      dstNewCompanyId (newcompanyID),
      dstErrorMsg (NULL_STRING);

   dstNewCompanyId.strip();

   try
   {
      m_rpGIUserSession->getField( NULL, SYSTMGMTS, dstCompanyId );
      m_rpGIUserSession->getField( NULL, MGMTCONAME, dstCompanyName );

      if (dstCompanyId != dstNewCompanyId)
      {
         DSTCGlobalSession &dstcGlobalSession =
            dynamic_cast<DSTCGlobalSession &> (m_rpGIUserSession->getBFSession()->getGlobalSession());

         if (dstcGlobalSession.getMgmtCo (newcompanyID) <= WARNING)
         {

            CWaitCursor wait;
            // call view 276 for audit purpose
            try
            {
               DSTCUserSession &session = dynamic_cast<DSTCUserSession& >(m_rpGIUserSession->getBFSession()->getUserSession());

               session.fireFighterLogon(newcompanyID);
            }
            catch( ... )
            {
               // we catch the exception, ignore it and continue
            }

            // Set Mgmco
            if (m_rpGIWorkSession != NULL)
            {
               DSTCWorkSession *pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(m_rpGIWorkSession->getBFSession());
               pDSTCWorkSession->setMgmtCo (newcompanyID);
               if (m_rpGIUserSession)
               {
                  CommandDispatcher::getInstance()->invokeCommand( m_rpGIUserSession,
                                                                   CMD_BPROC_PROGRESS_CTRL, PROC_NO_TYPE, true, NULL);
               }
               DSTCAWDSession* pSession =NULL;
               pSession = dynamic_cast<DSTCAWDSession* >( m_rpGIWorkSession->getSession() );
               if (pSession)
               {
                  pSession->associateDSTCWorkSession (pDSTCWorkSession, true);
               }
            }

            CsiSession& csiSession = CsiSession::getInstance();
            if( csiSession.IsReflectionStart() )
            {
               csiSession.executeProcess(DcCsiProcesses::CHOOSE_MANAGE_COMP);
               csiSession.clearParameters();
            }
            GenericInterface *rpGIUserAccess (NULL);

            if (m_rpGIWorkSession != NULL)
            {
               rpGIUserAccess = m_rpGIWorkSession->getGIContainer()->findGI( m_rpGIWorkSession->getBFSession(), CMD_BPROC_USER_ACCESS );
            }
            if (rpGIUserAccess != NULL)
            {
               rpGIUserAccess->refresh (NULL, I_("Refresh Security"));
            }

            // Determine Company Name
            DSTCUserSession *pDSTCUserSession = dynamic_cast<DSTCUserSession *>(m_rpGIUserSession->getBFSession());
            DString dstrCompanyId, dstrCompanyName;
            long  lNumberOfCompanies = pDSTCUserSession->getNumberOfCompanies( DSTCHost::getPrimaryHost() );
            for( short nCtr = 0; nCtr < lNumberOfCompanies; ++nCtr )
            {
               pDSTCUserSession->getCompanyInfo( DSTCHost::getPrimaryHost(), nCtr, dstrCompanyId, dstrCompanyName );
               if( dstrCompanyId == newcompanyID )
               {
                  dstCompanyName = dstrCompanyName;
                  break;
               }
            }

            m_rpGIUserSession->setField( NULL, SYSTMGMTS, newcompanyID );
            m_rpGIUserSession->setField( NULL, MGMTCONAME, dstCompanyName );

            // Store ManagementCompany into Registry
            DString dstrManagementCompanyEntry = newcompanyID + I_( "/" ) + dstCompanyName;
            DString dstrUserID;
            m_rpGIUserSession->getField( NULL, USERID, dstrUserID );

            DSTCUserSession* pUserSession = dynamic_cast<DSTCUserSession*>(m_rpGIUserSession->getBFSession());
            DString dstrCompanyCode = NULL_STRING;
            if( pUserSession != NULL )
            {
               DSTCGlobalSession& gs = dynamic_cast<DSTCGlobalSession&>(pUserSession->getGlobalSession());
               MgmtCo* pMgmtCo = NULL;
               MgmtCoOptions* pOptions = NULL;
               gs.findMgmtCo( newcompanyID, pMgmtCo );

               if(pMgmtCo && pMgmtCo->getMgmtCoOptions(pOptions) <= WARNING && 
                  pOptions){
                     pOptions->getField( ifds::CompanyCode, dstrCompanyCode, BF::HOST, false );
               }
               dstrCompanyCode.stripAll ().upperCase ();
            }

            ConfigManager *cfgMgrUser = ConfigManager::getManager( REG_USER );
            Configuration cfgUser = cfgMgrUser->retrieveConfig( dstrUserID );
            ConfigValue cfgValueManagementCompany( dstrManagementCompanyEntry );
            cfgUser.set( REG_MANAGEMENTCOMPANY, cfgValueManagementCompany );
            cfgMgrUser->storeConfig( cfgUser );
            cfgMgrUser->persist();

            ReloadResource (newcompanyID);

            m_rpGIUserSession->getField( NULL, CLIENTNAME, dstrClientName );
            m_statusBar.SetManagementCodeStatusBar( dstCompanyName.c_str() );
            m_statusBar.SetCompanyCodeStatusBar( dstrCompanyCode.c_str() );
            m_statusBar.SetClientNameStatusBar( dstrClientName.c_str() );

            fillAllCheckingSecurity();
            addIDITagValue (dstErrorMsg, IDI_MSG, dstCompanyName);
            DISPLAYCONDITIONFROMFILEIDI (CND::GUI_AWD_SYSTEM_CHANGED, dstErrorMsg);

            return true;
         }
         else
         {
            ConditionMessageBox (FRAMEBELOW(), GETHIGHESTSEVERITY());
         }
      }
   }
   catch (ConditionException &ce)
   {
      ConditionMessageBox (ce);
   }
   catch ( ... )
   {
      addIDITagValue( dstErrorMsg, IDI_MSG, dstNewCompanyId );
      DISPLAYCONDITIONFROMFILEIDI( CND::GUI_AWD_SYSTEM_ERROR, dstErrorMsg );
   }
   return false;
}

void CDSTCView::OnTaxrates()
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnTaxrates") );
   CWaitCursor wait;

   DSTCUserSession *dstcUserSession = dynamic_cast<DSTCUserSession *>(m_rpGIUserSession->getBFSession());

   DString dstrMgmtCoId;
   m_rpGIUserSession->getField( NULL, SYSTMGMTS, dstrMgmtCoId );

   //if no permission, return
   bool bTaxRatesPermit = dstcUserSession->hasReadPermission( dstrMgmtCoId, UAF::TAX_RATES );
   if( !bTaxRatesPermit || !m_btnFund.IsWindowEnabled() ) //reject the call if the button is disabled
   {
      return;
   }
   startCall();
   destroyBusInfo(); // Close FYI screen - why?

   // Create the Tax Rates dialog
   if( CMD_MODELESS_INPROCESS != CommandDispatcher::getInstance()->invokeCommand(
                                                                                m_rpGIWorkSession, CMD_BPROC_TAXRATES, PROC_NO_TYPE, false, NULL ) )
   {  // Error processing
      ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
      return;
   }
}


//******************************************************************************
void CDSTCView::destroyBusInfo()
{
   GenericInterface *pBusInfo;
   if( m_rpGIUserSession )
   {
      pBusInfo = m_rpGIUserSession->getGIContainer()->
                 findGI( m_rpGIUserSession->getBFSession(), CMD_GUI_BUSINFO );
      if( pBusInfo )
      {
         m_rpGIUserSession->getGIContainer()->destroy( pBusInfo );
      }
   }
}

//******************************************************************************

bool CDSTCView::CanPerformSearch()
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, CANPERFORMSEARCH );

#ifdef _HARNESS
   m_btnHarness.EnableWindow( FALSE );
#endif

   m_bDiscard = true;

   try
   {
      if( m_bIdCallerEnd && !m_bIdCaller )
      {
         CommandDispatcher::getInstance()->invokeCommand( m_rpGIWorkSession,
                                                          CMD_BPROC_IDCALLER, PROC_NO_TYPE, false, NULL );
      }

      if( m_rpGIWorkSession != NULL )
      {
         DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(m_rpGIWorkSession->getBFWorkSession());

         if( dstWorkSession->hasNonHostUpdates( ) )
         {
            DiscardMsgDlg discardDlg(NULL, TXT_DISCARD_MSGA, TXT_DISCARD_MSGB, TXT_DISCARD);
            if( discardDlg.DoModal() == IDCANCEL )
            {
               return(false);
            }
            else
            {
               m_rpGIWorkSession->ok( NULL );
            }
         }
      }

      RoadComMgr::callEndOnAllActiveObjects();
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
      throw;
   }
   m_btnGetWork.EnableWindow( m_bAWD && !m_bCallStart);

#ifdef _HARNESS
   m_btnHarness.EnableWindow( TRUE );
#endif

   return(true);
}
//******************************************************************************

void CDSTCView::OnChangeEdtAreaCode()
{
   CString strAreaCode;
   m_edtAreaCode.GetWindowText(strAreaCode);
   if( strAreaCode.GetLength() == 3 )//area code already entered
      GetDlgItem(IDC_EDT_SEARCH3)->SetFocus();

   //m_edtSearch3.SetFocus();

}
//******************************************************************************

void CDSTCView::ReloadResource( const DString &dstrCompId )
{
   DString dstrClientId(dstrCompId);
/**
  if (m_rpGIWorkSession)
    m_rpGIWorkSession->getField( NULL, CLIENTID, dstrClientId );
*/
   DSTCWorkSession *dstWorkSession = NULL;
   MgmtCo *mgmtCo = NULL;
   if( m_rpGIWorkSession != NULL )
   {
      dstWorkSession = dynamic_cast<DSTCWorkSession *>(m_rpGIWorkSession->getBFWorkSession());
   }
   if( dstWorkSession != NULL )
   {
      dstWorkSession->getMgmtCo().getField( ifds::ClientID, dstrClientId, BF::HOST);
   }

// ((MFDSTCApp*)AfxGetApp())->LoadResourceDll( dstrCompId );
   ((MFDSTCApp*)AfxGetApp())->LoadResourceDll( dstrClientId );
   ((CMainFrame*)AfxGetMainWnd())->ChangeMenu();
   ((CMainFrame*)AfxGetMainWnd())->setAwdActive( m_bAWD );
   ((CMainFrame*)AfxGetMainWnd())->setMgmCo( dynamic_cast<DSTCUserSession *>(m_rpGIUserSession->getBFSession()) );

   UpdateLabels();

   // Session
   DString dstrTitle;
   CString cstrTitle;
   cstrTitle.LoadString( AFX_IDS_APP_TITLE );
   CWnd  *pGUI = CWnd::FindWindow( NULL, cstrTitle );
   if( pGUI != NULL )
   {
      dstrTitle = DString( cstrTitle ) + I_(" - ");
      dstrTitle.appendInt( m_ucSession );
      pGUI->SetWindowText( CString(dstrTitle.c_str()) );
   }
}

//******************************************************************************

void CDSTCView::enableTradeButton( bool enable )
{
   m_btnFinancial.EnableWindow( enable );
}

//******************************************************************************

void CDSTCView::OnHelp1()
{
   LaunchHelp(I_("Desktop.chm>TriPane"));
}

//******************************************************************************

void CDSTCView::OnHelp2()
{
   LaunchHelp(I_("User Guide.chm>TriPane"));
}

//******************************************************************************

void CDSTCView::OnHelp3()
{
   LaunchHelp(I_("Setup Guide.chm>TriPane"));
}

//******************************************************************************

void CDSTCView::LaunchHelp(const DString &dstrHelpFilename)
{
   DString dstrDataPath = GetConfigValueAsString(  CONFIGURATION_CONSTANTS::MFDSTC,
                                                   CONFIGURATION_CONSTANTS::DataPath,
                                                   CONFIGURATION_CONSTANTS::Path );
   dstrDataPath += I_("\\");
   dstrDataPath += dstrHelpFilename;
   ::HtmlHelp(NULL, NULL, HH_CLOSE_ALL, 0);
   HWND hwndHtmlHelp = ::HtmlHelp( m_hWnd, dstrDataPath.c_str(), HH_DISPLAY_TOPIC, NULL);
}

//******************************************************************************
void CDSTCView::openFundGroupDlg (int control)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "openFundGroupDlg" ) );

   E_COMMANDRETURN eRtn = CMD_CANCEL;
    CWaitCursor wait;

   if( !m_rpGIWorkSession )//have to create a worksession
    {
      if( CommandDispatcher::getInstance()->invokeCommand( m_rpGIUserSession,
                                                            CMD_BPROC_WORK_SESSION, PROC_NO_TYPE,
                                             false, &m_rpGIWorkSession )!= CMD_MODELESS_INPROCESS )
      {  // Error handling
         ASSERT( 0 );
            return;
      }
   }

   m_rpGIUserSession->setParameter( MFCAN_IP_PARAM::SPONSOR_GROUP, I_("SPONSOR") );
    DString dstrFundGroup;
    eRtn = CommandDispatcher::getInstance()->invokeCommand( m_rpGIWorkSession, CMD_BPROC_FUNDGROUP, PROC_NO_TYPE, true, NULL );

    switch( eRtn )
    {
      case CMD_OK:
        case CMD_MODELESS_INPROCESS:
        {
         m_rpGIWorkSession->getParameter( I_("FUNDSPONSOR"), dstrFundGroup );
//            GetDlgItem(IDC_EDT_SEARCH3)->SetWindowText( dstrFundGroup.c_str() );

         //m_rpGIWorkSession->getParameter( FUND_CODE, dstrFundCode );
            GetDlgItem(control)->SetWindowText( dstrFundGroup.c_str() );

            break;
        }

      case CMD_CANCEL:
             break;

      default:
             // Display error
             ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
             break;
   }
}
//******************************************************************************
void CDSTCView::openFundClassListDlg (int control)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenFundClassListDlg" ) );

   E_COMMANDRETURN eRtn = CMD_CANCEL;
    CWaitCursor wait;
    if( !m_rpGIWorkSession )//have to create a worksession
    {
      if( CommandDispatcher::getInstance()->invokeCommand( m_rpGIUserSession,
                                                            CMD_BPROC_WORK_SESSION, PROC_NO_TYPE, false, &m_rpGIWorkSession )
            != CMD_MODELESS_INPROCESS )
        {  // Error handling
         ASSERT( 0 );
            return;
         }
   }
    CString strFundCode, strClassCode;

    GetDlgItem(control)->GetWindowText( strFundCode );
    DString dstrFundCode(strFundCode), dstrClassCode;
    m_rpGIWorkSession->setParameter( FUND_CODE, dstrFundCode );

    eRtn = CommandDispatcher::getInstance()->invokeCommand( m_rpGIWorkSession,
                                                            CMD_BPROC_FUNDCLASS, PROC_NO_TYPE, true, NULL );//PROC_SUPPORT??
    switch( eRtn )
    {
      case CMD_OK:
        case CMD_MODELESS_INPROCESS:
        {
         m_rpGIWorkSession->getParameter( FUND_CODE, dstrFundCode );
            GetDlgItem(control)->SetWindowText( dstrFundCode.c_str() );
            break;
        }
        case CMD_CANCEL:
            break;
        default:
         // Display error
            ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
            break;
   }
}
//******************************************************************************

void CDSTCView::F4pressed()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenFundClassListDlg" ) );

   int usingComboNdx = m_cmbUsing.GetCurSel();
   DString searchUsingKey = *(DString*)m_cmbUsing.GetItemData( usingComboNdx );

   if( searchUsingKey == SEARCHBANKINGUSING::FUND )//or FUND_CLASS
   {
      if( GetFocus() != GetDlgItem( IDC_EDT_SEARCH3 ) )
         return;
      try
      {
       openFundClassListDlg (IDC_EDT_SEARCH3);
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
   else if( searchUsingKey == SEARCHALLENTITYUSING::WHEREUSE )
   {
       if( GetFocus() != GetDlgItem( IDC_EDT_SEARCH2 ) )
         return;

      CString cstrSearch1;
      GetDlgItem( IDC_CMB_SEARCH1 )->GetWindowText (cstrSearch1);
      DString dstrSearch1 = cstrSearch1;

      try
      {
         if ( dstrSearch1.stripAll ().upperCase () == I_("FUND"))
            openFundClassListDlg (IDC_EDT_SEARCH2);
         else if (dstrSearch1.stripAll ().upperCase () == I_("FUNDSPONSOR"))
            openFundGroupDlg (IDC_EDT_SEARCH2);

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
   else if( searchUsingKey == SEARCHBANKINGUSING::FUND_GROUP )
   {
      try
      {
         E_COMMANDRETURN eRtn = CMD_CANCEL;
         CWaitCursor wait;
         if( !m_rpGIWorkSession )//have to create a worksession
         {
            if( CommandDispatcher::getInstance()->invokeCommand( m_rpGIUserSession,
                                                                 CMD_BPROC_WORK_SESSION, PROC_NO_TYPE, false, &m_rpGIWorkSession )
                != CMD_MODELESS_INPROCESS )
            {  // Error handling
               ASSERT( 0 );
               return;
            }
         }

         m_rpGIUserSession->setParameter( MFCAN_IP_PARAM::SPONSOR_GROUP, I_("GROUP") );
         DString dstrFundGroup;
         eRtn = CommandDispatcher::getInstance()->invokeCommand( m_rpGIWorkSession,
                                                                 CMD_BPROC_FUNDGROUP, PROC_NO_TYPE, true, NULL );
         switch( eRtn )
         {
            case CMD_OK:
            case CMD_MODELESS_INPROCESS:
               {
                  m_rpGIWorkSession->getParameter( I_("FUNDGROUP"), dstrFundGroup );
                  GetDlgItem(IDC_EDT_SEARCH3)->SetWindowText( dstrFundGroup.c_str() );
                  break;
               }
            case CMD_CANCEL:
               break;
            default:
               // Display error
               ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
               break;
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
   else if( searchUsingKey == SEARCHBANKINGUSING::FUND_SPONSOR )
   {
      try
      {
         E_COMMANDRETURN eRtn = CMD_CANCEL;
         CWaitCursor wait;
         if( !m_rpGIWorkSession )//have to create a worksession
         {
            if( CommandDispatcher::getInstance()->invokeCommand( m_rpGIUserSession,
                                                                 CMD_BPROC_WORK_SESSION, PROC_NO_TYPE, false, &m_rpGIWorkSession )
                != CMD_MODELESS_INPROCESS )
            {  // Error handling
               ASSERT( 0 );
               return;
            }
         }

         m_rpGIUserSession->setParameter( MFCAN_IP_PARAM::SPONSOR_GROUP, I_("SPONSOR") );
         DString dstrFundGroup;
         eRtn = CommandDispatcher::getInstance()->invokeCommand( m_rpGIWorkSession,
                                                                 CMD_BPROC_FUNDGROUP, PROC_NO_TYPE, true, NULL );
         switch( eRtn )
         {
            case CMD_OK:
            case CMD_MODELESS_INPROCESS:
               {
                  m_rpGIWorkSession->getParameter( I_("FUNDSPONSOR"), dstrFundGroup );
                  GetDlgItem(IDC_EDT_SEARCH3)->SetWindowText( dstrFundGroup.c_str() );
                  break;
               }
            case CMD_CANCEL:
               break;
            default:
               // Display error
               ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
               break;
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
}

//*****************************************************************************
void CDSTCView::OnBtnSettlement()
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, ONBTNSETTLEMENT );
   CWaitCursor wait;

   //reject the call if the button is disabled
   if( !m_btnSettlement.IsWindowEnabled() )
   {
      return;
   }

   try
   {
      // Close FYI screen
      destroyBusInfo();

      m_statusBar.SetMessageStatusBar( TXT_LOAD_SETTLEMENT );
      // Create the Fund Info dialog
      startCall();
      E_COMMANDRETURN eRtn = CommandDispatcher::getInstance()->invokeCommand(
         m_rpGIWorkSession, CMD_BPROC_SETTLEMENT, PROC_NO_TYPE, false, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
         case CMD_CANCEL:
            break;
         default:
            // Display error
            ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
            break;
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
   m_statusBar.SetMessageStatusBar( NULL_STRING );
}

//*****************************************************************************
void CDSTCView::OnUpdateAmsReports(CCmdUI* pCmdUI)
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateAmsReports") );

   DSTCUserSession *dstcUserSession =
      dynamic_cast<DSTCUserSession *>(m_rpGIUserSession->getBFSession());

   DString dstrMgmtCoId;
   m_rpGIUserSession->getField( NULL, SYSTMGMTS, dstrMgmtCoId );
   //if no permission, return
   bool bAmsReportModifyPermit =
      dstcUserSession->hasUpdatePermission(dstrMgmtCoId, UAF::AMS_REPORT) &&
      dstcUserSession->hasCreatePermission(dstrMgmtCoId, UAF::AMS_REPORT);
   pCmdUI->Enable(bAmsReportModifyPermit);
}

//*****************************************************************************
void CDSTCView::OnAMSReports()
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnAMSReports" ) );
   CWaitCursor cursor;

   m_statusBar.SetMessageStatusBar( TXT_LOAD_REPORTS );
   startCall();
   if( m_rpGIWorkSession )
   {
      if( CMD_MODELESS_INPROCESS != CommandDispatcher::getInstance()->invokeCommand( m_rpGIWorkSession, CMD_BPROC_REPORT, PROC_NO_TYPE, false, NULL ) )
      {  // Error processing
         ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
         m_statusBar.SetMessageStatusBar( NULL_STRING );
         return;
      }
   }
   m_statusBar.SetMessageStatusBar( NULL_STRING );
}

//*****************************************************************************

void CDSTCView::OnReportStatus()
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnReportStatus" ) );
   CWaitCursor cursor;

   m_statusBar.SetMessageStatusBar( TXT_LOAD_REPORTS );
   startCall();
   if( m_rpGIWorkSession )
   {
      if( CMD_MODELESS_INPROCESS != CommandDispatcher::getInstance()->invokeCommand( m_rpGIUserSession, CMD_BPROC_REPORT_STATUS, PROC_NO_TYPE, false, NULL ) )
      {  // Error processing
         ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
         m_statusBar.SetMessageStatusBar( NULL_STRING );
         return;
      }
   }
   m_statusBar.SetMessageStatusBar( NULL_STRING );
}

//******************************************************************************
void CDSTCView::OnTradeSearch()
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnTradeSearch()"));

   CWaitCursor wait;

   onSystemMenuItem( TXT_TRADE_SEARCH,
                     CMD_BPROC_TRADE_SEARCH,
                false,
                I_( "" ) );
}

//******************************************************************************
void CDSTCView::OnUpdateTradeSearch(CCmdUI* pCmdUI)
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateTradeSearch") );
   DSTCUserSession *dstcUserSession =
      dynamic_cast<DSTCUserSession *>(m_rpGIUserSession->getBFSession());

   DString dstrMgmtCoId;
   m_rpGIUserSession->getField( NULL, SYSTMGMTS, dstrMgmtCoId );
   pCmdUI->Enable(dstcUserSession->hasReadPermission( dstrMgmtCoId, UAF::TRADE_SEARCH ));
}

//******************************************************************************
void CDSTCView::OnTrailerFeeSetup()
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnTrailerFeeSetup()"));

    DString dstrParamsIDI;

   addIDITagValue (dstrParamsIDI, I_("AccountNum"), I_("ALL"));
    addIDITagValue (dstrParamsIDI, I_("BrowserTitle"),I_("Trailer Fee Setup : ") );
    addIDITagValue (dstrParamsIDI, I_("screen"),I_("TrailerFeeSetup") );

    onSystemMenuItem(TXT_INTERFACE_FILE, CMD_BPROC_TRAILER_FEE_SETUP, false, dstrParamsIDI);
}

//******************************************************************************
void CDSTCView::OnUpdateTrailerFeeSetup(CCmdUI* pCmdUI)
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateTrailerFeeSetup") );

   DSTCUserSession *dstcUserSession = dynamic_cast<DSTCUserSession *>(m_rpGIUserSession->getBFSession());
   DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(m_rpGIWorkSession->getBFWorkSession());

   DString dstrMgmtCoId;
   DString dstrTrailerFeeArch;

   dstWorkSession->getOption( ifds::TrailerFeeArch, dstrTrailerFeeArch, BF::HOST, false );

   m_rpGIUserSession->getField( NULL, SYSTMGMTS, dstrMgmtCoId );
   bool bHasReadPermission = dstcUserSession->hasReadPermission( dstrMgmtCoId, UAF::SYSTEMLVL_TRAILER_FEE_SETUP );
   pCmdUI->Enable (bHasReadPermission && dstrTrailerFeeArch == YES);
}


//******************************************************************************
void CDSTCView::OnUpdateFinancial(CCmdUI* pCmdUI)
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateFinancial") );

   DSTCUserSession *dstcUserSession =
      dynamic_cast<DSTCUserSession *>(m_rpGIUserSession->getBFSession());

   DString  mgmtCoId = I_( "" );;
   bool     bEnable  = true;

   m_rpGIUserSession->getField( NULL, SYSTMGMTS, mgmtCoId );

   bEnable = dstcUserSession->hasCreatePermission( mgmtCoId, UAF::TRADING_PURCHASE ) ||
             dstcUserSession->hasCreatePermission( mgmtCoId, UAF::TRADING_EXCHANGE ) ||
             dstcUserSession->hasCreatePermission( mgmtCoId, UAF::TRADING_REDEMPTION);

   // Trade Entry menu option
   pCmdUI->Enable(bEnable);
}

//******************************************************************************
void CDSTCView::OnUpdateSettlement(CCmdUI* pCmdUI)
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateSettlement") );
   DSTCUserSession *dstcUserSession =
      dynamic_cast<DSTCUserSession *>(m_rpGIUserSession->getBFSession());

   DString  mgmtCoId = I_( "" );;
   bool     bEnable  = true;

   m_rpGIUserSession->getField( NULL, SYSTMGMTS, mgmtCoId );

   bEnable = dstcUserSession->hasReadPermission( mgmtCoId, UAF::SETTLE_ALL_TRADE ) ||
             dstcUserSession->hasReadPermission( mgmtCoId, UAF::SETTLE_ACCOUNT ) ||
             dstcUserSession->hasReadPermission( mgmtCoId, UAF::SETTLE_WIRE_ORDER ) ||
             dstcUserSession->hasReadPermission( mgmtCoId, UAF::SETTLE_BROKER );

   // Settlement menu option
   pCmdUI->Enable(bEnable);
}

//Menu Handlers

//******************************************************************************
void CDSTCView::OnHistoricalInfoSrch()
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnHistoricalInfoSrch"));

   onSystemMenuItem(TXT_LOAD_HISTORICAL_INFO_SEARCH,
      CMD_BPROC_HISTORICAL_INFO_SRCH, true);
}

//******************************************************************************
void CDSTCView::OnUpdateHistoricalInfoSrch(CCmdUI* pCmdUI)
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateHistoricalInfoSrch") );
   bool enable = !m_rpGIWorkSession;
   if( m_rpGIWorkSession )
   {
      int childrecnt = m_rpGIWorkSession->getGIContainer()->getChildCount( m_rpGIWorkSession );
      if( childrecnt == 0 ) { enable = true;    }
   }
   pCmdUI->Enable( enable );
}

//*****************************************************************************
void CDSTCView::OnBrokerAMS()
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBrokerAMS" ));

   onSystemMenuItem(TXT_LOAD_AMS_BROKER_DATA,
      CMD_BPROC_AMSBROKER, true);
}

//*****************************************************************************
void CDSTCView::OnUpdateBrokerAMS(CCmdUI* pCmdUI)
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateBrokerAMS") );

   pCmdUI->Enable(enableSystemMenuItem(UAF::BROKER_AMS_RESTRICT));
}

//******************************************************************************
void CDSTCView::OnProtectedfundsetup()
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnProtectedfundsetup"));

   onSystemMenuItem(TXT_LOAD_PROTECTED_FUND_DATA,
      CMD_BPROC_PROTECTED_FUND, true);
}

//******************************************************************************
void CDSTCView::OnUpdateProtectedfundsetup(CCmdUI* pCmdUI)
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateProtectedfundsetup") );

   pCmdUI->Enable(enableSystemMenuItem(UAF::PROTECTED_FUND_SETUP));
}


//******************************************************************************
void CDSTCView::OnDailyTransactionsFees()
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnDailyTransactionsFees"));

   DString dstrParamsIDI;

   addIDITagValue (dstrParamsIDI, MFCAN_IP_PARAM::SEARCH_TYPE,
      SEARCH_TYPE::DAILY_TRANSACTIONS_FEES);
   addIDITagValue (dstrParamsIDI, MFCAN_IP_PARAM::SEARCH_CRITERIA,
      DTF_SEARCH_CRITERIA::DAILY_TRANSACTIONS_FEES);
   onSystemMenuItem (TXT_LOAD_DAILY_TRANSACTIONS_FEES,
      CMD_BPROC_FEATURES_SEARCH, false, dstrParamsIDI);
}

//******************************************************************************
void CDSTCView::OnUpdateDailyTransactionsFees(CCmdUI* pCmdUI)
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateDailyTransactionsFees") );

   pCmdUI->Enable (enableSystemMenuItem (UAF::DAILY_TRANSACTIONS_FEES));
}


//*****************************************************************************
void CDSTCView::OnSystemLevelFee()
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnSystemLevelFee") );

   onSystemMenuItem(TXT_SYSTEM_LEVEL_FEE,
      CMD_BPROC_FEE_PARAMETER_SYSTEM, true);
}

//******************************************************************************
void CDSTCView::OnUpdateSystemLevelFee(CCmdUI* pCmdUI)
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateGlobalAMS") );
   bool enable = !m_rpGIWorkSession;
   if( m_rpGIWorkSession )
   {
      int childrecnt = m_rpGIWorkSession->getGIContainer()->getChildCount( m_rpGIWorkSession );
      if( childrecnt == 0 ) { enable = true;    }
   }

   if(enable)
   {
      if( !m_rpGIWorkSession )
      {
         if( CommandDispatcher::getInstance()->invokeCommand( m_rpGIUserSession,
         CMD_BPROC_WORK_SESSION, PROC_NO_TYPE, false, &m_rpGIWorkSession ) != CMD_MODELESS_INPROCESS )
         {  // Error handling
            ASSERT( 0 );
            return;
         }
      }
      if( m_rpGIWorkSession )
      {
         DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(m_rpGIWorkSession->getBFWorkSession());

         enable = enableSystemMenuItem(UAF::FEE_PARAMETER_SYSTEM);
      }
   }
   pCmdUI->Enable(enable);
}

//***********************************************************************************
void CDSTCView::OnGlobalAMS()
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnGlobalAMS"));

   onSystemMenuItem(TXT_LOAD_AMS_GLOBAL, CMD_BPROC_AMS_GLOBAL, true);
}

//******************************************************************************
void CDSTCView::OnUpdateGlobalAMS(CCmdUI* pCmdUI)
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateGlobalAMS") );

   pCmdUI->Enable(enableSystemMenuItem(UAF::AMS_GLOBAL));
}


//*****************************************************************************
void CDSTCView::OnMktIndexValues()
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnMktIndexValues" ) );

   onSystemMenuItem(TXT_LOAD_MKT_INDEX_VALUES,
      CMD_BPROC_MKT_INDEX_VALUES, false);
}

//*****************************************************************************
void CDSTCView::OnUpdateMktIndexValues(CCmdUI* pCmdUI)
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateMktIndexValues") );
   pCmdUI->Enable(enableSystemMenuItem(UAF::MKT_INDEX_VALUES));
}


//*****************************************************************************
void CDSTCView::OnMktIndexMaster()
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnMktIndexMaster" ) );

   onSystemMenuItem(TXT_LOAD_MKT_INDEX_MASTER,
      CMD_BPROC_MKT_INDEX_MASTER, false);
}

//*****************************************************************************
void CDSTCView::OnUpdateMktIndexMaster(CCmdUI* pCmdUI)
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateMktIndexMaster") );

   pCmdUI->Enable(enableSystemMenuItem(UAF::MKT_INDEX_MASTER));
}

//*****************************************************************************
void CDSTCView::OnMsgInquirySearch()
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnMsgInquirySearch" ) );

   onSystemMenuItem( IDS_LOADING_MSG_SEARCH, CMD_BPROC_MSG_SEARCH, false );
}

//*****************************************************************************
void CDSTCView::OnUpdateMsgInquirySearch(CCmdUI* pCmdUI)
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateMsgInquirySearch") );

   pCmdUI->Enable( enableSystemMenuItem( UAF::MSG_SEARCH ) );
}

//*****************************************************************************
void CDSTCView::OnFileInquirySearch()
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnFileInquirySearch" ) );

   onSystemMenuItem( IDS_LOADING_FILE_SEARCH, CMD_BPROC_FILE_SEARCH, false );
}

//*****************************************************************************
void CDSTCView::OnUpdateFileInquirySearch(CCmdUI* pCmdUI)
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateFileInquirySearch") );

   pCmdUI->Enable( enableSystemMenuItem( UAF::FILE_SEARCH ) );
}


//*****************************************************************************
void CDSTCView::OnCancellationInstr()
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnCancellationInstr" ) );

   onSystemMenuItem( ID_TRANSACTIONS_CANCELLATIONINSTRUCTION, CMD_BPROC_CANCELLATION_INSTR, false );
}

//*****************************************************************************
void CDSTCView::OnUpdateCancellationInstr(CCmdUI* pCmdUI)
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateCancellationInstr") );

   pCmdUI->Enable( enableSystemMenuItem( UAF::CANCELLATION_INSTRUCTION) );
}


//*****************************************************************************
void CDSTCView::OnManualDividend()
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnManualDividend" ) );

   DString dstrParamsIDI;

   addIDITagValue (dstrParamsIDI, MFCAN_IP_PARAM::CALLER, I_("ManualDividend"));
   onSystemMenuItem(TXT_LOAD_MANUAL_DIVIDEND, CMD_BPROC_TRADES, false, dstrParamsIDI);
}

//*****************************************************************************
void CDSTCView::OnUpdateManualDividend(CCmdUI* pCmdUI)
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateManualDividend"));
   pCmdUI->Enable(enableSystemMenuItem(UAF::MANUAL_DIVIDEND));
}

//*****************************************************************************

void CDSTCView::OnSettlementLocation()
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnSettlementLocation" ) );

   onSystemMenuItem(TXT_LOAD_SETTLELOC_SYSLVL, CMD_BPROC_SETTLEMENT_INSTRUCTIONS_SYSLVL, false);
}

//*****************************************************************************
void CDSTCView::OnUpdateSettlementLocation(CCmdUI* pCmdUI)
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateSettlementLocation"));
   pCmdUI->Enable( enableSystemMenuItem(UAF::SETTLE_LOCATION_SYS_LVL) );
}

//*****************************************************************************

void CDSTCView::OnFeeModel()
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnFeeModel" ) );
   DString dstrParamsIDI;

   addIDITagValue (dstrParamsIDI, MFCAN_IP_PARAM::SEARCH_TYPE,
      SEARCH_TYPE::SYSTEM );
   onSystemMenuItem(TXT_LOAD_CLIENT_FEE_MODEL, CMD_BPROC_FEE_MODEL, true, dstrParamsIDI);
}

//*****************************************************************************
void CDSTCView::OnUpdateFeeModel(CCmdUI* pCmdUI)
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateFeeModel"));
   pCmdUI->Enable( enableSystemMenuItem(UAF::FEE_MODEL) );
}

//*****************************************************************************

void CDSTCView::OnFundSponsorFeeModel()
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnFundSponsorFeeModel" ) );
   DString dstrParamsIDI;

   addIDITagValue (dstrParamsIDI, MFCAN_IP_PARAM::SEARCH_TYPE,
      SEARCH_TYPE::FUNSSPONSORFEEMODEL);
   addIDITagValue (dstrParamsIDI, MFCAN_IP_PARAM::SEARCH_CRITERIA,
      FEEMODEL_SEARCH_CRITERIA::FUNDSPONSORMODEL );

   onSystemMenuItem(TXT_LOAD_FUND_SPONSOR_FEE_MODEL, CMD_BPROC_FEATURES_SEARCH, false, dstrParamsIDI);
}

//*****************************************************************************
void CDSTCView::OnUpdateFundSponsorFeeModel(CCmdUI* pCmdUI)
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateFundSponsorFeeModel"));
   pCmdUI->Enable( enableSystemMenuItem(UAF::FUNDSPONSOR_FEE_MODEL) );
}


//*****************************************************************************

void CDSTCView::OnFundBroker()
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnFeeModel" ) );
   //onSystemMenuItem(TXT_LOAD_FUND_BROKER, CMD_BPROC_FUND_BROKER, false );
   DString dstrParamsIDI;

   addIDITagValue (dstrParamsIDI, MFCAN_IP_PARAM::SEARCH_TYPE,
      SEARCH_TYPE::FUNDBROKER);
   addIDITagValue (dstrParamsIDI, MFCAN_IP_PARAM::SEARCH_CRITERIA,
      FUNDBROKER_SEARCH_CRITERIA::FUNDBROKER );

   onSystemMenuItem(TXT_LOAD_FUND_BROKER, CMD_BPROC_FEATURES_SEARCH, false, dstrParamsIDI);
}

//*****************************************************************************
void CDSTCView::OnUpdateFundBroker(CCmdUI* pCmdUI)
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateFeeModel"));

   pCmdUI->Enable( enableSystemMenuItem(UAF::FUND_BROKER_MAINTENANCE) );
}

//*****************************************************************************

void CDSTCView::OnAggregateOrder()
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnAggregateOrder" ) );
   //onSystemMenuItem(TXT_LOAD_FUND_BROKER, CMD_BPROC_FUND_BROKER, false );
   DString dstrParamsIDI;

   addIDITagValue (dstrParamsIDI, MFCAN_IP_PARAM::SEARCH_TYPE,
      SEARCH_TYPE::AGGREGATEDORDER);
   addIDITagValue (dstrParamsIDI, MFCAN_IP_PARAM::SEARCH_CRITERIA,
      AGGREGATION_SEARCH_CRITERIA::AGGREGATION );

   onSystemMenuItem(TXT_LOAD_AGGREGATED_ORDER, CMD_BPROC_FEATURES_SEARCH, false, dstrParamsIDI);
}

//*****************************************************************************
void CDSTCView::OnUpdateAggregateOrder(CCmdUI* pCmdUI)
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateAggregateOrder"));

   pCmdUI->Enable( enableSystemMenuItem(UAF::AGGREGATED_ORDER_INFORMATION) );
}

//*****************************************************************************
void CDSTCView::OnPayToEntity()
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnPayToEntity"));

   DString dstrParamsIDI;

   addIDITagValue(dstrParamsIDI, MFCAN_IP_PARAM::SEARCH_TYPE,
      SEARCH_TYPE::BROKER_FEATURES);
   addIDITagValue(dstrParamsIDI, MFCAN_IP_PARAM::SEARCH_CRITERIA,
      BF_SEARCH_CRITERIA::PAY_TO_ENTITY);
   //addIDITagValue(dstrParamsIDI, MFCAN_IP_PARAM::BACKGROUND_SEARCH, I_("Y"));
   onSystemMenuItem(TXT_LOAD_PAY_TO_ENTITY, CMD_BPROC_FEATURES_SEARCH,
      false, dstrParamsIDI);
}

//*****************************************************************************
void CDSTCView::OnUpdatePayToEntity(CCmdUI* pCmdUI)
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdatePayToEntity"));

   pCmdUI->Enable(enableSystemMenuItem(UAF::PAY_TO_ENTITY));
}

//*****************************************************************************
void CDSTCView::OnPaymentBatch()
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnPaymentBatch"));
   DString dstrParamsIDI;

   addIDITagValue (dstrParamsIDI, I_("BrowserTitle"),I_("Payment Release: "));
   addIDITagValue (dstrParamsIDI, I_("from_screen"), I_("MainScreen"));
   addIDITagValue (dstrParamsIDI, I_("screen"), I_("PaymentRelease"));
   onSystemMenuItem (TXT_LOAD_PAY_TO_ENTITY, CMD_BPROC_PAYMENT_BATCH, false, dstrParamsIDI);
}

//*****************************************************************************
void CDSTCView::OnPaymentSearch()
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnPaymentSearch"));
   DString dstrParamsIDI;

   addIDITagValue (dstrParamsIDI, I_("BrowserTitle"), I_("Payment Information: "));
   addIDITagValue (dstrParamsIDI, I_("from_screen"), I_("MainScreen"));
   addIDITagValue (dstrParamsIDI, I_("screen"), I_("PaymentInformation"));
   onSystemMenuItem (TXT_LOAD_PAY_TO_ENTITY, CMD_BPROC_PAYMENT_SEARCH, false, dstrParamsIDI);
}

//*****************************************************************************
void CDSTCView::OnUpdatePaymentBatch(CCmdUI* pCmdUI)
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdatePaymentBatch"));

   DString dstrMarket = DSTCommonFunctions::getMarket();
   pCmdUI->Enable( true );
   pCmdUI->Enable( enableSystemMenuItem(UAF::PAYMENT_BATCH) && dstrMarket != MARKET_IDS::CANADA );
}

//*****************************************************************************
void CDSTCView::OnUpdatePaymentSearch(CCmdUI* pCmdUI)
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdatePaymentSearch"));

   DString dstrMarket = DSTCommonFunctions::getMarket();
   pCmdUI->Enable( enableSystemMenuItem(UAF::PAYMENT_SEARCH) && dstrMarket != MARKET_IDS::CANADA );
}

//*****************************************************************************
void CDSTCView::OnFundLimitation()
{
    MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnFundLimitation"));

    DString dstrParamsIDI;

    addIDITagValue (dstrParamsIDI, I_("option"), I_("brokerBranchRep") );
    addIDITagValue (dstrParamsIDI, I_("BrowserTitle"),I_("Fund Limitation : ") );
    addIDITagValue (dstrParamsIDI, I_("screen"),I_("OvrdLimit") );

    onSystemMenuItem(TXT_FUND_CLASS_LIMITATION, CMD_BPROC_FUND_CLASS_LIMITATION, false, dstrParamsIDI);
}

//*****************************************************************************
void CDSTCView::OnUpdateFundLimitation (CCmdUI* pCmdUI)
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateFundLimitation"));

   pCmdUI->Enable( enableSystemMenuItem(UAF::BROKER_TRADING_OVERRIDES) );
}

//*****************************************************************************
void CDSTCView::OnRegulatoryStandards ()
{
    MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnRegulatoryStandards"));

    DString dstrParamsIDI;

    CString cstrBrowserTitle;
    cstrBrowserTitle.LoadString(TXT_REGULATORY_STANDARDS);

	addIDITagValue (dstrParamsIDI, I_("from_screen"), I_("MainScreen"));
	addIDITagValue (dstrParamsIDI, I_("BrowserTitle"), cstrBrowserTitle);
	addIDITagValue (dstrParamsIDI, I_("screen"), I_("RegStandards"));

    onSystemMenuItem(TXT_REGULATORY_STANDARDS, CMD_BPROC_REGULATORY_STANDARDS, false, dstrParamsIDI);
}

//*****************************************************************************
void CDSTCView::OnUpdateRegulatoryStandards (CCmdUI* pCmdUI)
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateRegulatoryStandards"));

   pCmdUI->Enable( enableSystemMenuItem(UAF::REGULATORY_STANDARDS) );
}

//*****************************************************************************
void CDSTCView::OnRegulatoryDocuments ()
{
    MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnRegulatoryDocuments"));

    DString dstrParamsIDI;
    CString cstrBrowserTitle;
    cstrBrowserTitle.LoadString(TXT_REGULATORY_DOCUMENTS);

   addIDITagValue (dstrParamsIDI, I_("from_screen"), I_("MainScreen"));
   addIDITagValue (dstrParamsIDI, I_("BrowserTitle"), cstrBrowserTitle);
   addIDITagValue (dstrParamsIDI, I_("screen"), I_("RegDoc"));

    onSystemMenuItem(TXT_REGULATORY_DOCUMENTS, CMD_BPROC_REGULATORY_DOCUMENTS, false, dstrParamsIDI);
}

//*****************************************************************************
void CDSTCView::OnUpdateRegulatoryDocuments (CCmdUI* pCmdUI)
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateRegulatoryDocuments"));

   pCmdUI->Enable( enableSystemMenuItem(UAF::REGULATORY_DOCUMENTS) );
}

//*****************************************************************************
void CDSTCView::OnInterfaceFile ()
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnInterfaceFile"));

   DString dstrParamsIDI;

   addIDITagValue (dstrParamsIDI, I_("AccountNum"), I_("ALL"));
   addIDITagValue (dstrParamsIDI, I_("BrowserTitle"), I_("Interface File : "));
   addIDITagValue (dstrParamsIDI, I_("screen"), I_("RESPInterfaceFile"));

   onSystemMenuItem(TXT_INTERFACE_FILE, CMD_BPROC_INTERFACE_FILE, false, dstrParamsIDI);
}

//*****************************************************************************
void CDSTCView::OnUpdateInterfaceFile (CCmdUI* pCmdUI)
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateInterfaceFile"));

   pCmdUI->Enable( enableSystemMenuItem(UAF::RESP_INTERFACE_FILE) );
}
//*****************************************************************************
void CDSTCView::OnFundMaster()
{
    MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnFundMaster"));

    DString dstrParamsIDI;

    addIDITagValue (dstrParamsIDI, I_("BrowserTitle"),I_("Fund Master: ") );

    onSystemMenuItem (TXT_FUND_MASTER_INQ, CMD_BPROC_FUND_MASTER, false, dstrParamsIDI);
}

//*****************************************************************************
void CDSTCView::OnUpdateFundMaster(CCmdUI* pCmdUI)
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateFundMaster"));

   pCmdUI->Enable( enableSystemMenuItem (UAF::FUND_MASTER) );
}

//*****************************************************************************
void CDSTCView::OnFundClassCopy()
{
    MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnFundClassCopy"));

    DString dstrParamsIDI;

    addIDITagValue (dstrParamsIDI, I_("BrowserTitle"), I_("Fund Class Copy:"));
    addIDITagValue (dstrParamsIDI, I_("screen"), I_("ClassCopy")); //DesktopWeb conversion

    onSystemMenuItem(TXT_FUND_CLASS_COPY, CMD_BPROC_FUND_CLASS_COPY, false, dstrParamsIDI);
}

//*****************************************************************************
void CDSTCView::OnUpdateFundClassCopy (CCmdUI* pCmdUI)
{
   MAKEFRAME2 (CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateFundClassCopy"));

   pCmdUI->Enable (enableSystemMenuItem(UAF::FUND_CLASS_COPY) );
}

//*****************************************************************************
void CDSTCView::OnFundClassMaintenance ()
{
   MAKEFRAME2 (CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnFundClassMaintenance"));

   DString dstrParamsIDI;
   CString cstrBrowserTitle;
   cstrBrowserTitle.LoadString(TXT_FND_CLS_MAINT);

   addIDITagValue (dstrParamsIDI, I_("BrowserTitle"), cstrBrowserTitle);
   addIDITagValue (dstrParamsIDI, I_("screen"), I_("ClassSetup_Search"));
   addIDITagValue (dstrParamsIDI, I_("createCache"), I_("true"));

   onSystemMenuItem (TXT_FUND_CLASS_COPY, CMD_BPROC_FUND_CLASS_MAINTENANCE, false, dstrParamsIDI);
}

//*****************************************************************************
void CDSTCView::OnUpdateFundClassMaintenance (CCmdUI* pCmdUI)
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateFundClassMaintenance"));

   pCmdUI->Enable (enableSystemMenuItem(UAF::FUND_CLASS_MAINTENANCE));
}


//*****************************************************************************
void CDSTCView::OnMFAndMFRInvoiceInstruction()
{
   MAKEFRAME2 (CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnMFAndMFRInvoiceInstruction"));

   DString dstrParamsIDI;

   addIDITagValue (dstrParamsIDI, I_("BrowserTitle"), I_("Invoice Instruction Maintenance"));
   addIDITagValue (dstrParamsIDI, I_("screen"),       I_("InvoiceInstr"));
   addIDITagValue (dstrParamsIDI, I_("from_screen"),  I_("MainScreen"));

   onSystemMenuItem (TXT_INVOICE_INSTRUCTION, CMD_BPROC_INVOICE_INSTRUCTION, true, dstrParamsIDI);
}

//*****************************************************************************
void CDSTCView::OnUpdateMFAndMFRInvoiceInstruction(CCmdUI* pCmdUI)
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateMFAndMFRInvoiceInstruction"));

   pCmdUI->Enable( enableSystemMenuItem(UAF::INVOICE_INSTRUCTION) );
}

//*****************************************************************************
void CDSTCView::OnMFAndMFRReportGroup()
{
   MAKEFRAME2 (CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnMFAndMFRReportGroup"));

   DString dstrParamsIDI;

   addIDITagValue (dstrParamsIDI, I_("BrowserTitle"), I_("Report Group Maintenance"));
   addIDITagValue (dstrParamsIDI, I_("screen"),       I_("ReportGroup"));
   addIDITagValue (dstrParamsIDI, I_("from_screen"),  I_("MainScreen"));

   onSystemMenuItem (TXT_REPORT_GROUP, CMD_BPROC_REPORT_GROUP, true, dstrParamsIDI);
}

//*****************************************************************************
void CDSTCView::OnUpdateMFAndMFRReportGroup(CCmdUI* pCmdUI)
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateMFAndMFRReportGroup"));

   pCmdUI->Enable( enableSystemMenuItem(UAF::REPORT_GROUP) );
}

//*****************************************************************************
void CDSTCView::OnMFAndMFRAdditionalAssets()
{
   MAKEFRAME2 (CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnMFAndMFRAdditionalAssets"));

   DString dstrParamsIDI;

   addIDITagValue (dstrParamsIDI, I_("BrowserTitle"), I_("Additional Assets Maintenance"));
   addIDITagValue (dstrParamsIDI, I_("screen"),       I_("AdditionalAsset"));
   addIDITagValue (dstrParamsIDI, I_("from_screen"),  I_("MainScreen"));

   onSystemMenuItem (TXT_ADDITIONAL_ASSETS, CMD_BPROC_ADDITIONAL_ASSETS, true, dstrParamsIDI);
}

//*****************************************************************************
void CDSTCView::OnUpdateMFAndMFRAdditionalAssets(CCmdUI* pCmdUI)
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateMFAndMFRAdditionalAssets"));

   pCmdUI->Enable (enableSystemMenuItem(UAF::ADDITIONAL_ASSETS));
}

//*****************************************************************************
void CDSTCView::OnPaymentInstructions ()
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnPaymentInstructions"));

   DString dstrParamsIDI;

   addIDITagValue(dstrParamsIDI, MFCAN_IP_PARAM::SEARCH_TYPE,
      SEARCH_TYPE::BROKER_FEATURES);
   addIDITagValue(dstrParamsIDI, MFCAN_IP_PARAM::SEARCH_CRITERIA,
      BF_SEARCH_CRITERIA::PAYMENT_INSTRUCTIONS);
   //addIDITagValue(dstrParamsIDI, MFCAN_IP_PARAM::BACKGROUND_SEARCH, I_("Y"));
   onSystemMenuItem(TXT_LOAD_PAYMENT_INSTRUCTIONS,
      CMD_BPROC_FEATURES_SEARCH, false, dstrParamsIDI);
}

//*****************************************************************************
void CDSTCView::OnUpdatePaymentInstructions(CCmdUI* pCmdUI)
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdatePaymentInstructions"));

   pCmdUI->Enable(enableSystemMenuItem(UAF::PAYMENT_INSTRUCTIONS));
}

//*****************************************************************************
void CDSTCView::OnAccountBalanceOverride()
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION,
               CLASSNAME,
               I_( "OnAccountBalanceOverride(  )" ) );

   DString dstrParamsIDI;

   CString cstrBrowserTitle;
   cstrBrowserTitle.LoadString(TXT_ACCOUNT_BALANCE_OVERRIDE);

   addIDITagValue (dstrParamsIDI, I_("from_screen"), I_("MainScreen"));
   addIDITagValue (dstrParamsIDI, I_("BrowserTitle"), cstrBrowserTitle);
   addIDITagValue (dstrParamsIDI, I_("screen"), I_("AcctBalOvrd"));

   onSystemMenuItem (TXT_LOAD_ACCOUNT_BALANCE_OVERRIDE, CMD_BPROC_ACCOUNT_BALANCE_OVERRIDE, false, dstrParamsIDI);
}

//*****************************************************************************
void CDSTCView::OnUpdateAccountBalanceOverride(CCmdUI* pCmdUI)
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION,
               CLASSNAME,
               I_("OnUpdateAccountBalanceOverride"));

   pCmdUI->Enable( enableSystemMenuItem( UAF::ACCOUNT_BALANCE_OVERRIDE ) );
}

//*****************************************************************************
void CDSTCView::OnDilutionCalculator()
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION,
               CLASSNAME,
               I_( "OnDilutionCalculator(  )" ) );

   DString dstrParamsIDI;

   addIDITagValue (dstrParamsIDI, I_("from_screen"), I_("MainScreen"));
   addIDITagValue (dstrParamsIDI, I_("BrowserTitle"), I_("Dilution Calculator:"));
   addIDITagValue (dstrParamsIDI, I_("screen"), I_("DilutionCalculator"));
   onSystemMenuItem( TXT_LOAD_DILUTION_CALCULATOR, CMD_BPROC_DILUTION_CALCULATOR, false, dstrParamsIDI );
}

//*****************************************************************************
void CDSTCView::OnUpdateDilutionCalculator(CCmdUI* pCmdUI)
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION,
               CLASSNAME,
               I_("OnUpdateDilutionCalculator"));

   //pCmdUI->Enable( TRUE ); // temp - uncomment for testing
   pCmdUI->Enable( enableSystemMenuItem( UAF::DILUTION_CALCULATOR ) );
}

//*****************************************************************************
void CDSTCView::OnMgmtCoPayToEntity()
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnMgmtCoPayToEntity"));

   DString dstrParamsIDI;

   addIDITagValue(dstrParamsIDI, MFCAN_IP_PARAM::SEARCH_TYPE_MGMT, I_("MgmtCo"));

   onSystemMenuItem(TXT_LOAD_PAY_ENTITY,
      CMD_BPROC_PAY_TO_ENTITY, false, dstrParamsIDI);
}

//*****************************************************************************
void CDSTCView::OnUpdateMgmtCoPayToEntity(CCmdUI* pCmdUI)
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateMgmtCoPayToEntity"));

   DString dstrMgmtCoPayReq, dstrSplitComm;

   if( !m_rpGIWorkSession )
   {
      if( CommandDispatcher::getInstance()->invokeCommand( m_rpGIUserSession,
                                                            CMD_BPROC_WORK_SESSION, PROC_NO_TYPE, false, &m_rpGIWorkSession )
            != CMD_MODELESS_INPROCESS )
      {  // Error handling
         ASSERT( 0 );
         return;
      }
   }
   if ( m_rpGIWorkSession )
   {
      DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(m_rpGIWorkSession->getBFWorkSession());
      dstWorkSession->getOption( ifds::MgmtCoPayReq, dstrMgmtCoPayReq, BF::HOST, false );
      dstWorkSession->getOption( ifds::SplitComm, dstrSplitComm, BF::HOST, false );

      bool bEnableMenu = enableSystemMenuItem(UAF::MGMTCO_PAYMENT_INSTRUCTION) &&
                        dstrMgmtCoPayReq == YES && dstrSplitComm == YES;

      pCmdUI->Enable(bEnableMenu);
   }
}

//*****************************************************************************
void CDSTCView::OnMgmtCoPaymentInstr()
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnMgmtCoPaymentInstr"));

   DString dstrParamsIDI;

   addIDITagValue(dstrParamsIDI, MFCAN_IP_PARAM::SEARCH_TYPE_MGMT, I_("MgmtCo"));
   addIDITagValue(dstrParamsIDI, I_("PaymentFor"), I_("CO"));
   addIDITagValue(dstrParamsIDI, I_("PayToEntity"), I_("CLIENT"));
   onSystemMenuItem(TXT_LOAD_PAYMENT_INSTRUCTIONS,
      CMD_BPROC_PAYMENT_INSTRUCTIONS, false, dstrParamsIDI);
}

//*****************************************************************************
void CDSTCView::OnUpdateMgmtCoPaymentInstr(CCmdUI* pCmdUI)
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateMgmtCoPaymentInstr"));

   DString dstrMgmtCoPayReq, dstrSplitComm;

   if( !m_rpGIWorkSession )
   {
      if( CommandDispatcher::getInstance()->invokeCommand( m_rpGIUserSession,
                                                            CMD_BPROC_WORK_SESSION, PROC_NO_TYPE, false, &m_rpGIWorkSession )
            != CMD_MODELESS_INPROCESS )
      {  // Error handling
         ASSERT( 0 );
         return;
      }
   }
   if( m_rpGIWorkSession )
   {
      DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(m_rpGIWorkSession->getBFWorkSession());
      dstWorkSession->getOption( ifds::MgmtCoPayReq, dstrMgmtCoPayReq, BF::HOST, false );
      dstWorkSession->getOption( ifds::SplitComm, dstrSplitComm, BF::HOST, false );

      bool bEnableMenu = enableSystemMenuItem(UAF::MGMTCO_PAYMENT_INSTRUCTION) &&
                        dstrMgmtCoPayReq == YES && dstrSplitComm == YES;

      pCmdUI->Enable(bEnableMenu);
   }
}

//*****************************************************************************
void CDSTCView::OnHoldingCompany()
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnHoldingCompany"));

   DString dstrParamsIDI;

   onSystemMenuItem(TXT_HOLDING_COMPANIES, CMD_BPROC_HOLDING_COMP, true);
}

//*****************************************************************************
void CDSTCView::OnUpdateHoldingCompany(CCmdUI* pCmdUI)
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateMgmtCoPaymentInstr"));

   DString dstrMgmtCoPayReq, dstrSplitComm;

   if( !m_rpGIWorkSession )
   {
      if( CommandDispatcher::getInstance()->invokeCommand( m_rpGIUserSession,
                                                            CMD_BPROC_WORK_SESSION, PROC_NO_TYPE, false, &m_rpGIWorkSession )
            != CMD_MODELESS_INPROCESS )
      {  // Error handling
         ASSERT( 0 );
         return;
      }
   }
   if( m_rpGIWorkSession )
   {
      DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(m_rpGIWorkSession->getBFWorkSession());

      bool bEnableMenu = enableSystemMenuItem(UAF::HOLDING_COMP_MAINT);
      pCmdUI->Enable(bEnableMenu);
   }
}

//*****************************************************************************
void CDSTCView::OnBrokerBanking()
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBrokerBanking"));

   DString dstrParamsIDI;

   addIDITagValue(dstrParamsIDI, MFCAN_IP_PARAM::SEARCH_TYPE,
      SEARCH_TYPE::BROKER_FEATURES);
   addIDITagValue(dstrParamsIDI, MFCAN_IP_PARAM::SEARCH_CRITERIA,
      BF_SEARCH_CRITERIA::BANKING);
   //addIDITagValue(dstrParamsIDI, MFCAN_IP_PARAM::BACKGROUND_SEARCH, I_("Y"));
   onSystemMenuItem(TXT_LOAD_BROKER_BANKING,
      CMD_BPROC_FEATURES_SEARCH, false, dstrParamsIDI);
}

//*****************************************************************************
void CDSTCView::OnUpdateBrokerBanking(CCmdUI* pCmdUI)
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateBrokerBanking"));

   pCmdUI->Enable(enableSystemMenuItem(UAF::BANKING_BROKER_CODE) ||
      enableSystemMenuItem(UAF::BANKING_BRANCH_CODE) ||
      enableSystemMenuItem(UAF::BANKING_REP_CODE));
}

//*****************************************************************************
void CDSTCView::OnFinancialInstitutions()
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnFinancialInstitutions"));

   DString dstrParamsIDI;

   addIDITagValue (dstrParamsIDI, MFCAN_IP_PARAM::SEARCH_TYPE,
      SEARCH_TYPE::FI_FEATURES);
   addIDITagValue (dstrParamsIDI, MFCAN_IP_PARAM::SEARCH_CRITERIA,
      FI_SEARCH_CRITERIA::INSTITUTIONS);
   onSystemMenuItem(TXT_LOAD_FINANCIAL_INSTITUTION,
      CMD_BPROC_FEATURES_SEARCH, false, dstrParamsIDI);
}

//*****************************************************************************
void CDSTCView::OnUpdateFinancialInstitutions (CCmdUI* pCmdUI)
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateFinancialInstitutions"));

   pCmdUI->Enable (enableSystemMenuItem(UAF::INSTITUTION_MAINTENANCE));
}

//*****************************************************************************
void CDSTCView::OnPortfolioSetup()
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnPortfolioSetup"));

   DString dstrParamsIDI;

   addIDITagValue (dstrParamsIDI, I_("from_screen"), I_("MainScreen"));
   addIDITagValue (dstrParamsIDI, I_("BrowserTitle"), I_("Portfolio Setup:"));
   addIDITagValue (dstrParamsIDI, I_("screen"),I_("PortfolioSetup") );
   onSystemMenuItem(TXT_LOAD_PORTFOLIO_SETUP,
      CMD_BPROC_PORTFOLIO_SETUP, false, dstrParamsIDI);
}

//*****************************************************************************
void CDSTCView::OnUpdatePortfolioSetup (CCmdUI* pCmdUI)
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdatePortfolioSetup"));

   pCmdUI->Enable (enableSystemMenuItem(UAF::PORTFOLIO_SETUP));
}

//*****************************************************************************
void CDSTCView::OnCommisionReduction()
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnCommisionReduction"));

   DString dstrParamsIDI, strBrowserTitle;

   CString cstrBrowserTitle;
   cstrBrowserTitle.LoadString(TXT_COMMISSION_REDUCTION);
   strBrowserTitle = cstrBrowserTitle;
   strBrowserTitle += I_(":");

   addIDITagValue (dstrParamsIDI, I_("from_screen"), I_("MainScreen"));
   addIDITagValue (dstrParamsIDI, I_("BrowserTitle"), strBrowserTitle);
   addIDITagValue (dstrParamsIDI, I_("screen"),I_("CommRed") );
   onSystemMenuItem(TXT_LOAD_COMMISSION_REDUCTION,
      CMD_BPROC_COMMISSION_REDUCTION, false, dstrParamsIDI);
}

//*****************************************************************************
void CDSTCView::OnUpdateCommisionReduction (CCmdUI* pCmdUI)
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateCommisionReduction"));

   pCmdUI->Enable (enableSystemMenuItem(UAF::COMMISSION_REDUCTION));
}

//*****************************************************************************
void CDSTCView::OnInterestRateConfiguration()
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnInterestRateConfiguration"));

   DString dstrParamsIDI, strBrowserTitle;

   CString cstrBrowserTitle;
   cstrBrowserTitle.LoadString(TXT_INTEREST_RATE_CONFIGURATION);
   strBrowserTitle = cstrBrowserTitle;
   strBrowserTitle += I_(":");

   addIDITagValue (dstrParamsIDI, I_("from_screen"), I_("MainScreen"));
   addIDITagValue (dstrParamsIDI, I_("BrowserTitle"), strBrowserTitle);
   addIDITagValue (dstrParamsIDI, I_("screen"),I_("InterestRateConfig") );
   onSystemMenuItem(TXT_LOAD_INTEREST_RATE_CONFIG,
      CMD_BPROC_INTEREST_CONFIGURATION, false, dstrParamsIDI);
}

//*****************************************************************************
void CDSTCView::OnUpdateInterestRateConfiguration(CCmdUI* pCmdUI)
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateInterestRateConfiguration"));

   pCmdUI->Enable (enableSystemMenuItem(UAF::INTEREST_CONFIGURATION));
}

//*****************************************************************************
void CDSTCView::OnInterestRateMaintenance()
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnInterestRateMaintenance"));

   DString dstrParamsIDI, strBrowserTitle;

   CString cstrBrowserTitle;
   cstrBrowserTitle.LoadString(TXT_INTEREST_RATE_MAINTENANCE);
   strBrowserTitle = cstrBrowserTitle;
   strBrowserTitle += I_(":");

   addIDITagValue (dstrParamsIDI, I_("from_screen"), I_("MainScreen"));
   addIDITagValue (dstrParamsIDI, I_("BrowserTitle"), strBrowserTitle);
   addIDITagValue (dstrParamsIDI, I_("screen"),I_("IntRateMain") );
   onSystemMenuItem(TXT_LOAD_INTEREST_RATE_MAINTENANCE,
      CMD_BPROC_INTEREST_MAINTENANCE, false, dstrParamsIDI);
}

//*****************************************************************************
void CDSTCView::OnUpdateInterestRateMaintenance(CCmdUI* pCmdUI)
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateInterestRateMaintenance"));

   pCmdUI->Enable (enableSystemMenuItem(UAF::INTEREST_MAINTENANCE));
}

//*****************************************************************************
void CDSTCView::OnSegMaintenanceGuaranteeRules ()
{
   MAKEFRAME2 (CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnSegMaintenanceGuaranteeRules"));

   DString dstrParamsIDI;

   addIDITagValue (dstrParamsIDI, I_("from_screen"), I_("MainScreen"));
   addIDITagValue (dstrParamsIDI, I_("BrowserTitle"), I_("SEG Guarantee Rules"));
   addIDITagValue (dstrParamsIDI, I_("screen"),I_("GuaranteeRule") );
   onSystemMenuItem (TXT_LOAD_GUARANTEE_RULES,
      CMD_BPROC_SEG_GUARANTEE_RULES, false, dstrParamsIDI);
}

//*****************************************************************************
void CDSTCView::OnUpdateMaintenanceGuaranteeRules (CCmdUI* pCmdUI)
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateMaintenanceGuaranteeRules"));

   pCmdUI->Enable (enableSystemMenuItem (UAF::GUARANTEE_RULES));
}

//*****************************************************************************
void CDSTCView::OnRESPDiplomaMenuItem()
{
   MAKEFRAME2 (CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnRESPDiplomaMenuItem"));

   DString dstrParamsIDI;

   addIDITagValue (dstrParamsIDI, I_("from_screen"), I_("MainScreen"));
   addIDITagValue (dstrParamsIDI, I_("BrowserTitle"), I_("RESP Diploma"));
   addIDITagValue (dstrParamsIDI, I_("screen"),I_("RESPDiploma") );
   onSystemMenuItem (TXT_LOAD_RESP_DIPLOMA,
      CMD_BPROC_RESP_DIPLOMA, false, dstrParamsIDI);
}

//*****************************************************************************
void CDSTCView::OnUpdateRESPDiplomaMenuItem(CCmdUI* pCmdUI)
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateRESPDiplomaMenuItem"));

   pCmdUI->Enable (enableSystemMenuItem (UAF::RESP_DIPLOMA));
}
//*****************************************************************************
void CDSTCView::OnSegMaintenanceSegAttributes ()
{
   MAKEFRAME2 (CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnSegMaintenanceSegAttributes"));

   DString dstrParamsIDI;

   addIDITagValue (dstrParamsIDI, I_("from_screen"), I_("MainScreen"));
   addIDITagValue (dstrParamsIDI, I_("BrowserTitle"), I_("SEG Attributes"));
   addIDITagValue (dstrParamsIDI, I_("screen"),I_("SEGAttributes") );
   onSystemMenuItem (TXT_LOAD_SEG_ATTRIBUTES,
      CMD_BPROC_SEG_ATTRIBUTES, false, dstrParamsIDI);
}

//*****************************************************************************
void CDSTCView::OnUpdateSegMaintenanceSegAttributes (CCmdUI* pCmdUI)
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateSegMaintenanceSegAttributes"));

   pCmdUI->Enable (enableSystemMenuItem (UAF::SEG_ATTRIBUTES));
}

//*****************************************************************************
void CDSTCView::OnForeignFinancialInstitutionMaintenance()
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnForeignFinancialInstitutionMaintenance"));

   DString dstrParamsIDI,strBrowserTitle;
   DString dstrMarket = DSTCommonFunctions::getMarket();
   CString cstrBrowserTitle;

   cstrBrowserTitle.LoadString(TXT_FIN_INST_REGLTRY_MAINT_TITLE);
   strBrowserTitle = cstrBrowserTitle;
   strBrowserTitle += I_(":");

   addIDITagValue (dstrParamsIDI, I_("from_screen"), I_("MainScreen"));
   addIDITagValue (dstrParamsIDI, I_("BrowserTitle"), strBrowserTitle);
   addIDITagValue (dstrParamsIDI, I_("screen"),I_("FinanInst") );
   addIDITagValue (dstrParamsIDI, I_("market"), dstrMarket );

   onSystemMenuItem (TXT_LOADING_FIN_INST_REGLTRY_MAINT,
      CMD_BPROC_FFI_MAINT, false, dstrParamsIDI);

}

//*****************************************************************************
void CDSTCView::OnUpdateForeignFinancialInstitutionMaintenance(CCmdUI* pCmdUI)
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateForeignFinancialInstitutionMaintenance"));

   pCmdUI->Enable (enableSystemMenuItem (UAF::FFI_MAINT));
}

//*****************************************************************************
void CDSTCView::OnTrailerFeesInquiry()
{
    MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnTrailerFeesInquiry"));

    DString dstrParamsIDI,strBrowserTitle;
    CString cstrBrowserTitle;

    cstrBrowserTitle.LoadString(TXT_TRAILER_FEES_INQUIRY_TITLE);
    strBrowserTitle = cstrBrowserTitle;
    strBrowserTitle += I_(":");

    addIDITagValue (dstrParamsIDI, I_("from_screen"), I_("MainScreen"));
    addIDITagValue (dstrParamsIDI, I_("BrowserTitle"), strBrowserTitle);
    addIDITagValue (dstrParamsIDI, I_("screen"),I_("TrailerFeeInquiry") );
    onSystemMenuItem(TXT_LOADING_TRAILER_FEES_INQUIRY, CMD_BPROC_TRAILER_FEES_INQUIRY, false, dstrParamsIDI);
}

//*****************************************************************************
void CDSTCView::OnUpdateTrailerFeesInquiry(CCmdUI* pCmdUI)
{
    MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateTrailerFeesInquiry"));

    pCmdUI->Enable(enableSystemMenuItem(UAF::TRAILER_FEES_INQUIRY));
}

//*****************************************************************************
void CDSTCView::OnAccountGroup()
{
    MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnAccountGroup"));

    DString dstrParamsIDI, strBrowserTitle;
    CString cstrBrowserTitle;

    cstrBrowserTitle.LoadString(TXT_ACCOUNT_GROUP_TITLE);
    strBrowserTitle = cstrBrowserTitle;
    strBrowserTitle += I_(":");

    addIDITagValue (dstrParamsIDI, I_("from_screen"), I_("MainScreen"));
    addIDITagValue (dstrParamsIDI, I_("BrowserTitle"), strBrowserTitle);
    addIDITagValue (dstrParamsIDI, I_("screen"),I_("AccountGroup") );
    onSystemMenuItem(TXT_LOADING_ACCOUNT_GROUP, CMD_BPROC_ACCOUNT_GROUP, false, dstrParamsIDI);
}


//*****************************************************************************
void CDSTCView::OnUpdateAccountGroup(CCmdUI* pCmdUI)
{
    MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateAccountGroup"));

    pCmdUI->Enable(enableSystemMenuItem(UAF::ACCOUNT_GROUPING));
}

//*****************************************************************************
void CDSTCView::OnAccountHouseholdInfo()
{
    MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnAccountHouseholdInfo"));

    DString dstrParamsIDI, strBrowserTitle;
    CString cstrBrowserTitle;

    cstrBrowserTitle.LoadString(TXT_ACCOUNT_GROUPING_INFO_TITLE);
    strBrowserTitle = cstrBrowserTitle;
    strBrowserTitle += I_(":");

    addIDITagValue (dstrParamsIDI, I_("from_screen"), I_("MainScreen"));
    addIDITagValue (dstrParamsIDI, I_("BrowserTitle"), strBrowserTitle);
    addIDITagValue (dstrParamsIDI, I_("screen"),I_("GroupingInformation") );
    onSystemMenuItem(TXT_LOADING_ACCOUNT_GROUP, CMD_BPROC_ACCOUNT_GROUPING_INFO, false, dstrParamsIDI);
}

//*****************************************************************************
void CDSTCView::OnUpdateAccountHouseholdInfo(CCmdUI* pCmdUI)
{
    MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateAccountHouseholdInfo"));

    pCmdUI->Enable(enableSystemMenuItem(UAF::ACCOUNT_GROUPING_INFO));
}

//*****************************************************************************
void CDSTCView::OnFundRulesMaintenance()
{
    MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnFundRulesMaintenance"));

    DString dstrParamsIDI, strBrowserTitle;
    CString cstrBrowserTitle;

    cstrBrowserTitle.LoadString(TXT_FUND_RULES_MAINTENANCE_TITLE);
    strBrowserTitle = cstrBrowserTitle;
    strBrowserTitle += I_(":");

    addIDITagValue (dstrParamsIDI, I_("from_screen"), I_("MainScreen"));
    addIDITagValue (dstrParamsIDI, I_("BrowserTitle"), strBrowserTitle);
    addIDITagValue (dstrParamsIDI, I_("screen"),I_("FundRules") );
    onSystemMenuItem(TXT_LOADING_FUND_RULES_MAINTENANCE, CMD_BPROC_FUND_RULES_MAINTENANCE, false, dstrParamsIDI);
}

//*****************************************************************************
void CDSTCView::OnUpdateFundRulesMaintenance(CCmdUI* pCmdUI)
{
    MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateFundRulesMaintenance"));

    pCmdUI->Enable(enableSystemMenuItem(UAF::FUND_RULES_MAINTENANCE));
}

//*****************************************************************************
void CDSTCView::OnTransferAccounts()
{
    MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnTransferAccounts"));

    DString dstrParamsIDI;
    CString cstrBrowserTitle;

    cstrBrowserTitle.LoadString(TXT_TRANSFER_OF_ACCOUNTS_TITLE);

    addIDITagValue(dstrParamsIDI, I_("from_screen"), I_("MainScreen"));
    addIDITagValue(dstrParamsIDI, I_("BrowserTitle"), cstrBrowserTitle);
    addIDITagValue(dstrParamsIDI, I_("screen"),I_("TransferAccounts") );

    onSystemMenuItem(TXT_LOADING_TRANSFER_OF_ACCOUNTS, CMD_BPROC_TRANSFER_OF_ACCOUNTS, false, dstrParamsIDI);
}


//*****************************************************************************
void CDSTCView::OnUpdateTransferAccounts(CCmdUI* pCmdUI)
{
    MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateTransferAccounts"));

    pCmdUI->Enable(enableSystemMenuItem(UAF::TRANSFER_OF_ACCOUNTS));
}

//*****************************************************************************
void CDSTCView::OnPrivateWealthInformation()
{
    MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnPrivateWealthInformation"));

    DString dstrParamsIDI, strBrowserTitle;
    CString cstrBrowserTitle;

    cstrBrowserTitle.LoadString(TXT_PRIVATE_WEALTH_INFO_TITLE);
    strBrowserTitle = cstrBrowserTitle;
    strBrowserTitle += I_(":");

    addIDITagValue (dstrParamsIDI, I_("from_screen"), I_("MainScreen"));
    addIDITagValue (dstrParamsIDI, I_("BrowserTitle"), strBrowserTitle);
    addIDITagValue (dstrParamsIDI, I_("screen"),I_("PWInfo") );
    onSystemMenuItem(TXT_LOADING_PRIVATE_WEALTH_INFO, CMD_BPROC_PRIVATE_WEALTH_INFO, false, dstrParamsIDI);
}

//*****************************************************************************
void CDSTCView::OnUpdatePrivateWealthInformation(CCmdUI* pCmdUI)
{
    MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateAccountGroup"));

    pCmdUI->Enable(enableSystemMenuItem(UAF::PRIVATE_WEALTH_INFO));
}

//*****************************************************************************
void CDSTCView::OnFATCAFilingDetail()
{
    MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnFATCAFilingDetail"));

    DString dstrParamsIDI, strBrowserTitle;
    CString cstrBrowserTitle;

    cstrBrowserTitle.LoadString(TXT_FATCA_FILING_DETAIL_TITLE);
    strBrowserTitle = cstrBrowserTitle;
    strBrowserTitle += I_(":");

    addIDITagValue (dstrParamsIDI, I_("from_screen"), I_("MainScreen"));
    addIDITagValue (dstrParamsIDI, I_("BrowserTitle"), strBrowserTitle);
    addIDITagValue (dstrParamsIDI, I_("screen"),I_("FATCAFilingDetl") );
    onSystemMenuItem(TXT_LOADING_FATCA_FILING_DETAIL, CMD_BPROC_FATCA_FILING_DETAIL, false, dstrParamsIDI);
}

//*****************************************************************************
void CDSTCView::OnUpdateFATCAFilingDetail(CCmdUI* pCmdUI)
{
    MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateAccountGroup"));

    pCmdUI->Enable(enableSystemMenuItem(UAF::FATCA_FILING_DETAIL));
}

//*****************************************************************************
void CDSTCView::OnSystemIdentificationMaintenance()
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnSystemIdentificationMaintenance"));

   DString dstrParamsIDI,strBrowserTitle;
   CString cstrBrowserTitle;

   cstrBrowserTitle.LoadString(TXT_FIN_INST_IDENT_MAINT_TITLE);
   strBrowserTitle = cstrBrowserTitle;
   strBrowserTitle += I_(":");

   addIDITagValue (dstrParamsIDI, I_("from_screen"), I_("MainScreen"));
   addIDITagValue (dstrParamsIDI, I_("BrowserTitle"), strBrowserTitle);
   addIDITagValue (dstrParamsIDI, I_("screen"),I_("FinInstIden") );
   onSystemMenuItem (TXT_LOADING_FIN_INST_IDENT_MAINT,
      CMD_BPROC_IDENTIFICATION_MAINT, false, dstrParamsIDI);

}

//*****************************************************************************
void CDSTCView::OnUpdateSystemIdentificationMaintenance(CCmdUI* pCmdUI)
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateSystemIdentificationMaintenance"));

   pCmdUI->Enable (enableSystemMenuItem (UAF::FUND_IDENT_MAINT) || 
                   enableSystemMenuItem (UAF::BROKER_IDENT_MAINT));
}

//*****************************************************************************
void CDSTCView::OnFundGroup()
{
	MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnFundGroup"));

	DString dstrParamsIDI;

	CString cstrBrowserTitle;
	cstrBrowserTitle.LoadString(TXT_FUND_GROUP_TXT);

	addIDITagValue (dstrParamsIDI, I_("from_screen"), I_("MainScreen"));
	addIDITagValue (dstrParamsIDI, I_("BrowserTitle"), cstrBrowserTitle);
	addIDITagValue (dstrParamsIDI, I_("screen"), I_("FundGroup"));

	onSystemMenuItem(TXT_FUND_GROUP, CMD_BPROC_FUND_GROUP, false, dstrParamsIDI);
}

//*****************************************************************************
void CDSTCView::OnUpdateFundGroup (CCmdUI* pCmdUI)
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateFundGroup"));

   pCmdUI->Enable( enableSystemMenuItem(UAF::FUND_GROUP) );
}

//*****************************************************************************
void CDSTCView::OnFundBrokerLinkage()
{
	MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnFundBrokerLinkage"));

	DString dstrParamsIDI;

	CString cstrBrowserTitle;
	cstrBrowserTitle.LoadString(TXT_FUND_BROKER_LINKAGE);

	addIDITagValue (dstrParamsIDI, I_("from_screen"), I_("MainScreen"));
	addIDITagValue (dstrParamsIDI, I_("BrowserTitle"), cstrBrowserTitle);
	addIDITagValue (dstrParamsIDI, I_("screen"), I_("FundBrokerLinkage"));

	onSystemMenuItem(TXT_FUND_BROKER_LINKAGE, CMD_BPROC_FUND_BROKER_LINKAGE, false, dstrParamsIDI);
}

//*****************************************************************************
void CDSTCView::OnUpdateFundBrokerLinkage (CCmdUI* pCmdUI)
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateFundBrokerLinkage"));

   pCmdUI->Enable( enableSystemMenuItem(UAF::FUND_BROKER_LINKAGE) );
}

//*****************************************************************************
//bModal = false, means modeless
//*****************************************************************************
void CDSTCView::onSystemMenuItem ( UINT uiMsgId,
                                   const I_CHAR* processId,
                                   bool bModal /*=false*/,
                                   const DString& dstrParamsIDI /*=NULL_STRING*/)
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_( "onSystemMenuItem" ));

   CWaitCursor cursor;
   E_COMMANDRETURN eRtn = CMD_CANCEL;

   m_statusBar.SetMessageStatusBar(uiMsgId);
   startCall();
   destroyBusInfo();
   if (dstrParamsIDI != NULL_STRING)
   {
      m_rpGIWorkSession->setParameter (I_("UrlParams"), dstrParamsIDI);
      I_CHAR *temp = const_cast< I_CHAR* >(dstrParamsIDI.c_str());

      do
      {
         DString paramName,
            paramValue;

         temp = parseIdiString (temp, paramName, paramValue);
         m_rpGIWorkSession->setParameter (paramName, paramValue);
      }
      while (temp && temp != NULL_STRING && *temp);
   }
   eRtn = CommandDispatcher::getInstance()->invokeCommand( m_rpGIWorkSession,
                                                           processId,
                                                           PROC_NO_TYPE,
                                                           bModal,
                                                           NULL);
   if (eRtn != CMD_OK && eRtn != CMD_MODELESS_INPROCESS && eRtn != CMD_CANCEL)
   {
      ConditionMessageBox(FRAMEBELOW(), GETHIGHESTSEVERITY());
   }
   m_statusBar.SetMessageStatusBar(NULL_STRING);
   //kill the worksession, only if the process is modal
   if (bModal)
   {
      OnBtnEndCall();
      //AfxGetMainWnd()->PostMessage( WM_COMMAND, IDC_BTN_END );
   }
}


//this method checks only for read permisions;
//enhancements to this method should be made so
//other types of permissions can be checked, too
//******************************************************************************
bool CDSTCView::enableSystemMenuItem(I_CHAR * const dstrUaf)
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("enableSystemMenuItem"));
   bool enable = !m_rpGIWorkSession;//disable the menu handler while there is work

   if( m_rpGIWorkSession )
   {
      int childrecnt = m_rpGIWorkSession->getGIContainer()->getChildCount( m_rpGIWorkSession );
      if( childrecnt == 0 ) { enable = true;    }
   }

   if (enable)
   {
      DSTCUserSession *dstcUserSession =
         dynamic_cast<DSTCUserSession *>(m_rpGIUserSession->getBFSession());
      DString dstrMgmtCoId;

      m_rpGIUserSession->getField(NULL, SYSTMGMTS, dstrMgmtCoId);
      enable = dstcUserSession->hasReadPermission(dstrMgmtCoId, dstrUaf);
   }
   return enable;

}


//******************************************************************************
bool CDSTCView::clearWorksession(bool bDiscard, bool bSkipAWD, bool SearchBTN )
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("clearWorksession"));

   GenericInterface *_pGIWorkSession = NULL;

   bool havews = false;

   if(! m_rpGIUserSession) return true;
   int childrecnt = m_rpGIUserSession->getGIContainer()->getChildCount( m_rpGIUserSession );
   int i = 0;

   while( i< childrecnt )
   {
     _pGIWorkSession = m_rpGIUserSession->getGIContainer()->getChild(m_rpGIUserSession, i);
     if( !_pGIWorkSession || _pGIWorkSession->getCommandName() != CMD_BPROC_WORK_SESSION )
     {
        i++;
        continue;
     }

      if( !bDiscard )
      {
         DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(_pGIWorkSession->getBFWorkSession());
         dstWorkSession->cleanupWorkSession();
         _pGIWorkSession->getGIContainer()->destroyChildren( _pGIWorkSession );
       i++;
      }
     else
     {
         _pGIWorkSession->ok( NULL );
       if( !SearchBTN )
       {
          m_rpGIUserSession->getGIContainer()->destroy( _pGIWorkSession );
          if( m_rpGIWorkSession == _pGIWorkSession )   m_rpGIWorkSession = NULL;
          _pGIWorkSession = NULL;
          childrecnt = m_rpGIUserSession->getGIContainer()->getChildCount( m_rpGIUserSession );
       }else {
          i++;
       }
     }
     havews = true;
   }

   return havews;

}

//*****************************************************************************
LRESULT CDSTCView::OnEndCurrSession( WPARAM wType, LPARAM lParam )
{
   TRACE_METHOD( CLASSNAME, I_("OnEndCurrSession") );

   if(!m_currpGIWorkSession || !isWorkSessionValid(m_currpGIWorkSession) ) return(0);

   CWaitCursor cursor;

   if (m_workEvent) {
      m_workEvent->replyDone();
      m_workEvent.reset();
   }

   //this function is called by confirmation, do not need check discard flag.
   m_currpGIWorkSession->ok( NULL );
   m_rpGIUserSession->getGIContainer()->destroy( m_currpGIWorkSession );
   if( m_rpGIWorkSession == m_currpGIWorkSession )  m_rpGIWorkSession = NULL;
   m_currpGIWorkSession = NULL;

   return (0);
}

//*****************************************************************************
bool CDSTCView::isWorkSessionValid(GenericInterface* pWS )
{
   TRACE_METHOD( CLASSNAME, I_("OnEndCurrSession") );

   GenericInterface *_pGIWorkSession = NULL;
   if(! m_rpGIUserSession) return false;
   int childrecnt = m_rpGIUserSession->getGIContainer()->getChildCount( m_rpGIUserSession );

   for ( int i=0; i< childrecnt; i++ )
   {
     _pGIWorkSession = m_rpGIUserSession->getGIContainer()->getChild(m_rpGIUserSession, i);
     if( _pGIWorkSession && _pGIWorkSession->getCommandName() == CMD_BPROC_WORK_SESSION )
     {
        if (_pGIWorkSession == pWS ) return true;
     }
   }
   return (0);
}



//******************************************************************************

bool CDSTCView::displayActiveBatches()
{
   bool blRetVal = false;
   if (m_rpGIUserSession)
   {
      CWaitCursor();
      CommandDispatcher::getInstance()->invokeCommand( m_rpGIUserSession,
                                                       CMD_BPROC_ACTIVE_BATCH, PROC_NO_TYPE, true, NULL);
      DString dstrActiveBatches;
     m_rpGIUserSession->getParameter ( I_("ActiveBatches"), dstrActiveBatches );
     if( !dstrActiveBatches.empty() )
     {
      //blRetVal = true;//Oct 17 - Serban asked for warning only
      // Display error
      CString strActBatches = dstrActiveBatches.c_str();
      CString cstrBatch;
      cstrBatch.LoadString(TXT_CLOSE_ACTIVE_BATCH);
      AfxMessageBox( cstrBatch+strActBatches, MB_ICONWARNING );
     }
   }
   return blRetVal;
}

//*****************************************************************************
void CDSTCView::OnReleaseFrozenAccount()
{
    MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnReleaseFrozenAccount"));

    DString dstrParamsIDI;

    addIDITagValue (dstrParamsIDI, I_("option"), I_("brokerBranchRep") );
    addIDITagValue (dstrParamsIDI, I_("BrowserTitle"),I_("Release Frozen Account : ") );
    addIDITagValue (dstrParamsIDI, I_("screen"), I_("ReleaseFrozenAcct")); //DesktopWeb conversion

    onSystemMenuItem(TXT_RELEASE_FROZEN_ACCOUNT, CMD_BPROC_RELEASE_FROZEN_ACCOUNT, false, dstrParamsIDI);
}

//*****************************************************************************
void CDSTCView::OnUpdateReleaseFrozenAccount(CCmdUI* pCmdUI)
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateReleaseFrozenAccount"));

   pCmdUI->Enable( enableSystemMenuItem(UAF::RELEASE_FROZEN_ACCOUNT) );
}

//******************************************************************************
void CDSTCView::NotifyStatusBarOnRegistryChange(void)
{
   HWND hWnd = m_statusBar.m_hWnd;

   if ( m_rpGIUserSession )
   {
      m_notifyHeader.idFrom = IDC_LOG_DISPLAY_CONDITION_NAME;
      m_notifyHeader.hwndFrom = ((CWnd*)this)->m_hWnd;
      m_notifyHeader.code = UM_IFDSSTATUSBARCHANGE;

      // Make sure that status pane is refreshed properly
      ::SendMessage( hWnd, WM_NOTIFY,(WPARAM)IDC_LOG_DISPLAY_CONDITION_NAME ,(LPARAM)&m_notifyHeader );

      DString dstrUserID;
      DString dstrAWDProfile;
      DString dstrMgmtCoName;
      DString dstrClientName;
      DString dstrCompanyID;

      getRegistry();

      // Refresh pan all of pane text
      m_rpGIUserSession->getField( NULL, USERID, dstrUserID );
      m_rpGIUserSession->getField( NULL, AWDPROFILE, dstrAWDProfile );
      m_rpGIUserSession->getField( NULL, MGMTCONAME, dstrMgmtCoName );
      m_rpGIUserSession->getField( NULL, CLIENTNAME, dstrClientName );
      m_rpGIUserSession->getField( NULL, SYSTMGMTS, dstrCompanyID );

      DSTCUserSession* pUserSession = dynamic_cast<DSTCUserSession*>(m_rpGIUserSession->getBFSession());
      DString dstrCompanyCode = NULL_STRING;
      if( pUserSession != NULL )
      {
         DSTCGlobalSession& gs = dynamic_cast<DSTCGlobalSession&>(pUserSession->getGlobalSession());
         MgmtCo* pMgmtCo = NULL;
         MgmtCoOptions* pOptions = NULL;
         gs.findMgmtCo( dstrCompanyID, pMgmtCo );

         if(pMgmtCo && pMgmtCo->getMgmtCoOptions(pOptions) <= WARNING && 
            pOptions){
               pOptions->getField( ifds::CompanyCode, dstrCompanyCode, BF::HOST, false );
         }
         dstrCompanyCode.stripAll ().upperCase ();
      }

      m_statusBar.SetProfileStatusBar( dstrAWDProfile.c_str() );
      m_statusBar.SetManagementCodeStatusBar( dstrMgmtCoName.c_str() );
      m_statusBar.SetSystemStatusBar( dstrUserID.c_str() );
      m_statusBar.SetCompanyCodeStatusBar( dstrCompanyCode.c_str() );
      m_statusBar.SetClientNameStatusBar( dstrClientName.c_str() );
   }
}

//*****************************************************************************

void CDSTCView::onSmartForms (const DString &dstrCRDA)
{
   MAKEFRAME2 ( CND::IFASTGUI_CONDITION, CLASSNAME, ONBTNFINANCIAL );

    DString urlParamsIDI;
    E_COMMANDRETURN eRtn = CMD_OK;

   addIDITagValue (urlParamsIDI, I_("screen"),I_("Smart Form : ") );
    addIDITagValue (urlParamsIDI, I_("BrowserTitle"),I_("SmartForms : ") );
    addIDITagValue (urlParamsIDI, I_("crda"), dstrCRDA );

    m_rpGIWorkSession->setParameter (I_("UrlParams"), urlParamsIDI);

   eRtn = CommandDispatcher::getInstance()->invokeCommand (m_rpGIWorkSession, CMD_BPROC_SMART_FORM, PROC_NO_TYPE, true, NULL);
}
//******************************************************************************
void CDSTCView::OnSmartForms ()
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnTrailerFeeSetup()"));

    DString dstrParamsIDI;
   DString dstrAccountNum = NULL;

   m_bManualSmartForm = true;
    addIDITagValue (dstrParamsIDI, I_("BrowserTitle"),I_("SmartForms : ") );
    addIDITagValue (dstrParamsIDI, I_("screen"),I_("SmartForms") );

    onSystemMenuItem(TXT_INTERFACE_FILE, CMD_BPROC_SMART_FORM, false, dstrParamsIDI);

    GetDlgItem(IDC_EDT_SEARCH3)->SetWindowText( dstrAccountNum.c_str () );
}

//******************************************************************************
void CDSTCView::OnUpdateSmartForms (CCmdUI* pCmdUI)
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateTrailerFeeSetup") );

   DSTCUserSession *dstcUserSession = dynamic_cast<DSTCUserSession *>(m_rpGIUserSession->getBFSession());
   DString dstrMgmtCoId;

   m_rpGIUserSession->getField( NULL, SYSTMGMTS, dstrMgmtCoId );
   bool bHasReadPermission = dstcUserSession->hasReadPermission( dstrMgmtCoId, UAF::SMART_FORM ) &&
                             dstcUserSession->hasCreatePermission( dstrMgmtCoId, UAF::SEARCH_FOR_ACCOUNT_OR_ENTITY );
   pCmdUI->Enable (bHasReadPermission);
}

//*****************************************************************************
void  CDSTCView::OpenKYC (const DString &accountNum,
                    const DString &dstrBusArea,
                    const DString &dstrSmartForm )
{
   MAKEFRAME2 ( CND::IFASTGUI_CONDITION, CLASSNAME, ONBTNFINANCIAL );

   CWaitCursor    cursor;
    E_COMMANDRETURN eRtn = CMD_OK;
    DString       lastAccountNum = accountNum;

    startCall();

    if (m_rpGIWorkSession)
    {
        lastAccountNum.strip();
        lastAccountNum.stripLeading ('0');

      m_rpGIWorkSession->setParameter (MFCAN_IP_PARAM::ACCOUNT_NUM, lastAccountNum);

      if (DSTCommonFunctions::codeInList (dstrBusArea, MFS) && dstrSmartForm == I_("Y"))
      {
         eRtn =CommandDispatcher::getInstance()->invokeCommand (m_rpGIWorkSession, CMD_BPROC_DEMOGRAPHICS,
                                                                  PROC_NO_TYPE, false, NULL);
      }

      switch (eRtn)
      {
         case CMD_OK:
         case CMD_CANCEL:
         case CMD_MODELESS_INPROCESS:
            break;

         default:
            // Display error
            ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
            break;
      }
   }
}

//******************************************************************************
void CDSTCView::OnLanguageEnglish()
{
   DString dstrClientId;
   DSTCWorkSession *dstWorkSession = NULL;
   DSTCUserSession *dstUserSession = NULL;
   MgmtCo *mgmtCo = NULL;

   if( m_rpGIWorkSession != NULL )
   {
      dstWorkSession = dynamic_cast<DSTCWorkSession *>(m_rpGIWorkSession->getBFWorkSession());
      if( dstWorkSession != NULL )
      {
         dstWorkSession->getMgmtCo().getField( ifds::ClientID, dstrClientId, BF::HOST);
      }
   }

   if(!OnBtnEndCall1())
   {
      return;
   }

   m_rpGIFiller->getParent()->getGIContainer()->destroy( m_rpGIFiller );
   m_rpGIFiller = NULL;
      
   ClientLocale clientLocale(ClientLocaleContext::get());
   clientLocale.setLocale(I_("enUS"));
   
   ClientLocaleContext::set(clientLocale);


   if( m_rpGIUserSession != NULL )
   {
      DSTCUserSession *dstcUserSession = dynamic_cast<DSTCUserSession *>(m_rpGIUserSession->getBFSession());
      dstcUserSession->setClientLocale(clientLocale);
   }

   fillAllCheckingSecurity();
   DString dstrMarket = clientLocale.getMarket();
   ((MFDSTCApp*)AfxGetApp())->LoadResourceDllByLanguageAndMarket( dstrClientId, dstrMarket, I_("ENG") );

   ((CMainFrame*)AfxGetMainWnd())->ChangeMenu();
   ((CMainFrame*)AfxGetMainWnd())->setAwdActive( m_bAWD );
   ((CMainFrame*)AfxGetMainWnd())->setMgmCo( dynamic_cast<DSTCUserSession *>(m_rpGIUserSession->getBFSession()) );

   UpdateLabels();

   // Session
   DString dstrTitle;
   CString cstrTitle;
   cstrTitle.LoadString( AFX_IDS_APP_TITLE );
   CWnd  *pGUI = CWnd::FindWindow( NULL, cstrTitle );
   if( pGUI != NULL )
   {
      dstrTitle = DString( cstrTitle ) + I_(" - ");
      dstrTitle.appendInt( m_ucSession );
      pGUI->SetWindowText( CString(dstrTitle.c_str()) );
   }
}

//******************************************************************************
void CDSTCView::OnLanguageFrench()
{
   DString dstrClientId;
   DSTCWorkSession *dstWorkSession = NULL;
   DSTCUserSession *dstUserSession = NULL;
   MgmtCo *mgmtCo = NULL;

   if( m_rpGIWorkSession != NULL )
   {
      dstWorkSession = dynamic_cast<DSTCWorkSession *>(m_rpGIWorkSession->getBFWorkSession());
      if( dstWorkSession != NULL )
      {
         dstWorkSession->getMgmtCo().getField( ifds::ClientID, dstrClientId, BF::HOST);
      }
   }

   if(!OnBtnEndCall1())
   {
      return;
   }

   m_rpGIFiller->getParent()->getGIContainer()->destroy( m_rpGIFiller );
   m_rpGIFiller = NULL;
      
   ClientLocale clientLocale(ClientLocaleContext::get());
   clientLocale.setLocale(I_("frCA"));
   ClientLocaleContext::set(clientLocale);

   if( m_rpGIUserSession != NULL )
   {
      DSTCUserSession *dstcUserSession = dynamic_cast<DSTCUserSession *>(m_rpGIUserSession->getBFSession());
      dstcUserSession->setClientLocale(clientLocale);
   }

   fillAllCheckingSecurity();
   DString dstrMarket = clientLocale.getMarket();

   ((MFDSTCApp*)AfxGetApp())->LoadResourceDllByLanguageAndMarket( dstrClientId, dstrMarket, I_("FR") );
   ((CMainFrame*)AfxGetMainWnd())->ChangeMenu();
   ((CMainFrame*)AfxGetMainWnd())->setAwdActive( m_bAWD );
   ((CMainFrame*)AfxGetMainWnd())->setMgmCo( dynamic_cast<DSTCUserSession *>(m_rpGIUserSession->getBFSession()) );

   UpdateLabels();

   // Session
   DString dstrTitle;
   CString cstrTitle;
   cstrTitle.LoadString( AFX_IDS_APP_TITLE );
   CWnd  *pGUI = CWnd::FindWindow( NULL, cstrTitle );
   if( pGUI != NULL )
   {
      dstrTitle = DString( cstrTitle ) + I_(" - ");
      dstrTitle.appendInt( m_ucSession );
      pGUI->SetWindowText( CString(dstrTitle.c_str()) );
   }
}

//******************************************************************************
void CDSTCView::OnUpdateLanguageEnglish(CCmdUI *pCmdUI)
{
   // TODO: Add your command update UI handler code here
   DString strCurDLLLanguage = ( (MFDSTCApp*)( AfxGetApp() ) )->getLanguage();
   DString strMarket = DSTCommonFunctions::getMarket();

   DSTCUserSession *dstcUserSession = dynamic_cast<DSTCUserSession *>(m_rpGIUserSession->getBFSession());
   
   DString dstrMgmtCoId;
   m_rpGIUserSession->getField(NULL, SYSTMGMTS, dstrMgmtCoId);
   
   bool bAllowLangToggle = dstcUserSession->hasReadPermission(dstrMgmtCoId, UAF::LANGUAGE_TOGGLE);

// Temporarily use only market and value to drive the menu (until the slot has the lang toggle data fix in
   pCmdUI->Enable (bAllowLangToggle && (strCurDLLLanguage != I_("ENG")) && (strMarket == MARKET_IDS::CANADA));
//   pCmdUI->Enable ((strCurDLLLanguage != I_("ENG")) && (strMarket == MARKET_IDS::CANADA));
}

//******************************************************************************
void CDSTCView::OnUpdateLanguageFrench(CCmdUI *pCmdUI)
{
   // TODO: Add your command update UI handler code here
   DString strCurDLLLanguage = ( (MFDSTCApp*)( AfxGetApp() ) )->getLanguage();
   DString strMarket = DSTCommonFunctions::getMarket();


   DSTCUserSession *dstcUserSession = dynamic_cast<DSTCUserSession *>(m_rpGIUserSession->getBFSession());
   
   DString dstrMgmtCoId;
   m_rpGIUserSession->getField(NULL, SYSTMGMTS, dstrMgmtCoId);
   
   bool bAllowLangToggle = dstcUserSession->hasReadPermission(dstrMgmtCoId, UAF::LANGUAGE_TOGGLE);

// Temporarily use only market and value to drive the menu (until the slot has the lang toggle data fix in
//   pCmdUI->Enable ((strCurDLLLanguage != I_("FR")) && (strMarket == MARKET_IDS::CANADA));
   pCmdUI->Enable (bAllowLangToggle && (strCurDLLLanguage != I_("FR")) && (strMarket == MARKET_IDS::CANADA));
}

//*****************************************************************************
void CDSTCView::OnEventDateGen()
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnEventDateGen"));

   DString dstrParamsIDI;

   addIDITagValue (dstrParamsIDI, I_("BrowserTitle"), I_("Event/Trade Date Generation"));
   addIDITagValue (dstrParamsIDI, I_("screen"), I_("ClassSetup_EventGen"));

   onSystemMenuItem(TXT_EVENT_DATE_GEN, CMD_BPROC_EVENT_DATE_GEN, false, dstrParamsIDI);
}

//*****************************************************************************
void CDSTCView::OnUpdateEventDateGen (CCmdUI* pCmdUI)
{
   MAKEFRAME2 (CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateEventDateGen"));

   pCmdUI->Enable (enableSystemMenuItem(UAF::EVENT_DATE_GEN) );
}

//*****************************************************************************
void CDSTCView::OnRemitUnclmAcct()
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnRemitUnclmAcct"));

   DString dstrParamsIDI;
   CString cstrBrowserTitle;
   cstrBrowserTitle.LoadString(TXT_REMIT_UNCLM_ACCT);

   addIDITagValue (dstrParamsIDI, I_("BrowserTitle"), cstrBrowserTitle);
   addIDITagValue (dstrParamsIDI, I_("screen"), I_("RemitUnclmAcct"));

   onSystemMenuItem(TXT_REMIT_UNCLM_ACCT, CMD_BPROC_REMIT_UNCLM_ACCT, false, dstrParamsIDI);
}

//*****************************************************************************
void CDSTCView::OnUpdateRemitUnclmAcct (CCmdUI* pCmdUI)
{
   MAKEFRAME2 (CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateRemitUnclmAcct"));

   pCmdUI->Enable (enableSystemMenuItem(UAF::REMIT_UNCLM_ACCT) );
}

//*****************************************************************************
void CDSTCView::OnEventSchduleMain()
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnEventSchduleMain"));

   DString dstrParamsIDI;

   addIDITagValue (dstrParamsIDI, I_("BrowserTitle"), I_("Event Schedule Maintenance"));
   addIDITagValue (dstrParamsIDI, I_("screen"), I_("ClassSetup_EvenMain"));

   onSystemMenuItem(TXT_EVENT_SCH_MAIN, CMD_BPROC_EVENT_SCH_MAIN, false, dstrParamsIDI);
}

//*****************************************************************************
void CDSTCView::OnUpdateEventSchduleMain (CCmdUI* pCmdUI)
{
   MAKEFRAME2 (CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateEventSchduleMain"));

   pCmdUI->Enable (enableSystemMenuItem(UAF::EVENT_SCH_MAIN) );
}

//*****************************************************************************
void CDSTCView::OnTradeSchduleMain()
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnTradeSchduleMain"));

   DString dstrParamsIDI;

   addIDITagValue (dstrParamsIDI, I_("BrowserTitle"), I_("Trade Date Schedule"));
   addIDITagValue (dstrParamsIDI, I_("screen"), I_("TradeDateMain"));

   onSystemMenuItem(TXT_TRADE_SCH_MAIN, CMD_BPROC_TRADE_SCH_MAIN, false, dstrParamsIDI);
}

//*****************************************************************************
void CDSTCView::OnUpdateTradeSchduleMain (CCmdUI* pCmdUI)
{
   MAKEFRAME2 (CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateTradeSchduleMain"));

   pCmdUI->Enable (enableSystemMenuItem(UAF::TRADE_SCH_MAIN) );
}

//******************************************************************************
void CDSTCView::OnAccountForeignTaxReview()
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnAccountForeignTaxReview"));

   DString dstrParamsIDI;

   CString cstrBrowserTitle;
   cstrBrowserTitle.LoadString(TXT_ACCT_FOREIGN_REVIEW_TITLE);

   addIDITagValue (dstrParamsIDI, I_("from_screen"), I_("MainScreen"));
   addIDITagValue (dstrParamsIDI, I_("BrowserTitle"), DString(cstrBrowserTitle));
   addIDITagValue (dstrParamsIDI, I_("screen"), I_("AcctGovFile"));

   onSystemMenuItem(TXT_ACCT_FOREIGN_REVIEW, CMD_BPROC_FOREIGN_TAX_REVIEW, false, dstrParamsIDI);

}

//******************************************************************************
void CDSTCView::OnUpdateAccountForeignTaxReview(CCmdUI* pCmdUI)
{
   MAKEFRAME2 (CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateAccountForeignTaxReview"));
   
//   DString dstrFATCAApplicable;
//   if( m_rpGIWorkSession != NULL )
//   {   
//      DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(m_rpGIWorkSession->getBFWorkSession());
//      dstWorkSession->getOption( ifds::FATCAApplicable, dstrFATCAApplicable, BF::HOST, false );
//      dstrFATCAApplicable.strip().upperCase();
//   }

//   pCmdUI->Enable (dstrFATCAApplicable == I_("Y"));
   pCmdUI->Enable (true);
}

//******************************************************************************
void CDSTCView::OnAccountFeeModelAssociation()
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnAccountForeignTaxReview"));

   DString dstrParamsIDI;

   CString cstrBrowserTitle;
   cstrBrowserTitle.LoadString(TXT_FEE_MODEL_ASSOCIATION_TITLE);

   addIDITagValue (dstrParamsIDI, I_("from_screen"), I_("MainScreen"));
   addIDITagValue (dstrParamsIDI, I_("BrowserTitle"), DString(cstrBrowserTitle));
   addIDITagValue (dstrParamsIDI, I_("screen"), I_("AcctAssociate"));

   onSystemMenuItem(TXT_FEE_MODEL_ASSOCIATION, CMD_BPROC_ACCT_FEE_MODEL_ASSOCIATION, false, dstrParamsIDI);
}

//******************************************************************************
void CDSTCView::OnUpdateAccountFeeModelAssociation(CCmdUI* pCmdUI)
{
   DSTCUserSession *dstcUserSession = dynamic_cast<DSTCUserSession *>(m_rpGIUserSession->getBFSession());
   DString dstrMgmtCoId;

   m_rpGIUserSession->getField( NULL, SYSTMGMTS, dstrMgmtCoId );
   bool bHasReadPermission = dstcUserSession->hasReadPermission( dstrMgmtCoId, UAF::ACCT_FEE_MODEL_ASSOCIATION );
   pCmdUI->Enable (bHasReadPermission);   
}


//******************************************************************************
void CDSTCView::OnFundGroupRegulatory()
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnFundGroupRegulatory"));

   DString dstrParamsIDI;
   DString dstrMarket = DSTCommonFunctions::getMarket();

   CString cstrBrowserTitle;
   cstrBrowserTitle.LoadString(TXT_FUNDGROUP_REGULATORY);

   addIDITagValue (dstrParamsIDI, I_("from_screen"), I_("MainScreen"));
   addIDITagValue (dstrParamsIDI, I_("BrowserTitle"), DString(cstrBrowserTitle));
   addIDITagValue (dstrParamsIDI, I_("screen"), I_("FinanInst"));
   addIDITagValue (dstrParamsIDI, I_("From_Menu"), I_("Fund"));
   addIDITagValue (dstrParamsIDI, I_("market"), dstrMarket);

   onSystemMenuItem(TXT_FUNDGROUP_REGULATORY, CMD_BPROC_FUNDGROUP_REGULATORY, false, dstrParamsIDI);
}

//******************************************************************************
void CDSTCView::OnUpdateFundGroupRegulatory(CCmdUI* pCmdUI)
{
   DSTCUserSession *dstcUserSession = dynamic_cast<DSTCUserSession *>(m_rpGIUserSession->getBFSession());
   DString dstrMgmtCoId;

   m_rpGIUserSession->getField( NULL, SYSTMGMTS, dstrMgmtCoId );
   bool bHasReadPermission = dstcUserSession->hasReadPermission( dstrMgmtCoId, UAF::FUNDGROUP_REGULATORY );
   pCmdUI->Enable (bHasReadPermission);   
}

//******************************************************************************
void CDSTCView::OnTradeVerification()
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnTradeVerification()"));
   
   CWaitCursor wait;
   onSystemMenuItem( TXT_TRADE_VERIFICATION,
                     CMD_BPROC_TRADE_VERIFICATION_SEARCH, 
                     false,
                     I_( "" ) );
}
//******************************************************************************
void CDSTCView::OnUpdateTradeVerification(CCmdUI* pCmdUI)
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateTradeVerification") );
   
   DSTCUserSession *dstcUserSession = dynamic_cast<DSTCUserSession *>(m_rpGIUserSession->getBFSession());
   DString dstrMgmtCoId;
   m_rpGIUserSession->getField( NULL, SYSTMGMTS, dstrMgmtCoId );
   pCmdUI->Enable(dstcUserSession->hasUpdatePermission( dstrMgmtCoId, UAF::TRADE_VERIFICATION ));
}
//******************************************************************************
void CDSTCView::OnRegulatoryAgreement()
{
	MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnRegulatoryAgreement()"));

	DString dstrParamsIDI;

	CString cstrBrowserTitle;
	cstrBrowserTitle.LoadString(TXT_REGULATORY_AGREEMENT);

	addIDITagValue(dstrParamsIDI, I_("from_screen"), I_("MainScreen"));
	addIDITagValue(dstrParamsIDI, I_("BrowserTitle"), cstrBrowserTitle);
	addIDITagValue(dstrParamsIDI, I_("screen"), I_("RegAgreement"));

	onSystemMenuItem(TXT_REGULATORY_AGREEMENT,
                     CMD_BPROC_REGULATORY_AGREEMENT, 
                     false,
					 dstrParamsIDI);
}
//******************************************************************************
void CDSTCView::OnUpdateRegulatoryAgreement(CCmdUI* pCmdUI)
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateRegulatoryAgreement"));
   
   pCmdUI->Enable(enableSystemMenuItem(UAF::REGULATORY_AGREEMENT));
}
//******************************************************************************
void CDSTCView::OnBrokerCutOff()
{
	MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnBrokerCutOff"));
	
	m_rpGIWorkSession->setParameter(I_("BrokerLevel"), YES);
	onSystemMenuItem(TXT_BROKER_CUTOFF_TIME,
      CMD_BPROC_ACCT_LVL_CUT_OFF_TIMES, false);
}
//******************************************************************************
void CDSTCView::OnUpdateBrokerCutOff(CCmdUI* pCmdUI)
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateBrokerCutOff") );

   pCmdUI->Enable(enableSystemMenuItem(UAF::BROKER_CUT_OFF));
}
//******************************************************************************
void CDSTCView::OnExternalTAFundLinkage()
{
	MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnExternalTAFundLinkage") );

	DString dstrParamsIDI;
	CString cstrBrowserTitle;
	cstrBrowserTitle.LoadString(TXT_EXTERNALTA_FUND_LINKAGE_TITLE);

	addIDITagValue (dstrParamsIDI, I_("from_screen"), I_("MainScreen"));
	addIDITagValue (dstrParamsIDI, I_("BrowserTitle"), cstrBrowserTitle);
	addIDITagValue (dstrParamsIDI, I_("screen"), I_("ExternalTA"));

	onSystemMenuItem (TXT_LOAD_EXTERNALTA_FUND_LINKAGE, CMD_BPROC_EXTERNAL_TA_FUND_LINKAGE, false, dstrParamsIDI);


}
//******************************************************************************
void CDSTCView::OnUpdateExternalTAFundLinkage(CCmdUI* pCmdUI)
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateExternalTAFundLinkage") );

   	pCmdUI->Enable(enableSystemMenuItem(UAF::EXTERNAL_TA_FUND_LINKAGE));
}
//******************************************************************************
static Json::Value DStringToJson(const DString& dstr) 
{
   size_t size = WideCharToMultiByte( CP_UTF8, 0, dstr.c_str(), -1,
                                              NULL, 0,  NULL, NULL);

   char *buffer = new char[size];

   size = WideCharToMultiByte( CP_UTF8, 0, dstr.c_str(), dstr.length(),
                                              buffer, size,  NULL, NULL);
   buffer[size] = '\0';

   Json::Value result(buffer);
   delete[] buffer;
   return result;
}

static DString JsonToDString(const Json::Value& value) 
{
   if (!value.isConvertibleTo(Json::stringValue)) {
      return NULL_STRING;
   }

   DStringA dstr(value.asString());
   size_t size = MultiByteToWideChar( CP_UTF8, 0, dstr.c_str(), -1,
                                              NULL, 0);

   wchar_t *buffer = new wchar_t[size];
   size = MultiByteToWideChar( CP_UTF8, 0, dstr.c_str(), dstr.length(),
                                              buffer, size);
   buffer[size] = L'\0';

   DString result(buffer);
   delete[] buffer;
   return result;
}

void CDSTCView::PostWorkEventMessage(boost::shared_ptr<WorkEvent> const & event) 
{
   PostMessage( WM_WORK_EVENT, 0, reinterpret_cast<LPARAM>(event->clone()) );
}

LRESULT CDSTCView::onWorkEvent(WPARAM wParam, LPARAM lParam) 
{
   MAKEFRAME2 ( CND::IFASTGUI_CONDITION, CLASSNAME, ONAWDEVENT );

   if(m_rpGIUserSession && m_rpGIUserSession->getGIContainer()->hasModalGI()) {
	   CND::CIFast_IFast_ifastgui_err_modal_dialog_is_displaying condition;
	   ADDCONDITIONFROMOBJECT(condition);
		
	   ConditionMessageBox(MYFRAME(), GETCURRENTHIGHESTSEVERITY());

		return(0);
   }

   boost::scoped_ptr<WorkEvent> event(reinterpret_cast<WorkEvent *>(lParam));

   E_COMMANDRETURN eRtn = CMD_FAILURE;

   const Json::Value& eventRoot = event->getEventRoot();

   DString dstrCompanyId = eventRoot["CompanyID"].asString();

   if(NULL_STRING==GetMgmCoName(dstrCompanyId)) {
      // We do not have this company. Maybe there is
      // another instance of Desktop that does, so just
      // exit quietly without an error.
      return(0);
   }

   DString dstrEventType = eventRoot["EventType"].asString();
   if (dstrEventType==I_("DTopStatus")) {
      if (m_workEvent) {
         event->replyInProcess();
      } else {
         event->replyReady();
      }
      return(0);
   }


   if (eventRoot["LoggedIn"]["multi"].asString() == "yes") {
      DiscardMsgDlg discardDlg(NULL, TXT_MULTI_AWD_MSGA, TXT_MULTI_AWD_MSGB, TXT_CONTINUE, TXT_CANCELED);
      if( discardDlg.DoModal() == IDCANCEL )
      {
         return(0);
      }
   }


   event->startInProcess();

   if(!OnBtnEndCall1() ) {
      event->replyError(I_("WORK_SESSION_IN_USE"));
      return(0);
   }

   //start the call...
   startCall(false);
   destroyBusInfo();
   if (m_rpGIWorkSession)
   {
      if( DiffMgmCo(dstrCompanyId) )
      {
         if( !SetMgmCo(dstrCompanyId) )
         {
            event->replyError(I_("CANNOT_CHANGE_MGMTCO"));
            return(0);
         }
      }
   }

   DString dstrEventName = eventRoot["EventName"].asString();

   if (dstrEventType==I_("SmartForm")) {
      Json::Value inFields = eventRoot["InFields"];

      if (inFields.isObject()) {
         DString dstrAWDCrda = inFields["AWDCrda"].asString();
         if (dstrAWDCrda!=NULL_STRING) {
            onSmartForms(dstrAWDCrda);
            event->replyDone();
            return(0);
         }
      }
      
      event->replyError(I_("CANNOT_INVOKE_SMARTFORM"));
      return(0);

   } else
   if (dstrEventType==I_("None")) {
	   return(0);
   }

   if (dstrEventType!=I_("BusProc")) {
	   event->replyError(I_("INVALID_EVENT_MESSAGE"));
	   return(0);
   }

   m_cmbSearch.SetCurSel( 0 );
   OnSelchangeCmbSearch();
   destroyBusInfo();
   resetRoadData();

   DString dstrSearchUsingCode = eventRoot["SearchUsingCode"].asString();
   if (dstrSearchUsingCode!=NULL_STRING) {
      DString dstrFirstValue      = JsonToDString(eventRoot["FirstValue"]);
      DString dstrSecondValue     = JsonToDString(eventRoot["SecondValue"]);
      DString dstrThirdValue      = JsonToDString(eventRoot["ThirdValue"]);

      m_rpGIWorkSession->setParameter( SRCHLIT::SEARCH_CRITERIA_CODE, SEARCHCRITERIA::ACCOUNT_SEARCH );
      m_rpGIWorkSession->setParameter( SRCHLIT::SEARCH_USING_CODE, dstrSearchUsingCode );
      m_rpGIWorkSession->setParameter( SRCHLIT::EXACTSEARCH, I_("Y") );

      m_rpGIWorkSession->setParameter( SRCHLIT::FIRST_VALUE, dstrFirstValue );
      m_rpGIWorkSession->setParameter( SRCHLIT::SECOND_VALUE, dstrSecondValue );
      m_rpGIWorkSession->setParameter( SRCHLIT::THIRD_VALUE,  dstrThirdValue );

      eRtn = CommandDispatcher::getInstance()->invokeCommand ( m_rpGIWorkSession,
                                                               CMD_BPROC_SEARCH,
                                                               PROC_NO_TYPE,
                                                               true,
                                                               NULL
                                                               );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            break;
         case CMD_CANCEL:
			break;
         default:
            event->replyError(I_("CANNOT_FIND_ACCOUNT"));
            ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
            return(0);
         break;
      }

      BaseAccountDetailsDlg* pAcctDetailsDlg = dynamic_cast <BaseAccountDetailsDlg*>
         (m_rpGIUserSession->getGIContainer()->findGI(m_rpGIWorkSession->getBFWorkSession(), CMD_GUI_ACCOUNT_DETAILS));

      if (!pAcctDetailsDlg)
      {
         event->replyError(I_("ACCOUNT_DLG_NOT_INVOKED"));
         return(0);
      }
   
      pAcctDetailsDlg->MoveDlg();
      pAcctDetailsDlg->SetForegroundWindow();

      DString lastAcctNumber;
      pAcctDetailsDlg->getParent ()->getField (m_rpGIWorkSession, IFASTBP_PROC::ACCOUNT_DETAILS_LIST,
         ifds::AccountNum, lastAcctNumber);
      pAcctDetailsDlg->setGlobal (WORK_GLOBAL, ifds::LastActiveAccountNum, lastAcctNumber);

      m_rpGIWorkSession->setParameter (MFCAN_IP_PARAM::ACCOUNT_NUM, lastAcctNumber);

      pAcctDetailsDlg->getParent()->getField (m_rpGIWorkSession, IFASTBP_PROC::ACCOUNT_DETAILS_LIST,
         ifds::AccountNum, lastAcctNumber);

      pAcctDetailsDlg->setGlobal(WORK_GLOBAL, ifds::LastActiveAccountNum, lastAcctNumber);
   }

   if (dstrEventType==I_("BusProc") && dstrEventName!=CMD_BPROC_ACC_DETAILS) {

      Json::Value inFields = eventRoot["InFields"];

      if (inFields.isObject()) {
         for( Json::ValueIterator itr = inFields.begin() ; itr != inFields.end() ; itr++ ) {
            DString dstrFieldName = itr.key().asString();
            Json::Value value = (*itr);
            if (value.isConvertibleTo(Json::stringValue)) {
               m_rpGIWorkSession->setParameter (dstrFieldName, JsonToDString(value));
            }
         }
      
      } else {
         event->replyError(I_("INVALID_EVENT_MESSAGE"));
         return(0);
      }

      m_rpGIWorkSession->setParameter (IS_WORK_EVENT, I_("Y"));

      m_workEvent.swap(event);  // Take ownership

      startCall();

      eRtn = CommandDispatcher::getInstance()->invokeCommand ( m_rpGIWorkSession,
                                                               dstrEventName.c_str(),
                                                               PROC_NO_TYPE,
                                                               (dstrEventName==CMD_BPROC_NASU),
                                                               NULL
                                                             );
      switch( eRtn )
      {
         case CMD_MODELESS_INPROCESS:
            break;
         case CMD_OK:
         case CMD_CANCEL:
            m_workEvent->replyDone();
            m_workEvent.reset();
            break;
         default:
            m_workEvent->replyError(I_("CANNOT_INVOKE_PROCESS"));
            m_workEvent.reset();
            ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
            return(0);
         break;
      }

   } else {
      m_workEvent.swap(event);  // Take ownership
      startCall();
   }


   return(0);

}

DString CDSTCView::getWorkEventField(DString fieldId) {
   if (m_workEvent) {
      const Json::Value& eventRoot = m_workEvent->getEventRoot();

      Json::Value inFields = eventRoot["InFields"];
      if (inFields.isObject()) {
         return JsonToDString(inFields[fieldId.asA()]);
      }
   }
   return NULL_STRING;
}


void CDSTCView::UpdateWorkEvent() {
   if (m_workEvent) {

      BaseAccountDetailsDlg* pAcctDetailsDlg = dynamic_cast <BaseAccountDetailsDlg*>
         (m_rpGIUserSession->getGIContainer()->findGI(m_rpGIWorkSession->getBFWorkSession(), CMD_GUI_ACCOUNT_DETAILS));
      if (pAcctDetailsDlg)
      {
         notifyOk(m_rpGIWorkSession, dynamic_cast<AbstractProcess *>(pAcctDetailsDlg->getParent()));
      }

      m_workEvent->replyUpdate(m_WorkOutData);
	  m_WorkOutData = std::make_pair(Json::Value(Json::objectValue), Json::Value(Json::nullValue));
   }
}

DString CDSTCView::GetMgmCoName(DString companyID)
{
   DSTCUserSession *pDSTCUserSession = dynamic_cast<DSTCUserSession *>(m_rpGIUserSession->getBFSession());
   DString dstrCompanyId, dstrCompanyName;
   long  lNumberOfCompanies = pDSTCUserSession->getNumberOfCompanies( DSTCHost::getPrimaryHost() );
   for( short nCtr = 0; nCtr < lNumberOfCompanies; ++nCtr )
   {
      pDSTCUserSession->getCompanyInfo( DSTCHost::getPrimaryHost(), nCtr, dstrCompanyId, dstrCompanyName );
      if( dstrCompanyId == companyID )
      {
         return dstrCompanyName;
      }
   }
   return NULL_STRING;
}

void CDSTCView::SetWorkComment(const DString& dstrComment) {
   if (m_workEventAgent) {
      m_WorkOutData.second=DStringToJson(dstrComment);
   }
}

void CDSTCView::SetWorkData(const DString& cmdName, const BFData& data) {

   if (!m_workEventAgent) 
      return;

   DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(m_rpGIWorkSession->getBFWorkSession());
	const DSTCSecurity* pSecurity = dynamic_cast<const DSTCSecurity*>(dstWorkSession->getSecurity(DSTCHost::getPrimaryHost()));
   if (!pSecurity)
      return;

   DString dstrCompanyId( NULL_STRING );
   dstWorkSession->getMgmtCo().getField( ifds::CompanyId, dstrCompanyId, BF::HOST);

   Json::Value outFields = m_workEventAgent->getOutFields(pSecurity, dstrCompanyId);
      
   if (outFields.isObject()) {

      Json::Value procOutFields = outFields[cmdName.asA()];
      if (procOutFields.isArray() && procOutFields.size() > 0) {

         if (!m_WorkOutData.first.isMember(cmdName.asA())) {
            m_WorkOutData.first[cmdName.asA()] = Json::Value(Json::objectValue);
         }

         Json::Value& procData = m_WorkOutData.first[cmdName.asA()];

         for( Json::ValueIterator itr = procOutFields.begin() ; itr != procOutFields.end() ; itr++ ) {
            DString dstrFieldName = NULL_STRING;
            BFContainerId idCcontainer = BF::NullContainerId;
            if ((*itr).isConvertibleTo(Json::stringValue)) {
               DString dstrField = (*itr).asString();
               size_t pos = dstrField.find(I_('.'));
               if (pos!=DString::npos) {
                  idCcontainer = BFContainerId(dstrField.left(pos).asInteger());
                  dstrFieldName = dstrField.right(dstrField.size() - pos - 1);
               } else {
                  dstrFieldName = dstrField;
               }
            }
            if (dstrFieldName!=NULL_STRING) {
               const BFFieldId fieldId (BFFieldId::getId (dstrFieldName));
               DString dstrValue;
               try {
                  data.getElementValue(fieldId, dstrValue, 0UL);
                  if (dstrValue!=NULL_STRING) {
                     procData[dstrFieldName.asA()] = DStringToJson(dstrValue.strip());
                  }
               } catch(...) {
                  // field does not exist ... that's OK.  ( a little cheesy ).
                  // but do not want to crash
               }
            }
         }
      }
   }
}

void CDSTCView::notifyOk(const GenericInterface *rpGICaller,
                         AbstractProcess *process) 
{

   if (!m_workEventAgent) 
      return;

   DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(m_rpGIWorkSession->getBFWorkSession());
	const DSTCSecurity* pSecurity = dynamic_cast<const DSTCSecurity*>(dstWorkSession->getSecurity(DSTCHost::getPrimaryHost()));
   if (!pSecurity)
      return;

   DString dstrCompanyId( NULL_STRING );
   dstWorkSession->getMgmtCo().getField( ifds::CompanyId, dstrCompanyId, BF::HOST);

   Json::Value outFields = m_workEventAgent->getOutFields(pSecurity, dstrCompanyId);
      
   DString cmdName;
   cmdName = process->getCommandName();
   if (outFields.isObject()) {

      Json::Value procOutFields = outFields[cmdName.asA()];
      if (procOutFields.isArray() && procOutFields.size() > 0) {

         if (!m_WorkOutData.first.isMember(cmdName.asA())) {
            m_WorkOutData.first[cmdName.asA()] = Json::Value(Json::objectValue);
         }

         Json::Value& procData = m_WorkOutData.first[cmdName.asA()];

         for( Json::ValueIterator itr = procOutFields.begin() ; itr != procOutFields.end() ; itr++ ) {
            DString dstrField = NULL_STRING;
            DString dstrFieldName = NULL_STRING;
            BFContainerId idCcontainer = BF::NullContainerId;
            if ((*itr).isConvertibleTo(Json::stringValue)) {
               dstrField = (*itr).asString();
               size_t pos = dstrField.find(I_('.'));
               if (pos!=DString::npos) {
                  idCcontainer = BFContainerId(dstrField.left(pos).asInteger());
                  dstrFieldName = dstrField.right(dstrField.size() - pos - 1);
               } else {
                  dstrFieldName = dstrField;
               }
            }
            if (dstrFieldName!=NULL_STRING) {
               const BFFieldId fieldId (BFFieldId::getId (dstrFieldName));
               DString dstrValue;
               try {
                  process->getField (rpGICaller, idCcontainer, fieldId, dstrValue, false);
                  if (dstrValue!=NULL_STRING) {
                     procData[dstrField.asA()] = DStringToJson(dstrValue.strip());
                  }
               } catch(...) {
                  // field does not exist ... that's OK.  ( a little cheesy ).
                  // but do not want to crash
               }
            }
         }
      }
   }
}

void CDSTCView::createWork(const DString& dstrEventName) {
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, CREATEWORK );
   if (m_workEventAgent) {
   
      if (m_rpGIWorkSession)
      {
         DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(m_rpGIWorkSession->getBFWorkSession());
		   const DSTCSecurity* pSecurity = dynamic_cast<const DSTCSecurity*>(dstWorkSession->getSecurity(DSTCHost::getPrimaryHost()));
         if (pSecurity)
         {
            Json::Value request = Json::Value();
            
            request["RequestType"] = "Create";
            request["EventName"] = DStringToJson(dstrEventName);
      
            DString dstrCompanyId( NULL_STRING );
            dstWorkSession->getMgmtCo().getField( ifds::CompanyId, dstrCompanyId, BF::HOST);
            request["CompanyId"] = DStringToJson(dstrCompanyId);

            request["Fields"] = m_WorkOutData.first;
            request["Comments"] = m_WorkOutData.second;
            Json::Value response = WorkEventAgent::callService(pSecurity, request, dstrCompanyId);

            if (response["status"] == "Rejected") {
               if (response["messages"][0u]["msgCode"] == "AWD_BUSAREA_NOT_FOUND") {
                  DString dstrParmMsg;
                  addIDITagValue( dstrParmMsg, IDI_LABEL1, dstrCompanyId );
                  DISPLAYCONDITIONFROMFILEIDI( CND::GUI_AWD_MGMCO_ENTRY_MISSING, dstrParmMsg );
               } else {
                  DISPLAYCONDITIONFROMFILE( CND::GUI_AWD_FAILED_UPDATE_OR_CREATE );
               }
            }
         }
      }

   }
} 

Json::Value CDSTCView::lookupWork(const DString& accountNum, const DString& awdContentId) {
   Json::Value params = Json::Value();
   params["AccountNum"] = accountNum.asA(); 
   params["AWDContentId"] = awdContentId.asA(); 
   return lookupWork(params);
}

Json::Value CDSTCView::lookupWork(const DString& accountNum) {
   Json::Value params = Json::Value();
   params["AccountNum"] = accountNum.asA(); 
   return lookupWork(params);
}


Json::Value CDSTCView::lookupWork(const Json::Value& params) {
MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, CREATEWORK );
   if (m_rpGIWorkSession)
   {
      DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(m_rpGIWorkSession->getBFWorkSession());
      const DSTCSecurity* pSecurity = dynamic_cast<const DSTCSecurity*>(dstWorkSession->getSecurity(DSTCHost::getPrimaryHost()));
      if (pSecurity)
      {
         Json::Value request = Json::Value();
         
         request["RequestType"] = "Lookup";

         DString dstrCompanyId( NULL_STRING );
         dstWorkSession->getMgmtCo().getField( ifds::CompanyId, dstrCompanyId, BF::HOST);
         request["CompanyId"] = DStringToJson(dstrCompanyId);

         request["Params"] = params; 

         Json::Value response = WorkEventAgent::callService(pSecurity, request, dstrCompanyId);

         if (response["status"] == "Rejected") {
            if (response["messages"][0u]["msgCode"] == "AWD_BUSAREA_NOT_FOUND") {
               DString dstrParmMsg;
               addIDITagValue( dstrParmMsg, IDI_LABEL1, dstrCompanyId );
               DISPLAYCONDITIONFROMFILEIDI( CND::GUI_AWD_MGMCO_ENTRY_MISSING, dstrParmMsg );
            } else {
               DISPLAYCONDITIONFROMFILE( CND::GUI_AWD_FAILED_UPDATE_OR_CREATE );
            }
         }

         return response;
      }
   }
   return Json::Value();
}

//*****************************************************************************
void CDSTCView::OnRegPlanTransfer()
{
	MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnRegPlanTransfer"));

	DString dstrParamsIDI;

	CString cstrBrowserTitle;
	cstrBrowserTitle.LoadString(TXT_REG_PLAN_TRANSFER);

	onSystemMenuItem(TXT_REG_PLAN_TRANSFER, CMD_BPROC_REG_PLAN_TRANSFER_SEARCH, false, dstrParamsIDI);
}

//*****************************************************************************
void CDSTCView::OnUpdateRegPlanTransfer(CCmdUI* pCmdUI)
{
   MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateFundBrokerLinkage"));

   pCmdUI->Enable( enableSystemMenuItem(UAF::REG_PLAN_TRANSFER) );
}

//*****************************************************************************
void CDSTCView::OnRegAcctExtr()
{
    MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnRegAcctExtr"));

    DString dstrParamsIDI, strBrowserTitle;
    CString cstrBrowserTitle;

    cstrBrowserTitle.LoadString(TXT_REG_ACCT_EXTR_TITLE);
    strBrowserTitle = cstrBrowserTitle;
    strBrowserTitle += I_(":");

    addIDITagValue (dstrParamsIDI, I_("from_screen"), I_("MainScreen"));
    addIDITagValue (dstrParamsIDI, I_("BrowserTitle"), strBrowserTitle);
    addIDITagValue (dstrParamsIDI, I_("screen"),I_("RegAcctExtr") );
    onSystemMenuItem(TXT_LOADING_REG_ACCT_EXTR, CMD_BPROC_REG_ACCT_EXTR, false, dstrParamsIDI);
}

//*****************************************************************************
void CDSTCView::OnUpdateRegAcctExtr(CCmdUI* pCmdUI)
{
    MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateRegAcctExtr"));

    pCmdUI->Enable(enableSystemMenuItem(UAF::REG_ACCT_EXTR));
}

//*****************************************************************************
void CDSTCView::OnRegAcctInfoRev()
{
    MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnRegAcctInfoRev"));

    DString dstrParamsIDI, strBrowserTitle;
    CString cstrBrowserTitle;

    cstrBrowserTitle.LoadString(TXT_REG_ACCT_INFO_REV_TITLE);
    strBrowserTitle = cstrBrowserTitle;
    strBrowserTitle += I_(":");

    addIDITagValue (dstrParamsIDI, I_("from_screen"), I_("MainScreen"));
    addIDITagValue (dstrParamsIDI, I_("BrowserTitle"), strBrowserTitle);
    addIDITagValue (dstrParamsIDI, I_("screen"),I_("RegAcctInfoRev") );
    onSystemMenuItem(TXT_LOADING_REG_ACCT_INFO_REV, CMD_BPROC_REG_ACCT_INFO_REV, false, dstrParamsIDI);
}

//*****************************************************************************
void CDSTCView::OnUpdateRegAcctInfoRev(CCmdUI* pCmdUI)
{
    MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateRegAcctExtr"));

    pCmdUI->Enable(enableSystemMenuItem(UAF::REG_ACCT_INFO_REV));
}

//*****************************************************************************
void CDSTCView::OnWithholdingTaxRatesMaintenance()
{
    MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnWithholdingTaxRatesMaintenance"));

    DString dstrParamsIDI, strBrowserTitle;
    CString cstrBrowserTitle;

    cstrBrowserTitle.LoadString(TXT_WITHHOLDING_TAX_RATES_MAINTENANCE);
    strBrowserTitle = cstrBrowserTitle;
	strBrowserTitle += I_(":");

    addIDITagValue (dstrParamsIDI, I_("from_screen"), I_("MainScreen"));
    addIDITagValue (dstrParamsIDI, I_("BrowserTitle"), strBrowserTitle);
    addIDITagValue (dstrParamsIDI, I_("screen"),I_("WhtRatesMaint") );
    onSystemMenuItem(TXT_LOAD_WITHHOLDING_TAX_RATES_MAINTENANCE, CMD_BPROC_WITHHODLDING_TAX_RATES_MAINTANENCE, false, dstrParamsIDI);
}

//*****************************************************************************
void CDSTCView::OnUpdateWithholdingTaxRatesMaintenance(CCmdUI* pCmdUI)
{
    MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateWithholdingTaxRatesMaintenance"));

    pCmdUI->Enable(enableSystemMenuItem(UAF::WITHHODLDING_TAX_RATES_MAINTANENCE));
}

//*****************************************************************************
void CDSTCView::OnFundDistributionSplitMaintenance()
{
    MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnFundDistributionSplitMaintenance"));

    DString dstrParamsIDI, strBrowserTitle;
    CString cstrBrowserTitle;

    cstrBrowserTitle.LoadString(TXT_FUND_DISTRIBUTION_SPLIT_MAINTENANCE);
    strBrowserTitle = cstrBrowserTitle;
	strBrowserTitle += I_(":");
    

    addIDITagValue (dstrParamsIDI, I_("from_screen"), I_("MainScreen"));
    addIDITagValue (dstrParamsIDI, I_("BrowserTitle"), strBrowserTitle);
    addIDITagValue (dstrParamsIDI, I_("screen"),I_("FundDistribSplit") );
    onSystemMenuItem(TXT_LOAD_FUND_DISTRIBUTION_SPLIT_MAINTENANCE, CMD_BPROC_FUND_DISTRIBUTION_SPLIT_MAINTENANCE, false, dstrParamsIDI);
}

//*****************************************************************************
void CDSTCView::OnUpdateFundDistributionSplitMaintenance(CCmdUI* pCmdUI)
{
    MAKEFRAME2(CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateFundDistributionSplitMaintenance"));

    pCmdUI->Enable(enableSystemMenuItem(UAF::FUND_DISTRIBUTION_SPLIT_MAINTENANCE));
}
//******************************************************************************
void CDSTCView::OnRDSPInterfaceTransactions()
{
	MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnRDSPInterfaceTransactions") );

	DString dstrParamsIDI;
	CString cstrBrowserTitle;
	cstrBrowserTitle.LoadString(TXT_RDSP_INTERFACE_TRANSACTIONS_TITLE);

	addIDITagValue (dstrParamsIDI, I_("from_screen"), I_("MainScreen"));
	addIDITagValue (dstrParamsIDI, I_("BrowserTitle"), I_("RDSP Interface Transactions"));
	addIDITagValue (dstrParamsIDI, I_("screen"), I_("RDSPInterfaceTransactions"));

	onSystemMenuItem (TXT_LOAD_RDSP_INTERFACE_TRANSACTIONS, CMD_BPROC_RDSP_INTERFACE_TRANSACTIONS, false, dstrParamsIDI);

}
//******************************************************************************
void CDSTCView::OnUpdateRDSPInterfaceTransactions(CCmdUI* pCmdUI)
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, I_("OnUpdateRDSPInterfaceTransactions") );

   //Needs to be changed based on permission
   pCmdUI->Enable(true /*enableSystemMenuItem(UAF::RDSP_INTERFACE_TRANSACTIONS*/);
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/dstcview.cpp-arc  $
 * 
 *    Rev 1.306   Jul 23 2012 22:34:34   dchatcha
 * P0179630 FN01 FATCA Project - Foriegn Tax Review.
 * 
 *    Rev 1.305   Jul 23 2012 19:05:52   dchatcha
 * P0179630 FN01 FATCA Project - Foriegn Tax Review.
 * 
 *    Rev 1.304   Jul 16 2012 12:18:12   dchatcha
 * P0179630 FN01 FATCA Project - Foriegn Tax Review.
 * 
 *    Rev 1.303   Jul 06 2012 18:20:36   wp040240
 * IN 2938135 - Desktop/Web screens - to be converted to new Java/Script library 
 * 
 *    Rev 1.302   May 01 2012 09:25:34   if991250
 * CPF - validating that the Registration agent has the appropriate tax type for the CPF account
 * 
 *    Rev 1.301   Apr 05 2012 12:50:32   wp040039
 * PETP0187485-Entity Maintenance
 * 
 *    Rev 1.300   Mar 29 2012 21:26:12   wp040039
 * PETP0187485.FN01- CPF - Agent bank and CPFB
 * Added label for search using Registration Agent
 * 
 *    Rev 1.299   Feb 17 2012 16:54:54   dchatcha
 * P0188394 FN01 - Performance Fee
 * 
 *    Rev 1.298   Feb 15 2012 12:23:38   if991250
 * RESP Diploma Desktop Web
 * 
 *    Rev 1.297   Feb 07 2012 02:16:26   panatcha
 * DesktopWeb conversion
 * 
 *    Rev 1.296   Feb 07 2012 01:01:42   panatcha
 * correct parm for P0188394 - iFast Performance Fee
 * 
 *    Rev 1.295   Jan 24 2012 00:10:52   panatcha
 * P0188394 - iFast Performance Fee
 * 
 *    Rev 1.294   Dec 30 2011 10:30:36   if991250
 * Allowing the language toggle only if the band has read permission on UAF 224
 * 
 *    Rev 1.293   Dec 30 2011 08:56:06   if991250
 * Changing the UserSession locale on language toggle
 * 
 *    Rev 1.292   Dec 28 2011 08:42:52   if991250
 * Killing the work session when changing language
 * 
 *    Rev 1.291   Dec 22 2011 14:55:36   if991250
 * IA French resources/substitutions
 * 
 *    Rev 1.290   Dec 19 2011 23:46:02   popescu
 * DSK French / last screens to be converted to extJS
 * 
 *    Rev 1.289   Dec 05 2011 09:00:30   purdyech
 * ControlTextRewriter Logic
 *
 *    Rev 1.288   Nov 25 2011 15:58:46   wp040168
 * P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
 *
 *    Rev 1.287   Nov 21 2011 18:42:54   wp040168
 * P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
 *
 *    Rev 1.286   Nov 19 2011 01:27:50   wp040143
 * P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
 *
 *    Rev 1.285   Nov 14 2011 08:34:16   popescu
 * Desktop French - modify the screen inputs for the Interface file
 *
 *    Rev 1.284   Nov 09 2011 06:16:38   popescu
 * 2713113 - Global Search Issues
 *
 *    Rev 1.283   Oct 21 2011 13:28:14   popescu
 * SEG - Configuration  S1 (SEG and Desktop skeleton) - synch-up
 *
 *    Rev 1.282   Oct 11 2011 11:46:08   dchatcha
 * P0186484 FN01 - INA - Desktop Seg and Desktop French Enhancements, add language DLL switching support for domestic client.
 *
 *    Rev 1.281   Oct 05 2011 17:15:06   popescu
 * PET186484 - Cross Environment Search
 *
 *    Rev 1.280   Sep 19 2011 19:45:10   dchatcha
 * P0186477 FN01 - GIA Enhancements, remove GIA Attributes as this one will be part of fund setup.
 *
 *    Rev 1.279   Sep 19 2011 10:53:18   dchatcha
 * P0186477 FN01 - GIA Enhancements, functionality will depend on DSK function number.
 *
 *    Rev 1.278   Sep 14 2011 23:30:04   popescu
 * PET186484 - Global Search - added the list of envs to url for global search
 *
 *    Rev 1.277   Aug 31 2011 10:31:42   dchatcha
 * P0186477 FN01 - GIA Enhancements, typo on interest rate configuration screen title.
 *
 *    Rev 1.276   Aug 23 2011 10:11:42   jankovii
 * P0186477 FN01 - GIA Enhancements
 *
 *    Rev 1.275   Aug 22 2011 15:08:22   jankovii
 * P0186477 FN01 - GIA Enhancements
 *
 *    Rev 1.274   Aug 22 2011 12:06:12   dchatcha
 * P0186477 FN01 - GIA Enhancements, Link to interest rate maintenance screen
 *
 *    Rev 1.273   Aug 04 2011 18:27:12   dchatcha
 * P0186477 FN01 - GIA Enhancements
 *
 *    Rev 1.272   Aug 04 2011 05:00:20   wutipong
 * IN2538299 - Error msg when loading desktop (C30252)
 *
 *    Rev 1.271   Jul 28 2011 11:37:48   jankovii
 * PET186484 - Global Search
 *
 *    Rev 1.270   May 24 2011 11:52:36   jankovii
 * Sync up: IN 2532301 - NASU Issue in MFS and Domestic Clients
 *
 *    Rev 1.269   May 12 2011 11:07:34   jankovii
 * Sync up: IN 2511918 - Desktop refresh not working properly with SF
 *
 *    Rev 1.268   May 06 2011 13:28:52   jankovii
 * Sync up: IN 2511918 - Desktop refresh not working properly with SF
 *
 *    Rev 1.267   Mar 30 2011 15:57:54   jankovii
 * Sync up: PET 179563 FN01 - Smart Forms
 *
 *    Rev 1.266   Mar 28 2011 15:36:16   jankovii
 * PET 179563 FN01 - Smart Forms
 *
 *    Rev 1.265   Mar 18 2011 14:13:18   jankovii
 * Sync up: PET 179563 FN01 - Smart Forms
 *
 *    Rev 1.264   Feb 25 2011 08:21:30   wutipong
 * IN#2379878 - Regulatory Documents screen's title bar displayed incorrectly
 *
 *    Rev 1.263   Feb 01 2011 16:59:10   dchatcha
 * P0179308 FN01 - Multi Manager Subscription and Direct Debit Payment.
 *
 *    Rev 1.262   Jan 31 2011 17:52:34   popescu
 * P0179308 FN01 - Multi Manager Subscription and Direct Debit Payment.
 *
 *    Rev 1.261   Dec 09 2010 15:13:10   jankovii
 * IN 2339013 - P0175778: Uptreaming QA testing
 *
 *    Rev 1.260   Nov 25 2010 14:14:32   jankovii
 * PET175778FN01 - Upstreaming Phase 2
 *
 *    Rev 1.259   Nov 22 2010 13:42:44   jankovii
 * PET175778 FN01 - Upstreaming Phase 2
 *
 *    Rev 1.258   Sep 30 2010 10:10:36   jankovii
 * PET168727 FN22 - Trailer Fee Setup
 *
 *    Rev 1.257   Jul 05 2010 14:09:40   jankovii
 * PET165541_FN09_QESI Phase 2
 *
 *    Rev 1.256   Mar 05 2010 16:01:20   yingz
 * call view 276 after user change management company for rr, ff login
 *
 *    Rev 1.255   Feb 19 2010 13:17:20   popescu
 * Fixed an iterator issue - for the the trading screen mapping.
 *
 *    Rev 1.254   Jan 29 2010 11:20:22   popescu
 * Incident 1995449 - Desktop awd history lookup results
 *
 *    Rev 1.253   Jan 18 2010 06:10:32   dchatcha
 * IN# 1952546 - Indicator to show that the database DSK is connected to is scrambled, new bug found when switch management company.
 *
 *    Rev 1.252   Jan 14 2010 04:54:02   dchatcha
 * P0160872 - Fund Setup Phase II - Removed Fund Detail from main menu as replaced by Fund Class Maintenance.
 *
 *    Rev 1.251   Dec 22 2009 06:31:46   dchatcha
 * IN# 1952546 - Indicator to show that the database DSK is connected to is scrambled.
 *
 *    Rev 1.250   Dec 02 2009 09:54:00   popescu
 * P0160872 - Fund Setup Phase II
 *
 *    Rev 1.249   Nov 24 2009 23:02:34   popescu
 * Incident 1845648 - subsequent fix
 *
 *    Rev 1.248   Sep 21 2009 17:17:32   popescu
 * Added support for launching the Trading screen if mapping for pruchase and redeem work types exists in the AWD Ini file
 *
 *    Rev 1.247   Sep 21 2009 15:57:20   popescu
 * Added support for launching the Trading screen if mapping for pruchase and redeem work types exists in the AWD Ini file
 *
 *    Rev 1.246   Aug 21 2009 12:14:08   purdyech
 * Removed "Exiting application" dialog
 *
 *    Rev 1.245   May 14 2009 11:35:36   dchatcha
 * PET160872 FN01 Fund Setup-Class Level.
 *
 *    Rev 1.244   Feb 20 2009 14:57:28   purdyech
 * ZTS Revision 6
 *
 *    Rev 1.243   Feb 06 2009 14:54:30   purdyech
 * Interim CheckIn for ZTS Support (Chris is goin' on vacation!)
 *
 *    Rev 1.242   16 Jan 2009 14:57:18   kovacsro
 * IN#1513670 - Desktop Business Area dropdown defaulting incorrectly from AWD
 *
 *    Rev 1.241   Dec 03 2008 13:56:48   jankovii
 * IN 1505615 - Unclaimed Property - DSK/View issue
 *
 *    Rev 1.240   Nov 03 2008 14:39:20   jankovii
 * PET 5517 FN71 - Unclaimed property phase 2.
 *
 *    Rev 1.239   Nov 03 2008 05:26:54   yaviratp
 * PET5517 FN71B2 Unclaimed Property - new browser screen (Release Frozen Account).
 *
 *    Rev 1.238   Sep 09 2008 16:25:32   jankovii
 * PET 5517 FN71 Stale Cheque.
 *
 *    Rev 1.237   Aug 11 2008 15:04:54   jankovii
 * PET0057430 FN01 - Performance Fee.
 *
 *    Rev 1.236   18 Jul 2008 13:55:02   popescu
 * Incident 1190617 - pop a progress control dialog to monitor the static data loading when the management company is swithced
 *
 *    Rev 1.235   Jul 16 2008 10:16:54   jankovii
 * PET 59888 - AML Enhancemement.
 *
 *    Rev 1.234   Jul 11 2008 16:22:26   jankovii
 * PET59888 FN01 - AML Enhancement.
 *
 *    Rev 1.233   23 May 2008 08:54:40   kovacsro
 * IN#1246386 (closed) - fixed Broker level fund limitation screen
 *
 *    Rev 1.232   Apr 21 2008 16:08:26   daechach
 * Change calling to 'CMD_BPROC_PAYMENT_SEARCH' inside method OnFundLimitation() to 'CMD_BPROC_FUND_CLASS_LIMITATION'
 *
 *    Rev 1.231   07 Mar 2008 14:09:20   kovacsro
 * IN#1172388 - if CheckClosedBatch GC is on, show 'Batch is locked' error message, if that is the case
 *
 *    Rev 1.230   06 Dec 2007 15:20:24   popescu
 * Incident 1088629 - read the ACL set-up for the web pages URL instead of the using the xml configuration file.
 *
 *    Rev 1.229   17 Oct 2007 10:18:14   kovacsro
 * IN#1015356 - added a wait cursor, since this is time consuming
 *
 *    Rev 1.228   16 Oct 2007 15:55:12   kovacsro
 * IN#1015356 - changed the hard edit into a soft one
 *
 *    Rev 1.227   27 Sep 2007 14:38:16   kovacsro
 * IN#1015356 - restored 1.224 and added displayActiveBatches()
 *
 *    Rev 1.226   26 Sep 2007 16:56:50   kovacsro
 * IN1015356 - finalized
 *
 *    Rev 1.225   25 Sep 2007 10:32:02   popescu
 * Incident 1015356 - pop-up message for active batches
 *
 *    Rev 1.224   Aug 13 2007 10:18:02   ivespaul
 * PET2360 - Web Integration - check security/function ids to
 * enable/disable management fee rebate, dilution calculator and
 * account balance override web screens.
 *
 *    Rev 1.223   Aug 10 2007 11:47:34   ivespaul
 * PET2360 - Web Integration.
 *
 *    Rev 1.222   Mar 15 2007 14:55:24   jankovii
 * PET 2302 FN01 - Payment Release.
 *
 *    Rev 1.221   Feb 14 2007 15:12:22   jankovii
 * PET 2302 FN01 - Payment Release.
 *
 *    Rev 1.220   Dec 18 2006 17:51:20   popescu
 * Added support for dde server
 *
 *    Rev 1.219   Dec 06 2006 15:39:38   fengyong
 * Sync up to 74, Incident #770115 - fix screen title of fundlimitation
 *
 *    Rev 1.218   Nov 22 2006 15:55:06   fengyong
 * Incident #754735  - disable remarks button if there is no account number or user do not have access to remark screen.
 *
 *    Rev 1.217   Nov 21 2006 16:35:08   jankovii
 * PET 2287 FN01 Grupo Mundial Trade Aggregation.
 *
 *    Rev 1.216   Nov 02 2006 13:42:10   fengyong
 * PET2185 FN02 Add function Id for fund limitation.
 *
 *    Rev 1.215   Nov 01 2006 11:18:44   ZHANGCEL
 * PET2217 FN26 -- Add a logic to pop up FundSponsor list with <F4>
 *
 *    Rev 1.214   Oct 19 2006 09:37:32   fengyong
 * Temp check in for PET 2185 - Fund limitation
 *
 *    Rev 1.213   Oct 05 2006 17:21:52   fengyong
 * Incident 727548 - disable payment search screen for canada market
 *
 *    Rev 1.211   Aug 25 2006 15:40:32   fengyong
 * PET2192 FN17 - Add system menu Payment Search
 *
 *    Rev 1.210   Aug 23 2006 14:53:26   fengyong
 * temp check in for PET 2192
 *
 *    Rev 1.209   Aug 04 2006 14:35:48   ZHANGCEL
 * PET2192 FN11 - Move submenu item "Pay to Entity" and "Payment Instruction" to System Maintenance sub menu
 *
 *    Rev 1.208   Jul 27 2006 18:02:52   ZHANGCEL
 * PET2192 FN11 - Commission Payments to MgmtCo related changes
 *
 *    Rev 1.207   May 08 2006 11:43:06   popescu
 * Incident# 613483 - the standard  'Confirmation' window will pop-up for entering AWD Comments - enhancement
 *
 *    Rev 1.206   Nov 22 2005 09:51:14   porteanm
 * PET1228_FN01-EU Savings Directive Phase two.
 *
 *    Rev 1.205   Nov 11 2005 18:33:52   porteanm
 * PET1228_FN01-EU Savings Directive Phase two.
 *
 *    Rev 1.204   Nov 10 2005 13:22:16   porteanm
 * PET 1286 FN01 - Bulk Cancellation.
 *
 *    Rev 1.203   Nov 04 2005 11:06:10   ZHANGCEL
 * PET 1286  FN01 -- Add  Cancellation Instruction search related issue
 *
 *    Rev 1.202   Oct 27 2005 10:41:26   jankovii
 * PET1228_FN01-EU Savings Directive Phase
 *
 *    Rev 1.201   Sep 22 2005 18:55:00   fengyong
 * Incident 403519 - Add menu Default Setting
 *
 *    Rev 1.200   Sep 14 2005 15:23:48   fengyong
 * Incident #402467 - menu item enabled when change mgmt company and there is no childrent desktop window opened.
 *
 *    Rev 1.199   Sep 14 2005 10:20:44   yingbaol
 * Fix Combo box issue.
 *
 *    Rev 1.198   Aug 03 2005 11:48:44   hernando
 * Incident 358734 - Flag from INI determines FYI on start.
 *
 *    Rev 1.197   May 27 2005 10:30:54   popescu
 * Incident # 319459 - called the trades process for manual dividends
 *
 *    Rev 1.196   Apr 18 2005 09:18:02   yingbaol
 * Incident 288575: Search by whereuse support
 *
 *    Rev 1.195   Mar 09 2005 16:08:46   yingbaol
 * PET1171,FN01: EU saving, entity update
 *
 *    Rev 1.194   Feb 24 2005 19:21:18   popescu
 * Incident # 243353, added timer used to monitor if fund master/detail list are fully loade. Status bar message is displayed while data is loading, synch-up from release 59.04
 *
 *    Rev 1.193   Feb 14 2005 18:50:44   hernando
 * PET1117 FN66-68 - Added msgs to support Message Inquiry and File Inquiry fns.
 *
 *    Rev 1.192   Feb 08 2005 11:30:36   hernando
 * PET1117 FN66-68 - Added functions to support Message Inquiry and File Inquiry menu items.
 *
 *    Rev 1.191   Jan 17 2005 18:27:06   hernando
 * PTS10037736 - Removed reference to AWDEVENT.
 *
 *    Rev 1.190   Dec 07 2004 10:29:04   zhangcel
 * PET1117 - FN8 -- Added User access check for Aggregated Order
 *
 *    Rev 1.189   Nov 26 2004 14:48:34   zhangcel
 * PET1117/FN8 -- Aggregated Order related changes
 *
 *    Rev 1.188   Nov 24 2004 16:51:38   Fengyong
 * uncomment functional ID
 *
 *    Rev 1.187   Nov 18 2004 09:52:50   Fengyong
 * no change
 *
 *    Rev 1.186   Nov 14 2004 15:00:34   purdyech
 * PET910 - .NET Conversion
 *
 *    Rev 1.185   Nov 07 2004 14:56:22   popescu
 * PET 1117/06, synch changes
 *
 *    Rev 1.184   Oct 19 2004 14:40:22   FENGYONG
 * PET1117 FN54 - Fund Broker Static
 *
 *    Rev 1.183   Oct 13 2004 16:19:26   VADEANUM
 * PET1117 FN21 - Renamed from SettleLoc to SettlementInstr
 *
 *    Rev 1.182   Oct 01 2004 12:25:48   FENGYONG
 * Add FundBroker to Menu
 *
 *    Rev 1.181   Sep 21 2004 13:27:10   HERNANDO
 * PET1094 FN06 - Absatzmeldung Files enhancement.
 *
 *    Rev 1.180   Sep 02 2004 13:28:52   FENGYONG
 * uncomment UAF check for PET1117 FN5 after view code go to master
 *
 *    Rev 1.179   Aug 12 2004 14:41:12   FENGYONG
 * Since release 58, generic interfacecontainer do not accept globleview
 *
 *    Rev 1.178   Aug 10 2004 11:28:06   FENGYONG
 * PET 1117 FN5 - Client Condition Fee
 *
 *    Rev 1.177   Jul 27 2004 13:32:26   FENGYONG
 * Removed GlobelVW for GenericInterfaceContainer,
 * Fix 58 and up release compile problem.
 *
 *    Rev 1.176   Jun 17 2004 17:47:18   FENGYONG
 * PTS10031349, fix problems caused by  "onSystemMenuItem" function.
 *
 *    Rev 1.175   Jun 17 2004 13:52:50   HERNANDO
 * Sync'd 1.160.1.5 -  PTS 10028385 - Update business area.
 *
 *    Rev 1.174   May 20 2004 10:53:54   FENGYONG
 * PET1046 - transfer switch - rel 57
 *
 *    Rev 1.173   May 19 2004 15:16:56   FENGYONG
 * PET1046 - transfer switch, fix after unit test
 *
 *    Rev 1.172   May 19 2004 13:15:52   YINGBAOL
 * PTS10029450: change logic of display discard error message when there is an AWD object has not been updated
 *
 *    Rev 1.171   May 11 2004 14:24:46   FENGYONG
 * PET1046 FN1 - transfer-switch -Rel57
 *
 *    Rev 1.170   May 05 2004 17:35:12   YINGBAOL
 * PET1017:AWD clone
 *
 *    Rev 1.169   May 05 2004 14:05:52   VADEANUM
 * PET 1017 - AWD Comments - work in progress.
 *
 *    Rev 1.168   May 03 2004 11:55:34   HERNANDO
 * PET1017 FN02 - Enabled/disabled AWD buttons.  Added call to store Object ID.
 *
 *    Rev 1.167   Mar 26 2004 14:28:52   YINGBAOL
 * Sync. Version 1.160.1.6
 *
 *    Rev 1.166   Mar 12 2004 11:20:30   YINGBAOL
 * PTS10028049: sync.version 1.160.1.3
 *
 *    Rev 1.165   Mar 04 2004 09:03:16   YINGBAOL
 * PTS10027730:sync.Version 1.162.1.2
 *
 *    Rev 1.164   Mar 02 2004 14:32:54   YINGBAOL
 * PTS10027246: Sync. version 1.161.1.1
 *
 *    Rev 1.163   Feb 23 2004 14:25:16   YINGBAOL
 * PTS10027246:Sync trunk.
 *
 *    Rev 1.162   Jan 30 2004 16:44:16   VADEANUM
 * PET 859 FN23 - ADL support.
 *
 *    Rev 1.161   Jan 28 2004 21:35:24   popescu
 * PET 859, FN 23, modified resources (dialogs and menu item) and coded for the features search dialog
 *
 *    Rev 1.160   Jan 12 2004 14:54:24   YINGBAOL
 * PET987: AWDSession change
 *
 *    Rev 1.159   Dec 31 2003 14:39:50   HERNANDO
 * PET910 - AWD Voice Integration enhancement.
 *
 *    Rev 1.158   Dec 04 2003 15:51:12   ZHANGCEL
 * PTS 10020087 -- Enhanced to pass host information
 *
 *    Rev 1.157   Nov 27 2003 15:06:16   ZHANGCEL
 * minor changes
 *
 *    Rev 1.156   Nov 27 2003 14:21:42   ZHANGCEL
 * PTS ticket 10022899: Bug fix for the serach error showing issue; Synch up 1.155.1.0
 *
 *    Rev 1.155   Nov 20 2003 17:31:20   HERNANDO
 * PET859 FN1 - Added OnSettlementLocation and OnUpdateSettlementLocation.
 *
 *    Rev 1.154   Oct 24 2003 17:20:18   popescu
 * CIBC PET 809, FN 13
 *
 *    Rev 1.153   Oct 04 2003 16:02:10   popescu
 * CIBC PET 809, FN 13;
 * also cleaned-up BankSearch and BankList objects,
 * replaced with FinancialInstitutionList
 *
 *    Rev 1.152   Sep 23 2003 18:44:24   popescu
 * Added the IDD_FINANCIAL_INSTITUTIONS dialog in the resources, as well as the new menu item for invoking it
 *
 *    Rev 1.151   Aug 01 2003 11:51:26   popescu
 * synch-up with 52, added the security check for payment instructions and pay to entity
 *
 *    Rev 1.150   Jul 11 2003 18:35:58   popescu
 * dstcview synch-up 52 - 53
 *
 *    Rev 1.149   Jun 17 2003 16:06:54   SMITHDAV
 * Move CSI shutdown to dstcview.
 *
 *    Rev 1.148   Jun 09 2003 16:08:08   SMITHDAV
 * Changes related to Attachmate EXTRA integration
 *
 *    Rev 1.147   May 23 2003 14:38:32   HERNANDO
 * Added OnManualDividend and OnUpdateManualDividend.
 *
 *    Rev 1.146   Apr 16 2003 13:22:50   popescu
 * Enable the system level menu items when there is no worksession available (where there is no work)
 *
 *    Rev 1.145   Apr 16 2003 09:39:44   YINGBAOL
 * remove AMS Global from search  to system menu
 *
 *    Rev 1.144   Apr 09 2003 17:14:48   popescu
 * synch-up to trunc
 *
 *    Rev 1.143   Mar 31 2003 16:20:28   sanchez
 * Enable/disable menu options "Settlement" and "Trade Entry" depending on security flags
 *
 *    Rev 1.142   Mar 25 2003 11:53:30   sanchez
 * Hookup the "Trade Entry" and "Settlement" menu options to the ON_COMMAND() macro.
 *
 *    Rev 1.141   Mar 21 2003 20:03:52   PURDYECH
 * Sync 1.138.1.0 back to trunk
 *
 *    Rev 1.139.1.0   Mar 21 2003 18:35:14   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 *
 *    Rev 1.139   Mar 14 2003 17:28:00   FENGYONG
 * Add menu Broker level AMS
 *
 *    Rev 1.138   Mar 05 2003 14:22:42   KOVACSRO
 * Show discard screen if there are updates before opening trade search screen.
 *
 *    Rev 1.137   Mar 03 2003 09:46:28   KOVACSRO
 * Added TradeSearch
 *
 *    Rev 1.136   Feb 26 2003 13:46:10   linmay
 * clean up message
 *
 *    Rev 1.135   Feb 18 2003 11:46:12   popescu
 * Added security check for AMS report menu item
 *
 *    Rev 1.134   Feb 06 2003 12:03:40   popescu
 * Checking in for Historical Info Search screen
 *
 *    Rev 1.133   Feb 06 2003 10:24:44   popescu
 * added the handlers for Historical Info Searc
 *
 *    Rev 1.132   Feb 05 2003 13:24:46   HERNANDO
 * Revised UAF for MKT_INDEX.
 *
 *    Rev 1.131   Jan 31 2003 13:09:52   HERNANDO
 * Added OnUpdateMktIndex.
 *
 *    Rev 1.130   Jan 31 2003 11:38:00   popescu
 * Added the a message on the status bar
 *
 *    Rev 1.129   Jan 29 2003 16:07:26   YINGBAOL
 * System level Fee should be model
 *
 *    Rev 1.128   Jan 29 2003 13:29:06   HERNANDO
 * Added OnMktIndexValues.
 *
 *    Rev 1.127   Jan 23 2003 11:22:58   HERNANDO
 * Renamed CMD_BPROC_INDEX_MASTER to CMD_BPROC_MKT_INDEX_MASTER.
 *
 *    Rev 1.126   Jan 22 2003 15:56:38   popescu
 * Compilation fix
 *
 *    Rev 1.125   Jan 22 2003 15:52:48   popescu
 * Fixes related with not being able to commit the changes to backend if the dialog ProtectedFundDialog is modal
 *
 *    Rev 1.124   Jan 21 2003 15:12:02   YINGBAOL
 * added  OnSystemLevelFee()
 *
 *    Rev 1.123   Jan 21 2003 11:22:20   HERNANDO
 * Added OnMktIndexMaster.
 *
 *    Rev 1.122   Jan 20 2003 15:43:58   popescu
 * Checked in for unit testing the ProtectedFundSetup feature
 *
 *    Rev 1.121   Dec 08 2002 22:17:18   HSUCHIN
 * added report status option
 *
 *    Rev 1.120   Nov 27 2002 13:18:48   HSUCHIN
 * fixed sync up mistake
 *
 *    Rev 1.119   Nov 27 2002 11:55:30   HSUCHIN
 * sync up with R50_Rework 1.117.1.0
 *
 *    Rev 1.117.1.0   Nov 27 2002 11:48:56   HSUCHIN
 * added reports and sync up with R50_Dev
 *
 *    Rev 1.117   Nov 19 2002 15:30:12   HERNANDO
 * Undid changes for PTS 10009814.
 *
 *    Rev 1.116   Oct 09 2002 23:55:38   PURDYECH
 * PVCS Database Conversion
 *
 *    Rev 1.115   Oct 01 2002 08:52:12   PURDYECH
 * Overload resolution conflict.
 *
 *    Rev 1.114   Sep 30 2002 11:01:38   PURDYECH
 * BFFieldId no longer has operator long(), so explicit getId() calls are needed in places.
 *
 *    Rev 1.113   Sep 19 2002 14:20:56   YINGBAOL
 * Copy / Paste support for account number
 *
 *    Rev 1.112   Sep 16 2002 18:07:44   HERNANDO
 * PTS 10009813 - Multiple AWD Business Areas mapped to the same System ID will cause look-ups to ignore Business Area.
 *
 *    Rev 1.111   Sep 16 2002 17:11:46   HERNANDO
 * PTS 10009814 - Removed 'COR' from Transfer Agency code.
 *
 *    Rev 1.110   Aug 29 2002 12:57:20   SMITHDAV
 * ClientLocale and typed field changes.
 *
 *    Rev 1.109   Aug 26 2002 17:09:28   HERNANDO
 * Precautinary code - removed tabs from all getValueAsString from a table in the .ini file.
 *
 *    Rev 1.108   Aug 26 2002 16:34:56   HERNANDO
 * Precautionary code - Remove tabs from the value of an AWD Mapped Field in getWorkDataForAccountSearch.
 *
 *    Rev 1.107   Aug 16 2002 13:51:24   YINGBAOL
 * check permission for Setttlement
 *
 *    Rev 1.106   Jul 31 2002 10:20:18   YINGBAOL
 * Allow delete for Edit
 *
 *    Rev 1.105   Jul 30 2002 12:04:42   YINGBAOL
 * added LEdit Type and force user to input numeric number for SIN Account Nbr. ShareholderNbr and Certificate Nbr.
 *
 *    Rev 1.104   Jul 17 2002 15:34:20   KOVACSRO
 * Fixed some copy-paste errors.
 *
 *    Rev 1.103   Jul 17 2002 13:19:28   HERNANDO
 * Added/revised AWD literals -- for Canadian mkt.
 *
 *    Rev 1.102   Jul 03 2002 14:13:28   HERNANDO
 * Changed use of GUI_AWD_MGMCO_ENTRY_MISSING and GUI_AWD_INVALID_MAPPED_EVENT.  Changed parm for GUI_AWD_SYSTEM_ERROR.  Uncommented ifdef to attempt getWorkData processing with BFAwdData implementation.
 *
 *    Rev 1.101   Jun 14 2002 10:23:38   HSUCHIN
 * bug fix to settlement dlg launch
 *
 *    Rev 1.100   Jun 08 2002 13:28:32   HSUCHIN
 * added settlement support
 *
 *    Rev 1.99   May 29 2002 15:17:44   KOVACSRO
 * BFData Implementation - Phase II - syncup
 *
 *    Rev 1.98   24 May 2002 17:13:38   KOVACSRO
 * fund and client banking.
 *
 *    Rev 1.97.1.0   May 28 2002 12:19:50   PURDYECH
 * BFData Implementation - Phase II
 *
 *    Rev 1.97   23 May 2002 11:05:14   KOVACSRO
 * BFData.
 *
 *    Rev 1.96.1.0   May 23 2002 10:40:54   PURDYECH
 * BFData Implementation Verification Corrections
 *
 *    Rev 1.96   25 Apr 2002 14:48:58   HERNANDO
 * Modified SetMgmCo to retain user's ManagementCompany selection in the registry.
 *
 *    Rev 1.95   15 Apr 2002 14:54:40   HERNANDO
 * PTS 10007576 - Add newSearch.
 *
 *    Rev 1.94   Apr 04 2002 10:54:50   JANKAREN
 * PTS 10007509 - added UserAccess for Broker, Branch and Rep
 *
 *    Rev 1.93   Apr 03 2002 18:34:42   HERNANDO
 * Allow changing MgmtCo without losing AWD Work Object.
 *
 *    Rev 1.92   Apr 03 2002 16:26:02   HERNANDO
 * Session and AWD changes.
 *
 *    Rev 1.91   27 Mar 2002 20:01:06   PURDYECH
 * Process/WindowFactory overhaul
 *
 *    Rev 1.90   Mar 20 2002 17:27:50   HERNANDO
 * PTS 10007526 - Accelerator for Ctrl-R.
 *
 *    Rev 1.89   Feb 26 2002 11:13:40   HERNANDO
 * Added check for [MGMCO] table in getWorkDataForAccountSearch.
 *
 *    Rev 1.88   Feb 14 2002 11:11:52   HERNANDO
 * Added doNASU.  Added Conditions.  Unlock AWD objects.  Chg'd DiscardMsgDlg calls.
 *
 *    Rev 1.87   10 Jan 2002 12:18:40   KOVACSRO
 * Keeping MgmtCompanies arround.
 *
 *    Rev 1.86   Dec 20 2001 13:31:46   HERNANDO
 * Added AWD-related conditions.
 *
 *    Rev 1.85   Dec 12 2001 15:20:14   HERNANDO
 * clean up.
 *
 *    Rev 1.84   Dec 10 2001 18:25:26   HERNANDO
 * Changed implementation of Session labelling -- fixes ReloadResource without Session when changing MgmtCos.
 *
 *    Rev 1.83   Dec 07 2001 17:59:18   HERNANDO
 * Revised use of AwdInterface; removed m_pAwdInterface; fixed ReloadResource to redisplay AWD Menu Items.
 *
 *    Rev 1.82   Nov 29 2001 16:31:34   HERNANDO
 * Added ON_COMMAND(ID_HELP, OnHelp1) for F1 default to Desktop help.
 *
 *    Rev 1.81   Nov 29 2001 14:30:58   HERNANDO
 * Added OnHelp1(), OnHelp2(), OnHelp3(), LaunchHelp(), dwHtmlHelpCookie; removed OnHelp()
 *
 *    Rev 1.80   Nov 28 2001 17:27:26   HERNANDO
 * Added OnHelp().
 *
 *    Rev 1.79   13 Nov 2001 10:30:20   KOVACSRO
 * synch-up to 1.77.1.0
 *
 *    Rev 1.78   Nov 07 2001 17:57:42   ZHANGCEL
 * Haspermission changes
 *
 *    Rev 1.77   Oct 12 2001 14:03:58   HERNANDO
 * Added messages to eventually be replaced with conditions.  Removed duplicate function call.
 *
 *    Rev 1.76   26 Sep 2001 18:05:08   HUANGSHA
 * fix for loading the resource dll
 *
 *    Rev 1.75   24 Sep 2001 11:00:18   HSUCHIN
 * added function to enable/disable trade button
 *
 *    Rev 1.74   Sep 20 2001 10:58:40   HUANGSHA
 * Load resource dll based on ClientId instead of the CompanyId
 *
 *    Rev 1.73   Aug 09 2001 15:44:18   HUANGSHA
 * remove the hardcoded string
 *
 *    Rev 1.72   03 Aug 2001 16:41:52   HSUCHIN
 * removed hostupdated check onbtnendcall and fixed Discard msg from using hardcoded text to use string table
 *
 *    Rev 1.71   30 Jul 2001 15:49:52   YINGZ
 * auto change of resources
 *
 *    Rev 1.70   Jul 30 2001 13:59:44   YINGBAOL
 * useing string table instead of hard code
 *
 *    Rev 1.69   11 Jul 2001 12:20:42   SMITHDAV
 * Fix Global Session cleanup problems.
 *
 *    Rev 1.68   Jul 09 2001 18:59:42   HERNANDO
 * Changed getWorkData - uses AWD Status, .default implemented.
 *
 *    Rev 1.67   09 Jul 2001 15:25:12   SMITHDAV
 * Mgmt company refresh related changes.
 *
 *    Rev 1.66   06 Jul 2001 14:14:34   HSUCHIN
 * create a work session on initial update hence downloaded some global management company info to improve performance.
 *
 *    Rev 1.65   Jun 21 2001 18:36:26   HERNANDO
 * Added Default Business Area for AWD GetWorkData.
 *
 *    Rev 1.64   Jun 19 2001 18:45:12   HERNANDO
 * Changed parameter passed to Encorr and Forms.
 *
 *    Rev 1.63   Jun 15 2001 17:47:44   HERNANDO
 * Added AWD for Luxembourg.
 *
 *    Rev 1.62   14 Jun 2001 12:00:14   SMITHDAV
 * Fixed worksession cleanup problems.
 *
 *    Rev 1.61   11 Jun 2001 16:54:16   KOVACSRO
 * 1. Added redemption user access code.
 * 2. Added permission check for 'New Shareholder" button.
 *
 *    Rev 1.60   Jun 11 2001 15:27:24   HERNANDO
 * Restructuring sync- changed SetMgmtCo, OnBtnSearch,  OnCmdMsg, OnAwdHistory.
 *
 *    Rev 1.59   May 17 2001 19:08:54   HERNANDO
 * Sync with 1.57.2.2
 *
 *    Rev 1.58   03 May 2001 14:07:30   SMITHDAV
 * Session management restructuring.
 *
 *    Rev 1.57   Apr 02 2001 13:05:00   DINACORN
 * Used DSTCommonFunctions MARKET_IDS constants
 *
 *    Rev 1.56   Mar 19 2001 18:12:50   HERNANDO
 * Disable Search Button on Search.
 *
 *    Rev 1.55   Mar 09 2001 14:40:34   ZHANGCEL
 * remove the code those are regarding with the Bank EnquiryThread
 *
 *    Rev 1.54   Mar 09 2001 09:56:26   JANKAREN
 * Add permission for tax rates
 *
 *    Rev 1.53   07 Mar 2001 15:44:40   BUZILAMI
 * Broker, Branch, SlsRep Bank Instructions changes
 *
 *    Rev 1.52   Mar 02 2001 13:53:12   HSUCHIN
 * bug fix for mgmt co change
 *
 *    Rev 1.51   Feb 22 2001 15:59:50   HERNANDO
 * Added Business_Area criteria to AWD History.
 *
 *    Rev 1.50   Feb 14 2001 10:37:16   HSUCHIN
 * initialized mgmco on initial upadate
 *
 *    Rev 1.49   Feb 13 2001 09:34:00   HSUCHIN
 * removed mfdstcsetup::init() from initialupdate
 *
 *    Rev 1.48   Feb 12 2001 17:17:50   DINACORN
 * Change "MSDW - Japan" to "Japan"
 *
 *    Rev 1.47   Feb 06 2001 14:59:40   HERNANDO
 * Added SystemID criteria to AWD History.
 *
 *    Rev 1.46   Jan 25 2001 16:47:56   OLTEANCR
 * added in OnInitialUpdate( ) :setWorkSessionDetailsFactory(new DSTCWorkSessionDetailsFactory )
 *
 *    Rev 1.45   Jan 17 2001 10:39:00   ZHANGCEL
 * Added calling EnquiryBankAtBackgroud in OnCmdMsg() to force the baklist to be set up as long as Management company changed
 *
 *    Rev 1.44   Nov 17 2000 11:30:50   HERNANDO
 * Revised OnAwdHistory; handles more fields, displays msgs.
 *
 *    Rev 1.43   Nov 10 2000 11:40:10   HERNANDO
 * Revised getWorkDataForAccountSearch.
 *
 *    Rev 1.42   Nov 08 2000 15:19:40   HSUCHIN
 * fixed Change Management Company bug due to infrastructure changes.
 *
 *    Rev 1.41   Nov 01 2000 16:49:14   HERNANDO
 * Added alternate find for MGMCO table.
 *
 *    Rev 1.40   Oct 31 2000 16:45:44   HERNANDO
 * Modified CanPerformSearch wrt AWD objects and Discard Dlg
 *
 *    Rev 1.39   Oct 31 2000 11:35:08   VASILEAD
 * Passed GIC in creation of UserSessionProcess
 *
 *    Rev 1.38   Oct 23 2000 16:24:16   HERNANDO
 * Made chgs. re clearing WorkSession; as confirmed.
 *
 *    Rev 1.37   Oct 20 2000 14:46:10   HERNANDO
 * Quick fix - MgmCo name in SetMgmCo
 *
 *    Rev 1.36   Oct 18 2000 18:17:38   HERNANDO
 * Added flag - conditional Discard of AWD work object
 *
 *    Rev 1.35   Oct 13 2000 15:22:00   HERNANDO
 * Conditional getWorkData based on INI implementation
 *
 *    Rev 1.34   Oct 10 2000 15:41:00   HERNANDO
 * stripAll on Account Number before look up.
 *
 *    Rev 1.33   Oct 10 2000 11:58:40   HERNANDO
 * AWD Look Up removed upon successful MgmCo chg
 *
 *    Rev 1.32   Oct 06 2000 17:51:48   HERNANDO
 * Remove an AWD Look Up if changing Management Co
 *
 *    Rev 1.31   Oct 06 2000 17:19:52   HERNANDO
 * Added OnAwdHistory
 *
 *    Rev 1.30   Oct 04 2000 10:35:26   ZHANGCEL
 * Recovered "Entity" to SearchComb List and filtered the "EntityID" from SearchUsingEntitySet
 *
 *    Rev 1.29   Sep 29 2000 17:08:36   HERNANDO
 * Undid Subsession chg. until further investigation.
 *
 *    Rev 1.28   Sep 29 2000 16:40:38   HERNANDO
 * Subsession for Worksession fix; creates AWD session
 *
 *    Rev 1.27   Sep 29 2000 13:29:18   YINGZ
 * change market from cfds - canada to canada
 *
 *    Rev 1.26   Sep 28 2000 18:10:40   HERNANDO
 * Fixed bug - possible getAwdSession from NULL
 *
 *    Rev 1.25   Sep 28 2000 15:18:50   HERNANDO
 * Chg'd getWorkData to handle Area Code; cleaned up code
 *
 *    Rev 1.24   Sep 27 2000 13:14:36   ZHANGCEL
 * Remove "Entity" from SearchComb list
 *
 *    Rev 1.23   Sep 22 2000 15:09:38   HERNANDO
 * Fixed bug in SetUsingList
 *
 *    Rev 1.22   Sep 22 2000 13:44:02   KOVACSRO
 * allow user not enter the area code for a telephone search.
 *
 *    Rev 1.21   Sep 22 2000 08:59:04   KOVACSRO
 * Added area code for telephone.
 *
 *    Rev 1.20   Sep 13 2000 17:58:00   HERNANDO
 * Chg'd expected location of MGMCO Table (Session -> AWDEvent)
 *
 *    Rev 1.19   Sep 08 2000 15:11:16   HERNANDO
 * Implemented (Revised) GetWorkData - Requires Config. Table settings
 *
 *    Rev 1.18   Aug 29 2000 15:12:50   YINGBAOL
 * add search account using intermediary code and account
 *
 *    Rev 1.17   Aug 25 2000 10:43:24   YINGBAOL
 * add trade screen to NASU flow
 *
 *    Rev 1.16   Aug 16 2000 15:01:42   YINGBAOL
 * implement function "Search for Trade"
 *
 *    Rev 1.15   Jul 31 2000 17:33:00   HERNANDO
 * Added revised GetWorkData fn.; currently disabled
 *
 *    Rev 1.14   Jun 19 2000 14:46:32   HUANGSHA
 * don't disable F8 and F12 button if no new search started
 *
 *    Rev 1.13   Jun 05 2000 17:09:18   HUANGSHA
 * Fixed the label display problem, disabel the menu item: IDM_TAXRATES
 *
 *    Rev 1.12   Jun 01 2000 12:16:08   BUZILA
 * Trading security rights is governed only by flags 37 and 38 from seccurity view
 *
 *    Rev 1.11   Jun 01 2000 11:34:36   BUZILA
 * added security for Trading
 *
 *    Rev 1.10   Apr 20 2000 16:38:46   BUZILA
 * changed to MgmtCoId
 *
 *    Rev 1.9   Apr 12 2000 11:04:52   BUZILA
 * we should not send to AWD discarded changes
 *
 *    Rev 1.8   Apr 05 2000 14:31:30   DT24433
 * changed usage of GIContainer and changed to use hasPermission
 *
 *    Rev 1.7   Apr 03 2000 15:41:16   DT24433
 * removed unused header, some commented code, and businfo member variable
 *
 *    Rev 1.6   Apr 03 2000 10:35:38   YINGZ
 * code sync
 *
 *    Rev 1.5   Mar 30 2000 09:45:40   BUZILA
 * fix BusInfoDlg cleanup
 *
 *    Rev 1.4   Mar 23 2000 15:50:10   BUZILA
 * fix double destroing BusInfo on EndCall
 *
 *    Rev 1.3   Mar 22 2000 09:00:30   PETOLESC
 * Added Tax Rates, RESP dialogs.
 *
 *    Rev 1.2   Mar 02 2000 10:54:38   DT24433
 * changes for new dispatcher base classes
 *
 *    Rev 1.1   Feb 29 2000 15:21:16   BUZILA
 * added Trading screen/process/CBO
 *
 *    Rev 1.0   Feb 15 2000 11:01:12   SMITHDAV
 * Initial revision.
 *
 *    Rev 1.70   Feb 07 2000 10:47:04   VASILEAD
 * Refresh fix
 *
 *    Rev 1.69   Feb 02 2000 18:10:00   BUZILA
 * changes
 *
 *    Rev 1.68   Feb 02 2000 16:03:18   VASILEAD
 * Moved PopulateAccountOwner at AccDetailsProcess
 *
 *    Rev 1.67   Feb 02 2000 11:10:54   BUZILA
 * enabling updates check on EndCall
 *
 *    Rev 1.66   Jan 30 2000 17:56:56   POPESCUS
 * SIT fixes
 *
 *    Rev 1.65   Jan 28 2000 17:49:24   POPESCUS
 * JERRY!!!! :-)) FIXED THE BIG CRASH AT THE END;
 *
 *    Rev 1.64   Jan 27 2000 14:13:30   VASILEAD
 * Fixes for final release
 *
 *    Rev 1.63   Jan 18 2000 16:36:08   HSUCHIN
 * changed launchAccountDetails's parameters
 *
 *    Rev 1.62   Jan 18 2000 09:16:00   HSUCHIN
 * minor fix
 *
 *    Rev 1.61   Jan 17 2000 15:22:06   YINGBAOL
 * hllapi change sync
 *
 *    Rev 1.60   Jan 17 2000 14:00:38   POPESCUS
 * support for refresh and misc
 *
 *    Rev 1.59   Jan 16 2000 17:01:02   POPESCUS
 * changes for the refresh of account details after a new shareholder is created
 *
 *    Rev 1.58   Jan 14 2000 14:44:16   HSUCHIN
 * end call flow
 *
 *    Rev 1.57   Dec 24 1999 10:29:58   VASILEAD
 * Fixed NASU flow
 *
 *    Rev 1.56   24 Dec 1999 08:25:00   HSUCHIN
 * end call now checks and warns user of uncommitted changes
 *
 *    Rev 1.55   Dec 23 1999 16:28:42   YINGBAOL
 * hllapi change sync
 *
 *    Rev 1.54   23 Dec 1999 15:53:02   HSUCHIN
 * End call no longer calls confirmation
 *
 *    Rev 1.53   Dec 01 1999 19:54:30   VASILEAD
 * Stuff
 *
 *    Rev 1.52   Dec 01 1999 12:27:34   POPESCUS
 * clean the work session before creating a new shareholder
 *
 *    Rev 1.51   Nov 28 1999 16:15:30   POPESCUS
 * fix
 *
 *    Rev 1.50   Nov 25 1999 10:37:36   HSUCHIN
 * end call for awd now calls confirm.
 *
 *    Rev 1.49   Nov 25 1999 10:08:52   HSUCHIN
 * bug fix
 *
 *    Rev 1.48   Nov 24 1999 19:05:40   HSUCHIN
 * end call now calls confirmation screen when there is awd work or there was maintanance done.
 *
 *    Rev 1.47   Nov 24 1999 10:09:40   POPESCUS
 *
 *    Rev 1.46   Nov 22 1999 10:32:30   ZHANGCEL
 * change WhereUsedDlg invoking type from modeless to modal
 *
 *    Rev 1.45   Nov 16 1999 17:39:54   ZHANGCEL
 * Modify bModal from "true" to "false" for invoking NewShareHolder
 *
 *    Rev 1.44   Nov 10 1999 13:46:26   VASILEAD
 * Changed USER_GLOBALS to WORK_GLOBALS
 *
 *    Rev 1.43   Nov 02 1999 16:42:56   HSUCHIN
 * Insync with C1 in AWD Integration
 *
 *    Rev 1.42   Oct 24 1999 11:18:02   POPESCUS
 * Added the remarks button to the main control screen
 *
 *    Rev 1.41   Oct 23 1999 14:56:48   POPESCUS
 * Took out an include
 *
 *    Rev 1.40   Oct 23 1999 12:01:40   POPESCUS
 *
 *    Rev 1.39   Oct 18 1999 11:58:24   BUZILA
 * Update transactions
 *
 *    Rev 1.38   Oct 18 1999 09:49:02   POPESCUS
 *
 *    Rev 1.37   Oct 14 1999 10:47:40   HSUCHIN
 * AWD now using Session Object.  There are still outstanding issues.
 *
 *    Rev 1.36   24 Sep 1999 16:34:12   HUANGSHA
 * Added search for Address Book
 *
 *    Rev 1.35   13 Sep 1999 13:52:52   HUANGSHA
 * Synchronize with M1's changes
 *
 *    Rev 1.34   Aug 27 1999 07:44:26   DT24433
 * added better error checking in OnBtnIdCaller
 *
 *    Rev 1.33   Aug 25 1999 13:41:30   PRAGERYA
 * Search for ShrInfo and AcctInfo partly implemented
 *
 *    Rev 1.32   Aug 19 1999 10:58:18   VASILEAD
 * Reset caller info after End call button was pressed
 *
 *    Rev 1.31   Aug 18 1999 14:02:58   PRAGERYA
 * New Shareholder button enabled
 *
 *    Rev 1.30   Aug 18 1999 12:22:48   PRAGERYA
 * Substitute lists in combo boxes
 *
 *    Rev 1.29   Aug 17 1999 17:38:48   DT24433
 * changed getFieldForCurrentListItem to getField
 *
 *    Rev 1.28   Aug 11 1999 14:05:52   DT24433
 * changes for unique substitute keys
 *
 *    Rev 1.27   Aug 11 1999 12:32:18   DT24433
 * substitutes changed key from index to host code
 *
 *    Rev 1.26   Aug 10 1999 15:25:50   HSUCHIN
 * Added Error message for Get work when AWD is logged off after search screen is loaded up.
 *
 *    Rev 1.25   Aug 10 1999 13:16:42   YINGZ
 * caller infor should only be entered if nobody has enter it
 *
 *    Rev 1.24   Aug 08 1999 14:50:40   VASILEAD
 * changed to allow proper refresh
 *
 *    Rev 1.23   Aug 06 1999 12:52:42   VASILEAD
 * ?
 *
 *    Rev 1.22   04 Aug 1999 11:16:16   HUANGSHA
 * Same as MFDSTC.h
 *
 *    Rev 1.21   Aug 03 1999 17:08:36   BUZILA
 * added ..
 *
 *    Rev 1.20   Jul 29 1999 19:07:20   HSUCHIN
 * Fixed AWD to use Databroker for Search Options
 *
 *    Rev 1.19   Jul 23 1999 15:40:26   POPESCUS
 * Fixed some conditins displaying
 *
 *    Rev 1.18   Jul 23 1999 10:23:04   POPESCUS
 * Using substiutes list for the combos
 *
 *    Rev 1.17   Jul 20 1999 14:23:54   YINGZ
 * add hour glass
 *
 *    Rev 1.16   Jul 20 1999 11:18:42   VASILEAD
 * New conditions update
 *
 *    Rev 1.15   Jul 19 1999 16:39:20   POPESCUS
 * Fixed security stuff
 *
 *    Rev 1.14   Jul 19 1999 11:51:58   POPESCUS
 * Fixed refresh of security access rights
 *
 *    Rev 1.13   Jul 16 1999 14:20:22   PRAGERYA
 * SysLoad
 *
 *    Rev 1.12   Jul 16 1999 12:31:48   POPESCUS
 * Added message to warn user before changing the management company
 *
 *    Rev 1.11   Jul 15 1999 17:10:20   POPESCUS
 *
 *    Rev 1.10   Jul 15 1999 16:09:26   HSUCHIN
 * bug fix with awd container
 *
 *    Rev 1.9   Jul 15 1999 12:51:32   POPESCUS
 * No change.
 *
 *    Rev 1.8   Jul 15 1999 12:30:42   POPESCUS
 * Added a string in the string table
 *
 *    Rev 1.7   Jul 13 1999 17:37:36   POPESCUS
 * Fixed combo subsitute list  for search
 *
 *    Rev 1.6   Jul 13 1999 17:23:12   HSUCHIN
 * small bug fix
 *
 *    Rev 1.5   Jul 12 1999 18:27:24   HSUCHIN
 * Fixed AWD namespace tags.
 *
 *    Rev 1.3   Jul 08 1999 17:32:58   POPESCUS
 * Fixed memory leaks related to the search stuff
 *
 *    Rev 1.2   Jul 08 1999 16:33:00   HSUCHIN
 * fixed mistyped namespace definition for AWD
*/



