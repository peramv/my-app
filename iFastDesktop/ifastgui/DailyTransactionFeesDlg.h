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
// ^FILE   : DailyTransactionFeesDlg.h
// ^AUTHOR : Monica Vadeanu
// ^DATE   : Jan 2004
//
// ^CLASS    : DailyTransactionFeesDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : Handles the code for the Fund Info screen
//
// -----------------------------------------------------------------------------
//
//******************************************************************************

#include <ifastgui\BaseMainDlg.h>
#include <uibase\ifdslistctrl.h>


class DailyTransactionFeesDlg : public BaseMainDlg
{
public:
   // standard constructor
   DailyTransactionFeesDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, 
      GenericInterface* pGIParent, const Command& rCommand);
// Dialog Data
   //{{AFX_DATA(DailyTransactionFeesDlg)
   enum
   {
      IDD = IDD_DAILY_TRANSACTIONS_FEES
   };
   //}}AFX_DATA

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(DailyTransactionFeesDlg)
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
   //{{AFX_MSG(DailyTransactionFeesDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnAdmDates();
   afx_msg void OnBtnAdd();
   afx_msg void OnBtnDelete();
   afx_msg void OnBtnReset();
   afx_msg void OnBtnMore();   
   afx_msg void OnBtnHistorical ();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
   
   void DoListItemChanged(UINT listControlID,
                          const DString &strKey,
                          bool bIsNewItem ,
                          bool bIsDummyItem);
private:
//methods   
	LRESULT OpenFundListDlg  (WPARAM, LPARAM);
   void SetDlgCaption();
   CWnd* m_pWndItemInFocus;
//properties   

	DString _dstrDailyTransFeeRecordType;
	DString _dstrFeeCode;
	DString _dstrFundCode;
	DString _dstrClassCode;
	DString _dstrEffectiveDate;	
};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/DailyTransactionFeesDlg.h-arc  $
//
//   Rev 1.3   Jul 16 2010 15:57:46   jankovii
//PET0170770_FN01_Anti Dilution Levy
//
//   Rev 1.2   Jul 14 2010 13:35:08   jankovii
//PET0170770_FN01_Anti Dilution Levy
//
//   Rev 1.1   Feb 11 2004 11:31:44   VADEANUM
//PET859 FN23 - ADL - first working version.
//
//   Rev 1.0   Feb 03 2004 16:56:48   VADEANUM
//Initial revision.
//
*/
