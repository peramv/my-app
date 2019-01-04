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

// gxext.h : common extensions
/////////////////////////////////////////////////////////////////////////////

#ifndef _GXEXT_H_
#define _GXEXT_H_

#ifndef _GXSTATE_H_
#include "grid\gxstate.h"
#endif

#ifndef _GXRESRC_H_
#include "grid\gxresrc.h"
#endif

//
// GridMFC Extension DLL
// initialize declaration context
//

#ifdef _GXDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    GX_DATAEXT
#endif

// header file

/////////////////////////////////////////////////////////////////////////////
// Time and date formatting

#include <time.h>

#if !defined(_AFX_NO_DB_SUPPORT)

#include <sqlext.h> // TIMESTAMP_STRUCT

#else

// needed for GXFormatTimeStamp

typedef short int               SWORD;
typedef unsigned short int      UWORD;
typedef unsigned long int       UDWORD;

typedef SWORD                   SQLSMALLINT;
typedef UDWORD                  SQLUINTEGER;
typedef UWORD                   SQLUSMALLINT;

typedef struct tagTIMESTAMP_STRUCT
{
		SQLSMALLINT    year;
		SQLUSMALLINT   month;
		SQLUSMALLINT   day;
		SQLUSMALLINT   hour;
		SQLUSMALLINT   minute;
		SQLUSMALLINT   second;
		SQLUINTEGER    fraction;
} TIMESTAMP_STRUCT;

#endif

size_t AFXAPI GXIntlStrFtime(
	HINSTANCE nResourceHandle,
	UINT nStrFTimeResourceID,
	LPTSTR s,
	size_t maxs,
	LPCTSTR f,
	const struct tm *t);

void AFXAPI GXFormatTimeStamp(CString& strRet, const CTime* pTime);
void AFXAPI GXFormatTimeStamp(CString& strRet, const TIMESTAMP_STRUCT* pTime);

// Parsing date/time values

// NOTE: This methods are provided because parsing
// date/time values was not possible with VC 1.5x
// and VC 2.x projects.
//
// If you are using VC 4.x or greater, we recommend
// using the COleDateTime::ParseDateTime for this
// purpose.

void AFXAPI GXImplementOleDateTime();
void AFXAPI GXImplementNoOleDateTime();
void AFXAPI GXUpdateDateTimeSettings();
GXDateFormat AFXAPI GXGetDateFormatFromWinIni(BOOL bReload, BOOL& bCentury, TCHAR& chDateSep);
TCHAR AFXAPI GXGetTimeSeparatorFromWinIni(BOOL bReload = FALSE);

// CTime
BOOL AFXAPI GXParseDateTime(struct tm* ptm, LPCTSTR szValue, GXDateFormat DateFormat = gxDEFAULT);

// TIMESTAMP_STRUCT
BOOL AFXAPI GXParseDateTime(TIMESTAMP_STRUCT* ptm, LPCTSTR szValue, GXDateFormat DateFormat = gxDEFAULT);

/////////////////////////////////////////////////////////////////////////////
// global methods

CView*      AFXAPI GXGetActiveView();
	// returns pointer to active view object

CDocument*  AFXAPI GXGetActiveDocument();
	// returns pointer to active document

CWnd* AFXAPI GXGetParentWnd(const CWnd* pWnd, struct CRuntimeClass* pClass, BOOL bAnyState);
	// returns pointer to parent window
	// or NULL if parent window is not derived from pClass

void AFXAPI GXFormatString1(CString& rString, LPCTSTR lpszFormat, LPCTSTR lpsz1);

CString AFXAPI GXReplaceString(CString& strTarget, CString strFind, CString strReplace);

void AFXAPI GXWriteProfileLong(LPCTSTR szSection, LPCTSTR szEntry, LONG val);
LONG AFXAPI GXGetProfileLong(LPCTSTR szSection, LPCTSTR szEntry, LONG val);

/////////////////////////////////////////////////////////////////////////////
// Preprocessor directives

#ifndef _GXDLL

#define DECLARE_REGISTER() \
public: \
	static LPCTSTR AFXAPI RegisterClass(); \
	static void AFXAPI UnregisterClass(); \
	static LPCTSTR AFXAPI RegisterClass(HINSTANCE hInstance); \
	static void AFXAPI UnregisterClass(HINSTANCE hInstance); \
	static CMapPtrToWord GXNEAR _gxregmap; \
protected: \
	static LRESULT CALLBACK AFX_EXPORT WndProcHook(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam); \
	virtual void PostNcDestroy();
// END DECLARE_REGISTER


#ifdef _WIN64

#define IMPLEMENT_REGISTER(class_name, _style, icon, cursor, background) \
	CMapPtrToWord GXNEAR class_name::_gxregmap; \
	LPCTSTR AFXAPI class_name::RegisterClass() \
	{ \
		WNDCLASS wndcls;  \
		LPCTSTR szName = _T(#class_name) ; \
		if (::GetClassInfo(AfxGetInstanceHandle(), szName, &wndcls)) \
			return szName; \
		wndcls.style = _style ; \
		wndcls.lpfnWndProc = class_name::WndProcHook ; \
		wndcls.cbClsExtra = wndcls.cbWndExtra = 0 ; \
		wndcls.hInstance = AfxGetInstanceHandle() ; \
		wndcls.hIcon = icon ; \
		wndcls.hCursor = cursor ; \
		wndcls.hbrBackground = background ; \
		wndcls.lpszMenuName = NULL ; \
		wndcls.lpszClassName = szName ; \
		if (!::RegisterClass(&wndcls)) \
			AfxThrowResourceException() ; \
		return szName ;  } \
	LPCTSTR AFXAPI class_name::RegisterClass(HINSTANCE hInstance) \
	{ \
		WNDCLASS wndcls;  \
		LPCTSTR szName = _T(#class_name) ; \
		if (::GetClassInfo(hInstance, szName, &wndcls)) \
			return szName; \
		wndcls.style = _style ; \
		wndcls.lpfnWndProc = class_name::WndProcHook ; \
		wndcls.cbClsExtra = wndcls.cbWndExtra = 0 ; \
		wndcls.hInstance = hInstance ; \
		wndcls.hIcon = icon ; \
		wndcls.hCursor = cursor ; \
		wndcls.hbrBackground = background ; \
		wndcls.lpszMenuName = NULL ; \
		wndcls.lpszClassName = szName ; \
		if (!::RegisterClass(&wndcls)) \
			AfxThrowResourceException() ; \
		return szName ;  } \
	LRESULT CALLBACK AFX_EXPORT class_name::WndProcHook(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) \
	{ \
		class_name * pWnd = new class_name(); \
		pWnd->Attach(hWnd); \
		_gxregmap[pWnd] = 1; \
		::SetWindowLongPtr(hWnd, GWLP_WNDPROC, (SEC_LONG)AfxWndProc); \
		return ::CallWindowProc(AfxWndProc, hWnd, msg, wParam, lParam); } \
	void AFXAPI class_name::UnregisterClass() \
	{ \
		::UnregisterClass( _T(#class_name) , AfxGetInstanceHandle() );  } \
	void AFXAPI class_name::UnregisterClass(HINSTANCE hInstance) \
	{ \
		::UnregisterClass( _T(#class_name) , hInstance );  } \
	void class_name::PostNcDestroy() \
	{ \
		WORD w; \
		if (_gxregmap.Lookup(this, w)) \
		{ \
			delete this; \
			_gxregmap.RemoveKey(this); \
		} \
	}
// END IMPLEMENT_REGISTER

#else	//WIN32

#define IMPLEMENT_REGISTER(class_name, _style, icon, cursor, background) \
	CMapPtrToWord GXNEAR class_name::_gxregmap; \
	LPCTSTR AFXAPI class_name::RegisterClass() \
	{ \
		WNDCLASS wndcls;  \
		LPCTSTR szName = _T(#class_name) ; \
		if (::GetClassInfo(AfxGetInstanceHandle(), szName, &wndcls)) \
			return szName; \
		wndcls.style = _style ; \
		wndcls.lpfnWndProc = class_name::WndProcHook ; \
		wndcls.cbClsExtra = wndcls.cbWndExtra = 0 ; \
		wndcls.hInstance = AfxGetInstanceHandle() ; \
		wndcls.hIcon = icon ; \
		wndcls.hCursor = cursor ; \
		wndcls.hbrBackground = background ; \
		wndcls.lpszMenuName = NULL ; \
		wndcls.lpszClassName = szName ; \
		if (!::RegisterClass(&wndcls)) \
			AfxThrowResourceException() ; \
		return szName ;  } \
	LPCTSTR AFXAPI class_name::RegisterClass(HINSTANCE hInstance) \
	{ \
		WNDCLASS wndcls;  \
		LPCTSTR szName = _T(#class_name) ; \
		if (::GetClassInfo(hInstance, szName, &wndcls)) \
			return szName; \
		wndcls.style = _style ; \
		wndcls.lpfnWndProc = class_name::WndProcHook ; \
		wndcls.cbClsExtra = wndcls.cbWndExtra = 0 ; \
		wndcls.hInstance = hInstance ; \
		wndcls.hIcon = icon ; \
		wndcls.hCursor = cursor ; \
		wndcls.hbrBackground = background ; \
		wndcls.lpszMenuName = NULL ; \
		wndcls.lpszClassName = szName ; \
		if (!::RegisterClass(&wndcls)) \
			AfxThrowResourceException() ; \
		return szName ;  } \
	LRESULT CALLBACK AFX_EXPORT class_name::WndProcHook(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) \
	{ \
		class_name * pWnd = new class_name(); \
		pWnd->Attach(hWnd); \
		_gxregmap[pWnd] = 1; \
		::SetWindowLong(hWnd, GWL_WNDPROC, (DWORD)AfxWndProc); \
		return ::CallWindowProc(AfxWndProc, hWnd, msg, wParam, lParam); } \
	void AFXAPI class_name::UnregisterClass() \
	{ \
		::UnregisterClass( _T(#class_name) , AfxGetInstanceHandle() );  } \
	void AFXAPI class_name::UnregisterClass(HINSTANCE hInstance) \
	{ \
		::UnregisterClass( _T(#class_name) , hInstance );  } \
	void class_name::PostNcDestroy() \
	{ \
		WORD w; \
		if (_gxregmap.Lookup(this, w)) \
		{ \
			delete this; \
			_gxregmap.RemoveKey(this); \
		} \
	}
// END IMPLEMENT_REGISTER

#endif	// _WIN64

#else // DLL version

#include "grid\gxstate.h"

#define DECLARE_REGISTER() \
public: \
	static LPCTSTR AFXAPI RegisterClass(); \
	static void AFXAPI UnregisterClass(); \
	static LPCTSTR AFXAPI RegisterClass(HINSTANCE hInstance); \
	static void AFXAPI UnregisterClass(HINSTANCE hInstance); \
protected: \
	static LRESULT CALLBACK AFX_EXPORT WndProcHook(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam); \
	virtual void PostNcDestroy();
// END DECLARE_REGISTER


#ifdef _WIN64

#define IMPLEMENT_REGISTER(class_name, _style, icon, cursor, background) \
	LPCTSTR AFXAPI class_name::RegisterClass() \
	{ \
		WNDCLASS wndcls;  \
		LPCTSTR szName = _T(#class_name) ; \
		if (::GetClassInfo(AfxGetInstanceHandle(), szName, &wndcls)) \
			return szName; \
		wndcls.style = _style ; \
		wndcls.lpfnWndProc = class_name::WndProcHook ; \
		wndcls.cbClsExtra = wndcls.cbWndExtra = 0 ; \
		wndcls.hInstance = AfxGetInstanceHandle() ; \
		wndcls.hIcon = icon ; \
		wndcls.hCursor = cursor ; \
		wndcls.hbrBackground = background ; \
		wndcls.lpszMenuName = NULL ; \
		wndcls.lpszClassName = szName ; \
		if (!::RegisterClass(&wndcls)) \
			AfxThrowResourceException() ; \
		return szName ;  } \
	LPCTSTR AFXAPI class_name::RegisterClass(HINSTANCE hInstance) \
	{ \
		WNDCLASS wndcls;  \
		LPCTSTR szName = _T(#class_name) ; \
		if (::GetClassInfo(hInstance, szName, &wndcls)) \
			return szName; \
		wndcls.style = _style ; \
		wndcls.lpfnWndProc = class_name::WndProcHook ; \
		wndcls.cbClsExtra = wndcls.cbWndExtra = 0 ; \
		wndcls.hInstance = hInstance ; \
		wndcls.hIcon = icon ; \
		wndcls.hCursor = cursor ; \
		wndcls.hbrBackground = background ; \
		wndcls.lpszMenuName = NULL ; \
		wndcls.lpszClassName = szName ; \
		if (!::RegisterClass(&wndcls)) \
			AfxThrowResourceException() ; \
		return szName ;  } \
	LRESULT CALLBACK AFX_EXPORT class_name::WndProcHook(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) \
	{ \
		class_name * pWnd = new class_name(); \
		pWnd->Attach(hWnd); \
		GXGetAppState()->m_ctlusrState.m_ctrlmap[pWnd] = 1; \
		::SetWindowLongPtr(hWnd, GWLP_WNDPROC, (SEC_LONG)AfxWndProc); \
		return ::CallWindowProc(AfxWndProc, hWnd, msg, wParam, lParam); } \
	void AFXAPI class_name::UnregisterClass() \
	{ \
		::UnregisterClass( _T(#class_name) , AfxGetInstanceHandle() );  } \
	void AFXAPI class_name::UnregisterClass(HINSTANCE hInstance) \
	{ \
		::UnregisterClass( _T(#class_name) , hInstance );  } \
	void class_name::PostNcDestroy() \
	{ \
		WORD w; \
		if (GXGetAppState()->m_ctlusrState.m_ctrlmap.Lookup(this, w)) \
		{ \
			delete this; \
			GXGetAppState()->m_ctlusrState.m_ctrlmap.RemoveKey(this); \
		} \
	}
// END IMPLEMENT_REGISTER

#else	//WIN32

#define IMPLEMENT_REGISTER(class_name, _style, icon, cursor, background) \
	LPCTSTR AFXAPI class_name::RegisterClass() \
	{ \
		WNDCLASS wndcls;  \
		LPCTSTR szName = _T(#class_name) ; \
		if (::GetClassInfo(AfxGetInstanceHandle(), szName, &wndcls)) \
			return szName; \
		wndcls.style = _style ; \
		wndcls.lpfnWndProc = class_name::WndProcHook ; \
		wndcls.cbClsExtra = wndcls.cbWndExtra = 0 ; \
		wndcls.hInstance = AfxGetInstanceHandle() ; \
		wndcls.hIcon = icon ; \
		wndcls.hCursor = cursor ; \
		wndcls.hbrBackground = background ; \
		wndcls.lpszMenuName = NULL ; \
		wndcls.lpszClassName = szName ; \
		if (!::RegisterClass(&wndcls)) \
			AfxThrowResourceException() ; \
		return szName ;  } \
	LPCTSTR AFXAPI class_name::RegisterClass(HINSTANCE hInstance) \
	{ \
		WNDCLASS wndcls;  \
		LPCTSTR szName = _T(#class_name) ; \
		if (::GetClassInfo(hInstance, szName, &wndcls)) \
			return szName; \
		wndcls.style = _style ; \
		wndcls.lpfnWndProc = class_name::WndProcHook ; \
		wndcls.cbClsExtra = wndcls.cbWndExtra = 0 ; \
		wndcls.hInstance = hInstance ; \
		wndcls.hIcon = icon ; \
		wndcls.hCursor = cursor ; \
		wndcls.hbrBackground = background ; \
		wndcls.lpszMenuName = NULL ; \
		wndcls.lpszClassName = szName ; \
		if (!::RegisterClass(&wndcls)) \
			AfxThrowResourceException() ; \
		return szName ;  } \
	LRESULT CALLBACK AFX_EXPORT class_name::WndProcHook(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) \
	{ \
		class_name * pWnd = new class_name(); \
		pWnd->Attach(hWnd); \
		GXGetAppState()->m_ctlusrState.m_ctrlmap[pWnd] = 1; \
		::SetWindowLong(hWnd, GWL_WNDPROC, (DWORD)AfxWndProc); \
		return ::CallWindowProc(AfxWndProc, hWnd, msg, wParam, lParam); } \
	void AFXAPI class_name::UnregisterClass() \
	{ \
		::UnregisterClass( _T(#class_name) , AfxGetInstanceHandle() );  } \
	void AFXAPI class_name::UnregisterClass(HINSTANCE hInstance) \
	{ \
		::UnregisterClass( _T(#class_name) , hInstance );  } \
	void class_name::PostNcDestroy() \
	{ \
		WORD w; \
		if (GXGetAppState()->m_ctlusrState.m_ctrlmap.Lookup(this, w)) \
		{ \
			delete this; \
			GXGetAppState()->m_ctlusrState.m_ctrlmap.RemoveKey(this); \
		} \
	}
// END IMPLEMENT_REGISTER

#endif	//_WIN64

#endif // _GXDLL

/////////////////////////////////////////////////////////////////////////////
// Drawing routines

class CGXDrawingAndFormatting
{
public:
	virtual ~CGXDrawingAndFormatting();

	// Patterns (used in brushes)
	virtual const CBitmap* GXGetPatternBitmap(int n);

	// Text routines
	virtual int  GXDrawTextLikeMultiLineEditEx(CDC* pDC, LPCTSTR lpszString, int nCount, CRect rect, UINT nFormat, LPRECT lpRectClip = NULL, gxEllipseType gxFormatEx = gxNoEllipse);

	virtual int  GXDrawTextLikeMultiLineEdit(CDC* pDC, LPCTSTR lpszString, int nCount, CRect rect, UINT nFormat, LPRECT lpRectClip = NULL);
	virtual int  GXDrawRotatedText(CDC* pDC, LPCTSTR lpszString, int nCount, CRect rect, UINT nFormat, LONG lfOrientation, LPRECT lpRectClip = NULL);
	virtual int  GXGetMultiLineTextPosUnderPt(CDC* pDC, LPCTSTR lpszString, int nCount, CRect rect, UINT nFormat, CPoint pt);
	virtual int  GXGetMultiLineTextBreakCount(CDC* pDC, LPCTSTR lpszString, int nCount, CRect rc, UINT nFormat);
	virtual int  GXComputeLineBreaks(CDC* pDC, LPCTSTR sz, int nCount, LPRECT rc, UINT nFormat, int* LineBreaks, int* LineLengths, int nMaxBreaks);

	// Text formatting and parsing
	virtual CString GXFormatText(const CGXStyle& style, LPCTSTR pszValue = NULL, unsigned nValueType = GX_VT_STRING, CGXGridCore* pGrid = NULL, CGXControl* pControl = NULL);
	virtual BOOL GXDeval(LPCTSTR s, double *d, unsigned* pImportFormat = NULL, unsigned* pImportPlaces = NULL);

	// 3d frame
	virtual void GXDraw3dFrame(CDC* pDC, int x0, int y0, int x1, int y1, int w, COLORREF rgbTopLeft, COLORREF rgbBottomRight);

	// sunken borders (for windows in dialogs)
	virtual void _GXDrawSunkenBorders(CDC* pDC, CRect& rc, BOOL bBorder, BOOL bClientEdge);

	// focus text (push buttons call this when button has focus)
	virtual void GXDrawFocusText(CDC* pDC, CRect rect, BOOL bFocus, LPCTSTR lpszString, UINT nFormat);

	// CGXStatic::Draw
	virtual void DrawStatic(CGXControl* pControl, CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle);

	static void AFXAPI ImplementDrawRotatedText();
	static void AFXAPI ImplementNumberFormatting();
};

// Support for DDP/DIB Bitmaps

// supporting routines for device independent bitmaps
HANDLE AFXAPI GXLoadResourceBitmap(HINSTANCE hInstance, LPCTSTR lpString);
HANDLE AFXAPI GXLoadResourceBitmap(LPCTSTR lpString);
DWORD AFXAPI GXGetNumDIBColorEntries(LPBITMAPINFO pBmpInfo);

// transparent bitmaps
void AFXAPI GXDrawTransparentBitmap(CDC* pDC, CBitmap* pBitmap, int xStart,
	int yStart, COLORREF cTransparentColor);

// Button state

const UINT GX_BTNFOCUS      = 0x01;
const UINT GX_BTNSCOPE      = 0x02;
const UINT GX_BTNPRESSED    = 0x04;
const UINT GX_BTNCHECKED    = 0x04;
const UINT GX_BTNUNCHECKED  = 0x08;

// Pure VGA colors
COLORREF AFXAPI GXGetVGAColor(int index);

// Find a color in the array
int AFXAPI GXFindColor(COLORREF rgbColor);

// Patterns (used in brushes)
extern int _gxnPatternCount;
const CBitmap* AFXAPI GXGetPatternBitmap(int n);

class CGXStyle;

// Drawing routines

void AFXAPI GXDrawInset(CDC* pDC, int x, int y, int dx, int dy, COLORREF rgbFace = RGB(255,255,255));
void AFXAPI GXDrawButton(CDC* pDC, int x, int y, int dx, int dy, BOOL bPressed, COLORREF rgbFace = RGB(192,192,192));
void AFXAPI GXInvertRect(CDC* pDC, const CRect& rect, const CRect& rectClip);
void AFXAPI GXPatB(CDC* pDC,int x,int y,int dx,int dy, COLORREF rgb);
void AFXAPI GXPatB(CDC* pDC,const CRect& rc, COLORREF rgb);
void AFXAPI GXDrawBlankButton(CDC* pDC, int x, int y, int dx, int dy, BOOL bPressed = FALSE);
int  AFXAPI GXDrawRadioButtons(CDC* pDC, CRect rect, LPCTSTR pszValue, LPCTSTR pszChoices, BOOL bDraw3D = FALSE);
int  AFXAPI GXHitTestRadioButtons(CDC* pDC, CRect rect, LPCTSTR pszChoices, CPoint pt);
int  AFXAPI GXDrawTextLikeMultiLineEdit(CDC* pDC, LPCTSTR lpszString, int nCount, CRect rect, UINT nFormat, LPRECT lpRectClip = NULL);
int  AFXAPI GXDrawTextLikeMultiLineEditEx(CDC* pDC, LPCTSTR lpszString, int nCount, CRect rect, UINT nFormat, LPRECT lpRectClip = NULL, gxEllipseType gxFormatEx = gxNoEllipse);
int  AFXAPI GXGetMultiLineTextPosUnderPt(CDC* pDC, LPCTSTR lpszString, int nCount, CRect rect, UINT nFormat, CPoint pt);
int  AFXAPI GXGetMultiLineTextBreakCount(CDC* pDC, LPCTSTR lpszString, int nCount, CRect rc, UINT nFormat);
int  AFXAPI GXComputeLineBreaks(CDC* pDC, LPCTSTR sz, int nCount, LPRECT rc, UINT nFormat, int* LineBreaks, int* LineLengths, int nMaxBreaks);
void AFXAPI GXDraw3dFrame(CDC* pDC, int x0, int y0, int x1, int y1, int w, COLORREF rgbTopLeft, COLORREF rgbBottomRight);
void AFXAPI GXDraw3dFrame(CDC* pDC, const CRect &rc, int w, COLORREF rgbTopLeft, COLORREF rgbBottomRight);
int  AFXAPI GXGetNextLine(CString& s, CString &sLine);
void AFXAPI GXGetColString(LPCTSTR pszLine, int nCol, LPTSTR szResult, int nMaxLen);
int AFXAPI GXFindChoiceListItem(const CString& strFind, int nCol, const CString& strChoiceList, BOOL bSkipFirstRow, CString& sItem, BOOL bExact = TRUE);
void AFXAPI GXSortChoiceList(CString& strChoiceList, int nCol = 0, BOOL bSkipFirstRow = FALSE);
BOOL AFXAPI GXLoadSysColorBitmap(CBitmap& bmp, LPCTSTR lpszName);
CString AFXAPI GXFormatText(const CGXStyle& style, LPCTSTR pszValue = NULL, unsigned nValueType = GX_VT_STRING, CGXGridCore* pGrid = NULL, CGXControl* pControl = NULL);
int  AFXAPI GXDrawRotatedText(CDC* pDC, LPCTSTR lpszString, int nCount, CRect rect, UINT nFormat, LONG lfOrientation, LPRECT lpRectClip = NULL);

void AFXAPI _GXDrawSunkenBorders(CDC* pDC, CRect& rc, BOOL bBorder, BOOL bClientEdge);
BOOL AFXAPI GXDeval(LPCTSTR s, double *d, unsigned* pImportFormat = NULL, unsigned* pImportPlaces = NULL);

// Useful drawing functions ... these exist in the MFC from version 3 onwards.
#ifdef WIN32

#define GXFillSolidRect1(dc, rect, color) \
		(dc)->FillSolidRect(rect, color)
		
#define GXFillSolidRect2(dc, x, y, cx, cy, color) \
		(dc)->FillSolidRect(x, y, cx, cy, color)
		
#define GXDraw3dRect1(dc, rect, color1, color2) \
		(dc)->Draw3dRect(rect, color1, color2)
		
#define GXDraw3dRect2(dc, x, y, cx, cy, color1, color2) \
		(dc)->Draw3dRect(x, y, cx, cy, color1, color2)

#else // WIN32

extern void AFXAPI GXFillSolidRect1(CDC* pDC, LPCRECT lpRect, COLORREF color);
extern void AFXAPI GXFillSolidRect2(CDC* pDC, int x, int y, int cx, int cy, COLORREF color);
extern void AFXAPI GXDraw3dRect1(CDC* pDC, LPCRECT lpRect, COLORREF color1, COLORREF color2);
extern void AFXAPI GXDraw3dRect2(CDC* pDC, int x, int y, int cx, int cy, COLORREF color1,
						COLORREF color2);  
						
#endif // WIN32

#if(WINVER < 0x0400)
/* 3D border styles */
#define BDR_RAISEDOUTER 0x0001
#define BDR_SUNKENOUTER 0x0002
#define BDR_RAISEDINNER 0x0004
#define BDR_SUNKENINNER 0x0008

#define BDR_OUTER       0x0003
#define BDR_INNER       0x000c
#define BDR_RAISED      0x0005
#define BDR_SUNKEN      0x000a


#define EDGE_RAISED     (BDR_RAISEDOUTER | BDR_RAISEDINNER)
#define EDGE_SUNKEN     (BDR_SUNKENOUTER | BDR_SUNKENINNER)
#define EDGE_ETCHED     (BDR_SUNKENOUTER | BDR_RAISEDINNER)
#define EDGE_BUMP       (BDR_RAISEDOUTER | BDR_SUNKENINNER)
#endif

void AFXAPI GXDrawEdge(CDC* pDC, CRect rect, UINT nEdge, BOOL bAdjust = FALSE);
void AFXAPI GXDrawFocusText(CDC* pDC, CRect rect, BOOL bFocus, LPCTSTR lpszString, UINT nFormat = DT_CENTER);


/////////////////////////////////////////////////////////////////////////////////
// CGXDIB  : Device independant bitmaps

class CGXDIB : public CObject
{
	DECLARE_DYNCREATE(CGXDIB)
public:

// Attributes
	HANDLE m_hbm;
	DWORD m_dwColors;
	int m_nWidth;
	int m_nHeight;
	BOOL m_bGDIObject;

	BOOL Attach(HANDLE hObject);
	HANDLE Detach();
	HANDLE GetSafeHandle() const;
	DWORD GetColorCount();
	CSize GetSize();

// Constructors
	CGXDIB();
	BOOL LoadDIB(LPCTSTR lpszResourceName);
	BOOL LoadDIB(UINT nIDResource);

// Operations
	// clean up
	void DestroyDIB();

	enum StretchFlags
	{
		none = 0,
		asymmetric = 1,
		symmetric = 2
	};

	// drawing
	void Draw(CDC* pDC, LPRECT lpRect, int nStretchFlags = none, UINT ntAlign = DT_TOP|DT_LEFT, LPRECT lpSrc = NULL);

	static void AFXAPI Draw(CDC* pDC, HANDLE hbm, LPRECT lpRect, int nStretchFlags = none, UINT ntAlign = DT_TOP|DT_LEFT, LPRECT lpSrc = NULL);

// Implementation
public:
	virtual ~CGXDIB();
};

/////////////////////////////////////////////////////////////////////////////////
// CGXDIBPool : Collection of DIBS

class CGXDIBPool : public CObject
{
	DECLARE_DYNAMIC(CGXDIBPool)
public:

// Attributes
	CMapStringToPtr  m_mapDIBHandles;

// Constructors
	CGXDIBPool();

// Operations
	virtual HANDLE LookupOrCreateDIB(const CString& strValue);
	void EmptyPool();

	virtual LPCTSTR GetResourceString(const CString& strValue, CString& strResource);
	virtual HANDLE LoadDIB(const CString& strValue, LPCTSTR pszResourceString);
	virtual void CreateValueString(UINT nID, CString& strRet);
	virtual void CreateValueString(const CString& strResourceName, CString& strRet);

// Implementation
public:
	virtual ~CGXDIBPool();
};

//////////////////////////////////////////////////////////////////////////////////////
// CGXPrintDevice: printer settings

class CGXPrintDeviceImp;

class CGXPrintDevice: public CObject
{
	DECLARE_SERIAL(CGXPrintDevice)

//  Data
protected:
	HGLOBAL         m_hDevMode;
	HGLOBAL         m_hDevNames;
	HDC             m_hPrintDC;
	CGXAbstractPrintDeviceImp* m_pPrintDeviceImp;

//  Constructor/destructor
public:
	CGXPrintDevice();
	CGXPrintDevice(const CGXPrintDevice&);
	CGXPrintDevice& operator=(const CGXPrintDevice&);
	virtual ~CGXPrintDevice();
	void Serialize(CArchive& ar);
	static void AFXAPI ImplementPrintDevice();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// device handles
public:
	// Create and destroy printer device objects
	void CreateDeviceHandles(LPDEVNAMES pDevnames, DWORD nSizeDevnames, LPDEVMODE pDevmode, DWORD nSizeDevmode);
	void CreateDeviceHandles(HGLOBAL hDN, HGLOBAL hDM);

	void DestroyDeviceHandles();

	// Compare printer device objects
	BOOL CompareDeviceHandles(LPDEVNAMES pDevnames, DWORD nSizeDevnames, LPDEVMODE pDevmode, DWORD nSizeDevmode);
	BOOL CompareDeviceHandles(HGLOBAL hDN, HGLOBAL hDM);

	// Copy printer device objects
	void CopyDeviceHandles(HGLOBAL& hDN, HGLOBAL& hDM);

	// if printer device objects do not yet exist, create and initialize them with defaults,
	void NeedDeviceHandles();

	// get information about print device
	virtual HDC GetPrintDC();
	virtual void ResetPrintDC();

	// get buffers with device info,
	// !!! You must delete these buffers after usage
	void GetDeviceInfo(LPDEVNAMES& pDevnames, DWORD &nSizeDevnames, LPDEVMODE& pDevmode, DWORD& nSizeDevmode);

	void GetDeviceInfo(HGLOBAL hDN, HGLOBAL hDM, LPDEVNAMES& pDevnames, DWORD &nSizeDevnames, LPDEVMODE& pDevmode, DWORD& nSizeDevmode);

	// load default settings
	void GetDefaults();

	friend class CGXPrintDeviceImp;
};


/////////////////////////////////////////////////////////////////////////////
// CGXWaitCursor: hourglass wrapper

struct CGXWaitCursor
{
// Construction/Destruction
	CGXWaitCursor();
	~CGXWaitCursor();

// Operations
	void Restore();
};

/////////////////////////////////////////////////////////////////////////////
// class CGXLongOperation

const int MAXLEVEL = 64;

class CGXLongOperation
{
public:
// Construction/Destruction
	CGXLongOperation();
	~CGXLongOperation();

	// static Data
	static void AFXAPI SetAbortString(LPCTSTR s);  // Text to be displayed in abort-dialog
	static void AFXAPI SetAbortString(UINT nID);

	static void AFXAPI SetDefaultCancelText(LPCTSTR s);
	static void AFXAPI SetDefaulDoneText(LPCTSTR s);
	static void AFXAPI SetDefaultStatusText(LPCTSTR s);

	static void AFXAPI SetTicksFirstTime(DWORD dw);
	static void AFXAPI SetTicksContinued(DWORD dw);

	static void AFXAPI SetFrameWnd(CWnd* pWnd);

	static int  AFXAPI GetCurrentLevel();          // level of operation
	static BOOL AFXAPI GetLockedState();           // locked state indicates not to update the status bar
	static BOOL AFXAPI GetWaitCursorState();       // Long operations will display a waitcursor
	static BOOL AFXAPI GetAbortState();            // User pressed <ESC>-Key
	static BOOL AFXAPI GetAbortConfirmedState();   // User confirmed aborting in abort-dialog
	static BOOL AFXAPI GetRollbackConfirmedState();// User confirmed rollback in abort-dialog

	static void AFXAPI SetPercentDone(int nPercent);

	static void AFXAPI ImplementLongOperation();

	// Status text for current operation
	LPCTSTR GetStatusText() const;
	void  SetStatusText(LPCTSTR s, BOOL bCopyBuffer = TRUE);
	void  SetStatusText(UINT nID);
	void  FreeStatusText();
			// deletes the status text for the current level

	void  SetCanRollback(BOOL bCanRollback);// Can the user rollback the operation?
	void  SetCanAbort(BOOL bCanAbort);      // Can the user abort the operation?

	static void  AFXAPI SetLockedState(BOOL bLocked = TRUE);
		// locked state indicates not to update the status bar in higher operation levels

	// Operations
	BOOL NeedMessages();            // Test, if messages should be processed
	BOOL DoMessages(BOOL& bAbort);  // Process messages and check if user aborted
	BOOL DoMessages();  // simply process messages
		// returns TRUE, if messages have been processed

	void SetUpdateStatusBar(BOOL b);
		// specifies if a WM_SETMESSAGESTRING should be
		// send to the status bar automatically

	void SetResetStatusBar(BOOL b);
		// specifies if the status bar should be
		// cleared when the operation is finished

	// Ticks
	DWORD GetTickCount() const;
#if !defined(_AFXDLL) && !defined(_WINDLL)
	CString GetStrFTime(LPTSTR f) const;
#endif

private:
	// current operation-level
	DWORD m_nTickStart;             // start-time
	DWORD m_nLastTick;              // last time processing messages

	LPCTSTR m_pszStatusText;    // Text to be displayed in status line

	BOOL    m_bResetStatusBar;    // automaticaly reset status bar
	BOOL    m_bUpdateStatusBar;   // automaticaly update status bar

	// helper methods
private:
	void ProcessMessages();

	friend class CGXLongOperationImp;
};

/////////////////////////////////////////////////////////////////////////////
// Inline function declarations

#ifdef _GX_ENABLE_INLINES
#include "grid\gxext.inl"
#endif

/////////////////////////////////////////////////////////////////////////////

//
// GridMFC extension DLL
// reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

//

#endif // _GXEXT_H_
