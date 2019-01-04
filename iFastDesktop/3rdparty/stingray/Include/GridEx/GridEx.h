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
#if !defined __GRIDEX__H__
#define __GRIDEX__H__

#if _MFC_VER < 0x900
#error Microsoft Visual Studio 2008 SP1, including MFC 9 Feature Pack, or higher is required.
#endif // _MSC_VER

//-----------------------------------------------//
// Library linkage:                              //
// Specify linkage to the correct library name   //
// based on project settings.                    //
//-----------------------------------------------//
#ifndef _OGEX_EXPORT_IMPL
	#if	_MSC_VER > 1400 //VC9 and higher
		#ifndef _UNICODE
			#if   !defined(_OGEXDLL) && !defined(_AFXDLL) &&  defined(_DEBUG)
				#define _GRIDEXAUTOLIBNAME "ogex201d.lib"
			#elif !defined(_OGEXDLL) && !defined(_AFXDLL) && !defined(_DEBUG)
				#define _GRIDEXAUTOLIBNAME "ogex201.lib"
			#elif !defined(_OGEXDLL) &&  defined(_AFXDLL) &&  defined(_DEBUG)
				#define _GRIDEXAUTOLIBNAME "ogex201ad.lib"
			#elif !defined(_OGEXDLL) &&  defined(_AFXDLL) && !defined(_DEBUG)
				#define _GRIDEXAUTOLIBNAME "ogex201a.lib"
			#elif  defined(_OGEXDLL) &&  defined(_AFXDLL) &&  defined(_DEBUG)
				//#define _RWUXTHEMEDLL
				#if defined _MANAGED
					#define _GRIDEXAUTOLIBNAME "ogex201asdm.lib"
				#else
					#define _GRIDEXAUTOLIBNAME "ogex201asd.lib"
				#endif
			#elif  defined(_OGEXDLL) &&  defined(_AFXDLL) && !defined(_DEBUG)
				//#define _RWUXTHEMEDLL
				#if defined _MANAGED
					#define _GRIDEXAUTOLIBNAME "ogex201asm.lib"
				#else
					#define _GRIDEXAUTOLIBNAME "ogex201as.lib"
				#endif
				
			#elif  defined(_OGEXDLL) && !defined(_AFXDLL)
				#error One of Stingray Studio DLL defines is specified but _AFXDLL is not. Stingray Studio DLLs cannot be used with static MFC libraries.
			#endif
		#else
			#if   !defined(_OGEXDLL) && !defined(_AFXDLL) &&  defined(_DEBUG)
				#define _GRIDEXAUTOLIBNAME "ogex201ud.lib"
			#elif !defined(_OGEXDLL) && !defined(_AFXDLL) && !defined(_DEBUG)
				#define _GRIDEXAUTOLIBNAME "ogex201u.lib"
			#elif !defined(_OGEXDLL) &&  defined(_AFXDLL) &&  defined(_DEBUG)
				#define _GRIDEXAUTOLIBNAME "ogex201aud.lib"
			#elif !defined(_OGEXDLL) &&  defined(_AFXDLL) && !defined(_DEBUG)
				#define _GRIDEXAUTOLIBNAME "ogex201au.lib"
			#elif  defined(_OGEXDLL) &&  defined(_AFXDLL) &&  defined(_DEBUG)
				//#define _RWUXTHEMEDLL
				#if defined _MANAGED
					#define _GRIDEXAUTOLIBNAME "ogex201asudm.lib"
				#else
					#define _GRIDEXAUTOLIBNAME "ogex201asud.lib"
				#endif
				
			#elif  defined(_OGEXDLL) &&  defined(_AFXDLL) && !defined(_DEBUG)
				//#define _RWUXTHEMEDLL
				#if defined _MANAGED
					#define _GRIDEXAUTOLIBNAME "ogex201asum.lib"
				#else
					#define _GRIDEXAUTOLIBNAME "ogex201asu.lib"
				#endif
				
			#elif  defined(_OGEXDLL) && !defined(_AFXDLL)
				#error One of Stingray Studio DLL defines is specified but _AFXDLL is not. Stingray Studio DLLs cannot be used with static MFC libraries.
			#endif
		#endif // UNICODE
	#endif // MSC_VER >= 1400
#endif // _OGEX_EXPORT_IMPL

#ifdef _GRIDEXAUTOLIBNAME	
	#pragma comment(lib, _GRIDEXAUTOLIBNAME)
	#pragma message( "Automatically linking with " _GRIDEXAUTOLIBNAME)
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
#include "afxcontrolbars.h"
#include "Grid\gxall.h"
#include "GridEx\ColorButton\GXColorButton.h"
#include "GridEx\ToolTips\gxttnex.h"
#include "GridEx\PopUpMenuEdit\PopUpMenuEdit.h"
#include "GridEx\ExcelHeaders\GXHeaderExcel.h"
#include "GridEx\ExcelSelection\GXGridCoreEx.h"
#include "GridEx\ToolTips\GXGridToolTipsEx.h"

// Resource Includes.
#include "GridEx\Res\OGResEx.h"

using namespace ogex;

#endif // __GRIDEX__H__
