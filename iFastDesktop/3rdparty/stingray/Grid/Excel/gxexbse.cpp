///////////////////////////////////////////////////////////////////////////////
// gxexbse.cpp
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

#include "grid\gxexbse.h"

#include "grid\gxdcadpt.h"

#include "grid\gxexhlp.h"

/////////////////////////////////////////////////////////////////////////////
// CGXExcelGrid construction

CGXExcelGrid::CGXExcelGrid(CWnd* /*pGridWnd*/, CDocument* /*pGridDoc*/, BOOL /*bIsViewContext*/)
{
	// no implementation
}
	
CGXExcelGrid::~CGXExcelGrid()
{
	// no implementation
}

// Implementation
// It is also possible to have this function implemented in the derived class
CGXGridCore* CGXExcelGrid::GetCorePtr()
{
	CGXGridCore* pCore = dynamic_cast<CGXGridCore*>(this);
		
	ASSERT(pCore != NULL); // Error--> this class has to be used in conjunction with 
	// CGXGridCore

	return pCore;
}

BOOL CGXExcelGrid::IsFormulaMode()
{
	BOOL bFormula(FALSE);

	if( ((_core*)GetCorePtr())->m_pDefaultDataClass == RUNTIME_CLASS(CGXFormulaSheet))
		bFormula = TRUE;
	
	return bFormula;
}

// operations/handlers

BOOL CGXExcelGrid::OnPasteFromClipboardImpl(const CGXRange& rg)
{
	CGXGridCore* pCore = GetCorePtr();
	
	if(pCore == NULL)
		return FALSE;

	CGXExcelClipHandler clip(IsFormulaMode());
	
	BOOL b(FALSE);

	try
	{
		b = clip.Paste(pCore, rg);
	}
	catch(egxExcelRWFlags flags)
	{
		GX_EX_FMT_TRACE("OG Pro Error: CGXExcelReaderImpl::ExcelWriteImpl.")
		CGXExRWErrorHandler::HandleError(flags);

		GX_THROW_LAST
	}
	
	if (b)
		return TRUE;
	else
		return pCore->CGXGridCore::OnPasteFromClipboard(rg);
		
}

BOOL CGXExcelGrid::OnCheckClipboardFormatImpl()
{
	CGXGridCore* pCore = GetCorePtr();
	
	if(pCore == NULL)
		return FALSE;

	CGXExcelClipHandler clip(IsFormulaMode());
	
	if ( clip.CanPaste(pCore) )
		return TRUE;
	else
		return pCore->CGXGridCore::OnCheckClipboardFormat();
}

BOOL CGXExcelGrid::CopyRangeImpl(const CGXRangeList& selList)
{
	CGXGridCore* pCore = GetCorePtr();
	
	if(pCore == NULL)
		return FALSE;

	// we will only copy one selected range in BIFF format. This is the same with Excel
	CGXExcelClipHandler clip(IsFormulaMode());
	
	CGXRange* pRange = selList.GetHead();
	BOOL b(FALSE);
	
	try
	{
		b = clip.Copy(pCore, *pRange);
	}
	catch(egxExcelRWFlags flags)
	{
		GX_EX_FMT_TRACE("OG Pro Error: CGXExcelReaderImpl::ExcelWriteImpl.")
		CGXExRWErrorHandler::HandleError(flags);

		GX_THROW_LAST
	}
	
	b |= pCore->CGXGridCore::CopyRange(selList);
	
	return b;
}


/////////////////////////////////////////////////////////////////////////////
// CGXExcelGrid diagnostics

#ifdef _DEBUG
void CGXExcelGrid::AssertValid() const
{
}

void CGXExcelGrid::Dump(CDumpContext& dc) const
{
	dc;
}
#endif //_DEBUG
