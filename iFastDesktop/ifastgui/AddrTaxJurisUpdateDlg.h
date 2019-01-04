#ifndef ADDRTAXJURISUPDATEDLG_H
#define ADDRTAXJURISUPDATEDLG_H
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
// ^FILE   : AddrTaxJurisUpdateDlg.h
// ^AUTHOR : Wutipong W.
// ^DATE   : 14/10/2008
//
// ^CLASS    : AddrTaxJurisUpdateDlg
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


class AddrTaxJurisUpdateDlg : public BaseMainDlg
{
public:
   //**
   // * Standard dialog constructor for DSTC

   AddrTaxJurisUpdateDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, 
         GenericInterface* pGIParent, const Command& rCommand);
   //{{AFX_DATA(AdminDatesDialog)
   enum
   {
      IDD = IDD_CONFIRM_ADDR_JURIS_UPDATE_DIALOGEX
   };

   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(AddrTaxJurisUpdateDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   virtual BOOL OnInitDialog();
   virtual void OnChkUpdateTaxJuris();
   virtual void OnChkUpdateProvRes();
   //}}AFX_VIRTUAL

protected:
   virtual SEVERITY doInit();
   virtual bool doRefresh(
                         GenericInterface * /*rpGICaller*/, 
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
/* $Log:   Y:/VCS/BF iFAST/ifastgui/AddrTaxJurisUpdateDlg.h-arc  $ */
//
//   Rev 1.0   Oct 29 2008 21:15:32   wongsakw
//Initial revision.
