#ifndef SLSREPLISTDLG_H
#define SLSREPLISTDLG_H
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
// ^FILE   : SaleRepListDlg.h
// ^AUTHOR : Celia Zhang
// ^DATE   : 12/21/99
//
// ^CLASS    : SaleRepListDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : Handles the code for the Remarks dialog
//
//
//
// -----------------------------------------------------------------------------
//

/////////////////////////////////////////////////////////////////////////////
// SlsRepListDlg dialog

#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif
#include <uibase\ifdslistctrl.h>

class SlsRepListDlg : public BaseMainDlg
{
// Construction
public:
   SlsRepListDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, 
      GenericInterface* pGIParent, const Command& rCommand);

// Dialog Data
   //{{AFX_DATA(SlsRepListDlg)
   enum
   {
      IDD = IDD_SLSREP_LIST
   };
   CButton m_BtnMore;
   // NOTE: the ClassWizard will add data members here
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(SlsRepListDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(SlsRepListDlg)
   afx_msg void OnDblclkSlsrepList( NMHDR* pNMHDR, LRESULT* pResult );
   afx_msg void OnBtnMore();
   //}}AFX_MSG

   void OnPostInitDialog();
   virtual SEVERITY doInit();
   virtual bool doRefresh(GenericInterface *rpGICaller, 
      const I_CHAR * szOriginalCommand);
   DECLARE_MESSAGE_MAP()
private:
   DString m_dstrBrokerCode,
      m_dstrBranchCode,
      m_dstrCaller;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SLSREPLISTDLG_H__752F9E22_B322_11D3_9A90_00C04F33D7DE__INCLUDED_)

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/SlsRepListDlg.h-arc  $
 * 
 *    Rev 1.5   Jul 10 2003 22:22:00   popescu
 * check in for payment instruct, used mfcan_ip_param for some interporcess param passing
 * 
 *    Rev 1.4   Jul 07 2003 12:55:52   HERNANDO
 * Replaced AddListControl with AddIFDSListControl.
 * 
 *    Rev 1.3   Mar 21 2003 18:41:06   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.2   Oct 09 2002 23:56:14   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.1   16 Oct 2001 11:20:26   HSUCHIN
 * Implemented GetMore functionality
 * 
 *    Rev 1.0   Feb 15 2000 11:01:24   SMITHDAV
 * Initial revision.
// 
//    Rev 1.5   Jan 14 2000 08:51:30   POPESCUS
// finally made those dialogs and processes work
// 
//    Rev 1.4   Dec 24 1999 14:18:10   POPESCUS
// fixes and removed commented code
// 
//    Rev 1.3   Dec 22 1999 12:24:22   ZHANGCEL
// Revision bug fixed
// 
//    Rev 1.2   Dec 22 1999 11:39:58   ZHANGCEL
// for release
*/