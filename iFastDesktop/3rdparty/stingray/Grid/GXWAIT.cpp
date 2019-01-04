///////////////////////////////////////////////////////////////////////////////
// GxWait.cpp
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

// gxwait.cpp : implementation of the CGXLongOperation class
//

//
// Change Log:
//	03.14.2006 - Converted deprecated functions to their secure counter parts. 
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

#ifndef _AFXPRIV_H_
#include "afxpriv.h"
#endif

#ifndef _GXEXT_H_
#include "grid\gxext.h"
#endif

#ifndef _GXSTATE_H_
#include "grid\gxstate.h"
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXWAIT")
#endif

#ifdef _DEBUG
#undef THIS_FILE
#define new DEBUG_NEW
static char THIS_FILE[] = __FILE__;
#endif

#ifndef _GXDLL
CThreadLocal<GX_WAIT_STATE> GXNEAR _gxWaitState;
#endif

/////////////////////////////////////////////////////////////////////////////
// GX_WAIT_STATE

GX_WAIT_STATE::GX_WAIT_STATE()
{
	m_dwTicksFirstTime = 750;
	m_dwTicksContinued = 1500;

	m_bAbortDialog = TRUE;
	m_bWaitCursor = FALSE;
	m_bCanceled = FALSE;
	m_bUserConfirmed = FALSE;
	m_bRollbackConfirmed = FALSE;

	m_bCanAbort = TRUE;
	m_bCanRollback = TRUE;

	m_nRefCount = 0;
	m_nLevelLocked = -1;

	m_nPercentDone = -1;

	memset((void*) m_apszStatusText, 0, sizeof(m_apszStatusText));
	memset(m_abOwnStatusText, 0, sizeof(m_abOwnStatusText));

	m_nIndicatorState = 0;
	// QA: 31989 - #if Secure Code Cleanup.
	_tcscpy(m_szStatusBuf, _T(""));

	m_hFrameWnd = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// CGXLongOperation

CGXLongOperation::CGXLongOperation()
{
	GX_WAIT_STATE* pWaitState = GXGetWaitState();

	if (GXGetAppData()->m_pLongOperationImp)
		GXGetAppData()->m_pLongOperationImp->Start(this);
	else
		pWaitState->m_nRefCount++;
}

CGXLongOperation::~CGXLongOperation()
{
	GX_WAIT_STATE* pWaitState = GXGetWaitState();

	if (GXGetAppData()->m_pLongOperationImp)
		GXGetAppData()->m_pLongOperationImp->Stop(this);
	else
		--pWaitState->m_nRefCount;
}

void CGXLongOperation::FreeStatusText()
{
	if (GXGetAppData()->m_pLongOperationImp)
		GXGetAppData()->m_pLongOperationImp->FreeStatusText(this);
}

void CGXLongOperation::SetStatusText(LPCTSTR pszText, BOOL bCopyBuffer)
{
	if (GXGetAppData()->m_pLongOperationImp)
		GXGetAppData()->m_pLongOperationImp->SetStatusText(this, pszText, bCopyBuffer);
}

BOOL CGXLongOperation::DoMessages()
{
	if (GXGetAppData()->m_pLongOperationImp)
		return GXGetAppData()->m_pLongOperationImp->DoMessages(this);

	return FALSE;
}

BOOL CGXLongOperation::DoMessages(BOOL& bAbort)
{
	bAbort = FALSE;

	if (GXGetAppData()->m_pLongOperationImp)
		return GXGetAppData()->m_pLongOperationImp->DoMessages(this, bAbort);

	return FALSE;
}

// Implementation

void CGXLongOperation::ProcessMessages()
{
	if (GXGetAppData()->m_pLongOperationImp)
		GXGetAppData()->m_pLongOperationImp->ProcessMessages(this);
}

