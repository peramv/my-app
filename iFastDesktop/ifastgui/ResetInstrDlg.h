#pragma once
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
//    Copyright 2003 by International Financial, Inc.
//
//******************************************************************************
//
// ^FILE   : ResetInstrDlg.h
// ^AUTHOR : 
// ^DATE   : Jan 24, 2003
//
// ^CLASS    : ResetInstrDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

#include <ifastgui\BaseMainDlg.h>
#include <ifastgui\ifasthistoricalinfo.hpp>

class ResetInstrDlg : public BaseMainDlg
{

public:

//******************************************************************************
// Dialog Data
//******************************************************************************

   //{{AFX_DATA(ResetInstrDlg)
   enum
   {
      IDD = IDD_RESET_INSTRUCTIONS
   };    
   //}}AFX_DATA

   //******************************************************************************
   // Constructor
   //******************************************************************************

   ResetInstrDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);

   //******************************************************************************
   // Destructor
   //******************************************************************************

   ~ResetInstrDlg(); 

// Implementation
protected:

   //******************************************************************************
   // Overrides
   // ClassWizard generated virtual function overrides
   //******************************************************************************

   //{{AFX_VIRTUAL(ResetInstrDlg)   
   virtual BOOL PreTranslateMessage(MSG* pMsg);
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   //******************************************************************************
   // Generated message map functions
   //******************************************************************************

   //{{AFX_MSG(ResetInstrDlg)
   virtual BOOL OnInitDialog();    
   afx_msg void OnBtnMore();        
   afx_msg void OnBtnHistorical();   
   afx_msg void OnBtnSearch();   
   afx_msg void OnBtnAdd();
   afx_msg void OnBtnDelete();
   afx_msg void OnBtnReset();
   afx_msg void OnBtnReverse();
   //}}AFX_MSG
   
   DECLARE_MESSAGE_MAP()

   SEVERITY doInit();

   void OnPostInitDialog();

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
   bool doDisablePermCheckButton(UINT nID);
   void DoListItemChanged(UINT listControlID, const DString &strKey, bool bIsNewItem, bool bIsDummyItem);
private:
   
   //******************************************************************************
   // All the control hookups are done in this procedure.  This is called by the 
   // OnInitDialog function.
   // @returns void.
   //******************************************************************************
   void addControls( );  
   void showCriteriaValue ( UINT controlID );
   void loadCriteriaValue ( UINT controlID );
   void setupCriteriaValueControl( const DString &dstrValue );
   LRESULT OpenIdentifyAccountsDlg( WPARAM,LPARAM );
   LRESULT OpenFundClassListDlg( WPARAM, LPARAM );

   int iCurrentAccountId, _lastCriteriaValueControl;
   DString _dstrParent;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/ResetInstrDlg.h-arc  $
//
//   Rev 1.7   Jul 08 2003 15:01:40   HERNANDO
//PTS 10019155.
//
//   Rev 1.6   May 29 2003 09:26:18   sanchez
//Function prototype for DoListItemChanged() to diable Historical button for new and dummy records. PTS 10016740
//
//   Rev 1.5   Mar 21 2003 18:40:06   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.4   Mar 05 2003 11:30:02   PURDYECH
//Use IFastHistoricalInfo instead of deriving from IFastBaseMainDlg
//
//   Rev 1.3   Jan 29 2003 16:26:08   HSUCHIN
//added support for historical
//
//   Rev 1.2   Jan 27 2003 07:44:22   HSUCHIN
//added support for reversal
//
//   Rev 1.1   Jan 26 2003 16:05:18   HSUCHIN
//added more functionality
//
//   Rev 1.0   Jan 24 2003 16:11:20   HSUCHIN
//Initial Revision
 */
