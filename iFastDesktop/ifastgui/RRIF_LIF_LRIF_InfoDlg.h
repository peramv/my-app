#ifndef RRIF_LIF_LRIF_INFODLG_H
#define RRIF_LIF_LRIF_INFODLG_H
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
// ^FILE   : RRIF_LIF_LRIF_InfoDlg.h
// ^AUTHOR : Yakov Prager
// ^DATE   : 3/99
//
// ^CLASS    : RRIF_LIF_LRIF_InfoDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : Handles the code for the Remarks dialog
//******************************************************************************

#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif

#ifndef __AFXDTCTL_H__
   #include <afxdtctl.h>
#endif

#ifndef COMBOBASE_H
   #include <uibase\combobase.h>
#endif

#ifndef DSTDATETIMECTRL_H
   #include <uibase\DSTDateTimeCtrl.h>
#endif

#if _MSC_VER > 1000
   #pragma once
#endif // _MSC_VER > 1000
// RRIF_LIF_LRIF_InfoDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// RRIF_LIF_LRIF_InfoDlg dialog

class RRIF_LIF_LRIF_InfoDlg : public BaseMainDlg
{
// Construction
public:
   RRIF_LIF_LRIF_InfoDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, 
      GenericInterface* pGIParent, const Command& rCommand);

// Dialog Data
   //{{AFX_DATA(RRIF_LIF_LRIF_InfoDlg)
   enum
   {
      IDD = IDD_RRIF_LIF_LRIF
   };
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(RRIF_LIF_LRIF_InfoDlg)
public:
   virtual BOOL PreTranslateMessage(MSG* pMsg);
   LRESULT OpenIdentifyAccountsDlg( WPARAM,LPARAM );

protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(RRIF_LIF_LRIF_InfoDlg)
   afx_msg void OnBtnAddress();
   afx_msg void OnBtnAdmDates();
   afx_msg void OnBtnAllocation();
   afx_msg void OnBtnBank();
   afx_msg void OnBtnMinMax();
   afx_msg void OnBtnAdd();
   afx_msg void OnBtnDelete();
   afx_msg void OnBtnMore();
   virtual BOOL OnInitDialog();
   afx_msg void OnDestroy();
   afx_msg void OnBtnAddCopy();
   afx_msg void OnBtnReset(); 
   afx_msg void OnBtnCalculate();
   afx_msg void OnChkActiveOnly(); //added for CHG0041174

   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()

   /**
      * Loading entity list and first selection
      * This method is invoked by the base architecture after OnInitDialog has 
      * completed.  This should be implemented for time intensive setup so that
      * the screen can display quickly and then do this processing.
      */
   void OnPostInitDialog();

   bool ListViewControlFilter( long lSubstituteId, const DString *strKey = NULL  );//added for CHG0041174
   bool isCurrentRRIFRecordInactive ();//added for CHG0041174
   /**
     * Required implementation for the refresh method.  No refresh activity is
     * performed for this class.
     * @param rpGICaller - A reference pointer to the calling object.
     * @param szOriginalCommand - A string literal representing the original
     * command issuing the refresh (which may provide a hint on whether this
     * object needs to check for refresh).
     * @returns true if successful, call getErrors for errors if false
     */
   virtual bool doRefresh(GenericInterface *, const I_CHAR *);
   virtual void ControlUpdated(UINT controlID, const DString &strValue);

   //virtual void InitControl( UINT controlID );
   //virtual bool SetDataFromControl( UINT controlID, const DString &strValue, bool bFormatted, SEVERITY &sevRtn, int index );
   virtual bool GetDataForControl( UINT controlID, DString &strValueOut, bool bFormatted, int index   ) const;
   virtual void DoListItemChanged( UINT listControlID, const DString &strKey, bool bIsNewItem , bool bIsDummyItem);
   virtual bool GetOverrideItemString( long lSubstituteId, const DString &ColumnKey, DString &strOut);
   SEVERITY doInit(); 
   /**
      implement here any bussiness rules related to the buttons that were added for permission check 
      (add or delete buttons)
      return true if it should be disabled and false if it should be enabled
      DO NOT call EnableWindow() here
   * @param nID - the control's ID
   */
   bool doDisablePermCheckButton(UINT nID);
   /**
   implement here any bussiness rules related to any buttons that were NOT added for permission check
   example: GetDlgItem( IDC_BTN_RESET )->EnableWindow( FALSE );
   Do not enable/disable here buttons that were added for permission check
   this method is called just before CheckPermission returns
   */
   void doDisableNonPermButtons();
   /**
    if overwritten by derived class, return true if nID control should be disabled, otherwise return false
    * @param nID - the control's ID
    * @param bIsNew - current item is new
    */
   //bool doDisableControl(UINT nID, bool bIsNew);

   void tabSelectionChanged( UINT tabControlID, const DString& strPageName );
   virtual bool doDisableControl(UINT nID, bool bIsNew);
private:
   void ShowAddressBank(bool bAddressBank);
   void enableDateControl(bool bEnable);
   void DisplayPayOptionRelate();
   void displayScheduleFields();
   void hideControlsForGeneralInfoPaymentTab( bool bShow );
   void hideControlsForMiscInfoTab( bool bShow );
   void registerTabControls (bool bShow);
   void addStaticControls (void);
   void hideAllControlsOnMiscTab(void);

   CButton m_ckbActiveOnly; //added for CHG0041174
   HACCEL  m_hAccel;
   CFont*  m_pFont;
   DString m_strAccountNumber,
           m_strShareholderNum,
           m_strLastName,
           m_strFirstName;
   int     m_iCurrentPage;

};
#endif // !defined(AFX_RRIF_LIF_LRIF_INFODLG_H__155CC541_DF35_11D3_A398_005004146900__INCLUDED_)

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/RRIF_LIF_LRIF_InfoDlg.h-arc  $
 * 
 *    Rev 1.21   Feb 11 2010 17:04:50   dchatcha
 * IN# 1941146 - R95/96 - RRIF Payment screen view is incorrect, overlapping with second tab.
 * 
 *    Rev 1.20   Apr 23 2009 11:31:28   wutipong
 * PET157825 FN03 MISC RRIF GAPS
 * 
 *    Rev 1.19   Nov 24 2008 06:41:38   daechach
 * IN# 1212736 - DESKTOP issues with RRIF/LIF Screen Display - resolution, Introduced Tab control to RRIF screen.
*/
