///////////////////////////////////////////////////////////////////////////////
// gxccbwnd.cpp : implementation of the CGXComboBoxWnd control
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
#pragma code_seg("GX_SEG_GXCCBWND")
#endif

IMPLEMENT_DYNAMIC(CGXComboBoxWnd, CComboBox);
GRID_IMPLEMENT_CONTROL(CGXComboBoxWnd, CGXStatic);

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif



// It is necessary to subclass the edit portion
// of the combobox, so that arrow keys can be processed
// in the virtual CGXComboBoxWnd::OnKeyDown message.
//
// If you want to process key messages for the combobox,
// you should override the virtual OnKeyDown() method
// and return TRUE.
//

/////////////////////////////////////////////////////////////////////////////
// CGXComboEditPart

CGXComboEditPart::CGXComboEditPart()
{
}

CGXComboEditPart::~CGXComboEditPart()
{
}


BEGIN_MESSAGE_MAP(CGXComboEditPart, CEdit)
	//{{AFX_MSG_MAP(CGXComboEditPart)
	ON_WM_KILLFOCUS()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGXComboEditPart message handlers

void CGXComboEditPart::OnKillFocus(CWnd* pNewWnd)
{
	CGXComboBoxWnd* pParent = (CGXComboBoxWnd*) GetParent();
	ASSERT(pParent->CGXControl::IsKindOf(CONTROL_CLASS(CGXComboBoxWnd)));

	CEdit::OnKillFocus(pNewWnd);

	// TRACE0("CGXComboEditPart::OnKillFocus()\n");

	if (pNewWnd != pParent && (pNewWnd == NULL || !pParent->IsChild(pNewWnd)))
		pParent->SendMessage(WM_KILLFOCUS, (WPARAM) pNewWnd->GetSafeHwnd(), 0);
}

void CGXComboEditPart::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CGXComboBoxWnd* pParent = (CGXComboBoxWnd*) GetParent();
	ASSERT(pParent->CGXControl::IsKindOf(CONTROL_CLASS(CGXComboBoxWnd)));

	// TRACE0("CGXComboEditPart::OnKeyDown(%u)\n", nChar);

	if (!pParent->OnKeyDown(nChar, nRepCnt, nFlags))
		CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}

/////////////////////////////////////////////////////////////////////////////
// CGXComboBoxWnd

const int nComboBtnWidth = 15;
const int nComboBtnHeight = 18;

CGXComboBoxWnd::CGXComboBoxWnd(CGXGridCore* pGrid)
	: CGXStatic(pGrid)
{
	// public attributes which define some behavior of the combobox

	if (GXGetAppData()->bWin4)
		m_nExtraFrame = 3;  // extra frame for combobox in cell
	else
		m_nExtraFrame = 2;

	m_bFillWithChoiceList = TRUE;
	m_bWantArrowKeys = FALSE;
	m_bSizeToContent = FALSE;
	m_nIndexValue = -1;
	m_bDispChoice = FALSE;
	m_bDropDownOnClick = TRUE;
	m_bInactiveDrawAllCell = TRUE; // draw text over pushbutton when inactive
	m_bInactiveDrawButton = FALSE;  // draw pushbutton when inactive

	// internal attributes
	m_bIsActive = FALSE;
	m_bModified = FALSE;
	m_rgbWndHilightText   = GetSysColor(COLOR_HIGHLIGHTTEXT);
	m_bDropDownOnNextSetFocus = FALSE;
	m_bRefreshOnSetCurrentCell = TRUE;
	m_nDefaultHeight = 0;
	m_bDraw3dFrame = TRUE;  // draw 3d frame for ownerdrawn combobox
	m_bForceInsideCell = FALSE; // set this parameter TRUE if you do not
		// want that the active combobox overlaps neighbouring cells
	m_bFindTextSupported = TRUE;
}

CGXComboBoxWnd::~CGXComboBoxWnd()
{
	DestroyWindow();
}

CWnd* CGXComboBoxWnd::GetWndPtr() const
{
	return (CWnd*) this;
}

// Comment: added code for subclassing edit portion of combobox.
// undef the SubclassWindow macro
#ifdef SubclassWindow
#undef SubclassWindow
#endif

BOOL CGXComboBoxWnd::Create(DWORD dwStyle, UINT nID)
{
	AddChild(m_pButton = new CGXComboBoxWndButton(this));

	// return CComboBox::Create(dwStyle, CRect(0, 0, 0, 0), GridWnd(), nID);
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
			// CGXComboEditPart class
			m_wndEdit.SubclassWindow(pEdit->GetSafeHwnd());
		}
	}

	m_bFindTextSupported = !(GetStyle() & (CBS_OWNERDRAWFIXED | CBS_OWNERDRAWVARIABLE));

	return b;
}

BEGIN_MESSAGE_MAP(CGXComboBoxWnd, CComboBox)
	//{{AFX_MSG_MAP(CGXComboBoxWnd)
	ON_WM_ERASEBKGND()
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// Status
void CGXComboBoxWnd::SetActive(BOOL bActive)
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

BOOL CGXComboBoxWnd::IsActive()
{
	return m_bIsActive;
}

void CGXComboBoxWnd::SetModify(BOOL bModified)
{
	m_bModified = bModified;
}

BOOL CGXComboBoxWnd::GetModify()
{
	return m_bModified;
}

CRect CGXComboBoxWnd::GetCellRect(ROWCOL nRow, ROWCOL nCol, LPRECT rectItem /* = NULL */, const CGXStyle* pStyle /*= NULL*/)
{
	// compute the interior rectangle for the text
	// without buttons and borders

	CRect rect = CGXControl::GetCellRect(nRow, nCol, rectItem, pStyle);

	BOOL bCCell = Grid()->IsCurrentCell(nRow, nCol);

	if (// current cell drawn as static text with button
		bCCell && !IsActive()
		// not current cell but shall keep space for button
		// when m_bInactiveDrawAllCell is FALSE or
		// m_bInactiveDrawButton is TRUE
		|| !bCCell && (!m_bInactiveDrawAllCell || m_bInactiveDrawButton))
		rect.right -= nComboBtnWidth;

	if (!bCCell || !IsActive())
		rect.left += 2;  // 2 pixel frame at left

	return rect;
}

CSize CGXComboBoxWnd::AddBorders(CSize size, const CGXStyle& style)
{
	size.cx += nComboBtnWidth + 4; // some extra pixels because active cells
								   // have a larger button

	return CGXStatic::AddBorders(size, style);
}

void CGXComboBoxWnd::OnInitChildren(ROWCOL nRow, ROWCOL nCol, const CRect& rect)
{
	nRow, nCol;

	if (m_pButton)
	{
		int dy = rect.Height();

		// initialize combobox button only if
		// not the current cell
		CRect rectBtn(
				max(rect.left+1, rect.right-1-nComboBtnWidth),
				rect.top,
				rect.right-1,
				rect.top + dy -1);

		if (m_bSizeToContent)
		{
			// Determine the default height for the combobox edit part
			const CGXStyle* pStyle = NULL;
			if (IsInit() && m_nRow == nRow && m_nCol == nCol)
			{
				NeedStyle();
				pStyle = m_pStyle;
			}
			else if (m_bInactiveDrawButton)
				pStyle = &Grid()->LookupStyleRowCol(nRow, nCol);

			if (pStyle)
			{
				if (m_nDefaultHeight == 0)
				{
					// Get font metrics
					TEXTMETRIC tm;
					CClientDC dc(GridWnd());
					Grid()->OnGridPrepareDC(&dc);
					CFont* pOldFont = Grid()->LoadFont(&dc, *pStyle);
					dc.GetTextMetrics(&tm);
					if (pOldFont)
						dc.SelectObject(pOldFont);

					m_nDefaultHeight = tm.tmHeight;
				}

				int dy = min(m_nDefaultHeight+2, rect.Height() - 2*m_nExtraFrame);

				if (pStyle->GetIncludeVerticalAlignment())
				{
					// vertical alignment for single line text
					// is done by computing the window rectangle for the CComboBox
					switch (pStyle->GetVerticalAlignment())
					{
					case DT_VCENTER:
						rectBtn.top += (rect.Height() - dy) / 2 - m_nExtraFrame;
						break;
					case DT_BOTTOM:
						rectBtn.top = rect.bottom - dy - 2 * m_nExtraFrame;
					break;
					}
				}
			}

			rectBtn.bottom = rectBtn.top + dy + 2*m_nExtraFrame;
			rectBtn.bottom--;
		}

		m_pButton->SetRect(rectBtn);
	}
}

// Operations
void CGXComboBoxWnd::Init(ROWCOL nRow, ROWCOL nCol)
{
	// Stores the cell coordinates, resets the style and sets the window text
	m_nDefaultHeight = 0;   // Force OnInitChildren to determine font height
	CGXStatic::Init(nRow, nCol);

	m_bDropDownOnNextSetFocus = FALSE;
	m_nStartChar = 0;
	m_nEndChar = -1;
	SetEditSel(0, -1);   // Select all

	SetActive(FALSE);
	NeedStyle();

	// check if we need to fill combobox with the choice list
	if (m_bFillWithChoiceList)
	{
		ResetContent();

		// fill with Choices
		if (m_pStyle->GetIncludeChoiceList())
		{
			CString s = m_pStyle->GetChoiceListRef();
			CString sItem;
			int n = 0;
			while (!s.IsEmpty() && n != -1)
			{
				n = GXGetNextLine(s, sItem);
				AddString(sItem);
			}
		}
	}

	// set current selection
	SetValue(m_pStyle->GetValueRef());

	if (Grid()->GetParam()->GetActivateCellFlags() & GX_CAFOCUS_SETCURRENT && OnStartEditing())
		SetActive(TRUE);

	SetModify(FALSE);

	// Force drawing of buttons for current cell
	if (!IsActive() && m_pButton)
		GridWnd()->InvalidateRect(m_pButton->GetRect());
}


void CGXComboBoxWnd::GetWindowText(CString& rString) const
{
	int nIndex;

	if ((GetStyle() & 0x03) == CBS_DROPDOWN
		&& GetWindowTextLength() > 0)
	{
		CComboBox::GetWindowText(rString);
	}
	else if ((nIndex = GetCurSel()) != CB_ERR)
	{
		GetLBText(nIndex, rString);
	}
	else
		rString.Empty();
}

void CGXComboBoxWnd::GetCurrentText(CString& strResult)
{
	strResult.Empty();

	// get the string for the current selected item
	if (IsInit())
		GetWindowText(strResult);
}

void CGXComboBoxWnd::SetCurrentText(const CString& str)
{
	if (!IsInit())
		return;

	if (!IsActive())
		SetActive(TRUE);

	if (ValidateString(str))
	{
		if ((GetStyle() & 0x03) == CBS_DROPDOWN)
			SetWindowText(str);
		else
			SelectString(-1, str);
		SetModify(TRUE);
		OnModifyCell();
	}
}

BOOL CGXComboBoxWnd::ValidateString(const CString& sEdit)
{
	if (sEdit.IsEmpty())
		return TRUE;

	BOOL bValid = TRUE;

	if (m_bFillWithChoiceList && m_nIndexValue != -1 && m_bDispChoice)
	{
		if (m_pStyle->GetIncludeChoiceList() &&
			m_pStyle->GetChoiceListRef().GetLength() > 0)
		{
			CString sMatch;

			// finds exact string or the first string with the same prefix
			int nIndex = FindStringInChoiceList(sMatch, sEdit,
				m_pStyle->GetChoiceListRef(), FALSE);

			if (nIndex == -1)
				bValid = FALSE;
		}
		else
			bValid = FALSE;
	}

	return bValid;
}

void CGXComboBoxWnd::SetValue(LPCTSTR pszRawValue)
{
	// Convert the value to the text which should be
	// displayed in the current cell and show this
	// text.

	int r = CB_ERR;

	// either set current selection
	if (m_nIndexValue != -1)
	{
		if (_tcslen(pszRawValue) > 0)
			r = SetCurSel(_ttoi(pszRawValue)-m_nIndexValue);
	}
	// or find closest match
	else if (_tcslen(pszRawValue) > 0)
	{
		// find the first list-box string that matches the
		//   string specified in lpszFind. 
		int nIndex = FindStringExact( -1, pszRawValue );

		// if the string was not found
		if ( nIndex == -1 )
		{
			// search the entire list box for pszRawValue
			r = SelectString( -1, pszRawValue );
		}
		
		// else, the string was found at nIndex
		else
		{
			// select the string at nIndex
			r = SetCurSel( nIndex );
		}
	}

	// if failed, try SetWindowText (will work only
	// with editable combobox).
	if (r == CB_ERR && (GetStyle() & 0x03) == CBS_DROPDOWN)
	{
		SetWindowText(pszRawValue);
		SetEditSel(0, -1);   // Select all
	}
}

BOOL CGXComboBoxWnd::GetValue(CString& sResult)
{
	if (!IsInit())
		return FALSE;

	if (m_nIndexValue != -1)
	{
		int n = GetCurSel();
		if (n >= 0)
		{
			n += m_nIndexValue;
			wsprintf(sResult.GetBufferSetLength(20), _T("%d"), n);
			sResult.ReleaseBuffer();
		}
		else
			sResult.Empty();

		return TRUE;
	}
	else
	{
		GetWindowText(sResult);

		return TRUE;
	}
}

BOOL CGXComboBoxWnd::GetControlText(CString& strResult, ROWCOL nRow, ROWCOL nCol, LPCTSTR pszRawValue, const CGXStyle& style)
{
	CString sItem;

	// First, we need to convert the raw value into an choice list entry
	// when CGXComboBox is used with GXCOMBO_DISPLAYCHOICE flag.
	if (m_nIndexValue != -1 && m_bDispChoice
		&& style.GetIncludeChoiceList()
		&& m_bFillWithChoiceList)
	{
		if (pszRawValue == NULL && style.GetIncludeValue())
			pszRawValue = style.GetValueRef();

		if (pszRawValue == NULL || _tcslen(pszRawValue) == 0)
			return FALSE;

		// determine index
		int nIndex = (short) _ttoi(pszRawValue);

		// the following operation needs a zero-based index
		if (nIndex != -1)
			nIndex -= m_nIndexValue;

		GetChoiceListItem(sItem, style.GetChoiceListRef(), nIndex);
			// base class version will format the text as specified in mask
		pszRawValue = sItem;
	}

	// Now, we can use this entry.
	return CGXControl::GetControlText(strResult, nRow, nCol, pszRawValue, style);
}

BOOL CGXComboBoxWnd::SetControlText(ROWCOL nRow, ROWCOL nCol, const CString& str, UINT nFlags, const CGXStyle* pOldStyle)
{
	 //note: if you want to allow deleting of a dropdownlist, just call the baseclass
     if ((GetStyle() & 0x03) == CBS_DROPDOWNLIST && str.IsEmpty() )
		return TRUE; // allow clearing to continue
	
	return CGXControl::SetControlText(nRow, nCol, str, nFlags, pOldStyle);	
}

BOOL CGXComboBoxWnd::ConvertControlTextToValue(CString& str, ROWCOL nRow, ROWCOL nCol, const CGXStyle* pOldStyle)
{
	CGXStyle* pStyle = NULL;

	BOOL bTextFit = m_nIndexValue != -1;
	BOOL bDispChoice = m_bDispChoice;
	int nIndexOffset = m_nIndexValue;

	// check if we need to convert to an index
	if (m_bFillWithChoiceList && (bTextFit || bDispChoice))
	{
		if (pOldStyle == NULL)
		{
			pStyle = Grid()->CreateStyle();
			Grid()->ComposeStyleRowCol(nRow, nCol, pStyle);
			pOldStyle = pStyle;
		}

		if (pOldStyle && pOldStyle->GetIncludeChoiceList())
		{
			CString sMatch;

			// finds exact string or the first string with the same prefix
			int nIndex = FindStringInChoiceList(sMatch, str,
				pOldStyle->GetChoiceListRef(), FALSE);

			if (bDispChoice)
			{
				if (nIndex != -1)
				{
					nIndex += nIndexOffset;
					wsprintf(str.GetBuffer(20), _T("%d"), nIndex);
					str.ReleaseBuffer();
				}
				else
					str.Empty();
			}
			else
				// assign the exact choice or the choice with the same prefix
				str = sMatch;
		}

		if (pStyle)
			Grid()->RecycleStyle(pStyle);
	}

	return TRUE;
}

BOOL CGXComboBoxWnd::Store()
{
	// Calls SetStyleRange() and resets the modify flag
	ASSERT(m_pStyle);

	if (IsReadOnly())
	{
		Init(m_nRow, m_nCol);
		SetModify(FALSE);
		Refresh();
	}

	CString sValue;
	if (m_pStyle && GetModify() && GetValue(sValue))
	{
		SetActive(FALSE);

		return Grid()->SetValueRange(
			CGXRange(m_nRow, m_nCol),
			sValue,
			gxOverride,
			0, GX_INVALIDATE);
			// Cell will be automatically redrawn inactive
	}

	return TRUE;
}

void CGXComboBoxWnd::Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle)
{
	ASSERT(pDC != NULL && pDC->IsKindOf(RUNTIME_CLASS(CDC)));
	// ASSERTION-> Invalid Device Context ->END
	ASSERT(nRow <= Grid()->GetRowCount() && nCol <= Grid()->GetColCount());
	// ASSERTION-> Cell coordinates out of range ->END

	// Notes on Draw:
	// if (nRow == m_nRow && nCol == m_nCol && m_bIsActive)
	//     initialize CWnd, make it visible and set focus
	// else {
	//     lookup style and draw static, e.g.:
	//     - text with GXDrawTextLikeMultiLineEdit
	//     - owner drawn combobox: trigger DrawItem
	// }

	ASSERT_VALID(pDC);

	// if (nRow == m_nRow && nCol == m_nCol && m_bIsActive)
	//     initialize CWnd, make it visible and set focus
	if (nRow == m_nRow && nCol == m_nCol && IsActive() && !Grid()->IsPrinting())
	{
		// ------------------ Active Window ---------------------------

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
			TRACE1("Failed to create font '%s' in CGXComboBoxWnd::Draw\n",
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

		CRect rectText = CGXControl::GetCellRect(nRow, nCol, rect);

		// Select font
		pOldFont = pDC->SelectObject(&m_font);

		TEXTMETRIC    tm;
		pDC->GetTextMetrics(&tm);

		if (pOldFont)
			pDC->SelectObject(pOldFont);

		SetCellColor(rgbCell);

		SetFont(&m_font);

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

		rectText.bottom += (tm.tmHeight + 2 + 2*m_nExtraFrame) * min(8, CComboBox::GetCount());

		// OnGetListboxRect() is a hook for enlarging the dropdown rectangle
		CRect listBoxRect = OnGetListboxRect(rectText);
		MoveWindow(listBoxRect, FALSE);
		m_rgbCell = rgbCell;

		SetActive(TRUE);

		if (GXGetAppData()->bWin4)
			SetItemHeight(-1, dy);
		else
			SetItemHeight(-1, dy+m_nExtraFrame);

		ShowWindow(SW_HIDE);

		if (GetFocus() == GridWnd())
		{
			Grid()->SetIgnoreFocus(TRUE);
			SetFocus();
			Grid()->SetIgnoreFocus(FALSE);
		}

		if (m_pStyle->GetIncludeMaxLength() && m_pStyle->GetMaxLength() > 0)
			LimitText((int) m_pStyle->GetMaxLength());

		SetEditSel(nStart, nEnd);

		ShowWindow(SW_SHOW);

		if (nRow > Grid()->GetFrozenRows() && (Grid()->GetTopRow() > nRow 
			|| nCol > Grid()->GetFrozenCols() && Grid()->GetLeftCol() > nCol))
		// Ensure that the window cannot draw outside the clipping area!
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
				ValidateRect(r); 
				InvalidateRect(rectClip); 
			}
		}

		UpdateWindow();

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

		if (GetStyle() & (CBS_OWNERDRAWFIXED | CBS_OWNERDRAWVARIABLE))
		{
			// Background + Frame
			DrawBackground(pDC, rect, style, TRUE);

			CRect r = CGXControl::GetCellRect(nRow, nCol, &rect, &style);

			if (m_bSizeToContent)
			{
				int dy = min(m_nDefaultHeight+2, r.Height() - 2 * m_nExtraFrame);

				if (style.GetIncludeVerticalAlignment())
				{
					// vertical alignment for single line text
					// is done by computing the window rectangle for the CComboBox
					switch (style.GetVerticalAlignment())
					{
					case DT_VCENTER:
						r.top += (r.Height() - dy) / 2 - m_nExtraFrame;
						break;
					case DT_BOTTOM:
						r.top = r.bottom - dy - 2 * m_nExtraFrame;
					break;
					}
				}

				r.bottom = r.top + dy + 2*m_nExtraFrame;
				r.bottom--;
			}

			UINT itemID;
			if (!style.GetIncludeValue() || _tcsclen(style.GetValueRef()) == 0)
				itemID = 0;
			else
				itemID = (UINT) _ttoi(style.GetValueRef());

			// trigger draw-notification
			DRAWITEMSTRUCT drawItemStruct;

			drawItemStruct.CtlType = ODT_COMBOBOX;
			drawItemStruct.CtlID = GetDlgCtrlID();
			drawItemStruct.itemID = itemID;
			drawItemStruct.itemAction = ODA_DRAWENTIRE;
			drawItemStruct.itemState = ODS_SELECTED;
			drawItemStruct.hwndItem = m_hWnd;
			drawItemStruct.hDC = pDC->GetSafeHdc();
			drawItemStruct.itemData = GetItemData(itemID);

			if (!Grid()->IsPrinting() &&
				(!style.GetIncludeDraw3dFrame() || style.GetDraw3dFrame() == gxFrameNormal)
				&& m_bDraw3dFrame)
			{
				GXDraw3dFrame(pDC, r.left, r.top, r.right-1, r.bottom-1, 1,
					  RGB(0,0,0), RGB(255,255,255));
				drawItemStruct.rcItem = CRect(r.left+2, r.top+2, r.right-2, r.bottom-2);
			}
			else
				drawItemStruct.rcItem = r;

			DrawItem(&drawItemStruct);
		}
		else
		{
			// ------------------ Static Text ---------------------------
			CGXStatic::Draw(pDC, rect, nRow, nCol, style, pStandardStyle);
		}
	}
}

CRect CGXComboBoxWnd::OnGetListboxRect(const CRect& rcCellRect)
{
	// override this method for example if you want to change
	// the height of the listbox.
    // With Common Controls 6, flag CBS_NOINTEGRALHEIGHT is needed in the style for control overriden
	// to get the height changed
    // pWnd->Create(WS_VSCROLL|CBS_DROPDOWN|CBS_NOINTEGRALHEIGHT, GX_IDS_CTRL_CBS_DROPDOWN);

	// NOTE: do not change the width of the rectangle!

	return rcCellRect;
}

CSize CGXComboBoxWnd::CalcSize(CDC* pDC, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle, BOOL bVert)
{
	if (GetStyle() & (CBS_OWNERDRAWFIXED | CBS_OWNERDRAWVARIABLE))
		return CSize(0,0);

	// Size of edit portion
	CSize sizeEdit = CGXStatic::CalcSize(pDC, nRow, nCol, style, pStandardStyle, bVert);

	// Determine size of listbox entries
	CSize sizeCombo(0, 0);  

	// Select font
	CFont* pOldFont = LoadFont(pDC, style, pStandardStyle);

	if (bVert)
	{
		// row height
		TEXTMETRIC    tm;
		pDC->GetTextMetrics(&tm);
		int dyHeight = tm.tmHeight + tm.tmExternalLeading + 1;

		if (!m_bForceInsideCell)
			sizeCombo.cy = dyHeight + 1;
		else
			sizeCombo.cy = dyHeight + 1 + 2 * m_nExtraFrame;
	}
	else
	{
		if (m_bFillWithChoiceList)
		{
			CSize sz;

			// check each item
			if (m_bFillWithChoiceList && style.GetIncludeChoiceList())
			{
				CString s = style.GetChoiceListRef();
				CString sItem;
				int n = 0;
				while (!s.IsEmpty() && n != -1)
				{
					n = GXGetNextLine(s, sItem);

					sz = pDC->GetTextExtent(sItem, sItem.GetLength());
					sizeCombo.cx = max(sizeCombo.cx, sz.cx);
				}
			}
		}
	}

	if (pOldFont)
		pDC->SelectObject(pOldFont);

	// Add space for borders, left and right margin, 3d frame etc.
	sizeCombo = AddBorders(sizeCombo, style);

	// Return the size which fits for both listbox entries and edit portion
	return CSize(max(sizeCombo.cx, sizeEdit.cx), max(sizeCombo.cy, sizeEdit.cy));
}

void CGXComboBoxWnd::Hide()
{
	// Hides the CComboBox without changing the m_bIsActive flag
	// and without invalidating the screen
	if (m_hWnd && IsWindowVisible())
	{
		Grid()->SetIgnoreFocus(TRUE);
		ShowDropDown(FALSE);
		HideCaret();
		ShowWindow(SW_HIDE);
		if (GetFocus() == &m_wndEdit)
			Grid()->GridWnd()->SetFocus();
		Grid()->SetIgnoreFocus(FALSE);
	}
}

// Mouse hit
BOOL CGXComboBoxWnd::LButtonUp(UINT nFlags, CPoint pt, UINT nHitState)
{
	// Sets the caret position
	if (!(nHitState & GX_SELECT) && (Grid()->GetParam()->GetActivateCellFlags() &
		(GX_CAFOCUS_CLICKINTEXT|GX_CAFOCUS_CLICKONCELL|GX_CAFOCUS_SETCURRENT)) > 0)
	{
		SetActiveAndDropDown();

		// check child buttons
		CGXControl::LButtonUp(nFlags, pt, nHitState);

		return TRUE;
	}

	return CGXControl::LButtonUp(nFlags, pt, nHitState);
}

BOOL CGXComboBoxWnd::LButtonDblClk(UINT nFlags, CPoint pt)
{
	// Sets the caret position
	if (!IsActive() && (Grid()->GetParam()->GetActivateCellFlags() &
		GX_CAFOCUS_DBLCLICKONCELL) > 0)
	{
		SetActiveAndDropDown();

		// check child buttons
		CGXControl::LButtonDblClk(nFlags, pt);

		return TRUE;
	}

	return CGXControl::LButtonDblClk(nFlags, pt);
}

void CGXComboBoxWnd::OnClickedButton(CGXChild* pChild)
{
	if (!IsActive()
		|| !((GetStyle() & 0x03) == CBS_DROPDOWNLIST)
		|| !m_bDropDownOnClick)
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

	CGXControl::OnClickedButton(pChild);

	// Unused:
	pChild;
}

void CGXComboBoxWnd::SetActiveAndDropDown()
{
	if (!IsActive())
	{
		if (!OnStartEditing())
			return;

		SetActive(TRUE);
		Refresh();
	}

	if ((GetStyle() & 0x03) == CBS_DROPDOWNLIST
		&& !GetDroppedState()
		&& m_bDropDownOnClick)
	{
		if (GXGetAppData()->bWin4)
		{
			GridWnd()->UpdateWindow();

			// Workaround for Win95 Comboboxes,
			// because ShowDropDown(TRUE) does not work for some
			// reasons in this context.
			// (The listbox would be immediately hidden again).
			PostMessage(WM_LBUTTONDOWN, MK_LBUTTON, MAKELONG(0, 0));
			PostMessage(WM_LBUTTONUP, MK_LBUTTON, MAKELONG(0, 0));
		}
		else
			m_bDropDownOnNextSetFocus = TRUE;
			// OnSetFocus will call ShowDropDown(TRUE)
			// and reset m_bDropDownOnNextSetFocus.
	}
}

// Keyboard

// called from CGXGridCore when current cell is incative
// (does not have the focus) and before CGXGridCore
// interpretes the key.

BOOL CGXComboBoxWnd::OnGridKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!m_hWnd)
		return FALSE;

	BOOL bProcessed = FALSE;

	BOOL bCtl = GetKeyState(VK_CONTROL) & 0x8000;
	//BOOL bShift = GetKeyState(VK_SHIFT) & 0x8000;
	//BOOL bAlt = GetKeyState(VK_MENU) & 0x8000;

	// Pass all CTRL keys to the grid
	if (!bCtl)
	{
		switch (nChar)
		{
		case VK_END:
			if (OnStartEditing())
			{
				if (!IsInit())
					Init(m_nRow, m_nCol);

				SetActive(TRUE);

				// position caret
				CString s;
				GetCurrentText(s);
				int nLen = (int)_tcslen(s);

				// position caret
				SetEditSel(nLen, nLen);

				bProcessed = TRUE;
			}
			break;

		case VK_HOME:
			if (OnStartEditing())
			{
				if (!IsInit())
					Init(m_nRow, m_nCol);

				SetActive(TRUE);

				// position caret
				SetEditSel(0, 0);

				bProcessed = TRUE;
			}
			break;
		}
	}

	if (bProcessed)
	{
		if (!Grid()->ScrollCellInView(m_nRow, m_nCol))
			Refresh();

		return TRUE;
	}

	return CGXControl::OnGridKeyDown(nChar, nRepCnt, nFlags);
}

BOOL CGXComboBoxWnd::OnGridSysKeyDown(UINT nChar, UINT nRepCnt, UINT flags)
{
	if (nChar == VK_DOWN)
	{
		// trigger OnStartEditing
		if (!OnStartEditing())
			return FALSE;

		SetActive(TRUE);

		// Redraw the cell
		if (!Grid()->ScrollCellInView(m_nRow, m_nCol))
			Refresh();

		GridWnd()->UpdateWindow();
		ShowDropDown(TRUE);

		return TRUE;
	}

	return CGXControl::OnGridSysKeyDown(nChar, nRepCnt, flags);
}

BOOL CGXComboBoxWnd::OnGridChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!m_hWnd)
		return FALSE;

	// is this a valid character (no Ctrl-Key)
	CString s = (TCHAR) nChar;

	// pass valid characters as string to OnGridDoubleByteChar
	if (nChar >= 0x020 && nChar != 0x7f)
		return OnGridDoubleByteChar((CString) (TCHAR) nChar, nRepCnt, nFlags);

	// default processing
	return CGXControl::OnGridChar(nChar, nRepCnt, nFlags);
}

BOOL CGXComboBoxWnd::OnGridDoubleByteChar(const CString& sChar, UINT nRepCnt, UINT nFlags)
{
	// Unused:
	nRepCnt, nFlags;

	if (IsReadOnly())
		return FALSE;

	if (IsActive())
	{
		CString sEdit;
		GetCurrentText(sEdit);

		int nStartChar, nEndChar;
		GetEditSel(nStartChar, nEndChar);

		if (nEndChar == -1)
			sEdit = sChar;
		else if (nEndChar > nStartChar && nEndChar+1 < sEdit.GetLength())
			sEdit = sEdit.Left(nStartChar) + sChar + sEdit.Mid(nEndChar+1);
		else
			sEdit = sEdit.Left(nStartChar) + sChar + sEdit.Mid(nEndChar);

		// if (ValidateString(sEdit))
		ReplaceSel(sChar);
		nStartChar += sChar.GetLength();
		SetEditSel(nStartChar, nStartChar);

		return TRUE;
	}
	else
	{
		// discard key if cell is read only
		if (IsReadOnly() || !OnStartEditing())
			return FALSE;

		SetActive(TRUE);

		if ((GetStyle() & 0x03) == CBS_DROPDOWNLIST)
		{
			// Select entry for dropdown lists
			CString sEdit;
			GetCurrentText(sEdit);
			int r = FindString(-1, sEdit);
			SelectString(r, sChar);
			if (GetCurSel() == r)
				SelectString(-1, sChar);
		}
		else
		{
			// Replace text
			SetCurrentText(sChar);
			SetEditSel(sChar.GetLength(), sChar.GetLength());
		}
		SetModify(TRUE);
		OnModifyCell();
		Refresh();

		return TRUE;
	}
}

// Find and Replace
BOOL CGXComboBoxWnd::FindText(const GX_FR_STATE& find, ROWCOL nRow, ROWCOL nCol, BOOL bCurrentPos, BOOL bSetCell)
{
	// FindText not supported for ownerdrawn combobox
	if (!m_bFindTextSupported)
		return FALSE;

	LPCTSTR szValue = NULL;
	LPCTSTR pszFound = NULL;
	LPCTSTR szFind = find.strFindUpper;
		// strFindUpper contains the string to search.
		// if bCase is FALSE (case insensitive search),
		// the text in strFindUpper is converted to uppercase

	// if the active cell contains the text, mark it and return TRUE
	// if not, do a find and return FALSE
	if (nRow == m_nRow && nCol == m_nCol && IsActive())
	{
		CString s;

		int nStart, nEnd;

		GetEditSel(nStart, nEnd);
		GetCurrentText(s);

		// Convert text in s to upper case if we are doing a case insensitive search
		if (!find.bCase)
			s.MakeUpper();

		LPCTSTR pv = szValue = s;

		if (nStart != -1 && nEnd != -1)
			szValue += nStart + (bCurrentPos ? 0 : _tclen(szValue + nStart));

		pszFound = _tcsstr(szValue, szFind);

		if (pszFound != NULL)
		{
			if (bSetCell)
			{
				int nStart = (int)(pszFound - pv);

				// mark the text I have found
				Grid()->ScrollCellInView(nRow, nCol);
				SetEditSel(nStart, nStart+(int)_tcslen(szFind));
			}
			return TRUE;
		}
	}
	else
	{
		CString s;
		BOOL b;
		if (find.m_pStyle)
		{
			b = GetControlText(s, nRow, nCol, NULL, *find.m_pStyle);
		}
		else
		{
			// request a style object
			CGXStyle* pStyle = Grid()->CreateStyle();

			Grid()->ComposeStyleRowCol(nRow, nCol, pStyle);

			b = GetControlText(s, nRow, nCol, NULL, *pStyle);

			// free style object
			Grid()->RecycleStyle(pStyle);
		}

		if (b)
		{
			// Convert text to upper case if we are doing a case insensitive search
			if (!find.bCase)
				s.MakeUpper();

			szValue = s;
		}
		else
			szValue = _T("");

		pszFound = _tcsstr(szValue, szFind);

		if (pszFound != NULL)
		{
			if (bSetCell)
			{
				int nStart = (int)(pszFound - szValue);

				// mark the text I have found
				Grid()->ScrollCellInView(nRow, nCol);
				Grid()->SetCurrentCell(nRow, nCol, GX_SMART|GX_NOSETFOCUS);
				SetActive(TRUE);
				SetEditSel(nStart, nStart+(int)_tcslen(szFind));
				Refresh();
			}
			return TRUE;
		}
	}

	return FALSE;
}

void CGXComboBoxWnd::ReplaceSel(LPCTSTR pszReplaceText)
{
	// ReplaceSel not supported for ownerdrawn combobox
	if (!m_bFindTextSupported)
		return;

	if (IsReadOnly())
		return;

	if (IsActive())
	{
		CString s;

		int nStart, nEnd;

		GetEditSel(nStart, nEnd);
		GetCurrentText(s);

		if (nStart < 0)
			nStart = 0;

		CString r;
		if (nStart > 0)
			r = s.Left(nStart);

		r += pszReplaceText;

		if (nEnd > 0 && nEnd < s.GetLength())
			r += s.Mid(nEnd);

		SetCurrentText(r);

		int l = (int)_tcslen(pszReplaceText);

		if (nStart > 0)
			SetEditSel(nStart, nStart+l);
		else
			SetEditSel(0, l);
	}
	else
	{
		CGXControl::ReplaceSel(pszReplaceText);
	}

}

BOOL CGXComboBoxWnd::ReplaceAll(const GX_FR_STATE& find, ROWCOL nRow, ROWCOL nCol)
{
	// ReplaceAll not supported for ownerdrawn combobox
	if (!m_bFindTextSupported)
		return FALSE;

	BOOL bFound = FALSE;
	LPCTSTR szTemp = NULL;
	LPCTSTR szValue = NULL;
	LPCTSTR pszFound = NULL;
	LPCTSTR szFind = find.strFind;
	LPCTSTR szReplace = find.strReplace;

	CString s, sTemp;

	int nStart = 0, nEnd = -1;

	// if the active cell contains the text, mark it and return TRUE
	// if not, do a find and return FALSE
	if (nRow == m_nRow && nCol == m_nCol && IsActive())
	{
		GetEditSel(nStart, nEnd);
		GetCurrentText(s);
	}
	else if (find.m_pStyle)
	{
		GetControlText(s, nRow, nCol, NULL, *find.m_pStyle);
	}
	else
	{
		// request a style object
		CGXStyle* pStyle = Grid()->CreateStyle();

		Grid()->ComposeStyleRowCol(nRow, nCol, pStyle);

		GetControlText(s, nRow, nCol, NULL, *pStyle);

		// free style object
		Grid()->RecycleStyle(pStyle);
	}

	// Convert text in s to upper case if we are doing a case insensitive search
	sTemp = s;
	if (!find.bCase)
		sTemp.MakeUpper();
	szValue = s;
	szTemp = sTemp;

	nStart = max(0, nStart);

	int nReplace = (int)_tcslen(szReplace);
	int nFind = (int)_tcslen(szFind);

	// result text
	TCHAR szResult[1024];
	// QA: 31989 - #if Secure Code Cleanup.
	_tcsncpy(szResult, szValue, nStart);
	LPTSTR pszResult = szResult + nStart;

	// original text
	LPCTSTR pszValue = szValue + nStart;

	// text to compare (upper case if case insensitive search)
	LPCTSTR pszTemp  = szTemp + nStart;

	do
	{
		pszFound = _tcsstr(pszTemp, szFind);

		if (pszFound == NULL)
			// copy remaining after last match
			// QA: 31989 - #if Secure Code Cleanup.
			_tcscpy(pszResult, pszValue);
		else
		{
			bFound = TRUE;

			// copy text before match
			// QA: 31989 - #if Secure Code Cleanup.
			_tcsncpy(pszResult, pszValue, pszFound-pszTemp);
			pszResult += pszFound-pszTemp;

			// append replaced text
			// QA: 31989 - #if Secure Code Cleanup.
			_tcsncpy(pszResult, szReplace, nReplace);
			pszResult += nReplace;
			*pszResult = _T('\0');

			// increase pointers in original text (skip matching text)
			pszValue += pszFound-pszTemp+nFind;
			pszTemp = pszFound+nFind;

			// just to be sure ...
			ASSERT(pszValue == szValue + (pszTemp-szTemp));
		}
	}
	while (pszFound && *pszTemp);

	if (bFound)
		Grid()->SetValueRange(CGXRange(nRow, nCol), szResult, gxOverride);

	return bFound;
}

BOOL CGXComboBoxWnd::GetSelectedText(CString& strResult)
{
	if (IsActive())
	{
		CString s;

		if (m_nIndexValue != -1 && !m_bDispChoice)
		{
			int n = GetCurSel();
			if (n != -1)
			{
				n += m_nIndexValue;
				wsprintf(s.GetBufferSetLength(20), _T("%d"), n);
				s.ReleaseBuffer();
			}
		}
		else
		{
			int nStartChar = 0,
				nEndChar = -1;

			GetEditSel(nStartChar, nEndChar);
			GetCurrentText(s);

			if (nEndChar > nStartChar)
				strResult = s.Mid(nStartChar, nEndChar-nStartChar);
			else
				strResult = s.Mid(nStartChar);
		}
	}
	else if (IsInit())
	{
		NeedStyle();

		GetControlText(strResult, m_nRow, m_nCol, NULL, *m_pStyle);
	}
	else
		strResult.Empty();

	return TRUE;
}

void CGXComboBoxWnd::SetCellColor(COLORREF rgb)
{
	m_rgbCell = rgb;
}

void CGXComboBoxWnd::OnKillFocus(CWnd* pNewWnd)
{
	CComboBox::OnKillFocus(pNewWnd);
	CGXControl::OnKillFocus(pNewWnd);
}

BOOL CGXComboBoxWnd::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	GetClientRect(rect);

	// Erase Background
	// GXPatB(pDC, rect, m_rgbCell);
	GXPatB(pDC, rect, RGB(255,255,255));
	if (m_pStyle)
		pDC->FillRect(rect, Grid()->LookupOrCreateBrush(m_pStyle->GetInteriorRef()));

	return TRUE;
}

void CGXComboBoxWnd::GetEditSel(int& nStart, int& nEnd)
{
	if ((GetStyle() & CBS_DROPDOWNLIST) == CBS_DROPDOWNLIST)// Possible C4554 Warning
	{
		// need these value for find/replace
		nStart = m_nStartChar;
		nEnd = m_nEndChar;
	}
	else
	{
		DWORD dw = CComboBox::GetEditSel();
		nStart = max((short) LOWORD(dw), 0);
		nEnd = (short) HIWORD(dw);
	}
}

BOOL CGXComboBoxWnd::SetEditSel(int nStart, int nEnd)
{
	if ((GetStyle() & CBS_DROPDOWNLIST) == CBS_DROPDOWNLIST) // Possible C4554 Warning
	{
		// need to store these value for find/replace
		m_nStartChar = nStart;
		m_nEndChar = nEnd;
		return FALSE;
	}

	return CComboBox::SetEditSel(nStart, nEnd);
}

BOOL CGXComboBoxWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT flags)
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
			bGrid = TRUE;
			break;

		case VK_PRIOR:
		case VK_NEXT:
		case VK_DOWN:
		case VK_UP:
			bGrid = !m_bWantArrowKeys && !GetDroppedState();
			break;

		case VK_LEFT:
			if (!m_bWantArrowKeys && !GetDroppedState())
			{
				if ((GetStyle() & 0x03) == CBS_DROPDOWNLIST)
					bGrid = TRUE;
				else
				{
					int ns, nr;
					GetEditSel(ns, nr);
					if (ns == 0)
						bGrid = TRUE;
				}
			}
			break;

		case VK_RIGHT:
			if (!m_bWantArrowKeys && !GetDroppedState())
			{
				if ((GetStyle() & 0x03) == CBS_DROPDOWNLIST)
					bGrid = TRUE;
				else
				{
					int ns, nr;
					CString s;
					GetEditSel(ns, nr);
					GetCurrentText(s);
					if (nr >= (int) _tcsclen(s))
						bGrid = TRUE;
				}
			}
			break;

		case VK_TAB:
			bGrid = TRUE;
			break;

		case VK_RETURN:
			if (GetDroppedState())
			{
				ShowDropDown(FALSE);
				return TRUE;
			}
			else
				bGrid = TRUE;
			break;

		case VK_DELETE:
			if ((GetStyle() & 0x03) == CBS_DROPDOWNLIST)
			{
				// do not delete a dropdownlist
				return FALSE;

				//note: if you want to allow clearing of a dropdownlist, you can use this code
				//SetActive(FALSE);
				//SetModify(FALSE);
				//Grid()->SetControlTextRowCol(m_nRow, m_nCol, _T(""), GX_UPDATENOW, m_pStyle);
				//return TRUE;
			}
			break;

		}
	}

	if (bGrid)
		return Grid()->ProcessKeys(this, WM_KEYDOWN, nChar, nRepCnt, flags);

	return FALSE;
}

BOOL CGXComboBoxWnd::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (OnKeyDown((int) pMsg->wParam, LOWORD(pMsg->lParam), HIWORD(pMsg->lParam)))
			return TRUE;
	}

	return CComboBox::PreTranslateMessage(pMsg);
}

BOOL CGXComboBoxWnd::OnCommand(WPARAM wParam, LPARAM lParam)
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
		switch (nNotification)
		{
		case CBN_SELCHANGE:
		case CBN_EDITCHANGE:
			if (!IsReadOnly())
			{
				SetModify(TRUE);
				OnModifyCell();
			}
			else
			{
				if ((GetStyle() & 0x03) == CBS_DROPDOWNLIST)
					SetCurSel(m_nOldSel);
				else
					SetWindowText(m_sOldText);
			}

			break;

		case CBN_CLOSEUP:
			Grid()->SetDropDownCell(FALSE);

			if (!IsReadOnly())
			{
				if (GetModify())
					OnModifyCell();
			}
			else
			{
				if ((GetStyle() & 0x03) == CBS_DROPDOWNLIST)
					SetCurSel(m_nOldSel);
				else
					SetWindowText(m_sOldText);
			}
			break;

		case CBN_SETFOCUS:
			OnSetfocus();
			break;

		case CBN_DROPDOWN:
			Grid()->SetDropDownCell(TRUE);
			m_nOldSel = GetCurSel();
			GetWindowText(m_sOldText);
			break;
		}
	}

	return CGXStatic::OnCommand(wParam, lParam);
}

void CGXComboBoxWnd::OnSetfocus()
{
	if (!GetDroppedState() && m_bDropDownOnNextSetFocus)
		ShowDropDown(TRUE);

	m_bDropDownOnNextSetFocus = FALSE;
}

BOOL CGXComboBoxWnd::CanFloatCell(ROWCOL, ROWCOL, const CGXStyle&, BOOL)
{
	// combobox don't support floating
	return FALSE;
}
