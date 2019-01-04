#ifndef REGPLANTRANSFERDLG_H
#define REGPLANTRANSFERDLG_H
//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2005 by International Financial Data Services
//
//*****************************************************************************
//
// ^FILE   : RegPlanTransferDlg.h
// ^AUTHOR : Mihai Buzila
// ^DATE   : November 4, 2016
//
// ^CLASS    : RegPlanTransferDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : Handles the code for the RegPlanTransfer dialog
//
//
// -----------------------------------------------------------------------------
//

#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif

#ifndef DSTCOMMONFUNCTION_HPP
   #include <ifastcbo\DSTCommonFunction.hpp>
#endif

#ifndef DSTOLEDATETIME_H
   #include <uibase\DSTOleDateTime.h>
#endif

#include <ifastgui\ifasthistoricalinfo.hpp>

#if _MSC_VER > 1000
   #pragma once
#endif // _MSC_VER > 1000

//*******************************************************************************************
// RegPlanTransferDlg dialog
// The class EffectiveDateSort is definde for the sorting of CONTRACT_LIST by effective date


class RegPlanTransferDlg : public BaseMainDlg
{
// Construction
public:
   RegPlanTransferDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );

// Dialog Data
   //{{AFX_DATA(RegPlanTransferDlg)
   enum
   {
      IDD = IDD_REG_PLAN_TRANSFER
   };
   //}}AFX_DATA

   CButton m_ckbActiveOnly;

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(RegPlanTransferDlg)
public:
   virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:
   LRESULT OpenExternalInstitutionSearchDlg (WPARAM, LPARAM);
   LRESULT OpenFundClassListDlg( WPARAM, LPARAM );

   // Generated message map functions
   //{{AFX_MSG(RegPlanTransferDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnAdmDates();
   afx_msg void OnKillfocusDtpEffDate(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnAdd();
   afx_msg void OnCopy();
   afx_msg void OnBtnAddAlloc();
   afx_msg void OnBtnDeleteAlloc();
   afx_msg void OnDel();
   afx_msg void OnBtnHistorical();
   afx_msg void OnBtnReset();
   afx_msg void OnBtnMore();
   afx_msg void OnChkActiveOnly();

   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()

   /**
    * This method is invoked by the base architecture after OnInitDialog has 
    * completed.  This should be implemented for time intensive setup so that
    * the screen can display quickly and then do this processing.
    */
   void OnPostInitDialog();
   bool ListViewControlFilter( long lSubstituteId, const DString * );
   bool isCurrentRegPlanTransferRecordInactive ();

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
   virtual bool doRefresh( GenericInterface * /*rpGICaller*/, 
                           const I_CHAR * /*szOriginalCommand*/ );

   virtual bool GetOverrideItemString( long lSubstituteId, 
                                       const DString& ColumnKey, 
                                       DString& strOut );

   virtual bool GetDataForControl( UINT controlID,
                                   DString &strValueOut,
                                   bool bFormatted,
                                   int index ) const;

   bool SetDataFromControl( UINT controlID,
                            const DString &strValue,
                            bool bFormatted,
                            SEVERITY &sevRtn,
                            int index );

   void DoListItemChanged( UINT listControlID, 
                           const DString &strKey, 
                           bool bIsNewItem, 
                           bool bIsDummyItem );

   virtual void ControlUpdated( UINT controlID, const DString &strValue );

private:
   // private member functions
   void LoadContractInfo();

   void setTitleBar ( );

   void UpdateLatestItemStopDate();

   bool GetEffDateMinusOne( DString& dstrEffDate, 
                            DString& dstrEffDateMinusOne );

   // private member data
   DString m_dstrAccountNumber;
   DString m_dstrShareHoldNum;
   DString m_dstrKey;
   DString m_dstrTransIdEmpty;
   DString m_dstrOwnerName;
   DString m_dstrSpouseName;
   DString m_dstrAskDofBirthSp;
   DString m_dstrAskDofBirthEntity;
   bool    bEffDateChanged;
   bool    m_bNewCopyAdded;
   bool    isSelItemNew;
   bool    _bIsNew;
   int m_uiClassCodeDialogItem;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
//}}AFX_INSERT_LOCATION}}



#endif // !defined(REGPLANTRANSFERDLG_H)
