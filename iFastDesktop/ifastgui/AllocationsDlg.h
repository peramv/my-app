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
//    Copyright 1999 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : AllocationsDlg.h
// ^AUTHOR : Yakov Prager
// ^DATE   : 09/17/99
//
// ^CLASS    : AllocationsDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : Handles the code for the AllocationsDlg dialog
//
//
//
// ^METHOD : process()
//
// ^DESCRIPTION : Get the intial stuff. Gets parms from call global.
//                
//
// ^PARAMETERS  :
//    ^^STRINGVECTOR *display - Values to add to list, comes from
//                                CallDataPtr()->_psvParm1
//    ^^string title            - Title of dialog, comes from
//                                CallDataPtr()->_sParm1
//
// ^RETURNS     :
//    ^^ int - Index into string vector of item selected or -1
//             CallDataPtr->iParm1
//
// ^THROWS      :
//
// ^EXAMPLE     :
//
// -----------------------------------------------------------------------------
//
//******************************************************************************

#include <ifastgui\basemaindlg.h>
#include <ifastgui\allocationshelper.h>

/////////////////////////////////////////////////////////////////////////////
// AllocationsDlg dialog

class AllocationsDlg : public BaseMainDlg
{
// Construction
public:
   AllocationsDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);

private:
// Dialog Data
   //{{AFX_DATA(AllocationsDlg)
   enum
   {
      IDD = IDD_ALLOCATIONS
   };
   int m_rbUsage;
   BOOL  m_bReplaceAsDefault;
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(AllocationsDlg)
public:
   virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   virtual bool ListViewControlFilter( long lSubstituteId, const DString *strKey = NULL );

// Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(AllocationsDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnAccelAllocType();
   afx_msg void OnAccelFund();
   afx_msg void OnRbDefault();
   afx_msg void OnRbOneTime();
   afx_msg void OnBtnAddAcctAlloc();
   afx_msg void OnBtnAddFundAlloc();
   afx_msg void OnBtnAddShrAlloc();
   afx_msg void OnBtnDeleteAcctAlloc();
   afx_msg void OnBtnDeleteFundAlloc();
   afx_msg void OnBtnDeleteShrAlloc();
   afx_msg void OnBtnReset();
   afx_msg void OnAccelAcct();
   afx_msg void OnChkReplace();
   afx_msg void OnRbAutoTransfer();
   afx_msg void OnBtnAutoAddAcctAlloc();
   afx_msg void OnBtnAutoDeleteAcctAlloc();
   afx_msg void OnRbOneTimeTrade();
   afx_msg void OnSelchangeCmbAcctTax();
   afx_msg void OnBtnSplitCom();
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
   /**
      * This method should be overridden in the derived dialog if there is
      * OnOk processing to be done after the base processing.  Note that the OnOk
      * processing can no longer be "cancelled" at this point.  BaseMainDlg 
      * enforces its actions by making OnOk private.
      * @param bCancelStatus - true = Ok successful, false = Ok failed
      */
   //virtual void PostOk(
   //   bool /* bOkStatus */
   //   );
   /**
      * This method may be overridden to provide dialog specific handling
      * when list selection changes.  Note that the item will already be
      * the current item in the list (both list control and list container).
      * Avoid doing list operations during this method.
      * @param listControlID - Control ID of list changing selection
      * @param strKey - reference to string key for item.
      */
   virtual void DoListItemChanged( UINT listControlID, 
                                   const DString &strKey, bool bIsNewItem , bool bIsDummyItem);
   /**
      * This method should be overridden if there are any controls which the 
      * derived dialog supports outside of the base architecture.  This would
      * typically be if the derived dialog is supporting data not stored in the
      * parent process.  
      * The default implementation is to return false - no override.
      * @param controlID - Control to get data for.
      * @param strValueOut - String to return data for the control.
      * @param bFormatted - true = return in display format, false = return in
      * host format
      * @param index - index of field, if multiple fields for control
      * @returns true if override provided for the specified control, false
      * otherwise
      */
   virtual bool GetDataForControl( UINT controlID, DString &dstrValueOut,
                                   bool bFormatted, int index = 0 ) const;
   /**
      * This method should be overridden if there are any controls which the 
      * derived dialog supports outside of the base architecture.  This would
      * typicaly be if the derived dialog is supporting data not stored in the
      * parent process.  The data provided is in display format.
      * The default implementation is to return false - no override.
      * @param controlID - Control to get data for.
      * @param strValue - String with data to validate/save.
      * @param sevRtn - SEVERITY returned if override was true.
      * @param bFormatted - true = data in display format, false = data in
      * host format
      * @returns true if override provided for the specified control, false
      * otherwise
      */
   virtual bool SetDataFromControl( UINT controlID, const DString &strValue, 
                                    bool bFormatted, SEVERITY &sevRtn, int index );
   virtual bool GetOverrideItemString( long lSubstituteId, 
                                       const DString &dstrColumnKey, DString &dstrOut );
   virtual void ControlUpdated( UINT ControlID, const DString &strValue );
   virtual void CheckPermission();
   LRESULT OpenIdentifyAccountsDlg( WPARAM,LPARAM );
	virtual bool doDisablePermCheckButton(UINT nID);
   void showHideFrontEndLoadCommissionControls();


private:
   bool hasFrontEndLoadCommission();
   void fillAccTaxCMB();
   void CheckRifStatus();
   void switchAllocationType();
   void setRadioButton();                          // check radio button
   bool isRRifAlloction() const;  
   void loadOneTimeAllocation();
   void loadDefaultAllocation();
   void loadTradeOneTimeAllocation();

   void setupDefaultControls();
   void setupOnetimeATControls();
   void showControls();
   void LoadATAllocation();
   void enableDisableOneTimeAllocation(bool bEnable=true);
   void AccountLevelAllocationForATChanged(SEVERITY &sevRtn, const BFFieldId &idFiled,const DString& strNewValue );
   void displayAllocationGroups();
   void displayAllocations( int iAllocationGroupNum );
   void InitControl( UINT controlID );
   void initAcctTaxCombo(UINT iControlID);
   void getAcctTaxValue(const BFContainerId& idContainer,DString& dstrOutValue) const;

/*
  void initFundCombo( int iFundComboId );
  void initClassCombo( int iClassComboId );
   */
   void SetShareholderCaption();
   void SetTransactionCaption();
   void calcTotalPercent( const BFContainerId& idList, DString &dstrOutTotalPercent ) const;
   void calcTotalAmount( DString &dstrOutTotalAmount, const BFContainerId& idList = BF::NullContainerId ) const;
//CP20030319   void SetShrLevelData( const BFFieldId& idField, const DString &dstrValue, bool bFormatted ) const;
   void SetUserAccesFuncCode();
   void EnableAllButtons(bool bEnable);
   void checkAllocType();
   bool isFundGroupApplicable();

   //void InitReplaceAsDefaultVector();
   //void ReplaceMarkedSysAllocationsAsDefaults();

   void focusOnSelectedItem();
   LRESULT OpenFundClassListDlg( WPARAM, LPARAM );
   bool isFELCommApplicable();

   HACCEL m_hAccel;
   DString m_dstrMarket;
   //std::map< DString, bool > mapReplaceAsDefault;

   DString m_dstrAllocType;
   DString m_dstrAccountNum;
   DString m_strTransType;//PAC, SWP or AT - for permission check
   DString m_strTradeTransType;//ED , TR - for permission check
   DString m_dstrTransNum;
   DString _strTransType;//should replace m_strTransType and m_strTradeTransType, eventually
   DString _strAllocationListKey;
   bool _blNewShrItem;
   bool bRRIF;

   BFContainerId m_lOneTimeAllocList;
   BFContainerId m_lOneTimeList;
   UINT  m_uiClassCodeDialogItem;
   UINT m_uiAccItem;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

