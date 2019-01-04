///////////////////////////////////////////////////////////////////////////////
// fnstat2.cpp: Statistical worksheet functions
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

#define  CELLRANGE

extern gxMatrix __cdecl _gx_lincoef(gxOperand argv[], int v_type);

#ifdef CELLRANGE
extern	int __cdecl _gx_analyze_ranges(gxRange * rp1, gxRange * rp2);
#endif

extern gxNumber __cdecl _gx_phi(gxNumber x);
void __cdecl _gx_dump_matrix(gxMatrix m);

static int __cdecl compare_ascd(const void *vp1, const void *vp2)
{
	const double *np1 = (const double *) vp1;
	const double *np2 = (const double *) vp2;

	if (*np1 < *np2)
		return -1;
	else if (*np1 == *np2)
		return 0;
	else
		return 1;
}

static int __cdecl compare_dscd(const void *vp1, const void *vp2)
{
	const double *np1 = (const double *) vp1;
	const double *np2 = (const double *) vp2;

	if (*np1 > *np2)
		return -1;
	else if (*np1 == *np2)
		return 0;
	else
		return 1;
}


gxOperand __cdecl _gx_fn_erf(gxOperand argv[])
{
	gxOperand op;
	gxNumber llimit,
			 ulimit,
			 erf1 = 0,
			 erf2 = 0;
	int i,
		llmit_only = 1;

	if (argv->val.count != 1 && argv->val.count != 2)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	for (i = 1; i < argv->val.count + 1; i++)
	{
		_gx_cvt2constant(argv + i);
		if (argv[i].type != GX_NUMBER)
			_gx_function_error(GX_FN_ERR_ARG_NUMERIC);
	}
	if (argv[1].val.number < 0)
		_gx_function_error(GX_FN_ERR_ERF_LLIMIT);
	llimit = sqrt(2.0) * argv[1].val.number;
	erf1 = 2 * _gx_phi(llimit) - 1;
	if (argv->val.count == 2)
	{
		if (argv[2].val.number < 0)
			_gx_function_error(GX_FN_ERR_ERF_ULIMIT);
		llmit_only = 0;
		ulimit = sqrt(2.0) * argv[2].val.number;
		erf2 = 2 * _gx_phi(ulimit) - 1;
	}
	if (llmit_only)
		op.val.number = erf1;
	else
		op.val.number = erf2 - erf1;
	op.type = GX_NUMBER;
	return op;
}

gxOperand  __cdecl _gx_fn_erfc(gxOperand argv[])
{
	gxOperand op;
	gxNumber x,
			 erf;

	if (argv->val.count != 1)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	if (argv[1].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_ARG_NUMERIC);
	_gx_cvt2constant(argv + 1);
	if (argv[1].val.number < 0)
		_gx_function_error(GX_FN_ERR_ERF_LLIMIT);
	x = sqrt(2.0) * argv[1].val.number;
	erf = 2 * _gx_phi(x) - 1;
	op.val.number = 1 - erf;
	op.type = GX_NUMBER;
	return op;
}

gxOperand  __cdecl _gx_fn_frequency(gxOperand argv[])
{
	gxOperand op;
	gxMatrix result;
	gxNumber *bins,
			 x;
	unsigned bin_count = 0,
		n,
		i,
		rdim,
		cdim,
		col_vec;
	int empty_bin = 0;
	gxCell *cp;
	gxScanBuf scan;

	if (argv->val.count != 2)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	GX_HANDLE_OP_ERROR(argv[1]);
	GX_HANDLE_OP_ERROR(argv[2]);
	if (!(argv[1].type == GX_RANGE && argv[2].type == GX_RANGE))
		_gx_function_error(GX_FN_ERR_CF_RANGE);
#ifdef CELLRANGE
	rdim = argv[2].val.range.r1 - argv[2].val.range.r0 + 1;
	cdim = argv[2].val.range.c1 - argv[2].val.range.c0 + 1;
	col_vec = (rdim > cdim ? 1 : 0);
	n = rdim * cdim;
	n = GX_MIN(n, _gx_cell_count(_gx_get_expr_si(), GX_CONSTANT_LIST | GX_RECALC_LIST));
	bins = _gx_mknumarray(n);

	_gx_init_range_scan(_gx_get_expr_si(), argv[2].val.range, &scan,
						GX_CONSTANT_LIST | GX_RECALC_LIST);

	while ((cp = _gx_do_range_scan(&scan)) != NULL)
	{
		if (_gx_fn_get_value(cp->row, cp->col, &x))
		{
			bins[bin_count] = x;
			bin_count++;
		}
	}
	result.r_dim = bin_count + 1;
	result.c_dim = 1;
	_gx_mkwm(&result);
	for (i = 0; i < bin_count + 1; i++)
		result.data[i] = 0;
	if (bin_count == 0)
		empty_bin = 1;
	_gx_init_range_scan(_gx_get_expr_si(), argv[1].val.range, &scan,
						GX_CONSTANT_LIST | GX_RECALC_LIST);
	while ((cp = _gx_do_range_scan(&scan)) != NULL)
		if (_gx_fn_get_value(cp->row, cp->col, &x))
		{
			if (!empty_bin)
			{
				if (x < bins[0])
					result.data[0]++;
				else if (bins[bin_count - 1] <= x)
					result.data[bin_count]++;
				else
					for (i = 0; i < bin_count - 1; i++)
						if (bins[i] <= x && x < bins[i + 1])
						{
							result.data[i + 1]++;
							break;
						}
			}
		}
	if (col_vec)
		_gx_dump_matrix(result);
	else
		_gx_dump_matrix(_gx_mtranspose(result));
	op.val.number = result.data[0];
#endif
	op.type = GX_NUMBER;
	_gx_cleanwm();
	return op;
}



gxOperand __cdecl _gx_fn_large(gxOperand argv[])
{
	gxOperand op;

	unsigned n,
		count = 0;
	gxNumber key,
			 x,
			*gxlist;
	gxScanBuf scan;
	gxCell *cp;

	if (argv->val.count != 2)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 2);
	GX_HANDLE_OP_ERROR(argv[1]);
	if ((argv[1].type != GX_RANGE) || (argv[2].type != GX_NUMBER))
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
#ifdef CELLRANGE
	key = argv[2].val.number;
	n = (argv[1].val.range.r1 - argv[1].val.range.r0 + 1) *
		(argv[1].val.range.c1 - argv[1].val.range.c0 + 1);
	n = GX_MIN(n, _gx_cell_count(_gx_get_expr_si(), GX_CONSTANT_LIST | GX_RECALC_LIST));
	if (key <= 0 || key > n)
		_gx_function_error(GX_FN_ERR_ARG_OUT_OF_RNG);
	gxlist = _gx_mknumarray(n);
	_gx_init_range_scan(_gx_get_expr_si(), argv[1].val.range, &scan,
						GX_CONSTANT_LIST | GX_RECALC_LIST);
	while ((cp = _gx_do_range_scan(&scan)) != NULL)
		if (_gx_fn_get_value(cp->row, cp->col, &x))
		{
			gxlist[count] = x;
			count++;
		}
	qsort(gxlist, count, sizeof(double), compare_dscd);
	op.val.number = gxlist[(int) key - 1];
#endif
	op.type = GX_NUMBER;
	_gx_cleanwm();
	return op;
}


gxOperand __cdecl _gx_fn_small(gxOperand argv[])
{
	gxOperand op;

	unsigned n,
		count = 0;
	gxNumber key,
			 x,
			*gxlist;
	gxScanBuf scan;
	gxCell *cp;

	if (argv->val.count != 2)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 2);
	GX_HANDLE_OP_ERROR(argv[1]);
#ifdef CELLRANGE
	if ((argv[1].type != GX_RANGE) || (argv[2].type != GX_NUMBER))
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	key = argv[2].val.number;
	n = (argv[1].val.range.r1 - argv[1].val.range.r0 + 1) *
		(argv[1].val.range.c1 - argv[1].val.range.c0 + 1);
	n = GX_MIN(n, _gx_cell_count(_gx_get_expr_si(), GX_CONSTANT_LIST | GX_RECALC_LIST));
	if (key <= 0 || key > n)
		_gx_function_error(GX_FN_ERR_ARG_OUT_OF_RNG);
	gxlist = _gx_mknumarray(n);

	_gx_init_range_scan(_gx_get_expr_si(), argv[1].val.range, &scan,
						GX_CONSTANT_LIST | GX_RECALC_LIST);
	while ((cp = _gx_do_range_scan(&scan)) != NULL)
		if (_gx_fn_get_value(cp->row, cp->col, &x))
		{
			gxlist[count] = x;
			count++;
		}
	qsort(gxlist, count, sizeof(double), compare_ascd);
	op.val.number = gxlist[(int) key - 1];
#endif
	op.type = GX_NUMBER;
	_gx_cleanwm();
	return op;
}


static gxNumber percentile(gxNumber * gxlist, int count, gxNumber perct)
{
	int pos1,
		pos2;
	gxNumber p,
			 val1,
			 val2;

	if (count == 0)
		return 0.0;
	p = (count - 1) * perct;
	pos1 = (int) floor(p);
	pos2 = (int) ceil(p);
	qsort(gxlist, count, sizeof(double), compare_ascd);
	val1 = gxlist[pos1];
	val2 = gxlist[pos2];
	_gx_cleanwm();
	return val1 + (val2 - val1) * (p - pos1);
}


gxOperand __cdecl _gx_fn_percentile(gxOperand argv[])
{
	gxOperand op;
	gxNumber *gxlist,
			 x;
	unsigned count = 0,
		n;
	gxScanBuf scan;
	gxCell *cp;

	if (argv->val.count != 2)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	if (argv[2].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	_gx_cvt2constant(argv + 2);
	if ((argv[2].val.number < 0) || (argv[2].val.number > 1))
		_gx_function_error(GX_FN_ERR_ARG_OUT_OF_RNG);

	switch (argv[1].type)
	{
	case GX_NUMBER:
		_gx_cvt2constant(argv + 1);
		op.val.number = argv[1].val.number;
		break;
#ifdef CELLRANGE
	case GX_CELL:
		_gx_cvt2constant(argv + 1);
		op.val.number = argv[1].val.number;
		break;
	case GX_RANGE:
		GX_HANDLE_OP_ERROR(argv[1]);
		n = (argv[1].val.range.r1 - argv[1].val.range.r0 + 1) *
			(argv[1].val.range.c1 - argv[1].val.range.c0 + 1);
		n = GX_MIN(n, _gx_cell_count(_gx_get_expr_si(), GX_CONSTANT_LIST | GX_RECALC_LIST));
		gxlist = _gx_mknumarray(n);
		_gx_init_range_scan(_gx_get_expr_si(), argv[1].val.range, &scan,
							GX_CONSTANT_LIST | GX_RECALC_LIST);
		while ((cp = _gx_do_range_scan(&scan)) != NULL)
			if (_gx_fn_get_value(cp->row, cp->col, &x))
			{
				gxlist[count] = x;
				count++;
			}
		op.val.number = percentile(gxlist, count, argv[2].val.number);
		break;
#endif
	default:
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	}
	op.type = GX_NUMBER;
	return op;
}


gxOperand __cdecl _gx_fn_quartile(gxOperand argv[])
{
	gxOperand op;
	gxNumber *gxlist,
			 x;
	unsigned count = 0,
		n;
	gxScanBuf scan;
	gxCell *cp;

	if (argv->val.count != 2)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);

	if (argv[2].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	_gx_cvt2constant(argv + 2);
	if ((argv[2].val.number < 0) || (argv[2].val.number > 4))
		_gx_function_error(GX_FN_ERR_ARG_OUT_OF_RNG);

	switch (argv[1].type)
	{
	case GX_NUMBER:
		_gx_cvt2constant(argv + 2);
		op.val.number = argv[1].val.number;
		break;
#ifdef CELLRANGE
	case GX_CELL:
		_gx_cvt2constant(argv + 2);
		op.val.number = argv[1].val.number;
		break;
	case GX_RANGE:
		GX_HANDLE_OP_ERROR(argv[1]);
		n = (argv[1].val.range.r1 - argv[1].val.range.r0 + 1) *
			(argv[1].val.range.c1 - argv[1].val.range.c0 + 1);
		n = GX_MIN(n, _gx_cell_count(_gx_get_expr_si(), GX_CONSTANT_LIST | GX_RECALC_LIST));
		gxlist = _gx_mknumarray(n);
		_gx_init_range_scan(_gx_get_expr_si(), argv[1].val.range, &scan,
							GX_CONSTANT_LIST | GX_RECALC_LIST);
		while ((cp = _gx_do_range_scan(&scan)) != NULL)
			if (_gx_fn_get_value(cp->row, cp->col, &x))
			{
				gxlist[count] = x;
				count++;
			}
		op.val.number = percentile(gxlist, count, (int) argv[2].val.number / 4.0);
		break;
#endif
	default:
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	}

	op.type = GX_NUMBER;
	return op;
}

gxOperand __cdecl _gx_fn_median(gxOperand argv[])
{
	gxOperand op;
	gxNumber *gxlist,
			 x;
	unsigned n,
		count = 0;
	int i;
	gxScanBuf scan;
	gxCell *cp;

	for (i = 0; i < argv->val.count; i++)
		switch (argv[i + 1].type)
		{
		case GX_NUMBER:
			count++;
			break;
#ifdef CELLRANGE
		case GX_CELL:
			count++;
			break;
		case GX_RANGE:
			n = (argv[i + 1].val.range.r1 - argv[i + 1].val.range.r0 + 1) *
				(argv[i + 1].val.range.c1 - argv[i + 1].val.range.c0 + 1);
			count += n;
			break;
#endif
		case GX_OP_ERROR:
			_gx_propagate_error(argv);
		default:
			break;
		}
#ifdef CELLRANGE
	n = GX_MIN(count, _gx_cell_count(_gx_get_expr_si(), GX_CONSTANT_LIST | GX_RECALC_LIST));
#endif
	gxlist = _gx_mknumarray(count);
	count = 0;
	for (i = 0; i < argv->val.count; i++)
	{
		switch (argv[i + 1].type)
		{
		case GX_NUMBER:
			gxlist[count] = argv[i + 1].val.number;
			count++;
			break;
#ifdef CELLRANGE
		case GX_CELL:
			if (_gx_fn_get_value(argv[i + 1].val.range.r0,
								 argv[i + 1].val.range.c0, &x))
			{
				gxlist[count] = x;
				count++;
			}
			break;
		case GX_RANGE:
			_gx_init_range_scan(_gx_get_expr_si(), argv[i + 1].val.range, &scan,
								GX_CONSTANT_LIST | GX_RECALC_LIST);
			while ((cp = _gx_do_range_scan(&scan)) != NULL)
				if (_gx_fn_get_value(cp->row, cp->col, &x))
				{
					gxlist[count] = x;
					count++;
				}
			break;
#endif
		case GX_OP_ERROR:
			_gx_propagate_error(argv);
		default:
			break;
		}
	}
	op.val.number = percentile(gxlist, count, 0.5);
	op.type = GX_NUMBER;
	return op;
}


gxOperand __cdecl _gx_fn_percentrank(gxOperand argv[])
{
#ifdef CELLRANGE
	gxOperand op;
	gxNumber *gxlist,
			 key,
			 x,
			 offset;
	unsigned n,
		pos,
		count = 0;
	gxScanBuf scan;
	gxCell *cp;

	if (argv->val.count != 2)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	if (argv[2].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	_gx_cvt2constant(argv + 2);
	key = argv[2].val.number;

	op.type = GX_NUMBER;
	switch (argv[1].type)
	{
	case GX_NUMBER:
		_gx_cvt2constant(argv + 1);
		if (argv[1].val.number != key)
			_gx_function_error(GX_FN_ERR_ARG_OUT_OF_RNG);
		op.val.number = argv[1].val.number;
		return op;
	case GX_CELL:
		_gx_cvt2constant(argv + 1);
		if (argv[1].val.number != key)
			_gx_function_error(GX_FN_ERR_ARG_OUT_OF_RNG);
		op.val.number = argv[1].val.number;
		return op;
	case GX_RANGE:
		GX_HANDLE_OP_ERROR(argv[1]);
		break;
	default:
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	}
	n = (argv[1].val.range.r1 - argv[1].val.range.r0 + 1) *
		(argv[1].val.range.c1 - argv[1].val.range.c0 + 1);
	n = GX_MIN(n, _gx_cell_count(_gx_get_expr_si(), GX_CONSTANT_LIST | GX_RECALC_LIST));
	gxlist = _gx_mknumarray(n);

	_gx_init_range_scan(_gx_get_expr_si(), argv[1].val.range, &scan,
						GX_CONSTANT_LIST | GX_RECALC_LIST);
	while ((cp = _gx_do_range_scan(&scan)) != NULL)
		if (_gx_fn_get_value(cp->row, cp->col, &x))
		{
			gxlist[count] = x;
			count++;
		}
	qsort(gxlist, count, sizeof(double), compare_ascd);
	if (key < gxlist[0] || key > gxlist[count - 1])
		_gx_function_error(GX_FN_ERR_ARG_OUT_OF_RNG);
	for (pos = 0; pos < n; pos++)
	{
		if (gxlist[pos] == key)
			break;
		if (gxlist[pos] > key)
		{
			pos--;
			break;
		}
	}
	offset = (key - gxlist[pos]) / (gxlist[pos + 1] - gxlist[pos]);
	op.val.number = ((double) pos + offset) / (double) (count - 1);
	op.type = GX_NUMBER;
	return op;
#else
	gxOperand op;
	op.type = GX_NUMBER;
	_gx_function_error(GX_BAD_RANGE);
	return op;
#endif
}

#pragma warning (push)
#pragma warning (disable: 4701)

gxOperand __cdecl _gx_fn_mode(gxOperand argv[])
{
	gxOperand op;
	gxNumber *gxlist,
			*list_copy,
			 x,
			 cur_num,
			 mode = 0;
	unsigned i,
		j,
		n = 0,
		count = 0,
		max_count = 0,
		cur_count = 1;
	gxScanBuf scan;
	gxCell *cp;

	for (i = 0; i < (unsigned) argv->val.count; i++)
		switch (argv[i + 1].type)
		{
		case GX_NUMBER:
			count++;
			break;
#ifdef CELLRANGE
		case GX_CELL:
			count++;
			break;
		case GX_RANGE:
			n = (argv[i + 1].val.range.r1 - argv[i + 1].val.range.r0 + 1) *
				(argv[i + 1].val.range.c1 - argv[i + 1].val.range.c0 + 1);
			count += n;
			break;
#endif
		case GX_OP_ERROR:
			_gx_propagate_error(argv);
		default:
			break;
		}
#ifdef CELLRANGE
	n = GX_MIN(count, _gx_cell_count(_gx_get_expr_si(), GX_CONSTANT_LIST | GX_RECALC_LIST));
#endif
	gxlist = _gx_mknumarray(count);
	list_copy = _gx_mknumarray(count);

	count = 0;
	for (i = 0; i < (unsigned) argv->val.count; i++)
	{
		switch (argv[i + 1].type)
		{
		case GX_NUMBER:
			gxlist[count] = list_copy[count] = argv[i + 1].val.number;
			count++;
			break;
#ifdef CELLRANGE
		case GX_CELL:
			if (_gx_fn_get_value(argv[i + 1].val.range.r0,
								 argv[i + 1].val.range.c0, &x))
			{
				gxlist[count] = list_copy[count] = x;
				count++;
			}
			break;
		case GX_RANGE:
			_gx_init_range_scan(_gx_get_expr_si(), argv[i + 1].val.range, &scan,
								GX_CONSTANT_LIST | GX_RECALC_LIST);
			while ((cp = _gx_do_range_scan(&scan)) != NULL)
				if (_gx_fn_get_value(cp->row, cp->col, &x))
				{
					gxlist[count] = list_copy[count] = x;
					count++;
				}
			break;
#endif
		case GX_OP_ERROR:
			_gx_propagate_error(argv);
		default:
			break;
		}
	}
	qsort(gxlist, count, sizeof(double), compare_ascd);
	cur_num = gxlist[0];
	for (i = 1; i < count; i++)
	{
		if (cur_num == gxlist[i])
			cur_count++;
		else
		{
			if (cur_count > max_count)
			{
				max_count = cur_count;
				mode = cur_num;
			}
			else if (cur_count == max_count)
			{
				/* if ther is a tie, take the one first */
				/* appeared in the original list.       */
				for (j = 0; j < count; j++)
				{
					if (list_copy[j] == cur_num)
					{
						mode = cur_num;
						break;
					}
					else if (list_copy[j] == mode)
						break;
				}
			}
			cur_count = 1;
			cur_num = gxlist[i];
		}
	}
	_gx_cleanwm();
	if (cur_count > max_count)
	{
		max_count = cur_count;
		mode = cur_num;
	}
	if (max_count == 1)
	{
		_gx_function_error(GX_FN_ERR_NO_MODE);
	}
	else
	{
		op.type = GX_NUMBER;
		op.val.number = mode;
	}
	return op;
}

#pragma warning (pop) //4701


gxOperand __cdecl _gx_fn_rank(gxOperand argv[])
{
	gxOperand op;
	int ascending = 0,
		found = 0,
		less = 0,
		greater = 0;
	gxNumber x,
			 key;
	gxScanBuf scan;
	gxCell *cp;

	if (argv->val.count < 2 || argv->val.count > 3)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);

	_gx_cvt2constant(argv + 1);
	if ((argv[1].type != GX_NUMBER) || (argv[2].type != GX_RANGE))
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	GX_HANDLE_OP_ERROR(argv[2]);
	if (argv->val.count == 3)
	{
		if (argv[3].type != GX_NUMBER)
			_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
		else
		{
			_gx_cvt2constant(argv + 3);
			if (argv[3].val.number != 0)
				ascending = 1;
		}
	}
	key = argv[1].val.number;
#ifdef CELLRANGE
	_gx_init_range_scan(_gx_get_expr_si(), argv[2].val.range, &scan,
						GX_CONSTANT_LIST | GX_RECALC_LIST);
	while ((cp = _gx_do_range_scan(&scan)) != NULL)
		if (_gx_fn_get_value(cp->row, cp->col, &x))
		{
			if (x == key && !found)
				found++;
			if (x < key)
				less++;
			else if (x > key)
				greater++;
		}
	if (!found)
#endif
		_gx_function_error(GX_FN_ERR_NUM_NOT_IN_LIST);
	op.type = GX_NUMBER;
	if (ascending)
		op.val.number = less + 1;
	else
		op.val.number = greater + 1;
	return op;
}


gxOperand __cdecl _gx_fn_permut(gxOperand argv[])
{

	gxOperand op;
	gxNumber permut = 1;
	int low,
		high,
		i;

	if (argv->val.count != 2)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);

	_gx_cvt2constant(argv + 1);
	_gx_cvt2constant(argv + 2);
	if ((argv[1].type != GX_NUMBER) || (argv[2].type != GX_NUMBER))
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	if ((argv[1].val.number <= 0) || (argv[2].val.number < 0) ||
		(argv[1].val.number < argv[2].val.number))
		_gx_function_error(GX_FN_ERR_PERMUT);

	high = (int) argv[1].val.number;
	low = (int) argv[2].val.number;

	for (i = high; i > high - low; i--)
		permut = permut * i;
	op.type = GX_NUMBER;
	op.val.number = (gxNumber) permut;
	return op;
}


gxOperand __cdecl _gx_fn_trend(gxOperand argv[])
{
#ifdef CELLRANGE
	gxMatrix coefs,
			 result;
	unsigned v_type,
		r,
		c,
		i,
		count = 0;
	gxNumber x,
			 new_xs[10];
	gxOperand op,
			  op1[3];

	if (argv->val.count != 3)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	GX_HANDLE_OP_ERROR(argv[1]);
	GX_HANDLE_OP_ERROR(argv[2]);
	GX_HANDLE_OP_ERROR(argv[3]);
	if (argv[2].type != GX_RANGE || argv[3].type != GX_RANGE)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	/* new_xs.r_dim = argv[1].val.range.r1 - argv[1].val.range.r0 + 1;
	 * new_xs.c_dim = argv[1].val.range.c1 - argv[1].val.range.c0 + 1; */

	switch (argv[1].type)
	{
	case GX_NUMBER:
		new_xs[count] = argv[1].val.number;
		count++;
		break;
	case GX_CELL:
		if (_gx_fn_get_value(argv[1].val.range.r0, argv[1].val.range.c0, &x))
		{
			new_xs[count] = x;
			count++;
		}
		break;
	case GX_RANGE:
		for (r = argv[1].val.range.r0; r <= argv[1].val.range.r1; r++)
			for (c = argv[1].val.range.c0; c <= argv[1].val.range.c1; c++)
				if (_gx_fn_get_value(r, c, &x))
				{
					new_xs[count] = x;
					count++;
				}
		break;
	}
	v_type = _gx_analyze_ranges(&(argv[2].val.range), &(argv[3].val.range));
	if (v_type == 0)
		_gx_function_error(GX_FN_ERR_IMPROP_DIM);
	op1[1] = argv[2];
	op1[2] = argv[3];
	coefs = _gx_lincoef(op1, v_type);

	result.r_dim = count;
	result.c_dim = 1;
	_gx_mkwm(&result);
	for (i = 0; i < count; i++)
	{
		result.data[i] = coefs.data[0] * new_xs[i] + coefs.data[1];
	}
	_gx_dump_matrix(result);
	op.val.number = result.data[0];
	op.type = GX_NUMBER;
	_gx_cleanwm();
	return op;
#else
	gxOperand op;
	op.type = GX_NUMBER;
	_gx_function_error(GX_BAD_RANGE);
	return op;
#endif
}


gxOperand __cdecl _gx_fn_forecast(gxOperand argv[])
{
#ifdef CELLRANGE
	gxMatrix x;
	int v_type;
	gxOperand op,
			  op1[3];

	if (argv->val.count != 3)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 1);
	GX_HANDLE_OP_ERROR(argv[2]);
	GX_HANDLE_OP_ERROR(argv[3]);
	if (argv[1].type != GX_NUMBER || argv[2].type != GX_RANGE ||
		argv[3].type != GX_RANGE)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	v_type = _gx_analyze_ranges(&(argv[2].val.range), &(argv[3].val.range));
	if (v_type == 0)
		_gx_function_error(GX_FN_ERR_IMPROP_DIM);
	op1[1] = argv[2];
	op1[2] = argv[3];
	x = _gx_lincoef(op1, v_type);
	op.type = GX_NUMBER;
	op.val.number = x.data[0] * argv[1].val.number + x.data[1];
	_gx_cleanwm();
	return op;
#else
	gxOperand op;
	op.type = GX_NUMBER;
	_gx_function_error(GX_BAD_RANGE);
	return op;
#endif
}
