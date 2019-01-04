///////////////////////////////////////////////////////////////////////////////
// gxsstr.cpp: String Utilities
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
// Portions Copyright (C) 1995-1998 X Engineering Software Systems Corp
//

#define _OG_EXPORT_IMPL
#define _RW_IMPL

#include "stdafx.h"
#include "grid\gxsinc.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// static int iso_escape = 0;  /* 1 => octal escape ISO 0xa1..0xff */

void  __cdecl _gx_set_iso_escape(int x)
{
	GXGetEngineState()->iso_escape = x;
}

int  __cdecl _gx_get_iso_escape(void)
{
	return GXGetEngineState()->iso_escape;
}

LPTSTR	__cdecl _gx_xs_strdup(LPCTSTR s)
{
	LPTSTR newstr;

	if (s == NULL)
	{
		return NULL;
	}
	newstr = (LPTSTR) GX_XSmalloc((_tcslen(s) + 1)*sizeof(TCHAR));
	// QA: 31989 - #if Secure Code Cleanup.
	return _tcscpy(newstr, s);
}

LPTSTR	__cdecl _gx_xs_short_strdup(LPCTSTR s)
{
	LPTSTR newstr = (LPTSTR) GX_XSmalloc(8+sizeof(TCHAR));
	// QA: 31989 - #if Secure Code Cleanup.
	_tcsncpy(newstr, s, 8/sizeof(TCHAR));
	newstr[8/sizeof(TCHAR)] = _T('\0');
	return newstr;
}

void  __cdecl _gx_xs_short_strcpy(LPTSTR dst, LPCTSTR src, BOOL bAddEOS)
{
	for (int n = 0; n < 8/sizeof(TCHAR); n++)
	{
		*dst++ = *src;
		if (*src)
			src++;
	}

	if (bAddEOS)
		*dst = _T('\0');
}



int  __cdecl _gx_decode_hex_digit(TCHAR c)
{
	if (c >= _T('0') && c <= _T('9'))
		return c - '0';
	if (c >= _T('a') && c <= _T('f'))
		return c - _T('a') + 10;
	if (c >= _T('A') && c <= _T('F'))
		return c - _T('A') + 10;
	return -1;
}

LPTSTR	__cdecl _gx_xs_encode_string(LPTSTR outstr, LPCTSTR instr, int quote_escape)
/*
 * Encodes non-printing and special characters \ and " according to
 * to ANSI C rules.  The " character is backslash-escaped only if
 * quote_escape is true.  Returns a pointer to terminating NUL character
 * of the output string.
 */
{
	LPTSTR bp = outstr;
	TCHAR c;
	while ((c = *instr++) != 0)
	{
		switch (c)
		{
		case _T('\n'):  /* newline (LF) */
			*bp++ = _T('\\');
			*bp++ = _T('n');
			break;
		case _T('\t'):  /* horizontal tab (HT) */
			*bp++ = _T('\\');
			*bp++ = _T('t');
			break;
		case _T('\v'):  /* vertical tab (VT) */
			*bp++ = _T('\\');
			*bp++ = _T('v');
			break;
		case _T('\b'):  /* backspace (BS) */
			*bp++ = _T('\\');
			*bp++ = _T('b');
			break;
		case _T('\r'):  /* carriage return (CR) */
			*bp++ = _T('\\');
			*bp++ = _T('r');
			break;
		case _T('\f'):  /* formfeed (FF) */
			*bp++ = _T('\\');
			*bp++ = _T('f');
			break;
		case 7: /* \a = audible alert (BEL) */
			*bp++ = _T('\\');
			*bp++ = _T('a');
			break;
		case _T('\"'):  /* double quote */
			if (quote_escape)
				*bp++ = _T('\\');
			*bp++ = _T('\"');
			break;
		case _T('\\'):  /* backslash */
			*bp++ = _T('\\');
			*bp++ = _T('\\');
			break;
		default:
			if ((c >= _T(' ') && c <= _T('~')) ||   /* printable ASCII */
				(!GXGetEngineState()->iso_escape && (c >= 0xa1 && c <= 0xff))  /* printable ISO */
				|| c < 0)
				*bp++ = c;
			else
			{
				*bp++ = _T('\\');

				// TODO: UNICODE needs more digits
				if ((*instr >= _T('0') && *instr <= _T('7')) || c > 077)
				{   /* 3 digit octal */
					*bp++ = (TCHAR) ((c >> 6 & 7) + _T('0'));
					*bp++ = (TCHAR) (((c >> 3) & 7) + _T('0'));
					*bp++ = (TCHAR) ((c & 7) + _T('0'));
				}
				else if (c > 007)
				{   /* 2 digit octal */
					*bp++ = (TCHAR) (((c >> 3) & 7) + _T('0'));
					*bp++ = (TCHAR) ((c & 7) + _T('0'));
				}
				else    /* 1 digit octal */
					*bp++ = (TCHAR) ((c & 7) + _T('0'));
			}
		}
	}
	*bp = _T('\0');
	return bp;
}

LPTSTR	__cdecl _gx_xs_encode_html(LPTSTR outstr, LPCTSTR instr)
/*
 * Encodes non-printing and special characters according to
 * to HTML and Netscape rules.  Returns a pointer to terminating
 * NUL character of the output string.
 */
{
	LPTSTR bp = outstr;
	TCHAR c;
	while ((c = *instr++) != 0)
	{
		switch (c)
		{
		case _T('\n'):  /* newline (LF) */
		case _T('\r'):  /* carriage return (CR) */
			*bp++ = _T('<');
			*bp++ = _T('B');
			*bp++ = _T('R');
			*bp++ = _T('>');
			break;
		case _T('&'):   /* ampersand */
			*bp++ = _T('&');
			*bp++ = _T('a');
			*bp++ = _T('m');
			*bp++ = _T('p');
			*bp++ = _T(';');
			break;
		case _T('<'):   /* left angle bracket */
			*bp++ = _T('&');
			*bp++ = _T('l');
			*bp++ = _T('t');
			*bp++ = _T(';');
			break;
		case _T('>'):   /* right angle bracket */
			*bp++ = _T('&');
			*bp++ = _T('g');
			*bp++ = _T('t');
			*bp++ = _T(';');
			break;
		case _T('\"'):  /* double quote */
			*bp++ = _T('&');
			*bp++ = _T('q');
			*bp++ = _T('u');
			*bp++ = _T('o');
			*bp++ = _T('t');
			*bp++ = _T(';');
			break;
		default:
			if (c >= _T(' ') && c <= _T('~'))   /* printable ASCII */
				*bp++ = (TCHAR) c;
			else
			{   /* use decimal escape sequence */
				*bp++ = _T('&');
				*bp++ = _T('#');
				// QA: 31989 - #if Secure Code Cleanup.
				_stprintf(bp, _T("%d"), c);
				while (*bp)
					bp++;
				*bp++ = _T(';');
			}
		}
	}
	*bp = _T('\0');
	return bp;
}

LPTSTR	__cdecl _gx_xs_decode_string(LPTSTR outstr, LPCTSTR instr)
{
	TCHAR c;
	TCHAR ovalue;
	int x;
	int count = 0;
	while ((c = *instr++) != 0)
	{
		if (++count == GX_MAX_TEXT)
			break;
		if (c == _T('\\'))
		{   /* backslash escape */
			switch (c = *instr++)
			{
			case _T('\0'):  /* end of string */
				*outstr = c;
				return outstr;
			case _T('n'):
				*outstr++ = _T('\n');
				break;
			case _T('t'):
				*outstr++ = _T('\t');
				break;
			case _T('v'):
				*outstr++ = _T('\v');
				break;
			case _T('b'):
				*outstr++ = _T('\b');
				break;
			case _T('r'):
				*outstr++ = _T('\r');
				break;
			case _T('f'):
				*outstr++ = _T('\f');
				break;
			case _T('a'):
				*outstr++ = 7;  /* \a = audible alert (BEL) */
				break;
			case _T('\\'):
				*outstr++ = _T('\\');
				break;
			case _T('\"'):
				*outstr++ = _T('\"');
				break;
			case _T('x'):   /* this is \xhh format */
				if ((x = _gx_decode_hex_digit(*instr)) > 0)
				{
					ovalue = (TCHAR) x;
					if ((x = _gx_decode_hex_digit(*(++instr))) > 0)
					{
						ovalue = (TCHAR) ((ovalue << 4) | x);
						instr++;
					}
					*outstr++ = ovalue;
				}
				else
					*outstr++ = c;  /* no hex present, output the _T('x') */
				break;
			default:
				if (c >= _T('0') && c <= _T('7'))
				{   /* octal encoding, first digit */
					ovalue = (TCHAR) (c - _T('0'));
					if (*instr >= _T('0') && *instr <= _T('7'))
					{   /* 2nd digit? */
						ovalue = (TCHAR) ((ovalue << 3) | (*instr++ - _T('0')));
						if (*instr >= _T('0') && *instr <= _T('7')) /* 3rd digit? */
							ovalue = (TCHAR) ((ovalue << 3) | (*instr++ - _T('0')));
					}
					*outstr++ = ovalue;
				}
				else    /* ignore the backslash escape */
					*outstr++ = c;
			}
		}
		else    /* c != _T('\\') */
			*outstr++ = c;
	}
	*outstr = _T('\0');
	return outstr;
}

int  __cdecl _gx_xs_string_linecount(LPCTSTR t)
{
	register int c = 1;
	register LPCTSTR p;

	p = t;
	while (*p)
		if (*p++ == _T('\n'))  // TODO: make DBCS aware!
			c++;
	return c;
}
