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
// ^FILE   : AccountContractDlg.cpp
// ^AUTHOR : 
// ^DATE   : Jan 17, 2003
//
// ^CLASS    : AccountContractDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

#include "stdafx.h"

#include "mfdstc.h"
#include <bfproc\AbstractProcess.hpp>
#include "AccountContractDlg.h"
#include <ifastcbo\DSTCommonFunction.hpp>
#include <uibase\DSTListCtrl.h>
#include <ifastcbo\DSTCWorkSession.hpp>
#include <uibase\DSTComboBox.h>

#include <ifastbp\accountcontractprocessincludes.h>
#include <ifastbp\resetinstrprocessincludes.h>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_ACCOUNT_CONTRACT;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_RESET_INSTR;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< AccountContractDlg > dlgCreator( CMD_GUI_ACCOUNT_CONTRACT );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME               = I_( "AccountContractDlg" );
   const I_CHAR * const LV_CONTRACT_LIST        = I_( "AccountContractList" );         
   const I_CHAR * const YES                     = I_( "Y" );
   const I_CHAR * const NO                      = I_( "N" );         
   const I_CHAR * const ALL                     = I_( "All" );
}


namespace CND
{  // Conditions used
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

namespace UAF
{
   extern CLASS_IMPORT I_CHAR * const PROTECTED_FUND_RESET_INSTR;
}
//******************************************************************************
// Constructor
//******************************************************************************
AccountContractDlg::AccountContractDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
:BaseMainDlg( AccountContractDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );   
   //{{AFX_DATA_INIT( AccountContractDlg )
   //}}AFX_DATA_INIT
   
}

//******************************************************************************
// Destructor
//******************************************************************************
AccountContractDlg::~AccountContractDlg ()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
// Called by MFC framework to exchange and validate dialog data
//******************************************************************************
void AccountContractDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange( pDX );
   //{{AFX_DATA_MAP( AccountContractDlg ) 
   //}}AFX_DATA_MAP
}

//******************************************************************************
// MFC Message Map
//******************************************************************************

BEGIN_MESSAGE_MAP( AccountContractDlg, BaseMainDlg )
//{{AFX_MSG_MAP( AccountContractDlg )
ON_BN_CLICKED( IDC_BTN_MORE, OnBtnMore )
ON_BN_CLICKED( IDC_BTN_CONTRACT_RESET, OnBtnContractReset )
ON_BN_CLICKED( IDC_BTN_HISTORICAL, OnBtnHistorical )
ON_CBN_SELCHANGE (IDC_CMB_FUND, OnSelchangeCmbFund)
ON_BN_CLICKED( IDC_BTN_ADM_DATES, OnBtnAdminDates )
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//******************************************************************************
// Initialization of Dialog, get InterProcess Global data and sets up the 
// caption in the title bar.
//******************************************************************************
BOOL AccountContractDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );
   BaseMainDlg::OnInitDialog();
   
   DString dstrShrNum, dstrAccountNum, dstrEntityName;
   getParent()->getField(this, IFASTBP_PROC::MFACCOUNT, ifds::ShrNum, dstrShrNum);      
   getParent()->getField( this, IFASTBP_PROC::MFACCOUNT, ifds::AccountNum, dstrAccountNum );  
   SetAccount( dstrAccountNum );   
   dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName( getDataGroupId(),dstrAccountNum,dstrEntityName );
   SetShrAcctCaption(dstrShrNum, dstrAccountNum, dstrEntityName);

   return(TRUE);  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

//******************************************************************************
// Call by based architecture.  Controls are initialized here by calling the
// addControls() method.  The More button is enable/disable based on the CBO
// data.
//******************************************************************************
void AccountContractDlg::OnPostInitDialog()
{
   CWaitCursor wait;
   TRACE_METHOD( CLASSNAME, I_( "OnPostInitDialog" ) );
   addControls( );
   fillFundCombo();
   GetDlgItem( IDC_BTN_MORE )->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::ACCOUNT_CONTRACT_LIST ) );
   bool bResetInstr = hasReadPermission ( UAF::PROTECTED_FUND_RESET_INSTR );
   GetDlgItem( IDC_BTN_CONTRACT_RESET )->EnableWindow ( bResetInstr );
}

//******************************************************************************
// doInit method is not used.
//******************************************************************************
SEVERITY AccountContractDlg::doInit()
{
   return ( NO_CONDITION );
}

//******************************************************************************
// This method sets up the custom controls to the correct data set.
//******************************************************************************
void AccountContractDlg::addControls( )
{
   AddListControl( CLASSNAME, IDC_LV_CONTRACTS, LV_CONTRACT_LIST, ifds::ContractHeadingSet, 
                   IFASTBP_PROC::ACCOUNT_CONTRACT_LIST, 0, true, LISTFLAG_NOT_AUTO_ADD );   
   DString dstrMarket = DSTCommonFunctions::getMarket();
   if ( dstrMarket == MARKET_IDS::CANADA ) {
      AddControl( CTRL_STATIC, IDC_TXT_FUND_NBR, IFASTBP_PROC::ACCOUNT_CONTRACT_LIST, ifds::FundNumber, CTRLFLAG_DEFAULT, IDC_LV_CONTRACTS );
   }
   AddControl( CTRL_STATIC, IDC_TXT_FUND_CODE, IFASTBP_PROC::ACCOUNT_CONTRACT_LIST, ifds::FundCode, CTRLFLAG_DEFAULT, IDC_LV_CONTRACTS );
   AddControl( CTRL_STATIC, IDC_TXT_CLASS, IFASTBP_PROC::ACCOUNT_CONTRACT_LIST, ifds::ClassCode, CTRLFLAG_DEFAULT, IDC_LV_CONTRACTS );
   AddControl( CTRL_STATIC, IDC_TXT_CUR_FUND_DESC, IFASTBP_PROC::ACCOUNT_CONTRACT_LIST, ACC_CONTRACT::FUNDDESC, CTRLFLAG_DEFAULT, IDC_LV_CONTRACTS );
   AddControl( CTRL_STATIC, IDC_TXT_START_DATE, IFASTBP_PROC::ACCOUNT_CONTRACT_LIST, ifds::EffectiveDate, CTRLFLAG_DEFAULT, IDC_LV_CONTRACTS );
   AddControl( CTRL_STATIC, IDC_TXT_END_DATE, IFASTBP_PROC::ACCOUNT_CONTRACT_LIST, ifds::MaturityDate, CTRLFLAG_DEFAULT, IDC_LV_CONTRACTS );
   AddControl( CTRL_STATIC, IDC_TXT_GUAR_UNIT, IFASTBP_PROC::ACCOUNT_CONTRACT_LIST, ifds::GuarUnits, CTRLFLAG_DEFAULT, IDC_LV_CONTRACTS );
   AddControl( CTRL_STATIC, IDC_TXT_GUAR_AMT, IFASTBP_PROC::ACCOUNT_CONTRACT_LIST, ifds::GuarAmt, CTRLFLAG_DEFAULT, IDC_LV_CONTRACTS );
   AddControl( CTRL_STATIC, IDC_TXT_INC_DEC, IFASTBP_PROC::ACCOUNT_CONTRACT_LIST, ifds::GainOrLossAmt, CTRLFLAG_DEFAULT, IDC_LV_CONTRACTS );
   AddControl( CTRL_STATIC, IDC_TXT_CUR_MKTV, IFASTBP_PROC::ACCOUNT_CONTRACT_LIST, ifds::MktValue, CTRLFLAG_DEFAULT, IDC_LV_CONTRACTS );
   LoadListControl ( IDC_LV_CONTRACTS );  
   ConnectControlsToData ();  
   LoadControls();      
}

//******************************************************************************
// Method to refresh dialog controls
// @param   GenericInterface *rpGICaller - pointer to the calling object
// @param   const I_CHAR *szOriginalCommand - Not used in this case, but 
//                      can be used to instruct special processing.
//******************************************************************************
bool AccountContractDlg::doRefresh( GenericInterface * rpGICaller, 
                                  const I_CHAR * szOriginalCommand )
{
   DString dstrShrNum, dstrAccountNum, dstrEntityName;
   getParent()->getField(this, IFASTBP_PROC::MFACCOUNT, ifds::ShrNum, dstrShrNum);      
   getParent()->getField( this, IFASTBP_PROC::MFACCOUNT, ifds::AccountNum, dstrAccountNum );  
   SetAccount( dstrAccountNum );   
   dynamic_cast<DSTCWorkSession *>(getBFWorkSession())->getFirstSequenced01AccountholderEntityName( getDataGroupId(),dstrAccountNum,dstrEntityName );
   SetShrAcctCaption(dstrShrNum, dstrAccountNum, dstrEntityName);
   LoadListControl ( IDC_LV_CONTRACTS );
   return(true);
}

//******************************************************************************
//******************************************************************************
void AccountContractDlg::OnBtnMore  ( )
{
   TRACE_METHOD( CLASSNAME, ONBTNMORE );

   CWaitCursor wait; 
//   SetMessageStatusBar( TXT_LOAD_CONTRACTS );

   static int cursel;

   cursel = GetList( IDC_LV_CONTRACTS )->GetNextItem( -1, LVIS_SELECTED | LVNI_FOCUSED );

   const DString *crtKey = &getParent()->getCurrentListItemKey( this, IFASTBP_PROC::ACCOUNT_CONTRACT_LIST );

   if( getParent()->performSearch( this, IFASTBP_PROC::ACCOUNT_CONTRACT_LIST, SEARCH_NEXT_BLOCK ) <= WARNING )
   {
      LoadListControl( IDC_LV_CONTRACTS );
      if( *crtKey != NULL_STRING )
      {
         GetList( IDC_LV_CONTRACTS )->SetSelection( crtKey );
      }
   }
   GetDlgItem( IDC_BTN_MORE )->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::ACCOUNT_CONTRACT_LIST ) );
   GetList( IDC_LV_CONTRACTS )->SetSelection(cursel, true, true);
   SetMessageStatusBar(NULL_STRING);
}

//******************************************************************************
//******************************************************************************
void AccountContractDlg::OnSelchangeCmbFund() 
{
   TRACE_METHOD( CLASSNAME, I_("OnSelchangeCmbRespBen") );

   CWaitCursor wait;
//   SetMessageStatusBar( TXT_LOAD_CONTRACTS );  
   DString* dstrFundClass, dstr;
   CComboBox* cb =static_cast<CComboBox* >(GetDlgItem( IDC_CMB_FUND ) );
   dstrFundClass = (DString*)cb->GetItemData ( cb->GetCurSel() );
   //Copy the key to pass in to getfield which is then replaced by the fund description.
   if ( dstrFundClass ) {
      dstr = *dstrFundClass;
   } else {
      dstr = NULL_STRING;
   }
   // need to set the key first before overriding dstr.
   setParameter( ACC_CONTRACT::FUNDCLASS, dstr );
   getParent()->getField(this, IFASTBP_PROC::ACCOUNT_CONTRACT_LIST, ACC_CONTRACT::SEARCHFUNDDESC, dstr );
   SetDlgItemText ( IDC_TXT_FUND_DESC, dstr.c_str() );  
   //GetList ( IDC_LV_CONTRACTS )->DeleteAllItems();   
   getParent()->performSearch( this, IFASTBP_PROC::ACCOUNT_CONTRACT_LIST, SEARCH_START );
   LoadListControl ( IDC_LV_CONTRACTS );
   GetDlgItem( IDC_BTN_MORE )->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::ACCOUNT_CONTRACT_LIST ) );   

   SetMessageStatusBar(NULL_STRING);    
}

void AccountContractDlg::OnBtnHistorical() 
{
   TRACE_METHOD( CLASSNAME, I_("OnBtnHistorical") );   
   CWaitCursor wait;   
   IFastHistoricalInfo f;
   f( this, IFASTBP_PROC::ACCOUNT_CONTRACT_LIST, I_("MULTI") );
}

void AccountContractDlg::OnBtnContractReset() 
{
  MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnContractReset" ) );

   try
   {
      E_COMMANDRETURN eRtn = CMD_CANCEL;

      DString dstrAccountNum;
      getParent()->getField( this, IFASTBP_PROC::MFACCOUNT, ifds::AccountNum, dstrAccountNum );  
      
      setParameter( RESET_INSTR::ACCOUNT_NUM, dstrAccountNum );
      setParameter( RESET_INSTR::PARENT, RESET_INSTR::CONTRACT_DETAIL );
      //invoke the broker dialog and process

      eRtn = invokeCommand( getParent(), CMD_BPROC_RESET_INSTR, PROC_NO_TYPE, true, NULL );
/*      
      switch( eRtn )
      {
         case CMD_OK:
         case CMD_MODELESS_INPROCESS:
            {
               //get the broker code that the user selected from the branch list and 
               //set the field on the account object
               DString dstrAMSCode;

               getParameter( AMS_Para::AMS_CODE, dstrAMSCode );
               if( !dstrAMSCode.empty() )
               {
                  bool bSuccess = SetControlText( IDC_EDT_CRITERIA_VALUE, dstrAMSCode );
                  BaseControl * pBC = dynamic_cast< BaseControl *> (GetDlgItem( IDC_EDT_BROKER ));
                  if( !bSuccess && pBC )
                     pBC->Load();
                  if( pBC && pBC->IsToolTipVisible() )
                     pBC->ToggleToolTip();
               }
               break;
            }
         case CMD_CANCEL:
            break;
         default:
            // Display error
            ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
            break;
      }*/
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

void AccountContractDlg::OnBtnAdminDates()
{
   ShowAdminDates ( IFASTBP_PROC::ACCOUNT_CONTRACT_LIST );
}

void AccountContractDlg::fillFundCombo( )
{

   const DString *pCurKey = &( getParent()->getCurrentListItemKey( this, IFASTBP_PROC::PROT_FUND_LIST ) );
   const DString *pKey=&( getParent()->getFirstListItemKey( this, IFASTBP_PROC::PROT_FUND_LIST ));
   std::set < DString > protFundList;
   if( (*pKey)!=NULL_STRING )
   {
      do
      {
         DString dstr1,dstr2;
         getParent()->getField( this, IFASTBP_PROC::PROT_FUND_LIST, ifds::FundCode, dstr1 );
         dstr1.strip();
         getParent()->getField( this, IFASTBP_PROC::PROT_FUND_LIST, ifds::ClassCode, dstr2 );
         dstr2.strip();

         dstr1+=I_(" ")+dstr2;
         protFundList.insert(dstr1);         
      }while( *(pKey=&(getParent()->getNextListItemKey( this, IFASTBP_PROC::PROT_FUND_LIST ))) != NULL_STRING );

      if( (*pCurKey)!=NULL_STRING )
         getParent()->setCurrentListItem(this, IFASTBP_PROC::PROT_FUND_LIST, *pCurKey);
   }

   CComboBox* cb =static_cast<CComboBox* >(GetDlgItem( IDC_CMB_FUND ) );
   int iIndex;
   CString cstr;
   cstr.LoadString ( IDS_CAT_ALL );
   iIndex = cb->AddString ( cstr );   
   pCurKey = &( getParent()->getCurrentListItemKey( this, IFASTBP_PROC::ACCOUNT_HOLDINGS ) );
   pKey=&( getParent()->getFirstListItemKey( this, IFASTBP_PROC::ACCOUNT_HOLDINGS ));
   if( (*pKey)!=NULL_STRING )
   {
      do
      {
         DString dstr1,dstr2;
         getParent()->getField( this, IFASTBP_PROC::ACCOUNT_HOLDINGS, ifds::rxFundCode, dstr1 );
         dstr1.strip();
         getParent()->getField( this, IFASTBP_PROC::ACCOUNT_HOLDINGS, ifds::rxClassCode, dstr2 );
         dstr2.strip();

         dstr1+=I_(" ")+dstr2;
         if ( !protFundList.insert ( dstr1 ).second ) {
            iIndex = cb->AddString(dstr1.c_str());
            cb->SetItemData( iIndex, reinterpret_cast< DWORD >( pKey ) );
         }
      }while( *(pKey=&(getParent()->getNextListItemKey( this, IFASTBP_PROC::ACCOUNT_HOLDINGS ))) != NULL_STRING );

      if( (*pCurKey)!=NULL_STRING )
         getParent()->setCurrentListItem(this, IFASTBP_PROC::ACCOUNT_HOLDINGS, *pCurKey);
   }
   cb->SetCurSel(0);
}

//******************************************************************************

void AccountContractDlg::DoListItemChanged(  UINT listControlID,
                                             const DString &strKey,
                                             bool bIsNewItem ,
                                             bool bIsDummyItem
                                 )
{

   if( listControlID == IDC_LV_CONTRACTS )
   {
      // History
      GetDlgItem(IDC_BTN_HISTORICAL)->EnableWindow( (bIsNewItem || bIsDummyItem) ? FALSE : TRUE );
   }	
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/AccountContractDlg.cpp-arc  $
// 
//    Rev 1.11   Sep 15 2005 15:09:42   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.10   Mar 10 2004 13:02:04   HERNANDO
// PET965 FN11 - Added parameter to iFastHistoricalInfo.
// 
//    Rev 1.9   Feb 27 2004 15:55:24   HERNANDO
// PET965 FN11 - Enable/Disable Historical Button based on list item in doListItemChanged.
// 
//    Rev 1.8   Mar 21 2003 18:30:32   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.7   Mar 05 2003 11:30:08   PURDYECH
// Use IFastHistoricalInfo instead of deriving from IFastBaseMainDlg
// 
//    Rev 1.6   Jan 29 2003 15:50:18   HSUCHIN
// added historical functionality
// 
//    Rev 1.5   Jan 26 2003 15:55:06   HSUCHIN
// minor change to reset instr launch
// 
//    Rev 1.4   Jan 26 2003 14:45:28   HSUCHIN
// added hookup to contract resets and bug fix for control loading
// 
//    Rev 1.3   Jan 22 2003 18:00:16   HSUCHIN
// fixed bug in refresh
// 
//    Rev 1.2   Jan 21 2003 14:59:14   HSUCHIN
// set all as default for fund combo
// 
//    Rev 1.1   Jan 21 2003 13:45:04   HSUCHIN
// setup caption and added all to fund drop down and other enhancements
// 
//    Rev 1.0   Jan 20 2003 17:22:46   HSUCHIN
// Initial Revision
 */


