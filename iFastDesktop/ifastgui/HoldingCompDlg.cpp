//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Canada, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2002 by International Financial  Ltd.
//
//******************************************************************************
//
// ^FILE   : HoldingCompDlg.h
// ^AUTHOR : 
// ^DATE   : 07/26/04
//
// ^CLASS    : HoldingCompDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

#include "stdafx.h"

#ifndef IFASTGUI_H
   #include "mfdstc.h"
#endif

#ifndef DSTEDIT_H
   #include <uibase\DSTEdit.h>
#endif
#include "holdingcompdlg.h"
#include <ifastbp\holdingcompprocessinclude.h>
#include <uibase\DSTListCtrl.h>
#include <uibase\DSTComboBox.h>
#include <ifastgui\ifasthistoricalinfo.hpp>
#include <bfproc\abstractprocess.hpp>


extern CLASS_IMPORT const I_CHAR* CMD_GUI_HOLDING_COMP;
#include <bfproc\concretedialogcreator.hpp>
#include <ifastcbo/DSTCWorkSession.hpp>
#include <ifastcbo/MgmtCoOptions.hpp>
#include <discardmsgdlg.h>

static ConcreteDialogCreator< HoldingCompDlg > dlgCreator( CMD_GUI_HOLDING_COMP );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ACCOUNT_ASSOCIATION;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ADDITIONAL_ASSETS;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_INVOICE_INSTRUCTION;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_REPORT_GROUP;

namespace MFCAN_IP_PARAM
{
   extern IFASTBP_LINKAGE const I_CHAR * const HOLDING_COMP_CODE;
   extern IFASTBP_LINKAGE const I_CHAR * const HOLDING_COMP_NAME;
}

namespace
{
   const I_CHAR * const CLASSNAME                     = I_( "HoldingCompDlg" );
   const I_CHAR * const YES                           = I_( "Y" );
   const I_CHAR * const NO                            = I_( "N" );

   const I_CHAR* const  LV_FEE_MODEL_LIST             = I_( "HoldingComp" );
   const I_CHAR* const  LV_SCALE_FEE                  = I_( "ScaleFee" );
   const I_CHAR* const  PERCENT                       = I_( "Percent" );
   const I_CHAR * const FLAT                          = I_( "0" );
   const I_CHAR * const PERCENTAGE                    = I_( "1" );
   const I_CHAR * const SCALE                         = I_( "2" );
   const I_CHAR * const TIER                          = I_( "3" );
   const I_CHAR * const FEE_CODE_MANAGEMENT_FEE       = I_("18");
   const I_CHAR * const FEE_CPDE_MANAGEMENT_REBATE    = I_("95");
   const I_CHAR * const FEE_CODE_MANAGEMENT_DISCOUNT  = I_("180");


   const I_CHAR * const NUMBERS = I_("0123456789.");
   const I_CHAR * const	NOT_APPLY  =  I_("NA");
}

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FEE_MODEL;

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const HOLDING_COMP_MAINT;
}

namespace ifds
{   
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFDateFieldId StopDate;
   extern CLASS_IMPORT const BFTextFieldId LV_HoldingComp;
   extern CLASS_IMPORT const BFTextFieldId InvApplicable;
   extern CLASS_IMPORT const BFTextFieldId RptGrpApplicable;
}

//******************************************************************************

HoldingCompDlg::HoldingCompDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( HoldingCompDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   m_rbSearchBy = 1;
   isProcSupport = getProcessType() == PROC_SUPPORT;
   //{{AFX_DATA_INIT(HoldingCompDlg)
   // NOTE: the ClassWizard will add member initialization here
   //}}AFX_DATA_INIT
}

//******************************************************************************
HoldingCompDlg::~HoldingCompDlg()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}
//******************************************************************************

void HoldingCompDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange( pDX );
   //{{AFX_DATA_MAP(HoldingCompDlg)
   // NOTE: the ClassWizard will add DDX and DDV calls here
   DDX_Radio(pDX, IDC_RB_SRC_ALL, m_rbSearchBy);
   //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(HoldingCompDlg, BaseMainDlg)
//{{AFX_MSG_MAP(HoldingCompDlg)
ON_BN_CLICKED(IDC_BTN_SEARCH, OnBtnSearch)
ON_BN_CLICKED(IDC_BTN_RESET, OnBtnReset)
ON_BN_CLICKED(IDC_BTN_ADD, OnBtnAdd)
ON_BN_CLICKED(IDC_BTN_DEL, OnBtnDel)
ON_BN_CLICKED(IDC_BTN_MORE, OnBtnMore)
ON_BN_CLICKED(IDC_BTN_ADM_DATES, OnBtnAdmDates)
ON_BN_CLICKED(IDC_BTN_FEE_MODEL, OnBtnFeeModel)
ON_BN_CLICKED(IDC_BTN_INVOICE_INSTR, OnBtnInvoiceInstr)
ON_BN_CLICKED(IDC_BTN_REPORTING_GROUP, OnBtnReportingGroup)
ON_BN_CLICKED(IDC_BTN_ADDITIONAL_ASSETS, OnBtnAdditionalAssets)
ON_BN_CLICKED(IDC_BTN_ACCOUNT_LIST, OnBtnAccountList)
ON_BN_CLICKED(IDC_RB_SRC_ALL,      OnBtnSearchAll)
ON_BN_CLICKED(IDC_RB_SRC_EFF_DATE, OnBtnSearchEffDate)
ON_BN_CLICKED(IDC_BTN_HISTORICAL, OnBtnHistorical)
//}}AFX_MSG_MAP

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// HoldingCompDlg message handlers


//******************************************************************************
void HoldingCompDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, I_( "OnPostInitDialog" ) );
   //SetUserAccesFunctionCode(UAF::FEE_MODEL);
   //addBtnAddForPermissionCheck(IDC_BTN_ADD, IDC_LST_HOLDING_COMPANIES);
   //addBtnDeleteForPermissionCheck(IDC_BTN_DEL, IDC_LST_HOLDING_COMPANIES);
   SetUserAccesFunctionCode (UAF::HOLDING_COMP_MAINT);
	addControlGroupIDForPermissionCheck (IDC_LST_HOLDING_COMPANIES);
   addBtnAddForPermissionCheck(IDC_BTN_ADD, IDC_LST_HOLDING_COMPANIES);
   addBtnDeleteForPermissionCheck(IDC_BTN_DEL, IDC_LST_HOLDING_COMPANIES);

   addControls();
   doRefresh(this, NULL);
   GetDlgItem(IDC_BTN_MORE)->EnableWindow( getParent()->doMoreRecordsExist( this, BF::AllContainerIds ) );
}

//******************************************************************************
SEVERITY HoldingCompDlg::doInit()
{
   SEVERITY sevRtn = SEVERE_ERROR;

   sevRtn = NO_CONDITION;
   getParent()->getParameter( HOLDINGCOMP::FROM_SCR, m_frSCR );

   return(sevRtn);
}
//******************************************************************************
void HoldingCompDlg::addControls( )
{
   TRACE_METHOD( CLASSNAME, I_( "addControls" ) );
   int controlFlags = isProcSupport ? CTRLFLAG_NOT_UPDATABLE : 0;

   AddControl( CTRL_EDIT, IDC_EDT_SRC_HLD_COMP_CODE, BF::NullContainerId, ifds::SrcHoldingCompCode,0,0);
   AddControl( CTRL_EDIT, IDC_EDT_SRC_HLD_COMP_NAME, BF::NullContainerId, ifds::SrcHoldingCompName,0,0);
   
   AddControl( CTRL_CHECKBOX, IDC_RB_SRC_ALL, CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_GUI_FIELD );
   AddControl( CTRL_CHECKBOX, IDC_RB_SRC_EFF_DATE, CTRLFLAG_NOT_UPDATABLE | CTRLFLAG_GUI_FIELD );
   AddControl( CTRL_DATE,     IDC_DTP_SRC_EFFECTIVE, BF::NullContainerId, ifds::AsofDate,0,0);
   
   ConnectControlToData(IDC_DTP_SRC_EFFECTIVE, true);
   LoadControl(IDC_DTP_SRC_EFFECTIVE);


   AddListControl( CLASSNAME, IDC_LST_HOLDING_COMPANIES, I_("HOLDING COMPANIES"), 
      ifds::LV_HoldingComp, IFASTBP_PROC::HOLDING_COMP_LIST, controlFlags, true );

   AddControl( CTRL_EDIT,    IDC_EDT_HLD_CO_CODE,   IFASTBP_PROC::HOLDING_COMP_LIST, 
               ifds::WhereUseKey,controlFlags,IDC_LST_HOLDING_COMPANIES);
   AddControl( CTRL_EDIT,    IDC_EDT_HLD_CO_NAME,   IFASTBP_PROC::HOLDING_COMP_LIST, 
               ifds::HoldingCompName,controlFlags,IDC_LST_HOLDING_COMPANIES);
   AddControl( CTRL_COMBO,   IDC_CMB_USAGE,   IFASTBP_PROC::HOLDING_COMP_LIST, 
               ifds::CompanyUsage,controlFlags|CTRLFLAG_INITCOMBO_BY_SUB_LIST,IDC_LST_HOLDING_COMPANIES);
   AddControl( CTRL_COMBO,   IDC_CMB_ASSET_AGGR_TYPE,   IFASTBP_PROC::HOLDING_COMP_LIST, 
               ifds::AggregationMethod,controlFlags | CTRLFLAG_INITCOMBO_BY_SUB_LIST,IDC_LST_HOLDING_COMPANIES);
   AddControl( CTRL_COMBO,   IDC_CMB_LANGUAGE,   IFASTBP_PROC::HOLDING_COMP_LIST, 
               ifds::Language,controlFlags | CTRLFLAG_INITCOMBO_BY_SUB_LIST,IDC_LST_HOLDING_COMPANIES);
   
   
   AddControl( CTRL_DATE,   IDC_DTP_EFFECTIVE_DATE,   IFASTBP_PROC::HOLDING_COMP_LIST, 
               ifds::Deff,controlFlags,IDC_LST_HOLDING_COMPANIES);
   AddControl( CTRL_DATE,   IDC_DTP_STOP_DATE,   IFASTBP_PROC::HOLDING_COMP_LIST, 
               ifds::StopDate,controlFlags,IDC_LST_HOLDING_COMPANIES);

   //dynamic_cast<DSTEdit*>(GetControl( IDC_EDT_MODEL_CODE ) )->SetMaxCharNum( 6 );

}

//*********************************************************************************
void HoldingCompDlg::ControlUpdated(UINT controlID,
                                 const DString &strValue )
{
   switch( controlID )
   {
      case IDC_CMB_USAGE: //FeeCode
      case IDC_CMB_ASSET_AGGR_TYPE: //FeeCode
         {
            EnableDisableButtons();
         }
         break; 
/*	  case IDC_CMB_USAGE:
		 {
			GetDlgItem( IDC_BTN_INVOICE_INSTR )->EnableWindow( true );
			GetDlgItem( IDC_BTN_REPORTING_GROUP )->EnableWindow( true );
			
			DString dstrUsageCode;
			getParent()->getField(this, IFASTBP_PROC::HOLDING_COMP_LIST, ifds::CompanyUsage, dstrUsageCode, false);
			dstrUsageCode.strip().upperCase();
		    
			if( !dstrUsageCode.empty()){
				if (dstrUsageCode == I_( "MF" )){
					GetDlgItem( IDC_BTN_INVOICE_INSTR )->EnableWindow( true && (dstrInvApplicable == I_("1") ) );
					GetDlgItem( IDC_BTN_REPORTING_GROUP )->EnableWindow( false );
				}
				if (dstrUsageCode == I_( "MFR" )){
					GetDlgItem( IDC_BTN_INVOICE_INSTR )->EnableWindow( false );
					GetDlgItem( IDC_BTN_REPORTING_GROUP )->EnableWindow( true && (dstrRptGrpApplicable == I_("1") ) );
				}
			}
		 }
		 break;
	  case IDC_CMB_ASSET_AGGR_TYPE:
		 {
			GetDlgItem( IDC_BTN_ADDITIONAL_ASSETS )->EnableWindow( false );
			
			DString dstrAggrTypeCode;
			getParent()->getField(this, IFASTBP_PROC::HOLDING_COMP_LIST, ifds::AggregationMethod, dstrAggrTypeCode, false);
			dstrAggrTypeCode.strip().upperCase();

			DSTComboBox *dstcomboAggrTypeCode = dynamic_cast< DSTComboBox * >( GetDlgItem( IDC_CMB_ASSET_AGGR_TYPE ) );
			if( !dstrAggrTypeCode.empty() ){
				if (dstrAggrTypeCode == I_( "TGA" )){
					GetDlgItem( IDC_BTN_ADDITIONAL_ASSETS )->EnableWindow( true );
				}
			}
		 }
		 break; */
      default:
         break;

   }
}
//******************************************************************************
void HoldingCompDlg::SetDlgCaption()
{
   TRACE_METHOD( CLASSNAME, I_( "SetDlgCaption" ) );
/*   DString strShrNum, strAccountNum, strEmptyString,dstrEntityName;
   getParent()->getField(this, IFASTBP_PROC::MFACOUNT, ifds::ShrNum, strShrNum, false);
   getParent()->getField(this, IFASTBP_PROC::MFACOUNT, ifds::AccountNum, strAccountNum, false);
   getParent()->getField( this, FEEPARAM::PRIMARY_ACCOUNT_OWNER, dstrEntityName );

   SetShrAcctCaption(strShrNum, strAccountNum, dstrEntityName);*/
}

//******************************************************************************

bool HoldingCompDlg::doRefresh( GenericInterface * rpGICaller, 
                             const I_CHAR * szOriginalCommand )
{
   TRACE_METHOD( CLASSNAME, I_( "doRefresh" ) );

   SetDlgCaption();
   ConnectControlsToData();
   LoadListControl(IDC_LST_HOLDING_COMPANIES);

   return(true);
}

//******************************************************************************
void HoldingCompDlg::OnBtnReset() 
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnReset" ) );
   ResetListItem( IDC_LST_HOLDING_COMPANIES );
   GetList( IDC_LST_HOLDING_COMPANIES )->SetFocus();  
}

//*********************************************************************************

void HoldingCompDlg::OnBtnAdd()
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnAdd" ) );
   AddToListControl( IDC_LST_HOLDING_COMPANIES);
   GetList( IDC_LST_HOLDING_COMPANIES )->SetFocus();
}

//********************************************************************************
void HoldingCompDlg::OnBtnDel()
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnDel" ) );

   bool bDelete = true;
   AbstractProcess* parent = (AbstractProcess*)getParent();
      
   bool isNew =  parent->isCurrentListItemNew(this, IFASTBP_PROC::HOLDING_COMP_LIST);   
   
   if( !isNew && IDNO == AfxMessageBox( TXT_HOLD_COMP_DEL_WARNING, MB_YESNO ) )
		bDelete = false;

   if(bDelete)
   {
      DeleteFromListControl( IDC_LST_HOLDING_COMPANIES );
   }
   GetList( IDC_LST_HOLDING_COMPANIES )->SetFocus();
}

//******************************************************************************
void HoldingCompDlg::DoListItemChanged(UINT listControlID, const DString &strKey,
                                       bool bIsNewItem, bool bIsDummyItem)
{
	if(listControlID ==  IDC_LST_HOLDING_COMPANIES)
	{
		EnableDisableButtons();
	}
}

void HoldingCompDlg::EnableDisableButtons()
{
   bool newItem = true;
   AbstractProcess* pHoldingCompProc = dynamic_cast<AbstractProcess*>(getParent());
   if(pHoldingCompProc)
   {
      newItem  = pHoldingCompProc->isCurrentListItemNew(this, IFASTBP_PROC::HOLDING_COMP_LIST);
   }

   
   DString dstrFeeModelExist;
   DString dstrFeeAggregationExist;
   DString dstrBillingInstrExist;
   DString dstrReportGroupExist;   
   DString dstrShrAcctLastProcDate;
   DString dstrCompanyUsage;
   DString dstrAggregationMethod;
   DString dstrRptGrpApplicable;
   DString dstrInvApplicable;

   DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
   dstWorkSession->getOption( ifds::InvApplicable, dstrInvApplicable, BF::HOST, false );
   dstWorkSession->getOption( ifds::RptGrpApplicable, dstrRptGrpApplicable, BF::HOST, false );

   getParent()->getField(this, IFASTBP_PROC::HOLDING_COMP_LIST, ifds::FeeModelExist,       dstrFeeModelExist);
   getParent()->getField(this, IFASTBP_PROC::HOLDING_COMP_LIST, ifds::FeeAggregationExist, dstrFeeAggregationExist);
   getParent()->getField(this, IFASTBP_PROC::HOLDING_COMP_LIST, ifds::BillingInstrExist,   dstrBillingInstrExist);
   getParent()->getField(this, IFASTBP_PROC::HOLDING_COMP_LIST, ifds::ReportGroupExist,    dstrReportGroupExist);
   getParent()->getField(this, IFASTBP_PROC::HOLDING_COMP_LIST, ifds::ShrAcctLastProcDate, dstrShrAcctLastProcDate);
   getParent()->getField(this, IFASTBP_PROC::HOLDING_COMP_LIST, ifds::CompanyUsage,        dstrCompanyUsage, false);
   getParent()->getField(this, IFASTBP_PROC::HOLDING_COMP_LIST, ifds::AggregationMethod,   dstrAggregationMethod, false);
   
   int bAllowDelete            =  isProcSupport || dstrShrAcctLastProcDate.strip() != I_("")    ? FALSE : TRUE;
   int bEnableInvInstr         = !isProcSupport && dstrCompanyUsage.strip()        == I_("MF")  && dstrInvApplicable == I_("1") && !newItem ? TRUE : FALSE;
   int bEnableReportGroup      = !isProcSupport && dstrCompanyUsage.strip()        == I_("MFR") && dstrRptGrpApplicable == I_("1") && !newItem ? TRUE : FALSE;
   int bEnableAdditionalAssets = !isProcSupport && dstrAggregationMethod.strip()   == I_("TGA") && !newItem ? TRUE : FALSE;
   int bEnableFeeModel         = !isProcSupport && !newItem ? TRUE : FALSE;
   int bEnableAccountList      = !isProcSupport && !newItem ? TRUE : FALSE;

   GetDlgItem(IDC_BTN_DEL)->EnableWindow(bAllowDelete);
   GetDlgItem(IDC_BTN_INVOICE_INSTR)->EnableWindow(bEnableInvInstr);
   GetDlgItem(IDC_BTN_REPORTING_GROUP)->EnableWindow(bEnableReportGroup);
   GetDlgItem(IDC_BTN_ADDITIONAL_ASSETS)->EnableWindow(bEnableAdditionalAssets);

   GetDlgItem(IDC_BTN_FEE_MODEL)->EnableWindow(bEnableFeeModel);
   GetDlgItem(IDC_BTN_ACCOUNT_LIST)->EnableWindow(bEnableAccountList);

   GetDlgItem(IDC_BTN_ADD)->EnableWindow(!isProcSupport);
   GetDlgItem(IDC_BTN_HISTORICAL)->EnableWindow(!isProcSupport);
   GetDlgItem(IDC_BTN_ADM_DATES)->EnableWindow(!isProcSupport);
   GetDlgItem(IDC_BTN_RESET)->EnableWindow(!isProcSupport);
}

//**********************************************************************************
bool HoldingCompDlg::doDisablePermCheckButton(UINT nID)
{
   if(nID == IDC_BTN_DEL)
   {      
      DString dstrShrAcctLastProcDate;
      getParent()->getField(this, IFASTBP_PROC::HOLDING_COMP_LIST, ifds::ShrAcctLastProcDate, dstrShrAcctLastProcDate);
      int bAllowDelete =  isProcSupport || dstrShrAcctLastProcDate.strip() != I_("")    ? FALSE : TRUE;
      if(!bAllowDelete)
         return true;
   }

   return false;
}




//**********************************************************************************
void HoldingCompDlg::OnBtnMore()
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnMoreFeeParam" ) );
   CWaitCursor wait;
   static int cursel;
   cursel = GetList( IDC_LST_HOLDING_COMPANIES )->GetNextItem(-1, LVIS_SELECTED | LVNI_FOCUSED);  
   const DString *crtKey = &getParent()->getCurrentListItemKey( this,IFASTBP_PROC::HOLDING_COMP_LIST );
   if( getParent()->performSearch( this, BF::AllContainerIds, SEARCH_NEXT_BLOCK ) <= WARNING )
   {
      LoadListControl( IDC_LST_HOLDING_COMPANIES );
      if( *crtKey != NULL_STRING )
      {
         GetList( IDC_LST_HOLDING_COMPANIES )->SetSelection( crtKey );
      }
   }
   GetDlgItem(IDC_BTN_MORE)->EnableWindow( getParent()->doMoreRecordsExist( this, BF::AllContainerIds ) );
   GetList( IDC_LST_HOLDING_COMPANIES )->SetSelection(cursel, true, true);
   SetMessageStatusBar(NULL_STRING);   

}

void HoldingCompDlg::OnBtnSearch()
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnSearch" ) );
   bool bSearch = true;
   
   FocusOnControl(IDC_BTN_SEARCH);

   if(getParent()->workSessionHasUpdates())
   {
	   CString cstr;
	   cstr.LoadString( TXT_WARNING_LOST_CHANGE );
		if( IDNO == AfxMessageBox( TXT_WARNING_LOST_CHANGE, MB_YESNO ) )
			bSearch = false;
      else
         resetChanges();
   }
   if(bSearch)
   {
      CWaitCursor wait;
      static int cursel;
      if( getParent()->performSearch( this, BF::AllContainerIds, SEARCH_START ) <= WARNING )
      {
         LoadListControl( IDC_LST_HOLDING_COMPANIES );
         //if( *crtKey != NULL_STRING )
         //{
         //   GetList( IDC_LST_HOLDING_COMPANIES )->SetSelection( crtKey );
         //}
      }
      GetDlgItem(IDC_BTN_MORE)->EnableWindow( getParent()->doMoreRecordsExist( this, BF::AllContainerIds ) );
      //GetList( IDC_LST_HOLDING_COMPANIES )->SetSelection(cursel, true, true);
      SetMessageStatusBar(NULL_STRING);   
   }
}


//**********************************************************************************
void HoldingCompDlg::OnBtnAdmDates() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnAdminDates" ) );
   CWaitCursor wait;
   ShowAdminDates( IFASTBP_PROC::HOLDING_COMP_LIST );
}
//**********************************************************************************
void HoldingCompDlg::resetChanges() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "resetChanges" ) );
   const BFDataGroupId& dataGroupId = getParent()->getDataGroupId(); 
   DSTCWorkSession* pDSTCWorkSession = dynamic_cast<DSTCWorkSession *>(getBFWorkSession());   
   pDSTCWorkSession->reset(dataGroupId, true);
	const DString *crtKey = &getParent()->getCurrentListItemKey( this, IFASTBP_PROC::HOLDING_COMP_LIST);
   
   if (crtKey && !(*crtKey).empty())
	{
		LoadListControl(IDC_LST_HOLDING_COMPANIES);
		GetList (IDC_LST_HOLDING_COMPANIES)->SetSelection (crtKey);
	 	getParent()->setCurrentListItem (this, IFASTBP_PROC::HOLDING_COMP_LIST, *crtKey);
	}
}

//**********************************************************************************
void HoldingCompDlg::OnBtnFeeModel() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnFeeModel" ) );

   bool bSearch = true;
   if(getParent()->workSessionHasUpdates())
   {
	   CString cstr;
	   cstr.LoadString( TXT_WARNING_LOST_CHANGE );
		if( IDNO == AfxMessageBox( TXT_WARNING_LOST_CHANGE, MB_YESNO ) )
			bSearch = false;
      else
         resetChanges();
   }
   if(bSearch)
   {
      try
      {
         E_COMMANDRETURN eRtn = CMD_CANCEL;
         CWaitCursor wait;  


         DString dstrHoldingCompCode;
         DString dstrHoldingCompName;

         getParent()->getField(this, IFASTBP_PROC::HOLDING_COMP_LIST, ifds::WhereUseKey, dstrHoldingCompCode, false);
         getParent()->getField(this, IFASTBP_PROC::HOLDING_COMP_LIST, ifds::HoldingCompName, dstrHoldingCompName, false);
         setParameter (MFCAN_IP_PARAM::HOLDING_COMP_CODE, dstrHoldingCompCode);
         setParameter (MFCAN_IP_PARAM::HOLDING_COMP_NAME, dstrHoldingCompName);
               

         eRtn = invokeCommand( getParent(), CMD_BPROC_FEE_MODEL, PROC_MAINT, true, NULL );
         switch( eRtn )
         {
            case CMD_OK:
            case CMD_MODELESS_INPROCESS:
               {
               }
            case CMD_CANCEL:
               break;

            default:
               // Display error
               ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
               break;
         }
         BFWorkSession * worksession = getBFWorkSession();
         if(worksession->getHadTrxnError() || worksession->getIsEndSession())
         {
            PostMessage( WM_COMMAND, IDCANCEL );
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


//**********************************************************************************
void HoldingCompDlg::OnBtnInvoiceInstr() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnFeeModel" ) );

   bool bSearch = true;
   if(getParent()->workSessionHasUpdates())
   {
	   CString cstr;
	   cstr.LoadString( TXT_WARNING_LOST_CHANGE );
		if( IDNO == AfxMessageBox( TXT_WARNING_LOST_CHANGE, MB_YESNO ) )
			bSearch = false;
      else
         resetChanges();
   }
   if(bSearch)
   {
      try
      {
         E_COMMANDRETURN eRtn = CMD_CANCEL;
         CWaitCursor wait;  

         DString dstrParamsIDI;
         addIDITagValue (dstrParamsIDI, I_("BrowserTitle"), I_("Invoice Instruction Maintenance"));
         addIDITagValue (dstrParamsIDI, I_("screen"),       I_("InvoiceInstr"));
         addIDITagValue (dstrParamsIDI, I_("from_screen"),  I_("MainScreen"));

         DString dstrHoldingCompCode;
         getParent()->getField(this, IFASTBP_PROC::HOLDING_COMP_LIST, ifds::WhereUseKey, dstrHoldingCompCode, false);
         addIDITagValue (dstrParamsIDI, I_("HoldingEntityCode"),  dstrHoldingCompCode);

	   CString cstrInvoiceTitle;
	   cstrInvoiceTitle.LoadString(TXT_INVOICE_INSTRUCTION);
	   setParameter (I_("BrowserTitle"), DString(cstrInvoiceTitle));
      setParameter (I_("UrlParams"), dstrParamsIDI);

         eRtn = invokeCommand( getParent(), CMD_BPROC_INVOICE_INSTRUCTION, PROC_SUPPORT, true, NULL );
         switch( eRtn )
         {
            case CMD_OK:
            case CMD_MODELESS_INPROCESS:
               {
               }
            case CMD_CANCEL:
               break;

            default:
               // Display error
               ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
               break;
         }
         BFWorkSession * worksession = getBFWorkSession();
         if(worksession->getHadTrxnError() || worksession->getIsEndSession())
         {
            PostMessage( WM_COMMAND, IDCANCEL );
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

//**********************************************************************************
void HoldingCompDlg::OnBtnReportingGroup() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnFeeModel" ) );

   bool bSearch = true;
   if(getParent()->workSessionHasUpdates())
   {
	   CString cstr;
	   cstr.LoadString( TXT_WARNING_LOST_CHANGE );
		if( IDNO == AfxMessageBox( TXT_WARNING_LOST_CHANGE, MB_YESNO ) )
			bSearch = false;
      else
         resetChanges();
   }
   if(bSearch)
   {
      try
      {
         E_COMMANDRETURN eRtn = CMD_CANCEL;
         CWaitCursor wait;  

         DString dstrParamsIDI;
         addIDITagValue (dstrParamsIDI, I_("BrowserTitle"), I_("Report Group Maintenance"));
         addIDITagValue (dstrParamsIDI, I_("screen"),       I_("ReportGroup"));
         addIDITagValue (dstrParamsIDI, I_("from_screen"),  I_("HoldingCompDlg"));

         DString dstrHoldingCompCode;
         getParent()->getField(this, IFASTBP_PROC::HOLDING_COMP_LIST, ifds::WhereUseKey, dstrHoldingCompCode, false);
         addIDITagValue (dstrParamsIDI, I_("HoldingEntityCode"),  dstrHoldingCompCode);
   	  
	   CString cstrReportTitle;
	   cstrReportTitle.LoadString(TXT_REPORT_GROUP);
	   setParameter (I_("BrowserTitle"), DString(cstrReportTitle));
         setParameter (I_("UrlParams"), dstrParamsIDI);

         eRtn = invokeCommand( getParent(), CMD_BPROC_REPORT_GROUP, PROC_SUPPORT, true, NULL );
         switch( eRtn )
         {
            case CMD_OK:
            case CMD_MODELESS_INPROCESS:
               {
               }
            case CMD_CANCEL:
               break;

            default:
               // Display error
               ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
               break;
         }
         BFWorkSession * worksession = getBFWorkSession();
         if(worksession->getHadTrxnError() || worksession->getIsEndSession())
         {
            PostMessage( WM_COMMAND, IDCANCEL );
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
//**********************************************************************************
void HoldingCompDlg::OnBtnAdditionalAssets() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnFeeModel" ) );

   bool bSearch = true;
   if(getParent()->workSessionHasUpdates())
   {
	   CString cstr;
	   cstr.LoadString( TXT_WARNING_LOST_CHANGE );
		if( IDNO == AfxMessageBox( TXT_WARNING_LOST_CHANGE, MB_YESNO ) )
			bSearch = false;
      else
         resetChanges();
   }
   if(bSearch)
   {
      try
      {
         E_COMMANDRETURN eRtn = CMD_CANCEL;
         CWaitCursor wait;  

         DString dstrParamsIDI;
         addIDITagValue (dstrParamsIDI, I_("BrowserTitle"), I_("Additional Assets Maintenance"));
         addIDITagValue (dstrParamsIDI, I_("screen"),       I_("AdditionalAsset"));
         addIDITagValue (dstrParamsIDI, I_("from_screen"),  I_("HoldingCompDlg"));

         DString dstrHoldingCompCode;
         getParent()->getField(this, IFASTBP_PROC::HOLDING_COMP_LIST, ifds::WhereUseKey, dstrHoldingCompCode, false);
         addIDITagValue (dstrParamsIDI, I_("HoldingEntityCode"),  dstrHoldingCompCode);

	      CString cstrAdditionAsset;
	      cstrAdditionAsset.LoadString(TXT_ADDITIONAL_ASSETS);
	      setParameter (I_("BrowserTitle"), DString(cstrAdditionAsset));
         setParameter (I_("UrlParams"), dstrParamsIDI);

         eRtn = invokeCommand( getParent(), CMD_BPROC_ADDITIONAL_ASSETS, PROC_SUPPORT, true, NULL );
         switch( eRtn )
         {
            case CMD_OK:
            case CMD_MODELESS_INPROCESS:
               {
               }
            case CMD_CANCEL:
               break;

            default:
               // Display error
               ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
               break;
         }
         BFWorkSession * worksession = getBFWorkSession();
         if(worksession->getHadTrxnError() || worksession->getIsEndSession())
         {
            PostMessage( WM_COMMAND, IDCANCEL );
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

//**********************************************************************************
void HoldingCompDlg::OnBtnAccountList() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnFeeModel" ) );

   bool bSearch = true;
   if(getParent()->workSessionHasUpdates())
   {
	   CString cstr;
	   cstr.LoadString( TXT_WARNING_LOST_CHANGE );
		if( IDNO == AfxMessageBox( TXT_WARNING_LOST_CHANGE, MB_YESNO ) )
			bSearch = false;
      else
         resetChanges();
   }
   if(bSearch)
   {
      try
      {
         E_COMMANDRETURN eRtn = CMD_CANCEL;
         CWaitCursor wait;  

         DString dstrParamsIDI;
         addIDITagValue (dstrParamsIDI, I_("BrowserTitle"), I_("Fee Model Association"));
         addIDITagValue (dstrParamsIDI, I_("screen"),       I_("AcctAssociate"));
         addIDITagValue (dstrParamsIDI, I_("from_screen"),  I_("HoldingCompDlg"));

         DString dstrHoldingCompCode;
         getParent()->getField(this, IFASTBP_PROC::HOLDING_COMP_LIST, ifds::WhereUseKey, dstrHoldingCompCode, false);
         addIDITagValue (dstrParamsIDI, I_("HoldingEntityCode"),  dstrHoldingCompCode);

         CString cstrBrowserTitle;
         cstrBrowserTitle.LoadString(TXT_FEE_MODEL_ASSOCIATION_TITLE);
         setParameter(I_("BrowserTitle"), DString(cstrBrowserTitle));
         setParameter(I_("UrlParams"), dstrParamsIDI);

         eRtn = invokeCommand( getParent(), CMD_BPROC_ACCOUNT_ASSOCIATION, PROC_SUPPORT, true, NULL );
         switch( eRtn )
         {
            case CMD_OK:
            case CMD_MODELESS_INPROCESS:
               {
               }
            case CMD_CANCEL:
               break;

            default:
               // Display error
               ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
               break;
         }
         BFWorkSession * worksession = getBFWorkSession();
         if(worksession->getHadTrxnError() || worksession->getIsEndSession())
         {
            PostMessage( WM_COMMAND, IDCANCEL );
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




void HoldingCompDlg::OnBtnSearchAll() 
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnSearchAll" ) );
   // TODO: Add your control notification handler code here
   getParent()->setField( this, BF::NullContainerId, ifds::SearchAll, I_("Y"));
   getParent()->setField( this, BF::NullContainerId, ifds::AsofDate, I_("12319999"));
   LoadControl(IDC_DTP_SRC_EFFECTIVE);

}

void HoldingCompDlg::OnBtnSearchEffDate() 
{
   TRACE_METHOD( CLASSNAME, I_( "OnBtnSearchEffDate" ) );
   // TODO: Add your control notification handler code here
   getParent()->setField( this, BF::NullContainerId, ifds::SearchAll, I_("N"));
	DString dstrCurBusDate;
   DSTCWorkSession *dstWorkSession = dynamic_cast<DSTCWorkSession *>(getParent()->getBFWorkSession());
	dstWorkSession->getMgmtCoOptions()->getField(ifds::CurrBusDate, dstrCurBusDate, BF::HOST);
   dstrCurBusDate.strip();
   getParent()->setField( this, BF::NullContainerId, ifds::AsofDate, dstrCurBusDate );
   LoadControl(IDC_DTP_SRC_EFFECTIVE);

}

void HoldingCompDlg::OnBtnHistorical()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnHistorical" ) );

   E_COMMANDRETURN eRtn = CMD_CANCEL;

   IFastHistoricalInfo historicalInfo;
   historicalInfo( this, IFASTBP_PROC::HOLDING_COMP_LIST, I_("MULTI") );
}

bool HoldingCompDlg::canCancel()
{
//   return true;
   BFWorkSession * worksession = getBFWorkSession();
   if(!worksession->getHadTrxnError() && !worksession->getIsEndSession() && getParent()->workSessionHasUpdates())
   {
      DiscardMsgDlg discardDlg(NULL, TXT_DISCARD_MSGA, TXT_DISCARD_MSGB, TXT_DISCARD);

      return(discardDlg.DoModal() != IDCANCEL);         
   }

   return(true);
}
