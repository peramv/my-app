///////////////////////////////////////////////////////////////////////////////
// gxapatr.cpp : Function implementations for the application adapter
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

#include "grid\gxapatr.h"

#include "grid\gxtbmgr.h"

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXTABSER")
#endif


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// warning about RTTI
#include "grid\gxrtti.h"

//@doc
//@mfunc
//@rem
//Constructs a CGXAdapter object
//@xref <c CGXAppAdapter>
CGXAppAdapter::CGXAppAdapter()
{
	m_pTabWndHolder = NULL;
}

CGXAppAdapter::~CGXAppAdapter()
{
	if(m_pTabWndHolder != NULL)
		delete m_pTabWndHolder;
}

// return a tab manager based on the Frame run time class that gets passed in

//@doc
//@mfunc
//@parm CRuntimeClass* | pRClass | The runtime class of the frame requesting this information
//@parm CDocument*     | pDocument | The pointer to the document that is in context (This is usually the primary document that is related to this frame)
//@rem
//This function simply returns a pointer to the contained tab window manager instance. 
//Please refer CGXTabWndMgr. This tab manager instance is uniquely identified by 
//the runtime class of the frame and the document instance.
//@xref <c CGXAppAdapter> <c CGXTabWndMgr> <c CGXFrameAdapter> <c CGXDocument>
CGXTabWndMgr* CGXAppAdapter::GetTabManager(CRuntimeClass* pRClass, CDocument* pDocument)
{
	if(m_pTabWndHolder == NULL)
		m_pTabWndHolder = CreateTabWndHolder();
	
	// The default implementation does not use the frame runtime class. It only uses the document
	// pointer that gets passed in. You can derive from CGXAppAdapter to have two dimsenional
	// support where different maps would be used based on the runtime class of the frame
	CGXTabWndMgr* pMgr = m_pTabWndHolder->CreateObject( (SEC_DWORD) pDocument); 
	
	ASSERT(pMgr != NULL);

	// OnInitialize can be called repeatedly. It should always check current state
	pMgr->OnInitialize();
	
	return pMgr;

	GX_UNUSED_ALWAYS(pRClass);
	GX_UNUSED_ALWAYS(pDocument);
}


//@doc
//@mfunc
//@parm CRuntimeClass* | pRClass | The runtime class of the frame
//@parm CDocument*     | pDocument | The pointer to the document (usually the primary document)
//that is used as the context for this frame type.
//@rem
//The instance of CGXTabWndMgr that is uniquely identified by 
//this frame runtime class and document instance will be removed.
//@xref <c CGXAppAdapter> <mf CGXAppAdapter::GetTabManager> <c CGXFrameAdapter> <c CGXDocument> 
void CGXAppAdapter::RemoveTabManager(CRuntimeClass* pRClass, CDocument* pDocument)
{
	ASSERT(m_pTabWndHolder != NULL);

	m_pTabWndHolder->RemoveObject( (SEC_DWORD) pDocument); 

	GX_UNUSED_ALWAYS(pRClass);
	GX_UNUSED_ALWAYS(pDocument);
}

//@doc
//@mfunc 
//@parm CCreateContext* | pContext | The create context that is used to identify the document template.
//@rem
//Helper that calls through to GetDocTemplate(CRuntimeClass* pViewClass, CRuntimeClass* pDocClass) by gleaning the parameters for the call from CCreateContext.
//@xref 
//<c CGXAppAdapter>
CDocTemplate* CGXAppAdapter::GetDocTemplate(CCreateContext* pContext)
{	
	return GetDocTemplate(pContext->m_pNewViewClass, pContext->m_pCurrentDoc->GetRuntimeClass());
}

//@doc
//@mfunc
//@rem
//This function will be called to create an instance of the Tab Window holder. 
//The node manager class performs simply duties such as object instantiation 
//and garbage collection. You can override this function to use your own implementation 
//if you wish to change the default behavior.
//@xref <c CGXAppAdapter>
CGXNodeManager<CGXTabWndMgr>* CGXAppAdapter::CreateTabWndHolder()
{
	return new CGXNodeManager<CGXTabWndMgr>(RUNTIME_CLASS(CGXTabWndMgr));
}
