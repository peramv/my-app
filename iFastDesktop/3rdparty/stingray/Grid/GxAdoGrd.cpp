///////////////////////////////////////////////////////////////////////////////
// gxadogrd.cpp : implementation of CGXAdoGrid class
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

#if NTDDI_VERSION >= NTDDI_WIN8
#pragma message(_T("To suppress the backward-compatibility ADO messages, please refer to Grid's StdAfx.h file."))
#endif

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

#ifndef _GXADO_H_
#include "grid\gxado.h"
#endif

/*
#if (ADO_MAJOR < 2)
#error We recommend using ADO version 2.0 or later with OG 7.0 or later.\nIf you must use any earlier versions, please contact support for a workaround.
#endif
*/

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

const TCHAR szUnsupportedField[] = _T("Trying to store unsupported field type to data source");
const TCHAR szUnboundField[]     = _T("You have tried to modify the value of an unbound field!");

IMPLEMENT_SERIAL(CGXAdoParam, CGXBrowseParam, 0 /* schema number*/)



/////////////////////////////////////////////////////////////////////////////
// CGXAdoParam

//@doc
//@mfunc
//@rem
//Constructs a <c CGXAdoParam> object.
//@xref <c CGXAdoParam>
CGXAdoParam::CGXAdoParam()
{
	// Record count
	m_bEOFSeen = FALSE;
	m_nRecordCount = -1;

	// Record count increment
	m_nRecordCountInc = 500;

	// Display wait cursor when moving more than the
	// specified number of records in the recordset.
	m_lMoveRecordWaitCursor = 500;

	// Caching
	// m_nCacheSize = 100;
	// m_nRowCacheStart = GX_INVALID;
	// ... maybe later

	//Transaction pending
	m_nTransPending = 0;
	//Current recordset cursor position 0 based
	m_nLastRecord = -1;
}

CGXAdoParam::~CGXAdoParam()
{
}

void CGXAdoParam::Serialize(CArchive& ar)
{
	CGXBrowseParam::Serialize(ar);

	static const WORD wVersion = 1;
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
			TRACE0( "Incompatible format while reading CGXAdoParam" );
			TRACE2("in %s at line %d\n", __FILE__, __LINE__);
			ASSERT(0);
			// ASSERTION-> Wrong version detected while reading object ->END
#endif
			AfxThrowArchiveException(CArchiveException::badSchema);
			return;
		}
	}

	// need to serialize also the m_awColIndex array
	// (if columns have been dragged to another place)
	m_awColIndex.Serialize(ar);

	if (!ar.IsStoring())
	{
		CGXStylesMap* pStyMap = GetStylesMap();

		if (pStyMap)
		{
			m_bsBoolean = pStyMap->GetBaseStyleId(GX_IDS_STYLE_DBBOOLEAN);
			m_bsNumeric = pStyMap->GetBaseStyleId(GX_IDS_STYLE_DBNUMERIC);
			m_bsDate = pStyMap->GetBaseStyleId(GX_IDS_STYLE_DBDATE);
			m_bsText = pStyMap->GetBaseStyleId(GX_IDS_STYLE_DBTEXT);
			m_bsBinary = pStyMap->GetBaseStyleId(GX_IDS_STYLE_DBBINARY);
			m_bsDeletedRows = pStyMap->GetBaseStyleId(GX_IDS_STYLE_DELETEDROWS);
		}
	}
}

// Copying attributes from one param into another will not initialize the param object
// you have to reinitialize the param with a new ADORecordset for it to become usable.
CGXAdoParam& CGXAdoParam::operator=(const CGXAdoParam& p)
{
	CGXBrowseParam::operator=(p);
	m_bsBoolean = p.m_bsBoolean;
	m_bsNumeric = p.m_bsNumeric;
	m_bsDate = p.m_bsDate;
	m_bsText = p.m_bsText;
	m_bsBinary = p.m_bsBinary;
	m_bsDeletedRows = p.m_bsDeletedRows;
	m_bsCurrency = p.m_bsCurrency;
	m_bsGUID = p.m_bsGUID;
	m_bsMemo = p.m_bsMemo;
	m_bsChapter = p.m_bsChapter;
	// The rest of the members help stay in sync with the external data and are hence ignored
	// since this has to be reinitialized with a new ADORecordset
	return *this;
}
/////////////////////////////////////////////////////////////////////////////
// CGXAdoGrid
//@doc
//@mfunc
//parm CWnd* | pGridWnd | A pointer to the parent <c CWnd> object for the <c CGXAdoGrid> object.
//parm CDocument* | pGridDoc | A pointer to the document, if any. Otherwise <bold>NULL<ebold>.
//parm BOOL | bIsViewContextYou  | Should pass TRUE for this parameter if the grid is used in a CView.
//@rem
//Constructs a CGXAdoGrid object.
//You will only need to call this constructor if you want to attach a CGXAdoGrid object to a CGXGridHandleView or CGXGridHandleWnd.
//@ex
/* This example shows you how you can attach a <c CGXAdoGrid> (derived from <c CGXGridCore>) to <c CGXGridHandleView>:
|
void CMyGridView::OnInitialUpdate()

{

AttachGrid( new CGXAdoGrid(this, GetDocument(), TRUE) );

CGXGridHandleView::OnInitialUpdate();


...

}
*/
//@xref <c CGXAdoGrid> <c CGridHandleView> <c CGridHandleWnd>
CGXAdoGrid::CGXAdoGrid(CWnd* pGridWnd, CDocument* pGridDoc, BOOL bIsViewContext)
	: CGXBrowserGrid(pGridWnd, pGridDoc, bIsViewContext)
{
	m_bIsOpen = FALSE;
	//	m_nLastRecord = -1;
}
BOOL CGXAdoGrid::m_bUnInitialize = TRUE;

CGXAdoGrid::~CGXAdoGrid()
{
	if (m_bUnInitialize)
		CoUninitialize();
}
void CGXAdoGrid::SetNoUnInitialize(BOOL bUnInitialize)
{
	m_bUnInitialize = bUnInitialize;
}


long CGXAdoGrid::SyncPosition()
{
	BOOL bSuccess;
	CComPtr<ADORecordset> piRecordset = OnGetRecordset();
	//If not yet initialized do it...
	if (GetAdoParam()->m_nLastRecord == -1)
	{
		VARIANT_BOOL bEof;
		GX_ADO_CHECK(piRecordset->get_EOF(&bEof),piRecordset,bSuccess)
		if (!bEof)
		{
			GetAdoParam()->m_nLastRecord = 0;
			GX_ADO_CHECK(piRecordset->MoveFirst(),piRecordset,bSuccess)
		}
	}

	// else just return the current cursor position
	return GetAdoParam()->m_nLastRecord;
}

void CGXAdoGrid::MoveToPosition(long nRecord, BOOL bSync)
{
	CComPtr<ADORecordset> piRecordset = OnGetRecordset();
	COleVariant varBookmark;

	BOOL bSuccess;
		if (bSync)
			SyncPosition();

		long lMove = nRecord-GetAdoParam()->m_nLastRecord;

		if (lMove == 0)
			return ;

		VARIANT_BOOL bEof,bBof;
		GX_ADO_CHECK(piRecordset->get_BOF(&bBof),piRecordset,bSuccess)
		GX_ADO_CHECK(piRecordset->get_EOF(&bEof),piRecordset,bSuccess)
		if (lMove > 0 && !bEof || lMove < 0 && !bBof)
		{
			COleVariant vNull;
			vNull.vt = VT_NULL;
			vNull.scode = DISP_E_PARAMNOTFOUND;
			if(bEof)	//Bookmarks doesnt work for eof, so move previous
			{
				GX_ADO_CHECK(piRecordset->MovePrevious(),piRecordset,bSuccess)
				lMove++;
			}
			if(bBof)	//Bookmarks doesnt work for bof, so move next
			{
				GX_ADO_CHECK(piRecordset->MoveNext(),piRecordset,bSuccess)
				lMove--;
			}
			if(lMove < 0)
			{
				// The following code removed in OG6.1 to make use of adBookmarkCurrent..
				//GX_ADO_CHECK(piRecordset->get_Bookmark(&varBookmark),piRecordset, bSuccess)
				GX_ADO_CHECK(piRecordset->Move(lMove, COleVariant((long)adBookmarkCurrent)), piRecordset,bSuccess)
				if(!bSuccess)goto ErrorExit;
			}
			else if(lMove > 0)
			{
				// The following code removed in OG6.1 to make use of adBookmarkCurrent..
				//GX_ADO_CHECK(piRecordset->get_Bookmark(&varBookmark),piRecordset, bSuccess)
				GX_ADO_CHECK(piRecordset->Move(lMove, COleVariant((long)adBookmarkCurrent)),piRecordset,bSuccess)
				if(!bSuccess)goto ErrorExit;
			}
		}
		GX_ADO_CHECK(piRecordset->get_EOF(&bEof),piRecordset,bSuccess)
		if(bEof)goto ErrorExit;
		GetAdoParam()->m_nLastRecord = nRecord;
		return;
ErrorExit:
		//Typically happens when records have been deleted in the source by someother app
		AfxThrowUserException();
}
/////////////////////////////////////////////////////////////////////////////
// CGXAdoGrid record count

// a) Typical case
//    - ADORecordset::get_RecordCount() returns the last seen record
//      OnTestGridDimension will increase the record count with
//      pBrowseData->m_nRecordCountInc records at a time.
//
// b) Known record count
//    - If you know the record count, e.g. if you want to determine
//      the record count by calling "SELECT COUNT(*)", you should
//      override Onget_RecordCount(). Calling OnTestGridDimension() will
//      have no effect when Onget_RecordCount() returns a valid value.
//
// NOTE: If you want that the grid determines the record count
// so that there is no further record count testing necessary,
// you can call OnTestGridDimension(GX_MAXROWCOL, 0) from your
// OnInitialUpdate() routine.

void CGXAdoGrid::OnTestGridDimension(ROWCOL nLastRow, ROWCOL nLastCol)
{

	CGXBrowseParam* pBrowseData = GetBrowseParam();
	CComPtr<ADORecordset> piRecordset = OnGetRecordset();
	BOOL bWait;

	// TRACE2("OnTestGridDimension(%ld, %ld)\n", nLastRow, nLastCol);
	if (pBrowseData->m_bEOFSeen || (ADORecordset*)piRecordset == NULL  || !IsRecordsetOpen())
		return;

	long lRecord = -1;

	if (nLastRow < LONG_MAX)
		lRecord = GetRecordFromRow(nLastRow);
	else
		lRecord = LONG_MAX;

	// NOTE: if nLastRow is equal to GX_MAXROWCOL, lRecord is -1

	if (OnGetRecordCount() != LONG_MAX  // Record count is already known
		|| lRecord <= pBrowseData->m_nRecordLastSeen)   // record is already checked
		return;

	BOOL bSuccess;

	// the record count should increase with a given increment, e.g. 500 rows at a time
	if (lRecord != LONG_MAX && pBrowseData->m_nRecordCountInc > 1 && lRecord > 0)
		// rounds up lRecord to the next possible increment
		lRecord = ((lRecord-1) / pBrowseData->m_nRecordCountInc + 1) * pBrowseData->m_nRecordCountInc;

	bWait = FALSE;

	// First case: is record set empty?
	VARIANT_BOOL bBof, bEof;
	GX_ADO_CHECK(piRecordset->get_BOF(&bBof), piRecordset, bSuccess)
	GX_ADO_CHECK(piRecordset->get_EOF(&bEof), piRecordset, bSuccess)
	if (bBof && bEof)
	{
		pBrowseData->m_bEOFSeen = TRUE;
		pBrowseData->m_nRecordLastSeen = -1;
	}
	// Second case: we have to manually move through the records
	else
	{
		long nCurrentRecord = SyncPosition();
			// quickly move to last seen record
		long nRecordLastSeen = pBrowseData->m_nRecordLastSeen;

		ROWCOL nLastRow = nRecordLastSeen+GetHeaderRows()+1;	//$
		bWait = abs(nCurrentRecord-lRecord) > pBrowseData->m_lMoveRecordWaitCursor;
		if (bWait)
			AfxGetApp()->BeginWaitCursor();

		MoveToPosition(nRecordLastSeen, FALSE);

			// and try to position to record lRecord
		VARIANT_BOOL bEof;
		GX_ADO_CHECK(piRecordset->get_EOF(&bEof), piRecordset, bSuccess)
		if(!bSuccess) goto ErrorExit;
		while (nRecordLastSeen < lRecord && !bEof)
		{
			GX_ADO_CHECK(piRecordset->MoveNext(), piRecordset, bSuccess)
			if(!bSuccess) goto ErrorExit;
			GX_ADO_CHECK(piRecordset->get_EOF(&bEof), piRecordset, bSuccess)
			nRecordLastSeen++;
		}

		// Now, save the record and the "EOF seen" state
		GX_ADO_CHECK(piRecordset->get_EOF(&bEof), piRecordset, bSuccess)
		pBrowseData->m_bEOFSeen = bEof;
		pBrowseData->m_nRecordLastSeen = nRecordLastSeen-1;
		GetAdoParam()->m_nLastRecord = nRecordLastSeen;

		DelayFloatCells(CGXRange().SetRows(nLastRow, GetRowCount()));  // $
		DelayMergeCells(CGXRange().SetRows(nLastRow, GetRowCount()));  // $

	}

	if (bWait)
		AfxGetApp()->EndWaitCursor();

	// TRACE(_T("OnTestGridDimension(%lu, %lu)"), nLastRow, nLastCol);
	// TRACE(_T("m_bEOFSeen = %d, m_nRecordLastSeen = %ld\n"), pBrowseData->m_bEOFSeen, pBrowseData->m_nRecordLastSeen);

	// Unused:
	nLastCol;
	return;
ErrorExit:
	return;
}

// OnGetRecordCount()
//
// This method returns the number of records if last record has been accessed
// or LONG_MAX if record count is indetermined.
//
// If you know the exact record count in advance (maybe by using a "SELECT COUNT(*)"),
// you can override this method and return the record count.
//

long CGXAdoGrid::OnGetRecordCount()
{
	CComPtr<ADORecordset> piRecordset = OnGetRecordset();
	CGXBrowseParam* pBrowseData = GetBrowseParam();

	if ((ADORecordset*)piRecordset == NULL   || !IsRecordsetOpen())
		return 0;

	// check if record count is known
	if (pBrowseData->m_bEOFSeen)
		return pBrowseData->m_nRecordLastSeen+1;

	// last record has not been seen yet, record count is unknown
	return LONG_MAX;
}

/////////////////////////////////////////////////////////////////////////////
// CGXAdoGrid support for Caching
//

void CGXAdoGrid::OnFillCache()
{
	// not implemented
	;
}


void CGXAdoGrid::CloseRecordset(CComPtr<ADORecordset> piRecordset)
{
	BOOL bSuccess;
	GX_ADO_CHECK(piRecordset->Close(),piRecordset,bSuccess)
	if ( bSuccess )
	{
		m_bIsOpen = FALSE;
	}
	else AfxMessageBox(_T("Unable to Close Recordset"));
}

BOOL CGXAdoGrid::IsRecordsetOpen()
{
	return m_bIsOpen;
}


/////////////////////////////////////////////////////////////////////////////
// CGXAdoGrid diagnostics

#ifdef _DEBUG
void CGXAdoGrid::AssertValid() const
{
}

void CGXAdoGrid::Dump(CDumpContext& dc) const
{
	dc;
}
#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// CGXAdoGrid message handlers
//@doc
//@mfunc
//@rdesc A pointer to an <c ADORecordset> object.
//@rem
//Returns a pointer to the attached <c ADORecordset> object.
//The default implementation of this method returns the <c ADORecordset>
//object previously specified with <mf SetRecordSet>.<nl> 
//<nl>
//You may also call <mf SetRecordSet> to attach a recordset to the grid. 
//Then you need not override <mf OnGetRecordset>.
//@xref <c CGXAdoGrid> <mf CGXAdoGrid::SetRecordset>
CComPtr<ADORecordset> CGXAdoGrid::OnGetRecordset()
{
	return m_piRecordset;
}

/////////////////////////////////////////////////////////////////////////////
// CGXAdoGrid message handlers

// Initialization
//
// NOTE: CGXAdoGrid fully supports the MFC document/view architecture.
// If you want to be able to open several views on the same Oledb recordset,
// you should override the OnInitialUpdate routine in your view class.
//
// Example:

// void CADOqueryView::OnInitialUpdate()
// {
//  SetRecordset(GetDocument()->m_piRecordset);
//
//  SetParam(&GetDocument()->m_param, FALSE);   // Share CGXAdoParam object among views
//
//  CGXAdoRecordView::OnInitialUpdate();
//
//  EnableHints(TRUE);  // Enable sending out hints
// }
//
// Another frequently asked question:
//
// If you want to insert unbound columns where you want to
// display some additional info based on existing columns,
// you can insert columns with
//      InsertCols(nCol, #ofCols);
// and override OnLoadCellStyle(). In OnLoadCellStyle()
// you can determine the values of the other columns
// with GetValueRowCol(nRow, nCol).
//

void CGXAdoGrid::OnGridInitialUpdate()
{

	COleVariant vNull;
	CComPtr<ADORecordset> piRecordset = OnGetRecordset();
	BOOL bSuccess;
	// check parameter object
	CGXGridParam* pParam = GetParam();

	BOOL bIsInit = FALSE;
		// bIsInit = TRUE if data need to be initialized
		// bIsInit = FALSE if this is only a new view on the same cursor

	if (pParam == NULL)
		SetParam(pParam = new CGXAdoParam);
	else
		// parameter object has already been attached in derived class, so
		// we only need to check if we must initialize it
		bIsInit = pParam->IsInit();
			// CGXGridCore::OnGridInitialUpdate() will set pParam->IsInit() = TRUE
			// So, if OnGridInitialUpdate is called for a new view on the same data,
			// bIsInit will be TRUE

	ASSERT(pParam->IsKindOf(RUNTIME_CLASS(CGXAdoParam)));
	// ASSERTION-> This is not a CGXAdoParam object.
	// You did probably use a CGXGridParam object instead. ->END

	CGXAdoParam* pAdoData = GetAdoParam();

	CGXBrowserGrid::OnGridInitialUpdate();

	InitBrowserSettings();  // Default browser appearance

	// recordset must be allocated already
	//ASSERT((ADORecordset*)piRecordset != NULL);

	// reusable style object for user attributes
	if (pAdoData->m_pTmpStyle == NULL)
		pAdoData->m_pTmpStyle = CreateStyle();

	// Initialize pointer to some objects
	CGXStylesMap* pStyMap = pParam->GetStylesMap();
	ASSERT_VALID(pStyMap);

	CGXProperties* pProp = pParam->GetProperties();
	ASSERT_VALID(pProp);

	// Register user-defined attributes

	// Checkbox: "TRUE" is checked, "FALSE" is unchecked
	pStyMap->AddUserAttribut(GX_IDS_UA_CHECKBOX_CHECKED);
	pStyMap->AddUserAttribut(GX_IDS_UA_CHECKBOX_UNCHECKED);

	StandardStyle().SetUserAttribute(GX_IDS_UA_CHECKBOX_CHECKED, _T("TRUE"));
	StandardStyle().SetUserAttribute(GX_IDS_UA_CHECKBOX_UNCHECKED, _T("FALSE"));

	// Arrow headers should be drawn as in OG 1.0
	CGXBrowseGridArrowRowHeader* pArrowControl = (CGXBrowseGridArrowRowHeader*)
		GetRegisteredControl(GX_IDS_CTRL_BROWSEARROWHEADER);
	pArrowControl->m_bWin95Look = FALSE;

	// Only initialize data if this is not only a new view
	// on the same data and CGXAdoParam has not been loaded
	// from archive.
	if (!bIsInit)
	{
		// Register individual base style for any database field type
		// each database field type will have its own base style, so that
		// a field types special appearance or control type can be easily
		// changed through the base style.
		//
		// If you want for example change all adNumeric columns to be associated with
		// a spin-edit control, simply call
		//      BaseStyle(pAdoData->m_bsNumeric).SetControl(GX_IDS_CTRL_SPINEDIT);
		//
		// Table of base styles:
		//
		// Database Field Type  Base Style Id             String Resource Id
		// ------------------------------------------------------------------------
		// AFX_RFX_BOOL:        pAdoData->m_bsBoolean     GX_IDS_STYLE_DBBOOLEAN
		// AFX_RFX_BYTE:        pAdoData->m_bsNumeric     GX_IDS_STYLE_DBNUMERIC
		// AFX_RFX_INT:         pAdoData->m_bsNumeric     GX_IDS_STYLE_DBNUMERIC
		// AFX_RFX_LONG:        pAdoData->m_bsNumeric     GX_IDS_STYLE_DBNUMERIC
		// AFX_RFX_SINGLE:      pAdoData->m_bsNumeric     GX_IDS_STYLE_DBNUMERIC
		// AFX_RFX_DOUBLE:      pAdoData->m_bsNumeric     GX_IDS_STYLE_DBNUMERIC
		// AFX_RFX_DATE:        pAdoData->m_bsDate        GX_IDS_STYLE_DBDATE
		// AFX_RFX_TEXT:        pAdoData->m_bsText        GX_IDS_STYLE_DBTEXT
		// AFX_RFX_ATEXT:       pAdoData->m_bsText        GX_IDS_STYLE_DBTEXT
		// AFX_RFX_WTEXT:       pAdoData->m_bsText        GX_IDS_STYLE_DBTEXT
		// AFX_RFX_LONGBINARY:  pAdoData->m_bsBinary      GX_IDS_STYLE_DBBINARY
		// AFX_RFX_BINARY:      pAdoData->m_bsBinary      GX_IDS_STYLE_DBBINARY
		//
		// [VC7] Add Styles For ATEXT & WTEXT.

		CGXStyle styleDefault;

		// Boolean fiels will be displayed with horizontally centered checkboxes
		pAdoData->m_bsBoolean = pStyMap->RegisterStyle(
						GX_IDS_STYLE_DBBOOLEAN,
						CGXStyle()
							.SetControl(GX_IDS_CTRL_CHECKBOX3D)
							.SetHorizontalAlignment(DT_CENTER)
							.SetVerticalAlignment(DT_VCENTER),
						TRUE);

		// All other field types will be displayed with the standard style settings
		pAdoData->m_bsNumeric = pStyMap->RegisterStyle(GX_IDS_STYLE_DBNUMERIC, styleDefault, TRUE);
		pAdoData->m_bsCurrency = pStyMap->RegisterStyle(GX_IDS_STYLE_DBCURRENCY, styleDefault, TRUE);
		pAdoData->m_bsDate = pStyMap->RegisterStyle(GX_IDS_STYLE_DBDATE, styleDefault, TRUE);
		pAdoData->m_bsText = pStyMap->RegisterStyle(GX_IDS_STYLE_DBTEXT, styleDefault, TRUE);
		pAdoData->m_bsBinary = pStyMap->RegisterStyle(GX_IDS_STYLE_DBBINARY, styleDefault, TRUE);
		pAdoData->m_bsMemo = pStyMap->RegisterStyle(GX_IDS_STYLE_DBMEMO, styleDefault, TRUE);
		pAdoData->m_bsGUID = pStyMap->RegisterStyle(GX_IDS_STYLE_DBGUID, styleDefault, TRUE);
		pAdoData->m_bsChapter = pStyMap->RegisterStyle(GX_IDS_STYLE_CHAPTER, styleDefault, TRUE);

		// Style for appearance of deleted rows
		pAdoData->m_bsDeletedRows = pStyMap->RegisterStyle(
						GX_IDS_STYLE_DELETEDROWS,
						CGXStyle()
							.SetTextColor(RGB(192,192,192))
							.SetInterior(CGXBrush().SetPattern(4))
							.SetEnabled(FALSE),
						TRUE);

		// Open the query
		OpenRecordset();
	}
	else
	{
		// if document has been read from archive, and
		// recordset is not yet open, try to open it.
		// column specific data should have been
		// read from the archive.
		if (piRecordset && !IsRecordsetOpen())
			// piRecordset->m_nFields == 0))
		{
			vNull.vt = VT_NULL;
			vNull.scode = DISP_E_PARAMNOTFOUND;
			GX_ADO_CHECK(piRecordset->Open(vNull, vNull, adOpenKeyset, adLockOptimistic, adCmdUnknown), piRecordset, bSuccess)
		}
	}
	return;
}

// OpenRecordset
//
// Opens the recordset (if not yet opened),
// initializes the columns (width, field name,
// length, base style) and redraws the grid.
//

//@doc
//@mfunc
//@rem
//Opens the recordset (only if not yet opened), initializes the columns 
//(width, field name, length, base style) and redraws the grid. 
//The method is typically called from <mf CGXAdoGrid::OnGridInitialUpdate>.<nl>
//<nl>
//If no recordset has been attached to the grid, the method will assert.<nl>
//<nl>
//If the recordset has already been opened, the method only initializes the grid 
//columns based on the fields information in the <c ADORecordset>.<nl>
//<nl>
//The method will reset any contents in the <c CGXData> object.
//@xref <c CGXAdoGrid> <mf GXGridCore::OnGridInitialUpdate>
void CGXAdoGrid::OpenRecordset()
{
	COleVariant vNull;

	CComVariant varIndex;
	long	lFieldCount = 0;
	short	nFieldCount, nField;
	CGXProperties* pProp;
	CGXAdoParam* pParam;
	BOOL bOldLockUpdate, bOldEnableUndo,bLock, bSuccess;
	CGXStyle* pStyle;
	CGXBrowseParam* pBrowseData = GetBrowseParam();
	CComPtr<ADORecordset> piRecordset = OnGetRecordset();
	
	// recordset must be allocated already
	//ASSERT((ADORecordset*)piRecordset != NULL);

	// Reset the current cell
	ResetCurrentCell();
	SetCurrentCell(0,0);
	pBrowseData->m_bEOFSeen = FALSE;
	pBrowseData->m_nRecordLastSeen = -1;
	pBrowseData->m_awColIndex.RemoveAll();
	pBrowseData->m_awRowIndex.RemoveAll();

	m_nTopRow = GetFrozenRows() + 1;
	m_nLeftCol = GetFrozenCols() + 1;

	if (piRecordset)
		CloseRecordset(piRecordset);
	// Open the recordset, if it has not yet been opened
	if (piRecordset && !IsRecordsetOpen())
	{
		CGXWaitCursor theWait;
		vNull.vt = VT_ERROR;
		vNull.scode = DISP_E_PARAMNOTFOUND;
		
		GX_ADO_CHECK(piRecordset->Open(vNull, vNull, adOpenKeyset, adLockOptimistic, adCmdUnknown), piRecordset, bSuccess)
		if (!bSuccess) return;
		m_bIsOpen = TRUE; 
	}

	if(piRecordset)
	{
		VARIANT_BOOL bEof;
		if (IsRecordsetOpen())
		{
			GX_ADO_CHECK(piRecordset->get_EOF(&bEof), piRecordset, bSuccess)
			if(!bEof)
			GX_ADO_CHECK(piRecordset->MoveFirst(), piRecordset, bSuccess)
			if(!bSuccess) return;
		}
	}

	pParam = (CGXAdoParam*) GetParam();
	pProp  = pParam->GetProperties();

	// Determine if cells can be changed
	StandardStyle().SetReadOnly(!CanUpdate());

	// but make sure titles and default values can be set
	// while initializing the grid
	bLock = pParam->IsLockReadOnly();
	pParam->SetLockReadOnly(FALSE);

	// Empty undo and redo list
	pParam->EmptyUndoList();
	pParam->EmptyRedoList();

	// Initialize cells
	bOldEnableUndo = pParam->IsEnableUndo();
	pParam->EnableUndo(FALSE);

	// Disable any drawing for the following operations
	bOldLockUpdate = LockUpdate();

	OnTestGridDimension(1, 1);

	// Determine field information:
	// a) determine field information: name, base style, length
	// b) store the field name with SetStyleRange()
	// c) store the column width with SetColWidth()

	pStyle = CreateStyle();

	// Delete contents of CGXData
	pParam->GetData()->StoreRowCount(0);
	pParam->GetData()->StoreColCount(0);


	if(piRecordset && IsRecordsetOpen()){
		m_piFields = NULL;
		GX_ADO_CHECK(piRecordset->get_Fields(&m_piFields), piRecordset, bSuccess)
		if(!bSuccess) return;
		GX_ADO_CHECK(m_piFields->get_Count(&lFieldCount), piRecordset, bSuccess)
		if(!bSuccess)return;

		nFieldCount = (short)lFieldCount;
	}
	else nFieldCount = (short) 0;

	// Reserve space in CGXData
	pParam->GetData()->StoreRowCount(1);
	pParam->GetData()->StoreColCount(nFieldCount + GetHeaderCols());

	pParam->m_nFields = nFieldCount;

	for (nField = 0; nField < nFieldCount; nField++)
	{
		// column info for column nCol in grid/field nField in ADORecordset
		ROWCOL nCol = (ROWCOL) nField + 1 + GetHeaderCols();

		CComPtr<ADOField> pField;

		varIndex.vt = VT_I4;
		varIndex.lVal = (long)nField;
		GX_ADO_CHECK(m_piFields->get_Item(varIndex, &pField), piRecordset, bSuccess)
		if(!bSuccess) return;
		//if(FAILED(hr)) goto ErrorExit;

		// a) determine the base style
		WORD wBaseStyle;        // base style id
		CString strName;
		long cbLength;

		// User can override InitColInfo to hook into default initialization of columns
		BOOL bColumnSettingsLocked = FALSE;

		OnInitColInfo(nCol, pField, strName, cbLength, wBaseStyle, &bColumnSettingsLocked);

		if(!bColumnSettingsLocked)
		{
			// b) store field name in cell (0, nCol)
			SetValueRange(CGXRange(0, nCol), strName);

			// c) store column width
			SetColWidth(nCol, nCol, Width_LPtoDP(
				min(GetMaxColWidth(), max(cbLength, strName.GetLength())) * GX_NXAVGWIDTH));
				// ( GX_NXAVGWIDTH is the average width of a character in pixels ).

			// d) store the info in the column style.

			// This makes moving columns easy, because when the user
			// drags columns the grid will do all the necessary steps.

			// The base style and maximum length of the input text is also
			// stored in the column style. All cells in the column will
			// inherit their style attributes from the column style.

			SetStyleRange(CGXRange().SetCols(nCol),
					(*pStyle)
						.SetMaxLength((WORD) cbLength)
						.SetBaseStyle(wBaseStyle)
				);
		}
		
	}

	// Reposition current cell
	OnTestGridDimension(GetHeaderRows()+2, 0); // check at least
		// one additional row so that record status beam
		// "Next Record" buttons are not greyed
	if (GetRowCount() > GetHeaderRows() && GetColCount() > GetHeaderCols())
		SetCurrentCell(GetHeaderRows()+1, GetHeaderCols()+1);

	// reset LockUpdate state
	LockUpdate(bOldLockUpdate);

	// reset EnableUndo state
	pParam->EnableUndo(bOldEnableUndo);

	// reset LockReadOnly state
	pParam->SetLockReadOnly(bLock);

	// clean up
	delete pStyle;
	pBrowseData->m_nEditMode = noMode;

	// Added this to keep the selection in sync with the current cell when in special mode
	// works only if SetSpecialMode was called before calling the base class OnInitialUpdate
	MoveCurrentCellEx(GX_TOP);

	// readraw the grid (if LockUpdate != TRUE)
	Redraw(GX_INVALIDATE);

	return;
}



// OnInitColInfo
//
// Overridable which is called to get the default settings for
// specific columns based on their data type

//
// Set *pbColumnSettingsLocked to TRUE if you do not want the calling
// routine to further change your settings. If *pbColumnSettingsLocked
// is FALSE or if pbColumnSettingsLocked is NULL, OnOpenRecordSet will modify
// the column width and headers. So pbColumnSettingsLocked can be NULL, so
// check before using it in any override.

//@doc
//@mfunc
//@parm ROWCOL | nCol | Specifies the column id
//@parm const ADOField& | fieldInfo | A reference to an <bold>ADOFieldInfo<ebold> object which contains the information about the DAO field. 
//@parm CString& | strName | A reference to a <c CString> to receive the column title.  
//@parm long& | cbLength | A reference to a long to receive the display width of the column in characters.
//@parm WORD& | wBaseStyle | A reference to a <bold>WORD<ebold> to receive the base style id for the column
//@parm BOOL * | pbColumnSettingsLocked | A pointer to a BOOL variable.  See the remarks section for more information.
//@rem
//Called from <mf OpenRecordset> to determine the default settings for columns based on their 
//data types. The method associates the columns with a base style, determines the column title and width.<nl>
//<nl> 
//In the base class version of this method, cbLength is calculated with <mf GetDisplaySize>.<nl>
//<nl>
//The method assigns the following base styles to the column depending on its data type:
//<ul>
//<li>adInteger, <nl>adBigInt, 
//<nl>adSingle, 
//<nl>adDouble: m_bsNumeric
//<bold>adVarChar<ebold>: m_bsText<eli>
//<li><bold>adBoolean<ebold>: m_bsBoolean<eli>
//<li><bold>adCurrency<ebold>: m_bsCurrency<eli>
//<li><bold>adDate<ebold>: m_bsDate<eli>
//<li>adLongVarBinary: m_bsBinary <eli>
//<li><bold>adGUID<ebold>: m_bsGUID<eli>
//<eul>
//The CGXAdoParam class holds the base style ids.<nl>
//<nl>
//Set *pbColumnSettingsLocked to TRUE if you do not want the calling routine to further change your settings. If *pbColumnSettingsLocked is FALSE or pbColumnSettingsLocked is NULL, OnOpenRecordSet will modify the column widht and headers. Note: Be sure to check for pbColumnSettingsLocked = NULL in your overrides.<nl>
//<nl>
//@xref <mf CGXAdoGrid::GetDisplaySize> <mf CGXAdoGrid::OpenRecordset> <c CGXAdoParam> <c CGXAdoGrid>
void CGXAdoGrid::OnInitColInfo(ROWCOL nCol,
	CComPtr<ADOField> piField,
	CString& strName,
	long& cbLength,
	WORD& wBaseStyle,
	BOOL* pbColumnSettingsLocked/* = NULL*/)
{
	CGXAdoParam* pAdoData = GetAdoParam();
	CComPtr<ADORecordset> piRecordset = OnGetRecordset();

	// see OnInitialUpdate() above for the table of CGXAdoGrid base styles

	DataTypeEnum sFieldType;
	BOOL bSuccess;
	GX_ADO_CHECK(piField->get_Type(&sFieldType), piRecordset, bSuccess)
	//if(FAILED(hr)) goto ErrorExit;
	switch(sFieldType)
	{
	case adWChar:
	case adVarWChar:
	case adLongVarWChar:
	case adChar:
	case adLongVarChar:
	case adVarChar:        wBaseStyle = pAdoData->m_bsText;       break;
	case adNumeric:
	case adVarNumeric:
	case adUnsignedTinyInt:
	case adUnsignedSmallInt:
	case adUnsignedInt:
	case adUnsignedBigInt:
	case adTinyInt:
	case adSmallInt:
	case adInteger:
	case adBigInt:
	case adSingle:
	case adDouble:      wBaseStyle = pAdoData->m_bsNumeric;    break;
	case adBoolean:     wBaseStyle = pAdoData->m_bsBoolean;    break;
	case adCurrency:    wBaseStyle = pAdoData->m_bsCurrency;   break;
	case adDBTimeStamp:
	case adDBTime:
	case adDBDate:
	case adDate:        wBaseStyle = pAdoData->m_bsDate;       break;
	case adGUID:        wBaseStyle = pAdoData->m_bsGUID;       break;
	case adChapter:     wBaseStyle = pAdoData->m_bsChapter;       break;
	case adBinary:
	case adVarBinary:
	case adLongVarBinary: wBaseStyle = pAdoData->m_bsBinary;	break;
	default:
		TRACE0("Unknown Datatype\n");
		ASSERT(FALSE);
		AfxThrowNotSupportedException();
	}


	CComBSTR bStrName;
	GX_ADO_CHECK(piField->get_Name(&bStrName), piRecordset, bSuccess)
	strName = CString(bStrName);
	cbLength = GetDisplaySize(piField);

	if(pbColumnSettingsLocked)
		*pbColumnSettingsLocked = FALSE; //allow further changes by default

// In any override, if you return *pbColumnSettingsLocked = TRUE, then you
// must explicitly set header name, colwidth, and basestyle in the override.
// Here is some sample code.

//			SetValueRange(CGXRange(0, nCol), strName);
//			SetColWidth(nCol, nCol, Width_LPtoDP(
//				min(GetMaxColWidth(), max(cbLength, strName.GetLength())) * GX_NXAVGWIDTH));
//			SetStyleRange(CGXRange().SetCols(nCol),
//					(*pStyle)
//						.SetMaxLength((WORD) cbLength)
//						.SetBaseStyle(wBaseStyle)
//				);

	// Unused:
	nCol;
	return;
}

// GetDisplaySize
//
// NOTE:
// This method is called from the virtual method OnInitColInfo to
// determine the column size. If you prefer other default column
// widths for special columns, you should override GetDisplaySize.

const int MAX_NUM_STRING_SIZE = 29;

//@doc
//@mfunc
//@parm const ADOField& | filedInfo | A reference to an <c ADOField> structure which contains field information for a field in an <c ADORecordset>.
//@rdesc Returns the default column width in characters.
//@rem
//This method is called from <mf OnInitColInfo> to determine the default column width in characters 
//for the specified field type. You may override this method if you want to change the initial 
//widths for specific data types.
//@xref <c CGXAdoGrid> <mf CGXAdoGrid::OnInitColInfo>
long CGXAdoGrid::GetDisplaySize(CComPtr<ADOField> piField)
{

	//CGXAdoParam* pAdoParam = GetAdoParam(); // Unused
	DataTypeEnum sFieldType;
	long lSize;
	BOOL bSuccess;
	GX_ADO_CHECK(piField->get_Type(&sFieldType), m_piRecordset, bSuccess)
	if(!bSuccess) return 0;

	// computes column size
	switch(sFieldType)
	{

	case adBoolean:
		return 4;

	case adUnsignedTinyInt:
	case adTinyInt:
		return 3;

	case adUnsignedSmallInt:
	case adUnsignedInt:
	case adSmallInt:
	case adInteger:
		return 6;

	case adUnsignedBigInt:
	case adBigInt:
		return 11;

	case adCurrency:
		return 11;

	case adSingle:
	case adDouble:
		return MAX_NUM_STRING_SIZE;

	case adDBTimeStamp:
	case adDBTime:
	case adDBDate:
	case adDate:
		// NOTE: This is the maximum supported size of a timestamp, not the average size.
		// This size accounts for intervals (the :FFF) which is not supported by many databases.
		return 24;  // DTB: 'YYYY-MM-DD HH:MM:SS:FFF'

	case adWChar:
	case adVarWChar:
	case adLongVarWChar:
	case adChar:
	case adLongVarChar:
	case adVarChar:
		{
#if defined(_WIN64) && (NTDDI_VERSION < NTDDI_WIN8) // SRSTUDIO-1792/1867
            GX_ADO_CHECK(piField->get_DefinedSize(reinterpret_cast<__int64*>(&lSize)), m_piRecordset, bSuccess)
	#else
		// NOTE: If you receive an error message here, make sure you are targeting
		// the correct OS with the NTDDI_VERSION definition. 
            GX_ADO_CHECK(piField->get_DefinedSize(reinterpret_cast<long*>(&lSize)), m_piRecordset, bSuccess)
	#endif // _MSC_VER >= 1700

		if(!bSuccess) return 0;
		return lSize;
		}

	case adNumeric:
		{
			BYTE cSize;
			GX_ADO_CHECK(piField->get_Precision(&cSize), m_piRecordset, bSuccess)
			if(!bSuccess) return 0;
			return cSize+2;	// +2 for decimal point and sign
		}

	case adBinary:
	case adVarBinary:
	case adLongVarBinary:
	case adGUID:
	case adChapter:
		// not supported types, field will be hidden
		return 0;

	}
	return 0;
}

// CanUpdate
//
// TRUE if the data in the grid can be changed

BOOL CGXAdoGrid::CanUpdate()	//Checked
{
	BOOL bSuccess;
	CComPtr<ADORecordset> piRecordset = OnGetRecordset();

	if(piRecordset && IsRecordsetOpen())
	{
		VARIANT_BOOL bResult;
		GX_ADO_CHECK(piRecordset->Supports(adUpdate, &bResult), piRecordset, bSuccess)
		return bResult && bSuccess;
	}
	else return FALSE;
}

// CanAppend
//
// TRUE if user shall be able to append new rows.
// Call CGXBrowserGrid::SetCanAppend(FALSE) if you want to disable this feature.

BOOL CGXAdoGrid::CanAppend()	//Checked
{
	BOOL bSuccess;
	CComPtr<ADORecordset> piRecordset = OnGetRecordset();

	if(piRecordset && IsRecordsetOpen())
	{
		VARIANT_BOOL bResult;
		GX_ADO_CHECK(piRecordset->Supports(adAddNew
		, &bResult), piRecordset, bSuccess)
		return bSuccess && CGXBrowserGrid::CanAppend() && bResult;
	}
	else return FALSE;
}

// DeleteRows
//
// Called to delete records from the ADORecordset.
//
// Records will be deleted with piRecordset->Delete(); and
// after deleting the records the recordset will be requeried.

extern "C" static int __gxcomparelong(const void* p1, const void* p2)
{
	long l = *(long*) p1 - *(long*) p2;

	return (l>0) ? 1 : (l<0) ? -1 : 0;
}

void CGXAdoGrid::DeleteRows(const CRowColArray& awRowStart, const CRowColArray& awRowEnd, BOOL* pbSuccess)
{
	BOOL bSuccess, bDone=TRUE;	//Two BOOLs for two different kinds of ErrorExits(for Before
							// and after BeginTransaction())

	if (pbSuccess != NULL)
		*pbSuccess = FALSE;

	int nIndex = 0,index;
	ROWCOL nCount = 0;
	long* alRecords = NULL;
	BOOL bOldUndo, bOldLock;
	CComPtr<ADORecordset> prs = OnGetRecordset();
	//CGXRangeList* pSelList = GetParam()->GetRangeList();//Unused
	CGXBrowseParam* pBrowseData = GetBrowseParam();
	int i =0;

	if (!CanUpdate())
		return;

	ROWCOL nEditRow, nEditCol;
	BOOL bCCell = GetCurrentCell(nEditRow, nEditCol);

	// Save current cell's data
	TransferCurrentCell();

	// check if row to be deleted is in edit mode
	if (pBrowseData->m_nEditMode != noMode)
	{
		for (int index = (int)awRowEnd.GetUpperBound(); index >= 0; index--)
		{
			if (pBrowseData->m_nCurrentRow >= awRowStart[index] &&
				pBrowseData->m_nCurrentRow <= awRowEnd[index])
			{
				CancelRecord();
				break;
			}
		}
	}

	// check if row (not to be deleted) is in edit mode
	if (pBrowseData->m_nEditMode != noMode)
	{
		CString s;

		// cannot proceed if row cannot be saved
		if (!Update(&s))
			return;
	}

	// Now, it is sure that m_nEditMode is reset.
	ASSERT(pBrowseData->m_nEditMode == noMode);

	bOldLock = LockUpdate(TRUE);

	// Empty undo/redo list
	bOldUndo = GetParam()->IsEnableUndo();
	GetParam()->EmptyUndoList();
	GetParam()->EmptyRedoList();
	GetParam()->EnableUndo(FALSE);

	//$ Calling begintrans doesnt work
	BeginTrans(_T("Deleting Rows"));

		// First, sort the array of records
		for (index = (int)awRowEnd.GetUpperBound(); index >= 0; index--)
			nCount += awRowEnd[index]-awRowStart[index]+1;

		alRecords = new long[nCount];

		for (index = (int)awRowEnd.GetUpperBound(); index >= 0; index--)
		{
			ROWCOL nRecords = awRowEnd[index]-awRowStart[index]+1;
			for (ROWCOL n = 0; n < nRecords; n++)
				alRecords[nIndex++] = GetRecordFromRow(awRowStart[index]+n);
		}

		qsort(alRecords, (size_t) nCount, sizeof(long), __gxcomparelong);

		// Get the cursor location.
		// The position of the cursor after calling Delete seems to
		// depend on the location of the cursor.
		CursorLocationEnum curLoc = adUseClient;
		GX_ADO_CHECK(prs->get_CursorLocation(&curLoc), prs, bSuccess)

		for (index = (int) nCount-1; index >= 0; index--)
		{
			MoveToPosition(alRecords[index]);
			GX_ADO_CHECK(prs->Delete(adAffectCurrent), prs, bSuccess)
			if(!bSuccess) goto ErrorExit;
			if(curLoc == adUseClient)
			{
				GX_ADO_CHECK(prs->MovePrevious(), prs, bSuccess)
				if(!bSuccess) goto ErrorExit;
				GetAdoParam()->m_nLastRecord--;
			}
			if(curLoc == adUseServer)
			{
				GX_ADO_CHECK(prs->MoveNext(), prs, bSuccess)
				if(!bSuccess) goto ErrorExit;
			}

			//GetAdoParam()->m_nLastRecord--; //only needed for asUseClient

			for (int n = 0; n <= pBrowseData->m_awRowIndex.GetUpperBound(); n++)
			{
				if (pBrowseData->m_awRowIndex[n] > alRecords[index]+GetHeaderRows()+1)
					pBrowseData->m_awRowIndex[n]--;
			}
		}

		for (index = (int)awRowEnd.GetUpperBound(); index >= 0; index--)
		{
			if ((int) awRowStart[index] < pBrowseData->m_awRowIndex.GetSize())
				pBrowseData->m_awRowIndex.RemoveAt((int) awRowStart[index],
					min((int) awRowEnd[index], pBrowseData->m_awRowIndex.GetUpperBound())
					-(int) awRowStart[index]+1);
		}

		//CommitTrans here doesnt work too

		CommitTrans();

		if (pbSuccess != NULL)
			*pbSuccess = TRUE;

		// Remove selection
		SetSelection(0);

		if (bCCell && nEditRow >= awRowStart[0])
		{
			// Sync current cell
				// First, mark as invalid
			StoreCurrentCell(FALSE);

			nEditRow = min(awRowStart[0], GetRowCount());
		}

		for (i = (int)awRowEnd.GetUpperBound(); i >= 0; i--)
			CGXGridCore::StoreRemoveRows(awRowStart[i],awRowEnd[i]);

		// Reset high water mark
		pBrowseData->m_bEOFSeen = FALSE;
		pBrowseData->m_nRecordLastSeen = -1;
		GetAdoParam()->m_nLastRecord = -1;

		// Requery
		{
			CGXWaitCursor theWait;
			GX_ADO_CHECK(prs->Requery(-1), prs, bSuccess)
			if(!bSuccess) goto ErrorExit;
		}

ErrorExit:
		if(!bDone) return;
		if(!bSuccess)
			Rollback();

	delete[] alRecords;

	GetParam()->EnableUndo(bOldUndo);

	// Reposition current cell
	if (bCCell)
	{
		OnTestGridDimension(nEditRow, 0);
		nEditRow = min(nEditRow, GetRowCount());
		SetCurrentCell(nEditRow, nEditCol);
	}

	LockUpdate(bOldLock);

	Redraw();

	if (bCCell)
		TransferCurrentCell(FALSE);

	return;
}

// Requery
//
// Requeries the ADORecordset. It is also necessary to reset
// the last seen record, so that OnTestGridDimension will not
// get confused.

void CGXAdoGrid::Requery()
{
	CGXBrowseParam* pBrowseData = GetBrowseParam();
	CComPtr<ADORecordset> piRecordset = OnGetRecordset();

	// Save and reset current cell
	TransferCurrentCell();

	//Reset high watermark
	pBrowseData->m_bEOFSeen = FALSE;
	pBrowseData->m_nRecordLastSeen = -1;
	GetAdoParam()->m_nLastRecord = -1;
	if (piRecordset)
	{
		CGXWaitCursor theWait;
		piRecordset->Requery(-1);
	}
	pBrowseData->m_nRecordLastSeen = 1;
}

/////////////////////////////////////////////////////////////////////////////
// CGXAdoGrid overridables

// OnLoadCellStyle
//
// give the programmer the chance to load the value from data source
// or apply additional formattings at runtime

BOOL CGXAdoGrid::OnLoadCellStyle(ROWCOL nRow, ROWCOL nCol, CGXStyle& style, LPCTSTR pszExistingValue)
{
	// NOTE: if pszExistingValue is not NULL, it contains
	// the already existing value of the current buffer. You should
	// then only initialize specific formattings here, but
	// not change the cell value.
	//
	// if pszExistingValue is NULL, you should load the value
	// from your external data source.
	//
	// Currently, pszExistingValue is not NULL when the value has
	// been changed for the current record. In a future version
	// pszExistingValue may also be not NULL if the value is
	// cached somewhere else.
	BOOL bSuccess;
	//CGXAdoParam* pAdoData = GetAdoParam();//Unused
	CGXBrowseParam* pBrowseData = GetBrowseParam();
	CComPtr<ADORecordset> piRecordset = OnGetRecordset();
	if ((ADORecordset*)piRecordset && pszExistingValue == NULL && nRow >= GetFirstRow())
	{
		if(!m_piFields)
			GX_ADO_CHECK(piRecordset->get_Fields(&m_piFields), piRecordset, bSuccess)

		int nField = GetFieldFromCol(nCol);
		long lFieldCount;
		GX_ADO_CHECK(m_piFields->get_Count(&lFieldCount), piRecordset, bSuccess)
		if(!bSuccess)
		{
			if (pBrowseData->m_bEOFSeen && nRow > GetLastRow())
			{
				style.SetEnabled(FALSE);
				return TRUE;
			}
		}
		else
		// Get style from current record in data source
		if (!m_bNoValueNeeded && nField != -1 &&  nField < lFieldCount && MoveTo(nRow))
		{
			CString sValue;
			// transfer value from recordset and convert it to a string
			ConvertValueToString(nCol, sValue);
			style.SetValue(sValue);
		}
		else if (pBrowseData->m_bEOFSeen && nRow > GetLastRow())
			style.SetEnabled(FALSE);
		// To allow numeric formating of numeric types...included in OG6.11
		if (style.GetIncludeValue())
		{
			int nField = GetFieldFromCol(nCol);
			CComPtr<ADOField> pField;
			COleVariant varIndex;

			varIndex.vt = VT_I4;
			varIndex.lVal = (long)nField;
			GX_ADO_CHECK(m_piFields->get_Item(varIndex, &pField), piRecordset, bSuccess)
			if(bSuccess)
			{
				DataTypeEnum lFieldType;
				GX_ADO_CHECK(pField->get_Type(&lFieldType), piRecordset, bSuccess)
				if(bSuccess)
				{
					switch(lFieldType)
					{
						case adUnsignedTinyInt:
						case adUnsignedSmallInt:
						case adUnsignedInt:
						case adUnsignedBigInt:
						case adTinyInt:
						case adSmallInt:
						case adBigInt:
						case adInteger:
						case adSingle:
						case adDouble:
						case adBoolean:
						case adNumeric:
							style.SetValueType(GX_VT_NUMERIC);
					}
				}
			}
		}

		return TRUE;
	}

	// You may override this method and apply additional
	// formattings specific to columns or depending on
	// the cells value or context, but be carefull
	// that you don't forget to call this base class
	// version of the method.
	//
	// This method is also a nice hook for filling the choice
	// list of a combobox with the query results of another
	// recordset.
	//

	return FALSE;   // return TRUE if you have changed the style object!
}


// ConvertValueToString
// ConvertValueToString() gets the CFieldInfo of the bound
// Field and converts the value to a string

//@doc
//@mfunc
//@parm ROWCOL | nCol | Specifies the column id.
//@parm CString& | sResult | Reference to a CString to receive the converted value.
//@rem
//Called from <mf OnLoadCellStyle> to retrieve a string with the value for the <c ADOField> bound to the specified column. The string will be displayed in the grid.<nl>
//<nl>
//The default implementation of this method converts all MS Access data types except <bold>dbGUID<ebold>.<nl>
//You may override this method if you want to convert the values for these data types, too.
//@note
//It should also be possible to convert the values for these special data types 
//in a subclassed <c CGXControl> class. An example could be a CGXDaoBitmapControl class, 
//where you could convert an adLongVarBinary field to a bitmap. 
//@xref <c CGXAdoGrid> <mf CGXBrowserGrid::OnLoadCellStyle> <mf CGXControl::Draw>
void CGXAdoGrid::ConvertValueToString(ROWCOL nCol, CString& strRet)
{
	//CGXAdoParam* pAdoParam = GetAdoParam();//Unused
	CComPtr<ADORecordset> piRecordset = OnGetRecordset();
	int nField = GetFieldFromCol(nCol);

	GXGetAdoFieldString(strRet, piRecordset, nField);
}


// MoveTo
//
// This method tries to position the recordset to the given
// row. It will return FALSE if the positioning failed.
//

BOOL CGXAdoGrid::MoveTo(ROWCOL nRow)
{
	BOOL bSuccess/*,bWait=FALSE*/;
	CGXBrowseParam* pBrowseData = GetBrowseParam();
	CComPtr<ADORecordset> piRecordset = OnGetRecordset();

	if ((ADORecordset*)piRecordset == NULL || !IsRecordsetOpen() ||
		(long) (nRow-GetHeaderRows()) > OnGetRecordCount())
		return FALSE;

	long nRecord = GetRecordFromRow(nRow);

	long nCurrentRecord = SyncPosition();

	if(nCurrentRecord == nRecord)
		return TRUE;

	// make sure that recordset is not empty

	VARIANT_BOOL bBof, bEof;
	GX_ADO_CHECK(piRecordset->get_BOF(&bBof), piRecordset, bSuccess)
	GX_ADO_CHECK(piRecordset->get_EOF(&bEof), piRecordset, bSuccess)

	if(bEof && bBof)
	{
		pBrowseData->m_bEOFSeen = TRUE;
		pBrowseData->m_nRecordLastSeen = -1;
		return FALSE;
	}

	TRY
	{
	if(abs(nCurrentRecord-nRecord) > pBrowseData->m_lMoveRecordWaitCursor)
	{
		CGXWaitCursor theWait;
		MoveToPosition(nRecord, FALSE);
	}
	else
		MoveToPosition(nRecord,FALSE);
	}
	CATCH(CUserException, e)
	{
		//Typically occrs when records have been deleted in the source by someother app
		// Requery in a new message, otherwise ASSERT in LookupStyleRowCol
		// Also remove
		MSG msg;
		while (PeekMessage(&msg, GridWnd()->m_hWnd, WM_GX_ADO_REQUERY, WM_GX_ADO_REQUERY, PM_REMOVE));
		::PostMessage(GridWnd()->m_hWnd, WM_GX_ADO_REQUERY, 0, 0);
		/*Requery();
		OpenRecordset();
		Redraw();*/
		// TRACE0("Posted WM_GX_ADO_REQUERY\n");
		GX_THROW_LAST
		return FALSE;
	}
	END_CATCH
	GX_ADO_CHECK(piRecordset->get_EOF(&bEof), piRecordset, bSuccess)
	if (bEof)
	{
		pBrowseData->m_bEOFSeen = TRUE;
		return FALSE;
	}
//$ ErrorExits
	return TRUE;
}

// OnFlushRecord
//
// This method writes dirty fields back to the data source.
// This action can rise exceptions. Sometimes it is necessary
// that the method catches the exception, sometimes it is
// necessary that the exception falls through. This behavior
// is determined through the ps parameter.
//
// If ps is NULL, OnFlushRecord will let exceptions fall through
// If ps is a pointer to a CString, exceptions will be caught and
// ps will be initialized with the text describing the exception.

BOOL CGXAdoGrid::OnFlushRecord(ROWCOL nRow, CString* ps)
{
	BOOL bSuccess;
	CGXBrowseParam* pBrowseData = GetBrowseParam();
	CComPtr<ADORecordset> piRecordset = OnGetRecordset();
	VARIANT_BOOL bEof, bBof;
	COleVariant vNull, varBookmark;
	GX_ADO_CHECK(piRecordset->get_EOF(&bEof), piRecordset, bSuccess)

	GX_ADO_CHECK(piRecordset->get_EOF(&bBof), piRecordset, bSuccess)

	// Sandwich ADORecordset into Edit/AddNew and Update
	vNull.vt = VT_ERROR;
	vNull.scode = DISP_E_PARAMNOTFOUND;

	TRY
	{
		if (pBrowseData->m_nEditMode == addnew)
		{
			GX_ADO_CHECK(piRecordset->AddNew(vNull, vNull), piRecordset, bSuccess)
			if (!bSuccess) return FALSE;
		}

		else
		{
			VERIFY(MoveTo(nRow));
		}

		// Force writing dirty cells to ADORecordset
		// Base class version contains the necessary functionality
		// to check all fields and call OnFlushCellValue
		CGXBrowserGrid::OnFlushRecord(nRow, NULL /* force throwing an exception */);
	}
	CATCH (CException, e)
	{
		// ps is a valid CString if we shall catch the exception
		if (ps)
		{
			TRACE0("CGXAdoGrid::OnFlushRecord failed!\n");

			ps->Empty();
		}
		else
			// let exception fall through
			THROW_LAST();

		// failed, ...
		GX_THROW_LAST
		goto ErrorExit;
	}
	END_CATCH

	PreUpdateRecordset(nRow);

	GX_ADO_CHECK(piRecordset->Update(vNull,vNull), piRecordset, bSuccess)
	if(!bSuccess) goto ErrorExit;

	return TRUE;
ErrorExit:
	{
		GridWnd()->SendMessage(WM_CANCELMODE, 0, 0);
		GX_ADO_CHECK(piRecordset->CancelUpdate(),piRecordset,bSuccess)

		//move cursor to first record
		GetAdoParam()->m_nLastRecord=0;
		GX_ADO_CHECK(piRecordset->MoveFirst(),piRecordset,bSuccess)

		if (ps == NULL)  // check if we should throw an exception
			AfxThrowNotSupportedException();

		return FALSE;
	}

}

// PreUpdateRecordset
//
// let the programmer update additional fields in the recordset which
// are not bound to the grid should not be visible to the user.
//
// This overridable is called from OnFlushRecord
// just before the piRecordset->Update method is called.

//@doc
//@mfunc
//@parm ROWCOL | nRow | Specifies the current row id. You may call <mf GetRecordFromRow> to convert the row id to a zero-based record index.
//@rem
//This overridable is called from <mf OnFlushRecord> after all changed values have been flushed 
//to the <c ADORecordset> and just before the <mf ADORecordset::Update> method is called. 
//You may override it if you want to do any changes in the current record of the <c ADORecordset> 
//before it is updated to the database.
//@xref <c CGXAdoGrid> <mf CGXBrowserGrid::OnFlushRecord> 
void CGXAdoGrid::PreUpdateRecordset(ROWCOL nRow)
{
	// Unused:
	nRow;
}


void CGXAdoGrid::OnFlushCellValue(ROWCOL nRow, ROWCOL nCol, LPCTSTR pszChangedValue)
{
	// Unused:
	nRow;
	BOOL bSuccess;

	long lFieldCount;
	COleVariant varIndex, vNull, vFieldValue, var;
	DataTypeEnum lFieldType;

	// cannot handle this.
	if (pszChangedValue == NULL)
		return;

	//CGXBrowseParam* pBrowseData = GetBrowseParam();//Unused
	//CGXAdoParam* pAdoParam = GetAdoParam();//Unused
	CComPtr<ADORecordset> piRecordset = OnGetRecordset();

	int nField = GetFieldFromCol(nCol);

	GX_ADO_CHECK(m_piFields->get_Count(&lFieldCount), piRecordset, bSuccess)
	if(!bSuccess)
	{
		SetWarningText(_T("Unable to connect to datasource at this time"));
		AfxThrowNotSupportedException();
		return;
	}
	//if (FAILED(hr))		goto ErrorExit;

	if (nField < 0 || nField >= lFieldCount)
	{
		// This case will happen if the user did insert new
		// columns, e.g. a sum based on other fields in the row.
		// If you want to do this, you should make sure that CGXDaoGrid
		// does not try to write this values to the CRecordset.

		// Possible solution to avoid this message is to set
		// the column read-only or static or override this method.

		SetWarningText(_T("You have tried to modify the value of an unbound field"));
		AfxThrowNotSupportedException();
		return;
	}

	CComPtr<ADOField> pField;
	varIndex.vt = VT_I4;
	varIndex.lVal = (long)nField;
	GX_ADO_CHECK(m_piFields->get_Item(varIndex, &pField), piRecordset, bSuccess)
	if(!bSuccess) goto ErrorExit;
	GX_ADO_CHECK(pField->get_Type(&lFieldType), piRecordset, bSuccess)
	if(!bSuccess) goto ErrorExit;
	// Make empty strings NULL
	if (_tcslen(pszChangedValue) == 0)
	{
		if(lFieldType == adNumeric)
			pField->put_Value(COleVariant(_T("0")));	//adNumeric doesn't seem to accept VT_NULL
		else
		{
			vNull.vt = VT_NULL;
			pField->put_Value(vNull);
		}
	}
	else
	{
		switch (lFieldType)
		{
		case adWChar:
		case adVarWChar:
		case adLongVarWChar:
		case adChar:
		case adLongVarChar:
		case adVarChar:
				GX_ADO_CHECK(pField->put_Value(COleVariant(pszChangedValue)), piRecordset, bSuccess)
				break;
		case adUnsignedTinyInt:
				GX_ADO_CHECK(pField->put_Value(
					COleVariant((BYTE) _ttoi(pszChangedValue))), piRecordset, bSuccess)
				break;
		case adUnsignedSmallInt:
				var.vt = VT_UI2;
				var.uiVal = (WORD)_ttoi(pszChangedValue);
				GX_ADO_CHECK(pField->put_Value(var),piRecordset,bSuccess)
				break;
		case adUnsignedInt:
				var.vt = VT_UINT;
				var.uintVal = (UINT)_ttoi(pszChangedValue);
				GX_ADO_CHECK(pField->put_Value(var),piRecordset,bSuccess)
				break;
		case adUnsignedBigInt:
				var.vt = VT_UI4;
				var.ulVal = (DWORD)_ttol(pszChangedValue);
				GX_ADO_CHECK(pField->put_Value(var),piRecordset,bSuccess)
				break;
		case adTinyInt:
				var.vt = VT_I1;
				var.cVal = (BYTE)_ttoi(pszChangedValue);
				GX_ADO_CHECK(pField->put_Value(var),piRecordset,bSuccess)
				break;
		case adSmallInt:
				GX_ADO_CHECK(pField->put_Value(
					COleVariant((SHORT) _ttoi(pszChangedValue), VT_I2)), piRecordset, bSuccess)
				break;
		case adInteger:
				GX_ADO_CHECK(pField->put_Value(
					COleVariant((LONG) _ttol(pszChangedValue), VT_I4)), piRecordset, bSuccess)
				break;
		case adBigInt:
				GX_ADO_CHECK(pField->put_Value(
					COleVariant((LONG) _ttol(pszChangedValue), VT_I8)), piRecordset, bSuccess)
				break;
		case adSingle:
				GX_ADO_CHECK(pField->put_Value(
					COleVariant((FLOAT) _gxttof(pszChangedValue))), piRecordset, bSuccess)
				break;
		case adDouble:
				GX_ADO_CHECK(pField->put_Value(
					COleVariant((DOUBLE) _gxttof(pszChangedValue))), piRecordset, bSuccess)
				break;
		case adNumeric:
				GX_ADO_CHECK(pField->put_Value(
					COleVariant((FLOAT) _gxttof(pszChangedValue))), piRecordset, bSuccess)
				break;
		case adBoolean:
			{
				BOOL bBool = _tcsicmp(pszChangedValue, _T("TRUE")) == 0;
				GX_ADO_CHECK(pField->put_Value(
					COleVariant((SHORT) bBool, VT_BOOL)), piRecordset, bSuccess)
				break;
			}
		case adCurrency:
			{
				COleCurrency varCurr;
				varCurr.ParseCurrency(pszChangedValue);
				CComVariant var;
				var.vt = VT_CY;
				var.cyVal = varCurr.m_cur;
				GX_ADO_CHECK(pField->put_Value(
					var), piRecordset, bSuccess)
				break;
			}

		case adDBTimeStamp:
		case adDBTime:
		case adDBDate:
		case adDate:
			{
				COleDateTime varTime;
				if(!varTime.ParseDateTime(pszChangedValue))
				{
					if (pszChangedValue != NULL && _tcslen(pszChangedValue) > 0)
						varTime = _gxttof(pszChangedValue);
				}
				CComVariant var;
				var.vt = VT_DATE;
				var.date = varTime.m_dt;
				GX_ADO_CHECK(pField->put_Value(
				var), piRecordset, bSuccess)
				break;
			}
		case adBinary:
		case adVarBinary:
		case adLongVarBinary:
		case adGUID:
		case adChapter:

			// This case will only happen if you have set the
			// dirty field for these columns but you have not
			// overriden this method to store the data back to
			// the recordset.
			//
			ASSERT(1);
			SetWarningText(_T("Trying to store unsupported field type to data source"));
			AfxThrowNotSupportedException();
			return;
		}
	}
	return;
ErrorExit:
	SetWarningText(_T("Unable to store fields at this time"));
	AfxThrowNotSupportedException();
	return;
}
// OnAddedNewRecord
//
// OnAddedNewRecord is called after a record has been suceesfully appended
// to the recordset.

void CGXAdoGrid::OnAddedNewRecord()
{

	CGXBrowseParam* pBrowseData = GetBrowseParam();
	pBrowseData->m_bEOFSeen = FALSE;
	GetAdoParam()->m_nLastRecord = -1;
}

void CGXAdoGrid::OnMovedCurrentCell(ROWCOL nRow, ROWCOL nCol)
{
	CGXBrowserGrid::OnMovedCurrentCell(nRow, nCol);
}

// BeginTrans
//
// BeginTrans calls BeginTrans for the Connection.
//
// This method does not call the CGXGridCore base class
// version because Undo/Redo support differs a lot for
// this ADO Grid.

void CGXAdoGrid::BeginTrans(LPCTSTR pszDescription)	//Checked
{

	BOOL bSuccess;
	long lTransLevel;
	CComPtr<ADORecordset> piRecordset = OnGetRecordset();
	CComPtr<ADOProperties> pProperties;
	CComPtr<ADOProperty> pProperty;
	CComPtr<ADOConnection> piConnection;

	if ((ADORecordset*)piRecordset == NULL || !IsRecordsetOpen())
		return;

	CComVariant var;
	// The following line will give a compiler error unless you have Oledb SDK 2.0 or later...
	GX_ADO_CHECK(piRecordset->get_ActiveConnection(&var), piRecordset, bSuccess)
	if(!bSuccess)
		goto ErrorExit;
	piConnection = (ADOConnection *) V_DISPATCH(&var);

	GX_ADO_CHECK(piConnection->get_Properties(&pProperties), piRecordset, bSuccess)

	GX_ADO_CHECK(pProperties->get_Item(COleVariant(_T("Transaction DDL")), &pProperty), piRecordset, bSuccess)

	if((ADOProperty*)pProperty == NULL || !bSuccess)
		goto ErrorExit;

	long attrib;
	GX_ADO_CHECK(pProperty->get_Attributes(&attrib), piRecordset, bSuccess)
	if(attrib == adPropNotSupported || !(attrib & adPropWrite))
	{
		ASSERT("Transaction not supported by this provider!!\n");
		goto ErrorExit;
	}

	GX_ADO_CHECK(piConnection->BeginTrans(&lTransLevel), piRecordset, bSuccess)
	// While using the provider for ODBC and connecting to a data source via Jet
	// you cannot initiate a transaction because Jet does not allow transactions
	// on a connection when there are open recordsets associated with it...

	if(!bSuccess)
		goto ErrorExit;
	GetAdoParam()->m_nTransPending++;

	pszDescription;

ErrorExit:
	return;
}

// CommitTrans
//
// CommitTrans calls CommitTrans for the Connection.
//
// This method does not call the CGXGridCore base class
// version because Undo/Redo support differs a lot for
// this ADO Grid.


void CGXAdoGrid::CommitTrans()
{
	if(GetAdoParam()->m_nTransPending <= 0)
		return;

	CComPtr<ADORecordset> piRecordset = OnGetRecordset();
	BOOL bSuccess;
	if (!piRecordset || !IsRecordsetOpen())
		return;

	CComPtr<ADOConnection> piConnection;
	CComVariant var;
	// The following line will give a compiler error unless you have Oledb SDK 2.0 or later...
	GX_ADO_CHECK(piRecordset->get_ActiveConnection(&var), piRecordset, bSuccess)
	if(!bSuccess)
		goto ErrorExit;
	piConnection = (ADOConnection *) V_DISPATCH(&var);

	if(GetAdoParam()->m_nTransPending > 0)
	{
		GX_ADO_CHECK(piConnection->CommitTrans(), piRecordset, bSuccess)
		if(!bSuccess)
			goto ErrorExit;
		GetAdoParam()->m_nTransPending--;
	}
ErrorExit:
	// Requery the recordset first before operating on it
	// Also Reset high watermark to keep the grid in sync
	GetBrowseParam()->m_bEOFSeen = FALSE;
	GetBrowseParam()->m_nRecordLastSeen = -1;
	GetAdoParam()->m_nLastRecord = -1;
	if (piRecordset)
	{
		CGXWaitCursor theWait;
		piRecordset->Requery(-1);
	}
	// End of Requery
	return;
}

// Rollback
//
// Rollback calls Rollback for the Connection.
//
// This method does not call the CGXGridCore base class
// version because Undo/Redo support differs a lot for
// this ADO Grid.

void CGXAdoGrid::Rollback()			//Checked
{

	CComPtr<ADORecordset> piRecordset = OnGetRecordset();
	BOOL bSuccess;

	if (!piRecordset || !IsRecordsetOpen())
		return;

	CComPtr<ADOConnection> piConnection;
	CComVariant var;
	// The following line will give a compiler error unless you have Oledb SDK 2.0 or later...
	GX_ADO_CHECK(piRecordset->get_ActiveConnection(&var), piRecordset, bSuccess)
	if(!bSuccess) goto ErrorExit;
	piConnection = (ADOConnection *) V_DISPATCH(&var);

	if(GetAdoParam()->m_nTransPending > 0)
	{
		GX_ADO_CHECK(piConnection->RollbackTrans(), piRecordset, bSuccess)
		if(!bSuccess)
			goto ErrorExit;
		GetAdoParam()->m_nTransPending--;
	}

ErrorExit:
	Requery();
	return;
}

// OnReplaceAll
//
// OnReplaceAll switches the CGXAdoGrid into a specific context
// before it calls the base class CGXGridCore::OnReplaceAll method.
//
// Special context is:
// - GXGetLastFRState()->bTransaction = FALSE;
// - pBrowseData->m_bDoReplaceAll = TRUE;
//
// This special settings make sure that each change in a cell
// will automatically update the recordset, and that if
// an update throws an exception CGXAdoGrid::OnReplaceAll
// is resonsible for catching this exception.
//

void CGXAdoGrid::OnReplaceAll(LPCTSTR lpszFind, LPCTSTR lpszReplace, BOOL bCase)
{
	CGXBrowseParam* pBrowseData = GetBrowseParam();
	//ADORecordset* piRecordset = OnGetRecordset();//Unused

	if (!CanUpdate())
		return;

	// Disable undo creation
	GetParam()->EmptyUndoList();
	GetParam()->EmptyRedoList();
	BOOL bUndo = GetParam()->IsEnableUndo();
	GetParam()->EnableUndo(FALSE);

	pBrowseData->m_bDoReplaceAll = TRUE;
		// StoreStyleRowCol checks pBrowseData->m_bDoReplaceAll
		// If it is TRUE, the record will immediately get updated

	// Temporarily turn off append row
	BOOL bAppend = CanAppend();
	pBrowseData->m_bCanAppend = FALSE;

	// Save current cell's data
	TransferCurrentCell();

	ROWCOL nEditRow, nEditCol;
	GetCurrentCell(nEditRow, nEditCol);

	BeginTrans(GXGetAppData()->strmReplaceAll);

	BOOL bOldLock = LockUpdate(TRUE);

	TRY
	{
		GX_FR_STATE* pState = GXGetLastFRState();

			// CGXGridCore::OnReplaceAll checks the following member.
			// If it is FALSE it will not call BeginTrans/CommitTrans
			// and if the user aborts the operation, it throws a
			// CUserException.
		pState->bTransaction = FALSE;

		// don't call CGXBrowserGrid::OnReplaceAll !!!
		CGXGridCore::OnReplaceAll(lpszFind, lpszReplace, bCase);

		// update last record
		if (pBrowseData->m_nEditMode != noMode)
			Update();

		CommitTrans();

		// Requery
		Requery();
	}
	AND_CATCH(CException, e)
	{
		Rollback();
		Requery();

		GX_THROW_LAST
	}
	END_CATCH

	pBrowseData->m_bDoReplaceAll = FALSE;
	pBrowseData->m_bCanAppend = bAppend;

	LockUpdate(bOldLock);

	Redraw();

	// Reenable undo mechanism
	GetParam()->EnableUndo(bUndo);

	SetCurrentCell(nEditRow, nEditCol);
}


// Sorting
//
// Sorting can be done by sorting the recordset with ADO

void CGXAdoGrid::SortRows(CGXRange sortRange, const CGXSortInfoArray& sortInfo, UINT flags /*= GX_UPDATENOW*/)
{
	CComPtr<ADORecordset> pSet = OnGetRecordset();
	VARIANT_BOOL bSuccess;

	ASSERT(sortRange.IsTable());
	// ASSERTION-> It is not supported to sort only a limited range
	// of rows with a CGXAdoGrid ->END

	TransferCurrentCell();

	// Sort the grid with the columns specified in awCols.
	CGXAdoParam* pParam = (CGXAdoParam*) GetParam();
	pParam->EmptyUndoList();
	pParam->EmptyRedoList();

	if (pParam->m_nEditMode != noMode)
	Update();
	// Get the source sql string to append order by.......
	COleVariant var;
	GX_ADO_CHECK(pSet->get_Source(&var), pSet, bSuccess)
	var.vt = VT_BSTR;
	CString sql = (LPCWSTR)var.bstrVal;
	CString strTemp(sql);
	strTemp.MakeLower(); // make it case insensitive

	//int index;
	//index = sql.Find(_T(" order by "));		//Remove the existing order by string
	int index = strTemp.Find(_T(" order by "));
	if(index != -1)
		sql = sql.Left(index);
	// Unused: (in relase build)
	sortRange;


	////////////////////////
	CComPtr<ADORecordset> piRecordset = OnGetRecordset();

	CursorLocationEnum curLoc = adUseClient;
	GX_ADO_CHECK(piRecordset->get_CursorLocation(&curLoc), piRecordset, bSuccess)

	//build sort list
    CString strSort = _T("");
    for (int i = 0; i < sortInfo.GetSize(); i++)
				{
					short nField = (short) GetFieldFromCol(sortInfo[i].nRC);
					COleVariant varIndex;
					varIndex.vt = VT_I4;
					varIndex.lVal = (long)nField;
					CComPtr<ADOField> piField;
					GX_ADO_CHECK(m_piFields->get_Item(varIndex, &piField), pSet, bSuccess)
					CComBSTR bStrName;
					GX_ADO_CHECK(piField->get_Name(&bStrName), pSet, bSuccess)
					CString strName = CString(bStrName);

					if(curLoc != adUseClient)
		                 strSort += _T("[");

					strSort += strName;

					if(curLoc != adUseClient)
	                     strSort += _T("]");

					if (sortInfo[i].sortOrder == CGXSortInfo::descending)
						strSort += _T(" DESC");
					if (i+1 < sortInfo.GetSize())
						strSort += _T(", ");
				}

		if(curLoc == adUseClient)
		{
			// use ado Sort property
            piRecordset->put_Sort(CComBSTR(strSort));
		}
		else
		{
			//use order by string...
			sql += _T(" order by ");
			sql += strSort;
		}

	//Close recordset to make source string writable
	GX_ADO_CHECK(piRecordset->Close(),piRecordset,bSuccess)
	//Change the source sql string
	GX_ADO_CHECK(piRecordset->put_Source(CComBSTR (sql)),piRecordset,bSuccess) COleVariant vNull; vNull.vt = VT_ERROR; vNull.scode = DISP_E_PARAMNOTFOUND;
	//Reopen it....
	GX_ADO_CHECK(piRecordset->Open(vNull, vNull, adOpenKeyset, adLockOptimistic, adCmdText),piRecordset,bSuccess)
	SetSelection(0);

	Requery();
	Redraw(flags);

	GetParam()->m_nLastSortedRow = GX_INVALID;
	GetParam()->m_nLastSortedCol = sortInfo[0].nRC;

	GetParam()->m_bSortAscending = sortInfo[0].sortOrder == CGXSortInfo::ascending;
	SetCurrentCell(GetTopRow(),sortInfo[0].nRC);
	MoveCurrentCell(GX_TOP);
	// Added this to make the selection move with the current cell in special mode
	MoveCurrentCellEx(GX_TOP);
}

//@doc
//@mfunc
//@parm CComBSTR | bstrSource | Specifies the source string 
//@parm CComBSTR | bstrSQL    |  Specifies the SQL string
//@rdesc 
//A pointer to an ADO recordset object
//@rem
//This creates an ADO recordset bound to the given source and SQL. By default it creates the recordset with adOpenKeyset cursor type (only this type is supported) and adLockOptimistic LockType property.<nl>
//<nl>
//Remember this only creates a recordset for you, it does not bind it to the grid. Call SetRecordset to bind it to the grid.
//@xref<c CGXAdoGrid>
CComPtr<ADORecordset> CGXAdoGrid::CreateRecordset(
	CComBSTR		bstrSource,
	CComBSTR		bstrSQL)
{
	HRESULT		hr;
	COleVariant	vNull;
	CComPtr<ADORecordset> piRecordSet;
	CComPtr<ADOConnection> piConnection;

	hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		AfxMessageBox(_T("Unable to Initialize COM"));
		goto ErrorExit;
	}
	//Intialize Connection
	hr = CoCreateInstance(CLSID_CADOConnection, NULL, CLSCTX_INPROC_SERVER, IID_IADOConnection, (LPVOID *)&piConnection);
	if(FAILED(hr))
	{
		AfxMessageBox(_T("Unable to create connection object"));
		goto ErrorExit;
	}

	if ( bstrSource == NULL || bstrSQL == NULL )
	{
		AfxMessageBox(_T("Invalid(NULL) Source name or SQL string"));
		goto ErrorExit;
	}
 	//Initialize Recordset
	hr = CoCreateInstance(CLSID_CADORecordset, NULL, CLSCTX_INPROC_SERVER, IID_IADORecordset, (LPVOID *)&piRecordSet);
	if(FAILED(hr))
	{
		AfxMessageBox(_T("Unable to create Recordset"));
		if (FAILED(hr))		goto ErrorExit;
	}


	BOOL bSuccess;
	hr = piConnection->Open( bstrSource, NULL, NULL, -1 );
 	if (FAILED(hr))
	{
		AfxMessageBox(_T("Unable to make connection to Source: ")+CString(bstrSource));
		goto ErrorExit;
	}

	hr = piRecordSet->putref_ActiveConnection(piConnection);
	if (FAILED(hr))
	{
		AfxMessageBox(_T("Unable to bind Connection/Recordset"));
		goto ErrorExit;
	}


	hr = piRecordSet->put_Source(bstrSQL);
	if (FAILED(hr))
	{
		AfxMessageBox(_T("Unable to put_Source"));
		goto ErrorExit;
	}


	// If your provider does not have cursor capabilities set use
	// put_CursorLocation(adUseClient) on the recordset before calling Open
	// to make ADO use the cursor library from the service components.

	vNull.vt = VT_ERROR;
	vNull.scode = DISP_E_PARAMNOTFOUND;
	GX_ADO_CHECK(piRecordSet->Open(vNull, vNull, adOpenKeyset, adLockOptimistic, adCmdText),piRecordSet,bSuccess)
	if(!bSuccess) goto ErrorExit;
	return piRecordSet;

ErrorExit:
	TCHAR szBuf[256];
	wsprintf(szBuf, _T("Error: %d \n"), hr);
	if (hr)
		AfxMessageBox(szBuf);
	if (m_bUnInitialize)
		CoUninitialize();
	return NULL;
}

#endif // #if _MFC_VER >= 0x0420 && !defined(_GX_NO_ADO_SUPPORT)
