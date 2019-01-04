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
// ^FILE   : ShrFundSponsorAgreementDlg.h
// ^AUTHOR : Monica Vadeanu
// ^DATE   : Jan 2004
//
// ^CLASS    : ShrFundSponsorAgreementDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : Handles the code for the Fund Info screen
//
// -----------------------------------------------------------------------------
//
//******************************************************************************

#include <ifastgui\BaseMainDlg.h>
#include <uibase\ifdslistctrl.h>


class ShrFundSponsorAgreementDlg : public BaseMainDlg
{
public:
   // standard constructor
   ShrFundSponsorAgreementDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, 
      GenericInterface* pGIParent, const Command& rCommand);
// Dialog Data
   //{{AFX_DATA(ShrFundSponsorAgreementDlg)
   enum
   {
      IDD = IDD_SHR_FUND_SPONSOR_AGREEMENT
   };
   //}}AFX_DATA

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(ShrFundSponsorAgreementDlg)
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
   //{{AFX_MSG(ShrFundSponsorAgreementDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnAdmDates();
   afx_msg void OnBtnAdd();
   afx_msg void OnBtnDelete();
   afx_msg void OnBtnReset();   
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
   
private:
//methods   	
   void SetDlgCaption();
   CWnd* m_pWndItemInFocus;
//properties   

	DString _dstrAccount;
	DString _dstrShareholder;
};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastgui/ShrFundSponsorAgreementDlg.h-arc  $
//
//   Rev 1.0   Jul 26 2004 10:35:04   VADEANUM
//Initial revision.
//
