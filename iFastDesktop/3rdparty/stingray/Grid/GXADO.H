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
// Authors: Praveen Ramesh, Stefan Hoenig
//

// gxado.h : header file
//

#ifndef _GXADO_H_
#define _GXADO_H_

#if ! ( defined(_GX_VER) && _GX_VER >= 0x0903 )
#pragma message( "Please make sure that you include Objective Grid 9.03 header files")
#pragma message( "or a later version and not an older version header files!")
Fatal error!
#endif

// compile this file only if ADO is supported
#if _MFC_VER >= 0x0400 && !defined(_GX_NO_ADO_SUPPORT)

// include decls for base class

#include <adoid.h>			// ADO C++ header	 
#include <adoint.h>			// ADO C++ header

#ifndef _GXMSG_H
#include "grid\gxmsg.h"
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

// initialization of ADO support (obsolete)
inline void GXInitAdo(UINT uiMfcVersion) { uiMfcVersion; }  
inline void GXInitAdo() { GXInitAdo(_MFC_VER); }

// Other global helper methods

void GXGetAdoFieldString(CString& strRet, ADORecordset* pRecordset, int nField);
CString GXGetFieldName(ADOField* pAdoField);
CString GXGetFieldName(ADORecordset* pRecordset, int nIndex);
void GXFillChoiceList(ADORecordset* pSet, CString& strChoiceList, BOOL bDisplayHeader);


// We do not link to adoid.lib anymore as of OG 6.1
// force linking with adoid.lib

//#ifndef _GXNOADOIDAUTOLIB
//#pragma comment(lib, "adoid.lib")
//#endif

// Replica of adoid.lib, but without the debug problem in adoid.lib...
// link to the correct version of adoid.lib

#ifdef _UNICODE
	#ifdef _DEBUG
		#ifdef _AFXDLL
			#pragma message("gxadoidusd.lib")
			#pragma comment(lib, "gxadoidusd.lib")
		#else
			#pragma message("gxadoidud.lib")
			#pragma comment(lib, "gxadoidud.lib")
		#endif //_AFXDLL
	#else
		#ifdef _AFXDLL
			#pragma message("gxadoidus.lib")
			#pragma comment(lib, "gxadoidus.lib")
		#else
			#pragma message("gxadoidu.lib")
			#pragma comment(lib, "gxadoidu.lib")
		#endif //_AFXDLL
	#endif//_DEBUG
#else
	#ifdef _DEBUG
		#ifdef _AFXDLL
			#pragma message("gxadoidsd.lib")
			#pragma comment(lib, "gxadoidsd.lib")
		#else
			#pragma message("gxadoidd.lib")
			#pragma comment(lib, "gxadoidd.lib")
		#endif //_AFXDLL
	#else
		#ifdef _AFXDLL
			#pragma message("gxadoids.lib")
			#pragma comment(lib, "gxadoids.lib")
		#else
			#pragma message("gxadoid.lib")
			#pragma comment(lib, "gxadoid.lib")
		#endif //_AFXDLL
	#endif //_DEBUG
#endif //_UNICODE

/////////////////////////////////////////////////////////////////////////////

// Some defines

#define ISOPEN(precordset)	\
	TRUE \

//statement is the statement to be executed
//recordset is a pointer to recordset to retrieve the errors if any occured
//succeded is the output param that would have true or false.
#define GX_ADO_CHECK(exp, recordset, succeded)	\
	{							\
		HRESULT hr;					\
		succeded = TRUE;			\
		if(FAILED(hr = exp))		\
		{							\
			succeded = FALSE;				\
			ADOConnection *piConnection = 0;	\
			VARIANT var;\
			VariantInit(&var);\
			recordset->get_ActiveConnection(&var);\
			piConnection = (ADOConnection *) V_DISPATCH(&var);\
			ADOErrors *piErrors = 0;	\
			piConnection->get_Errors(&piErrors);	\
			long lCount;		\
			piErrors->get_Count(&lCount);	\
			ADOError *piError = 0;						\
			for(int i=0; i<(int)lCount; i++)		\
			{										\
				VARIANT varIndex;					\
				varIndex.vt = VT_INT;				\
				varIndex.intVal = i;				\
				piErrors->get_Item(varIndex, &piError);	\
				BSTR error;							\
				piError->get_Description(&error);	\
				AfxMessageBox(CString(error));				\
			}										\
			piErrors->Clear();						\
			if (piErrors)		\
				piErrors->Release();\
			if (piConnection)		\
				piConnection->Release();\
			if (piError)		\
				piError->Release();\
		}							\
	}							\


/////////////////////////////////////////////////////////////////////////////
// CGXAdoParam
//

class CGXAdoParam: public CGXBrowseParam
{
	DECLARE_SERIAL(CGXAdoParam)

public:
// Attributes - Base styles
	WORD
		m_bsBoolean,
		m_bsNumeric,
		m_bsCurrency,
		m_bsDate,
		m_bsText,
		m_bsBinary,
		m_bsMemo,
		m_bsGUID,
		m_bsChapter;

	// Style for appearance of deleted rows
	WORD
		m_bsDeletedRows;

// Implementation
public:
	int m_nTransPending;
	CGXAdoParam();
	virtual ~CGXAdoParam();
	virtual void Serialize(CArchive& ar);
	virtual CGXAdoParam& operator=(const CGXAdoParam& p);
protected:
	long m_nLastRecord;
	friend class CGXAdoGrid;
};


/////////////////////////////////////////////////////////////////////////////
// CGXAdoGrid
//
// base class which provides base functionailty for sql-query-browser-grids

class CGXAdoGrid : public CGXBrowserGrid
{

// Construction
public:
	CGXAdoGrid(CWnd* pGridWnd = NULL, CDocument* pGridDoc = NULL, BOOL bIsViewContext = FALSE);

// Attributes
public:
	// Atributes - Ado Specific
	CGXAdoParam* GetAdoParam();

	virtual ADORecordset* OnGetRecordset();
	virtual ADORecordset* CreateRecordset(BSTR bstrSource,BSTR bstrSQL);

	void SetRecordset(ADORecordset* pRecordset, BOOL bOpen = TRUE);
	void AttachForeignTable(ROWCOL nCol, ADORecordset* pSet, UINT nKeyCol, UINT nDispCol, BOOL bDispAllCols, BOOL bDisplayHeader);

// Overridables - Ado specific
public:
	virtual void OpenRecordset();
	virtual void ConvertValueToString(ROWCOL nCol, CString& sResult);

protected:
	virtual void OnInitColInfo(ROWCOL nCol, ADOField* fieldInfo, CString& strName,
		long& cbLength, WORD& wBaseStyle, BOOL* pbColumnSettingsLocked = NULL);
	virtual long GetDisplaySize(ADOField* piField);

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
	virtual void SortRows(CGXRange sortRange, const CGXSortInfoArray& sortInfo, UINT flags = GX_UPDATENOW);

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
	// they are called from overridden On... method in CGXAdoRecordWnd and CGXAdoRecordView
	virtual void OnGridInitialUpdate();
	virtual void OnTestGridDimension(ROWCOL nLastRow, ROWCOL nLastCol);

	virtual void OnReplaceAll(LPCTSTR lpszFind, LPCTSTR lpszReplace,
		BOOL bCase);

	virtual void OnMovedCurrentCell(ROWCOL nRow, ROWCOL nCol);

	// Transactions
public:
	virtual BOOL IsRecordsetOpen();
	void CloseRecordset(ADORecordset*);
	ADOFields* m_piFields;
	virtual void BeginTrans(LPCTSTR pszDescription);
	virtual void CommitTrans();
	virtual void Rollback();

protected:
	virtual ~CGXAdoGrid();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Implementation - Attributes
	long SyncPosition();
	void MoveToPosition(long nRecord, BOOL bSync = TRUE);
protected:
	BOOL m_bIsOpen;

private:
	ADORecordset* m_piRecordset;   // You should call OnGetRecordset to access this pointer!
};


/////////////////////////////////////////////////////////////////////////////
// CGXAdoRecordView view

class CGXAdoRecordView : public CGXView, public CGXAdoGrid
{
/////////////////////////////////////////////////////////////////////////////
// Constructors

protected: // create from serialization only
	CGXAdoRecordView();
	DECLARE_DYNCREATE(CGXAdoRecordView)

// Attributes:
public:

/////////////////////////////////////////////////////////////////////////////
// CView overridable member functions
protected:
	virtual ~CGXAdoRecordView();
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXAdoRecordView)
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
	//{{AFX_MSG(CGXAdoRecordView)
	afx_msg void OnUpdateRecordFirst(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRecordPrev(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRecordNext(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRecordLast(CCmdUI* pCmdUI);
	afx_msg BOOL OnMove(UINT nIDMoveCommand);
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
	afx_msg LRESULT OnFindReplaceCmd(WPARAM wParam, LPARAM lParam);
	afx_msg void OnUpdateEditUndorecord(CCmdUI* pCmdUI);
	afx_msg void OnEditUndorecord();
	afx_msg void OnRecordDelete();
	afx_msg void OnUpdateRecordDelete(CCmdUI* pCmdUI);
	afx_msg void OnView100();
	afx_msg void OnViewZoomin();
	afx_msg void OnViewZoomout();
	afx_msg void OnFormatFreezecols();
	afx_msg void OnFormatUnfreezecols();
	afx_msg void OnUpdateFormatFreezecols(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFormatUnfreezecols(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewZoomin(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewZoomout(CCmdUI* pCmdUI);
	afx_msg void OnWinIniChange(LPCTSTR lpszSection);
	afx_msg LRESULT OnAdoRequery( WPARAM wParam, LPARAM lParam );
	DECLARE_MESSAGE_MAP()

// CWnd functions used in CGXAdoGrid
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

// resolve ambiguity between CGXGridCore and CGXView
	CString GetTabName();
	void SetTabName(CString s);
};


/////////////////////////////////////////////////////////////////////////////
// CGXAdoRecordWnd window

class CGXAdoRecordWnd : public CWnd, public CGXAdoGrid
{
	DECLARE_REGISTER()
	DECLARE_DYNCREATE(CGXAdoRecordWnd)

// Construction
public:
	CGXAdoRecordWnd();
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

	//{{AFX_MSG(CGXAdoRecordWnd)
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
	afx_msg LRESULT OnAdoRequery( WPARAM wParam, LPARAM lParam );
	DECLARE_MESSAGE_MAP()

// CWnd functions used in CGXAdoGrid
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
#include "grid\gxado.inl"
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

#endif // _GX_NO_ADO_SUPPORT

#endif // _GXADO_H_
