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

#ifndef _GXDTABWND_H_
#define _GXDTABWND_H_

#ifdef _GXDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    GX_DATAEXT
#endif

/////////////////////////////////////////////////////////////////////////////
// CGXDTabBeam window


class CGXDTabInfo: public CObject
{
public:
	int         nWidth;
	CString     sLabel;
	BOOL        bSel;
	CObject*    pExtra;
	BOOL        bDeleteExtra;
	HMENU       hMenu;
	BOOL        m_bHot;

	// Scrollbar Info
	SCROLLINFO  sbInfoVert,
				sbInfoHorz;

	// Color
	COLORREF rgbFaceNormal;
	COLORREF rgbFaceSel;
	CBrush   brFaceNormal;
	CBrush   brFaceSel;

	// bit-field flag to decide whether a tab should use its own color or
	// the default tab beam color.
	unsigned int flagUseOwnColorFaceNormal:1;  //1 bit flag
	unsigned int flagUseOwnColorFaceSel:1;

	CGXDTabInfo();
	virtual ~CGXDTabInfo();

};


/////////////////////////////
// AutoDuck tag block block for CGXDTabBeam 
// adinsert AutoDuck insertion point for CGXDTabBeam 
//@topic CGXDTabBeam  Class Overview |
//This class implements the tab-beam control used in the CGXDTabWnd. It provides a similar look
//and feel as that of workbooks of MS Excel 2000.

//@doc CGXDTabBeam 
//@class This class implements the tab-beam control used in the CGXDTabWnd. It provides a similar look
//and feel as that of workbooks of MS Excel 2000. It behaves the same as CGXTabBeam window. CGXDTabBeam is
//intended to be used with CGXDTabWnd. It haven't not tested extensively when used with other windows. So, it
//is recommended that you use CGXTabBeam instead in other situation such as in the dialog.
class CGXDTabBeam : public CWnd
{
	DECLARE_DYNCREATE(CGXDTabBeam)
	

// Construction, initialization
public:
	CGXDTabBeam();
	BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	void CreateBrushes();
	void CreateFonts();
	void UpdateColors();
	void DestroyFonts();
	void DisplayScrollBtns(BOOL bSet = TRUE, int nScrollBtns = 2);
	void ScrollTabInView(int nTab);

	void SetNotifyWnd(CWnd* pNotify);
	void SetTabBkColor(int nTab, COLORREF cr);
	void SetTabSelBkColor(int nTab, COLORREF cr);

	virtual ~CGXDTabBeam();

// Attributes
public:
	CFont*      m_pFontCurrent;         // current tab font
	CFont*      m_pFontNormal;          // normal tab font

	COLORREF    m_rgbTextCurrent;       // current tab text color
	COLORREF    m_rgbTextNormal;        // normal tab text color
	COLORREF    m_rgbFaceNormal;        // normal tab back color
	COLORREF    m_rgbFaceSel;           // selected tab back color
	COLORREF    m_rgbBeam;              // beam color

	CBrush      m_brFaceNormal;
	CBrush      m_brFaceSel;
	CBrush      m_brBlack;

	CPen        m_penShadow;

	CObArray    m_TabInfo;              // Tab Infos

	int         m_nTabs;                // no of tabs
	int         m_nCurrent;             // current tab
	int         m_nFirstTab;            // First Visible Tab

	int         m_nWidthEx;             // Extra space at right and left side (triangles)
	int         m_nMargin;              // x coordinate of first tab
	int         m_nHeight;              // height of the beam
	int         m_nButtonWidth;         // width of scroll button (= scroll's thumb button)

	BOOL        m_bScrollBtns;          // Display ScrollButtons
	int         m_nScrollBtns;          // only arrows: 2; also most left and right: 4

	BOOL        m_bLastVisible;         // Is Last Button Visible

	HCURSOR     m_hcurArrow;

	// Mouse Actions
	int         m_nBtnDown;
	BOOL        m_bBtnDown;
	BOOL        m_bMouseCapture;

	int         m_nxTracking;           // If not -1, this marks the left
										// edge of the painting area
				// m_nxTracking will be set in
				// CGXDTabWnd while tracking the SplitterBar

	// Wnd to receive messages
	CWnd*       m_pNotifyWnd;


protected:
	// Hot Property For Buttons.	
	BOOL m_bBtnHot[4];

// Operations
public:
	virtual void    DrawTab(CDC* pDC, int nTab, BOOL bMouseMove = FALSE);
	virtual void    DrawButton(CDC* pDC, int i, BOOL bPressed);
	virtual int     CalcTabOffset(int nTab);
	virtual int     CalcTabFromOffset(int nOffset);
	virtual int     CalcLastVisibleTab();

	virtual void    AutoMove(UINT nRefMessage = WM_LBUTTONUP);
	virtual void    SwitchToTab(CPoint point);
	virtual int     ScrollBtnHit(CPoint point, int nButton = -1, BOOL bScroll = TRUE);
	virtual void    Scroll(int nDirection);

	// TabInfo
	CGXDTabInfo& GetTab(int nTab);
	virtual void    InsertTab(BOOL bInsert, LPCTSTR szLabel, CObject* pExtra = NULL, BOOL bDelExtra = FALSE, int nWidth = -1, HMENU hMenu = 0);
	virtual void    DeleteTab(int nTab);
	virtual void    AdjustTabSize(int nTab);
	virtual int     FindTab(const CObject *pExtra);

	// Current Selection, TabCount
	int     GetCurSel();
	int     GetCount();

protected:
	// To Handle Mouse leave
	BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);

// Implementation
public:
	static void DrawBlankButton(CDC* pDC, int x, int y, int dx, int dy, BOOL bPressed);
	static void PatB(CDC* pDC,int x,int y,int dx,int dy, COLORREF rgb);

protected:
	// Generated message map functions
	//{{AFX_MSG(CGXDTabBeam)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnSysColorChange();
	afx_msg void OnWinIniChange(LPCTSTR lpszSection);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CGXDTabWnd window

// this class is based on the source code of the CSplitterWnd class

#define ID_GX_EDITWND       23001

class CGXDEditLabelPopup : public CEdit
{
	DECLARE_DYNAMIC(CGXDEditLabelPopup);

// Construction
public:
	CGXDEditLabelPopup(CRect rect, CWnd* pParentWnd, UINT nID);

// Attributes
public:

// Operations
public:

// Implementation
public:
	virtual ~CGXDEditLabelPopup();

protected:
	// Generated message map functions
	//{{AFX_MSG(CGXDEditLabelPopup)
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg UINT OnGetDlgCode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////
// AutoDuck tag block block for CGXDTabWnd 
// adinsert AutoDuck insertion point for CGXDTabWnd 
//@topic CGXDTabWnd  Class Overview |
//This is a another tab window class that provides support dynamic splitter window. The tab window provide the 
//functionality to switch between several views in a frame window. If you want to support dynamic splitter
//window, you can use this tab window class, otherwise use the CGXTabWnd instead.


//@doc CGXDTabWnd 
//@class This is another tab window class that provides support to dynamic splitter window. If you are not going
//to support dynmaic splitter window, it is recommended to use the CGXTabWnd in the library. The CGXDTabWnd class
//displays a tab-beam control on the bottom-left side of the frame window. When it is used together with CDXSplitWnd,
//only one tab-beam control is drawn on the bottom-left side of the frame window even when user splitter the window
//by dragging the splitter box using mouse. This behavior is similar to that of workbooks in the MS Excel 2000. <nl>
//The GridDSplit sample in the sample folder demostrates the how CGXDTabWnd and CDXSplitWnd can be used together.
class CGXDTabWnd : public CWnd
{
	DECLARE_DYNCREATE(CGXDTabWnd)
	

// Construction
public:
	CGXDTabWnd(CRuntimeClass *pBeamClass = RUNTIME_CLASS(CGXDTabBeam));

	// Create a single view type splitter with multiple splits
	BOOL Create(CWnd* pParentWnd, LPCTSTR szFirstLabel,
				CCreateContext* pContext,
				DWORD dwStyle = WS_CHILD | WS_VISIBLE |	WS_HSCROLL | WS_VSCROLL,
				DWORD dwExStyle = WS_EX_CLIENTEDGE,
				UINT nID = AFX_IDW_PANE_FIRST);

// Overridables and other helpers (for implementation of derived classes)
protected:
#if _MFC_VER < 0x0300
	// for deriving from a standard control
	virtual WNDPROC* GetSuperWndProcAddr();
#endif

// Attributes
public:
	CRuntimeClass* m_pDynamicViewClass;
	BOOL m_bHasHScroll, m_bHasVScroll;
	UINT m_nFirstViewID;
	UINT m_nLastViewID;
	CGXDTabBeam* m_pBeam;
	CWnd* m_pActivePane;
	int m_cxBeam;           // size of the beam ( = x-position of the splitter)
	int m_cxWnd;
	int m_cxSplitter;
	int m_cxVScroll, m_cyHScroll;
	int m_nBarWidths;
	BOOL m_bTracking;
	HCURSOR m_hcurArrow;
	BOOL m_bCtrlsCreated;
	CGXDEditLabelPopup* m_pEditWnd;
	CBrush m_brErase;

	CRuntimeClass* m_pBeamClass;    // used for creating the beam

	BOOL m_bDrawSunken;
		// set m_bDrawSunken = TRUE if you want to draw
		// the grid control with sunken borders in the dialog.
		// This attribute is ignored if the WS_EX_CLIENTEDGE
		// style bit is set for the window.

protected:
	LONG m_lxBeam;          // temporary used for size of the beam

// Operations
public:
	void PatB(CDC* pDC, int x, int y, int cx, int cy, COLORREF clr);

	virtual CWnd* AttachWnd(CWnd* pWnd, LPCTSTR szLabel);
	void SaveScrollbarState(CWnd* pSheetWnd);
	void RestoreScrollbarState(CWnd* pSheetWnd);
	BOOL CreateCommon(CWnd* pParentWnd, DWORD dwStyle, DWORD dwExStyle, UINT nID);
	BOOL CreateScrollBarCtrl(DWORD dwStyle, UINT nID);
	void RecalcLayout(BOOL bTracking = FALSE);
	void ShowScrollBar(UINT nBar, BOOL bShow);
	void GetInsideRect(CRect& rect) const;
	CWnd* CreateView(CRuntimeClass* pViewClass, LPCTSTR szLabel, CCreateContext* pContext = NULL, UINT nID = 0);
	void SwitchTab(CWnd* pWnd);
	void SwitchTab(int nTab);
	void RemoveTab(int nTabToDelete);
	void RemoveTab(CWnd* pWnd);
	void OnDrawSplitter(CDC* pDC, const CRect& rectArg);
	UINT GetNextID();
	CGXDTabBeam& GetBeam();
	CWnd* GetActivePane();

	LPCTSTR GetTabName(int nTab);
	LPCTSTR GetTabName(const CWnd* pSheet);
	void SetTabName(int nTab, LPCTSTR szName, BOOL bNotifySheet = TRUE);
	void SetTabName(const CWnd* pSheet, LPCTSTR szName, BOOL bNotifySheet = TRUE);

// Implementation
public:
	virtual ~CGXDTabWnd();

protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	// Generated message map functions
	//{{AFX_MSG(CGXDTabWnd)
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnTabSwitch(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnCanTabSwitch(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnTabDblClk(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnEditCancel(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnEditEnd(WPARAM wParam, LPARAM lParam);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnNcPaint();
	afx_msg void OnSysColorChange();
	afx_msg void OnWinIniChange(LPCTSTR lpszSection);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif//_GXDTABWND_H_
