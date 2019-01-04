#ifndef REGPLANTRANSFERSEARCHDLG_H
#define REGPLANTRANSFERSEARCHDLG_H
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
// ^FILE   : RegPlanTransferSearchDlg.h
// ^AUTHOR : Mihai Buzila
// ^DATE   : November 4, 2016
//
// ^CLASS    : RegPlanTransferSearchDlg
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
// RegPlanTransferSearchDlg dialog
// The class EffectiveDateSort is definde for the sorting of CONTRACT_LIST by effective date


class RegPlanTransferSearchDlg : public BaseMainDlg
{
// Construction
public:
   RegPlanTransferSearchDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand );

// Dialog Data
   //{{AFX_DATA(RegPlanTransferSearchDlg)
   enum
   {
      IDD = IDD_REG_PLAN_TRANSFER_SRCH
   };
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(RegPlanTransferSearchDlg)
public:
   virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(RegPlanTransferSearchDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnSearch();
   afx_msg void OnBtnRefresh();
   afx_msg void OnBtnMore();
   afx_msg void OnBtnBrowse();
   //}}AFX_MSG
   afx_msg void OnDblclkLvResults(NMHDR* pNMHDR, LRESULT* pResult);

   DECLARE_MESSAGE_MAP()

   /**
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
   virtual bool doRefresh( GenericInterface * /*rpGICaller*/, 
                           const I_CHAR * /*szOriginalCommand*/ );

   //virtual bool GetOverrideItemString( long lSubstituteId, 
   //                                    const DString& ColumnKey, 
   //                                    DString& strOut );

   //virtual bool GetDataForControl( UINT controlID,
   //                                DString &strValueOut,
   //                                bool bFormatted,
   //                                int index ) const;

   //bool SetDataFromControl( UINT controlID,
   //                         const DString &strValue,
   //                         bool bFormatted,
   //                         SEVERITY &sevRtn,
   //                         int index );

   void DoListItemChanged( UINT listControlID, 
                           const DString &strKey, 
                           bool bIsNewItem, 
                           bool bIsDummyItem );

   virtual void ControlUpdated( UINT controlID, const DString &strValue );
   void ShowSearchControls(DString dstrSearchType);

private:
   LRESULT OpenBrokerListDlg( WPARAM, LPARAM );
   LRESULT  OpenBranchListDlg( WPARAM, LPARAM );
   LRESULT  OpenSlsRepListDlg( WPARAM, LPARAM );
   LRESULT OpenExternalInstitutionSearchDlg (WPARAM, LPARAM);
   // private member data
   DString m_dstrKey;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
//}}AFX_INSERT_LOCATION}}



#endif // !defined(REGPLANTRANSFERSEARCHDLG_H)
