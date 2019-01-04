///////////////////////////////////////////////////////////////////////////////
// gxslgamm.cpp
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
// Portions of this code copied from GNU C Runtime Library
//

/*
 * Copyright (c) 1985 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 */

/*
		C program for floating point log Gamma function

		_gx_lgamma(x) computes the log of the absolute
		value of the Gamma function.
		The sign of the Gamma function is returned in the
		external quantity _gx_signgam.

		The coefficients for expansion around zero
		are #5243 from Hart & Cheney; for expansion
		around infinity they are #5404.

		Calls log, floor and sin.
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

#if 0
#include "mathimpl.h"
#else
#include <math.h>
#endif
#if defined(vax)||defined(tahoe)
#include <errno.h>
#endif /* defined(vax)||defined(tahoe) */

int _gx_signgam;

static const double goobie = 0.9189385332046727417803297;   /* log(2*pi)/2 */
static const double pi = 3.1415926535897932384626434;

#define M 6
#define N 8
static const double p1[] = {
	0.83333333333333101837e-1,
	-.277777777735865004e-2,
	0.793650576493454e-3,
	-.5951896861197e-3,
	0.83645878922e-3,
	-.1633436431e-2,
};
static const double p2[] = {
	-.42353689509744089647e5,
	-.20886861789269887364e5,
	-.87627102978521489560e4,
	-.20085274013072791214e4,
	-.43933044406002567613e3,
	-.50108693752970953015e2,
	-.67449507245925289918e1,
	0.0,
};
static const double q2[] = {
	-.42353689509744090010e5,
	-.29803853309256649932e4,
	0.99403074150827709015e4,
	-.15286072737795220248e4,
	-.49902852662143904834e3,
	0.18949823415702801641e3,
	-.23081551524580124562e2,
	0.10000000000000000000e1,
};

static double pos(double), neg(double), asym(double);

double __cdecl _gx_lgamma(double arg)
{

	_gx_signgam = 1;
	if (arg <= 0.)
		return (neg(arg));
	if (arg > 8.)
		return (asym(arg));
	return (log(pos(arg)));
}

static double asym(double arg)
{
	double n,
		   argsq;
	int i;

	/* Avoid overflow of arg*arg.  */
	n = 0.0;
	if (arg > 1.0e8)
		goto noasym;

	argsq = 1. / (arg * arg);
	for (i = M - 1; i >= 0; i--)
	{
		n = n * argsq + p1[i];
	}
noasym:
	return ((arg - .5) * log(arg) - arg + goobie + n / arg);
}

static double neg(double arg)
{
	double t;

	arg = -arg;
	/* to see if arg were a true integer, the old code used the
	 * mathematically correct observation: sin(n*pi) = 0 <=> n is an integer.
	 * but in finite precision arithmetic, sin(n*PI) will NEVER be zero
	 * simply because n*PI is a rational number.  hence it failed to work
	 * with our newer, more accurate sin() which uses true pi to do the
	 * argument reduction... temp = sin(pi*arg); */
	t = floor(arg);
	if (arg - t > 0.5e0)
		t += 1.e0;  /* t := integer nearest arg */
#if defined(vax)||defined(tahoe)
	if (arg == t)
	{
		return (infnan(ERANGE));    /* +INF */
	}
#endif /* defined(vax)||defined(tahoe) */
	_gx_signgam = (int) (t - 2 * floor(t / 2)); /* _gx_signgam =  1 if t was
												 * odd, */
	/* 0 if t was even */
	_gx_signgam = _gx_signgam - 1 + _gx_signgam;    /* _gx_signgam =  1 if t
													 * was odd, */
	/* -1 if t was even */
	t = arg - t;    /* -0.5 <= t <= 0.5 */
	if (t < 0.e0)
	{
		t = -t;
		_gx_signgam = -_gx_signgam;
	}
	return (-log(arg * pos(arg) * sin(pi * t) / pi));
}

static double pos(double arg)
{
	double n,
		   d,
		   s;
	register int i;

	if (arg < 2.)
		return (pos(arg + 1.) / arg);
	if (arg > 3.)
		return ((arg - 1.) * pos(arg - 1.));

	s = arg - 2.;
	for (n = 0, d = 0, i = N - 1; i >= 0; i--)
	{
		n = n * s + p2[i];
		d = d * s + q2[i];
	}
	return (n / d);
}
