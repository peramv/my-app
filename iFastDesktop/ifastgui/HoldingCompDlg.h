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
// ^FILE   : HoldingCompDlg.h
// ^AUTHOR : 
// ^DATE   : 07/26/04
//
// ^CLASS    : HoldingCompDlg
// ^SUBCLASS : 
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************


#include <ifastgui\basemaindlg.h>
#include <ifastgui\ifasthistoricalinfo.hpp>


#if _MSC_VER > 1000
   #pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// HoldingCompDlg dialog

class HoldingCompDlg : public BaseMainDlg
{
// Construction
public:
   HoldingCompDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
   ~HoldingCompDlg();

// Dialog Data
   //{{AFX_DATA(HoldingCompDlg)
   enum
   {
      IDD = IDD_HOLDING_COMP
   };
   // NOTE: the ClassWizard will add data members here
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(HoldingCompDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL
   virtual bool canCancel();

// Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(HoldingCompDlg)
   afx_msg void OnBtnSearch();
   afx_msg void OnBtnReset();
   afx_msg void OnBtnAdd();
   afx_msg void OnBtnDel();
   afx_msg void OnBtnMore(); 
   afx_msg void OnBtnAdmDates(); 
   afx_msg void OnBtnFeeModel(); 
   afx_msg void OnBtnInvoiceInstr(); 
   afx_msg void OnBtnReportingGroup(); 
   afx_msg void OnBtnAdditionalAssets(); 
   afx_msg void OnBtnAccountList(); 
   afx_msg void OnBtnSearchAll();
   afx_msg void OnBtnSearchEffDate();
   afx_msg void OnBtnHistorical();
 
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


   virtual void ControlUpdated(UINT controlID, const DString &strValue);
   bool doDisablePermCheckButton(UINT nID);
   void EnableDisableButtons();
   void DoListItemChanged(UINT listControlID, const DString &strKey, bool bIsNewItem, bool bIsDummyItem);
   void resetChanges();
   virtual bool isKillWorkSessiononTxnError(){return(false);};

private:

   void SetDlgCaption();
   void addControls( );
   DString m_frSCR;
   int   m_rbSearchBy;
   bool isProcSupport;

};

