///////////////////////////////////////////////////////////////////////////////
// fnmisc2.cpp: Miscelaneous worksheet functions
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

#if _MFC_VER < 0x0300
#pragma warning(disable:4051)
#endif
#pragma warning(disable:4244) // conversion from 'double' to 'int', possible loss of data
// This warning happens when a worksheet function needs an INT parameter
// and converts the Number value to an int without explicit type cast
// I prefer to turn that warning off here and not to type-cast each function - this
// lets me later find all those affected lines again easier

#define CELLRANGE
extern int __cdecl _gx_fn_get_string(int r, int c, LPTSTR sbuf);
extern int __cdecl _gx_analyze_ranges(gxRange * rp1, gxRange * rp2);
void __cdecl _gx_dump_matrix(gxMatrix m);

/*
int compare_numpair_ascd(np1, np2)
NumPair *np1, *np2;
{
	 if (np1->val1<np2->val1)
		  return -1;
	 else if (np1->val1==np2->val1)
		  return 0;
	 else return 1;
}
*/

gxOperand __cdecl _gx_fn_days360(gxOperand argv[])
{
	gxOperand op;
	int date1,
		date2;

	if (argv->val.count != 2)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 1);
	_gx_cvt2constant(argv + 2);
	if ((argv[1].type != GX_NUMBER) || (argv[2].type != GX_NUMBER))
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	date1 = argv[1].val.number;
	date2 = argv[2].val.number;
	if (!GX_VALID_DT(date1) || !GX_VALID_DT(date2))
		_gx_function_error(GX_FN_ERR_INVALID_DATE);
	op.val.number = (gxNumber) _gx_days360(_gx_get_expr_si(), date1, date2);
	op.type = GX_NUMBER;
	return op;
}


gxOperand __cdecl _gx_fn_edate(gxOperand argv[])
{
	gxOperand op;
	int start_date,
		mos,
		month,
		day,
		year,
		yrs;
	long edate;
	int si = _gx_get_expr_si();

	if (argv->val.count != 2)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 1);
	_gx_cvt2constant(argv + 2);
	if ((argv[1].type != GX_NUMBER) || (argv[2].type != GX_NUMBER))
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	start_date = argv[1].val.number;
	mos = argv[2].val.number;
	if (!_gx_decode_date(si, start_date, &year, &month, &day))
		_gx_function_error(GX_FN_ERR_INVALID_DATE);
	yrs = mos / 12;
	mos = mos % 12;
	year += yrs;
	if ((month += mos) <= 0)
	{
		year--;
		month += 12;
	}
	else if (month > 12)
	{
		year++;
		month -= 12;
	}
	if (day > _gx_end_of_month(month, year))
		day = _gx_end_of_month(month, year);

/*
	 if (day > _gx_months[month-1].noDays) day = _gx_months[month-1].noDays;
*/
	if ((edate = _gx_encode_date(si, year, month, day)) == 0)
		_gx_function_error(GX_FN_ERR_INVALID_DATE);
	op.val.number = (gxNumber) edate;
	op.type = GX_NUMBER;
	return op;
}


gxOperand __cdecl _gx_fn_eomonth(gxOperand argv[])
{
	gxOperand op;
	int month,
		day,
		year,
		yrs,
		mos,
		type = 1;
	int si = _gx_get_expr_si();

	if (argv->val.count != 2)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 1);
	_gx_cvt2constant(argv + 2);

	if ((argv[1].type != GX_NUMBER) || (argv[2].type != GX_NUMBER))
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	if (!_gx_decode_date(si, (int) argv[1].val.number, &year, &month, &day))
		_gx_function_error(GX_FN_ERR_INVALID_DATE);

	mos = argv[2].val.number;
	if (mos < 0)
		type = -1;
	yrs = mos / 12;
	mos = type * (abs(mos) % 12);
	year += yrs;
	month += mos;
	if (month < 1)
	{
		year--;
		month += 12;
	}
	else if (month > 12)
	{
		year++;
		month -= 12;
	}
	day = _gx_end_of_month(month, year);
/*     if (month==2 && GX_LEAPYEAR(year)) day++;    leap year */
	if ((op.val.number = _gx_encode_date(si, year, month, day)) == 0)
		_gx_function_error(GX_FN_ERR_INVALID_DATE);
	op.type = GX_NUMBER;
	return op;
}


static int weekday(int date)
{
	int date_ref = 1;   /* we know that 1/1/1900 is sunday a */
	return ((date - date_ref) % 7 + 1);
}

gxOperand __cdecl _gx_fn_weekday(gxOperand argv[])
{
	gxOperand op;
	gxNumber x;

	if (argv->val.count != 1)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 1);
	if (argv[1].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	x = _gx_get_one_number(argv);
	if (!GX_VALID_DT(x))
		_gx_function_error(GX_FN_ERR_INVALID_DATE);
	op.val.number = (gxNumber) weekday((int) argv[1].val.number);
	op.type = GX_NUMBER;
	return op;
}


gxOperand __cdecl _gx_fn_yearfrac(gxOperand argv[])
{

	gxOperand op;
	int start_date,
		end_date,
		basis = 0;
	gxNumber x;

	_gx_cvt2constant(argv + 1);
	_gx_cvt2constant(argv + 2);
	if (argv->val.count < 2 || argv->val.count > 3)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	if (argv[1].type != GX_NUMBER || argv[2].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);

	start_date = argv[1].val.number;
	end_date = argv[2].val.number;
	if (argv->val.count == 3)
	{
		_gx_cvt2constant(argv + 3);
		if (argv[3].type != GX_NUMBER)
			_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
		basis = argv[3].val.number;
	}
	_gx_find_yearfrac1(_gx_get_expr_si(), start_date, end_date, basis, &x);
	op.val.number = x;
	op.type = GX_NUMBER;
	return op;
}


static int do_one_match(LPCTSTR s1, LPCTSTR s2)
{
	// TODO: is that DBCS aware?
	while (*s1 != _T('\0'))
	{
		switch (*s1)
		{
		case _T('?'):
			break;
		case _T('*'):
			while (*(++s1) == _T('*'));
			if (*s1 == _T('\0'))
				return 1;   /* case like  "t*" matches"test" */
			while (*s2 != _T('\0'))
			{
				if (*s1 == *s2 || *s1 == _T('?'))
					if (do_one_match(s1, s2))
						return 1;
				s2++;
			}
			return 0;
		default:
			if (*s1 != *s2)
				return 0;
		}
		s1++;
		s2++;
	}
	if (*s2 != _T('\0'))
		return 0;
	return 1;
}

#ifdef CELLRANGE
static int match_string(LPCTSTR s, gxRange data)
{
	int count = 0;
	unsigned r,
		c;
	LPTSTR x = _gx_get_expr_sbuf();

	for (r = data.r0; r <= data.r1; r++)
		for (c = data.c0; c <= data.c1; c++)
		{
			count++;
			if (_gx_fn_get_string(r, c, x))
				if (do_one_match(s, x))
					return count;
		}
	return 0;
}
#endif

gxOperand __cdecl _gx_fn_match(gxOperand argv[])
{
#ifdef CELLRANGE
	gxOperand op;
	gxNumber key,
			 x,
			 match = 0;
	int match_type = 0,
		count = 0,
		m_flag = 0;
	LPCTSTR str_key;
	gxScanBuf scan;
	gxCell *cp;

	if (argv->val.count < 2)
		_gx_function_error(GX_FN_ERR_TOO_FEW_ARGS);
	if (argv->val.count > 3)
		_gx_function_error(GX_FN_ERR_TOO_MANY_ARGS);

	_gx_cvt2constant(argv + 1);
	GX_HANDLE_OP_ERROR(argv[2]);
	if ((argv[1].type != GX_NUMBER && argv[1].type != GX_STRING)
		|| (argv[2].type != GX_RANGE))
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	if (argv->val.count == 3)
	{
		if (argv[3].type != GX_NUMBER)
			_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
		else if (argv[3].val.number != 0)
		{
			_gx_cvt2constant(argv + 3);
			match_type = fabs(argv[3].val.number) / argv[3].val.number;
		}
	}
	if (argv[2].val.range.r0 != argv[2].val.range.r1 &&
		argv[2].val.range.c0 != argv[2].val.range.c1)
		_gx_function_error(GX_FN_ERR_IMPROP_DIM);
	op.type = GX_NUMBER;
	if (argv[1].type == GX_STRING)
		if (match_type == 0)
		{
			str_key = argv[1].val.string;
			op.val.number =
				(gxNumber) match_string(str_key, argv[2].val.range);
			//if (op.val.number == 0)
			//	_gx_function_error(GX_FN_ERR_NO_MATCH);
			//else
				return op;
		}
		else
			_gx_function_error(GX_FN_ERR_STR_MATCH);
	key = argv[1].val.number;
	_gx_init_range_scan(_gx_get_expr_si(), argv[2].val.range, &scan,
						GX_CONSTANT_LIST | GX_RECALC_LIST);
	while ((cp = _gx_do_range_scan(&scan)) != NULL)
		if (_gx_fn_get_value(cp->row, cp->col, &x))
		{
			count++;
			if (x == key)
			{   /* apply to all 3 match types */
				m_flag = 1;
				op.val.number = count;
				return op;
			}
			switch (match_type)
			{
			case 1:
				if (x < key)
				{
					if (m_flag)
					{
						if (x > match)
						{
							match = x;
							op.val.number = (gxNumber) count;
						}
					}
					else
					{
						match = x;
						m_flag = 1;
						op.val.number = (gxNumber) count;
					}
				}
				break;
			case -1:
				if (x > key)
				{
					if (m_flag)
					{
						if (x < match)
						{
							match = x;
							op.val.number = (gxNumber) count;
						}
					}
					else
					{
						match = x;
						m_flag = 1;
						op.val.number = (gxNumber) count;
					}
				}
				break;
			}
		}
	if (!m_flag)
	{
		op.val.number = (gxNumber) 0;
	//	_gx_function_error(GX_FN_ERR_NO_MATCH);
	}
	return op;
#else
	gxOperand op;
	op.type = GX_NUMBER;
	_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	return op;
#endif
}


gxOperand __cdecl _gx_fn_networkdays(gxOperand argv[])
{
#ifdef CELLRANGE
	gxOperand op;
	int hday_count = 0,
		hdays = 0,
		wkends;
	unsigned n;
	int i,
		d,
		day1,
		day2;
	gxNumber x,
			 w,
			*hday_list = 0;
	gxScanBuf scan;
	gxCell *cp;

	if (argv->val.count < 2)
		_gx_function_error(GX_FN_ERR_TOO_FEW_ARGS);
	if (argv->val.count > 3)
		_gx_function_error(GX_FN_ERR_TOO_MANY_ARGS);

	_gx_cvt2constant(argv + 1);
	_gx_cvt2constant(argv + 2);
	GX_HANDLE_OP_ERROR(argv[3]);
	if ((argv[1].type != GX_NUMBER) || (argv[2].type != GX_NUMBER))
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);

	if (argv->val.count == 3)
	{
		if (!((argv[3].type == GX_RANGE) || (argv[3].type == GX_CELL)))
			_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
		switch (argv[3].type)
		{
		case GX_CELL:
			if (_gx_fn_get_value(argv[3].val.range.r0,
								 argv[3].val.range.c0, &x))
			{
				hday_count = 1;
				hday_list = _gx_mknumarray(hday_count);
				hday_list[0] = x;
			}
			break;
		case GX_RANGE:
			n = (argv[3].val.range.r1 - argv[3].val.range.r0 + 1) *
				(argv[3].val.range.c1 - argv[3].val.range.c0 + 1);
			n = GX_MIN(n, _gx_cell_count(_gx_get_expr_si(),
										 GX_CONSTANT_LIST | GX_RECALC_LIST));
			_gx_init_range_scan(_gx_get_expr_si(), argv[3].val.range, &scan,
								GX_CONSTANT_LIST | GX_RECALC_LIST);
			hday_list = _gx_mknumarray(n);
			while ((cp = _gx_do_range_scan(&scan)) != NULL)
			{
				if (_gx_fn_get_value(cp->row, cp->col, &x))
				{
					hday_list[hday_count] = x;
					hday_count++;
				}
			}
		}
	}
	day1 = argv[1].val.number;
	day2 = argv[2].val.number;
	if (!GX_VALID_DT(day1))
		_gx_function_error(GX_FN_ERR_INVALID_DATE);
	if (!GX_VALID_DT(day2))
		_gx_function_error(GX_FN_ERR_INVALID_DATE);

	wkends = ((day2 - day1) / 7) * 2;
/*   if ((weekday(day1)==1) || (weekday(day1)==7))
		wkends++; */
	d = (day2 - day1) % 7;
	if (d != 0)
	{
		w = weekday(day1) + d;
		if (w == 7)
			wkends++;
		if (w >= 8)
			wkends += 2;
	}
	for (i = 0; i < hday_count; i++)
	{
		int a1,
			a2;
		a1 = (int) hday_list[i];
		a2 = weekday(a1);
		if ((a1 >= day1) || (a1 <= day2))
			if ((a2 != 1) && (a2 != 7))
				hdays++;
	}
	op.type = GX_NUMBER;
	op.val.number = day2 - day1 - hdays - wkends + 1;
	return op;
#else
	gxOperand op;
	op.type = GX_NUMBER;
	_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	return op;
#endif
}


static int is_holiday(gxNumber * gxlist, int count, int date)
{
	int found = 0,
		i;

	for (i = 0; i < count; i++)
		if (date == (int) gxlist[i])
			found = 1;
	return found;
}


gxOperand __cdecl _gx_fn_workday(gxOperand argv[])
{
#ifdef CELLRANGE

	gxOperand op;
	unsigned n;
	int hday_count = 0,
		incr = 1,
		day1,
		days,
		networkdays = 0;
	gxNumber x,
			*hday_list = 0;
	gxScanBuf scan;
	gxCell *cp;

	if (argv->val.count < 2)
		_gx_function_error(GX_FN_ERR_TOO_FEW_ARGS);
	if (argv->val.count > 3)
		_gx_function_error(GX_FN_ERR_TOO_MANY_ARGS);

	_gx_cvt2constant(argv + 1);
	_gx_cvt2constant(argv + 2);

	if ((argv[1].type != GX_NUMBER) || (argv[2].type != GX_NUMBER))
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);

	if (argv->val.count == 3)
	{
		if (!((argv[3].type == GX_RANGE) || (argv[3].type == GX_CELL)))
			_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
		switch (argv[3].type)
		{
		case GX_CELL:
			if (_gx_fn_get_value(argv[3].val.range.r0,
								 argv[3].val.range.c0, &x))
			{
				hday_count = 1;
				hday_list = _gx_mknumarray(hday_count);
				hday_list[0] = x;
			}
			break;
		case GX_RANGE:
			n = (argv[3].val.range.r1 - argv[3].val.range.r0 + 1) *
				(argv[3].val.range.c1 - argv[3].val.range.c0 + 1);
			n = GX_MIN(n, _gx_cell_count(_gx_get_expr_si(),
										 GX_CONSTANT_LIST | GX_RECALC_LIST));
			_gx_init_range_scan(_gx_get_expr_si(), argv[3].val.range, &scan,
								GX_CONSTANT_LIST | GX_RECALC_LIST);
			hday_list = _gx_mknumarray(n);
			while ((cp = _gx_do_range_scan(&scan)) != NULL)
			{
				if (_gx_fn_get_value(cp->row, cp->col, &x))
				{
					hday_list[hday_count] = x;
					hday_count++;
				}
			}
		}
	}
	day1 = argv[1].val.number;
	if (day1 < 0.0 || day1 >= 73051.0)
		_gx_function_error(GX_FN_ERR_INVALID_DATE);
	days = argv[2].val.number;
	if (days < 0)
		incr = -1;

	do
	{
		while ((weekday(day1) == 1) ||
			   (weekday(day1) == 7) ||
			   (is_holiday(hday_list, hday_count, day1)))
			day1 += incr;
		networkdays += incr;
		if (networkdays < abs(days))
			day1++;
		else
			break;
	} while (1);

	if (weekday(day1) == 1)
		day1++;
	if (weekday(day1) == 7)
		day1 += 2;
	op.type = GX_NUMBER;
	op.val.number = day1;
	return op;
#else
	gxOperand op;
	op.type = GX_NUMBER;
	_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	return op;
#endif
}

static void process_a_number(gxNumber x, int *sign, gxNumber * log_product)
{
	if (x < 0)
	{
		*sign *= -1;
		x *= -1;
	}
	*log_product += log(x);
}

gxOperand __cdecl _gx_fn_product(gxOperand argv[])
{
#ifdef CELLRANGE
	gxOperand op;
	gxNumber x = 0.0,
			 log_product = 0;
	int i,
		arg_count = argv->val.count,
		sign = 1;
	gxScanBuf scan;
	gxCell *cp;

	op.type = GX_NUMBER;
	op.val.number = 0.0;
	for (i = 0; i < arg_count; i++)
	{
		switch ((++argv)->type)
		{
		case GX_NUMBER:
			x = argv->val.number;
			if (x == 0.0)
				return op;
			process_a_number(x, &sign, &log_product);
			break;
		case GX_CELL:
			_gx_fn_get_value(argv->val.range.r0,
							 argv->val.range.c0, &x);
			if (x == 0.0)
				return op;
			process_a_number(x, &sign, &log_product);
			break;
		case GX_RANGE:
			_gx_init_range_scan(_gx_get_expr_si(), argv->val.range, &scan,
								GX_CONSTANT_LIST | GX_RECALC_LIST);
			while ((cp = _gx_do_range_scan(&scan)) != NULL)
				if (_gx_fn_get_value(cp->row, cp->col, &x))
				{
					if (x == 0.0)
						return op;
					process_a_number(x, &sign, &log_product);
				}
			if (x == 0.0)
				return op;
			break;
		case GX_OP_ERROR:
			_gx_propagate_error(argv);
		default:
			break;
		}
	}
	op.val.number = sign * exp(log_product);
	return op;
#else
	gxOperand op;
	op.type = GX_NUMBER;
	_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	return op;
#endif
}


static gxNumber interp2d(gxNumber * x_range, gxNumber * y_range, int count, gxNumber newx)
{

	int i,
		found = 0;
	gxNumber result;
	for (i = 0; i < count - 1; i++)
		if ((x_range[i] <= newx) && (newx <= x_range[i + 1]))
		{
			found++;
			break;
		}
	if (!found)
		_gx_function_error(GX_FN_ERR_NO_INTERP);
	result = y_range[i] + (y_range[i + 1] - y_range[i]) *
		(newx - x_range[i]) / (x_range[i + 1] - x_range[i]);
	return result;
}

gxOperand __cdecl _gx_fn_interp2d(gxOperand argv[])
{
#ifdef CELLRANGE
	gxOperand op;
	gxNumber *newx = 0,
			*x_range,
			*y_range,
			 v;
	gxMatrix newy;
	int col_vec = 0,
		v_type;
	unsigned i,
		j,
		count1 = 0,
		count2 = 0,
		n;

	if (argv->val.count != 3)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	GX_HANDLE_OP_ERROR(argv[1]);
	GX_HANDLE_OP_ERROR(argv[2]);
	if (argv[1].type != GX_RANGE || argv[2].type != GX_RANGE)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	v_type = _gx_analyze_ranges(&(argv[1].val.range), &(argv[2].val.range));
	if (v_type == 0)
		_gx_function_error(GX_FN_ERR_IMPROP_DIM);
	n = (argv[1].val.range.r1 - argv[1].val.range.r0 + 1) *
		(argv[1].val.range.c1 - argv[1].val.range.c0 + 1);
	n = GX_MIN(n, _gx_cell_count(_gx_get_expr_si(), GX_CONSTANT_LIST | GX_RECALC_LIST));
	x_range = _gx_mknumarray(n);
	y_range = _gx_mknumarray(n);
	for (i = argv[1].val.range.r0; i < argv[1].val.range.r1 + 1; i++)
		for (j = argv[1].val.range.c0; j < argv[1].val.range.c1 + 1; j++)
			if (_gx_fn_get_value(i, j, &v))
			{
				x_range[count1] = v;
				count1++;
			}
			else
				_gx_function_error(GX_FN_ERR_NON_NUM_IN_VEC);
	count1 = 0;
	for (i = argv[2].val.range.r0; i < argv[2].val.range.r1 + 1; i++)
		for (j = argv[2].val.range.c0; j < argv[2].val.range.c1 + 1; j++)
			if (_gx_fn_get_value(i, j, &v))
			{
				y_range[count1] = v;
				count1++;
			}
			else
				_gx_function_error(GX_FN_ERR_NON_NUM_IN_VEC);
	switch (argv[3].type)
	{
	case GX_CELL:
		_gx_cvt2constant(argv + 3);
	case GX_NUMBER:
		count2 = 1;
		newx = _gx_mknumarray(count2);
		newx[0] = argv[3].val.number;
		break;
	case GX_RANGE:
		{
			int rdim,
				cdim;
			rdim = argv[3].val.range.r1 - argv[3].val.range.r0 + 1;
			cdim = argv[3].val.range.c1 - argv[3].val.range.c0 + 1;
			if (!(rdim == 1 || cdim == 1))
				_gx_function_error(GX_FN_ERR_IMPROP_DIM);
			col_vec = (rdim > cdim ? 1 : 0);
			n = (argv[3].val.range.r1 - argv[3].val.range.r0 + 1) *
				(argv[3].val.range.c1 - argv[3].val.range.c0 + 1);
			n = GX_MIN(n, _gx_cell_count(_gx_get_expr_si(), GX_CONSTANT_LIST | GX_RECALC_LIST));
			newx = _gx_mknumarray(n);
			for (i = argv[3].val.range.r0; i < argv[3].val.range.r1 + 1; i++)
				for (j = argv[3].val.range.c0; j < argv[3].val.range.c1 + 1; j++)
					if (_gx_fn_get_value(i, j, &v))
					{
						newx[count2] = v;
						count2++;
					}
					else
						_gx_function_error(GX_FN_ERR_NON_NUM_IN_VEC);
			break;
		}
	default:
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	}
	newy.r_dim = count2;
	newy.c_dim = 1;
	_gx_mkwm(&newy);
	for (i = 0; i < count2; i++)
		newy.data[i] = interp2d(x_range, y_range, count1, newx[i]);
	if (col_vec)
		_gx_dump_matrix(newy);
	else
		_gx_dump_matrix(_gx_mtranspose(newy));
	op.type = GX_NUMBER;
	op.val.number = newy.data[0];
	_gx_cleanwm();
	return op;
#else
	gxOperand op;
	op.type = GX_NUMBER;
	_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	return op;
#endif
}


#ifdef CELLRANGE
static gxNumber interp3d(gxNumber * x, gxNumber * y, int count, gxNumber newx, gxNumber newy, int row, int col)
{

	int i,
		j,
		found = 0;
	gxNumber result,
			 z[2][2],
			 z1,
			 z2;

	for (i = 0; i < count - 1; i++)
		if ((x[i] <= newx) && (newx <= x[i + 1]))
		{
			found++;
			break;
		}
	if (found != 1)
		_gx_function_error(GX_FN_ERR_NO_INTERP);
	for (j = 0; j < count - 1; j++)
		if ((y[j] <= newy) && (newy <= y[j + 1]))
		{
			found++;
			break;
		}
	if (found != 2)
		_gx_function_error(GX_FN_ERR_NO_INTERP);
	if (!(_gx_fn_get_value(row + i, col + j, &z[0][0]) &&
		  _gx_fn_get_value(row + i, col + j + 1, &z[1][0]) &&
		  _gx_fn_get_value(row + i + 1, col + j, &z[0][1]) &&
		  _gx_fn_get_value(row + i + 1, col + j + 1, &z[1][1])))
	{
		_gx_function_error(GX_FN_ERR_INVALID_TBL);
	}
	z1 = z[0][0] + (z[0][1] - z[0][0]) * (newx - x[i]) / (x[i + 1] - x[i]);
	z2 = z[1][0] + (z[1][1] - z[1][0]) * (newx - x[i]) / (x[i + 1] - x[i]);
	result = z1 + (z2 - z1) * (newy - y[j]) / (y[j + 1] - y[j]);
	return result;
}
#endif

gxOperand __cdecl _gx_fn_interp3d(gxOperand argv[])
{
#ifdef CELLRANGE
	gxOperand op;
	gxNumber *x,
			*y,
			*newx = 0,
			*newy = 0,
			 v;
	gxMatrix newz;
	gxRange x_range,
			y_range;
	unsigned n,
		i,
		j;
	unsigned count1 = 0,
		count2 = 0,
		count3 = 0;
	int col_vec = 0;
	unsigned rdim,
		cdim;

	if (argv->val.count != 3)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	GX_HANDLE_OP_ERROR(argv[1]);
	GX_HANDLE_OP_ERROR(argv[2]);
	if (argv[1].type != GX_RANGE)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	if ((argv[1].val.range.r1 - argv[1].val.range.r0) !=
		(argv[1].val.range.c1 - argv[1].val.range.c0))
		_gx_function_error(GX_FN_ERR_IMPROP_DIM);
	n = (argv[1].val.range.r1 - argv[1].val.range.r0 + 1) *
		(argv[1].val.range.c1 - argv[1].val.range.c0 + 1);
	n = GX_MIN(n, _gx_cell_count(_gx_get_expr_si(), GX_CONSTANT_LIST | GX_RECALC_LIST));
	x = _gx_mknumarray((int) pow((gxNumber) n, 0.5) - 1);
	y = _gx_mknumarray((int) pow((gxNumber) n, 0.5) - 1);
	x_range.c0 = x_range.c1 = argv[1].val.range.c0;
	x_range.r0 = argv[1].val.range.r0 + 1;
	x_range.r1 = argv[1].val.range.r1;
	y_range.r0 = y_range.r1 = argv[1].val.range.r0;
	y_range.c0 = argv[1].val.range.c0 + 1;
	y_range.c1 = argv[1].val.range.c1;
	for (i = x_range.r0; i < x_range.r1 + 1; i++)
		for (j = x_range.c0; j < x_range.c1 + 1; j++)
			if (_gx_fn_get_value(i, j, &v))
			{
				x[count1] = v;
				count1++;
			}
			else
				_gx_function_error(GX_FN_ERR_INVALID_TBL);
	count1 = 0;
	for (i = y_range.r0; i < y_range.r1 + 1; i++)
	{
		for (j = y_range.c0; j < y_range.c1 + 1; j++)
		{
			if (_gx_fn_get_value(i, j, &v))
			{
				y[count1] = v;
				count1++;
			}
			else
				_gx_function_error(GX_FN_ERR_INVALID_TBL);
		}
	}
	switch (argv[2].type)
	{
	case GX_CELL:
		_gx_cvt2constant(argv + 2);
	case GX_NUMBER:
		count2 = 1;
		newx = _gx_mknumarray(count2);
		newx[0] = argv[2].val.number;
		break;
	case GX_RANGE:
		rdim = argv[2].val.range.r1 - argv[2].val.range.r0 + 1;
		cdim = argv[2].val.range.c1 - argv[2].val.range.c0 + 1;
		if (!(rdim == 1 || cdim == 1))
			_gx_function_error(GX_FN_ERR_IMPROP_DIM);
		col_vec = (rdim > cdim ? 1 : 0);
		n = rdim * cdim;
		n = GX_MIN(n, _gx_cell_count(_gx_get_expr_si(), GX_CONSTANT_LIST | GX_RECALC_LIST));
		newx = _gx_mknumarray(n);
		for (i = argv[2].val.range.r0; i < argv[2].val.range.r1 + 1; i++)
			for (j = argv[2].val.range.c0; j < argv[2].val.range.c1 + 1; j++)
				if (_gx_fn_get_value(i, j, &v))
				{
					newx[count2] = v;
					count2++;
				}
				else
					_gx_function_error(GX_FN_ERR_NON_NUM_IN_VEC);
		break;
	default:
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	}
	switch (argv[3].type)
	{
	case GX_CELL:
		_gx_cvt2constant(argv + 3);
	case GX_NUMBER:
		count3 = 1;
		newy = _gx_mknumarray(count3);
		newy[0] = argv[3].val.number;
		break;
	case GX_RANGE:
		rdim = argv[3].val.range.r1 - argv[3].val.range.r0 + 1;
		cdim = argv[3].val.range.c1 - argv[3].val.range.c0 + 1;
		if (!(rdim == 1 || cdim == 1))
			_gx_function_error(GX_FN_ERR_IMPROP_DIM);
		if (col_vec != (rdim > cdim ? 1 : 0))
			_gx_function_error(GX_FN_ERR_IMPROP_DIM);
		n = rdim * cdim;
		n = GX_MIN(n, _gx_cell_count(_gx_get_expr_si(), GX_CONSTANT_LIST | GX_RECALC_LIST));
		newy = _gx_mknumarray(n);
		for (i = argv[3].val.range.r0; i < argv[3].val.range.r1 + 1; i++)
			for (j = argv[3].val.range.c0; j < argv[3].val.range.c1 + 1; j++)
				if (_gx_fn_get_value(i, j, &v))
				{
					newy[count3] = v;
					count3++;
				}
				else
					_gx_function_error(GX_FN_ERR_NON_NUM_IN_VEC);
		if (count2 != count3)
			_gx_function_error(GX_FN_ERR_IMPROP_DIM);
		break;
	default:
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	}
	newz.r_dim = count2;
	newz.c_dim = 1;
	_gx_mkwm(&newz);
	for (i = 0; i < count2; i++)
		newz.data[i] = interp3d(x, y, count1, newx[i], newy[i],
						argv[1].val.range.r0 + 1, argv[1].val.range.c0 + 1);

	if (count2 > 1)
	{
		if (col_vec)
			_gx_dump_matrix(newz);
		else
			_gx_dump_matrix(_gx_mtranspose(newz));
	}
	op.type = GX_NUMBER;
	op.val.number = newz.data[0];
	_gx_cleanwm();
	return op;
#else
	gxOperand op;
	op.type = GX_NUMBER;
	_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	return op;
#endif
}
