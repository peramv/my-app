///////////////////////////////////////////////////////////////////////////////
// gxscrltp.cpp : implementation of the CGXScrollTip class
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
// Multi-monitor support
#include <multimon.h>

#if _MFC_VER >= 0x0400

#include "grid\gxproc.h"
#include "grid\gxscrltp.h"

//FOUNDATION_GLOBAL_FUNC_API(HWND) RWGetSafeHwnd();

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXSCRLTP")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif


struct GX_SCROLLTIP_STATE: public CGXNoTrackObject
{
	CString  m_strWndClass;  // class name
	CFont    m_fntFont;      // font to use
	CBrush   m_brBackground; // brush to use for background
	CSize    m_sizeVScroll;  // SM_CYVSCROLL, SM_CXVSCROLL metrics
	CSize    m_sizeHScroll;  // SM_CYHSCROLL, SM_CXHSCROLL metrics
	CSize    m_sizeThumb;    // SM_CXHTHUMB, SM_CYVTHUMB metrics

	GX_SCROLLTIP_STATE();
};                               


GX_PROCESS_LOCAL(GX_SCROLLTIP_STATE, _gxScrollTipState)
 
GX_SCROLLTIP_STATE::GX_SCROLLTIP_STATE()
{
}

/////////////////////////////////////////////////////////////////////////////
// CGXScrollTip

CGXScrollTip::CGXScrollTip()
{
}

CGXScrollTip::~CGXScrollTip()
{
	if (m_hWnd != NULL)
	{
		DestroyWindow();            // destroy the window
	}
}

BEGIN_MESSAGE_MAP(CGXScrollTip, CWnd)
	//{{AFX_MSG_MAP(CGXScrollTip)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CGXScrollTip message handlers

//---------------------------------------------------------------------------
BOOL CGXScrollTip::HandleThumbTrackMessage(CWnd * pParent, int nBar, LPCTSTR pszText, CScrollBar * pBar)
// Handles the thumbtrack message. ie moves the window to the slider position,
// and sets the window text
//---------------------------------------------------------------------------
{
	// workout the size of the text
	CSize sizeText;
	{
	CClientDC dc(this);
	CFont * pOldFont = dc.SelectObject(CFont::FromHandle(m_hFont));
	// Calculate the widht and height
	CRect	r(0,0,0,0);
	dc.DrawText(pszText, &r, DT_CALCRECT | DT_NOCLIP | DT_CENTER | DT_NOPREFIX);
	sizeText = CSize(r.Width(), r.Height());
	dc.SelectObject(pOldFont);
	}               // release client DC
	sizeText.cx += 6;           // allow space for a border
	sizeText.cy += 6;

	// work-out where to place the slider
	CPoint pt = GetSliderPositionHelper(pParent, nBar, pBar, sizeText);

	// Multi-monitor support
	CRect rectWorkArea;
	HMONITOR hMonitor = MonitorFromPoint(pt, MONITOR_DEFAULTTONEAREST);
	ASSERT(hMonitor != NULL);
	MONITORINFO monitorInfo = { sizeof(MONITORINFO) };
	VERIFY(GetMonitorInfo(hMonitor, &monitorInfo));
	rectWorkArea = monitorInfo.rcWork;
	// now clip to size of screen
	pt.x = min(pt.x, (rectWorkArea.BottomRight().x - sizeText.cx));
	pt.y = min(pt.y, (rectWorkArea.BottomRight().y - sizeText.cy));

	CWnd* pWnd = GetDesktopWindow();
	if (m_dcBackground.GetSafeHdc())
		RestoreBackground(this);

	// Set the window text, and move the window
	CRect rect(pt.x, pt.y, pt.x+sizeText.cx, pt.y+sizeText.cy);
	CRect rcUpdate;
	if (pWnd->GetUpdateRect(&rcUpdate)
		&& rcUpdate.IntersectRect(rcUpdate, rect))
		pWnd->UpdateWindow();
	
	rect -= rect.TopLeft();
	SetWindowPos(NULL, pt.x, pt.y, sizeText.cx, sizeText.cy, SWP_NOACTIVATE | SWP_NOREDRAW) ;
	SaveBackground(this, rect);
	SetWindowText(pszText);
	Invalidate(FALSE);
	ShowWindow(SW_SHOW);
	UpdateWindow();             // force update of window
	return TRUE;
}

//---------------------------------------------------------------------------
BOOL CGXScrollTip::HandleScrollMessage(CWnd * pParent, UINT nSBCode, int nBar, LPCTSTR pszText, CScrollBar * pBar)
// lazy message - does all the tooltip stuff for you.
//---------------------------------------------------------------------------
{
	switch(nSBCode)
	{
	case SB_THUMBTRACK:
		{
			// create the window if neccessary
			if (m_hWnd == NULL && !Create(pParent))
				return FALSE;

			HandleThumbTrackMessage(pParent, nBar, pszText, pBar);
			break;
		}

	case SB_THUMBPOSITION:
		{
			if (m_hWnd != NULL)
			{
				RestoreBackground(this);
				SetWindowPos(NULL, 0,0,0,0, SWP_NOREDRAW);
				DestroyWindow();            // destroy the window
			}
			break;
		}
	}
	return TRUE;
}

void CGXScrollTip::SaveBackground(CWnd* pWnd, const CRect& rect)
{
	CWindowDC dc(pWnd);

	m_rcBackground = rect;

	m_dcBackground.CreateCompatibleDC(&dc);
	m_bmBackground.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	m_hbmBackgroundOld   = (HBITMAP) m_dcBackground.SelectObject(&m_bmBackground)->GetSafeHandle();
	
	// Save the existing background so that we can later hide the window again
	m_dcBackground.BitBlt(0, 0, rect.Width(), rect.Height(), &dc, rect.left, rect.top, SRCCOPY);
}

void CGXScrollTip::RestoreBackground(CWnd* pWnd)
{
	if (m_dcBackground.GetSafeHdc())
	{
		CWindowDC dc(pWnd);

		CRect& rect = m_rcBackground;

		dc.BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &m_dcBackground, 0, 0,
		  SRCCOPY);

		m_dcBackground.SelectObject(CBitmap::FromHandle(m_hbmBackgroundOld));

		m_bmBackground.DeleteObject();

		m_dcBackground.DeleteDC();

		dc.BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &m_dcBackground, 0, 0,
			SRCCOPY);
	}
}

#ifndef WS_EX_TOOLWINDOW
#define WS_EX_TOOLWINDOW (GXGetAppData()->bWin4?0x00000080L:0L)
#endif

BOOL CGXScrollTip::Create(CWnd * pParent)
{
	pParent; 

	_gxScrollTipState->m_sizeVScroll.cx = GetSystemMetrics(SM_CXVSCROLL);
	_gxScrollTipState->m_sizeVScroll.cy = GetSystemMetrics(SM_CYVSCROLL);
	_gxScrollTipState->m_sizeHScroll.cx = GetSystemMetrics(SM_CXHSCROLL);
	_gxScrollTipState->m_sizeHScroll.cy = GetSystemMetrics(SM_CYHSCROLL);
	_gxScrollTipState->m_sizeThumb.cx = GetSystemMetrics(SM_CXHTHUMB);
	_gxScrollTipState->m_sizeThumb.cy = GetSystemMetrics(SM_CYVTHUMB);

	// register a classname for this window...
	if (_gxScrollTipState->m_strWndClass.IsEmpty())
	{
		_gxScrollTipState->m_strWndClass = AfxRegisterWndClass(/*CS_BYTEALIGNCLIENT |*/ CS_SAVEBITS | CS_HREDRAW | CS_VREDRAW,
							0 ,
							NULL);  // Use a NULL brush - we draw the background ourselves
		// for vertical-only scroll bars, we could use CS_BYTEALIGNCLIENT, which results
		// in marginally faster drawing, but not much use for following horizonals, as we'd
		// jump in byte-sized chunks


		// we're we successful?
		if (_gxScrollTipState->m_strWndClass.IsEmpty())
			return FALSE;  // return failed


		VERIFY(_gxScrollTipState->m_brBackground.CreateSolidBrush((::GetSysColor(COLOR_INFOBK))));
	}


	// create the bubble window and set the created flag
	CRect rect;
	rect.SetRectEmpty();

	BOOL bCreated = CreateEx(WS_EX_TOOLWINDOW, NULL/*_gxScrollTipState->m_strWndClass*/, NULL, WS_CHILD,
							   rect.left, rect.top, rect.right, rect.bottom,
							   ::GetDesktopWindow(),
							   (HMENU) NULL);

	if (!bCreated)
		return FALSE;

	// create a suitable font to use...
	if(_gxScrollTipState->m_fntFont.GetSafeHandle() == NULL)
	{
		CClientDC dc(this);  // used to calculate the font size
		LOGFONT        lf;
		memset(&lf, 0, sizeof(LOGFONT));

		lf.lfHeight = -::MulDiv(-10, dc.GetDeviceCaps(LOGPIXELSY), 72);
		lf.lfCharSet = ANSI_CHARSET;
		lf.lfQuality = DEFAULT_QUALITY;
		lf.lfClipPrecision = CLIP_LH_ANGLES | CLIP_STROKE_PRECIS;
		lf.lfPitchAndFamily = FF_SWISS;

		if (!_gxScrollTipState->m_fntFont.CreateFontIndirect(&lf))
			return FALSE;
	}
	m_hFont = HFONT(_gxScrollTipState->m_fntFont);             // current font = this default one

	// success
	return TRUE;
}


//---------------------------------------------------------------------------
void CGXScrollTip::OnPaint()
//---------------------------------------------------------------------------
{
	CPaintDC dc(this); // device context for painting

	// paint the window text, centred in the window
	CRect rect;
	GetClientRect(rect);

	CFont *pOldFont = dc.SelectObject(CFont::FromHandle(m_hFont));

	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(::GetSysColor(COLOR_INFOTEXT));

	// draw the text
	CString strText;
	GetWindowText(strText);

	HTHEME lhTheme = NULL;
	// Note: Calling dc.GetWindow() will return an invalid handle.
	// Instead call AfxGetMainWnd()->GetSafeHwnd().
	if (RWIsAppThemed() && RWIsThemeActive())
		lhTheme = RWOpenThemeData (RWGetSafeHwnd(), L"TOOLTIP");
	
	if (lhTheme)
	{		
		RWDrawThemeBackground( lhTheme, dc.GetSafeHdc(), TTP_STANDARD, TTSS_NORMAL, &rect, 0 );	
		RWCloseThemeData( lhTheme );
	}
	else
	{
		dc.FillRect(&rect, &_gxScrollTipState->m_brBackground);                // erase as close to draw as possible
	}
	
	CRect r = rect;
	r.top++;
	r.left++;
	dc.DrawText(strText, &r, DT_NOCLIP | DT_CENTER | DT_NOPREFIX); // know it'll fit

	CBrush br;
	br.CreateSolidBrush(RGB(0,0,0));
	dc.FrameRect(&rect, &br);                // erase as close to draw as possible

	// clean up the DC
	dc.SelectObject(pOldFont);
}


//---------------------------------------------------------------------------
CPoint AFXAPI CGXScrollTip::GetSliderPositionHelper(CWnd * pParent, int nBar,
											  CScrollBar * pBar,
											  CSize sizeText)
// returns suitable position for centre of the slider for a scrollbar
//---------------------------------------------------------------------------
{
	CPoint pt;
	CWnd * pWnd;
	SCROLLINFO SI;
	CRect rcWnd;
	int nWidth, nPos;

	if (pBar == NULL)
	{
		pParent->GetScrollInfo(nBar, &SI, SIF_TRACKPOS | SIF_PAGE | SIF_RANGE);
		pWnd = pParent;
	}
	else
	{
		nBar = ((pBar->GetStyle() & SBS_VERT) ? SB_VERT : SB_HORZ);
		pBar->GetScrollInfo(&SI, SIF_TRACKPOS | SIF_PAGE | SIF_RANGE);
		pWnd = pBar;
	}

	pWnd->GetClientRect(&rcWnd);
	if (SI.nMin == SI.nMax)
		return FALSE;           // NULL range - prevent divide by zero later

	if (nBar == SB_VERT)
	{
		nWidth = rcWnd.Height() - _gxScrollTipState->m_sizeVScroll.cy * 2;
	}
	else
	{
		nWidth = rcWnd.Width() - _gxScrollTipState->m_sizeHScroll.cx * 2;
	}

	if (SI.nPage == 0)
	{
		nWidth -= (nBar == SB_VERT ? _gxScrollTipState->m_sizeThumb.cy : _gxScrollTipState->m_sizeThumb.cx);
	}

	nPos = (SI.nTrackPos - SI.nMin + (SI.nPage / 2)) * nWidth / (SI.nMax - SI.nMin);

	if (nBar == SB_VERT)
	{
		pt.y = nPos + _gxScrollTipState->m_sizeVScroll.cy - sizeText.cy / 2;
		pt.x = rcWnd.Width();
		if (pBar == NULL)
			pt.x += _gxScrollTipState->m_sizeVScroll.cx;
		if (SI.nPage == 0)
			pt.y += _gxScrollTipState->m_sizeThumb.cy / 2;
	}
	else
	{
		pt.x = nPos + _gxScrollTipState->m_sizeHScroll.cx - sizeText.cx / 2;
		pt.y = rcWnd.Height();
		if (pBar == NULL)
			pt.y += _gxScrollTipState->m_sizeHScroll.cy;
		if (SI.nPage == 0)
			pt.x += _gxScrollTipState->m_sizeThumb.cx / 2;
	}
	pWnd->ClientToScreen(&pt);
	return pt;
}

#endif // _MFC_VER
