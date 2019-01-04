///////////////////////////////////////////////////////////////////////////////
// gxclear.cpp : Clearing cells
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
// Author: Stefan Hoenig
//

#define _OG_EXPORT_IMPL

#include "stdafx.h"

#ifdef _GXDLL
#undef AFXAPI_DATA
#define AFXAPI_DATA __based(__segname("_DATA"))
#endif

// Headers

#ifndef _GXRESRC_H_
#include "grid\gxresrc.h"
#endif

#ifndef _GXEXT_H_
#include "grid\gxext.h"
#endif

#ifndef _AFXPRIV_H_
#include "afxpriv.h"
#endif

#ifndef _GXCORE_H_
#include "grid\gxcore.h"
#endif

#ifndef _GXCTRL_H_
#include "grid\gxctrl.h"
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXCORCLP")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// Edit|Clear

class CGXGridClearCellsImp: public CGXAbstractGridClearCellsImp
{
public:
	virtual BOOL CanClear(CGXGridCore* pGrid);
	virtual BOOL Clear(CGXGridCore* pGrid, BOOL bStyleOrValue /* = TRUE */);
	virtual BOOL ClearCells(CGXGridCore* pGrid, const CGXRangeList& selList, BOOL bStyleOrValue);
	virtual BOOL ClearCellsAlternate(CGXGridCore* pGrid, const CGXRange& sel, BOOL bStyleOrValue); 
};

void CGXGridCore::ImplementClearCells()
{
	if (m_pClearCellsImp == NULL)
	{
		// QA: 31521 Removal from AutoDeletePtr
		//AutoDeletePtr(m_pClearCellsImp = new CGXGridClearCellsImp);
		m_pClearCellsImp = new CGXGridClearCellsImp;
	}
}

BOOL CGXGridClearCellsImp::CanClear(CGXGridCore* pGrid)
{
	if (pGrid->IsReadOnly())
		return FALSE;

	return pGrid->GetParam() && !pGrid->GetParam()->GetRangeList()->IsEmpty() || pGrid->IsCurrentCell();
}

BOOL CGXGridClearCellsImp::Clear(CGXGridCore* pGrid, BOOL bStyleOrValue /* = TRUE */)
{
	CGXLongOperation theOp;

	CGXRangeList selList;
	BOOL bSucess = FALSE;

	VERIFY(pGrid->CopyRangeList(selList, TRUE));

	bSucess = pGrid->ClearCells(selList, bStyleOrValue);

	return bSucess;
}

BOOL CGXGridClearCellsImp::ClearCells(CGXGridCore* pGrid, const CGXRangeList& selList, BOOL bStyleOrValue)
{
	pGrid->BeginTrans(pGrid->m_pAppData->strmClearData);

	CGXLongOperation theOp;

	BOOL bCanceled = FALSE;

	theOp.SetStatusText(pGrid->m_pAppData->strmClearData, FALSE);
	theOp.SetCanRollback(TRUE);
	theOp.SetLockedState(TRUE);

	ROWCOL nFirstRow = 0;
	ROWCOL nFirstCol = 0;
	ROWCOL nRowCount = pGrid->GetRowCount();
	ROWCOL nColCount = pGrid->GetColCount();

	nFirstRow = pGrid->GetHeaderRows()+1;
	nFirstCol = pGrid->GetHeaderCols()+1;

	POSITION pos = selList.GetHeadPosition( );
	while (pos)
	{
		selList.GetNext(pos)->ExpandRange(nFirstRow, 
				nFirstCol,
				nRowCount,
				nColCount);
	}

	CRowColArray    awLeftCol, awRightCol,
					awTopRow, awBottomRow;

	selList.GetRowArray(pGrid->GetRowCount(), awTopRow, awBottomRow, FALSE);
	selList.GetColArray(pGrid->GetColCount(), awLeftCol, awRightCol, FALSE);

	BOOL bOldLockAddRecalcRange = pGrid->m_bLockAddRecalcRange;

	TRY
	{
		for (int rowindex = 0; !bCanceled && rowindex < awTopRow.GetSize(); rowindex++)
		{
			for (int colindex = 0; !bCanceled && colindex < awLeftCol.GetSize(); colindex++)
			{
				// SetStyleRange possibly throws an User Exception

				if (!pGrid->m_bLockAddRecalcRange)
					pGrid->AddRecalcRange(CGXRange(awTopRow[rowindex], awLeftCol[colindex],
							awBottomRow[rowindex], awRightCol[colindex]));

				pGrid->m_bLockAddRecalcRange = TRUE;

				if (bStyleOrValue)
				{
					// Remove all style information
					bCanceled = !pGrid->SetStyleRange(
						CGXRange(awTopRow[rowindex], awLeftCol[colindex],
							awBottomRow[rowindex], awRightCol[colindex]),
						NULL,
						gxRemove);

					if (bCanceled || theOp.DoMessages(bCanceled) && bCanceled)
						AfxThrowUserException();
				}
				else
				{
					CString s;

					// Only the value
					for (ROWCOL nRow = awTopRow[rowindex]; !bCanceled && nRow <= awBottomRow[rowindex]; nRow++)
					{
						for (ROWCOL nCol = awLeftCol[colindex]; !bCanceled && nCol <= awRightCol[colindex]; nCol++)
						{
							CGXStyle* pStyle = pGrid->CreateStyle();
							pGrid->ComposeStyleRowCol(nRow, nCol, pStyle);

							CGXControl* pControl = pGrid->GetRegisteredControl(pStyle->GetControl());

							// Give the control the chance to validate
							// and change the pasted text
							if (pControl->GetControlText(s, nRow, nCol, NULL, *pStyle)
								&& !s.IsEmpty())
								bCanceled = !pGrid->SetControlTextRowCol(nRow, nCol, _T(""), GX_INVALIDATE, pStyle);

							pGrid->RecycleStyle(pStyle);

							if (bCanceled || theOp.DoMessages(bCanceled) && bCanceled)
								AfxThrowUserException();
						}
					}
				}

				pGrid->m_bLockAddRecalcRange = bOldLockAddRecalcRange;
			}
		}
	}
	CATCH(CUserException, e)
	{
		pGrid->m_bLockAddRecalcRange = bOldLockAddRecalcRange;

		if (theOp.GetRollbackConfirmedState())
			pGrid->Rollback();
		else
			pGrid->CommitTrans();

		GX_THROW_LAST

		return FALSE;
	}
	END_CATCH

	pGrid->CommitTrans();

	pGrid->RefreshViews();
	
	return TRUE;
}

BOOL CGXGridClearCellsImp::ClearCellsAlternate(CGXGridCore* pGrid, const CGXRange& sel, BOOL bStyleOrValue)
{
	if (!bStyleOrValue)
		return pGrid->ClearCells(sel, bStyleOrValue);

	// determine which "global" styles to erase:
	bool bTable = false;
	bool bCols = false;
	bool bRows = false;
	if (sel.IsTable())
	{
		bTable = true;
		bCols = bRows = true;
	}
	else if (sel.IsCols())
		bCols = true;
	else if (sel.IsRows())
		bRows = true;
	else
	{
		if (sel.top == 1 && sel.bottom == pGrid->GetRowCount())
			bCols = true;
		if (sel.left == 1 && sel.right == pGrid->GetColCount())
			bRows = true;

		if (bCols && bRows)
			bTable = true;
	}

	BOOL bRet = pGrid->ClearCells(sel, bStyleOrValue);
	if (bRet)
	{
		if (bRows)
			pGrid->SetStyleRange(CGXRange().SetRows(1, pGrid->GetRowCount()), NULL, gxRemove);
		if (bCols)
			pGrid->SetStyleRange(CGXRange().SetCols(1, pGrid->GetColCount()), NULL, gxRemove);
		if (bTable)
			pGrid->SetStyleRange(CGXRange().SetTable(), NULL, gxRemove);
	}

	return bRet;
}
