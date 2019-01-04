///////////////////////////////////////////////////////////////////////////////
// gxchhsbt.cpp : implementation of CGXHotSpotButton child class
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
// CGXHotSpotButton child class

CGXHotSpotButton::CGXHotSpotButton(CGXControl* pComposite)
	: CGXButton(pComposite)
{
}

void CGXHotSpotButton::Draw(CDC* pDC, BOOL bActive)
{
	if (!bActive)
		return;

	BOOL bPressed = bActive && HasFocus() && m_bPressed;

	CRect r = m_rect;

	HTHEME lhTheme = NULL;
	if (RWIsAppThemed() && RWIsThemeActive())
		lhTheme = RWOpenThemeData (RWGetSafeHwnd(), L"BUTTON");

	if (lhTheme)
	{
		int iState = PBS_NORMAL;		
		if (bPressed) iState = PBS_PRESSED;		
		
		RWDrawThemeBackground( lhTheme, pDC->GetSafeHdc(), BP_PUSHBUTTON, iState, &r, 0 );	
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

		if (bPressed)
		{
			r.top++;
			r.left++;
		}
	}

	// HotSpot-Pushbutton
	if (r.Height() >= 12)
	{
		GXPatB(pDC, r.left+3, r.top+3, 6, 2, 0);
		GXPatB(pDC, r.left+6, r.top+4, 3, 3, 0);
		GXPatB(pDC, r.left+4, r.top+7, 7, 1, 0);
		GXPatB(pDC, r.left+5, r.top+8, 5, 1, 0);
		GXPatB(pDC, r.left+6, r.top+9, 3, 1, 0);
		GXPatB(pDC, r.left+7, r.top+10, 1, 1, 0);
	}
}
