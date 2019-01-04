///////////////////////////////////////////////////////////////////////////////
// gxextb.cpp
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

#define _OG_EXPORT_IMPL

#include "stdafx.h"

#include "grid\gxextb.h"

IMPLEMENT_SERIAL(CGXExTabWndMgr, CGXTabWndMgr, 0)


CGXExTabWndMgr::CGXExTabWndMgr()
{
	m_pLoneDocument = NULL;
}
	
CGXExTabWndMgr::CGXExTabWndMgr(CWnd* pTabParent):CGXTabWndMgr(pTabParent)
{
	m_pLoneDocument = NULL;
}
	
CGXExTabWndMgr::~CGXExTabWndMgr()
{

}

void CGXExTabWndMgr::SetLDocument(CGXDocument* pDocument)
{
	m_pLoneDocument = pDocument;
}


BOOL CGXExTabWndMgr::ReadDocumentsFromArchive(CArchive& ar, CGXDocument* pDocThis, int nIndex)
{
	return ExIterateAndLoadDocuments(ar, pDocThis, nIndex);		
}


BOOL CGXExTabWndMgr::ExIterateAndLoadDocuments(CArchive& ar, CGXDocument* pDocThis, int /*nIndex*/)
{
	pDocThis->WorkBookSerialize(ar);

	return TRUE;
}

BOOL CGXExTabWndMgr::StoreDocumentsInArchive(CArchive& ar)
{
	return ExIterateAndSaveDocuments(ar);
}

BOOL CGXExTabWndMgr::ExIterateAndSaveDocuments(CArchive& ar) const
{
	ASSERT(m_pLoneDocument != NULL);

	m_pLoneDocument->WorkBookSerialize(ar);

	return TRUE;
}
