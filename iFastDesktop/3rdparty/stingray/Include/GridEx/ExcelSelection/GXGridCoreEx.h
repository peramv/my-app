#if !defined __GXGRIDCOREEX__H__
#define __GXGRIDCOREEX__H__
// GXGridCoreEx.h
//
//////////////////////////////////////////////////////////////////////////////
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
//////////////////////////////////////////////////////////////////////////////
//
// Author: Boris Meltreger
//

#include "GridEx\stdafx.h"
#include "GridEx\ExcelHeaders\gxheaderexcel.h"
#include "GridEx\ExcelSelection\ogdupl.h"
#include "GridEx\Res\OGResEx.h"
#include "GridEx\PopUpMenuEdit\PopUpMenuEdit.h" 
#include "GridEx\ToolTips\gxttnex.h"

namespace ogex
{

template<class T>
class CGXGridCoreEx : public T
{
public:
	CGXGridCoreEx(void);
	~CGXGridCoreEx(void);

	////////////////////////////////////////////////////////////
	//Excel Alpha Blend Selection
private:
	BOOL m_bDrawSelection;
	BOOL m_bLBtnDown;
	CRect m_rcMarker;
	int m_nAutoFill;
	BOOL m_bAutoFill;
	BOOL m_bDnD;
	CRect m_rcCurRect;
	BOOL m_bPaste;
	BOOL m_bCopyCut;
	BOOL m_bExcelLook;
	BOOL m_bContextMenu;
	COLORREF m_clrCopyCutSelection;
	CGXRangeList m_RedrawList;
public:
	struct AlphaBlend
	{
		int nPercentage;
		COLORREF clrTransparent;
		int nTolerance;
		COLORREF clrBlend;
	} m_AlphaBlend;

	// Operations
public:
	void InitializeExcel(); 
	void SetAlphaBlendSelection();
	virtual void AlphaBlendParams(int nPercentage = 50, COLORREF clrTransparent = (COLORREF)-1, int nTolerance = 0, COLORREF clrBlend = RGB(236,234,245));
	inline void SetSelectionColor(COLORREF clrBlend){m_AlphaBlend.clrBlend = clrBlend;}
	inline void SetSelectionColorTransparent(COLORREF clrTransparent){m_AlphaBlend.clrTransparent = clrTransparent;}
	inline void SetSelectionPercentage(int nPercentage){m_AlphaBlend.nPercentage = nPercentage;}
	inline void SetSelectionTolerance(int nTolerance){m_AlphaBlend.nTolerance = nTolerance;}
	inline COLORREF GetSelectionColor(){return m_AlphaBlend.clrBlend;}
	inline COLORREF GetSelectionColorTransparent(){return m_AlphaBlend.clrTransparent;}
	inline int GetSelectionPercentage(){return m_AlphaBlend.nPercentage;}
	inline int GetSelectionTolerance(){return m_AlphaBlend.nTolerance;}
	inline void SetCopyCutSelectionColor(COLORREF color){m_clrCopyCutSelection = color;}
	virtual BOOL SetCurrentCell(ROWCOL nRow, ROWCOL nCol, UINT flags = GX_UPDATENOW);
	void EnableContextMenuInEditCell(BOOL bMenu = TRUE);
	inline void EnableContextMenuInCurrentCell(BOOL bMenu = TRUE){m_bContextMenu = bMenu;}
	inline void EnableContextMenu(BOOL bMenu = TRUE){EnableContextMenuInEditCell(bMenu);
	EnableContextMenuInCurrentCell(bMenu);}
	virtual void SetSelection(POSITION pos, ROWCOL nTop = 0, ROWCOL nLeft = 0, ROWCOL nBottom = 0, ROWCOL nRight = 0);
	virtual void SelectRange(const CGXRange& range, BOOL bSelect = TRUE, BOOL bUpdate = TRUE);
	virtual BOOL SetStyleRange(const CGXRange& range, const CGXStyle* pStyle, GXModifyType mt, int nType = 0, const CObArray* pCellsArray = NULL, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);
	virtual BOOL SetStyleRange(const CGXRange& range, const CGXStyle& style, GXModifyType mt = gxOverride, int nType = 0, UINT flags = GX_UPDATENOW);
	virtual void ComposeStyleRowCol(ROWCOL nRow, ROWCOL nCol, CGXStyle* pStyle, BOOL bApplyStandard = TRUE);

protected:	
	virtual void OnDrawTLBR_InvertCells(CGXGridCore::DrawStruct& ds);
	virtual void DrawInvertCell(CDC *pDC, ROWCOL nRow, ROWCOL nCol, CRect rectItem);
	virtual void OnChangedSelection(const CGXRange* changedRect, BOOL bIsDragging, BOOL bKey);
	virtual void DrawSelectionFrame(CDC* pDC, BOOL bDrawOld = TRUE, const CGXRange* pNewRange = NULL);
	virtual BOOL OnActivateGrid( BOOL bActivate );
	virtual BOOL DoLButtonDown(UINT flags, CPoint point);
	virtual BOOL DoLButtonUp(UINT flags, CPoint point);
	virtual BOOL OnRButtonClickedRowCol(ROWCOL nRow, ROWCOL nCol, UINT nFlags, CPoint pt);
	virtual void CleanSelectionFrame(CGXRange rg);
	virtual void DrawInvertFrame(CDC* pDC, const CRect& rc, const CRect& rectClip, BOOL bTopVisible,
		BOOL bLeftVisible, int nMarker, BOOL bOnlyMarker = FALSE);
	virtual int OnExtHitTest(ROWCOL ncRow, ROWCOL ncCol, CPoint& ptTest, CRect& rect);
	virtual void ExcelLikeFill_OnLButtonDown(CGXGridCore* pGrid, CPoint& point, UINT& flags, int& ht, ROWCOL& nRow, ROWCOL& nCol);
	virtual CRect CalcRectFromRowCol(ROWCOL nStartRow, ROWCOL nStartCol, ROWCOL nEndRow, ROWCOL nEndCol, BOOL bOutsideClientArea = FALSE);
	virtual void DoAutoFill(CGXRange& rgFinal, CGXRange& rgStart);
	virtual void OnAutoFillDone(CGXRange& rgFinal);
	virtual BOOL MoveCurrentCell(int direction, UINT nCell = 1, BOOL bCanSelectRange = TRUE);
	virtual DROPEFFECT OnGridDragEnter(CGXNoOleDataObjectProxy* pDataObject,DWORD dwKeyState, CPoint point);
	virtual BOOL OnGridDrop(CGXNoOleDataObjectProxy* pDataObject, DROPEFFECT dropEffect, CPoint point);
	virtual void ShowContextCursor(CPoint &point);
	virtual BOOL CanChangeSelection(CGXRange* pRange, BOOL bIsDragging, BOOL bKey);
	virtual BOOL CanSelectCurrentCell(BOOL bSelect, ROWCOL dwSelectRow, ROWCOL dwSelectCol, ROWCOL dwOldRow, ROWCOL dwOldCol);
	virtual BOOL DoLButtonDblClk(UINT flags, CPoint point);
	virtual BOOL Paste();
	virtual BOOL MoveCells(CGXRange rg, ROWCOL nRow, ROWCOL nCol, CObject* pUndoInfo =NULL, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);
	virtual BOOL CopyCells(CGXRange rg, ROWCOL nRow, ROWCOL nCol, UINT flags = GX_UPDATENOW);
	virtual BOOL Copy();
	virtual BOOL Cut();
	virtual BOOL OnGridKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL ProcessKeys(CWnd* pSender, UINT nMessage, UINT nChar, UINT nRepCnt = 1, UINT flags = 0);
	virtual void CleanCopyCutSelection();
	////////////////////////////////////////////////////////////
	//Headers coloring
private:
	CGXRange m_rgLastHeaderMouseOver;
	BOOL m_bOnHeader;
	virtual BOOL DoMouseMove(UINT flags, CPoint point);
	virtual void ExcelHeaderMouseMove(CPoint &point);
public:
	virtual LRESULT CGXGridCoreEx<T>::OnStyleChanged();
	inline void SetCustomHeaderColor(enHeaderColor type, COLORREF color){
		((CGXHeaderExcel*)GetRegisteredControl(GX_IDS_CTRL_HEADER))->SetColor(type, color);}
};


/////////////////////////////////////////////////////////////////////////////
// C1stGridS1View construction/destruction
template<class T>
CGXGridCoreEx<T>::CGXGridCoreEx()
{
	m_rcMarker = CRect();
	m_rcCurRect = CRect();
	m_nAutoFill = 0;
	m_bAutoFill = FALSE;
	m_bDnD = FALSE;
	m_bPaste = FALSE;
	m_bCopyCut = FALSE;
	m_bOnHeader = FALSE;
	m_bExcelLook  = FALSE;
	m_bContextMenu = FALSE;
	m_clrCopyCutSelection = RGB(0,0,255);
	m_rgLastHeaderMouseOver = CGXRange(GX_INVALID,GX_INVALID);
}
template<class T>
CGXGridCoreEx<T>::~CGXGridCoreEx()
{
	m_RedrawList.DeleteAll();
}
template<class T>
void CGXGridCoreEx<T>::InitializeExcel() 
{
	EnableOleDropTarget(GX_DNDEGDESCROLL | GX_DNDAUTOSCROLL | GX_DNDTEXT | GX_DNDSTYLES);
	EnableOleDataSource();
	SetAlphaBlendSelection(); 
	GetParam()->SetExcelLikeSelectionFrame(TRUE);
	GetParam()->SetExcelLikeCurrentCell(TRUE);
	GetParam()->SetExcelLikeFillFlags(GX_XLFILLTEXT);
	GetParam()->SetExcelLikeHeaders(TRUE);
	CGXHeader* pHeader = new CGXHeaderExcel(this);
	((CGXStatic*)pHeader)->ImplementCellTips();
	RegisterControl(GX_IDS_CTRL_HEADER,pHeader);
	ChangeColHeaderStyle(CGXStyle().SetControl(GX_IDS_CTRL_HEADER));
	m_bExcelLook = TRUE; 
}

////////////////////////////////////////////////////////////////////////////
//Excel Selection
template<class T>
void CGXGridCoreEx<T>::SetAlphaBlendSelection()
{
	AlphaBlendParams();
	SetDrawingTechnique(gxDrawUsingMemDC);
} 
template<class T>
void CGXGridCoreEx<T>::AlphaBlendParams(int nPercentage,COLORREF clrTransparent, 
										int nTolerance, COLORREF clrBlend)
{
	m_AlphaBlend.nPercentage = nPercentage;
	m_AlphaBlend.clrTransparent = clrTransparent;
	m_AlphaBlend.nTolerance = nTolerance;
	m_AlphaBlend.clrBlend = clrBlend;
}
//for this function we have to add "virtual" in declaration in source and rebuild libraries
template<class T>
void CGXGridCoreEx<T>::OnDrawTLBR_InvertCells(CGXGridCore::DrawStruct& ds)
{
	if(!m_bExcelLook)
	{
		CGXGridCore::OnDrawTLBR_InvertCells(ds);
		return;
	}
	if(GetCurrentCellControl() && GetCurrentCellControl()->IsActive())
		return;

	unsigned nRow;
	CGXRangeList* pSelList = GetParam()->GetRangeList();
	for (ds.rectItem.top = ds.nyMin, nRow = 0; nRow < ds.nRows; nRow++)
	{
		ds.rectItem.bottom = ds.rectItem.top + ds.anHeights[nRow];

		ds.rectItem.left = ds.nxMin;

		for (unsigned nCol = 0; nCol < ds.nCols; nCol++)
		{
			ds.rectItem.right = ds.rectItem.left + ds.anWidths[nCol];

			unsigned r = ds.anRows[nRow],c = ds.anCols[nCol];
			BOOL bInList = pSelList->IsCellInList(r, c);
			if(r && c &&!bInList && !(m_nHitState & GX_FILLDRAG)&& !m_bDnD &&
				!(pSelList->GetCount()>=2 && r== m_nHitRow && c== m_nHitCol)
				|| !m_bDrawSelection )
				m_RedrawList.AddTail(new CGXRange(r,c));
			else if ( (ds.abBits[nRow*ds.nCols+nCol] & gxnFlagSel) > 0 &&
				!(m_bLBtnDown && (GetKeyState(VK_CONTROL) & 0x8000)))
				DrawInvertCell(ds.pDC, ds.anRows[nRow], ds.anCols[nCol], ds.rectItem);
			ds.rectItem.left = ds.rectItem.right;
		}

		ds.rectItem.top = ds.rectItem.bottom;
	}
}
template<class T>
void CGXGridCoreEx<T>::OnChangedSelection(const CGXRange* changedRect, BOOL bIsDragging, BOOL bKey)
{
	CGXGridCore::OnChangedSelection(changedRect, bIsDragging, bKey);
	ROWCOL nRow,nCol;
	GetCurrentCell(nRow,nCol);
	RedrawRowCol(nRow,nCol);
	POSITION pos = m_RedrawList.GetHeadPosition();
	if(m_RedrawList.GetCount())
	{

		while (pos)
		{

			RedrawRowCol(m_RedrawList.GetNext(pos), GX_INVALIDATE);
		}

		m_RedrawList.DeleteAll();
	}
}
template<class T>
void CGXGridCoreEx<T>::DrawInvertCell(CDC *pDC, ROWCOL nRow, ROWCOL nCol, CRect rectItem)
{
	if(!m_bExcelLook)
	{
		CGXGridCore::DrawInvertCell(pDC, nRow, nCol, rectItem);
		return;
	}
	if(m_bAutoFill)
		return;
	if(m_bPaste && m_bExcelLook)
		return;
	BOOL bCCell = IsCurrentCell(nRow, nCol);
	CGXRange rgCovered;
	ROWCOL nRFirst, nCFirst;

	if (nRow && nCol &&(!bCCell || m_pParam->GetHideCurrentCell() == GX_HIDE_ALWAYS) &&
		!(GetCoveredCellsRowCol(nRow, nCol, rgCovered) && rgCovered.GetFirstCell(nRFirst, nCFirst) && IsCurrentCell(nRFirst, nCFirst))) // QA 31642, 31775
	{
		CDrawingManager dm(*pDC);
		dm.HighlightRect(rectItem, m_AlphaBlend.nPercentage,  
			m_AlphaBlend.clrTransparent, m_AlphaBlend.nTolerance, m_AlphaBlend.clrBlend); 
	}
}

template<class T>
void CGXGridCoreEx<T>::DrawSelectionFrame(CDC* pDC, BOOL bDrawOld, const CGXRange* pNewRange)
{
	if(!m_bExcelLook)
	{
		CGXGridCore::DrawSelectionFrame(pDC, bDrawOld, pNewRange);
		return;
	}

	if( !m_bDrawSelection) 
		return;
	if(m_bPaste && m_bExcelLook)
		return;

	CGXRangeList* pSelList = GetParam()->GetRangeList();

	if(pSelList && pSelList->GetCount()==1 || m_bDnD) 
	{
		if(IsSelectingCells() && pNewRange )
			CleanSelectionFrame(*pNewRange);
		CGXGridCore::DrawSelectionFrame(pDC, bDrawOld, pNewRange);
	}
	else if(pSelList->GetCount()>=2 && m_bLBtnDown && (GetKeyState(VK_CONTROL) & 0x8000) )
	{
		if(IsSelectingCells())
		{
			if(!m_bCopyCut)
				m_bLBtnDown = FALSE;
			CleanSelectionFrame(m_rgLastSelectionFrame);
			if(!m_bDnD && m_nHitRow && m_nHitCol)
			{
				m_rcCurRect = CGXGridCore::CalcRectFromRowColEx(m_nHitRow, m_nHitCol);
				m_rcCurRect.DeflateRect(2,1,2,1);
				CBrush br(RGB(0,0,0));
				pDC->FrameRect(&m_rcCurRect, &br);
				br.DeleteObject();
			}
		}
	}
	else if(!IsSelectingCells() &&pSelList->GetCount()>=2 && m_bDrawSelection && !m_bDnD && !IsActiveCurrentCell()&& !(GetKeyState(VK_SHIFT) & 0x8000) 
		|| IsSelectingCells()&& m_nHitRow && m_nHitCol ||(GetKeyState(VK_SHIFT) & 0x8000))
	{
		CBrush br(RGB(0,0,0));
		if(pDC)
			pDC->FrameRect(&m_rcCurRect, &br); 
		br.DeleteObject();
	}
	if (m_bCopyCut && pDC)
	{
		POSITION pos = GetParam()->m_CopyRangeList.GetHeadPosition();
		while(pos)
		{
			CGXRange *pRg = GetParam()->m_CopyRangeList.GetNext(pos);
			CRect rc = CalcRectFromRowColEx(pRg->top,pRg->left,pRg->bottom,pRg->right);
			CBrush brush(3,m_clrCopyCutSelection);
			CBrush* pOldBrush = pDC->SelectObject(&brush);
			CRect r = rc, r_ = rc;

			if(m_rgLastSelectionFrame != *pRg)
			{
				r_.left -= 1;
				r_.top -= 1;
				for(int n = 0; n < 3; n++)
				{
					pDC->FrameRect(r_, &brush);
					r_.DeflateRect(1,1,1,1);
				}

			}
			else
			{
				r.right -=1;
				r.bottom -=1;
				for(int n = 0; n < 3; n++)
				{
					r.DeflateRect(1,1,1,1);
					pDC->FrameRect(r, &brush);				
				}
			}
			// Put back the old objects.
			pDC->SelectObject(pOldBrush);
		}
	}
	//bugfix2
	//if(pSelList->GetCount()==1 && pSelList->GetHead()->IsTable())
	if(IsSelectingCells())
		Invalidate();
}
template<class T>
void CGXGridCoreEx<T>::CleanSelectionFrame(CGXRange rg)
{
	if (!m_pGridWnd->IsWindowVisible()&& m_bDnD)
		return;
	if(rg.IsValid())
	{
		EvalVisibleFloatMergeCells(rg, FALSE);
		CRect rect = CalcRectFromRowColExEx(rg.top, rg.left,
			rg.bottom, rg.right);
		rect.InflateRect(2,2,4,4);
		InvalidateRect(rect);
		UpdateWindow();
	}
}
template<class T>
BOOL CGXGridCoreEx<T>::OnActivateGrid( BOOL bActivate )
{
	m_bDrawSelection = bActivate;
	BOOL bRet = CGXGridCore::OnActivateGrid( bActivate );

	if(m_bExcelLook && !bActivate)
		Redraw();
	return  bRet;
}
template<class T>
BOOL CGXGridCoreEx<T>::DoLButtonDown(UINT flags, CPoint point)
{ 
	ROWCOL  nRow = 0, nCol = 0;
	if(m_bExcelLook)
	{
		int ht = -1;
		if (!_doButtonDown1(this, flags, point, MK_MBUTTON | MK_RBUTTON, ht, nRow, nCol))
			return FALSE;
		if(IsActiveCurrentCell() && (GetKeyState(VK_CONTROL) & 0x8000 || GetKeyState(VK_SHIFT) & 0x8000))
			TransferCurrentCell();
		if(ht != GX_SELEDGEHIT)
		{
			m_bLBtnDown = TRUE;
			if(!nRow && !nCol)
			{
				CGXGridCore::SetSelection(NULL);
				Invalidate();
				if(m_nHitRow  == nRow && m_nHitCol  == nCol)
				{
					m_nHitRow=GetRowCount()+1;
					m_nHitCol=GetColCount()+1;
					return FALSE;
				}
			}

		}
		if(ht == GX_FILLHANDLEHIT)
		{
			m_nHitState = GX_HIT;
			m_nHitRow   = nRow;
			m_nHitCol   = nCol;

			if (GetParam()->m_nExcelLikeFillFlags && m_pExcelLikeFillImp)
			{
				m_bAutoFill = TRUE;
				ExcelLikeFill_OnLButtonDown(this, point, flags, ht, nRow, nCol);
			}

			if (GetCapture() != m_pGridWnd && m_nHitState)
			{
				// Catch all Mouse events
				if (m_bAutoScroll)
					// I am using AutoScroll until WM_LBUTTONUP Message
					AutoScroll(FALSE,
					nRow > 0 && !IsFrozenRow(nRow),
					nCol > 0 && !IsFrozenCol(nCol));

				SetCapture();
			}
			return TRUE;
		}
	}
	//bugfix1
	BOOL bLock = FALSE;
	if(m_bExcelLook && !nRow || !nCol)
		LockUpdate(bLock = !bLock);
	BOOL bRet = CGXGridCore::DoLButtonDown(flags, point);
	if(bLock) LockUpdate(FALSE);
	Redraw();
	return bRet;
}
template<class T>
void CGXGridCoreEx<T>::DrawInvertFrame(CDC* pDC, const CRect& rc, const CRect& rectClip, BOOL bTopVisible,
									   BOOL bLeftVisible, int nMarker, BOOL bOnlyMarker)
{
	if(!m_bExcelLook)
	{
		CGXGridCore::DrawInvertFrame(pDC, rc, rectClip, bTopVisible,
			bLeftVisible, nMarker, bOnlyMarker);
		return;
	}

	bOnlyMarker;
	CRect r = rc;
	r -= CPoint(1, 1);
	ROWCOL nRow, nCol;
	CRect rcActive;
	CGXRange* pSelected = NULL;
	CGXRange rgCovered;
	// check nMarker (in case full rows or cols are selected)
	switch (nMarker)
	{
	case GX_LEFT:
		if((GetCurrentCell(nRow, nCol)&& GetCurrentCellControl()->IsActive()))
		{
			rcActive = CalcRectFromRowCol(nRow, nCol,nRow, nCol);
			if (bTopVisible) GXInvertRect(pDC, CRect(rcActive.right, r.top-1, r.right-2, r.top+2), rectClip); //top
			if (bTopVisible) GXInvertRect(pDC, CRect(r.left+2, r.top-1, rcActive.right, r.top+1), rectClip); //top active
			GXInvertRect(pDC, CRect(rcActive.right, r.bottom-1, r.right-2, r.bottom+2), rectClip);//bottom
			GXInvertRect(pDC, CRect(r.left+7, r.bottom, rcActive.right, r.bottom+2), rectClip);//bottom active
			GXInvertRect(pDC, CRect(r.right-2, r.top-1, r.right+1, r.bottom+2), rectClip);//right
			m_rcMarker = CRect(r.left, r.bottom-1, r.left+6, r.bottom+3);
			GXInvertRect(pDC, m_rcMarker, rectClip);//marker

		}
		else
		{
			if (bTopVisible) GXInvertRect(pDC, CRect(r.left+2, r.top-1, r.right-2, r.top+2), rectClip); //top
			if (bLeftVisible) GXInvertRect(pDC, CRect(r.left-1, r.top-1, r.left+2, r.bottom-3), rectClip);//left
			GXInvertRect(pDC, CRect(r.left+7, r.bottom-1, r.right-2, r.bottom+2), rectClip);//bottom
			GXInvertRect(pDC, CRect(r.right-2, r.top-1, r.right+1, r.bottom+2), rectClip);//right
			m_rcMarker = CRect(r.left, r.bottom-2, r.left+6, r.bottom+3);
			GXInvertRect(pDC, m_rcMarker, rectClip);//marker
		}
		break;

	case GX_TOP:
		if((GetCurrentCell(nRow, nCol)&& GetCurrentCellControl()->IsActive()))
		{
			rcActive = CalcRectFromRowCol(nRow, nCol,nRow, nCol);
			if (bLeftVisible) GXInvertRect(pDC, CRect(r.left-1, rcActive.bottom, r.left+2, r.bottom+1), rectClip);//left 
			if (bLeftVisible) GXInvertRect(pDC, CRect(r.left-1, rcActive.top, r.left+1, rcActive.bottom), rectClip);//left active
			GXInvertRect(pDC, CRect(r.right-2, rcActive.bottom, r.right+1, r.bottom+1), rectClip);//right 
			GXInvertRect(pDC, CRect(r.right-1, r.top+7, r.right+1, rcActive.bottom), rectClip);//right active
			GXInvertRect(pDC, CRect(r.left+2, r.bottom-2, r.right-2, r.bottom+1), rectClip);//bottom
			m_rcMarker = CRect(r.right-1, r.top-3, r.right+2, r.top+6);
			GXInvertRect(pDC, m_rcMarker, rectClip);//marker

		}
		else
		{
			if (bTopVisible) GXInvertRect(pDC, CRect(r.left+2, r.top-1, r.right-4, r.top+2), rectClip);//top
			if (bLeftVisible) GXInvertRect(pDC, CRect(r.left-1, r.top-1, r.left+2, r.bottom+1), rectClip);//left
			GXInvertRect(pDC, CRect(r.left+2, r.bottom-2, r.right-2, r.bottom+1), rectClip);//bottom
			GXInvertRect(pDC, CRect(r.right-2, r.top+7, r.right+1, r.bottom+1), rectClip);//right
			m_rcMarker = CRect(r.right-3, r.top-3, r.right+2, r.top+6);
			GXInvertRect(pDC, m_rcMarker, rectClip);//marker
		}
		break;

	default:
		if((GetCurrentCell(nRow, nCol)&& GetCurrentCellControl()->IsActive()))
		{
			rcActive = CalcRectFromRowColExEx(nRow, nCol,nRow, nCol);
			if(GetParam()->GetRangeList())
				pSelected = GetParam()->GetRangeList()->GetTail();
			if(!pSelected)
				return;
			GetCoveredCellsRowCol(nRow, nCol, rgCovered);

			if(pSelected && pSelected->GetWidth()==1 && pSelected->GetHeight()==1
				|| rgCovered == *pSelected)
			{
				if (bTopVisible) GXInvertRect(pDC, CRect(r.left-1, r.top-1, r.right-1, r.top+1), rectClip);//top
				if (bLeftVisible) GXInvertRect(pDC, CRect(r.left-1, r.top+1, r.left+1, r.bottom+2), rectClip);//left
				GXInvertRect(pDC, CRect(r.left+1, r.bottom, r.right-4, r.bottom+2), rectClip);//bottom
				GXInvertRect(pDC, CRect(r.right-1, r.top-1, r.right+1, r.bottom-1), rectClip);//right
				m_rcMarker = CRect(r.right-3, r.bottom-1, r.right+2, r.bottom+3);
			}
			else if(pSelected && pSelected->GetWidth()==1 && pSelected->bottom == nRow
				|| pSelected && pSelected->GetWidth() == rgCovered.GetWidth() && pSelected->bottom == rgCovered.bottom)
			{
				if (bTopVisible) GXInvertRect(pDC, CRect(r.left+2, r.top-1, r.right-2, r.top+2), rectClip);//top
				if (bLeftVisible) GXInvertRect(pDC, CRect(r.left-1, r.bottom - rcActive.Height(), r.left+1, r.bottom+2), rectClip);//left active
				if (bLeftVisible) GXInvertRect(pDC, CRect(r.left-1, r.top-1, r.left+2, r.bottom - rcActive.Height()), rectClip);//left
				GXInvertRect(pDC, CRect(r.right-1, rcActive.top , r.right+1, r.bottom-1), rectClip);//right active
				GXInvertRect(pDC, CRect(r.right-2, r.top-1, r.right+1, rcActive.top), rectClip);//right
				GXInvertRect(pDC, CRect(r.left+1, r.bottom, r.right-3, r.bottom+2), rectClip);//bottom
				m_rcMarker = CRect(r.right-3, r.bottom-2, r.right+2, r.bottom+3);
			}
			else if(pSelected && pSelected->GetHeight()==1 && pSelected->right == nCol
				|| pSelected && pSelected->GetHeight() == rgCovered.GetHeight() && pSelected->right == rgCovered.right)
			{
				if (bTopVisible) GXInvertRect(pDC, CRect(r.left+2, r.top-1, rcActive.left-2, r.top+2), rectClip);//top
				if (bTopVisible) GXInvertRect(pDC, CRect(rcActive.left-2, r.top-1, r.right -1, r.top+1), rectClip);//top active
				if (bLeftVisible) GXInvertRect(pDC, CRect(r.left-1, r.top-1, r.left+2, r.bottom+2), rectClip);//left
				GXInvertRect(pDC, CRect(r.right-1, r.top-1, r.right+1, r.bottom-1), rectClip);//right active
				GXInvertRect(pDC, CRect(r.right-2, r.top, r.right+1, rcActive.top), rectClip);//right
				GXInvertRect(pDC, CRect(r.left+1, r.bottom, r.right-3, r.bottom+2), rectClip);//bottom
				m_rcMarker = CRect(r.right-3, r.bottom-2, r.right+2, r.bottom+3);
			}
			else if(pSelected && pSelected->GetHeight()==1 && pSelected->left == nCol
				|| pSelected && pSelected->GetHeight() == rgCovered.GetHeight() && pSelected->left == rgCovered.left)
			{
				if (bTopVisible) GXInvertRect(pDC, CRect(r.left-1, r.top-1, r.left+rcActive.Width(), r.top), rectClip);//top active
				if (bTopVisible) GXInvertRect(pDC, CRect(r.left+rcActive.Width(), r.top-1, r.right-2, r.top+2), rectClip);//top
				if (bLeftVisible) GXInvertRect(pDC, CRect(r.left-1, r.top+1, r.left+1, r.bottom+2), rectClip);//left
				GXInvertRect(pDC, CRect(r.left+1, r.bottom, r.left+rcActive.Width(), r.bottom+2), rectClip);//bottom active
				GXInvertRect(pDC, CRect(r.left+rcActive.Width(), r.bottom+1, r.right-4, r.bottom+2), rectClip);//bottom 
				GXInvertRect(pDC, CRect(r.right-2, r.top-1, r.right+1, r.bottom-2), rectClip);//right
				m_rcMarker = CRect(r.right-3, r.bottom-3, r.right+2, r.bottom+2);
			}
			else if(pSelected && pSelected->left ==nCol && pSelected->top == nRow 
				|| pSelected && pSelected->left == rgCovered.left && pSelected->top == rgCovered.top)
			{
				if (bTopVisible) GXInvertRect(pDC, CRect(r.left-1, r.top-1, r.left+rcActive.Width(), r.top), rectClip);//top active
				if (bTopVisible) GXInvertRect(pDC, CRect(r.left+rcActive.Width(), r.top-1, r.right-2, r.top+2), rectClip);//top
				if (bLeftVisible) GXInvertRect(pDC, CRect(r.left-1, r.top+1, r.left+1, r.bottom+1), rectClip);//left
				GXInvertRect(pDC, CRect(r.left+2, r.bottom-2, r.right-4, r.bottom+1), rectClip);//bottom
				GXInvertRect(pDC, CRect(r.right-1, r.top-1, r.right+1, r.bottom-4), rectClip);//right
				m_rcMarker = CRect(r.right-3, r.bottom-3, r.right+2, r.bottom+2);

			}
			else if(pSelected && pSelected->right ==nCol && pSelected->top == nRow
				|| pSelected && pSelected->right == rgCovered.right && pSelected->top == rgCovered.top)
			{
				if (bTopVisible) GXInvertRect(pDC, CRect(r.right-rcActive.Width(), r.top-1, r.right-1, r.top+1), rectClip);//top active
				if (bTopVisible) GXInvertRect(pDC, CRect(r.left+1, r.top-1, r.right-rcActive.Width(), r.top+2), rectClip);//top
				if (bLeftVisible) GXInvertRect(pDC, CRect(r.left-1, r.top-1, r.left, r.bottom+1), rectClip);//left
				GXInvertRect(pDC, CRect(r.left+2, r.bottom-2 , r.right-4, r.bottom+1), rectClip);//bottom
				GXInvertRect(pDC, CRect(r.right-1, r.top-1, r.right+1, r.top+rcActive.Height()), rectClip);//right active
				GXInvertRect(pDC, CRect(r.right-1, r.top+rcActive.Height(), r.right+1, r.bottom-2), rectClip);//right
				m_rcMarker = CRect(r.right-3, r.bottom-3, r.right+2, r.bottom+2);

			}
			else if(pSelected && pSelected->left ==nCol && pSelected->bottom == nRow
				|| pSelected && pSelected->left == rgCovered.left && pSelected->bottom == rgCovered.bottom)
			{
				if (bTopVisible) GXInvertRect(pDC, CRect(r.left+2, r.top-1, r.right-2, r.top+2), rectClip);//top
				if (bLeftVisible) GXInvertRect(pDC, CRect(r.left-1, r.bottom - rcActive.Height(), r.left, r.bottom+2), rectClip);//left active
				if (bLeftVisible) GXInvertRect(pDC, CRect(r.left-1, r.top-1, r.left+2, r.bottom - rcActive.Height()), rectClip);//left
				GXInvertRect(pDC, CRect(r.left+1, r.bottom, r.left+rcActive.Width(), r.bottom+2), rectClip);//bottom active
				GXInvertRect(pDC, CRect(r.left+rcActive.Width(), r.bottom+1, r.right-4, r.bottom+2), rectClip);//bottom 
				GXInvertRect(pDC, CRect(r.right-2, r.top-1, r.right+1, r.bottom-2), rectClip);//right
				m_rcMarker = CRect(r.right-3, r.bottom-3, r.right+2, r.bottom+2);

			}
			else if(pSelected && pSelected->right == nCol && pSelected->bottom == nRow
				|| pSelected && pSelected->right == rgCovered.right && pSelected->bottom == rgCovered.bottom)
			{
				if (bTopVisible) GXInvertRect(pDC, CRect(r.left+2, r.top-1, r.right-2, r.top+2), rectClip);//top
				if (bLeftVisible) GXInvertRect(pDC, CRect(r.left-1, r.top-1, r.left+2, r.bottom+2), rectClip);//left
				GXInvertRect(pDC, CRect(r.right-rcActive.Width(), r.bottom, r.right-3, r.bottom+2), rectClip);//bottom active
				GXInvertRect(pDC, CRect(r.left+2, r.bottom , r.right-rcActive.Width(), r.bottom+2), rectClip);//bottom 
				GXInvertRect(pDC, CRect(r.right-1, rcActive.top, r.right+1, r.bottom-1), rectClip);//right active
				GXInvertRect(pDC, CRect(r.right-2, r.top-1, r.right+1, rcActive.top), rectClip);//right
				m_rcMarker = CRect(r.right-3, r.bottom-1, r.right+2, r.bottom+3);
			}
			else if(pSelected && pSelected->left == nCol) 
			{
				if (bTopVisible) GXInvertRect(pDC, CRect(r.left+2, r.top-1, r.right-2, r.top+2), rectClip);//top
				if (bLeftVisible) GXInvertRect(pDC, CRect(r.left-1, rcActive.top, r.left, rcActive.bottom), rectClip);//left active
				if (bLeftVisible) GXInvertRect(pDC, CRect(r.left-1, r.top-1, r.left+2, rcActive.top), rectClip);//leftup
				if (bLeftVisible) GXInvertRect(pDC, CRect(r.left-1, rcActive.bottom, r.left+2, r.bottom +1), rectClip);//leftdown
				GXInvertRect(pDC, CRect(r.left+2, r.bottom-2 , r.right-4, r.bottom+1), rectClip);//bottom
				GXInvertRect(pDC, CRect(r.right-2, r.top-1, r.right+1, r.bottom-2), rectClip);//right
				m_rcMarker = CRect(r.right-3, r.bottom-3, r.right+2, r.bottom+2);
			}
			else if(pSelected && pSelected->right == nCol)
			{
				if (bTopVisible) GXInvertRect(pDC, CRect(r.left+2, r.top-1, r.right-2, r.top+2), rectClip);//top
				if (bLeftVisible) GXInvertRect(pDC, CRect(r.left-1, r.top-1, r.left+2, r.bottom+2), rectClip);//left
				GXInvertRect(pDC, CRect(r.left+2, r.bottom-2 , r.right-4, r.bottom+1), rectClip);//bottom
				GXInvertRect(pDC, CRect(r.right-1, rcActive.top, r.right+1, rcActive.bottom), rectClip);//right active
				GXInvertRect(pDC, CRect(r.right-2, r.top-1, r.right+1, rcActive.top), rectClip);//rightup
				GXInvertRect(pDC, CRect(r.right-2, rcActive.bottom, r.right+1, r.bottom -2), rectClip);//righdown
				m_rcMarker = CRect(r.right-3, r.bottom-3, r.right+2, r.bottom+2);
			}
			else if(pSelected && pSelected->top == nRow)
			{
				if (bTopVisible) GXInvertRect(pDC, CRect(rcActive.left, r.top-1, rcActive.right, r.top), rectClip);//top active
				if (bTopVisible) GXInvertRect(pDC, CRect(r.left+2, r.top-1, rcActive.left, r.top+2), rectClip);//topleft
				if (bTopVisible) GXInvertRect(pDC, CRect(rcActive.right, r.top-1, r.right-2, r.top+2), rectClip);//topright
				if (bLeftVisible) GXInvertRect(pDC, CRect(r.left-1, r.top-1, r.left+2, r.bottom+1), rectClip);//left
				GXInvertRect(pDC, CRect(r.left+2, r.bottom-2, r.right-4, r.bottom+1), rectClip);//bottom
				GXInvertRect(pDC, CRect(r.right-1, r.top-1, r.right+1, r.bottom-4), rectClip);//right
				m_rcMarker = CRect(r.right-3, r.bottom-3, r.right+2, r.bottom+2);
			}
			else if(pSelected && pSelected->bottom == nRow)
			{
				if (bTopVisible) GXInvertRect(pDC, CRect(r.left+2, r.top-1, r.right-2, r.top+2), rectClip);//top
				if (bLeftVisible) GXInvertRect(pDC, CRect(r.left-1, r.top-1, r.left+2, r.bottom+1), rectClip);//left
				GXInvertRect(pDC, CRect(rcActive.left, r.bottom-2, rcActive.right, r.bottom+1), rectClip);//bottom active
				GXInvertRect(pDC, CRect(r.left+2, r.bottom-2, rcActive.left, r.bottom+1), rectClip);//bottomleft
				GXInvertRect(pDC, CRect(rcActive.right, r.bottom-2, r.right-4, r.bottom+1), rectClip);//bottomright
				GXInvertRect(pDC, CRect(r.right-1, r.top-1, r.right+1, r.bottom-4), rectClip);//right
				m_rcMarker = CRect(r.right-3, r.bottom-3, r.right+2, r.bottom+2);
			}
		}
		else
		{
			if (bTopVisible) GXInvertRect(pDC, CRect(r.left+2, r.top-1, r.right-2, r.top+2), rectClip);//top
			if (bLeftVisible) GXInvertRect(pDC, CRect(r.left-1, r.top-1, r.left+2, r.bottom+1), rectClip);//left
			GXInvertRect(pDC, CRect(r.left+2, r.bottom-2, r.right-4, r.bottom+1), rectClip);//bottom
			GXInvertRect(pDC, CRect(r.right-2, r.top-1, r.right+1, r.bottom-4), rectClip);//right
			m_rcMarker = CRect(r.right-3, r.bottom-3, r.right+2, r.bottom+2);					
		}
		GXInvertRect(pDC, m_rcMarker, rectClip);//marker

		break;
	}
}
template<class T>
int CGXGridCoreEx<T>::OnExtHitTest(ROWCOL ncRow, ROWCOL ncCol, CPoint& ptTest, CRect& rect)
{
	int nHit = CGXGridCore::OnExtHitTest(ncRow, ncCol, ptTest, rect);
	if(m_bExcelLook)
	{
		if(m_rcMarker.PtInRect(ptTest))
			return GX_FILLHANDLEHIT;
		else if(nHit == GX_FILLHANDLEHIT)
			return 0;
	}
	return nHit;
}

template<class T>
void CGXGridCoreEx<T>::ExcelLikeFill_OnLButtonDown(CGXGridCore* pGrid, CPoint& point, UINT& flags, int& ht, ROWCOL& nRow, ROWCOL& nCol)
{
	pGrid;
	ASSERT(GetParam()->GetExcelLikeCurrentCell());
	// ASSERT: Otherwise the current cell will not be put in the rangelist below and will
	// crash when trying to drag the current cell.

	CGXRange rgSel = *(GetParam()->GetRangeList()->GetAt(GetParam()->GetRangeList()->FindRange(nRow, nCol)));
	// Cannot start an excel like fill from frozen/header rows/cols...
	// We don't support auto fill on complete row/col, yet
	if(nRow >= GetTopRow() && nCol >= GetLeftCol() 
		//&& !rgSel.IsRows() && !rgSel.IsCols() 
		&& !rgSel.IsTable()
		&& OnStartAutoFillSelection(rgSel, flags, point))
	{
		TransferCurrentCell(nRow, nCol);
		m_nHitState |= GX_FILLDRAG;
		((CGXGridExcelLikeFillImp*)m_pExcelLikeFillImp)->m_startRange = rgSel;
		((CGXGridExcelLikeFillImp*)m_pExcelLikeFillImp)->m_ExcelLastRect.SetRectEmpty();
		((CGXGridExcelLikeFillImp*)m_pExcelLikeFillImp)->m_ExcelLastRange.SetCells(0,0,0,0);
	}

	GX_UNUSED_ALWAYS(ht);
	GX_UNUSED_ALWAYS(flags);
	GX_UNUSED_ALWAYS(point);
}

//for this function we have to add "virtual" in declaration in source and rebuild libraries
template<class T>
CRect CGXGridCoreEx<T>::CalcRectFromRowCol(ROWCOL nStartRow, ROWCOL nStartCol, ROWCOL nEndRow, ROWCOL nEndCol, BOOL bOutsideClientArea)
{
	if(m_bExcelLook)
	{		
		if(m_bAutoFill && GetParam()->GetRangeList()&& GetParam()->GetRangeList()->FindRange(nStartRow, nStartCol))
		{
			CGXRange rgSel = *(GetParam()->GetRangeList()->GetAt(GetParam()->GetRangeList()->FindRange(nStartRow, nStartCol)));
			if(rgSel.IsCols())
				nEndRow = GetRowCount();
			else if(rgSel.IsRows())
				nEndCol = GetColCount();
		}
	}
	return CGXGridCore::CalcRectFromRowCol(nStartRow, nStartCol, nEndRow, nEndCol, bOutsideClientArea);
}
template<class T>
void CGXGridCoreEx<T>::DoAutoFill(CGXRange& rgFinal, CGXRange& rgStart)
{
	if(m_bExcelLook)
	{		
		if(rgStart.IsCols())
		{
			rgFinal.top = rgStart.top = 1;
			rgFinal.bottom = rgStart.bottom = GetRowCount();
			m_nAutoFill = 1;
		}
		else if(rgStart.IsRows())
		{
			rgFinal.left = rgStart.left = 1;
			rgFinal.right = rgStart.right = GetColCount();
			m_nAutoFill = 2;
		}
		else
			m_nAutoFill = 0;
	}
	CGXGridCore::DoAutoFill(rgFinal, rgStart);

}
template<class T>
void CGXGridCoreEx<T>::OnAutoFillDone(CGXRange& rgFinal)
{
	if(m_bExcelLook)
	{
		if(m_nAutoFill == 1)
			rgFinal = CGXRange().SetCols(rgFinal.left, rgFinal.right);
		else if(m_nAutoFill == 2)
			rgFinal = CGXRange().SetRows(rgFinal.top, rgFinal.bottom);
	}
	CGXGridCore::OnAutoFillDone(rgFinal);
	if(m_bExcelLook)
	{
		CGXGridCore::SetSelection(NULL);
		SelectRange(rgFinal);
		RedrawRowCol(rgFinal,GX_SMART);
		m_bAutoFill = FALSE;
	}
}
template<class T>
BOOL CGXGridCoreEx<T>::DoLButtonUp(UINT flags, CPoint point)
{
	ROWCOL nRow = 0;
	ROWCOL nCol = 0;

	if(m_bExcelLook)
	{	
		LockUpdate(TRUE);
		if(!m_bCopyCut)
			m_bLBtnDown = FALSE;

		GetCurrentCell(nRow, nCol);
	}
	BOOL bRet = CGXGridCore::DoLButtonUp(flags, point);
	if(m_bExcelLook)
	{	
		if(GetParam()->GetRangeList()->GetCount()>1 && 
			!(GetParam()->GetRangeList()->GetTail()->IsCols()
			||GetParam()->GetRangeList()->GetTail()->IsRows()))
		{
			m_bDrawSelection = FALSE;
			RedrawRowCol(nRow, nCol, GX_INVALIDATE);
			m_bDrawSelection = TRUE;
		}
		//if(IsActiveCurrentCell())
		//CleanSelectionFrame(m_rgLastSelectionFrame);
		LockUpdate(FALSE);
		Redraw();
	}

	return bRet;
}
template<class T>
BOOL CGXGridCoreEx<T>::MoveCurrentCell(int direction, UINT nCell, BOOL bCanSelectRange)
{
	if(m_bExcelLook)
	{
		CGXGridCore::SetSelection(NULL);
		Redraw();
	}
	return CGXGridCore::MoveCurrentCell(direction, nCell, bCanSelectRange);
}
template<class T>
DROPEFFECT CGXGridCoreEx<T>::OnGridDragEnter(CGXNoOleDataObjectProxy* pDataObject,
											 DWORD dwKeyState, CPoint point)
{
	if(m_bExcelLook)
	{
		if( GetParam()->GetRangeList()->GetCount()>1)
			return 0;
		m_bDnD = TRUE;
		m_rcCurRect = CRect();
	}
	return CGXGridCore::OnGridDragEnter(pDataObject, dwKeyState, point);
}
template<class T>
BOOL CGXGridCoreEx<T>::OnGridDrop(CGXNoOleDataObjectProxy* pDataObject,
								  DROPEFFECT dropEffect, CPoint point)
{
	m_bDnD = FALSE;
	m_bDrawSelection = FALSE;
	CGXRange * pOldRg = GetParam()->m_pDndSelList->GetHead();
	ROWCOL nRowCur, nColCur;
	GetCurrentCell(nRowCur, nColCur);
	LockUpdate(TRUE);
	BOOL bret = CGXGridCore::OnGridDrop(pDataObject,dropEffect, point);
	if(m_bExcelLook)
	{
		CGXRange NewRg = *GetParam()->GetRangeList()->GetTail();

		//Covered cells move with selection; can not drop on covered cells
		ROWCOL nRow, nCol,nRowNew, nColNew, nRowCov, nColCov;
		CGXRange rgCov, rgCovOld;
		NewRg.GetFirstCell(nRowNew, nColNew);
		do
		{
			if(GetCoveredCellsRowCol(nRowNew, nColNew, rgCov))
			{
				Undo();
				LockUpdate(FALSE);
				CGXGridCore::SetSelection(NULL);
				m_bDrawSelection = TRUE;
				SelectRange(*pOldRg);
				SetCurrentCell(nRowCur, nColCur);
				Redraw();
				return FALSE;
			}
		}
		while(NewRg.GetNextCell(nRowNew, nColNew));

		pOldRg->GetFirstCell(nRow, nCol);
		NewRg.GetFirstCell(nRowNew, nColNew);
		do
		{
			if(GetCoveredCellsRowCol(nRow, nCol, rgCovOld) && (rgCovOld.GetFirstCell(nRowCov, nColCov)&& nRow==nRowCov && nCol==nColCov))
			{
				SetCoveredCellsRowCol(nRowNew, nColNew, nRowNew + rgCovOld.GetHeight()-1,nColNew + rgCovOld.GetWidth()-1);
				StoreCoveredCellsRowCol(nRow, nCol, nRow + rgCovOld.GetHeight()-1,nCol + rgCovOld.GetWidth()-1, FALSE);		
			}
		}
		while(pOldRg->GetNextCell(nRow, nCol)&& NewRg.GetNextCell(nRowNew, nColNew));
		m_bDrawSelection = TRUE;
		CGXGridCore::SetSelection(NULL);
		SelectRange(NewRg);
		LockUpdate(FALSE);
	}
	Redraw();
	return bret;
}
template<class T>
BOOL CGXGridCoreEx<T>::DoMouseMove(UINT flags, CPoint point)
{
	BOOL bRet = CGXGridCore::DoMouseMove(flags, point);
	if(m_bExcelLook && GetParam()->GetExcelLikeHeaders())
		ExcelHeaderMouseMove(point);
	return bRet;
}
template<class T>
void CGXGridCoreEx<T>::ExcelHeaderMouseMove(CPoint &point)
{
	ROWCOL  nRow, nCol;
	int ht = HitTest(point, &nRow, &nCol);
	CGXHeaderExcel* pHeader = ((CGXHeaderExcel*)GetRegisteredControl(GX_IDS_CTRL_HEADER));
	CRect rect = GetGridRect();
	rect.DeflateRect(3,3,2,2);
	BOOL bOnHeader = m_bOnHeader;
	CGXRange rgLastHeaderMouseOver = m_rgLastHeaderMouseOver;
	if(ht == GX_HEADERHIT && rect.PtInRect(point))
	{
		pHeader->m_nHitRow = nRow;
		pHeader->m_nHitCol = nCol;
		pHeader->m_bOnHeader = TRUE;
		m_bOnHeader = TRUE;
		m_rgLastHeaderMouseOver = CGXRange(nRow,nCol);
	}
	else
	{
		pHeader->m_nHitRow = -1;
		pHeader->m_nHitCol = -1;
		pHeader->m_bOnHeader = FALSE;
		m_bOnHeader = FALSE;
		m_rgLastHeaderMouseOver = CGXRange(GX_INVALID,GX_INVALID);
	}
	if(bOnHeader != m_bOnHeader || rgLastHeaderMouseOver != m_rgLastHeaderMouseOver)
		Redraw();
}
template<class T>
void CGXGridCoreEx<T>::ShowContextCursor(CPoint &point)
{
	if(m_bExcelLook)
	{
		ROWCOL nRow, nCol;
		int  ht = HitTest(point, &nRow, &nCol);
		if((ht == GX_SELEDGEHIT || ht == GX_FILLHANDLEHIT) && GetParam()->GetRangeList()->GetCount()>1)
			point = CPoint(0,0);
	}
	CGXGridCore::ShowContextCursor(point);
}
template<class T>
BOOL CGXGridCoreEx<T>::CanChangeSelection(CGXRange* pRange, BOOL bIsDragging, BOOL bKey)
{
	if(m_bExcelLook)
	{
		bKey; bIsDragging;
		if(pRange && pRange->IsValid() )
		{
			ROWCOL nRow, nCol;
			CGXRange rgSpanned;
			pRange->GetFirstCell(nRow, nCol);
			do
			{
				if(GetCellRangeRowCol(nRow, nCol, rgSpanned))
					pRange->UnionRange(*pRange, rgSpanned);
			}
			while(pRange->GetNextCell(nRow, nCol));
		}

		return TRUE; 
	}
	return CGXGridCore::CanChangeSelection(pRange, bIsDragging, bKey);
}
template<class T>
BOOL CGXGridCoreEx<T>::SetCurrentCell(ROWCOL nRow, ROWCOL nCol, UINT flags )
{
	int nRedraw = 0;
	if(m_bExcelLook)
	{
		if(!nRow)
		{
			nRow = 1;
			nRedraw = 1;
		}
		if(!nCol)
		{
			nCol = 1;
			nRedraw = 2;
		}
		if(nRedraw) flags = GX_INVALIDATE;
	}
	BOOL bRet = CGXGridCore::SetCurrentCell( nRow, nCol, flags);
	{
		if(GetParam()->GetRangeList()->GetCount()== 1)
		{
			if(nRedraw == 1) RedrawRowCol(CGXRange().SetCols(nCol));
			if(nRedraw == 2) RedrawRowCol(CGXRange().SetRows(nRow));
		}
		else if(GetParam()->GetRangeList()->GetCount()>1)
		{
			ROWCOL r = m_nHitRow, c = m_nHitCol;
			BOOL bFrame = FALSE;
			if(!m_nHitRow)
			{
				bFrame=TRUE;
				r = 1;
			}
			if(!m_nHitCol)
			{
				bFrame=TRUE;
				c = 1;
			}

			if(bFrame && !(GetKeyState(VK_SHIFT) & 0x8000))
			{
				m_rcCurRect = CGXGridCore::CalcRectFromRowColEx(r,c);
				RedrawRowCol(r,c);
				m_rcCurRect.DeflateRect(2,1,2,1);
				CBrush br(RGB(0,0,0));
				GetGridDC()->FrameRect(&m_rcCurRect, &br);
				br.DeleteObject();
			}
		}
	}
	return bRet;
}
template<class T>
BOOL CGXGridCoreEx<T>::CanSelectCurrentCell(BOOL bSelect, ROWCOL dwSelectRow, ROWCOL dwSelectCol, ROWCOL dwOldRow, ROWCOL dwOldCol)
{
	if(m_bExcelLook && GetKeyState(VK_SHIFT) & 0x8000 && !IsActiveCurrentCell())
		return FALSE;
	if(m_bExcelLook && !(GetKeyState(VK_CONTROL) & 0x8000) && GetParam()->GetRangeList()->IsCellInList(dwSelectRow, dwSelectCol) && !m_bLBtnDown)
		return FALSE;

	return CGXGridCore::CanSelectCurrentCell(bSelect, dwSelectRow, dwSelectCol, dwOldRow, dwOldCol);
}
template<class T>
void CGXGridCoreEx<T>::SetSelection(POSITION pos, ROWCOL nTop, ROWCOL nLeft, ROWCOL nBottom, ROWCOL nRight)
{
	if(m_bExcelLook)
	{
		if(pos == 0, nTop == 0, nLeft == 0, nBottom == 0, nRight == 0)
			CleanSelectionFrame(m_rgLastSelectionFrame);

		GX_CHECKIMP(m_pUserSelectRangeImp, "CGXGridCore::SetSelection");
		if (m_pUserSelectRangeImp)
			m_pUserSelectRangeImp->SetSelection(this, pos, nTop, nLeft, nBottom, nRight);
		return;
	}
	CGXGridCore::SetSelection(pos, nTop, nLeft, nBottom, nRight);
}
template<class T>
void CGXGridCoreEx<T>::SelectRange(const CGXRange& range, BOOL bSelect, BOOL bUpdate)
{
	if(m_bExcelLook)
	{
		BOOL bCtl = GetKeyState(VK_CONTROL) & 0x8000;
		CGXRangeList *pSelList = GetParam()->GetRangeList();
		if (pSelList && bCtl && (range.top <= GetHeaderRows()||range.left <= GetHeaderCols())
			&& pSelList->IsCellInList(range.top, range.left, m_SelRectId))
			return ;
	}

	CGXGridCore::SelectRange(range, bSelect, bUpdate);   
}
template<class T>
BOOL CGXGridCoreEx<T>::DoLButtonDblClk(UINT flags, CPoint point)
{
	CGXRange rg; 
	int ht = -1; 
	if(m_bExcelLook)
	{
		ROWCOL  nRow, nCol;

		if (!_doButtonDown1(this, flags, point, MK_MBUTTON | MK_RBUTTON, ht, nRow, nCol))
			return FALSE;

		if (ht == GX_HEADERHIT)
		{
			CGXRangeList *pSelList = GetParam()->GetRangeList();
			if(pSelList->GetCount() !=1)
				return FALSE;
			rg = pSelList->GetHead();
		}
	}
	BOOL bRet = CGXGridCore::DoLButtonDblClk(flags, point);
	if(m_bExcelLook && ht == GX_HEADERHIT)
	{
		SelectRange(rg);
		RedrawRowCol(rg,GX_INVALIDATE);
	}
	return bRet;
}
template<class T>
BOOL CGXGridCoreEx<T>::Copy()
{	
	if(IsActiveCurrentCell() || !m_bExcelLook)
		return CGXGridCore::Copy();
	BOOL bSwitchDirectPaste = FALSE;
	BOOL bDirectCutPaste = GetParam()->m_bDirectCutPaste;
	DWORD nClipboardFlags = m_nClipboardFlags;

	if(m_bExcelLook)
	{
		m_bCopyCut = TRUE;		
		if(GXGetAppData()->m_bFormulaEnabled && GetKeyState(VK_SHIFT) & 0x8000) //Use SHIFT to paste to outside app like Excel
		{
			GetParam()->m_bDirectCutPaste = FALSE;
			m_nClipboardFlags = GX_DNDTEXT ; 
			bSwitchDirectPaste = TRUE;
		}
	}
	BOOL bRet = CGXGridCore::Copy();
	if(m_bExcelLook)
	{
		if(bSwitchDirectPaste)
		{
			GetParam()->m_bDirectCutPaste = bDirectCutPaste;
			m_nClipboardFlags = nClipboardFlags;
			bSwitchDirectPaste = FALSE;
		}
		Redraw();
	}
	return bRet;
}
template<class T>
BOOL CGXGridCoreEx<T>::Cut() 
{
	if(IsActiveCurrentCell() || !m_bExcelLook)
		return CGXGridCore::Cut();

	BOOL bSwitchDirectPaste = FALSE;
	DWORD nClipboardFlags = m_nClipboardFlags;
	BOOL bDirectCutPaste = GetParam()->m_bDirectCutPaste;
	if(GXGetAppData()->m_bFormulaEnabled && GetKeyState(VK_SHIFT) & 0x8000) //Use SHIFT to paste to outside app like Excel
	{
		GetParam()->m_bDirectCutPaste = FALSE;
		m_nClipboardFlags = GX_DNDTEXT ; 
		bSwitchDirectPaste = TRUE;
	}
	BOOL bRet = Copy();
	GetParam()->m_bCut = TRUE;

	if(bSwitchDirectPaste)
	{
		GetParam()->m_bDirectCutPaste = bDirectCutPaste;
		m_nClipboardFlags = nClipboardFlags;
		bSwitchDirectPaste = FALSE;
	}
	Redraw();
	return bRet;
}
template<class T>
BOOL CGXGridCoreEx<T>::Paste()
{
	if(!m_bExcelLook)
		return CGXGridCore::Paste();

	//if(IsActiveCurrentCell())
	//	return FALSE;
	LockUpdate(TRUE);
	BOOL bSwitchDirectPaste = FALSE;
	DWORD nClipboardFlags = m_nClipboardFlags;
	BOOL bDirectCutPaste = GetParam()->m_bDirectCutPaste;
	if(!m_bCopyCut)
	{
		GetParam()->m_bDirectCutPaste = FALSE;
		m_nClipboardFlags = GX_DNDTEXT ; 
		bSwitchDirectPaste = TRUE;
	}
	BOOL bCut = GetParam()->m_bCut;
	CGXRangeList OldSelList;

	if(bCut)
	{
		POSITION pos = GetParam()->m_CopyRangeList.GetHeadPosition();
		while (pos)
			OldSelList.AddTail(new CGXRange(*GetParam()->m_CopyRangeList.GetNext(pos)));		
	}
	int nCount = (int)GetParam()->m_CopyRangeList.GetCount();
	BOOL bOneCell = FALSE;
	if(nCount == 1)
	{
		CGXRange* pRg = GetParam()->m_CopyRangeList.GetHead();
		bOneCell = (pRg->GetHeight() == 1) & (pRg->GetWidth() == 1);
	}

	m_bPaste = TRUE;
	BOOL bRet = CGXGridCore::Paste();
	m_bPaste = FALSE;

	CGXRangeList *pSelList = GetParam( )->GetRangeList( );
	POSITION pos = pSelList->GetHeadPosition();
	CGXRange rgPaste;
	if(pSelList->GetCount())
	{
		rgPaste = pSelList->GetHead();
		while (pos)
		{
			rgPaste.UnionRange( rgPaste, pSelList->GetNext(pos));
		}
	}
	//Can not paste on covered cells if more than one cell copied

	CGXRange rgCov;
	if(!bOneCell)
	{
		ROWCOL nRowNew, nColNew;
		rgPaste.GetFirstCell(nRowNew, nColNew);
		do
		{
			if(GetCoveredCellsRowCol(nRowNew, nColNew, rgCov))
			{
				Undo();
				CGXGridCore::SetSelection(NULL);
				if(bCut)
				{
					CGXRangeList* pSelList = GetParam()->GetRangeList();
					POSITION pos = OldSelList.GetHeadPosition();
					while (pos)
						pSelList->AddTail(new CGXRange(*OldSelList.GetNext(pos)));
					Cut();
					OldSelList.DeleteAll();
				}
				m_bDrawSelection = TRUE;
				LockUpdate(FALSE);
				Redraw();
				return FALSE;
			}
		}
		while(rgPaste.GetNextCell(nRowNew, nColNew));
	}

	if(bCut)
	{
		OpenClipboard();
		EmptyClipboard();
		CloseClipboard();
		m_bLBtnDown = FALSE;
		m_bCopyCut = FALSE;
	}

	CGXGridCore::SetSelection(NULL);
	m_bLBtnDown = FALSE;
	if(rgPaste.right > GetColCount()) rgPaste.right = GetColCount();
	if(rgPaste.bottom > GetRowCount()) rgPaste.bottom = GetRowCount();
	CGXRange rgSelection = rgPaste;
	if(rgPaste.GetHeight() == 1 && rgPaste.GetWidth() == 1 && 
		GetCoveredCellsRowCol(rgPaste.top, rgPaste.left, rgCov))
		rgSelection = rgCov;
	SelectRange(rgSelection);
	CGXRange rgleft = rgPaste;
	CGXRange rgtop = rgPaste;
	rgleft.left = rgleft.right = rgtop.top = rgtop.bottom = 0;
	LockUpdate(FALSE);
	Redraw();

	if(bSwitchDirectPaste)
	{
		GetParam()->m_bDirectCutPaste = bDirectCutPaste;
		m_nClipboardFlags = nClipboardFlags;
		bSwitchDirectPaste = FALSE;
	}	
	return bRet;
}
template<class T>
BOOL CGXGridCoreEx<T>::OnRButtonClickedRowCol(ROWCOL nRow, ROWCOL nCol, UINT nFlags, CPoint pt)
{
	// Unused:
	nRow, nCol, nFlags;
	if(m_bContextMenu)
	{
		ClientToScreen(&pt);
		((CWinAppEx*)AfxGetApp())->GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT_OGEX, pt.x, pt.y, this, TRUE);
	}
	return CGXGridCore::OnRButtonClickedRowCol(nRow, nCol, nFlags, pt);
}
template<class T>
void CGXGridCoreEx<T>::EnableContextMenuInEditCell(BOOL bMenu)
{
	CGXEditControl * pControl = NULL;
	if(bMenu)
		pControl = new CPopUpMenuEdit(this, GX_IDS_CTRL_EDIT);		
	else
		pControl = new CGXEditControl(this, GX_IDS_CTRL_EDIT);

	RegisterControl(GX_IDS_CTRL_EDIT, pControl);
	((CGXStatic*)pControl)->ImplementCellTips();
}
template<class T>
BOOL CGXGridCoreEx<T>::SetStyleRange(const CGXRange& range, const CGXStyle* pStyle, GXModifyType mt,
									 int nType, const CObArray* pCellsArray, UINT flags,	GXCmdType ctCmd)
{
	BOOL bRet = CGXGridCore::SetStyleRange(range, pStyle, mt, nType, pCellsArray, flags, ctCmd);
	if(m_bExcelLook && m_bPaste)
	{
		POSITION pos = GetParam( )->GetRangeList( )->AddTail(new CGXRange);
		SetSelection(pos, range.top, range.left, range.bottom, range.right);
	}
	return bRet;
}
template<class T>
BOOL CGXGridCoreEx<T>::SetStyleRange(const CGXRange& range, const CGXStyle& style, GXModifyType mt, int nType, UINT flags)
{
	return CGXGridCore::SetStyleRange(range, style, mt, nType, flags);
}
template<class T>
BOOL CGXGridCoreEx<T>::CopyCells(CGXRange rg, ROWCOL nRow, ROWCOL nCol, UINT flags)
{
	if(m_bExcelLook)
		SelectRange(CGXRange(nRow,nCol,nRow+rg.GetHeight()-1,nCol+rg.GetWidth()-1));
	return CGXGridCore::CopyCells(rg, nRow, nCol, flags);
}
template<class T>
BOOL CGXGridCoreEx<T>::MoveCells(CGXRange rg, ROWCOL nRow, ROWCOL nCol, CObject* pUndoInfo, UINT flags, GXCmdType ctCmd)
{
	if(m_bExcelLook)
		SelectRange(CGXRange(nRow,nCol,nRow+rg.GetHeight()-1,nCol+rg.GetWidth()-1));
	return CGXGridCore::MoveCells(rg, nRow, nCol, pUndoInfo, flags, ctCmd);
}
#ifdef TICKCOUNT
#define _TC_(f) f
#else
#define _TC_(f)
#endif
template<class T>
void CGXGridCoreEx<T>::ComposeStyleRowCol(ROWCOL nRow, ROWCOL nCol, CGXStyle* pStyle, BOOL bApplyStandard)
{
	if(!m_bExcelLook)
		return CGXGridCore::ComposeStyleRowCol(nRow, nCol, pStyle, bApplyStandard);

	ASSERT(nRow <= GetRowCount() && nCol <= GetColCount());

	_TC_(DWORD ti2 = GetTickCount());
	GetStyleRowCol(nRow, nCol, *pStyle, gxCopy, 0);
	_TC_(tick2 += GetTickCount()-ti2);

	// Check if you only need the value
	if (m_bOnlyValueNeeded && pStyle->GetIncludeValue())
		return;

	_TC_(DWORD ti3 = GetTickCount());

	ROWCOL nhCols = GetHeaderCols(),
		nhRows = GetHeaderRows();

	// Row and Column styles

	// Apply Row style
	if (nCol > nhCols)
		GetStyleRowCol(nRow, 0, *pStyle, gxApplyNew, -1);   // -1 defines range instead of cell value

	// Apply Column style
	if (nRow > nhRows)
		GetStyleRowCol(0, nCol, *pStyle, gxApplyNew, -1);

	// Apply table style
	if (nRow > nhRows && nCol > nhCols)
		GetStyleRowCol(0, 0, *pStyle, gxApplyNew, -1);

	_TC_(tick3 += GetTickCount()-ti3);

	// inherit attributes from base styles
	_TC_(DWORD ti4 = GetTickCount());
	pStyle->LoadBaseStyle(*m_pParam->m_pStylesMap);
	_TC_(tick4 += GetTickCount()-ti4);

	_TC_(DWORD ti5 = GetTickCount());
	// column headers and row headers
	if (nRow <= nhRows)
		pStyle->ChangeStyle(*m_pStyleColHeader, gxApplyNew);

	if (nCol <= nhCols)
		pStyle->ChangeStyle(*m_pStyleRowHeader, gxApplyNew);
	_TC_(tick5 += GetTickCount()-ti5);

	_TC_(DWORD ti6 = GetTickCount());
	// set value, if column or row header
	if ((nRow == 0 || nCol == 0) && !pStyle->GetIncludeValue())
	{
		if (nRow == 0 && nCol > 0 && GetParam()->IsNumberedColHeaders())
		{
			// Column header in format A, B, ..., AA, ..., AAA, ... ZZZZZ

			TCHAR s[10], t[10];
			int n;
			for (n = 0; n < 9; n++)
			{
				nCol--;
				s[n] = (TCHAR) ((nCol%26) + _T('A'));
				if ((nCol = nCol/26) == 0)
					break;
			}

			// reverse string
			int i;
			for (i = 0; i < n+1; i++)
				t[i] = s[n-i];
			t[i] = 0;

			pStyle->SetValue(t);
		}
		else if (nCol == 0 && nRow > 0 && GetParam()->IsNumberedRowHeaders())
		{
			// Row header is simple a number
			pStyle->SetValue(nRow);
		}
	}
	_TC_(tick6 += GetTickCount()-ti6);

	_TC_(DWORD ti7 = GetTickCount());
	if (bApplyStandard)
		pStyle->ChangeStyle(*m_pStyleStandard, gxApplyNew);
	//removed from old code
	//if (GetParam()->m_bDirectCutPaste && GetParam()->m_bCut && GetParam()->m_CopyRangeList.IsCellInList(nRow, nCol))
	//{
	//	pStyle->SetInterior(CGXBrush().SetPattern(17).SetColor(RGB(192,192,192)));
	//}

	if(!(IsCurrentCell(nRow, nCol) && pStyle->GetIncludeControl() && GetRegisteredControl(pStyle->GetControl())->IsActive()))
	{
		if(pStyle->GetIncludeValue() 
			&& pStyle->GetIncludeNegativeStateColor() 
			&& _gxttof(pStyle->GetValue()) < 0  
			)
		{
			DWORD csColor ;
			csColor = pStyle->GetNegativeStateColor();
			pStyle->SetTextColor(csColor);
		}
	}

	_TC_(tick7 += GetTickCount()-ti7);
}
template<class T>
BOOL CGXGridCoreEx<T>::OnGridKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if(m_bExcelLook)
	{
		if(m_bCopyCut )
		{
			if(nChar == VK_RETURN || nChar == VK_ESCAPE)
			{
				if (nChar == VK_RETURN)
					Paste();
				CleanCopyCutSelection();
				return FALSE;
			}
		}
		else
			Redraw();
	}
	return CGXGridCore::OnGridKeyDown(nChar, nRepCnt, nFlags);
}
template<class T>
BOOL CGXGridCoreEx<T>::ProcessKeys(CWnd* pSender, UINT nMessage, UINT nChar, UINT nRepCnt, UINT flags)
{
	BOOL bRet = CGXGridCore::ProcessKeys(pSender, nMessage, nChar, nRepCnt, flags);
	if(m_bExcelLook && m_bCopyCut && IsActiveCurrentCell())
		CleanCopyCutSelection();
	CGXRange rg;
	if(nMessage == WM_CHAR && IsActiveCurrentCell() && 
		(m_rgLastSelectionFrame.GetWidth() ==1 && m_rgLastSelectionFrame.GetHeight() == 1 || 
		IsCurrentCell(m_rgLastSelectionFrame.bottom, m_rgLastSelectionFrame.right) ||
		GetCoveredCellsRowCol(m_rgLastSelectionFrame.top, m_rgLastSelectionFrame.left, rg) != NULL &&
		*GetCoveredCellsRowCol(m_rgLastSelectionFrame.top, m_rgLastSelectionFrame.left, rg)== m_rgLastSelectionFrame))
		CleanSelectionFrame(CGXRange(m_rgLastSelectionFrame.bottom, m_rgLastSelectionFrame.right));
	return bRet;
}
template<class T>
void CGXGridCoreEx<T>::CleanCopyCutSelection()
{
	m_bCopyCut = FALSE;
	GetParam()->m_bCut = FALSE;
	GetParam()->m_CopyRangeList.DeleteAll();
	OpenClipboard();
	EmptyClipboard();
	CloseClipboard();
	if(GXGetAppData()->m_bFormulaEnabled)
		this->Recalc();
	Redraw();
}

template<class T>
LRESULT CGXGridCoreEx<T>::OnStyleChanged()
{
	if(m_bExcelLook)
	{
		CGXHeaderExcel* pHeader = ((CGXHeaderExcel*)GetRegisteredControl(GX_IDS_CTRL_HEADER));
		pHeader->SetColors(_T("Black"));
		GetParam()->GetProperties()->SetColor(GX_COLOR_GRIDLINES, pHeader->GetColor(Separator));
		GetParam()->GetProperties()->SetColor(GX_COLOR_BACKGROUND, pHeader->GetColor(Row));
		Redraw();
	}
	return 0;
}

typedef CGXGridCoreEx<CGXGridView> 	CGXGridViewEx;
typedef CGXGridCoreEx<CGXGridWnd> 	CGXGridWndEx;

} // namespace ogex

#endif // __GXGRIDCOREEX__H__
