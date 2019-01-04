///////////////////////////////////////////////////////////////////////////////
// fnstring.cpp: String worksheet functions
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

#define CELLRANGE

/* returns character corresponding to ASCII code */
gxOperand __cdecl _gx_fn_char(gxOperand argv[])
{
	gxOperand op;
	unsigned n;
	LPTSTR expr_sbuf = _gx_get_expr_sbuf();

	n = (unsigned) _gx_get_one_number(argv);
#ifdef _UNICODE
	if (n < 1 || n > 0xffff)
#else
	if (n < 1 || n > 255)
#endif
		_gx_function_error(GX_FN_ERR_OP_OUT_OF_RANGE);
	expr_sbuf[0] = (TCHAR) n;
	expr_sbuf[1] = _T('\0');
	op.val.string = expr_sbuf;
	op.type = GX_STRING;
	return op;
}

/* removes non-printing characters from string */
gxOperand __cdecl _gx_fn_clean(gxOperand argv[])
{
	gxOperand op;
	LPCTSTR src;
	LPTSTR dst;
	TCHAR c;
	LPTSTR expr_sbuf = _gx_get_expr_sbuf();

	if (argv->val.count != 1)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(++argv);
	if (argv->type != GX_STRING)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	src = argv->val.string;
	dst = expr_sbuf;
	// TODO - make DBCS aware
	while ((c = *src++) != 0)
		if (_istprint(c))
			*dst++ = c;
	*dst = _T('\0');
	op.val.string = expr_sbuf;
	op.type = GX_STRING;
	return op;
}

/* ASCII code of first character in string */
gxOperand __cdecl _gx_fn_code(gxOperand argv[])
{
	gxOperand op;

	if (argv->val.count != 1)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(++argv);
	if (argv->type != GX_STRING)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
#ifdef _UNICODE
	op.val.number = *(argv->val.string) & 0xffff;
#else
	op.val.number = *(argv->val.string) & 0xff;
#endif
	op.type = GX_NUMBER;
	return op;
}

/* True if string1 == string2 */
gxOperand __cdecl _gx_fn_exact(gxOperand argv[])
{
	gxOperand op;

	if (argv->val.count != 2)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 1);
	_gx_cvt2constant(argv + 2);
	if (argv[1].type != GX_STRING || argv[2].type != GX_STRING)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	op.val.number = !_tcscmp(argv[1].val.string, argv[2].val.string);
	op.type = GX_NUMBER;
	return op;
}

gxOperand __cdecl _gx_fn_find(gxOperand argv[])
{
	gxOperand op;
	int i,
		n1,
		n2,
		index;

	if (argv->val.count != 3)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 1);
	_gx_cvt2constant(argv + 2);
	_gx_cvt2constant(argv + 3);
	if (argv[1].type != GX_STRING ||
		argv[2].type != GX_STRING ||
		argv[3].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	n1 = (int)_tcslen(argv[1].val.string);
	n2 = (int)_tcslen(argv[2].val.string);
	if (n1 > n2)
		_gx_function_error(GX_FN_ERR_SUBSTR_GT_STR);
	index = (int) argv[3].val.number;
	if (index < 0 || index > n2 - 1)
		_gx_function_error(GX_FN_ERR_INDEX_OUT_OF_RNG);
	for (i = index; i < n2 - n1 + 1; i++)
	{
		if (!_tcsncmp(argv[2].val.string + i, argv[1].val.string, n1))
			break;
	}
	if (i > n2 - n1)
		_gx_function_error(GX_FN_ERR_SUBSTR_NOT_FOUND);
	op.val.number = (gxNumber) i;
	op.type = GX_NUMBER;
	return op;
}

gxOperand __cdecl _gx_fn_hextonum(gxOperand argv[])
{
	gxOperand op;
	int x,
		i = 0;
	LPTSTR dp;
	TCHAR  digit;
	TCHAR  temp[10];

	if (argv->val.count != 1)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 1);
	if (argv[1].type != GX_STRING)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	dp = argv[1].val.string;
	while ((digit = *dp++) != 0)
	{
		if (!_istspace(digit))
			break;
	}
	// TODO: make DBCS aware
	--dp;
	while ((digit = *dp++) != 0)
	{
		if (digit != _T('0'))
			break;
	}
	--dp;
	temp[i++] = _T('0');
	while ((digit = *dp++) != 0)
	{
		if (!_istxdigit(digit))
		{
			if (_istspace(digit))
			{   /* might be trailing spaces */
				while ((digit = *dp++) != 0)
				{
					if (!_istspace(digit))
						break;
				}
			}
			if (digit)
				_gx_function_error(GX_FN_ERR_NON_HEX_DIGITS);
			else
				break;
		}
		temp[i++] = digit;
		if (i > 9)
			_gx_function_error(GX_FN_ERR_HEX_GT_32B);
	}
	temp[i] = '\0';
	// QA: 31989 - #if Secure Code Cleanup.
	_stscanf(temp, _T("%x"), &x);
	op.val.number = (gxNumber) x;
	op.type = GX_NUMBER;
	return op;
}

gxOperand __cdecl _gx_fn_numtohex(gxOperand argv[])
{
	gxOperand op;
	gxNumber x;
	LPTSTR expr_sbuf = _gx_get_expr_sbuf();

	if (argv->val.count != 1)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 1);
	if (argv[1].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	x = argv[1].val.number;
	if (x < -2147483648.0 || x > 2147483647.0)
		_gx_function_error(GX_FN_ERR_MAGNITUDE);
	// QA: 31989 - #if Secure Code Cleanup.
	_stprintf(expr_sbuf, _T("%x"), (int) x);
	op.val.string = expr_sbuf;
	op.type = GX_STRING;
	return op;
}

gxOperand __cdecl _gx_fn_left(gxOperand argv[])
{
	gxOperand op;
	unsigned n;
	LPTSTR expr_sbuf = _gx_get_expr_sbuf();

	if (argv->val.count != 2)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 1);
	_gx_cvt2constant(argv + 2);
	if (argv[1].type != GX_STRING || argv[2].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	if ((int) argv[2].val.number < 0)
		_gx_function_error(GX_FN_ERR_CNT_LT_0);
	n = GX_MIN((unsigned)_tcslen(argv[1].val.string), (unsigned) argv[2].val.number);
	// QA: 31989 - #if Secure Code Cleanup.
	_tcsncpy(expr_sbuf, argv[1].val.string, n);
	expr_sbuf[n] = _T('\0');
	op.val.string = expr_sbuf;
	op.type = GX_STRING;
	return op;
}

gxOperand __cdecl _gx_fn_right(gxOperand argv[])
{
	gxOperand op;
	int l,
		n;
	LPTSTR expr_sbuf = _gx_get_expr_sbuf();

	if (argv->val.count != 2)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 1);
	_gx_cvt2constant(argv + 2);
	if (argv[1].type != GX_STRING || argv[2].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	l = (int)_tcslen(argv[1].val.string);
	if ((int) argv[2].val.number < 0)
		_gx_function_error(GX_FN_ERR_CNT_LT_0);
	n = GX_MIN(l, (int) argv[2].val.number);
	// QA: 31989 - #if Secure Code Cleanup.
	_tcsncpy(expr_sbuf, argv[1].val.string + l - n, n);
	expr_sbuf[n] = _T('\0');
	op.val.string = expr_sbuf;
	op.type = GX_STRING;
	return op;
}

gxOperand __cdecl _gx_fn_mid(gxOperand argv[])
{
	gxOperand op;
	int i,
		l,
		n;
	LPTSTR expr_sbuf = _gx_get_expr_sbuf();

	if (argv->val.count != 3)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 1);
	_gx_cvt2constant(argv + 2);
	_gx_cvt2constant(argv + 3);

	if (argv[1].type != GX_STRING ||
		argv[2].type != GX_NUMBER ||
		argv[3].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);

	if (argv[1].type != GX_STRING)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE1);
	if (argv[2].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE2);
	if (argv[3].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE3);
	l = (int)_tcslen(argv[1].val.string);
	i = (int) argv[2].val.number;
//  if (get_excel_mode(_gx_get_expr_si()))
	i -= 1;
	if (i < 0 || i > l - 1)
		_gx_function_error(GX_FN_ERR_INDEX_OUT_OF_RNG);
	if ((int) argv[3].val.number < 0)
		_gx_function_error(GX_FN_ERR_CNT_LT_0);
	n = GX_MIN(l - i, (int) argv[3].val.number);
	// QA: 31989 - #if Secure Code Cleanup.
	_tcsncpy(expr_sbuf, argv[1].val.string + i, n);
	expr_sbuf[n] = _T('\0');
	op.val.string = expr_sbuf;
	op.type = GX_STRING;
	return op;
}

gxOperand __cdecl _gx_fn_length(gxOperand argv[])
{
	gxOperand op;

	if (argv->val.count != 1)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 1);
	if (argv[1].type != GX_STRING)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	op.val.number = (gxNumber) _tcslen(argv[1].val.string);
	op.type = GX_NUMBER;
	return op;
}

gxOperand __cdecl _gx_fn_lower(gxOperand argv[])
{
	gxOperand op;
	LPCTSTR s1;
	LPTSTR s2;
	LPTSTR expr_sbuf = _gx_get_expr_sbuf();

	if (argv->val.count != 1)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 1);
	if (argv[1].type == GX_NUMBER)
		s1 = _T("");
	else
	{
		if (argv[1].type != GX_STRING)
			_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
		s1 = argv[1].val.string;
	}
	s2 = expr_sbuf;
	// QA: 31989 - #if Secure Code Cleanup.
	_tcscpy(s2, s1);
	_tcslwr(s2);
	op.val.string = expr_sbuf;
	op.type = GX_STRING;
	return op;
}

gxOperand __cdecl _gx_fn_upper(gxOperand argv[])
{
	gxOperand op;
	LPCTSTR s1;
	LPTSTR s2;
	LPTSTR expr_sbuf = _gx_get_expr_sbuf();

	if (argv->val.count != 1)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 1);
	if (argv[1].type == GX_NUMBER)
		s1 = _T("");
	else
	{
		if (argv[1].type != GX_STRING)
			_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
		s1 = argv[1].val.string;
	}
	s2 = expr_sbuf;
	// QA: 31989 - #if Secure Code Cleanup.
	_tcscpy(s2, s1);
	_tcsupr(s2);
	op.val.string = expr_sbuf;
	op.type = GX_STRING;
	return op;
}

gxOperand __cdecl _gx_fn_proper(gxOperand argv[])
{
	gxOperand op;
	LPCTSTR s1;
	LPTSTR s2;
	TCHAR c;
	LPTSTR expr_sbuf = _gx_get_expr_sbuf();
	int flag = 1;

	if (argv->val.count != 1)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 1);
	if (argv[1].type == GX_NUMBER)
		s1 = _T("");
	else
	{
		if (argv[1].type != GX_STRING)
			_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
		s1 = argv[1].val.string;
	}
	s2 = expr_sbuf;

	// TODO: make DBCS aware
	while ((c = *s1++) != 0)
	{
		if (_istspace(c))
			flag = 1;
		if (flag)
			*s2++ = (TCHAR) _totupper(c);
		else
			*s2++ = (TCHAR) _totlower(c);
		if (!_istspace(c))
			flag = 0;
	}
	*s2 = _T('\0');
	op.val.string = expr_sbuf;
	op.type = GX_STRING;
	return op;
}

gxOperand __cdecl _gx_fn_repeat(gxOperand argv[])
{
	gxOperand op;
	int i,
		n,
		l;
	LPCTSTR s;
	LPTSTR expr_sbuf = _gx_get_expr_sbuf();

	if (argv->val.count != 2)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 1);
	_gx_cvt2constant(argv + 2);
	if (argv[1].type != GX_STRING || argv[2].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	s = argv[1].val.string;
	l = (int)_tcslen(s);
	n = (int) argv[2].val.number;
	if (n < 0)
		_gx_function_error(GX_FN_ERR_CNT_LT_0);
	if (l * n > GX_MAX_TEXT - 1)
		_gx_function_error(GX_FN_ERR_STR_TOO_LONG);
	*expr_sbuf = _T('\0');
	if (l > 0)
	{
		for (i = 0; i < n; i++)
			_gx_fn_xsstrcat(expr_sbuf, s, GX_MAX_TEXT);
	}
	op.val.string = expr_sbuf;
	op.type = GX_STRING;
	return op;
}

gxOperand __cdecl _gx_fn_replace(gxOperand argv[])
{
	gxOperand op;
	int i,
		n,
		l;
	LPCTSTR s;
	LPTSTR expr_sbuf = _gx_get_expr_sbuf();

	if (argv->val.count != 4)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 1);
	_gx_cvt2constant(argv + 2);
	_gx_cvt2constant(argv + 3);
	_gx_cvt2constant(argv + 4);
	if (argv[1].type != GX_STRING ||
		argv[2].type != GX_NUMBER ||
		argv[3].type != GX_NUMBER ||
		argv[4].type != GX_STRING)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	s = argv[1].val.string;
	l = (int)_tcslen(s);
	i = GX_MIN((int) argv[2].val.number, l);
	n = GX_MIN((int) argv[3].val.number, l - i);
	if (i < 0 || n < 0)
		_gx_function_error(GX_FN_ERR_ARG_OUT_OF_RNG);
	// QA: 31989 - #if Secure Code Cleanup.
	_tcsncpy(expr_sbuf, s, i);
	_gx_fn_xsstrcpy(expr_sbuf + i, argv[4].val.string, GX_MAX_TEXT - i);
	_gx_fn_xsstrcat(expr_sbuf, s + i + n, GX_MAX_TEXT);
	op.val.string = expr_sbuf;
	op.type = GX_STRING;
	return op;
}

gxOperand __cdecl _gx_fn_trim(gxOperand argv[])
{
	gxOperand op;
	LPCTSTR s1;
	LPTSTR s2;
	TCHAR c;
	int flag = 0;
	LPTSTR expr_sbuf = _gx_get_expr_sbuf();

	if (argv->val.count != 1)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 1);
	if (argv[1].type != GX_STRING)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	s1 = argv[1].val.string;
	s2 = expr_sbuf;
	while ((c = *s1++) != 0)
	{
		if (!_istspace(c))
		{
			flag = 1;
			*s2++ = c;
		}
		else if (flag)
		{
			*s2++ = _T(' ');
			flag = 0;
		}
	}
	if (*(s2 - 1) == _T(' '))
		*(s2 - 1) = _T('\0');
	else
		*s2 = _T('\0');
	op.val.string = expr_sbuf;
	op.type = GX_STRING;
	return op;
}

gxOperand __cdecl _gx_fn_value(gxOperand argv[])
{
	gxOperand op;

	if (argv->val.count != 1)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 1);
	if (argv[1].type != GX_STRING)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	op.val.number = _gxttof(argv[1].val.string);
	op.type = GX_NUMBER;
	return op;
}

gxOperand __cdecl _gx_fn_string(gxOperand argv[])
{
	gxOperand op;
	int places;
	gxNumber x;
	TCHAR fmt[10];
	LPTSTR expr_sbuf = _gx_get_expr_sbuf();

	if (argv->val.count != 2)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 1);
	_gx_cvt2constant(argv + 2);
	if (argv[2].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	if (argv[1].type == GX_NUMBER)
		x = argv[1].val.number;
	else
		x = 0.;
	places = (int) argv[2].val.number;
	if (places < 0 || places > 15)
		_gx_function_error(GX_FN_ERR_PLACES);

	// QA: 31989 - #if Secure Code Cleanup.
	_stprintf(fmt, _T("%%.%dlf"), places);
	_stprintf(expr_sbuf, fmt, x);
	op.val.string = expr_sbuf;
	op.type = GX_STRING;
	return op;
}

gxOperand __cdecl _gx_fn_s(gxOperand argv[])
{
	gxOperand op;
	gxCellValue cv;
	LPTSTR expr_sbuf = _gx_get_expr_sbuf();

	if (argv->val.count != 1)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	switch (argv[1].type)
	{
	case GX_STRING:
		_gx_fn_xsstrcpy(expr_sbuf, argv[1].val.string, GX_MAX_TEXT);
		break;
	case GX_NUMBER:
		*expr_sbuf = _T('\0');
		break;
#ifdef CELLRANGE
	case GX_CELL:
	case GX_RANGE:
		_gx_get_cell_value(_gx_get_expr_si(), argv[1].val.range.r0,
						   argv[1].val.range.c0, &cv);
		if (cv.type == GX_VALUE_STRING)
		{
			// QA: 31989 - #if Secure Code Cleanup.
			_tcscpy(expr_sbuf, cv.value.string);
			GX_XSfree(cv.value.string);
		}
		else
			*expr_sbuf = _T('\0');
		break;
#endif
	case GX_OP_ERROR:
		_gx_propagate_error(argv + 1);
	}
	op.val.string = expr_sbuf;
	op.type = GX_STRING;
	return op;
}

gxOperand __cdecl _gx_fn_n(gxOperand argv[])
{
	gxOperand op;
	gxNumber x = 0;
	gxCell *cp;

	if (argv->val.count != 1)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	switch (argv[1].type)
	{
	case GX_STRING:
		x = 0.;
		break;
	case GX_NUMBER:
		x = argv[1].val.number;
		break;
#ifdef CELLRANGE
	case GX_CELL:
	case GX_RANGE:
		cp = _gx_find_cell(_gx_get_expr_si(),
						   argv[1].val.range.r0, argv[1].val.range.c0);
		if (GX_CELL_CONTAINS_NUMBER(cp))
			x = cp->value.number;
		else
			x = 0.;
		break;
#endif
	case GX_OP_ERROR:
		_gx_propagate_error(argv + 1);
	}
	op.val.number = x;
	op.type = GX_NUMBER;
	return op;
}

gxOperand __cdecl _gx_fn_strlen(gxOperand argv[])
{
	gxNumber sum;
	gxCell *cp;
	gxOperand op;
	int i,
		n = argv->val.count;
	int si = _gx_get_expr_si();
	LPCTSTR text;

	sum = 0.;
	for (i = 0; i < n; i++)
		switch ((++argv)->type)
		{
		case GX_STRING:
			sum += (double) _tcslen(argv->val.string);
			break;
#ifdef CELLRANGE
		case GX_CELL:
			cp = _gx_find_cell(si, argv->val.range.r0, argv->val.range.c0);
			if (cp)
			{
				text = _gx_get_formatted_text(si, cp, NULL);
				sum += (double) _tcslen(text);
			}
			break;
#endif
		case GX_OP_ERROR:
			_gx_propagate_error(argv);
		default:
			_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
		}
	op.type = GX_NUMBER;
	op.val.number = sum;
	return op;
}

gxOperand __cdecl _gx_fn_strcat(gxOperand argv[])
{
	gxCell *cp;
	gxOperand op;
	TCHAR s[GX_MAX_TEXT];
	int i,
		n = argv->val.count;
	unsigned r,
		c;
	LPTSTR expr_sbuf = _gx_get_expr_sbuf();
	int si = _gx_get_expr_si();
	LPCTSTR text;

	*expr_sbuf = *s = _T('\0');

	for (i = 0; i < n; i++)
	{
		switch ((++argv)->type)
		{
		case GX_STRING:
			_gx_fn_xsstrcat(expr_sbuf, argv->val.string, GX_MAX_TEXT);
			break;
		case GX_NUMBER:
			// QA: 31989 - #if Secure Code Cleanup.
			_stprintf(s, _T("%.14g"), argv->val.number);
			_gx_fn_xsstrcat(expr_sbuf, s, GX_MAX_TEXT);
			break;
		case GX_CELL:
#ifdef CELLRANGE
			if ((cp = _gx_find_cell(si, argv->val.range.r0, argv->val.range.c0)) != NULL)
			{
				text = _gx_get_formatted_text(si, cp, NULL);
				_gx_fn_xsstrcat(expr_sbuf, text, GX_MAX_TEXT);
			}
#endif
			break;
		case GX_RANGE:
			for (r = argv->val.range.r0;
				 r <= argv->val.range.r1; r++)
				for (c = argv->val.range.c0;
					 c <= argv->val.range.c1; c++)
				{
					if ((cp = _gx_find_cell(si, r, c)) != NULL)
					{
						text = _gx_get_formatted_text(si, cp, NULL);
						_gx_fn_xsstrcat(expr_sbuf, text, GX_MAX_TEXT);
					}
				}
			break;
		case GX_OP_ERROR:
			_gx_propagate_error(argv);
		default:
			_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
		}
	}
	op.type = GX_STRING;
	op.val.string = expr_sbuf;
	return op;
}

/*
gxOperand __cdecl _gx_fn_format(gxOperand argv[])
{
#ifdef CELLRANGE
	gxOperand op;
	gxCell cell,
		  *cp;
	int n;
	TCHAR string[GX_MAX_TEXT];
	LPTSTR s;
	int si = _gx_get_expr_si();
	LPTSTR expr_sbuf = _gx_get_expr_sbuf();

	if (argv->val.count != 3)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 1);
	_gx_cvt2constant(argv + 2);
	if (argv[1].type != GX_STRING ||
		argv[2].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	switch (argv[3].type)
	{
	case GX_STRING:
		_gx_fn_xsstrcpy(string, argv[3].val.string, GX_MAX_TEXT);
		// cell.just = JUST_AUTO;
		cell.cell_type = GX_LABEL_CELL;
		cell.value_type = GX_VALUE_STRING;
		cell.value.string = string;
		cp = &cell;
		break;
	case GX_NUMBER:
		// cell.just = JUST_AUTO;
		cell.cell_type = GX_NUMERIC_CELL;
		cell.value_type = GX_VALUE_NUMERIC;
		cell.value.number = argv[3].val.number;
		cp = &cell;
		break;
	case GX_CELL:
		cp = _gx_find_cell(si, argv[3].val.range.r0, argv[3].val.range.c0);
		if (cp == NULL)
			cell.cell_type = GX_EMPTY_CELL;
		else
			cell = *cp;
		break;
	case GX_OP_ERROR:
		_gx_propagate_error(argv + 3);
	default:
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	}
	_gx_convert_upper(argv[1].val.string);
	s = argv[1].val.string;
	while (*s == _T(' '))
		s++;
	n = _tcslen(s);
	while (s[--n] == _T(' '))
	{
		if (n < 0)
			break;
		s[n] = _T('\0');
	}

	int nformat = GX_FMT_DEFAULT;
	if (!_tcscmp(_T("DEFAULT"), s))
			nformat = GX_FMT_DEFAULT;
	else if (!_tcscmp(_T("HIDDEN"), s))
			nformat = GX_FMT_HIDDEN;
	else if (!_tcscmp(_T("SCIENTIFIC"), s))
			nformat = GX_FMT_FLOAT;
	else if (!_tcscmp(_T("FIXED"), s))
			nformat = GX_FMT_FIXED;
	else if (!_tcscmp(_T("GENERAL"), s))
			nformat = GX_FMT_GEN;
	else if (!_tcscmp(_T("DOLLARS"), s))
			nformat = GX_FMT_DOLLARS;
	else if (!_tcscmp(_T("COMMA"), s))
			nformat = GX_FMT_COMMA;
	else if (!_tcscmp(_T("DD-MMM-YY"), s))
			nformat = GX_FMT_DAY_MONTH_YEAR;
	else if (!_tcscmp(_T("MMM-YY"), s))
			nformat = GX_FMT_MONTH_YEAR;
	else if (!_tcscmp(_T("DD-MMM"), s))
			nformat = GX_FMT_DAY_MONTH;
	else if (!_tcscmp(_T("HH:MM:SS"), s))
			nformat = GX_FMT_TIME;
	else if (!_tcscmp(_T("HEX"), s))
			nformat = GX_FMT_HEX;
	else if (!_tcscmp(_T("LOGIC"), s))
			nformat = GX_FMT_LOGIC;
	else if (!_tcscmp(_T("PERCENT"), s))
			nformat = GX_FMT_PERCENT;
	else if (!_tcscmp(_T("TEXT"), s))
			nformat = GX_FMT_TEXT;
	else if (!_tcscmp(_T("MM/DD/YY"), s))
			nformat = GX_FMT_DATE;
	else if (!_tcscmp(_T("DD.MM.YYYY"), s))
			nformat = GX_FMT_INTL_DATE;
	else if (!_tcscmp(_T("YYYY-MM-DD"), s))
			nformat = GX_FMT_ISO8061_DATE;
	else if (!_tcscmp(_T("CURRENCY1"), s))
			nformat = GX_FMT_CURRENCY_1;
	else if (!_tcscmp(_T("CURRENCY2"), s))
			nformat = GX_FMT_CURRENCY_2;
	else if (!_tcscmp(_T("CURRENCY3"), s))
			nformat = GX_FMT_CURRENCY_3;
	else if (!_tcscmp(_T("CURRENCY4"), s))
			nformat = GX_FMT_CURRENCY_4;
	else 
		 _gx_function_error(GX_FN_ERR_UNKNOWN_FMT);
	n = (int) argv[2].val.number;
	if (n < 0 || n > 15)
		_gx_function_error(GX_FN_ERR_PLACES);
	int places = n;

	_tcscpy(expr_sbuf, _gx_get_formatted_text(si, &cell, NULL));
	n = _tcslen(expr_sbuf);
	if (expr_sbuf[n] == _T(' '))
		expr_sbuf[n] = _T('\0');
	op.type = GX_STRING;
	op.val.string = expr_sbuf;
	return op;
#else
	gxOperand op;
	op.type = GX_NUMBER;
	_gx_function_error(GX_BAD_RANGE);
	return op;
#endif
}
*/


gxOperand __cdecl _gx_fn_tsv(gxOperand argv[])
{
	gxCell *cp;
	gxOperand op;
	TCHAR s[GX_MAX_TEXT];
	int i,
		n = argv->val.count;
	unsigned r,
		c;
	LPTSTR expr_sbuf = _gx_get_expr_sbuf();
	int si = _gx_get_expr_si();
	LPCTSTR text;

	*expr_sbuf = *s = _T('\0');

	for (i = 0; i < n; i++)
	{
		switch ((++argv)->type)
		{
		case GX_STRING:
			_gx_fn_xsstrcat(expr_sbuf, argv->val.string, GX_MAX_TEXT);
			_gx_fn_xsstrcat(expr_sbuf, _T("\n"), GX_MAX_TEXT);
			break;
		case GX_NUMBER:
			// QA: 31989 - #if Secure Code Cleanup.
			_stprintf(s, _T("%.14g"), argv->val.number);
			_gx_fn_xsstrcat(expr_sbuf, s, GX_MAX_TEXT);
			_gx_fn_xsstrcat(expr_sbuf, _T("\n"), GX_MAX_TEXT);
			break;
		case GX_CELL:
			if ((cp = _gx_find_cell(si, argv->val.range.r0, argv->val.range.c0)) != NULL)
			{
				text = _gx_get_formatted_text(si, cp, NULL);
				_gx_fn_xsstrcat(expr_sbuf, text, GX_MAX_TEXT);
				_gx_fn_xsstrcat(expr_sbuf, _T("\n"), GX_MAX_TEXT);
			}
			break;
		case GX_RANGE:
			for (r = argv->val.range.r0;
				 r <= argv->val.range.r1; r++)
				for (c = argv->val.range.c0;
					 c <= argv->val.range.c1; c++)
				{
					if ((cp = _gx_find_cell(si, r, c)) != NULL)
					{
						text = _gx_get_formatted_text(si, cp, NULL);
						_gx_fn_xsstrcat(expr_sbuf, text, GX_MAX_TEXT);
					}
					if (c < argv->val.range.c1)
						_gx_fn_xsstrcat(expr_sbuf, _T("\t"), GX_MAX_TEXT);
					else
						_gx_fn_xsstrcat(expr_sbuf, _T("\r\n"), GX_MAX_TEXT);
				}
			break;
		case GX_OP_ERROR:
			_gx_propagate_error(argv);
		default:
			_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
		}
	}
	op.type = GX_STRING;
	op.val.string = expr_sbuf;
	return op;
}
