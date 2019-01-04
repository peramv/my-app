///////////////////////////////////////////////////////////////////////////////
// gxccombo.cpp : implementation of the CGXGridCombo class
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

#ifndef _GXCORE_H_
#include "grid\gxcore.h0
#endif

#ifndef _GXCTRLI_H_
#include "grid\gxctrli.h"
#endif

#ifndef _GXDLL_H_
#include "grid\gxdll.h" // GXGetResourceHandle
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXCCOMBO")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

#ifndef WS_EX_TOOLWINDOW
#define WS_EX_TOOLWINDOW (GXGetAppData()->bWin4?0x00000080L:0L)
#endif

IMPLEMENT_DYNAMIC(CGXGridCombo, CWnd)

CGXGridCombo::CGXGridCombo(CWnd* pGridWnd, CWnd* pWnd, const CRect& rect)
{
	// Unused
	pWnd;

	m_pGridWnd = pGridWnd;
	m_pListBox = NULL;
	m_bColor = FALSE;

	SetComboBoxDropDown(TRUE);

	if (!CreateEx(
		WS_EX_TOOLWINDOW, GetClassName(), NULL, WS_POPUP | WS_VISIBLE,
		rect.left-1, rect.top, rect.Width()+1, rect.Height(),
		::GetDesktopWindow(), NULL))
	{
		TRACE0("Failed to create popup window in CGXGridCombo\n");
		ASSERT(0);
		// ASSERTION-> Failed to create popup window
		// Did you register the windowclass with CGXGridCombo::RegisterClass? ->END
	}

	SetComboBoxDropDown(FALSE);

	ASSERT_VALID(this);
}

void CGXGridCombo::AttachListBox(CWnd* pListBox)
{
	ASSERT_VALID(pListBox);

	m_pListBox = pListBox;
}

CGXGridCombo::~CGXGridCombo()
{
	if (m_pListBox)
		delete m_pListBox;
}

void AFXAPI CGXGridCombo::RegisterClass()
{
	GXGetAppData()->sComboClassName = AfxRegisterWndClass(CS_SAVEBITS);
}

void AFXAPI CGXGridCombo::UnregisterClass()
{
	if (GXGetAppData()->sComboClassName.GetLength() > 0)
		::UnregisterClass(GXGetAppData()->sComboClassName, GXGetResourceHandle());
	GXGetAppData()->sComboClassName.Empty();
}

BOOL AFXAPI CGXGridCombo::GetComboBoxDropDown()
{
	return GXGetAppData()->m_bDiscardNcActivate;
}

CString AFXAPI CGXGridCombo::GetClassName()
{
	return GXGetAppData()->sComboClassName;
}

void AFXAPI CGXGridCombo::SetComboBoxDropDown(BOOL b)
{
	GXGetAppData()->m_bDiscardNcActivate = b;
}

void CGXGridCombo::SetColor(COLORREF rgbText, COLORREF rgbBack)
{
	br.DeleteObject();
	m_bColor = TRUE;
	m_rgbText = rgbText;
	m_rgbBack = rgbBack;
	br.CreateSolidBrush(rgbBack);
}

BEGIN_MESSAGE_MAP(CGXGridCombo, CWnd)
	//{{AFX_MSG_MAP(CGXGridCombo)
	ON_WM_CTLCOLOR()
	ON_WM_ACTIVATE()
	ON_WM_SYSCOMMAND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// ======== CGXGridCombo message handlers

HBRUSH CGXGridCombo::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	if (m_bColor)
	{
		pDC->SetBkColor(m_rgbBack);
		pDC->SetTextColor(m_rgbText);
		return (HBRUSH) br.GetSafeHandle();
	}

	return CWnd::OnCtlColor(pDC, pWnd, nCtlColor);
}

BOOL CGXGridCombo::OnCommand(WPARAM wParam, LPARAM lParam)
{
#if _MFC_VER < 0x0300
	// UINT nNotification = HIWORD(lParam);
	HWND hCtl = (HWND) LOWORD(lParam);
#else
	// UINT nNotification = HIWORD(wParam);
	HWND hCtl = (HWND) lParam;
#endif

	if (hCtl == m_pListBox->GetSafeHwnd())
		return (BOOL) m_pGridWnd->SendMessage(WM_COMMAND, wParam, lParam);

	return CWnd::OnCommand(wParam, lParam);
}

void CGXGridCombo::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	ASSERT_VALID(this);

	CWnd::OnActivate(nState, pWndOther, bMinimized);
}

void CGXGridCombo::OnSysCommand(UINT nID, LPARAM lParam) 
{
	// Don't allow WM_SYSCOMMAND messages while dropdown list 
	// is visible

	// Unused:
	nID, lParam;

	return; 
}
