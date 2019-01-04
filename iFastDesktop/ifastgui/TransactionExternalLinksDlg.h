#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data ,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2004 by International Financial Data Services
//
//******************************************************************************
//
// ^FILE   : TransactionExternalLinksDlg.hpp
// ^AUTHOR : Monica Vadeanu
// ^DATE   : August 2004
//
// ^CLASS    : TransactionExternalLinksDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : Handles the code for the Fund Factors screen
//
//
//******************************************************************************


#include <ifastgui\BaseMainDlg.h>
#include <uibase\ifdslistctrl.h>


class TransactionExternalLinksDlg : public BaseMainDlg
{
public:
   // standard constructor
   TransactionExternalLinksDlg( CWnd* pParent, 
		                          GenericInterfaceContainer *pGIC, 
										  GenericInterface *pGIParent, 
										  const Command& rCommand );
// Dialog Data
   //{{AFX_DATA(TransactionExternalLinksDlg)
   enum
   {
      IDD = IDD_TRANSACTION_HISTORY_EXTERNAL_LINKS
   };
   //}}AFX_DATA

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(TransactionExternalLinksDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:
   virtual bool doRefresh( GenericInterface * /*rpGICaller*/, 
                           const I_CHAR * /*szOriginalCommand*/ );
   virtual SEVERITY doInit();
   virtual void OnPostInitDialog();
   // Generated message map functions
   //{{AFX_MSG(TransactionExternalLinksDlg)
   virtual BOOL OnInitDialog();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()


private:
//methods
    void SetDlgCaption();
//properties
	 DString _dstrTransNum;
	 DString _dstrAccountNum;
	 DString _dstrShareholderNum;
};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastgui/TransactionExternalLinksDlg.h-arc  $
//
//   Rev 1.1   Sep 07 2004 15:36:24   VADEANUM
//PET 1094 FN4 - Activest Bank File Interface.
//
//   Rev 1.0   Aug 30 2004 16:38:06   VADEANUM
//Initial revision.
//
