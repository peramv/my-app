///////////////////////////////////////////////////////////////////////////////
// gxadofrg.cpp : AttachForeignTable with code reference to CGXTabbedComboBox
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
// Authors: Praveen Ramesh, Stefan Hoenig
//

#define _OG_EXPORT_IMPL

#include "stdafx.h"

// compile this file only if DAO is supported
#if _MFC_VER >= 0x0420 && !defined(_GX_NO_ADO_SUPPORT)

#ifdef _GXDLL
// used for MFC 2.5 Extension DLL
	#undef AFXAPI_DATA
	#define AFXAPI_DATA __based(__segname("_DATA"))
#endif

// Headers 

#ifndef _GXRESRC_H_
#include "grid\gxresrc.h"
#endif

#ifndef _GXBROWSE_H_
#include "grid\gxbrowse.h"
#endif

#ifndef _GXCTRLI_H_
#include "grid\gxctrli.h"
#endif

#ifndef _GXADO_H_
#include "grid\gxado.h"
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif


#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXADOGRD")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif



void CGXAdoGrid::AttachForeignTable(ROWCOL nCol, CComPtr<ADORecordset> pSet, UINT nKeyCol, UINT nDispCol, BOOL bDispAllCols, BOOL bDisplayHeader)
{
	ASSERT((ADORecordset*)pSet != NULL);
	ASSERT(nCol > 0 && nCol <= GetColCount());

	CGXWaitCursor theWait;

	CString strChoiceList;
	GXFillChoiceList(pSet, strChoiceList, bDisplayHeader);

	TransferCurrentCell();

	CGXTabbedComboBox::ResetChoiceMap(GetParam(), (int) nCol);

	SetStyleRange(CGXRange().SetCols(nCol),
		CGXStyle()
			.SetControl(GX_IDS_CTRL_TABBED_COMBOBOX)
			.SetChoiceList(strChoiceList)
			.SetUserAttribute(GX_IDS_UA_TABLIST_KEYCOL, (LONG) nKeyCol)
			.SetUserAttribute(GX_IDS_UA_TABLIST_TEXTCOL, (LONG) nDispCol)
			.SetUserAttribute(GX_IDS_UA_TABLIST_SHOWALLCOLS, (LONG) bDispAllCols)
			.SetUserAttribute(GX_IDS_UA_TABLIST_TITLEROW, (LONG) bDisplayHeader)
			.SetUserAttribute(GX_IDS_UA_TABLIST_CHOICELISTID, nCol)
		);

	// Reinit current cell
	TransferCurrentCell(FALSE);
}

#endif // #if _MFC_VER >= 0x0420 && !defined(_GX_NO_ADO_SUPPORT)
