///////////////////////////////////////////////////////////////////////////////
// gxchcbwb.cpp : implementation of CGXComboBoxWndButton child class
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
// CGXComboBoxWndButton child class

CGXComboBoxWndButton::CGXComboBoxWndButton(CGXControl* pComposite)
	: CGXButton(pComposite)
{
}

void CGXComboBoxWndButton::Draw(CDC* pDC, BOOL bActive)
{
	CGXStyle style;
	Draw(pDC, bActive, style);
}


void CGXComboBoxWndButton::Draw(CDC* pDC, BOOL bActive, const CGXStyle& style)
{
	BOOL bDrawInactive = FALSE;

	// determine if button shall only be drawn for current cell
	CGXComboBoxWnd* pComboBox = (CGXComboBoxWnd*) m_pComposite;
	if (pComboBox->CGXControl::IsKindOf(CONTROL_CLASS(CGXComboBoxWnd)))
		bDrawInactive = pComboBox->m_bInactiveDrawButton;

	// if the CComboBox is active, it has its own button, so
	// I do only draw this button for the current cell when
	// the CComboBox is not active
	if (bActive && m_pComposite->IsActive()
		// return also if this is not the current cell
		// and button shall only be visible for current cell
		|| !bActive && !bDrawInactive)
		return;

	// draw the button
	BOOL bPressed = bActive && HasFocus() && m_bPressed;

	CRect r = m_rect;

	HTHEME lhTheme = NULL;
	if (RWIsAppThemed() && RWIsThemeActive())
		lhTheme = RWOpenThemeData (RWGetSafeHwnd(), L"COMBOBOX");

	if (lhTheme)
	{
		int iState = CBXS_NORMAL;
		
		if (bPressed) iState = CBXS_PRESSED;
		//else if (bDrawInactive) iState = CBXS_DISABLED;		
		        
		RWDrawThemeBackground(lhTheme, pDC->GetSafeHdc(), CP_DROPDOWNBUTTON, iState, &r, 0 );	
		
		int edgeState = bPressed ? EDGE_SUNKEN : EDGE_RAISED;
		RWDrawThemeEdge(lhTheme, pDC->GetSafeHdc(), CP_DROPDOWNBUTTON, iState, &m_rect, edgeState, BF_RECT, 0);

		RWCloseThemeData( lhTheme );
	}
	else
	{
		// Draw the button borders

		// Fill the face of the button (prior to loading bitmap)
		GXPatB(pDC, r, GXGetSysData()->clrBtnFace);

		// Windows 95-look
		COLORREF rgbFace = GXGetSysData()->GetSysColor(COLOR_BTNFACE);
		GXPatB(pDC, r, rgbFace);

		if (bPressed)
			GXDrawEdge(pDC, r, BDR_SUNKENINNER|BDR_SUNKENOUTER);
		else
			GXDrawEdge(pDC, r, BDR_RAISEDINNER|BDR_RAISEDOUTER);

		r.top += 2;
		r.bottom -= 2;

		// Now draw the bitmap centered on the face
		CDC memDC;
		if(memDC.CreateCompatibleDC(pDC))
		{
			CBitmap& bmp = GXGetSysData()->m_bmpDownArrow;
			CBitmap& bmpd = GXGetSysData()->m_bmpDownArrowDisabled;

			BOOL bDisabled = (style.GetIncludeEnabled() && !style.GetEnabled());
		 
			BITMAP bm;
			if (! bDisabled)
				VERIFY(bmp.GetObject(sizeof(bm), &bm) == sizeof(bm));
			else
				VERIFY(bmpd.GetObject(sizeof(bm), &bm) == sizeof(bm));

			int nLeft = max(0, (r.Width() - bm.bmWidth)/2) + r.left;
			int nTop  = max(0, (r.Height() - bm.bmHeight)/2) + r.top;

			if(bPressed)
				// The button is currently pressed, so offset bitmap to give
				// impression of movement.
				nLeft++, nTop++;
		
			CBitmap *pOldBmp = NULL; 
		
			if (! bDisabled)
				pOldBmp = memDC.SelectObject(&bmp);
			else
				pOldBmp = memDC.SelectObject(&bmpd);
			 
			pDC->BitBlt(nLeft, nTop, min(bm.bmWidth, r.Width()-1), min(bm.bmHeight, r.Height()-1), &memDC, 0, 0, SRCCOPY);
			memDC.SelectObject(pOldBmp);
		}
	}
}
