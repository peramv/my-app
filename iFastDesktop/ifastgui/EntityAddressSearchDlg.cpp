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
// ^FILE   : EntityAddressSearchDlg.cpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 01/07/2005
//
// ^CLASS    : EntityAddressSearchDlg
// ^SUBCLASS : 
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

#include "stdafx.h"

#ifndef IFASTGUI_H
   #include "mfdstc.h"
#endif

#ifndef ENTITYADDRESSSEARCHDLG_H
   #include "EntityAddressSearchDlg.h"
#endif
#include <ifastbp\EntityAddressSearchProcessincludes.h>
#include <ifastbp\mfcaninterprocparam.hpp>
#include <uibase\dstlistctrl.h>
#include <uibase\dstedit.h>
#include <ifastcbo\dstcommonfunction.hpp>
#include <ifastcbo\dstcworksession.hpp>
#include "discardmsgdlg.h"
#include <bfproc\genericinterfacecontainer.hpp>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_ENTITY_ADDRESS_SEARCH;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< EntityAddressSearchDlg > dlgCreator( CMD_GUI_ENTITY_ADDRESS_SEARCH);

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CLASS_IMPORT const I_CHAR* CMD_BPROC_ENTITY_ADDRESS_SEARCH;

namespace
{
	const I_CHAR * const YES							= I_( "Y" );
   const I_CHAR * const NO								= I_( "N" );
   const I_CHAR * const CLASSNAME					= I_( "EntityAddressSearchDlg" );
	const I_CHAR * const LV_ENTITY_ADDRESS			= I_( "Entity Address List" );
	const I_CHAR * const NAMES							= I_( "Names" );
	const I_CHAR * const LASTNAME						= I_( "LastName" );
	const I_CHAR * const ADDRESSID					= I_( "AddrId" );
	const I_CHAR * const POSTCODE						= I_( "PSTL" );
}
namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId SearchType;
   extern CLASS_IMPORT const BFTextFieldId SearchFirstName;
   extern CLASS_IMPORT const BFTextFieldId SearchLastName;
   extern CLASS_IMPORT const BFDecimalFieldId AddrId;
   extern CLASS_IMPORT const BFTextFieldId SearchPSTL;
   extern CLASS_IMPORT const BFTextFieldId SearchCountry;
	extern CLASS_IMPORT const BFTextFieldId SearchFieldCriteria1;
	extern CLASS_IMPORT const BFTextFieldId SearchFieldCriteria2;
	extern CLASS_IMPORT const BFTextFieldId EntityAddrSrch;
	extern CLASS_IMPORT const BFTextFieldId EntityAddressListHeading;

}

namespace CND
{//Conditionsused
   extern const long GUI_ERR_UNKNOWN_EXCEPTION;
}

//******************************************************************************

EntityAddressSearchDlg::EntityAddressSearchDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( EntityAddressSearchDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   //{{AFX_DATA_INIT(EntityAddressSearchDlg)
   // NOTE: the ClassWizard will add member initialization here
   //}}AFX_DATA_INIT
}

//******************************************************************************
EntityAddressSearchDlg::~EntityAddressSearchDlg()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}
//******************************************************************************

void EntityAddressSearchDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange( pDX );
   //{{AFX_DATA_MAP(EntityAddressSearchDlg)
   // NOTE: the ClassWizard will add DDX and DDV calls here
   //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(EntityAddressSearchDlg, BaseMainDlg)
//{{AFX_MSG_MAP(EntityAddressSearchDlg)
	ON_BN_CLICKED(IDC_BTN_REFRESH, OnBtnRefresh)
	ON_BN_CLICKED(IDC_BTN_MORE, OnBtnMore)
	ON_BN_CLICKED(IDC_BTN_SEARCH, OnBtnSearch)
	ON_NOTIFY(NM_DBLCLK, IDC_LV_ENTITY_ADDRESS, OnDblclkEntityAddressList)
	//}}AFX_MSG_MAP

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// EntityAddressSearchDlg message handlers

//*****************************************************************************
BOOL EntityAddressSearchDlg::OnInitDialog() 
{
   TRACE_METHOD(CLASSNAME, ONINITDIALOG);
   BaseMainDlg::OnInitDialog();
   return TRUE;
}

//******************************************************************************
void EntityAddressSearchDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, I_( "OnPostInitDialog" ) );
   CWaitCursor wait;
   addControls();
	showCriteria();
}

//******************************************************************************
SEVERITY EntityAddressSearchDlg::doInit()
{
   SEVERITY sevRtn = NO_CONDITION;

   return(sevRtn);
}
//******************************************************************************
void EntityAddressSearchDlg::addControls( )
{
   TRACE_METHOD( CLASSNAME, I_( "addControls" ) );    

	//list controls
	AddListControl( CLASSNAME,
		             IDC_LV_ENTITY_ADDRESS, 
						 LV_ENTITY_ADDRESS, 
						 ifds::EntityAddressListHeading,
                   IFASTBP_PROC::ENTITY_ADDRESS_LIST, 
						 0,true, LISTFLAG_NOT_AUTO_ADD );

   
   AddControl( CTRL_COMBO, 
		         IDC_CMB_USING, 
					IFASTBP_PROC::CRITERIA, 
					ifds::SearchType,
		         CTRLFLAG_AUTO_UPDATE_ON_CHANGE | CTRLFLAG_INITCOMBO_BY_SUB_LIST );    
  
	AddControl( CTRL_EDIT, 
		         IDC_EDT_SEARCH_VALUE1, 
					IFASTBP_PROC::CRITERIA, 
					ifds::SearchFieldCriteria1, 
		         CTRLFLAG_AUTO_UPDATE_ON_CHANGE );

	AddControl( CTRL_EDIT, 
		         IDC_EDT_SEARCH_VALUE2, 
					IFASTBP_PROC::CRITERIA, 
					ifds::SearchFieldCriteria2, 
		         CTRLFLAG_AUTO_UPDATE_ON_CHANGE );

	AddControl( CTRL_EDIT, 
		         IDC_EDT_ADDRESS, 
					IFASTBP_PROC::ENTITY_ADDRESS_LIST, 
					ifds::EntityAddrSrch, 
		         CTRLFLAG_AUTO_UPDATE_ON_CHANGE | CTRLFLAG_FIELDS_FROM_SUB_LIST, 
					(UINT)IDC_LV_ENTITY_ADDRESS );
	
	AddControl( CTRL_COMBO, 
		         IDC_CMB_COUNTRY, 
					IFASTBP_PROC::CRITERIA, 
					ifds::SearchCountry,
		         CTRLFLAG_AUTO_UPDATE_ON_CHANGE | CTRLFLAG_INITCOMBO_BY_SUB_LIST );    
	
   doRefresh (this, NULL_STRING);
	
}

//******************************************************************************

bool EntityAddressSearchDlg::doRefresh( GenericInterface * rpGICaller, 
                             const I_CHAR * szOriginalCommand )
{
   TRACE_METHOD( CLASSNAME, I_( "doRefresh" ) );

	ConnectControlsToData();
   LoadControls(IFASTBP_PROC::CRITERIA);
	GetDlgItem( IDC_BTN_MORE )->EnableWindow( false );

   return(true);
}

//******************************************************************************
void EntityAddressSearchDlg::OnBtnRefresh() 
{
	TRACE_METHOD( CLASSNAME, I_( "OnBtnRefresh" ) );

	GetDlgItem(IDC_BTN_REFRESH)->SetFocus();
	CWaitCursor wait;

	DString dstrSearchType;
	getParent()->getField(this,IFASTBP_PROC::CRITERIA,ifds::SearchType,dstrSearchType, false);
   getParent()->reset(this, IFASTBP_PROC::CRITERIA);
	getParent()->setField(this,IFASTBP_PROC::CRITERIA,ifds::SearchType,dstrSearchType, false);
	ReregisterObservers();
	showCriteria();
}

//******************************************************************************
void EntityAddressSearchDlg::OnBtnMore() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnMore" ) );

	GetDlgItem(IDC_BTN_MORE)->SetFocus();
	CWaitCursor wait;

	static int cursel;
   cursel = GetList( IDC_LV_ENTITY_ADDRESS )->GetNextItem( -1, LVIS_SELECTED | LVNI_FOCUSED );

   const DString *crtKey = &getParent()->getCurrentListItemKey( this, IFASTBP_PROC::ENTITY_ADDRESS_LIST );

   if( getParent()->performSearch( this, IFASTBP_PROC::ENTITY_ADDRESS_LIST, SEARCH_NEXT_BLOCK ) <= WARNING )
   {
      LoadListControl( IDC_LV_ENTITY_ADDRESS );
      if( *crtKey != NULL_STRING )
      {
         GetList( IDC_LV_ENTITY_ADDRESS )->SetSelection( crtKey );
      }
   }
   GetDlgItem( IDC_BTN_MORE )->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::ENTITY_ADDRESS_LIST ) );
	ConnectListToData( IDC_LV_ENTITY_ADDRESS, true );
	LoadListControl(IDC_LV_ENTITY_ADDRESS);
	showResults();
	GetList( IDC_LV_ENTITY_ADDRESS )->SetSelection(cursel, true, true);
   SetMessageStatusBar(NULL_STRING);
}
//******************************************************************************

void EntityAddressSearchDlg::OnBtnSearch() 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, I_( "OnBtnSearch" ) );

	GetDlgItem(IDC_BTN_SEARCH)->SetFocus();

	DString strSearchType;
  
	CWaitCursor wait;
   SetMessageStatusBar( TXT_SEARCHING );
   
   getParent()->performSearch(this, IFASTBP_PROC::ENTITY_ADDRESS_LIST, SEARCH_START );
  
	ConnectListToData( IDC_LV_ENTITY_ADDRESS, true );
	LoadListControl(IDC_LV_ENTITY_ADDRESS);
   if (GETHIGHESTSEVERITY() >= WARNING)
   {
      SetMessageStatusBar( NULL_STRING );
      //ConditionMessageBox( FRAMEBELOW(), GETHIGHESTSEVERITY() );
		OnBtnRefresh();
      return;
   }
	showResults();
   SetMessageStatusBar( NULL_STRING );
	GetDlgItem( IDC_BTN_MORE )->EnableWindow( getParent()->doMoreRecordsExist( this, IFASTBP_PROC::ENTITY_ADDRESS_LIST ) );
	setUpdateFlag(false);      // Clears Update for Dialog
   SetDefID( IDOK );
}

//******************************************************************************

void EntityAddressSearchDlg::ControlUpdated( UINT controlID, const DString &strValue )
{
	TRACE_METHOD( CLASSNAME, I_( "ControlUpdated" ) );
	CString cstrLabel;
	CWnd  *pWindow = NULL;
	switch( controlID )
   {
      case IDC_CMB_USING:
         {
            if ( strValue == NAMES )
            {
					GetDlgItem (IDC_STATIC_LABEL1)->EnableWindow(true);
					pWindow = GetDlgItem(IDC_STATIC_LABEL1);
					cstrLabel.LoadString(LBL_ENTITYADDRESS_FIRSTNAME);
					pWindow->SetWindowText(cstrLabel);
					GetDlgItem (IDC_STATIC_LABEL2)->EnableWindow(true);
					pWindow = GetDlgItem(IDC_STATIC_LABEL2);
					cstrLabel.LoadString(LBL_ENTITYADDRESS_LASTNAME);
					pWindow->SetWindowText(cstrLabel);
					//GetDlgItem (IDC_STATIC_LABEL2)->SetWindowText(  _T("    Last Name:") );
					ShowControl(IDC_EDT_SEARCH_VALUE1, true );
					ShowControl(IDC_EDT_SEARCH_VALUE2, true );
					ReInitControl(IDC_EDT_SEARCH_VALUE1, IFASTBP_PROC::CRITERIA, ifds::SearchFirstName);
					ReInitControl(IDC_EDT_SEARCH_VALUE2, IFASTBP_PROC::CRITERIA,ifds::SearchLastName);
               ConnectControl( IDC_EDT_SEARCH_VALUE1, true );
					GetControl( IDC_EDT_SEARCH_VALUE1 )->ConnectToData( true );
					LoadControl( IDC_EDT_SEARCH_VALUE1 );
					ShowControl( IDC_EDT_SEARCH_VALUE1, true );
					ConnectControl( IDC_EDT_SEARCH_VALUE2, true );
					GetControl( IDC_EDT_SEARCH_VALUE2 )->ConnectToData( true );
					LoadControl( IDC_EDT_SEARCH_VALUE2 );
					ShowControl( IDC_EDT_SEARCH_VALUE2, true );
					ShowControl( IDC_CMB_COUNTRY, false);
            }
				else if ( strValue == LASTNAME )
				{
					GetDlgItem (IDC_STATIC_LABEL1)->EnableWindow(true);
					pWindow = GetDlgItem(IDC_STATIC_LABEL1);
					cstrLabel.LoadString(LBL_ENTITYADDRESS_LASTNAME);
					pWindow->SetWindowText(cstrLabel);
					//GetDlgItem (IDC_STATIC_LABEL1)->SetWindowText( _T("Last Name:") );
					GetDlgItem(IDC_STATIC_LABEL2)->SetWindowText( _T("") );
					GetDlgItem (IDC_STATIC_LABEL2)->EnableWindow(false);
					ShowControl(IDC_EDT_SEARCH_VALUE1, true );
					ShowControl(IDC_EDT_SEARCH_VALUE2, false );
					ReInitControl(IDC_EDT_SEARCH_VALUE1, IFASTBP_PROC::CRITERIA, ifds::SearchLastName);
					ConnectControl( IDC_EDT_SEARCH_VALUE1, true );
					GetControl( IDC_EDT_SEARCH_VALUE1 )->ConnectToData( true );
					LoadControl( IDC_EDT_SEARCH_VALUE1 );
					ShowControl( IDC_EDT_SEARCH_VALUE1, true );
					ShowControl( IDC_CMB_COUNTRY, false);
				}
				else if ( strValue == ADDRESSID )
				{
					GetDlgItem (IDC_STATIC_LABEL1)->EnableWindow(true);
					pWindow = GetDlgItem(IDC_STATIC_LABEL1);
					cstrLabel.LoadString(LBL_ENTITYADDRESS_ADDRESSID);
					pWindow->SetWindowText(cstrLabel);
					//GetDlgItem(IDC_STATIC_LABEL1)->SetWindowText( _T("Address ID:") );
					GetDlgItem(IDC_STATIC_LABEL2)->SetWindowText( _T("            ") );
					GetDlgItem (IDC_STATIC_LABEL2)->EnableWindow(false);
					ShowControl (IDC_EDT_SEARCH_VALUE1, true );
					ReInitControl(IDC_EDT_SEARCH_VALUE1, IFASTBP_PROC::CRITERIA, ifds::AddrId);
					ShowControl (IDC_EDT_SEARCH_VALUE2, false );
					ConnectControl( IDC_EDT_SEARCH_VALUE1, true );
					GetControl( IDC_EDT_SEARCH_VALUE1 )->ConnectToData( true );
					LoadControl( IDC_EDT_SEARCH_VALUE1 );
					ShowControl( IDC_EDT_SEARCH_VALUE1, true );
					ShowControl( IDC_CMB_COUNTRY, false);
				}
				else if ( strValue == POSTCODE )
				{
					GetDlgItem (IDC_STATIC_LABEL1)->EnableWindow(true);
					pWindow = GetDlgItem(IDC_STATIC_LABEL1);
					cstrLabel.LoadString(LBL_ENTITYADDRESS_POSTCODE);
					pWindow->SetWindowText(cstrLabel);
					//GetDlgItem(IDC_STATIC_LABEL1)->SetWindowText( _T("Post Code:") );
					GetDlgItem (IDC_STATIC_LABEL2)->EnableWindow(true);
					pWindow = GetDlgItem(IDC_STATIC_LABEL2);
					cstrLabel.LoadString(LBL_ENTITYADDRESS_COUNTRYCODE);
					pWindow->SetWindowText(cstrLabel);
					//GetDlgItem(IDC_STATIC_LABEL2)->SetWindowText( _T("Country Code:") );
					ShowControl (IDC_EDT_SEARCH_VALUE1, true );
					ShowControl (IDC_EDT_SEARCH_VALUE2, false );
					ShowControl( IDC_CMB_COUNTRY, true );
					ReInitControl(IDC_EDT_SEARCH_VALUE1, IFASTBP_PROC::CRITERIA, ifds::SearchPSTL);
					ConnectControl( IDC_EDT_SEARCH_VALUE1, true );
					GetControl( IDC_EDT_SEARCH_VALUE1 )->ConnectToData( true );
					LoadControl( IDC_EDT_SEARCH_VALUE1 );
					ShowControl( IDC_EDT_SEARCH_VALUE1, true );
				}
	     }
         break;

		default:
         break;
   }
}

//******************************************************************************
bool EntityAddressSearchDlg::PreOk()
{
   TRACE_METHOD( CLASSNAME, PREOK );

   DSTListCtrl *dstListCtrlTemp = GetList(IDC_LV_ENTITY_ADDRESS);
   int iValue = dstListCtrlTemp->GetNextSelection();
   setParameter( PARM_SEARCHITEMFOUND, (iValue == -1) ? NULL_STRING : I_( "T" ) );
   return(true);
}

//******************************************************************************
void  EntityAddressSearchDlg::showDefaultSearchControls()
{
	DString dstrSearchType;
	getParent()->getField(this,IFASTBP_PROC::CRITERIA,ifds::SearchType,dstrSearchType,false);
	LoadControl( IDC_CMB_USING );
	if ( dstrSearchType.strip() == NAMES )
   {
		GetDlgItem (IDC_STATIC_LABEL1)->EnableWindow(true);
		CString cstrFirstName;
		cstrFirstName.LoadString(LBL_ENTITYADDRESS_FIRSTNAME);
		GetDlgItem (IDC_STATIC_LABEL1)->SetWindowText( cstrFirstName );
		GetDlgItem (IDC_STATIC_LABEL2)->EnableWindow(true);
		CString cstrLastName;
		cstrLastName.LoadString(TXT_LAST_NAME);
		GetDlgItem (IDC_STATIC_LABEL2)->SetWindowText(  cstrLastName );
		ShowControl(IDC_EDT_SEARCH_VALUE1, true );
		ShowControl(IDC_EDT_SEARCH_VALUE2, true );
		ReInitControl(IDC_EDT_SEARCH_VALUE1, IFASTBP_PROC::CRITERIA, ifds::SearchFirstName);
		ReInitControl(IDC_EDT_SEARCH_VALUE2, IFASTBP_PROC::CRITERIA,ifds::SearchLastName);
      ConnectControl( IDC_EDT_SEARCH_VALUE1, true );
		GetControl( IDC_EDT_SEARCH_VALUE1 )->ConnectToData( true );
		LoadControl( IDC_EDT_SEARCH_VALUE1 );
		ShowControl( IDC_EDT_SEARCH_VALUE1, true );
		ConnectControl( IDC_EDT_SEARCH_VALUE2, true );
		GetControl( IDC_EDT_SEARCH_VALUE2 )->ConnectToData( true );
		LoadControl( IDC_EDT_SEARCH_VALUE2 );
		ShowControl( IDC_EDT_SEARCH_VALUE2, true );
		ShowControl( IDC_CMB_COUNTRY, false);
   }
	else if ( dstrSearchType.strip() ==  LASTNAME )
	{
		GetDlgItem (IDC_STATIC_LABEL1)->EnableWindow(true);
		CString cstrLastName;
		cstrLastName.LoadString(TXT_LAST_NAME);
		GetDlgItem (IDC_STATIC_LABEL1)->SetWindowText( cstrLastName );
		GetDlgItem(IDC_STATIC_LABEL2)->SetWindowText( _T("") );
		GetDlgItem (IDC_STATIC_LABEL2)->EnableWindow(false);
		ShowControl(IDC_EDT_SEARCH_VALUE1, true );
		ShowControl(IDC_EDT_SEARCH_VALUE2, false );
		ReInitControl(IDC_EDT_SEARCH_VALUE1, IFASTBP_PROC::CRITERIA, ifds::SearchLastName);
		ConnectControl( IDC_EDT_SEARCH_VALUE1, true );
		GetControl( IDC_EDT_SEARCH_VALUE1 )->ConnectToData( true );
		LoadControl( IDC_EDT_SEARCH_VALUE1 );
		ShowControl( IDC_EDT_SEARCH_VALUE1, true );
		ShowControl( IDC_CMB_COUNTRY, false);
	}
	else if (dstrSearchType.strip() == ADDRESSID )
	{
		GetDlgItem (IDC_STATIC_LABEL1)->EnableWindow(true);
		CString cstrAddressId;
		cstrAddressId.LoadString(LBL_ENTITYADDRESS_ADDRESSID);
		GetDlgItem(IDC_STATIC_LABEL1)->SetWindowText( cstrAddressId );
		GetDlgItem(IDC_STATIC_LABEL2)->SetWindowText( _T("") );
		GetDlgItem (IDC_STATIC_LABEL2)->EnableWindow(false);
		ShowControl (IDC_EDT_SEARCH_VALUE1, true );
		ReInitControl(IDC_EDT_SEARCH_VALUE1, IFASTBP_PROC::CRITERIA, ifds::AddrId);
		ShowControl (IDC_EDT_SEARCH_VALUE2, false );
		ConnectControl( IDC_EDT_SEARCH_VALUE1, true );
		GetControl( IDC_EDT_SEARCH_VALUE1 )->ConnectToData( true );
		LoadControl( IDC_EDT_SEARCH_VALUE1 );
		ShowControl( IDC_EDT_SEARCH_VALUE1, true );
		ShowControl( IDC_CMB_COUNTRY, false);
	}
	else if ( dstrSearchType.strip() ==  POSTCODE )
	{
		GetDlgItem (IDC_STATIC_LABEL1)->EnableWindow(true);
		CString cstrPostCode;
		cstrPostCode.LoadString(LBL_ENTITYADDRESS_POSTCODE);
		GetDlgItem(IDC_STATIC_LABEL1)->SetWindowText( cstrPostCode );
		GetDlgItem (IDC_STATIC_LABEL2)->EnableWindow(true);
		CString cstrCtryCode;
		cstrCtryCode.LoadString(LBL_ENTITYADDRESS_COUNTRYCODE);
		GetDlgItem(IDC_STATIC_LABEL2)->SetWindowText( cstrCtryCode );
		ShowControl (IDC_EDT_SEARCH_VALUE1, true );
		ShowControl (IDC_EDT_SEARCH_VALUE2, false );
		ShowControl( IDC_CMB_COUNTRY, true );
		LoadControl( IDC_CMB_COUNTRY);
		ReInitControl(IDC_EDT_SEARCH_VALUE1, IFASTBP_PROC::CRITERIA, ifds::SearchPSTL);
		ConnectControl( IDC_EDT_SEARCH_VALUE1, true );
		GetControl( IDC_EDT_SEARCH_VALUE1 )->ConnectToData( true );
		LoadControl( IDC_EDT_SEARCH_VALUE1 );
		ShowControl( IDC_EDT_SEARCH_VALUE1, true );
	}
}

//******************************************************************************
void EntityAddressSearchDlg::showResults()
{
	TRACE_METHOD( CLASSNAME, I_( "showResults" ) );

	GetList(IDC_LV_ENTITY_ADDRESS)->ShowWindow(true);
	GetDlgItem(IDC_EDT_ADDRESS)->ShowWindow(true);
	GetDlgItem(IDC_RESULTS_FRAME)->EnableWindow(true);
	GetDlgItem (IDC_CMB_USING)->EnableWindow(false);
	GetDlgItem(IDC_BTN_SEARCH)->EnableWindow(false);
  // ConnectListToData( IDC_LV_ENTITY_ADDRESS, true ); 
   //LoadListControl(IDC_LV_ENTITY_ADDRESS);
    
	GetList(IDC_LV_ENTITY_ADDRESS)->SetFocus();

}
//******************************************************************************
void EntityAddressSearchDlg::showCriteria()
{
	TRACE_METHOD( CLASSNAME, I_( "showCriteria" ) );

	//list controls
	GetList(IDC_LV_ENTITY_ADDRESS)->ShowWindow(false);
	GetDlgItem(IDC_EDT_ADDRESS)->ShowWindow(false);
	
	GetDlgItem (IDC_CMB_USING)->EnableWindow(true);

	//static controls, frames (group boxes)
	GetDlgItem(IDC_RESULTS_FRAME)->EnableWindow(false);

   ConnectListToData( IDC_LV_ENTITY_ADDRESS, false ); 

	//buttons
	GetDlgItem(IDC_BTN_SEARCH)->EnableWindow(true);
	GetDlgItem(IDC_BTN_MORE)->EnableWindow(false);
	GetDlgItem(IDC_CMB_USING)->SetFocus();
	showDefaultSearchControls();
}

//******************************************************************************
void EntityAddressSearchDlg::OnDblclkEntityAddressList( NMHDR* pNMHDR, LRESULT* pResult ) 
{
   PostMessage( WM_COMMAND, IDOK );
   *pResult = 0;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/EntityAddressSearchDlg.cpp-arc  $
// 
//    Rev 1.5   Nov 19 2011 01:29:38   wp040143
// P0186484/FN06 - DESKTOP - iFast Desktop (French Customizations)
// 
//    Rev 1.4   Sep 15 2005 15:11:22   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.3   Apr 22 2005 11:49:26   ZHANGCEL
// Incident #294429 -- Use definition in string table instead of hard code for the lables
// 
//    Rev 1.2   Apr 21 2005 17:23:36   ZHANGCEL
// Incident #294429 -- Center the lables
// 
//    Rev 1.1   Mar 31 2005 17:07:22   ZHANGCEL
// PET 1171 - FN 01 -- Set SearchType to the current item
// 
//    Rev 1.0   Mar 10 2005 16:18:42   ZHANGCEL
// Initial revision.
//
*/