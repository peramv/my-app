#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2004 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : AWDCommentDlg.h
// ^AUTHOR : Monica Vadeanu
// ^DATE   : April 2004
//
// ----------------------------------------------------------
//
// ^CLASS    : AWDCommentDlg.cpp
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :  This is the code for a list selection dialog

//******************************************************************************
#include <bfsessn\bfawdsession.hpp>
#include <ifastgui\basemaindlg.h>
#include <afxdtctl.h>

//class BFAwdInterface;

class AWDCommentDlg : public BaseMainDlg
{
public:

   AWDCommentDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
   //{{AFX_DATA(AWDCommentDlg)
   enum
   {
      IDD = IDD_AWD_COMMENT
   };
   //}}AFX_DATA

   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(AWDCommentDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(AWDCommentDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnSelchangeCbWuUnit();
   //}}AFX_MSG

   DECLARE_MESSAGE_MAP()

   virtual void OnPostInitDialog();
   virtual bool PreOk();
   virtual void PostOk( bool /* bOkStatus */ );
   virtual bool doRefresh( GenericInterface *, const I_CHAR * /*szOriginalCommand*/ );

private:

   bool UpdateAWDObject();
   void ConfigureAWDControls();

   BFAwdSession *m_pAwdSession;
   //BFAwdInterface *m_pAwdInterface;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/AWDCommentDlg.h-arc  $
//
//   Rev 1.1   Jun 24 2004 11:23:08   HERNANDO
//PTS10031673 - Changed UpdateAWDObject to return a bool.
//
//   Rev 1.0   May 06 2004 16:40:32   VADEANUM
//Initial revision.
 */
