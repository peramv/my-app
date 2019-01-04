#ifndef SHRFAMILYDLG
#define SHRFAMILYDLG
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
// ^FILE   : ShrFamilyDlg.h
// ^AUTHOR : Claudio Sanchez
// ^DATE   : 1/203
//
// ^CLASS    : ShrFamilyDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : Handles the code for the Shareholder famly dialog
//
//******************************************************************************

#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif

#include <ifastgui\ifasthistoricalinfo.hpp>

#if _MSC_VER > 1000
   #pragma once
#endif

class ShrFamilyDlg : public BaseMainDlg
{
// Construction
public:
   ShrFamilyDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
   ~ShrFamilyDlg();
   
   void ShrFamilyDlg::SetDlgCaption();
// Dialog Data
   //{{AFX_DATA(ShrFamilyDlg)
   enum
   {
      IDD = IDD_SHRFAMILY
   };
   CButton m_BtnMore;
   //}}AFX_DATA

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(ShrFamilyDlg)
   virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:
   // Generated message map functions
   //{{AFX_MSG(ShrFamilyDlg)
   afx_msg void OnBtnChange();
   afx_msg void OnBtnAdd();
   afx_msg void OnBtnDelete();
   afx_msg void OnBtnReset();
   afx_msg void OnBtnHistorical();
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
   virtual bool doRefresh( GenericInterface *rpGICaller, 
                           const I_CHAR *szOriginalCommand );

private:
   LRESULT OpenBrokerListDlg( WPARAM, LPARAM );

private:
   DString  s_Name;
   DString  s_AcctNum;
   HACCEL   m_hAccel;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
//}}AFX_INSERT_LOCATION}}
#endif // SHRFAMILYDLG

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastgui/ShrFamilyDlg.hpp-arc  $
//
//   Rev 1.7   Dec 09 2011 11:33:20   dchatcha
//P0188902 FN02 - DYN Household Project
//
//   Rev 1.6   Nov 16 2011 19:30:34   dchatcha
//P0188902 FN02 - DYN Household Project
//
//   Rev 1.5   Nov 08 2011 12:10:54   dchatcha
//P0188902 FN02 - DYN Household Project
//
//   Rev 1.4   Mar 21 2003 18:41:00   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.3   Jan 15 2003 16:57:28   sanchez
//changes for setting caption of sharholder family dialog
//
//   Rev 1.2   Jan 14 2003 17:42:54   sanchez
//added  Revision Control Entries
 */