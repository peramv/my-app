#ifndef PaymentDlg_H
#define PaymentDlg_H
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
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : PaymentDlg.h
// ^AUTHOR : 
// ^DATE   : 11/17/11
//
// ^CLASS    : PaymentDlg.h
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

class PaymentDlg : public BaseMainDlg
{
public:
   /**
    * Standard dialog constructor for DSTC
    */
   PaymentDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
// Dialog Data
   //{{AFX_DATA(SavingsDirectiveDlg)
   enum
   {
      IDD = IDD_PAYMENT_INFO
   };
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(SavingsDirectiveDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support


   //}}AFX_VIRTUAL

// Implementation
protected:
   // Generated message map functions
//{{AFX_MSG(TransitsDlg)
   
   
   virtual BOOL OnInitDialog();
 afx_msg void OnBtnHistoricalPayment();
//}}AFX_MSG

   DECLARE_MESSAGE_MAP()

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
   

   virtual void OnPostInitDialog();
   virtual SEVERITY doInit();
   void ControlUpdated(UINT controlID,const DString &strValue);
   private:
		
		DString AccountNum;
		DString	m_RecordType;
		bool m_bDialogInit;

};

#endif // PaymentDlg_H

//*************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastgui/PaymentDlg.h-arc  $
//
//   Rev 1.0   Dec 08 2011 00:33:38   wp040032
//Initial revision.
//