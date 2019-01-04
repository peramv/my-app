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
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : ogonDlg.cpp
// ^AUTHOR : John Haubrich
// ^DATE   : 06-97
//
// ----------------------------------------------------------
//
// ^CLASS    : LogonDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS
//
//*******************************************************************************

#include "stdafx.h"
#include "MFDSTC.h"
#include "logonDlg.h"
#include <uibase\BaseControl.hpp>
#include "MainFrm.h"
#include <uibase\DSTCDoc.h>
#include "DSTCView.h"
#include <ifastbp\UserSessionProcessIncludes.h>
#include "ConfigurationConstants.h"
#include <ConfigManager.hpp>
#include <bfawdi/bfawdinterface.hpp>
#include <bf/log/log.hpp>

#include <ifsupp/AboutPropSheet.h>

extern CLASS_IMPORT const I_CHAR* CMD_GUI_LOGON;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< LogonDlg > dlgCreator( CMD_GUI_LOGON );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// #define MAX_PASSWORD_LENGTH   15

namespace
{
   const I_CHAR *CLASSNAME = I_( "LogonDlg" );
}

namespace CND
{
   extern const long GUI_NO_OPERATOR_ID_ENTERED;
   extern const long GUI_NO_PASSWORD_ENTERED;
   extern const long GUI_NEW_PASSWORD_CONFIRMATION_NO_MATCH;
   extern const long GUI_NEW_PASSWORD_TOO_SIMPLE;
}
//*******************************************************************************
// Public methods
//*******************************************************************************

LogonDlg::LogonDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( LogonDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   //{{AFX_DATA_INIT(LogonDlg)
   //}}AFX_DATA_INIT
}

//*******************************************************************************

void LogonDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(LogonDlg)
   DDX_Control(pDX, IDC_LOGON_SITE_CONFIG, m_XMLConfigTextBox);
   //}}AFX_DATA_MAP
}

//*******************************************************************************

BEGIN_MESSAGE_MAP(LogonDlg, BaseMainDlg)
//{{AFX_MSG_MAP(LogonDlg)
   ON_BN_CLICKED(IDC_BUTTON1, OnBtnDetails)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//*******************************************************************************
// Message handlers
//*******************************************************************************

BOOL LogonDlg::OnInitDialog()
{
   TRACE_METHOD( CLASSNAME, ONINITDIALOG );
   BaseMainDlg::OnInitDialog();

   AddControl( CTRL_EDIT, IDC_LOGON_USERID, BF::NullContainerId, USERID );
   AddControl( CTRL_EDIT, IDC_LOGON_PASSWORD, BF::NullContainerId, PASSWORD );
   AddControl( CTRL_EDIT, IDC_LOGON_NEWPW, BF::NullContainerId, NEWPASSWORD );
   AddControl( CTRL_EDIT, IDC_LOGON_CONFIRMNEWPW, BF::NullContainerId, ifds::NullFieldId, CTRLFLAG_GUI_FIELD );

   DString dstrXMLConfigFile =
      GetConfigValueAsString( CONFIGURATION_CONSTANTS::MFDSTC,
                              I_("SiteXML" ),
                              I_("file" ) );

   DString dstrXMLConfigFileDesc =
      GetConfigValueAsString( CONFIGURATION_CONSTANTS::MFDSTC,
                              I_("SiteXML" ),
                              I_("Description" ) );

   ConnectControlsToData();
   // Set initial size to 12 and bring us to the front
//   m_ctlUserID.LimitText( 12 );
//   m_ctlPassword.LimitText( MAX_PASSWORD_LENGTH );
//   m_ctlNewPW.LimitText( MAX_PASSWORD_LENGTH );
//   m_ctlConfirmNewPW.LimitText( MAX_PASSWORD_LENGTH );

   SetForegroundWindow();
   m_XMLConfigTextBox.SetWindowText(dstrXMLConfigFileDesc.c_str());

   return(TRUE);  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

void LogonDlg::OnBtnDetails()
{
   CWaitCursor waitCursor;

   AboutPropSheet::Display();
}

//******************************************************************************

// TODO - this field should move to CBO

bool LogonDlg::GetDataForControl(
                                UINT controlID,
                                DString &strValueOut,
                                bool bFormatted,
                                int index
                                ) const
{
   bool bRtn = false;

   switch( controlID )
   {
      case IDC_LOGON_CONFIRMNEWPW:
         strValueOut = m_confirmPassword;
         bRtn = true;
         break;
   }
   return(bRtn);
}

//*****************************************************************************

bool LogonDlg::PreOk()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTGUI_CONDITION, CLASSNAME, PREOK );
   DString strNewPassword;
   DString strConfirmNewPassword;
   DString strTmp;

   SetMessageStatusBar( TXT_PROGRESS_LOGON );
// - TODO These edits should all occur in CBO
   // Verify that required fields were entered
   if( GetControlText( IDC_LOGON_USERID, strTmp ).empty() )
   {
      ADDCONDITIONFROMFILE( CND::GUI_NO_OPERATOR_ID_ENTERED );
      FocusOnControl( IDC_LOGON_USERID );
      return(false);
   }
   if( GetControlText( IDC_LOGON_PASSWORD, strTmp ).empty() )
   {
      ADDCONDITIONFROMFILE( CND::GUI_NO_PASSWORD_ENTERED );
      FocusOnControl( IDC_LOGON_PASSWORD );
      return(false);
   }

   // Verify that new passwords match
   if( GetControlText( IDC_LOGON_NEWPW, strNewPassword ) !=
       GetControlText( IDC_LOGON_CONFIRMNEWPW, strConfirmNewPassword ) )
   {
      ADDCONDITIONFROMFILE( CND::GUI_NEW_PASSWORD_CONFIRMATION_NO_MATCH );
      FocusOnControl( IDC_LOGON_NEWPW );
      return(false);
   }

   // Verify that new passwords meet complexity rules
   if( strNewPassword.length() != 0 ) {
      int minLength = (GetConfigValueAsBool( I_("Support"), I_("SpecialPasswordRules") ) == 1 ) ? 8 : 6;
     if( strNewPassword.length() < minLength ) {
       DString idiStr;
       addIDITagValue( idiStr, I_("NUM_CHARS"), DString::asString(minLength) );
        ADDCONDITIONFROMFILEIDI( CND::GUI_NEW_PASSWORD_TOO_SIMPLE, idiStr );
        FocusOnControl( IDC_LOGON_NEWPW );
       return(false);
     }
   }

   DString dstrAWDAutoLogon =
      GetConfigValueAsString(  CONFIGURATION_CONSTANTS::MFDSTC,
                               I_("AwdType" ),
                               I_("AutoLogon" ) );
   if( dstrAWDAutoLogon == I_("1") ) {
      SetMessageStatusBar( I_("AWD Auto Logon") );
      AWDAutoLogon();
      SetMessageStatusBar( TXT_PROGRESS_LOGON );
   }

   return(true);
}

//*****************************************************************************

void LogonDlg::PostOk( bool bOkStatus )
{
   if( bOkStatus )
   {  // Save language
      getParent()->getField( this, LANGUAGE, m_dstrLanguage );
      ((MFDSTCApp*)AfxGetApp())->setLanguage( m_dstrLanguage );
   }
   else
   {
      FocusOnControl( IDC_LOGON_PASSWORD );
   }
}

//******************************************************************************

void LogonDlg::PostNcDestroy()
{
   BaseMainDlg::PostNcDestroy();
}

//******************************************************************************

bool LogonDlg::SetDataFromControl(
                                 UINT controlID,
                                 const DString &strValue,
                                 bool bFormatted,
                                 SEVERITY &sevRtn,
                                 int index
                                 )
{
   bool bRtn = false;

   switch( controlID )
   {
      case IDC_LOGON_CONFIRMNEWPW:
         m_confirmPassword = strValue;
         bRtn = true;
         break;
   }
   return(bRtn);
}

//******************************************************************************
void LogonDlg::AWDAutoLogon() const
{
   bf::log::LogStream ls( bf::log::awd );
   ls << bf::log::information << I_("AWD Auto Logon ");

   if( BFAwdInterface::isLoggedOn() ) {
      // Don't logon if we're already logged on
      ls << I_("unnecessary.  Already logged on.") << bf::log::endlf;
      return;
   }

   ls << I_(" starting") << bf::log::endlf;
   DString dstrUserId;
   DString dstrPassword;
   if( GetControlText( IDC_LOGON_USERID, dstrUserId ).empty() ) {
      return;
   }
   ls << I_("AWD AutoLogon UserId: ") << dstrUserId << bf::log::endlf;
   GetControlText( IDC_LOGON_PASSWORD, dstrPassword );

   I_CHAR szBuf[256] = {0};
   i_snprintf( szBuf, sizeof(szBuf) / sizeof(szBuf[0]),
               I_("awdlogon.exe %s %s"),
               dstrUserId.c_str(),
               dstrPassword.c_str() );
   STARTUPINFO si = {0};
   si.cb = sizeof(si);
   PROCESS_INFORMATION pi = {0};
   if( CreateProcess( NULL,   /* lpApplicationName */
                      szBuf,  /* lpCommandLine */
                      NULL,   /* lpProcessAttributes */
                      NULL,   /* lpThreadAttributes */
                      TRUE,   /* bInheritHandles */
                      0,      /* dwCreationFlags */
                      NULL,   /* lpEnvironment */
                      NULL,   /* lpCurrentDirectory */
                      &si,    /* lpStartupInfo */
                      &pi     /* lpProcessInformation */ ) != FALSE ){
      WaitForSingleObject( pi.hProcess, INFINITE );
      DWORD dwExitCode = 0;
      GetExitCodeProcess( pi.hProcess, &dwExitCode );
      CloseHandle( pi.hProcess );
      CloseHandle( pi.hThread );
      ls << I_("AWD AutoLogon finished: ") << dwExitCode << bf::log::endlf;
   }
   else {
      DWORD rc = GetLastError();
      ls << bf::log::severe << I_("AWD AutoLogon failed: ") << GetLastError() << I_(".  ") << bf::log::endlf;
   }

}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/LogonDlg.cpp-arc  $
 * 
 *    Rev 1.18   Dec 05 2011 09:00:46   purdyech
 * ControlTextRewriter Logic
 *
 *    Rev 1.17   Oct 06 2011 14:27:50   purdyech
 * IN2647659 Sync Up
 *
 *    Rev 1.16   Sep 16 2011 17:16:00   dchatcha
 * Usability Improvement on iFAST/Desktop
 *
 *    Rev 1.15   Oct 24 2009 12:24:04   purdyech
 * AboutDetailsDlg has been removed.
 *
 *    Rev 1.14   Feb 09 2009 15:44:38   purdyech
 * Use new PropertySheet-based AboutDetails dialog
 *
 *    Rev 1.13   Jun 24 2007 09:05:22   purdyech
 * Added AWD AutoLogon feature to desktop
 *
 *    Rev 1.12   May 14 2007 15:13:56   purdyech
 * PTS820423 - Added hidden 'Details' button to invoke AboutDetails dialog.
 *
 *    Rev 1.11   Sep 15 2005 12:57:54   popescu
 * Incident # 403519 - saved/restored the size of the dialog in the registry
 *
 *    Rev 1.10   Mar 21 2003 18:38:28   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 *
 *    Rev 1.9   Oct 09 2002 23:55:46   PURDYECH
 * PVCS Database Conversion
 *
 *    Rev 1.8   Aug 29 2002 12:57:24   SMITHDAV
 * ClientLocale and typed field changes.
 *
 *    Rev 1.7   Jul 05 2002 11:49:42   PURDYECH
 * Infrastructure Fixup ... no more ICU!
 *
 *    Rev 1.6   27 Mar 2002 20:01:14   PURDYECH
 * Process/WindowFactory overhaul
 *
 *    Rev 1.5   Aug 24 2001 14:01:58   HUANGSHA
 * temp fix locale stuff
 *
 *    Rev 1.4   30 Jul 2001 15:49:54   YINGZ
 * auto change of resources
 *
 *    Rev 1.3   27 Jun 2001 16:19:34   SMITHDAV
 * Infra 1.9 change.
 *
 *    Rev 1.2   May 29 2001 11:44:34   HUANGSHA
 * Code Cleanup
 *
 *    Rev 1.1   Jul 27 2000 17:37:50   BUZILA
 * ClientLocale changes
 *
 *    Rev 1.0   Feb 15 2000 11:01:18   SMITHDAV
 * Initial revision.
 *
 *    Rev 1.14   Jan 18 2000 13:56:12   DT24433
 * changed to add conditions instead of display during PreOk
 *
 *    Rev 1.13   Nov 17 1999 12:52:00   DT24433
 * added ConnectControlsToData
 *
 *    Rev 1.12   Nov 12 1999 10:11:34   DT24433
 * made confirm password control a GUI_FIELD
 *
 *    Rev 1.11   Nov 04 1999 13:28:20   DT24433
 * changed ok to PreOk/PostOk
 *
 *    Rev 1.10   Nov 02 1999 17:27:06   YINGZ
 * change override
 *
 *    Rev 1.9   Oct 18 1999 17:32:56   DT24433
 * initial changes for using control container
 *
 *    Rev 1.8   Aug 26 1999 10:30:28   HSUCHIN
 * Changed Dialog class to use GetDialogText to get control text.
 *
 *    Rev 1.7   Aug 13 1999 16:27:40   VASILEAD
 * set infra locale according to user language code
 *
 *    Rev 1.6   Aug 08 1999 17:34:22   VASILEAD
 * Limited the maximum user id length to 12
 *
 *    Rev 1.5   Aug 04 1999 11:39:44   PRAGERYA
 * Date fix
 *
 *    Rev 1.4   03 Aug 1999 17:05:12   HUANGSHA
 * Recheck as the Timezone is set wrongly
 *
 *    Rev 1.3   04 Aug 1999 17:03:42   HUANGSHA
 * Highlight the password if wrong
 *
 *    Rev 1.2   Jul 20 1999 11:19:04   VASILEAD
 * New conditions update
 *
 *    Rev 1.1   Jul 08 1999 10:05:26   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
