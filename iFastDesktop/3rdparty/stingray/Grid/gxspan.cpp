///////////////////////////////////////////////////////////////////////////////
// gxspan.cpp
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

// Headers

#ifdef _GXDLL
#undef AFXAPI_DATA
#define AFXAPI_DATA __based(__segname("_DATA"))
#endif

#ifndef _GXRESRC_H_
#include "grid\gxresrc.h"
#endif

#ifndef _GXEXT_H_
#include "grid\gxext.h"
#endif

#ifndef _GXCORE_H_
#include "grid\gxcore.h"
#endif

#ifndef _GXCTRL_H_
#include "grid\gxctrl.h"
#endif

#ifndef _GXSTYLES_H_
#include "grid\gxstyles.h"
#endif

#ifndef _GXDELAYR_H_
#include "grid\gxdelayr.h"
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXSPAN")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

// CObject RTTI

IMPLEMENT_DYNAMIC(CGXDWordArrayPtrArray, CPtrArray)
IMPLEMENT_SERIAL(CGXSpanCellPool, CObject, 1)

// Debug Info

class CGXSpanCellPoolImp: public CGXAbstractSpanCellPoolImp
{
public:
	virtual CGXSpanCellPool* CreateSpanCellPool();
	virtual CGXSpanCellPool* CreateSpanCellPool(const CGXSpanCellPool& src);
	virtual void CopySpanCellPool(CGXSpanCellPool& dest, const CGXSpanCellPool& src);
	virtual void InsertRows(CGXSpanCellPool* pPool, ROWCOL nRow, ROWCOL nCount);
	virtual void RemoveRows(CGXSpanCellPool* pPool, ROWCOL nFromRow, ROWCOL nToRow);
	virtual void MoveRows(CGXSpanCellPool* pPool, ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow);
	virtual void InsertCols(CGXSpanCellPool* pPool, ROWCOL nCol, ROWCOL nCount);
	virtual void RemoveCols(CGXSpanCellPool* pPool, ROWCOL nFromCol, ROWCOL nToCol);
	virtual void MoveCols(CGXSpanCellPool* pPool, ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nDestCol);
};

void AFXAPI CGXSpanCellPool::ImplementSpanCellPool()
{
	if (GXGetAppData()->m_pSpanCellPoolImp == NULL)
	{
		// QA: 31521 Removal from AutoDeletePtr
		//GXGetAppData()->AutoDeletePtr(GXGetAppData()->m_pSpanCellPoolImp = new CGXSpanCellPoolImp);
		GXGetAppData()->m_pSpanCellPoolImp = new CGXSpanCellPoolImp;
	}
}

CGXSpanCellPool* CGXSpanCellPoolImp::CreateSpanCellPool()
{
	return new CGXSpanCellPool;
}

void CGXSpanCellPoolImp::CopySpanCellPool(CGXSpanCellPool& dest, const CGXSpanCellPool& src)
{
	dest = src;
}

CGXSpanCellPool* CGXSpanCellPoolImp::CreateSpanCellPool(const CGXSpanCellPool& src)
{
	CGXSpanCellPool* pPool = new CGXSpanCellPool;
	*pPool = src;
	return pPool;
}

void CGXSpanCellPoolImp::InsertRows(CGXSpanCellPool* pPool, ROWCOL nRow, ROWCOL nCount)
{
	if (pPool)
		pPool->InsertRows(nRow, nCount);
}

void CGXSpanCellPoolImp::RemoveRows(CGXSpanCellPool* pPool, ROWCOL nFromRow, ROWCOL nToRow)
{
	if (pPool)
		pPool->RemoveRows(nFromRow, nToRow);
}

void CGXSpanCellPoolImp::MoveRows(CGXSpanCellPool* pPool, ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow)
{
	if (pPool)
		pPool->MoveRows(nFromRow, nToRow, nDestRow);
}

void CGXSpanCellPoolImp::InsertCols(CGXSpanCellPool* pPool, ROWCOL nCol, ROWCOL nCount)
{
	if (pPool)
		pPool->InsertCols(nCol, nCount);
}

void CGXSpanCellPoolImp::RemoveCols(CGXSpanCellPool* pPool, ROWCOL nFromCol, ROWCOL nToCol)
{
	if (pPool)
		pPool->RemoveCols(nFromCol, nToCol);
}

void CGXSpanCellPoolImp::MoveCols(CGXSpanCellPool* pPool, ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nDestCol)
{
	if (pPool)
		pPool->MoveCols(nFromCol, nToCol, nDestCol);
}


/////////////////////////////////////////////////////////////////////////////
// class CGXSpanCellPool

static BOOL GetSpanCellsRowColImp(ROWCOL nRow, ROWCOL nCol, CGXRange& rg, BOOL bRows, CGXDWordArrayPtrArray* pPtrArray);
static BOOL StoreSpanCellsRowColImp(ROWCOL nFromRow, ROWCOL nFromCol, ROWCOL nToRow, ROWCOL nToCol, BOOL bSet, CGXDWordArrayPtrArray* pPtrArray);

void CGXSpanCellPool::MakeEmpty()
{
	m_SpanCols.DeleteAll();
	m_SpanRows.DeleteAll();
}

void CGXSpanCellPool::InitFromRangeList(const CGXRangeList* pRangeList)
{							
	MakeEmpty();

	if (!pRangeList->IsEmpty())
	{
		CGXRange t;
		// check, if intersections with existing areas
		POSITION pos = pRangeList->GetHeadPosition();
		while (pos != NULL)
		{
			CGXRange& r = *pRangeList->GetNext(pos);

			if (!StoreSpanCellsRowCol(r.top, r.left, r.bottom, r.right, TRUE))
				break;
		}
	}
}

BOOL CGXSpanCellPool::GetSpanCellsRowCol(ROWCOL nRow, ROWCOL nCol, CGXRange& rg)
{
	if (nRow > INT_MAX || nCol > INT_MAX)
		return FALSE;

	BOOL b1 = GetSpanCellsRowColImp(nRow, nCol, rg, FALSE, &m_SpanCols);
	BOOL b2 = GetSpanCellsRowColImp(nRow, nCol, rg, TRUE, &m_SpanRows);

	return b1 || b2;
}

BOOL CGXSpanCellPool::StoreSpanCellsRowCol(ROWCOL nRow, ROWCOL nCol, ROWCOL nToRow, ROWCOL nToCol, BOOL bSet)
{
	if (nToRow > INT_MAX || nToCol > INT_MAX)
		return FALSE;

	TRY
	{
		BOOL b1 = StoreSpanCellsRowColImp(nRow, nCol, nToRow, nToCol, bSet, &m_SpanCols);

		// swap rows and cols
		BOOL b2 = StoreSpanCellsRowColImp(nCol, nRow, nToCol, nToRow, bSet, &m_SpanRows);

		return b1 || b2;
	}
	CATCH(CMemoryException, e)
	{
		GX_THROW_LAST
		return FALSE;
	}
	END_CATCH
}

void CGXSpanCellPool::Serialize(CArchive& ar)
{
	m_SpanCols.Serialize(ar);
	m_SpanRows.Serialize(ar);
}

CGXSpanCellPool& CGXSpanCellPool::operator=(const CGXSpanCellPool& pool)
{
	if(&pool == this)
		return *this;

	m_SpanRows = pool.m_SpanRows;
	m_SpanCols = pool.m_SpanCols;

	return *this;
}

/////////////////////////////////////////////////////////////////////////////
// Insert, Remove and Move Cells

// Warning: the following functions will only work if the
// spaned ranges don't span both rows and columns (especially covered cells)

void CGXSpanCellPool::InsertRows(ROWCOL nRow, ROWCOL nCount)
{
	m_SpanCols.InsertRows(nRow, nCount);
	m_SpanRows.InsertCols(nRow, nCount);
}

void CGXSpanCellPool::RemoveRows(ROWCOL nFromRow, ROWCOL nToRow)
{
	m_SpanCols.RemoveRows(nFromRow, nToRow);
	m_SpanRows.RemoveCols(nFromRow, nToRow);
}

void CGXSpanCellPool::MoveRows(ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow)
{
	m_SpanCols.MoveRows(nFromRow, nToRow, nDestRow);
	m_SpanRows.MoveCols(nFromRow, nToRow, nDestRow);
}

void CGXSpanCellPool::InsertCols(ROWCOL nCol, ROWCOL nCount)
{
	m_SpanCols.InsertCols(nCol, nCount);
	m_SpanRows.InsertRows(nCol, nCount);
}

void CGXSpanCellPool::RemoveCols(ROWCOL nFromCol, ROWCOL nToCol)
{
	m_SpanCols.RemoveCols(nFromCol, nToCol);
	m_SpanRows.RemoveRows(nFromCol, nToCol);
}

void CGXSpanCellPool::MoveCols(ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nDestCol)
{
	m_SpanCols.MoveCols(nFromCol, nToCol, nDestCol);
	m_SpanRows.MoveRows(nFromCol, nToCol, nDestCol);
}

/////////////////////////////////////////////////////////////////////////////
// static helper methods

static BOOL GetSpanCellsRowColImp(ROWCOL nRow, ROWCOL nCol, CGXRange& rg, BOOL bRows, CGXDWordArrayPtrArray* pPtrArray)
{
	int row, col;

	if (bRows)
	{
		// swap row and column
		row = (int) nCol;
		col = (int) nRow;
	}
	else
	{
		row = (int) nRow;
		col = (int) nCol;
	}

	CDWordArray* pDWordArray = NULL;

	if (row < pPtrArray->GetSize())
		pDWordArray = pPtrArray->GetAt(row);

	ROWCOL nSpan = GX_INVALID;

	// DWordArray members contains pointer to float cell
	// e.g. 0 0 0 0 4 4 4 4 0 0 10 10 10 ...
	if (pDWordArray && col < pDWordArray->GetSize())
		nSpan = pDWordArray->GetAt(col);
	else 
		nSpan = GX_INVALID;

	if (nSpan != GX_INVALID)
	{
		while (col < pDWordArray->GetSize()
			&& pDWordArray->GetAt(col) == nSpan)
			col++;

		if (bRows)
		{
			rg.top = nSpan;
			rg.bottom = (ROWCOL) col-1;
		}
		else
		{
			rg.left = nSpan;
			rg.right = (ROWCOL) col-1;
		}

		return TRUE;
	}

	return FALSE;
}

static BOOL StoreSpanCellsRowColImp(ROWCOL nFromRow, ROWCOL nFromCol, ROWCOL nToRow, ROWCOL nToCol, BOOL bSet, CGXDWordArrayPtrArray* pPtrArray)
{
	BOOL bDone = FALSE;

	if (bSet && nToCol == nFromCol)
		return FALSE;

	int col, row;

	for (ROWCOL nRow = nFromRow; nRow <= nToRow; nRow++)
	{
		col = (int) nFromCol;
		row = (int) nRow;

		CDWordArray* pDWordArray = NULL;

		if (row < pPtrArray->GetSize())
			pDWordArray = pPtrArray->GetAt(row);

		if (pDWordArray == NULL)
		{
			if (!bSet)
				continue;
			else
			{
				pDWordArray = new CDWordArray;
				pPtrArray->SetAtGrow(row, pDWordArray);
			}
		}

		ROWCOL nMergeCol = GX_INVALID;

		// DWordArray members contains pointer to float cell
		// e.g. 0 0 0 0 4 4 4 4 0 0 10 10 10 ...
		if (pDWordArray && col < pDWordArray->GetSize())
			nMergeCol = pDWordArray->GetAt(col);
		else
			nMergeCol = GX_INVALID;

		if (!bSet)
		{
			// Remove existing area
			if (nMergeCol != GX_INVALID)
			{
				while (col < pDWordArray->GetSize()
					&& pDWordArray->GetAt(col) == nMergeCol)
					pDWordArray->SetAt(col++, GX_INVALID);

				bDone = TRUE;
			}
		}
		else
		{
			// add new area
			if (nMergeCol != GX_INVALID)
				ASSERT(nMergeCol == nFromCol);

			while (pDWordArray->GetSize() < col)
				pDWordArray->SetAtGrow(pDWordArray->GetSize(), GX_INVALID);

			while (col <= (int) nToCol)
				pDWordArray->SetAtGrow(col++, nFromCol);

			while (col < pDWordArray->GetSize()
				&& pDWordArray->GetAt(col) == nMergeCol)
				pDWordArray->SetAt(col++, GX_INVALID);

			bDone = TRUE;
		}
	}

	return bDone;
}

/////////////////////////////////////////////////////////////////////////////
// class CGXDWordArrayPtrArray

CGXDWordArrayPtrArray::~CGXDWordArrayPtrArray()
{
	DeleteAll();
}

void CGXDWordArrayPtrArray::DeleteAt(int nIndex, int nCount)
{
	int nUpper = min(int(GetUpperBound()), nIndex+nCount-1);
	if (nUpper >= nIndex)
	{
		for (int index = nIndex; index <= nUpper; index++)
			delete GetAt(index);

		RemoveAt(nIndex, nUpper-nIndex+1);
	}
}

void CGXDWordArrayPtrArray::DeleteAll()
{
	for (int index = 0; index <= GetUpperBound(); index++)
		delete GetAt(index);

	RemoveAll();
}

void CGXDWordArrayPtrArray::Move(int nIndex, int nCount, int nDest)
{
	if (nDest == nIndex || nCount == 0
		|| GetUpperBound() < nIndex && GetUpperBound() < nDest)
		return;
	else if (nDest < nIndex)
		nIndex += nCount;
	else if (nDest > nIndex)
		nDest += nCount;

	InsertAt(nDest, NULL, nCount);
	for (int n = 0; nIndex+n <= GetUpperBound() && n < nCount; n++)
	{
		if (GetAt(nIndex+n))
			SetAt(nDest+n, GetAt(nIndex+n));
	}

	if (nIndex <= GetUpperBound())
		RemoveAt(nIndex, min(nCount, GetUpperBound()-nIndex+1));
}

void CGXDWordArrayPtrArray::Serialize(CArchive& ar)
{
	// Serializes only existing elements,
	// e.g.  1 xxx 2 xxx 3 xxx 7 xxx 22 xxx DWORD_MAX,
	// where xxx is a CDWordArray object and DWORD_MAX identifies the end of serialization

	static const WORD wVersion = 1;
	WORD wActualVersion = wVersion;

	ASSERT_VALID( this );

	if (ar.IsStoring())
	{
		ar << wVersion;
	}
	else
	{
		// Check for version first
		ar >> wActualVersion;
		if( wActualVersion != wVersion )
		{
			// Wrong version
#ifdef _DEBUG
			TRACE0( "Incompatible format while reading CGXDWordArrayPtrArray " );
			TRACE2("in %s at line %d\n", THIS_FILE, __LINE__);
			ASSERT(0);
			// ASSERTION-> Incompatible format while reading CGXDWordArrayPtrArray object ->END
#endif
			AfxThrowArchiveException(CArchiveException::badSchema);
			return;
		}
	}

	const DWORD dwTerm = 0xFFFFFFFF;

	if (ar.IsStoring())
	{
		// storing

		DWORD dwSize = (DWORD) GetSize();
		ar << dwSize;
		for (int index = 0; index <= GetUpperBound(); index++)
		{
			CDWordArray* pDWordArrayPtrArray = GetAt(index);
			if (pDWordArrayPtrArray)
			{
				ar << (DWORD) index;
				pDWordArrayPtrArray->Serialize(ar);
			}
		}
		ar << dwTerm;
	}
	else
	{
		// loading

		DeleteAll();

		DWORD dwSize;
		ar >> dwSize;

		SetSize((int) dwSize);

		DWORD dwIndex;
		ar >> dwIndex;

		while (dwIndex != dwTerm)
		{
			CDWordArray* pDWordArrayPtrArray = new CDWordArray;
			pDWordArrayPtrArray->Serialize(ar);

			SetAt((int) dwIndex, pDWordArrayPtrArray);

			// Next id
			ar >> dwIndex;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// Insert, Remove and Move Cells

BOOL CGXDWordArrayPtrArray::InsertRows(ROWCOL nRow, ROWCOL nCount)
{
	if (this == NULL || GetSize() == 0)
		return FALSE;

	if (nRow+nCount > INT_MAX)
		return FALSE;

	int row = (int) nRow;
	int count = (int) nCount;

	if (row <= GetUpperBound())
		InsertAt(row, NULL, count);

	return TRUE;
}

BOOL CGXDWordArrayPtrArray::RemoveRows(ROWCOL nFromRow, ROWCOL nToRow)
{
	if (this == NULL || GetSize() == 0 || nFromRow > (ROWCOL) GetUpperBound())
		return FALSE;

	nToRow = min(nToRow, (ROWCOL) GetUpperBound());

	int row = (int) nFromRow;
	int count = (int) (nToRow-nFromRow+1);

	DeleteAt(row, count);

	return TRUE;
}


BOOL CGXDWordArrayPtrArray::MoveRows(ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow)
{
	if (this == NULL || GetSize() == 0)
		return FALSE;

	if (!(nFromRow <= INT_MAX && nToRow <= INT_MAX && nDestRow <= INT_MAX))
		return FALSE;

	int row = (int) nFromRow;
	int count = (int) (nToRow-nFromRow+1);
	int dest = (int) nDestRow;

	Move(row, count, dest);

	return TRUE;
}

BOOL CGXDWordArrayPtrArray::InsertCols(ROWCOL nCol, ROWCOL nCount)
{
	if (this == NULL || GetSize() == 0)
		return FALSE;

	if (nCol+nCount > INT_MAX)
		return FALSE;

	int col = (int) nCol;
	int count = (int) nCount;

	// insert columns for each row
	for (int row = 0; row <= GetUpperBound(); row++)
	{
		if (GetAt(row))
		{
			if (col <= GetAt(row)->GetUpperBound())
				GetAt(row)->InsertAt(col, 0, count);
		}
	}

	return TRUE;
}

BOOL CGXDWordArrayPtrArray::RemoveCols(ROWCOL nFromCol, ROWCOL nToCol)
{
	if (this == NULL || GetSize() == 0)
		return FALSE;

	// delete columns for each row
	for (int row = 0; row <= GetUpperBound(); row++)
	{
		if (GetAt(row) && nFromCol < (ROWCOL) GetAt(row)->GetSize())
		{
			int col = (int) nFromCol;
			int count = (int) (min(nToCol, (ROWCOL) GetAt(row)->GetUpperBound())-nFromCol+1);

			GetAt(row)->RemoveAt(col, count);
		}
	}

	return TRUE;
}

BOOL CGXDWordArrayPtrArray::MoveCols(ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nDestCol)
{
	if (this == NULL || GetSize() == 0)
		return FALSE;

	if (!(nFromCol <= INT_MAX && nToCol <= INT_MAX && nDestCol <= INT_MAX))
		return FALSE;

	int nIndex, nCount, nDest;

	// move columns for each row
	for (int row = 0; row <= GetUpperBound(); row++)
	{
		CDWordArray* pDWordArray = GetAt(row);
		if (pDWordArray)
		{
			nIndex = (int) nFromCol;
			nCount = (int) (nToCol-nFromCol+1);
			nDest = (int) nDestCol;

			if (nDest == nIndex || nCount == 0
				|| pDWordArray->GetUpperBound() < nIndex && pDWordArray->GetUpperBound() < nDest)
				continue;
			else if (nDest < nIndex)
				nIndex += nCount;
			else if (nDest > nIndex)
				nDest += nCount;

			pDWordArray->InsertAt(nDest, NULL, nCount);
			for (int n = 0; nIndex+n <= GetUpperBound() && n < nCount; n++)
			{
				if (pDWordArray->GetAt(nIndex+n))
					pDWordArray->SetAt(nDest+n, pDWordArray->GetAt(nIndex+n));
			}

			if (nIndex <= pDWordArray->GetUpperBound())
				pDWordArray->RemoveAt(nIndex, min(nCount, pDWordArray->GetUpperBound()-nIndex+1));
		}
	}

	return TRUE;
}

CGXDWordArrayPtrArray& CGXDWordArrayPtrArray::operator=(const CGXDWordArrayPtrArray& ar)
{
	if(&ar == this)
		return *this;
	
	DeleteAll();
	
	for (int index = 0; index <= ar.GetUpperBound(); index++)
	{
		CDWordArray* pDWordArrayPtrArray = ar.GetAt(index);
		
		//allocate a new array and copy the elements
		CDWordArray* pNewWordArray = new CDWordArray();
		
		if(	pDWordArrayPtrArray)
		{
			for (int innerindex = 0; innerindex <= pDWordArrayPtrArray->GetUpperBound(); innerindex++)
			{
				pNewWordArray->SetAtGrow(innerindex, pDWordArrayPtrArray->GetAt(innerindex)); 
			}
		}
		
		SetAtGrow(index, pNewWordArray);
	}
	
	return *this;
}
