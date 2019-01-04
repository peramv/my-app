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

// gxwnd.h : header file
//

#ifndef _GXWND_H_
#define _GXWND_H_

#ifndef _GXEXT_H_
#include "grid\gxext.h"
#endif

#ifndef _GXCORE_H_
#include "grid\gxcore.h"
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

class CGXTabWnd;
class CGXGridWnd;
class CGXGridHandleWnd;
class CGXRecordInfoWnd;

/////////////////////////////////////////////////////////////////////////////
// CGXGridWnd support for dialog validation

void AFXAPI DDV_GXGridWnd(CDataExchange* pDX, CGXGridCore* pGrid);
void AFXAPI DDV_GXGridHandleWnd(CDataExchange* pDX, CGXGridHandleWnd* pGrid);

/////////////////////////////////////////////////////////////////////////////
// CGXGridWnd window

class CGXGridWnd : public CWnd, public CGXGridCore
{
	DECLARE_REGISTER()
	DECLARE_DYNCREATE(CGXGridWnd)

// Construction
public:
	CGXGridWnd();
	BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	void Initialize();

	// Support for tabwnds
public:
	static UINT AFXAPI GetParentTabViewID(const CWnd* pWnd);
	CScrollBar* GetScrollBarCtrl(int nBar) const;

// Attributes
public:
	BOOL m_bDrawSunken;
		// set m_bDrawSunken = TRUE if you want to draw
		// the grid control with sunken borders in the dialog.
		// This attribute is ignored if the WS_EX_CLIENTEDGE
		// style bit is set for the window.

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

	//{{AFX_MSG(CGXGridWnd)
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
	afx_msg void OnWinIniChange(LPCTSTR lpszSection);
	afx_msg void OnSysColorChange();
	afx_msg void OnNcPaint();
	afx_msg void OnTimer(SEC_UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// CWnd functions used in CGXGridCore
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
// CGXGridHandleWnd window

class CGXGridHandleWnd : public CWnd
{
	DECLARE_REGISTER()
	DECLARE_DYNCREATE(CGXGridHandleWnd)

// Construction
public:
	CGXGridHandleWnd();
	virtual ~CGXGridHandleWnd();
	BOOL CreateGrid(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	void Initialize();

	void AttachGrid(CGXGridCore* pGrid);

protected:
	CGXGridCore*   m_pGrid; // this the object which contains the implementation
							// of the grid functionality

// Attributes:
public:
	CGXGridCore* GetGrid();

	// Support for tabwnds
public:
	static UINT AFXAPI GetParentTabViewID(const CWnd* pWnd);

// Attributes
public:
	BOOL m_bDrawSunken;
		// set m_bDrawSunken = TRUE if you want to draw
		// the grid control with sunken borders in the dialog.
		// This attribute is ignored if the WS_EX_CLIENTEDGE
		// style bit is set for the window.

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
	CScrollBar* GetScrollBarCtrl(int nBar) const;
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

	//{{AFX_MSG(CGXGridHandleWnd)
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
	afx_msg void OnWinIniChange(LPCTSTR lpszSection);
	afx_msg void OnSysColorChange();
	afx_msg void OnNcPaint();
	afx_msg void OnTimer(SEC_UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// Inline function declarations

#ifdef _GX_ENABLE_INLINES
#include "grid\gxwnd.inl"
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

#endif // _GXWND_H_
