#if !defined __OGDUPL__H__
#define __OGDUPL__H__
// OGDupl.h
//
//////////////////////////////////////////////////////////////////////////////
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
//////////////////////////////////////////////////////////////////////////////
//

#include "Grid\gxabstr.h"

namespace ogex
{

class CGXGridExcelLikeFillImp: public CGXAbstractGridExcelLikeFillImp
{
public:
	CGXRange m_startRange;
	CRect m_ExcelLastRect;
	CGXRange m_ExcelLastRange;
	GRIDEX_API virtual void OnLButtonDown(CGXGridCore* pGrid, CPoint& point, UINT& flags, int& ht, ROWCOL& nRow, ROWCOL& nCol);
	GRIDEX_API virtual BOOL OnMouseMove(CGXGridCore* pGrid, CPoint& point, UINT& flags, ROWCOL& nRow, ROWCOL& nCol);
	GRIDEX_API virtual void OnLButtonUp(CGXGridCore* pGrid, CPoint& point, UINT& flags);
	GRIDEX_API virtual void DrawDragRect(CGXGridCore* pGrid, CGXRange& rect, BOOL bEraseOld, BOOL bDrawNew);
	GRIDEX_API virtual void FillRect(CGXGridCore* pGrid, CGXRange& nFrom, CGXRange& nTo);
	GRIDEX_API virtual void ClearCurrentDragRect(CGXGridCore* pGrid);
	GRIDEX_API virtual void OnAutoFillDone(CGXGridCore* pGrid, CGXRange& rFinal);
};

} // namespace ogex

//this function has limited visibility scope in source code, so we have to copy it here
static BOOL AFXAPI _doButtonDown1(CGXGridCore* pGrid, UINT flags, CPoint point, UINT xflags, int& ht, ROWCOL& nRow, ROWCOL& nCol)
{
	if (!pGrid->m_bInitDone)
		return FALSE;

	// Process middle mouse click

	pGrid->m_nMouseFlags = flags;
	pGrid->m_bActiveFrame = TRUE;

	// If the grid is already in a special mode, cancel the current mode
	// and return without further processing.

	if (pGrid->GetCapture() == pGrid->m_pGridWnd || flags & xflags)
	{
		// If the grid is already in a special mode, cancel the current mode.
		pGrid->m_pGridWnd->SendMessage(WM_CANCELMODE, 0, 0);
		pGrid->DoCancelMode();
		return FALSE;
	}

	// Be sure, all grid contents are up to date

	pGrid->UpdateWindow();

	// determine context of click

	ht = pGrid->HitTest(point, &nRow, &nCol);

	return TRUE;
}

#endif // __OGDUPL__H__
