#ifndef INVESTMENTHISDLG_H
#define INVESTMENTHISDLG_H

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
//    Copyright 2011 by International Financial Data Service
//
//******************************************************************************
//
// ^FILE   : InvestmentHistoryDlg.h
// ^AUTHOR :
// ^DATE   : 
//
// ^CLASS    : InvestmentHistoryDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : Handles the code for the Fund Info screen
//
// -----------------------------------------------------------------------------
//
//******************************************************************************

#include <ifastgui\BaseMainDlg.h>
#include <uibase\ifdslistctrl.h>

class LVInvestmentHistoryData : public IFDSListCtrlRowDataBase
{
public:
   virtual ~LVInvestmentHistoryData() {}
   virtual void update(BaseDlg* pDlg, IFDSListCtrl* pCtrl, const DString* pKey);

	DString dstrInvHisNumber;
	DString dstrInvHisStatus;
	DString dstrInvHisIntCalcMthd;
	DString dstrInvHisIntRateType;
	DString dstrInvHisTerm;
	DString dstrInvHisIntRate;
	DString dstrInvHisDepDate;
	DString dstrInvHisMatDate;
	DString dstrInvHisPrincipal;
	DString dstrInvHisIntFreq;
	DString dstrInvHisCurMktVal;
	DString dstrInvHisLastIntCrdDate;
	DString dstrInvHisAcurdToDate;
	DString dstrIntRateType;
    DString dstrAddlAmt;
}; 

class LVInvestmentHistoryAdapter : public IFDSListCtrlAdapter<LVInvestmentHistoryData>
{
public:
   // required overrides
   virtual int compare( IFDSListBase* pCtrl, int iSortColumn, bool bAscending, 
						RowData* pData1, RowData* pData2, LPARAM lParam1, LPARAM lParam2);

   virtual LRESULT onGetDispInfo(IFDSListCtrl* pCtrl, RowData* pData, LV_DISPINFO* pDispInfo);
}; 


class InvestmentHistoryDlg : public BaseMainDlg
{
public:
   /**
    * Standard dialog constructor for DSTC
    */
   InvestmentHistoryDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
// Dialog Data
   //{{AFX_DATA(SettlementDlg)
   enum
   {
      IDD = IDD_INVESTMENT_HISTORY_LIST
   };
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(SettlementDlg)

public:
   virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:
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
   /**
     * This method should be overridden in the derived dialog if there is
     * OnOk processing to be done after the base processing.  Note that the OnOk
     * processing can no longer be "cancelled" at this point.  BaseMainDlg 
     * enforces its actions by making OnOk private.
     * @param bCancelStatus - true = Ok successful, false = Ok failed
     */
   // Generated message map functions
   //{{AFX_MSG(SettlementDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnMaturityInt();
   afx_msg void OnBtnProgressiveInt();
   afx_msg void OnBtnIntSegments();
   afx_msg void OnBtnSearch();
   afx_msg void OnBtnMore();
   afx_msg void OnBtnMoreDetails();
   afx_msg void OnBtnMoreInterest();
   afx_msg void OnBtnRefresh();
   //}}AFX_MSG
	virtual void OnPostInitDialog();

	virtual void ControlUpdated (UINT controlID, const DString &strValue);
	virtual SEVERITY doInit();
	void DoListItemChanged ( UINT listControlID,
							 const DString &strKey, 
							 bool isNewItem,
							 bool bIsDummyItem);

	bool IsInputFieldsEmpty();
	void enableMaturityInstrs (bool bIsDummyItem);

   DECLARE_MESSAGE_MAP()

private:
   void SetDlgCaption ();
   void EnableControls(BOOL bEnable);

   LRESULT OpenFundClassListDlg(WPARAM wParam, LPARAM lParam);

   DString m_dstrAccountNum;
   UINT  m_uiClassCodeDialogItem;
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/InvestmentHistoryDlg.h-arc  $
//
//   Rev 1.10   Jul 06 2012 05:16:08   kitticha
//IN2932057 - Display the additional amount for investment history.
//
//   Rev 1.9   Apr 18 2012 15:29:40   wp040100
//IN # 2891939 - Added "Forced Indicator" column in Grid 1 and "Status" in Grid 3.
//
//   Rev 1.8   Feb 16 2012 12:01:10   jankovii
//Disabled maturity button when there are no records.
//
//   Rev 1.7   Feb 03 2012 10:43:10   jankovii
//IN 2813743 - P0186477FN03- Can't Access Maturity Instructions thru Investment Hist
//
//   Rev 1.6   Dec 19 2011 18:22:38   wp040100
//P0186477/FN03 - GIA - Investment History Changes
//
//   Rev 1.5   Dec 12 2011 18:25:58   wp040100
//P0186477/FN03 - GIA - Investment History - Integrated Fund Search
//
//   Rev 1.4   Dec 12 2011 12:01:38   wp040100
//P0186477/FN03 - GIA - Investment History Changes
//
//   Rev 1.3   Dec 01 2011 19:05:14   wp040100
//P0186477/FN03 - GIA - Investment History Changes
//
//   Rev 1.2   Nov 25 2011 17:41:24   wp040100
//P0186477/FN03 - GIA - Investment History Changes
 * 
 * 
// 
*/
