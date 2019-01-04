#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2004 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : ShrFundBrokerDlg.h
// ^AUTHOR : Monica Vadeanu
// ^DATE   : November 2004
//
// ^CLASS    : ShrFundBrokerDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : Handles the code for the Fund Info screen
//
// -----------------------------------------------------------------------------
//
//******************************************************************************

#include <ifastgui\BaseMainDlg.h>
#include <uibase\ifdslistctrl.h>


class ShrFundBrokerDlg : public BaseMainDlg
{
public:
   // standard constructor
   ShrFundBrokerDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, 
      GenericInterface* pGIParent, const Command& rCommand);
// Dialog Data
   //{{AFX_DATA(ShrFundBrokerDlg)
   enum
   {
      IDD = IDD_SHR_FUND_BROKER
   };
   //}}AFX_DATA

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(ShrFundBrokerDlg)
public:
   virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:
   virtual bool doRefresh( GenericInterface * /*rpGICaller*/ , 
                           const I_CHAR * /*szOriginalCommand*/);

   virtual SEVERITY doInit();
   virtual void ControlUpdated(UINT controlID, const DString &strValue);
   virtual void OnPostInitDialog();   
   // Generated message map functions
   //{{AFX_MSG(ShrFundBrokerDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnAdmDates();
   afx_msg void OnBtnAdd();
   afx_msg void OnBtnDelete();
   afx_msg void OnBtnMore();
   afx_msg void OnBtnReset();   
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
   
private:
//methods   	
   void SetDlgCaption();
	LRESULT OpenFundListDlg  (WPARAM, LPARAM);
   
//properties   
	CWnd* m_pWndItemInFocus;
	DString _dstrAccount;
	DString _dstrShareholder;
};



//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastgui/ShrFundBrokerDlg.h-arc  $
//
//   Rev 1.2   Nov 28 2004 14:08:40   vadeanum
//PET1117 FN08 - Shareholder Fund Broker support 
//
//   Rev 1.1   Nov 11 2004 16:30:52   vadeanum
//PET1117 FN08 - Shareholder Fund Broker support - work in progress.
//
//   Rev 1.0   Nov 04 2004 10:32:08   VADEANUM
//Initial revision.
//
