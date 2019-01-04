///////////////////////////////////////////////////////////////////////////////
// gxcore.cpp : implementation of the CGXGridCore class
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

#if _MFC_VER >= 0x0400

// Headers

#ifndef _GXCORE_H_
#include "grid\gxcore.h"
#endif

#ifndef _GXTTN_H_
#include "grid\gxttn.h"
#endif
#endif

#ifndef _GXRESRC_H_
#include "grid\gxresrc.h"
#endif

#ifndef _GXEXT_H_
#include "grid\gxext.h"
#endif

#ifndef _GXCORE_H_
#include "grid\gxcore.h"
#endif

#ifndef _GXCTRL_H_
#include "grid\gxctrl.h"
#endif

#ifndef _GXDLL_H_
#include "grid\gxdll.h"
#endif

#ifndef _GXMSG_H_
#include "grid\gxmsg.h"
#endif

#ifndef _AFXPRIV_H_
#include <afxpriv.h>
#endif

#ifndef _GXPLUGIN_H_
#include "grid\gxplugin.h"
#endif

#ifndef _GXABSTR_H_
#include "grid\gxabstr.h"
#endif

#include "grid\gxpriv.h"


#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXCORE")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

#ifdef TICKCOUNT
#define _TC_(f) f
#else
#define _TC_(f)
#endif

// Control CWnd IDs

#ifdef TICKCOUNT
DWORD tickIndFont = 0, tickStdFont = 0, tickDrawItem = 0, tickDraw = 0, tickLookup = 0;
DWORD tickLookupFont = 0, tickLoadFont = 0, tickCompStd = 0, tickComposeStyle = 0;
DWORD tick1 = 0, tick2 = 0, tick3 = 0, tick4 = 0, tick5 = 0, tick6 = 0, tick7 = 0;
DWORD tick8 = 0, tick9 = 0, tick10 = 0;
#endif

#ifndef _GXDLL
	// QA: 32120 - Wrapping with CThreadLocal.
	CThreadLocal<GX_CURSOR_STATE> GXNEAR _gxCursorState;
#endif

/////////////////////////////////////////////////////////////////////////////
// GX_CURSOR_STATE

GX_CURSOR_STATE::GX_CURSOR_STATE()
{ 
	m_hcurLast = m_hcurDestroy = 0; m_idcPrimaryLast = 0; 
	m_bNotFound = FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CGXGridCore

// this file contains following methods from CGXGridCore:

// - Initialization, Client Area and Parameter Object
// - Cell Formatting
// - Cell coordinates, Inserting, Moving and Removing cells, frozen cells
// - Methods for Windows messages


/////////////////////////////////////////////////////////////////////////////
// CGXGridCore construction/destruction

CGXGridCore::CGXGridCore(CWnd* pGridWnd, CDocument* pGridDoc, BOOL bIsViewContext)
{
#ifdef _DEBUG
	// Enable tracking of memory
	AfxEnableMemoryTracking(TRUE);
#endif  // _DEBUG
	
	m_pAppData = GXGetAppData();

	ASSERT(m_pAppData->m_bInitDone);
	// ASSERTION-> This constructor is called before the GXInit()
	// method has been called. This can be problematic because
	// at this time no factory object is available.
	//
	// Make sure you didn't simply forget to call GXInit() from
	// your application's InitInstance method. 
	//
	// Another reason for this problem can be that the object is 
	// constructed at the same time that your application object 
	// is instantiated, for example if you embedded this class 
	// as member variable in the application class. 
	// 
	// To resolve the problem we recommend you instantiate the
	// object on the heap. Change your class declaration and
	// declare a pointer to this class. After GXInit() has been
	// called you can call m_pGrid = new CGXGridCore. In your
	// class destructor don't forget to delete m_pGrid.
	// ->END

	// Pointer to window object
	m_pGridWnd			= pGridWnd;
	m_bIsViewContext	= bIsViewContext;
	m_pGridDoc			= pGridDoc;

	// Support for splitter windows
	m_pSplitterWnd	= NULL;
	m_nSplitRow		= 0;
	m_nSplitCol		= 0;
	m_pWndLastFocus = NULL;

	// Default control
	m_pDefaultControl = NULL;
	m_nLastControlHit = 0;
	m_pLastControlHit = NULL;

	// Parameter object
	m_pParam          = NULL;
	m_bOwnParam       = FALSE;

	// Topleft cell
	m_nTopRow = 1;
	m_nLeftCol = 1;

	// Current selection
	m_SelRectId = 0;

	// Grid window rectangle
	m_bRectDisplay	= FALSE;
	m_nZoom			= 100;

	// limit cell size so that it is not larger than
	// the grid area.
	m_bLimitRowHeight	= TRUE;
	m_bLimitColWidth	= TRUE;

	// used within a cell control to manage grid scrolling
	m_bScrollLockedFromCell		= FALSE;
	m_nLastSelectionFrameMarker = 0;

	// Active cell
	m_nEditRow					= 0;
	m_nEditCol					= 0;
	m_bActiveEditCell			= FALSE;
	m_bActiveFrame				= FALSE;
	m_bCacheCurrentCell			= TRUE;     // set this FALSE if you want to outline the current cell with special formattings
	m_bRefreshOnSetCurrentCell	= FALSE;
	// If your cells appearence is depending on whether
	// it is a current cell or not, you should set
	// m_bRefreshOnSetCurrentCell = TRUE. Otherwise
	// a smarter redrawing of the cell will be used.
	m_pCurrentCellControl	= NULL;
	m_bDropDownCell			= FALSE;

	// DBCS characters
	m_bDoubleByteChar = FALSE;

	// previous current cell coordinates (used by OnInitCurrentCell())
	m_nLastInitRow = GX_INVALID;
	m_nLastInitCol = GX_INVALID;

	m_dwButtonDownRow	= 1;
	m_dwButtonDownCol	= 1;
	m_dwLastMoveRow		= 1;
	m_dwLastMoveRow		= 1;

	// System Metrics
	m_dyBorder   = GetSystemMetrics(SM_CYBORDER);
	m_dxBorder   = GetSystemMetrics(SM_CXBORDER);
	m_dyFrame    = GetSystemMetrics(SM_CYFRAME);
	m_dxFrame    = GetSystemMetrics(SM_CXFRAME);

	// Update, hint
	m_bHintsEnabled = FALSE;
	m_nViewID		= 0;

	// Colors, pen styles
	m_psSelDragLine  = PS_DASH;

	// Cursor
	m_idcCursor = 0;

	// Display row/column header
	m_bDisplayHeaderRow = TRUE;
	m_bDisplayHeaderCol = TRUE;

	// Print
	m_bPrintInProgress = FALSE;
	m_nPrintTopRow = 1;
	m_nPrintLeftCol = 1;
	m_nPrintHandleRecordCount = gxCountPrint;
	m_bPrintCurSelOnly = FALSE;

	// States
	m_bOnlyValueNeeded		= FALSE;
	m_bNoValueNeeded		= FALSE;
	m_bDisableMouseMoveOver	= TRUE;
	m_nHitState				= 0;
	m_bEditBtnHit			= FALSE;
	m_bLockDrawSelectionFrame = FALSE;

	// Scrollbar
	m_bVertScrollBar			= TRUE;
	m_bHorzScrollBar			= TRUE;
	m_nLastSBRowCount			= 0;
	m_nLastSBColCount			= 0;
	m_bDoScrollNoUpdateWindow	= FALSE;

	// Draw using a memory dc (less flickering but slower)
	m_nDrawingTechnique = gxDrawDirectToDC;

	// Formula Engine support
	m_pDefaultDataClass			= RUNTIME_CLASS(CGXData);
	m_bRefreshOnlyUpdatedCells	= FALSE;
	m_bLockAddRecalcRange		= FALSE;
	m_nExpressionValueType		= m_pAppData->m_nExpressionValueType;	// formula engine will set this to GX_VALUE_EXPRESSION

	// Private members
	m_hcurArrow  = ::LoadCursor(NULL, IDC_ARROW);

	m_bAutoScroll			= FALSE;
	m_bAutoScrollStart		= FALSE;
	m_bAutoScrollStop		= FALSE;
	m_bSpeedKey				= FALSE;
	m_bAccelArrowKey		= FALSE;
	m_bAccelScrollbars		= FALSE;
	m_nAutoScrollDirection	= -1;
	m_bUpdateScrollbar		= FALSE;
	m_bLockedScrollbars		= FALSE;
	m_nVScrollSetting		= 0;
	m_nHScrollSetting		= 0;

	m_bInitDone		= FALSE;
	m_bTracking		= FALSE;
	m_bTrackMove	= FALSE;
	m_bCellHit		= FALSE;
	m_bSelDrag		= FALSE;
	m_pWndDrag		= NULL;
	m_nTrackingMode	= 0;

	m_nVScrollFactor = 2;
	m_nHScrollFactor = 2;

	m_nLastVisibleCol =
	m_nLastVisibleRow = GX_INVALID;

	m_cxOld = m_cyOld = 0;
	m_bLockResize = FALSE;
	m_bZoomed = FALSE;

	m_bValidatingCell		= FALSE;
	m_bLockActivateGrid		= FALSE;
	m_bLockCurrentCell		= FALSE;
	m_bWarningTextDisplayed = FALSE;
	m_bRefreshControl		= FALSE;
	m_bIgnoreFocus			= FALSE;
	m_bDrawCoveredCell		= FALSE;
	m_bForceDrawBackground	= FALSE;
	m_nNestedDraw			= 0;
	m_pDrawStruct			= NULL;
	m_bInvertRect			= FALSE;
	m_bForceOldDrawing		= FALSE;
	m_bLockEvalFloatCells	= FALSE;
	m_bLockEvalMergeCells	= FALSE;

	// Cache for styles created by LookupStyleRowCol
	m_nAltStylesRows	= 92;
	m_nAltStylesCols	= 64;
	m_nAltStylesCount	= m_nAltStylesRows*m_nAltStylesCols;
	m_nAltStylesColOffs = 16;
	m_nAltStylesRowOffs	= 16;

	m_papAltStyles = NULL;
	m_mapStyles.InitHashTable(257);     // prime number 

	// Grid Device Context
	m_pGridDC = NULL;
	m_hOldFont = 0;

	// Avoid freeing cells next time FreeObjectCache() is called
	m_nLockRow = m_nLockCol = 0;
	m_nLockRow2 = m_nLockCol2 = 0;
	m_bLockGDIObjects = FALSE;
	m_bLockStyleEdit = FALSE;

	// Buffered style - objects
	m_pStyleValue = NULL;
	m_pStyleGetValue = NULL;
	m_pStyleClass = NULL;
	m_pStyleEdit = NULL;

	// Standard styles
	m_pStyleStandard =
	m_pStyleRowHeader =
	m_pStyleColHeader = NULL;

	// Drag and Drop
#if _MFC_VER >= 0x0400 && !defined(_AFX_NO_OLE_SUPPORT)
	m_pOleDataSourceProxy	= NULL;
	m_nDndRowExt			= 0;
	m_nDndColExt			= 0;
	m_nRowsCopied			= 0;
	m_nColsCopied			= 0;
	m_nDndLastRow			= 0;
	m_nDndLastCol			= 0;
	m_nDndDropeffect		= 0;
	m_bDndGlobalTimer		= FALSE;
	m_dwDndDropTargetFlags	= GX_DNDEGDESCROLL | GX_DNDAUTOSCROLL | GX_DNDTEXT | GX_DNDSTYLES;
	m_bDndLastScrollCode2	= FALSE;
	m_nDndLastScrollCode	= 0;
	m_pRegDropTarget		= NULL;
#endif
	m_bHitTestSelEdge		= FALSE;
	m_nHitTestFrame			= 8;
	m_nDndFlags				= GX_DNDDISABLED;
	m_pCurrentCellControl	= NULL;
	// old settings
	// m_nClipboardFlags = GX_DNDCOLHEADER|GX_DNDROWHEADER
	//  |GX_DNDDIFFRANGEDLG|GX_DNDTEXT|GX_DNDSTYLES;

	// new settings: no col header, no row header, no "Diff Range" dialog
	m_nClipboardFlags = GX_DNDTEXT|GX_DNDSTYLES|GX_DNDCOMPOSE;

	// Tooltips
#if _MFC_VER >= 0x0400
	m_bTtnIsEnabled = FALSE;
	m_pTooltipProxy = NULL;
#endif

	m_pOldStyle = NULL;

	// Undo, Redo 
	m_pUndoImp		= NULL;
	m_bBlockCmd		= FALSE;
	m_bCellUndone	= FALSE;
	m_bLastFocus	= TRUE;

	m_nLastRow = 0;
	m_nLastCol = 0;
	m_sTransText.Empty();
	m_sEditRedo.Empty();
	m_sEditUndo.Empty();

	memset(&begin_component_ptr, 0, (&end_component_ptr-&begin_component_ptr)*sizeof(void*));

	CGXAbstractControlFactory* pControlFactory = m_pAppData->m_pControlFactory;
	if (pControlFactory && !m_bInitDone)
		pControlFactory->InitializeGridComponents(this);

	/*-------------------------------------------------------
	   DO NOT INITIALIZE IMPLEMENTATIONS TO NULL!
	   This has an adverse affect on cell behavior.
	---------------------------------------------------------
	   General grid components are initialized in the control
	   factory so that all grids in an application behave
	   similar. Refer to gxfactry.cpp and gxabstr.h 
	---------------------------------------------------------
	m_pPrintImp
	m_pSortImp
	m_pOldDrawingImp
	m_pCoveredCellsImp
	m_pDrawSpannedCellsImp
	m_pFloatCellsImp
	m_pMergeCellsImp
	m_pUndoImp
	m_pAbstractCalcSizeImp
	m_pUpdateHintImp
	m_pResizeToFitImp
	m_pHideCellsImp
	m_pFindReplaceImp
	m_pUserSelectRangeImp
	m_pExcelLikeFrameImp
	m_pExcelLikeFillImp
	m_pUserDragSelectRangeImp
	m_pMoveRowsColsImp
	m_pUserResizeCellsImp
	m_pOptimizedUpdateImp
	m_pMarkEditHeaderImp
	m_pFreezeMenuImp
	m_pDirectCopyMoveCellsImp
	m_pTextDataExchangeImp
	m_pStyleDataExchangeImp
	m_pCutPasteImp
	m_pClearCellsImp
	m_pRangeNameImp
	m_pOleDropTargetImp
	m_pOleDataSourceProxy
	-------------------------------------------------------*/

	// SRSTUDIO-1750 Initialized to 1 to avoid any divide by zero errors. 
	m_dyPrintHeight = 1;             
	m_dxPrintWidth  = 1; 
	m_dyHeight		= 1;
	m_dxWidth		= 1; 
}

CGXGridCore::~CGXGridCore()
{
#ifdef _CCHIT
	{
		TRACE0("Cells composed more than once:\n");
		LONG l;
		DWORD dw;
		POSITION pos = m_mapCellHit.GetStartPosition();
		while (pos)
		{
			m_mapCellHit.GetNextAssoc(pos, dw, l);
			if (l > 1)
				TRACE3("(%u,%u): %ld\n", GXDWordToRow(dw), GXDWordToCol(dw), l);
		}
	}
#endif

	ResetGrid();

#if _MFC_VER >= 0x0400
	// OLE data source
	GX_DELETE_CATCH<CGXNoOleDataSourceProxy>(m_pOleDataSourceProxy, _T("m_pOleDataSourceProxy"));

	// Tooltips
	GX_DELETE_CATCH<CGXNoToolTipCtrlProxy>(m_pTooltipProxy, _T("m_pTooltipProxy"));

#endif
	GX_DELETE_CATCH<CGXStyle>(m_pStyleValue, _T("m_pStyleValue"));
	GX_DELETE_CATCH<CGXStyle>(m_pStyleGetValue, _T("m_pStyleGetValue"));
	GX_DELETE_CATCH<CGXStyle>(m_pStyleEdit, _T("m_pStyleEdit"));

	// buffered style - objects
	m_pStyleClass = NULL;


	// Grid Local Data
	GXDeleteAllObjects(m_mapGridLocalData);

	
	//--------------
	// QA: 31521
	GX_DELETE_CATCH<CGXAbstractGridPrintImp>(m_pPrintImp, _T("m_pPrintImp"));
	GX_DELETE_CATCH<CGXAbstractGridSortImp>(m_pSortImp, _T("m_pSortImp"));
	GX_DELETE_CATCH<CGXAbstractGridOldDrawingImp>(m_pOldDrawingImp, _T("m_pOldDrawingImp"));
	GX_DELETE_CATCH<CGXAbstractGridCoveredCellsImp>(m_pCoveredCellsImp, _T("m_pCoveredCellsImp"));
	GX_DELETE_CATCH<CGXAbstractDrawSpannedCellsImp>(m_pDrawSpannedCellsImp, _T("m_pDrawSpannedCellsImp"));
	GX_DELETE_CATCH<CGXAbstractGridFloatCellsImp>(m_pFloatCellsImp, _T("m_pFloatCellsImp"));
	GX_DELETE_CATCH<CGXAbstractGridMergeCellsImp>(m_pMergeCellsImp, _T("m_pMergeCellsImp"));
	GX_DELETE_CATCH<CGXAbstractCommandFactory>(m_pUndoImp, _T("m_pUndoImp"));
	GX_DELETE_CATCH<CGXAbstractCalcSizeImp>(m_pAbstractCalcSizeImp, _T("m_pAbstractCalcSizeImp"));
	GX_DELETE_CATCH<CGXAbstractGridUpdateHintImp>(m_pUpdateHintImp, _T("m_pUpdateHintImp"));
	GX_DELETE_CATCH<CGXAbstractGridResizeToFitImp>(m_pResizeToFitImp, _T("m_pResizeToFitImp"));
	GX_DELETE_CATCH<CGXAbstractGridHideCellsImp>(m_pHideCellsImp, _T("m_pHideCellsImp"));
	GX_DELETE_CATCH<CGXAbstractGridFindReplaceImp>(m_pFindReplaceImp, _T("m_pFindReplaceImp"));
	GX_DELETE_CATCH<CGXAbstractGridUserSelectRangeImp>(m_pUserSelectRangeImp, _T("m_pUserSelectRangeImp"));
	GX_DELETE_CATCH<CGXAbstractGridExcelLikeFrameImp>(m_pExcelLikeFrameImp, _T("m_pExcelLikeFrameImp"));
	GX_DELETE_CATCH<CGXAbstractGridExcelLikeFillImp>(m_pExcelLikeFillImp, _T("m_pExcelLikeFillImp"));
	GX_DELETE_CATCH<CGXAbstractGridUserDragSelectRangeImp>(m_pUserDragSelectRangeImp, _T("m_pUserDragSelectRangeImp"));
	GX_DELETE_CATCH<CGXAbstractGridMoveRowsColsImp>(m_pMoveRowsColsImp, _T("m_pMoveRowsColsImp"));
	GX_DELETE_CATCH<CGXAbstractGridUserResizeCellsImp>(m_pUserResizeCellsImp, _T("m_pUserResizeCellsImp"));
	GX_DELETE_CATCH<CGXAbstractGridOptimizedUpdateImp>(m_pOptimizedUpdateImp, _T("m_pOptimizedUpdateImp"));
	GX_DELETE_CATCH<CGXAbstractGridMarkEditHeaderImp>(m_pMarkEditHeaderImp, _T("m_pMarkEditHeaderImp"));
	GX_DELETE_CATCH<CGXAbstractGridFreezeMenuHelperImp>(m_pFreezeMenuImp, _T("m_pFreezeMenuImp"));
	GX_DELETE_CATCH<CGXAbstractGridDirectCopyMoveCellsImp>(m_pDirectCopyMoveCellsImp, _T("m_pDirectCopyMoveCellsImp"));
	GX_DELETE_CATCH<CGXAbstractGridTextDataExchangeImp>(m_pTextDataExchangeImp, _T("m_pTextDataExchangeImp"));
	GX_DELETE_CATCH<CGXAbstractGridStyleDataExchangeImp>(m_pStyleDataExchangeImp, _T("m_pStyleDataExchangeImp"));
	GX_DELETE_CATCH<CGXAbstractGridCutPasteImp>(m_pCutPasteImp, _T("m_pCutPasteImp"));
	GX_DELETE_CATCH<CGXAbstractGridClearCellsImp>(m_pClearCellsImp, _T("m_pClearCellsImp"));
	GX_DELETE_CATCH<CGXAbstractGridRangeNameImp>(m_pRangeNameImp, _T("m_pRangeNameImp"));
	
	//if(m_pOleDropTargetImp) // Not allocated with "new"
	//{
	//	delete m_pOleDropTargetImp;
	//	m_pOleDropTargetImp = NULL;
	//}
	//if(m_pOleDataSourceProxy) // Not allocated with "new"
	//{
	//	delete m_pOleDataSourceProxy;
	//	m_pOleDataSourceProxy = NULL;
	//}
	//-------------------


	// QA: 31521
	POSITION pos = m_autodeleteptrlist.GetHeadPosition();
	void* p = NULL;
	while(pos)
	{
		p = m_autodeleteptrlist.GetNext(pos);
		// RWDN GX_DELETE_CATCH(p, _T("AutoDeletePtr"));
	}
	m_autodeleteptrlist.RemoveAll();
	// memset(&begin_component_ptr, 0, (&end_component_ptr-&begin_component_ptr)*sizeof(void*));

	// Plugins
	GXDeleteAllObjects(m_pluginList);

	// Style buffer
	int n = (int)m_StyleBuffer.GetCount();

	while (n-- > 0)
	{
		CGXStyle* pStyle = (CGXStyle*) m_StyleBuffer.RemoveHead();
		delete pStyle;
		pStyle = NULL;
	}

	if (m_papAltStyles)
	{
		for (unsigned w = 0; w < m_nAltStylesCount; w++)
		{
			CGXStyle* pStyle = (CGXStyle*) m_papAltStyles[w];
			delete pStyle;
			pStyle = NULL;
		}

		delete m_papAltStyles;
		m_papAltStyles = NULL;
	}

	{
		for (POSITION pos = m_mapStyles.GetStartPosition(); pos; )
		{
			CGXStyle* pStyle;
			GXNDX ndx;
			m_mapStyles.GetNextAssoc(pos, ndx, (CObject*&) pStyle);
			delete pStyle;
			pStyle = NULL;
		}

		m_mapStyles.RemoveAll();
	}

	if(m_pGridDC)
	{
		delete m_pGridDC;
		m_pGridDC = NULL;
	}

	m_pAppData->DetachGrid(this);
}

void CGXGridCore::ResetGrid()
{
	// destroy controls
	void* vptr = NULL;
	CGXControl* pControl;

	for (POSITION pos = m_ControlMap.GetStartPosition(); pos; )
	{
		m_ControlMap.GetNextAssoc(pos, vptr, (void*&) pControl);
		delete pControl;
		pControl = NULL;
	}

	m_ControlMap.RemoveAll();

	// cached objects
	FreeObjectCache();

	// Parameter Object
	if (m_bOwnParam)
	{
		delete m_pParam;
		m_pParam = NULL;
	}

	m_nLastControlHit = 0;
	m_pLastControlHit = NULL;
	if(m_pCurrentCellControl)
	{
		delete m_pCurrentCellControl;
		m_pCurrentCellControl = NULL;
	}
	if (m_pStyleValue) 
	{
		m_pStyleValue->Free();
	}
	if (m_pStyleGetValue) 
	{
		m_pStyleGetValue->Free();
	}
	if (m_pStyleEdit) 
	{
		m_pStyleEdit->Free();
	}
}

// Initialization of all associated objects

void CGXGridCore::OnGridInitialUpdate()
{
	WNDCLASS wcls;
	if (::GetClassInfo(AfxGetInstanceHandle(), _T("GXWND"), &wcls) == 0)
	{
		ASSERT(0);
		// ASSERTION-> Did you call GXInit() in the InitInstance method
		// of your application object? ->END
		AfxThrowNotSupportedException();
	}

	m_pAppData->m_bDiscardNcActivate = FALSE;

	POSITION pos = m_pluginList.GetHeadPosition();
	while (pos)
	{
		CGXPluginComponent* pComp = (CGXPluginComponent*) m_pluginList.GetNext(pos);
		pComp->PlugIn(m_pGridWnd);
	}

#if _MFC_VER >= 0x0400
	if (m_pTooltipProxy)
		m_pTooltipProxy->InitToolTip();
#endif

	// buffered style - objects
	if (m_pStyleValue == NULL)
		m_pStyleValue = CreateStyle();

	if (m_pStyleGetValue == NULL)
		m_pStyleGetValue = CreateStyle();

	m_pStyleClass = m_pStyleValue->GetRuntimeClass();

	if (m_pStyleEdit == NULL)
		m_pStyleEdit = CreateStyle();

	// check parameter object
	CGXGridParam* pParam = GetParam();

	if (pParam == NULL)
		SetParam(pParam = new CGXGridParam);

	m_pAppData->AttachGridToObject(pParam, this);

	FreeObjectCache();

	// check properties object
	if (pParam->GetProperties() == NULL)
	{
		// create a new one
		CGXProperties* pProperties = new CGXProperties;

		// Initialize it
		pProperties->AddDefaultUserProperties();
		
		if (m_pAppData->m_pGridProfileImp)
			pProperties->ReadProfile();

		// and connect it with the parameter object
		pParam->SetProperties(pProperties);

		// the parameter class will destroy the object
	}

	m_pAppData->AttachGridToObject(pParam->GetProperties(), this);

	// check styles
	if (pParam->GetStylesMap() == NULL)
	{
		CGXStylesMap* stylesmap = new CGXStylesMap(m_pStyleClass);
		stylesmap->CreateStandardStyles();
		if (m_pAppData->m_pGridProfileImp)
			stylesmap->ReadProfile();
		pParam->SetStylesMap(stylesmap);
	}

	m_pAppData->AttachGridToObject(pParam->GetStylesMap(), this);

	m_pStyleStandard  = NULL;
	m_pStyleRowHeader = NULL;
	m_pStyleColHeader = NULL;

	// Standard Styles
	CGXStylesMap* pStyMap = pParam->m_pStylesMap;

	VERIFY(pStyMap->LookupStyle(pStyMap->m_wStyleStandard, m_pStyleStandard));
	// ASSERTION-> standard styles not registered.
	// Did you call CGXStylesMap::CreateStandardStyles()? ->END

	VERIFY(pStyMap->LookupStyle(pStyMap->m_wStyleRowHeader, m_pStyleRowHeader));
	// ASSERTION-> standard styles not registered.
	// Did you call CGXStylesMap::CreateStandardStyles()? ->END

	VERIFY(pStyMap->LookupStyle(pStyMap->m_wStyleColHeader, m_pStyleColHeader));
	// ASSERTION-> standard styles not registered.
	// Did you call CGXStylesMap::CreateStandardStyles()? ->END

	ASSERT(m_pStyleStandard && m_pStyleColHeader && m_pStyleRowHeader);

	ASSERT_VALID(m_pStyleStandard);
	ASSERT_VALID(m_pStyleColHeader);
	ASSERT_VALID(m_pStyleRowHeader);

	// Register default control
	CGXAbstractControlFactory* pControlFactory = m_pAppData->m_pControlFactory;
	if (pControlFactory)
	{
		WORD nDefaultId = m_pStyleStandard->GetControl();
		CGXControl* pControl = pControlFactory->CreateControl(nDefaultId, this);
		if (pControl)
			RegisterControl(nDefaultId, pControl, TRUE /*  set default control */, FALSE);
	}

	// check data
#if _MFC_VER >= 0x0300
	ASSERT(m_pDefaultDataClass->IsDerivedFrom(RUNTIME_CLASS(CGXData)));
	// ASSERTION-> m_pDefaultDataClass must be derived from CCGXData ->END
#endif

	if (pParam->GetData() == NULL)
	{
		pParam->SetData((CGXData*) m_pDefaultDataClass->CreateObject());
		// m_pDefaultDataClass is CGXData by default 
		// or CGXFormulaSheet if EnableFormulaEngine has been called

		// Give CGXData a chance to adjust default parameter settings
		// (e.g. Formula Engine prefers direct copy/paste as default)
		pParam->GetData()->InitParam(pParam);
	}

	m_pAppData->AttachGridToObject(pParam->GetData(), this);

	pParam->m_bIsInit = TRUE;   // mark parameter object as initialized

	m_nZoom = pParam->m_pProperties->GetLastZoom();

	// calculate normal-text-font height and width
	GetDefaultFontSize(m_dxWidth, m_dyHeight);

	// mark as initialized
	m_bInitDone = TRUE;

	// set topleft cell
	m_nTopRow = max(GetFrozenRows()+1, m_nTopRow);
	m_nLeftCol = max(GetFrozenCols()+1, m_nLeftCol);

	// CGXTabWnd support
	if (m_pAppData->m_pTabWndInt)
		// Load sheet name from tabwindow if sheet-name is empty
		// or update tab beam if sheet-name is not empty
		m_pAppData->m_pTabWndInt->UpdateTabName(m_pGridWnd, pParam->m_sSheetName, !pParam->m_sSheetName.IsEmpty());

	// Sync current cell with existing views
	if (GetParam()->IsSyncCurrentCell()
		&& (GetColCount() >= GetParam()->m_nLastSyncEditCol)
		&& (GetRowCount() >= GetParam()->m_nLastSyncEditRow)
		)
	{
		ROWCOL nRow = GetParam()->m_nLastSyncEditRow;
		ROWCOL nCol = GetParam()->m_nLastSyncEditCol;

		StoreCurrentCell(TRUE, nRow, nCol);

		// update the record status beam
		UpdateRecordInfoWnd();
	}

	m_rgLastSelectionFrame.m_bValid = FALSE;
	if (!GetParam()->GetRangeList()->IsEmpty())
		m_rgLastSelectionFrame = *GetParam()->GetRangeList()->GetTail();

	m_pCurrentCellControl = NULL;

	UpdateFontMetrics();    // Actualizes the internally stored font metrics.
	UpdateScrollbars();     // Updates the scrollbars

	m_FloatCellData.Reset(this);
}

// CGXGridCore methods that will enable locale settings to be used for
// number formatting
void CGXGridCore::EnableLocaleNumbers()
{
	ASSERT(!GXGetAppData()->m_bFormulaEnabled);
	// not supported for the formula engine

	if(GXGetAppData()->m_bFormulaEnabled)
		return;

	GXGetAppData()->m_bLocaleNumbersEnabled = TRUE;
	GXGetAppData()->UpdateLocaleNumberSettings();
}

// parameter object

void CGXGridCore::SetParam(CGXGridParam* pParam, BOOL bMustDelete)
{
	if (pParam == NULL)
		pParam = new CGXGridParam;

	if (pParam == NULL)
		::AfxThrowMemoryException();

	ASSERT(pParam->IsKindOf(RUNTIME_CLASS(CGXGridParam)));
	ASSERT_VALID(pParam);

	if (m_pParam && m_bOwnParam)
	{
		delete m_pParam;
		m_pParam = NULL;
	}

	// Connect the parameter object
	m_pParam = pParam;
	m_bOwnParam = bMustDelete;
}

int CGXGridCore::GetViewID()
{
	return m_nViewID;
}

void CGXGridCore::EnableHints(BOOL b)
{ 
	m_bHintsEnabled = b;

#ifdef _DEBUG
	if (b)
		GX_CHECKIMP(m_pUpdateHintImp, "CGXGridCore::EnableHints");
#endif
}

// Client Area

void CGXGridCore::SetGridRect(BOOL bSet, LPRECT pRect /* = NULL*/)
{
	ASSERT(bSet == FALSE || pRect != NULL);
	// ASSERTION-> missing rect ->END

	m_bRectDisplay = bSet;
	if (pRect)
		m_rectDisplay = *pRect;
}

// Client Area depending on Printing or Display
CRect CGXGridCore::GetGridRect()
{
	CRect rect;

	if (m_bPrintInProgress)
		rect = m_rectPrint;
	else if (m_bRectDisplay)
		rect = m_rectDisplay;
	else
		m_pGridWnd->GetClientRect(&rect);

	if (rect.right < rect.left || rect.bottom < rect.top)
		rect.SetRect(0,0,0,0);

	return rect;
}

void CGXGridCore::SetPrinting(BOOL b, BOOL bClientToRect /* = FALSE */)
{
	if (b)
	{
		// Reset edit-mode for current cell
		ROWCOL nRow, nCol;
		if (GetCurrentCell(nRow, nCol))
		{
			CGXControl* pControl = GetControl(nRow, nCol);
			//if (pControl->GetModify())
			//  pControl->Store();
			if (pControl->IsActive())
				TransferCurrentCell();
			pControl->SetActive(FALSE);
		}
	}

	m_bPrintInProgress = b;

	if (bClientToRect)
	{
		// Initialize print attributes (see preview-window in print-settings-dialog)
		GetClientRect(m_rectPrint);
		GetDefaultFontSize(m_dxPrintWidth, m_dyPrintHeight);
		m_nPrintLeftCol = GetFrozenCols()+1;
		m_nPrintTopRow  = GetFrozenRows()+1;
	}

	// Initialize properties
	m_pParam->m_pProperties->SetPrinting(b);
}

CWnd* CGXGridCore::GetSharedScrollbarParentWnd() const
{
	CPtrList* pList = &m_pAppData->m_pSharedScrollBarRuntimeClassList;
	POSITION pos = pList->GetHeadPosition();
	CWnd* pWnd = NULL;
	while (pos && pWnd == NULL)
	{
		CRuntimeClass* pRuntimeClass = (CRuntimeClass*) pList->GetNext(pos);
		pWnd = GXGetParentWnd(m_pGridWnd, pRuntimeClass, TRUE);
	}

	return pWnd;
}

// Document
void CGXGridCore::SetModifiedFlag(BOOL bModified)
{
	// Setting the document dirty makes only sense, when the view is
	// linked to a document. If the view is linked to a document,
	// EnableHints(TRUE) should have been called.
	CDocument* pDoc = GetGridDoc();

	if (m_bHintsEnabled && pDoc != NULL)
		pDoc->SetModifiedFlag(bModified);
}


/////////////////////////////////////////////////////////////////////////////
// CGXGridCore diagnostics

#ifdef _DEBUG
void CGXGridCore::AssertValid() const
{
}

void CGXGridCore::Dump(CDumpContext& dc) const
{
// Current view
	AFX_DUMP1(dc, "\nm_nEditRow         = ", m_nEditRow);
	AFX_DUMP1(dc, "\nm_nEditCol         = ", m_nEditCol);
	AFX_DUMP1(dc, "\nm_nTopRow          = ", m_nTopRow);
	AFX_DUMP1(dc, "\nm_nLeftCol         = ", m_nLeftCol);
	AFX_DUMP1(dc, "\nm_nVScrollFactor   = ", m_nVScrollFactor);
	AFX_DUMP1(dc, "\nm_nHScrollFactor   = ", m_nHScrollFactor);

	AFX_DUMP1(dc, "\nm_bActiveFrame     = ", m_bActiveFrame);
	AFX_DUMP1(dc, "\nm_bActiveEditCell  = ", m_bActiveEditCell);

// Font
	AFX_DUMP1(dc, "\nm_dyHeight         = ", m_dyHeight);
	AFX_DUMP1(dc, "\nm_dxWidth          = ", m_dxWidth);

// Internal status variables
	AFX_DUMP1(dc, "\nm_bInitDone        = ", m_bInitDone);
	AFX_DUMP1(dc, "\nm_bDisplayHeaderRow = ", m_bDisplayHeaderRow);
	AFX_DUMP1(dc, "\nm_bDisplayHeaderCol = ", m_bDisplayHeaderCol);

// Print preview
	AFX_DUMP1(dc, "\nm_bPrintInProgress = ", m_bPrintInProgress);
	AFX_DUMP0(dc, "\nm_rectPrint        = ");
	dc << m_rectPrint;
	AFX_DUMP1(dc, "\nm_nPrintTopRow     = ", m_nPrintTopRow);
	AFX_DUMP1(dc, "\nm_nPrintLeftCol    = ", m_nPrintLeftCol);
	AFX_DUMP1(dc, "\nm_dyPrintHeight    = ", m_dyPrintHeight);
	AFX_DUMP1(dc, "\nm_dxPrintWidth     = ", m_dxPrintWidth);

	AFX_DUMP0(dc, "\nm_awPageFirstRow   = ");
	dc << m_awPageFirstRow;
	AFX_DUMP0(dc, "\nm_awPageFirstCol   = ");
	dc << m_awPageFirstCol;
	AFX_DUMP1(dc, "\nm_nCurrentPageRowIndex = ", m_nCurrentPageRowIndex);
	AFX_DUMP1(dc, "\nm_nCurrentPageColIndex = ", m_nCurrentPageColIndex);

// Parameter
	AFX_DUMP1(dc, "\nm_bOwnParam = ", m_bOwnParam);
	AFX_DUMP0(dc, "\nm_pParam = ");
	dc << m_pParam;

}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// internal mode

BOOL CGXGridCore::SetScrollLockedFromCell(BOOL b)
{
	BOOL bRet = m_bScrollLockedFromCell;
	m_bScrollLockedFromCell = b;
	return bRet;
}

BOOL CGXGridCore::IsScrollLockedFromCell()
{
	return m_bScrollLockedFromCell;
}


BOOL CGXGridCore::IsTracking(int* pnTrackingMode /*= NULL*/, ROWCOL* pnTracking /*= NULL*/)
{
	if (pnTrackingMode)
		*pnTrackingMode = m_nTrackingMode;
	if (pnTracking)
		*pnTracking = (m_nTrackingMode & GX_TRACKHEIGHT)
			? m_nRowTracking
			: m_nColTracking;
	return m_bTracking;
}

BOOL CGXGridCore::IsDragSelection(int* pnSelDragMode /*= NULL*/)
{
	if (pnSelDragMode)
		*pnSelDragMode = m_nSelDragMode;
	return m_bSelDrag;
}

BOOL CGXGridCore::IsSelectingCells()
{
	return m_nHitState > 0;
}

void CGXGridCore::SetReadOnly(BOOL bReadOnly)
{
	BOOL bOldReadOnly = IsReadOnly();

	if (StoreReadOnly(bReadOnly))
		UpdateReadOnly(bOldReadOnly, TRUE);
}

// ReadOnly

BOOL CGXGridCore::IsReadOnly()
{
	return m_pParam && m_pParam->m_bReadOnly;
}

BOOL CGXGridCore::StoreReadOnly(BOOL bReadOnly)
{
	ASSERT(m_pParam);
	m_pParam->m_bReadOnly = bReadOnly;
	return TRUE;
}

void CGXGridCore::UpdateReadOnly(BOOL bOldReadOnly, BOOL bCreateHint)
{
	ROWCOL nRow, nCol;
	CGXControl *pControl;
	if (GetCurrentCell(nRow, nCol) && (pControl = GetControl(nRow, nCol))->IsActive())
	{
		pControl->Reset();
		pControl->Init(nRow, nCol);
	}

	if (m_pUpdateHintImp && bCreateHint && m_bHintsEnabled)
		m_pUpdateHintImp->HintUpdateReadOnly(this, bOldReadOnly);
}

void CGXGridCore::AutoDeletePtr(void* p)
{
	m_autodeleteptrlist.AddHead(p);
}

#if _MFC_VER >= 0x0600
void CGXGridCore::ToolTipSetDelayTime(UINT nDelay)
{
   if (m_pTooltipProxy)
		((CGXToolTipCtrlProxy*)m_pTooltipProxy)->m_wndTtnToolTip.SetDelayTime(nDelay);
}

void CGXGridCore::ToolTipSetDelayTime(DWORD dwDuration, int iTime)
{
   if (m_pTooltipProxy)
		((CGXToolTipCtrlProxy*)m_pTooltipProxy)->m_wndTtnToolTip.SetDelayTime(dwDuration, iTime);
}

void CGXGridCore::ToolTipSetMaxTipWidth(int iWidth)
{
  if (m_pTooltipProxy)
		((CGXToolTipCtrlProxy*)m_pTooltipProxy)->m_wndTtnToolTip.SetMaxTipWidth(iWidth);
}

#endif
