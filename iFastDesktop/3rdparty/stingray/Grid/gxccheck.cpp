///////////////////////////////////////////////////////////////////////////////
// gxccheck.cpp : implementation of the CGXCheckBox control
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

#ifndef _GXCORE_H_
#include "grid\gxcore.h"
#endif

#ifndef _GXCTRLI_H_
#include "grid\gxctrli.h"
#endif

#ifndef _GXDLL_H_
#include "grid\gxdll.h" // GXGetResourceHandle
#endif


#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXCCHECK")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif


GRID_IMPLEMENT_CONTROL(CGXCheckBox, CGXControl);

/////////////////////////////////////////////////////////////////////////////
// CGXCheckBox control

// support for changing the checkbox bitmap colors
BOOL CGXCheckBox::m_gbCheckClrInc = FALSE;
COLORREF CGXCheckBox::m_grgbFrame = GetSysColor(COLOR_WINDOWFRAME);
COLORREF CGXCheckBox::m_grgbBack = GetSysColor(COLOR_WINDOW);

CGXCheckBox::CGXCheckBox(CGXGridCore* pGrid, BOOL bDraw3d /* = TRUE */, UINT nBitmapResourceId /* = 0 */, UINT nPrintResourceId /* = 0 */)
: CGXControl(pGrid)
{
	m_bScope = FALSE;
	m_bDraw3d = bDraw3d;
	m_hbitmapCheck = 0;
	m_hbitmapPrint = 0;
	m_nCheckBoxSize = 13;

	if (nBitmapResourceId)
		// user defined bitmap
		m_nBitmapResourceId = nBitmapResourceId;
	else
	{
		// Default bitmaps
		if (!bDraw3d)
			m_nBitmapResourceId = GX_IDB_CHECK_FLAT;
		else if (GXGetAppData()->bWin4)
			m_nBitmapResourceId = GX_IDB_CHECK_95;
		else
			m_nBitmapResourceId = GX_IDB_CHECK_NT;
	}

	if (nPrintResourceId)
		// user defined bitmap
		m_nPrintResourceId = nPrintResourceId;
	else
		m_nPrintResourceId = GX_IDB_CHECK_FLAT;
}

CGXCheckBox::~CGXCheckBox()
{
	// We have to call GlobalFree because GXLoadResourceBitmap
	// did call GlobalAlloc to copy the bitmap from the resource
	// into memory.

	if (m_hbitmapCheck != 0)
		::GlobalFree(m_hbitmapCheck);

	if (m_hbitmapPrint != 0)
		::GlobalFree(m_hbitmapPrint);
}

void AFXAPI CGXCheckBox::AddUserAttributes(CGXStylesMap* pStylesMap)
{
	// Checkbox, checked/uncheck represantation
	pStylesMap->AddUserAttribute(GX_IDS_UA_CHECKBOX_CHECKED);
	pStylesMap->AddUserAttribute(GX_IDS_UA_CHECKBOX_UNCHECKED);
}

void CGXCheckBox::SetCheckBackColor(COLORREF rgb)
{
	m_grgbBack = rgb;
	m_gbCheckClrInc = TRUE;
}

void CGXCheckBox::SetCheckFrameColor(COLORREF rgb)
{
	m_grgbFrame = rgb;
	m_gbCheckClrInc = TRUE;
}

void CGXCheckBox::ResetCheckColorScheme()
{
	m_gbCheckClrInc = FALSE;
}


BOOL CGXCheckBox::LoadBitmap()
{
	if (m_hbitmapCheck != 0)
		::GlobalFree(m_hbitmapCheck);

	if (m_hbitmapPrint != 0)
		::GlobalFree(m_hbitmapPrint);

	// Load bitmap from resource and copy it into memory

	HINSTANCE hSaveResource = AfxGetResourceHandle(); // save resource handle
	AfxSetResourceHandle(GXGetResourceHandle());    // switch resource handle to dll

	// First, try resource handle
	HINSTANCE hInst = AfxFindResourceHandle(MAKEINTRESOURCE(m_nBitmapResourceId), RT_BITMAP);
	m_hbitmapCheck = GXLoadResourceBitmap(hInst, MAKEINTRESOURCE(m_nBitmapResourceId));

	// If failed, try instance handle
	if (m_hbitmapCheck == 0)
	{
		hInst = AfxGetInstanceHandle();
		m_hbitmapCheck = GXLoadResourceBitmap(hInst, MAKEINTRESOURCE(m_nBitmapResourceId));
	}

	if (m_hbitmapCheck == 0)
		return FALSE;

	m_hbitmapPrint = GXLoadResourceBitmap(hInst, MAKEINTRESOURCE(m_nPrintResourceId));

	AfxSetResourceHandle(hSaveResource);    // reset resource handle

	// Loop through color table and replace system colors
	for (int nbmIndex = 0; nbmIndex < 2; nbmIndex++)
	{
		HANDLE hbm = (nbmIndex == 0) ? m_hbitmapCheck : m_hbitmapPrint;
		LPSTR lpDIB = (LPSTR) GlobalLock(hbm);

		DWORD dwColors = GXGetNumDIBColorEntries((LPBITMAPINFO)lpDIB);

		for (DWORD i = 0; i < dwColors; i++)
		{
			RGBQUAD* pColor = &((LPBITMAPINFO)lpDIB)->bmiColors[i];

			COLORREF rgbOld = RGB(pColor->rgbRed, pColor->rgbGreen, pColor->rgbBlue);

			COLORREF rgbNew = GetColorValue(rgbOld, nbmIndex);

			// replace color
			if (rgbOld != rgbNew)
			{
				pColor->rgbGreen = GetGValue(rgbNew);
				pColor->rgbBlue = GetBValue(rgbNew);
				pColor->rgbRed = GetRValue(rgbNew);
			}
		}

		GlobalUnlock(hbm);
	}

	return TRUE;
}

void CGXCheckBox::OnGridSysColorChange()
{
	// Reinitialize bitmaps
	LoadBitmap();
}

COLORREF CGXCheckBox::GetColorValue(COLORREF rgb, BOOL bPrint)
{
	// check if there are explicit colors specified
	COLORREF refF = m_gbCheckClrInc ? m_grgbFrame : GetSysColor(COLOR_WINDOWFRAME);
	COLORREF refB = m_gbCheckClrInc ? m_grgbBack : GetSysColor(COLOR_WINDOW);

	switch (rgb)
	{
	case RGB(255, 0, 0):
		return bPrint ? RGB(255, 255, 255) : refB;

	case RGB(0, 255, 0):
		return refF;

	case RGB(192, 192, 192):
		return GetSysColor(COLOR_BTNFACE);

	case RGB(0, 0, 0):
		return bPrint ? RGB(0, 0, 0) : GetSysColor(COLOR_WINDOWTEXT);

	default:
		return rgb;
	}
}

CRect CGXCheckBox::ComputeCheckBoxRect(CDC* pDC, CRect rect, LPCTSTR lpszString, DWORD dtAlign)
{
	int x = rect.left;
	int y = rect.top;
	int dx = rect.Width();
	int dy = rect.Height();

	int yHeight = m_nCheckBoxSize,    // height needed for text and checkbox
		xWidth = m_nCheckBoxSize;     // width needed for text and checkbox
	int len = (int)_tcslen(lpszString);

	TEXTMETRIC tm;
	pDC->GetTextMetrics(&tm);

	if (len > 0)
	{
		CSize size = pDC->GetTextExtent(lpszString, len);

		yHeight = min(tm.tmHeight+tm.tmInternalLeading, m_nCheckBoxSize);  // 601 -changed max to min
		xWidth = size.cx + m_nCheckBoxSize*3/2;
	}

	// compute rectangle for checkbox
	//	int xOffs = x + max(0, min(3, dx-xWidth)),
	//		yOffs = y + max(0, min(3, dy-yHeight));
	int xOffs = x + 3,	// Old code will cause checkboxes to be unaligned between 2 cells even
		// though they are both left aligned.
		yOffs = y + max(0, min(3, dy-yHeight));

	if (dtAlign & DT_CENTER)
		xOffs = x + max((dx-xWidth)/2, 0);
	else if (dtAlign & DT_RIGHT)
		xOffs = x + max(dx-xWidth, 0);

	if (dtAlign & DT_VCENTER)
		yOffs = y + max(abs(dy-yHeight)/2, 0); // 601 - added abs()
	else if (dtAlign & DT_BOTTOM)
		yOffs = y + max(dy-yHeight, 0);
	int xCorner = min(x+dx, xOffs + m_nCheckBoxSize),
		yCorner = min(y+dy, yOffs + m_nCheckBoxSize);

	return CRect(xOffs, yOffs, xCorner, yCorner);
}

void CGXCheckBox::DrawCheckBox(CDC* pDC, CRect rect, UINT nState, DWORD dtAlign, LPCTSTR lpszString)
{
	HTHEME lhTheme = NULL;
	if (RWIsAppThemed() && RWIsThemeActive())
		lhTheme = RWOpenThemeData (RWGetSafeHwnd(), L"BUTTON");

	if (lhTheme && m_nBitmapResourceId==GX_IDB_CHECK_95)
	{
		DrawXPCheckBox(lhTheme, pDC, rect, nState, dtAlign, lpszString);
		RWCloseThemeData( lhTheme );
	}
	else
	{
		CRect r = ComputeCheckBoxRect(pDC, rect, lpszString, dtAlign);

		int xOffs = r.left,
			yOffs = r.top,
			xCorner = r.right,
			yCorner = r.bottom;

		CBrush br(pDC->GetTextColor());

		CBrush* pOldBrush = pDC->SelectObject(&br);

		if (m_hbitmapCheck == 0)
		{
			if (!LoadBitmap())
			{
				TRACE(_T("Warning: bitmap could not be loaded in CGXCheckBox::DrawCheckBox!\n"));
				return;
			}
		}

		int dx = m_nCheckBoxSize;

		// the checkboxes are arranges as follows in the bitmap:
		// 0) unchecked
		// 1) checked
		// 2) unchecked with scope (grey backgorund)
		// 3) checked with scope (grey backgorund)
		// 4) indetermined

		// compute offset in 3dctrl bitmap
		int offset = 0;

		if (nState & GX_BTNSCOPE)
			offset = 2;

		if (nState & GX_BTNCHECKED)
			offset++;
		else if (!(nState & GX_BTNUNCHECKED))
			// indetermined state, gray box
			offset = 4;

		HANDLE hbm = (!Grid()->IsPrinting()) ? m_hbitmapCheck : m_hbitmapPrint;

		// Bitmap Info, width and height
		LPSTR lpDIB = (LPSTR) GlobalLock(hbm);

		BITMAPINFO* pBMI = (BITMAPINFO *) lpDIB;

		// Look at color table size, and work out where image bits start
		DWORD dwColorTableSize;
		DWORD dwColors = GXGetNumDIBColorEntries((LPBITMAPINFO)lpDIB);
		dwColorTableSize = dwColors * sizeof(RGBQUAD);
		LPSTR pBits = lpDIB + sizeof(BITMAPINFOHEADER) + dwColorTableSize;

		int dx2 = min(dx, xCorner-xOffs);
		int dy2 = min(dx, yCorner-yOffs);

		::StretchDIBits(pDC->GetSafeHdc(),
			xOffs, yOffs,
			dx2, dy2,
			dx*offset, 0,
			dx, dx,
			pBits,                    // Pointer to bits
			pBMI,                     // BITMAPINFO
			DIB_RGB_COLORS,           // Options
			SRCCOPY);                 // Raster operator code (ROP)

		::GlobalUnlock(hbm);

#if _MFC_VER >= 0x0300 && !defined(_MAC)
		if (m_bDraw3d && !pDC->IsPrinting())
			pDC->DrawEdge(CRect(xOffs, yOffs, xOffs+dx2, yOffs+dy2), EDGE_SUNKEN, BF_ADJUST);
#endif

		pDC->SelectObject(pOldBrush);
	}
}

void CGXCheckBox::DrawXPCheckBox(HTHEME lhTheme, CDC* pDC, CRect rect, UINT nState, DWORD dtAlign, LPCTSTR lpszString)
{
	m_rectBox = ComputeCheckBoxRect(pDC, rect, lpszString, dtAlign);
	CRect r = m_rectBox;

	int xOffs = r.left,
		yOffs = r.top,
		xCorner = r.right,
		yCorner = r.bottom;

	int dx = m_nCheckBoxSize;

	// the checkboxes are arranges as follows in the bitmap:
	// 0) unchecked
	// 1) checked
	// 2) unchecked with scope (grey backgorund)
	// 3) checked with scope (grey backgorund)
	// 4) indetermined

	// compute offset in 3dctrl bitmap
	int offset = 0;

	if (nState & GX_BTNSCOPE)
		offset = 2;

	if (nState & GX_BTNCHECKED)
		offset++;
	else if (!(nState & GX_BTNUNCHECKED))
		// indetermined state, gray box
		offset = 4;

	int dx2 = min(dx, xCorner-xOffs);
	int dy2 = min(dx, yCorner-yOffs);

	int checkState;		
	switch(offset)
	{
	case 0 :
		checkState = CBS_UNCHECKEDNORMAL;
		break;

	case 1 :
		checkState = CBS_CHECKEDNORMAL;
		break;

	case 2 :
		checkState = CBS_UNCHECKEDPRESSED;	
		break;

	case 3 :
		checkState = CBS_CHECKEDPRESSED;							
		break;

	case 4 :
		checkState = CBS_CHECKEDDISABLED;		
		break;
	default :
		checkState = CBS_CHECKEDNORMAL;
	}		

	r = CRect (xOffs, yOffs, xOffs + dx2, yOffs + dy2);
	RWDrawThemeBackground( lhTheme, pDC->GetSafeHdc(), BP_CHECKBOX, checkState, &r, 0 );
}

UINT CGXCheckBox::GetState(ROWCOL nRow, ROWCOL nCol, const CGXStyle& style)
{
	WORD w = 0;

	if (!style.GetEnabled())
		w |= GX_BTNSCOPE;

	if (IsInit() && Grid()->IsCurrentCell(nRow, nCol))
	{
		w |= GX_BTNFOCUS;

		if (m_bScope)
			w |= GX_BTNSCOPE;
	}

	// Load representations for TRUE/FALSE
	CString strTrue, strFalse;
	style.GetUserAttribute(GX_IDS_UA_CHECKBOX_CHECKED, strTrue);
	if (strTrue.IsEmpty())
		strTrue = _T("1");

	style.GetUserAttribute(GX_IDS_UA_CHECKBOX_UNCHECKED, strFalse);
	if (strFalse.IsEmpty())
		strFalse = _T("0");

	BOOL bTriState = style.GetIncludeTriState() && style.GetTriState();
	const CString& strVal = style.GetValueRef();

	if (strVal == strTrue)
		w |= GX_BTNCHECKED;
	else if (!bTriState
		|| strVal == strFalse)
		w |= GX_BTNUNCHECKED;
	// else
	// indetermined

	return w;
}

void CGXCheckBox::Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle)
{
	UINT w = GetState(nRow, nCol, style);

	DWORD dtAlign = DT_LEFT;
	if (style.GetIncludeHorizontalAlignment())
		dtAlign = style.GetHorizontalAlignment();

	if (style.GetIncludeVerticalAlignment())
		dtAlign |= style.GetVerticalAlignment();

	// Select font
	CFont* pOldFont = LoadFont(pDC, style, pStandardStyle);

	DrawBackground(pDC, rect, style);

	pDC->SetBkMode(TRANSPARENT);
	pDC->SetBkColor(style.GetInteriorRef().GetColor());
	pDC->SetTextColor(style.GetTextColor());

	CRect rectInterior = GetCellRect(nRow, nCol, rect);

	LPCTSTR szText = style.GetIncludeChoiceList()
		? (LPCTSTR) style.GetChoiceListRef()
		: _T("");

	DrawCheckBox(pDC, rectInterior, w, dtAlign, szText);

	CRect rectText = rectInterior;
	rectText.left += m_nCheckBoxSize*3/2;

	if (_tcslen(szText) > 0 && rectText.left < rectText.right)
	{
		if (style.GetWrapText())
			dtAlign |= DT_NOPREFIX | DT_WORDBREAK;
		else
			dtAlign |= DT_NOPREFIX | DT_SINGLELINE;

		GXDrawTextLikeMultiLineEdit(pDC,
			szText,
			-1,
			rectText,
			(UINT) dtAlign,
			&rect);
	}

	CGXControl::Draw(pDC, rect, nRow, nCol, style, pStandardStyle);

	if (pOldFont)
		pDC->SelectObject(pOldFont);
}

CSize CGXCheckBox::CalcSize(CDC* pDC, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle, BOOL bVert)
{
	// unused parameters:
	bVert, nRow, nCol;

	// Determine current size of cell (and take care if cell
	// is a covered, merged or float cell) and subtract space 
	// needed for borders, 3d-Frame or grid-lines with GetCellRect
	//
	// Don't call CalcRectFromRowCol because the calculation
	// of CalcRectFromRowCol is based on the current top
	// row and last visible row. If the cell is not visible,
	// the CRect would then be empty and that's not what we
	// want!

	CGXRange area = CGXRange(nRow, nCol);
	Grid()->GetCellRangeRowCol(nRow, nCol, area);
	CRect rc(0, 0, Grid()->CalcSumOfColWidths(area.left, area.right), Grid()->CalcSumOfRowHeights(area.top, area.bottom));
	rc = GetCellRect(nRow, nCol, rc, &style);
	CSize size(rc.Width(), rc.Height());

	// Select font
	CFont* pOldFont = LoadFont(pDC, style, pStandardStyle);

	CString sOutput = style.GetIncludeChoiceList() ? (LPCTSTR) style.GetChoiceListRef() : _T("");

	int dx = m_nCheckBoxSize;
	int ycbHeight = dx + 4,    // height needed for text and checkbox
		xcbWidth = dx + 6;     // width needed for text and checkbox

	rc.left += m_nCheckBoxSize*3/2;

	// BLOCK
	{
		DWORD dtAlign = style.GetHorizontalAlignment() | style.GetVerticalAlignment();

		int xFrame = max(GetSystemMetrics(SM_CXFRAME)/2, 3);

		if (!sOutput.IsEmpty())
		{
			dtAlign |= DT_NOPREFIX | DT_WORDBREAK;

			TEXTMETRIC    tm;
			pDC->GetTextMetrics(&tm);
			int dyHeight = tm.tmHeight + tm.tmExternalLeading;

			BOOL bWrap = style.GetIncludeWrapText() && style.GetWrapText();

			int nLineBreaks = 1;

			CRect rcTemp(rc.left, rc.top, rc.right, 32767);

			int LineBreaks[32], LineLengths[32];

			if (bWrap)
				nLineBreaks = GXComputeLineBreaks(pDC,
				sOutput,
				-1,
				rcTemp,
				(UINT) dtAlign,
				LineBreaks,
				LineLengths,
				32);

			if (bVert)
			{
				if (bWrap)
					size.cy = nLineBreaks*(dyHeight+1);
				else
					size.cy = (dyHeight+1);
			}
			else
			{
				CSize sz;

				int height = 0;
				int width = 0;

				// Optimize the width to be large enough for a single line
				// only if the cell is not large enough or if wraptext is FALSE
				if (!bWrap || nLineBreaks*(dyHeight+1) > rc.Height())
				{
					// The following loop determines the width of
					// each line of text (separated with a newline).

					CString s = sOutput;
					CString sItem;
					int n = 0;
					while (!s.IsEmpty() && n != -1)
					{
						n = GXGetNextLine(s, sItem);

						sz = pDC->GetTextExtent(sItem, sItem.GetLength());
						width = max(width, sz.cx + xFrame*2);
						height += sz.cy;
					}
					size.cx = width;
				}
				else
				{
					// Find the minimum width which is large enough for all
					// wrapped lines in a multline cell where the cells
					// row height is high enough.

					LPCTSTR lpszString = sOutput;

					for (int nBreak = 0; nBreak < nLineBreaks; nBreak++)
					{
						sz = pDC->GetTextExtent(lpszString+LineBreaks[nBreak], LineLengths[nBreak]);
						width = max(width, sz.cx + xFrame*2);
						height += sz.cy;
					}
					size.cx = width;
				}
			}
		}
		else
		{
			// no value
			size.cx = size.cy = 0;

			TEXTMETRIC    tm;
			pDC->GetTextMetrics(&tm);
			int dyHeight = tm.tmHeight + tm.tmExternalLeading;

			size.cy = dyHeight+1;
			size.cx = tm.tmMaxCharWidth + xFrame*2;
		}
	}

	if (pOldFont)
		pDC->SelectObject(pOldFont);

	return AddBorders(CSize(size.cx+xcbWidth, max(size.cy, ycbHeight)), style);
}

BOOL CGXCheckBox::LButtonDown(UINT nFlags, CPoint pt, UINT nHitState)
{
	nHitState, pt, nFlags;

	// style
	const CGXStyle& style = Grid()->LookupStyleRowCol(m_nRow, m_nCol);

	if (IsReadOnly() || style.GetIncludeReadOnly() && style.GetReadOnly())
		return FALSE;

	// compute checkbox rectangle for mouse hit-testing
	CRect rect = GetCellRect(m_nRow, m_nCol, NULL, &style);

	DWORD dtAlign = DT_LEFT;
	if (style.GetIncludeHorizontalAlignment())
		dtAlign = style.GetHorizontalAlignment();

	if (style.GetIncludeVerticalAlignment())
		dtAlign |= style.GetVerticalAlignment();

	CClientDC dc(GridWnd());
	Grid()->OnGridPrepareDC(&dc);

	// Select font
	CFont* pOldFont = LoadFont(&dc, style, NULL);

	m_rectBox = ComputeCheckBoxRect(&dc, rect,
		style.GetIncludeChoiceList() ? (LPCTSTR) style.GetChoiceListRef() : _T(""),
		dtAlign);


	if (pOldFont)
		dc.SelectObject(pOldFont);

	if (m_rectBox.PtInRect(pt))
	{
		m_bScope = TRUE;
		Refresh();
	}

	// check child buttons
	CGXControl::LButtonDown(nFlags, pt, nHitState);

	return TRUE;
}

BOOL CGXCheckBox::LButtonUp(UINT nFlags, CPoint pt, UINT nHitState)
{
	nHitState, pt, nFlags;

	m_bScope = FALSE;

	// check child buttons
	if (!CGXControl::LButtonUp(nFlags, pt, nHitState) && nHitState & GX_HITINCELL)
	{
		if (m_rectBox.PtInRect(pt))
			OnClickedButton(NULL);

	}

	return TRUE;
}

BOOL CGXCheckBox::MouseMove(UINT nFlags, CPoint pt, UINT nHitState)
{
	nHitState, pt, nFlags;

	BOOL bState = nHitState & GX_HITINCELL && m_rectBox.PtInRect(pt);

	if (bState != m_bScope)
	{
		m_bScope = bState;
		Refresh();
	}

	// check child buttons
	CGXControl::MouseMove(nFlags, pt, nHitState);

	return TRUE;
}

BOOL CGXCheckBox::LButtonDblClk(UINT nFlags, CPoint pt)
{
	pt, nFlags;

	m_bScope = FALSE;

	// check child buttons
	if (!CGXControl::LButtonDblClk(nFlags, pt))
	{
		if (m_rectBox.PtInRect(pt))
			OnClickedButton(NULL);
	}

	return TRUE;
}

BOOL CGXCheckBox::KeyPressed(UINT nMessage, UINT nChar, UINT nRepCnt, UINT flags)
{
	BOOL bRet = CGXControl::KeyPressed(nMessage, nChar, nRepCnt, flags);

	if (!bRet && nMessage == WM_CHAR && nChar == 32)
	{
		// trigger event
		OnClickedButton(NULL);
		return TRUE;
	}

	return bRet;
}

void CGXCheckBox::OnClickedButton(CGXChild* pChild)
{
	if (!OnStartEditing())
		return;

	// style
	const CGXStyle& style = Grid()->LookupStyleRowCol(m_nRow, m_nCol);

	if (IsReadOnly() || style.GetIncludeReadOnly() && style.GetReadOnly())
		return;

	BOOL bTriState = style.GetIncludeTriState() && style.GetTriState();

	// Load representations for TRUE/FALSE
	CString strTrue, strFalse;

	style.GetUserAttribute(GX_IDS_UA_CHECKBOX_CHECKED, strTrue);
	if (strTrue.IsEmpty())
		strTrue = _T("1");

	style.GetUserAttribute(GX_IDS_UA_CHECKBOX_UNCHECKED, strFalse);
	if (strFalse.IsEmpty())
		strFalse = _T("0");

	// Switch to next value
	CString strVal = style.GetValueRef();

	// checked to unchecked
	if (strVal == strTrue)
		strVal = strFalse;

	// unchecked to grayed
	else if (bTriState && strVal == strFalse)
		strVal.Empty();

	// if !bTriState did fall through
	// grayed to checked
	else
		strVal = strTrue;

	// Store value
	Grid()->SetValueRange(CGXRange(m_nRow, m_nCol), strVal, gxOverride);

	CGXControl::OnClickedButton(pChild);
}

BOOL CGXCheckBox::ConvertControlTextToValue(CString& str, ROWCOL nRow, ROWCOL nCol, const CGXStyle* pOldStyle)
{
	CGXStyle* pStyle = NULL;
	if (pOldStyle == NULL)
	{
		pStyle = Grid()->CreateStyle();
		Grid()->ComposeStyleRowCol(nRow, nCol, pStyle);
		pOldStyle = pStyle;
	}

	// Load representations for TRUE/FALSE
	CString strTrue, strFalse;
	pOldStyle->GetUserAttribute(GX_IDS_UA_CHECKBOX_CHECKED, strTrue);
	if (strTrue.IsEmpty())
		strTrue = _T("1");

	pOldStyle->GetUserAttribute(GX_IDS_UA_CHECKBOX_UNCHECKED, strFalse);
	if (strFalse.IsEmpty())
		strFalse = _T("0");

	BOOL bTriState = pOldStyle->GetIncludeTriState() && pOldStyle->GetTriState();

	if (str.CompareNoCase(strTrue) == 0)
		NULL;	// valid str
	else if (!bTriState
		|| str.CompareNoCase(strFalse) == 0)
		NULL;	// valid str
	else
		str.Empty();

	if (pStyle)
		Grid()->RecycleStyle(pStyle);

	return TRUE;
}

void CGXCheckBox::OnGridCancelMode()
{
	if (m_bScope)
	{
		m_bScope = FALSE;
		Refresh();
	}
}
