///////////////////////////////////////////////////////////////////////////////
// gxselgru.cpp : let user select cell ranges with mouse
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

#ifndef _GXRESRC_H_
#include "grid\gxresrc.h"
#endif

#ifndef _GXEXT_H_
#include "grid\gxext.h"
#endif

#ifndef _GXCORE_H_
#include "grid\gxcore.h"
#endif

//#ifndef _GXCTRL_H_
//#include "grid\gxctrl.h"
//#endif

//#ifndef _GXMSG_H_
//#include "grid\gxmsg.h"
//#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXCORSEL")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

enum GXExcelFillQuadrant {
	top,
	left,
	bottom,
	right,
	within
};

class CGXGridExcelLikeFillImp: public CGXAbstractGridExcelLikeFillImp
{
public:
	CGXRange m_startRange;
	CRect m_ExcelLastRect;
	CGXRange m_ExcelLastRange;
	virtual void OnLButtonDown(CGXGridCore* pGrid, CPoint& point, UINT& flags, int& ht, ROWCOL& nRow, ROWCOL& nCol);
	virtual BOOL OnMouseMove(CGXGridCore* pGrid, CPoint& point, UINT& flags, ROWCOL& nRow, ROWCOL& nCol);
	virtual void OnLButtonUp(CGXGridCore* pGrid, CPoint& point, UINT& flags);
	virtual void DrawDragRect(CGXGridCore* pGrid, CGXRange& rect, BOOL bEraseOld, BOOL bDrawNew);
	virtual void FillRect(CGXGridCore* pGrid, CGXRange& nFrom, CGXRange& nTo);
	virtual void ClearCurrentDragRect(CGXGridCore* pGrid);
	virtual void OnAutoFillDone(CGXGridCore* pGrid, CGXRange& rFinal);
};


void CGXGridCore::ImplementExcelLikeFill()
{
	// If not already plugged-in
	if (m_pExcelLikeFillImp == NULL)
		SetExcelLikeFillImp(new CGXGridExcelLikeFillImp);

	ImplementExcelLikeFrame();
}

// Called only when button down on the fill handle.
void CGXGridExcelLikeFillImp::OnLButtonDown(CGXGridCore* pGrid, CPoint& point, UINT& flags, int& ht, ROWCOL& nRow, ROWCOL& nCol)
{
	ASSERT(pGrid->GetParam()->GetExcelLikeCurrentCell());
		// ASSERT: Otherwise the current cell will not be put in the rangelist below and will
		// crash when trying to drag the current cell.

	CGXRange rgSel = *(pGrid->GetParam()->GetRangeList()->GetAt(pGrid->GetParam()->GetRangeList()->FindRange(nRow, nCol)));
	// Cannot start an excel like fill from frozen/header rows/cols...
	// We don't support auto fill on complete row/col, yet
	if(nRow >= pGrid->GetTopRow() && nCol >= pGrid->GetLeftCol() 
		&& !rgSel.IsRows() && !rgSel.IsCols() && !rgSel.IsTable()
		&& pGrid->OnStartAutoFillSelection(rgSel, flags, point))
	{
		pGrid->TransferCurrentCell(nRow, nCol);
		pGrid->m_nHitState |= GX_FILLDRAG;
		m_startRange = rgSel;
		m_ExcelLastRect.SetRectEmpty();
		m_ExcelLastRange.SetCells(0,0,0,0);
	}

	GX_UNUSED_ALWAYS(ht);
	GX_UNUSED_ALWAYS(flags);
	GX_UNUSED_ALWAYS(point);
}

#pragma warning (push)
#pragma warning (disable: 4701)

BOOL CGXGridExcelLikeFillImp::OnMouseMove(CGXGridCore* pGrid, CPoint& point, UINT& flags, ROWCOL& nRow, ROWCOL& nCol)
{
	GX_UNUSED_ALWAYS(flags);
	
	if (pGrid->m_nHitState & GX_FILLDRAG)
	{
		// Source rect during drag start...
		CRect rSource = pGrid->CalcRectFromRowCol(max(m_startRange.top, pGrid->GetTopRow()), max(m_startRange.left, pGrid->GetLeftCol()), max(m_startRange.bottom, pGrid->GetTopRow()), max(m_startRange.right, pGrid->GetLeftCol()));
		if(m_startRange.top < pGrid->GetTopRow())
			rSource.top -= pGrid->CalcSumOfRowHeights(m_startRange.top, pGrid->GetTopRow()-1);
		if(m_startRange.bottom < pGrid->GetTopRow())
			rSource.bottom -= pGrid->CalcSumOfRowHeights(m_startRange.bottom, pGrid->GetTopRow()-1);
		if(m_startRange.left < pGrid->GetLeftCol())
			rSource.left -= pGrid->CalcSumOfColWidths(m_startRange.left, pGrid->GetLeftCol()-1);
		if(m_startRange.right < pGrid->GetLeftCol())
			rSource.right -= pGrid->CalcSumOfColWidths(m_startRange.left, pGrid->GetLeftCol()-1);

		GXExcelFillQuadrant quad = within; 
		if(point.y < rSource.top)
		{
			if(point.x > (rSource.left + rSource.Width()/2))
			{
				if((rSource.top - point.y) > (point.x - rSource.right))
					quad = top;
				else
					quad = right;
			}
			else
			{
				if((rSource.top - point.y) > (rSource.left - point.x))
					quad = top;
				else
					quad = left;
			}
		}
		if(point.y > rSource.bottom)
		{
			if(point.x > (rSource.left + rSource.Width()/2))
			{
				if((point.y - rSource.bottom) > (point.x - rSource.right))
					quad = bottom;
				else
					quad = right;
			}
			else
			{
				if((point.y - rSource.bottom) > (rSource.left - point.x))
					quad = bottom;
				else
					quad = left;
			}
		}
		if(point.x > rSource.right)
		{
			if(point.y > (rSource.top + rSource.Height()/2))
			{
				if((point.x - rSource.right) > (point.y - rSource.bottom))
					quad = right;
				else
					quad = bottom;
			}
			else
			{
				if((point.x - rSource.right) > (rSource.top - point.y))
					quad = right;
				else
					quad = top;
			}
		}
		if(point.x < rSource.left)
		{
			if(point.y > (rSource.top + rSource.Height()/2))
			{
				if((rSource.right - point.x) > (point.y - rSource.bottom))
					quad = left;
				else
					quad = bottom;
			}
			else
			{
				if((rSource.right - point.x) > (rSource.top - point.y))
					quad = left;
				else
					quad = top;
			}
		}
		// So far determined the quadrant...
		// Now find th exact cell...
		CRect rCell = pGrid->CalcRectFromRowCol(nRow, nCol);
		ROWCOL rcTop, rcLeft, rcBottom, rcRight;
		if(quad == within)
		{
			// Calculations based on row/col values rather than cursor pos values...
			rcTop = m_startRange.top;
			rcLeft = m_startRange.left;
			if((m_startRange.bottom - nRow) > (m_startRange.right - nCol))
			{
				rcRight = m_startRange.right;
				rcBottom = nRow;
			}
			else if((m_startRange.bottom - nRow) < (m_startRange.right - nCol))
			{
				rcRight = nCol;
				rcBottom = m_startRange.bottom;
			}
			else // if equal...
			{
				rcRight = nCol;
				rcBottom = m_startRange.bottom;
			}
		}
		else if(quad == top)
		{
			rcLeft = m_startRange.left;
			rcRight = m_startRange.right;
			rcBottom = m_startRange.bottom;
			if(point.y < (rCell.bottom - rCell.Height()/2))
				rcTop = nRow;
			else 
				rcTop = nRow + 1;
		}
		else if(quad == bottom)
		{
			rcLeft = m_startRange.left;
			rcRight = m_startRange.right;
			rcTop = m_startRange.top;
			if((int)point.y > (rCell.bottom - (rCell.Height()/2)))
				rcBottom = nRow;
			else 
				rcBottom = nRow - 1;
		}
		else if(quad == left)
		{
			rcTop = m_startRange.top;
			rcBottom = m_startRange.bottom;
			rcRight = m_startRange.right;
			if(point.x < (rCell.right - rCell.Width()/2))
				rcLeft = nCol;
			else 
				rcLeft = nCol+1;
		}
		else if(quad == right)
		{
			rcTop = m_startRange.top;
			rcBottom = m_startRange.bottom;
			rcLeft = m_startRange.left;
			if(point.x > (rCell.left + rCell.Width()/2))
				rcRight = nCol;
			else 
				rcRight = nCol-1;
		}
		CGXRange rgNew(rcTop, rcLeft, rcBottom, rcRight);
		// Draw Focus rect around the final range...
		DrawDragRect(pGrid, rgNew, TRUE, TRUE);
	}

	return FALSE;
}

#pragma warning (pop) //4701

void CGXGridExcelLikeFillImp::DrawDragRect(CGXGridCore* pGrid, CGXRange& rgNew, BOOL bEraseOld, BOOL bDrawNew)
{
	// If new is same as old and if bDeleteOld and bDrawNew, nothing to do...
	if(bEraseOld && bDrawNew && rgNew.top == m_ExcelLastRange.top  
		&& rgNew.bottom == m_ExcelLastRange.bottom && rgNew.left == m_ExcelLastRange.left
			&& rgNew.right == m_ExcelLastRange.right)
		return;

	if(bDrawNew && !pGrid->CanChangeAutoFillSelection(rgNew, m_startRange))
	{
		// Recursive call to erase out the current selection
		DrawDragRect(pGrid, rgNew, TRUE, FALSE);
		return;
	}

	CGXGridParam* pParam = pGrid->GetParam();
	CClientDC dc(pGrid->m_pGridWnd);
	pGrid->OnGridPrepareDC(&dc);
	dc.IntersectClipRect(pGrid->GetGridRect());

	if (bEraseOld)
	{
		if (!m_ExcelLastRect.IsRectEmpty())
		{
			dc.DrawFocusRect(m_ExcelLastRect);
			m_ExcelLastRect.top++;
			m_ExcelLastRect.left++;
			m_ExcelLastRect.right--;
			m_ExcelLastRect.bottom--;
			dc.DrawFocusRect(m_ExcelLastRect);
		}
		m_ExcelLastRect.SetRectEmpty();
		m_ExcelLastRange.SetCells(0,0,0,0);
	}

	if (bDrawNew)
	{
		m_ExcelLastRange = rgNew;
		ROWCOL nDispTop = max(rgNew.top, pGrid->GetTopRow());
		ROWCOL nDispLeft = max(rgNew.left, pGrid->GetLeftCol());
		ROWCOL nDispBottom = min(rgNew.bottom, pGrid->CalcBottomRowFromRect(pGrid->GetGridRect()));
		ROWCOL nDispRight = min(rgNew.right, pGrid->CalcRightColFromRect(pGrid->GetGridRect()));

		CRect rectDraw = pGrid->CalcRectFromRowCol(nDispTop, nDispLeft, nDispBottom, nDispRight);
		
		if (pParam->GetProperties()->GetDisplayVertLines())
		{
			if (pParam->GetNewGridLineMode())
				rectDraw.right--;
			else
				rectDraw.left++;
		}

		if (pParam->GetProperties()->GetDisplayHorzLines())
		{
			if (pParam->GetNewGridLineMode())
				rectDraw.bottom--;
			else
				rectDraw.top++;
		}

		dc.DrawFocusRect(rectDraw);

		// save state
		m_ExcelLastRect = rectDraw;

		rectDraw.top++;
		rectDraw.left++;
		rectDraw.right--;
		rectDraw.bottom--;

		dc.DrawFocusRect(rectDraw);
	}
}
void CGXGridExcelLikeFillImp::OnLButtonUp(CGXGridCore* pGrid, CPoint& point, UINT& flags)
{
	GX_UNUSED_ALWAYS(flags);
	GX_UNUSED_ALWAYS(point);
	if(pGrid->m_nHitState & GX_FILLDRAG)
	{
		CGXRange rFinal = m_ExcelLastRange;
		// Erase the last drawn focus rect...
		
		CGXRange rgNull;
		DrawDragRect(pGrid, rgNull, TRUE, FALSE);
		pGrid->m_nHitState &= ~GX_FILLDRAG;
		// Fill the new selection with data...
		if(!(rFinal.top == 0 && rFinal.bottom == 0 && rFinal.left == 0 && rFinal.right == 0))
		{
			// Remove the current selection...
			pGrid->SetSelection(NULL);
			pGrid->DoAutoFill(rFinal, m_startRange);
			pGrid->OnAutoFillDone(rFinal);
			pGrid->RefreshViews(TRUE);
		}
	}
}

void CGXGridExcelLikeFillImp::OnAutoFillDone(CGXGridCore* pGrid, CGXRange& rFinal)
{
	// Set the new selection area...
	POSITION area = pGrid->GetParam()->GetRangeList()->AddTail(new CGXRange());
	pGrid->SetSelection(area, rFinal.top, rFinal.left, rFinal.bottom, rFinal.right);
}

void CGXGridExcelLikeFillImp::FillRect(CGXGridCore* pGrid, CGXRange& rgFrom, CGXRange& rgTo)
{
	// rgFrom == rgTo, do nothing...
	if(rgFrom.top == rgTo.top && rgFrom.left == rgTo.left && rgFrom.right == rgTo.right && rgFrom.bottom == rgTo.bottom)
		return;
	// Copy/Clear styles or values...
	BOOL bStyles = pGrid->GetParam()->m_nExcelLikeFillFlags & GX_XLFILLSTYLE ;
	BOOL bText = pGrid->GetParam()->m_nExcelLikeFillFlags & GX_XLFILLTEXT ;
	// If none of them set, nothing to do...
	if(!bStyles && !bText)
		return;

	// Store the following commands in a block command so that they could be undone in one shot
	if(pGrid->m_pUndoImp && pGrid->m_pParam->m_bUndoEnabled)
	{
		pGrid->AddCommand(pGrid->m_pUndoImp->CreateBlockCmd(), gxDo);
		pGrid->m_bBlockCmd = TRUE;
	}

	// Just clear cells at the bottom...
	if(rgTo.GetHeight() < rgFrom.GetHeight())
	{
		CGXRangeList rl;
		rl.AddTail(new CGXRange (rgTo.bottom+1, rgTo.left, rgFrom.bottom, rgTo.right));
		if(bStyles)
			pGrid->ClearCells(rl, TRUE);
		else if(bText)
			pGrid->ClearCells(rl, FALSE);
		pGrid->m_bBlockCmd = FALSE;
		return;
	}
	// Just clear cells to the right...
	if(rgTo.GetWidth() < rgFrom.GetWidth())
	{
		CGXRangeList rl;
		rl.AddTail(new CGXRange (rgTo.top, rgTo.right+1, rgFrom.bottom, rgFrom.right));
		if(bStyles)
			pGrid->ClearCells(rl, TRUE);
		else if(bText)
			pGrid->ClearCells(rl, FALSE);
		
		pGrid->m_bBlockCmd = FALSE;
		return;
	}

	int dir; // horz == 0; vert == 1
	// Range to be filled...
	ROWCOL nTop, nLeft, nRight, nBottom;

	// Expand veritically...
	if(rgFrom.GetWidth() == rgTo.GetWidth())	
	{
		dir = 1;
		nLeft = rgFrom.left;
		nRight = rgFrom.right;
		if(rgTo.bottom > rgFrom.bottom)
		{
			nTop = rgFrom.bottom + 1;
			nBottom = rgTo.bottom;
		}
		else
		{
			nTop = rgTo.top;
			nBottom = rgFrom.top - 1;
		}	
	}
	// Expand horizontally...
	else 
	{
		dir = 0;
		nTop = rgFrom.top;
		nBottom = rgFrom.bottom;
		if(rgTo.right > rgFrom.right)
		{
			nLeft = rgFrom.right + 1;
			nRight = rgTo.right;
		}
		else
		{
			nLeft = rgTo.left;
			nRight = rgFrom.left - 1;
		}
	}

	CGXRange rgToFill(nTop, nLeft, nBottom, nRight);
	CGXStyle* pStyle = pGrid->CreateStyle();
	if(dir == 1)	// Fill vertically...
	{
		ROWCOL rf = rgFrom.top;	// row position indicator in rgFrom...
		for(ROWCOL r = rgToFill.top; r <= rgToFill.bottom; r++)
		{
			for(ROWCOL c = rgToFill.left; c <= rgToFill.right; c++)
			{
				if(bStyles)
				{
					pGrid->ComposeStyleRowCol(rf, c, pStyle, FALSE);
					pGrid->SetStyleRange(CGXRange(r, c), *pStyle);
					pStyle->Free();
				}
				else if(bText)
				{
					//CString sValue = pGrid->GetValueRowCol(rf, c);
					//pGrid->SetValueRange(CGXRange(r, c), sValue);
					CString sValue = pGrid->GetCopyTextRowCol(rf, c);
					pGrid->SetControlTextRowCol(r, c, sValue);
				}
			}
			if(rf == rgFrom.bottom)
				rf = rgFrom.top;
			else
				rf++;
		}
	}
	else if(dir == 0)	// Fill horizontally...
	{
		ROWCOL cf = rgFrom.left;	// row position indicator in rgFrom...
		for(ROWCOL c = rgToFill.left; c <= rgToFill.right; c++)
		{
			for(ROWCOL r = rgToFill.top; r <= rgToFill.bottom; r++)
			{
				if(bStyles)
				{
					pGrid->ComposeStyleRowCol(r, cf, pStyle, FALSE);
					pGrid->SetStyleRange(CGXRange(r, c), *pStyle);
					pStyle->Free();
				}
				else if(bText)
				{
					//CString sValue = pGrid->GetValueRowCol(r, cf);
					//pGrid->SetValueRange(CGXRange(r, c), sValue);
					CString sValue = pGrid->GetCopyTextRowCol(r, cf);
					pGrid->SetControlTextRowCol(r, c, sValue);
				}
			}
			if(cf == rgFrom.right)
				cf = rgFrom.left;
			else
				cf++;
		}
	}
	pGrid->RecycleStyle(pStyle);
	pGrid->m_bBlockCmd = FALSE;
}

void CGXGridExcelLikeFillImp::ClearCurrentDragRect(CGXGridCore* pGrid)
{
	CGXRange rgNull;
	DrawDragRect(pGrid, rgNull, TRUE, FALSE);
}

