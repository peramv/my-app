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
// ^FILE   : DSTTimerListCtrl.cpp
// ^AUTHOR : robert Kovacs
// ^DATE   : 18/01/02
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : DSTTimerListCtrl
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#define WIN32UIBASE_DLL

#include "stdafx.h"

#include "DSTTimerListCtrl.h"

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const int TIMER_LENGTH = 200;
   const int ID_EVENT = 2;
}

namespace CND
{
}
/////////////////////////////////////////////////////////////////////////////
// DSTTimerListCtrl

BEGIN_MESSAGE_MAP(DSTTimerListCtrl, DSTListCtrl)
//{{AFX_MSG_MAP(DSTTimerListCtrl)
ON_WM_TIMER()
//}}AFX_MSG_MAP
ON_NOTIFY_REFLECT_EX(NM_DBLCLK, OnDblclkItem)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DSTTimerListCtrl message handlers

void DSTTimerListCtrl::OnTimer(UINT nIDEvent)
{
   //there might be some other timers arround...
   if( nIDEvent != ID_EVENT )
      return;

   //kill timer anyway; we don't need it anymore
   KillTimer(ID_EVENT);

   //we are guaranteed that this message was sent by the timer that we set up for m_nPreviousSelection
   //because if selection changed since m_nPreviousSelection, that timer was (hopefully) killed 
   int nCurrentSelection = GetNextSelection();//selection might changed while waiting; check the current selection
   if( nCurrentSelection>=0 && nCurrentSelection == m_nPreviousSelection )
      // the selection did not change; the waiting time passed so go ahead and handle selection
      HandleSelection( nCurrentSelection );

   stopWaitCursor();
}
//******************************************************************************

void DSTTimerListCtrl::newSelection(int iItem)
{
   startWaitCursor();
   if( m_nPreviousSelection == -1 )// first selection in list - there is no reason to wait here
   {
      m_nPreviousSelection = iItem;
      HandleSelection( iItem );
      stopWaitCursor();
   }
   else // New selected item; kill the existing timer (if any) and start up a new timer
   {
      m_nPreviousSelection = iItem;
      KillTimer(ID_EVENT);//if there is already a timer set up, it just become useless; kill it and start another
      if( !SetTimer( ID_EVENT, TIMER_LENGTH, NULL ) )
      {  // Timer failed - go ahead and handle selection
         HandleSelection( iItem );
         stopWaitCursor();
         return;
      }
   }
}
//******************************************************************************

void DSTTimerListCtrl::startWaitCursor()
{
   if( !m_bWaitCursor )
   {
      m_bWaitCursor = true;
      BeginWaitCursor( );
   }
}
//******************************************************************************
void DSTTimerListCtrl::stopWaitCursor()
{
   if( m_bWaitCursor )
   {
      EndWaitCursor();
      m_bWaitCursor = false;
   }
}

//******************************************************************************
BOOL DSTTimerListCtrl::OnDblclkItem(NMHDR* pNMHDR, LRESULT* pResult)
{
   //no need to activate timer if double clicked
   m_nPreviousSelection = -1;
   KillTimer(ID_EVENT);//if there is already a timer set up, it just become useless; kill it 

   NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
   if( pNMListView->iItem != -1 )
      newSelection(pNMListView->iItem);

   //base class functionality should be executed only after the selection has been made
   return(DSTListCtrl::OnDblclkItem(pNMHDR, pResult));
}
//******************************************************************************

void DSTTimerListCtrl::doOk()
{
   OnTimer( ID_EVENT );
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/uibase/DSTTimerListCtrl.cpp-arc  $
//
//   Rev 1.7   May 24 2003 14:59:14   PURDYECH
//Cosmetic changes.
// 
//    Rev 1.6   Jan 28 2003 16:12:56   KOVACSRO
// If no item has been selected, don't call HandleSelection (this can happen for empty lists)
// 
//    Rev 1.5   Oct 09 2002 17:42:48   PURDYECH
// New PVCS Database
// 
//    Rev 1.4   Sep 10 2002 14:34:38   PURDYECH
// Base condition split out
// 
//    Rev 1.3   Jul 16 2002 09:56:56   KOVACSRO
// Added doOk method, triggered when user hits OK button. This is necessary because in this case we need to stop the waiting process and proceed with the HandleSelection.
// 
//    Rev 1.2   21 May 2002 10:09:24   KOVACSRO
// Killing a useless timer.
// 
//    Rev 1.1   13 May 2002 12:36:50   KOVACSRO
// If an item has been double clicked, it is no need to setup a timer.
// 
//    Rev 1.0   04 Feb 2002 15:28:10   KOVACSRO
// Initial revision.
 * 
 *
 */
