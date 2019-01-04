///////////////////////////////////////////////////////////////////////////////
// gxhierGrid.cpp
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

#define _OG_EXPORT_IMPL

#include "stdafx.h"

#pragma warning(disable: 4244)

#ifdef _GXDLL
#undef AFXAPI_DATA
#define AFXAPI_DATA __based(__segname("_DATA"))
#endif

#ifndef _GX_HIERARCHY_GRID
#include "grid\HierGrid\gxhiergrid.h"
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXHIERGRID")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

#ifdef TICKCOUNT
#define _TC_(f) f
#else
#define _TC_(f)
#endif

#ifdef TICKCOUNT
#define _TC_(f) f
#else
#define _TC_(f)
#endif

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

WORD IGXHierarchyGrid::m_nUsedUpControlIds = 0;

IGXHierarchyGrid::IGXHierarchyGrid(gxHierGridType commonChildGridType /* =gxNone */, BOOL bCommonChildGridHeader /* = FALSE */)
{
	m_gridParent = NULL;
	m_CommonChildGridType = commonChildGridType;
	if(bCommonChildGridHeader)
		ASSERT(m_CommonChildGridType != 0);
		// TRUE only if common child grid type

	m_bCommonChildGridHeader = bCommonChildGridHeader;

	m_pRegularGridClass = NULL;
	m_pMRTGridClass = NULL;
	m_pWrappedGridClass = NULL;
	m_nMaxChildWidth = 0;
	m_nChildId = GX_INVALID;
	m_bProcessingPaint = FALSE;
	m_bScrollChildGridContainerCell = FALSE;
}

IGXHierarchyGrid::~IGXHierarchyGrid()
{
}

CRuntimeClass* IGXHierarchyGrid::GetGridClass(gxHierGridType type)
{
	switch(type)
	{
		case gxRegularGrid:	return m_pRegularGridClass;
		case gxMRTGrid:	return m_pMRTGridClass;
		case gxWrappedGrid:	return m_pWrappedGridClass;
		default: return NULL;
	}
}

WORD IGXHierarchyGrid::CreateAndRegisterControl(IGXHierarchyGrid* pChildHierGrid, WORD id /* =0 */)
{
	CGXGridCore* pThisAsGridCore = dynamic_cast<CGXGridCore*>(this);
	ASSERT(pThisAsGridCore);

	ASSERT(pChildHierGrid);

	BOOL bOldLock = pThisAsGridCore->LockUpdate(TRUE);

		// Cannot be NULL
	CGXGridWnd* pChildGrid = dynamic_cast<CGXGridWnd*>(pChildHierGrid);
	// Should also be a CGXGridWnd derivative.
	ASSERT(pChildGrid);

	WORD controlId;
	if(id) controlId = id;
	else controlId = _GX_GRID_WND_WRAPPER_BASE+m_nUsedUpControlIds++;
	
	pChildHierGrid->m_gridParent = (IGXHierarchyGrid*)this;

	CFriendlyGridWnd* pFriendlyGrid = (CFriendlyGridWnd*)pChildGrid;
	if(!(*pFriendlyGrid).m_bInitDone)
	{
		OnChildGridInitializing(pChildHierGrid);
		pChildGrid->Initialize();
	}

	OnRegisterChildGrid(pChildHierGrid);

	// Keep track of the MaxChildWidth.
	BOOL bOldLimit = pChildGrid->m_bLimitColWidth;
	pChildGrid->m_bLimitColWidth = FALSE;
	m_nMaxChildWidth = max(m_nMaxChildWidth, pChildGrid->CalcSumOfColWidths(0, pChildGrid->GetColCount()));
	pChildGrid->m_bLimitColWidth = bOldLimit;

	CGXHierGridWrapper* pGridWrapper = new CGXHierGridWrapper(pThisAsGridCore, pChildGrid, TRUE, TRUE, FALSE);
	pThisAsGridCore->RegisterControl(controlId, pGridWrapper, FALSE, FALSE);

	pThisAsGridCore->LockUpdate(bOldLock);

	return controlId;
}

void IGXHierarchyGrid::OnChildGridInitializing(IGXHierarchyGrid* /*pChildGrid*/)
{
	// Nothing to do.
}

void IGXHierarchyGrid::OnRegisterChildGrid(IGXHierarchyGrid* pChildHierGrid)
{
	pChildHierGrid;
}


IGXHierarchyGrid* IGXHierarchyGrid::GetGridFromControlId(WORD wControlId)
{
	if(wControlId == 0)
		return NULL;
	CGXHierGridWrapper* pWrapper = (CGXHierGridWrapper*)dynamic_cast<CGXGridCore*>(this)->GetRegisteredControl(wControlId);
	if(!pWrapper)
		return NULL;
	return dynamic_cast<IGXHierarchyGrid*>(pWrapper->GetWndPtr());
}

IGXHierarchyGrid* IGXHierarchyGrid::GetChildAt(ROWCOL nLogRow, BOOL bForceCreation /*= FALSE*/)
{
	return GetGridFromControlId(GetChildControlAt(nLogRow, bForceCreation));
}

WORD IGXHierarchyGrid::GetChildControlAt(ROWCOL nRow, BOOL bForceCreation /*= FALSE*/)
{
	if(bForceCreation && m_CommonChildGridType && nRow != 0) 
	{
		if(m_wChildGrids.GetSize() <= (long)nRow || !m_wChildGrids.GetAt(nRow))
			InsertChildAt(nRow, m_CommonChildGridType);
	}

	if(m_wChildGrids.GetSize() > (WORD)nRow && m_wChildGrids.GetAt(nRow) != 0) 
		return m_wChildGrids.GetAt(nRow);
	return 0;
}

IGXHierarchyGrid* IGXHierarchyGrid::GetParent()
{
	return m_gridParent;
}

CGXGridCore* IGXHierarchyGrid::GetParentGrid()
{
	return dynamic_cast<CGXGridCore*>(m_gridParent);
}


void IGXHierarchyGrid::SetChildGridTemplate(gxHierGridType gridType, CRuntimeClass* pRuntimeGridClass)
{
//	ClearChildGrids();
	// Move to class factory
	switch (gridType)
	{
		case gxRegularGrid:	m_pRegularGridClass = pRuntimeGridClass; break;
		case gxMRTGrid:	m_pMRTGridClass = pRuntimeGridClass; break;
		case gxWrappedGrid:	m_pWrappedGridClass = pRuntimeGridClass; break;
		default: ASSERT(FALSE);	// Wrong gridType
	}	
}

void IGXHierarchyGrid::SetCommonChildGridType(gxHierGridType gridType, CRuntimeClass* pRuntimeGridClass, BOOL bCommonChildGridHeader/*=FALSE*/)
{
 	ASSERT(m_CommonChildGridType == gxNone && gridType != gxNone);
		// Call this only once. And there be a valid common childgrid type.
	m_CommonChildGridType = gridType;
	m_bCommonChildGridHeader = bCommonChildGridHeader;
	SetChildGridTemplate(gridType, pRuntimeGridClass);
	if(m_bCommonChildGridHeader)
		InsertChildAt(0, m_CommonChildGridType);
}

void IGXHierarchyGrid::DeleteChildAt(ROWCOL nLogRow)
{
	if((ROWCOL)m_wChildGrids.GetSize() <= nLogRow)
		return;

	CGXGridCore* pThisAsGrid = dynamic_cast<CGXGridCore*>(this);

	WORD nControlId =  m_wChildGrids.GetAt(nLogRow);
	if(nControlId)
	{
		// First Hide the child.
		ShowChildAt(nLogRow, FALSE);

		// Delete and remove the control from the control map.
		delete pThisAsGrid->GetRegisteredControl(nControlId);
		CFriendlyGridTemplate<CGXGridView>* pFriendlyGrid = (CFriendlyGridTemplate<CGXGridView>*)pThisAsGrid;
		pFriendlyGrid->m_ControlMap.RemoveKey((void*) (SEC_DWORD) nControlId);
		m_wChildGrids.SetAt(nLogRow, 0);
	}
}

void IGXHierarchyGrid::DeleteChildren(ROWCOL nFromLogRow, ROWCOL nToLogRow)
{
	ASSERT(nFromLogRow <= nToLogRow);

	for(ROWCOL nParseRow = nFromLogRow; nParseRow <= nToLogRow; nParseRow++)
		DeleteChildAt(nParseRow);
}


void IGXHierarchyGrid::InsertLogRows(ROWCOL nLogRow, ROWCOL nCount)
{
	ROWCOL nCurSize = (DWORD)m_wChildGrids.GetSize();
	// Insert if the array is already that big...
	if(nCurSize > nLogRow)
		m_wChildGrids.InsertAt(nLogRow, 0, nCount);
	// else just increase the size of the array.
	else
		m_wChildGrids.SetSize(nLogRow+nCount);
	// Adjust the childid of the children
	nCurSize = (DWORD)m_wChildGrids.GetSize();
	for(ROWCOL i=nLogRow+nCount; i < nCurSize; i++)
	{
		IGXHierarchyGrid* pChildGrid = GetChildAt(i);
		if(pChildGrid)
			pChildGrid->m_nChildId = i;
	}
}

void IGXHierarchyGrid::RemoveLogRows(ROWCOL nFromRow, ROWCOL nToRow)
{
	if(nFromRow == GX_INVALID || nToRow == GX_INVALID)
		return;

	CGXGridCore* pThisAsGrid = dynamic_cast<CGXGridCore*>(this);
        ASSERT(pThisAsGrid != NULL);

	// Parse through all the rows and unregister/destroy the control.
	for(ROWCOL nRowParse = nFromRow; nRowParse <= nToRow; nRowParse++)
	{
		if(m_wChildGrids.GetSize() > nRowParse)
		{
			DeleteChildAt(nRowParse);
			// Remove entry from the Row/Control map.
			m_wChildGrids.RemoveAt(nRowParse);
		}
	}

	// now remove the rows...
	ROWCOL nAbsFromRow, nAbsToRow, nAbsCol;
	GetAbsCellFromLogCell(nFromRow, 0, nAbsFromRow, nAbsCol) ;
	GetAbsCellFromLogCell(nToRow, 0, nAbsToRow, nAbsCol) ;
	pThisAsGrid->CGXGridCore::RemoveRows(nAbsFromRow, nAbsToRow + 1);
	
	// Adjust the childid of the children
	ROWCOL nCurSize = (DWORD)m_wChildGrids.GetSize();
	for(ROWCOL i=nFromRow; i < nCurSize; i++)
	{
		IGXHierarchyGrid* pChildGrid = GetChildAt(i);
		if(pChildGrid)
			pChildGrid->m_nChildId = i;
	}
}

void IGXHierarchyGrid::MoveLogRows(ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow)
{
	// rearrange the array with row indices
	int nIndex = (int) nFromRow;
	int nCount = (int) nToRow - (int) nFromRow + 1;
	int nDest = (int) nDestRow;

	//int nFirst = min(nIndex, nDest);
	int nLast = max(nIndex+nCount, nDest+nCount);

	BOOL bProcessed = FALSE;

	// easiest case: nothing to do
	if (nDest == nIndex || nCount == 0)
		return;

	// move rows to the top
	else if (nDest < nIndex)
	{
		nIndex += nCount;
		bProcessed = TRUE;
	}

	// move rows to the bottom
	else if (nDest > nIndex)
	{
		nDest += nCount;
		bProcessed = TRUE;
	}

	// do the job
	if (bProcessed)
	{
		// First, assign row ids to the entries in the range
		// which not yet have a valid column id.

		int n;

		if (m_wChildGrids.GetUpperBound() < nLast)
			m_wChildGrids.SetSize(nLast+1);

		m_wChildGrids.InsertAt(nDest, 0, nCount);

		// initialize the new rows
		for (n = 0; n < nCount; n++)
			m_wChildGrids[nDest+n] = m_wChildGrids[nIndex+n];

		m_wChildGrids.RemoveAt(nIndex, nCount);
	}

	// Adjust the childid of the children
	ROWCOL nCurSize = (DWORD)m_wChildGrids.GetSize();
	for(ROWCOL  i = min(nFromRow,nDestRow); i < nCurSize; i++)
	{
		IGXHierarchyGrid* pChildGrid = GetChildAt(i);
		if(pChildGrid)
			pChildGrid->m_nChildId = i;
	}
}

void IGXHierarchyGrid::RearrangeChildren(const CGXRange& sortRange, const CRowColArray& awRowIndex)
{
	ASSERT(sortRange.IsRows());
	// ASSERTION-> Only full rows supported. Override this
	// method if you want to support sorting only a limited
	// range of cells ->END

	if(sortRange.top > m_wChildGrids.GetSize()-1)
		return;

	CWordArray newChildGridIDs;
	
	newChildGridIDs.SetSize(awRowIndex.GetSize());

	// First, replace child ids with existing child ids
	int nIndex;
	for (nIndex = 0; nIndex < awRowIndex.GetSize(); nIndex++)
		newChildGridIDs[nIndex] = GetChildControlAt(awRowIndex[nIndex]+sortRange.top);

	// Now, copy child ids to m_wChildGrids
	if (m_wChildGrids.GetSize() <= sortRange.bottom)
		m_wChildGrids.SetSize((int) sortRange.bottom+1);

	for (nIndex = 0
		; nIndex < awRowIndex.GetSize() && ((nIndex + (int) sortRange.top) < m_wChildGrids.GetSize())
		; nIndex++)
		m_wChildGrids[nIndex+(int) sortRange.top] = newChildGridIDs[nIndex];

	// Adjust the childid of the children
	ROWCOL nCurSize = (DWORD)m_wChildGrids.GetSize();
	for(ROWCOL i=sortRange.top; i < nCurSize; i++)
	{
		IGXHierarchyGrid* pChildGrid = GetChildAt(i);
		if(pChildGrid)
			pChildGrid->m_nChildId = i;
	}
}

#pragma warning (push)
#pragma warning (disable: 4706)

void IGXHierarchyGrid::InsertChildAt(ROWCOL nRow, gxHierGridType gridType)
{
	CWnd* pThisAsWnd = dynamic_cast<CWnd*>(this);
	ASSERT(pThisAsWnd);

	if(m_wChildGrids.GetSize() > (WORD)nRow)
	{
		WORD wControl;
		// Intentional Assignment???
		if(wControl = m_wChildGrids.GetAt(nRow))
		{
			CGXHierGridWrapper* pHier = (CGXHierGridWrapper*)dynamic_cast<CGXGridCore*>(this)->GetRegisteredControl(wControl);
			IGXHierarchyGrid* pGrid = dynamic_cast<IGXHierarchyGrid*>(pHier->GetWndPtr());
			if(pGrid && pGrid->GetGridType() == gridType)
				return;		// Child of the same type already exists...
		}
	}
	CGXGridWnd* pGridChildWnd = (CGXGridWnd*)GetGridClass(gridType)->CreateObject();
	DWORD flags = WS_VISIBLE;
	// The common child-header grid should not have a border.
	if(nRow != 0)
		flags |= WS_BORDER;

	VERIFY(pGridChildWnd->Create(flags, CRect(0,0,1,1), pThisAsWnd, m_nUsedUpControlIds));
	IGXHierarchyGrid* pChildAsHier = dynamic_cast<IGXHierarchyGrid*>(pGridChildWnd);
	
	InsertChildAt(nRow, pChildAsHier);
}

#pragma warning (pop) //4706

void IGXHierarchyGrid::InsertChildAt(ROWCOL nRow, IGXHierarchyGrid* pGrid)
{
	if(m_CommonChildGridType)
		ASSERT(pGrid->GetGridType() == m_CommonChildGridType);
		// Call this API only for non-CommonChildGridTypes

	pGrid->m_nChildId = nRow;		// A Id indicating the parent row where the child is inserted.

	if(m_wChildGrids.GetSize() > (WORD)nRow)
	{
		if(m_wChildGrids.GetAt(nRow))
			CreateAndRegisterControl(pGrid, m_wChildGrids.GetAt(nRow));
		else
			m_wChildGrids.SetAt(nRow, CreateAndRegisterControl(pGrid));
	}
	else
		m_wChildGrids.SetAtGrow(nRow, CreateAndRegisterControl(pGrid));
}

#pragma warning (push)
#pragma warning (disable: 4706)

int IGXHierarchyGrid::GetOptimalChildHeightAt(ROWCOL nPatternRow)
{
	if(m_wChildGrids.GetSize() <= (WORD)nPatternRow)
		return -1;
	CGXControl* pControl = dynamic_cast<CGXGridCore*>(this)->GetRegisteredControl(m_wChildGrids.GetAt(nPatternRow));
	CGXHierGridWrapper* pGridWrapper = NULL;
	// Intentional Assignment???
	if(pGridWrapper = dynamic_cast<CGXHierGridWrapper*>(pControl))
	{
		CGXGridWnd* pGrid = (CGXGridWnd*)pGridWrapper->GetWndPtr();
		BOOL bOldLimitRowHeight = pGrid->m_bLimitRowHeight;
		pGrid->m_bLimitRowHeight = FALSE;
		int height = pGrid->CalcSumOfRowHeights(0, pGrid->GetRowCount());
		pGrid->m_bLimitRowHeight = bOldLimitRowHeight;
		CFriendlyGridWnd* pFriendlyGrid = (CFriendlyGridWnd*)pGrid;
		if(pFriendlyGrid->m_bPrintInProgress)
			height += 1;
		else
			height += 3;
		return height;
	}
	return -1;
}

#pragma warning (pop) //4706

void IGXHierarchyGrid::ShowChildAt(ROWCOL nLogRow, BOOL bShow/*=TRUE*/)
{
	// Insert a child if not already there for CommonChildGridType grids.
	if(m_CommonChildGridType && bShow)
	{
		if(m_wChildGrids.GetSize() <= (long)nLogRow || !m_wChildGrids.GetAt(nLogRow))
			InsertChildAt(nLogRow, m_CommonChildGridType);
	}

	if(!bShow)
	{
		CGXGridCore* pGrid = dynamic_cast<CGXGridCore*>(this);
		ROWCOL nAbsChildRow, nAbsChildCol;
		GetAbsCellContainingChild(nLogRow, nAbsChildRow, nAbsChildCol);
		pGrid->GetControl(nAbsChildRow, nAbsChildCol)->Hide();
	}

	OnShowChildAt(nLogRow, bShow);
	// Send a hint to parent.
	CGXGridHint hint(gxHintUpdateChangedRowHeights, m_nChildId);
	if(m_gridParent)
		m_gridParent->UpdateHintFromChild(m_nChildId, &hint);
}

int IGXHierarchyGrid::GetMaxChildWidth()
{
	// If there is atleast one logical row and all children are of the same type.
//	if(GetLogRowCount() && m_CommonChildGridType)	
//		InsertChildAt(1, m_CommonChildGridType);	// Make sure atleast one child is inserted.

	return m_nMaxChildWidth;
}

void IGXHierarchyGrid::OnChangedChildColWidth(ROWCOL nChildId)
{
	IGXHierarchyGrid* pChild = GetChildAt(nChildId);
	if(!pChild)	// Not yet registered, so just return.
		return;
	CGXGridCore* pChildGrid = dynamic_cast<CGXGridCore*>(pChild);
	int nWidth = pChildGrid->CalcSumOfColWidths(0, pChildGrid->GetColCount());
	if(m_CommonChildGridType)
		m_nMaxChildWidth = nWidth;
	else
	{
		// Loop through all the children and get the max width.
		int nMaxWidth = 0;
		for(ROWCOL i=1; i <= GetLogRowCount(); i++)
		{
			IGXHierarchyGrid* pChild = GetChildAt(i);
			if(pChild)
			{
				CGXGridCore* pChildGrid = dynamic_cast<CGXGridCore*>(pChild);
				BOOL bOldLimit = pChildGrid->m_bLimitColWidth;
				pChildGrid->m_bLimitColWidth = FALSE;
				nMaxWidth = max(nMaxWidth, pChildGrid->CalcSumOfColWidths(0, pChildGrid->GetColCount()));
				pChildGrid->m_bLimitColWidth = bOldLimit;
			}
		}
		m_nMaxChildWidth = nMaxWidth;
	}
}

void IGXHierarchyGrid::UpdateHintFromChild(ROWCOL nChildId, CGXGridHint* pHint)
{
	CGXGridCore* pThisAsGridCore = dynamic_cast<CGXGridCore*>(this);
	// If common child grid types, pass on the hint to the other child grids.
	if(m_CommonChildGridType)
	{
		for(ROWCOL i=0; i <= GetLogRowCount() ; i++)
		{
			IGXHierarchyGrid* pChild = GetChildAt(i);
			if(pChild && nChildId != pChild->m_nChildId
				&& (pHint->m_id == gxHintUpdateChangedColWidths || pHint->m_id == gxHintUpdateMoveCols))	// Don't send it to the source.
				pChild->UpdateHintFromPeer(pHint);
		}
	}
	switch(pHint->m_id)
	{
	case gxHintRedraw:
			// QA: 32073 - HierGrid Plus/Minus Resizing.
			// Force a redraw all the way up to the parent.
			pThisAsGridCore->Redraw();
			break;
	case gxHintUpdateMoveCols:
			if(m_CommonChildGridType)
				pThisAsGridCore->Redraw();
			break;
	case gxHintUpdateChangedColWidths:
			OnChangedChildColWidth(nChildId);
			break;
	case gxHintUpdateChangedRowHeights:
	case gxHintUpdateInsertRows:
	case gxHintUpdateRemoveRows:
			OnChangedChildRowHeight(nChildId);
			break;
	case gxHintChangingRowBreaks:	// Sent by wrapped grids, when the columns are moved around
									// with or without affecting the no. of row-breaks.
			// if common child grid type, just redraw the whole parent grid.
			if(m_CommonChildGridType)
				pThisAsGridCore->Redraw();
			else
			{
				
				if(pHint->lParam != ((CDWordArray*)pHint->vptr)->GetSize())
					// Redraw the whole grid if new row-breaks count
					pThisAsGridCore->Redraw();	
				else
					// Redraw only if the resultant col count changed.
					OnChangedChildColWidth(nChildId);	
			}
			break;
	default:
		// Nothing.
		break;
	}

}

BOOL IGXHierarchyGrid::IsChildGridCellVisible(ROWCOL nChildId)
{
	// If header-child, then always visible.
	if(nChildId == 0)
		return TRUE;
	// If collapsed, then return FALSE.
	if(!IsChildShown(nChildId))
		return FALSE;

	CGXGridCore* pThisAsGridCore = dynamic_cast<CGXGridCore*>(this);

	ROWCOL nChildRow, nChildCol;
	GetAbsCellContainingChild(nChildId, nChildRow, nChildCol);
	// If not in the visible area, return FALSE
	if(nChildRow < pThisAsGridCore->GetTopRow()
		|| nChildRow > pThisAsGridCore->CalcBottomRowFromRect(pThisAsGridCore->GetGridRect())
		|| nChildCol > pThisAsGridCore->CalcRightColFromRect(pThisAsGridCore->GetGridRect())
		)
		return FALSE;

	return TRUE;
}

// Wrapper for child grids.

CGXHierGridWrapper::CGXHierGridWrapper(CGXGridCore* pGrid, CWnd* pWnd, BOOL bNeedDestroy, BOOL bCanActivate, BOOL bInvertBorders)
	: CGXWndWrapper(pGrid, pWnd, bNeedDestroy, bCanActivate, bInvertBorders)
{
}

CGXHierGridWrapper::CGXHierGridWrapper(CGXGridCore* pGrid)
	: CGXWndWrapper(pGrid)
{
}

/*
void CGXHierGridWrapper::OnNotifyMsg(MSG* pMsg)
{
	// Called from CGXGridCore::OnVScroll, OnHScroll
	pMsg;

	// deactivate the current cell when the user scrolls 

	if (pMsg->message == WM_VSCROLL
		|| pMsg->message == WM_HSCROLL)
	{
		SetActive(FALSE);
		Refresh();
	}
}
*/
BOOL CGXHierGridWrapper::IsActiveAlways()
{
	return TRUE;
}

void CGXHierGridWrapper::Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle)
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

	if(Grid()->IsPrinting())
		return;		// Printing logic will take care of printing children.

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

	// Restrict window within the visible parent rect.
	rect = GetCellRect(nRow, nCol, &rect, &style);
	m_pWnd->MoveWindow(rect, TRUE);
	m_pWnd->SetFont(&m_font);
	m_pWnd->Invalidate();
	m_pWnd->ShowWindow(SW_SHOW);

	if (nRow > Grid()->GetFrozenRows() && Grid()->GetTopRow() > nRow 
		|| nCol > Grid()->GetFrozenCols() && Grid()->GetLeftCol() > nCol)
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
/*	else
	{
		Hide();     // drawn area remains visible
		GridWnd()->ValidateRect(rect);
	}
*/

	// Avoid overdrawing with BitmapDC in CGXGridCore::OnDraw
	ExcludeClipRect(rect);

	// Unreferenced:
	pStandardStyle;
}

// HideChildWndInRect will hide the child windows if they intersect with rcHide(lParam).
// or if the child window is not in the visible area of the parent.
// Used as the callback function for EnumChildWindows, which gets called from HideChildGridsInRect
BOOL CALLBACK HideChildWndInRect(HWND hwnd,  LPARAM lParam)
{
	// Is this a child grid wnd?
	CGXGridWnd* pChildGrid = dynamic_cast<CGXGridWnd*>(CWnd::FromHandlePermanent(hwnd));
	if(!pChildGrid)
		return TRUE;

	// Get the WindowPlacement state.
	WINDOWPLACEMENT wndpl;
	UINT showCmd;
	// If the window is hidden don't worry about it.
	if(pChildGrid->GetWindowPlacement(&wndpl)
		&& wndpl.showCmd == SW_HIDE)
		return TRUE;

	showCmd = wndpl.showCmd;

	IGXHierarchyGrid* pChildAsHierarchy = dynamic_cast<IGXHierarchyGrid*>(pChildGrid);

	// If the child is in Show state but need not be, then hide it.
	if(showCmd == SW_SHOWNORMAL && !pChildAsHierarchy->m_gridParent->IsChildGridCellVisible(pChildAsHierarchy->m_nChildId))
	{
		pChildGrid->HideCaret();
		pChildGrid->MoveWindow0(FALSE);
		pChildGrid->ShowWindow(SW_HIDE);
		return TRUE;
	}

	if(!lParam)
		return TRUE;

	// Check if this window intersects with rcHide. Then hide it since it will get
	// redrawn if necessary.

	CRect* prcHide = (CRect*)lParam;
	CRect rcWndRect;
	pChildGrid->GetWindowRect(&rcWndRect);

	if(pChildAsHierarchy)
	{
		// Get the point just to the right of the frozen cols in the parent.
		CGXGridCore* pParent = dynamic_cast<CGXGridCore*>(pChildAsHierarchy->m_gridParent);
		int xRightOfFrozenCol = pParent->CalcSumOfColWidths(0, pParent->GetFrozenCols());
		xRightOfFrozenCol++;
		// Convert it to screen co-ords.
		CPoint ptRightOfFrozenCol(xRightOfFrozenCol, 0);
		pParent->GridWnd()->ClientToScreen(&ptRightOfFrozenCol);
		// Adjust the childs window rect co-ords.
		rcWndRect.left = ptRightOfFrozenCol.x;
	}

	CRect rcIntersect;
	// Check if the child grid intersects with the Hide-rect.
	if(rcIntersect.IntersectRect(prcHide, &rcWndRect))
	{
		// Yes, so hide the child grid.
		pChildGrid->HideCaret();
		pChildGrid->MoveWindow0(FALSE);
		pChildGrid->ShowWindow(SW_HIDE);
	}

	return TRUE;
}
