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
// ^FILE   : TransitsDlg.h
// ^AUTHOR : Serban Popescu
// ^DATE   : October, 2003
//
// ^CLASS    : TransitsDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION :
//
// -----------------------------------------------------------------------------
//
//******************************************************************************

#include <ifastgui\BaseMainDlg.h>

/////////////////////////////////////////////////////////////////////////////
// TransitsDlg dialog
class TransitsDlg : public BaseMainDlg
{
// Construction
public:
   TransitsDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, 
      GenericInterface* pGIParent, const Command& rCommand);
   virtual bool GetOverrideItemString (long lSubstituteId, 
      const DString& ColumnKey, DString& strOut);

// Dialog Data
   //{{AFX_DATA(TransitsDlg)
   enum
   {
      IDD = IDD_FINANCIAL_TRANSITS
   };
   // NOTE: the ClassWizard will add data members here
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(TransitsDlg)
public:
   virtual BOOL PreTranslateMessage(MSG* pMsg);
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
//{{AFX_MSG(TransitsDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnAdmDates();
   afx_msg void OnBtnAdd();
   afx_msg void OnBtnDelete();
   afx_msg void OnBtnReset();
   afx_msg void OnBtnMore();
//}}AFX_MSG
   DECLARE_MESSAGE_MAP()
private:
   void SetDlgCaption();
   LRESULT OpenBankListDlg (WPARAM, LPARAM);
   void modifyTransitCodeControlStyle ();
   DString m_dstrCaller;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/TransitsDlg.h-arc  $
//
//   Rev 1.2   Oct 27 2003 19:48:54   popescu
//CIBC PET809, FN 13, added Transit Search by name
//
//   Rev 1.1   Oct 24 2003 17:20:26   popescu
//CIBC PET 809, FN 13
//
//   Rev 1.0   Oct 04 2003 16:10:44   popescu
//Initial revision.
// Initial revision.
 *
 */

