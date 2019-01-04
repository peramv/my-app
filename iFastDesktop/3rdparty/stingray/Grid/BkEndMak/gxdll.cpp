// 
// Build wizard generated file. 
// DO NOT EDIT MANUALLY!!!
//
// Objective Grid
// gxdll.cpp: extension dll initialization
//
//////////////////////////////////////////////////////////////////////////////
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
//////////////////////////////////////////////////////////////////////////////
//
// Author: Stefan Hoenig
//

#define _OG_EXPORT_IMPL

#include "stdafx.h"

#ifdef _GXDLL
#undef AFXAPI_DATA
#define AFXAPI_DATA __based(__segname("_DATA"))
#endif

#pragma warning(disable: 4789)

// Headers

#ifdef _GXDLL

#ifndef _GXDLL_H_
#include "grid\gxdll.h"
#endif

#ifndef _GXSTATE_H_
#include "grid\gxstate.h"
#endif

#ifndef _GX_PROC_H__
#include "grid\gxproc.h"
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef _GX_VER
#if(_GX_VER > 0x01301)
#pragma message( "ERROR!!! Please update language version number in gxdll.cpp!")
#endif
#endif

#ifndef GX_LANG_VER
#define GX_LANG_VER "GX1301"
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXDLL")
#endif

#if _MFC_VER >= 0x0400 && _MFC_VER <= 0x0410
// turn off global optimization for this file 
// to prevent Win32s problems in release build

#pragma optimize("g", off)
#endif

#if _MFC_VER < 0x0400 // Win16

class CGXDynLinkLibrary: public CDynLinkLibrary
{
	DECLARE_DYNAMIC(CGXDynLinkLibrary)

public:
	CGXDynLinkLibrary(AFX_EXTENSION_MODULE& state);

private:
	GX_APP_STATE m_gxAppState;

	friend GX_APP_STATE* AFXAPI GXGetAppState();
};

#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

#if _MFC_VER <= 0x0200
	#ifdef _DEBUG
		LPCTSTR szLibName = _T("GX6116D.DLL");
	#else
		LPCTSTR szLibName = _T("GX6116R.DLL");
	#endif
#else _
	#ifdef _UNICODE
		#ifdef _DEBUG
			LPCTSTR szLibName = _T("og1301asud.DLL");
		#else
			LPCTSTR szLibName = _T("og1301asu.DLL");
		#endif
	#else
		#ifdef _DEBUG
			LPCTSTR szLibName = _T("og1301asd.DLL");
		#else
			LPCTSTR szLibName = _T("og1301as.DLL");
		#endif
	#endif
#endif //16-bits

/////////////////////////////////////////////////////////////////////////////
// Initialization of MFC Extension DLL

#include "afxdllx.h"    // standard MFC Extension DLL routines

static AFX_EXTENSION_MODULE NEAR gxExtensionDLL = { NULL, NULL };

static CDynLinkLibrary* s_pDLL;

HINSTANCE AFXAPI GXGetResourceHandle()
{
#if _MFC_VER >= 0x0300
	ASSERT(gxExtensionDLL.hResource != NULL);
	return gxExtensionDLL.hResource;
#else
	return gxExtensionDLL.hModule;
#endif
}

#if _MFC_VER >= 0x0300 // Win32

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE1("%s Initializing!\n", szLibName);

		// Extension DLL one-time initialization
		AfxInitExtensionModule(gxExtensionDLL, hInstance);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE1("%s Terminating!\n", szLibName);
		AfxTermExtensionModule(gxExtensionDLL, FALSE);
		s_pDLL = NULL;
	}

	// unused_
	lpReserved;

	return 1;   // ok
}

extern "C" extern void WINAPI GXInitDll()
{
	// Insert this DLL into the resource chain
#if _MFC_VER < 0x0400
	s_pDLL = new CGXDynLinkLibrary(gxExtensionDLL);
#else
	s_pDLL = new CDynLinkLibrary(gxExtensionDLL);
#endif
}

#else // Win16

extern "C" int CALLBACK LibMain(HINSTANCE hInstance, WORD, WORD, LPSTR)
{
	TRACE1("%s Initializing!\n", szLibName);

	// Extension DLL one-time initialization
	AfxInitExtensionModule(gxExtensionDLL, hInstance);

	return 1;
}

extern "C" extern void WINAPI GXInitDll()
{
	// Insert this DLL into the resource chain
	s_pDLL = new CGXDynLinkLibrary(gxExtensionDLL);
}

#endif // Win16

/////////////////////////////////////////////////////////////////////////////
// GX_APP_STATE: Global for Data for Instance

GX_APP_STATE::GX_APP_STATE()
{
	try
	{
		m_pAppData = new CGXAppData;
		m_pClassRegState = new CGXClassRegState();
		m_pLangDll = NULL;
	}catch(...)
	{
#ifdef _DEBUG
		afxDump << "Unable to allocate memory for GX_APP_STATE() variables!";
#endif
	}
}

GX_APP_STATE::~GX_APP_STATE()
{
	if(m_pAppData)
	{
		delete m_pAppData;
		m_pAppData = NULL;
	}
#if _MFC_VER >= 0x0400
	if(m_pLangDll)
	{
		delete m_pLangDll; // Language Dll
		m_pLangDll = NULL;
	}
#else
	// Process local data for VC 1,5
	GXDeleteAllObjects(m_mapProcessLocalData);
#endif
	
	if(m_pClassRegState)
	{
		delete m_pClassRegState;
		m_pClassRegState = NULL;
	}
}


#if _MFC_VER >= 0x0420 // Win32

// special class for automatic cleanup
class CGXAutoCleanUpProcessLocal: public CGXProcessLocal<GX_APP_STATE> 
{
public:
	CGXAutoCleanUpProcessLocal();
	~CGXAutoCleanUpProcessLocal();

	// grid specific clean up functions
	virtual void AutoTerminate(AFX_MODULE_STATE* pModuleState, GX_APP_STATE* pState);
	virtual void ForceTerminate(GX_APP_STATE* pState = NULL);
	
private:
			// Internal function used by ForceTerminate()	        
	        void TerminateModuleState();
};

CGXAutoCleanUpProcessLocal::CGXAutoCleanUpProcessLocal()
{
}

CGXAutoCleanUpProcessLocal::~CGXAutoCleanUpProcessLocal()
{
		GX_APP_STATE* pData = NULL;
		AFX_MODULE_STATE* pState = NULL;
		
		//ASSERT(0);

		for( POSITION pos = m_ObjectMap.GetStartPosition(); pos != NULL; )    
		{
			m_ObjectMap.GetNextAssoc( pos, pState, pData);

#ifdef _DEBUG
			afxDump << "~CGXProcessLocal called\n";
			afxDump << pState << " : Data value" << pData << "\n";

			// if you get this TRACE message then something is wrong with the state
			// of the object map that CGXAutoCleanUpProcessLocal holds. The module state
			// needs to be non zero and valid at clean up time. For Ole control modules that
			// are unloaded by COM please use ForceTerminate with the correct module state.
			if(!pState)
				TRACE0("Invalid module state in CGXAutoCleanUpProcessLocal object map\n");
#endif  //_DEBUG

			//clean up and delete the object
			if(pData && pState)
			{
				// ensures that the correct module state is set
				AutoTerminate(pState, pData);
			}
		}
		
		m_ObjectMap.RemoveAll();
		m_pObject = NULL;
}

// grid specific clean up function
void CGXAutoCleanUpProcessLocal::AutoTerminate(AFX_MODULE_STATE* pModuleState, GX_APP_STATE* pState)
{
	// it is important that this module state is valid. This is no problem with 
	// applications, extension dlls and regular dll but is to be carefully considered
	// with Ole controls
	AFX_MANAGE_STATE(pModuleState);
	ForceTerminate(pState);
}
	
// force terminate assumes that the module state has been correctly set. Call this function
// when Ole Control modules are terminated. In general this function is to be called when
// something that has an unique module state is terminated
void CGXAutoCleanUpProcessLocal::ForceTerminate(GX_APP_STATE* pState)
{
	if(pState == NULL)
		pState = GetData();
	
	if(pState == NULL)
	{
		TRACE0("Call to CGXAutoCleanUpProcessLocal::ForceTerminate fails\n");
		TRACE0("You can ignore this warning if you are simply calling GXTerminate\n");
		TRACE0("You no longer need the call to GXTerminate (aka GXTerminateData) except with OLE controls\n");
		// Did you set the correct module state with AFX_MANAGE_STATE before calling ForceTerminate? 
		// See also "Shared application data problem" below.
		return;
	}

	CGXAppData* pData = pState->m_pAppData;

	if(pData == NULL)
	{
		TRACE0("Call to CGXAutoCleanUpProcessLocal::ForceTerminate fails\n");
		TRACE0("You can ignore this warning if you are simply calling GXTerminate\n");
		TRACE0("You no longer need the call to GXTerminate (aka GXTerminateData) except with OLE controls\n");
		// Did you set the correct module state with AFX_MANAGE_STATE before calling ForceTerminate?
		// See also "Shared application data problem" below.

		// As of CD55, 
		//             replaced goto label with reusable internal function (see private function definition in this file) and 
		//             added else statement below for single entry/exit points
		// Ref: http://en.wikipedia.org/wiki/Control_flow#Minimal_structured_control_flow
		TerminateModuleState();
	}
	else // pData != NULL
	{
		//GXTerminate(pData);
		GXTerminateData(pData);
		TerminateModuleState();
	}
}

void CGXAutoCleanUpProcessLocal::TerminateModuleState()
{
	GX_APP_STATE* pDataL = NULL;
	if(m_ObjectMap.Lookup(AfxGetModuleState(), pDataL))
	{
		m_ObjectMap.RemoveKey(AfxGetModuleState());
		if(pDataL)
			delete pDataL;
	}
}

/*
Shared application data problem:
--------------------------------
We have rewritten GXTerminate in terms of GXForceTerminate.

For more detailed information about Objective Grid's DLL architecture, 
please refer to section 15.1 in Objective Grid User's Guide.

If you have an application that calls GXTerminate...
------------------------------------------------------

You can

a) Safely remove this call

b) Leave it as it is. In this case you will see the following TRACE message

		TRACE0("Call to CGXAutoCleanUpProcessLocal::ForceTerminate fails\n");
		TRACE0("You can ignore this warning if you are simply calling GXTerminate\n");
		TRACE0("You no longer need the call to GXTerminate (aka GXTerminateData) except with OLE controls\n");

		You may ignore this message.

c) If you have an application that links with multiple extension dlls that use OG or 
   if the application itself uses OG in addition to the DLL.

		REMOVE CALLS to GXTerminate as this will only cause problems.
*/

// used for automatic clean up
AFX_DATADEF CGXAutoCleanUpProcessLocal _gxAppState;

//extern "C" extern void WINAPI GXForceTerminate()
void __cdecl GXForceTerminate()
{
	_gxAppState.ForceTerminate();
}

GX_APP_STATE* AFXAPI GXGetAppState()
{
	return _gxAppState;
}

#elif _MFC_VER >= 0x0400 // Win32

PROCESS_LOCAL(GX_APP_STATE, _gxAppState)

GX_APP_STATE* AFXAPI GXGetAppState()
{
	return _gxAppState;
}

#else // 16 - Bit


GX_APP_STATE* AFXAPI GXGetAppState()
{
	// Find CDynLinkLibrary for this library
	CDynLinkLibrary* pDll;

	for (pDll = _AfxGetAppData()->pFirstDLL;
		pDll && pDll->m_hModule != gxExtensionDLL.hModule;
		pDll = pDll->m_pNextDLL)
		NULL;

	return &((CGXDynLinkLibrary*) pDll)->m_gxAppState;
}

#endif // 16 - Bit

/////////////////////////////////////////////////////////////////////////////
// CGXDynLinkLibrary application specific data

#if _MFC_VER < 0x0400 // Win16

IMPLEMENT_DYNAMIC(CGXDynLinkLibrary, CDynLinkLibrary);

CGXDynLinkLibrary::CGXDynLinkLibrary(AFX_EXTENSION_MODULE& state)
	: CDynLinkLibrary(state)
{
}

#endif

/////////////////////////////////////////////////////////////////////////////
// Support for OG language Dll's

#if _MFC_VER >= 0x0400 // Win32

CGXLangDll::CGXLangDll()
{
	m_hLangDll = m_hOldLang = m_hOldRes = NULL;
}


BOOL CGXLangDll::Load(LPCTSTR pszLang, LPCTSTR pszPath)
{
	BOOL bOK = FALSE;
	TCHAR szLangDLL[_MAX_PATH+14];  // max_path + \ + 8.3 name + 0-term

	if (m_hLangDll)                 // free previous loaded language
		Free();

	if (s_pDLL && pszLang)          // do not load if Grid dll not loaded
	{
		if (pszPath)
		{
			// QA: 31989 - #if Secure Code Cleanup.
			_tcsncpy(szLangDLL, pszPath, sizeof(szLangDLL)-14);
			szLangDLL[sizeof(szLangDLL)-14] = 0;
			if (szLangDLL[_tcsclen(szLangDLL)-1]!='\\')
			{
				// QA: 31989 - #if Secure Code Cleanup.
				_tcscat(szLangDLL, _T("\\"));
			}
		}
		else
			szLangDLL[0]=0;

		// QA: 31989 - #if Secure Code Cleanup.
		_tcscat(szLangDLL, _T(GX_LANG_VER));
		_tcscat(szLangDLL, pszLang);
		_tcscat(szLangDLL, _T(".DLL"));  // example : GX70NLD.DLL


		HINSTANCE hLangDLL = AfxLoadLibrary(szLangDLL);
		if (hLangDLL)               // loaded successfully
		{
			m_hOldLang = gxExtensionDLL.hResource;  // remember old hResource
			m_hOldRes  = s_pDLL->m_hResource;
			m_hLangDll =                // need handle to free dll
			gxExtensionDLL.hResource =  // modify return-value for GXGetResourceHandle()
			s_pDLL->m_hResource =       // modify return-value for AfxFindResourceHandle()
			hLangDLL;

			GXGetAppData()->LoadResources(); // reload resources

			bOK=TRUE;
		}
	}

	return bOK;
}


BOOL CGXLangDll::Free()
{
	BOOL bOK = FALSE;

	if (m_hLangDll && AfxFreeLibrary(m_hLangDll)) // free language dll
	{
		if (s_pDLL) // restore previous values if Grid dll still loaded
		{
			gxExtensionDLL.hResource = m_hOldLang;
			s_pDLL->m_hResource = m_hOldRes;

			GXGetAppData()->LoadResources(); // reload resources
		}

		m_hLangDll = m_hOldLang = m_hOldRes = NULL;
		bOK = TRUE;
	}

	return bOK;
}


CGXLangDll::~CGXLangDll()
{
	Free();
}


#endif // _MFC_VER >= 0x0400

// Register State management implementation

CGXClassRegState* GXGetRegState()
{
	return GXGetAppState()->m_pClassRegState;
}

GX_CLASSREG_STATE::GX_CLASSREG_STATE()
{
	m_pClassRegState = new CGXClassRegState();
}
	
GX_CLASSREG_STATE::~GX_CLASSREG_STATE()
{
	if(m_pClassRegState)
		delete m_pClassRegState;
}

// _gxClassRegStateNode implementation

_gxClassRegStateNode::_gxClassRegStateNode()
{
	m_pState = NULL;
	m_pNext = NULL;
}

_gxClassRegStateNode::_gxClassRegStateNode(AFX_MODULE_STATE* pState)
{
	m_pState = pState;
	m_pNext = NULL;
}

_gxClassRegStateNode::~_gxClassRegStateNode()
{
	// no implementation	
}


// _gxClassRegStateList implementation

_gxClassRegStateList::_gxClassRegStateList()
{
	m_pHead = NULL;
}

_gxClassRegStateList::~_gxClassRegStateList()
{
	ASSERT(m_pHead == NULL); // If this assert fails one or more of your dlls did not call
	// CGXClassRegState::RegisterRevoke
}
	
void _gxClassRegStateList::Add(AFX_MODULE_STATE* pState)
{
	if (m_pHead == NULL)
	{
		m_pHead = new _gxClassRegStateNode(pState);
		ASSERT(m_pHead != NULL);
		return;
	}


	_gxClassRegStateNode* pStartNode = m_pHead;

	while(pStartNode->m_pNext != NULL)
			pStartNode = pStartNode->m_pNext;

	pStartNode->m_pNext = new _gxClassRegStateNode(pState);
	
	ASSERT(pStartNode->m_pNext != NULL);
}

void _gxClassRegStateList::Remove(AFX_MODULE_STATE* pState)
{
	ASSERT(m_pHead != NULL);

	if(m_pHead == NULL)
		return;

	_gxClassRegStateNode* pStartNode = m_pHead;
	_gxClassRegStateNode* pPrevNode = NULL;

	BOOL bFound(FALSE);

	while(pStartNode != NULL)
	{
		if(pStartNode->m_pState == pState)
		{
			if(pPrevNode)
				pPrevNode->m_pNext = pStartNode->m_pNext;
			else
				m_pHead = m_pHead->m_pNext;

			bFound = TRUE;

			delete pStartNode;
			break;
		}

		pStartNode = pStartNode->m_pNext; // keep moving
	}
	
	if(bFound == FALSE)
		TRACE0("_gxClassRegStateList::Remove--->Enable to find specified module state\n");
}

AFX_MODULE_STATE* _gxClassRegStateList::GetNextState()
{
	if(m_pHead)
		return m_pHead->m_pState;	
	else
		return NULL;
}

BOOL _gxClassRegStateList::IsEmpty()
{
	return m_pHead == NULL;
}


// CGXClassRegState implementation

CGXClassRegState::CGXClassRegState()
{
	m_pList = new _gxClassRegStateList();
	ASSERT(m_pList != NULL); 
	
	m_bIgnoreAdd = FALSE;

	m_pRegisterState = NULL;
}

CGXClassRegState::~CGXClassRegState()
{
	if (m_pList != NULL)
		delete m_pList;
}

void CGXClassRegState::RegisterDone(AFX_MODULE_STATE* pState)
{
	if (m_pRegisterState == NULL)
		m_pRegisterState = pState;

	if (m_bIgnoreAdd == FALSE)
		m_pList->Add(pState);
}

void CGXClassRegState::RegisterRevoke(AFX_MODULE_STATE* pState)
{
	// remove this state
	m_pList->Remove(pState);

	if(m_pRegisterState == pState && !m_pList->IsEmpty())
	{
		AFX_MODULE_STATE* pSNew = m_pList->GetNextState();
		
		ASSERT(pSNew != NULL);

		AFX_MANAGE_STATE(pSNew)
		m_pRegisterState = NULL;
		m_bIgnoreAdd = TRUE;
		// register classes with the new module state	
		GXRegisterClasses(pSNew->m_hCurrentInstanceHandle);
		m_bIgnoreAdd = FALSE;
	}
	else if(m_pRegisterState == pState)
		m_pRegisterState = NULL;
}


#endif // _GXDLL
