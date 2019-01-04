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


class AWDHistoryDialog : public BaseMainDlg
{
public:

   AWDHistoryDialog( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
// Dialog Data
   //{{AFX_DATA(AWDHistoryDialog)
   enum
   {
      IDD = IDD_AWD_HISTORY
   };
   CWebBrowser m_AwdImageBrowser;
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(AWDHistoryDialog)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   virtual BOOL OnInitDialog();
   //}}AFX_VIRTUAL

protected:
//	virtual bool Cancel();

   virtual SEVERITY doInit();

   virtual bool doRefresh(
                         GenericInterface * /*rpGICaller*/, 
                         const I_CHAR * //*szOriginalCommand
                         );

   virtual void OnPostInitDialog();
   virtual void DoListItemChanged(UINT listControlID, const DString &strKey, bool bIsNewItem, bool bIsDummyItem);

//	virtual bool Ok();
   // Generated message map functions
   //{{AFX_MSG(AWDHistoryDialog)


   //}}AFX_MSG

   DECLARE_MESSAGE_MAP()

   private:

};
