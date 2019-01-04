///////////////////////////////////////////////////////////////////////////////
// gxdaval.cpp : helper routines for reading/writing
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

// compile this file only if DAO is supported
#if _MFC_VER >= 0x0400 && !defined(_AFX_NO_DAO_SUPPORT)

#ifdef _GXDLL
// used for MFC 2.5 Extension DLL
	#undef AFXAPI_DATA
	#define AFXAPI_DATA __based(__segname("_DATA"))
#endif

// Headers for imported classes

#ifndef _GXRESRC_H_
#include "grid\gxresrc.h"
#endif

#ifndef _GXDAO_H_
#include "grid\gxdao.h"
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif


#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXDAVAL")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// Warnings
#pragma warning (push)
#pragma warning (disable: 4995)

const TCHAR szUnknownType[]      = _T("Unknown Type");

// GXGetDaoFieldString()
//
// This method returns the string contents of a field from a CDaoRecordset
//

GRID_API void GXGetDaoFieldString(CString& strRet, CDaoRecordset* pRecordset, int nField, BOOL bDisplayMemo)
{
	short nType;

	// Get DAOField object and determine data type
	DAOField* pDAOField;
	DAO_CHECK(pRecordset->m_pDAOFields->get_Item(
		COleVariant((long)nField), &pDAOField));

	DAO_CHECK(pDAOField->get_Type(&nType));

	// Clean up
	pDAOField->Release();

	switch(nType)
	{
	case dbMemo:
		if (bDisplayMemo)
			break;

	case dbLongBinary:
	case dbGUID:
		// not supported data types
		//
		// NOTE: It is possible to convert the value for these special data types
		// in the CGXControl::Draw method.
		//
		// An example would be a CGXDaoBitmapControl class, where you you could convert a
		// dbLongBinary field to a bitmap.
		//
		// Another example would be to display memo fields in a message box when
		// the user double-clicked on the memo field. If the memo-field is drawn in the
		// cell, you could simply display "Memo" in the cell without need to convert the
		// COleVariant, but when the user double-clicks on the cell, you call
		// var = pRecordset->GetVieldFalue(nField) and convert the COleVariant into
		// a string.
		//
		// Skipping this normally very big data types increases performance. Although
		// ìt would be possible to translate memo fields to strings, I think it should
		// be the programmers choice if he wants to display them in cells.
		//

		return;
	}

	COleVariant var;
	var = pRecordset->GetFieldValue(nField);

	switch(var.vt)
	{
	case VT_EMPTY:
	case VT_NULL:
		strRet = _T("");
		break;
	case VT_I2:
		strRet.Format(_T("%hd"),V_I2(&var));
		break;
	case VT_I4:
		strRet.Format(_T("%d"),V_I4(&var));
		break;
	case VT_R4:
		strRet.Format(_T("%g"),(double)V_R4(&var));
		break;
	case VT_R8:
		strRet.Format(_T("%.13g"),V_R8(&var));
		break;
	case VT_CY:
		strRet = COleCurrency(var).Format();
		break;
	case VT_DATE:
		strRet = COleDateTime(var).Format();
		break;
	case VT_BSTR:
		strRet = V_BSTRT(&var);
		break;
	case VT_BOOL:
		strRet = V_BOOL(&var) ? _T("TRUE") : _T("FALSE");
		break;
	case VT_UI1:
		strRet.Format(_T("%d"),V_UI1(&var));
		break;
	default:
		strRet = szUnknownType;
		break;
	}
}

CString GXGetFieldName(DAOField* pDAOField)
{
	ASSERT(pDAOField != NULL);

	COleVariant var;

	DAO_CHECK(pDAOField->get_Name(&V_BSTR(&var)));
	var.vt = VT_BSTR;
	CString strName = V_BSTRT(&var);
	var.Clear();

	return strName;
}

CString GXGetFieldName(CDaoRecordset* pRecordset, int nIndex)
{
	// Get DAOField object and fill in field info struct
	DAOField* pDAOField;
	DAO_CHECK(pRecordset->m_pDAOFields->get_Item(
		COleVariant((long)nIndex), &pDAOField));

	CString s = GXGetFieldName(pDAOField);

	// Clean up
	pDAOField->Release();

	return s;
}

void GXFillChoiceList(CDaoRecordset* pSet, CString& strChoiceList, BOOL bDisplayHeader)
{
	ASSERT(pSet);

	//CDaoFieldInfo fieldInfo;
	//pSet->GetFieldInfo(1, fieldInfo);

	strChoiceList.Empty();

	int nFields = pSet->GetFieldCount( );

	// Column names
	if (bDisplayHeader)
	{
		for (int nField = 0; nField < nFields; nField++)
		{
			strChoiceList += GXGetFieldName(pSet, nField);
			if (nField < nFields-1)
				strChoiceList += _T("\t");
		}
		strChoiceList += _T("\n");
	}

	// Values
	pSet->MoveFirst();
	while (!pSet->IsEOF())
	{
		for (int nField = 0; nField < nFields; nField++)
		{
			CString strValue;
			GXGetDaoFieldString(strValue, pSet, nField, TRUE);
			strChoiceList += strValue;
			if (nField < nFields-1)
				strChoiceList += _T("\t");
		}
		strChoiceList += _T("\n");
		pSet->MoveNext();
	}
}

#pragma warning (disable: 4995)

#endif // #if _MFC_VER >= 0x0400 && !defined(_AFX_NO_DAO_SUPPORT)
