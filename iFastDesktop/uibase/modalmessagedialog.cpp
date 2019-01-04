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
// ^FILE   : ModalMessageDialog.cpp
// ^AUTHOR : Kristel Weber
// ^DATE   : 7/29/97
//
// ^CLASS    : ModalMessageDialog
//
// ^MEMBER VARIABLES :
//
// ----------------------------------------------------------
//
//******************************************************************************

#include "stdafx.h"
#ifndef MODALMESSAGEDIALOG_H
   #include "ModalMessageDialog.h"
#endif

#ifndef POPUPMESSAGERES_H
#define POPUPMESSAGERES_H
#include "PopupMessageRes.h"
#endif
namespace CND
{
}

//removed for new arch
//#ifndef RESOURCE_H
//#define RESOURCE_H
//#include "resource.h"
//#endif

#ifdef _DEBUG
   #define new DEBUG_NEW
   #undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//******************************************************************************

int DoModalMessageDialog(
                        const I_CHAR *text,
                        int style
                        )
{
   ModalMessageDialog dlg( text, style );
   return(dlg.DoModal());
}

//******************************************************************************
//             PUBLIC METHODS
//******************************************************************************

BEGIN_MESSAGE_MAP(ModalMessageDialog, MessageDialog)
ON_COMMAND(ID_ACCEL_MSGDETAIL, OnAccelMsgDetail)
ON_WM_DESTROY()
END_MESSAGE_MAP()

//******************************************************************************

ModalMessageDialog::ModalMessageDialog( CWnd *pParent ) :
MessageDialog( IDD_MODALMESSAGE, pParent )
{
   HWND hwndCap = ::GetCapture( );
   if( hwndCap != NULL )
   {
      ::SendMessage( hwndCap, WM_CANCELMODE, 0, 0 );
   }
}

//******************************************************************************

ModalMessageDialog::ModalMessageDialog(
                                      const I_CHAR *text,
                                      int style,
                                      CWnd *pParent
                                      ) :
MessageDialog( IDD_MODALMESSAGE, pParent ), m_style(style)
{
   m_csMessage = text;
   HWND hwndCap = ::GetCapture( );
   if( hwndCap != NULL )
   {
      ::SendMessage( hwndCap, WM_CANCELMODE, 0, 0 );
   }
}

//******************************************************************************

void ModalMessageDialog::setStyle( int style )
{
   m_style = style;
}

//******************************************************************************

BOOL ModalMessageDialog::PreTranslateMessage(MSG* pMsg)
{
   BOOL   IsTranslated = FALSE;

   // Make sure Accelerator keys are processed properly
   if( m_hAccel != NULL )
   {
      IsTranslated = ::TranslateAccelerator( m_hWnd, m_hAccel, pMsg );
   }
   if( !IsTranslated )
   {
      // pass message down the chain
      IsTranslated = MessageDialog::PreTranslateMessage( pMsg );
   }
   return( IsTranslated );
}

//******************************************************************************

BOOL ModalMessageDialog::OnInitDialog()
{
   m_hAccel = LoadAccelerators( NULL, MAKEINTRESOURCE( IDR_ACCELMESSAGE ) );

   I_CHAR *idi;
   CString csTitle;
   CString msgType;
   csTitle.Format( AFX_IDS_APP_TITLE );

   if( m_style & MB_ICONINFORMATION )
   {
      MessageBeep( MB_ICONASTERISK );
      idi = IDI_ASTERISK;
   }
   else if( ( m_style & MB_ICONWARNING ) >> 5 )
   {
      MessageBeep( MB_ICONEXCLAMATION );
      idi = IDI_EXCLAMATION;
      //removed for new arch
      //msgType.LoadString( TXT_WARNING );
      csTitle += msgType;
   }
   else
   {
      MessageBeep( MB_ICONHAND );
      idi = IDI_HAND;
      //removed for new arch
      //msgType.LoadString( TXT_ERROR );
      csTitle += msgType;
   }
   ((CStatic *)GetDlgItem( IDC_MESSAGEICON ))->SetIcon( LoadIcon( NULL, idi ) );

   setPosition( );

   SetWindowText( csTitle );
   SetDlgItemText( IDC_MESSAGETEXT, m_csMessage );

   return(TRUE);
}

//******************************************************************************

void ModalMessageDialog::OnAccelMsgDetail()
{
}

//******************************************************************************

void ModalMessageDialog::setPosition( void )
{
   RECT rectText;
   CWnd *wndText = (GetDlgItem)(IDC_MESSAGETEXT);
   wndText->GetWindowRect(&rectText);

   RECT rectOk;
   CWnd *wndOk = GetDlgItem( IDOK );
   wndOk->GetWindowRect( &rectOk );

   RECT rectDlg = getParentRect();
   int cyDlg = rectOk.bottom - rectOk.top + 30;
   calcSize( rectDlg.right - rectDlg.left - 30 );
   cyDlg += _height;

   rectText.right = rectText.left + _width;
   rectText.bottom = rectText.top + _height;
   ScreenToClient( &rectText );
   wndText->SetWindowPos( NULL, rectText.left, rectText.top,
                          rectText.right - rectText.left, rectText.bottom - rectText.top, SWP_NOZORDER );

   ScreenToClient( &rectOk );
   int cx = rectOk.right - rectOk.left;
   int cy = rectOk.bottom - rectOk.top;
   int xOk = (rectText.right - rectText.left)/2;
   int yOk = rectText.bottom+5;
   if( (m_style & MB_OKCANCEL) )
   {
      xOk -= (cx/2 + 5);
      CWnd *wndCancel = GetDlgItem( IDCANCEL );
      wndCancel->ShowWindow( SW_SHOW );
      wndCancel->SetWindowPos( NULL, xOk+cx+5, yOk, cx, rectOk.bottom - rectOk.top, SWP_NOZORDER );
   }
   cyDlg += 30;
   wndOk->SetWindowPos( NULL, xOk, yOk, cx, cy, SWP_NOZORDER );

   SetWindowPos( NULL, rectDlg.left, rectDlg.top, rectDlg.right - rectDlg.left, cyDlg, SWP_NOZORDER );
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/uibase/modalmessagedialog.cpp-arc  $
 * 
 *    Rev 1.2   Oct 09 2002 17:42:52   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.1   Sep 10 2002 14:34:40   PURDYECH
 * Base condition split out
 * 
 *    Rev 1.0   Feb 15 2000 11:01:40   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.1   Jul 08 1999 10:05:38   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
