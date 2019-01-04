#ifndef ENTITYADDRESSSEARCHDLG_H
#define ENTITYADDRESSSEARCHDLG_H
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
// ^FILE   : EntityAddressSearchDlg.h
// ^AUTHOR : Robert Kovacs
// ^DATE   : 02/25/2003
//
// ^CLASS    : EntityAddressSearchDlg
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
// EntityAddressSearchDlg dialog

class EntityAddressSearchDlg : public BaseMainDlg
{
// Construction
public:
   EntityAddressSearchDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
   ~EntityAddressSearchDlg();

// Dialog Data
   //{{AFX_DATA(EntityAddressSearchDlg)
   enum
   {
      IDD = IDD_ENTITY_ADDRESS_SEARCH 
   };
   // NOTE: the ClassWizard will add data members here
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(EntityAddressSearchDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(EntityAddressSearchDlg)
	afx_msg void OnDblclkEntityAddressList( NMHDR* pNMHDR, LRESULT* pResult );
	afx_msg void OnBtnRefresh();
	afx_msg void OnBtnMore();
	afx_msg void OnBtnSearch();
	afx_msg void OnDestroy();
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
	BOOL OnInitDialog() ;

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
   void ControlUpdated( UINT controlID, const DString &strValue );
   virtual bool PreOk();  
  
private:

   void addControls( );
	void showDefaultSearchControls();
	void showResults();
	void showCriteria();
};
#endif



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/EntityAddressSearchDlg.h-arc  $
//
//   Rev 1.0   Mar 10 2005 16:18:54   ZHANGCEL
//Initial revision.
*/
