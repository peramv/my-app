///////////////////////////////////////////////////////////////////////////////
// gxinfwnd.cpp : implementation of CGXRecordInfoWnd class
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

#ifdef _GXDLL
#undef AFXAPI_DATA
#define AFXAPI_DATA __based(__segname("_DATA"))
#endif

// Headers

#ifndef _GXRESRC_H_
#include "grid\gxresrc.h"
#endif

#ifndef _GXINFWND_H_
#include "grid\gxinfwnd.h"
#endif

#ifndef _GXMSG_H_
#include "grid\gxmsg.h"
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXINFBMM")
#endif

//FOUNDATION_GLOBAL_FUNC_API(HWND) RWGetSafeHwnd();

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CGXRecordInfoBeam, CWnd);

// enable use as custom control
GRID_IMPLEMENT_REGISTER(CGXRecordInfoBeam, GX_GLOBALCLASS, 0, 0, 0);




// Colors for Arrows
const COLORREF rgbBlack = RGB(0,0,0);
const COLORREF rgbGrey  = RGB(96,96,96);

const int nExtraSpace = 4;
const UINT gxnIdEditWnd = 27001;

/////////////////////////////////////////////////////////////////////////////
// CGXRecordInfoEdit

CGXRecordInfoEdit::CGXRecordInfoEdit()
{
}

CGXRecordInfoEdit::~CGXRecordInfoEdit()
{
}


BEGIN_MESSAGE_MAP(CGXRecordInfoEdit, CEdit)
	//{{AFX_MSG_MAP(CGXRecordInfoEdit)
	ON_WM_KEYDOWN()
	ON_WM_SETFOCUS()
	ON_WM_GETDLGCODE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CGXRecordInfoEdit message handlers

void CGXRecordInfoEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TRACE1("nChar %d\n", nChar);
	if (nChar == VK_RETURN)
	{
		CGXRecordInfoBeam* pBeam = (CGXRecordInfoBeam*) GetParent();
		ASSERT(pBeam->IsKindOf(RUNTIME_CLASS(CGXRecordInfoBeam)));

		pBeam->Scroll(GX_MOVERECORD_SEEK);
	}
	else
		CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CGXRecordInfoEdit::OnSetFocus(CWnd* pOldWnd)
{
	CEdit::OnSetFocus(pOldWnd);

	SetSel(0, -1);
}

UINT CGXRecordInfoEdit::OnGetDlgCode()
{
	return CEdit::OnGetDlgCode() | DLGC_WANTALLKEYS;
}

/////////////////////////////////////////////////////////////////////////////
// CGXRecordInfoBeam

BEGIN_MESSAGE_MAP(CGXRecordInfoBeam, CWnd)
	//{{AFX_MSG_MAP(CGXRecordInfoBeam)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()	
	ON_WM_LBUTTONUP()
	ON_WM_SETCURSOR()
	ON_WM_CTLCOLOR()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_SYSCOLORCHANGE()
	//}}AFX_MSG_MAP
	ON_WM_WININICHANGE()
END_MESSAGE_MAP()

CGXRecordInfoBeam::CGXRecordInfoBeam()
{
	m_nHeight = GetSystemMetrics(SM_CYHSCROLL);
	m_nButtonWidth = m_nHeight;

	m_nRecordCount = 1;
	m_nCurrentRecord = 1;

	m_pNotifyWnd = NULL;
	m_pFont = NULL;
	m_pWndEdit = NULL;

	m_bBtnDown = FALSE;
	m_bMouseCapture = FALSE;

	m_hcurArrow  = ::LoadCursor(NULL, IDC_ARROW);

	m_nInteriorWidth = 8;

	for (int i = 0; i < 4; i ++) m_bBtnHot[i] = FALSE;
}

#if _MFC_VER < 0x0300
WNDPROC* CGXRecordInfoBeam::GetSuperWndProcAddr()
{
	// Note: it is no longer necessary to override GetSuperWndProcAddr
	//  for each control class with a different WNDCLASS.
	//  This implementation now uses instance data, such that the previous
	//  WNDPROC can be anything.

	static WNDPROC NEAR pfnSuper;
	return &pfnSuper;
}
#endif

BOOL CGXRecordInfoBeam::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	if ( CWnd::Create(_T("GXNDBLCLKSWND"), NULL, dwStyle | WS_CHILD, rect, pParentWnd, nID) )
	{
		CreateFonts();
		SetWindowPos(NULL, 0, 0, 1, m_nHeight,
					SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE);

		UpdateColors();

		return TRUE;
	}

	return FALSE;
}

CGXRecordInfoBeam::~CGXRecordInfoBeam()
{
	DestroyFonts();
	delete m_pWndEdit;
}

void CGXRecordInfoBeam::CreateFonts()
{
	DestroyFonts();

	LOGFONT lf;

	memset(&lf, 0, sizeof(LOGFONT));

	CClientDC dc(this);
	lf.lfHeight = (m_nHeight-2);

	lf.lfCharSet = ANSI_CHARSET;
	lf.lfQuality = DEFAULT_QUALITY;
	lf.lfClipPrecision = CLIP_LH_ANGLES | CLIP_STROKE_PRECIS;
	// QA: 31989 - #if Secure Code Cleanup.
	_tcscpy(lf.lfFaceName, _T("Arial"));

	lf.lfPitchAndFamily = FF_SWISS ;

	// Create the font
	lf.lfWeight = FW_NORMAL;

	m_pFont = new CFont;
	m_pFont->CreateFontIndirect(&lf);

	// Rectangle for "Record: xxx"
	m_rectInterior.SetRect(m_nButtonWidth*2+1,
				   0,
				   m_nInteriorWidth*m_nHeight+1, // 130 ==> orginial value.
				   m_nHeight);
}

void CGXRecordInfoBeam::CreateEditWnd(const RECT& rect)
{
	ASSERT(m_pWndEdit == NULL);

	m_pWndEdit = new CGXRecordInfoEdit;

#ifndef _UNICODE
	m_pWndEdit->CWnd::Create(_T("EDIT"), NULL,
		ES_LEFT | ES_AUTOVSCROLL | ES_MULTILINE | WS_CHILD | WS_VISIBLE,
		rect, this, gxnIdEditWnd, NULL);
#else
	m_pWndEdit->CWnd::Create(_T("GXEDIT"), NULL,
		ES_LEFT | ES_AUTOVSCROLL | ES_MULTILINE | WS_CHILD | WS_VISIBLE,
		rect, this, gxnIdEditWnd, NULL);
#endif

	m_pWndEdit->SetFont(m_pFont);
}

int CGXRecordInfoBeam::GetWidth()
{
	return m_nButtonWidth*2 + m_nHeight*m_nInteriorWidth;
}

void CGXRecordInfoBeam::DestroyFonts()
{
	if (m_pFont)
		delete m_pFont;
}

void CGXRecordInfoBeam::SetNotifyWnd(CWnd* pNotify)
{
	m_pNotifyWnd = pNotify;
}

/////////////////////////////////////////////////////////////////////////////
// CGXRecordInfoBeam Painting

void CGXRecordInfoBeam::OnPaint()
{
	if (m_pFont == NULL)
		CreateFonts();

	CPaintDC dc(this); // device context for painting

	// default font
	CFont* pOldFont = dc.SelectObject(m_pFont);

	int i;
	CRect rect;
	GetClientRect(&rect);

	if (RWIsAppThemed() && RWIsThemeActive())
	{
		GXPatB(&dc, rect, m_rgbFace);
	}	

	// Scroll Buttons
	dc.SelectClipRgn(NULL);
	for (i = 0; i < 4; i++)
		DrawButton(&dc, i, m_bBtnDown && i == m_nBtnDown);

	dc.IntersectClipRect(m_rectInterior);

	// Border at top
	PatB(&dc, rect.left, 0, rect.Width(), 1, GXGetAppData()->bWin4 ? m_rgbFace : rgbBlack);

	// Grey Beam
	PatB(&dc, rect.left, 1, rect.Width(), rect.Height()+1, m_rgbBack);	

	// Record
	rect = m_rectInterior;

	// center vertically
	CSize size = dc.GetTextExtent(_T("t"), 1);
	rect.top += max(m_nHeight+1-size.cy, 0)/2;

	rect.left += nExtraSpace;

	if (m_strRecord.IsEmpty())
		m_strRecord.LoadString(GX_IDS_RECORD);

	dc.DrawText(m_strRecord, m_strRecord.GetLength(), rect, DT_CALCRECT);

	HTHEME lhTheme = NULL;

	// Note: Calling dc.GetWindow() will return an invalid handle. 
	// Instead, call AfxGetMainWnd()->GetSafeHwnd().
	if (RWIsAppThemed() && RWIsThemeActive()) 
		lhTheme = RWOpenThemeData(RWGetSafeHwnd(), L"EDIT" );
	
	if (lhTheme)
	{		
		CRect r (rect.left - nExtraSpace, rect.top, rect.right + nExtraSpace, rect.bottom);
		RWDrawThemeBackground(lhTheme,dc.GetSafeHdc(), EP_EDITTEXT, ETS_READONLY, &r, 0);				
	}

	dc.SetBkMode(TRANSPARENT);
	dc.DrawText(m_strRecord, m_strRecord.GetLength(), rect, DT_SINGLELINE);	

	// Black Border
	PatB(&dc, rect.right + nExtraSpace, 0, 1, m_nHeight, GXGetAppData()->bWin4 ? m_rgbFace : rgbBlack);

	m_rectEdit = CRect(rect.right + 2*nExtraSpace, rect.top, m_rectInterior.right, rect.bottom);
	if (m_pWndEdit == NULL)
		CreateEditWnd(m_rectEdit);

	if (GetFocus() != m_pWndEdit)
	{
		if (m_pWndEdit->IsWindowVisible())
		{
			// Hide the window withour invalidating the window area
			m_pWndEdit->MoveWindow0(FALSE);
			m_pWndEdit->ShowWindow(SW_HIDE);
		}

		CRect rc = m_rectEdit;
		rc.left += 3; // small margin for edit field

		if (lhTheme)
		  RWDrawThemeBackground(lhTheme,dc.GetSafeHdc(), EP_EDITTEXT, ETS_NORMAL, &m_rectEdit, 0);
		
		dc.DrawText(GetCurrentRecordText(), -1, rc, DT_SINGLELINE);
	}
	else
	{
		m_pWndEdit->SetFont(m_pFont);
		if (lhTheme)
		{
			CRect rc = m_rectEdit;				

			rc.InflateRect(1, 1);
			RWDrawThemeBackground(lhTheme,dc.GetSafeHdc(), EP_EDITTEXT, ETS_HOT, &rc, 0);				
		}		
		
		m_pWndEdit->SetWindowPos(NULL, m_rectEdit.left, m_rectEdit.top, m_rectEdit.Width(), m_rectEdit.Height(),
		 SWP_NOREDRAW|SWP_SHOWWINDOW);

		dc.ExcludeClipRect(m_rectEdit);
	}

	// Clean up
	dc.SelectObject(pOldFont);
	if (lhTheme) RWCloseThemeData(lhTheme);	
}

CString CGXRecordInfoBeam::GetCurrentRecordText()
{
	TCHAR s[20];
	wsprintf(s, _T("%ld"), m_nCurrentRecord);

	return s;
}

void CGXRecordInfoBeam::DrawButton(CDC* pDC, int nButton, BOOL bPressed)
{
	int i = nButton;

	CRect rect( i * m_nButtonWidth, 0, (i + 1) * m_nButtonWidth, m_nHeight);
	if (i >= 2)
	{
		rect.left += m_rectInterior.Width()+1;
		rect.right += m_rectInterior.Width()+1;
	}

	HTHEME lhTheme = NULL;

	if (RWIsAppThemed() && RWIsThemeActive())
		lhTheme = RWOpenThemeData (RWGetSafeHwnd(), L"BUTTON");

	if (lhTheme)
	{				
		int iState = bPressed ? PBS_PRESSED : (m_bBtnHot[nButton] ? PBS_HOT : PBS_NORMAL);
		switch(i)
		{
			case GX_MOVERECORD_FIRST:								
			case GX_MOVERECORD_PREV:				
				if (i <= 1 && IsOnFirstRecord()) iState = PBS_DISABLED;			
				break;

			case GX_MOVERECORD_LAST:				
			case GX_MOVERECORD_NEXT:
				if (i >= 2 && IsOnLastRecord()) iState = PBS_DISABLED;						
				break;
		}		
			
		RWDrawThemeBackground( lhTheme, pDC->GetSafeHdc(), BP_PUSHBUTTON, iState, &rect, 0 );		
		RWCloseThemeData(lhTheme);
	}
	else
	{
		DrawBlankButton(pDC, rect.left, rect.top, rect.Width(), rect.Height(), bPressed);

		// Black border
		PatB(pDC, rect.left, rect.bottom-1, rect.Width(), 1, rgbBlack);
	}

	// Draw arrows
	int x, y;

	COLORREF rgb = rgbBlack;    // Black

	CRect rectClient;
	GetClientRect(rectClient);

	if (i <= 1 && IsOnFirstRecord() || i >= 2 && IsOnLastRecord())
		rgb = rgbGrey;

	int cx = m_nHeight > 19 ? 6 : 5;
	int cy = m_nHeight > 19 ? 9 : 7;

	// center the 9-pixel high arrow vertically
	y = rect.top + ((rect.Height() - 9) / 2);
	int y2 = rect.top + ((rect.Height() - cy) / 2);

	// if pressed, image gets moved
	if (bPressed)
		y++;

	switch(i)
	{
	case GX_MOVERECORD_FIRST:
		// Most left
		x = rect.left + ((rect.Width() - cx) / 2) - 1;
		if (bPressed)
			x++;

		PatB(pDC, x, y2, 1, cy, rgb);

	case GX_MOVERECORD_PREV:
		// Left Arrow
		x = rect.left + ((rect.Width() - cx) / 2) - 1;
		if (bPressed)
			x++;

		PatB(pDC, x+2, y+4, 1, 1, rgb);
		PatB(pDC, x+3, y+3, 1, 3, rgb);
		PatB(pDC, x+4, y+2, 1, 5, rgb);
		PatB(pDC, x+5, y+1, 1, 7, rgb);

		if (m_nHeight > 19)
			PatB(pDC, x+6,   y, 1, 9, rgb);
		break;

	case GX_MOVERECORD_LAST:
		// Most Right
		x = rect.right - ((rect.Width() - cx) / 2);
		if (bPressed)
			x++;

		PatB(pDC, x, y2, 1, cy, rgb);

	case GX_MOVERECORD_NEXT:
		// Right Arrow
		x = rect.right - ((rect.Width() - cx) / 2);
		if (bPressed)
			x++;

		PatB(pDC, x-2, y+4, 1, 1, rgb);
		PatB(pDC, x-3, y+3, 1, 3, rgb);
		PatB(pDC, x-4, y+2, 1, 5, rgb);
		PatB(pDC, x-5, y+1, 1, 7, rgb);
		if (m_nHeight > 19)
			PatB(pDC, x-6,   y, 1, 9, rgb);
		break;
	}
}

BOOL CGXRecordInfoBeam::OnEraseBkgnd(CDC* pDC)
{
	// Not erasing the background here avoids flickering!
	pDC; // Unused
	
	// CRect rect;
	// GetClientRect(rect);

	// PatB(pDC, rect.left, 0, rect.Width(), rect.Height(), m_rgbBeam);

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CGXRecordInfoBeam Mouse Actions

// Replacement for SetCapture
// Sends WM_MOUSEMOVE Messages, when a Button is pressed
void CGXRecordInfoBeam::AutoMove(UINT nRefMessage)
{
	MSG   msgLoop;          // dummmy message structure to process incoming
							// messages while autoscrolling.
	CPoint ptCursorPos;

	msgLoop.message = 0;    // forces at least one loop.

	SetCapture();

	DWORD nLastTicks = GetTickCount();
	DWORD nTicksNeeded = 400;

	// Process all messages until the relevant mouse button
	// has been released.
	while (msgLoop.message != nRefMessage) // nRefMessage depends on which button
										// has been used to trigger autoscrolling.
	{
		// Process incoming messages until autoscroll button is released
		if (PeekMessage(&msgLoop, 0, 0, 0, PM_REMOVE))
		{
			if (msgLoop.message != WM_MOUSEMOVE)
			{
				TranslateMessage(&msgLoop);
				DispatchMessage(&msgLoop);
			}
			continue;
		}

		GetCursorPos(&ptCursorPos);
		ScreenToClient(&ptCursorPos);

		if (GetTickCount() - nLastTicks > nTicksNeeded)
		{
			// peridically do OnMouseMove
			OnMouseMove(0, ptCursorPos);
			if (nTicksNeeded > 300)
				nTicksNeeded -= 100;
			else if (nTicksNeeded > 100)
				nTicksNeeded -= 20;
		}
	}

	ReleaseCapture();
}

BOOL CGXRecordInfoBeam::IsOnFirstRecord()
{
	return m_nCurrentRecord == 1;
}

BOOL CGXRecordInfoBeam::IsOnLastRecord()
{
	return m_nCurrentRecord == m_nRecordCount;
}

void CGXRecordInfoBeam::SetCurrentRecord(long nRecord)
{
	m_nCurrentRecord = nRecord;
}

void CGXRecordInfoBeam::SetRecordCount(long nCount)
{
	m_nRecordCount = nCount;
}

long CGXRecordInfoBeam::GetCurrentRecord()
{
	return m_nCurrentRecord;
}

long CGXRecordInfoBeam::GetRecordCount()
{
	return m_nRecordCount;
}

// Button is hit
// 0 = most left, 1 = scroll left, 2 = scroll right, 3 = most right
// if nButton is not -1, it is checked if the mouse has left
// the pressed button, (the button will get unpressed in OnMouseMove)
int CGXRecordInfoBeam::ScrollBtnHit(CPoint point, int nButton /*= -1*/)
{
	if (point.y < 0 || point.y > m_nHeight
		|| m_rectInterior.PtInRect(point)
		|| point.x >= m_rectInterior.right+2*m_nButtonWidth)
		return -1;

	// get Button
	int nBtn = point.x / m_nButtonWidth;

	if (nBtn >= 2)
		nBtn = 2 + (point.x - m_rectInterior.right-1) / m_nButtonWidth;

	CRect rectClient;
	GetClientRect(rectClient);

	if (nBtn <= 1 && IsOnFirstRecord() || nBtn >= 2 && IsOnLastRecord())
		return -1;

	if (nButton != -1 && nBtn != nButton)
		return -1;

	return nBtn;
}

void CGXRecordInfoBeam::Scroll(int nDirection)
{
	long nRecord = 0;

	if (nDirection == GX_MOVERECORD_SEEK)
	{
		CString strText;
		m_pWndEdit->GetWindowText(strText);

		nRecord = _ttol(strText);
	}

	if (m_pNotifyWnd)
		m_pNotifyWnd->SendMessage(WM_GX_MOVERECORD, (WPARAM) nDirection, nRecord);
	else
		GetParent()->SendMessage(WM_GX_MOVERECORD, (WPARAM) nDirection, nRecord);
}

void CGXRecordInfoBeam::OnLButtonDown(UINT nFlags, CPoint point)
{
	if ((m_nBtnDown = ScrollBtnHit(point)) != -1)
	{
		// user clicked into scroll button

		// Scrolling
		CClientDC dc(this);
		DrawButton(&dc, m_nBtnDown, m_bBtnDown = TRUE);

		m_bMouseCapture = TRUE;
		AutoMove(WM_LBUTTONUP); // (SetCapture until WM_LBUTTONUP)

		// Perform scrolling
		Scroll(m_nBtnDown);
	
	}
	else if (m_rectEdit.PtInRect(point))  
	{
		// user clicked into edit field

		// update the field and set focus to it
		m_pWndEdit->SetWindowText(GetCurrentRecordText());
		m_pWndEdit->SetFocus();
		Invalidate();
		UpdateWindow();

		// let edit control track this mouse message
		m_pWndEdit->SendMessage(WM_LBUTTONDOWN, nFlags, MAKELONG(point.x, point.y));
	}

	CWnd::OnLButtonDown(nFlags, point);
}

void CGXRecordInfoBeam::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_bMouseCapture)
	{
		m_bMouseCapture = FALSE;

		if (m_nBtnDown != -1 && m_bBtnDown)
		{
			UpdateWindow();
			CClientDC dc(this);
			for (int i = 0; i < 4; i++)
				DrawButton(&dc, i, FALSE);
		}
	}

	m_bBtnDown = FALSE;

	CWnd::OnLButtonUp(nFlags, point);
}

void CGXRecordInfoBeam::OnMouseMove(UINT /*nFlags*/, CPoint point)
{
	if (!m_rectEdit.PtInRect(point))
		SetCursor(m_hcurArrow);

	// -- Handle Mouse Move
	if (RWIsAppThemed() && RWIsThemeActive())
	{
		UpdateWindow();
		CClientDC dc(this);

		int nBtnOver = ScrollBtnHit(point, -1);
		for (int i = 0; i < 4; i++)
		{
			BOOL bRedraw = (m_bBtnHot[i] && (i != nBtnOver))
			 || (!m_bBtnHot[i] && (i == nBtnOver));

			if (bRedraw)
			{
				m_bBtnHot[i] = (i == nBtnOver) ? TRUE : FALSE;
				DrawButton(&dc, i, FALSE);

				TRACKMOUSEEVENT eventTrack;

				memset( &eventTrack, 0x00, sizeof( eventTrack ) );
			
				eventTrack.cbSize = sizeof( eventTrack );
				eventTrack.dwFlags = TME_LEAVE;
				eventTrack.hwndTrack = m_hWnd;
				eventTrack.dwHoverTime = HOVER_DEFAULT;

				RWTrackMouseEvent( &eventTrack );
			}
		}
	}

	// -- Handle Mouse Move

	if (!m_bMouseCapture)
		return;

	if (m_nBtnDown != -1)
	{
		// Check if mouse has left the button,
		// ScrollBtnHit does scrolling
		BOOL bDraw = FALSE;
		if (ScrollBtnHit(point, m_nBtnDown) == -1)
		{
			bDraw = m_bBtnDown;
			m_bBtnDown = FALSE;
		}
		else
		{
			bDraw = !m_bBtnDown;
			m_bBtnDown = TRUE;
		}

		if (bDraw)
		{
			UpdateWindow();
			CClientDC dc(this);
			for (int i = 0; i < 4; i++)
			{
				DrawButton(&dc, i, i == m_nBtnDown && m_bBtnDown);
			}
		}

		if (m_bBtnDown)
		{
			// Perform scrolling
			Scroll(m_nBtnDown);
		}
	}	
}

BOOL CGXRecordInfoBeam::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	if (RWIsAppThemed() && RWIsThemeActive())
	{
		if( message == WM_MOUSELEAVE )
		{
			for (int i = 0; i < 4; i++)
			{
				if (m_bBtnHot[i])
				{
					UpdateWindow();
					CClientDC dc(this);

					m_bBtnHot[i] = FALSE;
					DrawButton(&dc, i, FALSE);
				}
			}
		}
	}
	
	return CWnd::OnWndMsg( message, wParam, lParam, pResult );
}

BOOL CGXRecordInfoBeam::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	return CWnd::OnSetCursor(pWnd, nHitTest, message);
}


HBRUSH CGXRecordInfoBeam::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CWnd::OnCtlColor(pDC, pWnd, nCtlColor);

	pDC->SetBkColor(m_rgbBack);

	return hbr;
}

// Color and scrollbar size

void CGXRecordInfoBeam::UpdateColors()
{
	// Colors
	m_rgbText = GXGetSysData()->GetSysColor(COLOR_WINDOWTEXT);
	m_rgbBack = GXGetSysData()->GetSysColor(COLOR_WINDOW);
	m_rgbFace = GXGetSysData()->GetSysColor(COLOR_BTNFACE);
	m_rgbBeam = GXGetSysData()->GetSysColor(COLOR_WINDOW);
}

void CGXRecordInfoBeam::OnSysColorChange()
{
	CWnd::OnSysColorChange();

	GXGetSysData()->UpdateSysColors();

	UpdateColors();

	Invalidate();
}

void CGXRecordInfoBeam::OnWinIniChange(LPCTSTR lpszSection)
{
	CWnd::OnWinIniChange(lpszSection);

	GXGetSysData()->UpdateSysSettings();

	int cy = GetSystemMetrics(SM_CYHSCROLL);

	if (m_nHeight != cy)
	{
		// scrollbar size did change

		m_nButtonWidth = m_nHeight = cy;

		CreateFonts();
	}

	Invalidate();
}

// Drawing helpers

void AFXAPI CGXRecordInfoBeam::PatB(CDC* pDC,int x,int y,int dx,int dy, COLORREF rgb)
{
	RECT    rc;

	rc.left   = x;
	rc.top    = y;
	rc.right  = x + dx;
	rc.bottom = (y + dy);

	COLORREF rgbOld = pDC->GetBkColor();
	pDC->SetBkColor(rgb);
	pDC->ExtTextOut(0,0,ETO_OPAQUE,&rc,NULL,0,NULL);
	pDC->SetBkColor(rgbOld);
}

void AFXAPI CGXRecordInfoBeam::DrawBlankButton(CDC* pDC, int x, int y, int dx, int dy, BOOL bPressed)
{
	// face color
	COLORREF rgbFace    = GXGetSysData()->GetSysColor(COLOR_BTNFACE);
	COLORREF rgbShadow  = GXGetSysData()->GetSysColor(COLOR_BTNSHADOW);
	COLORREF rgbHilite = GXGetSysData()->GetSysColor(COLOR_BTNHIGHLIGHT);
	COLORREF rgbFrame   = GXGetSysData()->GetSysColor(COLOR_WINDOWFRAME);

	x++;
	y++;
	dx--;
	dy--;

	// border around button
	PatB(pDC, x-1,  y-1,    dx+2, 1,  GXGetAppData()->bWin4 ? rgbFace : rgbFrame);
	PatB(pDC, x,    y+dy,   dx, 1,  rgbFrame);
	PatB(pDC, x-1,  y,      1,  dy, rgbFrame);
	PatB(pDC, x+dx, y,      1,  dy, rgbFrame);

	// interior grey
	PatB(pDC, x, y, dx, dy, rgbFace);
	
	if (bPressed)
	{
		// pressed in or down or down disabled
		PatB(pDC, x, y, 1, dy, rgbShadow);
		PatB(pDC, x, y, dx, 2, rgbShadow);

		PatB(pDC, x + dx - 1, y, 1, dy, rgbShadow);
		PatB(pDC, x, y + dy-1, dx, 1,   rgbShadow);
	}
	else
	{
		// regular button look
		if (GXGetAppData()->bWin4)
		{
			PatB(pDC, x+1, y, 1, dy - 1, rgbHilite);
			PatB(pDC, x+1, y, dx - 2, 1, rgbHilite);

			PatB(pDC, x + dx - 1, y, 1, dy, rgbShadow);
			PatB(pDC, x+1, y + dy-2, dx-1, 1,   rgbShadow);
		}
		else
		{
			PatB(pDC, x, y, 1, dy - 1, rgbHilite);
			PatB(pDC, x, y, dx - 1, 1, rgbHilite);

			PatB(pDC, x + dx - 1, y, 1, dy, rgbShadow);
			PatB(pDC, x, y + dy-2, dx, 1,   rgbShadow);

			PatB(pDC, x + 1 + dx - 3, y + 1, 1, dy-2, rgbShadow);
			PatB(pDC, x + 1, y + dy - 3, dx - 2, 1, rgbShadow);
		}
	}
}

