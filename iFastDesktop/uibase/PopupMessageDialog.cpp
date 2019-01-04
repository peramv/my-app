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
// ^FILE   : PopupMessageDialog.cpp
// ^AUTHOR : Kristel Weber
// ^DATE   : 7/29/97
//
// ^CLASS    : PopupMessageDialog
//
// ^MEMBER VARIABLES :
//
// ----------------------------------------------------------
//
//******************************************************************************

#include "stdafx.h"

#ifndef POPUPMESSAGERES_H
#define POPUPMESSAGERES_H
#include "PopupMessageRes.h"
#endif
#include "PopupMessageDialog.h"

#include <string>

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   int iBorderOffset = 5;
}

namespace CND
{
}
//******************************************************************************
//             PUBLIC METHODS
//******************************************************************************

BEGIN_MESSAGE_MAP(PopupMessageDialog, MessageDialog)
ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

//******************************************************************************

PopupMessageDialog::PopupMessageDialog( ) : MessageDialog()
{
}

//******************************************************************************

BOOL PopupMessageDialog::createModeless(
                                       const I_CHAR *text,
                                       CWnd *dlg,
                                       HWND hWndCtrl
                                       )
{
   BOOL bRet;
   bRet = Create( IDD_POPUPMESSAGE, dlg );

   if( bRet )
   {
      m_csMessage = text;
      _wndDlg = dlg;
      setPosition( hWndCtrl );
   }

   return( bRet );
}

//******************************************************************************

void PopupMessageDialog::setMessage(
                                   const I_CHAR *text,
                                   HWND hWndCtrl
                                   )
{
   m_csMessage = text;
   setPosition( hWndCtrl );
}

//******************************************************************************

void PopupMessageDialog::repositionWindow( )
{
   RECT rectDlg;
   _wndDlg->GetWindowRect( &rectDlg );

   SetWindowPos( NULL, rectDlg.left + _leftOffset, rectDlg.top + _topOffset,
                 _width, _height, SWP_NOZORDER );
}

//******************************************************************************

BOOL PopupMessageDialog::OnEraseBkgnd(CDC* pDC)
{
   // Set brush to desired background color
   COLORREF bkcolor = RGB(255, 255, 200);

   CBrush backBrush( bkcolor );

   // Save old brush
   CBrush* pOldBrush = pDC->SelectObject(&backBrush);

   CRect rect;
   pDC->GetClipBox(&rect);     // Erase the area needed

   pDC->PatBlt(rect.left, rect.top, rect.Width(),
               rect.Height(), PATCOPY);

   pDC->SetBkColor( bkcolor );
   pDC->DrawText( m_csMessage, -1, rect, DT_LEFT | DT_TOP );

   pDC->SelectObject(pOldBrush);

   return(TRUE);
}

//******************************************************************************
//
// ^PRIVATE METHOD      : MessageDialog::setPosition
//
// ^DESCRIPTION : sets the position of the popup message dialog based
//    on either the parent window or a field control on the parent window.
//    size of the message dialog is based on the length of the message text.
//
// ^PARAMETERS  : 
//   ^^ HWND hWndCtrl - field control ID to position message dialog next to;
//       if 0, then center within parent window
//
// ^RETURNS     : none
//
// ^THROWS      : none
//
//******************************************************************************
void PopupMessageDialog::setPosition( HWND hWndCtrl )
{
   // get parent dialog screen coordinates
   RECT rectDlg = getParentRect();

   int x, y, cx;
   CWnd *wndCtrl = NULL;
   RECT rectCtrl;
   BOOL ctrlIsOnRight = FALSE;

   if( hWndCtrl )
   {
      wndCtrl = FromHandle( hWndCtrl );
   }

   // Need to calculate the width of the message dialog before
   // calculating the height (to figure out where to break the lines)

   // if there is a valid control window,
   // then position the message dialog near the field specified
   if( wndCtrl )
   {
      wndCtrl->GetWindowRect( &rectCtrl );

      // position the message dialog to line up the the left side of the field
      // if the field starts on the left half of the parent dialog - otherwise
      // position it at the 
      // the message dialog goes above the 
      // position the message dialog to the left of the field if
      // the field is on the right side of the parent dialog;
      // otherwise position message dialog to the right of the field
      // -- What if field goes across entire dialog???

      // field is on right half of parent dialog
      if( rectCtrl.left > ( rectDlg.left + (rectDlg.right - rectDlg.left)/2 ) )
      {
         x = rectDlg.left + iBorderOffset;
         cx = rectCtrl.right - x;
         ctrlIsOnRight = TRUE;
      }
      // else field is on left half of parent dialog
      else
      {
         x = rectCtrl.left;
         cx = rectDlg.right - x - iBorderOffset;
      }
   }

   // if there was no edit field control specified,
   // center message dialog within parent
   // NOTE: The top of the message dialog is centered from top, and
   //    does not take into account the height of the message dialog.
   //    The width of the message dialog is the width of the parent
   //    window minus an offset for left and right margins.
   else
   {
      x = rectDlg.left + iBorderOffset;
      cx = rectDlg.right - rectDlg.left - 2 * iBorderOffset;
      y = rectDlg.top + (rectDlg.bottom - rectDlg.top)/2 + iBorderOffset;
   }

   int maxCalcWidth = calcSize( cx );
   if( maxCalcWidth < cx )
   {
      _width = maxCalcWidth + (2 * iBorderOffset);
      if( ctrlIsOnRight )
      {
         x += (cx - maxCalcWidth) - (2 * iBorderOffset);
      }
   }

   if( wndCtrl )
   {
      y = rectCtrl.top - _height - iBorderOffset;
      if( y < rectDlg.top )
      {
         y = rectCtrl.bottom + iBorderOffset;
      }
   }

   SetWindowPos( NULL, x, y, _width, _height, SWP_NOZORDER );

   // save size and position relative to parent window
   _leftOffset = x - rectDlg.left;
   _topOffset = y - rectDlg.top;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/uibase/PopupMessageDialog.cpp-arc  $
 * 
 *    Rev 1.2   Oct 09 2002 17:42:52   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.1   Sep 10 2002 14:34:42   PURDYECH
 * Base condition split out
 * 
 *    Rev 1.0   Feb 15 2000 11:01:42   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.1   Jul 08 1999 10:05:44   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
