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
// Author: Stefan Hoenig
//
// Portions of this code were copied from Objective Toolkit.

// gxdtctrl.h : Declarations for the Calendar Control
// 

#ifndef _GXCALC_H_
#define _GXCALC_H_

#if _MFC_VER >= 0x0400   // only supported for MFC version 4.0 or greater

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

// CGXBCalculator styles
#define GX_CS_RAISEDEDGE			0x0001L		// Same look as WS_EX_WINDOWEDGE
												// except compatible with Win 3.
#define GX_CS_DIVIDER				0x0002L		// Divider at top of calculator

// CGXBPopupCalculator style
#define GX_PCS_DESTROY_ON_EQUALS	0x0010L		// Popup calculator destroyed
												// everytime equals is pressed.

// Forward references ...
class CGXBCalcBtn;


/////////////////////////////////////////////////////////////////////////////
// CGXBCalculator window
//
class CGXBCalculator : public CWnd
{
	DECLARE_DYNAMIC(CGXBCalculator)

// Construction
public:
	CGXBCalculator();

	BOOL Create(DWORD dwStyle, int x, int y, CWnd* pParentWnd, UINT nID, 
				CCreateContext* pContext = NULL);

	BOOL CreateEx(DWORD dwExStyle, DWORD dwStyle, int x, int y, 
				  CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);

// Attributes
public:
	// List of calculator functions/buttons
	enum CGXBCalcOp
	{
		OpNull     = 0,			// No operation
		OpMultiply = 1,			// Multiply operator
		OpPlus     = 2,			// Plus operator
		OpMinus    = 3,			// Minus operator
		OpDivide   = 4,			// Divide operator
		OpPercent  = 5,			// Percentage operator
		OpEquals   = 6,			// Equals operator
		OpC        = 7,			// Clear function
		OpCE	   = 8,			// Clear error function
		Op0		   = 9,			// Decimal digit 0
		Op1        = 10,		// Decimal digit 1
		Op2        = 11,		// Decimal digit 2
		Op3        = 12,		// Decimal digit 3
		Op4        = 13,		// Decimal digit 4
		Op5        = 14,		// Decimal digit 5
		Op6        = 15,		// Decimal digit 6
		Op7        = 16,		// Decimal digit 7
		Op8        = 17,		// Decimal digit 8
		Op9        = 18,		// Decimal digit 9
		OpDP       = 19,		// Decimal place
		OpBack     = 20,		// Delete last character

		// Operations not yet implemented
		OpMPlus	   = 21,		// Memory add
		OpMMinus   = 22,		// Memory subtract
		OpM        = 23,		// Places current number into memory
		OpMRecall  = 24,		// Memory recall
		OpSqrt     = 25,		// Square root

		// Operations for user use only
		OpUser1    = 100,
		OpUser2    = 101,
		OpUser3    = 102,
		OpUser4    = 103,
		OpUser5    = 104,
		OpUser6    = 105,
		OpUser7    = 106,
		OpUser8    = 107
	};

// Operations
public:
	// Invalidates the button at the given index.
	void InvalidateBtn(int nIndex, BOOL bErase = FALSE);

	// Invalidates the LCD panel
	void InvalidatePanel(BOOL bErase = FALSE);

	// Resets the calculator back to a "zero" state
	void ResetCalc();

	// Returns the index of the button under the given point
	int HitTest(CPoint point) const;

	// Set/Get the current calculator value
	void   SetValue(double val);
	double GetValue() const;

	// Set the maximum number of decimal places to be displayed
	void SetDecimalPlaces(int nDP);
	int  GetDecimalPlaces() const;

// Overrides
protected:
	virtual BOOL CreateBtns(CWnd* pParentWnd);
	virtual BOOL CreatePanel(CWnd* pParentWnd);
	virtual BOOL HandleEvent(CGXBCalcOp op);
	virtual CString LoadDecSeparator();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXBCalculator)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGXBCalculator();

protected:
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);

#ifdef _DEBUG
	virtual void Dump(CDumpContext& dc) const;
	virtual void AssertValid() const;
#endif

protected:
	// Layes out the calculator buttons
	CSize CalcLayout(DWORD dwStyle);

	// Formats the value into a displayable string
	void SetDisplayString();

	// Presses the given button
	void PressBtn(int nIndex);

	// Sizes the panel to the width of the calculator.
	void SizePanel();

	// Formats the current number to the supplied no. of decimal places into
	// the supplied buffer
	void FormatNo(LPTSTR ptr, int nDP);

	// Returns the class style that this window "will" be registered with
	virtual UINT GetClassStyle() const;

	// Draws the calculator
	virtual void Draw(CDC& dc);

	// Draws the panel
	void DrawPanel(CDC& dc);

	// Functions used for handling inputs
	BOOL HandleDigit(CGXBCalcOp op);
	BOOL HandleDecimalPoint(CGXBCalcOp op);
	BOOL HandleBackspace(CGXBCalcOp op);
	BOOL HandleOperator(CGXBCalcOp op);
	BOOL HandleClear(CGXBCalcOp op);
	BOOL HandleClearError(CGXBCalcOp op);

	// Returns the decimal character used by scanf, printf
	TCHAR GetFormatDecimal();

	// Implementation, data members.
protected:
	enum // State flags
	{
		Capture         = 0x0001,	// We currently have capture
		HaveLead        = 0x0002,	// Have received the first byte of a 
									// multi-byte pair
		HasInitialValue = 0x0004,	// Reset won't clear current value
		CalcError       = 0x0008	// Calculator in error (divide by zero etc)
	};

	// General data members
	TCHAR     m_cLeadByte;			// Used by WM_CHAR for saving first byte
									// of multi-byte pair
	int       m_nState;				// Holds the current state(see state flags)

	// Calculation engine data members
	double    m_val;				// The current value 
	CGXBCalcOp m_lastOp;				// The last operator entered. This will
									// be actioned when the next operator is
									// entered.
	BOOL      m_bReplace;			// The next digit entered will replace the
									// current displayed number
	int       m_nDP;				// Max. no. of DP to display to
	int       m_nTotalDigits;		// Total no. of displayable digits
	
	// Panel (LCD display) data members
	CRect     m_panelRect;			// The outer rectange of the panel
	CString   m_strDisplay;			// The current display string for the panel
	CString   m_strDecSep;			// Decimal Separator

	// Drawing/layout data members
	CFont     m_btnFont;			// Font used for drawing buttons
	CFont     m_panelFont;			// Font used for drawing the panel
	HBITMAP   m_hEqualsBmp;			// Handle of bitmap used on equals button
	int       m_nBtnWidth;			// Width of a button (a column)
	int       m_nBtnHeight;			// Height of a button
	int       m_nVIndent;			// Vertical Indent of button matrix
	int       m_nHIndent;			// Horizontal Indent of button matrix
	int       m_nVSpace;			// Space between button rows
	int       m_nHSpace;			// Space between button columns
	int       m_nCapture;			// Index of button with capture

	// We maintain an array of the calculator buttons, m_btns. This would
	// normally be defined with CTypedPtrArray, but templates are not supported
	// by the Microsoft 16-Bit compiler and some Unix compilers. The following
	// is what CTypedPtrArray would have defined.
	class CGXBCalcBtnArray : public CObArray
	{
	public:
		// Accessing elements
		CGXBCalcBtn* GetAt(int nIndex) const
			{ return (CGXBCalcBtn*)CObArray::GetAt(nIndex); }
		CGXBCalcBtn*& ElementAt(int nIndex)
			{ return (CGXBCalcBtn*&)CObArray::ElementAt(nIndex); }
		void SetAt(int nIndex, CGXBCalcBtn* ptr)
			{ CObArray::SetAt(nIndex, (CObject*) ptr); }

		// Potentially growing the array
		void SetAtGrow(int nIndex, CGXBCalcBtn* newElement)
		   { CObArray::SetAtGrow(nIndex, (CObject*) newElement); }
		int Add(CGXBCalcBtn* newElement)
		   { return (int)CObArray::Add((CObject*) newElement); }
#ifdef WIN32
		int Append(const CGXBCalcBtnArray& src)
		   { return (int)CObArray::Append(src); }
		void Copy(const CGXBCalcBtnArray& src)
			{ CObArray::Copy(src); }
#endif

		// Operations that move elements around
		void InsertAt(int nIndex, CGXBCalcBtn* newElement, int nCount = 1)
			{ CObArray::InsertAt(nIndex, (CObject*) newElement, nCount); }
		void InsertAt(int nStartIndex, CGXBCalcBtnArray* pNewArray)
		   { CObArray::InsertAt(nStartIndex, pNewArray); }

		// overloaded operator helpers
		CGXBCalcBtn* operator[](int nIndex) const
			{ return (CGXBCalcBtn*)CObArray::operator[](nIndex); }
		CGXBCalcBtn*& operator[](int nIndex)
			{ return (CGXBCalcBtn*&)CObArray::operator[](nIndex); }
	} m_btns;

	// Implementation - message map and entries
	DECLARE_MESSAGE_MAP()

	afx_msg void OnPaint();
	afx_msg void OnSysColorChange();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnCancelMode();
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnNcPaint();
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
};


/////////////////////////////////////////////////////////////////////////////
// CGXBPopupCalculator window
//
class CGXBPopupCalculator : public CGXBCalculator
{
	DECLARE_DYNAMIC(CGXBPopupCalculator)

// Construction
public:
	CGXBPopupCalculator();

	BOOL Create(DWORD dwStyle, const RECT& ctrlRect, CWnd* pParentWnd, 
				CCreateContext* pContext = NULL);

	BOOL CreateEx(DWORD dwExStyle, DWORD dwStyle, const RECT& ctrlRect, 
				  CWnd* pParentWnd, CCreateContext* pContext = NULL);

// Attributes
public:
	// Set to TRUE if you want the calculator object to be deleted with
	// the window
	BOOL m_bAutoDelete;

// Overrides
public:
	// Called when a button is pressed on the calculator
	virtual BOOL HandleEvent(CGXBCalcOp op);

	// Handles dispatching the result off to interested windows
	virtual void Notify();

// Implementation
public:
	virtual ~CGXBPopupCalculator();

#ifdef _DEBUG
	virtual void Dump(CDumpContext& dc) const;
	virtual void AssertValid() const;
#endif

protected:
	// Returns the class style that this window "will" be registered with
	virtual UINT GetClassStyle() const;

// Implementation - message map and entries
protected:
	DECLARE_MESSAGE_MAP()

	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags );
	virtual void PostNcDestroy();
};


/////////////////////////////////////////////////////////////////////////////

// Function to convert Dialog Base Units to pixels.
CSize AFXAPI CGXBConvertDBU(int x, int y, HFONT hFont = NULL);


/////////////////////////////////////////////////////////////////////////////
// CGXBCalcBtn object
//
class CGXBCalcBtn : public CObject
{
// Construction
public:
	CGXBCalcBtn();

// Attributes
public:
	// Returns the width of the button
	BOOL GetWidth() const;

	// Returns the operation code for this button
	CGXBCalculator::CGXBCalcOp GetOp() const;

	// Set/Get the button state
	int  GetState() const;
	void SetState(int nState);

	// Returns TRUE if the given char is an accelerator for the button
	BOOL IsAccelerator(LPCTSTR lpszChar) const;

	// Returns TRUE if the WM_KEYDOWN char is an accelerator for the button
	BOOL IsKeyDownAccelerator(UINT nChar) const;

	// Sets the WM_KEYDOWN accelerator for this button
	void SetKeyDownAccel(UINT nChar);

	// Set/Get the rectange of the button (relative to calculators client)
	const CRect& GetRect() const;
	void SetRect(const RECT& rect);

	// Defines the attributes used for drawing a calculator button
	class Attrib
	{
	public:
		Attrib();
		Attrib(DWORD dwStyle, COLORREF textColor = 0L, HFONT hFont = NULL, 
			   HBITMAP* lphBitmap = NULL);
		Attrib(const Attrib& attrib);
		~Attrib();

		const Attrib& operator=(const Attrib& attrib);

		HFONT GetFont() const;
		COLORREF GetTextColor() const;
		HBITMAP GetBitmap() const;

	protected:
		HFONT    m_hFont;						// Font handle 
		HBITMAP* m_lphBitmap;					// Bitmap handle
		COLORREF m_textColor;					// Text color
		DWORD    m_dwStyle;						// Style (not currently used)
	};
	
// Operations
public:
	// Initialise button with accelerators are same as caption
	BOOL Initialise(const Attrib& attrib, CGXBCalculator::CGXBCalcOp op, 
					LPCTSTR lpszCaption, int nWidth = 1, 
					BOOL bStartsRow = FALSE);

	// Initialise button with single character accelerator
	BOOL Initialise(const Attrib& attrib, CGXBCalculator::CGXBCalcOp op, 
					LPCTSTR lpszCaption, TCHAR cAccel, int nWidth = 1, 
					BOOL bStartsRow = FALSE);

	// Initialise button with different accelerators to caption
	BOOL Initialise(const Attrib& attrib, CGXBCalculator::CGXBCalcOp op, 
					LPCTSTR lpszCaption, LPCTSTR lpszAccels, int nWidth = 1, 
					BOOL bStartsRow = FALSE);

// Overrides
public:
	// Draws the button!
	virtual void Draw(CDC& dc);

// Implementation
public:
	virtual ~CGXBCalcBtn();

#ifdef _DEBUG
	virtual void Dump(CDumpContext& dc) const;
	virtual void AssertValid() const;
#endif

// Implementation, data members.
public:
	// enum State values
	enum
	{
		Down      = 0x0001,						// Button is currently down
		StartsRow = 0x0002,						// Button starts a new row
		Hot       = 0x0004						// Button is hot, i.e. under mouse cursor
	};

protected:
	Attrib		             m_attribs;			// Button attributes
	CString                  m_strCaption;		// Button caption
	CString                  m_strAccels;		// Std keyboard accelerators
	UINT		             m_nKeyDownAccel;	// WM_KEYDOWN accelerators
	int                      m_nWidth;			// Width of button
	CRect		             m_rect;			// Rectangle of button (relative
												// to calculators client)
	int                      m_nState;			// State flags (see state bits)
	CGXBCalculator::CGXBCalcOp m_op;				// The operation of this button
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
#endif // _MFC_VER >= 0x0400

#endif //_GXCALC_H_

