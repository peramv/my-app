#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2003 by International Financial, Inc.
//
//******************************************************************************
//
// ^FILE   : InventorySummaryDlg.h
// ^AUTHOR : Celia Zhang
// ^DATE   : Feb 18, 2004
//
// ^CLASS    : InventorySummaryDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************


#include <ifastgui\basemaindlg.h>
#include <ifastgui\ifasthistoricalinfo.hpp>
#include <uibase\ifdslistctrl.h>

#if _MSC_VER > 1000
   #pragma once
#endif // _MSC_VER > 1000

class InventorySummaryDlg : public BaseMainDlg
{

public:

//******************************************************************************
// Dialog Data
//******************************************************************************

   //{{AFX_DATA(ReportDlg)
   enum
   {
      IDD = IDD_INVENTORY_SUMMARY
   };    
   //}}AFX_DATA

   //******************************************************************************
   // Constructor
   //******************************************************************************

   InventorySummaryDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);

   //******************************************************************************
   // Destructor
   //******************************************************************************

   ~InventorySummaryDlg(); 

// Implementation
protected:

   //******************************************************************************
   // Overrides
   // ClassWizard generated virtual function overrides
   //******************************************************************************

   //{{AFX_VIRTUAL(AccountContractDlg)   
   //virtual BOOL PreTranslateMessage(MSG* pMsg);
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   //******************************************************************************
   // Generated message map functions
   //******************************************************************************

   //{{AFX_MSG(AccountContractDlg)
   virtual BOOL OnInitDialog();    
   afx_msg void OnBtnMore();
   afx_msg void OnBtnMoreDetail();
   afx_msg void OnChkActiveOnly();
   afx_msg void OnSelchangeCmbFund();
   afx_msg void OnBtnTransactionHistory();
   afx_msg void OnDblclkLvInventoryDetails(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnBtnInvClawbackInfo();
   afx_msg void OnChkInvSummarySortOrder();
   //}}AFX_MSG
   
   DECLARE_MESSAGE_MAP()

   SEVERITY doInit();

   void OnPostInitDialog();

   //******************************************************************************
   // Method to refresh dialog controls
   // @param   GenericInterface *rpGICaller - pointer to the calling object
   // @param   const I_CHAR *szOriginalCommand - Not used in this case, but 
   //                      can be used to instruct special processing.
   // @returns bool - true.
   //******************************************************************************

   virtual bool doRefresh( GenericInterface * /*rpGICaller*/, 
                           const I_CHAR * /*szOriginalCommand*/ );      

   void DoListItemChanged( UINT listControlID,
                           const DString &strKey,
                           bool bIsNewItem,
                           bool bIsDummyItem );

   bool GetDataForControl( UINT controlID,
                           DString &strValueOut,
                           bool bFormatted,
                           int index=0 ) const;

   void ControlUpdated( UINT controlID,
                        const DString &strValue);

   bool SetDataFromControl( UINT controlID,
                            const DString &strValue,
                            bool bFormatted,
                            SEVERITY &sevRtn,
                            int index=0 );

   void reSortListByCombo(void);

private:
   
   //******************************************************************************
   // All the control hookups are done in this procedure.  This is called by the 
   // OnInitDialog function.
   // @returns void.
   //******************************************************************************
   void addControls();
   void fillFundCombo();
   void DisplayLSIFControls();
   void defaultCheckBoxSortOrder();

   void hideRolloverQualificationDate(IFDSListBase* const pBaseCtrl);
   DString _dstrFundCode;  // Initial fund code
   DString _dstrClassCode; // Initial class code

   bool m_bInventorySummaryListSelectionInProgress;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/InventorySummaryDlg.h-arc  $
//
//   Rev 1.4   25 Apr 2008 13:19:26   kovacsro
//IN#1112967 - fixed the fund name
//
//   Rev 1.3   Feb 17 2005 13:16:14   aguilaam
//PET1198_FN01: LSIF Reason Code enhancement. 
//
//   Rev 1.2   Jun 08 2004 13:59:44   HERNANDO
//PET1046 FN01 - Storing Fund and Class codes.
//
//   Rev 1.1   May 19 2004 17:51:30   HERNANDO
//PET1046 FN01 - Added LSIF/Inventory Details.
//
//   Rev 1.0   Feb 24 2004 10:22:56   ZHANGCEL
//Initial revision.
 */
