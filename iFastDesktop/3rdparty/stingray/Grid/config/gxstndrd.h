// This is a part of the Objective Grid C++ Library.
// Copyright © 1999-2004 Quovadx, Inc.  All Rights Reserved.
// 
// 
// This computer software is owned by Quovadx, Inc. and is protected by 
// U.S. copyright laws and other laws and by international treaties. This 
// computer software is furnished by Quovadx, Inc. pursuant to a written 
// license agreement and may be used, copied, transmitted, and stored 
// only in accordance with the terms of such license agreement and with 
// the inclusion of the above copyright notice.  This computer software or 
// any other copies thereof may not be provided or otherwise made available 
// to any other person.
// 
// U.S. Government Restricted Rights.  This computer software: 
//      (a) was developed at private expense and is in all respects the 
//          proprietary information of Quovadx, Inc.; 
//      (b) was not developed with government funds; 
//      (c) is a trade secret of Quovadx, Inc. for all purposes of the 
//          Freedom of Information Act; and 
//      (d) is a commercial item and thus, pursuant to Section 12.212 
//          of the Federal Acquisition Regulations (FAR) and DFAR 
//          Supplement Section 227.7202, Government’s use, duplication or 
//          disclosure of the computer software is subject to the restrictions 
//          set forth by Quovadx, Inc.
//
//
// This source code is only intended as a supplement to
// the Objective Grid Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding
// the Objective Grid product.
//
// Author: Stefan Hoenig
//

// gxstndrd.h : Generated Configuration Info for 
//                    configuration "gxstndrd"
//

// To automatically link your application with this configuration:
//
// Add 
// #include "config/gxstndrd.h" 
// before 
// #include "gxall.h" 
// in your application's stdafx.h file.

#ifndef _GXCONFIG_H_
#define _GXCONFIG_H_

#define _GXSTD		1	// This is an Objective Grid Standard Build

#ifdef _GXEXT
#undef _GXDLL
#define _GXDLL
#endif

/////////////////////////////////////////////////////////////////////////////
// Win32 libraries

//
// Automatic library inclusion macros that use the #pragma/lib feature
//
// Define _GXNOAUTOLIB when compiling OG so that it does
// not try and link to itself. -chicken and egg.
//
#if _MFC_VER >= 0x0300

#ifndef _GXNOAUTOLIB

	#ifndef _UNICODE
		#if !defined(_GXDLL) && !defined(_AFXDLL) && defined(_DEBUG)
			#define _GXAUTOLIBNAME "og903d.lib"
		#elif !defined(_GXDLL) && !defined(_AFXDLL) && !defined(_DEBUG)
			#define _GXAUTOLIBNAME "og903.lib"
		#elif !defined(_GXDLL) && defined(_AFXDLL) && defined(_DEBUG)
			#define _GXAUTOLIBNAME "og903ad.lib"
		#elif !defined(_GXDLL) && defined(_AFXDLL) && !defined(_DEBUG)
			#define _GXAUTOLIBNAME "og903a.lib"
		#elif defined(_GXDLL) && defined(_AFXDLL) && defined(_DEBUG)
			#define _GXAUTOLIBNAME "og903asd.lib"
		#elif defined(_GXDLL) && defined(_AFXDLL) && !defined(_DEBUG)
			#define _GXAUTOLIBNAME "og903as.lib"
		#elif defined(_GXDLL) && !defined(_AFXDLL)
			#error _GXDLL is defined but _AFXDLL is not. You must define both.
		#endif
	#else
		#if !defined(_GXDLL) && !defined(_AFXDLL) && defined(_DEBUG)
			#define _GXAUTOLIBNAME "og903ud.lib"
		#elif !defined(_GXDLL) && !defined(_AFXDLL) && !defined(_DEBUG)
			#define _GXAUTOLIBNAME "og903u.lib"
		#elif !defined(_GXDLL) && defined(_AFXDLL) && defined(_DEBUG)
			#define _GXAUTOLIBNAME "og903aud.lib"
		#elif !defined(_GXDLL) && defined(_AFXDLL) && !defined(_DEBUG)
			#define _GXAUTOLIBNAME "og903au.lib"
		#elif defined(_GXDLL) && defined(_AFXDLL) && defined(_DEBUG)
			#define _GXAUTOLIBNAME "og903asud.lib"
		#elif defined(_GXDLL) && defined(_AFXDLL) && !defined(_DEBUG)
			#define _GXAUTOLIBNAME "og903asu.lib"
		#elif defined(_GXDLL) && !defined(_AFXDLL)
			#error _GXDLL is defined but _AFXDLL is not. You must define both.
		#endif
	#endif

	#pragma comment(lib, _GXAUTOLIBNAME)

	// You may turn off OG specific compilation messase
	// by adding _GXNOMSG to your C/C++ settings.
	#ifndef _GXNOMSG
		#pragma message( "Automatically linking with " _GXAUTOLIBNAME )
	#endif

#else

#define _GXAUTOLIBNAME ""

#if !defined(_GXBUILD) && !defined(_GXNOMSG)
	#pragma message( "Automatic Linking for Objective Grid libraries is turned off." )
#endif

#endif // _GXNOAUTOLIB

#endif // MFC_VER

#endif // _GXCONFIG_H_

