///////////////////////////////////////////////////////////////////////////////
// gxDTabWnd.cpp
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

#ifdef _GXDLL
#undef AFXAPI_DATA
#define AFXAPI_DATA __based(__segname("_DATA"))
#endif

#ifndef _GXDSPLIT_H_
#include "grid\gxdsplit.h"
#endif

#ifndef _GXDTABWND_H_
#include "grid\gxdtabwnd.h"
#endif

//FOUNDATION_GLOBAL_FUNC_API(HWND) RWGetSafeHwnd();

IMPLEMENT_DYNCREATE(CGXDTabBeam, CWnd);
IMPLEMENT_DYNAMIC(CGXDEditLabelPopup, CEdit);

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

#define GX_IDW_HSCROLL_FIRST 1000
#define GX_IDW_VSCROLL_FIRST 1001
#define GX_IDW_SIZE_BOX 1002
#define GX_IDW_PANE_FIRST 1003

// enable use as custom control
//GRID_IMPLEMENT_REGISTER(CGXDTabBeam, CS_DBLCLKS | GX_GLOBALCLASS, 0, 0, 0);

// much of this code (e.g. CreateCommon, RecalcLayout, ...)
// is copied from the CSplitterWnd class and adapted to the tabwnd class

/////////////////////////////////////////////////////////////////////////////
// Win4 specific defines

// Scrolling
const int GX_SCRLMOSTLEFT  = 0;
const int GX_SCRLLEFT  = 1;
const int GX_SCRLRIGHT = 2;
const int GX_SCRLMOSTRIGHT = 3;

// Colors for Arrows
const COLORREF rgbBlack = RGB(0,0,0);
const COLORREF rgbGrey  = RGB(96,96,96);

/////////////////////////////////////////////////////////////////////////////
// CGXDTabInfo

CGXDTabInfo::CGXDTabInfo()
{
	pExtra = 0;
	bSel = FALSE;
	nWidth = 60;
	bDeleteExtra = FALSE;

	m_bHot = FALSE;

	// Scrollbar Info
	memset(&sbInfoVert, 0, sizeof(SCROLLINFO));
	memset(&sbInfoHorz, 0, sizeof(SCROLLINFO));
}

CGXDTabInfo::~CGXDTabInfo()
{
	if (bDeleteExtra)
		delete pExtra;
}


/////////////////////////////////////////////////////////////////////////////
// CGXDTabBeam

BEGIN_MESSAGE_MAP(CGXDTabBeam, CWnd)
	//{{AFX_MSG_MAP(CGXDTabBeam)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_SYSCOLORCHANGE()
	ON_WM_WININICHANGE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CGXDTabBeam::CGXDTabBeam()
{
	m_pFontNormal = 0;
	m_pFontCurrent = 0;

	m_nHeight = GetSystemMetrics(SM_CYHSCROLL);

	m_bScrollBtns = TRUE;
	m_nScrollBtns = 2;

	m_nButtonWidth = m_nHeight;
	m_nMargin = m_nScrollBtns * m_nButtonWidth;

	m_nWidthEx = 7;

	m_nxTracking = -1;

	m_nTabs = 0;
	m_nCurrent = -1;
	m_nFirstTab = 0;

	m_pNotifyWnd = 0;

	m_hcurArrow  = ::LoadCursor(NULL, IDC_ARROW);

	if (RWIsAppThemed() && RWIsThemeActive()) 
	{
		m_bMouseCapture = FALSE;
		for (int i = 0; i < 4; i ++) m_bBtnHot[i] = FALSE;
	}
}

//@doc CGXDTabBeam
//@mfunc Create this tab-beam control window.
//@rdesc BOOL Return TRUE if successful, otherwise return FALSE.
//@parm DWORD dwStyle The window style for this tab-beam control window.
//@parm  const RECT& rect A reference to RECT specifying the position of this tab-beam control.
//@parm  CWnd* pParentWnd A pointer to the parent window.
//@parm  UINT nID The id of this tab-beam control.
BOOL CGXDTabBeam::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	if ( CWnd::Create(NULL, NULL, dwStyle | WS_CHILD, rect, pParentWnd, nID) )
	{
		CreateFonts();
		SetWindowPos(NULL, 0, 0, 1, m_nHeight,
					SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE);

		UpdateColors();

		return TRUE;
	}

	return FALSE;
}

CGXDTabBeam::~CGXDTabBeam()
{
	DestroyFonts();

	for (int i = 0; i < m_nTabs; i++)
		delete m_TabInfo[i];
}

void CGXDTabBeam::CreateBrushes()
{
	m_brFaceSel.DeleteObject();
	m_brFaceNormal.DeleteObject();

	m_brFaceSel.CreateSolidBrush(m_rgbFaceSel);
	m_brFaceNormal.CreateSolidBrush(m_rgbFaceNormal);
}

void CGXDTabBeam::CreateFonts()
{
	DestroyFonts();

	LOGFONT lf;

	// use "Arial" as default font
	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfPitchAndFamily = VARIABLE_PITCH | FF_SWISS;
	lf.lfQuality = DEFAULT_QUALITY;
	lf.lfClipPrecision = CLIP_LH_ANGLES | CLIP_STROKE_PRECIS;
	// QA: 31989 - #if Secure Code Cleanup.
	_tcscpy(lf.lfFaceName, _T("Arial"));

#if _MFC_VER >= 0x0400
	if (GetSystemMetrics(SM_DBCSENABLED))
	{
		// Win95/4.0 only supports DEFAULT_GUI_FONT.  Using this
		// font makes it more easy to port the app to
		// international markets
		// Load default system font
		CFont font;
		font.CreateStockObject(DEFAULT_GUI_FONT);
		if (font.GetSafeHandle() == 0)
			font.CreateStockObject(SYSTEM_FONT);

		// Retrieve logical font information
		if (font.GetSafeHandle())
			font.GetObject(sizeof(lf), &lf);
	}
#endif

	lf.lfCharSet = GXGetFontState()->GetFontCharset(GXGetFontState()->LookupFontInfo(lf.lfFaceName));

	lf.lfItalic = 0;
	lf.lfUnderline = 0;
	lf.lfHeight = (m_nHeight-2);	// font size based on tab beam height

	// Create the normal font
	lf.lfWeight = FW_NORMAL;
	m_pFontNormal = new CFont;
	m_pFontNormal->CreateFontIndirect(&lf);

	// Create the bold font
	lf.lfWeight = FW_BOLD;
	m_pFontCurrent = new CFont;
	m_pFontCurrent->CreateFontIndirect(&lf);
}

void CGXDTabBeam::DestroyFonts()
{
	if (m_pFontNormal)
		delete m_pFontNormal;
	if (m_pFontCurrent)
		delete m_pFontCurrent;
}

void CGXDTabBeam::SetTabBkColor(int nTab, COLORREF cr)
{
	CGXDTabInfo *pInfo = &GetTab(nTab);

	pInfo->rgbFaceNormal = cr;
	pInfo->brFaceNormal.DeleteObject();
	pInfo->brFaceNormal.CreateSolidBrush(cr);

	// set flagUseOwnColorFaceNormal to be true
	pInfo->flagUseOwnColorFaceNormal = 1;

}

void CGXDTabBeam::SetTabSelBkColor(int nTab, COLORREF cr)
{
	CGXDTabInfo *pInfo = &GetTab(nTab);

	pInfo->rgbFaceSel = cr;
	pInfo->brFaceSel.DeleteObject();
	pInfo->brFaceSel.CreateSolidBrush(cr);

	// set flagUseOwnColorFaceSel to be true
	pInfo->flagUseOwnColorFaceSel = 1;
}


void CGXDTabBeam::DisplayScrollBtns(BOOL bSet, int nScrollBtns)
{
	if (bSet)
	{
		ASSERT(nScrollBtns == 2 || nScrollBtns == 4);
		m_nScrollBtns = nScrollBtns;
		m_nMargin = m_nScrollBtns * m_nButtonWidth;
	}
	else
	{
		m_nScrollBtns = 0;
		m_nMargin = 0;
	}
	m_bScrollBtns = bSet;
	Invalidate(FALSE);
}

void CGXDTabBeam::SetNotifyWnd(CWnd* pNotify)
{
	m_pNotifyWnd = pNotify;
}

// CGXDTabBeam Tabs

// Insert Tab or append Tab if bInsert is FALSE
// pExtra can be used for CWnd-Object
// bDelExtra must not be TRUE for a CWnd, because a CWnd normally gets destroyed itself
// (bDelExtra should be TRUE for buffers etc., which should get
// destroyed when the Tab gets destroyed)

//@doc CGXDTabBeam
//@mfunc Call this function to insert or append a tab to this tab-beam control.
//@rdesc void 
//@parm BOOL bInsert If TRUE, it inserts the tab, otherwise it append the tab.
//@parm  LPCTSTR szLabel A pointer to string for the name of the new tab.
//@parm  CObject* pExtra A pointer to some extra data associated with this tab. It usually is a
// window object.
//@parm  BOOL bDelExtra Flags indicating if the tab-beam should free the memory used by pExtra object. Generally,
//if pExtra is a window object, it should be FALSE and the window will destroy itself, otherwise it should be TRUE.
//@parm  int nWidth Width of this tab. It is generally a good idea to let the tab-beam figure out the width automatically 
//by passing -1.
//@parm  HMENU hMenu A pointer to a menu handle that to be accociated with this tab. When you switch 
//tabs, you can use this menu to modify the menu of the frame window.
void CGXDTabBeam::InsertTab(BOOL bInsert, LPCTSTR szLabel, CObject* pExtra, BOOL bDelExtra, int nWidth, HMENU hMenu)
{
	CGXDTabInfo* pInfo = new CGXDTabInfo;
	pInfo->sLabel = szLabel;
	pInfo->nWidth = nWidth;
	pInfo->pExtra = pExtra;
	pInfo->bDeleteExtra = bDelExtra;
	pInfo->hMenu = hMenu;

	// Use the CGXDTabBeam's default color and brush
	pInfo->flagUseOwnColorFaceNormal= 0;
	pInfo->flagUseOwnColorFaceSel=  0;

	// Initialize the color and brush anyway though
	// they are not used. This is to prevent some user go to
	// set the color flags to true in CGXDTabInfo directly
	// and get unexpected results.
	pInfo->rgbFaceNormal= m_rgbFaceNormal;
	pInfo->rgbFaceSel= m_rgbFaceSel;
	pInfo->brFaceNormal.CreateSolidBrush(m_rgbFaceNormal);
	pInfo->brFaceSel.CreateSolidBrush(m_rgbFaceSel);

	// Add info and adjust the tab size

	if (m_nCurrent == -1 || !bInsert)
	{
		m_TabInfo.SetAtGrow(m_nTabs, pInfo);
		if (nWidth < 0)
			AdjustTabSize(m_nTabs);
	}
	else
	{
		m_TabInfo.InsertAt(m_nCurrent, pInfo, 1);
		if (nWidth < 0)
			AdjustTabSize(m_nCurrent);
	}
	m_nTabs++;

	Invalidate();

	// Make sure tab is visible

	if (m_nCurrent == -1)
	{
		m_nCurrent = m_nTabs-1;
		ScrollTabInView(m_nCurrent);
	}
}

//@doc CGXDTabBeam
//@mfunc Call this function to delete the given tab. When using this function, if extra data pointer asccociated
//with this tab is a window, this function will not destroy the window. So you should get hold of the window 
//pointer first before delete this tab and then destory the window at some point.
//@rdesc void 
//@parm int nTab The index of the tab to be deleted.
void CGXDTabBeam::DeleteTab(int nTab)
{
	if (m_nCurrent == nTab)
	{
		m_nCurrent = 0;
		m_nFirstTab = 0;
	}

	delete m_TabInfo[nTab];
	m_TabInfo.RemoveAt(nTab);
	m_nTabs--;

	if (m_nFirstTab >= m_nTabs)
		m_nFirstTab = max(0, m_nTabs-1);

	Invalidate();
}

CGXDTabInfo& CGXDTabBeam::GetTab(int nTab)
{
	ASSERT(nTab >= 0 && nTab < m_TabInfo.GetSize());
	return *((CGXDTabInfo*) m_TabInfo[nTab]);
}

// Calculate the left x-coordinate of the tab
int CGXDTabBeam::CalcTabOffset(int nTab)
{
	int offset = m_bScrollBtns?m_nMargin+1:0;
	for (int i = m_nFirstTab; i < nTab; i++)
		offset += GetTab(i).nWidth + m_nWidthEx;
	if (nTab < m_nFirstTab)
	{
		for (int i = nTab; i < m_nFirstTab; i++)
			offset -= GetTab(i).nWidth + m_nWidthEx;
	}
	return offset;
}

// Get the tab for offset (x-coordinate)
int CGXDTabBeam::CalcTabFromOffset(int nOffset)
{
	int nTab = m_nFirstTab;
    int offset;
	for (offset = m_bScrollBtns?m_nMargin+1:0;
		nTab < m_nTabs && offset < nOffset;
		offset += GetTab(nTab++).nWidth + m_nWidthEx)
		;

	return nTab < m_nTabs || offset > nOffset ? nTab-1 : -1;
}

int CGXDTabBeam::CalcLastVisibleTab()
{
	CRect rect;
	GetClientRect(&rect);

	int offset = m_bScrollBtns?m_nMargin+1:0;
	offset += GetTab(m_nFirstTab).nWidth + 2*m_nWidthEx;
	int i; 
	for (i = m_nFirstTab+1; i < m_nTabs && offset < rect.right; i++)
		offset += GetTab(i).nWidth + m_nWidthEx;

	if (offset > rect.right)
		return max(m_nFirstTab, i-2);

	return m_nTabs-1;
}


// Tab has been pressed
void CGXDTabBeam::SwitchToTab(CPoint point)
{
	//BOOL bInvalidate = FALSE;//Unused
	int n = 0;
	if (point.x < m_nMargin)
		return;

	if (point.x - m_nMargin < m_nWidthEx)
		n = max(0, m_nFirstTab - 1);
	else
		n = CalcTabFromOffset(point.x);

	if (n == -1)
		return;

	BOOL bCanSwitch;

	if (m_pNotifyWnd)
		bCanSwitch = !m_pNotifyWnd->SendMessage(WM_GX_CANTABSWITCH, (WPARAM) n, 0);
	else
		bCanSwitch = !GetParent()->SendMessage(WM_GX_CANTABSWITCH, (WPARAM) n, 0);

	if (!bCanSwitch)
		return;

	BOOL bSwitch = (n != m_nCurrent);

	m_nCurrent = n;
	if (!GetTab(m_nCurrent).bSel)
	{
		for (int i = 0; i < m_nTabs; i++)
			GetTab(i).bSel = 0;
	}

	ScrollTabInView(m_nCurrent);

	if (bSwitch)
	{
		Invalidate();
		UpdateWindow();
	}

	// TabSwitch will always be sent, to give the parent window
	// the ability to set the focus to the sheet
	{
		if (m_pNotifyWnd)
			m_pNotifyWnd->PostMessage(WM_GX_TABSWITCH, (WPARAM) m_nCurrent, 0);
		else
			GetParent()->PostMessage(WM_GX_TABSWITCH, (WPARAM) m_nCurrent, 0);
	}
}

void CGXDTabBeam::ScrollTabInView(int nTab)
{
	if (nTab < m_nFirstTab)
	{
		Invalidate();
		m_nFirstTab = nTab;
	}
	else if (nTab > CalcLastVisibleTab())
	{
		Invalidate();
		do {
			m_nFirstTab++;
		} while (nTab > CalcLastVisibleTab());
	}
}

// Double Clicked a tab
void CGXDTabBeam::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if (point.x < m_nMargin || CalcTabFromOffset(point.x) == -1)
	{
		OnLButtonDown(nFlags, point);
		return;
	}

	int n = m_nCurrent;
	if (n < m_nFirstTab)
	{
		OnLButtonDown(nFlags, point);
		return;
	}

	if (m_pNotifyWnd)
		m_pNotifyWnd->PostMessage(WM_GX_TABDBLCLK, (WPARAM) n, 0);
	else
		GetParent()->PostMessage(WM_GX_TABDBLCLK, (WPARAM) n, 0);
}

// Adjust tab size to content
//@doc CGXDTabBeam
//@mfunc Call this function to adjust the tab size to its content.
//@rdesc void 
//@parm int nTab The index to the tab to adjust size for.
void CGXDTabBeam::AdjustTabSize(int nTab)
{
	CClientDC dc(this);

	CFont* pOldFont = dc.SelectObject(m_pFontCurrent);

	CSize size = dc.GetTextExtent(
		GetTab(nTab).sLabel,
		GetTab(nTab).sLabel.GetLength());

	dc.SelectObject(pOldFont);

	GetTab(nTab).nWidth = size.cx + m_nWidthEx;
	Invalidate();
}

//@doc CGXDTabBeam
//@mfunc Call this function to find the tab index by comparing the passing pointer value with that in 
//the pExtra field of the tab info.
//@rdesc int If a tab is found, return the zero-based index of it, otherwise return -1.
//@parm const CObject *pObject A pointer ot CObject to compare against.
int CGXDTabBeam::FindTab(const CObject *pObject)
{
	for (int i = 0; i < m_nTabs; i++)
		if (GetTab(i).pExtra == pObject)
			return i;
	return -1;
}

// Current Selection, TabCount inlines

//@doc CGXDTabBeam
//@mfunc Call this funtion to get the index of current displayed tab.
//@rdesc int Index of the current displayed tab.
int CGXDTabBeam::GetCurSel()
{ 
	return m_nCurrent; 
}

int CGXDTabBeam::GetCount()
{ 
	return m_nTabs; 
}


/////////////////////////////////////////////////////////////////////////////
// CGXDTabBeam Painting

void CGXDTabBeam::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	int i;
	CRect rectPaint;
	dc.GetClipBox(&rectPaint);

	if (m_nxTracking >= 0)
		rectPaint.left = max(m_nxTracking-1, 0);

	CDC dcMem;
	CBitmap bmPaint;
	CBitmap* pbmOld;

	GetClientRect(rectPaint);
	dcMem.CreateCompatibleDC(&dc);
	bmPaint.CreateCompatibleBitmap(&dc, rectPaint.Width(), rectPaint.Height());
	pbmOld = (CBitmap*) dcMem.SelectObject(&bmPaint);

	dcMem.OffsetViewportOrg(-rectPaint.left, -rectPaint.top);
	dcMem.SetBrushOrg(rectPaint.left % 8, rectPaint.top % 8);   // align dcMem with grid's dc

	// default font
	CFont* pOldFont = dcMem.SelectObject(m_pFontNormal);

	CRect rect;
	dcMem.GetClipBox(&rect);

	if (RWIsAppThemed() && RWIsThemeActive())
	{
		GXPatB (&dcMem, rect, m_rgbFaceNormal);
	}

	// Scroll Buttons
	dcMem.SelectClipRgn(NULL);
	if (m_bScrollBtns && (m_nxTracking == -2 || rect.left <= m_nMargin))
	{
		for (i = 0; i < m_nScrollBtns; i++)
			DrawButton(&dcMem, i + ((m_nScrollBtns==2)?1:0), FALSE);
	}

	// Tabs
	{
		rect.left = max(rect.left, m_bScrollBtns?m_nMargin+1:0);
		dcMem.IntersectClipRect(rect);

		HTHEME lhTheme = NULL;
		// Note: Calling dc.GetWindow() will return an invalid handle. 
		// Instead, call AfxGetMainWnd()->GetSafeHwnd().
		if (RWIsAppThemed() && RWIsThemeActive())
			lhTheme = RWOpenThemeData(RWGetSafeHwnd(), L"HEADER" );
		
		if (lhTheme)
		{
			CRect recPane = CRect(CPoint(rect.left, 1), CSize(rect.Width(), rect.Height()));		

			RWDrawThemeBackground (lhTheme, dcMem.GetSafeHdc(), HP_HEADERITEM, HIS_NORMAL, &recPane, NULL);
			RWCloseThemeData(lhTheme);
		}
		else
		{
			// Grey Beam
			PatB(&dcMem, rect.left, 1, rect.Width(), rect.Height(), m_rgbBeam);
		}

		// Black Border
		PatB(&dcMem, rect.left, 0, rect.Width(), 1, rgbBlack);

		// Which tabs need painting?
		int nLast = CalcTabFromOffset(rect.right+m_nWidthEx);
		if (nLast == -1)
			nLast = m_nTabs-1;

		int nFirst = max(CalcTabFromOffset(rect.left)-1, 0);

		// Draw tabs
		for (i = nLast; i >= nFirst; i--)
			if (i != m_nCurrent)
				DrawTab(&dcMem, i);

		// Current tab
		if (m_nCurrent >= nFirst && m_nCurrent <= nLast)
			DrawTab(&dcMem, m_nCurrent);
	}

	// Clean up
	dcMem.SelectObject(pOldFont);

	dc.BitBlt(rectPaint.left, rectPaint.top, rectPaint.Width(), rectPaint.Height(), &dcMem,
			rectPaint.left, rectPaint.top, SRCCOPY);

	// clean-up for memory DC
	dcMem.SelectObject(pbmOld);
}


void CGXDTabBeam::DrawTab(CDC* pDC, int nTab, BOOL bMouseMove)
{
	int x = CalcTabOffset(nTab);
	BOOL bSel = (GetTab(nTab).bSel);
	BOOL bCur = (nTab == m_nCurrent);
	
	int nHeight = m_nHeight - GXGetAppData()->bNotWin4;

	// Tab Polygon
	CRgn rgn;
	POINT pts[4];
	pts[0].x = x;                                   pts[0].y = 0;
	pts[1].x = x+GetTab(nTab).nWidth+2*m_nWidthEx;  pts[1].y = 0;
	pts[2].x = x+GetTab(nTab).nWidth+m_nWidthEx;    pts[2].y = nHeight;
	pts[3].x = x+m_nWidthEx;                        pts[3].y = nHeight;
	rgn.CreatePolygonRgn(pts, 4, ALTERNATE);
	
	if (bSel || bCur)
	{
		if (!GetTab(nTab).flagUseOwnColorFaceSel)
			pDC->FillRgn(&rgn, &m_brFaceSel);
		else
			pDC->FillRgn(&rgn, &GetTab(nTab).brFaceSel);
	}
	else
	{
		if (!GetTab(nTab).flagUseOwnColorFaceNormal)
			pDC->FillRgn(&rgn, &m_brFaceNormal);
		else
			pDC->FillRgn(&rgn, &GetTab(nTab).brFaceNormal);
	}

	HTHEME lhTheme = NULL;
	if (RWIsAppThemed() && RWIsThemeActive())
		lhTheme = RWOpenThemeData (RWGetSafeHwnd(), L"HEADER");
	
	if (lhTheme)
	{							
		if ((GetTab(nTab).m_bHot && bMouseMove) || bCur) 
		{
			CRect r = CRect(x+m_nWidthEx, nHeight, x+GetTab(nTab).nWidth+m_nWidthEx, 0);
			int iState = HIS_HOT;
		
			RWDrawThemeBackground (lhTheme, pDC->GetSafeHdc(), HP_HEADERITEM, iState, &r, NULL);
			RWCloseThemeData(lhTheme);	
		}
	}

	// Frame
	pDC->FrameRgn(&rgn, &m_brBlack, 1, 1);

	if (bCur)
		PatB(pDC, pts[0].x, 0, pts[1].x-pts[0].x, 1, m_rgbFaceSel);

	// shadow
	CPen* pOldPen = pDC->SelectObject(&m_penShadow);
	pDC->MoveTo(x+m_nWidthEx+1, nHeight-1);
	pDC->LineTo(x+GetTab(nTab).nWidth+m_nWidthEx-1, nHeight-1);
	pDC->LineTo(x+GetTab(nTab).nWidth+2*m_nWidthEx-2, 0);
	pDC->SelectObject(pOldPen);

	// Draw Text
	COLORREF rgbText = bCur ? m_rgbTextCurrent : m_rgbTextNormal;
	COLORREF rgbBack = bSel ? m_rgbFaceSel : m_rgbFaceNormal;

	pDC->SetTextColor(rgbText);
	pDC->SetBkColor(rgbBack);
	pDC->SetBkMode(TRANSPARENT);

	// Inside rect
	CRect rect;
	rect.left = x+m_nWidthEx;
	rect.right = rect.left+GetTab(nTab).nWidth;
	rect.top = 0;
	rect.bottom = m_nHeight;

	// check if current tab
	CFont* pOldFont = NULL;
	if (bCur)
		pOldFont = pDC->SelectObject(m_pFontCurrent);

	// center vertically
	CSize size = pDC->GetTextExtent(_T("t"), 1);
	rect.top += max(m_nHeight-size.cy, 0)/2;

	pDC->DrawText(GetTab(nTab).sLabel, -1, rect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);

	// clean up
	if (bCur)
		pDC->SelectObject(pOldFont);
}

void CGXDTabBeam::DrawButton(CDC* pDC, int nButton, BOOL bPressed)
{
	int i = nButton;

	if (m_nScrollBtns == 2)
		i--;

	CRect rect( i * m_nButtonWidth, 0, (i + 1) * m_nButtonWidth, m_nHeight);

	HTHEME lhTheme = NULL;
	if (RWIsAppThemed() && RWIsThemeActive())
		lhTheme = RWOpenThemeData (RWGetSafeHwnd(), L"BUTTON");

	if (lhTheme)
	{				
		int iState = bPressed ? PBS_PRESSED : (m_bBtnHot[nButton] ? PBS_HOT : PBS_NORMAL);
		int nc = (m_nScrollBtns == 2) ? i + 1 : i;

		CRect rectClient;
		GetClientRect(rectClient);

		if (GetCount() <= 1 || nc <= 1 && m_nFirstTab == 0 || nc >= 2 && CalcTabFromOffset(rectClient.right) == -1)
		  iState = PBS_DISABLED;
		RWDrawThemeBackground( lhTheme, pDC->GetSafeHdc(), BP_PUSHBUTTON, iState, &rect, 0 );		

		RWCloseThemeData(lhTheme);
	}
	else
	{
		DrawBlankButton(pDC, rect.left, rect.top, rect.Width(), rect.Height(), bPressed);

		// Black border
		if (GXGetAppData()->bWin4)
			PatB(pDC, rect.left, rect.bottom-1, rect.Width(), 1, rgbBlack);
	}

	// Draw arrows
	int x, y;

	int cx = m_nHeight > 19 ? 6 : 5;

	if (GXGetAppData()->bWin4)
		cx += 2;

	int cy = m_nHeight > 19 ? 9 : 7;

	// center the 9-pixel high arrow vertically
	y = rect.top + ((rect.Height() - 9) / 2);
	int y2 = rect.top + ((rect.Height() - cy) / 2);

	// if pressed, image gets moved
	if (bPressed)
		y++;

	if (m_nScrollBtns == 2)
		i++;

	COLORREF rgb = rgbBlack;    // Black

	CRect rectClient;
	GetClientRect(rectClient);

	if (GetCount() <= 1 || i <= 1 && m_nFirstTab == 0 || i >= 2 && CalcTabFromOffset(rectClient.right) == -1)
		rgb = rgbGrey;

	switch(i)
	{
	case GX_MOVERECORD_FIRST:
		// Most left
		x = rect.left + ((rect.Width() - cx) / 2) - 1;
		if (bPressed)
			x++;

		PatB(pDC, x, y2, 1, cy, rgb);

	case GX_MOVERECORD_PREV:
		// Left Arrow
		x = rect.left + ((rect.Width() - cx) / 2) - 1;
		if (bPressed)
			x++;

		PatB(pDC, x+2, y+4, 1, 1, rgb);
		PatB(pDC, x+3, y+3, 1, 3, rgb);
		PatB(pDC, x+4, y+2, 1, 5, rgb);
		PatB(pDC, x+5, y+1, 1, 7, rgb);

		if (m_nHeight > 19)
			PatB(pDC, x+6,   y, 1, 9, rgb);
		break;

	case GX_MOVERECORD_LAST:
		// Most Right
		x = rect.right - ((rect.Width() - cx) / 2);
		if (bPressed)
			x++;

		PatB(pDC, x, y2, 1, cy, rgb);

	case GX_MOVERECORD_NEXT:
		// Right Arrow
		x = rect.right - ((rect.Width() - cx) / 2);
		if (bPressed)
			x++;

		PatB(pDC, x-2, y+4, 1, 1, rgb);
		PatB(pDC, x-3, y+3, 1, 3, rgb);
		PatB(pDC, x-4, y+2, 1, 5, rgb);
		PatB(pDC, x-5, y+1, 1, 7, rgb);
		if (m_nHeight > 19)
			PatB(pDC, x-6,   y, 1, 9, rgb);
		break;
	}
}


BOOL CGXDTabBeam::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	GetClientRect(rect);

	if (m_nxTracking >= 0)
	{
		rect.left = max(m_nxTracking-1, 0);

		PatB(pDC, rect.left, 1, rect.Width(), rect.Height(), m_rgbBeam);
	}

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CGXDTabBeam Mouse Actions

// Replacement for SetCapture
// Sends WM_MOUSEMOVE Messages, when a Button is pressed
void CGXDTabBeam::AutoMove(UINT nRefMessage)
{
	MSG   msgLoop;          // dummmy message structure to process incoming
							// messages while autoscrolling.
	CPoint ptCursorPos;

	msgLoop.message = 0;    // forces at least one loop.

	SetCapture();

	DWORD nLastTicks = GetTickCount();
	DWORD nTicksNeeded = 200;

	// Process all messages until the relevant mouse button
	// has been released.
	while (msgLoop.message != nRefMessage) // nRefMessage depends on which button
										// has been used to trigger autoscrolling.
	{
		// Process incoming messages until autoscroll button is released
		if (PeekMessage(&msgLoop, 0, 0, 0, PM_REMOVE))
		{
			if (msgLoop.message != WM_MOUSEMOVE)
			{
				TranslateMessage(&msgLoop);
				DispatchMessage(&msgLoop);
			}
			continue;
		}

		GetCursorPos(&ptCursorPos);
		ScreenToClient(&ptCursorPos);

		if (GetTickCount() - nLastTicks > nTicksNeeded)
		{
			// peridically do OnMouseMove
			OnMouseMove(0, ptCursorPos);
			if (nTicksNeeded > 100)
				nTicksNeeded -= 20;
		}
	}

	ReleaseCapture();
}

// Button is hit
// 0 = most left, 1 = scroll left, 2 = scroll right, 3 = most right
// if nButton is not -1, it is checked if the mouse has left
// the pressed button, (the button will get unpressed in OnMouseMove)
int CGXDTabBeam::ScrollBtnHit(CPoint point, int nButton /*= -1*/, BOOL bScroll)
{
	if (point.y < 0 || point.y > m_nHeight
		|| point.x < 0 || point.x >= m_nMargin)
		return -1;

	// get Button
	int nBtn = point.x / m_nButtonWidth;

	if (m_nScrollBtns == 2)
		nBtn++;

	CRect rectClient;
	GetClientRect(rectClient);

	if (nBtn <= 1 && m_nFirstTab == 0 || nBtn >= 2 && CalcTabFromOffset(rectClient.right) == -1)
		return -1;

	if (nButton != -1 && nBtn != nButton)
		return -1;

	// Button is pressed
	if (bScroll) Scroll(nBtn);

	return nBtn;
}

void CGXDTabBeam::Scroll(int nDirection)
{
	// ensure that edit-popup is not visible
	GetParent()->SendMessage(WM_GX_EDITCANCEL, 0, 0);

	int n = m_nFirstTab;
	switch (nDirection)
	{
	case GX_SCRLMOSTLEFT:  n = 0; break;
	case GX_SCRLLEFT:  n = m_nFirstTab-1; break;
	case GX_SCRLRIGHT: n = m_nFirstTab+1; break;
	case GX_SCRLMOSTRIGHT: n = m_nTabs-1; break;
	default:
		return;
	}

	// Calculate last visible tabs
	CRect rect;
	GetClientRect(rect);
	rect.left = m_nMargin+1;

	int nLast = m_nTabs-1;
	int dx = GetTab(nLast).nWidth+2*m_nWidthEx;
	while (nLast > m_nFirstTab && dx+GetTab(nLast-1).nWidth+m_nWidthEx < rect.Width())
		dx += GetTab(--nLast).nWidth+m_nWidthEx;

	// Adjust n (this the new value for m_nFirstTab)
	n = max(0, min(nLast, n));

	// Check if n is different
	if (n != m_nFirstTab)
	{
		CRect rect;
		GetClientRect(rect);
		rect.left = m_nMargin+1;

		// Scroll
		if (n > m_nFirstTab)
		{
			int scrolled = 0;
			for (int i = m_nFirstTab; i < n; i++)
				scrolled += GetTab(i).nWidth+m_nWidthEx;
			ScrollWindow(-scrolled, 0, rect, rect);
		}
		else
		{
			int scrolled = 0;
			for (int i = n; i < m_nFirstTab; i++)
				scrolled += GetTab(i).nWidth+m_nWidthEx;
			ScrollWindow(scrolled, 0, rect, rect);
			rect.right = rect.left+scrolled+m_nWidthEx;
			InvalidateRect(rect, FALSE);
		}
		m_nFirstTab = n;
	}
}

void CGXDTabBeam::OnLButtonDown(UINT nFlags, CPoint point)
{
	if ((m_nBtnDown = ScrollBtnHit(point)) != -1)
	{
		// Scrolling
		CClientDC dc(this);
		DrawButton(&dc, m_nBtnDown, m_bBtnDown = TRUE);

		m_bMouseCapture = TRUE;
		AutoMove(WM_LBUTTONUP); // (SetCapture until WM_LBUTTONUP)
	}
	else if (nFlags & MK_CONTROL || nFlags & MK_SHIFT)
	{
		// Select Tabs
		CRect rect;
		GetClientRect(rect);
		rect.left = m_bScrollBtns?m_nMargin+1:0;
		int n = CalcTabFromOffset(point.x);
		if (n == -1)
			return;
		if (nFlags & MK_CONTROL)
		{
			GetTab(n).bSel = !GetTab(n).bSel;
			InvalidateRect(rect, FALSE);
		}
		else if (m_nCurrent != -1)
		{
			while (n != m_nCurrent)
			{
				GetTab(n).bSel = 1;
				n = (n > m_nCurrent)?n-1:n+1;
			}
			InvalidateRect(rect, FALSE);
		}
	}
	else
		SwitchToTab(point);

	CWnd::OnLButtonDown(nFlags, point);
}

void CGXDTabBeam::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_bMouseCapture)
	{
		m_bMouseCapture = FALSE;

		if (m_nBtnDown != -1 && m_bBtnDown)
		{
			UpdateWindow();
			CClientDC dc(this);
			for (int i = 0; i < m_nScrollBtns; i++)
				DrawButton(&dc, i + ((m_nScrollBtns==2)?1:0), FALSE);
		}
	}

	m_bBtnDown = FALSE;

	CWnd::OnLButtonUp(nFlags, point);
}

void CGXDTabBeam::OnMouseMove(UINT /*nFlags*/, CPoint point)
{
	SetCursor(m_hcurArrow);

	// -- Handle Mouse Move
	if (RWIsAppThemed() && RWIsThemeActive()) 
	{
		UpdateWindow();
		CClientDC dc(this);

		CFont* pOldFont = dc.SelectObject(m_pFontNormal);

		int nBtnOver = ScrollBtnHit(point, -1, FALSE);
		int i;
		for (i = 0; i < 4; i++)
		{
			BOOL bRedraw = (m_bBtnHot[i] && (i != nBtnOver))
			 || (!m_bBtnHot[i] && (i == nBtnOver));

			if (bRedraw)
			{
				m_bBtnHot[i] = (i == nBtnOver) ? TRUE : FALSE;
				DrawButton(&dc, i, FALSE);
			}
		}
		
		int n = CalcTabFromOffset(point.x);		
		for (i = m_nFirstTab; i < m_nTabs; i ++)
		{
			if (i == m_nCurrent) continue;

			CGXDTabInfo &tInfo = GetTab(i);
			if (i == n && !tInfo.m_bHot)
			{
				tInfo.m_bHot = TRUE;				
				DrawTab (&dc, i, TRUE);
			}
			else if (i != n && tInfo.m_bHot)
			{
				tInfo.m_bHot = FALSE;
				DrawTab (&dc, i, TRUE);
			}
		}
		
		dc.SelectObject(pOldFont);

		TRACKMOUSEEVENT eventTrack;

		memset( &eventTrack, 0x00, sizeof( eventTrack ) );
			
		eventTrack.cbSize = sizeof( eventTrack );
		eventTrack.dwFlags = TME_LEAVE;
		eventTrack.hwndTrack = m_hWnd;
		eventTrack.dwHoverTime = HOVER_DEFAULT;

		RWTrackMouseEvent( &eventTrack );
	}

	// -- Handle Mouse Move

	if (!m_bMouseCapture)
		return;

	if (m_nBtnDown != -1)
	{
		// Check if mouse has left the button,
		// ScrollBtnHit does scrolling
		BOOL bDraw = FALSE;
		if (ScrollBtnHit(point, m_nBtnDown) == -1)
		{
			bDraw = m_bBtnDown;
			m_bBtnDown = FALSE;
		}
		else
		{
			bDraw = !m_bBtnDown;
			m_bBtnDown = TRUE;
		}

		if (bDraw)
		{
			UpdateWindow();
			CClientDC dc(this);
			for (int i = 0; i < m_nScrollBtns; i++)
			{
				int n = i + ((m_nScrollBtns==2)?1:0);
				DrawButton(&dc, n, n == m_nBtnDown && m_bBtnDown);
			}
		}
	}
}

BOOL CGXDTabBeam::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	if (RWIsAppThemed() && RWIsThemeActive()) 
	{
		if( message == WM_MOUSELEAVE )
		{
			UpdateWindow();
			CClientDC dc(this);

			CFont* pOldFont = dc.SelectObject(m_pFontNormal);
			int i;
			for (i = 0; i < 4; i++)
			{
				if (m_bBtnHot[i])
				{
					m_bBtnHot[i] = FALSE;
					DrawButton(&dc, i, FALSE);
				}
			}
			
			for (i = 0; i < m_nTabs; i++)
			{
				if (i != m_nCurrent)
				{
					CGXDTabInfo &tInfo = GetTab(i);
					if (tInfo.m_bHot)
					{
						tInfo.m_bHot = FALSE;
						DrawTab (&dc, i);
					}
				}
			}

			dc.SelectObject(pOldFont);
		}
	}
	
	return CWnd::OnWndMsg( message, wParam, lParam, pResult );
}

void CGXDTabBeam::UpdateColors()
{
	// Colors
	m_rgbTextCurrent = GetSysColor(COLOR_WINDOWTEXT);
	m_rgbTextNormal = GetSysColor(COLOR_WINDOWTEXT);
	m_rgbFaceNormal = GetSysColor(COLOR_BTNFACE);
	m_rgbFaceSel = GetSysColor(COLOR_WINDOW); // RGB(255,255,255);
	m_rgbBeam = GetSysColor(COLOR_SCROLLBAR);

	// Brushes
	m_brFaceSel.DeleteObject();
	m_brFaceSel.CreateSolidBrush(m_rgbFaceSel);
	m_brFaceNormal.DeleteObject();
	m_brFaceNormal.CreateSolidBrush(m_rgbFaceNormal);
	m_brBlack.DeleteObject();
	m_brBlack.CreateSolidBrush(RGB(0,0,0));

	// Pens
	m_penShadow.DeleteObject();
	m_penShadow.CreatePen(PS_SOLID, 1, GetSysColor(COLOR_BTNSHADOW));
}

void CGXDTabBeam::OnSysColorChange()
{
	CWnd::OnSysColorChange();

	GXGetSysData()->UpdateSysColors();

	UpdateColors();

	Invalidate();

#if _MFC_VER < 0x0300
	// Also check scrollbar size
	if (GXGetAppData()->bWin4)
		OnWinIniChange(NULL);
#endif
}

void CGXDTabBeam::OnWinIniChange(LPCTSTR lpszSection)
{
	CWnd::OnWinIniChange(lpszSection);

	GXGetSysData()->UpdateSysSettings();

	int cy = GetSystemMetrics(SM_CYHSCROLL);

	if (m_nHeight != cy)
	{
		// scrollbar size did change

		m_nButtonWidth = m_nHeight = cy;
		m_nMargin = m_nScrollBtns * m_nButtonWidth;

		CreateFonts();

		for (int i = 0; i < m_nTabs; i++)
			AdjustTabSize(i);
	}

	Invalidate();
}

// Drawing helpers

void CGXDTabBeam::PatB(CDC* pDC,int x,int y,int dx,int dy, COLORREF rgb)
{
	RECT    rc;

	rc.left   = x;
	rc.top    = y;
	rc.right  = x + dx;
	rc.bottom = (y + dy);

	COLORREF rgbOld = pDC->GetBkColor();
	pDC->SetBkColor(rgb);
	pDC->ExtTextOut(0,0,ETO_OPAQUE,&rc,NULL,0,NULL);
	pDC->SetBkColor(rgbOld);
}

void CGXDTabBeam::DrawBlankButton(CDC* pDC, int x, int y, int dx, int dy, BOOL bPressed)
{
	// face color
	COLORREF rgbFace    = GXGetSysData()->GetSysColor(COLOR_BTNFACE);
	COLORREF rgbShadow  = GXGetSysData()->GetSysColor(COLOR_BTNSHADOW);
	COLORREF rgbHilite = GXGetSysData()->GetSysColor(COLOR_BTNHIGHLIGHT);
	COLORREF rgbFrame   = GXGetSysData()->GetSysColor(COLOR_WINDOWFRAME);

	x++;
	y++;
	dx--;
	dy--;

	// border around button
	PatB(pDC, x-1,    y-1,    dx+1, 1,  rgbFrame);
	PatB(pDC, x,    y+dy,   dx, 1,  rgbFrame);
	PatB(pDC, x-1,  y,      1,  dy, rgbFrame);
	PatB(pDC, x+dx, y,      1,  dy, rgbFrame);

	// interior grey
	PatB(pDC, x, y, dx, dy, rgbFace);

	if (bPressed)
	{
		// pressed in or down or down disabled
		PatB(pDC, x, y, 1, dy, rgbShadow);
		PatB(pDC, x, y, dx, 2, rgbShadow);

		PatB(pDC, x + dx - 1, y, 1, dy, rgbShadow);
		PatB(pDC, x, y + dy-1, dx, 1,   rgbShadow);
	}
	else
	{
		// regular button look
		if (GXGetAppData()->bWin4)
		{
			PatB(pDC, x+1, y+1, 1, dy - 2, rgbHilite);
			PatB(pDC, x+1, y+1, dx - 2, 1, rgbHilite);

			PatB(pDC, x + dx - 1, y+1, 1, dy-1, rgbShadow);
			PatB(pDC, x+1, y + dy-2, dx-1, 1,   rgbShadow);
		}
		else
		{
			PatB(pDC, x, y, 1, dy - 1, rgbHilite);
			PatB(pDC, x, y, dx - 1, 1, rgbHilite);

			PatB(pDC, x + dx - 1, y, 1, dy, rgbShadow);
			PatB(pDC, x, y + dy-2, dx, 1,   rgbShadow);

			PatB(pDC, x + 1 + dx - 3, y + 1, 1, dy-2, rgbShadow);
			PatB(pDC, x + 1, y + dy - 3, dx - 2, 1, rgbShadow);
		}
	}
}


IMPLEMENT_DYNCREATE(CGXDTabWnd, CWnd);

// enable use as custom control
//GRID_IMPLEMENT_REGISTER(CGXDTabWnd, CS_DBLCLKS | GX_GLOBALCLASS, 0, 0, 0);

// much of this code (e.g. CreateCommon, RecalcLayout, ...)
// is copied from the CSplitterWnd class and adapted to the tabwnd class

/////////////////////////////////////////////////////////////////////////////
// Win4 specific defines

#define CX_BORDER           1
#define CY_BORDER           1
#define IDW_TABBEAM         AFX_IDW_HSCROLL_FIRST+10
#define _GXGetDlgCtrlID(hWnd)  ((UINT)(WORD)::GetDlgCtrlID(hWnd))

/////////////////////////////////////////////////////////////////////////////
// CGXDTabWnd support for dialog validation

void AFXAPI DDV_GXTabWnd(CDataExchange* pDX, CGXDTabWnd* pTabWnd)
{
	if (pDX->m_bSaveAndValidate)
	{
		pDX->PrepareCtrl(pTabWnd->GetDlgCtrlID());

		// if deactivation is possible, OnCanActivate returns 0;
		// otherwise it returns 0
		if (pTabWnd->m_pActivePane->SendMessage(WM_GX_CANACTIVATE, 0, 0))
			pDX->Fail();
	}
}

CGXDTabWnd* GXDGetParentTabWnd(const CWnd* pWnd, BOOL bAnyState)
{
	return (CGXDTabWnd*) GXGetParentWnd(pWnd, RUNTIME_CLASS(CGXDTabWnd), bAnyState);
}

/////////////////////////////////////////////////////////////////////////////
// CGXDTabWnd

class CGXDTabWndInterface: public CGXAbstractTabWndInterface
{
public:
	virtual void UpdateTabName(const CWnd* pWnd, CString& sName, BOOL bUpdateBeam);
	virtual CString GetTabName(const CWnd* pWnd, int nTab);
};

void CGXDTabWndInterface::UpdateTabName(const CWnd* pWnd, CString& sName, BOOL bUpdateBeam)
{
	CGXDTabWnd* pTabWnd = GXDGetParentTabWnd(pWnd, TRUE);

	if (pTabWnd != NULL)
	{
		if (bUpdateBeam)
			pTabWnd->SetTabName(pWnd, sName, FALSE);
		else
			sName = pTabWnd->GetTabName(pWnd);
	}
}

CString CGXDTabWndInterface::GetTabName(const CWnd* pWnd, int nTab)
{
	CGXDTabWnd* pTabWnd = GXDGetParentTabWnd(pWnd, TRUE);

	CString s;
	if (pTabWnd != NULL)
		s = pTabWnd->GetBeam().GetTab(nTab).sLabel;

	return s;
}

//@doc CGXDTabWnd
//@mfunc Constructor
//@rdesc 
//@parm CRuntimeClass *pBeamClass
CGXDTabWnd::CGXDTabWnd(CRuntimeClass *pBeamClass)
{
#if _MFC_VER >= 0x0300 && defined(_DEBUG)
	ASSERT( pBeamClass && pBeamClass->IsDerivedFrom(RUNTIME_CLASS(CGXDTabBeam)) );
#endif

	m_pBeamClass = pBeamClass;
	m_bCtrlsCreated = FALSE;
	m_pBeam = 0;
	m_pActivePane = 0;
	m_cxBeam = 0;
	m_lxBeam = 0;
	m_cxWnd = 0;
	m_cxSplitter = 7;
	m_cxVScroll = GetSystemMetrics(SM_CXVSCROLL);
	m_cyHScroll = GetSystemMetrics(SM_CYHSCROLL);
	m_nBarWidths = m_cyHScroll + 2*GXGetAppData()->bWin4;
	m_bTracking = FALSE;
	m_hcurArrow  = ::LoadCursor(NULL, IDC_ARROW);
	m_pEditWnd = NULL;
	m_bHasHScroll = 1;
	m_bHasVScroll = 1;

	m_brErase.CreateSolidBrush(::GetSysColor(COLOR_BTNFACE));

	m_bDrawSunken = FALSE;

	// Register in grid for sharing scrollbars
	GXGetAppData()->RegisterSharedScrollBar(GetRuntimeClass());

	// Register interface for CGXGridCore
	if (GXGetAppData()->m_pTabWndInt == NULL)
		GXGetAppData()->m_pTabWndInt = new CGXDTabWndInterface;
}

//@doc CGXDTabWnd
//@mfunc Destructor.
//@rdesc 
CGXDTabWnd::~CGXDTabWnd()
{
	delete m_pBeam;
}

//@doc CGXDTabWnd
//@mfunc Call this function to access the internal tab-beam window.
//@rdesc CGXDTabBeam& A referenc to the contained tab-beam control window.
CGXDTabBeam& CGXDTabWnd::GetBeam()
{ 
	return *m_pBeam; 
}

//@doc CGXDTabWnd
//@mfunc A helper function to access the m_pActivePane member variable.
//@rdesc CWnd* Pointer to m_pActivePane. It is the active pane.
CWnd* CGXDTabWnd::GetActivePane()
{ 
	return m_pActivePane; 
}

//@doc CGXDTabWnd
//@mfunc Call this function to switch to a given tab. It is a convinent overload of SwitchTab(CWnd*).
//@rdesc void 
//@parm int nTab The index of the tab to switch to.
void CGXDTabWnd::SwitchTab(int nTab)
{
	ASSERT(nTab >= 0 && nTab <= m_pBeam->GetCount());
	SwitchTab((CWnd*) m_pBeam->GetTab(nTab).pExtra);
}

//@doc CGXDTabWnd
//@mfunc Call this function to remove the given tab and destroy the corresponding window.
//@rdesc void 
//@parm int nTab The index of the tab to be removed.
void CGXDTabWnd::RemoveTab(int nTab)
{
	ASSERT(nTab >= 0 && nTab <= m_pBeam->GetCount());
	RemoveTab((CWnd*) m_pBeam->GetTab(nTab).pExtra);
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

BOOL CGXDTabWnd::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= WS_CLIPCHILDREN;
	return CWnd::PreCreateWindow(cs);
}

//@doc CGXDTabWnd
//@mfunc Call this funtion to create this tab window. It will automatically create a new window for it's first
//tab. This runtime class of the new window must specified in the creation context structure. 
//@rdesc BOOL Return TRUE if the creation is successful, otherwise return FALSE.
//@parm CWnd* pParentWnd A pointer to the parent window.
//@parm  LPCTSTR szFirstLabel A pointer to the string for the name of the tab accociated with the new window.
//@parm  CCreateContext* pContext A pointer to creation context. It is usually the same pointer passed in from OnCreateClient method
//of CFrameWnd class. But it can be changed to any other window runtime class.
//@parm  DWORD dwStyle Style of this tab window. 
//@parm  DWORD dwExStyle Extended window style for this tab window. If the extended style contains WS_EX_CLIENTEDGE style, the
//WS_EX_CLIENTEDGE extended style will be removed.
//@parm  UINT nID The id to be used to identify this window.
BOOL CGXDTabWnd::Create(CWnd* pParentWnd, LPCTSTR szFirstLabel,	CCreateContext* pContext, DWORD dwStyle, DWORD dwExStyle, UINT nID)
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

	if (!CreateCommon(pParentWnd, dwStyle | WS_VISIBLE, dwExStyle, nID))
		return FALSE;

	CRect rect;
	pParentWnd->GetClientRect(&rect);

	MoveWindow(0, 0, rect.Width(), rect.Height(), FALSE);

	m_pDynamicViewClass = pContext->m_pNewViewClass;
		// save for later dynamic creations

	// add the first initial pane
	CWnd* pWnd = CreateView(m_pDynamicViewClass, szFirstLabel, pContext, nID);
	if (pWnd == NULL)
	{
		DestroyWindow(); // will clean up child windows
		return FALSE;
	}

	//Since our Tab window has WS_EX_CLIENTEDGE style, we need to remove this style from
	//the frame window
	if (GXGetAppData()->bWin4 && dwExStyle & WS_EX_CLIENTEDGE )
	{
		// remove the 3d style from the frame, since the view is
		//  providing it.
		// make sure to recalc the non-client area
		pParentWnd->ModifyStyleEx(WS_EX_CLIENTEDGE, 0, SWP_FRAMECHANGED);
	}


	m_bCtrlsCreated = TRUE;

	m_nFirstViewID = nID;
	m_nLastViewID = nID;
	m_pActivePane = pWnd;

	return TRUE;
}

#if _MFC_VER < 0x0300
WNDPROC* CGXDTabWnd::GetSuperWndProcAddr()
{
	// Note: it is no longer necessary to override GetSuperWndProcAddr
	//  for each control class with a different WNDCLASS.
	//  This implementation now uses instance data, such that the previous
	//  WNDPROC can be anything.

	static WNDPROC NEAR pfnSuper;
	return &pfnSuper;
}
#endif

#ifndef SIF_ALL
#define SIF_ALL 0x1F
#endif

void CGXDTabWnd::SaveScrollbarState(CWnd* pSheetWnd)
{
	// Save scrollbar state and store in CGXDTabInfo
	CGXDTabInfo* pInfo = &m_pBeam->GetTab(m_pBeam->FindTab(pSheetWnd));
#if _MFC_VER >= 0x0300
	pInfo->sbInfoVert.fMask = SIF_ALL;
	pInfo->sbInfoHorz.fMask = SIF_ALL;
	
	if (!pSheetWnd->GetScrollInfo(SB_VERT, &pInfo->sbInfoVert))
		pSheetWnd->GetScrollRange(SB_VERT, &pInfo->sbInfoVert. nMin, &pInfo->sbInfoVert.nMax);

	if (!pSheetWnd->GetScrollInfo(SB_HORZ, &pInfo->sbInfoHorz))
		pSheetWnd->GetScrollRange(SB_HORZ, &pInfo->sbInfoHorz. nMin, &pInfo->sbInfoHorz.nMax);
#else	
	pSheetWnd->GetScrollRange(SB_VERT, &pInfo->sbInfoVert. nMin, &pInfo->sbInfoVert.nMax);
	pSheetWnd->GetScrollRange(SB_HORZ, &pInfo->sbInfoHorz.nMin, &pInfo->sbInfoHorz.nMax);
#endif

	pInfo->sbInfoVert.nTrackPos = pSheetWnd->GetScrollPos(SB_VERT);
	pInfo->sbInfoHorz.nTrackPos = pSheetWnd->GetScrollPos(SB_HORZ);
}

void CGXDTabWnd::RestoreScrollbarState(CWnd* pSheetWnd)
{
	// Restore scrollbar state from CGXDTabInfo
	CGXDTabInfo* pInfo = &m_pBeam->GetTab(m_pBeam->FindTab(pSheetWnd));
	CWnd* pHScrollBar = GetDlgItem(AFX_IDW_HSCROLL_FIRST);
	CWnd* pVScrollBar = GetDlgItem(AFX_IDW_VSCROLL_FIRST);

	if (pInfo->sbInfoVert.nMax)
	{
#if _MFC_VER >= 0x0300
		if (pVScrollBar)
			pVScrollBar->EnableScrollBar(TRUE);

		pInfo->sbInfoVert.fMask = SIF_ALL | SIF_DISABLENOSCROLL;

		if (!pSheetWnd->SetScrollInfo(SB_VERT, &pInfo->sbInfoVert))
#endif
			pSheetWnd->SetScrollRange(SB_VERT, pInfo->sbInfoVert.nMin, pInfo->sbInfoVert.nMax);
		pSheetWnd->SetScrollPos(SB_VERT, pInfo->sbInfoVert.nTrackPos);
	}
	else
		if (pVScrollBar)
			pVScrollBar->EnableScrollBar(FALSE);

	if (pInfo->sbInfoHorz.nMax)
	{
#if _MFC_VER >= 0x0300
		if (pHScrollBar)
			pHScrollBar->EnableScrollBar(TRUE);

		pInfo->sbInfoHorz.fMask = SIF_ALL | SIF_DISABLENOSCROLL;

		if (!pSheetWnd->SetScrollInfo(SB_HORZ, &pInfo->sbInfoHorz))
#endif
			pSheetWnd->SetScrollRange(SB_HORZ, pInfo->sbInfoHorz.nMin, pInfo->sbInfoHorz.nMax);
		pSheetWnd->SetScrollPos(SB_HORZ, pInfo->sbInfoHorz.nTrackPos);
	}
	else
		if (pHScrollBar)
			pHScrollBar->EnableScrollBar(FALSE);

#if 0
#if _MFC_VER >= 0x0300
		if( GXGetAppData()->bWin4 && GetParent()->IsFrameWnd() )
		{
			CWnd* pSizeBox = GetDlgItem(GX_IDW_SIZE_BOX);
			if( pSizeBox )
			{
				if(pVScrollBar && pHScrollBar)
				{
					CRect rectInside;
					GetInsideRect(rectInside);
					CRect rectClient;
					GetClientRect(rectClient);
					CRect rect(rectInside.right - ::GetSystemMetrics(SM_CXVSCROLL), //left
							rectClient.bottom - m_nBarWidths, //top
							rectInside.right, //right
							rectClient.bottom); //bottom
					pSizeBox->MoveWindow(rect);
					pSizeBox->EnableWindow(FALSE);
					pSizeBox->ShowWindow(SW_SHOW);
				}
				else
				{
					pSizeBox->ShowWindow(SW_HIDE);
				}
			}
		}
#endif
#endif
}

//@doc CGXDTabWnd
//@mfunc A helper function called by Create method to create the window, the tab-beam window and scrollbars. 
//Both vertical and horizontal scrollbars are always created even the style doesn't contain WS_HSCROLL and WS_VSCROLL
//style bits.
//@rdesc BOOL Return TRUE if everything successfully, created, otherwise return FALSE.
//@parm CWnd* pParentWnd A pointer to the parent window.
//@parm  DWORD dwStyle specify the style for this tab window.
//@parm  DWORD dwExStyle Specify the extended style for this tab window.
//@parm  UINT nID The id to be used to identify this tab window.
BOOL CGXDTabWnd::CreateCommon(CWnd* pParentWnd, DWORD dwStyle, DWORD dwExStyle, UINT nID)
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
		if (!CreateEx(dwExStyle, _T("GxMdiFrame"), NULL, dwStyle, 0, 0, 0, 0,
			pParentWnd->GetSafeHwnd(), (HMENU)(SEC_DWORD)nID, NULL))
		{
			ASSERT(0);
			// ASSERTION-> Window could not be created.
			// Did you call GXInit() in you InitInstance method? ->END

			return FALSE;       // create invisible
		}
	}

	// attach the initial scrollbar parts
	TRY
	{
		// Scrollbars are always created even if m_bHasHScroll or 
		// m_bHasVScroll is FALSE.
		// If any of these flags is FALSE, the associated scrollbar
		// will be hidden.

		if (!CreateScrollBarCtrl(SBS_HORZ, AFX_IDW_HSCROLL_FIRST))
				AfxThrowResourceException();

		if (!m_bHasHScroll)
		{
			CWnd* pScrollBar = GetDlgItem(AFX_IDW_HSCROLL_FIRST);
			pScrollBar->ShowWindow(SW_HIDE);
		}

		if (!CreateScrollBarCtrl(SBS_VERT, AFX_IDW_VSCROLL_FIRST))
				AfxThrowResourceException();

		if (!m_bHasVScroll)
		{
			CWnd* pScrollBar = GetDlgItem(AFX_IDW_VSCROLL_FIRST);
			pScrollBar->ShowWindow(SW_HIDE);
		}
#if 0 //????
#if _MFC_VER >= 0x0300
		if (GXGetAppData()->bWin4 /*&& (m_bHasHScroll || m_bHasVScroll)*/ && GetParent()->IsFrameWnd())
		{
			if (!CreateScrollBarCtrl(SBS_SIZEBOX, GX_IDW_SIZE_BOX))
					AfxThrowResourceException();
			GetDlgItem(GX_IDW_SIZE_BOX)->EnableWindow(FALSE);
			if( !m_bHasVScroll || !m_bHasHScroll )
				GetDlgItem(GX_IDW_SIZE_BOX)->ShowWindow(SW_HIDE);
		}
#endif
#endif //0
		if (m_pBeam == NULL)
		{
			m_pBeam = (CGXDTabBeam*) m_pBeamClass->CreateObject();
			VERIFY(m_pBeam->Create(WS_VISIBLE, CRect(0, 0, 1, 1), this, IDW_TABBEAM));
		}

	}
	CATCH_ALL(e)
	{
		DestroyWindow(); // will clean up child windows
		return FALSE;
	}
	END_CATCH_ALL


	m_bCtrlsCreated = TRUE;

	return TRUE;
}

//@doc CGXDTabWnd
//@mfunc A helper function to create scrollbar control.
//@rdesc BOOL Return TRUE if the creation is successful, otherwise return FALSE.
//@parm DWORD dwStyle The style for the scrollbar.
//@parm  UINT nID The id of the scrollbar.
BOOL CGXDTabWnd::CreateScrollBarCtrl(DWORD dwStyle, UINT nID)
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

//@doc CGXDTabWnd
//@mfunc Call this function to reposition the scrollbars and the splitter window.
//@rdesc void 
//@parm BOOL bTracking If FALSE, the splitter window is also repositioned.
void CGXDTabWnd::RecalcLayout(BOOL bTracking)
{
	ASSERT_VALID(this);

	if (!m_bCtrlsCreated)
	{
		// TRACE0("RecalcLayout() is creating controls\n");
		VERIFY(CreateCommon(GetParent(), WS_CHILD | WS_HSCROLL | WS_VSCROLL, WS_EX_CLIENTEDGE, _GXGetDlgCtrlID(m_hWnd)));
		m_nLastViewID = m_nFirstViewID = AFX_IDW_PANE_FIRST;
		m_bCtrlsCreated = TRUE;
	}

	CRect rectInside;
	GetInsideRect(rectInside);

	CRect rectClient;
	GetClientRect(rectClient);

	// adjust the panes and scroll bars

	// is beam size already initialized?
	if (m_lxBeam == 0)
	{
		m_lxBeam = rectClient.right/2*100L;
		m_cxBeam = (int) (m_lxBeam/100);
		m_cxWnd = rectClient.right;
	}

	// give the hint for the maximum number of HWNDs
	HDWP hDWP = NULL;
	if(GetDlgItem(AFX_IDW_HSCROLL_FIRST+1) == NULL)
		hDWP = ::BeginDeferWindowPos(5);
	else
		hDWP = ::BeginDeferWindowPos(6);

	// size of scrollbars
	int cx = (rectClient.right - rectInside.right) - 2*GXGetAppData()->bWin4;
	int cy = (rectClient.bottom - rectInside.bottom) - 2*GXGetAppData()->bWin4;

	//-= ::GetSystemMetrics(SM_CXVSCROLL);	

	int nMulFact = 1;
	
	BOOL bTakeFullArea(FALSE);

	if(GetActivePane() && GetActivePane()->IsKindOf(RUNTIME_CLASS(CGXDSplitWnd)))
	{
		BOOL  bPane = FALSE;
		
		bPane = (((CGXDSplitWnd*)GetActivePane())->m_nCols) - 1;

		if(bPane)
			nMulFact = 1;
		else
			nMulFact = 2;
	}
	else
	{
		bTakeFullArea = TRUE;
		if(GetDlgItem(AFX_IDW_HSCROLL_FIRST+1) != NULL)	
			GetDlgItem(AFX_IDW_HSCROLL_FIRST+1)->MoveWindow0(FALSE);
	}

	//change 
	if(GetDlgItem(AFX_IDW_HSCROLL_FIRST+1) == NULL || bTakeFullArea)
	{
		int ySB = rectInside.bottom + CY_BORDER;
		CWnd* pScrollBar = GetDlgItem(AFX_IDW_HSCROLL_FIRST);
		ASSERT(pScrollBar != NULL);

		CWnd* pWnd = GetActivePane();
		BOOL bVScrollPresent = FALSE;

		//If the active pane is our splitter window, we are using the vertical scroll
		//bar of our splitter window, so we need to reserve room for this scroll bar.
		if( pWnd && pWnd->IsKindOf(RUNTIME_CLASS(CGXDSplitWnd)) )
			bVScrollPresent = ((CGXDSplitWnd*)GetActivePane())->GetDlgItem(AFX_IDW_VSCROLL_FIRST)->IsWindowVisible();

		if (m_bHasHScroll)
		{
			if( m_cxBeam >= rectInside.right - min(rectInside.right/4, 45) )
				m_cxBeam = rectInside.right - min(rectInside.right/4, 45);

			int cx = rectInside.right - m_cxBeam - nMulFact * m_cxSplitter - (bVScrollPresent ? ::GetSystemMetrics(SM_CXVSCROLL) : 0);
			
			hDWP = DeferClientPos(hDWP, pScrollBar, m_cxBeam + m_cxSplitter + 1, ySB, cx - 1, cy, TRUE);
		}
		else
			hDWP = DeferClientPos(hDWP, pScrollBar, rectClient.right, ySB,	0, cy, TRUE);
	}
	else	//share between two scrollbars
	{		
		int cxCol;
		int cyCol;

		CGXDSplitWnd* pSplitter = (CGXDSplitWnd*)GetActivePane();
		ASSERT(pSplitter);

		pSplitter->GetColumnInfo(1,cxCol,cyCol);
		
		BOOL bVScrollPresent = pSplitter->GetDlgItem(AFX_IDW_VSCROLL_FIRST)->IsWindowVisible();
		
		//bar1
		int ySB = rectInside.bottom + CY_BORDER;
		CWnd* pScrollBar = GetDlgItem(AFX_IDW_HSCROLL_FIRST);
		ASSERT(pScrollBar != NULL);
		if (m_bHasHScroll)
		{
			if(!bTakeFullArea)
			{
				int cxCol2, cyCol2;
				pSplitter->GetColumnInfo(0, cxCol2, cyCol2);

				int xBar = 0;
				int nWidth;
				if( cxCol2 <= 4 * m_cxSplitter )
				{
					// No need to draw Beam and splitter
					m_cxBeam = 0; 
					xBar = 1;
					nWidth = cxCol2 - 1;
				}
				else
				{
					// If m_cxBeam is too close to the splitter bar, adjust the
					// m_cxBream position so that we can always see the scroll bar!!!
					if( m_cxBeam >= cxCol2 - min(cxCol2/4, 25)) 
						m_cxBeam = cxCol2 - min(cxCol2/4, 25);
					xBar = m_cxBeam + m_cxSplitter + 1;
					nWidth = cxCol2 - xBar + 2;
				}
				hDWP = DeferClientPos(hDWP, pScrollBar, xBar, ySB, nWidth + m_cxSplitter/2, cy, TRUE);
			}
			else
			{
				int cx = rectInside.right - m_cxBeam - m_cxSplitter - (bVScrollPresent ? ::GetSystemMetrics(SM_CXVSCROLL) : 0);
				hDWP = DeferClientPos(hDWP, pScrollBar, m_cxBeam + m_cxSplitter + 1, ySB, cx - 1, cy, TRUE);
			}
		}
		else
			hDWP = DeferClientPos(hDWP, pScrollBar, rectClient.right, ySB, 0, cy, TRUE);
	
		//bar2
		if(!bTakeFullArea)
		{
			ySB = rectInside.bottom + CY_BORDER;
			pScrollBar = GetDlgItem(AFX_IDW_HSCROLL_FIRST+1);
			ASSERT(pScrollBar != NULL);
			if (m_bHasHScroll)
			{
				int xBar = rectInside.right - cxCol - m_cxSplitter/2 - 1 - (bVScrollPresent ? ::GetSystemMetrics(SM_CXVSCROLL) : 0 );
				hDWP = DeferClientPos(hDWP, pScrollBar, xBar, ySB, cxCol + m_cxSplitter/2, cy, TRUE);
			}
			else
				hDWP = DeferClientPos(hDWP, pScrollBar, rectClient.right, ySB, 0, cy, TRUE);
		}
	}


	// reposition scroll bars
	if (!bTracking && m_bHasVScroll)
	{
		int xSB = rectInside.right + CX_BORDER;
		CWnd* pScrollBar = GetDlgItem(AFX_IDW_VSCROLL_FIRST);
		ASSERT(pScrollBar != NULL);
		int cy = rectInside.bottom;
		hDWP = DeferClientPos(hDWP, pScrollBar, xSB, 0,	cx, cy, TRUE);
	}

#if 0
#if _MFC_VER >= 0x0300
	// reposition size box
	if (GXGetAppData()->bWin4 && GetParent()->IsFrameWnd())
	{
		CWnd* pScrollBar = GetDlgItem(GX_IDW_SIZE_BOX);
		ASSERT(pScrollBar != NULL);

		int xSB = rectInside.right + 2*CX_BORDER;
		int ySB = rectInside.bottom + 2*CY_BORDER;

		BOOL bVScrollPresent;
		CWnd* pWnd = GetActivePane();
		if( pWnd && pWnd->IsKindOf(RUNTIME_CLASS(CGXDSplitWnd)) )
			bVScrollPresent = ((CGXDSplitWnd*)GetActivePane())->GetDlgItem(AFX_IDW_VSCROLL_FIRST)->IsWindowVisible();
		else
			bVScrollPresent = GetDlgItem(AFX_IDW_VSCROLL_FIRST)->IsWindowVisible();
		BOOL bHScrollPresent = GetDlgItem(AFX_IDW_HSCROLL_FIRST)->IsWindowVisible();
		if( bHScrollPresent && bVScrollPresent )
		{
			// fix style if necessary
/*			BOOL bSizingParent = (GetSizingParent(this) != NULL);
			// modifyStyle returns TRUE if style changes
			if (pScrollBar->ModifyStyle(SBS_SIZEGRIP|SBS_SIZEBOX,
					bSizingParent ? SBS_SIZEGRIP : SBS_SIZEBOX))
				pScrollBar->Invalidate();
			pScrollBar->EnableWindow(bSizingParent);
	*/
			// reposition the size box
			hDWP = DeferClientPos(hDWP, pScrollBar,	xSB, ySB, cx, cy, TRUE);		
		}
		else
		{
//			pScrollBar->ShowWindow(SW_HIDE);

			hDWP = DeferClientPos(hDWP, pScrollBar,	xSB, ySB, 0, 0, TRUE);
		}
	}
#endif
#endif //0

	// repositon tab beam
	{
		int ySB = rectInside.bottom + CY_BORDER;
		CWnd* pBeam = GetDlgItem(IDW_TABBEAM);
		ASSERT(pBeam != NULL);

		int cx = m_bHasHScroll?m_cxBeam:rectClient.right;
		hDWP = DeferClientPos(hDWP, pBeam, 0, ySB,	cx, cy, FALSE);
	}


	if (!bTracking)
	{
		int x = 1;
		int y = 1;
		int cy = rectInside.Height() - CY_BORDER - 1;
		int cx = rectInside.Width() - CX_BORDER - 1;
		CWnd* pPane = m_pActivePane;
		if (pPane /*&& !pPane->IsKindOf(RUNTIME_CLASS(CGXDSplitWnd))*/)
		{
			hDWP = DeferClientPos(hDWP, pPane, x, y, cx, cy, FALSE);

			// send a WM_SIZE message to the active pane, so that
			// scrollbars will be displayed correctly
			pPane->SendMessage(WM_SIZE, SIZE_MAXIMIZED, MAKELONG(cx-x, cy-y));
			
			if(pPane->IsKindOf(RUNTIME_CLASS(CGXDSplitWnd)))
				((CGXDSplitWnd*)pPane)->RecalcLayout();
		}
	}

	::EndDeferWindowPos(hDWP);
}

//@doc CGXDTabWnd
//@mfunc A helper function to manager the hide and show for the scrollbars.
//@rdesc void 
//@parm UINT nBar A value indicating which scroll bar to show or to hide. The possible values are:<nl>
//SB_BOTH Both vertical and horizontal scroll bars.<nl>
//SB_VERT Vertical scrollbar.<nl>
//SB_HORZ Horizontal scrollbars.<nl>
//@parm  BOOL bShow If TRUE, the indicated scrollbars are shown, otherwiser they are hidden.
void CGXDTabWnd::ShowScrollBar(UINT nBar, BOOL bShow)
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
	if (GXGetAppData()->bWin4 && (pScrollBar = GetDlgItem(GX_IDW_SIZE_BOX)) != NULL /*&& GetParent()->IsFrameWnd()*/)
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

// like GetClientRect but inset by shared scrollbars
//@doc CGXDTabWnd
//@mfunc This function gets the client rectangle and subtracts the area used
//by scrollbars.
//@rdesc void 
//@parm CRect& rect A reference to accept the inside rectangle.
void CGXDTabWnd::GetInsideRect(CRect& rect) const
{
	ASSERT_VALID(this);

	GetClientRect(rect);
	ASSERT(rect.left == 0 && rect.top == 0);

	// subtract scrollbar clearance

	rect.bottom -= m_nBarWidths - CX_BORDER - GXGetAppData()->bWin4;

	// note:  vertical's width is same as beam's height
	if (m_bHasVScroll)
		rect.right -= m_nBarWidths - CY_BORDER - GXGetAppData()->bWin4;
	
	rect.top-=1;
}

//@doc CGXDTabWnd
//@mfunc Call this function to create a new window to this tab window. The other method to add a window
//to this tab window is using AttachWnd method. Even though this methods is called CreateView, the window
//is not required to be CView derived.
//@rdesc CWnd* A pointer to the new added window. If the creation is not successful, it will be NULL.
//@parm CRuntimeClass* pViewClass A pointer to the runtime class of the window to be created.
//@parm  LPCTSTR szLabel A pointer to the string used as the name for the tab accocisted with this new window.
//@parm  CCreateContext* pContext A pointer to the creation context.
//@parm  UINT nID The id to be used to identify this new window.
CWnd* CGXDTabWnd::CreateView(CRuntimeClass* pViewClass, LPCTSTR szLabel, CCreateContext* pContext, UINT nID)
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
		return pWnd;
	}
	END_CATCH_ALL

	ASSERT(pWnd->IsKindOf(RUNTIME_CLASS(CWnd)));
	ASSERT(pWnd->GetSafeHwnd() == NULL);       // not yet created

	// Create with the right size (wrong position)
	CRect rect;
	GetInsideRect(rect);

	DWORD dwStyle = AFX_WS_DEFAULT_VIEW & ~WS_BORDER;

	dwStyle = dwStyle & ~WS_VSCROLL;
	dwStyle = dwStyle & ~WS_HSCROLL;

	if (m_pBeam->m_nTabs > 0)
		dwStyle &= ~WS_VISIBLE;

	if (!pWnd->Create(NULL, NULL, dwStyle,
		rect, this, nID, pContext))
	{
		TRACE0("Warning: couldn't create client pane for splitter\n");
			// pWnd will be cleaned up by PostNcDestroy
		return NULL;
	}

	//We always want the child view window to have WS_EX_CLIENTEDGE style
//	if( GetExStyle() & WS_EX_CLIENTEDGE)
		pWnd->ModifyStyleEx(0, WS_EX_CLIENTEDGE);

	// send initial notification message
	HMENU hMenu = 0;
	if (pContext->m_pNewDocTemplate && pContext->m_pNewDocTemplate->IsKindOf(RUNTIME_CLASS(CMultiDocTemplate)))
		hMenu = ((CMultiDocTemplate*) pContext->m_pNewDocTemplate)->m_hMenuShared;

	m_pBeam->InsertTab(FALSE, szLabel, pWnd, FALSE, -1, hMenu);

	if (bSendInitialUpdate)
		pWnd->SendMessage(0x0364);

	// force a WM_SIZE
	pWnd->GetClientRect(rect);
	pWnd->MoveWindow(rect);

	SaveScrollbarState(pWnd);

	return pWnd;
}

UINT CGXDTabWnd::GetNextID()
{
	return ++m_nLastViewID;
}

//@doc CGXDTabWnd
//@mfunc Call this functin to add a new window to this tab window. There are two methods
//to add a new window to the tab window. The easiest method is to call CreateView of this 
//class, the other is use this method. This message allows you to add a new tab window in
//two step, i.e. first create the window and do some setting and then add the window to 
//this tab window.
//@rdesc CWnd*  A pointer to the same as the passed window. 
//@parm CWnd* pWnd A pointer to the window to be attached to this tab window.
//@parm  LPCTSTR szLabel A pointer to a string used as the name in the tab for this window.
CWnd* CGXDTabWnd::AttachWnd(CWnd* pWnd, LPCTSTR szLabel)
{
	ASSERT(pWnd->IsKindOf(RUNTIME_CLASS(CWnd)));
	ASSERT(pWnd->GetSafeHwnd() != NULL);       // must be created

	if (!m_bCtrlsCreated)
		RecalcLayout();

	// Create with the right size (wrong position)
	CRect rect;
	GetInsideRect(rect);
	pWnd->MoveWindow(rect);

	m_pBeam->InsertTab(FALSE, szLabel, pWnd, FALSE);

	pWnd->ShowScrollBar(SB_BOTH, FALSE);

	if (m_pActivePane == NULL)
	{
		m_pActivePane = pWnd;
		pWnd->ShowWindow(SW_SHOW);
		pWnd->SetActiveWindow();
	}

	pWnd->SendMessage(WM_GX_INITTAB, m_pBeam->FindTab(pWnd));

	SaveScrollbarState(pWnd);

	return pWnd;
}


BEGIN_MESSAGE_MAP(CGXDTabWnd, CWnd)
	//{{AFX_MSG_MAP(CGXDTabWnd)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_MESSAGE(WM_GX_TABSWITCH, OnTabSwitch)
	ON_MESSAGE(WM_GX_CANTABSWITCH, OnCanTabSwitch)
	ON_MESSAGE(WM_GX_TABDBLCLK, OnTabDblClk)
	ON_MESSAGE(WM_GX_EDITCANCEL, OnEditCancel)
	ON_MESSAGE(WM_GX_EDITEND, OnEditEnd)
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	ON_WM_SETFOCUS()
	ON_WM_ERASEBKGND()
	ON_WM_NCPAINT()
	ON_WM_SYSCOLORCHANGE()
	ON_WM_WININICHANGE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGXDTabWnd operations

//@doc CGXDTabWnd
//@mfunc Call this function to switch to a new tab.
//@rdesc void 
//@parm CWnd* pWnd A pointer to the window to switch to. The window must be associated with one of the tabs.
void CGXDTabWnd::SwitchTab(CWnd* pWnd)
{
	int nNewTab = m_pBeam->FindTab(pWnd);

	// save scrollbar state and hide window
	if (m_pActivePane)
	{
		// check first if switching to the other sheet is possible
		if (OnCanTabSwitch((WPARAM) nNewTab, 0) == 1)
			return;

		SaveScrollbarState(m_pActivePane);
		m_pActivePane->ShowWindow(SW_HIDE);
	}

	// Update status beam
	m_pBeam->ScrollTabInView(nNewTab);
	if (m_pBeam->m_nCurrent != nNewTab)
	{
		m_pBeam->m_nCurrent = nNewTab;
		m_pBeam->Invalidate(FALSE);
	}
	m_pBeam->UpdateWindow();

	// Select new pane
	m_pActivePane = pWnd;
	pWnd->SetActiveWindow();
	m_pActivePane->ShowWindow(SW_SHOW);
	m_pActivePane->SetFocus();

	//If the active pane is our splitter window, we need to hide
	//our vertical scroll bar, the splitter window already has 
	//vertical scrollbar
	if( m_pActivePane && m_pActivePane->IsKindOf(RUNTIME_CLASS(CGXDSplitWnd)) )
		ShowScrollBar(SBS_VERT, FALSE);
	else 
		ShowScrollBar(SBS_VERT, TRUE);

	// Update menu bar
	if (pWnd->IsKindOf(RUNTIME_CLASS(CView)))
	{
		GetParentFrame()->SetActiveView((CView*) pWnd);
		((CFrameWnd*) AfxGetMainWnd())->DelayUpdateFrameMenu(NULL);
	}

	// Restore scrollbar state
	RestoreScrollbarState(pWnd);

	// force a WM_SIZE message
	CRect rect;
	m_pActivePane->GetClientRect(rect);
	m_pActivePane->Invalidate();
	m_pActivePane->MoveWindow(rect);

	RecalcLayout();
}

//@doc CGXDTabWnd
//@mfunc Call this function to remove the window tab. The window will also be destroyed.
//@rdesc void 
//@parm CWnd* pWnd A pointer to the window it's tab is to be removed. The window must be accocistated with 
//one of the tabs.
void CGXDTabWnd::RemoveTab(CWnd* pWnd)
{
	// verify parameters
	CGXDTabBeam* pBeam = &GetBeam();
	int nTabCount = pBeam->GetCount();
	int nTabToDelete = m_pBeam->FindTab(pWnd);

	if (!(nTabCount > 1 && nTabToDelete < nTabCount))
	{
		TRACE0("Warning: invalid call to CGXDTabWnd::RemoveTab\n");
		return;
	}

	int nCurSel = min(pBeam->GetCurSel(), pBeam->GetCount()-2);
	int nFirstTab = min(pBeam->m_nFirstTab, nCurSel);

	// destroy window
	//CGXDTabInfo* pInfo = &
	pBeam->GetTab(nTabToDelete);
	pWnd->DestroyWindow();
	pBeam->DeleteTab(nTabToDelete);

	// switch to (or reactivate) current pane
	m_pActivePane = NULL;
	pBeam->m_nFirstTab = nFirstTab;
	SwitchTab(nCurSel);
}

//@doc CGXDTabWnd
//@mfunc An overload version of GetTabName.
//@rdesc LPCTSTR The string name of the given sheet window.
//@parm int nTab The index of the tab to find name for.
LPCTSTR CGXDTabWnd::GetTabName(int nTab)
{
	ASSERT(nTab >= 0 && nTab < GetBeam().GetCount());
	return GetBeam().GetTab(nTab).sLabel;
}

//@doc CGXDTabWnd
//@mfunc Find the tab name for the given sheet window.
//@rdesc LPCTSTR The string name of the given sheet window.
//@parm const CWnd* pSheet A pointer to the window it's name is reqested.
LPCTSTR CGXDTabWnd::GetTabName(const CWnd* pSheet)
{
	int nTab = GetBeam().FindTab(pSheet);
	if (nTab != -1)
		return GetBeam().GetTab(nTab).sLabel;

	return NULL;
}

//@doc CGXDTabWnd
//@mfunc Set a new name for the given tab window
//@rdesc void 
//@parm int nTab This index of the tab to change name.
//@parm  LPCTSTR s A string name for the tab.
//@parm  BOOL bNotifySheet If TRUE, it will send WM_GX_CHANGEDTAB message to this CGXDTabWnd window.
void CGXDTabWnd::SetTabName(int nTab, LPCTSTR s, BOOL bNotifySheet)
{
	ASSERT(nTab >= 0 && nTab < GetBeam().GetCount());
	GetBeam().GetTab(nTab).sLabel = s;
	GetBeam().AdjustTabSize(nTab);
	GetBeam().Invalidate();
	if (bNotifySheet)
		SendMessage(WM_GX_CHANGEDTAB, nTab);
}

//@doc CGXDTabWnd
//@mfunc Set a new name for the given tab window.
//@rdesc void 
//@parm const CWnd* pSheet A pointer to the window.
//@parm  LPCTSTR s New string name for the window.
//@parm  BOOL bNotifySheet If TRUE, it will send a WM_GX_CHANGEDTAB message to this CGXDTabWnd window.
void CGXDTabWnd::SetTabName(const CWnd* pSheet, LPCTSTR s, BOOL bNotifySheet)
{
	int nTab = GetBeam().FindTab(pSheet);
	ASSERT(nTab != -1);
	if (nTab != -1)
		SetTabName(nTab, s, bNotifySheet);
}

/////////////////////////////////////////////////////////////////////////////
// CGXDTabWnd message handlers

//@doc CGXDTabWnd
//@mfunc A custom message WM_GX_TABSWITCCH handler.
//@rdesc LRESULT Return 0.
//@parm WPARAM wParam Contains the index to the tab to switch to.
//@parm  LPARAM  Not used.
LRESULT CGXDTabWnd::OnTabSwitch(WPARAM wParam, LPARAM )
{
	// TRACE(_T("OnTabSwitch(%d)\n"), wParam);
	CGXDTabInfo& pInfo = m_pBeam->GetTab((int)wParam);

	if ((CWnd*) pInfo.pExtra == m_pActivePane)
	{
		MSG msg;
		// Is a double-click pending?
		if (PeekMessage(&msg, m_hWnd, WM_GX_TABDBLCLK, WM_GX_TABDBLCLK, PM_NOREMOVE))
			return 0;

		if (m_pActivePane->IsKindOf(RUNTIME_CLASS(CView)))
			GetParentFrame()->SetActiveView((CView*) m_pActivePane);
		m_pActivePane->SetFocus();
		m_pActivePane->Invalidate();
	}
	else
		SwitchTab((CWnd*) pInfo.pExtra);

	return 0;
}

//@doc CGXDTabWnd
//@mfunc A custom message WM_GX_CANTABSWITCH handler. 
//@rdesc LRESULT Return FALSE if switch tab is allowed, otherwise return TRUE.
//@parm WPARAM wParam Contains the index of the tab to switch to.
//@parm  LPARAM Not used.
LRESULT CGXDTabWnd::OnCanTabSwitch(WPARAM wParam, LPARAM )
{
	// TRACE(_T("OnTabSwitch(%d)\n"), wParam);
	CGXDTabInfo& pNewInfo = m_pBeam->GetTab((int)wParam);
	CWnd* pNewWnd = (CWnd*) pNewInfo.pExtra;

	if (pNewWnd == m_pActivePane)
		return 0;   // 0 means that switching to current pane is allowed
	else
	{
		// switch to different pane

		// 1st, check if I can deactive current pane
		// Next, check if I can active new pane

		// OnCanActivate returns 1, if activation is disabled
		if (m_pActivePane->SendMessage(WM_GX_CANACTIVATE, 0, 0)
			|| pNewWnd->SendMessage(WM_GX_CANACTIVATE, 1, 0))
		{
			m_pActivePane->SetFocus();
			return 1;
		}
	}

	return 0;   // switching is allowed

	// Please note:
	// switching is allowed when return value is 0
	// switching is disabled when return value is 1
}

//@doc CGXDTabWnd
//@mfunc A custom message WM_GX_TABDBLCLK handler.
//@rdesc LRESULT Return 0.
//@parm WPARAM wParam Contains the index to the tab been clicked on.
//@parm  LPARAM Not used.
LRESULT CGXDTabWnd::OnTabDblClk(WPARAM wParam, LPARAM )
{
	// TRACE(_T("OnTabDlbClk(%d)\n"), wParam);
	CGXDTabInfo& pInfo = m_pBeam->GetTab((int)wParam);
	CWnd* pWnd = (CWnd*) pInfo.pExtra;

	if (m_pEditWnd)
		return 0;

	if (pWnd->SendMessage(WM_GX_NEEDCHANGETAB, wParam, 0) == FALSE)
		return 0;

	CString s = pInfo.sLabel;

	int x = m_pBeam->CalcTabOffset((int)wParam);
	CRect rectInside;
	GetInsideRect(rectInside);

	CClientDC dc(this);
	CFont* pOldFont = dc.SelectObject(m_pBeam->m_pFontNormal);
	CSize size = dc.GetTextExtent(_T("W"), 1);
	dc.SelectObject(pOldFont);
	size.cx = size.cx*15;

	int nBorder = GetSystemMetrics(SM_CYDLGFRAME);

	CRect rect;
	rect.left = x;
	rect.top = max(rectInside.bottom-2*size.cy-2*nBorder, 0);
	rect.right = x+size.cx,
	rect.bottom = rect.top+size.cy+4*nBorder;

	if (rect.right > rectInside.right)
	{
		rect.left = max(0, rectInside.right - size.cx);
		rect.right = rectInside.right;
	}

	if (rect.left < 0)
	{
		rect.right = min(size.cx, rectInside.right);
		rect.left = 0;
	}

	UpdateWindow();

	m_pEditWnd = new CGXDEditLabelPopup(rect, this, ID_GX_EDITWND);
	m_pEditWnd->SetWindowText(s);
	m_pEditWnd->SetFont(m_pBeam->m_pFontNormal);
	m_pEditWnd->SetFocus();

	return 0;
}

//@doc CGXDTabWnd
//@mfunc A custom message WM_GX_EDITEND handler. 
//@rdesc LRESULT Return 0.
//@parm WPARAM Not used.
//@parm  LPARAM Not used.
LRESULT CGXDTabWnd::OnEditEnd(WPARAM , LPARAM )
{
	CString s;

	m_pEditWnd->GetWindowText(s);
	m_pEditWnd->DestroyWindow();
	delete m_pEditWnd;
	m_pEditWnd = NULL;

	m_pBeam->GetTab(m_pBeam->m_nCurrent).sLabel = s;
	m_pBeam->AdjustTabSize(m_pBeam->m_nCurrent);

	CGXDTabInfo& pInfo = m_pBeam->GetTab(m_pBeam->m_nCurrent);
	CWnd* pWnd = (CWnd*) pInfo.pExtra;

	pWnd->SendMessage(WM_GX_CHANGEDTAB, m_pBeam->m_nCurrent, 0);

	return 0;
}

//@doc CGXDTabWnd
//@mfunc A custom message WM_GX_EDITCANCEL handler. It destories the internal edit control
//window.
//@rdesc LRESULT Return 0.
//@parm WPARAM  Not used.
//@parm  LPARAM  Not used.
LRESULT CGXDTabWnd::OnEditCancel(WPARAM , LPARAM )
{
	if (m_pEditWnd)
	{
		m_pEditWnd->DestroyWindow();
		delete m_pEditWnd;
		m_pEditWnd = NULL;
	}

	return 0;
}

//@doc CGXDTabWnd
//@mfunc WM_PAINT message handler. 
//@rdesc void 
void CGXDTabWnd::OnPaint()
{
	ASSERT_VALID(this);

	if (!m_bCtrlsCreated)
		RecalcLayout();

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
		CRect rect(m_cxBeam /*+ CX_BORDER*/,
			rectInside.bottom,
			m_cxBeam+m_cxSplitter,
			rectClient.bottom);

		OnDrawSplitter(&dc, rect);
	}

	if (m_bHasHScroll && GetActivePane() && GetActivePane()->IsKindOf(RUNTIME_CLASS(CGXDSplitWnd)))
	{
		if( ((CGXDSplitWnd*)GetActivePane())->GetColumnCount() == 1 )
		{
			CRect rect(rectInside.right - m_cxSplitter - ::GetSystemMetrics(SM_CXVSCROLL),
					   rectInside.bottom,
					   rectInside.right - ::GetSystemMetrics(SM_CXVSCROLL),
					   rectClient.bottom);
			OnDrawSplitter(&dc, rect);
		}
	}

	// Do not call CWnd::OnPaint() for painting messages
}

//@doc CGXDTabWnd
//@mfunc WM_SIZE message handler.
//@rdesc void 
//@parm UINT nType
//@parm  int cx
//@parm  int cy
void CGXDTabWnd::OnSize(UINT nType, int cx, int cy)
{
	// ensure that edit popup is not visible
	OnEditCancel(0, 0);

	CWnd* pPane = m_pActivePane;
	if (pPane)
		pPane->SendMessage(WM_GX_LOCKRESIZE, GX_STARTRESIZE, 0);


	if (nType != SIZE_MINIMIZED && cx > 0 && cy > 0 && cx < 32767 && cy < 32767)
	{
		// Adapt m_lxBeam, if m_cxBeam has been changed
		if ((int) (m_lxBeam/100) != m_cxBeam)
			m_lxBeam = (LONG) m_cxBeam*100;

		if (m_bHasHScroll)
		{

			if (m_pBeam && m_cxWnd != 0 && m_lxBeam != 0)
			{
				LONG x = (m_pBeam->m_nMargin-20)*100L;
				m_lxBeam = (m_lxBeam-x)*(cx)/(m_cxWnd)+x;
			}
			else if (m_lxBeam == 0)
				m_lxBeam = cx/2*100L;
		}
		else
			m_lxBeam = cx*100L;

		m_cxBeam = (int) (m_lxBeam/100);

		RecalcLayout();
	}

	CWnd::OnSize(nType, cx, cy);

	if (pPane)
	{
		pPane->SendMessage(WM_GX_LOCKRESIZE, GX_ENDRESIZE, 0);
		CRect r;
		m_pActivePane->GetClientRect(r);
		pPane->SendMessage(WM_SIZE, nType, MAKELONG(r.Width(), r.Height()));

		RecalcLayout(); //We need to do this again !!!
	}

	UpdateWindow();
}

//@doc CGXDTabWnd
//@mfunc WM_VSCROLL message handler.
//@rdesc void 
//@parm UINT /*nSBCode*/
//@parm  UINT /*nPos*/
//@parm  CScrollBar* /*pScrollBar*/
void CGXDTabWnd::OnVScroll(UINT /*nSBCode*/, UINT /*nPos*/, CScrollBar* /*pScrollBar*/)
{
	// ensure that edit popup is not visible
	OnEditCancel(0, 0);

	// pass message to active pane
	MSG msg = *GetCurrentMessage();
	if (m_pActivePane)
		m_pActivePane->SendMessage(msg.message, msg.wParam, msg.lParam);
}

//@doc CGXDTabWnd
//@mfunc WM_HSCROLL message handler.
//@rdesc void 
//@parm UINT /*nSBCode*/
//@parm  UINT /*nPos*/
//@parm  CScrollBar* /*pScrollBar*/
void CGXDTabWnd::OnHScroll(UINT /*nSBCode*/, UINT /*nPos*/, CScrollBar* /*pScrollBar*/)
{
	// ensure that edit popup is not visible
	OnEditCancel(0, 0);

	// pass message to active pane
	MSG msg = *GetCurrentMessage();
	if (m_pActivePane)
		m_pActivePane->SendMessage(msg.message, msg.wParam, msg.lParam);
}

//@doc CGXDTabWnd
//@mfunc A helper function to fill the given rectangle with a given color.
//@rdesc void 
//@parm CDC* pDC A pointer to CDC to drawn the rectangle on.
//@parm  int x left poisition of the rectangle.
//@parm  int y Right position of the rectangle.
//@parm  int cx Width of the rectangle.
//@parm  int cy Height of the rectangle.
//@parm  COLORREF clr
void CGXDTabWnd::PatB(CDC* pDC, int x, int y, int cx, int cy, COLORREF clr)
{
	COLORREF rgbOld = pDC->GetBkColor();
	pDC->SetBkColor(clr);
	CRect rc(x, y, x + cx, y + cy);
	pDC->ExtTextOut(0,0,ETO_OPAQUE,&rc,NULL,0,NULL);
	pDC->SetBkColor(rgbOld);
}

//@doc CGXDTabWnd
//@mfunc A helper function to draw the splitter box within the given rectangle.
//@rdesc void 
//@parm CDC* pDC A pointer to CDC the splitter to be drawn on.
//@parm  const CRect& rect A reference to CRect within which the splitter box will be drawn.
void CGXDTabWnd::OnDrawSplitter(CDC* pDC, const CRect& rect)
{
	// if pDC == NULL then just invalidate
	if (pDC == NULL)
	{
		InvalidateRect(rect);
		return;
	}
	ASSERT_VALID(pDC);

	COLORREF rgbFace    = GetSysColor(COLOR_BTNFACE);
	COLORREF rgbShadow  = GetSysColor(COLOR_BTNSHADOW);
	COLORREF rgbHilite = GetSysColor(COLOR_BTNHIGHLIGHT);
	//COLORREF rgbFrame   = GetSysColor(COLOR_WINDOWFRAME);

	// Top left
	PatB(pDC, rect.left, rect.top, rect.Width() - 1, 1, rgbFace);
	PatB(pDC, rect.left, rect.top + 1, 1, rect.Height() - 1, rgbFace);
	
	// Top Left
	PatB(pDC, rect.left + 1, rect.top + 1, rect.Width() - 3, 1,  rgbHilite);
	PatB(pDC, rect.left + 1, rect.top + 2, 1, rect.Height() - 3, rgbHilite);

	// Center
	PatB(pDC, rect.left + 2, rect.top + 2, rect.Width() - 4, rect.Height() - 3, rgbFace);

	// Right Bottom
	PatB(pDC, rect.right - 2, rect.top + 1, 1, rect.Height() - 1, rgbShadow);
	PatB(pDC, rect.left + 1, rect.bottom - 1, rect.Width() - 3, 1, rgbShadow);

	//Right
	PatB(pDC, rect.right - 1, rect.top, 1, rect.Height(), RGB(0, 0, 0));

/*	CGXDTabBeam::PatB(pDC, rect.left, rect.top, 1, rect.Height(), RGB(0,0,0));
	CGXDTabBeam::PatB(pDC, rect.left+1, rect.top, 1, rect.Height(), rgbHilite);
	CGXDTabBeam::PatB(pDC, rect.left+2, rect.top, 1, rect.Height(), rgbFace);
	CGXDTabBeam::PatB(pDC, rect.left+3, rect.top, 1, rect.Height(), rgbShadow);
	CGXDTabBeam::PatB(pDC, rect.left+4, rect.top, 1, rect.Height(), RGB(0,0,0));
	                             
	// top border	                             
	if (GXGetAppData()->bNotWin4)
		CGXDTabBeam::PatB(pDC, rect.left, rect.top, rect.Width(), 1, RGB(0,0,0));
*/

}



//@doc CGXDTabWnd
//@mfunc WM_LBUTTONDWON message handler. 
//@rdesc void 
//@parm UINT nFlags
//@parm  CPoint point
void CGXDTabWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_pActivePane->SetFocus();

	CRect rectClient;
	GetClientRect(&rectClient);

	CRect rect(m_cxBeam+1,
		rectClient.bottom - m_cyHScroll,
		m_cxBeam+m_cxSplitter,
		rectClient.bottom);

	if (rect.PtInRect(point))
	{
		SetCapture();
		m_bTracking = TRUE;
		return;
	}

	// tell the splitter

	//added for the second for the splitter
	CRect rectInside;
	GetInsideRect(rectInside);
	CRect rectSplitter(rectInside.right - m_cxSplitter - ::GetSystemMetrics(SM_CXVSCROLL), //left
			rectClient.bottom - m_nBarWidths, //top
			rectInside.right - ::GetSystemMetrics(SM_CXVSCROLL), //right
			rectClient.bottom); //bottom


	if (rectSplitter.PtInRect(point))
	{
		
		if(GetActivePane() && GetActivePane()->IsKindOf(RUNTIME_CLASS(CGXDSplitWnd)))
		{
			((CGXDSplitWnd*)GetActivePane())->StartTracking(hSplitterBox);
			GetActivePane()->RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE|RDW_INTERNALPAINT |RDW_FRAME);
		}
		return;
	}


	CWnd::OnLButtonDown(nFlags, point);
}

//@doc CGXDTabWnd
//@mfunc WM_LBUTTONUP handler. If the window is in the tracking mode, it will clear up the 
//tracking and update the tab-beam control, otherwise, it calls CWnd::OnLButtonUp.
//@rdesc void 
//@parm UINT nFlags
//@parm  CPoint point
void CGXDTabWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_bTracking)
	{
		ReleaseCapture();
		m_bTracking = FALSE;
		OnMouseMove(nFlags, point);
		m_pBeam->m_nxTracking = -2;
		m_pBeam->Invalidate(FALSE);
		m_pBeam->UpdateWindow();
		m_pBeam->m_nxTracking = -1;
	}

	CWnd::OnLButtonUp(nFlags, point);
}

//@doc CGXDTabWnd
//@mfunc WM_MOUSEMOVE message handler. It updates the cursor when mouse is moved over the splitter
//and redraw the tab-beam and scroll bar.
//@rdesc void 
//@parm UINT nFlags
//@parm  CPoint point
void CGXDTabWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_bTracking && point.x != m_cxBeam)
	{
		if (point.x < m_pBeam->m_nMargin+20)
			return;

		CRect rectClient;
		GetClientRect(&rectClient);

		if (point.x > rectClient.right - 2 * m_nBarWidths)
			return;

		CRect rect(m_cxBeam+1,
			rectClient.bottom - m_nBarWidths,
			m_cxBeam+m_cxSplitter,
			rectClient.bottom);
		InvalidateRect(rect, FALSE);

		m_pBeam->m_nxTracking = min(m_cxBeam, point.x);

		m_cxBeam = point.x;
		RecalcLayout(TRUE);
		UpdateWindow();
		return;
	}
	else
	{
		CRect rectClient;
		GetClientRect(&rectClient);

		CRect rect(m_cxBeam+1,
			rectClient.bottom - m_nBarWidths,
			m_cxBeam+m_cxSplitter,
			rectClient.bottom);

		
		//added for the second for the splitter
		CRect rectInside;
		GetInsideRect(rectInside);
		CRect rectSplitter(rectInside.right - m_cxSplitter - ::GetSystemMetrics(SM_CXVSCROLL), //left
			rectClient.bottom - m_nBarWidths, //top
			rectInside.right - ::GetSystemMetrics(SM_CXVSCROLL), //right
			rectClient.bottom); //bottom

		BOOL b = (GetActivePane() && GetActivePane()->IsKindOf(RUNTIME_CLASS(CGXDSplitWnd)) && rectSplitter.PtInRect(point));

		
		TRACE1("The boolean value for our conditions is %d\n", b);
		TRACE1("The boolean value for our hitTest is %d\n", rectSplitter.PtInRect(point));

		if(GetActivePane())
		{
			TRACE1("The runtime class test result is %d\n", GetActivePane()->IsKindOf(RUNTIME_CLASS(CGXDSplitWnd)));
		}
		
		if (rect.PtInRect(point) || 
			(GetActivePane() && GetActivePane()->IsKindOf(RUNTIME_CLASS(CGXDSplitWnd)) && rectSplitter.PtInRect(point)))
		{
			static HCURSOR NEAR hcurLast = NULL;    // ATTENTION with DLLs
			static HCURSOR NEAR hcurDestroy = NULL;
			static UINT NEAR idcPrimaryLast = 0;        // store the primary IDC

			UINT    idcPrimary = 0;        // app supplied cursor
			LPCTSTR idcSecondary = 0;      // system supplied cursor

#ifdef _AFXDLL
			idcPrimary = GX_IDC_HSPLITBAR;
			// if your compiler reports an error, you should copy the
			// AFX_IDC_HSPLITBAR cursor from AFXRES.RC to your resource file
			// and name it GX_IDC_HSPLITBAR
#else
			idcPrimary = AFX_IDC_HSPLITBAR;
#endif
			idcSecondary = IDC_SIZEWE;

			// Block:
			{
				HCURSOR hcurToDestroy = NULL;
				if (idcPrimary != idcPrimaryLast)
				{
#if _MFC_VER >= 0x0300
					HINSTANCE hInst = AfxFindResourceHandle(
						MAKEINTRESOURCE(idcPrimary), RT_GROUP_CURSOR);
#else
					HINSTANCE hInst = AfxGetResourceHandle();
#endif

					// load in another cursor
					hcurToDestroy = hcurDestroy;

					// Note: If this LoadCursor call fails, it is likely that
					// gxres.rc file is not include in your resource file.
					// To correct the situation, include gxres.rc into your
					// resource script.
					// This should be done using the Resource.Set Includes... command.
					// and including gxresrc.h and gxres.rc

					if ((hcurDestroy = hcurLast =
						// AfxGetApp()->LoadCursor(idcPrimary)) == NULL
					   ::LoadCursor(hInst, MAKEINTRESOURCE(idcPrimary))) == NULL)
					{
						// will not look as good
						TRACE0("Warning: Could not find splitter cursor - using system provided alternative.\n");

						ASSERT(hcurDestroy == NULL);    // will not get destroyed
						// hcurLast = AfxGetApp()->LoadCursor(idcSecondary);
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
		}
	}

	CWnd::OnMouseMove(nFlags, point);
}

//@doc CGXDTabWnd
//@mfunc WM_SETCURSOR message handler. 
//@rdesc BOOL 
//@parm CWnd* pWnd
//@parm  UINT nHitTest
//@parm  UINT message
BOOL CGXDTabWnd::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	CRect rectClient;
	GetClientRect(&rectClient);

	CRect rect(m_cxBeam+1,
		rectClient.bottom - m_cyHScroll,
		m_cxBeam+m_cxSplitter,
		rectClient.bottom);

	CRect rectInside;
	GetInsideRect(rectInside);
	CRect rectSplitter(rectInside.right - m_cxSplitter - ::GetSystemMetrics(SM_CXVSCROLL), //left
			rectClient.bottom - m_nBarWidths, //top
			rectInside.right - ::GetSystemMetrics(SM_CXVSCROLL), //right
			rectClient.bottom); //bottom

	CPoint pt;
	::GetCursorPos(&pt);
	pWnd->ScreenToClient(&pt);

	if (pWnd == this && !m_bTracking && (rect.PtInRect(pt) || rectSplitter.PtInRect(pt)) )
		return TRUE;    // we will handle it in the mouse move
	return CWnd::OnSetCursor(pWnd, nHitTest, message);
}

//@doc CGXDTabWnd
//@mfunc WM_SETFOCUS message handler.
//@rdesc void 
//@parm CWnd* pOldWnd
void CGXDTabWnd::OnSetFocus(CWnd* pOldWnd)
{
	CWnd::OnSetFocus(pOldWnd);

	if (m_pActivePane && pOldWnd != m_pActivePane)
		m_pActivePane->SetFocus();
}

//@doc CGXDTabWnd
//@mfunc WM_ERASEBKGND message handler.
//@rdesc BOOL 
//@parm CDC* pDC
BOOL CGXDTabWnd::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	GetClientRect(rect);
	rect.left = rect.right - m_nBarWidths;
	pDC->FillRect(rect, &m_brErase);

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CGXDEditLabelPopup

CGXDEditLabelPopup::CGXDEditLabelPopup(CRect rect, CWnd* pParentWnd, UINT nID)
{
	if (GXGetAppData()->bWin4)
		Create(WS_BORDER | WS_VISIBLE | ES_AUTOHSCROLL, rect, pParentWnd, nID);
	else
		Create(WS_DLGFRAME | WS_BORDER | WS_VISIBLE | ES_AUTOHSCROLL, rect, pParentWnd, nID);
}

CGXDEditLabelPopup::~CGXDEditLabelPopup()
{
}

BEGIN_MESSAGE_MAP(CGXDEditLabelPopup, CEdit)
	//{{AFX_MSG_MAP(CGXDEditLabelPopup)
	ON_WM_KILLFOCUS()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_GETDLGCODE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGXDEditLabelPopup message handlers


void CGXDEditLabelPopup::OnKillFocus(CWnd* pNewWnd)
{
	CEdit::OnKillFocus(pNewWnd);

	GetParent()->SendMessage(WM_GX_EDITCANCEL, 0, 0);
}

void CGXDEditLabelPopup::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == 13)
		GetParent()->SendMessage(WM_GX_EDITEND, 0, 0);
	else if (nChar == 27)
		GetParent()->SendMessage(WM_GX_EDITCANCEL, 0, 0);
	else
		CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CGXDEditLabelPopup::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar != 13 && nChar != 27)
		CEdit::OnKeyUp(nChar, nRepCnt, nFlags);
}

UINT CGXDEditLabelPopup::OnGetDlgCode()
{
	return CEdit::OnGetDlgCode() | DLGC_WANTALLKEYS;
}


//@doc CGXDTabWnd
//@mfunc WM_NCPAINT message handler. Refer to CWnd::OnNcPaint in MFC for details.
//@rdesc void 
void CGXDTabWnd::OnNcPaint()
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

//@doc CGXDTabWnd
//@mfunc WM_SYSCOLORCHANGE message handler. It stores the new system color of later use
//and tell the window to redraw itself.
//@rdesc void 
void CGXDTabWnd::OnSysColorChange()
{
	CWnd::OnSysColorChange();

	GXGetSysData()->UpdateSysColors();

	m_brErase.DeleteObject();
	m_brErase.CreateSolidBrush(::GetSysColor(COLOR_BTNFACE));

	Invalidate();

#if _MFC_VER < 0x0300
	if (GXGetAppData()->bWin4)
		OnWinIniChange(NULL);
#endif
}

//@doc CGXDTabWnd
//@mfunc WM_WININICHANGE message handler. It obtains the new system settings and 
//call RecalcLayout method to reposition the window and its controls. Refer to 
//CWnd::OnWinIniChange in MFC for details.
//@rdesc void 
//@parm LPCTSTR lpszSection
void CGXDTabWnd::OnWinIniChange(LPCTSTR lpszSection)
{
	CWnd::OnWinIniChange(lpszSection);

	GXGetSysData()->UpdateSysSettings();

	m_cxVScroll = GetSystemMetrics(SM_CXVSCROLL);
	m_cyHScroll = GetSystemMetrics(SM_CYHSCROLL);
	m_nBarWidths = m_cyHScroll + 2*GXGetAppData()->bWin4;

	RecalcLayout();
}
