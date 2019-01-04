///////////////////////////////////////////////////////////////////////////////
// gxdrawro.cpp : draw rotated text
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
#ifndef _GXEXT_H_
#include "grid\gxext.h"
#endif

#ifndef _GXRESRC_H_
#include "grid\gxresrc.h"
#endif

#ifndef _GXSTATE_H_
#include "grid\gxstate.h"
#endif

#ifndef _GXDLL_H_
#include "grid\gxdll.h"
#endif

#include <math.h> // sin, cos

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXDRAWX")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

class CGXDrawRotatedTextImp: public CGXAbstractDrawRotatedTextImp
{
public:
	virtual int GXDrawRotatedText(CDC* pDC, LPCTSTR lpszString, int nCount, CRect rc, UINT nFormat, LONG lfOrientation, LPRECT lpClipRect);
};

void AFXAPI CGXDrawingAndFormatting::ImplementDrawRotatedText()
{
	if (GXGetAppData()->m_pDrawRotatedTextImp == NULL)
	{
		// QA: 31521 Removal from AutoDeletePtr
		//GXGetAppData()->AutoDeletePtr(GXGetAppData()->m_pDrawRotatedTextImp = new CGXDrawRotatedTextImp);
		GXGetAppData()->m_pDrawRotatedTextImp = new CGXDrawRotatedTextImp;
	}
}

#if _MFC_VER < 0x0300 && !defined(_DEBUG)
#pragma optimize("", off)
#endif

int CGXDrawRotatedTextImp::GXDrawRotatedText(CDC* pDC, LPCTSTR lpszString, int nCount, CRect rc, UINT nFormat, LONG lfOrientation, LPRECT lpClipRect)
{
	// Unused:
	lpClipRect;

	if (nCount == -1)
		nCount = (int)_tcslen(lpszString);

	// handle vertical text
	CSize size = pDC->GetTextExtent(lpszString, nCount);
	
	double normAngle = (double) lfOrientation/10;
	
	while (normAngle < 0)
		normAngle += 360.0;
	
	while (normAngle >= 360.0)
		normAngle -= 360.0;
	
	CRect rcOrig = rc;
	const double pipi = 3.1415926535;
	
	int nSaveDC = pDC->SaveDC();
	pDC->IntersectClipRect(lpClipRect?lpClipRect:rcOrig);           
	
	double x = (double) rc.left;
	double y = (double) rc.top;

	double dx = (double) rcOrig.Width();
	double dy = (double) rcOrig.Height();
	
	if(normAngle >= 0  && normAngle <=90)
	{
		y += ((size.cx*1.0*sin(normAngle*pipi/180.0))/1.0);
		y += size.cy/2.0;
		
		if (nFormat&DT_RIGHT)
		{
			nFormat &= (~DT_RIGHT);
			x += (dx-size.cx*cos(normAngle*pipi/180.0));
			x -= size.cy;
		}
		else if (nFormat&DT_CENTER)
		{
			nFormat &= (~DT_CENTER);
			x += ((dx-size.cx*cos(normAngle*pipi/180.0))/2.0);
			x -= size.cy/2.0;
		}
		
		if (nFormat&DT_BOTTOM)
		{
			nFormat &= (~DT_BOTTOM);
			y += (dy-size.cx*sin(normAngle*pipi/180.0));
			y -= size.cy;
		}
		else if (nFormat&DT_VCENTER)
		{
			nFormat &= (~DT_VCENTER);
			y += ((dy-size.cx*sin(normAngle*pipi/180.0))/2.0);
			y -= size.cy/2.0;
		}
	}
	else if(normAngle > 90  && normAngle < 180.0)
	{
		normAngle -= 90;
		x += ((size.cx*1.0*sin(normAngle*pipi/180.0))/1.0);
		
		x = (x>rc.right)?rc.right-size.cy:x;
		
		y += ((size.cx*1.0*cos(normAngle*pipi/180.0))/1.0);
		y += size.cy;
		
		if (nFormat&DT_RIGHT)
		{
			nFormat &= (~DT_RIGHT);
			x += (dx-size.cx*cos(normAngle*pipi/180.0));
			x -= size.cy;
		}
		else if (nFormat&DT_CENTER)
		{
			nFormat &= (~DT_CENTER);
			x += ((dx-size.cx*cos(normAngle*pipi/180.0))/2.0);
			x -= size.cy/2.0;
		}
		
		if (nFormat&DT_BOTTOM)
		{
			nFormat &= (~DT_BOTTOM);
			y += (dy-size.cx*sin(normAngle*pipi/180.0));
			y -= size.cy;
		}
		else if (nFormat&DT_VCENTER)
		{
			nFormat &= (~DT_VCENTER);
			y += ((dy-size.cx*sin(normAngle*pipi/180.0))/2.0);
			y -= size.cy/2.0;
		}
	}
	else if(normAngle >= 180.0  && normAngle <= 270.0)
	{
		normAngle -= 180.0;
		x += ((size.cx*1.0*cos(normAngle*pipi/180.0))/1.0);
		
		x += size.cy;
		
		if (nFormat&DT_RIGHT)
		{
			nFormat &= (~DT_RIGHT);
			x += (dx-size.cx*cos(normAngle*pipi/180.0));
			x -= size.cy;
		}
		else if (nFormat&DT_CENTER)
		{
			nFormat &= (~DT_CENTER);
			x += ((dx-size.cx*cos(normAngle*pipi/180.0))/2.0);
			x -= size.cy/2.0;
		}
		
		if (nFormat&DT_BOTTOM)
		{
			nFormat &= (~DT_BOTTOM);
			y += (dy-size.cx*sin(normAngle*pipi/180.0));
			y -= size.cy;
		}
		else if (nFormat&DT_VCENTER)
		{
			nFormat &= (~DT_VCENTER);
			y += ((dy-size.cx*sin(normAngle*pipi/180.0))/2.0);
//			y -= size.cy/2.0;
		}
	}
	else 
	{
		normAngle -= 270;
		x += ((size.cy*1.0*sin(normAngle*pipi/180.0))/1.0);
		
		if (nFormat&DT_RIGHT)
		{
			nFormat &= (~DT_RIGHT);
			x += (dx-size.cx*cos(normAngle*pipi/180.0));
			x -= size.cy;
		}
		else if (nFormat&DT_CENTER)
		{
			nFormat &= (~DT_CENTER);
			x += ((dx-size.cx*cos(normAngle*pipi/180.0))/2.0);
			x -= size.cy/2.0;
		}
		
		if (nFormat&DT_BOTTOM)
		{
			nFormat &= (~DT_BOTTOM);
			y += (dy-size.cx*sin(normAngle*pipi/180.0));
			y -= size.cy;
		}
		else if (nFormat&DT_VCENTER)
		{
			nFormat &= (~DT_VCENTER);
			y += ((dy-size.cx*sin(normAngle*pipi/180.0))/2.0);
			y -= size.cy/2.0;
		}
	}
	
	pDC->TextOut((int) x, (int) y, lpszString, nCount);
	
	pDC->RestoreDC(nSaveDC);
	
	return 0;
}

#if _MFC_VER < 0x0300 && !defined(_DEBUG)
#pragma optimize("", on)
#endif

