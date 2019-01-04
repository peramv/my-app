///////////////////////////////////////////////////////////////////////////////
// gxtime2.cpp : Date and Time parsing using the COleDateTime class
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

#if _MFC_VER >= 0x0400 

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

class CGXOleDateTimeImp: public CGXAbstractDateTimeImp
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

void AFXAPI GXImplementOleDateTime()
{
	if (GXGetAppData()->m_pDateTimeImp == NULL)
	{
		// QA: 31521 Removal from AutoDeletePtr
		//GXGetAppData()->AutoDeletePtr(GXGetAppData()->m_pDateTimeImp = new CGXOleDateTimeImp);
		GXGetAppData()->m_pDateTimeImp = new CGXOleDateTimeImp;
	}
}

// public methods
void CGXOleDateTimeImp::UpdateDateTimeSettings()
{
}

GXDateFormat CGXOleDateTimeImp::GetDateFormatFromWinIni(BOOL bReload, BOOL& bCentury, TCHAR& chDateSep)
{
	GX_UNUSED_ALWAYS(bReload);
	GX_UNUSED_ALWAYS(bCentury);
	GX_UNUSED_ALWAYS(chDateSep);

	return gxDEFAULT;
}

TCHAR CGXOleDateTimeImp::GetTimeSeparatorFromWinIni(BOOL bReload)
{
	GX_UNUSED_ALWAYS(bReload);

	return 0;
}

BOOL CGXOleDateTimeImp::ParseDateTime(struct tm* ptm, LPCTSTR szValue, GXDateFormat DateFormat)
{
	GX_UNUSED_ALWAYS(DateFormat);

	// can use COleDateTime for parsing
	COleDateTime date;

	memset(ptm, 0, sizeof(struct tm));

	if (date.ParseDateTime(szValue))
	{
		ptm->tm_year = date.GetYear()-1900; // tm_year is 1900 based
		ptm->tm_mon = date.GetMonth()-1;    // month is zero-based
		ptm->tm_mday = date.GetDay();
		ptm->tm_hour = date.GetHour();
		ptm->tm_min = date.GetMinute();
		ptm->tm_sec = date.GetSecond();

		return TRUE;
	}

	return FALSE;
}

BOOL CGXOleDateTimeImp::ParseDateTime(TIMESTAMP_STRUCT* ptm, LPCTSTR szValue, GXDateFormat DateFormat)
{
	GX_UNUSED_ALWAYS(DateFormat);

	// can use COleDateTime for parsing
	COleDateTime date;

	memset(ptm, 0, sizeof(TIMESTAMP_STRUCT));

	if (date.ParseDateTime(szValue))
	{
		ptm->year = (SWORD) date.GetYear();
		ptm->month = (UWORD) date.GetMonth();
		ptm->day = (UWORD) date.GetDay();
		ptm->hour = (UWORD) date.GetHour();
		ptm->minute = (UWORD) date.GetMinute();
		ptm->second = (UWORD) date.GetSecond();

		return TRUE;
	}

	return FALSE;
}

void CGXOleDateTimeImp::FormatTimeStamp(CString& strRet, const CTime* pTime)
{
	COleDateTime date;

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

void CGXOleDateTimeImp::FormatTimeStamp(CString& strRet, const TIMESTAMP_STRUCT* pTime)
{
	BOOL bTime =
		pTime->hour
		|| pTime->minute
		|| pTime->second;
	BOOL bDate =
		pTime->month > 0;

	// can use COleDateTime formatting
/*
	LPTSTR pFormat;
	if (bTime && bDate)
		pFormat = _T("%c");
	else if (bTime)
		pFormat = _T("%X");
	else
		pFormat = _T("%x");
*/

	DWORD dwFormat;

	if (bTime && bDate)
		dwFormat = LOCALE_NOUSEROVERRIDE;
	else if (bTime)
		dwFormat = LOCALE_NOUSEROVERRIDE | VAR_TIMEVALUEONLY;
	else
		dwFormat = LOCALE_NOUSEROVERRIDE  | VAR_DATEVALUEONLY;

	// Can use COleDateTime formatting
	COleDateTime date(
		pTime->year, pTime->month, pTime->day,
		pTime->hour, pTime->minute, pTime->second);

//	strRet = date.Format(pFormat);
	strRet = date.Format(dwFormat);  
}


#endif // _MFC_VER 
