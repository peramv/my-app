///////////////////////////////////////////////////////////////////////////////
// gxdrgwnd.cpp : CGXDragLineWnd window
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

#ifndef _GXRESRC_H_
#include "grid\gxresrc.h"
#endif

#ifndef _GXCORE_H_
#include "grid\gxcore.h"
#endif

#ifndef _GXPRIV_H_
#include "grid\gxpriv.h"
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXCORDIM")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CGXDragLineWnd

CGXDragLineWnd::CGXDragLineWnd(CGXGridCore* pGrid)
{
	m_pGrid = pGrid;
	m_flags = 0;
	m_type = 0;
	m_nClientRC = 0;
}

BOOL CGXDragLineWnd::CreateWnd(CWnd* pParent)
{
	if (!CreateEx(
			0, GXGetAppData()->sComboClassName, NULL, WS_CHILD,
			0, 0, 1, 1,
			pParent->GetSafeHwnd(), NULL))
	{
		TRACE0("Failed to create window in CreateWnd\n");
		ASSERT(0);
		// ASSERTION-> Failed to create window
		// Did you register the windowclass with CGXGridCombo::RegisterClass? ->END

		return FALSE;
	}

	return TRUE;
};

BEGIN_MESSAGE_MAP(CGXDragLineWnd, CWnd)
	//{{AFX_MSG_MAP(CGXDragLineWnd)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CGXDragLineWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect rect;
	GetClientRect(rect);

	if (m_flags == 0)
	{
		CPen pen;
		pen.CreatePenIndirect(m_pen);
		CPen* pOldPen = dc.SelectObject(&pen);

		dc.MoveTo(rect.left, rect.top);
		dc.LineTo(rect.right-1, rect.bottom-1);

		dc.SelectObject(pOldPen);
	}
	else
	{
		m_pGrid->DrawGridLine(&dc, rect.left, rect.top, rect.Width(), rect.Height(), 
			m_type, m_nClientRC, m_flags);
	}
}

