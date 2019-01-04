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
// ^FILE   : ProtectedFundSetupDlg.hpp
// ^AUTHOR : Serban Popescu
// ^DATE   : 01/08/03
//
// ^CLASS    : ProtectedFundSetupDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : Handles the code for the Fund Info screen
//
// -----------------------------------------------------------------------------
//
//******************************************************************************


#include <ifastgui\BaseMainDlg.h>
#include <uibase\listctrl.h>
#include <uibase\combobase.h>
#include <uibase\dstdatetimectrl.h>

#include <ifastgui\ifasthistoricalinfo.hpp>

class ProtectedFundSetupDlg : public BaseMainDlg
{
public:
   // standard constructor
   ProtectedFundSetupDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
// Dialog Data
   //{{AFX_DATA(ProtectedFundSetupDlg)
   enum
   {
      IDD = IDD_PROTECTED_FUND_SETUP
   };
   //}}AFX_DATA

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(ProtectedFundSetupDlg)
public:
   virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:
   virtual bool doRefresh( GenericInterface * /*rpGICaller*/, 
                           const I_CHAR * /*szOriginalCommand*/ );
   virtual SEVERITY doInit();
   virtual void ControlUpdated( UINT controlID, const DString &strValue );


   virtual void OnPostInitDialog();
   // Generated message map functions
   //{{AFX_MSG(ProtectedFundSetupDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnAdmDates();
   afx_msg void OnBtnAdd();
   afx_msg void OnBtnDelete();
   afx_msg void OnBtnReset();
   afx_msg void OnBtnHistorical();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()

   virtual void DoListItemChanged(
      UINT listControlID,
      const DString &strKey,
      bool bIsNewItem ,
      bool bIsDummyItem);
private:
//methods
   LRESULT OpenFundListDlg( WPARAM, LPARAM );
   CWnd* m_pWndItemInFocus;

//properties
};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/ProtectedFundSetupDlg.hpp-arc  $
//
//   Rev 1.6   Mar 21 2003 18:39:40   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.5   Mar 05 2003 11:29:56   PURDYECH
//Use IFastHistoricalInfo instead of deriving from IFastBaseMainDlg
//
//   Rev 1.4   Feb 03 2003 11:57:06   popescu
//Displaying the history button only when the item is not new, and adding some txt message for the status bar
//
//   Rev 1.3   Jan 28 2003 13:16:56   popescu
//Historical Info feature implementation
//
//   Rev 1.2   Jan 20 2003 15:44:00   popescu
//Checked in for unit testing the ProtectedFundSetup feature
//
//   Rev 1.1   Jan 14 2003 11:00:22   popescu
//Added F4 functionality
//
//   Rev 1.0   Jan 13 2003 12:50:18   popescu
//Initial revision.
 * 
 */
