///////////////////////////////////////////////////////////////////////////////
// gxdraold.cpp:  Old Drawing (with clipping)
// Ole drawing might be necessary if you have custom cell types that don't 
// take care on clipping themselves in Draw method.
// - Or -
// If you are using the CGXGridParam::m_bTransparentBackground setting
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

#ifndef _GXEXT_H_
#include "grid\gxext.h"
#endif

#ifndef _GXCORE_H_
#include "grid\gxcore.h"
#endif

#ifndef _GXCTRL_H_
#include "grid\gxctrl.h"
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXCORDRA")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// CGXAbstractGridOldDrawingImp* m_pOldDrawingImp;
// friend class CGXGridOldDrawingImp;

class CGXGridOldDrawingImp: public CGXAbstractGridOldDrawingImp
{
public:
	virtual BOOL OnDrawTLBR(CGXGridCore* pGrid, CDC* pDC, void* pds);
	virtual void OnDrawTLBR_DrawBackground(CGXGridCore* pGrid, void* pds);
};

void CGXGridCore::ImplementOldDrawing()
{
	if (m_pOldDrawingImp == NULL)
	{
		// QA: 31521 Removal from AutoDeletePtr
		//AutoDeletePtr(m_pOldDrawingImp = new CGXGridOldDrawingImp);
		m_pOldDrawingImp = new CGXGridOldDrawingImp;
	}
}

BOOL CGXGridOldDrawingImp::OnDrawTLBR(CGXGridCore* pGrid, CDC* pDC, void* pds)
{
	CGXGridCore::DrawStruct& ds = *((CGXGridCore::DrawStruct*) pds);

	if (pGrid->m_bForceOldDrawing || pGrid->GetParam()->m_bTransparentBackground)
	{
		BOOL bCanClip = TRUE;

		// Metafiles don't support SelectClipRgn!
		if (pDC->IsKindOf(RUNTIME_CLASS(CMetaFileDC)) && !pDC->IsPrinting())
			bCanClip = FALSE;

		// 16-Bit device drivers don't support SelectClipRgn!
		if (GXGetAppData()->bWin31 && pDC->IsPrinting())
			bCanClip = FALSE;

		pGrid->m_bForceOldDrawing = TRUE;

		pGrid->OnDrawTLBR_DrawBackground(ds);

		// clipping is necessary if erasing background is not allowed

		unsigned nRow;
		for (ds.rectItem.top = ds.nyMin, nRow = 0; nRow < ds.nRows; nRow++)
		{
			ds.rectItem.bottom = ds.rectItem.top + ds.anHeights[nRow];
			ds.rectItem.left = ds.nxMin;

			if (bCanClip)
			{
				pDC->IntersectClipRect(
						CRect(ds.rectClip.left, ds.rectItem.top,
							ds.rectClip.right, ds.rectItem.bottom)
						);
			}

			// draw all columns in nRow
			unsigned nCol;
			for (nCol = 0; nCol < ds.nCols; nCol++)
			{
				ds.rectItem.right = ds.rectItem.left + ds.anWidths[nCol];

				pGrid->OnDrawTLBR_DrawCell(ds, nRow, nCol);

				ds.rectItem.left = ds.rectItem.right;

			}

			// restore original clipping region
			if (bCanClip)
			{
				pDC->SelectClipRgn(NULL);
				pDC->IntersectClipRect(ds.rectClip);
			}

			ds.rectItem.top = ds.rectItem.bottom;
		}

		// Draw Borders
		unsigned nCol;
		for (nCol = 0; nCol < ds.nCols; nCol++)
			pGrid->OnDrawTLBR_DrawVertBorders(ds, nCol);

		for (nRow = 0; nRow < ds.nRows; nRow++)
			pGrid->OnDrawTLBR_DrawHorzBorders(ds, nRow);

		// Current cell
		if (ds.pCurrentControl && !ds.rectEdit.IsRectEmpty())
			ds.pCurrentControl->InvertBorders(ds.pDC, ds.rectEdit);

		// Invert cells
		if (ds.bAnyCellSelected)
			pGrid->OnDrawTLBR_InvertCells(ds);

		return TRUE;
	}

	return FALSE;
}

void CGXGridOldDrawingImp::OnDrawTLBR_DrawBackground(CGXGridCore* pGrid, void* pds)
{
	CGXGridCore::DrawStruct& ds = *((CGXGridCore::DrawStruct*) pds);

	const COLORREF rgbWhite = RGB(255,255,255);

	CGXBrush brStandard = pGrid->m_pStyleStandard->GetInteriorRef();
	CGXBrush brDesc;
	const CGXBrush* pbrDesc;

	if (!ds.bColor)
	{
		if (brStandard.GetStyle() == BS_SOLID)
			brStandard.SetColor(rgbWhite).SetBkColor(0);
		else
			brStandard.SetBkColor(rgbWhite).SetColor(0);
	}

	if (!pGrid->GetParam()->m_bTransparentBackground)
	{
		CRect rectClip = ds.rectClip;

		if (!pGrid->IsPrinting())
		{
			// Erase unused Background to the right ...
			if (pGrid->GetCol(ds.rightCol) == pGrid->GetColCount())
			{
				CRect rect = pGrid->CalcClientRectRightFromCol(pGrid->GetCol(ds.rightCol));
				GXPatB(ds.pDC, rect.left+1, rect.top,
					rect.Width(), rect.Height()+5, pGrid->m_pParam->m_pProperties->GetColor(gxnPropBackground));
				pGrid->DrawGridLine(ds.pDC, GX_VERTLINE, ds.rightCol+1);
				rectClip.right = rect.left; // -1;
			}

			// ... and to the bottom
			if (pGrid->GetRow(ds.bottomRow) == pGrid->GetRowCount())
			{
				CRect rect = pGrid->CalcClientRectBottomFromRow(pGrid->GetRow(ds.bottomRow));
				GXPatB(ds.pDC, rect.left, rect.top+1,
					rect.Width(), rect.Height(), pGrid->m_pParam->m_pProperties->GetColor(gxnPropBackground));
				pGrid->DrawGridLine(ds.pDC, GX_HORZLINE, ds.bottomRow+1);
				rectClip.bottom = rect.top; //-1;
			}
		}

		// Standard Color
		pGrid->DrawBrushRect(ds.pDC, rectClip, brStandard);

		// Draw Rectangles
		ds.rectItem.top = ds.nyMin;

		for (unsigned nRow = 0; nRow < ds.nRows; nRow++)
		{
			ds.rectItem.bottom = ds.rectItem.top + ds.anHeights[nRow];
			ds.rectItem.left = ds.nxMin;

			for (unsigned nCol = 0; nCol < ds.nCols; nCol++)
			{
				unsigned i;
				ds.rectItem.right = ds.rectItem.left + ds.anWidths[nCol];

				if ((ds.abBits[i = nRow*ds.nCols+nCol] & gxnFlagSpanned) == 0
					&& (ds.abBits[i] & gxnFlagColor) > 0)
				{
					int nyHeight = ds.anHeights[nRow],
						nxWidth = ds.anWidths[nCol];
					const CGXBrush& brInterior = ds.apStyles[i]->GetInteriorRef();

					unsigned nToRow = nRow+1,
						nToCol = nCol+1,
						i2 = nRow*ds.nCols+nCol+1,
						i3,
						i4;

					// Width (No. of cells in current row with same color)
					while (nToCol < ds.nCols
						&& (ds.abBits[i2] & gxnFlagSpanned) == 0
						&& (ds.apStyles[i2] == NULL
							|| (ds.abBits[i2] & gxnFlagColor) > 0
								&& ds.apStyles[i2]->GetInteriorRef() == brInterior))
					{
						ds.abBits[i2] &= ~gxnFlagColor;

						nxWidth += ds.anWidths[nToCol];
						i2++, nToCol++;
					}

					// Height (No. of rows with same color)
					while (nToRow < ds.nRows)
					{
						i3 = nToRow*ds.nCols+nCol,
						i4 = nToRow*ds.nCols+nToCol;

						unsigned i5 = i3;

						while (i5 < i4
							&& (ds.abBits[i5] & gxnFlagSpanned) == 0
							&& (ds.apStyles[i5] == 0
								|| (ds.abBits[i5] & gxnFlagColor) > 0
									&& ds.apStyles[i5]->GetInteriorRef() == brInterior))
							i5++;

						if (i5 == i4)
						{
							for (i5 = i3; i5 < i4; i5++)
							{
								ds.abBits[i5] &= ~gxnFlagColor;
							}
							nyHeight += ds.anHeights[nToRow];
							nToRow++;
						}
						else
							break;
					}

					// Draw cell background in advance only if
					// we can draw more than one cell in advance

					if (nToRow == nRow+1 && nToCol == nCol+1)
					{
						ds.abBits[i2] |= gxnFlagColor;
					}
					else
					{
						if (ds.bColor)
							pbrDesc = &brInterior;
						else
						{
							brDesc = brInterior;
							if (brDesc.GetStyle() == BS_SOLID)
								brDesc.SetColor(rgbWhite).SetBkColor(0);
							else
								brDesc.SetBkColor(rgbWhite).SetColor(0);

							pbrDesc = &brDesc;
						}

						pGrid->DrawBrushRect(ds.pDC,
							CRect(ds.rectItem.left, ds.rectItem.top,
								ds.rectItem.left+nxWidth, ds.rectItem.top+nyHeight),
							*pbrDesc);
					}
				}

				ds.rectItem.left = ds.rectItem.right;
			}

			ds.rectItem.top = ds.rectItem.bottom;
		}

	}
}

