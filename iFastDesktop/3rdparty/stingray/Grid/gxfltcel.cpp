///////////////////////////////////////////////////////////////////////////////
// gxfltcel.cpp: Floating cells implementation
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

#include "grid\gxfltcel.h"

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

void CGXGridCore::ImplementFloatCells()
{
	if (m_pFloatCellsImp == NULL)
	{
		// QA: 31521 Removal from AutoDeletePtr
		//AutoDeletePtr(m_pFloatCellsImp = new CGXGridFloatCellsImp);
		m_pFloatCellsImp = new CGXGridFloatCellsImp;
	}

	CGXSpanCellPool::ImplementSpanCellPool();
	CGXDelayedRangePool::ImplementDelayedRangePool();
	ImplementDrawSpannedCells();
	ImplementCalcSize();
}

/////////////////////////////////////////////////////////////////////////////
// Floating Cells

void CGXGridFloatCellsImp::SetFloatCellsMode(CGXGridCore* pGrid, WORD nMode, BOOL bRedraw /*=TRUE*/)
{
	CGXGridParam* pParam = pGrid->GetParam();

	if (nMode != pParam->m_wFloatCellsMode)
	{
		pParam->m_wFloatCellsMode = nMode;

		// Clean up float cells state
		delete pParam->m_pDispFloatCells;
		delete pParam->m_pDelayedDispFloatCells;
		pParam->m_pDelayedDispFloatCells = NULL;
		pParam->m_pDispFloatCells = NULL;

		switch (nMode)
		{
		case gxnFloatDisable:
			break;

		case gxnFloatEvalOnDisplay:
			// Reinit float cells state
			pParam->m_pDispFloatCells = new CGXSpanCellPool;
			break;

		case gxnFloatDelayEval:
			// Reinit float cells state
			pParam->m_pDelayedDispFloatCells = new CGXDelayedRangePool;
			pParam->m_pDispFloatCells = new CGXSpanCellPool;

			// Force all cells to be recalculated
			pGrid->DelayFloatCells(CGXRange().SetTable());
			break;
		}
	}

	if (bRedraw)
		pGrid->Redraw();
}

// DelayFloatCells
//
// Delays the evaluation of the given range of cells

void CGXGridFloatCellsImp::DelayFloatCells(CGXGridCore* pGrid, const CGXRange& range, ROWCOL nMaxCols)
{
	CGXGridParam* pParam = pGrid->GetParam();

	if (pParam->m_wFloatCellsMode != gxnFloatDelayEval)
		return;

	// Expand range to current dimension
	CGXRange rg = range;
	rg.ExpandRange(pGrid->GetHeaderRows()+1, pGrid->GetHeaderCols()+1, pGrid->GetRowCount(), pGrid->GetColCount());

	rg.top = max(pGrid->GetHeaderRows()+1, rg.top);
	rg.left = max(pGrid->GetHeaderCols()+1, rg.left);

	if (rg.right >= rg.left && rg.bottom >= rg.top)
	{
		// Display
		if (!pGrid->IsPrinting())
		{
			pParam->m_pDelayedDispFloatCells->DelayRange(rg);

			if (nMaxCols != GX_INVALID)
				pParam->m_pDelayedDispFloatCells->SetColCount(nMaxCols);
		}

		// Printing
		if (pParam->m_pDelayedPrintFloatCells != NULL)
		{
			pParam->m_pDelayedPrintFloatCells->DelayRange(rg);

			if (nMaxCols != GX_INVALID)
				pParam->m_pDelayedPrintFloatCells->SetColCount(nMaxCols);
		}
	}

}

// EvalFloatCells
//
// Evaluates those cells from the given range if they want to float
// other cells

BOOL CGXGridFloatCellsImp::EvalFloatCells(CGXGridCore* pGrid, const CGXRange& range,
	BOOL bUpdate, //= TRUE
	CGXRange* prgBoundary, // = NULL
	BOOL bLookupStyle) //
{
	// Is evaluation of floating cells temporary or completely turned off?
	if (pGrid->m_bLockEvalFloatCells)
		return FALSE;

	CGXGridParam* pParam = pGrid->GetParam();

	// Different modes
	switch (pParam->m_wFloatCellsMode)
	{
	case gxnFloatDisable:
		return FALSE;

	case gxnFloatDelayEval:
		return EvalDelayedFloatCells(pGrid, range, bUpdate, prgBoundary, bLookupStyle);

	case gxnFloatEvalOnDisplay:
		return EvalAllFloatCells(pGrid, range, bUpdate, prgBoundary, bLookupStyle);

	default:
		TRACE(_T("Warning: pParam->m_wFloatCellsMode invalid\n"));
		return FALSE;
	}
}

// EvalAllFloatCells
//
// Evaluates all cells from the given range if they want to float
// other cells.

BOOL CGXGridFloatCellsImp::EvalAllFloatCells(CGXGridCore* pGrid, CGXRange range, BOOL bUpdate, CGXRange* prgBoundary, BOOL bLookupStyle)
{
	BOOL bLock = FALSE;
	if (!bUpdate)
		bLock = pGrid->LockUpdate(TRUE);

	range.ExpandRange(pGrid->GetHeaderRows()+1,
		pGrid->GetHeaderCols()+1,
		pGrid->GetRowCount(),
		pGrid->GetColCount());

	// Calculate size

	BOOL bFloatDone = FALSE;

	pGrid->m_FloatCellData.InitColOffset(range.left);

	for (ROWCOL nRow = range.top; nRow <= range.bottom; nRow++)
	{
		if (!pGrid->IsRowHidden(nRow))
		{
			for (ROWCOL nCol = range.left; nCol <= range.right; nCol++)
			{
				if (!pGrid->IsColHidden(nCol))
					bFloatDone |= FloatCell(pGrid, nRow, nCol, prgBoundary, bLookupStyle);
			}
		}

		pGrid->m_FloatCellData.Reset(pGrid);
	}

	if (!bUpdate)
		pGrid->LockUpdate(bLock);
    
    // Reset internally cached dc, if any
	pGrid->ReleaseGridDC();
	
	return bFloatDone;
}

// EvalDelayedFloatCells
//
// Evaluates those cells from the given range which
// were previously marked as delayed with DelayFloatCells

BOOL CGXGridFloatCellsImp::EvalDelayedFloatCells(CGXGridCore* pGrid, CGXRange range,
	BOOL bUpdate, //= TRUE
	CGXRange* prgBoundary, // = NULL
	BOOL bLookupStyle) //
{
	CGXGridParam* pParam = pGrid->GetParam();

	range.ExpandRange(pGrid->GetHeaderRows()+1, pGrid->GetHeaderCols()+1, pGrid->GetRowCount(), pGrid->GetColCount());
	range.top = max(range.top, pGrid->GetHeaderRows()+1);
	range.left = max(range.left, pGrid->GetHeaderCols()+1);

	BOOL bFloatDone = FALSE;

	CDWordArray dwColStart;
	CDWordArray dwColEnd;

	CGXDelayedRangePool* pPool;
	if (pGrid->IsPrinting())
		pPool = pParam->m_pDelayedPrintFloatCells;
	else
		pPool = pParam->m_pDelayedDispFloatCells;

	if (pPool->EvalRows(range, dwColStart, dwColEnd))
	{
		BOOL bLock = FALSE;
		if (!bUpdate)
			bLock = pGrid->LockUpdate(TRUE);

		pGrid->m_FloatCellData.InitColOffset(range.left);

		for (int nIndex = 0; nIndex < dwColStart.GetSize(); nIndex++)
		{
			ROWCOL nRow = (ROWCOL) nIndex + range.top;

			if (!pGrid->IsRowHidden(nRow) && dwColEnd[nIndex] > 0)
			{
				// TRACE("Row = %d: %d, %d\n", nRow, dwColStart[nIndex], dwColEnd[nIndex]);

				for (ROWCOL nCol = dwColStart[nIndex]; nCol <= dwColEnd[nIndex]; nCol++)
				{
					if (!pGrid->IsColHidden(nCol))
						bFloatDone |= FloatCell(pGrid, nRow, nCol, prgBoundary, bLookupStyle);
				}
			}

			pGrid->m_FloatCellData.Reset(pGrid);
		}

		if (!bUpdate)
			pGrid->LockUpdate(bLock);
	}

    // Reset internally cached dc, if any
	pGrid->ReleaseGridDC();
	
	return bFloatDone;
}

// CanFloatCell
//
// Called to determins if the specified cell can float other cells or
// if it can be flooded.

BOOL CGXGridFloatCellsImp::CanFloatCell(CGXGridCore* pGrid, CGXControl* pControl, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, BOOL bFloatOrFlood)
{
	nRow, nCol;

	CGXGridParam* pParam = pGrid->GetParam();

	if (pParam->m_wFloatCellsMode == gxnFloatDisable)
		return FALSE;

	CGXRange rgCovered;
	if (pGrid->GetCoveredCellsRowCol(nRow, nCol, rgCovered))
		return FALSE;

	CGXRange rgMerged;
	if (pGrid->GetMergedCellsRowCol(nRow, nCol, rgMerged))
		return FALSE;

	// static cells can float over other cells if value is not empty
	if (bFloatOrFlood)
		return style.GetIncludeFloatCell() && style.GetFloatCell() && pControl->CanFloatCell(nRow, nCol, style, bFloatOrFlood);
	else
	{
        // QA: 31719 - Refix of this QA to the correct solution below. 
		// Don't float over the "Freeze line" or active cells
		return (nCol != pGrid->GetFrozenCols() + 1) && style.GetIncludeFloodCell() && style.GetFloodCell() && pControl->CanFloatCell(nRow, nCol, style, bFloatOrFlood);
	}
}

// FloatCell
//
// Evaluates the given cell.
//
// prgBoundary will be extended when the cell has become a floating
// cell or if it was a floating cell.

BOOL CGXGridFloatCellsImp::FloatCell(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, CGXRange* prgBoundary, BOOL bLookupStyle)
{
	CGXGridParam* pParam = pGrid->GetParam();

	if (pParam->m_wFloatCellsMode == gxnFloatDisable)
		return FALSE;

	if (nCol <= pGrid->GetHeaderCols() || nRow <= pGrid->GetHeaderRows())
		return FALSE;

	// Check if there is a cell to the left which could float over this cell
	CGXStyle* pStyle = NULL;
//  int nDirty = -1;

	int colindex = pGrid->m_FloatCellData.GetIndex(nCol);

	if (colindex < pGrid->m_FloatCellData.apStylesArray.GetSize())
		pStyle = (CGXStyle*) pGrid->m_FloatCellData.apStylesArray.GetAt(colindex);

	if (pStyle == NULL)
	{
		if (bLookupStyle && !pGrid->IsCurrentCell(nRow, nCol))
			pStyle = (CGXStyle*) &pGrid->LookupStyleRowCol(nRow, nCol); // .Clone();
		else
		{
			pStyle = pGrid->CreateStyle();
			pGrid->ComposeStyleRowCol(nRow, nCol, pStyle);
			pGrid->m_FloatCellData.apStylesArray.SetAtGrow(colindex, pStyle);
		}
	}

	CGXControl* pControl = pGrid->GetRegisteredControl(pStyle->GetControl());

	if (pGrid->IsCurrentCell(nRow, nCol))
		pControl->LoadStyle(nRow, nCol, pStyle);

	BOOL bCanFloat = pGrid->CanFloatCell(pControl, nRow, nCol, *pStyle, TRUE);
	// TRACE("bCanFLoat = %d for nRow = %d, nCol = %d\n", bCanFloat, nRow, nCol);

	// If this value is empty, first unfloat cell,
	// then float cell to the left

	// If value is not empty, make sure this cell is not
	// floated by another cell before checking
	// if this cell should float cells to the right

	CGXRange rgFloated;
	ROWCOL nCol1 = nCol-1;
	if (pGrid->GetFloatedCellsRowCol(nRow, nCol-1, rgFloated))
		nCol1 = rgFloated.left;

	BOOL b1 = FALSE;
	BOOL b2 = FALSE;
	if (bCanFloat)
	{
		b1 = FCellImpl(pGrid, nRow, nCol1, prgBoundary, bLookupStyle);
		b2 = FCellImpl(pGrid, nRow, nCol, prgBoundary, bLookupStyle);
	}
	else
	{
		b2 = FCellImpl(pGrid, nRow, nCol, prgBoundary, bLookupStyle);
		b1 = FCellImpl(pGrid, nRow, nCol1, prgBoundary, bLookupStyle);
	}

//  if (nDirty == -1 && pValueStyle)
//      delete pValueStyle;
//      pGrid->m_FloatCellData.apStylesArray.SetAtGrow(nDirty, NULL);

	return b1 || b2;
}

// FCellImpl
//
// Implementation for FloatCell

BOOL CGXGridFloatCellsImp::FCellImpl(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, CGXRange* prgBoundary, BOOL bLookupStyle)
{
	BOOL bFloatDone = FALSE;

	CGXRange rgFloated(nRow, nCol);
	pGrid->GetFloatedCellsRowCol(nRow, nCol, rgFloated);
	nCol = rgFloated.left;

	// Get Style and Control
	int colindex = pGrid->m_FloatCellData.GetIndex(nCol);

	CGXStyle* pStyle = NULL;

	if (colindex < pGrid->m_FloatCellData.apStylesArray.GetSize())
		pStyle = (CGXStyle*) pGrid->m_FloatCellData.apStylesArray.GetAt(colindex);

	if (pStyle == NULL)
	{
		if (bLookupStyle && !pGrid->IsCurrentCell(nRow, nCol))
			pStyle = (CGXStyle*) &pGrid->LookupStyleRowCol(nRow, nCol); //.Clone();
		else
		{
			pStyle = pGrid->CreateStyle();
			pGrid->ComposeStyleRowCol(nRow, nCol, pStyle);
			pGrid->m_FloatCellData.apStylesArray.SetAtGrow(colindex, pStyle);
		}
	}

	CGXControl* pControl = pGrid->GetRegisteredControl(pStyle->GetControl());

	if (pGrid->IsCurrentCell(nRow, nCol))
		pControl->LoadStyle(nRow, nCol, pStyle);

	// Is this cell floatable?
	ROWCOL nFloat = 0;
	if (pGrid->CanFloatCell(pControl, nRow, nCol, *pStyle, TRUE))
	{
		// Calculate horizontal size of cell

		// size
		if (nRow != pGrid->m_FloatCellData.nLastRow)
		{
			for (int i = 0; i < pGrid->m_FloatCellData.awSizeArray.GetSize(); i++)
				pGrid->m_FloatCellData.awSizeArray[i] = 0;
		}

		CSize size(0,0);
		if (colindex < pGrid->m_FloatCellData.awSizeArray.GetSize())
			size.cx = pGrid->m_FloatCellData.awSizeArray.GetAt(colindex);

		// if (size.cx == 0)
		{
			size = pControl->CalcSize(pGrid->GetGridDC(), nRow, nCol, *pStyle, &pGrid->StandardStyle(), FALSE);
			pGrid->m_FloatCellData.awSizeArray.SetAtGrow(colindex, (WORD) size.cx);
		}

		// Check number of cells to be floated
		ROWCOL nColCount = pGrid->GetColCount();
		BOOL bCanFloat;
		while (nCol+nFloat < nColCount && size.cx > pGrid->GetColWidth(nCol+nFloat))
		{
			// Break if next cell cannot be flooded (e.g. if value is not empty)
			int colindex2 = pGrid->m_FloatCellData.GetIndex(nCol+nFloat+1);

			CGXStyle* pStyle2 = NULL;

			if (colindex2 < pGrid->m_FloatCellData.apStylesArray.GetSize())
				pStyle2 = (CGXStyle*) pGrid->m_FloatCellData.apStylesArray.GetAt(colindex2);

			if (pStyle2 == NULL)
			{
				if (bLookupStyle && !pGrid->IsCurrentCell(nRow, nCol+nFloat+1))
					pStyle2 = (CGXStyle*) &pGrid->LookupStyleRowCol(nRow, nCol+nFloat+1); // .Clone();
				else
				{
					pStyle2 = pGrid->CreateStyle();
					pGrid->ComposeStyleRowCol(nRow, nCol+nFloat+1, pStyle2);
					pGrid->m_FloatCellData.apStylesArray.SetAtGrow(colindex2, pStyle2);
				}
			}

			CGXControl* pControl2 = pGrid->GetRegisteredControl(pStyle2->GetControl());
			if (pGrid->IsCurrentCell(nRow, nCol+nFloat+1))
				pControl2->LoadStyle(nRow, nCol+nFloat+1, pStyle2);

			bCanFloat = pGrid->CanFloatCell(pControl2, nRow, nCol+nFloat+1, *pStyle2, FALSE);

			if (!bCanFloat)
				break;

			// decrement size
			size.cx -= pGrid->GetColWidth(nCol+nFloat);
			nFloat++;
		}
	}

	// Float cells if status has changed
	if (rgFloated.right != nCol+nFloat)
		bFloatDone = pGrid->SetFloatedCellsRowCol(nRow, nCol, nRow, nCol+nFloat, GX_INVALIDATE);

	// bFloatDone |= rgFloated.right > nCol || nFloat > 0;

	if (bFloatDone && prgBoundary)
	{
		if (!prgBoundary->IsValid())
			prgBoundary->SetCells(nRow, nCol);

		prgBoundary->right = max(prgBoundary->right, rgFloated.right);
		prgBoundary->right = max(prgBoundary->right, nCol+nFloat);
		prgBoundary->left = min(prgBoundary->left, nCol);
		prgBoundary->top = min(prgBoundary->top, nRow);
		prgBoundary->bottom = max(prgBoundary->bottom, nRow);
	}

	return bFloatDone;
}

void CGXGridCore::FloatCellsData::InitColOffset(ROWCOL nCol)
{
	if (apStylesArray.GetSize() > 0)
		return;

	nColOffset = max(256, nCol)-256;
}

int CGXGridCore::FloatCellsData::GetIndex(ROWCOL nCol)
{
	if (nCol > nColOffset)
		return (int) (nCol-nColOffset);

	return 0;
}

void CGXGridCore::FloatCellsData::Reset(CGXGridCore* pGrid)
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


// SetFloatedCellsRowCol
//
// Changes the float cell state for the cell and updates the display
//
// Works very similar to SetCoveredCellsRowCol.

BOOL CGXGridFloatCellsImp::SetFloatedCellsRowCol(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, ROWCOL nToRow, ROWCOL nToCol, UINT flags /*= GX_UPDATENOW*/)
{
	CGXGridParam* pParam = pGrid->GetParam();

	ASSERT(pParam->m_wFloatCellsMode != gxnFloatDisable);
	ASSERT(nToRow >= nRow && nToCol >= nCol);

	ROWCOL nOldToRow = nRow,
		   nOldToCol = nCol;

	CGXRange rgFloated;
	if (pGrid->GetFloatedCellsRowCol(nRow, nCol, rgFloated))
	{
		nOldToRow = rgFloated.bottom;
		nOldToCol = rgFloated.right;
	}

	BOOL bSet = (nToRow != nRow || nToCol != nCol);

	// Command
	if (StoreFloatedCellsRowCol(pGrid, nRow, nCol, nToRow, nToCol, bSet))
	{
		 if (pGrid->m_nNestedDraw == 0)  // Don't update when called from OnDrawTopLeftBottomRight
			 pGrid->UpdateFloatedCellsRowCol(nRow, nCol, nOldToRow, nOldToCol, flags, TRUE);

		return TRUE;
	}

	return FALSE;
}

// GetFloatedCellsRowCol
//
// Returns a pointer to range with the floated cells.
// If it is NULL, no floated cell range could be found.

CGXRange* CGXGridFloatCellsImp::GetFloatedCellsRowCol(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, CGXRange& range)
{
	CGXGridParam* pParam = pGrid->GetParam();

	range.SetCells(nRow, nCol);

	if (pParam->m_wFloatCellsMode != gxnFloatDisable
		&& pGrid->GetFloatCellsPool()->GetSpanCellsRowCol(nRow, nCol, range))
		return &range;

	return NULL;
}

// MergeFloatedCells
//
// Expands the given area with any float cell ranges which intersect the area

void CGXGridFloatCellsImp::MergeFloatedCells(CGXGridCore* pGrid, CGXRange& area)
{
	CGXGridParam* pParam = pGrid->GetParam();

	if (pParam->m_wFloatCellsMode == gxnFloatDisable)
		return;

	CGXRange rgFloated;
	CGXRange t;

	for (ROWCOL nRow = area.top; nRow <= area.bottom; nRow++)
	{
		for (ROWCOL nCol = area.left; nCol <= area.right; nCol++)
		{
			if (pGrid->GetFloatedCellsRowCol(nRow, nCol, rgFloated))
			{
				nCol = rgFloated.right+1;

				area.UnionRange(rgFloated, area);
			}
		}
	}
}

// StoreFloatedCellsRowCol
//
// Returns TRUE if the range could be stored; It is FALSE if the range could not be
// stored or if  the range would overlap another range.
//

BOOL CGXGridFloatCellsImp::StoreFloatedCellsRowCol(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, ROWCOL nToRow, ROWCOL nToCol, BOOL bSet)
{
	CGXGridParam* pParam = pGrid->GetParam();

	// check if grid is read-only
	// if (GetParam()->m_bLockReadOnly && (IsReadOnly() || StandardStyle().GetReadOnly()))
	//	return FALSE;

	if (pParam->m_wFloatCellsMode == gxnFloatDisable)
		return FALSE;

	return pGrid->GetFloatCellsPool()->StoreSpanCellsRowCol(nRow, nCol, nToRow, nToCol, bSet);
}

// UpdateFloatedCellsRowCol
//
// Updates the display after a floating cell has been reset
// or if has been changed to flood other cells.

void CGXGridFloatCellsImp::UpdateFloatedCellsRowCol(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, ROWCOL nOldToRow, ROWCOL nOldToCol, UINT flags, BOOL bCreateHint)
{
	CGXGridParam* pParam = pGrid->GetParam();

	ASSERT(pParam->m_wFloatCellsMode != gxnFloatDisable);

	if (!pGrid->IsLockUpdate())
	{
		ROWCOL nToRow = nRow,
			   nToCol = nCol;

		CGXRange rgFloated;
		if (pGrid->GetFloatedCellsRowCol(nRow, nCol, rgFloated))
		{
			nToRow = rgFloated.bottom;
			nToCol = rgFloated.right;
		}

		pGrid->RedrawRowCol(nRow, nCol, max(nToRow, nOldToRow), max(nToCol, nOldToCol), flags, FALSE);
	}

	// Create Hint
	if (pGrid->m_pUpdateHintImp && bCreateHint && pGrid->m_bHintsEnabled)
		pGrid->m_pUpdateHintImp->HintUpdateFloatedCellsRowCol(pGrid, nRow, nCol, nOldToRow, nOldToCol, flags);
}

BOOL CGXGridFloatCellsImp::CanFloatCell(CGXControl* pControl, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, BOOL bFloatOrFlood)
{
	GX_UNUSED_ALWAYS(pControl);

	nRow, nCol;

	// static cells can float over other cells if value is not empty
	if (bFloatOrFlood)
	{
		// rotated cells don't float
		if (style.GetIncludeFont() 
			&& style.GetFontRef().GetIncludeOrientation() 
			&& style.GetFontRef().GetOrientation() != 0)
				return FALSE;

		return _tcslen(style.GetValueRef()) > 0;
	}
	else
		// static cells can be flooded by other floatable cells if value is empty
		return _tcslen(style.GetValueRef()) == 0;
}


