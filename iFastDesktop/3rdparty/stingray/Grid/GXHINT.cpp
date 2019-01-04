///////////////////////////////////////////////////////////////////////////////
// gxhint.cpp: implementation of CGXGridHint class
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

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXHINT")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(CGXGridHint, CObject)

/////////////////////////////////////////////////////////////////////////////
// CGXGridHint

CGXGridHint::CGXGridHint(UINT id, int viewID)
{
	m_id = id;
	nViewID = viewID;
	nRow1 = nRow2 = nRow3 = 0;
	nCol1 = nCol2 = nCol3 = 0;
	lParam = 0;
	dwParam = 0;
	vptr = 0;
	flags = 0;
	nViewID = nViewID;
}

/////////////////////////////////////////////////////////////////////////////
// CGXGridHint diagnostics

#ifdef _DEBUG
void CGXGridHint::AssertValid() const
{
	CObject::AssertValid();
}

void CGXGridHint::Dump(CDumpContext& dc) const
{
	AFX_DUMP1(dc, "\nnViewID  = ", nViewID);
	AFX_DUMP1(dc, "\nm_id     = ", m_id);
	AFX_DUMP1(dc, "\nnRow1    = ", nRow1);
	AFX_DUMP1(dc, "\nnRow2    = ", nRow2);
	AFX_DUMP1(dc, "\nnRow3    = ", nRow3);
	AFX_DUMP1(dc, "\nnCol1    = ", nCol1);
	AFX_DUMP1(dc, "\nnCol2    = ", nCol2);
	AFX_DUMP1(dc, "\nnCol3    = ", nCol3);
	AFX_DUMP1(dc, "\nlParam   = ", lParam);
	AFX_DUMP1(dc, "\ndwParam  = ", dwParam);
	AFX_DUMP1(dc, "\nflags    = ", flags);
	dc << "\nRange: " << range.top << "," << range.left << ",";
	dc << range.bottom << "," << range.right;
	if (pStyle)
	{
		dc << "\nStyle " << *pStyle;
		dc << "\nModifyType " << (UINT) mt;
	}
}

#endif //_DEBUG
