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
// Authors: Daniel Jebaraj, Praveen Ramesh
//
// Portions of this code were copied from Objective Toolkit.

// gxcurbas.h : Declarations for the Currency Control
// 
// 
// The source code for this control has been copied
// from Objective Toolkit.
//

#ifndef _GXCURBAS_H_
#define _GXCURBAS_H_

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

/////////////////////////////////////////////////////////////////////////////
// CGXBDropEdit window
//
// Adds a combo like drop down button to an edit control
//

class CGXBDropEdit : public CEdit
{
	DECLARE_DYNAMIC(CGXBDropEdit)

	
// Construction
public:
	CGXBDropEdit();

	BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);

	// Attach to an existing edit control
	BOOL AttachEdit(int nCtlID, CWnd* pParentWnd);

// Attributes
public:
	// Methods for manipulating the alignment mode (within the edit control)
	void SetRightAlign(BOOL bRightAlign = TRUE);
	BOOL IsRightAligned() const;

	// Methods for manipulating the border settings
	void SetBorder(WORD wLeftBorder, WORD wRightBorder);
	DWORD GetBorders() const;

// Operations
public:
	// Methods to set/get the bitmap on the button
	BOOL SetBitmap(UINT nBmpID);
	BOOL SetBitmap(LPCTSTR lpszBmpName);
	BOOL SetBitmap();						// Removes button
	HBITMAP GetBitmap() const;

	// Determintes whether the given point (in screen or client
	// coordinates) is a hit on the button.
	// OG specific made this virtual 4/2/97
	virtual BOOL HitTestBtn(CPoint point, BOOL bClient = FALSE) const;

	// Forces a redraw of the button
	void InvalidateBtn();

// Overrideables
protected:
	// Method called when the button has been clicked
	virtual void OnClicked();

	// Method called to draw the button
	virtual void DrawBtn(CDC& dc, CRect r);

	// Method to handle Mouse Leave messages.
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);

// Implementation
public:
	virtual ~CGXBDropEdit();

#ifdef _DEBUG
	virtual void Dump(CDumpContext& dc) const;
	virtual void AssertValid() const;
#endif

protected:
	// Implementation, data members.
	CRect   m_btnRect;				// The window rect of the button (in our
									// parents client coordinates)
	CBitmap m_bmp;					// Bitmap drawn on face of button
	LPCTSTR m_lpszBmpName;			// Resource ID of above bitmap
	WORD    m_wState;				// Current state (see States below)
	WORD    m_wLeftBorder;			// Left hand Gap between bitmap and border
	WORD    m_wRightBorder;			// Right hand Gap between bitmap and border

	// Bit settings in m_wState
	enum States
	{
		Pressed    = 0x0001,		// Button is currently down	
		Capture    = 0x0002,		// We are tracking a left click on the button		
		RightAlign = 0x0004,		// The button is right aligned within the edit
		Hover      = 0x0008
	};

	// Implementation - message map and entries
	DECLARE_MESSAGE_MAP()

	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnNcMouseMove(UINT nFlags, CPoint point);
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg void OnNcPaint();
	afx_msg void OnCancelMode();
	afx_msg void OnSysColorChange();
	afx_msg void OnEnable(BOOL bEnable);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

/////////////////////////////////////////////////////////////////////////////

// Function to take the given rectange in the given dc and draw it disabled.
void AFXAPI CGXBDrawDisabled(CDC& dc, int x, int y, int nWidth, int nHeight);




class CGXBCurrencyEdit : public CGXBDropEdit //public CWnd
{
	DECLARE_DYNAMIC(CGXBCurrencyEdit)
public:

	// The following nested helper class provides the core currency
	// formatting and parsing methods.

	class Format
	{
	public:
		// Construction/destruction.  Note: if the default initialization
		// does not occur, the object will in a valid but decidedly 
		// American state.

		Format(BOOL bInitializeFromSystemDefaults = TRUE);
		virtual ~Format() {}

		// Property retrieval and setting methods for all the currency
		// display options.  Some important notes: 
		//
		// 1) Setting the thousand separator to the null character ('\0') 
		//    will prevent its use.
		// 2) Setting the decimal digits to negative one (-1) will use 
		//    as many digits are necessary to display the number.  If
		//    the number of digits is larger than required, the output
		//    will be padded with the padding character.
		//
		// Negative Format  Positive Format
		//
		// 0	($1)		0	$1 
		// 1	-$1			1	1$ 
		// 2	$-1			2	$ 1
		// 3	$1-			3	1 $
		// 4	(1$)
		// 5	-1$			These formats are taken directly from
		// 6	1-$			Microsoft's documentation regarding
		// 7	1$-			the international section of WIN.INI.
		// 8	-1 $		The CGXBCurrencyEdit uses them for the
		// 9	-$ 1		positive and negative formats given via
		// 10	$ 1-		the formatting object.

		BOOL IsLeadingZeroEnabled() const
			{ return m_bLeadingZero; }
		void EnableLeadingZero(BOOL b)
			{ m_bLeadingZero = b; }
		BOOL IsDecimalSeparatorLineEnabled() const
			{ return m_bDecimalSeparatorLine; }
		void EnableDecimalSeparatorLine(BOOL b)
			{ m_bDecimalSeparatorLine = b; }
		BOOL IsRotateWhileAtEndEnabled() const
			{ return m_bRotateWhileAtEnd;	}
		void EnableRotateWhileAtEnd(BOOL b)
			{ m_bRotateWhileAtEnd = b;	}
		BOOL IsSeparatorsInLeadingSpaceEnabled() const
			{ return m_bSeparatorsInLeadingSpaces;	}
		void EnableSeparatorsInLeadingSpace(BOOL b)
			{ m_bSeparatorsInLeadingSpaces = b;	}
		LPCTSTR GetMonetarySymbol() const
			{ return m_strMonetarySymbol; }
		void SetMonetarySymbol(LPCTSTR p)
			{ m_strMonetarySymbol = p; }
		LPCTSTR GetGrouping() const
			{ return m_strGrouping; }
		BOOL SetGrouping(LPCTSTR x);
		TCHAR GetThousandSeparator() const
			{ return m_cThousandSeparator; }
		void SetThousandSeparator(TCHAR c)
			{ m_cThousandSeparator = c; }
		TCHAR GetDecimalSeparator() const
			{ return m_cDecimalSeparator; }
		void SetDecimalSeparator(TCHAR c)
			{ m_cDecimalSeparator = c; }
		TCHAR GetPaddingCharacter() const
			{ return m_cPaddingCharacter; }
		BOOL SetPaddingCharacter(TCHAR c);
		BOOL GetBackgroundColor(COLORREF& cr) const;
		void SetBackgroundColor(COLORREF cr);
		BOOL GetNegativeColor(COLORREF& cr) const;
		void SetNegativeColor(COLORREF cr);
		BOOL GetPositiveColor(COLORREF& cr) const;
		void SetPositiveColor(COLORREF cr);
		COLORREF GetDecimalSeparatorLineColor() const
			{ return m_crSeparator; }
		void SetDecimalSeparatorLineColor(COLORREF cr)
			{ m_crSeparator = cr; }
		int GetPositiveFormat() const
			{ return m_iPositiveFormat; }
		void SetPositiveFormat(int i);
		int GetNegativeFormat() const
			{ return m_iNegativeFormat; }	
		void SetNegativeFormat(int i);
		int GetDecimalDigits() const
			{ return m_iDecimalDigits; }
		void SetDecimalDigits(int i)
			{ m_iDecimalDigits = i; }
		int GetFractionalDigits() const
			{ return m_iFractionalDigits; }
		void SetFractionalDigits(int i)
			{ m_iFractionalDigits = i; }

		// Reads values as necessary from registry, INI file, etc. to
		// match settings specified by user in Control Panel.

		void InitializeFromSystemDefaults();

		// The following method clears any previously specified custom 
		// color use.

		void ClearCustomColors()
			{ m_iColorUseFlags = 0; }

		// The following methods convert between a numeric value and a
		// string representation.  If customization beyond that required
		// by the basic Format object is requied, derive your own class
		// and override the following methods; then pass your format
		// object to the SECCurrencyEdit in its constructor.

		virtual BOOL ParseValue(LPCTSTR pcsz, double& d, BOOL& bNegative) const;
		virtual void FormatValue(double dAbs, CString& str, BOOL bIsNegative) const;

		// If, for some pathological reason, the user needs to set the thousands
		// separator equivalent to the decimal separator, then he needs to derive
		// his own class and override these methods. Otherwise, it is not at all
		// likely that parsing will ever work consistently and accurately.

		virtual int FindDecimalSeparator(LPCTSTR pcszString, TCHAR cDecimal = '\0') const;
		virtual int FindFirstAndLastDigits(LPCTSTR pcszString, int& iFirst, int& iLast) const;
		
		// Operators - virtual to allow descendant handling.

		virtual Format& operator=(const Format& rhs);
		virtual BOOL operator==(const Format& rhs) const;
		virtual BOOL operator!=(const Format& rhs) const
			{ return !operator==(rhs); }

	private:
		BOOL m_bLeadingZero;			// leading 0 for numbers -1 < n < 1 ?
		BOOL m_bDecimalSeparatorLine;	// vertical line for decimal point?
		BOOL m_bRotateWhileAtEnd;		// Rotates the decimal part/fraction part while the 
										// the cursor is at the end...FALSE by default
		BOOL m_bSeparatorsInLeadingSpaces;	// will display seperators even on the leading spaces
										// FALSE by default
		CString m_strMonetarySymbol;		// currency symbol (default: $)
		CString m_strGrouping;			// decimal digit grouping sizes
		TCHAR m_cThousandSeparator;		// groups decimal digits (default: ,)
		TCHAR m_cDecimalSeparator;		// decimal point (default: .)
		TCHAR m_cPaddingCharacter;		// used to pad to left of decimal
		COLORREF m_crBackground;		// background color of control window
		COLORREF m_crNegative;			// color of text when value is negative
		COLORREF m_crPositive;			// color of text when value is negative
		COLORREF m_crSeparator;			// color of decimal separator line
		int m_iColorUseFlags;			// internal color flags variable
		int m_iPositiveFormat;			// WIN.INI format for positive values
		int m_iNegativeFormat;			// WIN.INI format for negative values
		int m_iDecimalDigits;			// number of characters left of decimal
		int m_iFractionalDigits;		// number of digits to right of decimal
	};

	// Construction/destruction.

	CGXBCurrencyEdit();
	CGXBCurrencyEdit(Format* pFmt);
	virtual ~CGXBCurrencyEdit();

	// Replaces an existing edit control.

	BOOL Initialize(CWnd* pwndParent, UINT uiControlID);

	// Gets or sets the actual numeric value directly.

	void GetValue(double& d) const;	
	void SetValue(double d, BOOL bRedraw = TRUE);

	// Gets of sets the display formatting data.

	void GetFormat(Format& f);
	void SetFormat(const Format& f);

	// The alignment is actually maintained via edit ES_* style values;
	// these methods are provided largely for convenience.

	enum Align { left = 0, center = 1, right = 2 };
	Align GetAlignment() const;
	void SetAlignment(Align a);

	// The read-only feature is actually mantained via the normal edit
	// control ES_READONLY style; these methods are provided largely
	// for convenience.  The EM_SETREADONLY message will also work.

	BOOL IsReadOnly() const;
	void SetReadOnly(BOOL b);
	
	void SetMargins(UINT nLeft, UINT nRight);
	DWORD GetMargins() const
		{ return MAKELONG(m_uiLeftMargin, m_uiRightMargin); }
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXBCurrencyEdit)
	//}}AFX_VIRTUAL

	BOOL m_bRotateWhileAtEnd;			// Rotates the decimal part/fraction part while the 
										// the cursor is at the end...FALSE by default
	BOOL m_bSeparatorsInLeadingSpaces;	// will display seperators even on the leading spaces
										// FALSE by default

protected:
	virtual BOOL ShowCalculator();
	void NotifyParent(UINT uiCode);

	// Override of the CGXBDropEdit for handling the button click.

	virtual void OnClicked()
		{ ShowCalculator(); }

	// Data structure used for maintaining selection details.
	// Two special settings should be noted: 0, -1 means select 
	// all and -1, 0 means no selection.

	typedef struct tagSelData
	{
		int iStart, iStop;
		tagSelData() : iStart(-1), iStop(0) {}
		tagSelData(const tagSelData& s) :
			iStart(s.iStart), iStop(s.iStop) {}
		void Set(int i, int j) { iStart = i; iStop = j; }
		void Clear() { iStart = -1; iStop = 0; }
		void Normalize()
		{
			int iTmp;
			if (iStart > iStop)
			{
				iTmp = iStop;
				iStop = iStart;
				iStart = iTmp;
			}
		}
		tagSelData& operator=(const tagSelData& rhs)
		{
			if (this != &rhs)
			{
				iStart = rhs.iStart;
				iStop = rhs.iStop;
			}
			return *this;
		}

	} SELDATA;

	// Data structure used for maintaining undo data.

	typedef struct tagUndoData
	{
		CString strText;
		int iCaretPos;
		SELDATA sel;

		tagUndoData() : iCaretPos(-1) {}
		tagUndoData(const tagUndoData& u) : 
			strText(u.strText), iCaretPos(u.iCaretPos), sel(u.sel) {}
		tagUndoData& operator=(const tagUndoData& rhs)
		{
			if (this != &rhs)
			{
				strText = rhs.strText;
				iCaretPos = rhs.iCaretPos;
				sel = rhs.sel;
			}
			return *this;
		}

	} UNDODATA;
	
	BOOL m_bNegative;		// Is the data value negative?
	BOOL m_bCanUndo;		// undo buffer has something?
	BOOL m_bParseOnSetText;	// parse value on WM_SETTEXT?
	BOOL m_bRedraw;			// is redraw allowed?
	BOOL m_bMouseSelect;	// are we mouse selecting?
	BOOL m_bOverstrike;		// is overstrike mode enabled?
	UNDODATA m_Undo;		// undo buffer
	double m_dValue;		// numeric value
	Format* m_pFormat;		// current format settings
	HFONT m_hFont;			// font set via WM_SETFONT
	int m_iCaretPos;		// caret character position
	SELDATA m_Sel;			// selection information
	UINT m_uiRightMargin;	// The right margin in pixels.
	UINT m_uiLeftMargin;	// The left margin in pixels.


	// Descendant classes may override the following members to provide
	// a right-button popup menu, background drawing, save their own 
	// data for an undo operation, etc.

	virtual BOOL PrepareTextForPaste(CString& strText);	
	virtual CMenu* CreatePopupMenu() const;
	virtual void DeletePopupMenu(CMenu* p) const;
	virtual void DoBackspace();
	virtual void DoDelete();
	virtual void DoInsert(LPCTSTR pcsz);
	virtual void EraseBackground(CDC* pDC);
	virtual void SaveDataForUndo(LPCTSTR p = NULL, int iCaret = -1);
	virtual void StartEdit(int iCaretPos);
	virtual void StopEdit();
	virtual void DrawDecimalSeparatorLine(CDC& DC, int x);
	virtual void HandleNegativeSignKey();
	virtual void ToggleOverstrikeMode();


	// Non-virtual members; descendant classes may utilize these, but should 
	// not override them.

	BOOL IsNegative() const
		{ return m_bNegative; }
	BOOL HasSel() const
		{ return m_Sel.iStart != -1 && m_Sel.iStop != m_Sel.iStart; }
	BOOL SetSel(int iStart, int iStop);
		BOOL SetSelNone()
		{ return SetSel(-1, 0); }
	BOOL SetSelAll()
		{ return SetSel(0, -1); }
	BOOL IsMouseSelecting() const
		{ return m_bMouseSelect; }
	BOOL IsEntireNumberSelected(BOOL* pbMore = NULL) const;
	BOOL IsOverstrikeEnabled() const
		{ return m_bOverstrike; }	
	COLORREF GetBackgroundColor() const;
	COLORREF GetTextColor() const;
	int PointToCaretPos(const CPoint& pt);
	void CalculateTextRect(CRect& rc);
	void DoInsert(TCHAR c)
		{ DoInsert(CString(c)); }
	void GetSelectedText(CString& s) const;
	void MoveCaret(int iChar, BOOL bUpdateSel = FALSE);
	void PaintingCore(CDC& DC);
	void QueueRedraw(BOOL bEraseBackground = TRUE)
		{ if (m_bRedraw) InvalidateRect(NULL, bEraseBackground); }
	void ReplaceSelString(LPCTSTR pcszNew, CString& str) const;
	void SetWindowTextNoParse(LPCTSTR p);
	void MoveCaretToNumber();
	void SetValue(double d, BOOL bNegative, BOOL bRedraw);

	// Handlers provided by ClassWizard.

	//{{AFX_MSG(CGXBCurrencyEdit)
	afx_msg void OnPaint();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG

	// Edit control message handlers not provided by ClassWizard.

	afx_msg LRESULT OnCanUndo(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnEmptyUndoBuffer(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGetSel(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetReadOnly(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetSel(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetMargins(WPARAM wParam, LPARAM lParam);

	// Standard message handlers not provided by ClassWizard.

	afx_msg LRESULT OnGetFont(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnCopy(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnCut(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnPaste(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetFont(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetRedraw(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSetText(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUndo(WPARAM wParam, LPARAM lParam);

	// Command handlers for right mouse button popup menu.

	afx_msg void OnEditUndo();
	afx_msg void OnEditCopy();
	afx_msg void OnEditCut();
	afx_msg void OnEditPaste();
	afx_msg void OnEditClear();
	afx_msg void OnEditSelectAll();

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
#endif // _MFC_VER >= 0x0400

#endif //_GXCURBAS_H_
