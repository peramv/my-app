#ifndef FTPLOGONDLG_H
#define FTPLOGONDLG_H
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
// ^FILE   : FTPLogonDlg.h
// ^AUTHOR : 
// ^DATE   : Dec 9, 2002
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

#include <configmanager.hpp>
class Configuration;
class ConfigManager;
class FTPLogonDlg : public BaseMainDlg
{

public:

//******************************************************************************
// Dialog Data
//******************************************************************************

   //{{AFX_DATA(FTPLogonDlg)
   enum
   {
      IDD = IDD_FTP_LOGON
   };
   
   //}}AFX_DATA

   //******************************************************************************
   // Constructor
   //******************************************************************************

   FTPLogonDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);

   //******************************************************************************
   // Destructor
   //******************************************************************************

   ~FTPLogonDlg(); 

// Implementation
protected:

   //******************************************************************************
   // Overrides
   // ClassWizard generated virtual function overrides
   //******************************************************************************

   //{{AFX_VIRTUAL(FTPLogonDlg)   
   //virtual BOOL PreTranslateMessage(MSG* pMsg);
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   //******************************************************************************
   // Generated message map functions
   //******************************************************************************

   //{{AFX_MSG(FTPLogonDlg)
   virtual BOOL OnInitDialog();    
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

   virtual void PostOk(
                      bool bOkStatus
                      );
   private:         
   ConfigManager   *m_pUser;
   Configuration    m_user;
};

#endif

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/FTPLogonDlg.h-arc  $
//
//   Rev 1.2   Mar 21 2003 18:36:52   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.1   Dec 10 2002 13:35:46   HSUCHIN
//additional support
//
//   Rev 1.0   Dec 10 2002 09:54:54   HSUCHIN
//Initial Revision
 */
