
#pragma once

//******************************************************************************
//
// COPYRIGHT:
//
// The computer systems, procedures, data bases and
// programs created and maintained by International Financial Data Services, Inc.,
// are proprietary in nature and as such are confIdential.
// Any unauthorized use or disclosure of such information
// may result in civil liabilities.
//
// Copyright 2010 by International Financial Data Services, Inc.
//
//******************************************************************************
//
// ^FILE   : AcctGuaranteeGuardOptDlg.h
// ^AUTHOR :
// ^DATE   : 
//
// ^CLASS    : AcctGuaranteeGuardOptDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : Handles the code for the Account Level Guarantee Guard Option screen
//
//******************************************************************************


#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif

#include <ifastgui\ifasthistoricalinfo.hpp>

class AcctGuaranteeGuardOptDlg : public BaseMainDlg
{
public:
   /**
    * Standard dialog constructor for DSTC
    */
   AcctGuaranteeGuardOptDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
// Dialog Data
   //{{AFX_DATA(AcctGuaranteeGuardOptDlg)
   enum
   {
      IDD = IDD_ACCT_GUARNT_GUARD_OPTN
   };
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(AcctGuaranteeGuardOptDlg)
public:
   virtual BOOL PreTranslateMessage(MSG* pMsg);  
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:
   /**
     * Required implementation for the refresh method.  No refresh activity is
     * performed for this class.
     * @param rpGICaller - A reference pointer to the calling object.
     * @param szOriginalCommand - A string literal representing the original
     * command issuing the refresh (which may provide a hint on whether this
     * object needs to check for refresh).
     * @returns true if successful, call getErrors for errors if false
     */
   virtual bool doRefresh( GenericInterface * /*rpGICaller*/, 
                           const I_CHAR * /*szOriginalCommand*/ );

   virtual void ControlUpdated ( UINT controlID, 
                                 const DString &strValue);

   bool GetDataForControl( UINT controlID, 
                           DString &strValueOut, 
                           bool bFormatted, 
                           int index ) const;

   // Generated message map functions
   //{{AFX_MSG(AcctGuaranteeGuardOptDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnReset();
   afx_msg void OnBtnAdd();
   afx_msg void OnBtnAdmin();
   afx_msg void OnBtnMore();

   //}}AFX_MSG

   virtual void OnPostInitDialog();
   virtual SEVERITY doInit();
   virtual bool doDisablePermCheckButton(UINT nID);

   DECLARE_MESSAGE_MAP()

private:

   void     SetDlgCaption ();
   DString  m_RecordType;
   bool     m_bDialogInit;
   DString  m_BtnAddEnable;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
// $Log:   Y:/VCS/BF iFAST/ifastgui/AcctGuaranteeGuardOptDlg.h-arc  $
//
//   Rev 1.1   Nov 04 2010 11:22:26   kitticha
//IN#2313085 - P0173756FN02- Don't bust the rules - Add Button not disabled.
//
//   Rev 1.0   Sep 17 2010 05:50:50   kitticha
//Initial revision.
//