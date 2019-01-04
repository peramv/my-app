
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
// ^FILE   : RESPTransfersDlg.h
// ^AUTHOR :
// ^DATE   : 
//
// ^CLASS    : RESPTransfersDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION :
//
// -----------------------------------------------------------------------------
//
//******************************************************************************


#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif


class RESPTransfersDlg : public BaseMainDlg
{
public:
   /**
    * Standard dialog constructor for DSTC
    */
   RESPTransfersDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
// Dialog Data
   //{{AFX_DATA(SettlementDlg)
   enum
   {
      IDD = IDD_RESP_TRANSFER
   };
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
   virtual bool doSend ( GenericInterface *rpGICaller, 
                         const I_CHAR *szMessage);
   // Generated message map functions
   //{{AFX_MSG(SettlementDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnAdd();
   afx_msg void OnBtnDelete();
   afx_msg void OnAcctLevelOverride();
   afx_msg void OnBtnMore();
   //}}AFX_MSG
   virtual void OnPostInitDialog();

   virtual void ControlUpdated( UINT controlID, const DString &strValue );
   virtual SEVERITY doInit();

   virtual void DoListItemChanged (UINT listControlID, const DString &strKey, bool bIsNewItem, bool bIsDummyItem);
   virtual void DoPreListItemChanged ( UINT listControlID, const DString &strKey, bool bIsNewItem, bool bIsDummyItem);

   void registerControlsToTab ();
   void addControls ();
   void displayDynamicLabels ();
   void showHideQESIControls (int bShowHide);
   void setAllowedChars ();
   void initAccLevelOverride();
   void enableBeneficiaryData ();
   void enableAddDelete (bool bIsNewItem = false , bool bIsDummyItem = false);
   void enableNEQs ();

   void addQESITab ();
   void showHideQESITotTxfr (int bShowHide); 
   void showHideQESITextYear(int bShowHide);
  
   void reloadControlsForNonTrusteeTxfr ();
   void enableDisableControlsForNonTrusteeTxfr (bool bShowHide);
   void displayQESITotTxfr();
   void displayNotionalTaxYear();
  
   void tabSelectionChanged( UINT tabControlID, const DString& strPageName );
   bool isNonTrusteeCurrContribYear();
   void enableDisableNotionalControls();
   void enableDisableSAGESControls (bool bEnableDisable);

   DECLARE_MESSAGE_MAP()

private:

   void SetDlgCaption ();
   bool isNonTrusteeHistRecord ();

   DString	m_dstrAccountNum;
   DString	m_dstrCaller;
   DString  m_HistoryPending;
   bool		m_bDialogInit,
            m_bRespTransferListSelectionInProgress;
   int		m_DecimalDigits;
   DString	m_TransType;
   DString	m_DepositType;
   DString	m_RedemptonCode;
   DString	m_EffectiveDate;

   DSTTabCtrl* m_pTabCtrl;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastgui/RESPTransfersDlg.h-arc  $
//
//   Rev 1.10   Sep 23 2011 18:16:08   popescu
//Incident 2646349 - P0184541Fn01- Non QESI Desktop Issues
//
//   Rev 1.9   Jul 29 2011 07:31:42   panatcha
//fix IN5285248 and IN2591262
//
//   Rev 1.8   Jul 25 2011 07:03:18   panatcha
//P0184541_FN01_InvescoQESItrans incidents
//
//   Rev 1.7   Jul 18 2011 05:51:22   panatcha
//IN2584478 - All reject error and re-label 
//
//   Rev 1.6   Jun 28 2011 10:09:20   panatcha
//P0184541_FN01_InvescoQESItrans
//