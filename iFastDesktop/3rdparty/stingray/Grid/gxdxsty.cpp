///////////////////////////////////////////////////////////////////////////////
// gxdxsty.cpp : style data exchange (OG Designer files or clipboard)
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

#ifndef _GXDELAYR_H_
#include "grid\gxdelayr.h"
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

class CGXGridStyleDataExchangeImp: public CGXAbstractGridStyleDataExchangeImp
{
public:
	virtual BOOL CopyCellsToArchive(CGXGridCore* pGrid, CArchive& ar, const CGXRangeList& selList, BOOL bLoadBaseStyles);
	virtual BOOL GetClipboardStyleRowCol(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, CGXStyle* pStyle, BOOL bLoadBaseStyles);
	virtual BOOL PasteCellsFromArchive(CGXGridCore* pGrid, CArchive& ar, const CGXRange& range, BOOL bIgnoreDiffRange);
};

void CGXGridCore::ImplementStyleDataExchange()
{
	if (m_pStyleDataExchangeImp == NULL)
	{
		// QA: 31521 Removal from AutoDeletePtr
		//AutoDeletePtr(m_pStyleDataExchangeImp = new CGXGridStyleDataExchangeImp);
		m_pStyleDataExchangeImp = new CGXGridStyleDataExchangeImp;
	}
}

BOOL CGXGridStyleDataExchangeImp::CopyCellsToArchive(CGXGridCore* pGrid, CArchive& ar, const CGXRangeList& selList, BOOL bLoadBaseStyles)
{
	// store rows/columns indizes to process in an array
	CRowColArray    awLeftCol, awRightCol,
					awTopRow, awBottomRow;

	selList.GetRowArray(pGrid->GetRowCount(), awTopRow, awBottomRow, FALSE);
	selList.GetColArray(pGrid->GetColCount(), awLeftCol, awRightCol, FALSE);

	// determine no of rows/cols to process
	ROWCOL nRows = 0;
	int rowindex;
	for (rowindex = 0; rowindex < awTopRow.GetSize(); rowindex++)
		nRows += awBottomRow[rowindex]-awTopRow[rowindex]+1;

	ROWCOL nCols = 0;
	int colindex;
	for (colindex = 0; colindex < awLeftCol.GetSize(); colindex++)
		nCols += awRightCol[colindex]-awLeftCol[colindex]+1;

	DWORD dwSize = nRows*nCols;

	ROWCOL nRowsDone = 0, nColsDone = 0;

	// status message, let the user abort the operation
	CGXLongOperation theOp;
	theOp.SetStatusText(pGrid->m_pAppData->strmCopyInternal, FALSE);

	CDocument* pOldDocument = ar.m_pDocument;

	// This is a bit dirty, but style-objects need access to the styles-map
	// and CArchive::m_pDocument is not needed for serializing the following objects
	ar.m_pDocument = (CDocument*) pGrid->GetParam()->GetStylesMap();

	ar << nRows;
	ar << nCols;

	BOOL bCanceled = FALSE;

	CObArray* pOldCellsArray = NULL;

	TRY
	{
		// Uurgh ... too much!
		if (dwSize >= UINT_MAX / sizeof(CObject*) || nRows > SHRT_MAX || nCols > SHRT_MAX)
			AfxThrowMemoryException();

		// Try, if Array fits in memory
		pOldCellsArray = new CObArray;

		pOldCellsArray->SetSize((int) dwSize);

		// fill pOldCellsArray row by row
		for (rowindex = 0; !bCanceled && rowindex < awTopRow.GetSize(); rowindex++)
		{
			for (ROWCOL nRow = awTopRow[rowindex]; nRow <= awBottomRow[rowindex]; nRow++)
			{
				nColsDone = 0;
				for (colindex = 0; !bCanceled && colindex < awLeftCol.GetSize(); colindex++)
				{
					for (ROWCOL nCol = awLeftCol[colindex]; nCol <= awRightCol[colindex]; nCol++)
					{

						// Store styles in array, but allow user to abort
						CGXStyle* pStyle;
						DWORD dwIndex;

						pStyle = pGrid->CreateStyle();
						dwIndex = nRowsDone*nCols+nColsDone;

						if (pGrid->GetClipboardStyleRowCol(nRow, nCol, pStyle, bLoadBaseStyles))
							pOldCellsArray->SetAt((int) dwIndex, pStyle);
						else
							pGrid->RecycleStyle(pStyle);

						// check, if user pressed ESC to cancel
						if (theOp.NeedMessages())
						{
							theOp.SetPercentDone((int) (dwIndex * 100 / dwSize));
							theOp.DoMessages(bCanceled);
							if (bCanceled)
								AfxThrowUserException();
						}

						nColsDone++;
					}
				}

				nRowsDone++;
			}
		}
	}
	CATCH(CException, e)
	{
		GX_THROW_LAST

		if (e->IsKindOf(RUNTIME_CLASS(CMemoryException)))
			AfxMessageBox(GX_IDM_RANGETOOBIG, MB_OK);
		bCanceled = TRUE;
	}
	END_CATCH


	theOp.DoMessages(bCanceled);

	if (!bCanceled)
	{
		// store in clipboard
		ar << pOldCellsArray;
	}

	// clean up
	if (pOldCellsArray)
	{
		for (int i = 0; i < pOldCellsArray->GetSize(); i++)
			delete pOldCellsArray->GetAt(i);
	}
	delete pOldCellsArray;

	ar.m_pDocument = pOldDocument;

	// you may use these internal attributes to determine
	// the number of written rows and cols after this function
	// returns

	pGrid->m_nRowsCopied = nRows;
	pGrid->m_nColsCopied = nCols;

	return !bCanceled;
}

BOOL CGXGridStyleDataExchangeImp::GetClipboardStyleRowCol(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, CGXStyle* pStyle, BOOL bLoadBaseStyles)
{
	int nValueType = 0;

	if (pGrid->m_nClipboardFlags&GX_DNDEXPRESSION)
		nValueType = pGrid->m_nExpressionValueType;

	// Shall I compose the style with all its base style settings?
	if (bLoadBaseStyles)
	{
		pGrid->ComposeStyleRowCol(nRow, nCol, pStyle, TRUE);
		return TRUE;
	}
	// or, shall I only copy the cells specific attributes
	else 
		return pGrid->GetStyleRowCol(nRow, nCol, *pStyle, gxCopy, nValueType);

}

// paste style information

BOOL CGXGridStyleDataExchangeImp::PasteCellsFromArchive(CGXGridCore* pGrid, CArchive& ar, const CGXRange& range, BOOL bIgnoreDiffRange)
{
	int nValueType = pGrid->m_nExpressionValueType;

	BOOL bCanceled = FALSE;

	CDocument* pOldDocument = ar.m_pDocument;

	// This is a bit dirty, but style-objects need access to the styles-map
	// and CArchive::m_pDocument is not needed for serializing the following objects
	ar.m_pDocument = (CDocument*) pGrid->GetParam()->GetStylesMap();

	ROWCOL nRows, nCols;

	ar >> nRows;
	ar >> nCols;

	CGXRange r(range.top, range.left, range.top+nRows-1, range.left+nCols-1);

	if (!bIgnoreDiffRange && (r.bottom != range.bottom || r.right != range.right) &&
		!pGrid->OnPasteDiffRange())
	{
		bCanceled = TRUE;
	}
	else
	{
		CString s;
		s.LoadString(GX_IDM_PASTEDATA);
		pGrid->BeginTrans(s);

		CGXLongOperation theOp;
		theOp.SetStatusText(pGrid->m_pAppData->strmPastingData, FALSE);
		theOp.SetCanRollback(TRUE);
		// theOp.SetLockedState(TRUE);

		// Store and decativate current cell
		pGrid->TransferCurrentCell();

		CObArray* pCellsArray = NULL;

		ar >> pCellsArray;

		CObArray* pCells = pCellsArray;
		CObArray altCellsArray;

		if (r.bottom > pGrid->GetRowCount())
		{
			if ((pGrid->m_nClipboardFlags & GX_DNDNOAPPENDROWS) == 0 && pGrid->SetRowCount(r.bottom))
				; // ok
			else
			{
				r.bottom = pGrid->GetRowCount();
				// no of columns did not change -> can still use pCellsArray
			}
		}

		ROWCOL nColCount = pGrid->GetColCount();
		if (r.right > nColCount)
		{
			if ((pGrid->m_nClipboardFlags & GX_DNDNOAPPENDCOLS) == 0 && pGrid->SetColCount(r.right))
				; // ok
			else
			{
				// no of columns did change -> fill alternative cells array
				pCells = &altCellsArray;

				DWORD dwSrcIndex = 0, dwDestIndex = 0;
				for (ROWCOL nRow = r.top; nRow <= r.bottom; nRow++)
				{
					for (ROWCOL nCol = r.left; nCol <= r.right; nCol++)
					{
						if (dwSrcIndex >= (DWORD) pCellsArray->GetSize())
							break;

						if (nCol <= nColCount)
						{
							CGXStyle* pStyle = (CGXStyle*) pCellsArray->GetAt((int) dwSrcIndex);
							pCells->SetAtGrow((int) dwDestIndex++, pStyle);
						}

						dwSrcIndex++;
					}
				}

				r.right = nColCount;
			}
		}

		if (r.top <= pGrid->GetRowCount() && r.left <= pGrid->GetColCount())
			bCanceled = !pGrid->SetStyleRange(r, NULL, gxCopy, nValueType, pCells);
		else
			bCanceled = TRUE;

		// clean up
		if (pCellsArray)
		{
			for (int i = 0; i < pCellsArray->GetSize(); i++)
				delete pCellsArray->GetAt(i);
		}
		delete pCellsArray;

		bCanceled |= theOp.GetRollbackConfirmedState();
	}

	if (bCanceled)
		pGrid->Rollback();
	else
		pGrid->CommitTrans();

	ar.m_pDocument = pOldDocument;

	return !bCanceled;
}

