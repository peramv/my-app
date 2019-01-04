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
//    Copyright 2000 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : FundClassDlg.h
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : FundClassDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : Handles the code for the Remarks dialog
//
//
//
// -----------------------------------------------------------------------------
#pragma once

#include <ifastgui\BaseMainDlg.h>
#include <uibase\ifdslistctrl.h>

/////////////////////////////////////////////////////////////////////////////
// FundClassDlg dialog

class FundClassDlg : public BaseMainDlg
{
// Construction
public:
   FundClassDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);

   virtual ~FundClassDlg();

   // Dialog Data
   //{{AFX_DATA(FundClassDlg)
   enum
   {
      IDD = IDD_FUND_SEARCH
   };
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(FundClassDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:
   bool GetOverrideItemString(long lSubstituteId, const DString &ColumnKey, DString &strOut);
   /**
  * Required implementation for the refresh method.  No refresh activity is
  * performed for this class. 
  * @param rpGICaller - A reference pointer to the calling object.
  * @param szOriginalCommand - A string literal representing the original
  * command issuing the refresh (which may provide a hint on whether this
  * object needs to check for refresh).
  * @returns true if successful, call getErrors for errors if false
  */
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
   virtual bool PreOk();
   virtual SEVERITY init2();
   virtual bool ListViewControlFilter( long lSubstituteId, const DString *strKey = NULL );
   void HideColumnForFundIDGrid(IFDSListBase* const pBaseCtrl);	
   // Generated message map functions
   //{{AFX_MSG(FundClassDlg)
   // NOTE: the ClassWizard will add member functions here
   afx_msg void OnDblclkFundClassList( NMHDR* pNMHDR, LRESULT* pResult );
   afx_msg void OnBtnSearch();
   afx_msg void OnSelchangeCmbUsing();
   afx_msg void OnSelchangeCmbFor();
   virtual BOOL OnInitDialog();
   afx_msg void OnDestroy();
   afx_msg void OnKillfocusSearchValue();
   afx_msg void OnBtnMore();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()

   DString   m_dstrSearchFor;
   DString   m_dstrSearchUsing;
   DString   m_dstrFundCode;
   DString   m_dstrFundNumber;
   DString   m_dstrFundClass;
   DString   m_dstrNameLanguage;
   DString   m_fundCategory;
   DString   m_dstrSearchValue;

   bool      m_bPerformSearch;
};

