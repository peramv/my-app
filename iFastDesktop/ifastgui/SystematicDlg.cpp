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
// ^FILE   : SystematicDlg.cpp
// ^AUTHOR : David Smith            Shaobo Huang for M2
// ^DATE   : March 11, 1999         Dec 24, 1999 
//
// ----------------------------------------------------------
//
// ^CLASS    : SystematicDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  
//
//******************************************************************************

#include "stdafx.h"

#ifndef ABSTRACTPROCESS_HPP
   #include <bfproc\AbstractProcess.hpp>
#endif

#ifndef ALLOCATIONSPROCESSINCLUDES_H
   #include <ifastbp\AllocationsProcessIncludes.h>
#endif

#ifndef DSTCFUNCS_H
   #include <uibase\DstcFuncs.h>
#endif

#ifndef DSTCOMBOBOX_H
   #include <uibase\DSTComboBox.h>
#endif

#ifndef DSTCOMMONFUNCTION_HPP
   #include <ifastcbo\DSTCommonFunction.hpp>
#endif

#ifndef DSTEDIT_H
   #include <uibase\DSTEdit.h>
#endif

#ifndef DSTLISTCTRL_H
   #include <uibase\DSTListCtrl.h>
#endif

#ifndef DSTSTATIC_H
   #include <uibase\DSTStatic.h>
#endif

#ifndef DSTCWORKSESSION_HPP
   #include <ifastcbo\DSTCWorkSession.hpp>
#endif

#ifndef MFCANINTERPROCPARAM_HPP
   #include <ifastbp\MFCANInterProcParam.hpp>
#endif

#ifndef IFASTGUI_H
   #include "MFDSTC.h"
#endif

#ifndef SPLITCOMMISSIONSPROCESSINCLUDES_H
   #include <ifastbp\SplitCommissionsProcessIncludes.h>
#endif

#include <ifastdataimpl\dse_substitute_vw.hpp>

#ifndef SYSTEMATICDLG_H
   #include "SystematicDlg.h"
#endif

#ifndef SYSTEMATICPROCESSINCLUDES_H
   #include <ifastbp\SystematicProcessIncludes.h>
#endif

#ifndef DSTGRIDWND_H
   #include <uibase\DSTGridWnd.h>
#endif

#ifndef IDENTIFYACCOUNTSPROCESSINCLUDES_HPP
   #include <ifastbp\IdentAccProcessIncludes.h>
#endif

#include <ifastcbo\mfaccount.hpp>
#include <ifastcbo\BrokerList.hpp>
#include <ifastcbo\Broker.hpp>
#include <ifastcbo\financialinstitution.hpp>

//HllApi
#include <ifastcsi\CsiSession.h>
#include <ifastcsi\ifastcsi.h>

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_BANK_INSTRUCTIONS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ALLOCATIONS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ADMINDATES;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ADDRESSES;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FUNDCLASS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_SPLITCOMMISSION;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_SYS_INDEX;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_IDENT_ACC;
extern CLASS_IMPORT const I_CHAR* CMD_GUI_SYSTEMATIC;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_DEMOGRAPHICS;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< SystematicDlg > dlgCreator( CMD_GUI_SYSTEMATIC );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   // trace literals
   const I_CHAR * const CLASSNAME         = I_( "SystematicDlg" );

   const I_CHAR *LV_SYSTEMATICS           = I_( "SystematicsList" ); 
   const I_CHAR *LV_SYSALLOCATION         = I_( "SysAllocationList" ); 

   const I_CHAR * const LV_SYSTEMATIC     = I_( "List View Systematic" );
   const I_CHAR * const LV_ALLOCATION     = I_( "List View SysAllocation" );
   const I_CHAR * const LV_AT_ALLOCATION  = I_("List View ATAllocation");
   const I_CHAR * const LV_AT_ACCT_ALLOCATION  = I_("List View AtAcctAllocation");


   const I_CHAR * const SEP_SLASH         = I_( "/" );  
   const I_CHAR * const SEP_HYPHEN        = I_( "-" );  

   const I_CHAR * const TRANS_TYPE_SAVING_PLAN       = I_( "V" );

   const I_CHAR * const YES               = I_( "Y" );
   const I_CHAR * const NO                = I_( "N" );

   const I_CHAR * const GROSS             = I_( "Gross" );
   const I_CHAR * const NET               = I_( "Net" );

   const I_CHAR * const STATUS_GOOD       = I_( "Good" );
   const I_CHAR * const STATUS_BAD        = I_( "Bad" );

   const I_CHAR * const INDICATOR_MONTHLY    = I_( "YYYYYYYYYYYY" );
   const I_CHAR * const INDICATOR_QUARTERLY  = I_( "YNNYNNYNNYNN" );
   const I_CHAR * const INDICATOR_QUARTERLY1 = I_( "NYNNYNNYNNYN" );
   const I_CHAR * const INDICATOR_QUARTERLY2 = I_( "NNYNNYNNYNNY" );
   const I_CHAR * const INDICATOR_ANNUALLY   = I_( "YNNNNNNNNNNN" );
   const I_CHAR * const INDICATOR_SEMIANNUALLY   = I_( "YNNNNNYNNNNN" );

   const I_CHAR * const INDICATOR_OTHER      = I_( "NNNNNNNNNNNN" );

   const I_CHAR * const FREQ_DAILY        = I_( "0" );
   const I_CHAR * const FREQ_WEEKLY       = I_( "1" );
   const I_CHAR * const FREQ_BIWEEKLY     = I_( "2" );
   const I_CHAR * const FREQ_MONTHLY      = I_( "3" );
   const I_CHAR * const FREQ_SEMIMONTHLY  = I_( "4" );
   const I_CHAR * const FREQ_QUARTERLY    = I_( "5" );
   const I_CHAR * const FREQ_SEMIANNUALLY = I_( "6" );
   const I_CHAR * const FREQ_ANNUALLY     = I_( "7" );
   const I_CHAR * const FREQ_OTHER        = I_( "8" );

   const I_CHAR * const ACCOUNT_NUM       = I_( "AccountNum" );
   const I_CHAR * const SHAREHOLDER_NUM = I_( "ShareholderNum" );
   const I_CHAR * const ENTITY_ID         = I_( "EntityID" );
   const I_CHAR * const ADDRESS_CODE      = I_( "AddressCode" );
   const I_CHAR * const SYSTEMATIC_KEY    = I_( "SystKey" );
   const I_CHAR * const DEFAULT_YN        = I_( "DefaultYN" );
   const I_CHAR * const PROC_TRANS_CODE   = I_( "TransCode" );
   const I_CHAR * const LIST_KEY          = I_( "ListKey" );

   const I_CHAR *MODUSER                  = I_( "ModUser" );
   const I_CHAR *MODDATE                  = I_( "ModDate" );
   const I_CHAR *PROCESSUSER              = I_( "Username" );
   const I_CHAR *PROCESSDATE              = I_( "ProcessDate" );

   const I_CHAR * const BANK_INSTRUCTION_TYPE= I_( "BankInstrType" );
   const I_CHAR * const SYSTEMATIC           = I_( "Systematic" );

   const I_CHAR * const COL_ACTIVE           = I_( "StatusCode" );
   const I_CHAR * const COL_FREQUENCY        = I_( "Frequency" );   
   const I_CHAR * const COL_PAYTYPE          = I_( "PayType" );

   const I_CHAR * const COL_FUND             = I_( "FundCode" );
   const I_CHAR * const COL_CLASS            = I_( "ClassCode" );
   const I_CHAR * const COL_PERCENT          = I_( "Percentage" );
   const I_CHAR * const COL_ALLOCAMOUNT      = I_( "AllocAmount" );
   const I_CHAR * const FUND_NUMBER          = I_( "Baycom" );
   const I_CHAR * const FUNDNUMBER        = I_( "FundNumber" );

   const I_CHAR * const AT_COL_FUND          = I_( "Fund" );
   const I_CHAR * const AT_COL_CLASS         = I_( "Class" );
   const I_CHAR * const AT_COL_PERCENT       = I_( "Percent" );
   const I_CHAR * const AT_ACCT_COL_ACCOUNT  = I_("Accounts");
   const I_CHAR * const AT_ACCT_COL_PERCENTAGE  = I_("Percentage");

   const I_CHAR * const AT_COL_UNITS         = I_( "Units" );

   const UINT  POP_TOOL_TIP             = WM_USER + 100;
   //const UINT  POP_DEMOGRAPHIC            = WM_USER + 101;
   const I_CHAR * const FUND_CODE            = I_( "FundCode" );
   const I_CHAR * const CLASS_CODE           = I_( "ClassCode" );
   const I_CHAR * const SHR_NUM              = I_( "ShrNum" );

   const I_CHAR * const CODE_BANKIDTYPE_ABA   = I_( "01" );
   const I_CHAR * const CODE_BANKIDTYPE_CANADA  = I_( "03" );
   const I_CHAR * const CODE_BANKIDTYPE_SWIFT = I_( "04" );
   const I_CHAR * const CODE_BANKIDTYPE_JAPAN = I_( "06" );
   const I_CHAR * const GRID_NAME             = I_( "OptionGrid" );
   const I_CHAR * const CALLER                = I_( "Caller" );
   const I_CHAR * const WORK_TYPE             = I_( "WORKTYPE" );
   const I_CHAR * const PAC                   = I_( "PAC" );
   const I_CHAR * const SWP                   = I_( "SWP" );

}                                         

namespace SYS_GRID 
{
   const I_CHAR * const SRC_OF_FUND  = I_("SrcOfFund");
   const I_CHAR * const GROSSNET  = I_("GrossOrNet");
   const I_CHAR * const FLAT_PERCENT  = I_("FlatPercent");
   const I_CHAR * const SPLIT_COMM  = I_("SplitComm");
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId AtFrequency;
   extern CLASS_IMPORT const BFTextFieldId FrFundNumber;
   extern CLASS_IMPORT const BFTextFieldId ToFundNumber;
   extern CLASS_IMPORT const BFTextFieldId SystematicPayType;
   extern CLASS_IMPORT const BFTextFieldId SystematicGridHeading;
   extern CLASS_IMPORT const BFTextFieldId SystematicGridLeftHeading;
   extern CLASS_IMPORT const BFTextFieldId SystematicGridLeftHeadingAT;
   extern CLASS_IMPORT const BFTextFieldId SystematicGridLeftHeadingSavingPlan;
   extern CLASS_IMPORT const BFTextFieldId VUBFee;
   extern CLASS_IMPORT const BFTextFieldId RxPlanCode;
   extern CLASS_IMPORT const BFTextFieldId BankInformation;
   extern CLASS_IMPORT const BFTextFieldId KYCAccountLevel;   
   extern CLASS_IMPORT const BFTextFieldId KYCRequired;	
   extern CLASS_IMPORT const BFTextFieldId FundAlloc;
   extern CLASS_IMPORT const BFTextFieldId RDRAdvice;
   extern CLASS_IMPORT const BFTextFieldId UCITFlag;
   extern CLASS_IMPORT const BFTextFieldId SystematicGridLeftHeadingCustomPayout;
   extern CLASS_IMPORT const BFTextFieldId SystematicGridLeftHeadingPortfolioPayout;
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const BANKING_INSTRUCTION;
   extern CLASS_IMPORT I_CHAR * const DEFAULT_ALLOCATION;
   extern CLASS_IMPORT I_CHAR * const ADDRESS_BOOK;
   extern CLASS_IMPORT I_CHAR * const SAVING_PLAN;
   extern CLASS_IMPORT I_CHAR * const PAC;
   extern CLASS_IMPORT I_CHAR * const SWP;
   extern CLASS_IMPORT I_CHAR * const AUTOMATIC_TRANSFER;
   extern CLASS_IMPORT I_CHAR * const SWP_TAX_OVERRIDE;
}

namespace BANKTYPE
{
   extern CLASS_IMPORT I_CHAR * const SYSTEMATIC;
}

namespace SYSTEMATICLIT
{
   const I_CHAR * const TRANS_TYPE = I_( "TransactionType" );
   const I_CHAR * const MULTI_ALLOCATION = I_( "FromMultiallocation" );

}

namespace TRADETYPE
{
   extern CLASS_IMPORT I_CHAR * const AUTO_TRANSFER;
   extern CLASS_IMPORT I_CHAR * const PAC;
   extern CLASS_IMPORT I_CHAR * const SWP;
}

namespace REG_AGENT_TAX_TYPE
{
	const I_CHAR * const ORD_ACC = I_("OA"); 
	const I_CHAR * const SPL_ACC = I_("SA");
	const I_CHAR * const SRS_ACC = I_("SR"); 
}

namespace AMT_TYPE
{
	extern CLASS_IMPORT I_CHAR * const CUSTOM;
	extern CLASS_IMPORT I_CHAR * const PORTFOLIO;
}

//******************************************************************************

SystematicDlg::SystematicDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( SystematicDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
, m_bInvAdvice( false )
, m_bEsc(false)
, m_uiDialogItem( 0 )
, m_idOldGridSubstitution( ifds::NullFieldId ) 
, openeditemkeys(NULL_STRING)
{
   //{{AFX_DATA_INIT(SystematicDlg)
   //}}AFX_DATA_INIT
   m_bSystematicItemChanging     = false;
   m_bSystematicItemChange       = false;
   m_bAllocationItemChange       = false;
   m_bBtnAllocation              = false;
   m_bNewItem                    = false;
   m_bSetMonthlyInd              = false;
//   m_bFeeLostFocus               = false;
   m_bAddCopy              = false;
   m_bScreenClose                = false;
   m_bConfirmFee                 = false;
   m_bTransTypeChange            = false;

   m_dstrEntityID                = NULL_STRING;
   m_dstrAccountNum              = NULL_STRING;

   m_dstrCurKey                  = NULL_STRING;

   m_pFont                       = NULL;
}

//******************************************************************************

void SystematicDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(SystematicDlg)
   DDX_Control(pDX, IDC_CHK_ONLY_ACTIVE, m_ckbActiveOnly);
   //}}AFX_DATA_MAP
}

//******************************************************************************

BEGIN_MESSAGE_MAP(SystematicDlg, BaseMainDlg)
//{{AFX_MSG_MAP(SystematicDlg)
ON_BN_CLICKED(IDC_BTN_BANK, OnBtnBank)
ON_BN_CLICKED(IDC_BTN_ALLOCATION, OnBtnAllocation)
ON_BN_CLICKED(IDC_BTN_ADM_DATES, OnBtnAdmDates)
ON_BN_CLICKED(IDC_BTN_NEW, OnBtnNew)
ON_BN_CLICKED(IDC_BTN_DELETE, OnBtnDelete)  
ON_BN_CLICKED(IDC_BTN_ADDRESS, OnBtnAddress)
ON_BN_CLICKED(IDC_BTN_RESET, OnBtnReset)
ON_BN_CLICKED(IDC_BTN_ADD_COPY, OnBtnAddCopy)
ON_NOTIFY(LVN_ITEMCHANGING, IDC_LV_SYSTEMATIC, OnItemchangingLvSystematic)
ON_WM_CLOSE()
ON_BN_CLICKED(IDC_BTN_SPLIT_COM, OnBtnSplitCom)
ON_BN_CLICKED(IDC_BTN_INDEXING, OnBtnIndexing)
ON_MESSAGE(POP_TOOL_TIP, ShowAcctList)
//ON_MESSAGE(POP_DEMOGRAPHIC, OpenDemographicDlg)
ON_MESSAGE( UM_OPENFUNDCLASSLISTDLG, OpenFundClassListDlg )
ON_MESSAGE( WM_LAUNCH_IDENT_ACC, OpenIdentifyAccountsDlg ) 
ON_EN_KILLFOCUS(IDC_EDT_MONTHLY, OnKillfocusEdtMonthly)
ON_CBN_KILLFOCUS(IDC_CMB_PAYTYPE, OnKillfocusCmbPayType)

ON_BN_CLICKED( IDC_BTN_HISTORICAL, OnBtnHistorical)
ON_BN_CLICKED (IDC_CHK_ONLY_ACTIVE, OnChkActiveOnly)

//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//******************************************************************************

SEVERITY SystematicDlg::doInit()
{
   SEVERITY sevRtn = SEVERE_ERROR;

   getParent()->getField(this, ifds::AccountNum, m_dstrAccountNum);
   m_dstrAccountNum.strip();
   m_lContainerID = IFASTBP_PROC::SYSTEMATIC_LIST;

   getParameter( CALLER, m_dstrCaller );
   getParameter( WORK_TYPE, m_dstrWorkType );

   sevRtn = NO_CONDITION;
   return(sevRtn);
}

//******************************************************************************

BOOL SystematicDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );
   
   BaseMainDlg::OnInitDialog();   
   return(TRUE);  // return TRUE unless you set the focus to a control
   // EXCEPTION: OCX Property Pages should return FALSE
}

//******************************************************************************
void SystematicDlg::SetUserAccesFuncCode(bool bUseParam /*= false*/)
{
   DString dstrTransType;
   if( bUseParam )
      getParent()->getField(this, SYSTEMATICLIT::TRANS_TYPE_PARAM, dstrTransType, false);
   else
      getParent()->getField(this, m_lContainerID, ifds::TransType, dstrTransType, false);
   if( dstrTransType == TRADETYPE::PAC )
      SetUserAccesFunctionCode(UAF::PAC);
   else if( dstrTransType == TRADETYPE::SWP )
      SetUserAccesFunctionCode(UAF::SWP);
   else if( dstrTransType == TRADETYPE::AUTO_TRANSFER )
      SetUserAccesFunctionCode(UAF::AUTOMATIC_TRANSFER);
   else if( dstrTransType == TRANS_TYPE_SAVING_PLAN )
      SetUserAccesFunctionCode(UAF::SAVING_PLAN);
}

//******************************************************************************
void SystematicDlg::OnPostInitDialog()
{

   SetAccount(m_dstrAccountNum);
   //SetAccountCaption();

   DString dstrShrNum, dstrEntityName;
   getParent()->getField( this, ifds::ShrNum,    dstrShrNum );
   getParent()->getField( this, SYSTEMATICLIT::PRIMARY_ACCOUNT_OWNER, dstrEntityName );
   SetShrAcctCaption(dstrShrNum, m_dstrAccountNum, dstrEntityName);

   addBtnAddForPermissionCheck(IDC_BTN_ADD_COPY, IDC_LV_SYSTEMATIC);
   addBtnAddForPermissionCheck(IDC_BTN_NEW, IDC_LV_SYSTEMATIC);
   addBtnDeleteForPermissionCheck(IDC_BTN_DELETE, IDC_LV_SYSTEMATIC);

   SetUserAccesFuncCode(true);   
   //Add all controls on the screen to the container
   addControls();

   // Set InvAdvice flag; determines whether Allocation is allowed
   DString dstrTemp;
   dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getOption ( ifds::InvAdvice, dstrTemp, BF::HOST, false);
   m_bInvAdvice = ( dstrTemp == YES );
   if( !m_bInvAdvice )
   {
      GetDlgItem( IDC_BTN_ALLOCATION )->EnableWindow( false );
   }

   //populate the systematic data
   populateData();  

   DSTListCtrl *rpList = GetList (IDC_LV_SYSTEMATIC);

   bool bIsDummy = getParentProcess()->isCurrentListItemDummy( this, rpList->getContainerId() );

   if (hasCreatePermission(GetUserAccesFunctionCode()) && 
	   m_dstrCaller == I_("FromAWD") && 
	   !bIsDummy && 
	   (m_dstrWorkType == PAC || m_dstrWorkType == SWP))
   {
	   OnBtnNew ();
   }

}

//******************************************************************************
void SystematicDlg::addControls() 
{
   //ListCtrl
   AddListControl(CLASSNAME, IDC_LV_SYSTEMATIC, LV_SYSTEMATIC, ifds::SystematicListHeading, m_lContainerID);
//   AddListControl(CLASSNAME, IDC_LV_ALLOCATION, LV_ALLOCATION, DBR::SysAllocListHeading, SYSALLOCATION_LIST, IDC_LV_SYSTEMATIC);
   //  AddListControl(CLASSNAME, IDC_LV_ALLOCATION, LV_ALLOCATION, DBR::SysAllocListHeading, SYSALLOCATION_LIST, 0, true, LISTFLAG_NOT_AUTO_ADD);
   AddListControl(CLASSNAME, IDC_LV_ALLOCATION, LV_ALLOCATION, ifds::NullFieldId, BF::NullContainerId, IDC_LV_SYSTEMATIC, true, LISTFLAG_NOT_AUTO_ADD);

   AddListControl(CLASSNAME, IDC_TXT_AT_ACCT_LIST, LV_AT_ACCT_ALLOCATION, ifds::LV_AtAcctAllocationHeading, 
                  IFASTBP_PROC::AT_ACCOUNT_ALLOCATIONLIST);

   //PayType    CTRLFLAG_FIELDS_FROM_SUB_LIST
   AddControl(CTRL_COMBO, IDC_CMB_PAYTYPE, m_lContainerID, ifds::SystematicPayType, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_SYSTEMATIC);
   //Fund & Class
/*
  AddControl(CTRL_COMBO, IDC_CMB_FUND,  m_lContainerID, DBR::FundCode, CTRLFLAG_MANUAL_INIT, IDC_LV_SYSTEMATIC);
  AddControl(CTRL_COMBO, IDC_CMB_CLASS, m_lContainerID, DBR::ClassCode, CTRLFLAG_MANUAL_INIT, IDC_LV_SYSTEMATIC);
*/
   AddControl(CTRL_EDIT, IDC_EDT_FUND,  m_lContainerID, ifds::FundCode, 0, IDC_LV_SYSTEMATIC);
   AddControl(CTRL_EDIT, IDC_EDT_CLASS, m_lContainerID, ifds::ClassCode, 0, IDC_LV_SYSTEMATIC);
   //Amount
   AddControl(CTRL_EDIT,  IDC_EDT_AMOUNT, m_lContainerID, ifds::Amount, 0, IDC_LV_SYSTEMATIC);
   dynamic_cast< DSTEdit * >( GetControl( IDC_EDT_AMOUNT ) )->SetAllowedChars( I_(".0123456789") );
   //Temp bug fix.  This should be handled by the infra.
   dynamic_cast<DSTEdit *>(GetControl(IDC_EDT_AMOUNT))->SetMaxCharNum( 12 );
   //Frequency
   AddControl(CTRL_COMBO, IDC_CMB_FREQ, m_lContainerID, ifds::Frequency, CTRLFLAG_INITCOMBO_BY_SUB_LIST | CTRLFLAG_AUTO_UPDATE_ON_CHANGE, IDC_LV_SYSTEMATIC );   

//   AddControl(CTRL_COMBO, IDC_CMB_FREQ, m_lContainerID, DBR::Frequency, CTRLFLAG_INITCOMBO_BY_SUB_LIST | CTRLFLAG_GUI_FIELD, IDC_LV_SYSTEMATIC ); 	
   // day of week
   AddControl(CTRL_COMBO, IDC_CMB_DAY_OF_WEEK, m_lContainerID, ifds::DayOfWeek, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_SYSTEMATIC);


   //Amount Type
   AddControl(CTRL_COMBO, IDC_CMB_TYPE, m_lContainerID, ifds::AmountType, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_SYSTEMATIC);

   //Effective Date
   AddControl(CTRL_DATE,  IDC_DTP_EFFECTIVE_DATE, m_lContainerID, ifds::EffectiveDate, 0, IDC_LV_SYSTEMATIC);

   //Stop Date
   AddControl(CTRL_DATE,  IDC_DTP_STOP_DATE, m_lContainerID, ifds::StopDate, 0, IDC_LV_SYSTEMATIC);

   AddControl(CTRL_COMBO, IDC_CMB_PLAN, m_lContainerID, ifds::PlanCode, CTRLFLAG_MANUAL_INIT, IDC_LV_SYSTEMATIC);

   //EOM
   AddControl(CTRL_COMBO, IDC_CMB_EOM, m_lContainerID, ifds::EndOfMonth, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_SYSTEMATIC);
   //Monthly
   AddControl(CTRL_EDIT, IDC_EDT_MONTHLY, m_lContainerID,  ifds::MonthIndicator, CTRLFLAG_AUTO_UPDATE_ON_CHANGE, IDC_LV_SYSTEMATIC);
   //((DSTEdit *)(GetDlgItem(IDC_EDT_MONTHLY)))->SetMaxCharNum(12);
   CString strYN("YNyn");
   ((DSTEdit *)(GetDlgItem(IDC_EDT_MONTHLY)))->SetAllowedChars(strYN);

   //Last Processed Date
   AddControl(CTRL_STATIC, IDC_TXT_LAST_PROCESSED, m_lContainerID, ifds::LastProcessDate, 0, IDC_LV_SYSTEMATIC);
   AddControl(CTRL_STATIC, IDC_TXT_NEXT_PROCESS, m_lContainerID, ifds::NextProcessDate, 0, IDC_LV_SYSTEMATIC);

   /**
    * From Bank information
    */
   AddControl(CTRL_STATIC, IDC_TXT_BANK_NAME,   m_lContainerID, ifds::InstName,      0, IDC_LV_SYSTEMATIC);
   AddControl(CTRL_STATIC, IDC_TXT_ACC_NAME,    m_lContainerID, ifds::BankAcctName,  0, IDC_LV_SYSTEMATIC);
   //Account Number and Acct Type
   AddControl(CTRL_EDIT, IDC_EDT_ACC_NBR, m_lContainerID, ifds::BankInformation, 0, /*CTRLFLAG_MANUAL_INIT,*/ IDC_LV_SYSTEMATIC);
   AddControl(CTRL_STATIC, IDC_TXT_TRANS_NUMBER, m_lContainerID, ifds::TransitNo, 0, IDC_LV_SYSTEMATIC);
   AddControl(CTRL_STATIC, IDC_TXT_INST_CODE,    m_lContainerID, ifds::BankIdValue, 0, IDC_LV_SYSTEMATIC);

   /**
    * To Address information
    */
   AddControl(CTRL_COMBO, IDC_CMB_ADDRESS_CODE, m_lContainerID, ifds::AddrCode,  CTRLFLAG_MANUAL_INIT, IDC_LV_SYSTEMATIC);
   AddControl(CTRL_EDIT, IDC_EDT_ADDRESS,       m_lContainerID, ifds::AddrLine1, CTRLFLAG_MANUAL_INIT, IDC_LV_SYSTEMATIC);

   /**
    * To Fund information
    */
/**  
   //Fund & Class
  AddControl(CTRL_COMBO, IDC_CMB_TO_FUND,      m_lContainerID, DBR::FundToCode, CTRLFLAG_MANUAL_LOAD | CTRLFLAG_MANUAL_INIT, IDC_LV_SYSTEMATIC);
  AddControl(CTRL_COMBO, IDC_CMB_TO_CLASS,     m_lContainerID, DBR::ClassToCode, CTRLFLAG_MANUAL_LOAD | CTRLFLAG_MANUAL_INIT, IDC_LV_SYSTEMATIC);
  AddControl(CTRL_EDIT, IDC_TXT_ACC_NBR,    m_lContainerID, DBR::BankAcctNum, 0, IDC_LV_SYSTEMATIC);
   //Batch and Trace number
   AddControl(CTRL_STATIC, IDC_TXT_TO_BATCH,       m_lContainerID, DBR::Batch, CTRLFLAG_MANUAL_LOAD | CTRLFLAG_MANUAL_INIT, 0, IDC_LV_SYSTEMATIC);
   AddControl(CTRL_STATIC, IDC_TXT_TO_TRANS_TYPE,  m_lContainerID, DBR::TransferType, CTRLFLAG_MANUAL_LOAD | CTRLFLAG_MANUAL_INIT, IDC_LV_SYSTEMATIC);
*/

//Automatic Transfer
   DString strMarket = DSTCommonFunctions::getMarket();

   AddControl(CTRL_DATE, IDC_AT_DTP_FIRST_TRANS,  m_lContainerID, ifds::EffectiveDate, 0, IDC_LV_SYSTEMATIC);

   AddControl(CTRL_DATE, IDC_AT_DTP_STOP,  m_lContainerID, ifds::StopDate, 0, IDC_LV_SYSTEMATIC);
   AddControl(CTRL_EDIT, IDC_EDT_AT_FUND,  m_lContainerID, ifds::FundToCode, 0, IDC_LV_SYSTEMATIC);
   AddControl(CTRL_EDIT, IDC_EDT_AT_CLASS,  m_lContainerID, ifds::ClassToCode, 0, IDC_LV_SYSTEMATIC);
   if( strMarket == MARKET_IDS::JAPAN )
   {
      AddControl(CTRL_COMBO, IDC_CMB_AT_ACCT_TO,  m_lContainerID, ifds::AccountTo, CTRLFLAG_MANUAL_INIT, IDC_LV_SYSTEMATIC);    
   }
   else
   {
      AddControl(CTRL_EDIT, IDC_EDT_AT_ACCT_TO,  m_lContainerID, ifds::AccountTo, 0, IDC_LV_SYSTEMATIC);

   }
   AddControl(CTRL_STATIC, IDC_TXT_AT_NAME,  BF::NullContainerId, ifds::Name, 0, IDC_LV_SYSTEMATIC);
   AddControl(CTRL_STATIC, IDC_EDT_AT_TRANS_TYPE,  BF::NullContainerId, SYSTEMATICLIT::TRANSACTION_TYPE, 0, IDC_LV_SYSTEMATIC);

   if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
   {
      AddControl(CTRL_EDIT, IDC_EDT_FROM_FUND,       m_lContainerID, ifds::FrFundNumber, 0, IDC_LV_SYSTEMATIC);
      AddControl(CTRL_EDIT, IDC_EDT_TO_FUND,       m_lContainerID, ifds::ToFundNumber, 0, IDC_LV_SYSTEMATIC);
   }
   else if( strMarket == MARKET_IDS::JAPAN )
   {
      GetDlgItem( IDC_EDT_FROM_FUND )->ShowWindow( SW_HIDE );
      GetDlgItem( IDC_EDT_TO_FUND )->ShowWindow( SW_HIDE );
   }

   m_idOldGridSubstitution = ifds::NullFieldId;
   AddGrid( CLASSNAME, IDC_GRID_OPTION, GRID_NAME, m_lContainerID, IDC_LV_SYSTEMATIC ); // init later 


   //Alignment of the monthly AIP,SWP
   m_pFont = new CFont();
   if( m_pFont )
   {
      CString strFaceName("Courier");
      m_pFont->CreatePointFont(10, strFaceName);
      GetDlgItem(IDC_LBL_UP_MONTHLY)->SetFont(m_pFont);
      GetDlgItem(IDC_EDT_MONTHLY)->SetFont(m_pFont);
   }

   DString dstrTaxType;
   getParent()->getField(this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::TaxType, dstrTaxType, false);
   dstrTaxType.strip();

   //int bShowRefNum = dstrTaxType == REG_AGENT_TAX_TYPE::ORD_ACC || 
   //                  dstrTaxType == REG_AGENT_TAX_TYPE::SPL_ACC || 
   //                  dstrTaxType == REG_AGENT_TAX_TYPE::SRS_ACC ? SW_SHOW : SW_HIDE;

   GetDlgItem( IDC_TXT_SYSTEMATIC_REF_NUM )->ShowWindow( SW_SHOW );
   GetDlgItem( IDC_EDT_SYSTEMATIC_REFNUM )->ShowWindow( SW_SHOW );

   //if(bShowRefNum)
   //{
      AddControl(CTRL_EDIT, IDC_EDT_SYSTEMATIC_REFNUM, m_lContainerID, ifds::TransNum, 0, IDC_LV_SYSTEMATIC);
//   }

   ConnectControlsToData();
}

//******************************************************************************

void SystematicDlg::populateData()
{
   LoadListControl(IDC_LV_SYSTEMATIC);

   DSTListCtrl* pListCtrl = GetList(IDC_LV_SYSTEMATIC);
   getParent()->getField(this, SYSTEMATICLIT::LISTKEY, m_dstrCurKey);
   m_dstrCurKey.strip();
   if( m_dstrCurKey.empty() )
   {
      DString dstrTransTypeParam, dstrTransType;
      getParent()->getField(this, SYSTEMATICLIT::TRANS_TYPE_PARAM, dstrTransTypeParam);
      dstrTransTypeParam.strip();
      if( !dstrTransTypeParam.empty() )
      {
         const DString *pKey = &getParent()->getFirstListItemKey(this, m_lContainerID);
         do
         {
            getParent()->getField(this, m_lContainerID, ifds::TransType, dstrTransType, false);
            if( dstrTransType.strip() == dstrTransTypeParam )
            {
               m_dstrCurKey = *pKey;
               break;
            }
         }
         while( *(pKey = &(getParent()->getNextListItemKey(this, m_lContainerID))) != NULL_STRING );
      }
   }
   pListCtrl->SetSelection(&m_dstrCurKey);
   enableDisableAllocation();

}


//******************************************************************************

void SystematicDlg::populateAllocations()
{
   DString dstrTransType, dstrAccountTo;

   getParent()->getField(this, m_lContainerID, ifds::TransType, dstrTransType, false);
   dstrTransType.strip().upperCase();

   if( dstrTransType == TRADETYPE::AUTO_TRANSFER )
   {
      if( getParent()->getNumberOfItemsInList(this, IFASTBP_PROC::AT_ACCOUNT_ALLOCATIONLIST) > 0 )
      {
         ReInitListControl(IDC_LV_ALLOCATION,ifds::ATAllocationListHeading,IFASTBP_PROC::AT_FUND_ALLOCATIONLIST,  LV_AT_ALLOCATION);
         if( getParent()->getNumberOfItemsInList(this, IFASTBP_PROC::AT_FUND_ALLOCATIONLIST) > 0 )
         {
            LoadListControl(IDC_LV_ALLOCATION);
            switchAllocAmountTypeColumn();
            getParent()->getField ( this, IFASTBP_PROC::AT_ACCOUNT_ALLOCATIONLIST, ifds::AllocAccountNum, dstrAccountTo );
         }
      }
      else
      {
         ConnectListToData(IDC_LV_ALLOCATION, false);  
         getParent()->getField(this, IFASTBP_PROC::SYSTEMATIC_LIST, ifds::AccountTo, dstrAccountTo );
      }
   }
   else
   {
      ReInitListControl(IDC_LV_ALLOCATION, ifds::SysAllocListHeading, IFASTBP_PROC::SYSALLOCATION_LIST, LV_ALLOCATION);
      if( getParent()->getNumberOfItemsInList(this, IFASTBP_PROC::SYSALLOCATION_LIST) > 0 )
      {
         LoadListControl(IDC_LV_ALLOCATION);       
         switchAllocAmountTypeColumn();
      }
   }

   DString dstrSplitComm(NULL_STRING);

   getParent()->getField(this, IFASTBP_PROC::SYSTEMATIC_LIST, ifds::SplitComm, dstrSplitComm, false);   
   if(dstrTransType != TRADETYPE::AUTO_TRANSFER)
   {
      (CWnd *)GetDlgItem(IDC_BTN_SPLIT_COM)->EnableWindow(dstrSplitComm == YES);
   }
   else
   {
      dstrAccountTo.strip();
      (CWnd *)GetDlgItem(IDC_BTN_SPLIT_COM)->EnableWindow(dstrSplitComm == YES && 
         dstrAccountTo != I_("") && dstrAccountTo != I_("0"));
   }
}

//******************************************************************************

void SystematicDlg::InitControl(UINT controlID)
{
   switch( controlID )
   {
      case IDC_CMB_ADDRESS_CODE:
         fillAddressCode();
         break;
      case IDC_CMB_PLAN:
         fillPlanCode();
         break;
      case IDC_CMB_AT_ACCT_TO:
         initAcctToCombo(IDC_CMB_AT_ACCT_TO);
         break;
   }
}

//******************************************************************************

void SystematicDlg::initAcctToCombo(UINT iControlID)
{
   DSTComboBox *pCmbAcctTax = dynamic_cast< DSTComboBox * >( GetDlgItem( iControlID ) );

   const DString *pKey = &(getParent()->getFirstListItemKey(this, IFASTBP_PROC::ACCOUNT_LIST));
   while( *pKey != NULL_STRING )
   {
      DString dstrAccountNum, dstr;
      getParent()->getField( this, IFASTBP_PROC::ACCOUNT_LIST, ifds::AllocAccountNum, dstrAccountNum,false );

      dstrAccountNum.strip().stripLeading( I_CHAR( '0' ) );
//		getParent()->getField( this, ALLOCATIONSPROC::MFACCOUNT_LIST, DBR::TaxType, dstr );
//		dstr.strip();
      dstr = dstrAccountNum;
      if( pCmbAcctTax->FindString( -1, dstr.c_str() ) == CB_ERR )
         int iIdx = pCmbAcctTax->AddString( dstr.c_str() );

      pKey = &(getParent()->getNextListItemKey(this, IFASTBP_PROC::ACCOUNT_LIST));
   }
}

//******************************************************************************

bool SystematicDlg::isATTransfer() const
{
   DString  dstrPayTypeDesc,dstrPayType,dstrTransType;
   getPayType(dstrTransType);

   return(dstrTransType == TRADETYPE::AUTO_TRANSFER);
}

//******************************************************************************

void SystematicDlg::ControlUpdated(UINT controlID, const DString &dstrValue)
{
   if( m_bAddCopy ) return;

   DString dstrTransType;

   switch( controlID )
   {
      case IDC_CMB_PAYTYPE:
         {
            showPayType();
            if( m_bTransTypeChange && !m_bSystematicItemChange )
			{
               RefreshListItem(IDC_LV_SYSTEMATIC);			   
			}
            m_bTransTypeChange = false;		
         }
         break;
      case IDC_EDT_AT_ACCT_TO:
         LoadControl(IDC_TXT_AT_NAME);
      case IDC_EDT_AT_FUND:		  
      case IDC_EDT_AT_CLASS:
      case IDC_CMB_AT_ACCT_TO:
      case IDC_EDT_TO_FUND:
         {
            GetControl (controlID)->LoadErrorState ();
            if( isATTransfer() && !m_bSystematicItemChange && !m_bBtnAllocation )
               populateAllocations();
            break;
         }

      case IDC_EDT_FUND:
      case IDC_EDT_CLASS:
      case IDC_EDT_FROM_FUND:
         getParent()->getField(this, m_lContainerID, ifds::TransType, dstrTransType, false);
         enableDisableAllocation();
         reinitGrid(dstrTransType);

         if( !m_bSystematicItemChange && !m_bBtnAllocation && !isATTransfer() )
            populateAllocations();
         break;

      case IDC_CMB_FREQ:
         {
            switchFrequency(dstrValue);
/**
      if(isATTransfer() && (dstrValue == FREQ_WEEKLY || dstrValue == FREQ_BIWEEKLY ) )
      {
        ShowMonthOrWeek(false);				 				
      }
      else
         {
        ShowMonthOrWeek(true);

        if (!m_bSetMonthlyInd)
        {
          bool bEnable = true;
          DString dstrTemp;
          if (!m_bSystematicItemChange)
          {
            if (dstrValue == FREQ_MONTHLY)
              dstrTemp =INDICATOR_MONTHLY;
            else if (dstrValue == FREQ_QUARTERLY )
              dstrTemp = INDICATOR_QUARTERLY;
            else if (dstrValue == FREQ_OTHER)
              dstrTemp = INDICATOR_OTHER;
            else 
            {
              bEnable = false;   
              dstrTemp = INDICATOR_OTHER;
            }
            SetControlText(IDC_EDT_MONTHLY, dstrTemp);
          }
          EnableControl(IDC_EDT_MONTHLY, bEnable);
          EnableControl(IDC_CMB_EOM, bEnable);
        }
      }
      m_bSetMonthlyInd = false;
*/
         }
         break;

      case IDC_CMB_ADDRESS_CODE:
         if( !m_bSystematicItemChange && !dstrValue.empty() )
         {
            DString dstrCode, dstrDesc;
            parsingCombinedField(dstrValue, dstrCode, dstrDesc, I_(" "));
            dstrCode.strip();
            fillAddress(dstrCode);
         }
         break;

      case IDC_EDT_AMOUNT:
         if( !m_bSystematicItemChange && !m_bBtnAllocation && !dstrValue.empty() )
         {
            LoadControl(IDC_EDT_AMOUNT);
            populateAllocations();
         }
         enableDisableAllocation();
         break;

      case IDC_CMB_TYPE:
         {
            if( !m_bSystematicItemChange && !dstrValue.empty() )
            {
               LoadControl(IDC_EDT_AMOUNT);
               if( !isATTransfer() )
                  LoadListControl(IDC_LV_ALLOCATION);
            }
            switchAllocAmountTypeColumn();

            enableDisableAllocation(&dstrValue);

		    LoadControl (IDC_CMB_TYPE);
         }
         break;
      case IDC_DTP_EFFECTIVE_DATE :
         {
            DString dstrAccountNum;
      	   getParent()->getField(this, ifds::AccountNum, dstrAccountNum);
	         MFAccount * pMFAccount = NULL;
            DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
	         if( dstWorkSession->getMFAccount( getDataGroupId(), dstrAccountNum, pMFAccount ) <= WARNING ) {
               if ( pMFAccount->isAMSAccount ( getDataGroupId() ) )
                  populateAllocations();
            }
         }
         break;
      default:
         break;
   }
}

//******************************************************************************

bool SystematicDlg::GetDataForControl(UINT controlID, DString &dstrValueOut, 
                                      bool bFormatted, int index) const
{
   bool bReturn = true;

   switch( controlID )
   {
      /*case IDC_CMB_FREQ:
          getFrequency(dstrValueOut);
        break;*/
      case IDC_CMB_DAY_OF_WEEK:
         getParent()->getField(this,IFASTBP_PROC::SYSTEMATIC_LIST,ifds::DayOfWeek,dstrValueOut,false);
         break;

         /*case IDC_EDT_MONTHLY:
           getMonthlyIndicator(dstrValueOut);
           break;
       */
      case IDC_CMB_ADDRESS_CODE:
         {
            getAddrCodeDesc(dstrValueOut);
            DSTComboBox* pComboBox = dynamic_cast<DSTComboBox*>(GetDlgItem(IDC_CMB_ADDRESS_CODE));
            int iSelect = pComboBox->SelectString(-1, dstrValueOut.c_str());
            pComboBox->SetCurSel(iSelect);
            break;
         }

      case IDC_EDT_ADDRESS:
         {
            DString dstrAddr;
            getParent()->getField(this, m_lContainerID, ifds::AddrLine1, dstrAddr);
            dstrValueOut = dstrAddr.strip();
            getParent()->getField(this, m_lContainerID, ifds::AddrLine2, dstrAddr);
            dstrValueOut = dstrValueOut + I_("\r\n") + dstrAddr.strip();
            getParent()->getField(this, m_lContainerID, ifds::AddrLine3, dstrAddr);
            dstrValueOut = dstrValueOut + I_("\r\n") + dstrAddr.strip();
            getParent()->getField(this, m_lContainerID, ifds::AddrLine4, dstrAddr);
            dstrValueOut = dstrValueOut + I_("\r\n") + dstrAddr.strip();
            getParent()->getField(this, m_lContainerID, ifds::AddrLine5, dstrAddr);
            dstrValueOut = dstrValueOut + I_("\r\n") + dstrAddr.strip();

            CString strAddr;
            strAddr = dstrValueOut.c_str();
            strAddr.TrimRight(_T("\r\n"));
            dstrValueOut = (LPCTSTR)strAddr;

            getParent()->getField(this, m_lContainerID, ifds::PostalCode, dstrAddr);
            dstrValueOut = dstrValueOut + I_("\r\n") + dstrAddr.strip();
            break;
         }

      case IDC_TXT_TRANS_NUMBER:
         {
            DString dstrBankIDType;
            int nMaxLength, nAllMaxLength;
            bool bIsAllDigits;
            getParent ()->getField ( this, 
                                     IFASTBP_PROC::SYSTEMATIC_LIST, 
                                     ifds::BankIdType, 
                                     dstrBankIDType, 
                                     false
                                   );
            if ( FinancialInstitution::getBankTransitNumInfo ( dstrBankIDType, 
                                                               nMaxLength, 
                                                               bIsAllDigits, 
                                                               nAllMaxLength
                                                             )
               )
            {
               if (bIsAllDigits)
               {
                  getParent ()->getField ( this, 
                                           IFASTBP_PROC::SYSTEMATIC_LIST, 
                                           ifds::TransitNo, 
                                           dstrValueOut, 
                                           false
                                         );
                  dstrValueOut.padLeft (nMaxLength, I_('0'));
                  bReturn = true;
               }
            }
            break;
         }
 
      case IDC_TXT_INST_CODE:
         {
            DString dstrBankIDType;
            int nMaxLength, nAllMaxLength;
            bool bIsAllDigits;
            getParent ()->getField ( this, 
                                     IFASTBP_PROC::SYSTEMATIC_LIST, 
                                     ifds::BankIdType, 
                                     dstrBankIDType, 
                                     false
                                   );

            if (FinancialInstitution::getBankIdNumInfo ( dstrBankIDType, 
                                                         nMaxLength, 
                                                         bIsAllDigits, 
                                                         nAllMaxLength
                                                        )
               )
            {
               if (bIsAllDigits)
               {
                  getParent ()->getField ( this, 
                                           IFASTBP_PROC::SYSTEMATIC_LIST, 
                                           ifds::BankIdValue, 
                                           dstrValueOut, 
                                           false
                                         );
                  dstrValueOut.padLeft (nMaxLength, I_('0'));
                  bReturn = true;
               }
            }
            break;
         }

      default:
         bReturn = false;
         break;
   }
   return(bReturn);
}

//******************************************************************************

bool SystematicDlg::SetDataFromControl(UINT controlID, const DString &strValue, 
                                       bool bFormatted, SEVERITY &sevRtn, int index)
{
   sevRtn = NO_CONDITION;
   bool bReturn = true;

   switch( controlID )
   {
      case IDC_CMB_DAY_OF_WEEK:
         {
            if( !strValue.empty() )
               getParent()->setField(this,IFASTBP_PROC::SYSTEMATIC_LIST,ifds::DayOfWeek,strValue,false);
            break;
         }

         /*case IDC_EDT_MONTHLY:
           {
             sevRtn = setMonthlyIndicator(strValue);
               
                DString dstrFrequency, dstrFrequency1;
                getParent()->getField(this, m_lContainerID, DBR::Frequency, dstrFrequency1, false);
             getFrequency(dstrFrequency, false);
             if (dstrFrequency.strip() != dstrFrequency1.strip())
             {
               m_bSetMonthlyInd = true;
               getParent()->setField(this, m_lContainerID, DBR::Frequency, dstrFrequency, false);
               LoadControl(IDC_CMB_FREQ);
             }
              break;
           }*/

      case IDC_CMB_ADDRESS_CODE:
         {
            DString dstrAddrCode, dstrAddrDesc;
            parsingCombinedField(strValue, dstrAddrCode, dstrAddrDesc, I_(" "));
            sevRtn  = getParent()->setField(this, m_lContainerID, ifds::AddrCode, dstrAddrCode, false);
            break;
         }

      default:
         bReturn = false;
         break;
   }
   return(bReturn);
}

//*****************************************************************************
SEVERITY SystematicDlg::populateAtAcctAllocRelate(const BFFieldId &idField, const DString& strValue)
{
   DString strOld;
   getParent()->getField(this, m_lContainerID, idField, strOld, false);
   strOld.strip();
   SEVERITY sevRtn = getParent()->setField(this, m_lContainerID, idField, strValue, false);
   if( strOld != strValue )
      PostMessage( POP_TOOL_TIP );

   return(sevRtn);
}

//*****************************************************************************

LRESULT SystematicDlg::ShowAcctList(WPARAM wParam, LPARAM lParam)
{
   showPayType();
   return( TRUE );
}

//******************************************************************************

bool SystematicDlg::GetOverrideItemString(long lSubstituteId, const DString &dstrColumnKey, DString &dstrOut)
{
   DString dstrStatus, dstrStopDate, dstrCurrBusDate;

   bool bReturn = true;
   if( lSubstituteId == ifds::SystematicListHeading.getId() )
   {
      if( dstrColumnKey == COL_ACTIVE )
      {
         getParent()->getField(this, m_lContainerID, ifds::StatusCode, dstrStatus, false);
         dstrStatus.strip();
         getParent()->getField(this, m_lContainerID, ifds::StopDate, dstrStopDate, false);
         dstrStopDate.strip();

         getParent()->getField(this, ifds::CurrBusDate, dstrCurrBusDate, false);
         dstrCurrBusDate.strip();

         COleDateTime dateStop, dateCurrBus;
         setOleDateFromHost(dateStop, dstrStopDate);
         setOleDateFromHost(dateCurrBus, dstrCurrBusDate);

         CString cstrTemp;
         cstrTemp.LoadString( (dstrStatus == YES) ? IDS_TXT_YES : IDS_TXT_NO );
         dstrOut = (LPCTSTR) cstrTemp;
      }
      else if( dstrColumnKey == COL_PAYTYPE )
      {
         getParent()->getField(this, m_lContainerID, ifds::SystematicPayType, dstrOut, true);    
      }
      else if( dstrColumnKey == COL_FUND )
      {
         getParent()->getField(this, m_lContainerID, ifds::FundCode,  dstrOut,  false);
         dstrOut.strip().upperCase();
      }
      else if( dstrColumnKey == COL_CLASS )
      {
         getParent()->getField(this, m_lContainerID, ifds::ClassCode, dstrOut, false);
         dstrOut.strip().upperCase();
      }
      /*else if (dstrColumnKey == COL_FREQUENCY)
      {				
         getFrequency(dstrOut, true);
         dstrOut.strip().upperCase();
      }*/
      else if( dstrColumnKey == FUND_NUMBER )
      // Get Fund Number.  this has been comment out
      {
         DString dstrFundCode, dstrClassCode;
         getParent()->getField( this, m_lContainerID, ifds::FundCode, dstrFundCode );
         getParent()->getField( this, m_lContainerID, ifds::ClassCode, dstrClassCode );
         dstrFundCode.strip().upperCase();
         dstrClassCode.strip().upperCase();
         dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->GetFundNumber ( dstrFundCode, dstrClassCode, dstrOut);
         return(true);
      }
      else
      {
         bReturn = false;
      }
   }
   else if( lSubstituteId == ifds::SysAllocListHeading.getId() )
   {
      if( dstrColumnKey == COL_PERCENT )
      {
         getParent()->getField(this, IFASTBP_PROC::SYSALLOCATION_LIST, ifds::Percentage,  dstrOut,  true);
         DString dstrTemp(dstrOut);
         dstrTemp = dstrTemp.stripAll(I_('.')).stripAll(I_('0')).stripAll();
         if( dstrTemp == I_("") )
         {
            dstrOut = dstrTemp;
         }
      }
      else if( dstrColumnKey == COL_FUND )
      {
         getParent()->getField(this, IFASTBP_PROC::SYSALLOCATION_LIST, ifds::FundCode,  dstrOut,  false);
         dstrOut.strip().upperCase();
      }
      else if( dstrColumnKey == COL_CLASS )
      {
         getParent()->getField(this, IFASTBP_PROC::SYSALLOCATION_LIST, ifds::ClassCode, dstrOut, false);
         dstrOut.strip().upperCase();
      }
      else if( dstrColumnKey == COL_ALLOCAMOUNT )
      {
         DString dstrFundCode;
         getParent()->getField(this, m_lContainerID, ifds::FundCode, dstrFundCode, false);
         dstrFundCode.strip().upperCase();
         if( !dstrFundCode.empty() )
         {
            getParent()->getField(this, m_lContainerID, ifds::Amount, dstrOut, true);
            dstrOut.strip();
         }
         else
         {
            bReturn = false;
         }
      }
      else
      {
         bReturn = false;
      }
   }
   else if( lSubstituteId ==  ifds::ATAllocationListHeading.getId() )
   {

      if( dstrColumnKey == AT_COL_FUND )
      {
         getParent()->getField(this, IFASTBP_PROC::AT_FUND_ALLOCATIONLIST, ifds::FundCode,  dstrOut,  true);
         dstrOut.strip().upperCase();
      }
      else if( dstrColumnKey == AT_COL_PERCENT )
      {
         getParent()->getField(this, IFASTBP_PROC::AT_FUND_ALLOCATIONLIST, ifds::Percentage,  dstrOut,  true);
         dstrOut.strip().upperCase();
      }
      else if( dstrColumnKey == AT_COL_CLASS )
      {
         getParent()->getField(this, IFASTBP_PROC::AT_FUND_ALLOCATIONLIST, ifds::ClassCode,  dstrOut,  true);
         dstrOut.strip().upperCase();
      }
      else if( dstrColumnKey == AT_COL_UNITS )
      {
         getParent()->getField(this, IFASTBP_PROC::AT_FUND_ALLOCATIONLIST, ifds::AllocAmount,  dstrOut,  true);
         dstrOut.strip().upperCase();
      }
      else
      {
         bReturn = false;

      }

   }
   else if( lSubstituteId ==  ifds::LV_AtAcctAllocationHeading.getId() )
   {
      if( dstrColumnKey == AT_ACCT_COL_ACCOUNT )
      {
         getParent()->getField(this, IFASTBP_PROC::AT_ACCOUNT_ALLOCATIONLIST, ifds::AllocAccountNum,  dstrOut,  true);
         dstrOut.strip().upperCase();
      }
      else if( dstrColumnKey == AT_ACCT_COL_PERCENTAGE )
      {
         getParent()->getField(this, IFASTBP_PROC::AT_ACCOUNT_ALLOCATIONLIST, ifds::Percentage,  dstrOut,  true);
         dstrOut.strip().upperCase();
      }
      else
      {
         bReturn = false;
      }
   }
   return(bReturn);
}

//******************************************************************************

void SystematicDlg::fillAddressCode()
{
   const BFContainerId& idContainer = IFASTBP_PROC::ADDRESS_LIST;

   DSTComboBox* pComboBox = dynamic_cast<DSTComboBox*>(GetDlgItem(IDC_CMB_ADDRESS_CODE));
   pComboBox->ResetContent();

   const DString *pCurKey = &(getParent()->getCurrentListItemKey(this, IFASTBP_PROC::ADDRESS_LIST));

   CStringList strList;

   DString dstrCode, dstrDesc;
   int iIndex;

   const DString *pKey = &(getParent()->getFirstListItemKey(this, IFASTBP_PROC::ADDRESS_LIST));
   while( *pKey != NULL_STRING )
   {
      getParent()->getField(this, IFASTBP_PROC::ADDRESS_LIST, ifds::AddrCode, dstrCode, false);
      dstrCode.strip();
      if( strList.Find(dstrCode.c_str()) == NULL )
      {
         strList.AddTail(dstrCode.c_str());
         getParent()->getField(this, IFASTBP_PROC::ADDRESS_LIST, ifds::AddrCode, dstrDesc);
         dstrDesc.strip();
         if( dstrDesc == NULL_STRING )
         {
            getParent()->getField(this, IFASTBP_PROC::ADDRESS_LIST, ifds::AddrCodeDesc, dstrDesc);
            dstrDesc.strip();
         }

         iIndex = pComboBox->AddString(dstrDesc.c_str());
         pComboBox->SetItemData(iIndex, reinterpret_cast<DWORD>(pKey));
      }
      pKey = &getParent()->getNextListItemKey(this, IFASTBP_PROC::ADDRESS_LIST);
   }
   if( *pCurKey != NULL_STRING )
      getParent()->setCurrentListItem(this, IFASTBP_PROC::ADDRESS_LIST, *pCurKey);
}

//******************************************************************************

void SystematicDlg::fillPlanCode()
{
   DSTComboBox* pComboBox = dynamic_cast<DSTComboBox*>(GetDlgItem(IDC_CMB_PLAN));
   pComboBox->FillInListValues( IFASTBP_PROC::SAVINGPLAN_MASTER_LIST, ifds::RxPlanCode);
}

//******************************************************************************

void SystematicDlg::fillAddress(const DString& dstrAddrCodeSel)
{
   COleDateTime dateEffectiveSel, dateEffective, dateCurrBus;
   DString dstrCurrBusDate, dstrEffectiveDate;

   getParent()->getField(this, ifds::CurrBusDate, dstrCurrBusDate, false);
   dstrCurrBusDate.strip();
   setOleDateFromHost(dateCurrBus,     dstrCurrBusDate);

   DString dstrAddrCode;
   CStringList strList;

   const DString *pCurKey = &(getParent()->getCurrentListItemKey(this, IFASTBP_PROC::ADDRESS_LIST));
   const DString *pKey = &getParent()->getFirstListItemKey(this, IFASTBP_PROC::ADDRESS_LIST);
   const DString *pKeySel = NULL;

   while( *pKey != NULL_STRING )
   {
      getParent()->getField(this, IFASTBP_PROC::ADDRESS_LIST, ifds::AddrCode, dstrAddrCode, false);
      dstrAddrCode.strip();
      if( dstrAddrCode == dstrAddrCodeSel )
      {
         getParent()->getField(this, IFASTBP_PROC::ADDRESS_LIST, ifds::EffectiveDate, dstrEffectiveDate, false);
         dstrEffectiveDate.strip();
         if( pKeySel == NULL )
         {
            pKeySel = pKey;
            setOleDateFromHost(dateEffectiveSel,   dstrEffectiveDate);
         }
         else
         {
            setOleDateFromHost(dateEffective,   dstrEffectiveDate);
            if( dateEffective <= dateCurrBus && dateEffective > dateEffectiveSel )
               pKeySel = pKey;
         }
      }
      pKey = &getParent()->getNextListItemKey(this, IFASTBP_PROC::ADDRESS_LIST);
   }

   DString dstrAddr;
   if( pKeySel != NULL )
   {
      getParent()->setCurrentListItem(this, IFASTBP_PROC::ADDRESS_LIST, *pKeySel);

      getParent()->getField(this, IFASTBP_PROC::ADDRESS_LIST,    ifds::AddrLine1, dstrAddr);
      getParent()->setField(this, m_lContainerID,  ifds::AddrLine1, dstrAddr);

      getParent()->getField(this, IFASTBP_PROC::ADDRESS_LIST,    ifds::AddrLine2, dstrAddr);
      getParent()->setField(this, m_lContainerID,  ifds::AddrLine2, dstrAddr);

      getParent()->getField(this, IFASTBP_PROC::ADDRESS_LIST,    ifds::AddrLine3, dstrAddr);
      getParent()->setField(this, m_lContainerID,  ifds::AddrLine3, dstrAddr);

      getParent()->getField(this, IFASTBP_PROC::ADDRESS_LIST,    ifds::AddrLine4, dstrAddr);
      getParent()->setField(this, m_lContainerID,  ifds::AddrLine4, dstrAddr);

      getParent()->getField(this, IFASTBP_PROC::ADDRESS_LIST,    ifds::AddrLine5, dstrAddr);
      getParent()->setField(this, m_lContainerID,  ifds::AddrLine5, dstrAddr);

      getParent()->getField(this, IFASTBP_PROC::ADDRESS_LIST,    ifds::PostalCode,dstrAddr);
      getParent()->setField(this, m_lContainerID,  ifds::PostalCode,dstrAddr);
   }
   else
   {
      dstrAddr = NULL_STRING;
      getParent()->setField(this, m_lContainerID,  ifds::AddrLine1, dstrAddr);
      getParent()->setField(this, m_lContainerID,  ifds::AddrLine2, dstrAddr);
      getParent()->setField(this, m_lContainerID,  ifds::AddrLine3, dstrAddr);
      getParent()->setField(this, m_lContainerID,  ifds::AddrLine4, dstrAddr);
      getParent()->setField(this, m_lContainerID,  ifds::AddrLine5, dstrAddr);
      getParent()->setField(this, m_lContainerID,  ifds::PostalCode,dstrAddr);
   }
   LoadControl(IDC_EDT_ADDRESS);
   if( *pCurKey != NULL_STRING )
      getParent()->setCurrentListItem(this, IFASTBP_PROC::ADDRESS_LIST, *pCurKey);
}

//******************************************************************************

void SystematicDlg::parsingPayType(const DString& dstrValueIn, DString& dstrTransType, DString& dstrPayType) const
{
   if( dstrValueIn == TRADETYPE::AUTO_TRANSFER )
   {
      dstrTransType  = TRADETYPE::AUTO_TRANSFER;
      dstrPayType    = TRADETYPE::AUTO_TRANSFER;
      return;
   }
   parsingCombinedField(dstrValueIn, dstrTransType, dstrPayType, SEP_HYPHEN);
}

//******************************************************************************

void SystematicDlg::parsingCombinedField(const DString& dstrValueIn, 
                                         DString& dstrField1, DString& dstrField2, 
                                         const DString& dstrSep) const
{
   DString::size_type findPos;
   findPos = dstrValueIn.find(dstrSep, 0);
   dstrField1 = dstrValueIn.substr(0, findPos);
   dstrField2 = dstrValueIn.substr(findPos + 1);
}

//******************************************************************************
/*
void SystematicDlg::showAutomaticTransfer()
{
   TRACE_METHOD( CLASSNAME, I_( "showAutomaticTransfer" ));
   DString dstrTransType, dstrPayType, dstrPayTypeDesc;
   //parsing the pay type from the combobox 
   GetControlText(IDC_CMB_PAYTYPE, dstrPayTypeDesc);
   dstrPayTypeDesc.strip();
   parsingPayType(const_cast<DString&>(dstrPayTypeDesc), dstrTransType, dstrPayType);
  int iShowAT = SW_HIDE;
  int iShowAT_ACCOUNT = SW_HIDE;
  int iShowAT_FUND = SW_HIDE;

  if (dstrTransType == TRADETYPE::AUTO_TRANSFER)
   {
    iShowAT = SW_SHOW;
    DString strAccoutTo;
    getParent()->getField(this, m_lContainerID, DBR::AccountTo, strAccoutTo, true);
  }
   GetDlgItem(IDC_AT_DTP_FIRST_TRANS)->ShowWindow(iShowAT);
}
*/
//******************************************************************************

void SystematicDlg::showPayType()
{
   TRACE_METHOD( CLASSNAME, I_( "showPayType" ));

   DString dstrTransType, dstrPayType, dstrPayTypeDesc;
   //parsing the pay type from the combobox 
   GetControlText(IDC_CMB_PAYTYPE, dstrPayTypeDesc);
   dstrPayTypeDesc.strip();
   parsingPayType(const_cast<DString&>(dstrPayTypeDesc), dstrTransType, dstrPayType);
   LoadControl(IDC_CMB_FREQ);//??


   bool bEnableFlag = false;
   DString dstrStatus;
   getParent()->getField(this, m_lContainerID, ifds::StatusCode, dstrStatus, false);
   if( dstrStatus.strip() == YES || m_bNewItem )
      bEnableFlag = true;

   int iShowFrame       = SW_SHOW;
   int iShowSP          = SW_SHOW;
   int iShowAT_Fund     = SW_HIDE;
   int iShowAT_ACCT     = SW_HIDE;
   int iShowSavingPlan  = SW_HIDE;

   int iShowBank = SW_HIDE; 
   int iShowAddress = SW_HIDE;
   int iShowFund = SW_HIDE;
   CString strAipSwp, strTemp;
   ConnectListToData(IDC_TXT_AT_ACCT_LIST,false);

	DString dstrPayMethod;
	getParent()->getField( this, ifds::PayMethod, dstrPayMethod, false );	

   if( dstrTransType == TRADETYPE::PAC )
   {
      strAipSwp.LoadString(TXT_SYSTEMATICS_AIP);

      strTemp.LoadString(FRA_SYSTEMATIC_TO);
      SetDlgItemText(IDC_FRA_TO, (LPCTSTR)strTemp);

      strTemp.LoadString ( FRA_SYSTEMATIC_FROM );
      SetDlgItemText (IDC_FRA_FROM, (LPCTSTR)strTemp);
      if( dstrPayType == I_("E") )
      {
			if ( I_( "CHQ" ) != dstrPayMethod.strip().upperCase() )
			{
				iShowBank    = SW_SHOW;
				iShowAddress = SW_HIDE;
			}
			else
			{
				iShowAddress = SW_SHOW;
				iShowBank    = SW_HIDE;
			}
         
         iShowFund    = SW_HIDE;
      }
      else
      {
         iShowFrame   = SW_HIDE;
         iShowBank    = SW_HIDE;
         iShowAddress = SW_HIDE;
         iShowFund    = SW_HIDE;
      }
   }
   else if( dstrTransType == TRADETYPE::SWP )
   {
      strAipSwp.LoadString(TXT_SYSTEMATICS_SWP);

      strTemp.LoadString(FRA_SYSTEMATIC_FROM);
      SetDlgItemText(IDC_FRA_TO, (LPCTSTR)strTemp);

      strTemp.LoadString(FRA_SYSTEMATIC_TO);
      SetDlgItemText(IDC_FRA_FROM, (LPCTSTR)strTemp);
      if( dstrPayType == I_("E") )
      {

			if ( I_( "CHQ" ) != dstrPayMethod.strip().upperCase() )
			{
				iShowBank    = SW_SHOW;
				iShowAddress = SW_HIDE;
			}
			else
			{
				iShowAddress = SW_SHOW;
				iShowBank    = SW_HIDE;
			}
                  
         iShowFund    = SW_HIDE;
      }
      else if( dstrPayType == I_("W") || dstrPayType == I_("X") )
      {
         iShowFrame   = SW_HIDE;
         iShowBank    = SW_HIDE;
         iShowAddress = SW_HIDE;
         iShowFund    = SW_HIDE;
      }
      else
      {
         iShowBank    = SW_HIDE;
         iShowAddress = SW_SHOW;
         iShowFund    = SW_HIDE;
      }
   }
   else if( dstrTransType == TRADETYPE::AUTO_TRANSFER )                     //Automatic Transfer
   {
      //     strTemp.LoadString ( FRA_SYSTEMATIC_TO );
      //     SetDlgItemText(IDC_FRA_TO, (LPCTSTR)strTemp);

      //     strTemp.LoadString ( FRA_SYSTEMATIC_FROM );
      //     SetDlgItemText (IDC_FRA_FROM, (LPCTSTR)strTemp);
      iShowFrame   = SW_HIDE;
      iShowBank    = SW_HIDE;
      iShowAddress = SW_HIDE;
      iShowFund    = SW_HIDE;
      iShowSP      = SW_HIDE;

      iShowAT_Fund = SW_SHOW;

      ConnectListToData(IDC_TXT_AT_ACCT_LIST,true);
      DString strMarket = DSTCommonFunctions::getMarket();

      int iFundItemNum(0);
      int iAcctItemNum = getParent()->getNumberOfItemsInList(this, IFASTBP_PROC::AT_ACCOUNT_ALLOCATIONLIST);
      if( iAcctItemNum > 0 )
         iFundItemNum = getParent()->getNumberOfItemsInList(this, IFASTBP_PROC::AT_FUND_ALLOCATIONLIST);
      if( isToFundClassAccountEmpty() && (iAcctItemNum > 1 || iFundItemNum > 1) )
      {
         //  Account level Allocation
         // if it is a new item, we  need to display fund
         // if it is a new item, but the user already go to the allocation screen and add acct level allocation, 
         // then we need to display the acct list here.
         iShowAT_ACCT  = SW_SHOW;
         iShowAT_Fund  = SW_HIDE;
         ConnectControlToData(IDC_EDT_AT_FUND,false);
         ConnectControlToData(IDC_EDT_AT_CLASS,false);
         if( strMarket == MARKET_IDS::JAPAN )
            ConnectControlToData(IDC_CMB_AT_ACCT_TO,false);
         else
            ConnectControlToData(IDC_EDT_AT_ACCT_TO,false);     
      }
      else
      {
         ConnectControlToData(IDC_EDT_AT_FUND,true);
         ConnectControlToData(IDC_EDT_AT_CLASS,true);
         if( strMarket == MARKET_IDS::JAPAN )
            ConnectControlToData(IDC_CMB_AT_ACCT_TO,true);
         else
            ConnectControlToData(IDC_EDT_AT_ACCT_TO,true);
      }   
      LoadListControl(IDC_TXT_AT_ACCT_LIST);
      LoadControl(IDC_AT_DTP_FIRST_TRANS);
      LoadControl(IDC_AT_DTP_STOP);
   }
   else if( dstrTransType == TRANS_TYPE_SAVING_PLAN )
   {
      iShowSavingPlan = SW_SHOW;
      iShowBank    = SW_SHOW;
   }
   else
   {
      iShowFrame   = SW_HIDE;
      iShowBank    = SW_HIDE;
      iShowAddress = SW_HIDE;
      iShowFund    = SW_HIDE;
      iShowAT_ACCT = SW_HIDE;
      iShowAT_Fund = SW_HIDE;
   }
   int iShowAT = (iShowAT_Fund == SW_SHOW || iShowAT_ACCT == SW_SHOW) ? SW_SHOW : SW_HIDE;

   bool bConnectAT = (iShowAT == SW_SHOW ) ? true : false;
   ConnectControlToData(IDC_AT_DTP_FIRST_TRANS,    bConnectAT);
   ConnectControlToData(IDC_AT_DTP_STOP,           bConnectAT);
   ConnectControlToData(IDC_DTP_EFFECTIVE_DATE,   !bConnectAT);
   ConnectControlToData(IDC_DTP_STOP_DATE,        !bConnectAT);
   if( !bConnectAT )
   {
      LoadControl(IDC_DTP_EFFECTIVE_DATE);
      LoadControl(IDC_DTP_STOP_DATE);
   }

   populateAllocations();

   reinitGrid( dstrTransType );


/**
 *	   From Frame infromation
 */
   (CWnd *)GetDlgItem(IDC_FRA_FROM)->ShowWindow(iShowFrame);
   (CWnd *)GetDlgItem(IDC_FRA_TO)->ShowWindow(iShowSP);

   //From Frame non-AT specific
   (CWnd *)GetDlgItem(IDC_TXT_EFFECTIVE)->ShowWindow(iShowSP);                
   (CWnd *)GetDlgItem(IDC_DTP_EFFECTIVE_DATE)->ShowWindow(iShowSP);
   (CWnd *)GetDlgItem(IDC_DTP_STOP_DATE)->ShowWindow(iShowSP);

   (CWnd *)GetDlgItem(IDC_TXT_NEXT_PROCESS)->ShowWindow(iShowSP);
   (CWnd *)GetDlgItem(IDC_STATIC_NEXT_PROCESS)->ShowWindow(iShowSP);

   GetDlgItem(IDC_TXT_PLAN)->ShowWindow(iShowSavingPlan);
   GetDlgItem(IDC_CMB_PLAN)->ShowWindow(iShowSavingPlan);


   //From Frame AT specific
   (CWnd *)GetDlgItem(IDC_AT_TXT_FIRST_TRANS)->ShowWindow(iShowAT);        //lable
   (CWnd *)GetDlgItem(IDC_AT_DTP_FIRST_TRANS)->ShowWindow(iShowAT);
   (CWnd *)GetDlgItem(IDC_AT_DTP_STOP)->ShowWindow(iShowAT);
   (CWnd *)GetDlgItem(IDC_AT_FROM)->ShowWindow(iShowAT);
   (CWnd *)GetDlgItem(IDC_TXT_AT_TO)->ShowWindow(iShowAT);


	DString strMarket = DSTCommonFunctions::getMarket();


   //Bank Information Frame 
	setBankRelatedControls( iShowBank );
	
   // Address Inforamtion Frame  
	setAddressRelatedControls( iShowAddress );

/**
 *      Automatic Transfer Information Frame
 */
   (CWnd *)GetDlgItem(IDC_TXT_AT_TRANS_TYPE)->ShowWindow(iShowAT);
   (CWnd *)GetDlgItem(IDC_EDT_AT_TRANS_TYPE)->ShowWindow(iShowAT);

   (CWnd *)GetDlgItem(IDC_AT_DTP_FIRST_TRANS)->ShowWindow(iShowAT);
   (CWnd *)GetDlgItem(IDC_AT_DTP_STOP)->ShowWindow(iShowAT);
   (CWnd *)GetDlgItem(IDC_AT_TXT_FIRST_TRANS)->ShowWindow(iShowAT);

   /**
   *		Automatic Transfer Account
   */
   (CWnd *)GetDlgItem(IDC_TXT_AT_ACCT_LIST)->ShowWindow(iShowAT_ACCT);

   /**
    *    Automatic Transfer Fund
    */
   (CWnd *)GetDlgItem(IDC_LBL_AT_FUND)->ShowWindow(iShowAT_Fund);

   if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
   {
      (CWnd *)GetDlgItem(IDC_EDT_TO_FUND)->ShowWindow(iShowAT_Fund);
   }
   else if( strMarket == MARKET_IDS::JAPAN )
   {
      (CWnd *)GetDlgItem(IDC_EDT_TO_FUND)->ShowWindow(SW_HIDE);
   }

   (CWnd *)GetDlgItem(IDC_EDT_AT_FUND)->ShowWindow(iShowAT_Fund);
   (CWnd *)GetDlgItem(IDC_LBL_AT_CLASS)->ShowWindow(iShowAT_Fund);
   (CWnd *)GetDlgItem(IDC_EDT_AT_CLASS)->ShowWindow(iShowAT_Fund);

   (CWnd *)GetDlgItem(IDC_LBL_AT_ACCT_TO)->ShowWindow(iShowAT_Fund);
   if( strMarket == MARKET_IDS::JAPAN )
   {
      (CWnd *)GetDlgItem(IDC_CMB_AT_ACCT_TO)->ShowWindow(iShowAT_Fund);
      (CWnd *)GetDlgItem(IDC_EDT_AT_ACCT_TO)->ShowWindow(SW_HIDE);

   }
   else
   {
      (CWnd *)GetDlgItem(IDC_EDT_AT_ACCT_TO)->ShowWindow(iShowAT_Fund);
      (CWnd *)GetDlgItem(IDC_CMB_AT_ACCT_TO)->ShowWindow(SW_HIDE);

   }
   (CWnd *)GetDlgItem(IDC_LBL_AT_NAME)->ShowWindow(iShowAT_Fund);
   (CWnd *)GetDlgItem(IDC_TXT_AT_NAME)->ShowWindow(iShowAT_Fund);


   (CWnd *)GetDlgItem(IDC_TXT_AT_TRANS_TYPE)->ShowWindow(iShowAT);
   (CWnd *)GetDlgItem(IDC_EDT_AT_TRANS_TYPE)->ShowWindow(iShowAT);


/**
  *  Systematic Fee Information Frame
  */
   if( iShowAT == SW_SHOW )
   {
      iShowSP     = SW_HIDE;
      iShowFund   = SW_HIDE;
   }

   (CWnd *)GetDlgItem(IDC_BTN_BANK)->EnableWindow(bEnableFlag);

   SetUserAccesFuncCode();
   CheckPermission();
   GetDlgItem(IDC_BTN_INDEXING)->
      EnableWindow( dstrTransType == TRADETYPE::PAC || dstrTransType == TRANS_TYPE_SAVING_PLAN );

   DString strIsFundLimitedByBankuptcy;      
   getParent()->getField(this, BF::NullContainerId, SYSTEMATICLIT::IsFundLimitedByBankuptcy, strIsFundLimitedByBankuptcy, false);   
   strIsFundLimitedByBankuptcy.strip().upperCase();
   
   DString dstrFundAlloc;
   getParent()->getField(this, ifds::FundAlloc, dstrFundAlloc, false);
   dstrFundAlloc.strip();
      
   BOOL bAllocBtnEnable = (dstrTransType != TRANS_TYPE_SAVING_PLAN) && 
                           m_bInvAdvice && 
                          (strIsFundLimitedByBankuptcy == NO) &&
                          dstrFundAlloc != I_("N");

   GetDlgItem(IDC_BTN_ALLOCATION)->EnableWindow( bAllocBtnEnable );
}

//******************************************************************************

bool SystematicDlg::doDisableControl(UINT nID, bool bIsNew)
{
   TRACE_METHOD( CLASSNAME, I_( "doDisableControl" ));

   bool bRetVal = false;
   bool bEnableFlag = false;
   DString dstrStatus, dstrModPerm;
   getParent()->getField(this, m_lContainerID, ifds::StatusCode, dstrStatus, false);
   getParent()->getField(this, m_lContainerID, ifds::ModPerm, dstrModPerm, false);

   if( dstrStatus.strip().upperCase() == YES || dstrModPerm.strip().upperCase() == YES || bIsNew )
      bEnableFlag = true;
   DString strMarket = DSTCommonFunctions::getMarket();

   switch( nID )
   {
      case IDC_CMB_PAYTYPE:
      case IDC_EDT_FUND:
      case IDC_EDT_CLASS:
      case IDC_EDT_AMOUNT:
      case IDC_CMB_TYPE:
      case IDC_DTP_EFFECTIVE_DATE:
      case IDC_DTP_STOP_DATE:
      case IDC_CMB_FREQ:
      case IDC_CMB_EOM:
      case IDC_EDT_MONTHLY:
      case IDC_EDT_TO_FUND:
      case IDC_EDT_AT_FUND:
      case IDC_EDT_AT_CLASS:
      case IDC_EDT_AT_ACCT_TO:
      case IDC_CMB_AT_ACCT_TO:

      case IDC_CMB_DAY_OF_WEEK:
         {
            if( !bEnableFlag )
               bRetVal = true;
         }
         break;
      case IDC_EDT_FROM_FUND:
      case IDC_AT_DTP_FIRST_TRANS:
      case IDC_AT_DTP_STOP:
         {
            if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
               if( !bEnableFlag )
                  bRetVal = true;
         }
         break;

         //always readonly
         //case IDC_EDT_ACC_NBR:
      case IDC_EDT_ADDRESS:
         bRetVal = true;
         break;

      default: bRetVal = false;
   }

   return(bRetVal);
}

//******************************************************************************
bool SystematicDlg::doDisablePermCheckButton(UINT nID)

{
   TRACE_METHOD (CLASSNAME, I_("doDisablePermCheckButtons"));
   
   bool bDisableBaseOnRuleType (false);
   DString dstrAccountNum;
   getParent()->getField (this, ifds::AccountNum, dstrAccountNum);
	MFAccount * pMFAccount(NULL);
   DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
	if (!dstrAccountNum.empty() && dstWorkSession->getMFAccount (getDataGroupId(), dstrAccountNum, pMFAccount) <= WARNING) 
   {
      DString commitmentStatus;
      
      pMFAccount->getField (ifds::CommitmentStatus, commitmentStatus, getDataGroupId(), false);
      bDisableBaseOnRuleType = commitmentStatus == I_("01") || 
                               commitmentStatus == I_("02") || 
                               commitmentStatus == I_("03");
   }
   if (bDisableBaseOnRuleType && 
        (nID == IDC_BTN_ADD_COPY ||
         nID == IDC_BTN_DELETE ||
         nID == IDC_BTN_NEW))
   {
      return true;
   }

   if (nID == IDC_BTN_ADD_COPY)
   {
      bool bEnableFlag = false;
      DString dstrStatus,dstrAmtTypeOvrd;
      
      getParent()->getField(this, m_lContainerID, ifds::StatusCode, dstrStatus, false);
	  getParent()->getField(this, m_lContainerID, ifds::AmtTypeOvrd, dstrAmtTypeOvrd, false);

      if ((dstrStatus.strip() == YES || m_bNewItem) && dstrAmtTypeOvrd != AMT_TYPE::PORTFOLIO)
         bEnableFlag = true;

      return (!bEnableFlag);
   }
   else if (nID == IDC_BTN_DELETE)
   {
      bool bEnableFlag = false;
      DString dstrModPerm;
      getParent()->getField (this, m_lContainerID, ifds::ModPerm, dstrModPerm, false);
      if( dstrModPerm.strip() == YES || m_bNewItem )
         bEnableFlag = true;
      return (!bEnableFlag);
   }   
   return (false);
}
//******************************************************************************

void SystematicDlg::enableDisableAllocation(const DString* pdstrAmountType)
{
   DString dstrValue, dstrModPerm;
   DString dstrFundAlloc, dstrSWPPortfolioPayoutPlan;DString str;
   
   getParent()->getField(this, m_lContainerID, ifds::TransType, str, false);
   getParent()->getField(this, m_lContainerID, ifds::StatusCode, dstrValue, false);
   getParent()->getField(this, m_lContainerID, ifds::ModPerm, dstrModPerm, false);
   getParent()->getField(this, ifds::FundAlloc, dstrFundAlloc, false);
   dstrFundAlloc.strip();

   getParent()->getField(this, IsSWPPortfolioPayoutPlan, dstrSWPPortfolioPayoutPlan);

   if (str == TRADETYPE::SWP && dstrSWPPortfolioPayoutPlan == YES)
   {
       GetDlgItem(IDC_BTN_ALLOCATION)->EnableWindow(false);
       return;
   }
   else 
   {
       GetDlgItem(IDC_BTN_ALLOCATION)->EnableWindow(true);
   }


   // When StatusCode = No or ModPerm = No, then record is not updatable by user. It applies to 
   // all transaction type

   if( dstrFundAlloc == I_("N") ||
       dstrValue.strip().upperCase() != YES && !m_bNewItem  || 
       dstrModPerm.strip().upperCase() != YES && !m_bNewItem  )
   {
      //(CWnd *)GetDlgItem(IDC_LV_ALLOCATION)->EnableWindow(false);
      (CWnd *)GetDlgItem(IDC_BTN_ALLOCATION)->EnableWindow(false);
      return;
   }

   if( isATTransfer() )  // there is default value in the CBO that set the field ModPerm to true
   {
      if (m_bNewItem)
         dstrModPerm = YES;

      DString strIsFundLimitedByBankuptcy;      
      getParent()->getField(this, BF::NullContainerId, SYSTEMATICLIT::IsFundLimitedByBankuptcy, strIsFundLimitedByBankuptcy, false);   
      strIsFundLimitedByBankuptcy.strip().upperCase();
         
      BOOL bAllocBtnEnable = m_bInvAdvice && 
                           (dstrModPerm.strip().upperCase() == YES ) && 
                           (strIsFundLimitedByBankuptcy == NO);

      (CWnd*)GetDlgItem(IDC_BTN_ALLOCATION)->EnableWindow( bAllocBtnEnable);      
   }
   else
   {
      if( str == TRANS_TYPE_SAVING_PLAN )
      {
         GetDlgItem(IDC_BTN_ALLOCATION)->EnableWindow( false );
      }
      else
      {
         if( pdstrAmountType == NULL )
            getParent()->getField(this, m_lContainerID, ifds::AmountType, dstrValue, false);
         else
            dstrValue = *pdstrAmountType;

         dstrValue.strip().upperCase();

         DString strIsFundLimitedByBankuptcy;
         getParent()->getField(this, BF::NullContainerId, SYSTEMATICLIT::IsFundLimitedByBankuptcy, strIsFundLimitedByBankuptcy, false);
         strIsFundLimitedByBankuptcy.strip().upperCase();

         BOOL bAllocBtnEnable = m_bInvAdvice && 
                                /*!(dstrValue == I_("U")) && */
                                (strIsFundLimitedByBankuptcy == NO);

         GetDlgItem( IDC_BTN_ALLOCATION )->EnableWindow( bAllocBtnEnable );
      }
   }
}

//******************************************************************************

void SystematicDlg::ShowFromBankRelated( bool bShow )
{
   DString  dstrBankIdType;
   DString  dstrMarket = DSTCommonFunctions::getMarket();
   int   nCmdShow = bShow ? SW_SHOW : SW_HIDE;

   getParent()->getField( this, m_lContainerID, ifds::BankIdType, dstrBankIdType, false );
   dstrBankIdType.strip();

   GetDlgItem( IDC_LBL_BANK_NAME )->ShowWindow( nCmdShow );
   GetDlgItem( IDC_TXT_BANK_NAME )->ShowWindow( nCmdShow );
   GetDlgItem( IDC_LBL_ACC_NBR )->ShowWindow( nCmdShow );
   GetDlgItem( IDC_EDT_ACC_NBR )->ShowWindow( nCmdShow );
   GetDlgItem( IDC_BTN_BANK )->ShowWindow( nCmdShow );
   //  GetDlgItem( IDC_FRA_FROM )->ShowWindow( nCmdShow );
   GetDlgItem( IDC_LBL_INST_CODE )->ShowWindow( nCmdShow );
   GetDlgItem( IDC_TXT_INST_CODE )->ShowWindow( nCmdShow );
   GetDlgItem( IDC_LBL_TRANS_NUMBER  )->ShowWindow( SW_HIDE );
   GetDlgItem( IDC_TXT_TRANS_NUMBER )->ShowWindow( SW_HIDE );
   if( bShow )
   {
      if( dstrMarket == MARKET_IDS::CANADA || dstrMarket == MARKET_IDS::LUXEMBOURG )
      {
         if( dstrBankIdType == CODE_BANKIDTYPE_CANADA || dstrBankIdType == CODE_BANKIDTYPE_JAPAN )
         {
            GetDlgItem( IDC_LBL_TRANS_NUMBER  )->ShowWindow( SW_SHOW );
            GetDlgItem( IDC_TXT_TRANS_NUMBER )->ShowWindow( SW_SHOW );
            CString cstrTemp;
            cstrTemp.LoadString( IDS_LBL_INSTCODE );
            SetDlgItemText( IDC_LBL_INST_CODE, cstrTemp );
         }
         else if( dstrBankIdType == CODE_BANKIDTYPE_ABA )
         {
            CString cstrTemp;
            cstrTemp.LoadString( IDS_LBL_ABA_NBR );
            SetDlgItemText( IDC_LBL_INST_CODE, cstrTemp );
         }
         else if( dstrBankIdType == CODE_BANKIDTYPE_SWIFT )
         {
            CString cstrTemp;
            cstrTemp.LoadString( IDS_LBL_SWIFT_CODE );
            SetDlgItemText( IDC_LBL_INST_CODE, cstrTemp );
         }
         else
         {
            CString cstrTemp;
            cstrTemp.LoadString( IDS_LBL_NBR );
            SetDlgItemText( IDC_LBL_INST_CODE, cstrTemp );
         }
      }
      else if( dstrMarket == MARKET_IDS::JAPAN )
      {
         GetDlgItem( IDC_LBL_ACC_NAME )->ShowWindow( nCmdShow );
         GetDlgItem( IDC_TXT_ACC_NAME )->ShowWindow( nCmdShow );
         GetDlgItem( IDC_LBL_INST_CODE )->ShowWindow( SW_HIDE );
         GetDlgItem( IDC_TXT_INST_CODE )->ShowWindow( SW_HIDE );
      }
   }

   GetDlgItem( IDC_BTN_BANK )->ShowWindow( nCmdShow );
}

//******************************************************************************

void SystematicDlg::getPayType(DString& dstrOut) const
{
   DString dstrTransType, dstrPayType;

   getParent()->getField(this, m_lContainerID, ifds::TransType, dstrTransType, false);
   getParent()->getField(this, m_lContainerID, ifds::PayType, dstrPayType, false);
   if( dstrTransType.strip() != NULL_STRING || dstrPayType.strip() != NULL_STRING )
   {
      if( dstrTransType == TRADETYPE::AUTO_TRANSFER )
         dstrOut = dstrTransType;
      else
         dstrOut = dstrTransType.strip() + I_("-") + dstrPayType.strip();

      dstrOut.upperCase();
   }
   else
      dstrOut = BLANK_STRING;
}

//********************************************************************************

bool SystematicDlg::isToFundClassAccountEmpty() const
{
   DString accountTo,FundTo,ClassTo;
   if( isATTransfer() )
   {
      getParent()->getField(this, m_lContainerID, ifds::AccountTo,accountTo);   
      getParent()->getField(this, m_lContainerID, ifds::FundToCode,FundTo);   
      FundTo.strip();
      getParent()->getField(this, m_lContainerID, ifds::ClassToCode,ClassTo);   
      ClassTo.strip();
      if( ClassTo.empty() && accountTo.empty() && FundTo.empty() )
         return(true);
   }
   return(false);
}

//******************************************************************************

void SystematicDlg::getAddrCodeDesc(DString& dstrOut) const
{
   DString dstrAddrCode, dstrAddrDesc;

   getParent()->getField(this, m_lContainerID, ifds::AddrCode, dstrAddrCode, false);
   dstrAddrCode.strip();

   getParent()->getField(this, m_lContainerID, ifds::AddrCode, dstrAddrDesc);
   dstrAddrDesc.strip();

   if( !dstrAddrDesc.empty() )
   {
      dstrOut = dstrAddrDesc;
   }
   else
   {
      CString strTemp;
      DString dstrCode, dstrDesc, dstrTemp;
      DSTComboBox* pComboBox = dynamic_cast<DSTComboBox*>(GetDlgItem(IDC_CMB_ADDRESS_CODE));
      for( int i = 0; i < pComboBox->GetCount(); i++ )
      {
         pComboBox->GetLBText(i, strTemp);
         dstrTemp = (LPCTSTR)strTemp;
         parsingCombinedField(dstrTemp, dstrCode, dstrDesc, I_(" "));
         if( dstrCode == dstrAddrCode )
            dstrOut = dstrTemp;
      }
   }
}

//******************************************************************************
void SystematicDlg::switchFrequency(const DString& dstrValue)
{
   bool bMonthly;

   if( dstrValue == FREQ_DAILY || dstrValue == FREQ_WEEKLY || dstrValue == FREQ_BIWEEKLY )
      bMonthly = false;
   else
      bMonthly = true;

   ShowMonthOrWeek(bMonthly);                
}

//************************************************************

void SystematicDlg::ShowMonthOrWeek(bool bMonth)
{
   DString dstrTransType;
   getParent()->getField(this, m_lContainerID, ifds::TransType, dstrTransType, false);
   if( bMonth )
   {
      (CWnd *)GetDlgItem(IDC_LBL_UP_MONTHLY)->ShowWindow(SW_SHOW);
      (CWnd *)GetDlgItem(IDC_TXT_MONTHLY)->ShowWindow(SW_SHOW);
      (CWnd *)GetDlgItem(IDC_EDT_MONTHLY)->ShowWindow(SW_SHOW);
      (CWnd *)GetDlgItem(IDC_TXT_DAY_OF_WEEK)->ShowWindow(SW_HIDE);
      (CWnd *)GetDlgItem(IDC_CMB_DAY_OF_WEEK)->ShowWindow(SW_HIDE);
      ConnectControlToData(IDC_CMB_EOM,true);
      LoadControl(IDC_CMB_EOM);

      (CWnd *)GetDlgItem(IDC_CMB_EOM)->ShowWindow(SW_SHOW);
      (CWnd *)GetDlgItem(IDC_TXT_EOM)->ShowWindow(SW_SHOW);
   }
   else
   {
      (CWnd *)GetDlgItem(IDC_LBL_UP_MONTHLY)->ShowWindow(SW_HIDE);
      if( dstrTransType != TRADETYPE::AUTO_TRANSFER )
      {
         (CWnd *)GetDlgItem(IDC_EDT_MONTHLY)->ShowWindow(SW_HIDE);
      }
      (CWnd *)GetDlgItem(IDC_TXT_DAY_OF_WEEK)->ShowWindow(SW_SHOW);
      (CWnd *)GetDlgItem(IDC_CMB_DAY_OF_WEEK)->ShowWindow(SW_SHOW);
      ConnectControlToData(IDC_CMB_EOM,false);
      (CWnd *)GetDlgItem(IDC_CMB_EOM)->ShowWindow(SW_HIDE);
      (CWnd *)GetDlgItem(IDC_TXT_EOM)->ShowWindow(SW_HIDE);
   }
}


//******************************************************************************

void SystematicDlg::refreshSystematicAlloctions()
{
   const DString *pCurKey = &(getParent()->getCurrentListItemKey(this, m_lContainerID));
   const DString *pCurAllocKey = &(getParent()->getCurrentListItemKey(this, IFASTBP_PROC::SYSALLOCATION_LIST));

   DString dstrValue( NULL_STRING );
   DString dstrFundCode, dstrClassCode;
   const DString *pKey = &getParent()->getFirstListItemKey(this, m_lContainerID);
   while( *pKey != NULL_STRING )
   {
      getParent()->setCurrentListItem(this, m_lContainerID, *pKey);

      int iItemNumber = getParent()->getNumberOfItemsInList(this, IFASTBP_PROC::SYSALLOCATION_LIST);
      if( iItemNumber > 1 )
      {
         getParent()->getField(this, m_lContainerID, ifds::FundCode,   dstrFundCode, false);
         getParent()->getField(this, m_lContainerID, ifds::ClassCode,  dstrClassCode, false);
         dstrFundCode.strip().upperCase();
         dstrClassCode.strip().upperCase();
         DString strMarket = DSTCommonFunctions::getMarket();

         if( !dstrFundCode.empty() || !dstrClassCode.empty() )
         {
            //clear fund/class field
            getParent()->setField(this, m_lContainerID, ifds::FundCode,     NULL_STRING, false);
            getParent()->setField(this, m_lContainerID, ifds::ClassCode,    NULL_STRING, false);
            getParent()->setField(this, m_lContainerID, ifds::FrFundNumber, NULL_STRING, false);
         }
         getParent()->send(this,SYSTEMATICLIT::MULTI_ALLOCATION);
      }
      else if( iItemNumber == 1 )
      {
         getParent()->getField(this, m_lContainerID, ifds::FundCode,  dstrFundCode, false);
         getParent()->getField(this, m_lContainerID, ifds::ClassCode, dstrClassCode,false);
         dstrFundCode.strip().upperCase();
         dstrClassCode.strip().upperCase();

         getParent()->getFirstListItemKey( this, IFASTBP_PROC::SYSALLOCATION_LIST );
         DString dstrAllocFund, dstrAllocClass;
         getParent()->getField(this, IFASTBP_PROC::SYSALLOCATION_LIST, ifds::FundCode,  dstrAllocFund, false);
         getParent()->getField(this, IFASTBP_PROC::SYSALLOCATION_LIST, ifds::ClassCode, dstrAllocClass, false);
         dstrAllocFund.strip().upperCase();
         dstrAllocClass.strip().upperCase();
         if( dstrFundCode != dstrAllocFund )
            getParent()->setField(this, m_lContainerID, ifds::FundCode,  dstrAllocFund, false);
         if( dstrClassCode != dstrAllocClass )
            getParent()->setField(this, m_lContainerID, ifds::ClassCode, dstrAllocClass, false);
      }
      pKey = &getParent()->getNextListItemKey(this, m_lContainerID);
   }
   if( *pCurKey != NULL_STRING )
   {
      getParent()->setCurrentListItem(this, m_lContainerID, *pCurKey);
      LoadControl(IDC_CMB_TYPE);
   }
}

//******************************************************************************** 

void SystematicDlg::SetAtFromAlloctions()
{
   const DString *pSysCurKey = &(getParent()->getCurrentListItemKey(this, m_lContainerID));

   DString dstrFundCode, dstrClassCode, dstrAccount;
   int iAcctItemNum(0),iFundItemNum(0);      

   iAcctItemNum = getParent()->getNumberOfItemsInList(this, IFASTBP_PROC::AT_ACCOUNT_ALLOCATIONLIST);
   if( iAcctItemNum > 0 )
      iFundItemNum = getParent()->getNumberOfItemsInList(this, IFASTBP_PROC::AT_FUND_ALLOCATIONLIST);
   if( isATTransfer() )
   {
      if( iAcctItemNum > 1 || iFundItemNum >1 )
      {
         getParent()->getField(this, m_lContainerID, ifds::FundToCode,  dstrFundCode,  false);
         getParent()->getField(this, m_lContainerID, ifds::ClassToCode, dstrClassCode, false);
         getParent()->getField(this, m_lContainerID, ifds::AccountTo,   dstrAccount,   true);
         dstrFundCode.strip().upperCase();
         dstrClassCode.strip().upperCase();
         dstrAccount.strip().stripLeading(I_('0'));
         if( !dstrFundCode.empty() )
            getParent()->setField(this, m_lContainerID, ifds::FundToCode,  NULL_STRING, false);
         if( !dstrClassCode.empty() )
            getParent()->setField(this, m_lContainerID, ifds::ClassToCode, NULL_STRING, false);
         if( !dstrAccount.empty() )
            getParent()->setField(this, m_lContainerID, ifds::AccountTo,   NULL_STRING, false);
      }
      else if( iAcctItemNum == 1 && iFundItemNum == 1 )
      {
         getParent()->getFirstListItemKey( this, IFASTBP_PROC::AT_ACCOUNT_ALLOCATIONLIST );
         getParent()->getFirstListItemKey( this, IFASTBP_PROC::AT_FUND_ALLOCATIONLIST );
         getParent()->getField(this, IFASTBP_PROC::AT_ACCOUNT_ALLOCATIONLIST, ifds::AllocAccountNum,  dstrAccount,  false);
         getParent()->getField(this, IFASTBP_PROC::AT_FUND_ALLOCATIONLIST,    ifds::FundCode,         dstrFundCode, false);
         getParent()->getField(this, IFASTBP_PROC::AT_FUND_ALLOCATIONLIST,    ifds::ClassCode,        dstrClassCode,false);
         getParent()->setField(this, m_lContainerID, ifds::FundToCode,  dstrFundCode,  false);
         getParent()->setField(this, m_lContainerID, ifds::ClassToCode, dstrClassCode, false);
         getParent()->setField(this, m_lContainerID, ifds::AccountTo,   dstrAccount,   false);
      }
      if( *pSysCurKey != NULL_STRING )
         getParent()->setCurrentListItem(this, m_lContainerID, *pSysCurKey);
   }
}

//******************************************************************************

bool SystematicDlg::doRefresh(GenericInterface * rpGICaller,const I_CHAR * szOriginalCommand)
{  
   getParent()->getField(this, ifds::AccountNum, m_dstrAccountNum);

   SetAccount(m_dstrAccountNum.strip());
//   SetAccountCaption();
   DString dstrShrNum, dstrEntityName;
   getParent()->getField( this, ifds::ShrNum,    dstrShrNum );
   getParent()->getField( this, SYSTEMATICLIT::PRIMARY_ACCOUNT_OWNER, dstrEntityName );
   SetShrAcctCaption(dstrShrNum, m_dstrAccountNum, dstrEntityName);

   //reload the address code
   DSTComboBox* pComboBox = dynamic_cast<DSTComboBox*>(GetDlgItem(IDC_CMB_ADDRESS_CODE));
   pComboBox->FillInListValues(IFASTBP_PROC::ADDRESS_LIST, ifds::AddrCode);

   populateData();

   UpdateData(FALSE);

   return(true);
}

//******************************************************************
void SystematicDlg::OnBtnHistorical()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnHistorical"));
   CWaitCursor wait;
   
   IFastHistoricalInfo f;
   f( this, IFASTBP_PROC::SYSTEMATIC_LIST);
}

//******************************************************************************
void SystematicDlg::OnBtnBank() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnBank" ) );

   CWaitCursor wait;

   try
   {
      DString dstrPACSWPId;

      getParent()->getField(this, IFASTBP_PROC::SYSTEMATIC_LIST, 
         ifds::PACSWPId, dstrPACSWPId, false);
      setParameter(MFCAN_IP_PARAM::ACCOUNT_NUM, m_dstrAccountNum);
      setParameter(MFCAN_IP_PARAM::BANK_TYPE, BANKTYPE::SYSTEMATIC);
      setParameter(MFCAN_IP_PARAM::LIST_KEY, dstrPACSWPId);

      E_COMMANDRETURN eRtn = invokeCommand(getParent(), 
         CMD_BPROC_BANK_INSTRUCTIONS, PROC_SUPPORT, true, NULL);

      if (eRtn != CMD_CANCEL)
      {
         LoadControl(IDC_TXT_BANK_NAME);
         LoadControl(IDC_TXT_ACC_NAME);
         LoadControl(IDC_EDT_ACC_NBR);
         RefreshListItem(IDC_LV_SYSTEMATIC);
         //Reinit the grid
         ReInitGrid(CLASSNAME, IDC_GRID_OPTION, GRID_NAME, m_lContainerID, 
            IDC_LV_SYSTEMATIC, ifds::SystematicGridHeading, 
            m_idOldGridSubstitution);
         showPayType();
      }
   }
   catch (ConditionException &ce)
   {
      ConditionMessageBox(ce);
   }
   catch (...)
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }
}

//******************************************************************************

void SystematicDlg::OnBtnAllocation() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnBank" ) );
   

   CWaitCursor wait;
   try
   {
      /**
         The following code is indentionally to clear the Fund and the Class combo.
         After the allocation is finished, the Fund and Class in systemation list will be
         changed accordingly.
      */
      m_bBtnAllocation = true;

      DString strTransType;
      const DString *pCurKey = 
         &(getParent()->getCurrentListItemKey(this, m_lContainerID));

      getParent()->getField(this, IFASTBP_PROC::SYSTEMATIC_LIST, 
         ifds::TransType, strTransType, false);
      setParameter (MFCAN_IP_PARAM::TRANS_TYPE, strTransType);
      //passes the current Systematic list key
      setParameter (MFCAN_IP_PARAM::LIST_KEY, *pCurKey);
      //the current account number
      setParameter (MFCAN_IP_PARAM::ACCOUNT_NUM, m_dstrAccountNum);
      //the caller is Systematic
      setParameter (MFCAN_IP_PARAM::CALLER, I_("Systematic"));

      if (isATTransfer())      
      {
         // pass automatic transfer to allocation process
         setParameter (ALLOCATIONSPROC::ALLOCATION_TYPE, 
            ALLOCATIONSPROC::SYSTEMATIC_AUTO_TRANSFER);
      }
      else
      {
         setParameter (ALLOCATIONSPROC::ALLOCATION_TYPE, 
            ALLOCATIONSPROC::SYSTEMATIC_ONE_TIME);
      }

      E_COMMANDRETURN eRtn = 
         invokeCommand(getParent(), CMD_BPROC_ALLOCATIONS, 
         PROC_SUPPORT, true, NULL);

      if (eRtn != CMD_CANCEL)
      {
         if (isATTransfer())
         {
            SetAtFromAlloctions();
            showPayType();
            RefreshListItem(IDC_LV_SYSTEMATIC);
            populateAllocations();
            switchAllocAmountTypeColumn();
         }
         else
         {
            //update the allocation fund in systematic list
            refreshSystematicAlloctions();
            LoadListControl(IDC_LV_SYSTEMATIC, pCurKey);
            LoadListControl(IDC_LV_ALLOCATION);
         }
      }
   }
   catch (ConditionException &ce)
   {
      ConditionMessageBox( ce );
   }
   catch ( ... )
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }
   m_bBtnAllocation = false;
}

//******************************************************************************

void SystematicDlg::OnBtnAdmDates() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_(" OnBtnAdminDates() " ) );
   DString str;

   getParent()->getField( this, m_lContainerID, ifds::ModUser, str );
   str.strip();
   setParameter(MODUSER, str );
   getParent()->getField( this, m_lContainerID, ifds::ModDate, str );
   str.strip();
   setParameter(MODDATE, str );
   getParent()->getField( this, m_lContainerID, ifds::ProcessDate, str );
   str.strip();
   setParameter(PROCESSDATE, str );
   getParent()->getField( this, m_lContainerID, ifds::Username, str );
   str.strip();
   setParameter(PROCESSUSER, str );

   try
   {
      bool bModal = false;   // Default to modeless
      E_COMMANDRETURN eRtn;
      eRtn = invokeCommand( getParent(), CMD_BPROC_ADMINDATES, PROC_NO_TYPE, true, NULL );
      switch( eRtn )
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

void SystematicDlg::OnBtnNew() 
{ 
   AddToListControl(IDC_LV_SYSTEMATIC);
   if( isATTransfer() )
   {
      ConnectControl(IDC_EDT_AT_FUND,true);
      DString strMarket = DSTCommonFunctions::getMarket();

      if( strMarket == MARKET_IDS::JAPAN )
         ConnectControl(IDC_CMB_AT_ACCT_TO,true);
      else ConnectControl(IDC_EDT_AT_ACCT_TO,true);
      ConnectControl(IDC_EDT_AT_CLASS,true);

   }
   DString strKey = GetList( IDC_LV_SYSTEMATIC )->GetCurrentKey();
   if( !strKey.empty() )
   {
      getParent()->setCurrentListItem( this, m_lContainerID, strKey );
      enableDisableAllocation();
   }

  // FocusOnControl(IDC_CMB_PAYTYPE);
}

//******************************************************************************

void SystematicDlg::OnBtnDelete() 
{
   DeleteFromListControl( IDC_LV_SYSTEMATIC );
}

//******************************************************************************

void SystematicDlg::OnBtnAddress() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnAddress" ) );

   SetMessageStatusBar( TXT_LOAD_ADDRESS_BOOK );

   CWaitCursor wait;
   E_COMMANDRETURN eRtn;
   bool bModal = true;   // Default to modal
   try
   {
      DString dstrTemp;
      dstrTemp = NULL_STRING;
      setParameter(SHAREHOLDER_NUM,   dstrTemp);
      setParameter(ACCOUNT_NUM,       m_dstrAccountNum);
      setParameter(ENTITY_ID,         m_dstrEntityID);

      getParent()->getField(this, m_lContainerID, ifds::AddrCode, dstrTemp, false);
      dstrTemp.strip();
      setParameter( ADDRESS_CODE,      dstrTemp );

      //eRtn = getParentProcess()->invokeProcessFromChild( this, CMD_BPROC_ADDRESSES, PROC_SUPPORT );
      eRtn = invokeCommand(getParent(), CMD_BPROC_ADDRESSES, PROC_SUPPORT, true, NULL);
      if( eRtn != CMD_CANCEL )
      {
         RefreshListItem(IDC_LV_SYSTEMATIC);

         //reload the address code
         getParameter(ADDRESS_CODE,      dstrTemp);
         dstrTemp.strip();
         clearParameters();
         if( !dstrTemp.empty() )
            getParent()->setField(this, m_lContainerID, ifds::AddrCode, dstrTemp, false);
         fillAddressCode();
         LoadControl(IDC_CMB_ADDRESS_CODE);
         if( !dstrTemp.empty() )
            fillAddress(dstrTemp);
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
   SetMessageStatusBar( NULL_STRING );
}

//******************************************************************************

void SystematicDlg::DoPreListItemChanged(
                                        UINT listControlID,
                                        const DString &strKey,
                                        bool bIsNewItem,  
                                        bool bIsDummyItem
                                        )
{

   if( listControlID == IDC_LV_ALLOCATION )
   {
      m_bAllocationItemChange = true;
   }
   else if( listControlID == IDC_LV_SYSTEMATIC )
   {
      m_bSystematicItemChange = true;
      m_bNewItem = bIsNewItem;
/*
      if( bIsDummyItem )
         FocusOnControl(IDC_CMB_PAYTYPE);*/
      /*if (!bIsNewItem)
      {
         DString dstrFrequency;
         getFrequency(dstrFrequency, false);
      }*/
   }


}

//******************************************************************************

void SystematicDlg::DoListItemChanged(UINT listControlID, const DString &strKey, bool bIsNewItem, bool bIsDummyItem)
{
   DString dstrFundCode, dstrClassCode;

   if( listControlID == IDC_LV_ALLOCATION )
   {
      m_bAllocationItemChange = false;
   }
   else if( listControlID == IDC_TXT_AT_ACCT_LIST )
   {
      populateAllocations();
   }
   else if( listControlID == IDC_LV_SYSTEMATIC )
   {
      m_bSystematicItemChange = false;
	  if(bIsNewItem || bIsDummyItem) 
	  {
		  const DString *pCurKey = &( getParent()->getCurrentListItemKey(this, m_lContainerID ) );
		  DString tmp = *pCurKey + I_(',');
		  if(openeditemkeys == NULL_STRING || openeditemkeys.find(tmp) == DString::npos )
		  {
				//PostMessage(POP_DEMOGRAPHIC);
           OpenDemographicDlg();
		        openeditemkeys += tmp;
		  }
	  }

      if( bIsDummyItem )
         FocusOnControl(IDC_CMB_PAYTYPE);

      m_bNewItem = bIsNewItem;
      //Change Allocation List Column Heading according to the AmountType
      switchAllocAmountTypeColumn();
      SetUserAccesFuncCode();

      DString str;
      getParent()->getField( this, m_lContainerID, ifds::TransType, str, false );
      GetDlgItem(IDC_BTN_INDEXING)->EnableWindow( str == TRADETYPE::PAC || str == TRANS_TYPE_SAVING_PLAN );
      //Historical button
      GetDlgItem(IDC_BTN_HISTORICAL)->EnableWindow(!bIsNewItem && !bIsDummyItem);
   }
}

//******************************************************************************
void SystematicDlg::switchAllocAmountTypeColumn()
{
   //Change Allocation List Column Heading according to the AmountType
   CString strText;
   DString dstrAmountType;
   getParent()->getField(this, ifds::AmountType, dstrAmountType, false);
   dstrAmountType.strip().upperCase();

   DSTListCtrl* pListCtrl = dynamic_cast<DSTListCtrl*>(GetDlgItem(IDC_LV_ALLOCATION));
   LVCOLUMN lvColumn;
   lvColumn.mask     = LVCF_TEXT;
   if( dstrAmountType == I_("U") )
      strText.LoadString(TXT_UNITS);
   else
      strText.LoadString(TXT_AMOUNT);
   lvColumn.pszText  = const_cast<LPTSTR>((LPCTSTR)strText);
   pListCtrl->SetColumn(4, &lvColumn);
}

//******************************************************************************

bool SystematicDlg::doSend(GenericInterface *rpGICaller,const I_CHAR * szMessage)
{//ticket 2404299 (REG_RL11.2/101 - PAC set up and delete issues)
 // throw all ERROR msg
	DString str( szMessage );
	DString dstrDisplayXrefWarning = NULL_STRING;
	getParent()->getField(this,SYSTEMATICLIT::IS_XREF_WARN_APPL,dstrDisplayXrefWarning,false );
	bool bDisplayWarning = false;
	DString dstrDisplayUCITWarning = NULL_STRING;
	DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
    const BFDataGroupId& idDataGroup = getParent()->getDataGroupId();
    if(dstWorkSession) 
      dstWorkSession->getOption( ifds::UCITFlag, dstrDisplayUCITWarning, idDataGroup, false );
    bDisplayWarning = ( dstrDisplayXrefWarning == I_("Y") ||
		                dstrDisplayUCITWarning == I_("Y") );
   if((str == I_( "ListAllErrors" ))|| 
	  (bDisplayWarning && str == I_("WarningConfirm")))
   {
	  LoadControlErrorState();

      CONDITIONVECTOR conditions;
      SEVERITY sevRtn = getParent()->getAllErrors(rpGICaller, conditions);

      CONDITIONVECTOR conditionsPacked;
      CONDITIONVECTOR::iterator iter = conditions.begin();
      while( iter != conditions.end( ) )
      {
         bool bFound(false);
         CONDITIONVECTOR::iterator iterPacked = conditionsPacked.begin();
		 DString dstrIter((*iter)->getMessage());

         while( iterPacked != conditionsPacked.end() )
         {
			DString dstrIterPacked((*iterPacked)->getMessage());
            if( (*iter)->getCode() == (*iterPacked)->getCode() &&
				dstrIter == dstrIterPacked)
            {
               bFound = true;
               break;
            }
            iterPacked++;
         }
         if( !bFound )
            conditionsPacked.push_back(*iter);

         iter++;
      }
	  if( sevRtn >= WARNING )
      {
         if( ConditionMessageBox(conditionsPacked, sevRtn) != IDOK )
            return(false);
      }
   }

   return(true);
}

//******************************************************************************

bool SystematicDlg::PreOk()
{ 

//   if (!m_bFeeLostFocus)
//      confirmAcqFee();
//   m_bFeeLostFocus = false;

   return(true);
}

//******************************************************************************

void SystematicDlg::PostOk()
{
   if( m_pFont )
   {
      m_pFont->DeleteObject();
      delete m_pFont;
      m_pFont = NULL;
   }
}

//******************************************************************************

void SystematicDlg::PostCancel()
{
   m_bScreenClose = true;
   if( m_pFont )
   {
      m_pFont->DeleteObject();
      delete m_pFont;
      m_pFont = NULL;
   }
}

//******************************************************************************
void SystematicDlg::OnBtnReset() 
{
   ResetListItem(IDC_LV_SYSTEMATIC);
   m_ckbActiveOnly.SetCheck (0);
   OnChkActiveOnly ();
}

//******************************************************************************

//******************************************************************************
/**
  *   This routine must be called before the SetCurrentList() called, (BP)
  *   This guarantees that the previous selected record is processed.
  *   Otherwise the whole mechanism will not be working properly
  */
void SystematicDlg::OnItemchangingLvSystematic(NMHDR* pNMHDR, LRESULT* pResult) 
{
   NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

   // TODO: Add your control notification handler code here
   if( pNMListView->iItem == -1 )
      return;

   if( pNMHDR->hwndFrom == GetDlgItem(IDC_LV_SYSTEMATIC)->m_hWnd )
   {
      if( LVN_SELECTED )
      {
         m_bSystematicItemChanging = false;
         DSTListCtrl* pListCtrl = GetList(IDC_LV_SYSTEMATIC);
         DString *pstrKey = (DString*)pListCtrl->GetItemData( pNMListView->iItem );
         if( m_dstrCurKey.empty() )
            m_dstrCurKey = *pstrKey;
/*         if (!m_bFeeLostFocus)
         {
            if (m_dstrCurKey != *pstrKey)
            {
               m_bSystematicItemChanging = true;
               confirmAcqFee();  
               m_dstrCurKey = *pstrKey;
            }
         }
         m_bFeeLostFocus = false;*/
      }
   }
   *pResult = 0;
}

//CP20030319//******************************************************************************
//CP20030319void SystematicDlg::getDescByCode(long lSubstituteID, DString &dstrCode, DString& dstrDesc) const
//CP20030319{
//CP20030319   DString dstrSubCode;
//CP20030319
//CP20030319   const DString *pKey = &(getParent()->getFirstListItemKey(this, lSubstituteID));
//CP20030319   while( *pKey != NULL_STRING )
//CP20030319   {
//CP20030319      getParent()->getField(this, lSubstituteID, ifds::Substitute_Code, dstrSubCode);
//CP20030319      if( dstrSubCode.strip() == dstrCode.strip() )
//CP20030319      {
//CP20030319         getParent()->getField(this, lSubstituteID, ifds::Substitute_Description, dstrDesc, false);
//CP20030319         dstrDesc.strip();
//CP20030319         return;
//CP20030319      }
//CP20030319      pKey = &(this->getParent()->getNextListItemKey(this, lSubstituteID));
//CP20030319   }
//CP20030319   dstrDesc = dstrCode;
//CP20030319}

//******************************************************************************

void SystematicDlg::OnClose() 
{
   // TODO: Add your message handler code here and/or call default
   m_bScreenClose = true; 
   BaseMainDlg::OnClose();
}

void SystematicDlg::OnBtnAddCopy() 
{
   DString dstrValue;
   getParent()->getField(this, m_lContainerID, ifds::StatusCode, dstrValue, false);
   if( dstrValue.strip() == YES )
   {
      CWaitCursor wait;      
      DString _dstrOrgKey = GetList(IDC_LV_SYSTEMATIC)->GetCurrentKey();
      m_bAddCopy = true;
      AddToListControl( IDC_LV_SYSTEMATIC );
      DString _dstrDestKey = GetList(IDC_LV_SYSTEMATIC)->GetCurrentKey();
      getParent()->setField(this, BF::NullContainerId, SYSTEMATICLIT::ORG_KEY, _dstrOrgKey);
      getParent()->setField(this, BF::NullContainerId, SYSTEMATICLIT::DEST_KEY, _dstrDestKey);    
      m_bAddCopy = false;
      RefreshListItem( IDC_LV_SYSTEMATIC );
      LoadListControl( IDC_LV_SYSTEMATIC, const_cast<DString*>(&_dstrDestKey) );
   }   
}

//******************************************************************************

LRESULT SystematicDlg::OpenFundClassListDlg( WPARAM, LPARAM )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenFundClassListDlg" ) );

   DString strMarket = DSTCommonFunctions::getMarket();
   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;
      CWaitCursor wait;      
      DString dstrShareholder;      
      getParent()->getField( this, ifds::ShrNum,    dstrShareholder );
      dstrShareholder.strip().stripLeading( I_CHAR( '0' ) );
      setParameter ( SHR_NUM , dstrShareholder );
      getParent()->getField(this, ifds::AccountNum, m_dstrAccountNum);
      m_dstrAccountNum.strip().stripLeading(I_CHAR('0'));
      setParameter ( ACCOUNT_NUM, m_dstrAccountNum );

      // Set Search Parameters (Code, Class, Number) for Fund Class Dialog
      switch( m_uiDialogItem )
      {
         case IDC_EDT_FUND:
         case IDC_EDT_AT_FUND:
            {
               CString cstrFundCode;
               GetDlgItem( m_uiDialogItem )->GetWindowText( cstrFundCode );
               DString dstrFundCode = cstrFundCode;
               setParameter( FUND_CODE, dstrFundCode );
               setParameter( CLASS_CODE, NULL_STRING );
               setParameter( FUNDNUMBER, NULL_STRING );
            }
            break;
         case IDC_EDT_CLASS:
         case IDC_EDT_AT_CLASS:
            {
               CString cstrFundClass;
               GetDlgItem( m_uiDialogItem )->GetWindowText( cstrFundClass );
               DString dstrFundClass = cstrFundClass;
               setParameter( FUND_CODE, NULL_STRING );
               setParameter( CLASS_CODE, dstrFundClass );
               setParameter( FUNDNUMBER, NULL_STRING );
            }
            break;

         case IDC_EDT_FROM_FUND:
         case IDC_EDT_TO_FUND:
            {
               CString cstrFundNumber;
               GetDlgItem( m_uiDialogItem )->GetWindowText( cstrFundNumber );
               DString dstrFundNumber = cstrFundNumber;
               setParameter( FUND_CODE, NULL_STRING );
               setParameter( CLASS_CODE, NULL_STRING );
               setParameter( FUNDNUMBER, dstrFundNumber );
            }
            break;

      }

      eRtn = invokeCommand( getParent(), CMD_BPROC_FUNDCLASS, PROC_SUPPORT, true, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               DString dstrFundCode, dstrClassCode, dstrFundNumber;
               getParameter ( FUND_CODE, dstrFundCode );
               getParameter ( CLASS_CODE, dstrClassCode );

               if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
               {
                  getParameter ( FUNDNUMBER, dstrFundNumber );
               }
               if( ( GetFocus() == GetDlgItem( IDC_EDT_FUND  ) ) || 
                   ( GetFocus() == GetDlgItem( IDC_EDT_CLASS ) ) ||
                   ( GetFocus() == GetDlgItem( IDC_EDT_FROM_FUND ) ) )
               {
                  getParent()->setField( this, m_lContainerID, ifds::FrFundNumber, dstrFundNumber );
                  getParent()->setField( this, m_lContainerID, ifds::FundCode, dstrFundCode );
                  getParent()->setField( this, m_lContainerID, ifds::ClassCode, dstrClassCode );

                  LoadControl ( IDC_EDT_FUND );
                  LoadControl ( IDC_EDT_CLASS );
                  if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
                  {
                     LoadControl ( IDC_EDT_FROM_FUND );
                  }
                  else if( strMarket == MARKET_IDS::JAPAN )
                  {
                     GetDlgItem( IDC_EDT_FROM_FUND )->ShowWindow( SW_HIDE );
                  }

               }
               else if( ( GetFocus() == GetDlgItem( IDC_EDT_AT_FUND ) ) || ( GetFocus() == GetDlgItem( IDC_EDT_AT_CLASS ) ) ||
                        ( GetFocus() == GetDlgItem( IDC_EDT_TO_FUND ) ) )
               {
                  getParent()->setField( this, m_lContainerID, ifds::ToFundNumber, dstrFundNumber );
                  getParent()->setField( this, m_lContainerID, ifds::FundToCode, dstrFundCode );
                  getParent()->setField( this, m_lContainerID, ifds::ClassToCode, dstrClassCode );

                  LoadControl ( IDC_EDT_AT_FUND );
                  LoadControl ( IDC_EDT_AT_CLASS );
                  if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
                  {
                     LoadControl ( IDC_EDT_TO_FUND );
                  }
               }
               //setFeeCurrency();
               populateAllocations();
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
   return(0);
}

//******************************************************************************
BOOL SystematicDlg::PreTranslateMessage(MSG* pMsg) 
{
   m_bEsc = false;
   if( pMsg->message == WM_KEYDOWN&&( int )( pMsg->wParam ) == VK_ESCAPE )
   {
      m_bEsc = true;

   }
   if( pMsg->message == WM_KEYDOWN && ( int )( pMsg->wParam ) == VK_F4 && !IsSelectedCtrlUpdateable() )
      return(TRUE);

   if( pMsg->message == WM_KEYDOWN&&( int )( pMsg->wParam ) == VK_F4 )
   {
      if( GetFocus() == GetDlgItem( IDC_EDT_FUND ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );      
         m_uiDialogItem = IDC_EDT_FUND;
      }
      else if( GetFocus() == GetDlgItem( IDC_EDT_FROM_FUND ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );      
         m_uiDialogItem = IDC_EDT_FROM_FUND;
      }
      else if( GetFocus() == GetDlgItem( IDC_EDT_TO_FUND ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );      
         m_uiDialogItem = IDC_EDT_TO_FUND;
      }
      else if( GetFocus() == GetDlgItem( IDC_EDT_CLASS ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );      
         m_uiDialogItem = IDC_EDT_CLASS;
      }
      else if( GetFocus() == GetDlgItem( IDC_EDT_AT_FUND ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );      
         m_uiDialogItem = IDC_EDT_AT_FUND;
      }
      else if( GetFocus() == GetDlgItem( IDC_EDT_AT_CLASS ) )
      {
         PostMessage( UM_OPENFUNDCLASSLISTDLG );      
         m_uiDialogItem = IDC_EDT_AT_CLASS;
      }
      else if( GetFocus() == GetDlgItem( IDC_EDT_AT_ACCT_TO ) )
      {
         DString strMarket = DSTCommonFunctions::getMarket();
         if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
         {
            PostMessage( WM_LAUNCH_IDENT_ACC );      
            m_uiAccItem = IDC_EDT_AT_ACCT_TO;
         }
      }

   }


   return(BaseMainDlg::PreTranslateMessage( pMsg ));
}

//******************************************************************************
bool SystematicDlg::ListViewControlFilter( long lSubstituteId, const DString * )
{
   if( lSubstituteId == ifds::SystematicListHeading.getId() )
   {
      return m_ckbActiveOnly.GetCheck() == 1 ? !isCurrentSystematicRecordInactive () : true;
	}
	else if (lSubstituteId == ifds::SysAllocListHeading.getId())
	{
		DSTListCtrl *rpList = GetList (IDC_LV_SYSTEMATIC);

		if (m_ckbActiveOnly.GetCheck() == 1 && rpList && rpList->GetItemCount () == 0)
		{
			return false;
   }
	}
	return true;
}

//******************************************************************************

void SystematicDlg::OnBtnSplitCom() {

   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnSplitCom" ) );
   E_COMMANDRETURN eRtn;

   bool bModal = true;   // Default to modeless

   CWaitCursor wait;
   try
   {
      DString dstrTransType, dstrTransTypeDesc;
      const DString *pCurKey = &(getParent()->getCurrentListItemKey(this, m_lContainerID));
      const DString *pAllocCurKey = NULL;

      getParent()->getField(this, m_lContainerID, ifds::TransType, dstrTransTypeDesc, true);
      dstrTransTypeDesc.strip();
      getParent()->getField(this, m_lContainerID, ifds::TransType, dstrTransType, false);
      dstrTransType.strip().upperCase();     

      if (dstrTransType == TRADETYPE::AUTO_TRANSFER)
      {
         setParameter(SPLITCOMM::CALLER, SPLITCOMM::SYSTEMATIC_ATALLOCATION);
         pAllocCurKey = &(getParent()->getCurrentListItemKey(this, 
            IFASTBP_PROC::AT_FUND_ALLOCATIONLIST));
      }
      else
      {
         setParameter(SPLITCOMM::CALLER, SPLITCOMM::SYSTEMATIC_ALLOCATION);
         pAllocCurKey = &(getParent()->getCurrentListItemKey(this, 
            IFASTBP_PROC::SYSALLOCATION_LIST));
      }
      setParameter(SPLITCOMM::TRANSACTION_TYPE_DESC, dstrTransTypeDesc);
      setParameter(SPLITCOMM::MAIN_LIST_KEY, *pCurKey);
      setParameter(SPLITCOMM::ALLOCATION_LIST_KEY, pAllocCurKey ? *pAllocCurKey : NULL_STRING);
      setParameter(SPLITCOMM::ACCOUNT_NUM, m_dstrAccountNum );
      eRtn = invokeCommand(getParent(), CMD_BPROC_SPLITCOMMISSION, PROC_SUPPORT, true, NULL);
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
void SystematicDlg::GetCellProperties( UINT ctrlId, 
                                       const DString &rowKey, 
                                       const DString &colKey, 
                                       BFContainerId& idContainer,
                                       BFFieldId &idField,
                                       DString& listItemKey,
                                       int& nCellState,
                                       UINT& cellCtrlType, 
                                       int& nCtrlInitMode,
                                       BFFieldId &idSubstitution,
                                       DString& comboList, 
                                       DString& mask, 
                                       int& nComboSortingMode ,
                                       DString& dstrAllowedChar )
{
   DString strMarket = DSTCommonFunctions::getMarket();
   dstrAllowedChar = NULL_STRING;
   if( ctrlId == IDC_GRID_OPTION && colKey  == _T("Value") )
   {
      if( rowKey == _T("BankAcctCurrency") )
      {
         idContainer       = m_lContainerID;
         idField           = ifds::BankAcctCurrency;
         nCellState        = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType      = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         idSubstitution    = ifds::BankAcctCurrency;
      }
      else if( rowKey == _T("SrcOfFund") )
      {
         idContainer    = m_lContainerID;
         idField        = ifds::SrcOfFund;
         idSubstitution = ifds::SrcOfFund;

         nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType   = ( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )?
                        GX_IDS_CTRL_CBS_DROPDOWNLIST : GX_IDS_CTRL_STATIC;
      }
      else if( rowKey == _T("SourceOfBankAcct") )
      {
         idContainer    = m_lContainerID;
         idField        = ifds::SourceOfBankAcct;
         nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType   = ( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )?
                        GX_IDS_CTRL_EDIT : GX_IDS_CTRL_STATIC;
      }
      else if( rowKey == _T("GrossOrNet") )
      {
         idContainer       = m_lContainerID;
         idField           = ifds::GrossOrNet;
         idSubstitution    = ifds::GrossOrNet;
         nCellState        = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType      = GX_IDS_CTRL_CBS_DROPDOWNLIST;
      }
      else if( rowKey == _T("Fee") )
      {
         idContainer    = m_lContainerID;
         idField        = ifds::Fee;
         nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType   = IDS_CTRL_NUMEDIT;
      }
      else if( rowKey == _T("FeeCurrency") )
      {
         idContainer    = m_lContainerID;
         idField        = ifds::FeeCurrency;
         nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType   = GX_IDS_CTRL_STATIC;
      }
      else if( rowKey == _T("ExchInFee") )
      {
         idContainer    = m_lContainerID;
         idField        = ifds::ExchInFee;
         nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType   = IDS_CTRL_NUMEDIT;
      }
      else if( rowKey == _T("ExchInFlatPercent") )
      {
         idContainer       = m_lContainerID;
         idField           = ifds::ExchInFlatPercent;
         idSubstitution    = ifds::ExchInFlatPercent;
         nCellState        = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType      = GX_IDS_CTRL_CBS_DROPDOWNLIST;
      }

      else if( rowKey == _T("ExchOutFee") )
      {
         idContainer    = m_lContainerID;
         idField        = ifds::ExchOutFee;
         nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType   = IDS_CTRL_NUMEDIT;
      }
      else if( rowKey == _T("ExchOutFlatPrcnt") )
      {
         idContainer       = m_lContainerID;
         idField           = ifds::ExchOutFlatPrcnt;
         idSubstitution    = ifds::ExchInFlatPercent;
         nCellState        = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType      = GX_IDS_CTRL_CBS_DROPDOWNLIST;
      }

      else if( rowKey == _T("AdminFeeAmt") )
      {
         idContainer    = m_lContainerID;
         idField        = ifds::AdminFeeAmt;
         nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType   = GX_IDS_CTRL_EDIT;
      }
      else if( rowKey == _T("AdminFeeCurr") )
      {
         idContainer    = m_lContainerID;
         idField        = ifds::AdminFeeCurr;
         nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType   = GX_IDS_CTRL_STATIC;
      }
      else if( rowKey == _T("FlatPercent") )
      {
         idContainer       = m_lContainerID;
         idField           = ifds::FlatPercent;
         idSubstitution    = ifds::FlatPercent;
         nCellState        = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType      = GX_IDS_CTRL_CBS_DROPDOWNLIST;
      }
      else if( rowKey == _T("SplitComm") )
      {
         idContainer    = m_lContainerID;
         idField        = ifds::SplitComm;
         nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType   = GX_IDS_CTRL_STATIC;
      }
      else if( rowKey == _T("BELFee") )
      {
         idContainer       = m_lContainerID;
         idField           = ifds::BELFee;
         idSubstitution    = ifds::BELFee;
         nCellState        = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType      = GX_IDS_CTRL_CBS_DROPDOWNLIST;
      }
      else if( rowKey == _T("StatusCode") )
      {
         idContainer       = m_lContainerID;
         idField           = ifds::StatusCode;
         idSubstitution    = ifds::StatusCode;
         nCellState        = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType      = GX_IDS_CTRL_CBS_DROPDOWNLIST;
      }
      else if( rowKey == _T("AnnualMaint") )
      {
         idContainer       = m_lContainerID;
         idField           = ifds::AnnualMaint;
         idSubstitution    = ifds::AnnualMaint;
         nCellState        = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType      = GX_IDS_CTRL_CBS_DROPDOWNLIST;
      }
      else if( rowKey == _T("InitialAmt") )
      {
         idContainer    = m_lContainerID;
         idField        = ifds::InitialAmt;
         nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType   = GX_IDS_CTRL_EDIT;
      }
      else if( rowKey == _T("VUBFeeType") )
      {
         idContainer    = m_lContainerID;
         idField        = ifds::VUBFeeType;
         idSubstitution = ifds::VUBFeeType;
         nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType   = GX_IDS_CTRL_STATIC;
      }
      else if( rowKey == _T("VUBExpectedAmt") )
      {
         idContainer    = m_lContainerID;
         idField        = ifds::VUBExpectedAmt;
         nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType   = GX_IDS_CTRL_EDIT;
      }
      else if( rowKey == _T("VUBCollectedAmt") )
      {
         idContainer    = m_lContainerID;
         idField        = ifds::VUBCollectedAmt;
         nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType   = GX_IDS_CTRL_EDIT;
      }
      else if( rowKey == _T("InitialVUBFee") )
      {
         idContainer    = m_lContainerID;
         idField        = ifds::InitialAmt;
         nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType   = GX_IDS_CTRL_EDIT;
      }
      else if( rowKey == _T("VUBFee") )
      {
         idContainer    = m_lContainerID;
         idField        = ifds::VUBFee;
         nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType   = GX_IDS_CTRL_EDIT;
         /*
          cellCtrlType = GX_IDS_CTRL_MASKEDIT;
          mask = I_("###/###");
         */
      }
      else if( rowKey == _T("VUBPayOption") )
      {
         idContainer       = m_lContainerID;
         idField           = ifds::VUBPayOption;
         nCellState        = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType      = GX_IDS_CTRL_CBS_DROPDOWNLIST;
      }
      else if( rowKey == _T("AnnualFeeDate") )
      {
         idContainer    = m_lContainerID;
         idField        = ifds::AnnualFeeDate;
         nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType   = GX_IDS_CTRL_STATIC;
      }
      else if( rowKey == _T("BatchName") )
      {
         idContainer    = m_lContainerID;
         idField        = ifds::BatchName;
         nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType   = GX_IDS_CTRL_STATIC;
      }
      else if( rowKey == _T("BatchTrace") )
      {
         idContainer    = m_lContainerID;
         idField        = ifds::BatchTrace;
         nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType   = GX_IDS_CTRL_STATIC;
      }
      else if( rowKey == _T("PayMethod") )
      {
         idContainer       = m_lContainerID;
         idField           = ifds::PayMethod;
         nCellState        = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType      = GX_IDS_CTRL_CBS_DROPDOWNLIST;
      }
      else if( rowKey == _T("ACHProcessor") )
      {
         idContainer = m_lContainerID;
         idField     = ifds::ACHProcessor;
         nCellState  = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType = GX_IDS_CTRL_CBS_DROPDOWNLIST;
      }
      else if( rowKey == _T("FedTaxPUDOverride") )
      {
         idContainer       = m_lContainerID;
         idField           = ifds::FedTaxPUDOverride;
         bool bUpdate      = getParent()->hasUpdatePermission(  UAF::SWP_TAX_OVERRIDE );
         nCellState        = bUpdate? 
                             DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY : 
                             DSTGridWnd::CELL_STATE::READ_ONLY;
         cellCtrlType      = GX_IDS_CTRL_CBS_DROPDOWNLIST;
      }
      else if( rowKey == _T("FedRate") )
      {
         idContainer    = m_lContainerID;
         idField        = ifds::FedRate;
         bool bUpdate   = getParent()->hasUpdatePermission(  UAF::SWP_TAX_OVERRIDE );
         nCellState     = bUpdate? 
                          DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY : 
                          DSTGridWnd::CELL_STATE::READ_ONLY;
         cellCtrlType   = GX_IDS_CTRL_EDIT;
      }
      else if( rowKey == _T("ProvTaxPUDOverride") )
      {
         idContainer       = m_lContainerID;
         idField           = ifds::ProvTaxPUDOverride;
         bool bUpdate      = getParent()->hasUpdatePermission(  UAF::SWP_TAX_OVERRIDE );
         nCellState        = bUpdate? 
                             DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY : 
                             DSTGridWnd::CELL_STATE::READ_ONLY;
         cellCtrlType      = GX_IDS_CTRL_CBS_DROPDOWNLIST;
      }
      else if( rowKey == _T("ProvRate") )
      {
         idContainer    = m_lContainerID;
         idField        = ifds::ProvRate;
         bool bUpdate   = getParent()->hasUpdatePermission(  UAF::SWP_TAX_OVERRIDE );
         nCellState     = bUpdate? DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY : DSTGridWnd::CELL_STATE::READ_ONLY;
         cellCtrlType   = GX_IDS_CTRL_EDIT;
      }
      else if( rowKey == _T("StopReason") )
      {
         idContainer       = m_lContainerID;
         idField           = ifds::StopReasonPAC;
         bool bUpdate      = getParent()->hasUpdatePermission(  UAF::SWP_TAX_OVERRIDE );
         nCellState        = bUpdate? 
                             DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY : 
                             DSTGridWnd::CELL_STATE::READ_ONLY;
         cellCtrlType      = GX_IDS_CTRL_CBS_DROPDOWNLIST;
      }
      else if( rowKey == _T("VerifyStat") )
      {
         idContainer       = m_lContainerID;
         idField           = ifds::VerifyStat;
         nCellState        = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType      = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         idSubstitution    = ifds::VerifyStat;
      }
      else if( rowKey == _T("NonFinConfirms") )
      {
         idContainer       = m_lContainerID;
         idField           = ifds::NonFinConfirms;
         nCellState        = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType      = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         idSubstitution    = ifds::NonFinConfirms;
      }
      else if( rowKey == _T("RDRAdvice") )
      {
         idContainer       = m_lContainerID;
         idField           = ifds::RDRAdvice;
         nCellState        = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
         cellCtrlType      = GX_IDS_CTRL_CBS_DROPDOWNLIST;
         idSubstitution    = ifds::RDRAdvice;
      }
	  else if (rowKey == I_("EventReceiptDate"))
      {
            idContainer    = m_lContainerID;
            idField        = ifds::EventReceiptDate;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_DATETIME;  
      }
      else if (rowKey == I_("EventReceiptTime"))
      {
            idContainer    = m_lContainerID;
            idField        = ifds::EventReceiptTime;
			nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
			cellCtrlType   = GX_IDS_CTRL_EDIT;
			//mask           = I_ ("##:##:##");
              
      }
     else if (I_("PSDAdvice")== rowKey )
	 {
			 idContainer    = m_lContainerID;
			 idField        = ifds::PSDAdvice;
			 idSubstitution = ifds::PSDAdvice;
			 nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
			 cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
	 }
	 else if (I_("Platform") == rowKey )
	 {
			idContainer    = m_lContainerID;
			idField        = ifds::Platform;
			idSubstitution = ifds::Platform;
			nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
			cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
	 }
	 else if (I_("SourceOfTrade") == rowKey )
	 {
			idContainer    = m_lContainerID;
			idField        = ifds::SourceOfTrade;
			idSubstitution = ifds::SourceOfTrade;
			nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
			cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
	 }
	 else if (I_("ChannelOfTrade") == rowKey )
	 {
			idContainer    = m_lContainerID;
			idField        = ifds::ChannelOfTrade;
			idSubstitution = ifds::ChannelOfTrade;
			nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
			cellCtrlType   = GX_IDS_CTRL_CBS_DROPDOWNLIST;
	 }
	 else if ( I_("SignatureDate") == rowKey )
	 {
	        idContainer    = m_lContainerID;
            idField        = ifds::SignatureDate;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_DATETIME;
	 }
	 else if ( I_("YearlyAmount") == rowKey )
	 {
	        idContainer    = m_lContainerID;
            idField        = ifds::YearlyAmount;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_STATIC;
	 }
	 else if ( I_("CPIRate") == rowKey )
	 {
	        idContainer    = m_lContainerID;
            idField        = ifds::CPIRate;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_STATIC;
	 }
	 else if ( I_("PayoutFactorRate") == rowKey )
	 {
	        idContainer    = m_lContainerID;
            idField        = ifds::PayoutFactorRate;
            nCellState     = DSTGridWnd::CELL_STATE::USE_FIELD_PROPERTY;
            cellCtrlType   = GX_IDS_CTRL_STATIC;
	 }
   }
}

//********************************************************************
bool SystematicDlg::OnGridSetCellValue( UINT ctrlId, 
                                        const DString &rowKey, 
                                        const DString &colKey, 
                                        const DString &strIn)
{
   if( ctrlId == IDC_GRID_OPTION && colKey  == _T("Value") )
   {
      if (rowKey == _T ("FlatPercent"))
      {
         DSTGridWnd *pGrid = GetGrid (ctrlId);
         if (pGrid)
         {
            pGrid->reloadCell (I_("Fee"), I_("Value"));
         }
      }
      else if( rowKey == _T("BankAcctCurrency") ) // settle currency
      {
         if( !m_bSystematicItemChange && !strIn.empty() )
         {
            LoadControl(IDC_EDT_AMOUNT);
            populateAllocations();
            return(true);
         }
      }
      else if( rowKey == _T("StatusCode") ) // StatusCode
      {
         DString strIsFundLimitedByBankuptcy;      
         getParent()->getField(this, BF::NullContainerId, SYSTEMATICLIT::IsFundLimitedByBankuptcy, strIsFundLimitedByBankuptcy, false);   
         strIsFundLimitedByBankuptcy.strip().upperCase();

         DString dstrFundAlloc;
         getParent()->getField(this, ifds::FundAlloc, dstrFundAlloc, false);
         dstrFundAlloc.strip();

         BOOL bAllocBtnEnable = strIn == YES && 
                              (strIsFundLimitedByBankuptcy == NO);

         GetDlgItem(IDC_BTN_BANK)->EnableWindow( bAllocBtnEnable );
         GetDlgItem(IDC_BTN_ALLOCATION)->EnableWindow( bAllocBtnEnable && dstrFundAlloc != I_("N"));
         GetDlgItem(IDC_BTN_SPLIT_COM)->EnableWindow( bAllocBtnEnable );
//       GetDlgItem(IDC_BTN_INDEXING)->EnableWindow( strIn == YES );
      }
      else if ( rowKey == _T( "PayMethod" ) )
      {
         DString dstrTransType, dstrPayType, dstrPayMethod;
         getParent()->getField(this, SYSTEMATICLIT::TRANS_TYPE_PARAM, dstrTransType );
         getParent()->getField( this, ifds::PayType,   dstrPayType );
         getParent()->getField( this, ifds::PayMethod, dstrPayMethod, false );

         dstrPayType.strip().upperCase();
         dstrPayMethod.strip().upperCase();

         int iShowBank    = SW_HIDE,
            iShowAddress = SW_HIDE;


         if( ( dstrTransType == TRADETYPE::PAC || dstrTransType == TRADETYPE::SWP ) &&
            I_( "E" ) == dstrPayType )
         {
            if ( I_( "CHQ" ) != dstrPayMethod ) 
               iShowBank    = SW_SHOW;
            else
               iShowAddress = SW_SHOW;
         }
         else if ( dstrTransType == TRANS_TYPE_SAVING_PLAN )
         {
            iShowBank    = SW_SHOW;
         }
         else if ( dstrTransType == TRANS_TYPE_SAVING_PLAN &&
            ( I_( "E" ) != dstrPayType && I_( "W" ) != dstrPayType && I_( "X" ) != dstrPayType ) )
         {
            iShowAddress = SW_SHOW;
         }

         setBankRelatedControls( iShowBank );
         setAddressRelatedControls( iShowAddress );
      }
   }
   return(false);
}

//********************************************************************
void SystematicDlg::reinitGrid( const DString& payType )
{
   bool blUseCBOSubstitutions = false;
   DString dstrSWPCustomPayoutPlan, dstrSWPPortfolioPayoutPlan;

   getParent()->getField(this, IsSWPCustomPayoutPlan, dstrSWPCustomPayoutPlan);
   getParent()->getField(this, IsSWPPortfolioPayoutPlan, dstrSWPPortfolioPayoutPlan);

   BFFieldId idHeading = ifds::SystematicGridLeftHeading;
   if( payType == TRADETYPE::AUTO_TRANSFER )
      idHeading = ifds::SystematicGridLeftHeadingAT;
   else if( payType == TRANS_TYPE_SAVING_PLAN )
      idHeading = ifds::SystematicGridLeftHeadingSavingPlan;
   else if (payType == TRADETYPE::SWP && dstrSWPCustomPayoutPlan == YES)
       idHeading = ifds::SystematicGridLeftHeadingCustomPayout;
   else if (payType == TRADETYPE::SWP && dstrSWPPortfolioPayoutPlan == YES)
       idHeading = ifds::SystematicGridLeftHeadingPortfolioPayout;
   else
      blUseCBOSubstitutions = true;

   DSTGridWnd *pGrid = GetGrid( IDC_GRID_OPTION );
   pGrid->setUseCBOSubstitutions( blUseCBOSubstitutions );

   m_idOldGridSubstitution = idHeading;

   ReInitGrid( CLASSNAME, IDC_GRID_OPTION, GRID_NAME, m_lContainerID, 
            IDC_LV_SYSTEMATIC, ifds::SystematicGridHeading, m_idOldGridSubstitution );	

}

//********************************************************************
void SystematicDlg::OpenDemographicDlg( )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenDemographicDlg" ) );
   
   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;

      DString dstrAccountNum, dstrBrokerCode, dstrKYCAccountLevel, dstrKYCRequired;

      DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
      const BFDataGroupId& idDataGroup = getParent()->getDataGroupId();
      if(dstWorkSession) 
         dstWorkSession->getOption( ifds::KYCAccountLevel, dstrKYCAccountLevel, idDataGroup, false );

      getParent()->getField(this, ifds::AccountNum, dstrAccountNum);
      MFAccount * pMFAccount = NULL;
      if( dstWorkSession->getMFAccount( getDataGroupId(), dstrAccountNum, pMFAccount ) <= WARNING )
      {
         BrokerList* pBrokerList;
         dstWorkSession->getBrokerList(pBrokerList);
         if( pBrokerList )
         {
            pMFAccount->getField(ifds::BrokerCode,	dstrBrokerCode,idDataGroup,false );
            dstrBrokerCode.strip();
            Broker*  pBroker;
            pBrokerList->getBroker(dstrBrokerCode, pBroker);
            if(pBroker )
               pBroker->getField( ifds::KYCRequired, dstrKYCRequired, idDataGroup, false);						
         }
      }

      if(dstrKYCRequired == YES && dstrKYCAccountLevel == YES)
      {
         setParameter( ACCOUNT_NUM, dstrAccountNum );

         //invoke the demographic dialog and process
         //eRtn = getParentProcess( )->invokeProcessFromChild( this,CMD_BPROC_DEMOGRAPHICS,PROC_SUPPORT );
         eRtn = invokeCommand( getParent(), CMD_BPROC_DEMOGRAPHICS, PROC_SUPPORT, true, NULL );

         switch( eRtn )
         {
            case CMD_OK:
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
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }
//   return(0);
}

//********************************************************************
void SystematicDlg::OnBtnIndexing() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnIndexing" ) );

   CWaitCursor wait;
   E_COMMANDRETURN eRtn;
   bool bModal = true;                               // Default to modal
   try
   {
      setParameter( MFCAN_IP_PARAM::ACCOUNT_NUM, m_dstrAccountNum );

      const DString *pCurKey = &(getParent()->getCurrentListItemKey(this, m_lContainerID));   
      setParameter( MFCAN_IP_PARAM::PAC_SWP_ID, *pCurKey );

      eRtn = invokeCommand(getParent(), CMD_BPROC_SYS_INDEX, PROC_SUPPORT, true, NULL);
      if( eRtn != CMD_CANCEL )
      {
         LoadListControl(IDC_LV_SYSTEMATIC, pCurKey);
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

void SystematicDlg::OnKillfocusEdtMonthly() 
{
   // TODO: Add your control notification handler code here
   if( m_bScreenClose ) return;
   LoadControl(IDC_EDT_MONTHLY);
}

//*******************************************************************************
void SystematicDlg::OnKillfocusCmbPayType()
{
   DString dstrValue;
   if( m_bScreenClose ) return;
   DSTComboBox* pCmb = dynamic_cast<DSTComboBox* >(GetControl(IDC_CMB_PAYTYPE) );
   if( pCmb )
   {
      int i = pCmb->GetCurSel();
      if( i >= 0 )
      {
         dstrValue = *reinterpret_cast< DString * >( pCmb->GetItemData( i )  );
         if( !m_bEsc )
            getParent()->setField(this,IFASTBP_PROC::SYSTEMATIC_LIST, ifds::SystematicPayType,dstrValue,true);
      }
   }
}

//********************************************************************
LRESULT SystematicDlg::OpenIdentifyAccountsDlg( WPARAM,LPARAM )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION,CLASSNAME,I_( "OpenIdentifyAccountsDlg" ) );   
   bool bRetVal = false;
   BaseControl *pBC = NULL;
   try
   {
      setParameter( IDENTACCPROC::FROM_SYSTEMATIC, I_("Y") );

      switch( getParentProcess( )->invokeProcessFromChild( this,CMD_BPROC_IDENT_ACC,PROC_SUPPORT ) )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               DString dstAcctNum = NULL_STRING;
               getParameter( MFCAN_IP_PARAM::ACCOUNT_NUM, dstAcctNum );
               dstAcctNum.strip();
               if( m_uiAccItem == IDC_EDT_AT_ACCT_TO )
               {
                  bRetVal = SetControlText( IDC_EDT_AT_ACCT_TO, dstAcctNum );
                  pBC = dynamic_cast< BaseControl *> (GetDlgItem( IDC_EDT_AT_ACCT_TO ));
                  if( pBC && pBC->IsToolTipVisible() )
                     pBC->ToggleToolTip();

                  if( !bRetVal )
                  {
                     if( pBC )
                     {
                        if( pBC->IsToolTipVisible() )
                           pBC->ToggleToolTip();

                        pBC->Load();
                     }
                  }
               }

               clearParameters( );
            }
            break;
         case CMD_CANCEL:
            break;
         default:
            //Displayerror
            ConditionMessageBox( FRAMEBELOW( ),GETHIGHESTSEVERITY( ) );
            break;
      }
   }
   catch( ConditionException&ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }

   return(0);

}

//********************************************************************
void SystematicDlg::setBankRelatedControls( int iShowBank )
{
   bool bConnectBank = (iShowBank == SW_SHOW) ? true : false;

   ConnectControlToData(IDC_EDT_ACC_NBR, bConnectBank);
   ConnectControlToData(IDC_TXT_BANK_NAME, bConnectBank);
   ConnectControlToData(IDC_TXT_INST_CODE, bConnectBank);
   ConnectControlToData(IDC_TXT_TRANS_NUMBER, bConnectBank);
   if( bConnectBank )
   {
	  LoadControl( IDC_EDT_ACC_NBR );
      LoadControl( IDC_TXT_BANK_NAME );
      LoadControl( IDC_TXT_INST_CODE );
      LoadControl( IDC_TXT_TRANS_NUMBER );
   }
   /**
     *   The Bank Institute Number and Transit Number is specific to Canada
     *   The Account Name is specific to MSDW
     */
   DString strMarket = DSTCommonFunctions::getMarket();
   if( strMarket == MARKET_IDS::JAPAN )
   {
      ConnectControlToData(IDC_TXT_ACC_NAME, bConnectBank);
      if( bConnectBank )
         LoadControl(IDC_TXT_ACC_NAME);

      GetDlgItem( IDC_LBL_ACC_NAME )->ShowWindow( iShowBank );
      GetDlgItem( IDC_TXT_ACC_NAME )->ShowWindow( iShowBank );
      GetDlgItem( IDC_LBL_TRANS_NUMBER )->ShowWindow( SW_HIDE );
      GetDlgItem( IDC_TXT_TRANS_NUMBER )->ShowWindow( SW_HIDE );
      GetDlgItem( IDC_LBL_INST_CODE )->ShowWindow( SW_HIDE );
      GetDlgItem( IDC_TXT_INST_CODE )->ShowWindow( SW_HIDE );
   }
   else
   {
      GetDlgItem( IDC_LBL_ACC_NAME )->ShowWindow( SW_HIDE );
      GetDlgItem( IDC_TXT_ACC_NAME )->ShowWindow( SW_HIDE );
   }

   //dynamic_cast<CEdit *>(GetDlgItem(IDC_EDT_ACC_NBR))->SetReadOnly(true);
   ShowFromBankRelated( bConnectBank );
}

//********************************************************************
void SystematicDlg::setAddressRelatedControls( int iShowAddress )
{
   bool bEnableFlag = false;
   DString dstrStatus;
   getParent()->getField( this, m_lContainerID, ifds::StatusCode, dstrStatus, false );
   if( dstrStatus.strip() == YES || m_bNewItem )
      bEnableFlag = true;

   bool bConnectAddr = ( iShowAddress == SW_SHOW ) ? true : false;

   ConnectControlToData( IDC_CMB_ADDRESS_CODE, bConnectAddr );
   EnableControl( IDC_CMB_ADDRESS_CODE,        bConnectAddr & bEnableFlag );

   ConnectControlToData(IDC_EDT_ADDRESS,      bConnectAddr);
   dynamic_cast<CEdit *>(GetDlgItem(IDC_EDT_ADDRESS))->SetReadOnly();

   (CWnd *)GetDlgItem(IDC_BTN_ADDRESS)->EnableWindow(bConnectAddr & bEnableFlag);

   (CWnd *)GetDlgItem( IDC_LBL_ADDRESS_CODE )->ShowWindow( iShowAddress );
   (CWnd *)GetDlgItem( IDC_CMB_ADDRESS_CODE )->ShowWindow( iShowAddress );
   (CWnd *)GetDlgItem( IDC_EDT_ADDRESS )->ShowWindow( iShowAddress );
   
   //Address button
   (CWnd *)GetDlgItem( IDC_BTN_ADDRESS )->ShowWindow( iShowAddress );
   if( iShowAddress == SW_SHOW )
   {
      LoadControl( IDC_CMB_ADDRESS_CODE );
      LoadControl( IDC_EDT_ADDRESS );
   }
}
//**************************************************************************
bool SystematicDlg::HideGridRowColumn(DString& dstrTag)
{
   bool bHide = false;
   if( dstrTag == I_( "FedTaxPUDOverride" ) ||
      dstrTag == I_( "FedRate" ) ||
      dstrTag == I_( "ProvTaxPUDOverride" )||
      dstrTag == I_( "ProvRate" ) )
   {
       DString dstrValue;
       getParent()->getField(this,SYSTEMATICLIT::WHTaxApply,dstrValue,false);
       if(dstrValue == NO )
       {
         bHide = true;
       }
   


   }
   else if ( dstrTag == I_( "PayMethod" ) ||
      dstrTag == I_( "ACHProcessor" )   )
   {
       DString dstrValue;
       getParent()->getField(this, SYSTEMATICLIT::FileProcessorApply,dstrValue,false);
       if(dstrValue == NO )
       {
         bHide = true;
       }
   }
   return bHide;

}

//******************************************************************************
void SystematicDlg::OnChkActiveOnly()
{
   if (m_ckbActiveOnly.GetCheck() == 1)
   {
      //if on the last systematic inactive record we need to add a dummy one, since the inactive record(s) will be removed from display,
      //when the active only check box is checked

      DString areAllSytematicRecordsInactive (I_("N"));
      getParent()->getField (this,SYSTEMATICLIT::AreAllSytematicRecordsInactive, areAllSytematicRecordsInactive, false);
      if (areAllSytematicRecordsInactive == I_("Y"))
      {
         AddToListControl (IDC_LV_SYSTEMATIC);
      }
   }
    LoadListControl(IDC_LV_SYSTEMATIC);
}

//******************************************************************************
bool SystematicDlg::isCurrentSystematicRecordInactive ()
{
	DSTCWorkSession* pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
	DString dstrStopDate (NULL_STRING), 
		dstrRecordStatus (YES), 
		dstrCurBusDate (NULL_STRING);

	if (pDSTCWorkSession)
	{      
		getParent()->getField (this, m_lContainerID, ifds::StopDate, dstrStopDate, false);
		getParent()->getField (this, m_lContainerID, ifds::StatusCode, dstrRecordStatus, false);
		pDSTCWorkSession->getOption (ifds::CurrBusDate, dstrCurBusDate, getParent()->getDataGroupId(), false);

		dstrStopDate.strip().upperCase();
		dstrRecordStatus.strip().upperCase();
		dstrCurBusDate.strip().upperCase();
   }
	return DSTCommonFunctions::CompareDates (dstrStopDate, dstrCurBusDate) == DSTCommonFunctions::FIRST_EARLIER || dstrRecordStatus.strip() != YES;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/SystematicDlg.cpp-arc  $
 * 
 *    Rev 1.184   Jul 26 2012 10:29:46   wp040027
 * P0198518 - RDR Functionality
 * 
 *    Rev 1.183   Jun 06 2012 14:24:12   if991250
 * INA: PAC French. Need to compare the unformatted PayType value
 * 
 *    Rev 1.182   May 28 2012 10:39:12   if991250
 * CPF - Account Entity + Systematics
 * 
 *    Rev 1.181   May 16 2012 10:11:22   jankovii
 * P0186481 FN07-GWA LWA Payment Options for SWP RRIF
 * 
 *    Rev 1.180   May 13 2012 16:57:20   if991250
 * CPF - PAC
 * 
 *    Rev 1.179   May 11 2012 09:42:34   if991250
 * added VerifyStat and NonFinConfirms attributes
 * 
 *    Rev 1.178   Apr 30 2012 15:31:50   popescu
 * 2902002 - P0186480FN02 - Diploma DSK Validation
 * 
 *    Rev 1.177   Mar 23 2012 10:45:18   if991250
 * IN  2885402 - PAC-EFT Systematic readonly for active commitments, Added Insured and Policy number
 * 
 *    Rev 1.176   Jan 11 2012 15:30:16   dchatcha
 * IN# 2796443 - Validation rule for Allocated Auto Transfer
 * 
 *    Rev 1.175   Aug 16 2011 10:51:44   wutipong
 * IN2527545 iFast Desktop image popus up in 2 screens for QC user.
 * 
 *    Rev 1.174   Feb 27 2011 21:15:30   panatcha
 * ticket 2404299 (REG_RL11.2/101 - PAC set up and delete issues)
 * 
 *    Rev 1.173   Nov 25 2010 14:04:32   jankovii
 * PET175778FN01 - Upstreaming Phase 2
 * 
 *    Rev 1.172   Jul 28 2009 07:25:38   dchatcha
 * PET 157825 - FN 13 - Dilution Allocation Enhancements, Default NO_SORT for combo box type.
 * 
 *    Rev 1.171   Jul 24 2009 01:33:44   dchatcha
 * PET 157825 - FN 13 - Dilution Allocation Enhancements, Sorting combo in grid.
 * 
 *    Rev 1.170   Nov 06 2008 02:26:06   daechach
 * PET5517 FN71 Unclaimed Property Phase 2
 * 
 *    Rev 1.169   Jan 22 2008 15:39:22   yingz
 * fix incident 1110884 - bank infor display problem
 * 
 *    Rev 1.168   Jan 06 2006 16:34:56   zhengcon
 * Incident#489826 -- Error symbol is seen when TO fund is populated using fund code
 * 
 *    Rev 1.167   Dec 20 2005 13:32:58   AGUILAAM
 * IN 465769 - fixed validation on fee and feepercent to issue appropriate errors, if necessary.
 * 
 *    Rev 1.166   Oct 20 2005 13:21:58   popescu
 * Incindent # 418142, sub-sequent fix. user should not be able to enter negative values, chars in the acquistion fee field.
 * 
 *    Rev 1.165   Oct 04 2005 17:58:42   yingbaol
 * New item issue
 * 
 *    Rev 1.164   Oct 04 2005 13:50:32   AGUILAAM
 * IN 418142 (R65) - If fee is defined by user as "flat" and default feetype is "percent", fee will be converted to amount or dollar value; display corresponding message right away
 * 
 *    Rev 1.163   Sep 15 2005 15:15:26   popescu
 * Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
 * 
 *    Rev 1.162   Jul 26 2005 15:37:44   Fengyong
 * Incident 361597 - fix crash on margin account
 * 
 *    Rev 1.161   Jun 28 2005 14:17:38   porteanm
 * Incident 339758 - Fixed IDC_LV_ALLOCATION loading for AMS account and  EffectiveDate changed.
 * 
 *    Rev 1.160   Jan 04 2005 11:01:34   yingbaol
 * PTS10036915:Implement HideGridRowColumn() method
 * 
 *    Rev 1.159   Oct 27 2004 10:37:06   VADEANUM
 * PET 1010 FN02 CCB 1383 - WHTax for Registered Accts on SWPs.
 * 
 *    Rev 1.158   Sep 09 2004 12:09:16   VADEANUM
 * PET 1094 FN4 - Activest Bank File Interface.
 * 
 *    Rev 1.157   Sep 07 2004 15:15:06   VADEANUM
 * PET 1094 FN4 - Activest Bank File Interface.
 * 
 *    Rev 1.156   Sep 03 2003 17:16:12   popescu
 * fixes regarding calling the allocation screen, seems that more places that originally thought are using the allocation screen
 * 
 *    Rev 1.155   Aug 28 2003 16:44:04   HSUCHIN
 * refresh default allocations when effective date is changed for ams accounts
 * 
 *    Rev 1.154   Aug 21 2003 09:48:14   HSUCHIN
 * change the way openDemographic dialog is executed so the paytype is not locked out
 * 
 *    Rev 1.153   Aug 01 2003 11:59:18   popescu
 * reinit tge attributes grid after banking so an eventual currency change would be shown
 * 
 *    Rev 1.152   Jul 11 2003 15:59:58   FENGYONG
 * PET 809, FN07 Show KYC screen FOR CIBC broker
 * 
 *    Rev 1.149   May 26 2003 11:27:20   popescu
 * OnBtnBank methods clean-up
 * 
 *    Rev 1.148   May 23 2003 10:04:40   popescu
 * Part of bank instructions cleaning up process, moved the bank types into the ifastids project
 * 
 *    Rev 1.147   May 22 2003 14:14:28   popescu
 * Replaced name 'BankInstr' with 'BankInstructions'; 
 * simplified child lists getters for the Shareholder object
 * 
 *    Rev 1.146   May 14 2003 11:16:20   popescu
 * added extra param to the process layer, which is used to pass the key string of the current selected item in the allocations list, in order to set selection on it in split commission dialog
 * 
 *    Rev 1.145   May 13 2003 20:05:30   popescu
 * FIxed pts 10016214, enable the split commission button in the split commission dialog if there is split commiision for the funds in allocation, after the allocation has been set
 * 
 *    Rev 1.144   May 13 2003 10:07:38   popescu
 * Split commission re-work
 * 
 *    Rev 1.143   Mar 21 2003 21:30:54   PURDYECH
 * Fixing sync up goofs
 * 
 *    Rev 1.142   Mar 21 2003 20:13:12   PURDYECH
 * Sync 1.140.1.0 back to trunk
 * 
 *    Rev 1.141   Mar 19 2003 14:45:12   popescu
 * Exchange Out fee automatic transfer, and Trad
 *
 *    Rev 1.140.1.0   Mar 21 2003 18:41:26   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.140   Mar 05 2003 11:30:04   PURDYECH
 * Use IFastHistoricalInfo instead of deriving from IFastBaseMainDlg
 * 
 *    Rev 1.139   Feb 06 2003 16:12:52   WINNIE
 * ModPerm applies to all transaction type. When ModPerm=NO, then update of the record is not allowed
 * 
 *    Rev 1.138   Feb 05 2003 12:59:16   KOVACSRO
 * Enable/Disable Historical button (Serban)
 * 
 *    Rev 1.137   Feb 05 2003 12:53:32   KOVACSRO
 * Fixed allocation button bug (implementation in ver. 1.136 broke the existing code that was disabling Allocation button for a bad record)
 * 
 *    Rev 1.136   Feb 04 2003 10:33:42   WINNIE
 * Disable button for systematic record if ModPerm field come back as No. User is not allowed to modify those records
 * 
 *    Rev 1.135   Jan 29 2003 18:50:00   WINNIE
 * disable delete button for DCAF automatic transfer
 * 
 *    Rev 1.134   Jan 29 2003 14:57:22   popescu
 * Added Historical button for Systematic
 * 
 *    Rev 1.133   Jan 18 2003 17:14:34   WINNIE
 * Correct field name for batch: sync up update and inquiry view. Add display of BatchName and BatchTrace for Systematic
 * 
 *    Rev 1.132   Oct 29 2002 11:47:26   HSUCHIN
 * sync up with release 49 - 1.130 (1.131 has been synced up already)
 * 
 *    Rev 1.131   Oct 25 2002 17:07:34   HERNANDO
 * PTS 10010354 - Removed extra code displayed with Address Code description.
 * 
 *    Rev 1.130   Oct 09 2002 23:56:16   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.129   Oct 08 2002 16:57:50   YINGBAOL
 * sync. 1.127.1.0
 * 
 *    Rev 1.128   Sep 30 2002 11:01:44   PURDYECH
 * BFFieldId no longer has operator long(), so explicit getId() calls are needed in places.
 * 
 *    Rev 1.127   Aug 29 2002 20:09:28   SMITHDAV
 * CellProperties fixes
 * 
 *    Rev 1.126   Aug 29 2002 18:28:00   SMITHDAV
 * Additional fixes.
 * 
 *    Rev 1.125   Aug 29 2002 18:16:10   SMITHDAV
 * Additional FieldId fixes.
 * 
 *    Rev 1.124   Aug 29 2002 12:57:26   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.123   Aug 08 2002 11:12:28   YINGBAOL
 * fix saving plan display issue----PTS10009363
 * 
 *    Rev 1.122   Jul 25 2002 15:48:50   HSUCHIN
 * temp bug fix to prevent amount entry to exceed 12 characters
 * 
 *    Rev 1.121   Jul 18 2002 17:21:14   KOVACSRO
 * passing TransType param for allocations.
 * 
 *    Rev 1.120   Jul 17 2002 14:28:32   KOVACSRO
 * PTS10008988 : showing TO accountHolder name, when user enters AccountTo field.
 * 
 *    Rev 1.119   Jul 05 2002 10:44:20   PURDYECH
 * Include file cleanup.
 * Code cleanup
 * 
 *    Rev 1.118   May 23 2002 10:40:10   PURDYECH
 * BFData Implementation Verification Corrections
 * 
 *    Rev 1.117   17 Apr 2002 14:11:52   KOVACSRO
 * Hour glass for Copy button.
 * 
 *    Rev 1.116   27 Mar 2002 20:01:24   PURDYECH
 * Process/WindowFactory overhaul
 * 
 *    Rev 1.115   14 Mar 2002 15:47:04   KOVACSRO
 * Fixed grid
 * 
 *    Rev 1.114   15 Feb 2002 12:11:30   HSUCHIN
 * fix for PTS: 10007017 -  The Month label is no longer hidden switching between monthly and weekly.
 * 
 *    Rev 1.113   08 Feb 2002 17:09:44   HSUCHIN
 * PTS: 10007017 - The monthly edit box now no longer hides when the systematic type is auto transfer.
 * 
 *    Rev 1.112   Jan 09 2002 15:16:54   YINGBAOL
 * fix paytype update issue
 * 
 *    Rev 1.111   Jan 08 2002 11:28:28   ZHANGCEL
 * Fix the crash when user hit ESC
 * 
 *    Rev 1.110   19 Dec 2001 10:58:36   KOVACSRO
 * fixed previous crash (before connecting controls to data, set the user access func. code using the systematic type parameter, rather than the field)
 * 
 *    Rev 1.108   14 Dec 2001 11:15:12   KOVACSRO
 * SetUserAccessCode before connecting controls to data.
 * 
 *    Rev 1.107   23 Nov 2001 14:26:20   KOVACSRO
 * perm check changes.
 * 
 *    Rev 1.106   19 Nov 2001 10:51:58   HSUCHIN
 * removed acqFee confirmation
 * 
 *    Rev 1.105   Oct 05 2001 16:55:36   YINGBAOL
 * fix internal error
 * 
 *    Rev 1.104   Sep 18 2001 16:36:40   ZHANGCEL
 * fixed the bug regarding EffectiveDate showing up
 * 
 *    Rev 1.103   Sep 12 2001 16:40:40   YINGBAOL
 * fix lost focus on grid cell
 * 
 *    Rev 1.102   Sep 12 2001 11:26:50   YINGBAOL
 * dynamic show up next process date by transtype
 * 
 *    Rev 1.101   Sep 07 2001 15:32:50   ZHANGCEL
 * added second parameter in the ListViewControlFilter()
 * 
 *    Rev 1.100   27 Aug 2001 17:38:36   WINNIE
 * enable allocation for SWP in 'unit'
 * 
 *    Rev 1.99   Aug 27 2001 09:44:36   YINGBAOL
 * fix paytype issue
 * 
 *    Rev 1.98   Aug 23 2001 09:40:00   YINGBAOL
 * add OnKillfocusCmbPayType and check default fee
 * 
 *    Rev 1.97   Aug 16 2001 10:24:04   YINGBAOL
 * code clean
 * 
 *    Rev 1.96   Aug 10 2001 12:53:20   YINGBAOL
 * disable NASU if identAcctDlg lauched from systematic and allocation screen
 * 
 *    Rev 1.95   Aug 09 2001 10:24:52   YINGBAOL
 * Transfer enhancement
 * 
 *    Rev 1.94   02 Aug 2001 18:29:04   HSUCHIN
 * keep sysindex active on bad status
 * 
 *    Rev 1.93   25 Jul 2001 13:56:38   YINGZ
 * bus rules, bug fix etc
 * 
 *    Rev 1.92   19 Jul 2001 13:13:24   YINGZ
 * make splitcomm read only
 * 
 *    Rev 1.91   Jul 12 2001 17:17:50   HERNANDO
 * Added m_bInvAdvice - determines BtnAllocation state.
 * 
*    Rev 1.90   11 Jul 2001 15:13:20   HSUCHIN
 * changed to pass listkey to sysIndex rather than PacSwpId
 * 
 *    Rev 1.89   09 Jul 2001 11:01:08   HSUCHIN
 * getField fix for DBR::SplitComm
 * 
 *    Rev 1.88   Jul 05 2001 17:54:06   HERNANDO
 * Changed translation changes of 1.86 for consistency.
 * 
 *    Rev 1.87   05 Jul 2001 15:10:26   YINGZ
 * set FeeCurrency etc to read only
 * 
 *    Rev 1.86   Jul 04 2001 15:45:56   HERNANDO
 * Translation changes.
 * 
 *    Rev 1.85   25 Jun 2001 17:00:14   YINGZ
 * support paytype for saving plan
 * 
 *    Rev 1.84   21 Jun 2001 11:09:10   KOVACSRO
 * moved logic for month indicator into CBO
 * 
 *    Rev 1.83   Jun 15 2001 13:20:42   ZHANGCEL
 * add fields in grid
 * 
 *    Rev 1.82   14 Jun 2001 13:47:48   SMITHDAV
 * Remove references to UserSessionProcess.
 * 
 *    Rev 1.81   12 Jun 2001 16:59:10   YINGZ
 * more work
 * 
 *    Rev 1.80   11 Jun 2001 15:18:30   YINGZ
 * checking in for testing
 * 
 *    Rev 1.79   11 Jun 2001 10:19:22   YINGZ
 * add new dunctions
 * 
 *    Rev 1.78   05 Jun 2001 16:06:46   YINGZ
 * for others to compile
 * 
 *    Rev 1.77   31 May 2001 17:10:14   YINGZ
 * just for checking
 * 
 *    Rev 1.76   31 May 2001 11:16:02   YINGZ
 * check in for Chin
 * 
 *    Rev 1.75   17 May 2001 09:42:48   YINGZ
 * paytype fix
 * 
 *    Rev 1.74   14 May 2001 14:53:00   HSUCHIN
 * Session management restructuring
 * 
 *    Rev 1.73   11 May 2001 11:06:02   YINGZ
 * enahncement for 42
 * 
 *    Rev 1.72   10 May 2001 14:15:54   YINGZ
 * re arrange systematic
 * 
 *    Rev 1.71   May 07 2001 11:27:38   HERNANDO
 * Added SetParameter for OnBtnSplitCom.
 * 
 *    Rev 1.70   01 May 2001 17:17:48   KOVACSRO
 * Made address readonly.
 * 
 *    Rev 1.69   30 Apr 2001 15:40:20   HSUCHIN
 * fix for multi account enabling split comm button
 * 
 *    Rev 1.68   Apr 26 2001 15:40:40   HERNANDO
 * UnFix.
 * 
 *    Rev 1.67   25 Apr 2001 10:02:58   HSUCHIN
 * Split Commission Button will not enable for Auto Transfer until the Account number is also enter with Fund/Class
 * 
 *    Rev 1.66   Apr 23 2001 15:18:02   HERNANDO
 * Added NextProcessDate.
 * 
 *    Rev 1.65   19 Apr 2001 17:19:38   KOVACSRO
 * Implemented checkPermission.
 * 
 *    Rev 1.64   Apr 19 2001 13:16:26   HERNANDO
 * Fix.
 * 
 *    Rev 1.63   Apr 17 2001 16:40:22   HERNANDO
 * Uses BankIdValue instead of InstCode.
 * 
 *    Rev 1.62   Apr 17 2001 11:26:18   YINGZ
 * focus to new item in addcopy
 * 
 *    Rev 1.61   Apr 12 2001 19:13:54   HERNANDO
 * Added ShowFromBankRelated fn.
 * 
 *    Rev 1.60   Apr 06 2001 15:38:52   HUANGSHA
 * enable the IDC_CMB_TYPE for dummy record
 * 
 *    Rev 1.59   06 Apr 2001 11:37:42   KOVACSRO
 * Added F4 perm. check.
 * 
 *    Rev 1.58   Apr 04 2001 16:00:30   HERNANDO
 * Bug fix.
 * 
 *    Rev 1.57   04 Apr 2001 14:34:26   HSUCHIN
 * added support for Auto Transfers
 * 
 *    Rev 1.56   Apr 04 2001 14:26:48   HERNANDO
 * Fixed uncorrelated Active display and field value.
 * 
 *    Rev 1.55   Apr 03 2001 16:00:22   HUANGSHA
 * removed the obsolet routines, disable the TransType combo when the focus is lost
 * 
 *    Rev 1.54   Apr 02 2001 15:41:08   DINACORN
 * Used DSTCommonFunctions MARKET_IDS constants
 * 
 *    Rev 1.53   01 Apr 2001 12:55:56   HSUCHIN
 * enable/disable split comm button based on default split commission results
 * 
 *    Rev 1.52   30 Mar 2001 18:02:56   KOVACSRO
 * perm. check does not work for systematics.
 * 
 *    Rev 1.51   30 Mar 2001 17:09:14   BUZILAMI
 * Systematic bank changes
 * 
 *    Rev 1.50   27 Mar 2001 16:56:00   KOVACSRO
 * perm. check stuff.
 * 
 *    Rev 1.49   Mar 22 2001 14:11:36   HSUCHIN
 * check splitcomm flag re enabled
 * 
 *    Rev 1.48   Mar 19 2001 15:00:56   HSUCHIN
 * Split Commission hook up temporary disabled
 * 
 *    Rev 1.47   01 Mar 2001 16:44:12   KOVACSRO
 * Modifications for permission check.
 * 
 *    Rev 1.46   Feb 23 2001 13:50:16   YINGBAOL
 * introduce systematicPayType
 * 
 *    Rev 1.45   Feb 12 2001 16:30:28   DINACORN
 * M3/C4 synchronization
 * Change "MSDW - Japan" to "Japan"
 * 
 *    Rev 1.44   Feb 09 2001 13:35:58   DINACORN
 * M3/C4 synchronization
 * 
 *    Rev 1.43   Dec 13 2000 14:54:48   KOVACSRO
 * 1. Modified DoListItemChanged.
 * 2.Added Dummy Item logic for perm. check.
 * 
 *    Rev 1.42   Dec 06 2000 12:38:02   KOVACSRO
 * 1. Added new item logic for perm. check.
 * 2. Set the TransType param (for BankInstruction permission reasons)
 * 
 *    Rev 1.41   Dec 01 2000 15:11:26   KOVACSRO
 * Added permission check logic.
 * 
 *    Rev 1.40   Nov 21 2000 10:24:14   HUANGSHA
 * fixed in Bad status data display
 * 
 *    Rev 1.39   Oct 27 2000 17:40:54   HUANGSHA
 * disable the TransType after reset for the old item
 * 
 *    Rev 1.38   Oct 19 2000 15:26:20   HUANGSHA
 * fix the bug for Enble/disable allocation button
 * 
 *    Rev 1.37   Sep 29 2000 18:03:24   HUANGSHA
 * change the Freqency setting logic, CFDS_CAN to "Canada"
 * 
 *    Rev 1.36   Sep 25 2000 15:46:08   HUANGSHA
 * display Allocation Column title according to the AmountType
 * 
 *    Rev 1.35   Sep 22 2000 16:31:54   HUANGSHA
 * sync with M3 for allocation refreshing and Fee disable logic
 * 
 *    Rev 1.34   Sep 01 2000 16:38:38   HUANGSHA
 * Sync with M3
 * 
 *    Rev 1.33   Aug 21 2000 17:05:02   YINGBAOL
 * we do not need to set AT list from allocation if it is launched from PAC and SWP
 * 
 *    Rev 1.32   Aug 11 2000 15:51:36   ZHANGCEL
 * In the case of Fund changed, reload control from CBO 
 * 
 *    Rev 1.31   Aug 09 2000 14:31:48   ZHANGCEL
 * Fund number bug fixed
 * 
 *    Rev 1.30   Aug 04 2000 16:51:08   YINGBAOL
 * in some case, we need to  load control from CBO in order to make screen data consistent with CBO
 * 
 *    Rev 1.29   Jul 26 2000 11:19:24   HERNANDO
 * Set parameters (Code, Class, Number) for Fund Search
 * 
 *    Rev 1.28   Jul 26 2000 11:01:04   YINGBAOL
 * check in for Ulli
 * 
 *    Rev 1.27   Jul 11 2000 13:50:16   YINGBAOL
 * add Fund Number Logic
 * 
 *    Rev 1.26   Jul 04 2000 18:05:58   YINGBAOL
 * fix F4 choose fund class
 * 
 *    Rev 1.25   Jun 30 2000 16:19:08   YINGBAOL
 * fix crash for PAC and SWP
 * 
 *    Rev 1.24   Jun 30 2000 09:50:30   YINGBAOL
 * fix add copy and some other bugs
 * 
 *    Rev 1.23   Jun 27 2000 16:14:40   YINGBAOL
 * change queterly indicate for PAC and SWP
 * 
 *    Rev 1.22   Jun 27 2000 15:39:24   YINGBAOL
 * fix
 * 
 *    Rev 1.21   Jun 27 2000 09:50:58   YINGBAOL
 * day of week added
 * 
 *    Rev 1.20   Jun 23 2000 15:05:30   HUANGSHA
 * Fix the control overlap problems for AT and PAC/SWp
 * 
 *    Rev 1.19   Jun 21 2000 16:05:10   YINGBAOL
 * take some unused code off and fix bugs
 * 
 *    Rev 1.18   Jun 21 2000 11:43:04   YINGBAOL
 * fix crash
 * 
 *    Rev 1.17   Jun 14 2000 14:38:34   YINGBAOL
 * fix list selection probelms
 * 
 *    Rev 1.16   Jun 12 2000 16:48:16   YINGBAOL
 * AT put back
 * 
 *    Rev 1.15   May 31 2000 16:46:08   YINGBAOL
 * temperally filter AT transtype systematic out
 * 
 *    Rev 1.14   May 25 2000 11:03:28   HUANGSHA
 * Fixed the bug for the crashing
 * 
 *    Rev 1.13   May 19 2000 17:51:48   HSUCHIN
 * Changed Fund/Class combo to edit and implemented fund search
 * 
 *    Rev 1.12   May 19 2000 16:14:56   HUANGSHA
 * get it working properly
 * 
 *    Rev 1.11   May 11 2000 16:05:54   YINGBAOL
 * add AT Feelogic
 * 
 *    Rev 1.10   May 01 2000 09:38:18   YINGBAOL
 * Automatic transfer added
 * 
 *    Rev 1.9   Apr 18 2000 09:25:22   YINGZ
 * addcopy
 * 
 *    Rev 1.8   Apr 17 2000 17:16:20   YINGZ
 * add AddCopy function for systematic
 * 
 *    Rev 1.7   Apr 17 2000 11:22:20   YINGBAOL
 * fix crash for M3
 * 
 *    Rev 1.6   Apr 14 2000 12:06:10   YINGBAOL
 * Automatic Transfer has been added in the systematic screen
 * 
 *    Rev 1.5   Apr 06 2000 10:35:06   DT24433
 * removed unused headers
 * 
 *    Rev 1.4   Apr 05 2000 14:17:16   HSUCHIN
 * more M2 sync up
 * 
 *    Rev 1.3   Apr 04 2000 10:48:28   YINGBAOL
 * M2 Sync.
 * 
 *    Rev 1.2   Mar 21 2000 10:21:36   HSUCHIN
 * removed fund number from fund combo box
 * 
 *    Rev 1.1   Mar 19 2000 10:36:04   HSUCHIN
 * C2 sync up
 * 
 *    Rev 1.0   Feb 15 2000 11:01:26   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.54   Feb 09 2000 12:11:04   HUANGSHA
 * Check in for release
 * 
 *    Rev 1.53   Feb 02 2000 17:24:22   HUANGSHA
 * Fixed a problem for Allocation refresh
 * 
 *    Rev 1.52   Feb 02 2000 10:30:40   PRAGERYA
 * Bug in refreshSystematicAlloctions fixed
 * 
 *    Rev 1.51   Jan 31 2000 17:25:44   HUANGSHA
 * Remove setCurrentItem for SysAllocation
 * 
 *    Rev 1.50   Jan 31 2000 16:59:48   HUANGSHA
 * Force amount type to D or S for Allocated trades
 * 
 *    Rev 1.49   Jan 31 2000 12:57:20   HUANGSHA
 * disable the paytype combo for exitsting records
 * 
 *    Rev 1.48   Jan 29 2000 16:42:32   HUANGSHA
 * check in
 * 
 *    Rev 1.47   Jan 28 2000 12:52:48   HUANGSHA
 * bug fix
 * 
 *    Rev 1.46   Jan 27 2000 13:11:02   HUANGSHA
 * check in 
 * 
 *    Rev 1.45   Jan 25 2000 17:11:32   HUANGSHA
 * Fixed bugs
 * 
 *    Rev 1.44   Jan 22 2000 17:27:18   HUANGSHA
 * made the changes required by BA
 * 
 *    Rev 1.43   Jan 21 2000 19:15:54   HUANGSHA
 * for test
 * 
 *    Rev 1.42   Jan 19 2000 16:12:54   HUANGSHA
 * fixed the bug for displaying the Amount
 * 
 *    Rev 1.41   Jan 18 2000 17:44:10   HUANGSHA
 * fixed some bugs reported in SIT
 * 
 *    Rev 1.40   Jan 13 2000 17:22:44   HUANGSHA
 * check in for release
 * 
 *    Rev 1.39   Jan 07 2000 16:43:26   HUANGSHA
 * Added address code refresh
 * 
 *    Rev 1.38   Dec 24 1999 12:12:32   HUANGSHA
 * fixed some bugs
 * 
 *    Rev 1.37   Dec 23 1999 12:12:08   HUANGSHA
 * check in for test
 * 
 *    Rev 1.36   Dec 21 1999 16:45:42   HUANGSHA
 * made the changes for sysallocations
 * 
 *    Rev 1.35   Dec 17 1999 18:14:50   HUANGSHA
 * added Address refresh
 * 
 *    Rev 1.34   Dec 16 1999 18:29:06   HUANGSHA
 * Check in for testing
 * 
 *    Rev 1.33   Dec 14 1999 15:34:46   HUANGSHA
 * check in for compiling
 * 
 *    Rev 1.32   Dec 03 1999 16:35:18   HUANGSHA
 * fixed invoking Allocation screen
 * 
 *    Rev 1.31   Dec 03 1999 15:15:20   BUZILA
 * changed invokeCommand  into invokeProcessFromChild
 * 
 *    Rev 1.30   Dec 03 1999 10:51:58   HUANGSHA
 * display the fund and class in uppercase
 * 
 *    Rev 1.29   Dec 02 1999 19:22:00   HUANGSHA
 * fixed allocation percentage display problem
 * 
 *    Rev 1.28   Dec 02 1999 17:57:04   POPESCUS
 * Fixed crashes in search
 * 
 *    Rev 1.27   Dec 01 1999 18:15:02   HUANGSHA
 * Enable systematic fee button for new item
 * 
 *    Rev 1.26   Dec 01 1999 12:52:30   HUANGSHA
 * disable the Allocation Button if no list item
 * 
 *    Rev 1.25   Dec 01 1999 10:51:46   BUZILA
 * metagroup fixes
 * 
 *    Rev 1.24   Dec 01 1999 10:29:08   HUANGSHA
 * enable all buttons even if there are no permissions in account level
 * 
 *    Rev 1.23   Nov 30 1999 16:45:38   PRAGERYA
 * SystematicKey parameter added for AllocationsProcess invocation
 * 
 *    Rev 1.22   Nov 30 1999 09:50:02   HUANGSHA
 * check in temporarily
 * 
 *    Rev 1.21   Nov 27 1999 16:26:54   HUANGSHA
 * check in
 * 
 *    Rev 1.20   Nov 25 1999 15:18:58   HUANGSHA
 * check in for the initial m2 release
 * 
 *    Rev 1.19   Nov 25 1999 10:25:32   HUANGSHA
 * check in for test
 * 
 *    Rev 1.18   Nov 24 1999 17:24:22   PRAGERYA
 * SetParameter for Allocations added
 * 
 *    Rev 1.17   Nov 24 1999 17:21:30   HUANGSHA
 * check in for Allocation test
 * 
 *    Rev 1.16   Nov 24 1999 09:29:12   HUANGSHA
 * check in for test
 * 
 *    Rev 1.15   Nov 15 1999 14:42:44   HUANGSHA
 * temporary check in
 * 
 *    Rev 1.14   Nov 02 1999 12:27:28   YINGZ
 * add info to open bank dlg
 * 
 *    Rev 1.13   Oct 22 1999 16:39:38   HUANGSHA
 * Incorrect checked in for revision 1.11
 * 
 *    Rev 1.11   Sep 24 1999 20:18:58   PRAGERYA
 * Default allocations started
 * 
 *    Rev 1.10   Sep 23 1999 16:28:20   VASILEAD
 * Modified to match C1 requirements
 * 
 *    Rev 1.9   Sep 23 1999 14:30:34   PRAGERYA
 * New Allocations process
 * 
 *    Rev 1.8   13 Sep 1999 18:31:04   HUANGSHA
 * Fixed merge errors
 * 
 *    Rev 1.7   13 Sep 1999 13:53:00   HUANGSHA
 * Synchronize with M1's changes
 * 
 *    Rev 1.6   Aug 23 1999 14:08:02   BUZILA
 * Changed Change button into Cancel
 * 
 *    Rev 1.5   Aug 20 1999 10:32:20   DT24433
 * changed getFieldForCurrentListItem to getField
 * 
 *    Rev 1.4   Aug 08 1999 16:08:44   VASILEAD
 * Allocation button disabled when we don't have any allocation
 * 
 *    Rev 1.3   Jul 20 1999 11:19:34   VASILEAD
 * New conditions update
 * 
 *    Rev 1.2   Jul 19 1999 12:44:06   POPESCUS
 * Added checks for user access rights for various buttons on the dialog
 * 
 *    Rev 1.1   Jul 08 1999 10:05:56   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */


