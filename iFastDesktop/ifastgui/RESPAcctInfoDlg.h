#ifndef RESP_ACCT_INFO_DLG_H
#define RESP_ACCT_INFO_DLG_H
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
//    Copyright 2010 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : RESPAcctInfoDlg.h
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : RESPAcctInfoDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif
#ifndef LISTCTRL_H
   #include <uibase\listctrl.h>
#endif
#ifndef __AFXDTCTL_H__
   #include <afxdtctl.h>
#endif

class RESPAcctInfoDlg : public BaseMainDlg
{
public:
   //**
   // * Standard dialog constructor for DSTC

   RESPAcctInfoDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, 
         GenericInterface* pGIParent, const Command& rCommand);
   //{{AFX_DATA(AdminDatesDialog)
   enum
   {
      IDD = IDD_RESP_ACCT_INFO
   };
   //}}AFX_DATA

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(RESPAcctInfoDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   virtual BOOL OnInitDialog();
   //}}AFX_VIRTUAL

protected:
   virtual SEVERITY doInit();
   virtual bool doRefresh( GenericInterface * /*rpGICaller*/, 
                           const I_CHAR * //*szOriginalCommand
                          );
   //{{AFX_MSG(AdminDatesDialog)

   //}}AFX_MSG
   virtual void OnPostInitDialog();
   DECLARE_MESSAGE_MAP()

};

#endif 
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
// $Log:   Y:/VCS/BF iFAST/ifastgui/RESPAcctInfoDlg.h-arc  $ 
//
//   Rev 1.0   Mar 12 2010 14:28:56   dchatcha
//Initial revision.
//
