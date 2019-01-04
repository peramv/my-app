///////////////////////////////////////////////////////////////////////////////
// gxwndhnd.cpp : implementation of CGXGridHandleWnd class
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

#ifndef _GXWND_H_
#include "grid\gxwnd.h"
#endif

#ifndef _GXMSG_H_
#include "grid\gxmsg.h"
#endif

#ifndef _GXCTRL_H_
#include "grid\gxctrl.h"
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXWNDHND")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CGXGridHandleWnd, CWnd)
GRID_IMPLEMENT_REGISTER(CGXGridHandleWnd, CS_DBLCLKS | GX_GLOBALCLASS, 0, 0, 0)

static UINT NEAR wm_Find = RegisterWindowMessage( FINDMSGSTRING );

/////////////////////////////////////////////////////////////////////////////
// CGXGridHandleWnd support for dialog validation

void AFXAPI DDV_GXGridHandleWnd(CDataExchange* pDX, CGXGridHandleWnd* pGrid)
{
	if (pDX->m_bSaveAndValidate)
	{
		pDX->PrepareCtrl(pGrid->GetDlgCtrlID());
		if (!pGrid->GetGrid()->CanActivateGrid(FALSE))
			pDX->Fail();
	}
}

/////////////////////////////////////////////////////////////////////////////
// CGXGridHandleWnd

CGXGridHandleWnd::CGXGridHandleWnd()
{
	m_pGrid = NULL;
	m_bDrawSunken = FALSE;
}

CGXGridHandleWnd::~CGXGridHandleWnd()
{
	delete m_pGrid;
}

void CGXGridHandleWnd::AttachGrid(CGXGridCore* pGrid)
{
	m_pGrid = pGrid;
}

BOOL CGXGridHandleWnd::CreateGrid(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	return Create(NULL, NULL,
		dwStyle | WS_CHILD,
		rect, pParentWnd, nID);
}

#if _MFC_VER < 0x0300
WNDPROC* CGXGridHandleWnd::GetSuperWndProcAddr()
{
	// Note: it is no longer necessary to override GetSuperWndProcAddr
	//  for each control class with a different WNDCLASS.
	//  This implementation now uses instance data, such that the previous
	//  WNDPROC can be anything.

	static WNDPROC NEAR pfnSuper;
	return &pfnSuper;
}
#endif

BEGIN_MESSAGE_MAP(CGXGridHandleWnd, CWnd)
	//{{AFX_MSG_MAP(CGXGridHandleWnd)
	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_HSCROLL()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_WM_SETCURSOR()
	ON_WM_SIZE()
	ON_WM_VSCROLL()
	ON_WM_GETDLGCODE()
	ON_WM_SETFOCUS()
	ON_MESSAGE(WM_GX_CHANGEDTAB, OnChangedTab)
	ON_MESSAGE(WM_GX_NEEDCHANGETAB, OnNeedChangeTab)
	ON_MESSAGE(WM_GX_CANACTIVATE, OnCanActivate)
	ON_MESSAGE(WM_GX_MOVERECORD, OnMoveRecord)
	ON_MESSAGE(WM_GX_LOCKRESIZE, OnLockResize)
	ON_WM_CHAR()
	ON_WM_SYSKEYDOWN()
	ON_WM_SYSCHAR()
	ON_WM_SYSKEYUP()
	ON_WM_KILLFOCUS()
	ON_WM_CANCELMODE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MBUTTONDBLCLK()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_SHOWWINDOW()
	ON_WM_KEYUP()
	ON_WM_MOUSEACTIVATE()
	ON_WM_SYSCOLORCHANGE()
	ON_WM_NCPAINT()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_REGISTERED_MESSAGE(wm_Find, OnFindReplaceCmd)
	ON_WM_WININICHANGE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGXGridHandleWnd initialization

void CGXGridHandleWnd::Initialize()
{
	if (m_pGrid == NULL)
		m_pGrid = new CGXGridCore(this);

	// is it embedded in a CGXTabWnd or CGXRecordInfoWnd?
	if (m_pGrid->GetSharedScrollbarParentWnd())
		m_pGrid->SetScrollBarMode(SB_BOTH, gxnShared | gxnEnhanced, FALSE);

	// no, turn on scroll bars depending on the style-bits of the window
	// (the programmer can specify them in AppStudio or directly when
	// calling the Create method)
	else
	{
		DWORD dwStyle = GetStyle();
		if ((DWORD) (dwStyle & WS_VSCROLL))
			m_pGrid->SetScrollBarMode(SB_VERT, gxnAutomatic | gxnEnhanced, FALSE);
		else
			m_pGrid->SetScrollBarMode(SB_VERT, gxnDisabled, FALSE);

		if ((DWORD) (dwStyle & WS_HSCROLL))
			m_pGrid->SetScrollBarMode(SB_HORZ, gxnAutomatic | gxnEnhanced, FALSE);
		else
			m_pGrid->SetScrollBarMode(SB_HORZ, gxnDisabled, FALSE);
	}

	OnInitialUpdate();
}

void CGXGridHandleWnd::OnInitialUpdate()
{
	if (m_pGrid)
		m_pGrid->OnGridInitialUpdate();
}

#define _GXGetDlgCtrlID(hWnd)          ((UINT)(WORD)::GetDlgCtrlID(hWnd))

UINT AFXAPI CGXGridHandleWnd::GetParentTabViewID(const CWnd* pWnd)
{
	UINT nID = _GXGetDlgCtrlID(pWnd->GetSafeHwnd());
	ASSERT(nID >= AFX_IDW_PANE_FIRST && nID < AFX_IDW_PANE_LAST);
	return nID-AFX_IDW_PANE_FIRST;
}

CScrollBar* CGXGridHandleWnd::GetScrollBarCtrl(int nBar) const
{
	CScrollBar* pBar = m_pGrid ? m_pGrid->DoGetScrollBarCtrl(nBar) : NULL;
	if (pBar != NULL)
		return pBar;

	return CWnd::GetScrollBarCtrl(nBar);
}

LRESULT CGXGridHandleWnd::OnChangedTab(WPARAM wParam, LPARAM /*lParam*/)
{
	if (m_pGrid)
		m_pGrid->OnTabChanged((int) wParam);

	return 0;
}

LRESULT CGXGridHandleWnd::OnNeedChangeTab(WPARAM /*wParam*/, LPARAM /*lParam*/)
{
	return m_pGrid ? m_pGrid->CanChangeTab() : 0;
}

LRESULT CGXGridHandleWnd::OnCanActivate(WPARAM wParam, LPARAM /*lParam*/)
{
	BOOL bCanActivate = m_pGrid && m_pGrid->CanActivateGrid((BOOL) wParam);

	// Please note:
	// activation is allowed when return value is 0
	// activation is disabled when return value is 1
	return bCanActivate ? 0 : 1;
}

LRESULT CGXGridHandleWnd::OnLockResize(WPARAM wParam, LPARAM )
{
	if (m_pGrid)
		m_pGrid->LockResize((BOOL) wParam);
	return 0;
}

LRESULT CGXGridHandleWnd::OnMoveRecord(WPARAM wParam, LPARAM lParam)
{
	SetFocus();
	if (m_pGrid)
		m_pGrid->OnInfoWndMoveRecord((int) wParam, (long) lParam);
	return 0;
}

LRESULT CGXGridHandleWnd::OnFindReplaceCmd(WPARAM, LPARAM lParam)
{
	CFindReplaceDialog* pDialog = CFindReplaceDialog::GetNotifier(lParam);

	if (m_pGrid)
		m_pGrid->OnFindReplace(pDialog);

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CGXGridHandleWnd message handlers

void CGXGridHandleWnd::OnPaint()
{
	// standard paint routine
	if (m_pGrid == NULL)
	{
		TRACE0("Warning! You must call CGXGridHandleWnd::Initialize() in OnInitDialog!\n");
		ASSERT(0);        // You must call Initialize() in OnInitDialog!
		AfxThrowNotSupportedException();
	}

	CPaintDC dc(this);
	m_pGrid->OnGridPrepareDC(&dc);
	m_pGrid->OnGridDraw(&dc);
}


void CGXGridHandleWnd::OnNcPaint()
{
	// Draw scrollbars and other non-client area
	Default();

	if (m_bDrawSunken
#if _MFC_VER >= 0x0400
		|| (GetExStyle() & WS_EX_CLIENTEDGE) > 0
#endif
		)
	{
		// Check if we have a valid parent window
		CWnd* pParentWnd = GetParent();
		if (pParentWnd == NULL)
			return;

		// Get device context for painting in parent window
		CClientDC dc(pParentWnd);

		// Grid rectangle
		CRect r;
		GetWindowRect( &r );
		pParentWnd->ScreenToClient( &r );

		// Add space for sunken border
		r.left -= 2;
		r.top -= 2;
		r.right += 3;
		r.bottom += 3;

		// Draw sunken border
		_GXDrawSunkenBorders(&dc, r, TRUE, TRUE);
	}
}

HBRUSH CGXGridHandleWnd::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	if (m_pGrid)
		return m_pGrid->DoCtlColor(pDC, pWnd, nCtlColor);
	return 0;
}

void CGXGridHandleWnd::OnDestroy()
{
	if (!(m_pGrid && m_pGrid->DoNotifyDestroy()))
		CWnd::OnDestroy();
}

void CGXGridHandleWnd::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (!(m_pGrid && m_pGrid->DoHScroll(nSBCode, nPos, pScrollBar)))
		CWnd::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CGXGridHandleWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!(m_pGrid && m_pGrid->ProcessKeys(this, WM_KEYDOWN, nChar, nRepCnt, nFlags)))
		CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CGXGridHandleWnd::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!(m_pGrid && m_pGrid->ProcessKeys(this, WM_KEYUP, nChar, nRepCnt, nFlags)))
		CWnd::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CGXGridHandleWnd::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!(m_pGrid && m_pGrid->ProcessKeys(this, WM_SYSKEYDOWN, nChar, nRepCnt, nFlags)))
		CWnd::OnSysKeyDown(nChar, nRepCnt, nFlags);
}

void CGXGridHandleWnd::OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!(m_pGrid && m_pGrid->ProcessKeys(this, WM_SYSCHAR, nChar, nRepCnt, nFlags)))
		CWnd::OnSysChar(nChar, nRepCnt, nFlags);
	nChar, nRepCnt, nFlags;
}

void CGXGridHandleWnd::OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!(m_pGrid && m_pGrid->ProcessKeys(this, WM_SYSKEYUP, nChar, nRepCnt, nFlags)))
		CWnd::OnSysKeyUp(nChar, nRepCnt, nFlags);
	nChar, nRepCnt, nFlags;
}

void CGXGridHandleWnd::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!(m_pGrid && m_pGrid->ProcessKeys(this, WM_CHAR, nChar, nRepCnt, nFlags)))
		CWnd::OnChar(nChar, nRepCnt, nFlags);
}

void CGXGridHandleWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	CWnd* pFocus = GetFocus();
	if (pFocus != this && (pFocus == NULL || !IsChild(pFocus)))
		SetFocus();

	if (!(m_pGrid && m_pGrid->DoLButtonDown(nFlags, point)))
		CWnd::OnLButtonDown(nFlags, point);
}

void CGXGridHandleWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (!(m_pGrid && m_pGrid->DoLButtonUp(nFlags, point)))
		CWnd::OnLButtonUp(nFlags, point);
}

void CGXGridHandleWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	if (!(m_pGrid && m_pGrid->DoMouseMove(nFlags, point)))
		CWnd::OnMouseMove(nFlags, point);
}

void CGXGridHandleWnd::OnLButtonDblClk(UINT flags, CPoint point)
{
	if (!(m_pGrid && m_pGrid->DoLButtonDblClk(flags, point)))
		CWnd::OnLButtonDblClk(flags, point);
}

void CGXGridHandleWnd::OnMButtonDblClk(UINT flags, CPoint point)
{
	if (!(m_pGrid && m_pGrid->DoMButtonDblClk(flags, point)))
		CWnd::OnMButtonDblClk(flags, point);
}

void CGXGridHandleWnd::OnMButtonDown(UINT flags, CPoint point)
{
	CWnd* pFocus = GetFocus();
	if (pFocus != this && (pFocus == NULL || !IsChild(pFocus)))
		SetFocus();

	if (!(m_pGrid && m_pGrid->DoMButtonDown(flags, point)))
		CWnd::OnMButtonDown(flags, point);
}

void CGXGridHandleWnd::OnMButtonUp(UINT flags, CPoint point)
{
	if (!(m_pGrid && m_pGrid->DoMButtonUp(flags, point)))
		CWnd::OnMButtonUp(flags, point);
}

void CGXGridHandleWnd::OnRButtonDblClk(UINT flags, CPoint point)
{
	if (!(m_pGrid && m_pGrid->DoRButtonDblClk(flags, point)))
		CWnd::OnRButtonDblClk(flags, point);
}

void CGXGridHandleWnd::OnRButtonDown(UINT flags, CPoint point)
{
	CWnd* pFocus = GetFocus();
	if (pFocus != this && (pFocus == NULL || !IsChild(pFocus)))
		SetFocus();

	if (!(m_pGrid && m_pGrid->DoRButtonDown(flags, point)))
		CWnd::OnRButtonDown(flags, point);
}

void CGXGridHandleWnd::OnRButtonUp(UINT flags, CPoint point)
{
	if (!(m_pGrid && m_pGrid->DoRButtonUp(flags, point)))
		CWnd::OnRButtonUp(flags, point);
}

BOOL CGXGridHandleWnd::OnEraseBkgnd(CDC* /*pDC*/)
{
	return TRUE;
}

BOOL CGXGridHandleWnd::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	if (m_pGrid && m_pGrid->DoSetCursor(pWnd, nHitTest, message))
		return TRUE;
	return CWnd::OnSetCursor(pWnd, nHitTest, message);
}

void CGXGridHandleWnd::OnSize(UINT nType, int cx, int cy)
{
	if (!(m_pGrid && m_pGrid->DoSize(nType, cx, cy)))
		CWnd::OnSize(nType, cx, cy);
}

void CGXGridHandleWnd::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CWnd::OnShowWindow(bShow, nStatus);
	if (m_pGrid)
		m_pGrid->DoShowWindow(bShow, nStatus);
}

void CGXGridHandleWnd::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (!(m_pGrid && m_pGrid->DoVScroll(nSBCode, nPos, pScrollBar)))
		CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CGXGridHandleWnd::OnSetFocus(CWnd* pOldWnd)
{
	CWnd::OnSetFocus(pOldWnd);
	if (m_pGrid)
		m_pGrid->OnGridSetFocus(pOldWnd);
}

void CGXGridHandleWnd::OnKillFocus(CWnd* pNewWnd)
{
	CWnd::OnKillFocus(pNewWnd);
	if (m_pGrid)
		m_pGrid->OnGridKillFocus(pNewWnd);
}

UINT CGXGridHandleWnd::OnGetDlgCode()
{
	if (m_pGrid)
		return m_pGrid->DoGetDlgCode(CWnd::OnGetDlgCode());
	return CWnd::OnGetDlgCode();
}

void CGXGridHandleWnd::OnCancelMode()
{
	// TRACE0("OnCancelMode\n");
	if (m_pGrid)
		m_pGrid->DoCancelMode();
}

int CGXGridHandleWnd::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	int retval;

	if (m_pGrid && m_pGrid->DoMouseActivate(pDesktopWnd, nHitTest, message, retval))
		return retval;

	return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

BOOL CGXGridHandleWnd::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if (m_pGrid && m_pGrid->DoCommand(wParam, lParam))
		return TRUE;

	return CWnd::OnCommand(wParam, lParam);
}

BOOL CGXGridHandleWnd::PreTranslateMessage(MSG* pMsg)
{
	if (m_pGrid && m_pGrid->OnGridPreTranslateMessage(pMsg))
		return TRUE;

	return CWnd::PreTranslateMessage(pMsg);
}

LRESULT CGXGridHandleWnd::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	LRESULT result;

	if (m_pGrid && m_pGrid->OnGridWindowProc(message, wParam, lParam, result))
		return result;

	return CWnd::WindowProc(message, wParam, lParam);
}

void CGXGridHandleWnd::OnWinIniChange(LPCTSTR lpszSection)
{
	if (m_pGrid)
		m_pGrid->OnGridWinIniChange(lpszSection);
	CWnd::OnWinIniChange(lpszSection);
}

void CGXGridHandleWnd::OnSysColorChange()
{
	if (m_pGrid)
		m_pGrid->OnGridSysColorChange();
	CWnd::OnSysColorChange();
}

void CGXGridHandleWnd::OnTimer(SEC_UINT nIDEvent)
{
	if (m_pGrid)
		m_pGrid->OnGridTimer(nIDEvent);

	CWnd::OnTimer(nIDEvent);
}

/////////////////////////////////////////////////////////////////////////////
// CGXGridHandleWnd printing

void CGXGridHandleWnd::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	if (m_pGrid)
		m_pGrid->OnGridBeginPrinting(pDC, pInfo);
}

void CGXGridHandleWnd::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	if (m_pGrid)
		m_pGrid->OnGridEndPrinting(pDC, pInfo);
}

void CGXGridHandleWnd::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	if (m_pGrid)
		m_pGrid->OnGridPrint(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CGXGridHandleWnd diagnostics

#ifdef _DEBUG
void CGXGridHandleWnd::AssertValid() const
{
	if (m_pGrid)
		m_pGrid->AssertValid();
	CWnd::AssertValid();
}

void CGXGridHandleWnd::Dump(CDumpContext& dc) const
{
	if (m_pGrid)
		m_pGrid->Dump(dc);
	CWnd::Dump(dc);
}

#endif //_DEBUG
