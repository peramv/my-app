///////////////////////////////////////////////////////////////////////////////
// fnlogic.cpp: Logic worksheet functions
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

#define     UNKNOWN     -1

#define CELLRANGE

static int logic_int(double x)
{
	if (_gx_xs_int_check(x))
		return UNKNOWN;
	else
		return (int) x;
}

static int compute_and(int x, int y)
{
	if (x == 0 || y == 0)
		return 0;
	if (x == 1 && y == 1)
		return 1;
	return UNKNOWN;
}

static int compute_or(int x, int y)
{
	if (x == 1 || y == 1)
		return 1;
	if (x == 0 && y == 0)
		return 0;
	return UNKNOWN;
}

static int compute_xor(int x, int y)
{
	if (x == 0 && y == 0)
		return 0;
	if (x == 1 && y == 1)
		return 0;
	if (x == 0 && y == 1)
		return 1;
	if (x == 1 && y == 0)
		return 1;
	return UNKNOWN;
}

static int compute_not(int x)
{
	if (x == 1)
		return 0;
	if (x == 0)
		return 1;
	return UNKNOWN;
}

gxOperand __cdecl _gx_fn_not(gxOperand argv[])
{
	gxOperand op;
	gxNumber x;
	int z = UNKNOWN;

	if (argv->val.count != 1)
		_gx_function_error(GX_FN_ERR_TOO_MANY_ARGS);

	switch ((++argv)->type)
	{
	case GX_NUMBER:
		z = compute_not(logic_int(argv->val.number));
		break;
#ifdef CELLRANGE
	case GX_CELL:
		if (_gx_fn_get_value(argv->val.range.r0,
							 argv->val.range.c0, &x))
			z = compute_not(logic_int(x));
		break;
#endif
	case GX_OP_ERROR:
		_gx_propagate_error(argv);
	default:
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	}
	op.type = GX_NUMBER;
	op.val.number = (gxNumber) z;
	return op;
}

gxOperand __cdecl _gx_fn_and(gxOperand argv[])
{
	gxOperand op;
	gxNumber x;
	int z = 1;
	int i,
		n = argv->val.count;
	unsigned r,
		c;

	for (i = 0; i < n; i++)
		switch ((++argv)->type)
		{
		case GX_NUMBER:
			z = compute_and(z, logic_int(argv->val.number));
			break;
#ifdef CELLRANGE
		case GX_CELL:
			if (_gx_fn_get_value(argv->val.range.r0,
								 argv->val.range.c0, &x))
				z = compute_and(z, logic_int(x));
			else
				z = compute_and(z, UNKNOWN);
			break;
		case GX_RANGE:
			for (r = argv->val.range.r0;
				 r <= argv->val.range.r1; r++)
				for (c = argv->val.range.c0;
					 c <= argv->val.range.c1; c++)
					if (_gx_fn_get_value(r, c, &x))
						z = compute_and(z, logic_int(x));
					else
						z = compute_and(z, UNKNOWN);
			break;
#endif
		case GX_OP_ERROR:
			_gx_propagate_error(argv);
		default:
			_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
		}
	op.type = GX_NUMBER;
	op.val.number = (gxNumber) z;
	return op;
}

gxOperand __cdecl _gx_fn_or(gxOperand argv[])
{
	gxOperand op;
	gxNumber x;
	int z = 0;
	int i,
		n = argv->val.count;
	unsigned r,
		c;

	for (i = 0; i < n; i++)
		switch ((++argv)->type)
		{
		case GX_NUMBER:
			z = compute_or(z, logic_int(argv->val.number));
			break;
#ifdef CELLRANGE
		case GX_CELL:
			if (_gx_fn_get_value(argv->val.range.r0,
								 argv->val.range.c0, &x))
				z = compute_or(z, logic_int(x));
			else
				z = compute_or(z, UNKNOWN);
			break;
		case GX_RANGE:
			for (r = argv->val.range.r0;
				 r <= argv->val.range.r1; r++)
				for (c = argv->val.range.c0;
					 c <= argv->val.range.c1; c++)
					if (_gx_fn_get_value(r, c, &x))
						z = compute_or(z, logic_int(x));
					else
						z = compute_or(z, UNKNOWN);
			break;
#endif
		case GX_OP_ERROR:
			_gx_propagate_error(argv);
		default:
			_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
		}
	op.type = GX_NUMBER;
	op.val.number = (gxNumber) z;
	return op;
}

gxOperand __cdecl _gx_fn_nand(gxOperand argv[])
{
	gxOperand op;
	gxNumber x;
	int z = 1;
	int i,
		n = argv->val.count;
	unsigned r,
		c;

	for (i = 0; i < n; i++)
		switch ((++argv)->type)
		{
		case GX_NUMBER:
			z = compute_and(z, logic_int(argv->val.number));
			break;
#ifdef CELLRANGE
		case GX_CELL:
			if (_gx_fn_get_value(argv->val.range.r0,
								 argv->val.range.c0, &x))
				z = compute_and(z, logic_int(x));
			else
				z = compute_and(z, UNKNOWN);
			break;
		case GX_RANGE:
			for (r = argv->val.range.r0;
				 r <= argv->val.range.r1; r++)
				for (c = argv->val.range.c0;
					 c <= argv->val.range.c1; c++)
					if (_gx_fn_get_value(r, c, &x))
						z = compute_and(z, logic_int(x));
					else
						z = compute_and(z, UNKNOWN);
			break;
#endif
		case GX_OP_ERROR:
			_gx_propagate_error(argv);
		default:
			_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
		}
	op.type = GX_NUMBER;
	op.val.number = (gxNumber) compute_not(z);
	return op;
}

gxOperand __cdecl _gx_fn_nor(gxOperand argv[])
{
	gxOperand op;
	gxNumber x;
	int z = 0;
	int i,
		n = argv->val.count;
	unsigned r,
		c;

	for (i = 0; i < n; i++)
		switch ((++argv)->type)
		{
		case GX_NUMBER:
			z = compute_or(z, logic_int(argv->val.number));
			break;
#ifdef CELLRANGE
		case GX_CELL:
			if (_gx_fn_get_value(argv->val.range.r0,
								 argv->val.range.c0, &x))
				z = compute_or(z, logic_int(x));
			else
				z = compute_or(z, UNKNOWN);
			break;
		case GX_RANGE:
			for (r = argv->val.range.r0;
				 r <= argv->val.range.r1; r++)
				for (c = argv->val.range.c0;
					 c <= argv->val.range.c1; c++)
					if (_gx_fn_get_value(r, c, &x))
						z = compute_or(z, logic_int(x));
					else
						z = compute_or(z, UNKNOWN);
			break;
#endif
		case GX_OP_ERROR:
			_gx_propagate_error(argv);
		default:
			_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
		}
	op.type = GX_NUMBER;
	op.val.number = (gxNumber) compute_not(z);
	return op;
}

gxOperand __cdecl _gx_fn_xor(gxOperand argv[])
{
	gxOperand op;
	gxNumber x;
	int z = 0;
	int i,
		n = argv->val.count;
	unsigned r,
		c;

	for (i = 0; i < n; i++)
		switch ((++argv)->type)
		{
		case GX_NUMBER:
			z = compute_xor(z, logic_int(argv->val.number));
			break;
#ifdef CELLRANGE
		case GX_CELL:
			if (_gx_fn_get_value(argv->val.range.r0,
								 argv->val.range.c0, &x))
				z = compute_xor(z, logic_int(x));
			else
				z = compute_xor(z, UNKNOWN);
			break;
		case GX_RANGE:
			for (r = argv->val.range.r0;
				 r <= argv->val.range.r1; r++)
				for (c = argv->val.range.c0;
					 c <= argv->val.range.c1; c++)
					if (_gx_fn_get_value(r, c, &x))
						z = compute_xor(z, logic_int(x));
					else
						z = compute_xor(z, UNKNOWN);
			break;
#endif
		case GX_OP_ERROR:
			_gx_propagate_error(argv);
		default:
			_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
		}
	op.type = GX_NUMBER;
	op.val.number = (gxNumber) z;
	return op;
}
