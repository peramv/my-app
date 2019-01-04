#ifndef HYPOREDDLG_H
#define HYPOREDDLG_H
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
// ^FILE   : HypoRedDlg.h
// ^AUTHOR : Robert Kovacs
// ^DATE   : 10/29/2002
//
// ^CLASS    : HypoRedDlg
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
// HypoRedDlg dialog

class HypoRedDlg : public BaseMainDlg
{
// Construction
public:
   HypoRedDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
   ~HypoRedDlg();

// Dialog Data
   //{{AFX_DATA(HypoRedDlg)
   enum
   {
      IDD = IDD_HYPOREDEMPTION
   };
   // NOTE: the ClassWizard will add data members here
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(HypoRedDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(HypoRedDlg)
	afx_msg void OnBtnRefresh();
	afx_msg void OnBtnNext();
	afx_msg void OnBtnCalculate();
	afx_msg void OnRadioAmount();
	afx_msg void OnRadioUnits();
	//}}AFX_MSG
   afx_msg void OnAccelSummary();
   afx_msg void OnAccelDetails();
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
   if overwritten by derived class, return true if nID control should be disabled, otherwise return false
   * @param nID - the control's ID
   * @param bIsNew - current item is new
   */
   bool doDisableControl(UINT nID, bool bIsNew);
   /**
     * This method is called after the tab selection changed
     * @param tabControlID - ID of the tab control 
      * @param pageName - Specifies the page name which has been selected
      */ 
   void tabSelectionChanged(UINT tabControlID, const DString& strPageName);
private:

	void SetDlgCaption();
   void addControls( );
	void showCriteria();
	void showHoldings();
	void showResults();
   //this method will check the correct RB based on Criteria::AmtType field's value
   void checkRB();
   void showChargebackCommission();

	DString getCurrentScreenType(){return m_strScreenType;};

	DString m_strScreenType;
	DString m_strSummary;
	DString m_strDetail;
   HACCEL  m_hAccel;
   
   BFFieldId _idHypoRedSummaryAmountHeadingSet;
   BFFieldId _idHypoRedDetailAmountHeadingSet;
   BFFieldId _idHypoRedSummaryUnitsHeadingSet;
   BFFieldId _idHypoRedDetailUnitsHeadingSet;
   BFFieldId _idHypoRedTotalHeadingSet;


};
#endif



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/HypoRedDlg.h-arc  $
//
//   Rev 1.3   May 10 2004 13:46:34   AGUILAAM
//PET985_FN01-1: LSIF HypoCalc enhancement - added clawback fields
//
//   Rev 1.2   Mar 21 2003 18:37:48   PURDYECH
//BFDataGroupId/BFContainerId changeover
//
//   Rev 1.1   Nov 25 2002 09:43:58   KOVACSRO
//Added implementation.
//
//   Rev 1.0   Oct 29 2002 10:55:36   KOVACSRO
//Initial Revision
//
*/
