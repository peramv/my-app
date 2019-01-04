///////////////////////////////////////////////////////////////////////////////
// fnfina.cpp: Financial worksheet functions
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

#define OLD_MATH

#define CELLRANGE

double log1p();

gxOperand __cdecl _gx_fn_cterm(gxOperand argv[])
{
	gxOperand op;
	gxNumber rate,
			 fv,
			 pv,
			 fvopv;

	if (argv->val.count != 3)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 1);
	_gx_cvt2constant(argv + 2);
	_gx_cvt2constant(argv + 3);
	if (argv[1].type != GX_NUMBER || argv[2].type != GX_NUMBER ||
		argv[3].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_ARG_NUMERIC);
	rate = argv[1].val.number;
	fv = argv[2].val.number;
	pv = argv[3].val.number;
	if (rate < -1.0)
		_gx_function_error(GX_FN_ERR_R_INT_GT_NEG_1);
	if (rate == 0.0)
		_gx_function_error(GX_FN_ERR_R_NE_0);
	if (pv == 0.0 || fv == 0.0)
		_gx_function_error(GX_FN_ERR_PV_FV_NE_0);
	fvopv = fv / pv;
	if (fvopv < 0.0)
		_gx_function_error(GX_FN_ERR_PV_FV_SIGN);
	op.type = GX_NUMBER;
#ifdef OLD_MATH
	op.val.number = log(fvopv) / log(1.0 + rate);
#else
	op.val.number = log(fvopv) / log1p(rate);
#endif
	return op;
}

/* double declining balance */
gxOperand __cdecl _gx_fn_ddb(gxOperand argv[])
{
	gxOperand op;
	gxNumber cost,
			 salvage,
			 ddb = 0,
			 bv;
	int life,
		period;

	if (argv->val.count != 4)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 1);
	_gx_cvt2constant(argv + 2);
	_gx_cvt2constant(argv + 3);
	_gx_cvt2constant(argv + 4);
	if (argv[1].type != GX_NUMBER || argv[2].type != GX_NUMBER ||
		argv[3].type != GX_NUMBER || argv[4].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_ARG_NUMERIC);
	cost = argv[1].val.number;
	salvage = argv[2].val.number;
	life = _gx_cvt2int(argv[3].val.number);
	period = _gx_cvt2int(argv[4].val.number);
	if ((double) life != argv[3].val.number ||
		(double) period != argv[4].val.number)
		_gx_function_error(GX_FN_ERR_L_P_INT);
	if (life < period || period < 1)
		_gx_function_error(GX_FN_ERR_L_GE_P_GE_1);
	if (cost < salvage || salvage < 0.0)
		_gx_function_error(GX_FN_ERR_C_GE_S_GE_0);
	bv = cost;
	while (period--)
	{
		ddb = GX_MAX(2.0 * bv / life, 0.0);
		bv = GX_MAX(bv - ddb, salvage);
	}
	op.type = GX_NUMBER;
	op.val.number = ddb;
	return op;
}

gxOperand __cdecl _gx_fn_fv(gxOperand argv[])
{
#ifdef CELLRANGE
	gxOperand op;
	gxNumber pmt,
			 rate,
			 power,
			 nper;

	if (argv->val.count != 3)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 1);
	_gx_cvt2constant(argv + 2);
	_gx_cvt2constant(argv + 3);
	if (argv[1].type != GX_NUMBER || argv[2].type != GX_NUMBER ||
		argv[3].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_ARG_NUMERIC);
	pmt = argv[1].val.number;
	rate = argv[2].val.number;
	nper = argv[3].val.number;
	if (rate < -1.0)
		_gx_function_error(GX_FN_ERR_R_INT_GT_NEG_1);
	if (nper <= 0)
		_gx_function_error(GX_FN_ERR_P_INT_GT_0);
	op.type = GX_NUMBER;
	if (rate == 0.0)
		op.val.number = nper * pmt;
	else
	{
		errno = 0;
#ifdef OLD_MATH
		power = pow(1.0 + rate, nper);
#else
		power = exp(log1p(rate) * nper);
#endif
		op.val.number = pmt * (power - 1.0) / rate;
		if (errno)
			_gx_function_error(GX_FN_ERR_FLOAT);
	}
	return op;
#else
	gxOperand op;
	op.type = GX_NUMBER;
	_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	return op;
#endif
}

/* polynomial evaluation used by _gx_fn_irr */
static gxNumber poly(gxNumber c[], gxNumber x, int n)
{
	register int i;
	gxNumber sum = 0.0;
	for (i = 0; i < n; i++)
		sum = sum * x + c[i];
	return sum;
}

#define GX_MAXIT 50

/* Internal rate of return using Newton-Raphson */
/* with Ralston's modification          */
gxOperand __cdecl _gx_fn_irr(gxOperand argv[])
{
#ifdef CELLRANGE
	gxOperand op;
	gxMatrix m,
			 mprime,
			 m2prime;
	gxNumber x,
			 delta,
			 p,
			 pprime,
			 u,
			 uprime;
	unsigned r,
		c;
	int i,
		j,
		n;

	if (argv->val.count != 2)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 1);
	GX_HANDLE_OP_ERROR(argv[2]);
	if (argv[1].type != GX_NUMBER || argv[2].type != GX_RANGE)
		_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	x = argv[1].val.number + 1.0;
	m.r_dim = argv[2].val.range.r1 - argv[2].val.range.r0 + 1;
	m.c_dim = argv[2].val.range.c1 - argv[2].val.range.c0 + 1;
	mprime.r_dim = m2prime.r_dim = m.r_dim;
	mprime.c_dim = m2prime.c_dim = m.c_dim;
	n = m.r_dim * m.c_dim;
	if (n < 2)
		_gx_function_error(GX_FN_ERR_2_CASH_FLOWS);
	_gx_mkwm(&m);
	_gx_mkwm(&mprime);
	_gx_mkwm(&m2prime);

	i = 0;
	for (r = argv[2].val.range.r0; r <= argv[2].val.range.r1; r++, i++)
	{
		j = 0;
		for (c = argv[2].val.range.c0; c <= argv[2].val.range.c1; c++, j++)
			if (!_gx_fn_get_value(r, c, m.data + (i * m.c_dim + j)))
				m.data[i * m.c_dim + j] = 0.0;
	}

	for (i = 0; i < n; i++)
	{   /* compute 1st and 2nd derivatives of p(x) */
		mprime.data[i] = m.data[i] * (n - 1 - i);
		m2prime.data[i] = mprime.data[i] * (n - 2 - i);
	}
	for (i = 0; i < GX_MAXIT; i++)
	{   /* do no more than GX_MAXIT iterations */
		pprime = poly(mprime.data, x, n - 1);
		p = poly(m.data, x, n);
		u = p / pprime;
		uprime = 1.0 - u * poly(m2prime.data, x, n - 2) / pprime;
		delta = -u / uprime;
		x += delta;
		if (fabs(delta) < 1.0e-8)
			break;
	}
	if (i == GX_MAXIT)
		_gx_function_error(GX_FN_ERR_NO_REAL_ROOT);
	if (x < 0.0)
		_gx_function_error(GX_FN_ERR_R_LT_M1);
	op.type = GX_NUMBER;
	op.val.number = x - 1.0;
	_gx_cleanwm();
	return op;
#else
	gxOperand op;
	op.type = GX_NUMBER;
	_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	return op;
#endif
}

gxOperand __cdecl _gx_fn_pmt(gxOperand argv[])
{
#ifdef CELLRANGE
	gxOperand op;
	gxNumber pv,
			 rate,
			 power,
			 nper;

	if (argv->val.count != 3)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 1);
	_gx_cvt2constant(argv + 2);
	_gx_cvt2constant(argv + 3);
	if (argv[1].type != GX_NUMBER || argv[2].type != GX_NUMBER ||
		argv[3].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_ARG_NUMERIC);
	pv = argv[1].val.number;
	rate = argv[2].val.number;
	nper = argv[3].val.number;
	if (rate < -1.0)
		_gx_function_error(GX_FN_ERR_R_INT_GT_NEG_1);
	if (nper <= 0.0)
		_gx_function_error(GX_FN_ERR_P_INT_GT_0);
	op.type = GX_NUMBER;
	if (rate == 0.0)
		op.val.number = pv / nper;
	else
	{
		errno = 0;
#ifdef OLD_MATH
		power = pow(1.0 + rate, -nper);
#else
		power = exp(log1p(rate) * -nper);
#endif
		op.val.number = pv * rate / (1.0 - power);
		if (errno)
			_gx_function_error(GX_FN_ERR_FLOAT);
	}
	return op;
#else
	gxOperand op;
	op.type = GX_NUMBER;
	_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	return op;
#endif
}

gxOperand __cdecl _gx_fn_pv(gxOperand argv[])
{
#ifdef CELLRANGE
	gxOperand op;
	gxNumber pmt,
			 rate,
			 power,
			 nper;

	if (argv->val.count != 3)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 1);
	_gx_cvt2constant(argv + 2);
	_gx_cvt2constant(argv + 3);
	if (argv[1].type != GX_NUMBER || argv[2].type != GX_NUMBER ||
		argv[3].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_ARG_NUMERIC);
	pmt = argv[1].val.number;
	rate = argv[2].val.number;
	nper = argv[3].val.number;
	if (rate < -1.0)
		_gx_function_error(GX_FN_ERR_R_INT_GT_NEG_1);
	if (nper <= 0)
		_gx_function_error(GX_FN_ERR_P_INT_GT_0);
	op.type = GX_NUMBER;
	if (rate == 0.0)
		op.val.number = nper * pmt;
	else
	{
		errno = 0;
#ifdef OLD_MATH
		power = pow(1.0 + rate, -nper);
#else
		power = exp(log1p(rate) * -nper);
#endif
		op.val.number = pmt * (1.0 - power) / rate;
		if (errno)
			_gx_function_error(GX_FN_ERR_FLOAT);
	}
	return op;
#else
	gxOperand op;
	op.type = GX_NUMBER;
	_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	return op;
#endif
}

gxOperand __cdecl _gx_fn_rate(gxOperand argv[])
{
#ifdef CELLRANGE
	gxOperand op;
	gxNumber fv,
			 pv,
			 fvopv,
			 nper;

	if (argv->val.count != 3)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 1);
	_gx_cvt2constant(argv + 2);
	_gx_cvt2constant(argv + 3);
	if (argv[1].type != GX_NUMBER || argv[2].type != GX_NUMBER ||
		argv[3].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_ARG_NUMERIC);
	fv = argv[1].val.number;
	pv = argv[2].val.number;
	nper = argv[3].val.number;
	if (nper <= 0.0)
		_gx_function_error(GX_FN_ERR_P_INT_GT_0);
	if (pv == 0.0 || fv == 0.0)
		_gx_function_error(GX_FN_ERR_PV_FV_NE_0);
	fvopv = fv / pv;
	if (fvopv < 0.0)
		_gx_function_error(GX_FN_ERR_PV_FV_SIGN);
	op.type = GX_NUMBER;
	errno = 0;
	op.val.number = pow(fvopv, 1.0 / nper) - 1.0;
	if (errno)
		_gx_function_error(GX_FN_ERR_FLOAT);
	return op;
#else
	gxOperand op;
	op.type = GX_NUMBER;
	_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	return op;
#endif
}

/* straight line depreciation */
gxOperand __cdecl _gx_fn_sln(gxOperand argv[])
{
#ifdef CELLRANGE
	gxOperand op;
	gxNumber cost,
			 salvage,
			 life;

	if (argv->val.count != 3)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 1);
	_gx_cvt2constant(argv + 2);
	_gx_cvt2constant(argv + 3);
	if (argv[1].type != GX_NUMBER || argv[2].type != GX_NUMBER ||
		argv[3].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_ARG_NUMERIC);
	cost = argv[1].val.number;
	salvage = argv[2].val.number;
	life = argv[3].val.number;
	if (life <= 0.0)
		_gx_function_error(GX_FN_ERR_L_GT_0);
	if (cost < salvage || salvage < 0.0)
		_gx_function_error(GX_FN_ERR_C_GE_S_GE_0);
	op.type = GX_NUMBER;
	op.val.number = (cost - salvage) / life;
	return op;
#else
	gxOperand op;
	op.type = GX_NUMBER;
	_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	return op;
#endif
}

gxOperand __cdecl _gx_fn_syd(gxOperand argv[])
{
#ifdef CELLRANGE
	gxOperand op;
	gxNumber cost,
			 salvage,
			 life,
			 period;

	if (argv->val.count != 4)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 1);
	_gx_cvt2constant(argv + 2);
	_gx_cvt2constant(argv + 3);
	_gx_cvt2constant(argv + 4);
	if (argv[1].type != GX_NUMBER || argv[2].type != GX_NUMBER ||
		argv[3].type != GX_NUMBER || argv[4].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_ARG_NUMERIC);
	cost = argv[1].val.number;
	salvage = argv[2].val.number;
	life = argv[3].val.number;
	period = argv[4].val.number;
	if (life <= 0.0)
		_gx_function_error(GX_FN_ERR_L_GT_0);
	if (period < 0.0)
		_gx_function_error(GX_FN_ERR_P_GE_0);
	if (cost < salvage || salvage < 0.0)
		_gx_function_error(GX_FN_ERR_C_GE_S_GE_0);
	op.type = GX_NUMBER;
	op.val.number = (cost - salvage) * (life - period + 1.0) /
		(life * (life + 1.0) / 2.0);
	return op;
#else
	gxOperand op;
	op.type = GX_NUMBER;
	_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	return op;
#endif
}

gxOperand __cdecl _gx_fn_term(gxOperand argv[])
{
#ifdef CELLRANGE
	gxOperand op;
	gxNumber pmt,
			 rate,
			 fv,
			 fvopmt;

	if (argv->val.count != 3)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 1);
	_gx_cvt2constant(argv + 2);
	_gx_cvt2constant(argv + 3);
	if (argv[1].type != GX_NUMBER || argv[2].type != GX_NUMBER ||
		argv[3].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_ARG_NUMERIC);
	pmt = argv[1].val.number;
	rate = argv[2].val.number;
	fv = argv[3].val.number;
	if (rate < -1.0)
		_gx_function_error(GX_FN_ERR_R_INT_GT_NEG_1);
	if (pmt == 0.0)
		_gx_function_error(GX_FN_ERR_PMT_NE_0);
	fvopmt = fv / pmt;
	if (fvopmt < 0.0)
		_gx_function_error(GX_FN_ERR_PMT_FV_SIGN);
	op.type = GX_NUMBER;
#ifdef OLD_MATH
	op.val.number = log(1.0 + fvopmt * rate) / log(1.0 + rate);
#else
	op.val.number = log(1.0 + fvopmt * rate) / log1p(rate);
#endif
	return op;
#else
	gxOperand op;
	op.type = GX_NUMBER;
	_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	return op;
#endif
}

// _gx_fn_npv did not validate with the sample
// data. Therefore I removed it from the keyword table.

gxOperand __cdecl _gx_fn_npv(gxOperand argv[])
{
#ifdef CELLRANGE
	gxOperand op;

	gxNumber x,
			 rate,
			 rate1,
			 factor,
			 npv = 0.0;
	unsigned r,
		c;
	if (argv->val.count != 2)
		_gx_function_error(GX_FN_ERR_ARG_CNT_WRONG);
	_gx_cvt2constant(argv + 1);
	if (argv[1].type != GX_NUMBER)
		_gx_function_error(GX_FN_ERR_R_NUMERIC);
	rate = argv[1].val.number;
	if (rate < -1.0)
		_gx_function_error(GX_FN_ERR_R_INT_GT_NEG_1);
	GX_HANDLE_OP_ERROR(argv[2]);
	if (argv[2].type != GX_RANGE)
		_gx_function_error(GX_FN_ERR_CF_RANGE);
	if (argv[2].val.range.r0 != argv[2].val.range.r1 &&
		argv[2].val.range.c0 != argv[2].val.range.c1)
		_gx_function_error(GX_FN_ERR_CF_COL_OR_ROW);
	factor = rate1 = 1.0 / (1.0 + rate);
	for (r = argv[2].val.range.r0; r <= argv[2].val.range.r1; r++)
		for (c = argv[2].val.range.c0; c <= argv[2].val.range.c1; c++)
		{
			if (!_gx_fn_get_value(r, c, &x))
				x = 0.0;
			npv += x * factor;
			factor *= rate1;
		}
	op.type = GX_NUMBER;
	op.val.number = npv;
	return op;
#else
	gxOperand op;
	op.type = GX_NUMBER;
	_gx_function_error(GX_FN_ERR_IMPROP_ARG_TYPE);
	return op;
#endif
}
