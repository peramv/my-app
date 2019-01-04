///////////////////////////////////////////////////////////////////////////////
// gxcwrap.cpp : implementation of the CGXWndWrapper control
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
#pragma code_seg("GX_SEG_GXCWRAP")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

GRID_IMPLEMENT_CONTROL(CGXWndWrapper, CGXControl);

/////////////////////////////////////////////////////////////////////////////
// CGXWndWrapper

CGXWndWrapper::CGXWndWrapper(CGXGridCore* pGrid, CWnd* pWnd, BOOL bNeedDestroy, BOOL bCanActivate, BOOL bInvertBorders)
	: CGXControl(pGrid)
{
	ASSERT(pGrid);
	ASSERT_VALID(pWnd);

	m_pWnd = pWnd;
	m_bIsActive = FALSE;
	m_bCanActivate = bCanActivate;
	m_bNeedDestroy = bNeedDestroy;
	m_bInvertBorders = bInvertBorders;
}

CGXWndWrapper::CGXWndWrapper(CGXGridCore* pGrid)
	: CGXControl(pGrid)
{
	m_pWnd = NULL;
	m_bIsActive = FALSE;
	m_bCanActivate = FALSE;
	m_bNeedDestroy = FALSE;
}

CGXWndWrapper::~CGXWndWrapper()
{
	if (m_bNeedDestroy)
	{
		m_pWnd->DestroyWindow();
		delete m_pWnd;
	}
}

CWnd* CGXWndWrapper::GetWndPtr()  const
{
	return m_pWnd;
}

// Status
void CGXWndWrapper::SetActive(BOOL bActive)
{
	m_bIsActive = bActive;
}

BOOL CGXWndWrapper::IsActive()
{
	return m_bCanActivate && m_bIsActive;
}

// Operations
void CGXWndWrapper::Init(ROWCOL nRow, ROWCOL nCol)
{
	ASSERT(::IsWindow(m_pWnd->GetSafeHwnd()));
	// ASSERTION-> Did you forget to call Create? ->END

	// Stores the cell coordinates, resets the style and sets the window text
	CGXControl::Init(nRow, nCol);

	SetActive(FALSE);
	SetModify(FALSE);
}

void CGXWndWrapper::Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle)
{
	ASSERT(::IsWindow(m_pWnd->GetSafeHwnd()));
	// ASSERTION-> Did you forget to call Create? ->END

	ASSERT(pDC != NULL && pDC->IsKindOf(RUNTIME_CLASS(CDC)));
	// ASSERTION-> Invalid Device Context ->END
	ASSERT(nRow <= Grid()->GetRowCount() && nCol <= Grid()->GetColCount());
	// ASSERTION-> Cell coordinates out of range ->END

	ASSERT_VALID(pDC);

	// Draw the decorated window

	// Erase Frame around the cell
    DrawFrame(pDC, rect, style);

	// Font
	if (m_font.GetSafeHandle())
		m_font.DeleteObject();

	CGXFont font(style.GetFontRef());
	font.SetSize(font.GetSize()*Grid()->GetZoom()/100);
	font.SetOrientation(0);

	// no vertical font for editing the cell
	const LOGFONT& _lf = font.GetLogFontRef();
	if ( !m_font.CreateFontIndirect(&_lf) )
	{
		TRACE1("Failed to create font '%s' in CGXWndWrapper::Draw\n",
			(LPCTSTR) m_pStyle->GetFontRef().GetDescription());
	}

	rect = GetCellRect(nRow, nCol, &rect, &style);

	m_pWnd->MoveWindow(rect, FALSE);
	m_pWnd->SetFont(&m_font);
	m_pWnd->Invalidate();
	m_pWnd->ShowWindow(SW_SHOW);

	if ((nRow > Grid()->GetFrozenRows() && Grid()->GetTopRow() > nRow) 
		|| (nCol > Grid()->GetFrozenCols() && Grid()->GetLeftCol() > nCol))
	// Ensure that the window cannot draw outside the clipping area!
	{
		CRect rectClip;
		if (pDC->GetClipBox(&rectClip) != ERROR)
		{
			CRect r = rect & Grid()->GetGridRect();
			GridWnd()->ClientToScreen(&r);
			m_pWnd->ScreenToClient(&r);
			GridWnd()->ClientToScreen(&rectClip);
			m_pWnd->ScreenToClient(&rectClip);
			m_pWnd->ValidateRect(r);
			m_pWnd->InvalidateRect(rectClip);
		}
	}

	m_pWnd->UpdateWindow();

	BOOL bFocus = FALSE;

	if (nRow == m_nRow && nCol == m_nCol && IsActive() && !Grid()->IsPrinting())
	{
		CGXRange rgCell(nRow, nCol);
		bFocus = 
			// Either a single cell
			NULL == Grid()->GetCellRangeRowCol(nRow, nCol, rgCell)
			// or cell is fully visible
			|| !(nRow < Grid()->GetTopRow() && rgCell.bottom > Grid()->GetFrozenRows()
				|| nCol < Grid()->GetLeftCol() && rgCell.right > Grid()->GetFrozenCols());

		// If some parts of cell are clipped don't set focus onto cell
	}

	// if (nRow == m_nRow && nCol == m_nCol && m_bIsActive)
	//     initialize CWnd, make it visible and set focus
	if (bFocus)
	{
		Grid()->SetIgnoreFocus(TRUE);
		if (m_pWnd->GetFocus() == GridWnd())
			m_pWnd->SetFocus();
		Grid()->SetIgnoreFocus(FALSE);
		SetModify(TRUE);
	}
	else
	{
		Hide();     // drawn area remains visible
		GridWnd()->ValidateRect(rect);
	}

	// Avoid overdrawing with BitmapDC in CGXGridCore::OnDraw
	ExcludeClipRect(rect);

	// Unreferenced:
	pStandardStyle;
}

void CGXWndWrapper::Hide()
{
	// Hides the CEdit without changing the m_bIsActive flag
	// and without invalidating the screen
	m_pWnd->HideCaret();
	m_pWnd->MoveWindow0(FALSE);
	m_pWnd->ShowWindow(SW_HIDE);
}

// Mouse hit
BOOL CGXWndWrapper::LButtonUp(UINT nFlags, CPoint pt, UINT nHitState)
{
	// Unreferenced:
	nFlags, pt, nHitState;

	if (m_bCanActivate)
	{
		SetActive(TRUE);
		Refresh();

		CRect r = GetCellRect(m_nRow, m_nCol);
		pt.x -= r.left;
		pt.y -= r.top;

		m_pWnd->PostMessage(WM_LBUTTONDOWN, MK_LBUTTON, MAKELONG(pt.x, pt.y));
		m_pWnd->PostMessage(WM_LBUTTONUP, MK_LBUTTON, MAKELONG(pt.x, pt.y));
	}

	// check child buttons
	CGXControl::LButtonUp(nFlags, pt, nHitState);

	return TRUE;
}

// Keyboard
BOOL CGXWndWrapper::KeyPressed(UINT nMessage, UINT nChar, UINT nRepCnt, UINT flags)
{
	// Called when the user presses a key on the inactive current cell
	// functionality:
	//    - set active

	// Unreferenced:
	nChar, flags, nRepCnt;

	if (IsActive())
	{
		if (m_pWnd->GetFocus() == GridWnd())
			m_pWnd->SetFocus();
		
		return TRUE;
	}

	if (m_bCanActivate)
	{
		NeedStyle();

		if (IsReadOnly() || !OnStartEditing())
			return FALSE;

		SetActive(TRUE);
		if (!Grid()->ScrollCellInView(m_nRow, m_nCol))
			Refresh();
	}

	CGXControl::KeyPressed(nMessage, nChar, nRepCnt, flags);

	return TRUE;
}

void CGXWndWrapper::InvertBorders(CDC* pDC, const CRect& r)
{
	if (m_bInvertBorders)
		CGXControl::InvertBorders(pDC, r);
}

BOOL CGXWndWrapper::OnEndEditing()
{
	if (IsActive())
	{
		// Give an active window the chance update its appearance
		// before it gets hidden

		m_pWnd->SendMessage(WM_KILLFOCUS, 0, 0);
		m_pWnd->UpdateWindow();
	}
	
	return TRUE;
}
