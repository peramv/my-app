///////////////////////////////////////////////////////////////////////////////
// exprfunc.cpp: Interface for Worksheet functions
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

/*
 * NOTE: Functions are passed an argument list, the first element of which
 *       contains a count of the number of actual arguments to the function.
 *       Each argument is of type GX_NUMBER, GX_CELL, GX_RANGE, or GX_STRING.  Functions
 *       which return a string should store it in the buffer pointed to by
 *       _gx_get_expr_sbuf(), which is guaranteed to be a safe place of length
 *       GX_MAX_TEXT.
 *
 *       The elements of the argument list should not be altered unless you
 *       are sure you know what you are doing.  The functions all use
 *       _gx_eval_error() to handle errors, which causes a "long jump" back
 *       to the beginning of evaluate().  This means that you must not call
 *       these functions from outside of evaluate()!  (They can call each
 *       other, of course, as long as evaluate() is somewhere down on the
 *       stack frame.)  You also don't need to worry about floating point
 *       errors (overflows, underflows, etc.) within the functions
 *       since evaluate() sets up a trap for that, too.
 */

#define _OG_EXPORT_IMPL
#define _RW_IMPL

#include "stdafx.h"
#include "grid\gxsinc.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

static int __cdecl fn_fn_cmp(const void *fn_1, const void *fn_2)
{
	return (-_tcscmp(((const gxKeyword *) fn_2)->name, ((const gxKeyword *) fn_1)->name));
}

static int __cdecl fn_text_cmp(const void *text, const void *fn)
{
	return (_tcscmp((LPCTSTR) text, ((const gxKeyword *) fn)->name));
}

//////////////////////////////////////////////////////////////////////
// Abstract base class CGXWorksheetFunctions

CGXWorksheetFunctions::CGXWorksheetFunctions()
{
}

gxKeyword* CGXWorksheetFunctions::LookupFunction(LPCTSTR text)
{
	// Unused:
	text;

	return NULL;
}

void CGXWorksheetFunctions::SortTable(gxKeyword* fn_table, int sizeofTable)
{  
	/* sort it for binary searches */
	qsort((void *) fn_table, sizeofTable / sizeof(gxKeyword), sizeof(gxKeyword), fn_fn_cmp);
}

gxKeyword* CGXWorksheetFunctions::Lookup(LPCTSTR text, gxKeyword* fn_table, int sizeofTable)
{
	return ((gxKeyword *) bsearch(text, fn_table,
		sizeofTable / sizeof(gxKeyword), sizeof(gxKeyword), fn_text_cmp));
}

//////////////////////////////////////////////////////////////////////
// Helper methods

gxKeyword * __cdecl _gx_fn_lookup(LPCTSTR text)
{
	if (GXGetEngineState()->m_pWorksheetFunctions)
		return GXGetEngineState()->m_pWorksheetFunctions->LookupFunction(text);

	return NULL;
}

gxNumber   __cdecl _gx_get_one_number(gxOperand argv[])
/*
  Convenience routine for functions which expect exactly one numeric arg.
*/
{
	gxNumber x = 0;
	if (argv->val.count != 1)
	{
		  _gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	}
	switch ((++argv)->type)
	{
	case GX_NUMBER:
		x = argv->val.number;
		break;
	case GX_CELL:
		if (!_gx_fn_get_value(argv->val.range.r0, argv->val.range.c0, &x))
			x = 0.;
		break;
	case GX_STRING:
		x = 0.;
		break;
	case GX_OP_ERROR:
		_gx_function_error(argv->val.err.code);
	default:
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	}
	return x;
}

int  __cdecl _gx_cvt2constant(gxOperand * opp)
/*
  Convenience routine to convert a cell operand to a constant.
  Returns 1 if operand pointed at by "opp" could be converted to a
  number or string constant; 0 otherwise.

  (There is a similar routine in expr.c which should not be used from
  from within functions since it would cause dynamically allocated strings
  to be handled improperly.)
*/
{
	gxCell *cp;
	switch (opp->type)
	{
	case GX_CELL:
		cp = _gx_find_cell(_gx_get_expr_si(), opp->val.range.r0, opp->val.range.c0);
		if (GX_CELL_IS_EMPTYVALUE(cp))
		{
			opp->type = GX_NUMBER;
			opp->val.number = 0.;
		}
		else if (GX_CELL_CONTAINS_ERROR(cp))
			_gx_function_error(GX_FN_ERR_CELL_ERROR);
		else if (GX_CELL_CONTAINS_TEXT(cp))
		{
			opp->type = GX_STRING;
			switch (cp->value_type)
			{
			case GX_VALUE_STRING:
				opp->val.string = _gx_xs_strdup(cp->value.string);
				break;
			case GX_VALUE_SHORT_STRING:
				opp->val.string = _gx_xs_short_strdup(cp->value.short_string);
				break;
			}
		}
		else if (GX_CELL_CONTAINS_NUMBER(cp))
		{
			opp->type = GX_NUMBER;
			opp->val.number = cp->value.number;
		}
		else
			assert(0);
		return 1;
	case GX_NUMBER:
	case GX_STRING:
		return 1;
	case GX_OP_ERROR:
		_gx_function_error(opp->val.err.code);
	default:
		return 0;   /* can't be converted to constant */
	}
}


int  __cdecl _gx_cvt2int(gxNumber x)
{
	if (_gx_xs_int_check(x))
		_gx_function_error(GX_FN_INT_OUT_OF_RNG);
	return (int) x;
}


int  __cdecl _gx_fn_get_value(int r, int c, gxNumber * vp)
{
	gxCell *cp;
	int status = 0;

	// TODO: provide an Excel-strictness function
	// in a future version because the following 
	// function will convert any string into a number
	// e.g. 125q will become 125 whereas MS Excel will
	// return 0 for cells that contain any non-digdit chars.

	cp = _gx_find_cell(_gx_get_expr_si(), r, c);
	if (GX_CELL_CONTAINS_ERROR(cp))
		_gx_function_error(GX_FN_ERR_CELL_ERROR);
	if (GX_CELL_CONTAINS_NUMBER(cp))
	{
		*vp = cp->value.number;
		status = 1;
	}
	else if (GX_CELL_CONTAINS_TEXT(cp))
	{
		LPCTSTR p = cp->value.string;
		int n = 0; 
		switch (cp->value_type)
		{
		case GX_VALUE_STRING:
			p = cp->value.string;
			while (*p == _T(' '))
				p++;
			if (*p == _T('-'))
				p++;
			status = _istdigit(*p);
			if (status)
				*vp = _gxttof(cp->value.string);
			break;
		case GX_VALUE_SHORT_STRING:
			p = cp->value.short_string;
			while (*p == _T(' ') && n < 8/sizeof(TCHAR))
				p++, n++;
			if (*p == _T('-'))
				p++, n++;;
			status = n < 8/sizeof(TCHAR) && _istdigit(*p);
			if (status)
			{
				TCHAR sbuf[10];
				_gx_xs_short_strcpy(sbuf, cp->value.short_string, TRUE);
				*vp = _gxttof(sbuf);
			}
			break;
		}
	}
	else
		status = 0;
	return status;
}

int __cdecl _gx_fn_get_string(int r, int c, LPTSTR sbuf)
{
	gxCell *cp;
	int status;

	cp = _gx_find_cell(_gx_get_expr_si(), r, c);
	if (GX_CELL_CONTAINS_ERROR(cp))
		_gx_function_error(GX_FN_ERR_CELL_ERROR);
	if (GX_CELL_CONTAINS_TEXT(cp))
	{
		switch (cp->value_type)
		{
		case GX_VALUE_STRING:
			// QA: 31989 - #if Secure Code Cleanup.
			_tcscpy(sbuf, cp->value.string);
			break;
		case GX_VALUE_SHORT_STRING:
			_gx_xs_short_strcpy(sbuf, cp->value.short_string, TRUE);
			break;
		default:
			assert(GX_CELL_CONTAINS_TEXT(cp));
		}
		status = 1;
	}
	else
		status = 0;
	return status;
}


void  __cdecl _gx_fn_xsstrcpy(LPTSTR dst, LPCTSTR src, int n)
{
	register int count = 0;
	--n;
	while ((*dst++ = *src++) != 0)
	{
		if (++count >= n)
		{
			dst[count - 1] = _T('\0');
			_gx_function_error(GX_FN_ERR_STR_TOO_LONG);
		}
	}
}

void  __cdecl _gx_fn_xsstrcat(LPTSTR dst, LPCTSTR src, int n)
{
	register int count = 0;
	while (*dst++)
		++count;
	if (count >= n)
		_gx_function_error(GX_FN_ERR_STR_TOO_LONG);
	--n;
	--dst;
	--count;
	while ((*dst++ = *src++) != 0)
	{
		if (++count >= n)
		{
			dst[count - 1] = _T('\0');
			_gx_function_error(GX_FN_ERR_STR_TOO_LONG);
		}
	}
}

void __cdecl _gx_eval_error(int code, LPTSTR fn_name);   // see _gx_expr_eval.c

void  __cdecl _gx_function_error(int code)
{
	_gx_clean_fn_args();
	_gx_eval_error(code, _gx_get_xs_fn_name());
}

void  __cdecl _gx_propagate_error(gxOperand * argv)
{
	_gx_eval_error(argv->val.err.code, argv->val.err.fn);
}

void  __cdecl _gx_clean_fn_args(void)
{
	int i;
	gxOperand *argv = _gx_get_fn_arg_ptr();

	if (argv != NULL)
	{
		for (i = 1; i < argv[0].val.count + 1; i++)
			if (argv[i].type == GX_STRING)
				GX_XSfree(argv[i].val.string);

		_gx_set_fn_arg_ptr(NULL);
	}
}
