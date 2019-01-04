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
// ^FILE   : FTPLogonDlg.cpp
// ^AUTHOR : 
// ^DATE   : Dec 9, 2002
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

#ifndef ABSTRACTPROCESS_HPP
   #include <bfproc\AbstractProcess.hpp>
#endif

#ifndef FTPLOGONDLG_H
   #include "FTPLogonDlg.h"
#endif

#include <bfproc\genericinterfacecontainer.hpp>
#include <ifastcbo\dstcusersession.hpp>
#include <configurationconstants.h>
#include <ifastbp\usersessionprocessincludes.h>
#include <uibase\dstedit.h>

#ifndef DSTCHOST_HPP
   #include <ifastdbrkr\DSTCHost.hpp>
#endif

#include <ifastbp\ftplogonprocessincludes.h>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_FTP_LOGON;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_USER_SESSION;

#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< FTPLogonDlg > dlgCreator( CMD_GUI_FTP_LOGON );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const I_CHAR * const CLASSNAME               = I_( "FTPLogonDlg" );
   const I_CHAR * const USER                    = I_( "User" );
   const I_CHAR * const MFDSTC                  = I_( "MFDSTC" );
   const I_CHAR * const FTPSITE                 = I_( "FTP" );
   const I_CHAR * const FTPPORT                 = I_( "Port" );   
}

namespace CND
{  // Conditions used
//CP20030319   extern CLASS_IMPORT const long GUI_ERR_UNKNOWN_EXCEPTION;
}

//******************************************************************************
// Constructor
//******************************************************************************
FTPLogonDlg::FTPLogonDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( FTPLogonDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );   
   //{{AFX_DATA_INIT( FTPLogonDlg )
   //}}AFX_DATA_INIT
   
}

//******************************************************************************
// Destructor
//******************************************************************************
FTPLogonDlg::~FTPLogonDlg ()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
// Called by MFC framework to exchange and validate dialog data
//******************************************************************************
void FTPLogonDlg::DoDataExchange( CDataExchange* pDX )
{
   BaseMainDlg::DoDataExchange( pDX );
   //{{AFX_DATA_MAP( FTPLogonDlg )   
   //}}AFX_DATA_MAP
}

//******************************************************************************
// MFC Message Map
//******************************************************************************

BEGIN_MESSAGE_MAP( FTPLogonDlg, BaseMainDlg )
//{{AFX_MSG_MAP( FTPLogonDlg )
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//******************************************************************************
// Initialization of Dialog, get InterProcess Global data and sets up the 
// caption in the title bar.
//******************************************************************************
BOOL FTPLogonDlg::OnInitDialog() 
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );
   BaseMainDlg::OnInitDialog();
   return(TRUE);  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

//******************************************************************************
// Call by based architecture.  Controls are initialized here by calling the
// addControls() method.  The More button is enable/disable based on the CBO
// data.
//******************************************************************************
void FTPLogonDlg::OnPostInitDialog()
{
   TRACE_METHOD( CLASSNAME, I_( "OnPostInitDialog" ) );
   CWaitCursor wait;
   AddControl( CTRL_EDIT,  IDC_EDIT3, BF::NullContainerId, ifds::FTPSite, 0, 0 );
   AddControl( CTRL_EDIT,  IDC_EDIT4, BF::NullContainerId, ifds::FTPPort, 0, 0 );
   AddControl( CTRL_EDIT,  IDC_EDT_FTP_USER, BF::NullContainerId, ifds::User_Id, 0, 0 );
   AddControl( CTRL_EDIT,  IDC_EDT_FTP_PWD, BF::NullContainerId, ifds::Password, 0, 0 );
   ConnectControlsToData();
   LoadControls();   
   dynamic_cast<DSTEdit *>( GetControl( IDC_EDIT4 ) )->SetAllowedChars( I_("0123456789") );
   dynamic_cast<DSTEdit *>( GetControl( IDC_EDIT4 ) )->SetMaxCharNum( 5 );
   m_pUser = ConfigManager::getManager( USER );   
   GenericInterface* rpGIUserSession = NULL;
   rpGIUserSession = getGIContainer()->findGI( getBFSession(), CMD_BPROC_USER_SESSION );
   DString userID;
   rpGIUserSession->getField ( this, USERID, userID );
   m_user = m_pUser->retrieveConfig( userID );
   DString dstrFTPSite, dstrFTPPort, dstrUserId;
   dstrFTPSite = m_user.getValueAsString( FTPSITE );
   dstrFTPPort = m_user.getValueAsString( FTPPORT );
   dstrUserId = m_user.getValueAsString( USER );   

   if ( dstrFTPSite == NULL_STRING ) {
      ConfigManager *pMFDSTC = ConfigManager::getManager( MFDSTC );
      Configuration cfgPath = pMFDSTC->retrieveConfig( CONFIGURATION_CONSTANTS::RTSHost );
      dstrFTPSite = cfgPath.getValueAsString( CONFIGURATION_CONSTANTS::RTSHostIP );
   }

   if ( dstrFTPPort == NULL_STRING ) {
      dstrFTPPort = I_("21");
   }

   SetDlgItemText ( IDC_EDIT3, dstrFTPSite.c_str () );
   SetDlgItemText ( IDC_EDIT4, dstrFTPPort.c_str () );
   SetDlgItemText ( IDC_EDT_FTP_USER, dstrUserId.c_str () );
}

//******************************************************************************
// doInit method is not used.
//******************************************************************************
SEVERITY FTPLogonDlg::doInit()
{
   return ( NO_CONDITION );
}

//******************************************************************************
// Method to refresh dialog controls
// @param   GenericInterface *rpGICaller - pointer to the calling object
// @param   const I_CHAR *szOriginalCommand - Not used in this case, but 
//                      can be used to instruct special processing.
//******************************************************************************
bool FTPLogonDlg::doRefresh( GenericInterface * rpGICaller, 
                                  const I_CHAR * szOriginalCommand )
{
   return(true);
}

//******************************************************************************
// Overrides canCancel so that discard dialog does not show up.
// @returns bool - true.
//******************************************************************************
bool FTPLogonDlg::canCancel() 
{   
   return(true);
}

void FTPLogonDlg::PostOk( bool bOkStatus )
{
   if ( bOkStatus ) {
      DString dstrFTPSite, dstrFTPPort, dstrUserId;
      getParent()->getField ( this, BF::NullContainerId, ifds::FTPSite, dstrFTPSite, false );
      getParent()->getField ( this, BF::NullContainerId, ifds::FTPPort, dstrFTPPort, false );
      getParent()->getField ( this, BF::NullContainerId, ifds::User_Id, dstrUserId, false );   
      ConfigValue cvFTPSite( dstrFTPSite );
      m_user.set( FTPSITE, cvFTPSite );
      ConfigValue cvFTPPort( dstrFTPPort );
      m_user.set( FTPPORT, cvFTPPort );
      ConfigValue cvUserId( dstrUserId );
      m_user.set( USER, cvUserId );

      if( !m_pUser->undefined() )
      {
         m_pUser->storeConfig( m_user );
         m_pUser->persist();
      }

   }
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/FTPLogonDlg.cpp-arc  $
// 
//    Rev 1.4   Sep 15 2005 15:12:34   popescu
// Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
// 
//    Rev 1.3   Jun 05 2003 15:42:44   HERNANDO
// PTS 10017935 - Replaced container Id with BF::NullContainerId.
// 
//    Rev 1.2   Mar 21 2003 18:36:50   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.1   Dec 10 2002 13:35:44   HSUCHIN
// additional support
// 
//    Rev 1.0   Dec 10 2002 09:54:52   HSUCHIN
// Initial Revision
 */


