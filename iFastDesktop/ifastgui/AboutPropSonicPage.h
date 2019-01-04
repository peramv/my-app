#pragma once

#include <uibase/ListCtrl.h>
#include "AboutPropPage.hpp"

// AboutPropSonicPage dialog

class AboutPropSonicPage : public CPropertyPage, public AboutPropPage
{
	DECLARE_DYNAMIC(AboutPropSonicPage)

public:
	AboutPropSonicPage();
	virtual ~AboutPropSonicPage();
   virtual void generateReport( std::wstringstream& ss );

// Dialog Data
	enum { IDD = IDD_ABOUT_SONIC };
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
   CString m_LDAPNS;
   CString m_Password;
   int m_iTimeout;
   BOOL m_bUseSingleConnection;

   CString m_strSMQTest;

   ListViewControl m_connectionList;
   ListViewControl m_viewBatchesList;

   static long checkPort( const CString& strHost, short nPort, CString& strResult );
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

   //{{AFX_MSG(AboutPropGeneralPage)
   afx_msg void OnPbPing();
   afx_msg void OnPbCheck();
   afx_msg void OnOK();
   virtual BOOL OnInitDialog();
   //}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};
