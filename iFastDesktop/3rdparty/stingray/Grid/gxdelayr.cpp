///////////////////////////////////////////////////////////////////////////////
// gxdelayr.cpp : Lazy evaluation support for floating and merge cells 
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

#ifndef _GXDELAYR_H_
#include "grid\gxdelayr.h"
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXDELAYR")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// CObject RTTI

IMPLEMENT_SERIAL(CGXDelayedRange, CObject, 1)
IMPLEMENT_SERIAL(CGXDelayedRangePool, CObject, 1)

// Debug Info

class CGXDelayedRangePoolImp: public CGXAbstractDelayedRangePoolImp
{
public:
	virtual CGXDelayedRangePool* CreateDelayedRangePool();
	virtual void CopyDelayedRangePool(CGXDelayedRangePool& dest, const CGXDelayedRangePool& src);
	virtual CGXDelayedRangePool* CreateDelayedRangePool(const CGXDelayedRangePool& src);
};

void AFXAPI CGXDelayedRangePool::ImplementDelayedRangePool()
{
	if (GXGetAppData()->m_pDelayedRangePoolImp == NULL)
	{
		// QA: 31521 Removal from AutoDeletePtr
		//GXGetAppData()->AutoDeletePtr(GXGetAppData()->m_pDelayedRangePoolImp = new CGXDelayedRangePoolImp);
		GXGetAppData()->m_pDelayedRangePoolImp = new CGXDelayedRangePoolImp;
	}
}

CGXDelayedRangePool* CGXDelayedRangePoolImp::CreateDelayedRangePool()
{
	return new CGXDelayedRangePool;
}

void CGXDelayedRangePoolImp::CopyDelayedRangePool(CGXDelayedRangePool& dest, const CGXDelayedRangePool& src)
{
	dest = src;
}


CGXDelayedRangePool* CGXDelayedRangePoolImp::CreateDelayedRangePool(const CGXDelayedRangePool& src)
{
	CGXDelayedRangePool* pPool = new CGXDelayedRangePool;
	*pPool = src;
	return pPool;
}

/////////////////////////////////////////////////////////////////////
// class CGXDelayedRange

CGXDelayedRange::CGXDelayedRange()
	: m_bResolved(FALSE)
{
}

void CGXDelayedRange::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
		ar << m_range;
	else
		ar >> m_range;

	m_awFirstRow.Serialize(ar);
	m_awLastRow.Serialize(ar);
}

void CGXDelayedRange::operator=(const CGXDelayedRange& other)
{
	m_bResolved = other.m_bResolved;
	m_range = other.m_range;
	m_awFirstRow.InsertAt(0, (CDWordArray*) &other.m_awFirstRow);
	m_awLastRow.InsertAt(0, (CDWordArray*) &other.m_awFirstRow);
}

void CGXDelayedRange::SetEmpty()
{
	m_awFirstRow.RemoveAll();
	m_awLastRow.RemoveAll();
	m_bResolved = TRUE;
}

// ResolveRange
//
// Determins the range of cells which are marked for evaluation
// and marks them as evaluated so that they will not be evaluated
// again.
//

BOOL CGXDelayedRange::ResolveRange(CGXRange& rg)
{
	BOOL bFound = FALSE;
	int n;
	for (n = 0; !bFound && n < m_awFirstRow.GetSize(); n++)
	{
		if (m_awLastRow[n]+1  < rg.top)
			continue;

		if (m_awFirstRow[n] > rg.bottom+1)
			break;

		if (m_awFirstRow[n] <= rg.top && m_awLastRow[n] >= rg.bottom)
		{
			// interval is alrady found
			return FALSE;
		}
		else if (m_awFirstRow[n] <= rg.top && m_awLastRow[n] <= rg.bottom)
		{
			bFound = TRUE;
			rg.top = m_awLastRow[n]+1;
			m_awLastRow[n] = rg.bottom;
		}
		else if (m_awFirstRow[n] >= rg.top && m_awLastRow[n] >= rg.bottom)
		{
			bFound = TRUE;
			rg.bottom = m_awFirstRow[n]-1;
			m_awFirstRow[n] = rg.top;
		}
		else if (m_awFirstRow[n] >= rg.top && m_awLastRow[n] <= rg.bottom)
		{
			bFound = TRUE;
			m_awFirstRow[n] = rg.top;
			m_awLastRow[n] = rg.bottom;
		}
	}

	if (!bFound)
	{
		TRY
		{
			if (n < m_awFirstRow.GetSize())
			{
				m_awFirstRow.InsertAt(n, rg.top);
				m_awLastRow.InsertAt(n, rg.bottom);
			}
			else
			{
				m_awFirstRow.SetAtGrow(n, rg.top);
				m_awLastRow.SetAtGrow(n, rg.bottom);
			}
		}
		CATCH(CMemoryException, e)
		{
			// Free some memory
			SetEmpty();
			GX_THROW_LAST
		}
		END_CATCH
	}

	for (n = 0; n+1 < m_awFirstRow.GetSize(); n++)
	{
		if (m_awLastRow[n] >= m_awFirstRow[n+1])
		{
			m_awLastRow[n] = m_awLastRow[n+1];

			m_awLastRow.RemoveAt(n+1);
			m_awFirstRow.RemoveAt(n+1);
		}
	}

	if (m_awFirstRow.GetSize() == 1
		&& m_awFirstRow[0] == m_range.top
		&& m_awLastRow[0] >= m_range.bottom)
	{
		// TRACE("Resolved Range: (%d, top %lu, left %lu, bottom %lu, right %lu)\n", m_range);
		SetEmpty();
	}
	else
	{
		/*
		TRACE("Intervals: (%d, top %lu, left %lu, bottom %lu, right %lu)  ", m_range);
		for (n = 0; n < m_awFirstRow.GetSize(); n++)
		{
			TRACE("%d-%d ", m_awFirstRow[n], m_awLastRow[n]);
		}
		TRACE("\n");
		*/
		;
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////
// class CGXDelayedRangePool

CGXDelayedRangePool::CGXDelayedRangePool()
{
}

void CGXDelayedRangePool::Serialize(CArchive& ar)
{
	m_argDelayed.Serialize(ar);
}

CGXDelayedRangePool::~CGXDelayedRangePool()
{
	MakeEmpty();
}

void CGXDelayedRangePool::MakeEmpty()
{
	// Clean up array
	int nCount = (int)m_argDelayed.GetSize();

	for (int i = 0; i < nCount; i++)
	{
		CGXDelayedRange* prgDelayed = (CGXDelayedRange*) m_argDelayed[i];
		delete prgDelayed;
	}

	m_argDelayed.RemoveAll();
}

void CGXDelayedRangePool::CleanUp()
{
	// Clean up array
	int nCount = (int)m_argDelayed.GetSize();

	for (int i = nCount-1; i >= 0; i--)
	{
		CGXDelayedRange* prgDelayed = (CGXDelayedRange*) m_argDelayed[i];

		if (prgDelayed->m_bResolved)
		{
			delete prgDelayed;
			m_argDelayed.RemoveAt(i);
		}
	}
}

void CGXDelayedRangePool::DelayRange(const CGXRange& range)
{
	CGXDelayedRange* prgDelayed = NULL;
	int nSize = (int)m_argDelayed.GetSize();
	int nLastResolved = -1;

	for (int i = 0; i < nSize; i++)
	{
		prgDelayed = (CGXDelayedRange*) m_argDelayed[i];

		if (prgDelayed->m_bResolved)
		{
			nLastResolved = i;
			continue;
		}

		// Mark those ranges as resolved which are only a subset of the new range
		// to be added
		if (range.IsCellInRange(prgDelayed->m_range.top, prgDelayed->m_range.left)
			&& range.IsCellInRange(prgDelayed->m_range.bottom, prgDelayed->m_range.right))
		{
			// TRACE("Delete Range: (%d, top %lu, left %lu, bottom %lu, right %lu)\n", prgDelayed->m_range);
			prgDelayed->SetEmpty();
			if (nLastResolved == -1)
				nLastResolved = i;
		}

		// check if we can extend an existing range
		else if (prgDelayed->m_awFirstRow.GetSize() == 0)
		{
			if (prgDelayed->m_range.right == range.left-1)
				prgDelayed->m_range.right = range.right;

			if (prgDelayed->m_range.bottom == range.top-1)
				prgDelayed->m_range.bottom = range.bottom;

			if (prgDelayed->m_range.IsCellInRange(range.top, range.left)
				&& prgDelayed->m_range.IsCellInRange(range.bottom, range.right))
				return;
		}
	}

	// Add range to be evaluated
	if (nLastResolved == -1)
	{
		prgDelayed = NULL;
		TRY
		{
			prgDelayed = new CGXDelayedRange;
			m_argDelayed.InsertAt(0, prgDelayed);
		}
		CATCH(CMemoryException, e)
		{
			if (prgDelayed)
				delete prgDelayed;
			
			GX_THROW_LAST
		}
		END_CATCH
	}
	else
		prgDelayed = (CGXDelayedRange*) m_argDelayed[nLastResolved];

	prgDelayed->m_bResolved = FALSE;
	prgDelayed->m_range = range;

	// TRACE("Added Range: (%d, top %lu, left %lu, bottom %lu, right %lu)\n", prgDelayed->m_range);
}

void CGXDelayedRangePool::SplitDelayedRange(const CGXRange& range)
{
	int nCount = (int)m_argDelayed.GetSize();

	for (int i = 0; i < nCount; i++)
	{
		CGXDelayedRange* prgDelayed = (CGXDelayedRange*) m_argDelayed[i];
		CGXRange rgIntersect;

		if (!prgDelayed->m_bResolved && rgIntersect.IntersectRange(prgDelayed->m_range, range))
		{
			if (prgDelayed->m_range.left < rgIntersect.left)
			{
				CGXDelayedRange* prgLeftDelayed = NULL;
				TRY
				{
					prgLeftDelayed = new CGXDelayedRange;
					*prgLeftDelayed = *prgDelayed;
					prgLeftDelayed->m_range.right = rgIntersect.left-1;
					prgDelayed->m_range.left = rgIntersect.left;
					m_argDelayed.SetAtGrow(
						m_argDelayed.GetSize(), prgLeftDelayed);
				}
				CATCH(CMemoryException, e)
				{
					delete prgLeftDelayed;

					GX_THROW_LAST
				}
				END_CATCH

				//TRACE("Split left Range: left (%d, top %lu, left %lu, bottom %lu, right %lu)", prgLeftDelayed->m_range);
				//TRACE(" right (%d, top %lu, left %lu, bottom %lu, right %lu)\n", prgDelayed->m_range);
			}

			if (prgDelayed->m_range.right > rgIntersect.right)
			{
				CGXDelayedRange* prgRightDelayed = NULL;
				TRY
				{
					prgRightDelayed = new CGXDelayedRange;
					*prgRightDelayed= *prgDelayed;
					prgRightDelayed->m_range.left = rgIntersect.right+1;
					prgDelayed->m_range.right = rgIntersect.right;
					m_argDelayed.SetAtGrow(
						m_argDelayed.GetSize(), prgRightDelayed);
				}
				CATCH(CMemoryException, e)
				{
					delete prgRightDelayed;

					GX_THROW_LAST
				}
				END_CATCH

				//TRACE("Split right Range: left (%d, top %lu, left %lu, bottom %lu, right %lu)", prgDelayed->m_range);
				//TRACE("right (%d, top %lu, left %lu, bottom %lu, right %lu)\n", prgRightDelayed->m_range);
			}
		}
	}
}

BOOL CGXDelayedRangePool::EvalRows(const CGXRange& range, CDWordArray &dwColStart, CDWordArray &dwColEnd)
{
	BOOL bFound = FALSE;

	if (range.bottom < range.top || range.right < range.left)
		return FALSE;

	TRY
	{
		dwColStart.RemoveAll();
		dwColEnd.RemoveAll();
		dwColStart.InsertAt(0, GX_INVALID, (int) range.GetHeight());
		dwColEnd.InsertAt(0, 0, (int) range.GetHeight());
	}
	CATCH(CMemoryException, e)
	{
		GX_THROW_LAST
		return FALSE;
	}
	END_CATCH

	// Split ranges which are a superset of range
	SplitDelayedRange(range);

	// Check each range and assign column ids to dwColStart[i] and dwColEnd[i]
	int nCount = (int)m_argDelayed.GetSize();
	for (int i = 0; i < nCount; i++)
	{
		CGXDelayedRange* prgDelayed = (CGXDelayedRange*) m_argDelayed[i];
		CGXRange rg;

		if (!prgDelayed->m_bResolved && rg.IntersectRange(prgDelayed->m_range, range))
		{
			if (prgDelayed->ResolveRange(rg))
			{
				ROWCOL dwFirstRow = max(rg.top, prgDelayed->m_range.top);
				ROWCOL dwLastRow = min(rg.bottom, prgDelayed->m_range.bottom);
				ROWCOL nFirstCol = prgDelayed->m_range.left;
				ROWCOL nLastCol = prgDelayed->m_range.right;

				// TRACE("Row1 = %d, nRow2 = %d\n", nIndexFirstRow, nIndexLastRow);

				int nFirstRow = (int) (dwFirstRow - range.top);
				int nLastRow = (int) (dwLastRow - range.top);

				for (int nIndex = nFirstRow; nIndex <= nLastRow; nIndex++)
				{
					if (dwColStart[nIndex] == GX_INVALID)
					{
						dwColStart[nIndex] = nFirstCol;
						dwColEnd[nIndex] = nLastCol;
					}
					else
					{
						dwColStart[nIndex] = min(dwColStart[nIndex], nFirstCol);
						dwColEnd[nIndex] = max(dwColEnd[nIndex], nLastCol);
					}
				}

				bFound = TRUE;
			}
		}
	}

	if (bFound)
		CleanUp();  // delete resolved ranges

	return bFound;
}

void CGXDelayedRangePool::SetRowCount(ROWCOL nMaxRow)
{
	int nCount = (int)m_argDelayed.GetSize();
	for (int i = 0; i < nCount; i++)
	{
		CGXDelayedRange* prgDelayed = (CGXDelayedRange*) m_argDelayed[i];

		prgDelayed->m_range.top = min(prgDelayed->m_range.top, nMaxRow);
		prgDelayed->m_range.bottom = min(prgDelayed->m_range.bottom, nMaxRow);
	}
}

void CGXDelayedRangePool::SetColCount(ROWCOL nMaxCol)
{
	int nCount = (int)m_argDelayed.GetSize();
	for (int i = 0; i < nCount; i++)
	{
		CGXDelayedRange* prgDelayed = (CGXDelayedRange*) m_argDelayed[i];

		prgDelayed->m_range.left = min(prgDelayed->m_range.left, nMaxCol);
		prgDelayed->m_range.right = min(prgDelayed->m_range.right, nMaxCol);
	}
}

CGXDelayedRangePool& CGXDelayedRangePool::operator=(const CGXDelayedRangePool& pool)
{
	if (&pool == this) 
		return *this;

	CleanUp();
	
	int nCount = (int)pool.m_argDelayed.GetSize();

	for (int i = 0; i < nCount; i++)
	{
		CGXDelayedRange* p = new CGXDelayedRange(); 
		*p = *(CGXDelayedRange*) pool.m_argDelayed[i];
		m_argDelayed.SetAtGrow(i, p ); 
	}
	
	return *this;
}

