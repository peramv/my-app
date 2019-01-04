
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
//    Copyright 2002 by International Financial Data Service
//
//******************************************************************************
//
// ^FILE   : DocumentListDlg.h
// ^AUTHOR :
// ^DATE   : 
//
// ^CLASS    : DocumentListDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : Handles the code for the Fund Info screen
//
// -----------------------------------------------------------------------------
//
//******************************************************************************


#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif
class DocumentListDlg : public BaseMainDlg
{
public:
   /**
    * Standard dialog constructor for DSTC
    */
   DocumentListDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
// Dialog Data
   //{{AFX_DATA(SettlementDlg)
   enum
   {
      IDD = IDD_DOCUMENT_LIST
   };
   int m_rbAcctReg;
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(SettlementDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:
   /**
     * Required implementation for the refresh method.  No refresh activity is
     * performed for this class.
     * @param rpGICaller - A reference pointer to the calling object.
     * @param szOriginalCommand - A string literal representing the original
     * command issuing the refresh (which may provide a hint on whether this
     * object needs to check for refresh).
     * @returns true if successful, call getErrors for errors if false
     */
   virtual bool doRefresh( GenericInterface * /*rpGICaller*/, 
                           const I_CHAR * /*szOriginalCommand*/ );
   /**
     * Get parameters from InterProcessData.
     * @returns SEVERITY, check conditions if > NO_SEVERITY
     */
   /**
     * This method should be overridden in the derived dialog if there is
     * OnOk processing to be done after the base processing.  Note that the OnOk
     * processing can no longer be "cancelled" at this point.  BaseMainDlg 
     * enforces its actions by making OnOk private.
     * @param bCancelStatus - true = Ok successful, false = Ok failed
     */
   //  virtual void PostOk(
   //     bool /* bOkStatus */
   //     );
   // Generated message map functions
   //{{AFX_MSG(SettlementDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnHistorical();
   afx_msg void OnRbAcctRegistration();
   afx_msg void OnRbTaxCompliant();
   afx_msg void OnRbDeathClaim();
   afx_msg void OnRbAccoutholderRisk();
   afx_msg void OnBtnMore();
   //}}AFX_MSG
   virtual void OnPostInitDialog();

   virtual void ControlUpdated( UINT controlID, const DString &strValue );
   virtual SEVERITY doInit();

   void OnBtnAdd();
   void OnBtnDelete();
   virtual void DoListItemChanged(UINT listControlID, const DString &strKey, bool bIsNewItem, bool bIsDummyItem);
   DECLARE_MESSAGE_MAP()

private:
	void SetDlgCaption();
	void switchDocumentListType();
	void setRadioButton();
	DString m_dstrAccountNum,	
			m_strEntityId;
	bool m_bDialogInit;
};

//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastgui/DocumentListDlg.h-arc  $
//
//   Rev 1.6   Jul 23 2012 12:55:42   wutipong
//PETP0179630_FN01 FATCA Account Entity Document Tracking
//
//   Rev 1.5   04 Nov 2008 13:11:56   popescu
//KYC-AML fixes after system integrated testing
//
//   Rev 1.4   03 Nov 2008 17:33:12   popescu
//KYC/AML - Joint accounts feature - after System Integrated Testing
// 
//    Rev 1.8   31 Oct 2008 16:17:20   popescu
// KYC/AML - joint accounts feature
*/