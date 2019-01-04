///////////////////////////////////////////////////////////////////////////////
// gxformat.cpp : Number formatting for numeric cells
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

#define _OG_EXPORT_IMPL

#include "stdafx.h"

#ifdef _GXDLL
#undef AFXAPI_DATA
#define AFXAPI_DATA __based(__segname("_DATA"))
#endif

#include <float.h>
#include <math.h>
#include <ctype.h>

// Headers
#ifndef _GXEXT_H_
#include "grid\gxext.h"
#endif

#ifndef _GXRESRC_H_
#include "grid\gxresrc.h"
#endif

#ifndef _GXSTATE_H_
#include "grid\gxstate.h"
#endif

#ifndef _GXDLL_H_
#include "grid\gxdll.h"
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXFORMAT")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

#pragma warning(disable: 4244)

class CGXNumberFormattingImp: public CGXAbstractNumberFormattingImp
{
public:
	// Text formatting and parsing
	virtual CString GXFormatText(const CGXStyle& style, LPCTSTR pszValue, unsigned nValueType, CGXGridCore* pGrid, CGXControl* pControl);
	virtual BOOL GXDeval(LPCTSTR s, double *d, unsigned* pImportFormat, unsigned* pImportPlaces);
};

void AFXAPI CGXDrawingAndFormatting::ImplementNumberFormatting()
{
	if (GXGetAppData()->m_pNumberFormattingImp == NULL)
	{
		//GXGetAppData()->AutoDeletePtr(GXGetAppData()->m_pNumberFormattingImp = new CGXNumberFormattingImp);
		GXGetAppData()->m_pNumberFormattingImp = new CGXNumberFormattingImp;
	}
}

int AFXAPI GXDecodeDate(long gdate, int *year, int *month, int *day);
int AFXAPI GXDecodeTime(double timeval, int *hr, int *min, int *sec);

const LONG primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
const int numberOfPrimes = 12;

static void mix_fractions(LONG& numerator, LONG& denominator)
{
    //LONG limit =(LONG) sqrt((double)numerator);

	int nPrime = 0;
	
	while (nPrime < numberOfPrimes && primes[nPrime]<= sqrt((double)numerator))
	
	{
    	while (denominator % primes[nPrime] == 0  && numerator % primes[nPrime] == 0)
		{
            denominator /=primes[nPrime];
		     numerator /= primes[nPrime];
		}
		nPrime++;
	}
	
}

static void add_commas(LPTSTR dst, LPCTSTR src, TCHAR d_sep, TCHAR t_sep)
{
	register LPCTSTR s;
	register LPTSTR d;
	register int count=0;

	s = src;
	while (*s)
    {
		if (*s++ == d_sep)//_T('.'))
			break;
		++count;
    }
	s = src;
	d = dst;
	while (*s)
    {
		if (*s == d_sep)//_T('.'))
			*d = d_sep;
		else
			*d = *s;
		d++;
		s++;
		if (count>3)
			if ((--count)%3 == 0) *d++ = t_sep;
    }
	*d = _T('\0');
}

BOOL CGXNumberFormattingImp::GXDeval(LPCTSTR s, double *d, unsigned* pImportFormat, unsigned* pImportPlaces)
/*
Tries to evaluate the entire string s as a double.  If successful, the
double is returned in d, and the function returns True.  Otherwise,
d is not altered and the function returns False.
*/
{
	TCHAR decsep = GXGetAppData()->charDecSep[0];
	TCHAR grpsep = GXGetAppData()->charGrpSep[0];
	
	const int maxCount = 256;
    double x;
    LPTSTR p;
	TCHAR buf[maxCount+1], c;
    int i, n, count = 0;
    int comma_index[20], comma_count = 0, decimal = 0, decimal_index = 0,
		dollars = 0, exponential = 0, exp_index = 0, digits = 0, places = 0,
		open_paren = 0, close_p_index = 0;
	
	/* strip leading and trailing spaces */
    while (*s == _T(' ')) 
		s++;	

    if (*s == _T('('))
	{
		s++;	/* could be negative of the form (123,456) */
		open_paren = 1;
	}

    if (*s == _T('$'))
	{
		s++;	/* strip leading '$' */
		dollars = 1;
	}

    p = buf;
    count = 0;
    while ((c = *s++) != 0)
	{
		if (c == grpsep) // _T(','))	/* strip commas but keep track of where they were */
		{
			comma_index[comma_count++] = count;
			if (comma_count == 20) 
				return 0;	/* just too many! */
		}
		else if (c == decsep)//_T('.'))				/* decimal point */
		{
			if (decimal) 
				return 0;			/* only one decimal point */

			decimal_index = count;
			decimal = 1;
			*p++ = c;
		}
		else if (c == _T('e') || c == _T('E'))
		{
			if (exponential) 
				return 0;		/* only one 'e' */
			if (open_paren) 
				return 0;
			exp_index = count;
			exponential = 1;
			*p++ = c;
		}
		else if (c == _T('+') || c == _T('-'))
		{
			if (open_paren) 
				return 0;
			*p++ = c;
		}
		else if (_istdigit(c))
		{
			*p++ = c;
			if (!exponential)
			{
				digits++;				/* one more sig digit */
				if (decimal)
					places++;			/* one more decimal place */
			}
		}
		else if (open_paren && c == _T(')') && *s == _T('\0'))
		{
			close_p_index = count;
			*p++ = c;
		}
		else if (c == _T(' '))
		{
			// check if there are any nonblank chars left
		    while (*s == _T(' '))
				s++;

			if (*s)
				return 0; // no blank but also not EOS
		}
		else
			return 0;
		if (count++ > maxCount)
			return 0;
	}
    *p = _T('\0');

    p = buf;
    if (comma_count)	/* make sure the commas were in the right places */
	{
		if (decimal)
			n = decimal_index;
		else if (close_p_index)
			n = close_p_index;
		else if (exponential)
			n = exp_index;
		else
			n = count;
		for (i = 0; i < comma_count; i++)
			if ((n - comma_index[i])%4) 
				return 0;
	}

    x = _tcstod(buf, &p);
    if (open_paren)		/* check for close paren */
	{
		if (*p != _T(')')) 
			return 0;
		p++;
	}
    
	if ((n = p - buf) != (int) _tcslen(buf)) 
		return 0;

    switch (n)
	{
   	case 0:
		return 0;
	case 1:
		if (!_istdigit(*buf)) 
			return 0;
		break;
	}

    if (open_paren)
		*d = -x;
    else
		*d = x;
    if (places > 15) places = 15;
    if (digits > 16) digits = 16;
	

	if (pImportFormat && pImportPlaces)
	{
		if (exponential)
		{
			*pImportFormat = GX_FMT_FLOAT;
			*pImportPlaces = digits - 1;
		}
		else if (dollars)
		{
			*pImportFormat = GX_FMT_DOLLARS;
			*pImportPlaces = places;
		}
		else if (comma_count || open_paren)
		{
			*pImportFormat = GX_FMT_COMMA;
			*pImportPlaces = places;
		}
		else
		{
			*pImportFormat = GX_FMT_FIXED;
			*pImportPlaces = places;
		}
	}

    return 1;
}

// GXFormatText - Cell formatting (numbers, dates)
//
// NOTE: With OG 6.0 we only provide some basic and very limited
// formatting capabilities. We will extend this in future versions
// to be more Excel like with support for custom and international formats.
//
// One very weak point in the formatting right now is that we have no currency
// formatting. What you can do to add this is subclass CGXDrawingAndFormatting
// and override GXFormatText. Then you can add your own format codes (or use
// the currently unused format codes (GX_FMT_USER1 .. GX_FMT_USER4)
// and format the value to your needs.

CString CGXNumberFormattingImp::GXFormatText(const CGXStyle& style, LPCTSTR pszValue, unsigned nValueType, CGXGridCore* pGrid, CGXControl* pControl )
{					 
// Unused:
	pControl, pGrid;
	
	TCHAR decsep = GXGetAppData()->charDecSep[0];
	TCHAR grpsep = GXGetAppData()->charGrpSep[0];

	const int maxCount = 256;
	TCHAR fmt[40],			/* buffer for format string */
		temp_text[maxCount];	/* temporary text buffer */

	if (pszValue == NULL)
	{
		pszValue = style.GetValueRef();
		nValueType = style.GetValueType();
	}

	if (!style.GetIncludeFormat())
		return pszValue;

	unsigned fmt_code = style.GetFormat();
	unsigned places = style.GetPlaces();

	CString s;
	double value = 0.0;

	if (fmt_code == GX_FMT_HIDDEN)
		return s;

	if (nValueType != GX_VT_NUMERIC)
		fmt_code = GX_FMT_TEXT;
	else
	{	
		//check to see if need to add proper decsep
		if(decsep != _T('.'))
		{
			CString s1 = pszValue; //need a copy
			int i = s1.Find(_T('.'));
			if(i > -1)
				s1.SetAt(i, decsep);
			value = _gxttof(s1);
		}
		else
			value = _gxttof(pszValue);
	}

	TRY
	{
		switch (fmt_code)
		{
		case GX_FMT_FIXED_PARENS:
			// QA: 31989 - #if Secure Code Cleanup.
			_stprintf(fmt, _T("%%.%dlf"), places);
			s.Format(fmt, fabs(value));
		   	add_commas(temp_text, s, decsep, grpsep);
            if( value<0. )
			     s.Format(_T("(%s)"), temp_text);
			else
				 s.Format(_T(" %s "), temp_text);
            break;

		case GX_FMT_MIXED_FRACTIONS:
			{
				if(places>6 || places < 1)
					places = 3;
				
				LONG numerator, denominator;
				double tempValue = fabs(value);
				
				denominator =(LONG) pow((double)10, (double) (places + 2) );

                numerator =(LONG) ((double) denominator * ( tempValue - floor(tempValue)) );

                mix_fractions(numerator, denominator);

				// this code truncates to places digits
				//s.Format(_T("%d"), denominator);
				//if( s.GetLength() > (int) places)
				//{
				//	s= _T("9999999999999");
				//	s = s.Left(places);
				//	numerator = (LONG)  (atof(s) * (float)numerator / (float)denominator);
                //    denominator = atoi(s);
                //}

				s.Format( _T(" %d/%d"),numerator, denominator);
				
				if( tempValue>= (double) 1 )
				{   
					// QA: 31989 - #if Secure Code Cleanup.
					_stprintf(fmt, _T("%d"), (LONG)floor(tempValue));
					s = fmt + s;
				}
			 	
				if(value < 0)
					s = _T('-') + s;
				else
					s = _T(' ') + s;
			}
		   break;
		case GX_FMT_USER1:
		case GX_FMT_USER2:
		case GX_FMT_USER3:
		case GX_FMT_USER4:
			// Note: if you override GXFormatText you might use
			// these format codes (GX_FMT_USER1 .. GX_FMT_USER4)
			// for your own currenct formatting (e.g. DM, Lira etc).

		case GX_FMT_DEFAULT:
		case GX_FMT_TEXT:
			s = pszValue;
			break;

		case GX_FMT_GEN:
			// QA: 31989 - #if Secure Code Cleanup.
			_stprintf(fmt, _T("%%.%dlg"), places);
			s.Format(fmt, value);
			break;

		case GX_FMT_FLOAT:
			// QA: 31989 - #if Secure Code Cleanup.
			_stprintf(fmt, _T("%%.%dle"), places);
			s.Format(fmt, value);
			break;

		case GX_FMT_FIXED:
			// QA: 31989 - #if Secure Code Cleanup.
			_stprintf(fmt, _T("%%.%dlf"), places);
			s.Format(fmt, value);
			break;

		case GX_FMT_PERCENT:
			if (value >= DBL_MAX / 100.0)
				s = _T(" Percent! ");
			else
			{
				// QA: 31989 - #if Secure Code Cleanup.
				_stprintf(fmt, _T("%%.%dlf%%%%"), places);
				s.Format(fmt, value * 100.0);
			}
			break;

		case GX_FMT_NUMLOCALE:
			s.Format(_T("%.14g"), value);
			if( GetNumberFormat(	LOCALE_USER_DEFAULT, // locale
									0,       // options  allow user overrides
									s,       // input number string
									NULL,  // formatting information
									temp_text,      // output buffer
									maxCount   )       // size of output buffer
				> 0 )
			{
				//allow space to right align with neg numbers
				s = temp_text;
				if (_istdigit(s.GetAt(s.GetLength()-1)))
				{
					s.Format(_T("%s "), temp_text);  
				}
				break;
			}
			// else fall through to GX_FMT_COMMA
		case GX_FMT_COMMA:
			// QA: 31989 - #if Secure Code Cleanup.
			_stprintf(fmt, _T("%%.%dlf"), places);
			s.Format(fmt, fabs(value));
			add_commas(temp_text, s, decsep, grpsep);
			if (value < 0.)
	      		s.Format(_T("(%s)"), temp_text);
			else
	      		s.Format(_T("%s "), temp_text);
			break;

		case GX_FMT_DOLLARS:
			// QA: 31989 - #if Secure Code Cleanup.
			_stprintf(fmt, _T("%%.%dlf"), places);
			s.Format(fmt, fabs(value));
			add_commas(temp_text, s, decsep, grpsep);
			if (value < 0.)
	      		s.Format(_T("($%s)"), temp_text);
			else
	      		s.Format(_T("$%s "), temp_text);
			break;

		case GX_FMT_HEX:
			s.Format(_T("0x%X"), abs((int) value));
			break;

		case GX_FMT_LOGIC:
			if (value < 0.0 || value >= 2.0)
				s = _T("?");
			else switch ((int) value)
			{
			case 0:
				s = _T("0");
				break;
			case 1:
				s = _T("1");
				break;
			default:
				s = _T("?");
			}
			break;

#if _MFC_VER >= 0x0300
       case GX_FMT_TIME_HM_AMPM:
			{	// h:mm AM/PM    11:03 AM
				COleDateTime dt = value;
				s = dt.Format(_T("%I:%M %p"));
			}
			break;

		case GX_FMT_TIME_HMS_AMPM:
			{	// h:mm: AM/PM    11:03:15 AM
				COleDateTime dt = value;
				s = dt.Format(_T("%I:%M:%S %p"));
			}
			break;

		case GX_FMT_TIME_HM:
			{	// h:mm      13:03  
				COleDateTime dt = value;
				s = dt.Format(_T("%H:%M"));
			}
			break;
		case GX_FMT_DAY_MONTH_YEAR:
			{	// DD-MMM-YY  Displays the date as a Gregorian date, in the format 01-Aug-91
				COleDateTime dt = value;
				s = dt.Format(_T("%d-%b-%y"));
			}
			break;

		case GX_FMT_MONTH_YEAR:
			{	// MMM-YY  Displays the date in the format Aug-91.  
				COleDateTime dt = value;
				s = dt.Format(_T("%b-%y"));
			}
			break;

		case GX_FMT_DAY_MONTH:
			{	// DD-MMM  Displays the date in the format 01-Aug.  
				COleDateTime dt = value;
				s = dt.Format(_T("%d-%b"));
			}
			break;

		case GX_FMT_INTL_DATE:
			{	// DD.MM.YYYY  Displays the date in the format 01.08.1991.
				COleDateTime dt = value;
				s = dt.Format(_T("%d.%m.%Y"));
			}
			break;

		case GX_FMT_ISO8061_DATE:
			{	// YYYY-MM-DD  Displays the date in the ISO 8061 date format 1991-08-01.  
				COleDateTime dt = value;
				s = dt.Format(_T("%Y-%m-%d"));
			}
			break;
			
		case GX_FMT_DATE:
			{	// Displays the date as specified in system settings
				COleDateTime dt = (double) (int) value;  // cut time part of value
				s = dt.Format();
			}
			break;
			
		case GX_FMT_TIME:
			{	// Displays the time as specified in system settings
				COleDateTime dt = fmod(value, 1.00);	// cut date part of value
				s = dt.Format();
			}
			break;

		case GX_FMT_DATETIME:
			{	// Displays the date and/or time as specified in system settings
				COleDateTime dt = value;
				s = dt.Format();
			}
			break;
#else
		case GX_FMT_DAY_MONTH_YEAR:
			{	// DD-MMM-YY  Displays the date as a Gregorian date, in the format 01-Aug-91
				TIMESTAMP_STRUCT tm;      
				memset(&tm, 0, sizeof(TIMESTAMP_STRUCT));
				int year, month, day;
				GXDecodeDate((long) value, &year, &month, &day);
				GXFormatTimeStamp(s, &tm);
				tm.year = (SWORD) year;
				tm.month = (UWORD) month;
				tm.day = (UWORD) day;
				GXFormatTimeStamp(s, &tm);
			}
			break;

		case GX_FMT_MONTH_YEAR:
			{	// MMM-YY  Displays the date in the format Aug-91.  
				TIMESTAMP_STRUCT tm;
				memset(&tm, 0, sizeof(TIMESTAMP_STRUCT));
				int year, month, day;
				GXDecodeDate((long) value, &year, &month, &day);
				tm.year = (SWORD) year;
				tm.month = (UWORD) month;
				tm.day = (UWORD) day;
				GXFormatTimeStamp(s, &tm);
			}
			break;


		case GX_FMT_DAY_MONTH:
			{	// DD-MMM  Displays the date in the format 01-Aug.  
				TIMESTAMP_STRUCT tm;
				memset(&tm, 0, sizeof(TIMESTAMP_STRUCT));
				int year, month, day;
				GXDecodeDate((long) value, &year, &month, &day);
				tm.year = (SWORD) year;
				tm.month = (UWORD) month;
				tm.day = (UWORD) day;
				GXFormatTimeStamp(s, &tm);
			}
			break;

		case GX_FMT_INTL_DATE:
			{	// DD.MM.YYYY  Displays the date in the format 01.08.1991.
				TIMESTAMP_STRUCT tm;
				int year, month, day;
				memset(&tm, 0, sizeof(TIMESTAMP_STRUCT));
				GXDecodeDate((long) value, &year, &month, &day);
				tm.year = (SWORD) year;
				tm.month = (UWORD) month;
				tm.day = (UWORD) day;
				GXFormatTimeStamp(s, &tm);
			}
			break;

		case GX_FMT_ISO8061_DATE:
			{	// YYYY-MM-DD  Displays the date in the ISO 8061 date format 1991-08-01.  
				TIMESTAMP_STRUCT tm;
				memset(&tm, 0, sizeof(TIMESTAMP_STRUCT));
				int year, month, day;
				GXDecodeDate((long) value, &year, &month, &day);
				tm.year = (SWORD) year;
				tm.month = (UWORD) month;
				tm.day = (UWORD) day;
				GXFormatTimeStamp(s, &tm);
			}
			break;
			
		case GX_FMT_DATE:
			{	// Displays the date as specified in system settings
				TIMESTAMP_STRUCT tm;
				memset(&tm, 0, sizeof(TIMESTAMP_STRUCT));
				int year, month, day;
				GXDecodeDate((long) value, &year, &month, &day);
				tm.year = (SWORD) year;
				tm.month = (UWORD) month;
				tm.day = (UWORD) day;
				GXFormatTimeStamp(s, &tm);
			}
			break;
			
		case GX_FMT_TIME:
			{	// Displays the time as specified in system settings
				double v = fmod(value, 1.00);	// cut date part of value
				TIMESTAMP_STRUCT tm;
				memset(&tm, 0, sizeof(TIMESTAMP_STRUCT));
				int hour, minute, second;
				GXDecodeTime(v, &hour, &minute, &second);
				tm.hour = (UWORD) hour;
				tm.minute = (UWORD) minute;
				tm.second = (UWORD) second;
				GXFormatTimeStamp(s, &tm);
			}
			break;

		case GX_FMT_DATETIME:
			{	// Displays the date and/or time as specified in system settings
				TIMESTAMP_STRUCT tm;
				memset(&tm, 0, sizeof(TIMESTAMP_STRUCT));
				int year, month, day;
				GXDecodeDate((long) value, &year, &month, &day);
				tm.year = (SWORD) year;
				tm.month = (UWORD) month;
				tm.day = (UWORD) day;
				double v = fmod(value, 1.00);	// cut date part of value
				int hour, minute, second;
				GXDecodeTime(v, &hour, &minute, &second);
				tm.hour = (UWORD) hour;
				tm.minute = (UWORD) minute;
				tm.second = (UWORD) second;
				GXFormatTimeStamp(s, &tm);
			}
			break;
#endif

		default:
			s = _T(" Format? ");
			break;
		}
	}
	CATCH_ALL(e)
	{
		s = pszValue;
		GX_THROW_LAST
	}
	END_CATCH_ALL

	return s;
}


// 16-bit date suppport (16-Bit does not support COleDateTime)

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

int AFXAPI GXDecodeDate(long gdate, int *year, int *month, int *day)
{
	int m;
	long day_of_quad;
	long quads;

	if (gdate <= 0 || gdate > 73050)
		return 0;
	quads = (gdate - 1) / 1461;
	day_of_quad = (gdate - 1) % 1461 + 1;
	if (day_of_quad <= 366)
	{
		_gx_months[1].noDays = 29;
		*day = (int) day_of_quad;
		*year = (int) (4 * quads);
	}
	else
	{
		_gx_months[1].noDays = 28;
		*day = (int) ((day_of_quad - 366 - 1) % 365 + 1);
		*year = (int) (4 * quads + (day_of_quad - 366 - 1) / 365 + 1);
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

int AFXAPI GXDecodeTime(double timeval, int *hr, int *min, int *sec)
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
