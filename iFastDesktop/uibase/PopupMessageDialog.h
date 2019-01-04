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
// ^FILE   : PopupMessageDialog.cpp
// ^AUTHOR : Kristel Weber
// ^DATE   : 7/29/97
//
// ^CLASS    : PopupMessageDialog
//
// ^DESCRIPTION : This class is for a modeless message dialog
//    (MessageBox is modal). After creating an instance of the class,
//    call the createModeless function to create the dialog. Before
//    destroying the dialog instance call the DestroyWindow method.
//
//
// ----------------------------------------------------------
//
// ^METHOD      : 	PopupMessageDialog
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
//   ^^ const char *text - message text
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
//   ^^ const char *text - new message
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

class PopupMessageDialog : public MessageDialog
{
// Construction
public:
   PopupMessageDialog(  );   // standard constructor

   BOOL createModeless(
                      const I_CHAR *text,
                      CWnd *dlg,
                      HWND hWndCtrl
                      );
   void repositionWindow(  );
   void setMessage(
                  const I_CHAR *text,
                  HWND hWndCtrl = 0
                  );

   BOOL OnEraseBkgnd(CDC* pDC);

// Implementation
protected:
   DECLARE_MESSAGE_MAP()

   private:
   int _leftOffset;
   int _topOffset;

   void setPosition( HWND hWndCtrl );
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/uibase/PopupMessageDialog.h-arc  $
 * 
 *    Rev 1.3   Oct 09 2002 17:42:54   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.2   19 Mar 2002 13:36:16   PURDYECH
 * Added #pragma once include guard
 * Removed compile time "including..." message.
 * 
 *    Rev 1.1   Feb 15 2000 18:58:58   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 11:01:00   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.1   Jul 08 1999 10:05:46   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
