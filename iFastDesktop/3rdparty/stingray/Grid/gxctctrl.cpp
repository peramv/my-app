///////////////////////////////////////////////////////////////////////////////
// gxctctrl.cpp : implementation of cell tip functionality
//				  in the grid controls
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
// Author: Ricky Pearson
//

//RWP02a (entire file)

#define _OG_EXPORT_IMPL

#include "stdafx.h"

#if _MFC_VER >= 0x0400

#include "grid\gxctrli.h"

#include "grid\gxctwnd.h"

#include "grid\gxsttip.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// Local constants
#define GX_CELLTIP_INFLATEWINDOW_CX	6
#define GX_CELLTIP_INFLATEWINDOW_CY 2


/////////////////////////////////////////////////////////////////////////////
// CGXControl
void CGXStatic::ImplementCellTips()
{
	if(m_pCellTipImpl != NULL)
	{
		TRACE0("OG Warning: CGXStatic::ImplementCellTips was called more than once\n");
		return;
	}
	else
		m_pCellTipImpl = new CGXCellTipStatic(this);
}

/////////////////////////////////////////////////////////////////////////////
// Implementation of cell tips for CGXStatic ////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CGXCellTipStatic

CGXCellTipStatic::CGXCellTipStatic(CGXStatic* pStatic)
{
	m_pStatic = pStatic;
}

CGXCellTipStatic::~CGXCellTipStatic()
{
}

BOOL CGXCellTipStatic::NeedShowCellTip(ROWCOL nRow, ROWCOL nCol, CGXStyle* pStyle)
{
	ASSERT(m_pStatic != NULL); // There has to be a control that is associated with this.

	if(m_pStatic == NULL)
		return FALSE;

	// Get the cell's style and cell tip text
	CString strCellText = _gxCellTipWndHelper::GetText(m_pStatic, nRow, nCol, pStyle);

	if (!m_pStatic->IsKindOf(RUNTIME_CLASS(CEdit)) && strCellText.Left(4) == _T("#BMP"))
	{
		return _gxCellTipWndHelper::GetBitmapClipping(m_pStatic, nRow, nCol, pStyle);
	}
	else
	{
		// Verify that the cell is single line
		if (pStyle->GetWrapText())
		{
			return FALSE;
		}

		return _gxCellTipWndHelper::GetTextClipping(m_pStatic, nRow, nCol, pStyle); 
	}
}

DWORD CGXCellTipStatic::GetCellTipID(ROWCOL nRow, ROWCOL nCol, CGXStyle* pStyle)
{
	ASSERT(m_pStatic != NULL); // There has to be a control that is associated with this.

	// return default
	if(m_pStatic == NULL)
		return GX_CELLTIP_ID_TEXT;

	
	CString strCellText = _gxCellTipWndHelper::GetText(m_pStatic, nRow, nCol, pStyle);

	if (!m_pStatic->IsKindOf(RUNTIME_CLASS(CEdit)) && strCellText.Left(4) == _T("#BMP"))
	{
		// Use CGXStaticBitmapCellTipWnd
		return GX_CELLTIP_ID_BITMAP;
	}
	else
	{
		// Use CGXTextCellTipWnd
		return GX_CELLTIP_ID_TEXT;
	}
}

void CGXCellTipStatic::InitializeCellTip(ROWCOL nRow, ROWCOL nCol, CGXStyle* pStyle, CGXCellTipWnd* pCellTip)
{
	ASSERT(m_pStatic != NULL); // There has to be a control that is associated with this.

	if(m_pStatic == NULL)
		return;

	
	ASSERT(pCellTip);

	if (!pCellTip)
		return;

	if (GX_CELLTIP_ID_TEXT == pCellTip->GetID())
	{
		// Set the cell tip text
		CString strTipText = _gxCellTipWndHelper::GetText(m_pStatic, nRow, nCol, pStyle);
		((CGXTextCellTipWnd*)pCellTip)->SetText(strTipText);

		// Get the cell tip font 
		CGXFont font = pStyle->GetFont();

		// Account for zooming factor
		LOGFONT lf = font.GetLogFont();
		int nZoom = pCellTip->m_pGrid->GetZoom();
		lf.lfHeight = lf.lfHeight * nZoom / 100;
		lf.lfWidth = lf.lfWidth * nZoom / 100;
		font.SetLogFont(lf);

		// Set the cell tip font
		((CGXTextCellTipWnd*)pCellTip)->SetFont(font);

		// Get cell and text rectangles in screen coordinates
		CRect rcCell = _gxCellTipWndHelper::GetAdjustedCellRect(m_pStatic, nRow, nCol, pStyle);
		CRect rcTextClient = _gxCellTipWndHelper::GetVisibleTextRect(m_pStatic, nRow, nCol, pStyle);

		// Get text size
		CSize sizeText = _gxCellTipWndHelper::GetTextSize(m_pStatic, nRow, nCol, pStyle);

		// Additional space around text
		sizeText.cx += GX_CELLTIP_INFLATEWINDOW_CX;
		sizeText.cy += GX_CELLTIP_INFLATEWINDOW_CY;

		// Get clipping
		UINT nClipping = _gxCellTipWndHelper::GetTextClipping(m_pStatic, nRow, nCol, pStyle);

		// Check if text is centered
		BOOL bTextCenteredHorz = pStyle->GetIncludeHorizontalAlignment() ? 
								 pStyle->GetHorizontalAlignment() == DT_CENTER : FALSE;
		BOOL bTextCenteredVert = pStyle->GetIncludeVerticalAlignment() ? 
								 pStyle->GetVerticalAlignment() == DT_VCENTER : FALSE;

		// 
		CPoint ptTextTopLeft = _gxCellTipWndHelper::GetTextTopLeft(m_pStatic, nRow, nCol, pStyle);
		CRect rcText(ptTextTopLeft.x, 
					 ptTextTopLeft.y, 
					 min(ptTextTopLeft.x + sizeText.cx, rcTextClient.right), 
					 min(ptTextTopLeft.y + sizeText.cy, rcTextClient.bottom));

		// Get the screen size
		CSize sizeScreen;
		sizeScreen.cx = GetSystemMetrics(SM_CXVIRTUALSCREEN);
		sizeScreen.cy = GetSystemMetrics(SM_CYVIRTUALSCREEN);


		// Get width and height of tip
		int nWidth, nHeight;

		if (nClipping & GX_CELLTIP_CLIPPING_BYSCREEN_HORZ)
		{
			nWidth = sizeText.cx;
		}
		else if (nClipping & GX_CELLTIP_CLIPPING_BYGRID_HORZ && !bTextCenteredHorz)
		{
			nWidth = ptTextTopLeft.x + sizeText.cx - rcCell.left;
		}
		else
		{
			nWidth = max(min(sizeScreen.cx - rcCell.left + 1, 
							 rcCell.right - rcCell.left + 1), 
						 ptTextTopLeft.x + sizeText.cx - rcCell.left);
		}

		if (nClipping & GX_CELLTIP_CLIPPING_BYSCREEN_VERT)
		{
			nHeight = sizeText.cy;
		}
		else if (nClipping & GX_CELLTIP_CLIPPING_BYGRID_VERT && !bTextCenteredVert)
		{
			nHeight = ptTextTopLeft.y + sizeText.cy - rcCell.top;
		}
		else
		{
			nHeight = max(min(sizeScreen.cy - rcCell.top, 
							 rcCell.bottom - rcCell.top), 
						 ptTextTopLeft.y + sizeText.cy - rcCell.top);
		}

		// Get the top-left for the cell tip
		CPoint pt = rcCell.TopLeft();

		// Adjust for screen clipped text
		if (nClipping & GX_CELLTIP_CLIPPING_BYSCREEN_HORZ)
		{
			pt.x = pt.x + nWidth > sizeScreen.cx ? sizeScreen.cx : 0;
		}
		if (nClipping & GX_CELLTIP_CLIPPING_BYSCREEN_VERT)
		{
			pt.y = pt.y + nHeight > sizeScreen.cy ? sizeScreen.cy : 0;
		}

		// Adjust top-left so that entire tip fits on screen
		pt.x = max(0, min(pt.x, (sizeScreen.cx - nWidth)));
		pt.y = max(0, min(pt.y, (sizeScreen.cy - nHeight)));

		// Calculate and set tip window rect
		CRect rcTip(pt.x, pt.y, pt.x + nWidth, pt.y + nHeight);
		((CGXTextCellTipWnd*)pCellTip)->SetTipRect(rcTip);

		// Calculate and set the text rect
		pCellTip->GetClientRect(rcText);
		ptTextTopLeft.x = min(ptTextTopLeft.x, (sizeScreen.cx - sizeText.cx + 2));
		ptTextTopLeft.y = min(ptTextTopLeft.y, (sizeScreen.cy - sizeText.cy + 2));
		pCellTip->ScreenToClient(&ptTextTopLeft);
		rcText.left = nClipping & GX_CELLTIP_CLIPPING_BYSCREEN_HORZ ? 
						rcText.left + 2: ptTextTopLeft.x;
		rcText.top = nClipping & GX_CELLTIP_CLIPPING_BYSCREEN_VERT ? 
						rcText.top : ptTextTopLeft.y;

		// Adjust for bottom alignment
		rcText.top = pStyle->GetVerticalAlignment() == DT_BOTTOM ? 
			max(0, rcText.top - 1) : rcText.top;

		// Save the text rect
		((CGXTextCellTipWnd*)pCellTip)->SetTextRect(rcText);

	}
	else if (GX_CELLTIP_ID_BITMAP == pCellTip->GetID())
	{

		// Get the bitmap
		CString strCellText = _gxCellTipWndHelper::GetText(m_pStatic, nRow, nCol, pStyle);
		HANDLE hBitmap = GXGetDIBState()->GetPool()->LookupOrCreateDIB(strCellText);
		if (!hBitmap)
			return;

		LPSTR lpDIB = (LPSTR)GlobalLock(hBitmap);
		if (!lpDIB)
			return;

		BITMAPINFO* pBMI = (BITMAPINFO*)lpDIB;
		if (!pBMI)
			return;

		// Get the bitmap's dimensions
		int nBitmapWidth = pBMI->bmiHeader.biWidth;
		int nBitmapHeight = pBMI->bmiHeader.biHeight;

		// Clean up bitmap
		::GlobalUnlock(hBitmap);

		// Save the handle
		((CGXStaticBitmapCellTipWnd*)pCellTip)->SetBitmapHandle(hBitmap);

		// Get the cell's alignment
		DWORD dwAlign = 0;
		dwAlign |= pStyle->GetIncludeHorizontalAlignment() ? 
				   pStyle->GetHorizontalAlignment() : 0;
		dwAlign |= pStyle->GetIncludeVerticalAlignment() ? 
				   pStyle->GetVerticalAlignment() : 0;

		// Get cell's rectangle and convert to screen coordinates
		CRect rcCell = _gxCellTipWndHelper::GetAdjustedCellRect(m_pStatic, nRow, nCol, pStyle);
		CRect rcText = _gxCellTipWndHelper::GetVisibleTextRect(m_pStatic, nRow, nCol, pStyle);

		// Get the top-left for the cell tip
		CPoint pt = rcCell.TopLeft();

		// Get width and height of tip
		CRect rcCompose(rcText.left, rcText.top, rcCell.right + 1, rcCell.bottom - 1);
		int nWidth = max(rcCompose.Width(), nBitmapWidth + 1);
		int nHeight = max(rcCompose.Height(), nBitmapHeight + 1);

		// Adjust top-left so that entire tip fits on screen
		pt.x = min(pt.x, (GetSystemMetrics(SM_CXVIRTUALSCREEN) - nWidth));
        pt.y = min(pt.y, (GetSystemMetrics(SM_CYVIRTUALSCREEN) - nHeight));


		// Calculate tip window rect
		CRect rcTip(pt.x, pt.y, pt.x + nWidth, pt.y + nHeight);

		// Adjust tip rect if bitmap is bottom aligned and clipped vertically
		if (dwAlign & DT_BOTTOM && nBitmapHeight >= rcCell.Height())
		{
			rcTip.top -= rcTip.bottom - rcCell.bottom;
			rcTip.bottom -= rcTip.bottom - rcCell.bottom;
		}

		// Save the cell tip rect
		((CGXStaticBitmapCellTipWnd*)pCellTip)->SetTipRect(rcTip);

		// Calculate bitmap rect
		CRect rcBitmap;
		pCellTip->GetClientRect(rcBitmap);

		// Adjust bitmap rect for cell alignment
		if (dwAlign & DT_CENTER && rcCell.Width() > nBitmapWidth)
		{
			rcBitmap.left += (rcBitmap.Width() - nBitmapWidth) / 2;
		}
		else if (dwAlign & DT_RIGHT && rcCell.Width() > nBitmapWidth)
		{
			rcBitmap.left += rcBitmap.Width() - nBitmapWidth;
		}
		if (dwAlign & DT_VCENTER && rcCell.Height() > nBitmapHeight)
		{
			rcBitmap.top += (rcBitmap.Height() - nBitmapHeight) / 2;
		}
		else if (dwAlign & DT_BOTTOM && rcCell.Height() > nBitmapHeight)
		{
			rcBitmap.top += rcBitmap.Height() - nBitmapHeight;
		}

		// Save the bitmap rect
		((CGXStaticBitmapCellTipWnd*)pCellTip)->SetBitmapRect(rcBitmap);
	}
}


#endif // _MFC_VER >= 0x0400
