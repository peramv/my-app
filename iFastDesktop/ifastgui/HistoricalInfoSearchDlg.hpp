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
//    Copyright 1999 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : HistoricalInfoSearchDlg.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : 01/08/03
//
// ^CLASS    : HistoricalInfoSearchDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : Handles the code for the Fund Info screen
//
// -----------------------------------------------------------------------------
//
//******************************************************************************


#include <ifastgui\BaseMainDlg.h>
#include <uibase\listctrl.h>
#include <uibase\combobase.h>
#include <uibase\dstdatetimectrl.h>

class HistoricalInfoSearchDlg : public BaseMainDlg
{
public:
   // standard constructor
   HistoricalInfoSearchDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
// Dialog Data
   //{{AFX_DATA(HistoricalInfoSearchDlg)
   enum
   {
      IDD = IDD_HISTORICAL_SEARCH
   };
   //}}AFX_DATA

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(HistoricalInfoSearchDlg)
public:
   virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:
   virtual SEVERITY doInit();
   virtual void OnPostInitDialog();
   virtual bool doRefresh( GenericInterface *rpGICaller, 
      const I_CHAR *szOriginalCommand );   // Generated message map functions
   //{{AFX_MSG(HistoricalInfoSearchDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnSrch();
   afx_msg void OnSelchangeCmbSrch();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
private:
//methods
   LRESULT OpenFundListDlg( WPARAM, LPARAM );
   LRESULT OpenBrokerListDlg( WPARAM, LPARAM );
   LRESULT OpenBranchListDlg( WPARAM, LPARAM );
   LRESULT OpenSlsRepListDlg( WPARAM, LPARAM );
   CWnd* m_pWndItemInFocus;
//properties
};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/HistoricalInfoSearchDlg.hpp-arc  $
//
//   Rev 1.3   Mar 21 2003 18:37:32   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.2   Feb 11 2003 15:22:34   popescu
//Bug fixes
//
//   Rev 1.1   Feb 11 2003 14:42:08   popescu
//changes related to the Historical information for Broker and Sales rep, as well as displaying the names for them in the Historical Info Search dialog
//
//   Rev 1.0   Feb 06 2003 11:55:00   popescu
//Initial revision.
 * 
 */
