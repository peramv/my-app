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

// gxtwnd.h : header file
//

#ifndef _GXTWND_H_
#define _GXTWND_H_

#ifndef _GXMSG_H_
#include "grid\gxmsg.h"
#endif

#ifndef _GXEXT_H_
#include "grid\gxext.h"   // for use as custom control
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

class CGXEditLabelPopup;
class CGXTabWnd;

/////////////////////////////////////////////////////////////////////////////
// CGXTabWnd support for dialog validation

void AFXAPI DDV_GXTabWnd(CDataExchange* pDX, CGXTabWnd* pTabWnd);

CGXTabWnd* GXGetParentTabWnd(const CWnd* pWnd, BOOL bAnyState);

inline CGXTabWnd* GetParentTabWnd(const CWnd* pWnd, BOOL bAnyState)  
{ return GXGetParentTabWnd(pWnd, bAnyState); }

/////////////////////////////////////////////////////////////////////////////
// CGXTabInfo Object

#if _MFC_VER <= 0x0300
typedef struct tagSCROLLINFO
{
	UINT    cbSize;
	UINT    fMask;
	int     nMin;
	int     nMax;
	UINT    nPage;
	int     nPos;
	int     nTrackPos;
}   SCROLLINFO, FAR *LPSCROLLINFO;
#endif

class CGXTabInfo: public CObject
{
public:
	int         nWidth;
	CString     sLabel;
	BOOL        bSel;
	CObject*    pExtra;
	BOOL        bDeleteExtra;
	HMENU       hMenu;

	// Scrollbar Info
	SCROLLINFO  sbInfoVert,
				sbInfoHorz;

	// Color
	COLORREF rgbFaceNormal;
	COLORREF rgbFaceSel;
	CBrush   brFaceNormal;
	CBrush   brFaceSel;

	// BOOL Theme State Field.
	BOOL m_bHot;

	// bit-field flag to decide whether a tab should use its own color or
	// the default tab beam color.
	unsigned int flagUseOwnColorFaceNormal:1;  //1 bit flag
	unsigned int flagUseOwnColorFaceSel:1;

	CGXTabInfo();
	virtual ~CGXTabInfo();

};

/////////////////////////////////////////////////////////////////////////////
// CGXTabBeam window

class CGXTabBeam : public CWnd
{
	DECLARE_DYNCREATE(CGXTabBeam)
	DECLARE_REGISTER()

// Construction, initialization
public:
	CGXTabBeam();
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

	// To Handle Mouse leave
	BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);

	virtual ~CGXTabBeam();

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
				// CGXTabWnd while tracking the SplitterBar

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
	CGXTabInfo& GetTab(int nTab);
	virtual void    InsertTab(BOOL bInsert, LPCTSTR szLabel, CObject* pExtra = NULL, BOOL bDelExtra = FALSE, int nWidth = -1, HMENU hMenu = 0);
	virtual void    DeleteTab(int nTab);
	virtual void    AdjustTabSize(int nTab);
	virtual int     FindTab(const CObject *pExtra);

	// Current Selection, TabCount
	int     GetCurSel();
	int     GetCount();

// Implementation
public:
	static void AFXAPI DrawBlankButton(CDC* pDC, int x, int y, int dx, int dy, BOOL bPressed);
	static void AFXAPI PatB(CDC* pDC,int x,int y,int dx,int dy, COLORREF rgb);

protected:
	// Generated message map functions
	//{{AFX_MSG(CGXTabBeam)
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
// CGXTabWnd window

// this class is based on the source code of the CSplitterWnd class

#define ID_GX_EDITWND       23001

class CGXEditLabelPopup;

class CGXTabWnd : public CWnd
{
	DECLARE_DYNCREATE(CGXTabWnd)
	DECLARE_REGISTER()

// Construction
public:
	CGXTabWnd(CRuntimeClass *pBeamClass = RUNTIME_CLASS(CGXTabBeam));

	// Create a single view type splitter with multiple splits
	BOOL Create(CWnd* pParentWnd, LPCTSTR szFirstLabel,
				CCreateContext* pContext,
				DWORD dwStyle = WS_CHILD | WS_VISIBLE |
					WS_HSCROLL | WS_VSCROLL,
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
	CGXTabBeam* m_pBeam;
	CWnd* m_pActivePane;
	int m_cxBeam;           // size of the beam ( = x-position of the splitter)
	int m_cxWnd;
	int m_cxSplitter;
	int m_cxVScroll, m_cyHScroll;
	int m_nBarWidths;
	BOOL m_bTracking;
	HCURSOR m_hcurArrow;
	BOOL m_bCtrlsCreated;
	CGXEditLabelPopup* m_pEditWnd;
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
	virtual CWnd* AttachWnd(CWnd* pWnd, LPCTSTR szLabel);
	void SaveScrollbarState(CWnd* pSheetWnd);
	void RestoreScrollbarState(CWnd* pSheetWnd);
	BOOL CreateCommon(CWnd* pParentWnd, DWORD dwStyle, UINT nID);
	BOOL CreateScrollBarCtrl(DWORD dwStyle, UINT nID);
	virtual void RecalcLayout(BOOL bTracking = FALSE);
	void ShowScrollBar(UINT nBar, BOOL bShow);
	void GetInsideRect(CRect& rect) const;
	CWnd* CreateView(CRuntimeClass* pViewClass, LPCTSTR szLabel, CCreateContext* pContext = NULL, UINT nID = 0);
	void SwitchTab(CWnd* pWnd);
	void SwitchTab(int nTab);
	void RemoveTab(int nTabToDelete);
	void RemoveTab(CWnd* pWnd);
	void OnDrawSplitter(CDC* pDC, const CRect& rectArg);
	UINT GetNextID();
	CGXTabBeam& GetBeam();
	CWnd* GetActivePane();

	LPCTSTR GetTabName(int nTab);
	LPCTSTR GetTabName(const CWnd* pSheet);
	void SetTabName(int nTab, LPCTSTR szName, BOOL bNotifySheet = TRUE);
	void SetTabName(const CWnd* pSheet, LPCTSTR szName, BOOL bNotifySheet = TRUE);

// Implementation
public:
	virtual ~CGXTabWnd();

protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	// Generated message map functions
	//{{AFX_MSG(CGXTabWnd)
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


/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// CGXEditLabelPopup window

class CGXEditLabelPopup : public CEdit
{
	DECLARE_DYNAMIC(CGXEditLabelPopup);

// Construction
public:
	CGXEditLabelPopup(CRect rect, CWnd* pParentWnd, UINT nID);

// Attributes
public:

// Operations
public:

// Implementation
public:
	virtual ~CGXEditLabelPopup();

protected:
	// Generated message map functions
	//{{AFX_MSG(CGXEditLabelPopup)
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg UINT OnGetDlgCode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

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

#endif // _GXTWND_H_
