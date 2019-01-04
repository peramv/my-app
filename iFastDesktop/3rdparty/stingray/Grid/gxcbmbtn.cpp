///////////////////////////////////////////////////////////////////////////////
// gxcbmbtn.cpp : implementation of the CGXBitmapButton control
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
#include "grid\gxcore.h"
#endif

#ifndef _GXCTRLI_H_
#include "grid\gxctrli.h"
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXCBMBTN")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif


GRID_IMPLEMENT_CONTROL(CGXBitmapButton, CGXControl);

/////////////////////////////////////////////////////////////////////////////
// CGXBitmapButton

//@doc
//@mfunc
//@parm CGXGridCore* | pGrid | Pointer to the parent grid.
//@parm UINT | nIDBitmapResource | Specifies the resource ID number of the bitmap resource for a bitmap button's normal or "up" state. Required.
//@parm UINT | nIDBitmapResourceSel | Specifies the resource ID number of the bitmap resource for a bitmap button's selected or "down" state. May be 0.
//@parm UINT | nIDBitmapResourceFocus | Specifies the resource ID number of the bitmap resource for a bitmap button's focused state. May be 0.
//@rem
//Constructs a bitmap control object.<nl>
//<nl>
//You need to register this object in the grid with <mf CGXGridCore::RegisterControl>
//before you can use it in cells (see example).
//@ex
/*
This example shows how you can register a bitmap control in the grid: |

 // Push Button
RegisterControl(GX_IDS_CTRL_PUSHBTN,
      new CGXPushbutton(this));

 // Your .RC - file:

STRINGTABLE DISCARDABLE
BEGIN
      IDS_CTRL_BITMAP        "Welcome bitmap"
END

 // In OnInitialUpdate, you should pass a new instance of the object together with the string resource id to RegisterControl.

void CGridSampleView::OnInitialUpdate( )
{
   ...

   RegisterControl(IDS_CTRL_BITMAP,
      new CGXBitmapButton(this, IDB_WELCOME));
}
*/
//@xref <c CGXBitmapButton> <mf CGXGridCore::RegisterControl>  
CGXBitmapButton::CGXBitmapButton(CGXGridCore* pGrid,
		UINT nIDBitmapResource,
		UINT nIDBitmapResourceSel,
		UINT nIDBitmapResourceFocus)
		: CGXControl(pGrid)
{
	ASSERT(pGrid);
	ASSERT(nIDBitmapResource);

	AddChild(m_pButton = new CGXBitmapButtonChild(this));

	m_bInvertBorders = (nIDBitmapResourceFocus == 0);

	m_pButton->LoadBitmaps(MAKEINTRESOURCE(nIDBitmapResource),
		MAKEINTRESOURCE(nIDBitmapResourceSel),
		MAKEINTRESOURCE(nIDBitmapResourceFocus));
}

void CGXBitmapButton::OnInitChildren(ROWCOL nRow, ROWCOL nCol, const CRect& rect)
{
	FocusOnChild(m_pButton);
	m_pButton->SetRect(rect);

	// Unreferenced:
	nRow, nCol;
};

void CGXBitmapButton::InvertBorders(CDC* pDC, const CRect& r)
{
	if (m_bInvertBorders)
		CGXControl::InvertBorders(pDC, r);
}

void CGXBitmapButton::Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle)
{
	// Background and 3d frame
	DrawBackground(pDC, rect, style);

	CGXControl::Draw(pDC, rect, nRow, nCol, style, pStandardStyle);
}

CSize CGXBitmapButton::CalcSize(CDC* pDC, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle, BOOL bVert)
{
	// Unused: 
	pDC, nRow, nCol, pStandardStyle, bVert;

	return 	AddBorders(m_pButton->GetSize(), style);
}

