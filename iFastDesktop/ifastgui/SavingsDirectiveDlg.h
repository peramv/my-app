#ifndef SavingsDirectiveDlg_H
#define SavingsDirectiveDlg_H
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
// ^FILE   : SavingsDirectiveDlg.h
// ^AUTHOR : 
// ^DATE   : 11/22/05
//
// ^CLASS    : SavingsDirectiveDlg
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

class SavingsDirectiveDlg : public BaseMainDlg
{
public:
   /**
    * Standard dialog constructor for DSTC
    */
   SavingsDirectiveDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
// Dialog Data
   //{{AFX_DATA(SavingsDirectiveDlg)
   enum
   {
      IDD = IDD_SAVINGS_DIRECTIVE
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
   afx_msg void OnBtnReset();
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
   /**
     * Get parameters from InterProcessData.
     * @returns SEVERITY, check conditions if > NO_SEVERITY
     */
   virtual SEVERITY doInit();
   /**
     * This method should be overridden in the derived dialog if there is
     * OnOk processing to be done after the base processing.  Note that the OnOk
     * processing can no longer be "cancelled" at this point.  BaseMainDlg 
     * enforces its actions by making OnOk private.
     * @param bCancelStatus - true = Ok successful, false = Ok failed
     */
   virtual void PostOk(
                      bool /* bOkStatus */
                      );

   virtual void OnPostInitDialog();
   private:
		void setDlgCaption();
		DString _accountNum, _transID;

};

#endif // SavingsDirectiveDlg_H
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/SavingsDirectiveDlg.h-arc  $
//
//   Rev 1.0   Nov 29 2005 17:03:54   AGUILAAM
//Initial revision.
//
//
 */
