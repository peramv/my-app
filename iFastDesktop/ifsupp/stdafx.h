// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently

#pragma once

#define NOMINMAX 1      // This resolves the inconsistency between RW and MFC
#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#define WINVER 0x0501
#include <CommonPort.h>
#include <DString.hpp>

#include <afxwin.h>
#include <afxext.h>
#ifndef _AFX_NO_AFXCMN_SUPPORT
   #include <afxcmn.h>
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxdisp.h>
#include <afxdlgs.h>
#include <afxtempl.h>
#include <shlwapi.h>


