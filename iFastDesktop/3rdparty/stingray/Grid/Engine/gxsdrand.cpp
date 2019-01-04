///////////////////////////////////////////////////////////////////////////////
// gxsdrand.cpp
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
 *  _gx_drand48, etc. pseudo-random number generator
 *  This implementation assumes unsigned short integers of at least
 *  16 bits, long integers of at least 32 bits, and ignores
 *  overflows on adding or multiplying two unsigned integers.
 *  Two's-complement representation is assumed in a few places.
 *  Some extra masking is done if unsigneds are exactly 16 bits
 *  or longs are exactly 32 bits, but so what?
 *  An assembly-language implementation would run significantly faster.
 */

#define _OG_EXPORT_IMPL
#define _RW_IMPL

#include "stdafx.h"


#if _MFC_VER >= 0x0300

#include "grid\gxsinc.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

#pragma warning(disable:4244)

#ifndef HAVEFP
#define HAVEFP 1
#endif
#define N   16
#define MASK    ((unsigned)(1 << (N - 1)) + (1 << (N - 1)) - 1)
#define LOW(x)  ((unsigned)(x) & MASK)
#define HIGH(x) LOW((x) >> N)
#define MUL(x, y, z)    { long l = (long)(x) * (long)(y); \
		(z)[0] = LOW(l); (z)[1] = HIGH(l); }
#define CARRY(x, y) ((long)(x) + (long)(y) > MASK)
#define ADDEQU(x, y, z) (z = CARRY(x, (y)), x = LOW(x + (y)))
#define X0  0x330E
#define X1  0xABCD
#define X2  0x1234
#define A0  0xE66D
#define A1  0xDEEC
#define A2  0x5
#define C   0xB
#define SET3(x, x0, x1, x2) ((x)[0] = (x0), (x)[1] = (x1), (x)[2] = (x2))
#define SETLOW(x, y, n) SET3(x, LOW((y)[n]), LOW((y)[(n)+1]), LOW((y)[(n)+2]))
#define SEED(x0, x1, x2) (SET3(x, x0, x1, x2), SET3(a, A0, A1, A2), c = C)
#define REST(v) for (i = 0; i < 3; i++) { xsubi[i] = x[i]; x[i] = temp[i]; } \
		return (v);
#define NEST(TYPE, f, F)    TYPE f(register unsigned short int *xsubi) { \
	register int i; register TYPE v; unsigned temp[3]; \
	for (i = 0; i < 3; i++) { temp[i] = x[i]; x[i] = LOW(xsubi[i]); }  \
	v = F(); REST(v); }
#define HI_BIT  (1L << (2 * N - 1))

static unsigned x[3] = {X0, X1, X2}, a[3] = {A0, A1, A2}, c = C;
static unsigned short lastx[3];
static void next();

#if HAVEFP
double __cdecl _gx_drand48()
{
#if pdp11
	static double two16m;   /* old pdp11 cc can't compile an expression */
	two16m = 1.0 / (1L << N);   /* in "double" initializer! */
#else
	static double two16m = 1.0 / (1L << N);
#endif

	next();
	return (two16m * (two16m * (two16m * x[0] + x[1]) + x[2]));
}

NEST(double, _gx_erand48, _gx_drand48);

#else

long irand48(register unsigned short m)
/* Treat x[i] as a 48-bit fraction, and multiply it by the 16-bit
 * multiplier m.  Return integer part as result.
 */
{
	unsigned r[4],
			 p[2],
			 carry0 = 0;

	next();
	MUL(m, x[0], &r[0]);
	MUL(m, x[2], &r[2]);
	MUL(m, x[1], p);
	if (CARRY(r[1], p[0]))
		ADDEQU(r[2], 1, carry0);
	return (r[3] + carry0 + CARRY(r[2], p[1]));
}

long krand48(register unsigned short *xsubi, unsigned short m)
/* same as irand48, except user provides storage in xsubi[] */
{
	register int i;
	register long iv;
	unsigned temp[3];

	for (i = 0; i < 3; i++)
	{
		temp[i] = x[i];
		x[i] = xsubi[i];
	}
	iv = irand48(m);
	REST(iv);
}
#endif

long int __cdecl _gx_lrand48()
{
	next();
	return (((long) x[2] << (N - 1)) + (x[1] >> 1));
}

long int __cdecl _gx_mrand48()
{
	register long l;

	next();
	/* sign-extend in case length of a long > 32 bits (as on Honeywell) */
	return ((l = ((long) x[2] << N) + x[1]) & HI_BIT ? l | -HI_BIT : l);
}

static void next()
{
	unsigned p[2],
			 q[2],
			 r[2],
			 carry0,
			 carry1;

	MUL(a[0], x[0], p);
	ADDEQU(p[0], c, carry0);
	ADDEQU(p[1], carry0, carry1);
	MUL(a[0], x[1], q);
	ADDEQU(p[1], q[0], carry0);
	MUL(a[1], x[0], r);
	x[2] = LOW(carry0 + carry1 + CARRY(p[1], r[0]) + q[1] + r[1] +
			   a[0] * x[2] + a[1] * x[1] + a[2] * x[0]);
	x[1] = LOW(p[1] + r[0]);
	x[0] = LOW(p[0]);
}

void __cdecl _gx_srand48(long int seedval)
{
	SEED(X0, LOW(seedval), HIGH(seedval));
}

unsigned short int *
	__cdecl _gx_seed48(unsigned short seed16v[3])
{
	SETLOW(lastx, x, 0);
	SEED(LOW(seed16v[0]), LOW(seed16v[1]), LOW(seed16v[2]));
	return (lastx);
}

void __cdecl _gx_lcong48(unsigned short int param[7])
{
	SETLOW(x, param, 0);
	SETLOW(a, param, 3);
	c = LOW(param[6]);
}

NEST(long, _gx_nrand48, _gx_lrand48);

NEST(long, _gx_jrand48, _gx_mrand48);

#ifdef DRIVER
/*
		This should print the sequences of integers in Tables 2
				and 1 of the TM:
		1623, 3442, 1447, 1829, 1305, ...
		657EB7255101, D72A0C966378, 5A743C062A23, ...
 */
#include <stdio.h>

main()
{
	int i;

	for (i = 0; i < 80; i++)
	{
		_tprintf("%4d ", (int) (4096 * _gx_drand48()));
		_tprintf("%.4X%.4X%.4X\n", x[2], x[1], x[0]);
	}
}
#endif

#endif
