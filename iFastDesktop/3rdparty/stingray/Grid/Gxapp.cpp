///////////////////////////////////////////////////////////////////////////////
// gxapp.cpp : Defines the class behaviors for the application.
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

#ifndef _GXLOCALE_H_
#define _GXLOCALE_H_
#include <locale.h>
#endif

#ifndef _GXSTATE_H_
#include "grid\gxstate.h"
#endif

#ifndef _GXDLL_H_
#include "grid\gxdll.h"
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXAPP")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

#ifndef _GXDLL
	// _gxAppData is NOT wrapped with CThreadLocal
	// because it is used as a member pointer inside another 
	// class. This can cause unexpected behavior. 
	CGXAppData GXNEAR _gxAppData;
	// QA: 32120 - Wrapping _gxSysData with CThreadLocal.
	CThreadLocal<GX_SYS_DATA> GXNEAR _gxSysData;
#endif

void __cdecl GXRegisterClasses(HINSTANCE hResource);
void __cdecl GXUnregisterClasses(HINSTANCE hResource);

#ifndef _UNICODE
	static const TCHAR BASED_CODE szComboBox[] = _T("COMBOBOX");
	static const TCHAR BASED_CODE szListbox[] = _T("LISTBOX");
	static const TCHAR BASED_CODE szEdit[] = _T("EDIT");
#else
	static const TCHAR BASED_CODE szComboBox[] = _T("GXCOMBOBOX");
	static const TCHAR BASED_CODE szListbox[] = _T("GXLISTBOX");
	static const TCHAR BASED_CODE szEdit[] = _T("GXEDIT");
#endif
static const TCHAR BASED_CODE szWnd[] = _T("GXWND");
static const TCHAR BASED_CODE szNdblWnd[] = _T("GXNDBLCLKSWND");
static const TCHAR BASED_CODE szMDIFrameWnd[] = _T("GxMdiFrame");

static void _gxdtordata(CGXAppData* pData);

// support for _gxttof API

#ifdef _UNICODE
double AFXAPI _gxwtof(LPCTSTR s)
{
   char astring[64];

   WideCharToMultiByte (CP_ACP, 0, s, -1,
						astring, 64, NULL, NULL);

   return atof(astring);
}
#endif

// RTTI helpers for backward compatibility to VC 1.5 apps

#if _MFC_VER < 0x0400

CObject* AFX_CDECL GXDynamicDownCast(CRuntimeClass* pClass, CObject* pObject)
{
	if (pObject != NULL && pObject->IsKindOf(pClass))
		return pObject;
	else
		return NULL;
}

#ifdef _DEBUG
CObject* AFX_CDECL GXStaticDownCast(CRuntimeClass* pClass, CObject* pObject)
{
	ASSERT(pObject == NULL || pObject->IsKindOf(pClass));
	return pObject;
}
#endif

#endif

#ifndef _GXDLL
extern "C" GRID_API void __cdecl GXForceTerminate(){}
#endif


// active View
// technique described in Knowledge-Base Article Q108587


CView* AFXAPI GXGetActiveView()
{
	CFrameWnd* pFrame = (CFrameWnd*) AfxGetApp()->m_pMainWnd;
	ASSERT(pFrame->IsKindOf(RUNTIME_CLASS(CFrameWnd)));

	CView *pView = pFrame->GetActiveView();
#if _MFC_VER >= 0x0250
	if (pView == NULL)
		pView = pFrame->GetActiveFrame()->GetActiveView();
#else
	if (pFrame->IsKindOf(RUNTIME_CLASS(CMDIFrameWnd)))
	{
		CWnd* pWnd = ((CMDIFrameWnd*)pFrame)->MDIGetActive();
		if (pWnd)
			pFrame = (CFrameWnd*) pWnd;
	}
	pView = pFrame->GetActiveView();
#endif

	return pView;
}

CDocument* AFXAPI GXGetActiveDocument()
{
	CFrameWnd * pFrame = (CFrameWnd *)(AfxGetApp()->m_pMainWnd);
	if (pFrame->IsKindOf(RUNTIME_CLASS(CMDIFrameWnd)))
	{
		CMDIChildWnd * pChild =
			((CMDIFrameWnd*)(AfxGetApp()->m_pMainWnd))->MDIGetActive();
		if ( !pChild )
			return NULL;
		return pChild->GetActiveDocument();
	}
	return pFrame->GetActiveDocument();
}

CWnd* AFXAPI GXGetParentWnd(const CWnd* pWnd, struct CRuntimeClass* pClass, BOOL bAnyState)
{
	CWnd* pParentWnd = pWnd->GetParent();
	if (!pParentWnd->IsKindOf(pClass))
		return NULL;        // not a splitter
	if (!bAnyState)
	{
		// ignore tabwnds in minimized (iconic) windows
		while ((pWnd = pWnd->GetParent()) != NULL)
			if (pWnd->IsIconic())
				return NULL;
	}
	return pParentWnd;
}

CString AFXAPI GXReplaceString(CString& strTarget, CString strFind, CString strReplace)
{
	int n = strTarget.Find(strFind);
	while (n != -1)
	{
		CString s;
		if (n > 0)
			s = strTarget.Left(n);

		s += strReplace;

		s += strTarget.Mid(n+strFind.GetLength());

		strTarget = s;

		n = strTarget.Find(strFind);
	}
												
	return strTarget;
}

void AFXAPI GXInit(UINT uiMfcVersion, CGXAbstractControlFactory* pFactory, LPCTSTR pszLang, LPCTSTR pszPath)
{
	// First, check version compatibility
	if (uiMfcVersion >= 0x0400)
	{
		if (_MFC_VER < 0x0400)
		{
#ifdef _DEBUG
			TRACE(_T("MFC Version conflict\n")
				_T("GridMFC DLL has been build with VC 2.x and application with VC 4.x"));
			ASSERT(0);
#else
			AfxMessageBox(_T("MFC Version conflict\n")
				_T("GridMFC DLL has been build with VC 2.x and application with VC 4.x"));
			AfxThrowNotSupportedException();
#endif
		}
	}

#if defined(_GXDLL)
	GXInitDll();
#endif

	GXGetAppData()->Init(pFactory);

	BOOL bResourceDone = FALSE;

#if _MFC_VER >= 0x0400 && defined(_GXDLL)
	if (pszLang && _tcsicmp(pszLang, _T("Eng")) != 0) // If 'Eng', no need to load a resource dll
	{
		GXGetAppState()->m_pLangDll = new CGXLangDll;
		bResourceDone = 
			GXGetAppState()->m_pLangDll->Load(pszLang, pszPath); // if dir-param is NULL, default directories are searched
	}
#else
	pszLang, pszPath;
#endif

	// save resource handle
	HINSTANCE hSaveResource = AfxGetResourceHandle();
	HINSTANCE hResource = GXGetResourceHandle();

	// switch it to dll
	AfxSetResourceHandle(hResource);

	if (!bResourceDone)
		GXGetAppData()->LoadResources();

	// combobox popup window
	GXGetAppData()->sComboClassName = AfxRegisterWndClass(CS_SAVEBITS);

	GXRegisterClasses(AfxGetInstanceHandle());

#if _MFC_VER < 0x0300
	// In 16-Bit environment, it is also necessary
	// to register all classes for the resource Dll
	if (hResource != AfxGetInstanceHandle())
		GXRegisterClasses(hResource);
#endif

	// reset resource handle
	AfxSetResourceHandle(hSaveResource);

	GXGetSysData()->UpdateSysColors();
	GXGetSysData()->UpdateSysSettings();

	GXGetAppData()->m_bInitDone = TRUE;
}

void __cdecl GXRegisterClasses(HINSTANCE hResource)
{
	GXGetAppData()->m_pControlFactory->RegisterWndClasses(hResource);

	// Register standard control classes
	// these controls will not be subclassed by Ctl3d
	WNDCLASS wcls;

	if (!::GetClassInfo(hResource, szEdit, &wcls))
	{
		// Use standard "edit" control as a template.
		VERIFY(::GetClassInfo(NULL, _T("edit"), &wcls));

		// set new values
		wcls.style |= GX_GLOBALCLASS;
		wcls.hInstance = hResource;
		wcls.lpszClassName = szEdit;
		::RegisterClass(&wcls);
	}

	// check to see if class already registered
	if (!::GetClassInfo(hResource, szListbox, &wcls))
	{
		// Use standard "listbox" control as a template.
		VERIFY(::GetClassInfo(NULL, _T("listbox"), &wcls));

		// set new values
		wcls.style |= GX_GLOBALCLASS;
		wcls.hInstance = hResource;
		wcls.lpszClassName = szListbox;
		::RegisterClass(&wcls);
	}

	// check to see if class already registered
	if (!::GetClassInfo(hResource, szComboBox, &wcls))
	{
		// Use standard "edit" control as a template.
		VERIFY(::GetClassInfo(NULL, _T("combobox"), &wcls));

		// set new values
		wcls.style |= GX_GLOBALCLASS;
		wcls.hInstance = hResource;
		wcls.lpszClassName = szComboBox;
		::RegisterClass(&wcls);
	}

	// GXWND can be used to subclass any CWnd derived control
	// in a dialog box with SubclassDlgItem
	if (!::GetClassInfo(hResource, szWnd, &wcls))
	{
		// set new values
		wcls.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
		wcls.style |= GX_GLOBALCLASS;
		wcls.lpfnWndProc = DefWindowProc;
		wcls.cbClsExtra = 0;
		wcls.cbWndExtra = 0;
		wcls.hInstance = hResource;
		wcls.lpszClassName = szWnd;
		wcls.hIcon = 0;
		wcls.hCursor = 0;
		wcls.hbrBackground = 0;
		wcls.lpszMenuName = NULL;
		::RegisterClass(&wcls);
	}

	// szNdblWnd is the same as GXWND but has no CS_DBLCLKS style
	if (!::GetClassInfo(hResource, szNdblWnd, &wcls))
	{
		// set new values
		wcls.style = CS_HREDRAW | CS_VREDRAW;
		wcls.style |= GX_GLOBALCLASS;
		wcls.lpfnWndProc = DefWindowProc;
		wcls.cbClsExtra = 0;
		wcls.cbWndExtra = 0;
		wcls.hInstance = hResource;
		wcls.lpszClassName = szNdblWnd;
		wcls.hIcon = 0;
		wcls.hCursor = 0;
		wcls.hbrBackground = 0;
		wcls.lpszMenuName = NULL;
		::RegisterClass(&wcls);
	}

	// szMDIFrameWnd is the same as GXWND but has no CS_HREDRAW / CS_VREDRAW style
	if (!::GetClassInfo(hResource, szMDIFrameWnd, &wcls))
	{
		// set new values
		wcls.style = CS_DBLCLKS;
		wcls.style |= GX_GLOBALCLASS;
		wcls.lpfnWndProc = DefWindowProc;
		wcls.cbClsExtra = 0;
		wcls.cbWndExtra = 0;
		wcls.hInstance = hResource;
		wcls.lpszClassName = szMDIFrameWnd;
		wcls.hIcon = 0;
		wcls.hCursor = 0;
		wcls.hbrBackground = 0;
		wcls.lpszMenuName = NULL;
		::RegisterClass(&wcls);
	}
	
	GXGetRegState()->RegisterDone(AfxGetModuleState());
}

// As of CD55, renamed GXTerminate() to GXTerminateData() for internal use by GXForceTerminate()
// Ref: GXTerminateData(CGXAppData*) defined in GXSTATE.h
void __cdecl GXTerminateData(CGXAppData* pData)
{
	if (pData == NULL)
		pData = GXGetAppData();

	if (pData == NULL || pData->m_pControlFactory == NULL)
		// GXInit() was never called, nothing to clean up
		return;

	// combobox popup window
	if (pData->sComboClassName.GetLength() > 0)
		::UnregisterClass(pData->sComboClassName, GXGetResourceHandle());
	pData->sComboClassName.Empty();

	HINSTANCE hInstance = GXGetResourceHandle();

#if _MFC_VER < 0x0300
	HINSTANCE hResource = AfxGetInstanceHandle();
	GXUnregisterClasses(hInstance);
	// In 16-Bit environment, it is also necessary
	// to unregister all classes of the resource Dll
	if (hResource != hInstance)
		GXUnregisterClasses(hResource);

#else

	GXUnregisterClasses(hInstance);

#endif

	// the following lines are normally not necessary because
	// these objects will be deleted in the CGXAppData destructor and GX_DIB_STATE dtor
	// but we don't want that Boundschecker claims there are memory leaks
	// if OG is used as shared Dll. 

	_gxdtordata(pData);

	GX_DIB_STATE* pDIBState = GXGetDIBState();
	if (pDIBState->m_pDIBPool)
		pDIBState->m_pDIBPool->EmptyPool();
	delete pDIBState->m_pDIBPool;
	pDIBState->m_pDIBPool = NULL;

	GX_FONT_STATE* pFontState = GXGetFontState();
	delete[] pFontState->m_aFontInfo;
	pFontState->m_aFontInfo = 0;

	for (int i = 0; i < pFontState->m_apNotInstalledFontInfo.GetSize(); i++)
	{
		CGXFontInfo* pInfo = (CGXFontInfo*) pFontState->m_apNotInstalledFontInfo[i];
		delete pInfo;
	}
	pFontState->m_apNotInstalledFontInfo.RemoveAll();

#ifdef _GXDLL
	GX_APP_STATE* pAppState = GXGetAppState();
	delete pAppState->m_pAppData;
	pAppState->m_pAppData = NULL;
#endif
}

// As of CD55, rewritten GXTerminate(CGXAppData*) with new, redefined GXForceTerminate() implementation (see gxdll.cpp and Gxapp.cpp)
// This will allow us to redefine GXTerminate as GXForceTerminate "under the covers", so that the end-user need not change their app.
// Ref: GXTerminate(CGXAppData*) defined in GXSTATE.h
void __cdecl GXTerminate(CGXAppData* /*pData*/)
{
	GXForceTerminate();
}

void __cdecl GXUnregisterClasses(HINSTANCE hInstance)
{
	GXGetAppData()->m_pControlFactory->UnregisterWndClasses(hInstance);

#if _MFC_VER < 0x0300
	::UnregisterClass(szEdit, hInstance);
	::UnregisterClass(szListbox, hInstance);
	::UnregisterClass(szWnd, hInstance);
#endif

	GXGetRegState()->RegisterRevoke(AfxGetModuleState());
}

extern "C" GRID_API BOOL __cdecl GXDiscardNcActivate()
{ 
	return GXGetAppData()->m_bDiscardNcActivate; 
}

extern "C" GRID_API void __cdecl GXSetNewGridLineMode(BOOL bEnable, UINT nStyle, BOOL bNoHeaderBorders)
{
	GXGetAppData()->m_bEnableNewGridLineMode = bEnable;
	GXGetAppData()->m_nDefaultGridLineStyle = nStyle;
	GXGetAppData()->m_bNoHeaderBorders = bNoHeaderBorders;
}

/////////////////////////////////////////////////////////////////////////////
// CGXAppData

// Memory Leak Testing
//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>


CGXAppData::CGXAppData()
{
	
	//_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );// RWDN
	//_CrtDumpMemoryLeaks(); // RWDN

	m_bInitDone					= FALSE;
	m_bDtorDone					= FALSE;
	m_uiStylesClipboardFormat	= 0;
	m_bDiscardNcActivate		= FALSE;
	m_pControlFactory			= NULL;
	m_pTabWndInt				= NULL;
	m_pRecordInfoWndInt			= NULL;
	m_pRecordInfoSplitterWndInt	= NULL;
	m_bEnableNewGridLineMode	= FALSE;
	m_nDefaultGridLineStyle		= PS_SOLID;
	m_bNoHeaderBorders			= FALSE;
	// Used in NumberFormatting to sync with regional settings
	charDecSep[0] = _T('.');
	charGrpSep[0] = _T(',');
	charDecSep[1] = 0;
	charGrpSep[1] = 0;
	m_bLocaleNumbersEnabled = FALSE;
	m_bFormulaEnabled		= FALSE;
	m_pEngineState			= NULL;
	m_pParseState			= NULL;
	m_pEvalState			= NULL;
	m_pRegexState			= NULL;
	m_pIntelliState			= NULL;
	m_pMemObjState			= NULL;
	m_nExpressionValueType	= GX_VALUE_EXPRESSION;
	m_bDisplayFontCharset	= FALSE;
	m_pDaFTools				= NULL;
	//--------------------------------------
	begin_component_ptr				= NULL;
	m_pCoveredCellPoolImp			= NULL;
	m_pSpanCellPoolImp				= NULL;
	m_pDelayedRangePoolImp			= NULL;
	m_pPrintDeviceImp				= NULL;
	m_pStyleCompareSubsetImp		= NULL;
	m_pStyleSerializeImp			= NULL;
	m_pDocSerializeImp				= NULL;
	m_pGridProfileImp				= NULL;
	m_pParamCopyOperatorImp			= NULL;
	m_pSortMoveDataImp				= NULL;
	m_pDrawRotatedTextImp			= NULL;
	m_pDateTimeImp					= NULL;
	m_pDataCopyMoveCellsImp			= NULL;
	m_pLongOperationImp				= NULL;
	m_pSerializeOG5CompatibleImp	= NULL;
	m_pNumberFormattingImp			= NULL;
	end_component_ptr				= NULL;
	//--------------------------------------
}

//used for locale formatting of numbers
void CGXAppData::UpdateLocaleNumberSettings()
{
	if(m_bLocaleNumbersEnabled)
	{
		_tsetlocale(LC_NUMERIC,_T(""));
	
		GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_SDECIMAL, charDecSep, 2);

		GetLocaleInfo(LOCALE_USER_DEFAULT, LOCALE_STHOUSAND , charGrpSep, 2);
	}
}

//make sure string has a period before it is stored
void CGXAppData::PutPointInString(CString& sValue)
{
	if(m_bLocaleNumbersEnabled && charDecSep[0] != _T('.'))
	{
		int nDecPlace = sValue.Find(charDecSep[0]);
		if(nDecPlace > -1)
		sValue.SetAt(nDecPlace, _T('.')); //insert the correct decimal
	}
}

void CGXAppData::Init(CGXAbstractControlFactory* pFactory)
{
	// Make this a unique clipboard format for the application
	// beause serialization of style objects among different
	// apps may fail (different base styles, different user attributes etc).
	TCHAR szClipName[128];
	wsprintf(szClipName, _T("Grid Styles %08x"), (SEC_UINT) AfxGetInstanceHandle());
	m_uiStylesClipboardFormat = ::RegisterClipboardFormat(szClipName);

	// Delete objects in case Init is called more than once
	if (m_pControlFactory != NULL)
		delete m_pControlFactory;

	m_pControlFactory = pFactory;

	if (m_pTabWndInt != NULL)
		delete m_pTabWndInt;
	m_pTabWndInt = NULL;

	if (m_pRecordInfoWndInt != NULL)
		delete m_pRecordInfoWndInt;
	m_pRecordInfoWndInt = NULL;

	if (m_pRecordInfoSplitterWndInt != NULL)
		delete m_pRecordInfoSplitterWndInt;
	m_pRecordInfoSplitterWndInt = NULL;

	// Cache various target platform version information
	DWORD dwVersion = ::GetVersion();
	nWinVer = (LOBYTE(dwVersion) << 8) + HIBYTE(dwVersion);
	bWin32s = (dwVersion & 0x80000000) != 0;
	bWin4 = (BYTE)dwVersion >= 4;
#if _MFC_VER < 0x0300
	// Under Win95 MSDOS Version is 7
	bWin4 |= HIBYTE(HIWORD(dwVersion)) >= 7; // MSDOS7 = Win95

	// Win NT 4.0 is harder to detect. The trick is to pass
	// ask for system color which are only defined under NT 4.0
	// but not under NT 3.51 or Win3.1
	bWin4 |= ::GetSysColor(21) > 0 || ::GetSysColor(22) > 0 || ::GetSysColor(23) > 0;

	bWin31 = 1 - bWin4;
#else
	bWin31 = bWin32s && !bWin4; // Windows 95 reports Win32s
#endif
	bNotWin4 = 1 - bWin4;   // for convenience


	m_pControlFactory->InitializeApplicationComponents();
}



static void _gxdtordata(CGXAppData* pData)
{
	ASSERT(pData);
	if(pData && !pData->m_bDtorDone)
	{
		GX_DELETE_CATCH<CGXAbstractControlFactory>(pData->m_pControlFactory, _T("m_pControlFactory"));
		GX_DELETE_CATCH<CGXAbstractTabWndInterface>(pData->m_pTabWndInt, _T("m_pTabWndInt"));
		GX_DELETE_CATCH<CGXAbstractRecordInfoWndInterface>(pData->m_pRecordInfoWndInt, _T("m_pRecordInfoWndInt"));
		GX_DELETE_CATCH<CGXAbstractRecordInfoWndInterface>(pData->m_pRecordInfoSplitterWndInt, _T("m_pRecordInfoSplitterWndInt"));	
		GX_DELETE_CATCH<CObject>(pData->m_pEngineState, _T("m_pEngineState"));	
		GX_DELETE_CATCH<CObject>(pData->m_pParseState, _T("m_pParseState"));
		GX_DELETE_CATCH<CObject>(pData->m_pEvalState, _T("m_pEvalState"));
		GX_DELETE_CATCH<CObject>(pData->m_pRegexState, _T("m_pRegexState"));
		GX_DELETE_CATCH<CGXDrawingAndFormatting>(pData->m_pDaFTools, _T("m_pDaFTools")); 
		GX_DELETE_CATCH<CObject>(pData->m_pIntelliState, _T("m_pIntelliState"));
		GX_DELETE_CATCH<CNoTrackObject>(pData->m_pMemObjState, _T("m_pMemObjState")); 
		GX_DELETE_CATCH<CGXAbstractCoveredCellPoolImp>(pData->m_pCoveredCellPoolImp, _T("m_pCoveredCellPoolImp"));
		GX_DELETE_CATCH<CGXAbstractSpanCellPoolImp>(pData->m_pSpanCellPoolImp, _T("m_pSpanCellPoolImp"));
		GX_DELETE_CATCH<CGXAbstractDelayedRangePoolImp>(pData->m_pDelayedRangePoolImp, _T("m_pDelayedRangePoolImp"));
		GX_DELETE_CATCH<CGXAbstractPrintDeviceImp>(pData->m_pPrintDeviceImp, _T("m_pPrintDeviceImp"));
		GX_DELETE_CATCH<CGXAbstractStyleCompareSubsetImp>(pData->m_pStyleCompareSubsetImp, _T("m_pStyleCompareSubsetImp"));
		GX_DELETE_CATCH<CGXAbstractStyleSerializeImp>(pData->m_pStyleSerializeImp, _T("m_pStyleSerializeImp"));
		GX_DELETE_CATCH<CGXAbstractGridDocSerializeImp>(pData->m_pDocSerializeImp, _T("m_pDocSerializeImp"));
		GX_DELETE_CATCH<CGXAbstractGridProfileImp>(pData->m_pGridProfileImp, _T("m_pGridProfileImp"));
		GX_DELETE_CATCH<CGXAbstractGridParamCopyOperatorImp>(pData->m_pParamCopyOperatorImp, _T("m_pParamCopyOperatorImp"));
		GX_DELETE_CATCH<CGXAbstractGridSortMoveDataImp>(pData->m_pSortMoveDataImp, _T("m_pSortMoveDataImp"));
		GX_DELETE_CATCH<CGXAbstractDrawRotatedTextImp>(pData->m_pDrawRotatedTextImp, _T("m_pDrawRotatedTextImp"));
		GX_DELETE_CATCH<CGXAbstractDateTimeImp>( pData->m_pDateTimeImp, _T("m_pDateTimeImp"));
		GX_DELETE_CATCH<CGXAbstractDataCopyMoveCellsImp>(pData->m_pDataCopyMoveCellsImp, _T("m_pDataCopyMoveCellsImp"));
		GX_DELETE_CATCH<CGXAbstractLongOperationImp>(pData->m_pLongOperationImp, _T("m_pLongOperationImp"));
		GX_DELETE_CATCH<CGXAbstractSerializeOG5CompatibleImp>(pData->m_pSerializeOG5CompatibleImp, _T("m_pSerializeOG5CompatibleImp"));
		GX_DELETE_CATCH<CGXAbstractNumberFormattingImp>(pData->m_pNumberFormattingImp, _T("m_pNumberFormattingImp"));
		
		// QA: 31521
		POSITION pos = pData->m_autodeleteptrlist.GetHeadPosition();
		void* p = NULL;
		while(pos)
		{
			p = (void*)(pData->m_autodeleteptrlist).GetNext(pos);
			if(p != NULL)
			{
				GX_DELETE_CATCH(p , _T("AutoDeletePtr"));
			}
		}
		pData->m_autodeleteptrlist.RemoveAll();

		// We finished cleaning up.
		pData->m_bDtorDone = TRUE;
	}
}

CGXAppData::~CGXAppData()
{
	_gxdtordata(this);
}

void CGXAppData::LoadResources()
{
	// Resource Strings
	strmRedo.LoadString(GX_IDM_REDO);
	strmUndo.LoadString(GX_IDM_UNDO);
	strmUndoInfo.LoadString(GX_IDM_UNDOINFO);
	strmStoreCells.LoadString(GX_IDM_STORECELLS);
	strmRestoreCells.LoadString(GX_IDM_RESTORECELLS);
	strmCellFormatting.LoadString(GX_IDM_CELLFORMATTING);
	strmRemoveRows.LoadString(GX_IDM_REMOVEROWS);
	strmRemoveCols.LoadString(GX_IDM_REMOVECOLS);
	strmCopyText.LoadString(GX_IDM_COPYTEXT);
	strmCopyInternal.LoadString(GX_IDM_COPYINTERNAL);
	strmCutData.LoadString(GX_IDM_CUTDATA);
	strmCuttingData.LoadString(GX_IDM_CUTTINGDATA);
	strmPastingData.LoadString(GX_IDM_PASTINGDATA);
	strmPasteData.LoadString(GX_IDM_PASTEDATA);
	strmReplacingAll.LoadString(GX_IDM_REPLACINGALL);
	strmReplaceAll.LoadString(GX_IDM_REPLACEALL);
	strmSearching.LoadString(GX_IDM_SEARCHING);
	strmResizeRows.LoadString(GX_IDM_RESIZEROWS);
	strmResizeCols.LoadString(GX_IDM_RESIZECOLS);
	strmSetFrozenRows.LoadString(GX_IDM_SETFROZENROWS);
	strmSetFrozenCols.LoadString(GX_IDM_SETFROZENCOLS);
	strmUndoCurrentCell.LoadString(GX_IDM_UNDOCURRENTCELL);
	strmPasteDiffRange.LoadString(GX_IDM_PASTEDIFFRANGE);
	strmDragDropCopy.LoadString(GX_IDM_DRAGDROP_COPY);
	strmDragDropMove.LoadString(GX_IDM_DRAGDROP_MOVE);
	strmClearData.LoadString(GX_IDM_CLEARDATA);
	strmMoveRows.LoadString(GX_IDM_MOVEROWS);
	strmMoveCols.LoadString(GX_IDM_MOVECOLS);
	strmInsertRows.LoadString(GX_IDM_INSERTROWS);
	strmInsertCols.LoadString(GX_IDM_INSERTCOLS);

	GXGetWaitState()->m_sAbortText.LoadString(GX_IDS_ABORTOPERATION);
	GXGetWaitState()->m_sDefaultStatusText.LoadString(GX_IDS_PROCESSING);
	GXGetWaitState()->m_sDefaultDoneText.LoadString(GX_IDS_DONE);
	GXGetWaitState()->m_sDefaultCancelText.LoadString(GX_IDS_CANCELESC);
};

void CGXAppData::AutoDeletePtr(void* p)
{
	m_autodeleteptrlist.AddHead(p);
}

void CGXAppData::RegisterSharedScrollBar(CRuntimeClass* pRuntimeClass)
{
	CPtrList* pList = &m_pSharedScrollBarRuntimeClassList;
	POSITION pos = pList->GetHeadPosition();
	while (pos)
	{
		if ((CRuntimeClass*) pList->GetNext(pos) == pRuntimeClass)
			return;
	}

	pList->AddTail(pRuntimeClass);
}

CWnd* CGXAppData::GetSharedScrollbarParentWnd(const CWnd* pChildWnd) const
{
	const CPtrList* pList = &m_pSharedScrollBarRuntimeClassList;
	POSITION pos = pList->GetHeadPosition();
	CWnd* pWnd = NULL;
	while (pos && pWnd == NULL)
	{
		CRuntimeClass* pRuntimeClass = (CRuntimeClass*) pList->GetNext(pos);
		pWnd = GXGetParentWnd(pChildWnd, pRuntimeClass, TRUE);
	}

	return pWnd;
}

// Object Mapping (Parent Param for StylesMap, data object etc).

// Call from CGXGridCore::OnInitialUpdate

void CGXAppData::AttachGridToObject(void* pObj, CGXGridCore* pGrid)
{
	CPtrList*& pList = (CPtrList*&) m_mapObjectToGridList[pObj];
	if (pList == NULL)
		pList = new CPtrList;

	pList->AddTail(pGrid);
}

CGXGridCore* CGXAppData::GetFirstGrid(void* pObj) const
{
	CPtrList* pList = NULL;
	
	if (m_mapObjectToGridList.Lookup(pObj, (void*&) pList))
		return (CGXGridCore*) pList->GetHead();

	return NULL;
}

// Call from CGXGridCore dtor

void CGXAppData::DetachGrid(CGXGridCore* pGrid)
{
	for (POSITION pos = m_mapObjectToGridList.GetStartPosition(); pos; )
	{
		CPtrList* pList;
		void* pObj;
		m_mapObjectToGridList.GetNextAssoc(pos, pObj, (void*&) pList);

		if (pList)
		{
			POSITION pos2 = pList->GetHeadPosition();
			while (pos2)
			{
				POSITION curpos2 = pos2;
				CGXGridCore* pGrid2 = (CGXGridCore*) pList->GetNext(pos2);
				if (pGrid2 == pGrid)
					pList->RemoveAt(curpos2);
			}

			if (pList->GetCount() == NULL)
			{
				delete pList;		   
				m_mapObjectToGridList.RemoveKey(pObj);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// System settings

// Constants
#define CX_BORDER   1
#define CY_BORDER   1

GX_SYS_DATA::GX_SYS_DATA()
{
	m_nSysColors = 0;

	// Cache various target platform version information
	DWORD dwVersion = ::GetVersion();
	bWin4 = (BYTE)dwVersion >= 4;

	// Standard cursors
	hcurHSplit = NULL;
	hcurVSplit = NULL;
	hcurArrow = ::LoadCursor(NULL, IDC_ARROW);
	ASSERT(hcurArrow != NULL);

	// cxBorder2 and cyBorder are 2x borders for Win4
	cxBorder2 = bWin4 ? CX_BORDER*2 : CX_BORDER;
	cyBorder2 = bWin4 ? CY_BORDER*2 : CY_BORDER;

	if(RW_VISUALSTYLE_WINDOWSCLASSIC == RWGetVisualStyle())
	{
		// QA: 32120 - Resolution to bitmap initialization under Windows Classic.
		UpdateSysColors();
	}
}

GX_SYS_DATA::~GX_SYS_DATA()
{
}

void GX_SYS_DATA::UpdateSysColors()
{
#if(WINVER >= 0x0400)
	m_nSysColors = 24;
#else
	m_nSysColors = 20;
#endif

	for (int i = 0; i < m_nSysColors; i++)
		m_argbSysColors.SetAtGrow(i, ::GetSysColor(i));

	clrBtnFace       = ::GetSysColor(COLOR_BTNFACE);
	clrBtnShadow     = ::GetSysColor(COLOR_BTNSHADOW);
	clrBtnHilite     = ::GetSysColor(COLOR_BTNHIGHLIGHT);
	clrWindowFrame   = ::GetSysColor(COLOR_WINDOWFRAME);
	clrText          = ::GetSysColor(COLOR_WINDOWTEXT);
	clrWindow        = ::GetSysColor(COLOR_WINDOW);
	clrHighlight     = ::GetSysColor(COLOR_HIGHLIGHT);
	clrHighlightText = ::GetSysColor(COLOR_HIGHLIGHTTEXT);
#ifdef WIN32
	clr3DLight       = ::GetSysColor(COLOR_3DLIGHT);
	clr3DDkShadow    = ::GetSysColor(COLOR_3DDKSHADOW);
#else
	clr3DLight       = ::GetSysColor(COLOR_BTNFACE);
	clr3DDkShadow    = ::GetSysColor(COLOR_WINDOWFRAME);
#endif

	// bitmaps
	if (m_bmpDownArrow.GetSafeHandle() != 0)
		m_bmpDownArrow.DeleteObject();

	if (m_bmpDownArrowDisabled.GetSafeHandle() != 0)
		m_bmpDownArrowDisabled.DeleteObject();

	GXLoadSysColorBitmap(m_bmpDownArrow, MAKEINTRESOURCE(GX_IDB_DOWNARROW));
	GXLoadSysColorBitmap(m_bmpDownArrowDisabled, MAKEINTRESOURCE(GX_IDB_DOWNARROW_DISABLED));
}

void GX_SYS_DATA::UpdateSysSettings()
{
	// Date, Time settings
	GXUpdateDateTimeSettings(); // updates static variables in gxtime.cpp
}

COLORREF GX_SYS_DATA::GetSysColor(int nIndex)
{
	if (nIndex < m_argbSysColors.GetSize())
		return m_argbSysColors[nIndex];
	else
		return ::GetSysColor(nIndex);
}

#if _MFC_VER >= 0x0400

/////////////////////////////////////////////////////////////////////////////
// GX_IME_STATE

#ifndef _GXDLL
	CThreadLocal<GX_IME_STATE>    _gxImeState;
#endif

GX_IME_STATE::GX_IME_STATE()
{
	m_pImeProxy = 0;
}

GX_IME_STATE::~GX_IME_STATE()
{
	delete m_pImeProxy;
}

#endif

///////////////////////////////////////////////////////////////////////////////
// CGXClassRegState
#ifndef _GXDLL

// QA: 32120 - Wrapping in CThreadLocal.
CThreadLocal<CGXClassRegState> _gxRegState;

CGXClassRegState::CGXClassRegState()
{
}
CGXClassRegState::~CGXClassRegState()
{
}
void CGXClassRegState::RegisterDone(AFX_MODULE_STATE*)
{
}
void CGXClassRegState::RegisterRevoke(AFX_MODULE_STATE*)
{
}

#endif

