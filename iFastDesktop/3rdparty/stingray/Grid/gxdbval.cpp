///////////////////////////////////////////////////////////////////////////////
// gxdbval.cpp : helper routines for reading/writing
//               string values in a recordset
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


// compile this file only if ODBC is supported
#ifndef _AFX_NO_DB_SUPPORT

#ifdef _GXDLL
// used for MFC 2.5 Extension DLL
	#undef AFXAPI_DATA
	#define AFXAPI_DATA __based(__segname("_DATA"))
#endif

// Headers

#ifndef _GXDLL_H_
#include "grid\gxdll.h"
#endif

#ifndef _GXODBC_H_
//#ifndef _WIN64 //RW64
#include "grid\gxodbc.h"
//#endif //_WIN64
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXDBVAL")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

const int MAX_NUM_STRING_SIZE = 29;

// helper routine which converts the value into a string

BOOL GXGetODBCValueString(CString& strRet, CRecordset* pRecordset, void* pv, int nDataType, DWORD dwSize, BOOL bDisplayMemo)
{
#if _MFC_VER >= 0x0420
	dwSize; // is obsolete in VC 4.2
#endif

	strRet.Empty();

	if (!pRecordset->IsFieldNull(pv))
	{
		switch(nDataType)
		{
		case AFX_RFX_BINARY:
			// not supported data types
			//
			// NOTE: It is possible to convert the value for these special data types
			// in the CGXControl::Draw method.
			//
			// An example would be a CGXDbBitmapControl class, where you you could convert a
			// AFX_RFX_LONGBINARY field to a bitmap.
			//
			return FALSE;

		case AFX_RFX_LONGBINARY:
			if (bDisplayMemo)
			{
				// convert CLongBinary to a string
				CLongBinary* plbMemo = (CLongBinary*) pv;

				// lock memory and convert if succesfull
				LPSTR pSrcStr = (LPSTR) GlobalLock(plbMemo->m_hData);
				if (pSrcStr && plbMemo->m_dwDataLength < INT_MAX)
				{
					int cb = (int) plbMemo->m_dwDataLength;
#ifndef _UNICODE
					LPTSTR pDestStr = strRet.GetBuffer(cb*sizeof(TCHAR));
					memcpy(pDestStr, pSrcStr, (size_t) plbMemo->m_dwDataLength);
#else
					// We need to convert the memo field to an UNICODE string
					int nSize = MultiByteToWideChar(CP_ACP, 0, pSrcStr, cb, NULL, 0);
					LPTSTR pDestStr = strRet.GetBuffer(nSize);
					MultiByteToWideChar(CP_ACP, 0, pSrcStr, cb, pDestStr, nSize);
#endif
					strRet.ReleaseBuffer();
					GlobalUnlock(plbMemo->m_hData);
				}
			}
			else
				return FALSE;
			break;

        // [VC7] Map new text types to AFX_RFX_TEXT.
#if (_MFC_VER >= 0x0700)
		case AFX_RFX_ATEXT:
		case AFX_RFX_WTEXT:
#endif
		case AFX_RFX_TEXT:
			strRet = *(CString*) pv;
			break;

		case AFX_RFX_BOOL:
			if (*(BOOL*) pv != AFX_RFX_BOOL_PSEUDO_NULL)
				strRet = *(BOOL*) pv ? _T("TRUE") : _T("FALSE");
			break;

		case  AFX_RFX_BYTE:
			if (*(BYTE*) pv != AFX_RFX_BYTE_PSEUDO_NULL)
			{
				wsprintf(strRet.GetBuffer(MAX_NUM_STRING_SIZE), _T("%u"), (WORD) *(BYTE*) pv);
				strRet.ReleaseBuffer();
			}
			break;

		case   AFX_RFX_INT:
			if (*(int*) pv != AFX_RFX_INT_PSEUDO_NULL)
			{
				wsprintf(strRet.GetBuffer(MAX_NUM_STRING_SIZE), _T("%ld"), (long) *(int*)pv);
				strRet.ReleaseBuffer();
			}
			break;

		case   AFX_RFX_LONG:
			if (*(long*) pv != AFX_RFX_LONG_PSEUDO_NULL)
			{
				wsprintf(strRet.GetBuffer(MAX_NUM_STRING_SIZE), _T("%ld"), *(long*)pv);
				strRet.ReleaseBuffer();
			}
			break;

		case   AFX_RFX_SINGLE:
			if (*(float*) pv != AFX_RFX_SINGLE_PSEUDO_NULL)
			{
				// QA: 31989 - #if Secure Code Cleanup.
				_stprintf(strRet.GetBuffer(MAX_NUM_STRING_SIZE), _T("%g"), *(float*)pv);
				strRet.ReleaseBuffer();
			}
			break;

		case   AFX_RFX_DOUBLE:
			if (*(double*) pv != AFX_RFX_DOUBLE_PSEUDO_NULL)
			{
				// QA: 31989 - #if Secure Code Cleanup.
				_stprintf(strRet.GetBuffer(MAX_NUM_STRING_SIZE), _T("%.13g"), *(double*)pv);
				strRet.ReleaseBuffer();
			}
			break;

#if _MFC_VER >= 0x0423
		case AFX_RFX_OLEDATE:
			{
				COleDateTime* pTime = (COleDateTime*)pv;
				strRet = pTime->Format();	// Will be modified based on contect like GXFormatTimeStamp
			}
			break;
#endif

#if _MFC_VER >= 0x0420
		case AFX_RFX_DATE:
			{
				CTime* pTime = (CTime*)pv;

				if (*pTime != AFX_RFX_DATE_PSEUDO_NULL)
					GXFormatTimeStamp(strRet, pTime);
			}
			break;

		case AFX_RFX_TIMESTAMP:
			{
				TIMESTAMP_STRUCT* pTime = (TIMESTAMP_STRUCT*)pv;

				if (pTime && !
					(pTime->year    == AFX_RFX_TIMESTAMP_PSEUDO_NULL
					&& pTime->month   == AFX_RFX_TIMESTAMP_PSEUDO_NULL
					&& pTime->day     == AFX_RFX_TIMESTAMP_PSEUDO_NULL
					&& pTime->hour    == AFX_RFX_TIMESTAMP_PSEUDO_NULL
					&& pTime->minute  == AFX_RFX_TIMESTAMP_PSEUDO_NULL
					&& pTime->second  == AFX_RFX_TIMESTAMP_PSEUDO_NULL
					&& pTime->fraction== AFX_RFX_TIMESTAMP_PSEUDO_NULL)
					)
					GXFormatTimeStamp(strRet, pTime);
			}
			break;
#else
		case AFX_RFX_DATE:
			// NOTE: you should call
			//      _tsetlocale(LC_TIME, _T(""))
			// at the initialization of your application if you want to support
			// local representations of date/time values.

			// I have to determine if the type of the field
			// is a CTime or a TIMESTAMP_STRUCT. CRecordset::GetFieldInfo
			// did assign the size of the data type to dwSize. So,
			// I can use this member to determine the data type of pv

			// handle CTime value

			if (dwSize == sizeof(CTime))
			{
				CTime* pTime = (CTime*)pv;

				if (*pTime != AFX_RFX_DATE_PSEUDO_NULL)
					GXFormatTimeStamp(strRet, pTime);
			}
			// handle TIMESTAMP_STRUCT value
			else if (dwSize == sizeof(TIMESTAMP_STRUCT))
			{
				TIMESTAMP_STRUCT* pTime = (TIMESTAMP_STRUCT*)pv;

				if (pTime && !
					(pTime->year    == AFX_RFX_TIMESTAMP_PSEUDO_NULL
					&& pTime->month   == AFX_RFX_TIMESTAMP_PSEUDO_NULL
					&& pTime->day     == AFX_RFX_TIMESTAMP_PSEUDO_NULL
					&& pTime->hour    == AFX_RFX_TIMESTAMP_PSEUDO_NULL
					&& pTime->minute  == AFX_RFX_TIMESTAMP_PSEUDO_NULL
					&& pTime->second  == AFX_RFX_TIMESTAMP_PSEUDO_NULL
					&& pTime->fraction== AFX_RFX_TIMESTAMP_PSEUDO_NULL)
					)
					GXFormatTimeStamp(strRet, pTime);
			}
			break;
#endif

		default:
			TRACE0("Invalid ODBC data type\n");
			ASSERT(1);
			return FALSE;
		}
	}

	return TRUE;
}

#pragma warning (push)
#pragma warning (disable: 4701)

// helper routine which converts the string into a recordset value
BOOL GXWriteODBCValueString(LPCTSTR pszValue, CRecordset* pRecordset, void* pv, int nDataType, DWORD dwSize, CString* psWarning, BOOL bConvertMemo)
{
#if _MFC_VER >= 0x0420
	dwSize; // is obsolete in VC 4.2
#endif

	BOOL bTimeStamp = FALSE;

	switch(nDataType)
	{
	case AFX_RFX_LONGBINARY:
		// convert string to CLongBinary
		if (bConvertMemo)
		{
			CLongBinary* plbMemo = (CLongBinary*) pv;

			UINT nLen = (UINT)_tcslen(pszValue);
			HGLOBAL hGlob;

#ifndef _UNICODE
			if (nLen > 0)
			{
				hGlob = GlobalAlloc(GPTR | GMEM_SHARE, (DWORD)nLen*sizeof(TCHAR));
				if (hGlob == NULL)
					AfxThrowMemoryException();

				LPSTR lpStr = (LPSTR)GlobalLock(hGlob);
				if (lpStr == NULL)
				{
					GlobalFree(hGlob);
					AfxThrowMemoryException();
				}

				// Cut off the null
				memcpy(lpStr, pszValue, nLen);

				GlobalUnlock(hGlob);    // Don't leave it locked.
			}
			else // Empty
			{
				nLen = 0;
				hGlob = NULL;
			}
#else
			if (nLen > 0)
			{
				// Convert UNICODE string to an ANSI string
				int nSize = WideCharToMultiByte(CP_ACP, 0, pszValue, -1, NULL, 0, NULL, NULL);
				hGlob = GlobalAlloc(GPTR | GMEM_SHARE, nSize);

				if (hGlob == NULL)
					AfxThrowMemoryException();

				LPSTR lpStr = (LPSTR)GlobalLock(hGlob);
				if (lpStr == NULL)
				{
					GlobalFree(hGlob);
					AfxThrowMemoryException();
				}

				WideCharToMultiByte(CP_ACP, 0, pszValue, -1, lpStr, nSize, NULL, NULL);

				GlobalUnlock(hGlob);    // Don't leave it locked.
			}
			else // Empty
			{
				nLen = 0;
				hGlob = NULL;
			}
#endif

			// Free memory we are replacing
			GlobalUnlock(plbMemo->m_hData);
			GlobalFree(plbMemo->m_hData);

			// Put in new data
			plbMemo->m_dwDataLength = (DWORD) nLen;
			plbMemo->m_hData = hGlob;

			if (nLen == 0)
			{
				if (pRecordset->IsFieldNullable(plbMemo))
					pRecordset->SetFieldNull(plbMemo, TRUE);
			}
			else
			{
				// It is required that we explicitly set it Dirty
				// and NOT Null
				pRecordset->SetFieldNull(plbMemo, FALSE);
				pRecordset->SetFieldDirty(plbMemo, TRUE);
			}
			break;
		}

	case AFX_RFX_BINARY:
		// not supported data types

		// This case will only happen if you have set the
		// dirty field for this columns but you have not
		// overriden this method to store the data back to
		// the recordset.
		//
		// You should override this method if you want to allow
		// changing AFX_RFX_BINARY or AFX_RFX_LONGBINARY fields.

		ASSERT(1);
		if (psWarning)
			*psWarning = _T("Trying to store unsupported field type to data source");
		return FALSE;

    // [VC7] Map new text types to AFX_RFX_TEXT.
#if (_MFC_VER >= 0x0700)
	case AFX_RFX_ATEXT:
	case AFX_RFX_WTEXT:
#endif
	case AFX_RFX_TEXT:
		*(CString*) pv = pszValue;
		break;

	case AFX_RFX_BOOL:
		if (pszValue == NULL || _tcslen(pszValue) == 0)
			*(BOOL*) pv = AFX_RFX_BOOL_PSEUDO_NULL;
		else
			*(BOOL*) pv = _tcsicmp(pszValue, _T("TRUE")) == 0;
		break;

	case  AFX_RFX_BYTE:
		if (pszValue == NULL || _tcslen(pszValue) == 0)
			*(BYTE*) pv = AFX_RFX_BYTE_PSEUDO_NULL;
		else
			*(BYTE*) pv = (BYTE) _ttoi(pszValue);
		break;

	case   AFX_RFX_INT:
		if (pszValue == NULL || _tcslen(pszValue) == 0)
			*(int*) pv = AFX_RFX_INT_PSEUDO_NULL;
		else
			*(int*) pv = (int) _ttoi(pszValue);
		break;

	case   AFX_RFX_LONG:
		if (pszValue == NULL || _tcslen(pszValue) == 0)
			*(long*) pv = AFX_RFX_LONG_PSEUDO_NULL;
		else
			*(long*) pv = (long) _ttol(pszValue);
		break;

	case   AFX_RFX_SINGLE:
		if (pszValue == NULL || _tcslen(pszValue) == 0)
			*(float*) pv = AFX_RFX_SINGLE_PSEUDO_NULL;
		else
			*(float*) pv = (float) _gxttof(pszValue);
		break;

	case   AFX_RFX_DOUBLE:
		if (pszValue == NULL || _tcslen(pszValue) == 0)
			*(double*) pv = AFX_RFX_DOUBLE_PSEUDO_NULL;
		else
			*(double*) pv = (double) _gxttof(pszValue);
		break;

#if _MFC_VER >= 0x0423
	case AFX_RFX_OLEDATE:
		if (!(*(COleDateTime*) pv).ParseDateTime(pszValue))
		{
			if (pszValue != NULL && _tcslen(pszValue) > 0)
			{
				(*(COleDateTime*) pv) = _gxttof(pszValue);
				break;
			}
			if (psWarning)
			{
				AfxFormatString1(*psWarning, GX_IDM_DATEINVALID, pszValue);
			}
			return FALSE;
		}
		break;
#endif

#if _MFC_VER >= 0x0420
	case AFX_RFX_TIMESTAMP:
		bTimeStamp = TRUE;
	case AFX_RFX_DATE:
#else
	case AFX_RFX_DATE:
		bTimeStamp = (dwSize == sizeof(TIMESTAMP_STRUCT));
#endif
		{
			BOOL bValid = TRUE;

			// I have to determine if the type of the field
			// is a CTime or a TIMESTAMP_STRUCT. CRecordset::GetFieldInfo
			// did assign the size of the data type to dwSize. So,
			// I can use this member to determine which data type
			// I shall use.
			//

			// handle CTime value
			if (!bTimeStamp)
			{
				if (pszValue == NULL || _tcslen(pszValue) == 0)
					*(CTime*) pv = AFX_RFX_DATE_PSEUDO_NULL;
				else
				{
					struct tm tm;
#if _MFC_VER >= 0x0400
					// borrowed some code from the DAO Date/Time classes
					COleDateTime date;

					if (!date.ParseDateTime(pszValue) && pszValue != NULL && _tcslen(pszValue) > 0)
						date = _gxttof(pszValue);

					if (date.GetStatus() == COleDateTime::valid)
					{
						tm.tm_year = date.GetYear()-1900; // tm_year is 1900 based
						tm.tm_mon = date.GetMonth()-1;    // month is zero-based
						tm.tm_mday = date.GetDay();
						tm.tm_hour = date.GetHour();
						tm.tm_min = date.GetMinute();
						tm.tm_sec = date.GetSecond();
					}
					else
						bValid = FALSE;
#else
					bValid = GXParseDateTime(&tm, pszValue);
#endif

					if (!bValid)
					{
						if (psWarning)
							AfxFormatString1(*psWarning, GX_IDM_DATEINVALID, pszValue);
						return FALSE;
					}

					// check if date will be recognized by CTime constructor
					struct tm atm = tm;
					time_t ti = mktime(&atm);
					if (ti == -1)       // indicates that time is not recognized
					{
						if (psWarning)
							AfxFormatString1(*psWarning, GX_IDM_DATEOUTOFRANGE, pszValue);
						// NOTE: This is a limitation of the MFC CTime class. If you depend
						// on dates earlier than 01.01.1970, you should consider using
						// TIMESTAMP_STRUCT. See also the GX_RFX_Date method at the beginning
						// of this file for further information.
						return FALSE;
					}

					// transfer value to CTime

					*(CTime*) pv = CTime(tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday,
						tm.tm_hour, tm.tm_min, tm.tm_sec );
				}
			}
			// handle TIMESTAMP_STRUCT value
			else
			{
				TIMESTAMP_STRUCT time;
				memset(&time, 0, sizeof(TIMESTAMP_STRUCT));

				// need my own parsing routine

				if (pszValue == NULL || _tcslen(pszValue) == 0)
				{
					time.year    = AFX_RFX_TIMESTAMP_PSEUDO_NULL;
					time.month   = AFX_RFX_TIMESTAMP_PSEUDO_NULL;
					time.day     = AFX_RFX_TIMESTAMP_PSEUDO_NULL;
					time.hour    = AFX_RFX_TIMESTAMP_PSEUDO_NULL;
					time.minute  = AFX_RFX_TIMESTAMP_PSEUDO_NULL;
					time.second  = AFX_RFX_TIMESTAMP_PSEUDO_NULL;
					time.fraction= AFX_RFX_TIMESTAMP_PSEUDO_NULL;
				}
				else
				{
#if _MFC_VER >= 0x0400
					// can use COleDateTime for parsing
					COleDateTime date;

					if (!date.ParseDateTime(pszValue) && pszValue != NULL && _tcslen(pszValue) > 0)
						date = _gxttof(pszValue);

					if (date.GetStatus() == COleDateTime::valid)
					{
						time.year = (SWORD) date.GetYear();
						time.month = (UWORD) date.GetMonth();
						time.day = (UWORD) date.GetDay();
						time.hour = (UWORD) date.GetHour();
						time.minute = (UWORD) date.GetMinute();
						time.second = (UWORD) date.GetSecond();
					}
					else
						bValid = FALSE;
#else
					bValid = GXParseDateTime(&time, pszValue);
#endif

					if (!bValid)
					{
						if (psWarning)
							AfxFormatString1(*psWarning, GX_IDM_DATEINVALID, pszValue);
						return FALSE;
					}
				}

				*(TIMESTAMP_STRUCT*) pv = time;
				break;
			}

		};
		break;

	default:
		TRACE0("Invalid ODBC data type\n");
		ASSERT(1);
		return FALSE;
	}

	// Make empty strings NULL
	if (_tcslen(pszValue) == 0)
		pRecordset->SetFieldNull(pv);
	else
		pRecordset->SetFieldNull(pv, FALSE);

	pRecordset->SetFieldDirty(pv);

	return TRUE;
}

#pragma warning (pop) //4701

#endif // _AFX_NO_DB_SUPPORT
