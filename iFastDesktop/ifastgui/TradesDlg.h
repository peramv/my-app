#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2000 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : TradesDlg.h
// ^AUTHOR : Serban Popescu
// ^DATE   : July 2004
//
// ^CLASS    : TradesDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
// -----------------------------------------------------------------------------
//
//******************************************************************************


#include <ifastgui\basemaindlg.h>

class DSTGridWnd;
class DSTTabCtrl;

class TradesDlg : public BaseMainDlg
{
public:
   // standard constructor
   TradesDlg ( CWnd* pParent, 
               GenericInterfaceContainer* pGIC, 
               GenericInterface* pGIParent, 
               const Command& rCommand);
   
// Dialog Data
   //{{AFX_DATA(TradesDlg)
   enum
   {
      IDD = IDD_TRADES2
   };
   //}}AFX_DATA

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(TradesDlg)
public:
   virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:
   virtual bool doSend ( GenericInterface *rpGICaller, 
                         const I_CHAR *szMessage);
   virtual bool doRefresh ( GenericInterface *rpGICaller, 
                            const I_CHAR *szOriginalCommand);
   virtual SEVERITY doInit();
   virtual void PostOk (bool okStatus);
   virtual void OnPostInitDialog();
   virtual void ControlUpdated ( UINT controlID, 
                                 const DString &strValue);
   virtual void GridControlUpdated ( UINT ctrlId,
                                    const DString &rowKey, 
                                    const DString &colKey,
                                    const DString &strNewValue, 
                                    bool bFormatted,
                                    SEVERITY nSeverity);
   virtual void tabSelectionChanged (  UINT tabControlID, 
                                       const DString &pageName);
   virtual void DoPreListItemChanged ( UINT listControlID,
                                       const DString &strKey,
                                       bool bIsNewItem,
                                       bool bIsDummyItem);
   virtual void DoListItemChanged ( UINT listControlID,
                                    const DString &strKey, 
                                    bool bIsNewItem,
                                    bool bIsDummyItem);
    virtual bool GetCellValue( UINT ctrlId,
                               const DString &rowKey,
                               const DString &colKey,
                               DString &strOut,
                               bool bFormatted);
   virtual bool OnGridSetCellValue ( UINT ctrlId, 
                                     const DString &rowKey, 
                                     const DString &colKey, 
                                     const DString &strIn);
   virtual bool SetCellValue( UINT ctrlId,
                              const DString &rowKey,
                              const DString &colKey,
                              const DString &strIn,
                              bool bFormatted,
                              SEVERITY &sevRtn);

   virtual void GetCellProperties ( UINT ctrlId, 
                                    const DString &rowKey, 
                                    const DString &colKey, 
                                    BFContainerId &idContainer,
                                    BFFieldId &idField,
                                    DString &listItemKey,
                                    int &nCellState,
                                    UINT &cellCtrlType, 
                                    int &nCtrlInitMode,
                                    BFFieldId &idSubstitution,
                                    DString &comboList, 
                                    DString &mask, 
                                    int& nComboSortingMode ,
									DString& dstrAllowedChar );

   virtual bool SetDataFromControl( UINT controlID,
                                    const DString &strValue,
                                    bool bFormatted,
                                    SEVERITY &sevRtn,
                                    int index = 0);

   virtual bool GetDataForControl(UINT controlID, 
                                  DString &dstrValueOut, 
                                  bool bFormatted, 
                                  int index = 0) const;

   virtual bool doDisablePermCheckButton (UINT nID);
   virtual void doDisableNonPermButtons ();

   // Generated message map functions
   //{{AFX_MSG(TradesDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnAdd();
   afx_msg void OnBtnDelete();
   afx_msg void OnBtnReset();
   afx_msg void OnBtnHistory();
   afx_msg void OnBtnBatch();
   afx_msg void OnBtnCloneAcct ();
   afx_msg void OnBtnInfoDetails();
   afx_msg void OnBtnFeesDetails();
   afx_msg void OnChkOverride();
   afx_msg void OnDblclkLvAllocations (NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnDblclkLvSplitCommissions (NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnKillFocusSettleDate (NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnChkOverrideTIS();
   afx_msg void OnChkOverrideCost();
   afx_msg void OnBtnAlertMessage();

   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
private:
   DSTGridWnd *m_pAttributesGrdWnd,
      *m_pFeesGrdWnd;
   DSTTabCtrl *m_pInfoTabCtrl,
      *m_pFeesTabCtrl;
   DString m_strMarket,
      m_accountNum,
      m_strCurrentTabInfoPage,
      m_strCurrentTabFeesPage,
      m_initialSettleDate,
      m_initialSettleInDate,
	  m_Caller,
	  m_tradeTransactionType,
	  m_initialCashDate;
   CWnd *m_pCWndF4Focus;
   bool m_bTradeListSelectionInProgress,
      m_bAllocationListSelectionInProgress,
      m_bSplitCommissionListSelectionInProgress,
      m_bRemarksPageRegistered,
      m_bRepInfoPageRegistered,
      m_bFeesPageRegistered,
      m_bSearchInProgress,
      m_bSettleDateKillFocusInProgress,
      m_popSalesRepCreateQuestion,
      m_bDilutionListSelectionInProgress,
      m_bMaturityInstrSelectionInProgress,
      m_bEUSDPageRegistered,
      m_bPayInstructSelectionInProgress,
	   m_bMultipleSettleLocSelectionInProgress,
	   m_bRESPBenefAllocationInProgress,
      m_bSettleDateOverriden,
      m_bRESPTransfersInProgress,
      m_bG1G2PageRegistered;
   bool m_bInvestmentDetailsListSelectionInProgress;
   bool m_bEstateAllocationListSelectionInProgress;

   void searchForAccounts ( const DString &searchUsing, 
                            const DString &firstValue,
                            const BFContainerId &idSearch,
                            UINT controlID);
//F4 helpers,  dialogs
   LRESULT OpenBrokerListDlg (WPARAM, LPARAM);
   LRESULT OpenBranchListDlg (WPARAM, LPARAM);
   LRESULT OpenSlsRepListDlg (WPARAM, LPARAM);
   LRESULT OpenAddrBookDlg (WPARAM, LPARAM);
   LRESULT OpenAccountSearchDlg (WPARAM, LPARAM);
   LRESULT OpenFundClassListDlg (WPARAM, LPARAM);
   LRESULT OpenAssocTransIdHelper (WPARAM, LPARAM);
   LRESULT OpenExternalInstitutionSearchDlg (WPARAM, LPARAM);
//convenience methods
   void show2Sides (const DString &transType);
   bool isOneSideTrade (const DString &transType);
   bool isOneSideTrade ();
   void resetCautionsCombo ( UINT comboLabelId,
                             UINT comboId);
   void fillCautionsCombo ( UINT comboLabelId,
                            UINT comboId,
                            const BFContainerId &shareholderContainerId,
                            const BFContainerId &accountContainerId,
                            const BFContainerId &acctCategoryListContainerId);
   void updateRepInfoPage ();
   bool updateBankingPage ();
   bool updateShareholderAddressPage ();
   bool updateSettleLocPage ();
   bool updateMultipleSettleLocPage ();
   bool updateBeneficiaryAllocationPage ();
   bool updatePSEEAPPage ();
   bool updateRESPTransferPage ();
   void updateRemarksPage ();
   void updateInfoTabCtrl (bool bSelectPageRepInfo);
   void updateFeesPage ();
   bool updateAllocationsPage ();
   bool updateSplitCommissionsPage ();
   bool updateTaxRatesPage ();
   void updateFeesTabCtrl (bool bSelectPageFees);
   bool updateGIAAttribPage ();
   bool updateEstateAllocationPage ();
   bool updateGIInvestmentsPage ();
   bool updateMaturityInstrPage ();
   void makeFreshDlg ();
   void updateNetworkIDExternalTransNum ();
   bool updateDilutionPage ();
   bool updateSavingsDirectivePage ();
   bool updatePayInstructPage ();
   void removeTabPage( UINT iPageName );
   bool updateG1G2Page ();
   void showG1G2Controls(bool bShow);
   CString getCustomString(const BFContainerId& bFContainerId, const BFFieldId& idField );
   void openRemarkScreen();
   void openAlertMessageScreen();
   void openAlertMsgAndRemarkScreen();
   bool updateRDSPTransferPage ();
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/*$Log:   Y:/VCS/BF iFAST/ifastgui/TradesDlg.h-arc  $
 * 
 *    Rev 1.99   25 Jul 2012 17:46:50   if991250
 * P0186484 : Estate Allocation
 * 
 *    Rev 1.98   Mar 20 2012 16:43:58   if991250
 * IN 2885623 - GI Money Oout
 * 
 *    Rev 1.97   Jan 06 2012 13:40:14   if991250
 * IA money out
 * 
 *    Rev 1.96   Nov 15 2011 15:36:08   popescu
 * P0186477 FN03- GIA Maturity/Cash Sweep Instructions
 * 
 *    Rev 1.95   Oct 31 2011 17:11:36   popescu
 * P0186477/FN 03 - GIA Trading - Money In - added two new tabs to trade dlg
 * 
 *    Rev 1.94   Nov 22 2010 13:25:52   jankovii
 * PET175778 FN01 - Upstreaming Phase 2
 * 
 *    Rev 1.93   Apr 21 2010 01:23:34   popescu
 * RESP-QESI Resp transfer screen
 * 
 *    Rev 1.92   Apr 20 2010 00:56:58   popescu
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading - PSE/EAP   screen
 * 
 *    Rev 1.91   Apr 15 2010 18:10:32   popescu
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading - F4 Browser screen helper...
 * 
 *    Rev 1.90   Apr 13 2010 09:41:40   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_Trading
 * 
 *    Rev 1.89   Mar 08 2010 13:23:08   jankovii
 * PET165541_FN01_QESI - RESP Gap_Dsk_TRADING 
 * 
 *    Rev 1.88   Dec 02 2009 14:57:04   popescu
 * Prepare the terrain for incident 1780456, which will go in release 98 
 * 
 *    Rev 1.87   Aug 11 2009 13:50:10   jankovii
 * PET0164824 FN01 - Eiger iShares Orders and ETF Fields
 * 
 *    Rev 1.86   Jul 24 2009 01:21:24   dchatcha
 * PET 157825 - FN 13 - Dilution Allocation Enhancements, Sorting combo in grid.
 * 
 *    Rev 1.85   Dec 23 2008 17:17:46   wongsakw
 * IN1393123 -- Non same day Switches not being settled through cycle autosettlement
 * 
 * More changes based on Serban's suggestion.
 * 
 *    Rev 1.84   Dec 19 2008 17:10:54   wongsakw
 * IN1393123 Non same day switches not being settled through cycle autosettlement
 * 
 *    Rev 1.83   06 Feb 2008 11:06:20   kovacsro
 * IN#1053526 - settlm. location
 * 
 *    Rev 1.82   Jan 22 2008 15:40:08   yingz
 * fix incident 1110884 - bank infor display problem
 * 
 *    Rev 1.81   Sep 04 2007 16:38:38   jankovii
 * In #939902 - Settle In date is manualy modifed set SettleDateOverride to Y.
 * 
 *    Rev 1.80   Nov 08 2006 17:30:12   popescu
 * PET 2281/FN 01- copy account for TA 
 * 
 *    Rev 1.79   Aug 29 2006 18:16:12   popescu
 * STP PET 2192 FN10/11 - bulking netting redemption
 * 
 *    Rev 1.78   Nov 29 2005 15:24:34   AGUILAAM
 * PET_1228_FN02: EUSD Phase 2
 * 
 *    Rev 1.77   Jul 07 2005 12:17:34   AGUILAAM
 * PET1235 : dilution, part of Rebook/Cancellation
 * 
 *    Rev 1.76   May 26 2005 17:16:40   popescu
 * Incident 280865 - subsequent fix for sales rep pop-up question display issue.
 * 
 *    Rev 1.75   Feb 17 2005 16:46:08   popescu
 * Incident # 243445, fixed the fees grid refresh and renamed one  member variable to reflect the usage
 * 
 *    Rev 1.74   Jan 21 2005 11:19:16   hernando
 * PET910 - .NET/AWD Testing - Retrieve ObjectID from AWD and store it in fields.
 * 
 *    Rev 1.73   Dec 20 2004 18:27:40   popescu
 * PET 1117/56 refresh/clean the dialog after add/delete/reset
 * 
 *    Rev 1.72   Dec 09 2004 12:37:56   popescu
 * PET 1117/56, more fees work /pending trade
 * 
 *    Rev 1.71   Dec 07 2004 01:38:20   popescu
 * PET 1117/56 trades processing/modify trade
 * 
 *    Rev 1.70   Nov 30 2004 07:53:42   popescu
 * PET 1117/06, made purchase total and OnBtnHistory active once again
 * 
 *    Rev 1.69   Nov 29 2004 20:31:06   popescu
 * PET 1117/06/56 fees/trades processing
 * 
 *    Rev 1.68   Nov 24 2004 21:36:52   popescu
 * PET 1117/06/56. trade processing, settle location
 * 
 *    Rev 1.67   Nov 17 2004 16:16:52   popescu
 * PET 1117/06, Trade processing
 * 
 *    Rev 1.66   Nov 16 2004 10:18:08   popescu
 * PTS 10030584, set SettleDateOverridden flag to Y, if user changes the SettleDate
 * 
 *    Rev 1.65   Nov 15 2004 11:42:40   popescu
 * PET 1117/06, synch .NET Changes
 * 
 *    Rev 1.64   Nov 07 2004 14:56:48   popescu
 * PET 1117/06, synch changes
//
//   Rev 1.7   Nov 04 2004 17:42:16   popescu
//PET 1117/06, Trade processing
//
//   Rev 1.6   Nov 02 2004 19:19:48   popescu
//PET 1117/06 Trade processing...
//
//   Rev 1.5   Oct 27 2004 11:27:12   popescu
//PET 1117/06
//
//   Rev 1.4   Oct 22 2004 19:59:06   popescu
//PET 1117/06, work in progress...
//
//   Rev 1.3   Oct 21 2004 06:29:46   popescu
//PET 1117/06 - Trade processing work in progress..
//
//   Rev 1.2   Oct 01 2004 19:25:54   popescu
//PET 1117/06, SSB Germany Trade processing
//
//   Rev 1.1   Sep 23 2004 16:01:12   popescu
//PET 1117/06 - Trade processing work in progress...
//
//   Rev 1.0   Aug 13 2004 18:58:26   popescu
//Initial revision.
 * 
//
*/

