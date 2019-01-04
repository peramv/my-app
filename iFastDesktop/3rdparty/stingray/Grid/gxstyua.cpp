///////////////////////////////////////////////////////////////////////////////
// gxstyua.cpp : implementation of the CGXAbstractUserAttribute classes
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
#pragma code_seg("GX_SEG_GXSTYUA")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CGXUserAttributeMap, CObArray, 0 /* schema number*/ )
IMPLEMENT_SERIAL(CGXAbstractUserAttribute, CObject, 0 /* schema number*/ )

CString CGXAbstractUserAttribute::m_strValueCache;


/////////////////////////////////////////////////////////////////
// User Attributes

/////////////////////////////////////////////////////////////////
// CGXAbstractUserAttribute

CGXAbstractUserAttribute::CGXAbstractUserAttribute()
{
}

CGXAbstractUserAttribute::~CGXAbstractUserAttribute()
{
}

//@doc 
//@mfunc 
//@parm CString | strValue | A CString with the text value.
//@rem
//SetValue is called with a <c CString> and changes the value of your attribute. 
//Override this method if you want to support reading values from registry 
//or the user attribute page. In your override you should interprete the <c CString> 
//and convert it to your binary representation of the value.
//@ex |
/*
CGXAbstractUserAttribute& CGXUserAttribute::SetValue(LPCTSTR pszValue)
{
   if (m_vtType == vtString)
      // Strings must be emptied because they allocated heap space
      delete m_value.pszValue;

   double d;
   if (_tcslen(pszValue) == 0)
   {
      m_vtType = vtEmpty;
   }
   else if (GXDeval(pszValue, &d))
   {
      m_vtType = vtDouble;
      m_value.dValue = d;
   }
   else if (_tcslen(pszValue) <= 8/sizeof(TCHAR))
   {
      m_vtType = vtShortString;
      _tcsncpy(m_value.szShortString, pszValue, 8/sizeof(TCHAR));
   }
   else
   {
      m_vtType = vtString;
      m_value.pszValue = new TCHAR[_tcslen(pszValue)+1];
      _tcscpy(m_value.pszValue, pszValue);
   }

   return *this;
}
*/
//@xref <c CGXAbstractUserAttribute> 
CGXAbstractUserAttribute& CGXAbstractUserAttribute::SetValue(const CString& strValue)
{
	return SetValue((LPCTSTR) strValue);
}

CGXAbstractUserAttribute::operator LPCTSTR() const
{
	return GetValue();
}

//@doc 
//@mfunc 
//@parm CArchive& | ar | A <c CArchive>-object for serialization 
//@rdesc
//<bold>TRUE<ebold> if object is empty; <bold>FALSE<ebold> otherwise. 
//@rem
//Override this method if you want to support serialization 
//and clipboard operations for this attribute class.
//@xref <c CGXAbstractUserAttribute> 
void CGXAbstractUserAttribute::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
		ar << GetValue();
	else
	{
		CString s;
		ar >> s;
		SetValue(s);
	}
}

//@doc 
//@mfunc 
//@parm CGXAbstractUserAttribute& | p | A reference to the other user attribute 
//@rdesc
//<bold>TRUE<ebold> if object is empty; <bold>FALSE<ebold> otherwise. 
//@rem
//Compares two user attributes. The default implementation will simply compare 
//the values returned by <mf GetValue> for both attributes to be compared. 
//Override this method if you need a more specialized behavior for your user attribute.
//@xref <c CGXAbstractUserAttribute> 
BOOL CGXAbstractUserAttribute::IsEqual(const CGXAbstractUserAttribute& p) const
{
	// First check id so that we know this is the same attribute type
	if (p.m_nId != m_nId)
		return FALSE;

	CString s = GetValue();

	return s.Compare(p.GetValue()) == 0;
}

//@doc 
//@mfunc 
//@rdesc
//<bold>TRUE<ebold> if object is empty; <bold>FALSE<ebold> otherwise. 
//@rem
//Checks if the value is empty. By default it simply checks if <mf GetValue> returns an empty string. 
//Override this method if you need a more specialized behavior for your user attribute.
//@xref <c CGXAbstractUserAttribute> 
BOOL CGXAbstractUserAttribute::IsEmpty() const
{
	return GetValue().IsEmpty();
}

//@doc 
//@mfunc 
//@parm LPCTSTR | pszValue | A pointer to the string with the text value.
//@rem
//SetValue is called with a <c CString> and changes the value of your attribute. 
//Override this method if you want to support reading values from registry 
//or the user attribute page. In your override you should interprete the <c CString> 
//and convert it to your binary representation of the value.
//@ex |
/*
CGXAbstractUserAttribute& CGXUserAttribute::SetValue(LPCTSTR pszValue)
{
   if (m_vtType == vtString)
      // Strings must be emptied because they allocated heap space
      delete m_value.pszValue;

   double d;
   if (_tcslen(pszValue) == 0)
   {
      m_vtType = vtEmpty;
   }
   else if (GXDeval(pszValue, &d))
   {
      m_vtType = vtDouble;
      m_value.dValue = d;
   }
   else if (_tcslen(pszValue) <= 8/sizeof(TCHAR))
   {
      m_vtType = vtShortString;
      _tcsncpy(m_value.szShortString, pszValue, 8/sizeof(TCHAR));
   }
   else
   {
      m_vtType = vtString;
      m_value.pszValue = new TCHAR[_tcslen(pszValue)+1];
      _tcscpy(m_value.pszValue, pszValue);
   }

   return *this;
}
*/
//@xref <c CGXAbstractUserAttribute> 
CGXAbstractUserAttribute& CGXAbstractUserAttribute::SetValue(LPCTSTR )
{
	ASSERT(0);
	// ASSERTION-> If you have registered the user attribute with
	// CGXStylesMap::AddUserAttribute this method must be implemented
	// so that the value can be changed in the user attribute page
	// and loaded from the registry ->END

	return *this;
}

//@doc 
//@mfunc 
//@rem 
//The textual representation of the binary value stored in this object.
//<f GetValue> returns a <c CString> with the textual representation 
//of the binary stored in the user attribute. Override this method 
//if you want to support writing values to registry or the user attribute page.
//@ex |
/*
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
*/
//@xref <c CGXAbstractUserAttribute> 

const CString& CGXAbstractUserAttribute::GetValue() const
{
	m_strValueCache.Empty();
	return m_strValueCache;
}

//@doc 
//@mfunc 
//@rem 
//<f GetDWordValue> returns a DWORD value. By default, the method returns (DWORD) atol(GetValue());<nl>
//
//The <c CGXUserAttribute> class provides an optimized version of this method. The internally stored
//number will be returned directly.
//@xref <c CGXAbstractUserAttribute> 
DWORD CGXAbstractUserAttribute::GetDWordValue() const
{
	return (DWORD) _ttol(GetValue());
}

//@doc 
//@mfunc 
//@rem 
//<f GetLongValue> returns a LONG value. By default, the method returns atol(GetValue());<nl>
//
//The <c CGXUserAttribute> class provides an optimized version of this method. The internally stored
//number will be returned directly.
//@xref <c CGXAbstractUserAttribute> 
LONG CGXAbstractUserAttribute::GetLongValue() const
{
	return _ttol(GetValue());
}

//@doc 
//@mfunc 
//@rem 
//<f GetDoubleValue> returns a double value. By default, the method returns atof(GetValue());<nl>
//
//The <c CGXUserAttribute> class provides an optimized version of this method. The internally stored
//number will be returned directly.
//@xref <c CGXAbstractUserAttribute> 
double CGXAbstractUserAttribute::GetDoubleValue() const
{
	return _gxttof(GetValue());
}

//@doc 
//@mfunc 
//@rem Clones this object. If you derive from 
//<c CGXAbstractUserAttribute> you have to provide this method.
//@ex |
/*
    // Copying attribute (e.g. from one style object to another)
   CGXAbstractUserAttribute* CGXUserAttribute::Clone() const
   {
      return new CGXUserAttribute(*this);
   }
*/
//@xref <c CGXAbstractUserAttribute> 
CGXAbstractUserAttribute* CGXAbstractUserAttribute::Clone() const
{
	ASSERT(0);
	// ASSERTION-> This method must be implemented in your derived
	// class. You should simply call 
	// return new CYourUserAttibute(*this);
	// ->END

	return NULL;
}

/////////////////////////////////////////////////////////////////
// CGXUserAttributeMap

CGXUserAttributeMap::CGXUserAttributeMap()
{
}

CGXUserAttributeMap::~CGXUserAttributeMap()
{
	Empty();
}

void CGXUserAttributeMap::Empty()
{
	for (int i = 0; i < GetSize(); i++)
	{
		CGXAbstractUserAttribute* p = (CGXAbstractUserAttribute*) GetAt(i);
		delete p;
	}

	RemoveAll();
}

BOOL CGXUserAttributeMap::IsEmpty() const
{
	return GetSize() == NULL;
}

// Attributes (each CGXUserAttributeMap always holds its own
// attribute objects on the heap)
void CGXUserAttributeMap::SetAttribute(WORD nID, const CGXAbstractUserAttribute& attribute)
{
	SetAttributePtr(nID, attribute.Clone());
}

void CGXUserAttributeMap::SetAttributePtr(WORD nID, CGXAbstractUserAttribute* pValue)
{
	int nIndex = FindAttribute(nID);
	pValue->m_nId = (WORD) nID;

	if (nIndex != -1)
	{
		CGXAbstractUserAttribute* p = (CGXAbstractUserAttribute*) GetAt(nIndex);
		delete p;

		SetAt(nIndex, pValue);
	}
	else
	{
		SetAtGrow(GetSize(), pValue);
		Sort();
	}
}

void CGXUserAttributeMap::DeleteAttribute(WORD nID)
{
	int nIndex = FindAttribute(nID);

	if (nIndex != -1)
	{
		CGXAbstractUserAttribute* p = (CGXAbstractUserAttribute*) GetAt(nIndex);
		delete p;

		RemoveAt(nIndex);
	}
}

const CGXAbstractUserAttribute* CGXUserAttributeMap::GetAttribute(WORD nID) const
{
	int nIndex = FindAttribute(nID);

	if (nIndex != -1)
		return (CGXAbstractUserAttribute*) GetAt(nIndex);
	else
		return NULL;
}

void CGXUserAttributeMap::ChangeMap(const CGXUserAttributeMap* pSrc, GXModifyType mt)
{
	// Append new attributes
	if (mt == gxCopy)
		Empty();

	if (mt == gxExclude)
	{
		for (int nSrc = 0; nSrc < pSrc->GetSize(); nSrc++)
		{
			CGXAbstractUserAttribute* p = (CGXAbstractUserAttribute*) pSrc->GetAt(nSrc);
			DeleteAttribute(p->m_nId);
		}
	}
	else
	{
		CObArray objArray;
		for (int nSrc = 0; nSrc < pSrc->GetSize(); nSrc++)
		{
			CGXAbstractUserAttribute* p = (CGXAbstractUserAttribute*) pSrc->GetAt(nSrc);
			int nIndex = FindAttribute(p->m_nId);
			if (mt == gxApplyNew && nIndex != -1)
				continue;

			CGXAbstractUserAttribute* pClone = p->Clone();
			pClone->m_nId = p->m_nId;

			if (nIndex != -1)
			{
				CGXAbstractUserAttribute* p = (CGXAbstractUserAttribute*) GetAt(nIndex);
				delete p;

				SetAt(nIndex, pClone);
			}
			else
			{
				objArray.SetAtGrow(objArray.GetSize(), pClone);
			}
		}

		if (objArray.GetSize() > 0)
		{
			InsertAt(GetSize(), &objArray);
			Sort();
		}
	}
}

// Operations
void CGXUserAttributeMap::WriteProfile(LPCTSTR pszSection) const
{
	for (int i = 0; i < GetSize(); i++)
	{
		CGXAbstractUserAttribute* p = (CGXAbstractUserAttribute*) GetAt(i);
		TCHAR s[10];
		wsprintf(s, _T("UA%lu"), p->m_nId);
		AfxGetApp()->WriteProfileString(pszSection, s, p->GetValue());
	}
}

void CGXUserAttributeMap::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << (WORD) GetSize();

		for (int i = 0; i < GetSize(); i++)
		{
			CGXAbstractUserAttribute* p = (CGXAbstractUserAttribute*) GetAt(i);
			ar << p;
			ar << p->m_nId;
		}
	}
	else
	{
		Empty();

		WORD w;
		ar >> w;

		SetSize(w);		

		for (int i = 0; i < GetSize(); i++)
		{
			CGXAbstractUserAttribute* p = NULL;
			ar >> p;
			ar >> p->m_nId;
			SetAt(i, p);
		}
	}
}

#ifndef _WINDU_SOURCE
extern "C" static int __cdecl __gxcomparefindattr(const void* vp1, const void* vp2)
#else
extern "C" int __cdecl __gxcomparefindattr(const void* vp1, const void* vp2)
#endif
{
	WORD nId = (WORD) (SEC_LONG) vp1;
	CGXAbstractUserAttribute* p = *((CGXAbstractUserAttribute**) vp2);
	
	if (nId == p->m_nId)
		return 0;
	else if (nId > p->m_nId)
		return 1;
	else
		return -1;
}

#ifndef _WINDU_SOURCE
extern "C" static int __cdecl __gxcomparesortatt(const void* vp1, const void* vp2)
#else
extern "C" int __cdecl __gxcomparesortatt(const void* vp1, const void* vp2)
#endif
{
	CGXAbstractUserAttribute* p1 = *((CGXAbstractUserAttribute**) vp1);
	CGXAbstractUserAttribute* p2 = *((CGXAbstractUserAttribute**) vp2);
	
	if (p1->m_nId == p2->m_nId)
		return 0;
	else if (p1->m_nId > p2->m_nId)
		return 1;
	else
		return -1;
}


int CGXUserAttributeMap::FindAttribute(WORD nID) const
{                  
	if (m_pData == NULL)
		return -1;
	
	SEC_LONG id = nID;

	// search array	- NOTE: Boundschecker complains
	// at the following line but this call is checked 
	// from us and is safe! So, when running Boundschecker
	// you can simply ignore the error,
	CObject** pItem = NULL;
	if (GetSize() > 0)
		pItem = (CObject**) bsearch(
			(const void*) id, 
			m_pData, 
			(size_t) GetSize(), 
			sizeof(CObject*), 
			__gxcomparefindattr);

	if (pItem == NULL)
		return -1;
	else
		return (int)(pItem-m_pData);
}

void CGXUserAttributeMap::Sort()
{
	qsort(m_pData, (size_t) GetSize(), sizeof(void*), __gxcomparesortatt);
}

