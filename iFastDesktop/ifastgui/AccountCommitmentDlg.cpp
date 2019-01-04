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
//    Copyright 2011 by International Financial Data Services.
//
//******************************************************************************
//
// ^FILE   : AccountCommitmentDlg.cpp
// ^CLASS  : AccountCommitmentDlg
//
//******************************************************************************
#include "stdafx.h"
#include "mfdstc.h"
#include "accountcommitmentdlg.h"

#include <uibase\dstedit.h>
#include <uibase\dstlistctrl.h>
#include <uibase\dstcombobox.h>
#include <uibase\dstcfuncs.h>
#include <uibase\ifdslistctrl.h>

#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastbp\accountcommitmentprocessincludes.h>
#include <ifastcbo\dstcommonfunction.hpp>
#include <uibase\DSTGridWnd.h>
#include <uibase\DSTOleDateTime.h>

#include <ifastcbo\dstcworksession.hpp>
#include <ifastcbo\mgmtcooptions.hpp>

#ifndef INCLUDED_ASSERT_H
#define INCLUDED_ASSERT_H
#include <assert.h>
#endif

extern CLASS_IMPORT const I_CHAR* CMD_GUI_ACCOUNT_COMMITMENT; 
extern IFASTBP_LINKAGE const I_CHAR* CMD_BPROC_BANK_INSTRUCTIONS;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< AccountCommitmentDlg > dlgCreator( CMD_GUI_ACCOUNT_COMMITMENT ); 

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME                     = I_("AccountCommitmentDlg");

   const I_CHAR * const INVESTMENT_TYPE_FIX           = I_( "F" );
   const I_CHAR * const INVESTMENT_TYPE_PROGESSIVE    = I_( "P" );
   const I_CHAR * const FORCED_RATE_CONFIG_DERIVED    = I_( "1" );
   const I_CHAR * const FORCED_RATE_FORCED            = I_( "2" );
}

namespace COMMIT_STATUS
{
   const I_CHAR * const ACTIVE          = I_( "01" );
   const I_CHAR * const SUSPENDED       = I_( "02" );
   const I_CHAR * const STOPPED         = I_( "03" );
   const I_CHAR * const MATURED         = I_( "04" );
}

namespace RUN_MODES
{
   const I_CHAR * const RUN_MODE_ADD  = I_("Add");
   const I_CHAR * const RUN_MODE_MOD  = I_("Mod");
   const I_CHAR * const RUN_MODE_STOP = I_("Stop");
   const I_CHAR * const RUN_MODE_SUSP = I_("Susp");
   const I_CHAR * const RUN_MODE_RNST = I_("Rnst");
   const I_CHAR * const RUN_MODE_REACT = I_("React");
}

namespace CND
{
   extern CLASS_IMPORT const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFDecimalFieldId ProgressiveIntRate;
   extern CLASS_IMPORT const BFNumericFieldId ProgressiveInvTerm;
   extern CLASS_IMPORT const BFTextFieldId ProgressiveIntRateDetailsList;
   extern CLASS_IMPORT const BFDateFieldId GIMaturityDate;
   extern CLASS_IMPORT const BFDateFieldId LastProcDate;
   extern CLASS_IMPORT const BFDateFieldId NextProcessDate;
   extern CLASS_IMPORT const BFDateFieldId NextDrawDate;
}

namespace BANKTYPE
{
   extern CLASS_IMPORT I_CHAR * const ACCOUNT_COMMITMENT;
}
//*****************************************************************************
// Public methods
//*****************************************************************************
AccountCommitmentDlg::AccountCommitmentDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand)
: BaseMainDlg( AccountCommitmentDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
,m_dstrCaller(NULL_STRING)
,m_dstrAccountNum (NULL_STRING)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
}

//*****************************************************************************
void AccountCommitmentDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(AccountCommitmentDlg)
   //}}AFX_DATA_MAP
}
//*****************************************************************************
BEGIN_MESSAGE_MAP(AccountCommitmentDlg, BaseMainDlg)
//{{AFX_MSG_MAP(AccountCommitmentDlg)
ON_BN_CLICKED(IDC_BTN_ADMIN, OnBtnAdmin)
ON_BN_CLICKED( IDC_BTN_BANK, OnBtnBank)
ON_BN_CLICKED( IDC_BTN_SUSPEND, OnBtnSuspend)
ON_BN_CLICKED( IDC_BTN_STOP, OnBtnStop)
ON_BN_CLICKED( IDC_BTN_RESET, OnBtnReset)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*****************************************************************************
SEVERITY AccountCommitmentDlg::doInit()
{
   TRACE_METHOD(CLASSNAME, DOINIT);

   getParameter (ACCOUNT_NUM, m_dstrAccountNum);
   getParameter (CALLER, m_dstrCaller);

   return (NO_CONDITION); /*sevRtn*/
}

//*****************************************************************************
BOOL AccountCommitmentDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );
   BaseMainDlg::OnInitDialog(); 
   
   AddControl ( CTRL_COMBO, IDC_CMB_COMMITMENT_TYPE,    IFASTBP_PROC::ACCOUNT_COMMITMENT, ifds::CommitmentUUID,
                CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST);
   AddControl ( CTRL_EDIT,  IDC_EDT_COMMITMENT_STATUS,     IFASTBP_PROC::ACCOUNT_COMMITMENT, ifds::CommitStatus, CTRLFLAG_NOT_UPDATABLE);
   AddControl ( CTRL_DATE,  IDC_DTP_COMMIT_EFFECTIVE_DATE, IFASTBP_PROC::ACCOUNT_COMMITMENT, ifds::CommitDeff,       CTRLFLAG_DEFAULT);
   AddControl ( CTRL_DATE,  IDC_DTP_COMMITMENT_END_DATE,   IFASTBP_PROC::ACCOUNT_COMMITMENT, ifds::CommitEndDate,    CTRLFLAG_NOT_UPDATABLE);
   
   AddControl ( CTRL_EDIT,  IDC_EDT_BENEFICIARY,           IFASTBP_PROC::ACCOUNT_COMMITMENT, ifds::BeneName,         CTRLFLAG_NOT_UPDATABLE);
   AddControl ( CTRL_EDIT,  IDC_EDT_ORIG_ACCT_NUM,         IFASTBP_PROC::ACCOUNT_COMMITMENT, ifds::OrigAccountNum,   CTRLFLAG_NOT_UPDATABLE);
   AddControl ( CTRL_EDIT,  IDC_EDT_ORIG_BENEF,            IFASTBP_PROC::ACCOUNT_COMMITMENT, ifds::OrigBeneName,     CTRLFLAG_NOT_UPDATABLE);
   AddControl ( CTRL_EDIT,  IDC_EDT_COMMISSION_PAID,       IFASTBP_PROC::ACCOUNT_COMMITMENT, ifds::CommissionPaid,   CTRLFLAG_NOT_UPDATABLE);
   AddControl ( CTRL_EDIT,  IDC_EDT_SURRENDER_CHARGES,     IFASTBP_PROC::ACCOUNT_COMMITMENT, ifds::SurrChrgApplied,  CTRLFLAG_NOT_UPDATABLE);
   AddControl ( CTRL_EDIT,  IDC_EDT_MAX_SURR_CHARGES,      IFASTBP_PROC::ACCOUNT_COMMITMENT, ifds::MaxSurrCharges,   CTRLFLAG_NOT_UPDATABLE);
   AddControl ( CTRL_EDIT,  IDC_EDT_COMMITTED_PACS,        IFASTBP_PROC::ACCOUNT_COMMITMENT, ifds::CommittedPACS,    CTRLFLAG_NOT_UPDATABLE);
   AddControl ( CTRL_EDIT,  IDC_EDT_PAID_PACS,             IFASTBP_PROC::ACCOUNT_COMMITMENT, ifds::PaidPACS,         CTRLFLAG_NOT_UPDATABLE);
   AddControl ( CTRL_EDIT,  IDC_EDT_MISSING_PACS,          IFASTBP_PROC::ACCOUNT_COMMITMENT, ifds::MissingPACS,      CTRLFLAG_NOT_UPDATABLE);
   AddControl ( CTRL_EDIT,  IDC_EDT_AMOUNT,                IFASTBP_PROC::ACCOUNT_COMMITMENT, ifds::CommitAmt,        CTRLFLAG_DEFAULT);


   AddControl ( CTRL_DATE,  IDC_DTP_PAC_EFF_DATE,          IFASTBP_PROC::ACCOUNT_COMMITMENT, ifds::PACDeff,          CTRLFLAG_NOT_UPDATABLE);
   AddControl ( CTRL_DATE,  IDC_DTP_PAC_STOP_DATE,         IFASTBP_PROC::ACCOUNT_COMMITMENT, ifds::PACStopDate,      CTRLFLAG_NOT_UPDATABLE);
   AddControl ( CTRL_EDIT,  IDC_EDT_PAC_AMOUNT,            IFASTBP_PROC::ACCOUNT_COMMITMENT, ifds::PACAmt,           CTRLFLAG_NOT_UPDATABLE);
   AddControl ( CTRL_EDIT,  IDC_EDT_BANK_NAME,             IFASTBP_PROC::ACCOUNT_COMMITMENT, ifds::InstName,         CTRLFLAG_NOT_UPDATABLE);
   AddControl ( CTRL_EDIT,  IDC_EDT_INST_CODE,             IFASTBP_PROC::ACCOUNT_COMMITMENT, ifds::InstCode,         CTRLFLAG_NOT_UPDATABLE);
   AddControl ( CTRL_EDIT,  IDC_EDT_TRANSIT_NUMBER,        IFASTBP_PROC::ACCOUNT_COMMITMENT, ifds::TransitNo,        CTRLFLAG_NOT_UPDATABLE);
   AddControl ( CTRL_EDIT,  IDC_EDT_BANK_ACCT_NBR,         IFASTBP_PROC::ACCOUNT_COMMITMENT, ifds::BankAcctNum,      CTRLFLAG_NOT_UPDATABLE);
   AddControl ( CTRL_EDIT,  IDC_EDT_PAID_PAC_AMT,          IFASTBP_PROC::ACCOUNT_COMMITMENT, ifds::PaidPACSAmt,      CTRLFLAG_NOT_UPDATABLE);
   
   AddControl ( CTRL_DATE,  IDC_DTP_LAST_PROCESS_DATE,     IFASTBP_PROC::ACCOUNT_COMMITMENT, ifds::LastProcDate,  CTRLFLAG_NOT_UPDATABLE);
   AddControl ( CTRL_DATE,  IDC_DTP_NEXT_PROCESS_DATE,     IFASTBP_PROC::ACCOUNT_COMMITMENT, ifds::NextProcessDate,     CTRLFLAG_NOT_UPDATABLE);
   AddControl ( CTRL_DATE,  IDC_DTP_NEXT_DRAW_DATE,        IFASTBP_PROC::ACCOUNT_COMMITMENT, ifds::NextDrawDate,     CTRLFLAG_DEFAULT);
//   AddIFDSListControl( ifdsListProgressiveIntRate, I_("PROGRESSIVE_INTEREST_RATE"), IFASTBP_PROC::ACCOUNT_COMMITMENT_DETAILS_LIST, ifds::ProgressiveIntRateDetailsList );

   //AddControl ( CTRL_COMBO, IDC_CMB_INT_CALC_TYPE,  
   //             IFASTBP_PROC::TRADE, ifds::IntCalcMthd, 
   //             CTRLFLAG_DEFAULT |  CTRLFLAG_INITCOMBO_BY_SUB_LIST);
   //AddControl ( CTRL_COMBO, IDC_CMB_DEPOSIT_TERM,   
   //             IFASTBP_PROC::TRADE, ifds::InvestTerm, 
   //             CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST);
   //AddControl ( CTRL_DATE,  IDC_DTP_MATURE_DATE,    
   //             IFASTBP_PROC::TRADE, ifds::GIMaturityDate, CTRLFLAG_DEFAULT );
   //AddControl ( CTRL_COMBO, IDC_CMB_INT_FREQ,       
   //             IFASTBP_PROC::TRADE, ifds::IntCredFreq,
   //             CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST);
   //AddControl ( CTRL_DATE,  IDC_DTP_NXT_INVEST_DAY, 
   //             IFASTBP_PROC::TRADE, ifds::NextIntCredDate, CTRLFLAG_DEFAULT  );
   //AddControl ( CTRL_COMBO, IDC_CMB_FORCED_RATE, IFASTBP_PROC::TRADE, ifds::ForcedRate, 
   //             CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST );
   //AddControl ( CTRL_EDIT,  IDC_EDT_INT_RATE,
   //             IFASTBP_PROC::TRADE, ifds::IntRate, CTRLFLAG_DEFAULT  );
   //AddControl ( CTRL_COMBO, IDC_CMB_COMM_REDUCTION, 
   //             IFASTBP_PROC::TRADE, ifds::CommRedRate, CTRLFLAG_DEFAULT | CTRLFLAG_INITCOMBO_BY_SUB_LIST );

   //IFDSListCtrl* ifdsListProgressiveIntRate = 
   //   new IFDSAdaptedListCtrl< LVProgressiveIntRateAdapter >( this, 
   //                                                           CLASSNAME, 
   //                                                           IDC_LV_INT_RATE_TERM, 
   //                                                           0, 
   //                                                           LISTFLAG_NOT_AUTO_ADD , 
   //                                                           false /*ShowSelAlways*/, 
   //                                                           false /*ShowConditions*/);

   //AddIFDSListControl( ifdsListProgressiveIntRate, 
   //                  I_("PROGRESSIVE_INTEREST_RATE"), 
   //                  IFASTBP_PROC::PROGRESSIVE_INTEREST_RATE_LIST, 
   //                  ifds::ProgressiveIntRateDetailsList );

   return TRUE; 
}
//******************************************************************************
void AccountCommitmentDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );
   AddListControl(CLASSNAME, IDC_LV_COMMITMENTS,   I_("ACCOUNT_COMMITMENT_DETAILS"), ifds::AccountCommitmentsHeading, IFASTBP_PROC::ACCOUNT_COMMITMENT_DETAILS_LIST, 0, true, LISTFLAG_NOT_AUTO_ADD );
   AddListControl(CLASSNAME, IDC_LV_COMMITMENTS_ACTIVITY,   I_("ACCOUNT_COMMITMENT_ACTIVITY"), ifds::AccountCommitActivityHeading, IFASTBP_PROC::ACCOUNT_COMMITMENT_ACTIVITY_LIST, 0, true, LISTFLAG_NOT_AUTO_ADD );

   doRefresh (this, NULL);

   LoadListControl(IDC_LV_COMMITMENTS);
//   LoadListControl(IDC_LV_COMMITMENTS_ACTIVITY);
   UpdateButtons();

   DString strIsDuringNASU;
   getParent()->getField(this, IFASTBP_PROC::ACCOUNT_COMMITMENT,ifds::IsDuringNASU,strIsDuringNASU,false);
   strIsDuringNASU.strip().upperCase();
   
   bool bEnableBtn = strIsDuringNASU==I_("Y")?false:true;
   GetDlgItem( IDC_BTN_SUSPEND )->EnableWindow( bEnableBtn );
   GetDlgItem( IDC_BTN_STOP )->EnableWindow( bEnableBtn );
}

//*****************************************************************************
bool AccountCommitmentDlg::doRefresh(GenericInterface * rpGICaller, const I_CHAR* szOriginalCommand )
{ 
   TRACE_METHOD( CLASSNAME, DOREFRESH );
   ConnectControlsToData ();
   LoadControls ();
   SetDlgCaption ();
   return true;
}

//**********************************************************************************
void AccountCommitmentDlg::SetDlgCaption()
{
   TRACE_METHOD( CLASSNAME, I_( "SetDlgCaption" ) );

   DString dstrShrNum, 
      dstrEntityName;


   SetShrAcctCaption (dstrShrNum, m_dstrAccountNum, dstrEntityName);
}


//******************************************************************************
void AccountCommitmentDlg::ControlUpdated(UINT controlID, const DString &strValue )
{
   switch( controlID )
   {
      case IDC_CMB_INVEST_TYPE:
      case IDC_CMB_FORCED_RATE:
         {
         }
      break;

      default:
         break;
   }
}

//******************************************************************************
void AccountCommitmentDlg::DoListItemChanged(
                                 UINT listControlID,
                                 const DString &strKey,
                                 bool bIsNewItem ,
                                 bool bIsDummyItem
                                 )
{
	if( listControlID ==  IDC_LV_COMMITMENTS )
	{
		LoadListControl( IDC_LV_COMMITMENTS_ACTIVITY, &strKey );
	}
}

void AccountCommitmentDlg::OnBtnSuspend()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnSuspend" ) );

   try
   {
      DString status;
      getParent()->getField ( this, IFASTBP_PROC::ACCOUNT_COMMITMENT, ifds::CommitStatus, status, false);  

      DString runMode;
      if(COMMIT_STATUS::ACTIVE == status)
         runMode = RUN_MODES::RUN_MODE_SUSP;
      else if(COMMIT_STATUS::SUSPENDED == status)
         runMode = RUN_MODES::RUN_MODE_RNST;
      
      getParent()->setField ( this, IFASTBP_PROC::ACCOUNT_COMMITMENT, ifds::RunMode, runMode, false);  

   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }
   PostMessage(WM_COMMAND, IDOK);
//   OnOK();
//   Exit(IDOK);
}

void AccountCommitmentDlg::OnBtnStop()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnStop" ) );

   try
   {
      DString status;
      getParent()->getField ( this, IFASTBP_PROC::ACCOUNT_COMMITMENT, ifds::CommitStatus, status, false);  

      DString runMode;
      if(COMMIT_STATUS::ACTIVE == status ||
         COMMIT_STATUS::SUSPENDED == status ||
         COMMIT_STATUS::MATURED == status)
         runMode = RUN_MODES::RUN_MODE_STOP;
      else if(COMMIT_STATUS::STOPPED == status)
         runMode = RUN_MODES::RUN_MODE_REACT;

         getParent()->setField ( this, IFASTBP_PROC::ACCOUNT_COMMITMENT, ifds::RunMode, runMode, false);  
   }
   catch( ConditionException &ce )
   {
      ConditionMessageBox( ce );
   }
   catch( ... )
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_UNKNOWN_EXCEPTION );
   }
//   OnOK();
   PostMessage(WM_COMMAND, IDOK);
//   Exit(IDOK);
}

void AccountCommitmentDlg::OnBtnReset()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnReset"));
   getParent()->reset(this, IFASTBP_PROC::ACCOUNT_COMMITMENT);
   doRefresh( this, NULL_STRING );
}

void AccountCommitmentDlg::OnBtnAdmin() 
{
   ShowAdminDates( IFASTBP_PROC::ACCOUNT_COMMITMENT);
}

void AccountCommitmentDlg::OnBtnBank()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnBank" ) );

   CWaitCursor wait;

   try
   {
      setParameter(MFCAN_IP_PARAM::ACCOUNT_NUM, m_dstrAccountNum);
      setParameter(MFCAN_IP_PARAM::BANK_TYPE, BANKTYPE::ACCOUNT_COMMITMENT);

      E_COMMANDRETURN eRtn = invokeCommand(getParent(), CMD_BPROC_BANK_INSTRUCTIONS, PROC_SUPPORT, true, NULL);

      if (eRtn != CMD_CANCEL)
      {
         showBankData();
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

void AccountCommitmentDlg::UpdateButtons()
{
   DString status;
   getParent()->getField ( this, IFASTBP_PROC::ACCOUNT_COMMITMENT, ifds::CommitStatus, status, false);  
   CString lSuspendString;
   CString lStopString;
   BOOL suspendEnabled = TRUE;
   BOOL stopEnabled = TRUE;

   if(COMMIT_STATUS::ACTIVE == status)
   {
      lSuspendString.LoadString( TXT_BTN_SUSPEND);
      lStopString.LoadString(TXT_BTN_STOP);
      suspendEnabled = TRUE;
      stopEnabled = TRUE;
   }
   else if(COMMIT_STATUS::SUSPENDED == status)
   {
      lSuspendString.LoadString(TXT_BTN_REINSTATE);
      lStopString.LoadString( TXT_BTN_STOP);
      suspendEnabled = TRUE;
      stopEnabled = TRUE;
   }
   else if(COMMIT_STATUS::STOPPED == status)
   {
      lSuspendString.LoadString(TXT_BTN_SUSPEND);
      lStopString.LoadString( TXT_BTN_REACTIVATE);
      suspendEnabled = FALSE;
      stopEnabled = TRUE;
   }
   else if(COMMIT_STATUS::MATURED == status)
   {
      lSuspendString.LoadString( TXT_BTN_SUSPEND);
      lStopString.LoadString(TXT_BTN_STOP);
      suspendEnabled = FALSE;
      stopEnabled = FALSE;
   }
   else
   {
      lSuspendString.LoadString( TXT_BTN_SUSPEND);
      lStopString.LoadString(TXT_BTN_STOP);
   }

   GetDlgItem(IDC_BTN_SUSPEND)->SetWindowText(lSuspendString);
   GetDlgItem(IDC_BTN_STOP)->SetWindowText(lStopString);

   GetDlgItem( IDC_BTN_SUSPEND )->EnableWindow(suspendEnabled);
   GetDlgItem( IDC_BTN_STOP )->EnableWindow(stopEnabled);


   //if(COMMIT_STATUS::ACTIVE == status)
   //{
   //   CString lDispName;
   //   lDispName.LoadString( TXT_BTN_SUSPEND);
   //   GetDlgItem(IDC_BTN_SUSPEND)->SetWindowText(lDispName);
   //}
   //else if(COMMIT_STATUS::SUSPENDED == status)
   //{
   //   CString lDispName;
   //   lDispName.LoadString( TXT_BTN_REINSTATE);
   //   GetDlgItem(IDC_BTN_SUSPEND)->SetWindowText(lDispName);
   //}
   //else if(COMMIT_STATUS::STOPPED == status || COMMIT_STATUS::MATURED == status)
   //{
   //   GetDlgItem( IDC_BTN_SUSPEND )->EnableWindow( FALSE );
   //   GetDlgItem( IDC_BTN_STOP )->EnableWindow( FALSE );
   //}
}

void AccountCommitmentDlg::showBankData()
{
   LoadControl( IDC_EDT_BANK_NAME);
   LoadControl( IDC_EDT_INST_CODE);
   LoadControl( IDC_EDT_TRANSIT_NUMBER);
   LoadControl( IDC_EDT_BANK_ACCT_NBR);
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/AccountCommitmentDlg.cpp-arc  $
// 
//    Rev 1.8   Jun 27 2012 10:34:14   if991250
// next draw date validation, display last proc date
// 
//    Rev 1.7   Jun 19 2012 16:56:06   if991250
// INA: PAC Draw Date
// 
//    Rev 1.6   Apr 02 2012 14:35:22   if991250
// IN 2898290 - showing PAC Amount on the dialog
// 
//    Rev 1.5   Mar 02 2012 12:54:06   if991250
// Account Commitment in NASU
// 
//    Rev 1.4   Feb 27 2012 15:34:32   if991250
// NASU, Commitment Id
// 
//    Rev 1.3   Feb 24 2012 18:44:58   if991250
// Account Commitment
// 
//    Rev 1.2   Feb 22 2012 17:01:48   if991250
// Account Commitment
// 
//    Rev 1.1   Feb 17 2012 10:38:06   if991250
// Account Commitment
// 
//    Rev 1.0   Jan 20 2012 16:12:48   if991250
// Initial revision.
// 
**/