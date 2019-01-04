///////////////////////////////////////////////////////////////////////////////
// gxadovw.cpp : implementation of CGXAdoRecordView class
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

#ifndef _GXVW_H_
#include "grid\gxvw.h"
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
#pragma code_seg("GX_SEG_GXADOVW")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

static UINT NEAR wm_Find = RegisterWindowMessage( FINDMSGSTRING );

/////////////////////////////////////////////////////////////////////////////
// CGXAdoRecordView

IMPLEMENT_DYNCREATE(CGXAdoRecordView, CGXView)

/////////////////////////////////////////////////////////////////////////////
// CGXAdoRecordView

BEGIN_MESSAGE_MAP(CGXAdoRecordView, CGXView)
	//{{AFX_MSG_MAP(CGXAdoRecordView)
	ON_UPDATE_COMMAND_UI(ID_RECORD_FIRST, OnUpdateRecordFirst)
	ON_UPDATE_COMMAND_UI(ID_RECORD_PREV, OnUpdateRecordPrev)
	ON_UPDATE_COMMAND_UI(ID_RECORD_NEXT, OnUpdateRecordNext)
	ON_UPDATE_COMMAND_UI(ID_RECORD_LAST, OnUpdateRecordLast)
	ON_COMMAND_EX(ID_RECORD_FIRST, OnMove)
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
	ON_COMMAND_EX(ID_RECORD_PREV, OnMove)
	ON_COMMAND_EX(ID_RECORD_NEXT, OnMove)
	ON_COMMAND_EX(ID_RECORD_LAST, OnMove)
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
	ON_WM_WININICHANGE()
	ON_REGISTERED_MESSAGE(wm_Find, OnFindReplaceCmd)
	ON_MESSAGE(WM_GX_ADO_REQUERY, OnAdoRequery)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CGXView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CGXView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGXAdoRecordView construction/destruction

CGXAdoRecordView::CGXAdoRecordView()
{
	SetGridWnd(this);
}

CGXAdoRecordView::~CGXAdoRecordView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CGXAdoRecordView initialization

void CGXAdoRecordView::OnInitialUpdate()
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
		// [VC7] IsChildPane Function Substituted with macro
		ASSERT(m_pSplitterWnd->IsKindOf(RUNTIME_CLASS(CSplitterWnd)));
		VERIFY(SPWND_ISCHILDPANE(m_pSplitterWnd, this, m_nSplitRow, m_nSplitCol));

		ASSERT(m_nSplitRow < 2);
		ASSERT(m_nSplitCol < 2);

		if (m_nSplitRow > 0 || m_nSplitCol > 0)
		{
			// copy settings from other pane
			CGXAdoRecordView *pView;

			pView = (CGXAdoRecordView *) m_pSplitterWnd->GetPane(0, 0);

			ASSERT(pView != NULL);
			ASSERT(pView->IsKindOf(RUNTIME_CLASS(CGXAdoRecordView)));

			if (m_nSplitRow > 0)
			{
				pView = (CGXAdoRecordView *) m_pSplitterWnd->GetPane(0, m_nSplitCol);

				ASSERT(pView != NULL);
				ASSERT(pView->IsKindOf(RUNTIME_CLASS(CGXAdoRecordView)));

				m_nLeftCol = pView->m_nLeftCol;
				m_nTopRow = pView->m_nTopRow;
				m_bDisplayHeaderRow = FALSE;

				// disable smart redrawing of WM_SIZE message
				pView->m_cxOld = pView->m_cyOld = 0;
			}

			if (m_nSplitCol > 0)
			{
				pView = (CGXAdoRecordView *) m_pSplitterWnd->GetPane(m_nSplitRow, 0);

				ASSERT(pView != NULL);
				ASSERT(pView->IsKindOf(RUNTIME_CLASS(CGXAdoRecordView)));

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
// CGXAdoRecordView support for CGXTabWnd/CGXAdoRecordInfoWnd

LRESULT CGXAdoRecordView::OnChangedTab(WPARAM wParam, LPARAM /*lParam*/)
{
	OnTabChanged((int) wParam);

	return 0;
}

LRESULT CGXAdoRecordView::OnCanActivate(WPARAM wParam, LPARAM /*lParam*/)
{
	BOOL bCanActivate = CanActivateGrid((BOOL) wParam);

	// Please note:
	// activation is allowed when return value is 0
	// activation is disabled when return value is 1
	return bCanActivate ? 0 : 1;
}

LRESULT CGXAdoRecordView::OnNeedChangeTab(WPARAM /*wParam*/, LPARAM /*lParam*/)
{
	return CanChangeTab();
}

LRESULT CGXAdoRecordView::OnMoveRecord(WPARAM wParam, LPARAM lParam)
{
	OnInfoWndMoveRecord((int) wParam, (long) lParam);
	return 0;
}

LRESULT CGXAdoRecordView::OnLockResize(WPARAM wParam, LPARAM )
{
	LockResize((BOOL) wParam);
	return 0;
}

CScrollBar* CGXAdoRecordView::GetScrollBarCtrl(int nBar) const
{
	CScrollBar* pBar = DoGetScrollBarCtrl(nBar);
	if (pBar != NULL)
		return pBar;

	return CGXView::GetScrollBarCtrl(nBar);
}

/////////////////////////////////////////////////////////////////////////////
// CView overridable member functions

void CGXAdoRecordView::OnActivateView( BOOL bActivate, CView* pActivateView, CView* pDeactiveView )
{
	if (bActivate != m_bActiveFrame && !GXDiscardNcActivate())
		OnActivateGrid(bActivate);
	CGXView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

void CGXAdoRecordView::OnDraw(CDC* pDC)
{
	OnGridDraw(pDC);
}

void CGXAdoRecordView::OnPrepareDC( CDC* pDC, CPrintInfo* pInfo /* = NULL */)
{
	OnGridPrepareDC(pDC, pInfo);
}

void CGXAdoRecordView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	OnGridUpdate(pSender, lHint, pHint);
}

BOOL CGXAdoRecordView::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if (DoCommand(wParam, lParam))
		return TRUE;

	return CGXView::OnCommand(wParam, lParam);
}

BOOL CGXAdoRecordView::PreTranslateMessage(MSG* pMsg)
{
	if (OnGridPreTranslateMessage(pMsg))
		return TRUE;

	return CGXView::PreTranslateMessage(pMsg);
}

LRESULT CGXAdoRecordView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result;

	if (OnGridWindowProc(message, wParam, lParam, result))
		return result;

	return CGXView::WindowProc(message, wParam, lParam);
}

/////////////////////////////////////////////////////////////////////////////
// CGXAdoRecordView printing

BOOL CGXAdoRecordView::OnPreparePrinting(CPrintInfo* pInfo)
{
	pInfo->SetMaxPage(0xffff);

	pInfo->m_pPD->m_pd.Flags &= ~PD_NOSELECTION;
	pInfo->m_pPD->m_pd.hInstance = AfxGetInstanceHandle();

	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGXAdoRecordView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	OnGridBeginPrinting(pDC, pInfo);
}

void CGXAdoRecordView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	OnGridEndPrinting(pDC, pInfo);
}

void CGXAdoRecordView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	OnGridPrint(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CGXAdoRecordView message handlers

void CGXAdoRecordView::OnPaint()
{
	// standard paint routine
	if (!m_bInitDone)
	{
		TRACE0("Warning! You must call CGXAdoRecordView::OnInitialUpdate()\n");
		ASSERT(0);        // You must call Initialize() in OnInitDialog!
		AfxThrowNotSupportedException();
	}

	CPaintDC dc(this);
	OnPrepareDC(&dc);
	OnDraw(&dc);
}

void CGXAdoRecordView::OnDestroy()
{
	if (!DoNotifyDestroy())
		CGXView::OnDestroy();
}

void CGXAdoRecordView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pBar)
{
	if (!DoVScroll(nSBCode, nPos, pBar))
		CGXView::OnVScroll(nSBCode, nPos, pBar);
}

void CGXAdoRecordView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pBar)
{
	if (!DoHScroll(nSBCode, nPos, pBar))
		CGXView::OnHScroll(nSBCode, nPos, pBar);
}

BOOL CGXAdoRecordView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	if (DoSetCursor(pWnd, nHitTest, message))
		return TRUE;
	return CView::OnSetCursor(pWnd, nHitTest, message);
}

void CGXAdoRecordView::OnMouseMove(UINT flags, CPoint point)
{
	if (!DoMouseMove(flags, point))
		CGXView::OnMouseMove(flags, point);
}

int CGXAdoRecordView::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// First, check out current control's
	int retval;

	if (DoMouseActivate(pDesktopWnd, nHitTest, message, retval))
		return retval;

	return CGXView::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

void CGXAdoRecordView::OnLButtonDown(UINT flags, CPoint point)
{
	if (!DoLButtonDown(flags, point))
		CGXView::OnLButtonDown(flags, point);
}

void CGXAdoRecordView::OnLButtonUp(UINT flags, CPoint point)
{
	if (!DoLButtonUp(flags, point))
		CGXView::OnLButtonUp(flags, point);
}


void CGXAdoRecordView::OnRButtonDown(UINT flags, CPoint point)
{
	if (!DoRButtonDown(flags, point))
		CGXView::OnRButtonDown(flags, point);
}

void CGXAdoRecordView::OnRButtonUp(UINT flags, CPoint point)
{
	if (!DoRButtonUp(flags, point))
		CGXView::OnRButtonUp(flags, point);
}

void CGXAdoRecordView::OnLButtonDblClk(UINT flags, CPoint point)
{
	if (!DoLButtonDblClk(flags, point))
		CGXView::OnLButtonDblClk(flags, point);
}

void CGXAdoRecordView::OnRButtonDblClk(UINT flags, CPoint point)
{
	if (!DoRButtonDblClk(flags, point))
		CGXView::OnRButtonDblClk(flags, point);
}

void CGXAdoRecordView::OnMButtonDown(UINT flags, CPoint point)
{
	if (!DoMButtonDown(flags, point))
		CGXView::OnLButtonDown(flags, point);
}

void CGXAdoRecordView::OnMButtonUp(UINT flags, CPoint point)
{
	if (!DoMButtonUp(flags, point))
		CGXView::OnMButtonUp(flags, point);
}

void CGXAdoRecordView::OnMButtonDblClk(UINT flags, CPoint point)
{
	if (!DoMButtonDblClk(flags, point))
		CGXView::OnMButtonDblClk(flags, point);
}

BOOL CGXAdoRecordView::OnEraseBkgnd(CDC* /*pDC*/)
{
	// I don't want the Screen to flicker!
	// Also, ...
	return TRUE;
}

void CGXAdoRecordView::OnSize(UINT nType, int cx, int cy)
{
	if (!DoSize(nType, cx, cy))
		CGXView::OnSize(nType, cx, cy);
}

void CGXAdoRecordView::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CGXView::OnShowWindow(bShow, nStatus);
	DoShowWindow(bShow, nStatus);
}

HBRUSH CGXAdoRecordView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	return DoCtlColor(pDC, pWnd, nCtlColor);
}

void CGXAdoRecordView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT flags)
{
	if (!ProcessKeys(this, WM_KEYDOWN, nChar, nRepCnt, flags))
		CGXView::OnKeyDown(nChar, nRepCnt, flags);
}

void CGXAdoRecordView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT flags)
{
	if (!ProcessKeys(this, WM_KEYUP, nChar, nRepCnt, flags))
		CGXView::OnKeyUp(nChar, nRepCnt, flags);
}

void CGXAdoRecordView::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!ProcessKeys(this, WM_SYSKEYDOWN, nChar, nRepCnt, nFlags))
		CGXView::OnSysKeyDown(nChar, nRepCnt, nFlags);
}

void CGXAdoRecordView::OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!ProcessKeys(this, WM_SYSKEYUP, nChar, nRepCnt, nFlags))
		CGXView::OnSysKeyUp(nChar, nRepCnt, nFlags);
}

void CGXAdoRecordView::OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!ProcessKeys(this, WM_SYSCHAR, nChar, nRepCnt, nFlags))
		CGXView::OnSysChar(nChar, nRepCnt, nFlags);
}

void CGXAdoRecordView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!ProcessKeys(this, WM_CHAR, nChar, nRepCnt, nFlags))
		CGXView::OnChar(nChar, nRepCnt, nFlags);
}

void CGXAdoRecordView::OnSetFocus(CWnd* pOldWnd)
{
	CGXView::OnSetFocus(pOldWnd);
	OnGridSetFocus(pOldWnd);
}

void CGXAdoRecordView::OnCancelMode()
{
	DoCancelMode();
}

void CGXAdoRecordView::OnWinIniChange(LPCTSTR lpszSection)
{
	OnGridWinIniChange(lpszSection);
	CGXView::OnWinIniChange(lpszSection);
}

void CGXAdoRecordView::OnSysColorChange()
{
	OnGridSysColorChange();
	CGXView::OnSysColorChange();
}

void CGXAdoRecordView::OnTimer(SEC_UINT nIDEvent)
{
	OnGridTimer(nIDEvent);

	CGXView::OnTimer(nIDEvent);
}

/////////////////////////////////////////////////////////////////////////////
// Menu_Actions

void CGXAdoRecordView::OnUpdateEditCopy(CCmdUI* pCmdUI)
	{ pCmdUI->Enable(CanCopy()); }

void CGXAdoRecordView::OnEditCopy()
	{ Copy(); }

void CGXAdoRecordView::OnEditCut()
	{ Cut(); }

void CGXAdoRecordView::OnUpdateEditCut(CCmdUI* pCmdUI)
	{ pCmdUI->Enable(CanCut()); }

void CGXAdoRecordView::OnEditPaste()
	{ Paste(); }

void CGXAdoRecordView::OnUpdateEditPaste(CCmdUI* pCmdUI)
	{ pCmdUI->Enable(CanPaste()); }

void CGXAdoRecordView::OnEditUndo()
	{ Undo(); }

void CGXAdoRecordView::OnUpdateEditUndo(CCmdUI* pCmdUI)
{
	CanUndo(pCmdUI);
}

void CGXAdoRecordView::OnEditRedo()
{
	Redo();
}

void CGXAdoRecordView::OnUpdateEditRedo(CCmdUI* pCmdUI)
{
	CanRedo(pCmdUI);
}

/////////////////////////////////////////////////////////////////////////////
// CEditView Find & Replace

void CGXAdoRecordView::OnEditFind()
{
	ASSERT_VALID(this);
	OnShowFindReplaceDialog(TRUE);
	ASSERT_VALID(this);
}

void CGXAdoRecordView::OnEditReplace()
{
	ASSERT_VALID(this);
	OnShowFindReplaceDialog(FALSE);
	ASSERT_VALID(this);
}

void CGXAdoRecordView::OnEditRepeat()
{
	ASSERT_VALID(this);
	if (!FindText())
		OnTextNotFound(GXGetLastFRState()->strFind);
	ASSERT_VALID(this);
}

LRESULT CGXAdoRecordView::OnFindReplaceCmd(WPARAM, LPARAM lParam)
{
	ASSERT_VALID(this);
	CFindReplaceDialog* pDialog = CFindReplaceDialog::GetNotifier(lParam);

	OnFindReplace(pDialog);

	ASSERT_VALID(this);
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CGXAdoRecordView diagnostics

#ifdef _DEBUG
void CGXAdoRecordView::AssertValid() const
{
	CGXView::AssertValid();
	CGXAdoGrid::AssertValid();
}

void CGXAdoRecordView::Dump(CDumpContext& dc) const
{
	CGXView::Dump(dc);
	CGXAdoGrid::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGXAdoRecordView message handlers

void CGXAdoRecordView::OnUpdateRecordFirst(CCmdUI* pCmdUI)
{
	CGXAdoGrid::OnUpdateRecordFirst(pCmdUI);
}

void CGXAdoRecordView::OnUpdateRecordPrev(CCmdUI* pCmdUI)
{
	CGXAdoGrid::OnUpdateRecordPrev(pCmdUI);
}

void CGXAdoRecordView::OnUpdateRecordNext(CCmdUI* pCmdUI)
{
	CGXAdoGrid::OnUpdateRecordNext(pCmdUI);
}

void CGXAdoRecordView::OnUpdateRecordLast(CCmdUI* pCmdUI)
{
	CGXAdoGrid::OnUpdateRecordLast(pCmdUI);
}

void CGXAdoRecordView::OnUpdateEditUndorecord(CCmdUI* pCmdUI)
{
	CGXAdoGrid::OnUpdateEditUndorecord(pCmdUI);
}

void CGXAdoRecordView::OnEditUndorecord()
{
	CGXAdoGrid::OnEditUndorecord();
}

void CGXAdoRecordView::OnRecordDelete()
{
	CGXAdoGrid::OnRecordDelete();
}

void CGXAdoRecordView::OnUpdateRecordDelete(CCmdUI* pCmdUI)
{
	CGXAdoGrid::OnUpdateRecordDelete(pCmdUI);
}

BOOL CGXAdoRecordView::OnMove(UINT nIDMoveCommand)
{
	return CGXAdoGrid::OnMove(nIDMoveCommand);
}

void CGXAdoRecordView::OnView100()
{
	SetZoom(100);
}

void CGXAdoRecordView::OnViewZoomin()
{
	if (GetZoom() < 300)
		SetZoom(GetZoom()*11/10);
}

void CGXAdoRecordView::OnViewZoomout()
{
	if (GetZoom() > 40)
		SetZoom(GetZoom()*10/11);
}

void CGXAdoRecordView::OnUpdateViewZoomin(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(GetParam() && GetZoom() < 300);
}

void CGXAdoRecordView::OnUpdateViewZoomout(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(GetParam() && GetZoom() > 40);
}

/////////////////////////////////////////////////////////////////////////////
// Freeze Rows and Columns menu handlers

void CGXAdoRecordView::OnFormatFreezecols()
{
	FreezeCols();
}

void CGXAdoRecordView::OnFormatUnfreezecols()
{
	UnfreezeCols();
}

void CGXAdoRecordView::OnUpdateFormatFreezecols(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(CanFreezeCols());
}

void CGXAdoRecordView::OnUpdateFormatUnfreezecols(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(CanUnfreezeCols());
}

void CGXAdoRecordView::OnKillFocus(CWnd* pNewWnd)
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


LPARAM CGXAdoRecordView::OnAdoRequery(WPARAM /*wParam*/, LPARAM /*lParam*/)
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
