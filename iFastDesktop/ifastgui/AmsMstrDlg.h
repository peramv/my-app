
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
// ^FILE   : AmsMstrDlg.h
// ^AUTHOR : Yingbao Li
// ^DATE   : Nov. 12,2002
//
// ^CLASS    : AmsMstrDlg
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
#include <ifastgui\ifasthistoricalinfo.hpp>

class AmsMstrDlg : public BaseMainDlg
{
public:
   /**
    * Standard dialog constructor for DSTC
    */
   AmsMstrDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
// Dialog Data
   //{{AFX_DATA(SettlementDlg)
   enum
   {
      IDD = IDD_AMSMST
   };
   //}}AFX_DATA


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

	virtual void DoListItemChanged(
                           UINT listControlID,
                           const DString &strKey,
                           bool bIsNewItem ,
                           bool bIsDummyItem
                           );

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
   afx_msg void OnBtnReset();
   afx_msg void OnBtnMore();
   afx_msg void OnBtnAddAms();
   afx_msg void OnBtnDelAms();
   afx_msg void OnBtnAddAlloc();
   afx_msg void OnBtnDelAlloc();
   afx_msg void OnBtnAdmDates();
   afx_msg void OnBtnLmtOverride();
   afx_msg void OnBtnHistorical();
   afx_msg void OnBtnAddCopy();
   afx_msg void onBtnDeltaAlloc();
   afx_msg void OnSelchangeTargetMixOpt();
   //}}AFX_MSG
   virtual void OnPostInitDialog();

   virtual void ControlUpdated( UINT controlID, const DString &strValue );
	virtual bool doDisablePermCheckButton(UINT nID);

   DECLARE_MESSAGE_MAP()
public:
		virtual bool filterListColumn(const BFFieldId &idSubstitute, const DString& dstrTag);

private:

   LRESULT OpenFundClassListDlg( WPARAM, LPARAM );
   void EnableControls( );
   void setDlgTitle();
   void ClearEnableChildControls( );
   void checkPermissionForInqUpdate();
   bool addControls();
   void DisplayAmsCurrencyThreshold();
   void DisplayAmsFundClass();
   void LoadAMSAllocationCombo();
   void EnableAllocationControls();
   void EnableAllocationEditControls(bool bShow);
   void DisplaySearchRelated();
   void addControlsForSearchCriteria();
   bool EnableDeltaAllocation();

   UINT    m_uiDialogItem;
   DString _dstrFromScr; 
   DString _dstrAmsCode;
   DString _dstrAmsType;
   DString _dstrEffectiveDate;
   DString _dstrCurrBusDate;
   bool m_bAddCopy; 
   bool m_bDummyItem;


};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/AmsMstrDlg.h-arc  $
//
//   Rev 1.10   Jul 06 2007 15:06:02   smithdav
//PET2360 FN02 - AMS - Make changes to Show/Hide for FOF
//
//   Rev 1.9   Aug 22 2003 13:28:04   linmay
//added logic for ams search
//
//   Rev 1.8   Jul 23 2003 11:12:08   linmay
//modified for cibc
//
//   Rev 1.7   Jul 18 2003 11:38:46   linmay
//modified for CIBC AMS
//
//   Rev 1.6   Apr 21 2003 09:52:48   YINGBAOL
//reimplement AMSType logic
//
//   Rev 1.5   Apr 09 2003 14:34:40   linmay
//fix bug for ticket#10014574
//
//   Rev 1.4   Mar 21 2003 18:32:42   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.3   Jan 02 2003 15:09:56   linmay
//added EnableAllocationControls
//
//   Rev 1.2   Dec 27 2002 11:03:58   linmay
//added type, name, allocation
//
//   Rev 1.1   Nov 29 2002 11:15:24   YINGBAOL
//added filterListColumn function
//
//   Rev 1.0   Nov 25 2002 10:14:04   YINGBAOL
//Initial Revision
//


*/