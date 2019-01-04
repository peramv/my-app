///////////////////////////////////////////////////////////////////////////////
// gxmarked.cpp: Outline row and column header for current cell
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

#ifndef _GXRESRC_H_
#include "grid\gxresrc.h"
#endif

#ifndef _GXEXT_H_
#include "grid\gxext.h"
#endif

#ifndef _GXCORE_H_
#include "grid\gxcore.h"
#endif

#ifndef _GXCTRL_H_
#include "grid\gxctrl.h"
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXCORDRA")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

class CGXGridMarkEditHeaderImp: public CGXAbstractGridMarkEditHeaderImp
{
public:
	virtual void MarkEdit(CGXGridCore* pGrid, ROWCOL nEditRow, ROWCOL nEditCol, UINT direction, UINT flags);
	virtual BOOL GetMarkHeaderState(CGXControl* pControl, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style);
};

void CGXGridCore::ImplementMarkEditHeader()
{
	if (m_pMarkEditHeaderImp == NULL)
	{
		// QA: 31521 Removal from AutoDeletePtr
		//AutoDeletePtr(m_pMarkEditHeaderImp = new CGXGridMarkEditHeaderImp);
		m_pMarkEditHeaderImp = new CGXGridMarkEditHeaderImp;
	}
}

void CGXGridMarkEditHeaderImp::MarkEdit(CGXGridCore* pGrid, ROWCOL nEditRow, ROWCOL nEditCol, UINT direction, UINT flags)
{
	// Invalidate the row and column header
	if (pGrid->IsLockUpdate())
		return;

	flags &= (GX_UPDATENOW | GX_SMART | GX_INVALIDATE);

	// TRACE2("CGXGridCore: BEGIN MarkEdit(%d, %d)\n", bShow, direction);

	ROWCOL bottomRow = pGrid->GetLastVisibleRow();
	ROWCOL rightCol = pGrid->GetLastVisibleCol();

	BOOL bVert = (!direction || direction == GX_VERT);
	BOOL bHorz = (!direction || direction == GX_HORZ);

	// check, if row or column is visible
	if ((pGrid->IsFrozenRow(nEditRow) || nEditRow >= pGrid->GetTopRow()) && nEditRow <= pGrid->GetRowCount()
		|| (pGrid->IsFrozenCol(nEditCol) || nEditCol >= pGrid->GetLeftCol()) && nEditCol <= pGrid->GetColCount())
	{
		// Bottom-Right cell
		if (nEditRow <= bottomRow || nEditCol <= rightCol)
		{
			// Row Header
			if (bVert && pGrid->m_pParam->m_pProperties->GetMarkRowHeader()
				&& (pGrid->IsFrozenRow(nEditRow) || nEditRow >= pGrid->GetTopRow())
				&& nEditRow <= bottomRow)
			{
				CRect rectItem = pGrid->CalcRectFromRowColExEx(nEditRow, 0, nEditRow, pGrid->GetHeaderCols());

				ASSERT(rectItem.right >= rectItem.left && rectItem.bottom >= rectItem.top);
				if (rectItem.Width() > 1 && rectItem.Height() > 1)
				{
					pGrid->m_bLockGDIObjects = TRUE;   // avoid emptying GDI-objects-cache
					pGrid->InvalidateRect(rectItem);
					if (flags & GX_UPDATENOW || flags & GX_SMART)
						pGrid->UpdateWindow();

					pGrid->m_bLockGDIObjects = FALSE;
					
					// QA: 31744
					pGrid->FreeObjectCache();
				}
			}

			// Column Header
			if (bHorz && pGrid->m_pParam->m_pProperties->GetMarkColHeader()
				&& (pGrid->IsFrozenCol(nEditCol) || nEditCol >= pGrid->GetLeftCol())
				&& nEditCol <= rightCol)
			{
				CRect rectItem = pGrid->CalcRectFromRowColExEx(0, nEditCol, pGrid->GetHeaderRows(), nEditCol);

				ASSERT(rectItem.right >= rectItem.left && rectItem.bottom >= rectItem.top);
				if (rectItem.Width() > 1 && rectItem.Height() > 1)
				{
					pGrid->m_bLockGDIObjects = TRUE;   // avoid emptying GDI-objects-cache
					pGrid->InvalidateRect(rectItem);
					if (flags & GX_UPDATENOW || flags & GX_SMART)
						pGrid->UpdateWindow();

					pGrid->m_bLockGDIObjects = FALSE;
					
					// QA: 31744
					pGrid->FreeObjectCache();
				}
			}
		}

	}

	// TRACE2("CGXGridCore: END   MarkEdit(%d, %d)\n", bShow, direction);
}

BOOL CGXGridMarkEditHeaderImp::GetMarkHeaderState(CGXControl* pControl, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style)
{
	// Unused:
	style;

	CGXGridCore* pGrid = pControl->Grid();
	BOOL bPressed = FALSE;
	ROWCOL ncRow, ncCol;
	BOOL bCurrent = pGrid->GetCurrentCell(ncRow, ncCol);

	CGXRange r(nRow, nCol);
	pGrid->GetCellRangeRowCol(nRow, nCol, r);

	if (ncRow <= pGrid->GetHeaderRows() || ncCol <= pGrid->GetHeaderCols())
		// headers is active Edit Cell
		//
		; // bPressed = pGrid->IsCurrentCell(nRow, nCol);
	else
	{
		// Row or Column of active Edit Cell
		bPressed |= nRow > 0
			&& !pGrid->GetParam()->IsSpecialMode(GX_MODELISTBOX)
			&& bCurrent && ncRow >= r.top && ncRow <= r.bottom
			&& pGrid->GetParam()->GetProperties()->GetMarkRowHeader();

		bPressed |= nCol > 0
			&& bCurrent && ncCol >= r.left && ncCol <= r.right
			&& pGrid->GetParam()->GetProperties()->GetMarkColHeader();
	}

	// currently Tracking size of this Row or Col ==> draw a pressed Button
	int nTrackingMode;
	ROWCOL nTracking;
	BOOL b = pGrid->IsTracking(&nTrackingMode, &nTracking);
	bPressed |= b &&
		(nTrackingMode & GX_TRACKWIDTH
			&& !pGrid->GetParam()->IsEnableTrackColWidth(GX_TRACK_NOPRESSEDHEADER)
			&& r.left <= nTracking
			&& r.right >= nTracking
		|| nTrackingMode & GX_TRACKHEIGHT
			&& !pGrid->GetParam()->IsEnableTrackRowHeight(GX_TRACK_NOPRESSEDHEADER)
			&& r.top <= nTracking
			&& r.bottom >= nTracking);

	return bPressed;
}
