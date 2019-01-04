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

// gxctrli.h : header file
//

#ifndef _GXCTRLI_H
#define _GXCTRLI_H

#ifndef _GXCTRL_H
#include "grid\gxctrl.h"
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


class CGXButton: public CGXChild
{
public:
	// construction, destrcution
	CGXButton(CGXControl* pComposite);

	// Drawing
	virtual void Draw(CDC* pDC, BOOL bActive);
	virtual void Draw(CDC* pDC, BOOL bActive, const CGXStyle& style);


	// Mouse hit
	virtual BOOL LButtonDown(UINT nFlags, CPoint pt);
	virtual BOOL MouseMove(UINT nFlags, CPoint pt);
	virtual BOOL LButtonUp(UINT nFlags, CPoint pt);

	// Keyboard
	virtual BOOL OnGridKeyDown(UINT nChar, UINT nRepCnt, UINT flags);
	virtual BOOL OnGridKeyUp(UINT nChar, UINT nRepCnt, UINT flags);

	virtual void OnGridCancelMode();

protected:
	BOOL m_bPressed;
	BOOL m_bMouseDown;
	BOOL m_bCanPress;
};

class CGXComboBoxButton: public CGXButton
{
public:
	// construction, destrcution
	CGXComboBoxButton(CGXControl* pComposite);

	// Drawing
	virtual void Draw(CDC* pDC, BOOL bActive, const CGXStyle& style);
};

class CGXHotSpotButton: public CGXButton
{
public:
	// construction, destrcution
	CGXHotSpotButton(CGXControl* pComposite);

	// Drawing
	virtual void Draw(CDC* pDC, BOOL bActive);
};

class CGXArrowButton: public CGXButton
{
public:
	// construction, destrcution
	CGXArrowButton(CGXControl* pComposite);

	virtual BOOL MouseMove(UINT nFlags, CPoint pt);
	virtual BOOL LButtonDown(UINT nFlags, CPoint pt);
	virtual BOOL LButtonUp(UINT nFlags, CPoint pt);

	// increase/decrease speed when mouse button is pressed
	DWORD dwLastTick,
		  dwTicksNeeded;
};

class CGXUpArrowButton: public CGXArrowButton
{
public:
	// construction, destrcution
	CGXUpArrowButton(CGXControl* pComposite);

	// Drawing
	virtual void Draw(CDC* pDC, BOOL bActive);
};

class CGXDownArrowButton: public CGXArrowButton
{
public:
	// construction, destrcution
	CGXDownArrowButton(CGXControl* pComposite);

	// Drawing
	virtual void Draw(CDC* pDC, BOOL bActive);
};

// CGXBitmapButtonChild supports device independent bitmaps

class CGXBitmapButtonChild : public CGXButton
{
public:
// Construction
	CGXBitmapButtonChild(CGXControl* pComposite);
	virtual ~CGXBitmapButtonChild();

	BOOL LoadBitmaps(LPCTSTR lpszBitmapResource,
			LPCTSTR lpszBitmapResourceSel = NULL,
			LPCTSTR lpszBitmapResourceFocus = NULL);

	BOOL LoadBitmaps(UINT nIDBitmapResource,
			UINT nIDBitmapResourceSel = 0,
			UINT nIDBitmapResourceFocus = 0);

	// Drawing
	virtual void Draw(CDC* pDC, BOOL bActive);

	virtual CSize GetSize();
	CSize GetSize(HANDLE hbm);

// Implementation:
public:
	// all bitmaps must be the same size
	HANDLE m_hBitmap;           // normal image (REQUIRED)
	HANDLE m_hBitmapSel;        // selected image (OPTIONAL)
	HANDLE m_hBitmapFocus;      // focused but not selected (OPTIONAL)
};

// Compatibility with OG 1.01
// CGXDIBitmapButtonChild functionality has been
// integrated into the CGXBitmapButtonChild in OG 1.1.

#define CGXDIBitmapButtonChild CGXBitmapButtonChild

/////////////////////////////////////////////////////////////////////////////
// CGXPushbutton control

class CGXPushbutton: public CGXControl
{
	DECLARE_CONTROL(CGXPushbutton)

public:
	// Constructor & Destructor
	CGXPushbutton(CGXGridCore* pGrid);
	CGXPushbutton(CGXGridCore* pGrid, CGXButton* pChild);

	// Operations
	virtual void InvertBorders(CDC* pDC, const CRect& r);
		// Prevents inverting the borders for the current cell

	virtual void Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle);

	virtual void Init(ROWCOL nRow, ROWCOL nCol);

	// Optimizing Size
	virtual CSize CalcSize(CDC* pDC, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle, BOOL bVert);

protected:
	virtual void OnInitChildren(ROWCOL nRow, ROWCOL nCol, const CRect& rect);

	// Attributes
	CGXChild* m_pButton;
};

/////////////////////////////////////////////////////////////////////////////
// CGXBitmapButton control

// CGXBitmapButton supports device independent bitmaps

class CGXBitmapButton: public CGXControl
{
	DECLARE_CONTROL(CGXBitmapButton)

// Construction
public:
	// Constructor & Destructor
	CGXBitmapButton(CGXGridCore* pGrid, UINT nIDBitmapResource,
		UINT nIDBitmapResourceSel = 0, UINT nIDBitmapResourceFocus = 0);

	// Operations
	virtual void InvertBorders(CDC* pDC, const CRect& r);
		// Prevents inverting the borders for the current cell

	virtual void Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle);
	virtual CSize CalcSize(CDC* pDC, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle, BOOL bVert);

protected:
	virtual void OnInitChildren(ROWCOL nRow, ROWCOL nCol, const CRect& rect);

	// Attributes
	CGXBitmapButtonChild* m_pButton;
	BOOL m_bInvertBorders;
	BOOL m_bCanPress;
};

// Compatibility with OG 1.01

#define CGXDIBitmapButton CGXBitmapButton

/////////////////////////////////////////////////////////////////////////////
// CGXCheckBox control

class CGXCheckBox: public CGXControl
{
	DECLARE_CONTROL(CGXCheckBox)

public:
	// Constructor & Destructor
	CGXCheckBox(CGXGridCore* pGrid, BOOL bDraw3d = TRUE, UINT nBitmapResourceId = 0, UINT nPrintResourceId = 0);
	virtual ~CGXCheckBox();
	static void AFXAPI AddUserAttributes(CGXStylesMap* stylesMap);

	// Drawing, optimal size
	virtual void Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle);
	virtual CSize CalcSize(CDC* pDC, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle, BOOL bVert);

	// Mouse hit
	virtual BOOL LButtonDown(UINT nFlags, CPoint pt, UINT nHitState);
	virtual BOOL MouseMove(UINT nFlags, CPoint pt, UINT nHitState);
	virtual BOOL LButtonUp(UINT nFlags, CPoint pt, UINT nHitState);
	virtual BOOL LButtonDblClk(UINT nFlags, CPoint pt);

	// Keyboard
	virtual BOOL KeyPressed(UINT nMessage, UINT nChar, UINT nRepCnt = 1, UINT flags = 0);

	// User clicked checkbox
	virtual void OnClickedButton(CGXChild* pChild);

	// System settings
	virtual void OnGridSysColorChange();

	// Checkbox
	virtual UINT GetState(ROWCOL nRow, ROWCOL nCol, const CGXStyle& style);
	virtual void DrawCheckBox(CDC* pDC, CRect rect, UINT nState, DWORD dtAlign, LPCTSTR lpszString);
	virtual CRect ComputeCheckBoxRect(CDC* pDC, CRect rect, LPCTSTR lpszString, DWORD dtAlign);
	virtual COLORREF GetColorValue(COLORREF rgb, BOOL bPrint);

	virtual void DrawXPCheckBox(HTHEME lhTheme, CDC* pDC, CRect rect, UINT nState, DWORD dtAlign, LPCTSTR lpszString);

	virtual BOOL LoadBitmap();  // 0 will load default bitmap
		// If you want to use CGXCheckbox with your own bitmap, you should
		// call LoadBitmap after constructing the CGXCheckBox object

	virtual BOOL ConvertControlTextToValue(CString& str, ROWCOL nRow, ROWCOL nCol, const CGXStyle* pOldStyle);
	virtual void OnGridCancelMode();

	// allows changing the colors that are used in the CB Bitmap
	static void SetCheckBackColor(COLORREF rgb);
	static void SetCheckFrameColor(COLORREF rgb);
	static void ResetCheckColorScheme();

protected:
	BOOL m_bDraw3d;

	HANDLE m_hbitmapCheck;
	HANDLE m_hbitmapPrint;
	UINT m_nBitmapResourceId;
	UINT m_nPrintResourceId;
	CSize m_sizeCheck;
	int m_nCheckBoxSize;

	// internal state - only valid for current cell
	BOOL m_bScope;
	CRect m_rectBox;

	// for changing the checkbox colors
	static BOOL m_gbCheckClrInc;
	static COLORREF m_grgbFrame;
	static COLORREF m_grgbBack;
};


/////////////////////////////////////////////////////////////////////////////
// CGXCheckBoxEx control
//
// Has an active state unlike the regular check box. Will Call OnModify etc...
//
class CGXCheckBoxEx: public CGXCheckBox
{
	DECLARE_CONTROL(CGXCheckBoxEx)

public:
	// Constructor & Destructor
	CGXCheckBoxEx(CGXGridCore* pGrid, BOOL bDraw3d = TRUE, UINT nBitmapResourceId = 0, UINT nPrintResourceId = 0);

	// Status
	virtual BOOL GetModify();
	virtual void SetModify(BOOL bModified);
	virtual BOOL IsActive();
	virtual void SetActive(BOOL bActive);
	virtual BOOL Store();

	// Operations...
	virtual void Init(ROWCOL nRow, ROWCOL nCol);

	// Drawing, optimal size
	virtual void Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle);

	// Mouse hit
	virtual BOOL LButtonDown(UINT nFlags, CPoint pt, UINT nHitState);

	// Keyboard
	virtual BOOL KeyPressed(UINT nMessage, UINT nChar, UINT nRepCnt = 1, UINT flags = 0);

	// User clicked checkbox
	virtual void OnClickedButton(CGXChild* pChild);

protected:
	BOOL m_bActive;
	BOOL m_bModified;

};


/////////////////////////////////////////////////////////////////////////////
// CGXRadioButton control

class CGXRadioButton: public CGXControl
{
	DECLARE_CONTROL(CGXRadioButton)

public:
	CGXRadioButton(CGXGridCore* pGrid, BOOL bDraw3d = FALSE);

	// Drawing, size
	virtual void Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle);
	virtual CSize CalcSize(CDC* pDC, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle, BOOL bVert);

	// Mouse hit
	virtual BOOL LButtonDown(UINT nFlags, CPoint pt, UINT nHitState);
	virtual BOOL LButtonUp(UINT nFlags, CPoint pt, UINT nHitState);

	// Keyboard
	virtual BOOL KeyPressed(UINT nMessage, UINT nChar, UINT nRepCnt = 1, UINT flags = 0);

protected:

	// Attributes:
protected:
	int m_nRadioBtns;   // No. of alternatives
	BOOL m_bDraw3d;
};

/////////////////////////////////////////////////////////////////////

// Has an active state and gives you an option to align radio button horizontally
class CGXRadioButtonEx: public CGXControl
{
	DECLARE_CONTROL(CGXRadioButtonEx)

public:
	CGXRadioButtonEx(CGXGridCore* pGrid, BOOL bDraw3d = FALSE);
	static void AFXAPI AddUserAttributes(CGXStylesMap* stylesMap);

	// Status
	virtual BOOL GetModify();
	virtual void SetModify(BOOL bModified);
	virtual BOOL IsActive();
	virtual void SetActive(BOOL bActive);
	virtual BOOL Store();
	virtual void Init(ROWCOL nRow, ROWCOL nCol);

	// Drawing, size
	virtual void Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle);
	virtual CSize CalcSize(CDC* pDC, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle, BOOL bVert);

	// Mouse hit
	virtual BOOL LButtonDown(UINT nFlags, CPoint pt, UINT nHitState);
	virtual BOOL LButtonUp(UINT nFlags, CPoint pt, UINT nHitState);

	// Keyboard
	virtual BOOL KeyPressed(UINT nMessage, UINT nChar, UINT nRepCnt = 1, UINT flags = 0);

	virtual BOOL IsWindowlessControl();

protected:

	// Attributes:
protected:
	BOOL m_bActive;
	BOOL m_bModified;

	int m_nRadioBtns;   // No. of alternatives
	BOOL m_bDraw3d;
};

/////////////////////////////////////////////////////////////////////////////
// CGXStatic control

class CGXStatic : public CGXControl
{
	DECLARE_CONTROL(CGXStatic)

// Construction
public:
	// Constructor & Destructor
	CGXStatic(CGXGridCore* pGrid);

	virtual CRect GetCellRect(ROWCOL nRow, ROWCOL nCol, LPRECT rectItem = NULL, const CGXStyle* pStyle = NULL);
		// compute the interior rectangle for the text
		// without buttons and borders
	virtual CSize AddBorders(CSize size, const CGXStyle& style);  // counterpart to GetCellRect

	virtual CSize CalcSize(CDC* pDC, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle, BOOL bVert);

	virtual BOOL CanFloatCell(ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, BOOL bFloatOrFlood);

	virtual void Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle);

	// cells tips enable
	void ImplementCellTips();
};

/////////////////////////////////////////////////////////////////////////////
// CGXHeader control

class CGXHeader: public CGXStatic
{
	DECLARE_CONTROL(CGXHeader)

public:
	CGXHeader(CGXGridCore* pGrid);

	virtual void OnGridSysColorChange();

	virtual void Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle);
	virtual void InvertBorders(CDC* pDC, const CRect& r);
	virtual BOOL GetMarkHeaderState(ROWCOL nRow, ROWCOL nCol, const CGXStyle& style);
};

// for compatibility with 1.0, 1.1
#define m_bAlwaysLeftJustified m_bAllwaysLeftJustified

/////////////////////////////////////////////////////////////////////////////
// CGXEditControl control

class CGXEditControl : public CEdit, public CGXStatic
{
	DECLARE_CONTROL(CGXEditControl)
	DECLARE_DYNAMIC(CGXEditControl)

// Construction
public:
	// Constructor & Destructor
	CGXEditControl(CGXGridCore* pGrid, UINT nID = 0);
	virtual ~CGXEditControl();
	virtual CWnd* GetWndPtr() const;

	// Status
	virtual void SetActive(BOOL bActive);
	virtual BOOL IsActive();

	virtual void SetModify(BOOL bModified);
	virtual BOOL GetModify();

	// Operations
	virtual void Init(ROWCOL nRow, ROWCOL nCol);
		// Stores the cell coordinates, resets the style and sets the window text

	virtual BOOL Store();
		// Call SetStyleRange() and assign FALSE to m_bIsActive
		// Cell will be automatically redrawn inactive

	virtual void Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle);
		// Notes on Draw:
		// if (nRow == m_nRow && nCol == m_nCol && m_bHasFocus)
		//     initialize CWnd, make it visible and set focus
		// else {
		//     lookup style and draw static, e.g.:
		//     - edit control with GXDrawTextLikeMultiLineEdit
		// }

	virtual void Hide();
		// Hides the CEdit without changing the m_bIsActive flag

	virtual BOOL GetValue(CString& strResult);
	virtual BOOL CanFloatCell(ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, BOOL bFloatOrFlood);
	virtual BOOL OnEndEditing();
	virtual void SetValue(LPCTSTR pszRawValue);
	virtual void GetCurrentText(CString& strResult);
	virtual void SetCurrentText(const CString& str);
	BOOL SetControlText(ROWCOL nRow, ROWCOL nCol, const CString& str, UINT nFlags, const CGXStyle* pOldStyle);

	virtual BOOL StripSeparatorFromValue(CString& sValue, const CGXStyle* pStyle, double& d);
		// called from Store & ConvertControlTextToValue (handles Paste)
		// to strip group separator from the value before it is stored

	virtual BOOL PutDecInValue(CString& sValue, const CGXStyle* pStyle);
		//called from Init to put correct dec sep in windowtext

	virtual BOOL AcceptCommasInNumbers(const CGXStyle* pStyle);
		//returns whether strings with thousands separator should be treated
		//as a number. Default behavior is to check for a number format
		//(eg. GX_FMT_FIXED)

	// Mouse hit
	virtual BOOL LButtonUp(UINT nFlags, CPoint pt, UINT nHitState);
	virtual BOOL LButtonDblClk(UINT nFlags, CPoint pt);

	// Keyboard
	// Called when the user presses a key on the inactive current cell
	virtual BOOL OnGridKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL OnGridChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL OnGridDoubleByteChar(const CString& sChar, UINT nRepCnt, UINT nFlags);

	// Called from OnChar (lets you change the nChar)
	virtual BOOL OnProcessChar(UINT nChar, UINT nRepCnt, UINT flags);

	// Find and Replace
	virtual BOOL FindText(const GX_FR_STATE& find, ROWCOL nRow, ROWCOL nCol, BOOL bCurrentPos, BOOL bSetCell = FALSE);
	virtual void ReplaceSel(LPCTSTR pszReplaceText);
	virtual BOOL ReplaceAll(const GX_FR_STATE& find, ROWCOL nRow, ROWCOL nCol);
	virtual BOOL GetSelectedText(CString& strResult);

	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

	// clipboard
	virtual BOOL Paste();
	virtual BOOL Cut();
	virtual BOOL Copy();

	// for paste validation
	virtual BOOL ValidatePaste(const CString& sPaste);

	// Edit control only
	int  CalcTextPosUnderPt(CPoint point);
	void SetWrapText(BOOL b);
	void SetRTLReading(BOOL b);
	void SetAllowEnter(BOOL b);
	void SetVertScrollBar(BOOL b);
	void SetCellColor(COLORREF rgb);
	void SetTextAlign(UINT ntAlign);
	void GetSel(int& nStartChar, int& nEndChar) const;
	DWORD GetSel() const;

// Implementation
protected:
	virtual BOOL CreateControl(DWORD dwStyle = 0, LPRECT lpRect = NULL);

	virtual DWORD CalcEditStyle(LPRECT rectNP, int& dyHeight);

	BOOL  UpdateEditStyle();
	int   GetLastVisibleLine(LPRECT lprect = NULL);

// Attributes
public:
	BOOL            m_bAutoSize;
	BOOL            m_bVertScrollBar;
	BOOL            m_bAlwaysLeftJustified;

protected:
	UINT            m_nID;

	BOOL            m_bIsActive;    // indicates, if the CWnd is active
	CFont           m_font;

	COLORREF        m_rgbWndHilightText;

	DWORD   m_dwEditStyle;
	LONG    m_ntAlign;
	BOOL    m_bUpdateEditStyle;
	int     m_dyHeight;
	int     m_dxMaxCharWidth;
	COLORREF
			m_rgbCell;
	BOOL    m_bAllowEnter;
	BOOL    m_bWrapText;
	BOOL	m_bRTL;
	BOOL    m_bSizeChanged;
	CString m_sLastChar;
	BOOL    m_bDoNotEmptyLastChar;
	int     m_nLimitText;
	BOOL    m_bFloatDone;

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXEditControl)
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT flags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT flags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnStyleChanged( int nStyleType, LPSTYLESTRUCT lpStyleStruct );
	//}}AFX_MSG
#if _MFC_VER >= 0x0400
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg LRESULT OnImeStartComposition(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnImeEndComposition(WPARAM wParam, LPARAM lParam);
#endif
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CGXVScrollEdit control

class CGXVScrollEdit: public CGXEditControl
{
	DECLARE_CONTROL(CGXVScrollEdit)
	DECLARE_DYNAMIC(CGXVScrollEdit)

public:
	// Constructor & Destructor
	CGXVScrollEdit(CGXGridCore* pGrid, UINT nID = 0);

	virtual DWORD CalcEditStyle(LPRECT rectNP, int& dyHeight);
	virtual BOOL CanFloatCell(ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, BOOL bFloatOrFlood);

	virtual CRect GetCellRect(ROWCOL nRow, ROWCOL nCol, LPRECT rectItem = NULL, const CGXStyle* pStyle = NULL);

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXVScrollEdit)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CGXHotSpotEdit control

class CGXHotSpotEdit: public CGXEditControl
{
	DECLARE_CONTROL(CGXHotSpotEdit)
	DECLARE_DYNAMIC(CGXHotSpotEdit)

public:
	// Constructor & Destructor
	CGXHotSpotEdit(CGXGridCore* pGrid, UINT nID = 0);
	virtual CRect GetCellRect(ROWCOL nRow, ROWCOL nCol, LPRECT rectItem = NULL, const CGXStyle* pStyle = NULL);
	virtual CSize AddBorders(CSize size, const CGXStyle& style);  // counterpart to GetCellRect

	virtual void Init(ROWCOL nRow, ROWCOL nCol);

	virtual BOOL CanFloatCell(ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, BOOL bFloatOrFlood);

protected:
	virtual void OnInitChildren(ROWCOL nRow, ROWCOL nCol, const CRect& rect);

	// Attributes:
	CGXChild* m_pHotSpot;

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXHotSpotEdit)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CGXSpinEdit control

class CGXSpinEdit: public CGXEditControl
{
	DECLARE_CONTROL(CGXSpinEdit)
	DECLARE_DYNAMIC(CGXSpinEdit)

public:
	// Constructor & Destructor
	CGXSpinEdit(CGXGridCore* pGrid, UINT nID = 0);
	static void AFXAPI AddUserAttributes(CGXStylesMap* stylesMap);

	virtual CRect GetCellRect(ROWCOL nRow, ROWCOL nCol, LPRECT rectItem = NULL, const CGXStyle* pStyle = NULL);

	virtual void Init(ROWCOL nRow, ROWCOL nCol);

	virtual CSize AddBorders(CSize size, const CGXStyle& style);  // counterpart to GetCellRect
	virtual BOOL CanFloatCell(ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, BOOL bFloatOrFlood);

protected:
	virtual BOOL LButtonDown(UINT nFlags, CPoint pt, UINT nHitState);
	virtual BOOL LButtonUp(UINT nFlags, CPoint pt, UINT nHitState);
	virtual void OnInitChildren(ROWCOL nRow, ROWCOL nCol, const CRect& rect);
	virtual void OnClickedButton(CGXChild* pChild);

	// Attributes:
	CGXChild* m_pUpArrow;
	CGXChild* m_pDownArrow;

	BOOL m_bWrap;
	LONG m_nMinBound, m_nMaxBound;
	BOOL m_bMinBound, m_bMaxBound;
	BOOL m_bStartValue;
	LONG m_nStartValue;

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXSpinEdit)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CGXComboBox control

// when the user presses the dropdown button,
// a CGXGridCombo window is displayed with WS_POPUP style
// and a CGXComboListBox window is embedded into the CGXGridCombo window.
//
// CGXComboListBox sends messages WM_GX_LBOXEND, WM_GX_LBOXCANCEL
// and WM_GX_LBOXCHANGED to the CGXComboBox control.
//
// When CGXComboBox receives a WM_GX_LBOXEND message, the current
// selection is stored and the listbox is destroyed.
//
// When CGXComboBox receives a WM_GX_LBOXCHANGE, the edit text is
// updated.
//
// When CGXComboBox receives a WM_GX_LBOXCANCEL, the listbox will
// be destroyed.
//

// flags
const UINT GXCOMBO_TEXTFIT   = 0x0001;
	// combobox adapts input text to an item in the dropdown list
const UINT GXCOMBO_NOTEXTFIT = 0x0002;
	// user can input any text
const UINT GXCOMBO_ZEROBASED = 0x0004;
	// cell value is a zero-based index
const UINT GXCOMBO_ONEBASED  = 0x0008;
	// cell value is a one-based index
const UINT GXCOMBO_DISPLAYCHOICE  = 0x0010;
	// must be combined either with GXCOMBO_ONEBASED or GXCOMBO_ZEROBASED
	// cell value is a index but the choice is displayed in the cell

 // CGXComboListBox will be embedded into the CGXGridCombo window.

class CGXComboListBox : public CListBox
{
	DECLARE_DYNAMIC(CGXComboListBox)

// Construction
public:
	CGXComboListBox(CWnd* pMsgWnd);
	virtual ~CGXComboListBox();

    // [VC7] CListBox Create Function returns BOOL.
	BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID = 0);

// Operations
public:
	void SetBackColor(COLORREF rgb);

// Implementation
protected:
	// Attributes
	BOOL    m_bKeyDown;
	BOOL    m_bLButtonDown;
	CWnd*   m_pMsgWnd;
	BOOL    m_bColor;
	COLORREF m_rgbBack;
	int     m_nOldSel;
	BOOL    m_bAlNum;
	int		m_nRepCnt;

protected:
	// Generated message map functions
	//{{AFX_MSG(CGXComboListBox)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

// CGXComboBox is the control which encapsulates
// the combobox behaviour.

class CGXComboBox: public CGXEditControl
{
	DECLARE_CONTROL(CGXComboBox)
	DECLARE_DYNAMIC(CGXComboBox)

public:
	// Constructor & Destructor
	CGXComboBox(CGXGridCore* pGrid, UINT nEditID, UINT nListBoxID, UINT nFlags);
	virtual ~CGXComboBox();

	virtual CRect GetCellRect(ROWCOL nRow, ROWCOL nCol, LPRECT rectItem = NULL, const CGXStyle* pStyle = NULL);
	virtual CSize AddBorders(CSize size, const CGXStyle& style);  // counterpart to GetCellRect

	virtual void Init(ROWCOL nRow, ROWCOL nCol);

	virtual CSize CalcSize(CDC* pDC, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle, BOOL bVert);

	// Keyboard
	virtual BOOL OnGridSysKeyDown(UINT nChar, UINT nRepCnt, UINT flags);
	virtual BOOL OnGridChar(UINT nChar, UINT nRepCnt, UINT flags);

	// WM_MOUSEACTIVATE message
	virtual BOOL MouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message, int& retval);

	// override this method for ownerdrawn list-boxes.
	virtual CGXGridCombo* CreateDropDown(CWnd* pWnd, const CRect& rect);
	virtual CWnd* CreateListBox(CWnd* pParentWnd, UINT nID = 0);
	virtual void ShowDropDown(BOOL bShow);
	virtual BOOL GetDroppedState();
	virtual BOOL ValidateString(const CString& sEdit);
	virtual void ReplaceSel(LPCTSTR pszReplaceText);

	virtual CGXGridCombo* GetGridComboBox() { return m_pDropDownWnd; }

	virtual BOOL GetControlText(CString& strResult, ROWCOL nRow, ROWCOL nCol, LPCTSTR pszRawValue, const CGXStyle& style);
	virtual BOOL ConvertControlTextToValue(CString& str, ROWCOL nRow, ROWCOL nCol, const CGXStyle* pOldStyle);
	virtual BOOL GetValue(CString& strResult);

	virtual void Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle);

	virtual BOOL CanFloatCell(ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, BOOL bFloatOrFlood);

	// Status
	virtual BOOL Store();
	virtual void SetActive(BOOL bActive);
	virtual void Reset();
	virtual void OnNotifyMsg(MSG* pMsg);

protected:
	// Childs
	virtual void OnInitChildren(ROWCOL nRow, ROWCOL nCol, const CRect& rect);
	virtual void OnClickedButton(CGXChild* pChild);

	// Override these methods if you don't want to fill the list from the coice-list
	virtual void OnStoreDroppedList(CListBox* lbox);
	virtual void OnFillDroppedList(CListBox* lbox);

	// Override this method for changing the defaulting listbox size
	virtual CRect OnGetListboxRect(const CRect& rcCellRect);

	// Override this method if you don't want that
	// the listbox will be destroyed
	virtual void DestroyDropDownWnd(CWnd* pDropDownWnd);

	// Attributes:
public:
	BOOL            m_bFillWithChoiceList;
	BOOL            m_bInactiveDrawAllCell; // draw text over pushbutton when inactive
	BOOL            m_bInactiveDrawButton;  // draw pushbutton when inactive
	UINT            m_nFlags;
	DWORD           m_dwListBoxStyle;       // default style for dropdown-list
	BOOL            m_bDropdownOnly;        // set this TRUE if text shall not be editable
	BOOL            m_bSizeToContent;       // set FALSE if button shall have the same height as cell


protected:
	CGXChild*       m_pButton;
	UINT            m_nListBoxID;
	CGXGridCombo*   m_pDropDownWnd;
	CFont           m_fontCombo;

	// Implementation
	int             m_nDefaultHeight;
	int             m_nExtraFrame;

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXComboBox)
	afx_msg LRESULT OnListBoxEnd(WPARAM, LPARAM);
	afx_msg LRESULT OnListBoxCancel(WPARAM, LPARAM);
	afx_msg LRESULT OnListBoxChanged(WPARAM, LPARAM);
	afx_msg LRESULT OnListBoxKillFocus(WPARAM, LPARAM);
	afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CGXListBox control

class CGXListBox: public CListBox, public CGXControl
{
	DECLARE_CONTROL(CGXListBox)
	DECLARE_DYNAMIC(CGXListBox)

// Construction
public:
	// Constructor & Destructor
	CGXListBox(CGXGridCore* pGrid, UINT nID = 0);
	virtual ~CGXListBox();
	virtual CWnd* GetWndPtr() const;

	// Status
	virtual void SetActive(BOOL bActive);
	virtual BOOL IsActive();

	virtual void SetModify(BOOL bModified);
	virtual BOOL GetModify();

	virtual void GetCurrentText(CString& strResult);
	virtual void SetCurrentText(const CString& str);

	// Operations
	virtual void Init(ROWCOL nRow, ROWCOL nCol);

	virtual BOOL Store();

	virtual CRect GetCellRect(ROWCOL nRow, ROWCOL nCol, LPRECT rectItem = NULL, const CGXStyle* pStyle = NULL);
	virtual CSize AddBorders(CSize size, const CGXStyle& style);  // counterpart to GetCellRect
	virtual CSize CalcSize(CDC* pDC, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle, BOOL bVert);
	virtual void Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle);
	virtual void Hide();

	// Mouse hit
	virtual BOOL LButtonUp(UINT nFlags, CPoint pt, UINT nHitState);
	virtual BOOL LButtonDblClk(UINT nFlags, CPoint pt);

	// Keyboard
	virtual BOOL KeyPressed(UINT nMessage, UINT nChar, UINT nRepCnt = 1, UINT flags = 0);

	// Notifications
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

	// Listbox control only
	virtual void FillListBox();

// Implementation
protected:
	virtual BOOL CreateControl();
	void SetCellColor(COLORREF rgb);

// Attributes
private:
	UINT            m_nID;

	BOOL            m_bIsActive;    // indicates, if the CWnd is active
	BOOL            m_bIsModify;
	CFont           m_font;

	COLORREF        m_rgbWndHilightText;

	int     m_dyHeight;
	COLORREF
			m_rgbCell;

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXListBox)
	afx_msg UINT OnGetDlgCode();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CGXComboEditPart window

// this class defines the subclassed edit portion of the CGXComboBoxWnd

class CGXComboEditPart : public CEdit
{
// Construction
public:
	CGXComboEditPart();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXComboEditPart)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGXComboEditPart();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXComboEditPart)
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CGXComboBoxWndButton child control

class CGXComboBoxWndButton: public CGXButton
{
public:
	// construction, destrcution
	CGXComboBoxWndButton(CGXControl* pComposite);

	// Drawing
	virtual void Draw(CDC* pDC, BOOL bActive);
	virtual void Draw(CDC* pDC, BOOL bActive, const CGXStyle& style);
};

/////////////////////////////////////////////////////////////////////////////
// CGXComboBoxWnd control

class CGXComboBoxWnd : public CComboBox, public CGXStatic
{
	DECLARE_CONTROL(CGXComboBoxWnd)
	DECLARE_DYNAMIC(CGXComboBoxWnd)

// Construction
public:
	// Constructor & Destructor
	CGXComboBoxWnd(CGXGridCore* pGrid);
	virtual ~CGXComboBoxWnd();
	virtual CWnd* GetWndPtr() const;

	BOOL Create(DWORD dwStyle, UINT nID = 0);

	// Status
	virtual void SetActive(BOOL bActive);
	virtual BOOL IsActive();

	virtual void SetModify(BOOL bModified);
	virtual BOOL GetModify();

	// Operations
	virtual void Init(ROWCOL nRow, ROWCOL nCol);
	virtual CSize CalcSize(CDC* pDC, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle, BOOL bVert);
	virtual CRect GetCellRect(ROWCOL nRow, ROWCOL nCol, LPRECT rectItem = NULL, const CGXStyle* pStyle = NULL);
	virtual CSize AddBorders(CSize size, const CGXStyle& style);  // counterpart to GetCellRect
	virtual BOOL Store();
	virtual void Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle);
	virtual void Hide();
	virtual BOOL LButtonUp(UINT nFlags, CPoint pt, UINT nHitState);
	virtual BOOL LButtonDblClk(UINT nFlags, CPoint pt);
	virtual void OnClickedButton(CGXChild* pChild);
	virtual BOOL OnGridKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL OnGridSysKeyDown(UINT nChar, UINT nRepCnt, UINT flags);
	virtual BOOL OnGridChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL OnGridDoubleByteChar(const CString& sChar, UINT nRepCnt, UINT nFlags);
	virtual void GetCurrentText(CString& strResult);
	virtual void SetCurrentText(const CString& str);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	void GetEditSel(int& nStart, int& nEnd);
	BOOL SetEditSel(int nStart, int nEnd);

	virtual BOOL GetControlText(CString& strResult, ROWCOL nRow, ROWCOL nCol, LPCTSTR pszRawValue, const CGXStyle& style);
	virtual BOOL ConvertControlTextToValue(CString& str, ROWCOL nRow, ROWCOL nCol, const CGXStyle* pOldStyle);
	virtual void SetValue(LPCTSTR pszRawValue);
	virtual BOOL GetValue(CString& strResult);
	virtual BOOL ValidateString(const CString& sEdit);
	virtual BOOL CanFloatCell(ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, BOOL bFloatOrFlood);

	// Override this method for changing the defaulting listbox size
	virtual CRect OnGetListboxRect(const CRect& rcCellRect);

	// Find and Replace
	virtual BOOL FindText(const GX_FR_STATE& find, ROWCOL nRow, ROWCOL nCol, BOOL bCurrentPos, BOOL bSetCell = FALSE);
	virtual void ReplaceSel(LPCTSTR pszReplaceText);
	virtual BOOL ReplaceAll(const GX_FR_STATE& find, ROWCOL nRow, ROWCOL nCol);

	virtual BOOL GetSelectedText(CString& strResult);

	// color
	void SetCellColor(COLORREF rgb);

	void GetWindowText(CString& rString) const;
	int GetWindowText(LPTSTR lpszStringBuf, int nMaxCount) const;

	//overridden to handle ignoring deletes for nonactive dropdownlists
	virtual BOOL SetControlText(ROWCOL nRow, ROWCOL nCol, const CString& str, UINT nFlags = GX_UPDATENOW, const CGXStyle* pOldStyle = NULL);



// Implementation
protected:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnKeyDown(UINT nChar, UINT nRepCnt, UINT flags);
	virtual void OnSetfocus();

	// Childs
	virtual void OnInitChildren(ROWCOL nRow, ROWCOL nCol, const CRect& rect);

	void SetActiveAndDropDown();

// Attributes
public:
	int             m_nExtraFrame;  // extra frame for combobox in cell

	BOOL            m_bFillWithChoiceList;
	BOOL            m_bWantArrowKeys;
	BOOL            m_bSizeToContent;
	int             m_nIndexValue;
	BOOL            m_bDispChoice;
	BOOL            m_bDropDownOnClick;
	BOOL            m_bInactiveDrawButton;
	BOOL            m_bInactiveDrawAllCell;
	BOOL            m_bForceInsideCell;
	BOOL			m_bFindTextSupported;

	CGXComboEditPart m_wndEdit;

	CGXChild*       m_pButton;

protected:
	BOOL            m_bIsActive;    // indicates, if the CWnd is active
	BOOL            m_bModified;

	CFont           m_font;

	COLORREF        m_rgbWndHilightText;
	COLORREF        m_rgbCell;

	int             m_nStartChar,
					m_nEndChar;

	BOOL            m_bDropDownOnNextSetFocus;

	int             m_nDefaultHeight;
	BOOL            m_bDraw3dFrame;
	CString			m_sOldText;
	int             m_nOldSel;

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXComboBoxWnd)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	friend class CGXComboEditPart;
};

/////////////////////////////////////////////////////////////////////////////
// CGXWndWrapper control

class CGXWndWrapper: public CGXControl
{
	DECLARE_CONTROL(CGXWndWrapper)

// Construction
public:
	// Constructor & Destructor
	CGXWndWrapper(CGXGridCore* pGrid, CWnd* pWnd, BOOL bNeedDestroy = FALSE, BOOL bCanActivate = FALSE, BOOL bInvertBorders = TRUE);
		// bCanActivate should be FALSE for Bitmaps, TRUE for controls
		// Please note that if you want to use CWnds in your grid,
		// you should consider subclassing with multiple inheritance from
		// CGXControl and CWnd (see CGXListBox or CGXEditControl for example).
		// By subclassing you have a compatible interface to the grid,
		// but also access to the message-map inherited from CWnd.
	virtual ~CGXWndWrapper();

	virtual CWnd* GetWndPtr() const;

	// Status
	virtual void SetActive(BOOL bActive);
	virtual BOOL IsActive();

	// Operations
	virtual void Init(ROWCOL nRow, ROWCOL nCol);
		// Stores the cell coordinates, resets the style and sets the window text

	virtual void Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle);
		// Notes on Draw:
		// Invalidates and updates the decorated windows
		// if (nRow == m_nRow && nCol == m_nCol && m_bHasFocus)
		//     set focus
		// else {
		//     set window inactive
		// }


	virtual void InvertBorders(CDC* pDC, const CRect& r);
	virtual void Hide();
	virtual BOOL OnEndEditing();


	// Mouse hit
	virtual BOOL LButtonUp(UINT nFlags, CPoint pt, UINT nHitState);

	// Keyboard
	virtual BOOL KeyPressed(UINT nMessage, UINT nChar, UINT nRepCnt = 1, UINT flags = 0);

protected:
	// default constructor for derived classes only
	CGXWndWrapper(CGXGridCore* pGrid);

// Attributes
protected:
	CWnd*           m_pWnd;

	BOOL            m_bIsActive;    // indicates, if the CWnd is active
	CFont           m_font;
	BOOL            m_bCanActivate; // FALSE for Bitmaps, TRUE for controls
	BOOL            m_bNeedDestroy; // TRUE when m_pWnd must be deleted
	BOOL            m_bInvertBorders;
};

/////////////////////////////////////////////////////////////////////////////
// CGXMaskControl control

// CGXMaskData

class CGXMaskData: public CObject
{
	DECLARE_DYNCREATE(CGXMaskData);

public:
	// construction, destruction
	CGXMaskData();
	virtual ~CGXMaskData();

	virtual void Empty();

	// Prepare mask
	virtual void SetMask(LPCTSTR strMask);

	// Data
	virtual void GetData(CString& strData, int nFirstChar = 0, int nLastChar = -1, BOOL bTrim = TRUE) const;    // filters out mask chars from m_astrDisplay and
				// replaces m_chPrompt chars with blanks
				// Return Value: TRUE if valid, FALSE if invalid chars

	virtual int SetData(LPCTSTR strData, int nStartPos = -1, BOOL bInsert = FALSE);
				// Adds mask chars to m_astrDisplay and
				// replaces blanks with m_chPrompt chars
				// Return Value: TRUE if valid, FALSE if invalid chars

	virtual void GetDisplayString(CString& strDisplay, int nFirstChar = 0, int nLastChar = -1) const;
				// Build strDisplay from m_astrDisplay

	virtual int SetDisplayString(LPCTSTR strDisplay, int nStartPos = -1, BOOL bInsert = FALSE);
				// Initializes m_astrDisplay

	BOOL SetPromptChar(const CString& sPrompt, BOOL bUpdateDisplayString = TRUE);

	const CString& GetPromptChar() const;

	virtual BOOL IsCharValid(int nPos, CString& sChar) const;

	virtual int GetNextDataPos(int nOldPos) const;
	virtual int GetPrevDataPos(int nOldPos) const;
	virtual int FindLastFilledDataPos(int nStartPos) const;

	virtual int PushChar(int nStartPos, const CString& sChar, int& nNextPos);
		// adds a character and returns the next data posiition
	virtual void PullChar(int nFromPos, int nToPos);

	// Validation
	virtual BOOL IsValidDisplayString() const;
				// Checks if m_astrDisplay is valid

	virtual BOOL IsEmptyMask() const;
				// Checks if there is a mask

	virtual int GetTextLength() const;

	virtual int GetEditPos(int nCharPos) const;
	virtual int GetCharPos(int nEditPos) const;

	virtual void ClearData();

	virtual void SetMaxLength(int nLength);
	virtual int SetMaxLength() const;

	// Overridables
	virtual BOOL IsMaskChar(TCHAR ch) const;

	// Helper functions
	virtual BOOL IsLiteral(int nPos) const;

protected:
	// Data members (arrays make it easier to handle multi byte chars)
	CStringArray m_astrMask;       // Holds the mask chars
	CByteArray64 m_abIsLiteral;    // Holds information which characters are literal
	CStringArray m_astrDisplay;    // Holds the display string
	CString m_sPrompt;             // The prompt character, space is default.
	BOOL m_bIgnoreEmptyMask;       // Ignore Mask when it is empty
	int m_nMaxLength;              // Use this as maximum length when mask is empty
#ifdef _MBCS
	static BOOL m_bDBCSEnabled;
#endif
};


// CGXMaskControl

class CGXMaskControl : public CEdit, public CGXStatic
{
	DECLARE_CONTROL(CGXMaskControl)
	DECLARE_DYNAMIC(CGXMaskControl)

// Construction
public:
	// Constructor & Destructor
	CGXMaskControl(CGXGridCore* pGrid, UINT nID = 0, CRuntimeClass* pDataClass = RUNTIME_CLASS(CGXMaskData));
	virtual ~CGXMaskControl();
	static void AFXAPI AddUserAttributes(CGXStylesMap* stylesMap);

	void AttachData(CRuntimeClass* pDataClass = RUNTIME_CLASS(CGXMaskData));
	virtual BOOL CreateControl(DWORD dwStyle = 0, LPRECT lpRect = NULL);
	virtual CWnd* GetWndPtr() const;

	// Status
	virtual void SetActive(BOOL bActive);
	virtual BOOL IsActive();

	virtual void SetModify(BOOL bModified);
	virtual BOOL GetModify();

	// Operations
	virtual void Init(ROWCOL nRow, ROWCOL nCol);
		// Stores the cell coordinates, resets the style and sets the window text

	virtual BOOL Store();
		// Call SetStyleRange() and assign FALSE to m_bIsActive
		// Cell will be automatically redrawn inactive

	virtual BOOL OnValidate();

	virtual void Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle);
		// Notes on Draw:
		// if (nRow == m_nRow && nCol == m_nCol && m_bHasFocus)
		//     initialize CWnd, make it visible and set focus
		// else {
		//     lookup style and draw static, e.g.:
		//     - edit control with GXDrawTextLikeMultiLineEdit
		// }

	virtual void Hide();
		// Hides the CEdit without changing the m_bIsActive flag

	virtual BOOL GetValue(CString& strResult);
	virtual void SetValue(LPCTSTR pszRawValue);
	virtual void GetCurrentText(CString& strResult);
	virtual void SetCurrentText(const CString& str);
	virtual BOOL GetControlText(CString& strResult, ROWCOL nRow, ROWCOL nCol, LPCTSTR pszRawValue, const CGXStyle& style);
	virtual BOOL ConvertControlTextToValue(CString& str, ROWCOL nRow, ROWCOL nCol, const CGXStyle* pOldStyle);

	virtual void InitMask(CGXMaskData* pMask, const CGXStyle& style);

	// Mouse hit
	virtual BOOL LButtonUp(UINT nFlags, CPoint pt, UINT nHitState);
	virtual BOOL LButtonDblClk(UINT nFlags, CPoint pt);

	// Keyboard
	// Called when the user presses a key on the inactive current cell
	virtual BOOL OnGridKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL OnGridChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL OnGridDoubleByteChar(const CString& sChar, UINT nRepCnt, UINT nFlags);

	// Find and Replace
	virtual BOOL FindText(const GX_FR_STATE& find, ROWCOL nRow, ROWCOL nCol, BOOL bCurrentPos, BOOL bSetCell = FALSE);
	virtual void ReplaceSel(LPCTSTR pszReplaceText);
	virtual BOOL ReplaceAll(const GX_FR_STATE& find, ROWCOL nRow, ROWCOL nCol);
	virtual BOOL GetSelectedText(CString& strResult);

	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

	// Edit control only
	int  CalcTextPosUnderPt(CPoint point);
	void SetCellColor(COLORREF rgb);
	void SetTextAlign(UINT ntAlign);
	void GetSel(int& nStartChar, int& nEndChar) const;
	DWORD GetSel() const;
	void GetCharSel(int& nPosition, int& nEndPos) const;
	void SetCharSel(int nPosition, int nEndPos, BOOL bNoScroll = FALSE);
	void SendEvent(UINT nEvent);

	// Clipboard
	virtual BOOL Copy();
	virtual BOOL Paste();
	virtual BOOL Cut();
	virtual BOOL CanCopy();
	virtual BOOL CanCut();
	virtual BOOL CanPaste();

// Implementation
protected:
	virtual DWORD CalcEditStyle(LPRECT rectNP, int& dyHeight);
	void UpdateDisplay(LPCTSTR lpszText = NULL);

	BOOL  UpdateEditStyle();
	int   GetLastVisibleLine(LPRECT lprect = NULL);

// Attributes
public:
	BOOL            m_bDisplayEmpty;    // Set this TRUE if mask should
		// also be displayed for empty values

	BOOL            m_bAlwaysLeftJustified;
	CGXMaskData*    m_pMask;
	CGXMaskData*    m_pExtMask;

protected:
	UINT            m_nID;

	BOOL            m_bIsActive;    // indicates, if the CWnd is active
	BOOL            m_bInsertMode;
	CFont           m_font;

	COLORREF        m_rgbWndHilightText;

	DWORD   m_dwEditStyle;
	LONG    m_ntAlign;
	BOOL    m_bUpdateEditStyle;
	int     m_dyHeight;
	int     m_dxMaxCharWidth;
	COLORREF
			m_rgbCell;
	BOOL    m_bForceReplaceData;
	// Generated message map functions
protected:
	//{{AFX_MSG(CGXMaskControl)
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT flags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT flags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
#if _MFC_VER >= 0x0300
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
#endif
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// Password control

class CGXPasswordControl: public CGXEditControl
{
	DECLARE_CONTROL(CGXPasswordControl)
	DECLARE_DYNAMIC(CGXPasswordControl)

public:
	// Constructor & Destructor
	CGXPasswordControl(CGXGridCore* pGrid, UINT nID = 0);

	// Overrides
	virtual BOOL GetControlText(CString& sResult, ROWCOL nRow, ROWCOL nCol, LPCTSTR pszRawValue, const CGXStyle& style);
	virtual void SetValue(LPCTSTR pszRawValue);
	virtual DWORD CalcEditStyle(LPRECT rectNP, int& dyHeight);
	virtual BOOL CanFloatCell(ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, BOOL bFloatOrFlood);

	// Disable Copy and Cut operations, so that user
	// cannot paste text into another application to
	// check out the cells contents
	virtual BOOL Copy();
	virtual BOOL Cut();

	// Attributes
	BOOL m_bReplaceAsterisk;
	TCHAR m_chPasswordChar;

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXPasswordControl)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CGXProgressCtrl control

class CGXProgressCtrl: public CGXControl
{
	DECLARE_CONTROL(CGXProgressCtrl)

public:
	// Construction/Destruction
	CGXProgressCtrl(CGXGridCore* pGrid);
	virtual ~CGXProgressCtrl();

public:
	// Initialization
	static void AFXAPI AddUserAttributes(CGXStylesMap* pStylesMap);

	// optimized method for changing the value
	static BOOL AFXAPI SetProgressValue(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol, LONG newPos);

	// CGXControl overridables
	virtual void Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle);
	virtual BOOL StoreStyle(ROWCOL nRow, ROWCOL nCol, const CGXStyle* pStyle, GXModifyType mt, int nType, const CGXStyle* pOldStyle);

	// Overridables
protected:
	virtual void OnGetCaption(CString& strCaption, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style);
	virtual COLORREF OnGetCaptionColor(BOOL bForeOrBack, const CGXStyle& style);
	virtual COLORREF OnGetCaptionTextColor(BOOL bForeOrBack, const CGXStyle& style);

	// Implementation
	CRect GetUpdateRect(LONG newValue, CRect boundRect, const CGXStyle& style);
	void UpdateUnitFactor(CRect boundRect, LONG normVal);

	// Attributes
protected:
	double m_unitFactor;
};

/////////////////////////////////////////////////////////////////////////////
// CGXTabbedComboBox control

class CGXTabbedComboLBox;
class CGXTabbedComboBox;
class CGXTabbedLBoxHeader;

class CGXTabbedComboBox : public CGXComboBox
{
	DECLARE_CONTROL(CGXTabbedComboBox)
	DECLARE_DYNAMIC(CGXTabbedComboBox)

// Construction
public:
	CGXTabbedComboBox(CGXGridCore* pGrid, UINT nEditID = 0, UINT nListBoxID = 0);
	static void AFXAPI AddUserAttributes(CGXStylesMap* stylesMap);

// Attributes
public:
	int m_nValueCol;        // Value to be stored in style
	int m_nDisplayCol;      // Text to be displayed in cell
	BOOL m_bDispAllCols;    // display table-like dropdown list
	BOOL m_bDisplayTitleRow;// Use first line in choice list
							// to display titles for each column
	int m_nSortCol;			// Sort the choicelist
	CString m_strColWidths; // Column Widths

	COLORREF m_rgbGridLine;
	COLORREF m_rgbBackColor;
	COLORREF m_rgbTextColor;
	BOOL m_bCheckAndFillCBEdit; // MS Access like replacing of edit text
	int m_nDefaultHeight;

	int m_nCurFillChoicelistId;
	LONG m_nSerial;

public:
	// Constructor & Destructor
	virtual ~CGXTabbedComboBox();

// Operations
public:
	void SetTabStops(int iTabStops);
	void AddTabStop(int iIndex, int iTabStop);
	virtual void CheckAndFillCBEdit();
	CMapStringToString* GetValueToChoiceMap(const CGXStyle& style);
	CMapStringToString* GetTextToChoiceMap(const CGXStyle& style);
	static void AFXAPI ResetChoiceMap(CGXGridParam* pParam, int nChoiceListId = -1);

// Overrides
	virtual void Init(ROWCOL nRow, ROWCOL nCol);
	virtual void Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle);
	virtual BOOL StoreStyle(ROWCOL nRow, ROWCOL nCol, const CGXStyle* pStyle, GXModifyType mt, int nType, const CGXStyle* pOldStyle);

	virtual void SetValue(LPCTSTR pszRawValue);
	virtual BOOL GetValue(CString& strResult);
	virtual BOOL GetControlText(CString& strResult, ROWCOL nRow, ROWCOL nCol, LPCTSTR pszRawValue, const CGXStyle& style);
	virtual BOOL ConvertControlTextToValue(CString& str, ROWCOL nRow, ROWCOL nCol, const CGXStyle* pOldStyle);

	virtual BOOL OnValidate();
	virtual CSize CalcSize(CDC* pDC, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle, BOOL bVert);

	virtual CGXGridCombo* CreateDropDown(CWnd* pWnd, const CRect& rect);
	virtual CWnd* CreateListBox(CWnd* pParentWnd, UINT nID);
	virtual CRect OnGetListboxRect(const CRect& rcCellRect);
	virtual void OnStoreDroppedList(CListBox* lbox);
	virtual void OnFillDroppedList(CListBox* lbox);
	virtual void DestroyDropDownWnd(CWnd* pDropDownWnd);
	virtual void ShowDropDown(BOOL bShow);
	virtual BOOL KeyPressed(UINT nMessage, UINT nChar, UINT nRepCnt, UINT flags);
	virtual BOOL ValidateString(const CString& sEdit);

protected:
	// interior state for current cell only
	CRect m_rectComboLBox;
	int m_nWidthLBox;
	int m_nColCount;
	int m_iTabCount;
	LPINT m_piarTabStops;
	CGXTabbedLBoxHeader* m_pWndTitleRow;

	BOOL m_bListBoxFilled;
	CGXTabbedComboLBox* m_pComboLbox;
	CGXGridCombo*   m_pComboLboxPopup;

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXTabbedComboBox)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

	friend class CGXTabbedComboLBox;
};

class CGXTabbedComboLBox : public CGXComboListBox
{
// Construction
public:
	CGXTabbedComboLBox(CGXTabbedComboBox* pTabbedComboBox);

// Attributes
	CGXTabbedComboBox* m_pTabbedComboBox;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXDropDownList)
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMIS);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);
	virtual int CompareItem(LPCOMPAREITEMSTRUCT lpCIS);
	//}}AFX_VIRTUAL

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXTabbedComboLBox)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

	friend class CGXTabbedComboBox;
};

class CGXTabbedComboBoxWnd;

class CGXTabbedLBoxHeader;

/////////////////////////////////////////////////////////////////////////////
// CGXTabbedComboBoxWnd window

class CGXTabbedComboBoxWnd : public CGXComboBoxWnd
{
	DECLARE_CONTROL(CGXTabbedComboBoxWnd);
	DECLARE_DYNAMIC(CGXTabbedComboBoxWnd);

// Construction
public:
	CGXTabbedComboBoxWnd(CGXGridCore* pGrid);
	static void AFXAPI AddUserAttributes(CGXStylesMap* stylesMap);

// Attributes
public:
	// for all cells
	int m_nValueCol;        // Value to be stored in style
	int m_nDisplayCol;      // Text to be displayed in cell
	BOOL m_bDispAllCols;    // display table-like dropdown list
	BOOL m_bDisplayTitleRow;    // Use first line in choice list
							// to display titles for each column
	int m_nSortCol;			// Sort the choicelist
	CString m_strColWidths; // Column Widths

	COLORREF m_rgbGridLine;
	COLORREF m_rgbBackColor;
	COLORREF m_rgbTextColor;

	void SetReadOnly(BOOL bReadOnly = TRUE);

// Operations
public:
	void SetTabStops(int iTabStops);
	void AddTabStop(int iIndex, int iTabStop);
	void LoadLBoxEntries();

// Overrides
	virtual HBRUSH OnGridCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL CreateControl(DWORD dwStyle = CBS_DROPDOWN, UINT nID = 0);
	virtual void Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle);
	virtual void Init(ROWCOL nRow, ROWCOL nCol);
	virtual void SetValue(LPCTSTR pszRawValue);
	virtual BOOL GetValue(CString& strResult);
	virtual BOOL GetControlText(CString& strResult, ROWCOL nRow, ROWCOL nCol, LPCTSTR pszRawValue, const CGXStyle& style);
	virtual BOOL ConvertControlTextToValue(CString& str, ROWCOL nRow, ROWCOL nCol, const CGXStyle* pOldStyle);
	virtual BOOL OnValidate();
	virtual void GetCurrentText(CString& strResult);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual void Hide();
	virtual void SetModify(BOOL bModified = TRUE);
	virtual BOOL GetModify();
	virtual BOOL LButtonUp(UINT nFlags, CPoint pt, UINT nHitState);
	virtual void OnClickedButton(CGXChild* pChild);
	void SetActiveAndDropDown();
	virtual BOOL OnKeyDown(UINT nChar, UINT nRepCnt, UINT flags);
	virtual CSize CalcSize(CDC* pDC, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle, BOOL bVert);
	virtual BOOL ValidateString(const CString& sEdit);
	virtual BOOL StoreStyle(ROWCOL nRow, ROWCOL nCol, const CGXStyle* pStyle, GXModifyType mt, int nType, const CGXStyle* pOldStyle);

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXTabbedComboBoxWnd)
	public:
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMIS);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);
	virtual int CompareItem(LPCOMPAREITEMSTRUCT lpCIS);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGXTabbedComboBoxWnd();

	// this class defines the subclassed edit portion of the CGXComboBoxWnd

protected:
	// interior state for current cell only
	CRect m_rectComboLBox;
	int m_nWidthLBox;
	CEdit* m_pWndCBEditPart;
	int m_nColCount;
	int m_iTabCount;
	LPINT m_piarTabStops;
	CGXTabbedLBoxHeader* m_pWndTitleRow;
	BOOL m_bReadOnly;
	BOOL m_bIgnoreNextDraw;
	BOOL m_bLockMeasure;
	CString m_sAddString;

public:
	HWND m_hComboLBox;

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXTabbedComboBoxWnd)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

	friend class CGXTabbedCBEditWnd;
};

// edit box

class CGXTabbedCBEditWnd : public CEdit
{
// Construction
public:
	CGXTabbedCBEditWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXTabbedCBEditWnd)
	protected:
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGXTabbedCBEditWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXTabbedCBEditWnd)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CGXCheckListComboBox

#if _MFC_VER >= 0x0400

class CGXCheckListComboLBox : public CCheckListBox
{
	DECLARE_DYNAMIC(CGXCheckListComboLBox)

// Construction
public:
	CGXCheckListComboLBox(CWnd* pMsgWnd);
	virtual ~CGXCheckListComboLBox();

    // [VC7] Create Function returns BOOL type.
	BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);

// Operations
public:
	void SetBackColor(COLORREF rgb);

// Implementation
protected:
	// Attributes
	BOOL    m_bKeyDown;
	BOOL    m_bLButtonDown;
	CWnd*   m_pMsgWnd;
	BOOL    m_bColor;
	COLORREF m_rgbBack;
	int     m_nOldSel;
	BOOL    m_bAlNum;

protected:
	// Generated message map functions
	//{{AFX_MSG(CGXCheckListComboLBox)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

// CGXComboBox is the control which encapsulates
// the combobox behaviour.

class CGXCheckListComboBox: public CGXComboBox
{
	DECLARE_CONTROL(CGXCheckListComboBox)
	DECLARE_DYNAMIC(CGXCheckListComboBox)

public:
	// Constructor & Destructor
	CGXCheckListComboBox(CGXGridCore* pGrid, UINT nEditID = 0, UINT nListBoxID = 0);
	virtual ~CGXCheckListComboBox();
	virtual BOOL OnProcessChar(UINT nChar, UINT nRepCnt, UINT flags);

	virtual CWnd* CreateListBox(CWnd* pParentWnd, UINT nID);
	virtual BOOL GetControlText(CString& strResult, ROWCOL nRow, ROWCOL nCol, LPCTSTR pszRawValue, const CGXStyle& style);
	virtual void Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle);
//  virtual BOOL GetValue(CString& strResult);

	// Override these methods if you don't want to fill the list from the coice-list
	virtual void OnStoreDroppedList(CListBox* lbox);
	virtual void OnFillDroppedList(CListBox* lbox);

	virtual BOOL KeyPressed(UINT nMessage, UINT nChar, UINT nRepCnt = 1, UINT flags = 0);
	virtual DWORD CalcEditStyle(LPRECT rectNP, int& dyHeight);
	virtual BOOL LButtonUp(UINT nFlags, CPoint pt, UINT nHitState);
	virtual void SetActive(BOOL bActive);
	int m_nCount;

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXCheckListComboBox)
	afx_msg LRESULT OnListBoxEnd(WPARAM, LPARAM);
	afx_msg LRESULT OnListBoxCancel(WPARAM, LPARAM);
	afx_msg LRESULT OnListBoxChanged(WPARAM, LPARAM);
	afx_msg LRESULT OnListBoxKillFocus(WPARAM, LPARAM);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


#endif  // _MFC_VER >= 0x0400

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Inline function declarations

#ifdef _GX_ENABLE_INLINES
#include "grid\gxctrli.inl"
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

#endif // _GXCTRLI_H
