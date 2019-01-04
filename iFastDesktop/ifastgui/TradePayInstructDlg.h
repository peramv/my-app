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
// ^FILE   : TradePayInstructDlg.h
// ^AUTHOR : Serban Popescu
// ^DATE   : August, 2006
//
// ^CLASS    : TradePayInstructDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : Handles the code for the Fund Info screen
//
// -----------------------------------------------------------------------------
//
//******************************************************************************


#include <ifastgui\BaseMainDlg.h>

#include <uibase\ifdslistctrl.h>
#include <uibase\dstbutton.h>
#include <uibase\dstlistctrl.h>

class TradePayInstructDlg : public BaseMainDlg
{
public:
   // standard constructor
   TradePayInstructDlg( CWnd* pParent, GenericInterfaceContainer* pGIC, 
                        GenericInterface* pGIParent, const Command& rCommand);
// Dialog Data
   //{{AFX_DATA(TradePayInstructDlg)
   enum
   {
      IDD = IDD_TRADE_PAYMENT_INSTRUCTIONS
   };
   //}}AFX_DATA

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(TradePayInstructDlg)
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
   virtual void OnPostInitDialog();
   // Generated message map functions
   //{{AFX_MSG(TradePayInstructDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnAdmDates();
   afx_msg void OnBtnBank();
   afx_msg void OnUseEntityAddressCheck();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
private:
//methods
   void ShowAndEnableBankRelatedControls (bool bShow);
   void ShowAndEnableAddressRelatedControls (bool bShow);
   void SetDlgCaption ();
//properties
   DString m_dstrTransNum,
      m_dstrListKey,
      m_dstrCaller;
};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/TradePayInstructDlg.h-arc  $
//
//   Rev 1.1   Sep 07 2006 21:39:22   popescu
//STP 2192/02
//
//   Rev 1.0   Aug 29 2006 18:27:38   popescu
//Initial revision.
//
 */
