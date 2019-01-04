#ifndef BRANCHLISTDLG_H
#define BRANCHLISTDLG_H
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
// ^FILE   : BankListDlg.h
// ^AUTHOR : Celia Zhang
// ^DATE   : 12/20/99
//
// ^CLASS    : BranchListDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : Handles the code for the Remarks dialog
//
//
//
// -----------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////
// BranchListDlg dialog

#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif

class BranchListDlg : public BaseMainDlg
{
// Construction
public:
   BranchListDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, 
      GenericInterface* pGIParent, const Command& rCommand);

// Dialog Data
   //{{AFX_DATA(BranchListDlg)
   enum
   {
      IDD = IDD_BRANCH_LIST
   };
   CButton m_BtnMore;
   // NOTE: the ClassWizard will add data members here
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(BranchListDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(BranchListDlg)
   afx_msg void OnDblclkBranchList(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnBtnMore();

   //}}AFX_MSG
   void OnPostInitDialog();
   virtual SEVERITY doInit();
   virtual bool doRefresh(GenericInterface *rpGICaller, 
      const I_CHAR *szOriginalCommand);
   DECLARE_MESSAGE_MAP()
private:
   DString m_dstrBrokerCode,
      m_dstrCaller;
};
#endif


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/BranchListDlg.h-arc  $
 * 
 *    Rev 1.4   Jul 10 2003 22:21:30   popescu
 * check in for payment instruct, used mfcan_ip_param for some interporcess param passing
 * 
 *    Rev 1.3   Mar 21 2003 18:33:38   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.2   Oct 09 2002 23:55:32   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.1   Jul 31 2002 16:16:20   HERNANDO
 * More button implementation.
 * 
 *    Rev 1.0   Feb 15 2000 11:01:08   SMITHDAV
 * Initial revision.
// 
//    Rev 1.6   Jan 14 2000 08:51:28   POPESCUS
// finally made those dialogs and processes work
// 
//    Rev 1.5   Jan 11 2000 08:41:48   POPESCUS
// fixes and validation
// 
//    Rev 1.4   Dec 24 1999 14:18:08   POPESCUS
// fixes and removed commented code
// 
//    Rev 1.3   Dec 22 1999 12:24:02   ZHANGCEL
// Revision bug fixed
// 
//    Rev 1.2   Dec 22 1999 11:39:04   ZHANGCEL
// for release
*/