
// TransactionsMonitor.h : main header file for the TransactionsMonitor application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols

#include <dstring.hpp>

// CTransactionsMonitorApp:
// See TransactionsMonitor.cpp for the implementation of this class
//

class CTransactionsMonitorApp : public CWinApp
{
public:
	CTransactionsMonitorApp();

	BOOL SiteConfigInit( const DString&, bool );

	DString GetUserNameEx() const { return strUserName; }
	DString GetPassword() const { return strPassword; }
	DString GetClient() const { return strClient; }

// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

private:
	DString strUserName;
	DString strPassword;
	DString strClient;
};

extern CTransactionsMonitorApp theApp;
