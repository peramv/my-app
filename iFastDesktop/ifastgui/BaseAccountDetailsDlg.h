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
// ^FILE   : BaseAccountDetailsDlg.h
// ^AUTHOR : AdrianVasile
// ^DATE   : 03/12/1999
//
// ^CLASS    : BaseAccountDetailsDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

/////////////////////////////////////////////////////////////////////////////

#include <ifastgui\basemaindlg.h>
#include <uibase\ctimerlistctrl.h>

/**
 * Class that display the Account Details screen.
 *
 * @author 
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 03/04/1999</dd></dl>
 * @version 0.1
 */
class BaseAccountDetailsDlg : public BaseMainDlg
{
// Construction
public:
   BaseAccountDetailsDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
   ~BaseAccountDetailsDlg();
   int lastFocus;
   void MoveDlg ();

// Dialog Data
   //{{AFX_DATA(BaseAccountDetailsDlg)
   enum
   {
      IDD = IDD_DETAILS
   };
   CButton m_ckbAllFunds;
   ListViewControl m_lvKanjiAddr;
   CComboBox m_cmbAddrSel;
   CButton m_btnAdd;
   CButton m_btnAdminDates;
   CListBox  m_lbOptions;
   CListBox  m_lbCautions;
   CListBox  m_lbAttributes;
   ListViewControl m_lvKanaAddr;
   ListViewControl m_lvEntitiesIds;
   ListViewControl m_lvTransactions;
   CTimerListCtrl  m_lvFunds;
   CTimerListCtrl  m_lvEntities;
   CTimerListCtrl  m_lvAccounts;
   int   m_rbEntities;
   int   m_rbTransacHist;
	CButton m_ckbActiveFunds;

   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(BaseAccountDetailsDlg)
public:
   virtual BOOL PreTranslateMessage(MSG* pMsg);
   virtual BOOL DestroyWindow();
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   bool doModelessSetFocus( GenericInterface * rpGICaller );
// Implementation
protected:
   // Generated message map functions
   //{{AFX_MSG(BaseAccountDetailsDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnRbEntities();
   afx_msg void OnRbShareholderAddresses();
   afx_msg void OnDblclkLbAttrib();
   afx_msg void OnDblclkLvHistoryTrades(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnDblclkLbOptions();
   afx_msg void OnRbTransHistory();
   afx_msg void OnRbPendingTrades();
   afx_msg void OnDblclkLbCautions();
   afx_msg void OnDblclkLvEntities(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnBtnAdminDates();
   afx_msg void OnSetfocusLbAttrib();
   afx_msg void OnSetfocusLbCautions();
   afx_msg void OnSetfocusLbOptions();
   afx_msg void OnSetfocusLvEntitiesIds(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnKillfocusLbAttrib();
   afx_msg void OnKillfocusLbCautions();
   afx_msg void OnKillfocusLbOptions();
   afx_msg void OnSetfocusLvAccounts(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnSetfocusLvEntities(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnSetfocusLvFunds(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnSetfocusLvHistoryTrades(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnSetfocusLvKanaAddr(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnSetfocusLvKanjiAddr(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnKillfocusLvEntities(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnKillfocusLvHistoryTrades(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnKillfocusLvEntitiesIds(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnAccelAccounts();
   afx_msg void OnAccelFund();
   afx_msg void OnAccelCautions();
   afx_msg void OnAccelOptions();
   afx_msg void OnAccelAttributes();
   afx_msg void OnKillfocusLvKanaAddr(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnKillfocusLvKanjiAddr(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnSelchangeCmbAddrSel();
   afx_msg void OnDblclkLvKanaAddr(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnDblclkLvKanjiAddr(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnMove(int x, int y);
   afx_msg void OnSelchangeLbAttrib();
   afx_msg void OnSelchangeLbCautions();
   afx_msg void OnSelchangeLbOptions();
   afx_msg void OnBtnNewAccount();
   afx_msg void OnBtnCloneAcct();
   afx_msg void OnBtnAddCOA();
   afx_msg void OnBtnAlertMessage();
   afx_msg void OnAllFunds();
   afx_msg void OnBtnAwd();
   afx_msg void OnClickLvAccounts(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnKillfocusLvFunds(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnBtnFundOfFunds();

   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()

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
   virtual bool doRefresh(
                         GenericInterface * /*rpGICaller*/, 
                         const I_CHAR * /*szOriginalCommand*/
                         );
   /*{  // Nothing to refresh here
      //return true;
   }    */
   /**
     * This is the implementation for OnOk processing to be done.  BaseMainDlg
     * enforces its actions by making OnOk private.
     * @returns a bool with true = perform Ok, false = stop process
     */
   virtual void PostCancel( bool /*bCancelStatus*/ );
   virtual void PostNcDestroy();
   void OnOK();

   bool GetOverrideItemString(long lSubstituteId, const DString &ColumnKey, DString &strOut);
//private:

protected:
   virtual void BtnAdminDates();
   virtual void RbPendingTrades();
   virtual void RbTransHistory();
   virtual void SetfocusLvEntitiesIds(NMHDR* pNMHDR, LRESULT* pResult);
   virtual void SetfocusLvHistoryTrades(NMHDR* pNMHDR, LRESULT* pResult);
   virtual void SetfocusLbOptions();
   virtual void SetfocusLbCautions();
   virtual void SetfocusLbAttrib();
   virtual void SetfocusLvFunds(NMHDR* pNMHDR, LRESULT* pResult);
   virtual void SetfocusLvEntities(NMHDR* pNMHDR, LRESULT* pResult);
   virtual void ItemchangedLvAccounts(int index);
   virtual void SetfocusLvAccounts(NMHDR* pNMHDR, LRESULT* pResult);
   virtual void fillAddressSelectList(){};

   void fillAccountInfo();
   void fillAccountList();
   void fillEntitiesIdsList();
   void fillEntitiesList();
   void fillFundList( );
   void fillTransactionsList();
   void fillPendingTradesList();
   virtual void fillShrAddressList();
   void fillCautionsList();
   void fillOptionsList();
   void fillAttributesList();
   void fillCallerInfo();
   void setGlobalInformation();
   void displayTitle();
   void SetTransHeading();
   void SetPendingHeading();
   bool BuildAge( const DString& birthDate, const DString& currDate, const DString& mask, DString& years, DString& months );
   bool AreThereAllocationInThisPending();
   void SetStatusBarMessage( CString& selStr, int code );
   void loadRRIFString();
   bool doSend( GenericInterface * rpGICaller, const I_CHAR * szMessage );
   bool canAddNewAccountOrClose( );
   LRESULT OnListViewItemChanged(WPARAM PreviousSelection, LPARAM ListIdentifier);
   void OnActiveFunds();
   LRESULT OnOpenAlertMessageBox(WPARAM wWordParam, LPARAM lLongParam );
   void openRemarkScreen();

	int lastFocusFunds;
   int lastFocusEntities;
   int lastFocusEntitiesIds;
   int lastFocusTransactions;
   //int lastFocusCautions;
   //int lastFocusOptions;
   //int lastFocusAttributes;
   CString lastFocusCautions;
   CString lastFocusOptions;
   CString lastFocusAttributes;
   int lastFocusKanaAddr;
   int lastFocusKanjiAddr;
   int TranPendingState;

   bool   flgTabPressed;
   
   enum AWD_Active
   {
      NO_AWD = 0, AWD_SESSION, AWD_PORTAL
   } m_AwdActive;

   HACCEL m_hAccel;
   //P0178584_FN01_NewPopUpMSG
   UINT getMailStageInfo(const DString& strValue);
   void fillChgMailInfoToCautionList(const DString& strValue, const DString &strType, CListBox*& pCautionsListBox, int &index);
   void displayMailInfoCaution(const DString& strValue, const DString &strType, CListBox*& pCautionsListBox, int &index);
   void openSTDChqAndRETMailAlertBox();
   void openAlertMessageScreen();
   void openAlertMsgAndRemarkScreen();
   //End - P0178584_FN01_NewPopUpMSG

   void openIWTNonTaxableAlertBox();
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
//}}AFX_INSERT_LOCATION}}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/BaseAccountDetailsDlg.h-arc  $
 * 
 *    Rev 1.31   Oct 28 2011 07:08:54   kitticha
 * PETP0188150 FN01 - Irish Withholding Tax Functionality.
 * 
 *    Rev 1.30   Jan 20 2011 03:00:00   panatcha
 * Update new fn: for P0178584 - Invesco Trimark New Popup messages
 * 
 *    Rev 1.29   Jan 19 2011 03:42:22   panatcha
 * Update according to Code Review for P0178584 - Invesco Trimark New Popup messages
 * 
 *    Rev 1.28   Jan 14 2011 04:48:22   panatcha
 * P0178584_FN01 - Invesco Trimark New Popup messages
 * 
 *    Rev 1.27   Nov 22 2010 13:41:38   jankovii
 * PET175778 FN01 - Upstreaming Phase 2
 * 
 *    Rev 1.26   Nov 06 2008 02:39:50   daechach
 * PET5517 FN71 Unclaimed Property Phase 2
 * 
 *    Rev 1.25   Oct 31 2008 16:04:14   wongsakw
 * IN1453089 Changes on the Unclaimed property screens
 * 
 *    Rev 1.24   Sep 22 2008 08:46:26   wongsakw
 * PET5517 FN71 Unclaimed Property
 * 
 *    Rev 1.23   Sep 21 2007 17:58:34   smithdav
 * PET 2360 FN02 - Launch Global AMS screen from AcctDetails for FOF funds.
 * 
 *    Rev 1.22   Nov 08 2006 17:30:00   popescu
 * PET 2281/FN 01- copy account for TA 
 * 
 *    Rev 1.21   Feb 23 2006 11:35:32   zhengcon
 * PET 2017_FN02--Partnerworld MT515 and Acct Level Default: remove method GetSubstitutionDescFromCode
 * 
 *    Rev 1.20   Feb 21 2006 10:37:52   zhengcon
 * PET 2017_FN02--Partnerworld MT515 and Acct Level Default
 * 
 *    Rev 1.19   Sep 01 2005 13:20:02   AGUILAAM
 * PET1250_FN07_Fund Merge: support display of active only or all  holdings based on generic control
 * 
 *    Rev 1.18   Mar 21 2003 18:33:22   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.17   Mar 05 2003 15:36:48   HSUCHIN
 * PTS 10014477 - bug where focus on fund history resets focus on fund selected list.
 * 
 *    Rev 1.16   Oct 09 2002 23:55:32   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.15   Jun 04 2002 11:16:38   ZHANGCEL
 * Added a new function: OnOk() to sove the problem of <Enter> key
 * 
 *    Rev 1.14   22 May 2002 19:15:48   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.13   04 Feb 2002 15:24:46   KOVACSRO
 * Timer List Control changes.
 * 
 *    Rev 1.12   Dec 07 2001 17:55:20   HERNANDO
 * Removed m_pAwdInterface.
 * 
 *    Rev 1.11   03 Dec 2001 13:03:48   KOVACSRO
 * added fillAddressSelectList().
 * 
 *    Rev 1.10   Nov 12 2001 17:00:48   HERNANDO
 * Replaced instantiated AwdInterface with pointer.
 * 
 *    Rev 1.9   Aug 21 2001 18:24:58   DINACORN
 * Removed IDC_BTN_CHANGE_BROWSE buttton;
 * Removed BrowseButton class.
 * 
 *    Rev 1.8   Jul 20 2001 15:22:42   HERNANDO
 * Clean up - Removed m_btnAWD.
 * 
 *    Rev 1.7   Mar 27 2001 14:28:26   YINGZ
 * add checking when user want to add new acct or close screen
 * 
 *    Rev 1.6   21 Feb 2001 18:13:10   KOVACSRO
 * Added doSend()
 * 
 *    Rev 1.5   Jan 16 2001 15:26:18   ZHANGCEL
 * Added a new function loadRRIFString()
 * 
 *    Rev 1.4   Dec 19 2000 11:02:30   ZHANGCEL
 * Added function OnClickLvAccounts() in order to add  or delete  RRIF_LIF_LRIF item in the Attribution list corresbondingly
 * 
 *    Rev 1.3   Nov 03 2000 11:15:52   DINACORN
 * Remove the logic for Change/Browse button in AccountDetails screen
 * 
 *    Rev 1.2   Jun 28 2000 14:05:54   HERNANDO
 * Implemented 'AWD History' Button on Details Dialog
 * 
 *    Rev 1.1   Feb 15 2000 18:59:12   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 11:01:08   SMITHDAV
 * Initial revision.
// 
//    Rev 1.11   Jan 25 2000 19:20:44   VASILEAD
// Refresh stuff
// 
//    Rev 1.10   Dec 10 1999 11:58:44   VASILEAD
// Added refresh support
// 
//    Rev 1.9   Dec 02 1999 14:42:54   YINGZ
// fix position problem
// 
//    Rev 1.8   Nov 30 1999 18:25:02   POPESCUS
// changes related to the NASU flow
// 
//    Rev 1.7   Nov 10 1999 13:46:26   VASILEAD
// Changed USER_GLOBALS to WORK_GLOBALS
// 
//    Rev 1.6   Oct 24 1999 16:26:58   VASILEAD
// Sync up with M2
// 
//    Rev 1.5   Sep 21 1999 14:20:34   VASILEAD
// Added functionality for All funds check box in Details screen
// 
//    Rev 1.4   Sep 20 1999 11:29:06   VASILEAD
// Changes to implement C1 requirements
// 
//    Rev 1.3   Sep 16 1999 16:52:56   VASILEAD
// Update Details dialog
// 
//    Rev 1.2   13 Sep 1999 13:52:34   HUANGSHA
// Synchronize with M1's changes
// 
//    Rev 1.1   Sep 03 1999 16:55:42   YINGZ
// base for details dlg
 * 
 *    Rev 1.9   Aug 09 1999 17:10:10   BUZILA
 * added COA call methods
 * 
 *    Rev 1.8   Jul 28 1999 13:35:12   VASILEAD
 * Add See allocations support for pending trades
 * 
 *    Rev 1.7   Jul 28 1999 10:41:56   YINGZ
 * allow cascade for all dlg
 * 
 *    Rev 1.6   Jul 26 1999 09:08:54   VASILEAD
 * Chage list box to combo box for address selection
 * 
 *    Rev 1.5   Jul 23 1999 15:04:54   VASILEAD
 * Changed the selection address from ListBox to ComboBox
 * 
 *    Rev 1.4   Jul 20 1999 18:18:38   VASILEAD
 * Set focus and hot key for Kana and Kanji address lists
 * 
 *    Rev 1.3   Jul 16 1999 13:03:02   VASILEAD
 * Double mask for the Amount field
 * 
 *    Rev 1.2   Jul 08 1999 10:58:42   VASILEAD
 * Put in the new java function for retriving the current date  formatting with the current locale
 * 
 *    Rev 1.1   Jul 08 1999 10:04:30   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
