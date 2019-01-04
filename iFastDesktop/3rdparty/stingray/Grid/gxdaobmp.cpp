///////////////////////////////////////////////////////////////////////////////
// gxdaobmp.cpp
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
// Authors: Stefan Hoenig, Daniel Jebaraj
//


#define _OG_EXPORT_IMPL

#include "stdafx.h"

/* compile this file only if DAO is supported
 */
#if _MFC_VER >= 0x0400 && !defined(_AFX_NO_DAO_SUPPORT)

#ifdef _GXDLL
// used for MFC 2.5 Extension DLL
	#undef AFXAPI_DATA
	#define AFXAPI_DATA __based(__segname("_DATA"))
#endif


#ifndef _GXDAO_H_
#include "grid\gxdao.h"
#endif

#ifndef __AFXTEMPL_H__
#include "afxtempl.h"
#endif

#ifndef _GX_MAN_H__
#include "grid\gxman.h"
#endif

#ifndef _GX_OLEVARIANT_USER_H__
#include "grid\gxoleusr.h"
#endif

#ifndef _GXDDIB_H_
#include "grid\gxddib.h"
#endif

#ifndef _GX_DAO_BMP_H__
#include "grid\gxdaobmp.h"
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif


#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXDAGRID")
#endif


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

GRID_IMPLEMENT_CONTROL(CGXDaoBitmap, CGXStatic);

/////////////////////////////////////////////////////////////////////////////
// CGXDaoBitmap

CGXDaoBitmap::CGXDaoBitmap(CGXGridCore* pGrid)
	: CGXStatic(pGrid)
{
}

void CGXDaoBitmap::Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle)
{
	ASSERT(pDC != NULL && pDC->IsKindOf(RUNTIME_CLASS(CDC)));
	// ASSERTION-> Invalid Device Context ->END
	ASSERT(nRow <= Grid()->GetRowCount() && nCol <= Grid()->GetColCount());
	// ASSERTION-> Cell coordinates out of range ->END
	ASSERT_VALID(pDC);

	CGXDaoGrid* pGrid = (CGXDaoGrid*) Grid();
	UINT nField = pGrid->GetFieldFromCol(nCol);

	TRACE1("Field %d\n", nField);

	DrawBackground(pDC, rect, style);

	if (rect.right <= rect.left || rect.Width() <= 1 || rect.Height() <= 1)
		return;

	
	const COleVariant* pVar = NULL;

	if(style.GetIncludeUserAttribute(GX_IDS_UA_DAOOLEBMP) )
		pVar = ( (CGXOleVarUserAttribute*)&style.GetUserAttribute(GX_IDS_UA_DAOOLEBMP))->GetOleVarValue();

	if (pVar)
	{
		// Draw bitmap

		// Don't subtract margins - only borders and 3d-frame
		// Therefore we call CGXControl::AddBorders
		CRect r = CGXControl::GetCellRect(nRow, nCol, rect, &style);

		DWORD dtAlign = style.GetHorizontalAlignment() | style.GetVerticalAlignment();
		
		HANDLE hBitmap = NULL;
		pGrid->OnGetBitmapHandleRowCol(nRow, nCol, hBitmap);

		hBitmap = CGXDataDib::Draw(pDC, *pVar , r, CGXDIB::none, (UINT) dtAlign);

		// you can override this function to get the bitmap handle and use it as needed
		// If you override this function and cache the bitmap you may find it useful to
		// handle OnGetBitmapHandleRowCol as well to return the cached value as an optimization
		BOOL bFree = pGrid->OnUseBitmapHandleRowCol(nRow, nCol, hBitmap);

		if(bFree)
			::GlobalFree(hBitmap);
		else
		{
			TRACE0("OG Info: Memory allocated for bitmap in CGXDaoBitmap::Draw is not freed\n");
			TRACE0("based on value returned from OnUseBitmapHandleRowCol.\n");
			TRACE0("You are responsible for freeing this with a call to GlobalFree\n");
		}

		// child Controls: spin-buttons, hotspot, combobox btn, ...
		CGXControl::Draw(pDC, rect, nRow, nCol, style, pStandardStyle);
	}
	else
		CGXStatic::Draw(pDC, rect, nRow, nCol, style, pStandardStyle);
}

#endif ///* compile this file only if DAO is supported
//_MFC_VER >= 0x0400 && !defined(_AFX_NO_DAO_SUPPORT)
