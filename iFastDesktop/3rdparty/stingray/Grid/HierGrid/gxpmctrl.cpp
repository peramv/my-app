///////////////////////////////////////////////////////////////////////////////
// gxpmctrl.cpp : implementation for the CGXPMControl
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

#ifndef GX_PMCONTROL
#include "grid\HierGrid\gxpmctrl.h"
#endif

#ifndef _GX_HIERARCHY_GRID
#include "grid\HierGrid\gxhiergrid.h"
#endif

#ifndef _SFL_SECDC_H_
#include "Foundation\Graphics\MFC\secdc.h"
#endif

using namespace stingray::foundation;

// Forward
class stingray::foundation::SECMemDC;

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_PMCTRL")
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

GRID_IMPLEMENT_CONTROL(CGXPMControl, CGXControl);

CGXPMControl::CGXPMControl(CGXGridCore* pGrid)
: CGXControl(pGrid) 
{
	m_nAlignment = center;
}

CGXPMControl::~CGXPMControl()
{
}

BOOL CGXPMControl::CreateControl(int /*nID*/)
{
	return TRUE;
}

// Operations
void CGXPMControl::Init(ROWCOL nRow, ROWCOL nCol)
{
	// Stores the cell coordinates, resets the style and sets the window text
	CGXControl::Init(nRow, nCol);

	SetActive(FALSE);

	NeedStyle();
	SetValue(m_pStyle->GetValueRef());

	SetModify(FALSE);
}

void CGXPMControl::SetValue(LPCTSTR pszRawValue)
{
	m_nState = _ttoi(pszRawValue);
}

BOOL CGXPMControl::GetValue(CString & strResult)
{
	// Reads out the control state and converts it into
	// the plain value which should be stored in the style object.

	if (!IsInit())
		return FALSE;

	if (GetModify())
	{
		int nState = m_nState;
		strResult.Format(_T("%d"),nState);
		return TRUE;
	}
	else 
		return CGXControl::GetValue(strResult);
}

// Code taken off the MVC code.
void CGXPMControl::DrawPMBox(CDC* pDC, CRect& outRect, const CGXStyle& style)
{
//		CRect outRect = ((CPMModel*)GetModel())->GetCurrentRect();
		
	// Box is too small to draw the PM Control.
	if(((outRect.right - outRect.left) <= 12) || ((outRect.bottom - outRect.top) <= 12) )
		return ;

	int iBottom(0);

	if(m_nState == 1) // NoteToSelf: Change '1' to EXPANDED
		iBottom = m_nLogicalCenter;
	else 
		iBottom = outRect.bottom;

	CRect boundRect;
	switch ( m_nAlignment )
	{
		case top /*TOP*/: 
			{
				boundRect.left = outRect.left + ( ((outRect.right - outRect.left) / 2) - 5);
				boundRect.top = outRect.top+5;
				boundRect.right = boundRect.left+ 9; 
				boundRect.bottom = boundRect.top+ 9;
			}
			break;
					
		case bottom /*BOTTOM*/: 
			{
				boundRect.left = outRect.left + ( ((outRect.right - outRect.left) / 2) - 5);
				boundRect.top = (/*outRect.bottom*/iBottom-5)-9;
				boundRect.right = boundRect.left+9; 
				boundRect.bottom = outRect.bottom-5 ; 
			}
			
			break ;

		case left /*LEFT*/: 
			{
				boundRect.left = outRect.left ;
				boundRect.top = outRect.top + ( ((/*outRect.bottom*/iBottom - outRect.top) / 2) - 5);
				boundRect.right = boundRect.left+9; 
				boundRect.bottom = boundRect.top+9 ; 
			}
			break ;

		case right /*RIGHT*/: 
			{
				boundRect.left = outRect.right-9 ;
				boundRect.top = outRect.top + ( ((/*outRect.bottom*/iBottom - outRect.top) / 2) - 5);
				boundRect.right = outRect.right; 
				boundRect.bottom = boundRect.top+9 ;
			}
			break ;

		case center /*CENTER*/: 
			{
				boundRect.left = outRect.left + ( ((outRect.right - outRect.left) / 2) - 5);
				boundRect.top = outRect.top + ( ((/*outRect.bottom*/iBottom - outRect.top) / 2) - 5);
				boundRect.right = boundRect.left+9; 
				boundRect.bottom = boundRect.top+9 ; 
			}
			break ;
	}

	HTHEME lhTheme = NULL;
	// QA: 28154 - We should use AfxGetMainWnd when using SECMemDC instead of pDC->GetWindow().
	if (RWIsAppThemed() && RWIsThemeActive())
		lhTheme = RWOpenThemeData (RWGetSafeHwnd(), L"TREEVIEW");

	if (lhTheme)
	{	
		HRESULT hr = S_OK;
		// Consider Cell as the TreeItem and draw the state.
		hr = RWDrawThemeBackground(lhTheme, pDC->GetSafeHdc(), TVP_TREEITEM, (m_nState == 1 ? 
         TREIS_SELECTED : TREIS_NORMAL), &outRect, 0 );				

		// Draw "+" or "-".
		int iState = (m_nState == 2) ? GLPS_CLOSED : GLPS_OPENED;
		hr = RWDrawThemeBackground(lhTheme, pDC->GetSafeHdc(), TVP_GLYPH, iState, &boundRect, 0 );	

		// Draw Brnach for "-".
		if (m_nState == 1)
		{
			int iLineBottom = (outRect.bottom) - ((outRect.bottom-outRect.top)/4);
			CRect r1 (boundRect.left+4, boundRect.bottom, boundRect.left+6, iLineBottom);			

			hr = RWDrawThemeBackground(lhTheme, pDC->GetSafeHdc(), TVP_BRANCH, 0, &r1, 0 );	

			pDC->MoveTo(boundRect.left+4, boundRect.bottom);
			pDC->LineTo(boundRect.left+4, iLineBottom/*boundRect.bottom+iLength*/);		

			CRect r2 (boundRect.left+4, iLineBottom, outRect.right, iLineBottom + 2);
			hr = RWDrawThemeBackground(lhTheme, pDC->GetSafeHdc(), TVP_BRANCH, 0, &r2, 0 );

			pDC->MoveTo(boundRect.left+4, iLineBottom);
			pDC->LineTo(outRect.right, iLineBottom);			
		}
		
		RWCloseThemeData( lhTheme );
	}
	else
	{
		//	SetOrigin(boundRect.left,boundRect.top);
		//	SetSize(9, 9);
		CPen   penSolid;
		CPen   penShaded;
		
		ASSERT(penSolid.CreatePen( PS_SOLID, 1, GetSysColor(COLOR_WINDOWTEXT) ));
		ASSERT(penShaded.CreatePen( PS_SOLID, 1, GetSysColor(COLOR_BTNSHADOW) ));
		
		COLORREF rgbBack = style.GetInteriorRef().GetColor();
		//	rgbBack = GetBkColor(pDC->GetSafeHdc());

		//	COLORREF rgbPrevBk = pDC->SetBkColor( rgbBack );

		//draw button box
		CPen *pPenOld = (CPen *)pDC->SelectObject(&penShaded);

		CBrush brush(rgbBack);
		CBrush* pBrushOld = (CBrush *)pDC->SelectObject(&brush);
		
		pDC->FillRect( outRect,&brush );
		pDC->Rectangle( boundRect );
		
		pDC->SelectObject(pBrushOld);
		pDC->SelectObject(pPenOld);

		pPenOld = pDC->SelectObject(&penSolid);

		CPoint pt = boundRect.CenterPoint();
		//	int w = boundRect.Width()/3;
		int w = 2;
		
		//put '-' sign in box
		pDC->MoveTo(pt.x - w, pt.y);
		pDC->LineTo(pt.x + w + 1, pt.y);
		
		if( m_nState == 2  ) // NoteToSelf: Change '2' to COLAPSED
		{
			//put '+' into box
			pDC->MoveTo(pt.x, (pt.y - w));
			pDC->LineTo(pt.x, pt.y + w + 1);
		}
		else 
		{
			pDC->MoveTo(boundRect.left+4, boundRect.bottom);
			//int iLength = ((CPMModel*)GetModel())->GetExpandedLength();
			int iLineBottom = (outRect.bottom) - ((outRect.bottom-outRect.top)/4);
		
			//if ( iLength >=  (/*outRect.bottom*/iBottom-boundRect.bottom) )
			//	iLength = (/*outRect.bottom*/iBottom-boundRect.bottom) - 2 ;
	
			pDC->LineTo(boundRect.left+4, iLineBottom/*boundRect.bottom+iLength*/);

			pDC->MoveTo(boundRect.left+4, iLineBottom/*boundRect.bottom+iLength*/);
			pDC->LineTo(outRect.right, iLineBottom /*boundRect.bottom+iLength*/);
		}

		pDC->SelectObject(pPenOld);

		penSolid.DeleteObject();
		penShaded.DeleteObject();
	}
}

void CGXPMControl::Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle)
{
	ASSERT(pDC != NULL && pDC->IsKindOf(RUNTIME_CLASS(CDC)));
	// ASSERTION-> Invalid Device Context ->END
	ASSERT(nRow <= Grid()->GetRowCount() && nCol <= Grid()->GetColCount());
	// ASSERTION-> Cell coordinates out of range ->END

	ASSERT_VALID(pDC);

	// Draw the decorated window

	// Erase Frame around the cell
//    DrawFrame(pDC, rect, style);

	// Font
	rect = GetCellRect(nRow, nCol, &rect, &style);

	DrawBackground(pDC, rect, style);

	pDC->SetBkMode(TRANSPARENT);
	pDC->SetBkColor(style.GetInteriorRef().GetColor());

	// Calculate the expanded size
	CGXRange rgCovered;
	ROWCOL nCovBotRow;
	if(Grid()->GetCoveredCellsRowCol(nRow, nCol, rgCovered))
		nCovBotRow = rgCovered.bottom;
	else 
		nCovBotRow = nRow;

	m_nLogicalCenter = rect.BottomRight().y - Grid()->GetRowHeight(nCovBotRow);

	CFont font;

	ASSERT(style.GetIncludeValue());
	m_nState = _ttoi(style.GetValueRef());

	DrawPMBox(pDC, rect, style);

	// Avoid overdrawing with BitmapDC in CGXGridCore::OnDraw
	// We do not want to exclude this rect when drawing with SECMemDC.
	// Usually, there will be a call to SetDrawingTechnique(gxDrawUsingMemDC)
	// in the application which causes Grid to use SECMemDC.
	// QA: 28154
	if(!pDC->IsKindOf(RUNTIME_CLASS(SECMemDC)))
	{
		ExcludeClipRect(rect);
	}

	// Unreferenced:
	pStandardStyle;
}
