///////////////////////////////////////////////////////////////////////////////
// gxselgrx.cpp : Implementation of Excel-like selection frame
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

#ifndef _GXMSG_H_
#include "grid\gxmsg.h"
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXCORMSG")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

class CGXGridExcelLikeFrameImp: public CGXAbstractGridExcelLikeFrameImp
{
public:
	virtual void DrawInvertFrame(CGXGridCore* pGrid, CDC* pDC, const CRect& rc, const CRect& rectClip, BOOL bTopVisible, BOOL bLeftVisible, int nMarker, BOOL bOnlyMarker);
	virtual void DrawSelectionRangeFrame(CGXGridCore* pGrid, CDC* pDC, const CGXRange& rg, int nMarker, BOOL bOnlyMarker);
	virtual void DrawSelectionFrame(CGXGridCore* pGrid, CDC* pDC, BOOL bDrawOld, const CGXRange* pNewRange);
	virtual void ToggleSelectionFrameMarker(CGXGridCore* pGrid);
	virtual BOOL LockSelectionFrame(CGXGridCore* pGrid, BOOL bLock, BOOL bCreateHint);
};

void CGXGridCore::ImplementExcelLikeFrame()
{
	if (m_pExcelLikeFrameImp == NULL)
	{
		// QA: 31521 Removal from AutoDeletePtr
		//AutoDeletePtr(m_pExcelLikeFrameImp = new CGXGridExcelLikeFrameImp);
		m_pExcelLikeFrameImp = new CGXGridExcelLikeFrameImp;
	}

	ImplementUserSelectRange();
}

void CGXGridExcelLikeFrameImp::DrawInvertFrame(CGXGridCore* pGrid, CDC* pDC, const CRect& rc, const CRect& rectClip, BOOL bTopVisible, BOOL bLeftVisible, int nMarker, BOOL bOnlyMarker)
{
	// Gridlinesbehavior
	CRect r = rc;

	int nyTop = bTopVisible?0:1;

	// New grid line mode (cell borders at bottom right of cell)
	if (pGrid->GetParam()->GetNewGridLineMode())
	{
		r -= CPoint(1, 1);

		if (!bOnlyMarker)
		{
			if (bTopVisible)
			{
				// Outside top border
				GXInvertRect(pDC, CRect(r.left-1, r.top-1, r.right+2, r.top+1), rectClip);

				// Inside top border
				GXInvertRect(pDC, CRect(r.left+2, r.top+2, r.right-2, r.top+3), rectClip);
			}
			else if (bLeftVisible && r.bottom > r.top) // last row is completely visible
			{
				// Top left pixel (at grid line)
				GXInvertRect(pDC, CRect(r.left+2, r.top, r.left+3, r.top+3), rectClip);
				GXInvertRect(pDC, CRect(r.right-2, r.top, r.right-1, r.top+1), rectClip);
			}

			if (bLeftVisible)
			{
				// Outside left border
				GXInvertRect(pDC, CRect(r.left-1, r.top+1, r.left+1, r.bottom+2), rectClip);

				// Inside left border
				GXInvertRect(pDC, CRect(r.left+2, r.top+3, r.left+3, r.bottom-2), rectClip);
			}
			else if (bTopVisible && r.right > r.left) // last column is completely visible
			{
				// Bottom left pixel (at grid line)
				GXInvertRect(pDC, CRect(r.left, r.bottom-2, r.left+2, r.bottom-1), rectClip);
				GXInvertRect(pDC, CRect(r.left, r.top+2, r.left+2, r.top+3), rectClip);
			}

			// Outside bottom border
			GXInvertRect(pDC, CRect(r.left+1, r.bottom+1, r.right+1, r.bottom+2), rectClip);

			// Outside right border
			GXInvertRect(pDC, CRect(r.right+1, r.top+1, r.right+2, r.bottom+2), rectClip);

			// Inside bottom border
			GXInvertRect(pDC, CRect(r.left+2, r.bottom-2, r.right-2, r.bottom-1), rectClip);

			// Inside right border
			GXInvertRect(pDC, CRect(r.right-2, r.top+2-nyTop, r.right-1, r.bottom-1), rectClip);
		}
/*		// check nMarker (in case full rows or cols are selected)
		switch (nMarker)
		{
		case GX_LEFT:
			GXInvertRect(pDC, CRect(r.left-1, r.bottom-2, r.left+2, r.bottom+3), rectClip);
			GXInvertRect(pDC, CRect(r.left-2, r.bottom-1, r.left+3, r.bottom+2), rectClip);
			GXInvertRect(pDC, CRect(r.left-2, r.bottom+2, r.left-1, r.bottom+3), rectClip);
			break;

		case GX_TOP:
			GXInvertRect(pDC, CRect(r.right-1, r.top-2, r.right+2, r.top+3), rectClip);
			GXInvertRect(pDC, CRect(r.right-2, r.top-1, r.right+3, r.top+2), rectClip);
			GXInvertRect(pDC, CRect(r.right+2, r.top-2, r.right+3, r.top-1), rectClip);
			break;

		default:
			GXInvertRect(pDC, CRect(r.right-1, r.bottom-2, r.right+2, r.bottom+3), rectClip);
			GXInvertRect(pDC, CRect(r.right-2, r.bottom-1, r.right+3, r.bottom+2), rectClip);
			GXInvertRect(pDC, CRect(r.right+2, r.bottom+2, r.right+3, r.bottom+3), rectClip);
			break;
		}*/
	}
	else    // Old grid line mode (cell borders at top left of cell)
	{
		if (!bOnlyMarker)
		{
			if (bTopVisible)
			{
				// Outside top border
				GXInvertRect(pDC, CRect(r.left-1, r.top-1, r.right+2, r.top), rectClip);

				// Inside top border
				GXInvertRect(pDC, CRect(r.left+2, r.top+2, r.right-2, r.top+3), rectClip);
			}
			else if (bLeftVisible && r.bottom > r.top) // last row is completely visible
			{
				// Top left pixel (at grid line)
				GXInvertRect(pDC, CRect(r.left+2, r.top, r.left+3, r.top+3), rectClip);
				GXInvertRect(pDC, CRect(r.right-2, r.top, r.right-1, r.top+1), rectClip);
			}

			if (bLeftVisible)
			{
				// Outside left border
				GXInvertRect(pDC, CRect(r.left-1, r.top, r.left, r.bottom+2), rectClip);

				// Inside left border
				GXInvertRect(pDC, CRect(r.left+2, r.top+3, r.left+3, r.bottom-2), rectClip);
			}
			else if (bTopVisible && r.right > r.left) // last column is completely visible
			{
				// Bottom left pixel (at grid line)
				GXInvertRect(pDC, CRect(r.left, r.bottom-2, r.left+2, r.bottom-1), rectClip);
				GXInvertRect(pDC, CRect(r.left, r.top+2, r.left+2, r.top+3), rectClip);
			}

			// Outside bottom border
			GXInvertRect(pDC, CRect(r.left, r.bottom, r.right, r.bottom+2), rectClip);

			// Outside right border
			GXInvertRect(pDC, CRect(r.right, r.top, r.right+2, r.bottom+2), rectClip);

			// Inside bottom border
			GXInvertRect(pDC, CRect(r.left+2, r.bottom-2, r.right-2, r.bottom-1), rectClip);

			// Inside right border
			GXInvertRect(pDC, CRect(r.right-2, r.top+2-nyTop, r.right-1, r.bottom-1), rectClip);
		}
	}

	// check nMarker (in case full rows or cols are selected)
	switch (nMarker)
	{
	case GX_LEFT:
		GXInvertRect(pDC, CRect(r.left+2, r.bottom-1, r.left+7, r.bottom+2), rectClip);
		GXInvertRect(pDC, CRect(r.left+3, r.bottom-3, r.left+7, r.bottom-2), rectClip);
		GXInvertRect(pDC, CRect(r.left+1, r.bottom-2, r.left+6, r.bottom+3), rectClip);
		GXInvertRect(pDC, CRect(r.left+1, r.bottom+2, r.left+2, r.bottom+3), rectClip);
		break;

	case GX_TOP:
		GXInvertRect(pDC, CRect(r.right-1, r.top+2, r.right+2, r.top+7), rectClip);
		GXInvertRect(pDC, CRect(r.right-3, r.top+3, r.right-2, r.top+7), rectClip);
		GXInvertRect(pDC, CRect(r.right-2, r.top+1, r.right+3, r.top+6), rectClip);
		GXInvertRect(pDC, CRect(r.right+2, r.top+1, r.right+3, r.top+2), rectClip);
		break;

	default:
		GXInvertRect(pDC, CRect(r.right-1, r.bottom-2, r.right+2, r.bottom+3), rectClip);
		GXInvertRect(pDC, CRect(r.right-2, r.bottom-1, r.right+3, r.bottom+2), rectClip);
		GXInvertRect(pDC, CRect(r.right+2, r.bottom+2, r.right+3, r.bottom+3), rectClip);
		break;
	}
}

void CGXGridExcelLikeFrameImp::DrawSelectionRangeFrame(CGXGridCore* pGrid, CDC* pDC, const CGXRange& rg, int nMarker, BOOL bOnlyMarker)
{
	if (pGrid->IsLockUpdate())
		return;

	ROWCOL  nfc = pGrid->GetFrozenCols();
	ROWCOL  nfr = pGrid->GetFrozenRows();
	ROWCOL  nLeftCol = pGrid->GetLeftCol();
	ROWCOL  nTopRow = pGrid->GetTopRow();

	ROWCOL nlRow = nTopRow-1;
	while (nlRow > nfr && pGrid->GetRowHeight(nlRow) == 0)
		nlRow--;

	ROWCOL nlCol = nLeftCol-1;
	while (nlCol > nfr && pGrid->GetColWidth(nlCol) == 0)
		nlCol--;

	BOOL bAnyColVisible = rg.left <= nfc || rg.right >= nlCol && rg.left <= pGrid->GetLastVisibleCol();
	BOOL bAnyRowVisible = rg.top <= nfr || rg.bottom >= nlRow && rg.top <= pGrid->GetLastVisibleRow();

	if (!bAnyColVisible || !bAnyRowVisible)
		return;

	// Last row completely visible (with outside border)
	BOOL bLastRowFullyVisible = rg.bottom >= nTopRow;
	BOOL bLastColFullyVisible = rg.right >= nLeftCol;

	// Only the bottom border of the last row is visible
	BOOL bLastRowOnlyBorderVisible = !bLastRowFullyVisible && rg.bottom >= nlRow && rg.bottom < nTopRow
		|| rg.bottom == nfr && rg.bottom+1 == nTopRow;
	BOOL bLastColOnlyBorderVisible = !bLastColFullyVisible && rg.right >= nlCol && rg.right < nLeftCol
		|| rg.right == nfc && rg.right+1 == nLeftCol;

	// First row is completely visible (with outside border)
	BOOL bFirstRowVisible = rg.top <= nfr || rg.top > nTopRow || rg.top == nTopRow && nfr+1 == nTopRow;
	BOOL bFirstColVisible = rg.left <= nfc || rg.left > nLeftCol || rg.left == nLeftCol && nfc+1 == nLeftCol;

	BOOL bFirstRowClipBorder = !bFirstRowVisible && rg.top == nTopRow;
	BOOL bFirstColClipBorder = !bFirstColVisible && rg.left == nLeftCol;

	// I have to take care on frozen rows and columns:
	//    +--|-----------+
	//    |r0|r2         |
	//   ======================= top row
	//    |r1|r3         |
	//    |  |           |r
	//    +--|-----------+
	//       |
	//      left column

	CRect rectGrid = pGrid->GetGridRect();
	int nyMax = rectGrid.Height();
	int nxMax = rectGrid.Width();

	int nxLeft = pGrid->CalcSumOfColWidths(0, nfc, nxMax);
	int nyTop = pGrid->CalcSumOfRowHeights(0, nfr, nyMax);

	CRect r[4], rcClip[4];
	BOOL bTopRow[4], bLeftCol[4];
	int i;
	for (i = 0; i < 4; i++)
	{
		rcClip[i].SetRectEmpty();
		r[i].SetRectEmpty();
		bTopRow[i] = bLeftCol[i] = FALSE;
	}

	if (rg.left <= nfc && rg.top < nTopRow)
	{
		r[0].top = (rg.top > 0 ? pGrid->CalcSumOfRowHeights(0, rg.top-1, nyMax) : 0);
		r[0].left = (rg.left > 0 ? pGrid->CalcSumOfColWidths(0, rg.left-1,nxMax) : 0);
		r[0].bottom = r[0].top + pGrid->CalcSumOfRowHeights(rg.top, min(nfr, rg.bottom), nyMax);
		r[0].right = r[0].left + pGrid->CalcSumOfColWidths(rg.left, min(nfc, rg.right), nxMax);

		rcClip[0].SetRect(0, 0, nxLeft, nyTop);
		bTopRow[0] = bLeftCol[0] = TRUE;
	}

	if (rg.left <= nfc && rg.bottom >= nTopRow)
	{
		if (bFirstRowVisible || bFirstRowClipBorder)
			r[1].top = pGrid->CalcSumOfClientRowHeights(0, pGrid->GetClientRow(rg.top)-1, nyMax);
		else
			r[1].top = nyTop;
		r[1].left = rg.left > 0 ? pGrid->CalcSumOfColWidths(0, rg.left-1, nxMax) : 0;
		r[1].bottom = nyTop + pGrid->CalcSumOfRowHeights(nTopRow, rg.bottom, nyMax);
		r[1].right = r[1].left + pGrid->CalcSumOfColWidths(rg.left, rg.right, nxMax);

		rcClip[1].SetRect(0, nyTop, nxLeft, rectGrid.bottom);
		bLeftCol[1] = TRUE;
		bTopRow[1] = rg.top >= nTopRow;
	}

	if (rg.top <= nfr && rg.right >= nLeftCol)
	{
		r[2].top = rg.top > 0 ? pGrid->CalcSumOfRowHeights(0, rg.top-1, nyMax) : 0;
		if (bFirstColVisible || bFirstColClipBorder)
			r[2].left = pGrid->CalcSumOfClientColWidths(0, pGrid->GetClientCol(rg.left)-1, nxMax);
		else
			r[2].left = nxLeft;
		r[2].bottom = r[2].top + pGrid->CalcSumOfRowHeights(rg.top, rg.bottom, nyMax);
		r[2].right = nxLeft + pGrid->CalcSumOfColWidths(nLeftCol, rg.right, nxMax);

		rcClip[2].SetRect(nxLeft, 0, rectGrid.right, nyTop);
		bLeftCol[2] = rg.left >= nLeftCol;
		bTopRow[2] = TRUE;
	}

	if ((rg.bottom >= nTopRow || bLastRowOnlyBorderVisible)
		&& (rg.right >= nLeftCol || bLastColOnlyBorderVisible))
	{
		if (bFirstRowVisible || bFirstRowClipBorder)
			r[3].top = pGrid->CalcSumOfClientRowHeights(0, pGrid->GetClientRow(rg.top)-1, nyMax);
		else
			r[3].top = nyTop;
		if (bFirstColVisible || bFirstColClipBorder)
			r[3].left = pGrid->CalcSumOfClientColWidths(0, pGrid->GetClientCol(rg.left)-1, nxMax);
		else
			r[3].left = nxLeft;
		r[3].bottom = nyTop + pGrid->CalcSumOfRowHeights(nTopRow, rg.bottom, nyMax);
		r[3].right = nxLeft + pGrid->CalcSumOfColWidths(nLeftCol, rg.right, nxMax);

		rcClip[3].SetRect(nxLeft, nyTop, rectGrid.right, rectGrid.bottom);
		bTopRow[3] = rg.top >= nTopRow;
		bLeftCol[3] = rg.left >= nLeftCol;
	}

	// Now draw the frames (and clip them as necessary)
	for (i = 0; i < 4; i++)
	{
		if (!rcClip[i].IsRectEmpty())
			pGrid->DrawInvertFrame(pDC, r[i] + rectGrid.TopLeft(), rcClip[i] + rectGrid.TopLeft(), bTopRow[i], bLeftCol[i], nMarker, bOnlyMarker);
	}
}

void CGXGridExcelLikeFrameImp::DrawSelectionFrame(CGXGridCore* pGrid, CDC* pDC, BOOL bDrawOld, const CGXRange* pNewRange)
{
	if (!pGrid->GetParam()->GetExcelLikeSelectionFrame() || pGrid->m_bLockDrawSelectionFrame)
		return;

	CRect rectGrid = pGrid->GetGridRect();
	CRect rc;

	if (bDrawOld && pGrid->m_rgLastSelectionFrame.IsValid() && pDC)
		pGrid->DrawSelectionRangeFrame(pDC, pGrid->m_rgLastSelectionFrame, pGrid->m_nLastSelectionFrameMarker);

	if (pNewRange)
	{
		CGXRange rg = *pNewRange;

		if (rg.top == 0 && rg.left == 0)
			rg.SetTable();
		else if (rg.left == 0)
			rg.SetRows(rg.top, rg.bottom);
		else if (rg.top == 0)
			rg.SetCols(rg.left, rg.right);
		else
			rg.SetCells(rg.top, rg.left, rg.bottom, rg.right);

		// When rows are selected, draw marker at bottom-left
		// When columns are selected, draw marker at top-right
		int nMarker = 0;

		if (rg.IsCols())
			nMarker = GX_TOP;
		else if (rg.IsRows())
			nMarker = GX_LEFT;

		rg.ExpandRange(pGrid->GetHeaderRows()+1, pGrid->GetHeaderCols()+1, pGrid->GetRowCount(), pGrid->GetColCount());

		pGrid->m_rgLastSelectionFrame = rg;
		pGrid->m_nLastSelectionFrameMarker = nMarker;
    
    	if (pDC)
			pGrid->DrawSelectionRangeFrame(pDC, pGrid->m_rgLastSelectionFrame, nMarker);
	}
}

void CGXGridExcelLikeFrameImp::ToggleSelectionFrameMarker(CGXGridCore* pGrid)
{
	// Hide marker before scrolling and show it afterwards
	if (pGrid->m_nLastSelectionFrameMarker && pGrid->m_rgLastSelectionFrame.IsValid())
		pGrid->DrawSelectionRangeFrame(pGrid->GetGridDC(), pGrid->m_rgLastSelectionFrame, pGrid->m_nLastSelectionFrameMarker, TRUE);
}

BOOL CGXGridExcelLikeFrameImp::LockSelectionFrame(CGXGridCore* pGrid, BOOL bLock, BOOL bCreateHint)
{                 
	if (pGrid->GetParam() == NULL || !pGrid->GetParam()->GetExcelLikeSelectionFrame())
		return FALSE;

 	BOOL bOldLock = pGrid->m_bLockDrawSelectionFrame;

	if (bLock != bOldLock)
	{
		CDC* pDC = NULL;
		
		if (!pGrid->IsLockUpdate() && pGrid->m_pGridWnd->IsWindowVisible())
		{
			pDC = new CClientDC(pGrid->m_pGridWnd);
			pGrid->PrepareDCAttribs(pDC);
		}

		pGrid->m_bLockDrawSelectionFrame = FALSE;

		if (bLock)
			pGrid->DrawSelectionFrame(pDC, TRUE, NULL);
		else if (!pGrid->GetParam()->GetRangeList()->IsEmpty())
			pGrid->DrawSelectionFrame(pDC, FALSE, pGrid->GetParam()->GetRangeList()->GetTail());
                                          
		delete pDC;
		                                       
		pGrid->m_bLockDrawSelectionFrame = bLock;
	}

	// Create Hint
	if (pGrid->m_pUpdateHintImp && bCreateHint && pGrid->m_bHintsEnabled)
		pGrid->m_pUpdateHintImp->HintLockSelectionFrame(pGrid, bLock);

	return bOldLock;
}

