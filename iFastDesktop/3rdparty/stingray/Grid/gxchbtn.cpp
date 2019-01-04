///////////////////////////////////////////////////////////////////////////////
// gxchbtn.cpp : implementation of CGXButton child class
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

#ifndef _GXCTRLI_H_
#include "grid\gxctrli.h"
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CGXButton child class

CGXButton::CGXButton(CGXControl* pComposite)
	: CGXChild(pComposite)
{
	m_bPressed = FALSE;
	m_bMouseDown = FALSE;
	m_bCanPress = TRUE;
}

void CGXButton::Draw(CDC* pDC, BOOL bActive, const CGXStyle& style)
{
	//only use this Draw method if buttonfacecolor specified in style
	if(!style.GetIncludeUserAttribute(GX_IDS_UA_BUTTONFACECOLOR))
	{
	    Draw(pDC,  bActive);
		return;
	}

	WORD nState = 0;

	if (bActive && HasFocus())
	{
		nState |= GX_BTNFOCUS;

		if (m_bPressed)
			nState |= GX_BTNPRESSED;
	}

	COLORREF rgbFace = style.GetIncludeUserAttribute(GX_IDS_UA_BUTTONFACECOLOR)
		               ? (COLORREF) _ttol(style.GetUserAttribute(GX_IDS_UA_BUTTONFACECOLOR))
					   : GXGetSysData()->GetSysColor(COLOR_BTNFACE);
	
	GXPatB(pDC, m_rect, rgbFace);

	if (nState & GX_BTNPRESSED)
		GXDrawEdge(pDC, m_rect, BDR_SUNKENOUTER | BDR_SUNKENINNER);
	else
		GXDrawEdge(pDC, m_rect, BDR_RAISEDOUTER | BDR_RAISEDINNER);

	CRect faceRect(m_rect.left+1, m_rect.top+1, m_rect.right-2, m_rect.bottom-2);
	if (nState & GX_BTNPRESSED)
		faceRect += CPoint(1,1);

	COLORREF rgbSaveColor = RGB(0, 0, 0);
	if(style.GetIncludeEnabled() && !style.GetEnabled())
	{
		rgbSaveColor = pDC->SetTextColor(GXGetSysData()->GetSysColor(COLOR_GRAYTEXT));
	}

	GXDrawFocusText(pDC, faceRect, nState&GX_BTNFOCUS, GetText(), DT_WORDBREAK);

	if(style.GetIncludeEnabled() && !style.GetEnabled())
	{
		pDC->SetTextColor(rgbSaveColor);
	}

}

void CGXButton::Draw(CDC* pDC, BOOL bActive)
{
	WORD nState = 0;

	if (bActive && HasFocus())
	{
		nState |= GX_BTNFOCUS;

		if (m_bPressed)
			nState |= GX_BTNPRESSED;
	}

	HTHEME lhTheme = NULL;
	if (RWIsAppThemed() && RWIsThemeActive())
		lhTheme = RWOpenThemeData (RWGetSafeHwnd(), L"BUTTON");

	if (lhTheme)
	{
		int iState = PBS_NORMAL;
		
		if      (nState & GX_BTNPRESSED) iState = PBS_PRESSED;
		else if (nState & GX_BTNSCOPE)   iState = PBS_HOT;
		else if (nState & GX_BTNFOCUS)   iState = PBS_NORMAL;		
		
		RWDrawThemeBackground( lhTheme, pDC->GetSafeHdc(), BP_PUSHBUTTON, iState, &m_rect, 0 );	
		RWCloseThemeData( lhTheme );
	}
	else
	{
		COLORREF rgbFace = GXGetSysData()->GetSysColor(COLOR_BTNFACE);

		GXPatB(pDC, m_rect, rgbFace);

		if (nState & GX_BTNPRESSED)
			GXDrawEdge(pDC, m_rect, BDR_SUNKENOUTER | BDR_SUNKENINNER);
		else 
			GXDrawEdge(pDC, m_rect, BDR_RAISEDOUTER | BDR_RAISEDINNER);
	}

	CRect faceRect(m_rect.left+1, m_rect.top+1, m_rect.right-2, m_rect.bottom-2);
	if (nState & GX_BTNPRESSED)
		faceRect += CPoint(1,1);

	GXDrawFocusText(pDC, faceRect, nState&GX_BTNFOCUS, GetText(), DT_WORDBREAK);
}

BOOL CGXButton::LButtonDown(UINT nFlags, CPoint pt)
{
	nFlags, pt;

	m_bPressed = TRUE;
	m_bMouseDown = TRUE;
	if (m_bCanPress)
	{
		Refresh();
	}

	if (m_pComposite->IsActive())
		GridWnd()->UpdateWindow();

	return TRUE;
}

BOOL CGXButton::LButtonUp(UINT nFlags, CPoint pt)
{
	nFlags, pt;

	if (m_bPressed && GetRect().PtInRect(pt))
		m_pComposite->OnClickedButton(this);

	m_bPressed = FALSE;
	m_bMouseDown = FALSE;
	if (m_bCanPress)
		Refresh();

	return TRUE;
}

BOOL CGXButton::MouseMove(UINT nFlags, CPoint pt)
{
	nFlags, pt;

	BOOL bState = Intersects(pt);

	if (m_bMouseDown && bState != m_bPressed)
	{
		m_bPressed = bState;
		if (m_bCanPress)
			Refresh();
	}

	return TRUE;
}

BOOL CGXButton::OnGridKeyDown(UINT nChar, UINT nRepCnt, UINT flags)
{
	// unused:
	nRepCnt, flags;

	if (nChar == 32)
	{
		// Draw pressed
		m_bPressed = TRUE;
		if (m_bCanPress)
			Refresh();
		return TRUE;
	}

	return FALSE;
}

BOOL CGXButton::OnGridKeyUp(UINT nChar, UINT nRepCnt, UINT flags)
{
	// unused:
	nRepCnt, flags;

	if (nChar == 32 && m_bPressed)
	{
		// trigger event
		m_pComposite->OnClickedButton(this);

		// Draw normal
		m_bPressed = FALSE;
		if (m_bCanPress)
			Refresh();
		return TRUE;
	}

	return FALSE;
}

void CGXButton::OnGridCancelMode()
{
	if (m_bPressed || m_bMouseDown)
	{
		m_bPressed = FALSE;
		m_bMouseDown = FALSE;
		Refresh();
	}
}
