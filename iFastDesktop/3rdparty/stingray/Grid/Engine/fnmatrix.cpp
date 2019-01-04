///////////////////////////////////////////////////////////////////////////////
// fnmatric.cpp: Matrix worksheet functions
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
#pragma warning (disable: 4701)
#pragma warning (disable: 4389) // Signed/Unsigned Mismatch

#define CELLRANGE

void __cdecl _gx_dump_matrix(gxMatrix m);

#define     ROW_VEC     1
#define     COL_VEC     2

#pragma warning(disable:4018)

#ifdef CELLRANGE
int __cdecl _gx_analyze_ranges(gxRange * rp1, gxRange * rp2)
{
	int rdim1,
		rdim2,
		cdim1,
		cdim2;

	rdim1 = rp1->r1 - rp1->r0;
	rdim2 = rp2->r1 - rp2->r0;
	cdim1 = rp1->c1 - rp1->c0;
	cdim2 = rp2->c1 - rp2->c0;
	if (rdim1 == 0 && rdim2 == 0 && cdim1 == cdim2)
		return ROW_VEC;
	if (cdim1 == 0 && cdim2 == 0 && rdim1 == rdim2)
		return COL_VEC;
	return 0;
}

static void check_size(gxMatrix * m)
{  /* for protection against huge ranges */
	unsigned dim = m->r_dim * m->c_dim;

	if (dim > _gx_cell_count(_gx_get_expr_si(), GX_CONSTANT_LIST | GX_RECALC_LIST))
		_gx_function_error(GX_FN_ERR_NON_NUM_IN_MTRX);
}

static void check_range_size(gxRange * rng)
{  /* for protection against huge ranges */
	unsigned dim = (rng->r1 + 1 - rng->r0) * (rng->c1 + 1 - rng->c0);

	if (dim > _gx_cell_count(_gx_get_expr_si(), GX_CONSTANT_LIST | GX_RECALC_LIST))
		_gx_function_error(GX_FN_ERR_NON_NUM_IN_MTRX);
}

void __cdecl _gx_fill_matrix(gxMatrix m, gxRange * range)
{
	register unsigned r,
		c;
	int i,
		j;

	for (r = range->r0, i = 0; r <= range->r1; r++, i++)
		for (c = range->c0, j = 0; c <= range->c1; c++, j++)
			if (!_gx_fn_get_value(r, c, m.data + (i * m.c_dim + j)))
			{
				_gx_function_error(GX_FN_ERR_NON_NUM_IN_MTRX);
			}
}

void __cdecl _gx_fill_matrixT(gxMatrix m, gxRange * range)
{
	register unsigned r,
		c;
	int i,
		j;

	for (r = range->r0, i = 0; r <= range->r1; r++, i++)
		for (c = range->c0, j = 0; c <= range->c1; c++, j++)
			if (!_gx_fn_get_value(r, c, m.data + (j * m.c_dim + i)))
			{
				_gx_function_error(GX_FN_ERR_NON_NUM_IN_MTRX);
			}
}

void __cdecl _gx_power_fill(gxMatrix m, gxRange * range)
{
	register unsigned r,
		c;
	int i,
		j;
	gxNumber x,
			 xn;

	c = range->c0;
	for (r = range->r0, i = 0; r <= range->r1; r++, i++)
	{
		if (!_gx_fn_get_value(r, c, &x))
		{
			_gx_function_error(GX_FN_ERR_NON_NUM_IN_VEC);
		}
		xn = x;
		GX_MVAL(m, i, m.c_dim - 1) = 1.0;
		GX_MVAL(m, i, m.c_dim - 2) = xn;
		for (j = m.c_dim - 3; j >= 0; --j)
		{
			xn *= x;
			GX_MVAL(m, i, j) = xn;
		}
	}
}

void __cdecl _gx_power_fillT(gxMatrix m, gxRange * range)
{
	register unsigned r,
		c;
	int i,
		j;
	gxNumber x,
			 xn;

	r = range->r0;
	for (c = range->c0, i = 0; c <= range->c1; c++, i++)
	{
		if (!_gx_fn_get_value(r, c, &x))
		{
			_gx_function_error(GX_FN_ERR_NON_NUM_IN_VEC);
		}
		xn = x;
		GX_MVAL(m, i, m.c_dim - 1) = 1.0;
		GX_MVAL(m, i, m.c_dim - 2) = xn;
		for (j = m.c_dim - 3; j >= 0; --j)
		{
			xn *= x;
			GX_MVAL(m, i, j) = xn;
		}
	}
}

extern void __cdecl _gx_preserve_raw(int si, gxCell * cp);
extern CGXStyle * __cdecl SafeDetachStyle(gxCell * cp);
extern void __cdecl AttachStyle(gxCell * cp, CGXStyle * pStyle);

/* highly dependent on structure of token buffers! */
void __cdecl _gx_dump_matrix(gxMatrix m)
{
	register gxCell *cp;
	register unsigned r,
		c;
	gxRange u_range;
	int undoable = 0;
	int si = _gx_get_expr_si();
	gxSheetContext *context = _gx_get_context_ptr(si);
	// gxCellProp cprop;
	unsigned expr_row,
		expr_col;
	gxExprNode ebuf[2];
	gxFormula fm;

	int mask = _gx_freeze_list_order(si, GX_ALL_LISTS);

	_gx_get_expr_rc(&expr_row, &expr_col);

	fm.expr_start = 0;
	fm.cons_start = GX_ENULL;
	fm.depend_start = 1;
	fm.expr_size = 2;
	fm.expression = ebuf;
	fm.comment = NULL;

	fm.expression[0].node_type = GX_NUMBER_NODE;
	fm.expression[0].value.operand = 0.0;
	fm.expression[0].has_parens = 0;
	fm.expression[0].number_is_hex = 0;
	fm.expression[0].right = GX_ENULL;
	fm.expression[0].left = GX_ENULL;

	fm.expression[1].node_type = GX_CELL_NODE;
	fm.expression[1].value.range.r0 = expr_row;
	fm.expression[1].value.range.r1 = expr_row;
	fm.expression[1].value.range.c0 = expr_col;
	fm.expression[1].value.range.c1 = expr_col;
	fm.expression[1].value.range.abs_r0 = 0;
	fm.expression[1].value.range.abs_r1 = 0;
	fm.expression[1].value.range.abs_c0 = 0;
	fm.expression[1].value.range.abs_c1 = 0;
	fm.expression[1].value.range.cell_only = 1;
	fm.expression[1].has_parens = 0;
	fm.expression[1].number_is_hex = 0;
	fm.expression[1].right = GX_ENULL;
	fm.expression[1].left = GX_ENULL;

//  undoable = context->do_preserve && get_undo_type(si) == UNDO_EDIT;
	undoable = context->do_preserve; 

	if (undoable)
	{   /* set up for undo */
		u_range.r0 = expr_row;
		u_range.c0 = expr_col;
		u_range.r1 = u_range.r0 + m.r_dim - 1;
		u_range.c1 = u_range.c0 + m.c_dim - 1;
        context->undo_dst = u_range;
		context->is_undo_init = 1;  // mark that there is undo info
	}

	CGXStyle* pStyle;
	for (r = 0; r < m.r_dim; r++)
		for (c = 0; c < m.c_dim; c++)
			if (!(r == 0 && c == 0))
			{
				pStyle = NULL;
				if ((cp = _gx_find_cell(si, r + expr_row, c + expr_col)) != NULL)
				{
					assert(cp->inserted);
					_gx_remove_cell(si, cp);
					if (undoable && (r > 0 || c > 0))
					{
						if (cp->pStyle)
							pStyle = cp->pStyle->Clone();
						_gx_preserve_raw(si, cp);
					}
					else
					{
						pStyle = SafeDetachStyle(cp);
						_gx_free_cell(cp);
					}
				}
				else if (undoable && (r > 0 || c > 0))
				{
					gxCell *newcell = _gx_new_cell(&context->empty_list);
					newcell->row = (gxRowCol) (r + expr_row);
					newcell->col = (gxRowCol) (c + expr_col);
					_gx_preserve_raw(si, newcell);
				}

				cp = _gx_new_cell(&context->recalc_list);
				cp->row = (gxRowCol) (r + expr_row);
				cp->col = (gxRowCol) (c + expr_col);
				cp->cell_type = GX_FORMULA_CELL;
				cp->value_type = GX_VALUE_NUMERIC;
				cp->value.number = fm.expression[0].value.operand =
					m.data[r * m.c_dim + c];
				cp->formula = _gx_formula_dup(&fm);
				AttachStyle(cp, pStyle);
				GX_CELL_SET_FLAGS(cp, GX_VISITED | GX_UPDATED);
				cp->serial = context->serial;
				_gx_insert_cell(si, cp);
			}

	_gx_unfreeze_list_order(si, mask);
}
#endif

gxOperand __cdecl _gx_fn_mmul(gxOperand argv[])
{
#ifdef CELLRANGE
	gxMatrix a,
			 b,
			 result;
	gxOperand op;

	if (argv->val.count != 2)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	GX_HANDLE_OP_ERROR(argv[1]);
	GX_HANDLE_OP_ERROR(argv[2]);
	if (argv[1].type != GX_RANGE || argv[2].type != GX_RANGE)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	a.r_dim = argv[1].val.range.r1 - argv[1].val.range.r0 + 1;
	a.c_dim = argv[1].val.range.c1 - argv[1].val.range.c0 + 1;
	b.r_dim = argv[2].val.range.r1 - argv[2].val.range.r0 + 1;
	b.c_dim = argv[2].val.range.c1 - argv[2].val.range.c0 + 1;
	if (a.c_dim != b.r_dim)
		_gx_function_error(GX_FN_ERR_MATRIX_DIMS);
	check_size(&a);
	check_size(&b);
	_gx_mkwm(&a);
	_gx_mkwm(&b);
	_gx_fill_matrix(a, &(argv[1].val.range));
	_gx_fill_matrix(b, &(argv[2].val.range));
	result = _gx_mmul(a, b);
	_gx_dump_matrix(result);
	op.type = GX_NUMBER;
	op.val.number = result.data[0];
	_gx_cleanwm();
	return op;
#else
	gxOperand op;
	op.type = GX_NUMBER;
	_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	return op;
#endif
}

gxOperand __cdecl _gx_fn_transpose(gxOperand argv[])
{
#ifdef CELLRANGE
	gxMatrix a,
			 result;
	gxOperand op;

	if (argv->val.count != 1)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	GX_HANDLE_OP_ERROR(argv[1]);
	if (argv[1].type != GX_RANGE)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	a.r_dim = argv[1].val.range.r1 - argv[1].val.range.r0 + 1;
	a.c_dim = argv[1].val.range.c1 - argv[1].val.range.c0 + 1;
	check_size(&a);
	_gx_mkwm(&a);
	_gx_fill_matrix(a, &(argv[1].val.range));
	result = _gx_mtranspose(a);
	_gx_dump_matrix(result);
	op.type = GX_NUMBER;
	op.val.number = result.data[0];
	_gx_cleanwm();
	return op;
#else
	gxOperand op;
	op.type = GX_NUMBER;
	_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	return op;
#endif
}

gxOperand __cdecl _gx_fn_invert(gxOperand argv[])
{
#ifdef CELLRANGE
	gxMatrix a,
			 result;
	gxOperand op;

	if (argv->val.count != 1)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	GX_HANDLE_OP_ERROR(argv[1]);
	if (argv[1].type != GX_RANGE)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	a.r_dim = argv[1].val.range.r1 - argv[1].val.range.r0 + 1;
	a.c_dim = argv[1].val.range.c1 - argv[1].val.range.c0 + 1;
	if (a.r_dim != a.c_dim)
		_gx_function_error(GX_FN_ERR_SQUARE);
	check_size(&a);
	_gx_mkwm(&a);
	_gx_fill_matrix(a, &(argv[1].val.range));
	result = _gx_minvert(a);
	if (result.r_dim == 0)
		_gx_function_error(GX_FN_ERR_SING);
	_gx_dump_matrix(result);
	op.type = GX_NUMBER;
	op.val.number = result.data[0];
	_gx_cleanwm();
	return op;
#else
	gxOperand op;
	op.type = GX_NUMBER;
	_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	return op;
#endif
}

gxOperand __cdecl _gx_fn_eigen(gxOperand argv[])
{
#ifdef CELLRANGE
	gxMatrix a,
			 result;
	gxOperand op;

	if (argv->val.count != 1)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	GX_HANDLE_OP_ERROR(argv[1]);
	if (argv[1].type != GX_RANGE)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	a.r_dim = argv[1].val.range.r1 - argv[1].val.range.r0 + 1;
	a.c_dim = argv[1].val.range.c1 - argv[1].val.range.c0 + 1;
	if (a.r_dim != a.c_dim)
		_gx_function_error(GX_FN_ERR_SQUARE);
	check_size(&a);
	_gx_mkwm(&a);
	_gx_fill_matrix(a, &(argv[1].val.range));
	if (_gx_asymmetric(a))
		_gx_function_error(GX_FN_ERR_SYMMETRY);
	result = _gx_meigen(a);
	_gx_dump_matrix(result);
	op.type = GX_NUMBER;
	op.val.number = result.data[0];
	_gx_cleanwm();
	return op;
#else
	gxOperand op;
	op.type = GX_NUMBER;
	_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	return op;
#endif
}

gxOperand __cdecl _gx_fn_det(gxOperand argv[])
{
#ifdef CELLRANGE
	gxMatrix a;
	gxOperand op;

	if (argv->val.count != 1)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	GX_HANDLE_OP_ERROR(argv[1]);
	if (argv[1].type != GX_RANGE)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	a.r_dim = argv[1].val.range.r1 - argv[1].val.range.r0 + 1;
	a.c_dim = argv[1].val.range.c1 - argv[1].val.range.c0 + 1;
	if (a.r_dim != a.c_dim)
		_gx_function_error(GX_FN_ERR_SQUARE);
	check_size(&a);
	_gx_mkwm(&a);
	_gx_fill_matrix(a, &(argv[1].val.range));
	op.type = GX_NUMBER;
	op.val.number = _gx_mdet(a);
	_gx_cleanwm();
	return op;
#else
	gxOperand op;
	op.type = GX_NUMBER;
	_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	return op;
#endif
}

gxOperand __cdecl _gx_fn_lls(gxOperand argv[])
{
#ifdef CELLRANGE
	gxMatrix a,
			 b,
			 result;
	int status;
	gxOperand op;

	if (argv->val.count != 2)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	GX_HANDLE_OP_ERROR(argv[1]);
	GX_HANDLE_OP_ERROR(argv[2]);
	if (argv[1].type != GX_RANGE || argv[2].type != GX_RANGE)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	a.r_dim = argv[1].val.range.r1 - argv[1].val.range.r0 + 1;
	a.c_dim = argv[1].val.range.c1 - argv[1].val.range.c0 + 1;
	b.r_dim = argv[2].val.range.r1 - argv[2].val.range.r0 + 1;
	b.c_dim = argv[2].val.range.c1 - argv[2].val.range.c0 + 1;
	if (a.r_dim != b.r_dim || b.c_dim != 1 || a.r_dim <= a.c_dim)
		_gx_function_error(GX_FN_ERR_IMPROP_DIM);
	check_size(&a);
	check_size(&b);
	_gx_mkwm(&a);
	_gx_mkwm(&b);
	_gx_fill_matrix(a, &(argv[1].val.range));
	_gx_fill_matrix(b, &(argv[2].val.range));
	status = _gx_mlls(a, b, &result);
	if (status)
		_gx_function_error(GX_FN_ERR_LIN_DEP);
	_gx_dump_matrix(result);
	op.type = GX_NUMBER;
	op.val.number = result.data[0];
	_gx_cleanwm();
	return op;
#else
	gxOperand op;
	op.type = GX_NUMBER;
	_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	return op;
#endif
}

gxOperand __cdecl _gx_fn_pls(gxOperand argv[])
{
#ifdef CELLRANGE
	gxMatrix a,
			 b,
			 result;
	int status,
		degree,
		v_type;
	gxOperand op;

	if (argv->val.count != 3)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	GX_HANDLE_OP_ERROR(argv[1]);
	GX_HANDLE_OP_ERROR(argv[2]);
	_gx_cvt2constant(argv + 3);
	if (argv[1].type != GX_RANGE || argv[2].type != GX_RANGE ||
		argv[3].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	v_type = _gx_analyze_ranges(&(argv[1].val.range), &(argv[2].val.range));
	if (v_type == 0)
		_gx_function_error(GX_FN_ERR_IMPROP_DIM);
	if (argv[3].val.number < 1.0 || argv[3].val.number > 10.0)
		_gx_function_error(GX_FN_ERR_DEGREE_1_10);
	degree = (int) argv[3].val.number;
	switch (v_type)
	{
	case ROW_VEC:
		a.r_dim = argv[1].val.range.c1 - argv[1].val.range.c0 + 1;
		a.c_dim = degree + 1;
		b.r_dim = argv[2].val.range.c1 - argv[2].val.range.c0 + 1;
		b.c_dim = argv[2].val.range.r1 - argv[2].val.range.r0 + 1;
		break;
	case COL_VEC:
		a.r_dim = argv[1].val.range.r1 - argv[1].val.range.r0 + 1;
		a.c_dim = degree + 1;
		b.r_dim = argv[2].val.range.r1 - argv[2].val.range.r0 + 1;
		b.c_dim = argv[2].val.range.c1 - argv[2].val.range.c0 + 1;
		break;
	}
	if (a.r_dim <= a.c_dim)
		_gx_function_error(GX_FN_ERR_DS_GE_DP2);
	check_range_size(&argv[1].val.range);
	check_size(&b);
	_gx_mkwm(&a);
	_gx_mkwm(&b);
	switch (v_type)
	{
	case ROW_VEC:
		_gx_power_fillT(a, &(argv[1].val.range));
		_gx_fill_matrixT(b, &(argv[2].val.range));
		break;
	case COL_VEC:
		_gx_power_fill(a, &(argv[1].val.range));
		_gx_fill_matrix(b, &(argv[2].val.range));
		break;
	}
	status = _gx_mlls(a, b, &result);
	if (status)
		_gx_function_error(GX_FN_ERR_LIN_DEP);
	_gx_dump_matrix(result);
	op.type = GX_NUMBER;
	op.val.number = result.data[0];
	_gx_cleanwm();
	return op;
#else
	gxOperand op;
	op.type = GX_NUMBER;
	_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	return op;
#endif
}

gxOperand __cdecl _gx_fn_polyfit(gxOperand argv[])
{
#ifdef CELLRANGE
	gxMatrix a,
			 b,
			 x,
			 y;
	int status,
		degree,
		v_type;
	gxOperand op;

	if (argv->val.count != 3)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	GX_HANDLE_OP_ERROR(argv[1]);
	GX_HANDLE_OP_ERROR(argv[2]);
	_gx_cvt2constant(argv + 3);
	if (argv[1].type != GX_RANGE || argv[2].type != GX_RANGE ||
		argv[3].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	v_type = _gx_analyze_ranges(&(argv[1].val.range), &(argv[2].val.range));
	if (v_type == 0)
		_gx_function_error(GX_FN_ERR_IMPROP_DIM);
	if (argv[3].val.number < 1.0 || argv[3].val.number > 10.0)
		_gx_function_error(GX_FN_ERR_DEGREE_1_10);
	degree = (int) argv[3].val.number;
	switch (v_type)
	{
	case ROW_VEC:
		a.r_dim = argv[1].val.range.c1 + 1 - argv[1].val.range.c0;
		a.c_dim = degree + 1;
		b.r_dim = argv[2].val.range.c1 + 1 - argv[2].val.range.c0;
		b.c_dim = argv[2].val.range.r1 + 1 - argv[2].val.range.r0;
		break;
	case COL_VEC:
		a.r_dim = argv[1].val.range.r1 + 1 - argv[1].val.range.r0;
		a.c_dim = degree + 1;
		b.r_dim = argv[2].val.range.r1 + 1 - argv[2].val.range.r0;
		b.c_dim = argv[2].val.range.c1 + 1 - argv[2].val.range.c0;
		break;
	}
	if (a.r_dim <= a.c_dim)
		_gx_function_error(GX_FN_ERR_DS_GE_DP2);
	check_range_size(&argv[1].val.range);
	check_size(&b);
	_gx_mkwm(&a);
	_gx_mkwm(&b);
	switch (v_type)
	{
	case ROW_VEC:
		_gx_power_fillT(a, &(argv[1].val.range));
		_gx_fill_matrixT(b, &(argv[2].val.range));
		break;
	case COL_VEC:
		_gx_power_fill(a, &(argv[1].val.range));
		_gx_fill_matrix(b, &(argv[2].val.range));
		break;
	}
	status = _gx_mlls_short(a, b, &x);
	if (status)
		_gx_function_error(GX_FN_ERR_LIN_DEP);
	y = _gx_mmul(a, x);
	if (v_type == COL_VEC)
	{
		_gx_dump_matrix(y);
	}
	else
	{
		_gx_freewm(&a);
		a = _gx_mtranspose(y);
		_gx_dump_matrix(a);
	}
	op.type = GX_NUMBER;
	op.val.number = y.data[0];
	_gx_cleanwm();
	return op;
#else
	gxOperand op;
	op.type = GX_NUMBER;
	_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	return op;
#endif
}

gxOperand __cdecl _gx_fn_linfit(gxOperand argv[])
{
#ifdef CELLRANGE
	gxMatrix a,
			 b,
			 x,
			 y;
	int status,
		degree,
		v_type;
	gxOperand op;

	if (argv->val.count != 2)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	GX_HANDLE_OP_ERROR(argv[1]);
	GX_HANDLE_OP_ERROR(argv[2]);
	if (argv[1].type != GX_RANGE || argv[2].type != GX_RANGE)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	v_type = _gx_analyze_ranges(&(argv[1].val.range), &(argv[2].val.range));
	if (v_type == 0)
		_gx_function_error(GX_FN_ERR_IMPROP_DIM);
	degree = 1;
	switch (v_type)
	{
	case ROW_VEC:
		a.r_dim = argv[1].val.range.c1 - argv[1].val.range.c0 + 1;
		a.c_dim = degree + 1;
		b.r_dim = argv[2].val.range.c1 - argv[2].val.range.c0 + 1;
		b.c_dim = argv[2].val.range.r1 - argv[2].val.range.r0 + 1;
		break;
	case COL_VEC:
		a.r_dim = argv[1].val.range.r1 - argv[1].val.range.r0 + 1;
		a.c_dim = degree + 1;
		b.r_dim = argv[2].val.range.r1 - argv[2].val.range.r0 + 1;
		b.c_dim = argv[2].val.range.c1 - argv[2].val.range.c0 + 1;
		break;
	}
	if (a.r_dim < 3)
		_gx_function_error(GX_FN_ERR_DS_GE_3);
	check_range_size(&argv[1].val.range);
	check_size(&b);
	_gx_mkwm(&a);
	_gx_mkwm(&b);
	switch (v_type)
	{
	case ROW_VEC:
		_gx_power_fillT(a, &(argv[1].val.range));
		_gx_fill_matrixT(b, &(argv[2].val.range));
		break;
	case COL_VEC:
		_gx_power_fill(a, &(argv[1].val.range));
		_gx_fill_matrix(b, &(argv[2].val.range));
		break;
	}
	status = _gx_mlls_short(a, b, &x);
	if (status)
		_gx_function_error(GX_FN_ERR_LIN_DEP);
	y = _gx_mmul(a, x);
	if (v_type == COL_VEC)
	{
		_gx_dump_matrix(y);
	}
	else
	{
		_gx_freewm(&a);
		a = _gx_mtranspose(y);
		_gx_dump_matrix(a);
	}
	op.type = GX_NUMBER;
	op.val.number = y.data[0];
	_gx_cleanwm();
	return op;
#else
	gxOperand op;
	op.type = GX_NUMBER;
	_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	return op;
#endif
}

gxOperand __cdecl _gx_fn_polycoef(gxOperand argv[])
{
#ifdef CELLRANGE
	gxMatrix a,
			 b,
			 x;
	int status,
		degree,
		v_type;
	gxOperand op;

	if (argv->val.count != 3)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	GX_HANDLE_OP_ERROR(argv[1]);
	GX_HANDLE_OP_ERROR(argv[2]);
	_gx_cvt2constant(argv + 3);
	if (argv[1].type != GX_RANGE || argv[2].type != GX_RANGE ||
		argv[3].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	v_type = _gx_analyze_ranges(&(argv[1].val.range), &(argv[2].val.range));
	if (v_type == 0)
		_gx_function_error(GX_FN_ERR_IMPROP_DIM);
	if (argv[3].val.number < 1.0 || argv[3].val.number > 10.0)
		_gx_function_error(GX_FN_ERR_DEGREE_1_10);
	degree = (int) argv[3].val.number;
	switch (v_type)
	{
	case ROW_VEC:
		a.r_dim = argv[1].val.range.c1 - argv[1].val.range.c0 + 1;
		a.c_dim = degree + 1;
		b.r_dim = argv[2].val.range.c1 - argv[2].val.range.c0 + 1;
		b.c_dim = argv[2].val.range.r1 - argv[2].val.range.r0 + 1;
		break;
	case COL_VEC:
		a.r_dim = argv[1].val.range.r1 - argv[1].val.range.r0 + 1;
		a.c_dim = degree + 1;
		b.r_dim = argv[2].val.range.r1 - argv[2].val.range.r0 + 1;
		b.c_dim = argv[2].val.range.c1 - argv[2].val.range.c0 + 1;
		break;
	}
	if (a.r_dim <= a.c_dim)
		_gx_function_error(GX_FN_ERR_DS_GE_DP2);
	check_range_size(&argv[1].val.range);
	check_size(&b);
	_gx_mkwm(&a);
	_gx_mkwm(&b);
	switch (v_type)
	{
	case ROW_VEC:
		_gx_power_fillT(a, &(argv[1].val.range));
		_gx_fill_matrixT(b, &(argv[2].val.range));
		break;
	case COL_VEC:
		_gx_power_fill(a, &(argv[1].val.range));
		_gx_fill_matrix(b, &(argv[2].val.range));
		break;
	}
	status = _gx_mlls_short(a, b, &x);
	if (status)
		_gx_function_error(GX_FN_ERR_LIN_DEP);
	if (v_type == COL_VEC)
	{
		_gx_dump_matrix(x);
	}
	else
	{
		_gx_freewm(&a);
		a = _gx_mtranspose(x);
		_gx_dump_matrix(a);
	}
	op.type = GX_NUMBER;
	op.val.number = x.data[0];
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
gxMatrix __cdecl _gx_lincoef(gxOperand argv[], int v_type)
{
	gxMatrix a,
			 b,
			 x;
	int status,
		degree;

	degree = 1;
	switch (v_type)
	{
	case ROW_VEC:
		a.r_dim = argv[1].val.range.c1 - argv[1].val.range.c0 + 1;
		a.c_dim = degree + 1;
		b.r_dim = argv[2].val.range.c1 - argv[2].val.range.c0 + 1;
		b.c_dim = argv[2].val.range.r1 - argv[2].val.range.r0 + 1;
		break;
	case COL_VEC:
		a.r_dim = argv[1].val.range.r1 - argv[1].val.range.r0 + 1;
		a.c_dim = degree + 1;
		b.r_dim = argv[2].val.range.r1 - argv[2].val.range.r0 + 1;
		b.c_dim = argv[2].val.range.c1 - argv[2].val.range.c0 + 1;
		break;
	}
	if (a.r_dim < 3)
		_gx_function_error(GX_FN_ERR_DS_GE_3);
	check_range_size(&argv[1].val.range);
	check_size(&b);
	_gx_mkwm(&a);
	_gx_mkwm(&b);
	switch (v_type)
	{
	case ROW_VEC:
		_gx_power_fillT(a, &(argv[1].val.range));
		_gx_fill_matrixT(b, &(argv[2].val.range));
		break;
	case COL_VEC:
		_gx_power_fill(a, &(argv[1].val.range));
		_gx_fill_matrix(b, &(argv[2].val.range));
		break;
	}
	status = _gx_mlls_short(a, b, &x);
	_gx_freewm(&a);
	_gx_freewm(&b);
	if (status)
		_gx_function_error(GX_FN_ERR_LIN_DEP);
	if (v_type == COL_VEC)
		return x;
	else
	{
/*    _gx_freewm(&a);  */
		a = _gx_mtranspose(x);
		return a;
	}
}
#endif

gxOperand __cdecl _gx_fn_lincoef(gxOperand argv[])
{
#ifdef CELLRANGE
	gxOperand op;
	gxMatrix x;
	int v_type;

	if (argv->val.count != 2)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	GX_HANDLE_OP_ERROR(argv[1]);
	GX_HANDLE_OP_ERROR(argv[2]);
	if (argv[1].type != GX_RANGE || argv[2].type != GX_RANGE)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	v_type = _gx_analyze_ranges(&(argv[1].val.range), &(argv[2].val.range));
	if (v_type == 0)
		_gx_function_error(GX_FN_ERR_IMPROP_DIM);
	x = _gx_lincoef(argv, v_type);
	_gx_dump_matrix(x);
	op.type = GX_NUMBER;
	op.val.number = x.data[0];
	_gx_cleanwm();
	return op;
#else
	gxOperand op;
	op.type = GX_NUMBER;
	_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	return op;
#endif
}

gxOperand __cdecl _gx_fn_fft(gxOperand argv[])
{
#ifdef CELLRANGE
	gxMatrix a,
			 b;
	gxOperand op;
	long i,
		n;
	unsigned r,
		c,
		r_dim,
		c_dim;

	if (argv->val.count != 1)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	GX_HANDLE_OP_ERROR(argv[1]);
	if (argv[1].type != GX_RANGE)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	r_dim = argv[1].val.range.r1 - argv[1].val.range.r0 + 1;
	c_dim = argv[1].val.range.c1 - argv[1].val.range.c0 + 1;
	if (c_dim < r_dim)
	{
		for (n = 1; n < r_dim; n <<= 1);    /* find power of 2 >= r_dim */
		if (n != r_dim)
			_gx_function_error(GX_FN_ERR_DIM_POW_2);
		a.r_dim = n;
		a.c_dim = 2;
		check_size(&a);
		_gx_mkwm(&a);
		switch (c_dim)
		{
		case 1: /* real data */
			c = argv[1].val.range.c0;
			for (r = argv[1].val.range.r0, i = 0;
				 r <= argv[1].val.range.r1; r++, i += 2)
			{
				if (!_gx_fn_get_value(r, c, a.data + i))
					_gx_function_error(GX_FN_ERR_NON_NUM_IN_MTRX);
				a.data[i + 1] = 0.0;
			}
			break;
		case 2: /* complex data */
			c = argv[1].val.range.c0;
			for (r = argv[1].val.range.r0, i = 0;
				 r <= argv[1].val.range.r1; r++, i += 2)
			{
				if (!_gx_fn_get_value(r, c, a.data + i) ||
					!_gx_fn_get_value(r, c + 1, a.data + (i + 1)))
					_gx_function_error(GX_FN_ERR_NON_NUM_IN_MTRX);
			}
			break;
		default:
			_gx_function_error(GX_FN_ERR_IMPROP_DIM);
		}
		_gx_fft(a, 1);
		_gx_dump_matrix(a);
	}
	else
	{
		for (n = 1; n < c_dim; n <<= 1);    /* find power of 2 >= c_dim */
		if (n != c_dim)
			_gx_function_error(GX_FN_ERR_DIM_POW_2);
		a.r_dim = n;
		a.c_dim = 2;
		check_size(&a);
		_gx_mkwm(&a);
		switch (r_dim)
		{
		case 1: /* real data */
			r = argv[1].val.range.r0;
			for (c = argv[1].val.range.c0, i = 0;
				 c <= argv[1].val.range.c1; c++, i += 2)
			{
				if (!_gx_fn_get_value(r, c, a.data + i))
					_gx_function_error(GX_FN_ERR_NON_NUM_IN_MTRX);
				a.data[i + 1] = 0.0;
			}
			break;
		case 2: /* complex data */
			r = argv[1].val.range.r0;
			for (c = argv[1].val.range.c0, i = 0;
				 c <= argv[1].val.range.c1; c++, i += 2)
			{
				if (!_gx_fn_get_value(r, c, a.data + i) ||
					!_gx_fn_get_value(r + 1, c, a.data + (i + 1)))
					_gx_function_error(GX_FN_ERR_NON_NUM_IN_MTRX);
			}
			break;
		default:
			_gx_function_error(GX_FN_ERR_IMPROP_DIM);
		}
		_gx_fft(a, 1);
		b = _gx_mtranspose(a);
		_gx_dump_matrix(b);
	}
	op.type = GX_NUMBER;
	op.val.number = a.data[0];
	_gx_cleanwm();
	return op;
#else
	gxOperand op;
	op.type = GX_NUMBER;
	_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	return op;
#endif
}

gxOperand __cdecl _gx_fn_invfft(gxOperand argv[])
{
#ifdef CELLRANGE
	gxMatrix a,
			 b;
	gxOperand op;
	unsigned 
		r,
		c,
		r_dim,
		c_dim;
	long i,
		n;

	if (argv->val.count != 1)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	GX_HANDLE_OP_ERROR(argv[1]);
	if (argv[1].type != GX_RANGE)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	r_dim = argv[1].val.range.r1 - argv[1].val.range.r0 + 1;
	c_dim = argv[1].val.range.c1 - argv[1].val.range.c0 + 1;
	if (c_dim < r_dim)
	{
		for (n = 1; n < r_dim; n <<= 1);    /* find power of 2 >= r_dim */
		if (n != r_dim)
			_gx_function_error(GX_FN_ERR_DIM_POW_2);
		a.r_dim = n;
		a.c_dim = 2;
		check_size(&a);
		_gx_mkwm(&a);
		switch (c_dim)
		{
		case 1: /* real data */
			c = argv[1].val.range.c0;
			for (r = argv[1].val.range.r0, i = 0;
				 r <= argv[1].val.range.r1; r++, i += 2)
			{
				if (!_gx_fn_get_value(r, c, a.data + i))
					_gx_function_error(GX_FN_ERR_NON_NUM_IN_MTRX);
				a.data[i + 1] = 0.0;
			}
			break;
		case 2: /* complex data */
			c = argv[1].val.range.c0;
			for (r = argv[1].val.range.r0, i = 0;
				 r <= argv[1].val.range.r1; r++, i += 2)
			{
				if (!_gx_fn_get_value(r, c, a.data + i) ||
					!_gx_fn_get_value(r, c + 1, a.data + (i + 1)))
					_gx_function_error(GX_FN_ERR_NON_NUM_IN_MTRX);
			}
			break;
		default:
			_gx_function_error(GX_FN_ERR_IMPROP_DIM);
		}
		_gx_fft(a, -1);
		_gx_dump_matrix(a);
	}
	else
	{
		for (n = 1; n < c_dim; n <<= 1);    /* find power of 2 >= c_dim */
		if (n != c_dim)
			_gx_function_error(GX_FN_ERR_DIM_POW_2);
		a.r_dim = n;
		a.c_dim = 2;
		check_size(&a);
		_gx_mkwm(&a);
		switch (r_dim)
		{
		case 1: /* real data */
			r = argv[1].val.range.r0;
			for (c = argv[1].val.range.c0, i = 0;
				 c <= argv[1].val.range.c1; c++, i += 2)
			{
				if (!_gx_fn_get_value(r, c, a.data + i))
					_gx_function_error(GX_FN_ERR_NON_NUM_IN_MTRX);
				a.data[i + 1] = 0.0;
			}
			break;
		case 2: /* complex data */
			r = argv[1].val.range.r0;
			for (c = argv[1].val.range.c0, i = 0;
				 c <= argv[1].val.range.c1; c++, i += 2)
			{
				if (!_gx_fn_get_value(r, c, a.data + i) ||
					!_gx_fn_get_value(r + 1, c, a.data + (i + 1)))
					_gx_function_error(GX_FN_ERR_NON_NUM_IN_MTRX);
			}
			break;
		default:
			_gx_function_error(GX_FN_ERR_IMPROP_DIM);
		}
		_gx_fft(a, -1);
		b = _gx_mtranspose(a);
		_gx_dump_matrix(b);
	}
	op.type = GX_NUMBER;
	op.val.number = a.data[0];
	_gx_cleanwm();
	return op;
#else
	gxOperand op;
	op.type = GX_NUMBER;
	_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	return op;
#endif
}

gxOperand __cdecl _gx_fn_dft(gxOperand argv[])
{
#ifdef CELLRANGE
	gxMatrix a,
			 b,
			 result;
	gxOperand op;
	long 
		r,
		c,
		r_dim,
		c_dim;
	unsigned i,
		n;
	int fft_flag = 0;

	if (argv->val.count != 1)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	GX_HANDLE_OP_ERROR(argv[1]);
	if (argv[1].type != GX_RANGE)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	r_dim = argv[1].val.range.r1 - argv[1].val.range.r0 + 1;
	c_dim = argv[1].val.range.c1 - argv[1].val.range.c0 + 1;
	if (c_dim < r_dim)
	{
		for (n = 1; n < r_dim; n <<= 1);    /* find power of 2 >= r_dim */
		if (n == r_dim)
			fft_flag = 1;
		a.r_dim = r_dim;
		a.c_dim = 2;
		check_size(&a);
		_gx_mkwm(&a);
		switch (c_dim)
		{
		case 1: /* real data */
			c = argv[1].val.range.c0;
			for (r = argv[1].val.range.r0, i = 0;
				 r <= argv[1].val.range.r1; r++, i += 2)
			{
				if (!_gx_fn_get_value(r, c, a.data + i))
					_gx_function_error(GX_FN_ERR_NON_NUM_IN_MTRX);
				a.data[i + 1] = 0.0;
			}
			break;
		case 2: /* complex data */
			c = argv[1].val.range.c0;
			for (r = argv[1].val.range.r0, i = 0;
				 r <= argv[1].val.range.r1; r++, i += 2)
			{
				if (!_gx_fn_get_value(r, c, a.data + i) ||
					!_gx_fn_get_value(r, c + 1, a.data + (i + 1)))
					_gx_function_error(GX_FN_ERR_NON_NUM_IN_MTRX);
			}
			break;
		default:
			_gx_function_error(GX_FN_ERR_IMPROP_DIM);
		}
		if (fft_flag)
		{
			_gx_fft(a, 1);
			result = a;
			_gx_dump_matrix(result);
		}
		else
		{
			b = _gx_dft(a, 1);
			result = b;
			_gx_dump_matrix(result);
		}
	}
	else
	{
		for (n = 1; n < c_dim; n <<= 1);    /* find power of 2 >= c_dim */
		if (n == c_dim)
			fft_flag = 1;
		a.r_dim = c_dim;
		a.c_dim = 2;
		check_size(&a);
		_gx_mkwm(&a);
		switch (r_dim)
		{
		case 1: /* real data */
			r = argv[1].val.range.r0;
			for (c = argv[1].val.range.c0, i = 0;
				 c <= argv[1].val.range.c1; c++, i += 2)
			{
				if (!_gx_fn_get_value(r, c, a.data + i))
					_gx_function_error(GX_FN_ERR_NON_NUM_IN_MTRX);
				a.data[i + 1] = 0.0;
			}
			break;
		case 2: /* complex data */
			r = argv[1].val.range.r0;
			for (c = argv[1].val.range.c0, i = 0;
				 c <= argv[1].val.range.c1; c++, i += 2)
			{
				if (!_gx_fn_get_value(r, c, a.data + i) ||
					!_gx_fn_get_value(r + 1, c, a.data + (i + 1)))
					_gx_function_error(GX_FN_ERR_NON_NUM_IN_MTRX);
			}
			break;
		default:
			_gx_function_error(GX_FN_ERR_IMPROP_DIM);
		}
		if (fft_flag)
		{
			_gx_fft(a, 1);
			b = _gx_mtranspose(a);
			result = b;
			_gx_dump_matrix(result);
		}
		else
		{
			b = _gx_dft(a, 1);
			_gx_freewm(&a);
			a = _gx_mtranspose(b);
			result = a;
			_gx_dump_matrix(result);
		}
	}
	op.type = GX_NUMBER;
	op.val.number = result.data[0];
	_gx_cleanwm();
	return op;
#else
	gxOperand op;
	op.type = GX_NUMBER;
	_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	return op;
#endif
}

gxOperand __cdecl _gx_fn_invdft(gxOperand argv[])
{
#ifdef CELLRANGE
	gxMatrix a,
			 b,
			 result;
	gxOperand op;
	unsigned 
		r,
		c,
		r_dim,
		c_dim;
	long i,
		n;
	int fft_flag = 0;

	if (argv->val.count != 1)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	GX_HANDLE_OP_ERROR(argv[1]);
	if (argv[1].type != GX_RANGE)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	r_dim = argv[1].val.range.r1 - argv[1].val.range.r0 + 1;
	c_dim = argv[1].val.range.c1 - argv[1].val.range.c0 + 1;
	if (c_dim < r_dim)
	{
		for (n = 1; n < r_dim; n <<= 1);    /* find power of 2 >= r_dim */
		if (n == r_dim)
			fft_flag = 1;
		a.r_dim = r_dim;
		a.c_dim = 2;
		check_size(&a);
		_gx_mkwm(&a);
		switch (c_dim)
		{
		case 1: /* real data */
			c = argv[1].val.range.c0;
			for (r = argv[1].val.range.r0, i = 0;
				 r <= argv[1].val.range.r1; r++, i += 2)
			{
				if (!_gx_fn_get_value(r, c, a.data + i))
					_gx_function_error(GX_FN_ERR_NON_NUM_IN_MTRX);
				a.data[i + 1] = 0.0;
			}
			break;
		case 2: /* complex data */
			c = argv[1].val.range.c0;
			for (r = argv[1].val.range.r0, i = 0;
				 r <= argv[1].val.range.r1; r++, i += 2)
			{
				if (!_gx_fn_get_value(r, c, a.data + i) ||
					!_gx_fn_get_value(r, c + 1, a.data + (i + 1)))
					_gx_function_error(GX_FN_ERR_NON_NUM_IN_MTRX);
			}
			break;
		default:
			_gx_function_error(GX_FN_ERR_IMPROP_DIM);
		}
		if (fft_flag)
		{
			_gx_fft(a, -1);
			result = a;
			_gx_dump_matrix(result);
		}
		else
		{
			b = _gx_dft(a, -1);
			result = b;
			_gx_dump_matrix(result);
		}
	}
	else
	{
		for (n = 1; n < c_dim; n <<= 1);    /* find power of 2 >= c_dim */
		if (n == c_dim)
			fft_flag = 1;
		a.r_dim = c_dim;
		a.c_dim = 2;
		check_size(&a);
		_gx_mkwm(&a);
		switch (r_dim)
		{
		case 1: /* real data */
			r = argv[1].val.range.r0;
			for (c = argv[1].val.range.c0, i = 0;
				 c <= argv[1].val.range.c1; c++, i += 2)
			{
				if (!_gx_fn_get_value(r, c, a.data + i))
					_gx_function_error(GX_FN_ERR_NON_NUM_IN_MTRX);
				a.data[i + 1] = 0.0;
			}
			break;
		case 2: /* complex data */
			r = argv[1].val.range.r0;
			for (c = argv[1].val.range.c0, i = 0;
				 c <= argv[1].val.range.c1; c++, i += 2)
			{
				if (!_gx_fn_get_value(r, c, a.data + i) ||
					!_gx_fn_get_value(r + 1, c, a.data + (i + 1)))
					_gx_function_error(GX_FN_ERR_NON_NUM_IN_MTRX);
			}
			break;
		default:
			_gx_function_error(GX_FN_ERR_IMPROP_DIM);
		}
		if (fft_flag)
		{
			_gx_fft(a, -1);
			b = _gx_mtranspose(a);
			result = b;
			_gx_dump_matrix(result);
		}
		else
		{
			b = _gx_dft(a, -1);
			_gx_freewm(&a);
			a = _gx_mtranspose(b);
			result = a;
			_gx_dump_matrix(result);
		}
	}
	op.type = GX_NUMBER;
	op.val.number = result.data[0];
	_gx_cleanwm();
	return op;
#else
	gxOperand op;
	op.type = GX_NUMBER;
	_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	return op;
#endif
}

#pragma warning (pop)
