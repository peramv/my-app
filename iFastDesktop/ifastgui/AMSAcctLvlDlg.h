#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by IFDS, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1999 by IFDS, Inc.
//
//******************************************************************************
//
// ^FILE   : AMSAcctLvlDlg.h
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : AMSAcctLvlDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : Handles the code for the AMSAcctLvl dialog
//
//******************************************************************************

#include <ifastgui\basemaindlg.h>

class AMSAcctLvlDlg : public BaseMainDlg
{

public:

   AMSAcctLvlDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
   ~AMSAcctLvlDlg();

// Dialog Data
   //{{AFX_DATA(AMSAcctLvlDlg)
   enum
   {
      IDD = IDD_AMSACCTLVL
   };
   //}}AFX_DATA

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(AMSAcctLvlDlg)
   virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:
   // Generated message map functions
   //{{AFX_MSG(AMSAcctLvlDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnAddAms();
   afx_msg void OnBtnDelAms();
   afx_msg void OnBtnHistorical();
   afx_msg void OnBtnAdmDates();
   afx_msg void OnBtnAddAlloc();
   afx_msg void OnBtnDelAlloc();
   afx_msg void OnBtnReset();
   afx_msg void OnFreqOverrideCheck();
   afx_msg void OnKillfocusCmbAMSType();   
   afx_msg void OnKillfocusEdtAMSCode();   
   afx_msg void OnBtnAmsAssetInfo ();
   afx_msg void OnBtnDeltaAlloc();
   afx_msg void OnSelchangeTargetMixOpt();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()

   virtual SEVERITY doInit();

   void OnPostInitDialog();
   virtual bool doRefresh(GenericInterface *rpGICaller, const I_CHAR *szOriginalCommand );
   virtual void ControlUpdated( UINT controlID, const DString &strValue );
   bool SetDataFromControl( UINT controlID, const DString &dstrValue, 
                            bool bFormatted, SEVERITY &sevRtn, int iIndex );
   virtual bool GetDataForControl(UINT controlID, DString &strValueOut, bool bFormatted, int index ) const;
   virtual void DoPreListItemChanged ( UINT listControlID,
                                       const DString &strKey,
                                       bool bIsNewItem,
                                       bool bIsDummyItem);
	virtual void DoListItemChanged(UINT listControlID, const DString &strKey, bool bIsNewItem , bool bIsDummyItem);
	void doDisableNonPermButtons();
	bool EnableDeltaAllocation();
private:

   LRESULT OpenFundClassListDlg( WPARAM, LPARAM );
   LRESULT OpenAMSMstrListDlg( WPARAM, LPARAM );

   void DisplayCaption();
   void DisplayAmsTypeSensitiveControls( const DString &dstrValue );
   void DisplayAMSCodeRelatedControls();
   void DisplayAMSTypeRelatedControls();
   void RefreshFreq();
   void doDisableBankruptcyRelatedControls (bool bFlag); //IN2818924 - DSK_AMS Validation for CDIC
   bool getFundLimitedByBankuptcy();

   HACCEL m_hAccel;
   DString m_Caller;
   bool m_bAMSTypeReadOnly;
   bool m_bUserDefinedAMS,
      m_bAMSAcctLvlListSelectionInProgress;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/AMSAcctLvlDlg.h-arc  $
//
//   Rev 1.20   Jan 31 2012 08:06:46   panatcha
//IN2818924 - DSK_AMS Validation for CDIC
//
//   Rev 1.19   Nov 25 2010 14:03:46   jankovii
//PET175778FN01 - Upstreaming Phase 2
//
//   Rev 1.18   05 Nov 2007 09:08:40   kovacsro
//IN#1062810 - added support to disable buttons
//
//   Rev 1.17   12 Oct 2007 10:56:40   popescu
//Fixed allocation problem with the effective date.
//
//   Rev 1.16   Sep 28 2007 16:34:16   smithdav
//PET 2360  FN02 - Display AMSMaster frequency when FreqOverride is not selected.
//
//   Rev 1.15   18 Sep 2007 17:46:44   popescu
//AMS/GAP 2360-6 - integrating the AMS AssetInfo screen with Desktop
//
//   Rev 1.14   Jul 27 2007 11:31:36   smithdav
//PET2360 FN02 - Add admin dates button.
//
//   Rev 1.13   Jul 18 2007 09:36:20   smithdav
//PET2360 FN02
//
//   Rev 1.12   Jul 11 2007 16:21:52   smithdav
//PET 2360 FN02 - AMS - Interim changes
//
//   Rev 1.11   Feb 04 2005 14:41:08   porteanm
//PTS 10033798 - Undid changes for "Should this Account be rebalanced in the next cycle" support.
//
//   Rev 1.10   Feb 01 2005 11:00:04   porteanm
//PTS 10033798 - "Should this Account be rebalanced in the next cycle" support.
//
//   Rev 1.9   Aug 11 2003 13:25:00   YINGBAOL
//account level AMS enhancement for CIBC
//
//   Rev 1.8   Jul 04 2003 10:56:58   HERNANDO
//PTS 10019039 - Defensive programming.  Assuming AMS Code is incorrect due to poor conversion.
//
//   Rev 1.7   Apr 25 2003 10:22:40   linmay
//PTS Ticket #10016353
//
//   Rev 1.6   Apr 24 2003 11:50:54   HERNANDO
//PTS 10016353.
//
//   Rev 1.5   Apr 22 2003 10:42:34   HERNANDO
//Added OnKillFocusCmbAMSType.
//
//   Rev 1.4   Apr 02 2003 11:56:08   HERNANDO
//Sync'd with 1.2.1.0
//
//   Rev 1.3   Mar 21 2003 18:32:32   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.2   Mar 18 2003 17:24:50   HERNANDO
//[updated] Dev-level revision for AMS.
//
//   Rev 1.1   Dec 02 2002 18:10:32   HERNANDO
//Renamed to OpenAMSMstrListDlg.
//
//   Rev 1.0   Nov 28 2002 18:34:34   HERNANDO
//Initial revision.
 * 
 */
