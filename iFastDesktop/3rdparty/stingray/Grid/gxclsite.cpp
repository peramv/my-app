///////////////////////////////////////////////////////////////////////////////
// gxclisite.cpp
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
// Author: Daniel Jebaraj
//

#define _OG_EXPORT_IMPL

#include "stdafx.h"

#include "grid\gxclsite.h"

#include "grid\gxbrowse.h"

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

#if _MFC_VER >= 0x0400

// Very simple client site implementation. We do not use MFC client site implementation
// It doesn't get any simpler than this!
CGXClientSite::CGXClientSite(CGXOleViewer* pViewer)
{
	m_cRef = 1;
	m_pViewer = pViewer;
}

CGXClientSite::~CGXClientSite()
{
	//TRACE0("CGXClientSite destroyed\n");
}

STDMETHODIMP CGXClientSite::QueryInterface(REFIID riid, void __RPC_FAR *__RPC_FAR *ppvObject)
{
	//afxDump.HexDump( "*", (BYTE*) &riid , sizeof(IID), sizeof(IID));
	
	if (IsEqualGUID(riid, IID_IUnknown) || IsEqualGUID(riid, IID_IOleClientSite) )
	{
		*ppvObject = this;
		m_cRef++;
		return S_OK;
	}
	else
		return E_NOINTERFACE;
}
    
STDMETHODIMP_(ULONG) CGXClientSite::AddRef( void)
{ 
	return m_cRef;
}
    
STDMETHODIMP_(ULONG) CGXClientSite::Release( void)
{
	--m_cRef;
	
	if(m_cRef == 0)
		delete this;

	return 1;
}

	
STDMETHODIMP CGXClientSite::SaveObject(void)
{
	TRACE(_T("IOleClientSite::SaveObject"));
	
	if (GetViewer())
	{
		HRESULT hr = S_OK;
		IPersistStorage* pStorage = NULL;
		hr = GetViewer()->GetOleObject()->QueryInterface(IID_IPersistStorage, (void**)&pStorage);
		
		if (FAILED(hr))
			return E_FAIL;
		
		if(pStorage->IsDirty() == S_OK)
		{
			hr = ::OleSave(pStorage, GetViewer()->GetStorage(), TRUE);
			
			if (FAILED(hr))
				return E_FAIL;
			
			pStorage->SaveCompleted(NULL);
		}

		GetViewer()->SaveFromStorage();
		
		pStorage->Release();
	}

	if (GetViewer())
		GetViewer()->OnModify();
	

	return S_OK;
}

STDMETHODIMP CGXClientSite::GetMoniker(DWORD dwAssign, DWORD dwWhichMoniker, IMoniker **ppmk)
{
	GX_UNUSED_ALWAYS(dwAssign);
	GX_UNUSED_ALWAYS(dwWhichMoniker);
	GX_UNUSED_ALWAYS(ppmk);

	TRACE(_T("IOleClientSite::GetMoniker"));
	
	return E_NOTIMPL;
}

STDMETHODIMP CGXClientSite::GetContainer(IOleContainer **ppContainer)
{
	GX_UNUSED_ALWAYS(ppContainer);

	TRACE(_T("IOleClientSite::GetContainer"));
	return E_NOTIMPL;
}

STDMETHODIMP CGXClientSite::ShowObject(void)
{
	TRACE(_T("IOleClientSite::ShowObject"));
	return S_OK;
}

STDMETHODIMP CGXClientSite::OnShowWindow(BOOL fShow)
{
	GX_UNUSED_ALWAYS(fShow);

	TRACE(_T("IOleClientSite::OnShowWindow"));
	return E_NOTIMPL;
}

STDMETHODIMP CGXClientSite::RequestNewObjectLayout(void)
{
	TRACE(_T("IOleClientSite::RequestNewObjectLayout"));
	return E_NOTIMPL;
}

CGXOleViewer* CGXClientSite::GetViewer()
{
	return m_pViewer;
}


// CGXAdviseSink Implementation

CGXAdviseSink::CGXAdviseSink(CGXOleViewer* pViewer)
{
	m_cRef = 1;
	m_pViewer = pViewer;
}

CGXAdviseSink::~CGXAdviseSink()
{
	//TRACE0("CGXAdviseSink destroyed\n");
}

STDMETHODIMP CGXAdviseSink::QueryInterface(REFIID riid, void __RPC_FAR *__RPC_FAR *ppvObject)
{
	//afxDump.HexDump( "*", (BYTE*) &riid , sizeof(IID), sizeof(IID));
	
	if (IsEqualGUID(riid, IID_IUnknown) || IsEqualGUID(riid, IID_IAdviseSink) )
	{
		*ppvObject = this;
		m_cRef++;
		return S_OK;
	}
	else
		return E_NOINTERFACE;
}
    
STDMETHODIMP_(ULONG) CGXAdviseSink::AddRef( void)
{ 
	return m_cRef;
}
    
STDMETHODIMP_(ULONG) CGXAdviseSink::Release( void)
{
	--m_cRef;
	
	if(m_cRef == 0)
		delete this;
	
	return 1;
}



STDMETHODIMP_(void)  CGXAdviseSink::OnDataChange(FORMATETC __RPC_FAR *pFormatetc, STGMEDIUM __RPC_FAR *pStgmed)
{
	TRACE0("CGXAdviseSink::OnDataChange(FORMATETC __RPC_FAR *pFormatetc, STGMEDIUM __RPC_FAR *pStgmed)\n");
	GX_UNUSED_ALWAYS(pStgmed);
	GX_UNUSED_ALWAYS(pFormatetc);
}
        
STDMETHODIMP_(void)  CGXAdviseSink::OnViewChange(DWORD dwAspect, LONG lindex)
{
	TRACE0("CGXAdviseSink::OnViewChange(DWORD dwAspect, LONG lindex) called\n");
	GX_UNUSED_ALWAYS(lindex);
	GX_UNUSED_ALWAYS(dwAspect);
}
        
STDMETHODIMP_(void)  CGXAdviseSink::OnRename(IMoniker __RPC_FAR *pmk)
{
	TRACE0("CGXAdviseSink::OnRename(IMoniker __RPC_FAR *pmk) called\n");
	GX_UNUSED_ALWAYS(pmk);
}
        
STDMETHODIMP_(void)  CGXAdviseSink::OnSave( void)
{
	TRACE0("CGXAdviseSink::OnSave( void) called\n");
}
        
STDMETHODIMP_(void)  CGXAdviseSink::OnClose( void)
{
	TRACE0("CGXAdviseSink::OnClose( void) called\n");
	GetViewer()->Close();
}

CGXOleViewer* CGXAdviseSink::GetViewer()
{
	return m_pViewer;
}

#endif // _MFC_VER >= 0x400
