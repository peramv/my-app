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
//    Copyright 1999 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : CloneAccountDlg.h
// ^AUTHOR : Serban Popescu
// ^DATE   : October, 2006
//
// ^CLASS    : CloneAccountDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : Handles the code for the Fund Info screen
//
// -----------------------------------------------------------------------------
//
//******************************************************************************


#include <ifastgui\BaseMainDlg.h>

class CloneAccountDlg : public BaseMainDlg
{
public:
   // standard constructor
   CloneAccountDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, 
                    GenericInterface* pGIParent, const Command& rCommand);
// Dialog Data
   //{{AFX_DATA(CloneAccountDlg)
   enum
   {
      IDD = IDD_CLONE_ACCOUNT
   };
   //}}AFX_DATA

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CloneAccountDlg)
public:
   virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:
   virtual bool doRefresh( GenericInterface * /*rpGICaller*/, 
                           const I_CHAR * /*szOriginalCommand*/);
   virtual SEVERITY doInit();
   virtual void ControlUpdated (UINT controlID, const DString &strValue);
   virtual bool SetDataFromControl( UINT controlID,
                                    const DString &strValue,
                                    bool bFormatted,
                                    SEVERITY &sevRtn,
                                    int index = 0);
   virtual void OnPostInitDialog();
   // Generated message map functions
   //{{AFX_MSG(CloneAccountDlg)
   virtual BOOL OnInitDialog();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
private:
//methods
//F4 helpers,  dialogs
   LRESULT OpenBrokerListDlg (WPARAM, LPARAM);
   LRESULT OpenBranchListDlg (WPARAM, LPARAM);
   LRESULT OpenSlsRepListDlg (WPARAM, LPARAM);
   void SetDlgCaption ();
//properties
   DString m_accountNum,
      m_dstrCaller;
   CWnd *m_pCWndF4Focus;
   bool m_popSalesRepCreateQuestion;
};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/CloneAccountDlg.h-arc  $
//
//   Rev 1.0   Nov 08 2006 17:34:02   popescu
//Initial revision.
//
//   Rev 1.1   Sep 07 2006 21:39:22   popescu
//STP 2192/02
//
//   Rev 1.0   Aug 29 2006 18:27:38   popescu
//Initial revision.
//
 */
