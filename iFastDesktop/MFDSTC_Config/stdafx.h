// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#endif

#pragma warning( disable : 4005 4018 4097 4146 4251 4663 4786 4275 )
// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER				// Allow use of features specific to Windows 95 and Windows NT 4 or later.
	#define WINVER 0x0501
#endif
#include <commonport.h>

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows NT 4 or later.
	#define WINVER 0x0501
#endif						

#ifndef _WIN32_WINDOWS		// Allow use of features specific to Windows 98 or later.
	#define WINVER 0x0501
#endif

#ifndef _WIN32_IE			// Allow use of features specific to IE 4.0 or later.
#define _WIN32_IE 0x0501	// Change this to the appropriate value to target IE 5.0 or later.
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// some CString constructors will be explicit

// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes

#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxsock.h>		// MFC socket extensions
#include <afxdlgs.h>

#include <vector>
#include <DString.hpp>

typedef std::vector<DString> CONFIG_VECTOR;
typedef CONFIG_VECTOR::iterator CONFIG_VECTOR_ITER;

extern CONFIG_VECTOR aConfig;
