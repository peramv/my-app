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
#if !defined __FOUNDATIONEX__H__
#define __FOUNDATIONEX__H__

#if _MFC_VER < 0x900
#error Microsoft Visual Studio 2008 SP1, including MFC 9 Feature Pack, or higher is required.
#endif // _MSC_VER

//-----------------------------------------------//
// Library linkage:                              //
// Specify linkage to the correct library name   //
// based on project settings.                    //
//-----------------------------------------------//
#ifndef _SFLEX_EXPORT_IMPL
	#if	_MSC_VER > 1400 //VC9 and higher
		#ifndef _UNICODE
			#if   !defined(_SFLEXDLL) && !defined(_AFXDLL) &&  defined(_DEBUG)
				#define _FOUNDATIONEXAUTOLIBNAME "sflex210d.lib"
			#elif !defined(_SFLEXDLL) && !defined(_AFXDLL) && !defined(_DEBUG)
				#define _FOUNDATIONEXAUTOLIBNAME "sflex210.lib"
			#elif !defined(_SFLEXDLL) &&  defined(_AFXDLL) &&  defined(_DEBUG)
				#define _FOUNDATIONEXAUTOLIBNAME "sflex210ad.lib"
			#elif !defined(_SFLEXDLL) &&  defined(_AFXDLL) && !defined(_DEBUG)
				#define _FOUNDATIONEXAUTOLIBNAME "sflex210a.lib"
			#elif  defined(_SFLEXDLL) &&  defined(_AFXDLL) &&  defined(_DEBUG)
				//#define _RWUXTHEMEDLL
				//#if defined _MANAGED
				//	#define _FOUNDATIONEXAUTOLIBNAME "sflex210asdm.lib"
				//#else
					#define _FOUNDATIONEXAUTOLIBNAME "sflex210asd.lib"
				//#endif
			#elif  defined(_SFLEXDLL) &&  defined(_AFXDLL) && !defined(_DEBUG)
				//#define _RWUXTHEMEDLL
				//#if defined _MANAGED
				//	#define _FOUNDATIONEXAUTOLIBNAME "sflex210asm.lib"
				//#else
					#define _FOUNDATIONEXAUTOLIBNAME "sflex210as.lib"
				//#endif
				
			#elif  defined(_SFLEXDLL) && !defined(_AFXDLL)
				#error One of Stingray Studio DLL defines is specified but _AFXDLL is not. Stingray Studio DLLs cannot be used with static MFC libraries.
			#endif
		#else
			#if   !defined(_SFLEXDLL) && !defined(_AFXDLL) &&  defined(_DEBUG)
				#define _FOUNDATIONEXAUTOLIBNAME "sflex210ud.lib"
			#elif !defined(_SFLEXDLL) && !defined(_AFXDLL) && !defined(_DEBUG)
				#define _FOUNDATIONEXAUTOLIBNAME "sflex210u.lib"
			#elif !defined(_SFLEXDLL) &&  defined(_AFXDLL) &&  defined(_DEBUG)
				#define _FOUNDATIONEXAUTOLIBNAME "sflex210aud.lib"
			#elif !defined(_SFLEXDLL) &&  defined(_AFXDLL) && !defined(_DEBUG)
				#define _FOUNDATIONEXAUTOLIBNAME "sflex210au.lib"
			#elif  defined(_SFLEXDLL) &&  defined(_AFXDLL) &&  defined(_DEBUG)
				//#define _RWUXTHEMEDLL
				//#if defined _MANAGED
				//	#define _FOUNDATIONEXAUTOLIBNAME "sflex210asudm.lib"
				//#else
					#define _FOUNDATIONEXAUTOLIBNAME "sflex210asud.lib"
				//#endif
				
			#elif  defined(_SFLEXDLL) &&  defined(_AFXDLL) && !defined(_DEBUG)
				//#define _RWUXTHEMEDLL
				//#if defined _MANAGED
				//	#define _FOUNDATIONEXAUTOLIBNAME "sflex210asum.lib"
				//#else
					#define _FOUNDATIONEXAUTOLIBNAME "sflex210asu.lib"
				//#endif
				
			#elif  defined(_SFLEXDLL) && !defined(_AFXDLL)
				#error One of Stingray Studio DLL defines is specified but _AFXDLL is not. Stingray Studio DLLs cannot be used with static MFC libraries.
			#endif
		#endif // UNICODE
	#endif // MSC_VER >= 1400
#endif // _SFLEX_EXPORT_IMPL

#ifdef _FOUNDATIONEXAUTOLIBNAME	
	#pragma comment(lib, _FOUNDATIONEXAUTOLIBNAME)
	#pragma message( "Automatically linking with " _FOUNDATIONEXAUTOLIBNAME)
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
// Application Includes.
#include "FoundationEx\Application\SflAppStyleEx.h"
#include "FoundationEx\Application\SflWinAppEx.h"
// Dialog Includes.
#include "FoundationEx\Dialog\SflDialogEx.h"
#include "FoundationEx\Dialog\SflPaneDialogEx.h"
// Docking Includes.
#include "FoundationEx\Docking\SflDockableCtrlPaneEx.h"
#include "FoundationEx\Docking\SflDockablePaneEx.h"
#include "FoundationEx\Docking\SflDockableTabPaneEx.h"
// Frame Includes.
#include "FoundationEx\Frame\SflFrameWndEx.h"
#include "FoundationEx\Frame\SflMDIFrameWndEx.h"
#include "FoundationEx\Frame\SflMDIChildWndEx.h"
#include "FoundationEx\Frame\SflFDIFrameWndEx.h"
#include "FoundationEx\Frame\SflFDIChildWndEx.h"
#include "FoundationEx\Frame\SflTopLevelFrameEx.h"
// Utility Includes.
#include "FoundationEx\Utils\SflCache.h"
// Manager Includes.
#include "FoundationEx\Manager\SflMultiViewMgr.h"
#include "FoundationEx\Manager\SflTaskbarMgr.h"
#include "FoundationEx\Manager\SflVisualMgr.h"
// Resource Includes.
#include "FoundationEx\Res\SflResEx.h"
// User Interface Includes.
#include "FoundationEx\UI\SflFluentUI.h"
#include "FoundationEx\UI\SflMenuBarEx.h"
#include "FoundationEx\UI\SflStandardUI.h"
#include "FoundationEx\UI\SflStatusBarEx.h"
#include "FoundationEx\UI\SflToolBarEx.h"
#include "FoundationEx\UI\SflChildToolBarEx.h"
#include "FoundationEx\UI\SflCaptionBarEx.h"
#include "FoundationEx\UI\SflBaseElementFactory.h"
#include "FoundationEx\UI\SflRibbonButtonsGroupEx.h"
#include "FoundationEx\UI\SflRibbonColorButtonEx.h"
#include "FoundationEx\UI\SflRibbonEditEx.h"
#include "FoundationEx\UI\SflRibbonFontComboBoxEx.h"
#include "FoundationEx\UI\SflRibbonGalleryEx.h"
#include "FoundationEx\UI\SflRibbonSliderEx.h"
using namespace sflex;

#endif // __FOUNDATIONEX__H__
