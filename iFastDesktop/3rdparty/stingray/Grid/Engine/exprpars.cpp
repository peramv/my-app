///////////////////////////////////////////////////////////////////////////////
// exprpars.cpp: Parsing routines
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
#include "exprscan.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

#pragma warning(disable:4100) // get rid off "unreferenced formal parameter" warning

/*---------------------------------------------------------------------------*/
/*  Private parsing structures and functions.                    */

typedef struct
{
	int error_flag;
	int error_reason;
	TokType error_expected;
	TokType error_found;
	int error_position;
}      ParseStatus;

typedef struct
{
	gxExprNode nbuf[GX_MAX_NODES];  /* Expression node buffer   */
	gxExprPointer nbuf_ptr;
	gxSToken ctoken;    /* Current token        */
	gxSToken lookahead[2];  /* Holds lookahead      */
	int look_flag[2];   /* Has there been lookahead */
	gxExprPointer stack[GX_MAX_NODES];  /* Semantic stack       */
	int sp;
	ParseStatus status; /* Current status of parse  */
}      ParseState;


static void match(int, ParseState *, TokType);
static TokType lookahead(int si, ParseState * ps);
static int get_match_error(TokType desired);


/*---------------------------------------------------------------------------*/
/*  Non-terminal parsing functions.                      */

static void formula(int, ParseState *, gxFormula *);
static void opt_constraint(int, ParseState *, gxFormula *);
static void opt_dependency(int, ParseState *, gxFormula *);
static void cell_list(int si, ParseState * ps);
static void depend_range(int si, ParseState * ps);
static void opt_comment(int, ParseState *, gxFormula *);
static void expression(int, ParseState *);
static void conditional_expr(int si, ParseState * ps);
static void more_conditional(int si, ParseState * ps);
static void log_or_expr(int si, ParseState * ps);
static void more_log_or(int si, ParseState * ps);
static void log_and_expr(int si, ParseState * ps);
static void more_log_and(int si, ParseState * ps);
static void bit_or_expr(int si, ParseState * ps);
static void more_bit_or(int si, ParseState * ps);
static void bit_xor_expr(int si, ParseState * ps);
static void more_bit_xor(int si, ParseState * ps);
static void bit_and_expr(int si, ParseState * ps);
static void more_bit_and(int si, ParseState * ps);
static void equality_expr(int si, ParseState * ps);
static void more_equality(int si, ParseState * ps);
static void relational_expr(int si, ParseState * ps);
static void more_relational(int si, ParseState * ps);
static void shift_expr(int si, ParseState * ps);
static void more_shift(int si, ParseState * ps);
static void additive_expr(int si, ParseState * ps);
static void more_additive(int si, ParseState * ps);
static void multiplicative_expr(int si, ParseState * ps);
static void more_multiplicative(int si, ParseState * ps);
static void unary_expr(int si, ParseState * ps);
static void exponent_expr(int si, ParseState * ps);
static void more_exponent(int si, ParseState * ps);
static void percent_expr(int si, ParseState * ps);
static void primary(int si, ParseState * ps);
static void opt_range(int si, ParseState * ps);
static void range_rhs(int si, ParseState * ps);
static void possible_function(int si, ParseState * ps);
static void opt_arguments(int si, ParseState * ps);
static void opt_rel_cell(int si, ParseState * ps);
static void opt_rel_row(int si, ParseState * ps);
static void opt_rel_col(int si, ParseState * ps);
static void arg_list(int si, ParseState * ps);
static void more_args(int si, ParseState * ps);
static int is_primary(TokType tt);
static TokType lookahead(int si, ParseState * ps);
static TokType lookahead2(int si, ParseState * ps);


/*---------------------------------------------------------------------------*/
/*  Semantic actions.                                */

static void do_conditional(int, ParseState *);
static void push_operator(int, ParseState *, gxOpType);
static void do_binary(int, ParseState *);
static void do_unary(int, ParseState *);
static void do_percent(int, ParseState *);
static void push_cell(int, ParseState *);
static void push_name(int, ParseState *);
static void make_function(int, ParseState *);
static void resolve_name(int, ParseState *);
static void push_string(int, ParseState *);
static void push_number(int, ParseState *);
static void push_rel(int, ParseState *);
static void push_illegal(int, ParseState *);
static void add_parens(int, ParseState *);
static void make_rangen(int, ParseState *);
static void add_rel_row(int, ParseState *);
static void add_rel_col(int, ParseState *);

static void done_expr(int, ParseState *, gxFormula *);
static void done_constraint(int, ParseState *, gxFormula *);
static void add_dependency(int, ParseState *);
static void start_dependency(int, ParseState *);
static void done_dependency(int, ParseState *, gxFormula *);
static void done_comment(int, ParseState *, gxFormula *);

static void cleanup_function(int si, ParseState * ps);


/*---------------------------------------------------------------------------*/
/*  External (and only) interface to the expression parser.          */
/*  (This function IS re-entrant.)                       */

int  __cdecl _gx_parse_formula(int si, LPCTSTR text, gxFormula * fm)
{
	ParseState ps;
	int i;

	ps.nbuf_ptr = 0;
	ps.look_flag[0] = 0;
	ps.look_flag[1] = 0;
	ps.sp = 0;
	ps.status.error_flag = 0;

	fm->expression = NULL;
	fm->expr_start = GX_ENULL;
	fm->cons_start = GX_ENULL;
	fm->depend_start = GX_ENULL;
	fm->expr_size = 0;
	fm->comment = NULL;

	_gx_scanner_init(text);
	formula(si, &ps, fm);
	if (!ps.status.error_flag)
	{
		fm->expression = (gxExprNode *) GX_XSmalloc(ps.nbuf_ptr * sizeof(gxExprNode));
		for (i = 0; i < ps.nbuf_ptr; i++)
			fm->expression[i] = ps.nbuf[i];
		fm->expr_size = ps.nbuf_ptr;
/*_gx_dump_ebuf (fm->expression, fm->expr_size);*/
	}
	_gx_set_expr_err_flag(ps.status.error_flag);
	_gx_set_error_reason(ps.status.error_reason);
	_gx_set_error_position(ps.status.error_position);

	return !ps.status.error_flag;
}


/*---------------------------------------------------------------------------*/
/*  Parsing functions.                               */

static void formula(int si, ParseState * ps, gxFormula * fm)
{
	match(si, ps, GX_T_EQUAL);
	if (ps->status.error_flag)
	{   /* check for '==' for better error reporting */
		if (ps->ctoken.type == GX_T_EQUAL_EQUAL)
		{
			ps->status.error_reason = GX_PARSE_ERR_PRIMARY;
			ps->status.error_position = 1;
		}
		return;
	}
	expression(si, ps);
	if (ps->status.error_flag)
		return;
	done_expr(si, ps, fm);
	if (ps->status.error_flag)
		return;
	opt_constraint(si, ps, fm);
	if (ps->status.error_flag)
		return;
	opt_dependency(si, ps, fm);
	if (ps->status.error_flag)
		return;
	opt_comment(si, ps, fm);
	if (ps->status.error_flag)
		return;
	match(si, ps, GX_T_END_OF_EXPR);
}


static void opt_constraint(int si, ParseState * ps, gxFormula * fm)
{
	if (lookahead(si, ps) != GX_T_SEMICOLON)
		return;

	match(si, ps, GX_T_SEMICOLON);
	if (ps->status.error_flag)
		return;
	expression(si, ps);
	if (ps->status.error_flag)
		return;
	done_constraint(si, ps, fm);
}


static void opt_dependency(int si, ParseState * ps, gxFormula * fm)
{
	TokType tt;

	if (lookahead(si, ps) != GX_T_BACKSLASH)
		return;

	match(si, ps, GX_T_BACKSLASH);
	if (ps->status.error_flag)
		return;

	tt = lookahead(si, ps);
	switch (tt)
	{
	case GX_T_CELL:
		match(si, ps, GX_T_CELL);
		if (ps->status.error_flag)
			return;
		push_cell(si, ps);
		if (ps->status.error_flag)
			return;
		depend_range(si, ps);
		if (ps->status.error_flag)
			return;
		break;

	case GX_T_NAME:
		match(si, ps, GX_T_NAME);
		if (ps->status.error_flag)
			return;
		push_name(si, ps);
		if (ps->status.error_flag)
			return;
		resolve_name(si, ps);
		if (ps->status.error_flag)
			return;
		break;
	default:
		return;
	}

	start_dependency(si, ps);
	if (ps->status.error_flag)
		return;
	cell_list(si, ps);
	if (ps->status.error_flag)
		return;
	done_dependency(si, ps, fm);
}

static void cell_list(int si, ParseState * ps)
{
	TokType tt;

	if (lookahead(si, ps) != GX_T_COMMA)
		return;

	match(si, ps, GX_T_COMMA);
	if (ps->status.error_flag)
		return;

	tt = lookahead(si, ps);
	switch (tt)
	{

	case GX_T_CELL:
		match(si, ps, GX_T_CELL);
		if (ps->status.error_flag)
			return;
		push_cell(si, ps);
		if (ps->status.error_flag)
			return;
		depend_range(si, ps);
		if (ps->status.error_flag)
			return;
		break;

	case GX_T_NAME:
		match(si, ps, GX_T_NAME);
		if (ps->status.error_flag)
			return;
		push_name(si, ps);
		if (ps->status.error_flag)
			return;
		resolve_name(si, ps);
		if (ps->status.error_flag)
			return;
		break;
	default:
		return;
	}

	add_dependency(si, ps);
	if (ps->status.error_flag)
		return;
	cell_list(si, ps);
}


static void depend_range(int si, ParseState * ps)
{
	TokType tt;

	tt = lookahead(si, ps);
	switch (tt)
	{
	case GX_T_DOT_DOT:
		match(si, ps, GX_T_DOT_DOT);
		if (ps->status.error_flag)
			return;
		break;
	case GX_T_DOT:
		match(si, ps, GX_T_DOT);
		if (ps->status.error_flag)
			return;
		break;
	case GX_T_COLON:
		match(si, ps, GX_T_COLON);
		if (ps->status.error_flag)
			return;
		break;
	default:
		return;
	}

	match(si, ps, GX_T_CELL);
	if (ps->status.error_flag)
		return;
	push_cell(si, ps);
	if (ps->status.error_flag)
		return;
	make_rangen(si, ps);
}

static void opt_comment(int si, ParseState * ps, gxFormula * fm)
{
	if (lookahead(si, ps) != GX_T_COMMENT)
		return;
	match(si, ps, GX_T_COMMENT);
	if (ps->status.error_flag)
		return;
	done_comment(si, ps, fm);
}


static void expression(int si, ParseState * ps)
{
	conditional_expr(si, ps);
}


static void conditional_expr(int si, ParseState * ps)
{
	log_or_expr(si, ps);
	if (ps->status.error_flag)
		return;
	more_conditional(si, ps);
}

static void more_conditional(int si, ParseState * ps)
{
	if (lookahead(si, ps) != GX_T_QMARK)
		return;

	match(si, ps, GX_T_QMARK);
	if (ps->status.error_flag)
		return;
	expression(si, ps);
	if (ps->status.error_flag)
		return;
	match(si, ps, GX_T_COLON);
	if (ps->status.error_flag)
		return;
	expression(si, ps);
	if (ps->status.error_flag)
		return;
	do_conditional(si, ps);
}


static void log_or_expr(int si, ParseState * ps)
{
	log_and_expr(si, ps);
	if (ps->status.error_flag)
		return;
	more_log_or(si, ps);
}

static void more_log_or(int si, ParseState * ps)
{
	if (lookahead(si, ps) != GX_T_D_BAR)
		return;

	match(si, ps, GX_T_D_BAR);
	if (ps->status.error_flag)
		return;
	push_operator(si, ps, GX_LOGICAL_OR);
	if (ps->status.error_flag)
		return;
	log_and_expr(si, ps);
	if (ps->status.error_flag)
		return;
	do_binary(si, ps);
	if (ps->status.error_flag)
		return;
	more_log_or(si, ps);
}


static void log_and_expr(int si, ParseState * ps)
{
	bit_or_expr(si, ps);
	if (ps->status.error_flag)
		return;
	more_log_and(si, ps);
}

static void more_log_and(int si, ParseState * ps)
{
	if (lookahead(si, ps) != GX_T_D_AMPERSAND)
		return;

	match(si, ps, GX_T_D_AMPERSAND);
	if (ps->status.error_flag)
		return;
	push_operator(si, ps, GX_LOGICAL_AND);
	if (ps->status.error_flag)
		return;
	bit_or_expr(si, ps);
	if (ps->status.error_flag)
		return;
	do_binary(si, ps);
	if (ps->status.error_flag)
		return;
	more_log_and(si, ps);
}


static void bit_or_expr(int si, ParseState * ps)
{
	bit_xor_expr(si, ps);
	if (ps->status.error_flag)
		return;
	more_bit_or(si, ps);
}

static void more_bit_or(int si, ParseState * ps)
{
	if (lookahead(si, ps) != GX_T_BAR)
		return;

	match(si, ps, GX_T_BAR);
	if (ps->status.error_flag)
		return;
	push_operator(si, ps, GX_BOOLEAN_OR);
	if (ps->status.error_flag)
		return;
	bit_xor_expr(si, ps);
	if (ps->status.error_flag)
		return;
	do_binary(si, ps);
	if (ps->status.error_flag)
		return;
	more_bit_or(si, ps);
}


static void bit_xor_expr(int si, ParseState * ps)
{
	bit_and_expr(si, ps);
	if (ps->status.error_flag)
		return;
	more_bit_xor(si, ps);
}

static void more_bit_xor(int si, ParseState * ps)
{
	if (lookahead(si, ps) != GX_T_CARET)
		return;

	match(si, ps, GX_T_CARET);
	if (ps->status.error_flag)
		return;
	push_operator(si, ps, GX_BOOLEAN_XOR);
	if (ps->status.error_flag)
		return;
	bit_and_expr(si, ps);
	if (ps->status.error_flag)
		return;
	do_binary(si, ps);
	if (ps->status.error_flag)
		return;
	more_bit_xor(si, ps);
}


static void bit_and_expr(int si, ParseState * ps)
{
	equality_expr(si, ps);
	if (ps->status.error_flag)
		return;
	more_bit_and(si, ps);
}

static void more_bit_and(int si, ParseState * ps)
{
	if (lookahead(si, ps) != GX_T_AMPERSAND)
		return;

	match(si, ps, GX_T_AMPERSAND);
	if (ps->status.error_flag)
		return;
	push_operator(si, ps, GX_BOOLEAN_AND);
	if (ps->status.error_flag)
		return;
	equality_expr(si, ps);
	if (ps->status.error_flag)
		return;
	do_binary(si, ps);
	if (ps->status.error_flag)
		return;
	more_bit_and(si, ps);
}


static void equality_expr(int si, ParseState * ps)
{
	relational_expr(si, ps);
	if (ps->status.error_flag)
		return;
	more_equality(si, ps);
}

static void more_equality(int si, ParseState * ps)
{
	TokType tt;

	tt = lookahead(si, ps);
	switch (tt)
	{
	case GX_T_BANG_EQUAL:
		match(si, ps, GX_T_BANG_EQUAL);
		if (ps->status.error_flag)
			return;
		push_operator(si, ps, GX_NOT_EQUAL);
		if (ps->status.error_flag)
			return;
		break;
	case GX_T_EQUAL_EQUAL:
		match(si, ps, GX_T_EQUAL_EQUAL);
		if (ps->status.error_flag)
			return;
		push_operator(si, ps, GX_EQUAL);
		if (ps->status.error_flag)
			return;
		break;
	case GX_T_EQUAL:    /* allow a single '=' here, I hope - TKM */
		match(si, ps, GX_T_EQUAL);
		if (ps->status.error_flag)
			return;
		push_operator(si, ps, GX_EQUAL);
		if (ps->status.error_flag)
			return;
		break;
	default:
		return;
	}

	relational_expr(si, ps);
	if (ps->status.error_flag)
		return;
	do_binary(si, ps);
	if (ps->status.error_flag)
		return;
	more_equality(si, ps);
}


static void relational_expr(int si, ParseState * ps)
{
	shift_expr(si, ps);
	if (ps->status.error_flag)
		return;
	more_relational(si, ps);
}

static void more_relational(int si, ParseState * ps)
{
	TokType tt;

	tt = lookahead(si, ps);
	switch (tt)
	{
	case GX_T_LANGLE:
		match(si, ps, GX_T_LANGLE);
		if (ps->status.error_flag)
			return;
		push_operator(si, ps, GX_LESS_THAN);
		if (ps->status.error_flag)
			return;
		break;
	case GX_T_RANGLE:
		match(si, ps, GX_T_RANGLE);
		if (ps->status.error_flag)
			return;
		push_operator(si, ps, GX_GREATER_THAN);
		if (ps->status.error_flag)
			return;
		break;
	case GX_T_LANGLE_EQUAL:
		match(si, ps, GX_T_LANGLE_EQUAL);
		if (ps->status.error_flag)
			return;
		push_operator(si, ps, GX_LT_OR_EQUAL);
		if (ps->status.error_flag)
			return;
		break;
	case GX_T_RANGLE_EQUAL:
		match(si, ps, GX_T_RANGLE_EQUAL);
		if (ps->status.error_flag)
			return;
		push_operator(si, ps, GX_GT_OR_EQUAL);
		if (ps->status.error_flag)
			return;
		break;
	default:
		return;
	}

	shift_expr(si, ps);
	if (ps->status.error_flag)
		return;
	do_binary(si, ps);
	if (ps->status.error_flag)
		return;
	more_relational(si, ps);
}


static void shift_expr(int si, ParseState * ps)
{
	additive_expr(si, ps);
	if (ps->status.error_flag)
		return;
	more_shift(si, ps);
}

static void more_shift(int si, ParseState * ps)
{
	TokType tt;

	tt = lookahead(si, ps);
	switch (tt)
	{
	case GX_T_D_LANGLE:
		match(si, ps, GX_T_D_LANGLE);
		if (ps->status.error_flag)
			return;
		push_operator(si, ps, GX_SHIFT_LEFT);
		if (ps->status.error_flag)
			return;
		break;
	case GX_T_D_RANGLE:
		match(si, ps, GX_T_D_RANGLE);
		if (ps->status.error_flag)
			return;
		push_operator(si, ps, GX_SHIFT_RIGHT);
		if (ps->status.error_flag)
			return;
		break;
	default:
		return;
	}

	additive_expr(si, ps);
	if (ps->status.error_flag)
		return;
	do_binary(si, ps);
	if (ps->status.error_flag)
		return;
	more_shift(si, ps);
}


static void additive_expr(int si, ParseState * ps)
{
	multiplicative_expr(si, ps);
	if (ps->status.error_flag)
		return;
	more_additive(si, ps);
}

static void more_additive(int si, ParseState * ps)
{
	TokType tt;

	tt = lookahead(si, ps);
	switch (tt)
	{
	case GX_T_PLUS:
		match(si, ps, GX_T_PLUS);
		if (ps->status.error_flag)
			return;
		push_operator(si, ps, GX_PLUS);
		if (ps->status.error_flag)
			return;
		break;
	case GX_T_MINUS:
		match(si, ps, GX_T_MINUS);
		if (ps->status.error_flag)
			return;
		push_operator(si, ps, GX_MINUS);
		if (ps->status.error_flag)
			return;
		break;
	default:
		return;
	}

	multiplicative_expr(si, ps);
	if (ps->status.error_flag)
		return;
	do_binary(si, ps);
	if (ps->status.error_flag)
		return;
	more_additive(si, ps);
}


static void multiplicative_expr(int si, ParseState * ps)
{
	unary_expr(si, ps);
	if (ps->status.error_flag)
		return;
	more_multiplicative(si, ps);
}

static void more_multiplicative(int si, ParseState * ps)
{
	TokType tt;

	tt = lookahead(si, ps);
	switch (tt)
	{
	case GX_T_STAR:
		match(si, ps, GX_T_STAR);
		if (ps->status.error_flag)
			return;
		push_operator(si, ps, GX_MULTIPLY);
		if (ps->status.error_flag)
			return;
		break;
	case GX_T_SLASH:
		match(si, ps, GX_T_SLASH);
		if (ps->status.error_flag)
			return;
		push_operator(si, ps, GX_DIVIDE);
		if (ps->status.error_flag)
			return;
		break;
	case GX_T_PERCENT:
		match(si, ps, GX_T_PERCENT);
		if (ps->status.error_flag)
			return;
		push_operator(si, ps, GX_MODULUS);
		if (ps->status.error_flag)
			return;
		break;
	default:
		return;
	}

	unary_expr(si, ps);
	if (ps->status.error_flag)
		return;
	do_binary(si, ps);
	if (ps->status.error_flag)
		return;
	more_multiplicative(si, ps);
}


static void unary_expr(int si, ParseState * ps)
{
	TokType tt;

	tt = lookahead(si, ps);
	switch (tt)
	{
	case GX_T_PLUS:
		match(si, ps, GX_T_PLUS);
		if (ps->status.error_flag)
			return;
		push_operator(si, ps, GX_UNARY_PLUS);
		if (ps->status.error_flag)
			return;
		exponent_expr(si, ps);
		if (ps->status.error_flag)
			return;
		do_unary(si, ps);
		break;
	case GX_T_MINUS:
		match(si, ps, GX_T_MINUS);
		if (ps->status.error_flag)
			return;
		push_operator(si, ps, GX_UNARY_MINUS);
		if (ps->status.error_flag)
			return;
		exponent_expr(si, ps);
		if (ps->status.error_flag)
			return;
		do_unary(si, ps);
		break;
	case GX_T_BANG:
		match(si, ps, GX_T_BANG);
		if (ps->status.error_flag)
			return;
		push_operator(si, ps, GX_LOGICAL_NOT);
		if (ps->status.error_flag)
			return;
		exponent_expr(si, ps);
		if (ps->status.error_flag)
			return;
		do_unary(si, ps);
		break;
	case GX_T_TILDE:
		match(si, ps, GX_T_TILDE);
		if (ps->status.error_flag)
			return;
		push_operator(si, ps, GX_BOOLEAN_NOT);
		if (ps->status.error_flag)
			return;
		exponent_expr(si, ps);
		if (ps->status.error_flag)
			return;
		do_unary(si, ps);
		break;
	default:
		exponent_expr(si, ps);
		if (ps->status.error_flag)
			return;
		break;
	}
}


static void exponent_expr(int si, ParseState * ps)
{
	percent_expr(si, ps);
	if (ps->status.error_flag)
		return;
	more_exponent(si, ps);
}

static void more_exponent(int si, ParseState * ps)
{
	if (lookahead(si, ps) != GX_T_D_STAR)
		return;

	match(si, ps, GX_T_D_STAR);
	if (ps->status.error_flag)
		return;
	push_operator(si, ps, GX_POWER);
	if (ps->status.error_flag)
		return;
	percent_expr(si, ps);
	if (ps->status.error_flag)
		return;
	do_binary(si, ps);
	if (ps->status.error_flag)
		return;
	more_exponent(si, ps);
}

static void percent_expr(int si, ParseState * ps)
{
	primary(si, ps);
	if (ps->status.error_flag)
		return;
	if (lookahead(si, ps) != GX_T_PERCENT || is_primary(lookahead2(si, ps)))
		return;
	match(si, ps, GX_T_PERCENT);
	if (ps->status.error_flag)
		return;
	push_operator(si, ps, GX_PERCENT);
	if (ps->status.error_flag)
		return;
	do_percent(si, ps);
	if (ps->status.error_flag)
		return;
}

static int is_primary(TokType tt)
{
	switch (tt)
	{
	case GX_T_CELL:
	case GX_T_NAME:
	case GX_T_FUNCTION:
	case GX_T_STRING:
	case GX_T_NUMBER:
	case GX_T_HEX_NUMBER:
	case GX_T_POUND:
	case GX_T_LPAREN:
	case GX_T_D_QMARK:
		return 1;
	default:
		return 0;
	}
}

static void primary(int si, ParseState * ps)
{
	TokType tt;
	LPTSTR pszName;

	tt = lookahead(si, ps);
	switch (tt)
	{
	case GX_T_CELL:
		match(si, ps, GX_T_CELL);
		if (ps->status.error_flag)
			return;
		push_cell(si, ps);
		if (ps->status.error_flag)
			return;
		opt_range(si, ps);
		break;

	case GX_T_NAME:
		match(si, ps, GX_T_NAME);
		if (ps->status.error_flag)
			return;
		push_name(si, ps);
		if (ps->status.error_flag)
			return;
		pszName = ps->lookahead[0].text;
		possible_function(si, ps);
		if (ps->status.error_flag)
			return;
		opt_range(si, ps);
		break;

	case GX_T_FUNCTION:
		match(si, ps, GX_T_FUNCTION);
		if (ps->status.error_flag)
			return;
		push_name(si, ps);
		if (ps->status.error_flag)
			return;
		opt_arguments(si, ps);
		if (ps->status.error_flag)
			return;
		make_function(si, ps);
		if (ps->status.error_flag)
			return;
		opt_range(si, ps);
		break;

	case GX_T_STRING:
		match(si, ps, GX_T_STRING);
		if (ps->status.error_flag)
			return;
		push_string(si, ps);
		break;

	case GX_T_NUMBER:
		match(si, ps, GX_T_NUMBER);
		if (ps->status.error_flag)
			return;
		push_number(si, ps);
		break;

	case GX_T_HEX_NUMBER:
		match(si, ps, GX_T_HEX_NUMBER);
		if (ps->status.error_flag)
			return;
		push_number(si, ps);
		break;

	case GX_T_POUND:
		match(si, ps, GX_T_POUND);
		if (ps->status.error_flag)
			return;
		push_rel(si, ps);
		if (ps->status.error_flag)
			return;
		opt_rel_cell(si, ps);
		break;

	case GX_T_LPAREN:
		match(si, ps, GX_T_LPAREN);
		if (ps->status.error_flag)
			return;
		expression(si, ps);
		if (ps->status.error_flag)
			return;
		match(si, ps, GX_T_RPAREN);
		if (ps->status.error_flag)
			return;
		add_parens(si, ps);
		break;

	case GX_T_D_QMARK:
		match(si, ps, GX_T_D_QMARK);
		if (ps->status.error_flag)
			return;
		push_illegal(si, ps);
		if (ps->status.error_flag)
			return;
		break;

	default:
		ps->status.error_flag = 1;
		ps->status.error_reason = GX_PARSE_ERR_PRIMARY;
		ps->status.error_position = ps->lookahead[0].position;
		break;
	}
}


static void opt_arguments(int si, ParseState * ps)
{
	if (lookahead(si, ps) != GX_T_LPAREN)
		return;

	match(si, ps, GX_T_LPAREN);
	if (ps->status.error_flag)
		return;
	arg_list(si, ps);
	if (ps->status.error_flag)
		return;
	match(si, ps, GX_T_RPAREN);
}

static void opt_range(int si, ParseState * ps)
{
	TokType tt;

	tt = lookahead(si, ps);
	switch (tt)
	{
	case GX_T_DOT_DOT:
		match(si, ps, GX_T_DOT_DOT);
		if (ps->status.error_flag)
			return;
		break;
	case GX_T_DOT:
		match(si, ps, GX_T_DOT);
		if (ps->status.error_flag)
			return;
		break;
	case GX_T_COLON:
		match(si, ps, GX_T_COLON);
		if (ps->status.error_flag)
			return;
		break;
	default:
		return;
	}

	range_rhs(si, ps);
	if (ps->status.error_flag)
		return;
	make_rangen(si, ps);
}

static void range_rhs(int si, ParseState * ps)
{
	TokType tt;

	tt = lookahead(si, ps);
	switch (tt)
	{
	case GX_T_CELL:
		match(si, ps, GX_T_CELL);
		if (ps->status.error_flag)
			return;
		push_cell(si, ps);
		break;

	case GX_T_NAME:
		match(si, ps, GX_T_NAME);
		if (ps->status.error_flag)
			return;
		push_name(si, ps);
		if (ps->status.error_flag)
			return;
		possible_function(si, ps);
		break;

	case GX_T_FUNCTION:
		match(si, ps, GX_T_FUNCTION);
		if (ps->status.error_flag)
			return;
		push_name(si, ps);
		if (ps->status.error_flag)
			return;
		match(si, ps, GX_T_LPAREN);
		if (ps->status.error_flag)
			return;
		arg_list(si, ps);
		if (ps->status.error_flag)
			return;
		match(si, ps, GX_T_RPAREN);
		if (ps->status.error_flag)
			return;
		make_function(si, ps);
		break;

	default:
		ps->status.error_flag = 1;
		ps->status.error_reason = GX_PARSE_ERR_RANGE_RHS;
		ps->status.error_position = ps->lookahead[0].position;
		break;
	}
}

static void possible_function(int si, ParseState * ps)
{
	TokType tt;

	tt = lookahead(si, ps);
	switch (tt)
	{
	case GX_T_LPAREN:
		match(si, ps, GX_T_LPAREN);
		if (ps->status.error_flag)
			return;
		arg_list(si, ps);
		if (ps->status.error_flag && 
			(ps->status.error_reason == GX_PARSE_ERR_BAD_NAME
			|| ps->status.error_reason == GX_PARSE_ERR_UNDEF_FN))
		{
			cleanup_function(si, ps);
			return;
		}
		match(si, ps, GX_T_RPAREN);
		if (ps->status.error_flag)
		{
			cleanup_function(si, ps);
			return;
		}
		make_function(si, ps);
		break;

	default:
		resolve_name(si, ps);
		break;
	}
}

static void opt_rel_cell(int si, ParseState * ps)
{
	if (lookahead(si, ps) != GX_T_LBRACE)
		return;

	match(si, ps, GX_T_LBRACE);
	if (ps->status.error_flag)
		return;
	expression(si, ps);
	if (ps->status.error_flag)
		return;
	add_rel_col(si, ps);
	if (ps->status.error_flag)
		return;
	opt_rel_row(si, ps);
	if (ps->status.error_flag)
		return;
	match(si, ps, GX_T_RBRACE);
}

static void opt_rel_row(int si, ParseState * ps)
{
	if (lookahead(si, ps) != GX_T_COMMA)
		return;

	match(si, ps, GX_T_COMMA);
	if (ps->status.error_flag)
		return;
	expression(si, ps);
	if (ps->status.error_flag)
		return;
	add_rel_row(si, ps);
}


static void arg_list(int si, ParseState * ps)
{
	if (lookahead(si, ps) == GX_T_RPAREN)
		return;

	expression(si, ps);
	if (ps->status.error_flag)
		return;
	more_args(si, ps);
}


static void more_args(int si, ParseState * ps)
{
	if (lookahead(si, ps) != GX_T_COMMA)
		return;

	match(si, ps, GX_T_COMMA);
	if (ps->status.error_flag)
		return;
	expression(si, ps);
	if (ps->status.error_flag)
		return;
	more_args(si, ps);
}


/*---------------------------------------------------------------------------*/
/*  Parsing support functions.                           */

static void match(int si, ParseState * ps, TokType desired)
{
	if (ps->look_flag[0])
	{
		ps->ctoken = ps->lookahead[0];
		ps->look_flag[0] = 0;
		if (ps->look_flag[1])
		{   /* move it up one in the queue */
			ps->lookahead[0] = ps->lookahead[1];
			ps->look_flag[0] = 1;
			ps->look_flag[1] = 0;
		}
	}
	else
		ps->ctoken = _gx_get_token(si);

	if (ps->ctoken.type == GX_T_ERROR)
	{
		ps->status.error_flag = 1;
		ps->status.error_reason = ps->ctoken.code;
		ps->status.error_position = ps->ctoken.position;
	}
	else if (ps->ctoken.type != desired)
	{
		ps->status.error_flag = 1;
		ps->status.error_reason = get_match_error(desired);
		ps->status.error_expected = desired;
		ps->status.error_found = ps->ctoken.type;
		ps->status.error_position = ps->ctoken.position;
	}
/*
else
	{
	_tprintf (_T("token:  type=%d  text=%s\n"), ps->ctoken.type, ps->ctoken.text);
	}
*/
}


static int get_match_error(TokType desired)
{
	switch (desired)
	{
	case GX_T_SEMICOLON:
		return GX_PARSE_ERR_T_SEMICOLON;
	case GX_T_COLON:
		return GX_PARSE_ERR_T_COLON;
	case GX_T_COMMA:
		return GX_PARSE_ERR_T_COMMA;
	case GX_T_QMARK:
		return GX_PARSE_ERR_T_QMARK;
	case GX_T_POUND:
		return GX_PARSE_ERR_T_POUND;
	case GX_T_BACKSLASH:
		return GX_PARSE_ERR_T_BACKSLASH;
	case GX_T_PLUS:
		return GX_PARSE_ERR_T_PLUS;
	case GX_T_MINUS:
		return GX_PARSE_ERR_T_MINUS;
	case GX_T_STAR:
		return GX_PARSE_ERR_T_STAR;
	case GX_T_SLASH:
		return GX_PARSE_ERR_T_SLASH;
	case GX_T_PERCENT:
		return GX_PARSE_ERR_T_PERCENT;
	case GX_T_BAR:
		return GX_PARSE_ERR_T_BAR;
	case GX_T_CARET:
		return GX_PARSE_ERR_T_CARET;
	case GX_T_AMPERSAND:
		return GX_PARSE_ERR_T_AMPERSAND;
	case GX_T_BANG:
		return GX_PARSE_ERR_T_BANG;
	case GX_T_TILDE:
		return GX_PARSE_ERR_T_TILDE;
	case GX_T_LANGLE:
		return GX_PARSE_ERR_T_LANGLE;
	case GX_T_RANGLE:
		return GX_PARSE_ERR_T_RANGLE;
	case GX_T_LPAREN:
		return GX_PARSE_ERR_T_LPAREN;
	case GX_T_RPAREN:
		return GX_PARSE_ERR_T_RPAREN;
	case GX_T_LBRACE:
		return GX_PARSE_ERR_T_LBRACE;
	case GX_T_RBRACE:
		return GX_PARSE_ERR_T_RBRACE;
	case GX_T_EQUAL:
		return GX_PARSE_ERR_T_EQUAL;
	case GX_T_D_STAR:
		return GX_PARSE_ERR_T_D_STAR;
	case GX_T_D_AMPERSAND:
		return GX_PARSE_ERR_T_D_AMPERSAND;
	case GX_T_D_BAR:
		return GX_PARSE_ERR_T_D_BAR;
	case GX_T_D_LANGLE:
		return GX_PARSE_ERR_T_D_LANGLE;
	case GX_T_D_RANGLE:
		return GX_PARSE_ERR_T_D_RANGLE;
	case GX_T_LANGLE_EQUAL:
		return GX_PARSE_ERR_T_LANGLE_EQUAL;
	case GX_T_RANGLE_EQUAL:
		return GX_PARSE_ERR_T_RANGLE_EQUAL;
	case GX_T_BANG_EQUAL:
		return GX_PARSE_ERR_T_BANG_EQUAL;
	case GX_T_EQUAL_EQUAL:
		return GX_PARSE_ERR_T_EQUAL_EQUAL;
	case GX_T_DOT_DOT:
		return GX_PARSE_ERR_T_DOT_DOT;
	case GX_T_CELL:
		return GX_PARSE_ERR_T_CELL;
	case GX_T_NAME:
		return GX_PARSE_ERR_T_NAME;
	case GX_T_FUNCTION:
		return GX_PARSE_ERR_T_FUNCTION;
	case GX_T_STRING:
		return GX_PARSE_ERR_T_STRING;
	case GX_T_NUMBER:
		return GX_PARSE_ERR_T_NUMBER;
	case GX_T_HEX_NUMBER:
		return GX_PARSE_ERR_T_HEX_NUMBER;
	case GX_T_COMMENT:
		return GX_PARSE_ERR_T_COMMENT;
	case GX_T_END_OF_EXPR:
		return GX_PARSE_ERR_T_END_OF_EXPR;
	case GX_T_ERROR:
		return GX_PARSE_ERR_T_ERROR;
	case GX_T_DOT:
		return GX_PARSE_ERR_T_DOT;
	default:
		return GX_PARSE_ERR_UNEXPECTED;
	}
}


static TokType lookahead(int si, ParseState * ps)
{
	if (!ps->look_flag[0])
	{
		ps->lookahead[0] = _gx_get_token(si);
		ps->look_flag[0] = 1;
	}
	return ps->lookahead[0].type;
}


static TokType lookahead2(int si, ParseState * ps)
{
	if (!ps->look_flag[1])
	{
		ps->lookahead[1] = _gx_get_token(si);
		ps->look_flag[1] = 1;
	}
	return ps->lookahead[1].type;
}


/*---------------------------------------------------------------------------*/
/*  Semantic action support functions.                       */

#define PUSH(ps,x)  ps->stack[(ps->sp)++] = x
#define POP(ps)     ps->stack[--(ps->sp)]
#define TOS(ps)     ps->stack[(ps->sp)-1]
#define REF(ps,x)   ps->nbuf[x]


static gxExprPointer new_node(ParseState * ps)
{
	ps->nbuf[ps->nbuf_ptr].left = GX_ENULL;
	ps->nbuf[ps->nbuf_ptr].right = GX_ENULL;
	ps->nbuf[ps->nbuf_ptr].has_parens = 0;
	ps->nbuf[ps->nbuf_ptr].number_is_hex = 0;
	ps->nbuf[ps->nbuf_ptr].arg_is_nonstrict = 0;
	ps->nbuf[ps->nbuf_ptr].is_typesafe = 0;
	ps->nbuf[ps->nbuf_ptr].is_extern_ref = 0;

	if (ps->nbuf_ptr >= GX_MAX_NODES)
	{
		ps->status.error_flag = 1;
		ps->status.error_reason = GX_PARSE_ERR_TOK_BUF_OVFL;
		ps->status.error_position = ps->ctoken.position;
	}
	return (ps->nbuf_ptr)++;
}


static void free_node(ParseState * ps, gxExprPointer node)
{
	if ((ps->nbuf_ptr - 1) != node)
	{
		ps->status.error_flag = 1;
		ps->status.error_reason = GX_PARSE_ERR_INTERNAL_FREE;
		ps->status.error_position = ps->ctoken.position;
	}
	else
		--(ps->nbuf_ptr);
}


/*---------------------------------------------------------------------------*/
/*  Semantic action functions.                           */

static void do_conditional(int /*si*/, ParseState * ps)
{
	gxExprPointer f_expr;
	gxExprPointer t_expr;
	gxExprPointer c_expr;
	gxExprPointer cn;
	gxExprPointer en;

	f_expr = POP(ps);
	t_expr = POP(ps);
	c_expr = POP(ps);

	cn = new_node(ps);
	en = new_node(ps);

	REF(ps, cn).node_type = GX_OPERATOR_NODE;
	REF(ps, cn).value.operator_ = GX_CONDITIONAL;
	REF(ps, cn).left = c_expr;
	REF(ps, cn).right = en;

	REF(ps, en).node_type = GX_EXTENSION_NODE;
	REF(ps, en).value.eback = cn;
	REF(ps, en).left = t_expr;
	REF(ps, en).right = f_expr;

	PUSH(ps, cn);
}


static void push_operator(int /*si*/, ParseState * ps, gxOpType op)
{
	gxExprPointer on;

	on = new_node(ps);
	REF(ps, on).node_type = GX_OPERATOR_NODE;
	REF(ps, on).value.operator_ = op;

	PUSH(ps, on);
}


static void do_binary(int /*si*/, ParseState * ps)
{
	gxExprPointer left;
	gxExprPointer op;
	gxExprPointer right;

	right = POP(ps);
	op = POP(ps);
	left = POP(ps);

	REF(ps, op).left = left;
	REF(ps, op).right = right;

	PUSH(ps, op);
}


static void do_unary(int /*si*/, ParseState * ps)
{
	gxExprPointer op;
	gxExprPointer right;

	right = POP(ps);
	op = TOS(ps);

	REF(ps, op).right = right;
}


static void do_percent(int /*si*/, ParseState * ps)
{
	gxExprPointer op;
	gxExprPointer right;

	op = POP(ps);
	right = POP(ps);

	REF(ps, op).right = right;

	PUSH(ps, op);
}


static void push_cell(int /*si*/, ParseState * ps)
{
	gxExprPointer cell;
	gxRange range;

	cell = new_node(ps);
	REF(ps, cell).node_type = GX_CELL_NODE;

	if (!_gx_text_to_range(ps->ctoken.text, &range))
	{
		ps->status.error_flag = 1;
		ps->status.error_reason = GX_PARSE_ERR_BAD_CELL;
		ps->status.error_position = ps->ctoken.position;
	}
	else
		REF(ps, cell).value.range = range;

	GX_XSfree(ps->ctoken.text);
	PUSH(ps, cell);
}


static void push_name(int /*si*/, ParseState * ps)
{
	gxExprPointer name;

	name = new_node(ps);
	REF(ps, name).node_type = GX_NAME_NODE;
	REF(ps, name).value.name = ps->ctoken.text;

	PUSH(ps, name);
}


static void check_strictness(ParseState * ps, gxExprPointer node, gxKeyword * fnp, int arg_count)
{
	gxExprPointer args[GX_MAX_ARGS];
	gxExprPointer np;
	int a,
		z;
	int i,
		j;
	int num_opt_args = 0;
	int num_var_args = 0;

	if (arg_count > GX_MAX_ARGS)
	{
		ps->status.error_flag = 1;
		ps->status.error_reason = GX_PARSE_ERR_TOO_MANY_ARGS;
		ps->status.error_position = ps->ctoken.position;
		return;
	}
	for (i = 0, np = node; np != GX_ENULL; np = REF(ps, np).right, ++i)
		args[i] = np;

	for (i = 0; i < fnp->num_args; i++)
		if (fnp->args[i].presence == GX_OPTIONAL)
			++num_opt_args;

	a = 0;
	for (i = 0; i < fnp->num_args; i++)
	{
		if (i >= arg_count)
			break;
		switch (fnp->args[i].presence)
		{
		case GX_REQUIRED:
			REF(ps, args[a]).arg_is_nonstrict = fnp->args[i].is_nonstrict;
			REF(ps, args[a]).value.arg.decl_arg_type = fnp->args[i].type;
			a++;
			break;

		case GX_OPTIONAL:   /* assumes optional args at end of list */
			REF(ps, args[a]).arg_is_nonstrict = fnp->args[i].is_nonstrict;
			REF(ps, args[a]).value.arg.decl_arg_type = fnp->args[i].type;
			a++;
			break;

		case GX_VARIABLE:   /* only one var arg in formal arg list */
			++num_var_args;
			if (i == (fnp->num_args - 1))
			{   /* var args at end of list */
				while (a < arg_count)
				{
					REF(ps, args[a]).arg_is_nonstrict = fnp->args[i].is_nonstrict;
					REF(ps, args[a]).value.arg.decl_arg_type = fnp->args[i].type;
					a++;
				}
			}
			else
			{   /* var args at beginning (or middle) of list */
				for (z = arg_count - 1, j = fnp->num_args - 1; j != i; j--, z--)
				{
					REF(ps, args[z]).arg_is_nonstrict = fnp->args[j].is_nonstrict;
					REF(ps, args[z]).value.arg.decl_arg_type = fnp->args[j].type;
				}
				for (; z >= a; z--)
				{
					REF(ps, args[z]).arg_is_nonstrict = fnp->args[i].is_nonstrict;
					REF(ps, args[z]).value.arg.decl_arg_type = fnp->args[i].type;
				}
				i = fnp->num_args;  /* fake multi-level break */
			}
			break;
		}
	}

/*
 * The following assumes that a function does not have both variable
 * arguments and optional arguments.  This is true for all current
 * (and most conceivable) functions.
 */

	if (arg_count < (fnp->num_args - num_opt_args))
	{
		ps->status.error_flag = 1;
		ps->status.error_reason = GX_PARSE_ERR_TOO_FEW_ARGS;
		ps->status.error_position = ps->ctoken.position;
	}
	else if ((arg_count > fnp->num_args) && !num_var_args)
	{
		ps->status.error_flag = 1;
		ps->status.error_reason = GX_PARSE_ERR_TOO_MANY_ARGS;
		ps->status.error_position = ps->ctoken.position;
	}
}


static void check_func_for_extern_refs(ParseState * ps, gxExprPointer nn, gxKeyword * fnp)
{
	gxExprPointer arg;

	if (_tcscmp(fnp->name, _T("XVALUE")))
		return;

	arg = REF(ps, nn).right;
	arg = REF(ps, arg).left;
	REF(ps, arg).is_extern_ref = 1;
}

static void cleanup_function(int /*si*/, ParseState * ps)
{
	gxExprPointer node = GX_ENULL;
	gxExprPointer nn = GX_ENULL;
	gxExprPointer on = GX_ENULL;
	gxKeyword *fnp;
	int arg_count = 0;

	on = GX_ENULL;
	while (1)
	{
		node = POP(ps);
		if (REF(ps, node).node_type == GX_NAME_NODE)
			break;

		++arg_count;
		nn = new_node(ps);
		REF(ps, nn).node_type = GX_ARG_NODE;
		if (on != GX_ENULL)
			REF(ps, on).value.arg.back = nn;
		REF(ps, nn).right = on;
		REF(ps, nn).left = node;
		on = nn;
	}
	if (nn != GX_ENULL)
		REF(ps, nn).value.arg.back = node;

	_gx_convert_upper(REF(ps, node).value.name);

	fnp = _gx_fn_lookup(REF(ps, node).value.name);
	if (fnp == NULL)
	{
		// fnp = ext_fn_lookup (REF(ps,node).value.name);
		// check_strictness (ps, nn, fnp, arg_count);
		;
	}
	else
	{
		check_strictness(ps, nn, fnp, arg_count);
		if (!ps->status.error_flag)
			check_func_for_extern_refs(ps, nn, fnp);
	}

	GX_XSfree(REF(ps, node).value.name);
	if (fnp == NULL)
	{
		REF(ps, node).node_type = GX_FUNCTION_NODE;
		REF(ps, node).value.fnp = fnp;
		ps->status.error_flag = 1;
		ps->status.error_reason = GX_PARSE_ERR_UNDEF_FN;
		ps->status.error_position = ps->ctoken.position;
	}
	else
	{
		REF(ps, node).node_type = GX_FUNCTION_NODE;
		REF(ps, node).value.fnp = fnp;
	}

	REF(ps, node).right = nn;
	PUSH(ps, node);
}

static void make_function(int /*si*/, ParseState * ps)
{
	gxExprPointer node = GX_ENULL;
	gxExprPointer nn = GX_ENULL;
	gxExprPointer on = GX_ENULL;
	gxKeyword *fnp;
	int arg_count = 0;

	on = GX_ENULL;
	while (1)
	{
		node = POP(ps);
		if (REF(ps, node).node_type == GX_NAME_NODE)
			break;

		++arg_count;
		nn = new_node(ps);
		REF(ps, nn).node_type = GX_ARG_NODE;
		if (on != GX_ENULL)
			REF(ps, on).value.arg.back = nn;
		REF(ps, nn).right = on;
		REF(ps, nn).left = node;
		on = nn;
	}
	if (nn != GX_ENULL)
		REF(ps, nn).value.arg.back = node;

	_gx_convert_upper(REF(ps, node).value.name);

	fnp = _gx_fn_lookup(REF(ps, node).value.name);
	if (fnp == NULL)
	{
		// fnp = ext_fn_lookup (REF(ps,node).value.name);
		// check_strictness (ps, nn, fnp, arg_count);
		;
	}
	else
	{
		check_strictness(ps, nn, fnp, arg_count);
		if (!ps->status.error_flag)
			check_func_for_extern_refs(ps, nn, fnp);
	}

	GX_XSfree(REF(ps, node).value.name);
	if (fnp == NULL)
	{
		REF(ps, node).node_type = GX_FUNCTION_NODE;
		REF(ps, node).value.fnp = fnp;
		ps->status.error_flag = 1;
		ps->status.error_reason = GX_PARSE_ERR_UNDEF_FN;
		ps->status.error_position = ps->ctoken.position;
	}
	else
	{
		REF(ps, node).node_type = GX_FUNCTION_NODE;
		REF(ps, node).value.fnp = fnp;
	}

	REF(ps, node).right = nn;
	PUSH(ps, node);
}

static void resolve_name(int si, ParseState * ps)
{
	gxExprPointer np;
	gxRangeName *rnp;

	np = TOS(ps);
	rnp = _gx_range_name_lookup(si, REF(ps, np).value.name, NULL);
	GX_XSfree(REF(ps, np).value.name);
	if (rnp == NULL)
	{
		REF(ps, np).node_type = GX_NAMED_RANGE_NODE;
		REF(ps, np).value.rnp = rnp;
		ps->status.error_flag = 1;
		ps->status.error_reason = GX_PARSE_ERR_BAD_NAME;
		ps->status.error_position = ps->ctoken.position;
	}
	else
	{
		REF(ps, np).node_type = (rnp->range.cell_only) ? GX_NAMED_CELL_NODE
			: GX_NAMED_RANGE_NODE;
		REF(ps, np).value.rnp = rnp;
	}
}


static void push_string(int /*si*/, ParseState * ps)
{
	gxExprPointer str;

	str = new_node(ps);
	REF(ps, str).node_type = GX_STRING_NODE;
	// ANSI C string escape
//  if (!_gx_get_context_ptr(si)->v2_string_mode)
	_gx_xs_decode_string(ps->ctoken.text, ps->ctoken.text);
	REF(ps, str).value.string = ps->ctoken.text;

	PUSH(ps, str);
}


static void push_number(int /*si*/, ParseState * ps)
{
	gxExprPointer num;
	int hexval;

	num = new_node(ps);
	REF(ps, num).node_type = GX_NUMBER_NODE;
	if (ps->ctoken.type == GX_T_HEX_NUMBER)
	{
		// QA: 31989 - #if Secure Code Cleanup.
		_stscanf(ps->ctoken.text, _T("%x"), &hexval);
		REF(ps, num).value.operand = (gxNumber) hexval;
		REF(ps, num).number_is_hex = 1;
	}
	else
	{
		REF(ps, num).value.operand = _gxttof(ps->ctoken.text);
		REF(ps, num).number_is_hex = 0;
		if (_gx_ieee_infnan(&(REF(ps, num).value.operand)))
		{
			ps->status.error_flag = 1;
			ps->status.error_reason = GX_PARSE_ERR_BAD_NAME;
			ps->status.error_position = ps->ctoken.position;
		}
	}
	GX_XSfree(ps->ctoken.text);

	PUSH(ps, num);
}


static void push_rel(int /*si*/, ParseState * ps)
{
	gxExprPointer rel;

	rel = new_node(ps);
	REF(ps, rel).node_type = GX_RELATIVE_NODE;
	REF(ps, rel).value.rel.r_expr = GX_ENULL;
	REF(ps, rel).value.rel.c_expr = GX_ENULL;

	PUSH(ps, rel);
}


static void push_illegal(int /*si*/, ParseState * ps)
{
	gxExprPointer illegal;

	illegal = new_node(ps);
	REF(ps, illegal).node_type = GX_OPERATOR_NODE;
	REF(ps, illegal).value.operator_ = GX_ILLEGAL_OP;

	PUSH(ps, illegal);
}


static void add_parens(int /*si*/, ParseState * ps)
{
	REF(ps, TOS(ps)).has_parens = 1;
}

static void make_rangen(int /*si*/, ParseState * ps)
{
	gxExprPointer lhs;
	gxExprPointer rhs;
	gxExprPointer jr;

	rhs = POP(ps);
	lhs = POP(ps);


	if ((REF(ps, rhs).node_type == GX_CELL_NODE) && (REF(ps, lhs).node_type == GX_CELL_NODE))
	{
		REF(ps, lhs).node_type = GX_RANGE_NODE;
		REF(ps, lhs).value.range.cell_only = 0;
		REF(ps, lhs).value.range.r1 = REF(ps, rhs).value.range.r0;
		REF(ps, lhs).value.range.c1 = REF(ps, rhs).value.range.c0;
		REF(ps, lhs).value.range.abs_r1 = REF(ps, rhs).value.range.abs_r0;
		REF(ps, lhs).value.range.abs_c1 = REF(ps, rhs).value.range.abs_c0;
		_gx_sort_range(&(REF(ps, lhs).value.range));
		free_node(ps, rhs);
		PUSH(ps, lhs);
	}
	else
	{
		jr = new_node(ps);
		REF(ps, jr).node_type = GX_OPERATOR_NODE;
		REF(ps, jr).value.operator_ = GX_JOINRANGE;
		REF(ps, jr).left = lhs;
		REF(ps, jr).right = rhs;
		PUSH(ps, jr);
	}
}

static void add_rel_row(int /*si*/, ParseState * ps)
{
	gxExprPointer en;
	gxExprPointer tos;

	en = POP(ps);
	tos = TOS(ps);
	REF(ps, tos).value.rel.r_expr = en;
}

static void add_rel_col(int /*si*/, ParseState * ps)
{
	gxExprPointer en;
	gxExprPointer tos;

	en = POP(ps);
	tos = TOS(ps);
	REF(ps, tos).value.rel.c_expr = en;
}


static void done_expr(int /*si*/, ParseState * ps, gxFormula * fm)
{
	gxExprPointer expr;

	expr = POP(ps);
	fm->expr_start = expr;
}


static void done_constraint(int /*si*/, ParseState * ps, gxFormula * fm)
{
	gxExprPointer expr;

	expr = POP(ps);
	fm->cons_start = expr;
}


static void start_dependency(int /*si*/, ParseState * /*ps*/)
{
/* This function intentionally left blank. */
}


static void add_dependency(int /*si*/, ParseState * ps)
{
	gxExprPointer cell;
	gxExprPointer np;

	cell = POP(ps);
	np = TOS(ps);
	while (REF(ps, np).right != GX_ENULL)
		np = REF(ps, np).right;
	REF(ps, np).right = cell;
}


static void done_dependency(int /*si*/, ParseState * ps, gxFormula * fm)
{
	gxExprPointer dep;

	dep = POP(ps);
	fm->depend_start = dep;
}


static void done_comment(int /*si*/, ParseState * ps, gxFormula * fm)
{
	fm->comment = ps->ctoken.text;
}
