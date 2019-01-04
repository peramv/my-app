///////////////////////////////////////////////////////////////////////////////
// gxdavw.cpp : implementation of CGXAdoRecordView class
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
// Authors: Praveen Ramesh, Stefan Hoenig
//

#define _OG_EXPORT_IMPL

#include "stdafx.h"

// compile this file only if ADO is supported
#if _MFC_VER >= 0x0400 && !defined(_GX_NO_ADO_SUPPORT)

#ifdef _GXDLL
// used for MFC 2.5 Extension DLL
	#undef AFXAPI_DATA
	#define AFXAPI_DATA __based(__segname("_DATA"))
#endif

// Headers 

#ifndef _GXRESRC_H_
#include "grid\gxresrc.h"
#endif

#ifndef _GXWND_H_
#include "grid\gxwnd.h"
#endif

#ifndef _GXMSG_H_
#include "grid\gxmsg.h"
#endif

#ifndef _GXADO_H_
#include "grid\gxado.h"
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXADOWND")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

static UINT NEAR wm_Find = RegisterWindowMessage( FINDMSGSTRING );

/////////////////////////////////////////////////////////////////////////////
// CGXAdoRecordWnd

IMPLEMENT_DYNCREATE(CGXAdoRecordWnd, CWnd)
GRID_IMPLEMENT_REGISTER(CGXAdoRecordWnd, CS_DBLCLKS | GX_GLOBALCLASS, 0, 0, 0)



CGXAdoRecordWnd::CGXAdoRecordWnd()
{
	SetGridWnd(this);
}

BOOL CGXAdoRecordWnd::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	return CWnd::Create(_T("GxWnd"), NULL,
		dwStyle | WS_CHILD,
		rect, pParentWnd, nID);
}

#if _MFC_VER < 0x0300
WNDPROC* CGXAdoRecordWnd::GetSuperWndProcAddr()
{
	// Note: it is no longer necessary to override GetSuperWndProcAddr
	//  for each control class with a different WNDCLASS.
	//  This implementation now uses instance data, such that the previous
	//  WNDPROC can be anything.

	static WNDPROC NEAR pfnSuper;
	return &pfnSuper;
}
#endif

BEGIN_MESSAGE_MAP(CGXAdoRecordWnd, CWnd)
	//{{AFX_MSG_MAP(CGXAdoRecordWnd)
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
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI(ID_RECORD_FIRST, OnUpdateRecordFirst)
	ON_UPDATE_COMMAND_UI(ID_RECORD_PREV, OnUpdateRecordPrev)
	ON_UPDATE_COMMAND_UI(ID_RECORD_NEXT, OnUpdateRecordNext)
	ON_UPDATE_COMMAND_UI(ID_RECORD_LAST, OnUpdateRecordLast)
	ON_COMMAND_EX(ID_RECORD_FIRST, OnMove)
	ON_COMMAND_EX(ID_RECORD_PREV, OnMove)
	ON_COMMAND_EX(ID_RECORD_NEXT, OnMove)
	ON_COMMAND_EX(ID_RECORD_LAST, OnMove)
	ON_REGISTERED_MESSAGE(wm_Find, OnFindReplaceCmd)
	ON_WM_WININICHANGE()
	ON_MESSAGE(WM_GX_ADO_REQUERY, OnAdoRequery)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGXAdoRecordWnd initialization

void CGXAdoRecordWnd::Initialize()
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

void CGXAdoRecordWnd::OnInitialUpdate()
{
	OnGridInitialUpdate();
}

/////////////////////////////////////////////////////////////////////////////
// CGXAdoRecordWnd support for CGXTabWnd/CGXAdoRecordInfoWnd

#define _GXGetDlgCtrlID(hWnd)          ((UINT)(WORD)::GetDlgCtrlID(hWnd))

UINT AFXAPI CGXAdoRecordWnd::GetParentTabViewID(const CWnd* pWnd)
{
	UINT nID = _GXGetDlgCtrlID(pWnd->m_hWnd);
	ASSERT(nID >= AFX_IDW_PANE_FIRST && nID < AFX_IDW_PANE_LAST);
	return nID-AFX_IDW_PANE_FIRST;
}

CScrollBar* CGXAdoRecordWnd::GetScrollBarCtrl(int nBar) const
{
	CScrollBar* pBar = DoGetScrollBarCtrl(nBar);
	if (pBar != NULL)
		return pBar;

	return CWnd::GetScrollBarCtrl(nBar);
}

LRESULT CGXAdoRecordWnd::OnChangedTab(WPARAM wParam, LPARAM /*lParam*/)
{
	OnTabChanged((int) wParam);

	return 0;
}

LRESULT CGXAdoRecordWnd::OnNeedChangeTab(WPARAM /*wParam*/, LPARAM /*lParam*/)
{
	return CanChangeTab();
}

LRESULT CGXAdoRecordWnd::OnCanActivate(WPARAM wParam, LPARAM /*lParam*/)
{
	BOOL bCanActivate = CanActivateGrid((BOOL) wParam);

	// Please note:
	// activation is allowed when return value is 0
	// activation is disabled when return value is 1
	return bCanActivate ? 0 : 1;
}

LRESULT CGXAdoRecordWnd::OnMoveRecord(WPARAM wParam, LPARAM lParam)
{
	SetFocus();
	OnInfoWndMoveRecord((int) wParam, (long) lParam);
	return 0;
}

LRESULT CGXAdoRecordWnd::OnLockResize(WPARAM wParam, LPARAM )
{
	LockResize((BOOL) wParam);
	return 0;
}

LRESULT CGXAdoRecordWnd::OnFindReplaceCmd(WPARAM, LPARAM lParam)
{
	ASSERT_VALID(this);
	CFindReplaceDialog* pDialog = CFindReplaceDialog::GetNotifier(lParam);

	OnFindReplace(pDialog);

	ASSERT_VALID(this);
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CGXAdoRecordWnd message handlers

void CGXAdoRecordWnd::OnPaint()
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

HBRUSH CGXAdoRecordWnd::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	return DoCtlColor(pDC, pWnd, nCtlColor);
}

void CGXAdoRecordWnd::OnDestroy()
{
	if (!DoNotifyDestroy())
		CWnd::OnDestroy();
}

void CGXAdoRecordWnd::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (!DoHScroll(nSBCode, nPos, pScrollBar))
		CWnd::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CGXAdoRecordWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!ProcessKeys(this, WM_KEYDOWN, nChar, nRepCnt, nFlags))
		CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CGXAdoRecordWnd::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!ProcessKeys(this, WM_KEYUP, nChar, nRepCnt, nFlags))
		CWnd::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CGXAdoRecordWnd::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!ProcessKeys(this, WM_SYSKEYDOWN, nChar, nRepCnt, nFlags))
		CWnd::OnSysKeyDown(nChar, nRepCnt, nFlags);
}

void CGXAdoRecordWnd::OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!ProcessKeys(this, WM_SYSCHAR, nChar, nRepCnt, nFlags))
		CWnd::OnSysChar(nChar, nRepCnt, nFlags);
	nChar, nRepCnt, nFlags;
}

void CGXAdoRecordWnd::OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!ProcessKeys(this, WM_SYSKEYUP, nChar, nRepCnt, nFlags))
		CWnd::OnSysKeyUp(nChar, nRepCnt, nFlags);
	nChar, nRepCnt, nFlags;
}

void CGXAdoRecordWnd::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!ProcessKeys(this, WM_CHAR, nChar, nRepCnt, nFlags))
		CWnd::OnChar(nChar, nRepCnt, nFlags);
}

void CGXAdoRecordWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	CWnd* pFocus = GetFocus();
	if (pFocus != this && (pFocus == NULL || !IsChild(pFocus)))
		SetFocus();

	if (!DoLButtonDown(nFlags, point))
		CWnd::OnLButtonDown(nFlags, point);
}

void CGXAdoRecordWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (!DoLButtonUp(nFlags, point))
		CWnd::OnLButtonUp(nFlags, point);
}

void CGXAdoRecordWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	if (!DoMouseMove(nFlags, point))
		CWnd::OnMouseMove(nFlags, point);
}

void CGXAdoRecordWnd::OnLButtonDblClk(UINT flags, CPoint point)
{
	if (!DoLButtonDblClk(flags, point))
		CWnd::OnLButtonDblClk(flags, point);
}

void CGXAdoRecordWnd::OnMButtonDblClk(UINT flags, CPoint point)
{
	if (!DoMButtonDblClk(flags, point))
		CWnd::OnMButtonDblClk(flags, point);
}

void CGXAdoRecordWnd::OnMButtonDown(UINT flags, CPoint point)
{
	if (!DoMButtonDown(flags, point))
		CWnd::OnMButtonDown(flags, point);
}

void CGXAdoRecordWnd::OnMButtonUp(UINT flags, CPoint point)
{
	if (!DoMButtonUp(flags, point))
		CWnd::OnMButtonUp(flags, point);
}

void CGXAdoRecordWnd::OnRButtonDblClk(UINT flags, CPoint point)
{
	if (!DoRButtonDblClk(flags, point))
		CWnd::OnRButtonDblClk(flags, point);
}

void CGXAdoRecordWnd::OnRButtonDown(UINT flags, CPoint point)
{
	if (!DoRButtonDown(flags, point))
		CWnd::OnRButtonDown(flags, point);
}

void CGXAdoRecordWnd::OnRButtonUp(UINT flags, CPoint point)
{
	if (!DoRButtonUp(flags, point))
		CWnd::OnRButtonUp(flags, point);
}

BOOL CGXAdoRecordWnd::OnEraseBkgnd(CDC* /*pDC*/)
{
	return TRUE;
}

BOOL CGXAdoRecordWnd::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	if (DoSetCursor(pWnd, nHitTest, message))
		return TRUE;
	return CWnd::OnSetCursor(pWnd, nHitTest, message);
}

void CGXAdoRecordWnd::OnSize(UINT nType, int cx, int cy)
{
	if (!DoSize(nType, cx, cy))
		CWnd::OnSize(nType, cx, cy);
}

void CGXAdoRecordWnd::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CWnd::OnShowWindow(bShow, nStatus);
	DoShowWindow(bShow, nStatus);
}

void CGXAdoRecordWnd::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (!DoVScroll(nSBCode, nPos, pScrollBar))
		CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CGXAdoRecordWnd::OnSetFocus(CWnd* pOldWnd)
{
	CWnd::OnSetFocus(pOldWnd);
	OnGridSetFocus(pOldWnd);
}

void CGXAdoRecordWnd::OnKillFocus(CWnd* pNewWnd)
{
	CWnd::OnKillFocus(pNewWnd);
	OnGridKillFocus(pNewWnd);
}

UINT CGXAdoRecordWnd::OnGetDlgCode()
{
	return DoGetDlgCode(CWnd::OnGetDlgCode());
}

void CGXAdoRecordWnd::OnCancelMode()
{
	DoCancelMode();
}

int CGXAdoRecordWnd::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	int retval;

	if (DoMouseActivate(pDesktopWnd, nHitTest, message, retval))
		return retval;

	return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

BOOL CGXAdoRecordWnd::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if (DoCommand(wParam, lParam))
		return TRUE;

	return CWnd::OnCommand(wParam, lParam);
}

BOOL CGXAdoRecordWnd::PreTranslateMessage(MSG* pMsg)
{
	if (OnGridPreTranslateMessage(pMsg))
		return TRUE;

	return CWnd::PreTranslateMessage(pMsg);
}

LRESULT CGXAdoRecordWnd::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	LRESULT result;

	if (OnGridWindowProc(message, wParam, lParam, result))
		return result;

	return CWnd::WindowProc(message, wParam, lParam);
}

void CGXAdoRecordWnd::OnWinIniChange(LPCTSTR lpszSection)
{
	OnGridWinIniChange(lpszSection);
	CWnd::OnWinIniChange(lpszSection);
}

void CGXAdoRecordWnd::OnSysColorChange()
{
	OnGridSysColorChange();
	CWnd::OnSysColorChange();
}

void CGXAdoRecordWnd::OnTimer(SEC_UINT nIDEvent)
{
	OnGridTimer(nIDEvent);

	CWnd::OnTimer(nIDEvent);
}

/////////////////////////////////////////////////////////////////////////////
// CGXAdoRecordWnd printing

void CGXAdoRecordWnd::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	OnGridBeginPrinting(pDC, pInfo);
}

void CGXAdoRecordWnd::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	OnGridEndPrinting(pDC, pInfo);
}

void CGXAdoRecordWnd::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	OnGridPrint(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CGXAdoRecordWnd diagnostics

#ifdef _DEBUG
void CGXAdoRecordWnd::AssertValid() const
{
	CWnd::AssertValid();
	CGXAdoGrid::AssertValid();
}

void CGXAdoRecordWnd::Dump(CDumpContext& dc) const
{
	CWnd::Dump(dc);
	CGXAdoGrid::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGXAdoRecordWnd message handlers

void CGXAdoRecordWnd::OnUpdateRecordFirst(CCmdUI* pCmdUI)
{
	CGXAdoGrid::OnUpdateRecordFirst(pCmdUI);
}

void CGXAdoRecordWnd::OnUpdateRecordPrev(CCmdUI* pCmdUI)
{
	CGXAdoGrid::OnUpdateRecordPrev(pCmdUI);
}

void CGXAdoRecordWnd::OnUpdateRecordNext(CCmdUI* pCmdUI)
{
	CGXAdoGrid::OnUpdateRecordNext(pCmdUI);
}

void CGXAdoRecordWnd::OnUpdateRecordLast(CCmdUI* pCmdUI)
{
	CGXAdoGrid::OnUpdateRecordLast(pCmdUI);
}

void CGXAdoRecordWnd::OnUpdateEditUndorecord(CCmdUI* pCmdUI)
{
	CGXAdoGrid::OnUpdateEditUndorecord(pCmdUI);
}

void CGXAdoRecordWnd::OnEditUndorecord()
{
	CGXAdoGrid::OnEditUndorecord();
}

void CGXAdoRecordWnd::OnRecordDelete()
{
	CGXAdoGrid::OnRecordDelete();
}

void CGXAdoRecordWnd::OnUpdateRecordDelete(CCmdUI* pCmdUI)
{
	CGXAdoGrid::OnUpdateRecordDelete(pCmdUI);
}

BOOL CGXAdoRecordWnd::OnMove(UINT nIDMoveCommand)
{
	return CGXAdoGrid::OnMove(nIDMoveCommand);
}

void CGXAdoRecordWnd::OnView100()
{
	SetZoom(100);
}

void CGXAdoRecordWnd::OnViewZoomin()
{
	if (GetZoom() < 300)
		SetZoom(GetZoom()*11/10);
}

void CGXAdoRecordWnd::OnViewZoomout()
{
	if (GetZoom() > 40)
		SetZoom(GetZoom()*10/11);
}

void CGXAdoRecordWnd::OnUpdateViewZoomin(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(GetParam() && GetZoom() < 300);
}

void CGXAdoRecordWnd::OnUpdateViewZoomout(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(GetParam() && GetZoom() > 40);
}

/////////////////////////////////////////////////////////////////////////////
// Freeze Rows and Columns menu handlers

void CGXAdoRecordWnd::OnFormatFreezecols()
{
	FreezeCols();
}

void CGXAdoRecordWnd::OnFormatUnfreezecols()
{
	UnfreezeCols();
}

void CGXAdoRecordWnd::OnUpdateFormatFreezecols(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(CanFreezeCols());
}

void CGXAdoRecordWnd::OnUpdateFormatUnfreezecols(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(CanUnfreezeCols());
}

LPARAM CGXAdoRecordWnd::OnAdoRequery(WPARAM /*wParam*/, LPARAM /*lParam*/)
{
//	TRACE0("OnAdoRequery called.\n");
	BOOL bLock = LockUpdate();

	SetTopRow(1);
	MoveCurrentCell(GX_TOPLEFT);

	Requery();

	LockUpdate(bLock);
	Redraw();
	return 0;
}
#endif // ndef _GX_NO_ADO_SUPPORT
