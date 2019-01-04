///////////////////////////////////////////////////////////////////////////////
// gxcprgrs.cpp : implementation of CGXProgressCtrl control
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

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXCPRGRS")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

///////////////////////////////////////////////////////////////////
// CGXProgressCtrl control

// You can register the control in the OnInitialUpdate() routine

//  CGXProgressCtrl* pProgressCtrl = new CGXProgressCtrl(this);
//  RegisterControl(GX_IDS_CTRL_PROGRESS, pProgressCtrl);
//
// You also have to register the user attributes with
//
//  CGXProgressCtrl::AddUserAttributes(GetParam()->GetStylesMap());
//
// You can apply the control to cells with
//
//  SetStyleRange(CGXRange(4,3,10,5),
//      CGXStyle()
//          .SetControl(GX_IDS_CTRL_PROGRESS)
//          .SetValue(50L)
//          .SetUserAttribute(GX_IDS_UA_PROGRESS_MIN, _T("0"))
//          .SetUserAttribute(GX_IDS_UA_PROGRESS_MAX, _T("100"))
//          .SetUserAttribute(GX_IDS_UA_PROGRESS_CAPTIONMASK, _T("%ld %%"))  // sprintf formatting for value
//          .SetTextColor(RGB(0, 0, 255))       // blue progress bar
//          .SetInterior(RGB(255, 255, 255))    // on white background
//      );
//
// You can change the value for cells at runtime by
// calling SetValueRange(), but if you need a less
// flickering way, you should call the static method
// CGXProgressCtrl::SetProgressValue. This will only
// redraw the small portion in the cell which has changed
// and not erase the whole cell.
//
// Example:
//
// void CMyGrid::UpdateProgressDisplay(LONG newValue)
// {
//     CGXProgressCtrl::SetProgressValue(this, 4, 5, newValue);
// }
//
// Note: When you change the value for a progress control,
// the progress control will not let you store invalid values.
// When you try to set a value below the lower bound or upper
// bound, the value will be adjusted so that it fits the given
// range.


GRID_IMPLEMENT_CONTROL(CGXProgressCtrl, CGXControl);

/////////////////////////////////////////////////////////////////////////////
// CGXProgressCtrl class

CGXProgressCtrl::CGXProgressCtrl(CGXGridCore* pGrid)
	: CGXControl(pGrid)
{
	ASSERT(pGrid != NULL);
}

CGXProgressCtrl::~CGXProgressCtrl()
{
}

void AFXAPI CGXProgressCtrl::AddUserAttributes(CGXStylesMap* pStylesMap)
{
	// Automatic registration of user attributes
	pStylesMap->AddUserAttribute(GX_IDS_UA_PROGRESS_MAX);
	pStylesMap->AddUserAttribute(GX_IDS_UA_PROGRESS_MIN);
	pStylesMap->AddUserAttribute(GX_IDS_UA_PROGRESS_CAPTIONMASK);
}

/////////////////////////////////////////////////////////////////////////////
// The following static function provides an optimized, less flickering
// way to update the progress bar contents of a single cell

BOOL AFXAPI CGXProgressCtrl::SetProgressValue(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, LONG newValue)
{
	// change the value, CGXProgessBar::OnDraw will be called
	BOOL b = pGrid->SetValueRange(CGXRange(nRow,nCol), (DWORD) newValue);

	return b;
}

/////////////////////////////////////////////////////////////////////////////
// virtual overrides for the caption text and color

void CGXProgressCtrl::OnGetCaption(CString& strCaption, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style)
{
	nRow, nCol; // unused:

	CString strMask;
	style.GetUserAttribute(GX_IDS_UA_PROGRESS_CAPTIONMASK, strMask);
	// override to change the caption
#if _MFC_VER >= 0x0300
	strCaption.Format(strMask, style.GetLongValue());
#else
	wsprintf(strCaption.GetBuffer(20), strMask, style.GetLongValue());
	strCaption.ReleaseBuffer();
#endif
}

COLORREF CGXProgressCtrl::OnGetCaptionColor(BOOL bForeOrBack, const CGXStyle& style)
{
	if (bForeOrBack)
		return style.GetTextColor();
	else
		return style.GetInteriorRef().GetColor();
}

COLORREF CGXProgressCtrl::OnGetCaptionTextColor(BOOL bForeOrBack, const CGXStyle& style)
{
	// Return the opposite of the background and foreground color
	if (bForeOrBack)
		return style.GetInteriorRef().GetColor();
	else
		return style.GetTextColor();

	/* You might also override this method and return
	if (bForeOrBack)
		return RGB(255,255,255)-style.GetTextColor();
	else
		return RGB(255,255,255)-style.GetInteriorRef().GetColor();
	*/
 }

/////////////////////////////////////////////////////////////////////////////
// Drawing the cell

void CGXProgressCtrl::Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle)
{
	BOOL bisBW = Grid()->GetParam()->GetProperties()->GetBlackWhite();

	// get the range
	CString strRange;
	LONG minVal, maxVal, normVal;

	strRange = style.GetUserAttribute(GX_IDS_UA_PROGRESS_MAX);//get the upper range
	maxVal = _ttol(strRange);

	strRange=style.GetUserAttribute(GX_IDS_UA_PROGRESS_MIN);//get the lower range
	minVal = _ttol(strRange);

	normVal = maxVal-minVal;

	// calculate the unit factor
	UpdateUnitFactor(rect, normVal);

	// get the colors
	COLORREF rgbCaptionBack, rgbCaptionFore;
	COLORREF rgbTextBack, rgbTextFore;

	if (!bisBW)
	{
		rgbCaptionFore = OnGetCaptionColor(TRUE, style);
		rgbCaptionBack = OnGetCaptionColor(FALSE, style);
		rgbTextFore = OnGetCaptionTextColor(TRUE, style);
		rgbTextBack = OnGetCaptionTextColor(FALSE, style);
	}
	else
	{
		rgbCaptionFore = RGB(0,0,0);
		rgbCaptionBack = RGB(255,255,255);
		rgbTextFore = RGB(255,255,255);
		rgbTextBack = RGB(0,0,0);
	}

	// caption text
	CString strCaption;
	OnGetCaption(strCaption, nRow, nCol, style);

	// Caption bar and background rectangles
	CRect captionRect = GetUpdateRect(style.GetLongValue(), rect, style);
	CRect backRect;
	backRect.SubtractRect(rect, captionRect);

	HTHEME lhTheme = NULL;
	if (RWIsAppThemed() && RWIsThemeActive())
		lhTheme = RWOpenThemeData (RWGetSafeHwnd(), L"PROGRESS");

	if (lhTheme)
	{				
		RWDrawThemeBackground( lhTheme, pDC->GetSafeHdc(), PP_BAR, 0, &rect, 0 );				
		RWDrawThemeBackground( lhTheme, pDC->GetSafeHdc(), PP_CHUNK, 0, &captionRect, 0 );

		RWCloseThemeData( lhTheme );
	}
	else
	{
		// draw the background rectangle
		GXPatB(pDC, backRect, rgbCaptionBack);// change to client rect

		// draw the caption rectangle
		GXPatB(pDC, captionRect, rgbCaptionFore);

		// Draw 3d effects for the caption bar
		if (captionRect.Width() > 1)
		{
			switch (style.GetDraw3dFrame())
			{
				case gxFrameRaised:
					GXDrawEdge(pDC, captionRect, EDGE_RAISED, FALSE);
					break;

				case gxFrameInset:
					GXDrawEdge(pDC, captionRect, EDGE_SUNKEN, FALSE);
					break;

				default:
					break; // do nothing
			}
		}	
	}

	// Select font
	CFont* pOldFont = LoadFont(pDC, style, pStandardStyle);

	// Draw text only if it completely fits into the cell
	CSize size = pDC->GetTextExtent(strCaption, strCaption.GetLength());

	if (size.cx < rect.Width())
	{
		int oldBkMode = pDC->SetBkMode(TRANSPARENT);

		// center text horizontal and vertical
		CPoint ptText;
		ptText.x = rect.left + (rect.Width()-size.cx)/2;
		ptText.y = rect.top + (rect.Height()-size.cy)/2;

		// check if text needs to be draw in foreground and background area
		BOOL bFore = ptText.x < captionRect.right;
		BOOL bBack = ptText.x + size.cx >= captionRect.right;

		COLORREF oldTextColor = pDC->GetTextColor();

		if (bBack)
		{
			// draw full text with background color
			pDC->SetTextColor(rgbTextBack);

			pDC->TextOut(ptText.x, ptText.y, strCaption, strCaption.GetLength());
		}

		if (bFore)
		{
			// draw the caption bar part of the text
			pDC->SetTextColor(rgbTextFore);

			BOOL bCanClip = TRUE;
			
			// Metafiles don't support SelectClipRgn!
			if (pDC->IsKindOf(RUNTIME_CLASS(CMetaFileDC)) && !pDC->IsPrinting())
				bCanClip = FALSE;

			// 16-Bit device drivers don't support SelectClipRgn!
			if (GXGetAppData()->bWin31 && pDC->IsPrinting())
				bCanClip = FALSE;

			// if text goes beyond caption bar, clip it
			if (bBack && bCanClip)
			{
				// we need to clip this text
				CRect rectClip;
				pDC->GetClipBox(&rectClip); // stored
				pDC->SelectClipRgn(NULL);
				pDC->IntersectClipRect(&captionRect);

				pDC->TextOut(ptText.x, ptText.y, strCaption, strCaption.GetLength());

				// restore clipping area
				pDC->SelectClipRgn(NULL);
				pDC->IntersectClipRect(&rectClip);
			}
			else // all text is in caption bar
			{
				// simply draw it
				pDC->TextOut(ptText.x, ptText.y, strCaption, strCaption.GetLength());
			}
		}

		pDC->SetTextColor(oldTextColor);
		pDC->SetBkMode(oldBkMode);
	}

	if (pOldFont)
		pDC->SelectObject(pOldFont);
}

/////////////////////////////////////////////////////////////////////////////
// Validating and adjusting the value

// StoreStyle
//
// StoreStyle lets you validate any input before it
// is stored in the grid.

BOOL CGXProgressCtrl::StoreStyle(ROWCOL nRow, ROWCOL nCol, const CGXStyle* pStyle, GXModifyType mt, int nType, const CGXStyle* pOldStyle)
{
	LONG maxVal, minVal, value;

	// check if value is to be changed
	if (mt != gxRemove && pStyle && pStyle->GetIncludeValue())
	{
		value = pStyle->GetLongValue();

		if (pStyle->GetIncludeUserAttribute(GX_IDS_UA_PROGRESS_MAX))
			maxVal = _ttol(pStyle->GetUserAttribute(GX_IDS_UA_PROGRESS_MAX));
		else
			maxVal = _ttol(pOldStyle->GetUserAttribute(GX_IDS_UA_PROGRESS_MAX));

		if (pStyle->GetIncludeUserAttribute(GX_IDS_UA_PROGRESS_MIN))
			minVal = _ttol(pStyle->GetUserAttribute(GX_IDS_UA_PROGRESS_MIN));
		else
			minVal = _ttol(pOldStyle->GetUserAttribute(GX_IDS_UA_PROGRESS_MIN));

		// adjust value if outside boundaries
		if (value < minVal || value > maxVal)
		{
			CGXStyle* pStyleEx = pStyle->Clone();

			pStyleEx->SetValue((DWORD) max(minVal, min(maxVal, value)));

			BOOL b = CGXControl::StoreStyle(nRow, nCol, pStyleEx, mt, nType, pOldStyle);

			Grid()->RecycleStyle(pStyleEx);

			return b;
		}
	}

	return CGXControl::StoreStyle(nRow, nCol, pStyle, mt, nType, pOldStyle);
}

///////////////////////////////////////////////////////////////////
// Implemenation

CRect CGXProgressCtrl::GetUpdateRect(LONG newValue, CRect boundRect, const CGXStyle& style)
{
	CRect rect;
	CString str;

	LONG minVal = _ttol(style.GetUserAttribute(GX_IDS_UA_PROGRESS_MIN));

	//make the range zero based for calculation
	newValue = max(minVal, newValue)-minVal;//subtract the minimum value
	rect.SetRect(boundRect.left,
		boundRect.top,
		boundRect.left+(int) (newValue/m_unitFactor),
		boundRect.bottom);

	return rect;
}

void CGXProgressCtrl::UpdateUnitFactor(CRect boundRect, LONG rangeVal)
{
	// factor number of value units per pixel
	if (boundRect.Width())
		m_unitFactor = (double) rangeVal / (double)boundRect.Width(); // divide by the width
	else
		m_unitFactor = 1;
}
