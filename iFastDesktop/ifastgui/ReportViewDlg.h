#ifndef REPORTVIEWDLG_H
#define REPORTVIEWDLG_H
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2002 by International Financial, Inc.
//
//******************************************************************************
//
// ^FILE   : ReportViewDlg.h
// ^AUTHOR : 
// ^DATE   : Nov 21, 2002
//
// ^CLASS    : 
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

class FTPConnection;
class ReportViewDlg : public BaseMainDlg
{

public:

//******************************************************************************
// Dialog Data
//******************************************************************************

   //{{AFX_DATA(ReportDlg)
   enum
   {
      IDD = IDD_REPORT_VIEW
   };    
   CRichEditCtrl m_re_report;
   //}}AFX_DATA

   //******************************************************************************
   // Constructor
   //******************************************************************************

   ReportViewDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);

   //******************************************************************************
   // Destructor
   //******************************************************************************

   ~ReportViewDlg(); 

// Implementation
protected:

   //******************************************************************************
   // Overrides
   // ClassWizard generated virtual function overrides
   //******************************************************************************

   //{{AFX_VIRTUAL(ReportDlg)   
   //virtual BOOL PreTranslateMessage(MSG* pMsg);
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   //******************************************************************************
   // Generated message map functions
   //******************************************************************************

   //{{AFX_MSG(ReportDlg)
   virtual BOOL OnInitDialog();    
   afx_msg void OnBtnPrint();
   //}}AFX_MSG
   
   DECLARE_MESSAGE_MAP()

   SEVERITY doInit();

   void OnPostInitDialog();

   //******************************************************************************
   // Method to refresh dialog controls
   // @param   GenericInterface *rpGICaller - pointer to the calling object
   // @param   const I_CHAR *szOriginalCommand - Not used in this case, but 
   //                      can be used to instruct special processing.
   // @returns bool - true.
   //******************************************************************************

   virtual bool doRefresh( GenericInterface * /*rpGICaller*/, 
                           const I_CHAR * /*szOriginalCommand*/ );   

   protected:

   //******************************************************************************
   // Overrides canCancel so that discard dialog does not show up.
   // @returns bool - true.
   //******************************************************************************
   bool canCancel();

   private:

   FTPConnection* _pFTPConnection;
   DString _dstrReportPath, _dstrReportName;
};

#endif

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/ReportViewDlg.h-arc  $
//
//   Rev 1.1   Mar 21 2003 18:40:02   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.0   Dec 08 2002 22:16:32   HSUCHIN
//Initial Revision
 */
