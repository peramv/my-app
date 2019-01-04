///////////////////////////////////////////////////////////////////////////////
// ExcelReadDoc.cpp : implementation of the CGXExcelReadDoc class
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

#include "grid\gxrddoc.h"

#include "grid\gxtmpl.h"

#include "grid\gxtbmgr.h"

#include "grid\gxexhlp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CGXExcelReadDoc

IMPLEMENT_SERIAL(CGXExcelReadDoc, CGXDocument, 0)


BEGIN_MESSAGE_MAP(CGXExcelReadDoc, CGXDocument)
	//{{AFX_MSG_MAP(CGXExcelReadDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGXExcelReadDoc construction/destruction

CGXExcelReadDoc::CGXExcelReadDoc()
{
	// we read/write Excel files
	ImplementExcelReadWrite();
	
	// lone document
	SetPrimaryDocument(this);
}

CGXExcelReadDoc::~CGXExcelReadDoc()
{
	// no implementation	
}

BOOL CGXExcelReadDoc::OnNewDocument()
{
	if (!CGXDocument::OnNewDocument())
		return FALSE;

	SetModifiedFlag();
	
	return TRUE;
}

BOOL CGXExcelReadDoc::OnOpenDocument(LPCTSTR pszPathName)
{
	if(!GetWriteAsExcel())
		return CGXDocument::OnOpenDocument(pszPathName);

	if (!BaseOnOpenDocument(pszPathName))
	{
		SetModifiedFlag(FALSE);
		return FALSE;
	}

	return TRUE;
}


BOOL CGXExcelReadDoc::BaseOnOpenDocument(LPCTSTR lpszPathName)
{
	if (IsModified())
		TRACE0("Warning: OnOpenDocument replaces an unsaved document.\n");

	CFileException fe;
	CFile* pFile = GetFile(lpszPathName,
		CFile::modeRead|CFile::shareDenyNone, &fe);
	if (pFile == NULL)
	{
		ReportSaveLoadException(lpszPathName, &fe,
			FALSE, AFX_IDP_FAILED_TO_OPEN_DOC);
		return FALSE;
	}

	DeleteContents();
	SetModifiedFlag();  // dirty during de-serialize

	CArchive loadArchive(pFile, CArchive::load | CArchive::bNoFlushOnDelete);
	loadArchive.m_pDocument = this;
	loadArchive.m_bForceFlat = FALSE;
	
	try
	{
		CWaitCursor wait;
		Serialize(loadArchive);     // load me
		loadArchive.Close();
		ReleaseFile(pFile, FALSE);
	}
	catch(CArchiveException* e)
	{
		loadArchive.Close();
		ReleaseFile(pFile, TRUE);
		DeleteContents();   // remove failed contents
	
		ReportSaveLoadException(lpszPathName, e,
				FALSE, AFX_IDP_FAILED_TO_OPEN_DOC);
	   
		GX_THROW_LAST
		e->Delete();

		return FALSE;
	}
	catch(egxExcelRWFlags flags)
	{
		loadArchive.Close();
		ReleaseFile(pFile, TRUE);
		DeleteContents();   // remove failed contents
	
		CGXExRWErrorHandler::HandleError(flags);
		
		GX_THROW_LAST
		return FALSE;
	}
	catch(...)
	{
		loadArchive.Close();
		ReleaseFile(pFile, TRUE);
		DeleteContents();   // remove failed contents
	
		CGXExRWErrorHandler::HandleError(egxGenericFailure);
		
		GX_THROW_LAST
		return FALSE;
	}
	
	SetModifiedFlag(FALSE);     // start off with unmodified

	return TRUE;
}



BOOL CGXExcelReadDoc::OnSaveDocument(LPCTSTR pszPathName)
{
	// Ensure that each views current cell is stored
	CGXGridHint hint(gxHintTransferCurrentCell);
	hint.lParam = TRUE;

	UpdateAllViews(NULL, 0, &hint);

	// Now, you can save the document
	if(GetWriteAsExcel() == FALSE)
	{
		if (!CGXDocument::OnSaveDocument(pszPathName))
			return FALSE;
	}
	else
	{
		CFile file;
		file.SetFilePath(pszPathName);
		CArchive ar(&file, CArchive::store);
		Serialize(ar);
	}

	SetModifiedFlag(FALSE);
	return TRUE;
}


BOOL CGXExcelReadDoc::CanCloseFrame(CFrameWnd* pFrame)
{
	// Ensure that views can be deactivated
	CView* pView = pFrame->GetActiveView();
	if (pView && pView->SendMessage(WM_GX_CANACTIVATE, 0, 0))
		return FALSE;

	// Is it a grid?
	CGXGridCore* pGrid = NULL;
	if (pView->IsKindOf(RUNTIME_CLASS(CGXGridView)))
		pGrid = (CGXGridCore*) ((CGXGridView*) pView);
	
	if (pGrid)
	{
		// Ensure that the current cell can be stored
		if (!pGrid->TransferCurrentCell(TRUE, GX_UPDATENOW, FALSE))
			// grid state is invalid, don't close the frame
			return FALSE;
	}

	// Now, we can close the view
	return CGXDocument::CanCloseFrame(pFrame);
}

/////////////////////////////////////////////////////////////////////////////
// CGXExcelReadDoc diagnostics

#ifdef _DEBUG
void CGXExcelReadDoc::AssertValid() const
{
	CGXDocument::AssertValid();
}

void CGXExcelReadDoc::Dump(CDumpContext& dc) const
{
	CGXDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGXExcelReadDoc commands

void CGXExcelReadDoc::Serialize(CArchive& ar)
{
	// This is implemented in CGXExcelDocAdapter
	CFile* pFile = ar.GetFile();
	ASSERT(pFile != NULL);

	SetFilePath(pFile->GetFilePath());
	
	GetExTabManager()->SetLDocument(this);
	
	ExcelSerializeImpl(ar);
}

void CGXExcelReadDoc::WorkBookSerialize(CArchive& ar)
{
	// This is implemented in CGXExcelDocAdapter
	ExcelWorkBookSerializeImpl(ar);
}

CGXExTabWndMgr* CGXExcelReadDoc::GetExTabManager()
{
	CGXTabWndMgr* pTabMgr = GetTabManager();
	
	ASSERT(pTabMgr != NULL);

	CGXExTabWndMgr* pExTabMgr = dynamic_cast<CGXExTabWndMgr*>(pTabMgr);
			
	ASSERT(pExTabMgr != NULL);
	
	return pExTabMgr;
}


BOOL CGXExcelReadDoc::SaveModified()
{
	return CDocument::SaveModified();
}
