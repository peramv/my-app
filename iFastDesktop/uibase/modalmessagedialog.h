#pragma once


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
// ^DATE   : 12/16/97
//
// ^CLASS    : ModalMessageDialog
//
// ^DESCRIPTION : This class is for a modeless message dialog
//    (MessageBox is modal). After creating an instance of the class,
//    call the createModeless function to create the dialog. Before
//    destroying the dialog instance call the DestroyWindow method.
//
//
// ----------------------------------------------------------
//
// ^METHOD      :    ModalMessageDialog
//
// ^DESCRIPTION : constructor
//
// ^PARAMETERS  : none
//
// ^RETURNS     : none
//
// ^THROWS      : none
//
// ----------------------------------------------------------
//
// ^METHOD      : createModeless
//
// ^DESCRIPTION : create and display the message dialog
//
// ^PARAMETERS  :
//   ^^ const I_CHAR *text - message text
//   ^^ CWnd *dlg - parent dialog
//   ^^ HWND hWndCtrl - field control ID to position message next to
//
// ^RETURNS     : BOOL - TRUE if created ok
//
// ^THROWS      : none
//
// ----------------------------------------------------------
//
// ^METHOD      : repositionWindow
//
// ^DESCRIPTION : repositions the message dialog window - position relative
//    calling dialog is maintained
//
// ^PARAMETERS  : none
//
// ^RETURNS     : none
//
// ^THROWS      : none
//
// ----------------------------------------------------------
//
// ^METHOD      : setMessage
//
// ^DESCRIPTION : set the text of the message to display, and display it
//
// ^PARAMETERS  :
//   ^^ const I_CHAR *text - new message
//   ^^ HWND hWndCtrl - field control id to position message next to,
//       Defaults to 0.
//
// ^RETURNS     : none
//
// ^THROWS      : none
//
// ----------------------------------------------------------
//
//******************************************************************************

#ifndef COMMONPORT_H
   #include <commonport.h>
#endif

#ifndef MESSAGEDIALOG_H
   #include <uibase\MessageDialog.h>
#endif

int DoModalMessageDialog( const I_CHAR *text, int style );

class ModalMessageDialog : public MessageDialog
{
// Construction
public:
   ModalMessageDialog( const I_CHAR *text,
                       int style,
                       CWnd *pParent=NULL );
   ModalMessageDialog( CWnd *pParent=NULL );

   void setStyle( int style );

// Implementation
protected:
   BOOL PreTranslateMessage(MSG* pMsg);
   BOOL OnInitDialog();
   virtual afx_msg void OnAccelMsgDetail();
   DECLARE_MESSAGE_MAP()

   private:
   HACCEL m_hAccel;
   int m_style;
   void setPosition( );
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/uibase/modalmessagedialog.h-arc  $
 * 
 *    Rev 1.3   Nov 27 2002 15:07:22   PURDYECH
 * Documentation Changes
 * 
 *    Rev 1.2   Oct 09 2002 17:42:52   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.1   19 Mar 2002 13:36:18   PURDYECH
 * Added #pragma once include guard
 * Removed compile time "including..." message.
 * 
 *    Rev 1.0   Feb 15 2000 11:01:00   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.1   Jul 08 1999 10:05:40   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */

