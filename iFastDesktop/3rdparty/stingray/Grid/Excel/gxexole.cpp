///////////////////////////////////////////////////////////////////////////////
// gxexole.cpp
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
// This is for the most part from an Inside OLE sample

#define _OG_EXPORT_IMPL

#include "stdafx.h"

#include "grid\gxexole.h"

#pragma warning(disable: 4244)

 
CGXEnumFormatEtc::CGXEnumFormatEtc(ULONG cFE, LPFORMATETC prgFE) 
{ 
    UINT	i; 
 
    m_cRef = 0; 
    m_iCur = 0; 
    
	m_cfe = cFE; 
    
	ASSERT(prgFE != NULL);

	m_prgfe=new FORMATETC[(UINT)cFE]; 
 
    if (m_prgfe != NULL) 
    { 
		for (i=0; i < cFE; i++) 
			m_prgfe[i]=prgFE[i]; 
    } 
} 
 
 
CGXEnumFormatEtc::~CGXEnumFormatEtc(void) 
{ 
    if (m_prgfe != NULL) 
        delete [] m_prgfe; 
} 
 
STDMETHODIMP CGXEnumFormatEtc::QueryInterface(REFIID riid, void** ppv) 
{ 
    *ppv=NULL; 
 
    if (IID_IUnknown == riid || IID_IEnumFORMATETC == riid) 
        *ppv = this; 
 
    //AddRef any interface we'll return. 
    if (NULL != *ppv) 
    { 
		((LPUNKNOWN)*ppv)->AddRef(); 
		return NOERROR; 
    } 
 
    return E_NOINTERFACE;
} 
 
 
STDMETHODIMP_(ULONG) CGXEnumFormatEtc::AddRef(void) 
{ 
    ++m_cRef; 
    return m_cRef; 
} 
 
STDMETHODIMP_(ULONG) CGXEnumFormatEtc::Release(void) 
{ 
    if (0 != --m_cRef) 
        return m_cRef; 
 
    delete this; 
    return 0; 
} 
 
 
STDMETHODIMP CGXEnumFormatEtc::Next(ULONG cFE, LPFORMATETC pFE, ULONG *pulFE) 
{ 
    ULONG	cReturn = 0L; 
 
    if (m_prgfe == NULL) 
        return S_FALSE; 
 
    if (pulFE == NULL) 
    { 
        if (cFE != 1) 
            return ResultFromScode(E_POINTER); 
    } 
    else 
        *pulFE = 0; 
 
    if (NULL == pFE || m_iCur >= m_cfe) 
        return S_FALSE; 
 
    while (m_iCur < m_cfe && cFE > 0) 
    { 
        *pFE++=m_prgfe[m_iCur++]; 
        cReturn++; 
        cFE--; 
    } 
 
    if (pulFE != NULL) 
        *pulFE = cReturn; 
 
    return NOERROR; 
} 
 
STDMETHODIMP CGXEnumFormatEtc::Skip(ULONG cSkip) 
{ 
    if (((m_iCur + cSkip) >= m_cfe) || NULL == m_prgfe) 
        return S_FALSE; 
 
    m_iCur += cSkip; 
    
	return NOERROR; 
} 
 
 
STDMETHODIMP CGXEnumFormatEtc::Reset(void) 
{ 
    m_iCur = 0; 
    return NOERROR; 
} 
 
 
STDMETHODIMP CGXEnumFormatEtc::Clone(LPENUMFORMATETC *ppEnum) 
{ 
    CGXEnumFormatEtc* pNew = NULL; 
 
    *ppEnum = NULL; 
 
    //Create the clone 
    pNew = new CGXEnumFormatEtc(m_cfe, m_prgfe); 
 
    if (NULL == pNew) 
        return E_OUTOFMEMORY; 
 
    pNew->AddRef(); 
    pNew->m_iCur = m_iCur; 
 
    *ppEnum = pNew; 
    return NOERROR; 
} 
 
//////////////////////////////////////////////////////////////////////////////////
// CGXDataObjectImpl
//////////////////////////////////////////////////////////////////////////////////

CGXDataObjectImpl::CGXDataObjectImpl(IStorage* pStorage, HGLOBAL hG)
{
	m_cRef = 0;
	m_pStorage = pStorage;
	
	m_hGlobal = hG;

	FORMATETC fetc[2];
	
	fetc[0].cfFormat = RegisterClipboardFormat(_T("BIFF8"));
	fetc[0].ptd = NULL;
	fetc[0].dwAspect = DVASPECT_CONTENT;
	fetc[0].lindex = -1;
	fetc[0].tymed = TYMED_ISTORAGE;

#ifndef _UNICODE
	fetc[1].cfFormat = CF_TEXT;
#else
	fetc[1].cfFormat = CF_UNICODETEXT;
#endif
	fetc[1].ptd = NULL;
	fetc[1].dwAspect = DVASPECT_CONTENT;
	fetc[1].lindex = -1;
	fetc[1].tymed = TYMED_HGLOBAL;

	
	pEnumFormatEtc = new CGXEnumFormatEtc(2, fetc);
	
	ASSERT(pEnumFormatEtc != NULL);
	
	pEnumFormatEtc->AddRef();
}

CGXDataObjectImpl::~CGXDataObjectImpl()
{
	if(pEnumFormatEtc)
		pEnumFormatEtc->Release();
}

// IUnknown
//
HRESULT STDMETHODCALLTYPE CGXDataObjectImpl::QueryInterface(REFIID riid, void ** ppvObject)
{
	*ppvObject = NULL;

	if(riid == IID_IUnknown || riid == IID_IDataObject)
	{
		AddRef();
		*ppvObject = this;
		return S_OK;
	}
	else
		return E_NOINTERFACE;
};

ULONG STDMETHODCALLTYPE CGXDataObjectImpl::AddRef(void)
{
	m_cRef++;
	
	return m_cRef;
};
    
ULONG STDMETHODCALLTYPE CGXDataObjectImpl::Release(void)
{
	m_cRef--;

	if(m_cRef == 0)
		delete this;
	
	return m_cRef;
};


// IDataObject
//
STDMETHODIMP CGXDataObjectImpl::GetData(FORMATETC *pformatetcIn, STGMEDIUM *pmedium)
{
	TRACE(_T("CGXDataObjectImpl::GetData\n"));
	
	if (pmedium == NULL)
		return E_POINTER;

	memset(pmedium, 0, sizeof(STGMEDIUM));

	TRACE(_T("Format = %x\n"), pformatetcIn->cfFormat);

	TRACE(_T("TYMED = %x\n"), pformatetcIn->tymed);

	if ((pformatetcIn->tymed & (TYMED_ISTORAGE|TYMED_HGLOBAL)) == 0)
		return DATA_E_FORMATETC;

	if ((pformatetcIn->tymed & TYMED_ISTORAGE))
	{
		pmedium->tymed = TYMED_ISTORAGE;
		pmedium->pstg = m_pStorage;
		pmedium->pUnkForRelease = NULL;
	} // HGLOBAL
	else
	{
		pmedium->tymed = TYMED_HGLOBAL;
		pmedium->hGlobal = m_hGlobal;
	}

	return S_OK;
}

STDMETHODIMP CGXDataObjectImpl::GetDataHere(FORMATETC* /* pformatetc */, STGMEDIUM* /* pmedium */)
{
	TRACE(_T("IDataObjectImpl::GetDataHere"));
	return E_NOTIMPL;
}

STDMETHODIMP CGXDataObjectImpl::QueryGetData(FORMATETC* /* pformatetc */)
{
	TRACE(_T("IDataObjectImpl::QueryGetData"));
	return E_NOTIMPL;
}

STDMETHODIMP CGXDataObjectImpl::GetCanonicalFormatEtc(FORMATETC* /* pformatectIn */,FORMATETC* /* pformatetcOut */)
{
	TRACE(_T("IDataObjectImpl::GetCanonicalFormatEtc"));
	return E_NOTIMPL;
}

STDMETHODIMP CGXDataObjectImpl::SetData(FORMATETC* /* pformatetc */, STGMEDIUM* /* pmedium */, BOOL /* fRelease */)
{
	TRACE(_T("IDataObjectImpl::SetData"));
	return E_NOTIMPL;
}

STDMETHODIMP CGXDataObjectImpl::EnumFormatEtc(DWORD /*dwDirection*/, IEnumFORMATETC**  ppenumFormatEtc)
{
	TRACE(_T("IDataObjectImpl::EnumFormatEtc"));
	
	*ppenumFormatEtc = pEnumFormatEtc;

	pEnumFormatEtc->AddRef();

	return S_OK;
}

STDMETHODIMP CGXDataObjectImpl::DAdvise(FORMATETC *pformatetc, DWORD advf, IAdviseSink *pAdvSink,
	DWORD *pdwConnection)
{
	TRACE(_T("IDataObjectImpl::DAdvise\n"));
	
	HRESULT hr = S_OK;
	if (m_spDataAdviseHolder == NULL)
		hr = CreateDataAdviseHolder(&m_spDataAdviseHolder);

	if (hr == S_OK)
		hr = m_spDataAdviseHolder->Advise((IDataObject*)this, pformatetc, advf, pAdvSink, pdwConnection);

	return hr;
}

STDMETHODIMP CGXDataObjectImpl::DUnadvise(DWORD dwConnection)
{
	TRACE(_T("IDataObjectImpl::DUnadvise\n"));
	
	HRESULT hr = S_OK;
	if (m_spDataAdviseHolder == NULL)
		hr = OLE_E_NOCONNECTION;
	else
		hr = m_spDataAdviseHolder->Unadvise(dwConnection);
	return hr;
}

STDMETHODIMP CGXDataObjectImpl::EnumDAdvise(IEnumSTATDATA **ppenumAdvise)
{
	TRACE(_T("IDataObjectImpl::EnumDAdvise\n"));
	
	HRESULT hr = E_FAIL;
	if (m_spDataAdviseHolder != NULL)
		hr = m_spDataAdviseHolder->EnumAdvise(ppenumAdvise);
	return hr;
}



