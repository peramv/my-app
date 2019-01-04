///////////////////////////////////////////////////////////////////////////////
// gxccbchk.cpp : implementation CGXCheckListComboBox control
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

/* CGXCheckListComboBox uses the CCheckListBox which is only
   available for MFC version 4.0 or later. */

#if _MFC_VER >= 0x0400

#ifdef _GXDLL
#undef AFXAPI_DATA
#define AFXAPI_DATA __based(__segname("_DATA"))
#endif

// Headers

#include "grid\gxresrc.h"

#ifndef _GXCTRLI_H_
#include "grid\gxctrli.h"
#endif

#ifndef _GXMSG_H_
#include "grid\gxmsg.h"
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXCCBCHK")
#endif

GRID_IMPLEMENT_CONTROL(CGXCheckListComboBox, CGXComboBox);
IMPLEMENT_DYNAMIC(CGXCheckListComboBox, CGXComboBox)
IMPLEMENT_DYNAMIC(CGXCheckListComboLBox, CCheckListBox)

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

const LPCTSTR szDelim = _T(";");

// CGXCheckListComboLBox

CGXCheckListComboLBox::CGXCheckListComboLBox(CWnd* pMsgWnd)
{
	m_bKeyDown = FALSE;
	m_bLButtonDown = FALSE;
	m_pMsgWnd = pMsgWnd;
	m_bColor = FALSE;
}

// [VC7] Return type changed to BOOL.
BOOL CGXCheckListComboLBox::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	// Function changed to return BOOL.
	BOOL bResult = CCheckListBox::Create(
		dwStyle | WS_VISIBLE | WS_BORDER|LBS_HASSTRINGS,
		rect, pParentWnd, nID);

	VERIFY(bResult);
	return bResult;
}

CGXCheckListComboLBox::~CGXCheckListComboLBox()
{
}

BEGIN_MESSAGE_MAP(CGXCheckListComboLBox, CCheckListBox)
	//{{AFX_MSG_MAP(CGXCheckListComboLBox)
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_WM_KEYUP()
	ON_WM_KILLFOCUS()
	ON_WM_SYSKEYUP()
	ON_WM_SYSKEYDOWN()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// ============ CGXCheckListComboLBox message handlers

void CGXCheckListComboLBox::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	m_bKeyDown =TRUE;
	m_nOldSel = GetCurSel();
	m_bAlNum = _istalnum((_TXCHAR) nChar);

	CCheckListBox::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CGXCheckListComboLBox::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_bLButtonDown = TRUE;
	m_nOldSel = GetCurSel();

	CCheckListBox::OnLButtonDown(nFlags, point);
}

void CGXCheckListComboLBox::OnLButtonUp(UINT nFlags, CPoint point)
{
	CCheckListBox::OnLButtonUp(nFlags, point);

	m_bLButtonDown = FALSE;
}

BOOL CGXCheckListComboLBox::OnEraseBkgnd(CDC* pDC)
{
#if _MFC_VER >= 0x0300
	HBRUSH hBrush = (HBRUSH) GetParent()->SendMessage(
		WM_CTLCOLORLISTBOX,
		(WPARAM) pDC->GetSafeHdc(),
		(LPARAM) m_hWnd);
#else
	HBRUSH hBrush = (HBRUSH) GetParent()->SendMessage(
		WM_CTLCOLOR,
		(WPARAM) pDC->GetSafeHdc(),
		MAKELONG((WORD) m_hWnd, (WORD) CTLCOLOR_LISTBOX));
#endif

	if (hBrush)
	{
		CRect rect;
		GetClientRect(rect);
		::FillRect(pDC->GetSafeHdc(), rect, hBrush);
		return TRUE;
	}

	return CCheckListBox::OnEraseBkgnd(pDC);
}

BOOL CGXCheckListComboBox::OnProcessChar(UINT , UINT , UINT )
{
	m_sLastChar.Empty();
	return FALSE;
}

DWORD CGXCheckListComboBox::CalcEditStyle(LPRECT rectNP, int& dyHeight)
{
	DWORD dwStyle = CGXEditControl::CalcEditStyle(rectNP, dyHeight);

	// Add ES_PASSWORD to the edit control style settings and
	// remove ES_MULTILINE bit becuase ES_PASSWORD does not work
	// together with ES_MULTILINE.

	return dwStyle | ES_READONLY;
}

void CGXCheckListComboLBox::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CCheckListBox::OnKeyUp(nChar, nRepCnt, nFlags);

	if (m_bKeyDown)
	{
		if (nChar == 9)
		{
			m_pMsgWnd->PostMessage(WM_KEYDOWN, 9);
			m_pMsgWnd->PostMessage(WM_KEYUP, 9);
			m_pMsgWnd->SendMessage(WM_GX_LBOXEND, 0, 0);
		}
		else if (nChar == 13)
			m_pMsgWnd->SendMessage(WM_GX_LBOXEND, 0, 0);
		else if (nChar == 27)
			m_pMsgWnd->SendMessage(WM_GX_LBOXEND, 0, 0);
		else
			m_bKeyDown = FALSE;
	}
}

void CGXCheckListComboLBox::OnKillFocus(CWnd* pNewWnd)
{
	CCheckListBox::OnKillFocus(pNewWnd);

	if (m_pMsgWnd)
		m_pMsgWnd->PostMessage(WM_GX_LBOXEND, 0, 0);
}

void CGXCheckListComboLBox::OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (m_bKeyDown && nChar == VK_DOWN)
		m_pMsgWnd->SendMessage(WM_GX_LBOXEND, 0, 0);
	else
		CCheckListBox::OnSysKeyUp(nChar, nRepCnt, nFlags);
}

void CGXCheckListComboLBox::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	m_bKeyDown =TRUE;

	CCheckListBox::OnSysKeyDown(nChar, nRepCnt, nFlags);
}

// CGXCheckListComboBox

const int nComboBtnWidth = 15;
const int nComboBtnHeight = 18;


CGXCheckListComboBox::CGXCheckListComboBox(CGXGridCore* pGrid, UINT nEditID, UINT nListBoxID)
	: CGXComboBox(pGrid, nEditID, nListBoxID, GXCOMBO_NOTEXTFIT)
{
}

CGXCheckListComboBox::~CGXCheckListComboBox()
{
}

BEGIN_MESSAGE_MAP(CGXCheckListComboBox, CGXComboBox)
	//{{AFX_MSG_MAP(CGXCheckListComboBox)
	ON_MESSAGE(WM_GX_LBOXEND, OnListBoxEnd)
	ON_MESSAGE(WM_GX_LBOXCANCEL, OnListBoxCancel)
	ON_MESSAGE(WM_GX_LBOXCHANGED, OnListBoxChanged)
	ON_MESSAGE(WM_GX_LBOXKILLFOCUS, OnListBoxKillFocus)
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CGXCheckListComboBox::GetControlText(CString& strResult, ROWCOL nRow, ROWCOL nCol, LPCTSTR pszRawValue, const CGXStyle& style)
{
	// Unused:
	pszRawValue, nRow, nCol;

	strResult.Empty();

	// use first entry in choice list as text to be displayed in cell
	if (style.GetIncludeChoiceList())
	{
		CString s = style.GetChoiceListRef();
		if (!s.IsEmpty())
			GXGetNextLine(s, strResult);
	}

	return TRUE;
}

CWnd* CGXCheckListComboBox::CreateListBox(CWnd* pParentWnd, UINT nID)
{
	// Creates the listbox

	// if you want to create an owner-drawn listbox, you should
	// derive a class from CGXCheckListComboLBox, override CreateListBox
	// and return a pointer to it.

	CGXCheckListComboLBox* pListBox = new CGXCheckListComboLBox(this);

	CRect rect;
	pParentWnd->GetClientRect(&rect);
	rect.left++;
	rect.right--;

	if (m_dwListBoxStyle == 0)
		m_dwListBoxStyle = WS_VSCROLL|LBS_NOTIFY;

	pListBox->Create(m_dwListBoxStyle, rect, pParentWnd, nID);

	// CGXCheckListComboBox will delete the listbox object.

	return pListBox;
}

void CGXCheckListComboBox::OnFillDroppedList(CListBox* lbox)
{
	const CGXStyle& style = Grid()->LookupStyleRowCol(m_nRow, m_nCol);

	CGXCheckListComboLBox* checklbox = (CGXCheckListComboLBox*) lbox;
	ASSERT(checklbox->IsKindOf(RUNTIME_CLASS(CGXCheckListComboLBox)));

	// fill with Choices
	if (style.GetIncludeChoiceList())
	{
		CString s = style.GetChoiceListRef();
		CString sItem;
		// skip first entry in choice list because this is the text to be displayed in the cell
		int n = GXGetNextLine(s, sItem);
		m_nCount = 0;
		while (!s.IsEmpty() && n != -1)
		{
			n = GXGetNextLine(s, sItem);

			lbox->AddString(sItem);
			m_nCount++;
		}
	}

	// enable choices
	if (style.GetIncludeValue())
	{
		DWORD dwValue = _ttol(style.GetValueRef());
		DWORD dwOption = 1;

		for (int n = 0; n < m_nCount; n++)
		{
			checklbox->SetCheck(n, (dwValue&dwOption) == dwOption);
			dwOption *= 2;
		}
	}
}

void CGXCheckListComboBox::OnStoreDroppedList(CListBox* lbox)
{
	CGXCheckListComboLBox* checklbox = (CGXCheckListComboLBox*) lbox;
	ASSERT(checklbox->IsKindOf(RUNTIME_CLASS(CGXCheckListComboLBox)));

	// Save the selection
	// enable choices

	CGXStyle style;
	Grid()->ComposeStyleRowCol(m_nRow, m_nCol, &style);
	DWORD dwPrevValue =  style.GetDWordValue();
	DWORD dwValue = 0;
	DWORD dwOption = 1;

	for (int n = 0; n < m_nCount; n++)
	{
		if (checklbox->GetCheck(n) == 1)
		{
			dwValue += dwOption;
		}

		dwOption *= 2;
	}

	// Selection has changed
	if(dwValue != dwPrevValue)
	{
		SetModify(TRUE);

		if (dwValue > 0)
			Grid()->SetValueRange(CGXRange(m_nRow, m_nCol), dwValue);
		else
			Grid()->SetValueRange(CGXRange(m_nRow, m_nCol), _T(""));
	}
}

LRESULT CGXCheckListComboBox::OnListBoxEnd(WPARAM, LPARAM )
{
	Grid()->SetIgnoreFocus(TRUE);
	Grid()->SetDropDownCell(FALSE);

	// User has selected an item
	if (m_pDropDownWnd)
	{
		CGXGridCombo::SetComboBoxDropDown(TRUE);

		NeedStyle();

		// empty cell, when user pressed alpahnumeric key
		if (!IsReadOnly())
			OnStoreDroppedList(&m_pDropDownWnd->GetLBox());

		// I need to set m_pDropDownWnd = NULL before I destroy the window
		// This avoids problems when killing the focus results in a call to ListBoxCancel
		CWnd* pDropDownWnd = m_pDropDownWnd;
		m_pDropDownWnd  = NULL;

		if (pDropDownWnd)
			DestroyDropDownWnd(pDropDownWnd);

		CGXGridCombo::SetComboBoxDropDown(FALSE);

		// Fire OnModifyCell event after Dropdown-window has been destroyed

		OnModifyCell();

#ifdef _WIN32
		if (GetFocus() == GridWnd())
			SetFocus();
#else
		if (::IsChild(AfxGetMainWnd()->GetSafeHwnd(),::GetFocus()));
			SetFocus();
#endif

		Grid()->SetIgnoreFocus(FALSE);

		SetModify(FALSE);
		SetActive(FALSE);
		Refresh();
	}

	return 0;
}

LRESULT CGXCheckListComboBox::OnListBoxCancel(WPARAM wParam, LPARAM lParam)
{
	return OnListBoxEnd(wParam, lParam);
}

LRESULT CGXCheckListComboBox::OnListBoxChanged(WPARAM, LPARAM)
{
	// User has changed selection
	return 0;
}

LRESULT CGXCheckListComboBox::OnListBoxKillFocus(WPARAM, LPARAM)
{
	// User has changed selection

	CWnd* pWnd = GetFocus();

	if (!(GridWnd()->IsChild(pWnd) || GridWnd() == pWnd))
		SendMessage(WM_GX_LBOXCANCEL, 0, 0);

	return 0;
}

BOOL CGXCheckListComboBox::KeyPressed(UINT nMessage, UINT nChar, UINT nRepCnt, UINT flags)
{
	if (nMessage == WM_SYSKEYDOWN)
		return CGXComboBox::KeyPressed(nMessage, nChar, nRepCnt, flags);

	return FALSE;
}

void CGXCheckListComboBox::OnSetFocus(CWnd* pOldWnd)
{
	CGXComboBox::OnSetFocus(pOldWnd);

	GetParent()->SetFocus();
}

void CGXCheckListComboBox::Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle)
{
	if (nRow == m_nRow && nCol == m_nCol
		&& IsActive() && !Grid()->IsPrinting())
	{
		Hide();
		CGXStatic::Draw(pDC, rect, nRow, nCol, style, pStandardStyle);
		InvertBorders(pDC, rect);
	}
	else
		CGXStatic::Draw(pDC, rect, nRow, nCol, style, pStandardStyle);
}

BOOL CGXCheckListComboBox::LButtonUp(UINT nFlags, CPoint pt, UINT nHitState)
{
	return CGXControl::LButtonUp(nFlags, pt, nHitState);
}

void CGXCheckListComboBox::SetActive(BOOL bActive)
{
	bActive;
}


#endif // #if _MFC_VER >= 0x0400

