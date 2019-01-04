///////////////////////////////////////////////////////////////////////////////
// gxsmatrx.cpp: Matrix routines
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

#if	!defined(M_PI)
#define	M_PI	3.14159265358979323846
#endif

#pragma warning (disable: 4018)
#pragma warning (disable: 4389) // Signed/Unsigned Mismatch

int _cdecl _gx_asymmetric(gxMatrix a)
{
    double x, 
		   y;
    
	register int i, j;

    for (i=0; i<a.r_dim; i++)
	for (j=0; j<i; j++)
	    if ((x = GX_MVAL(a, j, i)) != (y = GX_MVAL(a, i, j)))
			if (fabs(x-y)/GX_MAX(fabs(x),fabs(y)) > 1.0e-10) 
				return 1;
    return 0;
}

gxMatrix _cdecl _gx_mtranspose(gxMatrix a)
{
    gxMatrix at;
    register int i,
				 j;

    at.r_dim = a.c_dim;
    at.c_dim = a.r_dim;
    
	_gx_mkwm(&at);
    
	for (i=0; i<a.r_dim; i++)
		for (j=0; j<a.c_dim; j++)
			GX_MVAL(at, j, i) = GX_MVAL(a, i, j);
    return at;
}

gxMatrix _cdecl _gx_mmul(gxMatrix a, gxMatrix b)
{
    gxMatrix c;
    register int i,
				 j,
				 k;
    double sum;

    if (a.c_dim != b.r_dim)
	{
		c.r_dim = c.c_dim = 0;
		c.data = NULL;
		return c;
	}

    c.r_dim = a.r_dim;
    c.c_dim = b.c_dim;
    _gx_mkwm(&c);
    
	for (i=0; i<c.r_dim; i++)
		for (j=0; j<c.c_dim; j++)
			{
				sum = 0.0;
				for (k=0; k<a.c_dim; k++)
					sum += GX_MVAL(a, i, k) * GX_MVAL(b, k, j);
				GX_MVAL(c, i, j) = sum;
			}
	return c;
}

gxMatrix _cdecl _gx_mTmul(gxMatrix a, gxMatrix b)	/* computes aTb */
{
    gxMatrix c;
    register int i,
				 j, 
				 k;
    double sum;

    if (a.r_dim != b.r_dim)
	{
		c.r_dim = c.c_dim = 0;
		c.data = NULL;
		return c;
	}
    
	c.r_dim = a.c_dim;
    c.c_dim = b.c_dim;
    
	_gx_mkwm(&c);
    for (i=0; i<c.r_dim; i++)
		for (j=0; j<c.c_dim; j++)
	    {
			sum = 0.0;
			for (k=0; k<a.r_dim; k++)
				sum += GX_MVAL(a, k, i) * GX_MVAL(b, k, j);
			GX_MVAL(c, i, j) = sum;
	    }
    return c;
}

/*
 * LU decomposition by Crout's method with implicit partial pivoting
 * as described in Numerical Recipes in C, by Press et al.
 */

gxMatrix _cdecl _gx_mLUdecomp(gxMatrix a, int *indx, double *d)
{
    int i=0, j=0, k=0, imax=0,
				 pivot_count=0;

    double sum, 
		   temp,
		   a_max,
		   a_min;
    gxMatrix scale;

    scale.r_dim = a.r_dim;
    scale.c_dim = 1;
    _gx_mkwm(&scale);
    for (i=0; i<a.r_dim; i++)
	{
		a_max = 0.0;
		for (j=0; j<a.r_dim; j++) /* find max in each row for implicit pivot */
			a_max = GX_MAX(fabs(GX_MVAL(a, j, j)), a_max);
		if (a_max == 0.0)	/* matrix is singular */
	    {
			a.r_dim = a.c_dim = 0;
			return a;
	    }
	
		scale.data[i] = 1.0/a_max;
	}
    
	pivot_count = 0;
    
	for (j=0; j<a.c_dim; j++)	/* for each column */
	{
		for (i=0; i<j; i++)	/* for each element above the diagonal */
	    {
			sum = 0.0;
			for (k=0; k<i; k++)
			sum += GX_MVAL(a, i, k) * GX_MVAL(a, k, j);
			GX_MVAL(a, i, j) -= sum;	/* replace Aij with Uij */
	    }
	
		a_max = 0.0;

		for (i=j; i<a.r_dim; i++) /* for each element on and below diagonal */
		{
			sum = 0.0;
			for (k=0; k<j; k++)
				sum += GX_MVAL(a, i, k) * GX_MVAL(a, k, j);
			GX_MVAL(a, i, j) -= sum;
			
			temp = scale.data[i] * fabs(sum);

			if (temp >= a_max)
			{
				a_max = temp;
				imax = i;
			}
		}
	
		if (j != imax)
		{
			for (k=0; k<a.r_dim; k++)	/* interchange rows j and imax */
			{
				temp = GX_MVAL(a, imax, k);
				GX_MVAL(a, imax, k) = GX_MVAL(a, j, k);
				GX_MVAL(a, j, k) = temp;
			}
			scale.data[imax] = scale.data[j];
			pivot_count++;
		}
	
		indx[j] = imax;
		
		if (GX_MVAL(a, j, j) == 0.0)	/* matrix is singular */
		{
			a.r_dim = a.c_dim = 0;
			return a;
		}
	
		if (j != a.r_dim)	/* divide by Ujj to compute Lij */
			{
				temp = 1.0/GX_MVAL(a, j, j);
				for (i=j+1; i<a.r_dim; i++)
					GX_MVAL(a, i, j) *= temp;
			}
	} 
    
	a_max = a_min = fabs(GX_MVAL(a, 0, 0));
    
	for (j=1; j<a.r_dim; j++)		/* test for near singularity */
	{
		a_max = GX_MAX(fabs(GX_MVAL(a, j, j)), a_max);
		a_min = GX_MIN(fabs(GX_MVAL(a, j, j)), a_min);
	}

    if ((a_max + a_min) == a_max ||
	 a_max / a_min > 1.0e15)	/* matrix is near singular */
	{
		a.r_dim = a.c_dim = 0;
		return a;
	}
    
	_gx_freewm(&scale);
    
	*d = pivot_count % 1 ? -1.0 : 1.0;
    
	return a;
}


gxMatrix _cdecl _gx_mLUbksub(gxMatrix a, int *indx, gxMatrix b)
{
    int i,
		j;
    
	double sum,
		   temp;

    for (i=0; i<a.r_dim; i++)
	{
		temp = b.data[indx[i]];
		b.data[indx[i]] = b.data[i];
		sum = 0.0;
		for (j=0; j<i; j++)
			sum += GX_MVAL(a, i, j) * b.data[j];
		b.data[i] = temp - sum;
	}

    for (i=a.r_dim-1; i>=0; i--)
	{
		sum = 0.0;
		for (j=i+1; j<a.r_dim; j++)
			sum += GX_MVAL(a, i, j) * b.data[j];
		b.data[i] = (b.data[i] - sum) / GX_MVAL(a, i, i);
	}
		return b;
}


gxMatrix _cdecl _gx_minvert(gxMatrix a)
{
    gxMatrix indx,
			 col,
			 b;
    double d;
    
	int i,
		j,
		n;

    n = a.r_dim;
    indx.r_dim = (n+1)/2;
    indx.c_dim = 1;
    col.r_dim = n;
    col.c_dim = 1;
    b.r_dim = a.r_dim;
    b.c_dim = a.c_dim;
    _gx_mkwm(&col);
    _gx_mkwm(&indx);
    _gx_mkwm(&b);
    
	a = _gx_mLUdecomp(a, (int *) indx.data, &d);
    
	if (a.r_dim == 0)
		return a;
    
	for (j=0; j<n; j++)
	{
		for (i=0; i<n; i++)
			col.data[i] = 0.0;
		col.data[j] = 1.0;
		col = _gx_mLUbksub(a, (int *) indx.data, col);
		
		for (i=0; i<n; i++)
			GX_MVAL(b, i, j) = col.data[i];
	}

    _gx_freewm(&col);
    _gx_freewm(&indx);
    
	return b;
}

gxMatrix _cdecl _gx_mlinsolv(gxMatrix a, gxMatrix b)
{
    gxMatrix indx;
    double d;
    int i, j, n;

    n = a.r_dim;
    indx.r_dim = (n+1)/2;
    indx.c_dim = 1;
    _gx_mkwm(&indx);
    a = _gx_mLUdecomp(a, (int *) indx.data, &d);
    if (a.r_dim == 0)
		return a;
    
	return _gx_mLUbksub(a, (int *) indx.data, b);
	i, j, n;
}

int _cdecl _gx_mlls_short(gxMatrix a, gxMatrix b, gxMatrix *result)
{
	gxMatrix aTa,
			 aTb,
			 x,
			 y;

    if (a.r_dim <= a.c_dim)
		return 1;
    
	aTa = _gx_mTmul(a, a);
    aTb = _gx_mTmul(a, b);
    
	if (aTb.r_dim == 0)
		return 2;
	
	aTa = _gx_minvert(aTa);
    
	if (aTa.r_dim == 0)
		return 3;
    
	*result = _gx_mmul(aTa, aTb);
    
	return 0;
	x, y;
}

int _cdecl _gx_mlls(gxMatrix a, gxMatrix b, gxMatrix *result)
{
    gxMatrix aTa,
			 aTb,
			 x,
			 y;
    
	double sum2ymb,
			 sum2y,
			 sum2b,
			 sumy,
			 sumb,
			 ymb,
			 mse,
			 df,
			 r2,
			 numer,
			 denom;

    double alphaT(),
		   alphaF(),
				  F;
    
	int i,
		n,
		p;

    if (a.r_dim <= a.c_dim)
		return 1;
    
	aTa = _gx_mTmul(a, a);
    aTb = _gx_mTmul(a, b);
    
	if (aTb.r_dim == 0)
		return 2;
    
	aTa = _gx_minvert(aTa);
    
	if (aTa.r_dim == 0)
		return 3;
    
	x = _gx_mmul(aTa, aTb);
    y = _gx_mmul(a, x);
    
	sum2y = sumy = sum2b = sumb = sum2ymb = 0.0;
    n = a.r_dim;	/* number of points in the data set */
    p = a.c_dim;	/* number of parameters in the model */
    
	for (i=0; i<n; i++)
	{
		ymb = y.data[i] - b.data[i];
		sumy += y.data[i];
		sum2y += y.data[i] * y.data[i];
		sumb += b.data[i];
		sum2b += b.data[i] * b.data[i];
		sum2ymb += ymb * ymb;
	}
    
	df = (double) (n - p);
    numer = sum2y + sumb / n * (sumb - 2.0 * sumy);
    denom = sum2b - sumb / n * sumb;
    if ( p == 1 || denom == 0.0)
		r2 = 0.0;
    else
		r2 = numer/denom;
    
	mse = sum2ymb/df;	/* this is equiv to (numer - denom)/df */
    result->r_dim = 4;
    result->c_dim = a.c_dim + 1;
    
	_gx_mkwm(result);
    
	for (i=0; i < result->c_dim - 1; i++)
	{
		GX_MVAL(*result, 0, i) = x.data[i];
		GX_MVAL(*result, 1, i) = sqrt(GX_MVAL(aTa, i, i) * mse);
		if (mse == 0.0)	/* safety check for exact fit */
			GX_MVAL(*result, 2, i) = 1.0e15;
		else
			GX_MVAL(*result, 2, i) = GX_MVAL(*result, 0, i) / GX_MVAL(*result, 1, i);
		
		GX_MVAL(*result, 3, i) = _gx_alphaT(df, GX_MVAL(*result, 2, i));
	}

    i = result->c_dim - 1;
    
	GX_MVAL(*result, 0, i) = mse;
    GX_MVAL(*result, 1, i) = r2;
    
	if (p == 1)
		F = 0.0;
    else if ((1-r2)*1.0e30 < df*r2)	/* safety check for exact fit */
		F = 1.0e15;
    else
		F = (numer/(p - 1.0)) / mse; /* equiv to (r2/(p-1))/(1-r2)/(n-p)) */
    
	GX_MVAL(*result, 2, i) = F;
	if (p == 1)
		GX_MVAL(*result, 3, i) = 0.0;
    else
		GX_MVAL(*result, 3, i) = _gx_alphaF((double) (p-1), (double) (n-p), F);
    return 0;
}

double _cdecl _gx_mdet(gxMatrix a)
{
    gxMatrix indx;
    
	double d;
    int i, n;

    n = a.r_dim;
    
	indx.r_dim = (n+1)/2;
    indx.c_dim = 1;
    
	_gx_mkwm(&indx);
    
	a = _gx_mLUdecomp(a, (int *) indx.data, &d);
    
	if (a.r_dim == 0)	/* singular matrix */
		return 0.0;
	
	for (i=0; i<a.r_dim; i++)
		d *= GX_MVAL(a, i, i);
    return d;
}


/*
 * Radix 4 complex FFT adapted from algorithm 83,
 * J. Appl. Statist., vol 24, p. 153, 1975
 * (scaling and polarity have been changed from original)
 */

void _cdecl _gx_fastg(double xreal[], double ximag[], int n, int type)
{
    double bcos=0.0, bsin=0.0, cw1=0.0, cw2=0.0, cw3=0.0,
	sw1=0.0, sw2=0.0, sw3=0.0, tempr=0.0, x1=0.0, x2=0.0, 
	x3=0.0, xs0=0.0, xs1=0.0, xs2=0.0, xs3=0.0, y1=0.0, 
	y2=0.0, y3=0.0, ys0=0.0, ys1=0.0, ys2=0.0, ys3=0.0, 
	z=0.0, sinz=0.0;
    
	int ifaca, k, ifcab, litla, i0, i1, i2, i3;

    ifaca = n / 4;
    if (type > 0)	/* forward transform */
	{
		for (k=0; k<n; k++)
			ximag[k] = -ximag[k];
	}
	L5: ifcab = ifaca * 4;
    z = GX_M_PI / ifcab;
    sinz = sin(z);
    bcos = -2.0 * sinz * sinz;
    bsin = sin(2.0 * z);
    cw1 = 1.0;
    sw1 = 0.0;
    for (litla=0; litla<ifaca; litla++)
	{
	for (i0=litla; i0<n; i0+=ifcab)
	    {
			i1 = i0 + ifaca;
			i2 = i1 + ifaca;
			i3 = i2 + ifaca;
			xs0 = xreal[i0] + xreal[i2];
			xs1 = xreal[i0] - xreal[i2];
			ys0 = ximag[i0] + ximag[i2];
			ys1 = ximag[i0] - ximag[i2];
			xs2 = xreal[i1] + xreal[i3];
			xs3 = xreal[i1] - xreal[i3];
			ys2 = ximag[i1] + ximag[i3];
			ys3 = ximag[i1] - ximag[i3];
			xreal[i0] = xs0 + xs2;
			ximag[i0] = ys0 + ys2;
			x1 = xs1 + ys3;
			y1 = ys1 - xs3;
			x2 = xs0 - xs2;
			y2 = ys0 - ys2;
			x3 = xs1 - ys3;
			y3 = ys1 + xs3;
			if (litla == 0)
			{
				xreal[i2] = x1;
				ximag[i2] = y1;
				xreal[i1] = x2;
				ximag[i1] = y2;
				xreal[i3] = x3;
				ximag[i3] = y3;
				continue;
			}

			xreal[i2] = x1 * cw1 + y1 * sw1;
			ximag[i2] = y1 * cw1 - x1 * sw1;
			xreal[i1] = x2 * cw2 + y2 * sw2;
			ximag[i1] = y2 * cw2 - x2 * sw2;
			xreal[i3] = x3 * cw3 + y3 * sw3;
			ximag[i3] = y3 * cw3 - x3 * sw3;
	    }

	if (litla == ifaca-1)
		continue;
	
	z = cw1 * bcos - sw1 * bsin + cw1;
	sw1 = bcos * sw1 + bsin * cw1 + sw1;
	tempr = 1.5 - 0.5 * (z * z + sw1 * sw1);
	
	cw1 = z * tempr;
	sw1 = sw1 * tempr;
	cw2 = cw1 * cw1 - sw1 * sw1;
	sw2 = 2.0 * cw1 * sw1;
	cw3 = cw1 * cw2 - sw1 * sw2;
	sw3 = cw1 * sw2 + cw2 * sw1;
	
	}
    
	if (ifaca > 1)
	{
		ifaca = ifaca / 4;
		
		if (ifaca > 0) 
			goto L5;
		
		for (k=0; k<n; k+=2)
			{
				tempr = xreal[k] + xreal[k + 1];
				xreal[k + 1] = xreal[k] - xreal[k + 1];
				xreal[k] = tempr;
				tempr = ximag[k] + ximag[k + 1];
				ximag[k + 1] = ximag[k] - ximag[k + 1];
				ximag[k] = tempr;
			}
	}

    if (type > 0)
	{
		for (k=0; k<n; k++)
			ximag[k] = -ximag[k];
	}
    else
	{
		z = 1.0 / n;
		for (k=0; k<n; k++)
			{
			xreal[k] = xreal[k] * z;
			ximag[k] = ximag[k] * z;
			}
	}
    
}


void _cdecl _gx_scram(double xreal[], double ximag[], int /*n*/, int ipow)
{
    double tempr;
    double *xr = xreal-1;
    double *xi = ximag-1;
    
	int l[20], i, ii, itop, k;
    int j1, j2, j3, j4, j5, j6, j7, j8, j9, j10, j11, j12, j13, j14, j15,
	j16, j17, j18, j19, j20;

    ii = 1;
    itop = 1 << (ipow-1);
    i = 20 - ipow;
    for (k=0; k<=i; k++)
	l[k] = ii;
    i++;
    for (k=i; k<=19; k++)
	{
	ii *= 2;
	l[k] = ii;
	}
    ii = 0;
    for (j1 = 1; j1 <= l[1]; j1 += l[0]) {
     for (j2 = j1; j2 <= l[2]; j2 += l[1]) {
      for (j3 = j2; j3 <= l[3]; j3 += l[2]) {
       for (j4 = j3; j4 <= l[4]; j4 += l[3]) {
	for (j5 = j4; j5 <= l[5]; j5 += l[4]) {
	 for (j6 = j5; j6 <= l[6]; j6 += l[5]) {
	  for (j7 = j6; j7 <= l[7]; j7 += l[6]) {
	   for (j8 = j7; j8 <= l[8]; j8 += l[7]) {
	    for (j9 = j8; j9 <= l[9]; j9 += l[8]) {
	     for (j10 = j9; j10 <= l[10]; j10 += l[9]) {
	      for (j11 = j10; j11 <= l[11]; j11 += l[10]) {
	       for (j12 = j11; j12 <= l[12]; j12 += l[11]) {
		for (j13 = j12; j13 <= l[13]; j13 += l[12]) {
		 for (j14 = j13; j14 <= l[14]; j14 += l[13]) {
		  for (j15 = j14; j15 <= l[15]; j15 += l[14]) {
		   for (j16 = j15; j16 <= l[16]; j16 += l[15]) {
		    for (j17 = j16; j17 <= l[17]; j17 += l[16]) {
		     for (j18 = j17; j18 <= l[18]; j18 += l[17]) {
		      for (j19 = j18; j19 <= l[19]; j19 += l[18]) {
		       j20 = j19;
		       for (i=0; i<2; i++)
			   {
			   ii++;
			   if (ii < j20)
			       {
			       tempr = xr[ii];
			       xr[ii] = xr[j20];
			       xr[j20] = tempr;
			       tempr = xi[ii];
			       xi[ii] = xi[j20];
			       xi[j20] = tempr;
			       }
			   j20 = j20 + itop;
			   }
                       }
                      }
                     }
                    }
                   }
		  }
		 }
		}
	       }
	      }
	     }
	    }
	   }
	  }
	 }
	}
       }
      }
     }
    }

int _cdecl _gx_fastf(double xreal[], double ximag[], int n, int type)
{
    int power;

    if (type == 0) 
		return 0;

    for (power=2; power<=20; power++)
		if (n == (1 << power)) 
			break;

    if (power > 20)
		return 0;	/* must be power of 2 between 2 and 20 */

    _gx_fastg(xreal, ximag, n, type);
    _gx_scram(xreal, ximag, n, power);

    return 1;
}

void _cdecl _gx_fft(gxMatrix a, int type)
{
    gxMatrix b, c;
    
	int i, j, n;

    n = a.r_dim;
    
	if (n == 2)		/* can't do length 2 with radix 4 FFT */
    {
		b = _gx_dft(a, type);
		for (i=0; i<2*n; i++)
			a.data[i] = b.data[i];
		_gx_freewm(&b);
	}
    else
    {
		b.r_dim = c.r_dim = n;
		b.c_dim = c.c_dim = 1;
		_gx_mkwm(&b);
		_gx_mkwm(&c);
			
		j = 0;
			
		for (i=0; i<n; i++)
		{
			b.data[i] = a.data[j++];
			c.data[i] = a.data[j++];
		}
			
		_gx_fastf(b.data, c.data, n, type);
			
		j = 0;
			
		for (i=0; i<n; i++)
		{
			a.data[j++] = b.data[i];
			a.data[j++] = c.data[i];
		}
	
		_gx_freewm(&b);
		_gx_freewm(&c);
	}
}


gxMatrix _cdecl _gx_dft(gxMatrix a, int sign)
{
    int k, n, npts;
    double rsum, isum, w0, wn, sin_theta, cos_theta;
    gxMatrix b;

    b.r_dim = a.r_dim;
    b.c_dim = a.c_dim;
    
	_gx_mkwm(&b);
    
	npts = a.r_dim;
    
	w0 = sign*2.0*GX_M_PI/npts;
    
	for (n=0; n<npts; n++)
	{
	
		rsum = isum = 0.0;
		wn = w0*n;
	
		for (k=0; k<npts; k++)
			{
				sin_theta = sin(wn*k);
				cos_theta = cos(wn*k);
				rsum += a.data[2*k]*cos_theta - a.data[2*k+1]*sin_theta;
				isum += a.data[2*k]*sin_theta + a.data[2*k+1]*cos_theta;
			}
		
		if (sign == -1)
			{
				b.data[2*n] = rsum/npts;
				b.data[2*n+1] = isum/npts;
			}
		else
			{
				b.data[2*n] = rsum;
				b.data[2*n+1] = isum;
			}
	}

    return b;
}


gxMatrix _cdecl _gx_meigen(gxMatrix a)
{
    int i, j, k, l, m, iter;
    double b, c, f, g, h, p, r, s, dd, hh, scale;
    
	gxMatrix d, e;

    d.r_dim = e.r_dim = a.r_dim;
    d.c_dim = e.c_dim = 1;
    
	_gx_mkwm(&d);
    _gx_mkwm(&e);

    for (i=a.r_dim-1; i>0; i--)
	{
		l = i - 1;
		h = scale = 0.0;
		if (l > 0)
	    {
			for (k=0; k<=l; k++)
				scale += fabs(GX_MVAL(a, i, k));
			
			if (scale == 0.0)
				e.data[i] = GX_MVAL(a, i, l);
			else
			{
				for (k=0; k<=l; k++)
					{
						GX_MVAL(a, i, k) /= scale;
						h += GX_MVAL(a, i, k)*GX_MVAL(a, i, k);
					}
				
				f = GX_MVAL(a, i, l);
				g = f>0 ? -sqrt(h) : sqrt(h);
				e.data[i] = scale*g;
				h -= f*g;
				
				GX_MVAL(a, i, l) = f-g;
				f = 0.0;
				
				for (j=0; j<=l; j++)
					{
						g = 0.0;
						
						for (k=0; k<=j; k++)
							g += GX_MVAL(a, j, k)*GX_MVAL(a, i, k);
						
						for (k=j+1; k<=l; k++)
							g += GX_MVAL(a, k, j)*GX_MVAL(a, i, k);
						
						e.data[j] = g/h;
						f += e.data[j]*GX_MVAL(a, i, j);
					}
				
				hh = f/(2.0*h);
				
				for (j=0; j<=l; j++)
					{
						f = GX_MVAL(a, i, j);
						e.data[j] = g = e.data[j] - hh*f;
						
						for (k=0; k<=j ; k++)
							GX_MVAL(a, j, k) -= (f*e.data[k] + g*GX_MVAL(a, i, k));
					}
			}
	    }
	else
	    e.data[i] = GX_MVAL(a, i, l);
		d.data[i] = h;
	}

    e.data[0] = 0.0;
    
	for (i=0; i<a.r_dim; i++)
		d.data[i] = GX_MVAL(a, i, i);
    
	for (i=1; i<d.r_dim; i++) e.data[i-1] = e.data[i];
		e.data[d.r_dim-1] = 0.0;
    
	for (l=0; l<d.r_dim; l++)
	{
		iter = 0;
		
		do 
		{
			for (m=l; m<d.r_dim-1; m++)
			{
				dd = fabs(d.data[m]) + fabs(d.data[m+1]);
				if (fabs(e.data[m]) + dd == dd)
					break;
			}
			
			if (m != l)
			{
				// Commented this out : DJ 8/21/98
				// if (iter++ == 30) 
				//	_gx_function_error("too many iterations");
				
				g = (d.data[l+1] - d.data[l])/(2.0*e.data[l]);
				
				r = sqrt((g*g) + 1.0);
				
				if (g < 0.0)
					g = d.data[m] - d.data[l] + e.data[l]/(g - fabs(r));
				else
					g = d.data[m] - d.data[l] + e.data[l]/(g + fabs(r));
				
				s = c = 1.0;
				
				p = 0.0;

				for (i=m-1; i>=l; i--)
				{
						f = s*e.data[i];
						b = c*e.data[i];
					
					if (fabs(f) >= fabs(g))
					{
						c = g/f;
						r = sqrt((c*c) + 1.0);
						e.data[i+1] = f*r;
						c *= (s = 1.0/r);
					}
					else
					{
						s = f/g;
						r = sqrt((s*s) + 1.0);
						e.data[i+1] = g*r;
						s *= (c = 1.0/r);
					}
					
					g = d.data[i+1] - p;
					r = (d.data[i]-g)*s + 2.0*c*b;
					p = s*r;
					d.data[i+1] = g + p;
					g = c*r - b;
					
				}
				
				d.data[l] = d.data[l] - p;
				e.data[l] = g;
				e.data[m] = 0.0;
			}
			
		} while (m != l);
	}
   return d;
}
