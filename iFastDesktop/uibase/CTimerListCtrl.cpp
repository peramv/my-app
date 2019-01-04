// CTimerListCtrl.cpp : implementation file
//

#define WIN32UIBASE_DLL

#include "stdafx.h"

#ifndef CTIMERLISTCTRL_H
   #include "CTimerListCtrl.h"
#endif

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const int TIMER_LENGTH = 400;
}

namespace CND
{
}
/////////////////////////////////////////////////////////////////////////////
// CTimerListCtrl

BEGIN_MESSAGE_MAP(CTimerListCtrl, ListViewControl)
//{{AFX_MSG_MAP(CTimerListCtrl)
ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, OnItemchanged)
ON_WM_TIMER()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTimerListCtrl message handlers

void CTimerListCtrl::OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult)
{
   NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

   if( LVN_SELECTED )
   {
      // If first time any item selected, then immediately post Item
      // changed message to parent
      if( CurrentSelection == -1 )
      {
         CurrentSelection = pNMListView->iItem;
         CWnd *ParentWindow = GetParent();
         ListIdentifier = GetDlgCtrlID();
         ParentWindow->PostMessage( WM_VIEWITEMSELECTED, 
                                    (WPARAM)CurrentSelection,
                                    (LPARAM)ListIdentifier );
         ChangeCounter = 0;
      }
      else // New selected item, check if need to start up delay timer
      {
         CurrentSelection = pNMListView->iItem;
         // Only start delay timer if not already going
         if( !ChangeCounter )
         {
            if( SetTimer( 1, TIMER_LENGTH, NULL ) == 0 )
            {  // Timer failed - go ahead and Post changed message to parent
               CWnd *ParentWindow = GetParent();
               ListIdentifier = GetDlgCtrlID();
               ParentWindow->PostMessage( WM_VIEWITEMSELECTED, 
                                          (WPARAM)CurrentSelection,
                                          (LPARAM)ListIdentifier );
               *pResult = 0;
               return;
            }
         }
         ChangeCounter ++;
      }
   }
   *pResult = 0;
}

void CTimerListCtrl::OnTimer(UINT nIDEvent)
{
   if( ChangeCounter > 1 )
   {
      ChangeCounter = 1;
      if( SetTimer( 1, TIMER_LENGTH, NULL ) == 0 )
      {  // Timer failed - go ahead and Post changed message to parent dialog
         CWnd *ParentWindow = GetParent();
         ListIdentifier = GetDlgCtrlID();
         ParentWindow->PostMessage( WM_VIEWITEMSELECTED,
                                    (WPARAM)CurrentSelection, (LPARAM)ListIdentifier );
         ChangeCounter = 0;
      }
   }
   else
   {
      if( 1 == ChangeCounter )
      {  // Post Item changed message to parent dialog
         CWnd *ParentWindow = GetParent();
         ListIdentifier = GetDlgCtrlID();
         ParentWindow->PostMessage( WM_VIEWITEMSELECTED,
                                    (WPARAM)CurrentSelection, (LPARAM)ListIdentifier );
         ChangeCounter = 0;
      }
   }

}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/uibase/CTimerListCtrl.cpp-arc  $
 * 
 *    Rev 1.2   Oct 09 2002 17:42:38   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.1   Sep 10 2002 14:34:26   PURDYECH
 * Base condition split out
 * 
 *    Rev 1.0   Feb 15 2000 11:01:38   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.1   Jul 08 1999 10:04:54   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
