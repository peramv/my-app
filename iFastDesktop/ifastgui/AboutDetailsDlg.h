
#ifndef AboutDetailsDlg_h
#define AboutDetailsDlg_h

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
// ^FILE   : AboutDetailsDlg.h
// ^AUTHOR : Terry Erickson
// ^DATE   : 3/31/98
//
// ^CLASS    : AboutDetailsDlg
// ^SUBCLASS PARENT : CDialog
//
// ^CLASS DESCRIPTION : Displays the details dialog from the AboutBox
//
// -----------------------------------------------------------------------------
//                PUBLIC MEMBER FUNCTIONS
// -----------------------------------------------------------------------------
//
// ^METHOD      : AboutDetailsDlg
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

#ifndef LISTCTRL_H
   #include <uibase\ListCtrl.h>
#endif

/////////////////////////////////////////////////////////////////////////////
// AboutDetailsDlg dialog
class AboutDetailsDlg : public CDialog
{
// Construction
public:
   AboutDetailsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
   //{{AFX_DATA(AboutDetailsDlg)
   enum
   {
      IDD = IDD_ABOUTBOX_DETAILS
   };
   ListViewControl m_infoList;
   ListViewControl m_registryList;
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(AboutDetailsDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(AboutDetailsDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnSave();
   virtual void OnOK();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()

   private:

   void addRegistryEntry( const I_CHAR* lpcszConfig, const I_CHAR* lpcszKey, const I_CHAR* lpcszValue );
   CString GetModuleBuildInfo( HINSTANCE inst, const short infoType );
   CString LoadModuleInfo( CString moduleName );
   void LoadDependentInfo( CString dependentName );
   void GetLatestBuildDate( CString &latestDate, const CString &compareDate );
   DString GetInfoAsString() const;
   BOOL WalkTheProcess( CString moduleName );
   BOOL ShowImports( PIMAGE_DOS_HEADER dosHeader );
   PIMAGE_SECTION_HEADER GetSectionHeader( PSTR name, PIMAGE_NT_HEADERS pNTHeader );

   int m_itemCount;
   int m_registryCount;
public:
   afx_msg void OnLvnItemchangedLbRegistryInfo(NMHDR *pNMHDR, LRESULT *pResult);
};

#endif // AboutDetailsDlg_h

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/AboutDetailsDlg.h-arc  $
 * 
 *    Rev 1.4   May 14 2007 15:12:58   purdyech
 * PTS 820423 - Extensive changes to Component Dialog
 * 
 *    Rev 1.3   Oct 09 2002 23:55:26   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.2   19 Mar 2002 13:44:18   PURDYECH
 * Added #pragma once include guard
 * Removed compile time "including..." message.
 * 
 *    Rev 1.1   03 Jul 2001 15:55:04   SMITHDAV
 * Add revision list.
 * 
 *    Rev 1.0   Feb 15 2000 11:01:02   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.1   Jul 08 1999 10:04:24   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
