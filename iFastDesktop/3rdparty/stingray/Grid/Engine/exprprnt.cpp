///////////////////////////////////////////////////////////////////////////////
// exprprnt.cpp: Expression Printing
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

static LPCTSTR op_text[] =
{
	_T("+"), _T("-"), _T("+"), _T("-"), _T("*"), _T("/"), _T("**"), _T("%"), _T("&&"), _T("||"), _T("!"),
	_T("&"), _T("|"), _T("^"), _T("~"), _T("<<"), _T(">>"), _T("=="), _T("!="), _T("<"), _T(">"),
	_T("<="), _T(">="), _T("?"), _T(".."), _T("%")
};

static LPTSTR do_print(int, gxExprNode *, gxExprPointer, LPTSTR);

LPTSTR	__cdecl _gx_format_function_name(LPTSTR buf, LPCTSTR name, int add_parens)
{
	if (GXGetEngineState()->print_at_sign || *name == _T('@'))
	{
		// QA: 31989 - #if Secure Code Cleanup.
		_tcscpy(buf, _T("@"));
	}else
	{
		*buf = _T('\0');
	}
	// QA: 31989 - #if Secure Code Cleanup.
	_tcscat(buf, name);

	if (GXGetEngineState()->print_lc)
	{
		// QA: 31989 - #if Secure Code Cleanup.
		_tcslwr(buf);
	}

	if (add_parens && !GXGetEngineState()->print_at_sign)
	{   /* used in error messages */
		// QA: 31989 - #if Secure Code Cleanup.
		_tcscat(buf, _T("()"));
	}

	return buf;
}


/*---------------------------------------------------------------------------*/
/*  Print each of the components of a formula.                               */

void  __cdecl _gx_expr_print(int si, gxFormula * fm, LPTSTR tbuf)
{
	gxExprPointer dp;

	if (fm->expr_start == GX_ENULL)
	{
		// This happens when formulas are not found
		*tbuf = 0;
		return;
	}

	*(tbuf++) = _T('=');

	tbuf = do_print(si, fm->expression, fm->expr_start, tbuf);
	if (fm->cons_start != GX_ENULL)
	{
		*(tbuf++) = _T(';');
		tbuf = do_print(si, fm->expression, fm->cons_start, tbuf);
	}
	if (fm->depend_start != GX_ENULL && !GXGetEngineState()->print_lotus)
	{
		*(tbuf++) = _T('\\');
		for (dp = fm->depend_start; dp != GX_ENULL; dp = fm->expression[dp].right)
		{
			tbuf = do_print(si, fm->expression, dp, tbuf);
			if (fm->expression[dp].right != GX_ENULL)
				*tbuf++ = _T(',');
		}
	}
	if (fm->comment != NULL && !GXGetEngineState()->print_lotus)
	{
		*(tbuf++) = _T('/');
		*(tbuf++) = _T('/');
		// QA: 31989 - #if Secure Code Cleanup.
		_tcscpy(tbuf, fm->comment);

		while (*tbuf++)
			NULL;
		--tbuf;
	}
	*tbuf = _T('\0');
}

void __cdecl _gx_expr_only_print(int si, gxExprNode * expression, gxExprPointer expr_start, LPTSTR tbuf)
{
	tbuf = do_print(si, expression, expr_start, tbuf);
	*tbuf = _T('\0');
}


/*---------------------------------------------------------------------------*/
/*  Recursively print an expression.                                         */

static LPTSTR do_print(int si, gxExprNode * ebuf, gxExprPointer start, LPTSTR tbuf)
{
	assert(start != GX_ENULL);

	if (ebuf[start].has_parens)
		*(tbuf++) = _T('(');
	switch (ebuf[start].node_type)
	{
	case GX_OPERATOR_NODE:
		switch (ebuf[start].value.operator_)
		{
		case GX_PLUS:
		case GX_MINUS:
		case GX_MULTIPLY:
		case GX_DIVIDE:
		case GX_MODULUS:
		case GX_BOOLEAN_AND:
		case GX_BOOLEAN_OR:
		case GX_LESS_THAN:
		case GX_GREATER_THAN:
			tbuf = do_print(si, ebuf, ebuf[start].left, tbuf);
			*(tbuf++) = op_text[ebuf[start].value.operator_][0];
			tbuf = do_print(si, ebuf, ebuf[start].right, tbuf);
			break;

		case GX_BOOLEAN_XOR:
			tbuf = do_print(si, ebuf, ebuf[start].left, tbuf);
			if (GXGetEngineState()->print_lotus)
			{
				*(tbuf++) = _T('/');
				*(tbuf++) = _T('*');
				*(tbuf++) = _T('X');
				*(tbuf++) = _T('O');
				*(tbuf++) = _T('R');
				*(tbuf++) = _T('*');
				*(tbuf++) = _T('/');
			}
			else
				*(tbuf++) = op_text[ebuf[start].value.operator_][0];
			tbuf = do_print(si, ebuf, ebuf[start].right, tbuf);
			break;

		case GX_EQUAL:
		case GX_NOT_EQUAL:
		case GX_LOGICAL_AND:
		case GX_LOGICAL_OR:
		case GX_POWER:
		case GX_SHIFT_LEFT:
		case GX_SHIFT_RIGHT:
		case GX_LT_OR_EQUAL:
		case GX_GT_OR_EQUAL:
		case GX_JOINRANGE:
			tbuf = do_print(si, ebuf, ebuf[start].left, tbuf);
			if (GXGetEngineState()->print_lotus)
			{
				switch (ebuf[start].value.operator_)
				{
				case GX_EQUAL:
					*(tbuf++) = _T('=');
					break;
				case GX_POWER:
					*(tbuf++) = _T('^');
					break;
				case GX_NOT_EQUAL:
					*(tbuf++) = _T('<');
					*(tbuf++) = _T('>');
					break;
				case GX_LOGICAL_AND:
					*(tbuf++) = _T('#');
					*(tbuf++) = _T('A');
					*(tbuf++) = _T('N');
					*(tbuf++) = _T('D');
					*(tbuf++) = _T('#');
					break;
				case GX_LOGICAL_OR:
					*(tbuf++) = _T('#');
					*(tbuf++) = _T('O');
					*(tbuf++) = _T('R');
					*(tbuf++) = _T('#');
					break;
				default:
					*(tbuf++) = op_text[ebuf[start].value.operator_][0];
					*(tbuf++) = op_text[ebuf[start].value.operator_][1];
				}
			}
			else
			{
				*(tbuf++) = op_text[ebuf[start].value.operator_][0];
				*(tbuf++) = op_text[ebuf[start].value.operator_][1];
			}
			tbuf = do_print(si, ebuf, ebuf[start].right, tbuf);
			break;

		case GX_UNARY_PLUS:
		case GX_UNARY_MINUS:
		case GX_BOOLEAN_NOT:
			*(tbuf++) = op_text[ebuf[start].value.operator_][0];
			tbuf = do_print(si, ebuf, ebuf[start].right, tbuf);
			break;

		case GX_LOGICAL_NOT:
			if (GXGetEngineState()->print_lotus)
			{
				*(tbuf++) = _T('#');
				*(tbuf++) = _T('N');
				*(tbuf++) = _T('O');
				*(tbuf++) = _T('T');
				*(tbuf++) = _T('#');
			}
			else
				*(tbuf++) = op_text[ebuf[start].value.operator_][0];
			tbuf = do_print(si, ebuf, ebuf[start].right, tbuf);
			break;

		case GX_PERCENT:
			tbuf = do_print(si, ebuf, ebuf[start].right, tbuf);
			*(tbuf++) = op_text[ebuf[start].value.operator_][0];
			break;

		case GX_CONDITIONAL:
			tbuf = do_print(si, ebuf, ebuf[start].left, tbuf);
			*(tbuf++) = '?';
			tbuf = do_print(si, ebuf, ebuf[start].right, tbuf);
			break;

		case GX_ILLEGAL_OP:
			if (GXGetEngineState()->print_lotus)
			{
				*tbuf++ = _T('E');
				*tbuf++ = _T('R');
				*tbuf++ = _T('R');
			}
			else
			{
				*tbuf++ = _T('?');
				*tbuf++ = _T('?');
			}
			break;

		default:
			assert(0);
			break;
		}
		break;

	case GX_NUMBER_NODE:
/*
		if (ebuf[start].number_is_hex && !GXGetEngineState()->print_lotus)
		{
			//_stprintf(tbuf, _T("0x%X"), (int) ebuf[start].value.operand);
			_stprintf(tbuf, _T("%.14g"), ebuf[start].value.operand);
		}else
		{
			_stprintf(tbuf, _T("%.14g"), ebuf[start].value.operand);
		}
*/
		if (ebuf[start].number_is_hex && !GXGetEngineState()->print_lotus)
			_stprintf(tbuf, _T("0x%X"), (int) ebuf[start].value.operand);
		else
			_stprintf(tbuf, _T("%.14g"), ebuf[start].value.operand);
		while (*tbuf++)
			NULL;
		--tbuf;
		break;

	case GX_STRING_NODE:
		*tbuf++ = _T('"');
//          if (!_gx_get_context_ptr(si)->v2_string_mode)
		tbuf = _gx_xs_encode_string(tbuf, ebuf[start].value.string, 1);
/*          else
								{
								char *p = ebuf[start].value.string;
								while (*tbuf++ = *p++); --tbuf;
								}*/
		*tbuf++ = _T('"');
		break;

	case GX_CELL_NODE:
	case GX_RANGE_NODE:
		// QA: 31989 - #if Secure Code Cleanup.
		_tcscpy(tbuf, _gx_range_to_text(&ebuf[start].value.range));

		while (*tbuf++)
			NULL;
		--tbuf;
		break;

	case GX_NAME_NODE:
		// QA: 31989 - #if Secure Code Cleanup.
		_tcscpy(tbuf, ebuf[start].value.name);

		while (*tbuf++)
			NULL;
		--tbuf;
		break;

	case GX_NAMED_CELL_NODE:
	case GX_NAMED_RANGE_NODE:
		// QA: 31989 - #if Secure Code Cleanup.
		_tcscpy(tbuf, ebuf[start].value.rnp->name);

		while (*tbuf++)
			NULL;
		--tbuf;
		break;

	case GX_FUNCTION_NODE:
		_gx_format_function_name(tbuf, ebuf[start].value.fnp->name, 0);
		while (*tbuf++)
			NULL;
		--tbuf;
		if (ebuf[start].right != GX_ENULL)
		{   /* function has arguments */
			*tbuf++ = _T('(');
			tbuf = do_print(si, ebuf, ebuf[start].right, tbuf);
			*tbuf++ = _T(')');
		}
		else if (!GXGetEngineState()->print_at_sign)
		{
			*tbuf++ = _T('(');
			*tbuf++ = _T(')');
		}
		break;

	case GX_ARG_NODE:
		if (ebuf[ebuf[start].value.arg.back].node_type == GX_ARG_NODE)
			*tbuf++ = _T(',');
		tbuf = do_print(si, ebuf, ebuf[start].left, tbuf);
		if (ebuf[start].right != GX_ENULL)
			tbuf = do_print(si, ebuf, ebuf[start].right, tbuf);
		break;

	case GX_RELATIVE_NODE:
		*tbuf++ = _T('#');
		if (ebuf[start].value.rel.c_expr != GX_ENULL)
		{
			*tbuf++ = _T('{');
			tbuf = do_print(si, ebuf, ebuf[start].value.rel.c_expr, tbuf);
			if (ebuf[start].value.rel.r_expr != GX_ENULL)
			{
				*tbuf++ = _T(',');
				tbuf = do_print(si, ebuf, ebuf[start].value.rel.r_expr, tbuf);
			}
			*tbuf++ = _T('}');
		}
		break;

	case GX_EXTENSION_NODE:
		tbuf = do_print(si, ebuf, ebuf[start].left, tbuf);
		*tbuf++ = _T(':');
		tbuf = do_print(si, ebuf, ebuf[start].right, tbuf);
		break;
	}
	if (ebuf[start].has_parens)
		*(tbuf++) = _T(')');

	*tbuf = _T('\0');
	return tbuf;
}
