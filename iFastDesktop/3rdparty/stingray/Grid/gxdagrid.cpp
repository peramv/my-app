///////////////////////////////////////////////////////////////////////////////
// gxdagrid.cpp : implementation of CGXDaoGrid class
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

// compile this file only if DAO is supported
#if _MFC_VER >= 0x0400 && !defined(_AFX_NO_DAO_SUPPORT)

#ifdef _GXDLL
// used for MFC 2.5 Extension DLL
	#undef AFXAPI_DATA
	#define AFXAPI_DATA __based(__segname("_DATA"))
#endif

//Headers for imported classes

#ifndef _GXRESRC_H_
#include "grid\gxresrc.h"
#endif

#ifndef _GXBROWSE_H_
#include "grid\gxbrowse.h"
#endif

#ifndef _GXDAO_H_
#include "grid\gxdao.h"
#endif

#ifndef __AFXTEMPL_H__
#include <afxtempl.h>
#endif

#ifndef _GX_MAN_H__
#include "grid\gxman.h"
#endif

#ifndef _GX_OLEVARIANT_USER_H__
#include "grid\gxoleusr.h"
#endif

#ifndef _GX_DAO_BMP_H__
#include "grid\gxdaobmp.h"
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif


#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXDAGRID")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// Warnings
#pragma warning (push)
#pragma warning (disable: 4995)

const TCHAR szUnsupportedField[] = _T("Trying to store unsupported field type to data source");
const TCHAR szUnboundField[]     = _T("You have tried to modify the value of an unbound field!");

IMPLEMENT_SERIAL(CGXDaoParam, CGXBrowseParam, 0 /* schema number*/)

CGXDaoParam::CGXDaoParam()
{
	// Record count
	m_bEOFSeen = FALSE;
	m_nRecordCount = -1;
	m_nRecordLastSeen = -1;

	// Record count increment
	m_nRecordCountInc = 500;

	// Caching
	m_nCacheSize = 100;
	m_nRowCacheStart = GX_INVALID;

	// Display wait cursor when moving more than the
	// specified number of records in the recordset.
	m_lMoveRecordWaitCursor = 500;

	// display Memo fields (default)
	m_bDisplayMemo = TRUE;

	// default is that the DAO grid will ignore binary data
	m_bIgnoreBinaryData = TRUE;
}

CGXDaoParam::~CGXDaoParam()
{
}

void CGXDaoParam::Serialize(CArchive& ar)
{
	CGXBrowseParam::Serialize(ar);

	// version 2 from OG 7.0
	static const WORD wVersion = 2;
	WORD wActualVersion = wVersion;

	ASSERT_VALID( this );

	if (ar.IsStoring())
	{
		ar << wVersion;
		ar << m_bIgnoreBinaryData;
	}
	else
	{
		// Check for version first
		ar >> wActualVersion;
		if( wActualVersion > wVersion )
		{
#ifdef _DEBUG
			TRACE0( "Incompatible format while reading CGXDaoParam" );
			TRACE2("in %s at line %d\n", __FILE__, __LINE__);
			ASSERT(0);
			// ASSERTION-> Wrong version detected while reading object ->END
#endif
			AfxThrowArchiveException(CArchiveException::badSchema);
			return;
		}

		if(wActualVersion >=2)
			ar >> m_bIgnoreBinaryData;
		else
			m_bIgnoreBinaryData = TRUE;
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
			m_bsCurrency = pStyMap->GetBaseStyleId(GX_IDS_STYLE_DBCURRENCY);
			m_bsDate = pStyMap->GetBaseStyleId(GX_IDS_STYLE_DBDATE);
			m_bsText = pStyMap->GetBaseStyleId(GX_IDS_STYLE_DBTEXT);
			m_bsBinary = pStyMap->GetBaseStyleId(GX_IDS_STYLE_DBBINARY);
			m_bsMemo = pStyMap->GetBaseStyleId(GX_IDS_STYLE_DBMEMO);
			m_bsGUID = pStyMap->GetBaseStyleId(GX_IDS_STYLE_DBGUID);
			m_bsDeletedRows = pStyMap->GetBaseStyleId(GX_IDS_STYLE_DELETEDROWS);
		}
	}
}

// Copying attributes from one param into another will not initialize the param object
// you have to reinitialize the param with a new CDaoRecordset for it to become usable.
CGXDaoParam& CGXDaoParam::operator=(const CGXDaoParam& p)
{
	CGXBrowseParam::operator=(p);
	m_bIgnoreBinaryData = p.m_bIgnoreBinaryData;
	m_bDisplayMemo = p.m_bDisplayMemo;
	m_bsBoolean = p.m_bsBoolean;
	m_bsNumeric = p.m_bsNumeric;
	m_bsDate = p.m_bsDate;
	m_bsText = p.m_bsText;
	m_bsBinary = p.m_bsBinary;
	m_bsDeletedRows = p.m_bsDeletedRows;
	m_bsCurrency = p.m_bsCurrency;
	m_bsGUID = p.m_bsGUID;
	m_bsMemo = p.m_bsMemo;
	// The rest of the members help stay in sync with the external data and are hence ignored
	// since this has to be reinitialized with a new CDaoRecordset
	return *this;
}

/////////////////////////////////////////////////////////////////////////////
// CGXDaoGrid

CGXDaoGrid::CGXDaoGrid(CWnd* pGridWnd, CDocument* pGridDoc, BOOL bIsViewContext)
	: CGXBrowserGrid(pGridWnd, pGridDoc, bIsViewContext)
{
	m_pRecordset = NULL;
	m_nLastRecord = -1;

	m_strBinDescrip.LoadString(GX_IDS_BINDESCRIP);
}

CGXDaoGrid::~CGXDaoGrid()
{
}

/////////////////////////////////////////////////////////////////////////////
// CGXDaoGrid record count

// a) Typical case: MS Access table
//    - CDaoRecordset::GetRecordCount() returns the last seen record
//      OnTestGridDimension will increase the record count with
//      pBrowseData->m_nRecordCountInc records at a time.
//
// b) Attached tables or ODBC databases
//    - CDaoRecordset::GetRecordCount() will always return -1
//      OnTestGridDimension will increase the record count with
//      pBrowseData->m_nRecordCountInc records at a time.
//
// c) Any table type
//    - If you know the record count, e.g. if you want to determine
//      the record count by calling "SELECT COUNT(*)", you should
//      override OnGetRecordCount(). Calling OnTestGridDimension() will
//      have no effect when OnGetRecordCount() returns a valid value.
//
// NOTE: If you want that the grid determines the record count
// so that there is no further record count testing necessary,
// you can call OnTestGridDimension(GX_MAXROWCOL, 0) from your
// OnInitialUpdate() routine.

long CGXDaoGrid::SyncPosition()
{
	CDaoRecordset* pRecordset = OnGetRecordset();

	BOOL bReset = TRUE;

	if (m_nLastRecord != -1)
	{
		try
		{
			pRecordset->SetBookmark(m_varLastRecord);
			bReset = FALSE;
		}
		catch (CDaoException* e)
		{
			// Trace them the reason it failed to move to the specified record
			// TRACE(e->m_pErrorInfo->m_strDescription);
			// TRACE(_T(" - Exception has been catched and resolved in CGXDaoGrid::SyncPosition\n"));
			GX_THROW_LAST
			e->Delete();
		}
	}

	if (bReset)
	{
		m_nLastRecord = 0;
		try
		{
			pRecordset->MoveFirst();
			m_varLastRecord = pRecordset->GetBookmark();
		}
		catch (CDaoException* e)
		{
			// in case all records have been delete MoveFirst fails ...
			GX_THROW_LAST
			e->Delete();
		}
	}

	return m_nLastRecord;
}

void CGXDaoGrid::MoveToPosition(long nRecord, BOOL bSync)
{
	CDaoRecordset* pRecordset = OnGetRecordset();

	if (bSync)
		SyncPosition();

	long lMove = nRecord-m_nLastRecord;

	if (lMove == 0)
		return;

	if (lMove > 0 && !pRecordset->IsEOF() || lMove < 0 && !pRecordset->IsBOF())
	{
		try
		{
			pRecordset->Move(lMove);
			m_varLastRecord = pRecordset->GetBookmark();
			m_nLastRecord = nRecord;
		}
		catch (CDaoException* e)
		{
			/*
			// Trace them the reason it failed to move to the specified record
			TCHAR   szCause[255];

			e->GetErrorMessage(szCause, 255);
			TRACE(szCause);
			TRACE(_T(" - Exception has been catched and resolved in CGXDaoGrid::MoveToPosition\n"));
			*/
			GX_THROW_LAST
			e->Delete();

			// Booksmark are out of sync when we scrolled past the recordset
			// Therefore, we reset them and SyncPosition will call MoveFirst
			m_nLastRecord = -1;
		}
	}
}

void CGXDaoGrid::OnTestGridDimension(ROWCOL nLastRow, ROWCOL nLastCol)
{
	CGXBrowseParam* pBrowseData = GetBrowseParam();
	CDaoRecordset* pRecordset = OnGetRecordset();

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
	// sometimes returns too large values when used with dbOpenTable recordsets
	pBrowseData->m_nRecordCount = pRecordset->GetType() == dbOpenTable ? -1 : pRecordset->GetRecordCount();

	// the record count should increase with a given increment, e.g. 500 rows at a time
	if (lRecord != LONG_MAX && pBrowseData->m_nRecordCountInc > 1 && lRecord > 0)
		// rounds up lRecord to the next possible increment
		lRecord = ((lRecord-1) / pBrowseData->m_nRecordCountInc + 1) * pBrowseData->m_nRecordCountInc;

	BOOL bWait = FALSE;

	// First case: is record set empty?
	if (pRecordset->IsBOF() && pRecordset->IsEOF())
	{
		pBrowseData->m_bEOFSeen = TRUE;
		pBrowseData->m_nRecordLastSeen = -1;
	}
	// Second case: we can use CRecordset::GetRecordCount
	else if (CanUseRecordCount())
	{
		long nCurrentRecord = SyncPosition();
		long nRecordLastSeen = pBrowseData->m_nRecordCount;
		ROWCOL nLastRow = nRecordLastSeen+GetHeaderRows()+1;

		try
		{
			// quickly move to last seen record
			bWait = abs(nCurrentRecord-lRecord) > pBrowseData->m_lMoveRecordWaitCursor;
			if (bWait)
				AfxGetApp()->BeginWaitCursor();

			if (nRecordLastSeen != nCurrentRecord)
				MoveToPosition(nRecordLastSeen, FALSE);

			// and try to position to record lRecord
			while (nRecordLastSeen < lRecord && !pRecordset->IsEOF())
			{
				pRecordset->MoveNext();
				nRecordLastSeen = pRecordset->GetRecordCount()-1;
			}

		}
		catch (CDaoException* e)
		{
			// Trace them the reason it failed to move to the specified record
			TRACE(e->m_pErrorInfo->m_strDescription);
			GX_THROW_LAST
			e->Delete();
		}

		// Now, save the record
		pBrowseData->m_nRecordLastSeen = pRecordset->GetRecordCount()-1;
		pBrowseData->m_bEOFSeen = pRecordset->IsEOF();

		// Support for merge cells and floating cells
		// New rows have to be checked
		DelayFloatCells(CGXRange().SetRows(nLastRow, GetRowCount()));
		DelayMergeCells(CGXRange().SetRows(nLastRow, GetRowCount()));
	}
	// Third case: we have to manually move through the records
	else
	{
		long nCurrentRecord = SyncPosition();

		if(pBrowseData->m_nRecordLastSeen < m_nLastRecord)
			pBrowseData->m_nRecordLastSeen = m_nLastRecord;

		// quickly move to last seen record
		long nRecordLastSeen = pBrowseData->m_nRecordLastSeen+1;

		ROWCOL nLastRow = nRecordLastSeen+GetHeaderRows()+1;

		try
		{
			bWait = abs(nCurrentRecord-lRecord) > pBrowseData->m_lMoveRecordWaitCursor;
			if (bWait)
				AfxGetApp()->BeginWaitCursor();

			if (nRecordLastSeen != nCurrentRecord)
				MoveToPosition(nRecordLastSeen, FALSE);

			// and try to position to record lRecord
			while (nRecordLastSeen <= lRecord && !pRecordset->IsEOF())
			{
				pRecordset->MoveNext();
				nRecordLastSeen++;
			}
		}
		catch (CDaoException* e)
		{
			// Trace them the reason it failed to move to the specified record
			TRACE(e->m_pErrorInfo->m_strDescription);
			GX_THROW_LAST
			e->Delete();
		}

		// Now, save the record and the "EOF seen" state
		pBrowseData->m_bEOFSeen = pRecordset->IsEOF();
		pBrowseData->m_nRecordLastSeen = nRecordLastSeen-1;

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
// If you know the extact record count in advance (maybe by using a "SELECT COUNT(*)"),
// you can override thise method and return the record count.
//

long CGXDaoGrid::OnGetRecordCount()
{
	CGXBrowseParam* pBrowseData = GetBrowseParam();
	CDaoRecordset* pRecordset = OnGetRecordset();

	if (pRecordset == NULL || !pRecordset->IsOpen())
		return 0;

	// check if record count is known
	if (pBrowseData->m_bEOFSeen)
		return pBrowseData->m_nRecordLastSeen+1;

	// last record has not been seen yet, record count is unknown
	return LONG_MAX;
}

// OnGetRecordset()
//
// Returns a pointer to the attached CDaoRecordset
//

CDaoRecordset* CGXDaoGrid::OnGetRecordset()
{
	return m_pRecordset;
}

// CanUseRecordCount()
//
// This method is called to determine if CGXDAOGrid can rely on the
// value returned by pRecordset->GetRecordCount().
//
// If the return value is TRUE, the grid will determine the record count
// by calling the CDaoRecordset::GetRecordCount() member. Using this
// method has the advantage that there are not so many MoveNext()
// calls necessary.
//
// If the return value is FALSE, the grid will maintain the record count
// by using the pBrowseData->m_nRecordLastSeen member variable.
//
// Typically, access tables support GetRecordCount(). ODBC data sources
// and attached tables normally do not support GetRecordCount().

BOOL CGXDaoGrid::CanUseRecordCount()
{
	CGXBrowseParam* pBrowseData = GetBrowseParam();

	// pBrowseData->m_nRecordCount is initialized with pRecordset->GetRecordCount();
	// in OnTestGridDimension().

	return pBrowseData->m_nRecordCount != -1;
}

/////////////////////////////////////////////////////////////////////////////
// CGXDaoGrid support for the DAO Caching mechanism
//

void CGXDaoGrid::OnFillCache()
{
	CGXBrowseParam* pBrowseData = GetBrowseParam();
	CDaoRecordset* pRecordset = OnGetRecordset();

	// Rather than waiting for the cache to be filled with records as they
	// are fetched, this method explicitly fills the cache by calling the
	// CDaoRecordset::OnFillCache member function. This is a faster way to fill
	// the cache because OnFillCache fetches several records at once instead of
	// one at a time. For example, while each screenful of records is being
	// displayed, OnFillCache fetches the next screenful of records.
	//
	// NOTE: This only improves performance with external data sources
	// or attached tables. Tables directly created in MS Access do not
	// benefit from the DAO caching mechanism.

	if (pBrowseData->m_nCacheSize != -1
		&& pRecordset
		&& pRecordset->IsOpen()
		&& pRecordset->GetType() != dbOpenTable
		&& OnGetRecordCount() > 0
		&& pRecordset->CanBookmark())
	{
		ROWCOL nRowStart = GetTopRow();
		if (pBrowseData->m_nRowCacheStart == GX_INVALID
			|| nRowStart < pBrowseData->m_nRowCacheStart
			|| CalcBottomRowFromRect(GetGridRect())
				> pBrowseData->m_nRowCacheStart + pBrowseData->m_nCacheSize)
		{
			pBrowseData->m_nRowCacheStart = nRowStart;
			if (MoveTo(nRowStart))
			{
				COleVariant bookmark = pRecordset->GetBookmark();
				pRecordset->SetCacheStart(bookmark);
				pRecordset->SetCacheSize(pBrowseData->m_nCacheSize);
				pRecordset->FillCache();
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CGXDaoGrid diagnostics

#ifdef _DEBUG
void CGXDaoGrid::AssertValid() const
{
}

void CGXDaoGrid::Dump(CDumpContext& dc) const
{
	dc;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGXDaoGrid message handlers

// Initialization
//
// NOTE: CGXDaoGrid fully supports the MFC document/view architecture.
// If you want to be able to open several views on the same DAO recordset,
// you should override the OnInitialUpdate routine in your view class.
//
// Example:
//
// void CDaoqueryView::OnInitialUpdate()
// {
//  SetRecordset(&GetDocument()->m_dynamicSet);
//
//  SetParam(&GetDocument()->m_param, FALSE);   // Share CGXDaoParam object among views
//
//  CGXDaoRecordView::OnInitialUpdate();
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

void CGXDaoGrid::OnGridInitialUpdate()
{
	// check parameter object
	CGXGridParam* pParam = GetParam();

	BOOL bIsInit = FALSE;
		// bIsInit = TRUE if data need to be initialized
		// bIsInit = FALSE if this is only a new view on the same cursor

	if (pParam == NULL)
		SetParam(pParam = new CGXDaoParam);
	else
		// parameter object has already been attached in derived class, so
		// we only need to check if we must initialize it
		bIsInit = pParam->IsInit();
			// CGXGridCore::OnGridInitialUpdate() will set pParam->IsInit() = TRUE
			// So, if OnGridInitialUpdate is called for a new view on the same data,
			// bIsInit will be TRUE

	ASSERT(pParam->IsKindOf(RUNTIME_CLASS(CGXDaoParam)));
	// ASSERTION-> This is not a CGXDaoParam object.
	// You did probably use a CGXGridParam object instead. ->END

	CGXDaoParam* pDaoData = GetDaoParam();

	CGXBrowserGrid::OnGridInitialUpdate();

	InitBrowserSettings();  // Default browser appearance

	// recordset must be allocated already
	CDaoRecordset* pRecordset = OnGetRecordset();
	//ASSERT_VALID(pRecordset);
	//ASSERT(pRecordset->IsKindOf(RUNTIME_CLASS(CDaoRecordset)));

	// reusable style object for user attributes
	if (pDaoData->m_pTmpStyle == NULL)
		pDaoData->m_pTmpStyle = CreateStyle();

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

	if (!bIsInit)
	{
		// Register individual base style for any database field type
		// each database field type will have its own base style, so that
		// a field types special appearance or control type can be easily
		// changed through the base style.
		//
		// If you want for example change all dbByte columns to be associated with
		// a spin-edit control, simply call
		//      BaseStyle(pDaoData->m_bsByte).SetControl(GX_IDS_CTRL_SPINEDIT);
		//
		// Table of base styles:
		//
		// Database Field Type  Base Style Id             String Resource Id
		// ------------------------------------------------------------------------
		// dbBoolean:           pDaoData->m_bsBoolean     GX_IDS_STYLE_DBBOOLEAN
		// dbByte:              pDaoData->m_bsNumeric     GX_IDS_STYLE_DBNUMERIC
		// dbInteger:           pDaoData->m_bsNumeric     GX_IDS_STYLE_DBNUMERIC
		// dbLong:              pDaoData->m_bsNumeric     GX_IDS_STYLE_DBNUMERIC
		// dbSingle:            pDaoData->m_bsNumeric     GX_IDS_STYLE_DBNUMERIC
		// dbDouble:            pDaoData->m_bsNumeric     GX_IDS_STYLE_DBNUMERIC
		// dbCurrency:          pDaoData->m_bsCurrency    GX_IDS_STYLE_DBCURRENCY
		// dbDate:              pDaoData->m_bsDate        GX_IDS_STYLE_DBDATE
		// dbText:              pDaoData->m_bsText        GX_IDS_STYLE_DBTEXT
		// dbLongBinary:        pDaoData->m_bsBinary      GX_IDS_STYLE_DBBINARY
		// dbMemo:              pDaoData->m_bsMemo        GX_IDS_STYLE_DBMEMO
		// dbGUID:              pDaoData->m_bsGUID        GX_IDS_STYLE_DBGUID
		//

		CGXStyle styleDefault;

		// Boolean fiels will be displayed with horizontally centered checkboxes
		pDaoData->m_bsBoolean = pStyMap->RegisterStyle(
						GX_IDS_STYLE_DBBOOLEAN,
						CGXStyle()
							.SetControl(GX_IDS_CTRL_CHECKBOX3D)
							.SetHorizontalAlignment(DT_CENTER)
							.SetVerticalAlignment(DT_VCENTER),
						TRUE);

		// All other field types will be displayed with the standard style settings
		pDaoData->m_bsNumeric = pStyMap->RegisterStyle(GX_IDS_STYLE_DBNUMERIC, styleDefault, TRUE);
		pDaoData->m_bsCurrency = pStyMap->RegisterStyle(GX_IDS_STYLE_DBCURRENCY, styleDefault, TRUE);
		pDaoData->m_bsDate = pStyMap->RegisterStyle(GX_IDS_STYLE_DBDATE, styleDefault, TRUE);
		pDaoData->m_bsText = pStyMap->RegisterStyle(GX_IDS_STYLE_DBTEXT, styleDefault, TRUE);

		// binary fields will be seen with the ole object preview control
		pDaoData->m_bsBinary = pStyMap->RegisterStyle(GX_IDS_STYLE_DBBINARY, CGXStyle().SetControl(GX_IDS_CTRL_DAOOBJECT), TRUE);

		pDaoData->m_bsMemo = pStyMap->RegisterStyle(GX_IDS_STYLE_DBMEMO, styleDefault, TRUE);
		pDaoData->m_bsGUID = pStyMap->RegisterStyle(GX_IDS_STYLE_DBGUID, styleDefault, TRUE);

		// Style for appearance of deleted rows
		pDaoData->m_bsDeletedRows = pStyMap->RegisterStyle(
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
		if (pRecordset != NULL && !pRecordset->IsOpen())
		{
			try
			{
				pRecordset->Open();
			}
			catch (CDaoException* e)
			{
				// Tell them the reason it failed to open
				GX_THROW_LAST
				AfxMessageBox(e->m_pErrorInfo->m_strDescription);
				e->Delete();
				return;
			}
		}
	}
}

// OpenRecordset
//
// Opens the recordset (only if not yet opened),
// initializes the columns (width, field name,
// length, base style) and redraws the grid.
//

static void GetFieldInfo(DAOField* pDAOField, CDaoFieldInfo& fieldinfo)
{
	ASSERT(pDAOField != NULL);

	COleVariant var;

	// Always fetch the Primary properties
	{
		DAO_CHECK(pDAOField->get_Name(&V_BSTR(&var)));
		var.vt = VT_BSTR;
		fieldinfo.m_strName = V_BSTRT(&var);
		var.Clear();

		DAO_CHECK(pDAOField->get_Type(&fieldinfo.m_nType));

		DAO_CHECK(pDAOField->get_Size(&fieldinfo.m_lSize));

		DAO_CHECK(pDAOField->get_Attributes(&fieldinfo.m_lAttributes));
	}

	// Also, fetch default value
	try
	{
#if _MFC_VER >= 0x0421
		BOOL bUseDao30 = FALSE;
	#ifdef _AFXDLL
		AFX_MODULE_STATE* pState = AfxGetModuleState();
		if (pState->m_dwVersion < 421)
			bUseDao30 = TRUE;
	#endif // _AFXDLL

		if(!bUseDao30)
		{
			// Call the DAO 3.5 method
			DAO_CHECK(pDAOField->get_DefaultValue(&var));
		}
		else
		{
			// Call the DAO 3.0 method
			// get_DefaultValue takes BSTR* param not VARIANT*
			// [VC7] Change Function Pointer Definition.
			HRESULT (DAOField::*pMethod)(BSTR*) = (HRESULT (DAOField::*)(BSTR*))&DAOField::get_DefaultValue;
			DAO_CHECK((pDAOField->*pMethod)(&V_BSTR(&var)));
			var.vt = VT_BSTR;
		}
#else
		DAO_CHECK(pDAOField->get_DefaultValue(&V_BSTR(&var)));
		var.vt = VT_BSTR;
#endif
		fieldinfo.m_strDefaultValue = V_BSTRT(&var);
		var.Clear();
	}
	catch (CDaoException* e)
	{
		// Trace them the reason it failed to move to the specified record
		TRACE(e->m_pErrorInfo->m_strDescription);
		TRACE(_T(" - Exception has been catched and resolved in GetFieldInfo\n"));
		GX_THROW_LAST
		e->Delete();
	}
}

static void GetFieldInfo(CDaoRecordset* pRecordset, int nIndex, CDaoFieldInfo& fieldinfo)
{
	// Get DAOField object and fill in field info struct
	DAOField* pDAOField;
	DAO_CHECK(pRecordset->m_pDAOFields->get_Item(
		COleVariant((long)nIndex), &pDAOField));

	GetFieldInfo(pDAOField, fieldinfo);

	// Clean up
	pDAOField->Release();
}

void CGXDaoGrid::OpenRecordset()
{
	CGXBrowseParam* pBrowseData = GetBrowseParam();
	CDaoRecordset* pRecordset = OnGetRecordset();

	// recordset must be allocated already
	if (pRecordset == NULL)
	{
		TRACE0("Warning: OpenRecordset is called without a valid CDaoRecordset object.\n");
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


	// Open the recordset, if it has not yet been opened
	if (pRecordset && !pRecordset->IsOpen())
	{
		CGXWaitCursor theWait;

		try
		{
			pRecordset->Open();
		}
		catch (CDaoException* e)
		{
			// Tell them the reason it failed to open
			GX_THROW_LAST
			AfxMessageBox(e->m_pErrorInfo->m_strDescription);
			e->Delete();
			return;
		}
	}

	if (pRecordset && pRecordset->IsOpen() && !pRecordset->IsEOF())
	{
		pRecordset->MoveFirst();

		// backward scrolling is necessary
		ASSERT(pRecordset->CanScroll());
	}

	CGXBrowseParam* pParam = GetBrowseParam();

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

	CDaoFieldInfo fieldInfo;

	// Delete contents of CGXData
	pParam->GetData()->StoreRowCount(0);
	pParam->GetData()->StoreColCount(0);

	short nFieldCount = pRecordset ? pRecordset->GetFieldCount() : (short) 0;

	// Reserve space in CGXData
	pParam->GetData()->StoreRowCount(1);
	pParam->GetData()->StoreColCount(nFieldCount + GetHeaderCols());

	pParam->m_nFields = nFieldCount;

	for (short nField = 0; nField < nFieldCount; nField++)
	{
		// column info for column nCol in grid/field nField in CDaoRecordset
		ROWCOL nCol = (ROWCOL) nField + 1 + GetHeaderCols();

		// GetFieldInfo(pRecordset, nField, fieldInfo);
		pRecordset->GetFieldInfo(nField, fieldInfo);

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

			// The base style and maximum length of the input text is
			// stored in the column style. All cells in the column will
			// inherit their style attributes from the column style.

			switch (fieldInfo.m_nType)
			{
			case dbByte:
			case dbInteger:
			case dbLong:
			case dbSingle:
			case dbDouble:
			case dbBoolean:
			case dbCurrency:
				(*pStyle).SetUserAttribute(GX_UA_NUMERICVALUE, 1L);
				break;
			default:
				(*pStyle).SetIncludeUserAttribute(GX_UA_NUMERICVALUE, FALSE);
				break;
			}

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

	// trace a warning if MFC double-buffering mechanism is not turned
	// off.
	if (pRecordset && pRecordset->m_bCheckCacheForDirtyFields)
	{
		TRACE0("CGXDaoGrid Warning!\n");
		TRACE0("You have not turned off the CDaoRecordset double-buffering mechanism.\n");
		TRACE0("CGXDaoGrid will manually call SetFieldDirty / SetFieldNull. Therefore,\n");
		TRACE0("this CDaoRecordset feature is obsolete and will only slow down performance.\n");
		TRACE0("If you do not depend on this feature, you should set the CDaoRecordset attribute\n");
		TRACE0("m_bCheckCacheForDirtyFields = FALSE\n");
	}

	// Added this to keep the selection in sync with the current cell when in special mode
	// works only if SetSpecialMode was called before calling the base class OnInitialUpdate
	MoveCurrentCellEx(GX_TOP);

	// readraw the grid (if LockUpdate != TRUE)
	Redraw(GX_INVALIDATE);
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

void CGXDaoGrid::OnInitColInfo(ROWCOL nCol,
	const CDaoFieldInfo& fieldInfo,
	CString& strName,
	long& cbLength,
	WORD& wBaseStyle,
	BOOL* pbColumnSettingsLocked/* = NULL*/)
{

	CGXDaoParam* pDaoData = GetDaoParam();

	// see OnInitialUpdate() above for the table of CGXDaoGrid base styles

	switch(fieldInfo.m_nType)
	{
	case dbText:        wBaseStyle = pDaoData->m_bsText;       break;
	case dbByte:        wBaseStyle = pDaoData->m_bsNumeric;    break;
	case dbInteger:     wBaseStyle = pDaoData->m_bsNumeric;    break;
	case dbLong:        wBaseStyle = pDaoData->m_bsNumeric;    break;
	case dbSingle:      wBaseStyle = pDaoData->m_bsNumeric;    break;
	case dbDouble:      wBaseStyle = pDaoData->m_bsNumeric;    break;
	case dbBoolean:     wBaseStyle = pDaoData->m_bsBoolean;    break;
	case dbCurrency:    wBaseStyle = pDaoData->m_bsCurrency;   break;
	case dbDate:        wBaseStyle = pDaoData->m_bsDate;       break;
	case dbLongBinary:  wBaseStyle = pDaoData->m_bsBinary;     break;
	case dbMemo:        wBaseStyle = pDaoData->m_bsMemo;       break;
	case dbGUID:        wBaseStyle = pDaoData->m_bsGUID;       break;
	default:
		TRACE0("Unknown Datatype\n");
		ASSERT(FALSE);
		AfxThrowNotSupportedException();
	}

	strName = fieldInfo.m_strName;
	cbLength = GetDisplaySize(fieldInfo);

	if (strName.GetLength() > cbLength)
		cbLength = strName.GetLength();
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
// NOTE:
// This method is called from the virtual method OnInitColInfo to
// determine the column size. If you prefer other default column
// widths for special columns, you should override GetDisplaySize.

const int MAX_NUM_STRING_SIZE = 29;

long CGXDaoGrid::GetDisplaySize(const CDaoFieldInfo& fieldInfo)
{
	CGXDaoParam* pDaoParam = GetDaoParam();

	// computes column size
	switch(fieldInfo.m_nType)
	{

	case dbBoolean:
		return 4;

	case dbByte:
		return 3;

	case dbInteger:
		return 6;

	case dbLong:
		return 11;

	case dbCurrency:
		return 11;

	case dbSingle:
	case dbDouble:
		return MAX_NUM_STRING_SIZE;

	case dbDate:
		// NOTE: This is the maximum supported size of a timestamp, not the average size.
		// This size accounts for intervals (the :FFF) which is not supported by many databases.
		return 24;  // DTB: 'YYYY-MM-DD HH:MM:SS:FFF'

	case dbText:
		return fieldInfo.m_lSize;

	case dbMemo:
		// Memo fields
		if (pDaoParam->m_bDisplayMemo)
			return INT_MAX;

	case dbGUID:
		return 50;

	case dbLongBinary:
		// not supported types, field will be hidden
		return 0;

	}

	return 0;
}

// CanUpdate
//
// TRUE if the data in the grid can be changed

BOOL CGXDaoGrid::CanUpdate()
{
	CDaoRecordset* pRecordset = OnGetRecordset();

	return pRecordset && pRecordset->IsOpen() && pRecordset->CanUpdate();
}

// CanAppend
//
// TRUE if user shall be able to append new rows.
// Call CGXBrowserGrid::SetCanAppend(FALSE) if you want to disable this feature.

BOOL CGXDaoGrid::CanAppend()
{
	CDaoRecordset* pRecordset = OnGetRecordset();

	return CGXBrowserGrid::CanAppend() && pRecordset && pRecordset->IsOpen() && pRecordset->CanAppend();
}

// DeleteRows
//
// Called to delete selected records from the CRecordset.
//
// Records will be deleted with pRecordset->Delete(); and
// after deleting the records the recordset will be requeried.

extern "C" static int __cdecl __gxcomparelong(const void* p1, const void* p2)
{
	long l = *(long*) p1 - *(long*) p2;

	return (l>0) ? 1 : (l<0) ? -1 : 0;
}

void CGXDaoGrid::DeleteRows(const CRowColArray& awRowStart, const CRowColArray& awRowEnd, BOOL* pbSuccess)
{
#ifdef _DEBGUG
	for (int index = awRowEnd.GetUpperBound(); index >= 0; index--)
	{
		ASSERT(awRowEnd[index] >= awRowStart[index]);
		// ASSERTION -> DeleteRows assumes that awRowEnd[index] is
		// always greater or equal to awRowStart[index]. Make sure
		// you specify this arrays correctly. ->END
	}
#endif

	if (pbSuccess != NULL)
		*pbSuccess = FALSE;

	CGXBrowseParam* pBrowseData = GetBrowseParam();
	CDaoRecordset* pRecordset = OnGetRecordset();

	ROWCOL nEditRow, nEditCol;
	BOOL bCCell = GetCurrentCell(nEditRow, nEditCol);

	CDaoDatabase* pdb = pRecordset->m_pDatabase;

	// Save current cell's data
	TransferCurrentCell();

	// update last record first

	// check if row to be deleted is in edit mode
	if (pBrowseData->m_nEditMode != noMode)
	{
		for (int index = awRowEnd.GetUpperBound(); index >= 0; index--)
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

	BOOL bTrans = pRecordset->CanTransact();
	if (bTrans)
		pdb->m_pWorkspace->BeginTrans( );

	long* alRecords = NULL;

	try
	{
		// First, sort the array of records
		ROWCOL nCount = 0;
		int index;
		for (index = awRowEnd.GetUpperBound(); index >= 0; index--)
			nCount += awRowEnd[index]-awRowStart[index]+1;

		int nIndex = 0;
		alRecords = new long[nCount];

		for (index = awRowEnd.GetUpperBound(); index >= 0; index--)
		{
			ROWCOL nRecords = awRowEnd[index]-awRowStart[index]+1;
			for (ROWCOL n = 0; n < nRecords; n++)
				alRecords[nIndex++] = GetRecordFromRow(awRowStart[index]+n);
		}

		qsort(alRecords, (size_t) nCount, sizeof(long), __gxcomparelong);

		for (index = (int) nCount-1; index >= 0; index--)
		{
			pRecordset->SetAbsolutePosition(alRecords[index]);
			pRecordset->Delete();

			pRecordset->MovePrev();

			int n = 0;

			// First, make sure all rows have an index
			for (n = 0; n <= pBrowseData->m_awRowIndex.GetUpperBound(); n++)
			{
				if (pBrowseData->m_awRowIndex[n] == 0)
					pBrowseData->m_awRowIndex[n] = (ROWCOL) n;
			}

			for (n = 0; n <= pBrowseData->m_awRowIndex.GetUpperBound(); n++)
			{
				if (pBrowseData->m_awRowIndex[n] > alRecords[index]+GetHeaderRows()+1)
					pBrowseData->m_awRowIndex[n]--;
			}
		}

		for (index = awRowEnd.GetUpperBound(); index >= 0; index--)
		{
			if ((int) awRowStart[index] < pBrowseData->m_awRowIndex.GetSize())
				pBrowseData->m_awRowIndex.RemoveAt((int) awRowStart[index],
					min((int) awRowEnd[index], pBrowseData->m_awRowIndex.GetUpperBound())
					-(int) awRowStart[index]+1);
		}

		if (bTrans)
			pdb->m_pWorkspace->CommitTrans();

		if (pbSuccess != NULL)
			*pbSuccess = TRUE;

		// Remove selection
		SetSelection(0);

		if (bCCell && nEditRow >= awRowStart[0])
		{
			// Sync current cell
				// First, mark as invalid
			StoreCurrentCell(FALSE);

				// Next, position again
			nEditRow = max(1, min(awRowStart[0], GetRowCount()));
		}

		for (int i = awRowEnd.GetUpperBound(); i >= 0; i--)
			CGXGridCore::StoreRemoveRows(awRowStart[i],awRowEnd[i]);

		if (pRecordset->GetRecordCount() == 0)
			pRecordset->Requery();

		// Reset high water mark
		m_nLastRecord = -1;
		pBrowseData->m_nRecordLastSeen = -1;
		pBrowseData->m_bEOFSeen = FALSE;
	}
	catch (CDaoException* e)
	{
		if (bTrans)
			pdb->m_pWorkspace->Rollback();

		// Tell them the reason it failed to open
		GX_THROW_LAST
		AfxMessageBox(e->m_pErrorInfo->m_strDescription);
		e->Delete();
	}
	catch (CException* e)
	{
		if (bTrans)
			pdb->m_pWorkspace->Rollback();
		GX_THROW_LAST
		e->Delete();
	}

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
}

// Requery
//
// Requeries the CRecordset. It is also necessary to reset
// the last seen record, so that OnTestGridDimension will not
// get confused.

void CGXDaoGrid::Requery()
{
	CGXBrowseParam* pBrowseData = GetBrowseParam();
	CDaoRecordset* pRecordset = OnGetRecordset();

	// Save and reset current cell
	TransferCurrentCell();

	m_nLastRecord = -1;
	pBrowseData->m_bEOFSeen = FALSE;
	pBrowseData->m_nRecordLastSeen = -1;
	if (pRecordset && pRecordset->CanRestart())
	{
		CGXWaitCursor theWait;
		pRecordset->Requery();
	}

	// Reinit current cell
	TransferCurrentCell(FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// CGXDaoGrid overridables

// OnLoadCellStyle
//
// give the programmer the chance to load the value from data source
// or apply additional formattings at runtime

BOOL CGXDaoGrid::OnLoadCellStyle(ROWCOL nRow, ROWCOL nCol, CGXStyle& style, LPCTSTR pszExistingValue)
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

	CGXDaoParam* pDaoData = GetDaoParam();
	CGXBrowseParam* pBrowseData = GetBrowseParam();
	CDaoRecordset* pRecordset = OnGetRecordset();

	int nField = GetFieldFromCol(nCol);

	CGXStyle* pStyle = CreateStyle();
	GetColStyle(nCol, *pStyle, gxCopy);

	// Load default value from recordset on demand
	if (pDaoData->m_bEOFSeen && nRow == GetRowCount() && nField != -1
		&& pRecordset && pRecordset->IsOpen()
		&& nField < pRecordset->GetFieldCount())
	{
		try
		{
			if (!pStyle->GetIncludeValue())
			{
				CDaoFieldInfo fieldInfo;
				GetFieldInfo(pRecordset, nField, fieldInfo);

				// default value
				CString strDefaultValue = fieldInfo.m_strDefaultValue;

				// remove quotation marks ('"') from strings
				if (!strDefaultValue.IsEmpty() && strDefaultValue[0] == '"')
					strDefaultValue = strDefaultValue.Mid(1, strDefaultValue.GetLength()-2);

				if (!strDefaultValue.IsEmpty())
					GetParam()->GetData()->StoreValueRowCol(0, nCol, strDefaultValue, gxApplyNew, -1);
			}
		}
		catch (CDaoException* e)
		{
			// Trace them the reason it failed to move to the specified record
			// TRACE(e->m_pErrorInfo->m_strDescription);
			// TRACE(_T(" - Exception has been catched and resolved in CGXDaoGrid::OnLoadCellStyle\n"));
			GX_THROW_LAST
			e->Delete();
		}
	}

	// TRACE("OnLoadCellStyle %d,%d\n", nRow, nCol);

	BOOL bRet = FALSE;

	if (pszExistingValue == NULL && nRow >= GetFirstRow())
	{
		// Get style from current record in data source
		if (!m_bNoValueNeeded && nField != -1
			&& pRecordset && pRecordset->IsOpen()
			&& nField < pRecordset->GetFieldCount() && MoveTo(nRow))
		{
			CString sValue;

			BOOL bString = TRUE;

			try
			{
				if(!(nCol == 0 || nRow == 0) && !CheckForBinary(nRow, nCol, style))
				// transfer value from recordset and convert it to a string
					ConvertValueToString(nCol, sValue);
				else
					bString = FALSE;
			}
			catch (CDaoException* e)
			{
				// Outline deleted (or otherwise failed) records

				// load base style for deleted rows
				style.SetBaseStyle(pDaoData->m_bsDeletedRows);
				style.LoadBaseStyle(*GetParam()->GetStylesMap());
				GX_THROW_LAST
				e->Delete();
			}

			if(bString)
				style.SetValue(sValue);
		}
		else if (pBrowseData->m_bEOFSeen && nRow > GetLastRow())
			style.SetEnabled(FALSE);

		bRet = TRUE;
	}

	if (pStyle->GetIncludeUserAttribute(GX_UA_NUMERICVALUE))
		style.SetValueType(GX_VT_NUMERIC);

	RecycleStyle(pStyle);

	// You may override this method and apply additional
	// formattings specific to columns or depending on
	// the cells value or context, but be carefull
	// that you don't forget to call this base class
	// version of the method.
	//
	// This method is also a nice hook for filling the choice
	// list of a combobox with the query results of another
	// recordset.

	return bRet;   // return TRUE if you have changed the style object!
}

// ConvertValueToString
//
// ConvertValueToString() gets the COleVariant of the bound
// CDaoField and converts the value to a string
//

void CGXDaoGrid::ConvertValueToString(ROWCOL nCol, CString& strRet)
{
	CGXDaoParam* pDaoParam = GetDaoParam();
	CDaoRecordset* pRecordset = OnGetRecordset();
	int nField = GetFieldFromCol(nCol);

	GXGetDaoFieldString(strRet, pRecordset, nField, pDaoParam->m_bDisplayMemo);
}

// MoveTo
//
// This method tries to position the recordset to the given
// row. It will return FALSE if the positioning failed.
//

BOOL CGXDaoGrid::MoveTo(ROWCOL nRow)
{
	CGXBrowseParam* pBrowseData = GetBrowseParam();
	CDaoRecordset* pRecordset = OnGetRecordset();

	if (pRecordset == NULL || !pRecordset->IsOpen() ||
		(long) (nRow-GetHeaderRows()) > OnGetRecordCount())
		return FALSE;

	long nRecord = GetRecordFromRow(nRow);

	long nCurrentRecord = SyncPosition();

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
			MoveToPosition(nRecord, FALSE);
		}
		else
			MoveToPosition(nRecord, FALSE);
	}
	catch (CDaoException* e)
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

BOOL CGXDaoGrid::OnFlushRecord(ROWCOL nRow, CString* ps)
{
	CGXBrowseParam* pBrowseData = GetBrowseParam();
	CDaoRecordset* pRecordset = OnGetRecordset();

	try
	{
		COleVariant varBookmarkCurrent;
		if (pRecordset->CanBookmark() && !pRecordset->IsEOF() && !pRecordset->IsBOF())
			varBookmarkCurrent = pRecordset->GetBookmark();

		// Sandwich CDaoRecordset into Edit/AddNew and Update
		if (pBrowseData->m_nEditMode == addnew)
			pRecordset->AddNew();
		else
		{
			VERIFY(MoveTo(nRow));
			pRecordset->Edit();
		}

		// Force writing dirty cells to CDaoRecordset
		// Base class version contains the necessary functionality
		// to check all fields and call OnFlushCellValue

		CGXBrowserGrid::OnFlushRecord(nRow, NULL /* force throwing an exception */);

		PreUpdateRecordset(nRow);

		pRecordset->Update();

        if (pBrowseData->m_nEditMode == addnew && pRecordset->CanBookmark())
		{
			try
			{
				COleVariant varBookmarkNew =
					pRecordset->GetLastModifiedBookmark();
				pRecordset->SetBookmark(varBookmarkNew);

				ROWCOL nRow = pBrowseData->m_nCurrentRow;

				long nRec = pRecordset->GetAbsolutePosition();

				if (nRec >= 0 && nRec != GetRecordFromRow(nRow))
				{
					ROWCOL nIdx = nRec - GetHeaderRows() + 1;
					CRowColArray& awRowIndex = pBrowseData->m_awRowIndex;

					// TRACE("*** ms-q164615 ***  new-row %ld,  new-rec %ld\n", nRow, nRec);

					ASSERT(awRowIndex.GetSize() <= (int)nRow);
					awRowIndex.SetSize(nRow + 1);

					for (ROWCOL n = 0; n < nRow; n++)
					{
						ROWCOL i = GetRowIndex(n);
						if (i >= nIdx) awRowIndex[n] = i + 1;
					}
					awRowIndex[nRow] = nIdx;

					if (!IsLockUpdate())
						Redraw(GX_INVALIDATE);
				}
			}
			catch(CDaoException *)
			{
				// TRACE("cdg.ofr: dao exception, falling through\n");
				GX_THROW_LAST
			}
			catch(CException *)
			{
				// TRACE("cdg.ofr: exception, falling through\n");
				GX_THROW_LAST
			}
		}

		if (varBookmarkCurrent.vt != VT_EMPTY)
			pRecordset->SetBookmark(varBookmarkCurrent);
	}
	catch (CDaoException* e)
	{
		GridWnd()->SendMessage(WM_CANCELMODE, 0, 0);

		// Reset cursor
		if (!pRecordset->IsEOF() && !pRecordset->IsBOF() && pRecordset->m_nFields > 0)
			pRecordset->SetFieldDirty(NULL, FALSE);

		// ps is a valid CString if we shall catch the exception
		if (ps)
		{
			TRACE0("CGXDaoGrid::OnFlushRecord failed!\n");
			GX_THROW_LAST

			*ps = e->m_pErrorInfo->m_strDescription;
			e->Delete();
		}
		else                     // else
		{                        // let exception fall through
			GX_THROW_LAST
		}

		// failed, ...
		return FALSE;
	}
	catch (CException* e)
	{
		GridWnd()->SendMessage(WM_CANCELMODE, 0, 0);

		// Reset cursor
		if (!pRecordset->IsEOF() && !pRecordset->IsBOF() && pRecordset->m_nFields > 0)
			pRecordset->SetFieldDirty(NULL, FALSE);

		// ps is a valid CString if we shall catch the exception
		if (ps)
		{
			TRACE0("CGXDaoGrid::OnFlushRecord failed!\n");
			GX_THROW_LAST

			ps->Empty();
			e->Delete();
		}
		else					 // else
		{                        // let exception fall through
			GX_THROW_LAST
		}

		// failed, ...
		return FALSE;
	}

	return TRUE;
}


// PreUpdateRecordset
//
// let the programmer update additional fields in the recordset which
// are not bound to the grid should not be visible to the user.
//
// This overridable is called from OnFlushRecord
// just before the pRecordset->Update method is called.

void CGXDaoGrid::PreUpdateRecordset(ROWCOL nRow)
{
	// Unused:
	nRow;
}

// OnFlushCellValue
//
// OnFlushCellValue is called from within CGXBrowserGrid::OnFlushRecord
// for all values changed in the current buffer.


void CGXDaoGrid::OnFlushCellValue(ROWCOL nRow, ROWCOL nCol, LPCTSTR pszChangedValue)
{
	// Unused:
	nRow;

	// cannot handle this.
	if (pszChangedValue == NULL)
		return;

	CGXDaoParam* pDaoParam = GetDaoParam();
	CDaoRecordset* pRecordset = OnGetRecordset();

	int nField = GetFieldFromCol(nCol);

	if (nField < 0 || nField >= pRecordset->GetFieldCount())
	{
		// This case will happen if the user did insert new
		// columns, e.g. a sum based on other fields in the row.
		// If you want to do this, you should make sure that CGXDaoGrid
		// does not try to write this values to the CRecordset.

		// Possible solution to avoid this message is to set
		// the column read-only or static or override this method.

		SetWarningText(szUnboundField);
		AfxThrowNotSupportedException();
		return;
	}

	CDaoFieldInfo info;
	pRecordset->GetFieldInfo(nField, info);

	// Make empty strings NULL
	if (_tcslen(pszChangedValue) == 0)
		pRecordset->SetFieldValueNull(nField);
	else
	{
		switch (info.m_nType)
		{
		case dbGUID:
		case dbText:
		        /* [VC7] SetFieldValue has now changed only
		        to accept COleVariant as the second parameter*/
				pRecordset->SetFieldValue(nField,
					COleVariant(pszChangedValue, VT_BSTRT));
				break;
		case dbByte:
				pRecordset->SetFieldValue(nField,
					COleVariant((BYTE) _ttoi(pszChangedValue)));
				break;
		case dbInteger:
				pRecordset->SetFieldValue(nField,
					COleVariant((LONG) _ttol(pszChangedValue)));
				break;
		case dbLong:
				pRecordset->SetFieldValue(nField,
					COleVariant((LONG) _ttol(pszChangedValue)));
				break;
		case dbSingle:
				pRecordset->SetFieldValue(nField,
					COleVariant((float) _gxttof(pszChangedValue)));
				break;
		case dbDouble:
				pRecordset->SetFieldValue(nField,
					COleVariant((double) _gxttof(pszChangedValue)));
				break;
		case dbBoolean:
			{
				BOOL bBool = _tcsicmp(pszChangedValue, _T("TRUE")) == 0;
				pRecordset->SetFieldValue(nField,
					COleVariant((short) bBool, VT_BOOL));
				break;
			}
		case dbCurrency:
			{
				//Need to convert to COleCurrency suitable format to overcome design flaw limitation with locales
				int  decimal, sign;
				TCHAR decSep[4] = { 0, 0, 0, 0 };

				USES_CONVERSION;

				// QA: 31989 - #if Secure Code Cleanup.
				CString s = _fcvt( atof( T2CA(pszChangedValue) ), 4, &decimal, &sign );
				CString strResult;
			 
				GetLocaleInfo( LOCALE_USER_DEFAULT, LOCALE_SMONDECIMALSEP, decSep, 4 );
				 
				if( decimal < s.GetLength() )
					s.Insert( decimal, decSep );
				 
				if( sign != 0 ) 
					strResult = _T("-");
			 
				strResult += s;

				COleCurrency v;
				v.ParseCurrency(pszChangedValue);
				pRecordset->SetFieldValue(nField, v);
				break;
			}
		case dbDate:
			{
				COleDateTime v;
				v.ParseDateTime(pszChangedValue);
				if(!v.ParseDateTime(pszChangedValue))
				{
					if (pszChangedValue != NULL && _tcslen(pszChangedValue) > 0)
						v = _gxttof(pszChangedValue);
				}
				pRecordset->SetFieldValue(nField, v);
				break;
			}

		case dbMemo:
			if (pDaoParam->m_bDisplayMemo)
			{
				/* [VC7] SetFieldValue has now changed only
		        to accept COleVariant as the second parameter*/
				pRecordset->SetFieldValue(nField,
					COleVariant(pszChangedValue, VT_BSTRT));
				break;
			}

		case dbLongBinary:

			// This case will only happen if you have set the
			// dirty field for this columns but you have not
			// supplied data of type CGXAbstractBlob

			// You should supply this data in CGXBrowseDirtyFieldStruct
			// You should override OnFlushBlobValue if you want to allow
			// changing dbLongBinary, dbMemo or dbGUID fields.

			ASSERT(1);
			SetWarningText(szUnsupportedField);
			AfxThrowNotSupportedException();
			return;
		}
	}
}

// OnFlushBlobValue

// Note: You should override this method if you want to allow
// changing any binary fields that do not support the following default write of data

void CGXDaoGrid::OnFlushBlobValue(ROWCOL nRow, ROWCOL nCol, CGXAbstractBlob* pAttribute)
{
	// Unused:
	nRow;

	// cannot handle this.
	if (pAttribute == NULL)
		return;

	CGXDaoParam* pDaoParam = GetDaoParam();//Unused
	CDaoRecordset* pRecordset = OnGetRecordset();

	int nField = GetFieldFromCol(nCol);

	if (nField < 0 || nField >= pRecordset->GetFieldCount())
	{
		// This case will happen if the user did insert new
		// columns, e.g. a sum based on other fields in the row.
		// If you want to do this, you should make sure that CGXDaoGrid
		// does not try to write this values to the CRecordset.

		// Possible solution to avoid this message is to set
		// the column read-only or static or override this method.

		SetWarningText(szUnboundField);
		AfxThrowNotSupportedException();
		return;
	}

	CDaoFieldInfo info;
	pRecordset->GetFieldInfo(nField, info);


		switch (info.m_nType)
		{
			case dbLongBinary:
				{
					// write the data back to the record source
					CGXDaoBlob* pDaoBlob = (CGXDaoBlob*) pAttribute;
					pRecordset->SetFieldValue(nField, pDaoBlob->GetOleVariant());
					break;
				}
			default:
				TRACE0("OG Warning: OnFlushBlobValue called for non binary field\n");
				TRACE0("If this is intentional please check this call to make sure that\n");
				TRACE0(" the object is getting stored as expected\n");
		}

	// for cleanup
	CGXBrowserGrid::OnFlushBlobValue(nRow, nCol, pAttribute);
}

// handle this method if you wish to have a change in the viewer without subclassing CGXViewerFactory
void CGXDaoGrid::GetOleViewerRowCol(ROWCOL nRow, ROWCOL nCol, DWORD dwId, CGXOleViewer*& pViewer ) const
{
	// default is to do nothing
	GX_UNUSED_ALWAYS(nRow);
	GX_UNUSED_ALWAYS(nCol);
	GX_UNUSED_ALWAYS(dwId);
	GX_UNUSED_ALWAYS(pViewer);
}

// OnAddedNewRecord
//
// OnAddedNewRecord is called after a record has been suceesfully appended
// to the recordset.

void CGXDaoGrid::OnAddedNewRecord()
{
	FreeObjectCache();
	CGXBrowseParam* pBrowseData = GetBrowseParam();
	pBrowseData->m_bEOFSeen = FALSE;
	OnTestGridDimension(LONG_MAX, LONG_MAX);
}

// BeginTrans
//
// BeginTrans calls BeginTrans for the CDaoRecordset.
//
// This method does not call the CGXGridCore base class
// version because Undo/Redo support differs a lot for
// this DAO Grid.

void CGXDaoGrid::BeginTrans(LPCTSTR pszDescription)
{
	CDaoRecordset* pRecordset = OnGetRecordset();

	if (pRecordset == NULL || !pRecordset->IsOpen())
		return;

	CDaoWorkspace* pws = pRecordset->m_pDatabase->m_pWorkspace;

	if (pRecordset->CanTransact())
		pws->BeginTrans();

	pszDescription;
}

// CommitTrans
//
// CommitTrans calls CommitTrans for the CDaoRecordset.
//
// This method does not call the CGXGridCore base class
// version because Undo/Redo support differs a lot for
// this DAO Grid.

void CGXDaoGrid::CommitTrans()
{
	CDaoRecordset* pRecordset = OnGetRecordset();

	if (pRecordset == NULL || !pRecordset->IsOpen())
		return;

	CDaoWorkspace* pws = pRecordset->m_pDatabase->m_pWorkspace;

	if (pRecordset->CanTransact())
		pws->CommitTrans();
}

// Rollback
//
// Rollback calls Rollback for the CDaoRecordset.
//
// This method does not call the CGXGridCore base class
// version because Undo/Redo support differs a lot for
// this DAO Grid.

void CGXDaoGrid::Rollback()
{
	CDaoRecordset* pRecordset = OnGetRecordset();

	if (pRecordset == NULL || !pRecordset->IsOpen())
		return;

	CDaoWorkspace* pws = pRecordset->m_pDatabase->m_pWorkspace;

	if (pRecordset->CanTransact())
		pws->Rollback();

	Requery();
}

// OnReplaceAll
//
// OnReplaceAll switches the CGXDaoGrid into a specific context
// before it calls the base class CGXGridCore::OnReplaceAll method.
//
// Special context is:
// - GXGetLastFRState()->bTransaction = FALSE;
// - pBrowseData->m_bDoReplaceAll = TRUE;
//
// This special settings make sure that each change in a cell
// will automatically update the recordset, and that if
// an update throws an exception CGXDaoGrid::OnReplaceAll
// is resonsible for catching this exception.
//

void CGXDaoGrid::OnReplaceAll(LPCTSTR lpszFind, LPCTSTR lpszReplace,
		BOOL bCase)
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
	BOOL bAppend = CanAppend();
	pBrowseData->m_bCanAppend = FALSE;

	// Save current cell's data
	TransferCurrentCell();

	ROWCOL nEditRow, nEditCol;
	GetCurrentCell(nEditRow, nEditCol);

	BeginTrans(GXGetAppData()->strmReplaceAll);

	BOOL bOldLock = LockUpdate(TRUE);

	try
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
	catch(CDaoException* e)
	{
		Rollback();
		Requery();
		GX_THROW_LAST
		AfxMessageBox(e->m_pErrorInfo->m_strDescription);
		e->Delete();
	}
	catch(CException* e)
	{
		Rollback();
		Requery();
		GX_THROW_LAST
		e->Delete();
	}

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
// Sorting can be done by sorting the recordset with DAO

void CGXDaoGrid::SortRows(CGXRange sortRange, CGXSortInfoArray& sortInfo, UINT flags /*= GX_UPDATENOW*/)
{
	// Unused: (in relase build)
	sortRange;

	ASSERT(sortRange.IsTable());
	// ASSERTION-> It is not supported to sort only a limited range
	// of rows with a CGXDaoGrid ->END

	CDaoRecordset* pSet = OnGetRecordset();
	int i;
	for (i = 0; i < sortInfo.GetSize(); i++)
	{
		short nField = (short) GetFieldFromCol(sortInfo[i].nRC);
		CDaoFieldInfo fieldInfo;
		pSet->GetFieldInfo(nField, fieldInfo);

		// sorting not possible on longbinary or memo fields
		if(fieldInfo.m_nType == dbLongBinary || fieldInfo.m_nType == dbMemo)
			return;
	}

	MoveCurrentCell(GX_TOP);
	TransferCurrentCell();

	// Sort the grid with the columns specified in awCols.

	CGXDaoParam* pParam = (CGXDaoParam*) GetParam();

	pParam->EmptyUndoList();
	pParam->EmptyRedoList();

	if (pParam->m_nEditMode != noMode)
		Update();

	pSet->m_strSort.Empty();

	for (i = 0; i < sortInfo.GetSize(); i++)
	{
		short nField = (short) GetFieldFromCol(sortInfo[i].nRC);

		CDaoFieldInfo fieldInfo;
		pSet->GetFieldInfo(nField, fieldInfo, AFX_DAO_SECONDARY_INFO);

// note:	If you have a problem with sorting joined tables because fieldnames are not qualified
//			with the table, try overriding SortRows, copying up the base class code, and changing
//			the m_strSourceField in the second line below to m_strName.

		pSet->m_strSort += _T('[');
		pSet->m_strSort += fieldInfo.m_strSourceField;
		pSet->m_strSort += _T(']');

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

// support for binary fields

BOOL CGXDaoGrid::CheckForBinary(ROWCOL nRow, ROWCOL nCol, CGXStyle& style)
{
	// check if we should ignore binary data
	if(GetDaoParam()->GetIgnoreBinary())
		return FALSE;

	short nType;

	CDaoRecordset* pRecordset = OnGetRecordset();
	int nField = GetFieldFromCol(nCol);


	// Get DAOField object and determine data type
	DAOField* pDAOField;
	DAO_CHECK(pRecordset->m_pDAOFields->get_Item(
		COleVariant((long)nField), &pDAOField));

	DAO_CHECK(pDAOField->get_Type(&nType));

	// Clean up
	pDAOField->Release();

	BOOL bCanHandleField = CanHandleFieldAsBinary(nType);


	if(bCanHandleField)
	{
		CString strPreview;
		GetPreviewString(nType, strPreview);
		style.SetValue(strPreview);
	}

	// The data will be loaded only as required
	if( IsPreviewField(nCol, style) && !IsCurrentCell(nRow, nCol) )
		return bCanHandleField ? TRUE : FALSE;


	if(bCanHandleField)
	{
		static COleVariant var;
		var.Clear();

		BOOL bChange(TRUE);

		if(style.GetIncludeUserAttribute(GX_IDS_UA_DAOOLEBMP))
		{
			const CGXOleVarUserAttribute& oleAttr = (const CGXOleVarUserAttribute&)style.GetUserAttribute(GX_IDS_UA_DAOOLEBMP);

			//if (oleAttr.m_bModify == TRUE)
				bChange = FALSE;
		}

		if(bChange == TRUE)
		{
			var = pRecordset->GetFieldValue(nField);
			style.SetUserAttributePtr(GX_IDS_UA_DAOOLEBMP, new CGXOleVarUserAttribute(var) );
		}
		return TRUE;
	}
	else
		return FALSE;
}

// Will be called from CGXBrowserGrid::SetStyleRange
BOOL CGXDaoGrid::SetBinaryFlags(const CGXStyle* pStyle, int nField)
{
	if(pStyle == NULL)
		return FALSE;

	// check if this is binary data
	if(pStyle->GetIncludeUserAttribute(GX_IDS_UA_DAOOLEBMP))
	{
			CGXDaoParam* pBrowseData = GetDaoParam();
			CGXOleVarUserAttribute& oleAttr = (CGXOleVarUserAttribute&)pStyle->GetUserAttribute(GX_IDS_UA_DAOOLEBMP);

			if (oleAttr.m_bModifyState == TRUE)
			{
					pBrowseData->m_paDirtyFieldStruct[nField].bDirty = TRUE;

					CGXDaoBlob* pDaoBlob = NULL;
					BOOL bReuse(FALSE);
					if(pBrowseData->m_paDirtyFieldStruct[nField].pAttribute == NULL)
						pDaoBlob = new CGXDaoBlob();
					else
					{
						pDaoBlob = (CGXDaoBlob*)pBrowseData->m_paDirtyFieldStruct[nField].pAttribute;
						pDaoBlob->Cleanup();
						bReuse = TRUE;
					}

					pDaoBlob->SetOleVariant(oleAttr.GetOleVarValue());

					if(bReuse == FALSE)
						pBrowseData->m_paDirtyFieldStruct[nField].pAttribute = pDaoBlob;

					oleAttr.m_bModifyState = FALSE;
			}
		return TRUE;
	}
	else
		return FALSE;
}

// override this function if you wish to handle any other type of field as a binary field
// i.e., if you wish to spawn an external viewer etc. For example you can spawn word to
// edit Memo fields etc.
BOOL CGXDaoGrid::CanHandleFieldAsBinary(int nType) const
{
	if(nType == dbLongBinary)
		return TRUE;
	else
		return FALSE;
}

void CGXDaoGrid::GetPreviewString(int nType, CString& strPreview) const
{
	// use default text from resource
	strPreview = m_strBinDescrip;
	GX_UNUSED_ALWAYS(nType);
}


BOOL CGXDaoGrid::IsPreviewField(ROWCOL nCol, const CGXStyle& style) const
{
	GX_UNUSED_ALWAYS(nCol);
	GX_UNUSED_ALWAYS(style);
	return TRUE;
}

// the default is to return FALSE. Override and return TRUE if you set hBitmap to a valid
// value
BOOL CGXDaoGrid::OnGetBitmapHandleRowCol(ROWCOL /* nRow*/, ROWCOL /*nCol*/, HANDLE& /*hBitmap*/)
{
	return FALSE;
}

// Optionally you can store the bitmap handle and use it external to the grid or as an
// optimization (return the value from OnGetBitmapHandleRowCol above). If you store the
// handle return FALSE from this method. Otherwise the memory handle passed in will be
// freed by the caller when this function returns
BOOL CGXDaoGrid::OnUseBitmapHandleRowCol(ROWCOL /*nRow*/, ROWCOL /*nCol*/, HANDLE /*hBitmap*/)
{
	return TRUE;
}

#pragma warning (pop) //4995

#endif // #if _MFC_VER >= 0x0400 && !defined(_AFX_NO_DAO_SUPPORT)
