///////////////////////////////////////////////////////////////////////////////
// gxdbwnd.cpp : implementation of the CGXRecordWnd class
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


// compile this file only if ODBC is supported
#ifndef _AFX_NO_DB_SUPPORT

#ifdef _GXDLL
// used for MFC 2.5 Extension DLL
	#undef AFXAPI_DATA
	#define AFXAPI_DATA __based(__segname("_DATA"))
#endif

// Headers 

#ifndef _GXRESRC_H_
#include "grid\gxresrc.h"
#endif

#ifndef _GXBROWSE_H_
#include "grid\gxbrowse.h"
#endif

#ifndef _GXWND_H_
#include "grid\gxwnd.h"
#endif

#ifndef _GXMSG_H_
#include "grid\gxmsg.h"
#endif

#ifndef _GXODBC_H_
//#ifndef _WIN64 //RW64
#include "grid\gxodbc.h"
//#endif //_WIN64
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXDBWND")
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXDBWND")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CGXRecordWnd, CWnd)
GRID_IMPLEMENT_REGISTER(CGXRecordWnd, CS_DBLCLKS | GX_GLOBALCLASS, 0, 0, 0)

static UINT NEAR wm_Find = RegisterWindowMessage( FINDMSGSTRING );

/////////////////////////////////////////////////////////////////////////////
// CGXRecordWnd

CGXRecordWnd::CGXRecordWnd()
{
	SetGridWnd(this);
}

BOOL CGXRecordWnd::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	return CWnd::Create(_T("GxWnd"), NULL,
		dwStyle | WS_CHILD,
		rect, pParentWnd, nID);
}

#if _MFC_VER < 0x0300
WNDPROC* CGXRecordWnd::GetSuperWndProcAddr()
{
	// Note: it is no longer necessary to override GetSuperWndProcAddr
	//  for each control class with a different WNDCLASS.
	//  This implementation now uses instance data, such that the previous
	//  WNDPROC can be anything.

	static WNDPROC NEAR pfnSuper;
	return &pfnSuper;
}
#endif

BEGIN_MESSAGE_MAP(CGXRecordWnd, CWnd)
	//{{AFX_MSG_MAP(CGXRecordWnd)
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
	ON_REGISTERED_MESSAGE(wm_Find, OnFindReplaceCmd)
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
// CGXRecordWnd initialization

void CGXRecordWnd::Initialize()
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

void CGXRecordWnd::OnInitialUpdate()
{
	OnGridInitialUpdate();
}

/////////////////////////////////////////////////////////////////////////////
// CGXRecordWnd support for CGXTabWnd/CGXRecordInfoWnd

#define _GXGetDlgCtrlID(hWnd)          ((UINT)(WORD)::GetDlgCtrlID(hWnd))

UINT AFXAPI CGXRecordWnd::GetParentTabViewID(const CWnd* pWnd)
{
	UINT nID = _GXGetDlgCtrlID(pWnd->GetSafeHwnd());
	ASSERT(nID >= AFX_IDW_PANE_FIRST && nID < AFX_IDW_PANE_LAST);
	return nID-AFX_IDW_PANE_FIRST;
}

CScrollBar* CGXRecordWnd::GetScrollBarCtrl(int nBar) const
{
	CScrollBar* pBar = DoGetScrollBarCtrl(nBar);
	if (pBar != NULL)
		return pBar;

	return CWnd::GetScrollBarCtrl(nBar);
}

LRESULT CGXRecordWnd::OnChangedTab(WPARAM wParam, LPARAM /*lParam*/)
{
	OnTabChanged((int) wParam);

	return 0;
}

LRESULT CGXRecordWnd::OnNeedChangeTab(WPARAM /*wParam*/, LPARAM /*lParam*/)
{
	return CanChangeTab();
}

LRESULT CGXRecordWnd::OnCanActivate(WPARAM wParam, LPARAM /*lParam*/)
{
	BOOL bCanActivate = CanActivateGrid((BOOL) wParam);

	// Please note:
	// activation is allowed when return value is 0
	// activation is disabled when return value is 1
	return bCanActivate ? 0 : 1;
}

LRESULT CGXRecordWnd::OnLockResize(WPARAM wParam, LPARAM )
{
	LockResize((BOOL) wParam);
	return 0;
}

LRESULT CGXRecordWnd::OnMoveRecord(WPARAM wParam, LPARAM lParam)
{
	SetFocus();
	OnInfoWndMoveRecord((int) wParam, (long) lParam);
	return 0;
}

LRESULT CGXRecordWnd::OnFindReplaceCmd(WPARAM, LPARAM lParam)
{
	ASSERT_VALID(this);
	CFindReplaceDialog* pDialog = CFindReplaceDialog::GetNotifier(lParam);

	OnFindReplace(pDialog);

	ASSERT_VALID(this);
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CGXRecordWnd message handlers

void CGXRecordWnd::OnPaint()
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

HBRUSH CGXRecordWnd::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	return DoCtlColor(pDC, pWnd, nCtlColor);
}

void CGXRecordWnd::OnDestroy()
{
	if (!DoNotifyDestroy())
		CWnd::OnDestroy();
}

void CGXRecordWnd::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (!DoHScroll(nSBCode, nPos, pScrollBar))
		CWnd::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CGXRecordWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!ProcessKeys(this, WM_KEYDOWN, nChar, nRepCnt, nFlags))
		CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CGXRecordWnd::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!ProcessKeys(this, WM_KEYUP, nChar, nRepCnt, nFlags))
		CWnd::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CGXRecordWnd::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!ProcessKeys(this, WM_SYSKEYDOWN, nChar, nRepCnt, nFlags))
		CWnd::OnSysKeyDown(nChar, nRepCnt, nFlags);
}

void CGXRecordWnd::OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!ProcessKeys(this, WM_SYSCHAR, nChar, nRepCnt, nFlags))
		CWnd::OnSysChar(nChar, nRepCnt, nFlags);
	nChar, nRepCnt, nFlags;
}

void CGXRecordWnd::OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!ProcessKeys(this, WM_SYSKEYUP, nChar, nRepCnt, nFlags))
		CWnd::OnSysKeyUp(nChar, nRepCnt, nFlags);
	nChar, nRepCnt, nFlags;
}

void CGXRecordWnd::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!ProcessKeys(this, WM_CHAR, nChar, nRepCnt, nFlags))
		CWnd::OnChar(nChar, nRepCnt, nFlags);
}

void CGXRecordWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	CWnd* pFocus = GetFocus();
	if (pFocus != this && (pFocus == NULL || !IsChild(pFocus)))
		SetFocus();

	if (!DoLButtonDown(nFlags, point))
		CWnd::OnLButtonDown(nFlags, point);
}

void CGXRecordWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (!DoLButtonUp(nFlags, point))
		CWnd::OnLButtonUp(nFlags, point);
}

void CGXRecordWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	if (!DoMouseMove(nFlags, point))
		CWnd::OnMouseMove(nFlags, point);
}

void CGXRecordWnd::OnLButtonDblClk(UINT flags, CPoint point)
{
	if (!DoLButtonDblClk(flags, point))
		CWnd::OnLButtonDblClk(flags, point);
}

void CGXRecordWnd::OnMButtonDblClk(UINT flags, CPoint point)
{
	if (!DoMButtonDblClk(flags, point))
		CWnd::OnMButtonDblClk(flags, point);
}

void CGXRecordWnd::OnMButtonDown(UINT flags, CPoint point)
{
	if (!DoMButtonDown(flags, point))
		CWnd::OnMButtonDown(flags, point);
}

void CGXRecordWnd::OnMButtonUp(UINT flags, CPoint point)
{
	if (!DoMButtonUp(flags, point))
		CWnd::OnMButtonUp(flags, point);
}

void CGXRecordWnd::OnRButtonDblClk(UINT flags, CPoint point)
{
	if (!DoRButtonDblClk(flags, point))
		CWnd::OnRButtonDblClk(flags, point);
}

void CGXRecordWnd::OnRButtonDown(UINT flags, CPoint point)
{
	if (!DoRButtonDown(flags, point))
		CWnd::OnRButtonDown(flags, point);
}

void CGXRecordWnd::OnRButtonUp(UINT flags, CPoint point)
{
	if (!DoRButtonUp(flags, point))
		CWnd::OnRButtonUp(flags, point);
}

BOOL CGXRecordWnd::OnEraseBkgnd(CDC* /*pDC*/)
{
	return TRUE;
}

BOOL CGXRecordWnd::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	if (DoSetCursor(pWnd, nHitTest, message))
		return TRUE;
	return CWnd::OnSetCursor(pWnd, nHitTest, message);
}

void CGXRecordWnd::OnSize(UINT nType, int cx, int cy)
{
	if (!DoSize(nType, cx, cy))
		CWnd::OnSize(nType, cx, cy);
}

void CGXRecordWnd::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CWnd::OnShowWindow(bShow, nStatus);
	DoShowWindow(bShow, nStatus);
}

void CGXRecordWnd::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (!DoVScroll(nSBCode, nPos, pScrollBar))
		CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CGXRecordWnd::OnSetFocus(CWnd* pOldWnd)
{
	CWnd::OnSetFocus(pOldWnd);
	OnGridSetFocus(pOldWnd);
}

void CGXRecordWnd::OnKillFocus(CWnd* pNewWnd)
{
	CWnd::OnKillFocus(pNewWnd);
	OnGridKillFocus(pNewWnd);
}

UINT CGXRecordWnd::OnGetDlgCode()
{
	return DoGetDlgCode(CWnd::OnGetDlgCode());
}

void CGXRecordWnd::OnCancelMode()
{
	// TRACE0("OnCancelMode\n");
	DoCancelMode();
}

int CGXRecordWnd::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	int retval;

	if (DoMouseActivate(pDesktopWnd, nHitTest, message, retval))
		return retval;

	return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

BOOL CGXRecordWnd::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if (DoCommand(wParam, lParam))
		return TRUE;

	return CWnd::OnCommand(wParam, lParam);
}

BOOL CGXRecordWnd::PreTranslateMessage(MSG* pMsg)
{
	if (OnGridPreTranslateMessage(pMsg))
		return TRUE;

	return CWnd::PreTranslateMessage(pMsg);
}

LRESULT CGXRecordWnd::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	LRESULT result;

	if (OnGridWindowProc(message, wParam, lParam, result))
		return result;

	return CWnd::WindowProc(message, wParam, lParam);
}

void CGXRecordWnd::OnWinIniChange(LPCTSTR lpszSection)
{
	OnGridWinIniChange(lpszSection);
	CWnd::OnWinIniChange(lpszSection);
}

void CGXRecordWnd::OnSysColorChange()
{
	OnGridSysColorChange();
	CWnd::OnSysColorChange();
}

void CGXRecordWnd::OnTimer(SEC_UINT nIDEvent)
{
	OnGridTimer(nIDEvent);

	CWnd::OnTimer(nIDEvent);
}

/////////////////////////////////////////////////////////////////////////////
// CGXRecordWnd printing

void CGXRecordWnd::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	OnGridBeginPrinting(pDC, pInfo);
}

void CGXRecordWnd::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	OnGridEndPrinting(pDC, pInfo);
}

void CGXRecordWnd::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	OnGridPrint(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CGXRecordWnd diagnostics

#ifdef _DEBUG
void CGXRecordWnd::AssertValid() const
{
	CWnd::AssertValid();
	CGXODBCGrid::AssertValid();
}

void CGXRecordWnd::Dump(CDumpContext& dc) const
{
	CWnd::Dump(dc);
	CGXODBCGrid::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGXRecordWnd message handlers

void CGXRecordWnd::OnUpdateRecordFirst(CCmdUI* pCmdUI)
{
	CGXODBCGrid::OnUpdateRecordFirst(pCmdUI);
}

void CGXRecordWnd::OnUpdateRecordPrev(CCmdUI* pCmdUI)
{
	CGXODBCGrid::OnUpdateRecordPrev(pCmdUI);
}

void CGXRecordWnd::OnUpdateRecordNext(CCmdUI* pCmdUI)
{
	CGXODBCGrid::OnUpdateRecordNext(pCmdUI);
}

void CGXRecordWnd::OnUpdateRecordLast(CCmdUI* pCmdUI)
{
	CGXODBCGrid::OnUpdateRecordLast(pCmdUI);
}

void CGXRecordWnd::OnUpdateEditUndorecord(CCmdUI* pCmdUI)
{
	CGXODBCGrid::OnUpdateEditUndorecord(pCmdUI);
}

void CGXRecordWnd::OnEditUndorecord()
{
	CGXODBCGrid::OnEditUndorecord();
}

void CGXRecordWnd::OnRecordDelete()
{
	CGXODBCGrid::OnRecordDelete();
}

void CGXRecordWnd::OnUpdateRecordDelete(CCmdUI* pCmdUI)
{
	CGXODBCGrid::OnUpdateRecordDelete(pCmdUI);
}

BOOL CGXRecordWnd::OnMove(UINT nIDMoveCommand)
{
	return CGXODBCGrid::OnMove(nIDMoveCommand);
}

void CGXRecordWnd::OnView100()
{
	SetZoom(100);
}

void CGXRecordWnd::OnViewZoomin()
{
	if (GetZoom() < 300)
		SetZoom(GetZoom()*11/10);
}

void CGXRecordWnd::OnViewZoomout()
{
	if (GetZoom() > 40)
		SetZoom(GetZoom()*10/11);
}

void CGXRecordWnd::OnUpdateViewZoomin(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(GetParam() && GetZoom() < 300);
}

void CGXRecordWnd::OnUpdateViewZoomout(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(GetParam() && GetZoom() > 40);
}

/////////////////////////////////////////////////////////////////////////////
// Freeze Rows and Columns menu handlers

void CGXRecordWnd::OnFormatFreezecols()
{
	FreezeCols();
}

void CGXRecordWnd::OnFormatUnfreezecols()
{
	UnfreezeCols();
}

void CGXRecordWnd::OnUpdateFormatFreezecols(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(CanFreezeCols());
}

void CGXRecordWnd::OnUpdateFormatUnfreezecols(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(CanUnfreezeCols());
}

#endif // ndef _AFX_NO_DB_SUPPORT
