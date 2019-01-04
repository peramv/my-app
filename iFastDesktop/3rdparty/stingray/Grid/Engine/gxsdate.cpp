///////////////////////////////////////////////////////////////////////////////
// gxsdate.cpp: date utilities
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

#define ADJUST_1904 1462

static struct
{
	short noDays;
}      _gx_months[12] =
{
	31,
	28,
	31,
	30,
	31,
	30,
	31,
	31,
	30,
	31,
	30,
	31
};

long __cdecl _gx_encode_date(int si, int year, int month, int day)
{
	// Unused:
	si;

	long gdate,
		i,
		leap_year;

	leap_year = !(year % 4);    /* 1 if leap year */
	_gx_months[1].noDays = (short) (28 + leap_year);

	if (year >= 1900)
		year -= 1900;
	if (year < 0 || year > 199)
		return 0;
	if (month < 1 || month > 12)
		return 0;
	if (day < 1 || day > _gx_months[month - 1].noDays)
		return 0;
	gdate = (long) year * 365 + (year == 0 ? 0 : (year - 1) / 4 + 1);
	for (i = 0; i < month - 1; i++) /* days in prior _gx_months */
		gdate += _gx_months[i].noDays;
	gdate += day;   /* days in current month */
//  if (get_1904_mode(si))
//    gdate -= ADJUST_1904;
	return gdate;
}

long _gx_encode_date_360(int si, int year, int month, int day)
{
	// Unused:
	si;

	long gdate,
		i,
		leap_year;

	leap_year = !(year % 4);    /* 1 if leap year */
	_gx_months[1].noDays = (short) (28 + leap_year);

	if (year >= 1900)
		year -= 1900;
	if (year < 0 || year > 199)
		return 0;
	if (month < 1 || month > 12)
		return 0;
	if (day < 1 || day > _gx_months[month - 1].noDays)
		return 0;
	gdate = (long) year * 365 + (year == 0 ? 0 : (year - 1) / 4 + 1);
	for (i = 0; i < month - 1; i++) /* days in prior _gx_months */
		gdate += 30;
	gdate += day;   /* days in current month */
//  if (get_1904_mode(si))
//    gdate -= ADJUST_1904;
	return gdate;
}


int  __cdecl _gx_decode_date(int si, long gdate, int *year, int *month, int *day)
{
	// Unused:
	si;

	int m;
	long day_of_quad;
	long quads;

	if (gdate <= 0 || gdate > 73050)
		return 0;
//  if (get_1904_mode(si))
//    gdate += ADJUST_1904;
	quads = (gdate - 1) / 1461;
	day_of_quad = (gdate - 1) % 1461 + 1;
	if (day_of_quad <= 366)
	{
		_gx_months[1].noDays = 29;
		*day = day_of_quad;
		*year = 4 * quads;
	}
	else
	{
		_gx_months[1].noDays = 28;
		*day = (day_of_quad - 366 - 1) % 365 + 1;
		*year = 4 * quads + (day_of_quad - 366 - 1) / 365 + 1;
	}
	m = 0;
	while (*day > _gx_months[m].noDays)
	{
		*day -= _gx_months[m].noDays;
		m++;
	}
	*month = m + 1;
	return 1;
}

int  __cdecl _gx_end_of_month(int m, int y)
{
	switch (m)
	{
	case 4:
	case 6:
	case 9:
	case 11:
		return 30;
	case 2:
		if (GX_LEAPYEAR(y))
			return 29;
		return 28;
	default:
		return 31;
	}
}

/* this version of _gx_edate follows the "end-of-month" rule.  It's called
 * mostly by functions in finance_fns2.c.
 */
long  __cdecl _gx_edate(int si, long start_date, int mos)
{
	// Unused:
	si;

	int month,
		day,
		year,
		yrs,
		femflag = 0;
	long edate;

	_gx_decode_date(si, start_date, &year, &month, &day);
	if ((month == 2) && (day == _gx_end_of_month(month, year)))
		femflag = 1;
	yrs = mos / 12;
	mos = mos % 12;
	year += yrs;
	if ((month += mos) <= 0)
	{
		year--;
		month += 12;
	}
	else if (month > 12)
	{
		year++;
		month -= 12;
	}
	if ((day > _gx_end_of_month(month, year)) || femflag)
		day = _gx_end_of_month(month, year);
	edate = _gx_encode_date(si, year, month, day);
	return edate;
}


/* this function will be called by _gx_fn_yearfrac() and some financial functions. */
void  __cdecl _gx_find_yearfrac1(int si, long start_date, long end_date, int basis, gxNumber * year_frac)
{
	int year1,
		year2,
		month,
		day;
	gxNumber year_basis = 360.0,
			 days;

	_gx_decode_date(si, start_date, &year1, &month, &day);
	_gx_decode_date(si, end_date, &year2, &month, &day);
	if (basis == 0)
		days = _gx_days360(si, start_date, end_date) + 1;
	else
		days = end_date - start_date + 1;

	if (basis == 3)
		year_basis = 365.0;
	else if (basis == 1)
		year_basis = ((!(year1 % 4)) ? 366.0 : 365.0);
	*year_frac = fabs(days / year_basis);
	return;
}


/* this function is slightly different than fin_yearfrac, it is
 * provide for being consistant with many financial functions
 * with Excel and Quatro Pro
 */
void  __cdecl _gx_find_yearfrac(int si, long start_date, long end_date, int basis, gxNumber * year_frac)
{
	int year1,
		year2,
		month,
		day;
	gxNumber year_basis = 360.0,
			 days;

	_gx_decode_date(si, start_date, &year1, &month, &day);
	_gx_decode_date(si, end_date, &year2, &month, &day);
	if (basis == 0)
		days = _gx_days360(si, start_date, end_date);
	else
		days = end_date - start_date;

	if (basis == 3)
		year_basis = 365.0;
	else if (basis == 1)
		year_basis = ((!(year1 % 4)) ? 366.0 : 365.0);
	*year_frac = fabs(days / year_basis);
	return;
}


long  __cdecl _gx_days360(int si, long date1, long date2)
{
	int y1,
		y2,
		m1,
		m2,
		d1,
		d2;

	_gx_decode_date(si, date1, &y1, &m1, &d1);
	_gx_decode_date(si, date2, &y2, &m2, &d2);

	/* convention concerning Feb - "end-of-month rule" */
	if (d1 == _gx_end_of_month(m1, y1))
	{
		d1 = 30;
		if (d2 == _gx_end_of_month(m2, y2))
			d2 = 30;
	}
	/* convention concerning last day of the month */
	if (d1 == 31)
		d1--;
	if ((d2 == 31) && (d1 > 29))
		d2--;
	return (y2 - y1) * 360 + (m2 - m1) * 30 + (d2 - d1);
}

void  __cdecl _gx_current_time(int *yr, int *mo, int *da, int *hr, int *min, int *sec)
{
	time_t timeval;
	struct tm *t = NULL;

	timeval = time(NULL);
	// QA: 31989 - #if Secure Code Cleanup.
	t = localtime(&timeval);
	*yr = t->tm_year;
	*mo = t->tm_mon + 1;
	*da = t->tm_mday;
	*hr = t->tm_hour;
	*min = t->tm_min;
	*sec = t->tm_sec;
}

int  __cdecl _gx_get_date(int si, LPCTSTR date_str, int *mp, int *dp, int *yp, int *fmtp)
{
	// Unused:
	si;

#if _MFC_VER >= 0x0300
	COleDateTime dt;
	if (dt.ParseDateTime(date_str))
	{
		*mp = dt.GetMonth();
		*dp = dt.GetDay();
		*yp = dt.GetYear();

		*fmtp = GX_FMT_DATE;

		return 1;
	}                 
#else                                     
	TIMESTAMP_STRUCT tm;	
	if (GXParseDateTime(&tm, date_str))
	{
		*mp = tm.month;
		*dp = tm.day;
		*yp = tm.year;

		*fmtp = GX_FMT_DATE;

		return 1;
	}                 
#endif
	return 0;
}

int  __cdecl _gx_get_time(LPCTSTR time_str, int *hp, int *mp, int *sp)
{
#if _MFC_VER >= 0x0300
	COleDateTime dt;
	if (dt.ParseDateTime(time_str))
	{
		*hp = dt.GetHour();
		*mp = dt.GetMinute();
		*sp = dt.GetSecond();

		return 1;
	}
#else
	TIMESTAMP_STRUCT tm;	
	if (GXParseDateTime(&tm, time_str))
	{
		*hp = tm.hour;
		*mp = tm.minute;
		*sp = tm.second;

		return 1;
	}                 
#endif
	return 0;
}

int  __cdecl _gx_encode_time(double *timeval, int hr, int min, int sec)
{
	if (hr < 0 || hr > 23 || min < 0 || min > 59 || sec < 0 || sec > 59)
		return 0;
	*timeval = ((sec / 60.0 + min) / 60.0 + hr) / 24.0;
	return 1;
}

int  __cdecl _gx_decode_time(double timeval, int *hr, int *min, int *sec)
{
	register int total;

	timeval -= floor(timeval);  /* throw away the integer part */
	total = (int) (timeval * 24 * 60 * 60 + 0.5);
	*sec = total % 60;
	total /= 60;
	*min = total % 60;
	total /= 60;
	*hr = total;
	return 1;
}
