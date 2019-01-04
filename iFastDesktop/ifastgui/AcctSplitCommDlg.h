#ifndef ACCTSPLITCOMMDLG_H
#define ACCTSPLITCOMMDLG_H
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Canada, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2001 by DST Canada, Inc.
//
//******************************************************************************
//
// ^FILE   : AcctSplitCommDlg.h
// ^AUTHOR : 
// ^DATE   : Aug 23, 2001
//
// ^CLASS    : AcctSplitCommDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif

#if _MSC_VER > 1000
   #pragma once
#endif // _MSC_VER > 1000

class AcctSplitCommDlg : public BaseMainDlg
{
public:
   /**
    * Constructor
    */
   AcctSplitCommDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);

   /**
    * Destructor
    */
   ~AcctSplitCommDlg();

   /**
    * Dialog Data
    */
   //{{AFX_DATA(AcctSplitCommDlg)
   enum
   {
      IDD = IDD_ACCOUNT_SPLITCOMM
   };
   //}}AFX_DATA

   /**
    * Overrides
    */
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(AcctSplitCommDlg)   
protected:
   virtual BOOL PreTranslateMessage(MSG* pMsg);
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

protected:

   /**
    * Generated message map functions
    */
   //{{AFX_MSG(AcctSplitCommDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnAddDate();
   afx_msg void OnBtnDelDate();
   afx_msg void OnBtnAddRep();
   afx_msg void OnBtnDelRep();
   afx_msg void OnBtnReset();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()

   /**
     * This method initializes the Dialog by call addControls()
     * This method is invoked by the base architecture after OnInitDialog has 
     * completed.  This should be implemented for time intensive setup so that
     * the screen can display quickly and then do this processing.
     */
   void OnPostInitDialog();

   /**
     * Get parameters from InterProcessData.
     * @returns SEVERITY, check conditions if > NO_SEVERITY
     */
   virtual SEVERITY doInit();

   /**
     * The List controls are refreshed.
     * @param rpGICaller - A reference pointer to the calling object.
     * @param szOriginalCommand - A string literal representing the original
     * command issuing the refresh (which may provide a hint on whether this
     * object needs to check for refresh).
     * @returns true if successful, call getErrors for errors if false
     */
   virtual bool doRefresh(
                         GenericInterface * /*rpGICaller*/, 
                         const I_CHAR * /*szOriginalCommand*/
                         );

   void ControlUpdated(UINT controlID, const DString &dstrValue);

   /**
   implement here any bussiness rules related to the buttons that were added for permission check (add or delete buttons)
   return true if it should be disabled and false if it should be enabled
   DO NOT call EnableWindow() here
   * @param nID - the control's ID
   */
   bool doDisablePermCheckButton(UINT nID);


private:

   LRESULT OpenBrokerListDlg( WPARAM, LPARAM );
   LRESULT  OpenBranchListDlg( WPARAM, LPARAM );
   LRESULT  OpenSlsRepListDlg( WPARAM, LPARAM );

   void DisplayByEntityType();

   /**
     * Adds the custom controls used in the dialog
     */
   void addControls( );
   DString _dstrAccountNum, _dstrEntityName, _dstrShrNum;
   bool _bDisableAdd;
   DString _dstrCreateAcct, _dstrCreateShr;
};

#endif

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/AcctSplitCommDlg.h-arc  $
//
//   Rev 1.8   Mar 21 2003 18:31:00   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.7   Oct 17 2002 14:57:16   HSUCHIN
//sync up with release 49.  Disable Delete button during NASU
//
//   Rev 1.6   Oct 09 2002 23:55:28   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.5   23 Nov 2001 14:20:30   KOVACSRO
//perm check changes.
//
//   Rev 1.4   16 Nov 2001 16:21:32   HSUCHIN
//added boolean _bDisableAdd to be used in disabling the add button after 1 add and re-enabling after a delete.
//
//   Rev 1.3   24 Sep 2001 11:03:00   HSUCHIN
//fixed the way the title is displayed
//
//   Rev 1.2   13 Sep 2001 17:54:16   HSUCHIN
//added user security permission check
//
//   Rev 1.1   29 Aug 2001 16:12:50   HSUCHIN
//more dialog support added
//
//   Rev 1.0   23 Aug 2001 14:52:08   HSUCHIN
//Initial revision.
 */
