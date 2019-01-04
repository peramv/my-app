#ifndef RESPINFODLG_H
#define RESPINFODLG_H

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
// ^FILE   : TaxRatesDlg.h
// ^AUTHOR : Dan Petolescu
// ^DATE   : 01/05/2000
//
// ^CLASS    : RESPInfoDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

#include <ifastgui\BaseMainDlg.h>

#if _MSC_VER > 1000
   #pragma once
#endif // _MSC_VER > 1000
// RESPInfoDlg.h : header file
//
#ifndef CTIMERLISTCTRL_H
   #include <uibase\CTimerListCtrl.h>
#endif
/////////////////////////////////////////////////////////////////////////////
// RESPInfoDlg dialog

class RESPInfoDlg : public BaseMainDlg
{
// Construction
public:
   RESPInfoDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);

// Dialog Data
   //{{AFX_DATA(RESPInfoDlg)
   enum
   {
      IDD = IDD_RESPINFO
   };
   CTimerListCtrl m_RESPTotalList;
   //}}AFX_DATA

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(RESPInfoDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(RESPInfoDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnChange();
   afx_msg void OnBtnResptrans();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()

   virtual SEVERITY doInit(); 
   virtual bool doRefresh( GenericInterface * /*rpGICaller*/, const I_CHAR * /*szOriginalCommand*/ );

   void OnPostInitDialog();

   virtual bool Ok()
   {
      // just return true for now
      return(true);
   }
private:
   DString  _strAccountNumber;
   DString  _strLastName;
   DString  _strFirstName;
   DString  _strShareholderNum;

//   void PopulateRESPInfoBeneficiaryList();
   void DisplayTitle();
//   void PopulateDetails();
   void FillTotalList();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif
