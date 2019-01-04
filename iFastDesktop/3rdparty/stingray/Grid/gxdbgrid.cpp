///////////////////////////////////////////////////////////////////////////////
// gxdbgrid.cpp : implementation of the CGXODBCGrid class
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


// compile this file only if ODBC is supported
#ifndef _AFX_NO_DB_SUPPORT

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

#ifndef _GXODBC_H_
//#ifndef _WIN64 //RW64
#include "grid\gxodbc.h"
//#endif //_WIN64
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

IMPLEMENT_SERIAL(CGXDbParam, CGXBrowseParam, 0 /* schema number*/)

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXDBGRID")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

#if _MFC_VER >= 0x0420

#define InWaitForDataSource()   0

#else

inline BOOL InWaitForDataSource()   { return CDatabase::InWaitForDataSource(); }

#endif

const int MAX_NUM_STRING_SIZE = 29;

// set this USE_ABSOLUTEPOS = 1 if you want ODBC grid to use SetAbsolutePos instead
// of relative positioning in MoveTo.

// #if _MFC_VER >= 0x0420
// #define USE_ABSOLUTEPOS 1
// #endif

/////////////////////////////////////////////////////////////////////////////
// CGXDbParam

CGXDbParam::CGXDbParam()
{
	// Record count
	m_bEOFSeen = FALSE;
	m_nRecordCount = -1;
	m_nRecordLastSeen = -1;

	// Record count increment
	m_nRecordCountInc = 500;

	// Display wait cursor when moving more than the
	// specified number of records in the recordset.
	m_lMoveRecordWaitCursor = 30;

	m_nTransactionPending = 0;

	// Caching
	// m_nCacheSize = 100;
	// m_nRowCacheStart = GX_INVALID;
	// ... maybe later

#if _MFC_VER >= 0x0420
	m_apFieldInfo = NULL;
#endif

	// display Memo fields (default)
	m_bDisplayMemo = TRUE;
}

CGXDbParam::~CGXDbParam()
{
#if _MFC_VER >= 0x0420
	delete[] m_apFieldInfo;
#endif
}

void CGXDbParam::Serialize(CArchive& ar)
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
			TRACE0( "Incompatible format while reading CGXDbParam" );
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
// you have to reinitialize the param with a new CRecordset for it to become usable.
CGXDbParam& CGXDbParam::operator=(const CGXDbParam& p)
{
	CGXBrowseParam::operator=(p);
	m_bDisplayMemo = p.m_bDisplayMemo;
	m_bsBoolean = p.m_bsBoolean;
	m_bsNumeric = p.m_bsNumeric;
	m_bsDate = p.m_bsDate;
	m_bsText = p.m_bsText;
	m_bsBinary = p.m_bsBinary;
	m_bsDeletedRows = p.m_bsDeletedRows;
	// The rest of the members help stay in sync with the external data and are hence ignored
	// since this has to be reinitialized with a new CRecordset
	return *this;
}

/////////////////////////////////////////////////////////////////////////////
// CGXODBCGrid

CGXODBCGrid::CGXODBCGrid(CWnd* pGridWnd, CDocument* pGridDoc, BOOL bIsViewContext)
	: CGXBrowserGrid(pGridWnd, pGridDoc, bIsViewContext)
{
	m_pRecordset = NULL;
	m_bRecordAppended = FALSE;
}

CGXODBCGrid::~CGXODBCGrid()
{
}

/////////////////////////////////////////////////////////////////////////////
// CGXODBCGrid record count

// a) Typical case
//    - CRecordset::GetRecordCount() returns the last seen record
//      OnTestGridDimension will increase the record count with
//      pBrowseData->m_nRecordCountInc records at a time.
//
// b) Known record count
//    - If you know the record count, e.g. if you want to determine
//      the record count by calling "SELECT COUNT(*)", you should
//      override OnGetRecordCount(). Calling OnTestGridDimension() will
//      have no effect when OnGetRecordCount() returns a valid value.
//
// NOTE: If you want that the grid determines the record count
// so that there is no further record count testing necessary,
// you can call OnTestGridDimension(GX_MAXROWCOL, 0) from your
// OnInitialUpdate() routine.

void CGXODBCGrid::OnTestGridDimension(ROWCOL nLastRow, ROWCOL nLastCol)
{
	CRecordset* pRecordset = OnGetRecordset();
	CGXDbParam* pBrowseData = GetDbParam();

	// TRACE2("OnTestGridDimension(%ld, %ld)\n", nLastRow, nLastCol);
	if (pBrowseData->m_bEOFSeen || pRecordset == NULL || !pRecordset->IsOpen())
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

	// NOTE: Disable usage of GetRecordCount() because GetRecordCount()
	// sometimes returns too large values when used with SQL Server 6.5
	pBrowseData->m_nRecordCount = 0; // pRecordset ? pRecordset->GetRecordCount() : 0;

	// the record count should increase with a given increment, e.g. 500 rows at a time
	if (lRecord != LONG_MAX && pBrowseData->m_nRecordCountInc > 1 && lRecord > 0)
		// rounds up lRecord to the next possible increment
		lRecord = ((lRecord-1) / pBrowseData->m_nRecordCountInc + 1) * pBrowseData->m_nRecordCountInc;

	BOOL bWait = FALSE;

	// First case: is record set empty?
	if (pRecordset == NULL || pRecordset->IsBOF() && pRecordset->IsEOF())
	{
		pBrowseData->m_bEOFSeen = TRUE;
		pBrowseData->m_nRecordLastSeen = -1;
	}
	// Second case: we use CRecordset::GetRecordCount as high water mark
	else
	{
		long nRecordLastSeen = pBrowseData->m_nRecordLastSeen; //pBrowseData->m_nRecordCount-1;
		ROWCOL nLastRow = nRecordLastSeen+GetHeaderRows()+1;

		while (InWaitForDataSource())
			NULL;

		CRecordsetStatus rs;
		pRecordset->GetStatus(rs);

		if (rs.m_bRecordCountFinal)
		{
			pBrowseData->m_bEOFSeen = TRUE;
			pBrowseData->m_nRecordCount = pRecordset->GetRecordCount()-1;
			pBrowseData->m_nRecordLastSeen = pBrowseData->m_nRecordCount;
			return;
		}

		TRY
		{
			long lMove = nRecordLastSeen-rs.m_lCurrentRecord;
			if (lMove != 0)
			{
				// display wait cursor
				bWait = labs(nRecordLastSeen-lRecord) > pBrowseData->m_lMoveRecordWaitCursor;

				if (bWait)
					AfxGetApp()->BeginWaitCursor();

				pRecordset->Move(lMove);
			}

			// and try to position to record lRecord
			while (nRecordLastSeen < lRecord && !pRecordset->IsEOF())
			{
				pRecordset->MoveNext();
				nRecordLastSeen++; // = pRecordset->GetRecordCount()-1;
			}

		}
		CATCH(CDBException, e)
		{
			// Trace them the reason it failed to move to the specified record
			TRACE(e->m_strError);
			GX_THROW_LAST
			// e->Delete();
		}
		END_CATCH

		// Now, save the record
		pBrowseData->m_nRecordLastSeen = nRecordLastSeen-1; //pRecordset->GetRecordCount()-1;
		pBrowseData->m_bEOFSeen = pRecordset->IsEOF();

		// Support for merge cells and floating cells
		// New rows have to be checked
		DelayFloatCells(CGXRange().SetRows(nLastRow, GetRowCount()));
		DelayMergeCells(CGXRange().SetRows(nLastRow, GetRowCount()));

		// TRACE("DelayMergeCells(%d,%d)\n", nLastRow, GetRowCount());
	}

	if (bWait)
		AfxGetApp()->EndWaitCursor();


	// TRACE(_T("OnTestGridDimension(%lu, %lu)"), nLastRow, nLastCol);
	// TRACE(_T("m_bEOFSeen = %d, m_nRecordLastSeen = %ld\n"), pBrowseData->m_bEOFSeen, pBrowseData->m_nRecordLastSeen);

	// Unused:
	nLastCol;
}

// OnGetRecordCount()
//
// This method returns the number of records if last record has been accessed
// or LONG_MAX if record count is indetermined.
//
// If you know the exact record count in advance (maybe by using a "SELECT COUNT(*)"),
// you can override this method and return the record count.
//

long CGXODBCGrid::OnGetRecordCount()
{
	CRecordset* pRecordset = OnGetRecordset();
	CGXBrowseParam* pBrowseData = GetBrowseParam();

	if (pRecordset == NULL || !pRecordset->IsOpen())
		return 0;

	// check if record count is known
	if (pBrowseData->m_bEOFSeen)
		return pBrowseData->m_nRecordLastSeen+1;

	// last record has not been seen yet, record count is unknown
	return LONG_MAX;
}

/////////////////////////////////////////////////////////////////////////////
// CGXODBCGrid support for Caching
//

void CGXODBCGrid::OnFillCache()
{
	// not implemented
	;
}

/////////////////////////////////////////////////////////////////////////////
// CGXODBCGrid diagnostics

#ifdef _DEBUG
void CGXODBCGrid::AssertValid() const
{
}

void CGXODBCGrid::Dump(CDumpContext& dc) const
{
	dc;
}
#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// CGXODBCGrid message handlers

CRecordset* CGXODBCGrid::OnGetRecordset()
{
	return m_pRecordset;
}

/////////////////////////////////////////////////////////////////////////////
// CGXODBCGrid message handlers

// Initialization
//
// NOTE: CGXODBCGrid fully supports the MFC document/view architecture.
// If you want to be able to open several views on the same ODBC recordset,
// you should override the OnInitialUpdate routine in your view class.
//
// Example:
//
// void CODBCqueryView::OnInitialUpdate()
// {
//  SetRecordset(&GetDocument()->m_dynamicSet);
//
//  SetParam(&GetDocument()->m_param, FALSE);   // Share CGXDbParam object among views
//
//  CGXODBCRecordView::OnInitialUpdate();
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

void CGXODBCGrid::OnGridInitialUpdate()
{
	CRecordset* pRecordset = OnGetRecordset();
	// check parameter object
	CGXGridParam* pParam = GetParam();

	BOOL bIsInit = FALSE;
		// bIsInit = TRUE if data need to be initialized
		// bIsInit = FALSE if this is only a new view on the same cursor

	if (pParam == NULL)
		SetParam(pParam = new CGXDbParam);
	else
		// parameter object has already been attached in derived class, so
		// we only need to check if we must initialize it
		bIsInit = pParam->IsInit();
			// CGXGridCore::OnGridInitialUpdate() will set pParam->IsInit() = TRUE
			// So, if OnGridInitialUpdate is called for a new view on the same data,
			// bIsInit will be TRUE

	ASSERT(pParam->IsKindOf(RUNTIME_CLASS(CGXDbParam)));
	// ASSERTION-> This is not a CGXDbParam object.
	// You did probably use a CGXGridParam object instead. ->END

	CGXDbParam* pDbData = GetDbParam();

	CGXBrowserGrid::OnGridInitialUpdate();

	InitBrowserSettings();  // Default browser appearance

	// recordset must be allocated already
	// ASSERT_VALID(pRecordset);
	// ASSERT(pRecordset->IsKindOf(RUNTIME_CLASS(CRecordset)));

	// reusable style object for user attributes
	if (pDbData->m_pTmpStyle == NULL)
		pDbData->m_pTmpStyle = CreateStyle();

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
	// on the same data and CGXDbParam has not been loaded
	// from archive.
	if (!bIsInit)
	{
		// Register individual base style for any database field type
		// each database field type will have its own base style, so that
		// a field types special appearance or control type can be easily
		// changed through the base style.
		//
		// If you want for example change all dbByte columns to be associated with
		// a spin-edit control, simply call
		//      BaseStyle(pDbData->m_bsByte).SetControl(GX_IDS_CTRL_SPINEDIT);
		//
		// Table of base styles:
		//
		// Database Field Type  Base Style Id             String Resource Id
		// ------------------------------------------------------------------------
		// AFX_RFX_BOOL:        pDbData->m_bsBoolean     GX_IDS_STYLE_DBBOOLEAN
		// AFX_RFX_BYTE:        pDbData->m_bsNumeric     GX_IDS_STYLE_DBNUMERIC
		// AFX_RFX_INT:         pDbData->m_bsNumeric     GX_IDS_STYLE_DBNUMERIC
		// AFX_RFX_LONG:        pDbData->m_bsNumeric     GX_IDS_STYLE_DBNUMERIC
		// AFX_RFX_SINGLE:      pDbData->m_bsNumeric     GX_IDS_STYLE_DBNUMERIC
		// AFX_RFX_DOUBLE:      pDbData->m_bsNumeric     GX_IDS_STYLE_DBNUMERIC
		// AFX_RFX_DATE:        pDbData->m_bsDate        GX_IDS_STYLE_DBDATE
		// AFX_RFX_TEXT:        pDbData->m_bsText        GX_IDS_STYLE_DBTEXT
		// AFX_RFX_ATEXT:       pDbData->m_bsText        GX_IDS_STYLE_DBTEXT
		// AFX_RFX_WTEXT:       pDbData->m_bsText        GX_IDS_STYLE_DBTEXT
		// AFX_RFX_LONGBINARY:  pDbData->m_bsBinary      GX_IDS_STYLE_DBBINARY
		// AFX_RFX_BINARY:      pDbData->m_bsBinary      GX_IDS_STYLE_DBBINARY
		// [VC7] Map new text types to AFX_RFX_TEXT.

		CGXStyle styleDefault;

		// Boolean fiels will be displayed with horizontally centered checkboxes
		pDbData->m_bsBoolean = pStyMap->RegisterStyle(
						GX_IDS_STYLE_DBBOOLEAN,
						CGXStyle()
							.SetControl(GX_IDS_CTRL_CHECKBOX3D)
							.SetHorizontalAlignment(DT_CENTER)
							.SetVerticalAlignment(DT_VCENTER),
						TRUE);

		// All other field types will be displayed with the standard style settings
		pDbData->m_bsNumeric = pStyMap->RegisterStyle(GX_IDS_STYLE_DBNUMERIC, styleDefault, TRUE);
		pDbData->m_bsDate = pStyMap->RegisterStyle(GX_IDS_STYLE_DBDATE, styleDefault, TRUE);
		pDbData->m_bsText = pStyMap->RegisterStyle(GX_IDS_STYLE_DBTEXT, styleDefault, TRUE);
		pDbData->m_bsBinary = pStyMap->RegisterStyle(GX_IDS_STYLE_DBBINARY, styleDefault, TRUE);

		// Style for appearance of deleted rows
		pDbData->m_bsDeletedRows = pStyMap->RegisterStyle(
						GX_IDS_STYLE_DELETEDROWS,
						CGXStyle()
							.SetTextColor(RGB(192,192,192))
							.SetInterior(CGXBrush().SetPattern(4))
							.SetEnabled(FALSE),
						TRUE);

		// Open the query
		if (pRecordset != NULL)
			OpenRecordset();
	}
	else
	{
		// if document has been read from archive, and
		// recordset is not yet open, try to open it.
		// column specific data should have been
		// read from the archive.
		if (pRecordset && (!pRecordset->IsOpen() || pRecordset->m_nFields == 0))
		{
			TRY
			{
				pRecordset->Open();
			}
			CATCH(CDBException, e)
			{
				// Tell them the reason it failed to open
				GX_THROW_LAST
				AfxMessageBox(e->m_strError);
				return;
			}
			AND_CATCH_ALL(e)
			{
				GX_THROW_LAST
				return;
			}
			END_CATCH_ALL
		}

#if _MFC_VER >= 0x0420
		LoadFieldInfo();
#endif
	}

}

// OpenRecordset
//
// Opens the recordset (only if not yet opened),
// initializes the columns (width, field name,
// length, base style) and redraws the grid.
//

void CGXODBCGrid::OpenRecordset()
{
	CGXBrowseParam* pBrowseData = GetBrowseParam();
	CRecordset* pRecordset = OnGetRecordset();

	// recordset must be allocated already
	if (pRecordset == NULL)
	{
		TRACE0("Warning: OpenRecordset is called without a valid CRecordset object.\n");
		TRACE0("No records will be displayed in the grid.\n");
	}

	// Reset the current cell
	ResetCurrentCell();
	SetCurrentCell(0,0);
	pBrowseData->m_bEOFSeen = FALSE;
	pBrowseData->m_nRecordLastSeen = -1;
	pBrowseData->m_awColIndex.RemoveAll();
	pBrowseData->m_awRowIndex.RemoveAll();

	m_nTopRow = GetFrozenRows() + 1;
	m_nLeftCol = GetFrozenCols() + 1;


	while (InWaitForDataSource())
		NULL;

	// Open the recordset, if it has not yet been opened
	if (pRecordset && (!pRecordset->IsOpen() || pRecordset->m_nFields == 0))
	{
		CGXWaitCursor theWait;

		TRY
		{
			pRecordset->Open();
		}
		CATCH(CDBException, e)
		{
			// Tell them the reason it failed to open
			GX_THROW_LAST
			AfxMessageBox(e->m_strError);
			return;
		}
		AND_CATCH_ALL(e)
		{
			GX_THROW_LAST
			return;
		}
		END_CATCH_ALL
	}

	while (InWaitForDataSource())
		NULL;

	if (pRecordset && pRecordset->IsOpen() && !pRecordset->IsEOF())
	{
		pRecordset->MoveFirst();

		// backward scrolling is necessary
		ASSERT(pRecordset->CanScroll());
	}

	CGXDbParam* pParam = (CGXDbParam*) GetParam();

	// Determine if cells can be changed
	StandardStyle().SetReadOnly(!CanUpdate());

	// but make sure titles and default values can be set
	// while initializing the grid
	BOOL bLock = pParam->IsLockReadOnly();
	pParam->SetLockReadOnly(FALSE);

	// Empty undo and redo list
	pParam->EmptyUndoList();
	pParam->EmptyRedoList();

	// Initialize cells
	BOOL bOldEnableUndo = pParam->IsEnableUndo();
	pParam->EnableUndo(FALSE);

	// Disable any drawing for the following operations
	BOOL bOldLockUpdate = LockUpdate();

	OnTestGridDimension(1, 1);

	// Determine field information:
	// a) determine field information: name, base style, length
	// b) store the field name with SetStyleRange()
	// c) store the column width with SetColWidth()

	CGXStyle* pStyle = CreateStyle();

	// Delete contents of CGXData
	pParam->GetData()->StoreRowCount(0);
	pParam->GetData()->StoreColCount(0);

	short nFieldCount = pRecordset ? (short) pRecordset->m_nFields : (short) 0;

	// Reserve space in CGXData
	pParam->GetData()->StoreRowCount(1);
	pParam->GetData()->StoreColCount(nFieldCount + GetHeaderCols());

	pParam->m_nFields = nFieldCount;

#if _MFC_VER >= 0x0420
	LoadFieldInfo();
#endif

	for (short nField = 0; nField < nFieldCount; nField++)
	{
		// column info for column nCol in grid/field nField in CRecordset
		ROWCOL nCol = (ROWCOL) nField + 1 + GetHeaderCols();

#if _MFC_VER >= 0x0420
		CGXFieldInfo& fieldInfo = pParam->m_apFieldInfo[nField];
#else
		CFieldInfo fieldInfo;
		pRecordset->GetFieldInfo(nField, &fieldInfo);
#endif

		// a) determine the base style
		WORD wBaseStyle;        // base style id
		CString strName;
		long cbLength;

		// User can override InitColInfo to hook into default initialization of columns
		BOOL bColumnSettingsLocked = FALSE;
		OnInitColInfo(nCol, fieldInfo, strName, cbLength, wBaseStyle, &bColumnSettingsLocked);

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


#if _MFC_VER < 0x0300
	// In 16-Bit, CRecordset sometimes does not get the records
	// at first open. They all contained 0 values.

	// The following Requery solved the problem

	if (pRecordset && pRecordset->IsOpen())
		pRecordset->Requery();

	while (InWaitForDataSource())
		NULL;
#endif

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
}

#if _MFC_VER >= 0x0420
void CGXODBCGrid::LoadFieldInfo()
{
	CRecordset* pRecordset = OnGetRecordset();
	if (pRecordset == NULL)
		return;

	CGXDbParam* pParam = (CGXDbParam*) GetParam();

	// Initialize field info
	if (pParam->m_apFieldInfo)
		delete[] pParam->m_apFieldInfo;

	short nFieldCount = pRecordset ? (short) pRecordset->m_nFields : (short) 0;
	pParam->m_apFieldInfo = new CGXFieldInfo[nFieldCount];

	for (short nfield = 0; nfield < nFieldCount; nfield++)
	{
		CGXFieldInfo& fieldInfo = pParam->m_apFieldInfo[nfield];

		CODBCFieldInfo fld;
		pRecordset->GetODBCFieldInfo(nfield, fld);

		CFieldInfo& ci = pRecordset->m_rgFieldInfos[nfield];

		fieldInfo.nField = nfield+1;
		fieldInfo.strName = fld.m_strName;

		switch (fld.m_nSQLType)
		{
		case SQL_BIT:
		case SQL_TINYINT:
		case SQL_SMALLINT:
		case SQL_INTEGER:
		case SQL_REAL:
		case SQL_FLOAT:
		case SQL_DOUBLE:
		case SQL_DATE:
		case SQL_TIME:
		case SQL_TIMESTAMP:
		case SQL_DECIMAL:   // ODBC default xfer type
		case SQL_NUMERIC:   // ODBC default xfer type
		case SQL_WCHAR:
		case SQL_WVARCHAR:
		case SQL_WLONGVARCHAR:
		case SQL_CHAR:
		case SQL_VARCHAR:
		case SQL_LONGVARCHAR:
		case SQL_BIGINT:
			fieldInfo.nDataType = ci.m_nDataType;
			break;

		case SQL_BINARY:
		case SQL_VARBINARY:
			fieldInfo.nDataType = AFX_RFX_BINARY;
			break;

		case SQL_LONGVARBINARY:
			fieldInfo.nDataType = AFX_RFX_LONGBINARY;
			break;
		}
	}

	// Now, recollect all the value references
	POSITION pos = pRecordset->m_mapFieldIndex.GetStartPosition();
	void* pvKey;
	void* pvIndex;
	while (pos)
	{
		pRecordset->m_mapFieldIndex.GetNextAssoc(pos, pvKey, pvIndex);

		// Cached value is short not ptr
		pParam->m_apFieldInfo[(int)(SEC_DWORD) pvIndex-1].pv = pvKey;
	}
}
#endif

long CGXODBCGrid::GetColSize(ROWCOL nCol)
{
	CRecordset* pRecordset = OnGetRecordset();

	// recordset must be allocated already
	if (pRecordset == NULL)
		return 0;

	ASSERT_VALID(pRecordset);
	ASSERT(pRecordset->IsKindOf(RUNTIME_CLASS(CRecordset)));

	CGXDbParam* pParam = (CGXDbParam*) GetParam();
	short nField = (short) GetFieldFromCol(nCol);
#if _MFC_VER >= 0x0420
	CGXFieldInfo& fieldInfo = pParam->m_apFieldInfo[nField];
#else
	CFieldInfo fieldInfo;
	pRecordset->GetFieldInfo(nField, &fieldInfo);
#endif

	WORD wBaseStyle;        // base style id
	CString strName;
	long cbLength;

	// User can override InitColInfo to hook into default initialization of columns
	OnInitColInfo(nCol, fieldInfo, strName, cbLength, wBaseStyle);

	return cbLength;
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
// check before using it in any override

void CGXODBCGrid::OnInitColInfo(ROWCOL nCol,
	const CGXFieldInfo& fieldInfo,
	CString& strName,
	long& cbLength,
	WORD& wBaseStyle,
	BOOL* pbColumnSettingsLocked/* = NULL*/)
{
	CGXDbParam* pDbData = GetDbParam();
	CRecordset* pRecordset = OnGetRecordset();

	// see OnInitialUpdate() above for the table of CGXODBCGrid base styles

	switch(fieldInfo.nDataType)
	{
	case AFX_RFX_BOOL:        wBaseStyle = pDbData->m_bsBoolean; break;
	case AFX_RFX_BYTE:        wBaseStyle = pDbData->m_bsNumeric; break;
	case AFX_RFX_INT:         wBaseStyle = pDbData->m_bsNumeric; break;
	case AFX_RFX_LONG:        wBaseStyle = pDbData->m_bsNumeric; break;
	case AFX_RFX_SINGLE:      wBaseStyle = pDbData->m_bsNumeric; break;
	case AFX_RFX_DOUBLE:      wBaseStyle = pDbData->m_bsNumeric; break;
#if _MFC_VER >= 0x0423
	case AFX_RFX_OLEDATE:
#endif
	case AFX_RFX_DATE:        wBaseStyle = pDbData->m_bsDate;    break;
#if _MFC_VER >= 0x0420
	case AFX_RFX_TIMESTAMP:   wBaseStyle = pDbData->m_bsDate;    break;
#endif
    // [VC7] Map new text types to AFX_RFX_TEXT.
#if _MFC_VER >= 0x0700
	case AFX_RFX_ATEXT:
	case AFX_RFX_WTEXT:
#endif
	case AFX_RFX_TEXT:        wBaseStyle = pDbData->m_bsText;    break;
	case AFX_RFX_LONGBINARY:  wBaseStyle = pDbData->m_bsBinary;  break;
	case AFX_RFX_BINARY:      wBaseStyle = pDbData->m_bsBinary;  break;
	default:
		TRACE0("Unknown Datatype\n");
		ASSERT(FALSE);
		AfxThrowNotSupportedException();
	}

	// column length
	{
		SWORD cbColName;
		TCHAR szColName[255];
		SWORD fSqlType;     // SQL type
#ifdef _WIN64
		UINT64 cbColDef;
#else	// WIN32
		UDWORD cbColDef;    // Precision
#endif	// _WIN64
		SWORD ibScale;      // scale
		SWORD fNullable;    // is column nullable
		RETCODE nRetCode;

		short nField = GetFieldFromCol(nCol);

        // [VC7] SQlDescribeCol complains if the proper string type is
        // not passed to the column Name.		
		AFX_SQL_SYNC( SQLDescribeCol(pRecordset->m_hstmt, (SWORD) (nField+1),
		  (SQLTCHAR *)szColName, (SWORD) sizeof(szColName), &cbColName,
		  &fSqlType, &cbColDef, &ibScale, &fNullable) );        

		if (!pRecordset->Check(nRetCode))
			pRecordset->ThrowDBException(nRetCode);

		// Room for decimal point and sign in string
		if(fSqlType == SQL_NUMERIC || fSqlType == SQL_DECIMAL)
			cbColDef += 2;
		cbLength = GetDisplaySize(fieldInfo, (long)cbColDef);
		strName = (TCHAR *)szColName;
	}

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
}

// GetDisplaySize
//
// This method is called from the virtual method OnInitColInfo to
// determine the column size. If you prefer other default column
// widths for special columns, you should override GetDisplaySize.

long CGXODBCGrid::GetDisplaySize(const CGXFieldInfo& fieldInfo, long cbColDef)
{
	CGXDbParam* pDbParam = GetDbParam();

	// computes column size
	switch(fieldInfo.nDataType)
	{
	case AFX_RFX_BOOL:
		return 4;

	case AFX_RFX_BYTE:
		return 3;

	case AFX_RFX_INT:
		return 6;

	case AFX_RFX_LONG:
		return 11;

	case AFX_RFX_SINGLE:
	case AFX_RFX_DOUBLE:
		return MAX_NUM_STRING_SIZE;

#if _MFC_VER >= 0x0420
	case AFX_RFX_TIMESTAMP:
#endif
#if _MFC_VER >= 0x0423
	case AFX_RFX_OLEDATE:
#endif
	case AFX_RFX_DATE:
		// NOTE: This is the maximum supported size of a timestamp, not the average size.
		// This size accounts for intervals (the :FFF) which is not supported by many databases.
		return 24;  // DTB: 'YYYY-MM-DD HH:MM:SS:FFF'

    // [VC7] Map new text types to AFX_RFX_TEXT.
#if (_MFC_VER >= 0x0700)
	case AFX_RFX_ATEXT:
	case AFX_RFX_WTEXT:
#endif
	case AFX_RFX_TEXT:
		return cbColDef;

	case AFX_RFX_LONGBINARY:
		// Memo fields
		if (pDbParam->m_bDisplayMemo)
			return INT_MAX;

	case AFX_RFX_BINARY:
		// not supported types, field will be hidden
		return 0;
	}
	return 0;
}

// CanUpdate
//
// TRUE if the data in the grid can be changed

BOOL CGXODBCGrid::CanUpdate()
{
	CRecordset* pRecordset = OnGetRecordset();
	return pRecordset && pRecordset->IsOpen() && pRecordset->CanUpdate();
}

// CanAppend
//
// TRUE if user shall be able to append new rows.
// Call CGXBrowserGrid::SetCanAppend(FALSE) if you want to disable this feature.

BOOL CGXODBCGrid::CanAppend()
{
	CRecordset* pRecordset = OnGetRecordset();
	return CGXBrowserGrid::CanAppend() && pRecordset && pRecordset->IsOpen() && pRecordset->CanAppend();
}

// DeleteRows
//
// Called to delete records from the CRecordset.
//
// Records will be deleted with pRecordset->Delete(); and
// after deleting the records the recordset will be requeried.

#ifndef _WINDU_SOURCE
extern "C" static int __cdecl __gxcomparelong(const void* p1, const void* p2)
#else
extern "C" int __cdecl __gxcomparelong(const void* p1, const void* p2)
#endif
{
	long l = *(long*) p1 - *(long*) p2;

	return (l>0) ? 1 : (l<0) ? -1 : 0;
}


// DeleteRows
//
// Example set:
//
// Row, RecordId, Row Id
// 1    a		   1
// 2    b		   2
// 3    c		   3
// 4    d		   4
// 5    e		   5
// 6    f		   6
// 7    g		   7
//
//
// Suppose you delete row 4 and 5. The result should look like this:
//
// NOTE: The record gets deleted in the recordset. Therefore
// row id for row 4 and 5 should not change:
//
// 1    a		   1
// 2    b		   2
// 3    c		   3
// 4    f		   4
// 5    g		   5
//
// The comments in the code refer to this sample to explain
// how DeleteRows works.

void CGXODBCGrid::DeleteRows(const CRowColArray& awRowStart, const CRowColArray& awRowEnd, BOOL* pbSuccess)
{
	if (pbSuccess != NULL)
		*pbSuccess = FALSE;

	CRecordset* prs = OnGetRecordset();
	CGXBrowseParam* pBrowseData = GetBrowseParam();

	if (prs == NULL || InWaitForDataSource() ||
		!prs->IsOpen() || !prs->CanUpdate())
		return;

	ROWCOL nEditRow, nEditCol;
	BOOL bCCell = GetCurrentCell(nEditRow, nEditCol);

	CDatabase* pdb = prs->m_pDatabase;

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

	BOOL bOldLock = LockUpdate(TRUE);

	// Empty undo/redo list
	BOOL bOldUndo = GetParam()->IsEnableUndo();
	GetParam()->EmptyUndoList();
	GetParam()->EmptyRedoList();
	GetParam()->EnableUndo(FALSE);

	BOOL bTrans = prs->CanTransact();
	if (bTrans)
		 pdb->BeginTrans();

	long* alRecords = NULL;

	TRY
	{
		// First, sort the array of records
		ROWCOL nCount = 0;
		int index;
		for (index = (int)awRowEnd.GetUpperBound(); index >= 0; index--)
			nCount += awRowEnd[index]-awRowStart[index]+1;

		int nIndex = 0;
		alRecords = new long[nCount];

		for (index = (int)awRowEnd.GetUpperBound(); index >= 0; index--)
		{
			ROWCOL nRecords = awRowEnd[index]-awRowStart[index]+1;
			for (ROWCOL n = 0; n < nRecords; n++)
				alRecords[nIndex++] = GetRecordFromRow(awRowStart[index]+n);
		}

		qsort(alRecords, (size_t) nCount, sizeof(long), __gxcomparelong);

		// Now we have all records from highest record to lowest record and we
		// remove the records:

		CRecordsetStatus rs;
		prs->GetStatus(rs);

		long lRecord = rs.m_lCurrentRecord;

		// Whenever one record is deleted we loop through m_awRowIndex and decrease all
		// m_awRowIndex that point to a record after the deleted record (and therefore
		// shifts up one record).
		//
		// In our sample we delete record 5 and 6:
		//
		// Row, RecordId, Row Id
		// 1    a		   1
		// 2    b		   2
		// 3    c		   3
		// 4    <del>	   4		// NOTE: m_awRowIndex is not changed
		// 5    <del>	   5
		// 6    f		   4		// NOTE: m_awRowIndex is decremented
		// 7    g		   5

		for (index = (int) nCount-1; index >= 0; index--)
		{
			// Delete record in recordset

			long lMove = alRecords[index]-lRecord;
			if (lMove != 0)
				prs->Move(lMove);
			lRecord = alRecords[index]-1;

			prs->Delete();

			while (InWaitForDataSource())
				NULL;

			prs->MovePrev();

			// Decerement m_awRowIndex entries that point to a record in the
			// recordset below the deleted record

			for (int n = 0; n <= pBrowseData->m_awRowIndex.GetUpperBound(); n++)
			{
				if (pBrowseData->m_awRowIndex[n] > alRecords[index]+GetHeaderRows()+1)
					pBrowseData->m_awRowIndex[n]--;
			}
		}

		// Now we removes m_awRowIndex entries for the deleted records::

		// Our sample will now look like this:

		// Row, RecordId, Row Id
		// 1    a		   1
		// 2    b		   2
		// 3    c		   3
		// 4	f		   4
		// 5    g		   5

		for (index = (int)awRowEnd.GetUpperBound(); index >= 0; index--)
		{
			if ((int) awRowStart[index] < pBrowseData->m_awRowIndex.GetSize())
				pBrowseData->m_awRowIndex.RemoveAt((int) awRowStart[index],
					min((int) awRowEnd[index], pBrowseData->m_awRowIndex.GetUpperBound())
					-(int) awRowStart[index]+1);
		}

		if (bTrans)
			pdb->CommitTrans();

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

		// Let CGXGridCore adjust hidden rows, row heights,
		// floating and covered cells, row styles.

		for (int i = (int)awRowEnd.GetUpperBound(); i >= 0; i--)
			CGXGridCore::StoreRemoveRows(awRowStart[i],awRowEnd[i]);

		// Reset high water mark
		pBrowseData->m_bEOFSeen = FALSE;
		pBrowseData->m_nRecordLastSeen = -1;

		// Requery
		if (prs->CanRestart())
		{
			CGXWaitCursor theWait;
			prs->Requery();

			while (InWaitForDataSource())
				NULL;
		}
	}
	CATCH(CDBException, e)
	{
		if (bTrans)
			pdb->Rollback();

		GX_THROW_LAST
		AfxMessageBox(e->m_strError, MB_ICONEXCLAMATION);
	}
	AND_CATCH_ALL(e)
	{
		if (bTrans)
			pdb->Rollback();

		GX_THROW_LAST
	}
	END_CATCH_ALL

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
}

// Requery
//
// Requeries the CRecordset. It is also necessary to reset
// the last seen record, so that OnTestGridDimension will not
// get confused.

void CGXODBCGrid::Requery()
{
	CGXBrowseParam* pBrowseData = GetBrowseParam();
	CRecordset* pRecordset = OnGetRecordset();

	if (pRecordset == NULL)
		return;

	// Save and reset current cell
	TransferCurrentCell();

	pBrowseData->m_bEOFSeen = FALSE;
	pBrowseData->m_nRecordLastSeen = -1;
	if (pRecordset && pRecordset->CanRestart())
	{
		CGXWaitCursor theWait;
#if _MFC_VER >= 0x0400
		pRecordset->Requery();
#else
		pRecordset->Close();
		pRecordset->Open();
#endif

		while (InWaitForDataSource())
			NULL;
	}

#if _MFC_VER >= 0x0420
	LoadFieldInfo();
#endif

	// Reinit current cell
	TransferCurrentCell(FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CGXODBCGrid overridables

// OnLoadCellStyle
//
// give the programmer the chance to load the value from data source
// or apply additional formattings at runtime

BOOL CGXODBCGrid::OnLoadCellStyle(ROWCOL nRow, ROWCOL nCol, CGXStyle& style, LPCTSTR pszExistingValue)
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

	CGXDbParam* pDbData = GetDbParam();
	CGXBrowseParam* pBrowseData = GetBrowseParam();
	CRecordset* pRecordset = OnGetRecordset();

	while (InWaitForDataSource())
		NULL;

	BOOL bRet = FALSE;

	int nField = GetFieldFromCol(nCol);

	if (pRecordset && pszExistingValue == NULL && nRow >= GetFirstRow())
	{
		// Get style from current record in data source
		if (!m_bNoValueNeeded && nField != -1 && nField < (short) pRecordset->m_nFields && MoveTo(nRow))
		{
			// Outline deleted records
			if ( pRecordset->IsDeleted())
			{
				// load base style for deleted rows
				style.SetBaseStyle(pDbData->m_bsDeletedRows);
				style.LoadBaseStyle(*GetParam()->GetStylesMap());
			}

			// transfer value from recordset and convert it to a string
			CString sValue;
			ConvertValueToString(nCol, sValue);
			style.SetValue(sValue);
		}
		else if (pBrowseData->m_bEOFSeen && nRow > GetLastRow())
			style.SetEnabled(FALSE);

		bRet = TRUE;
	}

	if (nField != -1 && nField < (short) pRecordset->m_nFields)
	{
#if _MFC_VER >= 0x0420
		CGXFieldInfo& ci = GetDbParam()->m_apFieldInfo[nField];
		switch (ci.nDataType)
#else
		CFieldInfo ci;
		pRecordset->GetFieldInfo(nField, &ci);
		switch (ci.nDataType)
#endif
		{
		case AFX_RFX_BOOL:
		case AFX_RFX_BYTE:
		case AFX_RFX_INT:
		case AFX_RFX_LONG:
		case AFX_RFX_SINGLE:
		case AFX_RFX_DOUBLE:
			style.SetValueType(GX_VT_NUMERIC);
		}
	}

	// You may override this method and apply additional
	// formattings specific to columns or depending on
	// the cells value or context, but be carefull
	// that you don't forget to call this base class
	// version.
	//
	// This method is also a nice hook for filling the choice
	// list of a combobox with the query results of another
	// recordset.

	return bRet;   // return TRUE if you have Existing the style object!
}

// ConvertValueToString
//
// ConvertValueToString() gets the CFieldInfo of the bound
// Field and converts the value to a string
//

void CGXODBCGrid::ConvertValueToString(ROWCOL nCol, CString& strRet)
{
	GetFieldData(GetFieldFromCol(nCol), strRet);
}

void CGXODBCGrid::GetFieldData(int nField, CString& strRet)
{
	CRecordset* pRecordset = OnGetRecordset();
#if _MFC_VER >= 0x0420
	CGXFieldInfo& ci = GetDbParam()->m_apFieldInfo[nField];
	GXGetODBCValueString(strRet, pRecordset, ci.pv, ci.nDataType, 0, GetDbParam()->m_bDisplayMemo);
#else
	CFieldInfo ci;
	pRecordset->GetFieldInfo(nField, &ci);
	GXGetODBCValueString(strRet, pRecordset, ci.pv, ci.nDataType, ci.dwSize, GetDbParam()->m_bDisplayMemo);
#endif
}

// MoveTo
//
// This method tries to position the recordset to the given
// row. It will return FALSE if the positioning failed.
//

#if _MFC_VER >= 0x0420 && USE_ABSOLUTEPOS

// In MFC 4.2, MoveTo can use the new SetAbsolutePosition method.

BOOL CGXODBCGrid::MoveTo(ROWCOL nRow)
{
	CGXBrowseParam* pBrowseData = GetBrowseParam();
	CRecordset* pRecordset = OnGetRecordset();

	if (pRecordset == NULL || !pRecordset->IsOpen() ||
		(long) (nRow-GetHeaderRows()) > OnGetRecordCount())
		return FALSE;

	long nRecord = GetRecordFromRow(nRow);

	CRecordsetStatus rs;
	pRecordset->GetStatus(rs);
	long nCurrentRecord = rs.m_lCurrentRecord; // pRecordset->GetAbsolutePosition();

	// fix problem with updating the recordset when there is
	// only one record
	if (nRecord == 0 && nCurrentRecord == 0 && pBrowseData->m_nEditMode == noMode)
	{
		pRecordset->MoveFirst();
		return TRUE;
	}

	if (nCurrentRecord == nRecord)
		return TRUE;

	// TRACE(_T("MoveTo(%ld)\n"), nRow);

	// make sure that recordset is not empty
	if (pRecordset->IsEOF() && pRecordset->IsBOF())
	{
		pBrowseData->m_bEOFSeen = TRUE;
		pBrowseData->m_nRecordLastSeen = -1;
		return FALSE;
	}

	try
	{
		if (abs(nCurrentRecord-nRecord) > pBrowseData->m_lMoveRecordWaitCursor)
		{
			// display wait cursor
			CGXWaitCursor theWait;
			pRecordset->SetAbsolutePosition(nRecord+1);
		}
		else
			pRecordset->SetAbsolutePosition(nRecord+1);
	}
	catch (CDBException* e)
	{
		GX_THROW_LAST
		e->Delete();
		return FALSE;
	}

	if (pRecordset->IsEOF())
	{
		pBrowseData->m_bEOFSeen = TRUE;
		return FALSE;
	}

	return TRUE;
}

#else

BOOL CGXODBCGrid::MoveTo(ROWCOL nRow)
{
	CGXDbParam* pBrowseData = GetDbParam();
	CRecordset* pRecordset = OnGetRecordset();

	while (InWaitForDataSource())
		NULL;

	if (pRecordset == NULL || !pRecordset->IsOpen() ||
		(long) (nRow-GetHeaderRows()) > OnGetRecordCount())
		return FALSE;

	if (pRecordset->IsEOF() && pRecordset->IsBOF())
	{
		pBrowseData->m_bEOFSeen = TRUE;
		pBrowseData->m_nRecordLastSeen = -1;
		return FALSE;
	}

	if (pRecordset->IsEOF())
		pRecordset->MovePrev();

	if (pRecordset->IsBOF())
		pRecordset->MoveNext();

	long nRecord = GetRecordFromRow(nRow);
	BOOL bWait = FALSE;

	CRecordsetStatus rs;
	pRecordset->GetStatus(rs);

	if (rs.m_bRecordCountFinal && !pBrowseData->m_bEOFSeen)
	{
		pBrowseData->m_bEOFSeen = TRUE;
		pBrowseData->m_nRecordCount = pRecordset->GetRecordCount();
		pBrowseData->m_nRecordLastSeen = pBrowseData->m_nRecordCount-1;
	}

	// fix problem with 4.2 when m_lCurrentRecord is too high
	if (rs.m_lCurrentRecord > pBrowseData->m_nRecordLastSeen)
	{
		pRecordset->MoveFirst();
		rs.m_lCurrentRecord = 0;
	}

	// fix problem with updating the recordset when there is
	// only one record
	if (nRecord == 0 && rs.m_lCurrentRecord == 0)
	{
		pRecordset->MoveFirst();
		return TRUE;
	}

	long lMove = nRecord-rs.m_lCurrentRecord;

	if (lMove == 0)
		return TRUE;

	if (lMove > 0 && !pRecordset->IsEOF() || lMove < 0 && !pRecordset->IsBOF())
	{
		TRY
		{
			// TRACE(_T("MoveTo(%ld) (lMove = %d)"), nRecord, lMove);

			// display wait cursor
			bWait = labs(lMove) > pBrowseData->m_lMoveRecordWaitCursor;

			if (bWait)
				AfxGetApp()->BeginWaitCursor();

			pRecordset->Move(lMove);
		}
		CATCH(CDBException, e)
		{
			// Trace them the reason it failed to move to the specified record
			TRACE(e->m_strError);
			GX_THROW_LAST
		}
		END_CATCH
	}

	if (bWait)
		AfxGetApp()->EndWaitCursor();

	// pRecordset->GetStatus(rs);
	// TRACE(_T("=> Status(%ld)\n"), rs.m_lCurrentRecord);

	if (pRecordset->IsEOF())
	{
		pBrowseData->m_bEOFSeen = TRUE;
		return FALSE;
	}

	return TRUE;
}

#endif // _MFC_VER >=0x0420 && USE_ABSOLUTEPOS

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

BOOL CGXODBCGrid::OnFlushRecord(ROWCOL nRow, CString* ps)
{
	CGXBrowseParam* pBrowseData = GetBrowseParam();
	CRecordset* pRecordset = OnGetRecordset();

	if (!CanUpdate())
	{
		if (ps)
			*ps = _T("Update failed because recordset is readonly.");
		else
			AfxThrowNotSupportedException();

		return FALSE;
	}

	TRY
	{
		// Sandwich CRecordset into Edit/AddNew and Update
		if (pBrowseData->m_nEditMode == addnew)
			pRecordset->AddNew();
		else
		{
			if (!MoveTo(nRow))
				AfxThrowNotSupportedException();
			pRecordset->Edit();
		}

		// Force writing dirty cells to CRecordset
		// Base class version contains the necessary functionality
		// to check all fields and call OnFlushCellValue

		CGXBrowserGrid::OnFlushRecord(nRow, NULL /* force throwing an exception */);

		// let the programmer additional fields in the recordset which
		// are not bound to the grid should not be visible to the user.

		PreUpdateRecordset(nRow);

		pRecordset->Update();

		while (InWaitForDataSource())
			NULL;
	}
	CATCH (CDBException, e)
	{
		if (e->m_nRetCode == AFX_SQL_ERROR_MULTIPLE_ROWS_AFFECTED)
		{
			// Accept change but redraw whole grid and display a message box
			Redraw(GX_INVALIDATE);
			SetWarningText(e->m_strError);
			return TRUE;
		}

		GridWnd()->SendMessage(WM_CANCELMODE, 0, 0);

		// Reset cursor
		if (!pRecordset->IsEOF())
		{
			pRecordset->SetFieldDirty(NULL, FALSE);
			pRecordset->MoveNext();
		}
		else if (!pRecordset->IsBOF())
		{
			pRecordset->SetFieldDirty(NULL, FALSE);
			pRecordset->MovePrev();
		}

		// ps is a valid CString if we shall catch the exception
		if (ps)
		{
			TRACE0("CGXODBCGrid::OnFlushRecord failed!\n");

			*ps = e->m_strError;
		}
		else
			// let exception fall through
			THROW_LAST();

		// failed, ...
		GX_THROW_LAST
		return FALSE;
	}
	AND_CATCH(CException, e)
	{
		// Reset cursor
		if (!pRecordset->IsEOF())
		{
			pRecordset->SetFieldDirty(NULL, FALSE);
			pRecordset->MoveNext();
		}
		else if (!pRecordset->IsBOF())
		{
			pRecordset->SetFieldDirty(NULL, FALSE);
			pRecordset->MovePrev();
		}

		// ps is a valid CString if we shall catch the exception
		if (ps)
		{
			TRACE0("CGXODBCGrid::OnFlushRecord failed!\n");

			ps->Empty();
		}
		else
			// let exception fall through
			THROW_LAST();

		// failed, ...
		GX_THROW_LAST
		return FALSE;
	}
	END_CATCH

	return TRUE;
}

// PreUpdateRecordset
//
// let the programmer update additional fields in the recordset which
// are not bound to the grid should not be visible to the user.
//
// This overridable is called from OnFlushRecord
// just before the pRecordset->Update method is called.

void CGXODBCGrid::PreUpdateRecordset(ROWCOL nRow)
{
	// Unused:
	nRow;
}


// OnFlushCellValue
//
// OnFlushCellValue is called from within CGXBrowserGrid::OnFlushRecord
// for all values changed in the current buffer.

// Note: You should override this method if you want to allow
// changing dbLongBinary, dbMemo or dbGUID fields.

void CGXODBCGrid::OnFlushCellValue(ROWCOL nRow, ROWCOL nCol, LPCTSTR pszChangedValue)
{
	// Unused:
	nRow;

	CRecordset* pRecordset = OnGetRecordset();

	// cannot handle this.
	if (pszChangedValue == NULL)
		return;

	int nField = GetFieldFromCol(nCol);

	if (nField < 0 || nField >= (short) pRecordset->m_nFields)
	{
		// This case will happen if the user did insert new
		// columns, e.g. a sum based on other fields in the row.
		// If you want to do this, you should make sure that CGXODBCGrid
		// does not try to write this values to the CRecordset.

		// Possible solution to avoid this message is to set
		// the column read-only or static or override this method.

		SetWarningText(_T("You have tried to modify the value of an unbound field!"));
		AfxThrowNotSupportedException();
		return;
	}

	SetFieldData(nField, pszChangedValue);
}

void CGXODBCGrid::SetFieldData(int nField, LPCTSTR pszChangedValue)
{
	CRecordset* pRecordset = OnGetRecordset();
	CString s;

	// Convert the data to text
#if _MFC_VER >= 0x0420
	CGXFieldInfo& ci = GetDbParam()->m_apFieldInfo[nField];
	if (!GXWriteODBCValueString(pszChangedValue, pRecordset, ci.pv, ci.nDataType, 0, &s, GetDbParam()->m_bDisplayMemo))
#else
	CFieldInfo ci;
	pRecordset->GetFieldInfo(nField, &ci);
	if (!GXWriteODBCValueString(pszChangedValue, pRecordset, ci.pv, ci.nDataType, ci.dwSize, &s, GetDbParam()->m_bDisplayMemo))
#endif
	{
		if (!s.IsEmpty())
		{
			SetWarningText(s);
			AfxThrowNotSupportedException();
		}
	}
}

// OnAddedNewRecord
//
// OnAddedNewRecord is called after a record has been suceesfully appended
// to the recordset.

void CGXODBCGrid::OnAddedNewRecord()
{
	FreeObjectCache();

	// When you add a new record to a snap shot,
	// the problem is that it is not automatically
	// visible. Therefore, I have to start a Requery().
	CRecordset* pRecordset = OnGetRecordset();
	CGXBrowseParam* pBrowseData = GetBrowseParam();

	// Some data sources can be redrawn smarter,
	// e.g. the Requery() is not necessary for all
	// data sources, but I have looked here for a
	// way which is the most safe.
	//
	// You might also check out if it is possible
	// to turn off the ODBC Cursor library. You
	// can normally turn off using this library
	// when browsing MS Access tables.

	// If you don't want this behaviour, you can
	// comment out the Requery and uncomment the following
	// line

	// ((CGXRecordset*) pRecordset)->m_lCurrentRecord++;

	pBrowseData->m_bEOFSeen = FALSE;
	long nSeen = pBrowseData->m_nRecordLastSeen;
	if(nSeen<0) nSeen =0;
	pBrowseData->m_nRecordLastSeen = -1;
	pRecordset->Requery();

	while (InWaitForDataSource())
		NULL;

	OnTestGridDimension(nSeen+2, 0);

	// you may also check out if the Redraw is necessary
	// for your specific data-source. Some ODBC drivers have the
	// problem that they get out of sync when I do not redraw
	// the grid.

	m_nLockRow = m_nLockCol = m_bLockStyleEdit = 0;
	Redraw(GX_INVALIDATE);
}

void CGXODBCGrid::OnMovedCurrentCell(ROWCOL nRow, ROWCOL nCol)
{
	CGXBrowserGrid::OnMovedCurrentCell(nRow, nCol);
}

void CGXODBCGrid::BeginTrans(LPCTSTR pszDescription)
{
	CRecordset* prs = OnGetRecordset();

	if (prs == NULL || !prs->IsOpen())
		return;

	CDatabase* pdb = prs->m_pDatabase;

	if (GetDbParam()->m_nTransactionPending++ == 0 && prs->CanTransact())
		// only one call to BeginTrans allowed with ODBC!
		pdb->BeginTrans();

	pszDescription;
}

void CGXODBCGrid::CommitTrans()
{
	CRecordset* prs = OnGetRecordset();

	if (prs == NULL || !prs->IsOpen())
		return;

	CDatabase* pdb = prs->m_pDatabase;

	if (--GetDbParam()->m_nTransactionPending == 0 && prs->CanTransact())
		pdb->CommitTrans();
}

void CGXODBCGrid::Rollback()
{
	GetDbParam()->m_nTransactionPending = 0;

	CRecordset* prs = OnGetRecordset();

	if (prs == NULL || !prs->IsOpen())
		return;

	CDatabase* pdb = prs->m_pDatabase;

	if (prs->CanTransact())
	{
		pdb->Rollback();
		Requery();
	}
}

// OnReplaceAll
//
// OnReplaceAll switches the CGXODBCGrid into a specific context
// before it calls the base class CGXGridCore::OnReplaceAll method.
//
// Special context is:
// - GXGetLastFRState()->bTransaction = FALSE;
// - pBrowseData->m_bDoReplaceAll = TRUE;
//
// This special settings make sure that each change in a cell
// will automatically update the recordset, and that if
// an update throws an exception CGXODBCGrid::OnReplaceAll
// is resonsible for catching this exception.
//

void CGXODBCGrid::OnReplaceAll(LPCTSTR lpszFind, LPCTSTR lpszReplace, BOOL bCase)
{
	CGXBrowseParam* pBrowseData = GetBrowseParam();

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
	BOOL bAppend = pBrowseData->m_bCanAppend;
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
	CATCH(CDBException, e)
	{
		Rollback();
		Requery();

		GX_THROW_LAST
		AfxMessageBox(e->m_strError);
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
// Sorting can be done by sorting the recordset with ODBC

void CGXODBCGrid::SortRows(CGXRange sortRange, CGXSortInfoArray& sortInfo, UINT flags /*= GX_UPDATENOW*/)
{
	// Unused: (in relase build)
	sortRange;

	ASSERT(sortRange.IsTable());
	// ASSERTION-> It is not supported to sort only a limited range
	// of rows with a CGXODBCGrid ->END

	MoveCurrentCell(GX_TOP);
	TransferCurrentCell();

	// Sort the grid with the columns specified in awCols.

	CGXDbParam* pParam = (CGXDbParam*) GetParam();

	pParam->EmptyUndoList();
	pParam->EmptyRedoList();

	if (pParam->m_nEditMode != noMode)
		Update();

	CRecordset* pSet = OnGetRecordset();

	pSet->m_strSort.Empty();

	for (int i = 0; i < sortInfo.GetSize(); i++)
	{
		short nField = (short) GetFieldFromCol(sortInfo[i].nRC);

#if _MFC_VER >= 0x0420
		CGXFieldInfo& fieldInfo = pParam->m_apFieldInfo[nField];
#else
		CFieldInfo fieldInfo;
		pSet->GetFieldInfo(nField, &fieldInfo);
#endif

		pSet->m_strSort += fieldInfo.strName;

		if (sortInfo[i].sortOrder == CGXSortInfo::descending)
			pSet->m_strSort += _T(" DESC");

		if (i+1 < sortInfo.GetSize())
			pSet->m_strSort += _T(", ");
	}

	SetSelection(0);
	Requery();
	Redraw(flags);

	// remember last sorted row
	GetParam()->m_nLastSortedRow = GX_INVALID;
	GetParam()->m_nLastSortedCol = sortInfo[0].nRC;

	GetParam()->m_bSortAscending = sortInfo[0].sortOrder == CGXSortInfo::ascending;

	MoveCurrentCell(GX_TOP);

	// Added this to make the selection move with the current cell in special mode
	MoveCurrentCellEx(GX_TOP);
}

#endif // _AFX_NO_DB_SUPPORT
