///////////////////////////////////////////////////////////////////////////////
// gxoleusr.cpp
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

#define _OG_EXPORT_IMPL

#include "stdafx.h"

#if _MFC_VER >= 0x0400

#ifdef _GXDLL
// used for MFC 2.5 Extension DLL
	#undef AFXAPI_DATA
	#define AFXAPI_DATA __based(__segname("_DATA"))
#endif

#ifndef __AFXTEMPL_H__
#include "afxtempl.h"
#endif

#ifndef _GX_MAN_H__
#include "grid\gxman.h"
#endif

#ifndef _GX_OLEVARIANT_USER_H__
#include "grid\gxoleusr.h"
#endif


#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif


#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXDAGRID")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif


/////////////////////////////////////////////////////////////////
// User Attributes

/////////////////////////////////////////////////////////////////
// CGXOleVarUserAttribute

IMPLEMENT_SERIAL(CGXOleVarUserAttribute, CGXAbstractUserAttribute, 0)


CGXCaptiveManager<COleVariant> CGXOleVarUserAttribute::g_VarCreator;

CGXOleVarUserAttribute::CGXOleVarUserAttribute()
{
	m_pOleVar = NULL;
	m_bModifyState = FALSE;
}

CGXOleVarUserAttribute::CGXOleVarUserAttribute(const COleVariant& var)
{
	m_pOleVar = NULL;
	m_bModifyState = FALSE;

	SetOleVarValue(var);
}

CGXOleVarUserAttribute::~CGXOleVarUserAttribute()
{
	if(m_pOleVar)
		g_VarCreator.RecycleObject(m_pOleVar);
}

CGXAbstractUserAttribute& CGXOleVarUserAttribute::SetValue(const CString& strValue)
{
	UNUSED(strValue);
	ASSERT(0);
	return *this;

	GX_UNUSED_ALWAYS(strValue);
}

CGXOleVarUserAttribute::operator LPCTSTR() const
{
	return GetValue();
}

void CGXOleVarUserAttribute::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
#ifdef _WIN64
		ar << (ULONGLONG)GetOleVarValue();
#else	//WIN32
		ar << (DWORD)GetOleVarValue();
#endif	//_WIN64
	else
	{
#ifdef _WIN64
		ULONGLONG dw;
#else	//WIN32
		DWORD dw;
#endif	//_WIN64
		ar >> dw;
		if(dw != NULL)
			SetOleVarValue(*reinterpret_cast<COleVariant*>(dw));
	}
}

BOOL CGXOleVarUserAttribute::IsEqual(const CGXOleVarUserAttribute& p) const
{
	// First check id so that we know this is the same attribute type
	if (p.m_nId != m_nId)
		return FALSE;

	return m_pOleVar == p.GetOleVarValue();
}

BOOL CGXOleVarUserAttribute::IsEmpty() const
{
	return ((LPCVARIANT)*GetOleVarValue())->vt == VT_EMPTY;
}

CGXAbstractUserAttribute& CGXOleVarUserAttribute::SetValue(LPCTSTR )
{
	ASSERT(0);
	// ASSERTION-> Do not register this attribute with 
	// CGXStylesMap::AddUserAttribute. ->END
	return *this;
}

const CString& CGXOleVarUserAttribute::GetValue() const
{
	// no CString value 
	ASSERT(0);
	// ASSERTION-> Do not register this attribute with 
	// CGXStylesMap::AddUserAttribute. ->END
	return m_strValueCache;
}

CGXOleVarUserAttribute& CGXOleVarUserAttribute::SetOleVarValue(const COleVariant& var )
{
	ASSERT(m_bModifyState == FALSE);
	
	if(m_pOleVar)
		m_pOleVar->Clear();
	else
		m_pOleVar = g_VarCreator.CreateObject();
	
	// assign the value
	if(var.vt != VT_EMPTY || var.vt != VT_NULL)
		*m_pOleVar = var;

	return *this;
}

const COleVariant* CGXOleVarUserAttribute::GetOleVarValue() const
{
	if(m_pOleVar)
		return m_pOleVar;
	else
		return NULL;
}
CGXAbstractUserAttribute* CGXOleVarUserAttribute::Clone() const
{
	CGXOleVarUserAttribute* pVar = new CGXOleVarUserAttribute();
	
	if( m_pOleVar != NULL )
		pVar->SetOleVarValue(*m_pOleVar);
	
	return pVar;
}

#endif //#if _MFC_VER >= 0x0400
