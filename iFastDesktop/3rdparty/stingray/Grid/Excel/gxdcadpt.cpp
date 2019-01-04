///////////////////////////////////////////////////////////////////////////////
// gxdcadpt.cpp
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

#include "grid\gxdcadpt.h"

#include "grid\gxxrdrim.h"

#include "grid\gxman.h"

#include "grid\gxtbgadp.h"

#include "grid\gxwchr.h"

#include "grid\gxexhlp.h"

#include "grid\gxexhnd.h"

#include "grid\gxexmpst.h"

#pragma warning(disable: 4100 4244)


extern WCHAR* GetBiffStreamName();

#define _ID_GX_EX_CAPWINDOW 1000

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
// CGXExcelDocAdapter //////////////////////////////////////////////////////////////////////////////

CGXExcelDocAdapter::CGXExcelDocAdapter()
{
	// shared data
	m_pProperties = NULL;
	m_pStylesMap = NULL;
	m_pPrintDevice = NULL;

	// should we save out as .xls
	m_bWriteAsExcel = TRUE;
	
	// the number of tabs
	m_nTabCount = 0;
	
	m_pParamManager = NULL;

	// The Excel reader class
	m_pExcelReader = NULL;
	
	// default is document read mode
	m_bDocReadMode = TRUE;

	m_bWaitMode = TRUE;
}


CGXExcelDocAdapter::~CGXExcelDocAdapter()
{
	// perform cleanup here
	if(m_pParamManager != NULL)
		delete m_pParamManager;
	
	if(m_pExcelReader != NULL)
		delete m_pExcelReader;
}

void CGXExcelDocAdapter::ImplementExcelReadWrite()
{
	ASSERT(m_pExcelReader == NULL); // Error ImplementExcelRead was already called
	
	m_pExcelReader = new CGXExcelReaderImpl();
}


CGXDocument* CGXExcelDocAdapter::GetParentDoc()
{
	CGXDocument* pDocument = dynamic_cast<CGXDocument*>(this);
	
	ASSERT(pDocument != NULL); //Error->This has to be a CGXDocument
	
	return pDocument;
}


CGXExcelDocAdapter* CGXExcelDocAdapter::GetParentDocAdapter()
{
	CGXDocument* pDocument = dynamic_cast<CGXDocument*>(this);
	
	ASSERT(pDocument != NULL); //Error->This has to be a CGXDocument
	
	CGXDocument* pParentDoc = pDocument->GetPrimaryDocument();

	ASSERT(pParentDoc != NULL);

	CGXExcelDocAdapter* pDocAdapt = dynamic_cast<CGXExcelDocAdapter*>(pParentDoc);

	return pDocAdapt;
}


UINT CGXExcelDocAdapter::GetTabCount() const
{
	return m_nTabCount;
}

void CGXExcelDocAdapter::ExcelSerializeImpl(CArchive& ar, BOOL bReadAll /* = FALSE*/)
{
	ASSERT(ar.GetFile() != NULL);
	
	if(
		(ar.IsLoading() && IsExcelFile( ar.GetFile()->GetFilePath() ) ) ||
		(!ar.IsLoading() && GetWriteAsExcel())
	  ) // If this is an Excel file read it in as an Excel file
	{
		if(ar.IsLoading())
		{
			if(bReadAll)
			{
				GetExcelReaderA()->ExcelReadImpl(ar, this);
				SetWaitMode(FALSE);
			}
			else
			{
				SetWaitMode(TRUE);
				int eMode = GetExcelReaderA()->SetReadMode(gxExReadNum);
				GetExcelReaderA()->ExcelReadImpl(ar, this);
				GetExcelReaderA()->SetReadMode(eMode);
				m_nTabCount = GetExcelReader()->GetTabCount();
			}
		}
		else
			GetExcelReaderA()->ExcelWriteImpl(ar, this);
	}
	else
	{	
		//ExcelWorkBookSerializeImpl(ar);
		// call the base class. Will call workbookSerialize as required
		GetParentDoc()->CGXDocument::Serialize(ar);
	}
}
	
// This will not be called for Excel output and input. We also assume that a single document is used for holding
// the Excel file data as parameter objects
void CGXExcelDocAdapter::ExcelWorkBookSerializeImpl(CArchive& ar)
{
	UpdateTabCount();
	
	if(ar.IsLoading())
	{
		// simply iterate through and load or write the parameter objects/other shared objects
		ar >> m_nTabCount;
		
		
		CGXParamManager* pParamManager = GetParamManager();
		
		ASSERT(pParamManager != NULL); // You will have to supply a valid param manager
		
		CGXGridParam* pParam = NULL;
		
		for (UINT nC(0); nC < m_nTabCount; nC++)
		{
			pParam = pParamManager->CreateObject(nC);
			if (nC>0)
				SetSharedComponents(nC,0);
			pParam->Serialize(ar);
			if(nC == 0)
			{
				m_pProperties = pParam->GetProperties();
				m_pStylesMap = pParam->GetStylesMap();
				m_pPrintDevice = pParam->GetPrintDevice();
			}
		}
		
		// done
		GetExcelReader()->SetTabCount(m_nTabCount);
	}
	else
	{	
		ar << m_nTabCount;
		
		CGXParamManager* pParamManager = GetParamManager();
		
		ASSERT(pParamManager != NULL); // You will have to supply a valid param manager
		
		CGXGridParam* pParam = NULL;
		
		UINT nTabCount = GetParentDoc()->GetTabManager()->GetTabCount();
		
		for (UINT nC(0); nC < nTabCount; nC++)
		{
			pParam = pParamManager->CreateObject(nC);
			pParam->Serialize(ar);
		}
	}
}

CGXGridParam* CGXExcelDocAdapter::GetParam(UINT index) 
{
	CGXParamManager* pParamManager = GetParamManager();

	ASSERT(pParamManager != NULL); // You will have to supply a valid param manager
		
	CGXGridParam* pParam = NULL;

	pParam = pParamManager->CreateObject(index);
	
	return pParam;
}

int CGXExcelDocAdapter::GetIndex(const CObject* pObject)
{
	CGXTabWnd* pgxTabWnd = GetTabWnd();
	
	CGXTabBeam& tabbeam = pgxTabWnd->GetBeam(); 
		
	int nRetval = tabbeam.FindTab(pObject);
	
	ASSERT(nRetval != -1); //Error---> This window is not found in this tab
	
	return nRetval;
}

CGXGridCore* CGXExcelDocAdapter::GetGrid(UINT index)
{
	CGXTabWnd* pgxTabWnd = GetTabWnd();

	ASSERT(index >= 0 && index <= (UINT) pgxTabWnd->GetBeam().GetCount()); // Invalid index specified

	CObject* pOb = pgxTabWnd->GetBeam().GetTab(index).pExtra;

	CGXGridCore* pCore = dynamic_cast<CGXGridCore*>(pOb);

	ASSERT(pCore != NULL); //Error----> This is not a grid view that we can interact with

	return pCore;
}

CGXTabWnd* CGXExcelDocAdapter::GetTabWnd()
{
	CGXTabWndMgr* pTabMgr = GetParentDoc()->GetPrimaryDocument()->GetTabManager();
	ASSERT(pTabMgr != NULL); //Error---> There has to be a valid tab window manager

	CGXTabWndAdapter* pTabWndAdapter = pTabMgr->GetTabWndAdapter();
	ASSERT(pTabWndAdapter != NULL); //Error--->There has to be a valid adapter

	CGXGridTabWndAdapter* pGridTabWndAdapter = dynamic_cast<CGXGridTabWndAdapter*>(pTabWndAdapter);

	ASSERT(pGridTabWndAdapter != NULL); // Error----> This has to be a pGridTabWndAdapter. We access the CGXTabWnd
	// directly.

	CGXTabWnd* pgxTabWnd = pGridTabWndAdapter->GetTabWnd();

	return pgxTabWnd;
}

void CGXExcelDocAdapter::InitializeParam(UINT index, UINT nIndexPrim)
{
	if(index == 0 && nIndexPrim == 0xFFFF)
		GetParentDoc()->SetPrimaryDocument(GetParentDoc());
	
	CGXGridParam* pParam = GetParam(index);
	
	ASSERT(pParam != NULL); // Error ----> error with allocating or locating parameter objects

	if(index == 0 && nIndexPrim == 0xFFFF)
		AllocSharedComponents();

	SetSharedComponents(index, nIndexPrim);
}

void CGXExcelDocAdapter::AllocSharedComponents()
{
	m_pProperties = new CGXProperties;
	m_pStylesMap = new CGXStylesMap;
	
	m_pStylesMap->CreateStandardStyles();
	
	m_pPrintDevice = new CGXPrintDevice;
}

void CGXExcelDocAdapter::SetSharedComponents(UINT index, UINT nIndexPrim)
{
	BOOL bOwn = (index == 0 && nIndexPrim == 0xFFFF);
		
	CGXGridParam* pParam = GetParam(index);
	
	ASSERT(pParam != NULL); // Error ----> error with allocating or locating parameter objects

	if(pParam == NULL)
		return;
	
	if(nIndexPrim != 0xFFFF && index == nIndexPrim)
		return;

	pParam->SetStylesMap(m_pStylesMap, bOwn);
	pParam->SetProperties(m_pProperties, bOwn);
	pParam->SetPrintDevice(m_pPrintDevice, bOwn);
}


BOOL CGXExcelDocAdapter::IsExcelFile(const TCHAR* lpszFileName) const
{
	CString strFileName(lpszFileName);

	BOOL b(FALSE);

   CString str = strFileName.Right(3);
   str.MakeLower();
    if (str == _T("xls"))
		b = TRUE;
	else
		b = FALSE;

	WCHAR* pszW = NULL;

#ifdef _UNICODE
	pszW = lpszFileName;
#else
	pszW = CGXWChar::ConvertDef(lpszFileName);
#endif
	
	ASSERT(pszW != NULL);

	if(pszW == NULL)
		return FALSE;
	
	if ( ::StgIsStorageFile(pszW) != S_OK )
		b = FALSE;
	else
		b = (b && TRUE);

#ifndef _UNICODE	
	if(pszW)
		CGXWChar::FreeAllocData(pszW);
#endif

	return b;
}

BOOL CGXExcelDocAdapter::GetWriteAsExcel() const
{
	return m_bWriteAsExcel;
}

void CGXExcelDocAdapter::SetWriteAsExcel(BOOL b)
{
	m_bWriteAsExcel = b;
}
	
CGXExcelReader* CGXExcelDocAdapter::GetExcelReader() const
{
	return m_pExcelReader;
}

CGXExcelReader* CGXExcelDocAdapter::GetExcelReaderA()
{
	return m_pExcelReader;
}

void CGXExcelDocAdapter::ReadExcelData()
{
	// This is implemented in CGXExcelDocAdapter
	if(IsExcelFile(m_strFilePath) == TRUE)
		GetExcelReaderA()->ExcelReadImpl(m_strFilePath, this);
}


// The parameter object manager
CGXParamManager* CGXExcelDocAdapter::GetParamManager()
{
	CGXExcelDocAdapter* pDocAdapt = GetParentDocAdapter();
	
	if(pDocAdapt->m_pParamManager == NULL)
		pDocAdapt->m_pParamManager = new CGXParamManager(RUNTIME_CLASS(CGXGridParam));
	
	return pDocAdapt->m_pParamManager;
}

void CGXExcelDocAdapter::SetWaitMode(BOOL bWaitMode)
{
	m_bWaitMode = bWaitMode;
}

BOOL CGXExcelDocAdapter::GetWaitMode()
{
	return m_bWaitMode;
}


void CGXExcelDocAdapter::SetFilePath(LPCTSTR pszFilePath)
{
	m_strFilePath = pszFilePath;
}

const CString& CGXExcelDocAdapter::GetFilePath() const
{
	return m_strFilePath;
}

void CGXExcelDocAdapter::UpdateTabCount()
{
	m_nTabCount = GetExcelReader()->GetTabCount();
}


///////////////////////////////////////////////////////////////////////
// CGXExcelWndDocAdapter implementation ///////////////////////////////
///////////////////////////////////////////////////////////////////////

CGXExcelWndDocAdapter::CGXExcelWndDocAdapter()
{
	// always instantiated for Excel Read Write
	ImplementExcelReadWrite();
	UpdateTabCount();
}

CGXExcelWndDocAdapter::~CGXExcelWndDocAdapter()
{
}

CGXGridParam* CGXExcelWndDocAdapter::GetParam(UINT index) 
{
	ASSERT(index == GetExcelReader()->GetReadIndex() || index == 0); // This is only to be used with single tabs
	
	ASSERT(m_pCore != NULL);
	if(m_pCore == NULL)
		return NULL;

	return m_pCore->GetParam();
}

void CGXExcelWndDocAdapter::InitializeParam(UINT index)
{
	ASSERT(index == GetExcelReader()->GetReadIndex() || index == 0); // This is only to be used with single tabs
	
	CGXExcelDocAdapter::InitializeParam(index, 0xFFFF);
}

void CGXExcelWndDocAdapter::SetGrid(CGXGridCore* pCore)
{
	m_pCore = pCore;
}

CGXGridCore* CGXExcelWndDocAdapter::GetGrid(UINT index)
{
	ASSERT(index == GetExcelReader()->GetReadIndex() || index == 0); // This is only to be used with single tabs
	return m_pCore;
}

int CGXExcelWndDocAdapter::GetIndex(const CObject* /*pObject*/)
{
	return 0; // the only possible index
}

CGXDocument* CGXExcelWndDocAdapter::GetParentDoc()
{
	// There is a no parent document for a CGXExcelWndDocAdapter
	return NULL;
}

CGXTabWnd* CGXExcelWndDocAdapter::GetTabWnd()
{
	ASSERT(0); // There is a no tab window associated with a CGXExcelWndDocAdapter
	return NULL;
}

CGXExcelDocAdapter* CGXExcelWndDocAdapter::GetParentDocAdapter()
{
	ASSERT(0); // There is a no parent document for a CGXExcelWndDocAdapter
	return NULL;
}

void CGXExcelWndDocAdapter::ExcelSerializeImpl(CArchive& ar, BOOL bReadAll /* = FALSE*/)
{
	ASSERT(bReadAll == TRUE); // There is no two pass read associated with this adapter

	// call the base class with bReadAll set to TRUE
	CGXExcelDocAdapter::ExcelSerializeImpl(ar, TRUE);
}

void CGXExcelWndDocAdapter::ReadExcelFile(const CString& strFileName, UINT index)
{
	int eMode = GetExcelReaderA()->SetReadMode(gxExReadNum|gxExReadIndex);
	GetExcelReaderA()->ExcelReadImpl(strFileName, this);
	UpdateTabCount();

	GetExcelReaderA()->SetReadMode(gxExReadIndex|gxExReadAll);
	GetExcelReaderA()->SetReadIndex(index);
	GetExcelReader()->ExcelReadImpl(strFileName, this);
	
	// restore old mode
	GetExcelReaderA()->SetReadMode(eMode);
}


void CGXExcelWndDocAdapter::SaveExcelFile(const CString& strFileName)
{
	GetExcelReader()->SetTabCount(1);
	UpdateTabCount();

	CGXGridParam* pParam = GetParam(0);
	if((pParam->m_sSheetName).IsEmpty())
		pParam->m_sSheetName = _T("MyTab");

	GetExcelReader()->ExcelWriteImpl(strFileName, this);
}

void CGXExcelWndDocAdapter::ExcelWorkBookSerializeImpl(CArchive& ar)
{
	if(ar.IsLoading())
	{
		CGXGridParam* pParam = GetParam(0);
		ar >> pParam;
	}
	else
	{
		CGXGridParam* pParam = GetParam(0);
		ar << pParam;
	}
}


////////////////////////////////////////////////////////////////////////////////
// class CGXExcelClipHandler
////////////////////////////////////////////////////////////////////////////////
CGXExcelClipHandler::CGXExcelClipHandler(BOOL bFormula /*= FALSE*/)
{
	m_uiData = ::RegisterClipboardFormat(_T("BIFF8"));
	ASSERT(m_uiData != NULL); // Error-->Clipboard format registration for BIFF 8 fails
	// BIFF 8 clipboard support will be unavailable
	
	m_bFormula = bFormula;
}	

CGXExcelClipHandler::~CGXExcelClipHandler()
{
	DestroyGridWnd();
}

CGXGridWnd* CGXExcelClipHandler::GetGridWnd()
{
	if(m_gridWnd.m_hWnd == NULL)
	{
		BOOL b = m_gridWnd.Create(WS_CHILD, CRect(0, 0, 0, 0), CWnd::GetDesktopWindow(), _ID_GX_EX_CAPWINDOW);
		ASSERT(b); // Unable to create captive window...
		
		if(m_bFormula)
			m_gridWnd.EnableFormulaEngine();
	
		m_gridWnd.Initialize();
		m_gridWnd.ShowWindow(SW_SHOW);
	
		if(m_bFormula)
			m_gridWnd.m_nClipboardFlags |= GX_DNDEXPRESSION;
	}
	
	return &m_gridWnd;
}

void CGXExcelClipHandler::DestroyGridWnd()
{
	if(m_gridWnd.m_hWnd != NULL)
	{
		BOOL b = m_gridWnd.DestroyWindow();
		ASSERT(b);
	}
}

void CGXExcelClipHandler::ResetGridWnd()
{
	ASSERT_VALID(&m_gridWnd);
	if(m_gridWnd.m_hWnd)
	{
		m_gridWnd.SetRowCount(0);
		m_gridWnd.SetColCount(0);
	}
}

BOOL CGXExcelClipHandler::Copy(CGXGridCore* pCore, const CGXRange& rg)
{
	ResetGridWnd();
	
	CGXGridWnd* pGridWnd = GetGridWnd();
	
	BOOL bSuccess(TRUE);

	// copy this range to the captive grid
	CGXRangeList list;
	CGXRange range(rg);

	// workaround for range boundaries problem
	BOOL bRowLimit = FALSE;
	BOOL bColLimit = FALSE;

	if(range.bottom == pCore->GetRowCount())
		bRowLimit = TRUE;

	if(range.right == pCore->GetColCount())
		bColLimit = TRUE;

	if(range.IsCells())
	{
		if(range.bottom < pCore->GetRowCount())
			range.bottom++;

		if(range.right < pCore->GetColCount())
			range.right++;
	}

	list.AddHead(&range);
	bSuccess = pCore->CGXGridCore::CopyRange(list);
	list.RemoveHead();

	if(bSuccess == FALSE)
		return FALSE;

	pGridWnd->m_nClipboardFlags &= (~GX_DNDNOAPPENDROWS);
	pGridWnd->m_nClipboardFlags &= (~GX_DNDNOAPPENDCOLS);

	pGridWnd->SetRowCount(1);
	pGridWnd->SetColCount(1);
	pGridWnd->SetCurrentCell(1,1);
	pGridWnd->Paste();

	if(bRowLimit)
		pGridWnd->SetRowCount(pGridWnd->GetRowCount()+1);

	if(bColLimit)
		pGridWnd->SetColCount(pGridWnd->GetColCount()+1);

	
	ASSERT(pGridWnd->OpenClipboard());
	::EmptyClipboard();
	::CloseClipboard();

	// create a storage and serialize to it
	LPSTORAGE pStorage = NULL;
	HRESULT hr = ::StgCreateDocfile(NULL, STGM_READWRITE | 
								  STGM_SHARE_EXCLUSIVE | STGM_DIRECT | STGM_DELETEONRELEASE, 0, &pStorage);

	if(FAILED(hr))
		throw egxFailDocCreate;
		
	LPSTREAM ps = NULL;
	hr = pStorage->CreateStream(GetBiffStreamName(), STGM_READWRITE | STGM_SHARE_EXCLUSIVE |
						STGM_DIRECT, 0, 0, &ps);
	
	if(FAILED(hr))
		egxStreamFailCreate;

	CGXExcelWndDocAdapter docAdapt;
	docAdapt.SetGrid(pGridWnd);

	CGXExcelReader* pReader = docAdapt.GetExcelReader();
	ASSERT(pReader != NULL); // Error there has to be a Excel reader instance available
			
	if(pReader == NULL)
	throw egxCodeError;
			
	CGXExcelReaderImpl* pImplRdr = dynamic_cast<CGXExcelReaderImpl*>(pReader);
	ASSERT(pImplRdr != NULL); // Error the Excel reader has to be of type CGXExcelReaderImpl
	
	if(pImplRdr == NULL)
		throw egxCodeError;

	CGXExcelHandler::SetClipMode(TRUE);
	
	pImplRdr->SetTabCount(1);
	docAdapt.UpdateTabCount();

	pImplRdr->WriteBIFFHelper(ps, &docAdapt);
	CGXExcelHandler::SetClipMode(FALSE);
	
	ps->Release();
	// not really required
	hr = pStorage->Commit(STGC_DEFAULT);
	
	if(FAILED(hr))
	{
		GX_EX_FMT_TRACE("CGXExcelClipHandler::Copy");
		pStorage->Release();
		return FALSE;
	}
	
	/////////////////////////////////////////////////////////////////
	HGLOBAL hData = 0;
	
	// open memory file
	CSharedFile clipb (GMEM_MOVEABLE|GMEM_DDESHARE|GMEM_ZEROINIT);

	list.AddHead(&range);
	BOOL b = pCore->CopyTextToFile(clipb, list);
	list.RemoveHead();

	if (b)
		hData = clipb.Detach();
	///////////////////////////////////////////////////////////////


	CGXDataObjectImpl* pDataObject = new CGXDataObjectImpl(pStorage, hData);

	pDataObject->AddRef();

	hr = ::OleSetClipboard(pDataObject);
	
	if(FAILED(hr))
	{
		GX_EX_FMT_TRACE("CGXExcelClipHandler::Copy");
	}

	pDataObject->Release();

	hr = ::OleFlushClipboard();

	if(FAILED(hr))
	{
		GX_EX_FMT_TRACE("CGXExcelClipHandler::Copy");
	}

	CGXExcelHandler* pEH = GXExGetHandlerMap()->LocateHandler(typeDimension);
	pEH->ResetInternalState();

	return TRUE;
}

BOOL CGXExcelClipHandler::Paste(CGXGridCore* pCore, const CGXRange& /*rg*/)
{
	// check clipboard flags
	if (pCore->m_nClipboardFlags & GX_DNDSTYLES)
	{
		// check if this is internal format
		if( ::IsClipboardFormatAvailable(pCore->m_pAppData->m_uiStylesClipboardFormat) )
			return FALSE;
		
		// check if we have BIFF 8 available
		if(! ::IsClipboardFormatAvailable(m_uiData) )
			return FALSE;
		
		// we close the clipboard that the grid woulf have opened
		if(!CloseClipboard())
			return FALSE;

		// we know that BIFF 8 is now available
		IDataObject* pDataObj = NULL;
	
		HRESULT hr =  ::OleGetClipboard(&pDataObj);
	
		if(FAILED(hr))
			return FALSE;

		// get the Storage from the clipboard 
		FORMATETC fetc;
		fetc.cfFormat = m_uiData;
		fetc.tymed = TYMED_ISTORAGE;     
		fetc.dwAspect = DVASPECT_CONTENT;
		fetc.lindex = -1;

		STGMEDIUM stg;
		
		hr = pDataObj->GetData(&fetc,  //Pointer to the FORMATETC structure
						&stg  //Pointer to the STGMEDIUM structure
					);
		
		if(FAILED(hr))
			return FALSE;

		// open the workbook stream
		LPSTREAM pstm = NULL;
		
		OLECHAR* pszStream = GetBiffStreamName();
		hr = stg.pstg->OpenStream(pszStream, NULL, STGM_READ | STGM_SHARE_EXCLUSIVE,
													0, &pstm);
		
		
		if(FAILED(hr))
		{
			::ReleaseStgMedium(&stg);
			return FALSE;
		}

		// let the handlers know that we are in clipboard mode
		CGXExcelHandler::SetClipMode(TRUE);
		
		// get the captive grid window to be used
		CGXGridWnd* pGridWnd = GetGridWnd();
		
		if(pGridWnd == NULL)
		{
			if(pstm != NULL)
				pstm->Release();
		
			::ReleaseStgMedium(&stg);
			return FALSE;
		}

		pGridWnd->SetRowCount(GX_EX_DEFAULTSIZEROW);
		pGridWnd->SetColCount(GX_EX_DEFAULTSIZECOL);

		CGXExcelWndDocAdapter docAdapt;
		docAdapt.SetGrid(pGridWnd);
	
		// add pre read code here
		CGXGridParam* pParam = pGridWnd->GetParam();
		ASSERT(pParam != NULL);
		
		if(pParam == NULL)
		{
			if(pstm != NULL)
				pstm->Release();
		
			::ReleaseStgMedium(&stg);
			return FALSE;
		}

		pParam->EnableUndo(FALSE);

		try
		{
			CGXExcelReader* pReader = docAdapt.GetExcelReader();
			ASSERT(pReader != NULL); // Error there has to be a Excel reader instance available
			
			if(pReader == NULL)
				throw egxCodeError;
			
			CGXExcelReaderImpl* pImplRdr = dynamic_cast<CGXExcelReaderImpl*>(pReader);
			ASSERT(pImplRdr != NULL); // Error the Excel reader has to be of type CGXExcelReaderImpl
	
			if(pImplRdr == NULL)
				throw egxCodeError;

			pImplRdr->SetTabCount(1);
			docAdapt.UpdateTabCount();
	
			pImplRdr->ReadStream(pstm, &docAdapt);
		}
		catch(egxExcelRWFlags flags)
		{
			GX_EX_FMT_TRACE("OG Pro Error: Clipboard paste fails.")
			CGXExRWErrorHandler::HandleError(flags);
			
			if(pstm != NULL)
				pstm->Release();
		
			::ReleaseStgMedium(&stg);
			
			GX_THROW_LAST
			return FALSE;
		}

		// add post read code here
		pParam->EnableUndo(TRUE);
		
		// now copy the area over and do a paste internally
		CGXExcelHandler* pEH = GXExGetHandlerMap()->LocateHandler(typeDimension);

		ASSERT(pEH != NULL); // Interpretation of Dimensions is required. Maybe your map excluded this???

		if(pEH == NULL)
		{
			if(pstm != NULL)
				pstm->Release();
		
			::ReleaseStgMedium(&stg);
			return FALSE;
		}


		CGXExcelDimensionHandler* pH = dynamic_cast<CGXExcelDimensionHandler*>(pEH);

		ASSERT(pH != NULL); // Interpretation of Dimensions is required. Maybe your map used a different class for this???

		if(pH == NULL)
		{
			if(pstm != NULL)
				pstm->Release();
		
			::ReleaseStgMedium(&stg);
			return FALSE;
		}

		pGridWnd->CopyRange(CGXRange(pH->m_dimStruct.rwMic+1, pH->m_dimStruct.colMic+1, pH->m_dimStruct.rwMac, pH->m_dimStruct.colMac));

		// the actual paste operation. this will be accepted as internal data format
		pCore->Paste();

		// reset clipboard mode to FALSE
		CGXExcelHandler::SetClipMode(FALSE);
		
		// state is retained during clipboard mode
		pH->ResetInternalState();

		if(pstm != NULL)
			pstm->Release();
	
		::ReleaseStgMedium(&stg);
		
		ResetGridWnd();

		return TRUE;
	}
	else
		return FALSE;
}

BOOL CGXExcelClipHandler::CanCopy(CGXGridCore* /*pCore*/)
{
	if(m_uiData)
		return TRUE;
	else
		return FALSE;
}

BOOL CGXExcelClipHandler::CanPaste(CGXGridCore* /*pCore*/)
{
	if(!::IsClipboardFormatAvailable(m_uiData) )
			return FALSE;
	else
		return TRUE;
}




