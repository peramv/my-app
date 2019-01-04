#ifndef FIREFIGHTERLOGONDLG_H
#define FIREFIGHTERLOGONDLG_H
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
// ^FILE   : FireFighterLogonDlg.h
// ^AUTHOR : 
// ^DATE   : Dec 3, 2003
//
// ^CLASS    : 
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


class FireFighterLogonDlg : public BaseMainDlg
{

public:

//******************************************************************************
// Dialog Data
//******************************************************************************

   //{{AFX_DATA(FireFighterLogonDlg)
   enum
   {
      IDD = IDD_FIRE_FIGHTER_LOGON
   };
   
   //}}AFX_DATA

   //******************************************************************************
   // Constructor
   //******************************************************************************

   FireFighterLogonDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);

   //******************************************************************************
   // Destructor
   //******************************************************************************

   ~FireFighterLogonDlg(); 

// Implementation
protected:

   //******************************************************************************
   // Overrides
   // ClassWizard generated virtual function overrides
   //******************************************************************************

   //{{AFX_VIRTUAL(FireFighterLogonDlg)   
   //virtual BOOL PreTranslateMessage(MSG* pMsg);
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

   //******************************************************************************
   // Generated message map functions
   //******************************************************************************

   //{{AFX_MSG(FireFighterLogonDlg)
   virtual BOOL OnInitDialog();    
   //}}AFX_MSG
   
   DECLARE_MESSAGE_MAP()

   SEVERITY doInit();


   //******************************************************************************
   // Method to refresh dialog controls
   // @param   GenericInterface *rpGICaller - pointer to the calling object
   // @param   const I_CHAR *szOriginalCommand - Not used in this case, but 
   //                      can be used to instruct special processing.
   // @returns bool - true.
   //******************************************************************************

   virtual bool doRefresh( GenericInterface * /*rpGICaller*/, 
                           const I_CHAR * /*szOriginalCommand*/ );   

   //******************************************************************************
   // Overrides canCancel so that discard dialog does not show up.
   // @returns bool - true.
   //******************************************************************************
   bool canCancel();
   void setDlgTitle();

	virtual bool PreOk();

private:         
   DString			_dstrUserId;

};

#endif

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/FireFighterLogonDlg.hpp-arc  $
//
//   Rev 1.1   Dec 15 2003 11:07:28   linmay
//clean code
//
//   Rev 1.0   Dec 09 2003 09:10:28   linmay
//Initial Revision
//
 */
