#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Canada, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2002 by International Financial Ltd.
//
//******************************************************************************
//
// ^FILE   : FeeParamSysDlg.h
// ^AUTHOR : Yingbao Li, May Lin
// ^DATE   : 01/09/03
//
// ^CLASS    : FeeParamSysDlg
// ^SUBCLASS : 
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************


#include <ifastgui\BaseMainDlg.h>
#include <ifastgui\ifasthistoricalinfo.hpp>

#if _MSC_VER > 1000
   #pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// FeeParamDlg dialog

class FeeParamSysDlg : public BaseMainDlg
{
// Construction
public:
   FeeParamSysDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
   ~FeeParamSysDlg();

// Dialog Data
   //{{AFX_DATA(FeeParamSysDlg)
   enum
   {
//      IDD = IDD_FEE_PARAM_SYS
      IDD = IDD_FEE_PARAM_FUNDS
   };
   // NOTE: the ClassWizard will add data members here
   //}}AFX_DATA

   virtual bool canCancel();
   virtual bool isKillWorkSessiononTxnError();

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(FeeParamDlg)
public:
   virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(FeeParamSysDlg)
   afx_msg void OnBtnReset();
   afx_msg void OnBtnAddFeeParam();
   afx_msg void OnBtnDelFeeParam();
   afx_msg void OnBtnMoreFeeParam();
   afx_msg void OnBtnAdmDates(); 
   afx_msg void OnBtnSearch();
   afx_msg void OnBtnHistoricalSystemFee();
   afx_msg void OnBtnHistoricalFeeScale();
   afx_msg void OnBtnDetails();
   afx_msg void OnBtnSearchAll();
   afx_msg void OnBtnSearchEffDate();
   afx_msg void OnBtnCopy() ;
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
   /**
    * Required implementation for the refresh method.  No refresh activity is
    * performed for this class.
    * @param rpGICaller - A reference pointer to the calling object.
    * @param szOriginalCommand - A string literal representing the original
    * command issuing the refresh (which may provide a hint on whether this
    * object needs to check for refresh).
    * @returns true if successful, call getErrors for errors if false
    */
   bool doRefresh( GenericInterface * /*rpGICaller*/, 
                   const I_CHAR * /*szOriginalCommand*/);
   /**
     * This method is invoked by the base architecture after OnInitDialog has 
     * completed.  This should be implemented for time intensive setup so that
     * the screen can display quickly and then do this processing.
     */
   void OnPostInitDialog();


   /**
     * This method is optional - override if subclass needs to implement.
     * The override should perform any initialization 
     * required, including getting parameters from InterProcessData (they get
     * cleared after this call).
     * @returns SEVERITY, check conditions if > NO_SEVERITY
     */
   SEVERITY doInit();

   bool doDisablePermCheckButton(UINT nID);

   virtual bool GetDataForControl( UINT controlID,
                                   DString &strValueOut,
                                   bool bFormatted,
                                   int index=0) const;
   virtual void ControlUpdated( UINT controlID,
                                const DString &strValue);
   virtual void DoPreListItemChanged ( UINT listControlID,
                                       const DString &strKey,
                                       bool bIsNewItem,
                                       bool bIsDummyItem);
   virtual void DoListItemChanged( UINT listControlID,
                                   const DString &strKey, 
                                   bool bIsNewItem ,
                                   bool bIsDummyItem);
   virtual bool SetDataFromControl( UINT controlID,
                                    const DString &strValue,
                                    bool bFormatted,
                                    SEVERITY &sevRtn,
                                    int index);
private:

   UINT  m_uiClassCodeDialogItem;
   LRESULT OpenFundClassListDlg( WPARAM, LPARAM );
   LRESULT OpenBrokerListDlg( WPARAM, LPARAM );
   LRESULT OpenBranchListDlg( WPARAM, LPARAM );
   LRESULT OpenSlsRepListDlg( WPARAM, LPARAM );


   void addControls ();
   void DispFeeTypeRelated ();
   void ConnectScaleControls ();
   void GetCommGroup (const DString &dstrDec, 
                      DString &dstrCode);
   void addControlsForSearchCriteria();
   void DisplaySearchRelated ();
   void EnableSearchCriteria (bool bEnable);
   void EnableControls (bool bEnable);
   void ReloadListControl();

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

   virtual bool OnGridSetCellValue( UINT ctrlId,
                                    const DString &rowKey,
                                    const DString &colKey,
                                    const DString &strIn);

   DString   m_dstrSearchBy;
   bool m_bScaleListSelectionInProgress;
   CFont *m_pFont;

   DSTTabCtrl *m_pFeeParamSysTabControl;
   int      m_rbSearchBy;
   DString  m_FeeModelCode;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/FeeParamSysDlg.h-arc  $
//
//   Rev 1.17   Dec 01 2011 00:18:24   popescu
//INA - Commission Work
//
//   Rev 1.16   Jul 24 2009 12:46:54   dchatcha
//PET 157825 - FN 13 - Dilution Allocation Enhancements, Sorting combo in grid.
//
//   Rev 1.15   Apr 26 2005 13:39:12   Fengyong
//#Incident 288919 - Allow longger broker name fully visible.
//
//   Rev 1.14   Jul 21 2003 15:10:26   linmay
//PTS Ticket #10014935
//
//   Rev 1.13   Mar 21 2003 18:36:30   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.12   Mar 10 2003 15:18:02   linmay
//added OpenBranchListDlg( WPARAM, LPARAM) ;
//added OpenSlsRepListDlg( WPARAM, LPARAM );
//
//   Rev 1.11   Mar 05 2003 11:29:52   PURDYECH
//Use IFastHistoricalInfo instead of deriving from IFastBaseMainDlg
//
//   Rev 1.10   Jan 31 2003 09:43:30   linmay
//move  isTheSameBusinessDate() to cbo layer
//
//   Rev 1.9   Jan 31 2003 09:28:16   linmay
//added  EnableHistoryControl(long ContainerId);
//
//   Rev 1.8   Jan 29 2003 16:22:30   popescu
//Added the historical button for FeeParamSysDlg and FeeParamDlg
//
//   Rev 1.7   Jan 29 2003 10:34:18   linmay
//added enableScaleControl()
//
//   Rev 1.6   Jan 20 2003 15:12:18   linmay
//added enablecontrols
//
//   Rev 1.5   Jan 17 2003 18:02:48   linmay
//added OpenBrokerListDlg
//
//   Rev 1.4   Jan 15 2003 16:21:52   linmay
//added onBtnSearch(), EnableSearchCriteria()
// 
*/


