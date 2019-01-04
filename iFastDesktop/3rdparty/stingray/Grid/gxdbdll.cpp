///////////////////////////////////////////////////////////////////////////////
// gxdbdll.cpp : implementation of Dll interface for odbc classes (16-Bit only)
//
// Copyright (c) 1997-2012 Rogue Wave Software, Inc.  All Rights Reserved.
//
// This computer software is owned by Rogue Wave Software, Inc. and is protected by
// U.S. copyright laws and other laws and by international treaties. This
// computer software is furnished by Rogue Wave Software, Inc. pursuant to a written
// license agreement and may be used, copied, transmitted, and stored
// only in accordance with the terms of such license agreement and with
// the inclusion of the above copyright notice.  This computer software or
// any other copies thereof may not be provided or otherwise made available
// to any other person.
//
// U.S. Government Restricted Rights.  This computer software:
//      (a) was developed at private expense and is in all respects the
//          proprietary information of Rogue Wave Software, Inc.;
//      (b) was not developed with government funds;
//      (c) is a trade secret of Rogue Wave Software, Inc. for all purposes of the
//          Freedom of Information Act; and
//      (d) is a commercial item and thus, pursuant to Section 12.212
//          of the Federal Acquisition Regulations (FAR) and DFAR
//          Supplement Section 227.7202, Government’s use, duplication or
//          disclosure of the computer software is subject to the restrictions
//          set forth by Rogue Wave Software, Inc.
//
///////////////////////////////////////////////////////////////////////////////
//
// Author: Stefan Hoenig
//

#define _OG_EXPORT_IMPL

#include "stdafx.h"


// compile this file only if ODBC is supported
#ifndef _AFX_NO_DB_SUPPORT

#if _MFC_VER < 0x0300 // 16-bit only

#ifdef _GXDLL
// used for MFC 2.5 Extension DLL
	#undef AFXAPI_DATA
	#define AFXAPI_DATA __based(__segname("_DATA"))
#endif

// Headers 

#ifndef _GXDLL_H_
#include "grid\gxdll.h"
#endif

#ifndef _GXODBC_H_
//#ifndef _WIN64 //RW64
#include "grid\gxodbc.h"
//#endif //_WIN64
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif


#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXDBDLL")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

#ifdef _GXDLL

// MSVC 1.52 shared DLLs
#ifdef _DEBUG
	LPCTSTR szLibName = _T("GXD6116D.DLL");
#else
	LPCTSTR szLibName = _T("GXD6116R.DLL");
#endif

/////////////////////////////////////////////////////////////////////////////
// Initialization of MFC Extension DLL

#include "afxdllx.h"    // standard MFC Extension DLL routines

static AFX_EXTENSION_MODULE NEAR gxDBExtensionDLL = { NULL, NULL };

extern "C" int CALLBACK LibMain(HINSTANCE hInstance, WORD, WORD, LPSTR)
{
	TRACE1("%s Initializing!\n", szLibName);

	// Extension DLL one-time initialization
	AfxInitExtensionModule(gxDBExtensionDLL, hInstance);

	return 1;
}

extern "C" extern void WINAPI GXInitODBCDll()
{
	// Insert this DLL into the resource chain
	new CDynLinkLibrary(gxDBExtensionDLL);
}

#endif // _GXDLL

void GXInitODBC(UINT uiMfcVersion)
{                    
	uiMfcVersion;
#if defined(_GXEXT)
	GXInitODBCDll();
#endif
}

#endif // 16 Bit

#endif // _AFX_NO_DB_SUPPORT
