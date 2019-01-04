#ifndef ACCRUALSDLG_H
#define ACCRUALSDLG_H
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
//    Copyright 2002 by International Financial, Inc.
//
//******************************************************************************
//
// ^FILE   : AccrualsDlg.h
// ^AUTHOR : 
// ^DATE   : Jan 04, 2002
//
// ^CLASS    : AccrualsDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif

#if _MSC_VER > 1000
   #pragma once
#endif // _MSC_VER > 1000

class AccrualsDlg : public BaseMainDlg
{

public:

//******************************************************************************
// Dialog Data
//******************************************************************************

   //{{AFX_DATA(InterestAccrualDlg)
   enum
   {
      IDD = IDD_ACCRUALS
   };   
   //}}AFX_DATA

//******************************************************************************
// Constructor
//******************************************************************************

   AccrualsDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);

//******************************************************************************
// Destructor
//******************************************************************************

   ~AccrualsDlg(); 

// Implementation
protected:

//******************************************************************************
// Overrides
// ClassWizard generated virtual function overrides
//******************************************************************************

   //{{AFX_VIRTUAL(InterestAccrualDlg)   
   virtual BOOL PreTranslateMessage(MSG* pMsg);
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

//******************************************************************************
// Generated message map functions
//******************************************************************************

   //{{AFX_MSG(InterestAccrualDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnSelchangeCmbAccrualType();
   afx_msg void OnBtnMore();
   afx_msg void OnBtnSearch();
   afx_msg void OnRbDetails();
   afx_msg void OnRbTotalsByFund();
   afx_msg void OnChkIncUnStlTrades();
   afx_msg void OnSetFocusSearchControls ();
   afx_msg void OnKillFocusClassControls();
   LRESULT OpenFundClassListDlg( WPARAM, LPARAM );
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()

//******************************************************************************
// Method to refresh dialog controls
// @param   GenericInterface *rpGICaller - pointer to the calling object
// @param   const I_CHAR *szOriginalCommand - Not used in this case, but 
//                      can be used to instruct special processing.
// @returns bool - true.
//******************************************************************************

   virtual bool doRefresh( GenericInterface * /*rpGICaller*/, 
                           const I_CHAR * /*szOriginalCommand*/ );

//******************************************************************************
// Override which will filter the Interest accruals list box based on the radio
// button selection.  If the Details Radio button is selected, then the list will
// only contain list items with Record Type other than I_("S").  If the totals by
// fund radio button is selected then only the items with record type I_("S") 
// will be shown.
// @param   long lSubstituteId - Which substituion list to filter, in this case
//                only the interest accruals will need filtering.
//          const DString *strKey - The key of the current list item.
// @returns bool - true if the item is to be shown.
//                 false if the item is to be hidden.
//******************************************************************************

   bool ListViewControlFilter( long lSubstituteId, const DString *strKey );

//******************************************************************************
// Overrides canCancel so that discard dialog does not show up.
// @returns bool - true.
//******************************************************************************
   virtual bool canCancel();

private:

//******************************************************************************
// All the control hookups are done in this procedure.  This is called by the 
// OnInitDialog function.
// @returns void.
//******************************************************************************

   void addControls( );

//******************************************************************************
// This function returns the list cbo id based on the selection in the accrual
// type combo box.
// @returns long - INTEREST_SEARCH_CRITERIA_CBO id
//                 MF_SEARCH_CRITERIA_CBO id
//                 MF_REBATE_SEARCH_CRITERIA_CBO id
//******************************************************************************

   const BFContainerId& getListContainer( bool bSummary = false );

//******************************************************************************
// This function returns the search criteria cbo id based on the selection in the  
// accrual type combo box.
// @returns long - INTEREST_SEARCH_CRITERIA_CBO id
//                 MF_SEARCH_CRITERIA_CBO id
//                 MF_REBATE_SEARCH_CRITERIA_CBO id
//******************************************************************************

   const BFContainerId& getSearchContainerId( );

//******************************************************************************
// Sets the radio buttons based on the Accrual Summary field stored in the 
// Accruals Search criteria cbo.
// @param   const BFContainerId& idContainer  - INTEREST_SEARCH_CRITERIA_CBO
//                               MF_SEARCH_CRITERIA_CBO
//                               MF_REBATE_SEARCH_CRITERIA_CBO
// @returns void.
//******************************************************************************

   void setRadioButtons( const BFContainerId& idContainer );

//******************************************************************************
// Hides the start date control for All Fund Mode.  Also used to show the
// start date control when a fund/class code is entered.
// @param   bool bHide - Hides start date ( true )
//                       Shows start date (false )
// @returns void.
//******************************************************************************

   void hideStartDate( bool bHide );

//******************************************************************************
// Set the controls to hook to the Interest Accrual Search Criteria CBO
// and the Interest Accruals CBO.
// @returns void.
//******************************************************************************

   void loadInterestAccuralSearch( );

//******************************************************************************
// Set the controls to hook to the Management Fee Accrual Search Criteria CBO
// and the Management Fee Accruals CBO.
// @returns void.
//******************************************************************************

   void loadManagementFeeSearch( );

//******************************************************************************
// Set the controls to hook to the Management Fee Rebate Accrual Search Criteria 
// CBO and the Management Fee Rebate Accruals CBO.
// @returns void.
//******************************************************************************

   void loadManagementFeeRebateSearch( );

//******************************************************************************
// Reconnects the summary controls to the correct list cbo.
// @param   const BFContainerId& idContainer - the container to attach the summary controls.
//******************************************************************************

   void reConnectControls( const BFContainerId& idContainer, UINT idList );  

//******************************************************************************
// This will reconnect all the controls related to the search criteria to the
// correct cbo.
// @param   const BFContainerId& idContainer - the Container to attach the search controls.
// @returns void.
//******************************************************************************

   void reConnectSearchControls( const BFContainerId& idContainer );

//******************************************************************************
// This procedure will show/hide the Fund Number edit box.   When the the Fund
// Number edit box is shown, a smaller version of the Fund Code box 
// ( IDC_EDT_FUND_CODE )is shown and the original Fund Code box 
// ( IDC_EDT_FUND_CODE2 ) is hidden.
// @param   bool bshowFundNbr - Fund Number box shown ( true )
//                              Fund Number box hidden ( false )
// @returns void.
//******************************************************************************

   void showFundNumberControl( bool bshowFundNbr );

//******************************************************************************
// This function returns the active list control id based on the selection in the  
// accrual type combo box.
// @returns long - IDC_LV_INTEREST_ACCRUED resource control id
//                 IDC_LV_MF_ACCRUED resource control id
//                 IDC_LV_MFR_ACCRUED resource control id
//******************************************************************************

   int getActiveListControlId();

//******************************************************************************
// This functions clears all the total field information during Accrual type 
// switches or selection of fund by details/totals
// @returns void.
//******************************************************************************

   void clearTotalsControls();

//******************************************************************************
// The purpose of this function is to repopulated the FundCode, ClassCode and 
// StartDate information which is cleared up during switches between fund by 
// details/totals.
// @returns void.
//******************************************************************************

   void restoreSearchFundCodeValues();

   bool _bCanLuxMarket;             //True if the current Market is CAN or LUX
   UINT _currentFocusControl;       //UINT of the control in focus
   BOOL m_includeUnsettledTrades;   //True if check box Include Unsettl. is checked
   CButton m_btn_details;           //Member variable to details radio button.
   CButton m_btn_totals;            //Member variable to totals radio button.
   bool _bDetails;                  //Boolean variable to indicate whether details is selected
   DString _dstrMgmtFeeType;        //Stores the type of MF to display.
};

#endif

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log $
 */
