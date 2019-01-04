///////////////////////////////////////////////////////////////////////////////
// gxcorfr.cpp : Find and Replace (CGXGridCore)
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

#pragma warning(disable: 4267)

#ifdef _GXDLL
#undef AFXAPI_DATA
#define AFXAPI_DATA __based(__segname("_DATA"))
#endif

// Headers

#ifndef _GXRESRC_H_
#include "grid\gxresrc.h"
#endif

#ifndef _GXCORE_H_
#include "grid\gxcore.h"
#endif

#ifndef _GXCTRL_H_
#include "grid\gxctrl.h"
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXCORFR")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// GX_FR_STATE : last find/replace state

GX_FR_STATE::GX_FR_STATE()
{
	pFindReplaceDlg = NULL;
	bCase = FALSE;
	bNext = TRUE;
	bTransaction = TRUE;
#ifdef _UNICODE
	lpszMultiByteFindString = NULL;
#endif
	m_pActiveGrid = NULL;
	pFindReplaceDlgOwner = NULL;
	m_pStyle = NULL;
}

GX_FR_STATE::~GX_FR_STATE()
{
	strFind.Empty();
	strFindUpper.Empty();
	strReplace.Empty();
#ifdef _UNICODE
	delete[] lpszMultiByteFindString;
#endif
}

void GX_FR_STATE::PrepareFindReplace()
{
	strFindUpper = strFind;
	if (!bCase)
		strFindUpper.MakeUpper();

#ifdef _UNICODE
	// provide also a non UNICODE string
	delete[] lpszMultiByteFindString;

	int nLen = _tcsclen(strFind) + 1;
	lpszMultiByteFindString = new char[nLen];
	WideCharToMultiByte (CP_ACP, 0, (LPCWSTR) strFind, -1,
		lpszMultiByteFindString, nLen, NULL, NULL);
#endif
}

#if !defined(_GXDLL)
	// QA: 32120 - Wrapping with CThreadLocal.
	CThreadLocal<GX_FR_STATE> GXNEAR _gxLastFRState;
#endif


/////////////////////////////////////////////////////////////////////////////
// GX_FRSTATE : last find/replace state

void CGXGridCore::GetSelectedText(CString& strResult)
{
	ROWCOL nRow, nCol;

	if (GetCurrentCell(nRow, nCol))
	{
		CGXControl* pControl = GetControl(nRow, nCol);

		pControl->GetSelectedText(strResult);
	}
	else
		strResult.Empty();
}

void CGXGridCore::OnShowFindReplaceDialog(BOOL bFindOnly)
{
	GX_CHECKIMP(m_pFindReplaceImp, "CGXGridCore::OnShowFindReplaceDialog");

	if (m_pFindReplaceImp)
		m_pFindReplaceImp->OnShowFindReplaceDialog(this, bFindOnly);
}

void CGXGridCore::OnFindNext(LPCTSTR lpszFind, BOOL bNext, BOOL bCase)
{
	GX_CHECKIMP(m_pFindReplaceImp, "CGXGridCore::OnFindNext");

	if (m_pFindReplaceImp)
		m_pFindReplaceImp->OnFindNext(this, lpszFind, bNext, bCase);
}


BOOL CGXGridCore::FindText(BOOL bSetCell /*=TRUE*/)
{
	GX_CHECKIMP(m_pFindReplaceImp, "CGXGridCore::FindText");

	if (m_pFindReplaceImp)
		return m_pFindReplaceImp->FindText(this, bSetCell);

	return FALSE;
}

void CGXGridCore::OnReplaceSel(LPCTSTR lpszFind, BOOL bNext, BOOL bCase, LPCTSTR lpszReplace)
{
	GX_CHECKIMP(m_pFindReplaceImp, "CGXGridCore::OnReplaceSel");

	if (m_pFindReplaceImp)
		m_pFindReplaceImp->OnReplaceSel(this, lpszFind, bNext, bCase, lpszReplace);
}

void CGXGridCore::OnReplaceAll(LPCTSTR lpszFind, LPCTSTR lpszReplace, BOOL bCase)
{
	GX_CHECKIMP(m_pFindReplaceImp, "CGXGridCore::OnReplaceAll");

	if (m_pFindReplaceImp)
		m_pFindReplaceImp->OnReplaceAll(this, lpszFind, lpszReplace, bCase);
}

void CGXGridCore::OnFindReplace(CFindReplaceDialog* pDialog)
{
	GX_CHECKIMP(m_pFindReplaceImp, "CGXGridCore::OnFindReplace");

	if (m_pFindReplaceImp)
		m_pFindReplaceImp->OnFindReplace(this, pDialog);
}

BOOL CGXGridCore::FindText(ROWCOL& nRow, ROWCOL& nCol, BOOL bSetCell)
{
	GX_CHECKIMP(m_pFindReplaceImp, "CGXGridCore::FindText");

	if (m_pFindReplaceImp)
		return m_pFindReplaceImp->FindText(this, nRow, nCol, bSetCell);

	return FALSE;
}

void CGXGridCore::OnTextNotFound(LPCTSTR)
{
	MessageBeep(0);
}

