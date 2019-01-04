#ifndef ASPENSIONPLANDLG_H
#define ASPENSIONPLANDLG_H
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
// ^FILE   : AsPensionPlanDlg.h
// ^AUTHOR : Karen Jan
// ^DATE   : July 23, 2001
//
// ^CLASS    : AsPensionPlanDlg
// ^SUBCLASS : 
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif

#if _MSC_VER > 1000
   #pragma once
#endif // _MSC_VER > 1000
// AsPensionPlanDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// AsPensionPlanDlg dialog

class AsPensionPlanDlg : public BaseMainDlg
{
// Construction
public:
   AsPensionPlanDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
   ~AsPensionPlanDlg();

// Dialog Data
   //{{AFX_DATA(AsPensionPlanDlg)
   enum
   {
      IDD = IDD_AS_PENSION_PLAN
   };
   // NOTE: the ClassWizard will add data members here
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(AsPensionPlanDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(AsPensionPlanDlg)
   // NOTE: the ClassWizard will add member functions here
   virtual BOOL OnInitDialog();

   afx_msg void OnBtnReset();

   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()

   /**
     * Get parameters from InterProcessData.
     * @returns SEVERITY, check conditions if > NO_SEVERITY
     */
   virtual SEVERITY doInit();
   virtual SEVERITY init2();

   void OnPostInitDialog();

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
                         GenericInterface * /*rpGICaller*/, 
                         const I_CHAR * /*szOriginalCommand*/ );

   void enableControls();

private:

   void setDlgTitle( );

   DString m_dstrAccountNum;
   DString m_dstrShrNum;


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ASPENSIONPLANDLG_H__C956AAC4_749F_11D5_9A98_00C04F58BCFE__INCLUDED_)
