#pragma once

// Import/Export resolution
#undef IFSUPP_LINKAGE
#ifdef IFSUPP_DLL
   #define IFSUPP_LINKAGE CLASS_EXPORT
#else
   #define IFSUPP_LINKAGE CLASS_IMPORT
#endif

#include "AboutPropPage.hpp"

// AboutPropLogPage dialog

class IFSUPP_LINKAGE AboutPropLogPage : public CPropertyPage, public AboutPropPage
{
   DECLARE_DYNAMIC(AboutPropLogPage)

public:
   AboutPropLogPage();
   virtual ~AboutPropLogPage();
   virtual void generateReport( std::wstringstream& ss );

// Dialog Data
   enum { IDD = IDD_ABOUT_LOG };
   CEdit m_wndLogFile;
   CEdit m_wndLogPath;
   CButton m_btnLogEnable;
   CComboBoxEx m_wndLogLevel;
   CString m_strLogFile;
   CString m_strLogPath;
   BOOL m_bLogEnable;
   int m_iLogLevel;
   CString m_strViewLogPath;
   BOOL m_bViewLogEnable;
   BOOL m_bViewLogAppend;
   BOOL m_bViewLogComplete;
   BOOL m_bViewLogRequest;
   BOOL m_bViewLogResponse;
   CString m_strViewTimingPath;
   BOOL m_bViewTimingEnable;
   CString m_strExceptionPath;
   BOOL m_bExceptionEnable;

   BOOL m_bDisplayConditionName;
   BOOL m_bDisplayClientNamePane;
   BOOL m_bDesktopWebURL;

   CButton m_checkBoxSaveDesktopWebURL;



protected:
   virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

   //{{AFX_MSG(AboutPropLogPage)
   virtual BOOL OnInitDialog();
   virtual void OnOK();
   //}}AFX_MSG

   DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCheckDesktopWebUrl();
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifsupp/AboutPropLogPage.h-arc  $
//
//   Rev 1.0   Dec 05 2011 09:03:44   purdyech
//Initial revision.
//
//   Rev 1.3   Dec 22 2009 06:33:34   dchatcha
//IN# 1952546 - Indicator to show that the database DSK is connected to is scrambled.
 *
 */
