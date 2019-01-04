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
//    Copyright 1997-1998 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : AboutDlg.h
// ^AUTHOR : Terry Erickson
// ^DATE   : 3/31/98
//
// ^CLASS    : AboutDlg
// ^SUBCLASS PARENT : CDialog
//
// ^CLASS DESCRIPTION : Displays the AboutBox
//
// -----------------------------------------------------------------------------
//                PUBLIC MEMBER FUNCTIONS
// -----------------------------------------------------------------------------
//
// ^METHOD      : AboutDlg
//
// ^DESCRIPTION : constructor
//
// ^PARAMETERS  :
//    ^^ CWnd *pParent - Parent window, defaults to NULL
//
// ^RETURNS     : none
//
// ^THROWS      :
//
// ^SEE ALSO    :
//
// ^EXAMPLE     :
//
// -----------------------------------------------------------------------------
//
// ^METHOD      : GetModuleVersion
//
// ^DESCRIPTION : Gets the version information for a module
//
// ^PARAMETERS  :
//    ^^ HINSTANCE inst - Module instance
//
// ^RETURNS     :
//    ^^ CString - The version number as a string
//
// ^THROWS      :
//
// ^SEE ALSO    :
//
// ^EXAMPLE     :
//
// -----------------------------------------------------------------------------
//               PROTECTED MEMBER FUNCTIONS
// -----------------------------------------------------------------------------
//
// ^METHOD      : OnInitDialog
//
// ^DESCRIPTION : Initializes the dialog
//
// ^PARAMETERS  : none
//
// ^RETURNS     :
//    ^^ BOOL - If initialization succeeds
//
// ^THROWS      :
//
// ^SEE ALSO    :
//
// ^EXAMPLE     :
//
// -----------------------------------------------------------------------------
//
//******************************************************************************

#include "stdafx.h"

/////////////////////////////////////////////////////////////////////////////
// AboutDlg dialog
class AboutDlg : public CDialog
{
// Construction
public:
   AboutDlg(CWnd* pParent = NULL);   // standard constructor

//CP20030815   CString GetModuleVersion( HINSTANCE inst );

// Dialog Data
   //{{AFX_DATA(AboutDlg)
   enum
   {
      IDD = IDD_ABOUTBOXDST
   };
   //}}AFX_DATA

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(AboutDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(AboutDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnDetails();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/AboutDlg.h-arc  $
 * 
 *    Rev 1.3   Sep 23 2003 08:25:36   PURDYECH
 * Use ifds::getAppVersion to display version string.
 * 
 *    Rev 1.2   Oct 09 2002 23:55:26   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.1   19 Mar 2002 13:44:18   PURDYECH
 * Added #pragma once include guard
 * Removed compile time "including..." message.
 * 
 *    Rev 1.0   Feb 15 2000 11:01:02   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.1   Jul 08 1999 10:04:26   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
