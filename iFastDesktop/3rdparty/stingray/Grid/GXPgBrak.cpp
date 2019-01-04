///////////////////////////////////////////////////////////////////////////////
// CGXPageBreakPlugin.cpp : implementation file
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

#ifndef _GXVW_H_
#include "grid\gxvw.h"
#endif

#ifndef _GXPGBRAK_H_
#include "grid\gxpgbrak.h"
#endif//_GXPGBRAK_H_

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

using namespace std;

#pragma warning (disable: 4389) // Signed/Unsigned Mismatch

/////////////////////////////////////////////////////////////////////////////
// CGXPageBreakPlugin
HCURSOR CGXPageBreakPlugin::m_hV2Arrow = ::LoadCursor(NULL, IDC_SIZENS);
HCURSOR CGXPageBreakPlugin::m_hH2Arrow = ::LoadCursor(NULL, IDC_SIZEWE);

CGXPageBreakPlugin::CGXPageBreakPlugin()
{
	m_bSkipOtherPlugins = FALSE;
	m_bExitMessage = FALSE;

	m_bDrawPageBreak = FALSE;
	m_nPageBreakLineWidth = 4;
	m_clrCustomBreakLine = RGB(0, 0, 255);
	m_clrDefaultBreakLine = RGB(0, 255, 255);
	m_clrLabel = RGB(0, 0, 255);

	m_pGrid = NULL;
	m_pView = NULL;

	m_bFitToPages = FALSE;
	m_nColPages = m_nRowPages = 1;

	m_pageSize = CSize(0, 0);

}
 
CGXPageBreakPlugin::~CGXPageBreakPlugin()
{
	// make sure Detach won't get called
	 m_hWnd = NULL;
}
 

BEGIN_MESSAGE_MAP(CGXPageBreakPlugin, CWnd)
	//{{AFX_MSG_MAP(CGXPageBreakPlugin)
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
//	ON_WM_VSCROLL()
//	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CGXPageBreakPlugin message handlers

LRESULT CGXPageBreakPlugin::WindowProc(UINT /*message*/, WPARAM /*wParam*/, LPARAM /*lParam*/) 
{
	return 0;
}

//@doc CGXPageBreakPlugin
//@mfunc This is the starting point of message handling of this class. This function is 
// called by the view class it plugged into. It is similar to OnWndMsg function of CWnd
// class. It always reset the m_bSkipOtherPlugin and m_bExitMessage to FALSE before 
// delegate the message to CWnd::OnWndMsg function.
//@rdesc BOOL If not in page break mode, this function do nothing and just return FALSE, 
// otherwise, it return the return value of OnWndMsg function.
//@parm UINT message
//@parm  WPARAM wParam
//@parm  LPARAM lParam
//@parm  LRESULT *pResult
BOOL CGXPageBreakPlugin::HandleMessage(UINT message, WPARAM wParam, LPARAM lParam, LRESULT *pResult)
{
	m_bSkipOtherPlugins = FALSE;
	m_bExitMessage = FALSE;

	if( ! m_bDrawPageBreak ) // If we are not in page break mode, do nothing.
		return FALSE;

	return CWnd::OnWndMsg(message, wParam, lParam, pResult);
}

//@doc CGXPageBreakPlugin
//@mfunc This function connect this plugin into the view class that passed in as the unique
// argument. The view class has to be derived from CGXGridCore and CGXView class.
//@rdesc void 
//@parm CGXGridCore *pView The view class this plugin attached to
void CGXPageBreakPlugin::Plugin(CGXGridCore *pView) // QA 22649
{
	ASSERT(pView != NULL );
 
	m_pGrid = (CGXGridCore*) pView;
	m_pView = dynamic_cast<CGXView*>(pView);    
	m_hWnd = m_pView->GetSafeHwnd();
}

//@doc CGXPageBreakPlugin
//@mfunc If the user is dragging the page break line, this handle do the visual feedback
// as drawing the hint break line and showing where the break line will be located when
// user release the left button. Otherwise, this function do nothing.
//@rdesc void 
//@parm UINT nFlags
//@parm  CPoint point
void CGXPageBreakPlugin::OnLButtonDown(UINT /*nFlags*/, CPoint point) 
{
	CRect rc;
	int nHit = HitTestPageBreak(point, &rc);
	int nWidth = rc.Width();
	int nHeight = rc.Height();
	if( nHit == HORZEDGE || nHit == VERTEDGE )
	{
		if( ::GetCapture() != NULL )
			return;
		
		m_pView->SetCapture();
		m_pView->UpdateWindow();

		CRect rectSave = rc;

		int offset;
		if( nHit == HORZEDGE )
			offset = point.y - rc.top;
		else
			offset = point.x - rc.left;

		CDC* pDrawDC = m_pView->GetDC();

		CRect rcOld, rectLast(0, 0, 0, 0);
		CSize	size(rc.Width(), rc.Height());

		BOOL bMoved = FALSE;		
		BOOL bFinalErase, bErase;

		bFinalErase = bErase = FALSE;
		pDrawDC->DrawDragRect(rc, size, rectLast, size);
		
		rectLast = rc;

		AfxLockTempMaps();

		// Get messages utils capture lostor cancelled/accepted
		for(;;)
		{
			MSG msg;
			VERIFY(::GetMessage(&msg, NULL, 0, 0));
			if( CWnd::GetCapture() != m_pView )
				break;
			switch(msg.message)
			{
			case WM_LBUTTONUP:
			case WM_MOUSEMOVE:
				rcOld = rc;
				if( nHit == HORZEDGE )
				{
					rc.top = (int)(short)HIWORD(msg.lParam) - offset;
					rc.top = max(rc.top, m_pGrid->CalcTopFromClientRow(m_pGrid->GetFrozenRows() + 1) );
					rc.top = min(rc.top, m_pGrid->CalcTopFromClientRow(m_pGrid->GetClientRow(m_pGrid->GetRowCount() + 1)) - nHeight/2);
					rc.bottom = rc.top + nHeight;
				}
				else
				{
					rc.left = (int)(short)LOWORD(msg.lParam) - offset;
					rc.left = max(rc.left, m_pGrid->CalcLeftFromClientCol(m_pGrid->GetFrozenCols() + 1) );
					rc.left = min(rc.left, m_pGrid->CalcLeftFromClientCol(m_pGrid->GetClientCol(m_pGrid->GetColCount() + 1)) - nWidth/2);
					rc.right = rc.left + nWidth;
				}

				AdjustRect(&rc, nHit);

				bFinalErase = (msg.message == WM_LBUTTONUP);
				if( !rcOld.EqualRect(rc) || bFinalErase )
				{
					if( bMoved || bFinalErase )
					{
						bErase = TRUE;
						pDrawDC->DrawDragRect(rcOld, size, rectLast, size);
						rectLast = rcOld;
					}
					if( msg.message != WM_LBUTTONUP )
						bMoved = TRUE;
					if( bFinalErase )
					{
						goto ExitLoop;
					}
					
					if( !rcOld.EqualRect(rc) )
					{
						bErase = FALSE;
						pDrawDC->DrawDragRect(rc, size, rectLast, size);
						rectLast = rc;
					}
				}
				break;
			case WM_KEYDOWN:
				if( msg.wParam != VK_ESCAPE )
					break;
			case WM_RBUTTONDOWN:
				if( bMoved )
				{
					bErase = bFinalErase = TRUE;
					pDrawDC->DrawDragRect(rc, size, rectLast, size);
					rectLast = rc;
				}
				rc = rectSave;
				goto ExitLoop;
			default:
				DispatchMessage(&msg);
				break;
			}
		}
ExitLoop:
		m_pView->ReleaseDC(pDrawDC);
		ReleaseCapture();
		AfxUnlockTempMaps();

		m_bExitMessage = TRUE;

		if( bMoved )
		{
			if(!m_bFitToPages )
				UpdatePageBreak(rc, nHit, rectSave);
			m_pView->Invalidate();
		}
	}
}
 
//@doc CGXPageBreakPlugin
//@mfunc Keep track the user's mouse position and set proper cursor.
//@rdesc void 
//@parm UINT nFlags
//@parm  CPoint point
void CGXPageBreakPlugin::OnMouseMove(UINT /*nFlags*/, CPoint point) 
{
	int nHit = HitTestPageBreak(point, NULL);

	if( nHit == HORZEDGE )
	{
		m_bExitMessage = TRUE;
		::SetCursor(m_hV2Arrow);
	}
	else if( nHit == VERTEDGE )
	{
		m_bExitMessage = TRUE;
		::SetCursor(m_hH2Arrow);
	}
}
 
//@doc CGXPageBreakPlugin
//@mfunc Do the hit test of the point against the existing page break lines.
//@rdesc int return NONEDGE, HORZEDGE or VERTEDGE
//@parm CPoint pt Point to test for
//@parm  LPRECT pRect If the return value is HORZEDGE or VERTEDGE, then the argument 
// contains the rectangle area that the thick page break line will be drawing, otherwise
// the data is invalid.
int CGXPageBreakPlugin::HitTestPageBreak(CPoint pt, LPRECT pRect)
{
	vector<CGXBreakLineInfo>::iterator it;
	for(it = m_vecPageCol.begin(); it != m_vecPageCol.end(); it++)
	{
		if( (*it).rc.PtInRect(pt) )
		{
			if( pRect != NULL )
				*pRect = (*it).rc;
			return VERTEDGE;
		}
	}
	for(it = m_vecPageRow.begin(); it != m_vecPageRow.end(); it++)
	{
		if( (*it).rc.PtInRect(pt) )
		{
			if( pRect != NULL )
				*pRect = (*it).rc;
			return HORZEDGE;
		}
	}
	return NONEEDGE;
}

//@doc CGXPageBreakPlugin
//@mfunc When user drags the page break line, the page break line only falls on the 
// on the position of grid line, this function do the adjustment for the draging line.
//@rdesc void 
//@parm LPRECT pRect  The draging line as a thin rectangle.
//@parm  int nHitTest Indicate whether user is dragging vertcal or horizontal break line.
void CGXPageBreakPlugin::AdjustRect(LPRECT pRect, int nHitTest)
{
	CPoint pt;
	int nWidth = pRect->right - pRect->left;
	int nHeight = pRect->bottom - pRect->top;
	if( nHitTest == HORZEDGE )
	{
		pt.x = 0;
		pt.y = (pRect->top + pRect->bottom)/2;
		
		BOOL bBottom = FALSE;
		ROWCOL nRow = m_pGrid->CalcClientRowFromPt(pt);
		if( pRect->bottom >= m_pGrid->CalcTopFromClientRow(
					m_pGrid->GetClientRow(m_pGrid->GetRowCount() + 1)) )
		{
			nRow = m_pGrid->GetClientRow(m_pGrid->GetRowCount() + 1);
			bBottom = TRUE;
		}
		int y = m_pGrid->CalcTopFromClientRow(nRow);
		int cy = m_pGrid->GetRowHeight(m_pGrid->GetRow(nRow));
		if( bBottom )
			cy = 0;
		if( pt.y - y <= cy/2 )
		{
			// Choose top
			pRect->top = y - max(1, nHeight/2);
			pRect->bottom = pRect->top + nHeight;
		}
		else
		{
			// Choose bottom
			pRect->top = y + cy - max(1, nHeight/2);
			pRect->bottom = pRect->top + nHeight;
		}
	}
	else if( nHitTest == VERTEDGE )
	{
		pt.x = (pRect->left + pRect->right)/2;
		pt.y = 0;

		BOOL bRight = FALSE;
		ROWCOL nCol = m_pGrid->CalcClientColFromPt(pt);
		if( pRect->right > m_pGrid->CalcLeftFromClientCol(
					m_pGrid->GetClientCol(m_pGrid->GetColCount() + 1) ))
		{
			nCol = m_pGrid->GetClientCol(m_pGrid->GetColCount() + 1);
			bRight = TRUE;
		}
		int x = m_pGrid->CalcLeftFromClientCol(nCol);
		int cx = m_pGrid->GetColWidth(m_pGrid->GetCol(nCol));
		if( bRight )
			cx = 0;
		if( pt.x - x <= cx/2 )
		{
			// Choose left
			pRect->left = x - max(1, nWidth/2);
			pRect->right = pRect->left + nWidth;
		}
		else
		{
			// Choose right
			pRect->left = x + cx - max(1, nWidth/2);
			pRect->right = pRect->left + nWidth;
		}
	}
	else
	{
		ASSERT(FALSE);
	}
}

//@doc CGXPageBreakPlugin
//@mfunc This function calculate the page break line position in term of
// the grid cell row and column index. It go though similar steps as the 
// printing preview to calculate the page break position.
//@rdesc void 
void CGXPageBreakPlugin::CreatePageBreak()
{
	CPrintInfo* pPrintInfo = new CPrintInfo;
	pPrintInfo->m_pPD->SetHelpID(AFX_IDD_PRINTSETUP);
	pPrintInfo->m_pPD->m_pd.Flags |= PD_PRINTSETUP;
	pPrintInfo->m_pPD->m_pd.Flags &= ~PD_RETURNDC;

	pPrintInfo->m_bPreview = TRUE;
	
	CPreviewDC* pPreviewDC = new CPreviewDC;
	
	BOOL bRet = m_pView->OnPreparePrinting(pPrintInfo);
	//ASSERT(bRet);

	if ( bRet )
	{
		pPreviewDC->SetAttribDC(pPrintInfo->m_pPD->m_pd.hDC);
		pPreviewDC->m_bPrinting = TRUE;

		HDC hDC = ::GetDC(m_hWnd);
		pPreviewDC->SetOutputDC(hDC);

		m_pView->OnBeginPrinting(pPreviewDC, pPrintInfo);
 
	#ifdef _DEBUG
		TRACE0("Final Row break");
		int i; 
		for(i = 0; i < m_pGrid->m_awPageFirstRow.GetSize(); i++)
			TRACE1(" %d ", m_pGrid->m_awPageFirstRow[i]);
		TRACE0("\n");
		
		TRACE0("Final Col break");
		for(i = 0; i < m_pGrid->m_awPageFirstCol.GetSize(); i++)
			TRACE1(" %d ", m_pGrid->m_awPageFirstCol[i]);
		TRACE0("\n");
	#endif
 
		m_pView->OnEndPrinting(pPreviewDC, pPrintInfo);

		pPreviewDC->ReleaseOutputDC();
		::ReleaseDC(m_hWnd, hDC);
	}

		delete pPrintInfo;
		delete pPreviewDC;
}
 

//@doc CGXPageBreakPlugin
//@mfunc This function is called when user draging the page break line to a different
// position and release the mouse. This function will update the page break information
// as removing the old invalid page break index and add proper new page break index.
//@rdesc void 
//@parm LPRECT pRect The new line as a thin rectangle
//@parm  int nHitTest Indicate whether it is vertical or horizontal line
//@parm  LPRECT pInitRect The initial line as a thin rectangle
void CGXPageBreakPlugin::UpdatePageBreak(LPRECT pRect, int nHitTest, LPRECT pInitRect)
{
	AdjustRect(pRect, nHitTest);

	CRect rc = *pRect;
	CRect rc1 = *pInitRect;
	if( nHitTest == HORZEDGE )
	{
		CPoint pt(0, (rc.top + rc.bottom)/2);
		CPoint ptInit(0, (rc1.top + rc1.bottom)/2);
		ROWCOL nRow = m_pGrid->CalcClientRowFromPt(pt);
		if( pRect->bottom >= m_pGrid->CalcTopFromClientRow(
						m_pGrid->GetClientRow(m_pGrid->GetRowCount() + 1) ))
			nRow = GX_INVALID;

		ROWCOL nRowInit = m_pGrid->CalcClientRowFromPt(ptInit);
		if( pInitRect->bottom >= m_pGrid->CalcTopFromClientRow(
						m_pGrid->GetClientRow(m_pGrid->GetRowCount() + 1) ))
			nRowInit = GX_INVALID;

		// Convert it into actuall row index
		if( nRow != GX_INVALID )
			nRow = m_pGrid->GetRow(nRow);
		if( nRowInit != GX_INVALID )
			nRowInit = m_pGrid->GetRow(nRowInit);
		if( nRow != nRowInit )
		{
			CDWordArray& awRowBreaks = m_pGrid->GetParam()->GetProperties()->GetRowBreakArray();
			if( nRow != GX_INVALID )
			{
				CDWordArray arr;
				int i;
				for(i = 0; i < awRowBreaks.GetSize(); i++)
				{
					if( awRowBreaks[i] < nRow )
					{
						if( awRowBreaks[i] != nRowInit)
							arr.Add(awRowBreaks[i]);
					}
					else
						break;
				}
				if( nRow != m_pGrid->GetFrozenRows() + 1)
					arr.Add(nRow);
				for(; i < awRowBreaks.GetSize(); i++)
				{
					if( awRowBreaks[i] > nRow )
					{
						if( awRowBreaks[i] != nRowInit)
							arr.Add(awRowBreaks[i]);
					}
				}
				awRowBreaks.RemoveAll();
				awRowBreaks.Copy(arr);
			}
			else if( nRowInit != GX_INVALID )
			{
				for(int i = 0; i < awRowBreaks.GetSize(); i++)
				{
					if( awRowBreaks[i] == nRowInit )
					{
						awRowBreaks.RemoveAt(i);
						break;
					}
				}
			}
#ifdef _DEBUG
			TRACE0("Row breaks ");
			for(int i = 0; i < awRowBreaks.GetSize(); i++)
			{
				TRACE1(" %d ", awRowBreaks[i]);
			}
			TRACE0("\n");
#endif
			CreatePageBreak();
		}
	}
	else if (nHitTest == VERTEDGE )
	{
		CPoint pt((rc.left + rc.right)/2, 0);
		CPoint ptInit((rc1.left + rc1.right)/2, 0);
		ROWCOL nCol = m_pGrid->CalcClientColFromPt(pt);
		if( pRect->right >= m_pGrid->CalcLeftFromClientCol(
						m_pGrid->GetClientCol(m_pGrid->GetColCount() + 1) ))
			nCol = GX_INVALID;
		ROWCOL nColInit = m_pGrid->CalcClientColFromPt(ptInit);
		if( pInitRect->right >= m_pGrid->CalcLeftFromClientCol(
						m_pGrid->GetClientCol(m_pGrid->GetColCount() + 1) ))
			nColInit = GX_INVALID;
		
		// Convert into actual col
		if( nCol != GX_INVALID )
			nCol = m_pGrid->GetCol(nCol);
		if( nColInit != GX_INVALID )
			nColInit = m_pGrid->GetCol(nColInit);
		if( nCol != nColInit )
		{
			CDWordArray& awColBreaks = m_pGrid->GetParam()->GetProperties()->GetColBreakArray();
			if( nCol != GX_INVALID )
			{
				CDWordArray arr;
				int i;
				for(i = 0; i < awColBreaks.GetSize(); i++)
				{
					if( awColBreaks[i] < nCol )
					{
						if( awColBreaks[i] != nColInit)
							arr.Add(awColBreaks[i]);
					}
					else
						break;
				}
				if( nCol != m_pGrid->GetFrozenCols() + 1 )
					arr.Add(nCol);
				for(; i < awColBreaks.GetSize(); i++)
				{
					if( awColBreaks[i] > nCol )
					{
						if( awColBreaks[i] != nColInit)
							arr.Add(awColBreaks[i]);
					}
				}
				awColBreaks.RemoveAll();
				awColBreaks.Copy(arr);
			}
			else if( nColInit != GX_INVALID )
			{
				for(int i = 0; i < awColBreaks.GetSize(); i++)
				{
					if( awColBreaks[i] == nColInit )
					{
						awColBreaks.RemoveAt(i);
						break;
					}
				}
			}

#ifdef _DEBUG
			TRACE0("Col breaks ");
			for(int i = 0; i < awColBreaks.GetSize(); i++)
			{
				TRACE1(" %d ", awColBreaks[i]);
			}
			TRACE0("\n");
#endif
			CreatePageBreak();
		}
	} 
	else
	{
		ASSERT(FALSE);
	}
}

//@doc CGXPageBreakPlugin
//@mfunc This function calculate the final page break line position in term of the
// client coordinate and then draw the page break line and the labels.
//@rdesc void 
//@parm CDC *pDC The DC the page break line drawn on.
void CGXPageBreakPlugin::DrawPageBreak(CDC *pDC)
{
	CalcFinalPosition();

	//CGXProperties* pProp = m_pGrid->GetParam()->GetProperties(); // C4189 Unused

	int nTop = m_pGrid->CalcTopFromClientRow(m_pGrid->GetFrozenRows() + 1);
	int nLeft = m_pGrid->CalcLeftFromClientCol(m_pGrid->GetFrozenCols() + 1);

	CBrush brhCustom(m_clrCustomBreakLine);
	CBrush brhDefault(m_clrDefaultBreakLine);

	vector<CGXBreakLineInfo>::iterator it;

	if( m_vecPageRow.size() > 0 )
	{
		for(it = m_vecPageRow.begin(); it != m_vecPageRow.end(); it++)
		{
			if( (*it).bCustom )
				pDC->FillRect((*it).rc, &brhCustom);
			else
				pDC->FillRect((*it).rc, &brhDefault);
		}
	}
	if( m_vecPageCol.size() > 0 )
	{
		for(it = m_vecPageCol.begin(); it != m_vecPageCol.end(); it++)
		{
			if( (*it).bCustom )
				pDC->FillRect((*it).rc, &brhCustom);
			else
				pDC->FillRect((*it).rc, &brhDefault);
		}
	}
	brhCustom.DeleteObject();
	brhDefault.DeleteObject();

	if( m_vecPageLabels.size() > 0 )
	{
		CRect rc;

		vector<CGXPageLabelInfo>::iterator it;

		int nOldMode = pDC->SetBkMode(TRANSPARENT);

		CFont font;
		font.CreatePointFont(200, _T("Arial"), pDC);
		CFont* pOldFont = (CFont*)pDC->SelectObject(&font);

		COLORREF oldClr = pDC->SetTextColor(m_clrLabel);

		for(it = m_vecPageLabels.begin(); it != m_vecPageLabels.end(); it++)
		{
			CSize size = pDC->GetTextExtent((*it).strText);
			rc = (*it).rc;
			rc.left = max(rc.left, nLeft);
			rc.top = max(rc.top, nTop);
			//We need to do clipping so that it will not draw on top of the cell header
			pDC->ExtTextOut(((*it).rc.left + (*it).rc.right - size.cx)/2, 
							((*it).rc.top + (*it).rc.bottom - size.cy)/2,
							ETO_CLIPPED, rc, (*it).strText, NULL);
		}

		pDC->SetTextColor(oldClr);
		pDC->SetBkMode(nOldMode);
		pDC->SelectObject(pOldFont);
		font.DeleteObject();
	}
} 

//@doc CGXPageBreakPlugin
//@mfunc Calculate the final page break line position in term of the client coordinate.
// Note every page break line is stored as a thin rectangle so it is easy to do the hit
// test. The drawing of the these lines are actually done by using FillRect with the given
// color.
//@rdesc void 
void CGXPageBreakPlugin::CalcFinalPosition()
{
	m_vecPageRow.clear();
	m_vecPageCol.clear();
	m_vecPageLabels.clear();

	CGXProperties* pProp = m_pGrid->GetParam()->GetProperties();

	int nTop = m_pGrid->CalcTopFromClientRow(m_pGrid->GetFrozenRows() + 1);
	int nLeft = m_pGrid->CalcLeftFromClientCol(m_pGrid->GetFrozenCols() + 1);
	int nRight;
	int nBottom;

	CDWordArray& awRowIndex = m_pGrid->m_awPageFirstRow;
	CDWordArray& awColIndex = m_pGrid->m_awPageFirstCol;

	if( awRowIndex.GetSize() != 0 && awColIndex.GetSize() != 0)
	{
		CRect rc;
		CString s;
		 
		GetClientRect(&rc);

		// Create the page break line
		int i;
		for(i = 1; i < awRowIndex.GetSize(); i++)
		{
			ASSERT(awRowIndex[i] > 0 );
			if( awRowIndex[i] < m_pGrid->GetTopRow() )
				continue;
			nRight = min(m_pGrid->CalcLeftFromClientCol(m_pGrid->GetClientCol(m_pGrid->GetColCount() + 1)), rc.right);
			nBottom = m_pGrid->CalcTopFromClientRow(m_pGrid->GetClientRow(min(awRowIndex[i], m_pGrid->GetRowCount() + 1) ) );
			
			m_vecPageRow.push_back(CGXBreakLineInfo(
										CRect(nLeft, nBottom - max(1, m_nPageBreakLineWidth/2),
										nRight, nBottom + max(1, m_nPageBreakLineWidth/2)), 
										IsValueInArray(pProp->GetRowBreakArray(), 
														min(awRowIndex[i], m_pGrid->GetRowCount() + 1))
										));
		}

		for(i = 1; i < awColIndex.GetSize();  i++)
		{
			ASSERT(awColIndex[i] > 0 );
			if( awColIndex[i] < m_pGrid->GetLeftCol() )
				continue;
			nRight = m_pGrid->CalcLeftFromClientCol(
						m_pGrid->GetClientCol(min(awColIndex[i], m_pGrid->GetColCount() + 1) ) );
			nBottom = min(m_pGrid->CalcTopFromClientRow(m_pGrid->GetClientRow(m_pGrid->GetRowCount() + 1)), rc.bottom);
			m_vecPageCol.push_back(CGXBreakLineInfo(
										CRect(nRight - max(1, m_nPageBreakLineWidth/2),
										    nTop, nRight + max(1, m_nPageBreakLineWidth/2), nBottom),
										IsValueInArray(pProp->GetColBreakArray(), 
														min(awColIndex[i], m_pGrid->GetColCount() + 1))
										));
		}

		int t = 0;
		for(i = 1; i < awRowIndex.GetSize(); i++)
		{
			ASSERT(awRowIndex[i] > 0 );
			if( awRowIndex[i] < m_pGrid->GetTopRow() )
				continue;

			ASSERT(t < m_vecPageRow.size());
			rc.bottom = m_vecPageRow[t].rc.top;

			if( t == 0 )
			{
//				rc.top = nTop;
				ASSERT(awRowIndex[i - 1] < awRowIndex[i]);
				rc.top = rc.bottom - m_pGrid->CalcSumOfRowHeights(awRowIndex[i - 1], awRowIndex[i] - 1);
			}
			else
				rc.top = m_vecPageRow[t - 1].rc.bottom;

			t++;

			int k = 0;
			for(int j = 1; j < awColIndex.GetSize(); j++)
			{
				ASSERT(awColIndex[j] > 0 );
				if( awColIndex[j] < m_pGrid->GetLeftCol())
					continue;

				ASSERT(k < m_vecPageCol.size());
				rc.right = m_vecPageCol[k].rc.left;

				if( k == 0 )
				{
					//rc.left = nLeft;
					ASSERT(awColIndex[j - 1] < awColIndex[j]);
					rc.left = rc.right - m_pGrid->CalcSumOfColWidths(awColIndex[j - 1], awColIndex[j] - 1);
				}
				else
					rc.left = m_vecPageCol[k - 1].rc.right;

				k++;

				if( pProp->GetPageOrder() == 0 )
					s.Format(_T(" Page %d "), (i - 1) * (awColIndex.GetSize() - 1) + j);
				else
					s.Format(_T(" Page %d "), (j - 1) * (awRowIndex.GetSize() - 1) + i);

				m_vecPageLabels.push_back(CGXPageLabelInfo(rc, s));
			}
		}
		
/*		int nRow, nCol;
		for(i = 1; i < awRowIndex.GetSize(); i++)
		{
			ASSERT(awRowIndex[i] > 0 );

			if( awRowIndex[i] < m_pGrid->GetTopRow() )
				continue;
			
			nRow = awRowIndex[i];
			if( nRow > m_pGrid->GetRowCount() )
				nRow = m_pGrid->GetRowCount() + 1;
			rc.bottom = m_pGrid->CalcTopFromClientRow(m_pGrid->GetClientRow(nRow));

			int nHeight = m_pGrid->CalcSumOfRowHeights(awRowIndex[i - 1] + ((i > 1 )? 1 : 0), nRow);

			rc.top = rc.bottom - nHeight;

			for(int j = 1; j < awColIndex.GetSize(); j++)
			{
				ASSERT(awColIndex[j] > 0 );

				if( awColIndex[j] < m_pGrid->GetLeftCol() )
					continue;

				nCol = awColIndex[j];
				if( nCol > m_pGrid->GetColCount() )
					nCol = m_pGrid->GetColCount() + 1;
				rc.right = m_pGrid->CalcLeftFromClientCol(m_pGrid->GetClientCol(nCol));

				int nWidth = m_pGrid->CalcSumOfColWidths(awColIndex[j - 1] + 1, nCol);

				rc.left = rc.right - nWidth;

				if( pProp->GetPageOrder() == 0 )
					s.Format(_T(" Page %d "), (i - 1) * (awColIndex.GetSize() - 1) + j);
				else
					s.Format(_T(" Page %d "), (j - 1) * (awRowIndex.GetSize() - 1) + i);

				m_vecPageLabels.push_back(CGXPageLabelInfo(rc, s));
			}
		}
*/
	}

}

//@doc CGXPageBreakPlugin
//@mfunc Test if a given value is in the array.
//@rdesc BOOL Return TRUE if the value is in the array, otherwise return FALSE.
//@parm const CDWordArray &aw The array to look into.
//@parm  int value The value to test against.
BOOL CGXPageBreakPlugin::IsValueInArray(const CDWordArray &aw, int value)
{
	for(int i = 0; i < aw.GetSize(); i++)
		if( value == aw[i] )
			return TRUE;
	return FALSE;
}
 
//@doc CGXPageBreakPlugin
//@mfunc Call this function to ask this plugin to draw anything it need to draw.
//@rdesc void 
//@parm CDC *pDC The place this plugin to draw to.
void CGXPageBreakPlugin::DoDraw(CDC *pDC)
{
	if( m_bDrawPageBreak )
		DrawPageBreak(pDC);
}

//@doc CGXPageBreakPlugin
//@mfunc Toggle the page break mode for this plugin.
//@rdesc void 
//@parm BOOL bPageBreakMode
void CGXPageBreakPlugin::SetPageBreakMode(BOOL bPageBreakMode)
{
	m_bDrawPageBreak = bPageBreakMode;
	if( m_bDrawPageBreak )
		CreatePageBreak();

	m_pGrid->Invalidate();
}
//@doc CGXPageBreakPlugin
//@mfunc This handler recreate the page break if we resize the cell while in page
//break mode, otherwise does nothing.<nl>
//Please refer to CWnd::OnLButtonUp for the mean of the arguments.
//@rdesc void 
//@parm UINT nFlags
//@parm  CPoint
void CGXPageBreakPlugin::OnLButtonUp(UINT nFlags, CPoint pt)
{
	if( m_pGrid->m_bTracking )
	{
		if( m_bDrawPageBreak )
		{
			// Let the main view first calculate the changed cell size
			m_pGrid->DoLButtonUp(nFlags, pt);
			CreatePageBreak();
		}
	}
}
/*
//@doc CGXPageBreakPlugin
//@mfunc This function redraw the column header when user scroll the window in page break
//mode. If the application is not in page break mode, it does nothing. <nl>
//Please refer to CWnd::OnVScroll for the mean of the arguments.
//@rdesc void 
//@parm UINT nSBCode
//@parm  UINT nPos
//@parm  CScrollBar* pScrollBar
void CGXPageBreakPlugin::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if( m_bDrawPageBreak )
		m_pGrid->Invalidate();
}

//@doc CGXPageBreakPlugin
//@mfunc This function redraw the row header when application scrolls the window while in page
//break mode. If application is not in page break mode, it does nothing.<nl>
//Please refer to CWnd::OnHScroll for the mean of the arguments.
//@rdesc void 
//@parm UINT nSBCode
//@parm  UINT nPos
//@parm  CScrollBar* pScrollBar
void CGXPageBreakPlugin::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if( m_bDrawPageBreak )
	{
		m_pGrid->Invalidate();
	}
}
*/
//@doc CGXPageBreakPlugin
//@mfunc This function calculates the maximum page size. This page size is used to scale the 
//device context when we are doing printing preview and printing. It is called in the DoBeginPrinting
//method before setuping up the mapping mode of DC there.
//@rdesc void 
void CGXPageBreakPlugin::CalcPageSize(CDC* pDC)
{
	m_pGrid->m_awPageFirstRow.RemoveAll();
	m_pGrid->m_awPageFirstCol.RemoveAll();

	m_pGrid->SetPrinting(TRUE, TRUE);

	// Find the whole grid size
	ROWCOL frCol = m_pGrid->GetFrozenCols();
	ROWCOL frRow = m_pGrid->GetFrozenRows();

	int nFrColWidth = m_pGrid->CalcSumOfColWidths(0, frCol);
	int nFrRowHeight = m_pGrid->CalcSumOfRowHeights(0, frRow);

	//Grid size other than frozen col-row
	int nGridWidth = m_pGrid->CalcSumOfColWidths(frCol + 1, m_pGrid->GetColCount());
	int nGridHeight = m_pGrid->CalcSumOfRowHeights(frRow + 1, m_pGrid->GetRowCount());

	// The scaling (number of pages) must be specified in at least one direction
	int nColPages = m_nColPages;
	int nRowPages = m_nRowPages;
	ASSERT (m_nColPages > 0 || m_nRowPages > 0);
	if(m_nColPages <= 0 && m_nRowPages <= 0)
	{
		nColPages = 1;
		nRowPages = 1;
	}

	//Average size for each page
	if(nRowPages <= 0)
	{  // Number of Row Pages is not specified
		int nPageWidth = pDC->GetDeviceCaps(HORZRES);
		int nPageHeight = pDC->GetDeviceCaps(VERTRES);
		double dPageWidth = (double)(nGridWidth+nFrColWidth)/(double)nColPages;
		double dScale = dPageWidth/(double)nPageWidth;
		double dPageHeight = (double)nPageHeight*dScale;
		nRowPages = (int)ceil((double)(nGridHeight+nFrRowHeight)/dPageHeight);	
	}
	if(nColPages <= 0)
	{  // Number of Col Pages is not specified
		int nPageWidth = pDC->GetDeviceCaps(HORZRES);
		int nPageHeight = pDC->GetDeviceCaps(VERTRES);
		double dPageHeight = (double)(nGridHeight+nFrRowHeight)/(double)nRowPages;
		double dScale = dPageHeight/(double)nPageHeight;
		double dPageWidth = (double)nPageWidth*dScale;
		nColPages = (int)ceil((double)(nGridWidth+nFrColWidth)/dPageWidth);	
	}
	int	nAveWidth = (nGridWidth/nColPages + 1);
	int	nAveHeight = (nGridHeight/nRowPages + 1);

	// Calculate the page breaks and find the maximum size
	// First width
	int nMaxWidth = 0;
	int nColPageCount = 1;

	m_pGrid->m_awPageFirstCol.Add(frCol + 1);
	ROWCOL n;
	for(n = frCol + 1; n <= m_pGrid->GetColCount(); n++)
	{
		int nWidth = 0;
		if( nColPageCount < nColPages )
		{
			while(TRUE)
			{
				int tmp = m_pGrid->GetColWidth(n);
				if( nWidth + tmp <= nAveWidth )
					nWidth += tmp;
				else if( nWidth + tmp / 2 <= nAveWidth ) //
				{
					nWidth += tmp; 
					break;
				}
				else if ( nWidth == 0 ) // We add at least one col
				{
					nWidth += tmp;
					break;
				}
				else
				{
					n--; // Put this col to the next page
					break;
				}
				n++;
			}
		}
		else // We are at the last column of pages
		{
			nMaxWidth = max(nMaxWidth, m_pGrid->CalcSumOfColWidths(n, m_pGrid->GetColCount() + 1));

			m_pGrid->m_awPageFirstCol.Add(m_pGrid->GetColCount() + 1);

			break; // We are done, out of for loop
		}
		nMaxWidth = max(nMaxWidth, nWidth);
		nColPageCount++;

		m_pGrid->m_awPageFirstCol.Add(n + 1);
	}

	// Height
	int nMaxHeight = 0;
	int nRowPageCount = 1;

	m_pGrid->m_awPageFirstRow.Add(frRow + 1);
	for( n = frRow + 1; n <= m_pGrid->GetRowCount(); n++)
	{
		int nHeight = 0;
		if( nRowPageCount < nRowPages )
		{
			while(TRUE)
			{
				int tmp = m_pGrid->GetRowHeight(n);
				if( nHeight + tmp <= nAveHeight )
					nHeight += tmp;
				else if( nHeight + tmp / 2 <= nAveHeight )
				{
					nHeight += tmp;
					break;
				}
				else if( nHeight == 0 ) // We add at least on row
				{
					nHeight += tmp;
					break;
				}
				else
				{
					n--; // Put this col to the next page
					break;
				}
				n++;
			}
		}
		else // We are at the last page row
		{
			nMaxHeight = max(nMaxHeight, m_pGrid->CalcSumOfRowHeights(n, m_pGrid->GetRowCount() + 1) );
			
			m_pGrid->m_awPageFirstRow.Add(m_pGrid->GetRowCount() + 1);

			break; //We are done, out of this for loop
		}
		nMaxHeight = max(nMaxHeight, nHeight);

		nRowPageCount++;

		m_pGrid->m_awPageFirstRow.Add(n + 1);
	}

	ASSERT(nMaxWidth > 0 && nMaxHeight > 0);

	// Add the column and row header
	nMaxWidth += nFrColWidth;
	nMaxHeight += nFrRowHeight;

	m_pGrid->SetPrinting(FALSE);

	// Add Margins
	int l, t, r, b;
	m_pGrid->GetParam()->GetProperties()->GetMargins(t, l, b, r);

	nMaxWidth += l; 
	nMaxWidth += r; 
	nMaxHeight += t;
	nMaxHeight += b;

	// If only one page, don't try to fill the entire page
	if(nRowPages == 1 || nColPages == 1)
	{
		int nPageWidth = pDC->GetDeviceCaps(HORZRES);
		int nPageHeight = pDC->GetDeviceCaps(VERTRES);
		double dScaleH = (double)nMaxHeight/(double)nPageHeight;
		double dScaleW = (double)nMaxWidth/(double)nPageWidth;
		if(nRowPages==1 && dScaleH < dScaleW)
		{
			nMaxHeight = (int)ceil( dScaleW*(double)nPageHeight);
		}
		if(nColPages==1 && dScaleH > dScaleW)
		{
			nMaxWidth = (int)ceil( dScaleH*(double)nPageWidth);
		}
	}

	//Final maximum page size
	m_pageSize.cx = nMaxWidth;
	m_pageSize.cy = nMaxHeight;
}

//@doc CGXPageBreakPlugin
//@mfunc Call this function to fit the grid into given page wide and tall.  
//@rdesc void 
//@parm int nRowCount  Fit the grid into nRowCount page tall
//@parm  int nColCount Fit the grid into nColCound page wide
//@parm  BOOL bFitTo   Do the division if bFitTo is TRUE, othewise it will turn off the division if
//we aleady make the grid fit to certain configuration. 
void CGXPageBreakPlugin::SetPageGrid(int nRowCount, int nColCount, BOOL bFitTo)
{
//  5/15/2000 - Now either nRowCount or nColCount (but not both) can be zero or negative.
//  Then CalcPageSize() will calculate the number of pages 
//	based on the scaling of the direction for which the number of pages is specified.
	//	ASSERT(nRowCount > 0 && nColCount > 0 );
	ASSERT(nRowCount > 0 || nColCount > 0);

	m_nRowPages = nRowCount;
	m_nColPages = nColCount;
	m_bFitToPages = bFitTo;

	CreatePageBreak();

	m_pGrid->Invalidate();
}

//@doc CGXPageBreakPlugin
//@mfunc Call this function to setup the mapping mode for the device context.
//@rdesc void 
//@parm CDC *pDC The device context to be prepared
//@parm  CPrintInfo *pInfo Pointer to CPrintInfo.
void CGXPageBreakPlugin::DoPrepareDC(CDC *pDC, CPrintInfo *pInfo)
{
	// TODO: Add your specialized code here and/or call the base class
	if (pInfo)
	{
		// Adjust printer DC
		pDC->SetMapMode(MM_ANISOTROPIC);

		if( !m_bFitToPages )
		{
			pDC->SetWindowExt(GXGetFontState()->m_nLogPixelsX, GXGetFontState()->m_nLogPixelsY);

			int nlogx = pDC->GetDeviceCaps(LOGPIXELSX);
			int nlogy = pDC->GetDeviceCaps(LOGPIXELSY);

			pDC->SetViewportExt(nlogx, nlogy);
		}
		else
		{
			int nPageWidth = pDC->GetDeviceCaps(HORZRES);
			int nPageHeight = pDC->GetDeviceCaps(VERTRES);

			pDC->SetWindowExt(m_pageSize.cx, m_pageSize.cy);
			pDC->SetViewportExt(nPageWidth, nPageHeight);
		}
		// Mapping: 72 pixels/unit (like MM_TEXT)
	}
	else if (m_pGrid->GetParam()->IsDrawWYSIWYG())
	{
		// make sure grid is drawn exactly the same
		// as it will be printed.

		CGXPrintDevice* pPD = m_pGrid->GetParam()->GetPrintDevice();

		// GetPrintDC() will create printer device context
		// when it is called the first time. Further calls
		// will return the previously created device context.

		HDC hPrintDC = 0;
		if (pPD)
			hPrintDC = pPD->GetPrintDC();

		// Make sure, the same mapping mode is used
		if (hPrintDC != NULL)
		{
			pDC->SetAttribDC(hPrintDC);
			SIZE size;
			::SetMapMode(pDC->m_hAttribDC, MM_ANISOTROPIC);

			if( !m_bFitToPages )
			{
				::SetWindowExtEx(pDC->m_hAttribDC, GXGetFontState()->m_nLogPixelsX, GXGetFontState()->m_nLogPixelsY, &size);
				int nlogx = ::GetDeviceCaps(pDC->m_hAttribDC, LOGPIXELSX);
				int nlogy = ::GetDeviceCaps(pDC->m_hAttribDC, LOGPIXELSY);

				::SetViewportExtEx(pDC->m_hAttribDC, nlogx, nlogy, &size);
			}
			else
			{
				int nPageWidth = ::GetDeviceCaps(pDC->m_hAttribDC, HORZRES);
				int nPageHeight = ::GetDeviceCaps(pDC->m_hAttribDC, VERTRES);

				::SetWindowExtEx(pDC->m_hAttribDC, m_pageSize.cx, m_pageSize.cy, &size);
				::SetViewportExtEx(pDC->m_hAttribDC, nPageWidth, nPageHeight, &size);
			}
		}
	}
}

//@doc CGXPageBreakPlugin
//@mfunc Call this function to prepare the device context. This function should be called before 
//OnBeginPrinting method of the view this plugin plugged into. If this function returns FALSE,
//the main view should do the usually processing (e.g. call the OnBeginPrinting method of its base
//class). If this function return TRUE, the main view should not call OnBeginPrinting method of
//it based class.
//@rdesc BOOL Return TRUE to information the main view class not to call OnBeginPrinting method of its
//base class, otherwise the main view should do usually processing.
//@parm CDC *pDC A pointer to the printing device context.
//@parm  CPrintInfo *pInfo A pointer to the CPrintInfo structure.
BOOL CGXPageBreakPlugin::DoBeginPrinting(CDC *pDC, CPrintInfo *pInfo)
{
	if( m_bFitToPages )
	{
		switch (m_pGrid->m_nPrintHandleRecordCount)
		{
		case gxCountAlways: 
			m_pGrid->OnTestGridDimension(GX_MAXROWCOL, GX_MAXROWCOL); 
			break;

		case gxCountPrint: 
			if (!pInfo->m_bPreview)
				 m_pGrid->OnTestGridDimension(GX_MAXROWCOL, GX_MAXROWCOL); 
			break;

		default:
			;
			// no count
		}

		CGXGridParam* pParam = m_pGrid->GetParam();
		ASSERT(pParam->IsKindOf(RUNTIME_CLASS(CGXGridParam)));

		m_pGrid->m_bPrintPaintMsg = FALSE;

		m_pGrid->SetPrinting(TRUE);

		// Float Cells
		CGXAppData* pApp = GXGetAppData();
		CGXAbstractDelayedRangePoolImp* pDelayPool = (CGXAbstractDelayedRangePoolImp*) pApp->m_pDelayedRangePoolImp;
		CGXAbstractSpanCellPoolImp* pSpanPool = (CGXAbstractSpanCellPoolImp*) pApp->m_pSpanCellPoolImp;

		if (pSpanPool && pParam->m_pPrintFloatCells == NULL)
			pParam->m_pPrintFloatCells = pSpanPool->CreateSpanCellPool();

		if (pDelayPool && pParam->m_pDelayedPrintFloatCells == NULL)
			pParam->m_pDelayedPrintFloatCells = pDelayPool->CreateDelayedRangePool();

		m_pGrid->DelayFloatCells(CGXRange().SetTable());

		CalcPageSize(pDC);
		DoPrepareDC(pDC, pInfo);

		// set no of pages
		INT_PTR ipNoOfPages = (m_pGrid->m_awPageFirstRow.GetSize()-1)*(m_pGrid->m_awPageFirstCol.GetSize()-1);
		pInfo->SetMaxPage((UINT)ipNoOfPages);

		// page string gets displayed in the status line of the print preview
		CString s;
		wsprintf(s.GetBuffer(10), _T(" / %u"), pInfo->GetMaxPage());
		s.ReleaseBuffer();
		pInfo->m_strPageDesc += s;

		m_pGrid->SetPrinting(FALSE);

		return TRUE; // Tell the main view not to call OnBeginPrinting of its base class.
	}
	return FALSE; // Tell the main view to call OnBeginPrinting
}
