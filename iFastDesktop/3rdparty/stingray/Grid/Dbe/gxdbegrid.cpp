///////////////////////////////////////////////////////////////////////////////
// gxdbgrid.cpp : implementation of CGXDBEParam
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
// Author: Praveen Ramesh
//

#define _OG_EXPORT_IMPL

#include "stdafx.h"

#ifdef _GXDLL
#undef AFXAPI_DATA
#define AFXAPI_DATA __based(__segname("_DBENGINE"))
#endif

#ifndef _GXDBEPARAM
#include "grid\dbe\gxdbeprm.h"
#endif
 
inline void GXArchiveBool(CArchive& ar, BOOL& b)
{
	if (ar.IsStoring())
		ar << (BYTE) b;
	else
	{
		BYTE i;
		ar >> i;
		b = i;
	}
}


IMPLEMENT_SERIAL(CGXDBEParam, CGXGridParam, 0 /* schema number*/)

CGXDBEParam::CGXDBEParam()
{
	m_nCurrentRow = 0;              // current edited row (with pencil-row-header)

	m_bUpdateOnStore = FALSE;       // TRUE when Update shall be called
	m_bDoReplaceAll = FALSE;        // TRUE when OnReplaceAll is called
	
	m_pTmpStyle = NULL;             // temporary style object
	
	m_bCanStoreGridCellInCGXData = FALSE;
	m_bAllowPasteMultiCells = FALSE;
	
	m_nMaxColWidth = 255;
	
	m_bSyncCurrentCell = TRUE;
	
	// Display wait cursor when moving more than the
	// specified number of records in the recordset.
	m_lMoveRecordWaitCursor = LONG_MAX;
	
	m_bIsBrowseInit = FALSE;

}

CGXDBEParam::~CGXDBEParam()
{
	delete m_pTmpStyle;
}

void CGXDBEParam::Serialize(CArchive& ar)
{
	CGXGridParam::Serialize(ar);
	
	static const WORD wVersion = 2;
	WORD wActualVersion = wVersion;
	
	ASSERT_VALID( this );
	
	if (ar.IsStoring())
	{
		ar << wVersion;
	}
	else
	{
		// Check for version first
		ar >> wActualVersion;
		if( wActualVersion > wVersion )
		{
#ifdef _DEBUG
			TRACE0( "Incompatible format while reading CGXDBEParam" );
			TRACE2("in %s at line %d\n", __FILE__, __LINE__);
			ASSERT(0);
			// ASSERTION-> Wrong version detected while reading object ->END
#endif
			AfxThrowArchiveException(CArchiveException::badSchema);
			return;
		}
	}
	
	GXArchiveBool(ar, m_bIsBrowseInit);
}
 
