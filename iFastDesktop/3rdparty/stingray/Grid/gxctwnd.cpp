///////////////////////////////////////////////////////////////////////////////
// gxctwnd.cpp : implementation of the CGXCellTipWnd
//				 class and it's derivatives
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

#include "grid\gxctwnd.h"

//FOUNDATION_GLOBAL_FUNC_API(HWND) RWGetSafeHwnd();

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif


/////////////////////////////////////////////////////////////////////////////
// _gxCellTipWndHelper

CString _gxCellTipWndHelper::GetText(CGXControl* pControl, ROWCOL nRow, 
									 ROWCOL nCol, CGXStyle* pStyle)
{
	CString strRet;

	pControl->GetControlText(strRet, nRow, nCol, NULL, *pStyle);

	return strRet;
}

CSize _gxCellTipWndHelper::GetTextSize(CGXControl* pControl, ROWCOL nRow, 
									   ROWCOL nCol, CGXStyle* pStyle)
{
	CSize sizeText = 0;
	CFont* pOldFont = NULL;
	CFont* pFont = NULL;

	// Get the font
	if (!pStyle->GetIncludeFont())
		return sizeText;
	
	CGXFont font = pStyle->GetFont();

	// Get the cell's text
	CString strCellText = _gxCellTipWndHelper::GetText(pControl, nRow, nCol, pStyle);

	// Account for zooming factor
	LOGFONT lf = font.GetLogFont();
	int nZoom = pControl->Grid()->GetZoom();
	lf.lfHeight = lf.lfHeight * nZoom / 100;
	lf.lfWidth = lf.lfWidth * nZoom / 100;

	// Create a CFont to use for text extents
	pFont = new CFont;
	pFont->CreateFontIndirect(&lf);

	// Get size of text
	CClientDC dc(pControl->Grid()->GridWnd());
	pOldFont = dc.SelectObject(pFont);
	sizeText = dc.GetTextExtent((LPCTSTR)strCellText);
	dc.SelectObject(pOldFont);
	delete pFont;

	return sizeText;
}

CPoint _gxCellTipWndHelper::GetTextTopLeft(CGXControl* pControl, ROWCOL nRow, 
										   ROWCOL nCol, CGXStyle* pStyle)
{
	CPoint ptRet; 
	CFont* pFont = NULL;

	// Get the displayed text
	CString strCellText = GetText(pControl, nRow, nCol, pStyle);

	// Get the cell and text rectangles
	CRect rcCell = GetAdjustedCellRect(pControl, nRow, nCol, pStyle);
	CRect rcText = GetVisibleTextRect(pControl, nRow, nCol, pStyle);

	// Get the cell's alignment
	DWORD dwAlign = 0;
	dwAlign |= pStyle->GetIncludeHorizontalAlignment() ? 
			   pStyle->GetHorizontalAlignment() : 0;
	dwAlign |= pStyle->GetIncludeVerticalAlignment() ? 
			   pStyle->GetVerticalAlignment() : 0;

	// Top left alignment
	if (!dwAlign || dwAlign == DT_LEFT || dwAlign == DT_TOP || 
		(dwAlign & DT_LEFT && dwAlign & DT_TOP))
	{
		ptRet.x = rcText.left;
		ptRet.y = rcText.top;
		return ptRet;
	}

	// Get cell's font
	CGXFont font = pStyle->GetFont();
	LOGFONT lf = font.GetLogFont();
	pFont = new CFont;
	pFont->CreateFontIndirect(&lf);

	// Determine clipping for text and massage the string if alignment 
	// is not DT_LEFT | DT_TOP to determine what is actually drawn in the cell.
	// This is necessary, because we do not draw clipped characters in cells.
	// Instead, characters are lopped off until the string fits, then the
	// altered string is drawn with the appropriate justification.
	CSize sizeText;
	{
		CClientDC dc(pControl->Grid()->GridWnd());
		CFont* pOldFont = dc.SelectObject(pFont);
		sizeText = dc.GetTextExtent((LPCTSTR)strCellText);

		// Get the ellipsis flag if cell alignment is not DT_LEFT.
		// If the #### option is turned on, treat text in tip as
		// left aligned
		BOOL bEllipsis = FALSE;
		if (dwAlign & DT_CENTER || dwAlign & DT_RIGHT)
		{
			bEllipsis = pStyle->GetIncludeUserAttribute(GX_IDS_UA_ELLIPSISTYPE) ? 
						((CGXEllipseUserAttribute&)pStyle->
						GetUserAttribute(GX_IDS_UA_ELLIPSISTYPE))
						.GetEllipseValue() == gxDotEllipse : FALSE;
		}
		
		CString strTemp;
		int nEllipsisCount = 3;

		while ((dwAlign & DT_CENTER || dwAlign & DT_RIGHT) && 
			   (sizeText.cx > (rcText.Width()+1)) && 
			   (strCellText.GetLength() > 1) &&
			   (nEllipsisCount > 0))
		{
			// Lop off a character and try again
			strCellText = strCellText.Left(strCellText.GetLength() - 1);

			strTemp = strCellText;
			if (bEllipsis)
			{
				for (int i = 0; i < nEllipsisCount; i++)
				{
					strTemp += _T(".");
				}
					
				if (strCellText.GetLength() == 1)
				{
					nEllipsisCount--;
				}
			}
			sizeText = dc.GetTextExtent((LPCTSTR)strTemp);
		}

		dc.SelectObject(pOldFont);
	} // Release DC
	delete pFont;	// Clean up font

	// Determine horizontal position
	if (dwAlign & DT_RIGHT)
	{
		ptRet.x = rcText.left + max(0, rcText.Width()+1 - sizeText.cx);
	}
	else if (dwAlign & DT_CENTER)
	{
		ptRet.x = rcText.left + max(0, (rcText.Width()+1 - sizeText.cx) / 2);
	}
	else
	{
		ptRet.x = rcText.left;
	}

	if (dwAlign & DT_BOTTOM)
	{
		ptRet.y = rcText.top + max(0, rcText.Height() - sizeText.cy);
	}
	else if (dwAlign & DT_VCENTER)
	{
		ptRet.y = rcText.top + max(0, (rcText.Height() - sizeText.cy) / 2);
	}
	else
	{
		ptRet.y = rcText.top;
	}
	
	return ptRet;
}

CPoint _gxCellTipWndHelper::GetBitmapTopLeft(CGXControl* pControl, ROWCOL nRow, 
											 ROWCOL nCol, CGXStyle* pStyle)
{
	CPoint ptRet;

	// Get the bitmap
	CString strCellText = GetText(pControl, nRow, nCol, pStyle);
	HANDLE hBitmap = GXGetDIBState()->GetPool()->LookupOrCreateDIB(strCellText);
	if (!hBitmap)
		return FALSE;

	LPSTR lpDIB = (LPSTR)GlobalLock(hBitmap);
	if (!lpDIB)
		return FALSE;

	BITMAPINFO* pBMI = (BITMAPINFO*)lpDIB;
	if (!pBMI)
		return FALSE;

	// Get the bitmap's dimensions
	int nBitmapWidth = pBMI->bmiHeader.biWidth;
	int nBitmapHeight = pBMI->bmiHeader.biHeight;

	// Clean up bitmap
	::GlobalUnlock(hBitmap);

	// Get the cell's alignment
	DWORD dwAlign = 0;
	dwAlign |= pStyle->GetIncludeHorizontalAlignment() ? 
			   pStyle->GetHorizontalAlignment() : 0;
	dwAlign |= pStyle->GetIncludeVerticalAlignment() ? 
			   pStyle->GetVerticalAlignment() : 0;

	// Get cell's rectangle and convert to screen coordinates
	CRect rcCell = GetAdjustedCellRect(pControl, nRow, nCol, pStyle);

	// Adjust bitmap rect for cell alignment
	if (dwAlign & DT_CENTER && rcCell.Width() > nBitmapWidth)
	{
		ptRet.x = rcCell.left + (rcCell.Width() - nBitmapWidth) / 2;
	}
	else if (dwAlign & DT_RIGHT && rcCell.Width() > nBitmapWidth)
	{
		ptRet.x = rcCell.right - nBitmapWidth - 1;
	}
	else
	{
		ptRet.x = rcCell.left;
	}

	if (dwAlign & DT_VCENTER && rcCell.Height() > nBitmapHeight)
	{
		ptRet.y = rcCell.top + (rcCell.Height() - nBitmapHeight) / 2;
	}
	else if (dwAlign & DT_BOTTOM && rcCell.Height() > nBitmapHeight)
	{
		ptRet.y = rcCell.right - nBitmapHeight -1;
	}
	else 
	{
		ptRet.y = rcCell.top;
	}

	return ptRet;
}

CRect _gxCellTipWndHelper::GetAdjustedCellRect(CGXControl* pControl, ROWCOL nRow, 
											   ROWCOL nCol, CGXStyle* pStyle)
{
	// Get the cell's raw rect
	CRect rcCell = pControl->Grid()->CalcRectFromRowColExEx(nRow, nCol);
	pControl->Grid()->GridWnd()->ClientToScreen(rcCell);

	// Adjust rect for cell borders
	rcCell.left +=	 pStyle->GetIncludeBorders(gxBorderLeft) ? 
					 pStyle->GetBorders(gxBorderLeft).GetWidth() : 0;
	rcCell.right -=  pStyle->GetIncludeBorders(gxBorderRight) ? 
					 pStyle->GetBorders(gxBorderRight).GetWidth() - 1: 0;
	rcCell.top +=	 pStyle->GetIncludeBorders(gxBorderTop) ? 
					 pStyle->GetBorders(gxBorderTop).GetWidth() : 0;
	rcCell.bottom -= pStyle->GetIncludeBorders(gxBorderBottom) ? 
					 pStyle->GetBorders(gxBorderBottom).GetWidth() - 1 : 0;

	return rcCell;
}

CRect _gxCellTipWndHelper::GetVisibleTextRect(CGXControl* pControl, ROWCOL nRow, 
											  ROWCOL nCol, CGXStyle* pStyle)
{
	CRect rcCell = pControl->Grid()->CalcRectFromRowColExEx(nRow, nCol);
	CRect rcCellText = pControl->GetCellRect(nRow, nCol, rcCell, pStyle);
	pControl->Grid()->GridWnd()->ClientToScreen(rcCellText);

	return rcCellText;
}

UINT _gxCellTipWndHelper::GetBitmapClipping(CGXControl* pControl, ROWCOL nRow, 
											ROWCOL nCol, CGXStyle* pStyle)
{
	UINT nClipping = 0;

	// Get the cell's style and cell tip text
	CString strCellText = GetText(pControl, nRow, nCol, pStyle);

	// Get the bitmap
	HANDLE hBitmap = GXGetDIBState()->GetPool()->LookupOrCreateDIB(strCellText);
	if (!hBitmap)
		return FALSE;

	LPSTR lpDIB = (LPSTR)GlobalLock(hBitmap);
	if (!lpDIB)
		return FALSE;

	BITMAPINFO* pBMI = (BITMAPINFO*)lpDIB;
	if (!pBMI)
		return FALSE;

	// Get the bitmap's dimensions
	int nBitmapWidth = pBMI->bmiHeader.biWidth;
	int nBitmapHeight = pBMI->bmiHeader.biHeight;

	// Clean up bitmap
	::GlobalUnlock(hBitmap);

	// Get cell's rectangle and convert to screen coordinates
	CRect rcCell = _gxCellTipWndHelper::GetAdjustedCellRect(pControl, nRow, nCol, pStyle);

	// Determine if clipping has occered by the cell's rect
	nClipping |= nBitmapWidth > rcCell.Width() ? GX_CELLTIP_CLIPPING_BYCELL_HORZ : 0;
	nClipping |= nBitmapHeight > rcCell.Height() ? GX_CELLTIP_CLIPPING_BYCELL_VERT : 0;

	// Determine the top left point for the bitmap in screen coordinates
	CPoint ptBitmapTL = GetBitmapTopLeft(pControl, nRow, nCol, pStyle);

	// Determine the rect of the bitmap in screen coordinates
	CRect rcBitmap(ptBitmapTL.x, 
				   ptBitmapTL.y, 
				   ptBitmapTL.x + nBitmapWidth, 
				   ptBitmapTL.y + nBitmapHeight
				   );

	return nClipping |= GetClippingOutsideCell(pControl, nRow, nCol, pStyle, &rcBitmap);
}

UINT _gxCellTipWndHelper::GetTextClipping(CGXControl* pControl, ROWCOL nRow, 
										  ROWCOL nCol, CGXStyle* pStyle)
{
	UINT nClipping = 0;

	// Check for rotated text.  Rotated text is not supported with 
	// the current cell tip implementation.
	if (pStyle->GetIncludeFont() &&
		pStyle->GetFont().GetIncludeOrientation() &&
		pStyle->GetFont().GetOrientation() > 0)
	{
		return FALSE;
	}

	// Get text "client" rect in screen coordinates.  The "client"
	// rect is the actual rect where text can be drawn.  For many
	// cells, this is equivalent to the cell rect, but for cells 
	// with children, this area may be smaller.  For instance, 
	// CGXSpinEdit's text "client" is the cell's rect minus the
	// rect for the spin buttons.
	CRect rcCellText = GetVisibleTextRect(pControl, nRow, nCol, pStyle);

	// Get size of cell tip text
	CSize sizeText = GetTextSize(pControl, nRow, nCol, pStyle);

	// Get the cell text's top-left point and calculate the bounding 
	// rect for the actual text.  We need to calculate the bounding 
	// rect for clipping purposes.  The rect returned from GetCellRect()
	// is the "client" area in the cell for drawing text and does not 
	// reflect the actual location of text in the cell.  For this reason 
	// it is not sufficient for determining if text has been clipped.
	CPoint ptTextTopLeft = GetTextTopLeft(pControl, nRow, nCol, pStyle);
	CRect rcText(ptTextTopLeft.x, 
				ptTextTopLeft.y, 
				min(ptTextTopLeft.x + sizeText.cx, rcCellText.right), 
				min(ptTextTopLeft.y + sizeText.cy, rcCellText.bottom));

	// Check if text is clipped by the cell 
	nClipping |= sizeText.cx > (rcText.Width()+1) ? GX_CELLTIP_CLIPPING_BYCELL_HORZ : 0;
	nClipping |= sizeText.cy > rcText.Height() ? GX_CELLTIP_CLIPPING_BYCELL_VERT : 0;

	return nClipping | GetClippingOutsideCell(pControl, nRow, nCol, pStyle, &rcText);
}

UINT _gxCellTipWndHelper::GetClippingOutsideCell(CGXControl* pControl, ROWCOL nRow, 
												 ROWCOL nCol, CGXStyle* pStyle, 
												 CRect* rcData)
{
	// Unused
	nRow;
	nCol;
	pStyle;

	UINT nClipping = 0;

	// Check if cell data is clipped by the grid's client
	CRect rcGrid;
	pControl->Grid()->GridWnd()->GetClientRect(rcGrid);
	pControl->Grid()->GridWnd()->ClientToScreen(rcGrid);

	nClipping |= rcData->left < rcGrid.left || rcData->right > rcGrid.right ?
				 GX_CELLTIP_CLIPPING_BYGRID_HORZ : 0;
	nClipping |= rcData->top < rcGrid.top || rcData->bottom > rcGrid.bottom ?
				 GX_CELLTIP_CLIPPING_BYGRID_VERT : 0;

	// Check if text is clipped by the screen
	CSize sizeScreen;
	sizeScreen.cx = GetSystemMetrics(SM_CXVIRTUALSCREEN);
    sizeScreen.cy = GetSystemMetrics(SM_CYVIRTUALSCREEN);

	nClipping |= rcData->left < 0 || rcData->right > sizeScreen.cx ?
				 GX_CELLTIP_CLIPPING_BYSCREEN_HORZ : 0;
	nClipping |= rcData->top < 0 || rcData->bottom > sizeScreen.cy ?
				 GX_CELLTIP_CLIPPING_BYSCREEN_VERT : 0;

	return nClipping;
}


/////////////////////////////////////////////////////////////////////////////
// CGXCellTipWnd

IMPLEMENT_DYNAMIC(CGXCellTipWnd, CWnd)

CGXCellTipWnd::CGXCellTipWnd(CGXGridCore* pGrid)
{
	m_pGrid = pGrid;
}

CGXCellTipWnd::~CGXCellTipWnd()
{
	if (m_hWnd != NULL)
	{
		DestroyWindow();            // destroy the window
	}
}

BEGIN_MESSAGE_MAP(CGXCellTipWnd, CWnd)
	//{{AFX_MSG_MAP(CGXCellTipWnd)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_MBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CGXCellTipWnd::CreateTipWnd()
{
	// Create the cell tip window
	CRect rect;
	rect.SetRectEmpty();

	BOOL bCreated = CreateEx(WS_EX_TOOLWINDOW, 
							 NULL,
							 NULL, 
							 WS_CHILD,
							 rect.left, 
							 rect.top, 
							 rect.right, 
							 rect.bottom,
							 ::GetDesktopWindow(),
							 (HMENU)NULL);

	return bCreated;
}

BOOL CGXCellTipWnd::Show()
{
	if (m_hWnd && !IsWindowVisible())
	{
		CRect rect;
		GetWindowRect(rect);
		SaveBackground(this, rect);
		Invalidate(FALSE);
		ShowWindow(SW_SHOW);
		SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		UpdateWindow();
	}
	
	return TRUE;
}

BOOL CGXCellTipWnd::Hide()
{
	if (m_hWnd && IsWindowVisible())
	{
		RestoreBackground(this);
		ShowWindow(SW_HIDE);
		UpdateWindow();
	}

	return TRUE;
}

void CGXCellTipWnd::SaveBackground(CWnd* pWnd, const CRect& rect)
{
	CWindowDC dc(pWnd);

	CRect rcClient = rect;
	ScreenToClient(rcClient);

	m_rcBackground = rcClient;

	m_dcBackground.CreateCompatibleDC(&dc);
	m_bmBackground.CreateCompatibleBitmap(&dc, rcClient.Width(), rcClient.Height());
	m_hbmBackgroundOld = (HBITMAP)m_dcBackground.SelectObject(&m_bmBackground)->GetSafeHandle();
	
	// Save the existing background so that we can hide the window again later 
	m_dcBackground.BitBlt(0, 0, rcClient.Width(), rcClient.Height(), &dc, 
						  rcClient.left, rcClient.top, SRCCOPY);
}

void CGXCellTipWnd::RestoreBackground(CWnd* pWnd)
{
	if (m_dcBackground.GetSafeHdc())
	{
		CWindowDC dc(pWnd);
		CRect& rect = m_rcBackground;

		dc.BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &m_dcBackground, 0, 0,
		  SRCCOPY);

		m_dcBackground.SelectObject(CBitmap::FromHandle(m_hbmBackgroundOld));
		m_bmBackground.DeleteObject();
		m_dcBackground.DeleteDC();

		dc.BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &m_dcBackground, 0, 0,
			SRCCOPY);
	}
}

void CGXCellTipWnd::ForwardMouseMessage(UINT nFlags, CPoint point)
{
	// Unused
	nFlags;
	point;

	// Get the message
	const MSG* pMsg = GetCurrentMessage();
	MSG newMsg;
	memcpy(&newMsg, pMsg, sizeof(MSG));

	// Massage the coordinates to the grid's client rect
	POINT structPoint;
	structPoint.x = LOWORD(pMsg->lParam);
	structPoint.y = HIWORD(pMsg->lParam);

	ClientToScreen(&structPoint);
	m_pGrid->GridWnd()->ScreenToClient(&structPoint);

	// Stuff them back into an LPARAM
	LPARAM lParam = MAKELONG((WORD)structPoint.x, (WORD)structPoint.y);

	// Send the message to grid
	m_pGrid->GridWnd()->SendMessage(pMsg->message, pMsg->wParam, lParam);
}

void CGXCellTipWnd::ForwardMessage()
{
	// Get the message
	const MSG* pMsg = GetCurrentMessage();

	// Send the message to grid
	m_pGrid->GridWnd()->SendMessage(pMsg->message, pMsg->wParam, pMsg->lParam);
}

void CGXCellTipWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	ForwardMouseMessage(nFlags, point);
}

void CGXCellTipWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	ForwardMouseMessage(nFlags, point);
}

void CGXCellTipWnd::OnMButtonDown(UINT nFlags, CPoint point)
{
	ForwardMouseMessage(nFlags, point);
}

void CGXCellTipWnd::OnRButtonDown(UINT nFlags, CPoint point)
{
	ForwardMouseMessage(nFlags, point);
}

void CGXCellTipWnd::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// Unused
	nChar;
	nRepCnt;
	nFlags;

	// Forward the message
	ForwardMessage();
}

/////////////////////////////////////////////////////////////////////////////
// CGXTextCellTipWnd

CGXTextCellTipWnd::CGXTextCellTipWnd(CGXGridCore* pGrid) 
	: CGXCellTipWnd(pGrid)
{
	m_dwID = GX_CELLTIP_ID_TEXT;
}

IMPLEMENT_DYNAMIC(CGXTextCellTipWnd, CGXCellTipWnd)

BEGIN_MESSAGE_MAP(CGXTextCellTipWnd, CGXCellTipWnd)
	//{{AFX_MSG_MAP(CGXTextCellTipWnd)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CGXTextCellTipWnd::CreateTipWnd()
{
	// Create a background brush
	VERIFY(m_brBackground.CreateSolidBrush((::GetSysColor(COLOR_INFOBK))));

	return CGXCellTipWnd::CreateTipWnd();
}

void CGXTextCellTipWnd::SetFont(CGXFont& font)
{
	// Save the font
	m_font = font;
}

void CGXTextCellTipWnd::SetText(CString& strText)
{
	// Set the window text
	SetWindowText((LPCTSTR)strText);
}

void CGXTextCellTipWnd::SetTipRect(CRect& rcTip)
{
	// Set the window rect (but don't show it) so that 
	// GetClientRect will return the correct value
	SetWindowPos(NULL, 
				 rcTip.left, 
				 rcTip.top, 
				 rcTip.Width(), 
				 rcTip.Height(), 
				 SWP_HIDEWINDOW | SWP_NOACTIVATE | SWP_NOREDRAW
				 );
}
	
void CGXTextCellTipWnd::SetTextRect(CRect& rcText)
{
	// Save the text rect
	m_rcText = rcText;
}

CRect CGXTextCellTipWnd::GetTextRect()
{ 
	return m_rcText; 
}

void CGXTextCellTipWnd::OnPaint()
{
	CPaintDC dc(this); // Device context for painting

	// Get the client rect for drawing the border
	CRect rcClient;
	GetClientRect(rcClient);

	// Select the font and set up the DC
	CFont* pNewFont = new CFont;
	LOGFONT lf = m_font.GetLogFont();
	pNewFont->CreateFontIndirect(&lf);
	CFont* pOldFont = dc.SelectObject(pNewFont);
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(::GetSysColor(COLOR_INFOTEXT));

	// Get the text 
	CString strText;
	GetWindowText(strText);

	HTHEME lhTheme = NULL;
	// Note: Calling dc.GetWindow() will return an invalid handle. 
	// Instead call AfxGetMainWnd()->GetSafeHwnd().
	if (RWIsAppThemed() && RWIsThemeActive()) 
		lhTheme = RWOpenThemeData (RWGetSafeHwnd(), L"TOOLTIP");
	
	if (lhTheme)
	{		
		RWDrawThemeBackground( lhTheme, dc.GetSafeHdc(), TTP_STANDARD, TTSS_NORMAL, &rcClient, 0 );	
		RWCloseThemeData( lhTheme );
	}
	else
	{
		// Draw the background
		dc.FillRect(&rcClient, &(m_brBackground));	// Erase as close 
	      										// to draw as possible
	}

	// Draw the text
	dc.DrawText(strText, &m_rcText, DT_NOCLIP | DT_NOPREFIX | DT_LEFT | DT_TOP);

	// Draw the cell tip's border
	CBrush br;
	br.CreateSolidBrush(RGB(0,0,0));
	dc.FrameRect(&rcClient, &br);			// Erase as close to draw as possible

	// Clean up the DC
	dc.SelectObject(pOldFont);
	delete pNewFont;
}

/////////////////////////////////////////////////////////////////////////////
// CGXStaticBitmapCellTipWnd

CGXStaticBitmapCellTipWnd::CGXStaticBitmapCellTipWnd(CGXGridCore* pGrid)
	: CGXCellTipWnd(pGrid)
{
	m_hBitmap = NULL;
	m_dwID = GX_CELLTIP_ID_BITMAP;
}

IMPLEMENT_DYNAMIC(CGXStaticBitmapCellTipWnd, CGXCellTipWnd)

BEGIN_MESSAGE_MAP(CGXStaticBitmapCellTipWnd, CGXCellTipWnd)
	//{{AFX_MSG_MAP(CGXStaticBitmapCellTipWnd)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CGXStaticBitmapCellTipWnd::CreateTipWnd()
{
	// Create a background brush
	VERIFY(m_brBackground.CreateSolidBrush((::GetSysColor(COLOR_INFOBK))));

	return CGXCellTipWnd::CreateTipWnd();
}

void CGXStaticBitmapCellTipWnd::SetBitmapHandle(HANDLE hBitmap)
{
	// Save bitmap handle
	m_hBitmap = hBitmap;
}

void CGXStaticBitmapCellTipWnd::SetTipRect(CRect rcTip)
{
	// Set the window rect (but don't show it) so that GetClientRect will 
	// return the correct value
	SetWindowPos(NULL, rcTip.left, rcTip.top, rcTip.Width(), rcTip.Height(), 
				 SWP_HIDEWINDOW | SWP_NOACTIVATE | SWP_NOREDRAW);
}

void CGXStaticBitmapCellTipWnd::SetBitmapRect(CRect& rcBitmap)
{
	m_rcBitmap = rcBitmap;
}

void CGXStaticBitmapCellTipWnd::OnPaint()
{
	ASSERT(m_hBitmap);
	if (!m_hBitmap)
		return;

	CPaintDC dc(this); // Device context for painting

	// Get the client rect for drawing the border
	CRect rcClient;
	GetClientRect(rcClient);

	HTHEME lhTheme = NULL;
	// Note: Calling dc.GetWindow() will return an invalid handle. 
	// Instead, call AfxGetMainWnd()->GetSafeHwnd().
	if (RWIsAppThemed() && RWIsThemeActive())
		lhTheme = RWOpenThemeData (RWGetSafeHwnd(), L"TOOLTIP");
	
	if (lhTheme)
	{		
		RWDrawThemeBackground( lhTheme, dc.GetSafeHdc(), TTP_STANDARD, TTSS_NORMAL, &rcClient, 0 );	
		RWCloseThemeData( lhTheme );
	}
	else
	{
		// Draw the background
		dc.FillRect(&rcClient, &(m_brBackground));	// Erase as close 
													// to draw as possible
	}

	// Draw the bitmap
	CGXDIB::Draw(&dc, m_hBitmap, m_rcBitmap, CGXDIB::none, DT_LEFT | DT_TOP);

	// Draw the cell tip's border
	CBrush br;
	br.CreateSolidBrush(RGB(0,0,0));
	dc.FrameRect(&rcClient, &br);			// Erase as close to draw as possible
}

#endif // _MFC_VER 
