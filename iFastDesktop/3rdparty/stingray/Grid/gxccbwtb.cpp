///////////////////////////////////////////////////////////////////////////////
// gxccbwtb.cpp : implementation of CGXTabbedComboBoxWnd control
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
// Multi-monitor support
#include <multimon.h>

#ifdef _GXDLL
#undef AFXAPI_DATA
#define AFXAPI_DATA __based(__segname("_DATA"))
#endif

// Headers

#include "grid\gxresrc.h"

#ifndef _GXCTRLI_H_
#include "grid\gxctrli.h"
#endif

#ifndef _GXPRIV_H_
#include "grid\gxpriv.h"
#endif

#include <ctype.h>

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXCCBWTB")
#endif

GRID_IMPLEMENT_CONTROL(CGXTabbedComboBoxWnd, CGXComboBoxWnd);
IMPLEMENT_DYNAMIC(CGXTabbedComboBoxWnd, CGXComboBoxWnd);

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// Global methods

/////////////////////////////////////////////////////////////////////////////
// CGXTabbedComboBoxWnd

CGXTabbedComboBoxWnd::CGXTabbedComboBoxWnd(CGXGridCore* pGrid)
	: CGXComboBoxWnd(pGrid)
{
	m_nValueCol = 0;
	m_nDisplayCol = 0;
	m_bDispAllCols = TRUE; // no table-like dropdown list

	m_nWidthLBox = 0;
	m_pWndCBEditPart = NULL;
	m_iTabCount = 0;
	m_piarTabStops = NULL;
	// m_bWantArrowKeys = TRUE;
	m_bDisplayTitleRow = TRUE;
	m_nSortCol = -1; // no sorting
	m_bReadOnly = FALSE;
	m_rgbGridLine = RGB(192,192,192);
	m_bDropDownOnClick = FALSE;
    m_nLeftMargin = 0;
	m_hComboLBox = 0;

	m_pWndTitleRow = new CGXTabbedLBoxHeader();
	m_bIgnoreNextDraw = FALSE;
	m_bLockMeasure = FALSE;
	m_sAddString.Empty();
}

CGXTabbedComboBoxWnd::~CGXTabbedComboBoxWnd()
{
	delete m_pWndCBEditPart;
	delete m_piarTabStops;
	if (m_pWndTitleRow)
		m_pWndTitleRow->DestroyWindow();
	delete m_pWndTitleRow;
}

// Comment: added code for subclassing edit portion of combobox.
// undef the SubclassWindow macro
#ifdef SubclassWindow
#undef SubclassWindow
#endif

BOOL CGXTabbedComboBoxWnd::CreateControl(DWORD dwStyle, UINT nID)
{
	dwStyle |= WS_VSCROLL | CBS_DROPDOWN | CBS_OWNERDRAWVARIABLE | CBS_HASSTRINGS | CBS_NOINTEGRALHEIGHT;

#if _MFC_VER >= 0x0300 && _MFC_VER < 0x0420
	if (GXGetAppData()->bWin31)
		dwStyle &= ~CBS_DROPDOWNLIST;	// not supported under Win32s
#endif


	AddChild(m_pButton = new CGXComboBoxWndButton(this));

	CGXStylesMap* pStylesMap = NULL;
	if (Grid()->GetParam())
		pStylesMap = Grid()->GetParam()->GetStylesMap();

#ifndef _UNICODE
	BOOL b = CWnd::Create(_T("COMBOBOX"), NULL, dwStyle, CRect(0, 0, 0, 0), GridWnd(), nID);
#else
	BOOL b = CWnd::Create(_T("GXCOMBOBOX"), NULL, dwStyle, CRect(0, 0, 0, 0), GridWnd(), nID);
#endif

	if (b)
	{
		// check if combobox has an edit portion
		CEdit* pEdit = (CEdit*) GetWindow(GW_CHILD);
		if (pEdit)
		{
			// subclass the edit control. m_wndEdit is a variable of
			// CGXTabbedCBEditWnd class
			CGXTabbedCBEditWnd* pWnd = new CGXTabbedCBEditWnd;
			pWnd->CEdit::SubclassWindow(pEdit->GetSafeHwnd());
			m_pWndCBEditPart = pWnd;
		}
	}

	m_bFindTextSupported = TRUE; // Find&Replace is supported

	return b;
}

void AFXAPI CGXTabbedComboBoxWnd::AddUserAttributes(CGXStylesMap* pStylesMap)
{
	pStylesMap->AddUserAttribute(GX_IDS_UA_TABLIST_KEYCOL);

	pStylesMap->AddUserAttribute(GX_IDS_UA_TABLIST_TEXTCOL);
	
	pStylesMap->AddUserAttribute(GX_IDS_UA_TABLIST_SHOWALLCOLS,
		CGXStyle().SetControl(GX_IDS_CTRL_CHECKBOX3D)
			  .SetVerticalAlignment(DT_VCENTER)
			  .SetHorizontalAlignment(DT_CENTER));
	
	pStylesMap->AddUserAttribute(GX_IDS_UA_TABLIST_TITLEROW,
		CGXStyle().SetControl(GX_IDS_CTRL_CHECKBOX3D)
			  .SetVerticalAlignment(DT_VCENTER)
			  .SetHorizontalAlignment(DT_CENTER));
	
	pStylesMap->AddUserAttribute(GX_IDS_UA_TABLIST_SORTCOL);
}

BEGIN_MESSAGE_MAP(CGXTabbedComboBoxWnd, CGXComboBoxWnd)
	//{{AFX_MSG_MAP(CGXTabbedComboBoxWnd)
	ON_WM_SHOWWINDOW()
	ON_WM_SYSCHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGXTabbedComboBoxWnd message handlers

#if _MFC_VER < 0x0420

// Special code for Win 3.1 and Win32s

#define GX_STRING_PSEUDO_NULL _T("GX_DummYX")

static BOOL CALLBACK ListOfChild(HWND hwd, LPARAM lp)
{
	TCHAR buffer[30];

	CGXTabbedComboBoxWnd* pComboBox = (CGXTabbedComboBoxWnd*) lp;

	// ClassName of hwd
	::GetClassName(hwd, buffer, 20);

	// if not ComboLBox" -> continue search return TRUE)
	if (_tcscmp(buffer, _T("ComboLBox")) != 0)
		return TRUE;

	// Ptr to ComboLBox
	CListBox* pList = (CListBox*)CWnd::FromHandle(hwd);

	// Check if this is the right ComboLBox with the first entry
	// equal to GX_STRING_PSEUDO_NULL
	if (pList->FindString(-1, GX_STRING_PSEUDO_NULL) != LB_ERR)
	{
		pComboBox->m_hComboLBox = hwd;

		// stop searching (return FALSE)
		return FALSE;
	}
	else
		// continue searching (return TRUE)
		return  TRUE;
}

HBRUSH CGXTabbedComboBoxWnd::OnGridCtlColor(CDC*, CWnd* pWnd, UINT nCtlColor)
{
	// TRACE("CGXTabbedComboBoxWnd::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor = %d)\n", nCtlColor);

	BOOL bWin31 = GXGetAppData()->bWin31;
#if _MFC_VER < 0x0300
	bWin31 = TRUE;
#endif

	BOOL bOk = FALSE;

	if (bWin31)
	{
		if (IsActive() && nCtlColor == CTLCOLOR_LISTBOX && GetDroppedState())
		{
			// Get Listbox handle
			if (m_hComboLBox == 0)
			{
				m_bLockMeasure = TRUE;

				// Dummy String
				InsertString(0, GX_STRING_PSEUDO_NULL);

				// search all children of desktop
				::EnumChildWindows(::GetDesktopWindow(), ListOfChild, (LPARAM) this);

				// Remove dummy string
				DeleteString(0);

				m_bLockMeasure = FALSE;
			}

			pWnd = CWnd::FromHandle(m_hComboLBox);

			bOk = TRUE;
		}
	}
	else
	{
		if (IsActive() && nCtlColor == CTLCOLOR_LISTBOX)
			bOk = TRUE;
	}

#else

// MFC 4.2 does not have to handle Win32s issues

HBRUSH CGXTabbedComboBoxWnd::OnGridCtlColor(CDC*, CWnd* pWnd, UINT nCtlColor)
{
	BOOL bOk = FALSE;

	if (IsActive() && nCtlColor == CTLCOLOR_LISTBOX)
		bOk = TRUE;

#endif


	if (bOk)
	{
		static BOOL NEAR m_bLockMoveWindow = FALSE;
		if (m_bLockMoveWindow)
			return NULL;
		m_bLockMoveWindow = TRUE;

#ifndef _UNIX_
		TCHAR szClassName[24];
		::GetClassName(pWnd->GetSafeHwnd(), szClassName, sizeof(szClassName));
		if (_tcsicmp(szClassName, _T("ComboLBox")) == 0)
#endif
		{
			CRect rect;

			CRect rectComboLBox;
			pWnd->GetWindowRect(rectComboLBox);

			CRect rectCombo;
			CRect rectHeader;
			GetClientRect(rectCombo);
			ClientToScreen(&rectCombo);

			// adjust width
			rectComboLBox.right = rectComboLBox.left + max(rectCombo.Width(), m_nWidthLBox);

			// calculate rectangle for popup window
			// Multi-monitor support
			CRect desktopRect;
			HMONITOR hMonitor = MonitorFromWindow(m_hWnd, MONITOR_DEFAULTTONEAREST);
			ASSERT(hMonitor != NULL);
			MONITORINFO monitorInfo = { sizeof(MONITORINFO) };
			VERIFY(GetMonitorInfo(hMonitor, &monitorInfo));
			desktopRect = monitorInfo.rcWork;

			// shift to left if it goes beyond screen
			if (rectComboLBox.right > desktopRect.right)
				rectComboLBox -= CPoint(rectComboLBox.Width() - rectCombo.Width(), 0);

			// space for headers
			if (m_bDisplayTitleRow && (m_pWndTitleRow->GetSafeHwnd() == 0 || !m_pWndTitleRow->IsWindowVisible()))
			{
				unsigned int nHeight = (unsigned int) m_nDefaultHeight;

				CGXTabbedLBoxImp::MeasureHeight(m_pWndTitleRow->m_strTitles, nHeight, !m_bDispAllCols, m_nDisplayCol, m_iTabCount);

				// add small margin to top and botto´m
				nHeight += 4;

				// Create window for tile row on demand
				if (m_pWndTitleRow->GetSafeHwnd() == 0)
					m_pWndTitleRow->CreateHeader(this);

				m_pWndTitleRow->m_bDispAllCols = m_bDispAllCols;
				m_pWndTitleRow->m_nDisplayCol = m_nDisplayCol;
				m_pWndTitleRow->m_iTabCount = m_iTabCount;
				m_pWndTitleRow->m_piarTabStops = m_piarTabStops;
				m_pWndTitleRow->m_pFont = GetFont();

				// Position title row
				if (rectComboLBox.bottom > rectCombo.bottom)
				{
					// Insert header row between edit part and listbox
					rectHeader = rectComboLBox;
					rectHeader.bottom = rectHeader.top + (int) nHeight;

					m_pWndTitleRow->SetWindowPos(&wndTopMost, rectHeader.left,
						rectHeader.top,
						rectHeader.Width(),
						rectHeader.Height(),
						SWP_SHOWWINDOW
						);

					// Shift listbox down
					rectComboLBox += CPoint(0, rectHeader.Height());
				}
				else
				{
					// Position header row above listbox
					rectHeader = rectComboLBox;
					rectHeader.top = rectComboLBox.top - (int) nHeight;
					rectHeader.bottom = rectComboLBox.top;

					m_pWndTitleRow->SetWindowPos(&wndTopMost, rectHeader.left,
						rectHeader.top,
						rectHeader.Width(),
						rectHeader.Height(),
						SWP_SHOWWINDOW
						);
				}
			}

			rectComboLBox.IntersectRect(rectComboLBox, desktopRect);

			// Check if rectangle has been changed
			if (m_rectComboLBox != rectComboLBox)
			{
				// Show listbox
				// TRACE("MoveLBoxWindow(%d,%d,%d,%d) -> (%d,%d,%d,%d)\n", m_rectComboLBox, rectComboLBox);

				m_rectComboLBox = rectComboLBox;

				pWnd->MoveWindow(m_rectComboLBox, TRUE);
				if (m_bDisplayTitleRow && m_pWndTitleRow->GetSafeHwnd())
					m_pWndTitleRow->UpdateWindow();
			}
		}

		m_bLockMoveWindow = FALSE;

	}
	else if (IsActive() && nCtlColor == CTLCOLOR_EDIT)
	{
		// Hide title row
		if (!GetDroppedState() && m_pWndTitleRow->GetSafeHwnd() && m_pWndTitleRow->IsWindowVisible())
			m_pWndTitleRow->ShowWindow(SW_HIDE);
	}

	return NULL;
}

BOOL CGXTabbedComboBoxWnd::OnCommand(WPARAM wParam, LPARAM lParam)
{
#if _MFC_VER < 0x0300
	UINT nNotification = HIWORD(lParam);
	HWND hCtl = (HWND) LOWORD(lParam);
#else
	UINT nNotification = HIWORD(wParam);
	HWND hCtl = (HWND) lParam;
#endif

	if (hCtl == m_hWnd && IsActive())
	{
		if (nNotification == CBN_CLOSEUP)
		{
			// Hide title row
			if (m_pWndTitleRow->GetSafeHwnd() && m_pWndTitleRow->IsWindowVisible())
				m_pWndTitleRow->ShowWindow(SW_HIDE);
			m_rectComboLBox.SetRectEmpty();
		}
		else if (nNotification == CBN_DROPDOWN)
		{
			m_rectComboLBox.SetRectEmpty();
		}
	}

	return CGXComboBoxWnd::OnCommand(wParam, lParam);
}

void CGXTabbedComboBoxWnd::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CGXComboBoxWnd::OnShowWindow(bShow, nStatus);

	// Hide title row
	if (!bShow && m_pWndTitleRow->GetSafeHwnd() && m_pWndTitleRow->IsWindowVisible())
		m_pWndTitleRow->ShowWindow(SW_HIDE);
}

void CGXTabbedComboBoxWnd::Hide()
{
	// Hide title row
	if (m_pWndTitleRow->GetSafeHwnd() && m_pWndTitleRow->IsWindowVisible())
		m_pWndTitleRow->ShowWindow(SW_HIDE);

	CGXComboBoxWnd::Hide();
}


// Operations
void CGXTabbedComboBoxWnd::Init(ROWCOL nRow, ROWCOL nCol)
{
	// Stores the cell coordinates, resets the style and sets the window text
	m_nDefaultHeight = 0;   // Force OnInitChildren to determine font height
	CGXStatic::Init(nRow, nCol);

	m_bDropDownOnNextSetFocus = FALSE;
	m_nStartChar = 0;
	m_nEndChar = -1;
	SetEditSel(0, -1);   // Select all
	SetReadOnly(FALSE);

	SetActive(FALSE);
	NeedStyle();

	// User attributes
	m_nValueCol = _ttoi(m_pStyle->GetUserAttribute(GX_IDS_UA_TABLIST_KEYCOL));
	m_nDisplayCol = _ttoi(m_pStyle->GetUserAttribute(GX_IDS_UA_TABLIST_TEXTCOL));
	m_bDispAllCols = TRUE;
	if (m_pStyle->GetIncludeUserAttribute(GX_IDS_UA_TABLIST_SHOWALLCOLS))
		m_bDispAllCols = _ttoi(m_pStyle->GetUserAttribute(GX_IDS_UA_TABLIST_SHOWALLCOLS));
	m_bDisplayTitleRow = _ttoi(m_pStyle->GetUserAttribute(GX_IDS_UA_TABLIST_TITLEROW));
	m_strColWidths = m_pStyle->GetUserAttribute(GX_IDS_UA_TABLIST_COLWIDTHS);
	m_nSortCol = -1; // no sorting
	if (m_pStyle->GetIncludeUserAttribute(GX_IDS_UA_TABLIST_SORTCOL))
		m_nSortCol = _ttoi(m_pStyle->GetUserAttribute(GX_IDS_UA_TABLIST_SORTCOL));

	LoadLBoxEntries();

	// set current selection
	SetValue(m_pStyle->GetValueRef());
	SetModify(FALSE);

	if (Grid()->GetParam()->GetActivateCellFlags() & GX_CAFOCUS_SETCURRENT && OnStartEditing())
		SetActive(TRUE);

	SetReadOnly(Grid()->IsReadOnly() || m_pStyle->GetIncludeReadOnly() && m_pStyle->GetReadOnly());

	// Force drawing of buttons for current cell
	if (!IsActive() && m_pButton)
		GridWnd()->InvalidateRect(m_pButton->GetRect());
}

void CGXTabbedComboBoxWnd::LoadLBoxEntries()
{
	int anMaxWidth[GX_TABNMAXCOLS];
	int i;
	for (i = 0; i < GX_TABNMAXCOLS; i++)
		anMaxWidth[i] = -1;
	SetTabStops(GX_TABNMAXCOLS);
	m_nWidthLBox = 0;

	m_bLockMeasure = FALSE; // ??

	// check if we need to fill combobox with the choice list
	ResetContent();

	m_pWndTitleRow->m_strTitles.Empty();

	if (m_bFillWithChoiceList && !m_pStyle->GetChoiceListRef().IsEmpty())
	{
		// fill with choice list
		CString s = m_pStyle->GetChoiceListRef();
		CString sItem;
		int n = 0;
		TCHAR szDisplayText[128];

		if (m_nSortCol >= 0)
			GXSortChoiceList(s, m_nSortCol, m_bDisplayTitleRow);

		// Select font
		CClientDC dc(GridWnd());
		CFont* pOldFont = LoadFont(&dc, *m_pStyle, NULL);

		BOOL bTitleRowDone = FALSE;

		while (!s.IsEmpty() && n != -1)
		{
			n = GXGetNextLine(s, sItem);

			// Determine maximum width for each column
			CGXTabbedLBoxImp::DetermineMaxColWidth(&dc, sItem, GX_TABNMAXCOLS, anMaxWidth);

			// Make sure display string is at beginning of entry
			// This is necessary because the edit part assumes that
			// the text in the edit portion is the first column in
			// the listbox entries.

			if (m_nDisplayCol > 0)
			{
				GXGetColString(sItem, m_nDisplayCol, szDisplayText, 127);

				// Add a tab char
				// QA: 31989 - #if Secure Code Cleanup.
				_tcscat(szDisplayText, _T("\t"));

				// Insert string
				if (!bTitleRowDone && m_bDisplayTitleRow)
					m_pWndTitleRow->m_strTitles = (CString) szDisplayText + sItem;
				else
					AddString(m_sAddString = (CString) szDisplayText + sItem);
			}
			else
			{
				// First column already is the display text
				if (!bTitleRowDone && m_bDisplayTitleRow)
					m_pWndTitleRow->m_strTitles = sItem;
				else
					AddString(m_sAddString = sItem);
			}

			bTitleRowDone = TRUE;
		}

		// deselect font
		if (pOldFont)
			dc.SelectObject(pOldFont);

		m_sAddString.Empty();

		// calculate width and no. of columns
		LPCTSTR psz = m_strColWidths;
		int nCols;
		for (nCols = 0; nCols < GX_TABNMAXCOLS && anMaxWidth[nCols] != -1; nCols++)
		{
			if (psz && _istdigit(*psz))
			{
				anMaxWidth[nCols] = _ttoi(psz);
				// end of number
				while (*psz && _istdigit(*psz))
					psz++;
				// next number
				while (*psz && !_istdigit(*psz))
					psz++;
			}
			else if (!m_bDispAllCols && nCols != m_nDisplayCol)
				anMaxWidth[nCols] = 0;
			else
			{
				anMaxWidth[nCols] += 4; // reserve some space between columns
			}
			m_nWidthLBox += anMaxWidth[nCols];
		}

		// cumulate tab positions
		SetTabStops(nCols-1);
		for (i = 0; i < m_iTabCount; i++)
		{
			m_piarTabStops[i] = anMaxWidth[i];

			if (i > 0)
				m_piarTabStops[i] += m_piarTabStops[i-1];
		}

		// NOTE: Will add a switch later which avoids that
		// width is smaller than cell

		m_nWidthLBox += GetSystemMetrics(SM_CXVSCROLL);
	}

	m_bLockMeasure = FALSE;
}

BOOL CGXTabbedComboBoxWnd::StoreStyle(ROWCOL nRow, ROWCOL nCol, const CGXStyle* pStyle, GXModifyType mt, int nType, const CGXStyle* pOldStyle)
{
	ASSERT(pStyle || mt == gxRemove);
	ASSERT(pOldStyle);

	// We are only interested to interere changes in current cell
	if (!CGXControl::StoreStyle(nRow, nCol, pStyle, mt, nType, pOldStyle))
		return FALSE;

	if ((mt == gxOverride || mt == gxApplyNew)
		&& Grid()->IsCurrentCell(nRow, nCol))
	{
		if (pStyle->GetIncludeChoiceList() 
			|| pStyle->GetIncludeValue() && !GetModify() 
			|| pStyle->GetIncludeControl()
			|| pStyle->GetIncludeUserAttribute(GX_IDS_UA_TABLIST_KEYCOL)
			|| pStyle->GetIncludeUserAttribute(GX_IDS_UA_TABLIST_TEXTCOL)
			|| pStyle->GetIncludeUserAttribute(GX_IDS_UA_TABLIST_SHOWALLCOLS)
			|| pStyle->GetIncludeUserAttribute(GX_IDS_UA_TABLIST_SHOWALLCOLS)
			|| pStyle->GetIncludeUserAttribute(GX_IDS_UA_TABLIST_TITLEROW)
			|| pStyle->GetIncludeUserAttribute(GX_IDS_UA_TABLIST_COLWIDTHS)
			|| pStyle->GetIncludeUserAttribute(GX_IDS_UA_TABLIST_SORTCOL))
			Reset();  // CGXGridCore::OnDrawItem will call Init again
	}

	return TRUE;
}

void CGXTabbedComboBoxWnd::Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle)
{
	ASSERT(pDC != NULL && pDC->IsKindOf(RUNTIME_CLASS(CDC)));
	// ASSERTION-> Invalid Device Context ->END
	ASSERT(nRow <= Grid()->GetRowCount() && nCol <= Grid()->GetColCount());
	// ASSERTION-> Cell coordinates out of range ->END

	ASSERT_VALID(pDC);

	if (nRow == m_nRow && nCol == m_nCol && IsActive() && !Grid()->IsPrinting())
	{
		// ------------------ Active Window ---------------------------

		if (m_bIgnoreNextDraw)
		{
			m_bIgnoreNextDraw = FALSE;
			return;
		}

		int nStart, nEnd;
		GetEditSel(nStart, nEnd);

		if (m_pButton)
			m_pButton->SetRect(CRect(0,0,0,0));

		Hide();

		// Font
		if (m_font.GetSafeHandle())
			m_font.DeleteObject();

		CFont* pOldFont = 0;
		CGXFont font(m_pStyle->GetFontRef());
		font.SetSize(font.GetSize()*Grid()->GetZoom()/100);
		font.SetOrientation(0);

		// no vertical font for editing the cell
		const LOGFONT& _lf = font.GetLogFontRef();
		if ( !m_font.CreateFontIndirect(&_lf) )
		{
			TRACE1("Failed to create font '%s' in CGXTabbedComboBoxWnd::Draw\n",
				(LPCTSTR) m_pStyle->GetFontRef().GetDescription());
		}

		// Cell-Color
		m_rgbBackColor = m_pStyle->GetInteriorRef().GetColor();
		m_rgbTextColor = m_pStyle->GetTextColor();

		if (Grid()->GetParam()->GetProperties()->GetBlackWhite())
		{
			m_rgbBackColor = RGB(0,0,0);
			m_rgbTextColor = RGB(255,255,255);
		}

		SetCellColor(m_rgbBackColor);

		CRect rectText = CGXControl::GetCellRect(nRow, nCol, rect);

		// Select font
		pOldFont = pDC->SelectObject(&m_font);

		TEXTMETRIC    tm;
		pDC->GetTextMetrics(&tm);
		m_nDefaultHeight = tm.tmHeight;

		if (pOldFont)
			pDC->SelectObject(pOldFont);

		SetFont(&m_font);

		// Rectangle for edit portion and push button
		if (Grid()->GetParam()->GetProperties()->GetDisplayHorzLines())
			rectText.top --;

		if (Grid()->GetParam()->GetProperties()->GetDisplayVertLines())
			rectText.left--;

		int dy = rectText.Height();

		if (m_bSizeToContent)
		{
			dy = min(tm.tmHeight + 2, rectText.Height());

			if (m_pStyle->GetIncludeVerticalAlignment())
			{
				// vertical alignment for single line text
				// is done by computing the window rectangle for the CComboBox
				switch (m_pStyle->GetVerticalAlignment())
				{
				case DT_VCENTER:
					rectText.top += (rectText.Height() - dy) / 2;
					break;
				case DT_BOTTOM:
					rectText.top = rectText.bottom - dy - 2;
				break;
				}
			}

			rectText.bottom = rectText.top + dy;
		}

		// enlarge the edit box (static text) of the combobox
		// because we need additional space for the borders.
		if (GXGetAppData()->bWin4 || dy+2*m_nExtraFrame > rectText.Height())
		{
			if (!m_bForceInsideCell)
			{
				rectText.top -= m_nExtraFrame;
				rectText.bottom += m_nExtraFrame;
			}
			else
				dy -= 2*m_nExtraFrame;
		}

		ExcludeClipRect(rectText);

		// Enlarge rectangle with listbox portion
		rectText.bottom += (tm.tmHeight + 2) * min(8, CComboBox::GetCount()) + 3;
		
		//alternative sizing line
		//rectText.bottom += (tm.tmHeight + 2 + 2*m_nExtraFrame) * min(8, CComboBox::GetCount());

		// explicitly set the item heights  
		for (int i = 0; i < CComboBox::GetCount(); i++) 
			SetItemHeight(i, tm.tmHeight); 

		CRect r;
		GetWindowRect(r);

		//TRACE("a: %d,%d,%d,%d   b: %d,%d,%d,%d\n", rect, r);
		if (rectText == r)
			return;

		// Background + Frame
		DrawBackground(pDC, rect, style, TRUE);

		// OnGetListboxRect() is a hook for enlarging the dropdown rectangle
		CRect listBoxRect = OnGetListboxRect(rectText);
		MoveWindow(listBoxRect, FALSE);

		// Set the item height for the edit portion
		if (GXGetAppData()->bWin4)
			SetItemHeight(-1, dy);
		else
			SetItemHeight(-1, dy+m_nExtraFrame);

		// Show combobox
		SetActive(TRUE);
		// ShowWindow(SW_HIDE);
		ShowWindow(SW_SHOW);

		// Block: Ensure that the window cannot draw outside the clipping area!
		{
			CRect rectClip;
			if (pDC->GetClipBox(&rectClip) != ERROR)
			{
				CRect r;
				GetClientRect(r);
				GridWnd()->ClientToScreen(&r);
				ScreenToClient(&r);
				GridWnd()->ClientToScreen(&rectClip);
				ScreenToClient(&rectClip);
				ValidateRect(r); // CRect(0, 0, r.right, rectClip.top));
				InvalidateRect(rectClip); // CRect(0, 0, rectClip.left, r.bottom));
			}
		}

		UpdateWindow();

		if (GetFocus() == GridWnd())
		{
			Grid()->SetIgnoreFocus(TRUE);
			// TRACE("Draw::SetFocus\n");
			SetFocus();
			Invalidate(FALSE);
			UpdateWindow();
			Grid()->SetIgnoreFocus(FALSE);
		}

		if (m_pStyle->GetIncludeMaxLength() && m_pStyle->GetMaxLength() > 0)
			LimitText((int) m_pStyle->GetMaxLength());

		// SetEditSel(nStart, nEnd);
		SetReadOnly(Grid()->IsReadOnly() || m_pStyle->GetIncludeReadOnly() && m_pStyle->GetReadOnly());

		// child Controls: spin-buttons, hotspot, combobox btn, ...
		CGXControl::Draw(pDC, rect, nRow, nCol, *m_pStyle, pStandardStyle);
	}

	else
	//     lookup style and draw static:
	//     - edit control with GXDrawTextLikeMultiLineEdit
	// }
	{
		if (m_bSizeToContent)
		{
			CFont* pOldFont = LoadFont(pDC, style, pStandardStyle);

			TEXTMETRIC tm;
			pDC->GetTextMetrics(&tm);
			m_nDefaultHeight = tm.tmHeight; // OnInitChildren will use m_nDefaultHeight

			if (pOldFont)
				pDC->SelectObject(pOldFont);
		}

		// ------------------ Static Text ---------------------------
		CString str;
		HANDLE hbm = 0;
		if (GetControlText(str, nRow, nCol, NULL, style))
			hbm = GXGetDIBState()->GetPool()->LookupOrCreateDIB(str);

		if (hbm)
		{
			DrawBackground(pDC, rect, style);

			CRect r = GetCellRect(nRow, nCol, rect, &style);

			CGXDIB::Draw(pDC, hbm, r, CGXDIB::none, (UINT) (style.GetHorizontalAlignment()|style.GetVerticalAlignment()));

			// child Controls: spin-buttons, hotspot, combobox btn, ...
			CGXControl::Draw(pDC, rect, nRow, nCol, style, pStandardStyle);
		}
		else
		{
			CGXStatic::Draw(pDC, rect, nRow, nCol, style, pStandardStyle);
		}
	}
}

// SetTabStops
//

void CGXTabbedComboBoxWnd::SetTabStops(int iTabStops)
{
	delete m_piarTabStops;
	m_iTabCount = iTabStops;
	m_piarTabStops = new int[iTabStops];
}

// AddTabStop
//

void CGXTabbedComboBoxWnd::AddTabStop(int iIndex, int iTabStop)
{
	m_piarTabStops[iIndex] = iTabStop;
}

// SetReadOnly
//

void CGXTabbedComboBoxWnd::SetReadOnly(BOOL bReadOnly /* = TRUE */)
{
	EnableWindow(!bReadOnly);

	if (m_pWndCBEditPart == NULL)
		return;

	if (bReadOnly)
	{
		m_pWndCBEditPart->EnableWindow(TRUE);
		m_pWndCBEditPart->SetReadOnly(TRUE);
	}
	else
	{
		m_pWndCBEditPart->SetReadOnly(FALSE);
	}
}

// SetModify
//

void CGXTabbedComboBoxWnd::SetModify(BOOL bModified /* = TRUE */)
{
	CGXComboBoxWnd::SetModify(bModified);
}

// GetModify
//

BOOL CGXTabbedComboBoxWnd::GetModify()
{
	return CGXComboBoxWnd::GetModify();
}

// DrawItem
//

void CGXTabbedComboBoxWnd::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
	if (lpDIS->itemID == CB_ERR)
		return;

	CDC*    pDC = CDC::FromHandle(lpDIS->hDC);
	CString strLBEntry;
	CBrush  brSelected;
	CRect   recTemp = lpDIS->rcItem;

	// Colors
	COLORREF rgbBack, rgbText;
	if (lpDIS->itemState & ODS_SELECTED){

		rgbBack = GetSysColor (COLOR_HIGHLIGHT);
		rgbText = GetSysColor (COLOR_HIGHLIGHTTEXT);
	}
	else
	{
		rgbBack = m_rgbBackColor;
		rgbText = m_rgbTextColor;
	}

	// Check if this is the static part of dropdown listbox
#if _MFC_VER >= 0x0400
	BOOL bDrawComboBoxEdit = lpDIS->itemState & ODS_COMBOBOXEDIT;
#else
	BOOL bDrawComboBoxEdit = lpDIS->rcItem.left > 0;
#endif

	if (lpDIS->itemAction & (ODA_DRAWENTIRE | ODA_SELECT))
	{
		CString strLBEntry;
		if (GetLBTextLen(lpDIS->itemID) > 0)
			GetLBText(lpDIS->itemID, strLBEntry);

		CGXTabbedLBoxImp::DrawItem(pDC,
			lpDIS->rcItem,
			strLBEntry,
			!m_bDispAllCols || bDrawComboBoxEdit,
			m_nDisplayCol,
			m_iTabCount,
			m_piarTabStops,
			m_rgbGridLine,
			rgbBack,
			rgbText,
			m_nLeftMargin);
	}

	if (lpDIS->itemAction & ODA_FOCUS)
		pDC->DrawFocusRect(&recTemp);
}

// MeasureItem
//

void CGXTabbedComboBoxWnd::MeasureItem(LPMEASUREITEMSTRUCT lpMIS)
{
	if (m_bLockMeasure || lpMIS->itemID == CB_ERR)
		return;

	CString strLBEntry;
	if (GetLBTextLen(lpMIS->itemID) > 0)
		GetLBText(lpMIS->itemID, strLBEntry);

	else if (!m_sAddString.IsEmpty())
		strLBEntry = m_sAddString;

	if (!strLBEntry.IsEmpty())
	{
		CGXTabbedLBoxImp::MeasureHeight(strLBEntry, lpMIS->itemHeight,
			!m_bDispAllCols,
			m_nDisplayCol > 0,
			m_iTabCount);
	}
}

// CompareItem
//

int CGXTabbedComboBoxWnd::CompareItem(LPCOMPAREITEMSTRUCT)
{
	return -1;
}

void CGXTabbedComboBoxWnd::GetCurrentText(CString& strResult)
{
	strResult.Empty();

	// get the string for the current selected item
	if ((GetStyle() & CBS_DROPDOWNLIST) == CBS_DROPDOWNLIST)
	{
		// search text in CB
		int nCurSel = GetCurSel();
		if (nCurSel == CB_ERR)
			return;

		// Get selected item
		CString sItem;
		if (GetLBTextLen(nCurSel) > 0)
			GetLBText(nCurSel, sItem);

		// Get display text from item

		TCHAR szValue[128];
		GXGetColString(sItem, 0, szValue, 127);

		strResult = szValue;
	}
	else
		GetWindowText(strResult);
}

void CGXTabbedComboBoxWnd::SetValue(LPCTSTR pszRawValue)
{
	ASSERT(m_bFillWithChoiceList);
	// Don't call this function if m_bFillWithChoiceList is FALSE

	// Search for the key in the choice list and
	// set display string

	// Search for the key in the choice list and
	// set display string
	int nFound = -1;

	// Sort the choice list if necessary before finding the current selection
	CString s = m_pStyle->GetChoiceListRef();
	if (m_nSortCol >= 0)
		GXSortChoiceList(s, m_nSortCol, m_bDisplayTitleRow);

	CString sItem;
	nFound = GXFindChoiceListItem(pszRawValue, m_nValueCol, s, m_bDisplayTitleRow, sItem);

	SetCurSel(nFound);
}

BOOL CGXTabbedComboBoxWnd::GetValue(CString& sResult)
{
	if (!IsInit())
		return FALSE;

	CString strText;
	GetWindowText(strText);

	if (strText.IsEmpty())
	{
		sResult.Empty();
		return TRUE;
	}

	// search text in CB
	int nCurSel = FindString(-1, strText);

	if (nCurSel == CB_ERR)
		return FALSE;

	// Get selected item
	CString sItem;
	if (GetLBTextLen(nCurSel) > 0)
		GetLBText(nCurSel, sItem);

	// Get value from item, but take care on
	// possibly added display column at beginning of string
	int nCol = m_nValueCol;
	if (m_nDisplayCol > 0)
		nCol++;

	TCHAR szValue[128];
	GXGetColString(sItem, nCol, szValue, 127);

	sResult = szValue;
	return TRUE;
}

BOOL CGXTabbedComboBoxWnd::GetControlText(CString& strResult, ROWCOL , ROWCOL , LPCTSTR pszRawValue, const CGXStyle& style)
{
	ASSERT(m_bFillWithChoiceList);
	// Don't call this function if m_bFillWithChoiceList is FALSE

	// User attributes
	int nValueCol = _ttoi(style.GetUserAttribute(GX_IDS_UA_TABLIST_KEYCOL));
	int nDisplayCol = _ttoi(style.GetUserAttribute(GX_IDS_UA_TABLIST_TEXTCOL));
	int bDisplayTitleRow = _ttoi(style.GetUserAttribute(GX_IDS_UA_TABLIST_TITLEROW));

	if (pszRawValue == NULL)
		pszRawValue = style.GetValueRef();

	// search for value in choice list

	if (style.GetIncludeChoiceList())
	{
		CString sItem;
		if (GXFindChoiceListItem(pszRawValue, nValueCol, style.GetChoiceListRef(), bDisplayTitleRow, sItem) != -1)
		{
			TCHAR szValue[128];

			// return display string
			GXGetColString(sItem, nDisplayCol, szValue, 127);
			strResult = szValue;
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CGXTabbedComboBoxWnd::ConvertControlTextToValue(CString& str, ROWCOL nRow, ROWCOL nCol, const CGXStyle* pOldStyle)
{
	ASSERT(m_bFillWithChoiceList);
	// Don't call this function if m_bFillWithChoiceList is FALSE

	CGXStyle* pStyle = NULL;
	BOOL bSuccess = FALSE;

	if (pOldStyle == NULL)
	{
		pStyle = Grid()->CreateStyle();
		Grid()->ComposeStyleRowCol(nRow, nCol, pStyle);
		pOldStyle = pStyle;
	}

	// check for read-only
	if (str.IsEmpty())
	{
		bSuccess = TRUE;
	}

	// find display string
	else 
	{
		// User attributes
		int nValueCol = _ttoi(pOldStyle->GetUserAttribute(GX_IDS_UA_TABLIST_KEYCOL));
		int nDisplayCol = _ttoi(pOldStyle->GetUserAttribute(GX_IDS_UA_TABLIST_TEXTCOL));
		BOOL bDisplayTitleRow = _ttoi(pOldStyle->GetUserAttribute(GX_IDS_UA_TABLIST_TITLEROW));

		if (pOldStyle && pOldStyle->GetIncludeChoiceList())
		{
			CString sItem;
			if (GXFindChoiceListItem(str, nDisplayCol, pOldStyle->GetChoiceListRef(), bDisplayTitleRow, sItem) != -1)
			{
				TCHAR szValue[128];

				// get value
				GXGetColString(sItem, nValueCol, szValue, 127);

				// store key value
				str = szValue;
				bSuccess = TRUE;
			}
		}
	}

	if (pStyle)
		Grid()->RecycleStyle(pStyle);

	return bSuccess;
}

BOOL CGXTabbedComboBoxWnd::OnValidate()
{
	CString sText;

	if (IsActive() && GetModify())
	{
		if (!GetValue(sText))
			return FALSE;
	}

	return CGXControl::OnValidate();
}

BOOL CGXTabbedComboBoxWnd::ValidateString(const CString& sEdit)
{
	if (sEdit.IsEmpty() || !m_bFillWithChoiceList)
		return TRUE;

	CString sItem;
	int nItem = GXFindChoiceListItem(sEdit, m_nDisplayCol, m_pStyle->GetChoiceListRef(), m_bDisplayTitleRow, sItem, FALSE);

	return nItem != -1;
}

BOOL CGXTabbedComboBoxWnd::LButtonUp(UINT nFlags, CPoint pt, UINT nHitState)
{
	// check child buttons
	CGXControl::LButtonUp(nFlags, pt, nHitState);

	// Sets the caret position
	if (!(nHitState & GX_SELECT))
	{
		if (m_bDropDownOnClick)
			SetActiveAndDropDown();

		return TRUE;
	}

	return CGXControl::LButtonUp(nFlags, pt, nHitState);
}

void CGXTabbedComboBoxWnd::OnClickedButton(CGXChild* pChild)
{
	if (IsActive() || !m_bDropDownOnClick)
	{
		if (!IsActive())
		{
			if (!OnStartEditing())
				return;

			SetActive(TRUE);
			Refresh();
		}

		if (/*(GetStyle() & 0x03) == CBS_DROPDOWNLIST
			&&*/!GetDroppedState()
			&& !m_bDropDownOnClick)
		{
			m_bIgnoreNextDraw = TRUE;
			// if (GXGetAppData()->bWin4)
			{
				GridWnd()->UpdateWindow();

				// Workaround for Win95 Comboboxes,
				// because ShowDropDown(TRUE) does not work for some
				// reasons in this context.
				// (The listbox would be immediately hidden again).
				CRect rectCell = GetCellRect(m_nRow, m_nCol);
				CRect rectChild = m_pButton->GetRect();
				CPoint pt(rectChild.left-rectCell.left+5, rectChild.top-rectCell.top+5);

				PostMessage(WM_LBUTTONDOWN, MK_LBUTTON, MAKELONG(pt.x, pt.y));
				PostMessage(WM_LBUTTONUP, MK_LBUTTON, MAKELONG(pt.x, pt.y));
			}
			// else
			//  m_bDropDownOnNextSetFocus = TRUE;
				// OnSetFocus will call ShowDropDown(TRUE)
				// and reset m_bDropDownOnNextSetFocus.
		}
	}

	CGXControl::OnClickedButton(pChild);

	// Unused:
	pChild;
}


void CGXTabbedComboBoxWnd::SetActiveAndDropDown()
{
	if (!IsActive())
	{
		if (!OnStartEditing())
			return;

		SetActive(TRUE);
		Refresh();
	}

	if (/*(GetStyle() & 0x03) == CBS_DROPDOWNLIST
		&& */ !GetDroppedState()
		&& m_bDropDownOnClick)
	{
		if (GXGetAppData()->bWin4)
		{
			GridWnd()->UpdateWindow();

			// Workaround for Win95 Comboboxes,
			// because ShowDropDown(TRUE) does not work for some
			// reasons in this context.
			// (The listbox would be immediately hidden again).
			CRect rectCell = GetCellRect(m_nRow, m_nCol);
			CRect rectChild = m_pButton->GetRect();
			CPoint pt(rectChild.left-rectCell.left+5, rectChild.top-rectCell.top+5);

			PostMessage(WM_LBUTTONDOWN, MK_LBUTTON, MAKELONG(pt.x, pt.y));
			PostMessage(WM_LBUTTONUP, MK_LBUTTON, MAKELONG(pt.x, pt.y));
		}
		else
			m_bDropDownOnNextSetFocus = TRUE;
			// OnSetFocus will call ShowDropDown(TRUE)
			// and reset m_bDropDownOnNextSetFocus.
	}
}

BOOL CGXTabbedComboBoxWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT flags)
{
	BOOL bGrid = FALSE;

	Grid()->ScrollCellInView(m_nRow, m_nCol);

	if (GetKeyState(VK_CONTROL) & 0x8000)
	{
		bGrid = TRUE;
	}
	else
	{
		switch (nChar)
		{
		case VK_ESCAPE:
			if (GetDroppedState())
				ShowDropDown(FALSE);

			if (OnCancelEditing())
			{
				Init(m_nRow, m_nCol);
				Refresh();
				OnCanceledEditing();
				Grid()->SetIgnoreFocus(TRUE);
				GridWnd()->SetFocus();
				Grid()->SetIgnoreFocus(FALSE);

				return TRUE;
			}
			break;
		}
	}

	if (bGrid)
		return Grid()->ProcessKeys(this, WM_KEYDOWN, nChar, nRepCnt, flags);

	return  CGXComboBoxWnd::OnKeyDown(nChar, nRepCnt, flags);
}

CSize CGXTabbedComboBoxWnd::CalcSize(CDC* pDC, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle, BOOL bVert)
{
	// Unused:
	bVert, nRow, nCol;

	// User attributes
	int nDisplayCol = _ttoi(style.GetUserAttribute(GX_IDS_UA_TABLIST_TEXTCOL));
	BOOL bDisplayTitleRow = _ttoi(style.GetUserAttribute(GX_IDS_UA_TABLIST_TITLEROW));

	// Select font
	CFont* pOldFont = LoadFont(pDC, style, pStandardStyle);

	// Determine current size of cell (and take care if cell
	// is a covered cell
	CSize size;

	// BLOCK
	{
		TEXTMETRIC    tm;
		pDC->GetTextMetrics(&tm);
		int height = tm.tmHeight + tm.tmExternalLeading + 1;
		int width = 0;

		if (m_bFillWithChoiceList)
		{
			CSize sz;

			TCHAR szDisplayText[128];

			// check each item
			if (style.GetIncludeChoiceList())
			{
				CString s = style.GetChoiceListRef();
				int n = 0;
				CString sItem;

				if (bDisplayTitleRow)
					n = GXGetNextLine(s, sItem);

				while (!s.IsEmpty() && n != -1)
				{
					n = GXGetNextLine(s, sItem);

					GXGetColString(sItem, nDisplayCol, szDisplayText, 127);

					// TRACE1("sItem %s\n", (LPCTSTR) sItem);
					CString str;
					HANDLE hbm = 0;
					hbm = GXGetDIBState()->GetPool()->LookupOrCreateDIB(szDisplayText);

					if (hbm)
					{
						CGXDIB dib;
						dib.Attach(hbm);
						sz = dib.GetSize();
						dib.Detach();
					}
					else
						sz = pDC->GetTextExtent(szDisplayText, (int)_tcslen(szDisplayText));

					width = max(width, sz.cx);
					height = max(height, sz.cy);
				}
			}
		}

		size.cx = width;
		size.cy = height;
	}

	if (pOldFont)
		pDC->SelectObject(pOldFont);

	return Grid()->AddBorders(size, style);
}

/////////////////////////////////////////////////////////////////////////////
// CGXTabbedCBEditWnd

CGXTabbedCBEditWnd::CGXTabbedCBEditWnd()
{
}

CGXTabbedCBEditWnd::~CGXTabbedCBEditWnd()
{
}

BEGIN_MESSAGE_MAP(CGXTabbedCBEditWnd, CEdit)
	//{{AFX_MSG_MAP(CGXTabbedCBEditWnd)
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGXTabbedCBEditWnd message handlers

void CGXTabbedCBEditWnd::OnKillFocus(CWnd* pNewWnd)
{
	CGXTabbedComboBoxWnd* pParent = (CGXTabbedComboBoxWnd*) GetParent();
	ASSERT(pParent->CGXControl::IsKindOf(CONTROL_CLASS(CGXComboBoxWnd)));

	CEdit::OnKillFocus(pNewWnd);

	// TRACE0("CGXTabbedCBEditWnd::OnKillFocus()\n");

	if (pNewWnd != pParent && (pNewWnd == NULL || !pParent->IsChild(pNewWnd)))
		pParent->SendMessage(WM_KILLFOCUS, (WPARAM) pNewWnd->GetSafeHwnd(), 0);
}

void CGXTabbedCBEditWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CGXTabbedComboBoxWnd* pParent = (CGXTabbedComboBoxWnd*) GetParent();
	ASSERT(pParent->CGXControl::IsKindOf(CONTROL_CLASS(CGXComboBoxWnd)));

	// TRACE("CGXTabbedCBEditWnd::OnKeyDown(%u)\n", nChar);

	if (!pParent->OnKeyDown(nChar, nRepCnt, nFlags))
		CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}

LRESULT CGXTabbedCBEditWnd::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	// Cut Text right of a TAB character
	case WM_SETTEXT:

		LPTSTR  pTab;

		pTab = _tcschr((LPTSTR)lParam , _T('\t'));

		if (pTab)
		{
			pTab = (LPTSTR)lParam;

			int i;
			for(i = 0; i < 255; i++)
			{
				if (pTab[i] == _T('\t'))
				{
					pTab[i] = _T('\0');
					break;
				}
			}
		}
		break;
	}

	return CEdit::DefWindowProc(message, wParam, lParam);
}

void CGXTabbedCBEditWnd::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// Search the entry which fits to the char (like MS Access)
	CString     strText;
	CString     strLBText;
	int         iIndex;
	int         iSelStart;

	CGXTabbedComboBoxWnd* pParent = (CGXTabbedComboBoxWnd*) GetParent();
	ASSERT(pParent->CGXControl::IsKindOf(CONTROL_CLASS(CGXComboBoxWnd)));

	if (pParent->IsReadOnly())
		return;

	CString sEdit;
	GetWindowText(sEdit);

	int ns, ne;
	GetSel(ns, ne);

	CEdit::OnChar(nChar, nRepCnt, nFlags);

	// Is it an alphanumeric char
	if (_istprint((TCHAR) nChar))
	{
		GetWindowText(strText);

		// search text in CB
		iIndex = pParent->FindString(-1, strText);

		// if text found
		if (iIndex != CB_ERR)
		{
			iSelStart = strText.GetLength();

			// Get text from CB-list
			if (pParent->GetLBTextLen(iIndex) > 0)
				pParent->GetLBText(iIndex, strLBText);

			// Get display string
			TCHAR szValue[128];
			GXGetColString(strLBText, 0, szValue, 127);

			strText = szValue;

			SetWindowText(strText);

			// select to end of text
			SetSel(iSelStart, -1);
		}
		else
		{
			// Invalid input. Reset contents to previous state
			SetWindowText(sEdit);
			SetSel(ns, ne);
		}
	}
}

