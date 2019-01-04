
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
//    Copyright 2002 by International Financial Data Service
//
//******************************************************************************
//
// FILE   : RDSPTransfersDlg.h
// AUTHOR :
// DATE   : 
//
// CLASS    : RDSPTransfersDlg
// SUBCLASS : BaseMainDlg
//
// CLASS DESCRIPTION :
//
// -----------------------------------------------------------------------------
//
//******************************************************************************

#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif

class RDSPTransfersDlg : public BaseMainDlg
{
public:
   /**
    * Standard dialog constructor for DSTC
    */
   RDSPTransfersDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
// Dialog Data
   //{{AFX_DATA(SettlementDlg)
   enum
   {
      IDD = IDD_RDSP_TRANSFER
   };
   //}}AFX_DATA

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(SettlementDlg)
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

   /**
     * Get parameters from InterProcessData.
     * @returns SEVERITY, check conditions if > NO_SEVERITY
     */
   /**
     * This method should be overridden in the derived dialog if there is
     * OnOk processing to be done after the base processing.  Note that the OnOk
     * processing can no longer be "cancelled" at this point.  BaseMainDlg 
     * enforces its actions by making OnOk private.
     * @param bCancelStatus - true = Ok successful, false = Ok failed
     */
   //  virtual void PostOk(
   //     bool /* bOkStatus */
   //     );
   virtual bool doSend ( GenericInterface *rpGICaller, 
                         const I_CHAR *szMessage);
   // Generated message map functions
   //{{AFX_MSG(SettlementDlg)
   virtual BOOL OnInitDialog();
   //}}AFX_MSG
   virtual void OnPostInitDialog();
   virtual void ControlUpdated( UINT controlID, const DString &strValue );
   virtual SEVERITY doInit();
   void addControls ();
   void setAllowedChars ();
   void enableDisableControls();
   
   DECLARE_MESSAGE_MAP()

private:

   void SetDlgCaption ();

   DString	m_dstrAccountNum;
   DString	m_dstrCaller;
   bool		m_bDialogInit;
   int		m_DecimalDigits;
   DString	m_TransType;
   DString	m_DepositType;
   DString	m_RedemptonCode;
   DString	m_EffectiveDate;

};
