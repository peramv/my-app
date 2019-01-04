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
//    Copyright 1997 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : MainFrm.cpp
// ^AUTHOR : UnKnown
// ^DATE   : 11-96
//
// ----------------------------------------------------------
//
// ^CLASS    : CMainFrame
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"

#ifndef IFASTGUI_H
   #include "MFDSTC.h"
#endif

#ifndef MAINFRM_H
   #include "MainFrm.h"
#endif

#ifndef ABOUTDLG_H
   #include "AboutDlg.h"
#endif

#ifndef CONFIGMANAGER_HPP
   #include <ConfigManager.hpp>
#endif

#ifndef DSTCUSERSESSION_HPP
   #include <ifastcbo\DSTCUserSession.hpp>
#endif

#include <ifastcbo\dstcommonfunction.hpp>

#ifndef DSTCHOST_HPP
   #include <ifastdbrkr\DSTCHost.hpp>
#endif

#ifndef INCLUDED_DIRECT_H
#define INCLUDED_DIRECT_H
#include <direct.h>
#endif

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifndef DSTCVIEW_H
   #include "DstcView.h"
#endif


namespace
{  
   const I_CHAR *AWD_COMMMENTS      = I_( "AWD/Comments" );
   const I_CHAR *AWD_COMMMENTS_KEY  = I_( "COMMENTS" );
   const I_CHAR *FORMS_MENU         = I_( "&AWD/Forms" );
   const I_CHAR *FORMS              = I_( "Forms" );
   const I_CHAR *FORMS_KEY          = I_( "FORM" );
   const I_CHAR *ENCORR_MENU        = I_( "&EnCorr" );
   const I_CHAR *ENCORR             = I_( "EnCorr" );
   const I_CHAR *ENCORR_KEY         = I_( "ENCORR" );
   const I_CHAR *MGMCO_MENU         = I_( "&Mgmt Co" );
   const I_CHAR *MGMCO_KEY          = I_( "SYSTEM" );
   const I_CHAR *AWD_HISTORY        = I_( "A&WD History" );
   const I_CHAR *AWD_HISTORY_KEY    = I_( "AWDHISTORY" );

   const I_CHAR *CALLTRACKER     = I_( "&CallTracker" );
   const I_CHAR *LITERATURE      = I_( "L&iterature" );
   const I_CHAR *COUNT           = I_( "COUNT" );
   const I_CHAR *EVENT            = I_( "_EVENT" );
   const int MENU_SETTINGS        = 0;
   const int MENU_APPLICATION     = 1;
   const int MENU_SYSTEM          = 2;
   const UINT FIRST_DYNAMIC_MENU_ID = 0xE001;
}
namespace SessionTags
{
   extern const I_CHAR *SESSION;
}
/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
//{{AFX_MSG_MAP(CMainFrame)
ON_COMMAND(IDM_ABOUT, OnAbout)
ON_WM_CREATE()
//}}AFX_MSG_MAP
ON_WM_CLOSE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame() :
m_nNextMenuID( 0 )
{
}

//******************************************************************************
CMainFrame::~CMainFrame()
{
}

//******************************************************************************
BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
   // Change the style bits so we won't attempt to add anything to the title
   cs.style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;

   return(CFrameWnd::PreCreateWindow(cs));
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
//******************************************************************************
void CMainFrame::AssertValid() const
{
   CFrameWnd::AssertValid();
}

//******************************************************************************
void CMainFrame::Dump(CDumpContext& dc) const
{
   CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

//******************************************************************************
void CMainFrame::OnAbout()
{
   AboutDlg aboutDlg;
   aboutDlg.DoModal();
}

//******************************************************************************
void CMainFrame::setAwdActive( BOOL active )
{
   CMenu *pMenu = GetMenu();   
   if ( NULL != pMenu )
   {
      if ( pMenu->GetMenuItemCount() >= 1 )
      {        
         CMenu *pAppMenu = new CMenu();                     
         
         if ( NULL != pAppMenu &&
              pAppMenu->CreatePopupMenu() )
         {
            // Remove existing AWD Menu if it exists
            CString str;
            int count = pMenu->GetMenuItemCount();
            for (int i = 0; i < count; i++)
            {
               if (pMenu->GetMenuString( i, str, MF_BYPOSITION) && (str == "AWD"))
               {
                  pMenu->RemoveMenu( i, MF_BYPOSITION );
                  break;
               }
            }

            UINT d = pMenu->GetMenuItemCount(); 

            // Add AWD Menu
            if( active )
            {
               // Insert the AWD Menu as a second last item (right before Help)
               pMenu->InsertMenu( d - 1, 
                                 MF_BYPOSITION | MF_POPUP, 
                                 (UINT)pAppMenu->m_hMenu, 
                                 _T( "AWD" ) );                       

               // Add AWD Comments option          
               DynamicMenuItem dmiAWDComments;
               dmiAWDComments.mt      = AwdComments;
               dmiAWDComments.id      = IDM_AWDCOMMENTS;
               dmiAWDComments.strName = AWD_COMMMENTS;
               dmiAWDComments.strID   = AWD_COMMMENTS_KEY;                                      
               pAppMenu->AppendMenu( MF_ENABLED, dmiAWDComments.id, dmiAWDComments.strName.c_str() );

               // Append the Forms and EnCorr menu    
               appendSubMenu( pAppMenu, FORMS_MENU,  FORMS,  FORMS_KEY,  IDM_FORMS,  Forms );
               appendSubMenu( pAppMenu, ENCORR_MENU, ENCORR, ENCORR_KEY, IDM_ENCORR, EnCorr );

               // Add AWD History option
               DynamicMenuItem dmi;
               dmi.mt      = AwdHistory;
               dmi.id      = IDM_AWD;
               dmi.strName = AWD_HISTORY;
               dmi.strID   = AWD_HISTORY_KEY;
               pAppMenu->AppendMenu( MF_ENABLED, dmi.id, dmi.strName.c_str() );              
            }

            pAppMenu->Detach();

            delete pAppMenu;
            DrawMenuBar();
         }
      }
   }
}

//******************************************************************************
void CMainFrame::setMgmCo( const DSTCUserSession *dstUserSession )
{
   CMenu *pMenu = GetMenu();
   CMenu *popMenu = new CMenu();
   popMenu->CreatePopupMenu();

   DynamicMenuItem dmi;

   DString dstCompanyId( NULL_STRING );
   DString dstCompanyName( NULL_STRING );

   // Add Companies to Dynamic Menu
   unsigned long iNumCo = dstUserSession->getNumberOfCompanies( DSTCHost::getPrimaryHost() );
   for( unsigned long i=0; i < iNumCo; i++ )
   {
      dstUserSession->getCompanyInfo( DSTCHost::getPrimaryHost(), i, dstCompanyId, dstCompanyName );
      appendDynamicMenuItem (popMenu, System, dstCompanyName, dstCompanyId);
   }

   CString cstrText;
   cstrText.LoadString( TXT_MGMCO_MENU );
   pMenu->InsertMenu(MENU_SYSTEM,MF_BYPOSITION|MF_POPUP,(UINT)popMenu->m_hMenu, cstrText );

   popMenu->Detach();

   delete popMenu;
   DrawMenuBar();
}

//******************************************************************************
void CMainFrame::setCallTrackerActive( BOOL active )
{
//   set(active, IDM_CALLTRACKER, CALLTRACKER);
}

//******************************************************************************
void CMainFrame::setLiteratureActive( BOOL active )
{
//   set(active, IDM_LITERATURE, LITERATURE);
}

//******************************************************************************
void CMainFrame::set (BOOL active, UINT nMenuID, const I_CHAR *pcchMenu)
{
   CMenu *pMenu = GetMenu();
   CMenu *pSubMenu = pMenu->GetSubMenu( 1 );

   UINT status = pSubMenu->GetMenuState(  nMenuID, MF_BYCOMMAND );

   bool bPresent = ( -1 < status );

   if( active )
   {
      if( ! bPresent )
      {
         pSubMenu->AppendMenu( MF_ENABLED, nMenuID, pcchMenu );
      }
   }
   else
   {
      if( bPresent )
      {
         pSubMenu->RemoveMenu( nMenuID, MF_BYCOMMAND );
      }
   }
}

//******************************************************************************
void CMainFrame::appendSubMenu( CMenu *pMenu,
                                const I_CHAR *pcchMenu,
                                const I_CHAR *pcchItem,
                                const I_CHAR *pcchKey,
                                UINT nMenuID,
                                MenuType mt )
{
   CMenu mSub;
   mSub.CreatePopupMenu();
   mSub.AppendMenu( MF_ENABLED, nMenuID, pcchItem );

   DString strTable = pcchItem;
   strTable += I_( " Table" );

   ConfigManager *pMgr = ConfigManager::getManager( SessionTags::SESSION );
   Configuration cfgTable = pMgr->retrieveConfig( strTable );
   int count = cfgTable.getValueAsInt( COUNT );

   if( count )
   {
      CString cstrKey;
      DString strKey;
      DString strDesc;
      DString strID;

      for( int index = 1; index <= count; ++index )
      {
         cstrKey.Format( I_( "%s_%02d" ), pcchKey, index );
         strKey = LPCTSTR( cstrKey );
         strDesc = cfgTable.getValueAsString( strKey );

         if( ! strDesc.empty() )
         {
            strKey += EVENT;
            appendDynamicMenuItem( &mSub, mt, strDesc, strKey );
         }
      }
   }

   pMenu->AppendMenu( MF_POPUP, (UINT)mSub.m_hMenu, pcchMenu );
   mSub.Detach();
}


//******************************************************************************
//
// ^PRIVATE METHOD      : CMainFrame::appendDynamicMenuItem
//
// ^DESCRIPTION : appends a menu item using the highest
//
// ^PARAMETERS  :
//   ^^ CMenu *pMenu -
//   ^^ MenuType mt -
//   ^^ const string &strName -
//   ^^ const string &strID -
//
// ^RETURNS     : void -
//
// ^THROWS      : < description of all possible thrown exceptions >
//
// ^EXAMPLE     : < if the use of this member is not obvious,
//                  give an example >
//
//******************************************************************************
void CMainFrame::appendDynamicMenuItem( CMenu *pMenu,
                                        MenuType mt,
                                        const DString &strName,
                                        const DString &strID )
{
   DynamicMenuItem dmi;

   dmi.mt      = mt;
   dmi.id      = m_nNextMenuID++;
   dmi.strName = strName;
   dmi.strID   = strID;

   m_ivList.push_back( dmi );

   pMenu->AppendMenu( MF_ENABLED, dmi.id, dmi.strName.c_str() );
}


//******************************************************************************
CMainFrame::MenuType CMainFrame::findDynamicMenuItem( UINT nID, DString &strID )
{
   MenuType mt = Undefined;

   // First make sure the ID is in our range before looking for it
   if( FIRST_DYNAMIC_MENU_ID <= nID && nID < m_nNextMenuID )
   {
      const DynamicMenuItem &dmi = m_ivList[nID - FIRST_DYNAMIC_MENU_ID];

      mt = dmi.mt;
      strID = dmi.strID;
   }

   return(mt);
}

//******************************************************************************
void CMainFrame::resetDynamicMenuList()
{
   CMenu *pMenu = GetMenu();   
   if ( NULL != pMenu )
   {
      deleteMenuItem( pMenu, MGMCO_MENU );

      UINT d = pMenu->GetMenuItemCount();       
      if ( -1 != d )
      {  
         CMenu *pAppMenu = pMenu->GetSubMenu( d - 2 );
         if ( NULL != pAppMenu )
         {
            // Remove dynamic menu items  
            deleteMenuItem( pAppMenu, AWD_COMMMENTS );
            deleteMenuItem( pAppMenu, FORMS_MENU );
            deleteMenuItem( pAppMenu, ENCORR_MENU );           
            deleteMenuItem( pAppMenu, AWD_HISTORY );
         }
      }
   }
   
   int count = m_ivList.size();
   //what is this doing???
   for( int index = 0; index < count; ++index )
   {
      DynamicMenuItem &dmi = m_ivList[ index ];
   }

   // Clear out the menu list
   m_ivList.erase( m_ivList.begin(), m_ivList.end() );

   // Rest the next menu ID - this number should be sufficiently high
   m_nNextMenuID = FIRST_DYNAMIC_MENU_ID;
   DrawMenuBar(); 
}

//******************************************************************************
void CMainFrame::deleteMenuItem( CMenu *pMenu, const CString &cstrItem )
{
   int pos = findPosition( pMenu, cstrItem );

   if( 0 <= pos )
   {
      pMenu->DeleteMenu( pos, MF_BYPOSITION );
   }
}

//******************************************************************************
int CMainFrame::findPosition( CMenu *pMenu, const CString &cstrItem )
{
   CString cstrText;
   int pos = -1;
   int index = 0;
   int count = pMenu->GetMenuItemCount();

   while( index < count )
   {
      pMenu->GetMenuString( index, cstrText, MF_BYPOSITION );

      if( cstrItem == cstrText )
      {
         pos = index;
         break;
      }

      ++index;
   }

   return(pos);
}

//******************************************************************************
void CMainFrame::ChangeMenu()
{
   CMenu newMenu;
   newMenu.LoadMenu(IDR_MAINFRAME);
   SetMenu(&newMenu);
   newMenu.Detach();
}

//******************************************************************************
void CMainFrame::CheckMenuItem(DString item)
{
   CMenu *pMenu = GetMenu();
   int count = m_ivList.size();
   for( int index = 0; index < count; ++index )
   {
      DynamicMenuItem &dmi = m_ivList[ index ];
      if( dmi.strName.compare(item.c_str()) == 0 )
      {
         pMenu->CheckMenuItem(dmi.id, MF_BYPOSITION);
         return;
      }
   }
}


//******************************************************************************
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
   SetIcon( ::getUserIcon(), TRUE );
   SetIcon( ::getUserIcon(), FALSE );

   if ( -1 == CFrameWnd::OnCreate(lpCreateStruct) )
   {
      return -1;
   }

   // other initializations can go here

   return(0);
}

//******************************************************************************

void CMainFrame::OnClose()
{
	if( !( (CDSTCView*)GetActiveView() )->displayActiveBatches() )
	{
		CFrameWnd::OnClose();
	}
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/MainFrm.cpp-arc  $
 * 
 *    Rev 1.16   26 Sep 2007 17:00:48   kovacsro
 * IN#1015356 - added OnClose (don't allow users to log off if there are active batches)
 * 
 *    Rev 1.15   Jan 31 2005 15:30:16   hernando
 * PTS10038017 - Fixed 'AWD' inclusion on the menu bar.  'AWD' will only be added if AWD is an active profile.
 * 
 *    Rev 1.14   Dec 24 2004 12:00:28   purdyech
 * PTS1031333 - getUserIcon() function is now a global function which happens to reside in MFDSTC.cpp, instead of a member of MFDSTCApp.  Also, added ON_WM_CREATE() so that CMainFrame::OnCreate() would be called, and fleshed out CMainFrame::OnCreate().
 * 
 *    Rev 1.13   Dec 22 2004 16:56:38   zhangcel
 * PTS 10031333 -- Added a new function onCreate()
 * 
 *    Rev 1.12   May 06 2004 16:19:06   VADEANUM
 * PET 1017 - AWD Comments - moved AWD Froms/EnCorra to AWD and added AWDComments - work in progress.
 * 
 *    Rev 1.11   Oct 09 2002 23:55:46   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.10   Nov 26 2001 15:02:08   HERNANDO
 * Removed OnHelp().
 * 
 *    Rev 1.9   Nov 19 2001 18:37:54   HERNANDO
 * Data type changes.
 * 
 *    Rev 1.8   Nov 19 2001 16:39:36   HERNANDO
 * Implemented OnHelp with help.chm (Compiled HTML) in data directory.
 * 
 *    Rev 1.7   Sep 21 2001 16:14:58   YINGBAOL
 * fix memory leak
 * 
 *    Rev 1.6   Jun 12 2001 11:14:28   DINACORN
 * Sync. up with SSB (1.4.1.0)
 * 
 *    Rev 1.5   03 May 2001 14:07:36   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.4   Oct 25 2000 14:51:00   HERNANDO
 * Recovered - dynamically create companies in setMgmCo process
 * 
 *    Rev 1.3   Oct 19 2000 18:17:42   HERNANDO
 * Bug fix; added use of AwdHistory menu type.
 * 
 *    Rev 1.2   Oct 06 2000 17:46:40   HERNANDO
 * Added AWD History menu item.
 * 
 *    Rev 1.1   Apr 20 2000 16:38:48   BUZILA
 * changed to MgmtCoId
 * 
 *    Rev 1.0   Feb 15 2000 11:01:18   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.3   15 Dec 1999 11:11:24   HSUCHIN
 * added dynamic menu for change of management company
 * 
 *    Rev 1.2   Jul 13 1999 18:00:00   POPESCUS
 * Fixed assertion in logon screen when F1 is hit
 * 
 *    Rev 1.1   Jul 08 1999 10:05:26   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
