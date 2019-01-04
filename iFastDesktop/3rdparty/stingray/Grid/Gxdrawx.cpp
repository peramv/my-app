///////////////////////////////////////////////////////////////////////////////
// gxdrawx.cpp : drawing extensions and other tools
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
#ifndef _GXEXT_H_
#include "grid\gxext.h"
#endif

#ifndef _GXRESRC_H_
#include "grid\gxresrc.h"
#endif

#ifndef _GXSTATE_H_
#include "grid\gxstate.h"
#endif

#ifndef _GXDLL_H_
#include "grid\gxdll.h"
#endif

#include <math.h> // sin, cos

#include "RWUXTheme.h"

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXDRAWX")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

#ifndef _GXDLL
	// QA: 32120 - Wrapping with CThreadLocal.
	CThreadLocal<GX_DRAW_STATE> GXNEAR _gxDrawState;
#endif

#define NOELEMENTS(array) (sizeof(array)/sizeof(array[0]))

// instantiate CGXDrawingAndFormatting class on demand

CGXDrawingAndFormatting::~CGXDrawingAndFormatting()
{
}

CGXDrawingAndFormatting* AFXAPI GXDaFTools()
{
	if (GXGetAppData()->m_pDaFTools == NULL)
		GXGetAppData()->m_pDaFTools = new CGXDrawingAndFormatting;

	return GXGetAppData()->m_pDaFTools; 
}

void AFXAPI GXSetDaFTools(CGXDrawingAndFormatting* pTools)
{
	delete GXGetAppData()->m_pDaFTools;
	GXGetAppData()->m_pDaFTools = pTools;
}


// GXDeval and GXFormatText implemented in CGXDrawingAndFormattingEx

BOOL CGXDrawingAndFormatting::GXDeval(LPCTSTR s, double *d, unsigned* pImportFormat, unsigned* pImportPlaces)
{
	GX_CHECKIMP(GXGetAppData()->m_pNumberFormattingImp, "CGXDrawingAndFormatting::GXDeval");

	if (GXGetAppData()->m_pNumberFormattingImp)
		return GXGetAppData()->m_pNumberFormattingImp->GXDeval(s, d, pImportFormat, pImportPlaces);

	return FALSE;
}

CString CGXDrawingAndFormatting::GXFormatText(const CGXStyle& style, LPCTSTR pszValue, unsigned nValueType, CGXGridCore* pGrid, CGXControl* pControl )
{
	GX_CHECKIMP(GXGetAppData()->m_pNumberFormattingImp, "CGXDrawingAndFormatting::GXFormatText");

	if (GXGetAppData()->m_pNumberFormattingImp)
		return GXGetAppData()->m_pNumberFormattingImp->GXFormatText(style, pszValue, nValueType, pGrid, pControl);

	return pszValue ? pszValue : style.GetIncludeValue() ? style.GetValueRef() : _T("");
}

// supporting routines for device independent bitmaps

// Support for DDP/DIB Bitmaps

// GXLoadResourceBitmap
//
// Loads a DIB from the resource file and copies its contents
// to a memory handle.

HANDLE AFXAPI GXLoadResourceBitmap(HINSTANCE hInstance, LPCTSTR lpString)
{
	HRSRC  hRsrc;
	HGLOBAL hGlobal, hTemp;
	DWORD dwSize;
	HANDLE hBitmapFinal = NULL;
	LPBITMAPINFOHEADER  lpbi;
	LPVOID lpRes, lpNew;

	if ((hRsrc = FindResource(hInstance, lpString, RT_BITMAP)) != NULL)
	{
		// On Win32s, LoadResource does not return a true global memory handle. This
		// causes CreateDIBitmap to fail. To work around this problem, I use GlobalAlloc
		// to create a global memory handle.

		hTemp = LoadResource(hInstance, hRsrc);
		dwSize = SizeofResource(hInstance, hRsrc);
		lpRes = LockResource(hTemp);

		hGlobal = GlobalAlloc(GHND, dwSize);
		lpNew = GlobalLock(hGlobal);
		memcpy(lpNew, lpRes, (size_t) dwSize);
		UnlockResource(hTemp);
		FreeResource(hTemp);

		lpbi = (LPBITMAPINFOHEADER)lpNew;

		GlobalUnlock(hGlobal);
		hBitmapFinal = (HANDLE) hGlobal;
	}

	return (hBitmapFinal);
}

HANDLE AFXAPI GXLoadResourceBitmap(LPCTSTR lpString)
{
	// First, try resource handle
	HINSTANCE hInst = AfxFindResourceHandle(lpString, RT_BITMAP);
	HANDLE hBitmap = ::GXLoadResourceBitmap(hInst, lpString);

	// If failed, try instance handle (user dlls)
	if (hBitmap == 0)
		hBitmap = ::GXLoadResourceBitmap(AfxGetInstanceHandle(), lpString);

	return hBitmap;
}

// GXGetNumDIBColorEntries
//
// Returns the size of the color table in a DIB

DWORD AFXAPI GXGetNumDIBColorEntries(LPBITMAPINFO pBmpInfo)
{
	BITMAPINFOHEADER* pBIH;
	BITMAPCOREHEADER* pBCH;
	DWORD dwColors;
	int iBitCount;

	ASSERT(pBmpInfo);

	pBIH = &(pBmpInfo->bmiHeader);
	pBCH = (BITMAPCOREHEADER*) pBIH;

	// Start off by assuming the color table size from
	// the bit-per-pixel field.
	iBitCount = pBIH->biBitCount;

	switch (iBitCount) {
	case 1:
		dwColors = 2;
		break;
	case 4:
		dwColors = 16;
		break;
	case 8:
		dwColors = 256;
		break;
	default:
		dwColors = 0;
		break;
	}

	// the color table length is determined by the
	// biClrUsed field if the value in the field is nonzero.
	if (pBIH->biClrUsed != 0)
	{
		dwColors = pBIH->biClrUsed;
	}

	return dwColors;
}

// GXDrawTransparentBitmap
//
// This function lets you draw transparent bitmaps. The parameter
// cTransparentColor specifies the color for transparent pixels.
// All pixels in the bitmap which should be transparent should be
// marked with this color.
//
// The function was copied and adapated from knowledge base article Q79212
// Title: Drawing Transparent Bitmaps

void AFXAPI GXDrawTransparentBitmap(CDC* pDC, CBitmap* pBitmap, int xStart,
	int yStart, COLORREF cTransparentColor)
{
   CBitmap    bmAndBack, bmAndObject, bmAndMem, bmSave;
   CDC        dcMem, dcBack, dcObject, dcTemp, dcSave;

   dcTemp.CreateCompatibleDC(pDC);
   dcTemp.SelectObject(pBitmap);   // Select the bitmap

   BITMAP     bm;
   pBitmap->GetObject(sizeof(BITMAP), (LPSTR)&bm);

   CPoint     ptSize;
   ptSize.x = bm.bmWidth;            // Get width of bitmap
   ptSize.y = bm.bmHeight;           // Get height of bitmap
   dcTemp.DPtoLP(&ptSize, 1);      // Convert from device
									 // to logical points

   // Create some DCs to hold temporary data.
   dcBack.CreateCompatibleDC(pDC);
   dcObject.CreateCompatibleDC(pDC);
   dcMem.CreateCompatibleDC(pDC);
   dcSave.CreateCompatibleDC(pDC);

   // Create a bitmap for each DC. DCs are required for a number of
   // GDI functions.

   // Monochrome DC
   bmAndBack.CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);

   // Monochrome DC
   bmAndObject.CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);

   bmAndMem.CreateCompatibleBitmap(pDC, ptSize.x, ptSize.y);
   bmSave.CreateCompatibleBitmap(pDC, ptSize.x, ptSize.y);

   // Each DC must select a bitmap object to store pixel data.
   CBitmap* pbmBackOld   = dcBack.SelectObject(&bmAndBack);
   CBitmap* pbmObjectOld = dcObject.SelectObject(&bmAndObject);
   CBitmap* pbmMemOld    = dcMem.SelectObject(&bmAndMem);
   CBitmap* pbmSaveOld   = dcSave.SelectObject(&bmSave);

   // Set proper mapping mode.
   dcTemp.SetMapMode(pDC->GetMapMode());

   // Save the bitmap sent here, because it will be overwritten.
   dcSave.BitBlt(0, 0, ptSize.x, ptSize.y, &dcTemp, 0, 0, SRCCOPY);

   // Set the background color of the source DC to the color.
   // contained in the parts of the bitmap that should be transparent
   COLORREF cColor = dcTemp.SetBkColor(cTransparentColor);

   // Create the object mask for the bitmap by performing a BitBlt
   // from the source bitmap to a monochrome bitmap.
   dcObject.BitBlt(0, 0, ptSize.x, ptSize.y, &dcTemp, 0, 0,
		  SRCCOPY);

   // Set the background color of the source DC back to the original
   // color.
   dcTemp.SetBkColor(cColor);

   // Create the inverse of the object mask.
   dcBack.BitBlt(0, 0, ptSize.x, ptSize.y, &dcObject, 0, 0,
		  NOTSRCCOPY);

   // Copy the background of the main DC to the destination.
   dcMem.BitBlt(0, 0, ptSize.x, ptSize.y, pDC, xStart, yStart,
		  SRCCOPY);

   // Mask out the places where the bitmap will be placed.
   dcMem.BitBlt(0, 0, ptSize.x, ptSize.y, &dcObject, 0, 0, SRCAND);

   // Mask out the transparent colored pixels on the bitmap.
   dcTemp.BitBlt(0, 0, ptSize.x, ptSize.y, &dcBack, 0, 0, SRCAND);

   // XOR the bitmap with the background on the destination DC.
   dcMem.BitBlt(0, 0, ptSize.x, ptSize.y, &dcTemp, 0, 0, SRCPAINT);

   // Copy the destination to the screen.
   pDC->BitBlt(xStart, yStart, ptSize.x, ptSize.y, &dcMem, 0, 0,
		  SRCCOPY);

   // Place the original bitmap back into the bitmap sent here.
   dcTemp.BitBlt(0, 0, ptSize.x, ptSize.y, &dcSave, 0, 0, SRCCOPY);

   // Reset the memory bitmaps.
   dcBack.SelectObject(pbmBackOld);
   dcObject.SelectObject(pbmObjectOld);
   dcMem.SelectObject(pbmMemOld);
   dcSave.SelectObject(pbmSaveOld);

   // Memory DCs and Bitmap objects will be deleted automatically
}


/////////////////////////////////////////////////////////////////////////////
// GXLoadSysColorBitmap
//
// Function to load a bitmap changing it's colors to the current system color
// scheme.
//
BOOL AFXAPI GXLoadSysColorBitmap(CBitmap& bmp, LPCTSTR lpszName)
{
	// Table used to map default system colors onto the system color identifiers.
	static const DWORD sysColorMap[][2] =
	//	      b     g     r
	{{ RGB(0x00, 0x00, 0x00), COLOR_BTNTEXT },
	 { RGB(0x80, 0x80, 0x80), COLOR_BTNSHADOW },
	 { RGB(0xc0, 0xc0, 0xc0), COLOR_BTNFACE },
	 { RGB(0xff, 0xff, 0xff), COLOR_BTNHIGHLIGHT }};

	// Loads the bitmap changing the color table for the current color scheme
	ASSERT(bmp.m_hObject == NULL);

	HINSTANCE hInst = AfxFindResourceHandle(lpszName, RT_BITMAP);

	HRSRC hRsrc = ::FindResource(hInst, lpszName, RT_BITMAP);
	if(hRsrc == NULL)
		return FALSE;

	HGLOBAL hGlb = ::LoadResource(hInst, hRsrc);
	if(hGlb == NULL)
		return FALSE;

	LPBITMAPINFOHEADER lpBitmap = (LPBITMAPINFOHEADER)::LockResource(hGlb);
	if(lpBitmap == NULL)
	{
		::FreeResource(hGlb);
		return FALSE;
	}

	// Take a copy of the BITMAPINFOHEADER structure
	int nColorTableSize = 1 << lpBitmap->biBitCount;
	UINT nSize = (UINT)(lpBitmap->biSize + nColorTableSize * sizeof(RGBQUAD));
	LPBITMAPINFOHEADER lpBitmapInfo = (LPBITMAPINFOHEADER) new char[nSize];
	if(lpBitmapInfo == NULL)
	{
		::FreeResource(hGlb);
		return FALSE;
	}

	memcpy(lpBitmapInfo, lpBitmap, nSize);

	// Modifiy the color table for the current system colors.
	DWORD* pColorTable = (DWORD*)(((LPBYTE)lpBitmapInfo) + (UINT)lpBitmapInfo->biSize);
	for(int i=0; i < nColorTableSize; i++)
	{
		for(int j=0; j<NOELEMENTS(sysColorMap); j++)
		{
			if(pColorTable[i] == sysColorMap[j][0])
			{
				COLORREF newColor = ::GetSysColor((int)sysColorMap[j][1]);
				pColorTable[i] = RGB(GetBValue(newColor),
									 GetGValue(newColor),
									 GetRValue(newColor));
				break;
			}
		}
	}

	int nWidth  = (int)lpBitmapInfo->biWidth;		// Width of bitmap
	int nHeight = (int)lpBitmapInfo->biHeight;		// Height of bitmap

	// Create a new a bitmap and copy the bitmap over with the new color table.
	CWindowDC screenDC(NULL);
	CDC dc;
	if(!bmp.CreateCompatibleBitmap(&screenDC, nWidth, nHeight) ||
	   !dc.CreateCompatibleDC(NULL))
	{
		::FreeResource(hGlb);
		delete [] (char*)lpBitmapInfo; // QA: 31454, Added []
		return FALSE;
	}
	
	CBitmap* pBmpOld = (CBitmap*)dc.SelectObject(&bmp);

	LPBYTE lpBits = LPBYTE(lpBitmap+1);
#ifdef _WIN64
	lpBits += (1i64 << (lpBitmapInfo->biBitCount)) * sizeof(RGBQUAD);
#else
	// Use 1 for 32-bit builds
	lpBits += (1 << (lpBitmapInfo->biBitCount)) * sizeof(RGBQUAD);
#endif
	

	StretchDIBits(dc.GetSafeHdc(), 0, 0, nWidth, nHeight, 0, 0, nWidth, nHeight, 
				  lpBits, (LPBITMAPINFO)lpBitmapInfo, DIB_RGB_COLORS, SRCCOPY);

	dc.SelectObject(pBmpOld);

	::FreeResource(hGlb);
	delete [] (char*)lpBitmapInfo; // QA: 31454, Added []

	return TRUE;
}


/* Made the Black Color (0,0,1) instead of RGB(0,0,0). This is
nasty and not correct technically but the owner drawn comboboxes in
XP when themes are enabled behave differently. Since Black color is
RGB(0,0,0) and AddString casts back the pointer as NULL and hence the
CB_ADDSTRING message is not sent at all. This is causing the DrawItem
not to be called and hence black color is missing in the combobox. Causes
the indexes to go wrong also since black color is missing.*/

static COLORREF _GXPureVGAColorsArray[20] = {
		RGB(0,0,1),         // Black
		RGB(0,0,255),       // Bright blue
		RGB(0,255,0),       // Bright green
		RGB(0,255,255),     // Cyan
		RGB(255,0,0),       // Bright red
		RGB(255,0,255),     // Magenta
		RGB(255,255,0),     // Bright yellow
		RGB(255,255,255),   // White
		RGB(0,0,128),       // Dark blue
		RGB(0,128,0),       // Dark green
		RGB(0,128,128),     // Blue-green
		RGB(128,0,0),       // Brown
		RGB(128,0,128),     // Dark purple
		RGB(128,128,0),     // Olive
		RGB(128,128,128),   // Dark gray
		RGB(192,192,192),   // Light gray
		RGB(192,220,192),   // Pale green
		RGB(166,202,240),   // Light blue
		RGB(255,251,240),   // Off-white
		RGB(160,160,164),   // Medium gray
	};

// default interior brushes (8x8 bitmaps)

int _gxnPatternCount = GXNPATTERNS;

static WORD GXNEAR _GXPatternBitsArray[GXNPATTERNS][8] = {
		{ 0x44, 0x11, 0x44, 0x11, 0x44, 0x11, 0x44, 0x11 },
		{ 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa },
		{ 0xbb, 0xee, 0xbb, 0xee, 0xbb, 0xee, 0xbb, 0xee },
		{ 0xee, 0xff, 0xbb, 0xff, 0xee, 0xff, 0xbb, 0xff },
		{ 0xff, 0xff, 0xee, 0xff, 0xff, 0xff, 0xbb, 0xff },
		{ 0xfb, 0xff, 0xbf, 0xff, 0xfa, 0xff, 0xaf, 0xff },
		{ 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00 },
		{ 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc },
		{ 0x55, 0xcc, 0x99, 0x44, 0x55, 0xcc, 0x99, 0x44 },
		{ 0x44, 0x99, 0xcc, 0x55, 0x44, 0x99, 0xcc, 0x55 },
		{ 0x55, 0x55, 0x99, 0x99, 0x55, 0x55, 0x99, 0x99 },
		{ 0x55, 0x00, 0x99, 0x00, 0x55, 0x00, 0x99, 0x00 },

		// frequent (2 thin lines per 8-bit pattern)
		{ 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff },   /* --- */
		{ 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xdd },   /* ||| */
		{ 0xee, 0xdd, 0xbb, 0x77, 0xee, 0xdd, 0xbb, 0x77 },   /* /// */
		{ 0x77, 0xbb, 0xdd, 0xee, 0x77, 0xbb, 0xdd, 0xee },   /* \\\ */
		{ 0xee, 0x00, 0xee, 0xee, 0xee, 0x00, 0xee, 0xee },   /* +++ */

		{ 0xee, 0x55, 0xbb, 0x55, 0xee, 0xbb, 0x55, 0xee },

		// dotted (1 dotted line per 8-bit pattern)
		{ 0x88, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff },   /* --- */
		{ 0xfe, 0xff, 0xfe, 0xff, 0xfe, 0xff, 0xfe, 0xff },   /* ||| */
		{ 0xfe, 0xff, 0xfb, 0xff, 0xef, 0xff, 0xbf, 0xff },   /* /// */
		{ 0xf7, 0xff, 0xfd, 0xff, 0x7f, 0xff, 0xdf, 0xff },   /* \\\ */
		{ 0x88, 0xff, 0xfe, 0xff, 0xfe, 0xff, 0xfe, 0xff },   /* +++ */

		// thin (1 thin line per 8-bit pattern)
		{ 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff },   /* --- */
		{ 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe },   /* ||| */
		{ 0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xbf, 0x7f },   /* /// */
		{ 0xf7, 0xfb, 0xfd, 0xfe, 0x7f, 0xbf, 0xdf, 0xef },   /* \\\ */
		{ 0x00, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe },   /* +++ */

		// bold (1 thick line per 8-bit pattern)
		{ 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff },   /* --- */
		{ 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3 },   /* ||| */
		{ 0xf3, 0xf9, 0xfc, 0x7e, 0x3f, 0x9f, 0xcf, 0xe7 },   /* /// */
		{ 0xe7, 0xcf, 0x9f, 0x3f, 0x7e, 0xfc, 0xf9, 0xf3 },   /* \\\ */
		{ 0x00, 0x00, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3, 0xf3 },   /* +++ */

// Compatible patterns for pen styles (horizontal lines)
		{ 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11 }, // 1: PS_DASH        /* ------- */
		{ 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55 }, // 2: PS_DOT         /* ....... */
		{ 0xb1, 0xb1, 0xb1, 0xb1, 0xb1, 0xb1, 0xb1, 0xb1 }, // 3: PS_DASHDOT     /* _._._._ */
		{ 0x51, 0x51, 0x51, 0x51, 0x51, 0x51, 0x51, 0x51 }, // 4: PS_DASHDOTDOT  /* _.._.._ */

// Compatible patterns for pen styles (vertical lines)
		{ 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0xff }, // 1: PS_DASH        /* ------- */
		{ 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff }, // 2: PS_DOT         /* ....... */
		{ 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff }, // 3: PS_DASHDOT     /* _._._._ */
		{ 0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff }, // 4: PS_DASHDOTDOT  /* _.._.._ */
	};

const CBitmap* CGXDrawingAndFormatting::GXGetPatternBitmap(int n)
{
	ASSERT(n >= 0 && n < _gxnPatternCount);

	if (GXGetDrawState()->m_abmPatternArray[n].GetSafeHandle() == 0)
	{
		// create brush pattern, if needed
		VERIFY(GXGetDrawState()->m_abmPatternArray[n]
			.CreateBitmap(8,8,1,1,(const void*)_GXPatternBitsArray[n]));
	}

	return &GXGetDrawState()->m_abmPatternArray[n];
}

int AFXAPI GXFindColor(COLORREF rgbColor)
{
	for (int i = 0; i < 20; i++)
	{
		if (rgbColor == _GXPureVGAColorsArray[i])
			return i;
	}

	return -1;
}

COLORREF AFXAPI GXGetVGAColor(int i)
{
	ASSERT(i >= 0 && i < 20);
	// ASSERTION-> index out of range! ->END

	return _GXPureVGAColorsArray[i];
}

void AFXAPI GXSetVGAColor(int i, COLORREF rgbColor)
{ 
	ASSERT(i >= 0 && i < 20); // ASSERTION-> index out of range! ->END 
	_GXPureVGAColorsArray[i] = rgbColor; 
} 

void AFXAPI GXInvertRect(CDC* pDC, const CRect& rect, const CRect& rectClip)
{
	CRect r;
	if (rectClip.IsRectEmpty())
		r = rect;
	else if (!r.IntersectRect(rect, rectClip))
		return;

	pDC->InvertRect(r);
}

void AFXAPI GXPatB(CDC* pDC,int x,int y,int dx,int dy, COLORREF rgb)
{
	// Fill rectangle with color
	RECT    rc;

	rc.left   = x;
	rc.top    = y;
	rc.right  = x + dx;
	rc.bottom = (y + dy);

	COLORREF rgbOld = pDC->SetBkColor(GXGETCOLOR(rgb));
	pDC->ExtTextOut(0,0,ETO_OPAQUE,&rc,_T(""),0,NULL);
	pDC->SetBkColor(rgbOld);
}

void AFXAPI GXPatB(CDC* pDC,const CRect& rc, COLORREF rgb)
{
	// Fill rectangle with color
	COLORREF rgbOld = pDC->SetBkColor(GXGETCOLOR(rgb));
	pDC->ExtTextOut(0,0,ETO_OPAQUE,&rc,_T(""),0,NULL);
	pDC->SetBkColor(rgbOld);
}

void AFXAPI GXDrawInset(CDC* pDC, int x, int y, int dx, int dy, COLORREF rgbFace)
{
	// face
	GXPatB(pDC, x, y, dx, dy, rgbFace);

	// edge
	GXDrawEdge(pDC, CRect(x, y, x+dx, y+dy), BDR_SUNKENOUTER | BDR_SUNKENINNER);
}

void AFXAPI GXDrawButton(CDC* pDC, int x, int y, int dx, int dy, BOOL bPressed, COLORREF rgbFace)
{
	// face
	GXPatB(pDC, x, y, dx, dy, rgbFace);

	// edge
	GXDrawEdge(pDC, CRect(x, y, x+dx, y+dy),
		bPressed
		?BDR_SUNKENOUTER | BDR_SUNKENINNER
		:BDR_RAISEDOUTER | BDR_RAISEDINNER);
}

void AFXAPI GXDrawBlankButton(CDC* pDC, int x, int y, int dx, int dy, BOOL bPressed)
{
	// draw button with face color
	GXDrawButton(pDC, x, y, dx, dy, bPressed, GXGetSysData()->GetSysColor(COLOR_BTNFACE));
}

void AFXAPI GXDrawPushButton(CDC* pDC, int x, int y, int dx, int dy, UINT nState, LPCTSTR lpszString)
{
	CRect rect(x, y, x+dx-1, y+dy-1);

	if (nState & GX_BTNPRESSED)
		GXDrawEdge(pDC, rect, BDR_SUNKENOUTER | BDR_SUNKENINNER);
	else
		GXDrawEdge(pDC, rect, BDR_RAISEDOUTER | BDR_RAISEDINNER);

	CRect faceRect(rect.left+1, rect.top+1, rect.right-2, rect.bottom-2);
	if (nState & GX_BTNPRESSED)
		faceRect += CPoint(1,1);

	GXDrawFocusText(pDC, faceRect, nState&GX_BTNFOCUS, lpszString, DT_WORDBREAK);
}

void CGXDrawingAndFormatting::GXDrawFocusText(CDC* pDC, CRect rect, BOOL bFocus, LPCTSTR lpszString, UINT nFormat)
{
	CRect faceRect = rect;
	CRect textRect = rect;
	pDC->SetBkMode(TRANSPARENT);

	if (lpszString && *lpszString)
		pDC->DrawText(lpszString, -1,
			textRect,
			nFormat|DT_CALCRECT);
	else
		pDC->DrawText(_T("--"), -1,
			textRect,
			nFormat|DT_CALCRECT);

	textRect.right += 3;
	textRect.left -= 3;

	CRect centerRect;

	centerRect.top = faceRect.top + (faceRect.Height()-textRect.Height())/2;
	centerRect.bottom = centerRect.top + textRect.Height();
	centerRect.left = faceRect.left + (faceRect.Width()-textRect.Width())/2;
	centerRect.right = centerRect.left + textRect.Width();

	centerRect &= faceRect;

	if (lpszString)
		GXDrawTextLikeMultiLineEdit(pDC, lpszString, -1,
			centerRect, nFormat|DT_CENTER);

	if(!RWIsOfc2003StyleEnabled() && !RWIsVistaClassicStyleEnabled())
	{
		if (bFocus)
		{
			COLORREF rgbShadow = GXGetSysData()->GetSysColor(COLOR_BTNSHADOW);
			GXPatB(pDC, centerRect.left+2, centerRect.top, centerRect.Width()-3, 1, rgbShadow);
			GXPatB(pDC, centerRect.left+2, centerRect.bottom, centerRect.Width()-3, 1, rgbShadow);
			GXPatB(pDC, centerRect.left, centerRect.top+2, 1, centerRect.Height()-3, rgbShadow);
			GXPatB(pDC, centerRect.right, centerRect.top+2, 1, centerRect.Height()-3, rgbShadow);
		}
	}
}

void AFXAPI GXDrawEdge(CDC* pDC, CRect rect, UINT nEdge, BOOL bAdjust)
{
#if (WINVER >= 0x400) && !defined(_MAC) && !defined(_UNIX_)
	pDC->DrawEdge(rect, nEdge, bAdjust?BF_ADJUST:BF_RECT);
#else
	if (bAdjust)
	{
		if (nEdge&(BDR_RAISEDOUTER|BDR_SUNKENOUTER))
		{
			//  rect.InflateRect(1,1);
			rect.left--;
			rect.top--;
			rect.right++;
			rect.bottom++;
		}

		if (nEdge&(BDR_RAISEDINNER|BDR_SUNKENINNER))
		{
			//  rect.InflateRect(1,1);
			rect.left--;
			rect.top--;
			rect.right++;
			rect.bottom++;
		}
	}

	// face color
	COLORREF rgbFace    = GetSysColor(COLOR_BTNFACE);
	COLORREF rgbShadow  = GetSysColor(COLOR_BTNSHADOW);
	COLORREF rgbHilite = GetSysColor(COLOR_BTNHIGHLIGHT);
	COLORREF rgbFrame   = GetSysColor(COLOR_WINDOWFRAME);

	if (nEdge&BDR_RAISEDOUTER)
		GXDraw3dFrame(pDC, rect.left, rect.top, rect.right-1, rect.bottom-1, 1,
			rgbHilite, rgbFrame);
	else if (nEdge&BDR_SUNKENOUTER)
		GXDraw3dFrame(pDC, rect.left, rect.top, rect.right-1, rect.bottom-1, 1,
			rgbFrame, rgbHilite);
	if (nEdge&(BDR_RAISEDOUTER|BDR_SUNKENOUTER))
	{
		// rect.DeflateRect(1,1);
		rect.left++;
		rect.top++;
		rect.right--;
		rect.bottom--;
	}
	
	if (nEdge&BDR_RAISEDINNER)
		GXDraw3dFrame(pDC, rect.left, rect.top, rect.right-1, rect.bottom-1, 1,
			rgbFace, rgbShadow);
	else if (nEdge&BDR_SUNKENINNER)
		GXDraw3dFrame(pDC, rect.left, rect.top, rect.right-1, rect.bottom-1, 1,
			rgbShadow, rgbFace);
#endif
}

void AFXAPI GXDraw3dFrame(CDC* pDC, const CRect &rc, int w, COLORREF rgbTopLeft, COLORREF rgbBottomRight)
{
	GXDraw3dFrame(pDC, rc.left, rc.top, rc.right-1, rc.bottom-1, w,
			rgbTopLeft, rgbBottomRight);
}

void CGXDrawingAndFormatting::GXDraw3dFrame(CDC* pDC, int x0, int y0, int x1, int y1, int w,
			  COLORREF rgbTopLeft, COLORREF rgbBottomRight)
{
	COLORREF rgbOld = pDC->GetBkColor();
	CRect rc;

	for (int i = 0; i < w; i++)
	{
		pDC->SetBkColor(rgbTopLeft);

		// Top
		rc.SetRect(x0, y0, x1, y0+1);
		pDC->ExtTextOut(0,0,ETO_OPAQUE,&rc,_T(""),0,NULL);

		// Left
		rc.SetRect(x0, y0, x0+1, y1);
		pDC->ExtTextOut(0,0,ETO_OPAQUE,&rc,_T(""),0,NULL);

		pDC->SetBkColor(rgbBottomRight);

		// Bottom
		rc.SetRect(x0, y1, x1+1, y1+1);
		pDC->ExtTextOut(0,0,ETO_OPAQUE,&rc,_T(""),0,NULL);

		// Right
		rc.SetRect(x1, y0, x1+1, y1);
		pDC->ExtTextOut(0,0,ETO_OPAQUE,&rc,_T(""),0,NULL);

		if (i < w-1)
		{
			x0++;
			y0++;
			x1--;
			y1--;
		}
	}

	pDC->SetBkColor(rgbOld);
}

int CGXDrawingAndFormatting::GXComputeLineBreaks(CDC* pDC,
	LPCTSTR sz,
	int nCount,     // nCount = size of string in bytes
	LPRECT rc,
	UINT nFormat,
	int* LineBreaks,
	int* LineLengths,
	int nMaxBreaks)
{
	BOOL bWrapText = nFormat & DT_WORDBREAK;

	CRect rect = rc;
	int nRight = CRect(rc).Width()+1;
	int nLineBreaks = 0;

	TEXTMETRIC    tm;
	pDC->GetTextMetrics(&tm);
	int dyHeight = tm.tmHeight + tm.tmExternalLeading;

	int nLine;
	if ((rect.Height()-dyHeight/3) <= dyHeight)
		nLine = 0;
	else
		nLine = max(0, rect.Height()/dyHeight);

	if (nCount == -1)
		nCount = (int)_tcslen(sz);

	CSize size;
	int n = 0;

	// SRSTUDIO-1688 Reduce the number of breaks before starting while loop.
	nMaxBreaks--;

	while (n < nCount)
	{
		int nWords = 0;
		int nIndex = n, nIndexLastWord;
		int nLineLength, nLineLengthLastWord;

		nLineLength = 0;

		do {
			nLineLengthLastWord = nLineLength;

			nIndexLastWord = nIndex;

			// skip blanks (before word)
			while (nIndex < nCount && sz[nIndex] == _T(' '))
			{
				nIndex++;
				nLineLength++;
			}

			// regular characters
			while (nIndex < nCount && _tcschr(_T(" \r\n"), sz[nIndex]) == NULL)
			{
				nLineLength += (int)_tclen( sz + nIndex );
				nIndex += (int)_tclen( sz + nIndex );
			}

			// end of word
			size = pDC->GetTextExtent(sz+n, nLineLength);

			nWords++;

			// skip blanks (after word)
			while (nIndex < nCount && sz[nIndex] == _T(' '))
			{
				nIndex++;
				nLineLength++;
			}

			// repeat until the word does not fit into the line
		} while ( size.cx <= nRight
			 && nIndex < nCount && sz[nIndex] != _T('\r') && sz[nIndex] != _T('\n'));

		rect.top += size.cy + 1;
		LineBreaks[nLineBreaks] = n;

		if (sz[nIndex] == _T('\r') && size.cx <= nRight)
		{
			// manual line feed
			size = pDC->GetTextExtent(sz+n, nLineLength);
			LineLengths[nLineBreaks++] = nLineLength;

			if (sz[n = nIndex+1] == _T('\n'))
				n++;

			if (n == nCount)
			{
				LineBreaks[nLineBreaks] = n;
				LineLengths[nLineBreaks++] = 0;
			}
		}
		else if (sz[nIndex] == _T('\n') && size.cx <= nRight)
		{
			// manual line feed
			size = pDC->GetTextExtent(sz+n, nLineLength);
			LineLengths[nLineBreaks++] = nLineLength;
			n = nIndex+1;

			if (n == nCount)
			{
				LineBreaks[nLineBreaks] = n;
				LineLengths[nLineBreaks++] = 0;
			}
		}
		else if (size.cx <= nRight)
		{
			// rest of text completly fits into the line
			LineLengths[nLineBreaks++] = nLineLength;
			break;
		}
		else if (nWords > 1 && nLine > 0 && bWrapText)
		{
			// several words, cut last word
			LineLengths[nLineBreaks++] = nLineLengthLastWord;
			n = nIndexLastWord;
		}
		else
		{
			// only one word or only one line
			nIndex = n;
			nLineLength = 0;
			size.cx = 0;

			do
			{
				nLineLength += (int)_tclen( sz + nIndex );
				nIndex += (int)_tclen( sz + nIndex );
				size = pDC->GetTextExtent(sz+n, nLineLength + 1);
			}
			while (nIndex < nCount && size.cx <= nRight);

			LineLengths[nLineBreaks++] = nLineLength;
			n = nIndex;
		}

		// next line
		if (nLine-- == 0 || nLineBreaks == nMaxBreaks || !bWrapText)
			break;
	}

	// check vertical alignment
	if (rect.top < rect.bottom)
	{
		if (nFormat & DT_VCENTER)
			rc->top = rc->top + (rc->bottom-rect.top+tm.tmExternalLeading)/2;
		else if (nFormat & DT_BOTTOM)
			rc->top = rc->top + (rc->bottom-rect.top);
	}

	return nLineBreaks;
}

int CGXDrawingAndFormatting::GXGetMultiLineTextBreakCount(CDC* pDC, LPCTSTR lpszString, int nCount, CRect rc, UINT nFormat)
{
	CRect rect = rc;
	int LineBreaks[32], LineLengths[32];

	int nLineBreaks = GXComputeLineBreaks(pDC,
		lpszString, nCount, &rect, nFormat, LineBreaks, LineLengths, 32);

	return nLineBreaks;
}                      


int CGXDrawingAndFormatting::GXDrawTextLikeMultiLineEditEx(CDC* pDC, LPCTSTR lpszString, int nCount, CRect rc, UINT nFormat, LPRECT lpClipRect, gxEllipseType gxFormatEx /* = gxNoEllipse */)
{
	// call the default if no special format is used
	if (gxFormatEx == gxNoEllipse)
		return GXDrawTextLikeMultiLineEdit(pDC, lpszString, nCount, rc, nFormat, lpClipRect);
	
	// this is the exact same code as GXDrawTextLikeMultiLineEdit with a few additions
	
	CRect rect = rc;
	int LineBreaks[32], LineLengths[32];

	if (nCount == -1)
		nCount = (int)_tcslen(lpszString);

	if (lpClipRect == NULL)
		lpClipRect = &rect;

#ifdef _DEBUG
	CRect _r;
	ASSERT(rc.IsRectEmpty() || _r.IntersectRect(rc, lpClipRect) && _r == rc);
	// ASSERTION-> lpClipRect must be bigger than rc. Please make sure
	// in your calling function that the boundaries of the clipping rectangle
	// are not inside the prefered drawing rectangle (rc). ->END
#endif

/*
	Uncomment these lines if vertical text should work for all cells
#if _MFC_VER >= 0x0400                 
	LOGFONT lf;
	pDC->GetCurrentFont()->GetObject(sizeof(lf), &lf);

	// draw vertical text
	if (lf.lfOrientation != 0 && lf.lfOrientation == lf.lfEscapement)
		return GXDrawRotatedText(pDC, lpszString, nCount, rc, nFormat, lf.lfOrientation, lpClipRect);
#endif
*/

	// regular text
	int nLineBreaks = GXComputeLineBreaks(pDC,
		lpszString, nCount, &rect, nFormat, LineBreaks, LineLengths, 32);

	TEXTMETRIC    tm;
	pDC->GetTextMetrics(&tm);
	int dyHeight = tm.tmHeight + tm.tmExternalLeading;

	// CEdit uses different height for larger fonts.
	// This value has been determined by experiment. I simply
	// compared the results by using different values and
	// 20 seemed to work fine.
	if (dyHeight >= 20) 
		dyHeight--;

	for (int nBreak = 0; nBreak < nLineBreaks; nBreak++)
	{
		int nLeft = -1;
		LPCTSTR pszLine = lpszString+LineBreaks[nBreak];
		int nBytes = LineLengths[nBreak];
		CSize size(0,0);
		BOOL bNeedClip = FALSE;
		CRect rectOldClip;

		// Implement some special clipping when text is
		// only one character. Let's show as much as possible
		// of this one character if it must be clipped
		// (possibly also shift it to the left boundary of
		// the clipping rectangle).
		if (nBytes == (int) _tclen(pszLine))
		{
			size = pDC->GetTextExtent(pszLine, nBytes);

			// clip when only one visible char does not
			// fit into clipping rectangle
			if (size.cx > ((CRect*) lpClipRect)->Width())
			{
				bNeedClip = TRUE;
				nLeft = lpClipRect->left;
			}
			// adjust left so that the char fits into the
			// clipping rectangle
			else if (size.cx > rect.Width())
				nLeft = min(lpClipRect->right - size.cx, rect.left);
		}

		// Adjust left so that text will be correctly aligned
		if (nLeft == -1 && (nFormat & (DT_CENTER|DT_RIGHT)) > 0)
		{
			if (size.cx == 0)
				size = pDC->GetTextExtent(pszLine, nBytes);

			if (nFormat & DT_RIGHT)
				nLeft = max(rect.left, rect.right-size.cx);
			else if (nFormat & DT_CENTER)
				nLeft = max(rect.left, rect.left+(rect.right-rect.left-size.cx)/2);
		}

		// default is to use the left of the preffered rectangle
		if (nLeft == -1)
			nLeft = rect.left;

		if (bNeedClip)
		{
			BOOL bCanClip = TRUE;
			
			// Metafiles don't support SelectClipRgn!
			if (pDC->IsKindOf(RUNTIME_CLASS(CMetaFileDC)) && !pDC->IsPrinting())
				bCanClip = FALSE;

			// 16-Bit device drivers don't support SelectClipRgn!
			if (GXGetAppData()->bWin31 && pDC->IsPrinting())
				bCanClip = FALSE;

			if (bCanClip)
			{
				// It's an expensive operation but there is no way
				// around clipping.
				pDC->GetClipBox(rectOldClip);
				pDC->IntersectClipRect(lpClipRect);

				// ELLIPSE CODE->
				if (gxFormatEx == gxPoundEllipse &&	/* Use #### */ 
					nFormat & DT_SINGLELINE			/* Single line cells only */)
				{
					CString strPound(_T("#"));
					pDC->TextOut(nLeft, rect.top, strPound);
					//pDC->DrawText(strPound, rect, nFormat);
				}
				else	
				// ELLIPSE CODE <-

				pDC->TextOut(nLeft, rect.top, pszLine, nBytes);
				//pDC->DrawText(pszLine, nBytes, rect, nFormat);

				// restore original clipping region
				pDC->SelectClipRgn(NULL);
				pDC->IntersectClipRect(rectOldClip);
			}
			// else
				// there is no way that we can draw that character
				// without messing up the other drawing. So, the
				// compromise is not to print that half char
		}
		else

// ELLIPSE CODE ->
		// Give feedback to user that data in the cell is clipped.  Check 
		// the user attribute flag, GX_IDS_UA_ELLIPSISTYPE, to determine
		// if this needs to be drawn with an ellipsis, ####, or no 
		// feedback at all.

		// Check if the ellipses flag is set and whether it is appropriate
		// to test for ellipses
		if ((dyHeight + 3 * tm.tmAscent / 4 > rect.Height() ||	// Next line is not visible OR
			nLineBreaks == nBreak + 1) &&						// Current line is last line AND
			(gxFormatEx ==  gxDotEllipse))						// Ellipsis flag is set
		{
			CString sLine(pszLine);
			int nLineChars = sLine.GetLength();
			if ( nBytes > 1  &&  nLineChars > nBytes )
			{
				// Number of '.' to append to end of string
				int nEllipsisSize = 3;

				// Try trimming the string (which starts at the first
				// character of the current line and ends with the end
				// of the cell's text) to the length determined in 
				// GXComputeLineBreaks(...).  This may be enough space to 
				// append the ellipsis.
				sLine = sLine.Left( nBytes ) +	 _T("...");
				CSize sizeLine = pDC->GetTextExtent(sLine, nBytes + nEllipsisSize );

				// If the string still isn't short enough, continue to lop off 
				// characters, one at a time, until the string is short enough
				// to append the ellipsis.  If the string is shortened to 1
				// character (not including the ellipsis), then start lopping
				// off periods from the ellipsis.  At a bare minimum, this 
				// chunk of code will display the first character in the string.
				// Note: The clipping section above will prevent the method 
				// from reaching this code if the first character can't be 
				// drawn completely.
				while (sizeLine.cx > rect.Width()  && nBytes + nEllipsisSize > 1)
				{
					if (nBytes == 1)
					{
						// Only one character left!  Don't lop it off -> always 
						// show at least one character.  Try using a smaller
						// version of the ellipsis.
						nEllipsisSize--;

						switch (nEllipsisSize)
						{
						case 2:
							// Two periods
							sLine = sLine.Left(1) + _T("..");
							break;
						case 1:
							// One periods
							sLine = sLine.Left(1) + _T(".");
							break;
						case 0:
							// No periods
							sLine =	sLine.Left(1);
							break;
						default:
							// This should never happen!
							ASSERT( FALSE );
						}
					}
					else
					{
						// OK to lop off another character
						sLine = sLine.Left(--nBytes) + _T("...");
					}

					// Get the new line length for next cycle
					sizeLine = pDC->GetTextExtent(sLine, nBytes + nEllipsisSize );

				} // while (...)

				// String has been modified to display some version of the
				// ellipsis and is now short enough to fit in the cell.
				// Draw it!
				pDC->TextOut(nLeft, rect.top, sLine, nBytes + nEllipsisSize);
				//pDC->DrawText(sLine, nBytes + nEllipsisSize, rect, nFormat);

			} // if (...)

			else
			{
				// Ellipse isn't necessary; the entire string fits
				pDC->TextOut(nLeft, rect.top, pszLine, nBytes);
				//pDC->DrawText(pszLine, nBytes, rect, nFormat);
			}

		}

		// Check if we should display the text as ####.  This is only
		// valid when the cell is single line.  It doesn't make sense
		// to display #### for multiline cells.
		else 
		if (_tcslen(pszLine) > (unsigned int)nBytes &&	// Text is too long AND
			(gxFormatEx == gxPoundEllipse) &&			// Pound flag is set AND
			nFormat & DT_SINGLELINE)					// Cell is single line
		{
			// Get the size of a # and determine how many will fit 
			CSize sizePound = pDC->GetTextExtent(_T("#"), 1);
			int nNumPounds = (int)(rect.Width() / sizePound.cx);

			if (nNumPounds)
			{
				CString strLine(_T(""));

				// Fill a string with as many #s as can be drawn in 
				// the given rect
				for (int i=0; i<nNumPounds; i++)
				{
					strLine += _T("#");
				}

				// Draw it!
				pDC->TextOut(nLeft, rect.top, strLine);
				//pDC->DrawText(strLine, rect, nFormat);
			}
			else
			{
				// Less than one # can be drawn in the given rect.  We'll have
				// to clip a single #.  This is expensive, but there's no other 
				// way to do it.  

				BOOL bCanClip = TRUE;
			
				// Metafiles don't support SelectClipRgn!
				if (pDC->IsKindOf(RUNTIME_CLASS(CMetaFileDC)) && !pDC->IsPrinting())
					bCanClip = FALSE;

				// 16-Bit device drivers don't support SelectClipRgn!
				if (GXGetAppData()->bWin31 && pDC->IsPrinting())
					bCanClip = FALSE;

				if (bCanClip)
				{
					// Set up clipping region
					pDC->GetClipBox(rectOldClip);
					pDC->IntersectClipRect(lpClipRect);

					CString strPound(_T("#"));
					pDC->TextOut(nLeft, rect.top, strPound);
					//pDC->DrawText(strPound, rect, nFormat);

					// Restore original clipping region
					pDC->SelectClipRgn(NULL);
					pDC->IntersectClipRect(rectOldClip);
				}
			}
		}
// ELLIPSE CODE <-
		else
		{
			// Simply draw the text without clipping (that's very fast)
			pDC->TextOut(nLeft, rect.top, pszLine, nBytes);
			//pDC->DrawText(pszLine, nBytes, rect, nFormat);
		}

		rect.top += dyHeight;
	}

	return 0;
}

int CGXDrawingAndFormatting::GXDrawTextLikeMultiLineEdit(CDC* pDC, LPCTSTR lpszString, int nCount, CRect rc, UINT nFormat, LPRECT lpClipRect)
{
	CRect rect = rc;
	int LineBreaks[32], LineLengths[32];

	if (nCount == -1)
		nCount = (int)_tcslen(lpszString);

	if (lpClipRect == NULL)
		lpClipRect = &rect;

#ifdef _DEBUG
	CRect _r;
	ASSERT(rc.IsRectEmpty() || _r.IntersectRect(rc, lpClipRect) && _r == rc);
	// ASSERTION-> lpClipRect must be bigger than rc. Please make sure
	// in your calling function that the boundaries of the clipping rectangle
	// are not inside the prefered drawing rectangle (rc). ->END
#endif

/*
	Uncomment these lines if vertical text should work for all cells
#if _MFC_VER >= 0x0400                 
	LOGFONT lf;
	pDC->GetCurrentFont()->GetObject(sizeof(lf), &lf);

	// draw vertical text
	if (lf.lfOrientation != 0 && lf.lfOrientation == lf.lfEscapement)
		return GXDrawRotatedText(pDC, lpszString, nCount, rc, nFormat, lf.lfOrientation, lpClipRect);
#endif
*/

	// regular text
	int nLineBreaks = GXComputeLineBreaks(pDC,
		lpszString, nCount, &rect, nFormat, LineBreaks, LineLengths, 32);

	TEXTMETRIC    tm;
	pDC->GetTextMetrics(&tm);
	int dyHeight = tm.tmHeight + tm.tmExternalLeading;

	// CEdit uses different height for larger fonts.
	// This value has been determined by experiment. I simply
	// compared the results by using different values and
	// 20 seemed to work fine.
	if (dyHeight >= 20) 
		dyHeight--;

	for (int nBreak = 0; nBreak < nLineBreaks; nBreak++)
	{
		int nLeft = -1;
		LPCTSTR pszLine = lpszString+LineBreaks[nBreak];
		int nBytes = LineLengths[nBreak];
		CSize size(0,0);
		BOOL bNeedClip = FALSE;
		CRect rectOldClip;

		// Implement some special clipping when text is
		// only one character. Let's show as much as possible
		// of this one character if it must be clipped
		// (possibly also shift it to the left boundary of
		// the clipping rectangle).
		if (nBytes == (int) _tclen(pszLine))
		{
			size = pDC->GetTextExtent(pszLine, nBytes);

			// clip when only one visible char does not
			// fit into clipping rectangle
			if (size.cx > ((CRect*) lpClipRect)->Width())
			{
				bNeedClip = TRUE;
				nLeft = lpClipRect->left;
			}
			// adjust left so that the char fits into the
			// clipping rectangle
			else if (size.cx > rect.Width())
				nLeft = min(lpClipRect->right - size.cx, rect.left);
		}

		// Adjust left so that text will be correctly aligned
		if (nLeft == -1 && (nFormat & (DT_CENTER|DT_RIGHT)) > 0)
		{
			if (size.cx == 0)
				size = pDC->GetTextExtent(pszLine, nBytes);

			if (nFormat & DT_RIGHT)
				nLeft = max(rect.left, rect.right-size.cx);
			else if (nFormat & DT_CENTER)
				nLeft = max(rect.left, rect.left+(rect.right-rect.left-size.cx)/2);
		}

		// default is to use the left of the preffered rectangle
		if (nLeft == -1)
			nLeft = rect.left;

		if (bNeedClip)
		{
			BOOL bCanClip = TRUE;
			
			// Metafiles don't support SelectClipRgn!
			if (pDC->IsKindOf(RUNTIME_CLASS(CMetaFileDC)) && !pDC->IsPrinting())
				bCanClip = FALSE;

			// 16-Bit device drivers don't support SelectClipRgn!
			if (GXGetAppData()->bWin31 && pDC->IsPrinting())
				bCanClip = FALSE;

			if (bCanClip)
			{
				// It's an expensive operation but there is no way
				// around clipping.
				pDC->GetClipBox(rectOldClip);
				pDC->IntersectClipRect(lpClipRect);

				pDC->TextOut(nLeft, rect.top, pszLine, nBytes);
				//pDC->DrawText(pszLine, nBytes, &rect, nFormat);

				// restore original clipping region
				pDC->SelectClipRgn(NULL);
				pDC->IntersectClipRect(rectOldClip);
			}
			// else
				// there is no way that we can draw that character
				// without messing up the other drawing. So, the
				// compromise is not to print that half char
		}
		else
		{
			// simply draw the text without clipping (that's very fast)

			// SRSTUDIOQA-5619-------------------
			// Account for DT_RIGHT horizontal alignment.
			CString str(pszLine);
			if(nFormat & DT_RIGHT)
			{
				str = str.Left(nBytes);
			}
			pDC->TextOut(nLeft, rect.top, (LPCTSTR)str, nBytes);
			//-----------------------------------
			//pDC->TextOut(nLeft, rect.top, pszLine, nBytes);
			//pDC->DrawText(pszLine, nBytes, &rect, nFormat);
		}
		rect.top += dyHeight;
	}

	return 0;
}

int CGXDrawingAndFormatting::GXDrawRotatedText(CDC* pDC, LPCTSTR lpszString, int nCount, CRect rc, UINT nFormat, LONG lfOrientation, LPRECT lpClipRect)
{
	GX_CHECKIMP(GXGetAppData()->m_pDrawRotatedTextImp, "CGXDrawingAndFormatting::GXDrawRotatedText");

	if (GXGetAppData()->m_pDrawRotatedTextImp)
		return GXGetAppData()->m_pDrawRotatedTextImp->GXDrawRotatedText(pDC, lpszString, nCount, rc, nFormat, lfOrientation, lpClipRect);

	return 0;
}

int CGXDrawingAndFormatting::GXGetMultiLineTextPosUnderPt(CDC* pDC, LPCTSTR lpszString, int nCount, CRect rect, UINT nFormat, CPoint pt)
{
	int LineBreaks[32], LineLengths[32];

	int nLineBreaks = GXComputeLineBreaks(pDC,
		lpszString, nCount, &rect, nFormat, LineBreaks, LineLengths, 32);

	TEXTMETRIC tm;
	pDC->GetTextMetrics(&tm);

	int dyHeight = tm.tmHeight + tm.tmExternalLeading;

	// eliminate vertical alignment flags
	int nBreak;
	for (nBreak = 0; nBreak < nLineBreaks; nBreak++)
	{
		if (pt.y < rect.top+dyHeight)
			break;
		rect.top += dyHeight;
	}

	// clicked outside area
	if (pt.y < rect.top || nBreak == nLineBreaks)
		return -1;

	LPCTSTR szLine = lpszString+LineBreaks[nBreak];
	int nBytes = LineLengths[nBreak];
	if (nBytes == 0)
		return -1;


	// compute line
	CSize size = pDC->GetTextExtent(szLine, nBytes);

	int dxWidth = tm.tmMaxCharWidth;
	// find pos in line
	int nIndex = 0;

	// Take care of RTL langs.
	if(!(pDC->GetTextAlign() & TA_RTLREADING))
	{
		// Left to Right
		int nLeft = rect.left;
		if (nFormat & DT_RIGHT)
			nLeft = max(rect.left, rect.right-size.cx);
		else if (nFormat & DT_CENTER)
			nLeft = max(rect.left, rect.left+(rect.right-rect.left-size.cx)/2);

		if (pt.x < nLeft-dxWidth/3)
			return -1;

		do
		{
			nIndex += (int)_tclen(szLine+nIndex);
			size = pDC->GetTextExtent(szLine, nIndex);
		} while (size.cx+nLeft <= pt.x && nIndex < nBytes);

		if (nIndex == nBytes && size.cx+nLeft+dxWidth/3 <= pt.x)
			return -1;

		if (size.cx+nLeft > pt.x)
			nIndex -= (int)((szLine+nIndex) - _tcsdec(szLine, szLine+nIndex));
	}
	else
	{
		// Right to Left
		int nRight = rect.right;

		if(nFormat & DT_CENTER)
			nRight = min(rect.right, rect.right-(rect.right-rect.left-size.cx)/2);
		else if (!(nFormat & DT_RIGHT))	// Left aligned
			nRight = min(rect.right, rect.left + size.cx);

		do
		{
			nIndex += (int)_tclen(szLine+nIndex);
			size = pDC->GetTextExtent(szLine, nIndex);
		} while (nRight-size.cx >= pt.x && nIndex < nBytes);

		if (nIndex == nBytes && nRight-size.cx-dxWidth/3 >= pt.x)
			return -1;

		if (nRight-size.cx < pt.x)
			nIndex -= (int)((szLine+nIndex) - _tcsdec(szLine, szLine+nIndex));

	}
	
	return LineBreaks[nBreak]+nIndex;
}

int AFXAPI GXGetNextLine(CString& s, CString &sLine)
{
	int n = s.FindOneOf(_T("\r\n"));

	if (n >= 0)
	{
		sLine = s.Left(n);
		// if there is a "\r\n", skip the newline character
		if (s[n] == _T('\r') && n+1 < s.GetLength() && s[n+1] == _T('\n'))
			n++;
		s = s.Mid(n+1);
	}
	else
	{
		sLine = s;
		s.Empty();
	}

	return n;
}

void AFXAPI GXGetColString(LPCTSTR pszLine, int nCol, LPTSTR szResult, int nMaxLen)
{
	// Skip leading columns
	LPCTSTR pszFind = pszLine - 1;
	for (int i = 0; pszFind != NULL && i < nCol; i++)
		pszFind = _tcschr(pszFind + 1, _T('\t'));

	// Copy column
	if (pszFind)
	{
		// Skip tab char
		pszFind++;

		// Copy byte by byte until next tab or null is found
		int nLen = 0;
		LPTSTR p;
		for (p = szResult;
			nLen < nMaxLen && *pszFind && *pszFind != _T('\t');
			p++, nLen++, pszFind++)
			*p = *pszFind;

		// end of string
		*p = 0;
	}
	else
		// empty
		*szResult = 0;

}

int AFXAPI GXFindChoiceListItem(const CString& strFind, int nCol, const CString& strChoiceList, BOOL bSkipFirstRow, CString& sItem, BOOL bExact)
{
	int nEntry = 0;

	// search for string in choice list
	CString s = strChoiceList;
	int n = 0;
	TCHAR szValue[128];

	if (bSkipFirstRow)
		n = GXGetNextLine(s, sItem);

	while (!s.IsEmpty() && n != -1)
	{
		n = GXGetNextLine(s, sItem);

		GXGetColString(sItem, nCol, szValue, 127);

		if (bExact && _tcscmp(szValue, strFind) == 0
			|| !bExact && _tcsnicmp(szValue, strFind, strFind.GetLength()) == 0)
			return nEntry;

		nEntry++;
	}

	sItem.Empty();
	return -1;
}

static int GXNEAR s_nCol = 0;
static LPTSTR GXNEAR s_pstr1, s_pstr2;
static const int GXNEAR s_nMaxLen = 128;

#if defined(_UNIX_)
static int __cdecl __compare(const void* p1, const void* p2)
#else
extern "C" static int __cdecl __compare(const void* p1, const void* p2)
#endif
{
	CString* ps1 = (CString*) p1;
	CString* ps2 = (CString*) p2;

	if (s_nCol > 0)
	{
		GXGetColString(*ps1, s_nCol, s_pstr1, s_nMaxLen);
		GXGetColString(*ps2, s_nCol, s_pstr2, s_nMaxLen);

		return _tcsicmp(s_pstr1, s_pstr2);
	}
	else
		return ps1->CompareNoCase(*ps2);
}     

#if _MFC_VER < 0x0400

// CStringArray has no GetData() member

class CGXStringArray: public CStringArray
{                                         
public:
	CString* GetData() { return m_pData; }
};

#define CStringArray CGXStringArray

#endif	

void AFXAPI GXSortChoiceList(CString& strChoiceList, int nCol, BOOL bSkipFirstRow)
{
	int n = 0;

	CString sRowOne;
	if (bSkipFirstRow)
		n = GXGetNextLine(strChoiceList, sRowOne);

	CStringArray array;
	CString sItem;

	// Fill String Array
	while (!strChoiceList.IsEmpty() && n != -1)
	{
		n = GXGetNextLine(strChoiceList, sItem);
		array.SetAtGrow(array.GetSize(), sItem);
	}

	s_nCol = nCol;
	s_pstr1 = new TCHAR[s_nMaxLen];
	s_pstr2 = new TCHAR[s_nMaxLen];

	// Sort String Array
	qsort(array.GetData(), array.GetSize(), sizeof(CString), __compare);

	// Cleanup
	delete s_pstr1;
	delete s_pstr2;

	// Write Choice List back
	if (bSkipFirstRow)
	{
		strChoiceList = sRowOne;
		strChoiceList += _T("\r\n");
	}
	else
		strChoiceList.Empty();

	for (int i = 0; i < array.GetSize(); i++)
	{
		strChoiceList += array[i];
		strChoiceList += _T("\r\n");
	}
}

/////////////////////////////////////////////////////////////////////////////
// helper routine for drawing sunken border (WS_CLIENTEDGE)

// called from OnNcPaint to give the control a 3d-sunken effect.

void CGXDrawingAndFormatting::_GXDrawSunkenBorders(CDC* pDC, CRect& rc, BOOL bBorder, BOOL bClientEdge)
{
#if _MFC_VER >= 0x0400
	if (bBorder)
		::DrawEdge(pDC->GetSafeHdc(), &rc, (bClientEdge ? (BDR_RAISEDINNER | BDR_SUNKENINNER) : (BDR_RAISEDOUTER | BDR_SUNKENOUTER)),
			BF_RECT | BF_ADJUST | (bClientEdge ? BF_FLAT : BF_MONO));

	if (bClientEdge)
		::DrawEdge(pDC->GetSafeHdc(), &rc, EDGE_SUNKEN, BF_RECT | BF_ADJUST);
#else
	// Unused:
	bBorder, bClientEdge;

	GXDraw3dFrame(pDC, rc.left+1, rc.top+1, rc.right-2, rc.bottom-2, 1,
		  RGB(96,96,96), RGB(255,255,255));
	GXDraw3dFrame(pDC, rc.left, rc.top, rc.right-1, rc.bottom-1, 1,
		  RGB(192,192,192), RGB(192,192,192));
#endif
}


void CGXDrawingAndFormatting::DrawStatic(CGXControl* pControl, CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle)
{
	CGXGridCore* pGrid = pControl->Grid();
	CGXGridParam* pParam = pGrid->GetParam();

	pControl->DrawBackground(pDC, rect, style);

	CString sOutput;

	if (pParam->m_nDisplayExpression & GX_EXPR_DISPLAYALWAYS)
		sOutput = pGrid->GetExpressionRowCol(nRow, nCol);
	else
		pControl->GetControlText(sOutput, nRow, nCol, NULL, style);

	if (sOutput.IsEmpty())
	{
		pControl->CGXControl::Draw(pDC, rect, nRow, nCol, style, pStandardStyle);
		return;
	}

	if (rect.right <= rect.left || rect.Width() <= 1 || rect.Height() <= 1)
		return;

	// ------------------ Static Text ---------------------------

	CString str;
	HANDLE hbm = 0;
	
	// check for #bmp only for static cells (and not 
	// for cells where the user can enter the text)

	if (!pControl->IsKindOf(RUNTIME_CLASS(CEdit)))
		hbm = GXGetDIBState()->GetPool()->LookupOrCreateDIB(sOutput);

	if (hbm)
	{
		// Draw bitmap

		// Don't subtract margins - only borders and 3d-frame
		// Therefore we call CGXControl::AddBorders
		CRect r = pControl->CGXControl::GetCellRect(nRow, nCol, rect, &style);

		DWORD dtAlign = style.GetHorizontalAlignment() | style.GetVerticalAlignment();

		CGXDIB::Draw(pDC, hbm, r, CGXDIB::none, (UINT) dtAlign);

		// child Controls: spin-buttons, hotspot, combobox btn, ...
		pControl->CGXControl::Draw(pDC, rect, nRow, nCol, style, pStandardStyle);
	}
	else
	{
		// Draw text

		// Select font
		CFont* pOldFont = pControl->LoadFont(pDC, style, pStandardStyle);

		// Rectangle
		CRect rectItem = rect;

		// subtract margins and borders 
		CRect rectText = pControl->GetCellRect(nRow, nCol, rect);

		// Cell-Color
		COLORREF rgbText = style.GetTextColor();
		COLORREF rgbCell = style.GetInteriorRef().GetColor();

		if (pParam->GetProperties()->GetBlackWhite())
		{
			rgbText = RGB(0,0,0);
			rgbCell = RGB(255,255,255);
		}

		if (_tcslen(sOutput) > 0)
		{
			pDC->SetBkMode(TRANSPARENT);
			pDC->SetBkColor(rgbCell);
			pDC->SetTextColor(rgbText);

			DWORD dtAlign = style.GetHorizontalAlignment() | style.GetVerticalAlignment();

			if (style.GetWrapText())
				dtAlign |= DT_NOPREFIX | DT_WORDBREAK;
			else
				dtAlign |= DT_NOPREFIX | DT_SINGLELINE;

			BOOL bRTLReading = style.GetIncludeUserAttribute(GX_IDS_UA_RTLREADING) ?
				(BOOL)_ttoi( style.GetUserAttribute(GX_IDS_UA_RTLREADING)) : FALSE;

			if(bRTLReading)
				pDC->SetTextAlign(TA_RTLREADING);

			if (style.GetIncludeFont() 
				&& style.GetFontRef().GetIncludeOrientation() 
				&& style.GetFontRef().GetOrientation() != 0)
			{
				// draw vertical text
				GXDaFTools()->GXDrawRotatedText(pDC, 
					sOutput,
					sOutput.GetLength(),
					rectText,
					(UINT) dtAlign,
					style.GetFontRef().GetOrientation(), 
					&rect);
			}
			else
			{
				
				// check if ellipses are to be used
				if(!style.GetIncludeUserAttribute(GX_IDS_UA_ELLIPSISTYPE))
					GXDrawTextLikeMultiLineEdit(pDC,
					sOutput,
					sOutput.GetLength(),
					rectText,
					(UINT) dtAlign,
					&rect);
				else
						GXDrawTextLikeMultiLineEditEx(pDC,
					sOutput,
					sOutput.GetLength(),
					rectText,
					(UINT) dtAlign,
					&rect, ( (CGXEllipseUserAttribute&)style.GetUserAttribute(GX_IDS_UA_ELLIPSISTYPE)).GetEllipseValue());
			}
		}

		// child Controls: spin-buttons, hotspot, combobox btn, ...
		pControl->CGXControl::Draw(pDC, rect, nRow, nCol, style, pStandardStyle);

		if (pOldFont)
			pDC->SelectObject(pOldFont);
	}
}
