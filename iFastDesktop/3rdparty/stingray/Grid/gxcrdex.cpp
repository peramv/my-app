///////////////////////////////////////////////////////////////////////////////
// gxcrdex.cpp : implementation of the CGXRadioButtonEx control
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
// Author: Praveen Ramesh
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
#pragma code_seg("GX_SEG_GXCRADIO")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

GRID_IMPLEMENT_CONTROL(CGXRadioButtonEx, CGXControl);



/////////////////////////////////////////////////////////////////////////////
// CGXRadioButtonEx control

const int nRadioBtnSize = 12;

static void DrawRadioButton(CDC* pDC, CRect rect, BOOL bSelected, BOOL bDraw3D, CDC* pSrcDC)
{
	// center button
	rect.top += (rect.Height()-nRadioBtnSize)/2;
	rect.bottom = rect.top + nRadioBtnSize;
	rect.left += nRadioBtnSize / 4;
	rect.right = rect.left + nRadioBtnSize;

	// TRACE(_T("%d,%d,%d,%,d\n"), rect);

	HTHEME lhTheme = NULL;
	if (RWIsAppThemed() && RWIsThemeActive())
		lhTheme = RWOpenThemeData (RWGetSafeHwnd(), L"BUTTON");

	if (lhTheme)
	{	
		int iState = bSelected ? RBS_CHECKEDNORMAL : RBS_UNCHECKEDNORMAL;
		
		RWDrawThemeBackground( lhTheme, pDC->GetSafeHdc(), BP_RADIOBUTTON, iState, &rect, 0 );	
		RWCloseThemeData( lhTheme );
	}
	else
	{
		if (!bDraw3D)
		{
			// Pen
			CPen pen;
			pen.CreateStockObject(BLACK_PEN);
			CPen* pOldPen = pDC->SelectObject(&pen);

			// Brush
			CBrush brush;
			brush.CreateStockObject(WHITE_BRUSH);
			CBrush* pOldBrush = pDC->SelectObject(&brush);

			pDC->Ellipse(rect);

			pDC->SelectObject(pOldBrush);
			pDC->SelectObject(pOldPen);

			if (bSelected)
			{
				rect.top += 2;
				rect.left += 2;
				rect.bottom -= 2;
				rect.right -= 2;

				CBrush brush;
				brush.CreateStockObject(BLACK_BRUSH);
				CBrush* pOldBrush = pDC->SelectObject(&brush);

				pDC->Ellipse(rect);
				pDC->SelectObject(pOldBrush);
			}

		}
		else
		{
			const int dx = 14, dy = 13;

			// normal image version
			pDC->BitBlt(rect.left, rect.top,
				dx, dy,
				pSrcDC, bSelected ? dx : 0, dy, SRCCOPY);
		}
	}
}

int AFXAPI GXDrawRadioButtonsHorz(CDC* pDC, CRect rect, LPCTSTR pszValue, LPCTSTR pszChoices, BOOL bDraw3D, CString sTextAlign = _T("1"))
{
	ASSERT(pszValue);
	ASSERT(pszChoices);
	ASSERT_VALID(pDC);

	// text for radio buttons
	LPTSTR pszItems = new TCHAR[_tcslen(pszChoices)+1];
	// QA: 31989 - #if Secure Code Cleanup.
	_tcscpy(pszItems, pszChoices);

	// item height
	TEXTMETRIC tm;
	pDC->GetTextMetrics(&tm);

	int dyHeight = max(nRadioBtnSize, tm.tmHeight + tm.tmExternalLeading);
	int dxWidth = max(nRadioBtnSize, tm.tmMaxCharWidth);

	// Current selection
	int nCurSel = -1;
	if (pszValue && *pszValue)
		nCurSel = _ttoi(pszValue);

	// Clipping
	int nSaveDC = pDC->SaveDC();
	pDC->IntersectClipRect(rect);

	CDC memDC;
	CBitmap* pOldBitmap = NULL;

	if (bDraw3D)
	{
		// load resources from OG dll
		if (GXGetDrawState()->m_bm3dCtrl.GetSafeHandle() == NULL)
		{
			// save resource handle
			HINSTANCE hSaveResource = AfxGetResourceHandle();

			// switch it to dll
			AfxSetResourceHandle(GXGetResourceHandle());
			// ->END

			GXGetDrawState()->m_bm3dCtrl.LoadBitmap(GX_IDB_3DCTRL);

			// reset resource handle
			AfxSetResourceHandle(hSaveResource);
		}

		memDC.CreateCompatibleDC(pDC);
		pOldBitmap = memDC.SelectObject(&GXGetDrawState()->m_bm3dCtrl);
		if (pOldBitmap == NULL)
			return 0;     // destructors will clean up
	}

	// Draw each item
	int nRadio = 0;

	// QA: 31989 - #if Secure Code Cleanup.
	LPTSTR token = _tcstok(pszItems, _T("\r\n"));

	CRect rcItem = CRect(rect.left,
				rect.top,
				rect.left + dxWidth,
				rect.top + dyHeight);
	while (token != 0)
	{
		if (*token)
		{
			if( sTextAlign == _T("1") ) //text to the right
			{
				DrawRadioButton(pDC, rcItem, nRadio++ == nCurSel, bDraw3D, &memDC);

				rcItem.left += nRadioBtnSize + nRadioBtnSize/2;
				CSize sz = pDC->GetTextExtent(token, (int)_tcslen(token));
				rcItem.right = rcItem.left + sz.cx;
				pDC->DrawText(token, (int)_tcslen(token), rcItem, DT_SINGLELINE | DT_LEFT);
		
				rcItem.left = rcItem.right + 2;
				rcItem.right = rcItem.left + dxWidth;
			}
			else //text to the left
			{
				
				rcItem.left += nRadioBtnSize/4;

                CSize sz = pDC->GetTextExtent(token, (int)_tcslen(token));
				rcItem.right = rcItem.left + sz.cx;
				pDC->DrawText(token, (int)_tcslen(token), rcItem, DT_SINGLELINE | DT_LEFT);
		

				rcItem.left = rcItem.right ;
				rcItem.right = rcItem.left + nRadioBtnSize + nRadioBtnSize/2;

				DrawRadioButton(pDC, rcItem, nRadio++ == nCurSel, bDraw3D, &memDC);

				
			    rcItem.left = rcItem.right + dxWidth;
			}
		}

		// QA: 31989 - #if Secure Code Cleanup.
		token = _tcstok(NULL, _T("\r\n"));
	}

	if (bDraw3D)
	{
		if (pOldBitmap)
			memDC.SelectObject(pOldBitmap);
	}

	// clean up
	pDC->RestoreDC(nSaveDC);

	delete pszItems;

	return nRadio;
}


static int AFXAPI GXDrawRadioButtonsVert(CDC* pDC, CRect rect, LPCTSTR pszValue, LPCTSTR pszChoices, BOOL bDraw3D, CString sTextAlign = _T("1"))
{
	ASSERT(pszValue);
	ASSERT(pszChoices);
	ASSERT_VALID(pDC);

	// text for radio buttons
	LPTSTR pszItems = new TCHAR[_tcslen(pszChoices)+1];
	// QA: 31989 - #if Secure Code Cleanup.
	_tcscpy(pszItems, pszChoices);

	// item height
	TEXTMETRIC tm;
	pDC->GetTextMetrics(&tm);

	int dyHeight = max(nRadioBtnSize, tm.tmHeight + tm.tmExternalLeading);

	// Current selection
	int nCurSel = -1;
	if (pszValue && *pszValue)
		nCurSel = _ttoi(pszValue);

	// Clipping
	int nSaveDC = pDC->SaveDC();
	pDC->IntersectClipRect(rect);

	CDC memDC;
	CBitmap* pOldBitmap = NULL;

	if (bDraw3D)
	{
		// load resources from OG dll
		if (GXGetDrawState()->m_bm3dCtrl.GetSafeHandle() == NULL)
		{
			// save resource handle
			HINSTANCE hSaveResource = AfxGetResourceHandle();

			// switch it to dll
			AfxSetResourceHandle(GXGetResourceHandle());
			// ->END

			GXGetDrawState()->m_bm3dCtrl.LoadBitmap(GX_IDB_3DCTRL);

			// reset resource handle
			AfxSetResourceHandle(hSaveResource);
		}

		memDC.CreateCompatibleDC(pDC);
		pOldBitmap = memDC.SelectObject(&GXGetDrawState()->m_bm3dCtrl);
		if (pOldBitmap == NULL)
			return 0;     // destructors will clean up
	}

	// Draw each item
	int nRadio = 0;

	// QA: 31989 - #if Secure Code Cleanup.
	LPTSTR token = _tcstok(pszItems, _T("\r\n"));

	while (token != 0)
	{
		if (*token)
		{
			if( sTextAlign == _T("1") ) //text to the right
			{
				
				CRect rcItem = CRect(rect.left,
					rect.top + nRadio * dyHeight,
					rect.right,
					rect.top + (nRadio+1) * dyHeight);

				DrawRadioButton(pDC, rcItem, nRadio++ == nCurSel, bDraw3D, &memDC);

				rcItem.left += nRadioBtnSize + nRadioBtnSize/2;

				pDC->DrawText(token, (int)_tcslen(token), rcItem, DT_SINGLELINE | DT_LEFT);
			}
			else //text to the left
			{
				
				CRect rcItem = CRect(rect.left,
					rect.top + nRadio * dyHeight,
					rect.right,
					rect.top + (nRadio+1) * dyHeight);
                
                CSize sz = pDC->GetTextExtent(token, (int)_tcslen(token));
				rcItem.left += nRadioBtnSize/4;
				rcItem.right = rcItem.left + sz.cx;
				pDC->DrawText(token, (int)_tcslen(token), rcItem, DT_SINGLELINE | DT_LEFT);
		

				rcItem.left = rcItem.right ;
				rcItem.right = rcItem.left + nRadioBtnSize;//+ nRadioBtnSize/2;

				DrawRadioButton(pDC, rcItem, nRadio++ == nCurSel, bDraw3D, &memDC);

			}

		}

		// QA: 31989 - #if Secure Code Cleanup.
		token = _tcstok(NULL, _T("\r\n"));
	}

	if (bDraw3D)
	{
		if (pOldBitmap)
			memDC.SelectObject(pOldBitmap);
	}

	// clean up
	pDC->RestoreDC(nSaveDC);

	delete pszItems;

	return nRadio;
}

static int AFXAPI GXHitTestRadioButtonsVert(CDC* pDC, CRect rect, LPCTSTR pszChoices, CPoint pt)
{
	ASSERT(pszChoices);
	ASSERT_VALID(pDC);

	// text for radio buttons
	LPTSTR pszItems = new TCHAR[(int)_tcslen(pszChoices)+1];
	// QA: 31989 - #if Secure Code Cleanup.
	_tcscpy(pszItems, pszChoices);

	// item height
	TEXTMETRIC tm;
	pDC->GetTextMetrics(&tm);

	int dyHeight = max(nRadioBtnSize, tm.tmHeight + tm.tmExternalLeading);

	// check each item
	int nRadio = 0;
	BOOL bFound = FALSE;
	// QA: 31989 - #if Secure Code Cleanup.
	LPTSTR token = _tcstok(pszItems, _T("\r\n"));

	while (token != 0)
	{
		if (*token)
		{
			// Is Button.hit?
			CRect rcItem = CRect(rect.left,
				rect.top + nRadio * dyHeight,
				rect.left + nRadioBtnSize + nRadioBtnSize/2,
				rect.top + (nRadio+1) * dyHeight);

			bFound = rcItem.PtInRect(pt);
			if (bFound)
				break;

			// Is Text hit?
			rcItem.left = rect.left + nRadioBtnSize + nRadioBtnSize/2;
			rcItem.right = rect.right;

			pDC->DrawText(token, (int)_tcslen(token), rcItem, DT_SINGLELINE | DT_LEFT | DT_CALCRECT);
			bFound = rcItem.PtInRect(pt);
			if (bFound)
				break;

			nRadio++;
		}

		// QA: 31989 - #if Secure Code Cleanup.
		token = _tcstok(NULL, _T("\r\n"));
	}

	delete pszItems;

	return bFound ? nRadio : -1;
}

int AFXAPI GXHitTestRadioButtonsHorz(CDC* pDC, CRect rect, LPCTSTR pszChoices, CPoint pt, CString sTextAlign = _T("1"))
{
	ASSERT(pszChoices);
	ASSERT_VALID(pDC);

	// text for radio buttons
	LPTSTR pszItems = new TCHAR[_tcslen(pszChoices)+1];

	// QA: 31989 - #if Secure Code Cleanup.
	_tcscpy(pszItems, pszChoices);

	// item height
	TEXTMETRIC tm;
	pDC->GetTextMetrics(&tm);

	int dyHeight = max(nRadioBtnSize, tm.tmHeight + tm.tmExternalLeading);
	int dxWidth = max(nRadioBtnSize, tm.tmMaxCharWidth);

	// check each item
	int nRadio = 0;
	BOOL bFound = FALSE;

	// QA: 31989 - #if Secure Code Cleanup.
	LPTSTR token = _tcstok(pszItems, _T("\r\n"));

	CRect rcItem = CRect(rect.left,
				rect.top,
				rect.left + dxWidth,
				rect.top + dyHeight);

	while (token != 0)
	{
		if (*token)
		{
			bFound = rcItem.PtInRect(pt);
			if (bFound)
				break;
          if(sTextAlign == _T("1")) //textright
		  {
				rcItem.left += nRadioBtnSize + nRadioBtnSize/2;
				CSize sz = pDC->GetTextExtent(token, (int)_tcslen(token));
				rcItem.right = rcItem.left + sz.cx;

				bFound = rcItem.PtInRect(pt);
				if (bFound)
					break;

				rcItem.left = rcItem.right + 2;
				rcItem.right = rcItem.left + dxWidth;
		  }
		  else  //textleft
		  {
             	rcItem.left += 2;

                CSize sz = pDC->GetTextExtent(token, (int)_tcslen(token));
				rcItem.right = rcItem.left + sz.cx +  nRadioBtnSize + nRadioBtnSize/2;
			
                bFound = rcItem.PtInRect(pt);
				if (bFound)
					break;
		
			    rcItem.left = rcItem.right + dxWidth;

		  }
			nRadio++;
		}

		// QA: 31989 - #if Secure Code Cleanup.
		token = _tcstok(NULL, _T("\r\n"));
	}

	delete pszItems;

	return bFound ? nRadio : -1;
}

CGXRadioButtonEx::CGXRadioButtonEx(CGXGridCore* pGrid, BOOL bDraw3d)
	: CGXControl(pGrid)
{
	m_bDraw3d = bDraw3d;
	m_bActive = FALSE;
	m_bModified = FALSE;
}

void CGXRadioButtonEx::Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style_static, const CGXStyle* pStandardStyle)
{
	CGXStyle& style = const_cast <CGXStyle&>(style_static);

	if(nRow == m_nRow && nCol == m_nCol && IsActive())
	{
		style = *m_pStyle;
	}

	// Select font
	CFont* pOldFont = LoadFont(pDC, style, pStandardStyle);

	// Cell-Color
	COLORREF rgbText = style.GetTextColor();
	COLORREF rgbCell = style.GetInteriorRef().GetColor();

	if (Grid()->GetParam()->GetProperties()->GetBlackWhite())
	{
		rgbText = RGB(0,0,0);
		rgbCell = RGB(255,255,255);
	}

	DrawBackground(pDC, rect, style);

	// Erase Background
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetBkColor(rgbCell);
	pDC->SetTextColor(rgbText);

	LPCTSTR pszValue = _T("");
	LPCTSTR pszChoices = _T("");

	if (style.GetIncludeValue())
		pszValue = style.GetValueRef();

	if (style.GetIncludeChoiceList())
		pszChoices = style.GetChoiceListRef();

	CString sAlign;
	style.GetUserAttribute(GX_IDS_UA_RADIOBUTTON_ALIGN, sAlign);

	CString sTextAlign; // "0" is left "1" is right
    style.GetUserAttribute(GX_IDS_UA_RADIOBUTTONTEXTALIGN, sTextAlign);


	if(sAlign == _T("1"))	// "0" for vertical "1" for horizontal
		m_nRadioBtns = GXDrawRadioButtonsHorz(pDC, rect, pszValue, pszChoices, m_bDraw3d, sTextAlign);
	else
		m_nRadioBtns = GXDrawRadioButtonsVert(pDC, rect, pszValue, pszChoices, m_bDraw3d, sTextAlign);

	CGXControl::Draw(pDC, rect, nRow, nCol, style, pStandardStyle);

	if (pOldFont)
		pDC->SelectObject(pOldFont);
}

// const int nRadioBtnSize = 12;

CSize CGXRadioButtonEx::CalcSize(CDC* pDC, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle, BOOL bVert)
{
	// Select font
	CFont* pOldFont = LoadFont(pDC, style, pStandardStyle);

	LPCTSTR pszChoices = _T("");

	if (style.GetIncludeChoiceList())
		pszChoices = style.GetChoiceListRef();

	// text for radio buttons
	LPTSTR pszItems = new TCHAR[_tcslen(pszChoices)+1];

	// QA: 31989 - #if Secure Code Cleanup.
	_tcscpy(pszItems, pszChoices);

	// item height
	TEXTMETRIC tm;
	pDC->GetTextMetrics(&tm);

	int dyHeight = max(nRadioBtnSize, tm.tmHeight + tm.tmExternalLeading);
	
	int dxWidth = max(nRadioBtnSize, tm.tmMaxCharWidth);

	
	CRect rect;

	// check each item
	int nxWidth = dxWidth, nyHeight = 0;
	int nxWidth1 = 0;

	CString sAlign;
	style.GetUserAttribute(GX_IDS_UA_RADIOBUTTON_ALIGN, sAlign);

	CString sTextAlign; // "0" is left "1" is right
    style.GetUserAttribute(GX_IDS_UA_RADIOBUTTONTEXTALIGN, sTextAlign);


	// QA: 31989 - #if Secure Code Cleanup.
	LPTSTR token = _tcstok(pszItems, _T("\r\n"));

	while (token != 0)
	{
		if (*token)
		{
			nxWidth1 += nRadioBtnSize + nRadioBtnSize/2;
			CSize size = pDC->GetTextExtent(token, (int)_tcslen(token));
			nxWidth1 += size.cx ;
			nxWidth1 += ( sTextAlign == _T("1") ) ? 2 : dxWidth +  nRadioBtnSize/4;

			if( sAlign == _T("1") ) //horz
			{
				nxWidth = bVert ? max(nxWidth, nxWidth1) : nxWidth1;
				nyHeight = dyHeight;
			}
			else //vert
			{
                if( bVert )
				{
 				   nyHeight += dyHeight;
				}
				else
				{
                   nyHeight = dyHeight;
				}
                nxWidth = max(nxWidth, nxWidth1);
				nxWidth1 = 0;
			}
		}

		// QA: 31989 - #if Secure Code Cleanup.
		token = _tcstok(NULL, _T("\r\n"));

		if(token==0 && sTextAlign == _T("0"))
           nxWidth -= (nRadioBtnSize/2 + dxWidth - 2);
	}

	delete pszItems;

	if (pOldFont)
		pDC->SelectObject(pOldFont);

	// unused parameters:
	nRow, nCol;

	return AddBorders(CSize(nxWidth + 4, nyHeight + 4), style);
}

BOOL CGXRadioButtonEx::LButtonDown(UINT nFlags, CPoint pt, UINT nHitState)
{
	return CGXControl::LButtonDown(nFlags, pt, nHitState);
}

BOOL CGXRadioButtonEx::LButtonUp(UINT nFlags, CPoint pt, UINT nHitState)
{
	nHitState, pt, nFlags;

	if (nHitState & GX_HITINCELL)
	{
		int nOldValue = -1;
		LPCTSTR pszChoices = _T("");

		CGXStyle& style = *m_pStyle;	
		if(IsActive())
			style = *m_pStyle;
		else
			style = const_cast <CGXStyle&> (Grid()->LookupStyleRowCol(m_nRow, m_nCol));

		if (IsReadOnly())
			return FALSE;

		if (style.GetIncludeChoiceList())
			pszChoices = style.GetChoiceListRef();

		if (style.GetIncludeValue() && _tcslen(style.GetValueRef()) > 0)
			nOldValue = _ttoi(style.GetValueRef());

		CClientDC dc(GridWnd());

		// Select font
		CFont* pOldFont = LoadFont(&dc, style, NULL);

		// adjust the hit for possible covered cell being partially hidden
		if( m_nRow < Grid()->GetTopRow() && !Grid()->IsFrozenRow(m_nRow) ) 
		{
			pt.y += Grid()->CalcSumOfRowHeights(m_nRow, Grid()->GetTopRow() - 1);
		}

		if( m_nCol < Grid()->GetLeftCol() )
		{
			pt.x += Grid()->CalcSumOfColWidths(m_nCol, Grid()->GetLeftCol() - 1);
		}
		
		Grid()->SetScrollLockedFromCell(TRUE);

		CString sAlign;
		style.GetUserAttribute(GX_IDS_UA_RADIOBUTTON_ALIGN, sAlign);
		int nValue;
		if(sAlign == _T("1"))	// "0" for vertical, "1" for horizontal
		{
		    style.GetUserAttribute(GX_IDS_UA_RADIOBUTTONTEXTALIGN, sAlign);  // "0" is textleft "1" is textright
			nValue = GXHitTestRadioButtonsHorz(&dc, GetCellRect(m_nRow, m_nCol), pszChoices, pt, sAlign);
		}
		else
			nValue = GXHitTestRadioButtonsVert(&dc, GetCellRect(m_nRow, m_nCol), pszChoices, pt);

		if (nValue != -1)
		{
			if(!IsActive())
			{
				if(OnStartEditing())
					SetActive(TRUE);
			}
			if(IsActive() && nValue != nOldValue)
			{
				TCHAR szValue[10];
				wsprintf(szValue, _T("%d"), nValue);
			//	Grid()->SetValueRange(CGXRange(m_nRow, m_nCol), szValue, gxOverride);
				m_pStyle->SetValue(szValue);
				Grid()->RedrawRowCol(m_nRow, m_nCol);
				SetModify(TRUE);
				OnModifyCell();
			}
		}

		if (pOldFont)
			dc.SelectObject(pOldFont);

		if (nValue != -1)
			OnClickedButton(NULL);
	}

	CGXControl::LButtonUp(nFlags, pt, nHitState);

	return TRUE;
}

BOOL CGXRadioButtonEx::KeyPressed(UINT nMessage, UINT nChar, UINT nRepCnt, UINT flags)
{
	BOOL bRet = CGXControl::KeyPressed(nMessage, nChar, nRepCnt, flags);

	if (!bRet && nMessage == WM_CHAR && nChar == 32)
	{

		if(!IsActive())
		{
			if (!OnStartEditing())
				return FALSE;
			SetActive(TRUE);
		}
		CGXStyle& style = *m_pStyle;

		if (IsReadOnly())
			return FALSE;

		int nOldValue = -1;
		if (style.GetIncludeValue() && _tcslen(style.GetValueRef()) > 0)
			nOldValue = _ttoi(style.GetValueRef());

		int nNewValue = nOldValue+1;
		if (nNewValue >= m_nRadioBtns)
			nNewValue = 0;

		TCHAR szValue[10];
		wsprintf(szValue, _T("%d"), nNewValue);
//		Grid()->SetValueRange(CGXRange(m_nRow, m_nCol), szValue, gxOverride);
		m_pStyle->SetValue(szValue);
		Grid()->RedrawRowCol(m_nRow, m_nCol);
		SetModify(TRUE);
		OnModifyCell();

		return TRUE;
	}
	// Process Delete Key when active...
	else if(!bRet && nMessage == WM_KEYDOWN && nChar == 46 && IsActive())
	{
		m_pStyle->SetValue(_T(""));
		Grid()->RedrawRowCol(m_nRow, m_nCol);
		SetModify(TRUE);
		OnModifyCell();
	}
	return bRet;
}

void CGXRadioButtonEx::Init(ROWCOL nRow, ROWCOL nCol)
{
	// Stores the cell coordinates, resets the style and sets the window text
	CGXControl::Init(nRow, nCol);

	NeedStyle();

	SetModify(FALSE);
}

void CGXRadioButtonEx::SetActive(BOOL bActive)
{
	if(!m_bActive && bActive)
	{
		// Force a call to GetStyleRowCol() because
		// GetStyleRowCol() might set style attributes
		// depending on the IsActive() flag
		FreeStyle();
		NeedStyle();
	}
	m_bActive = bActive;
}

BOOL CGXRadioButtonEx::IsActive()
{
	return m_bActive;
}

BOOL CGXRadioButtonEx::GetModify()
{
	return m_bModified;
}

void CGXRadioButtonEx::SetModify(BOOL bModified)
{
	m_bModified = bModified;
}

BOOL CGXRadioButtonEx::Store()
{
	// Calls SetStyleRange() and resets the modify flag
	ASSERT(m_pStyle);

	CString sValue;
	if (m_pStyle && GetModify())
	{
		sValue = m_pStyle->GetValue();
		SetActive(FALSE);
		FreeStyle();

		return Grid()->SetValueRange(
			CGXRange(m_nRow,  m_nCol),
			sValue,
			gxOverride,
			0,
			GX_INVALIDATE);
			// Cell will be automatically redrawn inactive
	}

	return TRUE;
}

void AFXAPI CGXRadioButtonEx::AddUserAttributes(CGXStylesMap* pStylesMap)
{
	// Radio button alignment specification
	pStylesMap->AddUserAttribute(GX_IDS_UA_RADIOBUTTON_ALIGN,
		CGXStyle()
		.SetControl(GX_IDS_CTRL_ZEROBASED_EX)
		.SetChoiceList(_T("Vertical\nHorizontal"))
		);

	//cb Radio button text position
	pStylesMap->AddUserAttribute(GX_IDS_UA_RADIOBUTTONTEXTALIGN,
		CGXStyle()
		.SetControl(GX_IDS_CTRL_ZEROBASED_EX)
		.SetChoiceList(_T("Left\nRight"))
		);
}

BOOL CGXRadioButtonEx::IsWindowlessControl()
{
	return TRUE;
}
