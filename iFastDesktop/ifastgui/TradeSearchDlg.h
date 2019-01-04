#ifndef TRADESEARCHDLG_H
#define TRADESEARCHDLG_H
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
//    Copyright 2002 by DST Canada, Inc.
//
//******************************************************************************
//
// ^FILE   : TradeSearchDlg.h
// ^AUTHOR : Robert Kovacs
// ^DATE   : 02/25/2003
//
// ^CLASS    : TradeSearchDlg
// ^SUBCLASS : 
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************


#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif
#ifndef INCLUDED_VECTOR
   #define INCLUDED_VECTOR
   #include <vector>
#endif

#if _MSC_VER > 1000
   #pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// TradeSearchDlg dialog

class TradeSearchDlg : public BaseMainDlg
{
// Construction
public:
   TradeSearchDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
   ~TradeSearchDlg();
   LRESULT OpenIdentifyAccountsDlg(WPARAM , LPARAM );
	LRESULT OpenFundClassListDlg( WPARAM, LPARAM );

// Dialog Data
   //{{AFX_DATA(TradeSearchDlg)
   enum
   {
      IDD = IDD_TRADE_SEARCH
   };
   // NOTE: the ClassWizard will add data members here
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(TradeSearchDlg)
public:
   virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(TradeSearchDlg)
   afx_msg void OnBtnRefresh();
   afx_msg void OnBtnMore();
   afx_msg void OnBtnBrowse();
   afx_msg void OnBtnSearch();
   afx_msg void OnRBPending();
   afx_msg void OnRBTransaction();
   afx_msg void OnBtnMessage();
   afx_msg void OnBtnBulkCancel();  
	//}}AFX_MSG
   afx_msg void OnDblclkLvResults(NMHDR* pNMHDR, LRESULT* pResult);

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
   bool doRefresh(
                 GenericInterface * /*rpGICaller*/, 
                 const I_CHAR * /*szOriginalCommand*/
                 );
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
   
	/**
     * This method can be overridden to respond to data changes in a control.
     * @param controlID - ID of control that is changed.
     * @param strValue - unformatted value of change, this is not meaningful
     *   for a control associated with multiple fields at the same time.
     */
   void ControlUpdated(
                           UINT controlID,
                           const DString &strValue
                      );
	/**
   if overwritten by derived class, return true if nID control should be disabled, otherwise return false
   * @param nID - the control's ID
   * @param bIsNew - current item is new
   */
   bool doDisableControl(UINT nID, bool bIsNew);
   bool GetOverrideItemString(
                                     long lSubstituteId,
                                     const DString& ColumnKey,
                                     DString& strOut
                             );
   /**
     * This method may be overridden to provide dialog specific handling
     * when list selection changes.  Note that the item will already be
     * the current item in the list (both list control and list container) and
     * the associated controls will be loaded.  This call does occur prior to
     * any loading of sub-lists.  If you need to affect the loading of controls
     * (connect/disconnect associated controls) for this list use
     * DoPreListItemChanged instead.
     * Avoid doing list control operations during this method.
     * @param listControlID - Control ID of list changing selection
     * @param strKey - reference to string key for item.
     */
   void DoListItemChanged(
                              UINT listControlID,
                              const DString &strKey,
                              bool bIsNewItem ,
                              bool bIsDummyItem
                         );

private:

   DString getCurrentScreenType(){return m_strScreenType;};
   void addControls( );
	void showCriteria();
	void showResults();
   bool isPending();
   /**
   * @param bShowNetwork - if true, show Network related controls (and hide the edit box, date controls
   * else show the other controls (and hide Network related controls)
   */
   void showNetworkControls(bool bShowNetwork);
   void reInitEditSearch(const DString& strSearchUsing);
	void showAccountSearchControls(bool bShowAcctSearch);
	void showTradeDateSearchControls(bool bShowTradeDateSearch);
	void showFundClassSearchControls(bool bShowFundClassSearch);
	void enableFundClassControls(bool bShowFundClassControls);

	DString m_strScreenType;
	UINT    m_uiIdentAccItem;
};
#endif



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/TradeSearchDlg.h-arc  $
//
//   Rev 1.6   Jan 16 2012 13:46:38   wp040027
//P0188394_Performance Fees - Trade Search
//
//   Rev 1.5   Nov 08 2005 18:36:36   porteanm
//PET1286 FN01 - Bulk Cancellation.
//
//   Rev 1.4   Nov 04 2005 11:34:10   ZHANGCEL
//PET1286 FN01 -- Added TradeDate Search related functions
//
//   Rev 1.3   Feb 22 2005 14:51:28   hernando
//PET1117 FN66-68 - Added OnBtnMessage.
//
//   Rev 1.2   May 11 2004 11:34:02   ZHANGCEL
//PET1046_FN02 -- Trade Search by account enhancement
//
//   Rev 1.1   Mar 21 2003 18:41:50   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.0   Mar 03 2003 09:52:56   KOVACSRO
//Initial revision.

*/
