#pragma once

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
//    Copyright 2003 by International Financial Data Service
//
//******************************************************************************
//
// ^FILE     : MsgDetailDlg.h
// ^CLASS    : MsgDetailDlg
// ^SUBCLASS : BaseMainDlg
//
// -----------------------------------------------------------------------------
//
//******************************************************************************

#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif
class MsgDetailDlg : public BaseMainDlg
{
public:

   MsgDetailDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);

   //{{AFX_DATA(MsgDetailDlg)
   enum
   {
      IDD = IDD_MSG_DETAIL
   };
   //}}AFX_DATA

   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(MsgDetailDlg)
   protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

protected:

   virtual bool doRefresh( GenericInterface *, const I_CHAR *);

   // Generated message map functions
   //{{AFX_MSG(MsgDetailDlg)
   virtual BOOL OnInitDialog();
   //}}AFX_MSG

   virtual void OnPostInitDialog();

   DECLARE_MESSAGE_MAP()
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastgui/MsgDetailDlg.h-arc  $
//
//   Rev 1.0   Feb 21 2005 09:59:18   hernando
//Initial revision.
