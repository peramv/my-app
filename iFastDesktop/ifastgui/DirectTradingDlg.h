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
// ^FILE   : DirectTradingDlg.h
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : DirectTradingDlg
// ^SUBCLASS : IFastBaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

#include <ifastgui\BaseMainDlg.h>

// DirectTradingDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DirectTradingDlg dialog

class DirectTradingDlg : public BaseMainDlg
{
// Construction
public:
   DirectTradingDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);


private:
   //{{AFX_DATA(DirectTradingDlg)
   enum
   {
      IDD = IDD_DIRECT_TRADING
   };
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(DirectTradingDlg)
public:

protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:
   // Generated message map functions
   //{{AFX_MSG(DirectTradingDlg)
   afx_msg void OnBtnBank();
   afx_msg void OnBtnAdm();

   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()

   BOOL OnInitDialog();

   /**
     * Loading entity list and first selection
     * This method is invoked by the base architecture after OnInitDialog has 
     * completed.  This should be implemented for time intensive setup so that
     * the screen can display quickly and then do this processing.
     */
   void OnPostInitDialog();

   /**
     * Get parameters from InterProcessData.
     * @returns SEVERITY, check conditions if > NO_SEVERITY
     */
   virtual SEVERITY doInit();
   /**
     * Required implementation for the refresh method.  No refresh activity is
     * performed for this class.
     * @param rpGICaller - A reference pointer to the calling object.
     * @param szOriginalCommand - A string literal representing the original
     * command issuing the refresh (which may provide a hint on whether this
     * object needs to check for refresh).
     * @returns true if successful, call getErrors for errors if false
     */
   virtual bool doRefresh(GenericInterface * rpGICaller, const I_CHAR * szOriginalCommand);

   void InitControl(UINT controlID);

   virtual void ControlUpdated(UINT controlID, const DString &strValue);

   bool ListViewControlFilter( long lSubstituteId, const DString *strKey = NULL  );
   void DisplayTitle();
private:

   void addControls();
   void populateData();
   void ShowFromBankRelated( bool show );
   DString m_dstrAccountNum;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/DirectTradingDlg.h-arc  $
//
//   Rev 1.1   Oct 24 2003 13:12:46   FENGYONG
//Add String TXT_DIRECT_TRADING_TITLE
//
//   Rev 1.0   Oct 07 2003 09:51:24   FENGYONG
//Initial Revision
 *
 */
