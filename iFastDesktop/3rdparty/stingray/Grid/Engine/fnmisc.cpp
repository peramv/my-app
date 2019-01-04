///////////////////////////////////////////////////////////////////////////////
// fnmisc.cpp: Miscelaneous worksheet functions
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

#pragma warning (push)
#pragma warning (disable: 4700 4701) // 4701 SRSTUDIO-1792

#define CELLRANGE

extern int __cdecl _gx_fn_get_string(int r, int c, LPTSTR sbuf);


/* @@(cell) */
gxOperand __cdecl _gx_fn_indirect(gxOperand argv[])
{
#ifdef CELLRANGE
	gxOperand op;
	gxRange range;

	if (argv->val.count != 1)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 1);
	if (argv[1].type != GX_STRING)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	if (!_gx_text_to_range(argv[1].val.string, &range))
		_gx_function_error(GX_FN_ERR_ARG_CELL_OR_RNG);
	if (range.cell_only)
		op.type = GX_CELL;
	else
		op.type = GX_RANGE;
	op.val.range = range;
	return op;
#else
	gxOperand op;
	op.type = GX_NUMBER;
	_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	return op;
#endif
}

gxOperand __cdecl _gx_fn_row(gxOperand argv[])
{
#ifdef CELLRANGE
	gxOperand op;
	unsigned expr_row,
		expr_col;

	_gx_get_expr_rc(&expr_row, &expr_col);

	if (argv->val.count > 1)
		_gx_function_error(GX_FN_ERR_TOO_MANY_ARGS);
	if (argv->val.count == 1)
	{
		GX_HANDLE_OP_ERROR(argv[1]);
		if (argv[1].type != GX_CELL && argv[1].type != GX_RANGE)
			_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
		op.val.number = argv[1].val.range.r0;
	}
	else
	{
		op.val.number = expr_row;
	}
	op.type = GX_NUMBER;
	return op;
#else
	gxOperand op;
	op.type = GX_NUMBER;
	_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	return op;
#endif
}

gxOperand __cdecl _gx_fn_rows(gxOperand argv[])
{
#ifdef CELLRANGE
	gxOperand op;

	if (argv->val.count != 1)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	GX_HANDLE_OP_ERROR(argv[1]);
	if (argv[1].type != GX_RANGE)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	op.type = GX_NUMBER;
	op.val.number = argv[1].val.range.r1 - argv[1].val.range.r0 + 1;
	return op;
#else
	gxOperand op;
	op.type = GX_NUMBER;
	_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	return op;
#endif
}

gxOperand __cdecl _gx_fn_col(gxOperand argv[])
{
#ifdef CELLRANGE
	gxOperand op;
	unsigned expr_row,
		expr_col;

	_gx_get_expr_rc(&expr_row, &expr_col);

	if (argv->val.count > 1)
		_gx_function_error(GX_FN_ERR_TOO_MANY_ARGS);
	if (argv->val.count == 1)
	{
		GX_HANDLE_OP_ERROR(argv[1]);
		if (argv[1].type != GX_CELL && argv[1].type != GX_RANGE)
			_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
		op.val.number = argv[1].val.range.c0;
	}
	else
	{
		op.val.number = expr_col;
	}
	op.type = GX_NUMBER;
	return op;
#else
	gxOperand op;
	op.type = GX_NUMBER;
	_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	return op;
#endif
}

gxOperand __cdecl _gx_fn_cols(gxOperand argv[])
{
#ifdef CELLRANGE
	gxOperand op;

	if (argv->val.count != 1)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	GX_HANDLE_OP_ERROR(argv[1]);
	if (argv[1].type != GX_RANGE)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	op.type = GX_NUMBER;
	op.val.number = argv[1].val.range.c1 - argv[1].val.range.c0 + 1;
	return op;
#else
	gxOperand op;
	op.type = GX_NUMBER;
	_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	return op;
#endif
}

gxOperand __cdecl _gx_fn_cellref(gxOperand argv[])
{
#ifdef CELLRANGE
	gxOperand op;

	if (argv->val.count != 2)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 1);
	_gx_cvt2constant(argv + 2);
	if (argv[1].type != GX_NUMBER || argv[2].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	op.type = GX_CELL;
	op.val.range.c0 = op.val.range.c1 = (int) argv[1].val.number;
	op.val.range.r0 = op.val.range.r1 = (int) argv[2].val.number;
	op.val.range.cell_only = 1;
	if (!GX_BOUNDS_CHECK(op.val.range.r0, op.val.range.c0))
		_gx_function_error(GX_FN_ERR_INVALID_CELL_REF);
	return op;
#else
	gxOperand op;
	op.type = GX_NUMBER;
	_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	return op;
#endif
}

gxOperand __cdecl _gx_fn_rangeref(gxOperand argv[])
{
#ifdef CELLRANGE
	gxOperand op;

	if (argv->val.count != 4)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 1);
	_gx_cvt2constant(argv + 2);
	_gx_cvt2constant(argv + 3);
	_gx_cvt2constant(argv + 4);
	if (argv[1].type != GX_NUMBER || argv[2].type != GX_NUMBER ||
		argv[3].type != GX_NUMBER || argv[4].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	op.type = GX_RANGE;
	op.val.range.c0 = (int) argv[1].val.number;
	op.val.range.r0 = (int) argv[2].val.number;
	op.val.range.c1 = (int) argv[3].val.number;
	op.val.range.r1 = (int) argv[4].val.number;
	op.val.range.abs_r0 = 0;
	op.val.range.abs_r1 = 0;
	op.val.range.abs_c0 = 0;
	op.val.range.abs_c1 = 0;
	op.val.range.cell_only = 0;
	if (!GX_BOUNDS_CHECK(op.val.range.r0, op.val.range.c0) ||
		!GX_BOUNDS_CHECK(op.val.range.r1, op.val.range.c1))
		_gx_function_error(GX_FN_ERR_INVALID_RNG_REF);
	return op;
#else
	gxOperand op;
	op.type = GX_NUMBER;
	_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	return op;
#endif
}

gxOperand __cdecl _gx_fn_choose(gxOperand argv[])
{
#ifdef CELLRANGE
	gxOperand op;
	int select;
	LPTSTR expr_sbuf = _gx_get_expr_sbuf();

	if (argv->val.count == 0)
		_gx_function_error(GX_FN_ERR_TOO_FEW_ARGS);
	_gx_cvt2constant(argv + 1);
	if (argv[1].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_FIRST_NUMERIC);
	select = (int) argv[1].val.number;
	if (select < 0 || select > argv->val.count - 2)
		_gx_function_error(GX_FN_ERR_SEL_OUT_OF_RNG);
	select += 2;
	op = _gx_do_eval(argv[select].val.etree.nbuf, argv[select].val.etree.start);
	if (op.type == GX_STRING)
	{
		// QA: 31989 - #if Secure Code Cleanup.
		_tcscpy(expr_sbuf, op.val.string);
		GX_XSfree(op.val.string);
		op.val.string = expr_sbuf;
	}
	return op;
#else
	gxOperand op;
	op.type = GX_NUMBER;
	_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	return op;
#endif
}

gxOperand __cdecl _gx_fn_date(gxOperand argv[])
{
	gxOperand op;
	int year,
		month,
		day;

	if (argv->val.count != 3)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 1);
	_gx_cvt2constant(argv + 2);
	_gx_cvt2constant(argv + 3);
	if (argv[1].type != GX_NUMBER || argv[1].type != GX_NUMBER ||
		argv[1].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_ARG_NUMERIC);
	year = (int) argv[1].val.number;
	month = (int) argv[2].val.number;
	day = (int) argv[3].val.number;

	if ((op.val.number = _gx_encode_date(_gx_get_expr_si(), year, month, day)) == 0)
		_gx_function_error(GX_FN_ERR_INVALID_DATE);
	op.type = GX_NUMBER;
	return op;
}

gxOperand __cdecl _gx_fn_time(gxOperand argv[])
{
	gxOperand op;
	int hr,
		min,
		sec;

	if (argv->val.count != 3)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 1);
	_gx_cvt2constant(argv + 2);
	_gx_cvt2constant(argv + 3);
	if (argv[1].type != GX_NUMBER || argv[1].type != GX_NUMBER ||
		argv[1].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_ARG_NUMERIC);
	hr = (int) argv[1].val.number;
	min = (int) argv[2].val.number;
	sec = (int) argv[3].val.number;

	if (!_gx_encode_time(&(op.val.number), hr, min, sec))
		_gx_function_error(GX_FN_ERR_TIME);
	op.type = GX_NUMBER;
	return op;
}

gxOperand __cdecl _gx_fn_hour(gxOperand argv[])
{
	gxOperand op;
	int hr,
		min,
		sec;
	gxNumber x;

	x = _gx_get_one_number(argv);
	if (!_gx_decode_time(x, &hr, &min, &sec))
		_gx_function_error(GX_FN_ERR_TIME);
	op.type = GX_NUMBER;
	op.val.number = (double) hr;
	return op;
}

gxOperand __cdecl _gx_fn_minute(gxOperand argv[])
{
	gxOperand op;
	int hr,
		min,
		sec;
	gxNumber x;

	x = _gx_get_one_number(argv);
	if (!_gx_decode_time(x, &hr, &min, &sec))
		_gx_function_error(GX_FN_ERR_TIME);
	op.type = GX_NUMBER;
	op.val.number = (double) min;
	return op;
}

gxOperand __cdecl _gx_fn_second(gxOperand argv[])
{
	gxOperand op;
	int hr,
		min,
		sec;
	gxNumber x;

	x = _gx_get_one_number(argv);
	if (!_gx_decode_time(x, &hr, &min, &sec))
		_gx_function_error(GX_FN_ERR_TIME);
	op.type = GX_NUMBER;
	op.val.number = (double) sec;
	return op;
}

gxOperand __cdecl _gx_fn_day(gxOperand argv[])
{
	gxOperand op;
	int year,
		month,
		day;
	gxNumber x;

	x = _gx_get_one_number(argv);
	if (x < 0.0 || x >= 73051.0)
		_gx_function_error(GX_FN_ERR_INVALID_DATE);
	_gx_decode_date(_gx_get_expr_si(), (int) x, &year, &month, &day);
	op.type = GX_NUMBER;
	op.val.number = (double) day;
	return op;
}

gxOperand __cdecl _gx_fn_month(gxOperand argv[])
{
	gxOperand op;
	int year,
		month,
		day;
	gxNumber x;

	x = _gx_get_one_number(argv);
	if (x < 0.0 || x >= 73051.0)
		_gx_function_error(GX_FN_ERR_INVALID_DATE);
	_gx_decode_date(_gx_get_expr_si(), (int) x, &year, &month, &day);
	op.type = GX_NUMBER;
	op.val.number = (double) month;
	return op;
}

gxOperand __cdecl _gx_fn_year(gxOperand argv[])
{
	gxOperand op;
	int year,
		month,
		day;
	gxNumber x;

	x = _gx_get_one_number(argv);
	if (x < 0.0 || x >= 73051.0)
		_gx_function_error(GX_FN_ERR_INVALID_DATE);
	_gx_decode_date(_gx_get_expr_si(), (int) x, &year, &month, &day);
	op.type = GX_NUMBER;
	op.val.number = (double) year;
	return op;
}

gxOperand __cdecl _gx_fn_now(gxOperand argv[])
{
	gxOperand op;
	int year,
		month,
		day;
	long dateval;
	int hr,
		min,
		sec;

	if (argv->val.count)
		_gx_function_error(GX_FN_ERR_NO_ARGS);
	_gx_current_time(&year, &month, &day, &hr, &min, &sec);
	dateval = _gx_encode_date(_gx_get_expr_si(), year, month, day);
	_gx_encode_time(&(op.val.number), hr, min, sec);
	op.val.number += dateval;
	op.type = GX_NUMBER;
	return op;
}

gxOperand __cdecl _gx_fn_today(gxOperand argv[])
{
	gxOperand op;
	int year,
		month,
		day;
	int hr,
		min,
		sec;

	if (argv->val.count)
		_gx_function_error(GX_FN_ERR_NO_ARGS);
	_gx_current_time(&year, &month, &day, &hr, &min, &sec);
	op.val.number = (double) _gx_encode_date(_gx_get_expr_si(), year, month, day);
	op.type = GX_NUMBER;
	return op;
}

#ifdef CELLRANGE
static int lookup(gxOperand * opp, int r, int c)
{
	gxNumber x;
	LPTSTR expr_sbuf = _gx_get_expr_sbuf();

	if (_gx_fn_get_string(r, c, expr_sbuf))
	{
		opp->type = GX_STRING;
		opp->val.string = expr_sbuf;
		return 1;
	}
	else if (_gx_fn_get_value(r, c, &x))
	{
		opp->type = GX_NUMBER;
		opp->val.number = x;
		return 1;
	}
	else
	{
		opp->type = GX_NUMBER;
		opp->val.number = 0.0;
		return 1;   /* changed from "0" to fix wks "bug" */
	}
}
#endif

gxOperand __cdecl _gx_fn_vlookup(gxOperand argv[])
{
#ifdef CELLRANGE
	gxOperand op,
			  op1,
			  lastop1;
	unsigned r,
		c,
		offset,
		colms;

	if (argv->val.count != 3)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 1);
	GX_HANDLE_OP_ERROR(argv[2]);
	_gx_cvt2constant(argv + 3);
	if ((argv[1].type != GX_NUMBER && argv[1].type != GX_STRING) ||
		argv[2].type != GX_RANGE ||
		argv[3].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	offset = (int) argv[3].val.number;
	colms = argv[2].val.range.c1 - argv[2].val.range.c0 + 1;
	if (offset < 0 || offset >= colms)
		_gx_function_error(GX_FN_ERR_OFF_OUT_OF_RNG);
	c = argv[2].val.range.c0;
	for (r = argv[2].val.range.r0; r <= argv[2].val.range.r1; r++)
	{
		lastop1 = op1;
		if (!lookup(&op1, r, c))
			_gx_function_error(GX_FN_ERR_INDEX_COL_E_CELL);
		if (argv[1].type == GX_NUMBER)
		{
			if (op1.type == GX_NUMBER)
			{
				if (argv[1].val.number == op1.val.number)
				{
					lookup(&op, r, c + offset);
					return op;
				}
				else if (argv[1].val.number < op1.val.number)
				{
					if (r > argv[2].val.range.r0)
					{
						lookup(&op, r - 1, c + offset);
						return op;
					}
					else
						break;
				}
				else if (r == argv[2].val.range.r1)
				{
					lookup(&op, r, c + offset);
					return op;
				}
			}
			else
			{   /* op1.type == GX_STRING */
				if (r == argv[2].val.range.r1)
				{
					lookup(&op, r, c + offset);
					return op;
				}
			}
		}
		else if (argv[1].type == GX_STRING && op1.type == GX_STRING)
		{
			if (!_tcscmp(argv[1].val.string, op1.val.string))
			{
				lookup(&op, r, c + offset);
				return op;
			}
		}
	}
	_gx_function_error(GX_FN_ERR_BAD_LOOKUP);
	return op;
#else
	gxOperand op;
	op.type = GX_NUMBER;
	_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	return op;
#endif
}

gxOperand __cdecl _gx_fn_hlookup(gxOperand argv[])
{
#ifdef CELLRANGE
	gxOperand op,
			  op1,
			  lastop1;
	unsigned r,
		c,
		offset,
		rows;

	if (argv->val.count != 3)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 1);
	GX_HANDLE_OP_ERROR(argv[2]);
	_gx_cvt2constant(argv + 3);
	if ((argv[1].type != GX_NUMBER && argv[1].type != GX_STRING) ||
		argv[2].type != GX_RANGE ||
		argv[3].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	offset = (int) argv[3].val.number;
	rows = argv[2].val.range.r1 - argv[2].val.range.r0 + 1;
	if (offset < 0 || offset >= rows)
		_gx_function_error(GX_FN_ERR_ROW_OUT_OF_RNG);
	r = argv[2].val.range.r0;
	for (c = argv[2].val.range.c0; c <= argv[2].val.range.c1; c++)
	{
		lastop1 = op1;
		if (!lookup(&op1, r, c))
			_gx_function_error(GX_FN_ERR_INDEX_ROW_E_CELL);
		if (argv[1].type == GX_NUMBER)
		{
			if (op1.type == GX_NUMBER)
			{
				if (argv[1].val.number == op1.val.number)
				{
					lookup(&op, r + offset, c);
					return op;
				}
				else if (argv[1].val.number < op1.val.number)
				{
					if (c > argv[2].val.range.c0)
					{
						lookup(&op, r + offset, c - 1);
						return op;
					}
					else
						break;
				}
				else if (c == argv[2].val.range.c1)
				{
					lookup(&op, r + offset, c);
					return op;
				}
			}
			else
			{   /* op1.type == GX_STRING */
				if (c == argv[2].val.range.c1)
				{
					lookup(&op, r + offset, c);
					return op;
				}
			}
		}
		else if (argv[1].type == GX_STRING && op1.type == GX_STRING)
		{
			if (!_tcscmp(argv[1].val.string, op1.val.string))
			{
				lookup(&op, r + offset, c);
				return op;
			}
		}
	}
	_gx_function_error(GX_FN_ERR_BAD_LOOKUP);
	return op;
#else
	gxOperand op;
	op.type = GX_NUMBER;
	_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	return op;
#endif
}

gxOperand __cdecl _gx_fn_alarm(gxOperand argv[])
{
#ifdef CELLRANGE
	gxOperand op;
	int status;
	LPTSTR expr_sbuf = _gx_get_expr_sbuf();
	unsigned expr_row,
		expr_col;

	_gx_get_expr_rc(&expr_row, &expr_col);

	_gx_cvt2constant(argv + 1);
	if (argv[1].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	if (argv[1].val.number == 0.0)
	{
		op.type = GX_NUMBER;
		op.val.number = 0.0;
		return op;
	}
#if _MFC_VER >= 0x0300
	Beep(400, 100);
#endif

	op = _gx_do_eval(argv[2].val.etree.nbuf, argv[2].val.etree.start);

	if (op.type == GX_STRING)
	{   /* must be a v2-style deferred expr */
		// QA: 31989 - #if Secure Code Cleanup.
		_tcscpy(expr_sbuf, op.val.string);
		status = _gx_si_evaluate_expr(_gx_get_expr_si(),
									  expr_sbuf, expr_row, expr_col, &op);
		if (!status)
			_gx_function_error(GX_FN_ERR_COND_STR_PARSE);
		if (op.type == GX_STRING)
		{
			// QA: 31989 - #if Secure Code Cleanup.
			_tcscpy(expr_sbuf, op.val.string);
			GX_XSfree(op.val.string);
			op.val.string = expr_sbuf;
		}
	}
	return op;
#else
	gxOperand op;
	op.type = GX_NUMBER;
	_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	return op;
#endif
}

gxOperand __cdecl _gx_fn_salarm(gxOperand argv[])
{
#ifdef CELLRANGE
	gxOperand op;
	int status;
	LPTSTR expr_sbuf = _gx_get_expr_sbuf();
	unsigned expr_row,
		expr_col;

	_gx_get_expr_rc(&expr_row, &expr_col);

	_gx_cvt2constant(argv + 1);
	if (argv[1].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	if (argv[1].val.number == 0.0)
	{
		op.type = GX_NUMBER;
		op.val.number = 0.0;
		return op;
	}
	op = _gx_do_eval(argv[2].val.etree.nbuf, argv[2].val.etree.start);

	if (op.type == GX_STRING)
	{   /* must be a v2-style deferred expr */
		// QA: 31989 - #if Secure Code Cleanup.
		_tcscpy(expr_sbuf, op.val.string);
		status = _gx_si_evaluate_expr(_gx_get_expr_si(),
									  expr_sbuf, expr_row, expr_col, &op);
		if (!status)
			_gx_function_error(GX_FN_ERR_COND_STR_PARSE);
		if (op.type == GX_STRING)
		{
			// QA: 31989 - #if Secure Code Cleanup.
			_tcscpy(expr_sbuf, op.val.string);
			GX_XSfree(op.val.string);
			op.val.string = expr_sbuf;
		}
	}
	return op;
#else
	gxOperand op;
	op.type = GX_NUMBER;
	_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	return op;
#endif
}

gxOperand __cdecl _gx_fn_message(gxOperand argv[])
{
#ifdef CELLRANGE
	gxOperand op;

	if (argv->val.count != 2)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 1);
	_gx_cvt2constant(argv + 2);
	if (argv[1].type != GX_NUMBER || argv[2].type != GX_STRING)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	if (argv[1].val.number != 0.0)
	{
		gxSheetContext *context = _gx_get_context_ptr(_gx_get_expr_si());

		if (context->first_error)
		{   /* don't overwrite error msg */
#if _MFC_VER >= 0x0300
			Beep(400, 100);
#endif

			// QA: 31989 - #if Secure Code Cleanup.
			_tcscpy(context->szErrorText, argv[2].val.string);
			context->first_error = 0;
		}
	}
	op.type = GX_NUMBER;
	op.val.number = argv[1].val.number;
	return op;
#else
	gxOperand op;
	op.type = GX_NUMBER;
	_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	return op;
#endif
}

gxOperand __cdecl _gx_fn_init(gxOperand argv[])
{
#ifdef CELLRANGE
	gxOperand op;
	int select;
	LPTSTR expr_sbuf = _gx_get_expr_sbuf();

/*
		if (argv->val.count != 2)
				_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
*/
	select = (_gx_check_recalc_status(_gx_get_expr_si()) & 64) ? 2 : 1;
	op = _gx_do_eval(argv[select].val.etree.nbuf, argv[select].val.etree.start);
	if (op.type == GX_STRING)
	{
		_tcscpy(expr_sbuf, op.val.string);
		GX_XSfree(op.val.string);
		op.val.string = expr_sbuf;
	}
	return op;
/*
		_gx_cvt2constant(argv+select);
		if (argv[select].type != GX_NUMBER && argv[1].type != GX_STRING &&
				argv[select].type != GX_OP_ERROR)
						_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
		return argv[select];
*/
#else
	gxOperand op;
	op.type = GX_NUMBER;
	_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	return op;
#endif
}

gxOperand __cdecl _gx_fn_datevalue(gxOperand argv[])
{
	gxOperand op;
	int month,
		day,
		year;
	int dummy;

	if (argv->val.count != 1)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 1);
	if (argv[1].type != GX_STRING)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	if (!_gx_get_date(_gx_get_expr_si(), argv[1].val.string, &month, &day, &year, &dummy))
		_gx_function_error(GX_FN_ERR_INVALID_DATE);
	if ((op.val.number = _gx_encode_date(_gx_get_expr_si(), year, month, day)) == 0)
		_gx_function_error(GX_FN_ERR_INVALID_DATE);
	op.type = GX_NUMBER;
	return op;
}

gxOperand __cdecl _gx_fn_timevalue(gxOperand argv[])
{
	gxOperand op;
	int hr,
		min,
		sec;
	LPTSTR time;

	if (argv->val.count != 1)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 1);
	if (argv[1].type != GX_STRING)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	time = argv[1].val.string;
	if (!_gx_get_time(time, &hr, &min, &sec))
		_gx_function_error(GX_FN_ERR_TIME);
	if (!_gx_encode_time(&(op.val.number), hr, min, sec))
		_gx_function_error(GX_FN_ERR_TIME);
	op.type = GX_NUMBER;
	return op;
}

gxOperand __cdecl _gx_fn_regex(gxOperand argv[])
{
	gxOperand op;
	LPCTSTR error_text;

	if (argv->val.count != 2)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 1);
	_gx_cvt2constant(argv + 2);
	if (argv[1].type != GX_STRING || argv[2].type != GX_STRING)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	if ((error_text = _gx_XSre_comp(argv[1].val.string)) != NULL)
		_gx_function_error(GX_FN_ERR_REGEX);
	op.type = GX_NUMBER;
	op.val.number = (double) _gx_XSre_exec(argv[2].val.string);
	return op;
}

// not supported:
#if 0
gxOperand __cdecl _gx_fn_annotate(gxOperand argv[])
{
	gxOperand op;
	int i;
	LPTSTR expr_sbuf = _gx_get_expr_sbuf();

	if (argv->val.count < 3)
		_gx_function_error(GX_FN_ERR_TOO_FEW_ARGS);
	if (argv->val.count > 5)
		_gx_function_error(GX_FN_ERR_TOO_MANY_ARGS);
	for (i = 1; i <= argv->val.count; i++)
	{
		_gx_cvt2constant(argv + i);
		if (i == 1)
		{
			if (argv[i].type != GX_STRING)
				_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
		}
		else
		{
			if (argv[i].type != GX_NUMBER)
				_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
		}
	}
	switch (argv->val.count)
	{
	case 3:
		_stprintf(expr_sbuf, _T("(%lg,%lg)%s"),
				argv[2].val.number, argv[3].val.number,
				argv[1].val.string);
		break;
	case 4:
		_stprintf(expr_sbuf, _T("(%lg,%lg,%lg)%s"),
				argv[2].val.number, argv[3].val.number,
				argv[4].val.number, argv[1].val.string);
		break;
	case 5:
		_stprintf(expr_sbuf, _T("(%lg,%lg,%lg,%lg)%s"),
				argv[2].val.number, argv[3].val.number,
				argv[4].val.number, argv[5].val.number,
				argv[1].val.string);
		break;
	}
	op.type = GX_STRING;
	op.val.string = expr_sbuf;
	return op;
}

gxOperand __cdecl _gx_fn_xvalue(gxOperand argv[])
{
#ifdef CELLRANGE
	gxOperand op;
	// LPCTSTR error_text;
	int ci;
	gxCellValue cv;

	if (argv->val.count != 2)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 1);
	if (argv[1].type != GX_STRING || argv[2].type != GX_CELL)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	ci = get_file_cache_handle(_gx_get_expr_si(), argv[1].val.string);
	if (ci > 0)
	{   /* success */
		get_file_cache_value(ci,
							 argv[2].val.range.r0, argv[2].val.range.c0,
							 &cv);
		switch (cv.type)
		{
		case GX_VALUE_NUMERIC:
			op.type = GX_NUMBER;
			op.val.number = cv.value.number;
			break;
		case GX_VALUE_STRING:
			_tcscpy(_gx_get_expr_sbuf(), cv.value.string);
			GX_XSfree(cv.value.string);
			op.type = GX_STRING;
			op.val.string = _gx_get_expr_sbuf();
			break;
		case GX_VALUE_ERROR:
			_gx_function_error(GX_FN_ERR_CELL_ERROR);
		case GX_VALUE_NA:
		case GX_VALUE_NONE:
			op.type = GX_NUMBER;
			op.val.number = 0.0;    /* empty cells are zero for now */
			break;
		default:
			assert(cv.type);
		}
	}
	else if (ci == 0)
	{   /* file cache full (should never happen) */
		_gx_function_error(0);
	}
	else
	{   /* ci == -1; couldn't access file */
		_gx_function_error(GX_FN_ERR_X_FILE_OPEN);
	}
	return op;
#else
	gxOperand op;
	op.type = GX_NUMBER;
	_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	return op;
#endif
}

#endif

#pragma warning (pop) //4700