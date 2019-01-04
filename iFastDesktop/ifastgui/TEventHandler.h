#ifndef TEVENT_HANDLER_H
  #define TEVENT_HANDLER_H
//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : TEventHandler.h
// ^AUTHOR : Yongmei Feng
// ^DATE   : 5-06
//
// ----------------------------------------------------------

#include <windows.h>

#include "mshtml.h"

namespace TEventHandlerNamespace
{
template <class event_handler_class, typename device_interface, typename device_event_interface>
class TEventHandler : IDispatch
{
  friend class class_event_handler;

  typedef HRESULT (event_handler_class::*parent_on_invoke)
  (
    TEventHandler<event_handler_class, device_interface, device_event_interface>* pthis,
	DISPID dispidMember, 
	REFIID riid,
	LCID lcid, 
	WORD wFlags, 
	DISPPARAMS* pdispparams, 
	VARIANT* pvarResult,
	EXCEPINFO* pexcepinfo, 
	UINT* puArgErr
  );

public :
  TEventHandler
  (
    event_handler_class& parent,
	device_interface* pdevice_interface,  
	parent_on_invoke parent_on_invoke_function
  ) :
    m_cRef(1),
    m_parent(parent),
	m_parent_on_invoke(parent_on_invoke_function),
	m_pIConnectionPoint(0),
	m_dwEventCookie(0)
  {
	 setElementId( pdevice_interface );
    SetupConnectionPoint(pdevice_interface);
  }
	   
  ~TEventHandler()
  {
	// Call ShutdownConnectionPoint() here JUST IN CASE connection points are still 
	// alive at this time. They should have been disconnected earlier.
    ShutdownConnectionPoint();
  }

  STDMETHOD_(ULONG, AddRef)()
  {
	InterlockedIncrement(&m_cRef);
	
	return m_cRef;  
  }
	   
  STDMETHOD_(ULONG, Release)()
  {
	InterlockedDecrement(&m_cRef);
	
	if (m_cRef == 0)
	{
		delete this;
		return 0;
	}
	
	return m_cRef;
  }
	   
  STDMETHOD(QueryInterface)(REFIID riid, void ** ppvObject)
  {
	if (riid == IID_IUnknown)
	{
		*ppvObject = (IUnknown*)this;
		AddRef();
		return S_OK;
	}
	
	if ((riid == IID_IDispatch) || (riid == __uuidof(device_event_interface)))
	{
		*ppvObject = (IDispatch*)this;
		AddRef();
		return S_OK;
	}
	
	return E_NOINTERFACE;
  }
	   
  STDMETHOD(GetTypeInfoCount)(UINT* pctinfo)
  {
	return E_NOTIMPL;
  }
	   
  STDMETHOD(GetTypeInfo)(UINT itinfo, LCID lcid, ITypeInfo** pptinfo)
  {
	return E_NOTIMPL;
  }
	   
  STDMETHOD(GetIDsOfNames)(REFIID riid, LPOLESTR* rgszNames, UINT cNames,
		   LCID lcid, DISPID* rgdispid)
  {
	return E_NOTIMPL;
  }
	   
  STDMETHOD(Invoke)(DISPID dispidMember, REFIID riid,
		   LCID lcid, WORD wFlags, DISPPARAMS* pdispparams, VARIANT* pvarResult,
		   EXCEPINFO* pexcepinfo, UINT* puArgErr)
  {
	return (m_parent.*m_parent_on_invoke)(this, dispidMember, riid, lcid, wFlags, pdispparams, pvarResult, pexcepinfo, puArgErr);
  }
	   
protected :
  LONG						m_cRef;

  // Pertaining to the owner of this object.
  event_handler_class&		m_parent;  // Non-reference counted. This is to prevent circular references.

  // Pertaining to connection points.
  IConnectionPoint*			m_pIConnectionPoint;  // Ref counted of course.
  DWORD						m_dwEventCookie;
  parent_on_invoke			m_parent_on_invoke;
  CString					m_ElemId;

  void SetupConnectionPoint(device_interface* pdevice_interface)
  {
    IConnectionPointContainer*	pIConnectionPointContainerTemp = NULL;
    IUnknown*					pIUnknown = NULL;

    // QI this object itself for its IUnknown pointer which will be used 
    // later to connect to the Connection Point of the device_interface object.
    this -> QueryInterface(IID_IUnknown, (void**)&pIUnknown);

    if (pIUnknown)
    {
      // QI the pdevice_interface for its connection point.
      pdevice_interface -> QueryInterface (IID_IConnectionPointContainer, (void**)&pIConnectionPointContainerTemp);
	
      if (pIConnectionPointContainerTemp)
      {
	    pIConnectionPointContainerTemp -> FindConnectionPoint(__uuidof(device_event_interface), &m_pIConnectionPoint);
		pIConnectionPointContainerTemp -> Release();
	    pIConnectionPointContainerTemp = NULL;
      }
	
      if (m_pIConnectionPoint)
      {
	    m_pIConnectionPoint -> Advise(pIUnknown, &m_dwEventCookie);
      }
	
      pIUnknown -> Release();
	  pIUnknown = NULL;
    }
  }

public :

  void ShutdownConnectionPoint()
  {
    if (m_pIConnectionPoint)
    {
	  m_pIConnectionPoint -> Unadvise(m_dwEventCookie);
	  m_dwEventCookie = 0;
	  m_pIConnectionPoint -> Release();
	  m_pIConnectionPoint = NULL;
    }
  }

  void setElementId( device_interface* pdevice_interface )
  {
	  IHTMLElement* pElem = static_cast<IHTMLElement * >(pdevice_interface);
	  if( pElem )
	  {
		CComVariant var;
		if ( FAILED(pElem->getAttribute(_bstr_t(_T("id")),0,&var)))
		{
			m_ElemId = _T("");
		}
		if(var.vt == VT_NULL)
		{
			m_ElemId = _T("");			
		}
		m_ElemId = CString(_bstr_t(var).Detach ());		
	  }
  }

  CString& getElementId()  {	  return m_ElemId;  }

};

};

#endif

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastgui/TEventHandler.h-arc  $
//
//   Rev 1.1   Apr 19 2007 17:46:20   smithdav
//Use "id" attribute instead of "name" attribute to identify elements.
//
//   Rev 1.0   Jun 08 2006 14:01:46   fengyong
//Initial revision.
 */