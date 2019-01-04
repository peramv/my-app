///////////////////////////////////////////////////////////////////////////////
// gxtbmgr.cpp : Function implementations for the tab window manager class and helpers
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

#include "AFXPRIV.H"

#include "grid\gxtmpl.h"

#include "grid\gxtbmgr.h"

#include "grid\gxtbadpt.h"

#include "grid\gxtbgadp.h"

#include "grid\gxpriv.h"

#include "grid\gxmsg.h"

#include "grid\gxapatr.h"

#include "grid\gxproc.h"

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXTABSER")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_SERIAL(CGXTabCreateInfo, CObject, 0)
IMPLEMENT_SERIAL(CGXTabWndMgr, CObject, 0);


// this will be passed in to create the actual views as tab children
CGXTabCreateInfo::CGXTabCreateInfo()
{
	m_pViewRuntimeClass = NULL; 
	m_pContext = NULL;
	m_bUseContextIntact = FALSE;
	m_pDocTemplate = NULL;
	m_pDocument = NULL;
	
	m_gxCGgen = gxGenFromDefault;

	m_bIsInit = FALSE;

	m_pContext = NULL;

	SetIndex(GX_INVALID_CREATEINFOINDEX);
}
	
CGXTabCreateInfo::CGXTabCreateInfo(CCreateContext* pContext, gxContextGen gen,
		CDocTemplate* pDocTemplate /* = NULL*/, const TCHAR* pszLabel /* = NULL*/, BOOL bUseContextIntact /* = FALSE */)
{
	SetCreateContext(pContext);
	
	m_bUseContextIntact = bUseContextIntact;
	m_strLabel = pszLabel;

	if(pDocTemplate != NULL)
		m_pDocTemplate = pDocTemplate;
	
	m_gxCGgen = gen;

	m_bIsInit = TRUE;
	
	m_pContext = NULL;

	SetIndex(GX_INVALID_CREATEINFOINDEX);
}
	
CGXTabCreateInfo::CGXTabCreateInfo(CGXTabCreateInfo& info)
{
	m_pContext = NULL;

	*this = info;
}
	
void CGXTabCreateInfo::operator=(CGXTabCreateInfo& info)
{
	if(m_pContext != NULL)
		delete m_pContext;

	m_pViewRuntimeClass = info.m_pViewRuntimeClass; 
	m_bUseContextIntact = info.m_bUseContextIntact;
	
	if(!info.m_strLabel.IsEmpty())
		m_strLabel = info.m_strLabel;
	
	m_pDocTemplate = info.m_pDocTemplate;
	m_pDocument = info.m_pDocument;
	m_gxCGgen = info.m_gxCGgen;

	m_bIsInit = TRUE;
	
	m_nIndex = info.m_nIndex;
	
	m_pContext = NULL;
}

	
void CGXTabCreateInfo::Initialize(CCreateContext* pContext, gxContextGen gen /* = gxGenFromDefault*/,
		CDocTemplate* pDocTemplate /* = NULL*/, const TCHAR* pszLabel /* = NULL*/, BOOL bUseContextIntact /* = FALSE */)
{
	SetCreateContext(pContext);

	m_bUseContextIntact = bUseContextIntact;
	
	m_strLabel = pszLabel;
	
	if(pDocTemplate != NULL)
		m_pDocTemplate = pDocTemplate;

	m_bIsInit = TRUE;

	SetIndex(GX_INVALID_CREATEINFOINDEX);
	
	m_pContext = NULL;
	
	m_gxCGgen = gen;
}
	
BOOL CGXTabCreateInfo::IsInit()
{
	return m_bIsInit;
}

void CGXTabCreateInfo::SetInit(BOOL b)
{
	m_bIsInit = b;
}

CGXTabCreateInfo::~CGXTabCreateInfo()
{
	//TRACE0("OG Info: CGXTabCreateInfo destroyed");
	
	if(m_pContext != NULL)
		delete m_pContext;
}

void CGXTabCreateInfo::Serialize(CArchive& ar)
{
	if(ar.IsLoading())
	{
		// get back the runtime class information
		m_pViewRuntimeClass = CGXRuntimeClassOp::Load(ar);
		m_pDocRuntimeClass = CGXRuntimeClassOp::Load(ar);
			
		// reset the context
		m_pContext = NULL;

		ar >> m_bUseContextIntact;
		
		WORD w(0);

		ar >> w;
		
		m_gxCGgen = (gxContextGen)w;
	
		m_bIsInit = TRUE;
	}
	else
	{
		//serialize the runtime class information
		CGXRuntimeClassOp::Store(m_pViewRuntimeClass, ar);
		CGXRuntimeClassOp::Store(m_pDocument->GetRuntimeClass(), ar);

		ar << m_bUseContextIntact;
		
		ar << (WORD) m_gxCGgen;
	}
}

CRuntimeClass* CGXTabCreateInfo::GetViewRuntimeClass() const
{	
	return m_pViewRuntimeClass;
}

void CGXTabCreateInfo::SetViewRuntimeClass(CRuntimeClass* pRuntimeClass)
{
	ASSERT( pRuntimeClass->IsDerivedFrom(RUNTIME_CLASS(CView) ) ); // Error the view clas has to be derived from CView. Other models are
	// not supported -->END
	
	m_pViewRuntimeClass = pRuntimeClass;
}

CRuntimeClass* CGXTabCreateInfo::GetDocRuntimeClass() const
{	
	return m_pDocRuntimeClass;
}

void CGXTabCreateInfo::SetDocRuntimeClass(CRuntimeClass* pRuntimeClass)
{
	ASSERT( pRuntimeClass->IsDerivedFrom(RUNTIME_CLASS(CGXDocument) ) ); // Error the document clas has to be derived from CGXDocument. Other models are
	// not supported -->END
	
	m_pDocRuntimeClass = pRuntimeClass;
}


CCreateContext* CGXTabCreateInfo::GetCreateContext() 
{
	if(m_pContext == NULL)
		m_pContext = new CCreateContext;

	m_pContext->m_pNewViewClass = GetViewRuntimeClass(); // runtime class of view to create or NULL
	m_pContext->m_pCurrentDoc = GetDocument();

	// for creating MDI children (CMDIChildWnd::LoadFrame)
	m_pContext->m_pNewDocTemplate = GetDocTemplate();

	
	return m_pContext;
}
void CGXTabCreateInfo::SetCreateContext(const CCreateContext* pContext)
{
	// Warning
	ASSERT(IsInit() == FALSE); // If the create context has already been initialized..important data could be 
	// overwritten. Please recheck if this is correct for your case...
	
	SetViewRuntimeClass(pContext->m_pNewViewClass); // runtime class of view to create or NULL

#ifdef _DEBUG
	if(pContext->m_pCurrentDoc)
		ASSERT_KINDOF(CGXDocument, pContext->m_pCurrentDoc);
#endif

	SetDocument( (CGXDocument*)pContext->m_pCurrentDoc);

	// for creating MDI children (CMDIChildWnd::LoadFrame)
	SetDocTemplate(pContext->m_pNewDocTemplate);
}

BOOL CGXTabCreateInfo::GetUseContextIntact() const
{
	return m_bUseContextIntact;	
}
void CGXTabCreateInfo::SetUseContextIntact(BOOL bContext)
{
	m_bUseContextIntact = bContext;
}

CString CGXTabCreateInfo::GetLabel() const
{
	return m_strLabel;
}
void CGXTabCreateInfo::SetLabel(CString strLabel)
{
	m_strLabel = strLabel;
}

CDocTemplate* CGXTabCreateInfo::GetDocTemplate() const
{
	// This can return NULL
	return m_pDocTemplate;
}

void CGXTabCreateInfo::SetDocTemplate(CDocTemplate* pDocTemplate)
{
	// This can be NULL
	m_pDocTemplate = pDocTemplate;
}

CGXDocument* CGXTabCreateInfo::GetDocument() const
{
	// This member can be null
	return m_pDocument;
}

void CGXTabCreateInfo::SetDocument(CGXDocument* pDocument)
{
	m_pDocument = pDocument;
	
	if(m_pDocument != NULL)
	{
		m_pDocRuntimeClass = m_pDocument->GetRuntimeClass();
		ASSERT_KINDOF(CGXDocument, pDocument); // The document has to be derived from CGXDocument. Other document types are unsupported.
	}
		
}

gxContextGen CGXTabCreateInfo::GetContextGenMode() const
{
	return m_gxCGgen;
}
	
void CGXTabCreateInfo::SetContextGenMode(gxContextGen gen)
{
	m_gxCGgen = gen;
}

int CGXTabCreateInfo::GetIndex()
{
	return m_nIndex;
}
	
void CGXTabCreateInfo::SetIndex(int index)
{
	m_nIndex = index;
}
	


// Diagnostic Support
#ifdef _DEBUG
void CGXTabCreateInfo::AssertValid() const
{
	CObject::AssertValid();
}

	
void CGXTabCreateInfo::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);

	// the view runtime class
	dc << "CGXTabCreateInfo\n";
	dc << "m_pViewRuntimeClass:" << m_pViewRuntimeClass; 
	
	// the document runtime class
	dc << "m_pDocRuntimeClass:" << m_pDocRuntimeClass; 
	
	// the current creation context
	dc << "m_pContext: " << m_pContext;
	
	// Whether the create context should be used intact.
	// a new document will not be created in this case.
	dc << "m_bUseContextIntact:" << m_bUseContextIntact;
	
	// the label for the tab. Only minimum information for the tab appearance is
	// persisted in this variant
	dc << "m_strLabel:" << m_strLabel;
	
	// the doc template to be used for document creation
	dc << "m_pDocTemplate:" << m_pDocTemplate;

	// pointer to the document used (set or created)
	dc << "m_pDocument:" << m_pDocument;

	// CCreateContext generation mode
	dc << "m_gxCGgen:" << m_gxCGgen;

	// Init 
	dc << "m_bIsInit:" << m_bIsInit;
	
	dc << "m_nIndex:" << m_nIndex;
}
#endif

//////////////////////////////////////////////////////////////////////////////////////////////
// Begin CGXTabWndMgr implementation
//////////////////////////////////////////////////////////////////////////////////////////////

CGXTabWndMgr::CGXTabWndMgr()
{
	// no tab window created
	m_pTabWndAdapter = NULL;	
	
#if _MSC_VER >= 1700
	m_ArrTabCreateInfo = new CGXTabCreateArray;
#endif
	
	m_bOwn = FALSE;	

	// default tab count
	m_nTabCount = 0;

	m_bDeleteTabInfo = FALSE;

	SetPrimaryIndex(0);
	
	m_pSupTabHolder = 0;
}
	
CGXTabWndMgr::CGXTabWndMgr(CWnd* pTabParent)
{
	// parent window
	if(GetTabWndAdapter() != NULL)
		GetTabWndAdapter()->SetParentWnd(pTabParent);

#if _MSC_VER >= 1700
	m_ArrTabCreateInfo = new CGXTabCreateArray;
#endif

	// externally supplied tab window
	m_bOwn = FALSE;
	m_nTabCount = 0;
}

// will be called after creation
void CGXTabWndMgr::OnInitialize()
{
	if(GetTabWndAdapter() == NULL)
	{
		m_pTabWndAdapter = new CGXGridTabWndAdapter();
		m_bOwn = TRUE;	
	}
}
	
void CGXTabWndMgr::SetTabWndAdapter(CGXTabWndAdapter* pAdapter, BOOL bOwn /* = FALSE */)
{
	TRACE0("OG Info: Replacing tab window adapter\n");
	ASSERT(pAdapter != NULL); // Invalid tab window adapter--->END
	
	if (GetTabWndAdapter() != NULL && m_bOwn)
		GetTabWndAdapter()->Destroy();
	
	m_pTabWndAdapter = pAdapter;
	m_bOwn = bOwn;
}

CGXTabWndAdapter* CGXTabWndMgr::GetTabWndAdapter() const
{
	return m_pTabWndAdapter;
}

CGXTabWndMgr::~CGXTabWndMgr()
{
	// clean up internal state
	Cleanup();
}

void CGXTabWndMgr::Cleanup()
{
#if _MSC_VER >= 1700   
	if(m_ArrTabCreateInfo != NULL)
	{
	for (int i = 0; i < m_ArrTabCreateInfo->GetSize() ; i++)
#else
	for (int i = 0; i < m_ArrTabCreateInfo.GetSize() ; i++)
#endif // _MSC_VER >= 1700
	{
#if _MSC_VER >= 1700 // VC 11  
		if(m_ArrTabCreateInfo->GetAt(i) != NULL)
#else
		if(m_ArrTabCreateInfo[i] != NULL)
#endif // _MSC_VER >= 1700
		{
#if _MSC_VER >= 1700  
			delete m_ArrTabCreateInfo->GetAt(i);
#else
			delete m_ArrTabCreateInfo[i];
#endif // _MSC_VER >= 1700
		}

#if _MSC_VER >= 1700
		m_ArrTabCreateInfo->GetAt(i) = NULL;
	}
#else
		m_ArrTabCreateInfo[i] = NULL;
#endif // _MSC_VER >= 1700
		
	}

	if(m_pTabWndAdapter != NULL && m_bOwn)
		m_pTabWndAdapter->Destroy();

	m_pTabWndAdapter = NULL;
	m_bOwn = FALSE;
	m_nTabCount = 0;

	if(m_bDeleteTabInfo && m_pPrimaryTabCreateInfo)
		delete m_pPrimaryTabCreateInfo;

	m_pPrimaryTabCreateInfo = NULL;

	m_bDeleteTabInfo = FALSE;

#if _MSC_VER >= 1700  
if(m_ArrTabCreateInfo != NULL)
{
	delete m_ArrTabCreateInfo;
	m_ArrTabCreateInfo = NULL;
}
#endif

	if(m_pSupTabHolder != NULL)
	{
		delete m_pSupTabHolder;
		m_pSupTabHolder = NULL;
	}

}

CGXTabCreateInfo* CGXTabWndMgr::GetPrimaryTabCreateInfo()
{
	TRACE1("Tab manager::GetPrimaryTabCreateInfo accessed: %x\n", this);
	TRACE1("Tab manager::GetPrimaryTabCreateInfo accessed m_pPrimaryTabCreateInfo: %x\n", m_pPrimaryTabCreateInfo);
	return m_pPrimaryTabCreateInfo;
}

void CGXTabWndMgr::SetPrimaryTabCreateInfo(CGXTabCreateInfo* pTabCreateInfo, BOOL bDeleteTabInfo /* = FALSE */)
{
	ASSERT(pTabCreateInfo != NULL);
		
	
	if(m_bDeleteTabInfo && m_pPrimaryTabCreateInfo)
	{
		delete m_pPrimaryTabCreateInfo;
		m_pPrimaryTabCreateInfo = NULL;
		m_bDeleteTabInfo = FALSE;
	}

	m_bDeleteTabInfo = bDeleteTabInfo;

	m_pPrimaryTabCreateInfo = pTabCreateInfo;
}


BOOL CGXTabWndMgr::GenerateCreateContext(CGXTabCreateInfo* pTabCreateInfo)
{
	ASSERT(pTabCreateInfo != NULL);

	switch (pTabCreateInfo->GetContextGenMode())
	{
		case gxGenFromDefault:
			{
				ASSERT(GetPrimaryTabCreateInfo());
				const CCreateContext* pC = GetPrimaryTabCreateInfo()->GetCreateContext();
				pTabCreateInfo->SetCreateContext(pC);		
				break;
			}
		case gxGenFromIndex:
			{
				ASSERT(pTabCreateInfo->GetIndex() != GX_INVALID_CREATEINFOINDEX);
#if _MSC_VER >= 1700
				CGXTabCreateInfo* pInfo = m_ArrTabCreateInfo->GetAt(pTabCreateInfo->GetIndex());
#else
				CGXTabCreateInfo* pInfo = m_ArrTabCreateInfo[pTabCreateInfo->GetIndex()];
#endif // _MSC_VER >= 1700
				
				ASSERT(pInfo != NULL); // Invalid index to use specified
				const CCreateContext* pC = pInfo->GetCreateContext();
				pTabCreateInfo->SetCreateContext(pC);		
				break;
			}
		default:
			ASSERT(0);
	};
	
	return TRUE;
}

BOOL CGXTabWndMgr::CreateSupTabs(CGXTabCreateInfo* pTabCreateInfo, CMDIChildWnd* pChildWnd, int nTabs /* = 0 */, TCHAR* pszFileName /* = NULL */)
{
	ASSERT(pChildWnd != NULL); // Error, suplementary tabs can only be created in the context of a MDI Child
	if(pChildWnd == NULL)
		return FALSE;

	CGXTabWndAdapter* pTabWnd = GetSupTabWndHolder().CreateObject((SEC_DWORD) pChildWnd);

	ASSERT(pTabWnd != NULL);

	if(pTabWnd == NULL)
		return FALSE;

	pTabWnd->SetParentWnd(pChildWnd);

	return CreateTabs(NULL, 0, NULL, pTabWnd);

	GX_UNUSED_ALWAYS(pszFileName);
	GX_UNUSED_ALWAYS(nTabs);
	GX_UNUSED_ALWAYS(pTabCreateInfo);
}

// called to remove an additional tab object 
void CGXTabWndMgr::RemoveSupTab(CMDIChildWnd* pChildWnd)
{
	ASSERT(pChildWnd != NULL); // Error, suplementary tabs can only be removed in the context of a MDI Child
	if(pChildWnd == NULL || GetSupTabWndHolder().GetObject( (SEC_DWORD)pChildWnd) == NULL)
		return;
	
	GetSupTabWndHolder().RemoveObject( (SEC_DWORD) pChildWnd);
}

BOOL CGXTabWndMgr::CreateTabs(CGXTabCreateInfo* pTabCreateInfo, int nTabs, TCHAR* pszFileName /* = NULL */, CGXTabWndAdapter* p /*= NULL*/)
{
	CGXTabWndAdapter* pTabAdapter = NULL;

	if(p != NULL)
		pTabAdapter = p;
	else
		pTabAdapter = GetTabWndAdapter(); 

	// set the correct tab count
	if(nTabs == 0)
		nTabs = m_nTabCount;
	else
		m_nTabCount = nTabs;

	// get the current document
	BOOL bLoaded(FALSE);

	// check if the array was loaded prior to this call
	if(pTabCreateInfo == NULL)
	{
#if _MSC_VER >= 1700
		pTabCreateInfo = m_ArrTabCreateInfo->GetAt(0);
#else
		pTabCreateInfo = m_ArrTabCreateInfo.GetAt(0);
#endif // _MSC_VER >= 1700
		
		
		// set the primary tab create info
#if _MSC_VER >= 1700
		SetPrimaryTabCreateInfo( m_ArrTabCreateInfo->GetAt( GetPrimaryIndex() ) );
#else
		SetPrimaryTabCreateInfo( m_ArrTabCreateInfo.GetAt( GetPrimaryIndex() ) );
#endif // _MSC_VER >= 1700
		
		bLoaded = TRUE;	
	}
	else
		// this is temp memory. Make a copy
		SetPrimaryTabCreateInfo(new CGXTabCreateInfo(* (pTabCreateInfo+GetPrimaryIndex()) ), TRUE);
	
	CGXDocument* pPrimaryDoc = GetPrimaryTabCreateInfo()->GetDocument();
		
	ASSERT_VALID(pPrimaryDoc);
	ASSERT_KINDOF(CGXDocument, pPrimaryDoc);

	pPrimaryDoc->SetPrimaryDocument(pPrimaryDoc);
	
	CGXDocument* pDoc = NULL;
		
	ASSERT(pTabAdapter != NULL); //instantiated without a valid tab window adapter. Check OnInitialize...
	
	CGXTabCreateInfo* pTempTabInfo = NULL;
	
	if(bLoaded == FALSE)
		pTempTabInfo = pTabCreateInfo;
	else
	{
#if _MSC_VER >= 1700   
		pTempTabInfo = m_ArrTabCreateInfo->GetAt(0);
#else
		pTempTabInfo = m_ArrTabCreateInfo[0];
#endif // _MSC_VER >= 1700
		
	}
	

	// iterate through and create the tabs
	for (int i = 0; i < nTabs; i++)
	{
			// check if the create context is to be used as is
			if(!pTempTabInfo->GetUseContextIntact())
			{
				// check if tab info is initialized
				if(pTempTabInfo->IsInit() == FALSE && i != GetPrimaryIndex())
					GenerateCreateContext(pTempTabInfo);
				
				if(bLoaded == FALSE && i != GetPrimaryIndex())
				{
					pDoc = (CGXDocument*) CGXDocTemplateOp::CreateDocumentFile(pTabCreateInfo->GetDocTemplate());
					ASSERT_KINDOF(CGXDocument, pDoc);
					
					// set the primary controlling document
					pDoc->SetPrimaryDocument(pPrimaryDoc);
					pTempTabInfo->SetDocument(pDoc);
				}
			}
			
			if(bLoaded == FALSE)
			{
#if _MSC_VER >= 1700  
				m_ArrTabCreateInfo->SetAtGrow(i, new CGXTabCreateInfo(*pTempTabInfo) );
#else
				m_ArrTabCreateInfo.SetAtGrow(i, new CGXTabCreateInfo(*pTempTabInfo) );
#endif // _MSC_VER >= 1700
				
			}

			// create the tab window view
			if(i)
			{
				CWnd* pCreateWnd = pTabAdapter->CreateView( pTempTabInfo->GetViewRuntimeClass(), pTempTabInfo->GetLabel(), pTempTabInfo->GetCreateContext() );
			
				pCreateWnd->SendMessage(WM_INITIALUPDATE);
			}
			else
			{
				pTabAdapter->Create(pTempTabInfo->GetLabel(), pTempTabInfo->GetCreateContext());
			}

			if(i < m_nTabCount - 1)
			{
				if(bLoaded == FALSE)
				{
					pTempTabInfo = ++pTabCreateInfo;
				}else
				{
#if _MSC_VER >= 1700
					pTempTabInfo = m_ArrTabCreateInfo->GetAt(i+1);
#else
					pTempTabInfo = m_ArrTabCreateInfo[i+1];
#endif // _MSC_VER >= 1700
				}
			}
	}	
	
	return TRUE;

	GX_UNUSED_ALWAYS(pszFileName);
}

BOOL CGXTabWndMgr::IterateAndSaveDocuments(CArchive& ar) const
{
		int i;
#if _MSC_VER >= 1700
		for(i = 0; i < m_nTabCount; i++)
		{
			ASSERT(m_ArrTabCreateInfo->GetAt(i) != NULL);
			if (m_ArrTabCreateInfo->GetAt(i) != NULL )
				ar << m_ArrTabCreateInfo->GetAt(i);
		}


		for(i = 0; i < m_nTabCount; i++)
		{
			ASSERT(m_ArrTabCreateInfo->GetAt(i) != NULL);
			ASSERT(m_ArrTabCreateInfo->GetAt(i)->GetDocument() !=NULL);
			if (m_ArrTabCreateInfo->GetAt(i) != NULL && m_ArrTabCreateInfo->GetAt(i)->GetDocument() !=NULL)
			{
				m_ArrTabCreateInfo->GetAt(i)->GetDocument()->WorkBookSerialize(ar);
				m_ArrTabCreateInfo->GetAt(i)->GetDocument()->SetModifiedFlag(FALSE);
			}
		}
#else
		for(i = 0; i < m_nTabCount; i++)
		{
			ASSERT(m_ArrTabCreateInfo[i] != NULL);
			if (m_ArrTabCreateInfo[i] != NULL )
				ar << m_ArrTabCreateInfo[i];
		}


		for(i = 0; i < m_nTabCount; i++)
		{
			ASSERT(m_ArrTabCreateInfo[i] != NULL);
			ASSERT(m_ArrTabCreateInfo[i]->GetDocument() !=NULL);
			if (m_ArrTabCreateInfo[i] != NULL && m_ArrTabCreateInfo[i]->GetDocument() !=NULL)
			{
				m_ArrTabCreateInfo[i]->GetDocument()->WorkBookSerialize(ar);
				m_ArrTabCreateInfo[i]->GetDocument()->SetModifiedFlag(FALSE);
			}
		}
#endif // _MSC_VER >= 1700
		return TRUE;
}

BOOL CGXTabWndMgr::IterateAndLoadDocuments(CArchive& ar, CGXDocument* pDocThis, int nIndex)
{
#if _MSC_VER >= 1700 // VC 11
		m_ArrTabCreateInfo->SetSize(m_nTabCount);
	int i;
	for(i = 0; i < m_nTabCount; i++)
	{
		ar >> m_ArrTabCreateInfo->GetAt(i);
	}

	//load the correct CDocTemplate runtime classes
	for(i = 0; i < m_nTabCount; i++)
	{
		ASSERT(m_ArrTabCreateInfo->GetAt(i) != NULL);
		CGXAppAdapter* pAppAdapt = dynamic_cast<CGXAppAdapter*>(AfxGetApp());
		ASSERT(pAppAdapt != NULL);
		
		if(pAppAdapt == NULL)
			return FALSE;

		m_ArrTabCreateInfo->GetAt(i)->SetDocTemplate(pAppAdapt->GetDocTemplate(m_ArrTabCreateInfo->GetAt(i)->GetViewRuntimeClass(), m_ArrTabCreateInfo->GetAt(i)->GetDocRuntimeClass()) );			
	}
		
	for(i = 0; i < m_nTabCount; i++)
	{
		ASSERT(m_ArrTabCreateInfo->GetAt(i) != NULL);
		ASSERT(m_ArrTabCreateInfo->GetAt(i)->GetDocument() == NULL);
			
		if(i == nIndex)
			m_ArrTabCreateInfo->GetAt(i)->SetDocument(pDocThis);
		else
			m_ArrTabCreateInfo->GetAt(i)->SetDocument( (CGXDocument*)CGXDocTemplateOp::CreateDocumentFile(m_ArrTabCreateInfo->GetAt(i)->GetDocTemplate() ) );

		if (m_ArrTabCreateInfo->GetAt(i) != NULL && m_ArrTabCreateInfo->GetAt(i)->GetDocument() !=NULL)
		{
			m_ArrTabCreateInfo->GetAt(i)->GetDocument()->WorkBookSerialize(ar);
		}

		m_ArrTabCreateInfo->GetAt(i)->GetDocument()->SetPrimaryDocument(pDocThis);
	}
	
	SetPrimaryTabCreateInfo(m_ArrTabCreateInfo->GetAt(GetPrimaryIndex()) );
#else
	m_ArrTabCreateInfo.SetSize(m_nTabCount);
	int i;
	for(i = 0; i < m_nTabCount; i++)
	{
		ar >> m_ArrTabCreateInfo[i];
	}


	//load the correct CDocTemplate runtime classes
	for(i = 0; i < m_nTabCount; i++)
	{
		ASSERT(m_ArrTabCreateInfo[i] != NULL);
		CGXAppAdapter* pAppAdapt = dynamic_cast<CGXAppAdapter*>(AfxGetApp());
		ASSERT(pAppAdapt != NULL);
		
		if(pAppAdapt == NULL)
			return FALSE;

		m_ArrTabCreateInfo[i]->SetDocTemplate(pAppAdapt->GetDocTemplate(m_ArrTabCreateInfo[i]->GetViewRuntimeClass(), m_ArrTabCreateInfo[i]->GetDocRuntimeClass()) );			
	}
		
	for(i = 0; i < m_nTabCount; i++)
	{
		ASSERT(m_ArrTabCreateInfo[i] != NULL);
		ASSERT(m_ArrTabCreateInfo[i]->GetDocument() == NULL);
			
		if(i == nIndex)
			m_ArrTabCreateInfo[i]->SetDocument(pDocThis);
		else
			m_ArrTabCreateInfo[i]->SetDocument( (CGXDocument*)CGXDocTemplateOp::CreateDocumentFile(m_ArrTabCreateInfo[i]->GetDocTemplate() ) );

		if (m_ArrTabCreateInfo[i] != NULL && m_ArrTabCreateInfo[i]->GetDocument() !=NULL)
		{
			m_ArrTabCreateInfo[i]->GetDocument()->WorkBookSerialize(ar);
		}

		m_ArrTabCreateInfo[i]->GetDocument()->SetPrimaryDocument(pDocThis);
	}
	
	SetPrimaryTabCreateInfo(m_ArrTabCreateInfo[GetPrimaryIndex()]);
#endif // _MSC_VER >= 1700
	return TRUE;
}

void CGXTabWndMgr::Serialize(CArchive& ar)
{
	if(ar.IsLoading())
	{
		ar >> m_nPrimaryIndex;
		ar >> m_nTabCount;
			
		ASSERT(m_nTabCount != 0);
	}
	else
	{
		ar << m_nPrimaryIndex;
		ar << m_nTabCount;
	}
}

// implementation
BOOL CGXTabWndMgr::ReadDocumentsFromArchive(CArchive& ar, CGXDocument* pDocThis, int nIndex /* = 0 */)
{
	Serialize(ar);     // save me first
	return IterateAndLoadDocuments(ar, pDocThis, nIndex);		
}
	
BOOL CGXTabWndMgr::StoreDocumentsInArchive(CArchive& ar)
{
	Serialize(ar);     // save me first
	return IterateAndSaveDocuments(ar);
}
	
int CGXTabWndMgr::GetPrimaryIndex()
{	
	return m_nPrimaryIndex;
}

void CGXTabWndMgr::SetPrimaryIndex(int nIndex)
{	
	m_nPrimaryIndex = nIndex;
}

void CGXTabWndMgr::SetPrimaryContext(CCreateContext* pContext)
{
	// make a copy
#if _MSC_VER >= 1700 
	m_ArrTabCreateInfo->GetAt(GetPrimaryIndex())->SetCreateContext(pContext);
#else
	m_ArrTabCreateInfo[GetPrimaryIndex()]->SetCreateContext(pContext) ;
#endif // _MSC_VER >= 1700 
}

void CGXTabWndMgr::SetParent(CWnd* pParentWnd)
{
	ASSERT_VALID(pParentWnd); // Parent window supplied has to be valid --> END

	GetTabWndAdapter()->SetParentWnd(pParentWnd);
}

BOOL CGXTabWndMgr::CanInsertWorkSheet() const
{
	return GetTabWndAdapter()->CanInsertWorkSheet();
}

BOOL CGXTabWndMgr::CanDeleteWorkSheet() const
{
	return GetTabWndAdapter()->CanDeleteWorkSheet();
}


struct _insertIter:public CGXNodeManagerNor<CGXTabWndAdapter>::nodeIter
{
public:
	_insertIter(int nInsert, BOOL bBefore, CRuntimeClass* pViewRuntimeClass, CCreateContext* pContext, const TCHAR* pszLabel = 0, UINT nID = 0);
	~_insertIter();
	virtual void Execute(CGXTabWndAdapter* pObject) const;
protected:
   BOOL m_bBefore ;
	int m_nInsert;
	CRuntimeClass* m_pViewRuntimeClass;
	CCreateContext* m_pContext;
	const TCHAR* m_pszLabel; 
	UINT m_nID;
};

_insertIter::_insertIter(int nInsert, BOOL bBefore, CRuntimeClass* pViewRuntimeClass, CCreateContext* pContext, const TCHAR* pszLabel, UINT nID)
{
   m_bBefore = bBefore ;
	m_nInsert = nInsert;
	m_pViewRuntimeClass = pViewRuntimeClass;
	m_pContext = pContext;
	m_pszLabel = pszLabel; 
	m_nID = nID;
}

_insertIter::~_insertIter()
{
}

void _insertIter::Execute(CGXTabWndAdapter* pObject) const
{
	TRACE0("_insertIter::Execute(CGXTabWndAdapter* pObject) called\n");
	pObject->InsertWorkSheet(m_nInsert, m_bBefore, m_pViewRuntimeClass, m_pContext, m_pszLabel, m_nID);
}

BOOL CGXTabWndMgr::InsertWorkSheet(int nInsert, BOOL bBefore, CGXTabCreateInfo* pTabCreateInfo, UINT nID)
{
	ASSERT(GetTabWndAdapter() != NULL); // Error Tab window adpater class has to be valid
	ASSERT(pTabCreateInfo != NULL); // Invalid context data 

	// create a new document if required
	if(!pTabCreateInfo->GetUseContextIntact())
	{
		CGXDocument* pDoc = (CGXDocument*) CGXDocTemplateOp::CreateDocumentFile(pTabCreateInfo->GetDocTemplate());
		ASSERT_KINDOF(CGXDocument, pDoc);
		
		pDoc->SetPrimaryDocument(GetPrimaryTabCreateInfo()->GetDocument());
		
		pTabCreateInfo->SetDocument(pDoc);
	}

	BOOL b = GetTabWndAdapter()->InsertWorkSheet(nInsert, bBefore, pTabCreateInfo->GetViewRuntimeClass(), pTabCreateInfo->GetCreateContext(), pTabCreateInfo->GetLabel(), nID);

	// handle the supplementary tabs
	_insertIter iter(nInsert, bBefore, pTabCreateInfo->GetViewRuntimeClass(), pTabCreateInfo->GetCreateContext(), pTabCreateInfo->GetLabel(), nID);
	
	GetSupTabWndHolder().IterateObjects(&iter);

	if(b)
	{
#if _MSC_VER >= 1700 
        if ( bBefore)
        {
		    m_ArrTabCreateInfo->InsertAt(nInsert, new CGXTabCreateInfo(*pTabCreateInfo));
        }
        else
        {
  		    m_ArrTabCreateInfo->InsertAt(nInsert + 1, new CGXTabCreateInfo(*pTabCreateInfo));
        }
#else
        if ( bBefore)
        {
		    m_ArrTabCreateInfo.InsertAt(nInsert, new CGXTabCreateInfo(*pTabCreateInfo));
        }
        else
        {
		   m_ArrTabCreateInfo.InsertAt(nInsert + 1, new CGXTabCreateInfo(*pTabCreateInfo));
        }
#endif // _MSC_VER >= 1700 

		// adjust the primary index
		if ( ( bBefore && nInsert <= GetPrimaryIndex() ) ||
             (!bBefore && nInsert + 1 <= GetPrimaryIndex() ) )
			SetPrimaryIndex(GetPrimaryIndex() + 1);
	
		UpdateTabCount();

		SetPrimaryModified(TRUE);
	}
	
	return b;
}

void CGXTabWndMgr::UpdateTabCount()
{
	ASSERT(GetTabWndAdapter() != NULL); // Error Tab window adpater class has to be valid

	if(GetTabWndAdapter() != NULL)
		m_nTabCount = GetTabWndAdapter()->GetTabCount();
}

void CGXTabWndMgr::SetPrimaryModified(BOOL b)
{
	ASSERT(GetPrimaryTabCreateInfo());
	ASSERT(GetPrimaryTabCreateInfo()->GetDocument());

	if(GetPrimaryTabCreateInfo() && GetPrimaryTabCreateInfo()->GetDocument())
		GetPrimaryTabCreateInfo()->GetDocument()->SetModifiedFlag(b);
}


struct _deleteIter:public CGXNodeManagerNor<CGXTabWndAdapter>::nodeIter
{
public:
	_deleteIter(int nDeleteIndex);
	~_deleteIter();
	virtual void Execute(CGXTabWndAdapter* pObject) const;
protected:
	int m_nDeleteIndex;
};

_deleteIter::_deleteIter(int nDeleteIndex)
{
	m_nDeleteIndex = nDeleteIndex;
}

_deleteIter::~_deleteIter()
{
}

void _deleteIter::Execute(CGXTabWndAdapter* pObject) const
{
	TRACE0("_deleteIter::Execute(CGXTabWndAdapter* pObject) called\n");
	pObject->DeleteWorksheet(m_nDeleteIndex);
}

BOOL CGXTabWndMgr::DeleteWorkSheet(int nDeleteIndex)
{
	if(nDeleteIndex == GetPrimaryIndex())
	{
		TRACE0("Attempt to destroy primary document fails. You cannot destroy the primary document.\n");
		return FALSE;
	}

	ASSERT(GetTabWndAdapter() != NULL); // Error Tab window adpater class has to be valid
	
	BOOL b = GetTabWndAdapter()->DeleteWorksheet(nDeleteIndex);

	_deleteIter del(nDeleteIndex);
	GetSupTabWndHolder().IterateObjects(&del);

	if(b)
	{
#if _MSC_VER >= 1700 
		ASSERT(m_ArrTabCreateInfo->GetAt(nDeleteIndex) != NULL);
		
		if(m_ArrTabCreateInfo->GetAt(nDeleteIndex))
			delete m_ArrTabCreateInfo->GetAt(nDeleteIndex);

		m_ArrTabCreateInfo->RemoveAt(nDeleteIndex);
#else
		ASSERT(m_ArrTabCreateInfo[nDeleteIndex] != NULL);
		
		if(m_ArrTabCreateInfo[nDeleteIndex])
			delete m_ArrTabCreateInfo[nDeleteIndex];

		m_ArrTabCreateInfo.RemoveAt(nDeleteIndex);
#endif // _MSC_VER >= 1700 	
		// adjust the primary index
		if (nDeleteIndex < GetPrimaryIndex())
			SetPrimaryIndex(GetPrimaryIndex() - 1);

		UpdateTabCount();
		
		SetPrimaryModified(TRUE);
	}
	
	return b;
}

// for managing the document dirty state

// will return TRUE if atleast one document is modifies
BOOL CGXTabWndMgr::IsModified()
{
	BOOL b(FALSE);
	for(int i = 0; i < m_nTabCount; i++)
	{
#if _MSC_VER >= 1700 // VC 11
		b = (b || m_ArrTabCreateInfo->GetAt(i)->GetDocument()->IsModified());
#else
		b = (b || m_ArrTabCreateInfo[i]->GetDocument()->IsModified());
#endif // _MSC_VER >= 1700
		
		// If TRUE we might as well return
		if (b)
			return b;
	}
	
	return b;
}

void CGXTabWndMgr::SetModify(BOOL bModify)
{
	for(int i = 0; i < m_nTabCount; i++)
	{
#if _MSC_VER >= 1700
		m_ArrTabCreateInfo->GetAt(i)->GetDocument()->SetModifiedFlag(bModify);
#else
		m_ArrTabCreateInfo[i]->GetDocument()->SetModifiedFlag(bModify);
#endif // _MSC_VER >= 1700
	}
}

int CGXTabWndMgr::GetTabCount()
{
	return m_nTabCount;
}

int CGXTabWndMgr::GetCursel() const
{
	ASSERT(GetTabWndAdapter() != NULL); // Error Tab window adpater class has to be valid
	
	if(GetTabWndAdapter() == NULL)
		return GX_INVALID;
	else
		return GetTabWndAdapter()->GetCursel();
}

CGXTabCreateArray* CGXTabWndMgr::GetTabCreateInfoArray()
{
#if _MSC_VER >= 1700
	return m_ArrTabCreateInfo;
#else
	return &m_ArrTabCreateInfo;
#endif // _MSC_VER >= 1700
}

CGXNodeManagerNor<CGXTabWndAdapter>& CGXTabWndMgr::GetSupTabWndHolder()
{
	if(m_pSupTabHolder == NULL)
		m_pSupTabHolder = CreateSupTabHolder();

	ASSERT(m_pSupTabHolder != NULL);

	return *m_pSupTabHolder;
}

struct CGXTabGridCreator :public CGXCreator<CGXTabWndAdapter>
{
	virtual CGXTabWndAdapter* CreateObject();
};

CGXTabWndAdapter* CGXTabGridCreator::CreateObject()
{
	return new CGXGridTabWndAdapter;
}

// Override and return a different creator if required
CGXNodeManagerNor<CGXTabWndAdapter>* CGXTabWndMgr::CreateSupTabHolder()
{
	return new CGXNodeManagerNor<CGXTabWndAdapter>(new CGXTabGridCreator, &CGXTabWndAdapter::Destroy);
}

/////////////////////////////////////////////////////////////////////
// Runtime class serialization support code
CRuntimeClass* PASCAL CGXRuntimeClassOp::Load(CArchive& ar)
	// loads a runtime class description
{
	WORD nLen;
	char szClassName[64];
	CRuntimeClass* pClass;

	ar >> nLen;

	if (nLen >= _gxcountof(szClassName) ||
		ar.Read(szClassName, nLen*sizeof(char)) != nLen*sizeof(char))
	{
		return NULL;
	}
	szClassName[nLen] = '\0';

	// search app specific classes
	AFX_MODULE_STATE* pModuleState = AfxGetModuleState();
	AfxLockGlobals(GX_CRIT_RUNTIMECLASSLIST);
	for (pClass = pModuleState->m_classList; pClass != NULL;
		pClass = pClass->m_pNextClass)
	{
		if (lstrcmpA(szClassName, pClass->m_lpszClassName) == 0)
		{
			AfxUnlockGlobals(GX_CRIT_RUNTIMECLASSLIST);
			return pClass;
		}
	}
	AfxUnlockGlobals(GX_CRIT_RUNTIMECLASSLIST);
#ifdef _AFXDLL
	// search classes in shared DLLs
	AfxLockGlobals(GX_CRIT_DYNLINKLIST);
	for (CDynLinkLibrary* pDLL = pModuleState->m_libraryList; pDLL != NULL;
		pDLL = pDLL->m_pNextDLL)
	{
		for (pClass = pDLL->m_classList; pClass != NULL;
			pClass = pClass->m_pNextClass)
		{
			if (lstrcmpA(szClassName, pClass->m_lpszClassName) == 0)
			{
				AfxUnlockGlobals(GX_CRIT_DYNLINKLIST);
				return pClass;
			}
		}
	}
	AfxUnlockGlobals(GX_CRIT_DYNLINKLIST);
#endif

	TRACE1("Warning: Cannot load %hs from archive.  Class not defined.\n",
		szClassName);

	return NULL; // not found
}

void CGXRuntimeClassOp::Store(CRuntimeClass* pRClass, CArchive& ar)
	// stores a runtime class description
{
	ASSERT(pRClass != NULL);

	WORD nLen = (WORD)lstrlenA(pRClass->m_lpszClassName);
	ar << nLen;
	ar.Write(pRClass->m_lpszClassName, nLen*sizeof(char));
}











