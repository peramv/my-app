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
// ^FILE   : TaxExemptAuthorizationDlg.h
// ^AUTHOR : Celia Zhang
// ^DATE   : July 15, 2004
//
// ^CLASS    : TaxExemptAuthorizationDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************


#include <ifastgui\basemaindlg.h>
#include <ifastgui\ifasthistoricalinfo.hpp>
#include <uibase\ifdslistctrl.h>

#if _MSC_VER > 1000
   #pragma once
#endif // _MSC_VER > 1000

class TaxExemptAuthorizationDlg : public BaseMainDlg
{

public:

//******************************************************************************
// Dialog Data
//******************************************************************************

   //{{AFX_DATA(ReportDlg)
   enum
   {
      IDD = IDD_TAX_EXEMPT_AUTHORIZATION
   };    
   //}}AFX_DATA

   //******************************************************************************
   // Constructor
   //******************************************************************************

   TaxExemptAuthorizationDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);

   // Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(FundBrokerDlg)
   public:
   virtual BOOL PreTranslateMessage(MSG* pMsg);
   //}}AFX_VIRTUAL
   
	//******************************************************************************
   // Destructor
   //******************************************************************************

   ~TaxExemptAuthorizationDlg(); 

// Implementation
protected:

   //******************************************************************************
   // Overrides
   // ClassWizard generated virtual function overrides
   //******************************************************************************

   //{{AFX_VIRTUAL(TaxExemptAuthorizationDlg)   
   //virtual BOOL PreTranslateMessage(MSG* pMsg);
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   //******************************************************************************
   // Generated message map functions
   //******************************************************************************

   //{{AFX_MSG(TaxExemptAuthorizationDlg)
   afx_msg void OnBtnReset();
   afx_msg void OnBtnAdd();
   afx_msg void OnBtnDelete();
   afx_msg void OnBtnAdmDates(); 
   afx_msg void OnBtnMore();
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
	virtual void ControlUpdated(UINT controlID, const DString &strValue);
	void DoListItemChanged( UINT listControlID,
                           const DString &strKey,
                           bool bIsNewItem,
                           bool bIsDummyItem );

   LRESULT OpenFundClassListDlg( WPARAM, LPARAM );

	void ExemptTypeControlUpdated();
  
private:
   
	//******************************************************************************
	// All the control hookups are done in this procedure.  This is called by the 
	// OnInitDialog function.
	// @returns void.
	//******************************************************************************
	void addControls();
	void EnableDisableDeleteButton();
	void getHeadingList (BFFieldId& idField);

	DString dstrMarket;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/TaxExemptAuthorizationDlg.h-arc  $
//
//   Rev 1.2   Nov 28 2005 09:57:08   jankovii
//PET1228_FN02_ EU Savings Directive Phase Two
//
//   Rev 1.1   Mar 04 2005 16:43:42   georgeet
//PET1171 FN01 - EU Savings Directive Tax Exemption.  Modified the existing screen to include four new fields with appropriate business logic.
//
//   Rev 1.0   Aug 06 2004 17:53:48   ZHANGCEL
//Initial revision.
//
 */
