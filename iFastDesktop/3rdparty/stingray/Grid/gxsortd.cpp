///////////////////////////////////////////////////////////////////////////////
// gxsortd.cpp : CGXData specific sorting routines
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

#ifndef _GXCORE_H_
#include "grid\gxcore.h"
#endif

#ifndef _GXEXT_H_
#include "grid\gxext.h"
#endif

#ifndef _GXSTYLES_H_
#include "grid\gxstyles.h"
#endif

#ifndef _GXDELAYR_H_
#include "grid\gxdelayr.h"
#endif

#include "grid\gxpriv.h"

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXPARAM")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

class CGXGridSortMoveDataImp: public CGXAbstractGridSortMoveDataImp
{
public:
	virtual BOOL StoreMoveDataRows(CGXData* pData, const CGXRange& sortRange, const CRowColArray& anRowIndex);
	virtual BOOL StoreMoveDataCols(CGXData* pData, const CGXRange& sortRange, const CRowColArray& anColIndex);
};

void AFXAPI CGXData::ImplementSortMoveData()
{
	if (GXGetAppData()->m_pSortMoveDataImp == NULL)
	{
		// QA: 31521 Removal from AutoDeletePtr
		//GXGetAppData()->AutoDeletePtr(GXGetAppData()->m_pSortMoveDataImp = new CGXGridSortMoveDataImp);
		GXGetAppData()->m_pSortMoveDataImp = new CGXGridSortMoveDataImp;
	}
}

// Sorting (rearranging) CGXData

BOOL CGXGridSortMoveDataImp::StoreMoveDataRows(CGXData* pData, const CGXRange& sortRange, const CRowColArray& anRowIndex)
{
	int nSize = (int)anRowIndex.GetSize() + (int) sortRange.top;

	// Cells
	{
		// Build a new row array
		CPtrArray apRowCells;
		apRowCells.SetSize(anRowIndex.GetSize());
		int n;
		for (n = 0; n < anRowIndex.GetSize(); n++)
		{
			int nSrc = (int) (anRowIndex[n]+sortRange.top);
			if (nSrc < pData->m_apapCellStyle.GetSize())
				apRowCells[n] = pData->m_apapCellStyle[nSrc];
			else
				apRowCells[n] = NULL;
		}

		// Copy this row array back to CGXData
		int nMax = sortRange.top;
		
		if (pData->m_apapCellStyle.GetSize() < nSize)
			pData->m_apapCellStyle.SetSize(nSize);
		
		for (n = 0; n < anRowIndex.GetSize(); n++)
		{
			int nDest = n + (int) (sortRange.top); 
			pData->m_apapCellStyle[nDest] = (CGXStylePtrArray *) apRowCells[n];
			if (apRowCells[n])
				nMax = max(nMax, nDest);
		}
		// truncate empty rows
		if (pData->m_apapCellStyle.GetSize() == nSize && nSize != nMax+1)
			pData->m_apapCellStyle.SetSize(nMax+1);
	}

	// row base styles
	{
		// Build a new row array
		CPtrArray apRows;
		apRows.SetSize(anRowIndex.GetSize());
		int n;
		for (n = 0; n < anRowIndex.GetSize(); n++)
		{
			int nSrc = (int) (anRowIndex[n]+sortRange.top);
			if (nSrc < pData->m_apRowBaseStyle.GetSize())
				apRows[n] = pData->m_apRowBaseStyle[nSrc];
			else
				apRows[n] = NULL;
		}

		// Copy this row array back to CGXData
		if (pData->m_apRowBaseStyle.GetSize() < nSize)
			pData->m_apRowBaseStyle.SetSize(nSize);
		int nMax = 0;
		for (n = 0; n < anRowIndex.GetSize(); n++)
		{
			int nDest = n + (int) (sortRange.top); 
			pData->m_apRowBaseStyle[nDest] = (CGXStyle *) apRows[n];
			if (apRows[n])
				nMax = max(nMax, nDest);
		}
		// truncate empty rows
		if (pData->m_apRowBaseStyle.GetSize() == nSize && nSize != nMax+1)
			pData->m_apRowBaseStyle.SetSize(nMax+1);
	}

	return TRUE;
}

BOOL CGXGridSortMoveDataImp::StoreMoveDataCols(CGXData* pData, const CGXRange& sortRange, const CRowColArray& anColIndex)
{
	// Cells
	CGXStylePtrArrayPtrArray& apapCellStyle = pData->m_apapCellStyle;
		// row array with pointers to arrays of columns

	int nSize = (int)anColIndex.GetSize() + (int) sortRange.left;
	CPtrArray apColCells;
	apColCells.SetSize(anColIndex.GetSize());

	for (int nRow = 0; nRow < apapCellStyle.GetSize(); nRow++)
	{
		CPtrArray* apCols = apapCellStyle[nRow];

		// Nothing to do if row is empty
		if (apCols != NULL)
		{
			// Build a new column array
			int n;
			for (n = 0; n < anColIndex.GetSize(); n++)
			{
				int nSrc = (int) (anColIndex[n]+sortRange.left);
				if (nSrc < apCols->GetSize())
					apColCells[n] = apCols->GetAt(nSrc);
				else
					apColCells[n] = NULL;
			}

			// Copy this column array back to CGXData
			if (apCols->GetSize() < nSize)
				apCols->SetSize(nSize);

			int nMax = sortRange.left;
			for (n = 0; n < anColIndex.GetSize(); n++)
			{
				int nDest = n + (int) (sortRange.left); 
				apCols->SetAt(nDest, (CGXStyle*) apColCells[n]);
				if (apColCells[n])
					nMax = max(nMax, nDest);
			}
			// truncate empty cells
			if (apCols->GetSize() == nSize && nSize != nMax+1)
				apCols->SetSize(nMax+1);
		}
	}

	// column base styles
	{
		// Build a new row array
		CPtrArray apCols;
		apCols.SetSize(anColIndex.GetSize());
		int n;
		for (n = 0; n < anColIndex.GetSize(); n++)
		{
			int nSrc = (int) (anColIndex[n]+sortRange.left);
			if (nSrc < pData->m_apColBaseStyle.GetSize())
				apCols[n] = pData->m_apColBaseStyle[nSrc];
			else
				apCols[n] = NULL;
		}

		// Copy this row array back to CGXData
		if (pData->m_apColBaseStyle.GetSize() < nSize)
			pData->m_apColBaseStyle.SetSize(nSize);
		int nMax = 0;
		for (n = 0; n < anColIndex.GetSize(); n++)
		{
			int nDest = n + (int) (sortRange.left); 
			pData->m_apColBaseStyle[nDest] = (CGXStyle *) apCols[n];
			if (apCols[n])
				nMax = max(nMax, nDest);
		}
		// truncate empty columns
		if (pData->m_apColBaseStyle.GetSize() == nSize && nSize != nMax+1)
			pData->m_apColBaseStyle.SetSize(nMax+1);
	}

	return TRUE;
}

