///////////////////////////////////////////////////////////////////////////////
// gxvwhnd.cpp : implementation of the CGXGridHandleView class
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

#ifndef _GXVW_H_
#include "grid\gxvw.h"
#endif

#ifndef _GXMSG_H_
#include "grid\gxmsg.h"
#endif

#ifndef _GXSTATE_H_
#include "grid\gxstate.h"
#endif

#ifndef _GXCTRL_H_
#include "grid\gxctrl.h"
#endif

#ifndef _GXEXT_H_
#include "grid\gxext.h"
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXVWHND")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CGXGridHandleView, CGXView)

static UINT NEAR wm_Find = RegisterWindowMessage( FINDMSGSTRING );

/////////////////////////////////////////////////////////////////////////////
// CGXGridHandleView

BEGIN_MESSAGE_MAP(CGXGridHandleView, CGXView)
	//{{AFX_MSG_MAP(CGXGridHandleView)
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
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_REGISTERED_MESSAGE(wm_Find, OnFindReplaceCmd)
	ON_WM_WININICHANGE()
	ON_COMMAND(ID_FILE_PRINT, CGXView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CGXView::OnFilePrintPreview)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CGXGridHandleView construction/destruction

CGXGridHandleView::CGXGridHandleView()
{
	m_pGrid = NULL;
}

CGXGridHandleView::~CGXGridHandleView()
{
	delete m_pGrid;
}

/////////////////////////////////////////////////////////////////////////////
// CGXGridHandleView initialization

void CGXGridHandleView::AttachGrid(CGXGridCore* pGrid)
{
	m_pGrid = pGrid;
}

void CGXGridHandleView::OnInitialUpdate()
{
	if (m_pGrid == NULL)
		m_pGrid = new CGXGridCore(this, GetDocument(), TRUE);

	CSplitterWnd* pSplitterWnd =
		m_pGrid->m_pSplitterWnd = GetParentDynamicSplitter(this, TRUE);

	// Commment: I have move the following lines before
	// CGXGridCore::OnGridInitialUpdate() so that scrollbars
	// can be initialized correctly.
	if (pSplitterWnd || m_pGrid->GetSharedScrollbarParentWnd())
		m_pGrid->SetScrollBarMode(SB_BOTH, gxnShared | gxnEnhanced);
	else
		m_pGrid->SetScrollBarMode(SB_BOTH, gxnAutomatic | gxnEnhanced);

	m_pGrid->OnGridInitialUpdate();
	CGXView::OnInitialUpdate();

	CGXGridParam* pParam = m_pGrid->GetParam();

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

	if (pSplitterWnd != NULL)
	{
		// [VC7] Substitute IsChildPane to macro.
		ASSERT(pSplitterWnd->IsKindOf(RUNTIME_CLASS(CSplitterWnd)));
		VERIFY(SPWND_ISCHILDPANE(pSplitterWnd, this, m_pGrid->m_nSplitRow, m_pGrid->m_nSplitCol));

		ASSERT(m_pGrid->m_nSplitRow < 2);
		ASSERT(m_pGrid->m_nSplitCol < 2);

		if (m_pGrid->m_nSplitRow > 0 || m_pGrid->m_nSplitCol > 0)
		{
			// copy settings from other pane
			CGXGridHandleView *pView;

			pView = (CGXGridHandleView *) pSplitterWnd->GetPane(0, 0);

			ASSERT(pView != NULL);
			if (pView->IsKindOf(RUNTIME_CLASS(CGXGridHandleView)))
			{
				if (m_pGrid->m_nSplitRow > 0)
				{
					pView = (CGXGridHandleView *) pSplitterWnd->GetPane(0, m_pGrid->m_nSplitCol);

					ASSERT(pView != NULL);
					if (pView->IsKindOf(RUNTIME_CLASS(CGXGridHandleView)))
					{
						m_pGrid->m_nLeftCol = pView->m_pGrid->m_nLeftCol;
						m_pGrid->m_nTopRow = pView->m_pGrid->m_nTopRow;
						m_pGrid->m_bDisplayHeaderRow = FALSE;


						// disable smart redrawing of WM_SIZE message
						pView->m_pGrid->m_cxOld = pView->m_pGrid->m_cyOld = 0;
					}
				}

				if (m_pGrid->m_nSplitCol > 0)
				{
					pView = (CGXGridHandleView *) pSplitterWnd->GetPane(m_pGrid->m_nSplitRow, 0);

					ASSERT(pView != NULL);
					if (pView->IsKindOf(RUNTIME_CLASS(CGXGridHandleView)))
					{
						m_pGrid->m_nTopRow = pView->m_pGrid->m_nTopRow;
						if (m_pGrid->m_nSplitRow == 0)
							m_pGrid->m_nLeftCol = pView->m_pGrid->m_nLeftCol;
						m_pGrid->m_bDisplayHeaderCol = FALSE;

						// disable smart redrawing of WM_SIZE message
						pView->m_pGrid->m_cxOld = pView->m_pGrid->m_cyOld = 0;
					}
				}
			}

		}

		m_pGrid->UpdateScrollbars();
	}
}

/////////////////////////////////////////////////////////////////////////////
// CGXGridHandleView support for CGXTabWnd/CGXRecordInfoWnd

LRESULT CGXGridHandleView::OnChangedTab(WPARAM wParam, LPARAM /*lParam*/)
{
	if (m_pGrid)
		m_pGrid->OnTabChanged((int) wParam);

	return 0;
}

LRESULT CGXGridHandleView::OnCanActivate(WPARAM wParam, LPARAM /*lParam*/)
{
	BOOL bCanActivate = m_pGrid && m_pGrid->CanActivateGrid((BOOL) wParam);

	// Please note:
	// activation is allowed when return value is 0
	// activation is disabled when return value is 1
	return bCanActivate ? 0 : 1;
}

LRESULT CGXGridHandleView::OnNeedChangeTab(WPARAM /*wParam*/, LPARAM /*lParam*/)
{
	return m_pGrid && m_pGrid->CanChangeTab();
}

LRESULT CGXGridHandleView::OnLockResize(WPARAM wParam, LPARAM )
{
	if (m_pGrid)
		m_pGrid->LockResize((BOOL) wParam);
	return 0;
}

LRESULT CGXGridHandleView::OnMoveRecord(WPARAM wParam, LPARAM lParam)
{
	if (m_pGrid)
		m_pGrid->OnInfoWndMoveRecord((int) wParam, (long) lParam);
	return 0;
}

CScrollBar* CGXGridHandleView::GetScrollBarCtrl(int nBar) const
{
	CScrollBar* pBar = m_pGrid ? m_pGrid->DoGetScrollBarCtrl(nBar) : NULL;
	if (pBar != NULL)
		return pBar;

	return CGXView::GetScrollBarCtrl(nBar);
}

/////////////////////////////////////////////////////////////////////////////
// CView overridable member functions

void CGXGridHandleView::OnDraw(CDC* pDC)
{
	if (m_pGrid)
		m_pGrid->OnGridDraw(pDC);
}

void CGXGridHandleView::OnPrepareDC( CDC* pDC, CPrintInfo* pInfo /* = NULL */)
{
	if (m_pGrid)
		m_pGrid->OnGridPrepareDC(pDC, pInfo);
}

void CGXGridHandleView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	if (m_pGrid)
		m_pGrid->OnGridUpdate(pSender, lHint, pHint);
}

void CGXGridHandleView::OnActivateView( BOOL bActivate, CView* pActivateView, CView* pDeactiveView )
{
	if (m_pGrid && bActivate != m_pGrid->m_bActiveFrame  && !GXDiscardNcActivate())
		m_pGrid->OnActivateGrid(bActivate);
	CGXView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

BOOL CGXGridHandleView::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if (m_pGrid && m_pGrid->DoCommand(wParam, lParam))
		return TRUE;

	return CGXView::OnCommand(wParam, lParam);
}

BOOL CGXGridHandleView::PreTranslateMessage(MSG* pMsg)
{
	if (m_pGrid && m_pGrid->OnGridPreTranslateMessage(pMsg))
		return TRUE;

	return CGXView::PreTranslateMessage(pMsg);
}

LRESULT CGXGridHandleView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result;

	if (m_pGrid && m_pGrid->OnGridWindowProc(message, wParam, lParam, result))
		return result;

	return CGXView::WindowProc(message, wParam, lParam);
}

/////////////////////////////////////////////////////////////////////////////
// CGXGridHandleView printing

BOOL CGXGridHandleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	pInfo->SetMaxPage(0xffff);

	pInfo->m_pPD->m_pd.Flags &= ~PD_NOSELECTION;
	pInfo->m_pPD->m_pd.hInstance = AfxGetInstanceHandle();

	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGXGridHandleView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	if (m_pGrid)
		m_pGrid->OnGridBeginPrinting(pDC, pInfo);
}

void CGXGridHandleView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	if (m_pGrid)
		m_pGrid->OnGridEndPrinting(pDC, pInfo);
}

void CGXGridHandleView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	if (m_pGrid)
		m_pGrid->OnGridPrint(pDC, pInfo);
}


/////////////////////////////////////////////////////////////////////////////
// CGXGridHandleView diagnostics

#ifdef _DEBUG
void CGXGridHandleView::AssertValid() const
{
	CGXView::AssertValid();
}

void CGXGridHandleView::Dump(CDumpContext& dc) const
{
	CGXView::Dump(dc);
}

#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// CGXGridHandleView message handlers

void CGXGridHandleView::OnPaint()
{
	// standard paint routine
	if (m_pGrid == NULL)
	{
		TRACE0("Warning! You must call CGXGridHandleView::OnInitialUpdate()\n");
		ASSERT(0);        // You must call Initialize() in OnInitDialog!
		AfxThrowNotSupportedException();
	}

	CPaintDC dc(this);
	m_pGrid->OnGridPrepareDC(&dc);
	m_pGrid->OnGridDraw(&dc);
}

void CGXGridHandleView::OnDestroy()
{
	if (!(m_pGrid && m_pGrid->DoNotifyDestroy()))
		CGXView::OnDestroy();
}

void CGXGridHandleView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pBar)
{
	if (!(m_pGrid && m_pGrid->DoVScroll(nSBCode, nPos, pBar)))
		CGXView::OnVScroll(nSBCode, nPos, pBar);
}

void CGXGridHandleView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pBar)
{
	if (!(m_pGrid && m_pGrid->DoHScroll(nSBCode, nPos, pBar)))
		CGXView::OnHScroll(nSBCode, nPos, pBar);
}

BOOL CGXGridHandleView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	if (m_pGrid && m_pGrid->DoSetCursor(pWnd, nHitTest, message))
		return TRUE;
	return CView::OnSetCursor(pWnd, nHitTest, message);
}

void CGXGridHandleView::OnMouseMove(UINT flags, CPoint point)
{
	if (!(m_pGrid && m_pGrid->DoMouseMove(flags, point)))
		CGXView::OnMouseMove(flags, point);
}

int CGXGridHandleView::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// First, check out current control's
	int retval;

	if (m_pGrid && m_pGrid->DoMouseActivate(pDesktopWnd, nHitTest, message, retval))
		return retval;

	return CGXView::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

void CGXGridHandleView::OnLButtonDown(UINT flags, CPoint point)
{
	if (!(m_pGrid && m_pGrid->DoLButtonDown(flags, point)))
		CGXView::OnLButtonDown(flags, point);
}

void CGXGridHandleView::OnLButtonUp(UINT flags, CPoint point)
{
	if (!(m_pGrid && m_pGrid->DoLButtonUp(flags, point)))
		CGXView::OnLButtonUp(flags, point);
}


void CGXGridHandleView::OnRButtonDown(UINT flags, CPoint point)
{
	if (!(m_pGrid && m_pGrid->DoRButtonDown(flags, point)))
		CGXView::OnRButtonDown(flags, point);
}

void CGXGridHandleView::OnRButtonUp(UINT flags, CPoint point)
{
	if (!(m_pGrid && m_pGrid->DoRButtonUp(flags, point)))
		CGXView::OnRButtonUp(flags, point);
}

void CGXGridHandleView::OnLButtonDblClk(UINT flags, CPoint point)
{
	if (!(m_pGrid && m_pGrid->DoLButtonDblClk(flags, point)))
		CGXView::OnLButtonDblClk(flags, point);
}

void CGXGridHandleView::OnRButtonDblClk(UINT flags, CPoint point)
{
	if (!(m_pGrid && m_pGrid->DoRButtonDblClk(flags, point)))
		CGXView::OnRButtonDblClk(flags, point);
}

void CGXGridHandleView::OnMButtonDown(UINT flags, CPoint point)
{
	if (!(m_pGrid && m_pGrid->DoMButtonDown(flags, point)))
		CGXView::OnLButtonDown(flags, point);
}

void CGXGridHandleView::OnMButtonUp(UINT flags, CPoint point)
{
	if (!(m_pGrid && m_pGrid->DoMButtonUp(flags, point)))
		CGXView::OnMButtonUp(flags, point);
}

void CGXGridHandleView::OnMButtonDblClk(UINT flags, CPoint point)
{
	if (!(m_pGrid && m_pGrid->DoMButtonDblClk(flags, point)))
		CGXView::OnMButtonDblClk(flags, point);
}

BOOL CGXGridHandleView::OnEraseBkgnd(CDC* /*pDC*/)
{
	// I don't want the Screen to flicker!
	// Also, ...
	return TRUE;
}

void CGXGridHandleView::OnSize(UINT nType, int cx, int cy)
{
	if (!(m_pGrid && m_pGrid->DoSize(nType, cx, cy)))
		CGXView::OnSize(nType, cx, cy);
}

void CGXGridHandleView::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CGXView::OnShowWindow(bShow, nStatus);
	if (m_pGrid)
		m_pGrid->DoShowWindow(bShow, nStatus);
}

HBRUSH CGXGridHandleView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	if (m_pGrid)
		return m_pGrid->DoCtlColor(pDC, pWnd, nCtlColor);
	return 0;
}

void CGXGridHandleView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT flags)
{
	if (!(m_pGrid && m_pGrid->ProcessKeys(this, WM_KEYDOWN, nChar, nRepCnt, flags)))
		CGXView::OnKeyDown(nChar, nRepCnt, flags);
}

void CGXGridHandleView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT flags)
{
	if (!(m_pGrid && m_pGrid->ProcessKeys(this, WM_KEYUP, nChar, nRepCnt, flags)))
		CGXView::OnKeyUp(nChar, nRepCnt, flags);
}

void CGXGridHandleView::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!(m_pGrid && m_pGrid->ProcessKeys(this, WM_SYSKEYDOWN, nChar, nRepCnt, nFlags)))
		CGXView::OnSysKeyDown(nChar, nRepCnt, nFlags);
}

void CGXGridHandleView::OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!(m_pGrid && m_pGrid->ProcessKeys(this, WM_SYSKEYUP, nChar, nRepCnt, nFlags)))
		CGXView::OnSysKeyUp(nChar, nRepCnt, nFlags);
}

void CGXGridHandleView::OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!(m_pGrid && m_pGrid->ProcessKeys(this, WM_SYSCHAR, nChar, nRepCnt, nFlags)))
		CGXView::OnSysChar(nChar, nRepCnt, nFlags);
}

void CGXGridHandleView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!(m_pGrid && m_pGrid->ProcessKeys(this, WM_CHAR, nChar, nRepCnt, nFlags)))
		CGXView::OnChar(nChar, nRepCnt, nFlags);
}

void CGXGridHandleView::OnSetFocus(CWnd* pOldWnd)
{
	CGXView::OnSetFocus(pOldWnd);
	if (m_pGrid)
		m_pGrid->OnGridSetFocus(pOldWnd);
}

void CGXGridHandleView::OnCancelMode()
{
	// TRACE0("OnCancelMode\n");
	if (m_pGrid)
		m_pGrid->DoCancelMode();
}

void CGXGridHandleView::OnWinIniChange(LPCTSTR lpszSection)
{
	if (m_pGrid)
		m_pGrid->OnGridWinIniChange(lpszSection);
	CGXView::OnWinIniChange(lpszSection);
}

void CGXGridHandleView::OnSysColorChange()
{
	if (m_pGrid)
		m_pGrid->OnGridSysColorChange();
	CGXView::OnSysColorChange();
}


void CGXGridHandleView::OnTimer(SEC_UINT nIDEvent)
{
	if (m_pGrid)
		m_pGrid->OnGridTimer(nIDEvent);

	CGXView::OnTimer(nIDEvent);
}

/////////////////////////////////////////////////////////////////////////////
// Menu_Actions

void CGXGridHandleView::OnUpdateEditCopy(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_pGrid && m_pGrid->CanCopy());
}

void CGXGridHandleView::OnEditCopy()
{
	if (m_pGrid)
		m_pGrid->Copy();
}

void CGXGridHandleView::OnEditCut()
{
	if (m_pGrid)
		m_pGrid->Cut();
}

void CGXGridHandleView::OnUpdateEditCut(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_pGrid && m_pGrid->CanCut());
}

void CGXGridHandleView::OnEditPaste()
{
	if (m_pGrid)
		m_pGrid->Paste();
}

void CGXGridHandleView::OnUpdateEditPaste(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_pGrid && m_pGrid->CanPaste());
}

void CGXGridHandleView::OnEditUndo()
{
	if (m_pGrid)
		m_pGrid->Undo();
}

void CGXGridHandleView::OnUpdateEditUndo(CCmdUI* pCmdUI)
{
	if (m_pGrid)
		m_pGrid->CanUndo(pCmdUI);
	else
		pCmdUI->Enable(FALSE);
}

void CGXGridHandleView::OnEditRedo()
{
	if (m_pGrid)
		m_pGrid->Redo();
}

void CGXGridHandleView::OnUpdateEditRedo(CCmdUI* pCmdUI)
{
	if (m_pGrid)
		m_pGrid->CanRedo(pCmdUI);
	else
		pCmdUI->Enable(FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// CEditView Find & Replace

void CGXGridHandleView::OnEditFind()
{
	ASSERT_VALID(this);
	if (m_pGrid)
		m_pGrid->OnShowFindReplaceDialog(TRUE);
	ASSERT_VALID(this);
}

void CGXGridHandleView::OnEditReplace()
{
	ASSERT_VALID(this);
	if (m_pGrid)
		m_pGrid->OnShowFindReplaceDialog(FALSE);
	ASSERT_VALID(this);
}

void CGXGridHandleView::OnEditRepeat()
{
	ASSERT_VALID(this);
	if (!(m_pGrid && m_pGrid->FindText()))
		m_pGrid->OnTextNotFound(GXGetLastFRState()->strFind);
	ASSERT_VALID(this);
}

LRESULT CGXGridHandleView::OnFindReplaceCmd(WPARAM, LPARAM lParam)
{
	ASSERT_VALID(this);
	CFindReplaceDialog* pDialog = CFindReplaceDialog::GetNotifier(lParam);

	if (m_pGrid)
		m_pGrid->OnFindReplace(pDialog);

	ASSERT_VALID(this);
	return 0;
}

void CGXGridHandleView::OnKillFocus(CWnd* pNewWnd)
{
	CGXView::OnKillFocus(pNewWnd);

	if (m_pGrid)
	{
		// Set m_bIgnoreFocus = FALSE so that OnGridKillFocus
		// will not fire a OnActivateGrid event. OnActivateGrid
		// already gets called from OnActivateView.

		BOOL b = m_pGrid->m_bIgnoreFocus;
		m_pGrid->m_bIgnoreFocus = TRUE;
		m_pGrid->OnGridKillFocus(pNewWnd);
		m_pGrid->m_bIgnoreFocus = b;
	}
}
