// MFDSTC_Config.h : main header file for the MFDSTC_Config application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


bool isTrue( const std::wstring& wstr );
const std::wstring& asBoolString( BOOL b );

// CMFDSTC_ConfigApp:
// See MFDSTC_Config.cpp for the implementation of this class
//

class CMFDSTC_ConfigApp : public CWinApp
{
public:
	CMFDSTC_ConfigApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFDSTC_ConfigApp theApp;