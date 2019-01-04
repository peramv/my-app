///////////////////////////////////////////////////////////////////////////////
// gxdbdyna.cpp : implementation of CGXDynamicRecordset class
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

//#ifndef _WIN64 //RW64
#ifndef _GXODBC_H_
#include "grid\gxodbc.h"
#endif //_GXODBC_H_
//#endif //_WIN64

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif


//#ifndef _WIN64 //RW64
IMPLEMENT_DYNAMIC(CGXDynamicRecordset, CRecordset)
//#endif //_WIN64

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXDBDYNA")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

#if _MFC_VER >= 0x0420

CGXFieldInfo::CGXFieldInfo()
{
	pv = NULL;
	nField = 0;
	nDataType = 0;
}

#endif

/////////////////////////////////////////////////////////////////////////////
// CGXFieldDesc

CGXFieldDesc::CGXFieldDesc()
{
	pv = NULL;
}

CGXFieldDesc::~CGXFieldDesc()
{
	strName.Empty();

	// deallocate value
	switch (nDataType)
	{
	case AFX_RFX_BOOL:
		{
		BOOL* p = (BOOL*) pv;
		delete p;
		}
		break;

	case AFX_RFX_BYTE:
		{
		BYTE* p = (BYTE*) pv;
		delete p;
		}
		break;

	case AFX_RFX_INT:
		{
		int* p = (int*) pv;
		delete p;
		}
		break;

	case AFX_RFX_LONG:
		{
		LONG* p = (LONG*) pv;
		delete p;
		}
		break;

	case AFX_RFX_SINGLE:
		{
		float* p = (float*) pv;
		delete p;
		}
		break;

	case AFX_RFX_DOUBLE:
		{
		double* p = (double*) pv;
		delete p;
		}
		break;

#if _MFC_VER >= 0x0420
	case AFX_RFX_TIMESTAMP:
#endif
	case AFX_RFX_DATE:
		{
		TIMESTAMP_STRUCT* p = (TIMESTAMP_STRUCT*) pv;
		delete p;
		}
		break;

	case AFX_RFX_BINARY:
		{
		CByteArray* p = (CByteArray*) pv;
		delete p;
		}
		break;

    // [VC7] Map New Types To AFX_RFX_TEXT.
#if (_MFC_VER >= 0x0700)
	case AFX_RFX_ATEXT:
	case AFX_RFX_WTEXT:
#endif
	case AFX_RFX_TEXT:
		{
		CString* p = (CString*) pv;
		delete p;
		}
		break;

	case AFX_RFX_LONGBINARY:
		{
		CLongBinary* p = (CLongBinary*) pv;
		delete p;
		}
		break;

#if _MFC_VER >= 0x0423

/*	case AFX_RFX_LPTSTR:
		{
		LPTSTR* p = (LPTSTR*) pv;
		delete p;
		}
		break;
*/
	case AFX_RFX_OLEDATE:
		{
		COleDateTime* p = (COleDateTime*) pv;
		delete p;
		}
		break;
#endif
	}
}

/////////////////////////////////////////////////////////////////////////////
// CGXDynamicRecordset

CGXDynamicRecordset::CGXDynamicRecordset(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CGXDynamicRecordset)
	m_nFields = 0;
	//}}AFX_FIELD_INIT

	m_aFieldDesc = NULL;
}

CGXDynamicRecordset::~CGXDynamicRecordset()
{
	delete[] m_aFieldDesc;
}

void CGXDynamicRecordset::Close()
{
	CRecordset::Close();

	delete[] m_aFieldDesc;
	m_aFieldDesc = NULL;

#if _MFC_VER >= 0x0420
	// We need to clean up this CRecordset internal map.
	// Otherwise, it will contain pointers to deleted values
	// when we reopen the recordset.
	m_mapFieldIndex.RemoveAll();
#endif

	m_nFields = 0;
}


CString CGXDynamicRecordset::GetDefaultConnect()
{
	if (m_sConnectString.IsEmpty())
		return CRecordset::GetDefaultConnect();

	return m_sConnectString;
}

CString CGXDynamicRecordset::GetDefaultSQL()
{
	return m_sSqlQuery;
}

void CGXDynamicRecordset::PreBindFields()
{
	ASSERT(m_nFields == 0);
	// ASSERTION-> Do not mix ClassWizard generated CRecordSet with this
	// CGXDynamicRecordset. The RFX DataExchange mechanism is not allowed
	// with this class. ->END

	RETCODE nRetCode;

	SWORD nResultCols = 0;
	SQLNumResultCols(m_hstmt, &nResultCols);
	m_nQueryFields = (UINT) nResultCols;

	if (nResultCols > 0)
	{
		m_aFieldDesc = new CGXFieldDesc[nResultCols];

		// get column names and specifications
		// and bind columns
		for (SWORD i = 0; i < nResultCols; i++)
		{
			CGXFieldDesc& fld = m_aFieldDesc[i];

			SWORD cbColName;
			TCHAR szColName[255];

            // [VC7] Change SQLDescribeCol to get correct type for colname
            // in ansi and unicode builds.           
			AFX_SQL_SYNC(SQLDescribeCol(m_hstmt, (SWORD) (i + 1),
			  (SQLTCHAR *)szColName, (SWORD) sizeof(szColName), &cbColName,
			  &fld.fSqlType, &fld.cbColDef, &fld.ibScale, &fld.fNullable));            

			if (!Check(nRetCode))
				ThrowDBException(nRetCode);

			// NOTE: See KB article Q140215 and Q125226
			// FIX: Brackets Cause Recordset Update to Fail in SQL Server
			// PRB: ODBC Reserved Word in a RFX Function Causes Syntax Error
			// There could be problems with VC 2.x which have been fixed in 4.x
			// [VC7] change char * to TCHAR *.
			fld.strName = _T('[');
			fld.strName += (TCHAR *)szColName;
			fld.strName += _T(']');

			switch (fld.fSqlType)
			{
			case SQL_BIT:
				fld.nDataType = AFX_RFX_BOOL;
				fld.pv = (void*) new BOOL;
				break;

			case SQL_TINYINT:
				fld.nDataType = AFX_RFX_BYTE;
				fld.pv = (void*) new BYTE;
				break;

			case SQL_SMALLINT:
				fld.nDataType = AFX_RFX_INT;
				fld.pv = (void*) new int;
				break;

			case SQL_INTEGER:
				fld.nDataType = AFX_RFX_LONG;
				fld.pv = (void*) new LONG;
				break;

			case SQL_REAL:
				fld.nDataType = AFX_RFX_SINGLE;
				fld.pv = (void*) new float;
				break;

			case SQL_FLOAT:
			case SQL_DOUBLE:
				fld.nDataType = AFX_RFX_DOUBLE;
				fld.pv = (void*) new double;
				break;

			case SQL_DATE:
			case SQL_TIME:
			case SQL_TIMESTAMP:
#if _MFC_VER >= 0x0420
				fld.nDataType = AFX_RFX_TIMESTAMP;
#else
				fld.nDataType = AFX_RFX_DATE;
#endif
				fld.pv = (void*) new TIMESTAMP_STRUCT;
				break;

			case SQL_BINARY:
			case SQL_VARBINARY:
				fld.nDataType = AFX_RFX_BINARY;
				fld.pv = (void*) new CByteArray;
				break;

			case SQL_DECIMAL:   // ODBC default xfer type
			case SQL_NUMERIC:   // ODBC default xfer type
				fld.cbColDef += 2;	// Room for decimal point and sign
			case SQL_CHAR:
			case SQL_VARCHAR:
			case SQL_LONGVARCHAR:
			case SQL_BIGINT:
			case SQL_WCHAR:
			case SQL_WVARCHAR:
			case SQL_WLONGVARCHAR:
			case SQL_GUID:
				fld.nDataType = AFX_RFX_TEXT;
				fld.pv = (void*) new CString;
				break;

			case SQL_LONGVARBINARY:
				fld.nDataType = AFX_RFX_LONGBINARY;
				fld.pv = (void*) new CLongBinary;
				break;

			default:
				ASSERT(FALSE);

			}
		}
		m_nFields = nResultCols;
	}

#if _MFC_VER >= 0x0420
	// Allocate internal arrays
	AllocStatusArrays();
#endif
}

void CGXDynamicRecordset::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CGXDynamicRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	//}}AFX_FIELD_MAP

	for (UINT nField = 0; nField < m_nFields; nField++)
	{
		CGXFieldDesc& fld = GetField(nField);

		switch (fld.nDataType)
		{
		case AFX_RFX_BOOL:
			RFX_Bool(pFX, fld.strName, *(BOOL*) fld.pv);
			break;

		case AFX_RFX_BYTE:
			RFX_Byte(pFX, fld.strName, *(BYTE*) fld.pv);
			break;

		case AFX_RFX_INT:
			RFX_Int(pFX, fld.strName, *(int*) fld.pv);
			break;

		case AFX_RFX_LONG:
			RFX_Long(pFX, fld.strName, *(long*) fld.pv);
			break;

		case AFX_RFX_SINGLE:
			RFX_Single(pFX, fld.strName, *(float*) fld.pv);
			break;

		case AFX_RFX_DOUBLE:
			RFX_Double(pFX, fld.strName, *(double*) fld.pv);
			break;

#if _MFC_VER >= 0x0420
		case AFX_RFX_TIMESTAMP:
#endif
		case AFX_RFX_DATE:
			GX_RFX_Date(pFX, fld.strName, *((TIMESTAMP_STRUCT*) fld.pv));
			break;

		case AFX_RFX_BINARY:
			RFX_Binary(pFX, fld.strName, *((CByteArray*) fld.pv));
			break;

        // [VC7] Map new text types to AFX_RFX_TEXT.
#if (_MFC_VER >= 0x0700)
		case AFX_RFX_ATEXT:
		case AFX_RFX_WTEXT:
#endif
		case AFX_RFX_TEXT:
			if( fld.fSqlType == SQL_GUID ) 
			{
				fld.fSqlType = pFX->m_prs->m_rgODBCFieldInfos[nField].m_nSQLType = SQL_VARCHAR;
			}

			RFX_Text(pFX, fld.strName, *((CString*) fld.pv), (int) min(32767, fld.cbColDef));
#if defined(_UNICODE) && _MFC_VER == 0x0420
			if (pFX->m_nOperation == CFieldExchange::NameValue
				|| pFX->m_nOperation == CFieldExchange::Value)
			{
				// this works around the problem that MFC 4.2
				// adds a parameter. If you compare the RFX_Text code
				// with MFC 4.21 you will see that MFC has
				// fixed this for VC 5.
				if (!(pFX->m_prs->m_dwOptions & CRecordset::optimizeBulkAdd))
				{
					// Add the member address to the param map
					pFX->m_prs->m_mapParamIndex.RemoveAll();
				}
			}
#endif // _UNICODE
			break;

		case AFX_RFX_LONGBINARY:
			RFX_LongBinary(pFX, fld.strName, *((CLongBinary*) fld.pv));
			break;

#if _MFC_VER >= 0x0423
/*
		case AFX_RFX_LPTSTR:
			RFX_Text(pFX, fld.strName, *((LPTSTR*) fld.pv), (int) min(32767, fld.cbColDef));
			break;
*/
		case AFX_RFX_OLEDATE:
			RFX_Date(pFX, fld.strName, *(COleDateTime*) fld.pv);
			break;
#endif
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CGXDynamicRecordset values

// The following two methods let you read and edit
// values in a recordset.

BOOL CGXDynamicRecordset::GetFieldData(int nField, CString& strRet, BOOL bConvertMemo)
{
	CGXFieldDesc& fld = m_aFieldDesc[nField];

	return GXGetODBCValueString(strRet, this, fld.pv, fld.nDataType, sizeof(TIMESTAMP_STRUCT), bConvertMemo);
}

BOOL CGXDynamicRecordset::SetFieldData(int nField, LPCTSTR pszValue, CString* psWarning, BOOL bConvertMemo)
{
	CGXFieldDesc& fld = m_aFieldDesc[nField];

	return GXWriteODBCValueString(pszValue, this, fld.pv, fld.nDataType, sizeof(TIMESTAMP_STRUCT), psWarning, bConvertMemo);
}

/////////////////////////////////////////////////////////////////////////////
// CGXDynamicRecordset diagnostics

#ifdef _DEBUG
void CGXDynamicRecordset::AssertValid() const
{
	CRecordset::AssertValid();
}

void CGXDynamicRecordset::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGXDynamicRecordset attributes

void CGXDynamicRecordset::SetSqlQuery(LPCTSTR szSqlQuery)
{
	m_sSqlQuery = szSqlQuery;
}

const CString& CGXDynamicRecordset::GetSqlQuery() const
{
	return m_sSqlQuery;
}

CGXFieldDesc& CGXDynamicRecordset::GetField(UINT nField) const
{
	ASSERT(nField < m_nQueryFields);

	return m_aFieldDesc[nField];
}

void CGXDynamicRecordset::SetConnectString(LPCTSTR szConnectString)
{
	m_sConnectString = szConnectString;
}

const CString& CGXDynamicRecordset::GetConnectString() const
{
	return m_sConnectString;
}

void CGXDynamicRecordset::FillChoiceList(CString& strChoiceList, BOOL bDisplayHeader)
{
	strChoiceList.Empty();

	// Column names
	if (bDisplayHeader)
	{
		for (UINT nField = 0; nField < m_nFields; nField++)
		{
			CGXFieldDesc& fld = GetField(nField);
			CString strName = fld.strName;
			if (strName[0] == _T('['))
				strName = strName.Mid(1, strName.GetLength()-2);

			strChoiceList += strName;
			if (nField < m_nFields-1)
				strChoiceList += _T("\t");
		}
		strChoiceList += _T("\n");
	}

	// Values
	MoveFirst();
	while (!IsEOF())
	{
		for (UINT nField = 0; nField < m_nFields; nField++)
		{
			CString strValue;
			GetFieldData(nField, strValue);
			strChoiceList += strValue;
			if (nField < m_nFields-1)
				strChoiceList += _T("\t");
		}
		strChoiceList += _T("\n");
		MoveNext();
	}
}

#endif // _AFX_NO_DB_SUPPORT

