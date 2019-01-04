///////////////////////////////////////////////////////////////////////////////
// gxddib.cpp : support class for bitmap rendering
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

#define _OG_EXPORT_IMPL

#include "stdafx.h"

#if _MFC_VER >= 0x0400 

#ifdef _GXDLL
// used for MFC 2.5 Extension DLL
	#undef AFXAPI_DATA
	#define AFXAPI_DATA __based(__segname("_DATA"))
#endif

#ifndef _GXDDIB_H_
#include "grid\gxddib.h"
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


CGXDataDib::CGXDataDib()
{
}

CGXDataDib::~CGXDataDib()
{
}

// Renders the bitmap. The actual rendering code is in the base class.
// This just locates the bitmap and then calls the drawing code
// After rendering it frees the associated global memory
// memory handle returned must be freed by the caller if bFree is FALSE (the default)
HANDLE CGXDataDib::Draw(CDC* pDC, const COleVariant& var, LPRECT lpRect, int nStretchFlags, 
						UINT ntAlign, LPRECT lpSrc, HANDLE hBitmap, BOOL bFree /* = FALSE*/)
{
	HANDLE hBmp = hBitmap ? hBitmap:LocateBitmap(var);
	
	if(hBmp)
	{
		CGXDIB::Draw(pDC, hBmp, lpRect, nStretchFlags, ntAlign, lpSrc);
		if(bFree)
			GlobalFree(hBmp);
	}	
	else
		TRACE0("Call to CGXDataDib::Draw fails\n");
	
	return hBmp;
}

// Locates the bitmap in a blob of data
// returns NULL if unable to locate bitmap
HANDLE CGXDataDib::LocateBitmap(const COleVariant& var, BOOL bIncludeFileHeader /*= FALSE*/)
{
	HANDLE hBitmap = NULL;
	
	const VARIANT* pV = (const VARIANT*) var; 
	
	ASSERT(pV->vt == (VT_ARRAY|VT_UI1));

	if(pV->vt == (VT_ARRAY|VT_UI1))  // (OLE SAFEARRAY)
	{
		//Retrieve size of array
		unsigned long cDimLength = pV->parray->rgsabound[0].cElements;
		
		BYTE* pBuffer = new BYTE[cDimLength];
	
		if(pBuffer != NULL)
		{
			void* pvArrayData = NULL;
				
			//Obtain safe pointer to the array
			SafeArrayAccessData(pV->parray,&pvArrayData);
				
			//Copy the bitmap into our buffer
			memcpy(pBuffer, pvArrayData, cDimLength);
				
			//Unlock the variant data
			SafeArrayUnaccessData(pV->parray);
		}
		else
			return NULL;

		BOOL bSearch = FALSE;
			
		BYTE* pBuf = pBuffer;
		BYTE* pBmp = NULL;
		ULONG cL = cDimLength;

		while (!bSearch)
		{
			BYTE* p = (BYTE*) memchr(pBuf, 'B', cL);
			BYTE* p1 = (BYTE*) memchr(p, 'M', cL - (pBuf - p));
				
			if( (p1 - p) == 1)
			{
				bSearch = TRUE;
				pBmp = p;
			}
			else
			{
				cL = cL - (pBuf - p - 1);
				pBuf = p + 1;
			}
		}

		if(pBmp && ((LPBITMAPFILEHEADER)pBmp)->bfType != 0x4d42) 
			TRACE(_T("CGXDataDib::READ fails...Bitmap File not readable!"));
		else
		{
			ULONG nOffset = bIncludeFileHeader ? 0:sizeof(BITMAPFILEHEADER);
			HGLOBAL hGlobal = ::GlobalAlloc(GHND, cDimLength - ( pBmp-pBuffer ) - nOffset );
			ASSERT(hGlobal);
			
			BYTE* lpNew = (BYTE*)::GlobalLock(hGlobal);
			ASSERT(lpNew);
			
			if(lpNew)
				memcpy(lpNew, pBmp + nOffset, (size_t) cDimLength- ( pBmp-pBuffer ) - nOffset );
			

			::GlobalUnlock(hGlobal);
			
			hBitmap = (HANDLE) hGlobal;
		}
		
		if(pBuffer != NULL)
			delete[] pBuffer;
		return hBitmap;
	}
	else 
	{
		TRACE0("Error: Bitmap data not in required format\n");
		return NULL;
	}	
}

#endif // _MFC_VER >= 0x0400 
