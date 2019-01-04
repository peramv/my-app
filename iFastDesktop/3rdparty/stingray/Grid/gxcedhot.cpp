///////////////////////////////////////////////////////////////////////////////
// gxcedhot.cpp : implementation of the CGXHotSpotEdit control
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
#pragma code_seg("GX_SEG_GXCEDHOT")
#endif

GRID_IMPLEMENT_CONTROL(CGXHotSpotEdit, CGXEditControl);
IMPLEMENT_DYNAMIC(CGXHotSpotEdit, CGXEditControl);

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CGXHotSpotEdit control

CGXHotSpotEdit::CGXHotSpotEdit(CGXGridCore* pGrid, UINT nID)
	: CGXEditControl(pGrid, nID)
{
	AddChild(m_pHotSpot = new CGXHotSpotButton(this));
}

void CGXHotSpotEdit::Init(ROWCOL nRow, ROWCOL nCol)
{
	CGXEditControl::Init(nRow, nCol);

	// Force drawing of button for current cell
	GridWnd()->InvalidateRect(m_pHotSpot->GetRect());
}

BEGIN_MESSAGE_MAP(CGXHotSpotEdit, CGXEditControl)
	//{{AFX_MSG_MAP(CGXHotSpotEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

const int nEditBtnWidth = 13;

CRect CGXHotSpotEdit::GetCellRect(ROWCOL nRow, ROWCOL nCol, LPRECT rectItem /* = NULL */, const CGXStyle* pStyle /*= NULL*/)
{
	// compute the interior rectangle for the text
	// without buttons and borders

	CRect rect = CGXEditControl::GetCellRect(nRow, nCol, rectItem, pStyle);

	rect.right -= nEditBtnWidth;

	return rect;
}

CSize CGXHotSpotEdit::AddBorders(CSize size, const CGXStyle& style)
{
	size.cx += nEditBtnWidth;

	return CGXEditControl::AddBorders(size, style);
}

void CGXHotSpotEdit::OnInitChildren(ROWCOL nRow, ROWCOL nCol, const CRect& rect)
{
	nRow, nCol;

	const int nEditBtnWidth = 13;

	// init hotspot button
	CRect rectBtn;
	rectBtn.IntersectRect(rect,
				CRect(rect.right-1-nEditBtnWidth, rect.top, rect.right-1, rect.top+nEditBtnWidth));

	if (rectBtn.Height() < rect.Height()-1)
	{
		rectBtn.top += 1;
		rectBtn.bottom += 1;
	}

	m_pHotSpot->SetRect(rectBtn);
}

BOOL CGXHotSpotEdit::CanFloatCell(ROWCOL, ROWCOL, const CGXStyle&, BOOL)
{
	// don't support floating
	return FALSE;
}
