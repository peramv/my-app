///////////////////////////////////////////////////////////////////////////////
// gxcurctl.cpp
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
// Authors: Daniel Jebaraj, Praveen Ramesh
//
// Portions of this code were copied from Objective Toolkit.

// gxcurr.cpp : implementation of the currency control
//

// Known issues

// const UINT UNSUPPORTED_STYLES = ES_MULTILINE | ES_LOWERCASE |
//										ES_UPPERCASE | ES_AUTOVSCROLL |
//										ES_PASSWORD | ES_WANTRETURN;
// The above styles are not supported by the base class and hence are
// unavailable under the grid also
// We do not support colors for the positive and negative segments		

#define _OG_EXPORT_IMPL

#include "stdafx.h"
#include "grid\gxcurbas.h"
#include "grid\gxresrc.h"
#include "grid\gxcurctl.h"
#include <math.h>

#include "grid\gxmsg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

static BOOL AfxRegisterNamedWndClass(LPCTSTR pcszName, UINT nClassStyle, 
									 HCURSOR hCursor, HBRUSH hbrBackground, 
									 HICON hIcon)
{
	WNDCLASS wndcls;
	if (::GetClassInfo(AfxGetInstanceHandle(), pcszName, &wndcls))
	{
		// NOTE: We have to trust that the hIcon, hbrBackground, and the
		// hCursor are semantically the same, because sometimes Windows does
		// some internal translation or copying of those handles before
		// storing them in the internal WNDCLASS retrieved by GetClassInfo.

		ASSERT(wndcls.style == nClassStyle);
		return TRUE;
	}

	wndcls.style = nClassStyle;
	wndcls.lpfnWndProc = DefWindowProc;
	wndcls.cbClsExtra = wndcls.cbWndExtra = 0;
	wndcls.hInstance = AfxGetInstanceHandle();
	wndcls.hIcon = hIcon;
	wndcls.hCursor = hCursor;
	wndcls.hbrBackground = hbrBackground;
	wndcls.lpszMenuName = NULL;
	wndcls.lpszClassName = pcszName;
    
	if (AfxRegisterClass(&wndcls))
		return TRUE;

	AfxThrowResourceException();
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CGXCurrencyEdit

IMPLEMENT_DYNAMIC(CGXCurrencyEdit, CGXBCurrencyEdit)
GRID_IMPLEMENT_CONTROL(CGXCurrencyEdit, CGXStatic)

TCHAR CGXCurrencyEdit::m_cBlankThouSep = _T('0');
TCHAR CGXCurrencyEdit::m_cBlankMonetarySym = _T('0');

CGXCurrencyEdit::CGXCurrencyEdit(CGXGridCore* pGrid, UINT nID)
	: CGXStatic(pGrid)
{
	m_nID = nID;

	m_bIsActive = FALSE;

	m_dyHeight = 0;
	m_dxMaxCharWidth = 0;
	m_bDoNotEmptyLastChar = FALSE;

	//to prevent recursion in OnSetText
	m_bSetText = FALSE;

	m_bModified = FALSE;

	m_bFirst = TRUE;


	//for the Find/Replace
	m_bIgnoreFractions = FALSE;

	//whether called from Init	
	m_bFromInit = FALSE;

	//Forces a TRUE hittest for the button. Not used in the
	//current implementation
	m_bForceHitTrue = FALSE; //default is FALSE
}

CGXCurrencyEdit::~CGXCurrencyEdit()
{
	m_CapCtrlWnd.DestroyWindow();
	DestroyWindow();
}

BOOL CGXCurrencyEdit::CreateControl(DWORD dwStyle)
{
#if defined(_UNIX_)
	CRect r(-100,-100,10,10);
#else
	CRect r(0,0,0,0);
#endif

	/*
	if (lpRect)
		r = *lpRect;
	*/
		// Get an edit control pointer and make sure the window class 
		// is registered.

		LPCTSTR PCSZ_CLASSNAME = _T("CGXBCurrencyEdit");
		const UINT CLASS_STYLE = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
		
		HCURSOR hcurIBeam = AfxGetApp()->LoadStandardCursor(IDC_IBEAM);
		VERIFY(AfxRegisterNamedWndClass(PCSZ_CLASSNAME, CLASS_STYLE,
										hcurIBeam, NULL, NULL));
		
		
		// If you're looking at this code because the following ASSERT
		// was tripped, it means the edit control has a style not supported
		// by the currency edit.  This is just a debugging aid; the 
		// unsupported styles will be stripped before continuing.

		const UINT UNSUPPORTED_STYLES = ES_MULTILINE | ES_LOWERCASE |
										ES_UPPERCASE | ES_AUTOVSCROLL |
										ES_PASSWORD | ES_WANTRETURN;
		
		// Commented out this assert. This control does not support
		// the above styles and will ignore them
		//ASSERT(!(dwStyle & UNSUPPORTED_STYLES));
		
		//Strip unsupported styles
		
		dwStyle &= ~UNSUPPORTED_STYLES;

		
		
		// Create the window from the parameters obtained above.

		BOOL bRetval = CWnd::CreateEx(0, PCSZ_CLASSNAME, _T(""), dwStyle,
						  r.left, r.top, r.Width(), r.Height(), 
						  GridWnd()->GetSafeHwnd(), (HMENU)(SEC_UINT)m_nID);
		
		//Create the control used internally for formatting
		if (!m_CapCtrlWnd.m_hWnd)
		{
			bRetval &= m_CapCtrlWnd.CWnd::CreateEx(0, PCSZ_CLASSNAME, _T(""), dwStyle,
						  r.left, r.top, r.Width(), r.Height(), 
						  GridWnd()->GetSafeHwnd(), (HMENU)(SEC_UINT)(m_nID+1));
		}

		// TRACE0("CGXCurrencyEdit::CreateControl gets called\n");
		//ASSERT(bRetval);
		return bRetval;
}

BEGIN_MESSAGE_MAP(CGXCurrencyEdit, CGXBCurrencyEdit)
	//{{AFX_MSG_MAP(CGXCurrencyEdit)
	ON_WM_GETDLGCODE()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	ON_WM_ERASEBKGND()
	ON_WM_KILLFOCUS()
	ON_WM_KEYUP()
	ON_WM_SYSKEYDOWN()
	ON_WM_SYSCHAR()
	ON_WM_SYSKEYUP()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_GX_SETTEXT, OnCalcSetText)
#if _MFC_VER >= 0x0400
	ON_WM_CONTEXTMENU()
#endif
	ON_MESSAGE(WM_SETTEXT, OnSetText)
END_MESSAGE_MAP()

// Status
void CGXCurrencyEdit::SetActive(BOOL bActive)
{
	m_bIsActive = bActive && m_hWnd;
}

BOOL CGXCurrencyEdit::IsActive()
{
	return m_bIsActive;
}

void CGXCurrencyEdit::SetModify(BOOL bModified)
{
	m_bModified = bModified;
}

BOOL CGXCurrencyEdit::GetModify()
{
	return m_bModified;
}

// Operations

void CGXCurrencyEdit::Init(ROWCOL nRow, ROWCOL nCol)
{
	m_bFromInit = TRUE;

	// Stores the cell coordinates, resets the style and sets the window text
	CGXStatic::Init(nRow, nCol);

	if (!m_hWnd)
		CreateControl();
	
	NeedStyle();
	
	CString s;
	if (m_pStyle->GetIncludeValue())
		 s = m_pStyle->GetValueRef();


	//Initialize the control from the user attributes for this cell
	InitFromUserAttributes(this, m_pStyle);

	// hook for setting the window text
	SetValue(s);

	//alignment
	if(m_pStyle->GetIncludeHorizontalAlignment())
	{
		switch(m_pStyle->GetHorizontalAlignment())
		{
			case DT_RIGHT:
					SetAlignment(right);
					break;
			case DT_LEFT:
					SetAlignment(left);
					break;
			case DT_CENTER:
					SetAlignment(center);
					break;
		}		
	}
	
	if (m_hWnd)
	{
		CEdit::SetSel(0, -1, FALSE);   // Select all

		if ((Grid()->GetParam()->GetActivateCellFlags() & GX_CAFOCUS_SETCURRENT)
			&& OnStartEditing())
			SetActive(TRUE);
	}

	m_bFromInit = FALSE;
	SetModify(FALSE);
}
//Initializes the control from the user attributes for the cell
//takes care on international settings...
void CGXCurrencyEdit::InitFromUserAttributes(CGXBCurrencyEdit* pEdit,const CGXStyle* pStyle)
{
	//This can be called for captive controls used internally for formatting
	//etc.
	if (pEdit == NULL)
		pEdit = this;
	//Set the other attributes of the control based on user attributes
	CString str1;
	str1 = pStyle->GetUserAttribute(GX_IDS_UA_CURRENCYDEF);

	//if this assert fails you have initialized the wrong number of attributes 
	//needed in the user attribute GX_IDS_UA_CURRENCYDEF
	
	//TRACE("The length of the user attributes is %d\n", str1.GetLength());

	BOOL bInitFromUserAttributes = TRUE;
	
	if(str1.IsEmpty())
		bInitFromUserAttributes = FALSE;

	if(bInitFromUserAttributes && str1.GetLength() != 4) 
		str1 = _T("11 1");

	//parse the string and set the control attributes
	CGXCurrencyEdit::Format format;
	
	format.EnableSeparatorsInLeadingSpace(m_bSeparatorsInLeadingSpaces);

	format.EnableRotateWhileAtEnd(m_bRotateWhileAtEnd);
	
	if(bInitFromUserAttributes)
	{
		TCHAR c = str1[0];
		format.EnableLeadingZero(c - _T('0'));
		c = str1[1];
		format.EnableDecimalSeparatorLine(c - _T('0'));
		format.SetPaddingCharacter(str1[2]);
	}
	
	//if these user attributes are not set the default from the win.ini settings will be
	//used
	if(!pStyle->GetUserAttribute(GX_IDS_UA_CURPOSFORMAT).IsEmpty())
		format.SetPositiveFormat(_ttoi(pStyle->GetUserAttribute(GX_IDS_UA_CURPOSFORMAT)));
	
	if(!pStyle->GetUserAttribute(GX_IDS_UA_CURNEGFORMAT).IsEmpty())
		format.SetNegativeFormat(_ttoi(pStyle->GetUserAttribute(GX_IDS_UA_CURNEGFORMAT)));
	
	if(!pStyle->GetUserAttribute(GX_IDS_UA_CURNUMDECIMALS).IsEmpty())
		format.SetDecimalDigits(_ttoi(pStyle->GetUserAttribute(GX_IDS_UA_CURNUMDECIMALS)));
	
	if(!pStyle->GetUserAttribute(GX_IDS_UA_CURNUMFRACT).IsEmpty())
		format.SetFractionalDigits(_ttoi(pStyle->GetUserAttribute(GX_IDS_UA_CURNUMFRACT)));

	//use a seperate user attribute for these
	if(!pStyle->GetUserAttribute(GX_IDS_UA_CURMON).IsEmpty())
	{
		CString strMon = pStyle->GetUserAttribute(GX_IDS_UA_CURMON);
		if(strMon[0] == m_cBlankMonetarySym)
			format.SetMonetarySymbol(_T(""));
		else
			format.SetMonetarySymbol(strMon);
	}

	if(!pStyle->GetUserAttribute(GX_IDS_UA_CURSEP).IsEmpty())
	{
		CString strSep = pStyle->GetUserAttribute(GX_IDS_UA_CURSEP);
		
		// is this the correct length...else use defaults
		if (strSep.GetLength() !=2)
			strSep = _T(",.");

		if(strSep[0] == m_cBlankThouSep)
			format.SetThousandSeparator(_T('\0'));
		else
			format.SetThousandSeparator(strSep[0]);
		format.SetDecimalSeparator(strSep[1]);
	}

	pEdit->SetFormat(format);
}

void CGXCurrencyEdit::SetCurrentText(const CString& str)
{
	if (!IsInit() || !m_hWnd)
		return;

	if (!IsActive())
		SetActive(TRUE);

	if (ValidateString(str))
	{
		OnSetText(0, (LPARAM)(LPCTSTR) str);
		SetModify(TRUE);
		OnModifyCell();
	}
}
 
// GetCurrentText
void CGXCurrencyEdit::GetCurrentText(CString& sResult)
{
	if (IsActive())
	{
		GetWindowText(sResult);
	}
	else if (IsInit())
	{
		GetControlText(sResult, m_nRow, m_nCol, NULL, *m_pStyle);
	}
	else
	{
		TRACE0("Warning: GetCurrentText was called for an unitialized control!\n");

		// Control is not initialized - Unable to determine text
		sResult.Empty();
	}
}

//Returns the value that will be as stored in the style object
BOOL CGXCurrencyEdit::GetValue(CString& strResult)
{
	// Reads out the window text and converts it into
	// the plain value which should be stored in the style object.
	if (!IsInit())
		return FALSE;

	Format f;
	GetFormat(f);
	
	double d;
	CGXBCurrencyEdit::GetValue(d);
	
	BOOL bNeg = d<0?TRUE:FALSE;
	if (bNeg)
		d = d*(-1);
	double d1 = 0.0;
	// If 0, log10(0) generates a -7776 error (divide by zero?)
	// which when captured by DAO\odbc dlls will cause further problems.
	if (d != 0.0 && f.GetDecimalDigits()!=-1 )
	{
		modf(log10(d), &d1);
		if (d1)
		{
			double logval = d1-(f.GetDecimalDigits()-1);
		
			if (logval>0)
			{
				double d2 = 0.0; double calcval = 0.0;
				modf(pow(10.0, logval), &d1);
				modf(d, &d2);
				if (d1)
					calcval = d2/(d1);
				modf(calcval, &d2);
				d = d2 + modf(d, &d1);
			}
		}
	}
	
	if (bNeg)
		d = d*(-1);

	CString s;
	CString str = _T("%."); 

	s.Format(_T("%d"),f.GetFractionalDigits()); 

	str+=s;
 
	strResult.Format( str+_T("f"), d);

	return TRUE;
}

void CGXCurrencyEdit::SetValue(LPCTSTR pszRawValue)
{
	// Convert the value to the text which should be
	// displayed in the current cell and show this
	// text.
//	TRACE("Set value is called with %s\n",pszRawValue);

	CString sText;
	GetControlText(sText, m_nRow, m_nCol, pszRawValue, *m_pStyle);
	if (m_hWnd)
		SetWindowText(sText);
}

BOOL CGXCurrencyEdit::Store()
{
	// Calls SetStyleRange() and resets the modify flag
	ASSERT(m_pStyle);

	CString sValue;
	if (m_pStyle && GetModify() && GetValue(sValue))
	{
		SetActive(FALSE);
		
		return Grid()->SetExpressionRowCol(
			m_nRow, m_nCol,
			sValue, GX_INVALIDATE);
			// Cell will be automatically redrawn inactive
	}

	return TRUE;
}

void CGXCurrencyEdit::Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle)
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
	//     - edit control with GXDrawTextLikeMultiLineEdit
	// }

	ASSERT_VALID(pDC);

	BOOL bOld = m_bFromInit;
	m_bFromInit = TRUE;

	// if (nRow == m_nRow && nCol == m_nCol && m_bIsActive)
	//     initialize CWnd, make it visible and set focus
	if (nRow == m_nRow && nCol == m_nCol && IsActive() && !Grid()->IsPrinting())
	{
		// ------------------ Active Window ---------------------------

		FreeStyle();
		NeedStyle();

		// Font
		if (m_font.GetSafeHandle())
			m_font.DeleteObject();

		CFont* pOldFont = 0;

		const LOGFONT& _lf = m_pStyle->GetFontRef().GetLogFont(Grid()->GetZoom());
		if ( !m_font.CreateFontIndirect(&_lf) )
		{
			TRACE1("Failed to create font '%s' in CGXCurrencyEdit::Draw\n",
				(LPCTSTR) m_pStyle->GetFontRef().GetDescription());
		}

		// Cell-Color
		COLORREF rgbText = m_pStyle->GetTextColor();//m_rgbWndHilightText;
		COLORREF rgbCell = m_pStyle->GetInteriorRef().GetColor();

		if (Grid()->GetParam()->GetProperties()->GetBlackWhite())
		{
			rgbText = RGB(0,0,0);
			rgbCell = RGB(255,255,255);
		}

		if (m_pFormat)
			m_pFormat->SetBackgroundColor(rgbCell);


		// Background + Frame
		DrawBackground(pDC, rect, *m_pStyle, TRUE);

		CRect rectText = GetCellRect(nRow, nCol, rect);

		pOldFont = pDC->SelectObject(&m_font);

		TEXTMETRIC    tm;
		pDC->GetTextMetrics(&tm);
		m_dyHeight = tm.tmHeight + tm.tmExternalLeading + 1;
		m_dxMaxCharWidth = tm.tmMaxCharWidth;

		if (pOldFont)
			pDC->SelectObject(pOldFont);

		if (!m_pStyle->GetWrapText()) //  && !m_pStyle->GetAllowEnter())
		{
			// vertical alignment for single line text
			// is done by computing the window rectangle for the CGXBCurrencyEdit
			if (m_pStyle->GetIncludeVerticalAlignment())
			{
				switch (m_pStyle->GetVerticalAlignment())
				{
				case DT_VCENTER:
					rectText.top += max(0, (rectText.Height() - m_dyHeight) /2);
					break;
				case DT_BOTTOM:
					rectText.top = max(rectText.top, rectText.bottom-m_dyHeight);
				break;
				}
			}
			rectText.bottom = min(rectText.bottom, rectText.top + m_dyHeight - 1);
		}

		SetFont(&m_font);

		//check if we need to draw the calculator button
		CString str1 = m_pStyle->GetUserAttribute(GX_IDS_UA_CURRENCYDEF);
		
		SetBitmap((UINT)0); // default is that there is no bitmap
		
		if(!str1.IsEmpty() && str1.GetLength() >= 4)
		{
			TCHAR c = str1[3];
			if (c != _T('0'))
				SetBitmap(GX_IDB_CALC);
		}

		MoveWindow(rectText, FALSE);
		
		//Set the color format
		Format fr;
		GetFormat(fr);
		fr.SetBackgroundColor(rgbCell);
		
		//We do not support multiple colors for the 
		//negative and positive inside the grid
		fr.SetNegativeColor(rgbText); 
		fr.SetPositiveColor(rgbText);
		SetFormat(fr);
		
		SetActive(TRUE);

		if (GetFocus() == GridWnd())
		{
			Grid()->SetIgnoreFocus(TRUE);
			SetFocus();
			Invalidate(FALSE);
			UpdateWindow();
			Grid()->SetIgnoreFocus(FALSE);
		}

		ShowWindow(SW_SHOW);

		CEdit::SetReadOnly(CGXControl::IsReadOnly());

		if ((Grid()->GetTopRow() > nRow || Grid()->GetLeftCol() > nCol))
		// Ensure that the window cannot draw outside the clipping area!
		{
			CRect rectClip;
			if (pDC->GetClipBox(&rectClip) != ERROR)
			{
				CRect r = rect & Grid()->GetGridRect();
				GridWnd()->ClientToScreen(&r);
				ScreenToClient(&r);
				GridWnd()->ClientToScreen(&rectClip);
				ScreenToClient(&rectClip);
				ValidateRect(r); // CRect(0, 0, r.right, rectClip.top));
				InvalidateRect(rectClip); // CRect(0, 0, rectClip.left, r.bottom));
			}
		}

		UpdateWindow();

#if _MFC_VER < 0x0300
		// scroll caret into view
		int nStart, nEnd;
		CEdit::GetSel(nStart, nEnd);
		CEdit::SetSel(nStart, nEnd, FALSE);
#endif

		// child Controls: spin-buttons, hotspot, combobox btn, ...
		CGXControl::Draw(pDC, rect, nRow, nCol, *m_pStyle, pStandardStyle);

		ExcludeClipRect(rectText);
	}
	else
	// else {
	//     lookup style and draw static:
	//     - edit control with GXDrawTextLikeMultiLineEdit
	// }
	{

		// ------------------ Static Text ---------------------------

		CGXStatic::Draw(pDC, rect, nRow, nCol, style, pStandardStyle);
	}

	//m_bFromInit = FALSE;
	m_bFromInit = bOld;
}

void CGXCurrencyEdit::Hide()
{
	// Hides the CGXBCurrencyEdit without changing the m_bIsActive flag
	// and without invalidating the screen
	if (m_hWnd && IsWindowVisible())
	{
		Grid()->SetIgnoreFocus(TRUE);
		HideCaret();
		MoveWindow0(FALSE);
		ShowWindow(SW_HIDE);
		Grid()->SetIgnoreFocus(FALSE);
	}
}

// Mouse hit
//fix: changed based on customer feedback
BOOL CGXCurrencyEdit::LButtonUp(UINT nFlags, CPoint pt, UINT nHitState)
{

	if (m_hWnd)
	{
		// Sets the caret position
		int n = CalcTextPosUnderPt(pt);

		if (n != -1 && (Grid()->GetParam()->GetActivateCellFlags() & GX_CAFOCUS_CLICKINTEXT) > 0
			|| Grid()->GetParam()->GetActivateCellFlags()&(GX_CAFOCUS_CLICKONCELL|GX_CAFOCUS_SETCURRENT))


		{
			if (IsActive())
				SetSel(n == -1 ? 0 : n, n);
			else if (OnStartEditing())
			{
				SetActive(TRUE);
				SetSel(n == -1 ? 0 : n, n);
			}
		}

		if (IsActive() && GetFocus() != this)
			Refresh();
	}

	// check child buttons
	CGXStatic::LButtonUp(nFlags, pt, nHitState);

	return TRUE;
}




BOOL CGXCurrencyEdit::LButtonDblClk(UINT nFlags, CPoint pt)
{
	if (m_hWnd)
	{
		if (!IsActive() &&
			(Grid()->GetParam()->GetActivateCellFlags() & GX_CAFOCUS_DBLCLICKONCELL) > 0
			)
		{
			if(OnStartEditing())
			{
				// Set control active
				SetActive(TRUE);
				Refresh();
			}

			// check child buttons
			CGXStatic::LButtonDblClk(nFlags, pt);

			return TRUE;
		}
	}

	return CGXStatic::LButtonDblClk(nFlags, pt);
}

// Keyboard

// called from CGXGridCore when current cell is incative
// (does not have the focus) and before CGXGridCore
// interpretes the key.

BOOL CGXCurrencyEdit::OnGridKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!m_hWnd)
		return FALSE;

	BOOL bProcessed = FALSE;

	BOOL bCtl = GetKeyState(VK_CONTROL) & 0x8000;

	// Pass all CTRL keys to the grid
	if (!bCtl)
	{
		switch (nChar)
		{
		case VK_DELETE:
			break;
		//fix:
		//added support for flipflopping the sign with the 
		//space key.
		case VK_SPACE:
 			{
 				CString s = Grid()->GetValueRowCol(m_nRow, m_nCol);
 				if (m_pFormat->ParseValue(s, m_dValue, m_bNegative)
					&& !(m_pStyle->GetIncludeReadOnly()&& m_pStyle->GetReadOnly()))
 				{
 					// invert the sign
 					m_bNegative = !m_bNegative;
 					CString s;
 					m_pFormat->FormatValue(m_dValue, s, m_bNegative);
 					SetWindowTextNoParse(s);
 					//return TRUE;
 				}
 				
 				bProcessed = TRUE;
 				return TRUE;
 			}

		case VK_END:
		case VK_HOME:
			if (OnStartEditing())
			{
				if (!IsInit())
					Init(m_nRow, m_nCol);
				SetActive(TRUE);

				bProcessed = TRUE;
			}
			break;
		}
	}

	if (bProcessed)
	{
		// eventually destroys and creates CGXBCurrencyEdit with appropriate window style
		if (!Grid()->ScrollCellInView(m_nRow, m_nCol))
			Refresh();

		return TRUE;
	}

	return CGXStatic::OnGridKeyDown(nChar, nRepCnt, nFlags);

}

BOOL CGXCurrencyEdit::OnGridChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!m_hWnd)
		return FALSE;

	// Unused:
	nRepCnt, nFlags;

	if (nChar >= 0x020 && nChar != 0x7f && !IsActive())
	{
		// discard key if cell is read only
		if (CGXControl::IsReadOnly() || !OnStartEditing())
			return FALSE;

		SetActive(TRUE);
		PostMessage(WM_CHAR, (WPARAM) nChar, MAKELPARAM(nRepCnt, nFlags));
		Refresh();
	}

	// default processing
	return CGXControl::OnGridChar(nChar, nRepCnt, nFlags);
}

BOOL CGXCurrencyEdit::OnGridDoubleByteChar(const CString& sChar, UINT nRepCnt, UINT nFlags)
{
	sChar, nRepCnt, nFlags;

	return TRUE;
}

BOOL CGXCurrencyEdit::Cut()
{
	return CGXControl::Cut();
}

BOOL CGXCurrencyEdit::Copy()
{
	return CGXControl::Copy();
}

BOOL CGXCurrencyEdit::Paste()
{
	return CGXControl::Paste();
}


void CGXCurrencyEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT flags)
{
	ASSERT(IsActive());
	
	BOOL bProcessed = FALSE;
	BOOL bCallDefault = TRUE;

//	TRACE("CGXCurrencyEdit::OnKeyDown nChar = %d\n", nChar);

	BOOL bCtl = GetKeyState(VK_CONTROL) & 0x8000;
	BOOL bShift = GetKeyState(VK_SHIFT) & 0x8000;

	Grid()->ScrollCellInView(m_nRow, m_nCol);

	
	// Pass all CTRL keys to the grid
	if (!bCtl)
	{
		// window text and caret position
		CString s;
		int ns, nr;

		GetWindowText(s);
		GetSel(ns, nr);
		
		switch (nChar)
		{
		case VK_RIGHT:
			bCallDefault = m_iCaretPos < (int) s.GetLength();
			break;

		case VK_LEFT:
			{
				bCallDefault = m_iCaretPos > 0;
				break;
			}
		case VK_DOWN:
			// process down arrow if not at last line
			bCallDefault = LineFromChar(nr)+1 < GetLineCount();
			break;

		case VK_UP:
			// process up arrow if not at first line
			bCallDefault = LineFromChar(ns) > 0;
			break;

		case VK_RETURN:
			// does edit control want to handle the RETURN key itsself?
			bCallDefault = FALSE;
			break;
		//Fix
		//Added support for flipflopping the sign
		case VK_SPACE:
 			{
 				if (m_pFormat->ParseValue(s, m_dValue, m_bNegative)
					&& !(m_pStyle->GetIncludeReadOnly()&& m_pStyle->GetReadOnly()))
 				{
 					// invert the sign
					m_bNegative = !m_bNegative;
 					CString s;
 					m_pFormat->FormatValue(m_dValue, s, m_bNegative);
 					SetWindowTextNoParse(s);
 					//return TRUE;
 				}
 				bCallDefault = FALSE;
 				bProcessed = TRUE;
 				return;
 			}

		case VK_F1:
		case VK_F2:
		case VK_F3:
		case VK_F4:
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
		case VK_TAB:
		case VK_NEXT:
		case VK_PRIOR:
			bCallDefault = FALSE;
			break;
		case VK_ESCAPE:
			// let grid handle escape key
			bCallDefault = FALSE;
			break;

		case VK_DELETE:
			{
				//fix:
				//changed the behavior of VK_DELETE. Does 
				//not delete the entire value anymore.
				SetModify(TRUE);
				
				if (bShift) 
					OnEditCut();
				else
					DoDelete();
					
				bCallDefault = FALSE;
				bProcessed = TRUE;
				return;

			}

		case VK_INSERT:
			{
				if (bShift)
				{
					Paste();
					bCallDefault = FALSE;
					bProcessed = TRUE;
				}
				else
					bCallDefault = TRUE;
				break;
			}

		case VK_HOME:
		case VK_END:
		case VK_SHIFT:
		default:
			// let CGXBCurrencyEdit handle insert key
			// let CGXBCurrencyEdit handle delete and Insert key
			// let CGXBCurrencyEdit handle all other keys
			bCallDefault = TRUE;
			break;
		}

		

	}


	if (bCallDefault)
		{
			CGXBCurrencyEdit::OnKeyDown(nChar, nRepCnt, flags);
			bProcessed = TRUE;
		}

	if (!bProcessed)
		Grid()->ProcessKeys(this, WM_KEYDOWN, nChar, nRepCnt, flags);
}


void CGXCurrencyEdit::OnChar(UINT nChar, UINT nRepCnt, UINT flags)
{
	
	if (!IsInit() || !IsActive() || (m_pStyle->GetIncludeReadOnly()&& m_pStyle->GetReadOnly())/*(GetStyle() & ES_READONLY)*/ || nChar == 8) // && nRepCnt == 0)
		return;

	
	BOOL bCallDefault = TRUE;

	// TRACE(_T("CGXCurrencyEdit::OnChar nChar = %d\n"), nChar);

	BOOL bCtl = GetKeyState(VK_CONTROL) & 0x8000;

	Grid()->ScrollCellInView(m_nRow, m_nCol);

	// CTRL+BACKSPACE??

	if (bCtl)
	{
		/*switch (nChar) // Handled in CGXBCurrencyEdit.
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
		}*/

		return; 

		// Pass all other CTRL keys to the grid
	}
	else if (nChar == 13 || nChar == 10)
	{
		bCallDefault = FALSE;
	}

	if (bCallDefault)
	{
		CGXBCurrencyEdit::OnChar(nChar, nRepCnt, flags);
		Grid()->ProcessKeys(this, WM_CHAR, nChar, nRepCnt, flags);
	}
}

void CGXCurrencyEdit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!Grid()->ProcessKeys(this, WM_KEYUP, nChar, nRepCnt, nFlags))
		CGXBCurrencyEdit::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CGXCurrencyEdit::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!Grid()->ProcessKeys(this, WM_SYSKEYDOWN, nChar, nRepCnt, nFlags))
		CGXBCurrencyEdit::OnSysKeyDown(nChar, nRepCnt, nFlags);
}

void CGXCurrencyEdit::OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!Grid()->ProcessKeys(this, WM_SYSCHAR, nChar, nRepCnt, nFlags))
		CGXBCurrencyEdit::OnSysChar(nChar, nRepCnt, nFlags);
}

void CGXCurrencyEdit::OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!Grid()->ProcessKeys(this, WM_SYSKEYUP, nChar, nRepCnt, nFlags))
		CGXBCurrencyEdit::OnSysKeyUp(nChar, nRepCnt, nFlags);
}

void CGXCurrencyEdit::OnLButtonDown(UINT nFlags, CPoint point)
{
	ASSERT_VALID(this);

	int nOldStartSel, nOldEndSel;
	GetSel(nOldStartSel, nOldEndSel);

	// call the base class so the caret gets set right
	CGXBCurrencyEdit::OnLButtonDown(nFlags, point);

	// check if user clicked into selectect text
	int nStartSel, nEndSel;
	CEdit::GetSel(nStartSel, nEndSel);

	if (nOldStartSel != nOldEndSel
		&& nStartSel == nEndSel
		&& nStartSel >= nOldStartSel
		&& nStartSel <= nOldEndSel)
	{
		// Keep old selection
		SetSel(nOldStartSel, nOldEndSel);

		// Start Drag&Drop
		Grid()->DndStartDragDrop(m_nRow, m_nCol);

		// if internal state is still valid
		if (!IsInit() || !IsActive() || !Grid()->IsCurrentCell(m_nRow, m_nCol))
			return;

		// ... continue
		SetSel(nStartSel, nEndSel);
	}
}

BOOL CGXCurrencyEdit::OnCommand(WPARAM wParam, LPARAM lParam)
{
#if _MFC_VER < 0x0300
	UINT nNotification = HIWORD(lParam);
	HWND hCtl = (HWND) LOWORD(lParam);
#else
	UINT nNotification = HIWORD(wParam);
	HWND hCtl = (HWND) lParam;
#endif

	if (hCtl == m_hWnd && IsActive())
	{
		if (nNotification == EN_CHANGE)
			OnModifyCell();
	}

	return CGXControl::OnCommand(wParam, lParam);
}

// The find methods have two implementations based on whether they should ignore decimals or not. If they are
// to ignore decimals a numeric search is done.  

BOOL CGXCurrencyEdit::FindText(const GX_FR_STATE& find, ROWCOL nRow, ROWCOL nCol, BOOL bCurrentPos, BOOL bSetCell)
{
	LPCTSTR szValue = NULL;
	LPCTSTR pszFound = NULL;
	LPCTSTR szFind = find.strFindUpper;
		// strFindUpper contains the string to search.
		// if bCase is FALSE (case insensitive search),
		// the text in strFindUpper is converted to uppercase

	if (!m_bIgnoreFractions)
	{
		// if the active cell contains the text, mark it and return TRUE
		// if not, do a find and return FALSE
		if (nRow == m_nRow && nCol == m_nCol && IsActive())
		{
			CString s;
			
			//Strip the monetary symbol if it's present
			Format f;
			GetFormat(f);
			LPCTSTR str = f.GetMonetarySymbol();
			
			//We asssume that the monetary symbol is at the beginning of szFind
			CString pTrunc(szFind);
			if (!_tcscmp(pTrunc.Left((int)_tcslen(str)),str))
				szFind = _tcsninc(szFind, _tcslen(str));
			
			int nStart(0), nEnd(0);

			CEdit::GetSel(nStart, nEnd);
			GetWindowText(s);

			s.MakeUpper();

			LPCTSTR pv = szValue = s;

			if (nStart!= INT_MAX && nStart != -1 && nEnd != -1)
				szValue += nStart + (bCurrentPos ? 0 : _tclen(szValue + nStart));

			pszFound = _tcsstr(szValue, szFind);

			if (pszFound != NULL)
			{
				if (bSetCell)
				{
					int nStart = (int)(pszFound - pv);

					// mark the text I have found
					SetSel(nStart, nStart+(int)_tcslen(szFind));
				}
				return TRUE;
			}
		}
		else
		{
			// request a style object
			CGXStyle* pStyle = Grid()->CreateStyle();

			Grid()->ComposeStyleRowCol(nRow, nCol, pStyle, FALSE);

			CString s;
			if (GetControlText(s, nRow, nCol, NULL, *pStyle))
			{
				// Convert text to upper case if we are doing a case insensitive search
				if (!find.bCase)
					s.MakeUpper();

				szValue = s;
			}
			else
				szValue = _T("");

			
			//Strip the monetary symbol if it's present
			TCHAR c = pStyle->GetUserAttribute(GX_IDS_UA_CURRENCYDEF)[2];
			
			if (!_tcscmp(szFind,&c))
				szFind = _tcsinc(szFind);

			
			// free style object
			Grid()->RecycleStyle(pStyle);

			pszFound = _tcsstr(szValue, szFind);

			if (pszFound != NULL)
			{
				if (bSetCell)
				{
					int nStart = (int)(pszFound - szValue);

					// mark the text I have found
					Grid()->ScrollCellInView(nRow, nCol);
					Grid()->SetCurrentCell(nRow, nCol, GX_SMART|GX_NOSETFOCUS);
					SetActive(TRUE);
					SetSel(nStart, nStart+(int)_tcslen(szFind));
					Refresh();
				}
				return TRUE;
			}
		}

		return FALSE;
	}
	
	else
	{
		int nVal(0);
		int nFind = _ttoi(szFind);
		
		if (nRow == m_nRow && nCol == m_nCol && IsActive())
		{
			if (m_LFRow==nRow)
				return FALSE;
			
			CString s;
			
			//Strip the monetary symbol if it's present
			Format f;
			GetFormat(f);
			
			LPCTSTR c = f.GetMonetarySymbol();
			
			
			CString pTrunc(szFind);

			if (_tcsstr(szFind,c)!=NULL || !_tcscmp(c, pTrunc.Left((int)_tcslen(c))))
				szFind = _tcsninc(szFind, _tcslen(c));

			//convert the find value to integer
			nFind = _ttoi(szFind);

			int nStart(0), nEnd(0);

			CEdit::GetSel(nStart, nEnd);
			GetWindowText(s);

			s.MakeUpper();



			//Strip the monetary char is it's present off the window text as well
			LPCTSTR sz = NULL;
			if (_tcsstr(s,c) !=NULL)
					sz = _tcsninc(s, _tcslen(c));
				else
					sz = s;
				

			nVal = _ttoi(sz);

			

			if (bSetCell && (nVal == nFind) && (nVal||nFind))
				{
					// Select the entire text
					SetSel(0, -1);
					m_LFRow = nRow;
					return TRUE;
				}
				else if((nVal == nFind) && (nVal||nFind))
				{
					m_LFRow = nRow;
					return TRUE;
				}
		}
		else
		{
			// request a style object
			CGXStyle* pStyle = Grid()->CreateStyle();

			Grid()->ComposeStyleRowCol(nRow, nCol, pStyle, FALSE);

			
			// to strip the monetary symbol if it's present
			TCHAR c = pStyle->GetUserAttribute(GX_IDS_UA_CURRENCYDEF)[2];
			
			
			CString s;
			LPCTSTR sz = NULL;
			if (GetControlText(s, nRow, nCol, NULL, *pStyle))
			{
				// Convert text to upper case if we are doing a case insensitive search
				if (!find.bCase)
					s.MakeUpper();
					
				if (_tcsstr(s,&c) !=NULL || s[0] == c)
					sz = _tcsinc(s);
				else
					sz = s;
				
				nVal = _ttoi(sz);
			}
			else
				nVal = 0;

			
			
			if (_tcsstr(szFind,&c)!=NULL || szFind[0] == c)
				szFind = _tcsinc(szFind);
		
			nFind = _ttoi(szFind);
			
			// free style object
			Grid()->RecycleStyle(pStyle);

		

				if (bSetCell && (nVal == nFind) && (nVal||nFind))
				{
					// mark the text I have found
					Grid()->ScrollCellInView(nRow, nCol);
					Grid()->SetCurrentCell(nRow, nCol, GX_SMART|GX_NOSETFOCUS);
					SetActive(TRUE);
					SetSel(0, -1);
					Refresh();
					m_LFRow = nRow;
					return TRUE;
				}
				else if((nVal == nFind) && (nVal||nFind))
				{
					m_LFRow = nRow;
					return TRUE;
				}
			
		}
		
		return FALSE;
	}
}

void CGXCurrencyEdit::ReplaceSel(LPCTSTR pszReplaceText)
{
	if (IsActive())
	{
		CString str;
		ReplaceSelString(pszReplaceText, str);
		SetWindowText(str);
		SetModify(TRUE);
		OnModifyCell();
		
	}
	else
		CGXControl::ReplaceSel(pszReplaceText);
}

BOOL CGXCurrencyEdit::ReplaceAll(const GX_FR_STATE& find, ROWCOL nRow, ROWCOL nCol)
{
	BOOL bFound = FALSE, bNegative;
	LPCTSTR szValue = NULL;
	LPCTSTR szTemp = NULL;
	LPCTSTR pszFound = NULL;
	LPCTSTR szReplace ;//= find.strReplace;
	LPCTSTR szFind = find.strFindUpper;
	
	
	if (!m_bIgnoreFractions)
	{
		CString s, sTemp;

		int nStart = 0, nEnd = -1;


		CGXStyle* pStyle = NULL;

		// if the active cell contains the text, mark it and return TRUE
		// if not, do a find and return FALSE
		if (nRow == m_nRow && nCol == m_nCol && IsActive())
		{
			CEdit::GetSel(nStart, nEnd);
			GetWindowText(s);
		}
		else
		{
			// request a style object
			pStyle = Grid()->CreateStyle();

			Grid()->ComposeStyleRowCol(nRow, nCol, pStyle, FALSE);

			GetControlText(s, nRow, nCol, NULL, *pStyle);
		
			if (s == _T(""))
				s = _T("0");
		}


	
		TCHAR c;
		Format f;

		if (nRow == m_nRow && nCol == m_nCol && IsActive())
		{
			GetFormat(f);
			c = f.GetDecimalSeparator();
		}
		else
		{
			//Inactive cell...style has to be initialized
			ASSERT(pStyle);
			//Initialize from the style object with helper
			c = pStyle->GetUserAttribute(GX_IDS_UA_CURRENCYDEF)[4];
		}
		


		CString tem = find.strReplace;	
		if (_tcschr( szFind, c ) != NULL)
		{
			//Make sure that the text to replace with has the same number of fractional
			//digits or the results will be weird
			if (_tcschr( find.strReplace, c)==NULL)
					tem = (LPCTSTR)(find.strReplace+_T("."));
		}
		
		szReplace = tem;
	

		// Convert text in s to upper case if we are doing a case insensitive search
		sTemp = s;
		if (!find.bCase)
			sTemp.MakeUpper();
		szValue = s;
		szTemp = sTemp;

		nStart = max(0, nStart);

		int nReplace = (int)_tcslen(szReplace);
		int nFind = (int)_tcslen(szFind);

		// result text
		TCHAR szResult[1024];
		// QA: 31989 - #if Secure Code Cleanup.
		_tcsncpy(szResult, szValue, nStart);
		LPTSTR pszResult = szResult + nStart;

		// original text
		LPCTSTR pszValue = szValue + nStart;

		// text to compare (upper case if case insensitive search)
		LPCTSTR pszTemp  = szTemp + nStart;

		do
		{
			pszFound = _tcsstr(pszTemp, szFind);

			if (pszFound == NULL)
				// copy remaining after last match
				// QA: 31989 - #if Secure Code Cleanup.
				_tcscpy(pszResult, pszValue);
			else
			{
				bFound = TRUE;

				// copy text before match
				// QA: 31989 - #if Secure Code Cleanup.
				_tcsncpy(pszResult, pszValue, pszFound-pszTemp);
				pszResult += pszFound-pszTemp;

				// append replaced text
				// QA: 31989 - #if Secure Code Cleanup.
				_tcsncpy(pszResult, szReplace, nReplace);
				pszResult += nReplace;
				*pszResult = _T('\0');

				// increase pointers in original text (skip matching text)
				pszValue += pszFound-pszTemp+nFind;
				pszTemp = pszFound+nFind;

				// just to be sure ...
				ASSERT(pszValue == szValue + (pszTemp-szTemp));
			}
		}
		while (pszFound && *pszTemp);
	
		CString str;

		if (bFound)
		{
			//We have to parse the value before we  can set it
		
			//We have to setup the captive control exactly as the regular one would
			//look in order to retain the format
		
			if (nRow == m_nRow && nCol == m_nCol && IsActive())
			{
				Format f;
				GetFormat(f);
				m_CapCtrlWnd.SetFormat(f);
			}
			else
			{
				//Inactive cell...style has to be initialized
				ASSERT(pStyle);
				//Initialize from the style object with helper
				InitFromUserAttributes(&m_CapCtrlWnd, pStyle);
			}
		
			double d(0);
			if (m_CapCtrlWnd.m_pFormat->ParseValue(szResult, d, bNegative))
			{	
			
				m_CapCtrlWnd.m_pFormat->FormatValue(d, str, bNegative);
			}
			else
				bFound = FALSE;
		}

		if (pStyle)
		// free style object
		Grid()->RecycleStyle(pStyle);

		if (bFound)
			Grid()->SetValueRange(CGXRange(nRow, nCol), str, gxOverride);
		
	
		return bFound;
	}

	else
	{
		
		int nVal(0);
		int nFind = _ttoi(szFind);
		
		if (nRow == m_nRow && nCol == m_nCol && IsActive())
		{
			
			CString s;
			
			//Strip the monetary symbol if it's present
			Format f;
			GetFormat(f);
			
			LPCTSTR c = f.GetMonetarySymbol();
			
			
			CString pTrunc(szFind);
			
			if (_tcsstr(szFind, c)!=NULL || !_tcscmp(c, pTrunc.Left((int)_tcslen(c))))
				szFind = _tcsninc(szFind, _tcslen(c));

			
			//convert the find value to integer
			nFind = _ttoi(szFind);

			int nStart(0), nEnd(0);

			CEdit::GetSel(nStart, nEnd);
			GetWindowText(s);

			s.MakeUpper();


			
			//Strip the monetary char is it's present off the window text as well
			LPCTSTR sz = NULL;
			//we assume that the monetary symbol is at the beginning
			if (_tcsstr(s, c) !=NULL)
					sz = _tcsninc(s, _tcslen(c));
				else
					sz = s;
				

			nVal = _ttoi(sz);

			

			if ((nVal == nFind) /*&& (nVal||nFind)*/)
				{
					// Select the entire text
					SetSel(0, -1);
					ReplaceSel(find.strReplace);
					return TRUE;
				}
				
		}
		else
		{
			// request a style object
			CGXStyle* pStyle = Grid()->CreateStyle();

			Grid()->ComposeStyleRowCol(nRow, nCol, pStyle, FALSE);

			
			// to strip the monetary symbol if it's present
			TCHAR c = pStyle->GetUserAttribute(GX_IDS_UA_CURRENCYDEF)[2];
			
			
			CString s;
			LPCTSTR sz = NULL;
			if (GetControlText(s, nRow, nCol, NULL, *pStyle))
			{
				// Convert text to upper case if we are doing a case insensitive search
				if (!find.bCase)
					s.MakeUpper();
					
				if (_tcsstr(s,&c) !=NULL || s[0] == c)
					sz = _tcsinc(s);
				else
					sz = s;
				
				nVal = _ttoi(sz);
			}
			else
				nVal = 0;

			
			
			if (_tcsstr(szFind,&c)!=NULL || szFind[0] == c)
				szFind = _tcsinc(szFind);
		
			nFind = _ttoi(szFind);
			
			// free style object
			Grid()->RecycleStyle(pStyle);

		

				if ((nVal == nFind) /*&& (nVal||nFind)*/)
				{
					Grid()->SetValueRange(CGXRange(nRow, nCol), find.strReplace, gxOverride);
					return TRUE;
				}
				
		
	}
	return FALSE;	
}
}

BOOL CGXCurrencyEdit::GetSelectedText(CString& sWindowText)
{
	if (IsActive())
	{
		// Get selected text
		int nStartChar = 0,
			 nEndChar = -1;

		GetSel(nStartChar, nEndChar);
		GetWindowText(sWindowText);

		// if no text is selected use all text
		if (nEndChar == nStartChar)
			return FALSE;   // no text selected

		else
		{
			// if nEndChar is -1 get whole text
			int nLength = (nEndChar == -1) ? GetWindowTextLength() : nEndChar-nStartChar;

			// Copy text to strResult
			sWindowText = sWindowText.Mid(nStartChar, nLength);

			return TRUE;    // text selected
		}
	}
	else
	{
		// No caret visible. Get text which is displayed in the cell
		GetCurrentText(sWindowText);

		return FALSE;   // no text selected
	}
}

// Edit specific

int CGXCurrencyEdit::CalcTextPosUnderPt(CPoint point)
{
	// used to compute textposition after mouseclick

	NeedStyle();


	// return -1 if the value string is empty
	if (!GetModify() && m_pStyle->GetValueRef().IsEmpty())
		return -1;

	CRect rect = GetCellRect(m_nRow, m_nCol);

	CString s;
	GetWindowText(s);

	DWORD ntAlign = m_pStyle->GetHorizontalAlignment() | m_pStyle->GetVerticalAlignment();

	if (m_pStyle->GetWrapText())
		ntAlign |= DT_NOPREFIX | DT_WORDBREAK;
	else
		ntAlign |= DT_NOPREFIX | DT_SINGLELINE;

	CClientDC dc(GridWnd());

	CFont* pOldFont = Grid()->LoadFont(&dc, *m_pStyle);

	int nHitChar = GXGetMultiLineTextPosUnderPt(
		&dc, s, -1, rect,
		(UINT) ntAlign, point);

	if (pOldFont)
	{
		if ((pOldFont = dc.SelectObject(pOldFont)) != NULL)
			pOldFont->DeleteObject();
	}

	return nHitChar;
}

void CGXCurrencyEdit::OnKillFocus(CWnd* pNewWnd)
{
	CGXBCurrencyEdit::OnKillFocus(pNewWnd);
	CGXControl::OnKillFocus(pNewWnd);
}

UINT CGXCurrencyEdit::OnGetDlgCode()
{
	return CGXBCurrencyEdit::OnGetDlgCode() | DLGC_WANTTAB | DLGC_WANTARROWS | DLGC_WANTCHARS;
}

BOOL CGXCurrencyEdit::OnEraseBkgnd(CDC* pDC)
{
	// Nothing to do - will be handled in currency edit base class ...

	return TRUE;
	
	GX_UNUSED_ALWAYS(pDC);
}

LRESULT CGXCurrencyEdit::OnSetText(WPARAM wParam, LPARAM lParam)
{
	// If the no-parse flag is set, let the default prodedure
	// give us the return value, then invalidate the client area
	// to force a redraw
	
	if (!m_bParseOnSetText)
	{
		LRESULT lRet = Default();
		if (!m_bFromInit)
		{
			SetModify(TRUE);
			OnModifyCell();
		}
		QueueRedraw();
		return lRet;
	}

	// wParam = (not used)
	// lParam = pointer to new text

	LPCTSTR pcsz = (LPCTSTR)lParam;
	if (m_pFormat->ParseValue(pcsz, m_dValue, m_bNegative))
	{
		CString s;
		m_pFormat->FormatValue(m_dValue, s, m_bNegative);
		SetWindowTextNoParse(s);
		return TRUE;
	}

	wParam; // UNUSED
	return FALSE;
}

LRESULT CGXCurrencyEdit::OnCalcSetText(WPARAM wParam, LPARAM lParam)
{
	// If the no-parse flag is set, let the default prodedure
	// give us the return value, then invalidate the client area
	// to force a redraw

	if (CGXControl::IsReadOnly())
		return TRUE;

	if (!m_bParseOnSetText)
	{
		LRESULT lRet = Default();
		if (!m_bFromInit)
		{
			SetModify(TRUE);
			OnModifyCell();
		}
		QueueRedraw();
		return lRet;
	}

	// wParam = (not used)
	// lParam = pointer to new text

	LPCTSTR pcsz = (LPCTSTR)lParam;
	if (m_pFormat->ParseValue(pcsz, m_dValue, m_bNegative))
	{
		CString s;
		m_pFormat->FormatValue(m_dValue, s, m_bNegative);
		SetWindowTextNoParse(s);
		return TRUE;
	}

	wParam; // UNUSED
	return FALSE;
}

BOOL CGXCurrencyEdit::GetControlText(CString& strResult, ROWCOL nRow, ROWCOL nCol, LPCTSTR pszRawValue, const CGXStyle& style)
{
	nRow, nCol;

	ASSERT(m_CapCtrlWnd.m_hWnd);
	
	CString strParse;
	
	if (pszRawValue != NULL)
	{
		//strParse = pszRawValue;
		//See if the raw value is useable as is
		CGXCurrencyEdit::Format f;
		GetFormat(f);
		CString strValue(pszRawValue);
		int nPos = strValue.Find('.');
		if(nPos!=-1)
			strValue.SetAt(nPos,f.GetDecimalSeparator());
		if (OnSetText(0, (LPARAM)(LPCTSTR) strValue))
		{
			//Yes, it is return TRUE
			strResult = strValue;//pszRawValue;
			return TRUE;
		}
		else
			return FALSE;
	}
	else if (style.GetIncludeValue())
	{
		strParse = style.GetValueRef();
		if (strParse.IsEmpty())
			return FALSE;
	}
	else
	{
		strResult.Empty();
		return FALSE;
	}
	
	
	InitFromUserAttributes(&m_CapCtrlWnd, &style);
	//$
	CGXCurrencyEdit::Format f;
	m_CapCtrlWnd.GetFormat(f);
	int nPos = strParse.Find('.');
	if(nPos!=-1)
		strParse.SetAt(nPos,f.GetDecimalSeparator());
	
	m_CapCtrlWnd.OnSetText(0, (LPARAM) (LPCTSTR)strParse);
	
	m_CapCtrlWnd.GetWindowText(strResult);
	
	
	//	TRACE("GetControlText returns %s\n", strResult);
	
	return !strResult.IsEmpty();
}


// Add all the CGXCurrencyEdit specific user attributes
void CGXCurrencyEdit::AddUserAttributes(CGXStylesMap* pStylesMap)
{
	pStylesMap->AddUserAttribute(GX_IDS_UA_CURRENCYDEF, CGXStyle()
		.SetControl(GX_IDS_CTRL_MASKEDIT)
		.SetUserAttribute(GX_IDS_UA_INPUTMASK, _T("##AAAA#")));
	
	pStylesMap->AddUserAttribute(GX_IDS_UA_CURPOSFORMAT, CGXStyle()
		.SetControl(GX_IDS_CTRL_ZEROBASED_EX)
		.SetChoiceList(CGXResourceString(GX_IDS_CHOICE_CURPOSFORMAT)));
	pStylesMap->AddUserAttribute(GX_IDS_UA_CURNEGFORMAT, CGXStyle()
		.SetControl(GX_IDS_CTRL_ZEROBASED_EX)
		.SetChoiceList(CGXResourceString(GX_IDS_CHOICE_CURNEGFORMAT)));

	pStylesMap->AddUserAttribute(GX_IDS_UA_CURNUMDECIMALS);
	pStylesMap->AddUserAttribute(GX_IDS_UA_CURNUMFRACT);
	
	pStylesMap->AddUserAttribute(GX_IDS_UA_CURMON);
	pStylesMap->AddUserAttribute(GX_IDS_UA_CURSEP);
}


BOOL CGXCurrencyEdit::ConvertControlTextToValue(CString& strValue, ROWCOL nRow, ROWCOL nCol, const CGXStyle* pOldStyle)
{
	CGXStyle* pStyle = NULL;
	BOOL bSuccess = FALSE, bNegative;

	if (pOldStyle == NULL)
	{
		pStyle = Grid()->CreateStyle();
		Grid()->ComposeStyleRowCol(nRow, nCol, pStyle);
		pOldStyle = pStyle;
	}

	// allow only valid input
	{
		//Set the format of the captive control
		InitFromUserAttributes(&m_CapCtrlWnd, pOldStyle);
		Format f;
		double d;
		m_CapCtrlWnd.GetFormat(f);

		if (strValue.IsEmpty())
		{
			//change 1
			bSuccess = TRUE;
		}
		else if (f.ParseValue(strValue, d, bNegative))
		{
			//change 2 Store value as double. SetExpressionRowCol will
			//take care of this
			
			CString s;
			CString str = _T("%.");
			s.Format(_T("%d"),f.GetFractionalDigits());
			str+=s;
			d = bNegative ? -d : d;
			s.Format( str+_T("f"), d);
			
			strValue = s;
			bSuccess = TRUE;
		}
		
	}

	if (pStyle)
		Grid()->RecycleStyle(pStyle);

	return bSuccess;
}

void CGXCurrencyEdit::GetSortKey(ROWCOL nRow, ROWCOL nCol, const CGXSortInfo& sortInfo, const CGXStyle& style, CString& sKey)
{
	BOOL bNegative;
	// Unused:
	nCol, nRow, sortInfo;

	sKey = style.GetValueRef();
	if (sKey .IsEmpty())
		return;

	
	InitFromUserAttributes(&m_CapCtrlWnd, &style);
	Format f;
	double d;
	m_CapCtrlWnd.GetFormat(f);

	int nPos = sKey.Find('.');
	if(nPos!=-1)
		sKey.SetAt(nPos,f.GetDecimalSeparator());

	if (f.ParseValue(sKey, d, bNegative))
	{
		//CString s;
		CString str = _T("%.");
		sKey.Format(_T("%d"),f.GetFractionalDigits());
		str+=sKey;
		d= bNegative ? -d : d;
		sKey.Format( str+_T("f"), d);
		
		
	}
	
}


CWnd* CGXCurrencyEdit::GetWndPtr() const
{
	return (CWnd*) this;
}


BOOL CGXCurrencyEdit::CanFloatCell(ROWCOL, ROWCOL, const CGXStyle&, BOOL)
{
	// Currency edit doesn't support floating
	return FALSE;
}


BOOL CGXCurrencyEdit::OnGridSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	nFlags, nRepCnt;

	BOOL bProcessed = FALSE;
	switch (nChar)
	{
	case VK_DOWN:		
		if (OnStartEditing())
		{
			SetActive(TRUE);
			if (!IsInit())
				Init(m_nRow, m_nCol);
		}
		else
			break;
		Refresh();
		Grid()->RedrawRowCol(m_nRow, m_nCol);
		if(GetBitmap() != NULL)
			ShowCalculator();
		break;
	case VK_UP:
		SetFocus();
	}
	
	return bProcessed;
}

//This function is not currently used in this implementation
BOOL CGXCurrencyEdit::HitTestBtn(CPoint point, BOOL bClient) const
{
	if (m_bForceHitTrue)
		return TRUE;
	else
		return CGXBCurrencyEdit::HitTestBtn(point, bClient);
}


BOOL CGXCurrencyEdit::StoreStyle(ROWCOL nRow, ROWCOL nCol, const CGXStyle* pStyle, GXModifyType mt, int nType, const CGXStyle* pOldStyle)
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
			(pStyle->GetIncludeUserAttribute(GX_IDS_UA_CURRENCYDEF)
			|| pStyle->GetIncludeUserAttribute(GX_IDS_UA_CURPOSFORMAT)
			|| pStyle->GetIncludeUserAttribute(GX_IDS_UA_CURNEGFORMAT)
			|| pStyle->GetIncludeUserAttribute(GX_IDS_UA_CURNUMDECIMALS)
			|| pStyle->GetIncludeUserAttribute(GX_IDS_UA_CURNUMFRACT)
			))
		{
			InitFromUserAttributes(this, pStyle);
		}
	}

	return TRUE;
}

