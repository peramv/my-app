///////////////////////////////////////////////////////////////////////////////
// gxmergcel.cpp: implementation of merge cell functionality
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

// Headers

#ifdef _GXDLL
#undef AFXAPI_DATA
#define AFXAPI_DATA __based(__segname("_DATA"))
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

#ifndef _GXSTYLES_H_
#include "grid\gxstyles.h"
#endif

#ifndef _GXDELAYR_H_
#include "grid\gxdelayr.h"
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXSPAN")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

class CGXGridMergeCellsImp: public CGXAbstractGridMergeCellsImp
{
public:
	virtual void SetMergeCellsMode(CGXGridCore* pGrid, WORD nMode, BOOL bRedraw);
	virtual void DelayMergeCells(CGXGridCore* pGrid, const CGXRange& range, ROWCOL nMaxRows, ROWCOL nMaxCols);
	virtual BOOL EvalMergeCells(CGXGridCore* pGrid, const CGXRange& range, BOOL bUpdate, CGXRange* prgBoundary, BOOL bLookupStyle);
	virtual CGXRange* GetMergedCellsRowCol(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, CGXRange& range, int mtType);
	virtual BOOL CanMergeCell(CGXGridCore* pGrid, CGXControl* pControl, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, int mtType);
	virtual BOOL CanMergeCells(CGXGridCore* pGrid, const CGXStyle& style1, const CGXStyle& style2);
	virtual BOOL SetMergedCellsRowCol(CGXGridCore* pGrid, int mtType, ROWCOL nRow, ROWCOL nCol, ROWCOL nToRow, ROWCOL nToCol, UINT flags);
	virtual void UpdateMergedCellsRowCol(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, ROWCOL nOldToRow, ROWCOL nOldToCol, UINT flags, BOOL bCreateHint);
	virtual void MergeMergedCells(CGXGridCore* pGrid, CGXRange& range);

	enum MergeCellType
	{
		mtHorz = 0,
		mtVert = 1
	};

	// Implementation - EvalMergeCells implementation
	BOOL EvalAllMergeCells(CGXGridCore* pGrid, CGXRange range, BOOL bUpdate = TRUE, CGXRange* prgBoundary = NULL, BOOL bLookupStyle = FALSE);
	BOOL EvalDelayedMergeCells(CGXGridCore* pGrid, CGXRange range, BOOL bUpdate = TRUE, CGXRange* prgBoundary = NULL, BOOL bLookupStyle = FALSE);
	BOOL MergeCell(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, CGXRange* prgBoundary = NULL, BOOL bLookupStyle = FALSE);
	BOOL MCellImplHorz(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol1, ROWCOL nCol2, CGXRange* prgBoundary = NULL, BOOL bLookupStyle = FALSE);
	BOOL MCellImplVert(CGXGridCore* pGrid, ROWCOL nCol, ROWCOL nRow1, ROWCOL nRow2, CGXRange* prgBoundary = NULL, BOOL bLookupStyle = FALSE);

	// Implementation - Merge Cell Ranges
	BOOL StoreMergedCellsRowCol(CGXGridCore* pGrid, int mtType, ROWCOL nRow, ROWCOL nCol, ROWCOL nToRow, ROWCOL nToCol, BOOL bSet);
};

void CGXGridCore::ImplementMergeCells()
{
	if (m_pMergeCellsImp == NULL)
	{
		// QA: 31521 Removal from AutoDeletePtr
		//AutoDeletePtr(m_pMergeCellsImp = new CGXGridMergeCellsImp);
		m_pMergeCellsImp = new CGXGridMergeCellsImp;
	}

	ImplementDrawSpannedCells();
	CGXSpanCellPool::ImplementSpanCellPool();
	CGXDelayedRangePool::ImplementDelayedRangePool();
	CGXStyle::ImplementCompareSubset();
}

/////////////////////////////////////////////////////////////////////////////
// Merging Cells

// SetMergeCellsMode
//
// nMode can be one of
// gxnMergeDisable - Disable merge cells
// gxnMergeDelayEval - Delay evaluation of merge cells (recommended)
// gxnMergeEvalOnDisplay - Always evaluate cells before they are displayed (slow)
//

void CGXGridMergeCellsImp::SetMergeCellsMode(CGXGridCore* pGrid, WORD nMode, BOOL bRedraw /*=TRUE*/)
{
	CGXGridParam* pParam = pGrid->GetParam();

	if (nMode != pParam->m_wMergeCellsMode)
	{
		pParam->m_wMergeCellsMode = nMode;

		// Clean up merge cells state
		delete pParam->m_pDelayedMergeCells;
		delete pParam->m_pHorzMergeCells;
		delete pParam->m_pVertMergeCells;

		pParam->m_pDelayedMergeCells = NULL;
		pParam->m_pHorzMergeCells = NULL;
		pParam->m_pVertMergeCells = NULL;

		switch (nMode&0x03)
		{
		case gxnMergeDisable:
			break;

		case gxnMergeEvalOnDisplay:
			// Reinit float cells state
			pParam->m_pHorzMergeCells = new CGXSpanCellPool;
			pParam->m_pVertMergeCells = new CGXSpanCellPool;
			break;

		case gxnMergeDelayEval:
			// Reinit float cells state
			pParam->m_pHorzMergeCells = new CGXSpanCellPool;
			pParam->m_pVertMergeCells = new CGXSpanCellPool;
			pParam->m_pDelayedMergeCells = new CGXDelayedRangePool;

			// Force all cells to be recalculated
			pGrid->DelayMergeCells(CGXRange().SetTable());
			break;
		}
	}

	if (bRedraw)
		pGrid->Redraw();
}

// DelayMergeCells
//
// Delays the evaluation of the given range of cells
// and optionally evaluates the


// DWORD mnt1, mnt2, mnt3, mnt4, mnt5, mnt6, mnt7, mnt8;

void CGXGridMergeCellsImp::DelayMergeCells(CGXGridCore* pGrid, const CGXRange& range, ROWCOL nMaxRows, ROWCOL nMaxCols)
{
	CGXGridParam* pParam = pGrid->GetParam();

	if ((pParam->m_wMergeCellsMode&0x03) != gxnMergeDelayEval)
		return;

	// Expand range to current dimension
	CGXRange rg = range;
	ROWCOL nRowCount = pGrid->GetRowCount();
	ROWCOL nColCount = pGrid->GetColCount();

	rg.ExpandRange(0, 0, pGrid->GetRowCount(), pGrid->GetColCount());

	// Expand over hidden rows and columns
	if ((pParam->m_wMergeCellsMode&gxnMergeOverHidden) > 0)
	{
		while (pGrid->IsRowHidden(rg.top) && rg.top > 0)
			rg.top--;

		while (pGrid->IsRowHidden(rg.bottom) && rg.bottom < nRowCount)
			rg.bottom++;

		while (pGrid->IsColHidden(rg.left) && rg.left > 0)
			rg.left--;

		while (pGrid->IsColHidden(rg.right) && rg.right < nColCount)
			rg.right++;
	}


	// Hoprizontal
	pParam->m_pDelayedMergeCells->DelayRange(rg);

	if (nMaxRows != GX_INVALID)
		pParam->m_pDelayedMergeCells->SetRowCount(nMaxRows);

	if (nMaxCols != GX_INVALID)
		pParam->m_pDelayedMergeCells->SetColCount(nMaxCols);
}

// EvalMergeCells
//
// Evaluates those cells from the given range if they want to float
// other cells

BOOL CGXGridMergeCellsImp::EvalMergeCells(CGXGridCore* pGrid, const CGXRange& range,
	BOOL bUpdate, //= TRUE
	CGXRange* prgBoundary, // = NULL
	BOOL bLookupStyle) //
{
	CGXGridParam* pParam = pGrid->GetParam();

	// Is evaluation of floating cells temporary or completely turned off?
	if (pGrid->m_bLockEvalMergeCells)
		return FALSE;

	// Different modes
	switch (pParam->m_wMergeCellsMode&0x03)
	{
	case gxnMergeDisable:
		return FALSE;

	case gxnMergeDelayEval:
		return EvalDelayedMergeCells(pGrid, range, bUpdate, prgBoundary, bLookupStyle);

	case gxnMergeEvalOnDisplay:
		return EvalAllMergeCells(pGrid, range, bUpdate, prgBoundary, bLookupStyle);

	default:
		TRACE(_T("Warning: pParam->m_wMergeCellsMode invalid\n"));
		return FALSE;
	}
}

// EvalAllMergeCells
//
// Evaluates all cells from the given range if they want to float
// other cells.

BOOL CGXGridMergeCellsImp::EvalAllMergeCells(CGXGridCore* pGrid, CGXRange range, BOOL bUpdate, CGXRange* prgBoundary, BOOL bLookupStyle)
{
	BOOL bLock = FALSE;
	if (!bUpdate)
		bLock = pGrid->LockUpdate(TRUE);

	CGXGridParam* pParam = pGrid->GetParam();

	range.ExpandRange(0, 0, pGrid->GetRowCount(), pGrid->GetColCount());

	// Calculate size

	BOOL bMergeDone = FALSE;

	pGrid->m_MergeCellData.InitColOffset(range.left);
	pGrid->m_MergeCellData.apStylesArray.SetSize(pGrid->m_MergeCellData.GetIndex(range.right+1));

	for (ROWCOL nRow = range.top; nRow <= range.bottom; nRow++)
	{
		if ((pParam->m_wMergeCellsMode&gxnMergeOverHidden) > 0 || !pGrid->IsRowHidden(nRow))
		{
			for (ROWCOL nCol = range.left; nCol <= range.right; nCol++)
			{
				if ((pParam->m_wMergeCellsMode&gxnMergeOverHidden) > 0 || !pGrid->IsColHidden(nCol))
					bMergeDone |= MergeCell(pGrid, nRow, nCol, prgBoundary, bLookupStyle);
			}
		}

		pGrid->m_MergeCellData.Reset(pGrid);
	}

	if (!bUpdate)
		pGrid->LockUpdate(bLock);

	return bMergeDone;
}

// EvalDelayedMergeCells
//
// Evaluates those cells from the given range which
// were previously marked as delayed with DelayMergeCells

BOOL CGXGridMergeCellsImp::EvalDelayedMergeCells(CGXGridCore* pGrid, CGXRange range,
	BOOL bUpdate, //= TRUE
	CGXRange* prgBoundary, // = NULL
	BOOL bLookupStyle) //
{
	CGXGridParam* pParam = pGrid->GetParam();

	ROWCOL nColCount = pGrid->GetColCount();
	ROWCOL nRowCount = pGrid->GetRowCount();

	range.ExpandRange(0, 0, nRowCount, nColCount);

	BOOL bMergeDone = FALSE;

	CDWordArray dwColStart;
	CDWordArray dwColEnd;

	if (pParam->m_pDelayedMergeCells->EvalRows(range, dwColStart, dwColEnd))
	{
		BOOL bLock = FALSE;
		if (!bUpdate)
			bLock = pGrid->LockUpdate(TRUE);

		pGrid->m_MergeCellData.InitColOffset(range.left);

		for (int nIndex = 0; nIndex < dwColStart.GetSize(); nIndex++)
		{
			ROWCOL nRow = (ROWCOL) nIndex + range.top;

			if (((pParam->m_wMergeCellsMode&gxnMergeOverHidden) > 0 || !pGrid->IsRowHidden(nRow)) && dwColEnd[nIndex] >= dwColStart[nIndex])
			{
				// TRACE("Row = %d: %d, %d\n", nRow, dwColStart[nIndex], dwColEnd[nIndex]);

				for (ROWCOL nCol = dwColStart[nIndex]; nCol <= dwColEnd[nIndex]; nCol++)
				{
					if ((pParam->m_wMergeCellsMode&gxnMergeOverHidden) > 0 || !pGrid->IsColHidden(nCol))
						bMergeDone |= MergeCell(pGrid, nRow, nCol, prgBoundary, bLookupStyle);
				}
			}

			pGrid->m_MergeCellData.Reset(pGrid);
		}

		if (!bUpdate)
			pGrid->LockUpdate(bLock);
	}

	return bMergeDone;
}

// CanMergeCell
//
// Called to determins if the specified cell can float other cells or
// if it can be flooded.

BOOL CGXGridMergeCellsImp::CanMergeCell(CGXGridCore* pGrid, CGXControl* pControl, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, int mtType)
{
	nRow, nCol;

	CGXGridParam* pParam = pGrid->GetParam();

	if ((pParam->m_wMergeCellsMode&gxnMergeOverHidden) > 0
		&& (pGrid->IsRowHidden(nRow) || pGrid->IsColHidden(nCol)))
		return TRUE;

	if ((pParam->m_wMergeCellsMode&0x03) == gxnMergeDisable
		|| !style.GetIncludeMergeCell())
		return FALSE;
 
	// horizontal
	BOOL bHorz = 
		mtType == mtHorz
		&& (style.GetMergeCell() & GX_MERGE_HORIZONTAL) > 0
		&& !(pParam->m_wMergeCellsMode & gxnMergeVertOnly);

	// vertical
	BOOL bVert = 
		mtType == mtVert
		&& (style.GetMergeCell() & GX_MERGE_VERTICAL) > 0
		&& !(pParam->m_wMergeCellsMode & gxnMergeHorzOnly);


	if (bHorz || bVert)
	{
		CGXRange rgCovered;
		if (pGrid->GetCoveredCellsRowCol(nRow, nCol, rgCovered))
			return FALSE;

		return pControl->CanMergeCell(nRow, nCol, style, mtType);
	}

	return FALSE;
}

BOOL CGXGridMergeCellsImp::CanMergeCells(CGXGridCore* pGrid, const CGXStyle& style1, const CGXStyle& style2)
{
	GX_UNUSED_ALWAYS(pGrid);

	if (style1.GetIncludeMergeCell() && style2.GetIncludeMergeCell())
	{
		unsigned nCombinedFlags = style1.GetMergeCell() & style2.GetMergeCell();

		if ((nCombinedFlags & GX_MERGE_COMPVALUE) > 0)
			return style1.GetValueRef() == style2.GetValueRef();
		else
			return style1.IsSubSet(style2) && style2.IsSubSet(style1);
	}

	return FALSE;
}

// MergeCell
//
// Evaluates the given cell.
//
// prgBoundary will be extended when the cell has become a floating
// cell or if it was a floating cell.

BOOL CGXGridMergeCellsImp::MergeCell(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, CGXRange* prgBoundary, BOOL bLookupStyle)
{
	CGXGridParam* pParam = pGrid->GetParam();

	if ((pParam->m_wMergeCellsMode&0x03) == gxnMergeDisable)
		return FALSE;

	BOOL b1 = FALSE;
	BOOL b2 = FALSE;
	BOOL b3 = FALSE;
	BOOL b4 = FALSE;

	ROWCOL nColCount = pGrid->GetColCount();
	ROWCOL nRowCount = pGrid->GetRowCount();

	// TRACE("MergeCell(%lu, %lu)\n", nRow, nCol);

	if (!(pParam->m_wMergeCellsMode&gxnMergeVertOnly))
	{
		// check left column
		if (nCol > 0 && nCol <= nColCount)
		{
			pGrid->m_rgMerged.m_bValid = FALSE;
			ROWCOL nCol1 = nCol-1;

			if ((pParam->m_wMergeCellsMode&gxnMergeOverHidden) > 0)
			{
				while (pGrid->IsColHidden(nCol1) && nCol1 > 0)
					nCol1--;
			}

			b1 = MCellImplHorz(pGrid, nRow, nCol1, nCol, prgBoundary, bLookupStyle);

			if (b1 && pGrid->m_rgMerged.IsValid())
			{
				ROWCOL nc = pGrid->m_rgMerged.left;

				while (nc > 0
					&& MCellImplHorz(pGrid, nRow, nc-1, nc, prgBoundary, bLookupStyle))
					nc--;
			}
		}

		// check right column
		if (nCol >= 0 && nCol < nColCount)
		{
			pGrid->m_rgMerged.m_bValid = FALSE;
			ROWCOL nCol2 = nCol+1;

			if ((pParam->m_wMergeCellsMode&gxnMergeOverHidden) > 0)
			{
				while (pGrid->IsColHidden(nCol2) && nCol2 < nColCount)
					nCol2++;
			}

			b2 = MCellImplHorz(pGrid, nRow, nCol, nCol2, prgBoundary, bLookupStyle);

			if (b2 && pGrid->m_rgMerged.IsValid())
			{
				ROWCOL nc = pGrid->m_rgMerged.right;

				while (nc < nColCount
					&& MCellImplHorz(pGrid, nRow, nc, nc+1, prgBoundary, bLookupStyle))
					nc++;
			}
		}
	}


	if (!(pParam->m_wMergeCellsMode&gxnMergeHorzOnly))
	{
		// check upper row
		if (nRow > 0 && nRow <= nRowCount)
		{
			pGrid->m_rgMerged.m_bValid = FALSE;
			ROWCOL nRow1 = nRow-1;

			if ((pParam->m_wMergeCellsMode&gxnMergeOverHidden) > 0)
			{
				while (pGrid->IsRowHidden(nRow1) && nRow1 > 0)
					nRow1--;
			}

			b3 = MCellImplVert(pGrid, nCol, nRow1, nRow, prgBoundary, bLookupStyle);

			if (pGrid->m_rgMerged.IsValid())
			{
				ROWCOL nr = pGrid->m_rgMerged.top;

				while (nr > 0
					&& MCellImplVert(pGrid, nCol, nr-1, nr, prgBoundary, bLookupStyle))
					nr--;
			}
		}

		// check lower row
		if (nRow >= 0 && nRow < nRowCount)
		{
			pGrid->m_rgMerged.m_bValid = FALSE;

			ROWCOL nRow2 = nRow+1;

			if ((pParam->m_wMergeCellsMode&gxnMergeOverHidden) > 0)
			{
				while (pGrid->IsRowHidden(nRow2) && nRow2 < nRowCount)
					nRow2++;
			}

			b2 = MCellImplVert(pGrid, nCol, nRow, nRow2, prgBoundary, bLookupStyle);

			if (b4 && pGrid->m_rgMerged.IsValid())
			{
				ROWCOL nr = pGrid->m_rgMerged.top;

				while (nr < nRowCount
					&& MCellImplVert(pGrid, nCol, nr, nr+1, prgBoundary, bLookupStyle))
					nr++;
			}
		}
	}

	return b1 || b2 || b3 || b4;
}


// MCellImpl
//
// Implementation for MergeCell

BOOL CGXGridMergeCellsImp::MCellImplHorz(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol1, ROWCOL nCol2, CGXRange* prgBoundary, BOOL bLookupStyle)
{
	CGXGridParam* pParam = pGrid->GetParam();

	// TRACE("MCellImplHorz(%lu, %lu, %lu)\n", nRow, nCol1, nCol2);

	// Current state
	CGXRange rgMerged1(nRow, nCol1);
	BOOL bIsMerged1 = pGrid->GetMergedCellsRowCol(nRow, nCol1, rgMerged1, mtHorz) != NULL;

	CGXRange rgMerged2(nRow, nCol2);
	BOOL bIsMerged2 = pGrid->GetMergedCellsRowCol(nRow, nCol2, rgMerged2, mtHorz) != NULL;

	BOOL bMergeDone = FALSE;

	// Get Style and Control
	int colindex1 = pGrid->m_MergeCellData.GetIndex(nCol1);
	CGXStyle* pStyle1 = NULL;
	if (bLookupStyle)
		pStyle1 = (CGXStyle*) &pGrid->LookupStyleRowCol(nRow, nCol1);
	else
	{
		if (colindex1 < pGrid->m_MergeCellData.apStylesArray.GetSize())
			pStyle1 = (CGXStyle*) pGrid->m_MergeCellData.apStylesArray.GetAt(colindex1);

		if (pStyle1 == NULL)
		{
			pStyle1 = pGrid->CreateStyle();
			pGrid->ComposeStyleRowCol(nRow, nCol1, pStyle1);
			pGrid->m_MergeCellData.apStylesArray.SetAtGrow(colindex1, pStyle1);
		}
	}

	CGXControl* pControl1 = pGrid->GetRegisteredControl(pStyle1->GetControl());

	BOOL bCanMerge1 = pGrid->CanMergeCell(pControl1, nRow, nCol1, *pStyle1, mtHorz);

	// Get Style and Control
	int colindex2 = pGrid->m_MergeCellData.GetIndex(nCol2);
	CGXStyle* pStyle2 = NULL;
	if (bLookupStyle)
		pStyle2 = (CGXStyle*) &pGrid->LookupStyleRowCol(nRow, nCol2);
	else
	{
		if (colindex2 < pGrid->m_MergeCellData.apStylesArray.GetSize())
			pStyle2 = (CGXStyle*) pGrid->m_MergeCellData.apStylesArray.GetAt(colindex2);

		if (pStyle2 == NULL)
		{
			pStyle2 = pGrid->CreateStyle();
			pGrid->ComposeStyleRowCol(nRow, nCol2, pStyle2);
			pGrid->m_MergeCellData.apStylesArray.SetAtGrow(colindex2, pStyle2);
		}
	}

	CGXControl* pControl2 = pGrid->GetRegisteredControl(pStyle2->GetControl());

	if ((pParam->m_wMergeCellsMode&gxnMergeOverHidden) > 0
		&& (pGrid->IsRowHidden(nRow) || pGrid->IsColHidden(nCol2)))
		return TRUE;

	BOOL bCanMerge2 = pGrid->CanMergeCell(pControl2, nRow, nCol2, *pStyle2, mtHorz);

	BOOL bCanMerge = 
		bCanMerge1	
		&& bCanMerge2
		&& pGrid->CanMergeCells(*pStyle1, *pStyle2);

	if (bCanMerge)
	{
		if (rgMerged2.right != rgMerged1.right)
		{
			if (bIsMerged2)
				// Remove covering
			bMergeDone =
				pGrid->SetMergedCellsRowCol(mtHorz,
					rgMerged2.top, rgMerged2.left, rgMerged2.top, rgMerged2.left);

			bMergeDone |=
				// Apply new covering
				pGrid->SetMergedCellsRowCol(mtHorz,
					rgMerged1.top, rgMerged1.left, rgMerged1.bottom, rgMerged2.right);

		}
	}
	else
	{
		if (bIsMerged1 && rgMerged1.right >= nCol2)
		{
			bMergeDone =
				pGrid->SetMergedCellsRowCol(mtHorz,
					rgMerged1.top, rgMerged1.left, rgMerged1.top, rgMerged1.left);

			if (nCol1 > rgMerged1.left)
				bMergeDone |= pGrid->SetMergedCellsRowCol(mtHorz,
					rgMerged1.top, rgMerged1.left, rgMerged1.top, nCol1);
		}

		if (bIsMerged2 && rgMerged2.left <= nCol1)
		{
			if (rgMerged1.right != rgMerged2.right)
				bMergeDone |= pGrid->SetMergedCellsRowCol(mtHorz,
					rgMerged2.top, rgMerged2.left, rgMerged2.top, rgMerged2.left);

			if (nCol2 < rgMerged2.right)
				bMergeDone |= pGrid->SetMergedCellsRowCol(mtHorz,
					rgMerged2.top, nCol2, rgMerged2.top, rgMerged2.right);
		}

	}

	// bMergeDone |= rgMerged.right > nCol || nMerge > 0;

	if (bMergeDone && prgBoundary)
	{
		if (!prgBoundary->IsValid())
			prgBoundary->SetCells(nRow, nCol2);

		prgBoundary->right = max(prgBoundary->right, rgMerged2.right);
		prgBoundary->left = min(prgBoundary->left, rgMerged1.left);
		prgBoundary->top = min(prgBoundary->top, rgMerged1.top);
		prgBoundary->bottom = max(prgBoundary->bottom, rgMerged2.bottom);
	}

	return bMergeDone;
}

BOOL CGXGridMergeCellsImp::MCellImplVert(CGXGridCore* pGrid, ROWCOL nCol, ROWCOL nRow1, ROWCOL nRow2, CGXRange* prgBoundary, BOOL bLookupStyle)
{
	//CGXGridParam* pParam = pGrid->GetParam();// C4189 Unused.

	// TRACE("MCellImplVert(%lu, %lu, %lu)\n", nCol, nRow1, nRow2);
	bLookupStyle = TRUE;

	// Current state
	CGXRange rgMerged1(nRow1, nCol);
	BOOL bIsMerged1 = pGrid->GetMergedCellsRowCol(nRow1, nCol, rgMerged1, mtVert) != NULL;

	CGXRange rgMerged2(nRow2, nCol);
	BOOL bIsMerged2 = pGrid->GetMergedCellsRowCol(nRow2, nCol, rgMerged2, mtVert) != NULL;

	BOOL bMergeDone = FALSE;

	// Get Style and Control
	const CGXStyle* pStyle1 = &pGrid->LookupStyleRowCol(nRow1, nCol);
	CGXControl* pControl1 = pGrid->GetRegisteredControl(pStyle1->GetControl());

	BOOL bCanMerge1 = pGrid->CanMergeCell(pControl1, nRow1, nCol, *pStyle1, mtVert);

	// Get Style and Control
	const CGXStyle* pStyle2 = &pGrid->LookupStyleRowCol(nRow2, nCol);
	CGXControl* pControl2 = pGrid->GetRegisteredControl(pStyle2->GetControl());

	BOOL bCanMerge2 = pGrid->CanMergeCell(pControl2, nRow2, nCol, *pStyle2, mtVert);

	BOOL bCanMerge = 
		bCanMerge1	
		&& bCanMerge2
		&& pGrid->CanMergeCells(*pStyle1, *pStyle2);

	if (bCanMerge)
	{
		if (rgMerged2.bottom != rgMerged1.bottom)
		{
			if (bIsMerged2)
				// Remove covering
			bMergeDone =
				pGrid->SetMergedCellsRowCol(mtVert,
					rgMerged2.top, rgMerged2.left, rgMerged2.top, rgMerged2.left);

			bMergeDone |=
				// Apply new covering
				pGrid->SetMergedCellsRowCol(mtVert,
					rgMerged1.top, rgMerged1.left, rgMerged2.bottom, rgMerged1.right);

		}
	}
	else
	{
		if (bIsMerged1 && rgMerged1.bottom >= nRow2)
		{
			bMergeDone =
				pGrid->SetMergedCellsRowCol(mtVert,
					rgMerged1.top, rgMerged1.left, rgMerged1.top, rgMerged1.left);

			if (nRow1 > rgMerged1.top)
				bMergeDone |= pGrid->SetMergedCellsRowCol(mtVert,
					rgMerged1.top, rgMerged1.left, nRow1, rgMerged1.left);
		}

		if (bIsMerged2 && rgMerged2.top <= nRow1)
		{
			if (rgMerged1.bottom != rgMerged2.bottom)
				bMergeDone |= pGrid->SetMergedCellsRowCol(mtVert,
					rgMerged2.top, rgMerged2.left, rgMerged2.top, rgMerged2.left);

			if (nRow2 < rgMerged2.bottom)
				bMergeDone |= pGrid->SetMergedCellsRowCol(mtVert,
					nRow2, rgMerged2.left, rgMerged2.bottom, rgMerged2.left);
		}

	}

	// bMergeDone |= rgMerged.right > nCol || nMerge > 0;

	if (bMergeDone && prgBoundary)
	{
		if (!prgBoundary->IsValid())
			prgBoundary->SetCells(nRow2, nCol);

		prgBoundary->right = max(prgBoundary->right, rgMerged2.right);
		prgBoundary->left = min(prgBoundary->left, rgMerged1.left);
		prgBoundary->top = min(prgBoundary->top, rgMerged1.top);
		prgBoundary->bottom = max(prgBoundary->bottom, rgMerged2.bottom);
	}

	return bMergeDone;
}

void CGXGridCore::MergeCellsData::InitColOffset(ROWCOL nCol)
{
	if (apStylesArray.GetSize() > 0)
		return;

	nColOffset = max(256, nCol)-256;
}

int CGXGridCore::MergeCellsData::GetIndex(ROWCOL nCol)
{
	if (nCol > nColOffset)
		return (int) (nCol-nColOffset);

	return 0;
}

void CGXGridCore::MergeCellsData::Reset(CGXGridCore* pGrid)
{
	for (int i = 0; i < apStylesArray.GetSize(); i++)
	{
		if (apStylesArray[i])
		{
			pGrid->RecycleStyle((CGXStyle*) apStylesArray[i]);
			apStylesArray[i] = NULL;
		}
	}

	nLastRow = 0;
}


// SetMergedCellsRowCol
//
// Changes the float cell state for the cell and updates the display
//
// Works very similar to SetCoveredCellsRowCol.

BOOL CGXGridMergeCellsImp::SetMergedCellsRowCol(CGXGridCore* pGrid, int mtType, ROWCOL nRow, ROWCOL nCol, ROWCOL nToRow, ROWCOL nToCol, UINT flags /*= GX_UPDATENOW*/)
{
	CGXGridParam* pParam = pGrid->GetParam();

	ASSERT((pParam->m_wMergeCellsMode&0x03) != gxnMergeDisable);
	ASSERT(nToRow >= nRow && nToCol >= nCol);

	ROWCOL nOldToRow = nRow,
		   nOldToCol = nCol;

	CGXRange rgMerged;

	if (pGrid->GetMergedCellsRowCol(nRow, nCol, rgMerged, mtType))
	{
		nOldToRow = rgMerged.bottom;
		nOldToCol = rgMerged.right;
	}

	BOOL bSet = (nToRow != nRow || nToCol != nCol);

	// Command
	if (StoreMergedCellsRowCol(pGrid, mtType, nRow, nCol, nToRow, nToCol, bSet))
	{
		pGrid->m_rgMerged.SetCells(nRow, nCol, nToRow, nToCol);
		CGXRange rg(nRow, nCol, max(nOldToRow, nToRow), max(nOldToCol, nToCol));

		CGXRange rgBoundary;

		pGrid->DelayFloatCells(rg);

		if (pGrid->m_nNestedDraw == 0)  // Don't update when called from OnDrawTopLeftBottomRight
			 pGrid->UpdateMergedCellsRowCol(rg.top, rg.left, rg.bottom, rg.right, flags, TRUE);

		return TRUE;
	}

	return FALSE;
}

// GetMergedCellsRowCol
//
// Returns a pointer to range with the floated cells.
// If it is NULL, no floated cell range could be found.

CGXRange* CGXGridMergeCellsImp::GetMergedCellsRowCol(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, CGXRange& range, int mtType)
{
	CGXGridParam* pParam = pGrid->GetParam();

	if ((pParam->m_wMergeCellsMode&0x03) == gxnMergeDisable)
		return NULL;

	BOOL b1 = FALSE;
	BOOL b2 = FALSE;

	range.SetCells(nRow, nCol);

	if (mtType == -1 || mtType == mtHorz)
		b1 = pParam->m_pHorzMergeCells->GetSpanCellsRowCol(nRow, nCol, range);

	if (mtType == -1 || mtType == mtVert)
		b2 = pParam->m_pVertMergeCells->GetSpanCellsRowCol(nRow, nCol, range);

	if (b1 || b2)
		return &range;

	return NULL;
}

// MergeMergedCells
//
// Expands the given area with any float cell ranges which intersect the area

void CGXGridMergeCellsImp::MergeMergedCells(CGXGridCore* pGrid, CGXRange& area)
{
	CGXGridParam* pParam = pGrid->GetParam();

	if ((pParam->m_wMergeCellsMode&0x03) == gxnMergeDisable)
		return;

	CGXRange rgMerged;
	CGXRange t;

	for (ROWCOL nRow = area.top; nRow <= area.bottom; nRow++)
	{
		for (ROWCOL nCol = area.left; nCol <= area.right; nCol++)
		{
			if (pGrid->GetMergedCellsRowCol(nRow, nCol, rgMerged, mtHorz))
			{
				nCol = rgMerged.right+1;

				area.UnionRange(rgMerged, area);
			}
		}
	}

	for (ROWCOL nCol = area.left; nCol <= area.right; nCol++)
	{
		for (ROWCOL nRow = area.top; nRow <= area.bottom; nRow++)
		{
			if (pGrid->GetMergedCellsRowCol(nRow, nCol, rgMerged, mtVert))
			{
				nRow = rgMerged.bottom+1;

				area.UnionRange(rgMerged, area);
			}
		}
	}
}

// StoreMergedCellsRowCol
//
// Returns TRUE if the range could be stored; It is FALSE if the range could not be
// stored or if  the range would overlap another range.
//

BOOL CGXGridMergeCellsImp::StoreMergedCellsRowCol(CGXGridCore* pGrid, int mtType, ROWCOL nRow, ROWCOL nCol, ROWCOL nToRow, ROWCOL nToCol, BOOL bSet)
{
	CGXGridParam* pParam = pGrid->GetParam();

	ASSERT((pParam->m_wMergeCellsMode&0x03) != gxnMergeDisable);

	// check if grid is read-only
	// if (GetParam()->m_bLockReadOnly && (IsReadOnly() || StandardStyle().GetReadOnly()))
	//	return FALSE;

	if ((pParam->m_wMergeCellsMode&0x03) == gxnMergeDisable)
		return FALSE;

	if (mtType == mtHorz)
		return pParam->m_pHorzMergeCells->StoreSpanCellsRowCol(nRow, nCol, nToRow, nToCol, bSet);
	else
		return pParam->m_pVertMergeCells->StoreSpanCellsRowCol(nRow, nCol, nToRow, nToCol, bSet);

}

// UpdateMergedCellsRowCol
//
// Updates the display after a floating cell has been reset
// or if has been changed to flood other cells.

void CGXGridMergeCellsImp::UpdateMergedCellsRowCol(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, ROWCOL nOldToRow, ROWCOL nOldToCol, UINT flags, BOOL bCreateHint)
{
	CGXGridParam* pParam = pGrid->GetParam();

	ASSERT((pParam->m_wMergeCellsMode&0x03) != gxnMergeDisable);

	if (!pGrid->IsLockUpdate())
	{
		ROWCOL nToRow = nRow,
			   nToCol = nCol;

		CGXRange rgMerged;
		if (pGrid->GetMergedCellsRowCol(nRow, nCol, rgMerged))
		{
			nToRow = rgMerged.bottom;
			nToCol = rgMerged.right;
		}

		pGrid->RedrawRowCol(nRow, nCol, max(nToRow, nOldToRow), max(nToCol, nOldToCol), flags, FALSE);
	}

	if (pGrid->m_pUpdateHintImp && bCreateHint && pGrid->m_bHintsEnabled)
		pGrid->m_pUpdateHintImp->HintUpdateMergedCellsRowCol(pGrid, nRow, nCol, nOldToRow, nOldToCol, flags);
}
