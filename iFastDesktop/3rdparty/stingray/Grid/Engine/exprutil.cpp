///////////////////////////////////////////////////////////////////////////////
// exprutil.cpp: Miscellaneous utilities
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

/*---------------------------------------------------------------------------*/
/*  Duplicate a formula and all of its appendages.                           */

gxFormula * __cdecl _gx_formula_dup(gxFormula * oldf)
{
	gxFormula *newf;
	int i;

	newf = (gxFormula *) GX_XSmalloc(sizeof(gxFormula));
	newf->expression = (gxExprNode *) GX_XSmalloc(oldf->expr_size * sizeof(gxExprNode));

	for (i = 0; i < oldf->expr_size; i++)
	{
		newf->expression[i] = oldf->expression[i];
		if (oldf->expression[i].node_type == GX_STRING_NODE)
		{
			newf->expression[i].value.string =
				_gx_xs_strdup(oldf->expression[i].value.string);
		}
		else if (oldf->expression[i].node_type == GX_NAME_NODE)
		{
			newf->expression[i].value.name =
				_gx_xs_strdup(oldf->expression[i].value.name);
		}
	}

	newf->expr_size = oldf->expr_size;
	newf->expr_start = oldf->expr_start;
	newf->cons_start = oldf->cons_start;
	newf->depend_start = oldf->depend_start;

	if (oldf->comment == NULL)
		newf->comment = NULL;
	else
		newf->comment = _gx_xs_strdup(oldf->comment);

	return newf;
}


/*---------------------------------------------------------------------------*/
/*  Dump a list of expression nodes                                          */

static LPCTSTR type_text[] =
{
	_T("OPERATOR"),
	_T("NUMBER"),
	_T("STRING"),
	_T("CELL"),
	_T("RANGE"),
	_T("NAME"),
	_T("NAMED_CELL"),
	_T("NAMED_RANGE"),
	_T("FUNCTION"),
	_T("ARG"),
	_T("RELATIVE"),
	_T("EXTENSION")
};

void __cdecl _gx_dump_node(gxExprNode node, int n)
{
	node, n;
}

void __cdecl _gx_dump_ebuf(gxExprNode ebuf[], int size)
{
	ebuf, size;
}


/*---------------------------------------------------------------------------*/
/*  Error handling stuff.                                                    */

// static int expr_err_flag = 0;
// static int error_reason = 0;
// static int error_position = 0;

void  __cdecl _gx_set_error_reason(int reason)
{
	GXGetEngineState()->error_reason = reason;
}

int  __cdecl _gx_get_error_reason(void)
{
	return GXGetEngineState()->error_reason;
}

void  __cdecl _gx_set_error_position(int pos)
{
	GXGetEngineState()->error_position = pos;
}

int  __cdecl _gx_get_error_position(void)
{
	return GXGetEngineState()->error_position;
}

void  __cdecl _gx_set_expr_err_flag(int flag)
{
	GXGetEngineState()->expr_err_flag = flag;
}

int  __cdecl _gx_get_expr_err_flag(void)
{
	return GXGetEngineState()->expr_err_flag;
}


/*---------------------------------------------------------------------------*/
/*  Checks for particular types of references in an expression tree.         */

int  __cdecl _gx_references_cells(gxExprNode * nbuf, int size)
{
	int i;

	for (i = 0; i < size; i++)
	{
		if (nbuf[i].node_type == GX_CELL_NODE ||
			nbuf[i].node_type == GX_RANGE_NODE ||
			nbuf[i].node_type == GX_NAMED_CELL_NODE ||
			nbuf[i].node_type == GX_NAMED_RANGE_NODE)
			return 1;
	}
	return 0;
}

int  __cdecl _gx_calls_functions(gxExprNode * nbuf, int size)
{
	int i;
	for (i = 0; i < size; i++)
		if (nbuf[i].node_type == GX_FUNCTION_NODE)
			return 1;
	return 0;
}


/*---------------------------------------------------------------------------*/
/*  Free the dynamic memory consumed by a formula.                           */

void  __cdecl _gx_free_formula(gxFormula * fm)
{
	int i;

	for (i = 0; i < fm->expr_size; i++)
	{
		if (fm->expression[i].node_type == GX_STRING_NODE)
			GX_XSfree(fm->expression[i].value.string);
	}
	GX_XSfree(fm->expression);
	if (fm->comment != NULL)
		GX_XSfree(fm->comment);
	GX_XSfree(fm);
}

void  __cdecl _gx_free_formula_strings(gxFormula * fm)
{
	int i;

	for (i = 0; i < fm->expr_size; i++)
	{
		if (fm->expression[i].node_type == GX_STRING_NODE)
			GX_XSfree(fm->expression[i].value.string);
	}
	GX_XSfree(fm->expression);
	if (fm->comment != NULL)
		GX_XSfree(fm->comment);
}


/*---------------------------------------------------------------------------*/
/*  Miscellaneous stuff copied straight from the old expr.c                  */

void  __cdecl _gx_reset_first_error(int si)
{
	_gx_get_context_ptr(si)->first_error = 1;
}

void  __cdecl _gx_convert_upper(LPTSTR string)
{
	// TODO: make DBCS aware
	while (*string)
	{
		if (_istlower(*string))
			*string = (TCHAR) _totupper(*string);
		string++;
	}
}

void  __cdecl _gx_convert_lower(LPTSTR string)
{
	// TODO: make DBCS aware
	while (*string)
	{
		if (_istupper(*string))
			*string = (TCHAR) _totlower(*string);
		string++;
	}
}

int  __cdecl _gx_xs_int_check(double x)
{  /* check to see if it will work as an int */
	if (x >= 4294967296.0 || x <= -2147483649.0)
		return 1;
	return 0;
}

void  __cdecl _gx_str_trim(LPTSTR s)
{
	// TODO: make DBCS aware
	register int i = (int)_tcslen(s);
	while ((--i) != 0)
	{
		if (_istspace(s[i]))
			s[i] = '\0';
		else
			break;
	}
}

#pragma warning (push)
#pragma warning (disable: 4100)
int  __cdecl _gx_ieee_infnan(gxNumber * dp)
/*
  returns 1 if double pointed at by dp is +/-Infinity or NaN, 0 otherwise.
*/
{
#if defined (MIPSEL) || defined (sun3)
	unsigned char *cdp = (unsigned char *) dp;
#endif

#if defined(MIPSEL) || defined(IEEE_EL)
	if ((cdp[7] & 0x7f) == 0x7f && (cdp[6] & 0xf0) == 0xf0)
		return 1;
#endif /* IEEE_EL */
#if defined(sun3) || defined(sun4) || defined(MIPSEB) || defined(IEEE_EB)
	if ((cdp[0] & 0x7f) == 0x7f && (cdp[1] & 0xf0) == 0xf0)
		return 1;
#endif /* IEEE_EB */
	return 0;
}
#pragma warning (pop) //4100

int  __cdecl _gx_si_evaluate_expr(int si, LPCTSTR expr, int r, int c, gxOperand * result)
/*
 * Parse and evaluate "expr".  Returns "true" if parsable and
 * places result of evaluation in "result".  Returns "false" otherwise.
 */
{
	gxFormula fm;
	TCHAR formula[GX_MAX_TEXT];
	int status;

	if (expr[0] == _T('='))
		status = _gx_parse_formula(si, expr, &fm);
	else
	{
		formula[0] = _T('=');
		// QA: 31989 - #if Secure Code Cleanup.
		_tcscpy(formula + 1, expr);
		status = _gx_parse_formula(si, formula, &fm);
	}
	if (status)
	{
		int mask = _gx_freeze_list_order(si, GX_ALL_LISTS);
		*result = _gx_expr_eval(si, r, c, fm.expression, fm.expr_start);
		_gx_unfreeze_list_order(si, mask);
	}
	_gx_free_formula_strings(&fm);
	return status;
}
