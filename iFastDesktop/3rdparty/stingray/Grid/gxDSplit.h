// This is a part of the Objective Grid C++ Library.
// Copyright � 1999-2004 Quovadx, Inc.  All Rights Reserved.
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
//          Supplement Section 227.7202, Government�s use, duplication or 
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

#ifndef _GXDSPLIT_H_
#define _GXDSPLIT_H_

#ifdef _GXDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    GX_DATAEXT
#endif

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DXSplitWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Splitter Window

#define SPLS_DYNAMIC_SPLIT  0x0001
#define SPLS_INVERT_TRACKER 0x0002  // obsolete (now ignored)

// HitTest return values (values and spacing between values is important)

#ifndef HitTestValue
#define HitTestValue
enum HitTestValue
{
	noHit                   = 0,
	vSplitterBox            = 1,
	hSplitterBox            = 2,
	bothSplitterBox         = 3,        // just for keyboard
	vSplitterBar1           = 101,
	vSplitterBar15          = 115,
	hSplitterBar1           = 201,
	hSplitterBar15          = 215,
	splitterIntersection1   = 301,
	splitterIntersection225 = 525,
	gxInsideWndBox			= 1024
};
#endif

/////////////////////////////
// AutoDuck tag block block for
// adinsert AutoDuck insertion point for
//@topic  Class Overview |
//This class used together with CGXDTabWnd provides the dynamic splitter window support. It provides similar
//look and feel as the workbook of MS Excel 2000 ( A tab-beam is drawn at the left-bottom of the window whether
//the window is splitted or not). This class is intended to be used to support dynamic splitter window. If
//your application only needs static splitter window support, use CGXSplitterWnd instead.

//@doc
//@class The CGXDSplitWnd class used together with CGXDTabWnd provides the dynamic splitter window support. It provides
//similar look and feel as the workbooks of MS Excel 2000 (A tab-beam is drawn at the left-bottom corner of the window
//whether the window is splitted or not). This class is intended to be used to support dynamic splitter window. If
//your application only needs static splitter window support, use CGXSplitterWnd instead. To use CDCSplitWnd,
//you usually need to do the following steps: <nl>
//1. Override the OnCreateClient method of CFrameWnd class.<nl>
//2. Create a CGXDTabWnd window first.<nl>
//3. Call Create method of this class to create a CGXDSplitWnd window.<nl>
//4. Set the owner of this splitter window to the CGXDTabWnd window we created.<nl>
//5. Call AttachWnd of CGXDTabWnd to add the splitter window to the CGXDTabWnd we created.<nl>
//Refer to GridDSplit sample for more details.
class CGXDSplitWnd : public CWnd
{
	DECLARE_DYNAMIC(CGXDSplitWnd)

friend class CGXDTabWnd;

public:
	// Attributes
	CWnd* m_pOwnerWnd;
	CWnd* m_pBaseWnd;


// Construction
public:
	CGXDSplitWnd();
	// Create a single view type splitter with multiple splits
	BOOL Create(CWnd* pParentWnd, int nMaxRows, int nMaxCols, SIZE sizeMin,	CCreateContext* pContext,
				DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | SPLS_DYNAMIC_SPLIT,
				UINT nID = AFX_IDW_PANE_FIRST);

	// Create a multiple view type splitter with static layout
	BOOL CreateStatic(CWnd* pParentWnd,
				int nRows, int nCols,
				DWORD dwStyle = WS_CHILD | WS_VISIBLE,
				UINT nID = AFX_IDW_PANE_FIRST);

	virtual BOOL CreateView(int row, int col, CRuntimeClass* pViewClass,
			SIZE sizeInit, CCreateContext* pContext);

	virtual CView* GetFirstCView();



// Attributes
public:
	int GetRowCount() const;
	int GetColumnCount() const;

	// information about a specific row or column
	void GetRowInfo(int row, int& cyCur, int& cyMin) const;
	void SetRowInfo(int row, int cyIdeal, int cyMin);
	void GetColumnInfo(int col, int& cxCur, int& cxMin) const;
	void SetColumnInfo(int col, int cxIdeal, int cxMin);

	// for setting and getting shared scroll bar style
	DWORD GetScrollStyle() const;
	void SetScrollStyle(DWORD dwStyle);

	// views inside the splitter
	CWnd* GetPane(int row, int col) const;
	BOOL IsChildPane(CWnd* pWnd, int* pRow, int* pCol);
	BOOL IsChildPane(CWnd* pWnd, int& row, int& col); // obsolete
	int IdFromRowCol(int row, int col) const;

	BOOL IsTracking();  // TRUE during split operation

// Operations
public:
	virtual void RecalcLayout();    // call after changing sizes

// Overridables
protected:
	// to customize the drawing
	enum ESplitType { splitBox, splitBar, splitIntersection, splitBorder };
	virtual void OnDrawSplitter(CDC* pDC, ESplitType nType, const CRect& rect);
	virtual void OnInvertTracker(const CRect& rect);

public:
	// for customizing scrollbar regions
	virtual BOOL CreateScrollBarCtrl(DWORD dwStyle, UINT nID);

	// for customizing DYNAMIC_SPLIT behavior
	virtual void DeleteView(int row, int col);
	virtual BOOL SplitRow(int cyBefore);
	virtual BOOL SplitColumn(int cxBefore);
	virtual void DeleteRow(int rowDelete);
	virtual void DeleteColumn(int colDelete);

	// determining active pane from focus or active view in frame
	virtual CWnd* GetActivePane(int* pRow = NULL, int* pCol = NULL);
	virtual void SetActivePane(int row, int col, CWnd* pWnd = NULL);
protected:
	CWnd* GetActivePane(int& row, int& col); // obsolete

public:
	// high level command operations - called by default view implementation
	virtual BOOL CanActivateNext(BOOL bPrev = FALSE);
	virtual void ActivateNext(BOOL bPrev = FALSE);
	virtual BOOL DoKeyboardSplit();

	// synchronized scrolling
	virtual BOOL DoScroll(CView* pViewFrom, UINT nScrollCode,
		BOOL bDoScroll = TRUE);
	virtual BOOL DoScrollBy(CView* pViewFrom, CSize sizeScroll,
		BOOL bDoScroll = TRUE);

// Implementation
public:
	virtual ~CGXDSplitWnd();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// implementation structure
	struct CRowColInfo
	{
		int nMinSize;       // below that try not to show
		int nIdealSize;     // user set size
		// variable depending on the available size layout
		int nCurSize;       // 0 => invisible, -1 => nonexistant
	};

protected:
	// customizable implementation attributes (set by constructor or Create)
	CRuntimeClass* m_pDynamicViewClass;
	int m_nMaxRows, m_nMaxCols;

	// implementation attributes which control layout of the splitter
	int m_cxSplitter, m_cySplitter;         // size of splitter bar
	int m_cxBorderShare, m_cyBorderShare;   // space on either side of splitter
	int m_cxSplitterGap, m_cySplitterGap;   // amount of space between panes
	int m_cxBorder, m_cyBorder;             // borders in client area

	// current state information
	int m_nRows, m_nCols;
	BOOL m_bHasHScroll, m_bHasVScroll;
	CRowColInfo* m_pColInfo;
	CRowColInfo* m_pRowInfo;

    // [VC7] In VC7 these variables are removed, so localized them.
	BOOL bWin4, bNotWin4;

	// Tracking info - only valid when 'm_bTracking' is set
	BOOL m_bTracking, m_bTracking2;
	CPoint m_ptTrackOffset;
	CRect m_rectLimit;
	CRect m_rectTracker, m_rectTracker2;
	int m_htTrack;

	// implementation routines
	BOOL CreateCommon(CWnd* pParentWnd, SIZE sizeMin, DWORD dwStyle, UINT nID);
	virtual int HitTest(CPoint pt) const;
	virtual void GetInsideRect(CRect& rect) const;
	virtual void GetHitRect(int ht, CRect& rect);
	virtual void TrackRowSize(int y, int row);
	virtual void TrackColumnSize(int x, int col);
	virtual void DrawAllSplitBars(CDC* pDC, int cxInside, int cyInside);
	virtual void SetSplitCursor(int ht);
	CWnd* GetSizingParent();

	// starting and stopping tracking
	virtual void StartTracking(int ht);
	virtual void StopTracking(BOOL bAccept);

	// special command routing to frame
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

	//{{AFX_MSG(CGXDSplitWnd)
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint pt);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint pt);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint pt);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint pt);
	afx_msg void OnCancelMode();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpcs);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnDisplayChange();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR


#endif // _GXDSPLIT_H_
