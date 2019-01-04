///////////////////////////////////////////////////////////////////////////////
// gxcstat.cpp : implementation of the CGXStatic control
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
#pragma code_seg("GX_SEG_GXCSTAT")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

GRID_IMPLEMENT_CONTROL(CGXStatic, CGXControl);

/////////////////////////////////////////////////////////////////////////////
// CGXStatic

CGXStatic::CGXStatic(CGXGridCore* pGrid)
	: CGXControl(pGrid)
{
}

CRect CGXStatic::GetCellRect(ROWCOL nRow, ROWCOL nCol, LPRECT rectItem /* = NULL */, const CGXStyle* pStyle /*= NULL*/)
{
	// compute the interior rectangle for the text
	// without buttons and borders

	if (pStyle == NULL)
		pStyle = &Grid()->LookupStyleRowCol(nRow, nCol);

	CRect rect = CGXControl::GetCellRect(nRow, nCol, rectItem, pStyle);

	CString str;
	HANDLE hbm = 0;
	
	// check for #bmp only for static cells (and not 
	// for cells where the user can enter the text)

	if (hbm == NULL)
	{
		// On the top and on the left side is the Grid-Line (1pt)!
		// Put the appropriate Values here (these are for normal Text-Cells)
		int xFrame = max(GetSystemMetrics(SM_CXFRAME)/2, 2);
		int yFrame = 0; // or GetSystemMetrics(SM_CXFRAME);

		rect.left += xFrame;
		if (pStyle->GetIncludeHorizontalAlignment()
			&& pStyle->GetHorizontalAlignment() == DT_RIGHT)
			rect.right -= xFrame+1;
		else
			rect.right -= xFrame/2;
		rect.top += yFrame;
		rect.bottom -= yFrame;
	}

	return rect;
}

CSize CGXStatic::AddBorders(CSize size, const CGXStyle& style)
{
	// this is the counterpart to GetCellRect

	CString str;
	HANDLE hbm = 0;
	
	// check for #bmp only for static cells (and not 
	// for cells where the user can enter the text)

	if (hbm == NULL)
	{
		// On the top and on the left side is the Grid-Line (1pt)!
		// Put the appropriate Values here (these are for normal Text-Cells)
		int xFrame = max(GetSystemMetrics(SM_CXFRAME)/2, 2);
		int yFrame = 0; // or GetSystemMetrics(SM_CXFRAME);

		size.cx += xFrame;
		size.cx += xFrame+1;

		size.cy += 2*yFrame;
	}

	return Grid()->AddBorders(size, style);
}


void CGXStatic::Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle)
{
	ASSERT(pDC != NULL && pDC->IsKindOf(RUNTIME_CLASS(CDC)));
	// ASSERTION-> Invalid Device Context ->END
	ASSERT(nRow <= Grid()->GetRowCount() && nCol <= Grid()->GetColCount());
	// ASSERTION-> Cell coordinates out of range ->END

	ASSERT_VALID(pDC);

	GXDaFTools()->DrawStatic(this, pDC, rect, nRow, nCol, style, pStandardStyle);
}

// In OG 1.1, I have changed the behavior of CalcSize so that it does not
// resize columns any more if the row height is already large
// enough to hold the cells contents by wrapping the text.

CSize CGXStatic::CalcSize(CDC* pDC, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle, BOOL bVert)
{
	GX_CHECKIMP(Grid()->m_pAbstractCalcSizeImp, "CGXStatic::CalcSize");

	if (Grid()->m_pAbstractCalcSizeImp)
		return Grid()->m_pAbstractCalcSizeImp->CalcSize(this, pDC, nRow, nCol, style, pStandardStyle, bVert);

	return CSize(0,0);
}

BOOL CGXStatic::CanFloatCell(ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, BOOL bFloatOrFlood)
{
	if (Grid()->m_pFloatCellsImp)
		return Grid()->m_pFloatCellsImp->CanFloatCell(this, nRow, nCol, style, bFloatOrFlood);

	return FALSE;
}

