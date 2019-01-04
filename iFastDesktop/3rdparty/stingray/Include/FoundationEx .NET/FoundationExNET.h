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
#if !defined __FOUNDATIONEXNET__H__
#define __FOUNDATIONEXNET__H__

#if _MFC_VER < 0x900
#error Microsoft Visual Studio 2008 SP1, including MFC 9 Feature Pack, or higher is required.
#endif // _MSC_VER

//-----------------------------------------------//
// Library linkage:                              //
// Specify linkage to the correct library name   //
// based on project settings.                    //
//-----------------------------------------------//
#ifndef _SFLEXNET_EXPORT_IMPL
	#if	_MSC_VER > 1400 //VC9 and higher
		#ifndef _UNICODE
			#if   !defined(_SFLEXNETDLL) && !defined(_AFXDLL) &&  defined(_DEBUG)
				#define _FOUNDATIONEXNETAUTOLIBNAME "sflexnet100d.lib"
			#elif !defined(_SFLEXNETDLL) && !defined(_AFXDLL) && !defined(_DEBUG)
				#define _FOUNDATIONEXNETAUTOLIBNAME "sflexnet100.lib"
			#elif !defined(_SFLEXNETDLL) &&  defined(_AFXDLL) &&  defined(_DEBUG)
				#define _FOUNDATIONEXNETAUTOLIBNAME "sflexnet100ad.lib"
			#elif !defined(_SFLEXNETDLL) &&  defined(_AFXDLL) && !defined(_DEBUG)
				#define _FOUNDATIONEXNETAUTOLIBNAME "sflexnet100a.lib"
			#elif  defined(_SFLEXNETDLL) &&  defined(_AFXDLL) &&  defined(_DEBUG) && defined(_MANAGED)
				//#define _RWUXTHEMEDLL
					#define _FOUNDATIONEXNETAUTOLIBNAME "sflexnet100asdm.lib"
			#elif  defined(_SFLEXNETDLL) &&  defined(_AFXDLL) &&  defined(_DEBUG)
				//#define _RWUXTHEMEDLL
					#define _FOUNDATIONEXNETAUTOLIBNAME "sflexnet100asd.lib"
			#elif  defined(_SFLEXNETDLL) &&  defined(_AFXDLL) && !defined(_DEBUG) && defined(_MANAGED)
				//#define _RWUXTHEMEDLL
					#define _FOUNDATIONEXNETAUTOLIBNAME "sflexnet100asm.lib"
			#elif  defined(_SFLEXNETDLL) &&  defined(_AFXDLL) && !defined(_DEBUG)
				//#define _RWUXTHEMEDLL
					#define _FOUNDATIONEXNETAUTOLIBNAME "sflexnet100as.lib"
			#elif  defined(_SFLEXNETDLL) && !defined(_AFXDLL)
				#error One of Stingray Studio DLL defines is specified but _AFXDLL is not. Stingray Studio DLLs cannot be used with static MFC libraries.
			#endif
		#else
			#if   !defined(_SFLEXNETDLL) && !defined(_AFXDLL) &&  defined(_DEBUG)
				#define _FOUNDATIONEXNETAUTOLIBNAME "sflexnet100ud.lib"
			#elif !defined(_SFLEXNETDLL) && !defined(_AFXDLL) && !defined(_DEBUG)
				#define _FOUNDATIONEXNETAUTOLIBNAME "sflexnet100u.lib"
			#elif !defined(_SFLEXNETDLL) &&  defined(_AFXDLL) &&  defined(_DEBUG)
				#define _FOUNDATIONEXNETAUTOLIBNAME "sflexnet100aud.lib"
			#elif !defined(_SFLEXNETDLL) &&  defined(_AFXDLL) && !defined(_DEBUG)
				#define _FOUNDATIONEXNETAUTOLIBNAME "sflexnet100au.lib"
			#elif  defined(_SFLEXNETDLL) &&  defined(_AFXDLL) &&  defined(_DEBUG) && defined(_MANAGED)
				//#define _RWUXTHEMEDLL
					#define _FOUNDATIONEXNETAUTOLIBNAME "sflexnet100asudm.lib"
			#elif  defined(_SFLEXNETDLL) &&  defined(_AFXDLL) &&  defined(_DEBUG)
				//#define _RWUXTHEMEDLL
					#define _FOUNDATIONEXNETAUTOLIBNAME "sflexnet100asud.lib"
			#elif  defined(_SFLEXNETDLL) &&  defined(_AFXDLL) && !defined(_DEBUG) && defined(_MANAGED)
				//#define _RWUXTHEMEDLL
					#define _FOUNDATIONEXNETAUTOLIBNAME "sflexnet100asum.lib"
			#elif  defined(_SFLEXNETDLL) &&  defined(_AFXDLL) && !defined(_DEBUG)
				//#define _RWUXTHEMEDLL
					#define _FOUNDATIONEXNETAUTOLIBNAME "sflexnet100asu.lib"
			#elif  defined(_SFLEXNETDLL) && !defined(_AFXDLL)
				#error One of Stingray Studio DLL defines is specified but _AFXDLL is not. Stingray Studio DLLs cannot be used with static MFC libraries.
			#endif
		#endif // UNICODE
	#endif // MSC_VER >= 1400
#endif // _SFLEXNET_EXPORT_IMPL

#ifdef _FOUNDATIONEXNETAUTOLIBNAME	
	#pragma comment(lib, _FOUNDATIONEXNETAUTOLIBNAME)
	#pragma message( "Automatically linking with " _FOUNDATIONEXNETAUTOLIBNAME)
#endif

// SRSTUDIO-952
// All code in this file is unmanaged code unless specified with the '#pragma managed' tag.
// We specify '#pragma unmanaged' to avoid errors in the initialization of mixed assemblies.
#pragma warning(disable: 4949)
#pragma unmanaged

//-----------------------------------------------//
// Include files for this library.               //
// This header file will add all functionality.  //
// Add to your applications stdafx.h             //
//-----------------------------------------------//

// Dependency on SFLEX
#include "FoundationEx\FoundationEx.h"
// Resource Includes.
#include "FoundationEx .NET\Res\SflResExNET.h"
// WPF
#include "FoundationEx .NET\WPF\Views\SflWPFViewEx_Mngd.h"

#endif // __FOUNDATIONEXNET__H__
