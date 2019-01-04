///////////////////////////////////////////////////////////////////////////////
// gxchsfrm.cpp : Function implementations for the workbook SDI Frame window
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

#ifdef _GXDLL
#undef AFXAPI_DATA
#define AFXAPI_DATA __based(__segname("_DATA"))
#endif

#include "grid\gxresrc.h"

#include "grid\gxtmpl.h"

#include "grid\gxtbmgr.h"

#include "grid\gxfradpt.h"

#include "grid\gxchsfrm.h"

#include "grid\gxmsg.h"

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXTABSER")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CGXWFrame

IMPLEMENT_DYNCREATE(CGXWFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CGXWFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CGXWFrame)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_GX_INITNEW, OnInitNew)
	ON_MESSAGE(WM_GX_INITFILE, OnInitFromFile)
END_MESSAGE_MAP()



/////////////////////////////////////////////////////////////////////////////
// CGXWFrame construction/destruction

CGXWFrame::CGXWFrame()
{
	SetWindow(this);
}

CGXWFrame::~CGXWFrame()
{
}

/////////////////////////////////////////////////////////////////////////////
// CGXWFrame diagnostics

#ifdef _DEBUG
void CGXWFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CGXWFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGXWFrame message handlers
BOOL CGXWFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	return HandleOnCreateClient(lpcs, pContext);
}

// default initialization for the tabs
LRESULT CGXWFrame::OnInitNew(WPARAM wParam, LPARAM lParam)
{
	return InitNewHandler(wParam, lParam);
}

// When initializing from a file
LRESULT CGXWFrame::OnInitFromFile(WPARAM wParam, LPARAM lParam)
{
	return InitFromFileHandler(wParam, lParam);
}

void CGXWFrame::InsertWorkSheet()
{
	InsertWorkSheetHandler();
}

void CGXWFrame::DeleteWorkSheet()
{
	DeleteWorkSheetHandler();
}

void CGXWFrame::CanInsertWorkSheet(CCmdUI* pUI)
{
	pUI->Enable(CanInsertWorkSheetHandler());
}

void CGXWFrame::CanDeleteWorkSheet(CCmdUI* pUI) 
{
	pUI->Enable(CanDeleteWorkSheetHandler());
}






