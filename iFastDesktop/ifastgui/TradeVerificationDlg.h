#ifndef TRADEVERIFICATIONDLG_H
#define TRADEVERIFICATIONDLG_H
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
// ^FILE   : TradeVerificationDlg.h
// ^AUTHOR : Robbins Kuriakose
// ^DATE   : 21-Jul-2014
//
// ^CLASS    : TradeVerificationDlg
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
// TradeVerificationDlg dialog

class TradeVerificationDlg : public BaseMainDlg
{
// Construction
public:

   TradeVerificationDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
   ~TradeVerificationDlg();
   LRESULT OpenIdentifyAccountsDlg(WPARAM , LPARAM );
   LRESULT OpenFundClassListDlg( WPARAM, LPARAM );

// Dialog Data
   //{{AFX_DATA(TradeVerificationDlg)
   enum
   {
      IDD = IDD_TRADE_VERIFICATION
   };
   // NOTE: the ClassWizard will add data members here
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(TradeVerificationDlg)
public:

   virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:

   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   // Generated message map functions
   //{{AFX_MSG(TradeVerificationDlg)
   afx_msg void OnBtnReset();
   afx_msg void OnBtnMore();
   afx_msg void OnBtnDetails();
   afx_msg void OnBtnSearch();
   afx_msg void OnChkVerifyAll();
   afx_msg void OnChkDeleteAll();
	//}}AFX_MSG
   //afx_msg void OnDblclkLvResults(NMHDR* pNMHDR, LRESULT* pResult);

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
   void DoListItemChanged(
                              UINT listControlID,
                              const DString &strKey,
                              bool bIsNewItem ,
                              bool bIsDummyItem
                         );
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
  virtual bool PreOk();

private:

   DString getCurrentScreenType(){return m_strScreenType;};
   void addControls( );
   void showCriteria();
   void showResults();
 
   /**
   * @param bShowNetwork - if true, show Network related controls (and hide the edit box, date controls
   * else show the other controls (and hide Network related controls)
   */
   void showNetworkControls(bool bShowNetwork);
   void reInitEditSearch(const DString& strSearchUsing);
   void showFundClassSearchControls(bool bShowFundClassSearch);
   void showTransTypeSearchControls(bool bShowFundClassSearch);
   void enableFundClassControls(bool bShowFundClassControls);
   void enableSearchResultControls();
   virtual bool GetCellValue( UINT ctrlId, const DString &rowKey, const DString &colKey,
                              DString &dstrOut, bool bFormatted);
   virtual bool OnGridSetCellValue( UINT ctrlId,
                                    const DString &rowKey,
                                    const DString &colKey,
                                    const DString &strIn );
  LRESULT OnGridSelectionChanged( WPARAM,LPARAM )  ;
   void setGridUpdated( bool bUpdated )
   {
      _bGridUpdated = bUpdated;
   }
   void showPlatformSet(bool bShowPlatform);
   //Memeber variables
   DString m_strScreenType;
   UINT    m_uiIdentAccItem;
   BOOL    m_bVerifyAll, m_bDeleteAll, _bGridUpdated, _bTradeVerificationCtrlsAdded;
   void  setSerachCriteriaReadOnly(bool bReadOnly);
   bool   m_bIsFromGridLoading;
};
#endif

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/TradeVerificationDlg.h-arc  $//    Rev 1.0  July 21 2014
// Initial revision.
*/
