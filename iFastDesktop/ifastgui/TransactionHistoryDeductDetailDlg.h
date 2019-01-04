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
// ^FILE   : TransactionHistoryDeductDetailDlg.hpp
// ^AUTHOR : Monica Vadeanu
// ^DATE   : Jan 2004
//
// ^CLASS    : TransactionHistoryDeductDetailDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : Handles the code for the Fund Factors screen
//
// -----------------------------------------------------------------------------
//
//******************************************************************************


#include <ifastgui\BaseMainDlg.h>
#include <uibase\ifdslistctrl.h>


class TransactionHistoryDeductDetailDlg : public BaseMainDlg
{
public:
   // standard constructor
   TransactionHistoryDeductDetailDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
// Dialog Data
   //{{AFX_DATA(TransactionHistoryDeductDetailDlg)
   enum
   {
      IDD = IDD_TRANSACTION_HISTORY_DEDUCT_DETAIL
   };
   //}}AFX_DATA

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(TransactionHistoryDeductDetailDlg)
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
   //{{AFX_MSG(TransactionHistoryDeductDetailDlg)
   virtual BOOL OnInitDialog();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()


private:
//methods
    void SetDlgCaption();
//properties
    DString m_caller;
	 	
};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/TransactionHistoryDeductDetailDlg.h-arc  $
//
//   Rev 1.3   Dec 07 2004 21:20:52   popescu
//PET 1117/06, pending trades/fees fixes, add-ons
//
//   Rev 1.2   Feb 11 2004 14:29:54   VADEANUM
//PET859 FN23 - ADL - IFDSListControl implementation.
//
//   Rev 1.1   Feb 04 2004 16:53:02   VADEANUM
//PET 859 FN23 - ADL - Deductions Details
//
//   Rev 1.0   Feb 03 2004 16:59:02   VADEANUM
//Initial revision.
//
*/
