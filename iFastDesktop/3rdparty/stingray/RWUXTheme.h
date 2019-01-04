////////////////////////////////////////////////
// Copyright (c) 2002, 2003 Rogue Wave Software
// Theme funcitons proxy declarations
//
// This library is intended for internal use
// by Stingray Objective Studio and should not 
// be used separetely.

#ifndef __RWUXTHEME_H
#define __RWUXTHEME_H

#if _MSC_VER > 1000
   #pragma once
#endif

#ifndef _RWUXTHEMELIB
   #ifdef _SECDLL
      #define _RWOSDLL
   #else
      #ifdef _SFLDLL
         #define _RWOSDLL
      #else
         #ifdef _OBJCHART_DLL
            #define _RWOSDLL
         #else
            #ifdef _SECEDITDLL
               #define _RWOSDLL
            #else
               #ifdef _GXDLL
                  #define _RWOSDLL
               #else
                  #ifdef _OVDLL
                     #define _RWOSDLL
                  #endif
               #endif
            #endif
         #endif
      #endif
   #endif
#endif //_RWUXTHEMELIB

#undef _RWUXTHEMEAUTOLIBNAME

#ifndef RWTHEMEPROXYBUILD
   #if   _MSC_VER >= 1300 //VC7 and higher
      #ifndef _UNICODE
         #if   !defined(_RWOSDLL) && !defined(_AFXDLL) &&  defined(_DEBUG)
            #define _RWUXTHEMEAUTOLIBNAME "RWUXThemeD.lib"
         #elif !defined(_RWOSDLL) && !defined(_AFXDLL) && !defined(_DEBUG)
            #define _RWUXTHEMEAUTOLIBNAME "RWUXTheme.lib"
         #elif !defined(_RWOSDLL) &&  defined(_AFXDLL) &&  defined(_DEBUG)
            #define _RWUXTHEMEAUTOLIBNAME "RWUXThemeAD.lib"
         #elif !defined(_RWOSDLL) &&  defined(_AFXDLL) && !defined(_DEBUG)
            #define _RWUXTHEMEAUTOLIBNAME "RWUXThemeA.lib"
         #elif  defined(_RWOSDLL) &&  defined(_AFXDLL) &&  defined(_DEBUG)
            #define _RWUXTHEMEDLL
            #define _RWUXTHEMEAUTOLIBNAME "RWUXThemeSD.lib"
         #elif  defined(_RWOSDLL) &&  defined(_AFXDLL) && !defined(_DEBUG)
            #define _RWUXTHEMEDLL
            #define _RWUXTHEMEAUTOLIBNAME "RWUXThemeS.lib"
         #elif  defined(_RWOSDLL) && !defined(_AFXDLL)
            #error One of Objective Studio DLL defines is specified but _AFXDLL is not. Objective Studio DLLs cannot be used with static MFC libraries.
         #endif
      #else
         #if   !defined(_RWOSDLL) && !defined(_AFXDLL) &&  defined(_DEBUG)
            #define _RWUXTHEMEAUTOLIBNAME "RWUXThemeUD.lib"
         #elif !defined(_RWOSDLL) && !defined(_AFXDLL) && !defined(_DEBUG)
            #define _RWUXTHEMEAUTOLIBNAME "RWUXThemeU.lib"
         #elif !defined(_RWOSDLL) &&  defined(_AFXDLL) &&  defined(_DEBUG)
            #define _RWUXTHEMEAUTOLIBNAME "RWUXThemeAUD.lib"
         #elif !defined(_RWOSDLL) &&  defined(_AFXDLL) && !defined(_DEBUG)
            #define _RWUXTHEMEAUTOLIBNAME "RWUXThemeAU.lib"
         #elif  defined(_RWOSDLL) &&  defined(_AFXDLL) &&  defined(_DEBUG)
            #define _RWUXTHEMEDLL
            #define _RWUXTHEMEAUTOLIBNAME "RWUXThemeSUD.lib"
         #elif  defined(_RWOSDLL) &&  defined(_AFXDLL) && !defined(_DEBUG)
            #define _RWUXTHEMEDLL
            #define _RWUXTHEMEAUTOLIBNAME "RWUXThemeSU.lib"
         #elif  defined(_RWOSDLL) && !defined(_AFXDLL)
            #error One of Objective Studio DLL defines is specified but _AFXDLL is not. Objective Studio DLLs cannot be used with static MFC libraries.
         #endif
      #endif
   #else //VC6 or VC5
      #ifndef _UNICODE
         #if   !defined(_RWOSDLL) && !defined(_AFXDLL) &&  defined(_DEBUG)
            #define _RWUXTHEMEAUTOLIBNAME "RWUXThemeD60.lib"
         #elif !defined(_RWOSDLL) && !defined(_AFXDLL) && !defined(_DEBUG)
            #define _RWUXTHEMEAUTOLIBNAME "RWUXTheme60.lib"
         #elif !defined(_RWOSDLL) &&  defined(_AFXDLL) &&  defined(_DEBUG)
            #define _RWUXTHEMEAUTOLIBNAME "RWUXThemeAD60.lib"
         #elif !defined(_RWOSDLL) &&  defined(_AFXDLL) && !defined(_DEBUG)
            #define _RWUXTHEMEAUTOLIBNAME "RWUXThemeA60.lib"
         #elif  defined(_RWOSDLL) &&  defined(_AFXDLL) &&  defined(_DEBUG)
            #define _RWUXTHEMEDLL
            #define _RWUXTHEMEAUTOLIBNAME "RWUXThemeSD.lib"
         #elif  defined(_RWOSDLL) &&  defined(_AFXDLL) && !defined(_DEBUG)
            #define _RWUXTHEMEDLL
            #define _RWUXTHEMEAUTOLIBNAME "RWUXThemeS.lib"
         #elif  defined(_RWOSDLL) && !defined(_AFXDLL)
            #error One of Objective Studio DLL defines is specified but _AFXDLL is not. Objective Studio DLLs cannot be used with static MFC libraries.
         #endif
      #else
         #if   !defined(_RWOSDLL) && !defined(_AFXDLL) &&  defined(_DEBUG)
            #define _RWUXTHEMEAUTOLIBNAME "RWUXThemeUD60.lib"
         #elif !defined(_RWOSDLL) && !defined(_AFXDLL) && !defined(_DEBUG)
            #define _RWUXTHEMEAUTOLIBNAME "RWUXThemeU60.lib"
         #elif !defined(_RWOSDLL) &&  defined(_AFXDLL) &&  defined(_DEBUG)
            #define _RWUXTHEMEAUTOLIBNAME "RWUXThemeAUD60.lib"
         #elif !defined(_RWOSDLL) &&  defined(_AFXDLL) && !defined(_DEBUG)
            #define _RWUXTHEMEAUTOLIBNAME "RWUXThemeAU60.lib"
         #elif  defined(_RWOSDLL) &&  defined(_AFXDLL) &&  defined(_DEBUG)
            #define _RWUXTHEMEDLL
            #define _RWUXTHEMEAUTOLIBNAME "RWUXThemeSUD.lib"
         #elif  defined(_RWOSDLL) &&  defined(_AFXDLL) && !defined(_DEBUG)
            #define _RWUXTHEMEDLL
            #define _RWUXTHEMEAUTOLIBNAME "RWUXThemeSU.lib"
         #elif  defined(_RWOSDLL) && !defined(_AFXDLL)
            #error One of Objective Studio DLL defines is specified but _AFXDLL is not. Objective Studio DLLs cannot be used with static MFC libraries.
         #endif
      #endif
   #endif
#endif //RWTHEMEPROXYBUILD

#ifdef _RWUXTHEMEAUTOLIBNAME
   #pragma comment(lib, _RWUXTHEMEAUTOLIBNAME)
//CP20050210   #pragma message( "Automatically linking with " _RWUXTHEMEAUTOLIBNAME)
#endif

#ifdef _RWUXTHEMEDLL
   #ifndef RWTHEMEPROXYBUILD
      #define RWTHEMEAPI(rettype)   extern "C" rettype __declspec(dllimport) 
   #else
      #define RWTHEMEAPI(rettype)   extern "C" rettype __declspec(dllexport)
   #endif // RWTHEMEPROXYBUILD
#else //_RWUXTHEMEDLL
   #define RWTHEMEAPI(rettype) extern "C" rettype
#endif

//We need this section to allow applications to compile without including uxtheme.h
#include "VC6PlatDefs.h"

// Function to control XP Theming Behavior
RWTHEMEAPI(BOOL)  RWEnableXPThemesDrawing( BOOL enable = TRUE );


// Funcitons forwarded to UXThemeAPI
// For information on these functions look for function names without RW prefix in MSDN 
RWTHEMEAPI(HTHEME)   RWOpenThemeData(HWND hwnd, LPCWSTR pszClassList);
RWTHEMEAPI(HRESULT) RWCloseThemeData(HTHEME hTheme);
RWTHEMEAPI(HRESULT) RWDrawThemeBackground(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, const RECT *pRect, const RECT *pClipRect);
RWTHEMEAPI(HRESULT) RWDrawThemeText(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, LPCWSTR pszText, int iCharCount, DWORD dwTextFlags, DWORD dwTextFlags2, const RECT *pRect);
RWTHEMEAPI(HRESULT) RWGetThemeBackgroundContentRect(HTHEME hTheme, HDC hdc, int iPartId, int iStateId,  const RECT *pBoundingRect, RECT *pContentRect);
RWTHEMEAPI(HRESULT) RWGetThemeBackgroundExtent(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, const RECT *pContentRect, RECT *pExtentRect);
RWTHEMEAPI(HRESULT) RWGetThemePartSize(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, RECT *prc, enum THEMESIZE eSize, OUT SIZE *psz);
RWTHEMEAPI(HRESULT) RWGetThemeTextExtent(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, LPCWSTR pszText, int iCharCount, DWORD dwTextFlags, const RECT *pBoundingRect, RECT *pExtentRect);
RWTHEMEAPI(HRESULT) RWGetThemeTextMetrics(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, TEXTMETRIC* ptm);
RWTHEMEAPI(HRESULT) RWGetThemeBackgroundRegion(HTHEME hTheme, HDC hdc,  int iPartId, int iStateId, const RECT *pRect, HRGN *pRegion);
RWTHEMEAPI(HRESULT) RWHitTestThemeBackground(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, DWORD dwOptions, const RECT *pRect, HRGN hrgn, POINT ptTest, WORD *pwHitTestCode);
RWTHEMEAPI(HRESULT) RWDrawThemeEdge(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, const RECT *pDestRect, UINT uEdge, UINT uFlags, RECT *pContentRect);
RWTHEMEAPI(HRESULT) RWDrawThemeIcon(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, const RECT *pRect, HIMAGELIST himl, int iImageIndex);
RWTHEMEAPI(BOOL)  RWIsThemePartDefined(HTHEME hTheme, int iPartId, int iStateId);
RWTHEMEAPI(BOOL)  RWIsThemeBackgroundPartiallyTransparent(HTHEME hTheme, int iPartId, int iStateId);
RWTHEMEAPI(HRESULT) RWGetThemeColor(HTHEME hTheme, int iPartId, int iStateId, int iPropId, COLORREF *pColor);
RWTHEMEAPI(HRESULT) RWGetThemeMetric(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, int iPropId, int *piVal);
RWTHEMEAPI(HRESULT) RWGetThemeString(HTHEME hTheme, int iPartId, int iStateId, int iPropId, LPWSTR pszBuff, int cchMaxBuffChars);
RWTHEMEAPI(HRESULT) RWGetThemeBool(HTHEME hTheme, int iPartId, int iStateId, int iPropId, BOOL *pfVal);
RWTHEMEAPI(HRESULT) RWGetThemeInt(HTHEME hTheme, int iPartId, int iStateId, int iPropId, int *piVal);
RWTHEMEAPI(HRESULT) RWGetThemeEnumValue(HTHEME hTheme, int iPartId, int iStateId, int iPropId, int *piVal);
RWTHEMEAPI(HRESULT) RWGetThemePosition(HTHEME hTheme, int iPartId, int iStateId, int iPropId, POINT *pPoint);
RWTHEMEAPI(HRESULT) RWGetThemeFont(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, int iPropId, LOGFONT *pFont);
RWTHEMEAPI(HRESULT) RWGetThemeRect(HTHEME hTheme, int iPartId, int iStateId, int iPropId, RECT *pRect);
RWTHEMEAPI(HRESULT) RWGetThemeMargins(HTHEME hTheme, HDC hdc, int iPartId, int iStateId, int iPropId, RECT *prc, MARGINS *pMargins);
RWTHEMEAPI(HRESULT) RWGetThemeIntList(HTHEME hTheme, int iPartId, int iStateId, int iPropId, INTLIST *pIntList);
RWTHEMEAPI(HRESULT) RWGetThemePropertyOrigin(HTHEME hTheme, int iPartId, int iStateId, int iPropId, enum PROPERTYORIGIN *pOrigin);
RWTHEMEAPI(HRESULT) RWSetWindowTheme(HWND hwnd, LPCWSTR pszSubAppName, LPCWSTR pszSubIdList);
RWTHEMEAPI(HRESULT) RWGetThemeFilename(HTHEME hTheme, int iPartId, int iStateId, int iPropId, LPWSTR pszThemeFileName, int cchMaxBuffChars);
RWTHEMEAPI(COLORREF) RWGetThemeSysColor(HTHEME hTheme, int iColorId);
RWTHEMEAPI(HBRUSH)   RWGetThemeSysColorBrush(HTHEME hTheme, int iColorId);
RWTHEMEAPI(BOOL)  RWGetThemeSysBool(HTHEME hTheme, int iBoolId);
RWTHEMEAPI(int)      RWGetThemeSysSize(HTHEME hTheme, int iSizeId);
RWTHEMEAPI(HRESULT) RWGetThemeSysFont(HTHEME hTheme, int iFontId, LOGFONT *plf);
RWTHEMEAPI(HRESULT) RWGetThemeSysString(HTHEME hTheme, int iStringId, LPWSTR pszStringBuff, int cchMaxStringChars);
RWTHEMEAPI(HRESULT) RWGetThemeSysInt(HTHEME hTheme, int iIntId, int *piValue);
RWTHEMEAPI(BOOL)  RWIsThemeActive();
RWTHEMEAPI(BOOL)  RWIsAppThemed();
RWTHEMEAPI(HTHEME)   RWGetWindowTheme(HWND hwnd);
RWTHEMEAPI(HRESULT) RWEnableThemeDialogTexture(HWND hwnd, DWORD dwFlags);
RWTHEMEAPI(BOOL)  RWIsThemeDialogTextureEnabled(HWND hwnd);
RWTHEMEAPI(DWORD) RWGetThemeAppProperties();
RWTHEMEAPI(void)  RWSetThemeAppProperties(DWORD dwFlags);
RWTHEMEAPI(HRESULT) RWGetCurrentThemeName( LPWSTR pszThemeFileName, int cchMaxNameChars, LPWSTR pszColorBuff, int cchMaxColorChars, LPWSTR pszSizeBuff, int cchMaxSizeChars);
RWTHEMEAPI(HRESULT) RWGetThemeDocumentationProperty(LPCWSTR pszThemeName, LPCWSTR pszPropertyName, LPWSTR pszValueBuff, int cchMaxValChars);
RWTHEMEAPI(HRESULT) RWDrawThemeParentBackground(HWND hwnd, HDC hdc, RECT* prc);
RWTHEMEAPI(HRESULT) RWEnableTheming(BOOL fEnable);

// Color manipulation functions
RWTHEMEAPI(COLORREF) RWBlendColors( COLORREF dstClr, COLORREF srcClr, BYTE blendVal );
RWTHEMEAPI(COLORREF) RWLightenColor( COLORREF srcClr, BYTE lightAmount );
RWTHEMEAPI(BOOL)   RWIsDarkColor( COLORREF tstClr, DWORD threshold );
RWTHEMEAPI(COLORREF) RWSetContrast( COLORREF clr1, COLORREF clr2, int threshold );

// Defines to use in RWGetDNETColor
#define RW_TOOLBAR         0x00
#define RW_TOOLBARSEP      0x01
#define RW_TOOLBARTEXT     0x02
#define RW_TBBTNFACENORM   0x03
#define RW_TBBTNFRMNORM    0x04
#define RW_TBBTNFACEHOT    0x05
#define RW_TBBTNFRMHOT     0x06
#define RW_TBBTNFACEPRESS  0x07
#define  RW_TBBTNFRMPRESS  0x08
#define RW_TBBTNFACEDIS    0x09
#define RW_TBBTNFRMDIS     0x0A
#define RW_TBBTNFACECHK    0x0B
#define RW_TBBTNFRMCHK     0x0C
#define RW_TBBTNFACECHKHOT 0x0D
#define RW_TBBTNFRMCHKHOT  0x0E
#define RW_MENU            0x0F
#define RW_MENUTXT         0x10
#define RW_MENUDIS         0x11
#define RW_MENUTXTDIS      0x12
#define RW_MENUHOT         0x13
#define RW_MENUFRMHOT      0x14
#define RW_MENUTXTHOT      0x15
#define RW_MENUDISHOT      0x16
#define RW_MENUTXTDISHOT   0x17
#define RW_MENUFRMDISHOT   0x18
#define RW_MENUBAND        0x19
#define  RW_MENUFRAME      0x1A
#define RW_MENUSEP         0x1B
#define RW_MENUBAR         0x1C
#define RW_MENUBARTXT      0x1D
#define RW_ICONSHADOW      0x1E
#define RW_DISTEXT         0x1F
#define RW_GRIPPER         0x20

// Internal color map functions
RWTHEMEAPI(void)   RWResetColors();
RWTHEMEAPI(COLORREF) RWGetDNETColor( DWORD colorId );

// Imagelist manipulation functions
RWTHEMEAPI(void) RWDrawImage( HDC hDC, HIMAGELIST hImgLst, UINT index, UINT offsetX, UINT offsetY, UINT width, UINT height, BOOL isHiContrast );
RWTHEMEAPI(void) RWDrawHighlightedImage( HDC hDC, HIMAGELIST hImgLst, UINT index, UINT offsetX, UINT offsetY, UINT width, UINT height, COLORREF highlightingColor, BYTE amount );
RWTHEMEAPI(void) RWDrawFullImageShadow( HDC hDC, HIMAGELIST hImgLst, UINT index, UINT offsetX, UINT offsetY, UINT width, UINT height, COLORREF shadowColor );
RWTHEMEAPI(void) RWDrawFlatImageShadow( HDC hDC, HIMAGELIST hImgLst, UINT index, UINT offsetX, UINT offsetY, UINT width, UINT height, COLORREF shadowColor );

// Pre-drawn bitmaps manipulation functions
RWTHEMEAPI(void) RWDrawDCImage( HDC hDC, UINT offsetX, UINT offsetY, UINT width, UINT height, HDC hBmpDC, UINT bmpOffsetX, UINT bmpOffsetY, COLORREF transColor, BOOL isHiContrast );
RWTHEMEAPI(void) RWDrawDCHighlightedImage( HDC hDC, UINT offsetX, UINT offsetY, UINT width, UINT height, HDC hBmpDC, UINT bmpOffsetX, UINT bmpOffsetY, COLORREF transColor, COLORREF highlightingColor, BYTE amount );
RWTHEMEAPI(void) RWDrawDCFullImageShadow( HDC hDC, UINT offsetX, UINT offsetY, UINT width, UINT height, HDC hBmpDC, UINT bmpOffsetX, UINT bmpOffsetY, COLORREF transColor, COLORREF shadowColor );
RWTHEMEAPI(void) RWDrawDCFlatImageShadow( HDC hDC, UINT offsetX, UINT offsetY, UINT width, UINT height, HDC hBmpDC, UINT bmpOffsetX, UINT bmpOffsetY, COLORREF transColor, COLORREF shadowColor );

// Drawing functions - if possible - they rely on WinAPI functions - otherwise - internal implementation
RWTHEMEAPI(BOOL) RWTransparentBlt( HDC hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, HDC hdcSrc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, UINT crTransparent );
RWTHEMEAPI(BOOL) RWBlendBlt( HDC hdcDest, int nXOriginDest, int nYOriginDest, int nWidth, int nHeight, HDC hdcSrc, int nXOriginSrc, int nYOriginSrc, BYTE alphaConst );

// Helper functions
RWTHEMEAPI(HRESULT) RWDrawThemedBMPItem( HWND hWnd, HDC hDC, HBITMAP hBMP, LPCWSTR pszClassList, int iPartId, int iStateId, int x, int y, int cx, int cy, int bmpX, int bmpY, int bmpCX, int bmpCY, unsigned int transColor = 0x00C0C0C0 );

//Some functions not present on older operating system
RWTHEMEAPI(BOOL)   RWTrackMouseEvent( LPTRACKMOUSEEVENT lpEventTrack );

#endif // __RWUXTHEME_H
