//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2003 by International Financial.
//
//******************************************************************************
//
// ^FILE   : ResetInstrDlg.cpp
// ^AUTHOR : 
// ^DATE   : Jan 24, 2003
//
// ^CLASS    : ResetInstrDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

#include "stdafx.h"

#ifndef IFASTGUI_H
   #include "mfdstc.h"
#endif

#ifndef ABSTRACTPROCESS_HPP
   #include <bfproc\AbstractProcess.hpp>
#endif

#ifndef RESETINSTRDLG_H
   #include "ResetInstrDlg.h"
#endif

#ifndef DSTCOMMONFUNCTION_HPP
   #include <ifastcbo\DSTCommonFunction.hpp>
#endif

#ifndef DSTCLISTCTRL_H
   #include <uibase\DSTListCtrl.h>
#endif

#ifndef DSTCWORKSESSION_HPP
   #include <ifastcbo\DSTCWorkSession.hpp>
#endif

#ifndef DSTCOMBOBOX_H
   #include <uibase\DSTComboBox.h>
#endif

#ifndef DSTEDIT_H
   #include <uibase\DSTEdit.h>
#endif

#include <ifastbp\mfcaninterprocparam.hpp>
#include <ifastbp\resetinstrprocessincludes.h>
#include <ifastbp\fundclassprocessincludes.h>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_RESET_INSTR;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_IDENT_ACC;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_FUNDCLASS;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< ResetInstrDlg > dlgCreator( CMD_GUI_RESET_INSTR );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME               = I_( "ResetInstrDlg" );
   const I_CHAR * const LV_RESET_LIST           = I_( "ResetInstrList" );            
   const I_CHAR * const YES                     = I_( "Y" );
   const I_CHAR * const NO                      = I_( "N" );         
   const I_CHAR * const ALL                     = I_( "All" );
   const UINT SEARCH_SET = 1;   
}

namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const PROTECTED_FUND_RESET_INSTR;
}

namespace ifds
{
   extern CLASS_IMPORT const BFNumericFieldId ShrNum;
}

//******************************************************************************
// Constructor
//******************************************************************************
ResetInstrDlg::ResetInstrDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( ResetInstrDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );   
   //{{AFX_DATA_INIT( ResetInstrDlg )
   //}}AFX_DATA_INIT
   
}

//******************************************************************************
// Destructor
//******************************************************************************
ResetInstrDlg::~ResetInstrDlg ()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
// Called by MFC framework to exchange and validate dialog data
//******************************************************************************
void ResetInstrDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange( pDX );
   //{{AFX_DATA_MAP( ResetInstrDlg ) 
   //}}AFX_DATA_MAP
}

//******************************************************************************
// MFC Message Map
//******************************************************************************

BEGIN_MESSAGE_MAP( ResetInstrDlg, BaseMainDlg )
//{{AFX_MSG_MAP( ResetInstrDlg )
ON_BN_CLICKED( IDC_BTN_MORE, OnBtnMore )
ON_BN_CLICKED( IDC_BTN_HISTORICAL, OnBtnHistorical )
ON_BN_CLICKED( IDC_BTN_SEARCH, OnBtnSearch )
ON_BN_CLICKED( IDC_BTN_ADD, OnBtnAdd )
ON_BN_CLICKED( IDC_BTN_DELETE, OnBtnDelete )
ON_BN_CLICKED( IDC_BTN_RESET, OnBtnReset )
ON_BN_CLICKED( IDC_BTN_REVERSE , OnBtnReverse )
ON_MESSAGE( WM_LAUNCH_IDENT_ACC,OpenIdentifyAccountsDlg )
ON_MESSAGE( UM_OPENFUNDCLASSLISTDLG, OpenFundClassListDlg )
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//******************************************************************************
// Initialization of Dialog, get InterProcess Global data and sets up the 
// caption in the title bar.
//******************************************************************************
BOOL ResetInstrDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );
   BaseMainDlg::OnInitDialog();

   if( !_dstrParent.empty() ) // RESET_INSTR::CONTRACT_DETAIL
   {
      DString dstrShrNum, dstrAccountNum, dstrEntityName;
      getParent()->getField(this, IFASTBP_PROC::MFACCOUNT, ifds::ShrNum, dstrShrNum);
      getParent()->getField( this, IFASTBP_PROC::MFACCOUNT, ifds::AccountNum, dstrAccountNum );  
      SetAccount( dstrAccountNum );   
      dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName( getDataGroupId(),dstrAccountNum,dstrEntityName );
      SetShrAcctCaption(dstrShrNum, dstrAccountNum, dstrEntityName);
   }
   return(TRUE);  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

//******************************************************************************
// Call by based architecture.  Controls are initialized here by calling the
// addControls() method.  The More button is enable/disable based on the CBO
// data.
//******************************************************************************
void ResetInstrDlg::OnPostInitDialog()
{
   CWaitCursor wait;
   TRACE_METHOD( CLASSNAME, I_( "OnPostInitDialog" ) );
   addControls( );        
   GetDlgItem( IDC_BTN_MORE )->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::RESET_INSTR_CRITERIA ) );
   SetUserAccesFunctionCode(UAF::PROTECTED_FUND_RESET_INSTR);
   addBtnAddForPermissionCheck(IDC_BTN_ADD, IDC_LV_RESET);
   addBtnAddForPermissionCheck(IDC_BTN_REVERSE, IDC_LV_RESET);
   addBtnDeleteForPermissionCheck(IDC_BTN_DELETE, IDC_LV_RESET);

   // Disable historical button if list empty
   GetDlgItem( IDC_BTN_HISTORICAL )->EnableWindow( getParent()->getNumberOfItemsInList(this,IFASTBP_PROC::RESET_INSTR_LIST) > 0  );
}

//******************************************************************************
// doInit method is not used.
//******************************************************************************
SEVERITY ResetInstrDlg::doInit()
{
   getParameter( RESET_INSTR::PARENT, _dstrParent );
   return ( NO_CONDITION );
}

//******************************************************************************
// This method sets up the custom controls to the correct data set.
//******************************************************************************
void ResetInstrDlg::addControls( )
{
   AddControl( CTRL_COMBO, IDC_CMB_USING, IFASTBP_PROC::RESET_INSTR_CRITERIA, ifds::ResetInstrUsing, CTRLFLAG_INITCOMBO_BY_SUB_LIST, SEARCH_SET );   
   AddControl( CTRL_EDIT, IDC_EDT_VALUE, BF::NullContainerId, ifds::NullFieldId, CTRLFLAG_DEFAULT, 0  );
   AddControl( CTRL_DATE, IDC_DTP_VALUE, BF::NullContainerId, ifds::NullFieldId, CTRLFLAG_DEFAULT, 0  );
   AddListControl( CLASSNAME, IDC_LV_RESET, LV_RESET_LIST, ifds::ResetInstrHeadingSet, IFASTBP_PROC::RESET_INSTR_LIST, 0, true );   
   AddControl( CTRL_EDIT, IDC_EDT_ACCOUNT, IFASTBP_PROC::RESET_INSTR_LIST, ifds::AccountNum, CTRLFLAG_DEFAULT, IDC_LV_RESET );
   AddControl( CTRL_EDIT, IDC_EDT_FUNDNUMBER, IFASTBP_PROC::RESET_INSTR_LIST, ifds::FundNumber, CTRLFLAG_DEFAULT, IDC_LV_RESET );
   AddControl( CTRL_EDIT, IDC_EDT_FUND_CODE, IFASTBP_PROC::RESET_INSTR_LIST, ifds::FundCode, CTRLFLAG_DEFAULT, IDC_LV_RESET );
   AddControl( CTRL_EDIT, IDC_EDT_CLASS_CODE, IFASTBP_PROC::RESET_INSTR_LIST, ifds::ClassCode, CTRLFLAG_DEFAULT, IDC_LV_RESET );
   AddControl( CTRL_STATIC, IDC_TXT_FUND_NAME, IFASTBP_PROC::RESET_INSTR_LIST, RESET_INSTR::FUNDDESC, CTRLFLAG_DEFAULT, IDC_LV_RESET );
   AddControl( CTRL_COMBO, IDC_CMB_INSTRUCT, IFASTBP_PROC::RESET_INSTR_LIST, ifds::ResetType, CTRLFLAG_INITCOMBO_BY_SUB_LIST, IDC_LV_RESET );
   AddControl( CTRL_DATE, IDC_DTP_EFF_DATE, IFASTBP_PROC::RESET_INSTR_LIST, ifds::ResetDate, CTRLFLAG_DEFAULT, IDC_LV_RESET );
   AddControl( CTRL_STATIC, IDC_TXT_COMPLETE_DATE, IFASTBP_PROC::RESET_INSTR_LIST, ifds::CompleteDate, CTRLFLAG_DEFAULT, IDC_LV_RESET );
   AddControl( CTRL_STATIC, IDC_TXT_BATCH_NAME, IFASTBP_PROC::RESET_INSTR_LIST, ifds::BatchName, CTRLFLAG_DEFAULT, IDC_LV_RESET );
   AddControl( CTRL_STATIC, IDC_TXT_BATCH_DATE, IFASTBP_PROC::RESET_INSTR_LIST, ifds::BatchEffective, CTRLFLAG_DEFAULT, IDC_LV_RESET );
   AddControl( CTRL_STATIC, IDC_TXT_TRACE, IFASTBP_PROC::RESET_INSTR_LIST, ifds::Trace, CTRLFLAG_DEFAULT, IDC_LV_RESET );
//   AddControl( CTRL_STATIC, IDC_TXT_CANRESETID, RESET_INSTR::RESET_INSTR_LIST, ifds::CanResetId, CTRLFLAG_DEFAULT, IDC_LV_RESET );
   LoadListControl ( IDC_LV_RESET );  
   _lastCriteriaValueControl = IDC_EDT_VALUE;
   showCriteriaValue ( IDC_EDT_VALUE );
   ConnectControlsToData (SEARCH_SET);  
   LoadControls(SEARCH_SET);
}

//******************************************************************************
void ResetInstrDlg::DoListItemChanged(UINT listControlID,
   const DString &strKey, bool bIsNewItem, bool bIsDummyItem)
{
   // Keep historical button grayed for new and dummy items
   GetDlgItem( IDC_BTN_HISTORICAL )->EnableWindow( !bIsNewItem && !bIsDummyItem );
}

//******************************************************************************
// Method to refresh dialog controls
// @param   GenericInterface *rpGICaller - pointer to the calling object
// @param   const I_CHAR *szOriginalCommand - Not used in this case, but 
//                      can be used to instruct special processing.
//******************************************************************************
bool ResetInstrDlg::doRefresh( GenericInterface * rpGICaller, 
                                  const I_CHAR * szOriginalCommand )
{
   if( !_dstrParent.empty() ) // RESET_INSTR::CONTRACT_DETAIL
   {
      DString dstrShrNum, dstrAccountNum, dstrEntityName;
      getParent()->getField(this, IFASTBP_PROC::MFACCOUNT, ifds::ShrNum, dstrShrNum);
      getParent()->getField( this, IFASTBP_PROC::MFACCOUNT, ifds::AccountNum, dstrAccountNum );  
      SetAccount( dstrAccountNum );   
      dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName( getDataGroupId(),dstrAccountNum,dstrEntityName );
      SetShrAcctCaption(dstrShrNum, dstrAccountNum, dstrEntityName);
   }

//   LoadListControl ( IDC_LV_CONTRACTS );
   return(true);
}

//******************************************************************************
//******************************************************************************
void ResetInstrDlg::OnBtnMore  ( )
{
   TRACE_METHOD( CLASSNAME, ONBTNMORE );

   CWaitCursor wait; 
//   SetMessageStatusBar( TXT_LOAD_CONTRACTS );

   static int cursel;

   cursel = GetList( IDC_LV_CONTRACTS )->GetNextItem( -1, LVIS_SELECTED | LVNI_FOCUSED );

   const DString *crtKey = &getParent()->getCurrentListItemKey( this, IFASTBP_PROC::RESET_INSTR_LIST );

   if( getParent()->performSearch( this, IFASTBP_PROC::RESET_INSTR_CRITERIA, SEARCH_NEXT_BLOCK ) <= WARNING )
   {
      LoadListControl( IDC_LV_CONTRACTS );
      if( *crtKey != NULL_STRING )
      {
         GetList( IDC_LV_CONTRACTS )->SetSelection( crtKey );
      }
   }
   GetDlgItem( IDC_BTN_MORE )->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::RESET_INSTR_CRITERIA ) );
   GetList( IDC_LV_CONTRACTS )->SetSelection(cursel, true, true);
   SetMessageStatusBar(NULL_STRING);
}

//******************************************************************************

void ResetInstrDlg::OnBtnHistorical() 
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnHistorical") );
   CWaitCursor wait;   
   IFastHistoricalInfo f;
   f( this, IFASTBP_PROC::RESET_INSTR_LIST );
}

//******************************************************************************

BOOL ResetInstrDlg::PreTranslateMessage(MSG* pMsg) 
{
   if( pMsg->message == WM_KEYDOWN && ( int )( pMsg->wParam ) == VK_F4 && !IsSelectedCtrlUpdateable() )
      return(TRUE);

   if( pMsg->message == WM_KEYDOWN && ( int )( pMsg->wParam ) == VK_F4 )
   {
      if( GetFocus()== GetDlgItem( IDC_EDT_VALUE) ) {
         iCurrentAccountId = IDC_EDT_VALUE;
         DString dstrResetInstrUsing;         
         getParent()->getField ( this, IFASTBP_PROC::RESET_INSTR_CRITERIA, ifds::ResetInstrUsing, dstrResetInstrUsing, false );
         const BFFieldId& fieldId = BFFieldId::getId( dstrResetInstrUsing );
         if ( fieldId == ifds::AccountNum ) {
            PostMessage ( WM_LAUNCH_IDENT_ACC );
         }

      } else if( GetFocus()== GetDlgItem( IDC_EDT_ACCOUNT) ) {
         iCurrentAccountId = IDC_EDT_ACCOUNT;
         PostMessage( WM_LAUNCH_IDENT_ACC );
      } else if( GetFocus() == GetDlgItem( IDC_EDT_FUNDNUMBER ) ) {
         iCurrentAccountId = IDC_EDT_FUNDNUMBER;
         PostMessage( UM_OPENFUNDCLASSLISTDLG );               
      } else if( GetFocus() == GetDlgItem( IDC_EDT_FUND_CODE ) ) {
         iCurrentAccountId = IDC_EDT_FUND_CODE;
         PostMessage( UM_OPENFUNDCLASSLISTDLG );               
      } else if( GetFocus() == GetDlgItem( IDC_EDT_CLASS_CODE ) ) {
         iCurrentAccountId = IDC_EDT_CLASS_CODE;
         PostMessage( UM_OPENFUNDCLASSLISTDLG );               
      }
   }

   return(BaseMainDlg::PreTranslateMessage( pMsg ));
}

//******************************************************************************
//******************************************************************************

LRESULT ResetInstrDlg::OpenIdentifyAccountsDlg( WPARAM,LPARAM )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION,CLASSNAME,I_( "OpenIdentifyAccountsDlg" ) );

   E_COMMANDRETURN eRtn = CMD_CANCEL;
   //don't allow user to open identify account unless they cleared the account number
   CString strAccNum;
  
   CEdit* pEdit = static_cast<CEdit*>(GetDlgItem(iCurrentAccountId));
   pEdit->GetWindowText(strAccNum);

   DString dstAcctNum = NULL_STRING;
   dstAcctNum = (LPCTSTR) strAccNum;
   dstAcctNum.strip().stripLeading('0');
   if( dstAcctNum != NULL_STRING )
      return(0);

   bool bRetVal = false;
   BaseControl *pBC = NULL;
   try
   {
      eRtn = invokeCommand( getParent(), CMD_BPROC_IDENT_ACC, PROC_SUPPORT, true, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               DString dstrAccountNum = NULL_STRING;
               getParameter( MFCAN_IP_PARAM::ACCOUNT_NUM, dstrAccountNum );
               dstAcctNum.strip();
               bRetVal = SetControlText( iCurrentAccountId, dstrAccountNum );
               pBC = dynamic_cast< BaseControl *> (GetDlgItem( iCurrentAccountId ));
               if( pBC && pBC->IsToolTipVisible() )
                  pBC->ToggleToolTip();

               if( !bRetVal )
               {

                  BaseControl * pBC = dynamic_cast< BaseControl *> (GetDlgItem( iCurrentAccountId ));
                  if( pBC )
                  {
                     if( pBC->IsToolTipVisible() )
                        pBC->ToggleToolTip();

                     pBC->Load();
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

//****************************************************************************** 

void ResetInstrDlg::ControlUpdated(UINT controlID, const DString &dstrValue)
{
   switch( controlID )
   {
      case IDC_CMB_USING:
         {
            ClearControl ( _lastCriteriaValueControl );
            ConnectControlToData ( _lastCriteriaValueControl, false );
            setupCriteriaValueControl( dstrValue );
         }
         break;
      case IDC_EDT_FUND_CODE:
         {
            LoadControl ( IDC_EDT_FUNDNUMBER );
            LoadControl ( IDC_TXT_FUND_NAME );
         }
         break;
      case IDC_EDT_CLASS_CODE:
         {
            LoadControl ( IDC_EDT_FUNDNUMBER );
            LoadControl ( IDC_TXT_FUND_NAME );
         }
         break;
      case IDC_EDT_FUNDNUMBER:
         {
            LoadControl ( IDC_EDT_FUND_CODE );
            LoadControl ( IDC_EDT_CLASS_CODE );
            LoadControl ( IDC_TXT_FUND_NAME );
         }
         break;
      case IDC_EDT_ACCOUNT:
         {
            LoadControl ( IDC_EDT_FUND_CODE );
            LoadControl ( IDC_EDT_CLASS_CODE );
            LoadControl ( IDC_TXT_FUND_NAME );
         }
         break;
   }
}

//****************************************************************************** 

void ResetInstrDlg::setupCriteriaValueControl( const DString &dstrValue )
{
   DString dstrCriteriaType;
   if ( dstrValue == NULL_STRING ) {
      showCriteriaValue ( IDC_EDT_VALUE );
      EnableControl ( IDC_EDT_VALUE, false );
      return;
   }
   const BFFieldId& fieldId = BFFieldId::getId( dstrValue );
   const BFDataFieldProperties* pProps = BFDataFieldProperties::get ( fieldId );   
   switch ( pProps->getType() ) {
      case BFDataFieldProperties::Type::date :
         {
            // load dtp
            loadCriteriaValue ( IDC_DTP_VALUE );
         }
         break;
//      case BFDataFieldProperties::Type::bigdecimal :
      case BFDataFieldProperties::Type::integer :         
      case BFDataFieldProperties::Type::numeric :
         {
            // load edit control with input of 0-9
            EnableControl ( IDC_EDT_VALUE, true );
            loadCriteriaValue ( IDC_EDT_VALUE );
            dynamic_cast<DSTEdit *>( GetControl( IDC_EDT_VALUE ) )->SetAllowedChars( I_("0123456789") );
         }
         break;
   }   
}

//****************************************************************************** 

void ResetInstrDlg::loadCriteriaValue ( UINT controlID )
{
   showCriteriaValue ( controlID );
   DString dstrResetInstrUsing;
   getParent()->getField(this, IFASTBP_PROC::RESET_INSTR_CRITERIA, ifds::ResetInstrUsing, dstrResetInstrUsing, false);   
   const BFFieldId& fieldId = BFFieldId::getId( dstrResetInstrUsing );         
   ReInitControl ( controlID, IFASTBP_PROC::RESET_INSTR_CRITERIA, fieldId );   
   ConnectControlToData ( controlID, true );   
   LoadControl ( controlID );
   _lastCriteriaValueControl = controlID;
}

//****************************************************************************** 

void ResetInstrDlg::showCriteriaValue ( UINT controlID )
{
   GetDlgItem ( IDC_EDT_VALUE )->ShowWindow( controlID == IDC_EDT_VALUE ? SW_SHOW : SW_HIDE );   
   GetDlgItem ( IDC_DTP_VALUE )->ShowWindow( controlID == IDC_DTP_VALUE ? SW_SHOW : SW_HIDE );      
}

//****************************************************************************** 

void ResetInstrDlg::OnBtnSearch ( )
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnSearch") );

	bool bSearch = true;
	DString dtrUpdated;
	getParent()->getField( this, BF::NullContainerId, RESET_INSTR::updated, dtrUpdated, false );
	if(dtrUpdated.strip() == YES )
	{
		if( AfxMessageBox(TXT_WARNING_LOST_CHANGE,MB_YESNO ) == IDNO )
		{
			bSearch = false;
		}
	}
	if( bSearch )
	{		

      CWaitCursor wait;
      SetMessageStatusBar( TXT_LOAD_RESET_INSTR );  
      getParent()->performSearch( this, IFASTBP_PROC::RESET_INSTR_LIST, SEARCH_START );
      LoadListControl ( IDC_LV_RESET );
      GetDlgItem( IDC_BTN_MORE )->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::RESET_INSTR_LIST ) );   

      SetMessageStatusBar(NULL_STRING);  
   }
}

//****************************************************************************** 

void ResetInstrDlg::OnBtnAdd ( )
{
   AddToListControl ( IDC_LV_RESET );
}

//****************************************************************************** 

void ResetInstrDlg::OnBtnDelete ( )
{
   DeleteFromListControl ( IDC_LV_RESET );
}

//****************************************************************************** 

void ResetInstrDlg::OnBtnReset ( )
{
   ResetListItem ( IDC_LV_RESET );
}

//****************************************************************************** 

LRESULT ResetInstrDlg::OpenFundClassListDlg( WPARAM, LPARAM )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OpenFundClassListDlg" ) );

   DString strMarket = DSTCommonFunctions::getMarket();
   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;
      CWaitCursor wait;      
      CString cstr;
      GetDlgItem( iCurrentAccountId )->GetWindowText( cstr );
		DString dstr = cstr;
      // Set Search Parameters (Code, Class, Number) for Fund Class Dialog
      switch( iCurrentAccountId )
      {
         case IDC_EDT_FUND_NUMBER:
				setParameter( FUNDCLASSLIST::FUND_NUMBER, dstr );
				break;
         case IDC_EDT_FUND_CODE:
				setParameter( FUNDCLASSLIST::FUND_CODE, dstr );
				break;
			case IDC_EDT_CLASS_CODE:
				setParameter( FUNDCLASSLIST::CLASS_CODE, dstr );
            break;    
      }


      DString dstrAccountNum;
      getParent()->getField( this, IFASTBP_PROC::MFACCOUNT, ifds::AccountNum, dstrAccountNum );  
      setParameter( FUNDCLASSLIST::ACCT_NUM, dstrAccountNum );


      eRtn = invokeCommand( getParent(), CMD_BPROC_FUNDCLASS, PROC_SUPPORT, true, NULL );
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               DString dstrFundCode,dstrClassCode,dstrFundNumber;
               getParameter ( FUNDCLASSLIST::FUND_CODE, dstrFundCode );
               getParameter ( FUNDCLASSLIST::CLASS_CODE, dstrClassCode );

					if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
               {
                  getParameter ( PARM_FUND_NUMBER, dstrFundNumber );
               }
					
					getParent()->setField( this, IFASTBP_PROC::RESET_INSTR_LIST, 
								ifds::FundCode, dstrFundCode );
					getParent()->setField( this, IFASTBP_PROC::RESET_INSTR_LIST, 
								ifds::ClassCode, dstrClassCode );											
					
               if( strMarket == MARKET_IDS::CANADA || strMarket == MARKET_IDS::LUXEMBOURG )
               {
                  LoadControl ( IDC_EDT_FUNDNUMBER );
               }
					LoadControl ( IDC_EDT_FUND_CODE );
					LoadControl ( IDC_EDT_CLASS_CODE );
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

bool ResetInstrDlg::doDisablePermCheckButton(UINT nID)
{
   if( nID == IDC_BTN_REVERSE )
   {
      DString dstrCompleteDate, dstrCanResetId;      
      if ( getParent()->getNumberOfItemsInList(this,IFASTBP_PROC::RESET_INSTR_LIST) > 0 ) {
         getParent()->getField( this, IFASTBP_PROC::RESET_INSTR_LIST, ifds::CompleteDate, dstrCompleteDate, false );
         getParent()->getField( this, IFASTBP_PROC::RESET_INSTR_LIST, ifds::CanResetId, dstrCanResetId, false );
         if (( dstrCompleteDate == NULL_STRING ) || ( dstrCanResetId != I_("0") ))
            return true;
         else 
            return false;
      } else {
         return true;
      }
   }
   else if( nID == IDC_BTN_DELETE )
   {
      if ( getParent()->getNumberOfItemsInList(this,IFASTBP_PROC::RESET_INSTR_LIST) > 0 ) {
         DString dstrCompleteDate;
         getParent()->getField( this, IFASTBP_PROC::RESET_INSTR_LIST, ifds::CompleteDate, dstrCompleteDate, false );         
         return( dstrCompleteDate != NULL_STRING );
      } else {
         return true;
      }
   }
   return(false);
}

void ResetInstrDlg::OnBtnReverse()
{       
   CWaitCursor wait;      
   DString curKey = GetList(IDC_LV_RESET)->GetCurrentKey();
   //const DString *curKey = &getParent()->getCurrentListItemKey( this, RESET_INSTR::RESET_INSTR_LIST );      
   AddToListControl( IDC_LV_RESET );
   DString desKey = GetList(IDC_LV_RESET)->GetCurrentKey();
   //const DString *desKey = &getParent()->getCurrentListItemKey( this, RESET_INSTR::RESET_INSTR_LIST );      
   getParent()->setField(this, IFASTBP_PROC::RESET_INSTR_LIST, RESET_INSTR::ORIKEY, curKey);
   getParent()->setField(this, IFASTBP_PROC::RESET_INSTR_LIST, RESET_INSTR::DESTKEY, desKey);          
   RefreshListItem( IDC_LV_RESET );
   LoadListControl( IDC_LV_RESET, const_cast<DString*>(&desKey) );   
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/ResetInstrDlg.cpp-arc  $
// 
//    Rev 1.13   14 May 2010 18:01:52   smithdav
// Add BFBigDecimal field type as an improvement to the double backed BFDecimal.
// 
//    Rev 1.12   Sep 15 2005 15:14:54   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.11   Jun 14 2004 10:28:38   YINGBAOL
// PTS10031301:pass account number to fund class dialog 
// 
//    Rev 1.10   Jul 08 2003 15:05:58   HERNANDO
// PTS 10019155 - Added Caption display for doRefresh.
// 
//    Rev 1.9   Jul 08 2003 15:01:54   HERNANDO
// PTS 10019155.
// 
//    Rev 1.8   May 29 2003 09:25:18   sanchez
// Override DoListItemChanged() to diable Historical button for new and dummy records. PTS 10016740
// 
//    Rev 1.7   Mar 21 2003 18:40:04   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.6   Mar 05 2003 11:30:00   PURDYECH
// Use IFastHistoricalInfo instead of deriving from IFastBaseMainDlg
// 
//    Rev 1.5   Jan 29 2003 16:26:04   HSUCHIN
// added support for historical
// 
//    Rev 1.4   Jan 27 2003 10:09:08   HSUCHIN
// uncommented code for testing purpose
// 
//    Rev 1.3   Jan 27 2003 08:51:54   HSUCHIN
// bug fix for removal of control
// 
//    Rev 1.2   Jan 27 2003 07:44:14   HSUCHIN
// added support for reversal
// 
//    Rev 1.1   Jan 26 2003 16:05:22   HSUCHIN
// added more functionality
// 
//    Rev 1.0   Jan 24 2003 16:11:14   HSUCHIN
// Initial Revision
 */


