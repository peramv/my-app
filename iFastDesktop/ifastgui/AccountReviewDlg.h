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
// ^FILE   : AccountReviewDlg.h
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : AccountReviewDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : Handles the code for the AccountReview dialog
//
//******************************************************************************

#include <ifastgui\basemaindlg.h>

class AccountReviewDlg : public BaseMainDlg
{

public:

   AccountReviewDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
   ~AccountReviewDlg();

// Dialog Data
   //{{AFX_DATA(AccountReviewDlg)
   enum
   {
      IDD = IDD_ACCOUNTREVIEW
   };
   CButton m_BtnMore;
   //}}AFX_DATA

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(AccountReviewDlg)
   virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:
   // Generated message map functions
   //{{AFX_MSG(AccountReviewDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnAdmDates();
   afx_msg void OnBtnAdd();
   afx_msg void OnAccelAccountReviewlist();
   afx_msg void OnAccelDetails();
   afx_msg void OnBtnMore();
   afx_msg void OnBtnReset();
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
                         GenericInterface *rpGICaller, 
                         const I_CHAR *szOriginalCommand
                         );

   bool GetOverrideItemString(long lSubstituteId, const DString &dstrColumnKey, DString &dstrOut);
	void ControlUpdated ( UINT controlID, const DString &strValue);
   virtual void DoPreListItemChanged ( UINT listControlID,
                                       const DString &strKey,
                                       bool bIsNewItem,
                                       bool bIsDummyItem);
   virtual void DoListItemChanged ( UINT listControlID,
                                    const DString &strKey, 
                                    bool bIsNewItem,
                                    bool bIsDummyItem);

private:

   void DisplayCaption();

   DString m_dstrAccountNumber;
   DString m_dstrShrNum;

   HACCEL m_hAccel;
	bool m_bAccountReviewListSelectionInProgress;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/AccountReviewDlg.h-arc  $
//
//   Rev 1.6   Dec 07 2005 15:45:08   AGUILAAM
//IN 485796 - update record with blank actual review date will not be sent by Desktop; will be updated on the View side.
//
//   Rev 1.5   Mar 17 2005 14:12:50   aguilaam
//IN_234826: display shrnum, acctnum, entity owner name on acctreview screen
//
//   Rev 1.4   Mar 21 2003 18:30:44   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.3   Oct 09 2002 23:55:28   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.2   31 May 2002 14:02:28   HERNANDO
//Revised for Rel47.
//
//   Rev 1.1   22 May 2002 19:15:36   PURDYECH
//BFData Implementation
//
//   Rev 1.0   08 May 2002 18:12:34   HERNANDO
//Initial revision.
 * 
 */
