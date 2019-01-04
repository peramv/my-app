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
//    Copyright 2000 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : FundGroupDlg.h
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : FundGroupDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
// -----------------------------------------------------------------------------
#pragma once

#include <ifastgui\BaseMainDlg.h>
#include <uibase\ifdslistctrl.h>

/////////////////////////////////////////////////////////////////////////////
// FundGroupDlg dialog

class FundGroupDlg : public BaseMainDlg
{
// Construction
public:
   FundGroupDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);

   virtual ~FundGroupDlg();

   // Dialog Data
   //{{AFX_DATA(FundGroupDlg)
   enum
   {
      IDD = IDD_FUND_GROUP
   };
   //}}AFX_DATA

   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(FundGroupDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

protected:

	virtual SEVERITY doInit();
   virtual void OnPostInitDialog();
   virtual bool doRefresh(GenericInterface *, const I_CHAR *) {
      return(true);
   }

private:
	DString m_dstrSponsorGroup;

   // Generated message map functions
   //{{AFX_MSG(FundGroupDlg)
   // NOTE: the ClassWizard will add member functions here
   afx_msg void OnDblclkList( NMHDR* pNMHDR, LRESULT* pResult );
//   afx_msg void OnBtnSearch();
   virtual BOOL OnInitDialog();
   afx_msg void OnDestroy();
//   afx_msg void OnBtnMore();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
};

