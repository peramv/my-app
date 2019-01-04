///////////////////////////////////////////////////////////////////////////////
// gxcharro.cpp : implementation of arrow button child class
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
//          Supplement Section 227.7202, Government�s use, duplication or
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
// CGXArrowButton child class

CGXArrowButton::CGXArrowButton(CGXControl* pComposite)
	: CGXButton(pComposite)
{	
}

BOOL CGXArrowButton::MouseMove(UINT nFlags, CPoint pt)
{
	nFlags, pt;

	CGXButton::MouseMove(nFlags, pt);

	if (m_bPressed && GetRect().PtInRect(pt) && GetTickCount() >= dwLastTick+dwTicksNeeded)
	{
		// Increase speed
		if (dwTicksNeeded > 150)
			dwTicksNeeded = 150;
		else if (dwTicksNeeded > 50)
			dwTicksNeeded -= 5;

		dwLastTick = GetTickCount();
		m_pComposite->OnClickedButton(this);
	}

	return TRUE;
}

BOOL CGXArrowButton::LButtonDown(UINT nFlags, CPoint pt)
{
	nFlags, pt;

	CGXButton::LButtonDown(nFlags, pt);

	dwLastTick = GetTickCount();
	dwTicksNeeded = 500;

	m_pComposite->OnClickedButton(this);

	return TRUE;
}

BOOL CGXArrowButton::LButtonUp(UINT nFlags, CPoint pt)
{
	nFlags, pt;

	m_bPressed = FALSE;
	Refresh();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CGXUpArrowButton child class

CGXUpArrowButton::CGXUpArrowButton(CGXControl* pComposite)
	: CGXArrowButton(pComposite)
{
}

void CGXUpArrowButton::Draw(CDC* pDC, BOOL bActive)
{
	if (!bActive)
		return;

	BOOL bPressed = bActive && HasFocus() && m_bPressed;

	CRect r = m_rect;

	HTHEME lhTheme = NULL;
	if (RWIsAppThemed() && RWIsThemeActive())
		lhTheme = RWOpenThemeData (RWGetSafeHwnd(), L"SPIN");

	if (lhTheme)
	{
		int iState = UPS_NORMAL;		
		if (bPressed) iState = UPS_PRESSED;		
				
		RWDrawThemeBackground( lhTheme, pDC->GetSafeHdc(), SPNP_UP, iState, &r, 0 );	
		RWCloseThemeData( lhTheme );
	}
	else
	{
		COLORREF rgbFace = GXGetSysData()->GetSysColor(COLOR_BTNFACE);
		GXPatB(pDC, r, rgbFace);

		if (bPressed)
			GXDrawEdge(pDC, r, BDR_SUNKENINNER|BDR_SUNKENOUTER);
		else
			GXDrawEdge(pDC, r, BDR_RAISEDINNER|BDR_RAISEDOUTER);

		int x1, y1;

		if (r.Height() >= 8)
		{
			y1 = r.top + max((r.Height()-5) / 2, 0);
			x1 = r.left + max((r.Width()-7) / 2, 0);
		}
		else if (r.Height() >= 5)
		{
			y1 = r.top + max((r.Height()-3) / 2, 0);
			x1 = r.left + max((r.Width()-5) / 2, 0);
		}
		else
			return;
		 
		if (bPressed)
		{
			y1++;
			x1++;
		}

		x1 += 3;

		if (y1 < r.bottom) GXPatB(pDC, x1--, y1++, 1, 1, 0);
		if (y1 < r.bottom) GXPatB(pDC, x1--, y1++, 3, 1, 0);
		if (y1 < r.bottom) GXPatB(pDC, x1--, y1++, 5, 1, 0);
		if (r.Height() >= 8)
		if (y1 < r.bottom) GXPatB(pDC, x1--, y1++, 7, 1, 0);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CGXDownArrowButton child class

CGXDownArrowButton::CGXDownArrowButton(CGXControl* pComposite)
	: CGXArrowButton(pComposite)
{
}

void CGXDownArrowButton::Draw(CDC* pDC, BOOL bActive)
{
	if (!bActive)
		return;

	BOOL bPressed = bActive && HasFocus() && m_bPressed;

	CRect r = m_rect;

	HTHEME lhTheme = NULL;
	if (RWIsAppThemed() && RWIsThemeActive())
		lhTheme = RWOpenThemeData (RWGetSafeHwnd(), L"SPIN");

	if (lhTheme)
	{
		int iState = DNS_NORMAL;
		if (bPressed) iState = DNS_PRESSED;		
				
		RWDrawThemeBackground( lhTheme, pDC->GetSafeHdc(), SPNP_DOWN, iState, &r, 0 );	
		RWCloseThemeData( lhTheme );
	}
	else
	{
		COLORREF rgbFace = GXGetSysData()->GetSysColor(COLOR_BTNFACE);
		GXPatB(pDC, r, rgbFace);

		if (bPressed)
			GXDrawEdge(pDC, r, BDR_SUNKENINNER|BDR_SUNKENOUTER);
		else
			GXDrawEdge(pDC, r, BDR_RAISEDINNER|BDR_RAISEDOUTER);

		int x1, y1;

		if (r.Height() >= 8)
		{
			y1 = r.top + max((r.Height()-4) / 2, 0);
			x1 = r.left + max((r.Width()-7) / 2, 0);
		}
		else if (r.Height() >= 5)
		{
			y1 = r.top + max((r.Height()-2) / 2, 0);
			x1 = r.left + max((r.Width()-5) / 2, 0);
		}
		else
			return;
		 
		if (bPressed)
		{
			y1++;
			x1++;
		}

		if (y1 < r.bottom) GXPatB(pDC, x1++, y1++, 7, 1, 0);
		if (y1 < r.bottom) GXPatB(pDC, x1++, y1++, 5, 1, 0);
		if (y1 < r.bottom) GXPatB(pDC, x1++, y1++, 3, 1, 0);
		if (r.Height() >= 8)
		if (y1 < r.bottom) GXPatB(pDC, x1++, y1++, 1, 1, 0);
	}
}
