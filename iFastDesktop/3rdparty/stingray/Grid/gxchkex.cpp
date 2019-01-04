///////////////////////////////////////////////////////////////////////////////
// gxchkex.cpp : implementation of the CGXCheckBoxEx control
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
// Author: Praveen Ramesh
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

#ifndef _GXDLL_H_
#include "grid\gxdll.h" // GXGetResourceHandle
#endif


#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXCCHECK")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif


GRID_IMPLEMENT_CONTROL(CGXCheckBoxEx, CGXControl);

/////////////////////////////////////////////////////////////////////////////
// CGXCheckBoxEx control

CGXCheckBoxEx::CGXCheckBoxEx(CGXGridCore* pGrid, BOOL bDraw3d /* = TRUE */, UINT nBitmapResourceId /* = 0 */, UINT nPrintResourceId /* = 0 */)
	: CGXCheckBox(pGrid, bDraw3d, nBitmapResourceId, nPrintResourceId)
{
	m_bActive = FALSE;
	m_bModified = FALSE;
}

BOOL CGXCheckBoxEx::GetModify()
{
	return m_bModified;
}

void CGXCheckBoxEx::SetModify(BOOL bModified)
{
	m_bModified = bModified;
}

BOOL CGXCheckBoxEx::Store()
{
	// Calls SetStyleRange() and resets the modify flag
	ASSERT(m_pStyle);

	CString sValue;
	if (m_pStyle && GetModify())
	{
		sValue = m_pStyle->GetValue();
		SetActive(FALSE);
		FreeStyle();

		return Grid()->SetValueRange(
			CGXRange(m_nRow,  m_nCol),
			sValue,
			gxOverride,
			0,
			GX_INVALIDATE);
			// Cell will be automatically redrawn inactive
	}

	return TRUE;
}

void CGXCheckBoxEx::Init(ROWCOL nRow, ROWCOL nCol)
{
	// Stores the cell coordinates, resets the style and sets the window text
	CGXControl::Init(nRow, nCol);

	NeedStyle();

	SetModify(FALSE);
}

void CGXCheckBoxEx::Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle)
{
	if(nRow == m_nRow && nCol == m_nCol && IsActive())
	{
		//style = *m_pStyle;
		CGXCheckBox::Draw(pDC, rect, nRow, nCol, *m_pStyle, pStandardStyle);
		return;
	}
	CGXCheckBox::Draw(pDC, rect, nRow, nCol, style, pStandardStyle);
	return;
}

BOOL CGXCheckBoxEx::LButtonDown(UINT nFlags, CPoint pt, UINT nHitState)
{
	nHitState, pt, nFlags;

	// style
	const CGXStyle* pStyle;
	if(IsActive())
	{
		pStyle = m_pStyle;
	}
	else
	{
		pStyle = &Grid()->LookupStyleRowCol(m_nRow, m_nCol);		
	}

	if (IsReadOnly() || pStyle->GetIncludeReadOnly() && pStyle->GetReadOnly())
		return FALSE;

	// compute checkbox rectangle for mouse hit-testing
	CRect rect = GetCellRect(m_nRow, m_nCol, NULL, pStyle);

	DWORD dtAlign = DT_LEFT;
	if (pStyle->GetIncludeHorizontalAlignment())
		dtAlign = pStyle->GetHorizontalAlignment();

	if (pStyle->GetIncludeVerticalAlignment())
		dtAlign |= pStyle->GetVerticalAlignment();

	CClientDC dc(GridWnd());
	Grid()->OnGridPrepareDC(&dc);

	// Select font
	CFont* pOldFont = LoadFont(&dc, *pStyle, NULL);

	m_rectBox = ComputeCheckBoxRect(&dc, rect,
		pStyle->GetIncludeChoiceList() ? (LPCTSTR) pStyle->GetChoiceListRef() : _T(""),
		dtAlign);


	if (pOldFont)
		dc.SelectObject(pOldFont);

	if (m_rectBox.PtInRect(pt))
	{
		m_bScope = TRUE;
		Refresh();
	}

	// check child buttons
	CGXControl::LButtonDown(nFlags, pt, nHitState);

	return TRUE;
}

BOOL CGXCheckBoxEx::KeyPressed(UINT nMessage, UINT nChar, UINT nRepCnt, UINT flags)
{
	BOOL bRet = CGXCheckBox::KeyPressed(nMessage, nChar, nRepCnt, flags);
	// Process Delete Key if active...
	if(!bRet && nMessage == WM_KEYDOWN && nChar == 46 && IsActive())
	{
		m_pStyle->SetValue(_T(""));
		Grid()->RedrawRowCol(m_nRow, m_nCol);
		SetModify(TRUE);
		OnModifyCell();
		return TRUE;
	}

	return bRet;
}

void CGXCheckBoxEx::OnClickedButton(CGXChild* pChild)
{
	// style
	const CGXStyle* pStyle;
	if(IsActive())
		pStyle = m_pStyle;
	else
	{
		if (!OnStartEditing())
			return;
		SetActive(TRUE);
		pStyle = m_pStyle;
	}

	if (IsReadOnly() || pStyle->GetIncludeReadOnly() && pStyle->GetReadOnly())
		return;

	BOOL bTriState = pStyle->GetIncludeTriState() && pStyle->GetTriState();

	// Load representations for TRUE/FALSE
	CString strTrue, strFalse;

	pStyle->GetUserAttribute(GX_IDS_UA_CHECKBOX_CHECKED, strTrue);
	if (strTrue.IsEmpty())
		strTrue = _T("1");

	pStyle->GetUserAttribute(GX_IDS_UA_CHECKBOX_UNCHECKED, strFalse);
	if (strFalse.IsEmpty())
		strFalse = _T("0");

	// Switch to next value
	CString strVal = pStyle->GetValueRef();

	// checked to unchecked
	if (strVal == strTrue)
		strVal = strFalse;

	// unchecked to grayed
	else if (bTriState && strVal == strFalse)
		strVal.Empty();

	// if !bTriState did fall through
	// grayed to checked
	else
		strVal = strTrue;

	// Store value
//	Grid()->SetValueRange(CGXRange(m_nRow, m_nCol), strVal, gxOverride);
	m_pStyle->SetValue(strVal);
	Grid()->RedrawRowCol(m_nRow, m_nCol);
	SetModify(TRUE);
	OnModifyCell();

	CGXControl::OnClickedButton(pChild);
}

void CGXCheckBoxEx::SetActive(BOOL bActive)
{
	if(!m_bActive && bActive)
	{
		// Force a call to GetStyleRowCol() because
		// GetStyleRowCol() might set style attributes
		// depending on the IsActive() flag
		FreeStyle();
		NeedStyle();
	}
	m_bActive = bActive;
}

BOOL CGXCheckBoxEx::IsActive()
{
	return m_bActive;
}
