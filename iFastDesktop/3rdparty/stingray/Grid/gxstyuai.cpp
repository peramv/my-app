///////////////////////////////////////////////////////////////////////////////
// gxstyuai.cpp : implementation of the CGXUserAttribute class
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

#ifndef _GXRESRC_H_
#include "grid\gxresrc.h"
#endif

#ifndef _GXSTYLES_H_
#include "grid\gxstyles.h"
#endif

#ifndef _GXSTATE_H_
#include "grid\gxstate.h"
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXSTYUAI")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CGXUserAttribute, CGXAbstractUserAttribute, 0 /* schema number*/ )
IMPLEMENT_SERIAL(CGXEllipseUserAttribute, CGXAbstractUserAttribute, 0 /* schema number*/ )

/////////////////////////////////////////////////////////////////
// CGXStyle

// User attributs

CGXStyle& CGXStyle::SetIncludeUserAttribute(WORD nID, BOOL b)
{
	const CGXAbstractUserAttribute* pValue = NULL;

	BOOL bExist = m_pmapUserAttributes && (pValue = m_pmapUserAttributes->GetAttribute(nID)) != 0;

	// Check if state is changing
	if (b && !bExist || !b && bExist)
	{
		if (b)
		{
			// Allocate user attribues map
			if (m_pmapUserAttributes == NULL)
				m_pmapUserAttributes = new CGXUserAttributeMap;
			// Assign empty string
			m_pmapUserAttributes->SetAttributePtr(nID, new CGXUserAttribute());
			stylebits.userattr = 1;
		}
		else
		{
			// Clear out attribute and delete string
			// delete pValue;
			m_pmapUserAttributes->DeleteAttribute(nID);
			if (m_pmapUserAttributes->IsEmpty())
				stylebits.userattr = 0;
		}
	}

	return *this;
}

/////////////////////////////////////////////////////////////////
// CGXUserAttribute

static BOOL _deval(const CString& s, double *d)
{
	if (GXGetAppData()->m_pNumberFormattingImp && !GXDeval(s, d))
		return FALSE;

	// Make sure we return the same string that we got
	// (this fixes problems if we should store leading zeros. e.g.
	// 000333)

	CString t;
	t.Format(_T("%.13g"), *d);

	return t == s;
}

CGXUserAttribute::CGXUserAttribute()
{
	m_vtType = vtEmpty;
	memset(&m_value, 0, sizeof(m_value));
}

CGXUserAttribute::CGXUserAttribute(DWORD value)
{
	m_vtType = vtDWord;
	m_value.dwValue = value;
}

CGXUserAttribute::CGXUserAttribute(LONG value)
{
	m_vtType = vtLong;
	m_value.lValue = value;
}

CGXUserAttribute::CGXUserAttribute(const CString& value)
{
	double d;
	if (_deval(value, &d))
	{
		m_vtType = vtDouble;
		m_value.dValue = d;
	}
	else if (value.GetLength() <= 8/sizeof(TCHAR))
	{
		m_vtType = vtShortString;
		// QA: 31989 - #if Secure Code Cleanup.
		_tcsncpy(m_value.szShortString, value, 8/sizeof(TCHAR));
	}
	else
	{
		m_vtType = vtString;
		m_value.pszValue = new TCHAR[value.GetLength()+1];
		// QA: 31989 - #if Secure Code Cleanup.
		_tcscpy(m_value.pszValue, value);
	}
}

CGXUserAttribute::CGXUserAttribute(LPCTSTR pszValue)
{
	double d;
	if (_deval(pszValue, &d))
	{
		m_vtType = vtDouble;
		m_value.dValue = d;
	}
	else if (_tcslen(pszValue) <= 8/sizeof(TCHAR))
	{
		m_vtType = vtShortString;
		// QA: 31989 - #if Secure Code Cleanup.
		_tcsncpy(m_value.szShortString, pszValue, 8/sizeof(TCHAR));
	}
	else
	{
		m_vtType = vtString;
		m_value.pszValue = new TCHAR[_tcslen(pszValue)+1];
		// QA: 31989 - #if Secure Code Cleanup.
		_tcscpy(m_value.pszValue, pszValue);
	}
}

CGXUserAttribute::CGXUserAttribute(double value)
{
	m_vtType = vtDouble;
	m_value.dValue = value;
}

CGXUserAttribute::CGXUserAttribute(GXBYTE8 value)
{
	m_vtType = vtByte8;
	m_value.b8Value = value;
}

CGXUserAttribute::CGXUserAttribute(const CGXUserAttribute& p)
{
	m_vtType = p.m_vtType;

	if (m_vtType == vtString)
	{
		m_value.pszValue = new TCHAR[_tcslen(p.m_value.pszValue)+1];
		// QA: 31989 - #if Secure Code Cleanup.
		_tcscpy(m_value.pszValue, p.m_value.pszValue);
	}
	else
		// binary copy
		m_value.b8Value = p.m_value.b8Value;
}

CGXUserAttribute::~CGXUserAttribute()
{
	if (m_vtType == vtString)
		// Strings must be emptied because they allocated heap space
		delete[] m_value.pszValue;
}

const CString& CGXUserAttribute::GetValue() const
{
	switch (m_vtType)
	{
	case vtEmpty: 
		m_strValueCache.Empty(); 
		return m_strValueCache;

	case vtDWord: 
		m_strValueCache.Format(_T("%lu"), m_value.dwValue); 
		return m_strValueCache;

	case vtLong:  
		m_strValueCache.Format(_T("%ld"), m_value.lValue);
		return m_strValueCache;

	case vtShortString: 
		{
			LPTSTR p = m_strValueCache.GetBuffer(8/sizeof(TCHAR)+1);
			// QA: 31989 - #if Secure Code Cleanup.
			_tcsncpy(p, m_value.szShortString, 8/sizeof(TCHAR));
			p[8/sizeof(TCHAR)] = 0;
			m_strValueCache.ReleaseBuffer();
		}
		return m_strValueCache;

	case vtString:
		m_strValueCache = m_value.pszValue;
		return m_strValueCache;

	case vtDouble:
		m_strValueCache.Format(_T("%.13g"), m_value.dValue);
		return m_strValueCache;

	case vtByte8:
		{
			DWORD* pd = (DWORD*) &m_value.b8Value;
			m_strValueCache.Format(_T("%08x%08x"), pd[0], pd[1]);
			return m_strValueCache;
		}

	default:
		m_strValueCache = _T("Value?");
		return m_strValueCache;
	}
}

DWORD CGXUserAttribute::GetDWordValue() const
{
	switch (m_vtType)
	{
	case vtEmpty: 
	case vtByte8:
	default:
		return 0;

	case vtDWord: 
		return m_value.dwValue; 

	case vtLong:  
		return (DWORD) m_value.lValue;

	case vtDouble:
		return (DWORD) m_value.dValue;

	case vtShortString: 
	case vtString:
		return (DWORD) _ttol(GetValue());
	}
}

LONG CGXUserAttribute::GetLongValue() const
{
	switch (m_vtType)
	{
	case vtEmpty: 
	case vtByte8:
	default:
		return 0;

	case vtDWord: 
		return (LONG) m_value.dwValue; 

	case vtLong:  
		return m_value.lValue;

	case vtDouble:
		return (LONG) m_value.dValue;

	case vtShortString: 
	case vtString:
		return _ttol(GetValue());
	}
}

double CGXUserAttribute::GetDoubleValue() const
{
	switch (m_vtType)
	{
	case vtEmpty: 
	case vtByte8:
	default:
		return 0;

	case vtDWord: 
		return (double) m_value.dwValue; 

	case vtLong:  
		return (double) m_value.lValue;

	case vtDouble:
		return m_value.dValue;

	case vtShortString: 
	case vtString:
		return _gxttof(GetValue());
	}
}

CGXAbstractUserAttribute& CGXUserAttribute::SetValue(LPCTSTR pszValue)
{
	if (m_vtType == vtString)
		// Strings must be emptied because they allocated heap space
		delete[] m_value.pszValue;

	double d;
	if (_tcslen(pszValue) == 0)
	{
		m_vtType = vtEmpty;
	}
	else if (_deval(pszValue, &d))
	{
		m_vtType = vtDouble;
		m_value.dValue = d;
	}
	else if (_tcslen(pszValue) <= 8/sizeof(TCHAR))
	{
		m_vtType = vtShortString;
		// QA: 31989 - #if Secure Code Cleanup.
		_tcsncpy(m_value.szShortString, pszValue, 8/sizeof(TCHAR));
	}
	else
	{
		m_vtType = vtString;
		m_value.pszValue = new TCHAR[_tcslen(pszValue)+1];
		// QA: 31989 - #if Secure Code Cleanup.
		_tcscpy(m_value.pszValue, pszValue);
	}

	return *this;
}

void CGXUserAttribute::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << (BYTE) m_vtType;
		if (m_vtType != vtString && m_vtType != vtShortString)
			ar << m_value.b8Value;
		else
			ar << GetValue();
	}
	else
	{
		BYTE b;
		ar >> b, m_vtType = (CGXUserAttribute::ValueType) b;
		if (m_vtType != vtString && m_vtType != vtShortString)
			ar >> m_value.b8Value;
		else
		{
			CString s;
			ar >> s;
			if (s.GetLength() <= 8/sizeof(TCHAR))
			{
				m_vtType = vtShortString;
				// QA: 31989 - #if Secure Code Cleanup.
				_tcsncpy(m_value.szShortString, s, 8/sizeof(TCHAR));
			}
			else
			{
				m_vtType = vtString;
				m_value.pszValue = new TCHAR[s.GetLength()+1];
				// QA: 31989 - #if Secure Code Cleanup.
				_tcscpy(m_value.pszValue, s);
			}
		}
	}
}

// Copying attribute (e.g. from one style object to another)
CGXAbstractUserAttribute* CGXUserAttribute::Clone() const
{
	return new CGXUserAttribute(*this);
}

// Comparision
BOOL CGXUserAttribute::IsEqual(const CGXAbstractUserAttribute& pOther) const
{
	// First check id so that we know this is the same attribute type
	if (pOther.m_nId != m_nId)
		return FALSE;

	// Now it is save to assume that other object is also a CGXUserAttribute
	CGXUserAttribute& p = (CGXUserAttribute&) pOther;

	if (m_vtType != p.m_vtType)
		return FALSE;

	switch (m_vtType)
	{
	case vtEmpty:		return TRUE;
	case vtDWord:		return p.m_value.dwValue == m_value.dwValue; 
	case vtLong:		return p.m_value.lValue == m_value.lValue;
	case vtShortString: 
	case vtString:		{ CString s = GetValue(); return s.Compare(p.GetValue()) == 0; }
	case vtDouble:		return p.m_value.dValue == m_value.dValue;
	case vtByte8:		return memcmp(&p.m_value.b8Value, &m_value.b8Value, 8) == 0;
	default:			return FALSE;
	}
}


////////////////////////////////////////////////////////////////////// 
/////////////////////////////////////////////////////////////////////
// CGXEllipseUserAttribute class for gxEllipseType

CGXEllipseUserAttribute::CGXEllipseUserAttribute()
{
	m_gxEllipseType = gxNoEllipse;
}

CGXEllipseUserAttribute::CGXEllipseUserAttribute(gxEllipseType type)
{
	m_gxEllipseType = type;
}

CGXEllipseUserAttribute::CGXEllipseUserAttribute(const CGXEllipseUserAttribute& p)
{
	m_gxEllipseType = p.GetEllipseValue();
}

	
CGXEllipseUserAttribute::~CGXEllipseUserAttribute()
{
	// No implementation
}
	

CGXAbstractUserAttribute& CGXEllipseUserAttribute::SetValue(const CString& strValue)
{
	ASSERT(0);// ---> This user attribute is only to be used with gxEllipseType values
	// for strings use CGXUserAttribute
	return *this;
	strValue;
}

CGXAbstractUserAttribute& CGXEllipseUserAttribute::SetValue(LPCTSTR pszValue)
{
	ASSERT(0);// ---> This user attribute is only to be used with gxEllipseType values
	// for strings use CGXUserAttribute
	return *this;
	pszValue;
}

CGXAbstractUserAttribute& CGXEllipseUserAttribute::SetEllipseValue(gxEllipseType type)
{
	m_gxEllipseType = type;
	return *this;
}

const CString& CGXEllipseUserAttribute::GetValue() const
{
	ASSERT(0);// ---> This user attribute is only to be used with gxEllipseType values
	// for strings use CGXUserAttribute
	m_strValueCache.Empty();
	return m_strValueCache;
}

DWORD CGXEllipseUserAttribute::GetDWordValue() const
{
	ASSERT(0);// ---> This user attribute is only to be used with gxEllipseType values
	// You can ignore this ASSERT if you have reason to do this
	return m_gxEllipseType;
}

LONG CGXEllipseUserAttribute::GetLongValue() const
{
	ASSERT(0);// ---> This user attribute is only to be used with gxEllipseType values
	// You can ignore this ASSERT if you have reason to do this
	return m_gxEllipseType;
}

double CGXEllipseUserAttribute::GetDoubleValue() const
{
	ASSERT(0);// ---> This user attribute is only to be used with gxEllipseType values
	// You can ignore this ASSERT if you have reason to do this
	return m_gxEllipseType;
}

	
gxEllipseType CGXEllipseUserAttribute::GetEllipseValue() const
{
	return m_gxEllipseType;
}

CGXAbstractUserAttribute* CGXEllipseUserAttribute::Clone() const
{
	return new CGXEllipseUserAttribute(*this);
}

void CGXEllipseUserAttribute::Serialize(CArchive& ar)
{
	if(ar.IsStoring())
	{
		ar << (WORD)m_gxEllipseType;
	}
	else
	{
		WORD w(0);
		ar >> w;
		m_gxEllipseType = (gxEllipseType)w;
	}
}

	
BOOL CGXEllipseUserAttribute::IsEqual(const CGXAbstractUserAttribute& pOther) const
{
	ASSERT( pOther.IsKindOf(RUNTIME_CLASS(CGXEllipseUserAttribute)) );
	
	CGXEllipseUserAttribute& p = (CGXEllipseUserAttribute&) pOther;

	if( p.m_gxEllipseType == m_gxEllipseType)
		return TRUE;
	else
		return FALSE;
}

BOOL CGXEllipseUserAttribute::IsEmpty() const
{
	ASSERT(0);
	return TRUE;
}


