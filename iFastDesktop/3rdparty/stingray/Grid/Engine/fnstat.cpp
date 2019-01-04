///////////////////////////////////////////////////////////////////////////////
// fnstat.cpp: Statistical worksheet functions
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

double _gx_alphaT(), _gx_alphaF();

#define CELLRANGE

static int get_fvalue(int r, int c, gxNumber * value)
{
#ifdef CELLRANGE
	gxCell *cp;
	int si = _gx_get_expr_si();

	cp = _gx_find_cell(si, r, c);
	if (!GX_CELL_IS_EMPTY(cp))
	{
		if (GX_CELL_CONTAINS_ERROR(cp))
			_gx_function_error(GX_FN_ERR_CELL_ERROR);
		*value = _gxttof(_gx_get_formatted_text(si, cp, NULL));
		return 1;
	}
#endif
	return 0;
}

static void range_stats(gxRange * rp, gxNumber * sum, gxNumber * sum2, int *count)
{
	gxNumber x,
			 s = *sum,
			 s2 = *sum2;
	int cnt = *count;
	gxScanBuf scan;
	gxCell *cp;

	_gx_init_range_scan(_gx_get_expr_si(), *rp, &scan, GX_CONSTANT_LIST | GX_RECALC_LIST);
	while ((cp = _gx_do_range_scan(&scan)) != NULL)
	{
		if (_gx_fn_get_value(cp->row, cp->col, &x))
		{
			s += x;
			s2 += x * x;
			cnt++;
		}
	}
	*sum = s;
	*sum2 = s2;
	*count = cnt;
}

gxOperand __cdecl _gx_fn_vsum(gxOperand argv[])
{
	gxNumber sum,
			 x;
	gxOperand op;
	int i,
		n = argv->val.count;
	gxScanBuf scan;
	gxCell *cp;

	sum = 0.;
	for (i = 0; i < n; i++)
		switch ((++argv)->type)
		{
		case GX_NUMBER:
			sum += argv->val.number;
			break;
#ifdef CELLRANGE
		case GX_CELL:
			if (get_fvalue(argv->val.range.r0, argv->val.range.c0, &x))
				sum += x;
			break;
		case GX_RANGE:
			_gx_init_range_scan(_gx_get_expr_si(), argv->val.range, &scan,
								GX_CONSTANT_LIST | GX_RECALC_LIST);
			while ((cp = _gx_do_range_scan(&scan)) != NULL)
				if (get_fvalue(cp->row, cp->col, &x))
					sum += x;
			break;
#endif
		case GX_OP_ERROR:
			_gx_propagate_error(argv);
		default:
			break;  /* ignore it */
		}
	op.type = GX_NUMBER;
	op.val.number = sum;
	return op;
}

gxOperand __cdecl _gx_fn_sum(gxOperand argv[])
{
	gxNumber sum,
			 x;
	gxOperand op;
	int i,
		n = argv->val.count;
	gxScanBuf scan;
	gxCell *cp;

	sum = 0.;
	for (i = 0; i < n; i++)
		switch ((++argv)->type)
		{
		case GX_NUMBER:
			sum += argv->val.number;
			break;
		case GX_CELL:
			if (_gx_fn_get_value(argv->val.range.r0, argv->val.range.c0, &x))
				sum += x;
			break;
		case GX_RANGE:
			_gx_init_range_scan(_gx_get_expr_si(), argv->val.range, &scan,
								GX_CONSTANT_LIST | GX_RECALC_LIST);
			while ((cp = _gx_do_range_scan(&scan)) != NULL)
				if (_gx_fn_get_value(cp->row, cp->col, &x))
					sum += x;
			break;
		case GX_OP_ERROR:
			_gx_propagate_error(argv);
		default:
			break;  /* ignore it */
		}
	op.type = GX_NUMBER;
	op.val.number = sum;
	return op;
}

gxOperand __cdecl _gx_fn_sse(gxOperand argv[])
{
	gxNumber sum,
			 sum2,
			 x;
	gxOperand op;
	int i,
		n = argv->val.count;
	int count;

	sum = sum2 = 0.;
	count = 0;
	for (i = 0; i < n; i++)
		switch ((++argv)->type)
		{
		case GX_NUMBER:
			x = argv->val.number;
			sum += x;
			sum2 += x * x;
			count++;
			break;
		case GX_CELL:
			if (_gx_fn_get_value(argv->val.range.r0, argv->val.range.c0, &x))
			{
				sum += x;
				sum2 += x * x;
				count++;
			}
			break;
		case GX_RANGE:
			range_stats(&(argv->val.range), &sum, &sum2, &count);
			break;
		case GX_OP_ERROR:
			_gx_propagate_error(argv);
		default:
			break;  /* ignore it */
		}
	if (count < 1)
		_gx_function_error(GX_FN_ERR_POP_LT_1);
	op.type = GX_NUMBER;
	op.val.number = (sum2 - (sum * sum) / count);
	return op;
}

gxOperand __cdecl _gx_fn_ssq(gxOperand argv[])
{
	gxNumber sum2,
			 x;
	gxOperand op;
	int i,
		n = argv->val.count;
	gxScanBuf scan;
	gxCell *cp;

	sum2 = 0.;
	for (i = 0; i < n; i++)
		switch ((++argv)->type)
		{
		case GX_NUMBER:
			sum2 += argv->val.number * argv->val.number;
			break;
		case GX_CELL:
			if (_gx_fn_get_value(argv->val.range.r0, argv->val.range.c0, &x))
				sum2 += x * x;
			break;
		case GX_RANGE:
			_gx_init_range_scan(_gx_get_expr_si(), argv->val.range, &scan,
								GX_CONSTANT_LIST | GX_RECALC_LIST);
			while ((cp = _gx_do_range_scan(&scan)) != NULL)
				if (_gx_fn_get_value(cp->row, cp->col, &x))
					sum2 += x * x;
			break;
		case GX_OP_ERROR:
			_gx_propagate_error(argv);
		default:
			break;  /* ignore it */
		}
	op.type = GX_NUMBER;
	op.val.number = sum2;
	return op;
}

gxOperand __cdecl _gx_fn_avg(gxOperand argv[])
{
	gxNumber sum = 0.,
			 x;
	gxOperand op;
	int i,
		n = argv->val.count;
	int count = 0;
	gxScanBuf scan;
	gxCell *cp;

	for (i = 0; i < n; i++)
		switch ((++argv)->type)
		{
		case GX_NUMBER:
			sum += argv->val.number;
			count++;
			break;
		case GX_CELL:
			if (_gx_fn_get_value(argv->val.range.r0, argv->val.range.c0, &x))
			{
				sum += x;
				count++;
			}
			break;
		case GX_RANGE:
			_gx_init_range_scan(_gx_get_expr_si(), argv->val.range, &scan,
								GX_CONSTANT_LIST | GX_RECALC_LIST);
			while ((cp = _gx_do_range_scan(&scan)) != NULL)
				if (_gx_fn_get_value(cp->row, cp->col, &x))
				{
					sum += x;
					count++;
				}
			break;
		case GX_OP_ERROR:
			_gx_propagate_error(argv);
		default:
			break;  /* ignore it */
		}
	op.type = GX_NUMBER;
	if (count < 1)
	{
		if (_gx_get_blanks_are_zeros(_gx_get_expr_si()))
			op.val.number = 0.0;
		else
			_gx_function_error(GX_FN_ERR_SAMPLE_SIZE_LT_1);
	}
	else
		op.val.number = sum / count;

	return op;
}

/* called by gmean */
static gxNumber glog(gxNumber x)
{
	if (x <= 0.)
		_gx_function_error(GX_FN_ERR_OP_LE_0);
	return log(x);
}

/* geometric mean */
gxOperand __cdecl _gx_fn_gmean(gxOperand argv[])
{
	gxNumber sum,
			 x;
	gxOperand op;
	int i,
		n = argv->val.count;
	int count;
	gxScanBuf scan;
	gxCell *cp;

	sum = 0.;
	count = 0;
	for (i = 0; i < n; i++)
		switch ((++argv)->type)
		{
		case GX_NUMBER:
			sum += glog(argv->val.number);
			count++;
			break;
		case GX_CELL:
			if (_gx_fn_get_value(argv->val.range.r0, argv->val.range.c0, &x))
			{
				sum += glog(x);
				count++;
			}
			break;
		case GX_RANGE:
			_gx_init_range_scan(_gx_get_expr_si(), argv->val.range, &scan,
								GX_CONSTANT_LIST | GX_RECALC_LIST);
			while ((cp = _gx_do_range_scan(&scan)) != NULL)
				if (_gx_fn_get_value(cp->row, cp->col, &x))
				{
					sum += glog(x);
					count++;
				}
			break;
		case GX_OP_ERROR:
			_gx_propagate_error(argv);
		default:
			break;  /* ignore it */
		}
	op.type = GX_NUMBER;
	if (count < 1)
		_gx_function_error(GX_FN_ERR_SAMPLE_SIZE_LT_1);
	errno = 0;
	op.val.number = exp(sum / count);
	if (errno)
		_gx_function_error(GX_FN_ERR_FLOAT);
	return op;
}

/* called by hmean */
static gxNumber hinv(gxNumber x)
{
	if (x == 0.)
		_gx_function_error(GX_FN_ERR_OP_EQ_0);
	return 1.0 / x;
}

/* harmonic mean */
gxOperand __cdecl _gx_fn_hmean(gxOperand argv[])
{
	gxNumber sum,
			 x;
	gxOperand op;
	int i,
		n = argv->val.count;
	int count;
	gxScanBuf scan;
	gxCell *cp;

	sum = 0.;
	count = 0;
	for (i = 0; i < n; i++)
		switch ((++argv)->type)
		{
		case GX_NUMBER:
			sum += hinv(argv->val.number);
			count++;
			break;
		case GX_CELL:
			if (_gx_fn_get_value(argv->val.range.r0, argv->val.range.c0, &x))
			{
				sum += hinv(x);
				count++;
			}
			break;
		case GX_RANGE:
			_gx_init_range_scan(_gx_get_expr_si(), argv->val.range, &scan,
								GX_CONSTANT_LIST | GX_RECALC_LIST);
			while ((cp = _gx_do_range_scan(&scan)) != NULL)
				if (_gx_fn_get_value(cp->row, cp->col, &x))
				{
					sum += hinv(x);
					count++;
				}
			break;
		case GX_OP_ERROR:
			_gx_propagate_error(argv);
		default:
			break;  /* ignore it */
		}
	if (count < 1)
		_gx_function_error(GX_FN_ERR_SAMPLE_SIZE_LT_1);
	op.type = GX_NUMBER;
	op.val.number = count / sum;
	return op;
}

gxOperand __cdecl _gx_fn_msq(gxOperand argv[])
{
	gxNumber sum2,
			 x;
	gxOperand op;
	int i,
		n = argv->val.count;
	int count;
	gxScanBuf scan;
	gxCell *cp;

	sum2 = 0.;
	count = 0;
	for (i = 0; i < n; i++)
		switch ((++argv)->type)
		{
		case GX_NUMBER:
			sum2 += argv->val.number * argv->val.number;
			count++;
			break;
		case GX_CELL:
			if (_gx_fn_get_value(argv->val.range.r0, argv->val.range.c0, &x))
			{
				sum2 += x * x;
				count++;
			}
			break;
		case GX_RANGE:
			_gx_init_range_scan(_gx_get_expr_si(), argv->val.range, &scan,
								GX_CONSTANT_LIST | GX_RECALC_LIST);
			while ((cp = _gx_do_range_scan(&scan)) != NULL)
				if (_gx_fn_get_value(cp->row, cp->col, &x))
				{
					sum2 += x * x;
					count++;
				}
			break;
		case GX_OP_ERROR:
			_gx_propagate_error(argv);
		default:
			break;  /* ignore it */
		}
	if (count < 1)
		_gx_function_error(GX_FN_ERR_SAMPLE_SIZE_LT_1);
	op.type = GX_NUMBER;
	op.val.number = sum2 / count;
	return op;
}

gxOperand __cdecl _gx_fn_rms(gxOperand argv[])
{
	gxNumber sum2,
			 x;
	gxOperand op;
	int i,
		n = argv->val.count;
	int count;
	gxScanBuf scan;
	gxCell *cp;

	sum2 = 0.;
	count = 0;
	for (i = 0; i < n; i++)
		switch ((++argv)->type)
		{
		case GX_NUMBER:
			sum2 += argv->val.number * argv->val.number;
			count++;
			break;
		case GX_CELL:
			if (_gx_fn_get_value(argv->val.range.r0, argv->val.range.c0, &x))
			{
				sum2 += x * x;
				count++;
			}
			break;
		case GX_RANGE:
			_gx_init_range_scan(_gx_get_expr_si(), argv->val.range, &scan,
								GX_CONSTANT_LIST | GX_RECALC_LIST);
			while ((cp = _gx_do_range_scan(&scan)) != NULL)
				if (_gx_fn_get_value(cp->row, cp->col, &x))
				{
					sum2 += x * x;
					count++;
				}
			break;
		case GX_OP_ERROR:
			_gx_propagate_error(argv);
		default:
			break;  /* ignore it */
		}
	if (count < 1)
		_gx_function_error(GX_FN_ERR_SAMPLE_SIZE_LT_1);
	op.type = GX_NUMBER;
	op.val.number = sqrt(sum2 / count);
	return op;
}

gxOperand __cdecl _gx_fn_min(gxOperand argv[])
{
	gxNumber minval = HUGE,
			 x;
	gxOperand op;
	int i,
		n = argv->val.count;
	int count = 0;
	gxScanBuf scan;
	gxCell *cp;

	for (i = 0; i < n; i++)
		switch ((++argv)->type)
		{
		case GX_NUMBER:
			minval = GX_MIN(minval, argv->val.number);
			++count;
			break;
		case GX_CELL:
			if (_gx_fn_get_value(argv->val.range.r0, argv->val.range.c0, &x))
			{
				minval = GX_MIN(minval, x);
				++count;
			}
			break;
		case GX_RANGE:
			_gx_init_range_scan(_gx_get_expr_si(), argv->val.range, &scan,
								GX_CONSTANT_LIST | GX_RECALC_LIST);
			while ((cp = _gx_do_range_scan(&scan)) != NULL)
				if (_gx_fn_get_value(cp->row, cp->col, &x))
				{
					minval = GX_MIN(minval, x);
					++count;
				}
			break;
		case GX_OP_ERROR:
			_gx_propagate_error(argv);
		default:
			break;  /* ignore it */
		}
	if (count < 1)
		_gx_function_error(GX_FN_ERR_SAMPLE_SIZE_LT_1);
	op.type = GX_NUMBER;
	op.val.number = minval;
	return op;
}

gxOperand __cdecl _gx_fn_max(gxOperand argv[])
{
	gxNumber maxval = -HUGE,
			 x;
	gxOperand op;
	int i,
		n = argv->val.count;
	int count = 0;
	gxScanBuf scan;
	gxCell *cp;

	for (i = 0; i < n; i++)
		switch ((++argv)->type)
		{
		case GX_NUMBER:
			maxval = GX_MAX(maxval, argv->val.number);
			++count;
			break;
		case GX_CELL:
			if (_gx_fn_get_value(argv->val.range.r0, argv->val.range.c0, &x))
			{
				maxval = GX_MAX(maxval, x);
				++count;
			}
			break;
		case GX_RANGE:
			_gx_init_range_scan(_gx_get_expr_si(), argv->val.range, &scan,
								GX_CONSTANT_LIST | GX_RECALC_LIST);
			while ((cp = _gx_do_range_scan(&scan)) != NULL)
				if (_gx_fn_get_value(cp->row, cp->col, &x))
				{
					maxval = GX_MAX(maxval, x);
					++count;
				}
			break;
		case GX_OP_ERROR:
			_gx_propagate_error(argv);
		default:
			break;  /* ignore it */
		}
	if (count < 1)
		_gx_function_error(GX_FN_ERR_SAMPLE_SIZE_LT_1);
	op.type = GX_NUMBER;
	op.val.number = maxval;
	return op;
}

gxOperand __cdecl _gx_fn_var(gxOperand argv[])
{
	gxNumber sum,
			 sum2,
			 x;
	gxOperand op;
	int i,
		n = argv->val.count;
	int count;

	sum = sum2 = 0.;
	count = 0;
	for (i = 0; i < n; i++)
		switch ((++argv)->type)
		{
		case GX_NUMBER:
			x = argv->val.number;
			sum += x;
			sum2 += x * x;
			count++;
			break;
		case GX_CELL:
			if (_gx_fn_get_value(argv->val.range.r0, argv->val.range.c0, &x))
			{
				sum += x;
				sum2 += x * x;
				count++;
			}
			break;
		case GX_RANGE:
			range_stats(&(argv->val.range), &sum, &sum2, &count);
			break;
		case GX_OP_ERROR:
			_gx_propagate_error(argv);
		default:
			break;  /* ignore it */
		}
	if (count < 1)
		_gx_function_error(GX_FN_ERR_POP_LT_1);
	op.type = GX_NUMBER;
	op.val.number = (sum2 - (sum * sum) / count) / count;
	return op;
}

gxOperand __cdecl _gx_fn_std(gxOperand argv[])
{
	gxNumber sum,
			 sum2,
			 x;
	gxOperand op;
	int i,
		n = argv->val.count;
	int count;

	sum = sum2 = 0.;
	count = 0;
	for (i = 0; i < n; i++)
		switch ((++argv)->type)
		{
		case GX_NUMBER:
			x = argv->val.number;
			sum += x;
			sum2 += x * x;
			count++;
			break;
		case GX_CELL:
			if (_gx_fn_get_value(argv->val.range.r0, argv->val.range.c0, &x))
			{
				sum += x;
				sum2 += x * x;
				count++;
			}
			break;
		case GX_RANGE:
			range_stats(&(argv->val.range), &sum, &sum2, &count);
			break;
		case GX_OP_ERROR:
			_gx_propagate_error(argv);
		default:
			break;  /* ignore it */
		}
	if (count < 1)
		_gx_function_error(GX_FN_ERR_POP_LT_1);
	op.type = GX_NUMBER;
	op.val.number = sqrt((sum2 - (sum * sum) / count) / count);
	return op;
}

gxOperand __cdecl _gx_fn_vars(gxOperand argv[])
{
	gxNumber sum,
			 sum2,
			 x;
	gxOperand op;
	int i,
		n = argv->val.count;
	int count;

	sum = sum2 = 0.;
	count = 0;
	for (i = 0; i < n; i++)
		switch ((++argv)->type)
		{
		case GX_NUMBER:
			x = argv->val.number;
			sum += x;
			sum2 += x * x;
			count++;
			break;
		case GX_CELL:
			if (_gx_fn_get_value(argv->val.range.r0, argv->val.range.c0, &x))
			{
				sum += x;
				sum2 += x * x;
				count++;
			}
			break;
		case GX_RANGE:
			range_stats(&(argv->val.range), &sum, &sum2, &count);
			break;
		case GX_OP_ERROR:
			_gx_propagate_error(argv);
		default:
			break;  /* ignore it */
		}
	if (count < 2)
		_gx_function_error(GX_FN_ERR_SAMPLE_SIZE_LT_2);
	op.type = GX_NUMBER;
	op.val.number = (sum2 - (sum * sum) / count) / (count - 1);
	return op;
}

gxOperand __cdecl _gx_fn_stds(gxOperand argv[])
{
	gxNumber sum,
			 sum2,
			 x;
	gxOperand op;
	int i,
		n = argv->val.count;
	int count;

	sum = sum2 = 0.;
	count = 0;
	for (i = 0; i < n; i++)
		switch ((++argv)->type)
		{
		case GX_NUMBER:
			x = argv->val.number;
			sum += x;
			sum2 += x * x;
			count++;
			break;
		case GX_CELL:
			if (_gx_fn_get_value(argv->val.range.r0, argv->val.range.c0, &x))
			{
				sum += x;
				sum2 += x * x;
				count++;
			}
			break;
		case GX_RANGE:
			range_stats(&(argv->val.range), &sum, &sum2, &count);
			break;
		case GX_OP_ERROR:
			_gx_propagate_error(argv);
		default:
			break;  /* ignore it */
		}
	if (count < 2)
		_gx_function_error(GX_FN_ERR_SAMPLE_SIZE_LT_2);
	op.type = GX_NUMBER;
	op.val.number = sqrt((sum2 - (sum * sum) / count) / (count - 1));
	return op;
}

gxOperand __cdecl _gx_fn_count(gxOperand argv[])
{
	gxOperand op;
	int i,
		n = argv->val.count;
	int count;
	gxScanBuf scan;
	gxCell *cp;

	count = 0;
	for (i = 0; i < n; i++)
		switch ((++argv)->type)
		{
		case GX_NUMBER:
			count++;
			break;
		case GX_STRING:
			count++;
			break;
		case GX_CELL:
			cp = _gx_find_cell(_gx_get_expr_si(),
							   argv->val.range.r0, argv->val.range.c0);
			if (!GX_CELL_IS_EMPTYVALUE(cp))
				count++;
			break;
		case GX_RANGE:
			_gx_init_range_scan(_gx_get_expr_si(), argv->val.range, &scan,
								GX_CONSTANT_LIST | GX_RECALC_LIST);
			while ((cp = _gx_do_range_scan(&scan)) != NULL)
			{
				if (!GX_CELL_IS_EMPTYVALUE(cp))
					count++;
			}
			break;
		case GX_OP_ERROR:
			_gx_propagate_error(argv);
		}
	op.type = GX_NUMBER;
	op.val.number = (double) count;
	return op;
}

gxOperand __cdecl _gx_fn_t(gxOperand argv[])
{
	gxOperand op;
	double df,
		   t;

	if (argv->val.count != 2)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 1);
	_gx_cvt2constant(argv + 2);
	if ((argv[1].type != GX_NUMBER) || (argv[2].type != GX_NUMBER))
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	df = argv[1].val.number;
	t = argv[2].val.number;
	if (df <= 0.0)
		_gx_function_error(GX_FN_ERR_DF_GT_0);
	op.type = GX_NUMBER;
	if (t <= 0.0)
		op.val.number = 0.5 * _gx_alphaT(df, t);
	else
		op.val.number = 1.0 - 0.5 * _gx_alphaT(df, t);
	if (_gx_get_expr_err_flag())
		_gx_function_error(GX_FN_ERR_FLOAT);
	return op;
}

gxOperand __cdecl _gx_fn_f(gxOperand argv[])
{
	gxOperand op;

	if (argv->val.count != 3)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 1);
	_gx_cvt2constant(argv + 2);
	_gx_cvt2constant(argv + 3);
	if ((argv[1].type != GX_NUMBER) || (argv[2].type != GX_NUMBER) ||
		(argv[3].type != GX_NUMBER))
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	if (argv[1].val.number <= 0.0 || argv[2].val.number <= 0.0)
		_gx_function_error(GX_FN_ERR_DF_GT_0);
	if (argv[3].val.number < 0.0)
		_gx_function_error(GX_FN_ERR_F_GE_0);
	op.type = GX_NUMBER;
	op.val.number = 1.0 - _gx_alphaF(argv[1].val.number,
									 argv[2].val.number, argv[3].val.number);
	if (_gx_get_expr_err_flag())
		_gx_function_error(GX_FN_ERR_FLOAT);
	return op;
}

/* single population t-test */
gxOperand __cdecl _gx_fn_ttest(gxOperand argv[])
{
	gxNumber sum,
			 sum2,
			 t,
			 denom;
	gxOperand op;
	int count;

	if (argv->val.count != 2)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 2);
	GX_HANDLE_OP_ERROR(argv[1]);
	if ((argv[1].type != GX_RANGE) || (argv[2].type != GX_NUMBER))
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	sum = sum2 = 0.;
	count = 0;
	range_stats(&(argv[1].val.range), &sum, &sum2, &count);
	if (count < 2)
		_gx_function_error(GX_FN_ERR_SAMPLE_SIZE_LT_2);
	denom = sum2 - (sum * sum) / count;
	if (denom == 0.0)
	{   /* certainty */
		op.type = GX_NUMBER;
		op.val.number = 1.0;
		return op;
	}
	t = (sum / count - argv[2].val.number) *
		sqrt(count * (count - 1) / denom);
	op.type = GX_NUMBER;
	op.val.number = _gx_alphaT((gxNumber) (count - 1), t);
	if (_gx_get_expr_err_flag())
		_gx_function_error(GX_FN_ERR_FLOAT);
	return op;
}

/* paired t-test */
gxOperand __cdecl _gx_fn_pttest(gxOperand argv[])
{
	gxNumber sum,
			 sum2,
			 x,
			 y,
			 t,
			 denom;
	gxOperand op;
	int count,
		r,
		c,
		dr,
		dc,
		flagx,
		flagy;
	gxScanBuf scan;
	gxCell *cp;

	if (argv->val.count != 2)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	GX_HANDLE_OP_ERROR(argv[1]);
	GX_HANDLE_OP_ERROR(argv[2]);
	if ((argv[1].type != GX_RANGE) || (argv[2].type != GX_RANGE))
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	if ((argv[1].val.range.r1 - argv[1].val.range.r0 !=
		 argv[2].val.range.r1 - argv[2].val.range.r0) ||
		(argv[1].val.range.c1 - argv[1].val.range.c0 !=
		 argv[2].val.range.c1 - argv[2].val.range.c0))
		_gx_function_error(GX_FN_ERR_RNG_DIM_EQ);

	dr = argv[2].val.range.r0 - argv[1].val.range.r0;
	dc = argv[2].val.range.c0 - argv[1].val.range.c0;

	sum = sum2 = 0.;
	count = 0;

	_gx_init_range_scan(_gx_get_expr_si(), argv[1].val.range, &scan,
						GX_CONSTANT_LIST | GX_RECALC_LIST);
	while ((cp = _gx_do_range_scan(&scan)) != NULL)
	{
		r = cp->row;
		c = cp->col;
		flagx = _gx_fn_get_value(r, c, &x);
		flagy = _gx_fn_get_value(r + dr, c + dc, &y);
		if (flagx != flagy)
			_gx_function_error(GX_FN_ERR_SAMPLE_MISSING);
		if (flagx)
		{
			sum += x - y;
			sum2 += (x - y) * (x - y);
			count++;
		}
	}

	if (count < 2)
		_gx_function_error(GX_FN_ERR_SAMPLE_SIZE_LT_2);
	denom = sum2 - (sum * sum) / count;
	if (denom == 0.0)
	{   /* certainty */
		op.type = GX_NUMBER;
		op.val.number = 1.0;
		return op;
	}
	t = (sum / count) * sqrt(count * (count - 1) / denom);
	op.type = GX_NUMBER;
	op.val.number = _gx_alphaT((gxNumber) (count - 1), t);
	if (_gx_get_expr_err_flag())
		_gx_function_error(GX_FN_ERR_FLOAT);
	return op;
}

/* unpaired, equal variance */
gxOperand __cdecl _gx_fn_ttest2ev(gxOperand argv[])
{
	gxNumber sum,
			 sum2,
			 ux,
			 uy,
			 s2x,
			 s2y,
			 t,
			 denom;
	gxOperand op;
	int count,
		nx,
		ny;

	if (argv->val.count != 2)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	GX_HANDLE_OP_ERROR(argv[1]);
	GX_HANDLE_OP_ERROR(argv[2]);
	if ((argv[1].type != GX_RANGE) || (argv[2].type != GX_RANGE))
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);

	sum = sum2 = 0.;
	count = 0;
	range_stats(&(argv[1].val.range), &sum, &sum2, &count);
	ux = sum / count;
	s2x = sum2 - (sum * sum) / count;
	nx = count;

	sum = sum2 = 0.;
	count = 0;
	range_stats(&(argv[2].val.range), &sum, &sum2, &count);
	uy = sum / count;
	s2y = sum2 - (sum * sum) / count;
	ny = count;

	if ((nx + ny) < 3)
		_gx_function_error(GX_FN_ERR_POOL_LT_3);
	denom = sqrt(((s2x + s2y) / (nx + ny - 2)) * (1.0 / nx + 1.0 / ny));
	if (denom == 0.0)
	{   /* certainty */
		op.type = GX_NUMBER;
		op.val.number = 1.0;
		return op;
	}
	t = (ux - uy) / denom;
	op.type = GX_NUMBER;
	op.val.number = _gx_alphaT((gxNumber) (nx + ny - 2), t);
	if (_gx_get_expr_err_flag())
		_gx_function_error(GX_FN_ERR_FLOAT);
	return op;
}

/* unpaired, unequal variance */
gxOperand __cdecl _gx_fn_ttest2uv(gxOperand argv[])
{
	gxNumber sum,
			 sum2,
			 ux,
			 uy,
			 varnx,
			 varny,
			 nu,
			 t,
			 denom;
	gxOperand op;
	int count,
		nx,
		ny;

	if (argv->val.count != 2)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	GX_HANDLE_OP_ERROR(argv[1]);
	GX_HANDLE_OP_ERROR(argv[2]);
	if ((argv[1].type != GX_RANGE) || (argv[2].type != GX_RANGE))
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);

	sum = sum2 = 0.;
	count = 0;
	range_stats(&(argv[1].val.range), &sum, &sum2, &count);
	if (count < 2)
		_gx_function_error(GX_FN_ERR_SAMPLE_SIZE_LT_2);
	ux = sum / count;
	varnx = (sum2 - (sum * sum) / count) / ((count - 1) * count);
	nx = count;

	sum = sum2 = 0.;
	count = 0;
	range_stats(&(argv[2].val.range), &sum, &sum2, &count);
	if (count < 2)
		_gx_function_error(GX_FN_ERR_SAMPLE_SIZE_LT_2);
	uy = sum / count;
	varny = (sum2 - (sum * sum) / count) / ((count - 1) * count);
	ny = count;

	nu = (varnx + varny) * (varnx + varny) /
		(varnx * varnx / (nx - 1) + varny * varny / (ny - 1));

	denom = sqrt(varnx + varny);
	if (denom == 0.0)
	{   /* certainty */
		op.type = GX_NUMBER;
		op.val.number = 1.0;
		return op;
	}
	t = (ux - uy) / denom;
	op.type = GX_NUMBER;
	op.val.number = _gx_alphaT(nu, t);
	if (_gx_get_expr_err_flag())
		_gx_function_error(GX_FN_ERR_FLOAT);
	return op;
}

gxOperand __cdecl _gx_fn_ftest(gxOperand argv[])
{
	gxNumber sum,
			 sum2,
			 varx,
			 vary,
			 alpha;
	gxOperand op;
	int count,
		nx,
		ny;

	if (argv->val.count != 2)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	GX_HANDLE_OP_ERROR(argv[1]);
	GX_HANDLE_OP_ERROR(argv[2]);
	if ((argv[1].type != GX_RANGE) || (argv[2].type != GX_RANGE))
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);

	sum = sum2 = 0.;
	count = 0;
	range_stats(&(argv[1].val.range), &sum, &sum2, &count);
	if (count < 2)
		_gx_function_error(GX_FN_ERR_SAMPLE_SIZE_LT_2);
	varx = (sum2 - (sum * sum) / count) / (count - 1);
	nx = count;

	sum = sum2 = 0.;
	count = 0;
	range_stats(&(argv[2].val.range), &sum, &sum2, &count);
	if (count < 2)
		_gx_function_error(GX_FN_ERR_SAMPLE_SIZE_LT_2);
	vary = (sum2 - (sum * sum) / count) / (count - 1);
	ny = count;

	if (varx == 0.0 && vary == 0.0)
	{
		alpha = 2.0 * _gx_alphaF((double) (nx - 1), (double) (ny - 1), 1.0);
	}
	else if (vary > varx)
	{
		alpha = 2.0 * _gx_alphaF((double) (ny - 1), (double) (nx - 1), vary / varx);
	}
	else
	{
		alpha = 2.0 * _gx_alphaF((double) (nx - 1), (double) (ny - 1), varx / vary);
	}
	if (_gx_get_expr_err_flag())
		_gx_function_error(GX_FN_ERR_FLOAT);
	if (alpha > 1.0)
		alpha = 2.0 - alpha;
	op.type = GX_NUMBER;
	op.val.number = alpha;
	return op;
}

/* Pearson product-moment correlation coeff */
gxOperand __cdecl _gx_fn_corr(gxOperand argv[])
{
	gxNumber sumx,
			 sumy,
			 sum2x,
			 sum2y,
			 sumxy,
			 x,
			 y;
	gxOperand op;
	int count,
		r,
		c,
		dr,
		dc,
		flagx,
		flagy;
	gxScanBuf scan;
	gxCell *cp;

	if (argv->val.count != 2)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	GX_HANDLE_OP_ERROR(argv[1]);
	GX_HANDLE_OP_ERROR(argv[2]);
	if ((argv[1].type != GX_RANGE) || (argv[2].type != GX_RANGE))
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	if ((argv[1].val.range.r1 - argv[1].val.range.r0 !=
		 argv[2].val.range.r1 - argv[2].val.range.r0) ||
		(argv[1].val.range.c1 - argv[1].val.range.c0 !=
		 argv[2].val.range.c1 - argv[2].val.range.c0))
		_gx_function_error(GX_FN_ERR_RNG_DIM_EQ);

	dr = argv[2].val.range.r0 - argv[1].val.range.r0;
	dc = argv[2].val.range.c0 - argv[1].val.range.c0;

	sumx = sumy = sum2x = sum2y = sumxy = 0.0;
	count = 0;

	_gx_init_range_scan(_gx_get_expr_si(), argv[1].val.range, &scan,
						GX_CONSTANT_LIST | GX_RECALC_LIST);
	while ((cp = _gx_do_range_scan(&scan)) != NULL)
	{
		r = cp->row;
		c = cp->col;
		flagx = _gx_fn_get_value(r, c, &x);
		flagy = _gx_fn_get_value(r + dr, c + dc, &y);
		if (flagx != flagy)
			_gx_function_error(GX_FN_ERR_SAMPLE_MISSING);
		if (flagx)
		{
			sumx += x;
			sumy += y;
			sum2x += x * x;
			sum2y += y * y;
			sumxy += x * y;
			count++;
		}
	}

	op.type = GX_NUMBER;
	op.val.number = (count * sumxy - sumx * sumy) /
		sqrt((count * sum2x - sumx * sumx) * (count * sum2y - sumy * sumy));
	return op;
}

gxOperand __cdecl _gx_fn_normsdist(gxOperand argv[])
{
	gxOperand op;

	op.val.number = _gx_phi(_gx_get_one_number(argv));
	op.type = GX_NUMBER;
	return op;
}

gxOperand __cdecl _gx_fn_normsinv(gxOperand argv[])
{
	gxOperand op;
	gxNumber p = _gx_get_one_number(argv);

	if (p <= 0.0 || p >= 1.0)
		_gx_function_error(GX_FN_ERR_OP_OUT_OF_RANGE);

	op.val.number = _gx_phi_inverse(p);
	op.type = GX_NUMBER;
	return op;
}

gxOperand __cdecl _gx_fn_normdist(gxOperand argv[])
{
	gxOperand op;
	gxNumber mu,
			 sigma,
			 x,
			 cumulative,
			 z;

	_gx_cvt2constant(argv + 1);
	if (argv[1].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	_gx_cvt2constant(argv + 2);
	if (argv[2].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	_gx_cvt2constant(argv + 3);
	if (argv[3].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	_gx_cvt2constant(argv + 4);
	if (argv[4].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);

	x = argv[1].val.number;
	mu = argv[2].val.number;
	sigma = argv[3].val.number;
	cumulative = argv[4].val.number;

	if (sigma <= 0.0)
		_gx_function_error(GX_FN_ERR_OP_OUT_OF_RANGE);

	z = (x - mu) / sigma;

	if (cumulative == 0.0)
		op.val.number = exp(-0.5 * z * z) / (sigma * sqrt(2.0 * GX_M_PI));
	else
		op.val.number = _gx_phi(z);

	op.type = GX_NUMBER;
	return op;
}

gxOperand __cdecl _gx_fn_norminv(gxOperand argv[])
{
	gxOperand op;
	gxNumber mu,
			 sigma,
			 p;

	_gx_cvt2constant(argv + 1);
	if (argv[1].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	_gx_cvt2constant(argv + 2);
	if (argv[2].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	_gx_cvt2constant(argv + 3);
	if (argv[3].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);

	p = argv[1].val.number;
	mu = argv[2].val.number;
	sigma = argv[3].val.number;

	if (p <= 0.0 || p >= 1.0)
		_gx_function_error(GX_FN_ERR_OP_OUT_OF_RANGE);
	if (sigma <= 0.0)
		_gx_function_error(GX_FN_ERR_OP_OUT_OF_RANGE);

	op.val.number = _gx_phi_inverse(p) * sigma + mu;

	op.type = GX_NUMBER;
	return op;
}

gxOperand __cdecl _gx_fn_ztest(gxOperand argv[])
{
	gxOperand op;
	gxNumber mu,
			 sigma = 0.0,
			 x,
			 sum = 0.0,
			 sum2 = 0.0;
	int count = 0;

	_gx_cvt2constant(argv + 2);
	if (argv[2].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	x = argv[2].val.number;

	if (argv[1].type != GX_RANGE)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);

	if (argv[0].val.count == 3)
	{
		_gx_cvt2constant(argv + 3);
		if (argv[3].type != GX_NUMBER)
			_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
		sigma = argv[3].val.number;
		if (sigma <= 0.0)
			_gx_function_error(GX_FN_ERR_OP_OUT_OF_RANGE);
	}
	range_stats(&(argv[1].val.range), &sum, &sum2, &count);
	if (count < 2)
		_gx_function_error(GX_FN_ERR_SAMPLE_SIZE_LT_2);

	mu = sum / count;
	if (sigma == 0.0)
		sigma = sqrt((sum2 - (sum * sum) / count) / (count - 1));
	op.type = GX_NUMBER;
	op.val.number = 1.0 - _gx_phi((mu - x) / (sigma / sqrt((double) count)));
	return op;
}

gxOperand __cdecl _gx_fn_standardize(gxOperand argv[])
{
	gxOperand op;
	gxNumber mu,
			 sigma,
			 x;

	_gx_cvt2constant(argv + 1);
	if (argv[1].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	_gx_cvt2constant(argv + 2);
	if (argv[2].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	_gx_cvt2constant(argv + 3);
	if (argv[3].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);

	x = argv[1].val.number;
	mu = argv[2].val.number;
	sigma = argv[3].val.number;

	if (sigma <= 0.0)
		_gx_function_error(GX_FN_ERR_OP_OUT_OF_RANGE);

	op.type = GX_NUMBER;
	op.val.number = (x - mu) / sigma;
	return op;
}

gxOperand __cdecl _gx_fn_confidence(gxOperand argv[])
{
	gxOperand op;
	gxNumber alpha,
			 sigma;
	int size;

	_gx_cvt2constant(argv + 1);
	if (argv[1].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	_gx_cvt2constant(argv + 2);
	if (argv[2].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	_gx_cvt2constant(argv + 3);
	if (argv[3].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);

	alpha = argv[1].val.number;
	sigma = argv[2].val.number;
	size = _gx_cvt2int(argv[3].val.number);

	if (alpha <= 0.0 || alpha >= 1.0)
		_gx_function_error(GX_FN_ERR_OP_OUT_OF_RANGE);
	if (sigma <= 0.0)
		_gx_function_error(GX_FN_ERR_OP_OUT_OF_RANGE);
	if (size < 1)
		_gx_function_error(GX_FN_ERR_OP_OUT_OF_RANGE);

	op.type = GX_NUMBER;
	op.val.number = _gx_phi_inverse(1.0 - 0.5 * alpha) * sigma / sqrt((double) size);
	return op;
}
