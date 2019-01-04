///////////////////////////////////////////////////////////////////////////////
// gxview.cpp : implementation of CGXView class
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

#ifndef _GXVIEW_H_
#include "grid\gxview.h"
#endif

#ifndef _GXMSG_H_
#include "grid\gxmsg.h"
#endif

#ifndef _GXEXT_H_
#include "grid\gxext.h"
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXVIEW")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(CGXView, CView)

/////////////////////////////////////////////////////////////////////////////
// CGXView

CGXView::CGXView()
{
	m_pPD = NULL;
	m_bOwnPD = FALSE;
}

CGXView::~CGXView()
{
	if (m_bOwnPD)
		delete m_pPD;
}

/////////////////////////////////////////////////////////////////////////////
// CGXView printing

BOOL CGXView::OnPreparePrinting(CPrintInfo* pInfo)
{
	CGXWaitCursor theWait;

	// TRACE0("CGXView::OnPreparePrinting()\n");
	pInfo->SetMaxPage(0xffff);

	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGXView::OnFilePrintSetup()
{
	CGXWaitCursor theWait;
	// TRACE0("CGXView::OnFilePrintSetup()\n");
	CPrintDialog pd(TRUE);

	DoPrintDialog(&pd);
}

void CGXView::UpdatePrinterDevice(CGXPrintDevice* pd)
{
	if (GXGetAppData()->m_pPrintDeviceImp)
		GXGetAppData()->m_pPrintDeviceImp->UpdatePrinterDevice(pd);
}

int CGXView::DoPrintDialog(CPrintDialog* pPD)
{
	if (GXGetAppData()->m_pPrintDeviceImp)
	{
		int nResponse = GXGetAppData()->m_pPrintDeviceImp->DoPrintDialog(GetPrintDevice(), pPD);

		if (nResponse == IDOK)
			OnModifiedPrintDevice();
	
		return nResponse;
	}

	// No PrintDevice-Object
	return (int)AfxGetApp()->DoPrintDialog(pPD);
}

BOOL CGXView::DoPreparePrinting(CPrintInfo* pInfo)
{
	if (GXGetAppData()->m_pPrintDeviceImp)
	{
		if (!GXGetAppData()->m_pPrintDeviceImp->DoPreparePrinting(this, GetPrintDevice(), pInfo))
			return FALSE;

		OnModifiedPrintDevice();
		return TRUE;
	}

	// No PrintDevice-Object
	return CView::DoPreparePrinting(pInfo);
}

// Printer Settings Object

CGXPrintDevice* CGXView::GetPrintDevice()
{
	return m_pPD;
}

void CGXView::SetPrintDevice(CGXPrintDevice* pPD, BOOL bMustDelete)
{
	ASSERT_VALID(pPD);
	ASSERT(pPD->IsKindOf(RUNTIME_CLASS(CGXPrintDevice)));

	if (m_pPD && m_bOwnPD)
		delete m_pPD;

	m_pPD = pPD;
	m_bOwnPD = bMustDelete;
}

void CGXView::OnModifiedPrintDevice()
{
	// override this method and call GetDocument()->SetModifiedFlag()
	// if you maintain the printer settings in the document
}

/////////////////////////////////////////////////////////////////////////////
// CGXView diagnostics

#ifdef _DEBUG

void CGXView::AssertValid() const
{
	CView::AssertValid();

	if (m_bOwnPD)
		m_pPD->AssertValid();
}

void CGXView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);

	AFX_DUMP1(dc, "\nm_bOwnPD = ", (UINT)m_bOwnPD);
	AFX_DUMP0(dc, "\nm_pPD = ");
	dc << m_pPD;
}

#endif //_DEBUG

BEGIN_MESSAGE_MAP(CGXView, CView)
	//{{AFX_MSG_MAP(CGXView)
	ON_COMMAND(ID_FILE_PRINT_SETUP, OnFilePrintSetup)
	ON_MESSAGE(WM_GX_CHANGEDTAB, OnChangedTab)
	ON_MESSAGE(WM_GX_NEEDCHANGETAB, OnNeedChangeTab)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Initialization

void CGXView::OnInitialUpdate()
{
	// delete device object
	// this prevents problems in SDI environment
	if (m_bOwnPD) delete m_pPD;
	m_pPD = NULL;
	m_bOwnPD = FALSE;

	// if GetPrintDevice returns NULL,
	// MFC-Defaul-Settings are used.

	// If you want to have individual device settings
	// for the view, you should create an object
	// in your derived OnInitialUpdate() method.
	//
	// Example:
	// if (GetPrintDevice() == NULL)
	//    SetPrintDevice(new CGXPrintDevice);
	//
	
	CView::OnInitialUpdate();
}

/////////////////////////////////////////////////////////////////////////////
// Support for CSplitterWnd / CGXTabWnd

CSplitterWnd* AFXAPI CGXView::GetParentSplitter(const CWnd* pWnd, BOOL bAnyState)
{
	return (CSplitterWnd*) GXGetParentWnd(pWnd, RUNTIME_CLASS(CSplitterWnd), bAnyState);
}

CSplitterWnd* AFXAPI CGXView::GetParentDynamicSplitter(const CWnd* pWnd, BOOL bAnyState)
{
	CWnd* pSplitter = GetParentSplitter(pWnd, bAnyState);
	if (pSplitter && (pSplitter->GetStyle() & SPLS_DYNAMIC_SPLIT) != 0)
		return (CSplitterWnd*) pSplitter;
	return NULL;
}

#define _GXGetDlgCtrlID(hWnd)          ((UINT)(WORD)::GetDlgCtrlID(hWnd))

UINT AFXAPI CGXView::GetParentTabViewID(const CWnd* pWnd)
{
	UINT nID = _GXGetDlgCtrlID(pWnd->GetSafeHwnd());
	ASSERT(nID >= AFX_IDW_PANE_FIRST && nID < AFX_IDW_PANE_LAST);
	return nID-AFX_IDW_PANE_FIRST;
}

CScrollBar* CGXView::GetScrollBarCtrl(int nBar) const
{
	ASSERT(nBar == SB_HORZ || nBar == SB_VERT);
	if (GetStyle() & ((nBar == SB_HORZ) ? WS_HSCROLL : WS_VSCROLL))
	{
		// it has a regular windows style scrollbar (no control)
		return NULL;
	}

	// is it embedded in a CGXTabWnd or CGXRecordInfoWnd?
	CWnd* pParent = GXGetAppData()->GetSharedScrollbarParentWnd(this);

	if (pParent == NULL)
		return CView::GetScrollBarCtrl(nBar);            // no splitter

	// appropriate PANE id - look for sibling (splitter, or just frame)
	UINT nIDScroll;
	if (nBar == SB_HORZ)
		nIDScroll = AFX_IDW_HSCROLL_FIRST;
	else
		nIDScroll = AFX_IDW_VSCROLL_FIRST;

	// return shared scroll bars that are immediate children of splitter
	return (CScrollBar*)pParent->GetDlgItem(nIDScroll);
}

LRESULT CGXView::OnChangedTab(WPARAM /*wParam*/, LPARAM /*lParam*/)
{
	return 0;
}

LRESULT CGXView::OnNeedChangeTab(WPARAM /*wParam*/, LPARAM /*lParam*/)
{
	return TRUE;
}

LRESULT CGXView::OnCanActivate(WPARAM /*wParam*/, LPARAM /*lParam*/)
{
	// Please note:
	// activation is allowed when return value is 0
	// activation is disabled when return value is 1

	return 0;
}
