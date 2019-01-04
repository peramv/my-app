#ifndef ACBDLG_H
#define ACBDLG_H
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
// ^FILE   : ACBDlg.h
// ^AUTHOR : Zijian Ying
// ^DATE   : 04/19/1999
//
// ^CLASS    : ACBDlg
// ^SUBCLASS : BaseMainDlg
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************

#ifndef BASEMAINDLG_H
   #include <ifastgui\BaseMainDlg.h>
#endif

//#include <uibase\listctrl.h>

#include <bfutil\bfdate.hpp>

#if _MSC_VER > 1000
   #pragma once
#endif // _MSC_VER > 1000
// ACBDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ACBDlg dialog

class ACBDlg : public BaseMainDlg
{
// Construction
public:
   ACBDlg(CWnd* pParent, GenericInterfaceContainer* pGIC, GenericInterface* pGIParent, const Command& rCommand);
   virtual bool GetOverrideItemString(long lSubstituteId, const DString& ColumnKey, DString& strOut);

// Dialog Data
   //{{AFX_DATA(ACBDlg)
   enum
   {
      IDD = IDD_ACB
   };
   //ListViewControl m_ACBList;
   CComboBox m_FundList;
   CString m_RealizedGain;
   CString m_AdjustedCost;
   CString m_UnitACB;
   CString m_CurrentNAV;
   CString m_MarketValue;
   CString m_AccountCurrency;
   CString m_FundCurrency;
   //}}AFX_DATA


// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(ACBDlg)
protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
   //}}AFX_VIRTUAL

// Implementation
protected:

   // Generated message map functions
   //{{AFX_MSG(ACBDlg)
   virtual BOOL OnInitDialog();
   afx_msg void OnMore();
   //afx_msg void OnItemchangedLvAcbTrans(NMHDR* pNMHDR, LRESULT* pResult);
   afx_msg void OnSelendokCmbFund();
   afx_msg void OnBtnHistorical();
   afx_msg void OnBtnReset();
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()

   void OnPostInitDialog();

   virtual SEVERITY doInit();
   virtual bool doRefresh( GenericInterface * /*rpGICaller*/, 
                           const I_CHAR * /*szOriginalCommand*/ );
   virtual void DoListItemChanged (UINT listControlID,
                                   const DString &strKey, 
                                   bool bIsNewItem, 
                                   bool bIsDummyItem);

   //virtual void ControlUpdated( UINT controlID, const DString &strValue );
   virtual bool GetDataForControl( UINT controlID, DString &strValueOut, 
                                   bool bFormatted, int index ) const;
private:
   void ClearText();
   void getMarketValue(DString& FundCode, DString& ClassCode, CString& MV);
   void getCurNAV(DString& FundCode, DString& ClassCode, CString & NAV, CString &cstrFundCurrency);
   void getFunandClass(CString& src, DString& fundCode, DString& fundClass);
   DString AccountNum,FundCode,ClassCode,AccountCurrency;
   void makeFundClassString(DString& FundCode, DString& Class, CString& out);
   void PopulateFundAndFundClass();
   bool isFndClsACBAvailable(DString fndCode, DString classCode);
   CStringList Fund,FundClass;
   void DisplayTitle();
   void PopulateACBList();
   void updatePlugControls(void);
   void displayGIAOpeningMV();
   void displayT5EventDate();
   
   BFDate::DATE_FORMAT getDateFormatFromClientLocale(const ClientLocale& rLocale) const;
   BFDate::DATE_FORMAT inferMaskFormat( const DString& dstrMask ) const;
   
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
//}}AFX_INSERT_LOCATION

#endif // !defined(AFX_ACBDLG_H__0853BCF0_F669_11D2_AD64_00C04F572654__INCLUDED_)

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
// $Log:   Y:/VCS/BF iFAST/ifastgui/ACBDlg.hpp-arc  $
//
