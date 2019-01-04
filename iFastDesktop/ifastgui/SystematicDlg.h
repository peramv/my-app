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
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : SystematicDlg.h
// ^AUTHOR : David Smith
// ^DATE   : March 11, 1999
//
// ^CLASS    : SystematicDlg
// ^SUBCLASS : IFastBaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

#include <ifastgui\BaseMainDlg.h>
#include <ifastgui\ifasthistoricalinfo.hpp>

// SystematicDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SystematicDlg dialog

class SystematicDlg : public BaseMainDlg
{
// Construction
public:
   SystematicDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);

   void GetCellProperties( UINT ctrlId, 
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


private:
   //{{AFX_DATA(SystematicDlg)
   enum
   {
      IDD = IDD_SYSTEMATIC
   };
   //}}AFX_DATA

   CButton m_ckbActiveOnly;


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(SystematicDlg)
public:
   virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:
   // Generated message map functions
   //{{AFX_MSG(SystematicDlg)
   afx_msg void OnBtnBank();
   afx_msg void OnBtnAllocation();
   afx_msg void OnBtnAdmDates();
   afx_msg void OnBtnNew();
   afx_msg void OnBtnDelete();
   afx_msg void OnBtnAddress();
   afx_msg void OnBtnReset();
   afx_msg void OnBtnAddCopy();
   afx_msg void OnItemchangingLvSystematic(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnClose();
   afx_msg void OnBtnSplitCom();
   afx_msg void OnBtnIndexing();
   afx_msg void OnKillfocusEdtMonthly();
   afx_msg void OnKillfocusCmbPayType();
   afx_msg void OnBtnHistorical();
   afx_msg void OnChkActiveOnly();

   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()

   BOOL OnInitDialog();

   /**
     * Loading entity list and first selection
     * This method is invoked by the base architecture after OnInitDialog has 
     * completed.  This should be implemented for time intensive setup so that
     * the screen can display quickly and then do this processing.
     */
   void OnPostInitDialog();

   /**
     * Get parameters from InterProcessData.
     * @returns SEVERITY, check conditions if > NO_SEVERITY
     */
   virtual SEVERITY doInit();
   /**
     * Required implementation for the refresh method.  No refresh activity is
     * performed for this class.
     * @param rpGICaller - A reference pointer to the calling object.
     * @param szOriginalCommand - A string literal representing the original
     * command issuing the refresh (which may provide a hint on whether this
     * object needs to check for refresh).
     * @returns true if successful, call getErrors for errors if false
     */
   virtual bool doRefresh(GenericInterface * rpGICaller, const I_CHAR * szOriginalCommand);

   void InitControl(UINT controlID);

   bool GetOverrideItemString(long lSubstituteId, const DString &dstrColumnKey, DString &dstrValueOut);
   virtual void ControlUpdated(UINT controlID, const DString &strValue);

   bool GetDataForControl(UINT controlID, DString &dstrValueOut, 
                          bool bFormatted, int index = 0) const;
   bool SetDataFromControl(UINT controlID, const DString &dstrValue, 
                           bool bFormatted, SEVERITY &sevRtn, int index);
   virtual void DoListItemChanged(UINT listControlID, const DString &strKey, bool bIsNewItem, bool bIsDummyItem);
   virtual void DoPreListItemChanged(UINT listControlID, const DString &strKey, bool bIsNewItem, bool bIsDummyItem);

   virtual bool PreOk();
   virtual void PostOk();
   virtual void PostCancel();   
   bool ListViewControlFilter( long lSubstituteId, const DString *strKey = NULL  );
   bool doDisableControl(UINT nID, bool bIsNew);
   /**
   implement here any bussiness rules related to the buttons that were added for permission check (add or delete buttons)
   return true if it should be disabled and false if it should be enabled
   DO NOT call EnableWindow() here
   * @param nID - the control's ID
   */
   bool doDisablePermCheckButton(UINT nID);

  virtual bool HideGridRowColumn(DString& dstrTag);

   void initAcctToCombo(UINT iControlID);

   //ticket 2404299 (REG_RL11.2/101 - PAC set up and delete issues) 
   bool doSend(GenericInterface *rpGICaller,const I_CHAR * szMessage);

private:

   void addControls();
   LRESULT ShowAcctList(WPARAM wParam, LPARAM lParam);

   void populateData();
   void populateAllocations();
   void refreshSystematicAlloctions();
   void enableDisableAllocation(const DString* pdstrAmountType = NULL);
   void enableDisableAllControls(bool bEnableFlag);
   void  ShowFromBankRelated( bool show );
   void setBankRelatedControls( int iShowBank );
   void setAddressRelatedControls( int iShowAddress );
   void fillPayTypeCombo();
   void fillAddress(const DString& dstrAddrCodeSel);
   void fillAddressCode();
   void  fillPlanCode();
   void showPayType();
   //void	getFrequency(DString& dstrOut, bool bFormat = false) const;

   //int	getMonthlyIndicator(DString& dstrOut) const;
   void getPayType(DString& dstrOut) const;
   void getAddrCodeDesc(DString& dstrOut) const;
   bool  isATTransfer() const;
   bool  isToFundClassAccountEmpty() const;

   void switchFrequency(const DString& dstrFrequency);
   void switchAllocAmountTypeColumn();
//CP20030319   void getDescByCode(long lSubstituteID, DString &dstrCode, DString& dstrDesc) const;
   void SetUserAccesFuncCode(bool bUseParam = false);
   void parsingPayType(const DString& dstrValueIn, DString& dstrTransType, DString& dstrPayType) const;
   void parsingCombinedField(const DString& dstrValueIn, 
                             DString& dstrField1, DString& dstrField2, 
                             const DString& dstrSep) const;

   SEVERITY  populateAtAcctAllocRelate(const BFFieldId &idField, const DString& strValue);

   //SEVERITY setMonthlyIndicator(const DString &dstrValueIn);
   void SetAtFromAlloctions();

//   bool confirmAcqFee(const DString& dstrFee = NULL_STRING);

//	void showAutomaticTransfer();
   void ShowMonthOrWeek(bool bMonth);
   void reinitGrid( const DString& payType );

   LRESULT OpenFundClassListDlg( WPARAM, LPARAM );
   LRESULT OpenIdentifyAccountsDlg( WPARAM,LPARAM );
   void OpenDemographicDlg();
   bool isCurrentSystematicRecordInactive ();

   //Current selected key of Systematic List
   DString  m_dstrCurKey;
   DString  m_dstrAccountNum;
   DString  m_dstrEntityID;

   BFContainerId  m_lContainerID;

   bool    m_bSystematicItemChange;
   bool    m_bAllocationItemChange;
   bool   m_bBtnAllocation;
   bool   m_bNewItem;
   bool    m_bSystematicItemChanging;
//   bool		m_bFeeLostFocus;
   bool    m_bAddCopy;   
   bool   m_bScreenClose;
   bool   m_bConfirmFee;
   bool   m_bSetMonthlyInd;
   bool    m_bTransTypeChange;
   bool    m_bInvAdvice;
   
   DString openeditemkeys;
   UINT     m_uiAccItem;
   CFont* m_pFont;

   UINT    m_uiDialogItem;

   BFFieldId m_idOldGridSubstitution;
   bool     m_bEsc;

   DString m_dstrCaller;
   DString m_dstrWorkType;

};

//{{AFX_INSERT_LOCATION
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
//}}AFX_INSERT_LOCATION

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/SystematicDlg.h-arc  $
 * 
 *    Rev 1.57   Feb 27 2011 21:21:30   panatcha
 * ticket 2404299 (REG_RL11.2/101 - PAC set up and delete issues)
 * 
 *    Rev 1.56   Nov 25 2010 14:05:06   jankovii
 * PET175778FN01 - Upstreaming Phase 2
 * 
 *    Rev 1.55   Jul 24 2009 01:31:42   dchatcha
 * PET 157825 - FN 13 - Dilution Allocation Enhancements, Sorting combo in grid.
 * 
 *    Rev 1.54   Jan 04 2005 11:02:50   yingbaol
 * PTS10036915:Implement HideGridRowColumn() method
 * 
 *    Rev 1.53   Sep 09 2004 12:08:44   VADEANUM
 * PET 1094 FN4 - Activest Bank File Interface.
 * 
 *    Rev 1.52   Aug 21 2003 09:48:22   HSUCHIN
 * change the way openDemographic dialog is executed so the paytype is not locked out
 * 
 *    Rev 1.51   Jul 11 2003 16:00:04   FENGYONG
 * PET 809, FN07 Show KYC screen FOR CIBC broker
 * 
 *    Rev 1.50   Mar 21 2003 18:41:28   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.49   Mar 05 2003 11:29:42   PURDYECH
 * Use IFastHistoricalInfo instead of deriving from IFastBaseMainDlg
 * 
 *    Rev 1.48   Jan 29 2003 14:57:24   popescu
 * Added Historical button for Systematic
 * 
 *    Rev 1.47   Oct 09 2002 23:56:16   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.46   Aug 29 2002 20:09:28   SMITHDAV
 * CellProperties fixes
 * 
 *    Rev 1.45   Aug 29 2002 18:16:10   SMITHDAV
 * Additional FieldId fixes.
 * 
 *    Rev 1.44   Aug 29 2002 12:57:26   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.43   Jan 08 2002 11:26:54   ZHANGCEL
 * Added a new data member m_bESC
 * 
 *    Rev 1.42   19 Dec 2001 10:56:58   KOVACSRO
 * Added a param. to setUserAccessFuncCode
 * 
 *    Rev 1.41   23 Nov 2001 14:26:52   KOVACSRO
 * perm check changes.
 * 
 *    Rev 1.40   19 Nov 2001 10:52:02   HSUCHIN
 * removed acqFee confirmation
 * 
 *    Rev 1.39   Sep 07 2001 15:33:20   ZHANGCEL
 * added second parameter in the ListViewControlFilter()
 * 
 *    Rev 1.38   Aug 23 2001 09:39:02   YINGBAOL
 * add OnKillfocusCmbPayType method
 * 
 *    Rev 1.37   Aug 16 2001 10:24:02   YINGBAOL
 * code clean
 * 
 *    Rev 1.36   Aug 09 2001 10:24:52   YINGBAOL
 * Transfer enhancement
 * 
 *    Rev 1.35   Jul 12 2001 17:08:48   HERNANDO
 * Added m_bInvAdvice.
 * 
 *    Rev 1.34   21 Jun 2001 11:09:22   KOVACSRO
 * moved logic for month indicator into CBO
 * 
 *    Rev 1.33   12 Jun 2001 16:59:10   YINGZ
 * more work
 * 
 *    Rev 1.32   11 Jun 2001 15:18:30   YINGZ
 * checking in for testing
 * 
 *    Rev 1.31   11 Jun 2001 10:19:22   YINGZ
 * add new dunctions
 * 
 *    Rev 1.30   05 Jun 2001 16:06:46   YINGZ
 * for others to compile
 * 
 *    Rev 1.29   31 May 2001 17:10:14   YINGZ
 * just for checking
 * 
 *    Rev 1.28   31 May 2001 11:16:02   YINGZ
 * check in for Chin
 * 
 *    Rev 1.27   17 May 2001 09:42:50   YINGZ
 * paytype fix
 * 
 *    Rev 1.26   10 May 2001 14:15:54   YINGZ
 * re arrange systematic
 * 
 *    Rev 1.25   19 Apr 2001 17:17:04   KOVACSRO
 * perm. check stuff.
 * 
 *    Rev 1.24   Apr 12 2001 19:12:10   HERNANDO
 * Added ShowFromBankRelated fn.
 * 
 *    Rev 1.23   Apr 03 2001 16:00:28   HUANGSHA
 * removed the obsolet routines, disable the TransType combo when the focus is lost
 * 
 *    Rev 1.22   30 Mar 2001 18:03:48   KOVACSRO
 * Added CheckPerm.
 * 
 *    Rev 1.21   Mar 19 2001 14:53:54   HSUCHIN
 * bug fixes and more validation rules added
 * 
 *    Rev 1.20   Dec 13 2000 14:55:48   KOVACSRO
 * Modified DoListItemChanged, DoPreListItemChanged
 * 
 *    Rev 1.19   Dec 01 2000 15:09:28   KOVACSRO
 * added SetUserAccessFuncCode().
 * 
 *    Rev 1.18   Sep 29 2000 18:03:46   HUANGSHA
 * added switchFrequency()
 * 
 *    Rev 1.17   Sep 22 2000 16:31:56   HUANGSHA
 * sync with M3 for allocation refreshing and Fee disable logic
 * 
 *    Rev 1.16   Sep 01 2000 16:38:38   HUANGSHA
 * Sync with M3
 * 
 *    Rev 1.15   Aug 04 2000 16:51:12   YINGBAOL
 * in some case, we need to  load control from CBO in order to make screen data consistent with CBO
 * 
 *    Rev 1.14   Jul 26 2000 11:19:06   HERNANDO
 * Set parameters (Code, Class, Number) for Fund Search
 * 
 *    Rev 1.13   Jul 26 2000 11:01:10   YINGBAOL
 * 
 *    Rev 1.12   Jun 30 2000 09:50:32   YINGBAOL
 * fix add copy and some other bugs
 * 
 *    Rev 1.11   Jun 27 2000 09:51:08   YINGBAOL
 * day of week added
 * 
 *    Rev 1.10   May 31 2000 16:46:10   YINGBAOL
 * temperally filter AT transtype systematic out
 * 
 *    Rev 1.9   May 19 2000 17:51:48   HSUCHIN
 * Changed Fund/Class combo to edit and implemented fund search
 * 
 *    Rev 1.8   May 19 2000 16:14:58   HUANGSHA
 * get it working properly
 * 
 *    Rev 1.7   May 01 2000 09:38:18   YINGBAOL
 * Automatic transfer added
 * 
 *    Rev 1.6   Apr 14 2000 12:06:10   YINGBAOL
 * Automatic Transfer has been added in the systematic screen
 * 
 *    Rev 1.5   Apr 05 2000 14:17:16   HSUCHIN
 * more M2 sync up
 * 
 *    Rev 1.4   Apr 04 2000 10:48:36   YINGBAOL
 * M2 Sync.
 * 
 *    Rev 1.3   Mar 21 2000 10:21:36   HSUCHIN
 * removed fund number from fund combo box
 * 
 *    Rev 1.2   Mar 19 2000 10:36:04   HSUCHIN
 * C2 sync up
 * 
 *    Rev 1.1   Feb 15 2000 18:59:46   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 11:01:26   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.23   Feb 02 2000 17:24:22   HUANGSHA
 * Fixed a problem for Allocation refresh
 * 
 *    Rev 1.22   Jan 27 2000 13:11:56   HUANGSHA
 * check in
 * 
 *    Rev 1.21   Jan 25 2000 17:11:32   HUANGSHA
 * Fixed bugs
 * 
 *    Rev 1.20   Jan 22 2000 17:27:20   HUANGSHA
 * made the changes required by BA
 * 
 *    Rev 1.19   Jan 21 2000 19:15:56   HUANGSHA
 * for test
 * 
 *    Rev 1.18   Jan 18 2000 17:44:12   HUANGSHA
 * fixed some bugs reported in SIT
 * 
 *    Rev 1.17   Jan 07 2000 16:43:26   HUANGSHA
 * Added address code refresh
 * 
 *    Rev 1.16   Dec 21 1999 16:45:44   HUANGSHA
 * made the changes for sysallocations
 * 
 *    Rev 1.15   Dec 17 1999 18:14:48   HUANGSHA
 * added Address refresh
 * 
 *    Rev 1.14   Dec 16 1999 18:29:08   HUANGSHA
 * Check in for testing
 * 
 *    Rev 1.13   Dec 14 1999 15:34:46   HUANGSHA
 * check in for compiling
 * 
 *    Rev 1.12   Nov 30 1999 09:50:04   HUANGSHA
 * check in temporarily
 * 
 *    Rev 1.11   Nov 27 1999 16:27:00   HUANGSHA
 * check in
 * 
 *    Rev 1.10   Nov 25 1999 15:18:58   HUANGSHA
 * check in for the initial m2 release
 * 
 *    Rev 1.9   Nov 25 1999 10:25:24   HUANGSHA
 * check in for test
 * 
 *    Rev 1.8   Nov 24 1999 17:21:30   HUANGSHA
 * check in for Allocation test
 * 
 *    Rev 1.7   Nov 24 1999 09:29:20   HUANGSHA
 * check in for test
 * 
 *    Rev 1.6   Nov 15 1999 14:42:46   HUANGSHA
 * temporary check in
 * 
 *    Rev 1.5   Oct 18 1999 15:18:50   HUANGSHA
 * Revision Correction
 * 
 *    Rev 1.3   Sep 23 1999 16:28:20   VASILEAD
 * Modified to match C1 requirements
 * 
 *    Rev 1.2   Jul 19 1999 12:44:06   POPESCUS
 * Added checks for user access rights for various buttons on the dialog
 * 
 *    Rev 1.1   Jul 08 1999 10:05:56   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
