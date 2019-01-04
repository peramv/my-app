#pragma once
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
//    Copyright 2002 by International Financial Ltd.
//
//******************************************************************************
//
// ^FILE   : FeeModelDlg.h
// ^AUTHOR : 
// ^DATE   : 07/26/04
//
// ^CLASS    : FeeModelDlg
// ^SUBCLASS : 
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************


#include <ifastgui\BaseMainDlg.h>
#include <ifastgui\ifasthistoricalinfo.hpp>


#if _MSC_VER > 1000
   #pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// FeeModelDlg dialog

class FeeModelDlg : public BaseMainDlg
{
// Construction
public:
   FeeModelDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
   ~FeeModelDlg();

// Dialog Data
   //{{AFX_DATA(FeeModelDlg)
   enum
   {
      IDD = IDD_FEE_MODEL
   };
   // NOTE: the ClassWizard will add data members here
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(FeeModelDlg)
public:
   virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL
   virtual bool canCancel();
   virtual bool isKillWorkSessiononTxnError();
   virtual void DoListItemChanged(UINT listControlID, const DString &strKey, bool bIsNewItem, bool bIsDummyItem);

// Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(FeeModelDlg)
   afx_msg void OnBtnReset();
   afx_msg void OnBtnAdd();
   afx_msg void OnBtnDel();
   afx_msg void OnBtnMore(); 
   afx_msg void OnBtnAdmDates(); 
   afx_msg void OnBtnSearch();
   afx_msg void OnBtnAccountList();
   afx_msg void OnBtnSearchAll();
   afx_msg void OnBtnSearchEffDate();
   afx_msg void OnBtnFundList();
   afx_msg void OnBtnHistorical();
   afx_msg void OnChkFullMoneyOutApplicable();
   afx_msg void OnBtnCopyToNewModel();

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
   bool doRefresh(
                 GenericInterface * /*rpGICaller*/, 
                 const I_CHAR * /*szOriginalCommand*/
                 );
   /**
     * This method is invoked by the base architecture after OnInitDialog has 
     * completed.  This should be implemented for time intensive setup so that
     * the screen can display quickly and then do this processing.
     */
   void OnPostInitDialog();


   /**
     * This method is optional - override if subclass needs to implement.
     * The override should perform any initialization 
     * required, including getting parameters from InterProcessData (they get
     * cleared after this call).
     * @returns SEVERITY, check conditions if > NO_SEVERITY
     */
   SEVERITY doInit();


   virtual void ControlUpdated(
                              UINT controlID,
                              const DString &strValue
                              );
   bool doDisablePermCheckButton(UINT nID);
   void ShowHideControls();
   void resetChanges();
   LRESULT OpenHoldingCompDlg( WPARAM, LPARAM );

private:

   void SetDlgCaption();
   void addControls( );
   DString m_frSCR;
   int   m_rbSearchBy;

};



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/FeeModelDlg.h-arc  $
//
//   Rev 1.2   Oct 15 2004 16:06:38   FENGYONG
//PTS10034766 - disable add and delete when access FeeModel from fundsponsor fee model screen.
//
//   Rev 1.1   Aug 10 2004 11:28:32   FENGYONG
//PET 1117 FN5 - Client Condition Fee
//
//   Rev 1.0   Aug 09 2004 09:56:38   FENGYONG
//Initial Revision
//
//   Rev 1.7   Apr 04 2003 16:05:32   PURDYECH
//Sync 1.6.2.0 back to trunk
//
//   Rev 1.6.2.0   Mar 21 2003 18:36:26   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.6.1.0   Mar 05 2003 11:31:22   PURDYECH
//Use IFastHistoricalInfo instead of deriving from IFastBaseMainDlg
//
//   Rev 1.6   Feb 20 2003 09:28:06   YINGBAOL
//add doDisableControl and doDisablePermCheckButton
//
//   Rev 1.5   Jan 29 2003 16:22:26   popescu
//Added the historical button for FeeParamSysDlg and FeeModelDlg
//
//   Rev 1.4   Jan 22 2003 17:49:22   YINGBAOL
//clean some unused code
//
//   Rev 1.3   Jan 03 2003 19:39:30   YINGBAOL
//add logic for commission Group
//
//   Rev 1.2   Oct 09 2002 23:55:40   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.1   Feb 22 2002 14:17:28   YINGBAOL
//add more function
//
*/
