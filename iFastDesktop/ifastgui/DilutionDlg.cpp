//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by IFDS, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1999 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : DilutionDlg.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ----------------------------------------------------------
//
// ^CLASS    : DilutionDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for the Dilution dialog
//
//******************************************************************************

#include "stdafx.h"

#include "mfdstc.h"
#include <uibase\dstedit.h>
#include <uibase\dstlistctrl.h>
#include <uibase\DSTComboBox.h>

///#include "dse_dstcglob_vw.hpp"
#include <ifastcbo\dstcworksession.hpp>
#include "DilutionDlg.h"
#include <ifastbp\Dilutionprocessincludes.h>
#include <bfproc\abstractprocess.hpp>
#include <assert.h>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_DILUTION;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_BROKER;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< DilutionDlg > dlgCreator( CMD_GUI_DILUTION );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME      = I_( "DilutionDlg" );
   const I_CHAR * const LV_Dilution    = I_( "Dilution List" );
   const I_CHAR * const BROKER_CODE    = I_( "BrokerCode" );
   const I_CHAR * const YES       = I_( "Y" );
}

namespace PARAMETER
{
  const I_CHAR * const TRANSID      = I_( "TransId" );
}

namespace UAF
{   
	extern CLASS_IMPORT I_CHAR * const TRANS_HIST_DILUTION_ALLOC_LIST;	
}

namespace CND
{
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId Accountable;     
   extern CLASS_IMPORT const BFTextFieldId DilutionHeadSet;	// Column Heading field
   extern CLASS_IMPORT const BFDateFieldId RespDate;
   extern CLASS_IMPORT const BFDecimalFieldId AllocPercent;
   extern CLASS_IMPORT const BFTextFieldId BackDatedReason;
   extern CLASS_IMPORT const BFTextFieldId InterCode;
   extern CLASS_IMPORT const BFTextFieldId ReadOnly;
   extern CLASS_IMPORT const BFDecimalFieldId RefundAmount;
   extern CLASS_IMPORT const BFDecimalFieldId  DilutionAmount;
   extern CLASS_IMPORT const BFTextFieldId  RefundCurrency;
   extern CLASS_IMPORT const BFDecimalFieldId RefundFXRate;
   extern CLASS_IMPORT const BFTextFieldId RefundOption;
   extern CLASS_IMPORT const BFTextFieldId RefundPayType;
   extern CLASS_IMPORT const BFTextFieldId CPFRefundApplicable;
   extern CLASS_IMPORT const BFTextFieldId ShowDilution;
   extern CLASS_IMPORT const BFTextFieldId ShowExSysDilPymtNSM;
   extern CLASS_IMPORT const BFTextFieldId IsDilutionNSMEligible;
   extern CLASS_IMPORT const BFTextFieldId IsNetworkSettleEligible;
   extern CLASS_IMPORT const BFTextFieldId DilutionLinkNum;
}

UINT hiddenContrls[] = {
   IDC_STATIC_DILUTION_AMOUNT_DILU,
   IDC_EDIT_DILUTION_AMOUNT_DILU,  
   IDC_STATIC_CURRENCY_DILU,       
   IDC_EDIT_REFUND_AMOUNT_DILU,    
   IDC_STATIC_REFUND_AMOUNT_DILU,  
   IDC_STATIC_REFUND_PAYTYPE_DILU, 
   IDC_STATIC_REFUND_OPTION_DILU,  
   IDC_CMB_REFUND_OPTION_DILU,     
   IDC_STATIC_FXRATE_DILU,         
   IDC_EDIT_FXRATE_DILU,           
   IDC_CMB_REFUND_PAYTYPE_DILU,    
   IDC_CMB_CURRENCY_DILU,          
};

UINT numHiddenControl = sizeof(hiddenContrls)/sizeof(UINT); 

UINT expandUpContrls[] = {
   IDC_STATIC_GEN_1,
   IDC_LV_DILUTION_ALLOC,
};

UINT numExpandUpControl = sizeof(expandUpContrls)/sizeof(UINT);

//******************************************************************************

DilutionDlg::DilutionDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( DilutionDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   getParameter( I_( "FromScr" ) ,  _dstrFromScreen );
   getParameter( I_("AllowModify"), _dstrAllowModify );
   //{{AFX_DATA_INIT(DilutionDlg)
   //}}AFX_DATA_INIT
}

//******************************************************************************

DilutionDlg::~DilutionDlg()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************

void DilutionDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(DilutionDlg)
   //}}AFX_DATA_MAP
}

//******************************************************************************

BEGIN_MESSAGE_MAP(DilutionDlg, BaseMainDlg)
//{{AFX_MSG_MAP(DilutionDlg)
ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
ON_BN_CLICKED(IDC_BTN_DELETE, OnBtnDelete)
ON_BN_CLICKED(IDC_BTN_ADM_DATES, OnBtnAdmin)
ON_BN_CLICKED(IDC_BTN_HISTORICAL, OnBtnHistorical )
ON_MESSAGE( UM_OPENBROKERLISTDLG, OpenBrokerListDlg )
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DilutionDlg message handlers

BOOL DilutionDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );

   BaseMainDlg::OnInitDialog();

   DisplayCaption();   

   return(TRUE);  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

//******************************************************************************
void DilutionDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONPOSTINITDIALOG );

   // Dilution Allocations List
   AddListControl( CLASSNAME, IDC_LV_DILUTION_ALLOC, LV_Dilution, ifds::DilutionHeadSet, IFASTBP_PROC::DILUTION_LIST, 0, true );
   
   // Dilution Details
   AddControl( CTRL_COMBO, IDC_CMB_ACCOUNTABILITY, IFASTBP_PROC::DILUTION_LIST, ifds::Accountable, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_DILUTION_ALLOC );
   AddControl( CTRL_EDIT, IDC_EDT_PERCENTAGE, IFASTBP_PROC::DILUTION_LIST, ifds::AllocPercent, CTRLFLAG_DEFAULT, IDC_LV_DILUTION_ALLOC );
   AddControl( CTRL_DATE, IDC_DTP_RESPDATE, IFASTBP_PROC::DILUTION_LIST, ifds::RespDate, CTRLFLAG_DEFAULT, IDC_LV_DILUTION_ALLOC );
   AddControl( CTRL_COMBO, IDC_CMB_REASON_CODE, IFASTBP_PROC::DILUTION_LIST, ifds::BackDatedReason, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_DILUTION_ALLOC );
   AddControl( CTRL_EDIT, IDC_EDT_ASOCIATED_ACCOUNT, IFASTBP_PROC::DILUTION_LIST, ifds::AssociatedAcctNum, CTRLFLAG_DEFAULT, IDC_LV_DILUTION_ALLOC);
   AddControl( CTRL_EDIT, IDC_EDT_BILLING_ENTITY, IFASTBP_PROC::DILUTION_LIST, ifds::BillingToEntity, CTRLFLAG_DEFAULT, IDC_LV_DILUTION_ALLOC);
   AddControl( CTRL_COMBO, IDC_CMB_BILLING_TYPE, IFASTBP_PROC::DILUTION_LIST, ifds::BillingToEntityType, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_DILUTION_ALLOC );
   AddControl( CTRL_COMBO, IDC_CMB_BILLING_ENTITY, IFASTBP_PROC::DILUTION_LIST, ifds::InterCode, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_DILUTION_ALLOC );
   AddControl( CTRL_COMBO, IDC_CMB_EXT_SYS_PYMT_NSM, IFASTBP_PROC::DILUTION_LIST, ifds::ExSysDilPymtNSM, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_DILUTION_ALLOC );
   
   dynamic_cast<DSTEdit *> (GetControl (IDC_EDT_ASOCIATED_ACCOUNT))->SetAllowedChars (I_ ("0123456789"));
   
   DString dstrReadOnly;
   getParent()->getField(this, IFASTBP_PROC::DILUTION_LIST, ifds::ReadOnly, dstrReadOnly);   
   GetDlgItem( IDC_BTN_ADD )->EnableWindow(dstrReadOnly != YES);
   GetDlgItem( IDC_BTN_DELETE )->EnableWindow(dstrReadOnly != YES);

   AddControl( CTRL_EDIT, IDC_EDIT_REFUND_AMOUNT_DILU,   IFASTBP_PROC::DILUTION_LIST ,ifds::RefundAmount,   CTRLFLAG_DEFAULT, IDC_LV_DILUTION_ALLOC);
   AddControl( CTRL_EDIT, IDC_EDIT_DILUTION_AMOUNT_DILU, IFASTBP_PROC::DILUTION_LIST, ifds::DilutionAmount, CTRLFLAG_DEFAULT, IDC_LV_DILUTION_ALLOC );
   AddControl( CTRL_EDIT, IDC_EDIT_FXRATE_DILU,          IFASTBP_PROC::DILUTION_LIST, ifds::RefundFXRate,   CTRLFLAG_DEFAULT, IDC_LV_DILUTION_ALLOC );
   AddControl( CTRL_EDIT, IDC_CMB_CURRENCY_DILU ,        IFASTBP_PROC::DILUTION_LIST, ifds::RefundCurrency, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_DILUTION_ALLOC );
   AddControl( CTRL_COMBO, IDC_CMB_REFUND_OPTION_DILU,   IFASTBP_PROC::DILUTION_LIST, ifds::RefundOption,   CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_DILUTION_ALLOC );
   AddControl( CTRL_COMBO, IDC_CMB_REFUND_PAYTYPE_DILU,  IFASTBP_PROC::DILUTION_LIST, ifds::RefundPayType,  CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_DILUTION_ALLOC );

   AddControl( CTRL_COMBO, IDC_CMB_SETTLE_NETWORK,		 IFASTBP_PROC::DILUTION_LIST, ifds::SettleNetwork,  CTRLFLAG_INITCOMBO_BY_SUB_LIST | CTRLFLAG_INITCOMBO_WITH_BLANK, IDC_LV_DILUTION_ALLOC );
   AddControl( CTRL_COMBO, IDC_CMB_DILUTION_NSM,		 IFASTBP_PROC::DILUTION_LIST, ifds::DilutionNSM,  CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_DILUTION_ALLOC );
   
   AddControl( CTRL_EDIT, IDC_EDT_IFAST_LINKID,			 IFASTBP_PROC::DILUTION_LIST, ifds::DilutionLinkNum, CTRLFLAG_DEFAULT, IDC_LV_DILUTION_ALLOC);
   dynamic_cast<DSTEdit *> (GetControl (IDC_EDT_IFAST_LINKID))->SetAllowedChars (I_ ("0123456789"));
   dynamic_cast<DSTEdit *> (GetControl (IDC_EDT_IFAST_LINKID))->SetMaxCharNum(_dilutionNumMaxLength);

   if ( _dstrFromScreen == I_( "Transaction" ) )
   {
	   bool bEnableControls = false; 

	   if ( I_( "Y" ) == _dstrAllowModify.stripAll().upperCase() )
	   {
		    bEnableControls = hasUpdatePermission(  UAF::TRANS_HIST_DILUTION_ALLOC_LIST )
			               || hasCreatePermission(  UAF::TRANS_HIST_DILUTION_ALLOC_LIST );
		    			
	   }	   

	   GetDlgItem( IDC_BTN_ADD )->EnableWindow( bEnableControls );
	   GetDlgItem( IDC_BTN_DELETE )->EnableWindow( bEnableControls );

	   EnableControl( IDC_CMB_ACCOUNTABILITY, bEnableControls );
	   EnableControl( IDC_EDT_PERCENTAGE,     bEnableControls );
	   EnableControl( IDC_DTP_RESPDATE,       bEnableControls );
	   EnableControl( IDC_CMB_REASON_CODE,    bEnableControls );
	   EnableControl( IDC_EDT_ASOCIATED_ACCOUNT,bEnableControls );
	   EnableControl( IDC_EDT_BILLING_ENTITY,  bEnableControls );
	   EnableControl( IDC_CMB_BILLING_ENTITY,  bEnableControls );
	   EnableControl( IDC_CMB_BILLING_TYPE,    bEnableControls );
       EnableControl( IDC_CMB_EXT_SYS_PYMT_NSM,bEnableControls );
   }

   DString dstrCPFRefundApplicable;
   DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
   dstWorkSession->getOption (ifds::CPFRefundApplicable, dstrCPFRefundApplicable, getParent()->getDataGroupId(), false);
   dstrCPFRefundApplicable.strip().upperCase();

   HideCPFRelatedControls(dstrCPFRefundApplicable == I_("N"));

   doRefresh( this, NULL_STRING );
}

//******************************************************************************

bool DilutionDlg::doRefresh( GenericInterface * rpGICaller, const I_CHAR * szOriginalCommand )
{
   DisplayCaption();
   ConnectControlsToData();
   LoadListControl( IDC_LV_DILUTION_ALLOC );

   DString dstrIsSettleNetworkEligible, dstrIsDilutionNSMEligible, dstrShowDilution;
   getParent()->getField(this, IFASTBP_PROC::DILUTION_LIST, ifds::IsNetworkSettleEligible, dstrIsSettleNetworkEligible, false);
   getParent()->getField(this, IFASTBP_PROC::DILUTION_LIST, ifds::IsDilutionNSMEligible, dstrIsDilutionNSMEligible, false);

   DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
   dstWorkSession->getOption (ifds::ShowDilution, dstrShowDilution, getParent()->getDataGroupId(), false);
   bool bHideDilutionNSM = ShowHideDilutiontNSMField(dstrShowDilution != I_("N"));

   GetDlgItem(IDC_TXT_SETTLE_NETWORK)->ShowWindow(dstrIsSettleNetworkEligible == YES ? SW_SHOW:SW_HIDE);
   GetDlgItem(IDC_CMB_SETTLE_NETWORK)->ShowWindow(dstrIsSettleNetworkEligible == YES ? SW_SHOW:SW_HIDE);
   
   GetDlgItem(IDC_TXT_DILUTION_NSM)->ShowWindow(bHideDilutionNSM ? SW_HIDE : SW_SHOW);
   GetDlgItem(IDC_CMB_DILUTION_NSM)->ShowWindow(bHideDilutionNSM ? SW_HIDE : SW_SHOW);

   return( true );
}

//******************************************************************************

void DilutionDlg::OnBtnAdd() 
{
   AddToListControl( IDC_LV_DILUTION_ALLOC );           
}

//******************************************************************************

void DilutionDlg::OnBtnDelete() 
{
   DeleteFromListControl( IDC_LV_DILUTION_ALLOC );      
}

//******************************************************************************
void DilutionDlg::OnBtnAdmin() 
{
   ShowAdminDates(IFASTBP_PROC::DILUTION_LIST);
}

//******************************************************************************

void DilutionDlg::DisplayCaption() 
{
   DString dstrTransId;

   // Get TransId
   //getParent()->getField(this, IFASTBP_PROC::MFACCOUNT_CBO, ifds::TransId, dstrTransId);
   //dstrTransId.stripLeading();   
}

//******************************************************************************
void DilutionDlg::ControlUpdated(UINT controlID, const DString &strValue )
{
   if( controlID == IDC_CMB_BILLING_TYPE )
   {
	   bool bBroker = false;
	   bool bInter = false;

	   if (strValue == I_("BROK") || strValue == I_(""))
	   {
		   bBroker = true;
		   bInter = false;
	   }
	   else if (strValue == I_("INTR"))
	   {
         bBroker = false;
		   bInter = true;
	   }
	   GetDlgItem(IDC_EDT_BILLING_ENTITY)->ShowWindow (bBroker);
	   GetDlgItem (IDC_CMB_BILLING_ENTITY)->ShowWindow (bInter);
   }
   else if ( controlID == IDC_EDT_BILLING_ENTITY || 
             controlID == IDC_CMB_BILLING_ENTITY)
   {
      DString dstrShowDilution, dstrShowExSysDilPymtNSM;
      DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
      dstWorkSession->getOption (ifds::ShowDilution, dstrShowDilution, getParent()->getDataGroupId(), false);
      dstWorkSession->getOption (ifds::ShowExSysDilPymtNSM, dstrShowExSysDilPymtNSM, getParent()->getDataGroupId(), false);
      dstrShowDilution.strip().upperCase();
      dstrShowExSysDilPymtNSM.strip().upperCase();

      bool bHideExtSysPaymentNSM = ShowHideExSysDilPymtNSMField(dstrShowExSysDilPymtNSM != I_("N"));

      GetDlgItem(IDC_STATIC_GEN_9)->ShowWindow(bHideExtSysPaymentNSM ? SW_HIDE : SW_SHOW);
      GetDlgItem(IDC_CMB_EXT_SYS_PYMT_NSM)->ShowWindow(bHideExtSysPaymentNSM ? SW_HIDE : SW_SHOW);
   }
   else if ( controlID == IDC_EDIT_DILUTION_AMOUNT_DILU )
   {
		DString dstrDiluationAvail, dstrDilAmount = I_("Unknown");
		getParent()->getField(this, IFASTBP_PROC::DILUTION_LIST, ifds::DilutionAvail, dstrDiluationAvail); 
		if( dstrDiluationAvail == I_("N"))
		{
			GetDlgItem( IDC_EDIT_DILUTION_AMOUNT_DILU )->SetWindowText(dstrDilAmount.c_str());
		}
   }

   if (controlID == IDC_CMB_BILLING_TYPE || 
	   controlID == IDC_CMB_BILLING_ENTITY ||
	   controlID == IDC_EDT_BILLING_ENTITY ||
	   controlID == IDC_BTN_ADD ||
	   controlID == IDC_BTN_DELETE ||
      controlID == IDC_CMB_ACCOUNTABILITY)
   {
	   DString dstrIsDilutionNSMEligible;
	   getParent()->getField(this, IFASTBP_PROC::DILUTION_LIST, ifds::IsDilutionNSMEligible, dstrIsDilutionNSMEligible, false);
	   const int show = dstrIsDilutionNSMEligible == I_("Y") ? SW_SHOW: SW_HIDE;
	   
	   GetDlgItem(IDC_CMB_DILUTION_NSM)->ShowWindow(show);
	   GetDlgItem(IDC_TXT_DILUTION_NSM)->ShowWindow(show);
	   /* When showing dilution N$M first time. check value before displaying iFastLinkID */
	   DString dstrDilutionNSM;
	   getParent()->getField(this, IFASTBP_PROC::DILUTION_LIST, ifds::DilutionNSM, dstrDilutionNSM, false);
	   const int showLinkID = dstrIsDilutionNSMEligible == I_("Y") && dstrDilutionNSM == I_("02") ? SW_SHOW: SW_HIDE;
	   GetDlgItem(IDC_EDT_IFAST_LINKID)->ShowWindow(showLinkID);
	   GetDlgItem(IDC_TXT_IFAST_LINKID)->ShowWindow(showLinkID);
   }
   if( controlID = IDC_CMB_SETTLE_NETWORK || controlID == IDC_CMB_DILUTION_NSM)
   {
	   /* When settle network = FRSV or dilutionNSM = yes, displaying iFastLinkID */
	   DString dstrSettleNetwork, dstrDilutionNSM;
	   getParent()->getField(this, IFASTBP_PROC::DILUTION_LIST, ifds::SettleNetwork, dstrSettleNetwork, false);
	   getParent()->getField(this, IFASTBP_PROC::DILUTION_LIST, ifds::DilutionNSM, dstrDilutionNSM, false);

	   const int show = dstrSettleNetwork == I_("FSRV") || dstrDilutionNSM == I_("02") ? SW_SHOW:SW_HIDE;
	   
	   GetDlgItem(IDC_EDT_IFAST_LINKID)->ShowWindow(show);
	   GetDlgItem(IDC_TXT_IFAST_LINKID)->ShowWindow(show);
   }
}

//******************************************************************
BOOL DilutionDlg::PreTranslateMessage( MSG* pMsg ) 
{
   if( pMsg->message == WM_KEYDOWN && (int)(pMsg->wParam) == VK_F4 )
   {
      if( GetFocus()== GetDlgItem( IDC_EDT_BILLING_ENTITY ) )
         PostMessage( UM_OPENBROKERLISTDLG );
   }

   return(BaseMainDlg::PreTranslateMessage( pMsg ));
}

//******************************************************************
LRESULT DilutionDlg::OpenBrokerListDlg( WPARAM, LPARAM )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenBrokerListDlg" ) );

	try
	{
		E_COMMANDRETURN eRtn = CMD_CANCEL;
		CWaitCursor wait;
		DString brokerCode;

		GetControlText( IDC_EDT_BILLING_ENTITY, brokerCode );
		setParameter(BROKER_CODE, brokerCode);
		
		//invoke the broker dialog and process
		eRtn = invokeCommand( getParent(), CMD_BPROC_BROKER, PROC_SUPPORT, true, NULL );
		switch( eRtn )
		{
			case CMD_OK:
			case CMD_MODELESS_INPROCESS:
            {
				DString brokerCode;

				getParameter(BROKER_CODE, brokerCode );
				if( brokerCode != NULL_STRING )
				{
					GetDlgItem(IDC_EDT_BILLING_ENTITY)->SetWindowText( brokerCode.c_str() );
					
					//bool success = SetControlText( IDC_EDT_BILLING_ENTITY, brokerCode );
					/* BaseControl * pBC = dynamic_cast< BaseControl *> (GetDlgItem( IDC_EDT_BILLING_ENTITY ));
					if( !success && pBC )
						pBC->Load();
					if( pBC && pBC->IsToolTipVisible() )
						pBC->ToggleToolTip();*/
				}
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
void DilutionDlg::OnBtnHistorical()
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnHistorical"));
   CWaitCursor wait;

   IFastHistoricalInfo historicalInfo;
   historicalInfo( this, IFASTBP_PROC::DILUTION_LIST, I_( "SINGLE" ) );
}

//******************************************************************************
void DilutionDlg::HideCPFRelatedControls(bool bHideAndExpand)
{
   if(bHideAndExpand)
   {
      unsigned int i = 0;
      for(i=0;i<numHiddenControl;i++)
      {
         CWnd *pWnd = GetDlgItem(hiddenContrls[i]);

         if(pWnd)
         {
            pWnd->ShowWindow(SW_HIDE);
         }
      }

      for(i=0;i<numExpandUpControl;i++)
      {
         CWnd *pWnd = GetDlgItem(expandUpContrls[i]);

         if(pWnd)
         {
            WINDOWPLACEMENT wndPlacement;
            wndPlacement.length = sizeof(WINDOWPLACEMENT);
            pWnd->GetWindowPlacement(&wndPlacement);
            wndPlacement.rcNormalPosition.top -= 80;
            pWnd->SetWindowPlacement(&wndPlacement);
         }
      }
   }
}

//******************************************************************************
void DilutionDlg::DoListItemChanged( UINT listControlID,
                                     const DString &strKey,
                                     bool bIsNewItem ,
                                     bool bIsDummyItem )
{
   DString dstrShowDilution, dstrShowExSysDilPymtNSM;
   DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
   dstWorkSession->getOption (ifds::ShowDilution, dstrShowDilution, getParent()->getDataGroupId(), false);
   dstWorkSession->getOption (ifds::ShowExSysDilPymtNSM, dstrShowExSysDilPymtNSM, getParent()->getDataGroupId(), false);
   dstrShowDilution.strip().upperCase();
   dstrShowExSysDilPymtNSM.strip().upperCase();

   if( listControlID == IDC_LV_DILUTION_ALLOC )
   {
      // History
      GetDlgItem(IDC_BTN_HISTORICAL)->EnableWindow( (bIsNewItem || bIsDummyItem) ? false : true );
      // Admin
      GetDlgItem(IDC_BTN_ADM_DATES)->EnableWindow( (bIsNewItem || bIsDummyItem) ? false : true );

      bool bHideExtSysPaymentNSM = ShowHideExSysDilPymtNSMField(dstrShowExSysDilPymtNSM != I_("N"));
      bool bHideDilutionNSM = ShowHideDilutiontNSMField(dstrShowDilution != I_("N"));

      GetDlgItem(IDC_STATIC_GEN_9)->ShowWindow(bHideExtSysPaymentNSM ? SW_HIDE : SW_SHOW);
      GetDlgItem(IDC_CMB_EXT_SYS_PYMT_NSM)->ShowWindow(bHideExtSysPaymentNSM ? SW_HIDE : SW_SHOW);

      GetDlgItem(IDC_TXT_DILUTION_NSM)->ShowWindow(bHideDilutionNSM ? SW_HIDE : SW_SHOW);
      GetDlgItem(IDC_CMB_DILUTION_NSM)->ShowWindow(bHideDilutionNSM ? SW_HIDE : SW_SHOW);
   }
}

//******************************************************************************
bool DilutionDlg::ShowHideExSysDilPymtNSMField(bool bSystemFlagToShow)
{
   bool bResult = true;

   DString strShowExSysDilPymtNSM;
   getParent()->getField(this, IFASTBP_PROC::DILUTION_LIST, ifds::ShowExSysDilPymtNSM, strShowExSysDilPymtNSM, false); 
   strShowExSysDilPymtNSM.strip().upperCase();

   // system flag will be higher than record level flag
   if(bSystemFlagToShow)
   {
      bResult = strShowExSysDilPymtNSM != I_("Y");
   }

   // return true to hide field and false to show field!
   return  bResult;
}

//******************************************************************************
bool DilutionDlg::ShowHideDilutiontNSMField(bool bSystemFlagToShow)
{
   bool bResult = true;

   DString strShowDilution;
   getParent()->getField(this, IFASTBP_PROC::DILUTION_LIST, ifds::ShowDilution, strShowDilution, false); 
   strShowDilution.strip().upperCase();

   // system flag will be higher than record level flag
   if(bSystemFlagToShow)
   {
      bResult = strShowDilution != I_("Y");
   }

   // return true to hide field and false to show field!
   return  bResult;
}

//******************************************************************************
bool DilutionDlg::GetDataForControl(UINT controlID, DString &dstrValueOut, bool bFormatted, int index) const
{
	bool bReturn = false;

	switch(controlID)
	{
		case IDC_EDT_IFAST_LINKID:
			{
				if((dstrValueOut.stripAll()).length() > 0)
				{
					getParent()->getField(this, IFASTBP_PROC::DILUTION_LIST, ifds::DilutionLinkNum, dstrValueOut, false);
					dstrValueOut.padLeft(_dilutionNumMaxLength, I_('0'));
					bReturn = true;
				}
				break;
			}
		default:
			break;
	}
	return(bReturn);
}

//******************************************************************************
bool DilutionDlg::SetDataFromControl(UINT controlID, const DString &dstrValue, bool bFormatted, SEVERITY &sevRtn, int index)
{
	bool bReturn = false;
	sevRtn = NO_CONDITION;
	
	switch (controlID)
	{
		case IDC_EDT_IFAST_LINKID:
			{
				DString dstr = dstrValue;
				if((dstr.stripAll()).length() > 0)
				{					
					dstr.padLeft(_dilutionNumMaxLength, I_('0'));
					GetDlgItem(IDC_EDT_IFAST_LINKID)->SetWindowText(dstr.c_str());
					sevRtn = getParent()->setField(this, IFASTBP_PROC::DILUTION_LIST, ifds::DilutionLinkNum, dstr, false);
					bReturn = true;
				}
				break;
			}
		default:
			break;
	}
	return(bReturn);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/DilutionDlg.cpp-arc  $
// 
//    Rev 1.8   May 11 2012 15:20:18   wp040027
// PETP0187485-CPF-Dilution
// 
//    Rev 1.7   31 Aug 2007 11:11:24   popescu
// PET 2360 FN11 - Dilution.
// 
//    Rev 1.6   31 Aug 2007 10:11:10   popescu
// PET 2360 FN11 - Dilution.
// 
//    Rev 1.5   Aug 30 2007 15:20:56   jankovii
// PET 2360 FN11 - Dilution.
// 
//    Rev 1.4   Jan 30 2006 11:10:12   porteanm
// Incident 424704 - gap - TranshistDilutionAlloc update support.
// 
//    Rev 1.3   Jan 09 2006 17:07:30   porteanm
// Incident 424704 - gap - TranshistDilutionAlloc update support.
// 
//    Rev 1.2   Sep 15 2005 15:11:18   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.1   Jun 01 2005 15:49:58   ZHANGCEL
// Incident #323301 and #322193 : Change ReasonCode to BackDatedReason
// 
//    Rev 1.0   Mar 03 2005 18:21:58   Fengyong
// Initial revision.
// 
 */
