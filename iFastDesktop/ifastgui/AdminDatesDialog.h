

#ifndef ADMINDATES_H
#define ADMINDATES_H
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : AdminDatesDialog.h
// ^AUTHOR : Yingbao  Li
// ^DATE   : 05/05/1999
//
// ^CLASS    : AdminDatesDialog
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif
#ifndef LISTCTRL_H
   #include <uibase\listctrl.h>
#endif
#ifndef __AFXDTCTL_H__
   #include <afxdtctl.h>
#endif


class AdminDatesDialog : public BaseMainDlg
{
public:
   //**
   // * Standard dialog constructor for DSTC

   AdminDatesDialog( CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
// Dialog Data
   //{{AFX_DATA(AdminDatesDialog)
   enum
   {
      IDD = IDD_ADMINDATES
   };
   CStatic m_DefaultOneTime;

   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(AdminDatesDialog)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   virtual BOOL OnInitDialog();
   //}}AFX_VIRTUAL

// Implementation
protected:
//	virtual bool Cancel();
   //**
   //  * Get parameters from InterProcessData.
   //  * @returns SEVERITY, check conditions if > NO_SEVERITY

   virtual SEVERITY doInit();
   //**
   // * Required implementation for the refresh method.  No refresh activity is
   // * performed for this class.
   //  * @param rpGICaller - A reference pointer to the calling object.
   // * @param szOriginalCommand - A string literal representing the original
   // * command issuing the refresh (which may provide a hint on whether this
   //  * object needs to check for refresh).
   //  * @returns true if successful, call getErrors for errors if false

   virtual bool doRefresh(
                         GenericInterface * /*rpGICaller*/, 
                         const I_CHAR * //*szOriginalCommand
                         );

   /**
     * This is the implementation for OnOk processing to be done.  BaseMainDlg
     * enforces its actions by making OnOk private.
     * @returns a bool with true = perform Ok, false = stop process*/

//	virtual bool Ok();
   // Generated message map functions
   //{{AFX_MSG(AdminDatesDialog)


   //}}AFX_MSG
   virtual void OnPostInitDialog();
   DECLARE_MESSAGE_MAP()
   private:
   void DispInfo();
   DString DisplayType;

};

#endif 