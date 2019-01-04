#ifndef PENSIONINFODLG_H
#define PENSIONINFODLG_H
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
// ^FILE   : PensionInfoDlg.h
// ^AUTHOR : 
// ^DATE   : May 26, 2002
//
// ^CLASS    : PensionInfoDlg
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

class PensionInfoDlg : public BaseMainDlg
{

public:

//******************************************************************************
// Dialog Data
//******************************************************************************

   //{{AFX_DATA(InterestAccrualDlg)
   enum
   {
      IDD = IDD_PENSION_INFO
   };   
   //}}AFX_DATA

//******************************************************************************
// Constructor
//******************************************************************************

   PensionInfoDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);

//******************************************************************************
// Destructor
//******************************************************************************

   ~PensionInfoDlg();  

// Implementation
protected:

//******************************************************************************
// Overrides
// ClassWizard generated virtual function overrides
//******************************************************************************

   //{{AFX_VIRTUAL(PensionInfoDlg)   
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

//******************************************************************************
// Generated message map functions
//******************************************************************************

   //{{AFX_MSG(PensionInfoDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnkillFocusSexDistinct();
   afx_msg void OnBtnReset();
   afx_msg void OnBtnAdmDates();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()

//******************************************************************************
// Method to refresh dialog controls
// @param   GenericInterface *rpGICaller - pointer to the calling object
// @param   const I_CHAR *szOriginalCommand - Not used in this case, but 
//                      can be used to instruct special processing.
// @returns bool - true.
//******************************************************************************

   virtual bool doRefresh( GenericInterface * /*rpGICaller*/, 
                           const I_CHAR * /*szOriginalCommand*/ );

private:

//******************************************************************************
// All the control hookups are done in this procedure.  This is called by the 
// OnInitDialog function.
// @returns void.
//******************************************************************************

   void addControls( );

   bool _bCanLuxMarket;             //True if the current Market is CAN or LUX   
};

#endif

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log $
 */
