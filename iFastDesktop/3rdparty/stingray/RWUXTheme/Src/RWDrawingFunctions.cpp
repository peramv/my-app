///////////////////////////////////////////////////////////////////////////////
// RWDrawingFunctions.cpp
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

#include "stdafx.h"

// Drawing constants
// ~~~~~~~~~~~~~~~~~
const COLORREF	gFillColor = 0x00203241; 
const UINT		gShadowThreshold = 180 * 256;
const DWORD		ROP_DSPDxax = 0x00E20746;

// Color manipulation constants
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
const BYTE		gRedWeight   =	77;
const BYTE		gGreenWeight = 153;
const BYTE		gBlueWeight =  26;


RWTHEMEAPI(void) RWDrawImage( HDC hDC, HIMAGELIST hImgLst, UINT index, UINT offsetX, UINT offsetY, UINT width, UINT height, BOOL isHiContrast )
{
	if( !isHiContrast )
	{
		::ImageList_Draw( hImgLst, index, hDC, offsetX, offsetY , ILD_TRANSPARENT ); // TRUE if successful
	}
	else
	{
		HDC		hMemDC = ::CreateCompatibleDC( hDC );
		HDC		hMemDC2 = ::CreateCompatibleDC( hDC );

		HBITMAP hMemBmp = ::CreateCompatibleBitmap( hDC, width, height );
		HBITMAP hMemBmp2 = ::CreateCompatibleBitmap( hDC, width, height );

		HGDIOBJ hOldBmp = ::SelectObject( hMemDC, hMemBmp );
		HGDIOBJ hOldBmp2 = ::SelectObject( hMemDC2, hMemBmp2 );

		HBRUSH	hBrush = ::CreateSolidBrush( gFillColor );
		RECT	drawRc = { 0, 0, width, height };

		UINT		x, y;
		COLORREF	srcClr, dstClr;

		::BitBlt( hMemDC, 0, 0, width, height, hDC, offsetX, offsetY, SRCCOPY );

		::FillRect( hMemDC2,  &drawRc, hBrush ); DeleteObject( hBrush );
		::ImageList_Draw( hImgLst, index, hMemDC2, 0, 0, ILD_TRANSPARENT ); // TRUE if successful

		for( y = 0; y < height; y++ )
		{
			for( x = 0; x < width; x++ )
			{
				srcClr = ::GetPixel( hMemDC2, x, y );
				if( srcClr != gFillColor )
				{
					dstClr = (((srcClr & 0xFF0000) >> 16) * gBlueWeight) + (((srcClr & 0x00FF00) >> 8) * gGreenWeight) + ((srcClr & 0x0000FF) * gRedWeight);

					if( dstClr > 0xFD00 ) 
						srcClr = 0x000000;
					else
						if( dstClr < 0x6400 )
							srcClr = 0xFFFFFF;

					dstClr = RWLightenColor( srcClr, 32 );
					::SetPixelV( hMemDC, x, y, dstClr );
				}
			}
		}

		::BitBlt( hDC, offsetX, offsetY, width, height, hMemDC, 0, 0, SRCCOPY );

		::SelectObject( hMemDC2, hOldBmp2 );
		::DeleteObject( hMemBmp2 );

		::SelectObject( hMemDC, hOldBmp );
		::DeleteObject( hMemBmp );

		::DeleteDC( hMemDC2 );
		::DeleteDC( hMemDC );
	}
}

RWTHEMEAPI(void) RWDrawHighlightedImage( HDC hDC, HIMAGELIST hImgLst, UINT index, UINT offsetX, UINT offsetY, UINT width, UINT height, COLORREF highlightingColor, BYTE amount )
{
	HDC		hMemDC = ::CreateCompatibleDC( hDC );
	HDC		hMemDC2 = ::CreateCompatibleDC( hDC );

	HBITMAP hMemBmp = ::CreateCompatibleBitmap( hDC, width, height );
	HBITMAP hMemBmp2 = ::CreateCompatibleBitmap( hDC, width, height );

	HGDIOBJ hOldBmp = ::SelectObject( hMemDC, hMemBmp );
	HGDIOBJ hOldBmp2 = ::SelectObject( hMemDC2, hMemBmp2 );

	HBRUSH	hBrush = ::CreateSolidBrush( gFillColor );
	RECT	drawRc = { 0, 0, width, height };

	UINT		x, y;
	COLORREF	srcClr, dstClr, rbClr, gClr;

	::BitBlt( hMemDC, 0, 0, width, height, hDC, offsetX, offsetY, SRCCOPY );

	::FillRect( hMemDC2,  &drawRc, hBrush ); DeleteObject( hBrush ); hBrush = NULL;
	::ImageList_Draw( hImgLst, index, hMemDC2, 0, 0, ILD_TRANSPARENT ); // TRUE if successful

	rbClr = (highlightingColor & 0x00FF00FF) * (255 - amount);
	gClr = (highlightingColor & 0x0000FF00) * (255 - amount);

	for( y = 0; y < height; y++ )
	{
		for( x = 0; x < width; x++ )
		{
			srcClr = ::GetPixel( hMemDC2, x, y ); 
			if( srcClr != gFillColor )
			{
				dstClr = (((srcClr & 0xFF00FF) * amount + rbClr) & 0xFF00FF00) + (((srcClr & 0x00FF00) * amount + gClr) & 0x00FF0000);

				dstClr >>= 8;

				::SetPixelV( hMemDC, x, y, dstClr );
			}
		}
	}

	::BitBlt( hDC, offsetX, offsetY, width, height, hMemDC, 0, 0, SRCCOPY );

	::SelectObject( hMemDC2, hOldBmp2 );
	::DeleteObject( hMemBmp2 );

	::SelectObject( hMemDC, hOldBmp );
	::DeleteObject( hMemBmp );

	::DeleteDC( hMemDC2 );
	::DeleteDC( hMemDC );
}

RWTHEMEAPI(void) RWDrawFullImageShadow( HDC hDC, HIMAGELIST hImgLst, UINT index, UINT offsetX, UINT offsetY, UINT width, UINT height, COLORREF shadowColor )
{
	HDC		hMemDC = ::CreateCompatibleDC( hDC );
	HDC		hMemDCMono = ::CreateCompatibleDC( hDC );
	HBITMAP hMemBmp = ::CreateCompatibleBitmap( hDC, width, height );
	HBITMAP hMemBmpMono = ::CreateBitmap( width, height, 1, 1, NULL );

	HGDIOBJ hOldBmp = ::SelectObject( hMemDC, hMemBmp );
	HGDIOBJ hOldBmpMono = ::SelectObject( hMemDCMono, hMemBmpMono );

	HBRUSH	hBrush, hOldBrush, hOldMBrush;
	RECT	drawRc = { 0, 0, width, height };

	UINT		x, y;
	COLORREF	srcClr, dstClr;

	::FillRect( hMemDC,  &drawRc, (HBRUSH)::GetStockObject( WHITE_BRUSH ) );
	::ImageList_Draw( hImgLst, index, hMemDC, 0, 0, ILD_TRANSPARENT ); // TRUE if successful

	for( y = 0; y < height; y++ )
	{
		for( x = 0; x < width; x++ )
		{
			srcClr = GetPixel( hMemDC, x, y );
			if( srcClr != 0 )
			{
				dstClr = (((srcClr & 0xFF0000)>>16)*gBlueWeight) + (((srcClr & 0x00FF00) >> 8) * gGreenWeight) + ((srcClr & 0x0000FF) * gRedWeight);

				if( dstClr > gShadowThreshold )
					dstClr = 0x00FFFFFF;
				else
					dstClr = 0x00000000;
		
				SetPixelV( hMemDC, x, y, dstClr );
			}
		}
	}

	hOldMBrush = (HBRUSH)::SelectObject( hMemDCMono, ::GetStockObject( BLACK_BRUSH ) );
    BitBlt( hMemDCMono, 0, 0, width, height, hMemDC, 0, 0, SRCCOPY );

	hBrush = ::CreateSolidBrush( shadowColor );
	hOldBrush = (HBRUSH)::SelectObject( hDC, hBrush );

	srcClr = ::SetTextColor( hDC, RGB( 255, 255, 255 ) );
	dstClr = ::SetBkColor( hDC, RGB( 0, 0, 0 ) );
	
	BitBlt( hDC, offsetX, offsetY, width, height, hMemDCMono, 0, 0, ROP_DSPDxax );

	::SelectObject( hMemDCMono, hOldMBrush ); 
	::SelectObject( hDC, hOldBrush ); ::DeleteObject( hBrush );

	::SetTextColor( hDC, srcClr );
	::SetBkColor( hDC, dstClr );

	::SelectObject( hMemDCMono, hOldBmpMono );
	::DeleteObject( hMemBmpMono );

	::SelectObject( hMemDC, hOldBmp );
	::DeleteObject( hMemBmp );

	::DeleteDC( hMemDCMono );
	::DeleteDC( hMemDC );
}

RWTHEMEAPI(void) RWDrawFlatImageShadow( HDC hDC, HIMAGELIST hImgLst, UINT index, UINT offsetX, UINT offsetY, UINT width, UINT height, COLORREF shadowColor )
{
	HDC		hMemDC = ::CreateCompatibleDC( hDC );
	HDC		hMemDCMono = ::CreateCompatibleDC( hDC );
	HBITMAP hMemBmp = ::CreateCompatibleBitmap( hDC, width, height );
	HBITMAP hMemBmpMono = ::CreateBitmap( width, height, 1, 1, NULL );

	HGDIOBJ hOldBmp = ::SelectObject( hMemDC, hMemBmp );
	HGDIOBJ hOldBmpMono = ::SelectObject( hMemDCMono, hMemBmpMono );

	HBRUSH	hBrush = ::CreateSolidBrush( gFillColor ), hOldBrush, hOldMBrush;
	RECT	drawRc = { 0, 0, width, height };

	UINT		x, y;
	COLORREF	srcClr, dstClr;

	::FillRect( hMemDC,  &drawRc, hBrush ); ::DeleteObject( hBrush );
	::ImageList_Draw( hImgLst, index, hMemDC, 0, 0, ILD_TRANSPARENT ); // TRUE if successful

	for( y = 0; y < height; y++ )
	{
		for( x = 0; x < width; x++ )
		{
			srcClr = GetPixel( hMemDC, x, y );
			if( srcClr == gFillColor )
				srcClr = 0x00FFFFFF;
			else
				srcClr = 0x00000000;

			SetPixelV( hMemDC, x, y, srcClr );
		}
	}

	hOldMBrush = (HBRUSH)::SelectObject( hMemDCMono, ::GetStockObject( BLACK_BRUSH ) );
    BitBlt( hMemDCMono, 0, 0, width, height, hMemDC, 0, 0, SRCCOPY );

	hBrush = ::CreateSolidBrush( shadowColor );
	hOldBrush = (HBRUSH)::SelectObject( hDC, hBrush );

	srcClr = ::SetTextColor( hDC, RGB( 255, 255, 255 ) );
	dstClr = ::SetBkColor( hDC, RGB( 0, 0, 0 ) );
	
	BitBlt( hDC, offsetX, offsetY, width, height, hMemDCMono, 0, 0, ROP_DSPDxax );

	::SelectObject( hMemDCMono, hOldMBrush ); 
	::SelectObject( hDC, hOldBrush ); ::DeleteObject( hBrush );

	::SetTextColor( hDC, srcClr );
	::SetBkColor( hDC, dstClr );

	::SelectObject( hMemDCMono, hOldBmpMono );
	::DeleteObject( hMemBmpMono );

	::SelectObject( hMemDC, hOldBmp );
	::DeleteObject( hMemBmp );

	::DeleteDC( hMemDCMono );
	::DeleteDC( hMemDC );
}

 
RWTHEMEAPI(BOOL) RWBlendBlt( HDC hdcDest, int nXOriginDest, int nYOriginDest, int nWidth, int nHeight, HDC hdcSrc, int nXOriginSrc, int nYOriginSrc, BYTE alphaConst )
{
	HDC	hMemDC1 = NULL;
	HDC hMemDC2 = NULL;

	HBITMAP	hBmp1 = NULL, hBmp2 = NULL, hOldBmp1 = NULL, hOldBmp2 = NULL;

	int	x, y;

	hMemDC1 = CreateCompatibleDC( hdcDest );
	hMemDC2 = CreateCompatibleDC( hdcSrc );

	hBmp1 = CreateCompatibleBitmap( hdcDest, nWidth, nHeight );
	hBmp2 = CreateCompatibleBitmap( hdcSrc, nWidth, nHeight );

	hOldBmp1 = (HBITMAP)SelectObject( hMemDC1, hBmp1 );
	hOldBmp2 = (HBITMAP)SelectObject( hMemDC2, hBmp2 );

	SetBkColor( hMemDC1, RGB( 0xFF, 0xFF, 0xFF ) );
	SetBkColor( hMemDC2, RGB( 0xFF, 0xFF, 0xFF ) );

	BitBlt( hMemDC1, 0, 0, nWidth, nHeight, hdcDest, nXOriginDest, nYOriginDest, SRCCOPY );
	BitBlt( hMemDC2, 0, 0, nWidth, nHeight, hdcSrc, nXOriginSrc, nYOriginSrc, SRCCOPY );

	// Not the best algorithm, but since we are working with memory DC it should be pretty quick
	for( x = 0; x < nWidth; x++ )
	{
		for( y = 0; y < nHeight; y++ )
		{
			COLORREF col1 = GetPixel( hMemDC1, x, y );
			COLORREF col2 = GetPixel( hMemDC2, x, y );

			SetPixelV( hMemDC1, x, y, RWBlendColors( col1, col2, alphaConst ) );
		}
	}

	BitBlt( hdcDest, nXOriginDest, nYOriginDest, nWidth, nHeight, hMemDC1, 0, 0, SRCCOPY );

	SelectObject( hMemDC2, hOldBmp2 ); DeleteObject( hBmp2 );
	SelectObject( hMemDC1, hOldBmp1 ); DeleteObject( hBmp1 );

	DeleteDC( hMemDC2 );
	DeleteDC( hMemDC1 );

	return TRUE;
}

RWTHEMEAPI(BOOL) RWTransparentBlt( HDC hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, HDC hdcSrc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, UINT crTransparent )
{
	// Because there is memory leak bug in Win98 I have to comment this system function call we will have to rely on our implementation
/*
	if( PtrTransparentBlt )
		return PtrTransparentBlt( hdcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, hdcSrc, nXOriginSrc, nYOriginSrc, nWidthSrc, nHeightSrc, crTransparent );
*/
	//Current OS doesn't have TransparentBlt function so let's emulate TransparentBlt functionality.

	HDC			hMemDC = NULL;
	HBITMAP		hMask = NULL;
	HBITMAP		hOldBmp = NULL;
	int			nMaskWidth = 0;
	int			nMaskHeight = 0;
	COLORREF	oldBk = RGB( 0, 0, 0 );
	COLORREF	oldFg = RGB( 0, 0, 0 );
	BOOL		result = TRUE;

	// get real size of the mask
	nMaskWidth = nWidthSrc;
	nMaskHeight = nHeightSrc;

	// create monochrome mask bitmap on memory DC
	hMemDC = CreateCompatibleDC( hdcSrc );
	hMask = CreateBitmap( nMaskWidth, nMaskHeight - nYOriginSrc, 1, 1, NULL );
	hOldBmp = (HBITMAP)SelectObject( hMemDC, hMask );

	// set transparent color and create mask
	oldBk = SetBkColor( hdcSrc, crTransparent );
	result = BitBlt( hMemDC, 0, 0, nMaskWidth, nMaskHeight - nYOriginSrc, hdcSrc, nXOriginSrc, nYOriginSrc, SRCCOPY );
	SetBkColor( hdcSrc, oldBk );

	// Trasparency algorithm - D=D^S; D=D&Mask; D=D^S --> if(Mask==1) D else S

	// D=D^S
	result = BitBlt( hdcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, hdcSrc, nXOriginSrc, nYOriginSrc, SRCINVERT );

	// Let's apply mask - D=D&Mask
	oldFg = SetTextColor( hdcDest, RGB( 0, 0, 0 ) );
	oldBk = SetBkColor( hdcDest, RGB( 255, 255, 255 ) );

	result = BitBlt( hdcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, hMemDC, 0, 0, SRCAND );

	SetTextColor( hdcDest, oldFg );
	SetBkColor( hdcDest, oldBk );

	// D=D^S
	result = BitBlt( hdcDest, nXOriginDest, nYOriginDest, nWidthDest, nHeightDest, hdcSrc, nXOriginSrc, nYOriginSrc, SRCINVERT );

	SelectObject( hMemDC, hOldBmp );
	DeleteDC( hMemDC );

	DeleteObject( hMask );

	return result;
}

RWTHEMEAPI(HRESULT) RWDrawThemedBMPItem( HWND hWnd, HDC hDC, HBITMAP hBMP, LPCWSTR pszClassList, int iPartId, int iStateId, int x, int y, int cx, int cy, int bmpX, int bmpY, int bmpCX, int bmpCY, unsigned int transColor )
{
	HTHEME	hTheme = NULL;
	HRESULT	hr = 0;

	if( RWIsAppThemed() && RWIsThemeActive() )
	{
		hTheme = RWOpenThemeData( hWnd, pszClassList );
	}

	if( hTheme )
	{
		RECT	rc;
		BOOL	bRet = true;

		rc.left = x;
		rc.top = y;
		rc.right = x + cx;
		rc.bottom = y + cy;

		hr = RWDrawThemeBackground( hTheme, hDC, iPartId, iStateId, &rc, 0 );

		if( FAILED(hr) )
			return hr;

		HDC	hMemDC = CreateCompatibleDC( hDC );

		if( hMemDC )
		{
			HGDIOBJ hOldBmp = ::SelectObject( hMemDC, hBMP );

			bRet = RWTransparentBlt( hDC, x+bmpX, y+bmpY, bmpCX, bmpCY, hMemDC, 0, 0, bmpCX, bmpCY, transColor );

			::SelectObject( hMemDC, hOldBmp );
		}
		else
			bRet = FALSE;

		RWCloseThemeData( hTheme );

		if( bRet )
			return S_OK;
	}

	return E_FAIL;
}

RWTHEMEAPI(void) RWDrawDCImage( HDC hDC, UINT offsetX, UINT offsetY, UINT width, UINT height, HDC hBmpDC, UINT bmpOffsetX, UINT bmpOffsetY, COLORREF transColor, BOOL isHiContrast )
{
	HDC		hMemDC = ::CreateCompatibleDC( hDC );
	HDC		hMemDC2 = ::CreateCompatibleDC( hDC );

	HBITMAP hMemBmp = ::CreateCompatibleBitmap( hDC, width, height );
	HBITMAP hMemBmp2 = ::CreateCompatibleBitmap( hDC, width, height );

	HGDIOBJ hOldBmp = ::SelectObject( hMemDC, hMemBmp );
	HGDIOBJ hOldBmp2 = ::SelectObject( hMemDC2, hMemBmp2 );

	UINT		x, y;
	COLORREF	srcClr, dstClr;

	::BitBlt( hMemDC, 0, 0, width, height, hDC, offsetX, offsetY, SRCCOPY );
	::BitBlt( hMemDC2, 0, 0, width, height, hBmpDC, bmpOffsetX, bmpOffsetY, SRCCOPY );

	srcClr = ::GetPixel( hMemDC2, 0, 0 );
	transColor = ::SetPixel( hMemDC2, 0, 0, transColor );
	::SetPixelV( hMemDC2, 0, 0, srcClr );

	for( y = 0; y < height; y++ )
	{
		for( x = 0; x < width; x++ )
		{
			srcClr = ::GetPixel( hMemDC2, x, y );
			if( srcClr != transColor )
			{
				if( isHiContrast )
				{
					dstClr = (((srcClr & 0xFF0000) >> 16) * gBlueWeight) + (((srcClr & 0x00FF00) >> 8) * gGreenWeight) + ((srcClr & 0x0000FF) * gRedWeight);

					if( dstClr > 0xFD00 ) 
						srcClr = 0x000000;
					else
						if( dstClr < 0x6400 )
							srcClr = 0xFFFFFF;

					srcClr = RWLightenColor( srcClr, 32 );
				}

				::SetPixelV( hMemDC, x, y, srcClr );
			}
		}
	}

	::BitBlt( hDC, offsetX, offsetY, width, height, hMemDC, 0, 0, SRCCOPY );

	::SelectObject( hMemDC2, hOldBmp2 );
	::DeleteObject( hMemBmp2 );

	::SelectObject( hMemDC, hOldBmp );
	::DeleteObject( hMemBmp );

	::DeleteDC( hMemDC2 );
	::DeleteDC( hMemDC );
}

RWTHEMEAPI(void) RWDrawDCHighlightedImage( HDC hDC, UINT offsetX, UINT offsetY, UINT width, UINT height, HDC hBmpDC, UINT bmpOffsetX, UINT bmpOffsetY, COLORREF transColor, COLORREF highlightingColor, BYTE amount )
{
	HDC		hMemDC = ::CreateCompatibleDC( hDC );
	HDC		hMemDC2 = ::CreateCompatibleDC( hDC );

	HBITMAP hMemBmp = ::CreateCompatibleBitmap( hDC, width, height );
	HBITMAP hMemBmp2 = ::CreateCompatibleBitmap( hDC, width, height );

	HGDIOBJ hOldBmp = ::SelectObject( hMemDC, hMemBmp );
	HGDIOBJ hOldBmp2 = ::SelectObject( hMemDC2, hMemBmp2 );

	UINT		x, y;
	COLORREF	srcClr, dstClr, rbClr, gClr;

	::BitBlt( hMemDC, 0, 0, width, height, hDC, offsetX, offsetY, SRCCOPY );
	::BitBlt( hMemDC2, 0, 0, width, height, hBmpDC, bmpOffsetX, bmpOffsetY, SRCCOPY );

	rbClr = (highlightingColor & 0x00FF00FF) * (255 - amount);
	gClr = (highlightingColor & 0x0000FF00) * (255 - amount);

	srcClr = ::GetPixel( hMemDC2, 0, 0 );
	transColor = ::SetPixel( hMemDC2, 0, 0, transColor );
	::SetPixelV( hMemDC2, 0, 0, srcClr );

	for( y = 0; y < height; y++ )
	{
		for( x = 0; x < width; x++ )
		{
			srcClr = ::GetPixel( hMemDC2, x, y ); 
			if( srcClr != transColor )
			{
				dstClr = ((((srcClr & 0xFF00FF) * amount + rbClr) & 0xFF00FF00) + (((srcClr & 0x00FF00) * amount + gClr) & 0x00FF0000)) >> 8;

				::SetPixelV( hMemDC, x, y, dstClr );
			}
		}
	}

	::BitBlt( hDC, offsetX, offsetY, width, height, hMemDC, 0, 0, SRCCOPY );

	::SelectObject( hMemDC2, hOldBmp2 );
	::DeleteObject( hMemBmp2 );

	::SelectObject( hMemDC, hOldBmp );
	::DeleteObject( hMemBmp );

	::DeleteDC( hMemDC2 );
	::DeleteDC( hMemDC );
}

RWTHEMEAPI(void) RWDrawDCFullImageShadow( HDC hDC, UINT offsetX, UINT offsetY, UINT width, UINT height, HDC hBmpDC, UINT bmpOffsetX, UINT bmpOffsetY, COLORREF transColor, COLORREF shadowColor )
{
	HDC		hMemDC = ::CreateCompatibleDC( hDC );
	HDC		hMemDC2 = ::CreateCompatibleDC( hDC );
	HDC		hMemDCMono = ::CreateCompatibleDC( hDC );

	HBITMAP hMemBmp = ::CreateCompatibleBitmap( hDC, width, height );
	HBITMAP hMemBmp2 = ::CreateCompatibleBitmap( hDC, width, height );
	HBITMAP hMemBmpMono = ::CreateBitmap( width, height, 1, 1, NULL );

	HGDIOBJ hOldBmp = ::SelectObject( hMemDC, hMemBmp );
	HGDIOBJ hOldBmp2 = ::SelectObject( hMemDC2, hMemBmp2 );
	HGDIOBJ hOldBmpMono = ::SelectObject( hMemDCMono, hMemBmpMono );

	HBRUSH	hBrush, hOldBrush, hOldMBrush;

	UINT		x, y;
	COLORREF	srcClr, dstClr;

	::BitBlt( hMemDC2, 0, 0, width, height, hBmpDC, bmpOffsetX, bmpOffsetY, SRCCOPY );

	srcClr = ::GetPixel( hMemDC2, 0, 0 );
	transColor = ::SetPixel( hMemDC2, 0, 0, transColor );
	::SetPixelV( hMemDC2, 0, 0, srcClr );

	for( y = 0; y < height; y++ )
	{
		for( x = 0; x < width; x++ )
		{
			srcClr = GetPixel( hMemDC2, x, y );

			if( srcClr == transColor )
				srcClr = RGB( 255, 255, 255 );

			if( srcClr != 0 )
			{
				dstClr = (((srcClr & 0xFF0000)>>16)*gBlueWeight) + (((srcClr & 0x00FF00) >> 8) * gGreenWeight) + ((srcClr & 0x0000FF) * gRedWeight);

				if( dstClr > gShadowThreshold )
					dstClr = 0x00FFFFFF;
				else
					dstClr = 0x00000000;
		
				SetPixelV( hMemDC, x, y, dstClr );
			}
		}
	}

	hOldMBrush = (HBRUSH)::SelectObject( hMemDCMono, ::GetStockObject( BLACK_BRUSH ) );
    BitBlt( hMemDCMono, 0, 0, width, height, hMemDC, 0, 0, SRCCOPY );

	hBrush = ::CreateSolidBrush( shadowColor );
	hOldBrush = (HBRUSH)::SelectObject( hDC, hBrush );

	srcClr = ::SetTextColor( hDC, RGB( 255, 255, 255 ) );
	dstClr = ::SetBkColor( hDC, RGB( 0, 0, 0 ) );
	
	BitBlt( hDC, offsetX, offsetY, width, height, hMemDCMono, 0, 0, ROP_DSPDxax );

	::SelectObject( hMemDCMono, hOldMBrush ); 
	::SelectObject( hDC, hOldBrush ); ::DeleteObject( hBrush );

	::SetTextColor( hDC, srcClr );
	::SetBkColor( hDC, dstClr );

	::SelectObject( hMemDCMono, hOldBmpMono );
	::DeleteObject( hMemBmpMono );

	::SelectObject( hMemDC2, hOldBmp2 );
	::DeleteObject( hMemBmp2 );

	::SelectObject( hMemDC, hOldBmp );
	::DeleteObject( hMemBmp );

	::DeleteDC( hMemDCMono );
	::DeleteDC( hMemDC2 );
	::DeleteDC( hMemDC );
}

RWTHEMEAPI(void) RWDrawDCFlatImageShadow( HDC hDC, UINT offsetX, UINT offsetY, UINT width, UINT height, HDC hBmpDC, UINT bmpOffsetX, UINT bmpOffsetY, COLORREF transColor, COLORREF shadowColor )
{
	HDC		hMemDC = ::CreateCompatibleDC( hDC );
	HDC		hMemDC2 = ::CreateCompatibleDC( hDC );
	HDC		hMemDCMono = ::CreateCompatibleDC( hDC );

	HBITMAP hMemBmp = ::CreateCompatibleBitmap( hDC, width, height );
	HBITMAP hMemBmp2 = ::CreateCompatibleBitmap( hDC, width, height );
	HBITMAP hMemBmpMono = ::CreateBitmap( width, height, 1, 1, NULL );

	HGDIOBJ hOldBmp = ::SelectObject( hMemDC, hMemBmp );
	HGDIOBJ hOldBmp2 = ::SelectObject( hMemDC2, hMemBmp2 );
	HGDIOBJ hOldBmpMono = ::SelectObject( hMemDCMono, hMemBmpMono );

	HBRUSH	hBrush, hOldBrush, hOldMBrush;

	UINT		x, y;
	COLORREF	srcClr, dstClr;

	::BitBlt( hMemDC2, 0, 0, width, height, hBmpDC, bmpOffsetX, bmpOffsetY, SRCCOPY );

	srcClr = ::GetPixel( hMemDC2, 0, 0 );
	transColor = ::SetPixel( hMemDC2, 0, 0, transColor );
	::SetPixelV( hMemDC2, 0, 0, srcClr );

	for( y = 0; y < height; y++ )
	{
		for( x = 0; x < width; x++ )
		{
			srcClr = GetPixel( hMemDC2, x, y );
			if( srcClr == transColor )
				srcClr = 0x00FFFFFF;
			else
				srcClr = 0x00000000;

			SetPixelV( hMemDC, x, y, srcClr );
		}
	}

	hOldMBrush = (HBRUSH)::SelectObject( hMemDCMono, ::GetStockObject( BLACK_BRUSH ) );
    BitBlt( hMemDCMono, 0, 0, width, height, hMemDC, 0, 0, SRCCOPY );

	hBrush = ::CreateSolidBrush( shadowColor );
	hOldBrush = (HBRUSH)::SelectObject( hDC, hBrush );

	srcClr = ::SetTextColor( hDC, RGB( 255, 255, 255 ) );
	dstClr = ::SetBkColor( hDC, RGB( 0, 0, 0 ) );
	
	BitBlt( hDC, offsetX, offsetY, width, height, hMemDCMono, 0, 0, ROP_DSPDxax );

	::SelectObject( hMemDCMono, hOldMBrush ); 
	::SelectObject( hDC, hOldBrush ); ::DeleteObject( hBrush );

	::SetTextColor( hDC, srcClr );
	::SetBkColor( hDC, dstClr );

	::SelectObject( hMemDCMono, hOldBmpMono );
	::DeleteObject( hMemBmpMono );

	::SelectObject( hMemDC2, hOldBmp2 );
	::DeleteObject( hMemBmp2 );

	::SelectObject( hMemDC, hOldBmp );
	::DeleteObject( hMemBmp );

	::DeleteDC( hMemDCMono );
	::DeleteDC( hMemDC2 );
	::DeleteDC( hMemDC );
}

RWTHEMEAPI(BOOL) RWPaintGradientRect(HDC hdcDest, UINT offsetX, UINT offsetY, UINT width, UINT height, COLORREF color1, COLORREF color2, BOOL vertical)
{
	RECT		rStep;
	COLORREF	color;
	float		fStep			= 0.0f;
	float		fNumSteps		= 255.0f;
	BOOL		bVerticalColor	= !vertical;
	
	// Determine our step value
	if(bVerticalColor)
	{
		// Height of the color's band
		fStep = ((float)height)/fNumSteps;	
	}else
	{
		// Width of the color's band
		fStep = ((float)width)/fNumSteps;	
	}

	for (int iBand = 0; iBand < fNumSteps; iBand++) 
	{
		// Set current band
		if(bVerticalColor)
		{
			// Vertical Band
			rStep.left		= offsetX;
			rStep.top		= offsetY + (int)(iBand * fStep);
			rStep.right		= offsetX + width;
			rStep.bottom	= offsetY + (int)((iBand+1)* fStep);
		}
		else
		{
			// Horizontal Band
			rStep.left		= offsetX + (int)(iBand * fStep);
			rStep.top		= offsetY;
			rStep.right		= offsetX + (int)((iBand+1)* fStep);
			rStep.bottom	= offsetY + height;
		}

		// Set current color
		color = RGB((GetRValue(color1)-GetRValue(color2))*((float)iBand)/fNumSteps+GetRValue(color2),
			        (GetGValue(color1)-GetGValue(color2))*((float)iBand)/fNumSteps+GetGValue(color2),
			        (GetBValue(color1)-GetBValue(color2))*((float)iBand)/fNumSteps+GetBValue(color2));

		// Create Brushes
		HBRUSH hOldBrush	= NULL;
		HBRUSH hRectBrush	= NULL;
		hRectBrush = ::CreateSolidBrush(color);
		hOldBrush  = (HBRUSH)::SelectObject(hdcDest, hRectBrush);

		// Fill the current band
		::FillRect(hdcDest, &rStep, hRectBrush);

		// Clean up
		::SelectObject(hdcDest, hOldBrush);
		::DeleteObject(hRectBrush);

	}// End For
	return TRUE;
}
