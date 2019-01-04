/////////////////////////////////////////////////////////////////////////////////
// fnmath.cpp
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

#define acosh cosh
#define asinh sinh
#define atanh tanh

double __cdecl _gx_lgamma(double arg);  // _gx_lgamma.c
double __cdecl _gx_drand48();   // _gx_drand48.c

#define gamma _gx_lgamma

/*
double  atanh();
double  acosh();
double  asinh();
double  gamma();
*/

gxOperand __cdecl _gx_fn_abs(gxOperand argv[])
{
	gxOperand op;
	op.val.number = fabs(_gx_get_one_number(argv));
	op.type = GX_NUMBER;
	return op;
}

gxOperand __cdecl _gx_fn_acos(gxOperand argv[])
{
	gxOperand op;
	gxNumber x;
	x = _gx_get_one_number(argv);
	if ((x < -1.0) || (x > 1.0))
		_gx_function_error(GX_FN_ERR_DOMAIN_M1_1);
	op.val.number = acos(x);
	op.type = GX_NUMBER;
	return op;
}

gxOperand __cdecl _gx_fn_asin(gxOperand argv[])
{
	gxOperand op;
	gxNumber x;
	x = _gx_get_one_number(argv);
	if ((x < -1.0) || (x > 1.0))
		_gx_function_error(GX_FN_ERR_DOMAIN_M1_1);
	op.val.number = asin(x);
	op.type = GX_NUMBER;
	return op;
}

gxOperand __cdecl _gx_fn_atan(gxOperand argv[])
{
	gxOperand op;
	op.val.number = atan(_gx_get_one_number(argv));
	op.type = GX_NUMBER;
	return op;
}

gxOperand __cdecl _gx_fn_atan2(gxOperand argv[])
{
	gxOperand op;
	if (argv->val.count != 2)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 1);
	_gx_cvt2constant(argv + 2);
	if ((argv[1].type != GX_NUMBER) || (argv[2].type != GX_NUMBER))
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	if (argv[1].val.number == 0.0 && argv[2].val.number == 0.0)
		_gx_function_error(GX_FN_ERR_1_ARG_NE_0);
	op.val.number = atan2(argv[2].val.number, argv[1].val.number);
	op.type = GX_NUMBER;
	return op;
}

gxOperand __cdecl _gx_fn_cos(gxOperand argv[])
{
	gxOperand op;
	op.val.number = cos(_gx_get_one_number(argv));
	op.type = GX_NUMBER;
	return op;
}

gxOperand __cdecl _gx_fn_degrees(gxOperand argv[])
{
	gxOperand op;
	op.val.number = _gx_get_one_number(argv) * 180. / GX_M_PI;
	op.type = GX_NUMBER;
	return op;
}

gxOperand __cdecl _gx_fn_exp(gxOperand argv[])
{
	gxOperand op;
	errno = 0;
	op.val.number = exp(_gx_get_one_number(argv));
	if (errno)
		_gx_function_error(GX_FN_ERR_FLOAT);
	op.type = GX_NUMBER;
	return op;
}

gxOperand __cdecl _gx_fn_int(gxOperand argv[])
{
	gxOperand op;
	gxNumber x;
	x = _gx_get_one_number(argv);
	op.val.number = x > 0. ? floor(x) : ceil(x);
	op.type = GX_NUMBER;
	return op;
}

gxOperand __cdecl _gx_fn_ln(gxOperand argv[])
{
	gxOperand op;
	gxNumber x;
	x = _gx_get_one_number(argv);
	if (x <= 0.0)
		_gx_function_error(GX_FN_ERR_DOMAIN_GT_0);
	op.val.number = log(x);
	op.type = GX_NUMBER;
	return op;
}

gxOperand __cdecl _gx_fn_log2(gxOperand argv[])
{
	gxOperand op;
	gxNumber x;
	x = _gx_get_one_number(argv);
	if (x <= 0.0)
		_gx_function_error(GX_FN_ERR_DOMAIN_GT_0);
	op.val.number = log(x) / GX_M_LN2;
	op.type = GX_NUMBER;
	return op;
}

gxOperand __cdecl _gx_fn_log(gxOperand argv[])
{
	gxOperand op;
	gxNumber x;
	x = _gx_get_one_number(argv);
	if (x <= 0.0)
		_gx_function_error(GX_FN_ERR_DOMAIN_GT_0);
	op.val.number = log10(x);
	op.type = GX_NUMBER;
	return op;
}

gxOperand __cdecl _gx_fn_mod(gxOperand argv[])
{
	gxOperand op;
	gxNumber x,
			 y;
	if (argv->val.count != 2)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 1);
	_gx_cvt2constant(argv + 2);
	if ((argv[1].type != GX_NUMBER) || (argv[2].type != GX_NUMBER))
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	if (argv[2].val.number == 0.)
		_gx_function_error(GX_FN_ERR_DIV_0);
	x = argv[1].val.number;
	y = argv[2].val.number;
	op.val.number = x - y * floor(x / y);   /* Knuth Vol 1, p. 38 */
	if ((x < 0.0) ^ (y < 0.0)) // (x < 0.0 ^ y < 0.0) 
		op.val.number -= y; /* this makes it Lotus mod compatible */
	op.type = GX_NUMBER;
	return op;
}

gxOperand __cdecl _gx_fn_modulus(gxOperand argv[])
{
	gxOperand op;
	gxNumber x,
			 y;
	if (argv->val.count != 2)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 1);
	_gx_cvt2constant(argv + 2);
	if ((argv[1].type != GX_NUMBER) || (argv[2].type != GX_NUMBER))
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	if (argv[2].val.number == 0.)
		_gx_function_error(GX_FN_ERR_DIV_0);
	x = argv[1].val.number;
	y = argv[2].val.number;
	op.val.number = x - y * floor(x / y);   /* Knuth Vol 1, p. 38 */
	op.type = GX_NUMBER;
	return op;
}

gxOperand __cdecl _gx_fn_pi(gxOperand argv[])
{
	gxOperand op;
	if (argv->val.count)
		_gx_function_error(GX_FN_ERR_NO_ARGS);
	op.val.number = GX_M_PI;
	op.type = GX_NUMBER;
	return op;
}

gxOperand __cdecl _gx_fn_radians(gxOperand argv[])
{
	gxOperand op;
	op.val.number = _gx_get_one_number(argv) * GX_M_PI / 180;
	op.type = GX_NUMBER;
	return op;
}

#if _MFC_VER >= 0x0300
gxOperand __cdecl _gx_fn_rand(gxOperand argv[])
{
	gxOperand op;
	if (argv->val.count)
		_gx_function_error(GX_FN_ERR_NO_ARGS);
	op.val.number = _gx_drand48();
	op.type = GX_NUMBER;
	return op;
}
#endif

gxOperand __cdecl _gx_fn_round(gxOperand argv[])
{
	gxOperand op;
	int places;
	gxNumber x,
			 y;
	if (argv->val.count != 2)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 1);
	_gx_cvt2constant(argv + 2);
	if ((argv[1].type != GX_NUMBER) || (argv[2].type != GX_NUMBER))
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	places = (int) argv[2].val.number;
	if ((places < -15) || (places > 15))
		_gx_function_error(GX_FN_ERR_PLACES_M15_15);
	x = argv[1].val.number;
	y = pow(10., (double) places);
	op.val.number = x > 0. ? floor(x * y + 0.5) / y : ceil(x * y - 0.5) / y;
	op.type = GX_NUMBER;
	return op;
}

gxOperand __cdecl _gx_fn_sin(gxOperand argv[])
{
	gxOperand op;
	op.val.number = sin(_gx_get_one_number(argv));
	op.type = GX_NUMBER;
	return op;
}

gxOperand __cdecl _gx_fn_sqrt(gxOperand argv[])
{
	gxOperand op;
	gxNumber x;
	x = _gx_get_one_number(argv);
	if (x < 0.)
		_gx_function_error(GX_FN_ERR_ARG_IS_NEG);
	op.val.number = sqrt(x);
	op.type = GX_NUMBER;
	return op;
}

gxOperand __cdecl _gx_fn_tan(gxOperand argv[])
{
	gxOperand op;
	op.val.number = tan(_gx_get_one_number(argv));
	op.type = GX_NUMBER;
	return op;
}

/*
  Functions below this point are XS exclusives!
*/

gxOperand __cdecl _gx_fn_frac(gxOperand argv[])
{
	gxOperand op;
	gxNumber x;
	x = _gx_get_one_number(argv);
	op.val.number = x - (x > 0. ? floor(x) : ceil(x));
	op.type = GX_NUMBER;
	return op;
}

gxOperand __cdecl _gx_fn_ceil(gxOperand argv[])
{
	gxOperand op;
	op.val.number = ceil(_gx_get_one_number(argv));
	op.type = GX_NUMBER;
	return op;
}

gxOperand __cdecl _gx_fn_floor(gxOperand argv[])
{
	gxOperand op;
	op.val.number = floor(_gx_get_one_number(argv));
	op.type = GX_NUMBER;
	return op;
}

/* vector length */
gxOperand __cdecl _gx_fn_veclen(gxOperand argv[])
{
	gxNumber sum2,
			 x;
	gxOperand op;
	int i,
		n = argv->val.count;
	unsigned r,
		c;

	sum2 = 0.;
	for (i = 0; i < n; i++)
		switch ((++argv)->type)
		{
		case GX_NUMBER:
			x = argv->val.number;
			sum2 += x * x;
			break;
		case GX_CELL:
			if (_gx_fn_get_value(argv->val.range.r0,
								 argv->val.range.c0, &x))
				sum2 += x * x;
			break;
		case GX_RANGE:
			for (r = argv->val.range.r0;
				 r <= argv->val.range.r1; r++)
				for (c = argv->val.range.c0;
					 c <= argv->val.range.c1; c++)
					if (_gx_fn_get_value(r, c, &x))
						sum2 += x * x;
			break;
		case GX_OP_ERROR:
			_gx_propagate_error(argv);
		default:
			break;
		}
	op.type = GX_NUMBER;
	op.val.number = sqrt(sum2);
	return op;
}

#if _MFC_VER >= 0x0300
/* pseudo-gaussian random number */
gxOperand __cdecl _gx_fn_grand(gxOperand argv[])
{
	gxOperand op;
	register int i;
	gxNumber x = 0.;
	if (argv->val.count)
		_gx_function_error(GX_FN_ERR_NO_ARGS);
	for (i = 0; i < 12; i++)
		x += _gx_drand48();
	op.val.number = x - 6.0;
	op.type = GX_NUMBER;
	return op;
}
#endif

gxOperand __cdecl _gx_fn_cosh(gxOperand argv[])
{
	gxOperand op;
	errno = 0;
	op.val.number = cosh(_gx_get_one_number(argv));
	if (errno)
		_gx_function_error(GX_FN_ERR_FLOAT);
	op.type = GX_NUMBER;
	return op;
}

gxOperand __cdecl _gx_fn_sinh(gxOperand argv[])
{
	gxOperand op;
	errno = 0;
	op.val.number = sinh(_gx_get_one_number(argv));
	if (errno)
		_gx_function_error(GX_FN_ERR_FLOAT);
	op.type = GX_NUMBER;
	return op;
}

gxOperand __cdecl _gx_fn_tanh(gxOperand argv[])
{
	gxOperand op;
	op.val.number = tanh(_gx_get_one_number(argv));
	op.type = GX_NUMBER;
	return op;
}

gxOperand __cdecl _gx_fn_acosh(gxOperand argv[])
{
	gxOperand op;
	gxNumber x;
	x = _gx_get_one_number(argv);
	if (x < 1.0)
		_gx_function_error(GX_FN_ERR_DOMAIN_GE_1);
	op.val.number = acosh(x);
	op.type = GX_NUMBER;
	return op;
}

gxOperand __cdecl _gx_fn_asinh(gxOperand argv[])
{
	gxOperand op;
	gxNumber x;
	x = _gx_get_one_number(argv);
	op.val.number = asinh(x);
	op.type = GX_NUMBER;
	return op;
}

gxOperand __cdecl _gx_fn_atanh(gxOperand argv[])
{
	gxOperand op;
	gxNumber x;
	x = _gx_get_one_number(argv);
	if ((x <= -1.0) || (x >= 1.0))
		_gx_function_error(GX_FN_ERR_DOMAIN_M1_1_NE);
	op.val.number = atanh(x);
	op.type = GX_NUMBER;
	return op;
}

gxOperand __cdecl _gx_fn_dot(gxOperand argv[])
{
	gxOperand op;
	gxRange range1,
			range2;
	gxNumber x,
			 y,
			 sum;
	int dr1,
		dr2,
		dc1,
		dc2,
		r,
		c;

	sum = 0.;
	if (argv->val.count != 2)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	if (!(argv[1].type == GX_RANGE && argv[2].type == GX_RANGE))
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	range1 = argv[1].val.range;
	range2 = argv[2].val.range;
	dr1 = range1.r1 - range1.r0;
	dr2 = range2.r1 - range2.r0;
	dc1 = range1.c1 - range1.c0;
	dc2 = range2.c1 - range2.c0;
	if (dr1 == dr2 && dc1 == dc2)
	{   /* same dimensions */
		for (r = 0; r <= dr1; r++)
			for (c = 0; c <= dc1; c++)
			{
				if (!_gx_fn_get_value(range1.r0 + r, range1.c0 + c, &x))
					x = 0.;
				if (!_gx_fn_get_value(range2.r0 + r, range2.c0 + c, &y))
					y = 0.;
				sum += x * y;
			}
	}
	else if (dr1 == 0 && dc2 == 0 && dr2 == dc1)
	{
		for (c = 0; c <= dc1; c++)
		{
			if (!_gx_fn_get_value(range1.r0, range1.c0 + c, &x))
				x = 0.;
			if (!_gx_fn_get_value(range2.r0 + c, range2.c0, &y))
				y = 0.;
			sum += x * y;
		}
	}
	else if (dc1 == 0 && dr2 == 0 && dc2 == dr1)
	{
		for (r = 0; r <= dr1; r++)
		{
			if (!_gx_fn_get_value(range1.r0 + r, range1.c0, &x))
				x = 0.;
			if (!_gx_fn_get_value(range2.r0, range2.c0 + r, &y))
				y = 0.;
			sum += x * y;
		}
	}
	else
		_gx_function_error(GX_FN_ERR_RANGE_DIMS);
	op.type = GX_NUMBER;
	op.val.number = sum;
	return op;
}

gxOperand __cdecl _gx_fn_poly(gxOperand argv[])
{
	gxOperand op;
	gxNumber x = 0,
			 y,
			 sum;
	int i,
		n = argv->val.count;
	unsigned r,
		c;

	if (n < 2)
		_gx_function_error(GX_FN_ERR_ARG_CNT_LT_2);
	sum = 0.;
	switch ((++argv)->type)
	{
	case GX_NUMBER:
		x = argv->val.number;
		break;
	case GX_CELL:
		if (!_gx_fn_get_value(argv->val.range.r0,
							  argv->val.range.c0, &x))
			x = 0.0;
		break;
	case GX_OP_ERROR:
		_gx_propagate_error(argv);
	default:
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	}
	for (i = 1; i < n; i++)
		switch ((++argv)->type)
		{
		case GX_NUMBER:
			sum = sum * x + argv->val.number;
			break;
		case GX_CELL:
			if (!_gx_fn_get_value(argv->val.range.r0,
								  argv->val.range.c0, &y))
				_gx_function_error(GX_FN_ERR_IMPROP_COEF_TYPE);
			sum = sum * x + y;
			break;
		case GX_RANGE:
			for (r = argv->val.range.r0;
				 r <= argv->val.range.r1; r++)
				for (c = argv->val.range.c0;
					 c <= argv->val.range.c1; c++)
				{
					if (!_gx_fn_get_value(r, c, &y))
						_gx_function_error(GX_FN_ERR_IMPROP_COEF_TYPE);
					sum = sum * x + y;
				}
			break;
		case GX_OP_ERROR:
			_gx_propagate_error(argv);
		default:
			_gx_function_error(GX_FN_ERR_IMPROP_COEF_TYPE);
		}
	op.type = GX_NUMBER;
	op.val.number = sum;
	return op;
}

gxOperand __cdecl _gx_fn_sigmoid(gxOperand argv[])
{
	gxOperand op;
	op.val.number = 1. / (1. + exp(_gx_get_one_number(argv)));
	op.type = GX_NUMBER;
	return op;
}

gxOperand __cdecl _gx_fn_gamma(gxOperand argv[])
{
	gxOperand op;
	double _gx_gammalog(),
		   x;
	x = _gx_get_one_number(argv);
	if (x <= 0.0)
		_gx_function_error(GX_FN_ERR_DOMAIN_GT_0);
	errno = 0;
#ifdef OLD_MATH
	op.val.number = exp(_gx_gammalog(x));
#else
	op.val.number = exp(gamma(x));
#endif
	if (errno)
		_gx_function_error(GX_FN_ERR_FLOAT);
	op.type = GX_NUMBER;
	return op;
}

gxOperand __cdecl _gx_fn_lngamma(gxOperand argv[])
{
	gxOperand op;
	double _gx_gammalog(),
		   x;
	x = _gx_get_one_number(argv);
	if (x <= 0.0)
		_gx_function_error(GX_FN_ERR_DOMAIN_GT_0);
#ifdef OLD_MATH
	op.val.number = _gx_gammalog(x);
#else
	op.val.number = gamma(x);
#endif
	op.type = GX_NUMBER;
	return op;
}

gxOperand __cdecl _gx_fn_fact(gxOperand argv[])
{
	gxOperand op;
	double _gx_gammalog(),
		   x,
		   fact;
	x = _gx_get_one_number(argv);
#ifdef VAX
	if (x < 0.0 || x > 33.0)
		_gx_function_error(GX_FN_ERR_DOMAIN_0_33);
#else
	if (x < 0.0 || x > 170.0)
		_gx_function_error(GX_FN_ERR_DOMAIN_0_170);
#endif
	if (floor(x) != x)
		_gx_function_error(GX_FN_ERR_ARG_INT);
	if (x > 20)
	{
#ifdef OLD_MATH
		fact = exp(_gx_gammalog(x + 1.0));
#else
		fact = exp(gamma(x + 1.0));
#endif
	}
	else
	{
		fact = 1.0;
		while (x > 1.0)
		{
			fact *= x;
			x -= 1.0;
		}
	}
	op.val.number = fact;
	op.type = GX_NUMBER;
	return op;
}
