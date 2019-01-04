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
//    Copyright 2005 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : ConfirmReprintDlg.h
// ^AUTHOR : Monica Porteanu
// ^DATE   : May 2005
//
// ^CLASS    : ConfirmReprintDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : Handles the code for the Fund Info screen
//
// -----------------------------------------------------------------------------
//
//******************************************************************************

#include <ifastgui\BaseMainDlg.h>
#include <uibase\ifdslistctrl.h>

class ConfirmReprintDlg : public BaseMainDlg
{
public:
   // standard constructor
   ConfirmReprintDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, 
   GenericInterface* pGIParent, const Command& rCommand);
// Dialog Data
   //{{AFX_DATA(ConfirmReprintDlg)
   enum
   {
      IDD = IDD_CONFIRM_REPRINT
   };
   //}}AFX_DATA
// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(ConfirmReprintDlg)
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
   virtual void OnPostInitDialog();   
   virtual BOOL OnInitDialog(); 

   void SetDlgCaption();
   // Generated message map functions
   //{{AFX_MSG(ConfirmReprintDlg)      
   afx_msg void OnBtnReset();   
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
   
private:
//methods   	   
   CWnd* m_pWndItemInFocus;
//properties   

	DString _dstrTransId;
	DString _dstrFund;
	DString _dstrClass;
	DString _dstrAccountNum;
};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastgui/ConfirmReprintDlg.h-arc  $
//
//   Rev 1.0   May 24 2005 12:55:18   porteanm
//Initial revision.
//


