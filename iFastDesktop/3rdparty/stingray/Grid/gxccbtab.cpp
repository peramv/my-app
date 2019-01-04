///////////////////////////////////////////////////////////////////////////////
// gxccbtab.cpp : implementation of CGXTabbedComboBox control
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
// Multi-monitor support
#include <multimon.h>

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

#ifndef _GXMSG_H_
#include "grid\gxmsg.h"
#endif

#include <ctype.h>

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXCCBTAB")
#endif

GRID_IMPLEMENT_CONTROL(CGXTabbedComboBox, CGXComboBox);
IMPLEMENT_DYNAMIC(CGXTabbedComboBox, CGXComboBox);

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif


// Global methods

/////////////////////////////////////////////////////////////////////////////
// CGXTabbedComboBox

CGXTabbedComboBox::CGXTabbedComboBox(CGXGridCore* pGrid, UINT nEditID, UINT nListBoxID)
	: CGXComboBox(pGrid, nEditID, nListBoxID, GXCOMBO_NOTEXTFIT)
{
	m_nValueCol = 0;
	m_nDisplayCol = 0;
	m_bDispAllCols = TRUE; // no table-like dropdown list
	m_bSizeToContent = FALSE;

	m_nWidthLBox = 0;
	m_iTabCount = 0;
	m_piarTabStops = NULL;
	m_bDisplayTitleRow = TRUE;
	m_nSortCol = -1; // no sorting

	m_bCheckAndFillCBEdit = TRUE;

	m_rgbGridLine = RGB(192,192,192);
	m_pComboLbox = NULL;
	m_pComboLboxPopup = NULL;
	m_nDefaultHeight = 10;
	m_pWndTitleRow = new CGXTabbedLBoxHeader();
	m_bListBoxFilled = FALSE;
    m_nLeftMargin = 0;
	m_nCurFillChoicelistId = 0;
	
	m_nSerial = -1;
}

CGXTabbedComboBox::~CGXTabbedComboBox()
{
	delete m_piarTabStops;

	if (m_pWndTitleRow && m_pWndTitleRow->GetSafeHwnd())
		m_pWndTitleRow->DestroyWindow();
	delete m_pWndTitleRow;

	if (m_pComboLboxPopup && m_pComboLboxPopup->GetSafeHwnd() )
		m_pComboLboxPopup->DestroyWindow();
	delete m_pComboLboxPopup;
	m_pComboLboxPopup = NULL;
	m_pDropDownWnd = NULL;
}

void AFXAPI CGXTabbedComboBox::AddUserAttributes(CGXStylesMap* pStylesMap)
{
	pStylesMap->AddUserAttribute(GX_IDS_UA_TABLIST_KEYCOL);
	
	pStylesMap->AddUserAttribute(GX_IDS_UA_TABLIST_TEXTCOL);

	pStylesMap->AddUserAttribute(GX_IDS_UA_TABLIST_SHOWALLCOLS,
		CGXStyle().SetControl(GX_IDS_CTRL_CHECKBOX3D)
			  .SetVerticalAlignment(DT_VCENTER)
			  .SetHorizontalAlignment(DT_CENTER));
	
	pStylesMap->AddUserAttribute(GX_IDS_UA_TABLIST_TITLEROW,
		CGXStyle().SetControl(GX_IDS_CTRL_CHECKBOX3D)
			  .SetVerticalAlignment(DT_VCENTER)
			  .SetHorizontalAlignment(DT_CENTER));

	pStylesMap->AddUserAttribute(GX_IDS_UA_TABLIST_SORTCOL);
	
	pStylesMap->AddUserAttribute(GX_IDS_UA_TABLIST_CHOICELISTID);
}

BEGIN_MESSAGE_MAP(CGXTabbedComboBox, CGXComboBox)
	//{{AFX_MSG_MAP(CGXTabbedComboBox)
	ON_WM_CHAR()
	ON_MESSAGE(WM_GX_LBOXEND, OnListBoxEnd)	
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGXDropDownList message handlers

// Operations
void CGXTabbedComboBox::Init(ROWCOL nRow, ROWCOL nCol)
{
	CGXComboBox::Init(nRow, nCol);

	// User attributes
	m_nValueCol = _ttoi(m_pStyle->GetUserAttribute(GX_IDS_UA_TABLIST_KEYCOL));
	m_nDisplayCol = _ttoi(m_pStyle->GetUserAttribute(GX_IDS_UA_TABLIST_TEXTCOL));
	m_bDispAllCols = TRUE;
	if (m_pStyle->GetIncludeUserAttribute(GX_IDS_UA_TABLIST_SHOWALLCOLS))
		m_bDispAllCols = _ttoi(m_pStyle->GetUserAttribute(GX_IDS_UA_TABLIST_SHOWALLCOLS));
	m_bDisplayTitleRow = _ttoi(m_pStyle->GetUserAttribute(GX_IDS_UA_TABLIST_TITLEROW));
	m_strColWidths = m_pStyle->GetUserAttribute(GX_IDS_UA_TABLIST_COLWIDTHS);
	m_nSortCol = -1; // no sorting
	if (m_pStyle->GetIncludeUserAttribute(GX_IDS_UA_TABLIST_SORTCOL))
		m_nSortCol = _ttoi(m_pStyle->GetUserAttribute(GX_IDS_UA_TABLIST_SORTCOL));

	// set current selection
	SetValue(m_pStyle->GetValueRef());
	SetModify(FALSE);
	m_bListBoxFilled = FALSE;

	if (Grid()->GetParam()->GetActivateCellFlags() & GX_CAFOCUS_SETCURRENT && OnStartEditing())
		SetActive(TRUE);

	SetReadOnly(Grid()->IsReadOnly() || m_pStyle->GetIncludeReadOnly() && m_pStyle->GetReadOnly());

	// Force drawing of buttons for current cell
	if (!IsActive() && m_pButton)
		GridWnd()->InvalidateRect(m_pButton->GetRect());
}

BOOL CGXTabbedComboBox::StoreStyle(ROWCOL nRow, ROWCOL nCol, const CGXStyle* pStyle, GXModifyType mt, int nType, const CGXStyle* pOldStyle)
{
	ASSERT(pStyle || mt == gxRemove);
	ASSERT(pOldStyle);

	// We are only interested to interere changes in current cell
	if (!CGXControl::StoreStyle(nRow, nCol, pStyle, mt, nType, pOldStyle))
		return FALSE;

	if ((mt == gxOverride || mt == gxApplyNew)
		&& Grid()->IsCurrentCell(nRow, nCol))
	{
		if (pStyle->GetIncludeChoiceList() 
			|| pStyle->GetIncludeUserAttribute(GX_IDS_UA_TABLIST_CHOICELISTID)
			|| pStyle->GetIncludeUserAttribute(GX_IDS_UA_TABLIST_KEYCOL)
			|| pStyle->GetIncludeUserAttribute(GX_IDS_UA_TABLIST_TEXTCOL)
			|| pStyle->GetIncludeUserAttribute(GX_IDS_UA_TABLIST_SHOWALLCOLS)
			|| pStyle->GetIncludeUserAttribute(GX_IDS_UA_TABLIST_SHOWALLCOLS)
			|| pStyle->GetIncludeUserAttribute(GX_IDS_UA_TABLIST_TITLEROW)
			|| pStyle->GetIncludeUserAttribute(GX_IDS_UA_TABLIST_COLWIDTHS)
			|| pStyle->GetIncludeUserAttribute(GX_IDS_UA_TABLIST_SORTCOL))
		{
			int nChoiceListId = _ttoi(pStyle->GetUserAttribute(GX_IDS_UA_TABLIST_CHOICELISTID));

			if (nChoiceListId == 0 && m_pStyle)
				nChoiceListId = _ttoi(m_pStyle->GetUserAttribute(GX_IDS_UA_TABLIST_CHOICELISTID));

			ResetChoiceMap(Grid()->GetParam(), nChoiceListId);

			Reset();  // CGXGridCore::OnDrawItem will call Init again
		}
		else if (pStyle->GetIncludeValue() && !GetModify() || pStyle->GetIncludeControl())
			Reset();  // CGXGridCore::OnDrawItem will call Init again
	}

	return TRUE;
}

void CGXTabbedComboBox::Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle)
{
	ASSERT(pDC != NULL && pDC->IsKindOf(RUNTIME_CLASS(CDC)));
	// ASSERTION-> Invalid Device Context ->END
	ASSERT(nRow <= Grid()->GetRowCount() && nCol <= Grid()->GetColCount());
	// ASSERTION-> Cell coordinates out of range ->END

	ASSERT_VALID(pDC);

	CString str;
	HANDLE hbm = 0;
	if (GetControlText(str, nRow, nCol, NULL, style))
		hbm = GXGetDIBState()->GetPool()->LookupOrCreateDIB(str);

	if (nRow == m_nRow && nCol == m_nCol && !Grid()->IsPrinting())
	{
		// Cell-Color
		m_rgbBackColor = style.GetInteriorRef().GetColor();
		m_rgbTextColor = style.GetTextColor();
	}

	if (nRow == m_nRow && nCol == m_nCol && IsActive() && !Grid()->IsPrinting())
	{
		if(hbm)
			DrawBitmap(pDC, rect, nRow, nCol, style, pStandardStyle, hbm);
		else
		{
			CFont* pOldFont = LoadFont(pDC, style, pStandardStyle);

			TEXTMETRIC tm;
			pDC->GetTextMetrics(&tm);
			m_nDefaultHeight = tm.tmHeight; // ShowDropDown will use m_nDefaultHeight

			if (pOldFont)
				pDC->SelectObject(pOldFont);

			CGXComboBox::Draw(pDC, rect, nRow, nCol, style, pStandardStyle);
		}
	}

	else
	//     lookup style and draw static:
	//     - edit control with GXDrawTextLikeMultiLineEdit
	// }
	{
		// ------------------ Static Text ---------------------------
		
		if (hbm)
			DrawBitmap(pDC, rect, nRow, nCol, style, pStandardStyle, hbm);
		else
			CGXComboBox::Draw(pDC, rect, nRow, nCol, style, pStandardStyle);
	}
}
void CGXTabbedComboBox::DrawBitmap(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle, HANDLE hbm)
{
	DrawBackground(pDC, rect, style);
	CRect r = GetCellRect(nRow, nCol, rect, &style);
	CGXDIB::Draw(pDC, hbm, r, CGXDIB::none, (UINT) (style.GetHorizontalAlignment()|style.GetVerticalAlignment()));

	// child Controls: spin-buttons, hotspot, combobox btn, ...
	CGXControl::Draw(pDC, rect, nRow, nCol, style, pStandardStyle);
}
LRESULT CGXTabbedComboBox::OnListBoxEnd(WPARAM wParam, LPARAM lParam)
{
	CGXComboBox::OnListBoxEnd(wParam, lParam);
	Store();
	return 0;
}
// SetTabStops
//

void CGXTabbedComboBox::SetTabStops(int iTabStops)
{
	delete m_piarTabStops;
	m_iTabCount = iTabStops;
	m_piarTabStops = new int[iTabStops];
}

// AddTabStop
//

void CGXTabbedComboBox::AddTabStop(int iIndex, int iTabStop)
{
	m_piarTabStops[iIndex] = iTabStop;
}

CMapStringToString* CGXTabbedComboBox::GetValueToChoiceMap(const CGXStyle& style)
{
	int nChoiceListId = _ttoi(style.GetUserAttribute(GX_IDS_UA_TABLIST_CHOICELISTID));

	if (nChoiceListId <= 0)
		return NULL;

	CMapStringToString* pMap = NULL;

	if (nChoiceListId < Grid()->GetParam()->m_ArrayOfMapValueToChoice.GetSize())
		pMap = (CMapStringToString*) Grid()->GetParam()->m_ArrayOfMapValueToChoice[nChoiceListId];

	if (pMap == NULL)
	{
		int nValueCol = _ttoi(style.GetUserAttribute(GX_IDS_UA_TABLIST_KEYCOL));
		// int nDisplayCol = _ttoi(style.GetUserAttribute(GX_IDS_UA_TABLIST_TEXTCOL));
		int bDisplayTitleRow = _ttoi(style.GetUserAttribute(GX_IDS_UA_TABLIST_TITLEROW));

		// allocate and fill map with choice list
		Grid()->GetParam()->m_ArrayOfMapValueToChoice.SetAtGrow(nChoiceListId, pMap = new CMapStringToString);
		pMap->InitHashTable(257);

		int nEntry = 0;

		// search for string in choice list
		CString s = style.GetChoiceListRef();
		int n = 0;
		TCHAR szValue[128];

		CString sItem;
		if (bDisplayTitleRow)
			n = GXGetNextLine(s, sItem);

		while (!s.IsEmpty() && n != -1)
		{
			n = GXGetNextLine(s, sItem);

			GXGetColString(sItem, nValueCol, szValue, 127);

			pMap->SetAt(szValue, sItem);

			nEntry++;
		}
	}

	return pMap;
}
		
void AFXAPI CGXTabbedComboBox::ResetChoiceMap(CGXGridParam* pParam, int nChoiceListId)
{
	if (nChoiceListId == -1)
	{
		int i; 
		for (i = 0; i < pParam->m_ArrayOfMapValueToChoice.GetSize(); i++)
		{
			CMapStringToString* p = (CMapStringToString*) pParam->m_ArrayOfMapValueToChoice[i];
			delete p;
		}

		for (i = 0; i < pParam->m_ArrayOfMapTextToChoice.GetSize(); i++)
		{
			CMapStringToString* p = (CMapStringToString*) pParam->m_ArrayOfMapTextToChoice[i];
			delete p;
		}
		pParam->m_ArrayOfMapValueToChoice.RemoveAll();
		pParam->m_ArrayOfMapTextToChoice.RemoveAll();
	}
	else
	{
		if (nChoiceListId <= 0)
			return;

		if (nChoiceListId < pParam->m_ArrayOfMapValueToChoice.GetSize())
		{
			CMapStringToString* p = (CMapStringToString*) pParam->m_ArrayOfMapValueToChoice[nChoiceListId];
			delete p;
			pParam->m_ArrayOfMapValueToChoice[nChoiceListId] = NULL;
		}

		if (nChoiceListId < pParam->m_ArrayOfMapTextToChoice.GetSize())
		{
			CMapStringToString* p = (CMapStringToString*) pParam->m_ArrayOfMapTextToChoice[nChoiceListId];
			delete p;
			pParam->m_ArrayOfMapTextToChoice[nChoiceListId] = NULL;
		}
	}

	// OnFillDroppedList will check this
	pParam->m_nSerial++;
}

CMapStringToString* CGXTabbedComboBox::GetTextToChoiceMap(const CGXStyle& style)
{
	int nChoiceListId = _ttoi(style.GetUserAttribute(GX_IDS_UA_TABLIST_CHOICELISTID));

	if (nChoiceListId <= 0)
		return NULL;

	CMapStringToString* pMap = NULL;

	if (nChoiceListId < Grid()->GetParam()->m_ArrayOfMapTextToChoice.GetSize())
		pMap = (CMapStringToString*) Grid()->GetParam()->m_ArrayOfMapTextToChoice[nChoiceListId];

	if (pMap == NULL)
	{
		// int nValueCol = _ttoi(style.GetUserAttribute(GX_IDS_UA_TABLIST_KEYCOL));
		int nDisplayCol = _ttoi(style.GetUserAttribute(GX_IDS_UA_TABLIST_TEXTCOL));
		int bDisplayTitleRow = _ttoi(style.GetUserAttribute(GX_IDS_UA_TABLIST_TITLEROW));

		// allocate and fill map with choice list
		Grid()->GetParam()->m_ArrayOfMapTextToChoice.SetAtGrow(nChoiceListId, pMap = new CMapStringToString);

		int nEntry = 0;

		// search for string in choice list
		CString s = style.GetChoiceListRef();
		int n = 0;
		TCHAR szValue[128];

		CString sItem;
		if (bDisplayTitleRow)
			n = GXGetNextLine(s, sItem);

		while (!s.IsEmpty() && n != -1)
		{
			n = GXGetNextLine(s, sItem);

			GXGetColString(sItem, nDisplayCol, szValue, 127);

			pMap->SetAt(szValue, sItem);

			nEntry++;
		}
	}

	return pMap;
}
		
// Value
//


void CGXTabbedComboBox::SetValue(LPCTSTR pszRawValue)
{
	// get pointer to map or allocate on demand
	NeedStyle();

	CMapStringToString* pMap = GetValueToChoiceMap(*m_pStyle);

	if (pMap != NULL)
	{
		CString sItem;
		// search for value in map
		if (pMap->Lookup(pszRawValue, sItem))
		{
			TCHAR szValue[128];

			// Get display string
			GXGetColString(sItem, m_nDisplayCol, szValue, 127);
			SetWindowText(szValue);
			SetSel(0, -1);   // Select all

			if (m_bListBoxFilled)
				m_pComboLbox->SetCurSel(m_pComboLbox->FindStringExact(-1, szValue));
		}
		else
		{
			SetWindowText(_T(""));
		}
	}
	else
	{
		ASSERT(m_bFillWithChoiceList);
		// Don't call this function if m_bFillWithChoiceList is FALSE

		// Search for the key in the choice list and
		// set display string
		int nFound = -1;

		CString s = m_pStyle->GetChoiceListRef();
		if (m_bListBoxFilled && m_nSortCol >= 0)
			GXSortChoiceList(s, m_nSortCol, m_bDisplayTitleRow);

		CString sItem;
		nFound = GXFindChoiceListItem(pszRawValue, m_nValueCol, s, m_bDisplayTitleRow, sItem);

		if (nFound != -1)
		{
			TCHAR szValue[128];

			// Get display string
			GXGetColString(sItem, m_nDisplayCol, szValue, 127);
			SetWindowText(szValue);
			SetSel(0, -1);   // Select all

			if (m_bListBoxFilled)
				m_pComboLbox->SetCurSel(nFound);
		}

		if (nFound == -1)
			SetWindowText(_T(""));
	}
}

BOOL CGXTabbedComboBox::GetValue(CString& sResult)
{
	ASSERT(m_bFillWithChoiceList);
	// Don't call this function if m_bFillWithChoiceList is FALSE

	if (!IsInit())
		return FALSE;

	NeedStyle();

	// get pointer to map or allocate on demand
	CMapStringToString* pMap = GetTextToChoiceMap(*m_pStyle);
	if (pMap != NULL)
	{
		CString strText;
		GetWindowText(strText);

		if (strText.IsEmpty())
		{
			sResult.Empty();
			return TRUE;
		}

		// search text in map
		CString sItem;
		if (pMap->Lookup(strText, sItem))
		{
			TCHAR szValue[128];

			// Get display string
			GXGetColString(sItem, m_nValueCol, szValue, 127);
			sResult = szValue;
			return TRUE;
		}

		return FALSE;
	}
	else
	{
		CString strText;
		GetWindowText(strText);

		if (strText.IsEmpty())
		{
			sResult.Empty();
			return TRUE;
		}

		// search text in ChoiceList
		CString sItem;
		if (GXFindChoiceListItem(strText, m_nDisplayCol, m_pStyle->GetChoiceListRef(), m_bDisplayTitleRow, sItem) != -1)
		{
			// Get value
			TCHAR szValue[128];
			GXGetColString(sItem, m_nValueCol, szValue, 127);

			sResult = szValue;
			return TRUE;
		}

		return FALSE;
	}
}

BOOL CGXTabbedComboBox::GetControlText(CString& strResult, ROWCOL , ROWCOL , LPCTSTR pszRawValue, const CGXStyle& style)
{
	// get pointer to map or allocate on demand
	CMapStringToString* pMap = GetValueToChoiceMap(style);
	
	if (pMap != NULL)
	{
		// User attributes
		// int nValueCol = _ttoi(style.GetUserAttribute(GX_IDS_UA_TABLIST_KEYCOL));
		int nDisplayCol = _ttoi(style.GetUserAttribute(GX_IDS_UA_TABLIST_TEXTCOL));
		// int bDisplayTitleRow = _ttoi(style.GetUserAttribute(GX_IDS_UA_TABLIST_TITLEROW));

		if (pszRawValue == NULL)
			pszRawValue = style.GetValueRef();

		CString sItem;

		// search for value in map
		if (pMap->Lookup(pszRawValue, sItem))
		{
			TCHAR szValue[128];

			// return display string
			GXGetColString(sItem, nDisplayCol, szValue, 127);
			strResult = szValue;
			return TRUE;
		}
		else
		{
			sItem.Empty();
			return FALSE;
		}
	}

	// no id found - standard processing will loop thorugh choicelist with GXFindChoiceListItem
	ASSERT(m_bFillWithChoiceList);
	// Don't call this function if m_bFillWithChoiceList is FALSE

	// User attributes
	int nValueCol = _ttoi(style.GetUserAttribute(GX_IDS_UA_TABLIST_KEYCOL));
	int nDisplayCol = _ttoi(style.GetUserAttribute(GX_IDS_UA_TABLIST_TEXTCOL));
	int bDisplayTitleRow = _ttoi(style.GetUserAttribute(GX_IDS_UA_TABLIST_TITLEROW));

	if (pszRawValue == NULL)
		pszRawValue = style.GetValueRef();

	// search for value in choice list

	CString sItem;
	if (GXFindChoiceListItem(pszRawValue, nValueCol, style.GetChoiceListRef(), bDisplayTitleRow, sItem) != -1)
	{
		TCHAR szValue[128];

		// return display string
		GXGetColString(sItem, nDisplayCol, szValue, 127);
		strResult = szValue;
		return TRUE;
	}

	return FALSE;
}

BOOL CGXTabbedComboBox::ConvertControlTextToValue(CString& str, ROWCOL nRow, ROWCOL nCol, const CGXStyle* pOldStyle)
{
	ASSERT(m_bFillWithChoiceList);
	// Don't call this function if m_bFillWithChoiceList is FALSE

	CGXStyle* pStyle = NULL;
	BOOL bSuccess = FALSE;

	if (pOldStyle == NULL)
	{
		pStyle = Grid()->CreateStyle();
		Grid()->ComposeStyleRowCol(nRow, nCol, pStyle);
		pOldStyle = pStyle;
	}

	// find display string
	if (str.IsEmpty())
		bSuccess = TRUE; 
	else
	{
		// User attributes
		int nValueCol = _ttoi(pOldStyle->GetUserAttribute(GX_IDS_UA_TABLIST_KEYCOL));
		int nDisplayCol = _ttoi(pOldStyle->GetUserAttribute(GX_IDS_UA_TABLIST_TEXTCOL));
		BOOL bDisplayTitleRow = _ttoi(pOldStyle->GetUserAttribute(GX_IDS_UA_TABLIST_TITLEROW));

		// get pointer to map or allocate on demand
		CMapStringToString* pMap = GetTextToChoiceMap(*pOldStyle);
		if (pMap == NULL)
		{
			// original CGXTabbedComboBox code
			if (pOldStyle && pOldStyle->GetIncludeChoiceList())
			{
				CString sItem;
				if (GXFindChoiceListItem(str, nDisplayCol, pOldStyle->GetChoiceListRef(), bDisplayTitleRow, sItem) != -1)
				{
					TCHAR szValue[128];

					// get value
					GXGetColString(sItem, nValueCol, szValue, 127);

					// store key value
					str = szValue;
					bSuccess = TRUE;
				}
			}
		}
		else
		{
			// lookup in map
			CString sItem;
			if (pMap->Lookup(str, sItem))
			{
				TCHAR szValue[128];

				// Get display string
				GXGetColString(sItem, m_nValueCol, szValue, 127);

				// store key value
				str = szValue;
				bSuccess = TRUE;
			}
		}
	}

	if (pStyle)
		Grid()->RecycleStyle(pStyle);

	return bSuccess;
}

void CGXTabbedComboBox::CheckAndFillCBEdit()
{
	if (m_bCheckAndFillCBEdit && m_bFillWithChoiceList && IsActive() && !IsReadOnly())
	{
		CString strText, sItem;
		int iSelStart;

		GetWindowText(strText);

		int nChoiceListId = _ttoi(m_pStyle->GetUserAttribute(GX_IDS_UA_TABLIST_CHOICELISTID));

		if (nChoiceListId <= 0)
		{
			int nCurSel = GXFindChoiceListItem(strText, m_nDisplayCol, m_pStyle->GetChoiceListRef(), m_bDisplayTitleRow, sItem, TRUE);
			// if no exact text is found, find best match
			if (nCurSel == -1)
				nCurSel = GXFindChoiceListItem(strText, m_nDisplayCol, m_pStyle->GetChoiceListRef(), m_bDisplayTitleRow, sItem, FALSE);
		}
		else
		{
			CMapStringToString* pMap = NULL;

			if (nChoiceListId < Grid()->GetParam()->m_ArrayOfMapTextToChoice.GetSize())
				pMap = (CMapStringToString*) Grid()->GetParam()->m_ArrayOfMapTextToChoice[nChoiceListId];

			pMap->Lookup(strText, sItem);
		}

		if (!sItem.IsEmpty())
		{
			TCHAR szValue[128];

			// Get display string
			GXGetColString(sItem, m_nDisplayCol, szValue, 127);

			iSelStart = strText.GetLength();
			strText = szValue;
			SetCurrentText(strText);
			SetSel(iSelStart, -1, FALSE);
		}
	}
}


void CGXTabbedComboBox::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar >= 32 && !IsReadOnly())
	{
		ReplaceSel(_T(""));
		CGXComboBox::OnChar(nChar, nRepCnt, nFlags);
		CheckAndFillCBEdit();
	}
	else
		CGXComboBox::OnChar(nChar, nRepCnt, nFlags);
}

BOOL CGXTabbedComboBox::KeyPressed(UINT nMessage, UINT nChar, UINT nRepCnt, UINT flags)
{
	BOOL bRet = CGXComboBox::KeyPressed(nMessage, nChar, nRepCnt, flags);

	if (nMessage == WM_CHAR && (nChar >= 32) && !IsReadOnly())
		CheckAndFillCBEdit();

	return bRet;
}

BOOL CGXTabbedComboBox::OnValidate()
{
	CString sText;

	if (IsActive() && GetModify())
	{
		if (!GetValue(sText))
			return FALSE;
	}

	return CGXControl::OnValidate();
}

BOOL CGXTabbedComboBox::ValidateString(const CString& sEdit)
{
	if (sEdit.IsEmpty() || !m_bFillWithChoiceList)
		return TRUE;

	NeedStyle();

	// get pointer to map or allocate on demand
	CMapStringToString* pMap = GetTextToChoiceMap(*m_pStyle);
	CString sItem;
	if (pMap != NULL)
	{
		if (!pMap->Lookup(sEdit, sItem))
		{
			POSITION pos = pMap->GetStartPosition();
			while (pos)
			{
				CString key, line;
				pMap->GetNextAssoc(pos, key, line);

				TCHAR szValue[128];

				GXGetColString(line, m_nDisplayCol, szValue, 127);

				if (_tcsnicmp(szValue, sEdit, sEdit.GetLength()) == 0)
				{
					sItem = line;
					pMap->SetAt(sEdit, sItem);
					return TRUE;
				}
			}
			return FALSE;
		}
		else
			return TRUE;
	}
	else
	{
		if (sEdit.IsEmpty() || !m_bFillWithChoiceList)
			return TRUE;

		CString sItem;
		int nItem = GXFindChoiceListItem(sEdit, m_nDisplayCol, m_pStyle->GetChoiceListRef(), m_bDisplayTitleRow, sItem, FALSE);

		return nItem != -1;
	}
}

CSize CGXTabbedComboBox::CalcSize(CDC* pDC, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle, BOOL bVert)
{
	// Unused:
	bVert, nRow, nCol;

	// User attributes
	int nDisplayCol = _ttoi(style.GetUserAttribute(GX_IDS_UA_TABLIST_TEXTCOL));
	BOOL bDisplayTitleRow = _ttoi(style.GetUserAttribute(GX_IDS_UA_TABLIST_TITLEROW));

	// Select font
	CFont* pOldFont = LoadFont(pDC, style, pStandardStyle);

	// Determine current size of cell (and take care if cell
	// is a covered cell
	CSize size;

	// BLOCK
	{
		TEXTMETRIC    tm;
		pDC->GetTextMetrics(&tm);
		int height = tm.tmHeight + tm.tmExternalLeading + 1;
		int width = 0;

		if (m_bFillWithChoiceList)
		{
			CSize sz;

			TCHAR szDisplayText[128];

			// check each item
			if (style.GetIncludeChoiceList())
			{
				CString s = style.GetChoiceListRef();
				int n = 0;
				CString sItem;

				if (bDisplayTitleRow)
					n = GXGetNextLine(s, sItem);

				while (!s.IsEmpty() && n != -1)
				{
					n = GXGetNextLine(s, sItem);

					GXGetColString(sItem, nDisplayCol, szDisplayText, 127);

					// TRACE1("sItem %s\n", (LPCTSTR) sItem);
					CString str;
					HANDLE hbm = 0;
					hbm = GXGetDIBState()->GetPool()->LookupOrCreateDIB(szDisplayText);

					if (hbm)
					{
						CGXDIB dib;
						dib.Attach(hbm);
						sz = dib.GetSize();
						dib.Detach();
					}
					else
						sz = pDC->GetTextExtent(szDisplayText, (int)_tcslen(szDisplayText));

					width = max(width, sz.cx);
					height = max(height, sz.cy);
				}
			}
		}

		size.cx = width;
		size.cy = height;
	}

	if (pOldFont)
		pDC->SelectObject(pOldFont);

	return AddBorders(size, style);
}


CRect CGXTabbedComboBox::OnGetListboxRect(const CRect& rcCellRect)
{
	return CRect(rcCellRect.left,
		rcCellRect.bottom,
		max(rcCellRect.left + m_nWidthLBox, rcCellRect.right),
		rcCellRect.bottom+Grid()->GetParam()->GetDefaultComboBoxHeight());
}

CGXGridCombo* CGXTabbedComboBox::CreateDropDown(CWnd* pWnd, const CRect& rect)
{
	if (m_pComboLboxPopup == NULL)
		m_pComboLboxPopup = new CGXGridCombo(pWnd, this, rect);
		// CGXComboBox will destory the window

	return m_pComboLboxPopup;
}

CWnd* CGXTabbedComboBox::CreateListBox(CWnd* pParentWnd, UINT nID)
{
	if (m_pComboLbox == NULL)
	{
		// Create an ownerdrawn listbox
		m_pComboLbox = new CGXTabbedComboLBox(this);

		if (m_dwListBoxStyle == 0)
			m_dwListBoxStyle = WS_VSCROLL|LBS_NOTIFY;

		m_dwListBoxStyle |= LBS_OWNERDRAWVARIABLE | LBS_HASSTRINGS;

		m_pComboLbox->Create(m_dwListBoxStyle, CRect(0,0,1,1), pParentWnd, nID);
		// CGXComboBox will destroy the window
	}

	return m_pComboLbox;
}

void CGXTabbedComboBox::OnFillDroppedList(CListBox* lbox)
{
	VERIFY(lbox == m_pComboLbox);
	ASSERT(m_bFillWithChoiceList);
	// Don't call this function if m_bFillWithChoiceList is FALSE

	NeedStyle();

	int nChoiceListId = _ttoi(m_pStyle->GetUserAttribute(GX_IDS_UA_TABLIST_CHOICELISTID));

	// get pointer to map or allocate on demand
	CMapStringToString* pMap = GetTextToChoiceMap(*m_pStyle);
	if (pMap == NULL || nChoiceListId != m_nCurFillChoicelistId || m_nSerial < Grid()->GetParam()->m_nSerial)
	{
		m_nSerial = Grid()->GetParam()->m_nSerial;
		
		CString strText;
		GetWindowText(strText);

		// check if we need to fill combobox with the choice list
		if (!m_bListBoxFilled && m_bFillWithChoiceList)
		{
			// code copied from CGXTabbedComboBox::OnFillDroppedList(lbox);

			int anMaxWidth[GX_TABNMAXCOLS];
			int i;
			for (i = 0; i < GX_TABNMAXCOLS; i++)
				anMaxWidth[i] = -1;

			SetTabStops(GX_TABNMAXCOLS);

			m_pComboLbox->ResetContent();
			m_nWidthLBox = 0;

			if (m_pWndTitleRow)
				m_pWndTitleRow->m_strTitles.Empty();

			// fill with choice list
			if (m_pStyle->GetIncludeChoiceList() && !m_pStyle->GetChoiceListRef().IsEmpty())
			{
				CString s = m_pStyle->GetChoiceListRef();
				CString sItem;
				int n = 0;
				TCHAR szDisplayText[128];

				if (m_nSortCol >= 0)
				{
					GXSortChoiceList(s, m_nSortCol, m_bDisplayTitleRow);
					m_pStyle->SetChoiceList(s);
					m_pStyle->SetUserAttribute(GX_IDS_UA_TABLIST_SORTCOL, _T("-1"));
				}

				// Select font
				CClientDC dc(GridWnd());
				CFont* pOldFont = LoadFont(&dc, *m_pStyle, NULL);

				BOOL bTitleRowDone = FALSE;

				while (!s.IsEmpty() && n != -1)
				{
					n = GXGetNextLine(s, sItem);

					// Determine maximum width for each column
					CGXTabbedLBoxImp::DetermineMaxColWidth(&dc, sItem, GX_TABNMAXCOLS, anMaxWidth);

					// Make sure display string is at beginning of entry
					// This is necessary because the edit part assumes that
					// the text in the edit portion is the first column in
					// the listbox entries.

					if (m_nDisplayCol > 0)
					{
						GXGetColString(sItem, m_nDisplayCol, szDisplayText, 127);

						// Add a tab char
						// QA: 31989 - #if Secure Code Cleanup.
						_tcscat(szDisplayText, _T("\t"));

						// Insert string
						if (!bTitleRowDone && m_bDisplayTitleRow)
							m_pWndTitleRow->m_strTitles = (CString) szDisplayText + sItem;
						else
							m_pComboLbox->AddString((CString) szDisplayText + sItem);
					}
					else
					{
						// First column already is the display text
						if (!bTitleRowDone && m_bDisplayTitleRow)
							m_pWndTitleRow->m_strTitles = sItem;
						else
							m_pComboLbox->AddString(sItem);
					}

					bTitleRowDone = TRUE;
				}

				// deselect font
				if (pOldFont)
					dc.SelectObject(pOldFont);

				// calculate width and no. of columns
				LPCTSTR psz = m_strColWidths;
				int nCols;
				for (nCols = 0; nCols < GX_TABNMAXCOLS && anMaxWidth[nCols] != -1; nCols++)
				{
					if (psz && _istdigit(*psz))
					{
						anMaxWidth[nCols] = _ttoi(psz);
						// end of number
						while (*psz && _istdigit(*psz))
							psz++;
						// next number
						while (*psz && !_istdigit(*psz))
							psz++;
					}
					else if (!m_bDispAllCols && nCols != m_nDisplayCol)
						anMaxWidth[nCols] = 0;
					else
					{
						anMaxWidth[nCols] += 4; // reserve some space between columns
					}
					m_nWidthLBox += anMaxWidth[nCols];
				}

				// cumulate tab positions
				SetTabStops(nCols-1);
				for (i = 0; i < m_iTabCount; i++)
				{
					m_piarTabStops[i] = anMaxWidth[i];
					if (i > 0)
						m_piarTabStops[i] += m_piarTabStops[i-1];
				}

				// NOTE: Will add a switch later which avoids that
				// width is smaller than cell

				m_nWidthLBox += GetSystemMetrics(SM_CXVSCROLL);
			}
		}
	}

	// select string
	{
		CString s;
		GetWindowText(s);
		int n = m_pComboLbox->FindStringExact(-1, s);
		if (n == -1)
			m_pComboLbox->FindString(-1, s);
		if (n != -1)
			m_pComboLbox->SetCurSel(n);
		else
			m_pComboLbox->SelectString(-1, s);
		;
	}

	m_bListBoxFilled = TRUE;
	m_nCurFillChoicelistId = nChoiceListId;
}

void CGXTabbedComboBox::OnStoreDroppedList(CListBox* lbox)
{
	// Save the selection
	int index = lbox->GetCurSel();
	if (index != LB_ERR)
	{
		CString sItem;
		lbox->GetText(index, sItem);

		TCHAR szDisplay[128];
		GXGetColString(sItem, 0, szDisplay, 127);

		SetWindowText(szDisplay);
		SetActive(TRUE);
		SetModify(TRUE);
//		OnModifyCell();
		if (m_bDropdownOnly)
			Refresh();
	}
}

void CGXTabbedComboBox::DestroyDropDownWnd(CWnd*)
{
	// Don't destroy listbox, only hide it
	m_pComboLboxPopup->ShowWindow(SW_HIDE);
	if (m_pWndTitleRow->GetSafeHwnd() && m_pWndTitleRow->IsWindowVisible())
		m_pWndTitleRow->ShowWindow(SW_HIDE);

	// Reset attributes in listbox
	m_pComboLbox->m_bKeyDown = FALSE;
	m_pComboLbox->m_bLButtonDown = FALSE;
}

void CGXTabbedComboBox::ShowDropDown(BOOL bShow)
{
	// TRACE(_T("CGXComboBox::ShowDropDown(BOOL bShow = %d)\n"), bShow);

	if (!bShow)
	{
		// Hide dropdown-listbox
		if (m_pDropDownWnd)
			SendMessage(WM_GX_LBOXCANCEL, 0, IsActive());
		return;
	}
	else if (m_pDropDownWnd && m_pDropDownWnd->IsWindowVisible())
		// dropdown-listbox alread visible
		return;

	// else display dropdown-listbox
	Grid()->SetIgnoreFocus(TRUE);
	Grid()->SetDropDownCell(TRUE);
	Grid()->m_bLockActivateGrid = TRUE;

	// Style
	const CGXStyle& style = Grid()->LookupStyleRowCol(m_nRow, m_nCol);

	CRect rect = CGXControl::GetCellRect(m_nRow, m_nCol, NULL, &style);

	// calculate rectangle for popup window
	// Multi-monitor support
	CRect desktopRect;
	HMONITOR hMonitor = MonitorFromWindow(m_hWnd, MONITOR_DEFAULTTONEAREST);
	ASSERT(hMonitor != NULL);
	MONITORINFO monitorInfo = { sizeof(MONITORINFO) };
	VERIFY(GetMonitorInfo(hMonitor, &monitorInfo));
	desktopRect = monitorInfo.rcWork;

	// hook for changing the default listbox width/height
	Grid()->SetIgnoreFocus(TRUE);

	// create popup window
	m_pDropDownWnd = CreateDropDown(GridWnd(), CRect(0,0,1,1));

	// create listbox
	CWnd* pListBox = CreateListBox(m_pDropDownWnd, m_nListBoxID);
	ASSERT_VALID(pListBox);
	// ASSERTION-> Failed to create listbox ->END

	// embedd listbox in popup window
	m_pDropDownWnd->AttachListBox(pListBox);

	// listbox can be referenced with m_pDropDownWnd->GetLBox()

	// create GDI-font-object
	if (m_fontCombo.GetSafeHandle() != 0)
		m_fontCombo.DeleteObject();

	const LOGFONT& _lf = style.GetFontRef().GetLogFont(Grid()->GetZoom());
	if ( !m_fontCombo.CreateFontIndirect(&_lf) )
	{
		TRACE1("Failed to create font '%s' in CGXGridCore::OnDropDownListRowCol\n",
			(LPCTSTR) style.GetFontRef().GetDescription());
	}

	// set font in listbox
	m_pDropDownWnd->GetLBox().SetFont(&m_fontCombo);

	COLORREF rgbText = style.GetTextColor(),
			 rgbBack = style.GetInteriorRef().GetColor();

	// set colors in m_pDropDownWnd
	// (listbox colors are determined with OnCtlColor in CGXGridCombo)
	if (Grid()->GetParam()->GetProperties()->GetBlackWhite())
	{
		rgbText = RGB(0,0,0);
		rgbBack = RGB(255,255,255);
	}

	m_pDropDownWnd->SetColor(rgbText, rgbBack);

	// Fill entries (also a hook for changing the color)
	OnFillDroppedList(&m_pDropDownWnd->GetLBox());

	CRect rectComboLBox = OnGetListboxRect(rect);

	GridWnd()->ClientToScreen(rectComboLBox);

	// Scroll selected item into view
	CListBox& lBox = m_pDropDownWnd->GetLBox();
	int nOptHeight = m_nDefaultHeight*lBox.GetCount() + lBox.GetItemHeight(0)/2;
	if (nOptHeight < rectComboLBox.Height())
		rectComboLBox.bottom = rectComboLBox.top + nOptHeight;

	if (rectComboLBox.right > desktopRect.right)
		rectComboLBox -= CPoint(rectComboLBox.Width() - rect.Width(), 0);

	if (rectComboLBox.bottom > desktopRect.bottom)
		rectComboLBox -= CPoint(0, rectComboLBox.Height() + rect.Height());

	CGXGridCombo::SetComboBoxDropDown(TRUE);

	// Title row
	if (m_bDisplayTitleRow)
	{
		// Create window for tile row on demand
		if (m_pWndTitleRow->GetSafeHwnd() == 0)
			m_pWndTitleRow->CreateHeader(this);

		m_pWndTitleRow->m_bDispAllCols = m_bDispAllCols;
		m_pWndTitleRow->m_nDisplayCol = m_nDisplayCol;
		m_pWndTitleRow->m_iTabCount = m_iTabCount;
		m_pWndTitleRow->m_piarTabStops = m_piarTabStops;
		m_pWndTitleRow->m_pFont = GetFont();

		unsigned int nHeight = (unsigned int) m_nDefaultHeight;

		CGXTabbedLBoxImp::MeasureHeight(m_pWndTitleRow->m_strTitles, nHeight, !m_bDispAllCols, m_nDisplayCol, m_iTabCount);

		// add small margin to top and botto´m
		nHeight += 4;

		// Position title row
		if (rectComboLBox.bottom + (int) nHeight > desktopRect.bottom)
		{
			// Display listbox above cell
			rectComboLBox -= CPoint(0, rectComboLBox.Height() + rect.Height());
		}

		CRect r = rect;
		GridWnd()->ClientToScreen(&r);
		if (rectComboLBox.bottom > r.bottom)
		{
			// Insert header row between edit part and listbox
			CRect rectHeader = rectComboLBox;
			rectHeader.bottom = rectHeader.top + nHeight;

			m_pWndTitleRow->SetWindowPos(&wndTopMost, rectHeader.left,
				rectHeader.top,
				rectHeader.Width(),
				rectHeader.Height(),
				SWP_SHOWWINDOW
				);

			// Shift listbox down
			rectComboLBox += CPoint(0, rectHeader.Height());
		}
		else
		{
			// Position header row above listbox
			CRect rectHeader = rectComboLBox;
			rectHeader.top = rectComboLBox.top - nHeight;
			rectHeader.bottom = rectComboLBox.top;

			m_pWndTitleRow->SetWindowPos(&wndTopMost, rectHeader.left,
				rectHeader.top,
				rectHeader.Width(),
				rectHeader.Height(),
				SWP_SHOWWINDOW
				);
		}

		m_pWndTitleRow->UpdateWindow();
	}

	rectComboLBox.IntersectRect(rectComboLBox, desktopRect);

	// Display dropdown list box
	m_pDropDownWnd->SetWindowPos(&wndTopMost, rectComboLBox.left,
		rectComboLBox.top,
		rectComboLBox.Width(),
		rectComboLBox.Height(), SWP_SHOWWINDOW);

	lBox.SetWindowPos(NULL, 0, 0, rectComboLBox.Width(), rectComboLBox.Height(), SWP_SHOWWINDOW);

	// Set Focus
	m_pDropDownWnd->GetLBox().SetFocus();
	if (m_pDropDownWnd->GetLBox().GetCurSel() == LB_ERR)
		m_pDropDownWnd->GetLBox().SetCurSel(0);
	m_pDropDownWnd->GetLBox().UpdateWindow();

	CGXGridCombo::SetComboBoxDropDown(FALSE);
	Grid()->SetIgnoreFocus(FALSE);
	Grid()->m_bLockActivateGrid = FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CGXTabbedComboLBox

CGXTabbedComboLBox::CGXTabbedComboLBox(CGXTabbedComboBox* pTabbedComboBox)
	: CGXComboListBox(pTabbedComboBox)
{
	m_pTabbedComboBox = pTabbedComboBox;
}

// DrawItem
//

void CGXTabbedComboLBox::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
	if (lpDIS->itemID == CB_ERR)
		return;

	CDC* pDC = CDC::FromHandle(lpDIS->hDC);

	// Colors
	COLORREF rgbBack, rgbText;
	if (lpDIS->itemState & ODS_SELECTED){

		rgbBack = GetSysColor (COLOR_HIGHLIGHT);
		rgbText = GetSysColor (COLOR_HIGHLIGHTTEXT);
	}
	else
	{
		rgbBack = m_pTabbedComboBox->m_rgbBackColor;
		rgbText = m_pTabbedComboBox->m_rgbTextColor;
	}

	// Check if this is the static part of dropdown listbox
	BOOL bDrawComboBoxEdit = FALSE;

	if (lpDIS->itemAction & (ODA_DRAWENTIRE | ODA_SELECT))
	{
		CString strLBEntry;
		GetText(lpDIS->itemID, strLBEntry);

		CGXTabbedLBoxImp::DrawItem(pDC,
			lpDIS->rcItem,
			strLBEntry,
			!m_pTabbedComboBox->m_bDispAllCols || bDrawComboBoxEdit,
			m_pTabbedComboBox->m_nDisplayCol,
			m_pTabbedComboBox->m_iTabCount,
			m_pTabbedComboBox->m_piarTabStops,
			m_pTabbedComboBox->m_rgbGridLine,
			rgbBack,
			rgbText,
			m_pTabbedComboBox->m_nLeftMargin);
	}

	if (lpDIS->itemAction & ODA_FOCUS)
		pDC->DrawFocusRect(&lpDIS->rcItem);
}

// MeasureItem
//

void CGXTabbedComboLBox::MeasureItem(LPMEASUREITEMSTRUCT lpMIS)
{
	if (lpMIS->itemID == CB_ERR)
		return;

	CString strLBEntry;
	GetText(lpMIS->itemID, strLBEntry);

	lpMIS->itemHeight = (unsigned int) m_pTabbedComboBox->m_nDefaultHeight;

	CGXTabbedLBoxImp::MeasureHeight(strLBEntry, lpMIS->itemHeight,
		!m_pTabbedComboBox->m_bDispAllCols,
		m_pTabbedComboBox->m_nDisplayCol > 0,
		m_pTabbedComboBox->m_iTabCount);
}

// CompareItem
//

int CGXTabbedComboLBox::CompareItem(LPCOMPAREITEMSTRUCT)
{
	return -1;
}

BEGIN_MESSAGE_MAP(CGXTabbedComboLBox, CGXComboListBox)
	//{{AFX_MSG_MAP(CGXTabbedComboLBox)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



