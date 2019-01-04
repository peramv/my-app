///////////////////////////////////////////////////////////////////////////////
// gxprndev.cpp : serializable printer settings
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

#ifndef _AFXPRIV_H_
#include <afxpriv.h>
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

IMPLEMENT_SERIAL(CGXPrintDevice, CObject, 1)

#if _MFC_VER_ <= 0x0250
#define DWPORT  UINT
#else
#define DWPORT  DWORD
#endif

////////////////////////////////////////////////////////////////////////////////
// CGXPrintDevice constructor/destructor

CGXPrintDevice::CGXPrintDevice()
{
	CGXAppData* pAppData = GXGetAppData();

	ASSERT(pAppData->m_bInitDone);
	// ASSERTION-> This constructor is called before the GXInit()
	// method has been called. This can be problematic because
	// at this time no factory object is available.
	//
	// Make sure you didn't simply forget to call GXInit() from
	// your application's InitInstance method. 
	//
	// Another reason for this problem can be that the object is 
	// constructed at the same time that your application object 
	// is instantiated, for example if you embedded this class 
	// as member variable in the application class. 
	// 
	// To resolve the problem we recommend you instantiate the
	// object on the heap. Change your class declaration and
	// declare a pointer to this class. After GXInit() has been
	// called you can call m_pPrnDev = new CGXPrintDevice. In your
	// class destructor don't forget to delete m_pPrnDev.
	// ->END

	m_hDevMode = 0;
	m_hDevNames = 0;
	m_hPrintDC = 0;

	m_pPrintDeviceImp = pAppData->m_pPrintDeviceImp;
}

CGXPrintDevice::~CGXPrintDevice()
{
	DestroyDeviceHandles();
}

CGXPrintDevice::CGXPrintDevice(const CGXPrintDevice& pd)
{
	m_hDevMode = 0;
	m_hDevNames = 0;
	CreateDeviceHandles(pd.m_hDevNames, pd.m_hDevMode);
}

CGXPrintDevice& CGXPrintDevice::operator=(const CGXPrintDevice& pd)
{
	if (&pd == this)
		return *this;

	CreateDeviceHandles(pd.m_hDevNames, pd.m_hDevMode);
	return *this;
}

/////////////////////////////////////////////////////////////////////////////
// CGXPrintDevice serialization

void CGXPrintDevice::Serialize(CArchive& ar)
{
	ASSERT_VALID(this);

	static const WORD wVersion = 1;
	WORD wActualVersion = wVersion;

	ASSERT_VALID( this );

	if (ar.IsStoring())
	{
		ar << wVersion;
	}
	else
	{
		// Check for version first
		ar >> wActualVersion;
		if( wActualVersion != wVersion )
		{
			// Wrong version
#ifdef _DEBUG
			TRACE0("Incompatible format while reading CGXPrintDevice" );
			TRACE2("in %s at line %d\n", __FILE__, __LINE__);
#endif
			AfxThrowArchiveException(CArchiveException::badSchema);
			return;
		}
	}

	LPDEVNAMES pDevNames = 0;
	DWORD cbSizeDevNames = 0;

	LPDEVMODE pDevMode = 0;
	DWORD cbSizeDevMode = 0;

	if (ar.IsStoring())
	{
		GetDeviceInfo(pDevNames, cbSizeDevNames, pDevMode, cbSizeDevMode);

		// DevNames structure
		ar << cbSizeDevNames;
		if (cbSizeDevNames > 0)
			ar.Write(pDevNames, (DWPORT) cbSizeDevNames);

		// DevMode structure
		ar << cbSizeDevMode;
		if (cbSizeDevMode > 0)
			ar.Write(pDevMode, (DWPORT) cbSizeDevMode);

		delete pDevNames;
		delete pDevMode;
	}
	else
	{
		// DevNames structure
		ar >> cbSizeDevNames;
		if (cbSizeDevNames > 0)
		{
			pDevNames = (LPDEVNAMES) new char [cbSizeDevNames];
			ar.Read(pDevNames, (DWPORT) cbSizeDevNames);
		}

		// DevMode structure
		ar >> cbSizeDevMode;
		if (cbSizeDevMode > 0)
		{
			pDevMode = (LPDEVMODE) new char [cbSizeDevMode];
			ar.Read(pDevMode, (DWPORT) cbSizeDevMode);
		}

		// Handles
		CreateDeviceHandles((LPDEVNAMES) pDevNames,
			cbSizeDevNames,
			(LPDEVMODE) pDevMode,
			cbSizeDevMode);

		delete pDevNames;
		delete pDevMode;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CGXPrintDevice diagnostics

#ifdef _DEBUG
void CGXPrintDevice::AssertValid() const
{
	CObject::AssertValid();

	ASSERT(!(m_hDevNames == 0 && m_hDevMode != 0));
}

void CGXPrintDevice::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);

	dc << _T("\nm_hDevMode = ") << (SEC_UINT)m_hDevMode;
	dc << _T("\nm_hDevNames = ") << (SEC_UINT)m_hDevNames;
	dc << _T("\nm_hPrintDC = ") << (SEC_UINT)m_hPrintDC;
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGXPrintDevice operations

void CGXPrintDevice::CreateDeviceHandles(
	LPDEVNAMES pDevNames,
	DWORD cbSizeDevNames,
	LPDEVMODE pDevMode,
	DWORD cbSizeDevMode)
{
	if (m_pPrintDeviceImp)
		m_pPrintDeviceImp->CreateDeviceHandles(
			this,
			pDevNames,
			cbSizeDevNames,
			pDevMode,
			cbSizeDevMode);
}

void CGXPrintDevice::CreateDeviceHandles(
	HGLOBAL hDN,
	HGLOBAL hDM)
{
	if (m_pPrintDeviceImp)
		m_pPrintDeviceImp->CreateDeviceHandles(this, hDN, hDM);
}

void CGXPrintDevice::DestroyDeviceHandles()
{
	if (m_pPrintDeviceImp)
		m_pPrintDeviceImp->DestroyDeviceHandles(this);
}

void CGXPrintDevice::GetDeviceInfo(
	HGLOBAL hDN,
	HGLOBAL hDM,
	LPDEVNAMES& pDevNames,
	DWORD &cbSizeDevNames,
	LPDEVMODE& pDevMode,
	DWORD& cbSizeDevMode)
{
	if (m_pPrintDeviceImp)
		m_pPrintDeviceImp->GetDeviceInfo(this, hDN, hDM, pDevNames, cbSizeDevNames, pDevMode, cbSizeDevMode);
}

void CGXPrintDevice::GetDeviceInfo(
	LPDEVNAMES& pDevNames,
	DWORD &cbSizeDevNames,
	LPDEVMODE& pDevMode,
	DWORD& cbSizeDevMode)
{
	GetDeviceInfo(m_hDevNames, m_hDevMode, pDevNames, cbSizeDevNames, pDevMode, cbSizeDevMode);
}

void CGXPrintDevice::GetDefaults()
{
	if (m_pPrintDeviceImp)
		m_pPrintDeviceImp->GetDefaults(this);
}

void CGXPrintDevice::NeedDeviceHandles()
{
	if (m_hDevNames == 0)
		GetDefaults();
}

HDC CGXPrintDevice::GetPrintDC()
{
	GX_CHECKIMP(m_pPrintDeviceImp, "CGXPrintDevice::GetPrintDC");

	if (m_pPrintDeviceImp)
		return m_pPrintDeviceImp->GetPrintDC(this);

	return 0;
}

void CGXPrintDevice::ResetPrintDC()
{
	GX_CHECKIMP(m_pPrintDeviceImp, "CGXPrintDevice::ResetPrintDC");

	if (m_pPrintDeviceImp)
		m_pPrintDeviceImp->ResetPrintDC(this);

	m_hPrintDC = 0;
}

void CGXPrintDevice::CopyDeviceHandles(HGLOBAL& hDN, HGLOBAL& hDM)
{
	if (m_pPrintDeviceImp)
		m_pPrintDeviceImp->CopyDeviceHandles(this, hDN, hDM);
}

BOOL CGXPrintDevice::CompareDeviceHandles(
	LPDEVNAMES pDevNames,
	DWORD cbSizeDevNames,
	LPDEVMODE pDevMode,
	DWORD cbSizeDevMode)
{
	if (m_pPrintDeviceImp)
		return m_pPrintDeviceImp->CompareDeviceHandles(this, 
			pDevNames,
			cbSizeDevNames,
			pDevMode,
			cbSizeDevMode);

	return FALSE;
}

BOOL CGXPrintDevice::CompareDeviceHandles(HGLOBAL hDN, HGLOBAL hDM)
{
	if (m_pPrintDeviceImp)
		return m_pPrintDeviceImp->CompareDeviceHandles(this, hDN, hDM);

	return FALSE;
}
