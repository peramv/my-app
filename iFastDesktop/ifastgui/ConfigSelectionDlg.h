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
// ^FILE   : ConfigSelectionDlg.h
// ^AUTHOR : Terry Erickson
// ^DATE   : 3/31/98
//
// ^CLASS    : ConfigSelectionDlg
// ^SUBCLASS PARENT : CDialog
//
// ^CLASS DESCRIPTION : Displays the details dialog from the AboutBox
//
// -----------------------------------------------------------------------------
//                PUBLIC MEMBER FUNCTIONS
// -----------------------------------------------------------------------------
//
// ^METHOD      : ConfigSelectionDlg
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
#include <map>
#ifndef LISTCTRL_H
   #include <uibase\ListCtrl.h>
#endif

/////////////////////////////////////////////////////////////////////////////
// ConfigSelectionDlg dialog
class ConfigSelectionDlg : public CDialog
{
// Construction
public:
   ConfigSelectionDlg(CWnd* pParent = NULL);   // standard constructor
   ConfigSelectionDlg(const DString& dstrFileName, CWnd* pParent = NULL);

// Dialog Data
   //{{AFX_DATA(ConfigSelectionDlg)
   enum
   {
      IDD = IDD_CONFIG_SELECTOR
   };
   ListViewControl m_configList;
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(ConfigSelectionDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:

   void ConfigSelectionDlg::OnDblclkLbConfigList(NMHDR* pNMHDR, LRESULT* pResult);
// Generated message map functions
   //{{AFX_MSG(ConfigSelectionDlg)
   virtual BOOL OnInitDialog();
   virtual void OnOK();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()

private:
   int m_itemCount;
   DString  dstrFileName_;
   typedef std::map<CString, CString> CONFIGFILEMAP ;
   typedef CONFIGFILEMAP::iterator CONFIGFILEMAP_ITER;
   CONFIGFILEMAP mapConfigs_;

   void addFileToList( const DString& dstrFileName );

public:
   void setFileName( const DString& s ) { dstrFileName_ = s; }
   const DString& getFileName() { return dstrFileName_; }
   int getFileCount() const { return mapConfigs_.size(); }
   afx_msg void OnLvnItemchangedLbConfigList(NMHDR *pNMHDR, LRESULT *pResult);
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/ConfigSelectionDlg.h-arc  $
//
//   Rev 1.3   Dec 03 2010 07:55:02   purdyech
//Changes to implement view performance tracking and crash handling
//
//   Rev 1.2   Jan 12 2010 13:49:32   purdyech
//Support @ syntax for configuration file names (file'o'files)
//Display filename as description if description is blank
//
//   Rev 1.1   Aug 25 2009 08:38:20   purdyech
//displays multiple files in selection dialog
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
