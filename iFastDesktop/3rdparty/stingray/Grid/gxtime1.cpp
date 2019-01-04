///////////////////////////////////////////////////////////////////////////////
// gxtime.cpp : date and time parsing and formatting 
//              (without using COleDateTime class)
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

// Headers

#include <stddef.h>     /* for size_t */
#include <stdarg.h>     /* for va_arg */
#include <time.h>       /* for struct tm */
#include <ctype.h>

#ifndef _GXEXT_H_
#include "grid\gxext.h"
#endif

#ifndef _GXDLL_H_
#include "grid\gxdll.h"
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXTIME")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif


class CGXNoOleDateTimeImp: public CGXAbstractDateTimeImp
{
public:
	virtual void UpdateDateTimeSettings();
	virtual GXDateFormat GetDateFormatFromWinIni(BOOL bReload, BOOL& bCentury, TCHAR& chDateSep);
	virtual TCHAR GetTimeSeparatorFromWinIni(BOOL bReload);
	virtual BOOL ParseDateTime(struct tm* ptm, LPCTSTR szValue, GXDateFormat DateFormat);
	virtual BOOL ParseDateTime(TIMESTAMP_STRUCT* ptm, LPCTSTR szValue, GXDateFormat DateFormat);
	virtual void FormatTimeStamp(CString& strRet, const CTime* pTime);
	virtual void FormatTimeStamp(CString& strRet, const TIMESTAMP_STRUCT* pTime);
};

void AFXAPI GXImplementNoOleDateTime()
{
	if (GXGetAppData()->m_pDateTimeImp == NULL)
	{
		// QA: 31521 Removal from AutoDeletePtr
		//GXGetAppData()->AutoDeletePtr(GXGetAppData()->m_pDateTimeImp = new CGXNoOleDateTimeImp);
		GXGetAppData()->m_pDateTimeImp = new CGXNoOleDateTimeImp;
	}
}


// NOTE: This methods are provided because parsing
// date/time values was not possible with VC 1.5x
// and VC 2.x projects.
//
// If you are using VC 4.x or greater, we recommend
// using the COleDateTime::ParseDateTime for this
// purpose.

// helper methods:

static void AFXAPI StripLeadingBlanks(CString& sEdit);
static BOOL AFXAPI IsLeapYear(int Year);
static int AFXAPI GetEndMonth (int Month, int Year);
static int AFXAPI GetDD (CString& strDate);
static int AFXAPI GetYY (CString& strDate);
static int AFXAPI GetMM (CString& strDate);

// static data

static int nMonthMax[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
static GXDateFormat s_dateFormat = gxDEFAULT;
static TCHAR s_chTimeSep = 0;
static BOOL s_bCentury = FALSE;
static TCHAR s_chDateSep = '/';

void CGXNoOleDateTimeImp::UpdateDateTimeSettings()
{
	BOOL bCentury;
	TCHAR chDateSep;
	GXGetDateFormatFromWinIni(TRUE, bCentury, chDateSep);
	GXGetTimeSeparatorFromWinIni(TRUE);
}

// public methods
GXDateFormat CGXNoOleDateTimeImp::GetDateFormatFromWinIni(BOOL bReload, BOOL& bCentury, TCHAR& chDateSep)
{
	// Note: In your application, you should process
	// the WM_WININICHANGE message and call
	// GXGetDateFormatFromWinIni(TRUE).

	if (s_dateFormat == gxDEFAULT  || bReload)
	{
		CString sDefault = _T("MM.dd.yy");
		CString sShortDate;
		LPTSTR pszBuffer = sShortDate.GetBuffer(128);
		bCentury = FALSE;
#if _MFC_VER >= 0x0300
		GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_SSHORTDATE, pszBuffer, 128);
#else
		GetProfileString(_T("intl"), _T("sShortDate"), sDefault, pszBuffer, 128);
#endif
		sShortDate.ReleaseBuffer();


		s_dateFormat = gxMMDDYY;
		if (!sShortDate.IsEmpty())
		{
			sShortDate.MakeUpper();
			if (sShortDate[0] == _T('M'))
				s_dateFormat = gxMMDDYY;
			else if (sShortDate[0] == _T('D'))
				s_dateFormat = gxDDMMYY;
			else if (sShortDate[0] == _T('Y'))
				s_dateFormat = gxYYMMDD;

			// display century only when YYYY is found in sShortDate
			s_bCentury = sShortDate.Find(_T("YYYY")) != -1;
            LPCTSTR p = NULL;
			for (p = sShortDate; *p && _istalpha(*p) && *p != _T(' '); p++)
				NULL;

			s_chDateSep = *p;
		}
	}

	bCentury = s_bCentury;
	chDateSep = s_chDateSep;

	return s_dateFormat;
}

TCHAR CGXNoOleDateTimeImp::GetTimeSeparatorFromWinIni(BOOL bReload)
{
	// Note: In your application, you should process
	// the WM_WININICHANGE message and call
	// GXGetDateFormatFromWinIni(TRUE).

	if (s_chTimeSep == 0 || bReload)
	{
		CString sDefault = _T(":");
		CString sTime;
		LPTSTR pszBuffer = sTime.GetBuffer(128);
#if _MFC_VER >= 0x0300
		GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_STIME, pszBuffer, 128);
#else
		GetProfileString(_T("intl"), _T("sTime"), sDefault, pszBuffer, 128);
#endif
		sTime.ReleaseBuffer();

		if (sTime.IsEmpty())
			s_chTimeSep = _T(':');
		else
			s_chTimeSep = sTime[0];
	}

	return s_chTimeSep;
}

BOOL CGXNoOleDateTimeImp::ParseDateTime(struct tm* ptm, LPCTSTR szValue, GXDateFormat DateFormat)
{
	ASSERT(ptm);

	BOOL bValid = TRUE;

	// Split into time/date
	CString sSrc = szValue;
	CString sDate, sTime;

	// clear tm struct
	memset(ptm, 0, sizeof(struct tm));

	// find separators
	TCHAR chTimeSep = GXGetTimeSeparatorFromWinIni(FALSE);
	int nBlank = sSrc.Find(_T(' '));
	int nColon = sSrc.Find(chTimeSep);

	if (nBlank != -1 && nColon > nBlank)
	{
		// Parse date and time
		// Input format: "date hh:mm[:ss]"
		sTime = sSrc.Mid(nBlank+1);
		sDate = sSrc.Left(nBlank);
	}
	else if (nColon != -1)
	{
		// Parse only time
		// Input format: "hh:mm[:ss]"
		sTime = sSrc;
	}
	else
	{
		// Parse only date
		// Input format: "date"
		sDate = sSrc;
	}

	StripLeadingBlanks(sTime);
	StripLeadingBlanks(sDate);

	// Parse time string
	if (!sTime.IsEmpty())
	{
		ptm->tm_year = 70;
		ptm->tm_mon = 0;
		ptm->tm_mday = 1;

		int nColon1 = sTime.Find(chTimeSep);

		// hour
		if (bValid)
		{
			// must use "PM" to make the code to work with both military or AM/PM format
			if ((sTime.Right(2)).CompareNoCase(_T("PM")) == 0 || (sTime.Right(1)).CompareNoCase(_T("P")) == 0)
			{
				ptm->tm_hour = _ttoi(sTime.Left(nColon1)) + 12;
				if (ptm->tm_hour == 24)	// 12:mm PM 
					ptm->tm_hour = 12;
			}
			else
			{
				ptm->tm_hour = _ttoi(sTime.Left(nColon1));
				if ((sTime.Right(2)).CompareNoCase(_T("AM")) == 0 || (sTime.Right(1)).CompareNoCase(_T("A")) == 0)
				{
					bValid &= ptm->tm_hour <= 12;
					if (ptm->tm_hour == 12)	// 12:mm AM
						ptm->tm_hour = 0;
				}
			}

			bValid &= ptm->tm_hour >= 0 && ptm->tm_hour <= 24;
		}

		// minute
		if (bValid && !sTime.IsEmpty())
		{
			sTime = sTime.Mid(nColon1 + 1);
			ptm->tm_min = _ttoi(sTime.Left(2));
			bValid &= ptm->tm_min >= 0 && ptm->tm_min < 60;
		}

		// second
		if (bValid && !sTime.IsEmpty())
		{
			sTime = sTime.Mid(3);
			ptm->tm_sec = _ttoi(sTime.Left(2));
			bValid &= ptm->tm_sec >= 0 && ptm->tm_sec < 60;
		}
	}

	// Parse date string
	if (!sDate.IsEmpty())
	{
		if (sDate != sDate.SpanIncluding(_T("0123456789/-. ")))
		{
			// TRACE0("Invalid character in date\n");
			bValid = FALSE;
		}

		if ( sDate.GetLength() == 6 )
		{
			if (isdigit(sDate[0]) && isdigit(sDate[1]) && isdigit(sDate[2])
				&& isdigit(sDate[3]) && isdigit(sDate[4]) && isdigit(sDate[5]))
				sDate = sDate.Left(2)+_T('/')+sDate.Mid(2,2)+_T('/')+sDate.Right(2);
		}

		BOOL bCentury;

		TCHAR chDateSep;
		if (DateFormat == gxDEFAULT)
			DateFormat = GXGetDateFormatFromWinIni(FALSE, bCentury, chDateSep);

		if (DateFormat == gxDDMMYY)
		{
			bValid = bValid && (ptm->tm_mday = GetDD(sDate)) != -1;
			bValid = bValid && (ptm->tm_mon  = GetMM(sDate)) != -1;
			bValid = bValid && (ptm->tm_year = GetYY(sDate)) != -1;
			bValid = bValid && (ptm->tm_mday <= GetEndMonth(ptm->tm_mon, ptm->tm_year));
		}
		else if (DateFormat == gxMMDDYY)
		{
			bValid = bValid && (ptm->tm_mon  = GetMM(sDate)) != -1;
			bValid = bValid && (ptm->tm_mday = GetDD(sDate)) != -1;
			bValid = bValid && (ptm->tm_year = GetYY(sDate)) != -1;
			bValid = bValid && (ptm->tm_mday <= GetEndMonth(ptm->tm_mon, ptm->tm_year));
		}
		else if (DateFormat == gxYYMMDD)
		{
			bValid = bValid && (ptm->tm_year = GetYY(sDate)) != -1;
			bValid = bValid && (ptm->tm_mon  = GetMM(sDate)) != -1;
			bValid = bValid && (ptm->tm_mday = GetDD(sDate)) != -1;
			bValid = bValid && (ptm->tm_mday <= GetEndMonth(ptm->tm_mon, ptm->tm_year));
		}
		else
		{
			bValid = FALSE;
			ASSERT(0);
			// ASSERTION-> DateFormat is invalid ->END
		}

		if (bValid)
		{
			// make month zero-based
			ptm->tm_mon--;

			// adjust year (time_t only allows from 1970 to 2037)
			if (ptm->tm_year >= 1900)
				ptm->tm_year -= 1900;
			else if (ptm->tm_year <= 37) // year 2000-2037
				ptm->tm_year += 100;
		}
	}

	return bValid;
}

BOOL CGXNoOleDateTimeImp::ParseDateTime(TIMESTAMP_STRUCT* ptm, LPCTSTR szValue, GXDateFormat DateFormat)
{
	ASSERT(ptm);

	BOOL bValid = TRUE;

	// Split into time/date
	CString sSrc = szValue;
	CString sDate, sTime;

	// clear tm struct
	memset(ptm, 0, sizeof(TIMESTAMP_STRUCT));

	// find separators
	TCHAR chTimeSep = GXGetTimeSeparatorFromWinIni(FALSE);
	int nBlank = sSrc.Find(_T(' '));
	int nColon = sSrc.Find(chTimeSep);

	if (nBlank != -1 && nColon > nBlank)
	{
		// Parse date and time
		// Input format: "date hh:mm[:ss]"
		sTime = sSrc.Mid(nBlank+1);
		sDate = sSrc.Left(nBlank);
	}
	else if (nColon != -1)
	{
		// Parse only time
		// Input format: "hh:mm[:ss]"
		sTime = sSrc;
	}
	else
	{
		// Parse only date
		// Input format: "date"
		sDate = sSrc;
	}

	StripLeadingBlanks(sTime);
	StripLeadingBlanks(sDate);

	// Parse time string
	if (!sTime.IsEmpty())
	{
		ptm->year = 70;
		ptm->month = 0;
		ptm->day = 1;

		int nColon1 = sTime.Find(chTimeSep);

		// hour
		if (bValid)
		{
			// must use "PM" to make the code to work with both military or AM/PM format
			if ((sTime.Right(2)).CompareNoCase(_T("PM")) == 0 || (sTime.Right(1)).CompareNoCase(_T("P")) == 0)
			{
				ptm->hour = (UWORD) (_ttoi(sTime.Left(nColon1)) + 12);
				if (ptm->hour == 24)	// 12:mm PM 
					ptm->hour = 12;
			}
			else
			{
				ptm->hour = (UWORD) _ttoi(sTime.Left(nColon1));
				if ((sTime.Right(2)).CompareNoCase(_T("AM")) == 0 || (sTime.Right(1)).CompareNoCase(_T("A")) == 0)
				{
					bValid &= ptm->hour <= 12;
					if (ptm->hour == 12)	// 12:mm AM
						ptm->hour = 0;
				}
			}

			bValid &= ptm->hour >= 0 && ptm->hour <= 24;
		}

		// minute
		if (bValid && !sTime.IsEmpty())
		{
			sTime = sTime.Mid(nColon1 + 1);
			ptm->minute = (UWORD) _ttoi(sTime.Left(2));
			bValid &= ptm->minute >= 0 && ptm->minute < 60;
		}

		// secondond
		if (bValid && !sTime.IsEmpty())
		{
			sTime = sTime.Mid(3);
			ptm->second = (UWORD) _ttoi(sTime.Left(2));
			bValid &= ptm->second >= 0 && ptm->second < 60;
		}
	}

	// Parse date string
	if (!sDate.IsEmpty())
	{
		if (sDate != sDate.SpanIncluding(_T("0123456789/-. ")))
		{
			// TRACE0("Invalid character in date\n");
			bValid = FALSE;
		}

		if( sDate.GetLength() == 6 )
			if (isdigit(sDate[0]) && isdigit(sDate[1]) && isdigit(sDate[2])
				&& isdigit(sDate[3]) && isdigit(sDate[4]) && isdigit(sDate[5]))
				sDate = sDate.Left(2)+_T('/')+sDate.Mid(2,2)+_T('/')+sDate.Right(2);

		BOOL bCentury;

		TCHAR chDateSep;
		if (DateFormat == gxDEFAULT)
			DateFormat = GXGetDateFormatFromWinIni(FALSE, bCentury, chDateSep);

		if (DateFormat == gxDDMMYY)
		{
			bValid = bValid && (ptm->day = (UWORD) GetDD(sDate)) != (UWORD) -1;
			bValid = bValid && (ptm->month  = (UWORD) GetMM(sDate)) != (UWORD) -1;
			bValid = bValid && (ptm->year = (SWORD) GetYY(sDate)) != (SWORD) -1;
			bValid = bValid && (ptm->day <= (UWORD) GetEndMonth(ptm->month, ptm->year));
		}
		else if (DateFormat == gxMMDDYY)
		{
			bValid = bValid && (ptm->month  = (UWORD) GetMM(sDate)) != (UWORD) -1;
			bValid = bValid && (ptm->day = (UWORD) GetDD(sDate)) != (UWORD) -1;
			bValid = bValid && (ptm->year = (SWORD) GetYY(sDate)) != (SWORD) -1;
			bValid = bValid && (ptm->day <= (UWORD) GetEndMonth(ptm->month, ptm->year));
		}
		else if (DateFormat == gxYYMMDD)
		{
			bValid = bValid && (ptm->year = (SWORD) GetYY(sDate)) != (SWORD) -1;
			bValid = bValid && (ptm->month  = (UWORD) GetMM(sDate)) != (UWORD) -1;
			bValid = bValid && (ptm->day = (UWORD) GetDD(sDate)) != (UWORD) -1;
			bValid = bValid && (ptm->day <= (UWORD) GetEndMonth(ptm->month, ptm->year));
		}
		else
		{
			bValid = FALSE;
			ASSERT(0);
			// ASSERTION-> DateFormat is invalid ->END
		}
	}

	return bValid;
}

void CGXNoOleDateTimeImp::FormatTimeStamp(CString& strRet, const CTime* pTime)
{
	BOOL bTime =
		pTime->GetHour()
		|| pTime->GetMinute()
		|| pTime->GetSecond();
	BOOL bDate =
		pTime->GetMonth() > 0;

#if _MFC_VER >= 0x0300
	// can use CTime::Format member
	if (bTime && bDate)
		strRet = pTime->Format(_T("%c"));
	else if (bTime)
		strRet = pTime->Format(_T("%X"));
	else
		strRet = pTime->Format(_T("%x"));
#else
	// need to use my own Format method
	TCHAR szBuffer[64];
	struct tm* ptmTemp = pTime->GetLocalTm( NULL );
	ASSERT(ptmTemp != NULL); // make sure the time has been initialized!

	LPTSTR pFormat;

	if (bTime && bDate)
		pFormat = _T("%c");
	else if (bTime)
		pFormat = _T("%X");
	else
		pFormat = _T("%x");

	if (!GXIntlStrFtime(GXGetResourceHandle( ), GX_IDS_TIME_ADAY1,
		szBuffer, sizeof(szBuffer), pFormat, ptmTemp))
	szBuffer[0] = '\0';

	strRet = szBuffer;
#endif
}

void CGXNoOleDateTimeImp::FormatTimeStamp(CString& strRet, const TIMESTAMP_STRUCT* pTime)
{
	BOOL bTime =
		pTime->hour
		|| pTime->minute
		|| pTime->second;
	BOOL bDate =
		pTime->month > 0;

	// need to use my own Format method

	BOOL bCentury;
	TCHAR chDateSep;
	GXDateFormat DateFormat = GXGetDateFormatFromWinIni(FALSE, bCentury, chDateSep);
	TCHAR chSep = GXGetTimeSeparatorFromWinIni();

	CString sDate;
	CString sTime;

	if (bDate)
	{
		LPTSTR pszBuf = sDate.GetBuffer(128);

		if (bCentury)
		{
			// display 4-digit year
			if (DateFormat == gxDDMMYY)
				wsprintf(pszBuf, _T("%02d%c%02d%c%04d"),
					pTime->day, chDateSep, pTime->month, chDateSep, pTime->year);
			else if (DateFormat == gxMMDDYY)
				wsprintf(pszBuf, _T("%02d%c%02d%c%04d"),
					pTime->month, chDateSep, pTime->day, chDateSep, pTime->year);
			else if (DateFormat == gxYYMMDD)
				wsprintf(pszBuf, _T("%04d%c%02d%c%02d"),
					pTime->year, chDateSep, pTime->month, chDateSep, pTime->day);
		}
		else
		{
			// display 2-digit year
			if (DateFormat == gxDDMMYY)
				wsprintf(pszBuf, _T("%02d%c%02d%c%02d"),
					pTime->day, chDateSep, pTime->month, chDateSep, pTime->year%100);
			else if (DateFormat == gxMMDDYY)
				wsprintf(pszBuf, _T("%02d%c%02d%c%02d"),
					pTime->month, chDateSep, pTime->day, chDateSep, pTime->year%100);
			else if (DateFormat == gxYYMMDD)
				wsprintf(pszBuf, _T("%02d%c%02d%c%02d"),
					pTime->year%100, chDateSep, pTime->month, chDateSep, pTime->day);
		}
		sDate.ReleaseBuffer();
	}

	if (bTime)
	{
		LPTSTR pszBuf = sTime.GetBuffer(128);

		wsprintf(pszBuf, _T("%02d%c%02d%c%02d"),
			pTime->hour, chSep, pTime->minute, chSep, pTime->second);

		sTime.ReleaseBuffer();
	}

	strRet = sDate;
	if (bDate && bTime)
		strRet += _T(" ");
	if (bTime)
		strRet +=sTime;
}

////////////////////////////////////////////////////////////////////////
// Implemenation

static void AFXAPI StripLeadingBlanks(CString& sEdit)
{
	// find first non-space character
	LPCTSTR lpsz = sEdit;
	int n = 0;
	while (*lpsz == _T(' '))
	{
		lpsz = _tcsinc(lpsz);
		n++;
	}

	// fix up data
	if (n > 0)
		sEdit = sEdit.Mid(n);
}

static BOOL AFXAPI IsLeapYear(int nYear)
{
	return (((nYear % 4 == 0) && (nYear % 100 != 0)) || (nYear % 400 == 0));
}

// GetEndMonth
//
// Determines the number of days in the month

static int AFXAPI GetEndMonth (int nMonth, int nYear)
{
	ASSERT (nMonth >= 1);
	ASSERT (nMonth <= 12);

	int nLastDay = nMonthMax [nMonth-1];

	if (nMonth == 2)         // check for leap year
		if (IsLeapYear (nYear))
			nLastDay++;

	return nLastDay;
}

// GetDD
//
// Strips the leading two numbers from the string passed as
// an argument and returns them.  Also returns the string
// that was passed minus the two numbers.

static int AFXAPI GetDD (CString& strDate)
{
	// Get DD nDay Value
	if (strDate.GetLength())
	{
		StripLeadingBlanks(strDate);

		if(!isdigit(strDate[0]))
			strDate = strDate.Mid(1);
		int nChars;
		for (nChars = 0; nChars < strDate.GetLength() && isdigit(strDate[nChars]); nChars++)
			NULL;

		if (nChars == 0 || nChars > 2)          // string is bad
			return -1;

		int nDay = _ttoi(strDate);

		if (nDay > 31  || nDay < 1)
		{
			TRACE0("nDay must be between 1 and 31");
			return -1;
		}

		strDate = strDate.Mid(nChars);      // strip off the DD value

		return nDay;
	}
	else
		return -1;
}

// GetYY
//
// Strips the first two numbers from a string passed
// as an argument and returns them as the year.  Also
// returns the string minus the two numbers.

static int AFXAPI GetYY (CString& strDate)
{
	// Get YY Value
	if (strDate.GetLength())
	{
		StripLeadingBlanks(strDate);

		if(!isdigit(strDate[0]))
			strDate = strDate.Mid(1);
		int nChars;
		for (nChars = 0; nChars < strDate.GetLength() && isdigit(strDate[nChars]); nChars++)
			NULL;

		if (nChars == 0 || nChars > 4)          // string is bad
			return -1;

		int nYear = _ttoi(strDate);

		if (nChars <= 2)
		{
			// if only 2 digits, make it the current century
			// (when this tool were written).
			if (nYear > 0 && nYear < 100)
				nYear += 1900;

			// User can input years from 0 to 100 by typing in
			// a "0" before the year, e.g. 01.01.0060 or 01.01.060
			// but if he enters 01.01.60, the year will become
			// 01.01.1960.
		}

		strDate = strDate.Mid(nChars);      // strip off the YY value

		return nYear;
	}
	else
		return -1;
}

// GetMM
//
// Strips the leading two numbers from the string passed as
// an argument and returns the month.  Also returns the string
// that was passed minus the two numbers.

static int AFXAPI GetMM (CString& strDate)
{
	// Get MM Value
	if (strDate.GetLength())
	{
		StripLeadingBlanks(strDate);

		if(!isdigit(strDate[0]))
			strDate = strDate.Mid(1);
		int nChars;
		for (nChars = 0; nChars < strDate.GetLength() && isdigit(strDate[nChars]); nChars++)
			NULL;

		if (nChars == 0 || nChars > 2)          // string is bad
			return -1;

		int nMonth = _ttoi(strDate);

		if ((nMonth == 0) || (nMonth > 12))
		{
			TRACE0("Month must be between 1 and 12");
			return -1;
		}

		strDate = strDate.Mid(nChars);      // strip off the MM value

		return nMonth;
	}
	else
		return -1;
}
