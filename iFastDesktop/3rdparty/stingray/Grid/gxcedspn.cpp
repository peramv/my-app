///////////////////////////////////////////////////////////////////////////////
// gxcedspn.cpp : implementation of the CGXSpinEdit control
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
//          Supplement Section 227.7202, Government�s use, duplication or
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

#ifndef _GXCTRL_H_
#include "grid\gxctrli.h"
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXCEDSPN")
#endif

GRID_IMPLEMENT_CONTROL(CGXSpinEdit, CGXEditControl);
IMPLEMENT_DYNAMIC(CGXSpinEdit, CGXEditControl);

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif



/////////////////////////////////////////////////////////////////////////////
// CGXSpinEdit control

CGXSpinEdit::CGXSpinEdit(CGXGridCore* pGrid, UINT nID)
	: CGXEditControl(pGrid, nID)
{
	AddChild(m_pUpArrow = new CGXUpArrowButton(this));
	AddChild(m_pDownArrow = new CGXDownArrowButton(this));
}

void AFXAPI CGXSpinEdit::AddUserAttributes(CGXStylesMap* pStylesMap)
{
	// use spin-control in "User"-page
	CGXStyle styleSpin;
	styleSpin.SetControl(GX_IDS_CTRL_SPINEDIT).SetWrapText(FALSE);

		// Spinbounds: Minimum value
	pStylesMap->AddUserAttribute(GX_IDS_UA_SPINBOUND_MIN,
		&styleSpin);

		// Spinbounds: maximum value
	pStylesMap->AddUserAttribute(GX_IDS_UA_SPINBOUND_MAX,
		&styleSpin);

		// Spinbounds: start value when changing from null
	pStylesMap->AddUserAttribute(GX_IDS_UA_SPINSTART, &styleSpin);

		// Spinbounds: wrap value
	pStylesMap->AddUserAttribute(GX_IDS_UA_SPINBOUND_WRAP,
		CGXStyle().SetControl(GX_IDS_CTRL_CHECKBOX3D)
			  .SetVerticalAlignment(DT_VCENTER)
			  .SetHorizontalAlignment(DT_CENTER));
}

void CGXSpinEdit::Init(ROWCOL nRow, ROWCOL nCol)
{
	CGXEditControl::Init(nRow, nCol);

	// Force drawing of buttons for current cell
	GridWnd()->InvalidateRect(m_pUpArrow->GetRect());
	GridWnd()->InvalidateRect(m_pDownArrow->GetRect());

	NeedStyle();
}

BEGIN_MESSAGE_MAP(CGXSpinEdit, CGXEditControl)
	//{{AFX_MSG_MAP(CGXSpinEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

const int nEditBtnWidth = 13;

CRect CGXSpinEdit::GetCellRect(ROWCOL nRow, ROWCOL nCol, LPRECT rectItem /* = NULL */, const CGXStyle* pStyle /*= NULL*/)
{
	// compute the interior rectangle for the text
	// without buttons and borders

	CRect rect = CGXEditControl::GetCellRect(nRow, nCol, rectItem, pStyle);

	rect.right -= nEditBtnWidth+1;

	return rect;
}

CSize CGXSpinEdit::AddBorders(CSize size, const CGXStyle& style)
{
	size.cx += nEditBtnWidth+1;

	return CGXEditControl::AddBorders(size, style);
}

void CGXSpinEdit::OnInitChildren(ROWCOL nRow, ROWCOL nCol, const CRect& rect)
{
	nRow, nCol;

	const int nEditBtnWidth = 13;

	// CRect rect = CGXControl::GetCellRect(nRow, nCol, (LPRECT) &r, m_pStyle);

	// init arrow buttons
	CRect rectBtn;
	rectBtn.IntersectRect(rect,
			CRect(rect.right-2-nEditBtnWidth,
				rect.top+1, rect.right-1, rect.bottom-1)
		);

	m_pUpArrow->SetRect(
			CRect(rectBtn.left, rectBtn.top,
				rectBtn.right, rectBtn.top+rectBtn.Height()/2)
		);
	m_pDownArrow->SetRect(
			CRect(rectBtn.left, rectBtn.top+rectBtn.Height()/2,
				rectBtn.right, rectBtn.bottom)
		);
}

// Mouse hit
BOOL CGXSpinEdit::LButtonDown(UINT nFlags, CPoint pt, UINT nHitState)
{
	m_bWrap = (BOOL) _ttoi(m_pStyle->GetUserAttribute(GX_IDS_UA_SPINBOUND_WRAP));

	CString sMin, sMax;
	sMin = m_pStyle->GetUserAttribute(GX_IDS_UA_SPINBOUND_MIN);
	sMax = m_pStyle->GetUserAttribute(GX_IDS_UA_SPINBOUND_MAX);

	if ((m_bMinBound = !sMin.IsEmpty()) != FALSE)
		m_nMinBound = _ttol(sMin);

	if ((m_bMaxBound = !sMax.IsEmpty()) != FALSE)
		m_nMaxBound = _ttol(sMax);

	CString sStart;
	sStart = m_pStyle->GetUserAttribute(GX_IDS_UA_SPINSTART);

	if ((m_bStartValue = !sStart.IsEmpty()) != FALSE)
		m_nStartValue = _ttol(sStart);

	// if ((nHitState&GX_HITCURRENTCELL) > 0)
		return CGXEditControl::LButtonDown(nFlags, pt, nHitState);
	//FocusOnChild(NULL);
	//return FALSE;
}

// Mouse hit
BOOL CGXSpinEdit::LButtonUp(UINT nFlags, CPoint pt, UINT nHitState)
{
	// check child buttons
	return CGXEditControl::LButtonUp(nFlags, pt, nHitState);
}

void CGXSpinEdit::OnClickedButton(CGXChild* pChild)
{
	BOOL bActive = IsActive();

	if (!bActive && !OnStartEditing())
		return;

	SetActive(TRUE);

	CString strText;
	GetWindowText(strText);

	NeedStyle();

	// empty cell, when user pressed alpahnumeric key
	if (!IsReadOnly())
	{
		LONG lValue ;

		// style
		TCHAR sz[20];

		if ( m_bStartValue  &&  strText.IsEmpty() )
			lValue = m_nStartValue ;
		else
		{
			// Non-Null cell
			lValue = _ttol(strText);
			if (pChild == m_pUpArrow)
			{
				if (!m_bMaxBound || lValue < m_nMaxBound)
					lValue++;
				else if (m_bWrap && m_bMinBound)
					lValue = m_nMinBound;
			}
			else
			{
				if (!m_bMinBound || lValue > m_nMinBound)
					lValue--;
				else if (m_bWrap && m_bMaxBound)
					lValue = m_nMaxBound;
			}
		}

		if (m_bMinBound)
			lValue = max(m_nMinBound, lValue);

		if (m_bMaxBound)
			lValue = min(m_nMaxBound, lValue);

		wsprintf(sz, _T("%ld"), lValue);
		SetWindowText(sz);
		SetModify(TRUE);
		OnModifyCell();
		SetSel(0, -1);
	}

	// eventually destroys and creates CEdit with appropriate window style

	if (!bActive)
		Refresh();
	else
		UpdateEditStyle();

	CGXControl::OnClickedButton(pChild);
}

BOOL CGXSpinEdit::CanFloatCell(ROWCOL, ROWCOL, const CGXStyle&, BOOL)
{
	// don't support floating
	return FALSE;
}
