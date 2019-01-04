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
// ^FILE   : MessageDialog.cpp
// ^AUTHOR : Kristel Weber
// ^DATE   : 12/16/97
//
// ^CLASS    : MessageDialog
//
// ^MEMBER VARIABLES :
//    ^^ int _height - height of message dialog
//    ^^ int _leftOffset - left offset of message dialog from parent window
//    ^^ CString m_csMessage - message text
//    ^^ int _topOffset - top offset of message dialog from parent window
//    ^^ int _width - width of message dialog
//    ^^ CWnd *_wndDlg - parent window
//
// ----------------------------------------------------------
//
//******************************************************************************

#include "stdafx.h"

#ifndef POPUPMESSAGERES_H
#define POPUPMESSAGERES_H
#include "PopupMessageRes.h"
#endif

#ifndef INCLUDED_TYPEINFO
#define INCLUDED_TYPEINFO
#include <typeinfo>
#endif

#ifndef MESSAGEDIALOG_H
   #include "MessageDialog.h"
#endif

#ifndef INCLUDED_STRING
#define INCLUDED_STRING
#include <string>
#endif

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace
{
   const int iBorderOffset = 5;
}

namespace CND
{
}
//******************************************************************************
//             PUBLIC METHODS
//******************************************************************************

BEGIN_MESSAGE_MAP(MessageDialog, CDialog)
END_MESSAGE_MAP()

//******************************************************************************

MessageDialog::MessageDialog( ) : _wndDlg( NULL )
{
}

//******************************************************************************

MessageDialog::MessageDialog( int id, CWnd *pParent ) :
CDialog( id, pParent ), _wndDlg( pParent )
{
   CWnd *wnd = findWnd( _wndDlg );

   if( wnd )
   {
      wnd->SetForegroundWindow();
   }
}

//******************************************************************************

void MessageDialog::setText( const I_CHAR *text )
{
   m_csMessage = text;
}

//******************************************************************************

int MessageDialog::DoModal()
{
   // Next 2 lines shouldn't be converted to UNICODE - don't use commonport
   // macros
   std::string object = typeid( *this ).name();
   bool errorDialog = ( "class ConditionMessageDialog" == object );

   int rc = CDialog::DoModal();
   return(rc);
}

//******************************************************************************
//             PROTECTED METHODS
//******************************************************************************

//******************************************************************************
//
// ^Protected METHOD      : MessageDialog::calcSize
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
int MessageDialog::calcSize( int maxWidth )
{
   // reformat message to replace \n
   CString csTmp;
   csTmp.Format( I_( "%s" ), (LPCTSTR)m_csMessage );
   m_csMessage = csTmp;

   // get a device context to use to calculate height in screen coordinates
   // use the text metric to calculate height of text based on font, and
   // number of words per line
   CDC* pDC = GetWindowDC();
   TEXTMETRIC tm;
   pDC->GetTextMetrics(&tm);

   // calculate height (cy) for message text field and message dialog
   int cy = tm.tmHeight + tm.tmExternalLeading;

   int last_white = -1;
   int lnstart = 0;
   CSize sz;
   int i, j;
   DString sText;
   CString curText;
   int maxWidthFound = 0;

   // process each character in the message, breaking the message into
   // lines as necessary based on width of message box; lines are split
   // at word boundaries (white space)
   // also, the message itself can contain embedded newlines ('\n')
   for( i = j = 0; i < m_csMessage.GetLength(); i++, j++ )
   {
      sText += m_csMessage.GetAt( i );

      curText = sText.substr( lnstart, j-lnstart+1 ).c_str();
      sz = pDC->GetTextExtent( curText );

      maxWidthFound = ( maxWidthFound < sz.cx ) ? sz.cx : maxWidthFound;

      if( sText.at(j) == '\n' )
      {
         lnstart = j+1;
         cy += tm.tmHeight + tm.tmExternalLeading;
      }
      else if( sz.cx > maxWidth )
      {
         if( last_white == -1 )
         {
            sText.insert( j, I_( "\n" ) );
            lnstart = ++j;
         }
         else
         {
            sText.replace( last_white, 1, I_( "\n" ) );
            lnstart = last_white + 1;
         }
         last_white = -1;
         cy += tm.tmHeight + tm.tmExternalLeading;
      }
#ifdef DST_UNICODE
      if( iswspace( sText.at(j) ) )
#else
      if( isspace( sText.at(j) ) )
#endif
      {
         last_white = j;
      }
   }
   ReleaseDC( pDC );
   cy += 2 * iBorderOffset;
   m_csMessage = sText.c_str();

   // save size and position relative to parent window
   _width = maxWidth;
   _height = cy;

   return(maxWidthFound);
}

//******************************************************************************

RECT MessageDialog::getParentRect( void )
{
   RECT rect;
   CWnd *wnd = findWnd( _wndDlg );

   if( wnd )
   {
      wnd->GetClientRect( &rect );
      wnd->ClientToScreen( &rect );
   }
   else
   {
      WINDOWPLACEMENT     wpDesktop;      // Desktops location
      GetDesktopWindow()->GetWindowPlacement( &wpDesktop );
      rect.left = wpDesktop.rcNormalPosition.left;
      rect.top = wpDesktop.rcNormalPosition.top;
      rect.right = wpDesktop.rcNormalPosition.right/2;
      rect.bottom = wpDesktop.rcNormalPosition.bottom/2;
   }
   return(rect);
}

//******************************************************************************
//  Private methods
//******************************************************************************

//******************************************************************************
//
// ^PRIVATE METHOD      : MessageDialog::findWnd
//
// ^DESCRIPTION : Returns the parent, active, or application-main window
//
// ^PARAMETERS  :
//   ^^ CWnd *dlg -
//
// ^RETURNS     : CWnd * -
//
// ^THROWS      : none
//
//******************************************************************************
CWnd *MessageDialog::findWnd( CWnd *dlg )
{
   CWnd *wnd = dlg;

   if( ! wnd )
   {
      wnd = GetActiveWindow();

      if( ! wnd )
      {
         wnd = AfxGetMainWnd();
      }
   }

   return(wnd);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/uibase/MessageDialog.cpp-arc  $
 * 
 *    Rev 1.2   Oct 09 2002 17:42:50   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.1   Sep 10 2002 14:34:40   PURDYECH
 * Base condition split out
 * 
 *    Rev 1.0   Feb 15 2000 11:01:40   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.2   Aug 13 1999 15:18:16   VASILEAD
 * Changed isspace in iswspace for DST_UNICODE defined
 * 
 *    Rev 1.1   Jul 08 1999 10:05:30   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
