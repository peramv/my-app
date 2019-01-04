#ifndef CANCELLATIONINSTRDLG_H
#define CANCELLATIONINSTRDLG_H
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
//    Copyright 2002 by DST Canada, Inc.
//
//******************************************************************************
//
// ^FILE   : CancellationInstrDlg.h
// ^AUTHOR : Celia Zhang
// ^DATE   : 11/03/2005
//
// ^CLASS    : CancellationInstrDlg
// ^SUBCLASS : 
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************


#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif
#ifndef INCLUDED_VECTOR
   #define INCLUDED_VECTOR
   #include <vector>
#endif

#if _MSC_VER > 1000
   #pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CancellationInstrDlg dialog

class CancellationInstrDlg : public BaseMainDlg
{
// Construction
public:
   CancellationInstrDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
   ~CancellationInstrDlg();
   LRESULT OpenIdentifyAccountsDlg(WPARAM , LPARAM );
	LRESULT OpenFundClassListDlg( WPARAM, LPARAM );

// Dialog Data
   //{{AFX_DATA(CancellationInstrDlg)
   enum
   {
      IDD = IDD_CANCELLATION_INSTR
   };
   // NOTE: the ClassWizard will add data members here
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CancellationInstrDlg)
  
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(CancellationInstrDlg)
	afx_msg void OnBtnRefresh();
	afx_msg void OnBtnMore();
	afx_msg void OnBtnDetails();
	afx_msg void OnBtnSearch();
   afx_msg void OnBtnAdmDates();
	//}}AFX_MSG
   afx_msg void OnDblclkLvResults(NMHDR* pNMHDR, LRESULT* pResult);

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
     * This method can be overridden to respond to data changes in a control.
     * @param controlID - ID of control that is changed.
     * @param strValue - unformatted value of change, this is not meaningful
     *   for a control associated with multiple fields at the same time.
     */
   void ControlUpdated(
                           UINT controlID,
                           const DString &strValue
                      );

   /**
     * This method is optional - override if subclass needs to implement.
     * The override should perform any initialization 
     * required, including getting parameters from InterProcessData (they get
     * cleared after this call).
     * @returns SEVERITY, check conditions if > NO_SEVERITY
     */
   SEVERITY doInit();
   	
	/**
   if overwritten by derived class, return true if nID control should be disabled, otherwise return false
   * @param nID - the control's ID
   * @param bIsNew - current item is new
   */
   bool doDisableControl(UINT nID, bool bIsNew);
     

private:

   DString getCurrentScreenType(){return m_strScreenType;};
   void addControls( );
	void showCriteria();
	void showResults();
	
	DString m_strScreenType;
};
#endif



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/CancellationInstrDlg.h-arc  $
//
//   Rev 1.1   Nov 11 2005 17:01:36   ZHANGCEL
//PET 1286 FN01 -- Make it works properly for the Cancellation Instruction search screen
//
//   Rev 1.0   Nov 04 2005 11:51:04   ZHANGCEL
//Initial revision.
*/
