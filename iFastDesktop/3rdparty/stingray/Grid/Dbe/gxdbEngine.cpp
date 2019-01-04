///////////////////////////////////////////////////////////////////////////////
// gxdbEngine.cpp : implementation of CGXDBEngine
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
// Author: Praveen Ramesh
//

#define _OG_EXPORT_IMPL

#include "stdafx.h"

#ifdef _GXDLL
#undef AFXAPI_DATA
#define AFXAPI_DATA __based(__segname("_DBENGINE"))
#endif

#ifndef _GXDBENGINE
#include "grid\dbe\gxdbengine.h"
#endif

// Minimal implementation for the (impure) abstract base class.
CGXDBEngine::CGXDBEngine()
{
	m_nIncrement = 512;	// Fetch in increments of 512...
	m_nEditRecord = -1;
	m_nEditMode = noMode;
	m_bEOF = FALSE;
	m_nTransPending = 0;
}

CGXDBEngine::~CGXDBEngine()
{
	CleanUp();
}

void CGXDBEngine::CleanUp()
{
}

BOOL CGXDBEngine::IsEOFSeen()
{
	return m_bEOF;
}

void CGXDBEngine::OnDeletedRecords()
{
}

void CGXDBEngine::BeginTrans(LPCTSTR /*pszDescription*/)
{
}

void CGXDBEngine::CommitTrans()
{
}

void CGXDBEngine::Rollback()
{
}

CGXDBEngine* CGXDBEngine::GetChildAt(long /*nRecord*/)
{
	return NULL;
}

BOOL CGXDBEngine::AreChildrenAvailable()
{
	return FALSE;
}
