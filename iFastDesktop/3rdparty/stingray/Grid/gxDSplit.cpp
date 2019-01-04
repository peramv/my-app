///////////////////////////////////////////////////////////////////////////////
// CGXDSplitWnd.cpp : implementation file
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

#define _OG_EXPORT_IMPL

#include "stdafx.h"

#ifndef _GXDSPLIT_H_
#include "grid\gxDSplit.h"
#endif

#ifdef _GXDLL
#undef AFXAPI_DATA
#define AFXAPI_DATA __based(__segname("_DATA"))
#endif

#ifndef __AFXPRIV_H__
#include <afxpriv.h>
#endif //__AFXPRIV_H__

// [VC7] change of path for afximpl.h
#if _MFC_VER >=0x0700
#include <..\src\mfc\afximpl.h>
#else
#ifdef _WIN64
#include <..\src\mfc\afximpl.h>
#else // WIN32
#include <..\src\afximpl.h>
#endif // _WIN64
#endif

const TCHAR gxWndMDIFrame[] = AFX_WNDMDIFRAME;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// Visual attributes and other constants

IMPLEMENT_DYNAMIC(CGXDSplitWnd, CWnd)   // for swap tuning


// implemented in VIEWSCRL.cPP
extern UINT _AfxGetMouseScrollLines(BOOL bForceFresh = FALSE);

/////////////////////////////////////////////////////////////////////////////
// CGXDSplitWnd

BEGIN_MESSAGE_MAP(CGXDSplitWnd, CWnd)
	//{{AFX_MSG_MAP(CGXDSplitWnd)
	ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONUP()
	ON_WM_KEYDOWN()
	ON_WM_SIZE()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_NCCREATE()
	ON_WM_SYSCOMMAND()
	ON_WM_CANCELMODE()
	ON_MESSAGE_VOID(WM_DISPLAYCHANGE, OnDisplayChange)
	ON_MESSAGE_VOID(WM_WININICHANGE, OnDisplayChange)
	ON_MESSAGE_VOID(WM_SETTINGCHANGE, OnDisplayChange)
	ON_WM_MOUSEWHEEL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGXDSplitWnd construction/destruction

//@doc
//@mfunc Constructor
//@rdesc
CGXDSplitWnd::CGXDSplitWnd()
{
	// [VC7] Localized bWin4, bNotWin4, since it is not avilable in
	// afxData.
	DWORD dwVersion = ::GetVersion();
	bWin4 = (BYTE)dwVersion >= 4;
	bNotWin4 = 1 - bWin4;
#if (_MSC_VER >= 0x0700) && (_MSC_VER <= 0x0900)
	// Does not work in VS2010
	AFX_ZERO_INIT_OBJECT(CWnd);
#endif
	// default splitter box/bar sizes (includes borders)
	if (!bWin4)
	{
		m_cxSplitter = m_cySplitter = 4;
		m_cxBorderShare = m_cyBorderShare = 1;
		m_cxSplitterGap = m_cySplitterGap = 4 + 1 + 1;
		ASSERT(m_cxBorder == 0 && m_cyBorder == 0);
	}
	else
	{
		m_cxSplitter = m_cySplitter = 3 + 2 + 2;
		m_cxBorderShare = m_cyBorderShare = 0;
		m_cxSplitterGap = m_cySplitterGap = 3 + 2 + 2;
		m_cxBorder = m_cyBorder = 2;
	}

#ifdef _DEBUG
	if (GetSystemMetrics(SM_CXBORDER) != 1 ||
		GetSystemMetrics(SM_CYBORDER) != 1)
	{
		TRACE0("Warning: CGXDSplitWnd assumes 1 pixel border.\n");
		// will look ugly if borders are not 1 pixel wide and 1 pixel high
	}
#endif
}

//@doc
//@mfunc Destructor
//@rdesc
CGXDSplitWnd::~CGXDSplitWnd()
{
	delete[] m_pRowInfo;
	delete[] m_pColInfo;
}

//@doc CGXDSplitWnd
//@mfunc Call this function to create a dynamic splitter window. It is usually called inside the OnCreateClient function of
//CMainFrame class. Refere to the GridDSplit sample for usage of this class.
//@rdesc BOOL Return TRUE if the creation is successful, otherwise return FALSE.
//@parm CWnd* pParentWnd Pointer to the parent window. It should not be NULL.
//@parm  int nMaxRows The maximum rows. It has to be either 1 or 2.
//@parm  int nMaxCols The maximum columns. It has to be either 1 or 2.
//@parm  SIZE sizeMin The minimun size of the panes.
//@parm  CCreateContext* pContext A pointer to a CCreateContext structure. In most cases,
//this can be the pContext passed to the parent frame window.
//@parm  DWORD dwStyle Specifies the window style. This style must contains SPLS_DYNAMIC_SPLIT and WS_CHILD style in it.
//@parm  UINT nID The child window ID of the window. The ID can be AFX_IDW_PANE_FIRST unless the splitter window is nested inside another splitter window.
BOOL CGXDSplitWnd::Create(CWnd* pParentWnd,	int nMaxRows, int nMaxCols, SIZE sizeMin, CCreateContext* pContext, DWORD dwStyle, UINT nID)
{
	ASSERT(pParentWnd != NULL);
	ASSERT(sizeMin.cx > 0 && sizeMin.cy > 0);   // minimum must be non-zero

	ASSERT(pContext != NULL);
	ASSERT(pContext->m_pNewViewClass != NULL);
	ASSERT(dwStyle & WS_CHILD);
	ASSERT(dwStyle & SPLS_DYNAMIC_SPLIT);   // must have dynamic split behavior

	// Dynamic splitters are limited to 2x2
	ASSERT(nMaxRows >= 1 && nMaxRows <= 2);
	ASSERT(nMaxCols >= 1 && nMaxCols <= 2);
	ASSERT(nMaxCols > 1 || nMaxRows > 1);       // 1x1 is not permitted

	m_nMaxRows = nMaxRows;
	m_nMaxCols = nMaxCols;
	ASSERT(m_nRows == 0 && m_nCols == 0);       // none yet
	m_nRows = m_nCols = 1;      // start off as 1x1
	if (!CreateCommon(pParentWnd, sizeMin, dwStyle, nID))
		return FALSE;
	ASSERT(m_nRows == 1 && m_nCols == 1);       // still 1x1

	ASSERT(pContext->m_pNewViewClass->IsDerivedFrom(RUNTIME_CLASS(CWnd)));
	m_pDynamicViewClass = pContext->m_pNewViewClass;
		// save for later dynamic creations

	// add the first initial pane
	if (!CreateView(0, 0, m_pDynamicViewClass, sizeMin, pContext))
	{
		DestroyWindow(); // will clean up child windows
		return FALSE;
	}
	m_pColInfo[0].nIdealSize = sizeMin.cx;
	m_pRowInfo[0].nIdealSize = sizeMin.cy;

	return TRUE;
}

// simple "wiper" splitter
//@doc CGXDSplitWnd
//@mfunc Call this function to create a static splitter window. However, it is recommended that you use
//CGXSplitterWnd if you only want to support static splitter window.
//@rdesc BOOL Return TRUE if the creation succeeded, otherwise return FALSE.
//@parm CWnd* pParentWnd A pointer to the parent window.
//@parm  int nRows The number of rows the window to be splitted.
//@parm  int nCols The number of columns the window to be splitted.
//@parm  DWORD dwStyle Style of the window. It cann't contain SPLS_DYNAMIC_SPLIT style and has to have WS_CHILD style.
//@parm  UINT nID The child window ID of the window. The ID can be AFX_IDW_PANE_FIRST
//unless the splitter window is nested inside another splitter window.
BOOL CGXDSplitWnd::CreateStatic(CWnd* pParentWnd, int nRows, int nCols, DWORD dwStyle, UINT nID)
{
	ASSERT(pParentWnd != NULL);
	ASSERT(nRows >= 1 && nRows <= 16);
	ASSERT(nCols >= 1 && nCols <= 16);
	ASSERT(nCols > 1 || nRows > 1);     // 1x1 is not permitted
	ASSERT(dwStyle & WS_CHILD);
	ASSERT(!(dwStyle & SPLS_DYNAMIC_SPLIT)); // can't have dynamic split

	ASSERT(m_nRows == 0 && m_nCols == 0);       // none yet
	m_nRows = m_nMaxRows = nRows;
	m_nCols = m_nMaxCols = nCols;

	// create with zero minimum pane size
	if (!CreateCommon(pParentWnd, CSize(0, 0), dwStyle, nID))
		return FALSE;

	// all panes must be created with explicit calls to CreateView
	return TRUE;
}

//@doc CGXDSplitWnd
//@mfunc A helper function called by both Create and CreateStatic to create the splitter window.
//@rdesc BOOL Return TRUE if the creation is successful, otherwise return FALSE.
//@parm CWnd* pParentWnd A pointer to the parent window.
//@parm  SIZE sizeMin Minimal size of the panes.
//@parm  DWORD dwStyle Style of the window passed in Create or CreateStatic method.
//@parm  UINT nID The id for this window passed in the Create or CreateStatic method.
BOOL CGXDSplitWnd::CreateCommon(CWnd* pParentWnd, SIZE sizeMin, DWORD dwStyle, UINT nID)
{
	ASSERT(pParentWnd != NULL);
	ASSERT(sizeMin.cx >= 0 && sizeMin.cy >= 0);
	ASSERT(dwStyle & WS_CHILD);
	ASSERT(nID != 0);

	ASSERT(m_pColInfo == NULL && m_pRowInfo == NULL);   // only do once
	ASSERT(m_nMaxCols > 0 && m_nMaxRows > 0);

	// the Windows scroll bar styles bits turn on the smart scrollbars
	DWORD dwCreateStyle = dwStyle & ~(WS_HSCROLL|WS_VSCROLL);
	if (bWin4)
		dwCreateStyle &= ~WS_BORDER;

	if (!AfxDeferRegisterClass(AFX_WNDMDIFRAME_REG))
		return FALSE;

	// create with the same wnd-class as MDI-Frame (no erase bkgnd)
	if (!CreateEx(0, gxWndMDIFrame, NULL, dwCreateStyle, 0, 0, 0, 0,
	  pParentWnd->GetSafeHwnd(), (HMENU)(SEC_DWORD)nID, NULL))
		return FALSE;       // create invisible

	// attach the initial splitter parts
	TRY
	{
		m_pColInfo = new CRowColInfo[m_nMaxCols];
		for (int col = 0; col < m_nMaxCols; col++)
		{
			m_pColInfo[col].nMinSize = m_pColInfo[col].nIdealSize = sizeMin.cx;
			m_pColInfo[col].nCurSize = -1; // will be set in RecalcLayout
		}
		m_pRowInfo = new CRowColInfo[m_nMaxRows];
		for (int row = 0; row < m_nMaxRows; row++)
		{
			m_pRowInfo[row].nMinSize = m_pRowInfo[row].nIdealSize = sizeMin.cy;
			m_pRowInfo[row].nCurSize = -1; // will be set in RecalcLayout
		}

		// create scroll bars by setting the style
		SetScrollStyle(dwStyle);
	}
	CATCH_ALL(e)
	{
		DestroyWindow(); // will clean up child windows
		// Note: DELETE_EXCEPTION(e) not required
		return FALSE;
	}
	END_CATCH_ALL

	return TRUE;
}

//@doc CGXDSplitWnd
//@mfunc WM_NCCREATE message handler.
//@rdesc BOOL Return TRUE if the creation can be continued, otherwise return FALSE.
//@parm LPCREATESTRUCT lpcs Pointer to the creation structure.
BOOL CGXDSplitWnd::OnNcCreate(LPCREATESTRUCT lpcs)
{
	if (!CWnd::OnNcCreate(lpcs))
		return FALSE;

	// remove WS_EX_CLIENTEDGE style from parent window
	//  (the splitter itself will provide the 3d look)
	CWnd* pParent = GetParent();
	ASSERT_VALID(pParent);
	pParent->ModifyStyleEx(WS_EX_CLIENTEDGE, 0, SWP_DRAWFRAME);

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CGXDSplitWnd default creation of parts

// You must create ALL panes unless DYNAMIC_SPLIT is defined!
//  Usually the splitter window is invisible when creating a pane

//@doc CGXDSplitWnd
//@mfunc This function is called to create window for each of the panes in the splitter window.
//If you created the window using Create method, the windows in the pane is automatically created
//by Create method. If you created the window using CreateStatic, then you need to create windows
//for each of the pane using this method. It is not required the window in the pane to be CView
//derived.
//@rdesc BOOL Return TRUE if the creation is successful, otherwise return FALSE.
//@parm int row The row index of the pane to create this window for.
//@parm  int col The column index of the pane to create this window for.
//@parm  CRuntimeClass* pViewClass A pointer to the runtime class of the window to be created.
//@parm  SIZE sizeInit The initial size of the window.
//@parm  CCreateContext* pContext A pointer to a creation context used to create the view
//(usually the pContext passed into the parent frame’s overridden CFrameWnd::OnCreateClient
//member function in which the splitter window is being created).
BOOL CGXDSplitWnd::CreateView(int row, int col, CRuntimeClass* pViewClass, SIZE sizeInit, CCreateContext* pContext)
{
#ifdef _DEBUG
	ASSERT_VALID(this);
	ASSERT(row >= 0 && row < m_nRows);
	ASSERT(col >= 0 && col < m_nCols);
	ASSERT(pViewClass != NULL);
	ASSERT(pViewClass->IsDerivedFrom(RUNTIME_CLASS(CWnd)));
	ASSERT(AfxIsValidAddress(pViewClass, sizeof(CRuntimeClass), FALSE));

	if (GetDlgItem(IdFromRowCol(row, col)) != NULL)
	{
		TRACE2("Error: CreateView - pane already exists for row %d, col %d.\n",
			row, col);
		ASSERT(FALSE);
		return FALSE;
	}
#endif

	// set the initial size for that pane
	m_pColInfo[col].nIdealSize = sizeInit.cx;
	m_pRowInfo[row].nIdealSize = sizeInit.cy;

	BOOL bSendInitialUpdate = FALSE;

	CCreateContext contextT;
	if (pContext == NULL)
	{
		// if no context specified, generate one from the currently selected
		//  client if possible
		CView* pOldView = (CView*) GetFirstCView( ); //(CView*)GetActivePane();
		if (pOldView != NULL && pOldView->IsKindOf(RUNTIME_CLASS(CView)))
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

	CWnd* pWnd;
	TRY
	{
		pWnd = (CWnd*)pViewClass->CreateObject();
		if (pWnd == NULL)
			AfxThrowMemoryException();
	}
	CATCH_ALL(e)
	{
		TRACE0("Out of memory creating a splitter pane.\n");
		// Note: DELETE_EXCEPTION(e) not required
		return FALSE;
	}
	END_CATCH_ALL

	ASSERT_KINDOF(CWnd, pWnd);
	ASSERT(pWnd->GetSafeHwnd() == NULL);       // not yet created

	DWORD dwStyle = AFX_WS_DEFAULT_VIEW;
	if (bWin4)
		dwStyle &= ~WS_BORDER;

	// Create with the right size (wrong position)
	CRect rect(CPoint(0,0), sizeInit);
	if (!pWnd->Create(NULL, NULL, dwStyle,
		rect, this, IdFromRowCol(row, col), pContext))
	{
		TRACE0("Warning: couldn't create client pane for splitter.\n");
			// pWnd will be cleaned up by PostNcDestroy
		return FALSE;
	}
	ASSERT((int)_AfxGetDlgCtrlID(pWnd->GetSafeHwnd()) == IdFromRowCol(row, col));

	// send initial notification message
	if (bSendInitialUpdate)
		pWnd->SendMessage(WM_INITIALUPDATE);

	return TRUE;
}

CView* CGXDSplitWnd::GetFirstCView()
{
	// walk through HWNDs to avoid creating temporary CWnd objects
	// unless we need to call this function recursively
	for (HWND hWndChild = ::GetTopWindow(m_hWnd); hWndChild != NULL;
		hWndChild = ::GetNextWindow(hWndChild, GW_HWNDNEXT))
	{

			CWnd* pWnd = CWnd::FromHandlePermanent(hWndChild);
			if (pWnd != NULL)
			{
				if(pWnd->IsKindOf(RUNTIME_CLASS(CView)))
					return (CView*) pWnd;
			}
	}

	return NULL;
}


//@doc CGXDSplitWnd
//@mfunc A helper function to create the scroll bar for the splitter window.
//@rdesc BOOL Return TRUE if the creation is successful, otherwise return FALSE.
//@parm DWORD dwStyle The style for the scroll bar to be created.
//@parm  UINT nID The id for the scroll bar to be created.
BOOL CGXDSplitWnd::CreateScrollBarCtrl(DWORD dwStyle, UINT nID)
{
	ASSERT_VALID(this);
	ASSERT(this->GetSafeHwnd() != NULL);

//	ASSERT(((dwStyle & SB_VERT) == SB_VERT) || ((dwStyle & SBS_SIZEBOX) == SBS_SIZEBOX));

	HWND hParent = (((dwStyle & SB_VERT) == SB_VERT) || ((dwStyle & SBS_SIZEBOX) == SBS_SIZEBOX)) ? this->GetSafeHwnd():m_pOwnerWnd->m_hWnd;

	if(hParent == m_hWnd)
	return (::CreateWindow(_T("SCROLLBAR"), NULL,
		dwStyle | WS_VISIBLE | WS_CHILD,
		0, 0, 1, 1, hParent, (HMENU)(SEC_DWORD)nID,
		AfxGetInstanceHandle(), NULL) != NULL);
	else
		return ((CGXDTabWnd*)m_pOwnerWnd)->CreateScrollBarCtrl(dwStyle, nID);
}

//@doc CGXDSplitWnd
//@mfunc A helper function to convert the row-columnn index to the id of the pane.
//@rdesc int The id of the given pane.
//@parm int row The row index of the pane.
//@parm  int col The column index of the pane.
int CGXDSplitWnd::IdFromRowCol(int row, int col) const
{
	ASSERT_VALID(this);
	ASSERT(row >= 0);
	ASSERT(row < m_nRows);
	ASSERT(col >= 0);
	ASSERT(col < m_nCols);

	return AFX_IDW_PANE_FIRST + row * 16 + col;
}

/////////////////////////////////////////////////////////////////////////////
// CGXDSplitWnd attributes

//@doc CGXDSplitWnd
//@mfunc Call this function to obtain a pointer to the window in the given pane.
//@rdesc CWnd* A pointer to the window in the gvien pane.
//@parm int row The row index of the pane.
//@parm  int col The column index of the pane.
CWnd* CGXDSplitWnd::GetPane(int row, int col) const
{
	ASSERT_VALID(this);

	CWnd* pView = GetDlgItem(IdFromRowCol(row, col));
	ASSERT(pView != NULL);  // panes can be a CWnd, but are usually CViews

	// this is possible if the view is a tab window created view
	if(pView == NULL)
	{
		pView = GetDlgItem(IdFromRowCol(row, col));
	}

	if(pView)
		ASSERT(pView->GetParent()->GetSafeHwnd() == this->GetSafeHwnd());

	return pView;
}

//@doc CGXDSplitWnd
//@mfunc This function is called to check if a given window is in any pane of the splitter window.
//@rdesc BOOL Return TRUE if the window is in some pane of the splitter window, otherwise return FALSE.
//@parm CWnd* pWnd The pointer to a window to be checked for.
//@parm  int* pRow If the window is in some pane, the pointer to integer is used to accept the row index of the pane.
//@parm  int* pCol If the window is in some pane, the pointer to integer is used to accept the column index of the pane.
BOOL CGXDSplitWnd::IsChildPane(CWnd* pWnd, int* pRow, int* pCol)
{
	ASSERT_VALID(this);
	ASSERT_VALID(pWnd);

	UINT nID = _AfxGetDlgCtrlID(pWnd->GetSafeHwnd());
	if (IsChild(pWnd) && nID >= AFX_IDW_PANE_FIRST && nID <= AFX_IDW_PANE_LAST)
	{
		if (pRow != NULL)
			*pRow = (nID - AFX_IDW_PANE_FIRST) / 16;
		if (pCol != NULL)
			*pCol = (nID - AFX_IDW_PANE_FIRST) % 16;
		ASSERT(pRow == NULL || *pRow < m_nRows);
		ASSERT(pCol == NULL || *pCol < m_nCols);
		return TRUE;
	}
	else
	{
		if (pRow != NULL)
			*pRow = -1;
		if (pCol != NULL)
			*pCol = -1;
		return FALSE;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CGXDSplitWnd information access

// The get routines return the current size
// The set routines set the ideal size
//  RecalcLayout must be called to update current size

//@doc CGXDSplitWnd
//@mfunc Obtain the row size information of the given row.
//@rdesc void
//@parm int row The index of the row.
//@parm  int& cyCur A reference to an integer to accept the current height of the row.
//@parm  int& cyMin A reference to an integer to accept the minimal height of the row.
void CGXDSplitWnd::GetRowInfo(int row, int& cyCur, int& cyMin) const
{
	ASSERT_VALID(this);
	ASSERT(row >= 0 && row < m_nMaxRows);

	cyCur = m_pRowInfo[row].nCurSize;
	cyMin = m_pRowInfo[row].nMinSize;
}

//@doc CGXDSplitWnd
//@mfunc Store the row size information of the given row.
//@rdesc void
//@parm int row The index of the row.
//@parm  int cyIdeal The ideal height of the row.
//@parm  int cyMin The minimal height of the row. If a row height is less than this value by resizing
//window or drgging splitter bar, the row will be deleted.
void CGXDSplitWnd::SetRowInfo(int row, int cyIdeal, int cyMin)
{
	ASSERT_VALID(this);
	ASSERT(row >= 0 && row < m_nMaxRows);
	ASSERT(cyIdeal >= 0);
	ASSERT(cyMin >= 0);

	m_pRowInfo[row].nIdealSize = cyIdeal;
	m_pRowInfo[row].nMinSize = cyMin;
}

//@doc CGXDSplitWnd
//@mfunc Obtain the column size information for the given column.
//@rdesc void
//@parm int col The index of the column.
//@parm  int& cxCur A reference to an integer to accept the current width of the column.
//@parm  int& cxMin A reference to an integer to accept the minimal width of the column.
void CGXDSplitWnd::GetColumnInfo(int col, int& cxCur, int& cxMin) const
{
	ASSERT_VALID(this);
	ASSERT(col >= 0 && col < m_nMaxCols);

	cxCur = m_pColInfo[col].nCurSize;
	cxMin = m_pColInfo[col].nMinSize;
}

//@doc CGXDSplitWnd
//@mfunc Store the column size information for the given column.
//@rdesc void
//@parm int col The zero-based index of the column.
//@parm  int cxIdeal The ideal width of the column.
//@parm  int cxMin The minimal width of the column, if a column width is less than this value by resizing
//window or dragging the splitter bar, the column will be deleted.
void CGXDSplitWnd::SetColumnInfo(int col, int cxIdeal, int cxMin)
{
	ASSERT_VALID(this);
	ASSERT(col >= 0 && col < m_nMaxCols);
	ASSERT(cxIdeal >= 0);
	ASSERT(cxMin >= 0);

	m_pColInfo[col].nIdealSize = cxIdeal;
	m_pColInfo[col].nMinSize = cxMin;
}

//@doc CGXDSplitWnd
//@mfunc Call this function to obtain the scroll bar style information.
//@rdesc DWORD The style that contains the scroll bar style information.
DWORD CGXDSplitWnd::GetScrollStyle() const
{
	DWORD dwStyle = 0;
	if (m_bHasHScroll)
		dwStyle |= WS_HSCROLL;
	if (m_bHasVScroll)
		dwStyle |= WS_VSCROLL;
	return dwStyle;
}

//@doc CGXDSplitWnd
//@mfunc Set the scroll bar style. Note that this splitter window always create the vertical scroll bars and
//horizontal scroll bars. Depending on the WS_HSCROLL and WS_VSCROLL style bit of the style, the scroll bars are
//either hidden or shown.
//@rdesc void
//@parm DWORD dwStyle The style containing the scroll bar style information.
void CGXDSplitWnd::SetScrollStyle(DWORD dwStyle)
{
	// optimize for scroll info already set correctly
	dwStyle &= (WS_HSCROLL|WS_VSCROLL);
	if (GetScrollStyle() == dwStyle)
		return;

	// update to new state
	m_bHasHScroll = (dwStyle & WS_HSCROLL) != 0;
	m_bHasVScroll = (dwStyle & WS_VSCROLL) != 0;

	CWnd* pScrollBar;

	// show/hide all the shared horz scroll bars
	for (int col = 0; col < m_nCols; col++)
	{
		pScrollBar = m_pOwnerWnd->GetDlgItem(AFX_IDW_HSCROLL_FIRST + col);
		if (pScrollBar == NULL)
		{
			// create the scroll bar when necessary
			if (!CreateScrollBarCtrl(SBS_HORZ, AFX_IDW_HSCROLL_FIRST + col))
				AfxThrowResourceException();
			pScrollBar = m_pOwnerWnd->GetDlgItem(AFX_IDW_HSCROLL_FIRST + col);
		}
		pScrollBar->ShowWindow(m_bHasHScroll ? SW_SHOW : SW_HIDE);
	}

	// show/hide all the shared vert scroll bars
	for (int row = 0; row < m_nRows; row++)
	{
		pScrollBar = GetDlgItem(AFX_IDW_VSCROLL_FIRST + row);
		if (pScrollBar == NULL)
		{
			// create the scroll bar when necessary
			if (!CreateScrollBarCtrl(SBS_VERT, AFX_IDW_VSCROLL_FIRST + row))
				AfxThrowResourceException();
			pScrollBar = GetDlgItem(AFX_IDW_VSCROLL_FIRST + row);
		}
		pScrollBar->ShowWindow(m_bHasVScroll ? SW_SHOW : SW_HIDE);
	}

	// show/destroy size box if necessary
	if (m_bHasVScroll && m_bHasHScroll)
	{
		pScrollBar = GetDlgItem(AFX_IDW_SIZE_BOX);
		if (pScrollBar == NULL)
		{
			// create size box when necessary
			if (!CreateScrollBarCtrl(SBS_SIZEBOX|WS_DISABLED, AFX_IDW_SIZE_BOX))
				AfxThrowResourceException();
			pScrollBar = GetDlgItem(AFX_IDW_SIZE_BOX);
		}
		pScrollBar->ShowWindow(SW_SHOW);
	}
	else
	{
		// the size box can be destroyed instead of hidden
		pScrollBar = GetDlgItem(AFX_IDW_SIZE_BOX);
		if (pScrollBar != NULL)
			pScrollBar->DestroyWindow();
	}

	// Note: call RecalcLayout for the new layout to take effect
}

/////////////////////////////////////////////////////////////////////////////
// CGXDSplitWnd client operations/overridables

//@doc CGXDSplitWnd
//@mfunc A helper function to delete the window in the given pane.
//@rdesc void
//@parm int row The zero-based row index of the pane.
//@parm  int col The zero-based column index of the pane.
void CGXDSplitWnd::DeleteView(int row, int col)
{
	ASSERT_VALID(this);

	// if active child is being deleted - activate next
	CWnd* pPane = GetPane(row, col);
	ASSERT_KINDOF(CView, pPane);
	if (GetActivePane() == pPane)
		ActivateNext(FALSE);

	// default implementation assumes view will auto delete in PostNcDestroy
	pPane->DestroyWindow();
}

//@doc CGXDSplitWnd
//@mfunc Call this function to draw the the splitter bars and splitter boxes.
//@rdesc void
//@parm CDC* pDC A pointer to the device context to draw on. If pDC is NULL,
//then RedrawWindow is called and no split window is drawn.
//@parm  ESplitType nType A value of the enum ESplitType, which can be one of the following:<nl>
//splitBox   The splitter drag box.<nl>
//splitBar   The bar that appears between the two split windows.<nl>
//splitIntersection The intersection of the split windows. This element will not be called when running on Windows 95.<nl>
//splitBorder   The split window borders. <nl>
//@parm  const CRect& rectArg A reference to a CRect object specifying the size and shape of the split windows.
void CGXDSplitWnd::OnDrawSplitter(CDC* pDC, ESplitType nType, const CRect& rectArg)
{
	// if pDC == NULL, then just invalidate
	if (pDC == NULL)
	{
		RedrawWindow(rectArg, NULL, RDW_INVALIDATE|RDW_NOCHILDREN);
		return;
	}
	ASSERT_VALID(pDC);

	// otherwise, actually draw
	CRect rect = rectArg;
	switch (nType)
	{
	case splitBorder:
		ASSERT(bWin4);
		pDC->Draw3dRect(rect, afxData.clrBtnShadow, afxData.clrBtnHilite);
		rect.InflateRect(-CX_BORDER, -CY_BORDER);
		pDC->Draw3dRect(rect, afxData.clrWindowFrame, afxData.clrBtnFace);
		return;

	case splitIntersection:
		ASSERT(!bWin4);
		break;

	case splitBox:
		if (bWin4)
		{
			pDC->Draw3dRect(rect, afxData.clrBtnFace, afxData.clrWindowFrame);
			rect.InflateRect(-CX_BORDER, -CY_BORDER);
			pDC->Draw3dRect(rect, afxData.clrBtnHilite, afxData.clrBtnShadow);
			rect.InflateRect(-CX_BORDER, -CY_BORDER);
			break;
		}
		// fall through...
	case splitBar:
		if (!bWin4)
		{
			pDC->Draw3dRect(rect, afxData.clrBtnHilite, afxData.clrBtnShadow);
			rect.InflateRect(-CX_BORDER, -CY_BORDER);
		}
		break;

	default:
		ASSERT(FALSE);  // unknown splitter type
	}

	// fill the middle
	COLORREF clr = afxData.clrBtnFace;
#ifdef _MAC
	// just use white for interior if less than 16 colors
	if (pDC->GetDeviceCaps(NUMCOLORS) < 16)
		clr = RGB(0xFF, 0xFF, 0xFF);
#endif
	pDC->FillSolidRect(rect, clr);
}

/////////////////////////////////////////////////////////////////////////////
// Dynamic row/col split etc

static int AFXAPI CanSplitRowCol(CGXDSplitWnd::CRowColInfo* pInfoBefore,
	int nBeforeSize, int nSizeSplitter)
	// request to split Before row at point nBeforeSize
	// returns size of new pane (nBeforeSize will be new size of Before pane)
	// return -1 if not big enough
{
	ASSERT(pInfoBefore->nCurSize > 0);
	ASSERT(pInfoBefore->nMinSize > 0);
	ASSERT(nBeforeSize <= pInfoBefore->nCurSize);

	// space gets take from before pane (weird UI for > 2 splits)
	if (nBeforeSize < pInfoBefore->nMinSize)
	{
		TRACE0("Warning: split too small to fit in a new pane.\n");
		return -1;
	}

	int nNewSize = pInfoBefore->nCurSize - nBeforeSize - nSizeSplitter;
	if (nBeforeSize < pInfoBefore->nMinSize)
	{
		TRACE0("Warning: split too small to shrink old pane.\n");
		return -1;
	}
	if (nNewSize < (pInfoBefore+1)->nMinSize)
	{
		TRACE0("Warning: split too small to create new pane.\n");
		return -1;
	}
	return nNewSize;
}

//@doc CGXDSplitWnd
//@mfunc Call this function to split the row at the given position.
//@rdesc BOOL Return TRUE if the splitting is successful, otherwise return FALSE.
//@parm int cyBefore The position, in pixels, before which the split occurs.
BOOL CGXDSplitWnd::SplitRow(int cyBefore)
{
	ASSERT_VALID(this);
	ASSERT(GetStyle() & SPLS_DYNAMIC_SPLIT);
	ASSERT(m_pDynamicViewClass != NULL);
	ASSERT(m_nRows < m_nMaxRows);

	cyBefore -= m_cyBorder;
	int rowNew = m_nRows;
	int cyNew = CanSplitRowCol(&m_pRowInfo[rowNew-1], cyBefore, m_cySplitter);
	if (cyNew == -1)
		return FALSE;   // too small to split

	// create the scroll bar first (so new views can see that it is there)
	if (m_bHasVScroll &&
		!CreateScrollBarCtrl(SBS_VERT, AFX_IDW_VSCROLL_FIRST + rowNew))
	{
		TRACE0("Warning: SplitRow failed to create scroll bar.\n");
		return FALSE;
	}

	m_nRows++;  // bump count during view creation

	// create new views to fill the new row (RecalcLayout will position)
	for (int col = 0; col < m_nCols; col++)
	{
		CSize size(m_pColInfo[col].nCurSize, cyNew);
		if (!CreateView(rowNew, col, m_pDynamicViewClass, size, NULL))
		{
			TRACE0("Warning: SplitRow failed to create new row.\n");
			// delete anything we partially created 'col' = # columns created
			while (col > 0)
				DeleteView(rowNew, --col);
			if (m_bHasVScroll)
				GetDlgItem(AFX_IDW_VSCROLL_FIRST + rowNew)->DestroyWindow();
			m_nRows--;      // it didn't work out
			return FALSE;
		}
	}

	// new parts created - resize and re-layout
	m_pRowInfo[rowNew-1].nIdealSize = cyBefore;
	m_pRowInfo[rowNew].nIdealSize = cyNew;
	ASSERT(m_nRows == rowNew+1);
	RecalcLayout();

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE|RDW_INTERNALPAINT |RDW_FRAME);

	return TRUE;
}

//@doc CGXDSplitWnd
//@mfunc Call this function to split column at the given position
//@rdesc BOOL Return TRUE if the splitting is successful, otherwise return FALSE.
//@parm int cxBefore The position, in pixels, before which the split occurs.
BOOL CGXDSplitWnd::SplitColumn(int cxBefore)
{
	ASSERT_VALID(this);
	ASSERT(GetStyle() & SPLS_DYNAMIC_SPLIT);
	ASSERT(m_pDynamicViewClass != NULL);
	ASSERT(m_nCols < m_nMaxCols);

	cxBefore -= m_cxBorder;
	int colNew = m_nCols;
	int cxNew = CanSplitRowCol(&m_pColInfo[colNew-1], cxBefore, m_cxSplitter);
	if (cxNew == -1)
		return FALSE;   // too small to split

	// create the scroll bar first (so new views can see that it is there)
	if (m_bHasHScroll &&
		!CreateScrollBarCtrl(SBS_HORZ, AFX_IDW_HSCROLL_FIRST + colNew))
	{
		TRACE0("Warning: SplitRow failed to create scroll bar.\n");
		return FALSE;
	}

	m_nCols++;  // bump count during view creation

	// create new views to fill the new column (RecalcLayout will position)
	for (int row = 0; row < m_nRows; row++)
	{
		CSize size(cxNew, m_pRowInfo[row].nCurSize);
		if (!CreateView(row, colNew, m_pDynamicViewClass, size, NULL))
		{
			TRACE0("Warning: SplitColumn failed to create new column.\n");
			// delete anything we partially created 'col' = # columns created
			while (row > 0)
				DeleteView(--row, colNew);
			if (m_bHasHScroll)
				m_pOwnerWnd->GetDlgItem(AFX_IDW_HSCROLL_FIRST + colNew)->DestroyWindow();
			m_nCols--;      // it didn't work out
			return FALSE;
		}
	}

	// new parts created - resize and re-layout
	m_pColInfo[colNew-1].nIdealSize = cxBefore;
	m_pColInfo[colNew].nIdealSize = cxNew;
	ASSERT(m_nCols == colNew+1);
	RecalcLayout();

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE|RDW_INTERNALPAINT |RDW_FRAME);

	return TRUE;
}

//@doc CGXDSplitWnd
//@mfunc Call this function to delete the given row of the splitter window.
//@rdesc void
//@parm int rowDelete The zero-based index of the row to be deleted.
void CGXDSplitWnd::DeleteRow(int rowDelete)
{
	ASSERT_VALID(this);
	ASSERT(GetStyle() & SPLS_DYNAMIC_SPLIT);

	ASSERT(m_nRows > 1);
	ASSERT(rowDelete < m_nRows);

	int rowActive, colActive;
	if (GetActivePane(&rowActive, &colActive) != NULL && rowActive == rowDelete)
	{
		if (++rowActive >= m_nRows)
			rowActive = 0;
		SetActivePane(rowActive, colActive);
	}

	CWnd* pScrollDel = m_bHasVScroll ?
		GetDlgItem(AFX_IDW_VSCROLL_FIRST+rowDelete) : NULL;
	for (int col = 0; col < m_nCols; col++)
	{
		DeleteView(rowDelete, col);
		for (int row = rowDelete+1; row < m_nRows; row++)
		{
			CWnd* pPane = GetPane(row, col);
			ASSERT(pPane != NULL);
			pPane->SetDlgCtrlID(IdFromRowCol(row-1, col));
			if (m_bHasVScroll && col == m_nCols-1)
			{
				CWnd* pScroll = GetDlgItem(AFX_IDW_VSCROLL_FIRST+row);
				if (pScroll != NULL)
					pScroll->SetDlgCtrlID(AFX_IDW_VSCROLL_FIRST+row-1);
			}
		}
	}
	m_nRows--;
	if (pScrollDel != NULL)
		pScrollDel->DestroyWindow();

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE|RDW_INTERNALPAINT |RDW_FRAME);

	RecalcLayout();     // re-assign the space
}

//@doc CGXDSplitWnd
//@mfunc Call this function to delete the given column of the splitter window.
//@rdesc void
//@parm int colDelete The zero-based index of the column to be deleted.
void CGXDSplitWnd::DeleteColumn(int colDelete)
{
	ASSERT_VALID(this);
	ASSERT(GetStyle() & SPLS_DYNAMIC_SPLIT);

	ASSERT(m_nCols > 1);
	ASSERT(colDelete < m_nCols);

	int rowActive, colActive;
	if (GetActivePane(&rowActive, &colActive) != NULL && colActive == colDelete)
	{
		if (++colActive >= m_nCols)
			colActive = 0;
		SetActivePane(rowActive, colActive);
	}

	CWnd* pScrollDel = m_bHasHScroll ?
		m_pOwnerWnd->GetDlgItem(AFX_IDW_HSCROLL_FIRST+colDelete) : NULL;
	for (int row = 0; row < m_nRows; row++)
	{
		DeleteView(row, colDelete);
		for (int col = colDelete+1; col < m_nCols; col++)
		{
			CWnd* pPane = GetPane(row, col);
			ASSERT(pPane != NULL);
			pPane->SetDlgCtrlID(IdFromRowCol(row, col-1));
			if (m_bHasHScroll && row == m_nRows-1)
			{
				CWnd* pScroll = m_pOwnerWnd->GetDlgItem(AFX_IDW_HSCROLL_FIRST+col);
				if (pScroll != NULL)
					pScroll->SetDlgCtrlID(AFX_IDW_HSCROLL_FIRST+col-1);
			}
		}
	}
	m_nCols--;
	if (pScrollDel != NULL)
		pScrollDel->DestroyWindow();

	if(GetParent() && GetParent()->IsKindOf(RUNTIME_CLASS(CGXDTabWnd)))
		((CGXDTabWnd*)GetParent())->RecalcLayout();


	RecalcLayout();     // re-assign the space
}

/////////////////////////////////////////////////////////////////////////////
// CGXDSplitWnd tracking support

// like GetClientRect but inset by shared scrollbars
//@doc CGXDSplitWnd
//@mfunc A helper method to calculate the rectangle area of client rectange minus the area used by scroll bar.
//@rdesc void
//@parm CRect& rect
void CGXDSplitWnd::GetInsideRect(CRect& rect) const
{
	ASSERT_VALID(this);

	GetClientRect(rect);
	ASSERT(rect.left == 0 && rect.top == 0);

	// subtract space for 3d borders
	rect.InflateRect(-m_cxBorder, -m_cyBorder);

	// subtract scrollbar clearance
	if (m_bHasVScroll)
		rect.right -= afxData.cxVScroll - CX_BORDER;

	//if (m_bHasHScroll)
	//	rect.bottom -= afxData.cyHScroll - CY_BORDER;

}

class _cview:public CView
{
	friend class CGXDSplitWnd;
};

//@doc CGXDSplitWnd
//@mfunc Start the mouse tracking with the given hit testing result.
//@rdesc void
//@parm int ht The hit testing result. Refer to HitTest method for possible values.
void CGXDSplitWnd::StartTracking(int ht)
{
	ASSERT_VALID(this);
	if (ht == noHit)
		return;

	// GetHitRect will restrict 'm_rectLimit' as appropriate
	GetInsideRect(m_rectLimit);

	if (ht >= splitterIntersection1 && ht <= splitterIntersection225)
	{
		// split two directions (two tracking rectangles)
		int row = (ht - splitterIntersection1) / 15;
		int col = (ht - splitterIntersection1) % 15;

		GetHitRect(row + vSplitterBar1, m_rectTracker);
		int yTrackOffset = m_ptTrackOffset.y;
		m_bTracking2 = TRUE;
		GetHitRect(col + hSplitterBar1, m_rectTracker2);
		m_ptTrackOffset.y = yTrackOffset;
	}
	else if (ht == bothSplitterBox)
	{
		// hit on splitter boxes (for keyboard)
		GetHitRect(vSplitterBox, m_rectTracker);
		int yTrackOffset = m_ptTrackOffset.y;
		m_bTracking2 = TRUE;
		GetHitRect(hSplitterBox, m_rectTracker2);
		m_ptTrackOffset.y = yTrackOffset;

		// center it
		m_rectTracker.OffsetRect(0, m_rectLimit.Height()/2);
		m_rectTracker2.OffsetRect(m_rectLimit.Width()/2, 0);
	}
	else
	{
		// only hit one bar
		GetHitRect(ht, m_rectTracker);
	}

	// allow active view to preserve focus before taking it away
	CView* pView = (CView*)GetActivePane();
	if (pView != NULL && pView->IsKindOf(RUNTIME_CLASS(CView)))
	{
		ASSERT_VALID(pView);
		CFrameWnd* pFrameWnd = GetParentFrame();
		ASSERT_VALID(pFrameWnd);
		((_cview*)pView)->OnActivateFrame(WA_INACTIVE, pFrameWnd);
	}

	// steal focus and capture
	SetCapture();
	SetFocus();

	// make sure no updates are pending
	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_UPDATENOW);

	// set tracking state and appropriate cursor
	m_bTracking = TRUE;
	OnInvertTracker(m_rectTracker);
	if (m_bTracking2)
		OnInvertTracker(m_rectTracker2);
	m_htTrack = ht;
	SetSplitCursor(ht);
}

//@doc CGXDSplitWnd
//@mfunc A helper function to track the row size so that we can properly delete the row if the row height is
//to small.
//@rdesc void
//@parm int y The height of the given row.
//@parm  int row The zero-based row index of the row being tracked.
void CGXDSplitWnd::TrackRowSize(int y, int row)
{
	ASSERT_VALID(this);
	ASSERT(m_nRows > 1);

	CPoint pt(0, y);
	ClientToScreen(&pt);
	GetPane(row, 0)->ScreenToClient(&pt);
	m_pRowInfo[row].nIdealSize = pt.y;      // new size
	if (pt.y < m_pRowInfo[row].nMinSize)
	{
		// resized too small
		m_pRowInfo[row].nIdealSize = 0; // make it go away
		if (GetStyle() & SPLS_DYNAMIC_SPLIT)
			DeleteRow(row);
	}
	else if (m_pRowInfo[row].nCurSize + m_pRowInfo[row+1].nCurSize
			< pt.y + m_pRowInfo[row+1].nMinSize)
	{
		// not enough room for other pane
		if (GetStyle() & SPLS_DYNAMIC_SPLIT)
			DeleteRow(row + 1);
	}
}

//@doc CGXDSplitWnd
//@mfunc A helper function to track the column size so that we can properly delete the column if the
//column width is too small.
//@rdesc void
//@parm int x The width of the given column.
//@parm  int col The zero-based column index of the column being tracked.
void CGXDSplitWnd::TrackColumnSize(int x, int col)
{
	ASSERT_VALID(this);
	ASSERT(m_nCols > 1);

	CPoint pt(x, 0);
	ClientToScreen(&pt);
	GetPane(0, col)->ScreenToClient(&pt);
	m_pColInfo[col].nIdealSize = pt.x;      // new size
	if (pt.x < m_pColInfo[col].nMinSize)
	{
		// resized too small
		m_pColInfo[col].nIdealSize = 0; // make it go away
		if (GetStyle() & SPLS_DYNAMIC_SPLIT)
			DeleteColumn(col);
	}
	else if (m_pColInfo[col].nCurSize + m_pColInfo[col+1].nCurSize
			< pt.x + m_pColInfo[col+1].nMinSize)
	{
		// not enough room for other pane
		if (GetStyle() & SPLS_DYNAMIC_SPLIT)
			DeleteColumn(col + 1);
	}
}

//@doc CGXDSplitWnd
//@mfunc Call this function to stop mouse tracking and complete the proper splitter action.
//@rdesc void
//@parm BOOL bAccept If TRUE, the splitter action will be accepted, otherwise no splitter action will occur.
void CGXDSplitWnd::StopTracking(BOOL bAccept)
{
	ASSERT_VALID(this);

	if (!m_bTracking)
		return;

	ReleaseCapture();

	// erase tracker rectangle
	OnInvertTracker(m_rectTracker);
	if (m_bTracking2)
		OnInvertTracker(m_rectTracker2);
	m_bTracking = m_bTracking2 = FALSE;

	// save old active view
	CWnd* pOldActiveView = GetActivePane();

	// m_rectTracker is set to the new splitter position (without border)
	// (so, adjust relative to where the border will be)
	m_rectTracker.OffsetRect(-CX_BORDER , -CY_BORDER);
	m_rectTracker2.OffsetRect(-CX_BORDER, -CY_BORDER);

	if (bAccept)
	{
		if (m_htTrack == vSplitterBox)
		{
			SplitRow(m_rectTracker.top);
		}
		else if (m_htTrack >= vSplitterBar1 && m_htTrack <= vSplitterBar15)
		{
			// set row height
			TrackRowSize(m_rectTracker.top, m_htTrack - vSplitterBar1);
			RecalcLayout();
		}
		else if (m_htTrack == hSplitterBox)
		{
			SplitColumn(m_rectTracker.left);
		}
		else if (m_htTrack >= hSplitterBar1 && m_htTrack <= hSplitterBar15)
		{
			// set column width
			TrackColumnSize(m_rectTracker.left, m_htTrack - hSplitterBar1);
			RecalcLayout();
		}
		else if (m_htTrack >= splitterIntersection1 &&
			m_htTrack <= splitterIntersection225)
		{
			// set row height and column width
			int row = (m_htTrack - splitterIntersection1) / 15;
			int col = (m_htTrack - splitterIntersection1) % 15;

			TrackRowSize(m_rectTracker.top, row);
			TrackColumnSize(m_rectTracker2.left, col);
			RecalcLayout();
		}
		else if (m_htTrack == bothSplitterBox)
		{
			// rectTracker is vSplitter (splits rows)
			// rectTracker2 is hSplitter (splits cols)
			SplitRow(m_rectTracker.top);
			SplitColumn(m_rectTracker2.left);
		}
	}

	if (pOldActiveView == GetActivePane())
	{
		if (pOldActiveView != NULL)
		{
			SetActivePane(-1, -1, pOldActiveView); // re-activate
			pOldActiveView->SetFocus(); // make sure focus is restored
		}
	}

}

//@doc CGXDSplitWnd
//@mfunc A helper function to find the hitting rectange according to the given hit testing result.
//@rdesc void
//@parm int ht The hit testing result. Refer to HitTest method for possible values.
//@parm  CRect& rectHit Reference to the rectange to accept the found rectangle.
void CGXDSplitWnd::GetHitRect(int ht, CRect& rectHit)
{
	ASSERT_VALID(this);

	CRect rectClient;
	GetClientRect(&rectClient);
	rectClient.InflateRect(-m_cxBorder, -m_cyBorder);
	int cx = rectClient.Width();
	int cy = rectClient.Height();
	int x = rectClient.top;
	int y = rectClient.left;

	// hit rectangle does not include border
	// m_rectLimit will be limited to valid tracking rect
	// m_ptTrackOffset will be set to appropriate tracking offset
	m_ptTrackOffset.x = 0;
	m_ptTrackOffset.y = 0;

	if (ht == vSplitterBox)
	{
		cy = m_cySplitter - (2*m_cyBorder - bWin4);
		m_ptTrackOffset.y = -(cy / 2);
		ASSERT(m_pRowInfo[0].nCurSize > 0);
		m_rectLimit.bottom -= cy;
	}
	else if (ht == hSplitterBox)
	{
		cx = m_cxSplitter - (2*m_cxBorder - bWin4);
		m_ptTrackOffset.x = -(cx / 2);
		ASSERT(m_pColInfo[0].nCurSize > 0);
		m_rectLimit.right -= cx;
	}
	else if (ht >= vSplitterBar1 && ht <= vSplitterBar15)
	{
		cy = m_cySplitter - (2*m_cyBorder - bWin4);
		m_ptTrackOffset.y = -(cy / 2);
		int row;
		for (row = 0; row < ht - vSplitterBar1; row++)
			y += m_pRowInfo[row].nCurSize + m_cySplitterGap;
		m_rectLimit.top = y;
		y += m_pRowInfo[row].nCurSize + m_cyBorderShare + bWin4;
		m_rectLimit.bottom -= cy;
	}
	else if (ht >= hSplitterBar1 && ht <= hSplitterBar15)
	{
		cx = m_cxSplitter - (2*m_cxBorder - bWin4);
		m_ptTrackOffset.x = -(cx / 2);
		int col;
		for (col = 0; col < ht - hSplitterBar1; col++)
			x += m_pColInfo[col].nCurSize + m_cxSplitterGap;
		m_rectLimit.left = x;
		x += m_pColInfo[col].nCurSize + m_cxBorderShare + bWin4;
		m_rectLimit.right -= cx;
	}
	else
	{
		TRACE1("Error: GetHitRect(%d): Not Found!\n", ht);
		ASSERT(FALSE);
	}

	rectHit.right = (rectHit.left = x) + cx;
	rectHit.bottom = (rectHit.top = y) + cy;
}

//@doc CGXDSplitWnd
//@mfunc Helper function to find the hit testing result.
//@rdesc int The testing result. The possible value are: 	noHit, vSplitterBox, hSplitterBox,
//bothSplitterBox, vSplitterBar1 - vSplitterBar15, hSplitterBar1 - hSplitterBar15,
//splitterIntersection1 - splitterIntersection225.
//@parm CPoint pt The point to test against.
int CGXDSplitWnd::HitTest(CPoint pt) const
{
	ASSERT_VALID(this);

	CRect rectClient;
	GetClientRect(&rectClient);
	rectClient.InflateRect(-m_cxBorder, -m_cyBorder);

	CRect rectInside;
	GetInsideRect(rectInside);

	if (m_bHasVScroll && m_nRows < m_nMaxRows &&
		CRect(rectInside.right, rectClient.top, rectClient.right,
		rectClient.top + m_cySplitter - bWin4).PtInRect(pt))
	{
		return vSplitterBox;
	}

	if (m_bHasHScroll && m_nCols < m_nMaxCols &&
		CRect(rectClient.left, rectInside.bottom,
		 rectClient.left + m_cxSplitter - bWin4,
		 rectClient.bottom).PtInRect(pt))
	{
		return hSplitterBox;
	}

	// for hit detect, include the border of splitters
	CRect rect;
	rect = rectClient;


	if( m_pOwnerWnd && m_pOwnerWnd->GetDlgItem(AFX_IDW_HSCROLL_FIRST))
		if( m_pOwnerWnd->GetDlgItem(AFX_IDW_HSCROLL_FIRST)->IsWindowVisible() )
			rect.bottom += ::GetSystemMetrics(SM_CXHSCROLL);
	int col;
	for (col = 0; col < m_nCols - 1; col++)
	{
		rect.left += m_pColInfo[col].nCurSize;
		rect.right = rect.left + m_cxSplitterGap;
		if (rect.PtInRect(pt))
			break;
		rect.left = rect.right;
	}

	rect = rectClient;
	int row;
	for (row = 0; row < m_nRows - 1; row++)
	{
		rect.top += m_pRowInfo[row].nCurSize;
		rect.bottom = rect.top + m_cySplitterGap;
		if (rect.PtInRect(pt))
			break;
		rect.top = rect.bottom;
	}

	// row and col set for hit splitter (if not hit will be past end)
	if (col != m_nCols - 1)
	{
		if (row != m_nRows - 1)
			return splitterIntersection1 + row * 15 + col;
		return hSplitterBar1 + col;
	}

	if (row != m_nRows - 1)
		return vSplitterBar1 + row;

	return noHit;
}

/////////////////////////////////////////////////////////////////////////////
// CGXDSplitWnd tracking visuals

//@doc CGXDSplitWnd
//@mfunc Helper function to draw the ghost rectangle during mouse tracking.
//@rdesc void
//@parm const CRect& rect The rectangle to be drawn.
void CGXDSplitWnd::OnInvertTracker(const CRect& rect)
{
	ASSERT_VALID(this);
	ASSERT(!rect.IsRectEmpty());
	ASSERT((GetStyle() & WS_CLIPCHILDREN) == 0);

	// pat-blt without clip children on
	CDC* pDC = GetDC();
	// invert the brush pattern (looks just like frame window sizing)
	CBrush* pBrush = CDC::GetHalftoneBrush();
	HBRUSH hOldBrush = NULL;
	if (pBrush != NULL)
		hOldBrush = (HBRUSH)SelectObject(pDC->GetSafeHdc(), pBrush->m_hObject);
	pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATINVERT);
	if (hOldBrush != NULL)
		SelectObject(pDC->GetSafeHdc(), hOldBrush);
	ReleaseDC(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CGXDSplitWnd commands

// Keyboard interface
//@doc CGXDSplitWnd
//@mfunc Helper function for splitting the window using keyboard.
//@rdesc BOOL Return TRUE if the splitting can be done, otherwise return FALSE.
BOOL CGXDSplitWnd::DoKeyboardSplit()
{
	ASSERT_VALID(this);

	int ht;
	if (m_nRows > 1 && m_nCols > 1)
		ht = splitterIntersection1; // split existing row+col
	else if (m_nRows > 1)
		ht = vSplitterBar1;         // split existing row
	else if (m_nCols > 1)
		ht = hSplitterBar1;         // split existing col
	else if (m_nMaxRows > 1 && m_nMaxCols > 1)
		ht = bothSplitterBox;       // we can split both
	else if (m_nMaxRows > 1)
		ht = vSplitterBox;          // we can split rows
	else if (m_nMaxCols > 1)
		ht = hSplitterBox;          // we can split columns
	else
		return FALSE;               // can't split

	// start tracking
	StartTracking(ht);

#ifndef _MAC
	CRect rect;
	rect.left = m_rectTracker.Width() / 2;
	rect.top = m_rectTracker.Height() / 2;
	if (m_ptTrackOffset.y != 0)
		rect.top = m_rectTracker.top;
	if (m_ptTrackOffset.x != 0)
		rect.left = m_bTracking2 ? m_rectTracker2.left :m_rectTracker.left;
	rect.OffsetRect(-m_ptTrackOffset.x, -m_ptTrackOffset.y);
	ClientToScreen(&rect);
	SetCursorPos(rect.left, rect.top);
#endif

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// Main drawing and layout

//@doc CGXDSplitWnd
//@mfunc WM_DISPLAYCHANGLE message handler. If this window is visible and not minimized, it
//calls RecalcLayout method to reposition the panes and scroll bars.
//@rdesc void
void CGXDSplitWnd::OnDisplayChange()
{
	if (!IsIconic() && IsWindowVisible())
		RecalcLayout();
}

//@doc CGXDSplitWnd
//@mfunc WM_SIZE message handler. It calls RecalcLayout to reposition the panes and scroll bars if
//the window is not minimized. Please refer to CWnd::OnSize in MFC for details of the argument.
//@rdesc void
//@parm UINT nType
//@parm  int cx
//@parm  int cy
void CGXDSplitWnd::OnSize(UINT nType, int cx, int cy)
{
	if (nType != SIZE_MINIMIZED && cx > 0 && cy > 0)
		RecalcLayout();
	CWnd::OnSize(nType, cx, cy);
}

// Generic routine:
//  for X direction: pInfo = m_pColInfo, nMax = m_nMaxCols, nSize = cx
//  for Y direction: pInfo = m_pRowInfo, nMax = m_nMaxRows, nSize = cy
static void AFXAPI LayoutRowCol(CGXDSplitWnd::CRowColInfo* pInfoArray,
	int nMax, int nSize, int nSizeSplitter)
{
	ASSERT(pInfoArray != NULL);
	ASSERT(nMax > 0);
	ASSERT(nSizeSplitter > 0);

	CGXDSplitWnd::CRowColInfo* pInfo;
	int i;

	if (nSize < 0)
		nSize = 0;  // if really too small, layout as zero size

	// start with ideal sizes
	for (i = 0, pInfo = pInfoArray; i < nMax-1; i++, pInfo++)
	{
		if (pInfo->nIdealSize < pInfo->nMinSize)
			pInfo->nIdealSize = 0;      // too small to see
		pInfo->nCurSize = pInfo->nIdealSize;
	}
	pInfo->nCurSize = INT_MAX;  // last row/column takes the rest

	for (i = 0, pInfo = pInfoArray; i < nMax; i++, pInfo++)
	{
		ASSERT(nSize >= 0);
		if (nSize == 0)
		{
			// no more room (set pane to be invisible)
			pInfo->nCurSize = 0;
			continue;       // don't worry about splitters
		}
		else if (nSize < pInfo->nMinSize && i != 0)
		{
			// additional panes below the recommended minimum size
			//   aren't shown and the size goes to the previous pane
			pInfo->nCurSize = 0;

			// previous pane already has room for splitter + border
			//   add remaining size and remove the extra border
			ASSERT(afxData.cxBorder2 == afxData.cyBorder2);
			(pInfo-1)->nCurSize += nSize + afxData.cxBorder2;
			nSize = 0;
		}
		else
		{
			// otherwise we can add the second pane
			ASSERT(nSize > 0);
			if (pInfo->nCurSize == 0)
			{
				// too small to see
				if (i != 0)
					pInfo->nCurSize = 0;
			}
			else if (nSize < pInfo->nCurSize)
			{
				// this row/col won't fit completely - make as small as possible
				pInfo->nCurSize = nSize;
				nSize = 0;
			}
			else
			{
				// can fit everything
				nSize -= pInfo->nCurSize;
			}
		}

		// see if we should add a splitter
		ASSERT(nSize >= 0);
		if (i != nMax - 1)
		{
			// should have a splitter
			if (nSize > nSizeSplitter)
			{
				nSize -= nSizeSplitter; // leave room for splitter + border
				ASSERT(nSize > 0);
			}
			else
			{
				// not enough room - add left over less splitter size
				ASSERT(afxData.cxBorder2 == afxData.cyBorder2);
				pInfo->nCurSize += nSize;
				if (pInfo->nCurSize > (nSizeSplitter - afxData.cxBorder2))
					pInfo->nCurSize -= (nSizeSplitter - afxData.cyBorder2);
				nSize = 0;
			}
		}
	}
	ASSERT(nSize == 0); // all space should be allocated
}

// repositions client area of specified window
// assumes everything has WS_BORDER or is inset like it does
//  (includes scroll bars)
static void AFXAPI DeferClientPos(AFX_SIZEPARENTPARAMS* lpLayout,
	CWnd* pWnd, int x, int y, int cx, int cy, BOOL bScrollBar)
{
	ASSERT(pWnd != NULL);
	ASSERT(pWnd->GetSafeHwnd()!= NULL);

	if (bScrollBar)
	{
		// if there is enough room, draw scroll bar without border
		// if there is not enough room, set the WS_BORDER bit so that
		//   we will at least get a proper border drawn
		BOOL bNeedBorder = (cx <= CX_BORDER || cy <= CY_BORDER);
		pWnd->ModifyStyle(bNeedBorder ? 0 : WS_BORDER,
			bNeedBorder ? WS_BORDER : 0);
	}
	CRect rect(x, y, x+cx, y+cy);
	//CRect rect(x, y, x+CX_BORDER, y+CY_BORDER);

	// adjust for border size (even if zero client size)
	// [VC7] Localized bWin4, bNotWin4, since it is not avilable in
	// afxData.

	DWORD dwVersion = ::GetVersion();
	BOOL bWin4 = (BYTE)dwVersion >= 4;
	if (!bWin4)
	{
		if (bScrollBar)
			rect.InflateRect(CX_BORDER, CY_BORDER);
		else
			pWnd->CalcWindowRect(&rect);
	}

	// adjust for 3d border (splitter windows have implied border)
	if ((pWnd->GetExStyle() & WS_EX_CLIENTEDGE) ||
		  pWnd->IsKindOf(RUNTIME_CLASS(CGXDSplitWnd)))
		rect.InflateRect(afxData.cxBorder2, afxData.cyBorder2);

	// first check if the new rectangle is the same as the current
	CRect rectOld;
	pWnd->GetWindowRect(rectOld);
	pWnd->GetParent()->ScreenToClient(&rectOld);
	if (rect != rectOld)
		AfxRepositionWindow(lpLayout, pWnd->GetSafeHwnd(), rect);
}

//@doc CGXDSplitWnd
//@mfunc This is a helper function to obtain the sizable parent. It is called RecalcLayout method.
//@rdesc CWnd* The sizable parent window or NULL if none was found.
CWnd* CGXDSplitWnd::GetSizingParent()
{
	ASSERT_VALID(this);

	if (!bWin4)
		return NULL;

	// size box is in lower right corner of this window
	CRect rectClient;
	GetClientRect(rectClient);

	// find sizeable parent window
	CWnd* pParent = this;
	if (!(pParent->GetStyle() & WS_THICKFRAME))
		pParent = GetParent();

	// only allow if not maximized and has thick frame
	ASSERT_VALID(pParent);
	if ((pParent->GetStyle() & (WS_THICKFRAME|WS_MAXIMIZE)) == WS_THICKFRAME)
	{
		// convert client area of frame window relative to splitter
		CRect rect;
		pParent->GetClientRect(rect);
		pParent->ClientToScreen(rect);
		ScreenToClient(rect);

		// must match exactly to get the size box
		if (rectClient.BottomRight() == rect.BottomRight())
			return pParent;
	}

	return NULL;    // no sizeable parent found
}

//@doc CGXDSplitWnd
//@mfunc This function is responsible to reposition the panes and scroll bars in the
//splitter window according to the splitter information.
//@rdesc void
void CGXDSplitWnd::RecalcLayout()
{
	ASSERT_VALID(this);
	ASSERT(m_nRows > 0 && m_nCols > 0); // must have at least one pane

	CRect rectClient;
	GetClientRect(rectClient);
	rectClient.InflateRect(-m_cxBorder, -m_cyBorder);

	CRect rectInside;
	GetInsideRect(rectInside);

	rectInside.bottom += CY_BORDER + 1;

	// layout columns (restrict to possible sizes)
	LayoutRowCol(m_pColInfo, m_nCols, rectInside.Width(), m_cxSplitterGap);
	LayoutRowCol(m_pRowInfo, m_nRows, rectInside.Height(), m_cySplitterGap);

	// adjust the panes (and optionally scroll bars)

	// give the hint for the maximum number of HWNDs
	AFX_SIZEPARENTPARAMS layout;
	layout.hDWP = ::BeginDeferWindowPos((m_nCols + 1) * (m_nRows + 1) + 1);

	// size of scrollbars
	int cx = (rectClient.right - rectInside.right) - bNotWin4;
	int cy = (rectClient.bottom - rectInside.bottom) - bNotWin4;

	// reposition size box
	if (m_bHasHScroll && m_bHasVScroll)
	{
		CWnd* pScrollBar = GetDlgItem(AFX_IDW_SIZE_BOX);
		ASSERT(pScrollBar != NULL);

		// fix style if necessary
		BOOL bSizingParent = (GetSizingParent() != NULL);
		// modifyStyle returns TRUE if style changes
		if (pScrollBar->ModifyStyle(SBS_SIZEGRIP|SBS_SIZEBOX,
				bSizingParent ? SBS_SIZEGRIP : SBS_SIZEBOX))
			pScrollBar->Invalidate();

		//pScrollBar->EnableWindow(TRUE);
		pScrollBar->EnableWindow(bSizingParent);

		// reposition the size box
		DeferClientPos(&layout, pScrollBar,
			rectInside.right + bNotWin4,
			rectInside.bottom + bNotWin4, cx, cy, TRUE);
	}

	// reposition scroll bars
	if (FALSE/*m_bHasHScroll*/)
	{
		for (int col = 0; col < m_nCols; col++)
		{
			CWnd* pScrollBar = m_pOwnerWnd->GetDlgItem(AFX_IDW_HSCROLL_FIRST + col);
			ASSERT(pScrollBar != NULL);
			CRect rect;
			m_pOwnerWnd->GetClientRect(rect);
			pScrollBar->MoveWindow(CRect(rect.bottom-100,rect.right-300,100,100));
			pScrollBar->ShowWindow(SW_SHOW);
		}
		/*
		int cxSplitterBox = m_cxSplitter + afxData.bNotWin4;// split box bigger
		int x = rectClient.left;
		int y = rectInside.bottom + afxData.bNotWin4;
		for (int col = 0; col < m_nCols; col++)
		{
			CWnd* pScrollBar = m_pOwnerWnd->GetDlgItem(AFX_IDW_HSCROLL_FIRST + col);
			ASSERT(pScrollBar != NULL);
			int cx = m_pColInfo[col].nCurSize;
			if (col == 0 && m_nCols < m_nMaxCols)
				x += cxSplitterBox, cx -= cxSplitterBox;
			DeferClientPos(&layout, pScrollBar, x, y, cx, cy, TRUE);
			x += cx + m_cxSplitterGap;
		}*/
	}

	if (m_bHasVScroll)
	{
		int cySplitterBox = m_cySplitter + bNotWin4;// split box bigger
		int x = rectInside.right + bNotWin4;
		int y = rectClient.top;
		for (int row = 0; row < m_nRows; row++)
		{
			CWnd* pScrollBar = GetDlgItem(AFX_IDW_VSCROLL_FIRST + row);
			ASSERT(pScrollBar != NULL);
			int cy = m_pRowInfo[row].nCurSize;
			if (row == 0 && m_nRows < m_nMaxRows)
				y += cySplitterBox, cy -= cySplitterBox;
			DeferClientPos(&layout, pScrollBar, x, y, cx, cy, TRUE);
			y += cy + m_cySplitterGap;
		}
	}

	//BLOCK: Reposition all the panes
	{
		int x = rectClient.left;
		for (int col = 0; col < m_nCols; col++)
		{
			int cx = m_pColInfo[col].nCurSize;
			int y = rectClient.top;
			for (int row = 0; row < m_nRows; row++)
			{
				int cy = m_pRowInfo[row].nCurSize;
				CWnd* pWnd = GetPane(row, col);
				DeferClientPos(&layout, pWnd, x, y, cx, cy, FALSE);
				y += cy + m_cySplitterGap;
			}
			x += cx + m_cxSplitterGap;
		}
	}

	// move and resize all the windows at once!
	if (layout.hDWP == NULL || !::EndDeferWindowPos(layout.hDWP))
		TRACE0("Warning: DeferWindowPos failed - low system resources.\n");

	// invalidate all the splitter bars (with NULL pDC)
	DrawAllSplitBars(NULL, rectInside.right, rectInside.bottom);
}

//@doc CGXDSplitWnd
//@mfunc This function draws the splitter bars for the splitter window.
//It is called by OnPaint and RecalcLayout methods.
//@rdesc void
//@parm CDC* pDC The device context to draw on.
//@parm  int cxInside The width of the inside area of the splitter window.
//@parm  int cyInside The height of the inside area of the splitter window.
void CGXDSplitWnd::DrawAllSplitBars(CDC* pDC, int cxInside, int cyInside)
{
	ASSERT_VALID(this);

	// draw column split bars
	CRect rect;
	GetClientRect(rect);
	rect.left += m_cxBorder;
	int col;
	for (col = 0; col < m_nCols - 1; col++)
	{
		rect.left += m_pColInfo[col].nCurSize + m_cxBorderShare;
		rect.right = rect.left + m_cxSplitter;
		if (rect.left > cxInside)
			break;      // stop if not fully visible
		OnDrawSplitter(pDC, splitBar, rect);
		rect.left = rect.right + m_cxBorderShare;
	}

	// draw row split bars
	GetClientRect(rect);
	rect.top += m_cyBorder;
	for (int row = 0; row < m_nRows - 1; row++)
	{
		rect.top += m_pRowInfo[row].nCurSize + m_cyBorderShare;
		rect.bottom = rect.top + m_cySplitter;
		if (rect.top > cyInside)
			break;      // stop if not fully visible
		OnDrawSplitter(pDC, splitBar, rect);
		rect.top = rect.bottom + m_cyBorderShare;
	}

	// draw pane borders
	if (bWin4)
	{
		GetClientRect(rect);
		int x = rect.left;
		for (col = 0; col < m_nCols; col++)
		{
			int cx = m_pColInfo[col].nCurSize + 2*m_cxBorder;
			if (col == m_nCols-1 && m_bHasVScroll)
				cx += afxData.cxVScroll - CX_BORDER;
			int y = rect.top;
			for (int row = 0; row < m_nRows; row++)
			{
				int cy = m_pRowInfo[row].nCurSize + 2*m_cyBorder;
				if (row == m_nRows-1 && m_bHasHScroll)
					cy += afxData.cyHScroll - CX_BORDER;
				OnDrawSplitter(pDC, splitBorder, CRect(x, y, x+cx, y+cy));
				y += cy + m_cySplitterGap - 2*m_cyBorder;
			}
			x += cx + m_cxSplitterGap - 2*m_cxBorder;
		}
	}

}

//@doc CGXDSplitWnd
//@mfunc WM_PAINT message handler. It draws the splitter bar inside the splitter window ans splitter box
//at the end of the scroll bar.
//@rdesc void
void CGXDSplitWnd::OnPaint()
{
	ASSERT_VALID(this);
	CPaintDC dc(this);

	CRect rectClient;
	GetClientRect(&rectClient);
	rectClient.InflateRect(-m_cxBorder, -m_cyBorder);

	CRect rectInside;
	GetInsideRect(rectInside);

	// draw the splitter boxes
	if (m_bHasVScroll && m_nRows < m_nMaxRows)
	{
		OnDrawSplitter(&dc, splitBox,
			CRect(rectInside.right + bNotWin4, rectClient.top,
				rectClient.right, rectClient.top + m_cySplitter));
	}

	if (m_bHasHScroll && m_nCols < m_nMaxCols)
	{
		OnDrawSplitter(&dc, splitBox,
			CRect(rectClient.left, rectInside.bottom + bNotWin4,
				rectClient.left + m_cxSplitter, rectClient.bottom));
	}

	// extend split bars to window border (past margins)
	DrawAllSplitBars(&dc, rectInside.right, rectInside.bottom);

	if (!bWin4)
	{
		// draw splitter intersections (inside only)
		GetInsideRect(rectInside);
		dc.IntersectClipRect(rectInside);
		CRect rect;
		rect.top = rectInside.top;
		for (int row = 0; row < m_nRows - 1; row++)
		{
			rect.top += m_pRowInfo[row].nCurSize + m_cyBorderShare;
			rect.bottom = rect.top + m_cySplitter;
			rect.left = rectInside.left;
			for (int col = 0; col < m_nCols - 1; col++)
			{
				rect.left += m_pColInfo[col].nCurSize + m_cxBorderShare;
				rect.right = rect.left + m_cxSplitter;
				OnDrawSplitter(&dc, splitIntersection, rect);
				rect.left = rect.right + m_cxBorderShare;
			}
			rect.top = rect.bottom + m_cxBorderShare;
		}
	}
}

//@doc CGXDSplitWnd
//@mfunc WM_SETCURSOR message handler, please refer to CWnd::SetCursor in MFC for details.
//@rdesc BOOL
//@parm CWnd* pWnd
//@parm  UINT nHitTest
//@parm  UINT message
BOOL CGXDSplitWnd::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	if (nHitTest == HTCLIENT && pWnd == this && !m_bTracking)
		return TRUE;    // we will handle it in the mouse move

	return CWnd::OnSetCursor(pWnd, nHitTest, message);
}

//@doc CGXDSplitWnd
//@mfunc Call this function to set proper cursor for different hit testing result.
//@rdesc void
//@parm int ht Hit testing result returned from HitTest method.
void CGXDSplitWnd::SetSplitCursor(int ht)
{
	// cache of last needed cursor
	static HCURSOR hcurLast = NULL;
	static HCURSOR hcurDestroy = NULL;
	static UINT idcPrimaryLast = 0; // store the primary IDC


	UINT idcPrimary;        // app supplied cursor
	LPCTSTR idcSecondary;    // system supplied cursor (MAKEINTRESOURCE)

	AfxLockGlobals(CRIT_SPLITTERWND);
	if (ht == vSplitterBox ||
		ht >= vSplitterBar1 && ht <= vSplitterBar15)
	{
		idcPrimary = AFX_IDC_VSPLITBAR;
		idcSecondary = IDC_SIZENS;
	}
	else if (ht == hSplitterBox ||
		ht >= hSplitterBar1 && ht <= hSplitterBar15)
	{
		idcPrimary = AFX_IDC_HSPLITBAR;
		idcSecondary = IDC_SIZEWE;
	}
	else if (ht == bothSplitterBox ||
		(ht >= splitterIntersection1 && ht <= splitterIntersection225))
	{
		idcPrimary = AFX_IDC_SMALLARROWS;
		idcSecondary = IDC_SIZEALL;
	}
	else
	{
		SetCursor(afxData.hcurArrow);
		idcPrimary = 0;     // don't use it
		idcSecondary = 0;   // don't use it
	}

	if (idcPrimary != 0)
	{
		HCURSOR hcurToDestroy = NULL;
		if (idcPrimary != idcPrimaryLast)
		{
			HINSTANCE hInst = AfxFindResourceHandle(
				MAKEINTRESOURCE(idcPrimary), RT_GROUP_CURSOR);

			// load in another cursor
			hcurToDestroy = hcurDestroy;

			// Note: If this LoadCursor call fails, it is likely that
			//  _AFX_NO_SPLITTER_RESOURCES is defined in your .RC file.
			// To correct the situation, remove the following line from your
			//  resource script:
			//      #define _AFX_NO_SPLITTER_RESOURCES
			// This should be done using the Resource.Set Includes... command.

			if ((hcurDestroy = hcurLast =
			   ::LoadCursor(hInst, MAKEINTRESOURCE(idcPrimary))) == NULL)
			{
				// will not look as good
				TRACE0("Warning: Could not find splitter cursor - using system provided alternative.\n");

				ASSERT(hcurDestroy == NULL);    // will not get destroyed
				hcurLast = ::LoadCursor(NULL, idcSecondary);
				ASSERT(hcurLast != NULL);
			}
			idcPrimaryLast = idcPrimary;
		}
		ASSERT(hcurLast != NULL);
		::SetCursor(hcurLast);
		ASSERT(hcurLast != hcurToDestroy);
		if (hcurToDestroy != NULL)
			::DestroyCursor(hcurToDestroy); // destroy after being set
	}
	AfxUnlockGlobals(CRIT_SPLITTERWND);
}

//@doc CGXDSplitWnd
//@mfunc WM_MOUSEMOVE message handler. It stops tracking if this window doesn't has mouse capture, otherwise
//if this window is in tracking mode, it redraw the tracking rectangle of the splitter bar or box.
//@rdesc void
//@parm UINT /*nFlags*/
//@parm  CPoint pt
void CGXDSplitWnd::OnMouseMove(UINT /*nFlags*/, CPoint pt)
{
	if (GetCapture() != this)
		StopTracking(FALSE);

	if (m_bTracking)
	{
		// move tracker to current cursor position

		pt.Offset(m_ptTrackOffset); // pt is the upper right of hit detect
		// limit the point to the valid split range
		if (pt.y < m_rectLimit.top)
			pt.y = m_rectLimit.top;
		else if (pt.y > m_rectLimit.bottom)
			pt.y = m_rectLimit.bottom;
		if (pt.x < m_rectLimit.left)
			pt.x = m_rectLimit.left;
		else if (pt.x > m_rectLimit.right)
			pt.x = m_rectLimit.right;

		if (m_htTrack == vSplitterBox ||
			m_htTrack >= vSplitterBar1 && m_htTrack <= vSplitterBar15)
		{
			if (m_rectTracker.top != pt.y)
			{
				OnInvertTracker(m_rectTracker);
				m_rectTracker.OffsetRect(0, pt.y - m_rectTracker.top);
				OnInvertTracker(m_rectTracker);
			}
		}
		else if (m_htTrack == hSplitterBox ||
			m_htTrack >= hSplitterBar1 && m_htTrack <= hSplitterBar15)
		{
			if (m_rectTracker.left != pt.x)
			{
				OnInvertTracker(m_rectTracker);
				m_rectTracker.OffsetRect(pt.x - m_rectTracker.left, 0);
				OnInvertTracker(m_rectTracker);
			}
		}
		else if (m_htTrack == bothSplitterBox ||
		   (m_htTrack >= splitterIntersection1 &&
			m_htTrack <= splitterIntersection225))
		{
			if (m_rectTracker.top != pt.y)
			{
				OnInvertTracker(m_rectTracker);
				m_rectTracker.OffsetRect(0, pt.y - m_rectTracker.top);
				OnInvertTracker(m_rectTracker);
			}
			if (m_rectTracker2.left != pt.x)
			{
				OnInvertTracker(m_rectTracker2);
				m_rectTracker2.OffsetRect(pt.x - m_rectTracker2.left, 0);
				OnInvertTracker(m_rectTracker2);
			}
		}
	}
	else
	{
		// simply hit-test and set appropriate cursor

		int ht = HitTest(pt);
		SetSplitCursor(ht);
	}
}

//@doc CGXDSplitWnd
//@mfunc WM_LBUTTONDOWN message handler, it calls StartTracking if we are not in tracking mode yet.
//@rdesc void
//@parm UINT /*nFlags*/
//@parm  CPoint pt
void CGXDSplitWnd::OnLButtonDown(UINT /*nFlags*/, CPoint pt)
{
	if (m_bTracking)
		return;

	StartTracking(HitTest(pt));
}

//@doc CGXDSplitWnd
//@mfunc WM_LBUTTONDBLCLK message handler, please refer to CWnd::OnLButtonDblClk in MFC for details.
//@rdesc void
//@parm UINT /*nFlags*/
//@parm  CPoint pt
void CGXDSplitWnd::OnLButtonDblClk(UINT /*nFlags*/, CPoint pt)
{
	int ht = HitTest(pt);
	CRect rect;

	StopTracking(FALSE);

	if ((GetStyle() & SPLS_DYNAMIC_SPLIT) == 0)
		return;     // do nothing if layout is static

	if (ht == vSplitterBox)
	{
		// half split
		SplitRow(m_pRowInfo[0].nCurSize / 2);
	}
	else if (ht == hSplitterBox)
	{
		// half split
		SplitColumn(m_pColInfo[0].nCurSize / 2);
	}
	else if (ht >= vSplitterBar1 && ht <= vSplitterBar15)
	{
		int rowDelete = ht - vSplitterBar1;
		// don't delete the active row
		int row;
		if (GetActivePane(&row, NULL) != NULL && rowDelete == row)
			++rowDelete;
		DeleteRow(rowDelete);
	}
	else if (ht >= hSplitterBar1 && ht <= hSplitterBar15)
	{
		int colDelete = ht - hSplitterBar1;
		// don't delete the active column
		int col;
		if (GetActivePane(NULL, &col) != NULL && colDelete == col)
			++colDelete;
		DeleteColumn(colDelete);
	}
	else if (ht >= splitterIntersection1 && ht <= splitterIntersection225)
	{
		int rowDelete = (ht - splitterIntersection1) / 15;
		int colDelete = (ht - splitterIntersection1) % 15;
		int row, col;
		if (GetActivePane(&row, &col) != NULL)
		{
			// don't delete the active row or column
			if (col == colDelete)
				++colDelete;
			if (row == rowDelete)
				++rowDelete;
		}
		DeleteRow(rowDelete);
		DeleteColumn(colDelete);
	}
}

//@doc CGXDSplitWnd
//@mfunc WM_LBUTTONUP message handler, it calls StopTracking with TRUE as argument.
//@rdesc void
//@parm UINT /*nFlags*/
//@parm  CPoint /*pt*/
void CGXDSplitWnd::OnLButtonUp(UINT /*nFlags*/, CPoint /*pt*/)
{
	StopTracking(TRUE);
	if(m_pOwnerWnd)
		((CGXDTabWnd*)m_pOwnerWnd)->RecalcLayout();
}

//@doc CGXDSplitWnd
//@mfunc WM_CANCELMODE message handler, it calls StopTracking with FALSE as argument.
//@rdesc void
void CGXDSplitWnd::OnCancelMode()
{
	StopTracking(FALSE);
}

//@doc CGXDSplitWnd
//@mfunc WM_KEYDOWN message handler, please refer to CWnd::OnKeyDown in MFC for details.
//@rdesc void
//@parm UINT nChar
//@parm  UINT /*nRepCnt*/
//@parm  UINT /*nFlags*/
void CGXDSplitWnd::OnKeyDown(UINT nChar, UINT /*nRepCnt*/, UINT /*nFlags*/)
{
	CPoint pt;
	GetCursorPos(&pt);

	int cz = GetKeyState(VK_CONTROL) < 0 ? 1 : 16;
	int dx = 0;
	int dy = 0;

	switch (nChar)
	{
	case VK_ESCAPE:
		StopTracking(FALSE);
		return;
	case VK_RETURN:
		StopTracking(TRUE);
		return;

#ifndef _MAC
	case VK_LEFT:
		dx = -1;
		break;
	case VK_RIGHT:
		dx = +1;
		break;
	case VK_UP:
		dy = -1;
		break;
	case VK_DOWN:
		dy = +1;
		break;
#endif

	default:
		Default();  // pass other keys through
		return;
	}

	if (m_htTrack == vSplitterBox ||
		m_htTrack >= vSplitterBar1 && m_htTrack <= vSplitterBar15)
	{
		// no movement along X axis
		dx = 0;
	}
	if (m_htTrack == hSplitterBox ||
		m_htTrack >= hSplitterBar1 && m_htTrack <= hSplitterBar15)
	{
		// no movement along Y axis
		dy = 0;
	}

	// adjust to new position
	pt.x += dx * cz;
	pt.y += dy * cz;

	// make sure within valid limits
	ScreenToClient(&pt);
	if (pt.y < m_rectLimit.top)
		pt.y = m_rectLimit.top;
	else if (pt.y > m_rectLimit.bottom)
		pt.y = m_rectLimit.bottom;
	if (pt.x < m_rectLimit.left)
		pt.x = m_rectLimit.left;
	else if (pt.x > m_rectLimit.right)
		pt.x = m_rectLimit.right;
	ClientToScreen(&pt);

#ifndef _MAC
	// cause WM_MOUSEMOVE to filter through
	SetCursorPos(pt.x, pt.y);
#endif
}

//@doc CGXDSplitWnd
//@mfunc WM_SYSCOMMAND message handler, please refer to CWnd::OnSysCommand in MFC for details.
//@rdesc void
//@parm UINT nID
//@parm  LPARAM lParam
void CGXDSplitWnd::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == SC_SIZE)
	{
		CWnd* pParent = GetSizingParent();
		if (pParent != NULL)
		{
			pParent->SendMessage(WM_SYSCOMMAND, (WPARAM)nID, lParam);
			return;
		}
	}
	CWnd::OnSysCommand(nID, lParam);
}

/////////////////////////////////////////////////////////////////////////////
// CGXDSplitWnd command routing

//@doc CGXDSplitWnd
//@mfunc WM_COMMAND message handler, please refer to CWnd::OnCommand in MFC for details.
//@rdesc BOOL
//@parm WPARAM wParam
//@parm  LPARAM lParam
BOOL CGXDSplitWnd::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if (CWnd::OnCommand(wParam, lParam))
		return TRUE;

	// route commands to the splitter to the parent frame window
	return (BOOL)GetParentFrame()->SendMessage(WM_COMMAND, wParam, lParam);
}

//@doc CGXDSplitWnd
//@mfunc WM_NOTIFY message handler, please refer to CWnd::OnNotify in MFC for details.
//@rdesc BOOL
//@parm WPARAM wParam
//@parm  LPARAM lParam
//@parm  LRESULT* pResult
BOOL CGXDSplitWnd::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	if (CWnd::OnNotify(wParam, lParam, pResult))
		return TRUE;

	// route commands to the splitter to the parent frame window
	*pResult = GetParentFrame()->SendMessage(WM_NOTIFY, wParam, lParam);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// Scroll messages

//@doc CGXDSplitWnd
//@mfunc WM_MOUSEWHEEL message handler, please refer to CWnd::OnMouseWheel in MFC for details.
//@rdesc BOOL
//@parm UINT fFlags
//@parm  short zDelta
//@parm  CPoint point
BOOL CGXDSplitWnd::OnMouseWheel(UINT fFlags, short zDelta, CPoint point)
{
	BOOL bRetVal = FALSE;
	int row;
	int col;

	CScrollBar* pBar;
	CWnd* pPane;
	CScrollView* pView;
	int nOldPos;

	for (row = 0; row < m_nRows; row++)
	{
		for (col = 0; col < m_nCols; col++)
		{
			pPane = GetPane(row, col);
			pView = STATIC_DOWNCAST(CScrollView, pPane);
			if (pView != NULL)
			{
				pBar = pView->GetScrollBarCtrl(SB_VERT);
				if (pBar == NULL)
				{
					pBar = pView->GetScrollBarCtrl(SB_HORZ);
					if (pBar == NULL)
						continue;
				}

				nOldPos = pBar->GetScrollPos();
				if (pView->DoMouseWheel(fFlags, zDelta, point))
				{
					bRetVal = TRUE;
				}
				if (col < m_nCols -1)
					pBar->SetScrollPos(nOldPos, FALSE);
			}
		}
	}

	return TRUE;
}

//@doc CGXDSplitWnd
//@mfunc WM_HSCROLL message handler, please refer to CWnd::OnHScroll in MFC for details.
//@rdesc void
//@parm UINT nSBCode
//@parm  UINT nPos
//@parm  CScrollBar* pScrollBar
void CGXDSplitWnd::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	ASSERT(pScrollBar != NULL);
	int col = _AfxGetDlgCtrlID(pScrollBar->GetSafeHwnd()) - AFX_IDW_HSCROLL_FIRST;
	ASSERT(col >= 0 && col < m_nMaxCols);

	ASSERT(m_nRows > 0);
	int nOldPos = pScrollBar->GetScrollPos();
#ifdef _DEBUG
	int nNewPos=0;
#endif
	for (int row = 0; row < m_nRows; row++)
	{
		GetPane(row, col)->SendMessage(WM_HSCROLL,
			MAKELONG(nSBCode, nPos), (LPARAM)pScrollBar->GetSafeHwnd());
#ifdef _DEBUG
		if (row == 0)
			nNewPos = pScrollBar->GetScrollPos();
		if (pScrollBar->GetScrollPos() != nNewPos)
		{
			TRACE0("Warning: scroll panes setting different scroll positions.\n");
			// stick with the last one set
		}
#endif //_DEBUG
		// set the scroll pos to the value it was originally for the next pane
		if (row < m_nRows - 1)
			pScrollBar->SetScrollPos(nOldPos, FALSE);
	}
}

//@doc CGXDSplitWnd
//@mfunc This is WM_VSCROLL message handler. Please refer to CWnd::OnVScroll in MFC for details.
//@rdesc void
//@parm UINT nSBCode
//@parm  UINT nPos
//@parm  CScrollBar* pScrollBar
void CGXDSplitWnd::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	ASSERT(pScrollBar != NULL);
	int row = _AfxGetDlgCtrlID(pScrollBar->GetSafeHwnd()) - AFX_IDW_VSCROLL_FIRST;
	ASSERT(row >= 0 && row < m_nMaxRows);

	ASSERT(m_nCols > 0);
	int nOldPos = pScrollBar->GetScrollPos();
#ifdef _DEBUG
	int nNewPos=0;
#endif
	for (int col = 0; col < m_nCols; col++)
	{
		GetPane(row, col)->SendMessage(WM_VSCROLL,
			MAKELONG(nSBCode, nPos), (LPARAM)pScrollBar->GetSafeHwnd());
#ifdef _DEBUG
		if (col == 0)
			nNewPos = pScrollBar->GetScrollPos();
		if (pScrollBar->GetScrollPos() != nNewPos)
		{
			TRACE0("Warning: scroll panes setting different scroll positions.\n");
			// stick with the last one set
		}
#endif //_DEBUG
		// set the scroll pos to the value it was originally for the next pane
		if (col < m_nCols - 1)
			pScrollBar->SetScrollPos(nOldPos, FALSE);
	}
}

// synchronized scrolling
//@doc CGXDSplitWnd
//@mfunc Call this function to scroll the given view window.
//@rdesc BOOL Return TRUE if the scroll occurs, otherwise return FALSE.
//@parm CView* pViewFrom from which the scrolling message originates.
//@parm  UINT nScrollCode A scroll-bar code that indicates the user's scrolling request. Please refer to
//CSplitterWnd::DoScroll in MFC for more detailed mean of this code.
//@parm  BOOL bDoScroll Determines whether the specified scrolling action occurs.
//If bDoScroll is TRUE (that is, if a child window exists, and if the split windows have a scroll range),
//then the specified scrolling action can take place; if bDoScroll is FALSE (that is, if no child window exists,
//or the split views have no scroll range), then scrolling does not occur.
BOOL CGXDSplitWnd::DoScroll(CView* pViewFrom, UINT nScrollCode, BOOL bDoScroll)
{
	ASSERT_VALID(pViewFrom);

	int rowFrom=0, colFrom=0;
	if (!IsChildPane(pViewFrom, &rowFrom, &colFrom))
		return FALSE;

	BOOL bResult = FALSE;

	// save original positions
	int nOldVert=0;
	CScrollBar* pScrollVert = pViewFrom->GetScrollBarCtrl(SB_VERT);
	if (pScrollVert != NULL)
		nOldVert = pScrollVert->GetScrollPos();
	int nOldHorz=0;
	CScrollBar* pScrollHorz = pViewFrom->GetScrollBarCtrl(SB_HORZ);
	if (pScrollHorz != NULL)
		nOldHorz = pScrollHorz->GetScrollPos();

	// scroll the view from which the message is from
	if (pViewFrom->OnScroll(nScrollCode, 0, bDoScroll))
		bResult = TRUE;

	if (pScrollVert != NULL)
	{
#ifdef _DEBUG
		int nNewVert = pScrollVert->GetScrollPos();
#endif
		// scroll related columns
		for (int col = 0; col < m_nCols; col++)
		{
			if (col == colFrom)
				continue;

			// set the scroll pos to the value it was originally
			pScrollVert->SetScrollPos(nOldVert, FALSE);

			// scroll the pane
			CView* pView = (CView*)GetPane(rowFrom, col);
			ASSERT_KINDOF(CView, pView);
			ASSERT(pView != pViewFrom);
			if (pView->OnScroll(MAKEWORD(-1, HIBYTE(nScrollCode)), 0,
				bDoScroll))
			{
				bResult = TRUE;
			}

#ifdef _DEBUG
			if (pScrollVert->GetScrollPos() != nNewVert)
			{
				TRACE0("Warning: scroll panes setting different scroll positions.\n");
				// stick with the last one set
			}
#endif
		}
	}

	if (pScrollHorz != NULL)
	{
#ifdef _DEBUG
		int nNewHorz = pScrollHorz->GetScrollPos();
#endif
		// scroll related rows
		for (int row = 0; row < m_nRows; row++)
		{
			if (row == rowFrom)
				continue;

			// set the scroll pos to the value it was originally
			pScrollHorz->SetScrollPos(nOldHorz, FALSE);

			// scroll the pane
			CView* pView = (CView*)GetPane(row, colFrom);
			ASSERT_KINDOF(CView, pView);
			ASSERT(pView != pViewFrom);
			if (pView->OnScroll(MAKEWORD(LOBYTE(nScrollCode), -1), 0,
				bDoScroll))
			{
				bResult = TRUE;
			}

#ifdef _DEBUG
			if (pScrollHorz->GetScrollPos() != nNewHorz)
			{
				TRACE0("Warning: scroll panes setting different scroll positions.\n");
				// stick with the last one set
			}
#endif
		}
	}

	return bResult;
}

//@doc CGXDSplitWnd
//@mfunc A scroll helper that scroll the given view window by a given amount in the size argument.
//@rdesc BOOL Return TRUE if successful, otherwise return FALSE.
//@parm CView* pViewFrom from which the scrolling message originates.
//@parm  CSize sizeScroll The amount the window to be scrolled.
//@parm  BOOL bDoScroll Determines whether the specified scrolling action occurs.
//If bDoScroll is TRUE (that is, if a child window exists, and if the split windows have a scroll range),
//then the specified scrolling action can take place; if bDoScroll is FALSE (that is, if no child window exists,
//or the split views have no scroll range), then scrolling does not occur.
BOOL CGXDSplitWnd::DoScrollBy(CView* pViewFrom, CSize sizeScroll, BOOL bDoScroll)
{
	int rowFrom, colFrom;
	if (!IsChildPane(pViewFrom, &rowFrom, &colFrom))
		return FALSE;

	BOOL bResult = FALSE;

	// save original positions
	int nOldVert=0;
	CScrollBar* pScrollVert = pViewFrom->GetScrollBarCtrl(SB_VERT);
	if (pScrollVert != NULL)
		nOldVert = pScrollVert->GetScrollPos();
	int nOldHorz=0;
	CScrollBar* pScrollHorz = pViewFrom->GetScrollBarCtrl(SB_HORZ);
	if (pScrollHorz != NULL)
		nOldHorz = pScrollHorz->GetScrollPos();

	// scroll the view from which the message is from
	if (pViewFrom->OnScrollBy(sizeScroll, bDoScroll))
		bResult = TRUE;

	if (pScrollVert != NULL)
	{
#ifdef _DEBUG
		int nNewVert = pScrollVert->GetScrollPos();
#endif
		// scroll related columns
		for (int col = 0; col < m_nCols; col++)
		{
			if (col == colFrom)
				continue;

			// set the scroll pos to the value it was originally for the next pane
			pScrollVert->SetScrollPos(nOldVert, FALSE);

			// scroll the pane
			CView* pView = (CView*)GetPane(rowFrom, col);
			ASSERT_KINDOF(CView, pView);
			ASSERT(pView != pViewFrom);
			if (pView->OnScrollBy(CSize(0, sizeScroll.cy), bDoScroll))
				bResult = TRUE;

#ifdef _DEBUG
			if (pScrollVert->GetScrollPos() != nNewVert)
			{
				TRACE0("Warning: scroll panes setting different scroll positions.\n");
				// stick with the last one set
			}
#endif
		}
	}

	if (pScrollHorz != NULL)
	{
#ifdef _DEBUG
	int nNewHorz = pScrollHorz->GetScrollPos();
#endif
		// scroll related rows
		for (int row = 0; row < m_nRows; row++)
		{
			if (row == rowFrom)
				continue;

			// set the scroll pos to the value it was originally for the next pane
			pScrollHorz->SetScrollPos(nOldHorz, FALSE);

			// scroll the pane
			CView* pView = (CView*)GetPane(row, colFrom);
			ASSERT_KINDOF(CView, pView);
			ASSERT(pView != pViewFrom);
			if (pView->OnScrollBy(CSize(sizeScroll.cx, 0), bDoScroll))
				bResult = TRUE;

#ifdef _DEBUG
			if (pScrollHorz->GetScrollPos() != nNewHorz)
			{
				TRACE0("Warning: scroll panes setting different scroll positions.\n");
				// stick with the last one set
			}
#endif
		}
	}

	return bResult;
}

/////////////////////////////////////////////////////////////////////////////
// Focus control and control over the current pane/child

//@doc CGXDSplitWnd
//@mfunc Check if we can active the next or previous pane.
//@rdesc BOOL Return TRUE if we can, otherwise return FALSE.
//@parm BOOL If TRUE, it checks if we can active previous pane, otherwise it checks if we can activate next pane.
BOOL CGXDSplitWnd::CanActivateNext(BOOL)
{
	ASSERT_VALID(this);

	if (GetActivePane() == NULL)
	{
		TRACE0("Warning: Can't go to next pane - there is no current pane.\n");
		return FALSE;
	}
	ASSERT(m_nRows != 0);
	ASSERT(m_nCols != 0);
	// if more than 1x1 we can go to the next or prev pane
	return (m_nRows > 1) || (m_nCols > 1);
}

//@doc CGXDSplitWnd
//@mfunc Call this function to move backward or forward the active pane.
//@rdesc void
//@parm BOOL bPrev If FALSE, it moves from left to right and then top to bottom, otherwise it
//moves from right to left and then bottom to top.
void CGXDSplitWnd::ActivateNext(BOOL bPrev)
{
	ASSERT_VALID(this);

	// find the coordinate of the current pane
	int row, col;
	if (GetActivePane(&row, &col) == NULL)
	{
		TRACE0("Warning: Cannot go to next pane - there is no current view.\n");
		return;
	}
	ASSERT(row >= 0 && row < m_nRows);
	ASSERT(col >= 0 && col < m_nCols);

	// determine next pane
	if (bPrev)
	{
		// prev
		if (--col < 0)
		{
			col = m_nCols - 1;
			if (--row < 0)
				row = m_nRows - 1;
		}
	}
	else
	{
		// next
		if (++col >= m_nCols)
		{
			col = 0;
			if (++row >= m_nRows)
				row = 0;
		}
	}

	// set newly active pane
	SetActivePane(row, col);
}

//@doc CGXDSplitWnd
//@mfunc Set the active pane to the given pane given be the index.
//@rdesc void
//@parm int row Row index of the pane.
//@parm  int col Column index of the pane.
//@parm  CWnd* pWnd Pointer to the window in the given pane. If this pointer is NULL, the function will
//automatically obtain the window in the given pane. If pointer is not NULL, caller of this function is
//responsible to make sure this window is the window in the given pane.
void CGXDSplitWnd::SetActivePane(int row, int col, CWnd* pWnd)
{
	// set the focus to the pane
	CWnd* pPane = pWnd == NULL ? GetPane(row, col) : pWnd;
	if (pPane->IsKindOf(RUNTIME_CLASS(CView)))
	{
		CFrameWnd* pFrameWnd = GetParentFrame();
		ASSERT_VALID(pFrameWnd);
		pFrameWnd->SetActiveView((CView*)pPane);
	}
	else
	{
		TRACE0("Warning: Next pane is not a view - calling SetFocus.\n");
		pPane->SetFocus();
	}
}

//@doc CGXDSplitWnd
//@mfunc Use this function to get the active pane and the row and column index of the active pane if a active pane exists.
//@rdesc CWnd* The window in the active pane.
//@parm int* pRow Pointer to integer to accept the row index of the active pane.
//@parm  int* pCol Pointer to integer to accept the column index of the active pane.
CWnd* CGXDSplitWnd::GetActivePane(int* pRow, int* pCol)
	// return active view, NULL when no active view
{
	ASSERT_VALID(this);

	// attempt to use active view of frame window
	CWnd* pView = NULL;
	CFrameWnd* pFrameWnd = GetParentFrame();
	ASSERT_VALID(pFrameWnd);
	pView = pFrameWnd->GetActiveView();

	// failing that, use the current focus
	if (pView == NULL)
		pView = GetFocus();

	// make sure the pane is a child pane of the splitter
	if (pView != NULL && !IsChildPane(pView, pRow, pCol))
		pView = NULL;

	return pView;
}

/////////////////////////////////////////////////////////////////////////////
// CGXDSplitWnd diagnostics

#ifdef _DEBUG
void CGXDSplitWnd::AssertValid() const
{
	CWnd::AssertValid();
	ASSERT(m_nMaxRows >= 1);
	ASSERT(m_nMaxCols >= 1);
	ASSERT(m_nMaxCols > 1 || m_nMaxRows > 1);       // 1x1 is not permitted
	ASSERT(m_nRows >= 1);
	ASSERT(m_nCols >= 1);
	ASSERT(m_nRows <= m_nMaxRows);
	ASSERT(m_nCols <= m_nMaxCols);
}

void CGXDSplitWnd::Dump(CDumpContext& dc) const
{
	CWnd::Dump(dc);

	if (m_pDynamicViewClass != NULL)
		dc << _T("m_pDynamicViewClass = ") << m_pDynamicViewClass->m_lpszClassName;
	dc << _T("\nm_nMaxRows = ") << m_nMaxRows;
	dc << _T("\nm_nMaxCols = ") << m_nMaxCols;
	dc << _T("\nm_nRows = ") << m_nRows;
	dc << _T("\nm_nCols = ") << m_nCols;
	dc << _T("\nm_bHasHScroll = ") << m_bHasHScroll;
	dc << _T("\nm_bHasVScroll = ") << m_bHasVScroll;
	dc << _T("\nm_cxSplitter = ") << m_cxSplitter;
	dc << _T("\nm_cySplitter = ") << m_cySplitter;
	if (m_bTracking)
	{
		dc << _T("\nTRACKING: m_htTrack = ") << m_htTrack;
		dc << _T("\nm_rectLimit = ") << m_rectLimit;
		dc << _T("\nm_ptTrackOffset = ") << m_ptTrackOffset;
		dc << _T("\nm_rectTracker = ") << m_rectTracker;
		if (m_bTracking2)
			dc << _T("\nm_rectTracker2 = ") << m_rectTracker2;
	}

	dc << _T("\n");
}
#endif

/////////////////////////////////////////////////////////////////////////////


// CSplitterWnd
//@doc CGXDSplitWnd
//@mfunc Obtains the row count of this splitter window.
//@rdesc int The row count of this splitter window
int CGXDSplitWnd::GetRowCount() const
	{ return m_nRows; }
//@doc CGXDSplitWnd
//@mfunc Obtains the column count of this splitter window
//@rdesc int The column count of this splitter window
int CGXDSplitWnd::GetColumnCount() const
	{ return m_nCols; }
// obsolete functions
//@doc CGXDSplitWnd
//@mfunc Check if the given window is the window in the specified pane
//@rdesc BOOL Return TRUE if it is the window in the specified pane, otherwise return FALSE.
//@parm CWnd* pWnd The window to check.
//@parm  int& row Zero-based row index of the pane.
//@parm  int& col Zero-based column index of the pane.
BOOL CGXDSplitWnd::IsChildPane(CWnd* pWnd, int& row, int& col)
	{ return IsChildPane(pWnd, &row, &col); }
//@doc CGXDSplitWnd
//@mfunc Overload version of GetActivePane(int*, int*).
//@rdesc CWnd* The window in the active pane.
//@parm int& row Row index of the active pane in zero-based.
//@parm  int& col Col index of the active pane in zero-based.
CWnd* CGXDSplitWnd::GetActivePane(int& row, int& col)
	{ return GetActivePane(&row, &col); }
//@doc CGXDSplitWnd
//@mfunc Call this function to check the mouse tracking status.
//@rdesc BOOL Return TRUE if we are in the mouse tracking status, otherwise return FALSE.
BOOL CGXDSplitWnd::IsTracking()
	{ return m_bTracking; }
