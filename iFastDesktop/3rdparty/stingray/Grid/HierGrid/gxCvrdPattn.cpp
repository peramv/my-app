///////////////////////////////////////////////////////////////////////////////
// gxVcrdPattn.cpp : implementation file
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


#define _OG_EXPORT_IMPL

#include "stdafx.h"

#ifdef _GXDLL
#undef AFXAPI_DATA
#define AFXAPI_DATA __based(__segname("_DATA"))
#endif

#ifndef _GX_COVERED_PATTERN
#include "grid\HierGrid\gxCvrdPattn.h"
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_PMCTRL")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

#ifdef TICKCOUNT
#define _TC_(f) f
#else
#define _TC_(f)
#endif

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

ROWCOL CGXCoveredCellPatternMap::GetEffectiveColCount() const
{
	return m_nEffectiveColCount + m_nRowHeaderWidth + m_nPMButtonCellWidth;
}

void CGXCoveredCellPatternMap::SetColCount(ROWCOL nCols)
{
	m_nCols = nCols;	
	m_colWidths.SetSize(nCols);
	if(!m_rowBreaks.GetSize())
		m_rowBreaks.SetSize(1);
	if(m_rowBreaks.GetSize() == 1)
		m_rowBreaks.SetAt(0, nCols-1);

	for(ROWCOL i=0; i<m_nCols; i++)
	{
		m_colWidths.SetAt(i, m_nDefaultCellWidth);
	}
	CalcColCount();
}

int CGXCoveredCellPatternMap::GetColCount() const
{
	return m_nCols;
}

void CGXCoveredCellPatternMap::InsertCols(ROWCOL nCol, ROWCOL nCount)
{
	m_nCols += nCount;
	// Adjust array widths.
	m_colWidths.InsertAt(nCol-1, m_nDefaultCellWidth, nCount);
	// Adjust array breaks.
	if(!m_rowBreaks.GetSize())
		m_rowBreaks.SetSize(1);

	if(!m_indentWidths.GetSize())
		m_indentWidths.SetSize(1);

	if(m_nBreaks == 1)
	{
		m_rowBreaks.SetAt(0, m_nCols-1);
		m_indentWidths.SetAt(0, 0);
	}
	else
	{
		for(ROWCOL i = 0; i<m_nBreaks; i++)
		{
			long nBreak;
			nBreak = (long)m_rowBreaks.GetAt(i);
			if(nBreak >= (long)(nCol-1))
				m_rowBreaks.SetAt(i, nBreak+nCount);
		}
	}
	// Recalculate the effective col count.
	CalcColCount();
}

void CGXCoveredCellPatternMap::RemoveCols(ROWCOL nCol, ROWCOL nCount)
{
	ASSERT(m_nCols >= nCount);
	m_nCols -= nCount;
	// Adjust array widths.
	m_colWidths.RemoveAt(nCol-1, nCount);
	// Adjust breaks array.
	// Complexitiy is due to the removed columns possibly being spread out between 
	// rows in the row-breaks-array.
	if(m_nBreaks != 0)
	{
		ROWCOL nToBeRemoved = nCount;
		ROWCOL nRemoveAt = nCol-1;	// 0 based.
		long nPrevRowBreak = -1;	// 0 based 
		long nCurrentRowBreak;	// 0 based.
		ROWCOL nCurrentRowSize;
		
		for(ROWCOL i = 0; i<m_nBreaks; i++)
		{
			// If the removed columns affect the bounds of this logical row.
			if((nCurrentRowBreak = (long)m_rowBreaks.GetAt(i)) >= (long)nRemoveAt)
			{
				// If there are more columns, yet to be removed from the break-array.
				if(nToBeRemoved)
				{
					nCurrentRowSize = nCurrentRowBreak - nPrevRowBreak;
					// If the columns to be removed fall beyond this logical row.
					if((nRemoveAt + nToBeRemoved - 1) > (ROWCOL)nCurrentRowBreak)
					{
						int nRemoveInThisRow = nCurrentRowBreak - nRemoveAt + 1;
						nToBeRemoved -= nRemoveInThisRow;
						// Remove only those columns that are within this logical row.
						m_rowBreaks.SetAt(i, nCurrentRowBreak-(nCount-nToBeRemoved));
						nRemoveAt = nCurrentRowBreak+1;
					}
					// The columns to be removed fall within this logical range.
					else
					{
						m_rowBreaks.SetAt(i, nCurrentRowBreak - nCount);
						nToBeRemoved = 0;
					}
				}
				// Columns were removed in the logical rows above the current row.
				// So just adjust the break index.
				else
					m_rowBreaks.SetAt(i, nCurrentRowBreak-nCount);
			}
			nPrevRowBreak = nCurrentRowBreak;
		}
	}
	// Recalculate the effective col count.
	CalcColCount();
}

void CGXCoveredCellPatternMap::SetColWidths(CDWordArray* pArrayWidths)
{
	ASSERT((ROWCOL)pArrayWidths->GetSize() == m_nCols);
	for(ROWCOL i=0; i<m_nCols; i++)
	{
		m_colWidths.SetAt(i, pArrayWidths->GetAt(i));
	}
	CalcColCount();
}

void CGXCoveredCellPatternMap::SetRowBreaks(CDWordArray* pArrayBreaks, CWordArray* panIndentWidths /*=NULL*/)
{
	m_nBreaks = (DWORD)pArrayBreaks->GetSize();
	m_rowBreaks.RemoveAll();
	m_rowBreaks.Copy(*pArrayBreaks);
	m_indentWidths.RemoveAll();
	if(panIndentWidths)
		m_indentWidths.Copy(*panIndentWidths);
	else
		m_indentWidths.InsertAt(0, 0, m_nBreaks);
	ASSERT(pArrayBreaks->GetAt(m_nBreaks-1) == m_nCols-1);
	CalcColCount();
}

const CDWordArray* CGXCoveredCellPatternMap::GetRowBreaks() const
{
	return &m_rowBreaks;	
}

void CGXCoveredCellPatternMap::CalcColCount()
{
	// Calculate effective col counts...
	long nCur = 0;
	int nGreatestColCount = 0;
	for(int i=0; i<m_rowBreaks.GetSize(); i++)
	{
		int nColCount = 0;
		nColCount += m_indentWidths.GetAt(i);
		for(;nCur<=(long)m_rowBreaks.GetAt(i); nCur++)
		{
			nColCount += m_colWidths.GetAt(nCur);			
		}
		nGreatestColCount = nGreatestColCount > nColCount ? nGreatestColCount : nColCount;
	}
	m_nEffectiveColCount = nGreatestColCount;
}

CGXCoveredCellPatternMap::CGXCoveredCellPatternMap()
{
	m_nBreaks = 1;
//	m_rowBreaks.SetSize(1);
//	m_rowBreaks.SetAt(0,0);
	m_nRowHeaderWidth = 0;
	m_nCols = 0;
	m_nEffectiveColCount = 0;
	m_bIsHeaders = 1;
	m_nPMButtonCellWidth = 4;
	m_nDefaultCellWidth = 15;
	m_wChildIndentWidth = 0;
	m_nCellWidthPrecision = 568; // In Device Points. Equal to 4 device pixels
}



ROWCOL CGXCoveredCellPatternMap::GetRowSpan()
{
	return m_nBreaks*2;	// One extra row for every row to host child grid.
}

CGXRange* CGXCoveredCellPatternMap::GetSpanCellsRowCol(ROWCOL nRow, ROWCOL nCol, CGXRange & range, ROWCOL* nPatternCol)
{
	ROWCOL nColOrig = nCol;
	ROWCOL npRow = (nRow-1) % (m_nBreaks*2);
	// nCol is part of the column header...
	if(nCol <= m_nRowHeaderWidth)
	{
		ROWCOL nTopRow = (((nRow-1) / (m_nBreaks*2)) * (m_nBreaks*2)) + 1;
		ROWCOL nBottomRow = nTopRow + ((m_nBreaks*2) - 1);
		*nPatternCol = GX_INVALID;
		return &range.SetCells(nTopRow, 1, nBottomRow, m_nRowHeaderWidth);
	}

	nCol -= m_nRowHeaderWidth;

	if(nCol <= m_nPMButtonCellWidth)
	{
		*nPatternCol = GX_INVALID;
		ROWCOL nTopRow = (nRow % 2) ? nRow : nRow-1;	// The plus/minus button cell covers both the parent row and the child grid row.
		return &range.SetCells(nTopRow, m_nRowHeaderWidth+1, nTopRow+1, m_nRowHeaderWidth+m_nPMButtonCellWidth);
	}

	nCol -= m_nPMButtonCellWidth;

	if((npRow % 2) == 1)	// Means row containing the child grid.
	{
		*nPatternCol = GX_INVALID;
		if(nCol <= m_wChildIndentWidth)
			return &range.SetCells(nRow, m_nRowHeaderWidth+m_nPMButtonCellWidth+1, nRow, m_nRowHeaderWidth+m_nPMButtonCellWidth+m_wChildIndentWidth);
		return &range.SetCells(nRow, m_nRowHeaderWidth+m_nPMButtonCellWidth+m_wChildIndentWidth+1, nRow, GetEffectiveColCount());
	}

	npRow = (npRow / 2);	// Adjust npRow such that resultant npRow is irrespective of the child grid rows.

	// Check for indents
	
	if(nCol <= m_indentWidths.GetAt(npRow))
	{
		*nPatternCol = GX_INVALID;
		ROWCOL nLeftCol = m_nRowHeaderWidth+m_nPMButtonCellWidth;
		return &range.SetCells(nRow, nLeftCol+1, nRow, nLeftCol+m_indentWidths.GetAt(npRow));
	}
	else
		nCol -= m_indentWidths.GetAt(npRow);


	ROWCOL nFromCol=1, nToCol;
	long iWidth;
	if(npRow == 0)
		iWidth = 0;
	else 
	{
		iWidth = (long)m_rowBreaks.GetAt(npRow-1); 
		if(iWidth == (long)m_rowBreaks.GetAt(npRow))	// No cols in this row
		{
			(*nPatternCol) = GX_INVALID;		// not part of the pattern...
			return &range.SetCells(nRow, 1+m_nRowHeaderWidth+m_nPMButtonCellWidth+m_indentWidths.GetAt(npRow), nRow, GetEffectiveColCount());
		}
		iWidth++;	// Start of the next row...
	}
	nToCol = m_colWidths.GetAt(iWidth);
	while(nCol > nToCol && iWidth < (long)m_rowBreaks.GetAt(npRow))
	{
		nFromCol += m_colWidths.GetAt(iWidth);
		iWidth++;
		nToCol += m_colWidths.GetAt(iWidth);
	}
	if(nCol > nToCol)
	{
		(*nPatternCol) = GX_INVALID;		// not part of the pattern...
		return &range.SetCells(nRow, nToCol+1+m_nRowHeaderWidth+m_nPMButtonCellWidth+m_indentWidths.GetAt(npRow), nRow, max(nColOrig, GetEffectiveColCount()));
	}
	(*nPatternCol) = iWidth+1;		// iWidth is 0 based and nPatternCol is 1 based...
	return &range.SetCells(nRow, nFromCol+m_nRowHeaderWidth+m_nPMButtonCellWidth+m_indentWidths.GetAt(npRow), nRow, nToCol+m_nRowHeaderWidth+m_nPMButtonCellWidth+m_indentWidths.GetAt(npRow));
}

BOOL CGXCoveredCellPatternMap::GetAbsRangeFromPatternCell(ROWCOL nLogRow, ROWCOL nLogCol, ROWCOL& nAbsRow, ROWCOL& nAbsLeftCol, CGXRange* range)
{
	// Row breaks should have been set; If headers == 0 then logrow cannot be less than 1.
	if(m_rowBreaks.GetSize() == 0 || nLogRow < (ROWCOL)!m_bIsHeaders || nLogCol > m_nCols)
		return FALSE;
	// Top and bottom actual rows
	ROWCOL nAbsRightCol;
	nAbsRow = (nLogRow - 1 + m_bIsHeaders)*(m_nBreaks*2) + 1;	
	
	int iBAIndex; // Breaks Array index
	for(iBAIndex = 0; iBAIndex < m_rowBreaks.GetSize(); iBAIndex++)
	{
		if((long)m_rowBreaks.GetAt(iBAIndex) < (long)(nLogCol-1))
			continue;
		else
			break;
	}
	// Found the right row...
	if((long)m_rowBreaks.GetAt(iBAIndex) >= (long)(nLogCol-1))
	{
		nAbsRow += (iBAIndex*2);
		nAbsLeftCol = m_nRowHeaderWidth + m_nPMButtonCellWidth+m_indentWidths.GetAt(iBAIndex);
		ROWCOL nLogColParser;
		if(iBAIndex == 0)
			nLogColParser = 0;
		else
			nLogColParser = m_rowBreaks.GetAt(iBAIndex - 1) + 1;	// left most to begin with...
		while(nLogColParser < (nLogCol-1))
		{
			nAbsLeftCol += m_colWidths.GetAt(nLogColParser);
			nLogColParser++;
		}
		nAbsLeftCol++;
		nAbsRightCol = nAbsLeftCol + m_colWidths.GetAt(nLogCol-1) - 1;
	}
	else return FALSE;
	// Compute the range occupied by this logical cell
	if(range)
		range->SetCells(nAbsRow, nAbsLeftCol, nAbsRow, nAbsRightCol);
	return TRUE;
}

void CGXCoveredCellPatternMap::SetColWidth(int nPatternCol, int nColWidth)
{
	m_colWidths.SetAt(nPatternCol-1, nColWidth);	// nPatternCol is 1 based...
	CalcColCount();
}

int CGXCoveredCellPatternMap::GetColWidth(int nPatternCol)
{
	return m_colWidths.GetAt(nPatternCol-1);	// nPatternCol is 1 based...
}

void CGXCoveredCellPatternMap::MoveColWidth(int nFromCol, int nToCol, int nDestCol)
{
	ASSERT(nFromCol <= nToCol);
	ASSERT(nDestCol < nFromCol || nDestCol > nToCol);
	ASSERT((nToCol-1) < m_colWidths.GetSize());

	if(nToCol < nFromCol)
		return;

	// Convert to 0 based indices.
	nFromCol--;
	nToCol--;
	nDestCol--;

	// First, adjust the col-width array.
	// Prepare a temp array of col widths to be moved.
	CDWordArray aColsToMove;
	int nIndex = nFromCol;
	for(int i = nFromCol; i <= nToCol; i++)
	{
		// Prepare the temp array.
		aColsToMove.Add(m_colWidths.GetAt(nIndex));
		// Remove the moved cols from the array.
		m_colWidths.RemoveAt(nIndex);
	}
	int nSize = nToCol - nFromCol + 1;
	DWORD nDest = nDestCol > nToCol ? nDestCol - nSize : nDestCol;
	// Append the moved cols back into the col widths array.
	m_colWidths.InsertAt(nDest, &aColsToMove);

	// Second, adjust the breaks array.
	BOOL bMovingToTheLeft;
	if(nDestCol < nFromCol)
		bMovingToTheLeft = TRUE;
	else
		bMovingToTheLeft = FALSE;

	if(bMovingToTheLeft)
	{
		for(int i=0; i<m_rowBreaks.GetSize(); i++)
		{
			long nBreak = (long)m_rowBreaks.GetAt(i);
			if(nBreak >= (long)nDestCol && nBreak < (long)nFromCol)
				m_rowBreaks.SetAt(i, nBreak+nSize);
			else if(nBreak >= (long)nFromCol && nBreak < (long)nToCol)
				m_rowBreaks.SetAt(i, nToCol);
		}
	}
	else	// Moving to the right.
	{
		for(int i=0; i<m_rowBreaks.GetSize(); i++)
		{
			long nBreak = (long)m_rowBreaks.GetAt(i);
			if(nBreak >= (long)nFromCol && nBreak >= (long)nToCol && nBreak < (long)nDestCol)
				m_rowBreaks.SetAt(i, nBreak-nSize);
			else if(nBreak >= (long)nFromCol && nBreak <= (long)nToCol)
				m_rowBreaks.SetAt(i, nFromCol-1);
		}
	}

	CalcColCount();
}

// Remove all empty rows from the breaks array.
BOOL CGXCoveredCellPatternMap::PurgeEmptyRows()
{
	BOOL bPurged = FALSE;
	for(int i=0; i<m_rowBreaks.GetSize();)
	{
		// If first break, check for -1
		if(i == 0 && (long)m_rowBreaks.GetAt(i) == -1)
		{
			m_rowBreaks.RemoveAt(i);
			m_nBreaks--;
			bPurged = TRUE;
			continue;
		}
		// Check if this break is the same as the previous.
		else if(i != 0 && (long)m_rowBreaks.GetAt(i) == (long)m_rowBreaks.GetAt(i-1))
		{
			m_rowBreaks.RemoveAt(i);
			m_nBreaks--;
			bPurged = TRUE;
			continue;
		}
		i++;
	}
	if(bPurged)
		CalcColCount();
	return bPurged;
}

// Get the wrapped row where the col is.
// nCol & nRow are 1 based.
BOOL CGXCoveredCellPatternMap::GetRowOfCol(int nCol, int& nRow)
{
	nCol--;		// 1 based to 0 based.
	for(int i=0; i<m_rowBreaks.GetSize(); i++)
	{
		if(nCol <= (long)m_rowBreaks.GetAt(i))
		{
			nRow = i+1;	// 0 based to 1 based.
			return TRUE;
		}
	}
	return FALSE;
}

void CGXCoveredCellPatternMap::SetRowHeaderWidth(int nHdrWidth)
{
	m_nRowHeaderWidth = nHdrWidth;
}

int CGXCoveredCellPatternMap::GetRowHeaderWidth() const
{
	return m_nRowHeaderWidth;
}

CGXCoveredCellPatternMap& CGXCoveredCellPatternMap::operator=(const CGXCoveredCellPatternMap& map)
{
	// Copy the row breaks array;
	m_rowBreaks.RemoveAll();
	const CDWordArray* theOtherArray = map.GetRowBreaks();
	int nSize = (int)theOtherArray->GetSize();
	m_nBreaks = nSize;
	m_rowBreaks.SetSize(nSize);
	int i;
	for(i=0; i<nSize; i++)
		m_rowBreaks.SetAt(i, theOtherArray->GetAt(i)); 

	// Copy the col widths array;
	m_colWidths.RemoveAll();
	nSize = (int)map.m_colWidths.GetSize();
	m_colWidths.SetSize(nSize);
	for(i=0; i<nSize; i++)
		m_colWidths.SetAt(i, map.m_colWidths.GetAt(i)); 

	// Copy the indent widths for the wrapped rows.
	m_indentWidths.RemoveAll();
	nSize = (int)map.m_indentWidths.GetSize();
	m_indentWidths.SetSize(nSize);
	for(i=0; i<nSize; i++)
		m_indentWidths.SetAt(i, map.m_indentWidths.GetAt(i)); 

	m_bIsHeaders = map.m_bIsHeaders;

	m_nCellWidthPrecision = map.m_nCellWidthPrecision;

	m_nCols = map.GetColCount();

	m_nDefaultCellWidth = map.m_nDefaultCellWidth;

	m_nEffectiveColCount = map.GetEffectiveColCount();

	m_nRowHeaderWidth = map.GetRowHeaderWidth();

	m_nPMButtonCellWidth = map.m_nPMButtonCellWidth;

	m_wChildIndentWidth = map.m_wChildIndentWidth;

	return *this;
}
