#ifndef TRANSACTIONHISTORYDLG_H
#define TRANSACTIONHISTORYDLG_H
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
//    Copyright 2004 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : TransactionHistoryDlg.h
// ^AUTHOR : Zijian Ying
// ^DATE   : 03/11/1999
//
// ^CLASS    : TransactionHistoryDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif

#ifndef CTIMERLISTCTRL_H
   #include <uibase\CTimerListCtrl.h>
#endif

/**
 * Class that display the TransactionHistory screen.
 *
 * @author 
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 03/11/1999</dd></dl>
 * @version 0.1
 */

class TransactionHistoryDlg : public BaseMainDlg
{
// Construction
public:
   TransactionHistoryDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);

// Dialog Data
   //{{AFX_DATA(TransactionHistoryDlg)
   enum
   {
      IDD = IDD_TRANSACTIONS
   };
   CComboBox m_Activity;
   CComboBox m_Fund;
   CTimerListCtrl  m_TransDetail;
   CTimerListCtrl  m_lvReportView;
   CString m_FundCurrency;
   CString m_NetAmount;
   CString m_PreBalance;
   CString m_SettleDate;
   CString m_SettleInDate;
   int   m_rbHistory;
   CString m_BatchNum; // Order Batch Num
   CString  m_SettleBatchNum;
   CString m_TransNbr;
   CString m_FundLongName;
   CString m_BranchCode;
   CString m_BrokerCode;
   CString m_SlsrepCode;
   CString m_FundNumber;
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(TransactionHistoryDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:
   // Generated message map functions
   //{{AFX_MSG(TransactionHistoryDlg)
   afx_msg void OnRbHistory();
   afx_msg void OnRbPending();
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnMore();
   afx_msg void OnDblclkLvAttributes(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnItemchangedLvAttributes(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnBtnBrowse();
   afx_msg void OnSelendokCmbFund();
   afx_msg void OnSelendokCmbActivity();
   afx_msg void OnBtnAdmDates();
   afx_msg void OnBtnModify();
   afx_msg void OnBtnAwd();
   afx_msg void OnBtnSettlement();
	afx_msg void OnBtnSettlLocationInstr();	
	afx_msg void OnBtnDeductDetail();
	afx_msg void OnBtnInvSummary();
	afx_msg void OnBtnTransactionExternalLinks();
   afx_msg void OnBtnTransactionHistory();
   afx_msg void OnBtnInvClawbackInfo();
   afx_msg void OnBtnInvestInfo();
   afx_msg void OnBtnTrxnCancelation();
   afx_msg void OnBtnTrxnDilution();
   afx_msg void OnBtnReprint();
   afx_msg void OnBtnInternalLink();
	afx_msg void OnBtnSavingsDirective();
	afx_msg void OnBtnPaymentSearch();
   afx_msg void OnBtnPayInstruct();
   afx_msg void OnBtnHistory();
   afx_msg void OnBtnAuthorization();
   afx_msg void OnBtnBatch();
   afx_msg void OnBtnMultiSettlInstr();
   afx_msg void OnBtnRESPHist();
   afx_msg void OnBtnPaymentInfoFlag(); 
   afx_msg void OnBtnShareLot();
   afx_msg void OnBtnGuaranteeRules();
   afx_msg void OnBtnRDSPNotionalActivity();

   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()

   void OnPostInitDialog();

   virtual SEVERITY doInit();
   virtual bool doRefresh( GenericInterface * /*rpGICaller*/, 
                           const I_CHAR *); /*szOriginalCommand*/
   virtual bool Ok()
   {
      // just return true for now
      return(true);
   }

private:
    CString ALLFUND;
    CString cmAllActivities;
    CString cmCashDividends;
    CString cmTransactions;
    CString FundMode;
    bool m_bCanReenter;
    bool m_bFromRefresh;
    bool m_bIgnore;
    bool m_bMessageDisplayed;
    bool m_bIsPending;

    enum AWD_Active
    {
       NO_AWD = 0, AWD_SESSION, AWD_PORTAL
    } m_AwdActive;

    bool m_bFromSettlement;
    CStringList m_FundList;
    DString AccountNum,TransId,FundCode,NumEntry,ClassCode,ShareholderNum,AllFundMode;
    DString EntityId,TransType,TransNum,TradeDate, ReqTransid, InquiryOnly;
    DString PendingFundCode,PendingClassCode,PendingTransType,PendingTransNum,PendingTradeDate,PendingTrade;
    DString CrossPrcsGrossNetMethod;
    DString DisableInvInfo;
    DString DisableMsg;
    DString Reprint;
    DString TxnCancel;
    DString CallFrom;
	DString FromScr;
    bool bPopulateDetails;
    E_PROCESSTYPE procType;
    DString rebook_;
    DString OrgFund, OrgClass;
    DString dstrTransSeq,dstrPendingRid;
    bool m_bFromSettlementScreen;
   bool AreThereAllocationInThisPending();
   void ClearStaticText();
   int DisplayCashDiv(const DString *ty);
   void fillDisplayValTag(const BFContainerId& containerId, const BFFieldId &idCode, DString &fieldVal, DString &txtMsg);
   void DisplayCodeDesc( const BFContainerId& idList, const BFFieldId &idCode, const BFFieldId &idDesc, UINT FieldLabelId, int CodeType=0, bool bDisplayDash = true);
   void DisplayCodeDesc01( const BFContainerId& idList, const BFFieldId &idCode, const BFFieldId &idDesc, UINT FieldLabelId, DString& dstrRes, int CodeType=0);
   void DisplayTaxRates( const BFContainerId& idList, const BFFieldId &idCode, const BFFieldId &idDesc, UINT FieldLabelId );   		
   void DisplayItem( const BFContainerId& idList, const BFFieldId &idField, UINT FieldLabelId, int ItemType=0);
   void DisplayFeeRate(bool bIsFee);
   bool DisplayThisItem(DString& src, int ItemType=0);
   void DisplayTitle();
   int DisplayTransaction(const DString *ty);
   int GetActivity();
   void getFunandClass(CString& src, DString& fundCode, DString& fundClass);
   void getFundCurrency(DString& fundCode,DString& ClassCode,DString& out);
   void getFundName(DString& fundCode,DString& out);
   bool HighlightThisPending(DString& AccountNum,DString& FundCode,DString& ClassCode, DString& TransType,DString& TransNum, DString& TradeDate);
   bool IsAllFundMode();
   void makeFundClassString(DString& FundCode, DString& Class, CString& out);
   LRESULT OnUmCanReenter(WPARAM a=0L, LPARAM b=0L);
   void PopulateDetails();
   void PopulateFundCom();
   void PopulateMainList();
   void PopulatePendingDetails();
   void PopulatePendingList();
   void PopulateTransDetails();
   void PopulateTransDetailsEqualizationAmt( const bool bDisplayEqAmtAndFactor );
   void PopulateTransList();
   void ReplaceYandN(DString& str);
   void SetHeading();
   void SetPendingHeading();
   void SetPendingStaticText();
   void SetTransHeading();
   void SetTransStaticText();
   int WhichDlgShouldBeLaunched(long curSelItem);
   int WhichDlgShouldBeLaunchedPending(long curSelItem);
   int WhichDlgShouldBeLaunchedTrans(long curSelItem);
   LRESULT OnListViewItemChanged(WPARAM PreviousSelection, LPARAM ListIdentifier);
   bool isSelectionSpecified();
   void PrefixWithZero(DString& dstrAmount);
   void displayTransDec(const DString& dstrDecimalTypeDesc);
   void NSCCControlNumber (bool isPending = false);
   void adjustGrossNet( DString &strGrossNetMethod );
   void OnDblClickedSourceOfFundsChecked();
   void DisplayResponseRequiredValueInAttributeList(const BFContainerId& idContainer);

	void enableSettlementLocInstr( const BFContainerId& idContainer, const BFFieldId &idCodeAccountTo );
	void enableShareLotButton();
   bool isTransactionCancelled();

   class DateMap_Compare
   {
	public:
	   DateMap_Compare() {}
	   bool operator() ( const DString& Key1, const DString& Key2 ) const;

	private:
   }; 

   typedef std::map < DString, DString, DateMap_Compare > DATESORTINGMAP;
   DATESORTINGMAP DateSortingMap;
   DATESORTINGMAP::iterator DateSortingIter; 
   
   void displayADLCharge( const DString &dstrTransType );
   void enableAuthorizationButton (const BFContainerId& idContainer);
   void enableBatchButton (const BFContainerId& idContainer);
   void enableMultiSettlInstrButton (const BFContainerId& idContainer);
   void enableRESPHistButton ();
   void enablePaymentButton (const BFContainerId& idContainer);
   bool isMoneyMarketFund(const DString &fundCode);
   void enableRDSPNotionalActivityButton ();

	DString batch;
};
  

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/TransactionHistoryDlg.h-arc  $
 * 
 *    Rev 1.61   Mar 09 2012 18:05:20   dchatcha
 * P0186484 FN 05 - SEG Trade Processing.
 * 
 *    Rev 1.60   Jan 18 2012 16:45:12   wp040027
 * P0188394_Performance Fees - Launching valuation dtl/Sharelot Screens
 * 
 *    Rev 1.59   Dec 08 2011 21:28:48   wp040032
 * P0183989 - Money Market Non Receipt
 * 
 *    Rev 1.58   Aug 03 2011 11:20:48   wp040027
 * P0186774 - Mutual Fund Order Processing
 * 
 *    Rev 1.57   Dec 09 2010 15:18:56   jankovii
 * IN 2339013 - P0175778: Uptreaming QA testing
 * 
 *    Rev 1.56   May 13 2010 01:33:52   popescu
 * RESP-QESI fixes
 * 
 *    Rev 1.55   Aug 12 2009 12:06:52   jankovii
 * PET0164824 FN01 - Eiger iShares Orders and ETF Fields
 * 
 *    Rev 1.54   May 28 2009 06:39:58   wutipong
 * IN1608629 - Aimprod RTS error : Disable the settlement button on the trans history dialog only when the dialog is open from settlement dialog. -- Sync Up
 * 
 *    Rev 1.53   May 27 2009 15:05:58   jankovii
 * PET 159770 FN05 Auto Batching.
 * 
 *    Rev 1.52   May 22 2009 10:38:30   jankovii
 * PET 159770 FN05 Auto Batching.
 * 
 *    Rev 1.51   Mar 02 2009 10:03:06   jankovii
 * PET0159508 FN03 ESG In Cash Transfer 
 * 
 *    Rev 1.50   Jun 04 2008 09:10:38   wongsakw
 * PETP00524000_FN01 Pending Trades by Fund Class Field Modifications Report
 * 
 *    Rev 1.49   Jan 18 2008 11:30:52   daechach
 * IN#1123784,1133269 - Gross/Net field not populated in desktop modify screen , Pending transaction on Desktop unavailable
 * 
 *    Rev 1.48   14 Dec 2007 10:25:02   kovacsro
 * added new method to adjust GrossNet filed values
 * 
 *    Rev 1.47   Mar 14 2007 14:34:02   jankovii
 * PET 2292 FN01 - Switch Settlement.
 * 
 *    Rev 1.46   Sep 21 2006 01:51:08   popescu
 * STP PET 2217/13
 * 
 *    Rev 1.45   Aug 29 2006 16:40:12   fengyong
 * PET2192 FN17 - Add transaction detail button to payment search screen
 * 
 *    Rev 1.44   Aug 23 2006 14:53:42   fengyong
 * temp check in for PET 2192
 * 
 *    Rev 1.43   Mar 02 2006 16:30:36   jankovii
 * PET 2072 FN01- NSCC Control Number.
 * 
 *    Rev 1.42   Nov 29 2005 15:24:38   AGUILAAM
 * PET_1228_FN02: EUSD Phase 2
 * 
 *    Rev 1.41   Sep 20 2005 12:53:44   fengyong
 * Incident 402113 - In Transaction history screen:
 * All fund mode and select fund combo box, do not need check transId.
 * 
 *    Rev 1.40   Jul 08 2005 09:41:54   Yingbaol
 * PET1235,FN01:Transaction cancellation rebook
 * 
 *    Rev 1.39   May 30 2005 17:58:58   porteanm
 * PET OPC Confirm Reprint - Reprint/TxnCancel.
 * 
 *    Rev 1.38   May 20 2005 16:24:36   porteanm
 * PET OPC Confirm Reprint - Reprint button support.
 * 
 *    Rev 1.37   Mar 04 2005 17:18:46   Fengyong
 * PET1190 FN04 - TransCancel Tempery check in for other coder
 * 
 *    Rev 1.36   Mar 03 2005 14:35:16   aguilaam
 * PET1171_FN01: display view 330 details on Transaction Detail screen (history) EUSDSavings - others
 * 
 *    Rev 1.35   Feb 22 2005 16:33:36   hernando
 * PET1117 FN66-68 - Added DString DisableMsg and OnBtnMessage().
 * 
 *    Rev 1.34   Feb 17 2005 13:16:26   aguilaam
 * PET1198_FN01: LSIF Reason Code enhancement. 
 * 
 *    Rev 1.33   Sep 23 2004 12:21:58   HERNANDO
 * PET1094 FN08 - Added PopulateTransDetailsEqualizationAmt.
 * 
 *    Rev 1.32   Sep 07 2004 15:37:32   VADEANUM
 * PET 1094 FN4 - Activest Bank File Interface.
 * 
 *    Rev 1.31   May 14 2004 14:44:38   HERNANDO
 * PET1046 FN01 - Added parameter to disable Inventory Information button.
 * 
 *    Rev 1.30   Feb 23 2004 13:43:36   ZHANGCEL
 * PET1001_FN01: add function to launch Inventory Summary screen
 * 
 *    Rev 1.29   Feb 16 2004 10:59:36   ZHANGCEL
 * Sync up :PTS ticket 10026640: disable or enable Pending Trade Radio button base on the value of PendingTrade_4
 * 
 *    Rev 1.28   Feb 05 2004 10:20:30   VADEANUM
 * PET859 FN23 - ADL - Deductions and ADLFeeCharge on Transaction History
 * 
 *    Rev 1.27   Nov 25 2003 15:12:32   VADEANUM
 * PET892 FN1 - Trade Settlement Location support - modified signature for enableSettlementLocInstr( )
 * 
 *    Rev 1.26   Nov 25 2003 11:57:52   VADEANUM
 * PET892 FN1 - Trade Settlement Location support - added enableSettlementLocInstr( ).
 * 
 *    Rev 1.25   Nov 11 2003 13:11:58   VADEANUM
 * PET892 FN1 - Trade Settlement Location support.
 * 
 *    Rev 1.24   Oct 16 2003 12:38:40   FENGYONG
 * PTS 10017160 Sorting pending list in trasactionhistory
 * 
 *    Rev 1.23   Aug 25 2003 18:19:30   HERNANDO
 * Added PrefixWithZero.
 * 
 *    Rev 1.22   Mar 21 2003 18:42:00   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.21   Mar 03 2003 09:50:50   KOVACSRO
 * Added isSelectionSpecified.
 * 
 *    Rev 1.20   Dec 20 2002 14:27:16   HERNANDO
 * Changed DisplayTaxRates.
 * 
 *    Rev 1.19   Nov 06 2002 10:32:56   YINGBAOL
 * sync. up release 49
 * 
 *    Rev 1.18   Oct 09 2002 23:56:18   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.17   Sep 04 2002 19:04:02   HERNANDO
 * Added DisplayFeeRate.
 * 
 *    Rev 1.16   Aug 29 2002 12:57:30   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.15   Aug 26 2002 15:56:56   HERNANDO
 * Added DisplayTaxRates function.
 * 
 *    Rev 1.14   Aug 23 2002 19:02:22   HERNANDO
 * Added parameter to DisplayCodeDesc.
 * 
 *    Rev 1.13   Aug 20 2002 17:44:40   HERNANDO
 * Enhancement - Added m_SettleBatchNum for Static Text display.
 * 
 *    Rev 1.12   13 Jun 2002 14:41:10   YINGZ
 * add reqtransid to support settlement
 * 
 *    Rev 1.11   12 Jun 2002 16:32:30   YINGZ
 * add settlement btn on transhistory scr
 * 
 *    Rev 1.10   15 Feb 2002 11:36:06   KOVACSRO
 * using timer list control.
 * 
 *    Rev 1.9   Dec 10 2001 13:48:20   HERNANDO
 * Removed m_pAwdInterface; clean-up.
 * 
 *    Rev 1.8   Nov 13 2001 16:33:54   HERNANDO
 * Added m_pAwdInterface; replaced m_awd
 * 
 *    Rev 1.7   Jul 20 2001 14:28:38   HERNANDO
 * Added AWD History Button.  Look-up based on Transaction Number, Account Number, and Business Area.
 * 
 *    Rev 1.6   15 Apr 2001 13:03:24   HSUCHIN
 * added variable to store PROC_TYPE
 * 
 *    Rev 1.5   Mar 23 2001 12:33:10   HSUCHIN
 * passing list item key to transaction allocation dialog and minor bug fix
 * 
 *    Rev 1.4   Mar 05 2001 11:57:06   ZHANGCEL
 * Added new function OnBtnModify() for PendingTrade modification.
 * 
 *    Rev 1.3   Jul 31 2000 16:53:14   HUDAVID
 * added baycom number and other changes
 * 
 *    Rev 1.2   Apr 05 2000 13:52:32   DT24433
 * changed to use hasPermission
 * 
 *    Rev 1.1   Feb 15 2000 18:59:52   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 11:01:28   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.8   Aug 26 1999 17:45:20   DT24433
 * removed TrailingAndLeading
 * 
 *    Rev 1.7   Aug 05 1999 12:09:44   YINGZ
 * Japanese yen
 * 
 *    Rev 1.6   Jul 27 1999 14:21:38   YINGZ
 * change to display wirs/direct, good/bad
 * 
 *    Rev 1.5   Jul 22 1999 15:00:10   YINGZ
 * process amount and units in pending
 * 
 *    Rev 1.4   Jul 20 1999 14:24:24   YINGZ
 * ?
 * 
 *    Rev 1.3   Jul 19 1999 16:34:46   POPESCUS
 * Fixed user security access to the address book
 * 
 *    Rev 1.2   Jul 09 1999 16:34:56   YINGZ
 * restore allocation support
 * 
 *    Rev 1.1   Jul 08 1999 10:06:02   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */

#endif // TRANSACTIONHISTORYDLG_H
