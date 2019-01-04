///////////////////////////////////////////////////////////////////////////////
// fnexcel.cpp: Excel worksheet functions
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

gxOperand __cdecl _gx_fn_intersect(gxOperand argv[])
{
	gxOperand op;

	if (argv->val.count != 2)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	if (argv[1].type != GX_RANGE || argv[2].type != GX_RANGE)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	op.type = GX_RANGE;
	if (!_gx_intersection(&argv[1].val.range, &argv[2].val.range, &op.val.range))
		op.type = GX_OP_NA;
	return op;
}


gxOperand __cdecl _gx_fn_na(gxOperand argv[])
{
	gxOperand op;

	if (argv->val.count)
		_gx_function_error(GX_FN_ERR_NO_ARGS);
	op.type = GX_OP_NA;
	return op;
}


gxOperand __cdecl _gx_fn_iserr(gxOperand argv[])
{
	gxOperand op;

	if (argv->val.count != 1)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	op.type = GX_NUMBER;
	op.val.number = (argv[1].type == GX_OP_ERROR) ? 1 : 0;
	return op;
}


gxOperand __cdecl _gx_fn_index(gxOperand argv[])
{
	gxOperand op;

	if ((argv->val.count >= 1) && (argv[1].type != GX_RANGE))
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);

	switch (argv->val.count)
	{
	case 1:
		return argv[1];
	case 3:
		_gx_cvt2constant(argv + 3);
		if (argv[3].type != GX_NUMBER)
			_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
		/* fall through */
	case 2:
		_gx_cvt2constant(argv + 2);
		if (argv[2].type != GX_NUMBER)
			_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
		break;
	default:
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
		break;
	}

	op.type = GX_CELL;
	op.val.range = argv[1].val.range;
	op.val.range.cell_only = 1;

	if (argv->val.count == 2)
	{
		if (argv[1].val.range.r0 == argv[1].val.range.r1)
			op.val.range.c0 += (int) argv[2].val.number - 1;
		else if (argv[1].val.range.c0 == argv[1].val.range.c1)
			op.val.range.r0 += (int) argv[2].val.number - 1;
		else
			_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	}
	else
	{   /* (argv->val.count == 3) */
		if ((argv[2].val.number == 0) && (argv[3].val.number == 0))
			_gx_function_error(GX_FN_ERR_INDEX_OPS_EQ_0);
		else if (argv[2].val.number == 0)
		{
			op.type = GX_RANGE;
			op.val.range.cell_only = 0;
			op.val.range.c0 += (int) argv[3].val.number - 1;
			op.val.range.c1 = op.val.range.c0;
		}
		else if (argv[3].val.number == 0)
		{
			op.type = GX_RANGE;
			op.val.range.cell_only = 0;
			op.val.range.r0 += (int) argv[2].val.number - 1;
			op.val.range.r1 = op.val.range.r0;
		}
		else
		{
			op.val.range.r0 += (int) argv[2].val.number - 1;
			op.val.range.c0 += (int) argv[3].val.number - 1;
		}
	}

	if (!GX_IN_RANGE(argv[1].val.range, op.val.range.r0, op.val.range.c0))
		_gx_function_error(GX_FN_ERR_ARG_OUT_OF_RNG);

	return op;
}



static LPCTSTR format_info[] =    /* This depends on the values of the FMT_*
								 * defines */
{  /* in cell.h                       */
	_T("G"),
	_T("S2"),
	_T("F2"),
	_T("G"),
	_T("C0"),
	_T(",0"),
	_T("G"),
	_T("G"),
	_T("D1"),
	_T("D2"),
	_T("D3"),
	_T("D1"),
	_T("G"),
	_T("D8"),
	_T("P0"),
	_T("G"),
	_T("C0"),
	_T("C0"),
	_T("C0"),
	_T("C0"),
	_T("D4"),
	_T("D1")
};

/* The initializers for this array are incorrect - TKM
static char just_info[] =   / * This depends on the values of the FMT_* defines * /
		{           / * in cell.h                      * /
		"\"\"",
		"'",
		"\"",
		"",
		"\"\""
		};
*/

gxOperand __cdecl _gx_fn_cellinfo(gxOperand argv[])
{
	gxOperand op;
	gxCellValue cval;

	if (argv->val.count != 2)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 1);
	if (argv[1].type != GX_STRING || (argv[2].type != GX_RANGE && argv[2].type != GX_CELL))
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);

	_gx_convert_lower(argv[1].val.string);
	op.type = GX_NUMBER;

/*  if (_tcscmp(argv[1].val.string, "width") == 0)
				op.val.number = get_column_width (_gx_get_expr_si(), argv[2].val.range.c0);
			else */ if (_tcscmp(argv[1].val.string, _T("row")) == 0)
		op.val.number = argv[2].val.range.r0;
	else if (_tcscmp(argv[1].val.string, _T("col")) == 0)
		op.val.number = argv[2].val.range.c0;
//  else if (_tcscmp(argv[1].val.string, "protect") == 0)
//      op.val.number = (cprop.protect > PROTECT_LEVEL_0) ? 1 : 0;
	else if (_tcscmp(argv[1].val.string, _T("address")) == 0)
	{
		op.type = GX_STRING;
		op.val.string = _gx_xs_strdup(_gx_range_to_text(&argv[2].val.range));
	}
	else if (_tcscmp(argv[1].val.string, _T("contents")) == 0)
		op = argv[2];
/*  else if (_tcscmp(argv[1].val.string, "format") == 0)
				{
				op.type = GX_STRING;
				op.val.string = _gx_xs_strdup (format_info[cprop.format]);
				}
		else if (_tcscmp(argv[1].val.string, "prefix") == 0)
				{
				op.type = GX_STRING;
				op.val.string = _gx_xs_strdup (format_info[cprop.just]);
				}
	 */
	else if (_tcscmp(argv[1].val.string, _T("type")) == 0)
	{
		_gx_get_cell_value(_gx_get_expr_si(), argv[2].val.range.r0, argv[2].val.range.c0, &cval);
		op.type = GX_STRING;
		switch (cval.type)
		{
		case GX_VALUE_NONE:
			op.val.string = _gx_xs_strdup(_T("b"));
			break;
		case GX_VALUE_STRING:
		case GX_VALUE_SHORT_STRING:
			op.val.string = _gx_xs_strdup(_T("l"));
			break;
		default:
			op.val.string = _gx_xs_strdup(_T("v"));
			break;
		}
	}
//  else if (_tcscmp(argv[1].val.string, "color") == 0)
//      op.val.number = 0;
	else
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_VALUE);

	return op;
}
