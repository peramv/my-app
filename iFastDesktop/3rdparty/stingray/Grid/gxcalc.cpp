///////////////////////////////////////////////////////////////////////////////
// gxcalc.cpp : Calculator
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
// Portions of this code were copied from Objective Toolkit.

#define _OG_EXPORT_IMPL

#include "stdafx.h"
// Multi-monitor support
#include <multimon.h>
#include "grid\gxresrc.h"
#include "grid\gxcalc.h"

#include "grid\gxmsg.h"
#include <locale.h>

//FOUNDATION_GLOBAL_FUNC_API(HWND) RWGetSafeHwnd();

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// Handle macro for determining number of elements in an array
#define dimensionof(a) (sizeof(a)/sizeof(a[0]))


static const int nMaxSigFig  = 15;		// The no. of significant figures we
										// work to
static const int nMaxIntSize = 13;		// Maximum integer is 13 digits
static const int nDividerSpc = 2;		// Additional Vertical Gap around
										// divider

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CGXBCalculator
//
// Implements a simple calculator (window)
//
IMPLEMENT_DYNAMIC(CGXBCalculator, CWnd)

BEGIN_MESSAGE_MAP(CGXBCalculator, CWnd)
	ON_WM_PAINT()
	ON_WM_SYSCOLORCHANGE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_CANCELMODE()
	ON_WM_GETDLGCODE()
	ON_WM_CHAR()
	ON_WM_NCPAINT()
	ON_WM_NCCALCSIZE()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CGXBCalculator - Construction
//

CGXBCalculator::CGXBCalculator()
{
	m_nBtnWidth    =				// Width of a button
	m_nBtnHeight   =				// Height of a button
	m_nVIndent     =				// Indent of button matrix from top edge
	m_nHIndent     =				// Indent of button matrix from left edge
	m_nVSpace      =				// Vertical space between buttons
	m_nHSpace      =				// Horizontal space between buttons
	m_nCapture     =				// Index of button with capture
	m_nTotalDigits =				// Maximum number of displayable digits
	m_nState       = 0;				// State flags
	m_val          = 0.0;			// Current value
	m_bReplace     = FALSE;			// Next digit starts a new number
	m_lastOp       = OpNull;		// Last operator entered
	m_hEqualsBmp   = NULL;			// Handle of equals bitmap
	m_nDP          = nMaxSigFig;	// Max no. of decimal places

	m_panelRect.SetRectEmpty();		// Rectangle of LCD display panel
	m_strDisplay.Empty();			// Current display string

}

CGXBCalculator::~CGXBCalculator()
{
	if(m_hEqualsBmp)
	{
		::DeleteObject(m_hEqualsBmp);
		m_hEqualsBmp = NULL;
	}

	for(int i=0; i<m_btns.GetSize(); i++)
		delete m_btns[i];
	m_btns.RemoveAll();
}

BOOL CGXBCalculator::CreateEx(DWORD dwExStyle, DWORD dwStyle, int x, int y, 
							 CWnd* pParentWnd, UINT nID, 
							 CCreateContext* pContext)
{
	if (m_strDecSep.IsEmpty())
	{
		m_strDecSep	= LoadDecSeparator(); // Load decimal separator (virtual method)
	}

	GXGetSysData()->UpdateSysColors();

	ResetCalc();

	if(dwStyle & GX_CS_RAISEDEDGE)
	{
		// If we our going to use our own border style, ensure we ignore all
		// other border styles
#ifdef WIN32
		dwExStyle &= ~(WS_EX_CLIENTEDGE|WS_EX_STATICEDGE);
#endif
		dwStyle   &= ~WS_BORDER;
	}

	// Create the calculator button objects
	if(m_btns.GetSize() == 0)
		CreateBtns(pParentWnd);

	// Create LCD panel
	if(m_panelFont.m_hObject == NULL)
		CreatePanel(pParentWnd);

	// We need to calculator our size (so we can create the window rectangle
	// as the correct size)
	CSize sz = CalcLayout(dwStyle);

	// Allow for non-client space
	{
		CRect r;
		r.SetRectEmpty();
		::AdjustWindowRectEx(&r, dwStyle, FALSE, dwExStyle);

		sz.cx += r.Width();
		sz.cy += r.Height();

		if(dwStyle & GX_CS_RAISEDEDGE)
		{
			sz.cx += 4;
			sz.cy += 4;
		}
	}

	LPCTSTR lpszClassName = AfxRegisterWndClass(GetClassStyle(),
												GXGetSysData()->hcurArrow);

	if(!CWnd::CreateEx(dwExStyle,
					   lpszClassName,
					   NULL,
					   dwStyle,
					   x,
					   y,
					   sz.cx,
					   sz.cy,
					   pParentWnd->GetSafeHwnd(),
					   (HMENU)(SEC_UINT)nID,
#ifdef WIN32
					   (LPVOID) pContext))
#else 
					   (LPSTR) pContext))
#endif
	{
		return FALSE;
	}

	m_nState &= ~HasInitialValue;

	return TRUE;
}

BOOL CGXBCalculator::Create(DWORD dwStyle, int x, int y, CWnd* pParentWnd, 
						   UINT nID, CCreateContext* pContext)
{
	return CreateEx(0, dwStyle|WS_CHILD, x, y, pParentWnd, nID, pContext);
}


/////////////////////////////////////////////////////////////////////////////
// CGXBCalculator - Operations
//

//---------------------------------------------------------------------------
// CGXBCalculator::InvalidateBtn
//
// Invalidates the given button
//
void CGXBCalculator::InvalidateBtn(int nIndex, BOOL bErase /* = FALSE */)
{
	ASSERT_VALID(this);
	ASSERT(nIndex >= 0 && nIndex < m_btns.GetSize());

	InvalidateRect(m_btns[nIndex]->GetRect(), bErase);
}

//---------------------------------------------------------------------------
// CGXBCalculator::InvalidatePanel
//
// Invalidates the LCD display panel
//
void CGXBCalculator::InvalidatePanel(BOOL bErase /* = FALSE */)
{
	ASSERT_VALID(this);

	if(m_hWnd)
		InvalidateRect(m_panelRect, bErase);
}

//---------------------------------------------------------------------------
// CGXBCalculator::ResetCalc
//
// Resets the calculator back to a "zero" state
//
void CGXBCalculator::ResetCalc()
{
	ASSERT_VALID(this);

	if(!(m_nState & HasInitialValue) || m_hWnd)
	{
		// Only initialise if required
		m_val = 0.0;
		m_strDisplay.Empty();
	}

	m_nState   &= ~CalcError;
	m_bReplace  = TRUE;
	m_lastOp    = OpNull;

	if(m_hWnd)
		InvalidatePanel();
}

//---------------------------------------------------------------------------
// CGXBCalculator::SetValue
//
// Sets the currently displayed value
//
void CGXBCalculator::SetValue(double val)
{
	ASSERT_VALID(this);

	ResetCalc();
	m_val = val;

	if(m_hWnd == NULL)
		// We don't have a window yet. Creation of the window causes ResetCalc
		// to be called which will reset the calculator back to zero. To
		// avoid this, we set a state flag telling ResetCalc to preserve the
		// current value
		m_nState |= HasInitialValue;

	SetDisplayString();
}

//---------------------------------------------------------------------------
// CGXBCalculator::GetValue
//
// Returns the current calculator value. Note that if this is in the middle
// of an operation then it is unlikely to be the same as the current display
// value. You could force the end of the current calculation with
// HandleEvent(OpEquals).
//
double CGXBCalculator::GetValue() const
{
	ASSERT_VALID(this);

	return m_val;
}

//---------------------------------------------------------------------------
// CGXBCalculator::HitTest
//
// Returns the index of the button under the given point (relative to the
// calculators client area).
//
int CGXBCalculator::HitTest(CPoint point) const
{
	ASSERT_VALID(this);

	for(int i=0; i<m_btns.GetSize(); i++)
	{
		if(m_btns[i]->GetRect().PtInRect(point))
			return i;
	}

	return -1;
}

//---------------------------------------------------------------------------
// CGXBCalculator::SetDecimalPlaces
//
// Sets the maximum number of decimal places to display to. Note the
// calculator works to 15 significant places. Restricting the number of
// decimal places is a cause of inaccurate results.
//
void CGXBCalculator::SetDecimalPlaces(int nDP)
{
	ASSERT_VALID(this);

	if(m_hWnd)
		m_nDP = min(nDP, m_nTotalDigits);
	else
		m_nDP = nDP;
}

//---------------------------------------------------------------------------
// CGXBCalculator::GetDecimalPlaces
//
// Returns the current maximum number of decimal places.
//
int CGXBCalculator::GetDecimalPlaces() const
{
	ASSERT_VALID(this);

	return m_nDP;
}

//---------------------------------------------------------------------------
// CGXBCalculator::GetFormatDecimal
//
// Returns the decimal character used by scanf and printf.  The character
// that scanf/printf use is determined by the ANSI C Runtime call to 
// setlocale().  The default decimal character displayed on the calculator 
// is determined by the Win32 call to SetThreadLocale(), and can be different
// from the character used by scanf and printf.
//
TCHAR CGXBCalculator::GetFormatDecimal() {

	struct lconv* pLocale = localeconv();
	TCHAR cDecimal = *pLocale->decimal_point;
	
	return cDecimal;
}

/////////////////////////////////////////////////////////////////////////////
// CGXBCalculator overrides
//

//---------------------------------------------------------------------------
// CGXBCalculator::CreatePanel
//
// Creates the LCD panel (well it really initialises data associated with
// the panel).
//
BOOL CGXBCalculator::CreatePanel(CWnd* pParentWnd)
{
	// Create Font used by panel
	CFont* pFont = pParentWnd->GetFont();
	if(!pFont)
		pFont = CFont::FromHandle((HFONT) ::GetStockObject(SYSTEM_FONT));

	LOGFONT lf;
	pFont->GetObject(sizeof(lf), &lf);
	lf.lfWeight = FW_NORMAL;
	if(!m_panelFont.CreateFontIndirect(&lf))
		return FALSE;

	m_panelRect.SetRectEmpty();
	
	// Calculate height of panel
	{
		CWindowDC dc(NULL);
		CRect r;
		r.SetRectEmpty();
		CFont* pOldFont = dc.SelectObject(&m_panelFont);
		int cy = dc.DrawText(_T("T"), 1, &r, 
							 DT_CALCRECT|DT_EXTERNALLEADING|DT_RIGHT|DT_SINGLELINE);
		dc.SelectObject(pOldFont);

		m_panelRect.bottom = 4 + cy;
	}

	return TRUE;
}

//---------------------------------------------------------------------------
// CGXBCalculator::CreateBtns
//
// Initialises button dimensions, and fills the button array (m_btns) with
// button objects.
//
// Note that the m_btns array works left to right from top to bottom.
//
BOOL CGXBCalculator::CreateBtns(CWnd* pParentWnd)
{
	ASSERT(!m_strDecSep.IsEmpty());

	// Initialise dimensions
	m_nVIndent = 1;				// Indent from top/bottom
	m_nHIndent = 4;				// Indent from left/right
	m_nVSpace  = 1;				// Space between button columns
	m_nHSpace  = 0;				// Space between button rows

	// Create Font used by btn
	CFont* pFont = pParentWnd->GetFont();
	if(!pFont)
		pFont = CFont::FromHandle((HFONT) ::GetStockObject(SYSTEM_FONT));

	LOGFONT lf;
	pFont->GetObject(sizeof(lf), &lf);
	lf.lfWeight = FW_BOLD;
	if(!m_btnFont.CreateFontIndirect(&lf))
		return FALSE;

	// Calculate button size
	CSize sz;
	sz = CGXBConvertDBU(16, 14, (HFONT) m_btnFont.m_hObject);
	m_nBtnWidth  = sz.cx;
	m_nBtnHeight = sz.cy;

	// Create standard button attributes
	CGXBCalcBtn::Attrib blueTextBtn(0L, RGB(0, 0, 128), 
								   (HFONT) m_btnFont.m_hObject);
	CGXBCalcBtn::Attrib redTextBtn (0L, RGB(128, 0, 0), 
								   (HFONT) m_btnFont.m_hObject);
	CGXBCalcBtn* pBtn;

	// First row of buttons ......

		// Btn: Clear
		pBtn = new CGXBCalcBtn;
		pBtn->Initialise(blueTextBtn, OpC, _T("C"), 1, TRUE);
		m_btns.Add(pBtn);

		// Btn: Clear Error
		pBtn = new CGXBCalcBtn;
		pBtn->Initialise(blueTextBtn, OpCE, _T("CE"), _T('E'));
		m_btns.Add(pBtn);

		// Btn: BackSpace
		pBtn = new CGXBCalcBtn;
		pBtn->Initialise(blueTextBtn, OpBack, _T("<-"), (TCHAR) VK_BACK);
		pBtn->SetKeyDownAccel(VK_DELETE);
		m_btns.Add(pBtn);

		// Btn: Percentage
		pBtn = new CGXBCalcBtn;
		pBtn->Initialise(blueTextBtn, OpPercent, _T("%"));
		m_btns.Add(pBtn);

	// second row of buttons ......

		// Btn: Digit 7
		pBtn = new CGXBCalcBtn;
		pBtn->Initialise(redTextBtn, Op7, _T("7"), 1, TRUE);
		m_btns.Add(pBtn);

		// Btn: Digit 8
		pBtn = new CGXBCalcBtn;
		pBtn->Initialise(redTextBtn, Op8, _T("8"));
		m_btns.Add(pBtn);
		
		// Btn: Digit 9
		pBtn = new CGXBCalcBtn;
		pBtn->Initialise(redTextBtn, Op9, _T("9"));
		m_btns.Add(pBtn);

		// Btn: Divide
		pBtn = new CGXBCalcBtn;
		pBtn->Initialise(blueTextBtn, OpDivide, _T("/"));
		m_btns.Add(pBtn);

	// Third row of buttons ......

		// Btn: Digit 4
		pBtn = new CGXBCalcBtn;
		pBtn->Initialise(redTextBtn, Op4, _T("4"), 1, TRUE);
		m_btns.Add(pBtn);

		// Btn: Digit 5
		pBtn = new CGXBCalcBtn;
		pBtn->Initialise(redTextBtn, Op5, _T("5"));
		m_btns.Add(pBtn);

		// Btn: Digit 6
		pBtn = new CGXBCalcBtn;
		pBtn->Initialise(redTextBtn, Op6, _T("6"));
		m_btns.Add(pBtn);

		// Btn: Multiply
		pBtn = new CGXBCalcBtn;
		pBtn->Initialise(blueTextBtn, OpMultiply, _T("*"));
		m_btns.Add(pBtn);

	// Fourth row of buttons ......

		// Btn: Digit 1
		pBtn = new CGXBCalcBtn;
		pBtn->Initialise(redTextBtn, Op1, _T("1"), 1, TRUE);
		m_btns.Add(pBtn);

		// Btn: Digit 2
		pBtn = new CGXBCalcBtn;
		pBtn->Initialise(redTextBtn, Op2, _T("2"));
		m_btns.Add(pBtn);

		// Btn: Digit 3
		pBtn = new CGXBCalcBtn;
		pBtn->Initialise(redTextBtn, Op3, _T("3"));
		m_btns.Add(pBtn);

		// Btn: Minus
		pBtn = new CGXBCalcBtn;
		pBtn->Initialise(blueTextBtn, OpMinus, _T("-"));
		m_btns.Add(pBtn);

	// Fifth row of buttons ......

		// Btn: Digit 0
		pBtn = new CGXBCalcBtn;
		pBtn->Initialise(redTextBtn, Op0, _T("0"), 2, TRUE);
		m_btns.Add(pBtn);

		// Btn: Decimal Point
		pBtn = new CGXBCalcBtn;
		pBtn->Initialise(redTextBtn, OpDP,  m_strDecSep);
		m_btns.Add(pBtn);

		// Btn: Plus
		pBtn = new CGXBCalcBtn;
		pBtn->Initialise(blueTextBtn, OpPlus, _T("+"));
		m_btns.Add(pBtn);


	// Sixth row of buttons ......

		// Load bitmap for equals sign
		CBitmap bmp;
		if(GXLoadSysColorBitmap(bmp, MAKEINTRESOURCE(GX_IDB_CALCEQUALS)))
			m_hEqualsBmp = (HBITMAP) bmp.Detach();
		else
			m_hEqualsBmp = NULL;

		// Setup attributes for equals button
		CGXBCalcBtn::Attrib equalsBtn(0L, RGB(0, 0, 0), 
									 (HFONT) m_btnFont.m_hObject, 
									 &m_hEqualsBmp);

		// Create equals button
		CString strEnter;
		strEnter.LoadString(GX_IDS_CALCENTER);

		pBtn = new CGXBCalcBtn;
		pBtn->Initialise(equalsBtn, OpEquals, strEnter, _T('='), 4, TRUE);
		pBtn->SetKeyDownAccel(VK_RETURN);
		m_btns.Add(pBtn);

	// End of button creation

	return TRUE;
}

//---------------------------------------------------------------------------
// CGXBCalculator::HandleEvent
//
// Processes events caused by button presses, dispatching the event to an
// appropriate function to handle it.
//
BOOL CGXBCalculator::HandleEvent(CGXBCalcOp op)
{
	// Map button events onto functions
	struct
	{
		CGXBCalcOp op;
		BOOL (CGXBCalculator::*fn)(CGXBCalcOp op);
	}
	static const LookupTable[] =
	{
		{ Op0,        &CGXBCalculator::HandleDigit        },
		{ Op1,        &CGXBCalculator::HandleDigit        },
		{ Op2,        &CGXBCalculator::HandleDigit        },
		{ Op3,        &CGXBCalculator::HandleDigit        },
		{ Op4,        &CGXBCalculator::HandleDigit        },
		{ Op5,        &CGXBCalculator::HandleDigit        },
		{ Op6,        &CGXBCalculator::HandleDigit        },
		{ Op7,        &CGXBCalculator::HandleDigit        },
		{ Op8,        &CGXBCalculator::HandleDigit        },
		{ Op9,        &CGXBCalculator::HandleDigit        },
		{ OpDP,       &CGXBCalculator::HandleDecimalPoint },
		{ OpBack,     &CGXBCalculator::HandleBackspace    },
		{ OpPlus,     &CGXBCalculator::HandleOperator     },
		{ OpMinus,    &CGXBCalculator::HandleOperator     },
		{ OpDivide,   &CGXBCalculator::HandleOperator     },
		{ OpMultiply, &CGXBCalculator::HandleOperator     },
		{ OpEquals,   &CGXBCalculator::HandleOperator     },
		{ OpPercent,  &CGXBCalculator::HandleOperator     },
		{ OpC,        &CGXBCalculator::HandleClear        },
		{ OpCE,       &CGXBCalculator::HandleClearError   }
	};

	ASSERT_VALID(this);
	
	for(int i=0; i<dimensionof(LookupTable); i++)
	{
		if(LookupTable[i].op == op)
			// Dispatch the event
			return (this->*LookupTable[i].fn)(op);
	}
	
	// Event not found ......
	ASSERT(0);

	return FALSE;
}

// Virtual overrideable to load custom decimal separator. By default, loads
// from system resources.
CString CGXBCalculator::LoadDecSeparator() {
	CString strDecSep      = _T(".");		// Default decimal separator
	GetLocaleInfo(LOCALE_USER_DEFAULT		// System default decimal separator
		,LOCALE_SDECIMAL
		,strDecSep.GetBuffer(3)				// store in m_strDecSep
		,2);								// maximum Length = 1
	strDecSep.ReleaseBuffer();
	return strDecSep;
}

/////////////////////////////////////////////////////////////////////////////
// CGXBCalculator implementation
//

//---------------------------------------------------------------------------
// CGXBCalculator::CalcLayout
//
// By this point the m_btns array has been filled with buttons. These buttons
// are now layed out.
//
CSize CGXBCalculator::CalcLayout(DWORD dwStyle)
{
	CSize sz(0, 0);

	int x = m_nHIndent;
	int y = m_nVIndent;

	// Allow for divider
	if(dwStyle & GX_CS_DIVIDER)
		y += 2 /* Height of divider */ + (nDividerSpc * 2) + m_nVIndent;

	// Position panel
	m_panelRect.OffsetRect(-m_panelRect.left, -m_panelRect.top);	// Origin
	m_panelRect.OffsetRect(x, y);
	y += m_panelRect.Height() + m_nVSpace;
	
	// Position each button in turn
	for(int i=0; i<m_btns.GetSize(); i++)
	{
		CGXBCalcBtn& btn = *(m_btns[i]);

		// Offset button from last button
		if(btn.GetState() & CGXBCalcBtn::StartsRow)
		{
			if(i != 0)
			{
				// This button starts a new row.
				y += m_nBtnHeight + m_nVSpace;
				x = m_nHIndent;
			}
		}
		else
			x += m_nHSpace;

		// Position button
		int cx = m_nBtnWidth * btn.GetWidth();
		btn.SetRect(CRect(x, y, x + cx, y + m_nBtnHeight));

		// Move past button
		x += cx;

		sz.cx = max(sz.cx, x);
		sz.cy = max(sz.cy, y + m_nBtnHeight);
	}

	// Set panel width
	m_panelRect.right = sz.cx;
	SizePanel();

	sz.cx += m_nHIndent;
	sz.cy += m_nVIndent;

	return sz;
}

//---------------------------------------------------------------------------
// CGXBCalculator::SizePanel
//
// Calculate the displayable area of the panel.
//
void CGXBCalculator::SizePanel()
{
	ASSERT(!m_strDecSep.IsEmpty());

	int cx = m_panelRect.Width() - 4 /* Allows for borders */;
	
	HDC hDC = ::GetDC(NULL);
	HFONT hFontOld = (HFONT) ::SelectObject(hDC, m_panelFont.m_hObject);
	
	// Remove width of decimal point from total width
	SIZE sz;
	VERIFY(::GetTextExtentPoint(hDC, m_strDecSep, 1, &sz));
	cx -= sz.cx;

	// Now get width of a digit
	VERIFY(::GetTextExtentPoint(hDC, _T("0"), 1, &sz));
	m_nTotalDigits = cx / sz.cx;
	m_nTotalDigits--;				// Allows for a sign.

	m_nDP          = min(m_nTotalDigits, m_nDP);

	::SelectObject(hDC, hFontOld);
	::ReleaseDC(NULL, hDC);
}

//---------------------------------------------------------------------------
// CGXBCalculator::SetDisplayString
//
// Formats the number m_val into the display string buffer m_strDisplay.
//
void CGXBCalculator::SetDisplayString()
{
	ASSERT_VALID(this);

	if (m_strDecSep.IsEmpty())
	{
		m_strDecSep = LoadDecSeparator();
	}

	TCHAR buf[255];
	FormatNo(buf, m_nDP);

	// We need to validate some of the lengths
revalidate:
	int nIntLen, nFracLen, nLen, nMaxLen;
	LPTSTR ptr = buf;

	if(m_val < 0.0)
		ptr = _tcsinc(ptr);

	if(m_val > -1.0 && m_val < 1.0)
		// For values that have leading zero ("0.xxx") we don't want to count
		// leading zero as significant.
		nMaxLen = min(m_nTotalDigits, nMaxSigFig + 1);
	else
		nMaxLen = min(m_nTotalDigits, nMaxSigFig);

	nLen = lstrlen(buf);
	if((ptr = _tcschr(buf, m_strDecSep.GetAt(0))) != NULL)
	{
		nFracLen = lstrlen(_tcsinc(ptr));
		nIntLen  = nLen - nFracLen - 1;
	}
	else
	{
		nFracLen = 0;
		nIntLen  = nLen;
	}

	if(nIntLen > nMaxLen || nIntLen > nMaxIntSize)
	{
		// Number too large.
		m_nState |= CalcError;
		InvalidatePanel();
		return;
	}

	if((nIntLen + nFracLen) > nMaxLen)
	{
		// We have too many digits ... reduce size of fraction to accomodate
		int nDP = nMaxLen - nIntLen;
		ASSERT(nDP >= 0);
		FormatNo(buf, nDP);

		// The Integer part of the number could have been round to include an
		// additional digit ... ensure it hasn't
		goto revalidate;
	}

	m_strDisplay = buf;
}

//---------------------------------------------------------------------------
// CGXBCalculator::FormatNo
//
// Formats the number m_val into the given buffer to the given number of
// decimal places.
//
void CGXBCalculator::FormatNo(LPTSTR ptr, int nDP)
{
	ASSERT_VALID(this);
	ASSERT(ptr != NULL);
	ASSERT(nDP >= 0 && nDP <= nMaxSigFig);
	ASSERT(!m_strDecSep.IsEmpty());

	TCHAR fmt[20];
	TCHAR dec;

	// QA: 31989 - #if Secure Code Cleanup.
	_stprintf(fmt, _T("%%.%dlf"), nDP);
	_stprintf(ptr, fmt, m_val);

	// determine the decimal character being used by printf
	dec = GetFormatDecimal();

	// Strip trailing zeros from fraction
	if((ptr = _tcschr(ptr, dec)) != NULL)
	{
		LPTSTR lpszLast = NULL;

		// replace the printf dec char with current decimal
		// QA: 31989 - #if Secure Code Cleanup.
		_tcsncset(ptr, m_strDecSep.GetAt(0), 1);

		while(*ptr != 0)
		{
			if(*ptr == _T('0'))
			{
				if(lpszLast == NULL)
					lpszLast = ptr;
			}
			else
				lpszLast = NULL;

			ptr = _tcsinc(ptr);
		}

		if(lpszLast != NULL)
			*lpszLast = 0;
	}
}

//---------------------------------------------------------------------------
// CGXBCalculator::PressBtn
//
// Presses the button at the given index.
//
void CGXBCalculator::PressBtn(int nIndex)
{
	ASSERT_VALID(this);
	ASSERT(nIndex >= 0 && nIndex < m_btns.GetSize());

	// We show the button has been pressed
	m_btns[nIndex]->SetState(m_btns[nIndex]->GetState() | CGXBCalcBtn::Down);
	InvalidateBtn(nIndex);
	UpdateWindow();

	// Action the key press
	HandleEvent(m_btns[nIndex]->GetOp());

	// And release the button
	m_btns[nIndex]->SetState(m_btns[nIndex]->GetState() ^ CGXBCalcBtn::Down);
	InvalidateBtn(nIndex);
	UpdateWindow();
}

//---------------------------------------------------------------------------
// CGXBCalculator::GetClassStyle
//
// Returns the style that the window class "will" be registered with.
//
UINT CGXBCalculator::GetClassStyle() const
{
	return 0;
}

//---------------------------------------------------------------------------
// CGXBCalculator::Draw
//
// Draws the calculator!
//
void CGXBCalculator::Draw(CDC& dc)
{
	ASSERT_VALID(this);
	ASSERT_VALID(&dc);

	// Start by filling the background
	CRect client;
	GetClientRect(&client);
	GXFillSolidRect1(&dc, &client, GXGetSysData()->clrBtnFace);

	if(GetStyle() & GX_CS_DIVIDER)
	{
		CRect r;
		r.left = client.left + 1;
		r.right = client.right - 1;
		r.top  = client.top + m_nVIndent + nDividerSpc;
		r.bottom = r.top + 2;

		GXDraw3dRect1(&dc, &r, GXGetSysData()->clrBtnHilite, GXGetSysData()->clrBtnShadow);
	}

	// Draw the panel
	if(dc.RectVisible(m_panelRect))
		DrawPanel(dc);

	// Draw the buttons
	for(int i=0; i<m_btns.GetSize(); i++)
	{
		if(dc.RectVisible(m_btns[i]->GetRect()))
			m_btns[i]->Draw(dc);
	}
}

//---------------------------------------------------------------------------
// CGXBCalculator::DrawPanel
//
// Draws the LCD display panel.
//
void CGXBCalculator::DrawPanel(CDC& dc)
{
	ASSERT_VALID(this);
	ASSERT_VALID(&dc);
	ASSERT(!m_strDecSep.IsEmpty());

	HTHEME	lhTheme = NULL;
	HRESULT	hr = 0;

	// Calling dc.GetWindow() will return an invalid handle. 
	// Instead call AfxGetMainWnd()->GetSafeHwnd().
	if (RWIsAppThemed() && RWIsThemeActive())
	{
		lhTheme = RWOpenThemeData (RWGetSafeHwnd(), L"Edit");
	}

	// We draw inset borders.
	CRect r = m_panelRect;

	if( lhTheme )
	{
		hr = RWDrawThemeBackground( lhTheme, dc.GetSafeHdc(), EP_EDITTEXT, ETS_READONLY, &r, 0 );
		r.InflateRect(-2,-2);
	}
	else
	{
		GXDraw3dRect1(&dc, r, GXGetSysData()->clrBtnShadow, GXGetSysData()->clrBtnHilite);
		r.InflateRect(-1, -1);
		GXDraw3dRect1(&dc, r, GXGetSysData()->clrWindowFrame, GXGetSysData()->clrBtnFace);
		r.InflateRect(-1, -1);
	}

	CString temp;
	
	// Determine what should be displayed
	if(m_nState & CalcError)
		// The calculator is in error.
		temp.LoadString(GX_IDS_CALCERROR);
	else
	{
		temp = m_strDisplay;
		if(temp.IsEmpty())
		{
			// No current display string, so display zero.
			temp = _T("0");
			temp += m_strDecSep;
		}
		else if(temp.Find(m_strDecSep) == -1)
			// We always display a decimal place.
			temp += m_strDecSep;
	}

	// and display it
	CFont* pOldFont = dc.SelectObject(&m_panelFont);
	if( lhTheme )
	{
		dc.SetBkMode( TRANSPARENT );
	}

	dc.DrawText(temp, temp.GetLength(), r, 
				DT_SINGLELINE|DT_RIGHT|DT_VCENTER|DT_NOPREFIX|DT_EXTERNALLEADING);
	dc.SelectObject(pOldFont);

	if( lhTheme )
		RWCloseThemeData( lhTheme );
}


/////////////////////////////////////////////////////////////////////////////
// CGXBCalculator Calculator function handlers
//

//---------------------------------------------------------------------------
// CGXBCalculator::HandleDigit
//
// Handles the input of a numeric digit
//
BOOL CGXBCalculator::HandleDigit(CGXBCalcOp op)
{
	ASSERT_VALID(this);
	ASSERT(!m_strDecSep.IsEmpty());

	if(m_nState & CalcError)
	{
		// When in error we do nothing!
		MessageBeep((UINT) -1);
		return FALSE;
	}

	// Get the character code
	TCHAR c = (TCHAR)(_T('0') + (op - Op0));

	if(m_bReplace)
	{
		// The new digit is to replace the current display string
		m_strDisplay.Empty();
		m_bReplace = FALSE;
	}

	// We ignore the case where leading zeros are entered
	if(!(m_strDisplay.IsEmpty() && op == Op0))
	{
		// Make sure we are not over-running any preset lengths
		LPCTSTR ptr = m_strDisplay;
		if(*ptr == _T('-'))
			// Move past sign - we don't count this
			ptr = _tcsinc(ptr);
		
		int nMaxLen;
		if(*ptr == _T('0'))
			// For values that have leading zero ("0.xxx") we don't want to count
			// leading zero as significant.
			nMaxLen = min(m_nTotalDigits, nMaxSigFig + 1);
		else
			nMaxLen = min(m_nTotalDigits, nMaxSigFig);

		int nLen = lstrlen(ptr);
		int nFracLen = 0;
		ptr = _tcschr(ptr,  m_strDecSep.GetAt(0));
		BOOL bHasDP = FALSE;
		if(ptr)
		{
			bHasDP = TRUE;
			ptr = _tcsinc(ptr);
			nFracLen = lstrlen(ptr);
			nLen -= nFracLen + 1;
		}

		// Validate lengths
		if(nFracLen >= m_nDP ||							// No. of DPs
		   (bHasDP == FALSE && nLen >= nMaxIntSize) ||	// Integer size
		   (nLen + nFracLen) >= nMaxLen)				// Total width
			// Adding digit would exceed a max. length.
			MessageBeep((UINT) -1);
		else
			// This character is allowed, so add it to the display string
			m_strDisplay += c;
	}

	InvalidatePanel();

	return TRUE;
}

//---------------------------------------------------------------------------
// CGXBCalculator::HandleDecimalPoint
//
// Handles the input of a decimal point
//
BOOL CGXBCalculator::HandleDecimalPoint(CGXBCalcOp /* op */)
{
	ASSERT_VALID(this);
	ASSERT(!m_strDecSep.IsEmpty());

	if(m_nState & CalcError)
	{
		// When in error we do nothing!
		MessageBeep((UINT) -1);
		return FALSE;
	}

	if(m_bReplace)
	{
		// We replace the current display string
		m_strDisplay.Empty();
		m_bReplace = FALSE;
	}

	if(m_strDisplay.Find(m_strDecSep) != -1)
		// Can't have two decimal points
		return FALSE;

	if(m_strDisplay.IsEmpty())
	{
		// Nothing entered yet so we become zero point.
		m_strDisplay += _T('0');
		m_strDisplay += m_strDecSep;
	}
	else
		m_strDisplay += m_strDecSep;

	InvalidatePanel();

	return TRUE;
}

//---------------------------------------------------------------------------
// CGXBCalculator::HandleBackspace
//
// Deletes the last character inpiut
//
BOOL CGXBCalculator::HandleBackspace(CGXBCalcOp /* op */)
{
	ASSERT_VALID(this);

	if(m_nState & CalcError)
	{
		// When in error we do nothing!
		MessageBeep((UINT) -1);
		return FALSE;
	}

	if(m_bReplace || m_strDisplay.IsEmpty())
		// Nothing to delete
		return FALSE;

	if(m_strDisplay.GetLength() == 1)
		// We have deleted the last character
		m_strDisplay.Empty();
	else
		// Remove the right most character
		m_strDisplay = m_strDisplay.Left(m_strDisplay.GetLength()-1);

	InvalidatePanel();

	return TRUE;
}

//---------------------------------------------------------------------------
// CGXBCalculator::HandleOperator
//
// Handles the input of an operator
//
BOOL CGXBCalculator::HandleOperator(CGXBCalcOp op)
{
	ASSERT_VALID(this);

	if(m_nState & CalcError)
	{
		// When in error we do nothing!
		MessageBeep((UINT) -1);
		return FALSE;
	}

	double val = 0.0;
	if(!m_strDisplay.IsEmpty())
	{
		TCHAR dec;
		LPTSTR szDisplay = NULL;
		LPTSTR szTemp    = NULL;
		
		// determine the decimal character being used by scanf/printf
		dec = GetFormatDecimal();

		// replace the displayed decimal with the one used by scanf
		// if it is different
		if (dec != m_strDecSep.GetAt(0))
		{
			szDisplay = m_strDisplay.GetBuffer(3);
			if((szTemp = _tcschr(szDisplay, m_strDecSep.GetAt(0))) != NULL)
			{
				// QA: 31989 - #if Secure Code Cleanup.
				_tcsncset(szTemp, dec, 1);
				m_strDisplay.ReleaseBuffer();
			}
		}

		// Extract the current value from the display string
		// QA: 31989 - #if Secure Code Cleanup.
		if(_stscanf(m_strDisplay, _T("%lf"), &val) != 1)
		{
			ASSERT(0);
			return FALSE;
		}
	}

	if(op == OpPercent)
	{
		// Percentage we handle differently. These are actioned as a 
		// percentage of last value entered (operator must have
		// been '+' or '/').
		if(m_lastOp == OpMultiply || m_lastOp == OpDivide)
			val = (m_val * val) / 100.0;
		else
			val = 0.0;

		op = OpNull;
	}
	else if(m_lastOp != OpNull)
	{
		// Action the operator
		switch(m_lastOp)
		{
		case OpPlus:
			val = m_val + val;
			break;

		case OpMinus:
			val = m_val - val;
			break;

		case OpDivide:
			if(val == 0.0)
				// Divide by zero error
				m_nState |= CalcError;
			else
				val = m_val / val;
			break;

		case OpMultiply:
			val = m_val * val;
			break;

		default:
			ASSERT(0);
			return FALSE;
		}
	}

	if(!(m_nState & CalcError))
	{
		// Calculation was successful. 
		m_val = val;				// New value
		m_bReplace = TRUE;			// Next char. replaces current displayed 
									// value
		m_lastOp = op;				// Store the operator to be actioned on 
									// receipt of the next operator.
		if(m_lastOp == OpEquals)	
			m_lastOp = OpNull;		// We don't store '=' since this is the
									// end of the transaction.

		SetDisplayString();
	}

	InvalidatePanel();

	return TRUE;
}

//---------------------------------------------------------------------------
// CGXBCalculator::HandleClear
//
// Resets the state of the calculator
//
BOOL CGXBCalculator::HandleClear(CGXBCalcOp /* op */)
{
	ASSERT_VALID(this);

	ResetCalc();

	return TRUE;
}

//---------------------------------------------------------------------------
// CGXBCalculator::HandleClearError
//
// Clears the current transaction (resets display to zero)
//
BOOL CGXBCalculator::HandleClearError(CGXBCalcOp /* op */)
{
	ASSERT_VALID(this);

	if(m_nState & CalcError)
		// We're in error, so reset.
		HandleClear(OpC);
	else
	{
		m_strDisplay.Empty();
		m_bReplace = TRUE;

		InvalidatePanel();
	}

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CGXBCalculator message handlers
//

void CGXBCalculator::OnPaint() 
{
	CPaintDC paintDC(this); // device context for painting

	CRect clientRect;
	GetClientRect(&clientRect);

	// Attempt to create an off-screen DC to draw to.
	CDC memDC;
	CBitmap bmp;
	if(memDC.CreateCompatibleDC(&paintDC) == FALSE ||
	   bmp.CreateCompatibleBitmap(&paintDC, clientRect.Width(), 
								  clientRect.Height()) == FALSE)
	{
		// Failed to create it, so draw directly to the screen
		Draw(paintDC);
	}
	else
	{
		CBitmap* pOldBmp = memDC.SelectObject(&bmp);

		CRect clipRect;
		paintDC.GetClipBox(clipRect);

		// Set the clipping region for the off-screen DC
		CRgn clipRgn;
		clipRgn.CreateRectRgn(clipRect.left, clipRect.top, clipRect.right, 
							  clipRect.bottom);
		memDC.SelectClipRgn(&clipRgn);
		
		// and draw to the off-screen DC
		Draw(memDC);

		// Copy the results to the screen DC. 
		paintDC.BitBlt(clipRect.left, clipRect.top, clipRect.Width(), 
					   clipRect.Height(), &memDC, clipRect.left, 
					   clipRect.top, SRCCOPY);

		memDC.SelectObject(pOldBmp);
	}
}

void CGXBCalculator::OnSysColorChange() 
{
	// System color change, so reset my current colors and reload any bitmaps.
	GXGetSysData()->UpdateSysColors();

	if(m_hEqualsBmp)
	{
		::DeleteObject(m_hEqualsBmp);
		CBitmap bmp;
		if(GXLoadSysColorBitmap(bmp, MAKEINTRESOURCE(GX_IDB_CALCEQUALS)))
			m_hEqualsBmp = (HBITMAP) bmp.Detach();
		else
			m_hEqualsBmp = NULL;
	}

	CWnd::OnSysColorChange();
}

void CGXBCalculator::OnNcPaint() 
{
	if(GetStyle() & GX_CS_RAISEDEDGE)
	{
		// Handle drawing my own border style.
		CDC* pDC = CDC::FromHandle(::GetDCEx(m_hWnd, NULL, 
											 DCX_WINDOW|DCX_CACHE));

		CRect rect;
		GetWindowRect(&rect);
		rect.OffsetRect(-rect.left, -rect.top);

		GXDraw3dRect1(pDC, rect, GXGetSysData()->clr3DLight, GXGetSysData()->clr3DDkShadow);
		rect.InflateRect(-1, -1);
		GXDraw3dRect1(pDC, rect, GXGetSysData()->clrBtnHilite, GXGetSysData()->clrBtnShadow);

		ReleaseDC(pDC);
	}
	else
		CWnd::OnNcPaint();
}

void CGXBCalculator::OnNcCalcSize(BOOL bCalcValidRects, 
								 NCCALCSIZE_PARAMS FAR* lpncsp) 
{
	if(GetStyle() & GX_CS_RAISEDEDGE)
	{
		// Decrease rectangle to allow for my own border
		if(lpncsp)
			::InflateRect(&lpncsp->rgrc[0], -2, -2);
	}
	else
		CWnd::OnNcCalcSize(bCalcValidRects, lpncsp);
}

void CGXBCalculator::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if(GetFocus() != this)
	{
		CRect rect;
		GetClientRect(&rect);
		if(rect.PtInRect(point))
			// I have been clicked, so I want focus
			SetFocus();
		else
			return;
	}

	// Determine button hit occured on.
	int nIndex = HitTest(point);
	if(nIndex != -1)
	{
		ASSERT(!(m_nState & Capture));

		// Change the button to down, and set capture so we can tell when it
		// has been released.
		m_nState |= Capture;
		m_nCapture = nIndex;
		SetCapture();
		m_btns[nIndex]->SetState(m_btns[nIndex]->GetState() | CGXBCalcBtn::Down);
		InvalidateBtn(nIndex);
		UpdateWindow();
	}
	else
		CWnd::OnLButtonDown(nFlags, point);
}

void CGXBCalculator::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if(m_nState & Capture)
	{
		// We did have a button down ... reset my state.
		ReleaseCapture();
		m_nState ^= Capture;

		int nState = m_btns[m_nCapture]->GetState();
		if(nState & CGXBCalcBtn::Down)
		{
			// Change button to up.
			m_btns[m_nCapture]->SetState(nState ^ CGXBCalcBtn::Down);
			InvalidateBtn(m_nCapture);
		}

		if(HitTest(point) == m_nCapture)
		{
			// Release occured over button, so fire event
			HandleEvent(m_btns[m_nCapture]->GetOp());
		}

		if(GetSafeHwnd())
			UpdateWindow();
	}
	else
		CWnd::OnLButtonUp(nFlags, point);
}

void CGXBCalculator::OnMouseMove(UINT nFlags, CPoint point) 
{
	if(m_nState & Capture)
	{
		// We currently are tracking a button press. See if we have changed
		// state (mouse dragged in/out of button).
		int nIndex = HitTest(point);
		int nState = m_btns[m_nCapture]->GetState();
		if((nIndex == m_nCapture && !(nState & CGXBCalcBtn::Down)) ||
		   (nIndex != m_nCapture && (nState & CGXBCalcBtn::Down)))
		{
			// Toggle state
			m_btns[m_nCapture]->SetState(nState ^ CGXBCalcBtn::Down);
			InvalidateBtn(m_nCapture);
			UpdateWindow();
		}
	}
	else
	{
		CWnd::OnMouseMove(nFlags, point);

		int		nIndex;
		bool	needUpdate = false;

		for( nIndex = 0; nIndex < m_btns.GetSize(); nIndex++)
		{
			int iState = m_btns[nIndex]->GetState();
			if( iState & CGXBCalcBtn::Hot )
			{
				m_btns[nIndex]->SetState( iState & (~CGXBCalcBtn::Hot) );
				InvalidateBtn(nIndex);
				needUpdate = true;
			}

		}

		nIndex = HitTest( point );
		if( nIndex >= 0 )
		{
			m_btns[nIndex]->SetState(m_btns[nIndex]->GetState() | CGXBCalcBtn::Hot);
			InvalidateBtn(nIndex);
			needUpdate = true;

			TRACKMOUSEEVENT eventTrack;

			memset( &eventTrack, 0x00, sizeof( eventTrack ) );
			
			eventTrack.cbSize = sizeof( eventTrack );
			eventTrack.dwFlags = TME_LEAVE;
			eventTrack.hwndTrack = m_hWnd;
			eventTrack.dwHoverTime = HOVER_DEFAULT;

			RWTrackMouseEvent( &eventTrack );
		}

		if( needUpdate )
			UpdateWindow();
	}
}

void CGXBCalculator::OnCancelMode() 
{
	if(m_nState & Capture)
	{
		// We were tracking a button press ... reset state
		ReleaseCapture();
		m_nState ^= Capture;

		int nState = m_btns[m_nCapture]->GetState();
		if(nState & CGXBCalcBtn::Down)
		{
			// Button was down, draw it up.
			m_btns[m_nCapture]->SetState(nState ^ CGXBCalcBtn::Down);
			if( nState & CGXBCalcBtn::Hot )
				m_btns[m_nCapture]->SetState( nState & (~CGXBCalcBtn::Hot) );
			InvalidateBtn(m_nCapture);
		}
	}

	CWnd::OnCancelMode();
}

UINT CGXBCalculator::OnGetDlgCode() 
{
	// We want to receive all keyboard input.
	return DLGC_WANTMESSAGE|DLGC_WANTCHARS;
}

void CGXBCalculator::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	TCHAR c[3];

	// Handle case of receiving multi-byte character
#ifdef WIN32
	if(m_nState & HaveLead)
	{
		m_nState ^= HaveLead;
		c[0] = m_cLeadByte;
		c[1] = TCHAR(nChar);
		c[2] = TCHAR(NULL);
	}
	else if(_istlead(nChar))
	{
		m_nState |= HaveLead;
		m_cLeadByte = TCHAR(nChar);
		return;
	}
	else
#endif
	{
		c[0] = TCHAR(nChar);
		c[1] = TCHAR(NULL);
	}

	// We always match againt lower case (makes life easier)
#ifdef WIN32
	::CharLower(c);
#else 
	::AnsiLower(c);
#endif

	for(int i=0; i<m_btns.GetSize(); i++)
	{
		if(m_btns[i]->IsAccelerator(c))
		{
			// The char. acts as an accelerator for this button. Press it ...
			PressBtn(i);
			return;
		}
	}

	CWnd::OnChar(nChar, nRepCnt, nFlags);
}

void CGXBCalculator::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// By requesting all chars in OnGetDlgCode, we also receive the tab key.
	// We want our parent to handle this, so we pass it on.
	if(nChar == VK_TAB && !IsKindOf(RUNTIME_CLASS(CGXBPopupCalculator)))
	{
		BOOL bShift = (GetKeyState(VK_SHIFT) & 0x8000) ? TRUE : FALSE;
		CWnd* pParentWnd = GetParent();
		if(pParentWnd)
			pParentWnd->PostMessage(WM_NEXTDLGCTL, (WPARAM) bShift, 
									(LPARAM) FALSE);

		return;
	}

	for(int i=0; i<m_btns.GetSize(); i++)
	{
		if(m_btns[i]->IsKeyDownAccelerator(nChar))
		{
			// This WM_KEYDOWN char acts as an accelerlator for this button.
			// Press it ....
			PressBtn(i);
			return;
		}
	}

	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}


#ifdef _DEBUG
void CGXBCalculator::Dump(CDumpContext& dc) const
{
	CWnd::Dump(dc);

	dc << _T("m_val          = ") << m_val << _T("\n");
	dc << _T("m_nState       = ") << m_nState << _T("\n");
	dc << _T("m_lastOp       = ") << (UINT) m_lastOp << _T("\n");
	dc << _T("m_strDisplay   = ") << m_strDisplay << _T("\n");
	dc << _T("m_nDP          = ") << m_nDP << _T("\n");
	dc << _T("m_nTotalDigits = ") << m_nTotalDigits << _T("\n");
}

void CGXBCalculator::AssertValid() const
{
	CWnd::AssertValid();

	if(m_hWnd != NULL)
	{
		ASSERT(m_btns.GetSize());
		ASSERT(m_nCapture >= 0 && m_nCapture < m_btns.GetSize());
	}
}
#endif

BOOL CGXBCalculator::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	if( message == WM_MOUSELEAVE )
	{
		int		nIndex;
		bool	needUpdate = false;

		for( nIndex = 0; nIndex < m_btns.GetSize(); nIndex++)
		{
			int iState = m_btns[nIndex]->GetState();
			if( iState & CGXBCalcBtn::Hot )
			{
				m_btns[nIndex]->SetState( iState & (~CGXBCalcBtn::Hot) );
				InvalidateBtn(nIndex);
				needUpdate = true;
			}
		}

		if( needUpdate )
			UpdateWindow();
	}

	return CWnd::OnWndMsg( message, wParam, lParam, pResult );
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//  CGXBPopupCalculator window
//
//  Implements a popup variation of CGXBCalculator
//

BEGIN_MESSAGE_MAP(CGXBPopupCalculator, CGXBCalculator)
	ON_WM_KILLFOCUS()
	ON_WM_KEYDOWN()
	ON_WM_SYSKEYDOWN()
END_MESSAGE_MAP()

IMPLEMENT_DYNAMIC(CGXBPopupCalculator, CGXBCalculator)


/////////////////////////////////////////////////////////////////////////////
// CGXBPopupCalculator construction
//

CGXBPopupCalculator::CGXBPopupCalculator()
{
	m_bAutoDelete = FALSE;
}

CGXBPopupCalculator::~CGXBPopupCalculator()
{
}

BOOL CGXBPopupCalculator::Create(DWORD dwStyle, const RECT& ctrlRect, 
								CWnd* pParentWnd, CCreateContext* pContext)
{
	return CreateEx(0, dwStyle, ctrlRect, pParentWnd, pContext);
}

BOOL CGXBPopupCalculator::CreateEx(DWORD dwExStyle, DWORD dwStyle, 
								  const RECT& ctrlRect, CWnd* pParentWnd, 
								  CCreateContext* pContext)
{
	if (m_strDecSep.IsEmpty())
	{
		m_strDecSep	= LoadDecSeparator(); // Load decimal separator (virtual method)
	}

	if(dwStyle & GX_CS_RAISEDEDGE)
	{
		// If we our going to use our own border style, ensure we ignore all
		// other border styles
#ifdef WIN32
		dwExStyle &= ~(WS_EX_CLIENTEDGE|WS_EX_STATICEDGE);
#endif
		dwStyle   &= ~WS_BORDER;
	}

	// We need to calculate the size of the calculator to determine where we 
	// will place it. This duplicates some of what is done in 
	// CGXBCalculator::Create ... such is life!

	// Create the calculator button objects
	if(m_btns.GetSize() == 0)
		CreateBtns(pParentWnd);

	// Create LCD panel
	if(m_panelFont.m_hObject == NULL)
		CreatePanel(pParentWnd);

	// We need to calculator our size (so we can create the window rectangle
	// as the correct size)
	CSize sz = CalcLayout(dwStyle);

	// Allow for non-client space
	{
		CRect r;
		r.SetRectEmpty();
		::AdjustWindowRectEx(&r, dwStyle, FALSE, dwExStyle);

		sz.cx += r.Width();
		sz.cy += r.Height();

		if(dwStyle & GX_CS_RAISEDEDGE)
		{
			sz.cx += 4;
			sz.cy += 4;
		}
	}

	// Determine the working screen area for proper placement
	CRect rectWorkArea;

#ifdef WIN32
	// Multi-monitor support
	HMONITOR hMonitor = MonitorFromPoint(CPoint(ctrlRect.left,ctrlRect.top), MONITOR_DEFAULTTONEAREST);
	ASSERT(hMonitor != NULL);
	MONITORINFO monitorInfo = { sizeof(MONITORINFO) };
	VERIFY(GetMonitorInfo(hMonitor, &monitorInfo));
	rectWorkArea = monitorInfo.rcWork;
#else 
	int cxScreen = ::GetSystemMetrics(SM_CXSCREEN);
	int cyScreen = ::GetSystemMetrics(SM_CYSCREEN);
	
	rectWorkArea.SetRect(0,0,cxScreen,cyScreen);
#endif

	int x, y;

	// Position below the ctrl if possible (otherwise above)
	if((ctrlRect.bottom + sz.cy) >= rectWorkArea.bottom)
		y = ctrlRect.top - sz.cy;
	else
		y = ctrlRect.bottom;

	// Align with left edge of ctrl (if space) otherwise right align
	if((ctrlRect.left + sz.cx) >= rectWorkArea.right)
		x = ctrlRect.right - sz.cx;
	else
		x = ctrlRect.left;

	if(CGXBCalculator::CreateEx(dwExStyle, dwStyle | WS_POPUP, x, y, 
							   pParentWnd, NULL, pContext))
	{
		SetFocus();
		return TRUE;
	}

	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CGXBPopupCalculator Overrides
//

BOOL CGXBPopupCalculator::HandleEvent(CGXBCalcOp op)
{
	BOOL bRes = CGXBCalculator::HandleEvent(op);
	if(op == OpEquals && (GetStyle() & GX_PCS_DESTROY_ON_EQUALS))
	{
		Notify();

		// Since we are down several layers of function, and calling 
		// WM_DESTROY causes us to be deleted, we post a WM_CLOSE, to
		// destroy us at some later date.
		PostMessage(WM_CLOSE);
	}

	return bRes;
}

void CGXBPopupCalculator::Notify()
{
	// Tell our owner (if we have one) about the new display string
	if(m_hWndOwner && ::IsWindow(m_hWndOwner) && !(m_nState & CalcError))
	{
		::SendMessage(m_hWndOwner, WM_GX_SETTEXT, 0, 
					  (LPARAM)(LPCTSTR) m_strDisplay);
	}
}


/////////////////////////////////////////////////////////////////////////////
// CGXBPopupCalculator implementation
//

UINT CGXBPopupCalculator::GetClassStyle() const
{
	return CS_SAVEBITS;
}


/////////////////////////////////////////////////////////////////////////////
// CGXBPopupCalculator message handlers
//

void CGXBPopupCalculator::PostNcDestroy()
{
	if(m_bAutoDelete)
		delete this;
}

void CGXBPopupCalculator::OnKillFocus(CWnd* pNewWnd)
{
	// OG specific commented out the notify
	// this causes the value to be changed even when
	// the user hits ESC
	if(pNewWnd != this)
	{
		//Notify();
		DestroyWindow();
	}
}

void CGXBPopupCalculator::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if(nChar == VK_ESCAPE)
		// Escape kills us
		DestroyWindow();
	else if(nChar == VK_RETURN)
	{
		// Return actions the current operator, then kills us
		HandleOperator(OpEquals);
		Notify();
		DestroyWindow();
	}
	else
		CGXBCalculator::OnKeyDown(nChar, nRepCnt, nFlags);
}

// This override is grid specific
void CGXBPopupCalculator::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if(nChar == VK_DOWN)
	{
		// Return actions the current operator, then kills us
		HandleOperator(OpEquals);
		Notify();
		DestroyWindow();
	}
	else
		CGXBCalculator::OnKeyDown(nChar, nRepCnt, nFlags);

}

#ifdef _DEBUG
void CGXBPopupCalculator::Dump(CDumpContext& dc) const
{
	CGXBCalculator::Dump(dc);

	dc << _T("m_hWndOwner = ") << m_hWndOwner << _T("\n");
}

void CGXBPopupCalculator::AssertValid() const
{
	CGXBCalculator::AssertValid();

	ASSERT(m_hWndOwner == NULL || ::IsWindow(m_hWndOwner));
}
#endif



///////////////////////////////////////////////////////////////////////////////
// CGXBConvertDBU
//
// Function to convert Dialog Base Units to pixels.
//
CSize AFXAPI CGXBConvertDBU(int x, int y, HFONT hFont /* = NULL */)
{
	CSize sz;

	if (hFont != NULL)
	{
		HDC hDC = ::GetDC(NULL);
		HFONT hFontOld = (HFONT)::SelectObject(hDC, hFont);
		TEXTMETRIC tm;

		::GetTextMetrics(hDC, &tm);
		::GetTextExtentPoint(hDC,
			_T("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"), 52,
			&sz);
		sz.cx = (sz.cx + 26) / 52;
		sz.cy = tm.tmHeight + tm.tmExternalLeading;
		::SelectObject(hDC, hFontOld);
		::ReleaseDC(NULL, hDC);
	}
	else
	{
		sz.cx = LOWORD(GetDialogBaseUnits());
		sz.cy = HIWORD(GetDialogBaseUnits());
	}

	// Translate dialog units to pixels
	sz.cx = MulDiv(x, sz.cx, 4);
	sz.cy = MulDiv(y, sz.cy, 8);

	return sz;
}

















/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CGXBCalcBtn
//
// Base class (and implementation) for CGXBCalculator buttons.
//


//---------------------------------------------------------------------------
//
// CGXBCalcBtn  Default constructor
//
CGXBCalcBtn::CGXBCalcBtn()
{
	m_nWidth        = 1;
	m_nState        = 0;
	m_nKeyDownAccel = 0;
	m_rect.SetRectEmpty();
}

//---------------------------------------------------------------------------
//
// CGXBCalcBtn  Destructor
//
CGXBCalcBtn::~CGXBCalcBtn()
{
}

//---------------------------------------------------------------------------
//
// CGXBCalcBtn::Initialise
//
// Initialise button where accelerators are same as caption
//
BOOL CGXBCalcBtn::Initialise(const Attrib& attrib, CGXBCalculator::CGXBCalcOp op, 
							LPCTSTR lpszCaption, int nWidth /* = 1 */, 
							BOOL bStartsRow /* = FALSE */)
{
	return Initialise(attrib, op, lpszCaption, lpszCaption, nWidth, bStartsRow);
}

//---------------------------------------------------------------------------
//
// CGXBCalcBtn::Initialise
//
// Initialise button with single character accelerator
//
BOOL CGXBCalcBtn::Initialise(const Attrib& attrib, CGXBCalculator::CGXBCalcOp op, 
							LPCTSTR lpszCaption, TCHAR cAccel, 
							int nWidth /* = 1 */, 
							BOOL bStartsRow /* = FALSE */)
{
	CString temp = cAccel;
	return Initialise(attrib, op, lpszCaption, temp, nWidth, bStartsRow);
}

//---------------------------------------------------------------------------
//
// CGXBCalcBtn::Initialise
//
// Initialise button with different accelerators to caption
//
BOOL CGXBCalcBtn::Initialise(const Attrib& attrib, CGXBCalculator::CGXBCalcOp op, 
							LPCTSTR lpszCaption, LPCTSTR lpszAccel, 
							int nWidth /* = 1 */,  
							BOOL bStartsRow /* = FALSE */)
{
	m_attribs    = attrib;
	m_op         = op;
	m_strCaption = lpszCaption;
	m_nWidth     = nWidth;
	if(bStartsRow)
		m_nState |= StartsRow;
	else
		m_nState &= ~StartsRow;

	// We keep accelerators as lower case.
	m_strAccels  = lpszAccel;
	m_strAccels.MakeLower();

	return TRUE;
}

//---------------------------------------------------------------------------
//
// CGXBCalcBtn::GetWidth
//
// Return the width of the button. This is specified in the number of columns
// it occupies.
//
BOOL CGXBCalcBtn::GetWidth() const
{
	ASSERT_VALID(this);

	return m_nWidth;
}

//---------------------------------------------------------------------------
//
// CGXBCalcBtn::GetRect
//
// Return the window rectangle for the button (relative to CGXBCalculators
// client).
//
const CRect& CGXBCalcBtn::GetRect() const
{
	ASSERT_VALID(this);

	return m_rect;
}

//---------------------------------------------------------------------------
//
// CGXBCalcBtn::SetRect
//
// Sets the window rectangle for the button (relative to CGXBCalculators
// client).
//
void CGXBCalcBtn::SetRect(const RECT& rect)
{
	ASSERT_VALID(this);

	m_rect = rect;
}

//---------------------------------------------------------------------------
//
// CGXBCalcBtn::GetState
//
// Returns the current state flags for the button.
//
int  CGXBCalcBtn::GetState() const
{
	ASSERT_VALID(this);

	return m_nState;
}

//---------------------------------------------------------------------------
//
// CGXBCalcBtn::SetState
//
// Set the current button state (note this replaces any current state).
//
void CGXBCalcBtn::SetState(int nState)
{
	ASSERT_VALID(this);

	m_nState = nState;
}

//---------------------------------------------------------------------------
//
// CGXBCalcBtn::SetKeyDownAccel
//
// Sets the WM_KEYDOWN accelerator for this button (not normally set)
//
void CGXBCalcBtn::SetKeyDownAccel(UINT nChar)
{
	ASSERT_VALID(this);

	m_nKeyDownAccel = nChar;
}

//---------------------------------------------------------------------------
//
// CGXBCalcBtn::IsKeyDownAccelerator
//
// Returns TRUE if the given WM_KEYDOWN char is an accelerator for this btn.
//
BOOL CGXBCalcBtn::IsKeyDownAccelerator(UINT nChar) const
{
	ASSERT_VALID(this);

	return (nChar == m_nKeyDownAccel);
}

//---------------------------------------------------------------------------
//
// CGXBCalcBtn::IsAccelerator
//
// Returns TRUE if the given char (must be lower case) is an accelerator
// for this button.
//
BOOL CGXBCalcBtn::IsAccelerator(LPCTSTR lpszChar) const
{
	ASSERT_VALID(this);

	return (m_strAccels.Find(lpszChar) != -1);
}

//---------------------------------------------------------------------------
//
// CGXBCalcBtn::GetOp
//
// Returns the operation code associated with this button.
//
CGXBCalculator::CGXBCalcOp CGXBCalcBtn::GetOp() const
{
	ASSERT_VALID(this);

	return m_op;
}

//---------------------------------------------------------------------------
//
// CGXBCalcBtn::Draw
//
// Draws the button to the given DC. Note that the button is drawn relative
// to the CGXBCalculator's client rectangle.
//
void CGXBCalcBtn::Draw(CDC& dc)
{
	HTHEME	lhTheme = NULL;
	HRESULT	hr = 0;

	// Note: Calling dc.GetWindow() will return an invalid handle.
	// We instead call AfxGetMainWnd()->GetSafeHwnd().
	if (RWIsAppThemed() && RWIsThemeActive())
	{
		lhTheme = RWOpenThemeData (RWGetSafeHwnd(), L"Button");
	}

	// Draw the outer borders around the button
	CRect r = m_rect;

	CRect	rcContent;
	int		iState = PBS_NORMAL;

	if( m_nState & Hot )
		iState = PBS_HOT;

	if( m_nState & Down )
		iState = PBS_PRESSED;

	if( lhTheme )
	{
		hr = RWDrawThemeBackground( lhTheme, dc.GetSafeHdc(), BP_PUSHBUTTON, iState, &r, 0 );	
	}
	else
	{
		GXDraw3dRect1(&dc, r, GXGetSysData()->clrBtnShadow, GXGetSysData()->clrBtnHilite);
		r.InflateRect(-1, -1);
		GXDraw3dRect1(&dc, r, GXGetSysData()->clrWindowFrame, GXGetSysData()->clrWindowFrame);
		r.InflateRect(-1, -1);

		if(m_nState & Down)
		{
			// The button is current depressed. This has just a single width
			// inner border.
			GXDraw3dRect1(&dc, r, GXGetSysData()->clrBtnShadow, GXGetSysData()->clrBtnShadow);
			r.InflateRect(-1, -1);

			GXFillSolidRect1(&dc, r, GXGetSysData()->clrBtnFace);

			r.InflateRect(-1, -1);

			// Offset the button caption (gives appearance of movement).
			r.left += 2;
			r.top += 2;
		}
		else
		{
			// Up
			GXDraw3dRect1(&dc, r, GXGetSysData()->clrBtnHilite, GXGetSysData()->clrBtnShadow);
			r.InflateRect(-1, -1);
			GXDraw3dRect1(&dc, r, GXGetSysData()->clr3DLight, GXGetSysData()->clrBtnShadow);
			r.InflateRect(-1, -1);

			GXFillSolidRect1(&dc, r, GXGetSysData()->clrBtnFace);
		}
	}

	// If we have a bitmap then draw it now.
	HBITMAP hBmp = m_attribs.GetBitmap();
	if(hBmp)
	{
		CDC memDC;
		if(memDC.CreateCompatibleDC(&dc))
		{
			HGDIOBJ hOldBmp = memDC.SelectObject((HGDIOBJ) hBmp);

			BITMAP bm;
			::GetObject(hBmp, sizeof(bm), &bm);

			int x;
			if(!m_strCaption.IsEmpty())
				// The button has a caption so, offset bitmap from left hand
				// edge
				x = r.left + 5;
			else
				// The button has no caption so bitmap will be centered.
				x = max((r.Width() - bm.bmWidth)/2 + r.left, r.left);

			// Bitmap is always centered on the Y axis.
			int y = max((r.Height() - bm.bmHeight)/2 + r.top, r.top);

			int cx = min(r.right - x, bm.bmWidth);
			int cy = min(r.bottom - y, bm.bmHeight);

			dc.BitBlt(x, y, cx, cy, &memDC, 0, 0, SRCCOPY);
			memDC.SelectObject(hOldBmp);

			// Offset the remaining rectangle past the bitmap.
			r.left += cx;
		}
	}

	if(!m_strCaption.IsEmpty())
	{
		// We have a caption so draw it now.
		HGDIOBJ hFontOld = dc.SelectObject((HGDIOBJ) m_attribs.GetFont());
		dc.SetTextColor(m_attribs.GetTextColor());
		dc.SetBkColor(GXGetSysData()->clrBtnFace);

		if( lhTheme )
		{
			dc.SetBkMode( TRANSPARENT );
		}

		dc.DrawText(m_strCaption, m_strCaption.GetLength(), r, 
					DT_CENTER|DT_VCENTER|DT_SINGLELINE|DT_NOPREFIX);

		dc.SelectObject(hFontOld);
	}

	if( lhTheme )
		RWCloseThemeData( lhTheme );
}


#ifdef _DEBUG
void CGXBCalcBtn::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);

	dc << _T("m_op     = ") << (UINT) m_op << _T("\n");
	dc << _T("m_nState = ") << m_nState << _T("\n");
	dc << _T("m_rect   = ") << m_rect << _T("\n");
}

void CGXBCalcBtn::AssertValid() const
{
	CObject::AssertValid();

	ASSERT(m_nWidth > 0);
}
#endif




/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CGXBCalcBtn::Attrib
//
// CGXBCalcBtn attribute class. Defines the attributes for drawing the face
// of the button
//


//---------------------------------------------------------------------------
//
// CGXBCalcBtn::Attrib  Default constructor
//
CGXBCalcBtn::Attrib::Attrib()
{
	m_dwStyle   = 0L;					// Style flags for drawing button
	m_textColor = RGB(0, 0, 0);			// Color for drawing caption
	m_hFont     = NULL;					// Font used for drawing caption
	m_lphBitmap = NULL;					// Ptr to bitmap handle. This is an
										// optional bitmap which can be
										// drawn on the face of the button.
}

//---------------------------------------------------------------------------
//
// CGXBCalcBtn::Attrib  constructor
//
CGXBCalcBtn::Attrib::Attrib(DWORD dwStyle, COLORREF textColor /* = 0L */, 
						   HFONT hFont /* = NULL */, 
						   HBITMAP* lphBitmap /* = NULL */)
{
	m_dwStyle   = dwStyle;
	m_textColor = textColor;
	m_hFont     = hFont;
	m_lphBitmap = lphBitmap;
}

//---------------------------------------------------------------------------
//
// CGXBCalcBtn::Attrib  Copy constructor
//
CGXBCalcBtn::Attrib::Attrib(const Attrib& attrib)
{
	m_hFont     = attrib.m_hFont;
	m_lphBitmap = attrib.m_lphBitmap;
	m_textColor = attrib.m_textColor;
	m_dwStyle   = attrib.m_dwStyle;
}

//---------------------------------------------------------------------------
//
// CGXBCalcBtn::Attrib Destructor
//
CGXBCalcBtn::Attrib::~Attrib()
{
}

//---------------------------------------------------------------------------
//
// CGXBCalcBtn::Attrib  Assignment operator
//
const CGXBCalcBtn::Attrib& CGXBCalcBtn::Attrib::operator=(const CGXBCalcBtn::Attrib& attrib)
{
	m_hFont     = attrib.m_hFont;
	m_lphBitmap = attrib.m_lphBitmap;
	m_textColor = attrib.m_textColor;
	m_dwStyle   = attrib.m_dwStyle;

	return *this;
}

//---------------------------------------------------------------------------
//
// CGXBCalcBtn::Attrib::GetFont
//
// Returns the font for drawing the button caption
//
HFONT CGXBCalcBtn::Attrib::GetFont() const
{
	return m_hFont;
}

//---------------------------------------------------------------------------
//
// CGXBCalcBtn::Attrib::GetTextColor
//
// Returns the foreground (text) color for drawing the button caption
//
COLORREF CGXBCalcBtn::Attrib::GetTextColor() const
{
	return m_textColor;
}

//---------------------------------------------------------------------------
//
// CGXBCalcBtn::Attrib::GetBitmap
//
// Returns the bitmap handle associated with the button. Note this can be 
// (and probably is) NULL.
//
HBITMAP CGXBCalcBtn::Attrib::GetBitmap() const
{
	if(m_lphBitmap)
		return *m_lphBitmap;
	else
		return NULL;
}


