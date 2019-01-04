///////////////////////////////////////////////////////////////////////////////
// gxbrownd.cpp : implementation of CGXBrowserWnd
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

// Headers for imported classes

#ifndef _GXRESRC_H_
#include "grid\gxresrc.h"
#endif

#ifndef _GXBROWSE_H_
#include "grid\gxbrowse.h"
#endif

#ifndef _GXMSG_H_
#include "grid\gxmsg.h"
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXBROWND")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CGXBrowserWnd, CWnd)
GRID_IMPLEMENT_REGISTER(CGXBrowserWnd, CS_DBLCLKS | GX_GLOBALCLASS, 0, 0, 0)

static UINT NEAR wm_Find = RegisterWindowMessage( FINDMSGSTRING );

/////////////////////////////////////////////////////////////////////////////
// CGXBrowserWnd

CGXBrowserWnd::CGXBrowserWnd()
{
	SetGridWnd(this);
}

BOOL CGXBrowserWnd::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	return CWnd::Create(_T("GxWnd"), NULL,
		dwStyle | WS_CHILD,
		rect, pParentWnd, nID);
}

#if _MFC_VER < 0x0300
WNDPROC* CGXBrowserWnd::GetSuperWndProcAddr()
{
	// Note: it is no longer necessary to override GetSuperWndProcAddr
	//  for each control class with a different WNDCLASS.
	//  This implementation now uses instance data, such that the previous
	//  WNDPROC can be anything.

	static WNDPROC NEAR pfnSuper;
	return &pfnSuper;
}
#endif

BEGIN_MESSAGE_MAP(CGXBrowserWnd, CWnd)
	//{{AFX_MSG_MAP(CGXBrowserWnd)
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
	ON_MESSAGE(WM_GX_LOCKRESIZE, OnLockResize)
	ON_MESSAGE(WM_GX_MOVERECORD, OnMoveRecord)
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
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_WM_WININICHANGE()
	ON_REGISTERED_MESSAGE(wm_Find, OnFindReplaceCmd)
	ON_UPDATE_COMMAND_UI(ID_RECORD_FIRST, OnUpdateRecordFirst)
	ON_UPDATE_COMMAND_UI(ID_RECORD_PREV, OnUpdateRecordPrev)
	ON_UPDATE_COMMAND_UI(ID_RECORD_NEXT, OnUpdateRecordNext)
	ON_UPDATE_COMMAND_UI(ID_RECORD_LAST, OnUpdateRecordLast)
	ON_COMMAND_EX(ID_RECORD_FIRST, OnMove)
	ON_COMMAND_EX(ID_RECORD_PREV, OnMove)
	ON_COMMAND_EX(ID_RECORD_NEXT, OnMove)
	ON_COMMAND_EX(ID_RECORD_LAST, OnMove)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGXBrowserWnd initialization

void CGXBrowserWnd::Initialize()
{
	// is it embedded in a CGXTabWnd or CGXRecordInfoWnd?
	if (GetSharedScrollbarParentWnd())
		// use shared scrollbars
		SetScrollBarMode(SB_BOTH, gxnShared | gxnEnhanced, FALSE);

	// no, turn on scroll bars depending on the style-bits of the window
	// (the programmer can specify them in AppStudio or directly when
	// calling the Create method)
	else
	{
		DWORD dwStyle = GetStyle();
		if ((DWORD) (dwStyle & WS_VSCROLL))
			SetScrollBarMode(SB_VERT, gxnAutomatic | gxnEnhanced, FALSE);
		else
			SetScrollBarMode(SB_VERT, gxnDisabled, FALSE);

		if ((DWORD) (dwStyle & WS_HSCROLL))
			SetScrollBarMode(SB_HORZ, gxnAutomatic | gxnEnhanced, FALSE);
		else
			SetScrollBarMode(SB_HORZ, gxnDisabled, FALSE);
	}

	OnInitialUpdate();
}

void CGXBrowserWnd::OnInitialUpdate()
{
	OnGridInitialUpdate();
}

/////////////////////////////////////////////////////////////////////////////
// CGXBrowserWnd support for CGXTabWnd/CGXDaoRecordInfoWnd

#define _GXGetDlgCtrlID(hWnd)          ((UINT)(WORD)::GetDlgCtrlID(hWnd))

UINT AFXAPI CGXBrowserWnd::GetParentTabViewID(const CWnd* pWnd)
{
	UINT nID = _GXGetDlgCtrlID(pWnd->m_hWnd);
	ASSERT(nID >= AFX_IDW_PANE_FIRST && nID < AFX_IDW_PANE_LAST);
	return nID-AFX_IDW_PANE_FIRST;
}

CScrollBar* CGXBrowserWnd::GetScrollBarCtrl(int nBar) const
{
	CScrollBar* pBar = DoGetScrollBarCtrl(nBar);
	if (pBar != NULL)
		return pBar;

	return CWnd::GetScrollBarCtrl(nBar);
}

LRESULT CGXBrowserWnd::OnChangedTab(WPARAM wParam, LPARAM /*lParam*/)
{
	OnTabChanged((int) wParam);

	return 0;
}

LRESULT CGXBrowserWnd::OnNeedChangeTab(WPARAM /*wParam*/, LPARAM /*lParam*/)
{
	return CanChangeTab();
}

LRESULT CGXBrowserWnd::OnCanActivate(WPARAM wParam, LPARAM /*lParam*/)
{
	BOOL bCanActivate = CanActivateGrid((BOOL) wParam);

	// Please note:
	// activation is allowed when return value is 0
	// activation is disabled when return value is 1
	return bCanActivate ? 0 : 1;
}

LRESULT CGXBrowserWnd::OnLockResize(WPARAM wParam, LPARAM )
{
	LockResize((BOOL) wParam);
	return 0;
}

LRESULT CGXBrowserWnd::OnMoveRecord(WPARAM wParam, LPARAM lParam)
{
	SetFocus();
	OnInfoWndMoveRecord((int) wParam, (long) lParam);
	return 0;
}

LRESULT CGXBrowserWnd::OnFindReplaceCmd(WPARAM, LPARAM lParam)
{
	ASSERT_VALID(this);
	CFindReplaceDialog* pDialog = CFindReplaceDialog::GetNotifier(lParam);

	OnFindReplace(pDialog);

	ASSERT_VALID(this);
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CGXBrowserWnd message handlers

void CGXBrowserWnd::OnPaint()
{
	// standard paint routine
	if (!m_bInitDone)
	{
		TRACE0("Warning! You must call CGXGridWnd::Initialize() in OnInitDialog!\n");
		ASSERT(0);        // You must call Initialize() in OnInitDialog!
		AfxThrowNotSupportedException();
	}

	CPaintDC dc(this);
	OnGridPrepareDC(&dc);
	OnGridDraw(&dc);
}

HBRUSH CGXBrowserWnd::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	return DoCtlColor(pDC, pWnd, nCtlColor);
}

void CGXBrowserWnd::OnDestroy()
{
	if (!DoNotifyDestroy())
		CWnd::OnDestroy();
}

void CGXBrowserWnd::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (!DoHScroll(nSBCode, nPos, pScrollBar))
		CWnd::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CGXBrowserWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!ProcessKeys(this, WM_KEYDOWN, nChar, nRepCnt, nFlags))
		CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CGXBrowserWnd::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!ProcessKeys(this, WM_KEYUP, nChar, nRepCnt, nFlags))
		CWnd::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CGXBrowserWnd::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!ProcessKeys(this, WM_SYSKEYDOWN, nChar, nRepCnt, nFlags))
		CWnd::OnSysKeyDown(nChar, nRepCnt, nFlags);
}

void CGXBrowserWnd::OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!ProcessKeys(this, WM_SYSCHAR, nChar, nRepCnt, nFlags))
		CWnd::OnSysChar(nChar, nRepCnt, nFlags);
	nChar, nRepCnt, nFlags;
}

void CGXBrowserWnd::OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!ProcessKeys(this, WM_SYSKEYUP, nChar, nRepCnt, nFlags))
		CWnd::OnSysKeyUp(nChar, nRepCnt, nFlags);
	nChar, nRepCnt, nFlags;
}

void CGXBrowserWnd::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!ProcessKeys(this, WM_CHAR, nChar, nRepCnt, nFlags))
		CWnd::OnChar(nChar, nRepCnt, nFlags);
}

void CGXBrowserWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	CWnd* pFocus = GetFocus();
	if (pFocus != this && (pFocus == NULL || !IsChild(pFocus)))
		SetFocus();

	if (!DoLButtonDown(nFlags, point))
		CWnd::OnLButtonDown(nFlags, point);
}

void CGXBrowserWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (!DoLButtonUp(nFlags, point))
		CWnd::OnLButtonUp(nFlags, point);
}

void CGXBrowserWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	if (!DoMouseMove(nFlags, point))
		CWnd::OnMouseMove(nFlags, point);
}

void CGXBrowserWnd::OnLButtonDblClk(UINT flags, CPoint point)
{
	if (!DoLButtonDblClk(flags, point))
		CWnd::OnLButtonDblClk(flags, point);
}

void CGXBrowserWnd::OnMButtonDblClk(UINT flags, CPoint point)
{
	if (!DoMButtonDblClk(flags, point))
		CWnd::OnMButtonDblClk(flags, point);
}

void CGXBrowserWnd::OnMButtonDown(UINT flags, CPoint point)
{
	if (!DoMButtonDown(flags, point))
		CWnd::OnMButtonDown(flags, point);
}

void CGXBrowserWnd::OnMButtonUp(UINT flags, CPoint point)
{
	if (!DoMButtonUp(flags, point))
		CWnd::OnMButtonUp(flags, point);
}

void CGXBrowserWnd::OnRButtonDblClk(UINT flags, CPoint point)
{
	if (!DoRButtonDblClk(flags, point))
		CWnd::OnRButtonDblClk(flags, point);
}

void CGXBrowserWnd::OnRButtonDown(UINT flags, CPoint point)
{
	if (!DoRButtonDown(flags, point))
		CWnd::OnRButtonDown(flags, point);
}

void CGXBrowserWnd::OnRButtonUp(UINT flags, CPoint point)
{
	if (!DoRButtonUp(flags, point))
		CWnd::OnRButtonUp(flags, point);
}

BOOL CGXBrowserWnd::OnEraseBkgnd(CDC* /*pDC*/)
{
	return TRUE;
}

BOOL CGXBrowserWnd::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	if (DoSetCursor(pWnd, nHitTest, message))
		return TRUE;
	return CWnd::OnSetCursor(pWnd, nHitTest, message);
}

void CGXBrowserWnd::OnSize(UINT nType, int cx, int cy)
{
	if (!DoSize(nType, cx, cy))
		CWnd::OnSize(nType, cx, cy);
}

void CGXBrowserWnd::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CWnd::OnShowWindow(bShow, nStatus);
	DoShowWindow(bShow, nStatus);
}

void CGXBrowserWnd::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (!DoVScroll(nSBCode, nPos, pScrollBar))
		CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CGXBrowserWnd::OnSetFocus(CWnd* pOldWnd)
{
	CWnd::OnSetFocus(pOldWnd);
	OnGridSetFocus(pOldWnd);
}

void CGXBrowserWnd::OnKillFocus(CWnd* pNewWnd)
{
	CWnd::OnKillFocus(pNewWnd);
	OnGridKillFocus(pNewWnd);
}

UINT CGXBrowserWnd::OnGetDlgCode()
{
	return DoGetDlgCode(CWnd::OnGetDlgCode());
}

void CGXBrowserWnd::OnCancelMode()
{
	// TRACE0("OnCancelMode\n");
	DoCancelMode();
}

int CGXBrowserWnd::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	int retval;

	if (DoMouseActivate(pDesktopWnd, nHitTest, message, retval))
		return retval;

	return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

BOOL CGXBrowserWnd::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if (DoCommand(wParam, lParam))
		return TRUE;

	return CWnd::OnCommand(wParam, lParam);
}

BOOL CGXBrowserWnd::PreTranslateMessage(MSG* pMsg)
{
	if (OnGridPreTranslateMessage(pMsg))
		return TRUE;

	return CWnd::PreTranslateMessage(pMsg);
}

LRESULT CGXBrowserWnd::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	LRESULT result;

	if (OnGridWindowProc(message, wParam, lParam, result))
		return result;

	return CWnd::WindowProc(message, wParam, lParam);
}

void CGXBrowserWnd::OnWinIniChange(LPCTSTR lpszSection)
{
	OnGridWinIniChange(lpszSection);
	CWnd::OnWinIniChange(lpszSection);
}

void CGXBrowserWnd::OnSysColorChange()
{
	OnGridSysColorChange();
	CWnd::OnSysColorChange();
}

void CGXBrowserWnd::OnTimer(SEC_UINT nIDEvent)
{
	OnGridTimer(nIDEvent);

	CWnd::OnTimer(nIDEvent);
}

/////////////////////////////////////////////////////////////////////////////
// CGXBrowserWnd printing

void CGXBrowserWnd::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	OnGridBeginPrinting(pDC, pInfo);
}

void CGXBrowserWnd::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	OnGridEndPrinting(pDC, pInfo);
}

void CGXBrowserWnd::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	OnGridPrint(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CGXBrowserWnd diagnostics

#ifdef _DEBUG
void CGXBrowserWnd::AssertValid() const
{
	CWnd::AssertValid();
	CGXBrowserGrid::AssertValid();
}

void CGXBrowserWnd::Dump(CDumpContext& dc) const
{
	CWnd::Dump(dc);
	CGXBrowserGrid::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGXBrowserWnd message handlers

void CGXBrowserWnd::OnUpdateRecordFirst(CCmdUI* pCmdUI)
{
	CGXBrowserGrid::OnUpdateRecordFirst(pCmdUI);
}

void CGXBrowserWnd::OnUpdateRecordPrev(CCmdUI* pCmdUI)
{
	CGXBrowserGrid::OnUpdateRecordPrev(pCmdUI);
}

void CGXBrowserWnd::OnUpdateRecordNext(CCmdUI* pCmdUI)
{
	CGXBrowserGrid::OnUpdateRecordNext(pCmdUI);
}

void CGXBrowserWnd::OnUpdateRecordLast(CCmdUI* pCmdUI)
{
	CGXBrowserGrid::OnUpdateRecordLast(pCmdUI);
}

void CGXBrowserWnd::OnUpdateEditUndorecord(CCmdUI* pCmdUI)
{
	CGXBrowserGrid::OnUpdateEditUndorecord(pCmdUI);
}

void CGXBrowserWnd::OnEditUndorecord()
{
	CGXBrowserGrid::OnEditUndorecord();
}

void CGXBrowserWnd::OnRecordDelete()
{
	CGXBrowserGrid::OnRecordDelete();
}

void CGXBrowserWnd::OnUpdateRecordDelete(CCmdUI* pCmdUI)
{
	CGXBrowserGrid::OnUpdateRecordDelete(pCmdUI);
}

BOOL CGXBrowserWnd::OnMove(UINT nIDMoveCommand)
{
	return CGXBrowserGrid::OnMove(nIDMoveCommand);
}

void CGXBrowserWnd::OnView100()
{
	SetZoom(100);
}

void CGXBrowserWnd::OnViewZoomin()
{
	if (GetZoom() < 300)
		SetZoom(GetZoom()*11/10);
}

void CGXBrowserWnd::OnViewZoomout()
{
	if (GetZoom() > 40)
		SetZoom(GetZoom()*10/11);
}

void CGXBrowserWnd::OnUpdateViewZoomin(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(GetParam() && GetZoom() < 300);
}

void CGXBrowserWnd::OnUpdateViewZoomout(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(GetParam() && GetZoom() > 40);
}

/////////////////////////////////////////////////////////////////////////////
// Freeze Rows and Columns menu handlers

void CGXBrowserWnd::OnFormatFreezecols()
{
	FreezeCols();
}

void CGXBrowserWnd::OnFormatUnfreezecols()
{
	UnfreezeCols();
}

void CGXBrowserWnd::OnUpdateFormatFreezecols(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(CanFreezeCols());
}

void CGXBrowserWnd::OnUpdateFormatUnfreezecols(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(CanUnfreezeCols());
}
