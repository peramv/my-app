///////////////////////////////////////////////////////////////////////////////
// gxprndi.cpp : serializable printer settings
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

#include "grid\gxabstr.h"

#ifndef _GXEXT_H_
#include "grid\gxext.h"
#endif

#ifndef _AFXPRIV_H_
#include "afxpriv.h"
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXPRNDEV")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

#if _MFC_VER_ <= 0x0250
#define DWPORT  UINT
#else
#define DWPORT  DWORD
#endif

/////////////////////////////////////////////////////////////////////////////
// CWinAppEx

class CGXWinAppEx: public CWinApp
{
	// I need access to the protected members
	// m_hDevMode and m_hDevNames of CWinApp
	friend class CGXPrintDeviceImp;
};

////////////////////////////////////////////////////////////////////////////
// AfxCreateDC

#if _MFC_VER < 0x0400

HDC AFXAPI GXCreateDC(HGLOBAL hDevNames, HGLOBAL hDevMode)
{
	if (hDevNames == NULL)
		return NULL;

	LPDEVNAMES lpDevNames = (LPDEVNAMES)::GlobalLock(hDevNames);
	LPDEVMODE  lpDevMode = (hDevMode != NULL) ?
						(LPDEVMODE)::GlobalLock(hDevMode) : NULL;

	if (lpDevNames == NULL)
		return NULL;

	HDC hDC = ::CreateDC((LPCTSTR)lpDevNames + lpDevNames->wDriverOffset,
					  (LPCTSTR)lpDevNames + lpDevNames->wDeviceOffset,
					  (LPCTSTR)lpDevNames + lpDevNames->wOutputOffset,
					  lpDevMode);

	::GlobalUnlock(hDevNames);
	if (hDevMode != NULL)
		::GlobalUnlock(hDevMode);
	return hDC;
}

#else

#define GXCreateDC AfxCreateDC

#endif


class CGXPrintDeviceImp: public CGXAbstractPrintDeviceImp
{
public:
	virtual void UpdatePrinterDevice(CGXPrintDevice* pd);
	virtual int DoPrintDialog(CGXPrintDevice* pDevice, CPrintDialog* pPD);
	virtual BOOL DoPreparePrinting(CView* pView, CGXPrintDevice* pDevice, CPrintInfo* pInfo);
	virtual void CreateDeviceHandles(CGXPrintDevice* pDevice, LPDEVNAMES pDevNames, DWORD cbSizeDevNames, LPDEVMODE pDevMode, DWORD cbSizeDevMode);
	virtual void CreateDeviceHandles(CGXPrintDevice* pDevice, HGLOBAL hDN, HGLOBAL hDM);
	virtual void DestroyDeviceHandles(CGXPrintDevice* pDevice);
	virtual void GetDeviceInfo(CGXPrintDevice* pDevice, HGLOBAL hDN, HGLOBAL hDM, LPDEVNAMES& pDevNames, DWORD &cbSizeDevNames, LPDEVMODE& pDevMode, DWORD& cbSizeDevMode);
	virtual void GetDefaults(CGXPrintDevice* pDevice);
	virtual HDC GetPrintDC(CGXPrintDevice* pDevice);
	virtual void ResetPrintDC(CGXPrintDevice* pDevice);
	virtual void CopyDeviceHandles(CGXPrintDevice* pDevice, HGLOBAL& hDN, HGLOBAL& hDM);
	virtual BOOL CompareDeviceHandles(CGXPrintDevice* pDevice, LPDEVNAMES pDevNames, DWORD cbSizeDevNames, LPDEVMODE pDevMode, DWORD cbSizeDevMode);
	virtual BOOL CompareDeviceHandles(CGXPrintDevice* pDevice, HGLOBAL hDN, HGLOBAL hDM);
};

void AFXAPI CGXPrintDevice::ImplementPrintDevice()
{
	if (GXGetAppData()->m_pPrintDeviceImp == NULL)
	{
		//GXGetAppData()->AutoDeletePtr(GXGetAppData()->m_pPrintDeviceImp = new CGXPrintDeviceImp);
		GXGetAppData()->m_pPrintDeviceImp = new CGXPrintDeviceImp;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CGXPrintDeviceImp

void CGXPrintDeviceImp::UpdatePrinterDevice(CGXPrintDevice* pd)
{
	CGXWinAppEx* pApp = (CGXWinAppEx*) AfxGetApp();

	// TRACE0("UpdatePrinterDevice()\n");
	ASSERT(pd);

	// It is a known problem that BoundsChecker eventually
	// complains about freeing un unlocked handle at the
	// next line.
	//
	// The reason for this complaint is that the
	// CWinApp::UpdatePrinterSelection (VC 4.0 or eralier,
	// called from CWinApp::DoPrintDialog) forgets to unlock
	// pApp->m_hDevNames. As this has no further side effects
	// you need not worry about this complaint.
	if (pApp->m_hDevNames)
		::GlobalFree(pApp->m_hDevNames);
	pApp->m_hDevNames = 0;

	if (pApp->m_hDevMode)
		::GlobalFree(pApp->m_hDevMode);
	pApp->m_hDevMode = 0;

	pd->CopyDeviceHandles(pApp->m_hDevNames, pApp->m_hDevMode);
}

int CGXPrintDeviceImp::DoPrintDialog(CGXPrintDevice* pDevice, CPrintDialog* pPD)
{
	if (pDevice)
	{
		CGXWaitCursor theWait;

		pDevice->NeedDeviceHandles();

		UpdatePrinterDevice(pDevice);

		int nResponse = (int)AfxGetApp()->DoPrintDialog(pPD);

		if (nResponse == IDOK)
		{
			pDevice->CreateDeviceHandles(pPD->m_pd.hDevNames, pPD->m_pd.hDevMode);
		}

		return nResponse;
	}

	return 0;
}

BOOL CGXPrintDeviceImp::DoPreparePrinting(CView* pView, CGXPrintDevice* pDevice, CPrintInfo* pInfo)
{
	if (pDevice)
	{
		CGXWaitCursor theWait;

		pDevice->NeedDeviceHandles();
		UpdatePrinterDevice(pDevice);

		if (pView->CView::DoPreparePrinting(pInfo))
		{
			if (!pDevice->CompareDeviceHandles(pInfo->m_pPD->m_pd.hDevNames, pInfo->m_pPD->m_pd.hDevMode))
				pDevice->CreateDeviceHandles(pInfo->m_pPD->m_pd.hDevNames, pInfo->m_pPD->m_pd.hDevMode);

			return TRUE;
		}

		return FALSE;
	}

	// No PrintDevice-Object
	return pView->CView::DoPreparePrinting(pInfo);
}

void CGXPrintDeviceImp::CreateDeviceHandles(
	CGXPrintDevice* pDevice,											
	LPDEVNAMES pDevNames,
	DWORD cbSizeDevNames,
	LPDEVMODE pDevMode,
	DWORD cbSizeDevMode)
{
	// alloc and copy DEVNAMES structure

	BOOL bThrowException = FALSE;

	pDevice->DestroyDeviceHandles();

	if (cbSizeDevNames > 0)
	{
		pDevice->m_hDevNames = GlobalAlloc(GMEM_MOVEABLE | GMEM_DISCARDABLE, cbSizeDevNames);
		if (pDevice->m_hDevNames)
		{
			char* p = (char*) GlobalLock(pDevice->m_hDevNames);
			memcpy(p, pDevNames, (DWPORT) cbSizeDevNames);
			GlobalUnlock(pDevice->m_hDevNames);
		}
		else
			bThrowException = TRUE;
	}

	// alloc and copy DEVMODE structure
	if (cbSizeDevMode > 0)
	{
		pDevice->m_hDevMode = GlobalAlloc( GMEM_MOVEABLE | GMEM_DISCARDABLE,
			cbSizeDevMode);

		if (pDevice->m_hDevMode)
		{
			char* p = (char*) GlobalLock(pDevice->m_hDevMode);
			memcpy(p, pDevMode, (DWPORT) cbSizeDevMode);
			GlobalUnlock(pDevice->m_hDevMode);
		}
		else
			bThrowException = TRUE;
	}

	if (bThrowException)
		::AfxThrowMemoryException();
}

void CGXPrintDeviceImp::CreateDeviceHandles(CGXPrintDevice* pDevice,
	HGLOBAL hDN,
	HGLOBAL hDM)
{
	DWORD cbSizeDevNames = 0;
	LPDEVNAMES pDevNames = 0;

	DWORD cbSizeDevMode = 0;
	LPDEVMODE pDevMode = 0;

	if (hDN)
	{
		cbSizeDevNames = (DWORD)GlobalSize(hDN);
		pDevNames = (LPDEVNAMES) GlobalLock(hDN);
	}

	if (hDM)
	{
		cbSizeDevMode = (DWORD)GlobalSize(hDM);
		pDevMode = (LPDEVMODE) GlobalLock(hDM);
	}

	pDevice->CreateDeviceHandles(
		pDevNames,
		cbSizeDevNames,
		pDevMode,
		cbSizeDevMode);

	if (hDM)
		GlobalUnlock(hDM);

	if (hDN)
		GlobalUnlock(hDN);
}

void CGXPrintDeviceImp::DestroyDeviceHandles(CGXPrintDevice* pDevice)
{
	pDevice->ResetPrintDC();

	// DevNames
	if (pDevice->m_hDevNames)
	{
		GlobalFree(pDevice->m_hDevNames);
		pDevice->m_hDevNames = NULL;
	}

	// DevMode
	if (pDevice->m_hDevMode)
	{
		GlobalFree(pDevice->m_hDevMode);
		pDevice->m_hDevMode = 0;
	}
}


void CGXPrintDeviceImp::GetDeviceInfo(CGXPrintDevice* pDevice, 
	HGLOBAL hDN,
	HGLOBAL hDM,
	LPDEVNAMES& pDevNames,
	DWORD &cbSizeDevNames,
	LPDEVMODE& pDevMode,
	DWORD& cbSizeDevMode)
{
	GX_UNUSED_ALWAYS(pDevice);

	if (hDN)
	{
		cbSizeDevNames = (DWORD)GlobalSize(hDN);
		pDevNames = (LPDEVNAMES) new char [cbSizeDevNames];
		char* p = (char*) GlobalLock(hDN);
		memcpy(pDevNames, p, (DWPORT) cbSizeDevNames);
		GlobalUnlock(hDN);
	}
	else
	{
		pDevNames = 0;
		cbSizeDevNames = 0;
	}

	if (hDM)
	{
		cbSizeDevMode = (DWORD)GlobalSize(hDM);
		pDevMode = (LPDEVMODE) new char [cbSizeDevMode];
		char* p = (char*) GlobalLock(hDM);
		memcpy(pDevMode, p, (DWPORT) cbSizeDevMode);
		GlobalUnlock(hDM);
	}
	else
	{
		pDevMode = 0;
		cbSizeDevMode = 0;
	}
}

void CGXPrintDeviceImp::GetDefaults(CGXPrintDevice* pDevice)
{
	// initialize default printer settings
	CPrintDialog pd(TRUE);

	if (pd.GetDefaults())
	{
		// dmTTOption - Specifies how TrueType fonts should be printed.
		// DMTT_BITMAP is for printing as bitmap
		if (pd.m_pd.hDevMode)
		{
			LPDEVMODE pDevMode = (LPDEVMODE) GlobalLock(pd.m_pd.hDevMode);
			pDevMode->dmTTOption = DMTT_BITMAP;
			GlobalUnlock(pd.m_pd.hDevMode);
		}

		pDevice->CreateDeviceHandles(pd.m_pd.hDevNames, pd.m_pd.hDevMode);
	}
}

HDC CGXPrintDeviceImp::GetPrintDC(CGXPrintDevice* pDevice)
{
	if (pDevice == NULL)
		return 0;

	if (pDevice->m_hPrintDC == 0)
	{
		pDevice->NeedDeviceHandles();
		pDevice->m_hPrintDC = GXCreateDC(pDevice->m_hDevNames, pDevice->m_hDevMode);
	}

	return pDevice->m_hPrintDC;
}

void CGXPrintDeviceImp::ResetPrintDC(CGXPrintDevice* pDevice)
{
	if (pDevice->m_hPrintDC)
		::DeleteObject(pDevice->m_hPrintDC);

	pDevice->m_hPrintDC = 0;
}

void CGXPrintDeviceImp::CopyDeviceHandles(CGXPrintDevice* pDevice, HGLOBAL& hDN, HGLOBAL& hDM)
{
	LPDEVNAMES pDevNames = 0;
	DWORD cbSizeDevNames = 0;

	LPDEVMODE pDevMode = 0;
	DWORD cbSizeDevMode = 0;

	pDevice->GetDeviceInfo(pDevNames, cbSizeDevNames, pDevMode, cbSizeDevMode);

	hDN = hDM = 0;
	if (cbSizeDevNames == 0)    // no printer
		return;

	// alloc and copy DevNames structure
	hDN = GlobalAlloc(GMEM_MOVEABLE | GMEM_DISCARDABLE, cbSizeDevNames);

	if (hDN)
	{
		char* p = (char*) GlobalLock(hDN);
		memcpy(p, pDevNames, (DWPORT) cbSizeDevNames);
		GlobalUnlock(hDN);
	}

	// alloc and copy DevMode structure
	if (pDevMode)
	{
		hDM = GlobalAlloc( GMEM_MOVEABLE | GMEM_DISCARDABLE,
			cbSizeDevMode);

		if (hDM)
		{
			char* p = (char*) GlobalLock(hDM);
			memcpy(p, pDevMode, (DWPORT) cbSizeDevMode);
			GlobalUnlock(hDM);
		}
	}

	delete pDevNames;
	delete pDevMode;

	if (hDN == 0 || pDevMode && hDM == 0)
		::AfxThrowMemoryException();
}

BOOL CGXPrintDeviceImp::CompareDeviceHandles(CGXPrintDevice* pDevice, 
	LPDEVNAMES pDevNames,
	DWORD cbSizeDevNames,
	LPDEVMODE pDevMode,
	DWORD cbSizeDevMode)
{
	BOOL bEqual = TRUE;

	if (pDevice->m_hDevNames)
	{
		DWORD cbSize = (DWORD)GlobalSize(pDevice->m_hDevNames);
		if (cbSize == cbSizeDevNames)
		{
			char* p = (char*) GlobalLock(pDevice->m_hDevNames);
			if (memcmp(p, pDevNames, (DWPORT) cbSizeDevNames) != 0)
				bEqual = FALSE;
			GlobalUnlock(pDevice->m_hDevNames);
		}
		else
			bEqual = FALSE;
	}
	else
		bEqual = (cbSizeDevNames == 0);

	if (!bEqual)
		return FALSE;

	if (pDevice->m_hDevMode)
	{
		DWORD cbSize = (DWORD)GlobalSize(pDevice->m_hDevMode);
		if (cbSize == cbSizeDevMode)
		{
			char* p = (char*) GlobalLock(pDevice->m_hDevMode);
			if (memcmp(p, pDevMode, (DWPORT) cbSizeDevMode) != 0)
				bEqual = FALSE;
			GlobalUnlock(pDevice->m_hDevMode);
		}
		else
			bEqual = FALSE;
	}
	else
		bEqual = (cbSizeDevMode == 0);

	return bEqual;
}

BOOL CGXPrintDeviceImp::CompareDeviceHandles(CGXPrintDevice* pDevice, HGLOBAL hDN, HGLOBAL hDM)
{
	LPDEVNAMES pDevNames = 0;
	DWORD cbSizeDevNames = 0;

	LPDEVMODE pDevMode = 0;
	DWORD cbSizeDevMode = 0;

	pDevice->GetDeviceInfo(hDN, hDM, pDevNames, cbSizeDevNames, pDevMode, cbSizeDevMode);

	BOOL bEqual = pDevice->CompareDeviceHandles(
		pDevNames,
		cbSizeDevNames,
		pDevMode,
		cbSizeDevMode);

	delete pDevNames;
	delete pDevMode;

	return bEqual;
}
