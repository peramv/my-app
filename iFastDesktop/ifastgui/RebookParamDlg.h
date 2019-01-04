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
// ^FILE   : RebookParamDlg.h
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
class RebookParamDlg : public BaseMainDlg
{
public:
   RebookParamDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
   ~RebookParamDlg(){}
   enum
   {
      IDD = IDD_REBOOK_PARAM
   };
   //}}AFX_DATA

// Overrides
   // ClassWizard generated virtual function overrides
protected:
   //{{AFX_VIRTUAL(RebookParamDlg)
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

   //}}AFX_VIRTUAL
// Implementation
   protected:
   // Generated message map functions
   //{{AFX_MSG(RebookParamDlg)
   afx_msg void OnRbSameAccountTransType();
   afx_msg void OnRbDiffAccountTransType();
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


   void setDlgTitle();
   DString accountNum_,transNum_;
   
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/RebookParamDlg.h-arc  $
//
//   Rev 1.0   Jul 06 2005 16:41:30   Yingbaol
//Initial revision.
 * 
 * 
 */

