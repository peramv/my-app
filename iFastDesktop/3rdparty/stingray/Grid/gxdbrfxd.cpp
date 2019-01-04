///////////////////////////////////////////////////////////////////////////////
// gxdbrfxd.cpp : GX_RFX_Date implementation
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
#pragma code_seg("GX_SEG_GXDBRFXD")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// GX_RFX_Date

// This method has been copied from RFXDTE.EXE,
// a self-extracting file, from the Microsoft Software Library (MSL).

// See knowledge-base article Q114961
//
// Here is a brief summary:
//
// The RFX_Date() record field exchange function transfers data from a
// date/time field to a CTime object. AppWizard/ClassWizard will use this
// RFX_Date() function when mapping date/time fields to variables.
//
// The CTime object doesn't allow dates before the year 1970 and after the
// year 2037 (the CRT stores the time as a signed long, so the limit is
// actually Jan 18, 2038 19:14:07). Therefore, it may be better to use a
// TIMESTAMP_STRUCT (defined in the SQLEXT.H) to retrieve the date/time
// information.
//
// ...
//
// NOTE: Visual C++, 32-bit Edition, version 2.1 and above already have an
// RFX_DATE that takes a TIMESTAMP struct; adding this source code to a Visual
// C++ 2.1 project yields a multiple definition error.
//
// I have renamed the method to GX_RFX_Date so that no multiple definition error
// will happen if another library has already defined this method.
//

#if _MFC_VER < 0x0400

void GX_RFX_Date(CFieldExchange* pFX, const char *szName,
	TIMESTAMP_STRUCT& value)
{
	ASSERT(AfxIsValidAddress(pFX, sizeof(CFieldExchange)));
	ASSERT(AfxIsValidString(szName));

	RETCODE nRetCode;
	UINT nField;
	if (!pFX->IsFieldType(&nField))
		return;

	LONG* plLength = pFX->m_prs->GetFieldLength(pFX);
	switch (pFX->m_nOperation)
	{
	default:
LDefault:
		pFX->Default(szName, &value, plLength, SQL_C_TIMESTAMP,
			sizeof(value), TIMESTAMP_PRECISION);
		return;
	case CFieldExchange::BindParam:
		{
			TIMESTAMP_STRUCT* pts;
			if (pFX->m_prs->IsFieldFlagNull(nField, CFieldExchange::param))
			{
				pts = NULL;
				*plLength = SQL_NULL_DATA;
			}
			else
			{
				*plLength = sizeof(TIMESTAMP_STRUCT);
			}

			AFX_SQL_SYNC(::SQLSetParam(pFX->m_hstmt,
				(unsigned short int)nField,
				// SQLType same as CType for Params
				SQL_C_TIMESTAMP, SQL_C_TIMESTAMP, TIMESTAMP_PRECISION,
				0, &value, plLength));
			if (nRetCode != SQL_SUCCESS)
				pFX->m_prs->ThrowDBException(nRetCode, pFX->m_hstmt);
		}
		return;

	case CFieldExchange::BindFieldToColumn:
		{
			int nSqlType = pFX->GetColumnType(nField);
			if (nSqlType != SQL_DATE && nSqlType != SQL_TIME &&
				nSqlType != SQL_TIMESTAMP)
			{
				pFX->m_prs->ThrowDBException(AFX_SQL_ERROR_FIELD_SCHEMA_MISMATCH);
			}

			AFX_SQL_SYNC(::SQLBindCol(pFX->m_prs->m_hstmt, (unsigned short int)nField,
				SQL_C_TIMESTAMP, &value,
				(UINT)sizeof(TIMESTAMP_STRUCT), plLength));
			if (!pFX->m_prs->Check(nRetCode))
				pFX->m_prs->ThrowDBException(nRetCode);
		}
		return;

	case CFieldExchange::Fixup:
		if (*plLength == SQL_NULL_DATA)
		{
			pFX->m_prs->SetFieldFlags(nField,
				AFX_SQL_FIELD_FLAG_NULL, pFX->m_nFieldType);
			value.year    = AFX_RFX_TIMESTAMP_PSEUDO_NULL;
			value.month   = AFX_RFX_TIMESTAMP_PSEUDO_NULL;
			value.day     = AFX_RFX_TIMESTAMP_PSEUDO_NULL;
			value.hour    = AFX_RFX_TIMESTAMP_PSEUDO_NULL;
			value.minute  = AFX_RFX_TIMESTAMP_PSEUDO_NULL;
			value.second  = AFX_RFX_TIMESTAMP_PSEUDO_NULL;
			value.fraction= AFX_RFX_TIMESTAMP_PSEUDO_NULL;
		}
		return;

	case CFieldExchange::NameValue:
		if (pFX->m_prs->IsFieldFlagDirty(nField, pFX->m_nFieldType))
		{
#if _MFC_VER < 0x0300
			*pFX->m_pstr += pFX->m_prs->m_pDatabase->QuoteName(szName);
#else
			*pFX->m_pstr += szName;
#endif
			*pFX->m_pstr += _T("=");
		}
		// Fall through

	case CFieldExchange::Value:
		if (pFX->m_prs->IsFieldFlagDirty(nField, pFX->m_nFieldType))
		{
			if (pFX->m_prs->IsFieldFlagNull(nField, pFX->m_nFieldType))
			{
				*plLength = SQL_NULL_DATA;
			}
			else
			{
				*plLength = sizeof(TIMESTAMP_STRUCT);
			}

			*pFX->m_pstr += _T("?");
			*pFX->m_pstr += pFX->m_lpszSeparator;
			pFX->m_nParamFields++;
			AFX_SQL_SYNC(::SQLSetParam(pFX->m_hstmt,
				(unsigned short int)pFX->m_nParamFields, SQL_C_TIMESTAMP,
				(short int)pFX->GetColumnType(nField),
				TIMESTAMP_PRECISION, 0, &value, plLength));
		}
		return;

	case CFieldExchange::SetFieldNull:
		if ((pFX->m_pvField == NULL &&
			pFX->m_nFieldType == CFieldExchange::outputColumn) ||
			pFX->m_pvField == &value)
		{
			if (pFX->m_bField)
			{
				// Mark fields null
				pFX->m_prs->SetFieldFlags(nField,
					AFX_SQL_FIELD_FLAG_NULL, pFX->m_nFieldType);
				value.year    = AFX_RFX_TIMESTAMP_PSEUDO_NULL;
				value.month   = AFX_RFX_TIMESTAMP_PSEUDO_NULL;
				value.day     = AFX_RFX_TIMESTAMP_PSEUDO_NULL;
				value.hour    = AFX_RFX_TIMESTAMP_PSEUDO_NULL;
				value.minute  = AFX_RFX_TIMESTAMP_PSEUDO_NULL;
				value.second  = AFX_RFX_TIMESTAMP_PSEUDO_NULL;
				value.fraction= AFX_RFX_TIMESTAMP_PSEUDO_NULL;
				*plLength = SQL_NULL_DATA;
			}
			else
			{
				pFX->m_prs->ClearFieldFlags(nField,
					AFX_SQL_FIELD_FLAG_NULL, pFX->m_nFieldType);
				*plLength = sizeof(TIMESTAMP_STRUCT);
			}
#ifdef _DEBUG
			pFX->m_bFieldFound = TRUE;
#endif // _DEBUG
		}
		return;

	case CFieldExchange::MarkForAddNew:
		// can force writing of psuedo-null value (as a non-null)
		// by setting field dirty and non-null.
		if (!pFX->m_prs->IsFieldFlagDirty(nField, pFX->m_nFieldType))
		{
		   // check against PSEUDO_NULL value to see if dirty
		   if (!(value.year    == AFX_RFX_TIMESTAMP_PSEUDO_NULL&&
				 value.month   == AFX_RFX_TIMESTAMP_PSEUDO_NULL&&
				 value.day     == AFX_RFX_TIMESTAMP_PSEUDO_NULL&&
				 value.hour    == AFX_RFX_TIMESTAMP_PSEUDO_NULL&&
				 value.minute  == AFX_RFX_TIMESTAMP_PSEUDO_NULL&&
				 value.second  == AFX_RFX_TIMESTAMP_PSEUDO_NULL&&
				 value.fraction== AFX_RFX_TIMESTAMP_PSEUDO_NULL))
				{
					pFX->m_prs->SetFieldFlags(nField,
						AFX_SQL_FIELD_FLAG_DIRTY, pFX->m_nFieldType);
					pFX->m_prs->ClearFieldFlags(nField,
						AFX_SQL_FIELD_FLAG_NULL, pFX->m_nFieldType);
				}
		}
		return;

	case CFieldExchange::MarkForUpdate:
		{
			// check to see if PSEUDO_NULL. If not, mark as non-null
		   if (value.year    == AFX_RFX_TIMESTAMP_PSEUDO_NULL&&
			   value.month   == AFX_RFX_TIMESTAMP_PSEUDO_NULL&&
			   value.day     == AFX_RFX_TIMESTAMP_PSEUDO_NULL&&
			   value.hour    == AFX_RFX_TIMESTAMP_PSEUDO_NULL&&
			   value.minute  == AFX_RFX_TIMESTAMP_PSEUDO_NULL&&
			   value.second  == AFX_RFX_TIMESTAMP_PSEUDO_NULL&&
			   value.fraction== AFX_RFX_TIMESTAMP_PSEUDO_NULL)
				pFX->m_prs->SetFieldFlags(nField,
					AFX_SQL_FIELD_FLAG_NULL, pFX->m_nFieldType);
			else
				pFX->m_prs->ClearFieldFlags(nField,
					AFX_SQL_FIELD_FLAG_NULL, pFX->m_nFieldType);
		}
		goto LDefault;

	case CFieldExchange::GetFieldInfoValue:
		if (pFX->m_pfi->pv == &value)
		{
			pFX->m_pfi->nField = nField-1;
			goto LFieldFound;
		}
		return;

	case CFieldExchange::GetFieldInfoOrdinal:
		if (nField-1 == pFX->m_pfi->nField)
		{
LFieldFound:
			pFX->m_pfi->nDataType = AFX_RFX_DATE;
			pFX->m_pfi->strName = szName;
			pFX->m_pfi->pv = &value;
			pFX->m_pfi->dwSize = sizeof(value);
			// Make sure field found only once
			ASSERT(pFX->m_bFieldFound == FALSE);
			pFX->m_bFieldFound = TRUE;
		}
		return;
	}
}

#endif

#endif // _AFX_NO_DB_SUPPORT
