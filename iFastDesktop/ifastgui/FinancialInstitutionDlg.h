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
// ^FILE   : FinancialInstitutionDlg.h
// ^AUTHOR : Serban Popescu
// ^DATE   : October, 2003
//
// ^CLASS    : FinancialInstitutionDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION :
//
// -----------------------------------------------------------------------------
//
//******************************************************************************

#include <ifastgui\BaseMainDlg.h>

/////////////////////////////////////////////////////////////////////////////
// FinancialInstitutionDlg dialog
class FinancialInstitutionDlg : public BaseMainDlg
{
// Construction
public:
   FinancialInstitutionDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, 
      GenericInterface* pGIParent, const Command& rCommand);
   virtual bool GetOverrideItemString (long lSubstituteId, 
      const DString& ColumnKey, DString& strOut);

// Dialog Data
   //{{AFX_DATA(FinancialInstitutionDlg)
   enum
   {
      IDD = IDD_FINANCIAL_INSTITUTIONS
   };
   // NOTE: the ClassWizard will add data members here
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(FinancialInstitutionDlg)
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
   virtual void ControlUpdated (UINT controlID, const DString &strValue);
   virtual void DoListItemChanged (UINT listControlID,
      const DString &strKey, bool bIsNewItem, bool bIsDummyItem);

// Generated message map functions
//{{AFX_MSG(FinancialInstitutionDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnDblclkLvFI (NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnBtnAdmDates();
   afx_msg void OnBtnAdd();
   afx_msg void OnBtnDelete();
   afx_msg void OnBtnReset();
   afx_msg void OnBtnMore();
   afx_msg void OnBtnTransits();
//}}AFX_MSG
   DECLARE_MESSAGE_MAP()
private:
   void SetDlgCaption();
   void modifyInstCodeControlStyle (const DString &category, 
      const DString &type);
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/FinancialInstitutionDlg.h-arc  $
//
//   Rev 1.1   Oct 24 2003 17:20:24   popescu
//CIBC PET 809, FN 13
//
//   Rev 1.0   Oct 04 2003 16:10:38   popescu
//Initial revision.
// Initial revision.
 *
 */

