///////////////////////////////////////////////////////////////////////////////
// gxoledrg.cpp : implementation of the CGXGridDropTarget class
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
#pragma code_seg("GX_SEG_GXOLEDRG")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(CGXGridDropTargetPlugin, CGXPluginComponent)

/////////////////////////////////////////////////////////////////////////////
// CGXGridDropTarget
//

CGXGridDropTarget::CGXGridDropTarget()
{
	m_pGrid = NULL;
}

CGXGridDropTarget::~CGXGridDropTarget()
{
	Revoke();
}

/////////////////////////////////////////////////////////////////////////////
// registration

BOOL CGXGridDropTarget::Register(CGXGridCore* pGrid, DWORD dwFlags)
{
	// If the window is derived with multiple inheritance
	// from CGXGridCore and CWnd, pGrid should be the
	// same as pWnd.

	if (m_pGrid != NULL)
		return FALSE;

	ASSERT(pGrid);
	CWnd* pWnd = pGrid->GridWnd();

	// Make sure we do now have valid objects
	// derived from CGXGridCore and CWnd

	// ASSERT(dynamic_cast<CGXGridCore*>(pGrid));
	// ASSERT(dynamic_cast<CWnd*>(pWnd));

	ASSERT(pWnd->IsKindOf(RUNTIME_CLASS(CWnd)));

	m_pGrid = pGrid;

	if (m_pGrid == 0 || pWnd == 0)
		return FALSE;

	if (m_pGrid->m_pRegDropTarget != NULL)
	{
		ASSERT(0);
		// ASSERTION-> Grid already register as drop target. Don't
		// call both CGXGridDropTarget::Register and 
		// CGXGridCore::EnableOleDropTarget. Calling 
		// CGXGridCore::EnableOleDropTarget is already sufficient
		return FALSE;
	}

	// initialize metrics for drag-scrolling
	// in CGXGridCore

	m_pGrid->m_dwDndDropTargetFlags = dwFlags;
	m_pGrid->m_nDndScrollInset = nScrollInset;
	m_pGrid->m_nDndScrollDelay = nScrollDelay;
	m_pGrid->m_nDndScrollInterval = nScrollInterval;
	m_pGrid->m_nDndOutOfWndDelay = nScrollDelay*7;
	m_pGrid->m_nDndOufOfWndHorzScrollBy = 1;
	m_pGrid->m_nDndOufOfWndVertScrollBy = 1;
	m_pGrid->m_dwDndLastTick = 0;
	m_pGrid->m_pRegDropTarget = this;

	if (m_pGrid->m_pOleDropTargetImp == NULL)
	{
		CGXGridDropTargetPlugin* pTargetImp = new CGXGridDropTargetPlugin(pGrid);
		m_pGrid->m_pOleDropTargetImp = pTargetImp;
		m_pGrid->AddPlugin(pTargetImp);
	}

	// call default registration for CWnd controls
	BOOL b = COleDropTarget::Register(pWnd);

	return b;
}

/////////////////////////////////////////////////////////////////////////////
// default implementation of drag/drop scrolling

DROPEFFECT CGXGridDropTarget::OnDragScroll(CWnd*, DWORD dwKeyState,
	CPoint point)
{
	ASSERT_VALID(this);

	// delegate to CGXGridCore
	return m_pGrid->OnGridDragScroll(dwKeyState, point);
}

/////////////////////////////////////////////////////////////////////////////
// CGXGridDropTarget drop/ drop query handling

DROPEFFECT CGXGridDropTarget::OnDragEnter(CWnd*, COleDataObject* pDataObject,
	DWORD dwKeyState, CPoint point)
{
	ASSERT_VALID(this);

	// delegate to CGXGridCore
	CGXOleDataObjectProxy dataObject(pDataObject);
	return m_pGrid->OnGridDragEnter(&dataObject, dwKeyState, point);
}

DROPEFFECT CGXGridDropTarget::OnDragOver(CWnd*, COleDataObject* pDataObject,
	DWORD dwKeyState, CPoint point)
{
	ASSERT_VALID(this);

	// delegate to CGXGridCore
	CGXOleDataObjectProxy dataObject(pDataObject);
	return m_pGrid->OnGridDragOver(&dataObject, dwKeyState, point);
}

BOOL CGXGridDropTarget::OnDrop(CWnd*, COleDataObject* pDataObject,
	DROPEFFECT dropEffect, CPoint point)
{
	ASSERT_VALID(this);

	// delegate to CGXGridCore
	CGXOleDataObjectProxy dataObject(pDataObject);
	return m_pGrid->OnGridDrop(&dataObject, dropEffect, point);
}

DROPEFFECT CGXGridDropTarget::OnDropEx(CWnd*, COleDataObject* pDataObject,
	DROPEFFECT dropEffect, DROPEFFECT dropEffectList, CPoint point)
{
	ASSERT_VALID(this);

	// delegate to CGXGridCore
	CGXOleDataObjectProxy dataObject(pDataObject);
	return m_pGrid->OnGridDropEx(&dataObject, dropEffect, dropEffectList, point);
}

void CGXGridDropTarget::OnDragLeave(CWnd*)
{
	ASSERT_VALID(this);

	// delegate to CGXGridCore
	m_pGrid->OnGridDragLeave();
}

/////////////////////////////////////////////////////////////////////////////
// CGXGridDropTarget diagnostics

#ifdef _DEBUG
void CGXGridDropTarget::AssertValid() const
{
	COleDropTarget::AssertValid();
}

void CGXGridDropTarget::Dump(CDumpContext& dc) const
{
	COleDropTarget::Dump(dc);
}
#endif

/////////////////////////////////////////////////////////////////////////////
// CGXOleDataObjectProxy
//

CGXOleDataObjectProxy::CGXOleDataObjectProxy(COleDataObject* pDataObject, BOOL bAutoDelete)
{
	if (pDataObject)
	{
		m_pDataObject = pDataObject;
		m_bAutoDelete = bAutoDelete;
	}
	else
	{
		m_pDataObject = new COleDataObject;
		m_bAutoDelete = TRUE;
	}
}

CGXOleDataObjectProxy::~CGXOleDataObjectProxy()
{
	if (m_bAutoDelete)
		delete m_pDataObject;
}

BOOL CGXOleDataObjectProxy::GetData(CLIPFORMAT cfFormat, LPSTGMEDIUM lpStgMedium, LPFORMATETC lpFormatEtc)
{
	return m_pDataObject->GetData(cfFormat, lpStgMedium, lpFormatEtc);
}

BOOL CGXOleDataObjectProxy::IsDataAvailable(CLIPFORMAT cfFormat, LPFORMATETC lpFormatEtc)
{
	return m_pDataObject->IsDataAvailable(cfFormat, lpFormatEtc);
}

COleDataObject* CGXOleDataObjectProxy::GetOleDataObject() const
{ 
	return m_pDataObject; 
}

/////////////////////////////////////////////////////////////////////////////
// CGXGridCore drag/drop support

// Grid implementation for drop target

void CGXGridCore::EnableOleDropTarget(DWORD dwFlags)
{
	CGXGridDropTargetPlugin* p = new CGXGridDropTargetPlugin(this);
	AddPlugin(p);
	m_pOleDropTargetImp = p;
	if (dwFlags)
		m_dwDndDropTargetFlags = dwFlags;
}

CGXGridDropTargetPlugin::CGXGridDropTargetPlugin(CGXGridCore* pGrid)
{
	m_pGrid = pGrid;
	m_pobjDndDropTarget = NULL;
}

CGXGridDropTargetPlugin::~CGXGridDropTargetPlugin()
{
	delete m_pobjDndDropTarget;
}

BOOL CGXGridDropTargetPlugin::PlugIn(CWnd* pParentWnd)
{
	if (pParentWnd && m_pGrid->m_pRegDropTarget == NULL)
	{
		m_pobjDndDropTarget = new CGXGridDropTarget();
		m_pobjDndDropTarget->Register(m_pGrid, m_pGrid->m_dwDndDropTargetFlags);
	}

	return CGXPluginComponent::PlugIn(pParentWnd);
}

DROPEFFECT CGXGridDropTargetPlugin::OnGridDragScroll(CGXGridCore* pGrid, DWORD dwKeyState, CPoint /*point*/)
{
	if (pGrid->m_nDndDropeffect)
		return pGrid->m_nDndDropeffect;

	DROPEFFECT dropEffect;

	// check for force copy
#ifndef _MAC
	if ((dwKeyState & MK_CONTROL) == MK_CONTROL)
#else
	if ((dwKeyState & MK_OPTION) == MK_OPTION)
#endif
		dropEffect = DROPEFFECT_COPY; // copy data
	else
		dropEffect = DROPEFFECT_MOVE; // move data

	// some other keys return default
	return dropEffect;
}

DROPEFFECT CGXGridDropTargetPlugin::OnGridDragEnter(CGXGridCore* pGrid, CGXNoOleDataObjectProxy* pDataObject,
	DWORD dwKeyState, CPoint point)
{
	// TRACE("OnGridDragEnter\n");
	if (!pGrid->OnDndQueryAcceptData(pDataObject))
	{
		pGrid->m_nDndDropeffect = DROPEFFECT_SCROLL;
		return DROPEFFECT_NONE;
	}

	pGrid->m_nDndDropeffect = 0;

	if (!pGrid->IsActiveFrame() && pGrid->m_pGridWnd->IsKindOf(RUNTIME_CLASS(CView)))
	{
		CMDIChildWnd* pFrame = ((CMDIChildWnd*)pGrid->m_pGridWnd->GetParentFrame());
		if (pFrame && pFrame->IsKindOf(RUNTIME_CLASS(CMDIChildWnd)))
			pFrame->MDIActivate();
	}
	else
	{
		pGrid->m_pGridWnd->SetFocus();
	}

	// check if a CGXGridCore was the data source
	if (pGrid->m_bDndGridSource)
	{
		// reuse information from data source
		pGrid->m_nDndRowExt = pGrid->m_nDndRowsCopied;
		pGrid->m_nDndColExt = pGrid->m_nDndColsCopied;
	}
	else
		// calculate the size of the focus rectangle
		pGrid->OnDndCalculateFocusRect(pDataObject, pGrid->m_nDndRowExt, pGrid->m_nDndColExt);

	if (pGrid->m_nDndRowExt == 0 || pGrid->m_nDndColExt == 0)
	{
		pGrid->m_nDndDropeffect = DROPEFFECT_SCROLL;
		return DROPEFFECT_NONE;
	}

	// OnGridDragEnter will start a timer. This timer will
	// be executed until the grid receives a OnGridDragLeave
	// or OnGridDragDrop message.

	// If the drop target is the same as the data source
	// no timer is needed because the data source holds
	// its own timer (see DndStartDragDrop).

	if (!pGrid->m_bDndGlobalTimer && pGrid->m_dwDndDropTargetFlags & GX_DNDEGDESCROLL)
		VERIFY(pGrid->m_pGridWnd->SetTimer(GX_TIMER_DNDSCROLLOTHER, 25, NULL));

			// OnGridDragOver shall draw rect
	DROPEFFECT dropEffect = pGrid->OnGridDragOver(pDataObject, dwKeyState, point);

	pGrid->m_nDndDropeffect = 0;

	return dropEffect;
}

DROPEFFECT CGXGridDropTargetPlugin::OnGridDragOver(CGXGridCore* pGrid, CGXNoOleDataObjectProxy* /*pDataObject*/,
	DWORD dwKeyState, CPoint point)
{
	if(!pGrid->GetGridRect().PtInRect(point))
		return DROPEFFECT_NONE;

	//  TRACE("OnGridDragOver\n");
	if (pGrid->m_nDndDropeffect)
		return pGrid->m_nDndDropeffect;

	// outline the cells which will be replaced
		 // if different from m_lastrect
		// erase old rect, draw new rect
	pGrid->DndDrawMoveRect(point, TRUE, TRUE);

	if (pGrid->m_nDndLastRow == GX_INVALID)
		return DROPEFFECT_NONE;

	// cursor to be shown
	DROPEFFECT dropEffect;

	// check for force copy
#ifndef _MAC
	if ((dwKeyState & MK_CONTROL) == MK_CONTROL)
#else
	if ((dwKeyState & MK_OPTION) == MK_OPTION)
#endif
		dropEffect = DROPEFFECT_COPY; // copy data
	else
		dropEffect = DROPEFFECT_MOVE; // move data

	// some other keys return default
	return dropEffect;
}

DROPEFFECT CGXGridDropTargetPlugin::OnGridDropEx(CGXGridCore* pGrid, CGXNoOleDataObjectProxy* /*pDataObject*/,
	DROPEFFECT /*dropEffect*/, DROPEFFECT /*dropEffectList*/, CPoint /*point*/)
{
	pGrid->m_nDndDropeffect = 0;

	return (DROPEFFECT)-1;  // not implemented
}

void CGXGridDropTargetPlugin::OnGridDragLeave(CGXGridCore* pGrid)
{
	// TRACE("OnGridDragLeave\n");

	// Kill the timer started in OnGridDragEnter.
	if (!pGrid->m_bDndGlobalTimer && pGrid->m_dwDndDropTargetFlags & GX_DNDEGDESCROLL)
		pGrid->m_pGridWnd->KillTimer(GX_TIMER_DNDSCROLLOTHER); // kill the timer

	// Erase the focus rectangle
	pGrid->DndDrawMoveRect(CPoint(0, 0), TRUE, FALSE);

	pGrid->m_nDndDropeffect = 0;
	pGrid->m_nDndRowExt = 0;
	pGrid->m_nDndColExt = 0;
}

BOOL CGXGridDropTargetPlugin::OnGridDrop(CGXGridCore* pGrid, CGXNoOleDataObjectProxy* pDataObject,
	DROPEFFECT dropEffect, CPoint point)
{
	if (pGrid->m_nDndRowExt == 0 || pGrid->m_nDndColExt == 0)
		return DROPEFFECT_NONE;

	if (pGrid->m_nDndLastRow == GX_INVALID)
		return DROPEFFECT_NONE;

	pGrid->m_nDndDropeffect = 0;

	// Kill the timer started in OnGridDragEnter.
	if (!pGrid->m_bDndGlobalTimer && pGrid->m_dwDndDropTargetFlags & GX_DNDEGDESCROLL)
		pGrid->m_pGridWnd->KillTimer(GX_TIMER_DNDSCROLLOTHER);

	// Erase the focus rectangle
	pGrid->DndDrawMoveRect(point, TRUE, FALSE);

	if (dropEffect == DROPEFFECT_NONE)
		return dropEffect;

	// check if the source grid is also the target grid
	// drop cell is the same as the start cell
	ROWCOL nRow, nCol;
	pGrid->HitTest(point, &nRow, &nCol);

	CGXGridParam* pParam = pGrid->GetParam();

	// Adjust row/col if cursor is on a header cell
	// and pasting data onto a header is not allowed
	// Also check if a whole row or column should be pasted
	ROWCOL nFirstCol = (pGrid->m_dwDndDropTargetFlags&GX_DNDROWHEADER) ? 0 : pGrid->GetHeaderCols()+1; 
	ROWCOL nFirstRow = (pGrid->m_dwDndDropTargetFlags&GX_DNDCOLHEADER) ? 0 : pGrid->GetHeaderRows()+1;

	if (pParam->m_bDndSource)
	{
		nRow = max(nRow, pParam->m_nDndRowOffset)-pParam->m_nDndRowOffset;
		nCol = max(nCol, pParam->m_nDndColOffset)-pParam->m_nDndColOffset;
		nRow = min(pParam->m_nDndForceDropRow, nRow);
		nCol = min(pParam->m_nDndForceDropCol, nCol);
	}

	nRow = max(nRow, nFirstRow);
	nCol = max(nCol, nFirstCol);

	if ((pGrid->m_dwDndDropTargetFlags & GX_DNDNOAPPENDROWS))
	{
		ROWCOL nLastRow = pGrid->GetRowCount() - pGrid->m_nDndRowExt + 1;
		nRow = min(nRow, nLastRow);
	}

	if ((pGrid->m_dwDndDropTargetFlags & GX_DNDNOAPPENDCOLS))
	{
		ROWCOL nLastCol = pGrid->GetColCount() - pGrid->m_nDndColExt + 1;
		nCol = min(nCol, nLastCol);
	}

	if (pParam->m_bDndSource)
	{
		if (pParam->m_nDndStartRow == nRow && pParam->m_nDndStartCol == nCol)
			return DROPEFFECT_NONE;

		pGrid->m_nDndDropeffect = dropEffect;

		if (pParam->m_bDirectDragDrop && !pParam->m_bDndCurrentCellText
			&& pParam->m_pDndSelList->GetCount() == 1)
		{
			// OnDndDropData will directly copy or move cells in sheet
			pGrid->OnDndDropData(pDataObject, nRow, nCol);
		}
		else
		{
			if ((dropEffect & DROPEFFECT_COPY) == DROPEFFECT_COPY)
				pGrid->BeginTrans(pGrid->m_pAppData->strmDragDropCopy);
			else
			{
				pGrid->BeginTrans(pGrid->m_pAppData->strmDragDropMove);

				// m_bDndCurrentCellText is set in OnDndCacheGlobalData when
				// selected text from the current cell is copied to clipboard
				if (pParam->m_bDndCurrentCellText)
				{
					CGXControl *pCtrl = pParam->m_pDndCurrentCellControl;
					if (pCtrl->IsActive() && !pGrid->IsReadOnly() && !pCtrl->IsReadOnly())
						pCtrl->ReplaceSel(_T(""));
					pGrid->TransferCurrentCell();
				}
				else
					// clear styles when we copied styles
					// if only text was copied, clear only the text from the cells
					pGrid->ClearCells(*pParam->m_pDndSelList,
						pGrid->m_nDndFlags & GX_DNDSTYLES
						&& pGrid->m_dwDndDropTargetFlags & GX_DNDSTYLES);

				// make sure calling function does not
				// call ClearCells again.
				dropEffect = DROPEFFECT_COPY;
			}

			BOOL bSuccess = pGrid->OnDndDropData(pDataObject, nRow, nCol);

			// Paste Data
			if (bSuccess)
			{
				pGrid->CommitTrans();
			}
			else
				pGrid->Rollback();
		}

		pGrid->m_nDndDropeffect = 0;

		// let DoDragSource return DROPEFFECT_NONE
		// so that grid does not clear cells again
		dropEffect = DROPEFFECT_NONE;
	}
	else
	{
		pGrid->m_nDndDropeffect = dropEffect;
		pGrid->OnDndDropData(pDataObject, nRow, nCol);
		pGrid->m_nDndDropeffect = 0;
	}

	pGrid->m_nDndRowExt = 0;
	pGrid->m_nDndColExt = 0;

	return dropEffect;
}


BOOL CGXGridDropTargetPlugin::OnDndDropData(CGXGridCore* pGrid, CGXNoOleDataObjectProxy* pDataObject, ROWCOL nRow, ROWCOL nCol)
{
	CGXGridParam* pParam = pGrid->GetParam();

	if (pParam->IsLockReadOnly() && pGrid->IsReadOnly())
		return FALSE;

	STGMEDIUM stgmedium;
	BOOL bSuccess = FALSE;

	if (pParam->m_bDndSource && pParam->m_bDirectDragDrop && !pParam->m_bDndCurrentCellText
		&& pParam->m_pDndSelList->GetCount() == 1)
	{
		CGXRange range = *pParam->m_pDndSelList->GetHead();
		if (pGrid->m_nDndDropeffect == DROPEFFECT_COPY)
			pGrid->CopyCells(range, nRow, nCol);
		else
			pGrid->MoveCells(range, nRow, nCol);

		bSuccess = TRUE;
	}

	ASSERT(pGrid->m_pAppData->m_uiStylesClipboardFormat <= USHRT_MAX);
	if (!bSuccess && (pGrid->m_dwDndDropTargetFlags & GX_DNDSTYLES) && pDataObject->GetData((USHORT) pGrid->m_pAppData->m_uiStylesClipboardFormat, &stgmedium))
	{
		// Open archive
		CSharedFile mf;
#ifndef _WINDU_SOURCE
		mf.SetHandle(stgmedium.hGlobal);
#else
		mf.SetHandle(stgmedium.u.hGlobal);
#endif
		CArchive ar(&mf, CArchive::load);

		bSuccess = pGrid->PasteCellsFromArchive(ar, CGXRange(nRow,nCol), TRUE);

		ar.Close();
		mf.Detach();
	}

#ifdef _UNICODE
	if (!bSuccess && (pGrid->m_dwDndDropTargetFlags & GX_DNDTEXT) && pDataObject->GetData(CF_UNICODETEXT, &stgmedium))
#else
	if (!bSuccess && (pGrid->m_dwDndDropTargetFlags & GX_DNDTEXT) && pDataObject->GetData(CF_TEXT, &stgmedium))
#endif
	{
#ifndef _WINDU_SOURCE
		HGLOBAL hGlobal = stgmedium.hGlobal;
#else
		HGLOBAL hGlobal = stgmedium.u.hGlobal;
#endif
		LPCTSTR pText = (LPCTSTR)GlobalLock(hGlobal);
		bSuccess = pGrid->PasteTextFromBuffer(pText, (DWORD)GlobalSize(hGlobal), CGXRange(nRow,nCol));

		// free memory
		GlobalUnlock(hGlobal);
		GlobalFree(hGlobal);
	}

	if (bSuccess)
	{
		pGrid->SetSelection(0);
		pGrid->SetCurrentCell(nRow, nCol);
		if (pGrid->m_nDndRowExt > 1 || pGrid->m_nDndColExt > 1)
		{
			ROWCOL nRowExt = min(nRow+pGrid->m_nDndRowExt-1, pGrid->GetRowCount());
			ROWCOL nColExt = min(nCol+pGrid->m_nDndColExt-1, pGrid->GetColCount());
			CGXRange range(nRow, nCol, nRowExt, nColExt);

			if (pParam->m_bDndSource)
			{
				// check if full rows or columns have been dragged
				if (pParam->m_nDndForceDropCol != GX_MAXROWCOL)
				{
					if (pParam->m_nDndForceDropRow != GX_MAXROWCOL)
						range.SetTable();
					else
						range.SetRows(nRow, nRowExt);
				}
				else if (pParam->m_nDndForceDropRow != GX_MAXROWCOL)
					range.SetCols(nCol, nColExt);
			}

			pGrid->SelectRange(range, TRUE);
		}
	}

	return bSuccess;
}

// Overridables for drop target

BOOL CGXGridDropTargetPlugin::OnDndQueryAcceptData(CGXGridCore* pGrid, CGXNoOleDataObjectProxy* pDataObject)
{
	BOOL bCanDrop = FALSE;

	if (pGrid->m_dwDndDropTargetFlags & GX_DNDTEXT)
	{
#ifdef _UNICODE
		bCanDrop = pDataObject->IsDataAvailable(CF_UNICODETEXT);
#else
		bCanDrop = pDataObject->IsDataAvailable(CF_TEXT);
#endif
	}

	if (pGrid->m_dwDndDropTargetFlags & GX_DNDSTYLES)
	{
		ASSERT(pGrid->m_pAppData->m_uiStylesClipboardFormat <= USHRT_MAX);
		bCanDrop |= pDataObject->IsDataAvailable((USHORT) pGrid->m_pAppData->m_uiStylesClipboardFormat);
	}

	return bCanDrop;
}

// Compute the no of columns and rows
BOOL CGXGridDropTargetPlugin::OnDndCalculateFocusRect(CGXGridCore* pGrid, CGXNoOleDataObjectProxy* pOleDataObjectProxy, ROWCOL& nRowExt, ROWCOL& nColExt)
{
	STGMEDIUM stgmedium;

	nRowExt = nColExt = 0;

	ASSERT(pGrid->m_pAppData->m_uiStylesClipboardFormat <= USHRT_MAX);
	if ((pGrid->m_dwDndDropTargetFlags & GX_DNDSTYLES) && pOleDataObjectProxy->GetData((USHORT) pGrid->m_pAppData->m_uiStylesClipboardFormat, &stgmedium))
	{
		// Open archive
		CSharedFile mf;
#ifndef _WINDU_SOURCE
		mf.SetHandle(stgmedium.hGlobal);
#else
		mf.SetHandle(stgmedium.u.hGlobal);
#endif
		CArchive ar(&mf, CArchive::load);

		// The first two values contain the dimension
		ar >> nRowExt;
		ar >> nColExt;

		// Close archive
		ar.Close();
		mf.Detach();

		return TRUE;
	}

#ifdef _UNICODE
	if ((pGrid->m_dwDndDropTargetFlags & GX_DNDTEXT) && pOleDataObjectProxy->GetData(CF_UNICODETEXT, &stgmedium))
#else
	if ((pGrid->m_dwDndDropTargetFlags & GX_DNDTEXT) && pOleDataObjectProxy->GetData(CF_TEXT, &stgmedium))
#endif
	{
#ifndef _WINDU_SOURCE
		HGLOBAL hGlobal = stgmedium.hGlobal;
#else
		HGLOBAL hGlobal = stgmedium.u.hGlobal;
#endif
		// If data are dragged from a rich edit window, the following
		// function will fail and return 0. The grid will therefore display
		// a no drop cursor when you drag selected text out of a RichText
		// cell.

		if (GlobalSize(hGlobal) > 0)
		{
			LPCTSTR pText = (LPCTSTR) GlobalLock(hGlobal);
			ASSERT(pText);

			pGrid->CalcBufferDimension(pText, (DWORD)GlobalSize(hGlobal), nRowExt, nColExt);
			GlobalUnlock(hGlobal);

			return TRUE;
		}
	}

	return FALSE;
}


void CGXGridDropTargetPlugin::DndDrawMoveRect(CGXGridCore* pGrid, CPoint point, BOOL bEraseOld, BOOL bDrawNew)
{
	if (pGrid->m_nDndRowExt == 0 || pGrid->m_nDndColExt == 0)
		return; // invalid area

	CGXGridParam* pParam = pGrid->GetParam();

	// if both parameters are FALSE, simply invalidate the rect
	if (!bEraseOld && !bDrawNew && !pGrid->m_DndLastRect.IsRectEmpty())
	{
		InvalidateRect(pGrid->m_DndLastRect);
		UpdateWindow();
		pGrid->m_DndLastRect.SetRectEmpty();
	}

	// If there is no old rectangle, we can't erase it
	if (bEraseOld && !bDrawNew && pGrid->m_DndLastRect.IsRectEmpty())
		return;

	// Determine top-left row/col for rectangle
	ROWCOL nRow, nCol;
	pGrid->HitTest(point, &nRow, &nCol);

	if (/*ht == GX_NOHIT 
		||*/ nRow == GX_INVALID || nRow > pGrid->GetRowCount() && (pGrid->m_dwDndDropTargetFlags & GX_DNDNOAPPENDROWS) != 0
		|| nCol ==  GX_INVALID || nCol > pGrid->GetColCount() && (pGrid->m_dwDndDropTargetFlags & GX_DNDNOAPPENDCOLS) != 0)
	{
		nRow = nCol = GX_INVALID;
		bDrawNew = FALSE;
	}
	else
	{
		// Adjust row/col if cursor is on a header cell
		// and pasting data onto a header is not allowed
		// Also check if a whole row or column should be pasted
		ROWCOL nFirstCol = (pGrid->m_dwDndDropTargetFlags&GX_DNDROWHEADER) ? 0 : pGrid->GetHeaderCols()+1; 
	    ROWCOL nFirstRow = (pGrid->m_dwDndDropTargetFlags&GX_DNDCOLHEADER) ? 0 : pGrid->GetHeaderRows()+1;

		if (pParam->m_bDndSource)
		{
			nRow = max(nRow, pParam->m_nDndRowOffset)-pParam->m_nDndRowOffset;
			nCol = max(nCol, pParam->m_nDndColOffset)-pParam->m_nDndColOffset;
			nRow = min(pParam->m_nDndForceDropRow, nRow);
			nCol = min(pParam->m_nDndForceDropCol, nCol);
		}

		nRow = max(nRow, nFirstRow);
		nCol = max(nCol, nFirstCol);

		if (pGrid->m_dwDndDropTargetFlags & GX_DNDNOAPPENDROWS)
		{
			ROWCOL nLastRow = pGrid->GetRowCount() - pGrid->m_nDndRowExt + 1;
			nRow = min(nRow, nLastRow);
		}

		if (pGrid->m_dwDndDropTargetFlags & GX_DNDNOAPPENDCOLS)
		{
			ROWCOL nLastCol = pGrid->GetColCount() - pGrid->m_nDndColExt + 1;
			nCol = min(nCol, nLastCol);
		}
	}

	// If rectangle is already drawn at this row/col, there is no need to draw it again
	if (bEraseOld && bDrawNew
		&& nRow == pGrid->m_nDndLastRow && nCol == pGrid->m_nDndLastCol
		&& !pGrid->m_DndLastRect.IsRectEmpty())
		return;

	bEraseOld &= !pGrid->m_DndLastRect.IsRectEmpty();
	bDrawNew &= nRow != pGrid->m_nDndLastRow || nCol != pGrid->m_nDndLastCol || pGrid->m_DndLastRect.IsRectEmpty();

	if (!bEraseOld && !bDrawNew)
		return; // nothing to do

	// TRACE("DndDrawMoveRect(bEraseOld = %d, bDrawNew= %d)\n", bEraseOld, bDrawNew);

	CClientDC dc(pGrid->m_pGridWnd);
	pGrid->OnGridPrepareDC(&dc);
	dc.IntersectClipRect(pGrid->GetGridRect());

	if (bEraseOld)
	{
		if (!pGrid->m_DndLastRect.IsRectEmpty())
		{
			dc.DrawFocusRect(pGrid->m_DndLastRect);
			pGrid->m_DndLastRect.top++;
			pGrid->m_DndLastRect.left++;
			pGrid->m_DndLastRect.right--;
			pGrid->m_DndLastRect.bottom--;
			dc.DrawFocusRect(pGrid->m_DndLastRect);
		}

		pGrid->m_DndLastRect.SetRectEmpty();
		pGrid->m_nDndLastRow = GX_INVALID;
		pGrid->m_nDndLastCol = GX_INVALID;
	}

	if (bDrawNew)
	{
		// check here if the bounds have been set
		ROWCOL nDndRowBounds = min(pGrid->GetRowCount()+1, nRow+pGrid->m_nDndRowExt-1);
		ROWCOL nDndColBounds = min(pGrid->GetColCount()+1, nCol+pGrid->m_nDndColExt-1);

		CRect rectDraw = pGrid->CalcRectFromRowCol(nRow, nCol, nDndRowBounds, nDndColBounds);

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
		pGrid->m_DndLastRect = rectDraw;

		rectDraw.top++;
		rectDraw.left++;
		rectDraw.right--;
		rectDraw.bottom--;

		dc.DrawFocusRect(rectDraw);

		pGrid->m_nDndLastRow = nRow;
		pGrid->m_nDndLastCol = nCol;
	}
}

BOOL CGXGridDropTargetPlugin::DoDragScroll(CGXGridCore* pGrid, CPoint point)
{
	BOOL bOutOfWndScroll = pGrid->m_dwDndDropTargetFlags & GX_DNDAUTOSCROLL;

	// get client rectangle of destination window
	ScreenToClient(&point);
	CRect rectClient = pGrid->GetGridRect();
	CRect rect = rectClient;

	UINT nScrollCode = MAKEWORD(-1, -1);
	BOOL bScrollCode2 = FALSE;
	int nxScrollBy = 1, nyScrollBy = 1;

	// hit-test against inset region
	rect.InflateRect(-pGrid->m_nDndScrollInset, -pGrid->m_nDndScrollInset);

	if (rectClient.PtInRect(point) && !rect.PtInRect(point)
		|| bOutOfWndScroll && !rectClient.PtInRect(point))
	{
		// determine which way to scroll along both X & Y axis
		if (point.x < rect.left)
			nScrollCode = MAKEWORD(SB_LINEUP, HIBYTE(nScrollCode));
		else if (point.x >= rect.right)
			nScrollCode = MAKEWORD(SB_LINEDOWN, HIBYTE(nScrollCode));
		if (point.y < rect.top)
			nScrollCode = MAKEWORD(LOBYTE(nScrollCode), SB_LINEUP);
		else if (point.y >= rect.bottom)
			nScrollCode = MAKEWORD(LOBYTE(nScrollCode), SB_LINEDOWN);
		ASSERT(nScrollCode != MAKEWORD(-1, -1));

		bScrollCode2 = rectClient.PtInRect(point);
	}

	// handle autoscrolling outside of grid
	if (!rectClient.PtInRect(point))
	{
		// use standard font height as factor for speed

		if (point.x < rect.left)
			nxScrollBy = rect.left-point.x;
		else if (point.x >= rect.right)
			nxScrollBy = point.x-rect.right;
		if (point.y < rect.top)
			nyScrollBy = rect.top - point.y;
		else if (point.y >= rect.bottom)
			nyScrollBy = point.y - rect.bottom;

		nyScrollBy = max(1, nyScrollBy/(pGrid->GetFontHeight()+1)*pGrid->m_nDndOufOfWndVertScrollBy);
		nxScrollBy = max(1, nxScrollBy/(pGrid->GetFontHeight()+1)*pGrid->m_nDndOufOfWndHorzScrollBy);
	}

	if (nScrollCode != MAKEWORD(-1, -1))
	{
		// save tick count when timer ID changes
		DWORD dwTick = GetTickCount();
		if (nScrollCode != pGrid->m_nDndLastScrollCode
			|| pGrid->m_bDndLastScrollCode2 != bScrollCode2)
		{
			pGrid->m_dwDndLastTick = dwTick;
			pGrid->m_nDndNextTicks = pGrid->m_nDndScrollDelay;

			// Make a bigger delay when user drags out of window
			if (!rectClient.PtInRect(point))
				pGrid->m_nDndNextTicks = pGrid->m_nDndOutOfWndDelay;
		}

		// scroll if necessary
		if (dwTick - pGrid->m_dwDndLastTick > pGrid->m_nDndNextTicks)
		{
			pGrid->m_dwDndLastTick = dwTick;
			pGrid->m_nDndNextTicks = pGrid->m_nDndScrollInterval;

			// TRACE("DoDragScroll\n");
			// DoScroll will erase the focus rectangle if necessary
			//  DndDrawMoveRect(CPoint(0,0), TRUE, FALSE);

			if (LOBYTE(nScrollCode) != (BYTE) -1)
			{
				pGrid->OnAutoScroll(LOBYTE(nScrollCode) == SB_LINEUP ? GX_LEFT : GX_RIGHT, nxScrollBy);
					// OnAutoScroll will also take care on scrolling
					// neighbour panes in a dynamic splitter window
				UpdateWindow();
			}

			if (HIBYTE(nScrollCode) != (BYTE) -1)
			{
				pGrid->OnAutoScroll(HIBYTE(nScrollCode) == SB_LINEUP ? GX_UP : GX_DOWN, nyScrollBy);
				UpdateWindow();
			}

			// draw new focus rectangle
			pGrid->DndDrawMoveRect(point, FALSE, TRUE);
		}
	}

	pGrid->m_nDndLastScrollCode = nScrollCode;
	pGrid->m_bDndLastScrollCode2 = bScrollCode2;

	return (nScrollCode != MAKEWORD(-1, -1));
}

BOOL CGXGridDropTargetPlugin::IsOverAnotherApplication(CGXGridCore* pGrid, POINT point)
{
	GX_UNUSED_ALWAYS(pGrid);

	CFrameWnd* pFrame = (CFrameWnd*) AfxGetMainWnd();

	if (pFrame)
	{
		pFrame->ScreenToClient(&point);
		CWnd* pWnd = pFrame->ChildWindowFromPoint(point);
		if (pWnd == NULL)
			return TRUE;
		else
			return FALSE;  //it's inside parent frame
	}

	return FALSE;
}

BEGIN_MESSAGE_MAP(CGXGridDropTargetPlugin, CGXPluginComponent)
	//{{AFX_MSG_MAP(CGXGridDropTargetPlugin)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CGXGridDropTargetPlugin::OnTimer(SEC_UINT nIDEvent)
{
	if (nIDEvent == GX_TIMER_DNDSCROLLOTHER)
	{
		POINT point;
		::GetCursorPos(&point);
		m_pGrid->DoDragScroll(point);
	}
	else if  (nIDEvent == GX_TIMER_DNDSCROLLSELF)
	{
		POINT point;
		::GetCursorPos(&point);

		if (!m_pGrid->IsActiveFrame() || m_pGrid->IsOverAnotherApplication(point))
		{
			m_pGrid->m_nDndLastScrollCode = MAKEWORD(-1, -1);
			return; // Outside app - do nothing
		}

		m_pGrid->DoDragScroll(point);
	}
}

void CGXGridDropTargetPlugin::OnDestroy()
{
	if (m_pGrid && m_pGrid->m_pRegDropTarget)
	{
		m_pGrid->m_pRegDropTarget = NULL;   // object gets automatically deleted
		delete m_pobjDndDropTarget;
		m_pobjDndDropTarget = NULL;
	}
}

#endif // ndef _AFX_NO_OLE_SUPPORT

