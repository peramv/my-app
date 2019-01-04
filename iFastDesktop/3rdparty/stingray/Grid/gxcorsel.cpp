///////////////////////////////////////////////////////////////////////////////
// gxcorsel.cpp : cell selections (CGXGridCore)
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

#ifndef _GXCORE_H_
#include "grid\gxcore.h"
#endif

#ifndef _GXPRIV_H_
#include "grid\gxpriv.h"
#endif


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

#ifdef TICKCOUNT
#define _TC_(f) f
#else
#define _TC_(f)
#endif




/////////////////////////////////////////////////////////////////////////////
// Selected Cells

CGXLockSelectionFrame::CGXLockSelectionFrame(CGXGridCore* pGrid)
{
	m_pGrid = pGrid;   
	m_bLock = m_pGrid->LockSelectionFrame(TRUE);
}

CGXLockSelectionFrame::~CGXLockSelectionFrame()
{
	m_pGrid->LockSelectionFrame(m_bLock);
}

BOOL CGXGridCore::CopyRangeList(CGXRangeList& list, BOOL bCanUseCurrentCell)
{
	CGXRangeList* pSelList = GetParam()->GetRangeList();

	list.DeleteAll();
	POSITION pos = pSelList->GetHeadPosition();
	while (pos)
		list.AddTail(new CGXRange(*pSelList->GetNext(pos)));

	if (pSelList->IsEmpty() && bCanUseCurrentCell)
	{
		ROWCOL nRow, nCol;
		if (GetCurrentCell(&nRow, &nCol))
			list.AddTail(new CGXRange(nRow, nCol, nRow, nCol));
	}

	return !list.IsEmpty();
}

BOOL CGXGridCore::GetSelectedCols(CRowColArray& awLeft, CRowColArray& awRight, BOOL bRangeColsOnly /*=FALSE*/, BOOL bCanUseCurrentCell)
{
	CGXRangeList* pSelList = GetParam()->GetRangeList();

	BOOL bFound
		= pSelList->GetColArray(GetColCount(), awLeft, awRight, bRangeColsOnly);
	if (!bFound && bCanUseCurrentCell)
	{
		ROWCOL nRow, nCol;
		bFound = GetCurrentCell(&nRow, &nCol);
		if (bFound)
		{
			awLeft.SetAtGrow(0, nCol);
			awRight.SetAtGrow(0, nCol);
		}
	}
	return bFound;
}

ROWCOL CGXGridCore::GetSelectedCols(CRowColArray& awCols, BOOL bRangeColsOnly /*=FALSE*/, BOOL bCanUseCurrentCell)
{
	CRowColArray awLeft, awRight;
	int nCount = 0;

	awCols.SetSize(0);

	if (GetSelectedCols(awLeft, awRight, bRangeColsOnly, bCanUseCurrentCell))
	{
		for (int i = 0; i < awLeft.GetSize(); i++)
		{
			for (ROWCOL nCol = awLeft[i]; nCol <= awRight[i]; nCol++)
				awCols.SetAtGrow(nCount++, nCol);
		}
	}

	return nCount;
}

BOOL CGXGridCore::GetSelectedRows(CRowColArray& awTop, CRowColArray& awBottom, BOOL bRangeRowsOnly/*=FALSE*/, BOOL bCanUseCurrentCell)
{
	CGXRangeList* pSelList = GetParam()->GetRangeList();

	BOOL bFound
		= pSelList->GetRowArray(GetRowCount(), awTop, awBottom, bRangeRowsOnly);
	if (!bFound && bCanUseCurrentCell)
	{
		ROWCOL nRow, nCol;
		bFound = GetCurrentCell(&nRow, &nCol);
		if (bFound)
		{
			awTop.SetAtGrow(0, nRow);
			awBottom.SetAtGrow(0, nRow);
		}
	}
	return bFound;
}

ROWCOL CGXGridCore::GetSelectedRows(CRowColArray& awRows, BOOL bRangeRowsOnly /*=FALSE*/, BOOL bCanUseCurrentCell)
{
	CRowColArray awTop, awBottom;
	int nCount = 0;

	awRows.SetSize(0);

	if (GetSelectedRows(awTop, awBottom, bRangeRowsOnly, bCanUseCurrentCell))
	{
		for (int i = 0; i < awTop.GetSize(); i++)
		{
			for (ROWCOL nRow = awTop[i]; nRow <= awBottom[i]; nRow++)
				awRows.SetAtGrow(nCount++, nRow);
		}
	}

	return nCount;
}

BOOL CGXGridCore::GetInvertStateRowCol(ROWCOL nRow, ROWCOL nCol, const CGXRangeList* pSelList)
{
	return pSelList->IsCellInList(nRow, nCol);
}

void CGXGridCore::SelectRange(const CGXRange& range, BOOL bSelect /* = TRUE */, BOOL bUpdate )
{
	GX_CHECKIMP(m_pUserSelectRangeImp, "CGXGridCore::SelectRange");

	if (m_pUserSelectRangeImp)
		m_pUserSelectRangeImp->SelectRange(this, range, bSelect, bUpdate);
}

BOOL CGXGridCore::StoreSelectRange(const CGXRange& range, BOOL bSelect)
{
	GX_CHECKIMP(m_pUserSelectRangeImp, "CGXGridCore::StoreSelectRange");

	if (m_pUserSelectRangeImp)
		return m_pUserSelectRangeImp->StoreSelectRange(this, range, bSelect);

	return FALSE;
}

void CGXGridCore::UpdateSelectRange(const CGXRange& range, const CGXRangeList* pOldRangeList, BOOL bCreateHint)
{
	GX_CHECKIMP(m_pUserSelectRangeImp, "CGXGridCore::UpdateSelectRange");

	if (m_pUserSelectRangeImp)
		m_pUserSelectRangeImp->UpdateSelectRange(this, range, pOldRangeList, bCreateHint);
}

void CGXGridCore::SetSelection(POSITION pos, ROWCOL nTop, ROWCOL nLeft, ROWCOL nBottom, ROWCOL nRight)
{
	CGXRange rgCovered, rg;
	ROWCOL nRow, nCol;
	GetCurrentCell(&nRow, &nCol);
	GetCoveredCellsRowCol(nRow, nCol, rgCovered);
	BOOL bintersect = rg.IntersectRange(rgCovered, CGXRange(nTop, nLeft, nBottom, nRight));
	if(GetParam()->GetExcelLikeCurrentCell() && bintersect && rgCovered != NULL)
		return;
	GX_CHECKIMP(m_pUserSelectRangeImp, "CGXGridCore::SetSelection");

	if (m_pUserSelectRangeImp)
		m_pUserSelectRangeImp->SetSelection(this, pos, nTop, nLeft, nBottom, nRight);
}

void CGXGridCore::PrepareChangeSelection(POSITION oldPos, ROWCOL top, ROWCOL left, ROWCOL bottom, ROWCOL right, BOOL bCreateHint)
{
	GX_CHECKIMP(m_pUserSelectRangeImp, "CGXGridCore::PrepareChangeSelection");

	if (m_pUserSelectRangeImp)
		m_pUserSelectRangeImp->PrepareChangeSelection(this, oldPos, top, left, bottom, right, bCreateHint);
}

void CGXGridCore::PrepareClearSelection(BOOL bCreateHint)
{
	GX_CHECKIMP(m_pUserSelectRangeImp, "CGXGridCore::PrepareClearSelection");

	if (m_pUserSelectRangeImp)
		m_pUserSelectRangeImp->PrepareClearSelection(this, bCreateHint);
}

// Events

void CGXGridCore::OnChangedSelection(const CGXRange* /*changedRect*/, BOOL /*bIsDragging*/, BOOL /*bKey*/)
{
	if( GetParam()->GetExcelLikeHeaders() )
	{
		RedrawRowCol(GetHeaderRows()+1, (ROWCOL)0, GetRowCount(), GetHeaderCols());
		RedrawRowCol((ROWCOL)0, GetHeaderCols()+1, GetHeaderRows(), GetColCount());
	}
}

BOOL CGXGridCore::OnStartSelection(ROWCOL nRow, ROWCOL nCol, UINT flags, CPoint point)
{
	nRow, nCol, point, flags;

	return TRUE;
}

// just for compatibility with OG 1.0. It is recommended that
// you override CanChangeSelection instead.
void CGXGridCore::PreChangeSelection(CGXRange* /*range*/, BOOL /*bIsDragging*/, BOOL /*bKey*/)
{
}

BOOL CGXGridCore::CanChangeSelection(CGXRange* pRange, BOOL bIsDragging, BOOL bKey)
{
	// just for compatibility with OG 1.0
	PreChangeSelection(pRange, bIsDragging, bKey);

	return TRUE; // return TRUE unless you want to prevent selecting the range
}

void CGXGridCore::DrawInvertFrame(CDC* pDC, const CRect& rc, const CRect& rectClip, BOOL bTopVisible, BOOL bLeftVisible, int nMarker, BOOL bOnlyMarker)
{
	GX_CHECKIMP(m_pExcelLikeFrameImp, "CGXGridCore::DrawInvertFrame");

	if (m_pExcelLikeFrameImp)
		m_pExcelLikeFrameImp->DrawInvertFrame(this, pDC, rc, rectClip, bTopVisible, bLeftVisible, nMarker, bOnlyMarker);
}



void CGXGridCore::DrawSelectionRangeFrame(CDC* pDC, const CGXRange& rg, int nMarker, BOOL bOnlyMarker)
{
	GX_CHECKIMP(m_pExcelLikeFrameImp, "CGXGridCore::DrawSelectionRangeFrame");

//code below improves redrawing on switch focus, but there is still some flickering
/*	CWnd* pWnd = m_pGridWnd->GetFocus();
    BOOL bActive = false;
	if(GetCurrentCellControl())
	    bActive = GetCurrentCellControl()->IsActive();
	if(!bActive)
	{
		if (pWnd != m_pGridWnd )
		{
			if (m_bLastFocus)
			{
				m_bLastFocus = FALSE;
				m_pGridWnd->Invalidate();
			}
			return;
		}
		else
		{
			if (!m_bLastFocus)
			{
				m_bLastFocus = TRUE;
				m_pGridWnd->Invalidate();
			}
		} 
	} */ 

	if (m_pExcelLikeFrameImp && GetFocus())
		m_pExcelLikeFrameImp->DrawSelectionRangeFrame(this, pDC, rg, nMarker, bOnlyMarker);
}

void CGXGridCore::DrawSelectionFrame(CDC* pDC, BOOL bDrawOld, const CGXRange* pNewRange)
{
	if (m_pExcelLikeFrameImp)
		m_pExcelLikeFrameImp->DrawSelectionFrame(this, pDC, bDrawOld, pNewRange);
}

void CGXGridCore::ToggleSelectionFrameMarker()
{
	if (m_pExcelLikeFrameImp)
		m_pExcelLikeFrameImp->ToggleSelectionFrameMarker(this);
}

BOOL CGXGridCore::LockSelectionFrame(BOOL bLock, BOOL bCreateHint)
{                 
	if (m_pExcelLikeFrameImp)
		return m_pExcelLikeFrameImp->LockSelectionFrame(this, bLock, bCreateHint);

	return FALSE;
}


// If you want to plug-in your own implementation, 
// call this function before calling the base class Initialize/OnInitialUpdate
// to plugin your subclassed implementation...
// Make your subclass implementation a friend of your subclassed grid class...

void CGXGridCore::SetExcelLikeFillImp(CGXAbstractGridExcelLikeFillImp* pGridExcelLikeFillImp, BOOL /*bDelete TRUE */)
{
	// QA: 31521 Removal from AutoDeletePtr
	//if(bDelete)
	//	AutoDeletePtr(m_pExcelLikeFillImp = pGridExcelLikeFillImp);
	//else
		m_pExcelLikeFillImp = pGridExcelLikeFillImp;
}

BOOL CGXGridCore::OnStartAutoFillSelection(CGXRange& rgStart, UINT& flags, CPoint& point)
{
	GX_UNUSED_ALWAYS(rgStart);
	GX_UNUSED_ALWAYS(flags);
	GX_UNUSED_ALWAYS(point);

	return TRUE; 
}

BOOL CGXGridCore::CanChangeAutoFillSelection(CGXRange& rgNew, const CGXRange& rgStart)
{
	GX_UNUSED_ALWAYS(rgNew);
	GX_UNUSED_ALWAYS(rgStart);

	return TRUE;
}

void CGXGridCore::DoAutoFill(CGXRange& rgFinal, CGXRange& rgStart)
{
	if(m_pExcelLikeFillImp)
		m_pExcelLikeFillImp->FillRect(this, rgStart, rgFinal);
}

void CGXGridCore::OnAutoFillDone(CGXRange& rgFinal)
{
	if(m_pExcelLikeFillImp)
		m_pExcelLikeFillImp->OnAutoFillDone(this, rgFinal);
}

