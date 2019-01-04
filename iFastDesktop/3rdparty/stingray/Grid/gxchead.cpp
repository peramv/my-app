///////////////////////////////////////////////////////////////////////////////
// gxchead.cpp : implementation of the CGXHeader control
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


#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

#define ORANGE_HIGHLIGHT RGB(255, 180, 95)

GRID_IMPLEMENT_CONTROL(CGXHeader, CGXStatic);

/////////////////////////////////////////////////////////////////////////////
// CGXHeader

CGXHeader::CGXHeader(CGXGridCore* pGrid)
	: CGXStatic(pGrid)
{
	m_clrCustomSelectionColor = ORANGE_HIGHLIGHT;
	m_bUsesCustomSelectionColor = FALSE; 
}

void CGXHeader::Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle)
{
	// Rectangle
	CRect rectItem = rect;

	CRect rectText = GetCellRect(nRow, nCol, rect);

	if (rect.right <= rect.left || rect.Width() <= 1 || rect.Height() <= 1)
		return;

	BOOL bPressed = GetMarkHeaderState(nRow, nCol, style);

	BOOL bExcelLikeHeaders = Grid()->GetParam()->GetExcelLikeHeaders();

	//for excel-like headers, flip the state
	if( bExcelLikeHeaders )
		bPressed = !bPressed;
	
	ROWCOL nCRow, nCCol;
	BOOL bCurrent = FALSE;

	if( Grid()->GetCurrentCell(nCRow, nCCol) )
	{
		if( (nCRow == nRow && nRow > 0) || (nCCol == nCol && nCol > 0) )
			bCurrent=TRUE;
	}

	// Select font
	CGXStyle style1 = style;
	if (RWIsAppThemed() && RWIsThemeActive() && bExcelLikeHeaders)
	{
	}
	else
	{
		if(bExcelLikeHeaders)
		{
			style1.SetFont(CGXFont().SetBold(bCurrent ? !bPressed : false ));
		}
	}	

	CFont* pOldFont = LoadFont(pDC, style1, pStandardStyle);

	// Cell-Color
	COLORREF rgbText = style.GetTextColor();

	if (Grid()->GetParam()->GetProperties()->GetBlackWhite())
		rgbText = RGB(0,0,0);
	
	// Background
	DrawBackground(pDC, rect, style);

	CRect rc = Grid()->SubtractBorders(rect, style, TRUE);

	CGXProperties* pProp = Grid()->GetParam()->GetProperties();

	if (style.GetDraw3dFrame() == gxFrameNormal && pProp->GetDisplay3dButtons())
	{
		// Draw button look (if not pressed)
		COLORREF rgb3dDkShadow = RGB(0, 0, 0);
			if( bExcelLikeHeaders )
                 rgb3dDkShadow = RGB(128, 128, 128);

		if (!Grid()->IsPrinting())
		{
			COLORREF rgb3dHilight = GXGetSysData()->GetSysColor(COLOR_BTNHIGHLIGHT);

			if (RWIsAppThemed() && RWIsThemeActive() && bExcelLikeHeaders)
			{					
				if (!bPressed)	
				{
					GXPatB(pDC, rc, RWGetDNETColor(RW_TBBTNFACEHOT));											

				}

				GXPatB(pDC, CRect(rc.left, rc.bottom-1, rc.right-1, rc.bottom), rgb3dDkShadow);
				GXPatB(pDC, CRect(rc.right-1, rc.top, rc.right, rc.bottom), rgb3dDkShadow);
			}
			else
			{		
				if (!bPressed)
				{
					// Draw Raised like a normal CGXHeader (looks better
					// when grid lines are turned on)
					GXDraw3dFrame(pDC, rc.left, rc.top, rc.right-1, rc.bottom-1, 1, rgb3dHilight, rgb3dDkShadow);
					if(bExcelLikeHeaders)
					{
						GXPatB(pDC, CRect(rc.left, rc.top, rc.left+1, rc.bottom), RGB(255,255,255));
						GXPatB(pDC, CRect(rc.left, rc.bottom-1, rc.right-1, rc.bottom), RGB(0,0,0));
						GXPatB(pDC, CRect(rc.right-1, rc.top, rc.right, rc.bottom), RGB(0,0,0));
						GXPatB(pDC, CRect(rc.left, rc.bottom-2, rc.right-1, rc.bottom-1), rgb3dDkShadow);
						GXPatB(pDC, CRect(rc.right-2, rc.top+1, rc.right-1, rc.bottom-1), rgb3dDkShadow);
					}
				}
				else
				{
					GXPatB(pDC, CRect(rc.left, rc.bottom-1, rc.right-1, rc.bottom), rgb3dDkShadow);
					GXPatB(pDC, CRect(rc.right-1, rc.top, rc.right, rc.bottom), rgb3dDkShadow);
					if(bExcelLikeHeaders)
					{
						GXPatB(pDC, CRect(rc.left, rc.top, rc.left+1, rc.bottom-1), RGB(255,255,255));
					}else if(UsesCustomSelectionColor())
					{
						// Custom header color here...
						// Orange highlight of row and col header.
						 GXPatB(pDC, rc, GetCustomSelectionColor());  
					}
				}			
			}			
		}
		else
		{
			// border between headers and cells when printing
			ROWCOL nhr = Grid()->GetHeaderRows();
			ROWCOL nhc = Grid()->GetHeaderCols();

			CGXPen pen(PS_SOLID, 1, RGB(0,0,0));

			if (nCol <= nhc || nRow <= nhr)
			{
				if (style.GetIncludeBorders(gxBorderBottom)
					&& style.GetBordersRef(gxBorderBottom).GetStyle() == PS_NULL
					&& pProp->GetDisplayHorzLines())
					Grid()->DrawBorder(pen, rect, gxBorderBottom, pDC);

				if (style.GetIncludeBorders(gxBorderRight)
					&& style.GetBordersRef(gxBorderRight).GetStyle() == PS_NULL
					&& pProp->GetDisplayVertLines())
					Grid()->DrawBorder(pen, rect, gxBorderRight, pDC);
			}
		}
	}

	if (RWIsAppThemed() && RWIsThemeActive() && bExcelLikeHeaders)
	{
	}
	else
	{
		if (bPressed)
		{
			// text will be moved to the bottom-right corner a bit
			rectText.top++;
			rectText.left++;
		}	
	}	
    
	pDC->SetBkMode(TRANSPARENT);

	DWORD dtAlign = style.GetHorizontalAlignment() | style.GetVerticalAlignment();

	if (style.GetWrapText())
		dtAlign |= DT_NOPREFIX | DT_WORDBREAK;
	else
		dtAlign |= DT_NOPREFIX | DT_SINGLELINE;

	pDC->SetTextColor(rgbText);

	CString sOutput;
	GetControlText(sOutput, nRow, nCol, NULL, style);

	HANDLE hbm = GXGetDIBState()->GetPool()->LookupOrCreateDIB(sOutput);
	if (hbm)
	{
		// Draw bitmap
		rect = GetCellRect(nRow, nCol, rect, &style);

		DWORD dtAlign = style.GetHorizontalAlignment() | style.GetVerticalAlignment();

		CGXDIB::Draw(pDC, hbm, rect, CGXDIB::none, (UINT) dtAlign);

		// child Controls: spin-buttons, hotspot, combobox btn, ...
		CGXControl::Draw(pDC, rect, nRow, nCol, style, pStandardStyle);
	}
	else
	{
		if (!sOutput.IsEmpty())
		{
			if (style.GetIncludeFont() 
				&& style.GetFontRef().GetIncludeOrientation() 
				&& style.GetFontRef().GetOrientation() != 0)
			{
				if (sOutput.GetLength () > 2048)
				{
#if(_MFC_VER >= 0x0700)
					sOutput.Truncate (2048);
#else
					sOutput.Left(2048);
#endif
				}
				// draw vertical text
				GXDaFTools()->GXDrawRotatedText(pDC, 
					sOutput,
					sOutput.GetLength(),
					rectText,
					(UINT) dtAlign,
					style.GetFontRef().GetOrientation(), 
					&rect);
			}
			else
			{
				// check if ellipses are to be used
				if(!style.GetIncludeUserAttribute(GX_IDS_UA_ELLIPSISTYPE))
					GXDrawTextLikeMultiLineEdit(pDC,
						sOutput,
						sOutput.GetLength(),
						rectText,
						(UINT) dtAlign,
						&rect);
				else
					GXDrawTextLikeMultiLineEditEx(pDC,
						sOutput,
						sOutput.GetLength(),
						rectText,
						(UINT) dtAlign,
						&rect, 
						((CGXEllipseUserAttribute&)style.GetUserAttribute(GX_IDS_UA_ELLIPSISTYPE)).GetEllipseValue());
			}
		}
	}

	CGXControl::Draw(pDC, rect, nRow, nCol, style, pStandardStyle);

	if (pOldFont)
		pDC->SelectObject(pOldFont);
}

void CGXHeader::InvertBorders(CDC* pDC, const CRect& r)
{
	// Mark the header as current cell
	pDC->DrawFocusRect(r);
}

BOOL CGXHeader::GetMarkHeaderState(ROWCOL nRow, ROWCOL nCol, const CGXStyle& style)
{
   BOOL b = CGXControl::GetMarkHeaderState(nRow, nCol, style);
   if( Grid()->GetParam()->GetExcelLikeHeaders() )
   {
	   CGXRangeList* pSelList = Grid()->GetParam()->GetRangeList();
	   b |= pSelList->IsAnyCellFromRow(nRow)
	      | pSelList->IsAnyCellFromCol(nCol);
   }
   return b;
}

void CGXHeader::OnGridSysColorChange()
{
	RWResetColors();
}

// SRSTUDIO-1669 Sort Header Control
GRID_IMPLEMENT_CONTROL(CGXSortHeader, CGXHeader)

// SRSTUDIO-1669 Sort Header Control
void CGXSortHeader::Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle)
{
	CGXHeader::Draw(pDC, rect, nRow, nCol, style, pStandardStyle);
	if( (Grid()->GetParam()->m_nLastSortedCol == nCol) && (0 == nRow) )
	{
		CString s = style.GetValueRef();
		CRect rectArrow = rect;
		CSize size = pDC->GetTextExtent(s);

		int w = 7;
		int h = 7;          
		if (size.cx + 2 * w < rect.Width() )
		{
			rectArrow.left = rect.right - (rect.Width()- size.cx) / 2 + w/2;
			rectArrow.right = rectArrow.left + w;
		}

		if (h < rect.Height() )
		{
			rectArrow.top += (rect.Height() - h )/2 ;
			rectArrow.bottom = rectArrow.top + h;  
		}
		if(GetMarkHeaderState(nRow, nCol, style))
		{
			rectArrow.OffsetRect( 1, 0);
		}

		int nVertex = (rectArrow.left + rectArrow.right) / 2;
		int nBase = Grid()->GetParam()->m_bSortAscending ? rectArrow.bottom : rectArrow.top;
		int nPoint = Grid()->GetParam()->m_bSortAscending ? rectArrow.top : rectArrow.bottom;

		pDC->MoveTo( rectArrow.right, nBase);
		pDC->LineTo( rectArrow.left, nBase);
		pDC->LineTo( nVertex, nPoint);
		pDC->LineTo( rectArrow.right, nBase);
	}
}