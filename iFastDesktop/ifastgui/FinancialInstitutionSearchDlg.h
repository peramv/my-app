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
// ^FILE   : FinancialInstitutionSearchDlg.h
// ^AUTHOR : Serban Popescu
// ^DATE   : October, 2003
//
// ^CLASS    : FinancialInstitutionSearchDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION :
//
// -----------------------------------------------------------------------------
//
//******************************************************************************

#include <ifastgui\BaseMainDlg.h>

/////////////////////////////////////////////////////////////////////////////
// FinancialInstitutionSearchDlg dialog
class FinancialInstitutionSearchDlg : public BaseMainDlg
{
// Construction
public:
   FinancialInstitutionSearchDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, 
      GenericInterface* pGIParent, const Command& rCommand);
   virtual bool GetOverrideItemString(long lSubstituteId, 
      const DString& ColumnKey, DString& strOut);

// Dialog Data
   //{{AFX_DATA(FinancialInstitutionSearchDlg)
   enum
   {
      IDD = IDD_FINANCIAL_INSTITUTION_SEARCH
   };
   // NOTE: the ClassWizard will add data members here
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(FinancialInstitutionSearchDlg)
protected:
   //}}AFX_VIRTUAL

// Implementation
protected:
   void OnPostInitDialog();

   virtual SEVERITY doInit();
   virtual bool doRefresh(
      GenericInterface *rpGICaller, 
      const I_CHAR *szOriginalCommand);
   virtual void PostOk (bool bOkay);
   virtual void ControlUpdated(UINT controlID, const DString &strValue);

// Generated message map functions
//{{AFX_MSG(FinancialInstitutionSearchDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnSearch();
   afx_msg void OnDblclkLvFI (NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnBtnMore();
//}}AFX_MSG
   DECLARE_MESSAGE_MAP()
private:
   void GetFullFIName (DString &name) const;
   void SetDlgCaption();
   DString m_dstrFICategory,
      m_dstrFIName;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/FinancialInstitutionSearchDlg.h-arc  $
//
//   Rev 1.1   Jan 20 2004 18:27:52   popescu
//PET 809, FN 13,
//part backing-out bank master, 
//display the bank name in the FinancialSearchDialog caption if searching for transits
//
//   Rev 1.0   Oct 04 2003 16:10:42   popescu
//Initial revision.
// Initial revision.
 *
 */

