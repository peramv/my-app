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
//    Copyright 2002 by DST Systems, Inc.
//
//******************************************************************************

#define WIN32UIBASE_DLL

#include "stdafx.h"

#include "basedlg.h"
#include "dsttabctrl.h"
#include "dstlistctrl.h"
#include "dstgridwnd.h"

namespace CND
{
}

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DSTTabCtrl

DSTTabCtrl::DSTTabCtrl(
                      BaseDlg *rpParent,
                      const I_CHAR *dialogName,
                      UINT controlID, 
                      UINT parentControlID,
                      UINT flags
                      ) :
m_strDialogName( dialogName ),
m_parentControlID( parentControlID ),
m_flags( flags ),
m_strTabName(NULL_STRING),
m_icons( NULL ),
m_controlID( controlID )
{
   m_icons = new CImageList();
   ASSERT( m_icons != NULL );
   m_icons->Create( 16, 16, ILC_COLOR | ILC_MASK, 3, 3 );
   m_icons->Add(LoadIcon( NULL, IDI_ASTERISK ));
   m_icons->Add(LoadIcon( NULL, IDI_EXCLAMATION ));
   m_icons->Add(LoadIcon( NULL, IDI_HAND ));

   SubclassDlgItem( controlID, reinterpret_cast<CWnd *>( rpParent ) );
}
//******************************************************************************

DSTTabCtrl::~DSTTabCtrl()
{
   delete m_icons;

   PAGE_ITER pageEnd = m_pages.end();
   for( PAGE_ITER pIter = m_pages.begin(); pIter != pageEnd; pIter++ )
   {
      ( *pIter ).second->regControls.clear();
      ( *pIter ).second->regListControls.clear();
      ( *pIter ).second->regGrids.clear();
      delete ( *pIter ).second;
   }
   m_pages.clear();
}

//******************************************************************************

BEGIN_MESSAGE_MAP(DSTTabCtrl, CTabCtrl)
//{{AFX_MSG_MAP(DSTTabCtrl)
// NOTE - the ClassWizard will add and remove mapping macros here.
ON_NOTIFY_REFLECT (TCN_SELCHANGING, OnSelChanging)
ON_NOTIFY_REFLECT (TCN_SELCHANGE, OnSelChanged)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//******************************************************************************
///////////////////////////////PUBLIC methods///////////////////////////////
//******************************************************************************

void DSTTabCtrl::Init( BaseDlg *rpBD, const I_CHAR *tabCtrlName )
{
   m_rpParentDialog = rpBD;
   m_strTabName = tabCtrlName;
   SetImageList( m_icons );
}

//******************************************************************************

bool DSTTabCtrl::AddTab(const DString &tabName, int iPos /*=-1*/)
{
   bool bRet = false;

   if (getPagePos(tabName) == -1)
   {
      TC_ITEM tabItem;
      tabItem.mask = TCIF_TEXT;
//      tabItem.pszText = const_cast<const unsigned short*> (tabName.c_str());
      tabItem.pszText = const_cast<I_CHAR*> (tabName.c_str());

      if (iPos == -1)
      {
         iPos = GetItemCount();
      }
      InsertItem (iPos, &tabItem);

      PAGE_PROP* pPageProp = new PAGE_PROP;

      pPageProp->pageName = tabName;
      m_pages.insert (PAGE::value_type (tabName, pPageProp));
      bRet = true;
   }
   return bRet;
}

//******************************************************************************
bool DSTTabCtrl::AddTab(UINT tabStringId, int iPos /*=-1*/)
{
   CString strName;
   bool bRet = false;
   
   if (strName.LoadString(tabStringId))
   {
      DString dstrName(strName);
      bRet = AddTab(dstrName, iPos);
   }
   return bRet;
}

//******************************************************************************
bool DSTTabCtrl::RemoveTab (const DString &tabName)
{
   bool bRet = false;
   UINT nPos = getPagePos (tabName);
   int nSelectedPage = GetCurSel();

   if (nPos != -1 && DeleteItem (nPos))
   {
      PAGE_ITER iter = m_pages.find (tabName);
      
      assert (iter != m_pages.end());
      m_pages.erase (iter);
      bRet = true;
   }
   if (bRet)
   {
//if the selection happens to be on the same page as the page that was removed
//set the selection on first page, if exists
      if (nSelectedPage == nPos && GetItemCount() > 0)
      {
         bRet = SelectTab (getPageName (0), true); //force a selection
      }
   }
   return bRet;
}

//******************************************************************************
bool DSTTabCtrl::RemoveTab (UINT tabStringId)
{
   CString strName;
   bool bRet = false;
   
   if (strName.LoadString (tabStringId))
   {
      bRet = RemoveTab (DString (strName));
   }
   return bRet;
}

//******************************************************************************
bool DSTTabCtrl::SelectTab (const DString &tabName, bool force /*=false*/)
{
   UINT nTabPos = getPagePos (tabName);
   bool bRet = false;
   int nSelectedPage = GetCurSel();

   if (force ||
         (nTabPos != -1 && nSelectedPage != nTabPos && onSelChanging())
      )
   {
      if (force)
      {
         onSelChanging();
      }
      bRet = SetCurSel (nTabPos) != -1;
      if (force || bRet)
      {
         onSelChanged();
      }
   }
   return bRet;
}

//******************************************************************************
bool DSTTabCtrl::SelectTab (UINT tabStringId, bool force /*=false*/)
{
   CString strName;
   bool bRet = false;

   if (strName.LoadString (tabStringId))
   {
      bRet = SelectTab (DString (strName), force);
   }
   return bRet;
}

//******************************************************************************
bool DSTTabCtrl::HasTab (const DString &tabName)
{
   return getPagePos (tabName) != -1;
}

//******************************************************************************
bool DSTTabCtrl::HasTab (UINT tabStringId)
{
   CString strName;
   bool bRet = false;

   if (strName.LoadString (tabStringId))
   {
      bRet = HasTab (DString (strName));
   }
   return bRet;
}

//******************************************************************************
void DSTTabCtrl::Load(const DString &pageName)
{
   RefreshAllIcons();
   if( GetItemCount() == 0 )
      return;

   int nPage = getPagePos(pageName);
   if( nPage == -1 )//no name or wrong page name was provided
      nPage = 0;//go with the first page

   for( int i=0; i < GetItemCount(); i++ )
      if( i != nPage )
         showRegisteredControls(i, false);
   showRegisteredControls(nPage, true);

   //if current selection is different from nPage, set the correct tab selection
  if (GetCurSel() != nPage)
  {
      SetCurSel (nPage);
  }
}

//******************************************************************************
void DSTTabCtrl::Load(UINT stringID)
{
   if( stringID == 0 )
      Load();
   else
   {
      CString strName;
      if( strName.LoadString(stringID) )
      {
         DString dstrName(strName);
         Load(dstrName);
      }
   }
}

//******************************************************************************
void DSTTabCtrl::RefreshAllIcons()
{
   //remove all old icons and draw the new ones if any
   for( int i = 0; i < GetItemCount(); i++)
   {
      refreshIcon (i);
   }
}

//////////////////registering controls with a tab/////////////////////
//******************************************************************************

bool DSTTabCtrl::registerControl(UINT controlID, const DString& tabName)
{
   int nTabPos = getPagePos(tabName);
   if( nTabPos != -1 )
      return(registerControlWithPage(controlID, nTabPos));
   return(false);
}
//******************************************************************************

bool DSTTabCtrl::registerControl(UINT controlID, UINT stringID)
{
   CString str;
   if( str.LoadString(stringID) )
   {
      DString dstr(str);
      return(registerControl(controlID, dstr));
   }
   return(false);
}
//******************************************************************************

bool DSTTabCtrl::registerListControl(UINT controlID, const DString& tabName)
{
   int nTabPos = getPagePos(tabName);
   if( nTabPos != -1 )
      return(registerListControlWithPage(controlID, nTabPos));
   return(false);
}
//******************************************************************************

bool DSTTabCtrl::registerListControl(UINT controlID, UINT stringID)
{
   CString str;
   if( str.LoadString(stringID) )
   {
      DString dstr(str);
      return(registerListControl(controlID, dstr));
   }
   return(false);
}
//******************************************************************************

bool DSTTabCtrl::registerGridWnd(UINT controlID, const DString& tabName)
{
   int nTabPos = getPagePos(tabName);
   if( nTabPos != -1 )
      return(registerGridWndWithPage(controlID, nTabPos));
   return(false);
}
//******************************************************************************

bool DSTTabCtrl::registerGridWnd(UINT controlID, UINT stringID)
{
   CString str;
   if( str.LoadString(stringID) )
   {
      DString dstr(str);
      return(registerGridWnd(controlID, dstr));
   }
   return(false);
}
//////////////////removing a registered control/////////////////////
//******************************************************************************

bool DSTTabCtrl::removeControlFromPage(UINT controlID, const DString& tabName)
{
   int nTabPos = getPagePos(tabName);
   if( nTabPos != -1 )
      return(removeControlFromPageNo(controlID, nTabPos));
   return(false);
}
//******************************************************************************

bool DSTTabCtrl::removeControlFromPage(UINT controlID, UINT stringID)
{
   CString str;
   if( str.LoadString(stringID) )
   {
      DString dstr(str);
      return(removeControlFromPage(controlID, dstr));
   }
   return(false);
}
//******************************************************************************

bool DSTTabCtrl::removeListControlFromPage(UINT controlID, const DString& tabName)
{
   int nTabPos = getPagePos(tabName);
   if( nTabPos != -1 )
      return(removeListControlFromPageNo(controlID, nTabPos));
   return(false);
}
//******************************************************************************

bool DSTTabCtrl::removeListControlFromPage(UINT controlID, UINT stringID)
{
   CString str;
   if( str.LoadString(stringID) )
   {
      DString dstr(str);
      return(removeListControlFromPage(controlID, dstr));
   }
   return(false);
}
//******************************************************************************

bool DSTTabCtrl::removeGridWndFromPage(UINT controlID, const DString& tabName)
{
   int nTabPos = getPagePos(tabName);
   if( nTabPos != -1 )
      return(removeGridWndFromPageNo(controlID, nTabPos));
   return(false);
}
//******************************************************************************

bool DSTTabCtrl::removeGridWndFromPage(UINT controlID, UINT stringID)
{
   CString str;
   if( str.LoadString(stringID) )
   {
      DString dstr(str);
      return(removeGridWndFromPage(controlID, dstr));
   }
   return(false);
}
//******************************************************************************
/////////////////////////////////PRIVATE methods////////////////////////////
//******************************************************************************


//////////////////////////Handling selections///////////////////////////////////
//******************************************************************************
void DSTTabCtrl::OnSelChanging(NMHDR* pNMHDR, LRESULT* pResult)
{
   *pResult = onSelChanging() ? 0 : 1;
}

//******************************************************************************
void DSTTabCtrl::OnSelChanged(NMHDR* pNMHDR, LRESULT* pResult)
{
   onSelChanged();
   *pResult = 0;
}

//******************************************************************************
bool DSTTabCtrl::onSelChanging()
{
   bool bRet = false;
   int nSelectedPage = GetCurSel();

   if( nSelectedPage != -1 )
   {
      DString strname = getPageName(nSelectedPage);
      if( m_rpParentDialog->canTabSelChange(m_controlID, strname) )
      {
         disconnectControls(strname);
         //hide the registered controls
         showRegisteredControls(nSelectedPage, false);
         bRet = true;
      }
   }
   return bRet;
}

//******************************************************************************
void DSTTabCtrl::onSelChanged()
{
   int nSelectedPage = GetCurSel();
   DString strname = getPageName (nSelectedPage);

   connectControls (strname);
   //show the registered controls
   showRegisteredControls (nSelectedPage);
   //notify the parent dialog that tab selection has changed
   m_rpParentDialog->tabSelectionChanged(m_controlID, strname);
}

//////////////////registering controls with a tab/////////////////////
//******************************************************************************
bool DSTTabCtrl::registerControlWithPage (UINT controlID, UINT nPage)
{
   assert( nPage < GetItemCount() );
   PAGE_PROP * pProp = getPageProp(nPage);
   if( !pProp )
      return(false);

   CTRL_PROP cProp;
   cProp.bConnected = true;
   cProp.bShow =  true;
   cProp.sev = NO_SEVERITY;
   cProp.strKey = NULL_STRING;

   pProp->regControls.insert (REG_CONTROLS::value_type(controlID, cProp));
   return(true);
}

//******************************************************************************
bool DSTTabCtrl::registerListControlWithPage (UINT controlID, UINT nPage)
{
   assert( nPage < GetItemCount() );
   PAGE_PROP * pProp = getPageProp(nPage);
   if( !pProp )
      return(false);

   CTRL_PROP cProp;
   cProp.bConnected = true;
   cProp.bShow =  true;
   cProp.sev = NO_SEVERITY;
   cProp.strKey = NULL_STRING;

   pProp->regListControls.insert (REG_LIST_CONTROLS::value_type(controlID, cProp));
   return(true);
}

//******************************************************************************
bool DSTTabCtrl::registerGridWndWithPage(UINT controlID, UINT nPage)
{
   assert( nPage < GetItemCount() );
   PAGE_PROP * pProp = getPageProp(nPage);
   if( !pProp )
      return(false);

   CTRL_PROP cProp;
   cProp.bConnected = true;
   cProp.bShow = true;
   cProp.sev = NO_SEVERITY;
   cProp.strKey = NULL_STRING;

   pProp->regGrids.insert(REG_GRIDS::value_type(controlID, cProp));
   return(true);
}

//////////////////removing a registered control/////////////////////
//******************************************************************************

bool DSTTabCtrl::removeControlFromPageNo(UINT controlID, UINT nPage)
{
   bool bRet = false;
   assert( nPage < GetItemCount() );
   PAGE_PROP * pProp = getPageProp(nPage);
   if( !pProp )
      return(bRet);

   REG_CONTROLS_ITER iter = pProp->regControls.find(controlID);
   if( iter != pProp->regControls.end( ) )
   {
      pProp->regControls.erase(iter);
      bRet = true;
   }

   return(bRet);
}
//******************************************************************************

bool DSTTabCtrl::removeListControlFromPageNo(UINT controlID, UINT nPage)
{
   bool bRet = false;
   assert( nPage < GetItemCount() );
   PAGE_PROP * pProp = getPageProp(nPage);
   if( !pProp )
      return(bRet);

   REG_LIST_CONTROLS_ITER iter = pProp->regListControls.find(controlID);
   if( iter != pProp->regListControls.end() )
   {
      pProp->regListControls.erase(iter);
      bRet = true;
   }

   return(bRet);
}
//******************************************************************************

bool DSTTabCtrl::removeGridWndFromPageNo(UINT controlID, UINT nPage)
{
   bool bRet = false;
   assert( nPage < GetItemCount() );
   PAGE_PROP * pProp = getPageProp(nPage);
   if( !pProp )
      return(bRet);

   REG_GRIDS_ITER iter = pProp->regGrids.find(controlID);
   if( iter != pProp->regGrids.end() )
   {
      pProp->regGrids.erase(iter);
      bRet = true;
   }

   return(bRet);
}

////////////////////////////other private methods///////////////////////
//******************************************************************************
void DSTTabCtrl::refreshIcon (UINT nPage)
{
   PAGE_PROP *pProp = getPageProp (nPage);

   if (pProp)
   {
      int nRegContr = pProp->regControls.size();
      SEVERITY sevMax = NO_SEVERITY;

      //check base controls max severity
      REG_CONTROLS_ITER iter = pProp->regControls.begin();
      while( iter != pProp->regControls.end() )
      {
         SEVERITY sev = NO_SEVERITY;
         if( (*iter).second.bConnected )
         {
            BaseControl *pCtrl = m_rpParentDialog->GetControl((*iter).first);
            sev = pCtrl->GetErrorState();
         }
         else//for disconnected controls get the severity from PAGE_PROP
            sev = (*iter).second.sev;

         if( sev > sevMax )
            sevMax = sev;

         ++iter;
      }

      //check list controls max severity
      REG_LIST_CONTROLS_ITER listIter = pProp->regListControls.begin();
      while( listIter != pProp->regListControls.end() )
      {
         SEVERITY sev = NO_SEVERITY;
         if( (*listIter).second.bConnected )
         {
            UINT nID = (*listIter).first;
            DSTListCtrl *pCtrl = m_rpParentDialog->GetList(nID);
            sev = pCtrl->GetMaxErrorState();
         }
         else//for disconnected controls get the severity from PAGE_PROP
            sev = (*listIter).second.sev;

         if( sev > sevMax )
            sevMax = sev;

         ++listIter;
      }

      //check grid controls max severity
      REG_GRIDS_ITER iterGrid = pProp->regGrids.begin();
      while( iterGrid != pProp->regGrids.end() )
      {
         SEVERITY sev = NO_SEVERITY;
         if( (*iterGrid).second.bConnected )
         {
            UINT nID = (*iterGrid).first;
            DSTGridWnd *pCtrl = m_rpParentDialog->GetGrid(nID);
            sev = pCtrl->GetMaxErrorState();
         }
         else//for disconnected controls get the severity from PAGE_PROP
            sev = (*iterGrid).second.sev;

         if( sev > sevMax )
            sevMax = sev;

         ++iterGrid;
      }
      showIcon(nPage, sevMax);
   }
}

//******************************************************************************

DString DSTTabCtrl::getPageName(UINT nPage)
{
   PAGE_PROP* pProp = getPageProp(nPage);
   if( !pProp )
      return(NULL_STRING);

   return(pProp->pageName);
}
//******************************************************************************

void DSTTabCtrl::showRegisteredControls(UINT nPage, bool bShow)
{
   PAGE_PROP* pProp = getPageProp(nPage);
   if( !pProp )
      return;

   //base controls
   REG_CONTROLS_ITER iter = pProp->regControls.begin();
   while( iter != pProp->regControls.end() )
   {
      BaseControl *pCtrl = m_rpParentDialog->GetControl((*iter).first);
      if (pCtrl)
      {
         pCtrl->Show (bShow && (*iter).second.bShow );
      }
      ++iter;
   }
   //list controls
   REG_LIST_CONTROLS_ITER listIter = pProp->regListControls.begin();
   while( listIter != pProp->regListControls.end() )
   {
      UINT nID = (*listIter).first;
      CWnd* pWnd = m_rpParentDialog->GetDlgItem(nID);
      if( pWnd )
      {
         if( bShow )
            pWnd->ShowWindow(SW_SHOW && (*listIter).second.bShow );
         else
            pWnd->ShowWindow(SW_HIDE);
      }
      ++listIter;
   }

   //grids
   REG_GRIDS_ITER iterGrid = pProp->regGrids.begin();
   while( iterGrid != pProp->regGrids.end() )
   {
      UINT nID = (*iterGrid).first;
      CWnd* pWnd = m_rpParentDialog->GetDlgItem(nID);
      if( pWnd )
      {
         if( bShow )
            pWnd->ShowWindow(SW_SHOW);
         else
            pWnd->ShowWindow(SW_HIDE);
      }
      ++iterGrid;
   }
}

//******************************************************************************

void DSTTabCtrl::showIcon(UINT nPage, SEVERITY sevMax)
{
   TC_ITEM tabItem;

   tabItem.mask = TCIF_IMAGE;
   if( sevMax <= NO_SEVERITY )
      tabItem.iImage = -1;
   else if( sevMax == INFORMATIONAL )
      tabItem.iImage = 0;
   else if( sevMax == WARNING )
      tabItem.iImage = 1;
   else if( sevMax > WARNING )
      tabItem.iImage = 2;
   SetItem (nPage, &tabItem);
}

//******************************************************************************
DSTTabCtrl::PAGE_PROP* DSTTabCtrl::getPageProp (UINT nPageNum)
{
   assert (nPageNum < GetItemCount());
   
   TCHAR szText [255];
   TC_ITEM tabItem;
   tabItem.mask = TCIF_TEXT;
   tabItem.cchTextMax = 255;
   tabItem.pszText = szText;

   GetItem (nPageNum, &tabItem);   
   return m_pages [DString (szText)];
}

//******************************************************************************
int DSTTabCtrl::getPagePos (const DString& tabName)
{
   int nTabPos = -1;
   TCHAR szText[255];
   CString strTabName = tabName.c_str();
   TC_ITEM tabItem;
   tabItem.mask = TCIF_TEXT;
   tabItem.cchTextMax = 255;
   tabItem.pszText = szText;

   for (int i = 0; i < GetItemCount(); i++ )
   {
      GetItem (i, &tabItem);
      if (!strTabName.Compare (szText))
      {
         nTabPos = i;
         break;
      }
   }
   return nTabPos;
}

//******************************************************************************
void DSTTabCtrl::disconnectControls(const DString &strPageName)
{

   PAGE_PROP* pProp = getPageProp(strPageName);
   if( !pProp )
      return;

   //base controls
   REG_CONTROLS_ITER iter = pProp->regControls.begin();
   while( iter != pProp->regControls.end() )
   {
      UINT controlID = (*iter).first;
      BaseControl* pCtrl = m_rpParentDialog->GetControl(controlID);
      if( pCtrl->GetControlGroupID() )//only ask for controls with zero groupId
      {
         //ask the derived class if disconnect is necessary
         if( m_rpParentDialog->isDisconnectRequired(m_controlID, strPageName, controlID) )
         {
            (*iter).second.sev = pCtrl->GetErrorState();
            m_rpParentDialog->ConnectControlToData(controlID, false);
            (*iter).second.bConnected = false;
         }
      }
      ++iter;
   }

   //list controls
   REG_LIST_CONTROLS_ITER listIter = pProp->regListControls.begin();
   while( listIter != pProp->regListControls.end() )
   {
      UINT controlID = (*listIter).first;
      //ask the derived class if disconnect is necessary
      if( m_rpParentDialog->isDisconnectRequired(m_controlID, strPageName, controlID) )
      {
         //save current selection
         DSTListCtrl *pCtrl = m_rpParentDialog->GetList(controlID);
         DString strKey = pCtrl->GetCurrentKey();
         (*listIter).second.strKey = strKey;
         (*listIter).second.sev = pCtrl->GetMaxErrorState();
         m_rpParentDialog->ConnectListToData(controlID, false);
         (*listIter).second.bConnected = false;
      }
      ++listIter;
   }

   //grids 
   //TO DO (need to provide methods in Grid such as ConnectGrid)

}
//******************************************************************************

void DSTTabCtrl::connectControls(const DString &strPageName)
{
   //ask the derived class if connect is necessary
   //m_rpParentDialog->isConnectRequired(m_controlID, strPageName, controlID);
   PAGE_PROP* pProp = getPageProp(strPageName);
   if( !pProp )
      return;

   REG_CONTROLS_ITER iter = pProp->regControls.begin();
   while( iter != pProp->regControls.end() )
   {
      UINT controlID = (*iter).first;
      BaseControl* pCtrl = m_rpParentDialog->GetControl(controlID);
      if( pCtrl->GetControlGroupID() )//only ask for controls with zero groupId
      {
         //ask the derived class if connect is necessary
         if( m_rpParentDialog->isConnectRequired(m_controlID, strPageName, controlID) )
         {
            m_rpParentDialog->reInitControl(m_controlID, strPageName, controlID);
            m_rpParentDialog->ConnectControlToData(controlID, true);
            m_rpParentDialog->LoadControl(controlID);
            (*iter).second.bConnected = true;
            (*iter).second.sev = NO_SEVERITY;
         }
      }
      ++iter;
   }

   //list controls
   REG_LIST_CONTROLS_ITER listIter = pProp->regListControls.begin();
   while( listIter != pProp->regListControls.end() )
   {
      UINT controlID = (*listIter).first;
      //ask the derived class if disconnect is necessary
      if( m_rpParentDialog->isConnectRequired(m_controlID, strPageName, controlID) )
      {
         //give a chance to derived class to reInit the List control, if necessary
         m_rpParentDialog->reInitControl(m_controlID, strPageName, controlID);
         //get the previous selection
         DString strKey = (*listIter).second.strKey;
         m_rpParentDialog->ConnectListToData(controlID, true);
         (*listIter).second.bConnected = true;
         (*listIter).second.sev = NO_SEVERITY;
         m_rpParentDialog->LoadListControl(controlID, &strKey);
      }
      ++listIter;
   }

   //grids 
   //TO DO (need to provide methods in Grid such as ConnectGrid)
}

//*****************************************************************************
void DSTTabCtrl::showTabControl( UINT controlID,UINT nPage, bool bShow  )
{
   assert( nPage < GetItemCount() );
   PAGE_PROP * pProp = getPageProp(nPage);
   if( !pProp )
      return;

   REG_CONTROLS_ITER iter = pProp->regControls.begin();
   while( iter != pProp->regControls.end() )
   {
      if( (*iter).first == controlID )
      {
         (*iter).second.bShow = bShow;
         BaseControl* pCtrl = m_rpParentDialog->GetControl(controlID);
         pCtrl->Show( bShow );
         return;
      }   
      ++iter;
   }   
  //list controls
   REG_LIST_CONTROLS_ITER listIter = pProp->regListControls.begin();
   while( listIter != pProp->regListControls.end() )
   {
      if( (*listIter).first == controlID )
      {
         (*listIter).second.bShow = bShow;
         DSTListCtrl* pCtrl = m_rpParentDialog->GetList( controlID );
         pCtrl->Show( bShow );
         return;
      }   
      ++listIter;
   }
   //grids
   // To be down in the future
}

//******************************************************************************

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/uibase/DSTTabCtrl.cpp-arc  $
//
//   Rev 1.5   Mar 10 2005 17:02:08   yingbaol
//PET1171,FN01: EU Saving, add dynamic show/hide page control functionality.
//
//   Rev 1.4   Oct 27 2004 12:04:02   popescu
//PET 1117/06, added new method 'HasTab'
//
//   Rev 1.3   Oct 14 2004 10:33:00   popescu
//PET 1117/06, SSB Germany, fixed the page removal from tab controls
//
//   Rev 1.2   Mar 25 2004 13:53:34   popescu
//PET 1027, FN02, high risk entities, fix tab control issues related to validation of the controls attached to a page, and hide/display the error icon on the tab when focus is lost on a control; also add method to set the selection programatically.
// 
//    Rev 1.1   Oct 09 2002 17:42:48   PURDYECH
// New PVCS Database
// 
//    Rev 1.0   Oct 07 2002 14:30:34   KOVACSRO
// Initial revision.
 * 
 */
