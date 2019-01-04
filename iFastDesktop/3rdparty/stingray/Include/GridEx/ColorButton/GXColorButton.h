#if!defined __GXCOLORBUTTON__H__
#define __GXCOLORBUTTON__H__
// CGXColorButton.h
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

#include "GridEx\stdafx.h"

namespace ogex
{

class CGXColorButton : public CMFCColorButton, public CGXPushbutton
{
	GRIDEX_DECLARE_CONTROL(CGXColorButton);
	
 public:
	GRIDEX_API CGXColorButton(CGXGridCore* pGrid);
	GRIDEX_API virtual ~CGXColorButton();
	GRIDEX_API void SetModify(BOOL bModified);
	GRIDEX_API BOOL GetModify();
    GRIDEX_API void SetColor(COLORREF cl);
	GRIDEX_API COLORREF GetColor(ROWCOL nRow, ROWCOL nCol);
	GRIDEX_API COLORREF GetColor();
	GRIDEX_API BOOL OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	GRIDEX_API CMFCColorPopupMenu* GetPopup(){return m_pPopup;}

protected:
	GRIDEX_API void SetActive(BOOL bActive);
	GRIDEX_API void Init(ROWCOL nRow, ROWCOL nCol);
	GRIDEX_API BOOL LButtonUp(UINT nFlags, CPoint pt, UINT nHitState);
	GRIDEX_API BOOL KeyPressed(UINT nMessage, UINT nChar, UINT nRepCnt, UINT nFlags);
	GRIDEX_API void Hide();
	GRIDEX_API void UpdateColor(COLORREF color);
	GRIDEX_API virtual void Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle);
	GRIDEX_API BOOL OnLeftCell(ROWCOL nNewRow, ROWCOL nNewCol);
	GRIDEX_API void OnDraw(CDC* pDC, const CRect& rect, UINT uiState, ROWCOL nRow, ROWCOL nCol);
	GRIDEX_API void OnDraw(CDC* pDC, const CRect& rect, UINT uiState);
	GRIDEX_API void ActivateToolTip(BOOL bAddTool=FALSE);
	GRIDEX_API afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	GRIDEX_API afx_msg void OnKillFocus(CWnd* pNewWnd);
	GRIDEX_API BOOL PreTranslateMessage(MSG* pMsg);
	GRIDEX_DECLARE_MESSAGE_MAP()
		
	BOOL m_bKillFocus;
	BOOL m_bModified;

public:
	GRIDEX_API afx_msg void OnSetFocus(CWnd* pOldWnd);
	GRIDEX_API afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

} // namespace ogex

#endif // __GXCOLORBUTTON__H__
