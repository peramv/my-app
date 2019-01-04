///////////////////////////////////////////////////////////////////////////////
// gxadoval.cpp : helper routines for reading/writing
//                string values in a recordset
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
// Authors: Praveen Ramesh, Stefan Hoenig
//

#define _OG_EXPORT_IMPL

#include "stdafx.h"

// compile this file only if ADO is supported
#if _MFC_VER >= 0x0420 && !defined(_GX_NO_ADO_SUPPORT)

#ifdef _GXDLL
// used for MFC 2.5 Extension DLL
	#undef AFXAPI_DATA
	#define AFXAPI_DATA __based(__segname("_DATA"))
#endif

// Headers 

#ifndef _GXRESRC_H_
#include "grid\gxresrc.h"
#endif

#ifndef _GXADO_H_
#include "grid\gxado.h"
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXADOVAL")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif



const TCHAR szUnknownType[]      = _T("Unknown Type");

// GXGetAdoFieldString()
//
// This method returns the string contents of a field from a ADORecordset
// 

void GXGetAdoFieldString(CString& strRet, CComPtr<ADORecordset> piRecordset, int nField)
{
	COleVariant varValue;
	short nType;
	CComPtr<ADOFields> piFields;
	BOOL bSuccess;
	CString sFormat;
	HRESULT hr;
	FLOAT ft;


	// Get ADOField object and determine data type
	CComPtr<ADOField> pAdoField;
	GX_ADO_CHECK(piRecordset->get_Fields(&piFields), piRecordset, bSuccess)
	if(!bSuccess) 
		goto ErrorExit;
	GX_ADO_CHECK(piFields->get_Item(
		COleVariant((long)nField), &pAdoField), piRecordset, bSuccess)
	if(!bSuccess)
		goto ErrorExit;

//	Removing the error check with the macro, otherwise pFields->Release crashes
//	in apps built with VC6 SP1 and SP2 (SPs released so far) !!
//	GX_ADO_CHECK(pAdoField->get_Type((DataTypeEnum*)&nType), piRecordset, bSuccess)
//	if(!bSuccess) goto ErrorExit;

	if(FAILED(pAdoField->get_Type((DataTypeEnum*)&nType)))
	{
		AfxMessageBox(_T("Unable to get the Type of the field successfully"));
		goto ErrorExit;
	}


	GX_ADO_CHECK(pAdoField->get_Value(&varValue), piRecordset, bSuccess)
	if(!bSuccess) goto ErrorExit;

	switch(nType)
	{
	case adBinary:
	case adVarBinary:
	case adLongVarBinary: 
	case adGUID:
	case adChapter:
		// not supported data types
		//
		// NOTE: It is possible to convert the value for these special data types
		// in the CGXControl::Draw method.
		//
		// An example would be a CGXAdoBitmapControl class, where you you could convert a
		// dbLongBinary field to a bitmap.
		//
		// Another example would be to display memo fields in a message box when
		// the user double-clicked on the memo field. If the memo-field is drawn in the
		// cell, you could simply display "Memo" in the cell without need to convert the
		// COleVariant, but when the user double-clicks on the cell, you call
		// var = piRecordset->GetVieldFalue(nField) and convert the COleVariant into
		// a string.
		//
		// Skipping this normally very big data types increases performance. Although
		// ìt would be possible to translate memo fields to strings, I think it should
		// be the programmers choice if he wants to display them in cells.
		//

		return;
	}


	switch(varValue.vt)
	{
	case VT_EMPTY:
	case VT_NULL:
		strRet = _T("");
		break;
	case VT_UI1:
		strRet.Format(_T("%hu"),V_UI1(&varValue));
		break;
	case VT_UI2:
		strRet.Format(_T("%hu"),V_UI2(&varValue));
		break;
	case VT_UI4:
		strRet.Format(_T("%u"),V_UINT(&varValue));
		break;
	case VT_UI8:
		strRet.Format(_T("%lu"),V_UI4(&varValue));
		break;
	case VT_I1:
		strRet.Format(_T("%hd"),V_I1(&varValue));
		break;
	case VT_I2:
		strRet.Format(_T("%hd"),V_I2(&varValue));
		break;
	case VT_I4:
		strRet.Format(_T("%d"),V_I4(&varValue));
		break;
	case VT_I8:
		strRet.Format(_T("%ld"),V_I4(&varValue));
		break;
	case VT_R4:
		strRet.Format(_T("%g"),(double)V_R4(&varValue));
		break;
	case VT_R8:
		strRet.Format(_T("%.13g"),V_R8(&varValue));
		break;
	case VT_DECIMAL:
		// Convert to float...
		// Unable to convert to string here, instead converting to float
		//hr = VarBstrFromDec(&V_DECIMAL(&varValue), LANG_SYSTEM_DEFAULT, 0, &V_BSTR(&var));
		//var.vt = VT_BSTR;
		//strRet = V_BSTRT(&var);

		{
		// If there is any loss of data override ConvertValueToString and do the conversion yourself
		hr = VarR4FromDec(&V_DECIMAL(&varValue), &ft);
		if(FAILED(hr))
			return;
		// Begin Formatting
		// Get Precision and scale from the field's properties
		short nPrec=10, nScale=2;
		BYTE cTemp;
		GX_ADO_CHECK(pAdoField->get_Precision(&cTemp), piRecordset, bSuccess)
		if(!bSuccess)
			ASSERT(0);	// Don't know in what format to retrieve data
						// Override ConvertValueToString and retrieve data yourself
		else 
		{
			nPrec = cTemp;
			GX_ADO_CHECK(pAdoField->get_NumericScale(&cTemp), piRecordset, bSuccess)
			if(!bSuccess)
				ASSERT(0);	// Same workaround as above
			else
				nScale = cTemp;
		}
		sFormat.Format(_T("%%%d.%df"), nPrec+1, nScale);	// +1 for decimal; 
		// User reported problem that CString::Format is not able to convert float to double(b'cos of %f) succesfully (even with a cast)
		// Hence using a double explicitly
		double d = (double)ft;
		strRet.Format(sFormat, d);
		// End of formatting
		// Call VariantClear instead of the destructor calling Clear()
		// To prevent bug as described in MS Article ID: Q177912 
		VariantClear(&varValue);
		}
		break;
	case VT_CY:
		strRet = COleCurrency(varValue).Format();
		break;
	case VT_DATE:
		strRet = COleDateTime(varValue).Format();
		break;
	case VT_BSTR:
		strRet = (LPCWSTR)varValue.bstrVal;//$V_BSTRT(&var);
		break;
	case VT_BOOL:
		strRet = V_BOOL(&varValue) ? _T("TRUE") : _T("FALSE");
		break;
	default:
		strRet = _T("Unknown Data type");
		ASSERT(0);
		break;
	}
ErrorExit:
	return;
}


CString GXGetFieldName(CComPtr<ADOField> pADOField)
{
	ASSERT((ADOField*)pADOField != NULL);

	CComBSTR bStr;
	HRESULT hr;
	hr = pADOField->get_Name(&bStr);
	if(FAILED(hr))
		return CString("");
	CString strName = CString(bStr); 
	return strName;
}

CString GXGetFieldName(CComPtr<ADORecordset> pRecordset, int nIndex)
{
	// Get ADOField object and fill in field info struct
	CString s("");
	BOOLEAN bSuccess;
	CComPtr<ADOFields> pADOFields;
	CComPtr<ADOField> pADOField;
	GX_ADO_CHECK(pRecordset->get_Fields(&pADOFields),pRecordset,bSuccess)
	if(!bSuccess)goto ErrorExit;
	GX_ADO_CHECK(pADOFields->get_Item(
		COleVariant((long)nIndex), &pADOField), pRecordset, bSuccess)
	if(!bSuccess)goto ErrorExit;

	s = GXGetFieldName(pADOField);
	
ErrorExit:
	return s;
}


void GXFillChoiceList(CComPtr<ADORecordset> pSet, CString& strChoiceList, BOOL bDisplayHeader)
{
	ASSERT((ADORecordset*)pSet !=NULL);

//	ADOFieldInfo fieldInfo;
//	pSet->GetFieldInfo(1, fieldInfo);
	CComPtr<ADOFields> piFields;
	BOOL bSuccess;
	GX_ADO_CHECK(pSet->get_Fields(&piFields),pSet,bSuccess)
	if(!bSuccess)goto ErrorExit;

	strChoiceList.Empty();

	long nFields;
	GX_ADO_CHECK(piFields->get_Count(&nFields), pSet, bSuccess)


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
	GX_ADO_CHECK(pSet->MoveFirst(),pSet,bSuccess)
	VARIANT_BOOL bEof;
	GX_ADO_CHECK(pSet->get_EOF(&bEof), pSet, bSuccess)	
	while (!bEof)
	{
		for (int nField = 0; nField < nFields; nField++)
		{
			CString strValue;
			GXGetAdoFieldString(strValue, pSet, nField);
			strChoiceList += strValue;
			if (nField < nFields-1)
				strChoiceList += _T("\t");
		}
		strChoiceList += _T("\n");
		pSet->MoveNext();
		GX_ADO_CHECK(pSet->get_EOF(&bEof), pSet, bSuccess)	
	}
ErrorExit:
	return;

}

#endif // #if _MFC_VER >= 0x0420 && !defined(_GX_NO_ADO_SUPPORT)

