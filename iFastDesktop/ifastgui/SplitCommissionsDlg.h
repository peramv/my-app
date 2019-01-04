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
// ^FILE   : SplitCommissionsDlg.h
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : SplitCommissionsDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : Handles the code for the Remarks dialog
//
//******************************************************************************

#include <ifastgui\basemaindlg.h>

class SplitCommissionsDlg : public BaseMainDlg
{
// Construction
public:
   SplitCommissionsDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, 
      GenericInterface* pGIParent, const Command& rCommand);
   ~SplitCommissionsDlg();

// Dialog Data
   //{{AFX_DATA(RemarksDlg)
   enum
   {
      IDD = IDD_SPLITCOMMISSIONS
   };
   //}}AFX_DATA

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(RemarksDlg)
   virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:
   // Generated message map functions
   //{{AFX_MSG(SplitCommissionsDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnAdd();
   afx_msg void OnBtnDelete();
   afx_msg void OnBtnReset();
   afx_msg void OnBtnClose();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()

   virtual SEVERITY doInit();
   void OnPostInitDialog();

   virtual bool doRefresh(GenericInterface *rpGICaller, const I_CHAR *szOriginalCommand)
   {
      return true;
   };
   void DoListItemChanged(UINT listControlID, const DString &strKey, bool bIsNewItem, bool bIsDummyItem);
   bool GetOverrideItemString(long lSubstituteId, const DString &dstrColumnKey, DString &dstrOut);
   void ControlUpdated(UINT controlID, const DString &dstrValue);

   void showHideFlatPercentControls (const DString &dstrFlatPercent);

private:
   void DisplayByEntityType();
   void EnableSplitCommission(bool enable);
   LRESULT OpenBrokerListDlg(WPARAM, LPARAM);
   LRESULT OpenBranchListDlg(WPARAM, LPARAM);
   LRESULT OpenSlsRepListDlg(WPARAM, LPARAM);

   DString m_dstrCaller,
      m_dstrSplitComm,
      m_dstrTransactionNumber,
      m_dstrTransactionTypeDesc,
      m_dstrAllocationListKey,
      m_dstrSplitCommListKey,
      m_dstrFeeType;
   bool m_bIsInquiry,
      m_bIsSplitByRate;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/SplitCommissionsDlg.h-arc  $
//
//   Rev 1.17   Mar 03 2011 16:05:46   jankovii
//PET181943 FN01 - XMLPhase 2
//
//   Rev 1.16   Nov 27 2004 21:22:16   popescu
//PET 1117/06, trade processing
//
//   Rev 1.15   May 14 2003 11:16:18   popescu
//added extra param to the process layer, which is used to pass the key string of the current selected item in the allocations list, in order to set selection on it in split commission dialog
//
//   Rev 1.14   May 13 2003 10:07:36   popescu
//Split commission re-work
//
//   Rev 1.13   Mar 21 2003 18:41:10   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.12   Oct 09 2002 23:56:14   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.11   22 May 2002 19:16:28   PURDYECH
//BFData Implementation
//
//   Rev 1.10   May 03 2001 15:49:28   HERNANDO
//Added Parameters.
//
//   Rev 1.9   Mar 23 2001 15:08:50   HERNANDO
//Clean up; removed fns.
//
//   Rev 1.8   Mar 22 2001 18:32:58   HERNANDO
//Dialog changed to either split by Rate or Percent. 
//
//   Rev 1.7   Mar 22 2001 16:28:58   HERNANDO
//Check in for Winnie.
//
//   Rev 1.6   Mar 21 2001 18:38:00   HERNANDO
//Check in for Chin
//
//   Rev 1.5   Mar 20 2001 15:45:02   HSUCHIN
//implemented reset button, ensures split commission exists before being loaded.
//
//   Rev 1.4   Mar 19 2001 15:14:32   HSUCHIN
//pvcs error.. re check in
//
//   Rev 1.2   Mar 18 2001 17:59:18   HERNANDO
//development enhancements
//
//   Rev 1.0   Mar 13 2001 09:09:10   HSUCHIN
//Initial revision.
 * 
 *
 */
