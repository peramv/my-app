///////////////////////////////////////////////////////////////////////////////
// gxstygd2.cpp : CGXFont, CGXBrush profile support
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

#ifndef _GXSTYLES_H_
#include "grid\gxstyles.h"
#endif

#ifndef _GXSTATE_H_
#include "grid\gxstate.h"
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXSTYGDI")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif



///////////////////////////////////////////////////////////////////

CGXFont::CGXFont(LPCTSTR pszDescription)
{
	SetDescription(pszDescription);
}

void CGXFont::GetDescription(LPTSTR s) const
{
	LPTSTR p = s;
	LPCTSTR szd = _T("%d");

	ASSERT(s);
	if (!s)
		return;

	if (GetIncludeFaceName())
	{
#if !defined(_UNIX_) && !defined(_MAC)
		wsprintf(s, _T("%s"), GetFaceName());
		p = s + _tcslen(s);
#else
		p = s + _stprintf(s, _T("%s"), GetFaceName());
		// I have used _stprintf instead of wsprint because
		// I need the number of bytes and not the number of
		// characters when dealing with DBCS strings.
#endif
	}
	*p++ = _T(',');
	if (GetIncludeSize())
		p += wsprintf(p, szd, (int) GetSize());
	*p++ = _T(',');
	if (GetIncludeWeight())
		p += wsprintf(p, szd, (int) GetWeight());
	*p++ = _T(',');
	if (GetIncludeItalic())
		*p++ = (TCHAR) (GetItalic() + _T('0'));
	*p++ = _T(',');
	if (GetIncludeUnderline())
		*p++ = (TCHAR) (GetUnderline() + _T('0'));
	*p++ = _T(',');
	if (GetIncludeStrikeOut())
		*p++ = (TCHAR) (GetStrikeOut() + _T('0'));
	if (GetIncludeOrientation())
		p += wsprintf(p, szd, (int) GetOrientation());
	*p = _T('\0');
}

CString CGXFont::GetDescription() const
{
	TCHAR s[128];

	GetDescription(s);

	return s;
}

CGXFont& CGXFont::SetDescription(LPCTSTR s)
{
	ASSERT(s != NULL);
	// ASSERTION-> Passed NULL Pointer to CGXFont::ReadProfile ->END

	if (s == NULL)
		return *this;

	TCHAR t[128];
	Init();

	// Facename
	LPTSTR p =(LPTSTR) _tcschr(s, _T(','));
	if (*s != _T(','))
	{
		if(p != NULL)
		{
			// QA: 31989 - #if Secure Code Cleanup.
			_tcsncpy(t, s, p-s);
			t[p-s] = _T('\0');
			SetFaceName(t);
		}
		else
			SetFaceName(s);
	}
	if (p == NULL)
		return *this;

	// Size
	s = p+1;
	p =(LPTSTR)_tcschr(s, _T(','));
	if (*s != _T(','))
		SetSize(_ttoi(s));
	if (p == NULL)
		return *this;

	// Bold
	s = p+1;
	p =(LPTSTR) _tcschr(s, _T(','));
	if (*s != _T(','))
		SetWeight((BOOL) _ttoi(s));
	if (p == NULL)
		return *this;

	// Italic
	s = p+1;
	p = (LPTSTR) _tcschr(s, _T(','));
	if (*s != _T(','))
		SetItalic((BOOL) _ttoi(s));
	if (p == NULL)
		return *this;

	// Underline
	s = p+1;
	p =(LPTSTR)_tcschr(s, _T(','));
	if (*s != _T(','))
		SetUnderline((BOOL) _ttoi(s));
	if (p == NULL)
		return *this;

	// StrikeOut
	s = p+1;
	p =(LPTSTR)_tcschr(s, _T(','));
	if (*s != _T(','))
		SetStrikeOut((BOOL) _ttoi(s));
	if (p == NULL)
		return *this;

	// Orientation
	s = p+1;
	if (*s)
		SetOrientation((BOOL) _ttoi(s));

	return *this;
}

///////////////////////////////////////////////////////////////////

CGXBrush::CGXBrush(LPCTSTR pszDescription)
{ 
	SetDescription(pszDescription); 
}

CGXBrush& CGXBrush::SetDescription(LPCTSTR szDescription)
{
	DWORD style = 0;
	LONG hatch = 0;
	int r = 0, g = 0, b = 0;
	int rb = 0, gb = 0, bb = 0, bp = 0;
	COLORREF lbColor = 0, lbBkColor = 0;

	// int n = _stscanf(szDescription, szBrushFormat, &style, &hatch, &r, &g, &b);
	// sscanf is not available for extension DLLs
	int n = 1;
	if (_tcsclen(szDescription) > 0)
	{
		LPCTSTR p = szDescription;
		while (*p == _T(' '))
			p++;
		style = (DWORD) _ttol(p);
		p = _tcschr(p, _T(' '));
		if (p)
		{
			n++;
			while (*p == _T(' '))
				p++;
			hatch = _ttol(p);
			p = _tcschr(p, _T(' '));
		}
		if (p)
		{
			n++;
			while (*p == _T(' '))
				p++;
			r = _ttoi(p);
			p = _tcschr(p, _T(' '));
		}
		if (p)
		{
			n++;
			while (*p == _T(' '))
				p++;
			g = _ttoi(p);
			p = _tcschr(p, _T(' '));
		}
		if (p)
		{
			n++;
			while (*p == _T(' '))
				p++;
			b = _ttoi(p);
			p = _tcschr(p, _T(' '));
		}
		if (p)
		{
			n++;
			while (*p == _T(' '))
				p++;
			rb = _ttoi(p);
			p = _tcschr(p, _T(' '));
		}
		if (p)
		{
			n++;
			while (*p == _T(' '))
				p++;
			gb = _ttoi(p);
			p = _tcschr(p, _T(' '));
		}
		if (p)
		{
			n++;
			while (*p == _T(' '))
				p++;
			bb = _ttoi(p);
			p = _tcschr(p, _T(' '));
		}
		// Support for PALETTEINDEX and PALETTERGB and system color
		if (p)
		{
			n++;
			while (*p == _T(' '))
				p++;
			bp = _ttoi(p);
		}
	}
	ASSERT(n >= 5);
	// ASSERTION-> Wrong description string ->END
	if (n >= 5)
	{
		lbStyle = (UINT) style;
		lbColor = RGB(r, g, b) | (((DWORD)(BYTE)(bp))<<24);

		if (lbStyle == BS_PATTERN)
			lbHatch = (int)(SEC_DWORD) GXGetPatternBitmap(lbPattern = (int) hatch)->GetSafeHandle();
		else
			lbHatch = (int) hatch;
		if (n >= 8)
			lbBkColor = RGB(rb, gb, bb);

		// Support for PALETTEINDEX and PALETTERGB
		if (n >= 9 && bp == 1)
			lbColor = PALETTEINDEX(MAKEWORD(r, g));
		else if (n >= 9 && bp == 2)
			lbColor = PALETTERGB(r, g, b);
	}

	lbColor1 = GXCOLOR1(lbColor);
	lbColor2 = GXCOLOR2(lbColor);
	lbBkColor1 = GXCOLOR1(lbBkColor);
	lbBkColor2 = GXCOLOR2(lbBkColor);

	return *this;
}

void CGXBrush::GetDescription(LPTSTR s) const
{
	ASSERT(s);
	wsprintf(s, szBrushFormat, (DWORD) lbStyle, (LONG) lbHatch,
		GetRValue(lbColor2), GetGValue(lbColor2), GetBValue(lbColor2),
		GetRValue(lbBkColor2), GetGValue(lbBkColor2), GetBValue(lbBkColor2), 
		((BYTE)((GXGETCOLORNA2(lbColor1, lbColor2))>>24)));
}

CString CGXBrush::GetDescription() const
{
	DWORD style = lbStyle;
	LONG hatch = lbHatch;
	if (lbStyle == BS_PATTERN)
		hatch = lbPattern;
	int r = GetRValue(lbColor2), g = GetGValue(lbColor2), b = GetBValue(lbColor2);
	int rb = GetRValue(lbBkColor2), gb = GetGValue(lbBkColor2), bb = GetBValue(lbBkColor2);
	int pb = ((BYTE)((GXGETCOLORNA2(lbColor1, lbColor2))>>24));   // Support for PALETTEINDEX and PALETTERGB
	TCHAR s[64];
	wsprintf(s, szBrushFormat, style, hatch, r, g, b, rb, gb, bb, pb);
	return s;
}

