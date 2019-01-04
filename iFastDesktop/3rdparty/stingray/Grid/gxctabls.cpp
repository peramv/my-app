///////////////////////////////////////////////////////////////////////////////
// gxctabls.cpp : helper classes and methods for tabbed listboxes and comboboxes
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

#include "grid\gxresrc.h"

#ifndef _GXCTRLI_H_
#include "grid\gxctrli.h"
#endif

#ifndef _GXPRIV_H_
#include "grid\gxpriv.h"
#endif

#include <ctype.h>

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXCTABLS")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

#pragma warning (disable: 4267) // size_t to int

/////////////////////////////////////////////////////////////////////////////
// CGXTabbedLBoxHeader

CGXTabbedLBoxHeader ::CGXTabbedLBoxHeader ()
{
}

CGXTabbedLBoxHeader ::~CGXTabbedLBoxHeader ()
{
}

BOOL CGXTabbedLBoxHeader ::CreateHeader(CWnd*)
{
	DWORD dwStyle = 0;
	if (!GXGetAppData()->bWin31)
		dwStyle = WS_EX_TOOLWINDOW;

	return CreateEx(
		dwStyle, GXGetAppData()->sComboClassName, NULL, WS_CHILD,
		0, 0, 0, 0,
		::GetDesktopWindow(), NULL);
}

BEGIN_MESSAGE_MAP(CGXTabbedLBoxHeader, CWnd)
	//{{AFX_MSG_MAP(CGXTabbedLBoxHeader)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGXTabbedLBoxHeader message handlers

void CGXTabbedLBoxHeader ::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	// Attributes
	CRect rect;
	GetClientRect(rect);

	COLORREF rgbBack = GXSYSCOLOR(COLOR_BTNFACE);
	COLORREF rgbText = GXSYSCOLOR(COLOR_BTNTEXT);
	CDC* pDC = &dc;

	HTHEME lhTheme = NULL;
	if (RWIsAppThemed() && RWIsThemeActive())
		lhTheme = RWOpenThemeData (RWGetSafeHwnd(), L"HEADER");

	if (lhTheme)	
	{
		RWDrawThemeBackground( lhTheme, pDC->GetSafeHdc(), HP_HEADERITEM, HIS_NORMAL, &rect, 0 );
	}
	else
	{
		// Draw back ground
		GXPatB(&dc, rect, rgbBack);
	}

	// Set DC
	pDC->SetBkColor(rgbBack);
	pDC->SetTextColor(rgbText);
	pDC->SetBkMode(TRANSPARENT);

	// Load same font as ComboBox
	CFont* pOldFont = pDC->SelectObject(m_pFont);

	// Get ptr to first column
	LPCTSTR pszEntry = m_strTitles;
	if (m_bDispAllCols && m_nDisplayCol > 0)
	{
		pszEntry = _tcschr(pszEntry, _T('\t'));
		if (pszEntry)
			pszEntry++;
	}

	// Draw each column
	CRect r = rect;

	for (int i = 0; (i == 0 || m_bDispAllCols && i <= m_iTabCount); i++)
	{
		int nLen = 0;

		// Length of column text
		LPCTSTR p = _tcschr(pszEntry, _T('\t'));
		if (p)
			nLen = (int)(p - pszEntry);
		else
			nLen = (int)_tcslen(pszEntry);

		// Rectangle
		if (m_bDispAllCols && i < m_iTabCount)
			r.right = m_piarTabStops[i]-1;
		else
			r.right = rect.right;

		if (lhTheme)
		{
			int iState = (i == m_nDisplayCol) ? HIS_HOT : HIS_NORMAL;
			RWDrawThemeBackground( lhTheme, pDC->GetSafeHdc(), HP_HEADERITEM, iState, &r, 0 );
		}
		else
		{		
			// Raised effect
			GXDrawEdge(pDC, r, BDR_RAISEDINNER, FALSE);
		}		

		// Check if I shall draw a bitmap or text
		CString str;
		HANDLE hbm = GXGetDIBState()->GetPool()->LookupOrCreateDIB(pszEntry);

		if (hbm)
		{
			// bitmap
			CRect rect = r;
			rect.top++;
			rect.left++;
			rect.right--;
			rect.bottom--;
			CGXDIB::Draw(pDC, hbm, rect, CGXDIB::none, DT_CENTER|DT_VCENTER);
		}
		else
			// text
			GXDrawTextLikeMultiLineEdit(pDC, pszEntry, nLen, r, DT_CENTER|DT_VCENTER|DT_SINGLELINE);

		// next header rect
		r.left = r.right + 1;

		// next column text
		pszEntry += nLen;
		if (*pszEntry == _T('\t'))
			pszEntry++;
	}

	// Reset DC
	pDC->SelectObject(pOldFont);
	if (lhTheme) RWCloseThemeData(lhTheme);
}

/////////////////////////////////////////////////////////////////////////////
// CGXTabbedLBoxImp  static helper functions for tabbed listboxes

void AFXAPI CGXTabbedLBoxImp::DetermineMaxColWidth(CDC* pDC, LPCTSTR pszCol, int nColCount, LPINT anMaxColWidth)
{
	for (int i = 0; pszCol && *pszCol && i < nColCount; i++)
	{
		// Determine length of column
		int nColLen;
		for (nColLen = 0; pszCol[nColLen] && pszCol[nColLen] != _T('\t'); nColLen++)
			NULL;

		// Compute size
		CSize size;
		CString str;
		HANDLE hbm = 0;
		hbm = GXGetDIBState()->GetPool()->LookupOrCreateDIB(pszCol);

		if (hbm)
		{
			CGXDIB dib;
			dib.Attach(hbm);
			size = dib.GetSize();
			dib.Detach();
		}
		else
			size = pDC->GetTextExtent(pszCol, nColLen);

		// Is it bigger?
		if (size.cx > anMaxColWidth[i])
			anMaxColWidth[i] = size.cx;

		// Skip column
		pszCol += nColLen;
		if (*pszCol == _T('\t'))
			pszCol++;
	}
}


void AFXAPI CGXTabbedLBoxImp::DrawItem(CDC* pDC,
	const CRect& rcItem,
	const CString& strLBEntry,
	BOOL bOnlyDisplayCol,
	int nDisplayCol,
	int nTabCount,
	LPINT piarTabStops,
	COLORREF rgbGridLine,
	COLORREF rgbBack,
	COLORREF rgbText,
	int nLeftMargin)
{
	// Determine first column and length of line
	LPCTSTR pszEntry = strLBEntry;
	int nLen;
	if (bOnlyDisplayCol)
	{
		// Only display first column (which is the display column)
		LPCTSTR p = _tcschr(pszEntry, _T('\t'));
		if (p)
			nLen = (int)(p - pszEntry);
		else
			nLen = strLBEntry.GetLength();
	}
	else if (nDisplayCol > 0)
	{
		pszEntry = _tcschr(pszEntry, _T('\t'));
		if (pszEntry)
			pszEntry++;
		nLen = (int)_tcslen(pszEntry);
	}
	else
		nLen = strLBEntry.GetLength();

	int iTabCount = nTabCount;

	if (bOnlyDisplayCol)
		iTabCount = 0;

	CRect recTemp = rcItem;

	// Fill background
	CBrush  brSelected;
	brSelected.CreateSolidBrush(rgbBack);
	pDC->FillRect(&recTemp, &brSelected);
	brSelected.DeleteObject();

	// Draw grid lines
	int i;
	for (i = 0; i < iTabCount; i++)
		GXPatB(pDC, recTemp.left + piarTabStops[i] - 2 + nLeftMargin, recTemp.top, 1, recTemp.Height(), rgbGridLine);

	pDC->SetBkColor(rgbBack);
	pDC->SetTextColor(rgbText);
	pDC->SetBkMode(TRANSPARENT);

	// Draw all columns
	for (i = 0; i <= iTabCount; i++)
	{
		LPCTSTR pszNext = _tcschr(pszEntry, _T('\t'));
		int l = pszNext ? pszNext-pszEntry : _tcslen(pszEntry);

		if (i < iTabCount)
			recTemp.right = piarTabStops[i];
		else
			recTemp.right = rcItem.right;

		if (recTemp.Width() > 0)
		{
			// Check if I shall draw a bitmap or text
			CString str;
			HANDLE hbm = GXGetDIBState()->GetPool()->LookupOrCreateDIB(pszEntry);

			if (hbm)
			{
				// bitmap
				CGXDIB::Draw(pDC, hbm, recTemp, CGXDIB::none, DT_VCENTER);
			}
			else
			{
				// text
				CRect rcLeftMargin(recTemp);
				rcLeftMargin.left += nLeftMargin;
				GXDrawTextLikeMultiLineEdit(pDC, pszEntry, l, rcLeftMargin, DT_SINGLELINE|DT_VCENTER);
			}
		}

		recTemp.left = piarTabStops[i];
		if (pszNext)
			pszEntry = pszNext+1;
	}
}

void AFXAPI CGXTabbedLBoxImp::MeasureHeight(const CString& strLBEntry,
	unsigned int& nItemHeight,
	BOOL bOnlyDisplayCol,
	int nDisplayCol,
	int nTabCount)
{
	// Determine first column and length of line
	LPCTSTR pszEntry = strLBEntry;
	int nLen;
	if (bOnlyDisplayCol)
	{
		// Only display first column (which is the display column)
		LPCTSTR p = _tcschr(pszEntry, _T('\t'));
		if (p)
			nLen = (int)(p - pszEntry);
		else
			nLen = strLBEntry.GetLength();
	}
	else if (nDisplayCol > 0)
	{
		pszEntry = _tcschr(pszEntry, _T('\t'));
		if (pszEntry)
			pszEntry++;
		nLen = (int)_tcslen(pszEntry);
	}
	else
		nLen = strLBEntry.GetLength();

	int iTabCount = nTabCount;

	if (bOnlyDisplayCol)
		iTabCount = 0;

	// Check all columns
	for (int i = 0; i <= iTabCount; i++)
	{
		LPCTSTR pszNext = _tcschr(pszEntry, _T('\t'));

		// Check if I shall draw a bitmap or text
		CString str;
		HANDLE hbm = GXGetDIBState()->GetPool()->LookupOrCreateDIB(pszEntry);

		if (hbm)
		{
			// bitmap
			CGXDIB dib;
			dib.Attach(hbm);
			CSize size = dib.GetSize();
			dib.Detach();
			nItemHeight = max(nItemHeight, (UINT) size.cy);
		}

		if (pszNext)
			pszEntry = pszNext+1;
		else
			break;
	}
}

