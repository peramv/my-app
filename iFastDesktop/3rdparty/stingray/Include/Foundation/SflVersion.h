// 
// Build wizard generated file. 
// DO NOT EDIT MANUALLY!!!
//
// Stingray Foundation Library
// SflVersion.h
// 
//////////////////////////////////////////////////////////////////////////////
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
//////////////////////////////////////////////////////////////////////////////
// 
//@doc 
//@module SflVersion.h | Version information and automatic linking settings.
//
// Author:  GF
// <nl>Created: 1/00
// 


#ifndef __SFLVERSION_H__
#define __SFLVERSION_H__

#ifndef _SFL_MFC_SUPPORT
#ifdef _AFX
#define _SFL_MFC_SUPPORT
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// Win32 libraries

//
// Automatic library inclusion macros that use the #pragma/lib feature
//
// Define _SFLNOAUTOLIB when compiling SFL so that it does not try and link to itself.
// Proverbial chicken and egg problem.
//
#ifndef _SFLNOAUTOLIB
#if _MFC_VER >= 0x0421

	
	// If a custom autolink was used, do not bother with the defaults
	#ifndef SFL_CUSTOM_AUTOLINK
	
		// Ok, no custom autolink was used, use the default
		// The default is the configuration last set by the build wizard

		// Auto link options for ATL compatible builds
		#ifndef _SFL_MFC_SUPPORT
			#ifndef _UNICODE
				#if !defined(_SFLDLL) && defined(_DEBUG) 
					#define _SFLAUTOLIBNAME "sfl601wd.lib"
				#elif !defined(_SFLDLL) && !defined(_DEBUG)
					#define _SFLAUTOLIBNAME "sfl601w.lib"
				#elif defined(_SFLDLL) && defined(_DEBUG)
					#define _SFLAUTOLIBNAME "sfl601wsd.lib"
				#elif defined(_SFLDLL) && !defined(_DEBUG)
					#define _SFLAUTOLIBNAME "sfl601ws.lib"
				#endif
			#else
				#if !defined(_SFLDLL) && defined(_DEBUG)
					#define _SFLAUTOLIBNAME "sfl601wud.lib"
				#elif !defined(_SFLDLL) && !defined(_DEBUG)
					#define _SFLAUTOLIBNAME "sfl601wu.lib"
				#elif defined(_SFLDLL) && defined(_DEBUG)
					#define _SFLAUTOLIBNAME "sfl601wsud.lib"
				#elif defined(_SFLDLL) && !defined(_DEBUG)
					#define _SFLAUTOLIBNAME "sfl601wsu.lib"
				#endif
			#endif // _UNICODE without _SFL_MFC_SUPPORT
			
		// Auto link options for MFC compatible library builds
		#else // _SFL_MFC_SUPPORT defined
			#ifndef _UNICODE
				#if !defined(_SFLDLL) && !defined(_AFXDLL) && defined(_DEBUG)
					#define _SFLAUTOLIBNAME "sfl601d.lib"
				#elif !defined(_SFLDLL) && !defined(_AFXDLL) && !defined(_DEBUG)
					#define _SFLAUTOLIBNAME "sfl601.lib"
				#elif !defined(_SFLDLL) && defined(_AFXDLL) && defined(_DEBUG)
					#define _SFLAUTOLIBNAME "sfl601ad.lib"
				#elif !defined(_SFLDLL) && defined(_AFXDLL) && !defined(_DEBUG)
					#define _SFLAUTOLIBNAME "sfl601a.lib"
				#elif defined(_SFLDLL) && defined(_AFXDLL) && defined(_DEBUG)
					#define _SFLAUTOLIBNAME "sfl601asd.lib"
				#elif defined(_SFLDLL) && defined(_AFXDLL) && !defined(_DEBUG)
					#define _SFLAUTOLIBNAME "sfl601as.lib"
				#elif defined(_SFLDLL) && !defined(_AFXDLL)
					#error _SFLDLL is defined but _AFXDLL is not. You must define both.
				#endif
			#else
				#if !defined(_SFLDLL) && !defined(_AFXDLL) && defined(_DEBUG)
					#define _SFLAUTOLIBNAME "sfl601ud.lib"
				#elif !defined(_SFLDLL) && !defined(_AFXDLL) && !defined(_DEBUG)
					#define _SFLAUTOLIBNAME "sfl601u.lib"
				#elif !defined(_SFLDLL) && defined(_AFXDLL) && defined(_DEBUG)
					#define _SFLAUTOLIBNAME "sfl601aud.lib"
				#elif !defined(_SFLDLL) && defined(_AFXDLL) && !defined(_DEBUG)
					#define _SFLAUTOLIBNAME "sfl601au.lib"
				#elif defined(_SFLDLL) && defined(_AFXDLL) && defined(_DEBUG)
					#define _SFLAUTOLIBNAME "sfl601asud.lib"
				#elif defined(_SFLDLL) && defined(_AFXDLL) && !defined(_DEBUG)
					#define _SFLAUTOLIBNAME "sfl601asu.lib"
				#elif defined(_SFLDLL) && !defined(_AFXDLL)
					#error _SFLDLL is defined but _AFXDLL is not. You must define both.
				#endif
			#endif //_UNICODE with _SFL_MFC_SUPPORT
		#endif // _SFL_MFC_SUPPORT
		
	#endif	// SFL_CUSTOM_AUTOLINK

	#pragma comment(lib, _SFLAUTOLIBNAME)
		
	// You may turn off this SFL specific compilation message by adding _SFLNOMSG to your C/C++ preprocessor settings.
	#ifndef _SFLNOMSG
	#pragma message( "Automatically linking with " _SFLAUTOLIBNAME )
	#endif

#endif // _MFC_VER >= 0x0421
#endif // _SFLNOAUTOLIB

#include <ManifestDefs.h>

#endif // __SFLVERSION_H__
