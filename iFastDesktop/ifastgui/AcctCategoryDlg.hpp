#ifndef ACCTCATEGDLG
#define ACCTCATEGDLG
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
// ^FILE   : AcctCategoryDlg.h
// ^AUTHOR : Robert Kovacs
// ^DATE   : 01/24/2003
//
// ^CLASS    : AcctCategoryDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : Account Category screen
//
//******************************************************************************

#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif

#if _MSC_VER > 1000
   #pragma once
#endif

#include <ifastgui\ifasthistoricalinfo.hpp>

class AcctCategoryDlg : public BaseMainDlg
{
// Construction
public:
   AcctCategoryDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
   ~AcctCategoryDlg();
   
   void SetDlgCaption();
// Dialog Data
   //{{AFX_DATA(AcctCategoryDlg)
   enum
   {
      IDD = IDD_ACCT_CATEGORY
   };
   //}}AFX_DATA

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(AcctCategoryDlg)
protected:
   //}}AFX_VIRTUAL

// Implementation
protected:
   // Generated message map functions
   //{{AFX_MSG(AcctCategoryDlg)
   afx_msg void OnBtnAdd();
   afx_msg void OnBtnDelete();
   afx_msg void OnBtnReset();
   afx_msg void OnBtnAdmin();
   afx_msg void OnBtnHistorical();
   //}}AFX_MSG
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
     * Required implementation for the refresh method.  
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
 
   virtual void ControlUpdated (UINT controlID, const DString &strValue); //fund on fund

   virtual void DoListItemChanged( UINT listControlID,
                                              const DString &strKey, 
                                              bool isNewItem,
                                              bool bIsDummyItem); //fund on fund
  
   virtual void DoPreListItemChanged(UINT listControlID, const DString &strKey, bool bIsNewItem, bool bIsDummyItem);


   bool doDisablePermCheckButton(UINT nID);
   bool ListViewControlFilter(long lSubstituteId, const DString *strKey);

private:
   
	bool m_bNewItem;
};

//{{AFX_INSERT_LOCATION
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
//}}AFX_INSERT_LOCATION

#endif 

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastgui/AcctCategoryDlg.hpp-arc  $
//
//   Rev 1.4   Dec 01 2010 04:35:24   dchatcha
//P0175716 FN02 - Client Name Redemption - EPA Auto Settlement.
//
//   Rev 1.3   Jan 12 2009 11:11:00   jankovii
//IN 1549377 Estate and Death of Notification acct category can only be added by the system
//
//   Rev 1.2   Oct 28 2008 05:04:46   phiwponp
//PET22486FN45 - Fund on Funds Account Report.
//
//   Rev 1.1   Mar 21 2003 18:30:54   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.0   Jan 24 2003 13:10:10   KOVACSRO
//Initial revision.

 */