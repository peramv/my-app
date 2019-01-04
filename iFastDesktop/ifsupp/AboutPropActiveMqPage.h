#pragma once

// Import/Export resolution
#undef IFSUPP_LINKAGE
#ifdef IFSUPP_DLL
#define IFSUPP_LINKAGE CLASS_EXPORT
#else
#define IFSUPP_LINKAGE CLASS_IMPORT
#endif
#include "AboutPropPage.hpp"
#include "resource.h"

// AboutPropActiveMqPage dialog

class IFSUPP_LINKAGE AboutPropActiveMqPage : public CPropertyPage, public AboutPropPage
{
  DECLARE_DYNAMIC(AboutPropActiveMqPage)

 public:
  AboutPropActiveMqPage();
  virtual ~AboutPropActiveMqPage();
  virtual void generateReport(std::wstringstream& ss);

  // Dialog Data
  enum
  {
    IDD = IDD_ABOUT_ACTIVEMQ
  };
  CEdit m_wndTimeout;
  CStatic m_wndPing;
  CStatic m_wndCheck;
  int m_iMinConnections;
  int m_iMaxConnections;
  int m_iCountConnections;
  int m_iInUseConnections;
  int m_iCountFailures;
  CString m_BrokerURLs;
  CString m_User;
  CString m_SingleQueue;
  CString m_MultiQueue;
  CString m_LDAPQueue;
  CString m_AWDQueue;
  CString m_LDAPNS;
  CString m_Password;
  int m_iTimeout;
  BOOL m_bUseSingleConnection;

  CString m_strSMQTest;

  CListCtrl m_connectionList;
  CListCtrl m_viewBatchesList;

  static long checkPort(const CString& strHost, short nPort, CString& strResult);

 protected:
  virtual void DoDataExchange(CDataExchange* pDX);  // DDX/DDV support

  //{{AFX_MSG(AboutPropGeneralPage)
  afx_msg void OnPbPing();
  afx_msg void OnPbCheck();
  afx_msg void OnOK();
  virtual BOOL OnInitDialog();
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP()
};
