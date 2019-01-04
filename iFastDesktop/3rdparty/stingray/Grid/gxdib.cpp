///////////////////////////////////////////////////////////////////////////////
// gxdib.cpp : device independant bitmaps
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

#include "grid\gxresrc.h"

#ifndef _GEXT_H_
#include "grid\gxext.h"
#endif

#include <ctype.h>

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifndef _GXDLL
	// QA: 32120 - Wrapping with CThreadLocal.
	CThreadLocal<GX_DIB_STATE> GXNEAR _gxDIBState;
#endif

IMPLEMENT_DYNCREATE(CGXDIB, CObject)
IMPLEMENT_DYNAMIC(CGXDIBPool, CObject)

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXDIB")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

GX_DIB_STATE::GX_DIB_STATE()
{
	m_pDIBPool = NULL;
}

GX_DIB_STATE::~GX_DIB_STATE()
{
	if (m_pDIBPool)
		m_pDIBPool->EmptyPool();
	delete m_pDIBPool;
}

CGXDIBPool* GX_DIB_STATE::GetPool()
{
	if (m_pDIBPool == NULL)
		m_pDIBPool = new CGXDIBPool;

	return m_pDIBPool;
}

CGXDIB::CGXDIB()
{
	m_hbm = NULL;
	m_bGDIObject = TRUE;
}

CGXDIB::~CGXDIB()
{
	DestroyDIB();
}

void CGXDIB::DestroyDIB()
{
	if (m_hbm)
	{
		if(m_bGDIObject)
			::DeleteObject(m_hbm);
		else
			::GlobalFree((HANDLE)m_hbm);
	}
	
	// reset to default
	m_bGDIObject = TRUE;
}

BOOL CGXDIB::Attach(HANDLE hObject)
{
	DestroyDIB();

	if (hObject == NULL)
		return FALSE;

	m_hbm = hObject;

	LPSTR lpDIB = (LPSTR) GlobalLock(m_hbm);
	BITMAPINFO* pBMI = (BITMAPINFO *) lpDIB;

	m_dwColors = GXGetNumDIBColorEntries(pBMI);
	m_nWidth = (int) pBMI->bmiHeader.biWidth;
	m_nHeight = (int) pBMI->bmiHeader.biHeight;

	GlobalUnlock(m_hbm);

	return TRUE;
}

HANDLE CGXDIB::Detach()
{
	HANDLE handle = m_hbm;
	m_hbm = NULL;
	return handle;
}

BOOL CGXDIB::LoadDIB(LPCTSTR lpszResourceName)
{
	// First, try resource handle
	HINSTANCE hInst = AfxFindResourceHandle(lpszResourceName, RT_BITMAP);
	HANDLE hBitmap = ::GXLoadResourceBitmap(hInst, lpszResourceName);

	// If failed, try instance handle
	if (hBitmap == 0)
		hBitmap = ::GXLoadResourceBitmap(AfxGetInstanceHandle(), lpszResourceName);

	if (hBitmap)
	{
		Attach(hBitmap);
		m_bGDIObject = FALSE;
	}

	return hBitmap != NULL;
}

void CGXDIB::Draw(CDC* pDC, LPRECT lpRect, int nStretchFlags, UINT ntAlign, LPRECT lpSrc)
{
	Draw(pDC, m_hbm, lpRect, nStretchFlags, ntAlign, lpSrc);
}

void CGXDIB::Draw(CDC* pDC, HANDLE hbm, LPRECT lpRect, int nStretchFlags, UINT ntAlign, LPRECT lpSrc)
{
	// Bitmap Info, width and height
	LPSTR lpDIB = (LPSTR) GlobalLock(hbm);
	BITMAPINFO* pBMI = (BITMAPINFO *) lpDIB;

	DWORD dwColors = GXGetNumDIBColorEntries(pBMI);
	int nWidth = (int) pBMI->bmiHeader.biWidth;
	int nHeight = (int) pBMI->bmiHeader.biHeight;

	CRect rcDest = *lpRect;
	CRect rcSrc(0, 0, nWidth, nHeight);

	if (lpSrc)
		rcSrc = *lpSrc;

	switch (nStretchFlags)
	{
	case asymmetric:
		// stretch to lpRect
		rcDest = *lpRect;
		break;

	case symmetric:
		{
			CRect rcDisp = *lpRect;

			// factor
			long lHorzFact = rcDest.Width()*1000L/rcSrc.Width();
			long lVertFact = rcDest.Height()*1000L/rcSrc.Height();
			long sf = min(lHorzFact, lVertFact);

			long lHeight = sf*rcSrc.Height()/1000L;
			long lWidth =  sf*rcSrc.Width()/1000L;

			rcDest.bottom = rcDest.top + (int) lHeight;
			rcDest.right = rcDest.left + (int) lWidth;

			if (rcDest.Width() < rcDisp.Width())
			{
				// center source rectangle
				int dx = rcDisp.Width() - rcDest.Width();

				if (ntAlign & DT_CENTER)
				{
					rcDest.left += dx/2;
					rcDest.right += dx/2;
				}
				else if (ntAlign & DT_RIGHT)
				{
					rcDest.left += dx;
					rcDest.right += dx;
				}
			}

			if (rcDest.Height() < rcDisp.Height())
			{
				// center source rectangle
				int dy = rcDisp.Height() - rcDest.Height();

				if (ntAlign & DT_VCENTER)
				{
					rcDest.top += dy/2;
					rcDest.bottom += dy/2;
				}
				else if (ntAlign & DT_BOTTOM)
				{
					rcDest.top += dy;
					rcDest.bottom += dy;
				}
			}
		}
		break;

	case none:
		{
			if (rcSrc.Width() < rcDest.Width())
			{
				// center source rectangle
				int dx = rcDest.Width() - rcSrc.Width();

				if (ntAlign & DT_CENTER)
				{
					rcDest.left += dx/2;
					rcDest.right -= dx-dx/2;
				}
				else if (ntAlign & DT_RIGHT)
				{
					rcDest.left += dx;
				}
				else
				{
					rcDest.right -= dx;
				}
			}
			else if (rcSrc.Width() != rcDest.Width())
			{
				// clip source rectangle
				rcSrc.right = rcSrc.left + rcDest.Width();
			}


			if (rcSrc.Height() < rcDest.Height())
			{
				// center source rectangle
				int dy = rcDest.Height() - rcSrc.Height();

				if (ntAlign & DT_VCENTER)
				{
					rcDest.top += dy/2;
					rcDest.bottom -= dy-dy/2;
				}
				else if (ntAlign & DT_BOTTOM)
				{
					rcDest.top += dy;
				}
				else
				{
					rcDest.bottom -= dy;
				}
			}
			else if (rcSrc.Height() != rcDest.Height())
			{
				// clip source rectangle
				if (ntAlign & DT_BOTTOM)
					rcSrc.bottom = rcSrc.top + rcDest.Height();
				else
					rcSrc.top = rcSrc.bottom - rcDest.Height();
			}
		}
		break;
	}

	// Look at color table size, and work out where image bits start
	DWORD dwColorTableSize = dwColors * sizeof(RGBQUAD);
	LPSTR pBits = lpDIB + sizeof(BITMAPINFOHEADER) + dwColorTableSize;

	::StretchDIBits(pDC->GetSafeHdc(),
					rcDest.left, rcDest.top,
					rcDest.Width(), rcDest.Height(),
					rcSrc.left, rcSrc.top,
					rcSrc.Width(), rcSrc.Height(),
					pBits,                    // Pointer to bits
					pBMI,                     // BITMAPINFO
					DIB_RGB_COLORS,           // Options
					SRCCOPY);                 // Raster operator code (ROP)

	::GlobalUnlock(hbm);
}


CGXDIBPool::CGXDIBPool()
{
	EmptyPool();
}

CGXDIBPool::~CGXDIBPool()
{
	EmptyPool();
}

HANDLE CGXDIBPool::LookupOrCreateDIB(const CString& key)
{
	void* vptr = 0;
	HANDLE hbm = 0;

	CString str;
	LPCTSTR pszResourceString = GetResourceString(key, str);

	if (pszResourceString)
	{
		if (m_mapDIBHandles.Lookup(str, vptr))
#ifdef _WIN32
			hbm = (HANDLE) vptr;
#else
			hbm = (HANDLE) (UINT) (LONG) vptr;
#endif
		else
		{
			hbm = LoadDIB(key, pszResourceString);
	                                           
			m_mapDIBHandles.SetAt(str, (void*) hbm);
		}

	}

	return hbm;
}

void CGXDIBPool::EmptyPool()
{       
	CString key;
	POSITION pos = m_mapDIBHandles.GetStartPosition();
	void* vptr;         
	while (pos != NULL)
	{
		m_mapDIBHandles.GetNextAssoc(pos, key, vptr);
		::GlobalFree((HANDLE) (SEC_UINT) (SEC_LONG) vptr);      
	}

	m_mapDIBHandles.RemoveAll();
}

const LPCTSTR szBmpResource = _T("#BMP(");
const LPCTSTR szBmpFile = _T("#FIL(");
const TCHAR chBlank = _T(' ');
const TCHAR chStrDel = _T('"');

LPCTSTR CGXDIBPool::GetResourceString(const CString& strValue, CString& strResource)
{
	LPCTSTR pszValue = strValue;
	int n = 0;

	if (_tcsnicmp(strValue, szBmpResource, n = (int)_tcslen(szBmpResource)) == 0)
	{
		// Is it a string .BMP("BITMAP")
		int n1 = strValue.Find(chStrDel);
		if (n1 != -1)
		{
			strResource = strValue.Mid(n1+1);

			int n2 = strResource.Find(chStrDel);

			if (n2 == -1)
				return NULL;

			strResource = strResource.Left(n2);

			return strResource;
		}
		// or a number .BMP(5001)
		else
		{
			UINT nID = _ttoi(pszValue+n);

			if (nID == 0)
				return NULL;

#if _MFC_VER >= 0x0253
			strResource.Format(_T("#%u"), nID);
#else
			wsprintf(strResource.GetBuffer(20), _T("#%u"), nID);
			strResource.ReleaseBuffer();
#endif

			return MAKEINTRESOURCE(nID);
		}
	}

	return NULL;
}

void CGXDIBPool::CreateValueString(UINT nID, CString& strRet)
{
#if _MFC_VER >= 0x0253
	strRet.Format(_T("%s%u)"), szBmpResource, nID);
#else
	wsprintf(strRet.GetBuffer(64), _T("%s%u)"), szBmpResource, nID);
	strRet.ReleaseBuffer();
#endif
}

void CGXDIBPool::CreateValueString(const CString& strResourceName, CString& strRet)
{
#if _MFC_VER >= 0x0253
	strRet.Format(_T("%s%c%u%c)"), szBmpResource, chStrDel, strResourceName, chStrDel);
#else
	wsprintf(strRet.GetBuffer(64), _T("%s%c%u%c)"), szBmpResource, chStrDel, strResourceName, chStrDel);
	strRet.ReleaseBuffer();
#endif
}

HANDLE CGXDIBPool::LoadDIB(const CString& , LPCTSTR lpszResourceName)
{
	// First, try resource handle
	HINSTANCE hInst = AfxFindResourceHandle(lpszResourceName, RT_BITMAP);
	HANDLE hBitmap = ::GXLoadResourceBitmap(hInst, lpszResourceName);

	// If failed, try instance handle
	if (hBitmap == 0)
		hBitmap = ::GXLoadResourceBitmap(AfxGetInstanceHandle(), lpszResourceName);

	return hBitmap;
}

