#ifndef REPORTSTATUSDLG_H
#define REPORTSTATUSDLG_H
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
// ^FILE   : ReportStatusDlg.h
// ^AUTHOR : 
// ^DATE   : Nov 21, 2002
//
// ^CLASS    : ReportDlg
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
class ReportStatusDlg : public BaseMainDlg
{

public:

//******************************************************************************
// Dialog Data
//******************************************************************************

   //{{AFX_DATA(ReportDlg)
   enum
   {
      IDD = IDD_REPORTS_STATUS
   };    
   //}}AFX_DATA

   //******************************************************************************
   // Constructor
   //******************************************************************************

   ReportStatusDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);

   //******************************************************************************
   // Destructor
   //******************************************************************************

   ~ReportStatusDlg(); 

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
   afx_msg void OnBtnMore();           
   afx_msg void OnBtnSearch();      
   afx_msg void OnBtnView();
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
   
   //******************************************************************************
   // All the control hookups are done in this procedure.  This is called by the 
   // OnInitDialog function.
   // @returns void.
   //******************************************************************************
   void addControls( );
   void enableButtons( bool bEnable );
   bool ReportStatusDlg::openFTP( );
   FTPConnection* _pFTPConnection;
};

#endif

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/ReportStatusDlg.h-arc  $
//
//   Rev 1.3   Mar 21 2003 18:39:56   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.2   Dec 10 2002 13:36:28   HSUCHIN
//more ftp logic
//
//   Rev 1.1   Dec 10 2002 09:56:44   HSUCHIN
//added ftp logon
//
//   Rev 1.0   Dec 08 2002 22:16:28   HSUCHIN
//Initial Revision
 */
