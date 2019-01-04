// This is a part of the Objective Grid C++ Library.
// Copyright © 1999-2004 Quovadx, Inc.  All Rights Reserved.
// 
// 
// This computer software is owned by Quovadx, Inc. and is protected by 
// U.S. copyright laws and other laws and by international treaties. This 
// computer software is furnished by Quovadx, Inc. pursuant to a written 
// license agreement and may be used, copied, transmitted, and stored 
// only in accordance with the terms of such license agreement and with 
// the inclusion of the above copyright notice.  This computer software or 
// any other copies thereof may not be provided or otherwise made available 
// to any other person.
// 
// U.S. Government Restricted Rights.  This computer software: 
//      (a) was developed at private expense and is in all respects the 
//          proprietary information of Quovadx, Inc.; 
//      (b) was not developed with government funds; 
//      (c) is a trade secret of Quovadx, Inc. for all purposes of the 
//          Freedom of Information Act; and 
//      (d) is a commercial item and thus, pursuant to Section 12.212 
//          of the Federal Acquisition Regulations (FAR) and DFAR 
//          Supplement Section 227.7202, Government’s use, duplication or 
//          disclosure of the computer software is subject to the restrictions 
//          set forth by Quovadx, Inc.
//
//
// This source code is only intended as a supplement to
// the Objective Grid Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding
// the Objective Grid product.
//
// Author: Stefan Hoenig
//

// gxcore.h : interface of the core classes


#ifndef _GXCORE_H_
#define _GXCORE_H_

#ifndef _GXTCHAR_H_
#include "grid\gxtchar.h" 
#endif

#ifndef _GXABSTR_H_
#include "grid\gxabstr.h"
#endif

#ifndef _GXPLUGIN_H_
#include "grid\gxplugin.h"
#endif

#ifndef _GXSTYLES_H_
#include "grid\gxstyles.h"   // CGXStyle
#endif

#ifndef _GXCOLL_H_
#include "grid\gxcoll.h"     // Collections
#endif

#ifndef _GXIME_H_
#include "grid\gxime.h"
#endif

// constants

//
// GridMFC Extension DLL
// initialize declaration context
//

#ifdef _GXDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    GX_DATAEXT
#endif

// classes declared in this header file

class CGXRange;
class CGXRangeList;
class CGXProperties;
class CGXGridCore;
class CGXGridParam;
class CGXSortInfoArray;
struct CGXSortInfo;

// OLE Drag&Drop support
class CGXNoOleDataObjectProxy;
class CGXNoOleDataSourceProxy;

// Tooltip support
class CGXNoToolTipCtrlProxy;

// forward declarations;

class CGXPrintDevice;
class CGXControl;
class CGXData;
class CGXSpanCellPool;
class CGXCoveredCellPool;
class CGXDelayedRangePool;

class COleDataObject;
class COleDropSource;
class COleDropSource;

class CGXCommand;
class CGXGridHint;

// header file

// #define TICKCOUNT       // used to test performance
// #define _CCHIT           // used to test LookupStyleRowCol hits

// update technique and SetEditCell flags
// used by all command and update methods

const UINT   GX_NOREDRAW            = 0x0000;
const UINT   GX_INVALIDATE          = 0x0001;
const UINT   GX_UPDATENOW           = 0x0002;
const UINT   GX_SMART               = 0x0004;

// SetCurrentCell - extra flags
const UINT   GX_SCROLLINVIEW        = 0x0008;
const UINT   GX_DISPLAYEDITWND      = 0x0010;
const UINT   GX_NOSETFOCUS          = 0x0020;
const UINT   GX_NOSYNCCURRENTCELL   = 0x0040;
const UINT   GX_NOSELECTRANGE       = 0x0080;

// Resize rows and cols to fit size - extra flags
const UINT   GX_NOSHRINKSIZE        = 0x0008;

 
// flags for drawing lines used by
// CGXGridCore::DrawGridLine

const UINT   GX_TRACKLINE           = 0x0001;
const UINT   GX_SELDRAGLINE         = 0x0002;
const UINT   GX_ACTIVECELL          = 0x0004;
const UINT   GX_INVERT              = 0x0008;

// Predefined Color Properties
const int    GX_COLOR_GRIDLINES     = 0;
const int    GX_COLOR_FIXEDLINES    = 1;
const int    GX_COLOR_TRACKINGLINE  = 2;
const int    GX_COLOR_DRAGGINGLINE  = 3;
const int    GX_COLOR_BACKGROUND    = 4;

// Flags for Hitting, used in

// CGXGridCore::DoLButtonDown
// CGXGridCore::DoLButtonUp
// CGXGridCore::DoMouseMove
// CGXGridCore::OnLButtonHitRowCol

// CGXGridCore::m_nHitState contains following flags

const WORD GX_HIT            = 0x0001;
const WORD GX_SELECT         = 0x0002;
const WORD GX_HITSTART       = 0x0004;
const WORD GX_HITMOVE        = 0x0008;
const WORD GX_HITEND         = 0x0010;
const WORD GX_HITLEAVE       = 0x0020;
const WORD GX_HITINCELL      = 0x0040;
const WORD GX_CTRLPRESSED    = 0x0080;
const WORD GX_HITCURRENTCELL = 0x0100;
const WORD GX_FILLDRAG		 = 0x0200; // For excel like auto fill support

// used in GetStyleRowCol and StoreStyleRowCol
// indicating that a range and not only one cell is meant to be retrieved
// (either nRow or nCol is 0, see the class-reference)
const int GXRANGETYPE = -1;

// Enums

// GXDirectionType is used for specifying directions
// Some methods using its values are:
// CGXGridCore::DoScroll
// CGXGridCore::OnAutoScroll
// CGXGridCore::OnMoveEdit
// and many more

enum GXDirectionType
{
	GX_UP               = 1,
	GX_LEFT             = 2,
	GX_DOWN             = 3,
	GX_RIGHT            = 4,
	GX_PGDOWN           = 5,
	GX_PGUP             = 6,
	GX_TOP              = 7,
	GX_BOTTOM           = 8,
	GX_MOSTLEFT         = 9,
	GX_MOSTRIGHT        = 10,
	GX_TOPLEFT          = 11,
	GX_BOTTOMRIGHT      = 12
};

// GXHitTestType is used by
// CGXGridCore::HitTest

enum GXHitTestType
{
	GX_NOHIT            = 0,
	GX_VERTLINE         = 1,
	GX_HORZLINE         = 2,
	GX_CELLHIT          = 3,
	GX_HEADERHIT        = 4,
	GX_SELEDGEHIT       = 5,
	GX_FILLHANDLEHIT	= 6,
	GX_HDNCOL_VERTLINE	= 7,
	GX_HDNROW_HORZLINE	= 8,
};

// GXTrackingType specifies, if the user is tracking a vertical or horizontal line
// used by:
// CGXGridCore::OnStartTracking
// CGXGridCore::OnEndTracking
// CGXGridCore::OnMoveTracking

enum GXTrackingType
{
	GX_TRACKHEIGHT      = 1,
	GX_TRACKWIDTH       = 2
};

// GXDragModeType specifies, if the user is dragging rows or columns
enum GXDragModeType
{
	GX_SELDRAG_COL      = 1,
	GX_SELDRAG_ROW      = 2
};

// GXScrollbarSettings is used in SetScrollBar to specify the scrollbar-behaviour
enum GXScrollbarSettings
{
	gxnDisabled  = 0,
	gxnEnabled   = 1,
	gxnAutomatic = 2,
	gxnShared    = 4,
	gxnEnhanced  = 8
};

// Drawing technique
enum GXDrawingTechnique
{
	gxDrawDirectToDC = 0,   // All output is directly drawn to dc
	gxDrawUsingMemDC = 1    // All output is drawn using a CMemDC (less flickering but slower)
};

// How to handle record count while printing (usefull for ODBC or DAO grids)
enum PrintHandleRecordCount
{
	gxCountNever = 0,	// Let record count grow while printing
	gxCountAlways = 1,	// Count records for both printing and print preview before printing
	gxCountPrint = 2	// Count records only for printing but not for print preview (default)
};


enum DirectionValue
{
	GX_HORZ             = 1,
	GX_VERT             = 2,
	GX_BOTH             = 3
};

// drawing (used in OnDrawTopLeftBottomRight)
const int gxnFlagSel = 0x10;
const int gxnFlagColor = 0x20;
const int gxnFlagSpanned = 0x40;
const int gxnFlagCovered = 0x80;
const int gxnFlagSpannedCont = 0x100;
const int gxnFlagHorzLine = 0x200;
const int gxnFlagVertLine = 0x400;
const int gxnFlagFixedVertLine = 0x800;
const int gxnFlagFixedHorzLine = 0x1000;

// floating cells
const WORD gxnFloatDisable       = 0x00;
const WORD gxnFloatDelayEval     = 0x01;
const WORD gxnFloatEvalOnDisplay = 0x02;

// merge cells
const WORD gxnMergeDisable       = 0x00;
const WORD gxnMergeDelayEval     = 0x01;
const WORD gxnMergeEvalOnDisplay = 0x02;
const WORD gxnMergeHorzOnly      = 0x04;
const WORD gxnMergeVertOnly      = 0x08;
const WORD gxnMergeOverHidden    = 0x10;

// CGXStyle - SetMergeCell attribute
const unsigned GX_MERGE_HORIZONTAL   = 0x01;
const unsigned GX_MERGE_VERTICAL     = 0x02;
const unsigned GX_MERGE_COMPVALUE    = 0x04;
const unsigned GX_MERGE_COMPSTYLE    = 0x00;
const unsigned GX_MERGE_DISABLED     = 0x00;

// Flags for allowing selection used by
// CGXGridParam::EnableSelection
// CGXGridParam::IsEnableSelection

const WORD GX_SELFULL        = 0xff;
const WORD GX_SELNONE        = 0x00;
const WORD GX_SELROW         = 0x01;
const WORD GX_SELCOL         = 0x02;
const WORD GX_SELTABLE       = 0x04;
const WORD GX_SELCELL        = 0x08;
const WORD GX_SELMULTIPLE    = 0x10;
const WORD GX_SELSHIFT       = 0x20;
const WORD GX_SELKEYBOARD    = 0x40;

// Flags for changig row and col width used by
// CGXGridParam::EnableTrackRowHeight
// CGXGridParam::EnableTrackColWidth
// CGXGridParam::IsEnableTrackRowHeight
// CGXGridParam::IsEnableTrackColWidth

const WORD GX_TRACK_DISABLE     = 0x00;
const WORD GX_TRACK_ALL         = 0x01;
const WORD GX_TRACK_INDIVIDUAL  = 0x02;
const WORD GX_TRACK_EXTHITTEST  = 0x04;
const WORD GX_TRACK_NOTHEADER   = 0x08;

const WORD GX_TRACK_NOPRESSEDHEADER   = 0x10;   // don't show headers pressed
const WORD GX_TRACK_NOMARKTRACKLINE   = 0x20;   // don't mark line of tracked row/column
const WORD GX_TRACK_NOINVERTLINE      = 0x40;   // don't invert line for new row/column size
const WORD GX_TRACK_SMOOTHHEADER      = 0x80;   // show header contents while dragging
const WORD GX_TRACK_SMOOTHCELLS       = 0x100;  // show all cell contents while dragging

const WORD GX_TRACK_DEFAULT     = GX_TRACK_INDIVIDUAL
		| GX_TRACK_SMOOTHHEADER | GX_TRACK_NOPRESSEDHEADER | GX_TRACK_NOMARKTRACKLINE;

// Flags for Special Modes, used by
// CGXGridParam::SetSpecialMode
// CGXGridParam::IsSpecialMode

const WORD GX_MODELISTBOX     = 0x03;   // both
const WORD GX_MODELBOX_SS     = 0x01;   // Singe selection listbox emulation
const WORD GX_MODELBOX_MS     = 0x02;   // Multi selection listbox emulation

// Undo information needed when removing rows/columns
const WORD GX_RMUNDO_BASESTYLES = 0x01; // row and column styles
const WORD GX_RMUNDO_CELLSTYLES = 0x02; // cell contents

// Cell activation (set focus to cell) see m_wActivateCell
const WORD GX_CAFOCUS_CLICKINTEXT   = 0x01;     // (default)
const WORD GX_CAFOCUS_CLICKONCELL   = 0x02;
const WORD GX_CAFOCUS_SETCURRENT    = 0x04;
const WORD GX_CAFOCUS_DBLCLICKONCELL = 0x08;

// for compatibility with 1.0 and 1.1
#define GX_HIDE_ALWAYS GX_HIDE_ALLWAYS

// Hide current cell
const WORD GX_HIDE_NEVER            = 0x00;
const WORD GX_HIDE_ALWAYS           = 0x01;
const WORD GX_HIDE_INACTIVEFRAME    = 0x02;

// Drawíng order
const WORD GX_DRAWORDER_ROWS = 0x00;        // (default)
const WORD GX_DRAWORDER_COLS = 0x01;

// Drag and Drop options
const DWORD GX_DNDDISABLED   = 0x00;        // disable drop target
const DWORD GX_DNDCOLHEADER  = 0x01;        // also copy/move column header cells
const DWORD GX_DNDROWHEADER  = 0x02;        // also copy/move row header cells
const DWORD GX_DNDMULTI      = 0x04;        // allow dragging multiple selections
const DWORD GX_DNDTEXT       = 0x08;        // force dragging of CF_TEXT clipboard format
const DWORD GX_DNDSTYLES     = 0x10;        // force dragging of internal styles format
const DWORD GX_DNDCOMPOSE    = 0x20;        // when copying internal styles, compose the full style of the cell
											// and do not copy only the cell specific attributes
const DWORD GX_DNDAUTOSCROLL = 0x40;        // enable autoscroll when user drags out of windows
const DWORD GX_DNDEGDESCROLL = 0x80;        // enable edgescroll when user drags to the corner of the window
const DWORD GX_DNDDIFFRANGEDLG = 0x100;     // Paste only: Display "Selected Range is Different"-Dialog
const DWORD GX_DNDNOAPPENDROWS = 0x200;     // If the user pastes (or drops) more rows than
											// currently available, don't append as many rows as needed
const DWORD GX_DNDNOAPPENDCOLS = 0x400;     // If the user pastes (or drops) more columns than
											// currently available, don't append as many columns as needed
const DWORD GX_DNDEXPRESSION = 0x800;       // Copy Expression instead of value	(when GX_DNDSTYLES is set)
											// this setting has no effect for direct copy/paste in sheet
											// and for CF_TEXT clipboard format
const DWORD GX_DNDMULTILINETEXT = 0x1000;	// preserves \t \r \n in the cell's value

// some nType values that can be passed to SetStyleRange, GetStyleRowCol etc.
const int GX_VALUE_BASESTYLE  = -1;		// used for row, column and table style
const int GX_VALUE_TEXT       = 0;		// used to store/retrieve plain style information in cell
const int GX_VALUE_EXPRESSION = 1;		// use this when calling SetValueRage, StoreStyleRowCol etc.
										// and the value should be parsed (date, time, number, formula etc.)

const WORD GX_EXPR_DISPLAYNEVER  = 0;	// never display formula expression in cell
const WORD GX_EXPR_DISPLAYACTIVE = 1;	// display formula expression in cell when cell is active
const WORD GX_EXPR_DISPLAYALWAYS = 2;	// always display formula expression 

// GX_NXYFACTOR specifies the granularity of logical values.
// It is used in Width_LPtoDP, Width_DPtoLP, Height_LPtoDP and Height_DPtoLP
// to convert between logical and vertical values.
const int   GX_NXYFACTOR = 1000;

const int   GX_NXAVGWIDTH = 1000;       // logical char width (average)
const int   GX_NYHEIGHT = 1000;         // logical char height

const ROWCOL GX_INVALID      = 0xFFFFFFFF;
const ROWCOL GX_MAXROWCOL    = 0xFFFFFFFE;


// Excel like auto fill flags
const DWORD GX_XLFILLDISABLED = 0x00;		// Disable excel like drag&fill...
const DWORD GX_XLFILLTEXT = 0x01;			// During excel fill only value is copied over...
const DWORD GX_XLFILLSTYLE = 0x02;			// During excel fill the whole style is copied over...


// for the cell tips
const DWORD GX_CELLTIP_ID_NOTDEFINED			=	LONG_MAX;
const DWORD GX_CELLTIP_ID_TEXT					=	0x00000001;
const DWORD GX_CELLTIP_ID_BITMAP				=	0x00000002;

const DWORD GX_CELLTIP_CLIPPING_BYCELL_HORZ		=	0x0001;
const DWORD GX_CELLTIP_CLIPPING_BYCELL_VERT		=	0x0002;
const DWORD GX_CELLTIP_CLIPPING_BYGRID_HORZ		=	0x0004;
const DWORD GX_CELLTIP_CLIPPING_BYGRID_VERT		=	0x0008;
const DWORD GX_CELLTIP_CLIPPING_BYSCREEN_HORZ	=	0x0010;
const DWORD GX_CELLTIP_CLIPPING_BYSCREEN_VERT	=	0x0020;


// Alignment conversion
UINT    AFXAPI AlignTAToDT(UINT ntAlign);
UINT    AFXAPI AlignDTToTA(UINT ntAlign);
LONG    AFXAPI AlignTAToES(UINT ntAlign);
UINT    AFXAPI AlignESToTA(LONG ltAlign);

// packing row and column in a DWORD

DWORD AFXAPI GXRowColToDWord(ROWCOL nRow, ROWCOL nCol);
WORD AFXAPI GXDWordToRow(DWORD dwValue);
WORD AFXAPI GXDWordToCol(DWORD dwValue);

// Performance testing

#ifdef TICKCOUNT
extern DWORD tickIndFont, tickStdFont, tickDrawItem, tickDraw, tickLookup;
extern DWORD tickLookupFont, tickLoadFont, tickCompStd, tickComposeStyle;
extern DWORD tick1, tick2, tick3, tick4, tick5, tick6, tick7, tick8, tick9, tick10;
#endif

/////////////////////////////////////////////////////////////////////////////
// class CGXRange

class CGXRange
{
public:
	// Type
	enum RangeType { rtCells = 0, rtRows = 1, rtCols = 2, rtTable = 3 };

public:
	// operations
	CGXRange();
	CGXRange(const CGXRange& r);
	CGXRange(const CGXRange* r);
	CGXRange(ROWCOL nTop, ROWCOL nLeft, ROWCOL nBottom, ROWCOL nRight);
	CGXRange(ROWCOL nRow, ROWCOL nCol);

	const CGXRange& operator=(const CGXRange& r);

	int operator ==(const CGXRange &r) const;
	int operator !=(const CGXRange &r) const;

	CGXRange& SetCells(ROWCOL nTop, ROWCOL nLeft, ROWCOL nBottom, ROWCOL nRight);
	CGXRange& SetCells(ROWCOL nRow, ROWCOL nCol);
	CGXRange& SetRows(ROWCOL nFrom, ROWCOL nTo);
	CGXRange& SetRows(ROWCOL nRow);
	CGXRange& SetCols(ROWCOL nFrom, ROWCOL nTo);
	CGXRange& SetCols(ROWCOL nCol);
	CGXRange& SetTable();

	CGXRange& ExpandRange(ROWCOL nFirstRow, ROWCOL nFirstCol, ROWCOL nRowCount, ROWCOL nColCount);
	BOOL IntersectRange(const CGXRange& r1, const CGXRange& r2);
	BOOL UnionRange(const CGXRange& r1, const CGXRange& r2);


	BOOL IsCellInRange(ROWCOL nRow, ROWCOL nCol) const;

	BOOL IsRows() const;
	BOOL IsCols() const;
	BOOL IsCells() const;
	BOOL IsTable() const;

	BOOL IsValid() const;

	ROWCOL GetWidth() const;
	ROWCOL GetHeight() const;

	// Iterate through range
	BOOL GetFirstCell(ROWCOL &nRow, ROWCOL &nCol) const;
	BOOL GetNextCell(ROWCOL &nRow, ROWCOL &nCol, BOOL bSortByRow = TRUE) const;

public:
	// data
	RangeType   rtType;

	ROWCOL      top,
				left,
				bottom,
				right;

	BOOL        m_bValid;
};

CArchive& AFXAPI operator<<(CArchive& ar, const CGXRange& range);
CArchive& AFXAPI operator>>(CArchive& ar, CGXRange& range);

typedef CGXRange* LPRANGE;

/////////////////////////////////////////////////////////////////////////////
// class CGXRangeList

class CGXRangeList: public CPtrList
{
	DECLARE_SERIAL(CGXRangeList)
public:

	BOOL        IsCellInList(ROWCOL nRow, ROWCOL nCol, POSITION posWithOut = NULL/*, BOOL bEdit = TRUE*/) const;
	POSITION    FindRange(ROWCOL nRow, ROWCOL nCol);
	BOOL        IsAnyCellFromCol(ROWCOL nCol);
	BOOL        IsAnyCellFromRow(ROWCOL nRow);
	BOOL        GetColArray(ROWCOL nColCount, CRowColArray& awLeft, CRowColArray& awRight, BOOL bFixed = FALSE) const;
	BOOL        GetRowArray(ROWCOL nRowCount, CRowColArray& awTop, CRowColArray& awBottom, BOOL bFixed = FALSE) const;
	void        DeleteGarbage();

	void        InsertRows(ROWCOL nRow, ROWCOL nCount);
	void        InsertCols(ROWCOL nRow, ROWCOL nCount);
	void        RemoveRows(ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nRowCount = GX_MAXROWCOL);
	void        RemoveCols(ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nColCount = GX_MAXROWCOL);
	void        MoveRows(ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow, ROWCOL nRowCount = GX_MAXROWCOL);
	void        MoveCols(ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nDestCol, ROWCOL nColCount = GX_MAXROWCOL);

#ifdef _DEBUG
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Implementation
public:
	BOOL        FindFixedRows(POSITION& pos, ROWCOL nCount, ROWCOL& nStart, ROWCOL& nEnd);
	BOOL        FindFixedCols(POSITION& pos, ROWCOL nCount, ROWCOL& nStart, ROWCOL& nEnd);

	virtual ~CGXRangeList();
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	virtual CGXRangeList& operator=(const CGXRangeList& l);

// type safe return values from CPtrList

// Attributes (head and tail)
	// peek at head or tail
	CGXRange*& GetHead();
	CGXRange* GetHead() const;
	CGXRange*& GetTail();
	CGXRange* GetTail() const;

// Operations
	// get head or tail (and remove it) - don't call on empty list !
	CGXRange* RemoveHead();
	CGXRange* RemoveTail();

	// add before head or after tail
	POSITION AddHead(CGXRange* newElement);
	POSITION AddTail(CGXRange* newElement);

	// add another list of elements before head or after tail
	void AddHead(CGXRangeList* pNewList);
	void AddTail(CGXRangeList* pNewList);

	// iteration
	CGXRange*& GetNext(POSITION& rPosition); // return *Position++
	CGXRange* GetNext(POSITION& rPosition) const; // return *Position++
	CGXRange*& GetPrev(POSITION& rPosition); // return *Position--
	CGXRange* GetPrev(POSITION& rPosition) const; // return *Position--

	// getting/modifying an element at a given position
	CGXRange*& GetAt(POSITION position);
	CGXRange* GetAt(POSITION position) const;
	void SetAt(POSITION pos, CGXRange* newElement);

	// inserting before or after a given position
	POSITION InsertBefore(POSITION position, CGXRange* newElement);
	POSITION InsertAfter(POSITION position, CGXRange* newElement);

	// helper functions (note: O(n) speed)
	POSITION Find(CGXRange* searchValue, POSITION startAfter = NULL) const;
						// defaults to starting at the HEAD
						// return NULL if not found

	// Added members

	void        DeleteAll();
	void        DeleteTail();
	void        DeleteAt(POSITION position);
};

/////////////////////////////////////////////////////////////////////////////
// class CGXProperties

// colors
const int gxnPropGridLines        = 0;
const int gxnPropFixedLines       = 1;
const int gxnPropTrackingLines    = 2;
const int gxnPropDraggingLines    = 3;
const int gxnPropBackground       = 4;

// Defines

#define INCHtoDP(f) ((int) (f*((double) GXGetFontState()->m_nLogPixelsX)+0.51))
#define CMtoDP(f)   ((int) (f*((double) GXGetFontState()->m_nLogPixelsX)/2.54))
#define DPtoINCH(f) ((float) f/((double) GXGetFontState()->m_nLogPixelsX))
#define DPtoCM(f)   ((float) f*2.54/((double) GXGetFontState()->m_nLogPixelsX))

#define NROWS   10      // No of Rows for Footer/Header

// Predefined Tokens

const GTK_DOCUMENT      = 0;
const GTK_APP           = 1;
const GTK_PAGE          = 2;
const GTK_NOOFPAGE      = 3;
const GTK_DATE          = 4;
const GTK_REGISTER      = 5;


class CGXProperties: public CObject
{
	DECLARE_SERIAL(CGXProperties)

	// structures
	struct UserPropertyInfo
	{
		UserPropertyInfo();
		UserPropertyInfo(const UserPropertyInfo& srcInfo);
		~UserPropertyInfo ();

		WORD    nID;
		CString sName;
		CGXStyle* pStyle;
	};

public:
	// constants
	CGXAppData* m_pAppData;

	// profile entries
	static LPCTSTR szMarkRowHeader;
	static LPCTSTR szMarkColHeader;
	static LPCTSTR szDisplayRowHeader;
	static LPCTSTR szDisplayColHeader;
	static LPCTSTR szDisplay3DButtons;
	static LPCTSTR szDisplayVertLines;
	static LPCTSTR szDisplayHorzLines;

	static LPCTSTR szDefaultSection;

	// printing
	static LPCTSTR szPrintVertLines;
	static LPCTSTR szPrintHorzLines;
	static LPCTSTR szBlackWhite;
	static LPCTSTR szRowHeaders;
	static LPCTSTR szColHeaders;
	static LPCTSTR szCenterVertical;
	static LPCTSTR szCenterHorizontal;
	static LPCTSTR szPageOrder;
	static LPCTSTR szPrintFrame;
	static LPCTSTR szMargins;
	static LPCTSTR szFirstPage;
	static LPCTSTR szDistances;

	// current cell
	CString sInvertNormal;
	CString sInvertThick;
	CString sInvertDrawBorder;
	CString sInvertThickBorder;
	CString sInvertNoBorder;

public:
	// operations
	CGXProperties();
	CGXProperties(const CGXProperties& p);

	virtual ~CGXProperties();

	const CGXProperties& operator=(const CGXProperties& p);

	virtual void AddDefaultUserProperties();
	CGXStyle m_styleEmpty;

	void Serialize(CArchive& ar);

#ifdef _DEBUG
	void AssertValid() const;
	void Dump(CDumpContext& dc) const;
#endif

	// Profile
	virtual void WriteProfile() const;
	virtual BOOL ReadProfile();
	void SetSection(LPCTSTR pszSection);
	const CString& GetSection() const;

	// Colors
	int AddColorProperty(LPCTSTR pszName, COLORREF color = RGB(192,192,192));
	int AddColorProperty(UINT nID, COLORREF color = RGB(192,192,192));
	COLORREF GetColor(int nIndex) const;
	void SetColor(int nIndex, COLORREF rgbColor);

	// Printing
	void SetPrinting(BOOL b);
	BOOL GetPrinting() const;

	void                OnPrintHeaderAndFooter(CDC* pDC, CPrintInfo* pInfo, CDocument* pDoc = NULL, CGXGridParam* pParam = NULL);
	int                 CalculateHeight(CDC* pDC, CGXData &data, CGXStylesMap* pStylesMap);
	void                PrintHeaderFooter(CDC* pDC, CPrintInfo* pInfo, CRect& rect, CGXData& data, CGXStylesMap* pStylesMap);
	virtual CString     ParseText(LPCTSTR sz);

	int                 AddToken(LPCTSTR sz);
	virtual CString     SubstTokenText(int nToken, CString& sRest);
	CString             GetTokenArgs(CString& sRest);

	// Header&Footer
	void GetDistances(int& top, int& bottom);
	void SetDistances(int top, int bottom);
	void SetFirstPage(int nStart);
	int GetFirstPage();

	CStringArray        m_sTokenArray;
	CStringArray        m_sSubstTokenArray;

	// User attributes
	void AddUserProperty(WORD nID, const CGXStyle& style);
	void SetUserProperty(WORD nID, const CGXStyle& style);
	const CGXStyle& GetUserProperty(WORD nID);
	const CMapWordToPtr& GetUserPropertyInfoMap() const;

	// parent grid
	CGXGridCore* Grid() const;

protected:
	void Free();

public:
	// user attributes
	CMapWordToPtr      m_UserPropertyInfoMap;

	// attributes
	BOOL
			m_b3dButtons,           // 3d look alike Headers
			m_bDisplayVertLines,    // vertical gridlines
			m_bDisplayHorzLines,    // horinzontal gridlines
			m_bMarkRowHeader,       // mark row headers
			m_bMarkColHeader;       // mark column headers

	BOOL    m_bPrinting;

	CString m_sSection;

	// colors
	CStringArray        m_ColorNameArray;
	CDWordArray         m_ColorArray;

	int                 m_nZoom;

	// print settings
	LONG    m_nBottomMargin;
	LONG    m_nLeftMargin;
	LONG    m_nTopMargin;
	LONG    m_nRightMargin;
	GBOOL   m_bCenterHorizontal;
	GBOOL   m_bCenterVertical;
	GBOOL   m_bColHeaders;
	GBOOL   m_bPrintHorzLines;
	GBOOL   m_bRowHeaders;
	GBOOL   m_bPrintVertLines;
	LONG    m_nPageOrder;
	GBOOL   m_bBlackWhite;
	GBOOL   m_bPrintFrame;

	// Header&Footer
	LONG    m_nDistTop;
	LONG    m_nDistBottom;
	LONG    m_nFirstPage;

	CGXData    m_mapDataFooter;
	CGXData    m_mapDataHeader;

	WORD m_gxnPropTextHeadline;
	WORD m_gxnPropTextFootnote;

	// custom page breaks
	CDWordArray m_awColBreaks;
	CDWordArray m_awRowBreaks;

public:
	// access member functions
	void SetMarkRowHeader(BOOL b);
	BOOL GetMarkRowHeader() const;

	void SetMarkColHeader(BOOL b);
	BOOL GetMarkColHeader() const;

	void SetDisplayHorzLines(BOOL b);
	BOOL GetDisplayHorzLines() const;

	void SetDisplayVertLines(BOOL b);
	BOOL GetDisplayVertLines() const;

	void SetDisplay3dButtons(BOOL b);
	BOOL GetDisplay3dButtons() const;

	void SetLastZoom(int nZoom);
	int GetLastZoom() const;

	// Prrinting support
	BOOL GetBlackWhite() const;
	BOOL GetDisplayColHeaders() const;
	BOOL GetDisplayRowHeaders() const;

	BOOL    GetCenterHorizontal();
	BOOL    GetCenterVertical();
	BOOL    GetPrintRowHeaders();
	BOOL    GetPrintColHeaders();
	BOOL    GetPrintFrame();
	BOOL    GetPrintHorzLines();
	BOOL    GetPrintVertLines();
	BOOL    GetPrintBlackWhite();
	int     GetPageOrder();

	void    SetPrintHorzLines(BOOL b);
	void    SetPrintVertLines(BOOL b);
	void    SetCenterHorizontal(BOOL b);
	void    SetCenterVertical(BOOL b);
	void    SetBlackWhite(BOOL b);
	void    SetPrintRowHeaders(BOOL b);
	void    SetPrintColHeaders(BOOL b);
	void    SetPageOrder(int n);
	void    SetPrintFrame(BOOL b);

	void    GetMargins(int& top, int& left, int& bottom, int& right);
	void    SetMargins(int top, int left, int bottom, int right);

	CGXData& GetDataHeader();
	CGXData& GetDataFooter();

	CDWordArray& GetColBreakArray();
	CDWordArray& GetRowBreakArray();

	friend class CGXGridParamCopyOperatorImp;
};

/////////////////////////////////////////////////////////////////////////////
// class CGXGridParam

CObject* AFXAPI GXCreateObjectFromFile(CFile& file, CRuntimeClass* pRuntimeClass);
CObject* AFXAPI GXCreateObjectFromFile(LPCTSTR lpszFileName, CRuntimeClass* pRuntimeClass);
CObject* AFXAPI GXCreateObjectFromResource(LPCTSTR lpszResourceName, LPCTSTR lpszType, CRuntimeClass* pRuntimeClass);

class CGXCoveredCellPool;
class CGXGridDropTarget;

// This local version of CByteArray is required to workaround a bug in 
// the CByteArray::Serialize() implementation found in the IA64 SDK
// and MFC 7.0
#if defined(_WIN64) || _MFC_VER >= 0x0700

class CByteArray64 :  public CByteArray
{
public:
	CByteArray64();
	virtual ~CByteArray64();

	// This will hide the base class Serialize() function
	void Serialize(CArchive &ar);
};
#else //defined(_WIN64) || _MFC_VER >= 0x0700
#define CByteArray64 CByteArray
#endif	

class CGXGridParam : public CObject
{
	DECLARE_SERIAL(CGXGridParam)

// Constructor
public:
	CGXGridParam();

	// Support for loading/storing layout
	static CGXGridParam* AFXAPI CreateFromFile(LPCTSTR lpszFileName);
	static CGXGridParam* AFXAPI CreateFromResource(LPCTSTR lpszResourceName);
	static CGXGridParam* AFXAPI CreateFromResource(UINT nId);
	void WriteToFile(LPCTSTR lpszFileName) const;

	static void AFXAPI ImplementSerialize();
	static void AFXAPI ImplementCopyOperator();

	CGXAppData* m_pAppData;

// Objects
public:
	CGXProperties* GetProperties();
	void    SetProperties(CGXProperties* pProperties, BOOL bMustDelete = TRUE);

	CGXData* GetData();
	void    SetData(CGXData* p, BOOL bMustDelete = TRUE);

	CGXStylesMap* GetStylesMap();
	void    SetStylesMap(CGXStylesMap* p, BOOL bMustDelete = TRUE);

	CGXPrintDevice* GetPrintDevice();
	void    SetPrintDevice(CGXPrintDevice* pPD, BOOL bMustDelete = TRUE);

	CGXRangeList* GetRangeList();
	CGXRangeList* GetCoveredCellsList();
	void UpdateCoveredCellsList();

	CObList& GetUndoList();
	CObList& GetRedoList();
	void     EmptyUndoList();
	void     EmptyRedoList();

	void     InitCoveredCells();

// Attributes
public:
// Enable/Disable specific features
	void EnableThumbTrack(BOOL b);
	void EnableSelection(UINT wFlags = GX_SELFULL);
	void EnableMoveCols(BOOL b = TRUE);
	void EnableMoveRows(BOOL b = TRUE);
	void EnableTrackRowHeight(UINT wFlags = GX_TRACK_DEFAULT);
	void EnableTrackColWidth(UINT wFlags = GX_TRACK_DEFAULT);
	void EnableAllFeatures(BOOL b = TRUE);
	void SetSpecialMode(WORD wFlags);

	BOOL IsEnableThumbTrack();
	BOOL IsEnableSelection(WORD wFlags);
	BOOL IsEnableMoveCols();
	BOOL IsEnableMoveRows();
	BOOL IsEnableTrackRowHeight(WORD wFlags = GX_TRACK_INDIVIDUAL | GX_TRACK_ALL);
	BOOL IsEnableTrackColWidth(WORD wFlags = GX_TRACK_INDIVIDUAL | GX_TRACK_ALL);
	BOOL IsSpecialMode(WORD wFlags);

	void EnableUndo(BOOL bEnable = TRUE);
	BOOL IsEnableUndo();

	void EnableChangeTab(BOOL b);
	BOOL IsEnableChangeTab();

	void SetNumberedRowHeaders(BOOL b);
	void SetNumberedColHeaders(BOOL b);
	BOOL IsNumberedRowHeaders();
	BOOL IsNumberedColHeaders();

	void SetDefaultComboBoxHeight(int nHeight);
	int GetDefaultComboBoxHeight();

	void SetEatFirstMouseClick(BOOL b);
	BOOL IsEatFirstMouseClick();

	void SetTransparentBackground(BOOL b);
	BOOL IsTransparentBackground();

	void SetRemoveRowsFlags(WORD wFlags);
	void SetRemoveColsFlags(WORD wFlags);
	WORD GetRemoveRowsFlags();
	WORD GetRemoveColsFlags();

	void SetMinTrackRowHeight(int nHeight);
	void SetMinTrackColWidth(int nWidth);
	int GetMinTrackRowHeight();
	int GetMinTrackColWidth();

	void SetActivateCellFlags(WORD wFlags);
	WORD GetActivateCellFlags();

	void SetSmartResize(BOOL b);
	BOOL IsSmartResize();

	void SetLockReadOnly(BOOL b);
	BOOL IsLockReadOnly();

	void SetDrawOrder(WORD w);
	WORD GetDrawOrder();

	void SetHideCurrentCell(WORD nSetting);
	WORD GetHideCurrentCell();

	const CString& GetSheetName();
	void SetSheetName(LPCTSTR szName);

	void SetScrollLikeExcel(BOOL b);
	BOOL IsScrollLikeExcel();

	void SetSyncCurrentCell(BOOL b);
	BOOL IsSyncCurrentCell();

	void SetDrawWYSIWYG(BOOL b);
	BOOL IsDrawWYSIWYG();

	void SetEnterKeyAction(WORD nAction); // 0 for simply storing current cells value
	WORD GetEnterKeyAction();

	void SetUndoLimit(DWORD nMaxUndoOp);
	DWORD GetUndoLimit();

	void SetGridLineStyle(UINT nStyle);
	UINT GetGridLineStyle() const;

	void SetNewGridLineMode(BOOL b);
	BOOL GetNewGridLineMode();

	void SetExcelLikeCurrentCell(BOOL b);
	BOOL GetExcelLikeCurrentCell();

	void SetExcelLikeHeaders(BOOL b);
	BOOL GetExcelLikeHeaders();

	void SetExcelLikeSelectionFrame(BOOL b);
	BOOL GetExcelLikeSelectionFrame();

	void SetExcelLikeFillFlags(DWORD dw);
	DWORD GetExcelLikeFillFlags() const;

	void SetSortColsOnDblClk(BOOL b);
	BOOL GetSortColsOnDblClk();

	void SetSortRowsOnDblClk(BOOL b);
	BOOL GetSortRowsOnDblClk();

	BOOL IsInit() const;

	CGXGridCore* Grid() const;

// Attributes
public:
	// If you do not have row or column headers in the form 1, 2, 3, ... or A, B, C, ...
	// set the following parameters FALSE. This avoids refreshing all headers when
	// you do insert, move or remove rows or columns.
	BOOL                m_bNumberedRowHeaders;
	BOOL                m_bNumberedColHeaders;

	int                 m_nDefaultComboBoxHeight;

	BOOL                m_bEatFirstMouseClick;

	BOOL                m_bTransparentBackground;

	WORD                m_nRemoveRowsFlags,
						m_nRemoveColsFlags;

	int                 m_nMinTrackRowHeight,
						m_nMinTrackColWidth;

	WORD                m_wActivateCell;

	WORD                m_wAllowSelection;           // Selection of cells

	BOOL                m_bAllowSelDragCols,         // dragging columns
						m_bAllowSelDragRows;         // dragging rows

	WORD                m_wAllowTrackRowHeight,      // tracking row heights
						m_wAllowTrackColWidth;       // tracking column withs

	WORD                m_nSpecialMode;              // use as listbox

	BOOL                m_bThumbTrack;

	BOOL                m_bLockReadOnly;
			// if FALSE, the grid will not take care on read-only state
			// if TRUE, read-only cells are protected.

	BOOL                m_bSmartResize;

	WORD                m_wFloatCellsMode;
	WORD                m_wMergeCellsMode;

	BOOL                m_bDrawWYSIWYG;             // draw WYSIWIG

	WORD                m_nHideCurrentCell;

	WORD                m_nDrawRowOrder;

	ROWCOL              m_nHeaderRows,
						m_nHeaderCols;

	BOOL                m_bScrollLikeExcel;


	CString             m_sSheetName;           // Sheet name (when used in CGXTabWnd)

	ROWCOL              m_nFrozenRows,          // Frozen Rows
						m_nFrozenCols;          // Frozen Cols

	ROWCOL              m_nUndoFreezeFromCol,   // additional information
						m_nUndoFreezeToCol,     // for "Unfreeze" columns
						m_nUndoFreezeDestCol;

	ROWCOL              m_nUndoFreezeFromRow,   // additional information
						m_nUndoFreezeToRow,     // for "Unfreeze" rows
						m_nUndoFreezeDestRow;

	BOOL                m_bSyncCurrentCell;     // Synchronize current cell
	ROWCOL              m_nLastSyncEditRow,     // among several views
						m_nLastSyncEditCol;

	DWORD               m_dwUndoLimit;
	WORD                m_nEnterKeyAction;

	// Marked Cells
	CGXRangeList        m_SelRects;

	// Covered Cells
	CGXRangeList        m_CoveredCellsList;
	CGXCoveredCellPool*	m_pCoveredCells;

	// Floated Cells
	CGXSpanCellPool*    m_pDispFloatCells;
	CGXDelayedRangePool* m_pDelayedDispFloatCells;

	CGXSpanCellPool*    m_pPrintFloatCells;       // backup state while printing
	CGXDelayedRangePool* m_pDelayedPrintFloatCells;   // backup state while printing

	// Merged Cells
	CGXSpanCellPool*    m_pHorzMergeCells;
	CGXSpanCellPool*    m_pVertMergeCells;
	CGXDelayedRangePool* m_pDelayedMergeCells;

	// Property-Object
	BOOL                m_bOwnProperties;
	CGXProperties*      m_pProperties;

	// Styles Map
	BOOL                m_bOwnStylesMap;
	CGXStylesMap*       m_pStylesMap;

	// pointer to an optional Data-Object
	BOOL                m_bOwnData;
	CGXData*            m_pData;

	// Pointer to an optional PrintDevice-Object
	BOOL                m_bOwnPD;
	CGXPrintDevice*     m_pPD;

	BOOL                m_bReadOnly;

	BOOL                m_bNeedChangeTab;            // Enable or disable changing the worksheet-name

	// Undo, Redo, Transactions
	CObList             m_UndoList;
	CObList             m_RedoList;
	int                 m_nTrans;
	BOOL                m_bUndoEnabled;

	// Row Heights, Column Widths
	CByteArray64        m_abRowHidden,
						m_abColHidden;
	CGXMapDWordToLong   m_RowHeights,
						m_ColWidths;
	LONG                m_nDefaultHeight,
						m_nDefaultWidth;

	BOOL                m_bUpdateLocked; // see CGXGridCore::LockUpdate

	BOOL                m_bNewGridLineMode;
	WORD                m_nGridLineStyle; // dotted or regular grid lines

	BOOL                m_bExcelLikeCurrentCell,
						m_bExcelLikeSelectionFrame;

	BOOL                m_bExcelLikeHeaders;

	DWORD				m_nExcelLikeFillFlags;	// Excel like fill flags...

	BOOL                m_bSortColsOnDblClk,
						m_bSortRowsOnDblClk;

	ROWCOL				m_nLastSortedRow,	// remember last sorted row
						m_nLastSortedCol;

	BOOL				m_bSortAscending;	// remember if last sort was ascending or descending

	BOOL                m_bIsInit;      // TRUE when one-time initialization is done

public:
	// Temporary attributes for drag&drop
	BOOL    m_bDndSource;
	ROWCOL  m_nDndStartRow,
			m_nDndStartCol;
	CGXRangeList* m_pDndSelList;
	ROWCOL  m_nDndForceDropCol,
			m_nDndForceDropRow;
	ROWCOL  m_nDndRowOffset,
			m_nDndColOffset;
	BOOL   m_bDndCurrentCellText;       // TRUE if selected text from current cell is dragged
	CGXControl* m_pDndCurrentCellControl;

	// Copy,Cut/Paste
	BOOL	m_bDirectCopyPaste;
	BOOL	m_bDirectCutPaste;
	BOOL	m_bDirectDragDrop;

	BOOL	m_bCut;
	CGXRangeList m_CopyRangeList;

	// Display expressions in active/inactive cells
	WORD	m_nDisplayExpression;	// GX_EXPR_DISPLAYACTIVE, GX_EXPR_DISPLAYALWAYS

	// Cell depencies - updated cells:
	CGXRangeList m_UpdatedRangeList;

	// Tabbed comboboxes (old-fashioned way)
	CPtrArray m_ArrayOfMapValueToChoice;
	CPtrArray m_ArrayOfMapTextToChoice;
	LONG m_nSerial;

	// map with more objects that can be linked into parameter object
	CMapPtrToPtr m_mapParamLocalData;

// Implementation
public:
	virtual ~CGXGridParam();
	virtual void Serialize(CArchive& ar);
	virtual CGXGridParam& operator=(const CGXGridParam& p);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

// Parameter object local data

#define GX_PARAM_LOCAL(class_name, ident_name) \
	class_name* ident_name(CGXGridParam* pParam) { \
			void* voidptr; \
			class_name* pData; \
			if (!pParam->m_mapParamLocalData.Lookup(this, pData)) \
				pParam->m_mapParamLocalData.SetAt(this, pData = new class_name); \
			return pData; \
		} \

#define GX_EXTERN_PARAM_LOCAL(class_name, ident_name) \
	extern class_name* ident_name;

/////////////////////////////////////////////////////////////////////////////
// class CGXGridCore

class CGXTabWnd;
class CGXRecordInfoWnd;
class CGXDragLineWnd;
class CGXFormulaSheet;
class CGXLongOperation;
class CGXPlugInComponent;

class CGXGridCore
{
public:
// Construction, Destruction
	CGXGridCore(CWnd* pGridWnd = NULL, CDocument* pGridDoc = NULL, BOOL bIsViewContext = FALSE);
	virtual ~CGXGridCore();

public:
	// Components that are implemented in concrete classes 
	// derived from abstract base classes. The concrete implementation
	// is only necessary to be linked into an .exe if its functionality
	// is needed.

	void* begin_component_ptr;

	void ImplementPrinting();
	CGXAbstractGridPrintImp* m_pPrintImp;
	friend class CGXGridPrintImp;
	
	void ImplementGridSort();
	CGXAbstractGridSortImp* m_pSortImp;
	friend class CGXGridSortImp;
	
	void ImplementOldDrawing();
	CGXAbstractGridOldDrawingImp* m_pOldDrawingImp;
	friend class CGXGridOldDrawingImp;
	
	void ImplementCoveredCells();
	CGXAbstractGridCoveredCellsImp* m_pCoveredCellsImp;
	friend class CGXGridCoveredCellsImp;
	
	void ImplementDrawSpannedCells();
	CGXAbstractDrawSpannedCellsImp* m_pDrawSpannedCellsImp;
	friend class CGXDrawSpannedCellsImp;
	
	void ImplementFloatCells();
	CGXAbstractGridFloatCellsImp* m_pFloatCellsImp;
	friend class CGXGridFloatCellsImp;
	
	void ImplementMergeCells();
	CGXAbstractGridMergeCellsImp* m_pMergeCellsImp;
	friend class CGXGridMergeCellsImp;
	
	void ImplementUndoRedo();
	CGXAbstractCommandFactory* m_pUndoImp;
	friend class CGXCommandFactory;
	
	void ImplementCalcSize();
	CGXAbstractCalcSizeImp* m_pAbstractCalcSizeImp;
	friend class CGXCalcSizeImp;

	void ImplementUpdateHint();
	CGXAbstractGridUpdateHintImp* m_pUpdateHintImp;
	friend class CGXGridUpdateHintImp;

	void ImplementResizeToFit();
	CGXAbstractGridResizeToFitImp* m_pResizeToFitImp;
	friend class CGXGridResizeToFitImp;
	
	void ImplementHideCells();
	CGXAbstractGridHideCellsImp* m_pHideCellsImp;
	friend class CGXGridHideCellsImp;
	
	void ImplementFindReplace();
	CGXAbstractGridFindReplaceImp* m_pFindReplaceImp;
	friend class CGXGridFindReplaceImp;
	
	void ImplementUserSelectRange();
	CGXAbstractGridUserSelectRangeImp* m_pUserSelectRangeImp;
	friend class CGXGridUserSelectRangeImp;
	
	void ImplementExcelLikeFrame();
	CGXAbstractGridExcelLikeFrameImp* m_pExcelLikeFrameImp;
	friend class CGXGridExcelLikeFrameImp;
	
	void ImplementExcelLikeFill();
	void SetExcelLikeFillImp(CGXAbstractGridExcelLikeFillImp* pGridExcelLikeFillImp, BOOL bDelete = TRUE);
	CGXAbstractGridExcelLikeFillImp* m_pExcelLikeFillImp;
	friend class CGXGridExcelLikeFillImp;
	
	void ImplementUserDragSelectRange();
	CGXAbstractGridUserDragSelectRangeImp* m_pUserDragSelectRangeImp;
	friend class CGXGridUserDragSelectRangeImp;
	
	void ImplementMoveRowsCols();
	friend class CGXGridMoveRowsColsImp;
	CGXAbstractGridMoveRowsColsImp* m_pMoveRowsColsImp;
	
	void ImplementUserResizeCells();
	friend class CGXGridUserResizeCellsImp;
	CGXAbstractGridUserResizeCellsImp* m_pUserResizeCellsImp;
	
	void ImplementOptimizedUpdate();
	CGXAbstractGridOptimizedUpdateImp* m_pOptimizedUpdateImp;
	friend class CGXGridOptimizedUpdateImp;
	
	void ImplementMarkEditHeader();
	CGXAbstractGridMarkEditHeaderImp* m_pMarkEditHeaderImp;
	friend class CGXGridMarkEditHeaderImp;
	
	void ImplementFreezeMenuHelper();
	CGXAbstractGridFreezeMenuHelperImp* m_pFreezeMenuImp;
	friend class CGXGridFreezeMenuHelperImp;
	
	void ImplementDirectCopyMoveCells();
	CGXAbstractGridDirectCopyMoveCellsImp* m_pDirectCopyMoveCellsImp;
	friend class CGXGridDirectCopyMoveCellsImp;
	
	void ImplementTextDataExchange();
	CGXAbstractGridTextDataExchangeImp* m_pTextDataExchangeImp;
	friend class CGXGridTextDataExchangeImp;
	
	void ImplementStyleDataExchange();
	CGXAbstractGridStyleDataExchangeImp* m_pStyleDataExchangeImp;
	friend class CGXGridStyleDataExchangeImp;
	
	void ImplementCutPaste();
	CGXAbstractGridCutPasteImp* m_pCutPasteImp;
	friend class CGXGridCutPasteImp;
	
	void ImplementClearCells();
	CGXAbstractGridClearCellsImp* m_pClearCellsImp;
	friend class CGXGridClearCellsImp;
	
	void ImplementRangeName();
	CGXAbstractGridRangeNameImp* m_pRangeNameImp;
	friend class CGXGridRangeNameImp;
	
	CGXAbstractGridDropTargetImp* m_pOleDropTargetImp;
	friend class CGXGridDropTargetPlugin;

	CGXNoOleDataSourceProxy* m_pOleDataSourceProxy;
	friend class CGXOleDataSourceProxy;

	// locale numbers
	void EnableLocaleNumbers();

	// cell tips
	void EnableCellTips(CRuntimeClass* pCellTipWndFactory = NULL, BOOL bShowHeaders = FALSE, 
						BOOL bShowActive = FALSE, UINT nDelay = 500);
	CGXPluginComponent* m_pCellTipPlugin;
	
	// Plugins
	void EnableMouseWheel();    // Support for WM_MOUSEWHEEL message
	void EnableIntelliMouse();  // Advanced Intelli-mouse support with Internet Explorer-like 
								// panning and scrolling

	CGXPluginComponent* m_pImousePlugin;		// Make sure only one of the two above gets called.
	
	void EnableScrollTips();
	CGXPluginComponent* m_pScrollTipPlugin;		

	void ImplementAutoScroll();
	friend class CGXAutoScrollPlugin;
	CGXPluginComponent* m_pAutoScrollPlugin;		

	void* end_component_ptr;

	// Tooltips, Formula Engine, Ole Dnd see below
	void ImplementToolTips();
	
	void AutoDeletePtr(void* p);
	CPtrList m_autodeleteptrlist;

	CGXAppData* m_pAppData;

// Initialization, Client Area and Parameter Object
public:
	// Client Area
	CRect GetGridRect();
	void  SetGridRect(BOOL bSet, LPRECT rect = NULL);

	// Parameter object
	CGXGridParam* GetParam();
	void SetParam(CGXGridParam* pParam, BOOL bMustDelete = TRUE);

	// Printing mode
	BOOL IsPrinting();
	virtual void SetPrinting(BOOL b, BOOL bClientToRect = FALSE);

// Update, Hints, Initialization
public:
	void EnableHints(BOOL b = TRUE);
	virtual void SetModifiedFlag(BOOL bModified = TRUE);
	CDocument* GetGridDoc();

	void SetViewID(int nID);
	int GetViewID();

	void SetGridWnd(CWnd* pGridWnd, CDocument* pGridDoc = NULL, BOOL bIsViewContext = FALSE);
	CWnd* GridWnd();

public:
	virtual void OnGridPrepareDC(CDC* pDC, CPrintInfo*  pInfo = NULL );
	virtual void UpdateAllViews(CWnd* pSender, LPARAM lHint, CObject* pHint);

protected:
	virtual void OnGridInitialUpdate();
	virtual BOOL OnActivateGrid( BOOL bActivate ); // called by OnActivateView

	virtual void OnGridUpdate(CView* pSender, LPARAM lHint, CObject* pHint);

public:
// data members
	CWnd*   m_pGridWnd;     // this a main anchor for multiple inheritance
							// m_pGridWnd points to CGXGridView or CGridControl

	CDocument* m_pGridDoc; // pointer to the document (or NULL)

	BOOL    m_bIsViewContext;   // TRUE if the grid is used in a CView

protected:
	BOOL    m_bHintsEnabled;
	int     m_nViewID;
	int     m_nPrintHandleRecordCount;

// Cell Formatting
public:
	virtual BOOL SetStyleRange(const CGXRange& range, const CGXStyle* pStyle, GXModifyType mt, int nType = 0, const CObArray* pCellsArray = NULL, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);
			BOOL SetStyleRange(const CGXRange& range, const CGXStyle& style, GXModifyType mt = gxOverride, int nType = 0, UINT flags = GX_UPDATENOW);
	virtual BOOL GetStyleRowCol(ROWCOL nRow, ROWCOL nCol, CGXStyle& style, GXModifyType mt = gxCopy, int nType = 0);

	BOOL SetValueRange(const CGXRange& range, const CString& s, GXModifyType mt = gxOverride, int nType = 0, UINT flags = GX_UPDATENOW);
	BOOL SetValueRange(const CGXRange& range, LPCTSTR lpsz, GXModifyType mt = gxOverride, int nType = 0, UINT flags = GX_UPDATENOW);
#ifdef _UNICODE
	BOOL SetValueRange(const CGXRange& range, const char* lpsz, GXModifyType mt = gxOverride, int nType = 0, UINT flags = GX_UPDATENOW);
#endif
	BOOL SetValueRange(const CGXRange& range, DWORD dw, GXModifyType mt = gxOverride, int nType = 0, UINT flags = GX_UPDATENOW);
	BOOL SetValueRange(const CGXRange& range, WORD w, GXModifyType mt = gxOverride, int nType = 0, UINT flags = GX_UPDATENOW);
	BOOL SetValueRange(const CGXRange& range, short s, GXModifyType mt = gxOverride, int nType = 0, UINT flags = GX_UPDATENOW);
	BOOL SetValueRange(const CGXRange& range, LONG l, GXModifyType mt = gxOverride, int nType = 0, UINT flags = GX_UPDATENOW);
	BOOL SetValueRange(const CGXRange& range, float f, GXModifyType mt = gxOverride, int nType = 0, UINT flags = GX_UPDATENOW);
	BOOL SetValueRange(const CGXRange& range, double d, GXModifyType mt = gxOverride, int nType = 0, UINT flags = GX_UPDATENOW);

	// SetExpressionRowCol allows you to specify expression (number, value, date, formula) for a cell
	// The value will be parsed and correct cell format, formula stored (Formula Engine support must be enabled).
	BOOL SetExpressionRowCol(ROWCOL nRow, ROWCOL nCol, const CString& s, UINT flags = GX_UPDATENOW);
	const CString& GetExpressionRowCol(ROWCOL nRow, ROWCOL nCol);

	virtual CObArray* GetStyleArray(const CGXRange& range, int nType, CGXLongOperation* pTheOp);

	const CString& GetValueRowCol(ROWCOL nRow, ROWCOL nCol);

	BOOL GetColStyle(ROWCOL nCol, CGXStyle& style, GXModifyType mt = gxCopy);
	BOOL GetRowStyle(ROWCOL nRow, CGXStyle& style, GXModifyType mt = gxCopy);
	BOOL GetTableStyle(CGXStyle& style, GXModifyType mt = gxCopy);

	// Note: LookupStyle returns reference to temporary style-object. See class-reference.
	virtual const CGXStyle& LookupStyleRowCol(ROWCOL nRow, ROWCOL nCol);

	virtual void ComposeStyleRowCol(ROWCOL nRow, ROWCOL nCol, CGXStyle* pStyle, BOOL bApplyStandard = TRUE);

	virtual BOOL StoreStyleRowCol(ROWCOL nRow, ROWCOL nCol, const CGXStyle* pStyle, GXModifyType mt = gxOverride, int nType = 0);
	virtual void UpdateStyleRange(const CGXRange &range, const CGXStyle* pStyle = NULL, GXModifyType mt = gxOverride, int nType = 0, UINT flags = GX_INVALIDATE, BOOL bCreateHint = TRUE);

	virtual CGXStyle* CreateStyle();
	virtual void RecycleStyle(CGXStyle* pStyle);

	// Changing the styles map (with undo/redo support)
	virtual BOOL ChangeStylesMap(const CGXStylesMap& stylesMap, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);
	virtual void UpdateStylesMap(UINT flags, BOOL bCreateHint = TRUE);

	// Changing the proprties (with undo/redo support)
	virtual BOOL ChangeProperties(const CGXProperties& properties, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);
	virtual void UpdateProperties(UINT flags, BOOL bCreateHint = TRUE);

	// Changing the base style setting (with undo/redo support)
	BOOL ChangeStandardStyle(const CGXStyle& style, GXModifyType mt = gxOverride, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);
	BOOL ChangeRowHeaderStyle(const CGXStyle& style, GXModifyType mt = gxOverride, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);
	BOOL ChangeColHeaderStyle(const CGXStyle& style, GXModifyType mt = gxOverride, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);
		// all above call ChangeBaseStyle

	virtual BOOL ChangeBaseStyle(WORD wStyleID, const CGXStyle& style, GXModifyType mt = gxOverride, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);
	virtual void UpdateBaseStyle(WORD wStyleId, UINT flags, BOOL bCreateHint = TRUE);

	// Some useful shortcuts for the standard-styles 
	// (but better use ChangeBaseStyle to change base styles)
	CGXStyle& StandardStyle();
	CGXStyle& RowHeaderStyle();
	CGXStyle& ColHeaderStyle();
	CGXStyle& BaseStyle(WORD wStyleID);

	void UpdateFontMetrics();
		// call this method to update internal font metrics
		// after changing the font for the StandardStyle .

protected:
	CPtrList m_StyleBuffer;
	CGXStyle* m_pStyleValue;
	CGXStyle* m_pStyleGetValue;
	CRuntimeClass* m_pStyleClass;
	const CGXStyle* m_pOldStyle;
	CGXPen m_tempPen;

public:
	BOOL m_bOnlyValueNeeded;
	BOOL m_bNoValueNeeded;

// Cell coordinates
public:
	// Number of Rows and Colums

	// be careful: SetRowCount calls InsertRows and RemoveRows
	virtual BOOL SetRowCount(ROWCOL nRows, UINT flags = GX_UPDATENOW);
	// be careful: SetColCount calls InsertCols and RemoveCols
	virtual BOOL SetColCount(ROWCOL nCols, UINT flags = GX_UPDATENOW);

	virtual ROWCOL GetRowCount();
	virtual ROWCOL GetColCount();

protected:
	virtual BOOL StoreRowCount(ROWCOL nRows);
	virtual BOOL StoreColCount(ROWCOL nCols);
	virtual void UpdateChangedRowCount(ROWCOL nOldRows, UINT flags, BOOL bCreateHint = FALSE);
	virtual void UpdateChangedColCount(ROWCOL nOldCols, UINT flags, BOOL bCreateHint = FALSE);

	// Insert, Remove and Move Cells
public:
	virtual BOOL RemoveRows(ROWCOL nFromRow, ROWCOL nToRow, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);
	virtual BOOL RemoveCols(ROWCOL nFromCol, ROWCOL nToCol, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);
	virtual BOOL MoveRows(ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);
	virtual BOOL MoveCols(ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nDestCol, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);
	virtual BOOL InsertRows(ROWCOL nRow, ROWCOL nCount, int* anHeightArray = NULL, CObArray* pCellsArray = NULL, CObArray* pRowsArray = NULL, ROWCOL nColCount = 0, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);
	virtual BOOL InsertCols(ROWCOL nCol, ROWCOL nCount, int* anWidthArray = NULL, CObArray* pCellsArray = NULL, CObArray* pColsArray = NULL, ROWCOL nRowCount = 0, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);

protected:
	virtual BOOL StoreInsertRows(ROWCOL nRow, ROWCOL nCount, BOOL bProcessed = FALSE);
	virtual BOOL StoreInsertCols(ROWCOL nCol, ROWCOL nCount, BOOL bProcessed = FALSE);
	virtual BOOL StoreRemoveRows(ROWCOL nFromRow, ROWCOL nToRow, BOOL bProcessed = FALSE);
	virtual BOOL StoreRemoveCols(ROWCOL nFromCol, ROWCOL nToCol, BOOL bProcessed = FALSE);
	virtual BOOL StoreMoveRows(ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow, BOOL bProcessed = FALSE);
	virtual BOOL StoreMoveCols(ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nDestCol, BOOL bProcessed = FALSE);

	virtual void UpdateInsertRows(ROWCOL nRow, ROWCOL nCount, UINT flags, BOOL bCreateHint = FALSE);
	virtual void UpdateInsertCols(ROWCOL nCol, ROWCOL nCount, UINT flags, BOOL bCreateHint = FALSE);
	virtual void UpdateRemoveRows(ROWCOL nFromRow, ROWCOL nToRow, int* anOldHeights, UINT flags, BOOL bCreateHint = FALSE);
	virtual void UpdateRemoveCols(ROWCOL nFromCol, ROWCOL nToCol, int* anOldWidths, UINT flags, BOOL bCreateHint = FALSE);
	virtual void UpdateMoveRows(ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow, UINT flags, BOOL bCreateHint = FALSE);
	virtual void UpdateMoveCols(ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nDestCol, UINT flags, BOOL bCreateHint = FALSE);

	// Frozen Rows and Columns
public:
	virtual BOOL SetFrozenRows(ROWCOL nFrozenRows, ROWCOL nHeaderRows = 0, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);
	virtual BOOL SetFrozenCols(ROWCOL nFrozenCols, ROWCOL nHeaderCols = 0, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);
	virtual ROWCOL GetFrozenRows();
	virtual ROWCOL GetFrozenCols();
	virtual ROWCOL GetHeaderRows();
	virtual ROWCOL GetHeaderCols();
	BOOL IsFrozenRow(ROWCOL nRow);
	BOOL IsFrozenCol(ROWCOL nCol);

protected:
	virtual BOOL StoreFrozenRows(ROWCOL nFrozenRows, ROWCOL nHeaderRows);
	virtual BOOL StoreFrozenCols(ROWCOL nFrozenCols, ROWCOL nHeaderCols);
	virtual void UpdateFrozenRows(ROWCOL nOldFrozenRows, ROWCOL nOldHeaderRows, UINT flags, BOOL bCreateHint = FALSE);
	virtual void UpdateFrozenCols(ROWCOL nOldFrozenCols, ROWCOL nOldHeaderCols, UINT flags, BOOL bCreateHint = FALSE);

	// Sorting the grid
public:
	// Rows
	virtual void SortRows(CGXRange sortRange, CGXSortInfoArray& sortInfo, UINT flags = GX_UPDATENOW);
	virtual BOOL MoveDataRows(const CGXRange& sortRange, const CRowColArray& awRowIndex, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);
	virtual BOOL StoreMoveDataRows(const CGXRange& sortRange, const CRowColArray& awRowIndex);
	virtual void UpdateMoveDataRows(const CGXRange& sortRange, UINT flags = GX_UPDATENOW, BOOL bCreateHint =TRUE);
	virtual void OnGetSortRowsKey(ROWCOL nRow, const CGXSortInfoArray& sortInfo, CStringArray& keys);

	// Columns
	virtual void SortCols(CGXRange sortRange, CGXSortInfoArray& sortInfo, UINT flags = GX_UPDATENOW);
	virtual BOOL MoveDataCols(const CGXRange& sortRange, const CRowColArray& awColIndex, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);
	virtual BOOL StoreMoveDataCols(const CGXRange& sortRange, const CRowColArray& awColIndex);
	virtual void UpdateMoveDataCols(const CGXRange& sortRange, UINT flags = GX_UPDATENOW, BOOL bCreateHint =TRUE);
	virtual void OnGetSortColsKey(ROWCOL nCol, const CGXSortInfoArray& sortInfo, CStringArray& keys);

	// General
	virtual void SortKeys(const CGXSortInfoArray& sortInfo, CPtrArray& sortKeyArray);
	virtual void GetSortKey(CGXControl* pControl, ROWCOL nRow, ROWCOL nCol, const CGXSortInfo& sortInfo, const CGXStyle& style, CString& sKey);

	// Used within a cell control to control whether grid can scroll
public: 
	virtual BOOL SetScrollLockedFromCell(BOOL b = TRUE);
	virtual BOOL IsScrollLockedFromCell();
protected:
	BOOL m_bScrollLockedFromCell;

	// Current view
public:
	virtual void SetTopRow(ROWCOL nRow, UINT flags = GX_UPDATENOW, BOOL bCreateHint = TRUE);
	virtual void SetLeftCol(ROWCOL nCol, UINT flags = GX_UPDATENOW, BOOL bCreateHint = TRUE);
	void SetTopLeftRowCol(ROWCOL nRow, ROWCOL nCol, UINT flags = GX_UPDATENOW);

	ROWCOL GetTopRow();
	ROWCOL GetLeftCol();
	void GetTopLeftRowCol(ROWCOL* nRow, ROWCOL* nCol);

	ROWCOL GetClientRow(ROWCOL nRow);
	ROWCOL GetClientCol(ROWCOL nCol);
	ROWCOL GetRow(ROWCOL nClientRow);
	ROWCOL GetCol(ROWCOL nClientCol);

	BOOL IsDragSelection(int* pnSelDragMode = NULL);

protected:
	// User is dragging rows or columns
	virtual BOOL OnSelDragStart(ROWCOL nRow, ROWCOL nCol);
	virtual BOOL OnSelDragMove(ROWCOL nStartRow, ROWCOL nStartCol, ROWCOL nDragRow, ROWCOL nDragCol);
	virtual BOOL OnSelDragDrop(ROWCOL nStartRow, ROWCOL nStartCol, ROWCOL nDragRow, ROWCOL nDragCol);
	virtual void OnSelDragCancel();

	virtual BOOL OnSelDragRowsStart(ROWCOL nFirstRow, ROWCOL nLastRow);
	virtual BOOL OnSelDragColsStart(ROWCOL nFirstCol, ROWCOL nLastCol);
	virtual BOOL OnSelDragRowsMove(ROWCOL nFirstRow, ROWCOL nLastRow, ROWCOL nDestRow);
	virtual BOOL OnSelDragColsMove(ROWCOL nFirstCol, ROWCOL nLastCol, ROWCOL nDestCol);
	virtual BOOL OnSelDragRowsDrop(ROWCOL nFirstRow, ROWCOL nLastRow, ROWCOL nDestRow);
	virtual BOOL OnSelDragColsDrop(ROWCOL nFirstCol, ROWCOL nLastCol, ROWCOL nDestCol);

// Cell Size and Position
// Cell size
public:
	virtual BOOL SetRowHeight(ROWCOL nFromRow, ROWCOL nToRow, int nHeight, int* anHeightArray = NULL, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);
	virtual BOOL SetColWidth(ROWCOL nFromCol, ROWCOL nToCol, int nWidth, int* anWidthArray = NULL, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);
	virtual BOOL SetDefaultRowHeight(int nHeight, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);
	virtual BOOL SetDefaultColWidth(int nWidth, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);

	virtual int  GetRowHeight(ROWCOL nRow);
	virtual int  GetColWidth(ROWCOL nCol);
	virtual int  GetDefaultRowHeight();
	virtual int  GetDefaultColWidth();

	virtual BOOL HideRows(ROWCOL nFromRow, ROWCOL nToRow, BOOL bHide = TRUE, BOOL* abHideArray = NULL, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);
	virtual BOOL HideCols(ROWCOL nFromCol, ROWCOL nToCol, BOOL bHide = TRUE, BOOL* abHideArray = NULL, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);

	virtual BOOL IsRowHidden(ROWCOL nRow);
	virtual BOOL IsColHidden(ROWCOL nCol);

	virtual BOOL ResizeRowHeightsToFit(CGXRange range, BOOL bResizeCoveredCells = TRUE, UINT nFlags = GX_UPDATENOW);
	virtual BOOL ResizeColWidthsToFit(CGXRange range, BOOL bResizeCoveredCells = TRUE, UINT nFlags = GX_UPDATENOW);

	// limit cell size so that it is not larger than the grid area
	BOOL    m_bLimitRowHeight,  // checked in GetRowHeight
			m_bLimitColWidth;   // checked in GetColWidth

protected:
	virtual BOOL StoreHideRow(ROWCOL nRow, BOOL bHide);
	virtual BOOL StoreHideCol(ROWCOL nCol, BOOL bHide);

	virtual BOOL StoreDefaultRowHeight(int nHeight);
	virtual BOOL StoreDefaultColWidth(int nWidth);
	virtual BOOL StoreColWidth(ROWCOL nCol, int nWidth = 0);
	virtual BOOL StoreRowHeight(ROWCOL nRow, int nHeight = 0);

	virtual void UpdateChangedColWidths(ROWCOL nFromCol, ROWCOL nToCol, int* anOldWidths, UINT flags, BOOL bCreateHint = FALSE);
	virtual void UpdateChangedRowHeights(ROWCOL nFromRow, ROWCOL nToRow, int* anOldHeights, UINT flags, BOOL bCreateHint = FALSE);

public:
	// convert Height and Width pixel values to logical values and vice versa
	LONG Height_DPtoLP(int nHeight);
	LONG Width_DPtoLP(int nWidth);
	int Height_LPtoDP(LONG nHeight);
	int Width_LPtoDP(LONG nWidth);
	virtual int GetFontHeight();
	virtual int GetFontWidth();

	// Get Row, Col under point
	virtual int HitTest(CPoint& pt, ROWCOL* Row = NULL, ROWCOL* Col = NULL, CRect* rectHit = NULL);
	virtual int OnExtHitTest(ROWCOL ncRow, ROWCOL ncCol, CPoint& ptTest, CRect& rect);

	// Return row heights and column widths
	void GetArrayWithColWidths(ROWCOL nFromCol, ROWCOL nToCol, int* pArray);
	void GetArrayWithRowHeights(ROWCOL nFromRow, ROWCOL nToRow, int* pArray);

	// Calculations
	int CalcSumOfRowHeights(ROWCOL nFromRow, ROWCOL nToRow, int nAbortAt = 0);
	int CalcSumOfColWidths(ROWCOL nFromCol, ROWCOL nToCol, int nAbortAt = 0);
	int CalcSumOfClientRowHeights(ROWCOL nFromRow, ROWCOL nToRow, int nAbortAt = 0);
	int CalcSumOfClientColWidths(ROWCOL nFromCol, ROWCOL nToCol, int nAbortAt = 0);

	CRect CalcRectFromRowColExEx(ROWCOL nStartRow, ROWCOL nStartCol, ROWCOL nEndRow, ROWCOL nEndCol);
	CRect CalcRectFromRowColEx(ROWCOL nStartRow, ROWCOL nStartCol, ROWCOL nEndRow, ROWCOL nEndCol);
	CRect CalcRectFromRowColExEx(ROWCOL nRow, ROWCOL nCol);
	CRect CalcRectFromRowColEx(ROWCOL nRow, ROWCOL nCol);
	CRect CalcRectFromRowCol(ROWCOL nStartRow, ROWCOL nStartCol, ROWCOL nEndRow, ROWCOL nEndCol, BOOL bOutsideClientArea = FALSE);
	CRect CalcRectFromRowCol(ROWCOL nRow, ROWCOL nCol);

	// Get rows and cols from Points
		// Note: Result can be GX_INVALID
	ROWCOL CalcClientRowFromPt(CPoint& pt, int* yUp = NULL);
	ROWCOL CalcClientColFromPt(CPoint& pt, int* xLeft = NULL);

	// calculate last visible row or column from GridRect()
	ROWCOL CalcRightColFromRect(const CRect& rect);
	ROWCOL CalcBottomRowFromRect(const CRect& rect);
	ROWCOL CalcRightColFromRect(const CRect& rect, BOOL& bLastColVisible);
	ROWCOL CalcBottomRowFromRect(const CRect& rect, BOOL& bLastRowVisible);
	void CalcBottomRightRowColFromRect(const CRect& rect, ROWCOL *nRow, ROWCOL *nCol);

	CRect CalcGridLineRect(int type, ROWCOL nClientRC);

	ROWCOL GetLastVisibleRow(BOOL* pbLastRowVisible = NULL);
	ROWCOL GetLastVisibleCol(BOOL* pbLastColVisible = NULL);

	BOOL IsTracking(int* pnTrackingMode = NULL, ROWCOL* pnTracking = NULL);

protected:
	// Attributes for HitTest
	BOOL   m_bHitTestSelEdge;
	int    m_nHitTestFrame;

	// Tracking
	virtual BOOL OnStartTracking(ROWCOL nRow, ROWCOL nCol, int nTrackingMode);
	virtual void OnMoveTracking(ROWCOL nRow, ROWCOL nCol, int nTrackingMode, CSize& size);
	virtual void OnEndTracking(ROWCOL nRow, ROWCOL nCol, int nTrackingMode, CSize& size);
	virtual void OnCancelTracking();

	virtual BOOL OnTrackColWidth(ROWCOL nCol);  // return FALSE to prevent the display of the column-width cursor
	virtual BOOL OnTrackColWidthStart(ROWCOL nCol);
	virtual BOOL OnTrackColWidthMove(ROWCOL nCol, int nWidth);
	virtual BOOL OnTrackColWidthEnd(ROWCOL nCol, int nWidth);

	virtual BOOL OnTrackRowHeight(ROWCOL nRow); // return FALSE to prevent the display of the row-height cursor
	virtual BOOL OnTrackRowHeightStart(ROWCOL nRow);
	virtual BOOL OnTrackRowHeightMove(ROWCOL nRow, int nHeight);
	virtual BOOL OnTrackRowHeightEnd(ROWCOL nRow, int nHeight);

// Zoom, ReadOnly
public:
	virtual void SetZoom(int nZoom, UINT flags = GX_UPDATENOW);
	virtual void SetReadOnly(BOOL bReadOnly = TRUE);

	virtual int  GetZoom();
	virtual BOOL IsReadOnly();

protected:
	virtual BOOL StoreZoom(int nZoom, BOOL bCreateHint = TRUE);
	virtual BOOL StoreReadOnly(BOOL bReadOnly);

	virtual void UpdateZoom(int nOldZoom, UINT flags, BOOL bCreateHint = FALSE);
	virtual void UpdateReadOnly(BOOL bOldReadOnly, BOOL bCreateHint = FALSE);

	// support for CGXTabWnd, CGXRecordInfoWnd
public:
	CGXTabWnd* GetTabWnd() const;
	CWnd* GetSharedScrollbarParentWnd() const;
	virtual void OnInfoWndMoveRecord(int nDirection, long nRecord);
	virtual BOOL CanActivateGrid(BOOL bActivate);
	virtual BOOL CanChangeTab();
	CGXRecordInfoWnd* GetRecordInfoWnd() const;
	virtual void OnTabChanged(int nTab);

	CString GetTabName();
	void SetTabName(CString s);
	virtual void UpdateRecordInfoWnd();

// Selections and Covered Cells
	// Selected Cells (see also CGXRangeList)
public:
	BOOL GetSelectedCols(CRowColArray& awLeft, CRowColArray& awRight, BOOL bRangeColsOnly = FALSE, BOOL bCanUseCurrentCell = TRUE);
	virtual BOOL GetSelectedRows(CRowColArray& awTop, CRowColArray& awBottom, BOOL bRangeRowsOnly = FALSE, BOOL bCanUseCurrentCell = TRUE);

	ROWCOL GetSelectedCols(CRowColArray& awCols, BOOL bRangeColsOnly = FALSE, BOOL bCanUseCurrentCell = TRUE);
	virtual ROWCOL GetSelectedRows(CRowColArray& awRows, BOOL bRangeRowsOnly = FALSE, BOOL bCanUseCurrentCell = TRUE);

	virtual void SetSelection(POSITION SelRectId, ROWCOL nTop = 0, ROWCOL nLeft = 0, ROWCOL nBottom = 0, ROWCOL nRight = 0);

	virtual BOOL CopyRangeList(CGXRangeList& list, BOOL bEdit);

	BOOL IsSelectingCells();
	WORD GetHitState();

	virtual BOOL GetInvertStateRowCol(ROWCOL nRow, ROWCOL nCol, const CGXRangeList* pSelList);
	virtual void SelectRange(const CGXRange& range, BOOL bSelect = TRUE, BOOL bUpdate = TRUE);

	CGXRange m_rgLastSelectionFrame;
	int m_nLastSelectionFrameMarker;

	void DrawSelectionFrame(CDC* pDC, BOOL bDrawOld = TRUE, const CGXRange* pNewRange = NULL);
	BOOL LockSelectionFrame(BOOL bLock, BOOL bCreateHint = TRUE);
	void ToggleSelectionFrameMarker();

protected:
	void DrawSelectionRangeFrame(CDC* pDC, const CGXRange& rg, int nMarker = 0, BOOL bOnlyMarker = FALSE);
	virtual void DrawInvertFrame(CDC* pDC, const CRect& rc, const CRect& rectClip, BOOL bTopVisible, BOOL bLeftVisible, int nMarker, BOOL bOnlyMarker = FALSE);

	virtual BOOL StoreSelectRange(const CGXRange& range, BOOL bSelect);
	virtual void UpdateSelectRange(const CGXRange& range, const CGXRangeList* pOldRangeList, BOOL bCreateHint);

	// invert cells
	virtual void PrepareChangeSelection(POSITION SelRectId, ROWCOL nTop = 0, ROWCOL nLeft = 0, ROWCOL nBottom = 0, ROWCOL nRight = 0, BOOL bCreateHint = FALSE);
	virtual void PrepareClearSelection(BOOL bCreateHint = FALSE);

	// Events
	virtual BOOL CanChangeSelection(CGXRange* pRange, BOOL bIsDragging, BOOL bKey);
	virtual void OnChangedSelection(const CGXRange* changedRect, BOOL bIsDragging, BOOL bKey);
	virtual BOOL OnStartSelection(ROWCOL nRow, ROWCOL nCol, UINT flags, CPoint point);

// just for compatibility with OG 1.0. It is recommended that
// you override CanChangeSelection instead.
	virtual void PreChangeSelection(CGXRange* pRange, BOOL bIsDragging, BOOL bKey);

	// Attributes
	BOOL m_bLockDrawSelectionFrame;

// Auto Fill
protected:
	virtual BOOL OnStartAutoFillSelection(CGXRange& rgStart, UINT& flags, CPoint& point);
	virtual BOOL CanChangeAutoFillSelection(CGXRange& rgNew, const CGXRange& rgStart);
	virtual void DoAutoFill(CGXRange& rgFinal, CGXRange& rgStart);
	virtual void OnAutoFillDone(CGXRange& rgFinal);

// Covered Cells
public:
	virtual BOOL SetCoveredCellsRowCol(ROWCOL nRow, ROWCOL nCol, ROWCOL nToRow, ROWCOL nToCol, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);
	virtual CGXRange* GetCoveredCellsRowCol(ROWCOL nRow, ROWCOL nCol, CGXRange& range);

protected:
	virtual BOOL StoreCoveredCellsRowCol(ROWCOL nRow, ROWCOL nCol, ROWCOL nToRow, ROWCOL nToCol, BOOL bSet);
	virtual void UpdateCoveredCellsRowCol(ROWCOL nRow, ROWCOL nCol, ROWCOL nOldToRow, ROWCOL nOldToCol, UINT flags, BOOL bCreateHint = FALSE);
	virtual void MergeCoveredCells(CGXRange& range);

// Floating Cells
public:
	void SetFloatCellsMode(WORD nMode, BOOL bRedraw = TRUE);
	WORD GetFloatCellsMode() const;

	void DelayFloatCells(const CGXRange& range, ROWCOL nMaxCols = GX_INVALID);
	BOOL EvalFloatCells(const CGXRange& range, BOOL bUpdate = TRUE, CGXRange* prgBoundary = NULL, BOOL bLookupStyle = FALSE);

	virtual BOOL CanFloatCell(CGXControl* pControl, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, BOOL bFloatOrFlood);

	CGXRange* GetFloatedCellsRowCol(ROWCOL nRow, ROWCOL nCol, CGXRange& range);

protected:
	BOOL SetFloatedCellsRowCol(ROWCOL nRow, ROWCOL nCol, ROWCOL nToRow, ROWCOL nToCol, UINT flags = GX_UPDATENOW);
	void MergeFloatedCells(CGXRange& range);
	void UpdateFloatedCellsRowCol(ROWCOL nRow, ROWCOL nCol, ROWCOL nOldToRow, ROWCOL nOldToCol, UINT flags, BOOL bCreateHint = FALSE);

	CGXSpanCellPool* GetFloatCellsPool();

	// Implementation - Float Cell Data
	BOOL m_bLockEvalFloatCells;

	struct FloatCellsData
	{
		ROWCOL nColOffset;
		CObArray apStylesArray;         // cached style objects for latest row
		CWordArray awSizeArray;         // cached CalcSize return values for latest row
		ROWCOL nLastRow;                // latest row id

		void InitColOffset(ROWCOL nCol);
		int GetIndex(ROWCOL nCol);
		void Reset(CGXGridCore* pGrid);
	} m_FloatCellData;

// Merge Cells
public:
	void SetMergeCellsMode(WORD nMode, BOOL bRedraw = TRUE);
	WORD GetMergeCellsMode() const;

	void DelayMergeCells(const CGXRange& range, ROWCOL nMaxRows = GX_INVALID, ROWCOL nMaxCols = GX_INVALID);
	BOOL EvalMergeCells(const CGXRange& range, BOOL bUpdate = TRUE, CGXRange* prgBoundary = NULL, BOOL bLookupStyle = FALSE);

	CGXRange* GetMergedCellsRowCol(ROWCOL nRow, ROWCOL nCol, CGXRange& range, int mtType = -1);
	virtual BOOL CanMergeCell(CGXControl* pControl, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, int mtType);
	virtual BOOL CanMergeCells(const CGXStyle& style1, const CGXStyle& style2);

protected:
	BOOL SetMergedCellsRowCol(int mtType, ROWCOL nRow, ROWCOL nCol, ROWCOL nToRow, ROWCOL nToCol, UINT flags = GX_UPDATENOW);
	void UpdateMergedCellsRowCol(ROWCOL nRow, ROWCOL nCol, ROWCOL nOldToRow, ROWCOL nOldToCol, UINT flags, BOOL bCreateHint = FALSE);
	void MergeMergedCells(CGXRange& range);

	BOOL m_bLockEvalMergeCells;

	enum MergeCellType
	{
		mtHorz = 0,
		mtVert = 1
	};

	struct MergeCellsData
	{
		ROWCOL nColOffset;
		CObArray apStylesArray;         // cached style objects for latest row
		CWordArray awSizeArray;         // cached CalcSize return values for latest row
		ROWCOL nLastRow;                // latest row id

		void InitColOffset(ROWCOL nCol);
		int GetIndex(ROWCOL nCol);
		void Reset(CGXGridCore* pGrid);
	} m_MergeCellData;

	CGXRange m_rgMerged;

// Covered, Float and Merge Cells
public:
	virtual CGXRange* GetCellRangeRowCol(ROWCOL nRow, ROWCOL nCol, CGXRange& range);
	BOOL EvalVisibleFloatMergeCells(const CGXRange& range, BOOL bUpdate = TRUE, CGXRange* prgBoundary = NULL, BOOL bLookupStyle = FALSE);
	virtual BOOL EvalVisibleFloatMergeCells(const CGXRange& range, ROWCOL nfr, ROWCOL nfc, ROWCOL nTopRow, ROWCOL nLefCol, ROWCOL nLastRow, ROWCOL nLastCol, BOOL bUpdate = TRUE, CGXRange* prgBoundary = NULL, BOOL bLookupStyle = FALSE);

// Find&Replace
public:
	BOOL FindText(BOOL bSetCell = TRUE);
	BOOL FindText(ROWCOL& nRow, ROWCOL& nCol, BOOL bSetCell);
	void GetSelectedText(CString& strResult);

	// Find&Replace - Overridables
	virtual void OnFindNext(LPCTSTR lpszFind, BOOL bNext, BOOL bCase);
	virtual void OnReplaceSel(LPCTSTR lpszFind, BOOL bNext, BOOL bCase, LPCTSTR lpszReplace);
	virtual void OnReplaceAll(LPCTSTR lpszFind, LPCTSTR lpszReplace, BOOL bCase);

	virtual void OnTextNotFound(LPCTSTR lpszFind);

	virtual void OnShowFindReplaceDialog(BOOL bFindOnly);

protected:
	// Find&Replace - Implementation
	virtual void OnFindReplace(CFindReplaceDialog* pDialog);

// Attributes
	BOOL    m_bCanceled;
	ROWCOL  m_nFirstRow;

// Undo, Redo
public:
	virtual BOOL Undo();
	virtual BOOL Redo();

	virtual void BeginTrans(LPCTSTR pszDescription);
	virtual void CommitTrans();
	virtual void Rollback();

	virtual BOOL CanUndo(CCmdUI* pCmdUI);
	virtual BOOL CanRedo(CCmdUI* pCmdUI);

	virtual void AddCommand(CGXCommand* pCmd, GXCmdType ctCmd);
	virtual void RemoveCommand(GXCmdType ctCmd);
	virtual void OnCellUndone(ROWCOL nRow, ROWCOL nCol, BOOL bSetEdit = FALSE);

	virtual BOOL SetAdvancedUndo(BOOL bAdvUndo);
	virtual CObject* GetAdvancedUndoInfo();
	virtual BOOL UndoAdvanced(CObject* pAdvUndo, BOOL bCreateUndoInfo, BOOL bOnlyToolCells);
	virtual void CleanAdvancedUndo();
	virtual BOOL ExecuteCommand(CGXCommand* pCmd, CGXGridCore* pGrid, GXCmdType ctType);


protected:
	// Attributes
	BOOL m_bBlockCmd;
	BOOL m_bLastSetEdit;
	BOOL m_bCellUndone;
	ROWCOL m_nLastRow;
	ROWCOL m_nLastCol;
	CString m_sTransText;

	// text for undo/redo menu item
	CString m_sEditRedo;
	CString m_sEditUndo;

// Scrolling
public:
	virtual BOOL ScrollCellInView(ROWCOL nRow, ROWCOL nCol, UINT flags = GX_UPDATENOW, BOOL bFloatCell = FALSE);
	virtual BOOL DoScroll(int direction, ROWCOL nCell);
	virtual void UpdateScrollbars(BOOL bRedraw = TRUE, BOOL bOnlyIfDimensionChanged = FALSE);
	virtual void SetScrollBarMode(int nBar, int nSetting, BOOL bRedraw = TRUE);

	int GetScrollBarMode(int nBar);
	BOOL LockScrollbars(BOOL bLock);

	virtual BOOL OnAutoScroll(int direction, ROWCOL nCell);

protected:
	virtual BOOL OnLeftColChange(ROWCOL nNewLeftCol);
	virtual BOOL OnTopRowChange(ROWCOL nNewTopRow);
	virtual void OnLeftColChanged();
	virtual void OnTopRowChanged();

	// Scrollbars
	// I have here my own functions to support 16-Bit Grids with more than 32767 lines or cols
	// even with the 16-Bit version. See description of CWnd->
	virtual ROWCOL SetScrollPos(int nBar, ROWCOL nPos, BOOL bRedraw = TRUE);
	virtual void SetScrollRange(int nBar, ROWCOL nMinPos, ROWCOL nMaxPos, BOOL bRedraw = TRUE);
	virtual ROWCOL GetScrollPos(int nBar) const;
	virtual void GetScrollRange(int nBar, ROWCOL* lpMinPos, ROWCOL* lpMaxPos) const;

	void ScrollWindow(int xAmount, int yAmount, LPCRECT lpRect = NULL, LPCRECT lpClipRect = NULL);
	// ->END

public:	
	void AutoScroll(BOOL bSetCapture = FALSE, BOOL bVertical = TRUE, BOOL bHorizontal = TRUE);

	// Prevent or enable use of autoscroll-mode
	void SetAutoScroll(BOOL bAutoScroll);
	void SetAccelArrowKey(BOOL bEnable);
	void SetAccelScrollbars(BOOL bEnable);

protected:
	int m_nVScrollSetting;
	int m_nHScrollSetting;
	BOOL m_bLockedScrollbars;       // prevents flickering of scrolbars
	BOOL m_bScrollbarsChanged;      // SetScrollRange wil set this to be TRUE

	ROWCOL  m_nLastSBRowCount,      // UpdateScrollbars stores GetRowCount, GetColCount to these
			m_nLastSBColCount;      // attributes.

// The Current Cell
public:
	virtual BOOL SetCurrentCell(ROWCOL nRow, ROWCOL nCol, UINT flags = GX_SCROLLINVIEW | GX_UPDATENOW);
	virtual BOOL TransferCurrentCell(BOOL bSaveAndValidate = TRUE, UINT flags = GX_UPDATENOW, BOOL bCreateHint = TRUE);
	BOOL GetCurrentCell(ROWCOL* pnRow, ROWCOL* pnCol, BOOL bIgnorePrint = FALSE);
	BOOL GetCurrentCell(ROWCOL& nRow, ROWCOL& nCol, BOOL bIgnorePrint = FALSE);
	BOOL IsCurrentCell(ROWCOL nRow = GX_INVALID, ROWCOL nCol = GX_INVALID, BOOL bIgnorePrint = FALSE);
	BOOL IsActiveCurrentCell();

	virtual BOOL FindNextCell(int direction, ROWCOL& nSetRow, ROWCOL& nSetCol);
	virtual BOOL ProcessKeys(CWnd* pSender, UINT nMessage, UINT nChar, UINT nRepCnt = 1, UINT flags = 0);
	virtual BOOL MoveCurrentCell(int direction, UINT nCell = 1, BOOL bCanSelectRange = TRUE);
	virtual void ResetCurrentCell(BOOL bStoreIfModified = TRUE);
	virtual void HideCurrentCell();

	// delayed message box when invalid cell
	virtual void SetWarningText(LPCTSTR s);
	virtual void DisplayWarningText();
	CString m_sWarningText;
	BOOL    m_bLockActivateGrid;
	BOOL	m_bLockCurrentCell;  // Don't reset current cell when grid is deactivate
	BOOL    m_bRefreshControl;
	BOOL    m_bWarningTextDisplayed;
	BOOL	m_bKillFocusCalled;

protected:
	void StoreCurrentCell(BOOL bActive, ROWCOL nRow = 0, ROWCOL nCol = 0);

	virtual BOOL MoveCurrentCellEx(int direction, UINT nCell = 1);

	// events
	virtual BOOL OnValidateCell(ROWCOL nRow, ROWCOL nCol);
	virtual BOOL OnStartEditing(ROWCOL nRow, ROWCOL nCol);
	virtual void OnModifyCell(ROWCOL nRow, ROWCOL nCol);
	virtual BOOL OnCancelEditing(ROWCOL nRow, ROWCOL nCol);
	virtual void OnCanceledEditing(ROWCOL nRow, ROWCOL nCol);
	virtual BOOL OnEndEditing(ROWCOL nRow, ROWCOL nCol);
	virtual BOOL OnLeftCell(ROWCOL nRow, ROWCOL nCol, ROWCOL nNewRow, ROWCOL nNewCol);
	virtual BOOL OnDeleteCell(ROWCOL nRow, ROWCOL nCol);
	virtual void OnInitCurrentCell(ROWCOL nRow, ROWCOL nCol);
	virtual void OnMovedCurrentCell(ROWCOL nRow, ROWCOL nCol);
	virtual BOOL CanSelectCurrentCell(BOOL bSelect, ROWCOL dwSelectRow, ROWCOL dwSelectCol, ROWCOL dwOldRow, ROWCOL dwOldCol);
	virtual BOOL OnScrollBecauseOfEdit(int direction, ROWCOL nCell);

	virtual BOOL OnLButtonClickedRowCol(ROWCOL nRow, ROWCOL nCol, UINT nFlags, CPoint pt);
	virtual BOOL OnMButtonClickedRowCol(ROWCOL nRow, ROWCOL nCol, UINT nFlags, CPoint pt);
	virtual BOOL OnRButtonClickedRowCol(ROWCOL nRow, ROWCOL nCol, UINT nFlags, CPoint pt);

	virtual BOOL OnLButtonDblClkRowCol(ROWCOL nRow, ROWCOL nCol, UINT nFlags, CPoint pt);
	virtual BOOL OnMButtonDblClkRowCol(ROWCOL nRow, ROWCOL nCol, UINT nFlags, CPoint pt);
	virtual BOOL OnRButtonDblClkRowCol(ROWCOL nRow, ROWCOL nCol, UINT nFlags, CPoint pt);

	virtual BOOL OnMouseMoveOver(ROWCOL nRow, ROWCOL nCol, UINT flags, CPoint pt);

	// Buttons and Combobox
	virtual void OnClickedButtonRowCol(ROWCOL nHitRow, ROWCOL nHitCol);

	virtual BOOL OnLButtonHitRowCol(ROWCOL nHitRow, ROWCOL nHitCol, ROWCOL nDragRow, ROWCOL nDragCol, CPoint point, UINT flags, WORD nHitState);
	virtual BOOL OnMButtonHitRowCol(ROWCOL nHitRow, ROWCOL nHitCol, ROWCOL nDragRow, ROWCOL nDragCol, CPoint point, UINT flags, WORD nHitState);
	virtual BOOL OnRButtonHitRowCol(ROWCOL nHitRow, ROWCOL nHitCol, ROWCOL nDragRow, ROWCOL nDragCol, CPoint point, UINT flags, WORD nHitState);


public:
	BOOL m_bDisableMouseMoveOver;

public:
	CGXControl* GetCurrentCellControl();
	virtual CGXControl* GetControl(ROWCOL nRow, ROWCOL nCol);
	void RegisterControl(WORD nID, CGXControl* pControl, BOOL bDefault = FALSE, BOOL bShowInStyleSheet = TRUE);
	virtual CGXControl* GetRegisteredControl(WORD nID);

protected:
	CGXControl*  m_pDefaultControl;
	CGXControl*  m_pLastControlHit;
	UINT m_nLastControlHit;
	CMapPtrToPtr m_ControlMap;

	BOOL m_bValidatingCell;
	BOOL m_bCacheCurrentCell;   // set this FALSE if you want to outline the current cell with special formattings

	BOOL m_bRefreshOnSetCurrentCell;
					// If your cells appearence is depending on whether
					// it is a current cell or not, you should set
					// m_bRefreshOnSetCurrentCell = TRUE. Otherwise
					// a smarter redrawing of the cell will be used.

	ROWCOL m_nLastInitRow,  // used in OnInitCurrentCell()
		   m_nLastInitCol;

// Splitter support
public:
	CSplitterWnd*   m_pSplitterWnd;
	int             m_nSplitRow,
					m_nSplitCol;

	CGXGridCore*    GetOtherSplitRowChildPane(int nSplitRow, int nSplitCol);
	CGXGridCore*    GetOtherSplitColumnChildPane(int nSplitRow, int nSplitCol);


// Range names
public:
	virtual BOOL SetRangeName(LPCTSTR name, const CGXRange& rg, CObject* pUndoInfo = NULL, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);
	virtual BOOL GetRangeName(LPCTSTR name, CGXRange& rg);
	virtual BOOL DeleteRangeName(LPCTSTR name, CObject* pUndoInfo = NULL, GXCmdType ctCmd = gxDo);

// Clipboard - Cut, Copy and Paste helper
public:
	// copy to clibpoard helpers
	virtual BOOL CopyRange(const CGXRange& range);
	BOOL CopyTextToFile(CFile& destFile, const CGXRange& range);
	BOOL CopyCellsToArchive(CArchive& ar, const CGXRange& range, BOOL bLoadBaseStyles = FALSE);

	virtual BOOL CopyRange(const CGXRangeList& selList);
	virtual BOOL CopyTextToFile(CFile& destFile, const CGXRangeList& selList);
	virtual BOOL CopyCellsToArchive(CArchive& ar, const CGXRangeList& selList, BOOL bLoadBaseStyles = FALSE);
	virtual BOOL GetClipboardStyleRowCol(ROWCOL nRow, ROWCOL nCol, CGXStyle* pStyle, BOOL bLoadBaseStyles);
	virtual CString GetCopyTextRowCol(ROWCOL nRow, ROWCOL nCol);

	// cut cells - helpers
	BOOL CutRange(const CGXRange& range, BOOL bStyleOrValue = TRUE);
	virtual BOOL CutRange(const CGXRangeList& selList, BOOL bStyleOrValue = TRUE);

	BOOL ClearCells(const CGXRange& range, BOOL bStyleOrValue = TRUE);
	virtual BOOL ClearCells(const CGXRangeList& selList, BOOL bStyleOrValue = TRUE);

	// paste cells - helpers
	virtual BOOL PasteCellsFromArchive(CArchive& ar, const CGXRange& range, BOOL bIgnoreDiffRange = FALSE);
	virtual BOOL PasteTextFromBuffer(LPCTSTR psz, DWORD size, const CGXRange& range);
	virtual BOOL CalcBufferDimension(LPCTSTR psz, DWORD size, ROWCOL& nRows, ROWCOL& nCols);
	virtual BOOL SetControlTextRowCol(ROWCOL nRow, ROWCOL nCol, const CString& str, UINT nFlags = GX_UPDATENOW, const CGXStyle* pOldStyle = NULL);
	virtual BOOL PasteTextRowCol(ROWCOL nRow, ROWCOL nCol, const CString& str, UINT nFlags, const CGXStyle* pOldStyle);

	// paste cells - overridables
	// override this methods if you want to support additional clipboard formats
	virtual BOOL OnPasteDirect(const CGXRange& range);
	virtual BOOL OnPasteFromClipboard(const CGXRange& range);
	virtual BOOL OnCheckClipboardFormat();

	// copy/move ranges in one step
	virtual BOOL StoreCopyCells(CGXRange rg, ROWCOL nRow, ROWCOL nCol);
	virtual BOOL StoreMoveCells(CGXRange rg, ROWCOL nRow, ROWCOL nCol, CObject*& pUndoInfo, BOOL bCreateUndoInfo, GXCmdType ctCmd);
	virtual BOOL CopyCells(CGXRange rg, ROWCOL nRow, ROWCOL nCol, UINT flags = GX_UPDATENOW);
	virtual BOOL MoveCells(CGXRange rg, ROWCOL nRow, ROWCOL nCol, CObject* pUndoInfo = NULL, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);

	// displays message box when range is different
	virtual BOOL OnPasteDiffRange();

	// Implementation
	BOOL CopyTextToClipboard(const CGXRangeList& selList);
	BOOL CopyCellsToClipboard(const CGXRangeList& selList, BOOL bLoadBaseStyles = FALSE);

	CString m_sImportTabDelim;  // default is '\t', used for separating columns when importing text file
	CString m_sExportTabDelim;  // default is '\t', used for separating columns when exporting text file
	DWORD m_nClipboardFlags;

	// Attributes
protected:
	ROWCOL  m_nRowsCopied,  // No of rows/cols copied by CopyTextToFile or
			m_nColsCopied;  // CopyCellsToArchive operation

public:
	// OLE drag/drop support

	// start drag&drop operation
	virtual BOOL DndStartDragDrop(ROWCOL nRow, ROWCOL nCol);

	// Attributes - Options
	DWORD   m_nDndFlags;                // Data source options (Copy headers, Clipboard formats)
	DWORD   m_dwDndDropTargetFlags;     // Drop target options (AutoScroll, Drop on header)

#if _MFC_VER >= 0x0400 && !defined(_AFX_NO_OLE_SUPPORT)
public:
	// enable support for data source
	BOOL EnableOleDataSource(DWORD dwFlags = GX_DNDTEXT|GX_DNDSTYLES|GX_DNDCOMPOSE|GX_DNDDIFFRANGEDLG);
	void EnableOleDropTarget(DWORD dwFlags = GX_DNDEGDESCROLL|GX_DNDAUTOSCROLL|GX_DNDTEXT|GX_DNDSTYLES);

	// overridables for OLE dnd
	// overridable for data source
	virtual BOOL OnDndCacheGlobalData(CGXNoOleDataSourceProxy* pSrcItem, const CGXRangeList& selList, ROWCOL& nDndRowExt, ROWCOL& nDndColExt);

	// overridables for drop target
	virtual BOOL OnDndCalculateFocusRect(CGXNoOleDataObjectProxy* pOleDataObjectProxy, ROWCOL& nRowExt, ROWCOL& nColExt);
	virtual BOOL OnDndQueryAcceptData(CGXNoOleDataObjectProxy* pDataObject);
	virtual BOOL OnDndDropData(CGXNoOleDataObjectProxy* pDataObject, ROWCOL nRow, ROWCOL nCol);

	// support for drop target, functions called from CGXGridDropTarget
	virtual DROPEFFECT OnGridDragEnter(CGXNoOleDataObjectProxy* pDataObject, DWORD dwKeyState, CPoint point);
	virtual DROPEFFECT OnGridDragOver(CGXNoOleDataObjectProxy* pDataObject,	DWORD dwKeyState, CPoint point);
	virtual void OnGridDragLeave();
	virtual BOOL OnGridDrop(CGXNoOleDataObjectProxy* pDataObject, DROPEFFECT dropEffect, CPoint point);
	virtual DROPEFFECT OnGridDropEx(CGXNoOleDataObjectProxy* pDataObject, DROPEFFECT dropDefault, DROPEFFECT dropList, CPoint point);
	virtual DROPEFFECT OnGridDragScroll(DWORD dwKeyState, CPoint point);

	// helpers for drop target
	virtual void DndDrawMoveRect(CPoint point, BOOL bEraseOld, BOOL bDrawNew);
	BOOL DoDragScroll(CPoint point);
	BOOL IsOverAnotherApplication(POINT point);

	// Attributes - Data Source Proxy

	// Attributes - Focus Rectangle
	ROWCOL m_nDndLastRow,
		   m_nDndLastCol;
	BOOL   m_bDndDrawn;
	CRect  m_DndLastRect;
	ROWCOL m_nDndRowExt,
		   m_nDndColExt;                // No of rows/cols to be dropped

	// Attributes - Auto scrolling
	int m_nDndScrollInset;              // margin for inset scrolling regions
	UINT m_nDndScrollDelay;             // delay for starting inset scrolling
	UINT m_nDndScrollInterval;          // interval for auto scrolling
	UINT m_nDndOutOfWndDelay;           // delay for starting out of window scrolling
	UINT m_nDndOufOfWndHorzScrollBy,    // factor for no of rows/cols to scroll
		 m_nDndOufOfWndVertScrollBy;

	BOOL m_bDndGlobalTimer;             // TRUE for out of window scrolling

	UINT m_nDndLastScrollCode;
	BOOL m_bDndLastScrollCode2;
	DWORD m_dwDndLastTick;
	UINT m_nDndNextTicks;
	CGXGridDropTarget* m_pRegDropTarget;

	DROPEFFECT m_nDndDropeffect;        // last drop effect

	// static attributes for general information
	static BOOL     m_bDndGridSource;   // TRUE if CGXGridCore is a data source
	static ROWCOL   m_nDndRowsCopied,   // No of rows/cols copied in OnDndCacheGlobalData
					m_nDndColsCopied;
#endif

	
#if _MFC_VER >= 0x0400
public:
	// Support for tooltips on cells
	BOOL EnableGridToolTips(BOOL b = TRUE);
#if _MFC_VER >= 0x0600
	void ToolTipSetDelayTime( UINT nDelay );
	void ToolTipSetDelayTime( DWORD dwDuration, int iTime );
#endif//_MFC_VER >= 0x0600
	
protected:
	CGXNoToolTipCtrlProxy* m_pTooltipProxy;
	friend class CGXToolTipCtrlProxy;
	BOOL m_bTtnIsEnabled;               // TRUE if tooltips are enabled


#endif

	// Support for IntelliMouse 
public:
	CObList m_pluginList;
	void AddPlugin(CGXPluginComponent* pPlugin);

	// Call EnableFormulaEngine before CGXGridCore::OnGridInitialUpdate
	// to enable formula support
protected:
	CRuntimeClass* m_pDefaultDataClass;  // default: CGXData

public:
	void EnableFormulaEngine();  // assign CGXFormulaSheet to m_pDefaultDataClass
	CGXFormulaSheet* GetSheetContext();  // shortcut to get a pointer to CGXFormulaSheet

public:
	virtual BOOL GetUpdateFlag(ROWCOL nRow, ROWCOL nCol);  // is update flag set
	virtual void SetUpdateFlag(ROWCOL nRow, ROWCOL nCol, BOOL bToggle);  // set update flag (TRUE if cell shall be updated later)
	virtual void AddRecalcRange(const CGXRange& range);
	virtual BOOL RefreshViews(BOOL bRecalc = TRUE, CString* pErrorStr = NULL, BOOL bCreateHint = TRUE); // loop through visible cells and redraw cells with update flag
	virtual void Recalc(BOOL bForceRecalc = FALSE);
	virtual void ResetError();
	virtual BOOL GetError(CString& strError);

	// void CGXGridCore::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
	// --- add m_nHintRefreshViews

protected:
	BOOL m_bRefreshOnlyUpdatedCells;  // RefreshViews will set this TRUE if only marked cells should be redrawn
	BOOL m_bLockAddRecalcRange;
	int m_nExpressionValueType;

// Menu commands
public:
	virtual BOOL Copy();
	virtual BOOL Paste();
	virtual BOOL Cut();
	virtual BOOL Clear(BOOL bStyleOrValue = TRUE);

	virtual BOOL CanCopy();
	virtual BOOL CanCut();
	virtual BOOL CanPaste();
	virtual BOOL CanClear();

	virtual void FreezeCols();
	virtual BOOL CanFreezeCols();
	virtual void UnfreezeCols();
	virtual BOOL CanUnfreezeCols();
	virtual void FreezeRows();
	virtual BOOL CanFreezeRows();
	virtual void UnfreezeRows();
	virtual BOOL CanUnfreezeRows();

// Drawing of cells
public:
	virtual void RedrawRowCol(ROWCOL nStartRow, ROWCOL nStartCol, ROWCOL nEndRow, ROWCOL nEndCol, UINT flags = GX_UPDATENOW, BOOL bCreateHint = TRUE);
	virtual void Redraw(UINT flags = GX_UPDATENOW, BOOL bCreateHint = TRUE);
	void RedrawRowCol(ROWCOL nRow, ROWCOL nCol, UINT flags = GX_UPDATENOW, BOOL bCreateHint = TRUE);
	void RedrawRowCol(const CGXRange& range, UINT flags = GX_UPDATENOW, BOOL bCreateHint = TRUE);

	virtual CRect SubtractBorders(const CRect& rect, const CGXStyle& style, BOOL bSubtrLines = TRUE);
	virtual CSize AddBorders(CSize size, const CGXStyle& style);

	BOOL LockUpdate(BOOL b = TRUE);
	BOOL IsLockUpdate();

	// CGXGridCore Printing support
	virtual void OnAdjustPrintRectangle(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrintHeaderAndFooter(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnGridBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnGridEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnGridPrint(CDC* pDC, CPrintInfo* pInfo);

	// Grid Dimension
	virtual void OnTestGridDimension(ROWCOL nLastRow, ROWCOL nLastCol);

protected:
	virtual void OnGridDraw(CDC* pDC);  // called by OnPaint
	virtual void PrepareDCAttribs(CDC* pDC); // gets called on all CDCs before the grid draws into it.

	virtual void OnDrawItem(CDC *pDC, ROWCOL nRow, ROWCOL nCol, const CRect& rectDraw, const CGXStyle& style);
	virtual void MarkEdit(ROWCOL nEditRow, ROWCOL nEditCol, UINT direction = 0, UINT flags = GX_UPDATENOW);

	virtual void OnDrawTopLeftBottomRight(ROWCOL topRow, ROWCOL leftCol, ROWCOL bottomRow, ROWCOL rightCol, CDC* pDC);

	// implementation specific->
protected:
	int m_nNestedDraw;

	struct DrawStruct
	{
		DrawStruct();
		~DrawStruct();

		unsigned    nRows,
					nCols;

		ROWCOL      gridTopRow,
					gridLeftCol,
					gridFrozenCols,
					gridFrozenRows,
					gridHeaderCols,
					gridHeaderRows;

		CRect       rectEdit,
					rectItem;

		int         nxMin,
					nyMin;
		int         nxMax,
					nyMax;

		int*        anHeights;
		int*        anWidths;
		int*        anYOffset;
		int*        anXOffset;
		ROWCOL*     anRows;
		ROWCOL*     anCols;
		LPCSTYLE*   apStyles;
		WORD*       abBits;

		CGXControl* pCurrentControl;

		BOOL        bAnyCellCovered;
		BOOL        bAnyCellSelected;
		BOOL        bColor;
		COLORREF    rgbStandard;

		ROWCOL      topRow,
					leftCol,
					bottomRow,
					rightCol;

		CDC*        pDC;

		CRect       rectClip;
		CGXBrush    brTemp1, brTemp2;
	};

	DrawStruct* m_pDrawStruct;
	DrawStruct* m_pOldDrawStruct;
	CGXBrush m_tempBrush;
	BOOL m_bInvertRect;
	BOOL m_bForceOldDrawing;

	void OnDrawTLBR_EvalFloatMergeCell(DrawStruct& ds);
	void OnDrawTLBR_LoadCell(DrawStruct& ds, unsigned nRow, unsigned nCol);
	void OnDrawTLBR_DrawBackground(DrawStruct &ds, unsigned nRow);
	void OnDrawTLBR_DrawBackground(DrawStruct &ds);
	void OnDrawTLBR_DrawCell(DrawStruct& ds, unsigned nRow, unsigned nCol);
	void OnDrawTLBR_DrawVertBorders(DrawStruct& ds, unsigned nCol);
	void OnDrawTLBR_DrawHorzBorders(DrawStruct& ds, unsigned nRow);
	void OnDrawTLBR_InvertCells(DrawStruct& ds);
	void OnDrawTLBR_InvertCells(DrawStruct& ds, unsigned nRow);

	virtual void DrawInvertCell(CDC *pDC, ROWCOL nRow, ROWCOL nCol, CRect rectItem);
	virtual void DrawGridLine(CDC* pDC,int x,int y,int dx,int dy, int type, ROWCOL nClientRC, UINT flags = 0);
	void DrawGridLine(CDC* pDC, int type, ROWCOL nClientRC, UINT flags = 0);
	void OnDrawBorders(CDC *pDC, CRect rectItem, const CGXStyle& style);

public:
	void DrawBorder(const CGXPen& pen, const CRect& rect, GXBorderType bt, CDC* pDC, const CGXBrush* pbrInterior = NULL);
	void DrawBrushRect(CDC* pDC, const CRect& rect, const CGXBrush& brush);
	// ->END

public:
	GXDrawingTechnique SetDrawingTechnique(GXDrawingTechnique t);

protected:
	GXDrawingTechnique m_nDrawingTechnique;

	void DrawUsingMemDC(CDC* pDC);
	void DrawDirectToDC(CDC* pDC);

	BOOL m_bDrawCoveredCell; // flag for CGXControl::DrawBackground
	BOOL m_bForceDrawBackground; // flag for CGXControl::DrawBackground

// GDI-Objects, Cache operations
public:
	CFont*  LookupOrCreateFont(const CGXFont& font);
	CBrush* LookupOrCreateBrush(const CGXBrush& brush);
	CPen*   LookupOrCreatePen(const CGXPen& pen);
	CDC*    GetGridDC();
	void    ReleaseGridDC();

	CFont*  LoadFont(CDC* pDC, const CGXFont& font);

	virtual CFont*  LoadFont(CDC* pDC, const CGXStyle& style, const CGXStyle* pStandardStyle = NULL);

protected:
	virtual void FreeObjectCache();
	virtual void GetFontMetrics(CDC* pDC, int& dxWidth, int& dyHeight);

protected:
	void GetDefaultFontSize(int &dxWidth, int &dyHeight);


	// Object cache for drawing
	CGXMapByte8ToPtr	m_mapFontHandles;
	CGXMapByte8ToPtr	m_mapBrushHandles;
	CGXMapByte8ToPtr    m_mapPenHandles;
	CGXMapCellToOb      m_mapStyles;

	CMapWordToOb        m_mapAltStyles;
	void**              m_papAltStyles;
	ROWCOL              m_nAltStylesTopRow,
						m_nAltStylesLeftCol;
	CPtrList            m_listAltStyles;
	unsigned            m_nAltStylesRows,
						m_nAltStylesCols,
						m_nAltStylesColOffs,
						m_nAltStylesRowOffs,
						m_nAltStylesCount;
	CDC*                m_pGridDC;
	HFONT               m_hOldFont;

#ifdef _CCHIT
	CGXCollMapDWordToLong     m_mapCellHit;
#endif

	CGXStyle*           m_pStyleColHeader;
	CGXStyle*           m_pStyleRowHeader;
	CGXStyle*           m_pStyleStandard;

	CGXStyle*           m_pStyleEdit;

	CFont               m_fontEdit;
	CBrush              m_brushEdit;
	CPen                m_penEdit;
	CFont               m_fontCombo;

	int                 m_nZoom;

	BOOL                m_bLockGDIObjects;    // avoid emptying GDI-objects-cache
	BOOL                m_bLockStyleEdit;     // don't reload edit cell
	ROWCOL              m_nLockRow;
	ROWCOL              m_nLockCol;
	ROWCOL              m_nLockRow2;
	ROWCOL              m_nLockCol2;

	// Excluded clipping regions for BitmapDC drawing
	CPtrList            m_listExcludeClipRect;
	BOOL				m_bLastFocus;

/////////////////////////////////////////////////////////////////////////////
// Implementation

public:
	BOOL IsActiveFrame();
	void LockResize(BOOL bState);

// Calculations
	// Mouse Actions
	virtual void ShowContextCursor(CPoint& point);
	virtual void ShowContextCursor(UINT idcPrimary, LPCTSTR idcSecondary);
	virtual void SetGridCursor(UINT idcCursor);

protected:
	void ResetGrid();

	// Get rows and cols from Points
		// CalcClientRowColFromPt checks if nRow, nCol != GX_INVALID
	BOOL   CalcClientRowColFromPt(CPoint& pt, ROWCOL* nRow, ROWCOL* nCol, CRect* rect = NULL );
		// CalcValidClientRowColFromPt: if pt is Invalid --> nRow = GetRowCount, nCol = GetColCount
	void   CalcValidClientRowColFromPt(CPoint& pt, ROWCOL* nRow, ROWCOL* nCol);

	// Get coordinates rectangle from row, col
	int CalcLeftFromClientCol(ROWCOL nCol);
	int CalcTopFromClientRow(ROWCOL nRow);

	// Get rectangle from row, col
	CRect CalcRectFromClientRowCol(ROWCOL nClientRow, ROWCOL nClientCol);
	CRect CalcNextRectFromClientRowCol(ROWCOL nClientRow, ROWCOL nClientCol);

	CRect CalcClientRectRightFromCol(ROWCOL nCol);
	CRect CalcClientRectBottomFromRow(ROWCOL nRow);

public:
	// Current view
	ROWCOL  m_nEditRow,                  // row id for current cell
			m_nEditCol,                  // column id for current cell
			m_nTopRow,                   // top row
			m_nLeftCol,                  // left column
			m_nVScrollFactor,            // scrolling factor (if more than 32768 rows, it is > 1)
			m_nHScrollFactor;            // scrolling factor (if more than 32768 columns, it is > 1)

	CGXControl* m_pCurrentCellControl;

	BOOL    m_bVertScrollBar,
			m_bHorzScrollBar;

	BOOL    m_bActiveFrame,              // FrameWnd is activ
			m_bActiveEditCell;           // current cell is activ

	BOOL	m_bDoScrollNoUpdateWindow;	// Set this TRUE if DoScroll should not call UpdateWindow

public:
	BOOL    m_bDropDownCell;
	BOOL    m_bIgnoreFocus;              // ignore incoming KillFocus/SetFocus messages

	void    SetIgnoreFocus(BOOL b);
	void    SetDropDownCell(BOOL b);

protected:
	// Font
	int     m_dyHeight,                  // Font - height
			m_dxWidth;                   // Font - avg. width

	int     m_psSelDragLine;             // pen for "dragging columns/rows"
	CGXDragLineWnd* m_pWndDrag;

	UINT    m_idcCursor;                 // default Cursor

	// Parameter
	CGXGridParam*
			m_pParam;
	BOOL    m_bOwnParam;                 // is parameter-object life-time bound?

	// internal status
	BOOL    m_bInitDone,                 // TRUE if OnInitialUpdate has been called
			m_bAutoScroll,               // Autoscroll
			m_bDisplayHeaderRow,         // display row headers
			m_bDisplayHeaderCol;         // display column headers

	BOOL	m_bAutoScrollStart,			 // will be checked by autoscroll plugin component
			m_bAutoScrollVert,
			m_bAutoScrollHorz,
			m_bAutoScrollStop,
			m_bSpeedKey,
			m_bAccelArrowKey,
			m_bAccelScrollbars;
	
	int		m_nAutoScrollDirection;

	SEC_UINT	m_nAutoScrollTimer;

	UINT	m_nSpeedKeyChar,
			m_nSpeedKeyFlags;

	// Print / Print Preview
	BOOL    m_bPrintInProgress;          // Semaphor is TRUE when grid is printing
	CRect   m_rectPrint;                 // Return value for GetGridRect() when printing
	BOOL	m_bPrintCurSelOnly;			 // TRUE if "Selected Range" is set in prinf dialog
	ROWCOL  m_nPrintTopRow,              // Return value for GetTopRow() when printing
			m_nPrintLeftCol;             // Return value for GetLeftCol() when printing
	int    m_dyPrintHeight,             // Return value for GetFontHeight() when printing
			m_dxPrintWidth;              // Return value for GetFontWidth() when printing
	BOOL	m_bPrintPaintMsg;
	CRowColArray
			m_awPageFirstRow,            // Page breaks (rows)
			m_awPageFirstCol;            // Page breaks (columns)
	int     m_nCurrentPageRowIndex,      // Currently printed page (index for m_awPageFirstRow)
			m_nCurrentPageColIndex;      // Currently printed page (index for m_awPageFirstCol)

	BOOL    m_bUpdateScrollbar;          // Semaphor to avoid recursive call of UpdateScrollbars()

protected:

	// Dragging rows/columnns
	ROWCOL
			m_nSelDragRow,               // currently selected col/row which shall be dragged
			m_nSelDragCol;               //

	POSITION
			m_SelRectId;

	CGXRange
			m_rangeCurSel;

	ROWCOL  m_dwLastMoveRow,
			m_dwLastMoveCol,             // holds the last row/col of the cell where the mouse was dragged
			m_dwButtonDownRow,
			m_dwButtonDownCol;           // holds the row/col where the mouse was clicked

	// Grid Rectangle (see SetGridRect())
	CRect   m_rectDisplay;
	BOOL    m_bRectDisplay;

	// system settings
	int     m_dxFrame,                   // SM_CXFRAME
			m_dyFrame,                   // SM_CYFRAME
			m_dxBorder,                  // SM_CXBORDER
			m_dyBorder;                  // SM_CYBORDER

	HCURSOR m_hcurArrow;                 // handle for arrow cursor

	// This are only temporary Rectangles, (No scrolling!!!)
	CRect   m_rectTrack,                 // tracking
			m_rectBoundTrack,
			m_rectInvertBar,
			m_rectRC;

	CPoint  m_ptAutoPos;

	ROWCOL  m_RCnRowClient,
			m_RCnColClient;

	ROWCOL  m_nLastVisibleCol,           // Last Visible Row and Column:
			m_nLastVisibleRow;
	BOOL    m_bLastColVisible,
			m_bLastRowVisible;
	ROWCOL  m_nLastVisibleLeftCol,       // if values differ from m_nRopRow/m_nLeftRow
			m_nLastVisibleTopRow;        // m_nLastVisibleCol must be recalculated

	// Mouse actions
	BOOL
			m_bTracking,                 // TRUE if user is tracking row height/column width
			m_bCellHit,                  // TRUE if user is selecting cells
			m_bSelDrag;                  // TRUE if user is dragging rows/cols


	BOOL    m_bTrackMove,
			m_bTrackSmoothHeader,
			m_bTrackSmoothCells,
			m_bTrackMarkLine,
			m_bTrackInvertLine,
			m_bTrackPressedHeader;

	CSize   m_sizeTrackStart;

	WORD    m_nHitState;
	UINT    m_nMouseFlags;
	ROWCOL  m_nHitRow,
			m_nHitCol;
	int     m_nHitChar;
	BOOL    m_bHitCellScope,
			m_bHitMoved,
			m_bEditBtnHit;

	int     m_nTrackingMode,             // either GX_TRACKHEIGHT or GX_TRACKWIDTH
			m_nSelDragMode;              // either GX_SELDRAG_COL or GX_SELDRAG_ROW

	ROWCOL  m_nRowTracking,              // row index for tracking row height
			m_nColTracking;              // column index for tracking column width

	// smarter resizing: old window coordinates (see DoSize and DoShowWindow)
	int     m_cxOld,
			m_cyOld;
	CRect   m_rectWnd;
	BOOL    m_bLockResize;               // Needed for smart resizing
	BOOL    m_bZoomed;

	// support for eat first mouse click
	CWnd*   m_pWndLastFocus;

	// support for IME/DBCS
	BOOL    m_bDoubleByteChar;
	TCHAR   m_nDoubleByteLeadChar;

	// map with more objects that can be linked into grid object
	CMapPtrToPtr m_mapGridLocalData;

/////////////////////////////////////////////////////////////////////////////
// typically CView member functions
public:

protected:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Translated message map functions
protected:
	virtual BOOL DoSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	virtual BOOL DoVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL DoHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL DoSize(UINT nType, int cx, int cy);
	virtual BOOL DoMouseMove(UINT flags, CPoint point);
	virtual BOOL DoShowWindow(BOOL bShow, UINT nStatus);
	virtual BOOL DoLButtonDblClk(UINT flags, CPoint point);
	virtual BOOL DoLButtonDown(UINT flags, CPoint point);
	virtual BOOL DoLButtonUp(UINT flags, CPoint point);
	virtual BOOL DoMButtonDblClk(UINT flags, CPoint point);
	virtual BOOL DoMButtonDown(UINT flags, CPoint point);
	virtual BOOL DoMButtonUp(UINT flags, CPoint point);
	virtual BOOL DoRButtonDblClk(UINT flags, CPoint point);
	virtual BOOL DoRButtonDown(UINT flags, CPoint point);
	virtual BOOL DoRButtonUp(UINT flags, CPoint point);
	virtual HBRUSH DoCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL DoNotifyDestroy();
	virtual BOOL DoCancelMode();
	virtual BOOL DoMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message, int& retval);
	virtual BOOL DoCommand(WPARAM wParam, LPARAM lParam);
	virtual void OnGridWinIniChange(LPCTSTR lpszSection);
	virtual void OnGridSysColorChange();
	virtual UINT DoGetDlgCode(UINT uiDefaultVal);
	virtual CScrollBar* DoGetScrollBarCtrl(int nBar) const;

	// Focus
	virtual void OnGridKillFocus(CWnd* pNewWnd);
	virtual void OnGridSetFocus(CWnd* pOldWnd);

	// PreTranslateMessage
	virtual BOOL OnGridPreTranslateMessage(MSG* pMsg);

	// WindowProc
	virtual BOOL OnGridWindowProc(UINT message, WPARAM wParam, LPARAM lParam, LRESULT& result);

	// Timer
	virtual void OnGridTimer(SEC_UINT nIDEvent);

	// Keyboard events for both child windows and grid window before
	// they are processed. This virtuals are called from PreTranslateMessage.
	virtual BOOL OnGridKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL OnGridKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL OnGridChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL OnGridDoubleByteChar(const CString& sChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL OnGridDeadChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL OnGridSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL OnGridSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL OnGridSysChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL OnGridSysDeadChar(UINT nChar, UINT nRepCnt, UINT nFlags);

// CWnd functions used in CGXGridCore
protected:
	void InvalidateRect(LPCRECT lpRect, BOOL bErase = TRUE);
	void Invalidate(BOOL bErase = TRUE);
	void UpdateWindow();
	int ScrollWindowEx(int dx, int dy,
			LPCRECT lpRectScroll, LPCRECT lpRectClip,
			CRgn* prgnUpdate, LPRECT lpRectUpdate, UINT flags);
	CDC* GetDC();
	int ReleaseDC(CDC* pDC);
	void GetClientRect(LPRECT lpRect);
	virtual void ShowScrollBar(UINT nBar, BOOL bShow = TRUE);
	CWnd* SetCapture();
	CWnd* GetCapture();
	void ScreenToClient(LPPOINT lpPoint);
	void ScreenToClient(LPRECT lpRect);
	void OnMouseMove(UINT flags, CPoint pt);
	BOOL OpenClipboard();

	friend class CGXControl;

	friend class CGXBlockCmd;
	friend class CGXODBCGrid;
	friend class CGXGridHandleView;
	friend class CGXGridHandleWnd;
	friend class CGXGridDropTarget;
	friend class CGXDragLineWnd;
	friend class CGXAutoScrollPlugin;
	friend class CGXPageBreakPlugin; 
	friend static BOOL AFXAPI _doButtonDown1(CGXGridCore* pGrid, UINT flags, CPoint point, UINT xflags, int& ht, ROWCOL& nRow, ROWCOL& nCol);
	friend static BOOL AFXAPI _doButtonDown(CGXGridCore* pGrid, UINT flags, CPoint point, UINT xflags);
	friend static BOOL AFXAPI _doButtonUp(CGXGridCore* pGrid, UINT flags, CPoint point, int& ht, ROWCOL& nRow, ROWCOL& nCol, WORD& w);
};


// Grid local data

#define GX_GRID_LOCAL(class_name, ident_name) \
	class_name* ident_name(CGXGridCore* pGrid) { \
			void* voidptr; \
			class_name* pData; \
			if (!pGrid->m_mapGridLocalData.Lookup(this, pData)) \
				pGrid->m_mapGridLocalData.SetAt(this, pData = new class_name); \
			return pData; \
		} \

#define GX_EXTERN_GRID_LOCAL(class_name, ident_name) \
	extern class_name* ident_name;

/////////////////////////////////////////////////////////////////////////////
// CGXGridHint

// identifier

typedef enum
{
	gxFirstHint,
	gxHintRedraw,
	gxHintRedrawRowCol,
	gxHintUpdateChangedRowCount,
	gxHintUpdateChangedColCount,
	gxHintUpdateChangedRowHeights,
	gxHintUpdateChangedColWidths,
	gxHintUpdateInsertCols,
	gxHintUpdateInsertRows,
	gxHintUpdateRemoveCols,
	gxHintUpdateRemoveRows,
	gxHintUpdateMoveCols,
	gxHintUpdateMoveRows,
	gxHintPrepareChangeSelection,
	gxHintPrepareClearSelection,
	gxHintUpdateFrozenRows,
	gxHintUpdateFrozenCols,
	gxHintUpdateStyleRange,
	gxHintUpdateCoveredCellsRowCol,
	gxHintUpdateZoom,
	gxHintStoreZoom,
	gxHintUpdateReadOnly,
	gxHintChangedTab,
	gxHintUpdateSelectRange,
	gxHintTransferCurrentCell,
	gxHintSetTopRow,
	gxHintSetLeftCol,
	gxHintSyncCurrentCell,
	gxHintUpdateFloatedCellsRowCol,
	gxHintUpdateMergedCellsRowCol,
	gxHintLockSelectionFrame,
	gxHintMoveDataRows,
	gxHintMoveDataCols,
	gxHintUpdateProperties,
	gxHintUpdateStylesMap,
	gxHintUpdateBaseStyle,
	gxHintRefreshViews,
	gxLastHint
} GXHINTID;

// CGXGridHint class

class CGXGridHint : public CObject
{
	DECLARE_DYNAMIC(CGXGridHint)
public:
	CGXGridHint(UINT id, int viewID = -1);

// Attributes
public:
	UINT    m_id;

	CGXRange range;
	const CGXStyle* pStyle;
	GXModifyType mt;
	ROWCOL      nRow1, nRow2, nRow3;
	ROWCOL      nCol1, nCol2, nCol3;
	LONG    lParam;
	DWORD   dwParam;
	void*   vptr;
	UINT    flags;
	int     nViewID;

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};

// Excel-like selction frame

class CGXLockSelectionFrame
{
public:
	CGXLockSelectionFrame(CGXGridCore* pGrid);
	~CGXLockSelectionFrame();

	BOOL m_bLock;
	CGXGridCore* m_pGrid;
};

// Unlock read-only cells

class CGXGridUnlockReadOnly
{
public:
	BOOL m_bLock;
	CGXGridParam* m_pParam;
	CGXGridUnlockReadOnly(CGXGridParam* pParam) { m_pParam = pParam; m_bLock = pParam->IsLockReadOnly(); pParam->SetLockReadOnly(FALSE); }
	~CGXGridUnlockReadOnly() { m_pParam->SetLockReadOnly(m_bLock); }
	void LockReadOnly(BOOL bLock = TRUE) { m_pParam->SetLockReadOnly(bLock); }
};

/////////////////////////////////////////////////////////////////////////////
// Inline function declarations

#ifdef _GX_ENABLE_INLINES
#include "grid\gxcore.inl"
#endif

//
// GridMFC extension DLL
// reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

//

#endif // _GXCORE_H_

