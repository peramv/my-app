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
//    Copyright 1999 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : MsgSearchDlg.hpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : MsgSearchDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION :
//
// -----------------------------------------------------------------------------
//
//******************************************************************************


#include <ifastgui\BaseMainDlg.h>
#include <uibase\listctrl.h>
#include <uibase\combobase.h>
#include <uibase\dstdatetimectrl.h>

class MsgSearchDlg : public BaseMainDlg
{
public:
   // standard constructor
   MsgSearchDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, 
      GenericInterface* pGIParent, const Command& rCommand);
// Dialog Data
   //{{AFX_DATA(MsgSearchDlg)
   enum
   {
      IDD = IDD_MSG_SEARCH
   };
   //}}AFX_DATA

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(MsgSearchDlg)
public:
   virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:
   virtual bool doRefresh(
      GenericInterface * /*rpGICaller*/, 
      const I_CHAR * /*szOriginalCommand*/ );
   virtual SEVERITY doInit();
   virtual void ControlUpdated(
      UINT controlID, 
      const DString &strValue);
   virtual void OnPostInitDialog();
   virtual bool PreCancel();
   virtual bool doSend ( GenericInterface *rpGICaller, const I_CHAR *szMessage);


   // Generated message map functions
   //{{AFX_MSG(MsgSearchDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnSearch();
   afx_msg void OnSelchangeCmbUsing();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
   void getBrokerFieldId (BFFieldId &brokerId);
   UINT getBrokerEditControlId();
private:
//methods
   void SetDlgCaption();
   bool discardUpdates();
//properties
   CWnd* m_pWndItemInFocus;
   DString m_dstrBackgroundSearch;
};


//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastgui/MsgSearchDlg.h-arc  $
//
//   Rev 1.1   Mar 01 2005 10:52:06   hernando
//PET1117 FN66-68 - Added doSend.
//
//   Rev 1.0   Feb 21 2005 09:59:58   hernando
//Initial revision.
