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

// gxinfwnd.h : header file
//

#ifndef _GXINFWND_H_
#define _GXINFWND_H_

#ifndef _GXEXT_H_
#include "grid\gxext.h"  // for use as custom control
#endif

#ifndef _GXSPLIT_H_
#include "grid\gxsplit.h"
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

class CGXRecordInfoBeam;
class CGXRecordInfoWnd;
class CGXRecordInfoEdit;

/////////////////////////////////////////////////////////////////////////////
// CGXRecordInfoBeam window

class CGXRecordInfoBeam : public CWnd
{
	DECLARE_DYNCREATE(CGXRecordInfoBeam)
	DECLARE_REGISTER()

// Construction, initialization
public:
	CGXRecordInfoBeam();
	BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);

// Overridables and other helpers (for implementation of derived classes)
protected:
#if _MFC_VER < 0x0300
	// for deriving from a standard control
	virtual WNDPROC* GetSuperWndProcAddr();
#endif

// Attributes
public:
	void    SetCurrentRecord(long nRecord);
	void    SetRecordCount(long nCount);
	long    GetCurrentRecord();
	long    GetRecordCount();
	void    UpdateColors();
	virtual int     GetWidth();

// Operations
public:

// Implementation
public:
	virtual ~CGXRecordInfoBeam();

	virtual BOOL    IsOnFirstRecord();
	virtual BOOL    IsOnLastRecord();
	virtual CString GetCurrentRecordText();

	virtual void    DrawButton(CDC* pDC, int i, BOOL bPressed);

	void    AutoMove(UINT nRefMessage = WM_LBUTTONUP);

	int     ScrollBtnHit(CPoint point, int nButton = -1);
	virtual void    Scroll(int nDirection);

	void CreateEditWnd(const RECT& rect);
	void CreateFonts();
	void DestroyFonts();
	void SetNotifyWnd(CWnd* pNotify);
	static void AFXAPI DrawBlankButton(CDC* pDC, int x, int y, int dx, int dy, BOOL bPressed);
	static void AFXAPI PatB(CDC* pDC,int x,int y,int dx,int dy, COLORREF rgb);

// Implementation - Attributes
	CFont*      m_pFont;                // font

	COLORREF    m_rgbText;              // text color
	COLORREF    m_rgbBack;              // back color
	COLORREF    m_rgbFace;              // button color
	COLORREF    m_rgbBeam;              // beam color

	long        m_nRecordCount;         // no. of records
	long        m_nCurrentRecord;       // current record

	CString     m_strRecord;            // "Record°

	int         m_nHeight;              // height of the beam
	int         m_nButtonWidth;         // width of scroll button (= scroll's thumb button)
	CRect       m_rectInterior;         // interior rect (  Record: xxxx )
	CRect       m_rectEdit;             // edit window
	int         m_nInteriorWidth;       // how big to make the text area in button units.

	// Mouse Actions
	int         m_nBtnDown;
	BOOL        m_bBtnDown;
	BOOL        m_bMouseCapture;

	// Wnd to receive messages
	CWnd*       m_pNotifyWnd;
	CEdit*      m_pWndEdit;

	HCURSOR     m_hcurArrow;

protected:
	// Btn Hot indicators.	
	int m_bBtnHot[4];	

public:
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);

protected:
	// Generated message map functions
	//{{AFX_MSG(CGXRecordInfoBeam)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);	
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnWinIniChange(LPCTSTR lpszSection);
	afx_msg void OnSysColorChange();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CGXRecordInfoWnd window

// this class is based on the source code of the CSplitterWnd class

class CGXRecordInfoWnd: public CWnd
{
	DECLARE_DYNCREATE(CGXRecordInfoWnd)
	DECLARE_REGISTER()

// Construction
public:
	CGXRecordInfoWnd(CRuntimeClass *pBeamClass = RUNTIME_CLASS(CGXRecordInfoBeam));

	// Create the window with a single view
	BOOL Create(CWnd* pParentWnd,
				CCreateContext* pContext,
				DWORD dwStyle = WS_CHILD | WS_VISIBLE |
					WS_HSCROLL,
				UINT nID = AFX_IDW_PANE_FIRST);

// Overridables and other helpers (for implementation of derived classes)
protected:
#if _MFC_VER < 0x0300
	// for deriving from a standard control
	virtual WNDPROC* GetSuperWndProcAddr();
#endif

// Attributes
public:
	CGXRecordInfoBeam* GetBeam();
	CWnd* GetPane();

	BOOL m_bDrawSunken;
		// set m_bDrawSunken = TRUE if you want to draw
		// the grid control with sunken borders in the dialog.
		// This attribute is ignored if the WS_EX_CLIENTEDGE
		// style bit is set for the window.

// Operations
public:
	void GetInsideRect(CRect& rect) const;
	CWnd* AttachWnd(CWnd* pWnd);
	virtual void RecalcLayout();

// Implementation
public:
	virtual ~CGXRecordInfoWnd();

	BOOL CreateCommon(CWnd* pParentWnd, DWORD dwStyle, UINT nID);
	BOOL CreateScrollBarCtrl(DWORD dwStyle, UINT nID);
	void ShowScrollBar(UINT nBar, BOOL bShow);
	CWnd* CreateView(CRuntimeClass* pViewClass, CCreateContext* pContext = NULL, UINT nID = 0);
	void OnDrawSplitter(CDC* pDC, const CRect& rectArg);

// Implementation - Attributes
	CRuntimeClass* m_pBeamClass;    // used for creating the beam
	CGXRecordInfoBeam* m_pBeam;

	CRuntimeClass* m_pViewClass;
	CWnd* m_pPane;

	BOOL m_bHasHScroll, m_bHasVScroll;
	int m_cxVScroll, m_cyHScroll;

	int m_cxBeam;           // size of the beam ( = x-position of the splitter)
	int m_cxWnd;
	int m_cxSplitter;
	int m_nBarWidths;
	BOOL m_bCtrlsCreated;

	HCURSOR m_hcurArrow;
	CBrush m_brErase;
	BOOL m_bForceRecalcLayout;

	UINT m_nFirstViewID;
	UINT m_nLastViewID;

protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	// Generated message map functions
	//{{AFX_MSG(CGXRecordInfoWnd)
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnNcPaint();	
	afx_msg void OnWinIniChange(LPCTSTR lpszSection);
	afx_msg void OnSysColorChange();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CGXRecordInfoEdit window

class CGXRecordInfoEdit : public CEdit
{
// Construction
public:
	CGXRecordInfoEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXRecordInfoEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGXRecordInfoEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXRecordInfoEdit)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg UINT OnGetDlgCode();	
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#if _MFC_VER >= 0x0400

// This class is only supported under MFC 4.x or higher

class CGXRecordInfoSplitterWnd : public CGXSplitterWnd  
{
	DECLARE_DYNAMIC(CGXRecordInfoSplitterWnd)
public:
	CGXRecordInfoSplitterWnd(CRuntimeClass* pBeamClass = RUNTIME_CLASS(CGXRecordInfoBeam));
	virtual ~CGXRecordInfoSplitterWnd();

	CGXRecordInfoBeam* GetBeam();
	virtual void RecalcLayout();    // call after changing sizes

	CRuntimeClass* m_pBeamClass;
	CGXRecordInfoBeam* m_pBeam;

// Overrides
	virtual void SetActivePane(int row, int col, CWnd* pWnd = NULL);
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXRecordInfoSplitterWnd)
	//}}AFX_VIRTUAL

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXRecordInfoSplitterWnd)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

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


#endif // _GXINFWND_H_
