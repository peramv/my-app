///////////////////////////////////////////////////////////////////////////////
// gxdbvw.cpp : implementation of the CGXRecordView class
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

#ifndef _GXVW_H_
#include "grid\gxvw.h"
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
#pragma code_seg("GX_SEG_GXDBVW")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CGXRecordView, CGXView)

static UINT NEAR wm_Find = RegisterWindowMessage( FINDMSGSTRING );


/////////////////////////////////////////////////////////////////////////////
// CGXRecordView

BEGIN_MESSAGE_MAP(CGXRecordView, CGXView)
	//{{AFX_MSG_MAP(CGXRecordView)
	ON_UPDATE_COMMAND_UI(ID_RECORD_FIRST, OnUpdateRecordFirst)
	ON_UPDATE_COMMAND_UI(ID_RECORD_PREV, OnUpdateRecordPrev)
	ON_UPDATE_COMMAND_UI(ID_RECORD_NEXT, OnUpdateRecordNext)
	ON_UPDATE_COMMAND_UI(ID_RECORD_LAST, OnUpdateRecordLast)
	ON_WM_DESTROY()
	ON_WM_SETCURSOR()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_KEYDOWN()
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	ON_COMMAND(ID_EDIT_REDO, OnEditRedo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, OnUpdateEditRedo)
	ON_COMMAND(ID_EDIT_FIND, OnEditFind)
	ON_COMMAND(ID_EDIT_REPLACE, OnEditReplace)
	ON_COMMAND(ID_EDIT_REPEAT, OnEditRepeat)
	ON_REGISTERED_MESSAGE(wm_Find, OnFindReplaceCmd)
	ON_WM_SETFOCUS()
	ON_MESSAGE(WM_GX_NEEDCHANGETAB, OnNeedChangeTab)
	ON_MESSAGE(WM_GX_CHANGEDTAB, OnChangedTab)
	ON_MESSAGE(WM_GX_CANACTIVATE, OnCanActivate)
	ON_MESSAGE(WM_GX_MOVERECORD, OnMoveRecord)
	ON_MESSAGE(WM_GX_LOCKRESIZE, OnLockResize)
	ON_WM_CHAR()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_MBUTTONDBLCLK()
	ON_WM_CANCELMODE()
	ON_WM_SYSKEYDOWN()
	ON_WM_SHOWWINDOW()
	ON_WM_MOUSEACTIVATE()
	ON_WM_KEYUP()
	ON_WM_SYSKEYUP()
	ON_WM_SYSCHAR()
	ON_WM_PAINT()
	ON_WM_SYSCOLORCHANGE()
	ON_WM_TIMER()
	ON_COMMAND_EX(ID_RECORD_FIRST, OnMove)
	ON_COMMAND_EX(ID_RECORD_PREV, OnMove)
	ON_COMMAND_EX(ID_RECORD_NEXT, OnMove)
	ON_COMMAND_EX(ID_RECORD_LAST, OnMove)
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_WM_WININICHANGE()
	ON_COMMAND(ID_FILE_PRINT, CGXView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CGXView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGXRecordView construction/destruction

CGXRecordView::CGXRecordView()
{
	SetGridWnd(this);
}

CGXRecordView::~CGXRecordView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CGXRecordView initialization

void CGXRecordView::OnInitialUpdate()
{
	SetGridWnd(this, GetDocument(), TRUE);

	m_pSplitterWnd = GetParentDynamicSplitter(this, TRUE);

	// Commment: I have move the following lines before
	// CGXGridCore::OnGridInitialUpdate() so that scrollbars
	// can be initialized correctly.
	if (m_pSplitterWnd || GetSharedScrollbarParentWnd())
		SetScrollBarMode(SB_BOTH, gxnShared | gxnEnhanced);
	else
		SetScrollBarMode(SB_BOTH, gxnAutomatic | gxnEnhanced);

	OnGridInitialUpdate();
	CGXView::OnInitialUpdate();

	CGXGridParam* pParam = GetParam();

	// check print device
	if (GetPrintDevice() == NULL)
	{
		// is print device in parameter object?
		if (pParam->GetPrintDevice() == NULL)
			pParam->SetPrintDevice(new CGXPrintDevice);

		SetPrintDevice(pParam->GetPrintDevice(), FALSE);
	}

	// if this is a new pane in a dynamic splitter window
	// I will initialize top row or left column

	if (m_pSplitterWnd != NULL)
	{
		// [VC7] Substitute IsChildPane with macro.
		ASSERT(m_pSplitterWnd->IsKindOf(RUNTIME_CLASS(CSplitterWnd)));
		VERIFY(SPWND_ISCHILDPANE(m_pSplitterWnd, this, m_nSplitRow, m_nSplitCol));

		ASSERT(m_nSplitRow < 2);
		ASSERT(m_nSplitCol < 2);

		if (m_nSplitRow > 0 || m_nSplitCol > 0)
		{
			// copy settings from other pane
			CGXRecordView *pView;

			pView = (CGXRecordView *) m_pSplitterWnd->GetPane(0, 0);

			ASSERT(pView != NULL);
			ASSERT(pView->IsKindOf(RUNTIME_CLASS(CGXRecordView)));

			if (m_nSplitRow > 0)
			{
				pView = (CGXRecordView *) m_pSplitterWnd->GetPane(0, m_nSplitCol);

				ASSERT(pView != NULL);
				ASSERT(pView->IsKindOf(RUNTIME_CLASS(CGXRecordView)));

				m_nLeftCol = pView->m_nLeftCol;
				m_nTopRow = pView->m_nTopRow;
				m_bDisplayHeaderRow = FALSE;

				// disable smart redrawing of WM_SIZE message
				pView->m_cxOld = pView->m_cyOld = 0;
			}

			if (m_nSplitCol > 0)
			{
				pView = (CGXRecordView *) m_pSplitterWnd->GetPane(m_nSplitRow, 0);

				ASSERT(pView != NULL);
				ASSERT(pView->IsKindOf(RUNTIME_CLASS(CGXRecordView)));

				m_nTopRow = pView->m_nTopRow;
				if (m_nSplitRow == 0)
					m_nLeftCol = pView->m_nLeftCol;
				m_bDisplayHeaderCol = FALSE;

				// disable smart redrawing of WM_SIZE message
				pView->m_cxOld = pView->m_cyOld = 0;
			}

		}

		UpdateScrollbars();
	}
}

/////////////////////////////////////////////////////////////////////////////
// CGXRecordView support for CGXTabWnd/CGXRecordInfoWnd

LRESULT CGXRecordView::OnChangedTab(WPARAM wParam, LPARAM /*lParam*/)
{
	OnTabChanged((int) wParam);

	return 0;
}

LRESULT CGXRecordView::OnCanActivate(WPARAM wParam, LPARAM /*lParam*/)
{
	BOOL bCanActivate = CanActivateGrid((BOOL) wParam);

	// Please note:
	// activation is allowed when return value is 0
	// activation is disabled when return value is 1
	return bCanActivate ? 0 : 1;
}

LRESULT CGXRecordView::OnNeedChangeTab(WPARAM /*wParam*/, LPARAM /*lParam*/)
{
	return CanChangeTab();
}

LRESULT CGXRecordView::OnMoveRecord(WPARAM wParam, LPARAM lParam)
{
	OnInfoWndMoveRecord((int) wParam, (long) lParam);
	return 0;
}

LRESULT CGXRecordView::OnLockResize(WPARAM wParam, LPARAM )
{
	LockResize((BOOL) wParam);
	return 0;
}

CScrollBar* CGXRecordView::GetScrollBarCtrl(int nBar) const
{
	CScrollBar* pBar = DoGetScrollBarCtrl(nBar);
	if (pBar != NULL)
		return pBar;

	return CGXView::GetScrollBarCtrl(nBar);
}

/////////////////////////////////////////////////////////////////////////////
// CView overridable member functions

void CGXRecordView::OnActivateView( BOOL bActivate, CView* pActivateView, CView* pDeactiveView )
{
	if (bActivate != m_bActiveFrame && !GXDiscardNcActivate())
		OnActivateGrid(bActivate);
	CGXView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

void CGXRecordView::OnDraw(CDC* pDC)
{
	OnGridDraw(pDC);
}

void CGXRecordView::OnPrepareDC( CDC* pDC, CPrintInfo* pInfo /* = NULL */)
{
	OnGridPrepareDC(pDC, pInfo);
}

void CGXRecordView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	OnGridUpdate(pSender, lHint, pHint);
}

BOOL CGXRecordView::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if (DoCommand(wParam, lParam))
		return TRUE;

	return CGXView::OnCommand(wParam, lParam);
}

BOOL CGXRecordView::PreTranslateMessage(MSG* pMsg)
{
	if (OnGridPreTranslateMessage(pMsg))
		return TRUE;

	return CGXView::PreTranslateMessage(pMsg);
}

LRESULT CGXRecordView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result;

	if (OnGridWindowProc(message, wParam, lParam, result))
		return result;

	return CGXView::WindowProc(message, wParam, lParam);
}

/////////////////////////////////////////////////////////////////////////////
// CGXRecordView printing

BOOL CGXRecordView::OnPreparePrinting(CPrintInfo* pInfo)
{
	pInfo->SetMaxPage(0xffff);

	pInfo->m_pPD->m_pd.Flags &= ~PD_NOSELECTION;
	pInfo->m_pPD->m_pd.hInstance = AfxGetInstanceHandle();

	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGXRecordView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	OnGridBeginPrinting(pDC, pInfo);
}

void CGXRecordView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	OnGridEndPrinting(pDC, pInfo);
}

void CGXRecordView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	OnGridPrint(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CGXRecordView message handlers

void CGXRecordView::OnPaint()
{
	// standard paint routine
	if (!m_bInitDone)
	{
		TRACE0("Warning! You must call CGXRecordView::OnInitialUpdate()\n");
		ASSERT(0);        // You must call Initialize() in OnInitDialog!
		AfxThrowNotSupportedException();
	}

	CPaintDC dc(this);
	OnPrepareDC(&dc);
	OnDraw(&dc);
}

void CGXRecordView::OnDestroy()
{
	if (!DoNotifyDestroy())
		CGXView::OnDestroy();
}

void CGXRecordView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pBar)
{
	if (!DoVScroll(nSBCode, nPos, pBar))
		CGXView::OnVScroll(nSBCode, nPos, pBar);
}

void CGXRecordView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pBar)
{
	if (!DoHScroll(nSBCode, nPos, pBar))
		CGXView::OnHScroll(nSBCode, nPos, pBar);
}

BOOL CGXRecordView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	if (DoSetCursor(pWnd, nHitTest, message))
		return TRUE;
	return CView::OnSetCursor(pWnd, nHitTest, message);
}

void CGXRecordView::OnMouseMove(UINT flags, CPoint point)
{
	if (!DoMouseMove(flags, point))
		CGXView::OnMouseMove(flags, point);
}

int CGXRecordView::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// First, check out current control's
	int retval;

	if (DoMouseActivate(pDesktopWnd, nHitTest, message, retval))
		return retval;

	return CGXView::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

void CGXRecordView::OnLButtonDown(UINT flags, CPoint point)
{
	if (!DoLButtonDown(flags, point))
		CGXView::OnLButtonDown(flags, point);
}

void CGXRecordView::OnLButtonUp(UINT flags, CPoint point)
{
	if (!DoLButtonUp(flags, point))
		CGXView::OnLButtonUp(flags, point);
}


void CGXRecordView::OnRButtonDown(UINT flags, CPoint point)
{
	if (!DoRButtonDown(flags, point))
		CGXView::OnRButtonDown(flags, point);
}

void CGXRecordView::OnRButtonUp(UINT flags, CPoint point)
{
	if (!DoRButtonUp(flags, point))
		CGXView::OnRButtonUp(flags, point);
}

void CGXRecordView::OnLButtonDblClk(UINT flags, CPoint point)
{
	if (!DoLButtonDblClk(flags, point))
		CGXView::OnLButtonDblClk(flags, point);
}

void CGXRecordView::OnRButtonDblClk(UINT flags, CPoint point)
{
	if (!DoRButtonDblClk(flags, point))
		CGXView::OnRButtonDblClk(flags, point);
}

void CGXRecordView::OnMButtonDown(UINT flags, CPoint point)
{
	if (!DoMButtonDown(flags, point))
		CGXView::OnLButtonDown(flags, point);
}

void CGXRecordView::OnMButtonUp(UINT flags, CPoint point)
{
	if (!DoMButtonUp(flags, point))
		CGXView::OnMButtonUp(flags, point);
}

void CGXRecordView::OnMButtonDblClk(UINT flags, CPoint point)
{
	if (!DoMButtonDblClk(flags, point))
		CGXView::OnMButtonDblClk(flags, point);
}

BOOL CGXRecordView::OnEraseBkgnd(CDC* /*pDC*/)
{
	// I don't want the Screen to flicker!
	// Also, ...
	return TRUE;
}

void CGXRecordView::OnSize(UINT nType, int cx, int cy)
{
	if (!DoSize(nType, cx, cy))
		CGXView::OnSize(nType, cx, cy);
}

void CGXRecordView::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CGXView::OnShowWindow(bShow, nStatus);
	DoShowWindow(bShow, nStatus);
}

HBRUSH CGXRecordView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	return DoCtlColor(pDC, pWnd, nCtlColor);
}

void CGXRecordView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT flags)
{
	if (!ProcessKeys(this, WM_KEYDOWN, nChar, nRepCnt, flags))
		CGXView::OnKeyDown(nChar, nRepCnt, flags);
}

void CGXRecordView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT flags)
{
	if (!ProcessKeys(this, WM_KEYUP, nChar, nRepCnt, flags))
		CGXView::OnKeyUp(nChar, nRepCnt, flags);
}

void CGXRecordView::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!ProcessKeys(this, WM_SYSKEYDOWN, nChar, nRepCnt, nFlags))
		CGXView::OnSysKeyDown(nChar, nRepCnt, nFlags);
}

void CGXRecordView::OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!ProcessKeys(this, WM_SYSKEYUP, nChar, nRepCnt, nFlags))
		CGXView::OnSysKeyUp(nChar, nRepCnt, nFlags);
}

void CGXRecordView::OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!ProcessKeys(this, WM_SYSCHAR, nChar, nRepCnt, nFlags))
		CGXView::OnSysChar(nChar, nRepCnt, nFlags);
}

void CGXRecordView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!ProcessKeys(this, WM_CHAR, nChar, nRepCnt, nFlags))
		CGXView::OnChar(nChar, nRepCnt, nFlags);
}

void CGXRecordView::OnSetFocus(CWnd* pOldWnd)
{
	CGXView::OnSetFocus(pOldWnd);
	OnGridSetFocus(pOldWnd);
}

void CGXRecordView::OnCancelMode()
{
	// TRACE0("OnCancelMode\n");
	DoCancelMode();
}

void CGXRecordView::OnWinIniChange(LPCTSTR lpszSection)
{
	OnGridWinIniChange(lpszSection);
	CGXView::OnWinIniChange(lpszSection);
}

void CGXRecordView::OnSysColorChange()
{
	OnGridSysColorChange();
	CGXView::OnSysColorChange();
}

void CGXRecordView::OnTimer(SEC_UINT nIDEvent)
{
	OnGridTimer(nIDEvent);

	CGXView::OnTimer(nIDEvent);
}

/////////////////////////////////////////////////////////////////////////////
// Menu_Actions

void CGXRecordView::OnUpdateEditCopy(CCmdUI* pCmdUI)
	{ pCmdUI->Enable(CanCopy()); }

void CGXRecordView::OnEditCopy()
	{ Copy(); }

void CGXRecordView::OnEditCut()
	{ Cut(); }

void CGXRecordView::OnUpdateEditCut(CCmdUI* pCmdUI)
	{ pCmdUI->Enable(CanCut()); }

void CGXRecordView::OnEditPaste()
	{ Paste(); }

void CGXRecordView::OnUpdateEditPaste(CCmdUI* pCmdUI)
	{ pCmdUI->Enable(CanPaste()); }

void CGXRecordView::OnEditUndo()
	{ Undo(); }

void CGXRecordView::OnUpdateEditUndo(CCmdUI* pCmdUI)
{
	CanUndo(pCmdUI);
}

void CGXRecordView::OnEditRedo()
{
	Redo();
}

void CGXRecordView::OnUpdateEditRedo(CCmdUI* pCmdUI)
{
	CanRedo(pCmdUI);
}

/////////////////////////////////////////////////////////////////////////////
// CEditView Find & Replace

void CGXRecordView::OnEditFind()
{
	ASSERT_VALID(this);
	OnShowFindReplaceDialog(TRUE);
	ASSERT_VALID(this);
}

void CGXRecordView::OnEditReplace()
{
	ASSERT_VALID(this);
	OnShowFindReplaceDialog(FALSE);
	ASSERT_VALID(this);
}

void CGXRecordView::OnEditRepeat()
{
	ASSERT_VALID(this);
	if (!FindText())
		OnTextNotFound(GXGetLastFRState()->strFind);
	ASSERT_VALID(this);
}

LRESULT CGXRecordView::OnFindReplaceCmd(WPARAM, LPARAM lParam)
{
	ASSERT_VALID(this);
	CFindReplaceDialog* pDialog = CFindReplaceDialog::GetNotifier(lParam);

	OnFindReplace(pDialog);

	ASSERT_VALID(this);
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CGXRecordView diagnostics

#ifdef _DEBUG
void CGXRecordView::AssertValid() const
{
	CGXView::AssertValid();
	CGXODBCGrid::AssertValid();
}

void CGXRecordView::Dump(CDumpContext& dc) const
{
	CGXView::Dump(dc);
	CGXODBCGrid::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGXRecordView message handlers

void CGXRecordView::OnUpdateRecordFirst(CCmdUI* pCmdUI)
{
	CGXODBCGrid::OnUpdateRecordFirst(pCmdUI);
}

void CGXRecordView::OnUpdateRecordPrev(CCmdUI* pCmdUI)
{
	CGXODBCGrid::OnUpdateRecordPrev(pCmdUI);
}

void CGXRecordView::OnUpdateRecordNext(CCmdUI* pCmdUI)
{
	CGXODBCGrid::OnUpdateRecordNext(pCmdUI);
}

void CGXRecordView::OnUpdateRecordLast(CCmdUI* pCmdUI)
{
	CGXODBCGrid::OnUpdateRecordLast(pCmdUI);
}

void CGXRecordView::OnUpdateEditUndorecord(CCmdUI* pCmdUI)
{
	CGXODBCGrid::OnUpdateEditUndorecord(pCmdUI);
}

void CGXRecordView::OnEditUndorecord()
{
	CGXODBCGrid::OnEditUndorecord();
}

void CGXRecordView::OnRecordDelete()
{
	CGXODBCGrid::OnRecordDelete();
}

void CGXRecordView::OnUpdateRecordDelete(CCmdUI* pCmdUI)
{
	CGXODBCGrid::OnUpdateRecordDelete(pCmdUI);
}

BOOL CGXRecordView::OnMove(UINT nIDMoveCommand)
{
	return CGXODBCGrid::OnMove(nIDMoveCommand);
}

void CGXRecordView::OnView100()
{
	SetZoom(100);
}

void CGXRecordView::OnViewZoomin()
{
	if (GetZoom() < 300)
		SetZoom(GetZoom()*11/10);
}

void CGXRecordView::OnViewZoomout()
{
	if (GetZoom() > 40)
		SetZoom(GetZoom()*10/11);
}

void CGXRecordView::OnUpdateViewZoomin(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(GetParam() && GetZoom() < 300);
}

void CGXRecordView::OnUpdateViewZoomout(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(GetParam() && GetZoom() > 40);
}

/////////////////////////////////////////////////////////////////////////////
// Freeze Rows and Columns menu handlers

void CGXRecordView::OnFormatFreezecols()
{
	FreezeCols();
}

void CGXRecordView::OnFormatUnfreezecols()
{
	UnfreezeCols();
}

void CGXRecordView::OnUpdateFormatFreezecols(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(CanFreezeCols());
}

void CGXRecordView::OnUpdateFormatUnfreezecols(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(CanUnfreezeCols());
}

#endif // ndef _AFX_NO_DB_SUPPORT

void CGXRecordView::OnKillFocus(CWnd* pNewWnd)
{
	CGXView::OnKillFocus(pNewWnd);

	// Set m_bIgnoreFocus = FALSE so that OnGridKillFocus
	// will not fire a OnActivateGrid event. OnActivateGrid
	// already gets called from OnActivateView.

	BOOL b = m_bIgnoreFocus;
	m_bIgnoreFocus = TRUE;
	OnGridKillFocus(pNewWnd);
	m_bIgnoreFocus = b;
}
