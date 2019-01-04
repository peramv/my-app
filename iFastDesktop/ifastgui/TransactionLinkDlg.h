#pragma once
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
//    Copyright 2005 by IFDS.
//
//******************************************************************************
//
// ^FILE   : TransactionLinkDlg.h
// ^AUTHOR : Yingbao  Li
// ^DATE   : 26/06/2005
//
//
//
//******************************************************************************

/////////////////////////////////////////////////////////////////////////////
// Transaction Link

/**
 * Class that displays internal link for tranctions.
 *
 * @author Yingbao Li
 * </dd></dl><p><dl><dt><b>Date Created:</b></dt><dd> 06/25/2005</dd></dl>
 * @version 0.1
 */

#include <ifastgui\BaseMainDlg.h>
#include <uibase\ifdslistctrl.h>
class TransactionLinkDlg : public BaseMainDlg
{
public:
   TransactionLinkDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
   ~TransactionLinkDlg(){}
   enum
   {
      IDD = IDD_TRANS_LINK
   };
   //}}AFX_DATA

// Overrides
   // ClassWizard generated virtual function overrides
protected:
   //{{AFX_VIRTUAL(TransactionLinkDlg)
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

   //}}AFX_VIRTUAL
// Implementation
   protected:
   // Generated message map functions
   //{{AFX_MSG(TransactionLinkDlg)

	DECLARE_MESSAGE_MAP()


   //}}AFX_MSG
protected:
   virtual SEVERITY doInit();
   virtual bool doRefresh(
                          GenericInterface * /*rpGICaller*/, 
                          const I_CHAR * //*szOriginalCommand
                          );
   virtual BOOL OnInitDialog(); 
   virtual void OnPostInitDialog();

private:
   void setWinTitle();
   DString accountNum_,transNum_;
   
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/TransactionLinkDlg.h-arc  $
//
//   Rev 1.0   Jul 06 2005 16:44:02   Yingbaol
//Initial revision.
 * 
 * 
 */

