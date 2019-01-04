///////////////////////////////////////////////////////////////////////////////
// gxcurbas.cpp
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

// gxcurbas.cpp : Currency control implementation
// 
// The source code for this control has been copied
// from Objective Toolkit.
//

#define _OG_EXPORT_IMPL

#include "stdafx.h"

#include <locale.h> // for localeconv();
#include <math.h>

#include "grid\gxcalc.h"
#include "grid\gxcurbas.h"

#pragma warning(disable: 4189)

//FOUNDATION_GLOBAL_FUNC_API(HWND) RWGetSafeHwnd();

IMPLEMENT_DYNAMIC(CGXBCurrencyEdit, CGXBDropEdit)

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// Flags for CGXBCurrencyEdit::Format color usage.

const int USE_BACKGROUND_COLOR	= 0x1;
const int USE_NEGATIVE_COLOR	= 0x2;
const int USE_POSITIVE_COLOR	= 0x4;

// The following static data is used in formatting currency output.
// In each case, the %c is used as an identifier for which the 
// currency symbol will eventually be substituted.

typedef struct PrefixSuffix
{ 
	LPCTSTR pPrefix, pSuffix;
	
} PREFIXSUFFIX;

static PREFIXSUFFIX s_Positive[] = 
{
	{ _T("%s"), NULL },		// 0	$1
	{ NULL, _T("%s") },		// 1	1$ 
	{ _T("%s "), NULL },	// 2	$ 1
	{ NULL, _T(" %s") }		// 3	1 $
};

static PREFIXSUFFIX s_Negative[] = 
{
	{ _T("(%s"), _T(")") },		// 0	($1)
	{ _T("-%s"), NULL },		// 1	-$1 
	{ _T("%s-"), NULL },		// 2	$-1 
	{ _T("%s"), _T("-") },		// 3	$1- 
	{ _T("("), _T("%s)") },		// 4	(1$)
	{ _T("-"), _T("%s") },		// 5	-1$ 
	{ NULL, _T("-%s") },		// 6	1-$ 
	{ NULL, _T("%s-") },		// 7	1$- 
	{ _T("-"), _T(" %s") },		// 8	-1 $
	{ _T("-%s "), NULL },		// 9	-$ 1
	{ NULL, _T(" %s-")},		// 10   1 $-
	{ _T("%s "), _T("-") },		// 11	$ 1-
	{ _T("%s -"), NULL },		// 12   $ -1
	{ NULL, _T("- %s") },		// 13   1- $
	{ _T("(%s "), _T(")") },	// 14   ($ 1)
	{ _T("("), _T(" %s)") },	// 15   (1 $)
};

// Returns true if the specified key is down.

inline BOOL IsKeyDown(UINT uiKey)
	{ return !!(GetKeyState(uiKey) & 0x8000); }


#ifdef WIN32

inline void GetIntlString(LCTYPE lc, LPCTSTR pcszDefault, CString& s)
{
	int iChars = GetLocaleInfo(LOCALE_USER_DEFAULT, lc, NULL, 0);
	if (iChars > 0)
	{
		LPTSTR pBuf = s.GetBuffer(iChars);
		GetLocaleInfo(LOCALE_USER_DEFAULT, lc, pBuf, iChars);
		s.ReleaseBuffer();
		
		if (s.IsEmpty ()) 
			s = pcszDefault; 
	}
	else
	{
		s = pcszDefault;
	}
}

inline void GetIntlInt(LCTYPE lc, int iDefault, int& iDest)
{
	CString s;
	GetIntlString(lc, _T(""), s);
	if (s.IsEmpty())
		iDest = iDefault;
	else
		iDest = _ttoi(s);
}

#else
// Retrieves a string from the WIN.INI international CGXBtion.

inline void GetIntlString(LPCTSTR pcszKey, LPCTSTR pcszDefault, CString& s)
{
	const int BUFSIZE = 255;
	LPTSTR p = s.GetBuffer(BUFSIZE);
	::GetProfileString(_T("Intl"), pcszKey, pcszDefault, p, BUFSIZE);
	s.ReleaseBuffer();
}

// Retrieves an integer from the WIN.INI international CGXBtion.

inline void GetIntlInt(LPCTSTR pcszKey, int iDefault, int& iDest)
	{ iDest = ::GetProfileInt(_T("Intl"), pcszKey, iDefault); }

#endif

// Returns flags for menu item appending; grey if argument is true.

inline UINT GrayIf(BOOL bGrayed)
	{ return bGrayed ? MF_STRING | MF_GRAYED : MF_STRING; }

// Returns a count of the digits within the string.

static int CountDigits(LPCTSTR p)
{
	int iDigits = 0;
	while (*p != _T('\0'))
		 if (isdigit((unsigned char)*p++))
			iDigits++;
	return iDigits;
}

/*
// Find the first and last characters in the numeric portion.

static BOOL FindFirstAndLastDigits(LPCTSTR p, TCHAR cDecimal, 
								   int& iFirst, int& iLast)
{
	int iLength = lstrlen(p);
	iLast = iFirst = -1;
	for (int i = 0; i < iLength && iFirst == -1; i++)
	{
		TCHAR c = p[i];
		if (_istdigit(c) || (c == cDecimal))
			iFirst = i;
	}
	if (iFirst == -1)
		return FALSE;
	for (i = iLength - 1; i > -1 && iLast == -1; i--)
	{
		TCHAR c = p[i];
		if (_istdigit(c) || (c == cDecimal))
			iLast = i;
	}
	return TRUE;
}
*/
// Returns the index of the first digit after the specified index
// within the string. In this context, 'index' refers to the digit
// index, not an absolute index into the string; e.g., the zeroth
// digit will be the first digit to appear in the string and may
// be located via the GetDigitIndex function.

static int GetDigitAfterIndex(int i, LPCTSTR p)
{
	return i > 0 ? CountDigits(CString(p).Left(i)) : 0;
}


// Returns the index of the first digit before the specified index
// within the string. In this context, 'index' refers to the digit
// index, not an absolute index into the string; e.g., the zeroth
// digit will be the first digit to appear in the string and may
// be located via the GetDigitIndex function.

static int GetDigitBeforeIndex(int i, LPCTSTR p)
{
	return i > 1 ? CountDigits(CString(p).Left(i)) - 1 : 0;
}

// Returns the index of the specified digit number within the string
// or -1 if the string does not contain enough digits.

static int GetDigitIndex(int iDigitNumber, LPCTSTR p)
{
	if (p != NULL)
	{
		int iDigits = 0;
		for (int i = 0; p[i] != _T('\0'); i++)
			if (isdigit((unsigned char)p[i]) && (++iDigits > iDigitNumber))
				return i;
	}
	return -1;
}

// Returns the class name of the specified window.

static void AfxGetWindowClassName(CWnd* pWnd, CString& s)
{
	const int BUFSIZE = 256;
	TCHAR sz[BUFSIZE];
	if (GetClassName(pWnd->GetSafeHwnd(), sz, BUFSIZE) > 0)
		s = sz;
	else
		s.Empty();
}

// Returns true if the specified window is an edit control.

static BOOL IsEditControl(CWnd* pWnd)
{
	CString s;
	AfxGetWindowClassName(pWnd, s);
	return s.CompareNoCase(_T("edit")) == 0;
}

// Returns true if the string was fetched from the clipboard.

static BOOL GetClipboardText(CString& s)
{
	static UINT uiFmt = (sizeof(TCHAR) == sizeof(char)) ? CF_TEXT : CF_UNICODETEXT;

	if (IsClipboardFormatAvailable(uiFmt))
	{
		if (OpenClipboard(NULL))
		{
			HANDLE h = GetClipboardData(uiFmt);
			LPCTSTR p = (LPCTSTR)GlobalLock(h);
			s = p;
			GlobalUnlock(h);
			CloseClipboard();
			return TRUE;
		}
	}

	return FALSE;
}

// Returns true if the string was set to the clipboard.

static BOOL SetClipboardText(LPCTSTR pcsz)
{
	static UINT uiFmt = (sizeof(TCHAR) == sizeof(char)) ? CF_TEXT : CF_UNICODETEXT;

	if (pcsz != NULL && *pcsz != _T('\0'))
	{
		int iLength = (lstrlen(pcsz) + 1) * sizeof(TCHAR);
		HANDLE h = GlobalAlloc(GHND | GMEM_SHARE, iLength);
		LPTSTR p = (LPTSTR)GlobalLock(h);
		if (p != NULL)
		{
			lstrcpy(p, pcsz);
			GlobalUnlock(h);

			if (OpenClipboard(NULL))
			{
				if (EmptyClipboard())
				{
					SetClipboardData(uiFmt, h);
					h = NULL;
				}

				CloseClipboard();
				if (h != NULL)
					GlobalFree(h);
				else
					return TRUE;
			}
		}
	}

	return FALSE;
}

// This function takes a string containing a positive number, a
// decimal point character, and separator character.  It reformats
// the number, inserting the separator every 3 decimal digits.

// SRSTUDIO-391
// NOTE: As of CD53 SS 10.3 this function should no longer be used. Instead use
// GroupDigits with a mask.
static void GroupDigits(CString& s, const CGXBCurrencyEdit::Format* pFmt, int iGroupSize)
{
	ASSERT(iGroupSize > 1);
	TCHAR cSeparator = pFmt->GetThousandSeparator();

	int iLength = s.GetLength(), iDigits;
	int iDecimalIndex = pFmt->FindDecimalSeparator(s);
	if (iDecimalIndex != -1)
		iDigits = iDecimalIndex;
	else
		iDigits = iLength;

	// Calculate the number of separators to be added.

	int iNum = (iDigits - 1) / iGroupSize;
	if (iNum > 0)
	{
		LPTSTR p = new TCHAR[iLength + iNum + 1];
		LPTSTR pOut=p;
		for (int i = 0; i < iLength; i++)
		{
			*pOut++ = s.GetAt(i);
			iDigits--;

			if (iDigits > 0 && (iDigits % iGroupSize) == 0)
			{
				*pOut++ = cSeparator;
			}
		}
		*pOut = _T('\0');
		s = p;
		delete [] p;
		p = NULL;
	}
}

// SRSTUDIO-391
// Uses formatting mask based on locale settings to group digits. 
static void GroupDigits(CString& s, CString strMask, const CGXBCurrencyEdit::Format* pFmt)
{
	TCHAR cSeparator = pFmt->GetThousandSeparator();

	int iLength = s.GetLength(), iDigits;
	int iDecimalIndex = pFmt->FindDecimalSeparator(s);
	if (iDecimalIndex != -1)
	{
		iDigits = iDecimalIndex;
	}else
	{
		iDigits = iLength;
	}

	// Calculate the number of separators to be added.
	int iNum = (iDigits - 1);
	if (iNum > 0)
	{
		CString strTemp;
		CString strDigits = s.Left(iDigits);
		CString strDecimal;
		if(iDecimalIndex != -1)
		{
			strDecimal = s.Right(iLength - iDigits);
		}
		CString strOut;
		CString strTmpMask = strMask;

		while(strDigits.GetLength() > 0)
		{
			strTemp = strTmpMask.Right(1);
			// Remove last character in mask. 
			strTmpMask = strTmpMask.Left(strTmpMask.GetLength()-1);
			if(strTemp == "#")
			{
				strOut += strDigits.Right(1);
				// Remove last character in the in string.
				strDigits = strDigits.Left(strDigits.GetLength()-1);
			}else
			{
				// Mask character.
				strOut += cSeparator;
			}
		}
		// Reverse the string so it is in the correct order.
		strOut.MakeReverse();
		// Add any decimal digits
		if(iDecimalIndex != -1)
		{
			strOut += strDecimal;
		}
		// Reassign the out string.
		s = strOut;
	}
}

// SRSTUDIO-391
#define GROUPING_MASK_MAX_DIGIT 25

// A grouping mask will be created based on locale currency settings. 
// For English a mask should look similar to ###,###,###,###,###,###.
// For Indian a mask should look similar to ##,##,##,##,##,##,##,###.
static void CreateGroupingMask(CString const _strGrouping, CString& _strMaskOut)
{
	CString strGrouping = _strGrouping;
	CString strMask;
	CString strToken;
	int iGroup = 0;
	int iPrevGroup;
	int iPos = 0;

	// Get the first token.
	strToken = strGrouping.Tokenize(_T(";"),iPos);
	ASSERT(strToken != _T("") && strToken != _T("0"));
	// Construct the Grouping Mask.
	while(strToken != _T(""))
	{
		// Save previous grouping.
		iPrevGroup = iGroup;
		int res = _stscanf(strToken, _T("%d"), &iGroup);

		// Repeat Grouping?
		if(0 == iGroup)
		{
			// Repeat until we have a mask of GROUPING_MASK_MAX_DIGIT characters.
			while(strMask.GetLength() <= GROUPING_MASK_MAX_DIGIT)
			{
				for(int i = 0; i < iPrevGroup; i++)
				{
					strMask += _T("#");
				}
				strMask += _T(",");
			}
		}else
		{
			// Add mask iGroup number of mask symbols.
			for(int i = 0; i < iGroup; i++)
			{
				strMask += _T("#");
			}
			strMask += _T(",");
		}
		strToken = strGrouping.Tokenize(_T(";"),iPos);
	}
	// Reverse the mask so it is in the correct order.
	strMask.MakeReverse();
	// Assign the mask.
	_strMaskOut = strMask;
}


// According to the WIN32 internationalization specifications, any number
// of group sizes may be specified, each separated by a semicolon. In
// practice, however, the Control Panel/Regional Settings applet allows one
// only to pick a number if digits to be grouped. This number is then
// followed by ";0" to indicate that the given group size should simply 
// be repeated.

// SRSTUDIO-391
// This function now groups multiple groupings based on the user locale.

static void GroupDigits(CString& s, const CGXBCurrencyEdit::Format* pFmt,
						LPCTSTR pcszGrouping)
{
	CString strMask;
	CreateGroupingMask(pcszGrouping, strMask);
	GroupDigits(s, strMask, pFmt);
	return;
}

// Returns true if the specified window class could be registered.

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


static int RemoveAllButDigits(CString& s)
{
	int iRemoved = 0;
	LPTSTR pIn = s.GetBuffer(0), pOut;

	for (pOut = pIn; *pIn != '\0'; pIn++)
	{
		TCHAR c = *pIn;
		if (_istdigit(c))
			*pOut++ = *pIn;
		else
			iRemoved++;
	}

	*pOut = '\0';
	s.ReleaseBuffer();
	return iRemoved;
}

static int RemoveFromString(CString& s, TCHAR cRemove)
{
	int iRemoved = 0;
	LPTSTR pIn = s.GetBuffer(0), pOut;

	for (pOut = pIn; *pIn != '\0'; pIn++)
	{
		TCHAR c = *pIn;
		if (c != cRemove)
			*pOut++ = *pIn;
		else
			iRemoved++;
	}

	*pOut = '\0';
	s.ReleaseBuffer();
	return iRemoved;
}

static BOOL IsAllDigits(LPCTSTR p)
{
	while (*p != '\0')
		if (!_istdigit(*p++))
			return FALSE;
	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////
// CGXBCurrencyEdit::Format implementation

CGXBCurrencyEdit::Format::Format(BOOL bInitializeFromSystemDefaults) :
	m_bDecimalSeparatorLine(FALSE),
	m_crBackground(RGB(0, 0, 0)),
	m_crNegative(RGB(0, 0, 0)),
	m_crPositive(RGB(0, 0, 0)),
	m_crSeparator(GetSysColor(COLOR_3DSHADOW)),
	m_iColorUseFlags(0),
	m_cPaddingCharacter(_T(' ')),
	m_bSeparatorsInLeadingSpaces(FALSE),
	m_bRotateWhileAtEnd(FALSE)
{
	if (bInitializeFromSystemDefaults)
	{
		InitializeFromSystemDefaults();
	}
	else
	{
		m_bLeadingZero = TRUE;
		m_strMonetarySymbol = _T('$');
		m_strGrouping = _T("3;0");
		m_cThousandSeparator = _T(',');
		m_cDecimalSeparator = _T('.');
		m_iPositiveFormat = 0;
		m_iNegativeFormat = 0;
		m_iDecimalDigits = -1;
		m_iFractionalDigits = 2;
	}
}

void CGXBCurrencyEdit::Format::InitializeFromSystemDefaults()
{
	CString s;
	
#ifdef WIN32
	GetIntlString(LOCALE_SCURRENCY, _T("$"), m_strMonetarySymbol);
	GetIntlInt(LOCALE_ICURRENCY, 0, m_iPositiveFormat);
	GetIntlString(LOCALE_SMONGROUPING, _T("3;0"), m_strGrouping);
	GetIntlInt(LOCALE_ICURRDIGITS, 2, m_iFractionalDigits);
	GetIntlInt(LOCALE_INEGCURR, 0, m_iNegativeFormat);
	GetIntlString(LOCALE_SMONTHOUSANDSEP, _T(","), s);
	m_cThousandSeparator = s.GetAt(0);
	GetIntlString(LOCALE_SMONDECIMALSEP, _T("."), s);
	m_cDecimalSeparator = s.GetAt(0);
	GetIntlInt(LOCALE_ILZERO, TRUE, m_bLeadingZero);
	GetIntlInt(LOCALE_IDIGITS, -1, m_iDecimalDigits);
#else
	GetIntlString(_T("sCurrency"), _T("$"), m_strMonetarySymbol);
	m_strGrouping = _T("3;0");
	GetIntlInt(_T("iCurrency"), 0, m_iPositiveFormat);
	GetIntlInt(_T("iCurrDigits"), 2, m_iFractionalDigits);
	GetIntlInt(_T("iNegCurr"), 0, m_iNegativeFormat);
	GetIntlString(_T("sThousand"), _T(","), s);
	m_cThousandSeparator = s.GetAt(0);
	GetIntlString(_T("sMonDecimalSep"), _T("."), s);
	m_cDecimalSeparator = s.GetAt(0);
	GetIntlInt(_T("iLzero"), TRUE, m_bLeadingZero);
	GetIntlInt(_T("iDigits"), -1, m_iDecimalDigits);
#endif


}

BOOL CGXBCurrencyEdit::Format::SetPaddingCharacter(TCHAR c)
{
	if (!_istdigit(c) || (c == '0'))
	{
		m_cPaddingCharacter = c;
		return TRUE;
	}

	TRACE0("CGXBCurrencyEdit::Format::SetPaddingCharacter padding character must be a non-digit or zero\n");
	ASSERT(0);
	return FALSE;
}

BOOL CGXBCurrencyEdit::Format::GetBackgroundColor(COLORREF& cr) const
{
	if (m_iColorUseFlags & USE_BACKGROUND_COLOR)
	{
		cr = m_crBackground;
		return TRUE;
	}

	return FALSE;
}

void CGXBCurrencyEdit::Format::SetBackgroundColor(COLORREF cr)
{
	m_crBackground = cr;
	m_iColorUseFlags |= USE_BACKGROUND_COLOR;
}

BOOL CGXBCurrencyEdit::Format::GetNegativeColor(COLORREF& cr) const
{
	if (m_iColorUseFlags & USE_NEGATIVE_COLOR)
	{
		cr = m_crNegative;
		return TRUE;
	}

	return FALSE;
}

void CGXBCurrencyEdit::Format::SetNegativeColor(COLORREF cr)
{
	m_crNegative = cr;
	m_iColorUseFlags |= USE_NEGATIVE_COLOR;
}

BOOL CGXBCurrencyEdit::Format::GetPositiveColor(COLORREF& cr) const
{
	if (m_iColorUseFlags & USE_POSITIVE_COLOR)
	{
		cr = m_crPositive;
		return TRUE;
	}

	return FALSE;
}

void CGXBCurrencyEdit::Format::SetPositiveColor(COLORREF cr)
{
	m_crPositive = cr;
	m_iColorUseFlags |= USE_POSITIVE_COLOR;
}

BOOL CGXBCurrencyEdit::Format::SetGrouping(LPCTSTR x)
{
	int iGroupSize, iZero;
	// QA: 31989 - #if Secure Code Cleanup.
	int iNumFields = _stscanf(x, _T("%i;%i"), &iGroupSize, &iZero);

	// If you are reading this comment because one assert has tripped,
	// the problem is that the grouping string is unsupported. The WIN32 
	// API supposedly allows multiple group settings (e.g., a value could 
	// be formatted as "$ 1,2345,67,8.0"). But, since the Windows 95 and 
	// Windows NT Control Panel/Regional Settings applets allow only one 
	// specification, the grouping string must be of the form "x;0" wherein 
	// 'x' is the desired number of digits.
	
	if (iNumFields == 2 && -1 < iGroupSize && iZero == 0)
	{
		m_strGrouping = x;
		return TRUE;
	}
	else
	{
		ASSERT(0);
		return FALSE;
	}
}

int CGXBCurrencyEdit::Format::FindDecimalSeparator(LPCTSTR pcszString, TCHAR cDecimal) const
{
	if (cDecimal == '\0')
		cDecimal = m_cDecimalSeparator;
	LPTSTR pSep = (LPTSTR)_tcsrchr(pcszString, cDecimal);
	if (pSep == NULL)
		return -1;
	else
		return (int)(pSep - pcszString);
}

// Find the first and last characters in the numeric portion.

BOOL CGXBCurrencyEdit::Format::FindFirstAndLastDigits(LPCTSTR p, int& iFirst, int& iLast) const
{
	int iLength = lstrlen(p), i;
	iLast = iFirst = -1;

	// Find the last digit in the string.

	for (i = iLength - 1; i > -1 && iLast == -1; i--)
	{
		TCHAR c = p[i];
		if (_istdigit(c))
			iLast = i;
	}

	if (iLast == -1)
		return FALSE;

	// Now, work backwards from that digit.

	BOOL bDecimalAllowed = TRUE;
	iFirst = iLast;
	for (i = iLast - 1; i > -1; i--)
	{
		TCHAR c = p[i];
		if (_istdigit(c))
		{
			iFirst = i;
		}
		else if ((c == m_cDecimalSeparator) && bDecimalAllowed)
		{
			bDecimalAllowed = FALSE;
			iFirst = i;
		}
		else if (c == m_cThousandSeparator)
		{
			bDecimalAllowed = FALSE;
			iFirst = i;
		}
		else
		{
			break;
		}
	}

	return TRUE;
}

// The following method is responsible for extracting a numeric value
// from a string.  The string may have previously been formatted by a
// CGXBCurrencyEdit, or it may have come from some other source.  Some
// important items to remember follow.
//
// 1) Leading and trailing whitespace are stripped prior to parsing.
// 2) An empty string, or a single decimal point character will fail.
// 3) One or more sets of parenthesis or a minus sign will result in 
//    a negative value.
// 4) The prefix and suffix are not validated.  I.E. a monetary symbol,
//    padding character(s), or other text is ignored for maximum
//    flexibility in accepting foreign input.
// 5) The only valid characters actually inside the number are the
//    current thousands separator and decimal point; any other characters
//    will cause the parsing to fail.

BOOL CGXBCurrencyEdit::Format::ParseValue(LPCTSTR pcsz, double& d, 
										 BOOL& bNegative) const
{
	// If the string is empty, we assume a zero value.

	bNegative = FALSE;
	CString s(pcsz);
	if (s.IsEmpty())
	{
		d = 0.0;
		return TRUE;
	}

	// Trim whitespace and check for a pair of parenthesis; if found,
	// consider the value to be negative.

	s.TrimLeft();
	s.TrimRight();
	int iLength = s.GetLength();
	// If there is only one parenthesis, the other has been deleted by
	// an invalid character entry. Return FALSE for parse error.
	// If there are 2, then we have a negative number.

	BOOL bFoundOpenParen = (s.Find(_T('(')) != -1);
	BOOL bFoundCloseParen = ( s.ReverseFind(_T(')')) != -1);
	if (bFoundOpenParen || bFoundCloseParen) 
	{
		if (bFoundOpenParen && bFoundCloseParen)
			bNegative = TRUE;
		else
			return FALSE;		// parse error!
	}
	// Find the first and last characters in the numeric portion.

	int iFirst, iLast;
	if (!FindFirstAndLastDigits(s, iFirst, iLast))
		return FALSE;

	// If what we found is a single decimal point, get out of here.

	if (iFirst == iLast && s.GetAt(iFirst) == m_cDecimalSeparator)
		return FALSE;

	// Separate the string into a prefix, number, and suffix.

	CString strPrefix, strNumber, strSuffix;
	if (iFirst > 0)
		strPrefix = s.Left(iFirst);
	if (iLast < iLength - 1)
		strSuffix = s.Right(iLength - 1 - iLast);
	strNumber = s.Mid(iFirst, iLast - iFirst + 1);

	// Search the prefix and suffix for a negative sign.

	if (strPrefix.Find(_T('-')) != -1 || strSuffix.Find(_T('-')) != -1)
		bNegative = TRUE;

	// Finally, we validate the numeric string itself.  The only valid
	// characters are the thousand separator, a decimal point, and
	// numeric digits.  The thousand separator(s) is/are ignored, the
	// decimal point character is converted to the decmial point as
	// defined by the programmer's current locale for later use, and
	// digits, of course, are interpreted literally.
	//
	// During validation, we create a version of the number string minus
	// thousand separator(s) in a temporary buffer.  This allows us to
	// leverage the standard C library conversion routine to perform the
	// final numeric interpretation.

	// The validation procedure itself proceeds in three phases. First,
	// we try to find a decimal point. This allows us to divide the number
	// into two parts, integral and fractional. Second, separators are 
	// removed from the integral part. Third, if all characters remaining
	// in the two halves are digits, then we reassemble the numeric string
	// as 'integral.fractional' and use the standard C-library routine.

	CString strIntegral, strFractional;
	int iDecimalIndex = FindDecimalSeparator(strNumber);
	if (iDecimalIndex != -1)
	{
		strIntegral = strNumber.Left(iDecimalIndex);
		strFractional = strNumber.Mid(iDecimalIndex + 1);
	}
	else
	{
		strIntegral = strNumber;
	}

	RemoveFromString(strIntegral, m_cThousandSeparator);
	if (IsAllDigits(strIntegral) && IsAllDigits(strFractional))
	{
		struct lconv* pLocale = localeconv();
		strNumber = strIntegral + *pLocale->decimal_point + strFractional;
		d = _tcstod(strNumber, NULL);
		return TRUE;
	}

	return FALSE;
}

void CGXBCurrencyEdit::Format::FormatValue(double dAbs, CString& str, 
										  BOOL bIsNegative) const
{
	ASSERT(dAbs >= 0.0);

	//added code that truncates the number according to the allowed number
	//of whole digits : OG fix 4/2/97
	// Say when no. of decimals is 5 and the users enters is at the 5th digit
	// and enters more nos., then the most significant digit is truncated instead of
	// disabling the entry of nos. (kind of scrolling and truncating the decimal part)
	// The following code fixes this.
	// Also added the check for dAbs != 0, otherwise it would generate some kind of floating point 
	// error that will show its ugly face later (like when you try to execute a odbc query!!!)
	double d1 = 0.0;
	if(dAbs != 0 && !IsRotateWhileAtEndEnabled()) 
	{
		// Check the decimal part...
		if(GetDecimalDigits() != -1)
		{
			modf(log10(dAbs), &d1);
			if (d1)
			{
				double logval = d1-(GetDecimalDigits()-1);
		
				if (logval>0)
				{
					double d2 = 0.0; double calcval = 0.0;
					modf(pow(10.0, logval), &d1);
					modf(dAbs, &d2);
					if (d1)
						calcval = d2/(d1);
					modf(calcval, &d2);
					dAbs = d2 + modf(dAbs, &d1);
				}
			}
		}
	}

	CString strPrefix, strNumber, strSuffix;

	
	// Get a reference to the prefix/suffix structure used based
	// on the numeric value; then creating the prefix and suffix
	// strings based upon it.

	PREFIXSUFFIX& ps = bIsNegative ? s_Negative[GetNegativeFormat()] :
									 s_Positive[GetPositiveFormat()];
	if (ps.pPrefix != NULL)
	{
		if (_tcschr(ps.pPrefix, _T('%')))
			strPrefix.Format(ps.pPrefix, GetMonetarySymbol());
		else
			strPrefix = ps.pPrefix;
	}

	if (ps.pSuffix != NULL)
	{
		if (_tcschr(ps.pSuffix, _T('%')))
			strSuffix.Format(ps.pSuffix, GetMonetarySymbol());
		else
			strSuffix = ps.pSuffix;
	}

	// Create a format for the numeric portion and use it to create the
	// initial numeric string.

	CString strNumberFormat(_T("%")), strTmp;
	int iFra = GetFractionalDigits();
	strTmp.Format(_T(".%if"), iFra);
	strNumberFormat += strTmp;
	strNumber.Format(strNumberFormat, dAbs);

	// If the value has no mantissa and we're not supposed to allow
	// a leading zero, we need to get rid of it.

	if ((dAbs < 1.0) && !IsLeadingZeroEnabled())
	{
		strNumber.SetAt(0, _T(' '));
		strNumber.TrimLeft();
	}

	// Get the locale information and convert the decimal point to the
	// character we're supposed to use.

	struct lconv* pLocale = localeconv();
	TCHAR cDecimal = *pLocale->decimal_point;
	int iDecimalIndex = FindDecimalSeparator(strNumber, cDecimal);
	if (iDecimalIndex != -1)
	{
		if ((cDecimal = GetDecimalSeparator()) == _T('\0'))
			cDecimal = _T(' ');
		strNumber.SetAt(iDecimalIndex, cDecimal);
	}

	// Check if we're supposed to limit the number of decimal characters.

	int iNeeded = 0;
	int iDec = GetDecimalDigits();
	if (iDec != -1)
	{
		int iClip;
		if (iDecimalIndex == -1)
			iClip = strNumber.GetLength() - iDec;
		else
			iClip = iDecimalIndex - iDec;
		if (iClip > 0)
			strNumber = strNumber.Mid(iClip);

		// Figure out how many padding characters we need to add
		// (if any) to reach the specified number of places.

		if (iDecimalIndex != -1)
			iNeeded = iDec - iDecimalIndex;
		else
			iNeeded = iDec - strNumber.GetLength();

		/*
		if(strNumber.GetLength()>iDec)
		{
			strNumber = strNumber.Left(iDec);
		}*/

	}

	if (iDec != -1 && iNeeded > 0 && IsSeparatorsInLeadingSpaceEnabled())
	{
		CString strPadding(GetPaddingCharacter(), iNeeded);
		strNumber = strPadding + strNumber;
	}

	// Separate the thousands if necessary.
	TCHAR cGroupChar = GetThousandSeparator();
	if (cGroupChar != _T('\0'))
	{
			GroupDigits(strNumber, this, m_strGrouping);			
	}

	if (iDec != -1 && iNeeded > 0 && !IsSeparatorsInLeadingSpaceEnabled())
	{
		CString strPadding(GetPaddingCharacter(), iNeeded);
		strNumber = strPadding + strNumber;
	}

	// Assemble the final string from the three pieces.

	str.Empty();
	str += strPrefix;
	str += strNumber;
	str += strSuffix;
}

CGXBCurrencyEdit::Format& CGXBCurrencyEdit::Format::operator=(const Format& rhs)
{
	if (this != &rhs)
	{
		m_bLeadingZero = rhs.m_bLeadingZero;
		m_bDecimalSeparatorLine = rhs.m_bDecimalSeparatorLine;
		m_bRotateWhileAtEnd = rhs.m_bRotateWhileAtEnd;
		m_bSeparatorsInLeadingSpaces = rhs.m_bSeparatorsInLeadingSpaces; 
		m_strMonetarySymbol = rhs.m_strMonetarySymbol;
		m_strGrouping = rhs.m_strGrouping;
		m_cThousandSeparator = rhs.m_cThousandSeparator;
		m_cDecimalSeparator = rhs.m_cDecimalSeparator;
		m_cPaddingCharacter = rhs.m_cPaddingCharacter;
		m_crBackground = rhs.m_crBackground;
		m_crNegative = rhs.m_crNegative;
		m_crPositive = rhs.m_crPositive;
		m_crSeparator = rhs.m_crSeparator;
		m_iColorUseFlags = rhs.m_iColorUseFlags;
		m_iPositiveFormat = rhs.m_iPositiveFormat;
		m_iNegativeFormat = rhs.m_iNegativeFormat;
		m_iDecimalDigits = rhs.m_iDecimalDigits;
		m_iFractionalDigits = rhs.m_iFractionalDigits;
	}

	return *this;
}

BOOL CGXBCurrencyEdit::Format::operator==(const CGXBCurrencyEdit::Format& rhs) const
{
	return (this == &rhs) ||
		   (m_bLeadingZero == rhs.m_bLeadingZero &&
		    m_bDecimalSeparatorLine == rhs.m_bDecimalSeparatorLine &&
			m_bRotateWhileAtEnd == rhs.m_bRotateWhileAtEnd &&
			m_bSeparatorsInLeadingSpaces == rhs.m_bSeparatorsInLeadingSpaces &&
		    m_strMonetarySymbol == rhs.m_strMonetarySymbol &&
				m_strGrouping == rhs.m_strGrouping &&
		    m_cThousandSeparator == rhs.m_cThousandSeparator &&
		    m_cDecimalSeparator == rhs.m_cDecimalSeparator &&
		    m_cPaddingCharacter == rhs.m_cPaddingCharacter &&
		    m_crBackground == rhs.m_crBackground &&
		    m_crNegative == rhs.m_crNegative &&
		    m_crPositive == rhs.m_crPositive &&
			m_crSeparator == rhs.m_crSeparator &&
		    m_iColorUseFlags == rhs.m_iColorUseFlags &&
		    m_iPositiveFormat == rhs.m_iPositiveFormat &&
		    m_iNegativeFormat == rhs.m_iNegativeFormat &&
		    m_iDecimalDigits == rhs.m_iDecimalDigits &&
		    m_iFractionalDigits == rhs.m_iFractionalDigits);
}

void CGXBCurrencyEdit::Format::SetPositiveFormat(int i)
{ 
	ASSERT( i >= 0 );
	ASSERT( i < (sizeof( s_Positive ) / sizeof( s_Positive[0])) ); 
	m_iPositiveFormat = i; 
}

void CGXBCurrencyEdit::Format::SetNegativeFormat(int i)
{ 
	ASSERT( i >=0 );
	ASSERT( i < (sizeof( s_Negative ) / sizeof( s_Negative[0])) );
	m_iNegativeFormat = i; 
}

////////////////////////////////////////////////////////////////////////////////
// CGXBCurrencyEdit implementation

CGXBCurrencyEdit::CGXBCurrencyEdit() :
	m_bNegative(FALSE),
	m_bCanUndo(FALSE),
	m_bParseOnSetText(TRUE),
	m_bRedraw(TRUE),
	m_bMouseSelect(FALSE),
	m_bOverstrike(FALSE),
	m_dValue(0.0),
	m_hFont(NULL),
	m_iCaretPos(0),
	m_uiRightMargin(0),
	m_uiLeftMargin(0),
	m_bRotateWhileAtEnd(FALSE),
	m_bSeparatorsInLeadingSpaces(FALSE)
{
	m_pFormat = new Format;
}

CGXBCurrencyEdit::CGXBCurrencyEdit(CGXBCurrencyEdit::Format* pFmt) :
	m_bNegative(FALSE),
	m_bCanUndo(FALSE),
	m_bParseOnSetText(TRUE),
	m_bRedraw(TRUE),
	m_bMouseSelect(FALSE),
	m_bOverstrike(FALSE),
	m_dValue(0.0),
	m_hFont(NULL),
	m_iCaretPos(0),
	m_uiRightMargin(0),
	m_uiLeftMargin(0),
	m_pFormat(pFmt),
	m_bRotateWhileAtEnd(FALSE),
	m_bSeparatorsInLeadingSpaces(FALSE)
{
}

CGXBCurrencyEdit::~CGXBCurrencyEdit()
{
	delete m_pFormat;
}

BEGIN_MESSAGE_MAP(CGXBCurrencyEdit, CGXBDropEdit)

	//{{AFX_MSG_MAP(CGXBCurrencyEdit)
	ON_WM_PAINT()
	ON_WM_RBUTTONUP()
	ON_WM_SETFOCUS()
	ON_WM_LBUTTONDOWN()
	ON_WM_KILLFOCUS()
	ON_WM_KEYDOWN()
	ON_WM_GETDLGCODE()
	ON_WM_CHAR()
	ON_WM_SYSKEYDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	
	// Message overrides not provided by ClassWizard.
	
	ON_MESSAGE(EM_UNDO, OnUndo)
	ON_MESSAGE(EM_CANUNDO, OnCanUndo)
	ON_MESSAGE(EM_EMPTYUNDOBUFFER, OnEmptyUndoBuffer)
	ON_MESSAGE(EM_GETSEL, OnGetSel)
	ON_MESSAGE(EM_SETREADONLY, OnSetReadOnly)
	ON_MESSAGE(EM_SETSEL, OnSetSel)
	ON_MESSAGE(WM_COPY, OnCopy)
	ON_MESSAGE(WM_CUT, OnCut)
	ON_MESSAGE(WM_GETFONT, OnGetFont)
	ON_MESSAGE(WM_PASTE, OnPaste)
	ON_MESSAGE(WM_SETFONT, OnSetFont)
	ON_MESSAGE(WM_SETTEXT, OnSetText)
	ON_MESSAGE(WM_UNDO, OnUndo)
	ON_MESSAGE(EM_SETMARGINS, OnSetMargins)

	// Menu command handlers for right-button popup menu.

	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_COMMAND(ID_EDIT_SELECT_ALL, OnEditSelectAll)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)

END_MESSAGE_MAP()


// Creates the popup menu for display upon a right click; override this
// method to provide your own custom menu.

CMenu* CGXBCurrencyEdit::CreatePopupMenu() const
{
	CString s;
	double d;
	BOOL bEmpty = (GetWindowTextLength() < 1), bNegative;
	BOOL bNoPaste = !GetClipboardText(s) || !m_pFormat->ParseValue(s, d, bNegative) || IsReadOnly();
	CMenu* pPopupMenu = new CMenu;
	pPopupMenu->CreatePopupMenu();
	pPopupMenu->AppendMenu(GrayIf(!m_bCanUndo || IsReadOnly()), ID_EDIT_UNDO, _T("&Undo\tCtrl+Z"));
	pPopupMenu->AppendMenu(MF_SEPARATOR);
	pPopupMenu->AppendMenu(GrayIf(bEmpty || !HasSel() || IsReadOnly()), ID_EDIT_CUT, _T("Cu&t\tCtrl+X"));
	pPopupMenu->AppendMenu(GrayIf(bEmpty || !HasSel()), ID_EDIT_COPY, _T("&Copy\tCtrl+C"));
	pPopupMenu->AppendMenu(GrayIf(bNoPaste), ID_EDIT_PASTE, _T("&Paste\tCtrl+V"));
	pPopupMenu->AppendMenu(GrayIf(bEmpty || !HasSel() || IsReadOnly()), ID_EDIT_CLEAR, _T("&Delete\tDelete"));
	pPopupMenu->AppendMenu(MF_SEPARATOR);
	pPopupMenu->AppendMenu(GrayIf(bEmpty), ID_EDIT_SELECT_ALL, _T("Select &All"));
	return pPopupMenu;
}

// Deletes the popup menu; override this method when supplying a custom
// popup menu that requires resources that need to be freed.

void CGXBCurrencyEdit::DeletePopupMenu(CMenu* p) const
{
	delete p;
}

// Saves current state information to the undo buffer.

void CGXBCurrencyEdit::SaveDataForUndo(LPCTSTR p, int iCaret)
{
	if (p == NULL)
		GetWindowText(m_Undo.strText);
	else
		m_Undo.strText = p;
	if (iCaret == -1)
		m_Undo.iCaretPos = m_iCaretPos;
	else
		m_Undo.iCaretPos = iCaret;
	if (HasSel())
		m_Undo.sel = m_Sel;
	else
		m_Undo.sel.Clear();
	m_bCanUndo = TRUE;
}

// Returns true if the control can replace the specified edit control.

BOOL CGXBCurrencyEdit::Initialize(CWnd* pwndParent, UINT uiControlID)
{
	CWnd* pWnd = pwndParent->GetDlgItem(uiControlID);
	if (IsEditControl(pWnd))
	{
		// Get an edit control pointer and make sure the window class 
		// is registered.

		LPCTSTR PCSZ_CLASSNAME = _T("CGXBCurrencyEdit");
		const UINT CLASS_STYLE = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
		CEdit* pwndEdit = (CEdit*)pWnd;
		HCURSOR hcurIBeam = AfxGetApp()->LoadStandardCursor(IDC_IBEAM);
		VERIFY(AfxRegisterNamedWndClass(PCSZ_CLASSNAME, CLASS_STYLE,
										hcurIBeam, NULL, NULL));
		
		// Get the original font, the previous window in the tab order,
		// the control ID, the styles, and the rectangle to use for the
		// call to create (in parent client-area coordinates).
		
		CFont* pFont = pwndEdit->GetFont();
		CWnd* pwndPrev = pwndEdit->GetWindow(GW_HWNDPREV);
		UINT uiID = pwndEdit->GetDlgCtrlID();
		DWORD dwStyle = pwndEdit->GetStyle();
		DWORD dwExStyle = pwndEdit->GetExStyle();
		CRect rc;
		pwndEdit->GetWindowRect(&rc);
		pwndParent->ScreenToClient(&rc);

		// If you're looking at this code because the following ASSERT
		// was tripped, it means the edit control has a style not supported
		// by the currency edit.  This is just a debugging aid; the 
		// unsupported styles will be stripped before continuing.

		const UINT UNSUPPORTED_STYLES = ES_MULTILINE | ES_LOWERCASE |
										ES_UPPERCASE | ES_AUTOVSCROLL |
										ES_PASSWORD | ES_WANTRETURN;
		ASSERT(!(dwStyle & UNSUPPORTED_STYLES));
		dwStyle &= ~UNSUPPORTED_STYLES;

		// At this point, we no longer need the original window and may
		// safely destroy it.

		pwndEdit->DestroyWindow();

		// Convert the current value for the original window text.

		CString s;
		m_pFormat->FormatValue(m_dValue, s, m_bNegative);


		// Create the window from the parameters obtained above.

		if(CWnd::CreateEx(dwExStyle, PCSZ_CLASSNAME, s, dwStyle,
						  rc.left, rc.top, rc.Width(), rc.Height(), 
						  pwndParent->GetSafeHwnd(), (HMENU)(SEC_UINT)uiID))
		{
			SetFont(pFont);
			SetWindowPos(pwndPrev, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
			return TRUE;
		}
	}

	return FALSE;
}

// Sets the control text without allowing the automatic parsing that
// normally occurs upon receipt of a WM_SETTEXT.

void CGXBCurrencyEdit::SetWindowTextNoParse(LPCTSTR p)
{
	BOOL bOld = m_bParseOnSetText;
	m_bParseOnSetText = FALSE;
	SetWindowText(p);
	m_bParseOnSetText = bOld;
}


void CGXBCurrencyEdit::GetValue(double& d) const
{
	if (IsNegative())
		d = -m_dValue;
	else
		d = m_dValue;
}


// Sets the value directly, optionally updating the control's display.

void CGXBCurrencyEdit::SetValue(double d, BOOL bRedraw)
{
	if (d < 0.0)
		SetValue(-d, TRUE, bRedraw);
	else
		SetValue(d, FALSE, bRedraw);
}

void CGXBCurrencyEdit::SetValue(double d, BOOL bNegative, BOOL bRedraw)
{
	if (m_dValue != d || m_bNegative != bNegative)
	{
		m_dValue = d;
		m_bNegative = bNegative;

		// If the window exists, convert the value to text based
		// on the current formatting and set the window text.

		if (GetSafeHwnd())
		{
			CString s;
			m_pFormat->FormatValue(m_dValue, s, m_bNegative);
			SaveDataForUndo();
			SetWindowTextNoParse(s);
			if (bRedraw)
				QueueRedraw();
		}
	}
}

// Sets the format object parameters.

void CGXBCurrencyEdit::SetFormat(const CGXBCurrencyEdit::Format& f)
{
	if (*m_pFormat != f)
	{
		*m_pFormat = f;

		// If the window exists, convert the value to text based
		// on the current formatting and set the window text.

		if (GetSafeHwnd())
		{
			CString s;
			m_pFormat->FormatValue(m_dValue, s, m_bNegative);
			SetWindowTextNoParse(s);
		}

		QueueRedraw();
	}
}

// Gets the format object parameters.

void CGXBCurrencyEdit::GetFormat(CGXBCurrencyEdit::Format& f)
{
	f = *m_pFormat;
}

// Retrieves the color to use when drawing the control background.

COLORREF CGXBCurrencyEdit::GetBackgroundColor() const
{
	// If we're enabled, get the custom background color from the
	// format member; if it has none, use the 3D face color if read-
	// only, else use the default window background color.  If we're
	// disabled, we always use the 3D button face color

	COLORREF cr;
	if (IsWindowEnabled())
	{
		if (!m_pFormat->GetBackgroundColor(cr))
			cr = GetSysColor(IsReadOnly() ? COLOR_3DFACE : COLOR_WINDOW);
	}
	else
	{
		cr = GetSysColor(COLOR_3DFACE);
	}

	return cr;
}

// Retrieves the color to use when drawing the control text.

COLORREF CGXBCurrencyEdit::GetTextColor() const
{
	// Determining the correct text color requires a little thought.
	// If we're enabled, we check if the format member has a custom
	// color based on the sign of the value; if not, we simply use the
	// default window text color.  Otherwise, we need to check if we're
	// a 3D control.  If so, use the 3D shadow color; if not, we simply
	// use the gray text color.

	COLORREF cr;
	double dValue;
	GetValue(dValue);
	if (IsWindowEnabled())
	{
		BOOL bHasCustomColor;
		if (dValue < 0.0)
			bHasCustomColor = m_pFormat->GetNegativeColor(cr);
		else
			bHasCustomColor = m_pFormat->GetPositiveColor(cr);

		if (!bHasCustomColor)
			cr = GetSysColor(COLOR_WINDOWTEXT);
	}
	else if (GetExStyle() && WS_EX_CLIENTEDGE)
	{
		cr = GetSysColor(COLOR_3DSHADOW);
	}
	else
	{
		cr = GetSysColor(COLOR_GRAYTEXT);
	}

	// If you're reading this code because the following assert just
	// tripped, it means the text will be rendered in the very same color
	// as the background.  This could (obviously) be a problem...

	ASSERT(cr != GetBackgroundColor());
	return cr;
}

// Erases the control background on the specified DC.

void CGXBCurrencyEdit::EraseBackground(CDC* pDC)
{
	// Instantiate a brush, get the client rectangle, adjust the
	// right and bottom to work around GDI conventions, draw the
	// rectangle, and return success.

	CBrush br(GetBackgroundColor());
	CRect rc;
	GetClientRect(&rc);
	rc.InflateRect(1, 1);
	CBrush* pbrOld = pDC->SelectObject(&br);
	pDC->Rectangle(rc);
	pDC->SelectObject(pbrOld);
}

// Checks the styles and returns the appropriate enumerated type.

CGXBCurrencyEdit::Align CGXBCurrencyEdit::GetAlignment() const
{
	DWORD dwStyle = GetStyle();
	if (dwStyle & ES_RIGHT)
		return right;
	else if (dwStyle & ES_CENTER)
		return center;
	else
		return left;
}

// Sets the appropriate style based on the enumerated type.

void CGXBCurrencyEdit::SetAlignment(CGXBCurrencyEdit::Align a)
{
	ASSERT(a == left || a == center || a == right);
	static DWORD dwStyle[] = {ES_LEFT, ES_CENTER, ES_RIGHT};
	ModifyStyle((ES_LEFT | ES_CENTER | ES_RIGHT), dwStyle[a]);
}

// Calculates the portion of the client area in which text will
// actually appear.


void CGXBCurrencyEdit::CalculateTextRect(CRect& rc)
{
	CString s;
	GetWindowText(s);
	CSize sizeText;
	CRect rcClient;
	GetClientRect(&rcClient);

	// Adjust rectangle for margins.

	rcClient.left += m_uiLeftMargin;
	rcClient.right -= m_uiRightMargin;

	{ // BLOCK DC
		CClientDC DC(this);
		CFont* pfontOld = DC.SelectObject(GetFont());
		sizeText = DC.GetTextExtent(s);
		DC.SelectObject(pfontOld);
	} // FREE DC

	CSize sizeBorder(GetSystemMetrics(SM_CXBORDER), 
					 GetSystemMetrics(SM_CYBORDER));
	rc.SetRect(rcClient.left, sizeBorder.cy, rcClient.right,
			   sizeBorder.cy + sizeText.cy);

	Align a = GetAlignment();
	if (a == left)
		rc.left += sizeBorder.cx;
	else if (a == center)
		rc.left = rcClient.CenterPoint().x - (sizeText.cx / 2);
	else
		rc.left = rcClient.right - sizeBorder.cx - sizeText.cx;
	rc.right = rc.left + sizeText.cx;
}

// Moves the caret, optionally updating the selection, to a position
// in front of the specified character.
void CGXBCurrencyEdit::MoveCaret(int iChar, BOOL bUpdateSel)
{
	CString s;
	GetWindowText(s);
	BOOL bSelecting = IsKeyDown(VK_SHIFT) || IsMouseSelecting();

	if (-1 < iChar && iChar <= s.GetLength())
	{
		CRect rcText;
		CalculateTextRect(rcText);
		int x = rcText.left;

		if (iChar > 0)
		{
			CSize sizeText;
			CClientDC DC(this);
			CFont* pfontOld = DC.SelectObject(GetFont());
			sizeText = DC.GetTextExtent(s.Left(iChar));
			DC.SelectObject(pfontOld);
			x += sizeText.cx;
		}

		if (bUpdateSel)
		{
			if (HasSel())
			{
				if (bSelecting)
					SetSel(m_Sel.iStart, iChar);
				else
					SetSelNone();
			}
			else if (bSelecting)
			{
				SetSel(m_iCaretPos, iChar);
			}
		}

		SetCaretPos(CPoint(x, rcText.top));
		m_iCaretPos = iChar;
	}
	else
	{
		// If we have been asked to move the caret to an invalid
		// location and we are supposed to update the selection,
		// we must remove the selection.

		if (bUpdateSel && !bSelecting)
			SetSelNone();
	}
}

// Performs an insert operation using the specified text.
// changed based on customer feedback

void CGXBCurrencyEdit::DoInsert(LPCTSTR pcsz)
{
	// We do nothing if the control is read-only.

	if (IsReadOnly())
		return;

	// Otherwise, move the caret to the number and start initializing
	// necessary variables.

	int iOldCaret = m_iCaretPos;
	MoveCaretToNumber();
	CString s, strNew;
	GetWindowText(s);
	int iFirst, iLast;
	int iFractionalDigits = m_pFormat->GetFractionalDigits();
	int iDecimalDigits = m_pFormat->GetDecimalDigits();
	VERIFY(m_pFormat->FindFirstAndLastDigits(s, iFirst, iLast));
	BOOL bAtEnd = (m_iCaretPos > iLast);
	int iIndex = m_pFormat->FindDecimalSeparator(s);
	int iLength = s.GetLength();

	// The following code handles certain bizarre special cases that
	// come with supporting overstrike mode when there is no selection
	// and the caret position is to the left of the decimal separator.

	if (IsOverstrikeEnabled() && !HasSel() 
		&& ((m_iCaretPos <= iIndex) || (iIndex == -1 && m_iCaretPos < iLength)))  
	{
		// If the caret is at the decimal point or at a thousand
		// separator, move it to the next number.

		if ((m_iCaretPos == iIndex) || 
			(s.GetAt(m_iCaretPos) == m_pFormat->GetThousandSeparator()))
			m_iCaretPos++;
	}

	if (HasSel())
	{
		// If we have a selection, replace the current selection with the
		// insertion contents and hope for the best.

		ReplaceSelString(pcsz, strNew);
	}
	else if (iIndex > -1 && m_iCaretPos > iIndex)
	{
		if (bAtEnd)
		{
			// When inserting after the decimal point, we always assume
			// that the incoming text is nothing but digits.

			ASSERT(CountDigits(pcsz) == lstrlen(pcsz));

			// Get the integral portion of the number and add the new
			// characters as if they had been typed one at a time, each
			// rotating the fractional digits to the left.

			// OG Change: if you dont want the fraction to rotate when entering digits from the 
			// last position, do the following change...
			// 2/12/98...
			strNew = s;
			if(m_bRotateWhileAtEnd)
			{
				int iInsertLength = lstrlen(pcsz);
				strNew = s.Left(iIndex + 1);
				if (iInsertLength > iFractionalDigits)
					strNew += &pcsz[iInsertLength - iFractionalDigits];
				else
				{
					strNew += s.Mid(iIndex + iInsertLength + 1, 
								iFractionalDigits - iInsertLength);
					strNew += pcsz;
				}
			}
		}
		else
		{
			// We determine how many of the existing digits to keep (if any)
			// and append the string to be inserted. If the number of digits
			// to keep is positive, we appened them. if it is negative, this
			// indicates that we need to truncate the string.

			int iKeep = iLength - m_iCaretPos - lstrlen(pcsz);
			strNew = s.Left(m_iCaretPos) + pcsz;
			if (iKeep > 0)
				strNew += s.Right(iKeep);
			else if (iKeep < 0)
				strNew = strNew.Left(strNew.GetLength() + iKeep);
		}
	}
	else
	{
		// This path will be taken if the caret is to the left of
		// the decimal point. Thus, we check to see if the control
		// has a fixed number of digits and the caret is not at the
		// decimal point. If this is the case, or if overstrike mode
		// is enabled, then we replace the character at the given 
		// position.

		if (IsOverstrikeEnabled() 
			&& ((m_iCaretPos <= iIndex) || (iIndex == -1 && m_iCaretPos < iLength))) 
		{
			strNew = s;

			strNew.SetAt(m_iCaretPos, *pcsz);

			// The following line of code should probably not be
			// here for sake of consistency, but it is the best way
			// to make sure that the caret position gets incremented
			// during an insert.

			m_iCaretPos++;
		}
		else
		{
			if (m_iCaretPos > 0)
				strNew = s.Left(m_iCaretPos) + pcsz + s.Right(iLength - m_iCaretPos);
			else
				strNew = pcsz + s;
		}
	}

	// Shove the new text into the control, letting the WM_SETTEXT
	// handler parse and validate. Then get the new text for further
	// processing and make note of the original caret position.

	SetRedraw(FALSE);
	SetWindowText(strNew);
	SetRedraw(TRUE);
	GetWindowText(strNew);

	// If the control has a selection, the final position for the 
	// caret should be constant with respect to the right side of
	// the control.

	if (HasSel())
	{
		// If the entire number is selected, we put the caret to
		// the immediate left of the decimal point.

		if (IsEntireNumberSelected())
		{
			int iIndex = m_pFormat->FindDecimalSeparator(strNew);
			if (iIndex == -1)
				m_iCaretPos = strNew.GetLength();
			else if (iDecimalDigits == 0)
				m_iCaretPos = iIndex + 1;
			else
				m_iCaretPos = iIndex;
		}
		else
		{
			int iFromRight = iLength - max(m_iCaretPos, m_Sel.iStart);
			m_iCaretPos = strNew.GetLength() - iFromRight;
		}
	}
	else //if (s != strNew)
	{
		int iIndex = m_pFormat->FindDecimalSeparator(strNew);
		if (iIndex > -1 && m_iCaretPos > iIndex)
		{
			int iNewLength = strNew.GetLength();
			if (m_iCaretPos < iNewLength)
			{
				m_iCaretPos += CountDigits(pcsz);
				if (m_iCaretPos > iNewLength)
					m_iCaretPos = iNewLength;
			}
		}
		else
		{
			// Otherwise, the caret should move one to the right;
			// however, because the insert may have added a thousand 
			// separator, it's important to make sure the caret 
			// maintains its position relative to the end of the 
			// string.  Thus, we must get the new text and move the 
			// caret based on the actual increase in size.

			int iIncrement = strNew.GetLength() - iLength;
			m_iCaretPos += iIncrement;
		}
	}

	// Clip the caret to behind the last fractional digit to avoid
	// it being considered outside the numeric portion, thus
	// requiring a move prior to the next insert.

	VERIFY(m_pFormat->FindFirstAndLastDigits(strNew, iFirst, iLast));
	if (m_iCaretPos > (iLast + 1))
		m_iCaretPos = iLast + 1;
	MoveCaret(m_iCaretPos);

	// If the text actually changed, save the original data into
	// the undo buffer.  If a selection was present, clear it.
	// If either operation actually happened, queue a redraw

	BOOL bChanged = (s != strNew);
	if (bChanged)
	{
		SaveDataForUndo(s, iOldCaret);
		NotifyParent(EN_UPDATE);
	}
	if (HasSel())
	{
		m_Sel.Clear();
		QueueRedraw();
	}
	if (bChanged)
	{
		QueueRedraw();
		NotifyParent(EN_UPDATE);
	}
}

// Deletes the selection (if any), or deletes a single character in
// front of the caret position.


void CGXBCurrencyEdit::DoDelete()
{
	// We do nothing if the control is read-only, or if the caret
	// is at the end of the text and we have no selection.

	BOOL bHasSel = HasSel();
	if (IsReadOnly() || ((m_iCaretPos >= GetWindowTextLength()) && !bHasSel))
		return;
	
	CString s;
	GetWindowText(s);
	int iLength = s.GetLength();
	if (bHasSel || (iLength > 0 && m_iCaretPos < iLength))
	{
		int iOldCaret = m_iCaretPos;
		int iIndex = m_pFormat->FindDecimalSeparator(s);

		// If the control has a selection, the final digit index for the 
		// caret should be based on the left side of the selection.

		int iDigitIndex;
		if (bHasSel)
			iDigitIndex = GetDigitAfterIndex(min(m_Sel.iStart, m_iCaretPos), s);
		else
		{
			if (!_istdigit(s.GetAt(m_iCaretPos)))
			{
				int iDoomedDigit = GetDigitAfterIndex(m_iCaretPos, s);
				m_iCaretPos = GetDigitIndex(iDoomedDigit, s);
			}
			iDigitIndex = GetDigitAfterIndex(m_iCaretPos, s);
		}

		CString strNew;
		int iNewCaretPos = -1;
		if (bHasSel)
			ReplaceSelString(NULL, strNew);
		else if (iIndex > -1 && m_iCaretPos > iIndex)
		{
			strNew = s;
			strNew.SetAt(m_iCaretPos, _T('0'));
			iNewCaretPos = m_iCaretPos + 1;
		}
		else if (m_iCaretPos > 0)
			strNew = s.Left(m_iCaretPos) + s.Mid(m_iCaretPos + 1);
		else
			strNew = s.Mid(1);

		// If we are deleting the last digit in the control, we should
		// have a string without any digits; in this case, set the value
		// to zero.

		if (CountDigits(strNew) == 0)
			strNew += '0';

		SetRedraw(FALSE);
		SetWindowText(strNew);
		SetRedraw(TRUE);
		GetWindowText(strNew);

		// If the new control value is zero, then place the caret where it
		// can immediately be used to enter data. Otherwise, we should place 
		// the caret in front of the same digit number it used to precede.

		if (m_dValue == 0.0)
		{
			iIndex = m_pFormat->FindDecimalSeparator(strNew);
			if (iIndex == -1)
			{
				int iFirst, iLast;
				VERIFY(m_pFormat->FindFirstAndLastDigits(strNew, iFirst, iLast));
				iNewCaretPos = iLast + 1;
			}
			else
			{
				iNewCaretPos = iIndex;
			}
		}
		else
		{
			if (iNewCaretPos == -1)
				iNewCaretPos = GetDigitIndex(iDigitIndex, strNew);
			if (iNewCaretPos == -1)
				iNewCaretPos = strNew.GetLength();
		}

		MoveCaret(iNewCaretPos);

		// If the text actually changed, save the original data into
		// the undo buffer.

		BOOL bChanged = (s != strNew);
		if (bChanged)
		{
			SaveDataForUndo(s, iOldCaret);
			NotifyParent(EN_UPDATE);
			QueueRedraw();
			NotifyParent(EN_CHANGE);
		}

		if (bHasSel)
			SetSelNone();
	}
}

// Deletes the selection (if any), or deletes a single character
// behind the caret position.

void CGXBCurrencyEdit::DoBackspace()
{
	if (IsReadOnly())
		return;

	// If the control has a selection, this is exactly equivalent to 
	// performing a delete operation.

	if (HasSel())
	{
		DoDelete();
		return;
	}

	// Make sure that the caret is within the number.

	CString s;
	GetWindowText(s);
	int iFirst, iLast;
	VERIFY(m_pFormat->FindFirstAndLastDigits(s, iFirst, iLast));
	if (m_iCaretPos <= iFirst)
		return;

	// Then make sure that the caret is to the right of a digit and
	// not some other character.

	int iPrevDigit = GetDigitBeforeIndex(m_iCaretPos, s);
	int iPrevDigitIndex = GetDigitIndex(iPrevDigit, s);
	if (iPrevDigitIndex == -1)
		return;
	int iOldCaret = m_iCaretPos;
	m_iCaretPos = iPrevDigitIndex + 1;

	// The next step is to find the first and last digit locations as
	// a prelude to determining where the caret lies within them.

	CString strNew;
	int iIndex = m_pFormat->FindDecimalSeparator(s);
	int iNewCaretPos = m_iCaretPos - 1;

	if (iIndex > -1 && m_iCaretPos > iIndex)
	{
		// If the caret is within the fractional portion of
		// the number, replace the digit to its immediate left
		// with a zero and move it to the left of that digit.

		strNew = s;
		strNew.SetAt(iNewCaretPos, _T('0'));
	}
	else
	{
		// The caret should move one to the left; however, 
		// if the delete causes a thousand separator to 
		// disappear, the caret can appear to move one extra 
		// character to the left unless we adjust it.

		strNew = s.Left(m_iCaretPos - 1) + s.Mid(m_iCaretPos);

		if (m_pFormat->GetDecimalDigits() != -1)
			iNewCaretPos = m_iCaretPos;
		else
		{
			iNewCaretPos = GetDigitIndex(--iPrevDigit, strNew);
			if (iPrevDigit > -1)
				iNewCaretPos++;
		}
	}

	// If we are deleting the last digit in the control, we should
	// have a string without any digits; in this case, set the value
	// to zero.

	if (CountDigits(strNew) == 0)
		strNew += '0';

	SetRedraw(FALSE);
	SetWindowText(strNew);
	SetRedraw(TRUE);
	GetWindowText(strNew);

	// If the new control value is zero, then place the caret where it
	// can immediately be used to enter data. Otherwise, we should place
	// the caret to the immediate right of the previous digit. If there
	// are no previous digits, then it should be to the left of the 
	// first digit.

	if (m_dValue == 0.0)
	{
		iIndex = m_pFormat->FindDecimalSeparator(strNew);
		if (iIndex == -1)
		{
			VERIFY(m_pFormat->FindFirstAndLastDigits(strNew, iFirst, iLast));
			iNewCaretPos = iLast + 1;
		}
		else if (m_pFormat->GetDecimalDigits() == 0)
			iNewCaretPos = iIndex + 1;
		else
			iNewCaretPos = iIndex;
	}
	//else
	//{
	//	iNewCaretPos = GetDigitIndex(--iPrevDigit, strNew);
	//	if (iPrevDigit > -1)
	//		iNewCaretPos++;
	//}

	MoveCaret(iNewCaretPos);

	// If the text actually changed, save the original data into
	// the undo buffer.

	if (s != strNew)
	{
		SaveDataForUndo(s, iOldCaret);
		NotifyParent(EN_UPDATE);
		QueueRedraw();
		NotifyParent(EN_CHANGE);
	}
}

// Converts a point in client coordinates to a nearest caret position.

int CGXBCurrencyEdit::PointToCaretPos(const CPoint& pt)
{
	CString s;
	GetWindowText(s);
	int i = 0, iTotal;

	{ // BLOCK DC
		CClientDC DC(this);
		CFont* pfontOld = DC.SelectObject(GetFont());
		CRect rcText;
		CalculateTextRect(rcText);
		iTotal = rcText.left;

		for (LPCTSTR p = s; *p != _T('\0'); p++)
		{
			CSize sizeChar(DC.GetTextExtent(p, 1));
			if (pt.x < iTotal + sizeChar.cx / 2)
				break;
			iTotal += sizeChar.cx;
			i++;
		}
		DC.SelectObject(pfontOld);
	} // FREE DC

	return i;
}

// Starts the editing process (i.e. createsd the caret, moves it into
// position, etc.

void CGXBCurrencyEdit::StartEdit(int iCaretPos)
{
	TEXTMETRIC tm;
	{ // BLOCK DC
		CClientDC DC(this);
		CFont* pfontOld = DC.SelectObject(GetFont());
		DC.GetTextMetrics(&tm);
		DC.SelectObject(pfontOld);
	} // FREE DC

	int cx = GetSystemMetrics(SM_CXBORDER);
	VERIFY(::CreateCaret(GetSafeHwnd(), NULL, cx, tm.tmHeight));
	MoveCaret(iCaretPos);
	ShowCaret();
}


void CGXBCurrencyEdit::StopEdit()
{
	SetSelNone();
	::DestroyCaret();
}

// Returns true if the control has the ES_READONLY style.

BOOL CGXBCurrencyEdit::IsReadOnly() const
{
	return !!(GetStyle() & ES_READONLY);
}

// Sets or clears the ES_READONLY style depending upon the argument.

void CGXBCurrencyEdit::SetReadOnly(BOOL b)
{
	if (IsReadOnly() != b)
	{
		ModifyStyle(ES_READONLY, b ? ES_READONLY : 0);
		QueueRedraw();
	}
}

// Sets the control selection based on the specified start and stop
// parameters.  The parameters do not need to be normalized (i.e.
// start can be greater than stop), and certain combinations have
// special meanings:
//
// -1, 0 means no selection
// 0, -1 means select everything

BOOL CGXBCurrencyEdit::SetSel(int iStart, int iStop)
{
	int iLeft = min(iStart, iStop);
	int iRight = max(iStart, iStop);
	int iLength = GetWindowTextLength();
	int iCaret;

	// -1,0 means clear the selection; 0,-1 means select everything;
	// otherwise, validate the range.

	if (iStart == -1 && iStop == 0)
		m_Sel.Set(iStart, iStop), iCaret = -1;
	else if (iStart == 0 && iStop == -1)
		m_Sel.Set(iStart, iStop), iCaret = iLength;
	else if (-1 < iLeft && iRight <= iLength)
		m_Sel.Set(iStart, iStop), iCaret = iStop;
	else
		return FALSE;

	// If we're here, we have a valid selection range and can
	// simply update the caret and queue a redraw operation
	// minus background repaint.

	MoveCaret(iCaret);
	QueueRedraw(FALSE);
	return TRUE;
}

// Returns the control text, exchanging the contents of the selection 
// for the given replacement string.

void CGXBCurrencyEdit::ReplaceSelString(LPCTSTR pcszNew, CString& str) const
{
	// If all is selected, return the new string.

	if (m_Sel.iStart == 0 && m_Sel.iStop == -1)
		str = pcszNew;
	else
	{
		CString s;
		GetWindowText(s);
		SELDATA sel(m_Sel);
		sel.Normalize();
		int iLength = s.GetLength();

		str.Empty();
		if (sel.iStart > 0)
			str += s.Left(sel.iStart);
		if (pcszNew != NULL)
			str += pcszNew;
		if (sel.iStop < iLength)
			str += s.Right(iLength - sel.iStop);
	}
}

// Returns just the selected text (if any).

void CGXBCurrencyEdit::GetSelectedText(CString& str) const
{
	if (HasSel())
	{
		CString s;
		GetWindowText(s);
		SELDATA sel(m_Sel);
		sel.Normalize();

		if (m_Sel.iStart == 0 && m_Sel.iStop == -1)
			str = s;
		else
			str = s.Mid(sel.iStart, sel.iStop - sel.iStart);
	}
	else
		str.Empty();
}

// Draws a vertical separator line at the specified horizontal
// position on the given DC.

void CGXBCurrencyEdit::DrawDecimalSeparatorLine(CDC& DC, int x)
{
	CRect r;
	GetClientRect(&r);
	COLORREF cr;
	if (IsReadOnly())
		cr = GetSysColor(COLOR_3DSHADOW);
	else
		cr = m_pFormat->GetDecimalSeparatorLineColor();
	CPen p(PS_SOLID, 0, cr);
	CPen* ppenOld = DC.SelectObject(&p);
	DC.MoveTo(x, 0);
	DC.LineTo(x, r.bottom + 1);
	DC.SelectObject(ppenOld);
}

// Performs painting of the control's client area upon the specified
// DC.  This allows the actual WM_PAINT handler to draw to an offscreen
// bitmap and BitBlt if sufficient system resources are available.

void CGXBCurrencyEdit::PaintingCore(CDC& DC)
{
	EraseBackground(&DC);

	// Prep the DC for drawing the text.

	CFont* pFont = GetFont();
	CFont* pfontOld = DC.SelectObject(pFont);
	COLORREF cr = GetTextColor();
	DC.SetTextColor(cr);
	DC.SetBkMode(TRANSPARENT);

	// Calculate the rectangle in which the text is to be drawn,
	// get the text, draw it, and restore the DC.

	CRect rcText;
	UINT uiFlags = DT_SINGLELINE | DT_TOP | DT_NOPREFIX;
	CalculateTextRect(rcText);
	CString s;
	GetWindowText(s);

	int iVLine = -1;
	if (m_pFormat->IsDecimalSeparatorLineEnabled())
	{
		int iIndex = m_pFormat->FindDecimalSeparator(s);
		if (iIndex > -1)
		{
			s.SetAt(iIndex, _T(' '));
			iVLine = rcText.left;
			iVLine += DC.GetTextExtent(s.Left(iIndex)).cx;
			iVLine += DC.GetTextExtent(_T(" "), 1).cx / 2;
		}
	}

	if (HasSel())
	{
		int iLeft, iRight, iLength = s.GetLength();
		SELDATA sel(m_Sel);
		if (sel.iStop == -1)
			sel.iStop = iLength;
		sel.Normalize();

		// If text shows prior or after to the selection, draw it.

		if (sel.iStart > 0)
		{
			CString strLeft(s.Left(sel.iStart));
			iLeft = DC.GetTextExtent(strLeft).cx;
			DC.DrawText(strLeft, rcText, uiFlags | DT_LEFT);
		}
		else
		{
			iLeft = 0;
		}

		if (sel.iStop < iLength)
		{
			CString strRight(s.Right(iLength - sel.iStop));
			iRight = DC.GetTextExtent(strRight).cx;
			DC.DrawText(strRight, rcText, uiFlags | DT_RIGHT);
		}
		else
		{
			iRight = 0;
		}

		// Configure the DC for drawing the selected text.

		DC.SetBkMode(OPAQUE);
		DC.SetBkColor(GetSysColor(COLOR_HIGHLIGHT));
		DC.SetTextColor(GetSysColor(COLOR_HIGHLIGHTTEXT));
		int iNumChars = sel.iStop - sel.iStart;
		CString strSel(s.Mid(sel.iStart, iNumChars));
		rcText.left += iLeft;
		rcText.right -= iRight;
		DC.DrawText(strSel, rcText, uiFlags | DT_LEFT); 
	}
	else
	{
		DC.DrawText(s, rcText, uiFlags | DT_LEFT);
	}

	if (iVLine != -1)
		DrawDecimalSeparatorLine(DC, iVLine);
	DC.SelectObject(pfontOld);
}

BOOL CGXBCurrencyEdit::IsEntireNumberSelected(BOOL* pbMore) const
{
	if (pbMore != NULL)
		*pbMore = FALSE;
	
	if (m_Sel.iStart == 0 && m_Sel.iStop == -1)
	{	
		if (pbMore != NULL)
			*pbMore = TRUE;
		return TRUE;
	}
	else if (m_Sel.iStart == -1 && m_Sel.iStop == 0)
		return FALSE;

	// Find the first and last characters in the numeric portion.

	CString s;
	GetWindowText(s);
	int iFirst, iLast;
	if (!m_pFormat->FindFirstAndLastDigits(s, iFirst, iLast))
		return FALSE;

	SELDATA sel(m_Sel);
	sel.Normalize();

	// If the caller wants to know if the selection goes outside the
	// number itself (i.e., if "more" than the number is selected),
	// set the flag appropriately.

	if (pbMore != NULL)
		*pbMore = (sel.iStart < iFirst || (sel.iStop - 1) > iLast);

	return sel.iStart <= iFirst && sel.iStop >= iLast;
}

BOOL CGXBCurrencyEdit::ShowCalculator()
{
	GXGetAppData()->m_bDiscardNcActivate = TRUE;

	CRect rc;
	GetWindowRect(&rc);
	CGXBPopupCalculator* pCalc = new CGXBPopupCalculator;
	pCalc->SetValue(m_dValue);
	pCalc->m_bAutoDelete = TRUE;
	if (pCalc->Create(GX_PCS_DESTROY_ON_EQUALS | WS_VISIBLE | WS_POPUP, rc, this))
	{
		double dCurrentValue;
		GetValue(dCurrentValue);
		pCalc->SetOwner(this);
		pCalc->SetValue(dCurrentValue);
		GXGetAppData()->m_bDiscardNcActivate = FALSE;
		return TRUE;
	}
	GXGetAppData()->m_bDiscardNcActivate = FALSE;
	return FALSE;
}

void CGXBCurrencyEdit::SetMargins(UINT nLeft, UINT nRight)
{
	m_uiRightMargin = nRight;
	m_uiLeftMargin = nLeft;
	if (GetSafeHwnd())
		InvalidateRect(NULL);
}

void CGXBCurrencyEdit::NotifyParent(UINT uiCode)
{
	CWnd* pwndParent = GetParent();
	if (pwndParent != NULL)
	{
		WPARAM w = MAKELONG(GetDlgCtrlID(), uiCode);
		LPARAM l = reinterpret_cast<LPARAM>(GetSafeHwnd());
		pwndParent->SendMessage(WM_COMMAND, w, l);
	}
}

void CGXBCurrencyEdit::HandleNegativeSignKey()
{
	// If the entire number (or more) is selected, then assume
	// that the user wants a negative number; otherwise, assume
	// that the user wants to toggle the sign.

	BOOL bMore = FALSE;
	BOOL bEntireNumberSelected = IsEntireNumberSelected(&bMore);
	m_bNegative = (bEntireNumberSelected && bMore) ? TRUE : !m_bNegative;

	// Format the new value and save the undo data.

	CString strNew, strOld;
	GetWindowText(strOld);
	m_pFormat->FormatValue(m_dValue, strNew, m_bNegative);
	SaveDataForUndo();
	SetWindowTextNoParse(strNew);

	// If the entire number and more is selected, modify the 
	// selection to exclude the negative symbol(s). This is a bit
	// of special case handling that allows the user to tab into
	// the field and easily enter a negative number. If we did not
	// modify the selection, the negative sign would be wiped out
	// with the next keypress, resulting in a negative number.

	int iFirst, iLast;
	VERIFY(m_pFormat->FindFirstAndLastDigits(strNew, iFirst, iLast));

	if (bEntireNumberSelected && bMore)
	{
		SetSel(iFirst, iLast + 1);
		MoveCaret(iLast + 1, FALSE);
	}
	else
	{
		if (HasSel())
			SetSelNone();

		int iOldFirst, iOldLast;
		VERIFY(m_pFormat->FindFirstAndLastDigits(strOld, iOldFirst, iOldLast));
		int iIncrement = iLast - iOldLast;
		m_iCaretPos += iIncrement;
		if (m_iCaretPos < 0)
			m_iCaretPos = 0;
		else if (m_iCaretPos > strNew.GetLength())
			m_iCaretPos = strNew.GetLength();
		MoveCaret(m_iCaretPos, FALSE);
	}
}

void CGXBCurrencyEdit::MoveCaretToNumber()
{
	CString s;
	GetWindowText(s);
	int iFirst, iLast;
	VERIFY(m_pFormat->FindFirstAndLastDigits(s, iFirst, iLast));

	// If the caret is within the numeric portion of the field,
	// we should assume that the user has put it there for a 
	// good reason. Thus, we leave the caret alone.

	if (iFirst <= m_iCaretPos && m_iCaretPos <= (iLast + 1))
		return;

	// Otherwise, we need to move the caret to the immediate
	// left of the decimal point or to the immediate right
	// if the number of decimal digits is set to zero.
	
	int iDecimalIndex = m_pFormat->FindDecimalSeparator(s);
	if (m_pFormat->GetDecimalDigits() == 0)
	{
		ASSERT(m_pFormat->GetFractionalDigits() > 0);
		iDecimalIndex++;
	}
	else if (iDecimalIndex == -1)
	{
		iDecimalIndex = iLast + 1;
	}
	MoveCaret(iDecimalIndex, FALSE);
}

void CGXBCurrencyEdit::ToggleOverstrikeMode()
{
	m_bOverstrike = !m_bOverstrike;
}

// This method prepares incoming text for a paste operation. If the entire
// numeric portion is selected, then it leaves the text alone. If, however,
// the incoming text is going to be appended or inserted somewhere into
// the current control value, then we remove potentially difficult characters
// (currency signs, decimal separators, etc.) before proceeding.
//
// Returns: True if paste should continue, false otherwise.

BOOL CGXBCurrencyEdit::PrepareTextForPaste(CString& strText)
{
	if (!IsEntireNumberSelected())
		RemoveAllButDigits(strText);

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CGXBCurrencyEdit message handlers
LRESULT CGXBCurrencyEdit::OnGetFont(WPARAM wParam, LPARAM lParam)
{
	wParam; // UNUSED
	lParam; // UNUSED
	return (LRESULT)m_hFont;
}

LRESULT CGXBCurrencyEdit::OnSetFont(WPARAM wParam, LPARAM lParam)
{
	// wParam = handle of new font
	// lParam = non-zero if redraw required

	m_hFont = (HFONT)wParam;
	if (lParam)
		QueueRedraw();
	return 0L;
}

LRESULT CGXBCurrencyEdit::OnSetText(WPARAM wParam, LPARAM lParam)
{
	// If the no-parse flag is set, let the default prodedure
	// give us the return value, then invalidate the client area
	// to force a redraw

	if (!m_bParseOnSetText)
	{
		LRESULT lRet = Default();
		QueueRedraw();
		return lRet;
	}

	// wParam = (not used)
	// lParam = pointer to new text

	BOOL bNegative;
	double dNewValue;
	LPCTSTR pcsz = (LPCTSTR)lParam;

	if (m_pFormat->ParseValue(pcsz, dNewValue, bNegative))
	{
		SetValue(dNewValue, bNegative, TRUE);
		return TRUE;
	}

	wParam; // UNUSED

	return FALSE;
}

LRESULT CGXBCurrencyEdit::OnPaste(WPARAM wParam, LPARAM lParam)
{
	wParam; // UNUSED
	lParam; // UNUSED

	OnEditPaste();
	return 0L;
}

LRESULT CGXBCurrencyEdit::OnCanUndo(WPARAM wParam, LPARAM lParam)
{
	wParam; // UNUSED
	lParam; // UNUSED
	return m_bCanUndo;
}

LRESULT CGXBCurrencyEdit::OnUndo(WPARAM wParam, LPARAM lParam)
{
	wParam; // UNUSED
	lParam; // UNUSED

	OnEditUndo();
	return 0L;
}

LRESULT CGXBCurrencyEdit::OnGetSel(WPARAM wParam, LPARAM lParam)
{
	// wParam = pointer to start, lParam = pointer to end
	// Note: both parameters may be null.

	SEC_DWORD* pdwStart = (SEC_DWORD*)wParam;
	SEC_DWORD* pdwEnd = (SEC_DWORD*)lParam;
	if (pdwStart != NULL)
		*pdwStart = m_Sel.iStart;
	if (pdwEnd != NULL)
		*pdwEnd = m_Sel.iStop;

	// The return value contains both values if both are less
	// than USHRT_MAX, otherwise, it's negative one.

	if (m_Sel.iStart < USHRT_MAX && m_Sel.iStop < USHRT_MAX)
		return MAKELONG(m_Sel.iStart, m_Sel.iStop);
	else
		return -1L;
}

LRESULT CGXBCurrencyEdit::OnSetSel(WPARAM wParam, LPARAM lParam)
{
	// wParam = start, lParam = end
	SetSel((int)wParam, (int)lParam);
	return 0L;
}

LRESULT CGXBCurrencyEdit::OnSetReadOnly(WPARAM wParam, LPARAM lParam)
{
	// wParam = true if read-only is desired
	BOOL bReadOnly = (BOOL)wParam;
	if (bReadOnly != IsReadOnly())
		SetReadOnly(bReadOnly);

	wParam; // UNUSED
	lParam; // UNUSED

	return TRUE;
}

LRESULT CGXBCurrencyEdit::OnEmptyUndoBuffer(WPARAM wParam, LPARAM lParam)
{
	m_bCanUndo = FALSE;

	wParam; // UNUSED
	lParam; // UNUSED
	return 0L;
}

void CGXBCurrencyEdit::OnEditUndo()
{
	if (IsReadOnly())
		return;

	if (m_bCanUndo)
	{
		UNDODATA u(m_Undo);
		SaveDataForUndo();
		SetWindowText(u.strText);
		SetSel(u.sel.iStart, u.sel.iStop);
		if (GetFocus() == this)
			MoveCaret(u.iCaretPos);
	}
}

void CGXBCurrencyEdit::OnEditPaste()
{
	if (IsReadOnly())
		return;

	CString s;
	if (GetClipboardText(s) && PrepareTextForPaste(s))
		DoInsert(s);
}

void CGXBCurrencyEdit::OnEditCopy()
{
	if (HasSel())
	{
		CString s;
		GetSelectedText(s);
		SetClipboardText(s);
	}
}

void CGXBCurrencyEdit::OnEditClear()
{
	if (IsReadOnly())
		return;

	if (HasSel())
	{
		CString s;
		ReplaceSelString(NULL, s);
		SetWindowText(s);
		SetSelNone();
	}
	else
		SetValue(0.0);
	if (GetFocus() == this)
		MoveCaret(0);
}

void CGXBCurrencyEdit::OnEditSelectAll()
{
	SetSelAll();
}

LRESULT CGXBCurrencyEdit::OnCut(WPARAM wParam, LPARAM lParam)
{
	OnEditCut();

	wParam; // UNUSED
	lParam; // UNUSED

	return 0L;
}

void CGXBCurrencyEdit::OnEditCut()
{
	if (IsReadOnly())
		return;

	if (HasSel())
	{
		CString s;
		GetSelectedText(s);
		SetClipboardText(s);
		DoDelete();
	}
}

LRESULT CGXBCurrencyEdit::OnCopy(WPARAM wParam, LPARAM lParam)
{
	OnEditCopy();

	wParam; // UNUSED
	lParam; // UNUSED

	return 0L;
}

LRESULT CGXBCurrencyEdit::OnSetRedraw(WPARAM wParam, LPARAM lParam)
{
	lParam; // UNUSED

	// wParam = non-zero if redraw is allowed

	m_bRedraw = !!wParam;

	return 0L;
}

LRESULT CGXBCurrencyEdit::OnSetMargins(WPARAM wParam, LPARAM lParam)
{
	if (wParam & EC_LEFTMARGIN)
		m_uiLeftMargin = LOWORD(lParam);
	if (wParam & EC_RIGHTMARGIN)
		m_uiRightMargin = HIWORD(lParam);
	if (wParam & EC_USEFONTINFO)
	{
		TEXTMETRIC tm;

		{ // BLOCK DC
			CClientDC DC(this);
			CFont* pfontOld = DC.SelectObject(GetFont());
			DC.GetTextMetrics(&tm);
			DC.SelectObject(pfontOld);
		} // FREE DC

		m_uiLeftMargin = m_uiRightMargin = static_cast<UINT>(tm.tmAveCharWidth);
	}

	return 0L;
}

void CGXBCurrencyEdit::OnRButtonUp(UINT nFlags, CPoint point) 
{
	CPoint ptScreen(point);
	ClientToScreen(&ptScreen);
	CMenu* pPopupMenu = CreatePopupMenu();
	pPopupMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, 
							   ptScreen.x, ptScreen.y, this);
	DeletePopupMenu(pPopupMenu);
	CGXBDropEdit::OnRButtonUp(nFlags, point);
}

void CGXBCurrencyEdit::OnSetFocus(CWnd* pOldWnd) 
{
	CGXBDropEdit::OnSetFocus(pOldWnd);
	StartEdit(-1);
	SetSelAll();
	NotifyParent(EN_SETFOCUS);}

void CGXBCurrencyEdit::OnKillFocus(CWnd* pNewWnd) 
{
	CGXBDropEdit::OnKillFocus(pNewWnd);
	StopEdit();
	NotifyParent(EN_KILLFOCUS);
}

UINT CGXBCurrencyEdit::OnGetDlgCode() 
{
	return DLGC_WANTARROWS | DLGC_WANTCHARS;
}

void CGXBCurrencyEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	switch (nChar)
	{
		case VK_LEFT:
			MoveCaret(m_iCaretPos - 1, TRUE);
			break;
		case VK_RIGHT:
			MoveCaret(m_iCaretPos + 1, TRUE);
			break;
		case VK_HOME:
			MoveCaret(0, TRUE);
			break;
		case VK_END:
			MoveCaret(GetWindowTextLength(), TRUE);
			break;
		case VK_DELETE:
			if (IsKeyDown(VK_SHIFT))
				PostMessage(WM_CUT);
			else
				DoDelete();
			break;
		case VK_BACK:
			DoBackspace();
			break;

		// Only display the calculator if the bitmap is showing.

		case VK_F2:
			if(GetBitmap() != NULL)
				ShowCalculator();
			break;

		// Popup menu handling shortcuts.

		case VK_INSERT:
			if (IsKeyDown(VK_CONTROL))
				PostMessage(WM_COPY);
			else if (IsKeyDown(VK_SHIFT))
				PostMessage(WM_PASTE);
			else
				ToggleOverstrikeMode();
			break;
		case 'C':
			if (IsKeyDown(VK_CONTROL))
				PostMessage(WM_COPY);
			break;
		case 'V':
			if (IsKeyDown(VK_CONTROL))
				PostMessage(WM_PASTE);
			break;
		case 'X':
			if (IsKeyDown(VK_CONTROL))
				PostMessage(WM_CUT);
			break;
		case 'Z':
			if (IsKeyDown(VK_CONTROL))
				PostMessage(WM_UNDO);
			break;
	}
	
	CGXBDropEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CGXBCurrencyEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	char c = (char)nChar;
	TCHAR cDecimal = m_pFormat->GetDecimalSeparator();

	if (c == cDecimal)
	{
		// If the user has entered the decimal point character, we must
		// move the caret to the fractional portion of the number. If the
		// number has no fractional portion, we should move to the end
		// of the number (i.e., to the implied decimal point).

		if (HasSel())
			SetSelNone();
		CString s;
		GetWindowText(s);
		int iIndex = m_pFormat->FindDecimalSeparator(s);
		if (iIndex == -1)
		{
			int iFirst, iLast;
			if (m_pFormat->FindFirstAndLastDigits(s, iFirst, iLast))
				iIndex = iLast;
		}

		// Tripping this assert means that there are no digits being
		// displayed in the curency control--an undesirable situation.

		ASSERT(iIndex > -1);

		if (iIndex > -1)
			MoveCaret(iIndex + 1);
	}
	else if (c == '-')
	{
		HandleNegativeSignKey();
	}
	else if ('0' <= c && c <= '9')
	{
		DoInsert(c);
	}

	CGXBDropEdit::OnChar(nChar, nRepCnt, nFlags);
}


void CGXBCurrencyEdit::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if ((nChar == VK_F10) && IsKeyDown(VK_SHIFT))
	{
		CRect rc;
		GetClientRect(&rc);
		PostMessage(WM_RBUTTONUP, 0, MAKELONG(rc.Width() / 2, rc.Height() / 2));
	}
	else if (nChar == VK_BACK)
		PostMessage(WM_UNDO);
	
	CGXBDropEdit::OnSysKeyDown(nChar, nRepCnt, nFlags);
}

void CGXBCurrencyEdit::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	SetSelAll();
	CGXBDropEdit::OnLButtonDblClk(nFlags, point);
}

void CGXBCurrencyEdit::OnPaint() 
{
	CPaintDC DC(this);

	// If we're not currently allowing redraw, bail out of here.

	if (!m_bRedraw)
		return;

	// If we can create a memory DC and a bitmap compatible with the
	// painting DC, do the drawing in an offscreen buffer then BitBlt
	// into place to avoid flashing.

	CBitmap bmp;
	CDC dcMem;
	CRect rc;
	GetClientRect(&rc);
	CSize size(rc.Width(), rc.Height());
	if (dcMem.CreateCompatibleDC(&DC) && 
		bmp.CreateCompatibleBitmap(&DC, size.cx, size.cy))
	{
		CBitmap* pbmpOld = dcMem.SelectObject(&bmp);
		PaintingCore(dcMem);
		DC.BitBlt(0, 0, size.cx, size.cy, &dcMem, 0, 0, SRCCOPY);
		dcMem.SelectObject(pbmpOld);
	}
	else
	{
		PaintingCore(DC);
	}
}

void CGXBCurrencyEdit::OnLButtonDown(UINT nFlags, CPoint point) 
{
	SetRedraw(FALSE);
	SetFocus();
	SetRedraw(TRUE);
	SetSelNone();
	MoveCaret(PointToCaretPos(point));
	m_bMouseSelect = TRUE;
	SetCapture();

	CGXBDropEdit::OnLButtonDown(nFlags, point);
}

void CGXBCurrencyEdit::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (IsMouseSelecting())
		MoveCaret(PointToCaretPos(point), TRUE);	
	CGXBDropEdit::OnMouseMove(nFlags, point);
}

void CGXBCurrencyEdit::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (IsMouseSelecting())
	{
		m_bMouseSelect = FALSE;
		ReleaseCapture();
	}

	// If the user did not actually select anything with the mouse,
	// and if the caret was placed outside the number, then set
	// the entire contents.

	if (!HasSel())
	{
		CString s;
		GetWindowText(s);
		int iFirst, iLast;
		VERIFY(m_pFormat->FindFirstAndLastDigits(s, iFirst, iLast));

		if (m_iCaretPos < iFirst || m_iCaretPos > iLast)
			SetSelAll();
	}

	CGXBDropEdit::OnLButtonUp(nFlags, point);
}






/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//  CGXBDropEdit
//
//  CEdit derivative providing a combo like drop down button
//

IMPLEMENT_DYNAMIC(CGXBDropEdit, CEdit)

BEGIN_MESSAGE_MAP(CGXBDropEdit, CEdit)
	ON_WM_NCCALCSIZE()
	ON_WM_NCPAINT()
	ON_WM_NCLBUTTONDOWN()
	ON_WM_NCHITTEST()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_NCMOUSEMOVE()
	ON_WM_CANCELMODE()
	ON_WM_SYSCOLORCHANGE()
	ON_WM_ENABLE()
	ON_WM_SYSKEYDOWN()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CGXBDropEdit - construction/destruction
//
CGXBDropEdit::CGXBDropEdit() : m_wState(RightAlign), m_wLeftBorder(1),
							 m_wRightBorder(1)
{
}

CGXBDropEdit::~CGXBDropEdit()
{
}

BOOL CGXBDropEdit::AttachEdit(int nCtlID, CWnd* pParentWnd)
{
	// Attach to an existing edit control
	ASSERT_VALID(this);
	ASSERT(pParentWnd != NULL);

	GXGetSysData()->UpdateSysColors();

	if(!SubclassDlgItem(nCtlID, pParentWnd))
	{
		TRACE1("CGXBDropEdit could not attach to edit %d\n", nCtlID);
		return FALSE;
	}

	ASSERT_VALID(this);

	if(m_bmp.m_hObject)
	{
		// We have a bitmap, so we need to adjust the non-client area to include
		// the button. This calculation is performed in the WM_NCCALCSIZE 
		// handler, so force the non-client area to be recalculated.
		::SetWindowPos(m_hWnd, NULL, 0, 0, 0, 0, 
					   SWP_NOSIZE|SWP_NOMOVE|SWP_NOZORDER|SWP_DRAWFRAME);
	}

	return TRUE;
}

BOOL CGXBDropEdit::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	GXGetSysData()->UpdateSysColors();

	if(!CEdit::Create(dwStyle, rect, pParentWnd, nID))
		return FALSE;

	ASSERT_VALID(this);

	if(m_bmp.m_hObject)
	{
		// We have a bitmap, so we need to adjust the non-client area to include
		// the button. This calculation is performed in the WM_NCCALCSIZE 
		// handler (ignored on edit creation), so force the non-client area 
		// to be recalculated.
		::SetWindowPos(m_hWnd, NULL, 0, 0, 0, 0, 
					   SWP_NOSIZE|SWP_NOMOVE|SWP_NOZORDER|SWP_DRAWFRAME);
	}

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CGXBDropEdit attributes
//
void CGXBDropEdit::SetRightAlign(BOOL bRightAlign /* = TRUE */)
{
	// Button will be aligned to right of edit control if bRightAlign is
	// TRUE, otherwise it will be aligned to the left.

	WORD wSaveState = m_wState;
	if(bRightAlign)
		m_wState |= RightAlign;
	else
		m_wState &= ~RightAlign;

	if(m_wState != wSaveState && m_hWnd && m_bmp.m_hObject)
	{
		// Alignment has changed, so Force the non-client to be recalculated
		::SetWindowPos(m_hWnd, NULL, 0, 0, 0, 0, 
					   SWP_NOSIZE|SWP_NOMOVE|SWP_NOZORDER|SWP_DRAWFRAME);
	}
}

BOOL CGXBDropEdit::IsRightAligned() const
{
	// Returns TRUE if we are currently right aligned.
	return (m_wState & RightAlign) ? TRUE : FALSE;
}

void CGXBDropEdit::SetBorder(WORD wLeftBorder, WORD wRightBorder)
{
	// We set the the gap between the button borders and the bitmap

	if(wLeftBorder == m_wLeftBorder && wRightBorder == m_wRightBorder)
		// No change
		return;

	m_wLeftBorder  = wLeftBorder;
	m_wRightBorder = wRightBorder;

	if(m_hWnd && m_bmp.m_hObject)
	{
		// Force the non-client to be recalculated
		::SetWindowPos(m_hWnd, NULL, 0, 0, 0, 0, 
					   SWP_NOSIZE|SWP_NOMOVE|SWP_NOZORDER|SWP_DRAWFRAME);
	}
}

DWORD CGXBDropEdit::GetBorders() const
{
	// Returns left border in low word and right border in high word
	return MAKELONG(m_wLeftBorder, m_wRightBorder);
}


/////////////////////////////////////////////////////////////////////////////
// CGXBDropEdit operations
//
BOOL CGXBDropEdit::SetBitmap(LPCTSTR lpszBmpName)
{
	// Loads the given bitmap for display on the button face.

	BOOL bRes = TRUE;

	// Remove the existing bitmap.
	if(m_bmp.m_hObject)
		m_bmp.DeleteObject();

	m_btnRect.SetRectEmpty();
	m_lpszBmpName = lpszBmpName;
	if(m_lpszBmpName != NULL)
	{
		// Load the given bitmap, mapping it to the current system colors.
		if(!GXLoadSysColorBitmap(m_bmp, m_lpszBmpName))
		{
			m_lpszBmpName = NULL;

			TRACE0("CGXBDropEdit failed to load button bitmap\n");
			bRes = FALSE;
		}
	}
	else
		m_bmp.m_hObject = NULL;

	if(m_hWnd)
	{
		// Force the non-client to be recalculated for the new bitmap
		::SetWindowPos(m_hWnd, NULL, 0, 0, 0, 0, 
					   SWP_NOSIZE|SWP_NOMOVE|SWP_NOZORDER|SWP_DRAWFRAME);
	}

	return TRUE;
}

BOOL CGXBDropEdit::SetBitmap(UINT nBmpID)
{
	return SetBitmap(MAKEINTRESOURCE(nBmpID));
}

BOOL CGXBDropEdit::SetBitmap()
{
	// Removes the current bitmap which results in the button being removed
	// from the edit control.

	return SetBitmap((LPCTSTR) NULL);
}

HBITMAP CGXBDropEdit::GetBitmap() const
{
	return (HBITMAP)(m_bmp.m_hObject);
}

BOOL CGXBDropEdit::HitTestBtn(CPoint point, BOOL bClient) const
{
	// Returns TRUE if the given point is within the button. If bClient is
	// TRUE then point is in our client coordinates otherwise it is in
	// screen coordinates.
	ASSERT(m_bmp.m_hObject);

	CWnd* pParentWnd = GetParent();
	if(bClient)
	{
		// Point is in our client coordinates. Convert to parent client coords.
		if(pParentWnd)
		{
			ClientToScreen(&point);
			pParentWnd->ScreenToClient(&point);
		}
	}
	else
	{
		// Point is in screen coordinates. Convert to parent client coords.
		if(pParentWnd)
			pParentWnd->ScreenToClient(&point);
	}

	return m_btnRect.PtInRect(point);
}

void CGXBDropEdit::InvalidateBtn()
{
	// Invalidate the button.
	ASSERT(m_bmp.m_hObject);

	CWnd* pParentWnd = GetParent();
	if(pParentWnd)
		pParentWnd->InvalidateRect(m_btnRect, FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CGXBDropEdit overrideables
//
void CGXBDropEdit::OnClicked()
{
	// The button has been clicked. This implementation fires a
	// BN_CLICKED to our parent to handle the event.
	CWnd* pParentWnd = GetParent();
	if(pParentWnd)
	{
#ifdef WIN32
		WPARAM wParam = MAKELONG(GetDlgCtrlID(), BN_CLICKED);
		LPARAM lParam = (LPARAM) m_hWnd;
#else
		WPARAM wParam = GetDlgCtrlID();
		LPARAM lParam = MAKELONG(m_hWnd, BN_CLICKED);
#endif
		pParentWnd->SendMessage(WM_COMMAND, wParam, lParam);
	}
}

void CGXBDropEdit::DrawBtn(CDC& dc, CRect r)
{
	HTHEME lhTheme = NULL;
	// Note: Calling dc.GetWindow() will return an invalid handle. 
	// Instead, call AfxGetMainWnd()->GetSafeHwnd().
	if (RWIsAppThemed() && RWIsThemeActive())
		lhTheme = RWOpenThemeData (RWGetSafeHwnd(), L"BUTTON");
	
	if (lhTheme)
	{
		int iState = PBS_NORMAL;

		if (m_wState & Hover) iState = PBS_HOT;
		if (m_wState & Pressed) iState = PBS_PRESSED;			

		RWDrawThemeBackground( lhTheme, dc.GetSafeHdc(), BP_PUSHBUTTON, iState, &r, 0 );	
		
		RWCloseThemeData( lhTheme );
		r.InflateRect(-2, -2);			
	}
	else
	{
		// Handles drawing the button to the given rect 'r' in the given DC.
		if(m_wState & Pressed)
		{
			// Draw the button borders in the down state
			GXDraw3dRect1(&dc, r, GXGetSysData()->clrBtnShadow, GXGetSysData()->clrBtnShadow);
			r.InflateRect(-1, -1);
			GXFillSolidRect1(&dc, r, GXGetSysData()->clrBtnFace);
			r.InflateRect(-1, -1);
		}
		else
		{
			// Draw the normal button borders
			GXDraw3dRect1(&dc, r, GXGetSysData()->clrBtnFace, GXGetSysData()->clrWindowFrame);
			r.InflateRect(-1, -1);
			GXDraw3dRect1(&dc, r, GXGetSysData()->clrBtnHilite, GXGetSysData()->clrBtnShadow);
			r.InflateRect(-1, -1);

			GXFillSolidRect1(&dc, r, GXGetSysData()->clrBtnFace);
		}
	}
	
	// Now draw the bitmap to the button face
	CDC memDC;
	if(memDC.CreateCompatibleDC(&dc))
	{
		BITMAP bm;
		VERIFY(m_bmp.GetObject(sizeof(bm), &bm));

		// Calculate position of bitmap
		int x = r.left + m_wLeftBorder;
		int y = (r.Height() - bm.bmHeight) / 2 + r.top;

		if(m_wState & Pressed)
			// Button is down, so offset bitmap to give impression of movement
			x++, y++;

		CBitmap* pOldBmp = memDC.SelectObject(&m_bmp);
		dc.BitBlt(x, y, bm.bmWidth, bm.bmHeight, &memDC, 0, 0, SRCCOPY);
		memDC.SelectObject(pOldBmp);
	}
}


/////////////////////////////////////////////////////////////////////////////
// CGXBDropEdit message handlers
//
void CGXBDropEdit::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{
	// We override WM_NCCALCSIZE to increase the non-client area to include
	// space for a button.

	CEdit::OnNcCalcSize(bCalcValidRects, lpncsp);

	if(!m_bmp.m_hObject)
		// We have no bitmap - so no button to add.
		return;

	// Calculate width of button, based on width of bitmap, space for borders
	// and any user defined margins.
	m_btnRect.SetRectEmpty();

	BITMAP bm;
	VERIFY(m_bmp.GetObject(sizeof(bm), &bm));
	int nWidth = m_btnRect.right = bm.bmWidth + 4 + m_wLeftBorder + 
								   m_wRightBorder;

	// Now we can setup the rectangle of the button
	if(m_wState & RightAlign)		// Right aligned
	{
		lpncsp->rgrc[0].right -= nWidth;
		m_btnRect.left         = lpncsp->rgrc[0].right;
		m_btnRect.right        = m_btnRect.left + nWidth;
	}
	else							// Left aligned
	{
		m_btnRect.left         = lpncsp->rgrc[0].left;
		m_btnRect.right        = 
		lpncsp->rgrc[0].left   = m_btnRect.left + nWidth;
	}

	m_btnRect.top              = lpncsp->rgrc[0].top;
	m_btnRect.bottom           = lpncsp->rgrc[0].bottom;

	// m_btnRect now contains the coordinates of the button relative to our
	// parents client area.
}

#if _MFC_VER >= 0x0800 // Visual Studio 2005 (as of CTP August 2005)
LRESULT CGXBDropEdit::OnNcHitTest(CPoint point)
#else
UINT CGXBDropEdit::OnNcHitTest(CPoint point)
#endif
{
	// We look for hits on the button, returning HTBORDER (rather than
	// HTNOWHERE which would result in mouse events being swallowed).
#if _MFC_VER >= 0x0800 // Visual Studio 2005 (as of CTP August 2005)
	LRESULT nHit = CEdit::OnNcHitTest(point);
#else
	UINT nHit = CEdit::OnNcHitTest(point);
#endif

	if(nHit == HTNOWHERE && HitTestBtn(point))
		nHit = HTBORDER;

//#if _MFC_VER >= 0x0800 // Visual Studio 2005 (as of CTP August 2005)
//	return (LRESULT)nHit;
//#else
	return nHit;
//#endif
}

void CGXBDropEdit::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	ASSERT(!(m_wState & Pressed));

	if(!(m_wState & Pressed) && HitTestBtn(point))
	{
		// The button has been clicked - We now redraw the button as down
		// and capture the mouse so that we can detect the button being
		// released.
		m_wState |= Pressed | Capture;
		InvalidateBtn();
		UpdateWindow();
		SetCapture();

		// Note that when we are capturing, the mouse events we are interested
		// in will appear as normal mouse events rather than their non-client
		// equivalents.
	}
	else 
		CEdit::OnNcLButtonDown(nHitTest, point);
}

BOOL CGXBDropEdit::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	if( message == WM_NCMOUSELEAVE )
	{
		if (m_wState & Hover)
		{
			m_wState ^= Hover;

			InvalidateBtn();
			UpdateWindow();
		}
	}

	return CWnd::OnWndMsg( message, wParam, lParam, pResult );
}

void CGXBDropEdit::OnNcMouseMove(UINT nFlags, CPoint point)
{
	if (HitTestBtn(point) && !(m_wState & Hover))
	{
		m_wState |= Hover;
			
		InvalidateBtn();
		UpdateWindow();

		TRACKMOUSEEVENT eventTrack;

		memset( &eventTrack, 0x00, sizeof( eventTrack ) );
			
		eventTrack.cbSize = sizeof( eventTrack );
		eventTrack.dwFlags = TME_NONCLIENT | TME_LEAVE;
		eventTrack.hwndTrack = m_hWnd;
		eventTrack.dwHoverTime = HOVER_DEFAULT;
		
		RWTrackMouseEvent( &eventTrack );
	}

	CEdit::OnNcMouseMove(nFlags, point);
}

void CGXBDropEdit::OnMouseMove(UINT nFlags, CPoint point)
{
	if(m_wState & Capture)
	{
		// We are currently tracking a button press. Look for changes in state

		BOOL bHit = HitTestBtn(point, TRUE);
		if(bHit && !(m_wState & Pressed))
		{
			// The mouse has moved back into the button (it was previously
			// drawn up), so draw it as down.
			m_wState |= Pressed;
			InvalidateBtn();
			UpdateWindow();
		}
		else if(!bHit && (m_wState & Pressed))
		{
			// The mouse has moved out of the button, so draw it as up.
			m_wState ^= Pressed;
			InvalidateBtn();
			UpdateWindow();
		}
	}
	else
		CEdit::OnMouseMove(nFlags, point);
}

void CGXBDropEdit::OnLButtonUp(UINT nFlags, CPoint point)
{
	if(m_wState & Capture)
	{
		// We are currently tracking the mouse.
		ReleaseCapture();
		m_wState ^= Capture;

		if(m_wState & Pressed)
		{
			// It is currently drawn down, so now draw it up.
			m_wState ^= Pressed;
			InvalidateBtn();
			UpdateWindow();

		}

		if(HitTestBtn(point, TRUE))
			// The hit was over the button.
			OnClicked();
	}
	else
		CEdit::OnLButtonUp(nFlags, point);
}

void CGXBDropEdit::OnCancelMode()
{
	if(m_wState & Capture)
	{
		// We have to cancel our internal mode, so stop capturing.
		ReleaseCapture();
		m_wState ^= Capture;

		if(m_wState & Pressed)
		{
			// Need to draw the button as up.
			m_wState ^= Pressed;
			InvalidateBtn();
			UpdateWindow();
		}
	}
}

void CGXBDropEdit::OnNcPaint()
{
	// We override WM_NCPAINT to handle drawing a button in non-client space
	// we reserved during WM_NCCALCSIZE.
	CEdit::OnNcPaint();

	if(!m_bmp.m_hObject)
		// No button - so nothing to draw
		return;

	// We need to adjust the coordinates of rectange to have the Non-Client
	// area top left pixel as 0, 0.
	CRect r = m_btnRect;
	CRect windowRect;
	GetWindowRect(&windowRect);

	CWnd* pParentWnd = GetParent();
	if(pParentWnd)
		pParentWnd->ScreenToClient(&windowRect);

	r.OffsetRect(-windowRect.left, -windowRect.top);

	CWindowDC dc(this);

	// We attempt to draw to an off-screen DC - helps reduce flicker.
	CDC memDC;
	CBitmap bmp;
	if(memDC.CreateCompatibleDC(&dc) &&
	   bmp.CreateCompatibleBitmap(&dc, m_btnRect.Width(), m_btnRect.Height()))
	{
		CBitmap* pOldBmp = memDC.SelectObject(&bmp);

		// Draw the button face.
		CRect tempRect = m_btnRect;
		tempRect.OffsetRect(-m_btnRect.left, -m_btnRect.top);
		DrawBtn(memDC, tempRect);

		// If the window is disabled, dither the off-screen bitmap to reflect
		// this state.
		if(!IsWindowEnabled())
		{
			CGXBDrawDisabled(memDC, 2, 2, tempRect.Width() - 4, 
							tempRect.Height() - 4);
		}

		// Now we can copy the off-screen DC to the screen DC.
		dc.BitBlt(r.left, r.top, r.Width(), r.Height(), &memDC, 0, 0, SRCCOPY);

		memDC.SelectObject(pOldBmp);
	}
	else
		// Unable to create the off-screen DC - so draw directly to the screen
		DrawBtn(dc, r);
}

void CGXBDropEdit::OnEnable(BOOL bEnable)
{
	// We have either been enabled or disabled. We need to force a redraw
	// of the button to reflect the new state.
	InvalidateBtn();
	CEdit::OnEnable(bEnable);
}

void CGXBDropEdit::OnSysColorChange()
{
	// The system colors have changed. Adjust our colors accordingly.
	GXGetSysData()->UpdateSysColors();

	if(m_bmp.m_hObject)
	{
		ASSERT(m_lpszBmpName);

		m_bmp.DeleteObject();
		VERIFY(GXLoadSysColorBitmap(m_bmp, m_lpszBmpName));
	}

	CEdit::OnSysColorChange();
}

void CGXBDropEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if(nChar == VK_F4)
		OnClicked();
	else
		CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CGXBDropEdit::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if(nChar == VK_DOWN)
		OnClicked();
	else
		CEdit::OnSysKeyDown(nChar, nRepCnt, nFlags);
}


#ifdef _DEBUG
void CGXBDropEdit::Dump(CDumpContext& dc) const
{
	CEdit::Dump(dc);

	dc << _T("m_wState  = ") << m_wState << _T("\n");
	dc << _T("m_btnRect = ") << m_btnRect << _T("\n");
	dc << _T("m_bmp     = ") << m_bmp.m_hObject << _T("\n");
}

void CGXBDropEdit::AssertValid() const
{
	CEdit::AssertValid();
}
#endif



///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//  CGXBDrawDisabled
//
//  Helper function for dithering a bitmap to be disabled.
//
#define ROP_PSDPxax	0xB8074AL

void AFXAPI CGXBDrawDisabled(CDC& dc, int x, int y, int nWidth, int nHeight)
{
	// We take the drawn button and effectively gray it and add a shadow.
	CDC monoDC;
	CBitmap bmp;

	if(!monoDC.CreateCompatibleDC(&dc) ||
	   !bmp.CreateBitmap(nWidth, nHeight, 1, 1, NULL))
		return;

	COLORREF clrFace      = ::GetSysColor(COLOR_BTNFACE);
	COLORREF clrHighlight = ::GetSysColor(COLOR_BTNHIGHLIGHT);
	COLORREF clrShadow    = ::GetSysColor(COLOR_BTNSHADOW);

	// Initialise to 0.
	CBitmap* pOldBmp = monoDC.SelectObject(&bmp);
	monoDC.PatBlt(0, 0, nWidth, nHeight, WHITENESS);
	
	// Create mask based on the button bitmap.
	dc.SetBkColor(clrFace);
	monoDC.BitBlt(0, 0, nWidth, nHeight, &dc, x, y, SRCCOPY);

	dc.SetBkColor(clrHighlight);
	monoDC.BitBlt(0, 0, nWidth, nHeight, &dc, x, y, SRCPAINT);

	dc.SetBkColor(RGB(255,255,255));
	dc.SetTextColor(0L);

	CBrush btnHighLight, btnShadow;
	btnHighLight.CreateSolidBrush(clrHighlight);
	btnShadow.CreateSolidBrush(clrShadow);

	// Draw high light shadow where we have zeros in our mask.
	CBrush* pBrOld = dc.SelectObject(&btnHighLight);
	dc.BitBlt(x+1, y+1, nWidth-1, nHeight-1, &monoDC, 0, 0, ROP_PSDPxax);

	// Draw the shadow where we have zeros in our mask.
	dc.SelectObject(&btnShadow);
	dc.BitBlt(x, y, nWidth, nHeight, &monoDC, 0, 0, ROP_PSDPxax);

	dc.SelectObject(pBrOld);
	monoDC.SelectObject(pOldBmp);
}

///////////////////////////////////////////////////////////////////////////////


