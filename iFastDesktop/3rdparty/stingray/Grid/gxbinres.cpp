///////////////////////////////////////////////////////////////////////////////
// gxbinres.cpp : loading CGXGridParam (or other CObjects) from
//                binary resources or files
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

#ifndef _AFXPRIV_H_
#include "afxpriv.h"
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXBINRES")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

CObject* AFXAPI GXCreateObjectFromFile(CFile& file, CRuntimeClass* pRuntimeClass)
{
	CArchive ar(&file, CArchive::load);

	CObject* pObj;

	TRY
	{
		ar >> pObj;

		if (pRuntimeClass)
		{
			if (!pObj->IsKindOf(pRuntimeClass))
			{
				delete pObj;
				pObj = NULL;
			}
		}
	}
	CATCH_ALL(e)
	{
		// Object cannnot be loaded
		pObj = NULL;
		GX_THROW_LAST
	}
	END_CATCH_ALL

	return pObj;
}

CObject* AFXAPI GXCreateObjectFromFile(LPCTSTR lpszFileName, CRuntimeClass* pRuntimeClass)
{
	CFile file;
	CFileException e;
	if( !file.Open(lpszFileName, CFile::modeRead, &e) )
	{
#ifdef _DEBUG
		afxDump << "File could not be opened " << e.m_cause << "\n";
#endif
		return NULL;
	}

	return GXCreateObjectFromFile(file, pRuntimeClass);
}

CObject* AFXAPI GXCreateObjectFromResource(LPCTSTR lpszResourceName, LPCTSTR lpszType, CRuntimeClass* pRuntimeClass)
{
	ASSERT(lpszResourceName != NULL);

	// determine location of the binary resource in resource fork
	HINSTANCE hInst = AfxFindResourceHandle(lpszResourceName, lpszType);

	HRSRC hRsrc = ::FindResource(hInst, lpszResourceName, lpszType);

	// If failed, try instance handle
	if (hRsrc == 0)
		hRsrc = ::FindResource(hInst = AfxGetInstanceHandle(), lpszResourceName, lpszType);

	if (hRsrc == NULL)
		return NULL;

	HGLOBAL hData = LoadResource(hInst, hRsrc);
	if (hData == NULL)
		return NULL;

	DWORD dwSize = SizeofResource(hInst, hRsrc);
	LPBYTE pData = (LPBYTE) LockResource(hData);

#if _MFC_VER >= 0x0300
	CMemFile memFile;
	memFile.Attach(pData, dwSize);
#else
	HGLOBAL hGlobal = GlobalAlloc(GHND, dwSize);
	LPBYTE lpNew = (LPBYTE) GlobalLock(hGlobal);
	memcpy(lpNew, pData, (size_t) dwSize);
	UnlockResource(hData);
	FreeResource(hData);

	CSharedFile memFile;
	memFile.SetHandle(hGlobal, FALSE);
#endif

	CObject* pObj;

	TRY
	{
		pObj = GXCreateObjectFromFile(memFile, pRuntimeClass);
	}
	CATCH_ALL(e)
	{
#if _MFC_VER >= 0x0300
		memFile.Detach();
		UnlockResource(hData);
		FreeResource(hRsrc);
#endif

		THROW_LAST();
	}
	END_CATCH_ALL

#if _MFC_VER >= 0x0300
	memFile.Detach();
	UnlockResource(hData);
	FreeResource(hRsrc);
#endif

	return pObj;
}

/////////////////////////////////////////////////////////////////////////////
// CGXGridParam

#define GXLAYOUT _T("GXLAYOUT")

CGXGridParam* AFXAPI CGXGridParam::CreateFromFile(LPCTSTR lpszFileName)
{
	ASSERT(GXGetAppData()->m_pDocSerializeImp);
	// ASSERTION-> You have to call ImplementSerialize() or check Serialize in
	// the control factory wizard ->END

	return (CGXGridParam*) GXCreateObjectFromFile(
		lpszFileName, RUNTIME_CLASS(CGXGridParam));
}

CGXGridParam* AFXAPI CGXGridParam::CreateFromResource(LPCTSTR lpszResourceName)
{
	ASSERT(GXGetAppData()->m_pDocSerializeImp);
	// ASSERTION-> You have to call ImplementSerialize() or check Serialize in
	// the control factory wizard ->END

	return (CGXGridParam*) GXCreateObjectFromResource(
		lpszResourceName, GXLAYOUT, RUNTIME_CLASS(CGXGridParam));
}

CGXGridParam* AFXAPI CGXGridParam::CreateFromResource(UINT nId)
{
	ASSERT(GXGetAppData()->m_pDocSerializeImp);
	// ASSERTION-> You have to call ImplementSerialize() or check Serialize in
	// the control factory wizard ->END

	return CreateFromResource(MAKEINTRESOURCE(nId));
}

void CGXGridParam::WriteToFile(LPCTSTR lpszFileName) const
{
	ASSERT(GXGetAppData()->m_pDocSerializeImp);
	// ASSERTION-> You have to call ImplementSerialize() or check Serialize in
	// the control factory wizard ->END

	CFile file;
	CFileException e;
	if( !file.Open(lpszFileName, CFile::modeCreate | CFile::modeWrite, &e) )
	{
#ifdef _DEBUG
		afxDump << "File could not be opened " << e.m_cause << "\n";
#endif
		return;
	}

	CArchive ar(&file, CArchive::store);

	ar << this;
}

