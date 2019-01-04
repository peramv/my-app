#pragma once
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by IFDS, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1999 by IFDS, Inc.
//
//******************************************************************************
//
// ^FILE   : DilutionDlg.h
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : DilutionDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : Handles the code for the AMSAcctLvl dialog
//
//******************************************************************************

#include <ifastgui\basemaindlg.h>
#include <ifastgui\ifasthistoricalinfo.hpp>

class DilutionDlg : public BaseMainDlg
{

public:

   DilutionDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
   ~DilutionDlg();

// Dialog Data
   //{{AFX_DATA(DilutionDlg)
   enum
   {
      IDD = IDD_DILUTION
   };
   //}}AFX_DATA

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(DilutionDlg)
public:
   virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:
   // Generated message map functions
   //{{AFX_MSG(DilutionDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnBtnAdd();
   afx_msg void OnBtnDelete();
   afx_msg void OnBtnAdmin();
   afx_msg void OnBtnHistorical();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()

   void OnPostInitDialog();
   virtual bool doRefresh(GenericInterface *rpGICaller, const I_CHAR *szOriginalCommand );
   virtual void ControlUpdated( UINT controlID, const DString &strValue );
   void DoListItemChanged(UINT listControlID, const DString &strKey, bool bIsNewItem, bool bIsDummyItem);
   bool GetDataForControl(UINT controlID, DString &dstrValueOut, bool bFormatted, int index = 0) const;
   bool SetDataFromControl(UINT controlID, const DString &dstrValue, bool bFormatted, SEVERITY &sevRtn, int index);

private:

   void DisplayCaption();
   void HideCPFRelatedControls(bool bHideAndExpand);
   bool ShowHideExSysDilPymtNSMField(bool bSystemFlagToShow);
   bool ShowHideDilutiontNSMField(bool bSystemFlagToShow);
   LRESULT OpenBrokerListDlg( WPARAM, LPARAM );

   DString _dstrFromScreen,
	       _dstrAllowModify;
   static const int _dilutionNumMaxLength = 7;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/DilutionDlg.h-arc  $
//
//   Rev 1.2   Aug 30 2007 15:21:20   jankovii
//PET 2360 FN11 - Dilution.
//
//   Rev 1.1   Jan 09 2006 17:06:20   porteanm
//Incident 424704 - gap - TranshistDilutionAlloc update support.
//
//   Rev 1.0   Mar 03 2005 18:23:14   Fengyong
//Initial revision.
 * 
 */
