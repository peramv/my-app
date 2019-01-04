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
// ^FILE   : ManagementCompanyDlg.cpp
// ^AUTHOR : Jerry Leenerts
// ^DATE   : 2/99
//
// ----------------------------------------------------------
//
// ^CLASS    : ManagementCompanyDlg
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for the System/MGMT selection dialog
//
//******************************************************************************
#include "stdafx.h"
#include "WinUser.h"

#include "mfdstc.h"
#include "managementcompanydlg.h"
#include <bfawdi\bfawdinterface.hpp>
#include <bfproc\bpsessiontags.h>
#include <configmanager.hpp>
#include <uibase\dstcdoc.h>
#include "dstcview.h"
#include <bfawdi\diawdcnd.h>
#include "mainfrm.h"
#include <bfsessn\bfcpsession.hpp>
#include <ifastbp\usersessionprocessincludes.h>
#include <ifastdataimpl\dse_dstcglob_vw.hpp>
#include <assert.h>
#include "SiteConfig.h"
#include "ConfigurationConstants.h"
#include <ifsupp/ifsuppext.hpp>

#include <ifsupp/AboutPropSheet.h>


extern CLASS_IMPORT const I_CHAR* CMD_GUI_MANAGEMENT_COMPANY;
extern CLASS_IMPORT const I_CHAR* CMD_BPROC_PROGRESS_CTRL;
#include <bfproc\concretedialogcreator.hpp>
static ConcreteDialogCreator< ManagementCompanyDlg > dlgCreator( CMD_GUI_MANAGEMENT_COMPANY );

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   // trace literals
   const I_CHAR * const CLASSNAME               = I_( "ManagementCompanyDlg" );
   const I_CHAR * const DBLCLK                  = I_( "OnDblclkLstSelction" );
   const I_CHAR * const GETEXTENSION            = I_( "getExtension" );
   const I_CHAR * const STOREEXT                = I_( "storeExtension" );
   const I_CHAR * const STORECOMP               = I_( "storeCompany" );

   const I_CHAR * const MANAGEMENTCOMPANY       = I_( "ManagementCompany" );
   const I_CHAR * const PROFILE                 = I_( "Profile" );
   const I_CHAR * const SETTINGS                = I_( "Settings" );
   const I_CHAR * const USER                    = I_( "User" );
   const I_CHAR * const WORKSTATION             = I_( "Workstation" );
   const I_CHAR * const NONE                    = I_( "Workstation" );

   const I_CHAR * const ONSELCHANGELBSELCTION   = I_( "OnSelchangeLbSelction" );
   const I_CHAR * const FILLMANAGEMENTCOMPANIES = I_( "fillManagementCompanies" );
   const I_CHAR * const SELECTMANAGERPROFILE    = I_( "selectMangerProfile" );
   const I_CHAR * const IDI_LABEL1    = I_( "QUEUE1" );
}

namespace CND
{  // Conditions used
//CP20030319   extern CLASS_IMPORT const long GUI_ERR_AWD_PROFILE_REQUIRED;
   extern const long GUI_ERR_NOT_PROFILE;
   extern const long GUI_ERR_PROFILE_SELECTION_FAILED;
   extern const long GUI_AWD_NOT_LOGGED_ON;
   extern const long GUI_AWD_NOT_SETUP;
   extern const long GUI_MGMTCO_ERR_NO_MANAGEMENT_COMPANIES_FOUND;
   extern const long GUI_ERR_PROFILE_SELECTION_FAILED_IDI;
}



//******************************************************************************
// Public methods
//******************************************************************************

ManagementCompanyDlg::ManagementCompanyDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand )
: BaseMainDlg( ManagementCompanyDlg::IDD, pParent, pGIC, pGIParent, rCommand, CLASSNAME )
, m_LoadResource ( false )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   //{{AFX_DATA_INIT(ManagementCompanyDlg)
   //}}AFX_DATA_INIT
}

//******************************************************************************

void ManagementCompanyDlg::DoDataExchange(CDataExchange* pDX)
{
   BaseMainDlg::DoDataExchange(pDX);
   //{{AFX_DATA_MAP(ManagementCompanyDlg)
   DDX_Control(pDX, IDC_LB_SELCTION, m_Data);
   DDX_Control(pDX, IDC_LB_PROFILES, m_ProfileList);
   DDX_Control(pDX, IDC_TXT_CURRENT_PROFILE, m_CurrentProfile);
   DDX_Control(pDX, IDC_EDT_EXTENSION, m_Ext);
   DDX_Control(pDX, IDC_TXT_CURRENT, m_Current);
   //}}AFX_DATA_MAP
}

//******************************************************************************

BEGIN_MESSAGE_MAP(ManagementCompanyDlg, BaseMainDlg)
//{{AFX_MSG_MAP(ManagementCompanyDlg)
ON_LBN_DBLCLK(IDC_LB_SELCTION, OnDblclkLst)
ON_LBN_SELCHANGE(IDC_LB_SELCTION, OnSelchangeLbSelction)
ON_LBN_DBLCLK(IDC_LB_PROFILES, OnDblclkLst)
ON_LBN_SELCHANGE(IDC_LB_PROFILES, OnSelchangeLbProfiles)
ON_BN_CLICKED(IDC_BUTTON1, OnBtnDetails)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//******************************************************************************

SEVERITY ManagementCompanyDlg::doInit()
{
   TRACE_METHOD( CLASSNAME, DOINIT )

   // Need to get current selection
   m_strSelection = NULL_STRING;
   return(NO_CONDITION);
}

//******************************************************************************
// Message handlers
//******************************************************************************

void ManagementCompanyDlg::OnBtnDetails()
{
   CWaitCursor waitCursor;
   AboutPropSheet::Display();
}

void ManagementCompanyDlg::OnDblclkLst()
{
   TRACE_METHOD( CLASSNAME, DBLCLK );

   PostMessage( WM_COMMAND, IDOK );
}

//******************************************************************************

void ManagementCompanyDlg::OnSelchangeLbSelction()
{
   TRACE_METHOD( CLASSNAME, ONSELCHANGELBSELCTION );
   int ndx = m_Data.GetCurSel();

   if( ndx != LB_ERR )
   {
      CString csManagementCompanyDlg;

      m_Data.GetText( ndx, csManagementCompanyDlg );
      m_Current.SetWindowText( csManagementCompanyDlg );
   }
}

//******************************************************************************

BOOL ManagementCompanyDlg::OnInitDialog()
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, ONINITDIALOG )

   BaseMainDlg::OnInitDialog();

   //we need to get the userID here so we can display it on the dialog status bar
   //at this point the UserSessionProcess is not added into the container, yet
   DString userID;

   getParent()->getParent()->getField( this, USERID, userID );
   m_statusBar.SetSystemStatusBar( userID.c_str() );

   DString strCurrentProfile( NONE );
// DString opid;  // Decide where this resides = m_pRoadData->getElementValue( I_( "OPID" ) );

   m_pManager = ConfigManager::getManager( SessionTags::Session );
   m_bIsProfile = m_pManager->isProfileGroup();
   //m_pWorkstation = ConfigManager::getManager( I_("DefaultWorkstation") );
   m_pWorkstation = ConfigManager::getManager (WORKSTATION);
   m_workstation = m_pWorkstation->retrieveConfig( SETTINGS );
   m_pUser = ConfigManager::getManager( USER );
   m_user = m_pUser->retrieveConfig( userID );
   DString dstrCurrentManagementCompany = m_user.getValueAsString( MANAGEMENTCOMPANY );

   if( m_bIsProfile )
   {
      strCurrentProfile = m_user.getValueAsString( PROFILE );
//    strCurrentProfile = m_pManager->getCurrentProfileName();
   }
   else
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_NOT_PROFILE );
   }

   CString csManagementCompanyDlg;
   DString dsCurrentCompanyIndex;
   const DString *key = &getParent()->getFirstListItemKey( this, IFASTBP_PROC::MGMT_COMPANIES_LIST );

   if( (*key).empty() )
   {  // Failed to get management companies - not good
      DISPLAYCONDITIONFROMFILE( CND::GUI_MGMTCO_ERR_NO_MANAGEMENT_COMPANIES_FOUND );
      Exit( IDCANCEL );
      return(TRUE);
   }

   fillManagementCompanies( *key );
   getParent()->getField( this, SYSTMGMTS, dsCurrentCompanyIndex );

   long lCurrentCompanyIndex = dsCurrentCompanyIndex.convertToULong();

   m_Data.GetText( lCurrentCompanyIndex, csManagementCompanyDlg );
   m_Current.SetWindowText( csManagementCompanyDlg );
   m_CurrentProfile.SetWindowText( strCurrentProfile.c_str() );
   m_Data.SetTopIndex( lCurrentCompanyIndex );
   m_Data.SetCurSel( lCurrentCompanyIndex );
   selectManagementCompany( dstrCurrentManagementCompany );

   string_vector profilesFromXML = getProfileListFromXML();

   // Populate the profile list box if we are profile
	if( m_bIsProfile )
	{
		string_vector list;

		if (!profilesFromXML.empty())
		{
			list = profilesFromXML;
		}
		else
		{
			list = m_pManager->getProfileList();
		}

		string_vector::iterator iter = list.begin();

		int index = 0;
		while( iter != list.end() )
		{
			m_ProfileList.InsertString(index, (*iter).c_str());
			++iter;
			index++;
		}

		selectProfile( strCurrentProfile );
	}

   // Get the Extension (allow it to be 5 characters)
   m_Ext.LimitText( 5 );
   getExtension();

   return(TRUE);  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

string_vector ManagementCompanyDlg::getProfileListFromXML()
{
   string_vector list;

   ConfigManager *pDSTCMgr = ConfigManager::getManager( CONFIGURATION_CONSTANTS::MFDSTC );
   if (pDSTCMgr != NULL)
   {
	   Configuration cfgPath = pDSTCMgr->retrieveConfig( I_("Session") );

	   DString notUsingAWD = cfgPath.getValueAsString( I_("NotUse_AWD") );
	   if (!notUsingAWD.empty())
	   {
		   list.push_back(notUsingAWD);
	   }

	   DString useAWDIntegration = cfgPath.getValueAsString( I_("UseIntegration_AWD") );
	   if (!useAWDIntegration.empty())
	   {
		   list.push_back(useAWDIntegration);
	   }

	   DString useAWDPortalIntegration = cfgPath.getValueAsString( I_("UsePortalIntegration_AWD") );
	   if (!useAWDPortalIntegration.empty())
	   {
		   list.push_back(useAWDPortalIntegration);
	   }
   
	   DString callCentreIntegration = cfgPath.getValueAsString( I_("CallCentreIntegration") );
	   if (!callCentreIntegration.empty())
	   {
		   list.push_back(callCentreIntegration);
	   }
   }

   return(list);
}

//*****************************************************************************

bool ManagementCompanyDlg::PreOk()
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, PREOK )

   storeExtension();
   storeCompany();

// TODO - Currently showing conditions here, need to add conditions for
//   BaseMainDlg::OnOk to display
   // If there's an item selected, get it and pass it back
   int iSel = m_Data.GetCurSel();
   DString lastGoodProfile = m_pManager->getCurrentProfileName();

   if( -1 != iSel )
   {
      CString cstrTemp;
      m_Data.GetText( iSel, cstrTemp );
      m_strSelection = ( LPCTSTR )cstrTemp;
      ConfigValue cvManagementCompanyDlg( m_strSelection );
      m_user.set( MANAGEMENTCOMPANY, cvManagementCompanyDlg );
   }
   else
   {
      // They didn't choose one.
      m_strSelection = NULL_STRING;
   }

   // Check the current profile to see if AWD is required
   if( m_bIsProfile )
   {
      CString cstrProfile;
      iSel = m_ProfileList.GetCurSel();

      if( -1 != iSel )
      {
         m_ProfileList.GetText( iSel, cstrProfile );
         DString strProfile = LPCTSTR( cstrProfile );

         if( !selectManagerProfile( strProfile ) )
         {
            return(false);
         }
      }
      else
      {
         m_strSelection = NULL_STRING;
      }
   }

   // Make sure everything is still cool
   if( NULL_STRING != m_strSelection )
   {
      if( !m_pUser->undefined() )
      {
         m_pUser->storeConfig( m_user );
         m_pUser->persist();
      }

      Configuration awdCfg = m_pManager->retrieveConfig( SessionTags::USE_AWD );
      DString useAwd = awdCfg.getValueAsString( SessionTags::USE_AWD );

      bool bUsingAwd = ( !useAwd.empty() ) && ( useAwd[0] == 'Y' );

/*      bool bGetWork = false;  //  needs to be set !pCallGlobal->isTelTranMode();


      if ( bGetWork && !bUsingAwd )
      {  // Condition
         DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_AWD_PROFILE_REQUIRED );
         selectManagerProfile( lastGoodProfile );
         selectProfile( lastGoodProfile );
         return false;
      }
*/
      // If AWD is required - make sure they are logged onto AWD
      if( bUsingAwd )
      {
         try
         {
            bool loggedOn = BFAwdInterface::isLoggedOn();

            if( !loggedOn )
            {
               DISPLAYCONDITIONFROMFILE( CND::GUI_AWD_NOT_LOGGED_ON );
               selectManagerProfile( lastGoodProfile );
               selectProfile( lastGoodProfile );
               return(false);
            }
         }
         catch( ConditionException &ce )
         {
            if( DIAWDI_LOAD_MODULE_FAIL == ce.getCode() )
            {
               // Let the operator know and then return so another profile
               // may be selected.
               //AfxMessageBox( AWD_NOT_SETUP, MB_OK );
               DISPLAYCONDITIONFROMFILE( CND::GUI_AWD_NOT_SETUP );
               selectManagerProfile( lastGoodProfile );
               selectProfile( lastGoodProfile );
               return(false);
            }
            else
            {
               ConditionMessageBox( ce );
               Exit( IDCANCEL );
               return(false);
            }
         }
      }
   }
   SetForegroundWindow();

   int selIndex = m_ProfileList.GetCurSel();
   if( selIndex < 0 )	  {

	   DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_PROFILE_SELECTION_FAILED );
	   return(false);
   }
   else
		storeProfile();

   SetMessageStatusBar( TXT_LOAD_USER_ACCESS_LIST );
   m_LoadResource = true;
   return(true);
}

//*****************************************************************************

void ManagementCompanyDlg::PostOk (bool bOkStatus)
{
   if (bOkStatus)
   {
      E_COMMANDRETURN rtn = invokeCommand( getParent(),
                                           CMD_BPROC_PROGRESS_CTRL,
                                           getProcessType(),
                                           true,
                                           NULL);
   }
}

//******************************************************************************
// Private methods
//******************************************************************************
void ManagementCompanyDlg::fillManagementCompanies( const DString& firstKey )
{
   TRACE_METHOD( CLASSNAME, FILLMANAGEMENTCOMPANIES );

   const DString* key = &firstKey;

   m_Data.ResetContent();
   int row = 0;
   do
   {
      DString company;
      DString companyName;
      DString companyId;

      getParent()->getField( this, IFASTBP_PROC::MGMT_COMPANIES_LIST, ifds::CompanyName, companyName );
      getParent()->getField( this, IFASTBP_PROC::MGMT_COMPANIES_LIST, ifds::CompanyId, companyId );
      company = companyId.strip() + I_( "/" ) + companyName.strip();
      m_Data.AddString( company.c_str() );
      m_Data.SetItemData( row, (DWORD)key );
      row++;
   }
   while( *(key = &(getParent()->getNextListItemKey( this, IFASTBP_PROC::MGMT_COMPANIES_LIST )) ) != NULL_STRING );
}

//*****************************************************************************
//
// ^PRIVATE METHOD : ManagementCompanyDlg::getExtension()
//
// ^DESCRIPTION : Get the extension from the hard drive
//
// ^PARAMETERS  :
//      nothing
//
// ^RETURNS     :
//      normal
//
// ^THROWS      :
//
// ^EXAMPLE     :
//
//*****************************************************************************

void ManagementCompanyDlg::getExtension( void )
{
   TRACE_METHOD( CLASSNAME, GETEXTENSION );

   DString ext = m_workstation.getValueAsString( SessionTags::OperatorExtension );
   m_Ext.SetWindowText( ext.c_str() );
}

//*****************************************************************************
//
// ^PRIVATE METHOD : ManagementCompanyDlg::storeCompany()
//
// ^DESCRIPTION : Store the company
//
// ^PARAMETERS  :
//      nothing
//
// ^RETURNS     :
//      normal
//
// ^THROWS      :
//
// ^EXAMPLE     :
//
//*****************************************************************************

void ManagementCompanyDlg::storeCompany( void )
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, STORECOMP );

   int ndx = m_Data.GetCurSel();

   if( ndx != LB_ERR )
   {
      DString *key = (DString*)m_Data.GetItemData( ndx );
      DString s_ndx = DString::asString( ndx );
      DString dstMgmtCoId   = NULL_STRING;
      DString dstMgmtCoName = NULL_STRING;

//      getParent()->setField( this, SYSTMGMTS, s_ndx );
      getParent()->setCurrentListItem( this, IFASTBP_PROC::MGMT_COMPANIES_LIST, *key );
      getParent()->getField( this, IFASTBP_PROC::MGMT_COMPANIES_LIST, ifds::CompanyId, dstMgmtCoId, false );
      getParent()->setField( this, SYSTMGMTS, dstMgmtCoId.strip());


      getParent()->getField( this, IFASTBP_PROC::MGMT_COMPANIES_LIST, ifds::CompanyName, dstMgmtCoName );
      getParent()->setField( this, MGMTCONAME, dstMgmtCoName.strip() );
   }
}

//*****************************************************************************
//
// ^PRIVATE METHOD : ManagementCompanyDlg::storeExtension()
//
// ^DESCRIPTION : Store the extension
//
// ^PARAMETERS  :
//      nothing
//
// ^RETURNS     :
//      normal
//
// ^THROWS      :
//
// ^EXAMPLE     :
//
//*****************************************************************************

void ManagementCompanyDlg::storeExtension( void )
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, STOREEXT );

   CString cstrExt;

   m_Ext.GetWindowText( cstrExt );

   // TODO: Will this work?
   //assert(0);  // force us to check if this code works as expected...  CP20041110
   DString x = cstrExt;
   ConfigValue cvExt( x );

   if( !m_pWorkstation->undefined() )
   {
      m_workstation.set( SessionTags::OperatorExtension, cvExt );
      m_pWorkstation->storeConfig( m_workstation );
      m_pWorkstation->persist();
   }
// Decide where we want to store this
//   m_pRoadData->setElementValue( DD::Operator_Extension, LPCTSTR( cstrExt ), true );
}

//*****************************************************************************

void ManagementCompanyDlg::storeProfile()
{
   int selIndex = m_ProfileList.GetCurSel();

   if( selIndex >= 0 )
   {
      CString strCurrentProfile;

      m_ProfileList.GetText( selIndex, strCurrentProfile );

      DString profile( (LPCTSTR)strCurrentProfile );

      getParent()->setField( this, AWDPROFILE, profile );
   }
}

//*****************************************************************************

void ManagementCompanyDlg::OnSelchangeLbProfiles()
{
   TRACE_METHOD( CLASSNAME, ONSELCHANGELBSELCTION );
   int ndx = m_ProfileList.GetCurSel();

   if( ndx != LB_ERR )
   {
      CString strCurrentProfile;

      m_ProfileList.GetText( ndx, strCurrentProfile );
      m_CurrentProfile.SetWindowText( strCurrentProfile );
   }
}

//*****************************************************************************

bool ManagementCompanyDlg::selectManagerProfile( DString& strProfile )
{
   MAKEFRAME2( CND::IFASTGUI_CONDITION, CLASSNAME, SELECTMANAGERPROFILE )
   if(I_("Use AWD Portal Integration") == strProfile)
   {
      DString testMessage;
      bool testResults = ifsupp::testAWDConnectivity (testMessage);
      if(!testResults)
      {
//         MessageBox( HWND_DESKTOP, testMessage.c_str(), I_("Connection Error:") , MB_OK ) ;//)
         DString dstrParmMsg;
         addIDITagValue( dstrParmMsg, IDI_LABEL1, testMessage );
         DISPLAYCONDITIONFROMFILEIDI( CND::GUI_ERR_PROFILE_SELECTION_FAILED_IDI, dstrParmMsg );
         return(false);
      }

   }
   if( m_pManager->selectProfile( strProfile ) )
   {
      ConfigValue cvProfile( strProfile );
      m_user.set( PROFILE, cvProfile );
      // Decide where we want to store this
      //            m_pRoadData->setElementValue( DD::Profile, strProfile, true );
   }
   else
   {
      DISPLAYCONDITIONFROMFILE( CND::GUI_ERR_PROFILE_SELECTION_FAILED );
      return(false);
   }
   return(true);
}

//*****************************************************************************

void ManagementCompanyDlg::selectProfile( DString& strCurrentProfile )
{
   int index = m_ProfileList.FindStringExact( -1, strCurrentProfile.c_str() );

   if( LB_ERR == index )
   {
      CString cstrText;
      m_ProfileList.SetCurSel( 0 );
      if( m_ProfileList.GetCount() )
         m_ProfileList.GetText( 0, cstrText );
      if( cstrText.GetLength() > 0 )
         m_CurrentProfile.SetWindowText( cstrText );
      else
         m_CurrentProfile.SetWindowText( I_("") );
   }
   else
   {
      m_ProfileList.SetTopIndex( index );
      m_ProfileList.SetCurSel( index );
      m_CurrentProfile.SetWindowText( strCurrentProfile.c_str() );
   }
}

//*****************************************************************************

void ManagementCompanyDlg::selectManagementCompany( DString& strCurrentManagementCompany )
{
   int index = m_Data.FindStringExact( -1, strCurrentManagementCompany.c_str() );

   if( LB_ERR == index )
   {
      CString cstrText;
      m_Data.SetCurSel( 0 );
      if( m_Data.GetCount() )
         m_Data.GetText( 0, cstrText );
      if( cstrText.GetLength() > 0 )
         m_Current.SetWindowText( cstrText );
      else
         m_Current.SetWindowText( I_("") );
   }
   else
   {
      m_Data.SetTopIndex( index );
      m_Data.SetCurSel( index );
      m_Current.SetWindowText( strCurrentManagementCompany.c_str() );
   }
}

//*****************************************************************************

void ManagementCompanyDlg::PostNcDestroy()
{
   if( m_LoadResource )
   {
      DString dstMgmtCoId;
      getParent()->getField( this, IFASTBP_PROC::MGMT_COMPANIES_LIST, ifds::ClientID, dstMgmtCoId, false );
      ((MFDSTCApp*)AfxGetApp())->LoadResourceDll( dstMgmtCoId );
      ((CMainFrame*)AfxGetMainWnd())->ChangeMenu();
      ((CDSTCView*)(((CMainFrame*)AfxGetMainWnd())->GetActiveView()))->UpdateLabels();
   }
   BaseMainDlg::PostNcDestroy();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/ManagementCompanyDlg.cpp-arc  $
 * 
 *    Rev 1.28   Dec 05 2011 09:00:50   purdyech
 * ControlTextRewriter Logic
 *
 *    Rev 1.27   Mar 26 2009 09:25:40   purdyech
 * Sundry tweaks for ZTS - Rel 10
 *
 *    Rev 1.26   Feb 06 2009 14:55:24   purdyech
 * Interim CheckIn for ZTS Support (Chris is goin' on vacation!)
 *
 *    Rev 1.25   18 Jul 2008 13:55:16   popescu
 * Incident 1190617 - pop a progress control dialog to monitor the static data loading when the management company is swithced
 *
 *    Rev 1.24   Sep 15 2005 15:13:52   popescu
 * Incident#403519 - added CLASSNAME as the fifth parameter to  BaseMainDlg constructor
 *
 *    Rev 1.23   Feb 24 2005 19:10:48   popescu
 * Incident # 243353, added timer used to monitor if fund master/detail list are fully loade. Status bar message is displayed while data is loading
 *
 *    Rev 1.22   Nov 14 2004 15:00:44   purdyech
 * PET910 - .NET Conversion
 *
 *    Rev 1.21   Feb 23 2004 17:07:36   popescu
 * PTS 10027470, revert to old logic of saving the settings into the current user registry location instead of local machine
 *
 *    Rev 1.20   Dec 24 2003 13:53:52   HERNANDO
 * PET910 - Changed the storage location for Extension.  This won't impact any release.
 *
 *    Rev 1.19   Jun 18 2003 13:07:42   HERNANDO
 * Display fix.  Blank displayed for empty list.
 *
 *    Rev 1.18   May 02 2003 11:22:40   HERNANDO
 * Fixed display issue.  If registry has a value that no longer exists in the lists (Management Companies, Profiles), then default will be the first list item.
 *
 *    Rev 1.17   Mar 21 2003 18:38:40   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 *
 *    Rev 1.16   Mar 11 2003 15:09:44   popescu
 * Fixed some compilation errors in regards with teh latest base code changes
 *
 *    Rev 1.15   Oct 09 2002 23:55:46   PURDYECH
 * PVCS Database Conversion
 *
 *    Rev 1.14   Sep 30 2002 11:01:42   PURDYECH
 * BFFieldId no longer has operator long(), so explicit getId() calls are needed in places.
 *
 *    Rev 1.13   May 28 2002 12:19:52   PURDYECH
 * BFData Implementation - Phase II
 *
 *    Rev 1.12   22 May 2002 19:16:14   PURDYECH
 * BFData Implementation
 *
 *    Rev 1.11   25 Apr 2002 14:47:22   HERNANDO
 * Retain user's ManagementCompany and Profile selection in the registry.  Added function selectManagementCompany.
 *
 *    Rev 1.10   27 Mar 2002 20:01:14   PURDYECH
 * Process/WindowFactory overhaul
 *
 *    Rev 1.9   Sep 20 2001 10:58:42   HUANGSHA
 * Load resource dll based on ClientId instead of the CompanyId
 *
 *    Rev 1.8   03 Aug 2001 14:05:04   HSUCHIN
 * bug fix - fixed previous fix
 *
 *    Rev 1.7   03 Aug 2001 13:09:34   HSUCHIN
 * bug fix - Cancel no longer tries to load resource dll and crashes
 *
 *    Rev 1.6   30 Jul 2001 15:49:54   YINGZ
 * auto change of resources
 *
 *    Rev 1.5   05 Jun 2001 13:13:22   HSUCHIN
 * minor clean up
 *
 *    Rev 1.4   03 May 2001 14:07:38   SMITHDAV
 * Session management restructuring.
 *
 *    Rev 1.3   Mar 09 2001 14:40:48   ZHANGCEL
 * remove the code those are regarding with the Bank EnquiryThread
 *
 *    Rev 1.2   Sep 06 2000 14:53:40   YINGBAOL
 * make enquiring bank list at background when company changed
 *
 *    Rev 1.1   Apr 20 2000 16:38:48   BUZILA
 * changed to MgmtCoId
 *
 *    Rev 1.0   Feb 15 2000 11:01:18   SMITHDAV
 * Initial revision.
 *
 *    Rev 1.5   Nov 04 1999 13:43:22   DT24433
 * changed ok to PreOk/PostOk
 *
 *    Rev 1.4   Aug 20 1999 12:36:42   DT24433
 * changed getFieldFromCurrentListItem to getField
 *
 *    Rev 1.3   Jul 22 1999 19:02:52   POPESCUS
 * When changing companies the user access list must be refreshed
 *
 *    Rev 1.2   Jul 20 1999 11:19:08   VASILEAD
 * New conditions update
 *
 *    Rev 1.1   Jul 08 1999 10:05:28   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
