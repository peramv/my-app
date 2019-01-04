///////////////////////////////////////////////////////////////////////////////
// gxtbgadp.cpp : Function implementations for the tab window adapter (for CGXTabWnd).
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

// By implementing this adapter with another tab window or worksheet window you can 
// use this persistence mechanism with other tab windows. For example you can implement an
// adapter for SECTabWnd.

#define _OG_EXPORT_IMPL

#include "stdafx.h"

#ifdef _GXDLL
#undef AFXAPI_DATA
#define AFXAPI_DATA __based(__segname("_DATA"))
#endif

#include "grid\gxresrc.h"

#include "grid\gxtbadpt.h"

#include "grid\gxtbgadp.h"

#include "grid\gxtwnd.h"

#ifndef _AFXPRIV_H_
#include "afxpriv.h"
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXTABSER")
#endif


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

CGXGridTabWndAdapter::CGXGridTabWndAdapter()
{
	m_pTabWnd = new CGXTabWnd;
	m_pParentWnd = NULL;
}

CGXGridTabWndAdapter::~CGXGridTabWndAdapter()
{
	if(m_pTabWnd != NULL)
		delete m_pTabWnd;
}

void CGXGridTabWndAdapter::SetParentWnd(CWnd* pParentWnd)
{
	ASSERT_VALID(pParentWnd);  //Parent Window is invalid
	m_pParentWnd = pParentWnd;
}


CWnd* CGXGridTabWndAdapter::GetParentWnd() const
{
	return m_pParentWnd;
}


int CGXGridTabWndAdapter::GetTabCount() const
{
	ASSERT(m_pTabWnd != NULL);
	
	if(m_pTabWnd != NULL)
		return m_pTabWnd->GetBeam().GetCount();
	else
		return 0;
}

int CGXGridTabWndAdapter::GetCursel() const
{
	ASSERT(m_pTabWnd != NULL);
	
	if(m_pTabWnd != NULL)
		return m_pTabWnd->GetBeam().GetCurSel();
	else
		return GX_INVALID;
}

CWnd* CGXGridTabWndAdapter::CreateView(CRuntimeClass* pViewRuntimeClass, const TCHAR* pszLabel, CCreateContext* pContextDefault)
{
	ASSERT(m_pTabWnd != NULL);

	CString strLabel = pszLabel;
	
	if(!_tcscmp(pszLabel, _T("")))
		strLabel = GenerateLabel(m_pTabWnd->m_nLastViewID - AFX_IDW_PANE_FIRST + 1);

	if(m_pTabWnd != NULL)
		return m_pTabWnd->CreateView( pViewRuntimeClass, strLabel, pContextDefault);
	else
		return NULL;
}


BOOL CGXGridTabWndAdapter::Create(const TCHAR* pszLabel, CCreateContext* pCreateContext)
{
	ASSERT(m_pTabWnd != NULL);

	ASSERT_VALID(m_pParentWnd); // Error-->Invalid parent window

	CString strLabel = pszLabel;
	
	if(!_tcscmp(pszLabel, _T("")))
		strLabel = GenerateLabel();

	if(m_pTabWnd)
	{
		BOOL b(FALSE);
		b = m_pTabWnd->Create(m_pParentWnd, strLabel, pCreateContext);		
		if(b)
		{
			// there is only one pane so we can do this
			CWnd* pWnd = m_pTabWnd->GetActivePane();
			if(pWnd)
				pWnd->SendMessage(WM_INITIALUPDATE);
		}
		return b;
	}
	else
		return FALSE;
}

// return a meaningful default label
CString CGXGridTabWndAdapter::GenerateLabel(UINT nID /* = 0 */)
{
	ASSERT(m_pTabWnd != NULL); // The tab window cannot be null.

	UINT nIdToUse = nID + 1; 
	
	CString strLabel;
	strLabel.Format(GX_IDS_TABTEXT, nIdToUse);
	
	TRACE1("Label generated %s\n", strLabel);
	
	return strLabel;
}

BOOL CGXGridTabWndAdapter::InsertWorkSheet(int nInsert, BOOL bBefore, CRuntimeClass* pViewRuntimeClass, CCreateContext* pContext, const TCHAR* pszLabel /* = 0*/, UINT nID /*= 0*/)
{
	ASSERT(m_pTabWnd != NULL); // The tab window cannot be null.

	if( !(nInsert >= 0 && nInsert <= m_pTabWnd->GetBeam().GetCount()) )
			return FALSE;

	CString strLabel = pszLabel;

	if(!_tcscmp(pszLabel, _T("")))
		strLabel = GenerateLabel(m_pTabWnd->m_nLastViewID - AFX_IDW_PANE_FIRST + 1);

	// let CGXTabWnd do the creation
	BOOL bSendInitialUpdate(FALSE);
	CWnd* pWnd = SpecialTabWndCreate(m_pTabWnd, pViewRuntimeClass, bSendInitialUpdate,  pContext, strLabel, nID);
	
	ASSERT_VALID(pWnd);

	if(pWnd)
	{
		// Will fail if tab index is invalid
		m_pTabWnd->SwitchTab(nInsert);
		// pass TRUE to insert before currently selected tab
      if ( ! bBefore && nInsert == m_pTabWnd->GetBeam().GetCount() - 1) {
         m_pTabWnd->GetBeam().m_nCurrent = -1 ;
		   m_pTabWnd->GetBeam().InsertTab(FALSE, pszLabel, pWnd);
      }
      else
		   m_pTabWnd->GetBeam().InsertTab(TRUE, pszLabel, pWnd);
		
		//if (bSendInitialUpdate)
			pWnd->SendMessage(WM_INITIALUPDATE);

		// force a WM_SIZE
		CRect rect;
		pWnd->GetClientRect(rect);
		pWnd->MoveWindow(rect);

		m_pTabWnd->SaveScrollbarState(pWnd);


		// now switch to the newly inserted tab
		m_pTabWnd->SwitchTab(bBefore ? nInsert : nInsert + 1);

	}
	else
		return FALSE;

	return TRUE;
}

BOOL CGXGridTabWndAdapter::DeleteWorksheet(int nDeleteIndex)
{
	ASSERT(m_pTabWnd != NULL); // The tab window cannot be null.

	if(m_pTabWnd == NULL || nDeleteIndex > GetTabCount()-1)
		return FALSE;
	
	m_pTabWnd->RemoveTab(nDeleteIndex);
	
	return TRUE;
}

BOOL CGXGridTabWndAdapter::CanInsertWorkSheet() const
{
	return TRUE;
}

BOOL CGXGridTabWndAdapter::CanDeleteWorkSheet() const
{
	if (GetTabCount() == 1)
		return FALSE;
	else
		return TRUE;
}
	
void CGXGridTabWndAdapter::Destroy()
{
	delete this;	
}

CWnd* CGXGridTabWndAdapter::SpecialTabWndCreate(CGXTabWnd* pTabWnd, CRuntimeClass* pViewClass,  BOOL& bSendInitialUpdate,  CCreateContext* pContext, LPCTSTR szLabel, UINT nID)
{
	ASSERT(pTabWnd != NULL); // Error tab window passed in has to be valid


	bSendInitialUpdate = FALSE;

	if (nID == 0)
		nID = pTabWnd->m_nLastViewID + 1;

	CCreateContext contextT;
	if (pContext == NULL)
	{
		// if no context specified, generate one from the currently selected
		//  client if possible
		CView* pOldView = pTabWnd->GetParentFrame()->GetActiveView();
		if (pOldView != NULL)
		{
			// set info about last pane
			ASSERT(contextT.m_pCurrentFrame == NULL);
			contextT.m_pLastView = pOldView;
			contextT.m_pCurrentDoc = pOldView->GetDocument();
			if (contextT.m_pCurrentDoc != NULL)
				contextT.m_pNewDocTemplate =
				  contextT.m_pCurrentDoc->GetDocTemplate();
		}
		pContext = &contextT;
		bSendInitialUpdate = TRUE;
	}

	CWnd* pWnd = NULL;
	TRY
	{
		pWnd = (CWnd*)pViewClass->CreateObject();
		if (pWnd == NULL)
			AfxThrowMemoryException();
	}
	CATCH_ALL(e)
	{
		TRACE0("Out of memory creating a splitter pane\n");
		GX_THROW_LAST
		return pWnd;
	}
	END_CATCH_ALL

	ASSERT(pWnd->IsKindOf(RUNTIME_CLASS(CWnd)));
	ASSERT(pWnd->GetSafeHwnd() == NULL);       // not yet created

	// Create with the right size (wrong position)
	CRect rect;
	pTabWnd->GetInsideRect(rect);

	DWORD dwStyle = AFX_WS_DEFAULT_VIEW & ~WS_BORDER;

	if (pTabWnd->m_pBeam->m_nTabs > 0)
		dwStyle &= ~WS_VISIBLE;

	if (!pWnd->Create(NULL, NULL, dwStyle,
		rect, pTabWnd, nID, pContext))
	{
		TRACE0("Warning: couldn't create client pane for splitter\n");
			// pWnd will be cleaned up by PostNcDestroy
		return NULL;
	}

	// send initial notification message
	HMENU hMenu = 0;
	if (pContext->m_pNewDocTemplate && pContext->m_pNewDocTemplate->IsKindOf(RUNTIME_CLASS(CMultiDocTemplate)))
		hMenu = ((CMultiDocTemplate*) pContext->m_pNewDocTemplate)->m_hMenuShared;
	return pWnd;

	GX_UNUSED_ALWAYS(szLabel);
}


