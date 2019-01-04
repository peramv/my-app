
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
// ^FILE   : MatSweepInstructionsListDlg.h
// ^AUTHOR :
// ^DATE   : 
//
// ^CLASS    : MatSweepInstructionsListDlg
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
class MatSweepInstructionsListDlg : public BaseMainDlg
{
public:
   /**
    * Standard dialog constructor for DSTC
    */
   MatSweepInstructionsListDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
// Dialog Data
   //{{AFX_DATA(MatSweepInstructionsListDlg)
   enum
   {
      IDD = IDD_MATURITY_SWEEP_INSTR
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
	virtual void DoListItemChanged (UINT listControlID, const DString &strKey, bool bIsNewItem, bool bIsDummyItem);

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
   afx_msg void OnBtnAdd();
   afx_msg void OnBtnDelete();
   afx_msg void OnBtnCopy();
   afx_msg void OnBtnAddDetl();
   afx_msg void OnBtnBank();
   afx_msg void OnBtnDeleteDetl();
   //}}AFX_MSG
   virtual void OnPostInitDialog();

   virtual void ControlUpdated( UINT controlID, const DString &strValue );
   virtual SEVERITY doInit();

   void showBankData ();
   void showAddressData ();

   void enableCopyButton (bool bIsDummyItem);
   void enableInstrButtons (bool bIsDummyItem);
   void enableInstrDetlButtons (bool bIsDummyItem);

   DECLARE_MESSAGE_MAP()

private:
   void SetDlgCaption ();
   void enableControls(bool bEnable); 

   DString m_dstrAccountNum;
   DString m_strCaller;   
   DString m_strInstrType;
   DString m_TradeListKey;
   
};

//******************************************************************************
/* $Log::  
*/