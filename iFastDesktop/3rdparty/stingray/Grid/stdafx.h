///////////////////////////////////////////////////////////////////////////////
// stdafx.h : include file for standard system include files,
//            or project specific include files that are used frequently, 
//            but are changed infrequently
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

#pragma once

#include <SupportedPlatforms.h>
#include <ProductVersions.h>
#include <StingrayExportDefs.h>

// To suppress ADO messages on Windows 8, uncomment the #define below
//#define ADO_SUPPRESS_MESSAGE

#include "_build.h"

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

// [VC7] The afxdb.h in platform SDK and VC6 undefine UNICODE SQL Functions. To get
// around that include "sql.h" thus defining __SQL

#ifndef _WIN64
#ifndef _AFX_NO_DB_SUPPORT
#include <sql.h>
#include <afxdb.h>          // MFC database classes
#endif
#endif	// _WIN64

#if _MFC_VER >= 0x0400 && !defined(_AFX_NO_AFXCMN_SUPPORT)
#include <afxcmn.h>         // MFC support for Windows 95 Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

// #include <windowsx.h>

#include <afxpriv.h>
#include <ctype.h>

// As of Stingray Studio 2006 x64,
// we use the definition of _OG_EXPORT_IMPL below
// to work with StingrayExportDefs.h

#ifdef _GXDLL
// needed for MFC 3.0
#define GX_DATAEXT      AFX_DATA_EXPORT
// needed for StingrayExportDefs.h
#ifndef _OG_EXPORT_IMPL
	#define _OG_EXPORT_IMPL
#endif
#ifndef GX_DATADEF
	#define GX_DATADEF
#endif
#endif

#ifndef __RWUXTHEME_H
#include <RWUXTheme.h>
#endif

// No need to automatically link with OG libs for this build
#define _GXNOAUTOLIB
#define _GXNODAOAUTOLIB
#define _GXNOODBCAUTOLIB
#define _GXNOADOAUTOLIB

// Don't display message that automatic linking is turned off
#define _GXBUILD

/*
#if !defined(_GXDLL) && !defined(_GXEXT) && _MFC_VER >= 0x0400 && _MFC_VER <= 0x0410
// turn off global optimization for MFC 4.0/4.1
// to prevent Win32s problems with static release builds

#pragma optimize("g", off)
#endif
*/
// SFL DEPENDENCIES--------------------
//#define _SFLNOMSG
#include "Foundation\SflCommon.h"

#ifdef WIN32
#include "foundation\SflDef.h"
#endif
// ------------------------------------

#include "grid\gxall.h"

#if _GX_VER != 0x01301
#pragma message( "You have tried to compile with old Objective Grid header files." )
#pragma message( "Please make sure that you have correctly setup your include directory!" )
#error Wrong header files.
#endif

#if _MFC_VER < 0x0900
#pragma message( "Objective Grid requires Visual C++ 9.0 or later." )
#pragma message( "Please contact Microsoft or Rogue Wave to obtain an upgrade!" )
#error Wrong Visual C++ version.
#endif

#pragma warning( disable : 4700 )  // use of unitialized data
#pragma warning( disable : 4329 4510 4610) // /W1 4329 __declspec(align()) is ignored on enum
										   // /W4 4510 'class' : default constructor could not be generated
										   // /W4 4610 object 'class' can never be instantiated - user-defined constructor required
#pragma warning (disable: 4996) //Deprecated Functions
#pragma warning( disable : 4005 ) 

// [VC7] Macro for IsChildPane. (In VC6, passes last two
// arguments as reference and in VC7 as pointers.)
#if (_MFC_VER >= 0x0700)
#define SPWND_ISCHILDPANE(theClass, argClass, row, col) \
	theClass->IsChildPane(argClass, &row, &col) \

#else
#define SPWND_ISCHILDPANE(theClass, argClass, row, col) \
	theClass->IsChildPane(argClass, row, col) \

#endif

#define _RW_IMPL

