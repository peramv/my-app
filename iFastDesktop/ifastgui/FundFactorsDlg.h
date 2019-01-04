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
// ^FILE   : FundFactorsDlg.hpp
// ^AUTHOR : Amelia Aguila
// ^DATE   : 20/11/03
//
// ^CLASS    : FundFactorsDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : Handles the code for the Fund Factors screen
//
// -----------------------------------------------------------------------------
//
//******************************************************************************


#include <ifastgui\BaseMainDlg.h>
#include <uibase\ifdslistctrl.h>

class FundFactorsDlg : public BaseMainDlg
{
public:
   // standard constructor
   FundFactorsDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
// Dialog Data
   //{{AFX_DATA(FundFactorsDlg)
   enum
   {
      IDD = IDD_FUNDFACTORS
   };
   //}}AFX_DATA

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(FundFactorsDlg)
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
   //{{AFX_MSG(FundFactorsDlg)
   virtual BOOL OnInitDialog();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()


private:
//methods
    void SetDlgCaption();
//properties
};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/FundFactorsDlg.h-arc  $
//
//   Rev 1.1   Sep 09 2004 11:45:18   HERNANDO
//PET1117 FN22 - WKN & ISIN Enhancement.
//
//   Rev 1.0   Nov 20 2003 16:29:04   AGUILAAM
//Initial revision.
//
 * 
 */
