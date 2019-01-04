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
//    Copyright 2002 by International Financial.
//
//******************************************************************************
//
// ^FILE   : FireFighterLogonDlg.cpp
// ^AUTHOR : 
// ^DATE   : Dec 2, 2004
//
// ^CLASS    : 
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

#include "stdafx.h"

#ifndef IFASTGUI_H
   #include "mfdstc.h"
#endif


#ifndef FIREFIGHTERLOGONDLG_HPP
   #include "FireFighterLogonDlg.hpp"
#endif

#ifndef FIREFIGHTERLOGONINCLUDES_H
   #include <ifastbp\FireFighterLogonProcessIncludes.h>
#endif

#include <ifastcbo\dstcworksession.hpp>
#include <ifastbp\usersessionprocessincludes.h>
#include <uibase\dstedit.h>
#include <ifastdbrkr\dstchost.hpp>
#include <ifastdbrkr\dstcsecurity.hpp>


extern CLASS_IMPORT const I_CHAR* CMD_GUI_FIRE_FIGHTER_LOGON;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< FireFighterLogonDlg > dlgCreator( CMD_GUI_FIRE_FIGHTER_LOGON );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME      = I_( "FireFighterLogonDlg" );
   const I_CHAR * const USER           = I_( "User" );
   const I_CHAR * const COLUMN			= I_( ":" );
   const I_CHAR * const SPACE				= I_( " " );
   const I_CHAR * const NUMBERS			= I_( "0123456789." );
   const I_CHAR * const YES				= I_( "Y" );
   const I_CHAR * const NO					= I_( "N" );
	const I_CHAR * const RRID_TYPE		= I_( "R" );

}

namespace CND
{  // Conditions used
   extern const long GUI_NO_FIRE_FIGHTER_ID_ENTERED;
   extern const long GUI_NO_PASSWORD_ENTERED;
	extern const long GUI_NO_INCIDENT_NUMBER_ENTERED;
	extern const long GUI_NO_DESCRIPTION_ENTERED;
}

//******************************************************************************
// Constructor
//******************************************************************************
FireFighterLogonDlg::FireFighterLogonDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( FireFighterLogonDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );   
   //{{AFX_DATA_INIT( FireFighterLogonDlg )
   //}}AFX_DATA_INIT
   
}

//******************************************************************************
// Destructor
//******************************************************************************
FireFighterLogonDlg::~FireFighterLogonDlg ()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
// Called by MFC framework to exchange and validate dialog data
//******************************************************************************
void FireFighterLogonDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange( pDX );
   //{{AFX_DATA_MAP( FireFighterLogonDlg )   
   //}}AFX_DATA_MAP
}

//******************************************************************************
// MFC Message Map
//******************************************************************************

BEGIN_MESSAGE_MAP( FireFighterLogonDlg, BaseMainDlg )
//{{AFX_MSG_MAP( FireFighterLogonDlg )
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//******************************************************************************
// Initialization of Dialog, get InterProcess Global data and sets up the 
// caption in the title bar.
//******************************************************************************
BOOL FireFighterLogonDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );
   BaseMainDlg::OnInitDialog();

   AddControl( CTRL_EDIT,  IDC_EDT_FFID, IFASTBP_PROC::FIRE_FIGHTER_LOGON_INFO, ifds::FireFighterId, 0, 0 );
   AddControl( CTRL_EDIT,  IDC_EDT_PASSWORD, IFASTBP_PROC::FIRE_FIGHTER_LOGON_INFO, ifds::FireFighterPassword, 0, 0 );
   AddControl( CTRL_EDIT,  IDC_EDT_PTS_NUMBER, IFASTBP_PROC::FIRE_FIGHTER_LOGON_INFO, ifds::PTSNumber, 0, 0 );
   AddControl( CTRL_EDIT,  IDC_EDT_DESCRIPTION, IFASTBP_PROC::FIRE_FIGHTER_LOGON_INFO, ifds::FFDesc, CTRLFLAG_FIELDS_FROM_SUB_LIST | CTRLFLAG_WORD_WRAP, 0 );
   dynamic_cast<DSTEdit *>( GetControl( IDC_EDT_DESCRIPTION ) )->SetMaxCharNum( 60 );
   ( dynamic_cast < DSTEdit* > ( GetControl( IDC_EDT_PTS_NUMBER ) ) )->SetAllowedChars( NUMBERS );

   ConnectControlsToData();
   LoadControls();   
  
	doRefresh(this, NULL_STRING);

   SetForegroundWindow();

	return(TRUE);  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}


//******************************************************************************
// doInit method is not used.
//******************************************************************************
SEVERITY FireFighterLogonDlg::doInit()
{
   return ( NO_CONDITION );
}

//******************************************************************************
// Method to refresh dialog controls
// @param   GenericInterface *rpGICaller - pointer to the calling object
// @param   const I_CHAR *szOriginalCommand - Not used in this case, but 
//                      can be used to instruct special processing.
//******************************************************************************
bool FireFighterLogonDlg::doRefresh( GenericInterface * rpGICaller, 
                                  const I_CHAR * szOriginalCommand )
{
	DString dstrPassWord;
   getParent()->getParent()->getField( this, USERID, _dstrUserId );

	getParent()->getParent()->getField( this, PASSWORD, dstrPassWord );
	

	DString dstrAccessIdR, dstrAccessIdF;
	getParent()->getField(this, BF::NullContainerId, FIREFIGHTER::IS_ACCESSID_R,dstrAccessIdR );
	getParent()->getField(this, BF::NullContainerId, FIREFIGHTER::IS_ACCESSID_F,dstrAccessIdF );

	if ( dstrAccessIdR == YES || dstrAccessIdF == YES )
	{
		getParent()->setField( this, IFASTBP_PROC::FIRE_FIGHTER_LOGON_INFO, ifds::FireFighterId, _dstrUserId, false);
		getParent()->setField( this, IFASTBP_PROC::FIRE_FIGHTER_LOGON_INFO, ifds::FireFighterPassword, dstrPassWord, false);
		
		LoadControl(IDC_EDT_FFID);
		EnableControl( IDC_EDT_FFID, false );
		LoadControl(IDC_EDT_PASSWORD);
		EnableControl( IDC_EDT_PASSWORD, false );
	}
		
	setDlgTitle();
   return(true);
}

//******************************************************************************
// Overrides canCancel so that discard dialog does not show up.
// @returns bool - true.
//******************************************************************************
bool FireFighterLogonDlg::canCancel() 
{   
   return(true);
}

//******************************************************************************
void FireFighterLogonDlg::setDlgTitle()
{

   CString caption = GetBaseCaption().c_str();

   caption += COLUMN;
   caption += SPACE;
   caption += _dstrUserId.c_str();

   SetWindowText( caption );
}

//******************************************************************************
bool FireFighterLogonDlg::PreOk()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, PREOK );
   

   SetMessageStatusBar( TXT_PROGRESS_LOGON );
   // Verify that required fields were entered
   	CString cstr;
	GetDlgItem(IDC_EDT_FFID)->GetWindowText(cstr);
	DString strTmp(cstr);
   if( strTmp.empty() )
   {
      ADDCONDITIONFROMFILE( CND::GUI_NO_FIRE_FIGHTER_ID_ENTERED );
      FocusOnControl( IDC_EDT_FFID );
      return(false);
   }

	GetDlgItem(IDC_EDT_PASSWORD)->GetWindowText(cstr);
	strTmp = cstr;
   if( strTmp.empty() )
   {
      ADDCONDITIONFROMFILE( CND::GUI_NO_PASSWORD_ENTERED );
      FocusOnControl( IDC_EDT_PASSWORD );
      return(false);
   }

	/*
    DString dstrSameVersion;
	getParent()->getField(this, BF::NullContainerId, FIREFIGHTER::IS_THE_SAME_VERSION,dstrSameVersion );

	if ( dstrSameVersion == NO )
	{
         if( IDNO == AfxMessageBox( TXT_VERSION_NOT_MATCH, MB_YESNO ) )
         {
            return false;
		 }
	}
	*/

	// Incident Number is mandatory
	GetDlgItem(IDC_EDT_PTS_NUMBER)->GetWindowText(cstr);
	strTmp = cstr;
   if( strTmp.empty() )
   {
      ADDCONDITIONFROMFILE( CND::GUI_NO_INCIDENT_NUMBER_ENTERED );
      FocusOnControl( IDC_EDT_PTS_NUMBER );
      return(false);
   }

	// Descripion is mandatory
	GetDlgItem(IDC_EDT_DESCRIPTION)->GetWindowText(cstr);
	strTmp = cstr;
   if( strTmp.empty() )
   {
      ADDCONDITIONFROMFILE( CND::GUI_NO_DESCRIPTION_ENTERED );
      FocusOnControl( IDC_EDT_DESCRIPTION );
      return(false);
   }

	SEVERITY sevRte =  GETCURRENTHIGHESTSEVERITY();
	if (sevRte > WARNING )
	{
		doRefresh(this, NULL_STRING);
		return (false);
	}
   return(true);
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/FireFighterLogonDlg.cpp-arc  $
// 
//    Rev 1.8   Sep 28 2005 13:38:12   ZHANGCEL
// PET1235 - FN02 -- Apply wor wrap on Discreption field.
// 
//    Rev 1.7   Sep 15 2005 15:12:20   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.6   Sep 12 2005 16:02:08   ZHANGCEL
// PET1235 - FN02 -- Apply samilar logic as RRID for FFID
// 
//    Rev 1.5   Sep 01 2005 15:07:22   ZHANGCEL
// PET1235 -FN02 - Add logic to validate Description.
// 
//    Rev 1.4   Aug 31 2005 16:14:22   ZHANGCEL
// PET1235 - FN02 -- Add logic to validate Incident Number and move logic into doRefresh() function
// 
//    Rev 1.3   Aug 22 2005 10:52:22   ZHANGCEL
// PET 1235 - FN02 -- Enhancement for Restricted Read Only Unserid 
// 
//    Rev 1.2   Dec 15 2003 11:06:50   linmay
// clean code
// 
//    Rev 1.1   Dec 11 2003 11:36:14   linmay
// modified PreOK for version compare
// 
//    Rev 1.0   Dec 09 2003 09:10:08   linmay
// Initial Revision
// 
 */


