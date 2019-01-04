///////////////////////////////////////////////////////////////////////////////
// gxdtctrl.cpp : DateTime control implementation file
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
// Authors: Daniel Jebaraj, Stefan Hoenig
//
// Portions of this code were copied from Objective Toolkit.

#define _OG_EXPORT_IMPL

#include "stdafx.h"

#if _MFC_VER >= 0x0400   // only supported for MFC version 4.0 or greater

#ifdef _GXDLL
#undef AFXAPI_DATA
#define AFXAPI_DATA __based(__segname("_DATA"))
#endif

// Headers

#ifndef _GXDTCTRL_H_
#include "grid\gxdtctrl.h"
#endif

#ifndef _GXDTCAL_H_
#include "grid\gxdtcal.h"
#endif

#ifndef _GXSTATE_H_
#include "grid\gxstate.h"
#endif

#ifndef _GXEXT_H_
#include "grid\gxext.h"
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

GRID_IMPLEMENT_CONTROL(CGXDateTimeCtrl, CGXStatic)
IMPLEMENT_DYNAMIC(CGXDateTimeCtrl, CGXBDateTimeCtrl)
 
#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXDTBOX")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// Minimum and maximum values of COleDateTime
static const COleDateTime minDateTime = DATE(-657434L);	// About year 100
static const COleDateTime maxDateTime = DATE(2958465L);	// About year 9999
static const int MIN_PRECISION = 13;
static const int MAX_PRECISION = 15;

// Implementation of the helper CGXCaptiveDateTimeCtrl

void CGXCaptiveDateTimeCtrl::SetValue(LPCTSTR pszRawValue)
{
	// Convert the value to the text which should be
	// displayed in the current cell and show this
	// text.

	if (m_hWnd)
	{
		COleDateTime dt;
		
		if (pszRawValue == NULL || m_bForceStrValueAsNumber || !dt.ParseDateTime(pszRawValue))
		{
			if (pszRawValue != NULL && _tcslen(pszRawValue) > 0 && _gxttof(pszRawValue) != 0)
				dt = _gxttof(pszRawValue);
			else if (m_formatType == Custom)
				// Set date to zero date - 12/30/1899
				dt.SetDateTime(1899, 12, 30, 0, 0, 0);
			else if (m_formatType == Time)
				dt.SetTime(0, 0, 0);
			else
			{
				COleDateTime d = COleDateTime::GetCurrentTime();
				dt.SetDate(d.GetYear(), d.GetMonth(), d.GetDay());
			}
		}

		SetDateTime(dt);
	}
}

void CGXCaptiveDateTimeCtrl::LayoutGadgets(CDC* pDC, CRect clientRect)
{
    m_nRightOffset = 0;
    
    // Get DC used for calculating gadget size
    CDC& dc = *pDC;
    
    // Point holding the position of the next gadget.
    CPoint pt(1, 1);
    
    // Now we loop through the gadgets sequentially, setting their position.
    for(int i=0; i<m_gadgets.GetSize(); i++)
    {
        CGXBDTGadget& gadget = *m_gadgets[i];
        
        // Get the size of the gadget.
        gadget.CalcSize(dc);
        CRect r = gadget.GetRect();
        
        if(gadget.GetRect().bottom == -1)
        {
            // Gadget has no height, so set it to the height of the client
            // rectangle.
            r.OffsetRect(pt);
            r.top    = clientRect.top;
            r.bottom = clientRect.bottom;
        }
        else
            // Move the gadget so that it is left aligned with the previous
            // gadget
        {
            r.top+=clientRect.top;
            r.bottom+=clientRect.top;
            r.left+=clientRect.left;
            r.right+=clientRect.left;
            r.OffsetRect(pt);
        }
        if(gadget.GetStyle() & CGXBDTGadget::IsFixed)
        {
            // Fixed gadgets are right aligned.
            clientRect.right -= r.Width();
            r.OffsetRect(clientRect.right - r.left, 0);
            
            // Increase the amount of space reserved for fixed gadgets
            m_nRightOffset += r.Width();
        }
        else
            pt.x += r.Width();
        
        gadget.SetRect(r);
    }
}

void CGXCaptiveDateTimeCtrl::LayoutGadgets()
{
	// This override gets called but we do the work again in
	// the above funtion. So we simply do nothing here
	// CGXBDateTimeCtrl::LayoutGadgets();
}

/////////////////////////////////////////////////////////////////////////////
// CGXDateTimeCtrl

CGXDateTimeCtrl::CGXDateTimeCtrl(CGXGridCore* pGrid, UINT nID):CGXStatic(pGrid)
{
	// The control id
	m_nID = nID;
	// Whether the spin button should be drawn when inactive
	m_bInactiveDrawSpin = FALSE;
	// Whether button gadgets should be drawn when inactive
	m_bInactiveDrawButton = FALSE;
	// Specifies the delimiters used when parsing
	m_strDelim = _T(",");
	// last found gadget
	m_nLastGadget = 0;
	m_bFound = FALSE;

	m_bDateValueAsNumber = TRUE;

	m_nPrecision = 13;

	m_bInitCustomCurrent = TRUE;

	m_bRefreshOnSetCurrentCell = TRUE; // draw spin buttons when current cell

	// Do not let the control process the tab key
	m_bProcessTab = FALSE;

	m_bModify = FALSE;
	m_bActive = FALSE;
}

CGXDateTimeCtrl::~CGXDateTimeCtrl()
{
	m_TextCtrlWnd.DestroyWindow();
	m_DrawCtrlWnd.DestroyWindow();
	DestroyWindow();
}

CWnd* CGXDateTimeCtrl::GetWndPtr() const
{
	return (CWnd*) this;
}

void AFXAPI CGXDateTimeCtrl::AddUserAttributes(CGXStylesMap* pStylesMap)
{
	pStylesMap->AddUserAttribute(GX_IDS_UA_DATENOEDIT,
		CGXStyle()
			.SetControl(GX_IDS_CTRL_CHECKLIST_COMBOBOX)
			.SetChoiceList(CGXResourceString(GX_IDS_CHOICE_DATENOEDIT))
		);
	pStylesMap->AddUserAttribute(GX_IDS_UA_DATEMIN);
	pStylesMap->AddUserAttribute(GX_IDS_UA_DATEMAX);
	pStylesMap->AddUserAttribute(GX_IDS_UA_DATEVALIDMODE,
		CGXStyle()
			.SetControl(GX_IDS_CTRL_TABBED_COMBOBOX)
			.SetChoiceList(CGXResourceString(GX_IDS_CHOICE_DATEVALIDMODE))
			.SetUserAttribute(GX_IDS_UA_TABLIST_KEYCOL, _T("1"))
			.SetUserAttribute(GX_IDS_UA_TABLIST_TEXTCOL, _T("0"))
			.SetUserAttribute(GX_IDS_UA_TABLIST_SHOWALLCOLS, _T("0"))
		);
	pStylesMap->AddUserAttribute(GX_IDS_UA_DATEFORMATTYPE,
		CGXStyle()
			.SetControl(GX_IDS_CTRL_TABBED_COMBOBOX)
			.SetChoiceList(CGXResourceString(GX_IDS_CHOICE_DATEFORMATTYPE))
			.SetUserAttribute(GX_IDS_UA_TABLIST_KEYCOL, _T("1"))
			.SetUserAttribute(GX_IDS_UA_TABLIST_TEXTCOL, _T("0"))
			.SetUserAttribute(GX_IDS_UA_TABLIST_SHOWALLCOLS, _T("0"))
		);
	pStylesMap->AddUserAttribute(GX_IDS_UA_CUSTOMFORMAT);
	pStylesMap->AddUserAttribute(GX_IDS_UA_FASTINPUT,
		CGXStyle()
			.SetControl(GX_IDS_CTRL_CHECKBOX3D)
			.SetVerticalAlignment(DT_VCENTER)
			.SetHorizontalAlignment(DT_CENTER)
		);

	pStylesMap->AddUserAttribute(GX_IDS_UA_FORCESTRVALUEASNUMBER);
	pStylesMap->AddUserAttribute(GX_IDS_UA_PRECISION);
}

BOOL CGXDateTimeCtrl::CreateControl(DWORD dwStyle, LPRECT lpRect)
{
	CRect r(0,0,0,0);

	if (lpRect)
		r = *lpRect;
	
	dwStyle |= WS_CHILD|WS_TABSTOP;//|GXDT_DTS_UPDOWN;// |GXDT_DTS_CALENDAR;

	// used for formatting internally
	
	// Position windows outside visible area
	CRect rc(30000, 30000, 30500, 30100);
	if (!m_TextCtrlWnd.CreateEx(0, dwStyle, rc, GridWnd(), m_nID+1))
		return FALSE;
	if (!m_DrawCtrlWnd.CreateEx(0, dwStyle, rc, GridWnd(), m_nID+2))
		return FALSE;

	return CreateEx(0, dwStyle, r, GridWnd(), m_nID);
}

BEGIN_MESSAGE_MAP(CGXDateTimeCtrl, CGXBDateTimeCtrl)
	//{{AFX_MSG_MAP(CGXDateTimeCtrl)
	ON_WM_KILLFOCUS()
	ON_WM_ERASEBKGND()
	ON_WM_SHOWWINDOW()
	ON_WM_GETDLGCODE()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_LBUTTONUP()
	ON_WM_CHAR()
	ON_WM_SYSKEYDOWN()
	ON_WM_SYSCHAR()
	ON_WM_SYSKEYUP()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGXDateTimeCtrl message handlers

BOOL CGXDateTimeCtrl::SetFormat(CGXBDateTimeCtrl& control, const CGXStyle& style)
{
	// Date/Time format type (see FormatType)
	CString sFormat = style.GetUserAttribute(GX_IDS_UA_DATEFORMATTYPE);
	int n = _ttoi( sFormat );
	FormatType  format = (FormatType)min(4, n);
	CString  CustomFormat = style.GetUserAttribute(GX_IDS_UA_CUSTOMFORMAT) ;

	if (format == Custom || sFormat.IsEmpty() && !CustomFormat.IsEmpty())
	{
		control.SetFormat(CustomFormat);
	}
	else if (sFormat.IsEmpty())
		control.SetFormat(ShortDate);
	else
		control.SetFormat(format);

	return n > 0 && n != 3 || m_bDateTokens; // TRUE if empty current cell should be initialized with current date
							// FALSE if empty current cell should be initialized with PSEUDO_NULL (12/31/1899)
}

CRect CGXDateTimeCtrl::GetCellRect(ROWCOL nRow, ROWCOL nCol, LPRECT rectItem /* = NULL */, const CGXStyle* pStyle /*= NULL*/)
{
	// Don't call CGXStatic::GetCellRect - no frame needed

	return CGXControl::GetCellRect(nRow, nCol, rectItem, pStyle);	
}

CSize CGXDateTimeCtrl::AddBorders(CSize size, const CGXStyle& style)
{
	// Leave some space between buttons and text
	size.cx += 5;

	return CGXControl::AddBorders(size, style);
}

void CGXDateTimeCtrl::Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle)
{
	ASSERT(pDC != NULL && pDC->IsKindOf(RUNTIME_CLASS(CDC)));
	// ASSERTION-> Invalid Device Context ->END
	ASSERT(nRow <= Grid()->GetRowCount() && nCol <= Grid()->GetColCount());
	// ASSERTION-> Cell coordinates out of range ->END

	// Notes on Draw:
	// if (nRow == m_nRow && nCol == m_nCol && m_bIsActive)
	//     initialize CWnd, make it visible and set focus
	// else {
	//     lookup style and draw static, e.g.:
	//     This will be done by iterating through the gadgets
	// }

	ASSERT_VALID(pDC);
	
	
	BOOL bCCell = Grid()->IsCurrentCell(nRow,nCol);

	// Rendering the active control	
	if (nRow == m_nRow && nCol == m_nCol && IsActive() && !Grid()->IsPrinting())
	{
		// Font
		if (m_font.GetSafeHandle())
			m_font.DeleteObject();

		CFont* pOldFont = 0;
		const LOGFONT& _lf = m_pStyle->GetFontRef().GetLogFont(Grid()->GetZoom());
		if ( !m_font.CreateFontIndirect(&_lf) )
		{
			TRACE1("Failed to create font '%s' in CGXDateTimeCtrl::Draw\n",
				(LPCTSTR) m_pStyle->GetFontRef().GetDescription());
		}

		// Cell-Color
		m_clrText = style.GetTextColor();
		m_clrWindow = style.GetInteriorRef().GetColor();

		// Background + Frame
		DrawBackground(pDC, rect, *m_pStyle, TRUE);

		CRect rectText = GetCellRect(nRow, nCol, rect);

		pOldFont = GetFont();
	
		HGDIOBJ oldFont = pOldFont->GetSafeHandle();

		SetFont( &m_font);

		MoveWindow(rectText, FALSE);
		ShowWindow(SW_SHOW);

		if ((Grid()->GetTopRow() > nRow || Grid()->GetLeftCol() > nCol))
		{
			CRect rectClip;
			if (pDC->GetClipBox(&rectClip) != ERROR)
			{
				CRect r = rect & Grid()->GetGridRect();
				GridWnd()->ClientToScreen(&r);
				ScreenToClient(&r);
				GridWnd()->ClientToScreen(&rectClip);
				ScreenToClient(&rectClip);
				ValidateRect(r);
				InvalidateRect(rectClip);
			}
		}

		UpdateWindow();
	
		if (GetFocus() == GridWnd())
		{
			Grid()->SetIgnoreFocus(TRUE);
			SetFocus();
			Grid()->SetIgnoreFocus(FALSE);
		}

		// Reset the old font
		if (oldFont)
			SendMessage(WM_SETFONT, (WPARAM) oldFont,MAKELPARAM(FALSE, 0)); 

		ExcludeClipRect(rectText);
	}
		
	else 
	{
		// Select font
		CFont* pOldFont = LoadFont(pDC, style, pStandardStyle);

		// Background + Frame
		DrawBackground(pDC, rect, style, TRUE);

		CRect rectClip = rect;
		CRect rectText = GetCellRect(nRow, nCol, rect);

		// These drawing routines are mostly from the base class with
		// some changes

		BOOL bOnlyButton = _tcslen(style.GetValueRef()) == 0;
		BOOL bButton = m_bInactiveDrawButton || bCCell && !Grid()->IsPrinting();
		BOOL bSpin = m_bInactiveDrawSpin || bCCell && !Grid()->IsPrinting() && !IsReadOnly();

		// Use the captive draw control

		m_DrawCtrlWnd.m_bForceStrValueAsNumber = 
			        style.GetIncludeUserAttribute(GX_IDS_UA_FORCESTRVALUEASNUMBER) 
					? _ttoi( style.GetUserAttribute(GX_IDS_UA_FORCESTRVALUEASNUMBER))
					: FALSE;

		m_DrawCtrlWnd.SetValue(style.GetIncludeValue() ? (LPCTSTR) style.GetValueRef() : _T(""));

		SetFormat(m_DrawCtrlWnd, style);

		// We call our version of Layout gadgets that is
		// sensitive to the rect that we draw in
		// and knows how to use the dc we have already initialized

		m_DrawCtrlWnd.LayoutGadgets(pDC, rectText);
		
		// Cell-Color
		COLORREF rgbText = style.GetTextColor();
		COLORREF rgbCell = style.GetInteriorRef().GetColor();

		if (Grid()->GetParam()->GetProperties()->GetBlackWhite())
		{
			rgbText = RGB(0,0,0);
			rgbCell = RGB(255,255,255);
		}

		pDC->SetBkMode(TRANSPARENT);
		pDC->SetBkColor(rgbCell);
		pDC->SetTextColor(rgbText);

		// We iterate through and draw all the gadgets
		for(int i=(int)m_DrawCtrlWnd.m_gadgets.GetSize()-1; i>=0; i--)
		{
			CGXDTGadget* gadget = (CGXDTGadget*) m_DrawCtrlWnd.m_gadgets[i];

			// Skip if gadget is outside clipping area
			CRect r;
			if (gadget == NULL || !gadget->m_rect.IntersectRect(rectText, gadget->m_rect))
				continue;

			if(!bOnlyButton && m_DrawCtrlWnd.m_gadgets[i]->IsKindOf(RUNTIME_CLASS(CGXBDTNumericGadget)))
			{
				// Draw the numeric gadget here
				DrawNumericGadget(pDC, (CGXDTNumericGadget*)(m_DrawCtrlWnd.m_gadgets[i]), rectText);
			}
			else if(!bOnlyButton && m_DrawCtrlWnd.m_gadgets[i]->IsKindOf(RUNTIME_CLASS(CGXBDTListGadget)))
			{
				// Draw the List Gadget here
				DrawListGadget(pDC, (CGXDTListGadget*)(m_DrawCtrlWnd.m_gadgets[i]), rectText);
			}
			else if (!bOnlyButton && m_DrawCtrlWnd.m_gadgets[i]->IsKindOf(RUNTIME_CLASS(CGXBDTStaticGadget)))
			{
				// Draw the static Gadget here
				DrawStaticGadget(pDC, (CGXDTStaticGadget *)(m_DrawCtrlWnd.m_gadgets[i]), rectText);
			}
			else if (bButton && m_DrawCtrlWnd.m_gadgets[i]->IsKindOf(RUNTIME_CLASS(CGXBDTButtonGadget)))
			{
				// Draw the button Gadget here
				DrawButtonGadget(pDC, (CGXDTButtonGadget *)(m_DrawCtrlWnd.m_gadgets[i]), rectText);
			}
			else if (bSpin && m_DrawCtrlWnd.m_gadgets[i]->IsKindOf(RUNTIME_CLASS(CGXBDTSpinGadget)))
			{
				// Draw the spin Gadget here
				DrawSpinGadget(pDC, (CGXDTSpinGadget *)(m_DrawCtrlWnd.m_gadgets[i]), rectText);
			}
		}
		
		if (pOldFont)
			pDC->SelectObject(pOldFont);

	}
}

// Helper for static rendering of the spin control
void CGXDateTimeCtrl::DrawSpinGadget(CDC* pDC, CGXDTSpinGadget* pGadget, CRect rectClip)
{
	HTHEME lhTheme = NULL;
	if (RWIsAppThemed() && RWIsThemeActive())
		lhTheme = RWOpenThemeData (RWGetSafeHwnd(), L"SPIN");

	// Unused:
	rectClip;

	pDC->FillSolidRect(pGadget->m_rect, GXGetSysData()->clrBtnFace);

	// Select pens/brushes for drawing arrows
	HGDIOBJ hOldPen   = pDC->SelectObject(::GetStockObject(BLACK_PEN));
	HGDIOBJ hOldBrush = pDC->SelectObject(::GetStockObject(BLACK_BRUSH));

	// Split the button into two parts (spin up button/spin down button)
	int nHeight = pGadget->m_rect.Height()/2;

	// Draw the spin up button
	CRect r = pGadget->m_rect;
	r.bottom = r.top + nHeight;

	if (lhTheme)
	{
		int iState = UPS_NORMAL;
		if (pGadget->m_nState & CGXBDTSpinGadget::SpinUp) iState = UPS_PRESSED;	

		RWDrawThemeBackground (lhTheme, pDC->GetSafeHdc(), SPNP_UP, iState, &r, 0 );			
	}
	else
	{
		pGadget->DrawPart(*pDC, r, FALSE, pGadget->m_nState & CGXBDTSpinGadget::SpinUp);
	}

	// Draw the spin down button
	r = pGadget->m_rect;
	r.top = r.bottom - nHeight;

	if (lhTheme)
	{
		int iState = UPS_NORMAL;		
		if (pGadget->m_nState & CGXBDTSpinGadget::SpinDown) iState = UPS_PRESSED;				

		RWDrawThemeBackground (lhTheme, pDC->GetSafeHdc(), SPNP_DOWN, iState, &r, 0 );			
	}

	else
	{
		pGadget->DrawPart(*pDC, r, TRUE, pGadget->m_nState & CGXBDTSpinGadget::SpinDown);
	}

	pDC->SelectObject(hOldBrush);
	pDC->SelectObject(hOldPen);

	if (lhTheme) RWCloseThemeData (lhTheme);
}

// Numeric control
void CGXDateTimeCtrl::DrawNumericGadget(CDC* pDC, CGXDTNumericGadget* pGadget, CRect rectClip)
{
	// We normally use the current value, unless we are being editted and
	// have a half complete number (in which case we use m_nNewValue).
	int nValue = pGadget->m_nCurDigit ? pGadget->m_nNewValue : pGadget->m_nValue;

	// Build the display string
	TCHAR buf[20];
	if(pGadget->m_bLeadZero)					// with lead zero
	{
		TCHAR buf2[20];
		// QA: 31989 - #if Secure Code Cleanup.
		_stprintf(buf2, _T("%%0%dd"), pGadget->m_nWidth);
		_stprintf(buf, buf2, nValue);	
	}else							// without lead zero
	{
		// QA: 31989 - #if Secure Code Cleanup.
		_stprintf(buf, _T("%d"), nValue);
	}

	// If we are enabled (have focus) then we are highlighted
	COLORREF rgbText = 0, rgbBk = 0;
	int nBkMode = 0;
	if(pGadget->m_bEnabled)
	{
		rgbText = pDC->SetTextColor(GXGetSysData()->clrHighlightText);
		rgbBk = pDC->SetBkColor(GXGetSysData()->clrHighlight);
		nBkMode = pDC->SetBkMode(OPAQUE);
	}

	// and draw the value
	// We use GXDrawTextLikeMultiLineEdit because it's faster
	GXDrawTextLikeMultiLineEdit(pDC,
			buf,
			-1,
			pGadget->m_rect,
			(UINT) DT_SINGLELINE | DT_TOP | DT_CENTER |
		        DT_NOPREFIX | DT_EXTERNALLEADING,
			&rectClip);	// rectClip is the clipping area

	if(pGadget->m_bEnabled)
	{
		pDC->SetTextColor(rgbText);
		pDC->SetBkColor(rgbBk);
		pDC->SetBkMode(nBkMode);
	}
}

void CGXDateTimeCtrl::DrawListGadget(CDC* pDC, CGXDTListGadget* pGadget, CRect rectClip)
{
	// If we are enabled, then we highlight the current string
	COLORREF rgbText = 0, rgbBk = 0;
	int nBkMode = 0;
	if(pGadget->m_bEnabled)
	{
		rgbText = pDC->SetTextColor(GXGetSysData()->clrHighlightText);
		rgbBk = pDC->SetBkColor(GXGetSysData()->clrHighlight);
		nBkMode = pDC->SetBkMode(OPAQUE);
	}

	// Draw the current string
	GXDrawTextLikeMultiLineEdit(pDC,
			pGadget->m_list[pGadget->m_nValue],
			-1,
			pGadget->m_rect,
			(UINT) DT_SINGLELINE | DT_TOP | DT_CENTER |
		        DT_NOPREFIX | DT_EXTERNALLEADING,
			&rectClip);	// SH: s_rectClip is the clipping area

	if(pGadget->m_bEnabled)
	{
		pDC->SetTextColor(rgbText);
		pDC->SetBkColor(rgbBk);
		pDC->SetBkMode(nBkMode);
	}
}

void CGXDateTimeCtrl::DrawStaticGadget(CDC* pDC, CGXDTStaticGadget* pGadget, CRect rectClip)
{
	GXDrawTextLikeMultiLineEdit(pDC, pGadget->m_strCaption,
			-1,
			pGadget->m_rect,
			(UINT) DT_SINGLELINE | DT_TOP | DT_CENTER |
		        DT_NOPREFIX | DT_EXTERNALLEADING,
			&rectClip);	// rectClip is the clipping area
}


void CGXDateTimeCtrl::DrawButtonGadget(CDC* pDC, CGXDTButtonGadget* pGadget, CRect rectClip)
{
	HTHEME lhTheme = NULL;
	if (RWIsAppThemed() && RWIsThemeActive())
		lhTheme = RWOpenThemeData (RWGetSafeHwnd(), L"BUTTON");

	// Unused:
	rectClip;

	CRect r = pGadget->m_rect;

	if (lhTheme)
	{
		int iState = PBS_NORMAL;
		if (m_nState & CGXDTButtonGadget::Down) iState = UPS_PRESSED;	

		RWDrawThemeBackground (lhTheme, pDC->GetSafeHdc(), BP_PUSHBUTTON, iState, &r, 0 );			
		r.DeflateRect(2, 2);
	}
	else
	{
		// Draw the button borders
		if(m_nState & CGXDTButtonGadget::Down)				// Button is currently pressed
		{
			pDC->Draw3dRect(r, GXGetSysData()->clrBtnShadow, GXGetSysData()->clrBtnShadow);
			r.DeflateRect(1, 1);
			pDC->Draw3dRect(r, GXGetSysData()->clrBtnFace, GXGetSysData()->clrBtnFace);
			r.DeflateRect(1, 1);
		}
		else							// Button is currently raised
		{
			pDC->Draw3dRect(r, GXGetSysData()->clrBtnFace, GXGetSysData()->clrWindowFrame);
			r.DeflateRect(1, 1);
			pDC->Draw3dRect(r, GXGetSysData()->clrBtnHilite, GXGetSysData()->clrBtnShadow);
			r.DeflateRect(1, 1);
		}

		// Fill the face of the button (prior to loading bitmap)
		pDC->FillSolidRect(r, GXGetSysData()->clrBtnFace);
	}

	// Now draw the bitmap centered on the face
	CDC memDC;
	if(memDC.CreateCompatibleDC(pDC))
	{
		BITMAP bm;
		VERIFY(pGadget->m_bmp.GetObject(sizeof(bm), &bm) == sizeof(bm));

		int nLeft = (r.Width() - bm.bmWidth)/2 + r.left;
		int nTop  = (r.Height() - bm.bmHeight)/2 + r.top;

		if(m_nState & CGXDTButtonGadget::Down)
			// The button is currently pressed, so offset bitmap to give
			// impression of movement.
			nLeft++, nTop++;

		CBitmap *pOldBmp = memDC.SelectObject(&(pGadget->m_bmp));
		pDC->BitBlt(nLeft, nTop, bm.bmWidth, bm.bmHeight, &memDC, 0, 0, SRCCOPY);
		memDC.SelectObject(pOldBmp);
	}

	if (lhTheme) RWCloseThemeData (lhTheme);
}


void CGXDateTimeCtrl::Init(ROWCOL nRow,ROWCOL nCol)
{
	
	// Stores the cell coordinates, resets the style and sets the window text
	CGXStatic::Init(nRow, nCol);

	BOOL bModify = FALSE;

	if (!m_hWnd)
		CreateControl(0, CRect(0,0,1,1));// need to override CreateControl

	NeedStyle();

	// this will be done in SetValue
	COleDateTime      m_datetime;		// Current date/time

	// set the other attributes
	
	// set the non-editable fields
	SetNoEdit(_ttoi( m_pStyle->GetUserAttribute(GX_IDS_UA_DATENOEDIT)));

	m_bInitCustomCurrent = SetFormat(*this, *m_pStyle);

	// set the window text

	m_bForceStrValueAsNumber = 
			        m_pStyle->GetIncludeUserAttribute(GX_IDS_UA_FORCESTRVALUEASNUMBER) 
					? _ttoi( m_pStyle->GetUserAttribute(GX_IDS_UA_FORCESTRVALUEASNUMBER))
					: FALSE;
	SetValue(m_pStyle->GetIncludeValue() ? (LPCTSTR) m_pStyle->GetValueRef() : _T(""));

	// Get the precision, 13 min or 15 max inclusive
	if (m_pStyle->GetIncludeUserAttribute(GX_IDS_UA_PRECISION))
	{
		int nValue = _ttoi(m_pStyle->GetUserAttribute(GX_IDS_UA_PRECISION));
		if (nValue < MIN_PRECISION)
			m_nPrecision = MIN_PRECISION;
		else if (nValue > MAX_PRECISION)
			m_nPrecision = MAX_PRECISION;
		else
			m_nPrecision = nValue;
	}
	else
		m_nPrecision = MIN_PRECISION;

	// SetNoEdit(int nNoEdit)
	COleDateTime dt1;
	COleDateTime dt2;

	// get the Min and Max Values
	CString s = m_pStyle->GetUserAttribute(GX_IDS_UA_DATEMIN);
	if (m_bForceStrValueAsNumber || !dt1.ParseDateTime(s))
	{
		if (_tcslen(s) > 0 &&  _gxttof(s) != 0)
		    dt1 = _gxttof(s);	
		else
		    dt1 = minDateTime;
	}
	
	s = m_pStyle->GetUserAttribute(GX_IDS_UA_DATEMAX);
	if (m_bForceStrValueAsNumber || !dt2.ParseDateTime(s))
	{
		if (_tcslen(s) > 0 &&  _gxttof(s) != 0)
		    dt2 = _gxttof(s);	
		else
		    dt2 = maxDateTime;
	}
		
	ValidationMode mode = (ValidationMode)_ttoi( m_pStyle->GetUserAttribute(GX_IDS_UA_DATEVALIDMODE));

	SetMinMax(dt1, dt2, mode);
	
	
	m_bFastInput = m_pStyle->GetIncludeUserAttribute(GX_IDS_UA_FASTINPUT) ?
		(BOOL)_ttoi( m_pStyle->GetUserAttribute(GX_IDS_UA_FASTINPUT)) : TRUE;

	if (m_hWnd)
	{
		if ((Grid()->GetParam()->GetActivateCellFlags() & GX_CAFOCUS_SETCURRENT)
			&& OnStartEditing())
			SetActive(TRUE);
	}

	// We could have set it to the current time
	SetModify(bModify);
	
}

void CGXDateTimeCtrl::SetActive(BOOL bActive)
{
	m_bActive = bActive;
}

BOOL CGXDateTimeCtrl::IsActive()
{
	return m_bActive;
}

void CGXDateTimeCtrl::SetModify(BOOL bModified)
{
	m_bModify = bModified;
}

BOOL CGXDateTimeCtrl::GetModify()
{
	return m_bModify;
}

void CGXDateTimeCtrl::SetDateValueAsNumber(BOOL bSetDateValueAsNumber)
{
	m_bDateValueAsNumber = bSetDateValueAsNumber;
}

BOOL CGXDateTimeCtrl::IsDateValueAsNumber()
{
	return m_bDateValueAsNumber;
}

void CGXDateTimeCtrl::SetCurrentText(const CString& str)
{
	if (!IsInit() || !m_hWnd)
		return;

	if (!IsActive())
		SetActive(TRUE);

	COleDateTime dt;
	if (str.IsEmpty() || ValidateString(str) && dt.ParseDateTime(str))
	{
		SetDateTime(dt);
		OnModifyCell();
	}
}

BOOL CGXDateTimeCtrl::ValidateString(const CString& )
{
	return TRUE;
}

// GetCurrentText
// 
void CGXDateTimeCtrl::GetCurrentText(CString& sResult)
{
	if (IsInit() && GetModify())
	{
		sResult = GetDateTime().Format();
		GetControlText(sResult, m_nRow, m_nCol, sResult, *m_pStyle);
	}
	else
		CGXControl::GetCurrentText(sResult);
}

BOOL CGXDateTimeCtrl::GetValue(CString& strResult)
{
	// Reads out the window text and converts it into
	// the plain value which should be stored in the style object.

	if (!IsInit())
		return FALSE;

	if (GetModify())
	{
		if (m_bDateValueAsNumber)
		{
			/*CString strFormat;
			strFormat.Format(_T("%d"), m_nPrecision); 
			strFormat = _T("%.") + strFormat + _T("g");
			strResult.Format(strFormat, (DATE) GetDateTime());*/
			strResult = GetDateTime().Format();
		}
		else
			strResult = GetDateTime().Format(_T("%#c"));
		return TRUE;
	}
	else 
		return CGXControl::GetValue(strResult);
}

void CGXDateTimeCtrl::SetValue(LPCTSTR pszRawValue)
{
	// Convert the value to the text which should be
	// displayed in the current cell and show this
	// text.

	if (m_hWnd)
	{
		COleDateTime dt;

		if (pszRawValue == NULL || m_bForceStrValueAsNumber || !dt.ParseDateTime(pszRawValue))
		{
			if (pszRawValue != NULL && _tcslen(pszRawValue) > 0 && _gxttof(pszRawValue) != 0)
				dt = _gxttof(pszRawValue);
			else if (m_formatType == Custom && !m_bInitCustomCurrent)
				// Set date to zero date - 12/30/1899
				dt.SetDateTime(1899, 12, 30, 0, 0, 0);
			else if (m_formatType == Time)
				dt.SetTime(0, 0, 0);
			else
			{
				COleDateTime d = COleDateTime::GetCurrentTime();
				dt.SetDate(d.GetYear(), d.GetMonth(), d.GetDay());
			}
		}

		SetDateTime(dt);
		OnModifyCell();
	}
}

BOOL CGXDateTimeCtrl::Store()
{
	// Calls SetStyleRange() and resets the modify flag
	ASSERT(m_pStyle);

	CString sValue;
	if (m_pStyle && GetModify() && GetValue(sValue))
	{
		SetActive(FALSE);

		return Grid()->SetValueRange(
			CGXRange(m_nRow, m_nCol),
			sValue,
			gxOverride,
			0, GX_INVALIDATE);
			// Cell will be automatically redrawn inactive
	}

	return TRUE;
}


// GetControlText gives the text as displayed in the cell but as 
// plain text 
// Called when copying the cell contents to the clipboard

BOOL CGXDateTimeCtrl::GetControlText(CString& strDisplay, ROWCOL nRow, ROWCOL nCol, LPCTSTR pszRawValue, const CGXStyle& style)
{
	// Unused:
	nRow, nCol;

	// if value is specified, simply copy this value
	if (pszRawValue)
	{
		strDisplay = pszRawValue;

		if (strDisplay.IsEmpty())
			return FALSE;

		SetFormat(m_TextCtrlWnd, style);
	}

	// check the style object
	else if (style.GetIncludeValue())
	{
		strDisplay = style.GetValueRef();

		if (strDisplay.IsEmpty())
			return FALSE;

		SetFormat(m_TextCtrlWnd, style);
	}
	// no value
	else
	{
		strDisplay.Empty();
		return FALSE;
	}
	
	// we have to supply the text as it would look when displayed
	COleDateTime dt;
	if (!dt.ParseDateTime(strDisplay))
	{
		if (_tcslen(strDisplay) > 0 &&  _gxttof(strDisplay) != 0)
			dt = _gxttof(strDisplay);
		else
			return FALSE;
	}
	
	m_TextCtrlWnd.m_datetime = dt;
	m_TextCtrlWnd.UpdateGadgets();

	CString strTemp(_T(""));
	CString s;

	// Now iterate through all the gadgets and gather the text as 
	// it will be displayed
	for(int i=0; i<m_TextCtrlWnd.m_gadgets.GetSize(); i++)
		{
			int val = m_TextCtrlWnd.m_gadgets[i]->GetValue();	
			// s = _T(" ");
			s.Empty();
			if(m_TextCtrlWnd.m_gadgets[i]->IsKindOf(RUNTIME_CLASS(CGXBDTNumericGadget)))
			{
				CGXDTNumericGadget* pGadget = (CGXDTNumericGadget*) m_TextCtrlWnd.m_gadgets[i];

				// Build the display string
				TCHAR buf[20];
				if(pGadget->m_bLeadZero)					// with lead zero
				{
					TCHAR buf2[20];

					// QA: 31989 - #if Secure Code Cleanup.
					_stprintf(buf2, _T("%%0%dd"), pGadget->m_nWidth);
					_stprintf(buf, buf2, val);					
				}else							// without lead zero
				{
					// QA: 31989 - #if Secure Code Cleanup.
					_stprintf(buf, _T("%d"), val);
				}

				strTemp += buf;
			}
			else if(m_TextCtrlWnd.m_gadgets[i]->IsKindOf(RUNTIME_CLASS(CGXBDTListGadget)) && val!=-1)
			{
				s = ((CGXDTListGadget*)m_TextCtrlWnd.m_gadgets[i])->m_list[val];
				strTemp+=s;
			}
			else if (m_TextCtrlWnd.m_gadgets[i]->IsKindOf(RUNTIME_CLASS(CGXBDTStaticGadget)) && val!=-1)
			{
				s = ((CGXDTStaticGadget*)m_TextCtrlWnd.m_gadgets[i])->m_strCaption;
				strTemp+=s;
			}
		}
		

	// No further work is required
	strDisplay = strTemp;
	return TRUE;
}

CSize CGXDateTimeCtrl::CalcSize(CDC* pDC, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle, BOOL bVert)
{
	// Unused:
    nRow, nCol;
	
    CString strDisplay;
	
    // check the style object
    if (style.GetIncludeValue())
    {
        strDisplay = style.GetValueRef();
		SetFormat(m_TextCtrlWnd, style);
    }
    
    // Font
    // Select font
    CFont* pOldFont = LoadFont(pDC, style, pStandardStyle);
	
    // we have to setup the control as it would look when displayed
	COleDateTime dt;
	if (!dt.ParseDateTime(strDisplay))
	{
		if (_tcslen(strDisplay) > 0 &&  _gxttof(strDisplay) != 0)
			dt = _gxttof(strDisplay);
		else
			return FALSE;
	}
	
	m_TextCtrlWnd.m_datetime = dt;
	m_TextCtrlWnd.UpdateGadgets();
    
    CGXDTGadget* pGadget = NULL;
    int width = 0; int  height = 0;

    // Now iterate through the gadgets and calculate the total width/height

	if (!bVert)
	{
		for(int i=0; i<m_TextCtrlWnd.m_gadgets.GetSize(); i++)
		{
			pGadget = (CGXDTGadget*) m_TextCtrlWnd.m_gadgets[i];
			pGadget->CalcSize(*pDC);
			width+=pGadget->m_rect.Width();
		}
	}
	else
	{
		TEXTMETRIC    tm;
		pDC->GetTextMetrics(&tm);
		height = tm.tmHeight + tm.tmExternalLeading+1;

		for(int i=0; i<m_TextCtrlWnd.m_gadgets.GetSize(); i++)
		{
			pGadget = (CGXDTGadget*) m_TextCtrlWnd.m_gadgets[i];
			pGadget->CalcSize(*pDC);
			height = max(height, pGadget->m_rect.Height());
		}
	}
    
    // Reset the old font
    if (pOldFont)
		pDC->SelectObject(pOldFont);
    
    return AddBorders(CSize(width, height), style);
}

// SetControlText will attempt to convert the text to a valid date first with
// the help of COleDateTime and then with the help of the Date control and the
// current format

BOOL CGXDateTimeCtrl::ConvertControlTextToValue(CString& str, ROWCOL nRow, ROWCOL nCol, const CGXStyle* pOldStyle)
{
	CGXStyle* pStyle = NULL;
	BOOL bSuccess = FALSE;

	if (pOldStyle == NULL)
	{
		pStyle = Grid()->CreateStyle();
		Grid()->ComposeStyleRowCol(nRow, nCol, pStyle);
		pOldStyle = pStyle;
	}

	// allow only valid input
	{
		// First do this
		COleDateTime dt;
		
		if (str.IsEmpty())
		{
			;
			// if (Grid()->IsCurrentCell(nRow, nCol))
			//	Reset();
			bSuccess = TRUE;
		}
		else if (dt.ParseDateTime(str) && (DATE) dt != 0)
		{
			SetDateTime(dt);
			if (m_bDateValueAsNumber)
			{
				// Format the user attribute: precision.
				CString strFormat;
				strFormat.Format(_T("%d"), m_nPrecision);
				strFormat = _T("%.") + strFormat + _T("g");
				str.Format(strFormat, (DATE) dt);
			}
			else
				str = dt.Format();
			bSuccess = TRUE;
		}
		else
		{
			// parse the string using the current format
			CStringArray strArray;
			if (!ParseTextWithCurrentFormat(str, pOldStyle, strArray))
				return FALSE;
			
			SetFormat(m_TextCtrlWnd, *pOldStyle);

			int nArrIndex = 0;
			for(int i=0; i<m_TextCtrlWnd.m_gadgets.GetSize(); i++)
			{
				int val = m_TextCtrlWnd.m_gadgets[i]->GetValue();	
				// s.Empty();
				if(m_TextCtrlWnd.m_gadgets[i]->IsKindOf(RUNTIME_CLASS(CGXBDTNumericGadget)))
				{
					// TRACE(_T("The value %s\n"), strArray[nArrIndex]);
					((CGXDTNumericGadget*)m_TextCtrlWnd.m_gadgets[i])->m_nNewValue = _ttoi(strArray[nArrIndex]);	
					nArrIndex++;
					if (nArrIndex>strArray.GetUpperBound())
							break;
				}
				else if(m_TextCtrlWnd.m_gadgets[i]->IsKindOf(RUNTIME_CLASS(CGXBDTListGadget)) && val!=-1)
				{
					int nIndex = ((CGXDTListGadget*)m_TextCtrlWnd.m_gadgets[i])->FindMatch(strArray[nArrIndex], ((CGXDTListGadget*)m_TextCtrlWnd.m_gadgets[i])->GetValue()+1);
					if (nIndex!=-1)
					{
						// TRACE(_T("The value %s\n"), strArray[nArrIndex]);
						((CGXDTListGadget*)m_TextCtrlWnd.m_gadgets[i])->SetValue(nIndex);
						nArrIndex++;
						if (nArrIndex>strArray.GetUpperBound())
							break;
					}

				}

				if (m_bDateValueAsNumber)
				{
					// Format the user attribute: precision.
					CString strFormat;
					strFormat.Format(_T("%d"), m_nPrecision);
					strFormat = _T("%.") + strFormat + _T("g");
					str.Format(strFormat, (DATE) m_TextCtrlWnd.GetDateTime());
				}
				else
					str = m_TextCtrlWnd.GetDateTime().Format();
			}
			bSuccess = TRUE;
		}
	}

	if (pStyle)
		Grid()->RecycleStyle(pStyle);

	return bSuccess;
}

// This will return the text string as a string array
// This function is called from SetControlText to parse the
// text string into an array of CStrings that the control
// Gadgets will attempt to interpret

BOOL CGXDateTimeCtrl::ParseTextWithCurrentFormat(const CString& str, const CGXStyle* pOldStyle, CStringArray& strArray )
{
	// Unused:
	pOldStyle;

	// we assume that the significant segments are seperated by space

	// Please change m_strDelim to add other delimiters

	CString s;

	LPCTSTR psz = (LPCTSTR) str;
	
	BOOL bLastCharSpace = FALSE;
	DWORD size = str.GetLength()+1;

	// (newline will start a new row, tab delimiter will
	// move to the next column).
	// parse buffer (DBCS aware)
	for (DWORD nIndex = 0, nLast = 0; nIndex < size; nIndex += (int)_tclen(psz+nIndex))
	{
		// check for a delimiter
		if (psz[nIndex] == _T('\0') || _tcschr(_T("\r\n"), psz[nIndex]) || _tcschr(_T(" "), psz[nIndex])
			||!_tcscspn(&psz[nIndex], (LPCTSTR)m_strDelim))
		{
			s.Empty();
			// abort parsing the string if next char
			// is an end-of-string
			if (psz[nIndex] == _T('\0'))
			{

				// QA: 31989 - #if Secure Code Cleanup.
				_tcsncpy(s.GetBuffer((int) (nIndex-nLast)),
					psz+nLast,
					(size_t) (nIndex-nLast));
							
				s.ReleaseBuffer(nIndex-nLast);
				CString temStr = s;
				strArray.Add(temStr);
				temStr.Empty();
				break;
			}
			
			else if (_tcscspn(&psz[nIndex], (LPCTSTR)m_strDelim) == 0 && !bLastCharSpace)
			{
				if (psz[nIndex] == _T('\r') && psz[nIndex+1] == _T('\n'))
					nIndex++;

				// QA: 31989 - #if Secure Code Cleanup.
				_tcsncpy(s.GetBuffer((int) (nIndex-nLast)),
					psz+nLast,
					(size_t) (nIndex-nLast));
							
				s.ReleaseBuffer(nIndex-nLast);
				CString temStr = s;
				strArray.Add(temStr);
				temStr.Empty();
				bLastCharSpace = TRUE;
				// abort parsing the string if next char
				// is an end-of-string
				if (psz[nIndex+1] == _T('\0'))
					break;

			}
			// Now, that the value has been copied to the cell,
			// let's check if we should jump to a new row.
			else if (_tcschr(_T(" "), psz[nIndex]) && !bLastCharSpace)
			{
				if (psz[nIndex] == _T('\r') && psz[nIndex+1] == _T('\n'))
					nIndex++;

				// QA: 31989 - #if Secure Code Cleanup.
				_tcsncpy(s.GetBuffer((int) (nIndex-nLast)),
					psz+nLast,
					(size_t) (nIndex-nLast));
							
				s.ReleaseBuffer(nIndex-nLast);
				CString temStr = s;
				strArray.Add(temStr);
				temStr.Empty();
				bLastCharSpace = TRUE;
				// abort parsing the string if next char
				// is an end-of-string
				if (psz[nIndex+1] == _T('\0'))
					break;
			}
			
			nLast = nIndex + (int)_tclen(psz+nIndex);
			
		
		}
		else
		{	
			// nLast = nIndex + _tclen(psz+nIndex);
			bLastCharSpace = FALSE;
		}
	}
	if (strArray.GetSize())
		return TRUE;
	else
		return FALSE;
}

void CGXDateTimeCtrl::Hide()
{
	// Hides the CGXDateTimeCtrl without changing the m_bIsActive flag
	// and without invalidating the screen
	if (m_hWnd && IsWindowVisible())
	{
		Grid()->SetIgnoreFocus(TRUE);
		HideCaret();
		MoveWindow(CRect(10000,10000,10,10),FALSE);
		ShowWindow(SW_HIDE);
		Grid()->SetIgnoreFocus(FALSE);
	}
}

// Mouse hit
BOOL CGXDateTimeCtrl::LButtonUp(UINT nFlags, CPoint point, UINT nHitState)
{
	NeedStyle();

	CRect rect = GetCellRect(m_nRow, m_nCol);
	
	if (!m_hWnd || !m_gadgets.GetSize() || !rect.PtInRect(point))
		return FALSE;
	
	Grid()->SetIgnoreFocus(TRUE);

	if (Grid()->GetParam()->GetActivateCellFlags()
		& (GX_CAFOCUS_CLICKINTEXT|GX_CAFOCUS_CLICKONCELL|GX_CAFOCUS_SETCURRENT))
	{
		PositionGadget(nFlags, point);
	}
	
	// check child buttons
	CGXStatic::LButtonUp(nFlags, point, nHitState);
	
	Grid()->SetIgnoreFocus(FALSE);

	return TRUE;
}

BOOL CGXDateTimeCtrl::LButtonDblClk(UINT nFlags, CPoint point)
{
	if (!m_hWnd)
		return FALSE;

	if (!IsActive())
	{
		// Position Gadget will find the gadget and set the control active.
		PositionGadget(nFlags, point, TRUE);

		// check child buttons
		CGXStatic::LButtonDblClk(nFlags, point);

		return TRUE;
	}

	return CGXStatic::LButtonDblClk(nFlags, point);
}


// Called to position for editing
void CGXDateTimeCtrl::PositionGadget(UINT nFlags, CPoint pt, BOOL bIgnoreNullValue /* = FALSE */)
{
	CRect rect = GetCellRect(m_nRow, m_nCol);
	if (pt.x > rect.left && pt.y > rect.top)
		pt -= rect.TopLeft();

	// Layout gadgets has the correct client area
	// so that the gadgets have the correct rect for the hittest

	// SetRect will be called from LayoutGadgets to set the correct
	// gadget rect
	MoveWindow(rect, FALSE);
	LayoutGadgets();

	// Find gadget button press occured over.
	int nGadget = GadgetFromPoint(pt);

	// Clicked in cell
	if(m_gadgets[nGadget]->GetStyle() & CGXBDTGadget::WantFocus)
	{
		// when clicked in empty cell don't display value
		if (!bIgnoreNullValue && _tcslen(m_pStyle->GetValueRef()) == 0)
			return;
		else
			m_nCurGadget = nGadget;
	}
	else
		nGadget = -1;

	// Check current gadget
	if(m_nCurGadget < 0
		|| m_nCurGadget >= m_gadgets.GetSize()
		|| m_gadgets[m_nCurGadget] == NULL
		|| !(m_gadgets[m_nCurGadget]->GetStyle() & CGXBDTGadget::WantFocus))
	{
		// search first gadget
		for (int i = 0; i < m_gadgets.GetSize(); i++)
		{
			if (m_gadgets[i]->GetStyle() & CGXBDTGadget::WantFocus)
			{
				m_nCurGadget = i;
				break;
			}
		}
	}

	// Enable/disable gadgets
	for (int i = 0; i < m_gadgets.GetSize(); i++)
		m_gadgets[i]->Enable(m_nCurGadget == i);

	if (!OnStartEditing())
		return;

	// display cell
	SetActive(TRUE);
	Refresh();

	if (nGadget != -1)
		GridWnd()->UpdateWindow();

	// Send WM_LBUTTONDOWN
	SendMessage(WM_LBUTTONDOWN, (WPARAM)nFlags, MAKELPARAM(pt.x,pt.y));
	SendMessage(WM_LBUTTONUP, (WPARAM)nFlags, MAKELPARAM(pt.x,pt.y));
}

BOOL CGXDateTimeCtrl::OnStartEditing()
{
	if (!CGXControl::OnStartEditing())
		return FALSE;

	// Check current gadget
	if(m_nCurGadget < 0
		|| m_nCurGadget >= m_gadgets.GetSize()
		|| m_gadgets[m_nCurGadget] == NULL
		|| !(m_gadgets[m_nCurGadget]->GetStyle() & CGXBDTGadget::WantFocus))
	{
		// search first gadget
		for (int i = 0; i < m_gadgets.GetSize(); i++)
		{
			if (m_gadgets[i]->GetStyle() & CGXBDTGadget::WantFocus)
			{
				m_nCurGadget = i;
				break;
			}
		}
	}

	// Enable/disable gadgets
	for (int i = 0; i < m_gadgets.GetSize(); i++)
		m_gadgets[i]->Enable(m_nCurGadget == i);

	return TRUE;
}


// Keyboard

// called from CGXGridCore when current cell is inactive
// (does not have the focus) and before CGXGridCore
// interpretes the key.

BOOL CGXDateTimeCtrl::OnGridKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!m_hWnd)
		return FALSE;

	BOOL bProcessed = FALSE;

	BOOL bCtl = GetKeyState(VK_CONTROL) & 0x8000;
	BOOL bShift = GetKeyState(VK_SHIFT) & 0x8000;

	// Pass all CTRL keys to the grid
	if (!bCtl)
	{
		switch (nChar)
		{
		case VK_TAB:
		case VK_RETURN:
		case VK_UP:
		case VK_DOWN:
			// Allow these keys to go straight through
			break;

		case VK_DELETE:
			if (Grid()->GetParam()->GetRangeList()->IsEmpty() // no ranges of cells selected
				&& !IsReadOnly()        // cell is not readonly
				&& !bShift
				&& OnDeleteCell()       // OnDeleteCell notification returns TRUE
				&& OnStartEditing())    // OnStartEditing notification returns TRUE
			{
				// Delete text
				SetActive(FALSE);
				SetModify(FALSE);
				Grid()->SetControlTextRowCol(m_nRow, m_nCol, _T(""), GX_UPDATENOW, m_pStyle);

				bProcessed = TRUE;
			}
			break;

		case VK_END:
			Grid()->ScrollCellInView(m_nRow, m_nCol);

			if (OnStartEditing())
			{
				if (!IsInit())
					Init(m_nRow, m_nCol);
				SetActive(TRUE);
				Refresh();

				// find last gadget
				int nLast = -1;
				for (int i=0; i < m_gadgets.GetSize(); i++)
				{
					if(m_gadgets[i]->GetStyle() & CGXBDTGadget::WantFocus)
						nLast = i;

					m_gadgets[i]->Enable(FALSE);
				}

				if (nLast != -1)
					m_nCurGadget = nLast;

				m_gadgets[m_nCurGadget]->Enable(TRUE);

				return TRUE;
			}
			break;

		case VK_HOME:
			Grid()->ScrollCellInView(m_nRow, m_nCol);

			if (OnStartEditing())
			{
				if (!IsInit())
					Init(m_nRow, m_nCol);
				SetActive(TRUE);
				Refresh();
				
				// find first gadget
				int nFirst = -1;
				for (int i=0; i < m_gadgets.GetSize(); i++)
				{
					if(nFirst == -1 && (m_gadgets[i]->GetStyle() & CGXBDTGadget::WantFocus))
						nFirst = i;

					m_gadgets[i]->Enable(FALSE);
				}

				if (nFirst != -1)
					m_nCurGadget = nFirst;

				m_gadgets[m_nCurGadget]->Enable(TRUE);

				return TRUE;
			}
			break;
		}
	}

	return CGXStatic::OnGridKeyDown(nChar, nRepCnt, nFlags);

}

BOOL CGXDateTimeCtrl::OnGridChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!m_hWnd)
		return FALSE;

	// is this a valid character (no Ctrl-Key)
	CString s = (TCHAR) nChar;

	
	// pass valid characters as string to OnGridDoubleByteChar
	if (nChar >= 0x020 && nChar != 0x7f)
		return OnGridDoubleByteChar((CString) (TCHAR) nChar, nRepCnt, nFlags);
	

	// default processing
	return CGXControl::OnGridChar(nChar, nRepCnt, nFlags);
}


BOOL CGXDateTimeCtrl::OnGridDoubleByteChar(const CString& sChar, UINT nRepCnt, UINT nFlags)
{
	// Unused:
	sChar, nRepCnt, nFlags;

	// When several DBCS characters come in, the first char
	// will set the control active and subsequent chars will
	// be handled differently.

	if (IsActive())
	{
		return TRUE;
	}
	else
	{
		// discard key if cell is read only
		if (IsReadOnly() || !OnStartEditing())
			return FALSE;
		
		SetActive(TRUE);

		Refresh();


		// find first gadget
		int nFirst = -1;
		for (int i=0; i < m_gadgets.GetSize(); i++)
		{
			if(nFirst == -1 && (m_gadgets[i]->GetStyle() & CGXBDTGadget::WantFocus))
				nFirst = i;

			m_gadgets[i]->Enable(FALSE);
		}

		if (nFirst != -1)
			m_nCurGadget = nFirst;

		m_gadgets[m_nCurGadget]->Enable(TRUE);

//			ResetCurrentGadget(0);
		if (sChar.GetLength() == 1)
			PostMessage(WM_CHAR, WPARAM(sChar[0]), MAKELPARAM(1, 0));
	}

	return TRUE;
}

BOOL CGXDateTimeCtrl::OnGridSysKeyDown(UINT nChar, UINT nRepCnt, UINT flags)
{
	if(m_gadgets.GetSize() && nChar == VK_DOWN)
	{
		// trigger OnStartEditing
		if (!OnStartEditing())
			return FALSE;

		SetActive(TRUE);

		// Redraw the cell
		if (!Grid()->ScrollCellInView(m_nRow, m_nCol))
			Refresh();

		GridWnd()->UpdateWindow();

		// ALT + Down arrow is an accelerator for the calendar
		if(GetStyle() & GXDT_DTS_CALENDAR)
			PopupCalendar(0, 0, 0);

		return TRUE;
	}

	return CGXStatic::OnGridSysKeyDown(nChar, nRepCnt, flags);
}

void CGXDateTimeCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT flags)
{
	if (!IsActive())
	{
		Grid()->ProcessKeys(this, WM_KEYDOWN, nChar, nRepCnt, flags);
		return;
	}

	BOOL bProcessed = FALSE;
	BOOL bCallDefault = TRUE;

	
	BOOL bCtl = GetKeyState(VK_CONTROL) & 0x8000;
	BOOL bShift = GetKeyState(VK_SHIFT) & 0x8000;

	Grid()->ScrollCellInView(m_nRow, m_nCol);

	// Pass all CTRL keys to the grid
	if (!bCtl)
	{
		switch (nChar)
		{
		case VK_F1:
		case VK_F2:
		case VK_F3:
	  //case VK_F4:
		case VK_F5:
		case VK_F6:
		case VK_F7:
		case VK_F8:
		case VK_F9:
		case VK_F10:
		case VK_F11:
		case VK_F12:
		case VK_F13:
		case VK_F14:
		case VK_F15:
		case VK_F16:
		case VK_F17:
		case VK_F18:
		case VK_F19:
		case VK_F20:
		case VK_F21:
		case VK_F22:
		case VK_F23:
		case VK_F24:
		case VK_NEXT:
		case VK_PRIOR:
		case VK_ESCAPE:
		case VK_RETURN:
			{
				// let grid handle escape key
				bCallDefault = FALSE;
				break;
			}

		case VK_TAB:
			{
				if(m_bProcessTab)
				{
					if(bShift)
					{
						if(!IsFocusOnLeftMostGadget())	
						{
							// Can move left so call base class
							bCallDefault = TRUE;
							break;
						}
							
					}
					else
					{
						if(!IsFocusOnRightMostGadget())	
						{
							// Can move right so call base class
							bCallDefault = TRUE;
							break;
						}
					}

				}

				bCallDefault = FALSE;
				break;
			}

		case VK_DELETE:
			{
				// empty cell
				SetActive(FALSE);
				SetModify(FALSE);
				Grid()->SetControlTextRowCol(m_nRow, m_nCol, _T(""), GX_UPDATENOW, m_pStyle);
				bCallDefault = FALSE;
				bProcessed = TRUE;
				return;
			}

		case VK_SHIFT:
		case VK_BACK:
		case VK_INSERT:
		case VK_LEFT:
		case VK_RIGHT:
		case VK_END:
		case VK_HOME:
		case VK_DOWN:
		case VK_UP:
		
		default:
			{
				// let CGXBDateTimeCtrl handle delete and Insert key
				bCallDefault = TRUE;
				break;
			}
		}

		if (bCallDefault)
		{
			CGXBDateTimeCtrl::OnKeyDown(nChar, nRepCnt, flags);
			bProcessed = TRUE;
		}

	}

	if (!bProcessed)
		Grid()->ProcessKeys(this, WM_KEYDOWN, nChar, nRepCnt, flags);
}

void CGXDateTimeCtrl::OnChar(UINT nChar, UINT nRepCnt, UINT flags)
{
	if (!IsInit() || !IsActive() || (m_pStyle->GetIncludeReadOnly()&& m_pStyle->GetReadOnly())/*(GetStyle() & ES_READONLY)*/ || nChar == 8) // && nRepCnt == 0)
		return;

	BOOL bCallDefault = TRUE;

	// TRACE(_T("CGXDateTimeCtrl::OnChar nChar = %d\n"), nChar);

	BOOL bCtl = GetKeyState(VK_CONTROL) & 0x8000;

	Grid()->ScrollCellInView(m_nRow, m_nCol);

	// CTRL+BACKSPACE??

	if (bCtl)
	{
		switch (nChar)
		{
		case 24:    // CTRL+X
			OpenClipboard();
			EmptyClipboard();
			CloseClipboard();
			
			Cut();
			return;

		case 3:     // CTRL+C
			OpenClipboard();
			EmptyClipboard();
			CloseClipboard();
			
			Copy();
			return;

		case 22:    // CTRL+V
			Paste();
			return;
		}

		// Pass all other CTRL keys to the grid
	}
	else if (nChar == 13 || nChar == 10)
	{
		bCallDefault = FALSE;
	}

	if (bCallDefault)
	{
		SetModify(TRUE);
		CGXBDateTimeCtrl::OnChar(nChar, nRepCnt, flags);
		OnModifyCell();
		Grid()->ProcessKeys(this, WM_CHAR, nChar, nRepCnt, flags);
	}
}

void CGXDateTimeCtrl::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!Grid()->ProcessKeys(this, WM_KEYUP, nChar, nRepCnt, nFlags))
	{
		CGXBDateTimeCtrl::OnKeyUp(nChar, nRepCnt, nFlags);

		if (GetModify())
			OnModifyCell();
	}
}

void CGXDateTimeCtrl::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if(m_gadgets.GetSize() && nChar == VK_DOWN)
	{
		// ALT + Down arrow is an accelerator for the calendar
		if(GetStyle() & GXDT_DTS_CALENDAR)
			PopupCalendar(0, 0, 0);
	}
	else if (!Grid()->ProcessKeys(this, WM_SYSKEYDOWN, nChar, nRepCnt, nFlags))
		CGXBDateTimeCtrl::OnSysKeyDown(nChar, nRepCnt, nFlags);
}

void CGXDateTimeCtrl::OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!Grid()->ProcessKeys(this, WM_SYSCHAR, nChar, nRepCnt, nFlags))
		CGXBDateTimeCtrl::OnSysChar(nChar, nRepCnt, nFlags);
}

void CGXDateTimeCtrl::OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!Grid()->ProcessKeys(this, WM_SYSKEYUP, nChar, nRepCnt, nFlags))
		CGXBDateTimeCtrl::OnSysKeyUp(nChar, nRepCnt, nFlags);
}

void CGXDateTimeCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
	Grid()->SetIgnoreFocus(TRUE);

	CGXBDateTimeCtrl::OnLButtonUp(nFlags, point);

	Grid()->SetIgnoreFocus(FALSE);

	if (GetModify())
		OnModifyCell();
}

// Find and Replace
BOOL CGXDateTimeCtrl::FindText(const GX_FR_STATE& find, ROWCOL nRow, ROWCOL nCol, BOOL bCurrentPos, BOOL bSetCell)
{
	// Always performs an case insensitive search
	BOOL bFound = FALSE;

	LPCTSTR szFind = find.strFindUpper;
	int nFindLen = find.strFindUpper.GetLength();
		// strFindUpper contains the string to search.
		// if bCase is FALSE (case insensitive search),
		// the text in strFindUpper is converted to uppercase

	

	
	// if the active cell contains the text, mark it and return TRUE
	// if not, do a find and return FALSE
	if (nRow == m_nRow && nCol == m_nCol && IsActive())
	{
		int i = 0;
		BOOL bMarked = FALSE;	
		
		CString s = m_strlfText;
		if (!find.bCase)
			s.MakeUpper();

		if (m_LastFRow == nRow && m_LastFCol == nCol && !_tcsncmp(s,szFind,nFindLen) && !bCurrentPos)
		{
			i = m_nLastGadget;
			bMarked = TRUE;
			// return FALSE;
		}

		// int nStart, nEnd;

		// loop through all the gadgets
		int nGagdetFound = -1;
		for(; i<m_gadgets.GetSize(); i++)
		{
			int val = m_gadgets[i]->GetValue();	
			s.Empty();
			if(m_gadgets[i]->IsKindOf(RUNTIME_CLASS(CGXBDTNumericGadget)))
			{
				if (_istdigit(*szFind) && val == _ttoi(szFind))
				{
					nGagdetFound = i;
					m_LastFRow = nRow; m_LastFCol = nCol; m_strlfText = szFind;
					m_nLastGadget = i+1;
					m_bFound = TRUE;
					break;
				}
			}
			else if(m_gadgets[i]->IsKindOf(RUNTIME_CLASS(CGXBDTListGadget)) && val!=-1)
			{
				s = ((CGXDTListGadget*)m_gadgets[i])->m_list[val];
				if (!find.bCase)
					s.MakeUpper();

				if (_tcsncmp(s, szFind, nFindLen) == 0)
				{
					nGagdetFound = i;
					m_LastFRow = nRow; m_LastFCol = nCol; m_strlfText = szFind;
					m_nLastGadget = i+1;
					m_bFound = TRUE;
					break;
				}
			}
		}

		// if gadget was found, enable the gadget and disable all others
		if (nGagdetFound != -1)
		{
			for (i=0; i<m_gadgets.GetSize(); i++)
				m_gadgets[i]->Enable(i == nGagdetFound);
			return TRUE;
		}
		
		if (bMarked)
		{
			m_nLastGadget = 0;
			m_LastFRow = LONG_MAX; m_LastFCol = LONG_MAX; m_strlfText = _T("");
			return FALSE;
		}
			
		return FALSE;


	}
	else
	{
		// request a style object
		CGXStyle* pStyle = Grid()->CreateStyle();

		Grid()->ComposeStyleRowCol(nRow, nCol, pStyle, FALSE);

		// We don't use control text here
		// check the style object
		CString strDisplay(_T(""));
		if (pStyle->GetIncludeValue())
		{
			strDisplay = pStyle->GetValueRef();
				
			SetFormat(m_TextCtrlWnd, *pStyle);
		}
		else
		{
			// Just return FALSE
			return FALSE;
		}
	
		// we have to get the text as it would look when displayed
		COleDateTime dt;
		if (!dt.ParseDateTime(strDisplay))
		{
			if (_tcslen(strDisplay) > 0 &&  _gxttof(strDisplay) != 0)
				dt = _gxttof(strDisplay);
			else
				return FALSE;
		}
		
		m_TextCtrlWnd.m_datetime = dt;
		m_TextCtrlWnd.UpdateGadgets();

		CString strTemp(_T(""));
		CString s;
		// Now iterate through all the gadgets and see if any of the gadgets
		// have what we are looking for
		int i;

		for(i=0; i<m_TextCtrlWnd.m_gadgets.GetSize(); i++)
		{
			int val = m_TextCtrlWnd.m_gadgets[i]->GetValue();	
			s.Empty();
			if(m_TextCtrlWnd.m_gadgets[i]->IsKindOf(RUNTIME_CLASS(CGXBDTNumericGadget)))
			{
				if (_istdigit(*szFind) && val == _ttoi(szFind))
				{
					m_LastFRow = nRow; m_LastFCol = nCol; m_strlfText = szFind;
					m_nLastGadget = i + 1;
					bFound = TRUE;
					m_bFound = TRUE;
					break;
				}
			}
			else if(m_TextCtrlWnd.m_gadgets[i]->IsKindOf(RUNTIME_CLASS(CGXBDTListGadget)) && val!=-1)
			{
				
				s = ((CGXDTListGadget*)m_TextCtrlWnd.m_gadgets[i])->m_list[val];
				if (!find.bCase)
					s.MakeUpper();

				if (_tcsncmp(s, szFind, nFindLen) == 0)
				{
					m_LastFRow = nRow; m_LastFCol = nCol; m_strlfText = szFind;
					m_nLastGadget = i + 1;
					bFound = TRUE;
					m_bFound = TRUE;
					break;
				}
			}
			/* We ignore the static control here
			If you want to use it for some reason you can uncomment these lines
			else if (m_TextCtrlWnd.m_gadgets[i]->IsKindOf(RUNTIME_CLASS(CGXBDTStaticGadget)) && val!=-1)
			{
				s = ((CGXDTStaticGadget*)m_gadgets[i])->m_strCaption;
				if (!_tcsicmp(s, szFind))
				{
					m_LastFRow = nRow; m_LastFCol = nCol; m_strlfText = szFind;
					bFound = TRUE;
					break;
				}
			}*/
		}
		

		// free style object
		Grid()->RecycleStyle(pStyle);

		if (bSetCell && bFound)
			{
				// we have to now mark the text
				Grid()->ScrollCellInView(nRow, nCol);
				Grid()->SetCurrentCell(nRow, nCol, GX_SMART|GX_NOSETFOCUS);
				// Activate the date control
				SetActive(TRUE);
				Refresh();
				// Activate the gadget
				m_gadgets[i]->Enable(TRUE);
				return TRUE;
//				m_LastFRow = LONG_MAX; m_LastFCol = LONG_MAX; m_strlfText = _T("");
			}
		else if (bFound)
			return TRUE;
		
	}

	return FALSE;
}



void CGXDateTimeCtrl::ReplaceSel(LPCTSTR pszReplaceText)
{
	if (!IsInit())
		return;

	CGXControl::ReplaceSel(pszReplaceText);
}

BOOL CGXDateTimeCtrl::ReplaceAll(const GX_FR_STATE& find, ROWCOL nRow, ROWCOL nCol)
{
	// Always performs an case insensitive search
	BOOL bFound = FALSE;

	LPCTSTR szFind = find.strFindUpper;
	int nFindLen = find.strFindUpper.GetLength();
		// strFindUpper contains the string to search.
		// if bCase is FALSE (case insensitive search),
		// the text in strFindUpper is converted to uppercase

	

	
	// if the active cell contains the text, mark it and return TRUE
	// if not, do a find and return FALSE
	if (nRow == m_nRow && nCol == m_nCol && IsActive())
	{
		// Read only support
		if (m_pStyle->GetIncludeReadOnly()&& m_pStyle->GetReadOnly())
			return FALSE;
		
		int i = 0;
		BOOL bMarked = FALSE;	
		
		CString s = m_strlfText;
		if (!find.bCase)
			s.MakeUpper();

		if (m_LastFRow == nRow && m_LastFCol == nCol && !_tcsncmp(s,szFind,nFindLen) && find.bFindOnly)
		{
			i = m_nLastGadget;
			bMarked = TRUE;
			// return FALSE;
		}

		// int nStart, nEnd;

		// loop through all the gadgets
		for(; i<m_gadgets.GetSize(); i++)
		{
			int val = m_gadgets[i]->GetValue();	
			s.Empty();
			if(m_gadgets[i]->IsKindOf(RUNTIME_CLASS(CGXBDTNumericGadget)))
			{
				if (_istdigit(*szFind) && val == _ttoi(szFind))
				{
					m_gadgets[i]->Enable(TRUE);
					m_LastFRow = nRow; m_LastFCol = nCol; m_strlfText = szFind;
					m_nLastGadget = i+1;
					m_bFound = TRUE;
					ReplaceSel(find.strReplace);
					return TRUE;
				}
			}
			else if(m_gadgets[i]->IsKindOf(RUNTIME_CLASS(CGXBDTListGadget)) && val!=-1)
			{
				s = ((CGXDTListGadget*)m_gadgets[i])->m_list[val];
				if (!find.bCase)
					s.MakeUpper();

				if (!_tcsncmp(s, szFind, nFindLen))
				{
					m_gadgets[i]->Enable(TRUE);
					m_LastFRow = nRow; m_LastFCol = nCol; m_strlfText = szFind;
					m_nLastGadget = i+1;
					m_bFound = TRUE;
					ReplaceSel(find.strReplace);
					return TRUE;
				}
			}
		}
		if (bMarked)
		{
			m_nLastGadget = 0;
			m_LastFRow = LONG_MAX; m_LastFCol = LONG_MAX; m_strlfText = _T("");
			return FALSE;
		}
		
		return FALSE;


	}
	else
	{
		// request a style object
		CGXStyle* pStyle = Grid()->CreateStyle();

		Grid()->ComposeStyleRowCol(nRow, nCol, pStyle, FALSE);

		// ReadOnly support
		if (pStyle->GetIncludeReadOnly()&& pStyle->GetReadOnly())
			return FALSE;
		

		// We don't use control text here
		// check the style object
		CString strDisplay(_T(""));
		if (pStyle->GetIncludeValue())
		{
			strDisplay = pStyle->GetValueRef();
			SetFormat(m_TextCtrlWnd, *pStyle);
		}
		else
		{
			// Just return FALSE
			return FALSE;
		}
	
		// we have to get the text as it would look when displayed
		COleDateTime dt;
		if (!dt.ParseDateTime(strDisplay))
		{
			if (_tcslen(strDisplay) > 0 &&  _gxttof(strDisplay) != 0)
				dt = _gxttof(strDisplay);
			else
				return FALSE;
		}
		
		m_TextCtrlWnd.m_datetime = dt;
		m_TextCtrlWnd.UpdateGadgets();

		CString strTemp(_T(""));
		CString s;
		// Now iterate through all the gadgets and see if any of the gadgets
		// have what we are looking for
		int i;

		for(i=0; i<m_TextCtrlWnd.m_gadgets.GetSize(); i++)
		{
			int val = m_TextCtrlWnd.m_gadgets[i]->GetValue();	
			s.Empty();
			if(m_TextCtrlWnd.m_gadgets[i]->IsKindOf(RUNTIME_CLASS(CGXBDTNumericGadget)))
			{
				s.Format(_T("%d"),val); 
				if (!_tcscmp(s, szFind))
				{
					m_LastFRow = nRow; m_LastFCol = nCol; m_strlfText = szFind;
					m_nLastGadget = i + 1;
					bFound = TRUE;
					m_bFound = TRUE;
					break;
				}
			}
			else if(m_TextCtrlWnd.m_gadgets[i]->IsKindOf(RUNTIME_CLASS(CGXBDTListGadget)) && val!=-1)
			{
				s = ((CGXDTListGadget*)m_gadgets[i])->m_list[val];
				if (!_tcsicmp(s, szFind))
				{
					m_LastFRow = nRow; m_LastFCol = nCol; m_strlfText = szFind;
					m_nLastGadget = i + 1;
					bFound = TRUE;
					m_bFound = TRUE;
					break;
				}
			}
			/* We ignore the static control here
			If you want to use it for some reason you can uncomment these lines
			else if (m_TextCtrlWnd.m_gadgets[i]->IsKindOf(RUNTIME_CLASS(CGXBDTStaticGadget)) && val!=-1)
			{
				s = ((CGXDTStaticGadget*)m_gadgets[i])->m_strCaption;
				if (!_tcsicmp(s, szFind))
				{
					m_LastFRow = nRow; m_LastFCol = nCol; m_strlfText = szFind;
					bFound = TRUE;
					break;
				}
			}*/
		}
		

		// free style object
		Grid()->RecycleStyle(pStyle);

		if (bFound)
			{
				// we have to now mark the text
				Grid()->ScrollCellInView(nRow, nCol);
				Grid()->SetCurrentCell(nRow, nCol, GX_SMART|GX_NOSETFOCUS);
				// Activate the date control
				SetActive(TRUE);
				Refresh();
				// Activate the gadget
				m_gadgets[i]->Enable(TRUE);
				ReplaceSel(find.strReplace);
				return TRUE;
			}
		else if (bFound)
			return TRUE;
		
	}

	return FALSE;
}

BOOL CGXDateTimeCtrl::GetSelectedText(CString& sWindowText)
{
	int val = INT_MAX;
	int i;

	if (IsActive())
	{
		for(i=0; i<m_gadgets.GetSize(); i++)
		{
				if (((CGXDTGadget*)m_gadgets[i])->m_bEnabled == TRUE)
				{
					val = m_gadgets[i]->GetValue();	
					break;
				}
		}	
		
		if (val == INT_MAX)
			return FALSE;

		// 1. See if it is a Numeric gadget
		
		CGXBDTGadget* pTemp = m_gadgets[i];
		
		if (pTemp->IsKindOf(RUNTIME_CLASS(CGXBDTNumericGadget)))
		{
			sWindowText.Format(_T("%d"), val);
			return TRUE;
		}
		// 2. See if it is a List gadget
		else if (pTemp->IsKindOf(RUNTIME_CLASS(CGXBDTListGadget)))
		{
			if (val!=-1)
			{
				sWindowText = ((CGXDTListGadget*)m_gadgets[i])->m_list[val];
				return TRUE;
			}
			else
				return FALSE;
			
		}
		
	}
	else
	{
		return FALSE;   // no text selected
	}

	return FALSE;
}




void CGXDateTimeCtrl::OnKillFocus(CWnd* pNewWnd)
{
	CGXBDateTimeCtrl::OnKillFocus(pNewWnd);
	CGXStatic::OnKillFocus(pNewWnd);
}

BOOL CGXDateTimeCtrl::OnEraseBkgnd(CDC* pDC)
{
	UNUSED(pDC);

	CRect rect;
	GetClientRect(rect);

	// Erase Background
	GXPatB(pDC, rect, RGB(255,255,255));
	if (m_pStyle)
	{
		CBrush br;
		br.CreateSolidBrush(m_pStyle->GetInteriorRef().GetColor());
		pDC->FillRect(rect, &br);
	}

	return TRUE;

}

void CGXDateTimeCtrl::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CGXBDateTimeCtrl::OnShowWindow(bShow, nStatus);
}

void CGXDateTimeCtrl::OnSetFocus(CWnd* pOldWnd)
{
	m_nXOrigin = 0;
	CGXBDateTimeCtrl::OnSetFocus(pOldWnd);
}

// Copy
// 
// Copy will only copy data to clipboard if cell is active (has the focus)
// If you also want to support Copy for inactive controls, or if you
// want to support additional clipboard formats, you should
// override these methods.

BOOL CGXDateTimeCtrl::CanCopy()
{
	return CGXControl::CanCopy();
}

// Copy()
// 
// Called when user calls Edit|Copy and the grid
// has a current cell but no range is selected.
// 
// Standard grid copy for both active and inactive state...

BOOL CGXDateTimeCtrl::Copy()
{
	// just perform standard grid copy
	return IsInit()
		&& Grid()->IsCurrentCell(m_nRow, m_nCol)
		&& Grid()->CopyRange(CGXRange(m_nRow, m_nCol));
}

// Cut
// 
// Cut will only cut  data to clipboard if cell is active (has the focus)
// If you also want to support Cut for inactive controls, or if you
// want to support additional clipboard formats, you should
// override these methods.

BOOL CGXDateTimeCtrl::CanCut()
{
	return CGXControl::CanCut();
}

BOOL CGXDateTimeCtrl::Cut()
{
	return CGXControl::Cut();
}

// Paste
// 
// Paste will only paste data from clipboard if cell is active (has the focus)
// If you also want to support Paste for inactive controls, or if you
// want to support additional clipboard formats, you should
// override these methods.

BOOL CGXDateTimeCtrl::CanPaste()
{
	if (Grid()->GetParam()->GetRangeList()->GetCount() == 0
		&& IsInit() && IsActive()
		&& !(m_pStyle->GetIncludeReadOnly() && m_pStyle->GetReadOnly()))
	{
		// Check if clipboard is opened
		BOOL bOpen = FALSE;
		if (CWnd::GetOpenClipboardWindow() == NULL)
			bOpen = GridWnd()->OpenClipboard();

		HGLOBAL handle;
		handle = GetClipboardData(SF_TEXT);

		// If we did open the clipboard, we also need to close it again
		if (bOpen)
			CloseClipboard();

		return handle != 0;
	}

	return FALSE;
}

// Copy() performs the following job:
// a) Copy Selected Text as formatted in the cell

BOOL CGXDateTimeCtrl::Paste()
{
	if (Grid()->GetParam()->GetRangeList()->GetCount() == 0
		&& IsInit() && IsActive()
		&& !(m_pStyle->GetIncludeReadOnly() && m_pStyle->GetReadOnly()))
	{
		// Check if clipboard is opened
		BOOL bOpen = FALSE;
		if (CWnd::GetOpenClipboardWindow() == NULL)
			bOpen = GridWnd()->OpenClipboard();

		HGLOBAL handle;

		handle = GetClipboardData(SF_TEXT);

		// Check for CF_TEXT and related clipboard formats

		if (handle == 0)
		{
#ifdef _UNICODE
			handle = GetClipboardData(CF_UNICODETEXT);
#else
			handle = GetClipboardData(CF_TEXT);

			if (handle == 0)
				handle = GetClipboardData(CF_OEMTEXT);
#endif
		}
		
		// insert text into active current cell
		if (handle)
		{
			LPTSTR psz = (LPTSTR) GlobalLock(handle);
			ReplaceSel(psz);
			GlobalUnlock(handle);
		}



		// If we did open the clipboard, we also need to close it again
		if (bOpen)
			CloseClipboard();

		return handle != 0;
	}

	return FALSE;
}

BOOL CGXDateTimeCtrl::OnValidate()
{
	// save and validate current gadget
	if (m_nState & Editing)
		m_gadgets[m_nCurGadget]->Enable(FALSE);

	return CGXControl::OnValidate();
}

BOOL CGXDateTimeCtrl::CanFloatCell(ROWCOL, ROWCOL, const CGXStyle&, BOOL)
{
	// date time controls don't support floating
	return FALSE;
}


BOOL CGXDateTimeCtrl::OnChanging(const COleDateTime& /* newDateTime */)
{
	
	m_LastFRow = LONG_MAX; m_LastFCol = LONG_MAX; m_strlfText = _T("");
	// Return FALSE if you want to abort the change

	NeedStyle();

	// Check for ReadOnly
	if (m_pStyle->GetIncludeReadOnly()&& m_pStyle->GetReadOnly())
		return FALSE;
	else
	{
		SetModify(TRUE);
		return TRUE;
	}
}

void CGXDateTimeCtrl::OnChanged()
{
	Refresh();

	if (GetModify())
		OnModifyCell();
}

//
// Sorting

void CGXDateTimeCtrl::GetSortKey(ROWCOL nRow, ROWCOL nCol, const CGXSortInfo& sortInfo, const CGXStyle& style, CString& sKey)
{
	// Unused:
	nCol, nRow, sortInfo;

	sKey = style.GetValueRef();
	if (sKey .IsEmpty())
		return;

	SetFormat(m_TextCtrlWnd, style);
	
	// we have to supply the text as it would look when displayed
	COleDateTime dt;
	if (!dt.ParseDateTime(sKey))
		return;

	sKey.Format(_T("%f"), (DATE) dt); 
}


BOOL CGXDateTimeCtrl::StoreStyle(ROWCOL nRow, ROWCOL nCol, const CGXStyle* pStyle, GXModifyType mt, int nType, const CGXStyle* pOldStyle)
{
	ASSERT(pStyle || mt == gxRemove);
	ASSERT(pOldStyle);

	// We are only interested to interere changes in current cell
	if (!CGXControl::StoreStyle(nRow, nCol, pStyle, mt, nType, pOldStyle))
		return FALSE;

	if ((mt == gxOverride || mt == gxApplyNew)
		&& Grid()->IsCurrentCell(nRow, nCol))
	{
		if (pStyle->GetIncludeValue() && !GetModify() || pStyle->GetIncludeControl())
			Reset();  // CGXGridCore::OnDrawItem will call Init again

		else if (IsInit() && 
			(pStyle->GetIncludeUserAttribute(GX_IDS_UA_DATENOEDIT)
			|| pStyle->GetIncludeUserAttribute(GX_IDS_UA_DATEFORMATTYPE)
			|| pStyle->GetIncludeUserAttribute(GX_IDS_UA_CUSTOMFORMAT)
			))
		{
			SetFormat(*this, *pStyle);

			// Check current gadget
			if(m_nCurGadget < 0
				|| m_nCurGadget >= m_gadgets.GetSize()
				|| m_gadgets[m_nCurGadget] == NULL
				|| !(m_gadgets[m_nCurGadget]->GetStyle() & CGXBDTGadget::WantFocus))
			{
				// search first gadget
				for (int i = 0; i < m_gadgets.GetSize(); i++)
				{
					if (m_gadgets[i]->GetStyle() & CGXBDTGadget::WantFocus)
					{
						m_nCurGadget = i;
						break;
					}
				}
			}

			// Enable/disable gadgets
			for (int i = 0; i < m_gadgets.GetSize(); i++)
				m_gadgets[i]->Enable(m_nCurGadget == i);
		}
	}

	return TRUE;
}


#endif // #if _MFC_VER >= 0x0400   
