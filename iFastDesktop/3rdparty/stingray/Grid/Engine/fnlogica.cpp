///////////////////////////////////////////////////////////////////////////////
// fnlogica.cpp: Logic worksheet functions
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

gxOperand __cdecl _gx_fn_true(gxOperand argv[])
{
	gxOperand op;

	if (argv->val.count != 0)
		_gx_function_error(GX_FN_ERR_NO_ARGS);
	op.val.number = 1;
	op.type = GX_NUMBER;
	return op;
}

gxOperand __cdecl _gx_fn_false(gxOperand argv[])
{
	gxOperand op;

	if (argv->val.count != 0)
		_gx_function_error(GX_FN_ERR_NO_ARGS);
	op.val.number = 0;
	op.type = GX_NUMBER;
	return op;
}

gxOperand __cdecl _gx_fn_if(gxOperand argv[])
{
	gxOperand op;
	LPTSTR expr_sbuf = _gx_get_expr_sbuf();

/*
		if (argv->val.count != 3)
				_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
*/
	_gx_cvt2constant(argv + 1);
	if (argv[1].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	op = (argv[1].val.number != 0.0)
		? _gx_do_eval(argv[2].val.etree.nbuf, argv[2].val.etree.start)
		: _gx_do_eval(argv[3].val.etree.nbuf, argv[3].val.etree.start);
	/* if (op.type == GX_STRING || op.type == GX_OP_ERROR) */
	if (op.type == GX_STRING)
	{
		// QA: 31989 - #if Secure Code Cleanup.
		_tcscpy(expr_sbuf, op.val.string);
		GX_XSfree(op.val.string);
		op.val.string = expr_sbuf;
	}
	return op;
}

gxOperand __cdecl _gx_fn_isnumber(gxOperand argv[])
{
	gxOperand op;

	if (argv->val.count != 1)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 1);
	if (argv[1].type == GX_RANGE)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	op.val.number = argv[1].type == GX_NUMBER;
	op.type = GX_NUMBER;
	return op;
}

gxOperand __cdecl _gx_fn_isstring(gxOperand argv[])
{
	gxOperand op;

	if (argv->val.count != 1)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 1);
	if (argv[1].type == GX_RANGE)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	op.val.number = argv[1].type == GX_STRING;
	op.type = GX_NUMBER;
	return op;
}

gxOperand __cdecl _gx_fn_fileexists(gxOperand argv[])
{
	gxOperand op;
	FILE *fp;

	if (argv->val.count != 1)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 1);
	if (argv[1].type != GX_STRING)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);

	// QA: 31989 - #if Secure Code Cleanup.
	if ((fp = _tfopen(argv[1].val.string, _T("r"))) != NULL)
	{
		fclose(fp);
		op.val.number = 1;
	}
	else
		op.val.number = 0;
	op.type = GX_NUMBER;
	return op;
}

gxOperand __cdecl _gx_fn_iserror(gxOperand argv[])
{
	gxOperand op,
			  result;
	gxCell *cp;

	if (argv->val.count != 1)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);

	result = _gx_do_eval_et(argv[1].val.etree.nbuf, argv[1].val.etree.start);

	op.type = GX_NUMBER;

	switch (result.type)
	{
#ifdef CELLRANGE
	case GX_RANGE:
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	case GX_CELL:
		cp = _gx_find_cell(_gx_get_expr_si(), result.val.range.r0, result.val.range.c0);
		op.val.number = GX_CELL_CONTAINS_ERROR(cp) ? 1 : 0;
		break;
#endif
	case GX_OP_ERROR:
		op.val.number = 1;
		break;
	default:
		op.val.number = 0;
	}

	return op;
}
