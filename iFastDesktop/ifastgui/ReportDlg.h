#ifndef REPORTDLG_H
#define REPORTDLG_H
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2002 by International Financial, Inc.
//
//******************************************************************************
//
// ^FILE   : ReportDlg.h
// ^AUTHOR : 
// ^DATE   : Nov 21, 2002
//
// ^CLASS    : ReportDlg
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

class ReportDlg : public BaseMainDlg
{

public:

//******************************************************************************
// Dialog Data
//******************************************************************************

   //{{AFX_DATA(ReportDlg)
   enum
   {
      IDD = IDD_REPORTS
   };   
   //}}AFX_DATA

   //******************************************************************************
   // Constructor
   //******************************************************************************

   ReportDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);

   //******************************************************************************
   // Destructor
   //******************************************************************************

   ~ReportDlg(); 

// Implementation
protected:

   //******************************************************************************
   // Overrides
   // ClassWizard generated virtual function overrides
   //******************************************************************************

   //{{AFX_VIRTUAL(ReportDlg)   
   virtual BOOL PreTranslateMessage(MSG* pMsg);
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   //******************************************************************************
   // Generated message map functions
   //******************************************************************************

   //{{AFX_MSG(ReportDlg)
   virtual BOOL OnInitDialog();    
   afx_msg void OnRbRunNow();   
   afx_msg void OnRbSchedule();        
   afx_msg void OnBtnAdd();        
   afx_msg void OnBtnDel();
   afx_msg void OnBtnAlloc();
   afx_msg void OnSelchangeRptName();
   //}}AFX_MSG
   
   DECLARE_MESSAGE_MAP()

   SEVERITY doInit();

   void ReportDlg::OnPostInitDialog();

   //******************************************************************************
   // Method to refresh dialog controls
   // @param   GenericInterface *rpGICaller - pointer to the calling object
   // @param   const I_CHAR *szOriginalCommand - Not used in this case, but 
   //                      can be used to instruct special processing.
   // @returns bool - true.
   //******************************************************************************

   virtual bool doRefresh( GenericInterface * /*rpGICaller*/, 
                           const I_CHAR * /*szOriginalCommand*/ );

   void ControlUpdated(UINT controlID, const DString &dstrValue);

   protected:

   void DoListItemChanged( UINT listControlID, const DString &strKey, bool bIsNewItem, bool bIsDummyItem );

   private:

   LRESULT OpenBrokerListDlg ( WPARAM, LPARAM );      
   LRESULT OpenAMSMstrListDlg ( WPARAM, LPARAM );
   LRESULT OpenIdentifyAccountsDlg( WPARAM,LPARAM );

   //******************************************************************************
   // All the control hookups are done in this procedure.  This is called by the 
   // OnInitDialog function.
   // @returns void.
   //******************************************************************************
   void addControls( );

   void setupCriteriaValueControl( const DString &dstrValue );

   void showCriteriaValue ( UINT controlID );

   void loadCriteriaValue ( UINT controlID );

   void activateSchedule ( bool bActivate );

   void activateScheduleRadio ( bool bActivate );

   void activeAllocation ( bool bActive );

   UINT _lastCriteriaValueControl;
   CButton m_rb_run_now;
   CButton m_rb_schedule;
};

#endif

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/ReportDlg.h-arc  $
//
//   Rev 1.2   Mar 21 2003 18:39:52   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.1   Nov 29 2002 13:16:50   HSUCHIN
//added account/ams search and a bug fix for loading controls
//
//   Rev 1.0   Nov 27 2002 11:56:48   HSUCHIN
//Initial Revision
 */
