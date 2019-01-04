#if !defined RESPTRANSACTIONSDLG_H
   #define RESPTRANSACTIONSDLG_H
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
//    Copyright 2000 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : RESPTransactionsDlg.h
// ^AUTHOR : Dan Petolescu

// ^DATE   : 01/21/2000
//
// ^CLASS    : RESPTransactionsDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

   #include <ifastgui\BaseMainDlg.h>

   #if _MSC_VER > 1000
      #pragma once
   #endif // _MSC_VER > 1000


class RESPTransactionsDlg : public BaseMainDlg
{
// Construction
public:
   RESPTransactionsDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);

// Dialog Data
   //{{AFX_DATA(RESPTransactionsDlg)
   enum
   {
      IDD = IDD_RESPTRANSACTIONS
   };
   //}}AFX_DATA

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(RESPTransactionsDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(RESPTransactionsDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnAllocations ();
   afx_msg void OnBtnMore();
   afx_msg void OnBtnRESPTransactions();
   afx_msg void OnRbRESPHistory();
   afx_msg void OnRbRESPPending();
   afx_msg void OnBtnTransfer();
   afx_msg void OnBtnPSEEAP ();
   afx_msg void OnBtnSearch ();
   afx_msg void OnBtnReset ();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
   void OnPostInitDialog();
   virtual void ControlUpdated( UINT controlID, const DString &strValue );
   virtual bool GetOverrideItemString(long lSubstituteId, const DString& ColumnKey, DString& strOut);
   virtual SEVERITY doInit(); 
   virtual bool doRefresh( GenericInterface * /*rpGICaller*/, const I_CHAR * /*szOriginalCommand*/ );
   virtual void DoListItemChanged ( UINT listControlID,
                                    const DString &strKey, 
                                    bool bIsNewItem,
                                    bool bIsDummyItem);
private:
   DString  _strAccountNumber;
   DString  _strHistoryPendingMode;
   DString  _strShareholderNum;
   DString  _strCaller;

   void DisplayTitle();
   void enableBeneficiaryAllocation (const BFContainerId& idContainer);
   bool disableBeneAlloc (const BFContainerId& idContainer);
   void addControlsForSearchCriteria ();

   void enableTransfer (const BFContainerId& idContainer);
   void enablePSE (const BFContainerId& idContainer);
   void showControlsForTransType (const DString& transType = NULL_STRING);
   void showCriteria (bool bEnable);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif //RESPTRANSACTIONSDLG_H


//******************************************************************************
///              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/RESPTransactionsDlg.h-arc  $
 * 
 *    Rev 1.14   Nov 02 2010 14:24:54   jankovii
 * IN 2311933 - FN03 -  RESP Transaction History Trade date filters
 * 
 *    Rev 1.13   Aug 09 2010 16:14:22   jankovii
 * PET165541 FN03 SOC14 & SOC6
 * 
 *    Rev 1.12   Aug 06 2010 14:07:04   jankovii
 * PET165541 FN03 SOC14 & SOC6
 * 
 *    Rev 1.11   Jun 21 2010 17:20:42   popescu
 * Incident 2162449 - REL Pre99 Bene Alloc button grayed out on RESP Transaction History Screen
 * 
 *    Rev 1.10   May 13 2010 01:33:28   popescu
 * RESP-QESI fixes
 * 
 *    Rev 1.9   May 11 2010 08:19:42   popescu
 * QESI - RESP Fixes
 * 
 *    Rev 1.8   May 03 2010 19:41:02   popescu
 * PET165541_FN01_QESI - RESP Gap - small fixes
 * 
 *    Rev 1.7   Apr 21 2010 17:21:24   popescu
 * RESP-QESI Resp transfer screen
 * 
 *    Rev 1.6   Apr 15 2010 10:31:32   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.5   Apr 01 2010 00:48:18   popescu
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading - RESP Trading History Dialog
 * 
 *    Rev 1.4   Mar 29 2010 10:45:58   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.3   Mar 21 2003 18:40:22   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.2   Oct 09 2002 23:56:10   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.1   Mar 22 2000 09:02:50   PETOLESC
 * Added Tax Rates and RESP dialogs.
// 
//    Rev 1.4   Mar 02 2000 12:00:10   PETOLESC
// Corrected qa issues.
// 
//    Rev 1.3   Feb 16 2000 10:06:46   PETOLESC
// Included the list in MFAccount.
// 
//    Rev 1.2   Feb 10 2000 17:11:20   PETOLESC
// Removed RESPAccInfo buton.
// 
//    Rev 1.1   Feb 07 2000 11:02:32   PETOLESC
// Minor corrections and code cleaning.
 * 
 *
 */
