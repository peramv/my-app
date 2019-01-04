#ifndef TransCancellationDlg_H
#define TransCancellationDlg_H
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
// ^FILE   : TransCancellationDlg.h
// ^AUTHOR : 
// ^DATE   : 02/28/05
//
// ^CLASS    : TransCancellationDlg
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

class TransCancellationDlg : public BaseMainDlg
{
public:
   /**
    * Standard dialog constructor for DSTC
    */
   TransCancellationDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
// Dialog Data
   //{{AFX_DATA(TransCancellationDlg)
   enum
   {
      IDD = IDD_TXN_CANCELLATION
   };
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(TransCancellationDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:
   // Generated message map functions
   //{{AFX_MSG(TransCancellationDlg)
   afx_msg void OnChkVerify();   
   afx_msg void OnChkRebook();   
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
   // Generated message map functions
   //{{AFX_MSG(TransCancellationDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnRestore();
   afx_msg void OnBtnDilution();
   //}}AFX_MSG
   virtual void OnPostInitDialog();
   private:
	   bool bReadOnly,
	        m_bVerifyChecked;
      DString cashDivPaidAfter_;

	  void setDlgCaption();	
	void EnableCancellationOption(bool _bEnable);

   DString _dstrTradeDate,
         _dstrFund,
         _dstrClass,
         _transType,
         _dstrSWPSettleESGElig,
         _dstrTransTradeDate,
         _dstrTransSettleDate,
         _grantExists;
};

#endif // TransCancellationDlg_H
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/TransCancellationDlg.h-arc  $
//
//   Rev 1.8   Apr 15 2010 00:02:18   popescu
//PET165541_FN01_QESI - RESP Gap_Dsk_Trading
//
//   Rev 1.7   Dec 12 2007 14:50:46   wongsakw
//PET2360 FN60 Automatically Cancel Contribution Reciept
//
//   Rev 1.6   Mar 10 2006 14:43:20   porteanm
//Incident 563764 - TradeDate/SettleDate validation support for a cancelled transaction.
//
//   Rev 1.5   Mar 02 2006 17:36:08   ZHANGCEL
//PET1334 - FN01 -- ESG Settlement enhancement
//
//   Rev 1.4   Nov 26 2005 16:32:32   porteanm
//PET 1286 FN01 - Bulk Cancellation.
//
//   Rev 1.3   Nov 06 2005 15:58:14   porteanm
//PET 1286 FN01 - Bulk Cancellation.
//
//   Rev 1.2   Sep 01 2005 14:02:34   popescu
//Incident# 388632 - trans cancel screen code overhaul
//
//   Rev 1.1   Jul 08 2005 13:04:10   Yingbaol
//PET1235,FN01:cancellation rebook
//
//   Rev 1.0   Mar 03 2005 18:24:50   Fengyong
//Initial revision.
 * 
 */
