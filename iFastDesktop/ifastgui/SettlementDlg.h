
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
// ^FILE   : SettlementDlg.h
// ^AUTHOR : Yingbao Li
// ^DATE   : May 24,2002
//
// ^CLASS    : SettlementDlg
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
class SettlementDlg : public BaseMainDlg
{
public:
   /**
    * Standard dialog constructor for DSTC
    */
   SettlementDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
// Dialog Data
   //{{AFX_DATA(SettlementDlg)
   enum
   {
      IDD = IDD_SETTLEMENT
   };
   CButton m_btnBank;
   //}}AFX_DATA
   BOOL m_bSettleOnly;
   BOOL m_bSettleAll;
   BOOL m_bExcludeStopSettle;
   bool m_bTotal;


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(SettlementDlg)
protected:
   virtual BOOL PreTranslateMessage(MSG* pMsg);
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
   virtual SEVERITY doInit();
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
   afx_msg void OnBtnSearch();
   afx_msg void OnBtnDetail();
   afx_msg void OnBtnReset();
   afx_msg void OnBtnMore();
   afx_msg void OnRdTotalSettle();
   afx_msg void OnRdTotal();
   afx_msg void OnChkSettleOnly();
   afx_msg void OnChkSettleAll();
   afx_msg void OnBtnBank();
   afx_msg void OnRdBeneficiary();
   afx_msg void OnRdCorrespondent();
   afx_msg void OnChkExcludeStopSettle();

   //}}AFX_MSG
   virtual void OnPostInitDialog();

   virtual void ControlUpdated( UINT controlID, const DString &strValue );

   virtual void GetCellProperties( UINT ctrlId, 
                                   const DString &rowKey, 
                                   const DString &colKey, 
                                   BFContainerId& idContainer,
                                   BFFieldId &idField,
                                   DString& listItemKey,
                                   int& nCellState,
                                   UINT& cellCtrlType, 
                                   int& nCtrlInitMode,
                                   BFFieldId &idSubstitution,
                                   DString& comboList, 
                                   DString& mask, 
                                   int& nComboSortingMode ,
								   DString& dstrAllowedChar );   

   virtual bool GetOverrideItemString(
                                     long lSubstituteId,
                                     const DString& ColumnKey,
                                     DString& strOut
                                     );
   virtual bool OnGridSetCellValue( UINT ctrlId,
                                    const DString &rowKey,
                                    const DString &colKey,
                                    const DString &strIn);

   virtual bool GetDataForControl(
                                 UINT controlID,
                                 DString &strValueOut,
                                 bool bFormatted,
                                 int index=0
                                 ) const;


   virtual bool GetCellValue( UINT ctrlId,
                              const DString &rowKey,
                              const DString &colKey,
                              DString &strOut,
                              bool bFormatted);
   virtual bool GridControlFilter( UINT ctrlId, const DString &rowKey );
   virtual bool PreOk();
   virtual bool ListViewControlFilter( long lSubstituteId, const DString *strKey = NULL );

   DECLARE_MESSAGE_MAP()

   private:
   LRESULT OpenFundClassListDlg( WPARAM, LPARAM );
   LRESULT OpenBrokerListDlg( WPARAM, LPARAM );
   LRESULT OpenSelectAddressDlg( WPARAM, LPARAM );
   LRESULT OpenIdnAccountsDlg( WPARAM,LPARAM );

   void DisplayBankAddress(bool bInitial = false  ); 
   void DisplaySearchRelated(  );
   void EnableSearchCriteria(bool bEnable);
   bool addControlsForSearchCriteria( );
   void addControlsForSettle();
   void loadAddressInfo();
   void EnableControls(bool bEnable);
   void setDlgTitle();
   void ClearEnableChildControls( );
   void checkPermissionForInqUpdate();
   void setGridUpdated( bool bUpdated )
   {
      _bGridUpdated = bUpdated;
   }
   bool isGridUpdated() {
      return _bGridUpdated;
   }

   UINT    m_uiDialogItem;
   void setupBankControls( bool bCorrespBank, const BFContainerId& idContainer );
   void clearBankInfo( );
   void lockRdCorrespondent();
   int _iMaxBankLabels;
   CButton m_btn_bankBene;
   CButton m_btn_bankCorr;
   DString _dstrFromScr;
   bool    _bGridUpdated;
   bool    m_bAlreadySearch;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/SettlementDlg.h-arc  $
//
//   Rev 1.21   Jul 24 2009 01:34:52   dchatcha
//PET 157825 - FN 13 - Dilution Allocation Enhancements, Sorting combo in grid.
//
//   Rev 1.20   Dec 02 2004 16:30:36   yingbaol
//PTS10010256:refresh count in  total list when reset button is clicked.
//
//   Rev 1.19   Sep 03 2003 11:20:52   YINGBAOL
//Filtre list item at GUI layer and solving reset issue
//
//   Rev 1.18   Mar 21 2003 18:40:50   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.17   Oct 09 2002 23:56:12   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.16   Aug 29 2002 20:09:28   SMITHDAV
//CellProperties fixes
//
//   Rev 1.15   Aug 29 2002 18:16:08   SMITHDAV
//Additional FieldId fixes.
//
//   Rev 1.14   Aug 16 2002 13:51:24   YINGBAOL
//check permission for Setttlement
//
//   Rev 1.13   Aug 09 2002 11:18:16   YINGBAOL
//add filtre function to total settle list
//
//   Rev 1.12   Aug 08 2002 11:17:46   KOVACSRO
//Release 48: Added bFormatted parameter to GetCellValue
//
//   Rev 1.11   Jul 05 2002 13:40:12   YINGBAOL
//add confirm settlement dialog
//
//   Rev 1.10   Jun 27 2002 13:25:54   YINGBAOL
//add  ClearEnableChildControls method
//
//   Rev 1.9   Jun 21 2002 13:14:42   YINGBAOL
//add  setDlgTitle
//
//   Rev 1.8   Jun 20 2002 14:10:48   YINGBAOL
//add F4 For account search
// 


*/