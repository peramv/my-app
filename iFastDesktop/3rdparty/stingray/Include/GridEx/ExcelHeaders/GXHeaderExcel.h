#if !defined __GXHEADEREXCEL__H__
#define __GXHEADEREXCEL__H__

// GXHeaderExcel.h
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
// Author: Boris Meltreger
//

#include "grid\gxctrli.h"
#include "afxcoll.h"

namespace ogex
{

enum GRIDEX_API enHeaderColor {Row, RowMouse, RowSelected, RowSelectedMouse, RowPressed, RowPressedMouse,
					Column, ColumnTop, ColumnMouse, ColumnMouseTop, ColumnSelected, ColumnSelectedTop,
					ColumnSelectedMouse, ColumnSelectedMouseTop, ColumnPressed, ColumnPressedTop,
					ColumnPressedMouse, ColumnPressedMouseTop, 
					ZeroCell, ZeroCellMouse, ZeroCellPressed, ZeroCellPressedMouse,
                    TopLine, Separator, SeparatorSelected, SeparatorPressed, 
					ZeroCellTriangle, ZeroCellHighlightBorder, ZeroCellBorderTop, ZeroCellBorderLeft, ZeroCellBorderRight};

class CGXHeaderExcel: public CGXHeader		 
{
	GRIDEX_DECLARE_CONTROL(CGXHeaderExcel)

	COLORREF ExcelHeaderColors[31];
public:

	GRIDEX_API CGXHeaderExcel(CGXGridCore* pGrid);
	GRIDEX_API virtual void SetColors(CString defaultColors);
	GRIDEX_API virtual void SetLunaBlue();
	GRIDEX_API virtual void SetObsidianBlack();	
	GRIDEX_API virtual void SetSilver();
	GRIDEX_API void SetColor(enHeaderColor type, COLORREF color){ExcelHeaderColors[type] = color;}
	inline COLORREF GetColor(enHeaderColor type){return ExcelHeaderColors[type];}	 
	
	int m_nHitRow;
	int m_nHitCol;
	BOOL m_bOnHeader;

	GRIDEX_API virtual void Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle);
	GRIDEX_API virtual void InvertBorders(CDC* pDC, const CRect& r);
	GRIDEX_API enHeaderColor GetHeaderState(ROWCOL nRow, ROWCOL nCol);	
};

} // namespace ogex

#endif // __GXHEADEREXCEL__H__
