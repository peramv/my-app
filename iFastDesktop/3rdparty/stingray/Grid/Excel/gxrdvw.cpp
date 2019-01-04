///////////////////////////////////////////////////////////////////////////////
// ExcelReadView.cpp : implementation of the CGXExcelReadView class
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

#include "grid\gxrddoc.h"

#include "grid\gxrdvw.h"

#include "grid\gxexdef.h"

#include "grid\gxexhlp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CGXExcelReadWnd, CWnd)
GRID_IMPLEMENT_REGISTER(CGXExcelReadWnd, CS_DBLCLKS | GX_GLOBALCLASS, 0, 0, 0)

// CGXExcelReadView

IMPLEMENT_SERIAL(CGXExcelReadView, CGXGridView, 0)

BEGIN_MESSAGE_MAP(CGXExcelReadView, CGXGridView)
	//{{AFX_MSG_MAP(CGXExcelReadView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_MESSAGE(WM_GXINITIALUPDATE, ExcelFileInitialUpdate)
	ON_MESSAGE(WM_GXINITIALUPDATEDONE, ExcelFileInitialUpdateDone)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGXExcelReadView construction/destruction

CGXExcelReadView::CGXExcelReadView()
{
//	EnableFormulaEngine();
//	m_nExpressionValueType = GX_VALUE_EXPRESSION;
//	m_nClipboardFlags |= GX_DNDEXPRESSION;
}

CGXExcelReadView::~CGXExcelReadView()
{
}

BOOL CGXExcelReadView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CGXGridView::PreCreateWindow(cs);
}

int CGXExcelReadView::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	return CGXGridView::OnCreate(lpCreateStruct);
}
/////////////////////////////////////////////////////////////////////////////
// CGXExcelReadView drawing

void CGXExcelReadView::OnDraw(CDC* pDC)
{
	CGXExcelReadDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CGXGridView::OnDraw(pDC);
}

LRESULT CGXExcelReadView::ExcelFileInitialUpdate(WPARAM /*wParam*/, LPARAM /*lParam*/)
{
	OnExcelFileInitialUpdate();
	return 0;
}

LRESULT CGXExcelReadView::ExcelFileInitialUpdateDone(WPARAM wParam, LPARAM /*lParam*/)
{
	if(wParam == GX_EX_NEW_FILE)
		OnInitializeNewFile();

	OnExcelFileInitialUpdateDone();

	return 0;
}

void CGXExcelReadView::OnInitializeNewFile()
{
	// Initial defaults can be set here
	CGXProperties* pProp = GetParam()->GetProperties();

	pProp->SetDisplayVertLines(TRUE);
	pProp->SetDisplayHorzLines(TRUE);
	
	GXSetNewGridLineMode(TRUE);
}

void CGXExcelReadView::OnExcelFileInitialUpdateDone()
{
	SetFloatCellsMode(gxnFloatDelayEval);
	ChangeStandardStyle(CGXStyle().SetWrapText(FALSE));
	GetParam()->EnableUndo(TRUE);
	EnableHints();
	GetDocument()->SetModifiedFlag(FALSE);
}

void CGXExcelReadView::OnExcelFileInitialUpdate()
{
	// Get the index of this view
	int index = GetDocument()->GetIndex(this);
	
	ASSERT(index != -1);

	// Get the parameter object for this index
	CGXGridParam* pParam = GetDocument()->GetParam(index);

	SetParam(pParam, FALSE);

	// call the base class OnInitialUpdate
	CGXGridView::OnInitialUpdate();

	pParam->EnableUndo(FALSE);

	SetRowCount(GX_EX_DEFAULTSIZEROW);
	SetColCount(GX_EX_DEFAULTSIZECOL);
}

void CGXExcelReadView::OnInitialUpdate()
{
	// wait mode is TRUE when Excel file mode is on. In this case you should handle
	// OnExcelFileInitialUpdate
	if(GetDocument()->GetWaitMode())
		return;		

	CGXGridView::OnInitialUpdate();
}

BOOL CGXExcelReadView::OnPasteFromClipboard(const CGXRange& rg)
{
	return 	OnPasteFromClipboardImpl(rg);
}

BOOL CGXExcelReadView::OnCheckClipboardFormat()
{
	return 	OnCheckClipboardFormatImpl();
}

BOOL CGXExcelReadView::CopyRange(const CGXRangeList& selList)
{
	return CopyRangeImpl(selList);
}

/////////////////////////////////////////////////////////////////////////////
// CGXExcelReadView diagnostics

#ifdef _DEBUG
void CGXExcelReadView::AssertValid() const
{
	CGXGridView::AssertValid();
}

void CGXExcelReadView::Dump(CDumpContext& dc) const
{
	CGXGridView::Dump(dc);
}

CGXExcelReadDoc* CGXExcelReadView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGXExcelReadDoc)));
	return (CGXExcelReadDoc*)m_pDocument;
}
#endif //_DEBUG

///////////////////////////////////////////////////////////////////////////////////////////////
// CGXExcelReadWnd ////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CGXExcelReadWnd, CGXGridWnd)
	//{{AFX_MSG_MAP(CGXExcelReadWnd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CGXExcelReadWnd::CGXExcelReadWnd()
{
	// no implementation
}

CGXExcelReadWnd::~CGXExcelReadWnd()
{
	// no implementation
}

// Excel read/write support
void CGXExcelReadWnd::ReadExcelFile(const CString& strFileName, UINT index)
{
	// add code here to intialize from an Excel file
	CGXExcelWndDocAdapter docAdapt;
	docAdapt.SetGrid(this);
	
	OnPreExcelReadFile();

	try
	{
		docAdapt.ReadExcelFile(strFileName, index);
	}
	catch(egxExcelRWFlags flags)
	{
		GX_EX_FMT_TRACE("OG Pro Error: CGXExcelReaderImpl::ExcelWriteImpl.")
		CGXExRWErrorHandler::HandleError(flags);

		GX_THROW_LAST
	}
	catch(...)
	{
		GX_EX_FMT_MSG()
		GX_THROW_LAST
		return;
	}
	
	OnPostExcelReadFile();
}

void CGXExcelReadWnd::OnPreExcelReadFile()
{
	// add pre read code here
	CGXGridParam* pParam = GetParam();
	ASSERT(pParam != NULL);
	pParam->EnableUndo(FALSE);

	this->SetRowCount(GX_EX_DEFAULTSIZEROW);
	this->SetColCount(GX_EX_DEFAULTSIZECOL);
}

void CGXExcelReadWnd::OnPostExcelReadFile()
{
	// add post read code here...typically common Excel emulation code is added
	CGXGridParam* pParam = GetParam();
	pParam->EnableUndo(TRUE);
	SetFloatCellsMode(gxnFloatDelayEval);
	ChangeStandardStyle(CGXStyle().SetWrapText(FALSE));
}

void CGXExcelReadWnd::SaveExcelFile(const CString& strFileName)
{
	CGXExcelWndDocAdapter docAdapt;
	docAdapt.SetGrid(this);
	docAdapt.SaveExcelFile(strFileName);
}

BOOL CGXExcelReadWnd::OnPasteFromClipboard(const CGXRange& rg)
{
	return 	OnPasteFromClipboardImpl(rg);
}

BOOL CGXExcelReadWnd::OnCheckClipboardFormat()
{
	return 	OnCheckClipboardFormatImpl();
}

BOOL CGXExcelReadWnd::CopyRange(const CGXRangeList& selList)
{
	return CopyRangeImpl(selList);
}
