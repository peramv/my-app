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

// gxabstr.h : interface of abstract base classes that have no implementation


#ifndef _GXABSTR_H_
#define _GXABSTR_H_

#ifndef _GXVER_H_
#include "grid\gxver.h"
#endif


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

// abstract base classes declared in this file
class CGXAbstractControlFactory;
class CGXAbstractTabWndInterface;
class CGXAbstractRecordInfoWndInterface;
class CGXAbstractCommandFactory;
class CGXNoOleDataObjectProxy;
class CGXNoOleDataSourceProxy;
class CGXAbstractGridDropTargetImp;
class CGXNoToolTipCtrlProxy;
class CGXAbstractGridSortImp;
class CGXAbstractGridSortMoveDataImp;
class CGXAbstractCalcSizeImp;
class CGXAbstractStyleCompareSubsetImp;
class CGXAbstractGridFloatCellsImp;
class CGXAbstractSpanCellPoolImp;
class CGXAbstractDelayedRangePoolImp;
class CGXAbstractGridCoveredCellsImp;
class CGXAbstractCoveredCellPoolImp;
class CGXAbstractGridMergeCellsImp;
class CGXAbstractDrawSpannedCellsImp;
class CGXAbstractGridFindReplaceImp;
class CGXAbstractGridPrintImp;
class CGXAbstractGridOldDrawingImp;
class CGXAbstractGridUpdateHintImp;
class CGXAbstractGridResizeToFitImp;
class CGXAbstractPrintDeviceImp;
class CGXAbstractGridHideCellsImp;
class CGXAbstractStyleSerializeImp;
class CGXAbstractSerializeOG5CompatibleImp;
class CGXAbstractGridDocSerializeImp;
class CGXAbstractGridProfileImp;
class CGXAbstractGridParamCopyOperatorImp;
class CGXAbstractGridUserSelectRangeImp;
class CGXAbstractGridExcelLikeFrameImp;
class CGXAbstractGridUserDragSelectRangeImp;
class CGXAbstractGridMoveRowsColsImp;
class CGXAbstractGridUserResizeCellsImp;
class CGXAbstractGridOptimizedUpdateImp;
class CGXAbstractDrawRotatedTextImp;
class CGXAbstractDateTimeImp;
class CGXAbstractGridMarkEditHeaderImp;
class CGXAbstractGridFreezeMenuHelperImp;
class CGXAbstractDataCopyMoveCellsImp;
class CGXAbstractGridDirectCopyMoveCellsImp;
class CGXAbstractGridTextDataExchangeImp;
class CGXAbstractGridStyleDataExchangeImp;
class CGXAbstractGridCutPasteImp;
class CGXAbstractGridClearCellsImp;
class CGXAbstractGridRangeNameImp;
class CGXAbstractLongOperationImp;
class CGXAbstractNumberFormattingImp;
class CGXAbstractGridExcelLikeFillImp;

// Display a warning if funtions are called that have no concrete 
// implementation.
// 

#ifdef _DEBUG

void AFXAPI GXCheckImp(void* pImp, LPCTSTR pszFunc);
void AFXAPI GXSetAssertNoImp(LPCTSTR pszFunc);

#define GX_CHECKIMP(pImp, pszFunc) GXCheckImp(pImp, _T(pszFunc))

#else

#define GX_CHECKIMP(pImp, pszFunc) 
#define GXSetAssertNoImp(pszFunc)

#endif

/////////////////////////////////////////////////////////////////////////////
// Control Factory

// forward declarations 
class CGXControl;
class CGXGridCore;
class CGXStylesMap;

class CGXAbstractControlFactory
{
public:
	virtual CGXControl* CreateControl(UINT nID, CGXGridCore* pGrid) = 0;
	virtual void RegisterAllControls(CGXStylesMap* pStylesMap) = 0;
	virtual void RegisterAllUserAttributes(CGXStylesMap* pStylesMap) = 0;
	virtual void InitializeGridComponents(CGXGridCore* pGrid) = 0;
	virtual void InitializeApplicationComponents() = 0;
	virtual void RegisterWndClasses(HINSTANCE hResource) = 0;
	virtual void UnregisterWndClasses(HINSTANCE hResource) = 0;
};

// You should derive your own CGXAbstractControlFactory and override
// the CreateControl method if you are concerned about the executable size
// of your application.
//
// If you have implemented a derived CGXAbstractControlFactory, you should
// call
//     GXInit(new CMyControlFactory)
// instead of GXInit()
// in your InitInstance method.


/////////////////////////////////////////////////////////////////////////////
// Support for tab window - Load or refresh worksheet name

class CGXAbstractTabWndInterface
{
public:
	virtual void UpdateTabName(const CWnd* pWnd, CString& sName, BOOL bUpdateBeam) = 0;
	virtual CString GetTabName(const CWnd* pWnd, int nTab) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Support for record info window 

// forward declarations 
class CGXGridCore;

class CGXAbstractRecordInfoWndInterface
{
public:
	virtual void UpdateRecordInfoWnd(CGXGridCore* pGrid) = 0;
	virtual void SetActivePane(CGXGridCore* pGrid) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Undo/Redo support 

// forward declarations 
class CGXRange;
class CGXStylesMap;
class CGXProperties;
class CGXStyle;
class CGXGridCore;
class CGXCommand;
class CGXLongOperation;

class CGXAbstractCommandFactory
{
public:
	virtual ~CGXAbstractCommandFactory();

	virtual CGXCommand* CreateBlockCmd(LPCTSTR s = NULL) = 0;
	virtual CGXCommand* CreateSetRowHeightCmd(ROWCOL nFromRow, ROWCOL nToRow, int* anHeightArray) = 0;
	virtual CGXCommand* CreateHideRowsCmd(ROWCOL nFromRow, ROWCOL nToRow, BOOL* abHide) = 0;
	virtual CGXCommand* CreateSetDefaultRowHeightCmd(int nHeight) = 0;
	virtual CGXCommand* CreateSetColWidthCmd(ROWCOL nFromCol, ROWCOL nToCol, int* anWidthArray) = 0;
	virtual CGXCommand* CreateHideColsCmd(ROWCOL nFromCol, ROWCOL nToCol, BOOL* abHide) = 0;
	virtual CGXCommand* CreateSetDefaultColWidthCmd(int nWidth) = 0;
	virtual CGXCommand* CreateMoveRowsCmd(ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow) = 0;
	virtual CGXCommand* CreateMoveColsCmd(ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nDestCol) = 0;
	virtual CGXCommand* CreateRemoveRowsCmd(ROWCOL nFromRow, ROWCOL nToRow) = 0;
	virtual CGXCommand* CreateRemoveColsCmd(ROWCOL nFromCol, ROWCOL nToCol) = 0;
	virtual CGXCommand* CreateInsertRowsCmd(ROWCOL nRow, ROWCOL nCount, int* anHeightArray, CObArray* pCellsArray, CObArray* pRowsArray, ROWCOL nColCount) = 0;
	virtual CGXCommand* CreateInsertColsCmd(ROWCOL nCol, ROWCOL nCount, int* anWidthArray, CObArray* pCellsArray, CObArray* pColsArray, ROWCOL nRowCount) = 0;
	virtual CGXCommand* CreateSetCoveredCellsCmd(ROWCOL nRow, ROWCOL nCol, ROWCOL nToRow, ROWCOL nToCol) = 0;
	virtual CGXCommand* CreateSetStyleRangeCmd(const CGXRange& range, int nType, CObArray* pCellsArray) = 0;
	virtual CGXCommand* CreateSetFrozenRowsCmd(ROWCOL nFrozenRows, ROWCOL nHeaderRows) = 0;
	virtual CGXCommand* CreateSetFrozenColsCmd(ROWCOL nFrozenCols, ROWCOL nHeaderCols) = 0;
	virtual CGXCommand* CreateMoveDataRowsCmd(const CGXRange& rangeSort, CRowColArray* pawRowIndex) = 0;
	virtual CGXCommand* CreateMoveDataColsCmd(const CGXRange& rangeSort, CRowColArray* pawColIndex) = 0;
	virtual CGXCommand* CreateChangeStylesMapCmd(const CGXStylesMap& stylesMap) = 0;
	virtual CGXCommand* CreateChangePropertiesCmd(const CGXProperties& Properties) = 0;
	virtual CGXCommand* CreateChangeBaseStyleCmd(WORD wStyleId, const CGXStyle& BaseStyle, const CString& sName) = 0;
	virtual CGXCommand* CreateMoveCellsCmd(const CGXRange& rg, ROWCOL nRow, ROWCOL nCol, CObject* pUndoInfo) = 0;
	virtual CGXCommand* CreateSetRangeNameCmd(CString name, BOOL bOldRange, const CGXRange& oldRange) = 0;
	virtual CGXCommand* CreateDeleteRangeNameCmd(CString name, const CGXRange& oldRange, CObject* pUndoInfo) = 0;
	
	virtual BOOL SetAdvancedUndo(CGXGridCore* pGrid, BOOL bAdvUndo) = 0;
	virtual CObject* GetAdvancedUndoInfo(CGXGridCore* pGrid) = 0;
	virtual BOOL UndoAdvanced(CGXGridCore* pGrid, CObject* pAdvUndo, BOOL bCreateUndoInfo, BOOL bOnlyToolCells) = 0;
	virtual void CleanAdvancedUndo(CGXGridCore* pGrid) = 0;
	virtual BOOL ExecuteCommand(CGXCommand* pCmd, CGXGridCore* pGrid, GXCmdType ctType) = 0;
	virtual void AddCommand(CGXGridCore* pGrid, CGXCommand* pCmd, GXCmdType ctCmd) = 0;
	virtual void RemoveCommand(CGXGridCore* pGrid, GXCmdType ctCmd) = 0;
	virtual BOOL Undo(CGXGridCore* pGrid) = 0;
	virtual BOOL Redo(CGXGridCore* pGrid) = 0;
	virtual void BeginTrans(CGXGridCore* pGrid, LPCTSTR s) = 0;
	virtual void CommitTrans(CGXGridCore* pGrid) = 0;
	virtual void Rollback(CGXGridCore* pGrid) = 0;
	virtual void OnCellUndone(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, BOOL bSetEdit) = 0;
	virtual BOOL CanUndo(CGXGridCore* pGrid, CCmdUI* pCmdUI) = 0;
	virtual BOOL CanRedo(CGXGridCore* pGrid, CCmdUI* pCmdUI) = 0;
	virtual BOOL CreateRemoveRowsUndoInfo(CGXGridCore* pGrid, ROWCOL& nFromRow, ROWCOL& nCount, ROWCOL& nColCount, CObArray*& pOldCellsArray, CObArray*& pOldRowsArray, CGXLongOperation& theOp) = 0;
	virtual BOOL CreateRemoveColsUndoInfo(CGXGridCore* pGrid, ROWCOL& nFromCol, ROWCOL& nCount, ROWCOL& nRowCount, CObArray*& pOldCellsArray, CObArray*& pOldRowsArray, CGXLongOperation& theOp) = 0;
};


/////////////////////////////////////////////////////////////////////////////
// CGXNoOleDataObjectProxy
//
// This abstract base class helps us to call functions from COleDataObject
// without having to statically link in all the OLE stuff.
//
// The OLE stuff will only be linked into the application when
// the programmer wants to add support for OLE Drag'n Drop and
// registers the grid with CGXGridDropTarget::Register().
//
// The base class version does not hold a COleDataObject. Only the
// derived CGXOleDataObjectProxy implements a COleDataObject.

class CGXNoOleDataObjectProxy;
class CGXAbstractGridDropTargetImp;
class CGXNoOleDataSourceProxy;

#if _MFC_VER >= 0x0400 && !defined(_AFX_NO_OLE_SUPPORT)

class CGXNoOleDataObjectProxy
{
public:
	virtual ~CGXNoOleDataObjectProxy();

	virtual BOOL GetData(CLIPFORMAT cfFormat, LPSTGMEDIUM lpStgMedium,
		LPFORMATETC lpFormatEtc = NULL) = 0;

	virtual BOOL IsDataAvailable(CLIPFORMAT cfFormat,
		LPFORMATETC lpFormatEtc = NULL) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// CGXNoOleDataSourceProxy
//

class COleDropSource;
class CGXNoOleDataSourceProxy;
class CGXRangeList;

class CGXNoOleDataSourceProxy
{
public:
	virtual ~CGXNoOleDataSourceProxy();

	// CacheData & DelayRenderData operations similar to ::SetClipboardData
	virtual void CacheGlobalData(CLIPFORMAT cfFormat, HGLOBAL hGlobal,
		LPFORMATETC lpFormatEtc = NULL) = 0;    // for HGLOBAL based data

	// Clipboard and Drag/Drop access
	virtual DROPEFFECT DoDragDrop(
		DWORD dwEffects = DROPEFFECT_COPY|DROPEFFECT_MOVE|DROPEFFECT_LINK,
		LPCRECT lpRectStartDrag = NULL,
		COleDropSource* pDropSource = NULL) = 0;

	virtual void Empty() = 0;   // empty cache (similar to ::EmptyClipboard)

	// CGXGridCore Overridables
	virtual BOOL DndStartDragDrop(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol) = 0;
	virtual BOOL OnDndCacheGlobalData(CGXGridCore* pGrid, CGXNoOleDataSourceProxy* pSrcItem, const CGXRangeList& selList, ROWCOL& nDndRowExt, ROWCOL& nDndColExt) = 0;
};

class CGXAbstractGridDropTargetImp
{
public:
	// GridCore overrides
	// overridables for drop target
	virtual BOOL OnDndCalculateFocusRect(CGXGridCore* pGrid, CGXNoOleDataObjectProxy* pOleDataObjectProxy, ROWCOL& nRowExt, ROWCOL& nColExt) = 0;
	virtual BOOL OnDndQueryAcceptData(CGXGridCore* pGrid, CGXNoOleDataObjectProxy* pDataObject) = 0;
	virtual BOOL OnDndDropData(CGXGridCore* pGrid, CGXNoOleDataObjectProxy* pDataObject, ROWCOL nRow, ROWCOL nCol) = 0;

	// support for drop target, functions called from CGXGridDropTarget
	virtual DROPEFFECT OnGridDragEnter(CGXGridCore* pGrid, CGXNoOleDataObjectProxy* pDataObject, DWORD dwKeyState, CPoint point) = 0;
	virtual DROPEFFECT OnGridDragOver(CGXGridCore* pGrid, CGXNoOleDataObjectProxy* pDataObject, DWORD dwKeyState, CPoint point) = 0;
	virtual void OnGridDragLeave(CGXGridCore* pGrid) = 0;
	virtual BOOL OnGridDrop(CGXGridCore* pGrid, CGXNoOleDataObjectProxy* pDataObject, DROPEFFECT dropEffect, CPoint point) = 0;
	virtual DROPEFFECT OnGridDropEx(CGXGridCore* pGrid, CGXNoOleDataObjectProxy* pDataObject, DROPEFFECT dropDefault, DROPEFFECT dropList, CPoint point) = 0;
	virtual DROPEFFECT OnGridDragScroll(CGXGridCore* pGrid, DWORD dwKeyState, CPoint point) = 0;

	// helpers for drop target
	virtual void DndDrawMoveRect(CGXGridCore* pGrid, CPoint point, BOOL bEraseOld, BOOL bDrawNew) = 0;
	virtual BOOL DoDragScroll(CGXGridCore* pGrid, CPoint point) = 0;
	virtual BOOL IsOverAnotherApplication(CGXGridCore* pGrid, POINT point) = 0;
};

#endif // _AFX_NO_OLE_SUPPORT

/////////////////////////////////////////////////////////////////////////////
// CGXNoToolTipCtrlProxy
//
// This abstract base class helps to call functions from CToolTipCtrl
// without having to statically link in tooltip code if the functionality
// is not wished.

class CGXNoToolTipCtrlProxy
{
public:
	virtual ~CGXNoToolTipCtrlProxy();

	// Will be called from CGXGridCore::OnGridPreTranslateMessage
	virtual void RelayEvent(LPMSG lpMsg) = 0;

	// Will be called from CGXGridCore::DoMouseMove
	virtual BOOL OnMouseMove(UINT flags, CPoint pt) = 0;

	// Will be called from CGXGridCore::DoSize
	virtual void UpdateTipArea() = 0;

	// Reset tips 
	virtual void Reset() = 0;

	// Will be called from OnInitialUpdate
	virtual BOOL InitToolTip() = 0;
};


/////////////////////////////////////////////////////////////////////////////
// Sorting the grid

class CGXGridCore;
class CGXControl;
struct CGXSortInfo;
class CGXSortInfoArray;
class CGXRange;

class CGXAbstractGridSortImp
{
public:
	// General
	virtual void SortKeys(CGXGridCore* pGrid, const CGXSortInfoArray& sortInfo, CPtrArray& sortKeyArray) = 0;

	// Rows
	virtual void SortRows(CGXGridCore* pGrid, CGXRange& sortRange, CGXSortInfoArray& sortInfo, UINT flags) = 0;
	virtual BOOL MoveDataRows(CGXGridCore* pGrid, const CGXRange& sortRange, const CRowColArray& awRowIndex, UINT flags, GXCmdType ctCmd) = 0;
	virtual BOOL StoreMoveDataRows(CGXGridCore* pGrid, const CGXRange& sortRange, const CRowColArray& awRowIndex) = 0;
	virtual void UpdateMoveDataRows(CGXGridCore* pGrid, const CGXRange& sortRange, UINT flags, BOOL bCreateHint) = 0;
	virtual void OnGetSortRowsKey(CGXGridCore* pGrid, ROWCOL nRow, const CGXSortInfoArray& sortInfo, CStringArray& keys) = 0;

	// Columns
	virtual void SortCols(CGXGridCore* pGrid, CGXRange& sortRange, CGXSortInfoArray& sortInfo, UINT flags) = 0;
	virtual BOOL MoveDataCols(CGXGridCore* pGrid, const CGXRange& sortRange, const CRowColArray& awColIndex, UINT flags, GXCmdType ctCmd) = 0;
	virtual BOOL StoreMoveDataCols(CGXGridCore* pGrid, const CGXRange& sortRange, const CRowColArray& awColIndex) = 0;
	virtual void UpdateMoveDataCols(CGXGridCore* pGrid, const CGXRange& sortRange, UINT flags, BOOL bCreateHint) = 0;
	virtual void OnGetSortColsKey(CGXGridCore* pGrid, ROWCOL nCol, const CGXSortInfoArray& sortInfo, CStringArray& keys) = 0;

	// Dbl Click on header
	virtual BOOL OnLButtonDblClkRowCol(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, UINT nFlags, CPoint pt) = 0;
};

class CGXData;

class CGXAbstractGridSortMoveDataImp
{
public:
	virtual BOOL StoreMoveDataRows(CGXData* pData, const CGXRange& sortRange, const CRowColArray& anRowIndex) = 0;
	virtual BOOL StoreMoveDataCols(CGXData* pData, const CGXRange& sortRange, const CRowColArray& anColIndex) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// CalcSize (needed by floating cells and resize to fit)

class CGXAbstractCalcSizeImp
{
public:
	virtual CSize CalcSize(CGXControl* pControl, CDC* pDC, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle, BOOL bVert) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// IsSubset (needed by merge cells and toolbar items in mygridvw, e.g. bold. italic etc.)

class CGXAbstractStyleCompareSubsetImp
{
public:
	virtual BOOL IsSubset(const CGXStyle* pStyle, const CGXStyle& p) = 0;
};


/////////////////////////////////////////////////////////////////////////////
// Floating Cells

class CGXSpanCellPool;
class CGXRange;
class CGXGridCore;
class CGXStyle;

class CGXAbstractGridFloatCellsImp
{
public:
	virtual void SetFloatCellsMode(CGXGridCore* pGrid, WORD nMode, BOOL bRedraw) = 0;
	virtual void DelayFloatCells(CGXGridCore* pGrid, const CGXRange& range, ROWCOL nMaxCols) = 0;
	virtual BOOL EvalFloatCells(CGXGridCore* pGrid, const CGXRange& range, BOOL bUpdate, CGXRange* prgBoundary, BOOL bLookupStyle) = 0;
	virtual CGXRange* GetFloatedCellsRowCol(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, CGXRange& range) = 0;
	virtual BOOL CanFloatCell(CGXGridCore* pGrid, CGXControl* pControl, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, BOOL bFloatOrFlood) = 0;
	virtual BOOL SetFloatedCellsRowCol(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, ROWCOL nToRow, ROWCOL nToCol, UINT flags) = 0;
	virtual void UpdateFloatedCellsRowCol(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, ROWCOL nOldToRow, ROWCOL nOldToCol, UINT flags, BOOL bCreateHint) = 0;
	virtual void MergeFloatedCells(CGXGridCore* pGrid, CGXRange& range) = 0;
	virtual BOOL CanFloatCell(CGXControl* pControl, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, BOOL bFloatOrFlood) = 0;
};

class CGXAbstractSpanCellPoolImp
{
public:
	virtual CGXSpanCellPool* CreateSpanCellPool() = 0;
	virtual CGXSpanCellPool* CreateSpanCellPool(const CGXSpanCellPool& src) = 0;
	virtual void CopySpanCellPool(CGXSpanCellPool& dest, const CGXSpanCellPool& src) = 0;
	virtual void InsertRows(CGXSpanCellPool* pPool, ROWCOL nRow, ROWCOL nCount) = 0;
	virtual void RemoveRows(CGXSpanCellPool* pPool, ROWCOL nFromRow, ROWCOL nToRow) = 0;
	virtual void MoveRows(CGXSpanCellPool* pPool, ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow) = 0;
	virtual void InsertCols(CGXSpanCellPool* pPool, ROWCOL nCol, ROWCOL nCount) = 0;
	virtual void RemoveCols(CGXSpanCellPool* pPool, ROWCOL nFromCol, ROWCOL nToCol) = 0;
	virtual void MoveCols(CGXSpanCellPool* pPool, ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nDestCol) = 0;
};

class CGXDelayedRangePool;

class CGXAbstractDelayedRangePoolImp
{
public:
	virtual CGXDelayedRangePool* CreateDelayedRangePool() = 0;
	virtual CGXDelayedRangePool* CreateDelayedRangePool(const CGXDelayedRangePool& src) = 0;
	virtual void CopyDelayedRangePool(CGXDelayedRangePool& dest, const CGXDelayedRangePool& src) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Covered Cells

class CGXCoveredCellPool;
class CGXRangeList;

class CGXAbstractGridCoveredCellsImp
{
public:
	virtual BOOL SetCoveredCellsRowCol(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, ROWCOL nToRow, ROWCOL nToCol, UINT flags, GXCmdType ctCmd) = 0;
	virtual CGXRange* GetCoveredCellsRowCol(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, CGXRange& range) = 0;
	virtual BOOL StoreCoveredCellsRowCol(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, ROWCOL nToRow, ROWCOL nToCol, BOOL bSet) = 0;
	virtual void UpdateCoveredCellsRowCol(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, ROWCOL nOldToRow, ROWCOL nOldToCol, UINT flags, BOOL bCreateHint) = 0;
	virtual void MergeCoveredCells(CGXGridCore* pGrid, CGXRange& range) = 0;
	virtual BOOL RemoveRows(CGXGridCore* pGrid, ROWCOL nFromRow, ROWCOL nToRow, UINT& flags, GXCmdType ctCmd) = 0;
	virtual BOOL RemoveCols(CGXGridCore* pGrid, ROWCOL nFromCol, ROWCOL nToCol, UINT& flags, GXCmdType ctCmd) = 0;
};

class CGXAbstractCoveredCellPoolImp
{
public:
	virtual CGXCoveredCellPool* CreateCoveredCellPool() = 0;
	virtual void InitFromRangeList(CGXCoveredCellPool*, CGXRangeList&) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Merge Cells

class CGXAbstractGridMergeCellsImp
{
public:
	virtual void SetMergeCellsMode(CGXGridCore* pGrid, WORD nMode, BOOL bRedraw) = 0;
	virtual void DelayMergeCells(CGXGridCore* pGrid, const CGXRange& range, ROWCOL nMaxRows, ROWCOL nMaxCols) = 0;
	virtual BOOL EvalMergeCells(CGXGridCore* pGrid, const CGXRange& range, BOOL bUpdate, CGXRange* prgBoundary, BOOL bLookupStyle) = 0;
	virtual CGXRange* GetMergedCellsRowCol(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, CGXRange& range, int mtType) = 0;
	virtual BOOL CanMergeCell(CGXGridCore* pGrid, CGXControl* pControl, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, int mtType) = 0;
	virtual BOOL CanMergeCells(CGXGridCore* pGrid, const CGXStyle& style1, const CGXStyle& style2) = 0;
	virtual BOOL SetMergedCellsRowCol(CGXGridCore* pGrid, int mtType, ROWCOL nRow, ROWCOL nCol, ROWCOL nToRow, ROWCOL nToCol, UINT flags) = 0;
	virtual void UpdateMergedCellsRowCol(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, ROWCOL nOldToRow, ROWCOL nOldToCol, UINT flags, BOOL bCreateHint) = 0;
	virtual void MergeMergedCells(CGXGridCore* pGrid, CGXRange& range) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Drawing for covered, merhe and floating Cells

class CGXAbstractDrawSpannedCellsImp
{
public:
	virtual BOOL OnDrawTLBR_LoadCell(CGXGridCore* pGrid, void* pds, unsigned nRow, unsigned nCol) = 0;
	virtual BOOL OnDrawTLBR_DrawCell(CGXGridCore* pGrid, void* pds, unsigned nRow, unsigned nCol) = 0;
	virtual BOOL EvalVisibleFloatMergeCells(CGXGridCore* pGrid, const CGXRange& range, ROWCOL nfr, ROWCOL nfc, ROWCOL nTopRow, ROWCOL nLefCol, ROWCOL nLastRow, ROWCOL nLastCol, BOOL bUpdate, CGXRange* prgBoundary, BOOL bLookupStyle) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Find&Replace

class CFindReplaceDialog;

struct GX_FR_STATE;

class CGXAbstractGridFindReplaceImp
{
public:
	virtual void OnShowFindReplaceDialog(CGXGridCore* pGrid, BOOL bFindOnly) = 0;
	virtual void OnFindNext(CGXGridCore * pGrid, LPCTSTR lpszFind, BOOL bNext, BOOL bCase) = 0;
	virtual BOOL FindText(CGXGridCore* pGrid, BOOL bSetCell) = 0;
	virtual void OnReplaceSel(CGXGridCore* pGrid, LPCTSTR lpszFind, BOOL bNext, BOOL bCase, LPCTSTR lpszReplace) = 0;
	virtual void OnReplaceAll(CGXGridCore* pGrid, LPCTSTR lpszFind, LPCTSTR lpszReplace, BOOL bCase) = 0;
	virtual void OnFindReplace(CGXGridCore* pGrid, CFindReplaceDialog* pDialog) = 0;
	virtual BOOL FindText(CGXGridCore* pGrid, ROWCOL& nRow, ROWCOL& nCol, BOOL bSetCell) = 0;
	virtual BOOL FindText(CGXControl* pControl, const GX_FR_STATE& find, ROWCOL nRow, ROWCOL nCol, BOOL bCurrentPos, BOOL bSetCell) = 0;
	virtual BOOL ReplaceAll(CGXControl* pControl, const GX_FR_STATE& find, ROWCOL nRow, ROWCOL nCol) = 0;
};


//////////////////////////////////////////////////////////////////////////////
// Printing

class CGXGridParam;
class CGXProperties;
class CGXData;

class CGXAbstractGridPrintImp
{
public:
	virtual void OnGridBeginPrinting(CGXGridCore* pGrid, CDC* pDC, CPrintInfo* pInfo) = 0;
	virtual void OnGridPrint(CGXGridCore* pGrid, CDC* pDC, CPrintInfo* pInfo) = 0;
	virtual void OnGridEndPrinting(CGXGridCore* pGrid, CDC* pDC, CPrintInfo* pInfo) = 0;

	virtual void OnPrintHeaderAndFooter(CGXProperties* pProp, CDC* pDC, CPrintInfo* pInfo, CDocument* pDoc, CGXGridParam* pParam) = 0;
	virtual int CalculateHeight(CGXProperties* pProp, CDC* pDC, CGXData &data, CGXStylesMap* pStylesMap) = 0;
	virtual void PrintHeaderFooter(CGXProperties* pProp, CDC* pDC, CPrintInfo* pInfo, CRect& rect, CGXData& data, CGXStylesMap* pStylesMap) = 0;
	virtual CString ParseText(CGXProperties* pProp, LPCTSTR sz) = 0;
	virtual CString SubstTokenText(CGXProperties* pProp, int nToken, CString& sRest) = 0;
	virtual CString GetTokenArgs(CGXProperties* pProp, CString& sRest) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Old Drawing (with clipping)
// Ole drawing might be necessary if you have custom cell types that don't 
// take care on clipping themselves in Draw method.
// - Or -
// If you are using the CGXGridParam::m_bTransparentBackground setting


class CGXAbstractGridOldDrawingImp
{
public:
	virtual BOOL OnDrawTLBR(CGXGridCore* pGrid, CDC* pDC, void* pds) = 0;
	virtual void OnDrawTLBR_DrawBackground(CGXGridCore* pGrid, void* pds) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Update hint Mechanism

class CGXAbstractGridUpdateHintImp
{
public:
	virtual void OnGridUpdate(CGXGridCore * pGrid, CObject* pHint) = 0;
	virtual void HintUpdateReadOnly(CGXGridCore* pGrid, BOOL bOldReadOnly) = 0;
	virtual void HintSetCurrentCell(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, UINT flags) = 0;
	virtual BOOL HintTransferCurrentCell(CGXGridCore* pGrid, BOOL bSaveAndValidate, UINT flags) = 0;
	virtual void HintUpdateChangedRowCount(CGXGridCore* pGrid, ROWCOL nOldRows, UINT flags) = 0;
	virtual void HintUpdateChangedColCount(CGXGridCore* pGrid, ROWCOL nOldCols, UINT flags) = 0;
	virtual void HintUpdateFrozenCols(CGXGridCore* pGrid, ROWCOL nOldFrozenCols, ROWCOL nOldHeaderCols, UINT flags) = 0;
	virtual void HintUpdateFrozenRows(CGXGridCore* pGrid, ROWCOL nOldFrozenRows, ROWCOL nOldHeaderRows, UINT flags) = 0;
	virtual void HintSetTopRow(CGXGridCore* pGrid, ROWCOL nRow, UINT flags) = 0;
	virtual void HintSetLeftCol(CGXGridCore* pGrid, ROWCOL nCol, UINT flags) = 0;
	virtual void HintUpdateInsertRows(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCount, UINT flags) = 0;
	virtual void HintUpdateInsertCols(CGXGridCore* pGrid, ROWCOL nCol, ROWCOL nCount, UINT flags) = 0;
	virtual void HintRedrawRowCol(CGXGridCore* pGrid, ROWCOL nStartRow, ROWCOL nStartCol, ROWCOL nEndRow, ROWCOL nEndCol, UINT flags) = 0;
	virtual void HintRedraw(CGXGridCore* pGrid, UINT flags) = 0;
	virtual void HintRefreshViews(CGXGridCore* pGrid, CString* pErrorStr) = 0;
	virtual void HintOnTabChanged(CGXGridCore* pGrid, int nTab) = 0;
	virtual void HintOnAutoScroll(CGXGridCore* pGrid, int direction, ROWCOL nCell) = 0;
	virtual void HintUpdateSelectRange(CGXGridCore* pGrid, const CGXRange& range, const CGXRangeList* pOldRangeList) = 0;
	virtual void HintLockSelectionFrame(CGXGridCore* pGrid, BOOL bLock) = 0;
	virtual void HintPrepareChangeSelection(CGXGridCore* pGrid, POSITION oldPos, ROWCOL top, ROWCOL left, ROWCOL bottom, ROWCOL right) = 0;
	virtual void HintPrepareClearSelection(CGXGridCore* pGrid) = 0;
	virtual void HintUpdateChangedRowHeights(CGXGridCore* pGrid, ROWCOL nFromRow, ROWCOL nToRow, int* nOldHeights, UINT flags) = 0;
	virtual void HintUpdateChangedColWidths(CGXGridCore* pGrid, ROWCOL nFromCol, ROWCOL nToCol, int* nOldWidths, UINT flags) = 0;
	virtual void HintStoreZoom(CGXGridCore* pGrid, int nZoom) = 0;
	virtual void HintUpdateZoom(CGXGridCore* pGrid, int nOldZoom, UINT flags) = 0;
	virtual void HintUpdateStyleRange(CGXGridCore* pGrid, const CGXRange& range, const CGXStyle* pStyle, GXModifyType mt, int nType, UINT flags) = 0;
	virtual void HintUpdateStylesMap(CGXGridCore* pGrid, UINT flags) = 0;
	virtual void HintUpdateProperties(CGXGridCore* pGrid, UINT flags) = 0;
	virtual void HintUpdateBaseStyle(CGXGridCore* pGrid, WORD wStyleId, UINT flags) = 0;
	virtual void HintUpdateCoveredCellsRowCol(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, ROWCOL nOldToRow, ROWCOL nOldToCol, UINT flags) = 0;
	virtual void HintUpdateFloatedCellsRowCol(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, ROWCOL nOldToRow, ROWCOL nOldToCol, UINT flags) = 0;
	virtual void HintUpdateMergedCellsRowCol(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, ROWCOL nOldToRow, ROWCOL nOldToCol, UINT flags) = 0;
	virtual void HintUpdateMoveDataRows(CGXGridCore* pGrid, const CGXRange& sortRange, UINT flags) = 0;
	virtual void HintUpdateMoveDataCols(CGXGridCore* pGrid, const CGXRange& sortRange, UINT flags) = 0;
	virtual void HintUpdateRemoveRows(CGXGridCore* pGrid, ROWCOL nFromRow, ROWCOL nToRow, int* anOldHeights, UINT flags) = 0;
	virtual void HintUpdateRemoveCols(CGXGridCore* pGrid, ROWCOL nFromCol, ROWCOL nToCol, int* anOldWidths, UINT flags) = 0;
	virtual void HintUpdateMoveRows(CGXGridCore* pGrid, ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow, UINT flags) = 0;
	virtual void HintUpdateMoveCols(CGXGridCore* pGrid, ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nDestCol, UINT flags) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Resize cells to fit contents

class CGXAbstractGridResizeToFitImp
{
public:
	virtual BOOL ResizeRowHeightsToFit(CGXGridCore* pGrid, CGXRange& range, BOOL bResizeCoveredCells, UINT nFlags) = 0;
	virtual BOOL ResizeColWidthsToFit(CGXGridCore* pGrid, CGXRange& range, BOOL bResizeCoveredCells, UINT nFlags) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Printer settings (landscape, portrait, paper format etc.)

class CGXPrintDevice;

class CGXAbstractPrintDeviceImp
{
public:
	virtual void UpdatePrinterDevice(CGXPrintDevice* pd) = 0;
	virtual int DoPrintDialog(CGXPrintDevice* pDevice, CPrintDialog* pPD) = 0;
	virtual BOOL DoPreparePrinting(CView* pView, CGXPrintDevice* pDevice, CPrintInfo* pInfo) = 0;
	virtual void CreateDeviceHandles(CGXPrintDevice* pDevice, LPDEVNAMES pDevNames, DWORD cbSizeDevNames, LPDEVMODE pDevMode, DWORD cbSizeDevMode) = 0;
	virtual void CreateDeviceHandles(CGXPrintDevice* pDevice, HGLOBAL hDN, HGLOBAL hDM) = 0;
	virtual void DestroyDeviceHandles(CGXPrintDevice* pDevice) = 0;
	virtual void GetDeviceInfo(CGXPrintDevice* pDevice, HGLOBAL hDN, HGLOBAL hDM, LPDEVNAMES& pDevNames, DWORD &cbSizeDevNames, LPDEVMODE& pDevMode, DWORD& cbSizeDevMode) = 0;
	virtual void GetDefaults(CGXPrintDevice* pDevice) = 0;
	virtual HDC GetPrintDC(CGXPrintDevice* pDevice) = 0;
	virtual void ResetPrintDC(CGXPrintDevice* pDevice) = 0;
	virtual void CopyDeviceHandles(CGXPrintDevice* pDevice, HGLOBAL& hDN, HGLOBAL& hDM) = 0;
	virtual BOOL CompareDeviceHandles(CGXPrintDevice* pDevice, LPDEVNAMES pDevNames, DWORD cbSizeDevNames, LPDEVMODE pDevMode, DWORD cbSizeDevMode) = 0;
	virtual BOOL CompareDeviceHandles(CGXPrintDevice* pDevice, HGLOBAL hDN, HGLOBAL hDM) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Hiding cells 

class CGXAbstractGridHideCellsImp
{
public:
	virtual void RemoveRows(CGXGridCore* pGrid, ROWCOL nFromRow, ROWCOL nToRow) = 0;
	virtual void RemoveCols(CGXGridCore* pGrid, ROWCOL nFromCol, ROWCOL nToCol) = 0;
	virtual void InsertRows(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCount) = 0;
	virtual void InsertCols(CGXGridCore* pGrid, ROWCOL nCol, ROWCOL nCount) = 0;
	virtual void MoveRows(CGXGridCore* pGrid, ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow) = 0;
	virtual void MoveCols(CGXGridCore* pGrid, ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nDestCol) = 0;
	virtual BOOL HideRows(CGXGridCore* pGrid, ROWCOL nFromRow, ROWCOL nToRow, BOOL bHide, BOOL* abHideArray, UINT flags, GXCmdType ctCmd) = 0;
	virtual BOOL IsRowHidden(CGXGridCore* pGrid, ROWCOL nRow) = 0;
	virtual BOOL StoreHideRow(CGXGridCore* pGrid, ROWCOL nRow, BOOL bHide) = 0;
	virtual BOOL HideCols(CGXGridCore* pGrid, ROWCOL nFromCol, ROWCOL nToCol, BOOL bHide, BOOL* abHideArray, UINT flags, GXCmdType ctCmd) = 0;
	virtual BOOL IsColHidden(CGXGridCore* pGrid, ROWCOL nCol) = 0;
	virtual BOOL StoreHideCol(CGXGridCore* pGrid, ROWCOL nCol, BOOL bHide) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Serialize style objects

struct CGXPen;
struct CGXBrush;
class CGXFont;
class CGXStyle;

class CGXAbstractStyleSerializeImp
{
public:
	virtual void Serialize(CGXStyle* pStyle, CArchive& ar, const CGXStylesMap* pStylesMap) = 0;
	virtual void Serialize(CGXPen& lp, CArchive& ar) = 0;
	virtual void Serialize(CGXBrush& lb, CArchive& ar) = 0;
	virtual void Serialize(CGXFont* pFont, CArchive &ar) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Read style objects serialized with OG 5.0 or earlier

class CGXAbstractSerializeOG5CompatibleImp
{
public:
	virtual void SerializeOG5Map(CGXStyle* pStyle, CArchive& ar) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Serialize parameter, properties, stylesmap etc.

class CGXGridParam;
class CGXProperties;
class CGXStylePtrArray;
class CGXStylePtrArrayPtrArray;
class CGXData;
class CGXStylesMap;

class CGXAbstractGridDocSerializeImp
{
public:
	virtual void Serialize(CGXGridParam* pParam, CArchive& ar) = 0;
	virtual void Serialize(CGXProperties* pProp, CArchive& ar) = 0;
	virtual void Serialize(CGXStylePtrArray* pArray, CArchive& ar) = 0;
	virtual void Serialize(CGXStylePtrArrayPtrArray* pArray, CArchive& ar) = 0;
	virtual void Serialize(CGXData* pData, CArchive& ar) = 0;
	virtual void Serialize(CGXStylesMap* pStyMap, CArchive& ar) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Write styles, property settings to/from profile/registry

class CGXAbstractGridProfileImp
{
public:
	virtual void WriteProfile(const CGXProperties* pProp) = 0;
	virtual BOOL ReadProfile(CGXProperties* pProp) = 0;
	virtual void WriteProfile(const CGXStyle* pStyle, LPCTSTR pszSection, const CGXStylesMap* pStylesMap) = 0;
	virtual BOOL ReadProfile(CGXStyle* pStyle, LPCTSTR pszSection, const CGXStylesMap* pStylesMap) = 0;
	virtual void WriteProfile(const CGXFont* pFont, LPCTSTR pszSection, LPCTSTR pszEntry) = 0;
	virtual BOOL ReadProfile(CGXFont* pFont, LPCTSTR pszSection, LPCTSTR pszEntry) = 0;
	virtual BOOL ReadProfile(CGXStylesMap* pStyMap) = 0;
	virtual void WriteProfile(const CGXStylesMap* pStyMap) = 0;
};


/////////////////////////////////////////////////////////////////////////////
// Copy parameter object (operator= support)

class CGXAbstractGridParamCopyOperatorImp
{
public:
	virtual void CopyObject(CGXProperties* pDest, const CGXProperties& p) = 0;
	virtual void CopyObject(CGXStylesMap* pDest, const CGXStylesMap& p) = 0;
	virtual void CopyObject(CGXGridParam* pDest, const CGXGridParam& p) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Allow user to select range of cells in grid with mouse

class CGXAbstractGridUserSelectRangeImp
{
public:
	virtual BOOL MoveCurrentCellEx(CGXGridCore* pGrid, int direction, UINT nCell) = 0;
	virtual void OnLButtonDown(CGXGridCore* pGrid, CPoint& point, UINT& flags, int& ht, ROWCOL& nRow, ROWCOL& nCol) = 0;
	virtual BOOL OnMouseMove(CGXGridCore* pGrid, CPoint& point, UINT& flags, ROWCOL& nRow, ROWCOL& nCol) = 0;
	virtual void OnLButtonUp(CGXGridCore* pGrid, CPoint& point, UINT& flags) = 0;
	virtual void SelectRange(CGXGridCore* pGrid, const CGXRange& range, BOOL bSelect /* = TRUE */, BOOL bUpdate ) = 0;
	virtual BOOL StoreSelectRange(CGXGridCore* pGrid, const CGXRange& range, BOOL bSelect) = 0;
	virtual void UpdateSelectRange(CGXGridCore* pGrid, const CGXRange& range, const CGXRangeList* pOldRangeList, BOOL bCreateHint) = 0;
	virtual void SetSelection(CGXGridCore* pGrid, POSITION pos, ROWCOL nTop, ROWCOL nLeft, ROWCOL nBottom, ROWCOL nRight) = 0;
	virtual void PrepareChangeSelection(CGXGridCore* pGrid, POSITION oldPos, ROWCOL top, ROWCOL left, ROWCOL bottom, ROWCOL right, BOOL bCreateHint) = 0;
	virtual void PrepareClearSelection(CGXGridCore* pGrid, BOOL bCreateHint) = 0;
	virtual BOOL OnLButtonClickedRowCol(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, UINT nFlags, CPoint pt) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Excel-like selection frame

class CGXAbstractGridExcelLikeFrameImp
{
public:
	virtual void DrawInvertFrame(CGXGridCore* pGrid, CDC* pDC, const CRect& rc, const CRect& rectClip, BOOL bTopVisible, BOOL bLeftVisible, int nMarker, BOOL bOnlyMarker) = 0;
	virtual void DrawSelectionRangeFrame(CGXGridCore* pGrid, CDC* pDC, const CGXRange& rg, int nMarker, BOOL bOnlyMarker) = 0;
	virtual void DrawSelectionFrame(CGXGridCore* pGrid, CDC* pDC, BOOL bDrawOld, const CGXRange* pNewRange) = 0;
	virtual void ToggleSelectionFrameMarker(CGXGridCore* pGrid) = 0;
	virtual BOOL LockSelectionFrame(CGXGridCore* pGrid, BOOL bLock, BOOL bCreateHint) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Drag select rows and columns (and rearrange row/column order)

class CGXAbstractGridUserDragSelectRangeImp
{
public:
	virtual BOOL OnLButtonDown(CGXGridCore* pGrid, CPoint& point, UINT& flags, int& ht, ROWCOL& nRow, ROWCOL& nCol) = 0;
	virtual BOOL OnMouseMove(CGXGridCore* pGrid, CPoint& point, UINT& flags) = 0;
	virtual BOOL OnLButtonUp(CGXGridCore* pGrid, CPoint& point, UINT& flags) = 0;
	virtual BOOL OnSelDragStart(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol) = 0;
	virtual BOOL OnSelDragMove(CGXGridCore* pGrid, ROWCOL nRow1, ROWCOL nCol1, ROWCOL nRow, ROWCOL nCol) = 0;
	virtual BOOL OnSelDragDrop(CGXGridCore* pGrid, ROWCOL nRow1, ROWCOL nCol1, ROWCOL nRow, ROWCOL nCol) = 0;
	virtual void OnSelDragCancel(CGXGridCore* pGrid) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// rearrange row/column order API (MoveRows, MoveCols methods)

class CGXAbstractGridMoveRowsColsImp
{
public:
	virtual BOOL StoreMoveRows(CGXGridCore* pGrid, ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow, BOOL bProcessed) = 0;
	virtual void UpdateMoveRows(CGXGridCore* pGrid, ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow, UINT flags, BOOL bCreateHint) = 0;
	virtual BOOL StoreMoveCols(CGXGridCore* pGrid, ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nDestCol, BOOL bProcessed) = 0;
	virtual void UpdateMoveCols(CGXGridCore* pGrid, ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nDestCol, UINT flags, BOOL bCreateHint) = 0;
	virtual BOOL MoveRows(CGXGridCore* pGrid, ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow, UINT flags, GXCmdType ctCmd) = 0;
	virtual BOOL MoveCols(CGXGridCore* pGrid, ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nDestCol, UINT flags, GXCmdType ctCmd) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// allow user to resize rows or columns with mouse

class CGXAbstractGridUserResizeCellsImp
{
public:
	virtual BOOL OnMouseMove(CGXGridCore* pGrid, CPoint& point, UINT& flags) = 0;
	virtual BOOL OnLButtonDown(CGXGridCore* pGrid, CPoint& point, UINT& flags, int& ht, ROWCOL& nRow, ROWCOL& nCol) = 0;
	virtual BOOL OnLButtonUp(CGXGridCore* pGrid, CPoint& point, UINT& flags) = 0;
	virtual BOOL OnLButtonDblClk(CGXGridCore* pGrid, CPoint& point, UINT& flags, int& ht, ROWCOL& nRow, ROWCOL& nCol) = 0;
	virtual BOOL OnStartTracking(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, int nTrackingMode) = 0;
	virtual void OnMoveTracking(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, int nTrackingMode, CSize &size) = 0;
	virtual void OnCancelTracking(CGXGridCore* pGrid) = 0;
	virtual void OnEndTracking(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, int nTrackingMode, CSize& size) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Optimized update for inserting, removing rows and columns and for changing 
// row and column size.

class CGXAbstractGridOptimizedUpdateImp
{
public:
	virtual void UpdateInsertRows(CGXGridCore* pGrid, ROWCOL& nRow, ROWCOL& nCount, UINT& flags) = 0;
	virtual void UpdateInsertCols(CGXGridCore* pGrid, ROWCOL& nCol, ROWCOL& nCount, UINT& flags) = 0;
	virtual void UpdateRemoveRows(CGXGridCore* pGrid, ROWCOL& nFromRow, ROWCOL& nToRow, int* anOldHeights, UINT flags) = 0;
	virtual void UpdateRemoveCols(CGXGridCore* pGrid, ROWCOL& nFromCol, ROWCOL& nToCol, int* anOldWidths, UINT& flags) = 0;
	virtual void UpdateChangedRowHeights(CGXGridCore* pGrid, ROWCOL& nFromRow, ROWCOL& nToRow, int* nOldHeights, UINT& flags) = 0;
	virtual void UpdateChangedColWidths(CGXGridCore* pGrid, ROWCOL& nFromCol, ROWCOL& nToCol, int* nOldWidths, UINT& flags) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Draw rotated text in cells (CGXStyle::SetOrientation)

class CGXAbstractDrawRotatedTextImp
{
public:
	virtual int GXDrawRotatedText(CDC* pDC, LPCTSTR lpszString, int nCount, CRect rc, UINT nFormat, LONG lfOrientation, LPRECT lpClipRect) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Date/Time parsing and formatting (OG offers concrete classes for OleDateTime
// and NoOleDateTime)

enum GXDateFormat { gxDDMMYY, gxMMDDYY, gxYYMMDD, gxDEFAULT };
typedef struct tagTIMESTAMP_STRUCT TIMESTAMP_STRUCT;

class CGXAbstractDateTimeImp
{
public:
	virtual void UpdateDateTimeSettings() = 0;
	virtual GXDateFormat GetDateFormatFromWinIni(BOOL bReload, BOOL& bCentury, TCHAR& chDateSep) = 0;
	virtual TCHAR GetTimeSeparatorFromWinIni(BOOL bReload) = 0;
	virtual BOOL ParseDateTime(struct tm* ptm, LPCTSTR szValue, GXDateFormat DateFormat) = 0;
	virtual BOOL ParseDateTime(TIMESTAMP_STRUCT* ptm, LPCTSTR szValue, GXDateFormat DateFormat) = 0;
	virtual void FormatTimeStamp(CString& strRet, const CTime* pTime) = 0;
	virtual void FormatTimeStamp(CString& strRet, const TIMESTAMP_STRUCT* pTime) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Outline row and column header for current cell

class CGXAbstractGridMarkEditHeaderImp
{
public:
	virtual void MarkEdit(CGXGridCore* pGrid, ROWCOL nEditRow, ROWCOL nEditCol, UINT direction, UINT flags) = 0;
	virtual BOOL GetMarkHeaderState(CGXControl* pControl, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Freeze rows and columns

class CGXAbstractGridFreezeMenuHelperImp
{
public:
	virtual BOOL CanFreezeCols(CGXGridCore* pGrid) = 0;
	virtual BOOL CanUnfreezeCols(CGXGridCore* pGrid) = 0;
	virtual void FreezeCols(CGXGridCore* pGrid) = 0;
	virtual void UnfreezeCols(CGXGridCore* pGrid) = 0;
	virtual BOOL CanFreezeRows(CGXGridCore* pGrid) = 0;
	virtual BOOL CanUnfreezeRows(CGXGridCore* pGrid) = 0;
	virtual void FreezeRows(CGXGridCore* pGrid) = 0;
	virtual void UnfreezeRows(CGXGridCore* pGrid) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Direct copying and moving of cells

class CGXAbstractDataCopyMoveCellsImp
{
public:
	virtual BOOL StoreCopyCells(CGXData* pData, CGXRange rg, ROWCOL nRow, ROWCOL nCol) = 0;
	virtual BOOL StoreMoveCells(CGXData* pData, CGXRange& rg, ROWCOL nRow, ROWCOL nCol, CObject*& pUndoInfo, BOOL bCreateUndoInfo, int ctCmd) = 0;
};

class CGXAbstractGridDirectCopyMoveCellsImp
{
public:
	virtual BOOL CopyCells(CGXGridCore* pGrid, CGXRange& rg, ROWCOL nRow, ROWCOL nCol, UINT flags) = 0;
	virtual BOOL StoreCopyCells(CGXGridCore* pGrid, CGXRange& rg, ROWCOL nRow, ROWCOL nCol) = 0;
	virtual BOOL MoveCells(CGXGridCore* pGrid, CGXRange& rg, ROWCOL nRow, ROWCOL nCol, CObject* pUndoInfo, UINT flags, GXCmdType ctCmd) = 0;
	virtual BOOL StoreMoveCells(CGXGridCore* pGrid, CGXRange& rg, ROWCOL nRow, ROWCOL nCol, CObject*& pUndoInfo, BOOL bCreateUndo, GXCmdType ctCmd) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Text data exchange (clipboard and text files)

class CGXAbstractGridTextDataExchangeImp
{
public:
	virtual BOOL CopyTextToFile(CGXGridCore* pGrid, CFile& destFile, const CGXRangeList& selList) = 0;
	virtual CString GetCopyTextRowCol(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol) = 0;
	virtual BOOL PasteTextFromBuffer(CGXGridCore* pGrid, LPCTSTR psz, DWORD size, const CGXRange& range) = 0;
	virtual BOOL PasteTextRowCol(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, const CString& str, UINT nFlags, const CGXStyle* pOldStyle) = 0;
	virtual BOOL CalcBufferDimension(CGXGridCore* pGrid, LPCTSTR psz, DWORD size, ROWCOL& nRows, ROWCOL& nCols) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Style data exchange (clipboard and binary resources, files and og designer files)

class CGXAbstractGridStyleDataExchangeImp
{
public:
	virtual BOOL CopyCellsToArchive(CGXGridCore* pGrid, CArchive& ar, const CGXRangeList& selList, BOOL bLoadBaseStyles) = 0;
	virtual BOOL GetClipboardStyleRowCol(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, CGXStyle* pStyle, BOOL bLoadBaseStyles) = 0;
	virtual BOOL PasteCellsFromArchive(CGXGridCore* pGrid, CArchive& ar, const CGXRange& range, BOOL bIgnoreDiffRange) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Cut, Copy and Paste clipboard support

class CGXAbstractGridCutPasteImp
{
public:
	virtual BOOL CanCopy(CGXGridCore* pGrid) = 0;
	virtual BOOL Copy(CGXGridCore* pGrid) = 0;
	virtual BOOL CopyRange(CGXGridCore* pGrid, const CGXRangeList& selList) = 0;
	virtual BOOL CopyTextToClipboard(CGXGridCore* pGrid, const CGXRangeList& selList) = 0;
	virtual BOOL CopyCellsToClipboard(CGXGridCore* pGrid, const CGXRangeList& selList, BOOL bLoadBaseStyles) = 0;
	virtual BOOL CanCut(CGXGridCore* pGrid) = 0;
	virtual BOOL Cut(CGXGridCore* pGrid) = 0;
	virtual BOOL CutRange(CGXGridCore* pGrid, const CGXRangeList& selList, BOOL bStyleOrValue) = 0;
	virtual BOOL CanPaste(CGXGridCore* pGrid) = 0;
	virtual BOOL OnCheckClipboardFormat(CGXGridCore* pGrid) = 0;
	virtual BOOL Paste(CGXGridCore* pGrid) = 0;
	virtual BOOL OnPasteDirect(CGXGridCore* pGrid, const CGXRange& range) = 0;
	virtual BOOL OnPasteFromClipboard(CGXGridCore* pGrid, const CGXRange& rg) = 0;
	virtual BOOL OnPasteDiffRange(CGXGridCore* pGrid) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Clear cells support

class CGXAbstractGridClearCellsImp
{
public:
	virtual BOOL CanClear(CGXGridCore* pGrid) = 0;
	virtual BOOL Clear(CGXGridCore* pGrid, BOOL bStyleOrValue) = 0;
	virtual BOOL ClearCells(CGXGridCore* pGrid, const CGXRangeList& selList, BOOL bStyleOrValue) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Named Ranges (used for formula support only)

class CGXAbstractGridRangeNameImp
{
public:
	virtual BOOL SetRangeName(CGXGridCore* pGrid, LPCTSTR name, const CGXRange& rg, CObject* pUndoInfo, UINT flags, GXCmdType ctCmd) = 0;
	virtual BOOL GetRangeName(CGXGridCore* pGrid, LPCTSTR name, CGXRange& rg) = 0;
	virtual BOOL DeleteRangeName(CGXGridCore* pGrid, LPCTSTR name, CObject* pUndoInfo, GXCmdType ctCmd) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// CGXLongOperation support

class CGXAbstractLongOperationImp
{
public:
	virtual void Start(CGXLongOperation* pTheOp) = 0;
	virtual void Stop(CGXLongOperation* pTheOp) = 0;
	virtual void FreeStatusText(CGXLongOperation* pTheOp) = 0;
	virtual void SetStatusText(CGXLongOperation* pTheOp, LPCTSTR pszText, BOOL bCopyBuffer) = 0;
	virtual BOOL DoMessages(CGXLongOperation* pTheOp) = 0;
	virtual BOOL DoMessages(CGXLongOperation* pTheOp, BOOL& bAbort) = 0;
	virtual void ProcessMessages(CGXLongOperation* pTheOp) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Number formatting support for numeric cells

class CGXAbstractNumberFormattingImp
{
public:
	// Text formatting and parsing
	virtual CString GXFormatText(const CGXStyle& style, LPCTSTR pszValue, unsigned nValueType, CGXGridCore* pGrid, CGXControl* pControl) = 0;
	virtual BOOL GXDeval(LPCTSTR s, double *d, unsigned* pImportFormat, unsigned* pImportPlaces) = 0;
};

/////////////////////////////////////////////////////////////////////////////
// Excel like fill implementation

class CGXAbstractGridExcelLikeFillImp
{
public:
	virtual void OnLButtonDown(CGXGridCore* pGrid, CPoint& point, UINT& flags, int& ht, ROWCOL& nRow, ROWCOL& nCol) = 0;
	virtual BOOL OnMouseMove(CGXGridCore* pGrid, CPoint& point, UINT& flags, ROWCOL& nRow, ROWCOL& nCol) = 0;
	virtual void OnLButtonUp(CGXGridCore* pGrid, CPoint& point, UINT& flags) = 0;
	virtual void ClearCurrentDragRect(CGXGridCore* pGrid) = 0;
	virtual void DrawDragRect(CGXGridCore* pGrid, CGXRange& rect, BOOL bEraseOld, BOOL bDrawNew) = 0;
	virtual void FillRect(CGXGridCore* pGrid, CGXRange& nFrom, CGXRange& nTo) = 0;
	virtual void OnAutoFillDone(CGXGridCore* pGrid, CGXRange& rFinal) = 0;
};



/////////////////////////////////////////////////////////////////////////////
// Inline function declarations

#ifdef _GX_ENABLE_INLINES

// inlines

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


#endif //_GXABSTR_H_
