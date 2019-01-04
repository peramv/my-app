///////////////////////////////////////////////////////////////////////////////
// ExcelReadView.cpp : implementation of the CGXWChar class
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
// Author: Daniel Jebaraj
//

#define _OG_EXPORT_IMPL

#include "stdafx.h"

#include "grid\gxwchr.h"

CGXWChar::CGXWChar()
{
	// initialize to defaults
	m_pszWChar = NULL;
	m_uiPage = CP_ACP; // ANSI code page
	m_dwFlags = 0;
}
	
CGXWChar::CGXWChar(char* psz, UINT uiPage /*= CP_ACP*/, DWORD dwFlags /*= 0*/)
{
	m_uiPage = uiPage;
	m_dwFlags = dwFlags;
	m_pszWChar = Convert(psz);
}

	
CGXWChar::CGXWChar(WCHAR* pszW, UINT uiPage /*= CP_ACP*/, DWORD dwFlags /*= 0*/)
{
	m_uiPage = uiPage;
	m_dwFlags = dwFlags;
	m_pszWChar = pszW;
}

CGXWChar::~CGXWChar()
{
	Free();
}

void CGXWChar::Free()
{
	if(m_pszWChar != NULL)
		delete m_pszWChar;
	
	m_pszWChar = NULL;
}

WCHAR* CGXWChar::Convert(const char* psz)
{
	if (psz == NULL)
		return NULL;
	
	UINT nCount = MultiByteToWideChar(GetCodePage(), GetFlags(), psz, -1, NULL, NULL);
	
	if(nCount == 0)
	{
		ReportError();
		return NULL;
	}
	
	WCHAR* pszW = NULL;
	
	pszW = new WCHAR[nCount+1];
	
	if(pszW == NULL)
	{
		ReportError();
		return NULL;
	}

	if(!::MultiByteToWideChar(GetCodePage(), GetFlags(), psz, -1, pszW, nCount))
	{
		ReportError();
		return NULL;
	}

	pszW[nCount] = L'0';
	return pszW;
}

WCHAR* CGXWChar::ConvertDef(const char* psz)
{
	if (psz == NULL)
		return NULL;
	
	UINT nCount = MultiByteToWideChar(CP_ACP, 0, psz, -1, NULL, NULL);
	ASSERT(nCount);
	
	if(nCount == 0)
	{
		ReportError();
		return NULL;
	}

	WCHAR* pszW = NULL;
	
	pszW = new WCHAR[nCount+1];
	
	if(pszW == NULL)
	{
		ReportError();
		return NULL;
	}

	if(!::MultiByteToWideChar(CP_ACP, 0, psz, -1, pszW, nCount))
	{
		ReportError();
		return NULL;
	}

	pszW[nCount] = 0;
	
	return pszW;
}

void CGXWChar::FreeAllocData(WCHAR*& pszW)
{
	if(pszW)
		delete pszW;
	
	pszW = NULL;
}

void CGXWChar::ReportError()
{
	LPVOID lpMsgBuf;
	FormatMessage(
	FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
	NULL,
	GetLastError(),
	MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
	(LPTSTR) &lpMsgBuf,
	0,
	NULL );
	TRACE1("OG Pro Error: CGXWChar reports %s\n", (LPTSTR)lpMsgBuf);
	LocalFree( lpMsgBuf );
}

WCHAR* CGXWChar::Clone(const WCHAR* pszW)
{
	UINT nCount = (UINT)wcslen(pszW)+1;
	WCHAR* p = new WCHAR[nCount];
	
	if(p == NULL)
	{
		ReportError();
		return NULL;
	}

	wcscpy(p, pszW);
	return p;
}

const WCHAR* CGXWChar::GetWChar()
{
	return m_pszWChar;
}
	
WCHAR* CGXWChar::GetWCharRef()
{
	return m_pszWChar;
}
	
WCHAR* CGXWChar::Detach()
{
	WCHAR* p = m_pszWChar;
	m_pszWChar = NULL;
	return p;
}
	
void CGXWChar::Attach(WCHAR* pszW)
{
	Free();
	m_pszWChar = pszW;
}
	
void CGXWChar::SetWChar(const WCHAR* pszW)
{
	Free();
	m_pszWChar = CGXWChar::Clone(pszW);
}
	
void CGXWChar::SetChar(const char* psz)
{
	Free();
	m_pszWChar = Convert(psz);
}

UINT CGXWChar::GetCodePage() const
{
	return m_uiPage;
}
	
void CGXWChar::SetCodePage(UINT uiPage)
{
	m_uiPage = uiPage; 
}

DWORD CGXWChar::GetFlags() const
{
	return m_dwFlags;
}

void CGXWChar::SetFlags(DWORD dwFlags)
{
	m_dwFlags = dwFlags;
}

