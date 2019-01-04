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
// ^FILE   : OPCConfirmReprintDlg.h
// ^AUTHOR : Monica Porteanu
// ^DATE   : May 2005
//
// ^CLASS    : OPCConfirmReprintDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : Handles the code for the Fund Info screen
//
// -----------------------------------------------------------------------------
//
//******************************************************************************

#include <ifastgui\BaseMainDlg.h>
#include <uibase\ifdslistctrl.h>

#include <ifastgui\confirmreprintdlg.h>

class OPCConfirmReprintDlg : public ConfirmReprintDlg
{
public:
   // standard constructor
   OPCConfirmReprintDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, 
   GenericInterface* pGIParent, const Command& rCommand);

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(OPCConfirmReprintDlg)
public:
   virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:
   virtual bool doRefresh( GenericInterface * /*rpGICaller*/, 
                           const I_CHAR * /*szOriginalCommand*/);
   virtual void OnPostInitDialog();     

   // Generated message map functions
   //{{AFX_MSG(OPCConfirmReprintDlg)      
   afx_msg void OnBtnReset();   
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
   
private:
//methods   	   
   CWnd* m_pWndItemInFocus;
//properties   

    DString _dstrAccountNum;
	DString _dstrTransId;
	DString _dstrFund;
	DString _dstrClass;
};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastgui/OPCConfirmReprintDlg.h-arc  $
//
//   Rev 1.4   May 25 2005 14:55:48   porteanm
//PET OPC Confirm Reprint - Reset.
//
//   Rev 1.3   May 24 2005 12:57:50   porteanm
//PET OPC Confirm Reprint - Renamed OPC files. Changed class hierarchy.
//
//   Rev 1.2   May 06 2005 13:11:02   porteanm
//PET OPC Confirm Reprint - Typos for Release 63.
//
//   Rev 1.1   May 05 2005 17:35:36   porteanm
//PET OPC Confirm Reprint - New screen for Release 63.
//
//   Rev 1.0   May 05 2005 11:19:02   porteanm
//Initial revision.
//

