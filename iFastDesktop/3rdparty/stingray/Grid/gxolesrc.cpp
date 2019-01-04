///////////////////////////////////////////////////////////////////////////////
// gxolesrc.cpp : implementation of the OLE Drop Source
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
// Authors: Daniel Jebaraj, Stefan Hoenig
//

#define _OG_EXPORT_IMPL

#include "stdafx.h"

// compile this file only if OLE is supported
#if _MFC_VER >= 0x0400 && !defined(_AFX_NO_OLE_SUPPORT)

// Headers

#ifndef _GXOLE_H_
#include "grid\gxole.h"
#endif

#include <afxpriv.h>

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXOLESRC")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

#define new DEBUG_NEW

/////////////////////////////////////////////////////////////////////////////

BOOL CGXGridCore::EnableOleDataSource(DWORD dwFlags)
{
	delete m_pOleDataSourceProxy;
	m_pOleDataSourceProxy = NULL;

	m_nDndFlags = dwFlags;
	m_nClipboardFlags = dwFlags; // sync clipboard options
	
	if ( dwFlags == GX_DNDDISABLED )
		m_bHitTestSelEdge = FALSE;
	else
		m_bHitTestSelEdge = TRUE;

	m_pOleDataSourceProxy = new CGXOleDataSourceProxy;
	return m_pOleDataSourceProxy != NULL;
}

/////////////////////////////////////////////////////////////////////////////
// CGXOleDataSourceProxy
//

CGXOleDataSourceProxy::CGXOleDataSourceProxy(COleDataSource* pDataSource, BOOL bAutoDelete)
{
	if (pDataSource)
	{
		m_pDataSource = pDataSource;
		m_bAutoDelete = bAutoDelete;
	}
	else
	{
		m_pDataSource = new COleDataSource;
		m_bAutoDelete = TRUE;
	}
}

CGXOleDataSourceProxy::~CGXOleDataSourceProxy()
{
	if (m_bAutoDelete)
		delete m_pDataSource;
}

// CacheData & DelayRenderData operations similar to ::SetClipboardData
void CGXOleDataSourceProxy::CacheGlobalData(CLIPFORMAT cfFormat, HGLOBAL hGlobal,
		LPFORMATETC lpFormatEtc)
{
	m_pDataSource->CacheGlobalData(cfFormat, hGlobal, lpFormatEtc);
}

// Clipboard and Drag/Drop access
DROPEFFECT CGXOleDataSourceProxy::DoDragDrop(DWORD dwEffects,
		LPCRECT lpRectStartDrag, COleDropSource* pDropSource)
{
	return m_pDataSource->DoDragDrop(dwEffects, lpRectStartDrag, pDropSource);
}

// empty cache (similar to ::EmptyClipboard)
void CGXOleDataSourceProxy::Empty()
{
	m_pDataSource->Empty();
}

COleDataSource* CGXOleDataSourceProxy::GetOleDataSource() const
{ 
	return m_pDataSource; 
}


/////////////////////////////////////////////////////////////////////////////

// OnDndCacheGlobalData
//
// Override this method if you do not want to drag
// control values and style values.
//
// For example, you may wish not to load in the base styles
// when you call CopyCellsToArchive.

BOOL CGXOleDataSourceProxy::OnDndCacheGlobalData(CGXGridCore* pGrid, CGXNoOleDataSourceProxy* pSrcItem, const CGXRangeList& selList, ROWCOL& nDndRowExt, ROWCOL& nDndColExt)
{
	BOOL bText = pGrid->m_nDndFlags & GX_DNDTEXT;
	BOOL bStyles = pGrid->m_nDndFlags & GX_DNDSTYLES;
	BOOL bRetVal = FALSE;

	CGXGridParam* pParam = pGrid->GetParam();

	// Copy text
	if (bText)
	{
		CString s;
		HGLOBAL hTextData = 0;

		CSharedFile clipb (GMEM_MOVEABLE|GMEM_DDESHARE|GMEM_ZEROINIT);

		ROWCOL nRow, nCol;
		BOOL bCCell = pGrid->GetCurrentCell(nRow, nCol);

		if (selList.GetCount() == 1 && bCCell && *selList.GetHead() == CGXRange(nRow, nCol)
			&& pGrid->IsActiveCurrentCell() && pGrid->GetCurrentCellControl()->GetSelectedText(s)
			&& !s.IsEmpty())
		{
			clipb.Write(s, s.GetLength()*sizeof(TCHAR));
			hTextData = clipb.Detach();
			bStyles = FALSE;
			pGrid->m_nRowsCopied = 1;
			pGrid->m_nColsCopied = 1;

			// mark this attribute if selected text from an edit control is dragged
			pParam->m_bDndCurrentCellText = TRUE;
			pParam->m_pDndCurrentCellControl = pGrid->GetCurrentCellControl();
		}
		else if (pGrid->CopyTextToFile(clipb, selList))
			hTextData = clipb.Detach();

		if (hTextData)
		{
#ifdef _UNICODE
			pSrcItem->CacheGlobalData(CF_UNICODETEXT, hTextData);
#else
			pSrcItem->CacheGlobalData(CF_TEXT, hTextData);
#endif

			// CopyTextToFile stores dimension in m_nRowsCopied and m_nColsCopied
			nDndRowExt = pGrid->m_nRowsCopied;
			nDndColExt = pGrid->m_nColsCopied;
			bRetVal = TRUE;
		}
	}

	// Copy styles
	if (bStyles)
	{
		HGLOBAL hStylesData = 0;

		CSharedFile clipb (GMEM_MOVEABLE|GMEM_DDESHARE|GMEM_ZEROINIT);
		CArchive ar(&clipb, CArchive::store);

		BOOL bSuccess = pGrid->CopyCellsToArchive(ar, selList, (BOOL) (pGrid->m_nDndFlags & GX_DNDCOMPOSE));

		ar.Close();

		if (bSuccess)
		{
			hStylesData = clipb.Detach();

			ASSERT(pGrid->m_pAppData->m_uiStylesClipboardFormat <= USHRT_MAX);
			pSrcItem->CacheGlobalData((USHORT) pGrid->m_pAppData->m_uiStylesClipboardFormat, hStylesData);

			// CopyCellsToArchive stores dimension in m_nRowsCopied and m_nColsCopied
			nDndRowExt = pGrid->m_nRowsCopied;
			nDndColExt = pGrid->m_nColsCopied;
			bRetVal = TRUE;
		}
	}

	return bRetVal;
}

BOOL CGXOleDataSourceProxy::DndStartDragDrop(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol)
{
	// if there are no cells selected,
	// copy the current cell's coordinates
	CGXRangeList selList;
	DROPEFFECT dropEffect;

	CGXGridParam* pParam = pGrid->GetParam();

	// if user did click into a selected cell (or current cell), start OLE drag&drop
	if (pGrid->CopyRangeList(selList, TRUE) && selList.IsCellInList(nRow, nCol))
	{
		BOOL bMulti = pGrid->m_nDndFlags & GX_DNDMULTI;

		CGXRange range;
		if (!bMulti)
		{
			// Build up a single-range list
			range = selList.GetAt(selList.FindRange(nRow, nCol));
			selList.DeleteAll();
			selList.AddTail(new CGXRange(range));
		}

		pParam->m_nDndForceDropCol = GX_MAXROWCOL;
		pParam->m_nDndForceDropRow = GX_MAXROWCOL;

		// check if we should exclude headers
		ROWCOL nFirstRow = 0;
		ROWCOL nFirstCol = 0;

		if ((pGrid->m_nDndFlags & GX_DNDROWHEADER) == 0)
			nFirstCol = pGrid->GetHeaderCols()+1;

		if ((pGrid->m_nDndFlags & GX_DNDCOLHEADER) == 0)
			nFirstRow = pGrid->GetHeaderRows()+1;

		// loop through all selected ranges and expand them.
		// row and column headers will be excluded from expanded range.
		POSITION pos = selList.GetHeadPosition( );
		CGXRange* pRange = NULL;
		while (pos)
		{
			pRange = selList.GetNext(pos);

			// if a whole row or column is dragged, allow
			// it only to paste it as a whole row or column
			// if pasted into the same grid.
			if (pRange->IsTable())
			{
				pParam->m_nDndForceDropCol = nFirstCol;
				pParam->m_nDndForceDropRow = nFirstRow;
			}
			else if (pRange->IsRows())
			{
				pParam->m_nDndForceDropCol = nFirstCol;
			}
			else if (pRange->IsCols())
			{
				pParam->m_nDndForceDropRow = nFirstRow;
			}

			pRange->ExpandRange(nFirstRow,
					nFirstCol,
					pGrid->GetRowCount(),
					pGrid->GetColCount());
		}

		pGrid->m_bLockCurrentCell = TRUE;     // make sure current cell does not get deactivated

		pParam->m_bDndCurrentCellText = FALSE;
		pParam->m_pDndCurrentCellControl = NULL;

		// Copy data to the OLE data source object
		pGrid->OnDndCacheGlobalData(this, selList, pGrid->m_nDndRowsCopied, pGrid->m_nDndColsCopied);

		// Store settings in parameter object so that when the
		// user drops data into a different grid window
		// which is bound to the same parameter object can use
		// this information.

		pParam->m_bDndSource = TRUE;
		pParam->m_pDndSelList = &selList;
		pParam->m_nDndStartRow = min(pParam->m_nDndForceDropRow, max(nRow, nFirstRow));
		pParam->m_nDndStartCol = min(pParam->m_nDndForceDropCol, max(nCol, nFirstCol));
		if (selList.GetCount() == 1 && pRange)
		{
			// Adjust start row/col to avoid that when
			// the programmer selects a range of cells and
			// drags the cells by selecting the lower right corner
			// of the range that this corner becomes the upper left corner.
			pParam->m_nDndRowOffset = max(pParam->m_nDndStartRow, pRange->top) - pRange->top;
			pParam->m_nDndColOffset = max(pParam->m_nDndStartCol, pRange->left)- pRange->left;
			pParam->m_nDndStartRow = min(pParam->m_nDndStartRow, pRange->top);
			pParam->m_nDndStartCol = min(pParam->m_nDndStartCol, pRange->left);
		}
		else
		{
			pParam->m_nDndRowOffset = 0;
			pParam->m_nDndColOffset = 0;
		}

		// Show a drop cursor as soon as the user drags out
		// of the current cell
		CRect rect = pGrid->CalcRectFromRowColEx(nRow, nCol);
		pGrid->m_pGridWnd->ClientToScreen(&rect);

		// initiallize static member
		pGrid->m_bDndGridSource = TRUE; // data source is a CGXGridCore grid

		// Initialize auto-scrolling outside the source window
		if (pGrid->m_dwDndDropTargetFlags & GX_DNDAUTOSCROLL)
		{
			pGrid->m_bDndGlobalTimer = TRUE; // this window has its own timer
				// which exists until the end of the drag&drop operation.

			pGrid->m_pGridWnd->SetTimer(GX_TIMER_DNDSCROLLSELF, 25, NULL);
		}

		// Start the drag&drop operation
		dropEffect = this->DoDragDrop(DROPEFFECT_COPY|DROPEFFECT_MOVE, rect);

		// Remove selected cells if move operation
		if ((dropEffect & DROPEFFECT_MOVE) == DROPEFFECT_MOVE)
			DndStartDragDropMove(pGrid, selList);

		// Clean up OLE object
		this->Empty();

		// kill timer for this window
		if (pGrid->m_bDndGlobalTimer)
		{
			pGrid->m_pGridWnd->KillTimer(GX_TIMER_DNDSCROLLSELF);
			pGrid->m_bDndGlobalTimer = FALSE;
		}

		// Reset static member
		pGrid->m_bDndGlobalTimer = FALSE;
		pGrid->m_bDndGridSource = FALSE;

		// Reset settings in parameter object
		pParam->m_bDndSource = FALSE;
		pParam->m_nDndStartRow = 0;
		pParam->m_nDndStartCol = 0;
		pParam->m_pDndSelList = NULL;
		pParam->m_bDndCurrentCellText = FALSE;
		pParam->m_pDndCurrentCellControl = NULL;
		pGrid->m_bLockCurrentCell = FALSE;

		return TRUE; // no further processing in grid
	}

	return FALSE;
}

void CGXOleDataSourceProxy::DndStartDragDropMove(CGXGridCore* pGrid, CGXRangeList &selList)
{
	CGXGridParam* pParam = pGrid->GetParam();
	// m_bDndCurrentCellText is set in OnDndCacheGlobalData when
	// selected text from the current cell is copied to clipboard
	if (pParam->m_bDndCurrentCellText)
	{
		pGrid->BeginTrans(pGrid->m_pAppData->strmCutData);
		CGXControl *pCtrl = pParam->m_pDndCurrentCellControl;
		if (pCtrl->IsActive() && !pGrid->IsReadOnly() && !pCtrl->IsReadOnly())
			pCtrl->ReplaceSel(_T(""));
		pGrid->TransferCurrentCell();
		pGrid->CommitTrans();
	}
	else
		pGrid->ClearCells(selList, FALSE);
}
/////////////////////////////////////////////////////////////////////////////

#endif // ndef _AFX_NO_OLE_SUPPORT
