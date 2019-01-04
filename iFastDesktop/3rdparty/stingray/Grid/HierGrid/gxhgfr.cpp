///////////////////////////////////////////////////////////////////////////////
// gxhgfr.cpp : Implementation for Find/Replace in a Hierarchy Grid.
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

#ifdef _GXDLL
#undef AFXAPI_DATA
#define AFXAPI_DATA __based(__segname("_DATA"))
#endif

#ifndef GX_HGFRIMP_H
#include "grid\HierGrid\gxhgfr.h"
#endif

#ifndef _GX_HIERARCHY_GRID
#include "grid\HierGrid\gxhiergrid.h"
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_HGFR")
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

/*
template<class T>
void CGXHierarchyGrid<T>::ImplementHGFindReplace()
{
	if (m_pFindReplaceImp == NULL)
		AutoDeletePtr(m_pFindReplaceImp = new CGXHierarchyGridFindReplaceImp);
}

template void CGXHierarchyGrid<CGXGridWnd>::ImplementHGFindReplace();
template void CGXHierarchyGrid<CGXGridView>::ImplementHGFindReplace();
*/

BOOL CGXHierarchyGridFindReplaceImp::FindTextInChild(CGXGridCore* pGrid, ROWCOL nChildRow, BOOL bSetCell, BOOL bSetParent)
{
	IGXHierarchyGrid* pChildGrid = NULL;
	IGXHierarchyGrid* pHrGrid = dynamic_cast<IGXHierarchyGrid*>(pGrid);

	BOOL bFound = FALSE;

	// If visible, check child grid for a match.
	if( pHrGrid->IsChildShown(nChildRow) )
	{
		pChildGrid = pHrGrid->GetChildAt(nChildRow);

		if( pChildGrid )
		{
			ROWCOL nAbsRow, nAbsCol;
			bFound = dynamic_cast<CGXGridCore*>(pChildGrid)->FindText(bSetCell);
			// If found a match then set the parent's current cell to this child grid cell.
			if(bFound && bSetParent)
			{
				pHrGrid->GetAbsCellContainingChild(nChildRow, nAbsRow, nAbsCol);
				pGrid->SetCurrentCell(nAbsRow, nAbsCol, GX_NOSETFOCUS);
			}
		}
	}		
	return bFound;
}

void CGXHierarchyGridFindReplaceImp::ReplaceAllInChild(CGXGridCore* pGrid, ROWCOL nChildRow, LPCTSTR lpszFind, LPCTSTR lpszReplace, BOOL bCase)
{
	IGXHierarchyGrid* pChildGrid = NULL;
	IGXHierarchyGrid* pHrGrid = dynamic_cast<IGXHierarchyGrid*>(pGrid);

	// If visible call ReplaceAll on the child.
	if( pHrGrid->IsChildShown(nChildRow) )
	{
		pChildGrid = pHrGrid->GetChildAt(nChildRow);

		if( pChildGrid )
			dynamic_cast<CGXGridCore*>(pChildGrid)->OnReplaceAll(lpszFind, lpszReplace, bCase);
	}
}

BOOL CGXHierarchyGridFindReplaceImp::FindText(CGXGridCore* pGrid, ROWCOL& nRow, ROWCOL& nCol, BOOL bSetCell)
{
	//IGXHierarchyGrid* pChildGrid = NULL;
	IGXHierarchyGrid* pHrGrid = dynamic_cast<IGXHierarchyGrid*>(pGrid);
	ASSERT(pHrGrid != NULL);

	// Convert to logical row/col
	ROWCOL nLogRow, nLogCol, nAbsRow, nAbsCol;
	pHrGrid->GetLogCellFromAbsCell(nRow, nCol, nLogRow, nLogCol);
	if(nLogRow == GX_INVALID)
		return FALSE;
	
	GX_FR_STATE* pState = GXGetLastFRState();

	// If child is active (nLogCol == GX_INVALID)
	if(nLogCol == GX_INVALID )
	{
		// And a match found in the child, then just return TRUE
		if(FindTextInChild(pGrid, nLogRow, bSetCell, FALSE))
			return TRUE;

		// Else start searching the next rows.
		if(pState->bNext)
		{
			nLogRow++;
			nLogCol = 1;
		}
		else
			nLogCol = pHrGrid->GetLogColCount();
	}

	// search text in cells next to given coordinates (nRow, nCol)
	BOOL bFound = FALSE;

	while (nLogRow <= pHrGrid->GetLogRowCount() && nLogRow > 0)
	{
		CGXStyle* pStyle = pGrid->CreateStyle();


/*		else
*/
		{
			//Convert to absolute row/col
			pHrGrid->GetAbsCellFromLogCell(nLogRow, nLogCol, nAbsRow, nAbsCol);

			// check active cell or search next cell
			pGrid->ComposeStyleRowCol(nAbsRow, nAbsCol, pStyle);
			CGXControl* pControl = pGrid->GetRegisteredControl(pStyle->GetControl());
			ASSERT(pControl != 0);

			pState->m_pStyle = pStyle; // cache style object so that ReplaceAll can reuse it

			if (pStyle->GetEnabled() && pControl->FindText(*pState, nAbsRow, nAbsCol, FALSE, bSetCell))
				bFound = TRUE;
		}

		pState->m_pStyle = NULL;

		// free style object
		pGrid->RecycleStyle(pStyle);

		if (bFound)
			break;

		// Calc next cell to Find.
		nLogCol = nLogCol + (pState->bNext ? 1 : -1);
		if( pState->bNext )
		{
			if( nLogCol > pHrGrid->GetLogColCount() ) // Move to the first cell of next row
			{
				bFound = FindTextInChild(pGrid, nLogRow, bSetCell, TRUE);
				nLogRow++;
				nLogCol = 1;
			}
		}
		else
		{
			if( nLogCol <= 0 ) // Move to the last cell of previous row
			{
				nLogRow--;
				nLogCol = pHrGrid->GetLogColCount();
				bFound = FindTextInChild(pGrid, nLogRow, bSetCell, TRUE);
			}
		}
		if(bFound)
			break;
		pGrid->OnTestGridDimension(nAbsRow+1, 0);
	}

	return bFound;
}

BOOL CGXHierarchyGridFindReplaceImp::FindText(CGXGridCore* pGrid, BOOL bSetCell /*=TRUE*/)
{
	// Get the IGXHierarchyGrid interface from the grid.
	IGXHierarchyGrid* pHrGrid = dynamic_cast<IGXHierarchyGrid*>(pGrid);

	if(pHrGrid->GetLogRowCount() == 0 || pHrGrid->GetLogColCount() == 0)
		return FALSE;

	// active cell coordinates
	ROWCOL nRow, nCol;
	if (!pGrid->GetCurrentCell(nRow, nCol))
	{
		GX_FR_STATE* pState = GXGetLastFRState();

		// Get the logical top/left or bottom/right
		if(pState->bNext)
			pHrGrid->GetAbsCellFromLogCell(1, 1, nRow, nCol);
		else
			pHrGrid->GetAbsCellFromLogCell(pHrGrid->GetLogRowCount(), pHrGrid->GetLogColCount(), nRow, nCol);
	}

	ROWCOL nLogRow, nLogCol;
	
	// Convert to logical co-ords.
	pHrGrid->GetLogCellFromAbsCell(nRow, nCol, nLogRow, nLogCol);
	if(nLogRow == GX_INVALID)
		return FALSE;
	
	if( nLogCol == GX_INVALID )
		nLogCol = 1;

	((CFriendlyGridTemplate<CGXGridView>*)pGrid)->m_nFirstRow = nLogRow;

	BOOL bFound = FALSE;

	// Check if the current cell has a match.
	CGXControl* pControl = pGrid->GetControl(nRow, nCol);
	bFound = pControl->FindText(*GXGetLastFRState(), nRow, nCol, FALSE, bSetCell);

	// .... or search next cell
	if (!bFound)
		bFound = pGrid->FindText(nRow, nCol, bSetCell);

	// ... not found
	if (!bFound && bSetCell)
		pGrid->OnTextNotFound(GXGetLastFRState()->strFind);

	return bFound;
}

void CGXHierarchyGridFindReplaceImp::OnReplaceSel(CGXGridCore* pGrid, LPCTSTR lpszFind, BOOL bNext, BOOL bCase, LPCTSTR lpszReplace)
{
	// Get the IGXHierarchyGrid interface from the grid.
	IGXHierarchyGrid* pHrGrid = dynamic_cast<IGXHierarchyGrid*>(pGrid);

	if (pHrGrid->GetLogRowCount() == 0 || pHrGrid->GetLogColCount() == 0)
		return;

	GX_FR_STATE* pState = GXGetLastFRState();

	// active cell coordinates
	ROWCOL nRow, nCol;
	if (!pGrid->GetCurrentCell(nRow, nCol))
	{
		// Get the logical top/left or bottom/right
		if(pState->bNext)
			pHrGrid->GetAbsCellFromLogCell(1, 1, nRow, nCol);
		else
			pHrGrid->GetAbsCellFromLogCell(pHrGrid->GetLogRowCount(), pHrGrid->GetLogColCount(), nRow, nCol);
	}

	// initialize searchparameter structure
	pState->strFind = lpszFind;
	pState->strReplace = lpszReplace;
	pState->bCase = bCase;
	pState->bNext = bNext;
	pState->PrepareFindReplace();

	// Get the child grid if the current cell is the child-grid cell
	ROWCOL nLogRow, nLogCol;
	CGXGridCore* pChildGrid = NULL;
	pHrGrid->GetLogCellFromAbsCell(nRow, nCol, nLogRow, nLogCol);
	if(nLogRow != GX_INVALID && nLogCol == GX_INVALID )
		pChildGrid = dynamic_cast<CGXGridCore*>(pHrGrid->GetChildAt(nLogRow));

	CGXLongOperation theOp;

	((CFriendlyGridTemplate<CGXGridView>*)pGrid)->m_nFirstRow = nRow;

	// check active cell or search next cell
	BOOL bFound;
	
	if(!pChildGrid)
	{
		// Check the control.
		CGXControl* pControl = pGrid->GetControl(nRow, nCol);

		bFound = pControl->FindText(*pState, nRow, nCol, TRUE /* current pos */, TRUE /* do SetSel */);

		if (bFound)
			pControl->ReplaceSel(GXGetLastFRState()->strReplace);
		
		if (bFound && pControl->FindText(*pState, nRow, nCol, TRUE /* current pos */, FALSE /* do SetSel */))
			bFound = pControl->FindText(*pState, nRow, nCol, TRUE /* current pos */, TRUE /* do SetSel */);
		else
			bFound = FALSE;
	}
	else
	{
		// This is a child grid cell and so check the child grid.
		ROWCOL nCurRowBefore, nCurRowAfter, nCurColBefore, nCurColAfter;
		pChildGrid->GetCurrentCell(nCurRowBefore, nCurColBefore);
		pChildGrid->OnReplaceSel(lpszFind, bNext, bCase, lpszReplace);
		pChildGrid->GetCurrentCell(nCurRowAfter, nCurColAfter);
		// Decide if a next match was found based on the change in current cell
		bFound = (nCurRowBefore != nCurRowAfter) || (nCurColBefore != nCurColAfter);
	}
	
	if(!bFound)
		// .... or search next cell
		bFound = pGrid->FindText(nRow, nCol, TRUE /* set current cell */);

	// ... not found
	if (!bFound)
		pGrid->OnTextNotFound(pState->strFind);

#ifdef _UNICODE
	// Clean up non UNICODE text buffer
	delete[] pState->lpszMultiByteFindString;
	pState->lpszMultiByteFindString = NULL;
#endif
}

void CGXHierarchyGridFindReplaceImp::OnReplaceAll(CGXGridCore* pGrid, LPCTSTR lpszFind, LPCTSTR lpszReplace, BOOL bCase)
{
	IGXHierarchyGrid* pHrGrid = dynamic_cast<IGXHierarchyGrid*>(pGrid);
	ASSERT(pHrGrid != NULL);

	GX_FR_STATE* pState = GXGetLastFRState();

	if (pHrGrid->GetLogRowCount() == 0 || pHrGrid->GetLogColCount() == 0)
		return;

	// active cell coordinates
	ROWCOL nRow, nCol;
	if (!pGrid->GetCurrentCell(nRow, nCol))
	{
		GX_FR_STATE* pState = GXGetLastFRState();

		// Get the logical top/left or bottom/right
		if(pState->bNext)
			pHrGrid->GetAbsCellFromLogCell(1, 1, nRow, nCol);
		else
			pHrGrid->GetAbsCellFromLogCell(pHrGrid->GetLogRowCount(), pHrGrid->GetLogColCount(), nRow, nCol);
	}

	// Convert to logical row/col
	ROWCOL nLogRow, nLogCol;
	pHrGrid->GetLogCellFromAbsCell(nRow, nCol, nLogRow, nLogCol);
	if(nLogRow == GX_INVALID)
		return;
	
	// If child grid active then ReplaceAll in child grid first.
	if( nLogCol == GX_INVALID )
	{
		ReplaceAllInChild(pGrid, nLogRow, lpszFind, lpszReplace, bCase);
		nLogRow++;
		nLogCol = 1;
	}

	// initialize searchparameter structure
	pState->strFind = lpszFind;
	pState->strReplace = lpszReplace;
	pState->bCase = bCase;
	pState->bNext = TRUE;
	pState->PrepareFindReplace();

	CGXLongOperation theOp;
	theOp.SetStatusText(pGrid->m_pAppData->strmReplacingAll, FALSE);
	theOp.SetLockedState(TRUE);
	theOp.SetCanRollback(TRUE);

	if (pState->bTransaction)
		pGrid->BeginTrans(pGrid->m_pAppData->strmReplaceAll);
	((CFriendlyGridTemplate<CGXGridView>*)pGrid)->m_bCanceled = FALSE;

	// check active cell and replace

	((CFriendlyGridTemplate<CGXGridView>*)pGrid)->m_nFirstRow = nRow;

	ROWCOL dwStartRow = nRow;
	ROWCOL dwRowCount = nRow;
	ROWCOL dwRows = 0;

	BOOL bFound = FALSE;

	while (nLogRow <= pHrGrid->GetLogRowCount() && nLogRow >= 0)
	{
		dwRows++;
		if (theOp.NeedMessages())
		{
			if (pState->bNext)
				dwRowCount = pGrid->GetRowCount()-dwStartRow;
			theOp.SetPercentDone((int) (dwRows*100 / dwRowCount));
			theOp.DoMessages(((CFriendlyGridTemplate<CGXGridView>*)pGrid)->m_bCanceled);
			if (((CFriendlyGridTemplate<CGXGridView>*)pGrid)->m_bCanceled)
				break;
		}

		//Convert to absolute row/col
		ROWCOL nAbsRow, nAbsCol;
		pHrGrid->GetAbsCellFromLogCell(nLogRow, nLogCol, nAbsRow, nAbsCol);

		CGXStyle* pStyle = pGrid->CreateStyle();
		pGrid->ComposeStyleRowCol(nAbsRow, nAbsCol, pStyle);
		CGXControl* pControl = pGrid->GetRegisteredControl(pStyle->GetControl());
		ASSERT(pControl != 0);

		pState->m_pStyle = pStyle; // cache style object so that ReplaceAll can resuse it

		if (pControl->ReplaceAll(*pState, nAbsRow, nAbsCol))
			bFound = TRUE;

		pState->m_pStyle = NULL;

		// free style object
		pGrid->RecycleStyle(pStyle);

		// Calc next cell to Find.
		nLogCol = nLogCol + (pState->bNext ? 1 : -1);
		if( pState->bNext )
		{
			if( nLogCol > pHrGrid->GetLogColCount() ) // Move to the first cell of next row
			{
				// Check the child in this row before moving to the next row.
				ReplaceAllInChild(pGrid, nLogRow, lpszFind, lpszReplace, bCase);
				nLogRow++;
				nLogCol = 1;
			}
		}
		else
		{
			if( nLogCol <= 0 ) // Move to the last cell of previous row
			{
				nLogRow--;
				nLogCol = pHrGrid->GetLogColCount();
				// First check the child in the previous row.
				ReplaceAllInChild(pGrid, nLogRow, lpszFind, lpszReplace, bCase);
			}
		}

		pGrid->OnTestGridDimension(nAbsRow+1, 0);
	}

	theOp.SetPercentDone(-1);
	theOp.SetLockedState(FALSE);

	if (((CFriendlyGridTemplate<CGXGridView>*)pGrid)->m_bCanceled && !pState->bTransaction)
	{
		AfxThrowUserException();
	}
	else if (((CFriendlyGridTemplate<CGXGridView>*)pGrid)->m_bCanceled && theOp.GetRollbackConfirmedState())
	{
		if (pState->bTransaction)
			pGrid->Rollback();
	}
	else
	{
		if (!bFound)
			pGrid->OnTextNotFound(GXGetLastFRState()->strFind);

		if (pState->bTransaction)
			pGrid->CommitTrans();
	}

	pGrid->RefreshViews();

#ifdef _UNICODE
	// Clean up non UNICODE text buffer
	delete[] pState->lpszMultiByteFindString;
	pState->lpszMultiByteFindString = NULL;
#endif
}

// Overriden to prevent calling OnFindReplace on the child grid.
void CGXHierarchyGridFindReplaceImp::OnFindReplace(CGXGridCore* pGrid, CFindReplaceDialog* pDialog)
{
	GX_FR_STATE* pState = GXGetLastFRState();

	ASSERT(pDialog != NULL);
	ASSERT(pDialog == GXGetLastFRState()->pFindReplaceDlg);

/*	if (pState->m_pActiveGrid != pGrid)
	{
		// delegate to active grid view
		pState->m_pActiveGrid->OnFindReplace(pDialog);
		return;
	}
*/
	if (pDialog->IsTerminating())
	{
		pState->pFindReplaceDlg = NULL;
	}
	else if (pDialog->FindNext())
	{
		pGrid->OnFindNext(pDialog->GetFindString(),
			pDialog->SearchDown(), pDialog->MatchCase());
	}
	else if (pDialog->ReplaceCurrent())
	{
		ASSERT(!pState->bFindOnly);
		pGrid->OnReplaceSel(pDialog->GetFindString(),
			pDialog->SearchDown(), pDialog->MatchCase(),
			pDialog->GetReplaceString());
	}
	else if (pDialog->ReplaceAll())
	{
		pState->bTransaction = TRUE;
			// Programmer should set this variable = FALSE if he
			// wants to handle his own transaction-like mechanism.
			// E.g. CGXDaoGrid and CGXODBCGrid override OnReplaceAll
			// and set pState->bTransaction = FALSE.
		ASSERT(!pState->bFindOnly);
		pGrid->OnReplaceAll(pDialog->GetFindString(), pDialog->GetReplaceString(),
			pDialog->MatchCase());
	}
}

