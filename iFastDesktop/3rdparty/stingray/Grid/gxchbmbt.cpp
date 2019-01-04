///////////////////////////////////////////////////////////////////////////////
// gxchbmbt.cpp : implementation of CGXBitmapButtonChild child class
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

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CGXBitmapButtonChild child class

// CGXBitmapButtonChild supports device independent bitmaps

//@doc
//@mfunc
//@parm CGXControl* | pComposite | Pointer to the parent control object.
//@rem
//Constructs a button child object.<nl>
//<nl>
//You should create and add the button child in the constructor of your <c CGXControl>-derived 
//class (see example).
//The rectangle for the button should be passed to the child object when the control's 
//<mf OnInitChildren> method is called.
//@ex
/* This example shows how you can add a child to your control: |
CBtnEdit::CBtnEdit(CGXGridCore* pGrid, UINT nID)
   : CGXEditControl(pGrid, nID)
{
   AddChild(m_pButton = new CGXBitmapButtonChild(this));

   VERIFY(m_pButton->LoadBitmaps(IDB_BITMAP1));

   m_sizeBtn = CSize(14,14);
}

void CBitmapBtnEdit::OnInitChildren(ROWCOL nRow, ROWCOL nCol, const CRect& rect)
{
   nRow, nCol;

   int nTop = (max(0, rect.Height() - m_sizeBtn.cy)) / 2;

   // init BitmapBtn button
   CRect rectBtn;
   rectBtn.IntersectRect(rect,
            CRect(rect.left+3,
               rect.top + nTop,
               rect.left+3+m_sizeBtn.cx,
               rect.top+ nTop + m_sizeBtn.cy)
            );

   m_pButton->SetRect(rectBtn);
*/
//@xref 
//<c CGXBitmapButtonChild> <mf CGXControl::CGXControl> <mf CGXControl::OnInitChildren> <mf CGXChild::SetRect> 
CGXBitmapButtonChild::CGXBitmapButtonChild(CGXControl* pComposite)
	: CGXButton(pComposite)
{
	m_hBitmap = NULL;
	m_hBitmapSel = NULL;
	m_hBitmapFocus = NULL;
}

CGXBitmapButtonChild::~CGXBitmapButtonChild()
{
	// delete old bitmaps (if present)
	if (m_hBitmap)
		::GlobalFree(m_hBitmap);
	if (m_hBitmapSel)
		::GlobalFree(m_hBitmapSel);
	if (m_hBitmapFocus)
		::GlobalFree(m_hBitmapFocus);
}

// LoadBitmaps will load in one, two, three or all four bitmaps
// returns TRUE if all specified images are loaded
//@doc
//@mfunc
//@parm LPCTSTR  | lpszBitmapResource | Points to the null-terminated string that contains the name of the bitmap resource for a bitmap button's normal or "up" state. Required.
//@parm LPCTSTR  | lpszBitmapResourceSel | Points to the null-terminated string that contains the name of the bitmap button's selected or "down" state. May be 0.
//@parm LPCTSTR  | lpszBitmapResourceFocus | Points to the null-terminated string that contains the name of the bitmap button's focused state. May be 0.
//@rdesc
//Nonzero if successful; otherwise 0.
//@rem
//Use this function to load bitmap images identified by their resource names or ID numbers
//@xref <c CGXBitmapButtonChild>
BOOL CGXBitmapButtonChild::LoadBitmaps(LPCTSTR lpszBitmapResource,
	LPCTSTR lpszBitmapResourceSel, LPCTSTR lpszBitmapResourceFocus)
{
	// delete old bitmaps (if present)
	if (m_hBitmap)
		::GlobalFree(m_hBitmap);
	if (m_hBitmapSel)
		::GlobalFree(m_hBitmapSel);
	if (m_hBitmapFocus)
		::GlobalFree(m_hBitmapFocus);

	m_hBitmap = NULL;
	m_hBitmapSel = NULL;
	m_hBitmapFocus = NULL;

	m_hBitmap = GXLoadResourceBitmap(lpszBitmapResource);
	if (!m_hBitmap)
	{
		TRACE0("Failed to load bitmap for normal image.\n");
		return FALSE;   // need this one image
	}
	BOOL bAllLoaded = TRUE;
	if (lpszBitmapResourceSel != NULL)
	{
		m_hBitmapSel = GXLoadResourceBitmap(lpszBitmapResourceSel);
		if (!m_hBitmapSel)
		{
			TRACE0("Failed to load bitmap for selected image.\n");
			bAllLoaded = FALSE;
		}
	}
	if (lpszBitmapResourceFocus != NULL)
	{
		m_hBitmapFocus = GXLoadResourceBitmap(lpszBitmapResourceFocus);
		if (!m_hBitmapFocus)
			bAllLoaded = FALSE;
	}

	m_bCanPress = (lpszBitmapResourceSel != NULL)
		|| (lpszBitmapResourceFocus != NULL);

	return bAllLoaded;
}

//@doc
//@mfunc
//@parm UINT | nIDBitmapResource | Specifies the resource ID number of the bitmap resource for a bitmap button's normal or "up" state. Required.
//@parm UINT | nIdBitmapResourceSel | Specifies the resource ID number of the bitmap resource for a bitmap button's selected or "down" state. May be 0.
//@parm UINT | nIDBitmapResourceFocus | Specifies the resource ID number of the bitmap resource for a bitmap button's focused state. May be 0.
//@rdesc Nonzero if successful; otherwise 0.
//@rem
//Use this function to load bitmap images identified by their resource names or ID numbers.
//@xref <c CGXBitmapButtonChild>
BOOL CGXBitmapButtonChild::LoadBitmaps(UINT nIDBitmapResource,
	UINT nIDBitmapResourceSel, UINT nIDBitmapResourceFocus)
{
	return LoadBitmaps(MAKEINTRESOURCE(nIDBitmapResource),
		MAKEINTRESOURCE(nIDBitmapResourceSel),
		MAKEINTRESOURCE(nIDBitmapResourceFocus));
}

// Draw the appropriate bitmap
void CGXBitmapButtonChild::Draw(CDC* pDC, BOOL bActive)
{
	// must have at least the first bitmap loaded before calling DrawItem
	ASSERT(m_hBitmap != NULL);     // required

	// use the main bitmap for up, the selected bitmap for down
	HANDLE hBitmap = m_hBitmap;

	UINT state = m_bPressed ? ODS_SELECTED : HasFocus() ? ODS_FOCUS : 0;
	if ((state & ODS_SELECTED) && m_hBitmapSel != NULL)
	{
		hBitmap = m_hBitmapSel;
	}
#ifndef _MAC
	else if ((state & ODS_FOCUS) && m_hBitmapFocus != NULL)
#else
  else if ((state & ODS_FOCUS) && m_hBitmapFocus != NULL  &&
		(GridWnd()->GetParent()->GetStyle() & DS_WINDOWSUI))
#endif
	{
		hBitmap = m_hBitmapFocus;   // third image for focused
	}

	CRect rect;
	rect.CopyRect(&m_rect);

	// Bitmap Info, width and height
	LPSTR lpDIB = (LPSTR) GlobalLock(hBitmap);

	BITMAPINFO* pBMI = (BITMAPINFO *) lpDIB;
	int nDibWidth = (int) min(rect.Width(), pBMI->bmiHeader.biWidth);
	int nDibHeight = (int) min(rect.Height(), pBMI->bmiHeader.biHeight);

	int sx = 0, sy = 0;

	if (pBMI->bmiHeader.biHeight > rect.Height())
		sy = (int) pBMI->bmiHeader.biHeight - rect.Height();

	// Look at color table size, and work out where image bits start
	DWORD dwColors;
	DWORD dwColorTableSize;
	dwColors = GXGetNumDIBColorEntries((LPBITMAPINFO)lpDIB);
	dwColorTableSize = dwColors * sizeof(RGBQUAD);
	LPSTR pBits = lpDIB + sizeof(BITMAPINFOHEADER) + dwColorTableSize;

	::StretchDIBits(pDC->GetSafeHdc(),
					rect.left,                // Destination x
					rect.top,                 // Destination y
					nDibWidth,                // Destination width
					nDibHeight,               // Destination height
					sx,                       // Source x
					sy,                       // Source y
					nDibWidth,                // Source width
					nDibHeight,               // Source height
					pBits,                    // Pointer to bits
					pBMI,                     // BITMAPINFO
					DIB_RGB_COLORS,           // Options
					SRCCOPY);                 // Raster operator code (ROP)

	GlobalUnlock(hBitmap);

	// unreferenced:
	bActive;
}

CSize CGXBitmapButtonChild::GetSize()
{
	CSize size = GetSize(m_hBitmap);
	CSize sizeSel = GetSize(m_hBitmapSel);
	CSize sizeFocus = GetSize(m_hBitmapFocus);

	return CSize(
		max(size.cx, max(sizeSel.cx, sizeFocus.cx)),
		max(size.cy, max(sizeSel.cy, sizeFocus.cy))
		);
}

CSize CGXBitmapButtonChild::GetSize(HANDLE hbm)
{
	CSize size(0,0);

	if (hbm)
	{
		CGXDIB dib;
		dib.Attach(hbm);
		size = dib.GetSize();
		dib.Detach();
	}

	return size;
}
