///////////////////////////////////////////////////////////////////////////////
// gxdavw.cpp : implementation of CGXDaoRecordView class
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

// compile this file only if DAO is supported
#if _MFC_VER >= 0x0400 && !defined(_AFX_NO_DAO_SUPPORT)

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

#ifndef _GXDAO_H_
#include "grid\gxdao.h"
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif


#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXDAWND")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

static UINT NEAR wm_Find = RegisterWindowMessage( FINDMSGSTRING );

/////////////////////////////////////////////////////////////////////////////
// CGXDaoRecordWnd

IMPLEMENT_DYNCREATE(CGXDaoRecordWnd, CWnd)
GRID_IMPLEMENT_REGISTER(CGXDaoRecordWnd, CS_DBLCLKS | GX_GLOBALCLASS, 0, 0, 0)

CGXDaoRecordWnd::CGXDaoRecordWnd()
{
	SetGridWnd(this);
}

BOOL CGXDaoRecordWnd::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	return CWnd::Create(_T("GxWnd"), NULL,
		dwStyle | WS_CHILD,
		rect, pParentWnd, nID);
}

#if _MFC_VER < 0x0300
WNDPROC* CGXDaoRecordWnd::GetSuperWndProcAddr()
{
	// Note: it is no longer necessary to override GetSuperWndProcAddr
	//  for each control class with a different WNDCLASS.
	//  This implementation now uses instance data, such that the previous
	//  WNDPROC can be anything.

	static WNDPROC NEAR pfnSuper;
	return &pfnSuper;
}
#endif

BEGIN_MESSAGE_MAP(CGXDaoRecordWnd, CWnd)
	//{{AFX_MSG_MAP(CGXDaoRecordWnd)
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
	ON_REGISTERED_MESSAGE(wm_Find, OnFindReplaceCmd)
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
// CGXDaoRecordWnd initialization

void CGXDaoRecordWnd::Initialize()
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

void CGXDaoRecordWnd::OnInitialUpdate()
{
	OnGridInitialUpdate();
}

/////////////////////////////////////////////////////////////////////////////
// CGXDaoRecordWnd support for CGXTabWnd/CGXDaoRecordInfoWnd

#define _GXGetDlgCtrlID(hWnd)          ((UINT)(WORD)::GetDlgCtrlID(hWnd))

UINT AFXAPI CGXDaoRecordWnd::GetParentTabViewID(const CWnd* pWnd)
{
	UINT nID = _GXGetDlgCtrlID(pWnd->GetSafeHwnd());
	ASSERT(nID >= AFX_IDW_PANE_FIRST && nID < AFX_IDW_PANE_LAST);
	return nID-AFX_IDW_PANE_FIRST;
}

CScrollBar* CGXDaoRecordWnd::GetScrollBarCtrl(int nBar) const
{
	CScrollBar* pBar = DoGetScrollBarCtrl(nBar);
	if (pBar != NULL)
		return pBar;

	return CWnd::GetScrollBarCtrl(nBar);
}

LRESULT CGXDaoRecordWnd::OnChangedTab(WPARAM wParam, LPARAM /*lParam*/)
{
	OnTabChanged((int) wParam);

	return 0;
}

LRESULT CGXDaoRecordWnd::OnNeedChangeTab(WPARAM /*wParam*/, LPARAM /*lParam*/)
{
	return CanChangeTab();
}

LRESULT CGXDaoRecordWnd::OnCanActivate(WPARAM wParam, LPARAM /*lParam*/)
{
	BOOL bCanActivate = CanActivateGrid((BOOL) wParam);

	// Please note:
	// activation is allowed when return value is 0
	// activation is disabled when return value is 1
	return bCanActivate ? 0 : 1;
}

LRESULT CGXDaoRecordWnd::OnMoveRecord(WPARAM wParam, LPARAM lParam)
{
	SetFocus();
	OnInfoWndMoveRecord((int) wParam, (long) lParam);
	return 0;
}

LRESULT CGXDaoRecordWnd::OnLockResize(WPARAM wParam, LPARAM )
{
	LockResize((BOOL) wParam);
	return 0;
}

LRESULT CGXDaoRecordWnd::OnFindReplaceCmd(WPARAM, LPARAM lParam)
{
	ASSERT_VALID(this);
	CFindReplaceDialog* pDialog = CFindReplaceDialog::GetNotifier(lParam);

	OnFindReplace(pDialog);

	ASSERT_VALID(this);
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CGXDaoRecordWnd message handlers

void CGXDaoRecordWnd::OnPaint()
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

HBRUSH CGXDaoRecordWnd::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	return DoCtlColor(pDC, pWnd, nCtlColor);
}

void CGXDaoRecordWnd::OnDestroy()
{
	if (!DoNotifyDestroy())
		CWnd::OnDestroy();
}

void CGXDaoRecordWnd::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (!DoHScroll(nSBCode, nPos, pScrollBar))
		CWnd::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CGXDaoRecordWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!ProcessKeys(this, WM_KEYDOWN, nChar, nRepCnt, nFlags))
		CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CGXDaoRecordWnd::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!ProcessKeys(this, WM_KEYUP, nChar, nRepCnt, nFlags))
		CWnd::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CGXDaoRecordWnd::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!ProcessKeys(this, WM_SYSKEYDOWN, nChar, nRepCnt, nFlags))
		CWnd::OnSysKeyDown(nChar, nRepCnt, nFlags);
}

void CGXDaoRecordWnd::OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!ProcessKeys(this, WM_SYSCHAR, nChar, nRepCnt, nFlags))
		CWnd::OnSysChar(nChar, nRepCnt, nFlags);
	nChar, nRepCnt, nFlags;
}

void CGXDaoRecordWnd::OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!ProcessKeys(this, WM_SYSKEYUP, nChar, nRepCnt, nFlags))
		CWnd::OnSysKeyUp(nChar, nRepCnt, nFlags);
	nChar, nRepCnt, nFlags;
}

void CGXDaoRecordWnd::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!ProcessKeys(this, WM_CHAR, nChar, nRepCnt, nFlags))
		CWnd::OnChar(nChar, nRepCnt, nFlags);
}

void CGXDaoRecordWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	CWnd* pFocus = GetFocus();
	if (pFocus != this && (pFocus == NULL || !IsChild(pFocus)))
		SetFocus();

	if (!DoLButtonDown(nFlags, point))
		CWnd::OnLButtonDown(nFlags, point);
}

void CGXDaoRecordWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (!DoLButtonUp(nFlags, point))
		CWnd::OnLButtonUp(nFlags, point);
}

void CGXDaoRecordWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	if (!DoMouseMove(nFlags, point))
		CWnd::OnMouseMove(nFlags, point);
}

void CGXDaoRecordWnd::OnLButtonDblClk(UINT flags, CPoint point)
{
	if (!DoLButtonDblClk(flags, point))
		CWnd::OnLButtonDblClk(flags, point);
}

void CGXDaoRecordWnd::OnMButtonDblClk(UINT flags, CPoint point)
{
	if (!DoMButtonDblClk(flags, point))
		CWnd::OnMButtonDblClk(flags, point);
}

void CGXDaoRecordWnd::OnMButtonDown(UINT flags, CPoint point)
{
	if (!DoMButtonDown(flags, point))
		CWnd::OnMButtonDown(flags, point);
}

void CGXDaoRecordWnd::OnMButtonUp(UINT flags, CPoint point)
{
	if (!DoMButtonUp(flags, point))
		CWnd::OnMButtonUp(flags, point);
}

void CGXDaoRecordWnd::OnRButtonDblClk(UINT flags, CPoint point)
{
	if (!DoRButtonDblClk(flags, point))
		CWnd::OnRButtonDblClk(flags, point);
}

void CGXDaoRecordWnd::OnRButtonDown(UINT flags, CPoint point)
{
	if (!DoRButtonDown(flags, point))
		CWnd::OnRButtonDown(flags, point);
}

void CGXDaoRecordWnd::OnRButtonUp(UINT flags, CPoint point)
{
	if (!DoRButtonUp(flags, point))
		CWnd::OnRButtonUp(flags, point);
}

BOOL CGXDaoRecordWnd::OnEraseBkgnd(CDC* /*pDC*/)
{
	return TRUE;
}

BOOL CGXDaoRecordWnd::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	if (DoSetCursor(pWnd, nHitTest, message))
		return TRUE;
	return CWnd::OnSetCursor(pWnd, nHitTest, message);
}

void CGXDaoRecordWnd::OnSize(UINT nType, int cx, int cy)
{
	if (!DoSize(nType, cx, cy))
		CWnd::OnSize(nType, cx, cy);
}

void CGXDaoRecordWnd::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CWnd::OnShowWindow(bShow, nStatus);
	DoShowWindow(bShow, nStatus);
}

void CGXDaoRecordWnd::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (!DoVScroll(nSBCode, nPos, pScrollBar))
		CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CGXDaoRecordWnd::OnSetFocus(CWnd* pOldWnd)
{
	CWnd::OnSetFocus(pOldWnd);
	OnGridSetFocus(pOldWnd);
}

void CGXDaoRecordWnd::OnKillFocus(CWnd* pNewWnd)
{
	CWnd::OnKillFocus(pNewWnd);
	OnGridKillFocus(pNewWnd);
}

UINT CGXDaoRecordWnd::OnGetDlgCode()
{
	return DoGetDlgCode(CWnd::OnGetDlgCode());
}

void CGXDaoRecordWnd::OnCancelMode()
{
	DoCancelMode();
}

int CGXDaoRecordWnd::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	int retval;

	if (DoMouseActivate(pDesktopWnd, nHitTest, message, retval))
		return retval;

	return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

BOOL CGXDaoRecordWnd::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if (DoCommand(wParam, lParam))
		return TRUE;

	return CWnd::OnCommand(wParam, lParam);
}

BOOL CGXDaoRecordWnd::PreTranslateMessage(MSG* pMsg)
{
	if (OnGridPreTranslateMessage(pMsg))
		return TRUE;

	return CWnd::PreTranslateMessage(pMsg);
}

LRESULT CGXDaoRecordWnd::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	LRESULT result;

	if (OnGridWindowProc(message, wParam, lParam, result))
		return result;

	return CWnd::WindowProc(message, wParam, lParam);
}

void CGXDaoRecordWnd::OnWinIniChange(LPCTSTR lpszSection)
{
	OnGridWinIniChange(lpszSection);
	CWnd::OnWinIniChange(lpszSection);
}

void CGXDaoRecordWnd::OnSysColorChange()
{
	OnGridSysColorChange();
	CWnd::OnSysColorChange();
}

void CGXDaoRecordWnd::OnTimer(SEC_UINT nIDEvent)
{
	OnGridTimer(nIDEvent);

	CWnd::OnTimer(nIDEvent);
}

/////////////////////////////////////////////////////////////////////////////
// CGXDaoRecordWnd printing

void CGXDaoRecordWnd::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	OnGridBeginPrinting(pDC, pInfo);
}

void CGXDaoRecordWnd::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	OnGridEndPrinting(pDC, pInfo);
}

void CGXDaoRecordWnd::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	OnGridPrint(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CGXDaoRecordWnd diagnostics

#ifdef _DEBUG
void CGXDaoRecordWnd::AssertValid() const
{
	CWnd::AssertValid();
	CGXDaoGrid::AssertValid();
}

void CGXDaoRecordWnd::Dump(CDumpContext& dc) const
{
	CWnd::Dump(dc);
	CGXDaoGrid::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGXDaoRecordWnd message handlers

void CGXDaoRecordWnd::OnUpdateRecordFirst(CCmdUI* pCmdUI)
{
	CGXDaoGrid::OnUpdateRecordFirst(pCmdUI);
}

void CGXDaoRecordWnd::OnUpdateRecordPrev(CCmdUI* pCmdUI)
{
	CGXDaoGrid::OnUpdateRecordPrev(pCmdUI);
}

void CGXDaoRecordWnd::OnUpdateRecordNext(CCmdUI* pCmdUI)
{
	CGXDaoGrid::OnUpdateRecordNext(pCmdUI);
}

void CGXDaoRecordWnd::OnUpdateRecordLast(CCmdUI* pCmdUI)
{
	CGXDaoGrid::OnUpdateRecordLast(pCmdUI);
}

void CGXDaoRecordWnd::OnUpdateEditUndorecord(CCmdUI* pCmdUI)
{
	CGXDaoGrid::OnUpdateEditUndorecord(pCmdUI);
}

void CGXDaoRecordWnd::OnEditUndorecord()
{
	CGXDaoGrid::OnEditUndorecord();
}

void CGXDaoRecordWnd::OnRecordDelete()
{
	CGXDaoGrid::OnRecordDelete();
}

void CGXDaoRecordWnd::OnUpdateRecordDelete(CCmdUI* pCmdUI)
{
	CGXDaoGrid::OnUpdateRecordDelete(pCmdUI);
}

BOOL CGXDaoRecordWnd::OnMove(UINT nIDMoveCommand)
{
	return CGXDaoGrid::OnMove(nIDMoveCommand);
}

void CGXDaoRecordWnd::OnView100()
{
	SetZoom(100);
}

void CGXDaoRecordWnd::OnViewZoomin()
{
	if (GetZoom() < 300)
		SetZoom(GetZoom()*11/10);
}

void CGXDaoRecordWnd::OnViewZoomout()
{
	if (GetZoom() > 40)
		SetZoom(GetZoom()*10/11);
}

void CGXDaoRecordWnd::OnUpdateViewZoomin(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(GetParam() && GetZoom() < 300);
}

void CGXDaoRecordWnd::OnUpdateViewZoomout(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(GetParam() && GetZoom() > 40);
}

/////////////////////////////////////////////////////////////////////////////
// Freeze Rows and Columns menu handlers

void CGXDaoRecordWnd::OnFormatFreezecols()
{
	FreezeCols();
}

void CGXDaoRecordWnd::OnFormatUnfreezecols()
{
	UnfreezeCols();
}

void CGXDaoRecordWnd::OnUpdateFormatFreezecols(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(CanFreezeCols());
}

void CGXDaoRecordWnd::OnUpdateFormatUnfreezecols(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(CanUnfreezeCols());
}

#endif // ndef _AFX_NO_DAO_SUPPORT
