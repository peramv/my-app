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

#ifndef _AFXPRIV_H_
#include "afxpriv.h"
#endif

#ifndef _GXSTATE_H_
#include "grid\gxstate.h"
#endif

#ifndef _GXMSG_H_
#include "grid\gxmsg.h"
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXINFWND")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CGXRecordInfoWnd, CWnd);

// enable use as custom control
GRID_IMPLEMENT_REGISTER(CGXRecordInfoWnd, GX_GLOBALCLASS, 0, 0, 0);

/////////////////////////////////////////////////////////////////////////////
// Win4 specific defines

// new Win95 scroll bar styles
#ifndef SBS_SIZEGRIP
#define SBS_SIZEGRIP     0x00000010L
#endif

#ifndef WS_EX_SMCAPTION
#define WS_EX_SMCAPTION WS_EX_TOOLWINDOW
#endif

#define CX_BORDER           1
#define CY_BORDER           1
#define IDW_INFOBEAM         AFX_IDW_HSCROLL_FIRST+1
#define _GXGetDlgCtrlID(hWnd)  ((UINT)(WORD)::GetDlgCtrlID(hWnd))

// Colors for Arrows
const COLORREF rgbBlack = RGB(0,0,0);
const COLORREF rgbGrey  = RGB(96,96,96);

/////////////////////////////////////////////////////////////////////////////
// CGXRecordInfoWnd

class CGXRecordInfoWndInterface: public CGXAbstractRecordInfoWndInterface
{
public:
	virtual void UpdateRecordInfoWnd(CGXGridCore* pGrid);
	virtual void SetActivePane(CGXGridCore* pGrid);
};

void CGXRecordInfoWndInterface::UpdateRecordInfoWnd(CGXGridCore* pGrid)
{
	// Record Window support
	CGXRecordInfoWnd* pWnd = (CGXRecordInfoWnd*)
		GXGetParentWnd(pGrid->GridWnd(), RUNTIME_CLASS(CGXRecordInfoWnd), TRUE);

	if (pWnd && pWnd->GetBeam())
	{
		ROWCOL nRow = 1, nCol = 1;
		pGrid->GetCurrentCell(nRow, nCol);
		long nCurrent = (long) (nRow-pGrid->GetHeaderRows());
		long nCount = (long) (pGrid->GetRowCount()-pGrid->GetHeaderRows());

		if (pWnd->GetBeam()->GetCurrentRecord() != nCurrent
			|| pWnd->GetBeam()->GetRecordCount() != nCount)
		{
			pWnd->GetBeam()->SetRecordCount(nCount);
			pWnd->GetBeam()->SetCurrentRecord(nCurrent);
			pWnd->GetBeam()->Invalidate();
			pWnd->GetBeam()->UpdateWindow();
		}
	}
}

void CGXRecordInfoWndInterface::SetActivePane(CGXGridCore* pGrid)
{
	UpdateRecordInfoWnd(pGrid);
}

/////////////////////////////////////////////////////////////////////////////
// CGXRecordInfoWnd

CGXRecordInfoWnd::CGXRecordInfoWnd(CRuntimeClass *pBeamClass)
{
#if _MFC_VER >= 0x0300 && defined(_DEBUG)
	ASSERT( pBeamClass && pBeamClass->IsDerivedFrom(RUNTIME_CLASS(CGXRecordInfoBeam)) );
#endif

	m_pBeamClass = pBeamClass;
	m_bCtrlsCreated = FALSE;
	m_pBeam = 0;
	m_pPane = 0;
	m_cxBeam = 163;
	m_cxWnd = 0;
	m_cxSplitter = 6;
	m_cxVScroll = GetSystemMetrics(SM_CXVSCROLL);
	m_cyHScroll = GetSystemMetrics(SM_CYHSCROLL);
	m_nBarWidths = m_cyHScroll + 2*GXGetAppData()->bWin4;
	m_hcurArrow  = ::LoadCursor(NULL, IDC_ARROW);
	m_bHasHScroll = 1;
	m_bHasVScroll = 1;

	m_brErase.CreateSolidBrush(GXGetSysData()->GetSysColor(COLOR_BTNFACE));
	m_bForceRecalcLayout = FALSE;

	m_bDrawSunken = FALSE;

	// Register in grid for sharing scrollbars
	GXGetAppData()->RegisterSharedScrollBar(GetRuntimeClass());

	// Register interface for CGXGridCore

	// to remove any dependencies on CGXGridCore comment out the following
	// line 
	if (GXGetAppData()->m_pRecordInfoWndInt == NULL)
		GXGetAppData()->m_pRecordInfoWndInt = new CGXRecordInfoWndInterface;
}

CGXRecordInfoWnd::~CGXRecordInfoWnd()
{
	delete m_pBeam;
}

// repositions client area of specified window
// assumes everything has WS_BORDER or is inset like it does
//  (includes scroll bars)
static HDWP NEAR PASCAL DeferClientPos(HDWP hDWP, CWnd* pWnd,
		int x, int y, int cx, int cy, BOOL bScrollBar)
{
	ASSERT(pWnd != NULL);
	ASSERT(pWnd->GetSafeHwnd() != NULL);

	if (bScrollBar)
	{
		DWORD dwStyle = pWnd->GetStyle();

		// if there is enough room, draw scroll bar without border
		// if there is not enough room, set the WS_BORDER bit so that
		//   we will at least get a proper border drawn
		BOOL bNeedBorder = (cx <= CX_BORDER || cy <= CY_BORDER);
		if (bNeedBorder)
			dwStyle |= WS_BORDER;
		else
			dwStyle &= ~WS_BORDER;
#ifdef _WIN64
		::SetWindowLongPtr(pWnd->GetSafeHwnd(), GWL_STYLE, dwStyle);
#else	//WIN32
		::SetWindowLong(pWnd->GetSafeHwnd(), GWL_STYLE, dwStyle);
#endif	//_WIN64
	}

	// adjust for border size (even if zero client size)
	x -= CX_BORDER;
	y -= CY_BORDER;
	cx += 2 * CX_BORDER;
	cy += 2 * CY_BORDER;

	// first check if the new rectangle is the same as the current
	CRect rectOld;
	pWnd->GetWindowRect(rectOld);
	pWnd->GetParent()->ScreenToClient(&rectOld);
	if (rectOld.left == x && rectOld.top == y &&
		rectOld.Width() == cx && rectOld.Height() == cy)
	{
		return hDWP;        // nothing to do
	}

	return ::DeferWindowPos(hDWP, pWnd->GetSafeHwnd(), NULL,
		x, y, cx, cy, SWP_NOZORDER | SWP_NOACTIVATE);
}

BOOL CGXRecordInfoWnd::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= WS_CLIPCHILDREN;
	return CWnd::PreCreateWindow(cs);
}

BOOL CGXRecordInfoWnd::Create(CWnd* pParentWnd,
		CCreateContext* pContext,
		DWORD dwStyle,
		UINT nID)
{
	WNDCLASS wcls;
	if (::GetClassInfo(AfxGetInstanceHandle(), _T("GXWND"), &wcls) == 0)
	{
		ASSERT(0);
		// ASSERTION-> Did you call GXInit() in the InitInstance method
		// of your application object? ->END
		AfxThrowNotSupportedException();
	}

	ASSERT(pParentWnd != NULL);

	ASSERT(pContext != NULL);
	ASSERT(pContext->m_pNewViewClass != NULL);
	ASSERT(dwStyle & WS_CHILD);

	if (!CreateCommon(pParentWnd, dwStyle | WS_VISIBLE, nID))
		return FALSE;

	CRect rect;
	pParentWnd->GetClientRect(&rect);
	MoveWindow(0, 0, rect.Width(), rect.Height(), FALSE);

	m_pViewClass = pContext->m_pNewViewClass;
		// save for later dynamic creations

	// add the first initial pane
	CWnd* pWnd = CreateView(m_pViewClass, pContext, nID);
	if (pWnd == NULL)
	{
		DestroyWindow(); // will clean up child windows
		return FALSE;
	}

	m_bCtrlsCreated = TRUE;

	GetBeam()->SetNotifyWnd(m_pPane = pWnd);

	return TRUE;
}

#if _MFC_VER < 0x0300
WNDPROC* CGXRecordInfoWnd::GetSuperWndProcAddr()
{
	// Note: it is no longer necessary to override GetSuperWndProcAddr
	//  for each control class with a different WNDCLASS.
	//  This implementation now uses instance data, such that the previous
	//  WNDPROC can be anything.

	static WNDPROC NEAR pfnSuper;
	return &pfnSuper;
}
#endif

BOOL CGXRecordInfoWnd::CreateCommon(CWnd* pParentWnd,
	DWORD dwStyle, UINT nID)
{
	ASSERT(pParentWnd != NULL);
	ASSERT(dwStyle & WS_CHILD);
	ASSERT(nID != 0);

	// the Windows scroll bar styles bits turn no the smart scrollbars
	m_bHasHScroll = (dwStyle & WS_HSCROLL) != 0;
	m_bHasVScroll = (dwStyle & WS_VSCROLL) != 0;
	dwStyle &= ~(WS_HSCROLL | WS_VSCROLL);

	// create with the same wnd-class as MDI-Frame (no erase bkgnd)
	if (m_hWnd == 0)
	{
		if (!CreateEx(0, _T("GxMdiFrame"), NULL, dwStyle, 0, 0, 0, 0,
			pParentWnd->GetSafeHwnd(), (HMENU)(SEC_DWORD)nID, NULL))
		return FALSE;       // create invisible
	}

	// attach the initial scrollbar parts
	TRY
	{
		if (m_bHasHScroll)
			if (!CreateScrollBarCtrl(SBS_HORZ, AFX_IDW_HSCROLL_FIRST))
					AfxThrowResourceException();
		if (m_bHasVScroll)
			if (!CreateScrollBarCtrl(SBS_VERT, AFX_IDW_VSCROLL_FIRST))
					AfxThrowResourceException();

#if _MFC_VER >= 0x0300
		if (GXGetAppData()->bWin4 && (m_bHasHScroll || m_bHasVScroll) && GetParent()->IsFrameWnd())
			if (!CreateScrollBarCtrl(SBS_SIZEGRIP, AFX_IDW_SIZE_BOX))
					AfxThrowResourceException();
#endif

		if (m_pBeam == NULL)
		{
			m_pBeam = (CGXRecordInfoBeam*) m_pBeamClass->CreateObject();
			VERIFY(m_pBeam->Create(WS_VISIBLE, CRect(0, 0, 1, 1), this, IDW_INFOBEAM));
		}
	}
	CATCH_ALL(e)
	{
		DestroyWindow(); // will clean up child windows
		GX_THROW_LAST
		return FALSE;
	}
	END_CATCH_ALL

	return TRUE;
}

BOOL CGXRecordInfoWnd::CreateScrollBarCtrl(DWORD dwStyle, UINT nID)
{
	ASSERT_VALID(this);
	ASSERT(m_hWnd != NULL);

	return (::CreateWindow(_T("SCROLLBAR"), NULL, dwStyle | WS_VISIBLE | WS_CHILD,
		0, 0, 1, 1, m_hWnd, (HMENU)(SEC_DWORD)nID,
		AfxGetInstanceHandle(), NULL) != NULL);
}

#if _MFC_VER >= 0x0300

static CWnd* GetSizingParent(CWnd* pWnd)
{
	ASSERT_VALID(pWnd);

	if (!GXGetAppData()->bWin4)
		return NULL;

	// size box is in lower right corner of this window
	CRect rectClient;
	pWnd->GetClientRect(rectClient);

	// find sizeable parent window
	CWnd* pParent = pWnd;
	if (!(pParent->GetStyle() & WS_THICKFRAME))
		pParent = pWnd->GetParent();

	// only allow if not maximized and has thick frame
	ASSERT_VALID(pParent);
	if ((pParent->GetStyle() & (WS_THICKFRAME|WS_MAXIMIZE)) == WS_THICKFRAME)
	{
		// convert client area of frame window relative to splitter
		CRect rect;
		pParent->GetClientRect(rect);
		pParent->ClientToScreen(rect);
		pWnd->ScreenToClient(rect);

		// must match exactly to get the size box
		if (rectClient.BottomRight() == rect.BottomRight())
			return pParent;
	}

	return NULL;    // no sizeable parent found
}

#endif

void CGXRecordInfoWnd::RecalcLayout()
{		  
	ASSERT_VALID(this);

	if (!m_bCtrlsCreated)
	{
		// TRACE0("RecalcLayout() is creating controls\n");
		VERIFY(CreateCommon(GetParent(), WS_CHILD | WS_HSCROLL | WS_VSCROLL, _GXGetDlgCtrlID(m_hWnd)));
		m_bCtrlsCreated = TRUE;
	}

	CRect rectInside;
	GetInsideRect(rectInside);

	CRect rectClient;
	GetClientRect(rectClient);

	// adjust the panes and scroll bars
	m_cxBeam = m_pBeam->GetWidth();

	// give the hint for the maximum number of HWNDs
	HDWP hDWP = ::BeginDeferWindowPos(5);

	// size of scrollbars
	int cx = (rectClient.right - rectInside.right) - 2*GXGetAppData()->bWin4;
	int cy = (rectClient.bottom - rectInside.bottom) - 2*GXGetAppData()->bWin4;

	{
		int ySB = rectInside.bottom + CY_BORDER;
		CWnd* pScrollBar = GetDlgItem(AFX_IDW_HSCROLL_FIRST);
		ASSERT(pScrollBar != NULL);
		if (m_bHasHScroll)
		{
			int cx = rectInside.right - m_cxBeam - m_cxSplitter;
			hDWP = DeferClientPos(hDWP, pScrollBar, m_cxBeam + m_cxSplitter, ySB,
				cx, cy, TRUE);
		}
		else
			hDWP = DeferClientPos(hDWP, pScrollBar, rectClient.right, ySB,
				0, cy, TRUE);
	}

	// reposition scroll bars
	if (m_bHasVScroll)
	{
		int xSB = rectInside.right + CX_BORDER;
		CWnd* pScrollBar = GetDlgItem(AFX_IDW_VSCROLL_FIRST);
		ASSERT(pScrollBar != NULL);
		int cy = rectInside.bottom;
		hDWP = DeferClientPos(hDWP, pScrollBar, xSB, 0,
			cx, cy, TRUE);
	}


#if _MFC_VER >= 0x0300
	// reposition size box
	if (GXGetAppData()->bWin4 && m_bHasHScroll && m_bHasVScroll && GetParent()->IsFrameWnd())
	{
		int xSB = rectInside.right + 2*CX_BORDER;
		int ySB = rectInside.bottom + 2*CY_BORDER;

		CWnd* pScrollBar = GetDlgItem(AFX_IDW_SIZE_BOX);
		ASSERT(pScrollBar != NULL);

		// fix style if necessary
		BOOL bSizingParent = (GetSizingParent(this) != NULL);
		// modifyStyle returns TRUE if style changes
		if (pScrollBar->ModifyStyle(SBS_SIZEGRIP|SBS_SIZEBOX,
				bSizingParent ? SBS_SIZEGRIP : SBS_SIZEBOX))
			pScrollBar->Invalidate();
		pScrollBar->EnableWindow(bSizingParent);

		// reposition the size box
		hDWP = DeferClientPos(hDWP, pScrollBar,
			xSB, ySB, cx, cy, TRUE);
	}
#endif

	// repositon tab beam
	{
		int ySB = rectInside.bottom + CY_BORDER;
		CWnd* pBeam = GetDlgItem(IDW_INFOBEAM);
		ASSERT(pBeam != NULL);
		int cx = m_bHasHScroll?m_cxBeam:rectClient.right;
		hDWP = DeferClientPos(hDWP, pBeam, 0, ySB,
			cx, cy, FALSE);
	}


	{
		int x = 1;
		int y = 1;
		int cy = rectInside.Height() - 2*CY_BORDER;
		int cx = rectInside.Width() - 2*CX_BORDER;
		if (m_pPane)
		{
			hDWP = DeferClientPos(hDWP, m_pPane, x, y, cx, cy, FALSE);

			// send a WM_SIZE message to the active pane, so that
			// scrollbars will be displayed correctly
			m_pPane->SendMessage(WM_SIZE, SIZE_MAXIMIZED, MAKELONG(cx-x, cy-y));
		}
	}

	::EndDeferWindowPos(hDWP);
}

void CGXRecordInfoWnd::ShowScrollBar(UINT nBar, BOOL bShow)
{
	BOOL bRecalc = FALSE;
	CWnd* pScrollBar;

	// Vertical Scrollbar
	if (nBar == SB_BOTH || nBar == SB_VERT)
	{
		if ((pScrollBar = GetDlgItem(AFX_IDW_VSCROLL_FIRST)) != NULL)
		{
			if (!bShow && m_bHasVScroll)
			{
				pScrollBar->ShowWindow(SW_HIDE);
				pScrollBar->MoveWindow0(FALSE);
				m_bHasVScroll = FALSE;
				bRecalc = TRUE;
			}
			else if (bShow && !m_bHasVScroll)
			{
				pScrollBar->ShowWindow(SW_SHOW);
				m_bHasVScroll = TRUE;
				bRecalc = TRUE;
			}
		}
	}

	// Horizontal Scrollbar
	if (nBar == SB_BOTH || nBar == SB_HORZ)
	{
		if ((pScrollBar = GetDlgItem(AFX_IDW_HSCROLL_FIRST)) != NULL)
		{
			if (!bShow && m_bHasHScroll)
			{
				pScrollBar->ShowWindow(SW_HIDE);
				pScrollBar->MoveWindow0(FALSE);
				m_bHasHScroll = FALSE;
				bRecalc = TRUE;
			}
			else if (bShow && !m_bHasHScroll)
			{
				pScrollBar->ShowWindow(SW_SHOW);
				m_bHasHScroll = TRUE;
				bRecalc = TRUE;
			}
		}
	}

#if _MFC_VER >= 0x0300
	// Size Box
	if (GXGetAppData()->bWin4 && (pScrollBar = GetDlgItem(AFX_IDW_SIZE_BOX)) != NULL && GetParent()->IsFrameWnd())
	{
		if (!m_bHasHScroll || !m_bHasVScroll)
		{
			pScrollBar->ShowWindow(SW_HIDE);
			pScrollBar->MoveWindow0(FALSE);
		}
		else
		{
			pScrollBar->ShowWindow(SW_SHOW);
		}
	}
#endif

	if (bRecalc)
		RecalcLayout();
}

CGXRecordInfoBeam* CGXRecordInfoWnd::GetBeam()
{
	return m_pBeam;
}

// like GetClientRect but inset by shared scrollbars
void CGXRecordInfoWnd::GetInsideRect(CRect& rect) const
{
	ASSERT_VALID(this);

	GetClientRect(rect);
	ASSERT(rect.left == 0 && rect.top == 0);

	// subtract scrollbar clearance
	rect.bottom -= m_nBarWidths - CX_BORDER - GXGetAppData()->bWin4;

	if (m_bHasVScroll)
		rect.right -= m_nBarWidths - CY_BORDER - GXGetAppData()->bWin4;
}

CWnd* CGXRecordInfoWnd::CreateView(CRuntimeClass* pViewClass, CCreateContext* pContext, UINT nID)
{
	BOOL bSendInitialUpdate = FALSE;

	if (nID == 0)
		nID = ++m_nLastViewID;

	CCreateContext contextT;
	if (pContext == NULL)
	{
		// if no context specified, generate one from the currently selected
		//  client if possible
		CView* pOldView = GetParentFrame()->GetActiveView();
		if (pOldView != NULL)
		{
			// set info about last pane
			ASSERT(contextT.m_pCurrentFrame == NULL);
			contextT.m_pLastView = pOldView;
			contextT.m_pCurrentDoc = pOldView->GetDocument();
			if (contextT.m_pCurrentDoc != NULL)
				contextT.m_pNewDocTemplate =
				  contextT.m_pCurrentDoc->GetDocTemplate();
		}
		pContext = &contextT;
		bSendInitialUpdate = TRUE;
	}

	CWnd* pWnd = NULL;
	TRY
	{
		pWnd = (CWnd*)pViewClass->CreateObject();
		if (pWnd == NULL)
			AfxThrowMemoryException();
	}
	CATCH_ALL(e)
	{
		TRACE0("Out of memory creating a splitter pane\n");
		GX_THROW_LAST
		return pWnd;
	}
	END_CATCH_ALL

	ASSERT(pWnd->IsKindOf(RUNTIME_CLASS(CWnd)));
	ASSERT(pWnd->GetSafeHwnd() == NULL);       // not yet created

	// Create with the right size (wrong position)
	CRect rect;
	GetInsideRect(rect);

	DWORD dwStyle = AFX_WS_DEFAULT_VIEW & ~WS_BORDER;

	if (!pWnd->Create(NULL, NULL, dwStyle,
		rect, this, nID, pContext))
	{
		TRACE0("Warning: couldn't create client pane for splitter\n");
			// pWnd will be cleaned up by PostNcDestroy
		return NULL;
	}

	// send initial notification message
	HMENU hMenu = 0;
	if (pContext->m_pNewDocTemplate && pContext->m_pNewDocTemplate->IsKindOf(RUNTIME_CLASS(CMultiDocTemplate)))
		hMenu = ((CMultiDocTemplate*) pContext->m_pNewDocTemplate)->m_hMenuShared;

	if (bSendInitialUpdate)
		pWnd->SendMessage(WM_INITIALUPDATE);

	pWnd->ShowScrollBar(SB_BOTH, FALSE);

	GetBeam()->SetNotifyWnd(m_pPane = pWnd);

	return pWnd;
}

CWnd* CGXRecordInfoWnd::AttachWnd(CWnd* pWnd)
{
	ASSERT(pWnd->IsKindOf(RUNTIME_CLASS(CWnd)));
	ASSERT(pWnd->GetSafeHwnd() != NULL);       // must be created

	// Create with the right size (wrong position)
	CRect rect;
	GetInsideRect(rect);
	pWnd->MoveWindow(rect);

	pWnd->ShowScrollBar(SB_BOTH, FALSE);

	m_pPane = pWnd;

	if (!m_bCtrlsCreated)
		RecalcLayout();

	pWnd->ShowWindow(SW_SHOW);
	pWnd->SetActiveWindow();

	GetBeam()->SetNotifyWnd(pWnd);

	return pWnd;
}

BEGIN_MESSAGE_MAP(CGXRecordInfoWnd, CWnd)
	//{{AFX_MSG_MAP(CGXRecordInfoWnd)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_SETFOCUS()
	ON_WM_ERASEBKGND()
	ON_WM_NCPAINT()
	ON_WM_WININICHANGE()
	ON_WM_SYSCOLORCHANGE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGXRecordInfoWnd message handlers

void CGXRecordInfoWnd::OnPaint()
{
	ASSERT_VALID(this);

	if (!m_bCtrlsCreated || m_bForceRecalcLayout)
		RecalcLayout();

	m_bForceRecalcLayout = FALSE;

	CPaintDC dc(this);

	CRect rectClient;
	GetClientRect(&rectClient);
	CRect rectInside;
	GetInsideRect(rectInside);

	CRect rect;
	rect.top = 0;

	// draw the splitter boxes
	if (m_bHasHScroll)
	{
		CRect rect(m_cxBeam + CX_BORDER,
			rectInside.bottom,
			m_cxBeam+m_cxSplitter,
			rectClient.bottom);

		OnDrawSplitter(&dc, rect);
	}

	// Do not call CWnd::OnPaint() for painting messages
}

void CGXRecordInfoWnd::OnSize(UINT nType, int cx, int cy)
{
	if (m_pPane)
		m_pPane->SendMessage(WM_GX_LOCKRESIZE, GX_STARTRESIZE, 0);

	if (nType != SIZE_MINIMIZED && cx > 0 && cy > 0 && cx < 32767 && cy < 32767)
	{
		m_cxWnd = cx;

		RecalcLayout();
	}

	CWnd::OnSize(nType, cx, cy);

	UpdateWindow();

	if (m_pPane)
	{
		m_pPane->SendMessage(WM_GX_LOCKRESIZE, GX_ENDRESIZE, 0);
		CRect r;
		m_pPane->GetClientRect(r);
		m_pPane->SendMessage(WM_SIZE, nType, MAKELONG(r.Width(), r.Height()));
	}
}

void CGXRecordInfoWnd::OnVScroll(UINT /*nSBCode*/, UINT /*nPos*/, CScrollBar* /*pScrollBar*/)
{
	MSG msg = *GetCurrentMessage();
	if (m_pPane)
		m_pPane->SendMessage(msg.message, msg.wParam, msg.lParam);
}

void CGXRecordInfoWnd::OnHScroll(UINT /*nSBCode*/, UINT /*nPos*/, CScrollBar* /*pScrollBar*/)
{
	MSG msg = *GetCurrentMessage();
	if (m_pPane)
		m_pPane->SendMessage(msg.message, msg.wParam, msg.lParam);
}

void CGXRecordInfoWnd::OnDrawSplitter(CDC* pDC, const CRect& rect)
	// if pDC == NULL then just invalidate
{
	if (pDC == NULL)
	{
		InvalidateRect(rect);
		return;
	}
	ASSERT_VALID(pDC);

	COLORREF rgbFace    = GXGetSysData()->GetSysColor(COLOR_BTNFACE);
	COLORREF rgbFrame   = GXGetSysData()->GetSysColor(COLOR_WINDOWFRAME);

	GXPatB(pDC, rect, GXGetSysData()->GetSysColor(COLOR_WINDOW));
	GXPatB(pDC, rect.left, rect.top, rect.Width(), 1, GXGetAppData()->bWin4 ? rgbFace : rgbFrame);

	// draw black border below info beam
	GXPatB(pDC, rect.left, rect.bottom-1, rect.Width(), 1, rgbBlack);
}

void CGXRecordInfoWnd::OnSetFocus(CWnd* pOldWnd)
{
	CWnd::OnSetFocus(pOldWnd);

	if (m_pPane)
		m_pPane->SetFocus();
}

BOOL CGXRecordInfoWnd::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	GetClientRect(rect);
	rect.left = rect.right - m_nBarWidths + 1;
	pDC->FillRect(rect, &m_brErase);

	COLORREF rgbFace    = GXGetSysData()->GetSysColor(COLOR_BTNFACE);
	COLORREF rgbFrame   = GXGetSysData()->GetSysColor(COLOR_WINDOWFRAME);

	// Black Border
	GXPatB(pDC, rect.left, rect.bottom - m_nBarWidths, rect.Width(), 1, GXGetAppData()->bWin4 ? rgbFace : rgbFrame);

	return TRUE;
}

void CGXRecordInfoWnd::OnNcPaint()
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

void CGXRecordInfoWnd::OnSysColorChange()
{
	CWnd::OnSysColorChange();

	GXGetSysData()->UpdateSysColors();

	m_brErase.DeleteObject();
	m_brErase.CreateSolidBrush(::GetSysColor(COLOR_BTNFACE));

	Invalidate();
}

void CGXRecordInfoWnd::OnWinIniChange(LPCTSTR lpszSection)
{
	CWnd::OnWinIniChange(lpszSection);

	GXGetSysData()->UpdateSysSettings();

	m_cxVScroll = GetSystemMetrics(SM_CXVSCROLL);
	m_cyHScroll = GetSystemMetrics(SM_CYHSCROLL);

	CRect rectBeam;
	m_nBarWidths = m_cyHScroll + 2*GXGetAppData()->bWin4;

	m_bForceRecalcLayout = TRUE;
}

