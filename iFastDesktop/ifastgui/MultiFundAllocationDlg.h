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
// ^FILE   : MultiFundAllocationDlg.h
// ^AUTHOR : Serban Popescu
// ^DATE   : August, 2003
//
// ^CLASS    : MultiFundAllocationDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : Handles the code for the Fund Info screen
//
// -----------------------------------------------------------------------------
//
//******************************************************************************


#include <ifastgui\BaseMainDlg.h>
#include <uibase\ifdslistctrl.h>

class MultiFundAllocationDlg : public BaseMainDlg
{
public:
   // standard constructor
   MultiFundAllocationDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, 
      GenericInterface* pGIParent, const Command& rCommand);
// Dialog Data
   //{{AFX_DATA(MultiFundAllocationDlg)
   enum
   {
      IDD = IDD_MULTI_FUND_ALLOC
   };
   //}}AFX_DATA

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(MultiFundAllocationDlg)
public:
   virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:
   virtual bool doRefresh(GenericInterface * /*rpGICaller*/, 
      const I_CHAR * /*szOriginalCommand*/);
   virtual SEVERITY doInit();
   virtual void ControlUpdated(UINT controlID, const DString &strValue);
   virtual void OnPostInitDialog();
   // Generated message map functions
   //{{AFX_MSG(MultiFundAllocationDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnAddFrom();
   afx_msg void OnBtnDeleteFrom();
   afx_msg void OnBtnResetFrom();
   afx_msg void OnBtnAddTo();
   afx_msg void OnBtnDeleteTo();
   afx_msg void OnBtnResetTo();
   afx_msg void OnFullTransfer();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
   virtual void DoListItemChanged(
      UINT listControlID,
      const DString &strKey,
      bool bIsNewItem ,
      bool bIsDummyItem);
private:
//methods
   void SetDlgCaption();
   void changeAmountLabel(bool bWhatLabel);
   void callerDependentChanges();
   LRESULT OpenFundListDlg(WPARAM, LPARAM);
   CWnd* m_pWndItemInFocus;
   DString m_dstrCaller;
};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/MultiFundAllocationDlg.h-arc  $
//
//   Rev 1.1   Sep 01 2003 21:23:52   popescu
//PET 809 FN 02 CIBC Multi Fund Transfer
//
//   Rev 1.0   Aug 14 2003 15:52:40   popescu
//Initial revision.
 */
