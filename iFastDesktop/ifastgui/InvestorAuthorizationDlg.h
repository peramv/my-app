
#pragma once

//******************************************************************************
//
// COPYRIGHT:
//
// The computer systems, procedures, data bases and
// programs created and maintained by International Financial Data Services, Inc.,
// are proprietary in nature and as such are confIdential.
// Any unauthorized use or disclosure of such information
// may result in civil liabilities.
//
// Copyright 2009 by International Financial Data Services, Inc.
//
//******************************************************************************
//
// ^FILE   : InvestorAuthorizationDlg.h
// ^AUTHOR :
// ^DATE   : 
//
// ^CLASS    : InvestorAuthorizationDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : Handles the code for the Fund Info screen
//
//******************************************************************************


#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif

#include <ifastgui\ifasthistoricalinfo.hpp>

class InvestorAuthorizationDlg : public BaseMainDlg
{
public:
   /**
    * Standard dialog constructor for DSTC
    */
   InvestorAuthorizationDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
// Dialog Data
   //{{AFX_DATA(InvestorAuthorizationDlg)
   enum
   {
      IDD = IDD_INVESTOR_AUTHORIZATION
   };
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(InvestorAuthorizationDlg)
public:
   virtual BOOL PreTranslateMessage(MSG* pMsg);  
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

   virtual void ControlUpdated ( UINT controlID, 
                                 const DString &strValue);

   bool GetDataForControl( UINT controlID, 
                           DString &strValueOut, 
                           bool bFormatted, 
                           int index ) const;
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
   //{{AFX_MSG(InvestorAuthorizationDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnReset();
   afx_msg void OnBtnAdd();
   afx_msg void OnBtnDel();
   afx_msg void OnBtnBank();
   afx_msg void OnBtnAdmin();
   afx_msg void OnBtnHistorical();
   afx_msg void OnRadioAllFundDirectDeposit();
   afx_msg void OnRadioTIFDirectDeposit();
   //}}AFX_MSG

   virtual void OnPostInitDialog();
   virtual SEVERITY doInit();
   virtual void DoListItemChanged( UINT listControlID,
                                   const DString &strKey, 
                                   bool bIsNewItem ,	
                                   bool bIsDummyItem
                                  );

   DECLARE_MESSAGE_MAP()

private:

   LRESULT OpenBrokerListDlg( WPARAM, LPARAM );
   LRESULT OpenBranchListDlg( WPARAM, LPARAM );
   LRESULT OpenSlsRepListDlg( WPARAM, LPARAM );

   void     SetDlgCaption ();
   DString  m_RecordType;
   bool     m_bDialogInit;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
// $Log:   Y:/VCS/BF iFAST/ifastgui/InvestorAuthorizationDlg.h-arc  $
//
//   Rev 1.3   Dec 24 2009 03:19:08   dchatcha
//IN# 1947288 - Delete button enabled in error on Inv Auth screen. Code review,removed logic that usually done by  framework.
//
//   Rev 1.2   Dec 23 2009 02:39:54   dchatcha
//IN# 1947288 - Delete button enabled in error on Inv Auth screen.
//
//   Rev 1.1   22 Jul 2009 18:09:32   popescu
//PET156681 FN14 H36 Investor Authorization - clean-up various fixes.
//
//   Rev 1.0   Jul 09 2009 13:15:40   dchatcha
//Initial revision.
//
