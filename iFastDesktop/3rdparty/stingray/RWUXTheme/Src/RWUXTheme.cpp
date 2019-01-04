///////////////////////////////////////////////////////////////////////////////
// RWUXTheme.cpp
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

#include "stdafx.h"

// Function poniter prototypes
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//uxtheme.dll
typedef HTHEME  (__stdcall *tPtrOpenThemeData)(HWND hwnd, LPCWSTR pszClassList);
typedef HRESULT (__stdcall *tPtrCloseThemeData)(HTHEME hTheme);
typedef HRESULT (__stdcall *tPtrDrawThemeBackground)(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, const RECT *pRect, const RECT *pClipRect);
typedef HRESULT (__stdcall *tPtrDrawThemeText)(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, LPCWSTR pszText, int iCharCount, DWORD dwTextFlags, DWORD dwTextFlags2, const RECT *pRect);
typedef HRESULT (__stdcall *tPtrGetThemeBackgroundContentRect)(HTHEME hTheme, HDC hdc, int iPartId, int iStateId,  const RECT *pBoundingRect, RECT *pContentRect);
typedef HRESULT (__stdcall *tPtrGetThemeBackgroundExtent)(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, const RECT *pContentRect, RECT *pExtentRect);
typedef HRESULT (__stdcall *tPtrGetThemePartSize)(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, RECT *prc, enum THEMESIZE eSize, OUT SIZE *psz);
typedef HRESULT (__stdcall *tPtrGetThemeTextExtent)(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, LPCWSTR pszText, int iCharCount, DWORD dwTextFlags, const RECT *pBoundingRect, RECT *pExtentRect);
typedef HRESULT (__stdcall *tPtrGetThemeTextMetrics)(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, TEXTMETRIC* ptm);
typedef HRESULT (__stdcall *tPtrGetThemeBackgroundRegion)(HTHEME hTheme, HDC hdc,  int iPartId, int iStateId, const RECT *pRect, HRGN *pRegion);
typedef HRESULT (__stdcall *tPtrHitTestThemeBackground)(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, DWORD dwOptions, const RECT *pRect, HRGN hrgn, POINT ptTest, WORD *pwHitTestCode);
typedef HRESULT (__stdcall *tPtrDrawThemeEdge)(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, const RECT *pDestRect, UINT uEdge, UINT uFlags, RECT *pContentRect);
typedef HRESULT (__stdcall *tPtrDrawThemeIcon)(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, const RECT *pRect, HIMAGELIST himl, int iImageIndex);
typedef BOOL	(__stdcall *tPtrIsThemePartDefined)(HTHEME hTheme, int iPartId, int iStateId);
typedef BOOL	(__stdcall *tPtrIsThemeBackgroundPartiallyTransparent)(HTHEME hTheme, int iPartId, int iStateId);
typedef HRESULT (__stdcall *tPtrGetThemeColor)(HTHEME hTheme, int iPartId, int iStateId, int iPropId, COLORREF *pColor);
typedef HRESULT (__stdcall *tPtrGetThemeMetric)(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, int iPropId, int *piVal);
typedef HRESULT (__stdcall *tPtrGetThemeString)(HTHEME hTheme, int iPartId, int iStateId, int iPropId, LPWSTR pszBuff, int cchMaxBuffChars);
typedef HRESULT (__stdcall *tPtrGetThemeBool)(HTHEME hTheme, int iPartId, int iStateId, int iPropId, BOOL *pfVal);
typedef HRESULT (__stdcall *tPtrGetThemeInt)(HTHEME hTheme, int iPartId, int iStateId, int iPropId, int *piVal);
typedef HRESULT (__stdcall *tPtrGetThemeEnumValue)(HTHEME hTheme, int iPartId, int iStateId, int iPropId, int *piVal);
typedef HRESULT (__stdcall *tPtrGetThemePosition)(HTHEME hTheme, int iPartId, int iStateId, int iPropId, POINT *pPoint);
typedef HRESULT (__stdcall *tPtrGetThemeFont)(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, int iPropId, LOGFONT *pFont);
typedef HRESULT (__stdcall *tPtrGetThemeRect)(HTHEME hTheme, int iPartId, int iStateId, int iPropId, RECT *pRect);
typedef HRESULT (__stdcall *tPtrGetThemeMargins)(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, int iPropId, RECT *prc, MARGINS *pMargins);
typedef HRESULT (__stdcall *tPtrGetThemeIntList)(HTHEME hTheme, int iPartId, int iStateId, int iPropId, INTLIST *pIntList);
typedef HRESULT (__stdcall *tPtrGetThemePropertyOrigin)(HTHEME hTheme, int iPartId, int iStateId, int iPropId, enum PROPERTYORIGIN *pOrigin);
typedef HRESULT (__stdcall *tPtrSetWindowTheme)(HWND hwnd, LPCWSTR pszSubAppName, LPCWSTR pszSubIdList);
typedef HRESULT (__stdcall *tPtrGetThemeFilename)(HTHEME hTheme, int iPartId, int iStateId, int iPropId, LPWSTR pszThemeFileName, int cchMaxBuffChars);
typedef COLORREF (__stdcall *tPtrGetThemeSysColor)(HTHEME hTheme, int iColorId);
typedef HBRUSH	(__stdcall *tPtrGetThemeSysColorBrush)(HTHEME hTheme, int iColorId);
typedef BOOL	(__stdcall *tPtrGetThemeSysBool)(HTHEME hTheme, int iBoolId);
typedef int		(__stdcall *tPtrGetThemeSysSize)(HTHEME hTheme, int iSizeId);
typedef HRESULT (__stdcall *tPtrGetThemeSysFont)(HTHEME hTheme, int iFontId, LOGFONT *plf);
typedef HRESULT (__stdcall *tPtrGetThemeSysString)(HTHEME hTheme, int iStringId, LPWSTR pszStringBuff, int cchMaxStringChars);
typedef HRESULT (__stdcall *tPtrGetThemeSysInt)(HTHEME hTheme, int iIntId, int *piValue);
typedef BOOL	(__stdcall *tPtrIsThemeActive)();
typedef BOOL	(__stdcall *tPtrIsAppThemed)();
typedef HTHEME	(__stdcall *tPtrGetWindowTheme)(HWND hwnd);
typedef HRESULT (__stdcall *tPtrEnableThemeDialogTexture)(HWND hwnd, DWORD dwFlags);
typedef BOOL	(__stdcall *tPtrIsThemeDialogTextureEnabled)(HWND hwnd);
typedef DWORD	(__stdcall *tPtrGetThemeAppProperties)();
typedef void	(__stdcall *tPtrSetThemeAppProperties)(DWORD dwFlags);
typedef HRESULT (__stdcall *tPtrGetCurrentThemeName)( LPWSTR pszThemeFileName, int cchMaxNameChars, LPWSTR pszColorBuff, int cchMaxColorChars, LPWSTR pszSizeBuff, int cchMaxSizeChars);
typedef HRESULT (__stdcall *tPtrGetThemeDocumentationProperty)(LPCWSTR pszThemeName, LPCWSTR pszPropertyName, LPWSTR pszValueBuff, int cchMaxValChars);
typedef HRESULT (__stdcall *tPtrDrawThemeParentBackground)(HWND hwnd, HDC hdc, RECT* prc);
typedef HRESULT (__stdcall *tPtrEnableTheming)(BOOL fEnable);

// user32.dll
typedef BOOL (__stdcall *tPtrTrackMouseEvent)( LPTRACKMOUSEEVENT lpEventTrack );

// Flag to determine if XP Theme Drawing is allowed
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL gXPThemeDrawingEnabled = TRUE;

// Module handle to Loaded libraries
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
HMODULE	gUXTHEME_DLLmdl = NULL; 
HMODULE gUSER32_DLLmdl  = NULL;
HMODULE gCOMCTRL32_DLLmdl = NULL;

// Function ponters to functions in uxtheme.dll
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
tPtrOpenThemeData							PtrOpenThemeData = NULL;
tPtrCloseThemeData							PtrCloseThemeData = NULL;
tPtrDrawThemeBackground						PtrDrawThemeBackground = NULL;
tPtrDrawThemeText							PtrDrawThemeText = NULL;
tPtrGetThemeBackgroundContentRect			PtrGetThemeBackgroundContentRect = NULL;
tPtrGetThemeBackgroundExtent				PtrGetThemeBackgroundExtent = NULL;
tPtrGetThemePartSize						PtrGetThemePartSize = NULL;
tPtrGetThemeTextExtent						PtrGetThemeTextExtent = NULL;
tPtrGetThemeTextMetrics						PtrGetThemeTextMetrics = NULL;
tPtrGetThemeBackgroundRegion				PtrGetThemeBackgroundRegion = NULL;
tPtrHitTestThemeBackground					PtrHitTestThemeBackground = NULL;
tPtrDrawThemeEdge							PtrDrawThemeEdge = NULL;
tPtrDrawThemeIcon							PtrDrawThemeIcon = NULL;
tPtrIsThemePartDefined						PtrIsThemePartDefined = NULL;
tPtrIsThemeBackgroundPartiallyTransparent	PtrIsThemeBackgroundPartiallyTransparent = NULL;
tPtrGetThemeColor							PtrGetThemeColor = NULL;
tPtrGetThemeMetric							PtrGetThemeMetric = NULL;
tPtrGetThemeString							PtrGetThemeString = NULL;
tPtrGetThemeBool							PtrGetThemeBool = NULL;
tPtrGetThemeInt								PtrGetThemeInt = NULL;
tPtrGetThemeEnumValue						PtrGetThemeEnumValue = NULL;
tPtrGetThemePosition						PtrGetThemePosition = NULL;
tPtrGetThemeFont							PtrGetThemeFont = NULL;
tPtrGetThemeRect							PtrGetThemeRect = NULL;
tPtrGetThemeMargins							PtrGetThemeMargins = NULL;
tPtrGetThemeIntList							PtrGetThemeIntList = NULL;
tPtrGetThemePropertyOrigin					PtrGetThemePropertyOrigin = NULL;
tPtrSetWindowTheme							PtrSetWindowTheme = NULL;
tPtrGetThemeFilename						PtrGetThemeFilename = NULL;
tPtrGetThemeSysColor						PtrGetThemeSysColor = NULL;
tPtrGetThemeSysColorBrush					PtrGetThemeSysColorBrush = NULL;
tPtrGetThemeSysBool							PtrGetThemeSysBool = NULL;
tPtrGetThemeSysSize							PtrGetThemeSysSize = NULL;
tPtrGetThemeSysFont							PtrGetThemeSysFont = NULL;
tPtrGetThemeSysString						PtrGetThemeSysString = NULL;
tPtrGetThemeSysInt							PtrGetThemeSysInt = NULL;
tPtrIsThemeActive							PtrIsThemeActive = NULL;
tPtrIsAppThemed								PtrIsAppThemed = NULL;
tPtrGetWindowTheme							PtrGetWindowTheme = NULL;
tPtrEnableThemeDialogTexture				PtrEnableThemeDialogTexture = NULL;
tPtrIsThemeDialogTextureEnabled				PtrIsThemeDialogTextureEnabled = NULL;
tPtrGetThemeAppProperties					PtrGetThemeAppProperties = NULL;
tPtrSetThemeAppProperties					PtrSetThemeAppProperties = NULL;
tPtrGetCurrentThemeName						PtrGetCurrentThemeName = NULL;
tPtrGetThemeDocumentationProperty			PtrGetThemeDocumentationProperty = NULL;
tPtrDrawThemeParentBackground				PtrDrawThemeParentBackground = NULL;
tPtrEnableTheming							PtrEnableTheming = NULL;


//Function pointers to functions in USER32
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
tPtrTrackMouseEvent PtrTrackMouseEvent = NULL;

// Structure to map function name to function ptr
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
typedef struct tPtrNamePair
{
	void**	m_FuncPtr;
	LPCSTR	m_FuncName;
} SPtrNamePair;

// Current amount of functions in UXTheme.dll
// We will need to extend our dll when new functions
// will be added
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define UXTHEMEFUNCNUM 47 

// Mapping between fnk pointer and fnk name
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SPtrNamePair gNamePtrMapUXTHEMEDLL[UXTHEMEFUNCNUM] = {
	{ (void**)&PtrOpenThemeData,						"OpenThemeData" },
	{ (void**)&PtrCloseThemeData,						"CloseThemeData" },
	{ (void**)&PtrDrawThemeBackground,					"DrawThemeBackground" },
	{ (void**)&PtrDrawThemeText,						"DrawThemeText" },
	{ (void**)&PtrGetThemeBackgroundContentRect,		"GetThemeBackgroundContentRect" },
	{ (void**)&PtrGetThemeBackgroundExtent,				"GetThemeBackgroundExtent" },
	{ (void**)&PtrGetThemePartSize,						"GetThemePartSize" },
	{ (void**)&PtrGetThemeTextExtent,					"GetThemeTextExtent" },
	{ (void**)&PtrGetThemeTextMetrics,					"GetThemeTextMetrics" },
	{ (void**)&PtrGetThemeBackgroundRegion,				"GetThemeBackgroundRegion" },
	{ (void**)&PtrHitTestThemeBackground,				"HitTestThemeBackground" },
	{ (void**)&PtrDrawThemeEdge,						"DrawThemeEdge" },
	{ (void**)&PtrDrawThemeIcon,						"DrawThemeIcon" },
	{ (void**)&PtrIsThemePartDefined,					"IsThemePartDefined" },
	{ (void**)&PtrIsThemeBackgroundPartiallyTransparent, "IsThemeBackgroundPartiallyTransparent" },
	{ (void**)&PtrGetThemeColor,						"GetThemeColor" },
	{ (void**)&PtrGetThemeMetric,						"GetThemeMetric" },
	{ (void**)&PtrGetThemeString,						"GetThemeString" },
	{ (void**)&PtrGetThemeBool,							"GetThemeBool" },
	{ (void**)&PtrGetThemeInt,							"GetThemeInt" },
	{ (void**)&PtrGetThemeEnumValue,					"GetThemeEnumValue" },
	{ (void**)&PtrGetThemePosition,						"GetThemePosition" },
	{ (void**)&PtrGetThemeFont,							"GetThemeFont" },
	{ (void**)&PtrGetThemeRect,							"GetThemeRect" },
	{ (void**)&PtrGetThemeMargins,						"GetThemeMargins" },
	{ (void**)&PtrGetThemeIntList,						"GetThemeIntList" },
	{ (void**)&PtrGetThemePropertyOrigin,				"GetThemePropertyOrigin" },
	{ (void**)&PtrSetWindowTheme,						"SetWindowTheme" },
	{ (void**)&PtrGetThemeFilename,						"GetThemeFilename" },
	{ (void**)&PtrGetThemeSysColor,						"GetThemeSysColor" },
	{ (void**)&PtrGetThemeSysColorBrush,				"GetThemeSysColorBrush" },
	{ (void**)&PtrGetThemeSysBool,						"GetThemeSysBool" },
	{ (void**)&PtrGetThemeSysSize,						"GetThemeSysSize" },
	{ (void**)&PtrGetThemeSysFont,						"GetThemeSysFont" },
	{ (void**)&PtrGetThemeSysString,					"GetThemeSysString" },
	{ (void**)&PtrGetThemeSysInt,						"GetThemeSysInt" },
	{ (void**)&PtrIsThemeActive,						"IsThemeActive" },
	{ (void**)&PtrIsAppThemed,							"IsAppThemed" },
	{ (void**)&PtrGetWindowTheme,						"GetWindowTheme" },
	{ (void**)&PtrEnableThemeDialogTexture,				"EnableThemeDialogTexture" },
	{ (void**)&PtrIsThemeDialogTextureEnabled,			"IsThemeDialogTextureEnabled" },
	{ (void**)&PtrGetThemeAppProperties,				"GetThemeAppProperties" },
	{ (void**)&PtrSetThemeAppProperties,				"SetThemeAppProperties" },
	{ (void**)&PtrGetCurrentThemeName,					"GetCurrentThemeName" },
	{ (void**)&PtrGetThemeDocumentationProperty,		"GetThemeDocumentationProperty" },
	{ (void**)&PtrDrawThemeParentBackground,			"DrawThemeParentBackground" },
	{ (void**)&PtrEnableTheming,						"EnableTheming" } };

// Current amount of functions in MSImg32.dll
// We will need to extend our dll when new functions
// will be added
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define USER32FUNCNUM 1 

// Mapping between fnk pointer and fnk name
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
SPtrNamePair gNamePtrMapUSER32DLL[USER32FUNCNUM] = {
	{ (void**)&PtrTrackMouseEvent, "TrackMouseEvent" } };


// Function proxies
// ~~~~~~~~~~~~~~~~

// QA: 31959

// Check for common controls, ComCtrl32.dll
#define RW_COMCTRL32_LOADED() (gCOMCTRL32_DLLmdl || RWInitInternalVars())
// Check for UXTheme.dll
#define RW_UXTHEME_LOADED() (gUXTHEME_DLLmdl || RWInitUXThemeFunctionPtrs())

// Note: Operating systems less than Windows XP will not have a UXTheme.dll to load. 
#if NTDDI_VERSION < NTDDI_WINXP
	#define RW_MSLIBRARIES_LOADED()( RW_COMCTRL32_LOADED() )

#else
	#define RW_MSLIBRARIES_LOADED()( RW_COMCTRL32_LOADED() && RW_UXTHEME_LOADED() )

#endif

// Loads UXTheme.dll and maps internal map to function in UXTheme.dll. Windows XP and greater.
// Commented UXTHEMEFUNCNUM and USER32FUNCNUM to remove warning C4127 when compiled with /W4
BOOL RWInitUXThemeFunctionPtrs()
{
	// QA 32265
	static BOOL ret = TRUE;

	// Return if theme DLL loading has already failed once.
	// This prevents recursive calls on theme-less systems, i.e. Windows < WinXP [Win2K or below]
	if(ret == FALSE)
	{
		return FALSE;
	}
	
	// Check if theme DLL is already loaded
	// and if yes than ptrs should be initialized already
	if( (gUXTHEME_DLLmdl/* || UXTHEMEFUNCNUM == 0*/) && (gUSER32_DLLmdl/* || USER32FUNCNUM == 0 */) )
		return TRUE;

	//BOOL ret = TRUE; // QA 32265

	InitCommonControls();

	//	if( UXTHEMEFUNCNUM != 0 )
	//	{
	gUXTHEME_DLLmdl = ::LoadLibrary(_T("UXTHEME.DLL"));

	if( gUXTHEME_DLLmdl == NULL ) //Didn't succeeded loading theme library - not XP system
	{
		ret = FALSE;
	}
	else
		for( int i = 0; i < UXTHEMEFUNCNUM; i++ )
		{
			(*gNamePtrMapUXTHEMEDLL[i].m_FuncPtr) = (void*)::GetProcAddress(gUXTHEME_DLLmdl, gNamePtrMapUXTHEMEDLL[i].m_FuncName );
		}
		//	}

		//	if( USER32FUNCNUM != 0 )
		//	{
		gUSER32_DLLmdl = ::LoadLibrary(_T("USER32.DLL"));

		if( gUSER32_DLLmdl == NULL ) //NT or 95 with Themes????? or maybe just USER32.dll missing???
		{
			ret = FALSE;
		}
		else
		{
			for( int i = 0; i < USER32FUNCNUM; i++ )
			{
				(*gNamePtrMapUSER32DLL[i].m_FuncPtr) = (void*)::GetProcAddress(gUSER32_DLLmdl, gNamePtrMapUSER32DLL[i].m_FuncName );
			}
		}
		//}

		RWResetColors();
		HWND  hWnd = ::GetDesktopWindow();
		if(hWnd)
		{
			RWResetO2K3Colors(hWnd);
		}

		//return true;
		return ret;
}

//Performs cleanup
BOOL RWDeInitUXThemeFunctionPtrs()
{
	if( gUXTHEME_DLLmdl == NULL && gUSER32_DLLmdl == NULL && gCOMCTRL32_DLLmdl == NULL)
		return TRUE;

	int i;

	for( i = 0; i < UXTHEMEFUNCNUM; i++ )
	{
		(*gNamePtrMapUXTHEMEDLL[i].m_FuncPtr) = NULL;
	}

	for( i = 0; i < USER32FUNCNUM; i++ )
	{
		(*gNamePtrMapUSER32DLL[i].m_FuncPtr) = NULL;
	}

	if( gUXTHEME_DLLmdl )
	{
		::FreeLibrary( gUXTHEME_DLLmdl );
		gUXTHEME_DLLmdl = NULL;
	}

	if( gUSER32_DLLmdl )
	{
		::FreeLibrary( gUSER32_DLLmdl );
		gUSER32_DLLmdl = NULL;
	}

	if( gCOMCTRL32_DLLmdl )
	{
		::FreeLibrary( gCOMCTRL32_DLLmdl );
		gCOMCTRL32_DLLmdl = NULL;
	}

	return TRUE;
}

BOOL RWInitInternalVars()
{
	if(gCOMCTRL32_DLLmdl)
		return TRUE;

	DLLVERSIONINFO	dvi;

	memset( &dvi, 0x00, sizeof( dvi ) );
	dvi.cbSize = sizeof( dvi );

	gCOMCTRL32_DLLmdl= ::LoadLibrary( _T("COMCTL32.DLL") );
	LONG COMCTL32Ver = MAKELONG(0,5);

	if( gCOMCTRL32_DLLmdl )
	{
		DLLGETVERSIONPROC dgvProc = (DLLGETVERSIONPROC)::GetProcAddress( gCOMCTRL32_DLLmdl, "DllGetVersion" );

		if( dgvProc )
		{
			HRESULT hr = dgvProc( &dvi );

			if( SUCCEEDED( hr ) )
			{
				COMCTL32Ver = MAKELONG(dvi.dwMinorVersion,dvi.dwMajorVersion);
			}
		}
	}else
	{
		return FALSE;
	}

	//::FreeLibrary( gCOMCTRL32_DLLmdl );

	gXPThemeDrawingEnabled = COMCTL32Ver >= MAKELONG(0,6);
	return TRUE;
}

RWTHEMEAPI(HTHEME) RWOpenThemeData(HWND hwnd, LPCWSTR pszClassList)
{
	if(RW_MSLIBRARIES_LOADED() && PtrOpenThemeData)
		return PtrOpenThemeData( hwnd, pszClassList );

	return NULL;
}

RWTHEMEAPI(HRESULT) RWCloseThemeData(HTHEME hTheme)
{
	if(RW_MSLIBRARIES_LOADED() && PtrCloseThemeData)
		return PtrCloseThemeData( hTheme );

	return E_FAIL; 
}

RWTHEMEAPI(HRESULT) RWDrawThemeBackground(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, const RECT *pRect, const RECT *pClipRect)
{
	if(RW_MSLIBRARIES_LOADED() && PtrDrawThemeBackground)
		return PtrDrawThemeBackground( hTheme, hdc, iPartId, iStateId, pRect, pClipRect );

	return E_FAIL; 
}

RWTHEMEAPI(HRESULT) RWDrawThemeText(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, LPCWSTR pszText, int iCharCount, DWORD dwTextFlags, DWORD dwTextFlags2, const RECT *pRect)
{
	if(RW_MSLIBRARIES_LOADED() && PtrDrawThemeText)
		return PtrDrawThemeText( hTheme, hdc, iPartId, iStateId, pszText, iCharCount, dwTextFlags, dwTextFlags2, pRect );

	return E_FAIL; 
}

RWTHEMEAPI(HRESULT) RWGetThemeBackgroundContentRect(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, const RECT *pBoundingRect, RECT *pContentRect)
{
	if(RW_MSLIBRARIES_LOADED() && PtrGetThemeBackgroundContentRect)
		return PtrGetThemeBackgroundContentRect( hTheme, hdc, iPartId, iStateId, pBoundingRect, pContentRect );

	return E_FAIL; 
}

RWTHEMEAPI(HRESULT) RWGetThemeBackgroundExtent(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, const RECT *pContentRect, RECT *pExtentRect)
{
	if(RW_MSLIBRARIES_LOADED() && PtrGetThemeBackgroundExtent)
		return PtrGetThemeBackgroundExtent( hTheme, hdc, iPartId, iStateId, pContentRect, pExtentRect );

	return E_FAIL; 
}

RWTHEMEAPI(HRESULT) RWGetThemePartSize(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, RECT *prc, enum THEMESIZE eSize, OUT SIZE *psz)
{
	if(RW_MSLIBRARIES_LOADED() && PtrGetThemePartSize)
		return PtrGetThemePartSize( hTheme, hdc, iPartId, iStateId, prc, eSize, psz );

	return E_FAIL; 
}

RWTHEMEAPI(HRESULT) RWGetThemeTextExtent(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, LPCWSTR pszText, int iCharCount, DWORD dwTextFlags, const RECT *pBoundingRect, RECT *pExtentRect)
{
	if(RW_MSLIBRARIES_LOADED() && PtrGetThemeTextExtent)
		return PtrGetThemeTextExtent( hTheme, hdc, iPartId, iStateId, pszText, iCharCount, dwTextFlags, pBoundingRect, pExtentRect );

	return E_FAIL; 
}

RWTHEMEAPI(HRESULT) RWGetThemeTextMetrics(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, TEXTMETRIC* ptm)
{
	if(RW_MSLIBRARIES_LOADED() && PtrGetThemeTextMetrics)
		return PtrGetThemeTextMetrics( hTheme, hdc, iPartId, iStateId, ptm );

	return E_FAIL; 
}

RWTHEMEAPI(HRESULT) RWGetThemeBackgroundRegion(HTHEME hTheme, HDC hdc,  int iPartId, int iStateId, const RECT *pRect, HRGN *pRegion)
{
	if(RW_MSLIBRARIES_LOADED() && PtrGetThemeBackgroundRegion)
		return PtrGetThemeBackgroundRegion( hTheme, hdc, iPartId, iStateId, pRect, pRegion );

	return E_FAIL; 
}

RWTHEMEAPI(HRESULT) RWHitTestThemeBackground(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, DWORD dwOptions, const RECT *pRect, HRGN hrgn, POINT ptTest, WORD *pwHitTestCode)
{
	if(RW_MSLIBRARIES_LOADED() && PtrHitTestThemeBackground)
		return PtrHitTestThemeBackground( hTheme, hdc, iPartId, iStateId, dwOptions, pRect, hrgn, ptTest, pwHitTestCode );

	return E_FAIL; 
}

RWTHEMEAPI(HRESULT) RWDrawThemeEdge(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, const RECT *pDestRect, UINT uEdge, UINT uFlags, RECT *pContentRect)
{
	if(RW_MSLIBRARIES_LOADED() && PtrDrawThemeEdge)
		return PtrDrawThemeEdge( hTheme, hdc, iPartId, iStateId, pDestRect, uEdge, uFlags, pContentRect );

	return E_FAIL; 
}

RWTHEMEAPI(HRESULT) RWDrawThemeIcon(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, const RECT *pRect, HIMAGELIST himl, int iImageIndex)
{
	if(RW_MSLIBRARIES_LOADED() && PtrDrawThemeIcon)
		return PtrDrawThemeIcon( hTheme, hdc, iPartId, iStateId, pRect, himl, iImageIndex );

	return E_FAIL; 
}

RWTHEMEAPI(BOOL) RWIsThemePartDefined(HTHEME hTheme, int iPartId, int iStateId)
{
	if(RW_MSLIBRARIES_LOADED() && PtrIsThemePartDefined)
		return PtrIsThemePartDefined( hTheme, iPartId, iStateId );

	return FALSE;
}

RWTHEMEAPI(BOOL) RWIsThemeBackgroundPartiallyTransparent(HTHEME hTheme, int iPartId, int iStateId)
{
	if(RW_MSLIBRARIES_LOADED() && PtrIsThemeBackgroundPartiallyTransparent )
		return PtrIsThemeBackgroundPartiallyTransparent( hTheme, iPartId, iStateId );

	return FALSE;
}

RWTHEMEAPI(HRESULT) RWGetThemeColor(HTHEME hTheme, int iPartId, int iStateId, int iPropId, COLORREF *pColor)
{
	if(RW_MSLIBRARIES_LOADED() && PtrGetThemeColor)
		return PtrGetThemeColor( hTheme, iPartId, iStateId, iPropId, pColor );

	return E_FAIL; 
}

RWTHEMEAPI(HRESULT) RWGetThemeMetric(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, int iPropId, int *piVal)
{
	if(RW_MSLIBRARIES_LOADED() && PtrGetThemeMetric)
		return PtrGetThemeMetric( hTheme, hdc, iPartId, iStateId, iPropId, piVal );

	return E_FAIL; 
}

RWTHEMEAPI(HRESULT) RWGetThemeString(HTHEME hTheme, int iPartId, int iStateId, int iPropId, LPWSTR pszBuff, int cchMaxBuffChars)
{
	if(RW_MSLIBRARIES_LOADED() && PtrGetThemeString )
		return PtrGetThemeString( hTheme, iPartId, iStateId, iPropId, pszBuff, cchMaxBuffChars );

	return E_FAIL; 
}

RWTHEMEAPI(HRESULT) RWGetThemeBool(HTHEME hTheme, int iPartId, int iStateId, int iPropId, BOOL *pfVal)
{
	if(RW_MSLIBRARIES_LOADED() && PtrGetThemeBool)
		return PtrGetThemeBool( hTheme, iPartId, iStateId, iPropId, pfVal );

	return E_FAIL; 
}

RWTHEMEAPI(HRESULT) RWGetThemeInt(HTHEME hTheme, int iPartId, int iStateId, int iPropId, int *piVal)
{
	if(RW_MSLIBRARIES_LOADED() && PtrGetThemeInt)
		return PtrGetThemeInt( hTheme, iPartId, iStateId, iPropId, piVal );

	return E_FAIL; 
}

RWTHEMEAPI(HRESULT) RWGetThemeEnumValue(HTHEME hTheme, int iPartId, int iStateId, int iPropId, int *piVal)
{
	if(RW_MSLIBRARIES_LOADED() && PtrGetThemeEnumValue)
		return PtrGetThemeEnumValue( hTheme, iPartId, iStateId, iPropId, piVal );

	return E_FAIL; 
}

RWTHEMEAPI(HRESULT) RWGetThemePosition(HTHEME hTheme, int iPartId, int iStateId, int iPropId, POINT *pPoint)
{
	if(RW_MSLIBRARIES_LOADED() && PtrGetThemePosition)
		return PtrGetThemePosition( hTheme, iPartId, iStateId, iPropId, pPoint );

	return E_FAIL; 
}

RWTHEMEAPI(HRESULT) RWGetThemeFont(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, int iPropId, LOGFONT *pFont)
{
	if(RW_MSLIBRARIES_LOADED() && PtrGetThemeFont)
		return PtrGetThemeFont( hTheme, hdc, iPartId, iStateId, iPropId, pFont );

	return E_FAIL; 
}

RWTHEMEAPI(HRESULT) RWGetThemeRect(HTHEME hTheme, int iPartId, int iStateId, int iPropId, RECT *pRect)
{
	if(RW_MSLIBRARIES_LOADED() && PtrGetThemeRect)
		return PtrGetThemeRect( hTheme, iPartId, iStateId, iPropId, pRect );

	return E_FAIL; 
}

RWTHEMEAPI(HRESULT) RWGetThemeMargins(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, int iPropId, RECT *prc, MARGINS *pMargins)
{
	if(RW_MSLIBRARIES_LOADED() && PtrGetThemeMargins)
		return PtrGetThemeMargins( hTheme, hdc, iPartId, iStateId, iPropId, prc, pMargins );

	return E_FAIL; 
}

RWTHEMEAPI(HRESULT) RWGetThemeIntList(HTHEME hTheme, int iPartId, int iStateId, int iPropId, INTLIST *pIntList)
{
	if(RW_MSLIBRARIES_LOADED() && PtrGetThemeIntList)
		return PtrGetThemeIntList( hTheme, iPartId, iStateId, iPropId, pIntList );

	return E_FAIL; 
}

RWTHEMEAPI(HRESULT) RWGetThemePropertyOrigin(HTHEME hTheme, int iPartId, int iStateId, int iPropId, enum PROPERTYORIGIN *pOrigin)
{
	if(RW_MSLIBRARIES_LOADED() && PtrGetThemePropertyOrigin)
		return PtrGetThemePropertyOrigin( hTheme, iPartId, iStateId, iPropId, pOrigin );

	return E_FAIL; 
}

RWTHEMEAPI(HRESULT) RWSetWindowTheme(HWND hwnd, LPCWSTR pszSubAppName, LPCWSTR pszSubIdList)
{
	if(RW_MSLIBRARIES_LOADED() && PtrSetWindowTheme )
		return PtrSetWindowTheme( hwnd, pszSubAppName, pszSubIdList );

	return E_FAIL; 
}

RWTHEMEAPI(HRESULT) RWGetThemeFilename(HTHEME hTheme, int iPartId, int iStateId, int iPropId, LPWSTR pszThemeFileName, int cchMaxBuffChars)
{
	if(RW_MSLIBRARIES_LOADED() && PtrGetThemeFilename)
		return PtrGetThemeFilename( hTheme, iPartId, iStateId, iPropId, pszThemeFileName, cchMaxBuffChars );

	return E_FAIL; 
}

RWTHEMEAPI(COLORREF) RWGetThemeSysColor(HTHEME hTheme, int iColorId)
{
	if(RW_MSLIBRARIES_LOADED() && PtrGetThemeSysColor)
		return PtrGetThemeSysColor( hTheme, iColorId );

	return RGB( 0x00, 0x00, 0x00 );
}

RWTHEMEAPI(HBRUSH) RWGetThemeSysColorBrush(HTHEME hTheme, int iColorId)
{
	if(RW_MSLIBRARIES_LOADED() && PtrGetThemeSysColorBrush)
		return PtrGetThemeSysColorBrush( hTheme, iColorId );

	return NULL;
}

RWTHEMEAPI(BOOL) RWGetThemeSysBool(HTHEME hTheme, int iBoolId)
{
	if(RW_MSLIBRARIES_LOADED() && PtrGetThemeSysBool)
		return PtrGetThemeSysBool( hTheme, iBoolId );

	return FALSE;
}

RWTHEMEAPI(int)	RWGetThemeSysSize(HTHEME hTheme, int iSizeId)
{
	if(RW_MSLIBRARIES_LOADED() && PtrGetThemeSysSize)
		return PtrGetThemeSysSize( hTheme, iSizeId );

	return -1;
}

RWTHEMEAPI(HRESULT) RWGetThemeSysFont(HTHEME hTheme, int iFontId, LOGFONT *plf)
{
	if(RW_MSLIBRARIES_LOADED() && PtrGetThemeSysFont)
		return PtrGetThemeSysFont( hTheme, iFontId, plf );

	return E_FAIL; 
}

RWTHEMEAPI(HRESULT) RWGetThemeSysString(HTHEME hTheme, int iStringId, LPWSTR pszStringBuff, int cchMaxStringChars)
{
	if(RW_MSLIBRARIES_LOADED() && PtrGetThemeSysString )
		return PtrGetThemeSysString( hTheme, iStringId, pszStringBuff, cchMaxStringChars );

	return E_FAIL; 
}

RWTHEMEAPI(HRESULT) RWGetThemeSysInt(HTHEME hTheme, int iIntId, int *piValue)
{
	if(RW_MSLIBRARIES_LOADED() && PtrGetThemeSysInt)
		return PtrGetThemeSysInt( hTheme, iIntId, piValue );

	return E_FAIL; 
}

RWTHEMEAPI(BOOL) RWIsThemeActive()
{
	if(RW_MSLIBRARIES_LOADED() && gXPThemeDrawingEnabled && PtrIsThemeActive)
		return PtrIsThemeActive();

	return FALSE;
}

RWTHEMEAPI(BOOL) RWIsAppThemed()
{
	if(RW_MSLIBRARIES_LOADED() && PtrIsAppThemed)
		return PtrIsAppThemed();

	return FALSE;
}

RWTHEMEAPI(HTHEME) RWGetWindowTheme(HWND hwnd)
{
	if(RW_MSLIBRARIES_LOADED() && PtrGetWindowTheme)
		return PtrGetWindowTheme( hwnd );

	return NULL;
}

RWTHEMEAPI(HRESULT) RWEnableThemeDialogTexture(HWND hwnd, DWORD dwFlags)
{
	if(RW_MSLIBRARIES_LOADED() && PtrEnableThemeDialogTexture)
		return PtrEnableThemeDialogTexture( hwnd, dwFlags );

	return E_FAIL; 
}

RWTHEMEAPI(BOOL) RWIsThemeDialogTextureEnabled(HWND hwnd)
{
	if(RW_MSLIBRARIES_LOADED() && PtrIsThemeDialogTextureEnabled)
		return PtrIsThemeDialogTextureEnabled( hwnd );

	return FALSE;
}

RWTHEMEAPI(DWORD) RWGetThemeAppProperties()
{
	if(RW_MSLIBRARIES_LOADED() && PtrGetThemeAppProperties )
		return PtrGetThemeAppProperties();

	return 0x00000000;
}

RWTHEMEAPI(void) RWSetThemeAppProperties(DWORD dwFlags)
{
	if(RW_MSLIBRARIES_LOADED() && PtrSetThemeAppProperties)
		PtrSetThemeAppProperties( dwFlags );
}

RWTHEMEAPI(HRESULT) RWGetCurrentThemeName( LPWSTR pszThemeFileName, int cchMaxNameChars, LPWSTR pszColorBuff, int cchMaxColorChars, LPWSTR pszSizeBuff, int cchMaxSizeChars)
{
	if(RW_MSLIBRARIES_LOADED() && PtrGetCurrentThemeName)
		return PtrGetCurrentThemeName( pszThemeFileName, cchMaxNameChars, pszColorBuff, cchMaxColorChars, pszSizeBuff, cchMaxSizeChars );

	return E_FAIL; 
}

RWTHEMEAPI(HRESULT) RWGetThemeDocumentationProperty(LPCWSTR pszThemeName, LPCWSTR pszPropertyName, LPWSTR pszValueBuff, int cchMaxValChars)
{
	if(RW_MSLIBRARIES_LOADED() && PtrGetThemeDocumentationProperty)
		return PtrGetThemeDocumentationProperty( pszThemeName, pszPropertyName, pszValueBuff, cchMaxValChars );

	return E_FAIL; 
}

RWTHEMEAPI(HRESULT) RWDrawThemeParentBackground(HWND hwnd, HDC hdc, RECT* prc)
{
	if(RW_MSLIBRARIES_LOADED() && PtrDrawThemeParentBackground)
		return PtrDrawThemeParentBackground( hwnd, hdc, prc );

	return E_FAIL; 
}

RWTHEMEAPI(HRESULT) RWEnableTheming(BOOL fEnable)
{
	if(RW_MSLIBRARIES_LOADED() && PtrEnableTheming)
		return PtrEnableTheming( fEnable );

	return E_FAIL; 
}

RWTHEMEAPI(BOOL) RWTrackMouseEvent( LPTRACKMOUSEEVENT lpEventTrack )
{
	if(RW_MSLIBRARIES_LOADED() && PtrTrackMouseEvent)
		return PtrTrackMouseEvent( lpEventTrack );

	return FALSE; 
}

RWTHEMEAPI(BOOL) RWEnableXPThemesDrawing( BOOL enable )
{
	BOOL oldVal = gXPThemeDrawingEnabled;

	gXPThemeDrawingEnabled = enable;
	
	return oldVal;
}

// QA: 32441
BOOL SEC_AUX_DATA::m_bUpdateSysColorsCalled = FALSE;

// Look and Feel
RWTHEMEVAR_API SEC_AUX_DATA secData;

RWTHEMEAPI(SEC_AUX_DATA)& RWGetSecData()
{
	// QA: 32441
	if(!secData.m_bUpdateSysColorsCalled)
	{
		secData.UpdateSysColors();
	}
	return secData;
}

// Initialization code
SEC_AUX_DATA::SEC_AUX_DATA()
{
	// Cache various target platform version information

#ifndef UNDER_CE
	DWORD dwVersion = ::GetVersion();
	bWin4 = (BYTE)dwVersion >= 4;
#else
	OSVERSIONINFO osInfo;
	osInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&osInfo);
	bWin4 = osInfo.dwMajorVersion >= 4;
#endif //UNDER_CE (WindowsCE)

	// Cached system values (updated in CWnd::OnSysColorChange)

	// QA: 31826 - Removing call to UpdateSysColors();

	// Standard cursors
	hcurHSplit = NULL;
	hcurVSplit = NULL;
	hCurCrossHairs = NULL;
#ifndef UNDER_CE
	hcurArrow = ::LoadCursor(NULL, IDC_ARROW);
	//ASSERT(hcurArrow != NULL);
#else
	hcurArrow = NULL;
#endif //UNDER_CE (WindowsCE)


	// cxBorder2 and cyBorder are 2x borders for Win4
	cxBorder2 = bWin4 ? CX_BORDER*2 : CX_BORDER;
	cyBorder2 = bWin4 ? CY_BORDER*2 : CY_BORDER;
}

// Termination code
SEC_AUX_DATA::~SEC_AUX_DATA()
{
}

void SEC_AUX_DATA::UpdateSysColors()
{
	RWResetColors();

	//----------------------------------------------//
	// Since we need to update colors from the      //
	// current theme we need to have a handle to    //
	// the main window so we can open theme data.   //
	//----------------------------------------------//

	// QA: 31720, Removing call to AfxGetmainWnd(),
	// checking for NULL.
	HWND  hWnd = ::GetDesktopWindow();
	if(hWnd)
	{
		RWResetO2K3Colors(hWnd);
	}

	clrBtnFace       = ::GetSysColor(COLOR_BTNFACE);
	clrBtnShadow     = ::GetSysColor(COLOR_BTNSHADOW);
	clrBtnHilite     = ::GetSysColor(COLOR_BTNHIGHLIGHT);
	clrWindowFrame   = ::GetSysColor(COLOR_WINDOWFRAME);
	clrText          = ::GetSysColor(COLOR_WINDOWTEXT);
	clrWindow        = ::GetSysColor(COLOR_WINDOW);
	clrHighlight     = ::GetSysColor(COLOR_HIGHLIGHT);
	clrHighlightText = ::GetSysColor(COLOR_HIGHLIGHTTEXT);
#ifdef WIN32
	clr3DLight       = ::GetSysColor(COLOR_3DLIGHT);
	clr3DDkShadow    = ::GetSysColor(COLOR_3DDKSHADOW);
#else
	clr3DLight       = ::GetSysColor(COLOR_BTNFACE);
	clr3DDkShadow    = ::GetSysColor(COLOR_WINDOWFRAME);
#endif
	// QA: 32441
	m_bUpdateSysColorsCalled = TRUE;
}

extern BOOL g_IsWindowsClassicStyleEnabled  = FALSE;
extern BOOL g_IsDotNetStyleEnabled			= FALSE;
extern BOOL g_IsOfc2003StyleEnabled			= FALSE;
extern BOOL g_IsVistaClassicStyleEnabled	= FALSE;
extern BOOL g_IsVistaAeroGlassStyleEnabled	= FALSE;

BOOL RWSetVisualStyle(eRWVisualStyle iStyle)
{
	// Reset all global flags.
	g_IsWindowsClassicStyleEnabled  = FALSE;
	g_IsDotNetStyleEnabled			= FALSE;
	g_IsOfc2003StyleEnabled			= FALSE;
	g_IsVistaClassicStyleEnabled	= FALSE;
	g_IsVistaAeroGlassStyleEnabled	= FALSE;
	BOOL bSuccess					= TRUE;

	switch(iStyle)
	{
	case RW_VISUALSTYLE_WINDOWSCLASSIC:
		g_IsWindowsClassicStyleEnabled = TRUE;
		break;

	case RW_VISUALSTYLE_DOTNET:
        // QA 32288
		//if(RWIsThemeActive() && RWIsAppThemed())
		//{
			g_IsDotNetStyleEnabled = TRUE;
		//}else
		//{
		//	bSuccess = FALSE;
		//	g_IsWindowsClassicStyleEnabled = TRUE;
		//}
		break;

	case RW_VISUALSTYLE_OFFICE2003:
		// QA 32288
		//if(RWIsThemeActive() && RWIsAppThemed())
		//{
			g_IsOfc2003StyleEnabled = TRUE;
		//}else
		//{
		//	bSuccess = FALSE;
		//	g_IsWindowsClassicStyleEnabled = TRUE;
		//}
		break;

	case RW_VISUALSTYLE_VISTACLASSIC:
		{	
			DWORD dwVersion = ::GetVersion();
			if(((BYTE)dwVersion >= 6) && RWIsThemeActive() && RWIsAppThemed()) // Windows Vista
			{
				g_IsVistaClassicStyleEnabled = TRUE;
			}else
			{
				bSuccess = FALSE;
				g_IsWindowsClassicStyleEnabled = TRUE;
			}
		}
		break;

	case RW_VISUALSTYLE_VISTAAEROGLASS:
		{
			DWORD dwVersion = ::GetVersion();
			if(((BYTE)dwVersion >= 6) && RWIsThemeActive() && RWIsAppThemed()) // Windows Vista
			{
				// NOTE: We are not yet supporting this.
				g_IsVistaAeroGlassStyleEnabled = bSuccess = FALSE;
				g_IsWindowsClassicStyleEnabled = TRUE;
			}else
			{
				bSuccess = FALSE;
				g_IsWindowsClassicStyleEnabled = TRUE;
			}
		}
		break;

	default:
		bSuccess = FALSE;
		g_IsWindowsClassicStyleEnabled = TRUE;
		break;
	}

	// Refresh.
	secData.UpdateSysColors();

	return bSuccess;
}

eRWVisualStyle RWGetVisualStyle()
{
	if(g_IsWindowsClassicStyleEnabled)
	{
		return RW_VISUALSTYLE_WINDOWSCLASSIC;
	}else if(g_IsDotNetStyleEnabled)
	{
		return RW_VISUALSTYLE_DOTNET;
	}else if(g_IsOfc2003StyleEnabled)
	{
		return RW_VISUALSTYLE_OFFICE2003;
	}else if(g_IsVistaClassicStyleEnabled)
	{
		return RW_VISUALSTYLE_VISTACLASSIC;
	}else if(g_IsVistaAeroGlassStyleEnabled)
	{
		return RW_VISUALSTYLE_VISTAAEROGLASS;
	}else
	{
		return RW_VISUALSTYLE_INVALID;
	}
}

BOOL RWIsDotNetStyleEnabled() 
{
	return g_IsDotNetStyleEnabled;
}

BOOL RWSetDotNetStyle( BOOL bEnable )
{
	BOOL	oldStyle = g_IsDotNetStyleEnabled;

	if(bEnable)
	{
		RWSetVisualStyle(RW_VISUALSTYLE_DOTNET);
	}else
	{
		RWSetVisualStyle(RW_VISUALSTYLE_INVALID);
	}

	return oldStyle;
}

BOOL RWIsVistaClassicStyleEnabled()
{
	return g_IsVistaClassicStyleEnabled;
}

BOOL RWSetVistaClassicStyle(BOOL bEnable)
{
	if(bEnable)
	{
		return RWSetVisualStyle(RW_VISUALSTYLE_VISTACLASSIC);
	}else
	{
		return RWSetVisualStyle(RW_VISUALSTYLE_INVALID);
	}
}

BOOL RWIsVistaAeroGlassStyleEnabled()
{
	return g_IsVistaAeroGlassStyleEnabled;
}

BOOL RWSetVistaAeroGlassStyle(BOOL bEnable)
{
	// NOTE: We are not yet supporting this style.
	if(bEnable)
	{
		return RWSetVistaClassicStyle(RW_VISUALSTYLE_VISTAAEROGLASS);
	}else
	{
		return RWSetVistaClassicStyle(RW_VISUALSTYLE_INVALID);
	}
}

BOOL RWIsOfc2003StyleEnabled()
{
	return g_IsOfc2003StyleEnabled;
}

BOOL RWSetOfc2003Style(BOOL bEnable)
{
	BOOL oldStyle = g_IsOfc2003StyleEnabled;

	if(bEnable)
	{
		RWSetVisualStyle(RW_VISUALSTYLE_OFFICE2003);
	}else
	{
		RWSetVisualStyle(RW_VISUALSTYLE_INVALID);
	}

	return oldStyle;
}

// SRSTUDIO-800
BOOL RWIsWindowsClassicStyleEnabled()
{
	return g_IsWindowsClassicStyleEnabled;
}

// SRSTUDIO-800
BOOL RWSetWindowsClassicStyle(BOOL bEnable)
{
	BOOL oldStyle = g_IsWindowsClassicStyleEnabled;
		
	if(bEnable)
	{
		RWSetVisualStyle(RW_VISUALSTYLE_WINDOWSCLASSIC);
	}else
	{
		RWSetVisualStyle(RW_VISUALSTYLE_INVALID);
	}

	return oldStyle;
}

HWND RWGetSafeHwnd()
{
	HWND hWnd = NULL;
#if defined(_MFC_VER)
	if(AfxGetMainWnd())
	{
		hWnd =  AfxGetMainWnd()->GetSafeHwnd();
	}else
	{
		hWnd =  ::GetDesktopWindow();
	}
#else
	hWnd = ::GetDesktopWindow();
#endif // __MFC_VER

	return hWnd;
}

///////////////////////////////////////////////////////////////////////////////
#ifdef _RWUXTHEMEDLL
BOOL APIENTRY DllMain( HANDLE /*hModule*/, DWORD  ul_reason_for_call, LPVOID /*lpReserved*/ )
{
	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH: 
			{
				// These functions have been moved to RW_MSLIBRARIES_LOADED()
				/*RWInitInternalVars(); 
				  RWInitUXThemeFunctionPtrs(); 
				  RWResetColors();
				*/ 
				//::OutputDebugString("RWUXTheme Process Attach.\n");
				return TRUE;
			}
		case DLL_THREAD_ATTACH: 
			//::OutputDebugString("RWUXTheme Thread Attach.\n");
			return TRUE;
		case DLL_THREAD_DETACH: 
			//::OutputDebugString("RWUXTheme Thread Detach.\n");
			return TRUE;
		case DLL_PROCESS_DETACH: 
			{
				// It is possible that this clean up routine will not get called
				// if the process is manually terminated. 

				//::OutputDebugString("RWUXTheme Process Detach.\n");
				RWDeInitUXThemeFunctionPtrs(); 
				return TRUE;
			}
		default:
			{
				//::OutputDebugString("RWUXTheme Default.\n");
				RWDeInitUXThemeFunctionPtrs(); 
				return TRUE;
			}
	}
}
#else //_RWUXTHEMEDLL

//--------------------------------------------------------------
// SRSTUDIO-1482 - Prevent application crash on start based on 
// static object race conditions. This code is not longer needed, 
// but is left for reference. 
/*class CRWUXThemeInitializer
{
public:
	CRWUXThemeInitializer() { RWInitInternalVars(); RWInitUXThemeFunctionPtrs(); RWResetColors(); }
	~CRWUXThemeInitializer() { RWDeInitUXThemeFunctionPtrs(); }
};

static CRWUXThemeInitializer	initObj;
*/
//--------------------------------------------------------------
#endif //_RWUXTHEMEDLL
