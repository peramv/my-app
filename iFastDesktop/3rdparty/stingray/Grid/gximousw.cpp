///////////////////////////////////////////////////////////////////////////////
// gximousw.cpp : implementation of the CGXMouseWheelPlugin class
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
#include "grid\gxresrc.h"

#ifdef _GXDLL
#undef AFXAPI_DATA
#define AFXAPI_DATA __based(__segname("_DATA"))
#endif

#include "grid\gximouse.h"

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// determine number of elements in an array (not bytes)
#define _gxcountof(array) (sizeof(array)/sizeof(array[0]))

// GXGetMouseScrollLines is copied from the MFC CScrollView code. 
#if _MFC_VER >= 0x0421

UINT AFXAPI GXGetMouseScrollLines(BOOL bForceFresh /* = FALSE */)
{
	// if we've already got it and we're not refreshing,
	// return what we've already got

	static BOOL bGotScrollLines = FALSE;
	static UINT uCachedScrollLines = 0;

	if (!bForceFresh && bGotScrollLines)
		return uCachedScrollLines;

	// see if we can find the mouse window

	bGotScrollLines = TRUE;

	static UINT msgGetScrollLines = 0;
	static WORD nRegisteredMessage = 0;

	if (nRegisteredMessage == 0)
	{
		msgGetScrollLines = ::RegisterWindowMessage(MSH_SCROLL_LINES);
		if (msgGetScrollLines == 0)
			nRegisteredMessage = 1;     // couldn't register!  never try again
		else
			nRegisteredMessage = 2;     // it worked: use it
	}

	if (nRegisteredMessage == 2)
	{
		HWND hwMouseWheel = NULL;
		hwMouseWheel = FindWindow(MSH_WHEELMODULE_CLASS, MSH_WHEELMODULE_TITLE);
		if (hwMouseWheel && msgGetScrollLines)
		{
			uCachedScrollLines = (UINT)
				::SendMessage(hwMouseWheel, msgGetScrollLines, 0, 0);
			return uCachedScrollLines;
		}
	}

	// couldn't use the window -- try system settings

	OSVERSIONINFO ver;
	memset(&ver, 0, sizeof(ver));
	ver.dwOSVersionInfoSize = sizeof(ver);

	uCachedScrollLines = 3; // reasonable default
	if (!::GetVersionEx(&ver))
		return uCachedScrollLines;

	if ((ver.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS ||
		  ver.dwPlatformId == VER_PLATFORM_WIN32_NT)
		&& ver.dwMajorVersion < 4)
	{
		HKEY hKey;
		if (RegOpenKeyEx(HKEY_CURRENT_USER,  _T("Control Panel\\Desktop"),
				0, KEY_QUERY_VALUE, &hKey) == ERROR_SUCCESS)
		{
			TCHAR szData[128];
			DWORD dwKeyDataType;
			DWORD dwDataBufSize = _gxcountof(szData);

			if (RegQueryValueEx(hKey, _T("WheelScrollLines"), NULL, &dwKeyDataType,
					(LPBYTE) &szData, &dwDataBufSize) == ERROR_SUCCESS)
			{
				uCachedScrollLines = _tcstoul(szData, NULL, 10);
			}
			RegCloseKey(hKey);
		}
	}
	else if (ver.dwPlatformId == VER_PLATFORM_WIN32_NT && ver.dwMajorVersion >= 4)
	{
		::SystemParametersInfo(SPI_GETWHEELSCROLLLINES, 0, &uCachedScrollLines, 0);
	}

	return uCachedScrollLines;
}

#endif


/////////////////////////////////////////////////////////////////////////////
// CGXIntelliMousePlugin

IMPLEMENT_DYNAMIC(CGXMouseWheelPlugin, CGXPluginComponent)

BEGIN_MESSAGE_MAP(CGXMouseWheelPlugin, CGXPluginComponent)
	//{{AFX_MSG_MAP(CGXMouseWheelPlugin)
	//}}AFX_MSG_MAP
	// Standard printing commands
#if _MFC_VER >= 0x0421
	ON_WM_MOUSEWHEEL()
	ON_MESSAGE(WM_SETTINGCHANGE, OnSettingChange)
#endif
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGXMouseWheelPlugin construction/destruction

CGXMouseWheelPlugin::CGXMouseWheelPlugin()
{
}

CGXMouseWheelPlugin::~CGXMouseWheelPlugin()
{
}

/////////////////////////////////////////////////////////////////////////////
// CGXIntelliMousePlugin diagnostics

#ifdef _DEBUG
void CGXMouseWheelPlugin::AssertValid() const
{
	CGXPluginComponent::AssertValid();
}

void CGXMouseWheelPlugin::Dump(CDumpContext& dc) const
{
	CGXPluginComponent::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGXMouseWheelPlugin message handlers

#if _MFC_VER >= 0x0421

BOOL CGXMouseWheelPlugin::OnMouseWheel(UINT nFlags, short zDelta, CPoint /*point*/)
{
	// only this plugin should handle WM_MOUSEWHEEL message
	m_bExitMesssage = TRUE;

	if (nFlags == MK_CONTROL)
	{
		int zoom = OnIMouseGetZoom();

		if (zoom == 0)
			return FALSE;	// zooming not supported
		
		if (zDelta < 0 && zoom > 50)
			OnIMouseSetZoom(zoom-10);
		else if (zDelta > 0 && zoom < 200)
			OnIMouseSetZoom(zoom+10);
	}
	else if (nFlags == 0 || nFlags == MK_SHIFT)
	{
		if (zDelta == 0)
			return FALSE;

		DWORD dwStyle = GetStyle();
		CWnd* pWnd = CWnd::FromHandle(m_hWnd);
		CScrollBar* pBar = pWnd->GetScrollBarCtrl(SB_VERT);
		bool bHasVertBar = ((pBar != NULL) && pBar->IsWindowEnabled()) ||
						(dwStyle & WS_VSCROLL);

		pBar = pWnd->GetScrollBarCtrl(SB_HORZ);
		bool bHasHorzBar = ((pBar != NULL) && pBar->IsWindowEnabled()) ||
						(dwStyle & WS_HSCROLL);

		UINT uWheelScrollLines = GXGetMouseScrollLines();
		int nToScroll = abs(::MulDiv(-zDelta, uWheelScrollLines, WHEEL_DELTA));

		// Scroll horizontal if SHIFT is pressed or no vertical scrollbar
		if (bHasHorzBar && (nFlags == MK_SHIFT || !bHasVertBar))
		{
			if (uWheelScrollLines == WHEEL_PAGESCROLL)
			{
				if (zDelta > 0)
					OnIMouseHScroll(SB_PAGEUP, 1);
				else 
					OnIMouseHScroll(SB_PAGEDOWN, 1);
			}
			else
			{
				if (nToScroll == 0)
					return FALSE;

				if (zDelta > 0)
					OnIMouseHScroll(SB_LINEUP, nToScroll);
				else 
					OnIMouseHScroll(SB_LINEDOWN, nToScroll);
			}
		}
		else // scroll vertically
		{
			if (uWheelScrollLines == WHEEL_PAGESCROLL)
			{
				if (zDelta > 0)
					OnIMouseVScroll(SB_PAGEUP, 1);
				else 
					OnIMouseVScroll(SB_PAGEDOWN, 1);
			}
			else
			{
				if (nToScroll == 0)
					return FALSE;

				if (zDelta > 0)
					OnIMouseVScroll(SB_LINEUP, nToScroll);
				else 
					OnIMouseVScroll(SB_LINEDOWN, nToScroll);
			}
		}
	}
	else
		return FALSE;

	return TRUE;
}

//////////////////
// User changed system settings (possibly Wheel mouse).
// Reload  MouseWheel paramerters.
//
LRESULT CGXMouseWheelPlugin::OnSettingChange(WPARAM, LPARAM)
{
	GXGetMouseScrollLines(TRUE);
	return 0;
}

#endif

/////////////////////////////////////////////////////////////////////////////////////

// Let's send a window messages as default but you might
// also subclass CGXIntelliMousePlugin and override SetZoom,
// GetZoom etc.

int CGXMouseWheelPlugin::OnIMouseGetZoom()
{
	return (int) SendMessage(WM_GX_IMOUSE_GETZOOM, 0, 0);
}

void CGXMouseWheelPlugin::OnIMouseSetZoom(int nZoom)
{
	SendMessage(WM_GX_IMOUSE_SETZOOM, (WPARAM) nZoom, 0);
}

void CGXMouseWheelPlugin::OnIMouseVScroll(UINT nSBCode, UINT nScroll)
{
	// Call the virtual GetScrollBarCtrl method for the
	// original window
	CWnd* pWnd = CWnd::FromHandle(m_hWnd);
	CScrollBar* pBar = pWnd->GetScrollBarCtrl(SB_VERT);

	CSplitterWnd* pSplitter = (CSplitterWnd*) GetParent();
	if (pBar && pSplitter->IsKindOf(RUNTIME_CLASS(CSplitterWnd)))
		pWnd = pSplitter;
                                                                       
#if _MFC_VER >= 0x0300                                                                       
	while (nScroll-- > 0)
		pWnd->SendMessage(WM_VSCROLL, MAKEWPARAM(nSBCode, 0), (LPARAM) pBar->GetSafeHwnd());
	pWnd->SendMessage(WM_VSCROLL, MAKEWPARAM(SB_ENDSCROLL, 0), (LPARAM) pBar->GetSafeHwnd());
#else
	while (nScroll-- > 0)
		pWnd->SendMessage(WM_VSCROLL, (WPARAM) nSBCode, MAKELONG(0, pBar->GetSafeHwnd()));
	pWnd->SendMessage(WM_VSCROLL, (WPARAM) SB_ENDSCROLL, MAKELONG(0, pBar->GetSafeHwnd()));
#endif
}

void CGXMouseWheelPlugin::OnIMouseHScroll(UINT nSBCode, UINT nScroll)
{
	// Call the virtual GetScrollBarCtrl method for the
	// original window
	CWnd* pWnd = CWnd::FromHandle(m_hWnd);
	CScrollBar* pBar = pWnd->GetScrollBarCtrl(SB_HORZ);

	CSplitterWnd* pSplitter = (CSplitterWnd*) GetParent();
	if (pBar && pSplitter->IsKindOf(RUNTIME_CLASS(CSplitterWnd)))
		pWnd = pSplitter;

#if _MFC_VER >= 0x0300                                                                       
	while (nScroll-- > 0)
		pWnd->SendMessage(WM_HSCROLL, MAKEWPARAM(nSBCode, 0), (LPARAM) pBar->GetSafeHwnd());
	pWnd->SendMessage(WM_HSCROLL, MAKEWPARAM(SB_ENDSCROLL, 0), (LPARAM) pBar->GetSafeHwnd());
#else
	while (nScroll-- > 0)
		pWnd->SendMessage(WM_HSCROLL, (WPARAM) nSBCode, MAKELONG(0, pBar->GetSafeHwnd()));
	pWnd->SendMessage(WM_HSCROLL, (WPARAM) SB_ENDSCROLL, MAKELONG(0, pBar->GetSafeHwnd()));
#endif
}

