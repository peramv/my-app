///////////////////////////////////////////////////////////////////////////////
// gxbrowse.cpp : implementation of CGXBroswerGrid
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

// Headers for imported classes

#ifndef _GXRESRC_H_
#include "grid\gxresrc.h"
#endif

#ifndef _GXBROWSE_H_
#include "grid\gxbrowse.h"
#endif

#ifndef _GXDLL_H_
#include "grid\gxdll.h"
#endif

#ifndef _AFXPRIV_H_
#include "afxpriv.h"
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXBROWSE")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

#pragma warning (disable: 4245) // Signed/Unsigned Mismatch

IMPLEMENT_SERIAL(CGXBrowseParam, CGXGridParam, 0 /* schema number*/)

/////////////////////////////////////////////////////////////////////////////
// CGXBrowseGridArrowRowHeader

CGXBrowseGridArrowRowHeader::CGXBrowseGridArrowRowHeader(CGXBrowserGrid* pBrowserGrid)
	: CGXControl(pBrowserGrid)
{
	m_bmPencil.LoadBitmap(GX_IDB_PENCIL);
	m_bmStar.LoadBitmap(GX_IDB_STAR);
	m_bmArrow.LoadBitmap(GX_IDB_ARROW);

	m_pBrowserGrid = pBrowserGrid;

	m_bWin95Look = FALSE;
}

void CGXBrowseGridArrowRowHeader::Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle)
{
	// no arrow needed when printing
	if (Grid()->IsPrinting())
		return;

	// Is it the current row?
	BOOL bCurrentRow = nRow > 0 && Grid()->IsCurrentCell(nRow);

	// Is current row in edit mode?
	BOOL bPencil = m_pBrowserGrid->GetBrowseParam()->m_nEditMode != CGXBrowserGrid::noMode;

	// Is it the append row?
	BOOL bAppendRow = m_pBrowserGrid->CanAppend() &&
			(nRow == m_pBrowserGrid->GetAppendRow()                     // is it the append row?
			|| bPencil && nRow-1 == m_pBrowserGrid->GetAppendRow());    // is it the row after if append row is in edit mode

	// Background
	DrawBackground(pDC, rect, style);

	// Draw button look (if not printing and not
	// explicitly specified as raised or sunken)
	if (!Grid()->IsPrinting()
		&& Grid()->GetParam()->GetProperties()->GetDisplay3dButtons()
		&& (style.GetIncludeDraw3dFrame() || style.GetDraw3dFrame() == gxFrameNormal))
	{

		if (m_bWin95Look)
		{
			// Draw Raised with better 3d-effect (looks better
			// if grid lines are turned off)
			GXDrawEdge(pDC, rect, BDR_RAISEDOUTER | BDR_RAISEDINNER);
		}
		else
		{
			COLORREF rgb3dDkShadow = RGB(0, 0, 0);
			COLORREF rgb3dHilight = GXGetSysData()->GetSysColor(COLOR_BTNHIGHLIGHT);

			// Draw Raised like a normal CGXHeader (looks better
			// when grid lines are turned on)
			GXDraw3dFrame(pDC, rect.left, rect.top, rect.right-1, rect.bottom-1, 1,
				rgb3dHilight, rgb3dDkShadow);
		}
	}

	// choose bitmap for the header
	CBitmap* pBitmap = NULL;

	if (bCurrentRow && bPencil)
		pBitmap = &m_bmPencil;
	else if (bAppendRow)
		pBitmap = &m_bmStar;
	else if (bCurrentRow)
		pBitmap = &m_bmArrow;

	if (pBitmap)
	{
		// Bitmap size
		BITMAP     bm;
		pBitmap->GetObject(sizeof(BITMAP), (LPSTR)&bm);

		CPoint     ptSize;
		ptSize.x = bm.bmWidth;            // Get width of bitmap
		ptSize.y = bm.bmHeight;           // Get height of bitmap
		pDC->DPtoLP(&ptSize, 1);      // Convert from device to logical points

		// Draw bitmap
		if (rect.Width() >= ptSize.x && rect.Height() >= ptSize.x)
		{
			// must have at least the first bitmap loaded before calling DrawItem
			ASSERT(pBitmap->m_hObject != NULL);     // required

			int x = rect.left + max(1, (rect.Width()-ptSize.x)/2);
			int y = rect.top + max(1, (rect.Height()-ptSize.y)/2);

			GXDrawTransparentBitmap(pDC, // The destination DC.
				pBitmap, // The bitmap to be drawn.
				x,        // X coordinate.
				y,        // Y coordinate.
				RGB(192,192,192)); // The color for transparent
								   // pixels (white grey).

		}
	}

	CGXControl::Draw(pDC, rect, nRow, nCol, style, pStandardStyle);
}

/////////////////////////////////////////////////////////////////////////////
// CGXBrowseParam

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

CGXBrowseParam::CGXBrowseParam()
{
	// Current row - internal buffer
	m_paDirtyFieldStruct = NULL;    // changed fields
	m_nFields = 0;                  // number of fields in m_paDirtyFieldStruct
	
	m_nCurrentRow = 0;              // current edited row (with pencil-row-header)
	m_nEditMode = CGXBrowserGrid::noMode;           // current mode
	
	m_bUpdateOnStore = FALSE;       // TRUE when Update shall be called
	m_bDoReplaceAll = FALSE;        // TRUE when OnReplaceAll is called
	
	m_pTmpStyle = NULL;             // temporary style object
	
	// Record count
	m_bEOFSeen = TRUE;      // set this member FALSE if you don't
	// know the exact record count.
	
	m_nRecordLastSeen = -1; // Last seen record will be used to
	// determine the record count when OnGetRecordCount()
	// returns LONG_MAX
	
	m_nRecordCount = -1;    // can be used by derived classes
	// m_nRecordCount has no meaning for this base class
	
	m_bCanStoreGridCellInCGXData = FALSE;
	m_bAllowPasteMultiCells = FALSE;
	
	m_nMaxColWidth = 255;
	
	m_bSyncCurrentCell = TRUE;
	
	m_bCanAppend = TRUE;
	
	// Display wait cursor when moving more than the
	// specified number of records in the recordset.
	m_lMoveRecordWaitCursor = LONG_MAX;
	
	m_bIsBrowseInit = FALSE;

	// Recordset information
	m_pRecSetInfo = NULL;
}

CGXBrowseParam::~CGXBrowseParam()
{
	if (m_paDirtyFieldStruct)
	{
		delete[] m_paDirtyFieldStruct;
	}
	if(m_pTmpStyle)
	{
		delete m_pTmpStyle;
	}
	if (m_pRecSetInfo)
	{
		delete m_pRecSetInfo;
	}
}

void CGXBrowseParam::Serialize(CArchive& ar)
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
			TRACE0( "Incompatible format while reading CGXBrowseParam" );
			TRACE2("in %s at line %d\n", __FILE__, __LINE__);
			ASSERT(0);
			// ASSERTION-> Wrong version detected while reading object ->END
#endif
			AfxThrowArchiveException(CArchiveException::badSchema);
			return;
		}
	}
	
	GXArchiveBool(ar, m_bIsBrowseInit);

	if (wActualVersion >= 2)
	{
		// Recordset information
		if (ar.IsStoring())
			ar << m_pRecSetInfo;
		else
			ar >> m_pRecSetInfo;
	}
}

// Copying attributes from one param into another will not initialize the param object
// you have to reinitialize the param with the external data source for it to become usable.
CGXBrowseParam& CGXBrowseParam::operator=(const CGXBrowseParam& p)
{
	CGXGridParam::operator=(p);
	m_bAllowPasteMultiCells = p.m_bAllowPasteMultiCells;
	m_bCanStoreGridCellInCGXData = p.m_bCanStoreGridCellInCGXData;
	m_nMaxColWidth = p.m_nMaxColWidth;
	m_bCanAppend = p.m_bCanAppend;
	m_lMoveRecordWaitCursor = p.m_lMoveRecordWaitCursor;
	// The rest of the members help stay in sync with the external data and are hence ignored
	// since this has to be reinitialized with a new external data source
	return *this;
}

/////////////////////////////////////////////////////////////////////////////
// CGXBrowserGrid
//@doc
//@mfunc
//@parm CWnd* | pGridWnd | A pointer to the parent <c CWnd> object for the <c CGXBrowserGrid> object.
//@parm CDocument* | pGridDoc | A pointer to the document, if any. Otherwise <bold>NULL<ebold>.
//@parm You should pass <bold>TRUE<ebold> for this parameter if the grid is used in a <c CView>
//@rem
//Constructs a <c CGXBrowserGrid> object.<nl>
//<nl>
//You will only need to call this constructor if you want to attach a 
//<c CGXBrowserGrid> object to a <c CGXGridHandleView> or <c CGXGridHandleWnd>.
//@ex This example shows you how you can attach a 
// <c CGXBrowserGrid> (derived from <c CGXGridCore>) to <c CGXGridHandleView>:|
/*
void CMyGridView::OnInitialUpdate()
{
   AttachGrid( new CGXBrowserGrid(this, GetDocument(), TRUE) );
   CGXGridHandleView::OnInitialUpdate();
   GetGrid()->SetRowCount(10);
   GetGrid()->SetColCount(10);
   ...
}
*/
//@xref <c CGXBrowserGrid> <c CGXGridHandleView> <c CGXGridHandleWnd> 
CGXBrowserGrid::CGXBrowserGrid(CWnd* pGridWnd, CDocument* pGridDoc, BOOL bIsViewContext)
	: CGXGridCore(pGridWnd, pGridDoc, bIsViewContext)
{
	m_bUpdateDone = FALSE;
	m_bCacheCurrentCell = TRUE;
	m_nClipboardFlags = GX_DNDTEXT; // limit clipboard support to CF_TEXT
}

CGXBrowserGrid::~CGXBrowserGrid()
{
}

/////////////////////////////////////////////////////////////////////////////
// CGXBrowserGrid record count

// OnGetRecordCount()
//
// This method returns the number of records if last record has been accessed
// or LONG_MAX if record count is indetermined.
//
// If you know the exact record count in advance (maybe by using a "SELECT COUNT(*)"),
// you can override this method and return the record count.
//
// NOTE: If you return LONG_MAX, GetRowCount() will use pBrowseData->m_nRecordLastSeen
// for guessing the row count

long CGXBrowserGrid::OnGetRecordCount()
{
	// default: return rows in CGXData (we know exact record count)
	return max(0L, (long) GetParam()->GetData()->GetRowCount() - (long) GetHeaderRows());
}

// GetRowCount()
//
// This method is called to determine the number of rows in the
// grid. The default is to return the record count and add an
// extra row if the user can append rows (marked with an asterisk '*')
// and another extra row it the user is currently adding a new record.
//
// If the record count is not known yet, GetRowCount() will
// return m_nRecordLastSeen. The last seen record should be
// determined in OnTestGridDimension.
//
// FAQ:
// If you want that the grid fills up the entire view with
// empty cells, as for example Borland DBase does, you can
// override this method and return a bigger value.
//
// Example:
//
// ROWCOL CMyBrowserGrid::GetRowCount()
// {
//     return CGXBrowserGrid::GetRowCount()
//          + GetGridRect().Height()/GetDefaultRowHeight());
// }

ROWCOL CGXBrowserGrid::GetRowCount()
{
	return GetLastRow();
}

/////////////////////////////////////////////////////////////////////////////
// CGXBrowserGrid overridable for caching
//

void CGXBrowserGrid::OnFillCache()
{
	// Override this method if you want to add some enhanced caching.
	//
	// The first visible row in the grid can be determined with
	// ROWCOL nFirstRow = GetTopRow();
	// The last visible row can be determined with
	// ROWCOL nLastRow = CalcBottomRowFromRect(GetGridRect());
}

/////////////////////////////////////////////////////////////////////////////
// CGXBrowserGrid diagnostics

#ifdef _DEBUG
void CGXBrowserGrid::AssertValid() const
{
}

void CGXBrowserGrid::Dump(CDumpContext& dc) const
{
	dc;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGXBrowserGrid message handlers

void CGXBrowserGrid::OnGridInitialUpdate()
{
	// check parameter object
	CGXGridParam* pParam = GetParam();

	if (pParam == NULL)
		SetParam(pParam = new CGXBrowseParam);

	ASSERT(pParam && pParam->IsKindOf(RUNTIME_CLASS(CGXBrowseParam)));
	// ASSERTION-> This is not a CGXBrowseParam object.
	// You did probably use a CGXGridParam object instead. ->END

	CGXGridCore::OnGridInitialUpdate();
}

// InitBrowserSettings()
//
// Call this method from your derived OnGridInitialUpdate() or
// OnInitialUpdate() routine to initialize the default browser
// grid appearance.
//@doc
//@mfunc
//@syntax virtual void InitBrowserSettings();
//@rem
//Overridable which initializes the default grid appearance. 
//You should call this method from your <mf CGXBrowserGrid::OnInitialUpdate> method.
//@xref <c CGXBrowserGrid> <mf CGXGridCore::OnGridInitialUpdate>
void CGXBrowserGrid::InitBrowserSettings()
{
	// Initialize pointer to some objects
	CGXGridParam* pParam = GetParam();
	ASSERT_VALID(pParam);

	CGXStylesMap* pStyMap = pParam->GetStylesMap();
	ASSERT_VALID(pStyMap);

	CGXProperties* pProp = pParam->GetProperties();
	ASSERT_VALID(pProp);

	CGXBrowseParam* pBrowseData = GetBrowseParam();

	// Register user-defined controls
	RegisterControl(
			GX_IDS_CTRL_BROWSEARROWHEADER,
			new CGXBrowseGridArrowRowHeader(this)
		);

	if (pBrowseData && !pBrowseData->m_bIsBrowseInit)
	{
		BOOL bUndo = GetParam()->IsEnableUndo();
		GetParam()->EnableUndo(FALSE);

		// Following settings should only be initialized the first
		// time OnInitialUpdate is called. This is especially
		// usefull if the parameter-object is shared among
		// several views (MFC doc/view support) because OnInitialUpdate
		// is called for every new view.

		// Row and column headers
		ColHeaderStyle()
					.SetReadOnly(FALSE)
					.SetEnabled(FALSE); // Current cell cannot be moved to header

		RowHeaderStyle()
					.SetEnabled(FALSE)
					.SetControl(GX_IDS_CTRL_BROWSEARROWHEADER); // use previously registered header control

		// Special grid settings
		pParam->EnableMoveRows(FALSE);                  // rows cannot be dragged
		pParam->EnableMoveCols(TRUE);                   // columns can be dragged
		pParam->EnableTrackRowHeight(GX_TRACK_ALL);     // all rows have the same height.
		pParam->EnableThumbTrack(FALSE);                // thumb-tracking is disabled

		pParam->SetNumberedRowHeaders(FALSE);
		pParam->SetNumberedColHeaders(FALSE);

		// Do not allow selecting range of cells in the table
		// pParam->EnableSelection(GX_SELTABLE | GX_SELROW | GX_SELCOL);

		// set focus to control when moving current cell
		// pParam->SetActivateCellFlags(GX_CAFOCUS_SETCURRENT);

		// removing rows is not undoable for this kind of grid
		pParam->SetRemoveColsFlags(FALSE);
		pParam->SetRemoveRowsFlags(FALSE);

		pProp->SetMarkColHeader(FALSE);                 // Turn off pressed button effect for column headers
		pProp->SetPrintRowHeaders(FALSE);               // Don't print column headers

		// set row header width to 22 pixels
		SetColWidth(0, 0, 22);

		pBrowseData->m_bIsBrowseInit = TRUE;
		GetParam()->EnableUndo(bUndo);
	}
}

// SetMaxColWidth
//
// Loops through all columns and limits its
// size to nChar characters.

void CGXBrowserGrid::SetMaxColWidth(int nChar)
{
	CGXBrowseParam* pBrowseData = GetBrowseParam();

	ASSERT(pBrowseData);
	// ASSERTION-> You should first initalize the grid
	// before you call this method. Please make sure
	// that OnInitialUpdate has been called or at that
	// you did at least attach the parameter object! ->END

	// save setting
	GetBrowseParam()->m_nMaxColWidth = nChar;

	// loop through columns
	ROWCOL nCount = GetColCount();
	int nWidth = Width_LPtoDP( nChar * GX_NXAVGWIDTH );

	BOOL bLock = LockUpdate(TRUE);

	for (ROWCOL nCol = GetHeaderCols()+1; nCol <= nCount; nCol++)
	{
		if (GetColWidth(nCol) > nWidth)
			SetColWidth(nCol, nCol, nWidth);
	}

	LockUpdate(bLock);
}

// CanUpdate
//
// TRUE if the data in the grid can be changed
//@doc
//@mfunc
//@syntax virtual BOOL CanUpdate();
//@rdesc
//Non-zero if user can change data source; otherwise 0.
//@rem
//Called to determine if the user should be able to change data in the data source. 
//You may override 
//this method and return the CanUpdate state of your external data source (see example).
//@ex
/*
This example shows the DAO implementation of this method: |
BOOL CGXDaoGrid::CanUpdate()
{
   return m_pRecordset
      && m_pRecordset->IsOpen()
      && m_pRecordset->CanUpdate();
}
*/
//@xref <c CGXBrowserGrid>
BOOL CGXBrowserGrid::CanUpdate()
{
	return !IsReadOnly();
}

// CanAppend
//
// TRUE if user shall be able to append new rows.
// Call CGXBrowserGrid::SetCanAppend(FALSE) if you want to disable this feature.
//@doc
//@mfunc
//@syntax virtual BOOL CanAppend();
//@rdesc Non-zero if user can append records to the data source; otherwise 0.
//@rem
//Called to determine if the user should be able to append rows 
//to the data source. You may override this method and 
//return the CanAppend state of your external 
//data source and also call the base class version of this method (see example).
//@ex
/*
This example shows the DAO implementation of this method:|
BOOL CGXDaoGrid::CanAppend()
{
   return CGXBrowserGrid::CanAppend()
      && m_pRecordset
      && m_pRecordset->IsOpen()
      && m_pRecordset->CanAppend();
}
*/
//@xref <c CGXBrowserGrid> <mf CGXBrowserGrid::SetCanAppend >
BOOL CGXBrowserGrid::CanAppend()
{
	CGXBrowseParam* pBrowseData = GetBrowseParam();
	ASSERT(pBrowseData);

	return pBrowseData->m_bCanAppend && !IsReadOnly();
}

// GetFieldFromCol
//
// Returns the zero-based field index associated with a column.
// Performs well even if columns have been moved.
//
// Headers will return -1 !

//@doc
//@mfunc
//@syntax short GetFieldFromCol(ROWCOL nCol);
//@parm  ROWCOL | nCol | Specifies the column id.
//@rdesc 
//A zero-based short index.
//@rem
//Returns the zero-based field index associated with a column. 
//<mf CGXBrowserGrid::GetFieldFromCol> calls <mf CGXBrowserGrid::GetColIndex> and converts the column id 
//to a zero-based field index.<nl>
//<nl>
//If you override <mf CGXBrowserGrid::OnLoadCellStyle> (or any other methods where you connect the grid to 
//your data source), you should always take care to dereference the index associated with 
//a column. This enables your application to support rearranging columns.<nl>
//<nl>
//@ex
/*
This sample code shows you how you can use this method to dereference the 
original field associated with a column: |

   // determine field index for the column
   short nField = GetFieldFromCol(nCol);

   // now, I can determine field information
   CField* fld = GetDocument()->m_dbfile.GetField(nField);
*/
//@xref <c CGXBrowserGrid> <mf CGXBrowserGrid::GetColIndex> <mf CGXBrowserGrid::OnLoadCellStyle> 
short CGXBrowserGrid::GetFieldFromCol(ROWCOL nCol)
{
	return (short) (GetColIndex(nCol) - GetHeaderCols() - 1);
}

// GetRecordFromRow
//
// Returns the zero-based row index associated with a row
// Performs well even if rows have been sorted.
//
// Headers will return -1 !
//
// NOTE: If you always take care that you use
// GetRecordFromRow/GetRowIndex before reading data out of your
// data source, you can later easyly add support for
// sorting rows (see also dbfbrows sample). You will then only
// need to rearrange the m_awRowIndex array.
//@doc
//@mfunc
//@syntax long GetRecordFromRow(ROWCOL nRow);
//@parm ROWCOL | nRow | Specifies the row id.
//@rdesc
//A zero-based long number.
//@rem
//Returns the zero-based row index associated with a row. 
//<bold>GetRecordFromRow<ebold> calls <bold>GetRowIndex<ebold> and converts 
//the row id to a zero-based record index.<nl>
//<nl>
//If you override <mf CGXBrowserGrid::OnLoadCellStyle> (or any other methods where you 
//connect the grid to your data source), you should always take care to dereference the 
//index associated with a row. This will make it possible to add support for sorting rows.
//The DbfBrows sample application demonstrates how to add support for sorting the grid.
//@ex
//This sample code shows you how you can use this method to dereference 
//the original record associated with a row: |
/*
   // determine the record for the row
   long nRecord = GetRecordFromRow(nRow);

   // now, I can seek to the record
   GetDocument()->m_dbfile.Seek(nRecord);
*/
//@xref <mf CGXBrowserGrid::GetRowIndex> <mf CGXBrowserGrid::OnLoadCellStyle> 
long CGXBrowserGrid::GetRecordFromRow(ROWCOL nRow)
{
	return (long) GetRowIndex(nRow) - (long) GetHeaderRows() - 1L;
}

// GetRowIndex
//
// GetRowIndex is usefull for sorted rows so that
// the original pointer can be dereferenced
//@doc
//@mfunc
//@syntax virtual ROWCOL GetRowIndex(ROWCOL nRow);
//@parm ROWCOL | nRow | Specifies the row id.
//@rdesc
//A ROWCOL index for the row.
//@rem
//<bold>GetRowIndex<ebold> returns the original row id for a given row. 
//This original row id can be different from the given row when 
//the row has been moved or the grid has been sorted.<nl>
//<nl>
//<bold>GetRowIndex<ebold> is called to dereference the index associated 
//with the specified row. This method adds support for rearranging rows in the grid. 
//The return value is one-based.<nl>
//<nl>
//The base-class version retrieves the index from the <md CGXBrowserGrid::m_awRowIndex> 
//array maintained in the <c CGXBrowseParam> object.
//This is sufficient in most cases, but in some special cases you 
//may wish to maintain your personal index array or maybe even store the 
//index array in a file. You can support these special scenarios 
//by overriding this method.<nl>
//<nl>
//<c CGXBrowserGrid> also provides another method called <mf CGXBrowserGrid::GetRecordFromRow>.
//<mf CGXBrowserGrid::GetRecordFromRow> calls <mf CGXBrowserGrid::GetRowIndex> and converts the row id to a zero-based record index.
//@xref <c CGXBrowserGrid> <mf CGXBrowserGrid::GetRecordFromRow> <c CGXBrowseParam> 
ROWCOL CGXBrowserGrid::GetRowIndex(ROWCOL nRow)
{
	CGXBrowseParam* pBrowseData = GetBrowseParam();

	if (nRow >= (ROWCOL) INT_MAX)
		return nRow;

	int n = (int) nRow;

	// if there is no reference stored, simply
	// return the passed reference

	// as long as a row has not been moved
	// to another place, it will be zero and
	// therefore this method will return the
	// original row id.

	if (n <= pBrowseData->m_awRowIndex.GetUpperBound()
		&& pBrowseData->m_awRowIndex[n] != 0)
	{
		return pBrowseData->m_awRowIndex[n];
	}

	return nRow;
}

// GetColIndex
//
// GetColIndex is usefull for moved columns so that
// the original pointer can be dereferenced
//@doc
//@mfunc
//@syntax virtual ROWCOL GetColIndex(ROWCOL nCol);
//@parm ROWCOL | nCol | Specifies the column id.
//@rdesc
//A <bold>ROWCOL<ebold> index for the row.
//@rem
//<bold>GetColIndex<ebold> returns the original column id for a given column. 
//This original column id can be different from the given column when the column has 
//been moved or the grid has been sorted.<nl>
//<nl> 
//<bold>GetColIndex<ebold> is called to dereference the index associated 
//with the specified column. This method adds support for rearranging columns in the grid. 
//The return value is one-based.<nl>
//<nl>
//The base-class version retrieves the index from the <md CGXBrowserGrid::m_awColIndex> array maintained 
//in the <c CGXBrowseParam> object.  This is sufficient for most cases, but in some special 
//cases you may wish to maintain your personal index array or maybe even store the 
//index-array in a file. You can support these special scenarios by overriding this method.<nl>
//<nl>
//<c CGXBrowserGrid> also provides another method called <mf CGXBrowserGrid::GetFieldFromCol>. 
//<mf CGXBrowserGrid::GetFieldFromCol> calls <mf CGXBrowserGrid::GetColIndex> and converts 
//the column id to a zero-based field index.
//@xref <c CGXBrowserGrid> <mf CGXBrowserGrid::GetFieldFromCol> <mf CGXBrowseParam> 
ROWCOL CGXBrowserGrid::GetColIndex(ROWCOL nCol)
{
	CGXBrowseParam* pBrowseData = GetBrowseParam();

	if (nCol >= (ROWCOL) INT_MAX)
		return nCol;

	int n = (int) nCol;

	// if there is no reference stored, simply
	// return the passed reference

	// as long as a column has not been moved
	// to another place, it will be zero and
	// therefore this method will return the
	// original column id.

	if (n <= pBrowseData->m_awColIndex.GetUpperBound()
		&& pBrowseData->m_awColIndex[n] != 0)
	{
		return pBrowseData->m_awColIndex[n];
	}

	return nCol;
}

// StoreMoveCols
//
// StoreMoveCols rearranges the internal m_awColIndex
// array, when columns have been moved. If you always
// take care to call GetColIndex or GetFieldFromCol
// before acessing values, you will easily have
// support for moving columns in your browser.

BOOL CGXBrowserGrid::StoreMoveCols(ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nDestCol, BOOL bProcessed)
{
	CGXBrowseParam* pBrowseData = GetBrowseParam();
	ASSERT(pBrowseData);

	// rearrange the array with column indexes

	int nIndex = (int) nFromCol;
	int nCount = (int) nToCol - (int) nFromCol + 1;
	int nDest = (int) nDestCol;

	int nFirst = min(nIndex, nDest);
	int nLast = max(nIndex+nCount, nDest+nCount);

	bProcessed = FALSE;

	// easiest case: nothing to do
	if (nDest == nIndex || nCount == 0)
		NULL;

	// move columns to the left
	else if (nDest < nIndex)
	{
		nIndex += nCount;
		bProcessed = TRUE;
	}

	// move columns to the right
	else if (nDest > nIndex)
	{
		nDest += nCount;
		bProcessed = TRUE;
	}

	// do the job
	if (bProcessed && pBrowseData)
	{
		// First, assign column ids to the entries in the range
		// which not yet have a valid column id.

		int n;

		if(pBrowseData->m_awColIndex.GetUpperBound() < nLast)
			pBrowseData->m_awColIndex.SetSize(nLast+1);

		for (n = nFirst; n < nLast; n++)
		{
			if(pBrowseData->m_awColIndex[n] == 0)
				pBrowseData->m_awColIndex[n] = (ROWCOL) n;
		}

		pBrowseData->m_awColIndex.InsertAt(nDest, 0, nCount);

		// initialize the new columns
		for (n = 0; n < nCount; n++)
		{
			pBrowseData->m_awColIndex[nDest+n] = pBrowseData->m_awColIndex[nIndex+n];
		}

		pBrowseData->m_awColIndex.RemoveAt(nIndex, nCount);
	}

	return CGXGridCore::StoreMoveCols(nFromCol, nToCol, nDestCol, bProcessed);
}

// StoreRemoveCols
//
// see Note below.

BOOL CGXBrowserGrid::StoreRemoveCols(ROWCOL nFromCol, ROWCOL nToCol, BOOL bProcessed)
{
	CGXBrowseParam* pBrowseData = GetBrowseParam();
	ASSERT(pBrowseData);

	ROWCOL nColCount = GetColCount();
	if (nFromCol > nColCount)
		return FALSE;

	nToCol = min(nToCol, nColCount);

	bProcessed = TRUE;

	// if record is dirty, we need to update it
	// because the current record buffer needs to be
	// reinitialized with the new column count
	if (IsRecordDirty())
	{
		CString s;
		if (!Update(&s))
			return FALSE;
	}

	int nIndex = (int) nFromCol;
	int nCount = (int) nToCol - (int) nFromCol + 1;

	if(pBrowseData)
	{
		// First, make sure all columns have an index
		pBrowseData->m_awColIndex.SetSize((int) nColCount+1);
		for (ROWCOL nCol = nFromCol; nCol <= nColCount; nCol++)
		{
			if (pBrowseData->m_awColIndex[(int) nCol] == 0)
				pBrowseData->m_awColIndex[(int) nCol] = nCol;
		}

		// Now, we can remove columns
		if (nIndex <= pBrowseData->m_awColIndex.GetUpperBound())
			pBrowseData->m_awColIndex.RemoveAt(nIndex,
			min(nCount, pBrowseData->m_awColIndex.GetUpperBound()-nIndex+1));
	}

	// Note:
	// This method makes the assumption that if you delete
	// columns, the real columns will not be deleted in
	// the data structure that you are broswing with this grid.
	// They only will not be visible any more in the grid.
	//
	// Example:
	// You have 5 columns. GetColIndex(n) returns 1 2 3 4 5 for n = 1..5
	// Now, you remove column 2:
	// Then GetColIndex returns 1 3 4 5 for n = 1..4
	// If you need a different behavior, you have to override this
	// method.

	BOOL b = CGXGridCore::StoreRemoveCols(nFromCol, nToCol, bProcessed);

	// reinitialize current record buffer with the new column count
	EmptyEditBuffer();

	return b;
}

// StoreInsertCols
//
// see Note below.

BOOL CGXBrowserGrid::StoreInsertCols(ROWCOL nCol, ROWCOL nCount, BOOL bProcessed)
{
	CGXBrowseParam* pBrowseData = GetBrowseParam();
	ASSERT(pBrowseData);
	bProcessed = TRUE;

	// if record is dirty, we need to update it
	// because the current record buffer needs to be
	// reinitialized with the new column count
	if (IsRecordDirty())
	{
		CString s;
		if (!Update(&s))
			return FALSE;
	}

	int nIndex = (int) nCol;
	int nInsert = (int) nCount;
	int nColCount = (int) (pBrowseData->m_nFields > GetColCount()) ? pBrowseData->m_nFields : GetColCount();

	if (pBrowseData->m_awColIndex.GetUpperBound() < nColCount)
		pBrowseData->m_awColIndex.SetSize(nColCount+1);

	// initialize columns after the insertion point
	int n;
	for (n = nIndex; n <= nColCount; n++)
	{
		if (pBrowseData->m_awColIndex[n] == 0)
			pBrowseData->m_awColIndex[n] = (ROWCOL) n;
	}

	pBrowseData->m_awColIndex.InsertAt(nIndex, 0, nInsert);

	// Note:
	// This method makes the assumption that if you insert
	// columns, the real columns will be appended in
	// your data structure you are broswing with this grid.
	//
	// Example:
	// You have 5 columns. GetColIndex(n) returns 1 2 3 4 5 for n = 1..5
	// Now, you insert two column at column 2:
	// Then GetColIndex returns 1 6 7 3 4 5 for n = 1..7
	// If you need a different behavior, you have to override this
	// method.

	// initialize the new columns
	for (n = 0; n < nInsert; n++)
		pBrowseData->m_awColIndex[nIndex+n] = ++nColCount;

	BOOL b = CGXGridCore::StoreInsertCols(nCol, nCount, bProcessed);

	// reinitialize current record buffer with the new column count
	EmptyEditBuffer();

	return b;
}

// StoreMoveRows
//
// StoreMoveRows rearranges the internal m_awRowIndex
// array, when rows have been moved. If you always
// take care to call GetRowIndex or GetFieldFromRow
// before acessing values, you will easily have
// support for moving Rowumns in your browser.

BOOL CGXBrowserGrid::StoreMoveRows(ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow, BOOL bProcessed)
{
	CGXBrowseParam* pBrowseData = GetBrowseParam();
	ASSERT(pBrowseData);
	// rearrange the array with column indexes

	int nIndex = (int) nFromRow;
	int nCount = (int) nToRow - (int) nFromRow + 1;
	int nDest = (int) nDestRow;

	int nFirst = min(nIndex, nDest);
	int nLast = max(nIndex+nCount, nDest+nCount);

	bProcessed = FALSE;

	// easiest case: nothing to do
	if (nDest == nIndex || nCount == 0)
		NULL;

	// move columns to the left
	else if (nDest < nIndex)
	{
		nIndex += nCount;
		bProcessed = TRUE;
	}

	// move columns to the right
	else if (nDest > nIndex)
	{
		nDest += nCount;
		bProcessed = TRUE;
	}

	// do the job
	if (bProcessed)
	{
		// First, assign column ids to the entries in the range
		// which not yet have a valid column id.

		int n;

		if (pBrowseData->m_awRowIndex.GetUpperBound() < nLast)
			pBrowseData->m_awRowIndex.SetSize(nLast+1);

		for (n = nFirst; n < nLast; n++)
		{
			if (pBrowseData->m_awRowIndex[n] == 0)
				pBrowseData->m_awRowIndex[n] = (ROWCOL) n;
		}

		pBrowseData->m_awRowIndex.InsertAt(nDest, 0, nCount);

		// initialize the new columns
		for (n = 0; n < nCount; n++)
		{
			pBrowseData->m_awRowIndex[nDest+n] = pBrowseData->m_awRowIndex[nIndex+n];
		}

		pBrowseData->m_awRowIndex.RemoveAt(nIndex, nCount);
	}

	return CGXGridCore::StoreMoveRows(nFromRow, nToRow, nDestRow, bProcessed);
}

// StoreRemoveRows
//
// see Note below.

BOOL CGXBrowserGrid::StoreRemoveRows(ROWCOL nFromRow, ROWCOL nToRow, BOOL bProcessed)
{
	CGXBrowseParam* pBrowseData = GetBrowseParam();
	ASSERT(pBrowseData);

	ROWCOL nRowCount = GetRowCount();
	if (nFromRow > nRowCount)
		return FALSE;

	nToRow = min(nToRow, nRowCount);

	bProcessed = TRUE;

	// if record is dirty, we need to update it
	if (IsRecordDirty())
	{
		CString s;
		if (!Update(&s))
			return FALSE;
	}

	int nIndex = (int) nFromRow;
	int nCount = (int) nToRow - (int) nFromRow + 1;

	// First, make sure all rows have an index
	pBrowseData->m_awRowIndex.SetSize((int) nRowCount+1);
	for (ROWCOL nRow = nFromRow; nRow <= nRowCount; nRow++)
	{
		if (pBrowseData->m_awRowIndex[(int) nRow] == 0)
			pBrowseData->m_awRowIndex[(int) nRow] = nRow;
	}

	// Now, we can remove rows
	if (nIndex <= pBrowseData->m_awRowIndex.GetUpperBound())
		pBrowseData->m_awRowIndex.RemoveAt(nIndex,
		min(nCount, pBrowseData->m_awRowIndex.GetUpperBound()-nIndex+1));

	// Note:
	// This method makes the assumption that if you delete
	// rows, the real rows will not be deleted in
	// the data structure that you are broswing with this grid.
	// They only will not be visible any more in the grid.

	BOOL b = CGXGridCore::StoreRemoveRows(nFromRow, nToRow, bProcessed);

	return b;
}

// StoreInsertRows
//
// see Note below.

BOOL CGXBrowserGrid::StoreInsertRows(ROWCOL nRow, ROWCOL nCount, BOOL bProcessed)
{
	CGXBrowseParam* pBrowseData = GetBrowseParam();
	ASSERT(pBrowseData);
	bProcessed = TRUE;

	// if record is dirty, we need to update it
	// because the current record buffer needs to be
	// reinitialized with the new column count
	if (IsRecordDirty())
	{
		CString s;
		if (!Update(&s))
			return FALSE;
	}

	int nIndex = (int) nRow;
	int nInsert = (int) nCount;
	int nRowCount = (int) GetRowCount();

	if (pBrowseData->m_awRowIndex.GetUpperBound() < nRowCount)
		pBrowseData->m_awRowIndex.SetSize(nRowCount+1);

	// initialize the rows after the insertion point
	int n;
	for (n = nIndex; n <= nRowCount; n++)
	{
		if (pBrowseData->m_awRowIndex[n] == 0)
			pBrowseData->m_awRowIndex[n] = (ROWCOL) n;
	}

	pBrowseData->m_awRowIndex.InsertAt(nIndex, 0, nInsert);

	// Note:
	// This method makes the assumption that if you insert
	// rows, the real rows will be appended in
	// your data structure that you are broswing with this grid.

	// initialize the new columns
	for (n = 0; n < nInsert; n++)
		pBrowseData->m_awRowIndex[nIndex+n] = ++nRowCount;

	BOOL b = CGXGridCore::StoreInsertRows(nRow, nCount, bProcessed);

	return b;
}

// RemoveCols
//
// special handling for the CGXGridCore::RemoveCols method
// as we do not support undoing this action. This would
// get too complex with external data sources.
//

BOOL CGXBrowserGrid::RemoveCols(ROWCOL nFromCol, ROWCOL nToCol, UINT flags /* = GX_UPDATENOW */, GXCmdType ctCmd /*= gxDo*/)
{
	// RemoveCols does not support undo!

	// Turn off undo creation
	BOOL bEnableUndo = GetParam()->IsEnableUndo();
	GetParam()->EnableUndo(FALSE);

	// Execute the command
	BOOL bSuccess =
		CGXGridCore::RemoveCols(nFromCol, nToCol, flags, ctCmd);

	// If command was succesfull, empty undo/redo list
	// so that nothing gets messed up
	if (bSuccess)
	{
		GetParam()->EmptyUndoList();
		GetParam()->EmptyRedoList();
	}

	// reenable undo support
	GetParam()->EnableUndo(bEnableUndo);

	return bSuccess;
}

// RemoveRows
//
// special handling for the CGXGridCore::RemoveRows method
// as we do not support undoing this action. This would
// get too complex with external data sources.
//

BOOL CGXBrowserGrid::RemoveRows(ROWCOL nFromRow, ROWCOL nToRow, UINT flags /* = GX_UPDATENOW */, GXCmdType ctCmd /*= gxDo*/)
{
	// RemoveRows does not support undo!

	// Turn off undo creation
	BOOL bEnableUndo = GetParam()->IsEnableUndo();
	GetParam()->EnableUndo(FALSE);

	// Execute the command
	BOOL bSuccess =
		CGXGridCore::RemoveRows(nFromRow, nToRow, flags, ctCmd);

	// If command was succesfull, empty undo/redo list
	// so that nothing gets messed up
	if (bSuccess)
	{
		GetParam()->EmptyUndoList();
		GetParam()->EmptyRedoList();
	}

	// reenable undo support
	GetParam()->EnableUndo(bEnableUndo);

	return bSuccess;
}

// GetAppendRow
//
// Returns the row number for the append row.
// GX_INVALID if not supported.

//@doc
//@mfunc
//@syntax virtual ROWCOL GetAppendRow();
//@rdesc
//A <bold>ROWCOL<ebold> index for the append row. <bold>GX_INVALID<ebold> if not supported.
//@rem
//Returns the row id for the append row.
//If CanAppend returns <bold>FALSE<ebold> or if the last record has not been seen yet, 
//it will return <bold>GX_INVALID<ebold>.
//@xref <c CGXBrowserGrid> <mf CGXBrowserGrid::CanAppend> <mf CGXBrowserGrid::OnGetRecordCount> 
ROWCOL CGXBrowserGrid::GetAppendRow()
{
	if (!CanAppend() || OnGetRecordCount() == LONG_MAX)
		return GX_INVALID;

	return (ROWCOL) OnGetRecordCount() + GetHeaderRows() + 1;
}

// GetLastRow
//
// Returns the row number for the last row.
//@doc
//@mfunc
//@syntax virtual ROWCOL GetLastRow();
//@rdesc
//A <bold>ROWCOL<ebold> index specifying the last row.
//@rem
//Returns the row number for the last record.<nl> 
//<nl>
//If the record count is unknown, <bold>GetLastRow<ebold> will return the high-water mark 
//(m_nRecordLastSeen in <c CGXBrowseParam>). If the data source allows appending rows, 
//<bold>GetLastRow<ebold> will return the row id for the append-row (which is marked with an 
//asterisk in the row header).
//@xref <c CGXBrowserGrid> <mf CGXBrowserGrid::OnGetRecordCount>
//<mf CGXBrowserGrid::CanAppend> <c CGXBrowseParam> 
ROWCOL CGXBrowserGrid::GetLastRow()
{
	// estimate record count (if not yet known)

	CGXBrowseParam* pBrowseData = GetBrowseParam();
	ASSERT(pBrowseData);
	long lCount = OnGetRecordCount();

	// check if GetRecordCount() did return the last seen record
	if (lCount == LONG_MAX)
		lCount = pBrowseData->m_nRecordLastSeen+1;

	if (pBrowseData->m_bEOFSeen)
	{
		if (!IsPrinting())
		{
			if (CanAppend())
				lCount++;

			if (pBrowseData->m_nEditMode == addnew)
				lCount++;
		}
	}

	return lCount + GetHeaderRows();
}

// GetFirstRow
//
// Returns the row number for the first row.
//@doc
//@mfunc
//@rdesc
//A <bold>ROWCOL<ebold> index specifying the first row.
//@rem
//Returns the row number for the first record.
//@xref <c CGXBrowserGrid>
ROWCOL CGXBrowserGrid::GetFirstRow()
{
	return GetHeaderRows()+1;
}

// IsOnFirstRecord
//
//@doc
//@mfunc
//@syntax BOOL IsOnFirstRecord();
//@rdesc
//Nonzero if current record is first row; otherwise 0.
//@rem
//Returns nonzero if the current record is the first record.
//@xref <c CGXBrowserGrid>
BOOL CGXBrowserGrid::IsOnFirstRecord()
{
	ROWCOL nRow, nCol;
	return GetCurrentCell(nRow, nCol) && nRow <= GetFirstRow();
}

// IsOnLastRecord
//

//@doc
//@mfunc
//@syntax BOOL IsOnLastRecord();
//@rdesc
//Nonzero if current record is the last row; otherwise 0.
//@rem
//Returns nonzero if the current record is the last row 
//(when CanUpdate returns <bold>TRUE<ebold>, the last row is the append row).
//@xref <mf CGXBrowserGrid>
BOOL CGXBrowserGrid::IsOnLastRecord()
{
	ROWCOL nRow, nCol;
	if (!GetCurrentCell(nRow, nCol))
		return FALSE;

	// Never TRUE as long as we have not seen the last record

	return nRow == GetLastRow();
}

// MoveTo
//
// This method tries to position the recordset to the given
// row. It will return FALSE if the positioning failed.
//
// You should override thise method to position the current
// record in your external data source.

//@doc
//@mfunc
//@syntax BOOL MoveTo(ROWCOL nRow)
//@parm ROWCOL | nRow | Specifies the row id.
//@rdesc
//Nonzero if successful; otherwise 0.
//@rem
//Called to position the recordset to the given row. 
//You should return <bold>FALSE<ebold> if the positioning failed. See the attached example.<nl>
//<nl>
//One reason the positioning could fail and that you should return <bold>FALSE<ebold> 
//is if nRow is larger than the record count.
//@ex
/*
This sample demonstrates how <bold>MoveTo<ebold> positions the current 
record by calling <bold>SetAbsolutePosition<ebold> for a <bold>CDaoRecordset<ebold>. 
If the positioning fails, the method returns <bold>FALSE<ebold>. |
BOOL CGXDaoGrid::MoveTo(ROWCOL nRow)
{
   CGXBrowseParam* pBrowseData = GetBrowseParam();

   if (m_pRecordset == NULL || !m_pRecordset->IsOpen() ||
      (long) (nRow-GetHeaderRows()) > OnGetRecordCount())
      return FALSE;

   long nRecord = GetRecordFromRow(nRow);

   long nCurrentRecord = m_pRecordset->GetAbsolutePosition();

   if (nCurrentRecord == nRecord)
      return TRUE;

   try
   {
      if (abs(nCurrentRecord-nRecord) > pBrowseData->m_lMoveRecordWaitCursor)
      {
         // display wait cursor
         CGXWaitCursor theWait;
         m_pRecordset->SetAbsolutePosition(nRecord);
      }
      else
         m_pRecordset->SetAbsolutePosition(nRecord);
   }
   catch (CDaoException* e)
   {
      e->Delete();
      return FALSE;
   }

   if (m_pRecordset->IsEOF())
   {
      pBrowseData->m_bEOFSeen = TRUE;
      return FALSE;
   }

   return TRUE;
}
*/
//@xref <c CGXBrowserGrid>
BOOL CGXBrowserGrid::MoveTo(ROWCOL nRow)
{
	// no positioniong necessary when used with CGXData object.

	CGXBrowseParam* pBrowseData = GetBrowseParam();
	ASSERT(pBrowseData);
	long lCount = OnGetRecordCount();

	// check if GetRecordCount() did return the last seen record
	if (lCount == LONG_MAX)
		lCount = pBrowseData->m_nRecordLastSeen+1;

	ROWCOL nLastRow = (ROWCOL) lCount + GetHeaderRows();

	return nRow <= nLastRow;
}

// DeleteRecords
//
// Called to delete selected records from the data souce.
//
//@doc
//@mfunc
//@syntax virtual void DeleteRecords();
//@rem
//Called to delete all selected records.<nl>
//<nl>
//Records can be selected from the user by clicking on the row header 
//or programmatically with the <mf CGXBrowserGrid::SelectRange> command.<nl>
//<nl>
//The record will be deleted by calling the virtual method <mf CGXBrowserGrid::DeleteRows>. <nl>
//If you want to support deleting records from your bound data source, 
//it is recommended that you override <mf CGXBrowserGrid::DeleteRows> and not <mf CGXBrowserGrid::DeleteRecords>.
//@xref <c CGXBrowserGrid> <mf CGXGridCore::SelectRange> <mf CGXBrowserGrid::DeleteRows>  
void CGXBrowserGrid::DeleteRecords()
{
	CGXRangeList* pSelList = GetParam()->GetRangeList();

	if (!CanUpdate() || IsReadOnly() || !pSelList)
		return;

	// check that whole rows are selected and that "new row" is not selected
	if (!pSelList->IsAnyCellFromCol(0)
		|| pSelList->IsAnyCellFromRow( GetAppendRow() )
		)
		return;

	CRowColArray awRowStart, awRowEnd;
	GetSelectedRows(awRowStart, awRowEnd, TRUE, FALSE);

	DeleteRows(awRowStart, awRowEnd);
}

//@doc
//@mfunc
//@syntax virtual void DeleteRows(const CRowColArray& awRowStart, const CRowColArray& awRowEnd, BOOL* pbSuccess = NULL);
//@syntax void DeleteRows(ROWCOL nFromRow, ROWCOL nToRow);
//@syntax void DeleteRows(const CGXRange& range);
//@parm const CRowColArray& | awRowStart | Reference to an array of <bold>ROWCOL<ebold> attributes which holds the first row of each range to be deleted.
//@parm const CRowColArray& | awRowEnd   | Reference to an array of <bold>ROWCOL<ebold> attributes which holds the last row of each range to be deleted.
//@parm ROWCOL | nFromRow | Specifies the first row in the range of cells which should be deleted.
//@parm ROWCOL | nTopRow | Specifies the last row in the range of cells which should be deleted.
//@parm const CGXRange& | range | Specifies the range of cells to be deleted.
//@parm BOOL* | pbSuccess | Pointer to a BOOL for storing the success value of the operation.
//@rem
//Call this method if you want to delete rows from the grid. 
//You need not select a range of rows before calling this method because 
//you can directly specify the range of rows to be deleted.<nl>
//<nl>
//<mf CGXBrowserGrid::DeleteRows> will loop through the specified array of rows and delete them from the data source.<nl>
//<nl>
//If you have derived your own class from <c CGXBrowserGrid> 
//and bound it to an external data source, and if you want to 
//support deleting rows in your bound data source, you should override 
//the virtual variant of <mf CGXBrowserGrid::DeleteRows>.<nl>
//<nl>
//The other two variants are simple wrappers for the virtual variant. 
//They simplify calling this method.
//@xref <c CGXBrowserGrid> <mf CGXBrowserGrid::DeleteRecords> 
void CGXBrowserGrid::DeleteRows(ROWCOL nFromRow, ROWCOL nToRow)
{
	CRowColArray awRowStart, awRowEnd;
	awRowStart.SetAtGrow(0, nFromRow);
	awRowEnd.SetAtGrow(0, nToRow);

	DeleteRows(awRowStart, awRowEnd);
}

void CGXBrowserGrid::DeleteRows(const CGXRange& range)
{
	CRowColArray awRowStart, awRowEnd;
	awRowStart.SetAtGrow(0, range.top);
	awRowEnd.SetAtGrow(0, range.bottom);

	DeleteRows(awRowStart, awRowEnd);
}

void CGXBrowserGrid::DeleteRows(const CRowColArray& awRowStart, const CRowColArray& awRowEnd, BOOL* pbSuccess)
{
	// Save current cell's data
	TransferCurrentCell();

	// Empty undo/redo list
	if (GetParam()->IsEnableUndo())
	{
		GetParam()->EmptyUndoList();
		GetParam()->EmptyRedoList();
	}

	BeginTrans(m_pAppData->strmRemoveRows);
	BOOL bLockUpdate = LockUpdate(TRUE);

	for (int nIndex = (int)awRowStart.GetUpperBound(); nIndex >= 0; nIndex--)
		RemoveRows(awRowStart[nIndex], awRowEnd[nIndex]);

	LockUpdate(bLockUpdate);
	CommitTrans();
	Redraw();

	if (pbSuccess != NULL)
		*pbSuccess = TRUE; 

	// User can undo this action, but as soon as he starts editing a
	// row, undo information will be lost again!
}


// SetCurrentCell
//

BOOL CGXBrowserGrid::SetCurrentCell(ROWCOL nRow, ROWCOL nCol, UINT flags /* = GX_UPDATENOW */)
{
	if (nCol <= GetHeaderCols())
	{
		nCol = min(GetHeaderCols()+1, GetColCount());
	}

	return CGXGridCore::SetCurrentCell(nRow, nCol, flags);
}

// Requery
//

void CGXBrowserGrid::Requery()
{
	CGXBrowseParam* pBrowseData = GetBrowseParam();
	ASSERT(pBrowseData);
	// Reset current cell's data
	TransferCurrentCell(FALSE);
	if(pBrowseData)
	{
		pBrowseData->m_nRecordLastSeen = -1;
	}
}

// Overridables - Load cell styles and flush values

// OnLoadCellStyle
//
// give the programmer the chance to load the value from data source
// or apply additional formattings at runtime
//
// NOTE: You should override the following members instead
// of GetStyleRowCol/StoreStyleRowCol. They provide a better
// abstraction for loading/storing cell values in a CGXBrowserGrid

// The methods will be called when needed from CGXBrowserGrid::Update(),
// CGXBrowserGrid::GetStyleRowCol, CGXBrowserGrid::StoreStyleRowCol and
// CGXBrowserGrid::SetStyleRange

BOOL CGXBrowserGrid::OnLoadCellStyle(ROWCOL /*nRow*/, ROWCOL /*nCol*/, CGXStyle& /*style*/, LPCTSTR /*pszExistingValue*/)
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

	return FALSE;   // return TRUE if you have Existing the style object!
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

//@doc
//@mfunc
//@syntax virtual BOOL OnFlushRecord(ROWCOL nRow, CString* ps = NULL); throw( CException );
//@parm  ROWCOL | nRow | Specifies the row id.
//@parm  CString* | ps | Specifies a pointer to a <c CString> where 
//the method should store a warning text if the operation did fail or throw an exception. 
//If ps is <bold>NULL<ebold>, Update will not catch any exception.
//@rdesc
//Nonzero if successful; otherwise 0.
//@rem
//This method writes dirty fields back to the data source and 
//prepares the data source at record level before changes 
//are written to it with <mf CGXBrowserGrid::OnFlushCellValue>.<nl>
//<nl>
//This action can raise exceptions. Sometimes it is necessary for the method to 
//catch the exception, sometimes it is necessary that the exception fall through. 
//This behavior is determined through the ps parameter.<nl>
//<nl>
//If ps is <bold>NULL<ebold>, <mf CGXBrowserGrid::OnFlushRecord> will let exceptions fall through. 
//If ps is a pointer to a <c CString>, exceptions will be caught, and ps 
//will be initialized with the text describing the exception.<nl>
//<nl>
//This method will call <mf CGXBrowserGrid::OnFlushCellValue> for any dirty cell in the current record buffer.<nl>
//<nl>
//You should override this method if you need to prepare your data source at record-level 
//before changes are written to it with <mf CGXBrowserGrid::OnFlushCellValue>. For example, <c CGXDaoGrid> will either 
//call <bold>pRecordset->AddNew<ebold> or <bold>pRecordset->Edit<ebold> before calling the base class version of 
//<bold>OnFlushRecord<ebold> and after that calls <mf CGXBrowserGrid::Update> (see attached example). Another typical scenario 
//could be that you simply have to seek to a specific record in the data source.<nl>
//<nl>
//You may also override <bold>OnFlushRecord<ebold> if you want to handle additional exceptions 
//and set the appropriate warning text by retrieving the information from the exception object.<nl>
//<nl>
//When overriding this method, it is strongly recommended that you dereference 
//the record index associated with a row by calling the <mf CGXBrowserGrid::GetRecordFromRow> method.<nl>
//<nl>
//<bold>Example<ebold><nl>
//<nl>
//The following two samples demonstrate the two scenarios described above.<nl>
//<nl>
//a) <bold>CGXDaoGrid::OnFlushRecord<ebold> either calls <bold>pRecordset->AddNew<ebold> or 
//<bold>pRecordset->Edit<ebold> before calling the base class version of 
//<bold>OnFlushRecord<ebold> and after that calls <mf CGXBrowserGrid::Update>.<nl>
//<nl>
//<pre><code>
//BOOL CGXDaoGrid::OnFlushRecord(ROWCOL nRow, CString* ps)
//{
//   CGXBrowseParam* pBrowseData = GetBrowseParam();
//<nl>
//   try
//   {
//     COleVariant varBookmarkCurrent;
//      if (m_pRecordset->CanBookmark() && !m_pRecordset->IsEOF() && !m_pRecordset->IsBOF())
//         varBookmarkCurrent = m_pRecordset->GetBookmark();
//<nl>
//      // Sandwich CDaoRecordset into Edit/AddNew and Update
//      if (pBrowseData->m_nEditMode == addnew)
//         m_pRecordset->AddNew();
//      else
//      {
//         VERIFY(MoveTo(nRow));
//         m_pRecordset->Edit();
//      }
//<nl>
//      // Force writing dirty cells to CDaoRecordset
//      // Base class version contains the necessary functionality
//      // to check all fields and call OnFlushCellValue
//<nl>
//      CGXBrowserGrid::OnFlushRecord(nRow, NULL /* force throwing an exception */);
//<nl>
//      m_pRecordset->Update();
//<nl>
//      if (varBookmarkCurrent)
//         m_pRecordset->SetBookmark(varBookmarkCurrent);
//   }
//   catch (CDaoException* e)
//   {
//      GridWnd()->SendMessage(WM_CANCELMODE, 0, 0);
//<nl>
//      // Reset cursor
//      if (!m_pRecordset->IsEOF() && !m_pRecordset->IsBOF())
//         m_pRecordset->SetFieldDirty(NULL, FALSE);
//<nl>
//      // ps is a valid CString if we shall catch the exception
//      if (ps)
//      {
//         TRACE0("CGXDaoGrid::OnFlushRecord failed!\n");
//<nl>
//         *ps = e->m_pErrorInfo->m_strDescription;
//         e->Delete();
//      }
//      // else
//         // let exception fall through
//<nl>
//      // failed, ...
//     return FALSE;
//   }
//   catch (CException* e)
//   {
//      // ps is a valid CString if we shall catch the exception
//      if (ps)
//      {
//         TRACE0("CGXDaoGrid::OnFlushRecord failed!\n");
//<nl>
//         ps->Empty();
//         e->Delete();
//     }
//      // else
//        // let exception fall through
//<nl>
//      // failed, ...
//      return FALSE;
//   }
//<nl>
//   return TRUE;
//}
//<ecode><epre>
//b) CDbfBrowserView::OnFlushRecord (from the DbfBrows sample) simply seeks to 
//a specific record in the data source and, after calling the base class version of <bold>OnFlushRecord<ebold>,
//flushes the changes to the current record.
//<pre><code>
//BOOL CDbfBrowserView::OnFlushRecord(ROWCOL nRow, CString* ps)
//{
//   ASSERT(nRow <= LONG_MAX);
//   long nRecord = GetRecordFromRow(nRow);
//<nl>
//   if (!GetDocument()->m_dbfile.Seek(nRecord))
//      return FALSE;
//<nl>
//   // Force writing dirty cells to DBase file
//   // Base class version contains the necessary functionality
//   // to check all fields and call OnFlushCellValue
//<nl>
//   TRY
//   {
//      CGXBrowserGrid::OnFlushRecord(nRow, NULL /* force throwing exception */);
//  }
//   CATCH(CException, e)
//   {
//      // ps is a valid CString if we shall catch the exception
//      if (ps)
//      {
//         TRACE0("CGXBrowserGrid::OnFlushRecord failed!\n");
//<nl>
//         // OnFlushCellValue did call SetWarningText(s);
//         // this warning text will then be displayed.
//         ps->Empty();
//      }
//      else
//         // let exception fall through
//         THROW_LAST();
//<nl>
//      // failed, ...
//      return FALSE;
//   }
//   END_CATCH
//<nl>
//   // flush changes to file
//   GetDocument()->m_dbfile.Flush();
//<nl>
//   SetModifiedFlag();
//<nl>
//   return TRUE;
//}
//<ecode><epre>
//@xref 
//<c CGXBrowserGrid>
//<mf CGXBrowserGrid::OnFlushCellValue> <mf CGXBrowserGrid::GetRecordFromRow> <mf CGXGridCore::SetWarningText> 
BOOL CGXBrowserGrid::OnFlushRecord(ROWCOL nRow, CString* ps /* = NULL */)
{
	CGXBrowseParam* pBrowseData = GetBrowseParam();
	ASSERT(pBrowseData);
	CGXStyle style;
	ROWCOL nCount = GetColCount();
	CGXStyle* pStyle = NULL;

	TRY
	{
		// Force writing dirty cells to CGXData
		for (ROWCOL nCol = 0; nCol <= nCount; nCol++)
		{
			short nField = GetFieldFromCol(nCol);
			if (nField >= 0 && pBrowseData &&
				pBrowseData->m_paDirtyFieldStruct[nField].bDirty)
			{
				if(pBrowseData->m_paDirtyFieldStruct[nField].pAttribute != NULL)
					OnFlushBlobValue(nRow, nCol, pBrowseData->m_paDirtyFieldStruct[nField].pAttribute);
				else
					OnFlushCellValue(nRow, nCol, pBrowseData->m_paDirtyFieldStruct[nField].sValue);
			}
			else // check column style
			{
				if (pStyle)
					pStyle->Free();
				else
					pStyle = CreateStyle();
				
				GetColStyle(nCol, *pStyle, gxCopy);
				
				if (pStyle->GetIncludeValue() && pBrowseData->m_nEditMode == addnew)
					OnFlushCellValue(nRow, nCol, pStyle->GetValueRef());
			}
		}
	}
	CATCH(CException, e)
	{
		if (pStyle)
			RecycleStyle(pStyle);

		// if ps is a valid CString we catch the exception
		if (ps)
		{
			TRACE0("CGXBrowserGrid::OnFlushRecord failed!\n");
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

	if (pStyle)
		RecycleStyle(pStyle);

	return TRUE;
}

// With normal fields the grid internal current row cache is represented as a string. With blobs this is
// not possible. We therefore have a user attribute pointer that can be used to store any meaningful data.
// This data is then sent to OnFlushBlobValue. If your browser variant supports storing blob data you will
// have to override this method and store the data in the data source. If this method is called for a particular
// row, col to store an object then OnFlushCellValue will not be called.

//@doc
//@mfunc
//@syntax virtual void OnFlushBlobValue(ROWCOL nRow, ROWCOL nCol, CGXAbstractBlob* pAttribute);
//@parm ROWCOL | nRow | The row being flushed
//@parm ROWCOL | nCol | The column being flushed
//@parm CGXAbstractBlob* | pAttribute | The blob attribute (Explained below)
//@rem
//With normal fields the grid internal current row cache is represented as a string 
//With blobs this is not possible. We therefore have a user attribute pointer that can 
//be used to store any meaningful data. This data is then sent to OnFlushBlobValue. <nl>
//<nl>
//If your browser variant supports storing blob data you will have to override this 
//method and store the data in the data source. If this method is called for a particular 
//row, col to store an object then OnFlushCellValue will not be called.<nl>
//<nl>
//If you cannot write the passed value to the data source, you may throw an exception 
//and specify the text to be displayed in the grid with SetWarningText (see the attached example). 
//The default implementation does not do anything.<nl>
//<nl>
//When overriding this method, it is strongly recommended that you dereference the record 
//and field index associated with a row or column by calling the GetRecordFromRow or 
//GetFieldFromCol methods.<nl>
//<nl>
//OnFlushBlobValue is not called when the user changes the current cell in 
//the current record (unlike StoreStyleRowCol). It is called when the user 
//wants to move to a new record and therefore validation in OnFlushBlobValue 
//happens only at record level.<nl>
//<nl>
//@xref <c CGXBrowserGrid> <mf CGXBrowserGrid::OnFlushCellValue> <mf CGXBrowserGrid::OnFlushRecord>
void CGXBrowserGrid::OnFlushBlobValue(ROWCOL nRow, ROWCOL nCol, CGXAbstractBlob* pAttribute)
{
	// TRACE0("If you are storing blobs you should override this method and store the blob\n")
	
	GX_UNUSED_ALWAYS(nRow);
	GX_UNUSED_ALWAYS(nCol);
	GX_UNUSED_ALWAYS(pAttribute);
}

void CGXBrowserGrid::GetOleViewerRowCol(ROWCOL nRow, ROWCOL nCol, DWORD dwId, CGXOleViewer*& pViewer ) const
{
	// default is to do nothing
	GX_UNUSED_ALWAYS(nRow);
	GX_UNUSED_ALWAYS(nCol);
	GX_UNUSED_ALWAYS(dwId);
	GX_UNUSED_ALWAYS(pViewer);
}


// OnFlushCellValue
//
// OnFlushCellValue is called from within CGXBrowserGrid::OnFlushRecord
// for all values changed in the current buffer.
//
// You should override this method to store changed values in your data source.
//
// If you cannot write the passed value to the data source,
// you may throw an exception and specify the text to be displayed
// in the grid with SetWarningText().
//
// Example:
//
// if (Invalid data)
// {
//    SetWarningText(_T("Error writing data to data source!"));
//    AfxThrowUserException();
//    return;
// }

//@doc
//@mfunc
//@syntax virtual void OnFlushCellValue(ROWCOL nRow, ROWCOL nCol, LPCTSTR pszChangedValue);throw( CException );
//@parm  ROWCOL | nRow | Specifies the row id.
//@parm  ROWCOL | nCol | Specifies the column id.
//@parm LPCTSTR | pszChangedValue | pointer to a string which contains the changed value for the cell. Pointer must not be NULL.
//@rem
//<mf CGXBrowserGrid::OnFlushCellValue> is called from within <mf CGXBrowserGrid::OnFlushRecord>
//for all values changed in the current buffer.<nl>
//<nl>
//You should override this method to store changed values in your data source. 
//If you cannot write the passed value to the data source, you may throw an exception 
//and specify the text to be displayed in the grid with <mf CGXBrowserGrid::SetWarningText> (see the attached example). 
//<nl>
//The default implementation writes data into the <c CGXData> object.<nl>
//<nl>
//When overriding this method, it is strongly recommended that you dereference 
//the record and field index associated with a row or column by calling the 
//<mf CGXBrowserGrid::GetRecordFromRow> or <mf CGXBrowserGrid::GetFieldFromCol> methods.<nl>
//<nl>
//<mf CGXBrowserGrid::OnFlushCellValue> is not called when the user changes the current cell 
//in the current record (unlike <mf CGXBrowserGrid::StoreStyleRowCol>). It is called when the user 
//wants to move to a new record and therefore validation in 
//<mf CGXBrowserGrid::OnFlushCellValue> happens only at record level.
//@ex
/*
This sample demonstrates how you can convert values into a data source-specific format 
(e.g., date values into a region-independent format), validate the cell contents, 
and throw an exception if data are invalid. |

void CDbfBrowserView::OnFlushCellValue(ROWCOL nRow, ROWCOL nCol, LPCTSTR pszChangedValue)
{
   // Unused:
   nRow;

   ASSERT(pszChangedValue != NULL);

   // Cell value
   CField* fld = GetField(nCol);

   // Date
   //

   if (fld->type == 'D' && *pszValue)
   {
      // Convert displayable text into plain date values
      // when record gets flushed. If date format is invalid,
      // an exception will be thrown.
      char szDbfDate[128];

      TIMESTAMP_STRUCT ts;
      if (GXParseDateTime(&ts, pszChangedValue, gxDEFAULT))
      {
         wsprintf(szDbfDate, _T("%04d%2d%2d"), ts.year, ts.month, ts.day);
         // Cell value
         GetDocument()->m_dbfile.SetValue(GetFieldFromCol(nCol), pszChangedValue);
      }
      else
      {
         // set warning text so that a message box is displayed
         // and throw an exception
         CString s;
         AfxFormatString1(s, GX_IDM_DATEINVALID, pszChangedValue);
         SetWarningText(s);
         AfxThrowNotSupportedException();
      }
   }
   else if (fld->type == 'N')
   {  
      TCHAR szFormat[10], szValue[128];
      wsprintf(szFormat, _T("%%%d.%df"), fld->len, fld->decimals);
                                       
      BOOL bIsDigit = FALSE;                                       
      for (LPCTSTR p = pszChangedValue; *p; p++)
      {            
         if (_istdigit(*p) || _istpunct(*p))
            bIsDigit = TRUE;
         else if (!_istspace(*p))
         {
            // set warning text so that a message box is displayed
            // and throw an exception
            CString s;
            AfxFormatString1(s, IDM_NUMBERINVALID, pszChangedValue);
            SetWarningText(s);
            AfxThrowNotSupportedException();
         }  
      }

      if (bIsDigit)
         _stprintf(szValue, szFormat, _gxttof(pszChangedValue));
      else
         _tcscpy(szValue, _T(""));
      GetDocument()->m_dbfile.SetValue(GetFieldFromCol(nCol), szValue);
   }
   else
   {
      TCHAR szFormat[10], szValue[128];
      wsprintf(szFormat, _T("%%-%ds"), fld->len);
      wsprintf(szValue, szFormat, pszChangedValue);
      GetDocument()->m_dbfile.SetValue(GetFieldFromCol(nCol), szValue);
   }
}
*/
//@xref 
//<c CGXBrowserGrid>
//<mf CGXBrowserGrid::OnFlushRecord> <mf CGXBrowserGrid::GetRecordFromRow> 
//<mf CGXBrowserGrid::GetFieldFromCol> <mf CGXGridCore::SetWarningText> <c CGXData> 
void CGXBrowserGrid::OnFlushCellValue(ROWCOL nRow, ROWCOL nCol, LPCTSTR pszChangedValue)
{
	CGXData* pData = GetParam()->GetData();
	ASSERT(pData);
	if(pData)
	{
		pData->StoreValueRowCol(nRow, nCol, pszChangedValue, gxOverride, 0, m_pStyleValue);
	}
}

// Overridables - Changing records

// Edit
//
// Changes the grid context into edit-mode
// Following changes (StoreStyleRowCol) in the
// edited row will be stored in the current record buffer.
// This buffer will be flushed the next time Update() is
// called.

//@doc
//@mfunc
//@syntax virtual void Edit(ROWCOL nRow);
//@parm  ROWCOL | nRow | Specifies the row id
//Call this member function to allow changes to the current record. 
//After you call <bold>Edit<ebold>, you can change the data of the current row by calling
//<mf CGXBrowserGrid::SetStyleRange>. The operation is 
//completed when you call the <mf CGXBrowserGrid::Update> member function to save your changes on the data source.<nl>
//<nl>
//<mf CGXBrowserGrid::Edit> empties the current record buffer and resets all modified-bits. 
//If you call Edit and make changes, these changes will be written to the 
//current record buffer and a modified-bit is set. 
//When calling <mf CGXBrowserGrid::Update>, all modified columns are written to the data source.
//<nl>
//When calling <bold>Edit<ebold>, the grid displays a pencil in the row-header of the 
//specified row indicating to the user that the row is changed.<nl>
//<nl>
//Please note that if you call <bold>Edit<ebold> again while there were pending changes, 
//all pending changes will be canceled. You may also cancel pending changes in 
//the record with <mf CGXBrowserGrid::UndoRecord>.
//@ex
//The following sample code shows you how you can programmatically change 
//a record to your data source. |
//
//   // Change the contents of nRow in the grid.
//   if (CanUpdate())
//   {
//      // Enter edit-mode
//     Edit(nRow);
//
//      // Lock updating the grid
//      BOOL bLock = LockUpdate(TRUE);
//
//     SetValueRange(CGXRange(nRow, 1), "1");
//      SetValueRange(CGXRange(nRow, 2), "2");
//
//      // Unlock painting
//      LockUpdate(bLock);
//
//      // Flush pending changes, Update will also redraw
//      // the row.
//      Update();
//   }
//
//@devnote
//Please note that this code depends only on <c CGXBrowserGrid>-functionality and 
//thus makes appending rows independent from your specific data source. 
//You can use the same code for appending a row to a DAO recordset, ODBC 
//recordset or any other external data source.
//@rem
//Prepares for changes to the current record. Call <mf CGXBrowserGrid::Update> to complete the edit.
//@xref <mf CGXBrowserGrid::Update> <mf CGXBrowserGrid::UndoRecord> 
void CGXBrowserGrid::Edit(ROWCOL nRow)
{
	CGXBrowseParam* pBrowseData = GetBrowseParam();
	ASSERT(pBrowseData);
	CancelRecord();
	OnTestGridDimension(nRow, 0);

	if (!IsCurrentCell(nRow, GX_INVALID))
	{
		ROWCOL nCol = GetHeaderCols()+1;
		if(!FindNextCell(GX_RIGHT, nRow, nCol))
		{
			TRACE0("CGXBrowserGrid::Edit failed to position current cell.\n");
			return;
		}
		SetCurrentCell(nRow, nCol);
	}

	// Check if we could succesfully position to the new
	// record.
	if (pBrowseData && pBrowseData->m_nCurrentRow != nRow)
	{
		TRACE0("CGXBrowserGrid::Edit failed to position current cell.\n");
		return;
	}
	if(pBrowseData)
	{
		pBrowseData->m_nCurrentRow = nRow;
		pBrowseData->m_nEditMode = edit;
	}

	RedrawRowCol(pBrowseData->m_nCurrentRow, 0, GX_INVALIDATE);
}

// AddNew
//
// Changes the grid context into append-mode
// Following changes (StoreStyleRowCol) in the
// last row will be stored in the current record buffer.
// This buffer will be flushed the next time Update() is
// called.
//
// AddNew also adds an additional row to the grid.
//
//@doc
//@mfunc
//@syntax virtual ROWCOL AddNew();
//throw( CNotSupportedException );
//@rdesc 
//Returns the row id of the new row.
//@rem
//Prepares the grid for adding a new record. The grid appends a new line in the grid. <bold>AddNew<ebold> changes 
//the grid context into append-mode. Subsequent changes with 
//<mf CGXBrowserGrid::StoreStyleRowCol> in the last row will be stored in the current record buffer. 
//This buffer will be flushed the next time <mf CGXBrowserGrid::Update> is called.<nl>
//<nl>
//If you want to add records programmatically, you should call <mf CGXBrowserGrid::AddNew> 
//before changing the cells 
//in appended row and call <mf CGXBrowserGrid::Update> to complete the addition. See also the example.<nl>
//<nl>
//You can cancel the append-mode with <mf CGXBrowserGrid::UndoRecord>.<nl>
//<nl>
//If CanAppend returns FALSE, a CNotSupportedException will be thrown.<nl>
//@ex
/*The following sample code shows you how you can programmatically append 
a record to your data source. Please note that this code 
depends only on <c CGXBrowserGrid>-functionality and thus makes appending 
rows independent from your specific data source. You can use the same code for 
appending a row to a DAO recordset, ODBC recordset or any other external data source. |

   // Append a row to the grid
   if (CanAppend())
   {
      // Add a row
      ROWCOL nAppendRow = AddNew();
      ASSERT(nAppendRow != GX_INVALID);

      // Lock updating the grid
      BOOL bLock = LockUpdate(TRUE);

      // Change cells in new row
      SetValueRange(CGXRange(nAppendRow, 1), "1");
      SetValueRange(CGXRange(nAppendRow, 2), "2");

      // Unlock painting
      LockUpdate(bLock);

      // Flush pending changes, Update will also redraw
      // the row.
      Update();
   }
*/
//@xref <c CGXBrowserGrid> <mf CGXBrowserGrid::Update>
//<mf CGXBrowserGrid::UndoRecord> <mf CGXBrowserGrid::CanAppend> 
ROWCOL CGXBrowserGrid::AddNew()
{
	CGXBrowseParam* pBrowseData = GetBrowseParam();
	ASSERT(pBrowseData);
	if (!CanAppend())
		AfxThrowNotSupportedException();

	// empty edit buffer, change edit mode
	CancelRecord();
	OnTestGridDimension(GX_MAXROWCOL, 0);
	ROWCOL nAppendRow = GetAppendRow();

	if (!IsCurrentCell(nAppendRow, GX_INVALID))
		SetCurrentCell(nAppendRow, GetHeaderCols()+1);

	// Check if we could succesfully position to the new
	// record.
	if (pBrowseData && pBrowseData->m_nCurrentRow != nAppendRow)
	{
		TRACE0("CGXBrowserGrid::AddNew failed to position current cell.\n");
		return GX_INVALID;
	}

	ASSERT(pBrowseData->m_nCurrentRow != GX_INVALID);
	pBrowseData->m_nEditMode = addnew;

	// if last row is not completely visible, scroll down one tow
	BOOL bLastRowVisible;
	ROWCOL nBottomRow = CalcBottomRowFromRect(GetGridRect(), bLastRowVisible);

	BOOL bScroll = (!bLastRowVisible && nBottomRow >= pBrowseData->m_nCurrentRow - 1);

	// avoid flickering because of possible scrollbar interactions
	LockScrollbars(TRUE);

	// update the screen with an appended row
	UpdateInsertRows(pBrowseData->m_nCurrentRow + 1, 1, GX_INVALIDATE, TRUE);
	RedrawRowCol(pBrowseData->m_nCurrentRow, 0, GX_UPDATENOW, TRUE);

	if (bScroll)
		OnScrollBecauseOfEdit(GX_DOWN, 1);

	// reenable scrollbars and update them
	LockScrollbars(FALSE);

	return nAppendRow;
}

// Update
//
// Flushes any changes in the current record buffer to
// the data source by calling OnFlushRecord.
//
// OnFlushRecord may rise exceptions depending whether
// the ps parameter is NULL or not. See the description
// of OnFlushRecord for furher details.

BOOL CGXBrowserGrid::Update(CString* ps)
{
	CGXBrowseParam* pBrowseData = GetBrowseParam();
	ASSERT(pBrowseData);
	if (pBrowseData->m_nEditMode != addnew && pBrowseData->m_nEditMode != edit)
	{
		TRACE0("Error: must enter Edit or AddNew mode before updating.\n");
		// m_pRecordset->ThrowDBException(AFX_SQL_ERROR_ILLEGAL_MODE);
		if (ps)
			*ps = _T("Error: must enter Edit or AddNew mode before updating.");
		return FALSE;
	}

	if (!TransferCurrentCell())
		return FALSE;

	ASSERT(pBrowseData->m_paDirtyFieldStruct);
	// ASSERTION-> No edit buffer allocated ->END

	// Has record been changed?
	if (IsRecordDirty())
	{
		if (!OnFlushRecord(pBrowseData->m_nCurrentRow, ps))
			return FALSE;

		EmptyEditBuffer();

		// trigger an event indicating that a new record has been added
		if (pBrowseData->m_nEditMode == addnew)
		{
			pBrowseData->m_nEditMode = noMode;
			// pBrowseData->m_nRecordLastSeen++;
			OnAddedNewRecord();
		}

		/*
		// empty undo and redo list
		if (GetParam()->IsEnableUndo())
		{
			GetParam()->EmptyUndoList();
			GetParam()->EmptyRedoList();
		}
		*/

		m_bUpdateDone = TRUE;
	}

	// Reset internal edit mode
	pBrowseData->m_nEditMode = noMode;

	// Redraw the whole record
	RedrawRowCol(CGXRange().SetRows(pBrowseData->m_nCurrentRow), GX_INVALIDATE);

	// succesfull update
	return TRUE;
}

// EmptyEditBuffer
//
// Reinitializes the current record buffer. Any pending
// changes will be lost.

void CGXBrowserGrid::EmptyEditBuffer()
{
	CGXBrowseParam* pBrowseData = GetBrowseParam();
	ASSERT(pBrowseData);
	int nDirtyFields = (pBrowseData->m_nFields > GetColCount()) ? pBrowseData->m_nFields : GetColCount();

	if (pBrowseData->m_paDirtyFieldStruct)
	{
		delete[] pBrowseData->m_paDirtyFieldStruct;
	}

	pBrowseData->m_paDirtyFieldStruct = new CGXBrowseDirtyFieldStruct[nDirtyFields+1];
}

// IsRecordDirty
//
// Returns TRUE if grid is in edit-mode and cells in the
// current row have been changed.
//@doc
//@mfunc
//@syntax BOOL IsRecordDirty();
//@rem
//Call this method to check if the modified-bit for any column in the current record buffer is set.<nl>
//<nl>
//When calling <mf CGXBrowserGrid::Update> all modified columns are written to the data source. 
//<mf CGXBrowserGrid::UndoRecord> will cancel any pending changes.
//@xref <c CGXBrowserGrid> <mf CGXBrowserGrid::Update> <mf CGXBrowserGrid::UndoRecord> 
BOOL CGXBrowserGrid::IsRecordDirty()
{
	CGXBrowseParam* pBrowseData = GetBrowseParam();
	ASSERT(pBrowseData);
	if (pBrowseData && pBrowseData->m_paDirtyFieldStruct == NULL || pBrowseData->m_nEditMode == noMode)
		return FALSE;

	BOOL bDirty = FALSE;

	int nDirtyFields = (pBrowseData->m_nFields > GetColCount()) ? pBrowseData->m_nFields : GetColCount();
	
	for (short nField = 0; nField < nDirtyFields; nField++)
		bDirty |= pBrowseData->m_paDirtyFieldStruct[nField].bDirty;

	return bDirty;
}

// OnAddedNewRecord
//
// OnAddedNewRecord is called after a record has been suceesfully appended
// to the recordset.

//@doc
//@mfunc
//@syntax virtual void OnAddedNewRecord()
//@rem
//Called from <mf CGXBrowserGrid::Update> when a new record has been added to the datasource.<nl>
//<nl>
//The default implementation does not perform any functionality.<nl>
//<nl>
//Some specific data sources need to do a Requery, as for example ODBC record sets.
//This can sometimes be very slow, and you may consider overriding this method 
//for ODBC data sources and fine-tune it to the specific need of the ODBC driver.
//@devnote
//Do not call SetCurrentCell from within OnAddedNewRecord.
//Update and is called from SetCurrentCell. (See the call stack in OnAddedNewRecord). 
//Therefore any calls to SetCurrentCell have no effect because after OnAddedNewRecord returns 
//the callling SetCurrentCell method will continue its job and reposition the current cell.<nl>
//<nl>
//To work around this behavior override SetCurrentCell as follows:<nl>
//<nl>
//<pre><code>
// reset  bool attribute
//m_bAddedANewRecord = FALSE;
//<nl>
// //call base class version (maybe also call LockUpdate(TRUE))
//grid::SetCurrentCell
//<nl>
// //check bool attribute
//if (m_bAddedANewRecord )
//   SetCurrentCelL....
//<nl>
// //reset attribute
//m_bAddedANewRecord = FALSE;
//<ecode><epre>
//in your OnAddedNewRecord method set the m_bAddedNewRecord attribute (and don't call SetCurrentCell)
//<pre><code>
// m_bAddedNewRecord = TRUE
//<ecode><epre>
//@xref <c CGXBrowserGrid> <mf CGXBrowserGrid::Update> 
void CGXBrowserGrid::OnAddedNewRecord()
{
	FreeObjectCache();
}

// UndoRecord
//
// Cancels any pending changes in the current record and
// resets the edit- or append-mode and empties the undo/redo-list

void CGXBrowserGrid::UndoRecord()
{
	CancelRecord();

	// empty undo and redo list
	if (GetParam()->IsEnableUndo())
	{
		if (GetParam()->GetUndoList().GetCount() > 1)
			GetParam()->EmptyRedoList();
		GetParam()->EmptyUndoList();
	}
}

// CancelRecord
//
// Cancels any pending changes in the current record and
// resets the edit- or append-mode
//@doc
//@mfunc
//@syntax virtual void CancelRecord();
//@rem
//This method is called to cancel any pending changes in the current record and resets 
//the edit- or append-mode. If an <mf CGXBrowserGrid::AddNew> was pending, the last row is removed from the grid.<nl>
//<nl>
//Note on undo/redo support: <mf CGXBrowserGrid::CancelRecord> will not remove commands from the undo list. 
//As this could possibly confuse the customer, you should consider calling <<mf CGXBrowserGrid::UndoRecord> instead.
//@xref <c CGXBrowserGrid> <mf UndoRecord>
void CGXBrowserGrid::CancelRecord()
{
	CGXBrowseParam* pBrowseData = GetBrowseParam();
	ASSERT(pBrowseData);
	if(pBrowseData && pBrowseData->m_nEditMode == addnew)
	{
		ROWCOL nNewRow = pBrowseData->m_nCurrentRow;

		pBrowseData->m_nEditMode = noMode;
		EmptyEditBuffer();

		// Turn off updating for smoother drawing when grid
		// needs to be scrolled.
		BOOL bLockUpdate = FALSE;
		BOOL bLock = (GetTopRow() > GetHeaderRows()+1);

		if (bLock)
			bLockUpdate = LockUpdate(TRUE);

		LockScrollbars(TRUE);
		UpdateRemoveRows(nNewRow + 1, nNewRow + 1,  NULL, GX_UPDATENOW, TRUE);
		TransferCurrentCell(FALSE, GX_UPDATENOW, FALSE);
		RedrawRowCol(CGXRange().SetRows(nNewRow));
		LockScrollbars(FALSE);

		if (bLock)
		{
			// Redraw whole screen and update scrollbars all at once
			LockUpdate(bLockUpdate);
			Redraw();
		}
		else
			// refresh formula cells 
			RefreshViews();

	}
	else if (pBrowseData->m_nEditMode == edit)
	{
		ROWCOL nEditRow = pBrowseData->m_nCurrentRow;

		pBrowseData->m_nEditMode = noMode;
		EmptyEditBuffer();
		TransferCurrentCell(FALSE, GX_UPDATENOW, FALSE);
		RedrawRowCol(CGXRange().SetRows(nEditRow), GX_INVALIDATE);
	}
	else
		EmptyEditBuffer();
}

/////////////////////////////////////////////////////////////////////////////
// CGXGridCore overridables

void CGXBrowserGrid::OnGridDraw(CDC* pDC)
{
	// Caching
	OnFillCache();

	CGXGridCore::OnGridDraw(pDC);
}

BOOL CGXBrowserGrid::GetStyleRowCol(ROWCOL nRow, ROWCOL nCol, CGXStyle& style, GXModifyType mt, int nType)
{
	CGXBrowseParam* pBrowseData = GetBrowseParam();
	ASSERT(pBrowseData);
	ASSERT(nRow + GetHeaderRows() <= LONG_MAX);

	// load style from the CGXData object, if something specific is stored there
	// (this call will normally only have effect for column headers and column styles).

	CGXData* pData = GetParam()->GetData();
	ASSERT(pData);
	BOOL bSuccess = nRow <= pData->GetRowCount()
			&& nCol <= pData->GetColCount()
			&& pData->GetStyleRowCol(nRow, nCol, style, mt, nType);

	// no further processing for the following conditions

	if (mt == gxRemove
		|| nType == -1)
		return bSuccess;

	// changed value in record buffer if field is dirty
	LPCTSTR pszChangedValue = NULL;

	if (nRow > GetHeaderRows() && nCol > GetHeaderCols())
	{
		// Is this the currently buffered edit record
		// and has the specific field been changed?
		short nField = GetFieldFromCol(nCol);

		if (pBrowseData->m_nEditMode != noMode
				&& pBrowseData->m_nCurrentRow == nRow
				&& pBrowseData->m_paDirtyFieldStruct
				&& pBrowseData->m_paDirtyFieldStruct[nField].bDirty)
		{
			pszChangedValue = pBrowseData->m_paDirtyFieldStruct[nField].pAttribute?
				_T("Binary"):pBrowseData->m_paDirtyFieldStruct[nField].sValue;
		}

		// look in CGXData object
		pData->GetStyleRowCol(nRow, nCol, style, gxOverride, 0);

		// initialize value with changed value from current record buffer
		if (pszChangedValue != NULL)
			style.SetValue(pszChangedValue);

		//
		// All other style settings will be loaded from base styles, which
		// has for example in CGXDaoGrid::OpenRecordset been applied to
		// the column nCol in the OpenRecordset() method. (see CGXDaoGrid)

		// If you want to change the appearance of specific cells,
		// you have several options:
		// 1) You change the base style for the specific type of cell, e.g.
		//    use a spin edit control for dbByte values.
		// 2) You override GetStyleRowCol() and pass your specific cell attributes
		//    to the style object.
		// 3) You call SetStyleRange(CGXRange().SetCols(nCol), yourstyle) and change
		//    the column style settings for the specific column
		//
		// Note: You can determine the zero-based field index from a given
		// column by calling GetFieldFromCol(nCol) !
		//

		bSuccess = TRUE;
	}

	// give the programmer the chance to load value from data source
	// or apply additional formattings at runtime

	bSuccess |= OnLoadCellStyle(nRow, nCol, style, pszChangedValue);

	return bSuccess;
}

BOOL CGXBrowserGrid::StoreStyleRowCol(ROWCOL nRow, ROWCOL nCol, const CGXStyle* pStyle, GXModifyType mt, int nType)
{
	CGXBrowseParam* pBrowseData = GetBrowseParam();
	ASSERT(pBrowseData);
	BOOL bValue = pStyle && pStyle->GetIncludeValue()  // (change value)
		|| pStyle && mt == gxCopy; // (empty or copy value)

	if (nType != -1         // no row/column base style
		&& mt != gxRemove   // no clear command
		&& bValue    // value must be included
		&& pBrowseData->m_nEditMode != noMode   // grid is in edit mode
		&& pBrowseData->m_nCurrentRow == nRow   // this row is in edit mode
		&& nCol > GetHeaderCols()
		)
	{
		// If all the previous conditions are TRUE,
		// store the value into the current record buffer.

		ASSERT(pBrowseData->m_paDirtyFieldStruct);

		int nField = GetFieldFromCol(nCol);

		if(SetBinaryFlags(pStyle, nField))
			return TRUE;

		if (pStyle->GetIncludeValue())
			pBrowseData->m_paDirtyFieldStruct[nField].sValue = pStyle->GetValueRef();
		else
			pBrowseData->m_paDirtyFieldStruct[nField].sValue = _T("");
		pBrowseData->m_paDirtyFieldStruct[nField].bDirty = TRUE;

		return TRUE;
	}

	else // store it in CGXData
	{
		BOOL bIsGridCell =
			(nRow >= GetFirstRow() && nCol > GetHeaderCols());

		// Sometimes it makes no sense to store grid cells into
		// CGXData, for example CGXDaoGrid and CGXODBCGrid should
		// load cell data from or store them in the data source.

		if (!pBrowseData->m_bCanStoreGridCellInCGXData && bIsGridCell)
		{
			TRACE0("Warning: Trying to store a grid cell directly into CGXData\n");
			TRACE0("You should call Edit() / AddNew() before you try to change\n");
			TRACE0("data for a new row\n");

			TRACE0("Could it be that you have called SetStyleRange for a range\n");
			TRACE0("of several rows? SetStyleRange must not span over several rows\n");
			TRACE0("Or did you enable copy and paste or drag and drop with the\n");
			TRACE0("GX_DNDSTYLES flag? Only GX_DNDTEXT is possible with browser grids.\n");

			ASSERT(0);

			return FALSE;
		}

		CGXData* pData = GetParam()->GetData();

		return pData->StoreStyleRowCol(nRow, nCol, pStyle, mt, nType);
	}
}

void CGXBrowserGrid::OnModifyCell(ROWCOL nRow, ROWCOL nCol)
{
	CGXBrowseParam* pBrowseData = GetBrowseParam();
	ASSERT(pBrowseData);
	ASSERT(pBrowseData->m_nEditMode == noMode || pBrowseData->m_nCurrentRow == nRow);

	if (m_bDropDownCell)
		return;

	if (pBrowseData->m_nEditMode == noMode)
	{
		if (nRow == GetAppendRow())
			AddNew();
		else
			Edit(nRow);
	}

	// if AddNew or Edit was succesfull
	if (pBrowseData->m_nEditMode != noMode)
		CGXGridCore::OnModifyCell(nRow, nCol);
}

BOOL CGXBrowserGrid::CanSelectCurrentCell(BOOL bSelect, ROWCOL dwSelectRow, ROWCOL dwSelectCol, ROWCOL dwOldRow, ROWCOL dwOldCol)
{
	CGXBrowseParam* pBrowseData = GetBrowseParam();
	ASSERT(pBrowseData);
	if (!CGXGridCore::CanSelectCurrentCell(bSelect, dwSelectRow, dwSelectCol, dwOldRow, dwOldCol))
		return FALSE;

	pBrowseData->m_bUpdateOnStore = FALSE;

	ROWCOL nCurRow, nCurCol;

	// If current row has been changed and current cell is positioned to a new row
	if (!bSelect && pBrowseData->m_nEditMode != noMode && dwSelectRow && dwSelectRow != dwOldRow)
	{
		m_bUpdateDone = FALSE;

		// ... and if current cell is active
		if (GetCurrentCell(nCurRow, nCurCol) && GetControl(nCurRow, nCurCol)->GetModify())
			// set a flag which tells StoreStyleRowCol to update the cursor
			pBrowseData->m_bUpdateOnStore = TRUE;
		else
		{
			CString s;
			if (!Update(&s))
			{
				if (!s.IsEmpty())
					SetWarningText(s);
				return FALSE;
			}
		}
	}

	return TRUE;
}

BOOL CGXBrowserGrid::ProcessKeys(CWnd* pSender, UINT nMessage, UINT nChar, UINT nRepCnt, UINT flags)
{
	// Is the grid in a special mode (tracking, dragging, selecting)?
	if (GetCapture() == m_pGridWnd)
	{
		// ... give user a chance to abort this mode
		if (nChar == VK_ESCAPE)
			m_pGridWnd->SendMessage(WM_CANCELMODE, 0, 0);

		// otherwise, keys cannot be processed

		return TRUE;
	}

	BOOL bRetVal = TRUE;

	if (nMessage == WM_KEYDOWN && nChar == VK_ESCAPE)
	{
		Undo();
	}

	else if (pSender == GridWnd() && nMessage == WM_KEYDOWN && nChar == VK_DELETE
		&& GetParam()->GetRangeList()->IsAnyCellFromCol(0))

		DeleteRecords();

	else if (nMessage == WM_KEYDOWN)
	{
		bRetVal = FALSE;

		BOOL bAlt = GetKeyState(VK_MENU) & 0x8000;
		BOOL bCtl = GetKeyState(VK_CONTROL) & 0x8000;
		BOOL bShift = GetKeyState(VK_SHIFT) & 0x8000;
		WORD nAction = GetParam()->GetEnterKeyAction();

		switch (nChar)
		{
		case VK_RETURN:     // Enter
			if (nAction != GX_RIGHT)
			{
				if (!bAlt && !bCtl && !bShift && nAction != 0)
				{
					TransferCurrentCell(TRUE, GX_INVALIDATE);
					MoveCurrentCellEx(nAction, 1);
					bRetVal = TRUE;
				}
				else
					bRetVal = FALSE;
				break;
			}

			// FALL THROUGH if GX_RIGHT

		case VK_TAB:        // Tab-Key
			{
				ROWCOL nRow = 1, nCol = 1;
				GetCurrentCell(nRow, nCol);
				if (nChar == VK_RETURN || !bShift)

				{
					// Determine last column (and take care on hidden columns)
					ROWCOL ncRow = nRow, ncCol = nCol+1;
					if (!FindNextCell(GX_RIGHT, ncRow, ncCol))
						ncCol = nCol;

					// Jump to the right cell or move down a row,
					// if cell positioned at last cell
					if (nCol < ncCol)
						MoveCurrentCell(GX_RIGHT);
					else if (nRow < GetRowCount())
					{
						if (MoveCurrentCell(GX_MOSTLEFT))
							MoveCurrentCell(GX_DOWN);
					}
					else
					{
						MoveCurrentCell(GX_TOPLEFT);
					}
				}
				else
				{
					// Jump to the left cell or move up a row

					// Determine first column (and take care on hidden columns)
					ROWCOL ncRow = nRow, ncCol = max(nCol, 1)-1;
					if (!FindNextCell(GX_LEFT, ncRow, ncCol))
					{
						ncCol = nCol;
						ncRow = max(nRow, 1)-1;
						if (!FindNextCell(GX_UP, ncRow, ncCol))
							ncRow = nRow;
					}

					if (nCol > ncCol)
						MoveCurrentCell(GX_LEFT);
					else if (nRow > ncRow)
					{
						if (MoveCurrentCell(GX_MOSTRIGHT))
							MoveCurrentCell(GX_UP);
					}
					else
					{
						MoveCurrentCell(GX_BOTTOMRIGHT);
					}
				}
				bRetVal = TRUE;
			}
		}
	}
	else
		bRetVal = FALSE;

	if (!bRetVal)
		bRetVal = CGXGridCore::ProcessKeys(pSender, nMessage, nChar, nRepCnt, flags);

	return bRetVal;
}

BOOL CGXBrowserGrid::OnGridKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// Unused:
	nFlags, nRepCnt;

	//BOOL bCtl = GetKeyState(VK_CONTROL) & 0x8000;//Unused
	BOOL bShift = GetKeyState(VK_SHIFT) & 0x8000;
	//BOOL bAlt = GetKeyState(VK_MENU) & 0x8000;//Unused
	//BOOL bRet = FALSE;//Unused

	BOOL bProcessed = FALSE /*, bSpeedKey = FALSE*/;

	// TRACE1("WM_KEYDOWN: nChar %03d\n", nChar);
	switch (nChar)
	{
	case VK_DELETE:
		if (bShift)
		{
			if (CanCut())
				Cut();
			bProcessed = TRUE;
		}
		else
		{
			ROWCOL nRow, nCol;
			if (GetCurrentCell(nRow, nCol) && !IsActiveCurrentCell() && CanClear() && GetCurrentCellControl()->OnDeleteCell())
				Clear(FALSE);
			bProcessed = TRUE;

			if(bProcessed)
               	{
                    		SetCurrentCell(-1,-1); //trick - changed value got saved
                    		CRowColArray awCols;

				int count = GetSelectedCols(awCols);
				for(int n = 0; n < count; n++)
       		             RedrawRowCol(CGXRange().SetCols(awCols[n]));
	               }
		}
		break;
	}

	if (bProcessed)
		UpdateWindow();


	if (!bProcessed)
		return CGXGridCore::OnGridKeyDown(nChar, nRepCnt, nFlags);
	else 
		return TRUE;
}


BOOL CGXBrowserGrid::Undo()
{
	CGXBrowseParam* pBrowseData = GetBrowseParam();
	ASSERT(pBrowseData);
	// If the current cell has been modified and changes have not
	// been stored, Undo() simply cancels the changes.  No redo is possible

	if(pBrowseData->m_nEditMode == addnew 
			&& GetParam()->GetUndoList().IsEmpty() 
		|| GetParam()->IsEnableUndo() == FALSE
			&& pBrowseData->m_nEditMode != noMode)
	{
		CancelRecord();
		return TRUE;
	}

	return CGXGridCore::Undo();
}

BOOL CGXBrowserGrid::SetStyleRange(const CGXRange& range, const CGXStyle* pStyle, GXModifyType mt, int nType, const CObArray* pCellsArray, UINT flags, GXCmdType ctCmd)
{
	CGXBrowseParam* pBrowseData = GetBrowseParam();
	ASSERT(pBrowseData);
	// determine if a cell in the grid shall be changed
	// assign FALSE if it is a row/column style, a header or several rows
	BOOL bIsGridCell =
		range.IsCells()
		&& range.GetHeight() == 1
		&& range.top >= GetFirstRow()
		&& range.left > GetHeaderCols();

	// let the base class version do the work if not a cell in the grid
	if (!bIsGridCell)
		return CGXGridCore::SetStyleRange(range, pStyle, mt, nType, pCellsArray, flags, ctCmd);

	// make sure current row is in edit mode

	ROWCOL nRow = range.top;

	CString sErrorDesc;

	// check if there are pending changes in another record
	if (pBrowseData->m_nEditMode != noMode && nRow != pBrowseData->m_nCurrentRow)
	{
		// flush them to the data source
		if (!Update(&sErrorDesc))
			return FALSE;   // could not update previous record
	}

	BOOL bAddNew = FALSE;

	// ensure that the current row is in edit mode
	if (pBrowseData->m_nEditMode == noMode)
	{
		bAddNew = !MoveTo(nRow);

		if (bAddNew)
			AddNew();
		else
			Edit(nRow);
	}

	BOOL bSuccess = FALSE;

	// if AddNew or Edit was succesfull
	if (pBrowseData->m_nEditMode != noMode)
		bSuccess = CGXGridCore::SetStyleRange(range, pStyle, mt, nType, pCellsArray, flags, ctCmd);

	// Shall I check for dirty fields?
	BOOL bCheckDirtyBits = (ctCmd == gxUndo) || !bSuccess && pBrowseData->m_nEditMode != noMode;

	if (bCheckDirtyBits)
	{
		// remove unnecceary dirty bits from current record
		ASSERT(pBrowseData->m_paDirtyFieldStruct);

		CGXStyle* pStyle = CreateStyle();
		ROWCOL nRow = range.top;
		for (ROWCOL nCol = range.left; nCol <= range.right; nCol++)
		{
			short nField = GetFieldFromCol(nCol);

			// compare value
				// force GetStyleRowCol to look in data source (e.g. CDaoRecordset)
				// for the value
			pBrowseData->m_paDirtyFieldStruct[nField].bDirty = FALSE;

			pStyle->SetIncludeValue(FALSE);
			GetStyleRowCol(nRow, nCol, *pStyle);

				// set or reset dirty bit
			if (!SetBinaryFlags(pStyle, nField))
				pBrowseData->m_paDirtyFieldStruct[nField].bDirty = pStyle->GetIncludeValue()
				&& _tcscmp(pStyle->GetValueRef(), pBrowseData->m_paDirtyFieldStruct[nField].sValue) != 0;
		
			

		}
		RecycleStyle(pStyle);

		// Can I reset the edit mode for the record?
		if (!IsRecordDirty())
			CancelRecord();
	}

	if (bSuccess && bAddNew)
	{
		// ensure that current cell displays correct value
		// when redoing an previously abondened record
		ROWCOL nRow, nCol;
		CGXControl* pControl;
		if (GetCurrentCell(nRow, nCol))
		{
			CString s;
			pControl = GetControl(nRow, nCol);
			pControl->GetCurrentText(s);
			if (s.IsEmpty())
				TransferCurrentCell(FALSE, FALSE);
		}
	}

	// Was SetStyleRange called from OnReplaceAll and therefore
	// I have to update the current record immediately?

	if (bSuccess && pBrowseData->m_bDoReplaceAll)
	{
		ASSERT(ctCmd == gxDo);

		// try to write the current row back to data source
		Update(NULL);
			// Update possible throws an exception
			// which will be catched in OnReplaceAll()
	}

	// Was SetStyleRange called because user wants to move current cell
	// to a new record and therefore I have to update the current record?

	else if (bSuccess && pBrowseData->m_bUpdateOnStore || ( OnGetRecordCount()==1 && CanAppend() == FALSE ) )
	{
		ASSERT(ctCmd == gxDo);
		ASSERT(range.IsCells() && range.GetHeight() == 1 && range.GetWidth() == 1);

		ROWCOL nRow = range.top;
		ROWCOL nCol = range.left;
		short nField = GetFieldFromCol(nCol);

		pBrowseData->m_bUpdateOnStore = FALSE;

		// try to write the current row back to data source
		CString s;

		if (!Update(&s))  // Update() will catch possible exceptions and
						 // store the description info in s. If an
						 // exception occurs Update() returns FALSE.
		{
			GridWnd()->SendMessage(WM_CANCELMODE, 0, 0);

			CGXControl* pControl = GetControl(nRow, nCol);
			pControl->SetCurrentText(pBrowseData->m_paDirtyFieldStruct[nField].sValue);

			// Reset dirty flag for current column
			pBrowseData->m_paDirtyFieldStruct[nField].sValue.Empty();
			pBrowseData->m_paDirtyFieldStruct[nField].bDirty = FALSE;

			// Remove the command from undo list
			CObList& undoList = GetParam()->GetUndoList();
			if (GetParam()->IsEnableUndo() && undoList.GetCount() > 0)
				RemoveCommand(ctCmd);

			// Message box text (will be displayed later)
			if (!s.IsEmpty())
				SetWarningText(s);

			// failed, ...
			return FALSE;
		}
	}

	return bSuccess;
}


BOOL CGXBrowserGrid::SetBinaryFlags(const CGXStyle* pStyle, int nField)
{
	// default implementation does not do anything
	return FALSE;
	
	GX_UNUSED_ALWAYS(pStyle);
	GX_UNUSED_ALWAYS(nField);
}

void CGXBrowserGrid::OnCanceledEditing(ROWCOL nRow, ROWCOL nCol)
{
	// Can I reset the edit mode for the record?
	if (!IsRecordDirty())
		CancelRecord();

	// unused:
	nRow, nCol;
}

void CGXBrowserGrid::OnMovedCurrentCell(ROWCOL nRow, ROWCOL nCol)
{
	CGXBrowseParam* pBrowseData = GetBrowseParam();
	ASSERT(pBrowseData);
	if (nRow != pBrowseData->m_nCurrentRow)
	{
		// Redraw the header if MarkRowHeader is turned off, which would 
		// otherwise force a redraw on the row header
		if(!GetBrowseParam()->GetProperties()->GetMarkRowHeader())
			RedrawRowCol(pBrowseData->m_nCurrentRow, 0, GX_INVALIDATE);

		if (pBrowseData->m_nEditMode != noMode)
			Update();

		ASSERT(pBrowseData->m_nEditMode == noMode);

		pBrowseData->m_nCurrentRow = nRow;
		
		// Redraw the header if MarkRowHeader is turned off
		if(!GetBrowseParam()->GetProperties()->GetMarkRowHeader())
			RedrawRowCol(pBrowseData->m_nCurrentRow, 0, GX_INVALIDATE);
	}

	CGXGridCore::OnMovedCurrentCell(nRow, nCol);
}

// OnLeftCell
//
// OnLeftCell is called after the old current cell has been deactivated.
// So, at the time this event is called, there is no current cell in
// the grid.
//

BOOL CGXBrowserGrid::OnLeftCell(ROWCOL /*nRow*/, ROWCOL /*nCol*/, ROWCOL nNewRow, ROWCOL /*nNewCol*/)
{
	CGXBrowseParam* pBrowseData = GetBrowseParam();
	ASSERT(pBrowseData);

	if (m_bUpdateDone && nNewRow != pBrowseData->m_nCurrentRow)
	{
		RedrawRowCol(CGXRange().SetRows(pBrowseData->m_nCurrentRow));
			// no further redrawing of current cell necessary

		m_bUpdateDone = FALSE;

		return FALSE;
	}

	return TRUE;    // SetCurrentCell will redraw current cell
}

//
// Cut and Paste
//
// CGXBrowserGrid provides its own Cut() and Paste()
// routines as their functionality is limited.
//
//

// Cut()
// Cut() differs from the original CGXGridCore implementation
// the way that it only works cuts text form the current cell
// and not on selected ranges of cells
//

BOOL CGXBrowserGrid::CanCut()
{
	if (!CanUpdate())
		return FALSE;

	// make sure that there is no range selected
	if (GetParam() && GetParam()->GetRangeList()->GetCount() > 0)
	{
		if(GetParam()->GetRangeList()->GetCount() == 1 && GetParam()->GetExcelLikeCurrentCell())
		{
			//check if range is a single cell
			CGXRange* pRange = (CGXRange*)GetParam()->GetRangeList()->GetTail();
			if(pRange && !((pRange->GetWidth() == 1)&&(pRange->GetHeight() == 1)))
			{
				//more than one cell in range so disable
				return FALSE;
			}
		}
		else //More than one range so disable paste
			return FALSE;
	}

	// check current cell
	ROWCOL nRow, nCol;
	if (!GetCurrentCell(nRow, nCol))
		return FALSE;

	// process current cell
	CGXControl* pControl = GetControl(nRow, nCol);
	
	if(pControl)
		return pControl->CanCut();
	else
		return IsCurrentCell();
}

BOOL CGXBrowserGrid::Cut()
{
	if (!CanCut())
		return FALSE;

	// check current cell
	ROWCOL nRow, nCol;
	if (!GetCurrentCell(nRow, nCol))
		return FALSE;

	// process current cell
	CGXControl* pControl = GetControl(nRow, nCol);
	
	if(pControl)
		return pControl->Cut();
	/*
	CString s;
	pControl->GetSelectedText(s);

	// copy string to clipboard (CF_TEXT format)

	CSharedFile clipb (GMEM_MOVEABLE|GMEM_DDESHARE|GMEM_ZEROINIT);

	clipb.Write(s, _tcslen(s) * sizeof(TCHAR));
	clipb.Write(_T("\0"), sizeof(TCHAR));
	HGLOBAL hData = clipb.Detach();

	if (hData)
	{
		if (!GridWnd()->OpenClipboard())
			return FALSE;

		if (!EmptyClipboard())
		{
			TRACE0("Failed to empty clipboard in CGXDaoGrid::Cut()\n");
			VERIFY(CloseClipboard());
			return FALSE;
		}

#ifdef _UNICODE
		SetClipboardData(CF_UNICODETEXT, hData);
#else
		SetClipboardData(CF_TEXT, hData);
#endif
		VERIFY(CloseClipboard());

		if (pControl->IsActive())
			// replace selected text
			pControl->ReplaceSel(_T(""));
		else
			// ... or entire content of current cell
			SetControlTextRowCol(nRow, nCol, _T(""), GX_UPDATENOW);

		return TRUE;
	}
	*/
	return TRUE;
}

//
// Paste()
// Paste() differs from the original CGXGridCore implementation
// the way that it only works pastes text into the current cell
// and not on selected ranges of cells
//

BOOL CGXBrowserGrid::Paste()
{
	if (!CanUpdate() || IsReadOnly())
		return FALSE;

	CGXBrowseParam* pBrowseData = GetBrowseParam();
	ASSERT(pBrowseData);
	if(pBrowseData && pBrowseData->m_bAllowPasteMultiCells)
	{
		// make sure that there is no range selected
		if (GetParam() && GetParam()->GetRangeList()->GetCount() > 0)
			return FALSE;

		// check current cell
		ROWCOL nRow, nCol;
		if (!GetCurrentCell(nRow, nCol))
			return FALSE;

		// do not use GX_DNDSTYLES
		m_nClipboardFlags = m_nClipboardFlags & ~GX_DNDSTYLES; 

		BOOL bSuccess = CGXGridCore::Paste();

		if (pBrowseData->m_nEditMode == noMode)
			Update();

		SetCurrentCell(nRow, nCol);

		// SRSTUDIO-392 - Need to call redraw.
		Redraw();

		return bSuccess; 
	}else // Not allowing pasting of multiple cells.
	{
		// make sure that there is no range selected
		if (GetParam() && GetParam()->GetRangeList()->GetCount() > 0)
		{
			if(GetParam()->GetRangeList()->GetCount() == 1 && GetParam()->GetExcelLikeCurrentCell())
			{
				//check if range is a single cell
				CGXRange* pRange = (CGXRange*)GetParam()->GetRangeList()->GetTail();
				if(pRange && !((pRange->GetWidth() == 1) && (pRange->GetHeight() == 1)))
				{
					//more than one cell in range so disable
					return FALSE;
				}
			}else //More than one range so disable paste
			{
				return FALSE;
			}
		}

		// check current cell
		ROWCOL nRow, nCol;
		if (!GetCurrentCell(nRow, nCol))
			return FALSE;

		const CGXStyle& style = LookupStyleRowCol(nRow, nCol);
		if (style.GetIncludeReadOnly() && style.GetReadOnly())
			return FALSE;

		CGXControl* pControl = GetRegisteredControl(style.GetControl());
		ASSERT(pControl);
		if(!pControl)
		{
			return FALSE;
		}

		// pControl->Paste might return FALSE if control is not active.
		if(pControl && pControl->Paste())
		{
			// SRSTUDIO-392 - Need to call redraw.
			Redraw();

			return TRUE;		// Paste taken care of by the control
		}else
		{
			// Take care of controls that are not active.
			if (!GridWnd()->OpenClipboard())
			{
				TRACE0("Failed to open Clipboard in CGXBrowserGrid::Paste()\n");
				return FALSE;
			}

			HGLOBAL handle = 0;
			#ifdef _UNICODE
				handle = GetClipboardData(CF_UNICODETEXT);
			#else
				handle = GetClipboardData(CF_TEXT);
			#endif

			LPTSTR psz = NULL;

			if (handle && (psz = (LPTSTR) GlobalLock(handle)) != NULL)
			{
				// replace selected text
				// ReplaceSel also ensures that text is not too long.
				pControl->ReplaceSel(psz);

				if (!pControl->IsActive())
					pControl->SetActive(TRUE);

				// redraw the cell with new text
				pControl->Refresh();

				GlobalUnlock(handle);
			}

			CloseClipboard();

			return TRUE;
		}
	}
}

BOOL CGXBrowserGrid::CanPaste()
{
	if (!CanUpdate() || IsReadOnly())
		return FALSE;

	CGXBrowseParam* pBrowseData = GetBrowseParam();
	if (pBrowseData->m_bAllowPasteMultiCells)
	{
		// don't call CGXBrowserGrid
		return CGXGridCore::CanPaste(); 
	}else
	{
		// make sure that there is no range selected
		if (GetParam() && GetParam()->GetRangeList()->GetCount() > 0)
		{
			if(GetParam()->GetRangeList()->GetCount() == 1 && GetParam()->GetExcelLikeCurrentCell())
			{
				//check if range is a single cell
				CGXRange* pRange = (CGXRange*)GetParam()->GetRangeList()->GetTail();
				if(!((pRange->GetWidth() == 1)&&(pRange->GetHeight() == 1)))
				{
					//more than one cell in range so disable
					return FALSE;
				}
			}else //More than one range so disable paste
			{
				return FALSE;
			}
		}
		
		CGXControl* pControl = GetCurrentCellControl();
		
		if (pControl && pControl->CanPaste())
		{
			return TRUE;
		}else
		{
			#ifdef _UNICODE
			return IsClipboardFormatAvailable(CF_UNICODETEXT);
			#else
			return IsClipboardFormatAvailable(CF_TEXT);
			#endif
		}
	}
}

void CGXBrowserGrid::OnReplaceSel(LPCTSTR lpszFind, BOOL bNext, BOOL bCase,
		LPCTSTR lpszReplace)
{
	CGXBrowseParam* pBrowseData = GetBrowseParam();

	if (!CanUpdate())
		return;

	// Force updating row after change
	if(pBrowseData)
	{
		pBrowseData->m_bUpdateOnStore = TRUE;
	}
	
	// SetStyleRange will later check and reset this flag

	CGXGridCore::OnReplaceSel(lpszFind, bNext, bCase, lpszReplace);
}

void CGXBrowserGrid::OnReplaceAll(LPCTSTR lpszFind, LPCTSTR lpszReplace,
		BOOL bCase)
{
	CGXBrowseParam* pBrowseData = GetBrowseParam();

	if (!CanUpdate())
		return;

	if (GetRowCount() == 0 || GetColCount() == 0)
		return;

	// active cell coordinates
	ROWCOL nRow, nCol;
	if (!GetCurrentCell(&nRow, &nCol))
		return;

	ROWCOL nEditRow = nRow, nEditCol = nCol;
	// Disable undo creation
	BOOL bEnableUndo = GetParam()->IsEnableUndo();

	if(pBrowseData)
	{
		pBrowseData->m_bDoReplaceAll = TRUE;
	}
	
	// StoreStyleRowCol checks pBrowseData->m_bDoReplaceAll
	// If it is TRUE, the row will immediately get updated

	// Save current cell's data
	TransferCurrentCell();

	BeginTrans(m_pAppData->strmReplaceAll);

	BOOL bOldLock = LockUpdate(TRUE);

	TRY
	{
		GX_FR_STATE* pState = GXGetLastFRState();
		if(pState)
		{
			pState->bTransaction = FALSE;

			// initialize searchparameter structure
			pState->strFind = lpszFind;
			pState->strReplace = lpszReplace;
			pState->bCase = bCase;
			pState->bNext = TRUE;
			pState->PrepareFindReplace();
		}

		CGXLongOperation theOp;
		theOp.SetStatusText(m_pAppData->strmReplacingAll, FALSE);
		theOp.SetLockedState(TRUE);
		theOp.SetCanRollback(TRUE);

		m_bCanceled = FALSE;

		// check active cell and replace

		m_nFirstRow = nRow;

		ROWCOL dwStartRow = nRow;
		ROWCOL dwRowCount = nRow;
		ROWCOL dwRows = 0;

		BOOL bFound = FALSE;

		ROWCOL nRowCount = (ROWCOL) OnGetRecordCount() + GetHeaderRows();

		while (nRow <= nRowCount && nRow > 0)
		{
			dwRows++;
			if (theOp.NeedMessages())
			{
				if (pState->bNext)
				{
					dwRowCount = GetRowCount()-dwStartRow;
				}
				theOp.SetPercentDone((int) (dwRows*100 / dwRowCount));
				theOp.DoMessages(m_bCanceled);
				if (m_bCanceled)
					break;
			}

			CGXStyle* pStyle = CreateStyle();
			ComposeStyleRowCol(nRow, nCol, pStyle);
			CGXControl* pControl = GetRegisteredControl(pStyle->GetControl());
			ASSERT(pControl != 0);

			if(pState)
			{
				pState->m_pStyle = pStyle; // cache style object so that ReplaceAll can resuse it
			}

			if (pControl->ReplaceAll(*pState, nRow, nCol))
				bFound = TRUE;

			if(pState)
			{
				pState->m_pStyle = NULL;
			}

			// free style object
			RecycleStyle(pStyle);

			if (pState->bNext)
			{
				OnTestGridDimension(++nRow, 0);
				nRowCount = (ROWCOL) OnGetRecordCount() + GetHeaderRows();
			}else
			{
				nRow--;
			}
		}

		theOp.SetPercentDone(-1);
		theOp.SetLockedState(FALSE);

		if (m_bCanceled && !pState->bTransaction)
		{
			AfxThrowUserException();
		}
		else if (m_bCanceled && theOp.GetRollbackConfirmedState())
		{
			if (pState->bTransaction)
			{
				Rollback();
			}
		}
		else
		{
			if (!bFound)
			{
				OnTextNotFound(GXGetLastFRState()->strFind);
			}
		}

#ifdef _UNICODE
		// Clean up non UNICODE text buffer
		if(pState)
		{
			delete[] pState->lpszMultiByteFindString;
			pState->lpszMultiByteFindString = NULL;
		}
#endif

		// update last row
		if(pBrowseData && pBrowseData->m_nEditMode != noMode)
		{
			Update();
		}

		CommitTrans();

		// Requery
		Requery();
	}
	CATCH(CException, e)
	{
		if(pBrowseData)
		{
			pBrowseData->m_bDoReplaceAll = FALSE;
		}
		Rollback();
		Requery();

		GX_THROW_LAST
	}
	END_CATCH

	pBrowseData->m_bDoReplaceAll = FALSE;

	LockUpdate(bOldLock);

	Redraw();

	// Reenable undo mechanism
	GetParam()->EnableUndo(bEnableUndo);

	SetCurrentCell(nEditRow, nEditCol, GX_SMART | GX_NOSETFOCUS);
}

BOOL CGXBrowserGrid::CanChangeSelection(CGXRange* pRange, BOOL bIsDragging, BOOL bKey)
{
	CGXBrowseParam* pBrowseData = GetBrowseParam();
	ASSERT(pBrowseData);
	// update current row if user selects a new range

	// skip if user is selecting columns or has not changed
	// data in current row

	if (pRange != NULL && !pRange->IsCols() && pBrowseData && pBrowseData->m_nEditMode != noMode)
	{
		BOOL bOK = TransferCurrentCell();
		CString s;
		if (bOK)
			bOK = Update(&s);

		// Update will catch exception
		if (!s.IsEmpty())
			SetWarningText(s);

		if (!bOK)
			return FALSE;
	}

	return CGXGridCore::CanChangeSelection(pRange, bIsDragging, bKey);
}

// OnMove
//
// Move the current cell

BOOL CGXBrowserGrid::OnMove(UINT nIDMoveCommand)
{
	switch (nIDMoveCommand)
	{
		case ID_RECORD_PREV:
			MoveCurrentCell(GX_UP);
			break;

		case ID_RECORD_FIRST:
			MoveCurrentCell(GX_TOP);
			break;

		case ID_RECORD_NEXT:
			MoveCurrentCell(GX_DOWN);
			break;

		case ID_RECORD_LAST:
			MoveCurrentCell(GX_BOTTOM);
			break;

		default:
			// Unexpected case value
			ASSERT(FALSE);
	}

	return TRUE;
}

void CGXBrowserGrid::OnUpdateRecordFirst(CCmdUI* pCmdUI)
{
	if (GetParam() == NULL)
	{
		pCmdUI->Enable(FALSE);
		return;
	}

	// enable if opened, can scroll backwards,
	pCmdUI->Enable(!IsOnFirstRecord());
}

void CGXBrowserGrid::OnUpdateRecordPrev(CCmdUI* pCmdUI)
{
	OnUpdateRecordFirst(pCmdUI);
}

void CGXBrowserGrid::OnUpdateRecordNext(CCmdUI* pCmdUI)
{
	if(GetParam() == NULL && pCmdUI)
	{
		pCmdUI->Enable(FALSE);
		return;
	}

	OnUpdateRecordLast(pCmdUI);
}

void CGXBrowserGrid::OnUpdateRecordLast(CCmdUI* pCmdUI)
{
	if(GetParam() == NULL && pCmdUI)
	{
		pCmdUI->Enable(FALSE);
		return;
	}

	// enable if opened and not already on last record
	pCmdUI->Enable(!IsOnLastRecord());
}

void CGXBrowserGrid::OnRecordDelete()
{
	DeleteRecords();
}

void CGXBrowserGrid::OnUpdateRecordDelete(CCmdUI* pCmdUI)
{
	if(GetParam() == NULL && pCmdUI)
	{
		pCmdUI->Enable(FALSE);
		return;
	}

	CGXRangeList* pSelList = GetParam()->GetRangeList();
	ASSERT(pSelList);
	if(pSelList)
	{
		// check that whole rows are selected and that "new row" is not selected
		pCmdUI->Enable(CanUpdate()
			// and not already on last record
			&& pSelList->IsAnyCellFromCol(0)
			&& !pSelList->IsAnyCellFromRow( GetAppendRow() )
			);
	}
}


// Undo current record

void CGXBrowserGrid::OnUpdateEditUndorecord(CCmdUI* pCmdUI)
{
	CGXBrowseParam* pBrowseData = GetBrowseParam();
	ASSERT(pBrowseData);
	pCmdUI->Enable(GetParam() && pBrowseData && pBrowseData->m_nEditMode != noMode);
}

void CGXBrowserGrid::OnEditUndorecord()
{
	CGXBrowseParam* pBrowseData = GetBrowseParam();
	ASSERT(pBrowseData);
	if (pBrowseData && pBrowseData->m_nEditMode != noMode)
		UndoRecord();
}

// Sorting

void CGXBrowserGrid::SortRows(CGXRange sortRange, CGXSortInfoArray& sortInfo, UINT flags /*= GX_UPDATENOW*/)
{
	// Sort the grid with the columns specified in awCols.

	OnTestGridDimension(GX_MAXROWCOL, 0);

	if (sortRange.IsTable())
		sortRange.SetRows(GetHeaderRows()+1, (ROWCOL) OnGetRecordCount() + GetHeaderRows());

	CGXGridCore::SortRows(sortRange, sortInfo, flags);
}

BOOL CGXBrowserGrid::StoreMoveDataRows(const CGXRange& sortRange, const CRowColArray& awRowIndex)
{
	ASSERT(sortRange.IsRows());
	// ASSERTION-> Only full rows supported. Override this
	// method if you want to support sorting only a limited
	// range of cells ->END

	CRowColArray newRowIndex;

	newRowIndex.SetSize(awRowIndex.GetSize());

	// First, replace row ids with existing GetRowIndex ids
	int nIndex = 0;
	for (nIndex = 0; nIndex < awRowIndex.GetSize(); nIndex++)
		newRowIndex[nIndex] = GetRowIndex(awRowIndex[nIndex]+sortRange.top);

	// Now, copy row ids to m_awRowIndex
	if ((ROWCOL) GetBrowseParam()->m_awRowIndex.GetSize() <= sortRange.bottom)
		GetBrowseParam()->m_awRowIndex.SetSize((int) sortRange.bottom+1);

	// fill first ids
	for (nIndex = (int)GetBrowseParam()->m_awRowIndex.GetSize(); (ROWCOL) nIndex < sortRange.top; nIndex++)
		GetBrowseParam()->m_awRowIndex[nIndex] = (ROWCOL) nIndex;

	for (nIndex = 0; nIndex < awRowIndex.GetSize(); nIndex++)
		GetBrowseParam()->m_awRowIndex[nIndex+(int) sortRange.top] = newRowIndex[nIndex];

	// also give CGXData a chance
	GetParam()->GetData()->StoreMoveDataRows(sortRange, awRowIndex);

	return TRUE;
}

void CGXBrowserGrid::SortCols(CGXRange sortRange, CGXSortInfoArray& sortInfo, UINT flags /*= GX_UPDATENOW*/)
{
	// Sort the grid with the columns specified in awCols.

	OnTestGridDimension(0, GX_MAXROWCOL);

	if (sortRange.IsTable())
		sortRange.SetCols(GetHeaderCols()+1, GetColCount());

	CGXGridCore::SortCols(sortRange, sortInfo, flags);
}

BOOL CGXBrowserGrid::StoreMoveDataCols(const CGXRange& sortRange, const CRowColArray& awColIndex)
{
	ASSERT(sortRange.IsCols());
	// ASSERTION-> Only full rows supported. Override this
	// method if you want to support sorting only a limited
	// range of cells ->END

	CRowColArray newColIndex;

	newColIndex.SetSize(awColIndex.GetSize());

	// First, replace row ids with existing GetColIndex ids
	int nIndex = 0;
	for (nIndex = 0; nIndex < awColIndex.GetSize(); nIndex++)
		newColIndex[nIndex] = GetColIndex(awColIndex[nIndex]+sortRange.left);

	// Now, copy row ids to m_awColIndex
	if ((ROWCOL) GetBrowseParam()->m_awColIndex.GetSize() <= sortRange.right)
		GetBrowseParam()->m_awColIndex.SetSize((int) sortRange.right+1);

	// fill first ids
	for (nIndex = 0; (ROWCOL) nIndex < sortRange.left; nIndex++)
		GetBrowseParam()->m_awColIndex[nIndex] = (ROWCOL) nIndex;

	for (nIndex = 0; nIndex < awColIndex.GetSize(); nIndex++)
		GetBrowseParam()->m_awColIndex[nIndex+(int) sortRange.left] = newColIndex[nIndex];

	// also give CGXData a chance
	GetParam()->GetData()->StoreMoveDataCols(sortRange, awColIndex);

	return TRUE;
}

#if _MFC_VER >= 0x0400

BOOL CGXBrowserGrid::OnGridDrop(CGXNoOleDataObjectProxy* pDataObject,
	DROPEFFECT dropEffect, CPoint point)
{
	if (!GetBrowseParam()->m_bCanStoreGridCellInCGXData
		&& (m_dwDndDropTargetFlags & GX_DNDSTYLES) != 0)
	{
		ASSERT(0);
		// ASSERT-> Pasting style information is not supported
		// with browser grids unless m_bCanStoreGridCellInCGXData is TRUE ->END
	
		return FALSE;
	}

	if (dropEffect == DROPEFFECT_COPY)
		// OnGridDrop will efficiently redraw the grid
		return CGXGridCore::OnGridDrop(pDataObject, dropEffect, point);
	else
	{
		// We have to redraw the whole grid
		BOOL bLock = LockUpdate(TRUE);
		BOOL bRet = CGXGridCore::OnGridDrop(pDataObject, dropEffect, point);
		LockUpdate(bLock);
		Redraw(GX_INVALIDATE);
		
		return bRet;
	}
}

#endif

BOOL CGXBrowserGrid::ClearCells(const CGXRange& range, BOOL bStyleOrValue)
{
	CGXRangeList selList;
	selList.AddTail(new CGXRange(range));
	return ClearCells(selList, bStyleOrValue);
}

BOOL CGXBrowserGrid::ClearCells(const CGXRangeList& selList, BOOL bStyleOrValue)
{
	if (!GetBrowseParam()->m_bCanStoreGridCellInCGXData && bStyleOrValue)
	{
		ASSERT(0);
		// ASSERT-> Clearing out style information is not supported
		// with browser grids unless m_bCanStoreGridCellInCGXData is TRUE ->END
	
		return FALSE;
	}

	// determine affected rows for efficient redrawing
	ROWCOL nTop = GX_INVALID, nBottom = GX_INVALID;

	if (selList.GetCount() == 1)
	{
		ROWCOL nRow, nCol;
		GetCurrentCell(nRow, nCol);

		nTop = min(nRow, selList.GetHead()->top);
		nBottom = max(nRow, selList.GetHead()->bottom);
	}

	// CGXGridCore::ClearCells screen update is too optimized - with
	// CGXBrowserGrid we always have to redraw complete rows
	// and not individual cells

	BOOL bLock = LockUpdate(TRUE);
	BOOL bRet = CGXGridCore::ClearCells(selList, FALSE);
	LockUpdate(bLock);

	// Our own update of the screen
	if (nTop != GX_INVALID)
	{
		RedrawRowCol(CGXRange().SetRows(nTop, nBottom), GX_INVALIDATE);
		// refresh formula cells 
		RefreshViews();
	}
	else
		Redraw(GX_INVALIDATE);

	return bRet;
}

BOOL CGXBrowserGrid::PasteTextFromBuffer(LPCTSTR psz, DWORD size, const CGXRange& range)
{
	ROWCOL nRow1, nRow2, nCol;
	GetCurrentCell(nRow1, nCol);

	// CGXGridCore::PasteTextFromBuffer screen update is too optimized - with
	// CGXBrowserGrid we always have to redraw complete rows
	// and not individual cells

	BOOL bLock = LockUpdate(TRUE);

	// make sure CGXGridCore::PasteTextFromBuffer does not try to append
	// rows when CanAppend returns FALSE
	DWORD nClipboardFlags = m_nClipboardFlags;
	if (!CanAppend())
		m_nClipboardFlags |= GX_DNDNOAPPENDROWS;

	BOOL bRet = CGXGridCore::PasteTextFromBuffer(psz, size, range);

	// restore original setting 
	m_nClipboardFlags = nClipboardFlags;

	LockUpdate(bLock);
	
	GetCurrentCell(nRow2, nCol);

	// Redraw all rows between old and new current row
	RedrawRowCol(CGXRange().SetRows(nRow1, nRow2), GX_INVALIDATE);

	// refresh formula cells 
	RefreshViews();

	return bRet;
}

BOOL CGXBrowserGrid::SetControlTextRowCol(ROWCOL nRow, ROWCOL nCol, const CString& str, UINT nFlags, const CGXStyle* pOldStyle)
{
	CGXBrowseParam* pBrowseData = GetBrowseParam();
	ASSERT(pBrowseData);
	BOOL	bSuccess = FALSE;

	// check if there are pending changes in another record
	if(pBrowseData && pBrowseData->m_nEditMode !=noMode && nRow != pBrowseData->m_nCurrentRow)
	{
		CString sErrorDesc;

		// flush them to the data source
		if (!Update(&sErrorDesc))
			return FALSE;   // could not update previous record
	}

	// check if cell isn't readonly
	CGXStyle* pStyle = NULL;
	
	if (pOldStyle == NULL)
	{
		pStyle = CreateStyle();
		ComposeStyleRowCol(nRow, nCol, pStyle);
		pOldStyle = pStyle;
	}

	// will cancel ops
	if (pOldStyle->GetIncludeReadOnly() && pOldStyle->GetReadOnly())
	{
		// TODO: set or display a notification that operation could not be performed
		// ano not only return silently
 		return FALSE;   
	}

	// ensure that the current row is in edit mode
	if (pBrowseData->m_nEditMode == noMode)
	{
		if (MoveTo(nRow))
			Edit(nRow);
		else
			AddNew();
	}

	// if AddNew or Edit was succesfull
	if(pBrowseData && pBrowseData->m_nEditMode != noMode)
		bSuccess = CGXGridCore::SetControlTextRowCol(nRow, nCol, str, nFlags, pOldStyle);

	if (pStyle)
		RecycleStyle(pStyle);

	return bSuccess;
}
