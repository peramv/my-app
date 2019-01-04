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

// gxodbc.h : header file
//

#ifndef _GXODBC_H_
#define _GXODBC_H_

#if ! ( defined(_GX_VER) && _GX_VER >= 0x0903 )
#pragma message( "Please make sure that you include Objective Grid 9.03 header files")
#pragma message( "or a later version and not an older version header files!")
Fatal error!
#endif

#ifndef _GXCORE_H_
#include "grid\gxcore.h"
#endif

#ifndef _GXCTRL_H_
#include "grid\gxctrl.h"
#endif

#ifndef _GXBROWSE_H_
#include "grid\gxbrowse.h"
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

// initialization of ODBC support
void GXInitODBC(UINT uiMfcVersion);
	// when using GridMFC extension DLL with ODBC support under 16 Bit
	// you have to link your application with gxd6116d.lib import library
	// and call this method in OnInitInstance.
	// Otherwise, calling this method has no effect.

inline void GXInitODBC() { GXInitODBC(_MFC_VER); }

/////////////////////////////////////////////////////////////////////////////
// Win16 libraries

#ifndef _GXNOODBCAUTOLIB

#if !defined(_GXNOMSG) && _MFC_VER < 0x0300		// 16 bit
	#if !(defined(_GXDLL) || defined(_GXEXT))
		#ifndef _AFXDLL
			#ifdef _DEBUG
				#define _GXODBCLIBNAME "gxd16d.lib"
			#else
				#define _GXODBCLIBNAME "gxd16r.lib"
			#endif
		#else
			#ifdef _DEBUG
				#define _GXODBCLIBNAME "gxad16d.lib"
			#else
				#define _GXODBCLIBNAME "gxad16r.lib"
			#endif
		#endif
	#else
		#ifdef _DEBUG
			#define _GXODBCLIBNAME "gxd6116d.lib"
		#else
			#define _GXODBCLIBNAME "gxd6116r.lib"
		#endif
	#endif

	#pragma message( "Objective Grid requires linking with " _GXODBCLIBNAME  )

#endif // !defined(_GXNOMSG) && _MFC_VER < 0x0300		// 16 bit

#endif // _GXNOODBCAUTOLIB


#if _MFC_VER < 0x0400

// see gxodbc.cpp for info on this method

#define AFX_RFX_TIMESTAMP_PSEUDO_NULL 99

void GX_RFX_Date(CFieldExchange* pFX, const char *szName,
	TIMESTAMP_STRUCT& value);

#else

// MFC version 3.1 and greater already define this method

#define GX_RFX_Date RFX_Date

#endif

// helper routine which converts a recordset value into a string
BOOL GXGetODBCValueString(CString& strRet, CRecordset* pRecordset, void* pv, int nDataType, DWORD dwSize, BOOL bConvertMemo = TRUE);
BOOL GXWriteODBCValueString(LPCTSTR pszValue, CRecordset* pRecordset, void* pv, int nDataType, DWORD dwSize, CString* psWarning = NULL, BOOL bConvertMemo = TRUE);

/////////////////////////////////////////////////////////////////////////////
// CGXDynamicRecordset recordset

class CGXODBCGrid;

// CGXFieldDesc structure
//
// provides storage buffer + some additional info for result
// columns in CGXDynamicRecordset

struct CGXFieldDesc
{
	CString strName;    // column names
	SWORD fSqlType;     // SQL type
#ifdef _WIN64
	UINT64 cbColDef;
#else	// WIN32
	UDWORD cbColDef;    // Precision
#endif	// _WIN64
	SWORD ibScale;      // scale
	SWORD fNullable;    // is column nullable
	SDWORD cbValue;
	BOOL bDirty;        // field has been changed, need update
	void* pv;           // value
	UINT nDataType;     // AFX_ SQL type

	CGXFieldDesc();
	~CGXFieldDesc();
};

// CGXDynamicRecordset class
//
// enhances CRecordset class with possibility to specify
// SQL-Select-Statements at runtime.

class CGXDynamicRecordset : public CRecordset
{
	DECLARE_DYNAMIC(CGXDynamicRecordset)

public:
// Construction
	CGXDynamicRecordset(CDatabase* pDatabase = NULL);

public:
// Attributes
	void SetSqlQuery(LPCTSTR szSQLQuery);
	const CString& GetSqlQuery() const;

	void SetConnectString(LPCTSTR szConnectString);
	const CString& GetConnectString() const;

// Values
	BOOL GetFieldData(int nField, CString& strRet, BOOL bDisplayMemo = TRUE);
	BOOL SetFieldData(int nField, LPCTSTR pszValue, CString* psWarning = NULL, BOOL bDisplayMemo = TRUE);
	void FillChoiceList(CString& strChoiceList, BOOL bDisplayHeader);

// Implementation
public:
	virtual ~CGXDynamicRecordset();

	CGXFieldDesc& GetField(UINT nField) const;

protected:
	UINT m_nQueryFields;        // no. of result columns
	struct CGXFieldDesc  *m_aFieldDesc;
	CString m_sSqlQuery;        // query string
	CString m_sConnectString;   // connect string

	// Cursor data

// Field/Param Data
	//{{AFX_FIELD(CGXDynamicRecordset, CRecordset)
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXDynamicRecordset)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void PreBindFields();
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
	virtual void Close();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

/////////////////////////////////////////////////////////////////////////////
// CGXDbParam
//

#if _MFC_VER >= 0x0420

// MS did change the CFieldInfo structure. I have
// to emulate it, so that I can still can access
// the information.

// For returning field info on RFX fields
struct CGXFieldInfo
{
	// For ID'ing field
	UINT nField;        // Field number
	CString strName;    // Field name
	void* pv;       // Address of value for field

	// Return info GetFieldInfo
	UINT nDataType;     // data type of field (BOOL, BYTE, etc)

	// dwSize cannot be determined in MFC 4.2 anymore
	//  DWORD dwSize;       // Max size for field data

	CGXFieldInfo();
};

#else

#define CGXFieldInfo CFieldInfo

#endif

class CGXDbParam: public CGXBrowseParam
{
	DECLARE_SERIAL(CGXDbParam)

public:
// Attributes - Base styles
	WORD
		m_bsBoolean,
		m_bsNumeric,
		m_bsDate,
		m_bsText,
		m_bsBinary;

	// Style for appearance of deleted rows
	WORD
		m_bsDeletedRows;

	// display Memo fields (default: TRUE)
	BOOL
		m_bDisplayMemo;

	int m_nTransactionPending; // only 1 transaction allowed with ODBC

#if _MFC_VER >= 0x0420
	CGXFieldInfo* m_apFieldInfo;
#endif

// Implementation
public:
	CGXDbParam();
	virtual ~CGXDbParam();
	virtual void Serialize(CArchive& ar);
	virtual CGXDbParam& operator=(const CGXDbParam& p);
};

/////////////////////////////////////////////////////////////////////////////
// CGXODBCGrid
//
// base class which provides base functionailty for sql-query-browser-grids

class CGXODBCGrid : public CGXBrowserGrid
{
public:
// Compatibility with 1.0
	UINT GetFieldCol(ROWCOL nCol);

// Changed:
// virtual void Edit(long nRecord);
// virtual void Update();

// Construction
public:
	CGXODBCGrid(CWnd* pGridWnd = NULL, CDocument* pGridDoc = NULL, BOOL bIsViewContext = FALSE);

// Attributes
public:
	// Atributes - ODBC Specific
	CGXDbParam* GetDbParam();

	virtual CRecordset* OnGetRecordset();
	void SetRecordset(CRecordset* pRecordset);
	void AttachForeignTable(ROWCOL nCol, CGXDynamicRecordset* pSet, UINT nKeyCol, UINT nDispCol, BOOL bDispAllCols, BOOL bDisplayHeader);

// Overridables - ODBC specific
public:
	virtual void OpenRecordset();
	virtual void ConvertValueToString(ROWCOL nCol, CString& sResult);
	long GetColSize(ROWCOL nCol);
	void GetFieldData(int nField, CString& strRet);
	void SetFieldData(int nField, LPCTSTR pszChangedValue);

protected:
	virtual void OnInitColInfo(ROWCOL nCol, const CGXFieldInfo& fieldInfo, CString& strName,
		long& cbLength, WORD& wBaseStyle, BOOL* pbColumnSettingsLocked = NULL);
	virtual long GetDisplaySize(const CGXFieldInfo& fieldInfo, long cbColDef);

// CGXBrowserGrid Overridables

public:
	// Overridables - State members
	virtual BOOL CanUpdate();
	virtual BOOL CanAppend();
	virtual long OnGetRecordCount();

	// Overridables - Operations
	virtual void DeleteRows(const CRowColArray& awRowStart, const CRowColArray& awRowEnd, BOOL* pbSuccess = NULL);
	virtual void Requery();
	virtual BOOL MoveTo(ROWCOL nRow);

	// Overridables - Sorting 
	virtual void SortRows(CGXRange sortRange, CGXSortInfoArray& sortInfo, UINT flags = GX_UPDATENOW);

	// Wrapper methods for DeleteRows (not overridable)
	void DeleteRows(ROWCOL nFromRow, ROWCOL nToRow);
	void DeleteRows(const CGXRange& range);

protected:
	virtual void OnFillCache();

	// Overridables - Events
	virtual void OnAddedNewRecord();

	// Overridables - Load cell styles and flush values
	virtual BOOL OnLoadCellStyle(ROWCOL nRow, ROWCOL nCol, CGXStyle& style, LPCTSTR pszExistingValue);

	virtual void OnFlushCellValue(ROWCOL nRow, ROWCOL nCol, LPCTSTR pszChangedValue);
	virtual BOOL OnFlushRecord(ROWCOL nRow, CString* ps = NULL);
	virtual void PreUpdateRecordset(ROWCOL nRow);

		// NOTE: You should override the previous members instead
		// of GetStyleRowCol/StoreStyleRowCol. They provide a better
		// abstraction for loading/storing cell values in a CGXBrowserGrid

		// The methods will be called appropriately from within CGXBrowserGrid::Update(),
		// CGXBrowserGrid::GetStyleRowCol, CGXBrowserGrid::StoreStyleRowCol and
		// CGXBrowserGrid::SetStyleRange

// CGXGridCore Overridables
protected:
	// they are called from overridden On... method in CGXRecordWnd and CGXRecordView
	virtual void OnGridInitialUpdate();
	virtual void OnTestGridDimension(ROWCOL nLastRow, ROWCOL nLastCol);

	virtual void OnReplaceAll(LPCTSTR lpszFind, LPCTSTR lpszReplace,
		BOOL bCase);

	virtual void OnMovedCurrentCell(ROWCOL nRow, ROWCOL nCol);

	// Transactions
public:
	virtual void BeginTrans(LPCTSTR pszDescription);
	virtual void CommitTrans();
	virtual void Rollback();

protected:
	virtual ~CGXODBCGrid();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Implementation - Attributes
protected:
	BOOL m_bRecordAppended;

private:
	CRecordset* m_pRecordset;   // You should call OnGetRecordset to access this pointer!

#if _MFC_VER >= 0x0420
	void LoadFieldInfo();
#endif
};

/////////////////////////////////////////////////////////////////////////////
// CGXRecordView view

class CGXRecordView : public CGXView, public CGXODBCGrid
{
/////////////////////////////////////////////////////////////////////////////
// Constructors

protected: // create from serialization only
	CGXRecordView();
	DECLARE_DYNCREATE(CGXRecordView)

// Attributes:
public:

/////////////////////////////////////////////////////////////////////////////
// CView overridable member functions
protected:
	virtual ~CGXRecordView();
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXRecordView)
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
	//{{AFX_MSG(CGXRecordView)
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
	afx_msg void OnTimer(SEC_UINT nIDEvent);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG
	afx_msg void OnWinIniChange(LPCTSTR lpszSection);
	DECLARE_MESSAGE_MAP()

// CWnd functions used in CGXODBCGrid
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

// remove ambiguity between CGXODBCGrid and CGXView
	CString GetTabName();
	void SetTabName(CString s);
};


/////////////////////////////////////////////////////////////////////////////
// CGXRecordWnd window

class CGXRecordWnd : public CWnd, public CGXODBCGrid
{
	DECLARE_REGISTER()
	DECLARE_DYNCREATE(CGXRecordWnd)

// Construction
public:
	CGXRecordWnd();
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

	//{{AFX_MSG(CGXRecordWnd)
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
	afx_msg void OnTimer(SEC_UINT nIDEvent);
	//}}AFX_MSG
	afx_msg void OnWinIniChange(LPCTSTR lpszSection);
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

// CWnd functions used in CGXODBCGrid
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
#include "grid\gxodbc.inl"
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

#endif // _GXODBC_H_
