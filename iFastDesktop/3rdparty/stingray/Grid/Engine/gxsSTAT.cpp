///////////////////////////////////////////////////////////////////////////////
// gxsstat.cpp: Statistic utilities
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

#define ITMAX   200
#define FPMIN 1.0e-30
#define EPS 1.0e-12
#if !defined(GX_M_PI)
#define     GX_M_PI     3.14159265358979323846
#endif

/* compute log(gamma(x)) by Lanczos' approx. */
double	__cdecl _gx_gammalog(double x)
{
	static double c[6] = {76.18009173,
		-86.50532033,
		24.01409822,
		-1.231739516,
		0.120858003e-2,
	-0.536382e-5};
	double s1,
		   s2,
		   t,
		   z;
	int i;

	if (x < 1.0)
	{
		z = 1.0 - x;
		x = GX_M_PI * z;
		return log(x / sin(x)) - _gx_gammalog(1.0 + z);
	}
	s1 = x - 1.0;
	t = s1 + 5.5;
	t -= (s1 + 0.5) * log(t);
	s2 = 1.0;
	for (i = 0; i < 6; i++)
	{
		s1 += 1.0;
		s2 += c[i] / s1;
	}
	return -t + log(2.50662827465 * s2);
}

double	__cdecl _gx_betacf(double a, double b, double x)
{
	double qap,
		   qam,
		   qab,
		   em,
		   tem,
		   d;
	double bz,
		   bm = 1.0,
		   bp,
		   bpp;
	double az = 1.0,
		   am = 1.0,
		   ap,
		   app,
		   aold;
	int m;

	qab = a + b;
	qap = a + 1.0;
	qam = a - 1.0;
	bz = 1.0 - qab * x / qap;
	for (m = 1; m <= ITMAX; m++)
	{
		em = (double) m;
		tem = em + em;
		d = em * (b - em) * x / ((qam + tem) * (a + tem));
		ap = az + d * am;
		bp = bz + d * bm;
		d = -(a + em) * (qab + em) * x / ((qap + tem) * (a + tem));
		app = ap + d * az;
		bpp = bp + d * bz;
		aold = az;
		am = ap / bpp;
		bm = bp / bpp;
		az = app / bpp;
		bz = 1.0;
		if (fabs(az - aold) < (EPS * fabs(az)))
			return az;
	}
	_gx_set_expr_err_flag(1);   /* iteration count exceeded */
	return 0.0;
}

/* compute incomplete beta function */
double	__cdecl _gx_betai(double a, double b, double x)
{
	double bt;

	if (x < 0.0 || x > 1.0)
	{   /* domain error */
		_gx_set_expr_err_flag(1);
		return 0.0;
	}
	if (x == 0.0 || x == 1.0)
		bt = 0.0;
	else
	{
		errno = 0;
		bt = exp(_gx_gammalog(a + b) - _gx_gammalog(a) - _gx_gammalog(b) +
				 a * log(x) + b * log(1.0 - x));
		if (errno)
			_gx_function_error(GX_FN_ERR_FLOAT);
	}
	if (x < (a + 1.0) / (a + b + 2.0))
		return bt * _gx_betacf(a, b, x) / a;
	else
		return 1.0 - bt * _gx_betacf(b, a, 1.0 - x) / b;
}

/* two - sided */
double	__cdecl _gx_alphaT(double nu, double t)
{
	double p;
	if (nu > 1.0e6)
		nu = 1.0e6;
	p = _gx_betai(nu / 2.0, 0.5, nu / (nu + t * t));
	return p;
}

/* one - sided */
double	__cdecl _gx_alphaF(double nu1, double nu2, double F)
{
	if (nu1 > 1.0e6)
		nu1 = 1.0e6;
	if (nu2 > 1.0e6)
		nu2 = 1.0e6;
	if (F == 0.0)
		return 1.0;
	return _gx_betai(nu2 / 2.0, nu1 / 2.0, nu2 / (nu2 + nu1 * F));
}




/*  returns the incomplete gamma function P(a,x) evaluated by its series */
/*  representation as gamser. also returns log(Gamma(a)) as gln     */

static void gser(double *gamser, double a, double x, double *gln)
{

	int n;
	double sum,
		   del,
		   ap;

	*gln = _gx_gammalog(a);
	if (x <= 0.0)
	{
		/* if (x < 0.0 ) nrerror("x less than 0 in routine gser"); */
		*gamser = 0;
		return;
	}
	else
	{
		ap = a;
		del = sum = 1.0 / a;
		for (n = 1; n <= ITMAX; n++)
		{
			++ap;
			del *= x / ap;
			sum += del;
			if (fabs(del) < fabs(sum) * EPS)
			{
				*gamser = sum * exp(-x + a * log(x) - (*gln));
				return;
			}
		}   /* of for */
	}   /* of else */
	*gamser = 0;
}  /* of gser */


static void gcf(double *gammcf, double a, double x, double *gln)
{

	int i;
	double an,
		   b,
		   c,
		   d,
		   del,
		   g;

	*gln = _gx_gammalog(a);
	b = x + 1.0 - a;
	c = 1.0 / FPMIN;
	d = 1.0 / b;
	g = d;
	for (i = 1; i <= ITMAX; i++)
	{
		an = -i * (i - a);
		b += 2.0;
		d = an * d + b;
		if (fabs(d) < FPMIN)
			d = FPMIN;
		c = b + an / c;
		if (fabs(c) < FPMIN)
			c = FPMIN;
		d = 1.0 / d;
		del = d * c;
		g *= del;
		if (fabs(del - 1.0) < EPS)
			break;
	}   /* of for */
	*gammcf = exp(-x + a * log(x) - (*gln)) * g;
}


/* returns the incomplete gamma function P(a,x), page:218  */
static double gammp(double a, double x)
{

	double gamser,
		   gammcf,
		   gln;

	if (x < 0.0 || a <= 0.0)
		return 0.0;
	if (x < (a + 1.0))
	{
		gser(&gamser, a, x, &gln);
		return gamser;
	}
	else
	{
		gcf(&gammcf, a, x, &gln);
		return 1.0 - gammcf;
	}
}


/* return the cumulative normal probability function of x */
double	__cdecl _gx_phi(double x)
{
	return x < 0.0 ? (0.5 - gammp(0.5, x * x / 2) / 2) : (gammp(0.5, x * x / 2) / 2 + 0.5);
}


/*
double _gx_phi(double x)
  {
  return 0.5 * erf(x * M_SQRT1_2) + 0.5;
  }
*/

double	__cdecl _gx_phi_inverse(double x)
{
	double lo,
		   hi,
		   mid = 0,
		   z;
	int sign = 1;
	int it = 0;

	if (x <= 0.0 || x >= 1.0)
	{
		return 0.0; /* domain error */
	}
	if (x == 0.5)
		return 0.0;
	if (x < 0.5)
	{
		x = 1.0 - x;
		sign = -1;
	}
	lo = 0.0;
	hi = 1.0;

	while ((z = _gx_phi(hi)) < x)
	{   /* bracket */
		lo = hi;
		hi *= 2;
		if (++it > 50)
			break;
	}

	while (hi - lo > EPS)
	{   /* converge */
		mid = (lo + hi) / 2;
		z = _gx_phi(mid);
		if (z < x)
			lo = mid;
		else
			hi = mid;
		if (++it > 50)
			break;
	}
	return sign * mid;
}
