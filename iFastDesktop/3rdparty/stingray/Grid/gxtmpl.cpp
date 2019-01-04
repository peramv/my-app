///////////////////////////////////////////////////////////////////////////////
// gxtmpl.cpp : Function implementations for doc template handlers
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


#include "grid\gxtmpl.h"


#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXTABSER")
#endif


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif


// to gain access to protected members
struct __sdoctemplate: public CSingleDocTemplate
{
	__sdoctemplate(UINT nIDResource, CRuntimeClass* pDocClass,
		CRuntimeClass* pFrameClass, CRuntimeClass* pViewClass):CSingleDocTemplate(nIDResource, pDocClass, pFrameClass, pViewClass){};

	~__sdoctemplate();

	friend struct CGXDocTemplateOp;
};


struct __mdoctemplate: public CMultiDocTemplate
{
	__mdoctemplate(UINT nIDResource, CRuntimeClass* pDocClass,
		CRuntimeClass* pFrameClass, CRuntimeClass* pViewClass):CMultiDocTemplate(nIDResource, pDocClass, pFrameClass, pViewClass){};

	~__mdoctemplate();

	friend struct CGXDocTemplateOp;
};


CDocument* CGXDocTemplateOp::CreateDocumentFile(CDocTemplate* pDocTemplate)
{
	if(pDocTemplate->IsKindOf(RUNTIME_CLASS(CMultiDocTemplate)))
		return	CreateDocumentFile( (CMultiDocTemplate*) pDocTemplate);
	
	else if(pDocTemplate->IsKindOf(RUNTIME_CLASS(CSingleDocTemplate)))
		return CreateDocumentFile( (CSingleDocTemplate*) pDocTemplate);
	else
	{
		ASSERT(0);
		return NULL;
	}
}

CDocument* CGXDocTemplateOp::CreateDocumentFile(CMultiDocTemplate* pDocTemplate)
{
	ASSERT(pDocTemplate != NULL);
	
	ASSERT_KINDOF(CMultiDocTemplate, pDocTemplate);

	__mdoctemplate* pFriendTemplate = (__mdoctemplate*)pDocTemplate;	

	CDocument* pDocument = pDocTemplate->CreateNewDocument();
	
	if (pDocument == NULL)
	{
		TRACE0("CDocTemplate::CreateNewDocument returned NULL.\n");
		AfxMessageBox(AFX_IDP_FAILED_TO_CREATE_DOC);
		return NULL;
	}
	
	ASSERT_VALID(pDocument);

	BOOL bAutoDelete = pDocument->m_bAutoDelete;
	pDocument->m_bAutoDelete = FALSE;   // don't destroy if something goes wrong
	
	pDocument->m_bAutoDelete = bAutoDelete;
	
	// create a new document - with default document name
	pDocTemplate->SetDefaultTitle(pDocument);

	if (!pDocument->OnNewDocument())
	{
		// user has be alerted to what failed in OnNewDocument
		TRACE0("CDocument::OnNewDocument returned FALSE.\n");
		return NULL;
	}

	// it worked, now bump untitled count
	pFriendTemplate->m_nUntitledCount++;
	
	return pDocument;
}


CDocument* CGXDocTemplateOp::CreateDocumentFile(CSingleDocTemplate* pDocTemplate)
	// if lpszPathName == NULL => create new file of this type
{
	ASSERT(pDocTemplate != NULL);
	
	ASSERT_KINDOF(CSingleDocTemplate, pDocTemplate);

	__sdoctemplate* pFriendTemplate = (__sdoctemplate*)pDocTemplate;	

	CDocument* pDocument = NULL;
	
	BOOL bCreated = FALSE;      // => doc and frame created
	//BOOL bWasModified = FALSE;

	if (pFriendTemplate->m_pOnlyDoc != NULL)
	{
		// already have a document - reinit it
		pDocument = pFriendTemplate->m_pOnlyDoc;
		if (!pDocument->SaveModified())
			return NULL;        // leave the original one
	}
	else
	{
		// create a new document
		pDocument = pDocTemplate->CreateNewDocument();
		bCreated = TRUE;
	}

	if (pDocument == NULL)
	{
		AfxMessageBox(AFX_IDP_FAILED_TO_CREATE_DOC);
		return NULL;
	}
	ASSERT(pDocument == pFriendTemplate->m_pOnlyDoc);

	
	// create a new document
	pDocTemplate->SetDefaultTitle(pDocument);

	if (!pDocument->OnNewDocument())
	{
		// user has been alerted to what failed in OnNewDocument
		TRACE0("CDocument::OnNewDocument returned FALSE.\n");
		return NULL;
	}
	
	return pDocument;
}

