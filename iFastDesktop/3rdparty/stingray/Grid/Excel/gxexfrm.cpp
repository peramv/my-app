///////////////////////////////////////////////////////////////////////////////
// gxexfrm.cpp : implementation of the CGXExcelChildFrame class
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

#include "grid\gxfradpt.h"

#include "grid\gxexfrm.h"

#include "grid\gxrddoc.h"

#include "grid\gxrdvw.h"

#include "grid\gxxrdrim.h"

#include "grid\gxexdef.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CGXExcelChildFrame

IMPLEMENT_DYNCREATE(CGXExcelChildFrame, CGXWChildFrame)

BEGIN_MESSAGE_MAP(CGXExcelChildFrame, CGXWChildFrame)
	//{{AFX_MSG_MAP(CGXExcelChildFrame)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGXExcelChildFrame construction/destruction

CGXExcelChildFrame::CGXExcelChildFrame()
{
	SetDocRuntimeClass(RUNTIME_CLASS(CGXExcelReadDoc));
	SetViewRuntimeClass(RUNTIME_CLASS(CGXExcelReadView));

	// keeps track of the primary index between inserts and deletes
	m_nPrimary = 0xFFFF;
}

CGXExcelChildFrame::~CGXExcelChildFrame()
{
}

BOOL CGXExcelChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	return CMDIChildWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CGXExcelChildFrame diagnostics

#ifdef _DEBUG
void CGXExcelChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CGXExcelChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGXExcelChildFrame message handlers

LRESULT CGXExcelChildFrame::InitFromFileHandler(WPARAM wParam, LPARAM lParam)
{
	CGXExcelDocAdapter* pDocAdapt = dynamic_cast<CGXExcelDocAdapter*> (m_pContext->m_pCurrentDoc);
	m_nSize = pDocAdapt->GetTabCount();
	
	BOOL bFail(FALSE);

	if(m_nSize == 0 || m_nSize == -1)
	{
		m_nSize = GX_EX_DEFNUMTABS; // The most likely reason is that read failed.
		bFail = TRUE;
	}

	LRESULT l = CGXWChildFrame::InitNewHandler(wParam, lParam);
	
	// iterate through the children and post an OnInitialUpdate (delayed)
	SendMessageToDescendants(WM_GXINITIALUPDATE, 0, 0, TRUE, TRUE);

	if(bFail)
	{
		AfxMessageBox(GX_IDS_EGXGENERICFAILURE);
		return l;
	}
	pDocAdapt->ReadExcelData();
	
	// iterate through the children and post an OnInitialUpdateDone message
	SendMessageToDescendants(WM_GXINITIALUPDATEDONE, 0, 0, TRUE, TRUE);

	return l;
}

LRESULT CGXExcelChildFrame::InitNewHandler(WPARAM ui, LPARAM l)
{
	LRESULT lRet = CGXWChildFrame::InitNewHandler(ui, l);
	
	CGXExcelDocAdapter* pDoc = dynamic_cast<CGXExcelDocAdapter*>(m_pContext->m_pCurrentDoc);
	ASSERT(pDoc != NULL); // Error---> This has to be derived from CGXExcelReadDoc
	
	for(int i(0); i < m_nSize; i++ )
		pDoc->InitializeParam(i, 0xFFFF);

	// iterate through the documents and post an OnInitialUpdate (delayed)
	SendMessageToDescendants(WM_GXINITIALUPDATE, 0, 0, TRUE, TRUE);
	
	pDoc->GetExcelReader()->SetTabCount(m_nSize);

	// iterate through the documents and post an OnInitialUpdate (delayed)
	SendMessageToDescendants(WM_GXINITIALUPDATEDONE, GX_EX_NEW_FILE, 0, TRUE, TRUE);

	return lRet;
}

void CGXExcelChildFrame::OnChangeInitTabCreateInfo(CGXTabCreateInfo*& pInfo)
{
	CGXExcelDocAdapter* pDoc = dynamic_cast<CGXExcelDocAdapter*>(m_pContext->m_pCurrentDoc);
	ASSERT(pDoc != NULL); // Error---> This has to be derived from CGXExcelReadDoc

	if(pDoc->GetWaitMode() == FALSE)
		return;

	for(int i = 0; i < m_nSize; i++)
	{
		pInfo[i].SetUseContextIntact(TRUE);
		pInfo[i].SetDocument(pDoc->GetParentDoc());
	}
}	

void CGXExcelChildFrame::InsertWorkSheetHandler( BOOL bBefore)
{
	UINT nID(0);

	CGXTabWndMgr* pMgr = GetTabManager();
	
	ASSERT(pMgr != NULL);

	CGXTabCreateInfo* pTabCreateInfo = new CGXTabCreateInfo();
	
	// get insertion information
	int nInsert = pMgr->GetCursel();
	GetInsertInfo(nInsert, pTabCreateInfo, nID);

	// context information will be ignored
	pTabCreateInfo->SetInit(FALSE);
	pTabCreateInfo->SetCreateContext(m_pContext);

	pTabCreateInfo->SetUseContextIntact(TRUE); // a new document should not be created
	pMgr->InsertWorkSheet(nInsert, bBefore, pTabCreateInfo, nID);

	if(pTabCreateInfo != NULL)
		delete pTabCreateInfo;


	CGXTabWndAdapter* pTabWndAdapt =  pMgr->GetTabWndAdapter();
	
	ASSERT(pTabWndAdapt != NULL);
	
	CGXGridTabWndAdapter* pGridAdapt = (CGXGridTabWndAdapter*) pTabWndAdapt;

	ASSERT(pGridAdapt != NULL);

	CGXTabWnd* pTabWnd = pGridAdapt->GetTabWnd();
	
	ASSERT(pTabWnd != NULL);

	CGXTabInfo& tabInfo = pTabWnd->GetBeam().GetTab( bBefore ? nInsert : nInsert + 1);

	CGXExcelReadView* pWndCreated = (CGXExcelReadView*) tabInfo.pExtra;

	ASSERT(pWndCreated != NULL);

	CGXExcelDocAdapter* pDoc = dynamic_cast<CGXExcelDocAdapter*>(m_pContext->m_pCurrentDoc);
	ASSERT(pDoc != NULL); // Error---> This has to be derived from CGXExcelReadDoc

   if ( ! bBefore  &&  nInsert + 1 == pMgr->GetTabCount() - 1)
	   pDoc->GetParamManager()->CreateObject( nInsert + 1);
   else
	   pDoc->GetParamManager()->CreateAndInsertObject( nInsert);

	//pWndCreated->SendMessage(WM_GXINITIALUPDATE, 0, 0);

	if(m_nPrimary == 0xFFFF && (bBefore ? nInsert : nInsert + 1) == 0)
		m_nPrimary = 1;
	else if(m_nPrimary != 0xFFFF && (bBefore ? nInsert : nInsert + 1) <= m_nPrimary)
		m_nPrimary++;
	
	if(m_nPrimary == 0xFFFF)
		pDoc->InitializeParam(bBefore ? nInsert : nInsert + 1, 0xFFFF);
	else
		pDoc->InitializeParam(bBefore ? nInsert : nInsert + 1, m_nPrimary);

	pWndCreated->SendMessage(WM_GXINITIALUPDATE, 0, 0);
	
	pDoc->GetExcelReader()->SetTabCount(pDoc->GetExcelReader()->GetTabCount()+1);


	pWndCreated->SendMessage(WM_GXINITIALUPDATEDONE, GX_EX_NEW_FILE, 0);
}

void CGXExcelChildFrame::DeleteWorkSheetHandler()
{
	CGXTabWndMgr* pMgr = GetTabManager();
	ASSERT(pMgr != NULL);
	
	int index = pMgr->GetCursel();

	if(m_nPrimary == 0xFFFF && index == 0)
		return;
	else if(m_nPrimary != 0xFFFF && index == m_nPrimary)
		return;
	
	if(index < m_nPrimary && m_nPrimary != 0xFFFF)
		m_nPrimary--;

	CGXWChildFrame::DeleteWorkSheetHandler();
	
	CGXExcelDocAdapter* pDoc = dynamic_cast<CGXExcelDocAdapter*>(m_pContext->m_pCurrentDoc);
	ASSERT(pDoc != NULL); // Error---> This has to be derived from CGXExcelReadDoc

	pDoc->GetParamManager()->RemoveObject(index);

	pDoc->GetExcelReader()->SetTabCount(pDoc->GetExcelReader()->GetTabCount() - 1);
}

void CGXExcelChildFrame::HandleOnNewWindow()
{
	// Opening a new window on this data is not supported
	AfxMessageBox(GX_IDS_EGXNWINDOWERROR);
}
	
void CGXExcelChildFrame::HandleDestroy()
{
	CGXTabWndMgr* pMgr = GetTabManager();
	ASSERT(pMgr != NULL);
	
	pMgr->Cleanup();
 
	CGXWChildFrame::HandleDestroy();
}
