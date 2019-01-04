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

// gxbrowse.h : header file
//

#ifndef _GXBROWSE_H_
#define _GXBROWSE_H_

#ifndef _GXCORE_H_
#include "grid\gxcore.h"
#endif

// DECLARE_REGISTER

#ifndef _GXEXT_H_
#include "grid\gxext.h"
#endif

// CGXControl

#ifndef _GXCTRL_H_
#include "grid\gxctrl.h"
#endif

// CGXView

#ifndef _GXVIEW_H_
#include "grid\gxview.h"
#endif

// Verify that include path is correct

#if ! ( defined(_GX_VER) && _GX_VER >= 0x0903 )
#pragma message( "Please make sure that you include Objective Grid 9.03 header files")
#pragma message( "and not old header files!")
Fatal error!
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

// header file

class CGXBrowserGrid;

/////////////////////////////////////////////////////////////////////////////
// CGXBrowseGridArrowRowHeader control

class CGXBrowseGridArrowRowHeader : public CGXControl
{
public:
	CGXBrowseGridArrowRowHeader(CGXBrowserGrid* pODBCGrid);

	// event handler
	virtual void Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle);

// Attributes
public:
	CBitmap m_bmPencil;
	CBitmap m_bmStar;
	CBitmap m_bmArrow;
	CGXBrowserGrid* m_pBrowserGrid;
	BOOL m_bWin95Look;
};

/////////////////////////////////////////////////////////////////////////////
// CGXRecSetInfo 

class CGXRecSetInfo : public CObject
{
	DECLARE_SERIAL(CGXRecSetInfo)

public:
	CGXRecSetInfo();

	//serialization
	virtual void Serialize(CArchive& ar);

// Attributes
	CString m_strSource;          // query string
	CString m_strSqlQuery;        // query string
	CString m_strConnectString;   // connect string
};

/////////////////////////////////////////////////////////////////////////////
// CGXBrowseDirtyFieldStruct
//
// holds changed values for the current record

class CGXAbstractBlob;

struct CGXBrowseDirtyFieldStruct
{
	// changed fields
	BOOL bDirty;
	CString sValue;

	CGXAbstractBlob* pAttribute;

	CGXBrowseDirtyFieldStruct();
	~CGXBrowseDirtyFieldStruct();
};


////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// class CGXOleViewer
///////////////////////////////////////////////////////////////////////////////////////////////
// Viewer for ole objects
class CGXOleViewer
{
public:
	CGXOleViewer();
	virtual ~CGXOleViewer();

// overrides:
	// This can spawn an external viewer etc
	virtual void Render(const CGXStyle* pStyle, CGXGridCore* pGrid, CGXControl* pCtrl,  BOOL bShow = TRUE) = 0;

	// Activate an existing viewer
	virtual void ActivateExisting() = 0;

	// No rendering....simple access and return
	virtual HGLOBAL AccessData(const CGXStyle* pStyle, CGXGridCore* pGrid, CGXControl* pCtrl) = 0;

	// This should close any external viewer etc
	virtual void Close();
	
	virtual void OnModify();

	virtual void Clear() = 0;
	
	virtual void SaveFromStorage() = 0;
	
	virtual COleVariant& GetData() = 0;
	
	virtual LPSTORAGE GetStorage() = 0;

	virtual LPOLEOBJECT GetOleObject() = 0;

	virtual IOleClientSite* GetClientSite() = 0;

// clipboard support
	
	virtual BOOL CanPaste() = 0;

	virtual COleVariant* Paste() = 0;

	virtual BOOL CanCopy() = 0;
	
	virtual IDataObject* Copy(const CGXStyle* pStyle, CGXGridCore* pGrid, CGXControl* pCtrl) = 0;
	
	virtual BOOL CanCut() = 0;
	
	virtual IDataObject* Cut(const CGXStyle* pStyle, CGXGridCore* pGrid, CGXControl* pCtrl) = 0;


//access 
	CGXControl* GetActiveControl();
	void SetActiveControl(CGXControl* pControl);

//data
	CGXControl* m_pControl;
};

/////////////////////////////////////////////////////////////////////////////
// CGXBrowseParam
//
// holds all CGXBrowserGrid-specific data. This data can be
// shared among several CGXBrowserGrid-derived views so
// that the document/view architecture can be supported.
//

class CGXBrowseParam: public CGXGridParam
{
	DECLARE_SERIAL(CGXBrowseParam)

public:
	// Attributes
	BOOL m_bAllowPasteMultiCells;
		// Set this TRUE if you want to allow the user to paste
		// multiple lines of text into the grid. 
		// If FALSE OG will only paste into the current cell (default)

	BOOL m_bCanStoreGridCellInCGXData;
		// TRUE if any cell data can be directly stored in CGXData
		// FALSE if only headers can stored in CGXData
		// CGXDaoGrid and CGXODBCGrid initialize m_bCanStoreGridCellInCGXData = FALSE
		// The default value is TRUE.

	int  m_nMaxColWidth;            // holds the maximum col width in characters

	BOOL m_bCanAppend;              // Set this member FALSE if you want to disable appending rows

	BOOL m_bUpdateOnStore;          // TRUE when Update shall be called
	BOOL m_bDoReplaceAll;           // TRUE when OnReplaceAll is called

	BOOL m_bIsBrowseInit;           // TRUE when one-time initialization is done

	// moving columns / sorting rows
	CRowColArray
		m_awRowIndex,
		m_awColIndex;

	// Current record - internal buffer with changed values
	CGXBrowseDirtyFieldStruct* m_paDirtyFieldStruct;

	short m_nFields;                // number of fields in the bound data source (recordset)

	UINT m_nEditMode;               // current mode

	ROWCOL m_nCurrentRow;           // currently edited row

	CGXStyle* m_pTmpStyle;          // temporary style object


	// Record count
	BOOL m_bEOFSeen;                // set this member FALSE if you don't
									// know the exact record count.

	long m_nRecordLastSeen;         // Last seen record will be used to
		// determine the record count when OnGetRecordCount()
		// returns LONG_MAX

// Record count, currently only CGXDaoGrid and CGXODBCGrid use this members
	long
		m_nRecordCount,             // can be used by derived classes
		// m_nRecordCount has no meaning for this base class
		m_nRecordCountInc;          // can be used by derived classes
		// m_nRecordCount has no meaning for this base class

// Caching, currently only CGXDaoGrid takes advantage of this
	long m_nCacheSize;      // specify -1 for no caching
	ROWCOL m_nRowCacheStart;

	// Display wait cursor when moving more than the
	// specified number of records in the recordset.
	long
		m_lMoveRecordWaitCursor;

// Implementation
public:
	CGXBrowseParam();
	virtual ~CGXBrowseParam();
	virtual void Serialize(CArchive& ar);
	virtual CGXBrowseParam& operator=(const CGXBrowseParam& p);

//added for record information 
public:
	//operation
	CObject* m_pRecSetInfo;
	CGXRecSetInfo* GetRecSetInfo();
	void CreateRecSetInfo(CRuntimeClass* pClass = NULL);
};

/////////////////////////////////////////////////////////////////////////////
// CGXAbstractBlob
/////////////////////////////////////////////////////////////////////////////

// Has no data. Just implements a generic interface for cleanup. Data will be added
// to derived members as required
class CGXAbstractBlob 
{
public:
	CGXAbstractBlob();
	virtual ~CGXAbstractBlob();
	virtual void Cleanup(BOOL bDestruct = FALSE) = 0;
};


/////////////////////////////////////////////////////////////////////////////
// CGXBrowserGrid
//
// base class for browsing external data sources

class CGXBrowserGrid: public CGXGridCore
{
public:
// Construction
	CGXBrowserGrid(CWnd* pGridWnd = NULL, CDocument* pGridDoc = NULL, BOOL bIsViewContext = FALSE);

// Attributes
public:
	CGXBrowseParam* GetBrowseParam();

	enum EditMode { noMode, edit, addnew };

	// maximum col width
	void SetMaxColWidth(int nChar);
	int GetMaxColWidth();

	// records
	ROWCOL GetFirstRow();
	void SetCanAppend(BOOL b);

	BOOL IsOnLastRecord();
	BOOL IsOnFirstRecord();

	// Record state
	BOOL IsRecordDirty();
	long GetRecordFromRow(ROWCOL nRow);

	// Fields
	short GetFieldFromCol(ROWCOL nCol);

public:
	// Overridables - State members
	virtual BOOL CanUpdate();
	virtual BOOL CanAppend();
	virtual long OnGetRecordCount();

	virtual ROWCOL GetAppendRow();
	virtual ROWCOL GetLastRow();

	// Overridables - Operations
	virtual void DeleteRecords();
	virtual void DeleteRows(const CRowColArray& awRowStart, const CRowColArray& awRowEnd, BOOL* pbSuccess = NULL);
	virtual void Requery();
	virtual BOOL MoveTo(ROWCOL nRow);

	// Wrapper methods for DeleteRows (not overridable)
	void DeleteRows(ROWCOL nFromRow, ROWCOL nToRow);
	void DeleteRows(const CGXRange& range);

	// Overridables - Changing records
	virtual void Edit(ROWCOL nRow);
	virtual ROWCOL AddNew();
	virtual BOOL Update(CString* ps = NULL);
	virtual void UndoRecord();
	virtual void CancelRecord();

	// Overridables - Row/Column dereferencing
	virtual ROWCOL GetRowIndex(ROWCOL nRow);
	virtual ROWCOL GetColIndex(ROWCOL nCol);

	// binary data support
	virtual void GetOleViewerRowCol(ROWCOL nRow, ROWCOL nCol, DWORD dwId, CGXOleViewer*& pViewer ) const;
protected:
	// Overridables - Events
	virtual void OnAddedNewRecord();

	virtual void OnFillCache();
	virtual void InitBrowserSettings();

	// Overridables - Load cell styles and flush values
	virtual BOOL OnLoadCellStyle(ROWCOL nRow, ROWCOL nCol, CGXStyle& style, LPCTSTR pszExistingValue);

	virtual void OnFlushCellValue(ROWCOL nRow, ROWCOL nCol, LPCTSTR pszChangedValue);
	
	virtual void OnFlushBlobValue(ROWCOL nRow, ROWCOL nCol, CGXAbstractBlob* pAttribute);
	
	virtual BOOL OnFlushRecord(ROWCOL nRow, CString* ps = NULL);
	
	virtual BOOL SetBinaryFlags(const CGXStyle* pStyle, int nField);

		// NOTE: You should override the previous members instead
		// of GetStyleRowCol/StoreStyleRowCol. They provide a better
		// abstraction for loading/storing cell values in a CGXBrowserGrid

		// The methods will be called appropriately from within CGXBrowserGrid::Update(),
		// CGXBrowserGrid::GetStyleRowCol, CGXBrowserGrid::StoreStyleRowCol and
		// CGXBrowserGrid::SetStyleRange

	// Overridables - Sorting 
public:
	virtual void SortRows(CGXRange sortRange, CGXSortInfoArray& sortInfo, UINT flags = GX_UPDATENOW);
	virtual void SortCols(CGXRange sortRange, CGXSortInfoArray& sortInfo, UINT flags = GX_UPDATENOW);

protected:
	virtual BOOL StoreMoveDataRows(const CGXRange& sortRange, const CRowColArray& awRowIndex);
	virtual BOOL StoreMoveDataCols(const CGXRange& sortRange, const CRowColArray& awColIndex);

public:
	// called when text is pasted into cell
	virtual BOOL SetControlTextRowCol(ROWCOL nRow, ROWCOL nCol, const CString& str, UINT nFlags = GX_UPDATENOW, const CGXStyle* pOldStyle = NULL);

// Implementation - Menu handlers
protected:
	BOOL OnMove(UINT nIDMoveCommand);
	void OnUpdateRecordFirst(CCmdUI* pCmdUI);
	void OnUpdateRecordPrev(CCmdUI* pCmdUI);
	void OnUpdateRecordNext(CCmdUI* pCmdUI);
	void OnUpdateRecordLast(CCmdUI* pCmdUI);
	void OnUpdateEditUndorecord(CCmdUI* pCmdUI);
	void OnEditUndorecord();
	void OnRecordDelete();
	void OnUpdateRecordDelete(CCmdUI* pCmdUI);

// Implementation - CGXGridCore Overridables
public:
	virtual void OnGridInitialUpdate();
	virtual void OnGridDraw(CDC* pDC);
	virtual ROWCOL GetRowCount();
	virtual BOOL GetStyleRowCol(ROWCOL nRow, ROWCOL nCol, CGXStyle& style, GXModifyType mt = gxCopy, int nType = 0);
	virtual BOOL StoreStyleRowCol(ROWCOL nRow, ROWCOL nCol, const CGXStyle* pStyle, GXModifyType mt = gxOverride, int nType = 0);
	virtual BOOL ProcessKeys(CWnd* pSender, UINT nMessage, UINT nChar, UINT nRepCnt = 1, UINT flags = 0);
	virtual BOOL OnGridKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL CanSelectCurrentCell(BOOL bSelect, ROWCOL dwSelectRow, ROWCOL dwSelectCol, ROWCOL dwOldRow, ROWCOL dwOldCol);
	virtual void OnModifyCell(ROWCOL nRow, ROWCOL nCol);
	virtual BOOL SetStyleRange(const CGXRange& range, const CGXStyle* pStyle, GXModifyType mt, int nType = 0, const CObArray* pCellsArray = NULL, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);
	virtual void OnCanceledEditing(ROWCOL nRow, ROWCOL nCol);
	virtual void OnMovedCurrentCell(ROWCOL nRow, ROWCOL nCol);
	virtual BOOL OnLeftCell(ROWCOL nRow, ROWCOL nCol, ROWCOL nNewRow, ROWCOL nNewCol);
	virtual BOOL CanChangeSelection(CGXRange* range, BOOL bIsDragging, BOOL bKey);
	virtual BOOL SetCurrentCell(ROWCOL nRow, ROWCOL nCol, UINT flags = GX_SCROLLINVIEW | GX_UPDATENOW);
	virtual BOOL Undo();
	virtual BOOL Paste();
	virtual BOOL Cut();
	virtual BOOL CanCut();
	virtual BOOL CanPaste();

	virtual void OnReplaceSel(LPCTSTR lpszFind, BOOL bNext, BOOL bCase, LPCTSTR lpszReplace);
	virtual void OnReplaceAll(LPCTSTR lpszFind, LPCTSTR lpszReplace, BOOL bCase);

	#if _MFC_VER >= 0x0400
	BOOL OnGridDrop(CGXNoOleDataObjectProxy* pDataObject, DROPEFFECT dropEffect, CPoint point);
	#endif

	BOOL ClearCells(const CGXRange& range, BOOL bStyleOrValue = TRUE);
	virtual BOOL ClearCells(const CGXRangeList& selList, BOOL bStyleOrValue);
	virtual BOOL PasteTextFromBuffer(LPCTSTR psz, DWORD size, const CGXRange& range);

// Implementation - Rearrange the column indexes when one of the following events happen
	virtual BOOL StoreMoveCols(ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nDestCol, BOOL bProcessed = FALSE);
	virtual BOOL StoreInsertCols(ROWCOL nCol, ROWCOL nCount, BOOL bProcessed = FALSE);
	virtual BOOL StoreRemoveCols(ROWCOL nFromCol, ROWCOL nToCol, BOOL bProcessed = FALSE);

	// Rearrange the row indexes when one of the following events happen
	virtual BOOL StoreMoveRows(ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow, BOOL bProcessed = FALSE);
	virtual BOOL StoreInsertRows(ROWCOL nRow, ROWCOL nCount, BOOL bProcessed = FALSE);
	virtual BOOL StoreRemoveRows(ROWCOL nFromRow, ROWCOL nToRow, BOOL bProcessed = FALSE);

	// These special RemoveRows / RemoveCols implementations do not support undo!
	virtual BOOL RemoveRows(ROWCOL nFromRow, ROWCOL nToRow, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);
	virtual BOOL RemoveCols(ROWCOL nFromCol, ROWCOL nToCol, UINT flags = GX_UPDATENOW, GXCmdType ctCmd = gxDo);

	BOOL SetStyleRange(const CGXRange& range, const CGXStyle& style, GXModifyType mt = gxOverride, int nType = 0, UINT flags = GX_UPDATENOW);

// Implementation
protected:
	BOOL m_bUpdateDone;

	void EmptyEditBuffer();

protected:
	virtual ~CGXBrowserGrid();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

/////////////////////////////////////////////////////////////////////////////
// CGXBrowserView view

class CGXBrowserView : public CGXView, public CGXBrowserGrid
{
/////////////////////////////////////////////////////////////////////////////
// Constructors

protected: // create from serialization only
	CGXBrowserView();
	DECLARE_DYNCREATE(CGXBrowserView)

// Attributes:
public:

/////////////////////////////////////////////////////////////////////////////
// CView overridable member functions
protected:
	virtual ~CGXBrowserView();
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXBrowserView)
	public:
	virtual void OnInitialUpdate();
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo*  pInfo = NULL );
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual void OnActivateView( BOOL bActivate, CView* pActivateView, CView* pDeactiveView );
	virtual CScrollBar* GetScrollBarCtrl(int nBar) const;
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
#ifdef _WINDU_SOURCE
 public:
#endif
	afx_msg void OnUpdateEditUndorecord(CCmdUI* pCmdUI);
	afx_msg void OnEditUndorecord();
	afx_msg void OnRecordDelete();
	afx_msg void OnUpdateRecordDelete(CCmdUI* pCmdUI);
	afx_msg BOOL OnMove(UINT nIDMoveCommand);
	afx_msg void OnView100();
	afx_msg void OnViewZoomin();
	afx_msg void OnViewZoomout();
	afx_msg void OnFormatFreezecols();
	afx_msg void OnFormatUnfreezecols();
	afx_msg void OnUpdateFormatFreezecols(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFormatUnfreezecols(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewZoomin(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewZoomout(CCmdUI* pCmdUI);
#ifdef _WINDU_SOURCE
 protected:
#endif
	afx_msg void OnUpdateRecordFirst(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRecordPrev(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRecordNext(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRecordLast(CCmdUI* pCmdUI);
	afx_msg void OnDestroy();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT flags, CPoint point);
	afx_msg void OnLButtonDown(UINT flags, CPoint point);
	afx_msg void OnLButtonUp(UINT flags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT flags);
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnEditCopy();
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnEditCut();
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	afx_msg void OnEditRedo();
	afx_msg void OnUpdateEditRedo(CCmdUI* pCmdUI);
	afx_msg void OnEditFind();
	afx_msg void OnEditReplace();
	afx_msg void OnEditRepeat();
	afx_msg LRESULT OnFindReplaceCmd(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg LRESULT OnNeedChangeTab(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnChangedTab(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnCanActivate(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMoveRecord(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnLockResize(WPARAM wParam, LPARAM lParam);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnCancelMode();
	afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnPaint();
	afx_msg void OnSysColorChange();
	afx_msg void OnWinIniChange(LPCTSTR lpszSection);
	afx_msg void OnTimer(SEC_UINT nIDEvent);
	//{{AFX_MSG(CGXBrowserView)
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// CWnd functions used in CGXBrowserGrid
public:
	void InvalidateRect(LPCRECT lpRect, BOOL bErase = TRUE);
	void Invalidate(BOOL bErase = TRUE);
	void UpdateWindow();
	int ScrollWindowEx(int dx, int dy,
			LPCRECT lpRectScroll, LPCRECT lpRectClip,
			CRgn* prgnUpdate, LPRECT lpRectUpdate, UINT flags);
	CDC* GetDC();
	int ReleaseDC(CDC* pDC);
	void GetClientRect(LPRECT lpRect);
	void ShowScrollBar(UINT nBar, BOOL bShow = TRUE);
	CWnd* SetCapture();
	CWnd* GetCapture();
	void ScreenToClient(LPPOINT lpPoint);
	void ScreenToClient(LPRECT lpRect);
	BOOL OpenClipboard();

// remove ambiguity between CGXBrowserGrid and CGXView
	CString GetTabName();
	void SetTabName(CString s);
};

/////////////////////////////////////////////////////////////////////////////
// CGXBrowserWnd window

class CGXBrowserWnd : public CWnd, public CGXBrowserGrid
{
	DECLARE_REGISTER()
	DECLARE_DYNCREATE(CGXBrowserWnd)

// Construction
public:
	CGXBrowserWnd();
	BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	void Initialize();

	// Support for tabwnds
public:
	static UINT AFXAPI GetParentTabViewID(const CWnd* pWnd);
	CScrollBar* GetScrollBarCtrl(int nBar) const;

// Attributes
public:

// Operations
public:
	// CView Printing support
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);

// Overridables and other helpers (for implementation of derived classes)
protected:
#if _MFC_VER < 0x0300
	// for deriving from a standard control
	virtual WNDPROC* GetSuperWndProcAddr();
#endif

// Implementation
public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	// Generated message map functions
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnInitialUpdate();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

	//{{AFX_MSG(CGXBrowserWnd)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg LRESULT OnChangedTab(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnNeedChangeTab(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnCanActivate(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMoveRecord(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnLockResize(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnFindReplaceCmd(WPARAM wParam, LPARAM lParam);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnCancelMode();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnSysColorChange();
	afx_msg void OnWinIniChange(LPCTSTR lpszSection);
	afx_msg void OnTimer(SEC_UINT nIDEvent);
	//}}AFX_MSG
	afx_msg void OnUpdateRecordFirst(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRecordPrev(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRecordNext(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRecordLast(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditUndorecord(CCmdUI* pCmdUI);
	afx_msg void OnEditUndorecord();
	afx_msg void OnRecordDelete();
	afx_msg void OnUpdateRecordDelete(CCmdUI* pCmdUI);
	afx_msg BOOL OnMove(UINT nIDMoveCommand);
	afx_msg void OnView100();
	afx_msg void OnViewZoomin();
	afx_msg void OnViewZoomout();
	afx_msg void OnFormatFreezecols();
	afx_msg void OnFormatUnfreezecols();
	afx_msg void OnUpdateFormatFreezecols(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFormatUnfreezecols(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewZoomin(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewZoomout(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

// CWnd functions used in CGXBrowserGrid
public:
	void InvalidateRect(LPCRECT lpRect, BOOL bErase = TRUE);
	void Invalidate(BOOL bErase = TRUE);
	void UpdateWindow();
	int ScrollWindowEx(int dx, int dy,
			LPCRECT lpRectScroll, LPCRECT lpRectClip,
			CRgn* prgnUpdate, LPRECT lpRectUpdate, UINT flags);
	CDC* GetDC();
	int ReleaseDC(CDC* pDC);
	void GetClientRect(LPRECT lpRect);
	void ShowScrollBar(UINT nBar, BOOL bShow = TRUE);
	CWnd* SetCapture();
	CWnd* GetCapture();
	void ScreenToClient(LPPOINT lpPoint);
	void ScreenToClient(LPRECT lpRect);
	BOOL OpenClipboard();
};


/////////////////////////////////////////////////////////////////////////////
// Inline function declarations

#ifdef _GX_ENABLE_INLINES
#include "grid\gxbrowse.inl"
#endif

/////////////////////////////////////////////////////////////////////////////

//
// GridMFC extension DLL
// reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

//

#endif // _GXBROWSE_H_
