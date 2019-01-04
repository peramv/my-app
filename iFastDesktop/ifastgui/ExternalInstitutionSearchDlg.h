//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by IFDS Co., Ltd.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2016 by IFDS Co., Ltd.
//
//******************************************************************************
//
// ^FILE   : ExternalInstitutionSearchDlg.h
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : ExternalInstitutionSearchDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : Handles the code for the External Institution Search dialog
//

#pragma once

#include <ifastgui\BaseMainDlg.h>
#include <uibase\ifdslistctrl.h>

/////////////////////////////////////////////////////////////////////////////
// ExternalInstitutionSearchDlg dialog

class ExternalInstitutionSearchDlg : public BaseMainDlg
{
// Construction
public:
   ExternalInstitutionSearchDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);

   virtual ~ExternalInstitutionSearchDlg();

   // Dialog Data
   //{{AFX_DATA(ExternalInstitutionSearchDlg)
   enum
   {
      IDD = IDD_EXTERNAL_INSTITUTION_SEARCH
   };
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(ExternalInstitutionSearchDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:

   virtual bool GetDataForControl(  UINT controlID,
                                    DString &strValueOut,
                                    bool bFormatted,
                                    int index       ) const;
   virtual bool SetDataFromControl(  UINT controlID,
                                     const DString &strValue,
                                     bool bFormatted,
                                     SEVERITY &sevRtn,
                                     int index );
   void ControlUpdated( UINT controlID, const DString &strValue );

   virtual void OnPostInitDialog();
   virtual bool doRefresh(GenericInterface *, const I_CHAR *) {
      return(true);
   }

   virtual bool ListViewControlFilter( long lSubstituteId, const DString *strKey = NULL );
   // Generated message map functions
   //{{AFX_MSG(ExternalInstitutionSearchDlg)
   // NOTE: the ClassWizard will add member functions here
   afx_msg void OnDblclkExternalInstitutionList( NMHDR* pNMHDR, LRESULT* pResult );
   afx_msg void OnBtnSearch();
   afx_msg void OnSelchangeCmbUsing();
   virtual BOOL OnInitDialog();
   afx_msg void OnDestroy();
   afx_msg void OnBtnMore();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()

   DString   m_dstrSearchFor;
   DString   m_dstrSearchUsing;
   DString   m_dstrSearchValue;

   bool      m_bPerformSearch;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastgui/ExternalInstitutionSearchDlg.cpp-arc  $
// 
