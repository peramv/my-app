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
// ^FILE   : PaymentInstructionsDlg.h
// ^AUTHOR : Serban Popescu
// ^DATE   : June, 2003
//
// ^CLASS    : PaymentInstructionsDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : Handles the code for the Fund Info screen
//
// -----------------------------------------------------------------------------
//
//******************************************************************************


#include <ifastgui\BaseMainDlg.h>
#include <uibase\ifdslistctrl.h>
#include <ifastgui\ifasthistoricalinfo.hpp>

class PaymentInstructionsDlg : public BaseMainDlg
{
public:
   // standard constructor
   PaymentInstructionsDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, 
      GenericInterface* pGIParent, const Command& rCommand);
// Dialog Data
   //{{AFX_DATA(PaymentInstructionsDlg)
   enum
   {
      IDD = IDD_PAYMENTS_INSTRUCTIONS
   };
   //}}AFX_DATA

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(PaymentInstructionsDlg)
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
   virtual bool PreCancel();
   // Generated message map functions
   //{{AFX_MSG(PaymentInstructionsDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnAdmDates();
   afx_msg void OnBtnAdd();
   afx_msg void OnBtnDelete();
   afx_msg void OnBtnReset();
   afx_msg void OnBtnMore();
   afx_msg void OnBtnBank();
   afx_msg void OnUseEntityAddressCheck();
   afx_msg void OnBtnHistorical();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
   virtual void DoListItemChanged(UINT listControlID,
      const DString &strKey, bool bIsNewItem, bool bIsDummyItem);
   virtual bool ListViewControlFilter(long lSubstituteId, const DString *strKey);
   bool GetOverrideItemString(long lSubstituteId, 
      const DString &ColumnKey, DString &strOut);
   virtual bool PreOk();
private:
//methods
   LRESULT OpenBrokerListDlg(WPARAM, LPARAM);
   LRESULT OpenBranchListDlg(WPARAM, LPARAM);
   LRESULT OpenSlsRepListDlg(WPARAM, LPARAM);
	LRESULT OpenAccountSearchDlg (WPARAM, LPARAM);
   void OnDblclkBankList(NMHDR* pNMHDR, LRESULT* pResult);
   void ShowAndEnableBankRelatedControls(bool bShow);
   void ShowAndEnableAddressRelatedControls(bool bShow);
   void SetDlgCaption();
	void ShowAndEnableMgmtOrBroker();
   CWnd* m_pWndItemInFocus;
//properties
   DString m_dstrBrokerCode, 
      m_dstrBranchCode,
      m_dstrSalesRepCode,
      m_dstrPaymentFor,
      m_dstrPayToEntity,
		m_dstrSearchTypeMgmt,
      m_dstrCurrentBankInstructionsListKey;
};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/PaymentInstructionsDlg.h-arc  $
//
//   Rev 1.11   Jul 27 2006 18:03:42   ZHANGCEL
//PET2192 FN11 - Commission Payments to MgmtCo related changes
//
//   Rev 1.10   Oct 19 2005 17:16:36   AGUILAAM
//PET1243_FN00: ABN AMRO Trailer Fee Processing
//
//   Rev 1.9   Dec 09 2004 11:51:16   Fengyong
//PET1034745 - Add info box when no payment instruction record was added
//
//   Rev 1.8   Aug 14 2003 13:50:06   HERNANDO
//Added OnBtnHistorical.
//
//   Rev 1.7   Aug 07 2003 18:42:42   popescu
//set the bank instructions bank list selection on the bank selected in payment instructions dialog
//
//   Rev 1.6   Jul 26 2003 21:20:32   popescu
//worked on setting the caption of the payment instructions dialog
//
//   Rev 1.5   Jul 26 2003 19:39:04   popescu
//the refresh of the banking list didn't work properly in some cases, 
//
//   Rev 1.4   Jul 23 2003 18:19:50   popescu
//changed list controls to the new IFDSListCtrl
//
//   Rev 1.3   Jul 10 2003 22:21:44   popescu
//check in for payment instruct, used mfcan_ip_param for some interporcess param passing
//
//   Rev 1.2   Jul 09 2003 21:57:44   popescu
//Payment Instructiuons work, business rules implementation SSB_PET_821_FN17
//
//   Rev 1.1   Jul 02 2003 17:49:54   popescu
//work for payment instructions feature 
//
//   Rev 1.0   Jul 01 2003 18:17:56   popescu
//Initial revision.
 */
