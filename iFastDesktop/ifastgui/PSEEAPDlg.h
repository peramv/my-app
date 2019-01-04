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
// ^FILE   : PSEEAPDlg.h
// ^AUTHOR :
// ^DATE   : 
//
// ^CLASS    : PSEEAPDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : Handles the code for the Fund Info screen
//
// -----------------------------------------------------------------------------
//
//******************************************************************************


#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif
class PSEEAPDlg : public BaseMainDlg
{
public:
   /**
    * Standard dialog constructor for DSTC
    */
   PSEEAPDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
// Dialog Data
   //{{AFX_DATA(SettlementDlg)
   enum
   {
      IDD = IDD_RESP_PSEEAP
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
     */
   virtual bool doRefresh( GenericInterface * /*rpGICaller*/, 
                           const I_CHAR * /*szOriginalCommand*/ );
   // Generated message map functions
   //{{AFX_MSG(SettlementDlg)
   virtual BOOL OnInitDialog();
   //}}AFX_MSG
   virtual void OnPostInitDialog();
   virtual void ControlUpdated (UINT controlID, const DString &strValue);
   virtual SEVERITY doInit ();
   virtual void OnCancel ();
   virtual bool GetDataForControl( UINT controlID, 
                                   DString &dstrValueOut, 
                                   bool bFormatted, 
                                   int index) const;
   DECLARE_MESSAGE_MAP()

private:

   void SetDlgCaption ();
   DString	m_dstrAccountNum,
      m_dstrCaller;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/PSEEAPDlg.h-arc  $
//
//   Rev 1.2   May 05 2010 15:27:38   popescu
//RES-QESI Trading - PSE/EAP work - fixes for the dialog
//
//   Rev 1.1   Apr 30 2010 15:32:24   popescu
//RES-QESI Trading - PSE/EAP work
// Initial revision.
**/