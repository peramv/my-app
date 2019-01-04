///////////////////////////////////////////////////////////////////////////////
// gxstygd3.cpp : CGXPen profile support 
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

CGXPen::CGXPen(LPCTSTR szDescription)
{ 
	SetDescription(szDescription); 
}

CGXPen& CGXPen::SetDescription(LPCTSTR szDescription)
{
	DWORD style = 0;
	LONG width = 0;
	COLORREF lopnColor = 0;
	int r = 0, g = 0, b = 0, bp = 0;
	// int n = _stscanf(szDescription, szPenFormat, &style, &width, &r, &g, &b);
	// sscanf is nlot available for extension DLLs
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
			width = _ttol(p);
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
		lopnStyle = (UINT) style;
		lopnColor = RGB(r, g, b);
		lopnWidth = (unsigned) width;
	}
	if (n == 6)
	{
		lopnColor = RGB(r, g, b) | (((DWORD)(BYTE)(bp))<<24);
	}

	lopnColor1 = GXCOLOR1(lopnColor);
	lopnColor2 = GXCOLOR2(lopnColor);

	return SetInclude(n >= 5);
}

void CGXPen::GetDescription(LPTSTR s) const
{
	ASSERT(s);
	ASSERT(GetInclude());
	// ASSERTION-> Did you check GetInclude()? ->END
	COLORREF lopnColor = GXGETCOLORNA2(lopnColor1, lopnColor2);
	int pb = ((BYTE)((lopnColor)>>24)); // Support for PALETTEINDEX and PALETTERGB
	wsprintf(s, szPenFormat, (DWORD) lopnStyle, (LONG) lopnWidth, GetRValue(lopnColor),
		GetGValue(lopnColor), GetBValue(lopnColor), pb);
}

CString CGXPen::GetDescription() const
{
	ASSERT(GetInclude());
	// ASSERTION-> Did you check GetInclude()? ->END
	TCHAR s[64];
	COLORREF lopnColor = GXGETCOLORNA2(lopnColor1, lopnColor2);
	int pb = ((BYTE)((lopnColor)>>24)); // Support for PALETTEINDEX and PALETTERGB
	wsprintf(s, szPenFormat, (DWORD) lopnStyle, (LONG) lopnWidth, GetRValue(lopnColor),
		GetGValue(lopnColor), GetBValue(lopnColor), pb);
	return s;
}

