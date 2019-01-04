///////////////////////////////////////////////////////////////////////////////
// gxclbox.cpp : implementation of the CGXListBox control
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

#ifndef _GXCORE_H_
#include "grid\gxcore.h"
#endif

#ifndef _GXCTRLI_H_
#include "grid\gxctrli.h"
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXCLBOX")
#endif

IMPLEMENT_DYNAMIC(CGXListBox, CListBox);
GRID_IMPLEMENT_CONTROL(CGXListBox, CGXControl);

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CGXListBox

CGXListBox::CGXListBox(CGXGridCore* pGrid, UINT nID)
	: CGXControl(pGrid)
{
	m_nID = nID;

	m_bIsActive = FALSE;
	m_bIsModify = FALSE;

	m_dyHeight = 0;
	m_rgbWndHilightText   = GetSysColor(COLOR_HIGHLIGHTTEXT);
}

CGXListBox::~CGXListBox()
{
	DestroyWindow();
}

CWnd* CGXListBox::GetWndPtr() const
{
	return (CWnd*) this;
}

BOOL CGXListBox::CreateControl()
{
#ifndef _UNICODE
	return CWnd::Create(_T("LISTBOX"), NULL, WS_HSCROLL | WS_VSCROLL | LBS_NOTIFY, CRect(0, 0, 0, 0), GridWnd(), m_nID);
#else
	return CWnd::Create(_T("GXLISTBOX"), NULL, WS_HSCROLL | WS_VSCROLL | LBS_NOTIFY, CRect(0, 0, 0, 0), GridWnd(), m_nID);
#endif
}

BEGIN_MESSAGE_MAP(CGXListBox, CListBox)
	//{{AFX_MSG_MAP(CGXListBox)
	ON_WM_GETDLGCODE()
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_CHAR()
	ON_WM_SYSCHAR()
	ON_WM_SYSKEYDOWN()
	ON_WM_SYSKEYUP()
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// Status
void CGXListBox::SetActive(BOOL bActive)
{
	if (!m_bIsActive && bActive && m_hWnd)
	{				 
		m_bIsActive = TRUE;
		// Force a call to GetStyleRowCol() because
		// GetStyleRowCol() might set style attributes
		// depending on the IsActive() flag
		FreeStyle();
		NeedStyle();
	}
	else
		m_bIsActive = bActive && m_hWnd;
}

BOOL CGXListBox::IsActive()
{
	return m_bIsActive;
}

void CGXListBox::SetModify(BOOL bModified)
{
	m_bIsModify = bModified;
}

BOOL CGXListBox::GetModify()
{
	return m_bIsModify;
}

void CGXListBox::GetCurrentText(CString& strResult)
{
	if (IsActive())
	{
		int nIndex = GetCurSel();

		CString s;
		if (nIndex != LB_ERR)
			GetText(nIndex, strResult);
		else
			strResult.Empty();
	}
	else
		CGXControl::GetCurrentText(strResult);
}

void CGXListBox::SetCurrentText(const CString& str)
{
	if (!IsInit())
		return;

	if (!IsActive())
		SetActive(TRUE);

	if (ValidateString(str))
	{
		SetWindowText(str);
		SetModify(TRUE);
		OnModifyCell();
	}
}

// Operations
void CGXListBox::Init(ROWCOL nRow, ROWCOL nCol)
{
	// Stores the cell coordinates, resets the style and sets the window text
	CGXControl::Init(nRow, nCol);

	if (!m_hWnd)
		CreateControl();    // creates the window

	NeedStyle();

	SetActive(FALSE);
	SetModify(FALSE);
}

void CGXListBox::FillListBox()
{
	const CGXStyle& style = Grid()->LookupStyleRowCol(m_nRow, m_nCol);

	ResetContent();

	// fill with ChoiceList
	if (style.GetIncludeChoiceList())
	{
		CString s = style.GetChoiceListRef();
		CString sItem;
		int n = 0;
		while (!s.IsEmpty() && n != -1)
		{
			n = GXGetNextLine(s, sItem);
			AddString(sItem);
		}
	}

	// Select item
	CString sOutput;
	if (GetControlText(sOutput, m_nRow, m_nCol, NULL, style)
		&& _tcslen(sOutput) > 0)
	{
		SelectString(-1, sOutput);
	}
}

CSize CGXListBox::CalcSize(CDC* pDC, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle, BOOL bVert)
{
	int nyHeight = 0, nxWidth = 0;

	// Select font
	CFont* pOldFont = LoadFont(pDC, style, pStandardStyle);

	// fill with ChoiceList
	if (style.GetIncludeChoiceList())
	{
		CString s = style.GetChoiceListRef();
		int n = 0;
		CString sItem;
		while (!s.IsEmpty() && n != -1)
		{
			n = GXGetNextLine(s, sItem);

			CSize size = pDC->GetTextExtent(sItem, sItem.GetLength());
			nxWidth = max(nxWidth, size.cx);
			nyHeight += size.cy;
		}
	}

	if (pOldFont)
		pDC->SelectObject(pOldFont);

	// unused parameters:
	bVert, nRow, nCol;

	return AddBorders(CSize(nxWidth + 4, nyHeight + 4), style);
}

BOOL CGXListBox::Store()
{
	// Calls SetStyleRange() and resets the modify flag
	ASSERT(m_pStyle);

	if (IsReadOnly())
	{
		Init(m_nRow, m_nCol);
		SetModify(FALSE);
		Refresh();
	}

	SetActive(FALSE);

	if (m_pStyle && GetModify())
	{
		int nIndex = GetCurSel();

		CString s;
		if (nIndex != LB_ERR)
			GetText(nIndex, s);

		return Grid()->SetValueRange(
			CGXRange(m_nRow, m_nCol),
			s,
			gxOverride,
			0, GX_INVALIDATE);
			// Cell will be automatically redrawn inactive
	}
	return TRUE;
}

CRect CGXListBox::GetCellRect(ROWCOL nRow, ROWCOL nCol, LPRECT rectItem /* = NULL */, const CGXStyle* pStyle /*= NULL*/)
{
	// compute the interior rectangle for the text
	// without buttons and borders

	CRect rect = CGXControl::GetCellRect(nRow, nCol, rectItem, pStyle);

	// On the top and on the left side is the Grid-Line (1pt)!
	// Put the appropriate Values here (these are for normal Text-Cells)
	int xFrame = max(GetSystemMetrics(SM_CXFRAME)/2, 2);

	rect.left += xFrame;
	rect.right -= xFrame/2;

	return rect;
}

CSize CGXListBox::AddBorders(CSize size, const CGXStyle& style)
{
	// On the top and on the left side is the Grid-Line (1pt)!
	// Put the appropriate Values here (these are for normal Text-Cells)
	int xFrame = max(GetSystemMetrics(SM_CXFRAME)/2, 2);

	// this is the counterpart to GetCellRect

	size.cx += xFrame;
	size.cx += xFrame/2;

	return Grid()->AddBorders(size, style);
}

void CGXListBox::Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle)
{
	ASSERT(pDC != NULL && pDC->IsKindOf(RUNTIME_CLASS(CDC)));
	// ASSERTION-> Invalid Device Context ->END
	ASSERT(nRow <= Grid()->GetRowCount() && nCol <= Grid()->GetColCount());
	// ASSERTION-> Cell coordinates out of range ->END

	// Notes on Draw:
	// if (nRow == m_nRow && nCol == m_nCol && m_bIsActive)
	//     initialize CWnd, make it visible and set focus
	// else {
	//     draw items with DrawText
	// }

	ASSERT_VALID(pDC);

	// if (nRow == m_nRow && nCol == m_nCol && m_bIsActive)
	//     initialize CWnd, make it visible and set focus
	if (nRow == m_nRow && nCol == m_nCol && IsActive() && !Grid()->IsPrinting())
	{
		// ------------------ Active Window ---------------------------

		Hide();

		SetModify(TRUE);

		// Font
		if (m_font.GetSafeHandle())
			m_font.DeleteObject();

		CGXFont font(m_pStyle->GetFontRef());
		font.SetSize(font.GetSize()*Grid()->GetZoom()/100);
		font.SetOrientation(0);

		// no vertical font for editing the cell
		const LOGFONT& _lf = font.GetLogFontRef();
		if ( !m_font.CreateFontIndirect(&_lf) )
		{
			TRACE1("Failed to create font '%s' in CGXListBox::Draw\n",
				(LPCTSTR) m_pStyle->GetFontRef().GetDescription());
		}

		// Cell-Color
		COLORREF rgbText = m_rgbWndHilightText;
		COLORREF rgbCell = m_pStyle->GetInteriorRef().GetColor();

		if (Grid()->GetParam()->GetProperties()->GetBlackWhite())
		{
			rgbText = RGB(0,0,0);
			rgbCell = RGB(255,255,255);
		}

		// Background + Frame
		DrawBackground(pDC, rect, style, TRUE);

		CRect rectText = GetCellRect(nRow, nCol, rect);

		DWORD ntAlign = m_pStyle->GetHorizontalAlignment() | m_pStyle->GetVerticalAlignment();

		if (ntAlign & DT_RIGHT)
			rectText.right++;

		MoveWindow(rectText, FALSE);
		m_rgbCell = rgbCell;

		SetCellColor(rgbCell);

		SetFont(&m_font);

		SetActive(TRUE);

		FillListBox();

		// Call MoveWindow once more after listbox has been filled
		// with entries.
		MoveWindow(rectText, FALSE);

		ShowWindow(SW_SHOW);

		if (nRow > Grid()->GetFrozenRows() && (Grid()->GetTopRow() > nRow 
			|| nCol > Grid()->GetFrozenCols() && Grid()->GetLeftCol() > nCol))
		// Ensure that the window cannot draw outside the clipping area!
		{
			CRect rectClip;
			if (pDC->GetClipBox(&rectClip) != ERROR)
			{
				CRect r = rect & Grid()->GetGridRect();
				GridWnd()->ClientToScreen(&r);
				ScreenToClient(&r);
				GridWnd()->ClientToScreen(&rectClip);
				ScreenToClient(&rectClip);
				ValidateRect(r); 
				InvalidateRect(rectClip); 
			}
		}

		UpdateWindow();

		if (GetFocus() == GridWnd())
			SetFocus();

		// child Controls: spin-buttons, hotspot, combobox btn, ...
		CGXControl::Draw(pDC, rect, nRow, nCol, *m_pStyle, pStandardStyle);

		ExcludeClipRect(rectText);
	}
	else
	// else {
	//     lookup style and draw static:
	//     - edit control with GXDrawTextLikeMultiLineEdit
	// }
	{

		// ------------------ Static Text ---------------------------

		// Rectangle
		CRect rectItem = rect;

		if (rect.right <= rect.left || rect.Width() <= 1 || rect.Height() <= 1)
			return;

		// Select font
		CFont* pOldFont = LoadFont(pDC, style, pStandardStyle);

		// Cell-Color
		COLORREF rgbText = style.GetTextColor();
		COLORREF rgbCell = style.GetInteriorRef().GetColor();

		if (Grid()->GetParam()->GetProperties()->GetBlackWhite())
		{
			rgbText = RGB(0,0,0);
			rgbCell = RGB(255,255,255);
		}

		DrawBackground(pDC, rect, style);

		pDC->SetBkMode(TRANSPARENT);
		pDC->SetBkColor(rgbCell);
		pDC->SetTextColor(rgbText);

		DWORD dtAlign = DT_SINGLELINE
			| style.GetHorizontalAlignment()
			| style.GetVerticalAlignment();

		CRect rectText = GetCellRect(nRow, nCol, rect, &style);

		TEXTMETRIC tm;
		pDC->GetTextMetrics(&tm);
		int dyHeight = tm.tmHeight + tm.tmExternalLeading;

		rectText.bottom = rect.top + dyHeight;
		rectText.left += 2;

		CString strValue;
		if (style.GetIncludeValue())
			strValue = style.GetValueRef();

		// find selected item
		if (style.GetIncludeChoiceList())
		{
			int nLine = 0, nSelLine = -1, nFirstLineVisible = 0;
			CRect rectTemp = rectText;
			CString s = style.GetChoiceListRef();
			int n = 0;
			while (!s.IsEmpty() && n != -1)
			{
				CString sItem;
				n = GXGetNextLine(s, sItem);

				if (strValue == sItem)
					nSelLine = nLine;

				rectTemp = rectTemp + CPoint(0, dyHeight);

				if (rectTemp.bottom > rect.bottom)
				{
					if (nSelLine == -1)
						nFirstLineVisible++;
					else
						break;
				}

				nLine++;
			}

			if (nSelLine == -1)
				nFirstLineVisible = 0;

			nLine = 0;
			n = 0;
			s = style.GetChoiceListRef();
			while (!s.IsEmpty() && n != -1)
			{
				CString sItem;
				n = GXGetNextLine(s, sItem);

				if (nLine >= nFirstLineVisible)
				{
					GXDrawTextLikeMultiLineEdit(pDC, sItem, sItem.GetLength(), rectText, (UINT) dtAlign);
					if (strValue == sItem)
						pDC->InvertRect(rectText);

					rectText = rectText + CPoint(0, dyHeight);
					if (rectText.bottom > rect.bottom)
						break;
				}
				nLine++;
			}
		}

		CGXControl::Draw(pDC, rect, nRow, nCol, style, pStandardStyle);

		if (pOldFont)
			pDC->SelectObject(pOldFont);
	}
}

void CGXListBox::Hide()
{
	// Hides the CEdit without changing the m_bIsActive flag
	// and without invalidating the screen
	HideCaret();
	MoveWindow0(FALSE);
	ShowWindow(SW_HIDE);
}

// Mouse hit
BOOL CGXListBox::LButtonUp(UINT nFlags, CPoint pt, UINT nHitState)
{
	// Unreferenced:
	nFlags, pt, nHitState;

	if (!(nHitState & GX_SELECT) && (Grid()->GetParam()->GetActivateCellFlags() &
		(GX_CAFOCUS_CLICKINTEXT|GX_CAFOCUS_CLICKONCELL|GX_CAFOCUS_SETCURRENT)) > 0)
	{
		if (!OnStartEditing())
			return FALSE;

		SetActive(TRUE);
		Refresh();

		// emulate mouse message for CListBox
		{
			CRect r = GetCellRect(m_nRow, m_nCol);
			PostMessage(WM_LBUTTONDOWN, nFlags, MAKELONG(pt.x-r.left, pt.y-r.top));
			PostMessage(WM_LBUTTONUP, nFlags, MAKELONG(pt.x-r.left, pt.y-r.top));
		}

		// check child buttons
		CGXControl::LButtonUp(nFlags, pt, nHitState);
	}

	return TRUE;
}

BOOL CGXListBox::LButtonDblClk(UINT nFlags, CPoint pt)
{
	// Sets the caret position
	if (!IsActive() && (Grid()->GetParam()->GetActivateCellFlags() &
		GX_CAFOCUS_DBLCLICKONCELL) > 0)
	{
		if (!OnStartEditing())
			return FALSE;

		SetActive(TRUE);
		Refresh();

		// emulate mouse message for CListBox
		{
			CRect r = GetCellRect(m_nRow, m_nCol);
			PostMessage(WM_LBUTTONDOWN, nFlags, MAKELONG(pt.x-r.left, pt.y-r.top));
			PostMessage(WM_LBUTTONUP, nFlags, MAKELONG(pt.x-r.left, pt.y-r.top));
		}

		// check child buttons
		CGXControl::LButtonDblClk(nFlags, pt);

		return TRUE;
	}

	return CGXControl::LButtonDblClk(nFlags, pt);
}

// Keyboard
BOOL CGXListBox::KeyPressed(UINT nMessage, UINT nChar, UINT nRepCnt, UINT flags)
{
	// Called when the user presses a key on the inactive current cell
	// functionality:
	//    - set active

	nChar, nRepCnt, flags;

	NeedStyle();

	if (nMessage == WM_KEYDOWN)
	{
		if (!OnStartEditing())
			return FALSE;

		SetActive(TRUE);
	}
	else
		return FALSE;

	CGXControl::KeyPressed(nMessage, nChar, nRepCnt, flags);

	if (!Grid()->ScrollCellInView(m_nRow, m_nCol))
		Refresh();

	return TRUE;
}

void CGXListBox::SetCellColor(COLORREF rgb)
{
	m_rgbCell = rgb;
}

void CGXListBox::OnKillFocus(CWnd* pNewWnd)
{
	CListBox::OnKillFocus(pNewWnd);
	CGXControl::OnKillFocus(pNewWnd);
}

BOOL CGXListBox::OnCommand(WPARAM wParam, LPARAM lParam)
{
#if _MFC_VER < 0x0300
	UINT nNotification = HIWORD(lParam);
	HWND hCtl = (HWND) LOWORD(lParam);
#else
	UINT nNotification = HIWORD(wParam);
	HWND hCtl = (HWND) lParam;
#endif

	if (hCtl == m_hWnd)
	{
		if (nNotification == LBN_SELCHANGE)
		{
			if (!IsReadOnly())
			{
				SetModify(TRUE);
				OnModifyCell();
			}
		}
	}

	return CGXControl::OnCommand(wParam, lParam);
}

UINT CGXListBox::OnGetDlgCode()
{
	return CListBox::OnGetDlgCode() | DLGC_WANTTAB | DLGC_WANTARROWS | DLGC_WANTCHARS;
}

void CGXListBox::OnKeyDown(UINT nChar, UINT nRepCnt, UINT flags)
{
	BOOL bGrid = FALSE,     // TRUE if Grid()->ProcessKeys should be called
		 bEdit = TRUE;      // TRUE if CEdit::OnChar() should be called
		 // If both values are TRUE, CEdit::OnChar() will only be
		 // called if Grid()->ProcessKeys returned FALSE

	Grid()->ScrollCellInView(m_nRow, m_nCol);

	if (GetKeyState(VK_CONTROL) & 0x8000)
	{
		bGrid = TRUE;
		bEdit = FALSE;
	}
	else
	{
		switch (nChar)
		{
		case VK_F1:
		case VK_F2:
		case VK_F3:
		case VK_F4:
		case VK_F5:
		case VK_F6:
		case VK_F7:
		case VK_F8:
		case VK_F9:
		case VK_F10:
		case VK_F11:
		case VK_F12:
		case VK_F13:
		case VK_F14:
		case VK_F15:
		case VK_F16:
		case VK_F17:
		case VK_F18:
		case VK_F19:
		case VK_F20:
		case VK_F21:
		case VK_F22:
		case VK_F23:
		case VK_F24:
		case VK_ESCAPE:
		case VK_RIGHT:
		case VK_LEFT:
		case VK_RETURN:
		case VK_TAB:
		case VK_DELETE:
			bGrid = TRUE; bEdit = FALSE;
			break;
		case VK_DOWN:
		case VK_UP:
		case VK_HOME:
		case VK_END:
			bGrid = FALSE;
			bEdit = TRUE;
			break;
		}
	}

	if (bGrid)
		bEdit &= !Grid()->ProcessKeys(this, WM_KEYDOWN, nChar, nRepCnt, flags);

	if (bEdit)
	{
		CListBox::OnKeyDown(nChar, nRepCnt, flags);
	}
}

void CGXListBox::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!Grid()->ProcessKeys(this, WM_KEYUP, nChar, nRepCnt, nFlags))
		CListBox::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CGXListBox::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!Grid()->ProcessKeys(this, WM_CHAR, nChar, nRepCnt, nFlags))
		CListBox::OnChar(nChar, nRepCnt, nFlags);
}

void CGXListBox::OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!Grid()->ProcessKeys(this, WM_SYSCHAR, nChar, nRepCnt, nFlags))
		CListBox::OnSysChar(nChar, nRepCnt, nFlags);
}

void CGXListBox::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!Grid()->ProcessKeys(this, WM_SYSKEYDOWN, nChar, nRepCnt, nFlags))
		CListBox::OnSysKeyDown(nChar, nRepCnt, nFlags);
}

void CGXListBox::OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!Grid()->ProcessKeys(this, WM_SYSKEYUP, nChar, nRepCnt, nFlags))
		CListBox::OnSysKeyUp(nChar, nRepCnt, nFlags);
}

BOOL CGXListBox::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	GetClientRect(rect);

	// GXPatB(pDC, rect.left, rect.top, rect.Width(), rect.Height(), m_rgbCell);
	GXPatB(pDC, rect, RGB(255,255,255));
	if (m_pStyle)
		pDC->FillRect(rect, Grid()->LookupOrCreateBrush(m_pStyle->GetInteriorRef()));

	return TRUE;
}
