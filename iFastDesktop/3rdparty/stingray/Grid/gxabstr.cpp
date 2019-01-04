///////////////////////////////////////////////////////////////////////////////
// gxabstr.cpp : Function implementations for abstract base classes
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
#include <stdarg.h>

#ifdef _GXDLL
#undef AFXAPI_DATA
#define AFXAPI_DATA __based(__segname("_DATA"))
#endif

// Headers

#ifndef _GXABSTR_H_
#include "grid\gxabstr.h"
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXABSTR")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif



#if _MFC_VER >= 0x0400 && !defined(_AFX_NO_OLE_SUPPORT)

//////////////////////////////////////////////////////////////////////////////
// CGXNoOleDataSourceProxy

CGXNoOleDataSourceProxy::~CGXNoOleDataSourceProxy()
{
}

//////////////////////////////////////////////////////////////////////////////
// CGXNoOleDataObjectProxy

CGXNoOleDataObjectProxy::~CGXNoOleDataObjectProxy()
{
}

#endif

//////////////////////////////////////////////////////////////////////////////
// CGXNoToolTipCtrlProxy

CGXNoToolTipCtrlProxy::~CGXNoToolTipCtrlProxy()
{
}

//////////////////////////////////////////////////////////////////////////////
// CGXAbstractCommandFactory

CGXAbstractCommandFactory::~CGXAbstractCommandFactory()
{
}

//////////////////////////////////////////////////////////////////////////////

// Helper for warning about calls unimplemented functions

#ifdef _DEBUG

void AFXAPI GXCheckImp(void* pImp, LPCTSTR pszFunc)
{
	void* vptr;
	if (pImp == NULL && !GXGetAppData()->m_mapNoImpWarnings.Lookup(pszFunc, vptr))
	{
		GXGetAppData()->m_mapNoImpWarnings.SetAt(pszFunc, (void*) pszFunc);
		TRACE(_T("Warning: No concrete implementation for %s.\n"), pszFunc);

		ASSERT(!GXGetAppData()->m_mapAssertNoImp.Lookup(pszFunc, vptr));
		// ASSERTION-> GXSetAssertNoImp caused ASSERT ->END
	}
}

void AFXAPI GXSetAssertNoImp(LPCTSTR pszFunc)
{
	GXGetAppData()->m_mapAssertNoImp.SetAt(pszFunc, (void*) pszFunc);
}

void AFX_CDECL GXTraceOnce(LPCTSTR lpszFormat, ...)
{
	va_list args;
	va_start(args, lpszFormat);

	int nBuf;
	TCHAR szBuffer[512];

	// QA: 31989 - #if Secure Code Cleanup.
	nBuf = _vsntprintf(szBuffer, 512, lpszFormat, args);

	// was there an error? was the expanded string too long?
	ASSERT(nBuf >= 0);

	void* vptr;
	if (!GXGetAppData()->m_mapTraceOnce.Lookup(szBuffer, vptr))
	{
		GXGetAppData()->m_mapNoImpWarnings.SetAt(szBuffer, (void*) lpszFormat);
		TRACE(szBuffer);
	}

	va_end(args);
}

#endif //_DEBUG

