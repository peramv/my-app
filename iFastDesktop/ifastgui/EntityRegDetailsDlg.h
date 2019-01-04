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
// ^FILE   : EntityRegDetailsDlg.h
// ^AUTHOR : 
// ^DATE   : 23 December 2013
//
// ^CLASS    : EntityRegDetailsDlg
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

class EntityRegDetailsDlg : public BaseMainDlg
{

public:

   //******************************************************************************
   // Dialog Data
   //******************************************************************************

   //{{AFX_DATA(ReportDlg)
   enum
   {
      IDD = IDD_ENTITY_REG_DETAIL
   };    
   //}}AFX_DATA

   //******************************************************************************
   // Constructor
   //******************************************************************************

   EntityRegDetailsDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);

   // Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(FundBrokerDlg)
public:
   //virtual BOOL PreTranslateMessage(MSG* pMsg);
   //}}AFX_VIRTUAL

   //******************************************************************************
   // Destructor
   //******************************************************************************

   virtual ~EntityRegDetailsDlg(); 

   // Implementation
protected:

   //******************************************************************************
   // Overrides
   // ClassWizard generated virtual function overrides
   //******************************************************************************

   //{{AFX_VIRTUAL(AccountRegDetailsDlg)   
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   //******************************************************************************
   // Generated message map functions
   //******************************************************************************

   //{{AFX_MSG(AccountRegDetailsDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnReset();
   afx_msg void OnBtnEntRegAdd();
   afx_msg void OnBtnEntRegDelete();
   afx_msg void OnBtnEntRegHistorical();
   afx_msg void OnBtnEntRegAdmDates(); 
   afx_msg void OnBtnEntRegJurisAdd();
   afx_msg void OnBtnEntRegJurisDelete();
   afx_msg void OnBtnEntRegJurisHistorical();
   afx_msg void OnBtnEntRegJurisAdmDates(); 
   afx_msg void OnBtnHistorical();
   afx_msg void OnChkNoSystemReset();
   afx_msg void OnRbEntityRegDetail();
   afx_msg void OnRbEntityRegJurisDetail();
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

   //virtual void ControlUpdated(UINT controlID, const DString &strValue);

   void DoListItemChanged( UINT listControlID,
                           const DString &strKey,
                           bool bIsNewItem,
                           bool bIsDummyItem );

   virtual bool GetDataForControl( UINT controlID, DString &strValueOut, 
                                   bool bFormatted, int index ) const;

   virtual void ControlUpdated( UINT controlID, const DString &strValue );
   virtual void doDisableNonPermButtons();

private:

   //******************************************************************************
   // All the control hookups are done in this procedure.  This is called by the 
   // OnInitDialog function.
   // @returns void.
   //******************************************************************************
   void addControls();
   void getHeadingList (BFFieldId& idField);
   void showEntityRegDetail();
   void showEntityRegJurisDetail();
};