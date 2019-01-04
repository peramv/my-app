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
// ^FILE   : PayToEntityDlg.h
// ^AUTHOR : Serban Popescu
// ^DATE   : June, 2003
//
// ^CLASS    : PayToEntityDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : Handles the code for the Fund Info screen
//
// -----------------------------------------------------------------------------
//
//******************************************************************************


#include <ifastgui\BaseMainDlg.h>
#include <uibase\ifdslistctrl.h>
#include <uibase\dstlistctrl.h>

class PayToEntityDlg : public BaseMainDlg
{
public:
   // standard constructor
   PayToEntityDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, 
      GenericInterface* pGIParent, const Command& rCommand);
// Dialog Data
   //{{AFX_DATA(PayToEntityDlg)
   enum
   {
      IDD = IDD_PAYMENTS_PAY_TO_ENTITY
   };
   //}}AFX_DATA

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(PayToEntityDlg)
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
   //{{AFX_MSG(PayToEntityDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnAdmDates();
   afx_msg void OnBtnAdd();
   afx_msg void OnBtnDelete();
   afx_msg void OnBtnReset();
   afx_msg void OnBtnMore();
   afx_msg void OnBtnInstructions();
   afx_msg void OnDblclkPayToEntityList(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnBtnHistorical();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
   virtual void DoListItemChanged(
      UINT listControlID,
      const DString &strKey,
      bool bIsNewItem ,
      bool bIsDummyItem);
   virtual bool ListViewControlFilter(long lSubstituteId, const DString *strKey);

   bool doDisablePermCheckButton(UINT nID);   
private:
//methods
   void SetDlgCaption();
   bool discardUpdates();
   LRESULT OpenBrokerListDlg( WPARAM, LPARAM );
   CWnd* m_pWndItemInFocus;
   DString m_dstrBrokerCode,
      m_dstrBackgroundSearch, m_dstrSearchTypeMgmt;
//properties
};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/PayToEntityDlg.h-arc  $
//
//   Rev 1.8   Jul 31 2006 11:15:24   porteanm
//Incident 640733 - syncup - Disable the Delete button in Pay to Entity when PayInstructions already exist for PayEntity. Added PayInstructExists to view 258.
//
//   Rev 1.7   Jul 27 2006 18:04:16   ZHANGCEL
//PET2192 FN11 - Commission Payments to MgmtCo related changes
//
//   Rev 1.6   Aug 20 2003 19:51:16   popescu
//PTS 10020922,
//the payment instructions screen is launched as modal and as support from pay to entity. This will ensure that all transactions in payment instructions will be commited to the parent group id and will be sent after the pay to entity transactions are sent
//
//   Rev 1.5   Aug 14 2003 13:50:56   HERNANDO
//Added OnBtnHistorical.
//
//   Rev 1.4   Jul 25 2003 14:26:32   popescu
//Fix crash in payment instructions dialog, as result of filtering the payment instructions list, cleared the address fields when the checque option is selected for the payment method
//
//   Rev 1.3   Jul 23 2003 18:19:54   popescu
//changed list controls to the new IFDSListCtrl
//
//   Rev 1.2   Jul 09 2003 21:57:48   popescu
//Payment Instructiuons work, business rules implementation SSB_PET_821_FN17
//
//   Rev 1.1   Jul 01 2003 18:08:14   popescu
//Clean-up the code, new business rules, set the broker name to the dialog caption, etc...
//
//   Rev 1.0   Jun 27 2003 18:18:12   popescu
//Initial revision.
 */
