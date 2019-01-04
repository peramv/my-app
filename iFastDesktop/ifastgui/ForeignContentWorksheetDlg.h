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
// ^FILE   : FCWhatIfDlg.h
// ^AUTHOR : Monica Vadeanu
// ^DATE   : April 2004
//
// ^CLASS    : FCWhatIfDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : Handles the code for the Fund Info screen
//
// -----------------------------------------------------------------------------
//
//******************************************************************************

#include <ifastgui\BaseMainDlg.h>
#include <uibase\ifdslistctrl.h>


class ForeignContentWorksheetDlg : public BaseMainDlg
{
public:
   // standard constructor
   ForeignContentWorksheetDlg( CWnd* pParent, 
		                         GenericInterfaceContainer* pGIC, 
                               GenericInterface* pGIParent, 
					                const Command& rCommand );
// Dialog Data
   //{{AFX_DATA(FCWhatIfDlg)
   enum
   {
      IDD = IDD_FOREIGN_CONTENT_WORKSHEET
   };
   //}}AFX_DATA

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(FCWhatIfDlg)
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
   //{{AFX_MSG(FCWhatIfDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnCalculate();
   afx_msg void OnBtnRefresh(); 
   afx_msg void OnKillfocusCmbTransType();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
   
private:
//methods   
	LRESULT OpenFundListDlg  (WPARAM, LPARAM);
   void SetDlgCaption();
	void ConnectHypoControls(bool bConnected);
	void ConnectACBControls(bool bConnected);
	void initTransType();
	void displayLabelByTransType( );
   virtual void OnCancel();         
   void EnableHypoControls(bool bEnable);

private:


   CWnd* m_pWndItemInFocus;
//properties   	
	DString _dstrAccount;
	DString _dstrShareholder;
	DString m_dstrDefautTransType;
	bool    m_bNotify;


};

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastgui/ForeignContentWorksheetDlg.h-arc  $
//
//   Rev 1.3   May 26 2004 18:17:56   YINGBAOL
//PET985:fix click "X" button different from "Close" and disable search criteria part after user clicks "Calculate" button
//
//   Rev 1.2   May 25 2004 10:08:44   YINGBAOL
//PET985:Implement FundName etc...
//
//   Rev 1.1   May 19 2004 17:43:14   YINGBAOL
//PET985:make hypo work
//
//   Rev 1.0   Apr 21 2004 15:35:42   VADEANUM
//Initial revision.
//
