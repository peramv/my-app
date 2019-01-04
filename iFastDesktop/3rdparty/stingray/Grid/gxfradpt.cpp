///////////////////////////////////////////////////////////////////////////////
// gxfradpt.cpp : Function implementations for the frame adapter class
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

#ifdef _GXDLL
#undef AFXAPI_DATA
#define AFXAPI_DATA __based(__segname("_DATA"))
#endif

#include "grid\gxfradpt.h"

#include "grid\gxvw.h"

#include "grid\gxdoc.h"

#include "grid\gxtmpl.h"

#include "grid\gxtbmgr.h"

#include "grid\gxapatr.h"

#include "grid\gxmsg.h"

#include "grid\gxchfrm.h"

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXTABSER")
#endif


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CGXFrameAdapter construction/destruction

CGXFrameAdapter::CGXFrameAdapter()
{
	m_pWndPointer = NULL;

	//pointer to store the create context for delayed creation of the tab window
	m_pContext = NULL;
	// tab creation information
	m_pTabCreateInfo = NULL;

	m_pDefViewClass = RUNTIME_CLASS(CGXGridView);
	m_pDefDocClass = NULL;

	// default number of tabs
	m_nSize = GX_DEFNUMTABS;
}

void CGXFrameAdapter::SetWindow(CWnd* pWnd)
{
	m_pWndPointer = pWnd;
}

CWnd* CGXFrameAdapter::GetWindow() const
{
	return m_pWndPointer;
}


CGXFrameAdapter::~CGXFrameAdapter()
{
	// delete the stashed createcontext
	if(m_pContext != NULL)
		delete m_pContext;
	
	// m_pTabCreateInfo should have been freed in CanFreeTabCreateInfo
	ASSERT(m_pTabCreateInfo == NULL);
}

/////////////////////////////////////////////////////////////////////////////
// CGXFrameAdapter message handlers

void CGXFrameAdapter::SetDocRuntimeClass(CRuntimeClass* pRClass)
{
	ASSERT( pRClass != NULL );
	ASSERT( pRClass->IsDerivedFrom(RUNTIME_CLASS(CGXDocument))); // the document class has to be derived from CGXDocument -->END

	m_pDefDocClass = pRClass;
	
	TRACE0("OG Info: CGXFrameAdapter::SetDocRuntimeClass called\n");
	TRACE1("OG Info: Runtime class set to %s\n", pRClass->m_lpszClassName);
}

void CGXFrameAdapter::SetViewRuntimeClass(CRuntimeClass* pRClass)
{
	ASSERT( pRClass != NULL );
	ASSERT( pRClass->IsDerivedFrom(RUNTIME_CLASS(CView))); // the view class has to be derived from CView -->END

	m_pDefViewClass = pRClass;
	
	TRACE0("OG Info: CGXFrameAdapter::SetViewRuntimeClass called\n");
	TRACE1("OG Info: Runtime class set to %s\n", pRClass->m_lpszClassName);
}

void CGXFrameAdapter::SetNumberOfTabs(int nTabs)
{
	ASSERT(m_nSize); // 0 tabs not allowed -->END

	m_nSize = nTabs;
}

int CGXFrameAdapter::GetNumberOfTabs() const
{
	return m_nSize;
}


BOOL CGXFrameAdapter::HandleOnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	m_pContext =  new CCreateContext;
	
	memcpy(m_pContext, pContext, sizeof(CCreateContext));

	return TRUE;

	GX_UNUSED_ALWAYS(lpcs);
}

CGXAppAdapter* CGXFrameAdapter::GetApplicationAdapter() const 
{
	CGXAppAdapter* pAppAdapt = dynamic_cast<CGXAppAdapter*>(AfxGetApp());
			
	ASSERT(pAppAdapt != NULL); // did you derive your app class from CGXAppAdapter?
	
	return pAppAdapt;
}


// This function can be overriden to change the TabCreateInfo used
CGXTabCreateInfo* CGXFrameAdapter::GetTabCreateInfo()
{
	ASSERT(m_pDefDocClass != NULL); // error..did you initialize m_pDefDocClass with a call to SetDocRuntimeClass?
	// Also, please check if you wish to initialize the view runtime class SetViewRuntimeClass.
	
	CGXAppAdapter* pAppAdapt = GetApplicationAdapter();
	
	CGXTabCreateInfo* pInfo = new CGXTabCreateInfo[m_nSize];
	
	ASSERT(pInfo != NULL);
	
	// initialize the primary with the correct create context
	pInfo[GetTabManager()->GetPrimaryIndex()].SetCreateContext(m_pContext);

	CCreateContext cc;
	cc.m_pNewViewClass = m_pDefViewClass; // runtime class of view to create or NULL
	cc.m_pCurrentDoc = NULL;

	// for creating MDI children (CMDIChildWnd::LoadFrame)
	cc.m_pNewDocTemplate = pAppAdapt->GetDocTemplate(m_pDefViewClass, m_pDefDocClass);

	
	// rest will use defaults
	for(int i = 0; i < m_nSize; i++)
	{
		// initialize all but the primary
		if(i != GetTabManager()->GetPrimaryIndex() )
			pInfo[i].Initialize(&cc);
	}
	
	m_pTabCreateInfo = pInfo;

	OnChangeInitTabCreateInfo(pInfo);

	return pInfo;
}

// override this function if you want to make any changes to the generated tab create information
void CGXFrameAdapter::OnChangeInitTabCreateInfo(CGXTabCreateInfo*& pTabCreateInfo)
{
	// no implementation
	
	GX_UNUSED_ALWAYS(pTabCreateInfo);
}

void CGXFrameAdapter::CanFreeTabCreateInfo()
{
	if(m_pTabCreateInfo)
		delete[] m_pTabCreateInfo;
	
	m_pTabCreateInfo = NULL;

	TRACE0("OG Info: Freeing tab creation info in workbook mode\n");
}

CGXTabWndMgr* CGXFrameAdapter::GetTabManager() const
{
	CGXAppAdapter* pAppAdapt = dynamic_cast<CGXAppAdapter*>(AfxGetApp());
	ASSERT(pAppAdapt != NULL); // did you derive your app class from CGXAppAdapter?
	
	ASSERT(m_pContext != NULL); // We need a valid create context --> END

	CGXTabWndMgr* pMgr = pAppAdapt->GetTabManager(GetWindow()->GetRuntimeClass(), m_pContext->m_pCurrentDoc);
	
	ASSERT(pMgr != NULL);

	return pMgr;
}

LRESULT CGXFrameAdapter::InitNewHandler(WPARAM wParam, LPARAM lParam)
{
	GX_UNUSED_ALWAYS(lParam);

	BOOL bOnExistingData = wParam ? TRUE:FALSE ;
	
	CGXTabWndMgr* pMgr = GetTabManager(); 
	CGXTabCreateInfo* pInfo = NULL;
		
	if(bOnExistingData)
	{
		//access tab create information
		CGXTabCreateArray* pArTabCreateInfo = (CGXTabCreateArray*) wParam;	
		ASSERT(pArTabCreateInfo != NULL);
		pInfo = NULL;
		m_nSize = (int)pArTabCreateInfo->GetSize();
	}
	else
		pInfo = GetTabCreateInfo();
	
	if(bOnExistingData)
	{
		CMDIChildWnd* pChild = dynamic_cast<CMDIChildWnd*>(this);
		ASSERT(pChild != NULL); // Error this can be be used only when you have a CMDIChildWnd derived class as the derived class
		pMgr->CreateSupTabs(pInfo, pChild, m_nSize);
	}	
	else
	{
		pMgr->SetParent(GetWindow());
		pMgr->CreateTabs(pInfo, m_nSize);
	}

	if(!bOnExistingData)
		CanFreeTabCreateInfo();
	else
	{
		if(pInfo)
			delete[] pInfo;
	}
	return 0;
}

// When initializing from a file
LRESULT CGXFrameAdapter::InitFromFileHandler(WPARAM, LPARAM)
{
	CGXAppAdapter* pAppAdapt = dynamic_cast<CGXAppAdapter*>(AfxGetApp());
	ASSERT(pAppAdapt != NULL);
	
	ASSERT(m_pContext != NULL); // We need a valid create context --> END
	
	CGXTabWndMgr* pMgr = pAppAdapt->GetTabManager(GetWindow()->GetRuntimeClass(), m_pContext->m_pCurrentDoc);

	pMgr->SetParent(GetWindow());
	pMgr->CreateTabs(NULL);
	
	return 0;
}


void CGXFrameAdapter::GetInsertInfo(int nInsertBefore, CGXTabCreateInfo* pTabCreateInfo, UINT& nID)
{
	// get the application adapter
	CGXAppAdapter* pAppAdapt = GetApplicationAdapter();

	// the default is that there is no change to the ID
	nID;
	
	CCreateContext cc;
	cc.m_pNewViewClass = m_pDefViewClass; // runtime class of view to create or NULL
	cc.m_pCurrentDoc = NULL;

	// for creating MDI children (CMDIChildWnd::LoadFrame)
	cc.m_pNewDocTemplate = pAppAdapt->GetDocTemplate(m_pDefViewClass, m_pDefDocClass);

	pTabCreateInfo->Initialize(&cc);

	OnChangeInsertInfo(nInsertBefore, pTabCreateInfo, nID);
	
}

// override this function to supply actual insert information
void CGXFrameAdapter::OnChangeInsertInfo(int& nInsertBefore, CGXTabCreateInfo*& pTabCreateInfo, UINT& nID)
{
	//set the label for instance
	CString strLabel;
	strLabel.LoadString(GX_IDS_WKBOOKINSERTTAG);
	pTabCreateInfo->SetLabel(strLabel);
	
	GX_UNUSED_ALWAYS(nID);
	GX_UNUSED_ALWAYS(nInsertBefore);
}

void CGXFrameAdapter::InsertWorkSheetHandler( BOOL bBefore)
{
	UINT nID(0);

	CGXTabWndMgr* pMgr = GetTabManager();
	
	ASSERT(pMgr != NULL);

	CGXTabCreateInfo* pTabCreateInfo = new CGXTabCreateInfo;
	
	// get insertion information
	int nInsert = pMgr->GetCursel();
	GetInsertInfo(nInsert, pTabCreateInfo, nID);

	pMgr->InsertWorkSheet(nInsert, bBefore, pTabCreateInfo, nID);

	if(pTabCreateInfo != NULL)
		delete pTabCreateInfo;
}

void CGXFrameAdapter::DeleteWorkSheetHandler()
{
	CGXTabWndMgr* pMgr = GetTabManager();
	ASSERT(pMgr != NULL);
	
	pMgr->DeleteWorkSheet(pMgr->GetCursel());
}

BOOL CGXFrameAdapter::CanInsertWorkSheetHandler()
{
	CGXTabWndMgr* pMgr = GetTabManager();
	ASSERT(pMgr != NULL);
	
	if(pMgr == NULL)
		return FALSE;
	else
		return pMgr->CanInsertWorkSheet();
}

BOOL CGXFrameAdapter::CanDeleteWorkSheetHandler()
{
	CGXTabWndMgr* pMgr = GetTabManager();
	ASSERT(pMgr != NULL);
	
	if(pMgr == NULL)
		return FALSE;
	else
		return pMgr->CanDeleteWorkSheet();
}


CGXMDIFrameAdapter::CGXMDIFrameAdapter()
{
	// No implementation
}

CGXMDIFrameAdapter::~CGXMDIFrameAdapter()
{
	// No Implementation
}

void CGXMDIFrameAdapter::HandleOnNewWindow()
{
	TRACE0("CGXMDIFrameAdapter::HandleOnNewWindow called\n");
	
	CMDIChildWnd* pActiveChild = dynamic_cast<CMDIChildWnd*>(this);//pMDIFrame->MDIGetActive();
	
	ASSERT(pActiveChild != NULL); // Error this can be be used only when you have a CMDIChildWnd derived class as the derived class

	if(pActiveChild == NULL)
		return;
	
	CDocument* pDocument;
	if (pActiveChild == NULL ||
	  (pDocument = pActiveChild->GetActiveDocument()) == NULL)
	{
		TRACE0("Warning: No active document for WindowNew command.\n");
		AfxMessageBox(AFX_IDP_COMMAND_FAILURE);
		return;     // command failed
	}

	// we have the active document...now get the primary document
	CGXDocument* pgxDoc = dynamic_cast<CGXDocument*>(pDocument);

	ASSERT(pgxDoc != NULL); // Error this has to be a CGXDocument derived class

	if(pgxDoc == NULL)
		return;

	pgxDoc = pgxDoc->GetPrimaryDocument();

	ASSERT(pgxDoc != NULL); // Error primary document cannot be null

	if(pgxDoc == NULL)
		return;

	// otherwise we have a new frame !
	CDocTemplate* pTemplate = pgxDoc->GetDocTemplate();
	ASSERT_VALID(pTemplate);
	
	CFrameWnd* pFrame = pTemplate->CreateNewFrame(pgxDoc, pActiveChild);
	if (pFrame == NULL)
	{
		TRACE0("Warning: failed to create new frame.\n");
		return;     // command failed
	}

	CGXWChildFrame* pgxFrame = dynamic_cast<CGXWChildFrame*>(this);

	ASSERT(pgxFrame != NULL); // Error this has to be a CGXWChildFrame derived class

	if(pgxFrame == NULL)
		return;

	CGXTabWndMgr* pTabWndMgr = pgxFrame->GetTabManager();	

	ASSERT(pTabWndMgr != NULL);

	if(pTabWndMgr == NULL)
	{
		if(pFrame)
			delete pFrame;
		return;
	}

	pFrame->SendMessage(WM_GX_INITNEW, (WPARAM) pTabWndMgr->GetTabCreateInfoArray());

	pTemplate->InitialUpdateFrame(pFrame, pDocument);
}

void CGXMDIFrameAdapter::HandleDestroy()
{
	CGXTabWndMgr* pMgr = GetTabManager();
	ASSERT(pMgr != NULL);

	CMDIChildWnd* pWnd = dynamic_cast<CMDIChildWnd*>(this);
	
	ASSERT(pWnd != NULL); // Error this can be be used only when you have a CMDIChildWnd derived class as the derived class

	if(pWnd == NULL)
		return;
	
	pMgr->RemoveSupTab(pWnd);
}
