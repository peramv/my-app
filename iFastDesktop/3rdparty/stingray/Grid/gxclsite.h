// This is a part of the Objective Grid C++ Library.
// Copyright © 1999-2004 Quovadx, Inc.  All Rights Reserved.
// 
// 
// This computer software is owned by Quovadx, Inc. and is protected by 
// U.S. copyright laws and other laws and by international treaties. This 
// computer software is furnished by Quovadx, Inc. pursuant to a written 
// license agreement and may be used, copied, transmitted, and stored 
// only in accordance with the terms of such license agreement and with 
// the inclusion of the above copyright notice.  This computer software or 
// any other copies thereof may not be provided or otherwise made available 
// to any other person.
// 
// U.S. Government Restricted Rights.  This computer software: 
//      (a) was developed at private expense and is in all respects the 
//          proprietary information of Quovadx, Inc.; 
//      (b) was not developed with government funds; 
//      (c) is a trade secret of Quovadx, Inc. for all purposes of the 
//          Freedom of Information Act; and 
//      (d) is a commercial item and thus, pursuant to Section 12.212 
//          of the Federal Acquisition Regulations (FAR) and DFAR 
//          Supplement Section 227.7202, Government’s use, duplication or 
//          disclosure of the computer software is subject to the restrictions 
//          set forth by Quovadx, Inc.
//
//
// This source code is only intended as a supplement to
// the Objective Grid Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding
// the Objective Grid product.
//
// Author: Daniel Jebaraj
//

#ifndef _GX_CL_SITE__H__
#define _GX_CL_SITE__H__

#ifndef __IOleClientSite_INTERFACE_DEFINED__
#include "oleidl.h"
#endif

#if _MFC_VER >= 0x0400

//
// GridMFC Extension DLL
// initialize declaration context
//

#ifdef _GXDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    GX_DATAEXT
#endif

class CGXOleViewer;

// very simple client site implementation. We do not use MFC client site implementation
class CGXClientSite : public IOleClientSite
{
public:
	CGXClientSite(CGXOleViewer* pViewer);

	virtual ~CGXClientSite();

// IUnknown
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void __RPC_FAR *__RPC_FAR *ppvObject);
    
	virtual ULONG STDMETHODCALLTYPE AddRef( void);
    
	virtual ULONG STDMETHODCALLTYPE Release( void);
	
// IOleClientSite
	STDMETHOD(SaveObject)(void);

	STDMETHOD(GetMoniker)(DWORD dwAssign, DWORD dwWhichMoniker, IMoniker **ppmk);

	STDMETHOD(GetContainer)(IOleContainer **ppContainer);

	STDMETHOD(ShowObject)(void);

	STDMETHOD(OnShowWindow)(BOOL fShow);

	STDMETHOD(RequestNewObjectLayout)(void);

	// access
	CGXOleViewer* GetViewer();

protected:
// data
	ULONG m_cRef;
	CGXOleViewer* m_pViewer;
};


class CGXAdviseSink : public IAdviseSink
{
public:
	CGXAdviseSink(CGXOleViewer* pViewer);
	virtual ~CGXAdviseSink();

// IUnknown
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void __RPC_FAR *__RPC_FAR *ppvObject);
    
	virtual ULONG STDMETHODCALLTYPE AddRef( void);
    
	virtual ULONG STDMETHODCALLTYPE Release( void);

	virtual void STDMETHODCALLTYPE OnDataChange( 
             FORMATETC __RPC_FAR *pFormatetc,
            STGMEDIUM __RPC_FAR *pStgmed);
        
    virtual void STDMETHODCALLTYPE OnViewChange( 
            DWORD dwAspect,
            LONG lindex);
        
    virtual void STDMETHODCALLTYPE OnRename( 
            IMoniker __RPC_FAR *pmk);
        
    virtual void STDMETHODCALLTYPE OnSave( void);
        
    virtual void STDMETHODCALLTYPE OnClose( void);

//access
	CGXOleViewer* GetViewer();

	protected:
// data
	ULONG m_cRef;
	CGXOleViewer* m_pViewer;
	
};

//
// GridMFC extension DLL
// reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif //_GX_CL_SITE__H__

#endif
