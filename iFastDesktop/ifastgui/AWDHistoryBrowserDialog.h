#pragma once
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
//    Copyright 2013 by International Financial, Inc.
//
//******************************************************************************

//{{AFX_INCLUDES()
#include <ifastgui\webbrowser.h>
//}}AFX_INCLUDES

#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif


class AWDHistoryBrowserDialog : public BaseMainDlg
{
public:

   AWDHistoryBrowserDialog( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
// Dialog Data
   //{{AFX_DATA(AWDHistoryDialog)
   enum
   {
      IDD = IDD_AWD_HISTORY_BROWSER
   };
   CWebBrowser m_AwdPortalBrowser;
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(AWDHistoryBrowserDialog)
protected:
   virtual BOOL OnInitDialog();
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

protected:
   virtual SEVERITY doInit();
   virtual bool doRefresh(
                         GenericInterface * /*rpGICaller*/, 
                         const I_CHAR * //*szOriginalCommand
                         );
   virtual void OnPostInitDialog();
   void SetDlgCaption();
   // Generated message map functions
   //{{AFX_MSG(AWDHistoryBrowserDialog)


   //}}AFX_MSG

   DECLARE_MESSAGE_MAP()

   private:
	   DString _url;
	   DString _accountnum;
	   DString _extTransNum;
};
