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
// ^FILE   : InvDetlDeductionDlg.h
// ^AUTHOR : Amelia Aguila
// ^DATE   : Jan 
//
// ^CLASS    : InvDetlDeductionDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : Handles the code for the Fund Info screen
//
// -----------------------------------------------------------------------------
//
//******************************************************************************

#include <ifastgui\BaseMainDlg.h>
#include <uibase\ifdslistctrl.h>


class InvDetlDeductionDlg : public BaseMainDlg
{
public:
   // standard constructor
   InvDetlDeductionDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, 
      GenericInterface* pGIParent, const Command& rCommand);
// Dialog Data
   //{{AFX_DATA(InvDetlDeductionDlg)
   enum
   {
      IDD = IDD_INV_DETL_DEDUCTIONS_INQ_DLG
   };
   //}}AFX_DATA

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(InvDetlDeductionDlg)
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
   //virtual void ControlUpdated(UINT controlID, const DString &strValue);
   virtual void OnPostInitDialog();   
   // Generated message map functions
   //{{AFX_MSG(InvDetlDeductionDlg)
   virtual BOOL OnInitDialog();   
   afx_msg void OnBtnMore();    
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
   
private:
//methods   	
   void SetDlgCaption();
	   
//properties   
	CWnd* m_pWndItemInFocus;
	DString _dstrAccount;
	DString _dstrShareholder;
   DString _dstrTransId;
};



//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastgui/InvDetlDeductionDlg.h-arc  $
//
//   Rev 1.1   Feb 17 2005 13:16:08   aguilaam
//PET1198_FN01: LSIF Reason Code enhancement. 
//
//   Rev 1.0   Jan 28 2005 14:51:24   aguilaam
//Initial revision.
//

