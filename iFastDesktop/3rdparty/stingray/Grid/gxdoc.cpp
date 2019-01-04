///////////////////////////////////////////////////////////////////////////////
// gxdoc.cpp : Function implementations for the special workbook document
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

#include "grid\gxdoc.h"

#include "grid\gxapatr.h"

#include "grid\gxtbmgr.h"

IMPLEMENT_SERIAL(CGXDocument, CDocument, 0)

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXTABSER")
#endif


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif


// implementation of CGXDocument
CGXDocument::CGXDocument()
{
	m_pDocument = NULL;
}
	
CGXDocument::~CGXDocument()
{
	
}

void CGXDocument::WorkBookSerialize(CArchive& ar)
{
	// you have to implement this in your derived class. Simply copy your existing code from the Serialize 
	// override to this override
	ASSERT(0);
	GX_UNUSED_ALWAYS(ar);
}

// This will be called only for the primary document. The one that is created by the frame work. This gets
// delegated to the correct tab manager

class __doctemplaccess: public CDocTemplate
{
	__doctemplaccess(UINT nIDResource, CRuntimeClass* pDocClass,
		CRuntimeClass* pFrameClass, CRuntimeClass* pViewClass):CDocTemplate(nIDResource, pDocClass, pFrameClass, pViewClass){};
	
	~__doctemplaccess();

	friend class CGXDocument;
};


CGXTabWndMgr* CGXDocument::GetTabManager()
{
	CGXAppAdapter* pAppAdapt = dynamic_cast<CGXAppAdapter*>(AfxGetApp());
			
	ASSERT(pAppAdapt != NULL);
	
	__doctemplaccess* pDocTempl = (__doctemplaccess*) GetDocTemplate();

	ASSERT(pDocTempl != NULL);

	// get the correct tab manager for this document's frame window
	CGXTabWndMgr* pMgr = pAppAdapt->GetTabManager(pDocTempl->m_pFrameClass, this);
	
	ASSERT(pMgr != NULL);

	return pMgr;
}

void CGXDocument::Serialize(CArchive& ar)
{
	// get the correct tab manager for this document's frame window
	if(ar.IsLoading())
		SetPrimaryDocument(this);
	
	CGXTabWndMgr* pMgr = GetPrimaryDocument()->GetTabManager();
	
	// call the serialization helpers that will load the correct documents in order
	if(ar.IsLoading())
		pMgr->ReadDocumentsFromArchive(ar, this);
	else
		pMgr->StoreDocumentsInArchive(ar);
}

BOOL CGXDocument::DoSave(LPCTSTR lpszPathName, BOOL bReplace)
{
	TRACE1("The current document is %x\n", this);
	
	ASSERT(GetPrimaryDocument() != NULL); // The primary document acts as the controller for save operations and must be valid--->END
	

	if(GetPrimaryDocument() == this)
	{
		TRACE0("DoSave called for primary document. Actual save made\n");
		return CDocument::DoSave(lpszPathName, bReplace);
	}

	return GetPrimaryDocument()->DoSave(lpszPathName, bReplace);
}

void CGXDocument::SetPrimaryDocument(CGXDocument* pDoc) 
{
	TRACE1("The current document is %x\n", this);
	TRACE1("The primary document is %x\n", pDoc);

	ASSERT(pDoc != NULL);
	ASSERT_KINDOF(CGXDocument, pDoc);
		
	m_pDocument = pDoc;
}

CGXDocument* CGXDocument::GetPrimaryDocument() const
{
	return m_pDocument;
}


BOOL CGXDocument::SaveModified()
{
	if(GetPrimaryDocument() != this)
		return GetPrimaryDocument()->SaveModified();

	CGXTabWndMgr* pMgr = GetTabManager();

	if (!pMgr->IsModified())
		return TRUE;        // ok to continue

	BOOL bOrigModify = m_bModified;

	// for setmodified to be called
	SetModifiedFlag();

	// let the base class do the work
	BOOL b = CDocument::SaveModified();

	if(!b)
		m_bModified = bOrigModify;
	else
		m_bModified = FALSE; // Saved

	pMgr->SetModify(TRUE);
	
	return b;
}

