#ifndef SYSTEMATICFEEDLG_H
#define SYSTEMATICFEEDLG_H
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
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : SystematicFeeDlg.h
// ^AUTHOR : Shaobo Huang
// ^DATE   : Nov 20, 1999
//
// ^CLASS    : SystematicFeeDlg
// ^SUBCLASS : BaseMainDlg
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
// SystematicFeeDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SystematicFeeDlg dialog

class SystematicFeeDlg : public BaseMainDlg
{
// Construction
public:
   SystematicFeeDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);

private:
   //{{AFX_DATA(SystematicFeeDlg)
   enum
   {
      IDD = IDD_SYSTEMATIC_FEE
   };
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(SystematicFeeDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:
   // Generated message map functions
   //{{AFX_MSG(SystematicFeeDlg)
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()

   BOOL OnInitDialog();

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
   virtual bool doRefresh(GenericInterface * rpGICaller, const I_CHAR * szOriginalCommand);

   virtual bool GetDataForControl(UINT controlID, DString &dstrValueOut, 
                                  bool bFormatted, int index = 0) const;
private:
   void addControls();
   void showTransType();

   void getFundCurrency(DString &dstrFund, DString &dstrClass, DString &dstrCurr) const;

   DString m_dstrCurSystematicListKey;
   DString m_dstrAccountNum;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYSTEMATICDLG_H__55E2FE35_DAEF_11D2_8BBD_00105AA1A578__INCLUDED_)
