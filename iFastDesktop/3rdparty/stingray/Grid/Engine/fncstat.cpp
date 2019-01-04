///////////////////////////////////////////////////////////////////////////////
// fncstat.cpp: Conditional statistic worksheet functions
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

#define CEXPR_RANGE()   \
		eval_cstat_expr (si, argv->val.range.r0, \
				argv->val.range.c0, cexpr->val.etree.nbuf, \
				cexpr->val.etree.start)

#define CEXPR_CELL()    \
		eval_cstat_expr (si, cp->row, cp->col, \
				cexpr->val.etree.nbuf, \
				cexpr->val.etree.start)


#ifdef CELLRANGE
static int eval_cstat_expr(int si, int r, int c,
							   gxExprNode * nbuf, gxExprPointer start)
/*
 * This function handles "lazy" evaluation of the conditional expression
 * but also treats string results as a "deferred" expression ala version 2.
 */
{
	gxOperand result;
	int status;
	TCHAR expr_string[GX_MAX_TEXT];

	result = _gx_expr_eval(si, r, c, nbuf, start);

	switch (result.type)
	{
	case GX_NUMBER:
		return (result.val.number != 0.0);
	case GX_OP_ERROR:
		_gx_function_error(_gx_get_error_reason());
	case GX_STRING:
		// QA: 31989 - #if Secure Code Cleanup.
		_tcscpy(expr_string, result.val.string);
		status = _gx_si_evaluate_expr(si, expr_string, r, c, &result);
		if (!status)
			_gx_function_error(GX_FN_ERR_COND_STR_PARSE);
		switch (result.type)
		{
		case GX_NUMBER:
			return (result.val.number != 0.0);
		case GX_OP_ERROR:
			_gx_function_error(_gx_get_error_reason());
		default:
			_gx_function_error(GX_FN_ERR_NON_NUM_OPRND);
		}
	default:
		_gx_function_error(GX_FN_ERR_NON_NUM_OPRND);
	}
	return 0;
}
#endif

gxOperand __cdecl _gx_fn_csum(gxOperand argv[])
{
	gxNumber sum,
			 x;
	gxOperand op;
	int i,
		n = argv->val.count;
	gxOperand *cexpr = argv + n;
	gxCell *cp;
	gxScanBuf scan;
	int si = _gx_get_expr_si();

	sum = 0.;
	for (i = 0; i < n - 1; i++)
		switch ((++argv)->type)
		{
#ifdef CELLRANGE
		case GX_CELL:
			if (CEXPR_RANGE())
				if (_gx_fn_get_value(argv->val.range.r0, argv->val.range.c0, &x))
					sum += x;
			break;
		case GX_RANGE:
			_gx_init_range_scan(si, argv->val.range, &scan,
								GX_CONSTANT_LIST | GX_RECALC_LIST);
			while ((cp = _gx_do_range_scan(&scan)) != 0)
				if (CEXPR_CELL())
					if (_gx_fn_get_value(cp->row, cp->col, &x))
						sum += x;
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

gxOperand __cdecl _gx_fn_cavg(gxOperand argv[])
{
	gxNumber sum,
			 x;
	gxOperand op;
	int i,
		n = argv->val.count;
	int count;
	gxOperand *cexpr = argv + n;
	gxCell *cp;
	gxScanBuf scan;
	int si = _gx_get_expr_si();

	sum = 0.;
	count = 0;
	for (i = 0; i < n - 1; i++)
		switch ((++argv)->type)
		{
#ifdef CELLRANGE
		case GX_CELL:
			if (CEXPR_RANGE())
				if (_gx_fn_get_value(argv->val.range.r0, argv->val.range.c0, &x))
				{
					sum += x;
					count++;
				}
			break;
		case GX_RANGE:
			_gx_init_range_scan(si, argv->val.range, &scan,
								GX_CONSTANT_LIST | GX_RECALC_LIST);
			while ((cp = _gx_do_range_scan(&scan)) != 0)
				if (CEXPR_CELL())
					if (_gx_fn_get_value(cp->row, cp->col, &x))
					{
						sum += x;
						count++;
					}
			break;
#endif
		case GX_OP_ERROR:
			_gx_propagate_error(argv);
		default:
			_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
		}
	if (count < 1)
		_gx_function_error(GX_FN_ERR_SAMPLE_SIZE_LT_1);
	op.type = GX_NUMBER;
	op.val.number = sum / count;
	return op;
}

gxOperand __cdecl _gx_fn_cmin(gxOperand argv[])
{
	gxNumber minval = HUGE,
			 x;
	gxOperand op;
	int i,
		n = argv->val.count;
	int count = 0;
	gxOperand *cexpr = argv + n;
	gxCell *cp;
	gxScanBuf scan;
	int si = _gx_get_expr_si();

	for (i = 0; i < n - 1; i++)
		switch ((++argv)->type)
		{
#ifdef CELLRANGE
		case GX_CELL:
			if (CEXPR_RANGE())
				if (_gx_fn_get_value(argv->val.range.r0, argv->val.range.c0, &x))
				{
					minval = GX_MIN(minval, x);
					++count;
				}
			break;
		case GX_RANGE:
			_gx_init_range_scan(si, argv->val.range, &scan,
								GX_CONSTANT_LIST | GX_RECALC_LIST);
			while ((cp = _gx_do_range_scan(&scan)) != 0)
				if (CEXPR_CELL())
					if (_gx_fn_get_value(cp->row, cp->col, &x))
					{
						minval = GX_MIN(minval, x);
						++count;
					}
			break;
#endif
		case GX_OP_ERROR:
			_gx_propagate_error(argv);
		default:
			_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
		}
	if (count < 1)
		_gx_function_error(GX_FN_ERR_SAMPLE_SIZE_LT_1);
	op.type = GX_NUMBER;
	op.val.number = minval;
	return op;
}

gxOperand __cdecl _gx_fn_cmax(gxOperand argv[])
{
	gxNumber maxval = -HUGE,
			 x;
	gxOperand op;
	int i,
		n = argv->val.count;
	int count = 0;
	gxOperand *cexpr = argv + n;
	gxCell *cp;
	gxScanBuf scan;
	int si = _gx_get_expr_si();

	for (i = 0; i < n - 1; i++)
		switch ((++argv)->type)
		{
#ifdef CELLRANGE
		case GX_CELL:
			if (CEXPR_RANGE())
				if (_gx_fn_get_value(argv->val.range.r0, argv->val.range.c0, &x))
				{
					maxval = GX_MAX(maxval, x);
					++count;
				}
			break;
		case GX_RANGE:
			_gx_init_range_scan(si, argv->val.range, &scan,
								GX_CONSTANT_LIST | GX_RECALC_LIST);
			while ((cp = _gx_do_range_scan(&scan)) != 0)
				if (CEXPR_CELL())
					if (_gx_fn_get_value(cp->row, cp->col, &x))
					{
						maxval = GX_MAX(maxval, x);
						++count;
					}
			break;
#endif
		case GX_OP_ERROR:
			_gx_propagate_error(argv);
		default:
			_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
		}
	if (count < 1)
		_gx_function_error(GX_FN_ERR_SAMPLE_SIZE_LT_1);
	op.type = GX_NUMBER;
	op.val.number = maxval;
	return op;
}

gxOperand __cdecl _gx_fn_cvar(gxOperand argv[])
{
	gxNumber sum,
			 sum2,
			 x;
	gxOperand op;
	int i,
		n = argv->val.count;
	int count;
	gxOperand *cexpr = argv + n;
	gxCell *cp;
	gxScanBuf scan;
	int si = _gx_get_expr_si();

	sum = 0.;
	sum2 = 0.;
	count = 0;
	for (i = 0; i < n - 1; i++)
		switch ((++argv)->type)
		{
#ifdef CELLRANGE
		case GX_CELL:
			if (CEXPR_RANGE())
				if (_gx_fn_get_value(argv->val.range.r0, argv->val.range.c0, &x))
				{
					sum += x;
					sum2 += x * x;
					count++;
				}
			break;
		case GX_RANGE:
			_gx_init_range_scan(si, argv->val.range, &scan,
								GX_CONSTANT_LIST | GX_RECALC_LIST);
			while ((cp = _gx_do_range_scan(&scan)) != 0)
				if (CEXPR_CELL())
					if (_gx_fn_get_value(cp->row, cp->col, &x))
					{
						sum += x;
						sum2 += x * x;
						count++;
					}
			break;
#endif
		case GX_OP_ERROR:
			_gx_propagate_error(argv);
		default:
			_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
		}
	if (count < 1)
		_gx_function_error(GX_FN_ERR_POP_LT_1);
	op.type = GX_NUMBER;
	op.val.number = (sum2 - (sum * sum) / count) / count;
	return op;
}

gxOperand __cdecl _gx_fn_cstd(gxOperand argv[])
{
	gxNumber sum,
			 sum2,
			 x;
	gxOperand op;
	int i,
		n = argv->val.count;
	int count;
	gxOperand *cexpr = argv + n;
	gxCell *cp;
	gxScanBuf scan;
	int si = _gx_get_expr_si();

	sum = 0.;
	sum2 = 0.;
	count = 0;
	for (i = 0; i < n - 1; i++)
		switch ((++argv)->type)
		{
#ifdef CELLRANGE
		case GX_CELL:
			if (CEXPR_RANGE())
				if (_gx_fn_get_value(argv->val.range.r0, argv->val.range.c0, &x))
				{
					sum += x;
					sum2 += x * x;
					count++;
				}
			break;
		case GX_RANGE:
			_gx_init_range_scan(si, argv->val.range, &scan,
								GX_CONSTANT_LIST | GX_RECALC_LIST);
			while ((cp = _gx_do_range_scan(&scan)) != 0)
				if (CEXPR_CELL())
					if (_gx_fn_get_value(cp->row, cp->col, &x))
					{
						sum += x;
						sum2 += x * x;
						count++;
					}
			break;
#endif
		case GX_OP_ERROR:
			_gx_propagate_error(argv);
		default:
			_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
		}
	if (count < 1)
		_gx_function_error(GX_FN_ERR_POP_LT_1);
	op.type = GX_NUMBER;
	op.val.number = sqrt((sum2 - (sum * sum) / count) / count);
	return op;
}

gxOperand __cdecl _gx_fn_cvars(gxOperand argv[])
{
	gxNumber sum,
			 sum2,
			 x;
	gxOperand op;
	int i,
		n = argv->val.count;
	int count;
	gxOperand *cexpr = argv + n;
	gxCell *cp;
	gxScanBuf scan;
	int si = _gx_get_expr_si();

	sum = 0.;
	sum2 = 0.;
	count = 0;
	for (i = 0; i < n - 1; i++)
		switch ((++argv)->type)
		{
#ifdef CELLRANGE
		case GX_CELL:
			if (CEXPR_RANGE())
				if (_gx_fn_get_value(argv->val.range.r0, argv->val.range.c0, &x))
				{
					sum += x;
					sum2 += x * x;
					count++;
				}
			break;
		case GX_RANGE:
			_gx_init_range_scan(si, argv->val.range, &scan,
								GX_CONSTANT_LIST | GX_RECALC_LIST);
			while ((cp = _gx_do_range_scan(&scan)) != 0)
				if (CEXPR_CELL())
					if (_gx_fn_get_value(cp->row, cp->col, &x))
					{
						sum += x;
						sum2 += x * x;
						count++;
					}
			break;
#endif
		case GX_OP_ERROR:
			_gx_propagate_error(argv);
		default:
			_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
		}
	if (count < 2)
		_gx_function_error(GX_FN_ERR_SAMPLE_SIZE_LT_2);
	op.type = GX_NUMBER;
	op.val.number = (sum2 - (sum * sum) / count) / (count - 1);
	return op;
}

gxOperand __cdecl _gx_fn_cstds(gxOperand argv[])
{
	gxNumber sum,
			 sum2,
			 x;
	gxOperand op;
	int i,
		n = argv->val.count;
	int count;
	gxOperand *cexpr = argv + n;
	gxCell *cp;
	gxScanBuf scan;
	int si = _gx_get_expr_si();

	sum = 0.;
	sum2 = 0.;
	count = 0;
	for (i = 0; i < n - 1; i++)
		switch ((++argv)->type)
		{
#ifdef CELLRANGE
		case GX_CELL:
			if (CEXPR_RANGE())
				if (_gx_fn_get_value(argv->val.range.r0, argv->val.range.c0, &x))
				{
					sum += x;
					sum2 += x * x;
					count++;
				}
			break;
		case GX_RANGE:
			_gx_init_range_scan(si, argv->val.range, &scan,
								GX_CONSTANT_LIST | GX_RECALC_LIST);
			while ((cp = _gx_do_range_scan(&scan)) != 0)
				if (CEXPR_CELL())
					if (_gx_fn_get_value(cp->row, cp->col, &x))
					{
						sum += x;
						sum2 += x * x;
						count++;
					}
			break;
#endif
		case GX_OP_ERROR:
			_gx_propagate_error(argv);
		default:
			_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
		}
	if (count < 2)
		_gx_function_error(GX_FN_ERR_SAMPLE_SIZE_LT_2);
	op.type = GX_NUMBER;
	op.val.number = sqrt((sum2 - (sum * sum) / count) / (count - 1));
	return op;
}

gxOperand __cdecl _gx_fn_ccount(gxOperand argv[])
{
	gxOperand op;
	int i,
		n = argv->val.count;
	int count;
	gxOperand *cexpr = argv + n;
	gxCell *cp;
	gxScanBuf scan;
	int si = _gx_get_expr_si();

	count = 0;
	for (i = 0; i < n - 1; i++)
		switch ((++argv)->type)
		{
#ifdef CELLRANGE
		case GX_CELL:
			if (CEXPR_RANGE())
			{
				cp = _gx_find_cell(si, argv->val.range.r0, argv->val.range.c0);
				if (!GX_CELL_IS_EMPTYVALUE(cp))
					count++;
			}
			break;
		case GX_RANGE:
			_gx_init_range_scan(si, argv->val.range, &scan,
								GX_CONSTANT_LIST | GX_RECALC_LIST);
			while ((cp = _gx_do_range_scan(&scan)) != 0)
				if (CEXPR_CELL())
				{
					if (!GX_CELL_IS_EMPTYVALUE(cp))
						count++;
				}
			break;
#endif
		case GX_OP_ERROR:
			_gx_propagate_error(argv);
		default:
			_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
		}
	op.type = GX_NUMBER;
	op.val.number = (double) count;
	return op;
}
