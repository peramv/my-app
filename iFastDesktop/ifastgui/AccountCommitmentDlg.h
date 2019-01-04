//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2011 by International Financial Data Services.
//
//******************************************************************************
//
// ^FILE   : AccountCommitmentDlg.h
// ^CLASS  : AccountCommitmentDlg
// ^SUBCLASS : BaseMainDlg
//
//******************************************************************************

#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif


class AccountCommitmentDlg : public BaseMainDlg
{
public:

   AccountCommitmentDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
   void UpdateButtons();
   void showBankData();

   //{{AFX_DATA(AccountCommitmentDlg)
   enum
   {
      IDD = IDD_ACCT_COMMITMENT
   };
   //}}AFX_DATA

   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(AccountCommitmentDlg)


protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

protected:
   virtual bool doRefresh( GenericInterface * /*rpGICaller*/, 
                           const I_CHAR * /*szOriginalCommand*/ );
   // Generated message map functions
   //{{AFX_MSG(AccountCommitmentDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnAdmin();
   afx_msg void OnBtnBank();
   afx_msg void OnBtnReset();
   afx_msg void OnBtnStop();
   afx_msg void OnBtnSuspend();
   //}}AFX_MSG
   virtual void OnPostInitDialog();
   virtual SEVERITY doInit ();

   virtual void ControlUpdated( UINT controlID, const DString &strValue );

   // Generated message map functions
   //{{AFX_MSG(AccountCommitmentDlg)
   //}}AFX_MSG

   DECLARE_MESSAGE_MAP()
   void DoListItemChanged(UINT listControlID, const DString &strKey, bool bIsNewItem, bool bIsDummyItem);

private:

   void SetDlgCaption ();
   DString	m_dstrAccountNum;
   DString  m_dstrCaller;

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/AccountCommitmentDlg.h-arc  $
//
//   Rev 1.3   Feb 24 2012 18:45:08   if991250
//Account Commitment
//
//   Rev 1.2   Feb 22 2012 17:02:00   if991250
//Account Commitment
//
//   Rev 1.1   Feb 17 2012 10:38:14   if991250
//Account Commitment
//
//   Rev 1.0   Jan 20 2012 16:12:58   if991250
//Initial revision.
//
**/