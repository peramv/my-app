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

// gxctrl.h : header file
//
#ifndef _GXCTRL_H
#define _GXCTRL_H

#ifndef _GXRESRC_H_
#include "grid\gxresrc.h"
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


#undef GX_DATA
#undef GX_DATADEF

#if _MFC_VER < 0x0300
#define GX_DATA
#define GX_DATADEF
#else
#define GX_DATA AFX_DATA
#define GX_DATADEF AFX_DATADEF
#endif


// header file

class CGXGridCore;
class CGXStyle;
struct GX_FR_STATE;
class CGXChild;
class CGXControl;
class CGXGridCombo;
class CGXCellTipWnd;

enum GXModifyType;


// The following functions have been renamed from earlier version
// #define GetFormattedText    GetControlText
#define OnInitChilds        OnInitChildren

/////////////////////////////////////////////////////////////////////////////
// Runtime Type Information for the CGXControl class

struct CGXControlClass
{
// Attributes
	LPCSTR m_lpszClassName;
#ifdef _GXDLL
	CGXControlClass* (PASCAL* m_pfnGetBaseClass)();
#else
	CGXControlClass* m_pBaseClass;
#endif
};

// Helper macros

#define CONTROL_CLASS(class_name) (&class_name::ctrl##class_name)

#ifdef _GXDLL

#define DECLARE_CONTROL(class_name) \
protected: \
	static CGXControlClass* PASCAL _GetControlBaseClass(); \
public: \
	static GX_DATA CGXControlClass ctrl##class_name; \
	virtual CGXControlClass* GetControlClass() const; \

#define IMPLEMENT_CONTROL(class_name, base_class_name) \
	CGXControlClass* PASCAL class_name::_GetControlBaseClass() \
		{ return CONTROL_CLASS(base_class_name); } \
	GX_DATADEF CGXControlClass class_name::ctrl##class_name = { \
		#class_name, &class_name::_GetControlBaseClass }; \
	CGXControlClass* class_name::GetControlClass() const \
		{ return &class_name::ctrl##class_name; } \

#else

#define DECLARE_CONTROL(class_name) \
public: \
	static CGXControlClass GXNEAR ctrl##class_name; \
	virtual CGXControlClass* GetControlClass() const; \

#define IMPLEMENT_CONTROL(class_name, base_class_name) \
	CGXControlClass GXNEAR class_name::ctrl##class_name = { \
		#class_name, CONTROL_CLASS(base_class_name) }; \
	CGXControlClass* class_name::GetControlClass() const \
		{ return &class_name::ctrl##class_name; } \

#endif

/////////////////////////////////////////////////////////////////////////////
// Global methods

BOOL AFXAPI GXGetDoubleByteChar(TCHAR nChar, CString& sChar, BOOL& bDoubleByteChar, TCHAR& nDoubleByteLeadChar);

////////////////////////////////////////////////////////////////////////////
// CellTips implementation
class CGXCellTipWnd;

struct CGXCellTipBase
{
	CGXCellTipBase();
	
	virtual ~CGXCellTipBase();
	
	virtual BOOL NeedShowCellTip(ROWCOL nRow, ROWCOL nCol, CGXStyle* pStyle) = 0;

	virtual DWORD GetCellTipID(ROWCOL nRow, ROWCOL nCol, CGXStyle* pStyle) = 0;

	virtual void InitializeCellTip(ROWCOL nRow, ROWCOL nCol, CGXStyle* pStyle, CGXCellTipWnd* pCellTip) = 0;
};



/////////////////////////////////////////////////////////////////////////////
// Control base classes

class CGXControl
{
public:
	// a control allows you to have several childs (e.g. button, spin-arrows, ...)
	// LButtonDown, MouseMove, LButtonUp and Keypressed are automatically
	// redirected to the focused child.
	//
	// You should initialize the rectangles of the child by
	// overriding OnInitChildren

	// Constructor & Destructor
	CGXControl(CGXGridCore* pGrid);
	virtual ~CGXControl();
	static void AFXAPI AddUserAttributes(CGXStylesMap* stylesMap);

	// Run-Time Type Information
	// Object model (types, destruction, allocation)
	virtual CGXControlClass* GetControlClass() const;
	BOOL IsKindOf(const CGXControlClass* pClass) const;
	virtual CRuntimeClass* GetRuntimeClass() const;
	BOOL IsKindOf(const CRuntimeClass* pClass) const;

	operator CWnd*();
	virtual CWnd* GetWndPtr() const;

	// Status (need to be overriden)
	virtual void SetActive(BOOL bActive);
	virtual BOOL IsActive();    // default: FALSE
	virtual BOOL IsActiveAlways();	// default: FALSE

	virtual void SetModify(BOOL bModified);
	virtual BOOL GetModify();   // default: FALSE

	// Operations
	virtual void Init(ROWCOL nRow, ROWCOL nCol);
		// Retrieves the style and initializes the CWnd
		// Called, when current cell is moved to cell (nRow, nCol)

	virtual void Reset();
		// Hides the window, sets inactive and sets m_nRow, m_nCol to zero
		// Called, when current cell is moved to another cell, or
		// if control needs to be reinitialized

	BOOL IsInit() const;
	BOOL IsInit(ROWCOL nRow, ROWCOL nCol) const;
		// TRUE, if control is used as current cell
		//       (CGXControl::Init has been called and intrinsic state is initialized);
		// FALSE, if control is not used as current cell

	virtual BOOL Store();
		// Calls SetStyleRange() and resets the modify flag
		// Cell will be automatically redrawn

	virtual BOOL OnValidate();
		// Validates the active cell, default: FALSE

	virtual BOOL OnStartEditing();
		// called when the user starts editing (pressed key or mouse into text)

	virtual void OnModifyCell();
		// called when the user started modifying the text

	virtual BOOL OnCancelEditing();
		// called when the user pressed ESCAPE

	virtual void OnCanceledEditing();
		// called when the user pressed ESCAPE and the control has been reset

	virtual BOOL OnEndEditing();
		// called when the user accepted the contents

	virtual BOOL OnLeftCell(ROWCOL nNewRow, ROWCOL nNewCol);
		// called from SetCurrentCell when the cell has been
		// marked invalid and Grid()->IsCurrentCell(nRow, nCol)
		// returns FALSE. Return TRUE if the cell needs to
		// be redrawn.

	virtual BOOL OnDeleteCell();
		// called when the user pressed DELETE on an inactive current cell

	virtual CRect GetCellRect(ROWCOL nRow, ROWCOL nCol, LPRECT rectItem = NULL, const CGXStyle* pStyle = NULL);
		// Returns the rectangle, e.g. the rect for the text to be drawn without buttons
		// default: rect = Grid()->CalcRectFromRowColEx(nRow, nCol)
		//          Grid()->SubsctractBorders();

	virtual CSize AddBorders(CSize size, const CGXStyle& style);
		// Will be called from CalcSize to add borders and grid lines to col width / row height

	virtual CSize CalcSize(CDC* pDC, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle, BOOL bVert);
		// Computes the size needed to fit the cell's content in a cell.

	virtual BOOL CanFloatCell(ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, BOOL bFloatOrFlood);
		// Return TRUE if cell can float other cells or can be flooded by other floatable cells

	virtual BOOL CanMergeCell(ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, int mtType);
		// Return TRUE if cell can be merged with other cells

	virtual void InvertBorders(CDC* pDC, const CRect& r);
		// Inverts the borders for the current cell;
		// Override this methode if you don't want to have inverted borders,
		// or if you want to have thicker borders

	virtual void Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle);
		// Notes on Draw:
		// if (nRow == m_nRow && nCol == m_nCol && m_bHasFocus)
		//     initialize CWnd, make it visible and set focus
		// else {
		//     lookup style and draw static, e.g.:
		//     - edit control with GXDrawTextLikeMultiLineEdit
		//     - check box with GXDrawCheckBox
		//     - list box: DrawText for each item
		// }

	// current cell specific->
	virtual void GetCurrentText(CString& strResult);
		// override this method to return the text which
		// is displayed in the current cell

	virtual void SetCurrentText(const CString& str);
		// override this method to set the text as it should
		// be displayed in the current cell

	virtual BOOL GetValue(CString& strResult);
		// Reads out the window text and converts it into
		// the plain value which should be stored in the style object.

	virtual void SetValue(LPCTSTR pszRawValue);
		// Convert the value which should be stored in the
		// style object to the text which should be displayed
		// in the cell and display it in the active
		// current cell (e.g. with SetWindowText()).

		// This function is protected so that you are
		// forced to call SetValueRange instead of SetValue
		// directly from outside the control.
	// ->end

public:
	virtual BOOL GetControlText(CString& strResult, ROWCOL nRow, ROWCOL nCol, LPCTSTR pszRawValue, const CGXStyle& style);
		// get the text which is displayed in the cell.
		// RTF specific-> Convert RTF string to unformated text ->END
		// ME specific-> Insert literals ->END
		// Combobox specific-> Convert index to display string ->END

	virtual BOOL SetControlText(ROWCOL nRow, ROWCOL nCol, const CString& str, UINT nFlags = GX_UPDATENOW, const CGXStyle* pOldStyle = NULL);
		// set the text as it should be displayed in the cell.
		// RTF specific-> Convert unformated text to RTF string ->END
		// ME specific-> Adjust text to given mask and remove literals->END
		// Combobox specific-> Convert display string to index ->END
		// The default implementation checks for readonly and
		// maximum text length.


	virtual BOOL ConvertControlTextToValue(CString& str, ROWCOL nRow, ROWCOL nCol, const CGXStyle* pOldStyle);
		// called from SetControlText to get the value before it is stored in
		// the cell.

	virtual BOOL StoreStyle(ROWCOL nRow, ROWCOL nCol, const CGXStyle* pStyle, GXModifyType mt, int nType, const CGXStyle* pOldStyle);
		// CGXControl::StoreStyle will call CGXGridCore::StoreStyleRowCol
		// and check if cell is read-only.
		//
		// In OG 1.1, CGXGridCore::StoreStyleRowCol was directly called. This has
		// changed in version 1.2, in order to make the behavior more cell-oriented
		// and allow specific controls to modify the style object before it is stored
		// in the datastructure. The new RTF control will use the passed style object
		// and change the value depending on the new formattings. If the style object
		// is for example "Bold" and StoreStyle is called for an active RTF
		// control, the RTF control will make the paragraph bold (by changing
		// the cell's value which contains rich text formattings).
		//
		// NOTE: The check whether a cell is read-only has been moved from
		// CGXGridCore::StoreStyleRowCol to CGXControl::StoreStyle
		//

	virtual BOOL LoadStyle(ROWCOL nRow, ROWCOL nCol, CGXStyle* pStyle);
		// Determines the cell-specifc style information for the
		// specified cell. RTF handles font, textcolor and text
		// alignment in the RTF value. Therefore, LoadStyle will
		// extract this information from the RTF value and set
		// this attributes in the style object.

	virtual BOOL GetChoiceListItem(CString& strResult, LPCTSTR pszChoiceList, int nIndex);
		// determines choice list entry for a given index

	virtual int FindStringInChoiceList(CString& sMatch, LPCTSTR pszEdit, LPCTSTR pszChoiceList, BOOL bExact);
		// searches the choice list for a given string and returns the index

	virtual void Hide();
		// Hides the CWnd without changing the m_bIsActive flag

	virtual void Refresh();
		// Hides the CWnd and Redraws the cell

	// Mouse hit
	virtual BOOL MouseMove(UINT nFlags, CPoint pt, UINT nHitState);
		// default: Calls child with focus

	virtual BOOL MouseMoveOver(ROWCOL nRow, ROWCOL nCol, UINT flags, CPoint pt);

	// Left Button
	virtual BOOL LButtonDown(UINT nFlags, CPoint pt, UINT nHitState);
		// default: Sets focus to hit child control (see CGXControl)
	virtual BOOL LButtonUp(UINT nFlags, CPoint pt, UINT nHitState);
		// default: Calls child with focus
	virtual BOOL LButtonDblClk(UINT nFlags, CPoint point);
		// default: Sets focus to hit child control (see CGXControl)

	// Middle Button
	virtual BOOL MButtonDown(UINT nFlags, CPoint pt, UINT nHitState);
		// default: Sets focus to hit child control (see CGXControl)
	virtual BOOL MButtonUp(UINT nFlags, CPoint pt, UINT nHitState);
		// default: Calls child with focus
	virtual BOOL MButtonDblClk(UINT nFlags, CPoint point);
		// default: Sets focus to hit child control (see CGXControl)

	// Right Button
	virtual BOOL RButtonDown(UINT nFlags, CPoint pt, UINT nHitState);
		// default: Sets focus to hit child control (see CGXControl)
	virtual BOOL RButtonUp(UINT nFlags, CPoint pt, UINT nHitState);
		// default: Calls child with focus
	virtual BOOL RButtonDblClk(UINT nFlags, CPoint point);
		// default: Sets focus to hit child control (see CGXControl)

	// WM_MOUSEACTIVATE message
	virtual BOOL MouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message, int& retval);

	// PreTranslateMessage
	virtual BOOL OnGridPreTranslateMessage(MSG* pMsg);

	// Keyboard
	virtual BOOL KeyPressed(UINT nMessage, UINT nChar, UINT nRepCnt = 1, UINT flags = 0);
		// default: Calls child with focus

	virtual BOOL OnGridKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL OnGridKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL OnGridChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL OnGridDoubleByteChar(const CString& sChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL OnGridDeadChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL OnGridSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL OnGridSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL OnGridSysChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL OnGridSysDeadChar(UINT nChar, UINT nRepCnt, UINT nFlags);

	// Clipboard
	virtual BOOL Copy();
	virtual BOOL Paste();
	virtual BOOL Cut();
	virtual BOOL CanCopy();
	virtual BOOL CanCut();
	virtual BOOL CanPaste();

	// Sort Key
	virtual void GetSortKey(ROWCOL nRow, ROWCOL nCol, const CGXSortInfo& sortInfo, const CGXStyle& style, CString& sKey);

	// Find and Replace
	virtual BOOL FindText(const GX_FR_STATE& find, ROWCOL nRow, ROWCOL nCol, BOOL bCurrentPos, BOOL bSetCell = FALSE);
		// default: returns FALSE
		// override this method to support find

	virtual void ReplaceSel(LPCTSTR pszReplaceText);
		// override this method to support replace

	virtual BOOL ReplaceAll(const GX_FR_STATE& find, ROWCOL nRow, ROWCOL nCol);
		// override this method to support replace

	virtual BOOL GetSelectedText(CString& strResult);
		// override this method to return the selected text

	// Support for several child buttons (HotSpot, Combobox, Spinnbuttons)
	virtual void OnClickedButton(CGXChild* pChild);
		// pChild points to the callee (see CGXSpinEdit for an example)

	CGXGridCore* Grid();
		// Pointer to Grid

	CWnd* GridWnd();
		// Pointer to GridWnd

	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
		// Called from CGXGridCore::OnCommand for
		// ON_COMMAND messages (e.g. ON_CBN_SELCHANGE)

	virtual void OnNotifyMsg(MSG* pMsg);
		// Called from CGXGridCore::OnVScroll, OnHScroll

	virtual HBRUSH OnGridCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
		// Called from CGXGridCore::DoCtlColor

	virtual void OnGridWinIniChange(LPCTSTR lpszSection);
		// Called from CGXGridCore::OnGridWinIniChange

	virtual void OnGridSysColorChange();

	virtual BOOL IsReadOnly();

	virtual void OnGridCancelMode();

	// for the celltips
	virtual BOOL NeedShowCellTip(ROWCOL nRow, ROWCOL nCol, CGXStyle* pStyle);
	
	// return the ID that identifies the CGXCellTipWnd derivative that will be used
	virtual DWORD GetCellTipID(ROWCOL nRow, ROWCOL nCol, CGXStyle* pStyle);
	
	// Lets the control initialize the celltip
	virtual void InitializeCellTip(ROWCOL nRow, ROWCOL nCol, CGXStyle* pStyle, CGXCellTipWnd* pCellTip);

	// Windowless means just that, the control does not have a windows window associated with it
	virtual BOOL IsWindowlessControl();

protected:
	CFont* LoadFont(CDC* pDC, const CGXStyle& style, const CGXStyle* pStandardStyle);
		// compares the font with the standard font
		// if different, the method selects the font into the device context

	void FreeStyle(BOOL bGrid = TRUE);
		// deletes the style

	CGXStyle* NeedStyle();
		// loads the style

	virtual void AddChild(CGXChild*);
		// adds a child

	virtual void RemoveChild(CGXChild*);
		// removes a child

	virtual CGXChild* GetChild(int);
		// returns a child

	virtual int GetCount();
		// No. of childs

	virtual CGXChild* ChildWithFocus();
		// returns pointer to active child

	virtual void FocusOnChild(CGXChild* child);
		// sets active child to retrieve mouse and keys messages

	virtual void OnInitChildren(ROWCOL nRow, ROWCOL nCol, const CRect& rect);
		// override this methode to initialize the rectangle of the children

	void OnKillFocus(CWnd* pNewWnd);
		// call this method from your OnKillFocus message handler.
		// it will deactivate the grid, if necessary

	void ExcludeClipRect(const CRect& rect);
		// call this method to protect your controls to be overdrawn

	virtual void DrawBackground(CDC* pDC, const CRect& rect, const CGXStyle& style, BOOL bErase = FALSE);
	virtual void DrawFrame(CDC* pDC, const CRect& rect, const CGXStyle& style);

	virtual BOOL ValidateString(const CString& sEdit);
		// Called after the user pressed a key and before it is accepted.
		// Will also be called from SetCurrentText before the text is
		// displayed in the cell.

	virtual BOOL ValidatePaste(const CString& sPaste);
		// called when the user pastes text (when the cell is active)
		// Default implementation returns TRUE. If you implement this
		// build the complete string and call ValidateString (or) validate
		// the pasted text in this override itself. Refer to CGXEditControl
		// for a sample impl. This will be called from CGXControl::Paste which
		// will call ReplaceSel based on the return value from this call.

	virtual void OnInvalidKeyPressed(LPCTSTR pszChar);
		// called when the user pressed an invalid key which
		// could not be accepted.

	virtual BOOL GetMarkHeaderState(ROWCOL nRow, ROWCOL nCol, const CGXStyle& style);

	// Attributes:
public:
	BOOL            m_bRefreshOnSetCurrentCell;
					// If you have a control which appearence is
					// depending on whether it is a current cell
					// or not, you should set m_bRefreshOnSetCurrentCell
					// = TRUE.

private:
	CGXGridCore*    m_pGrid;        // Pointer to grid

protected:
	ROWCOL          m_nRow,         // Row for current cell
					m_nCol;         // Column for current cell
	CGXStyle*       m_pStyle;       // Style for current cell
	BOOL            m_bInit;

	// childs
	CPtrList*   m_pChildList;
	CGXChild*   m_pChildFocus;

	// support for IME/DBCS
	BOOL    m_bDoubleByteChar;
	TCHAR   m_nDoubleByteLeadChar;

	// celltips
	CGXCellTipBase* m_pCellTipImpl;

// Implementation
public:
#ifndef _GXDLL
	static CGXControlClass GXNEAR ctrlCGXControl;
#else
	static GX_DATA CGXControlClass ctrlCGXControl;
	static CGXControlClass* PASCAL _GetControlBaseClass();
#endif

	friend class CGXChild;
	friend class CGXCalcSizeImp;
	friend class CGXDrawingAndFormatting;
};

/////////////////////////////////////////////////////////////////////////////
// Child classes which can be used by the composite class

class CGXChild
{
public:
	// construction, destrcution
	CGXChild(CGXControl* pComposite);
	virtual ~CGXChild();

	// Member functions
	virtual void SetRect(const CRect& r);
	virtual CRect GetRect();
	virtual BOOL Intersects(CPoint pt);

	// Focus
	virtual BOOL HasFocus();

	// Text
	virtual void SetText(LPCTSTR s);
	virtual CString GetText();

	// Drawing
	virtual void Draw(CDC* pDC, BOOL bActive) = 0;
	virtual void Draw(CDC* pDC, BOOL bActive, const CGXStyle& style);
	virtual void Refresh();

	// Mouse hit
	virtual BOOL MouseMove(UINT nFlags, CPoint pt);

	// Left Button
	virtual BOOL LButtonDown(UINT nFlags, CPoint pt);
	virtual BOOL LButtonUp(UINT nFlags, CPoint pt);
	virtual BOOL LButtonDblClk(UINT nFlags, CPoint point);

	// Middle Button
	virtual BOOL MButtonDown(UINT nFlags, CPoint pt);
	virtual BOOL MButtonUp(UINT nFlags, CPoint pt);
	virtual BOOL MButtonDblClk(UINT nFlags, CPoint point);

	// Right Button
	virtual BOOL RButtonDown(UINT nFlags, CPoint pt);
	virtual BOOL RButtonUp(UINT nFlags, CPoint pt);
	virtual BOOL RButtonDblClk(UINT nFlags, CPoint point);

	virtual BOOL MouseMoveOver(ROWCOL nRow, ROWCOL nCol, UINT flags, CPoint pt);

	// Keyboard
	virtual BOOL KeyPressed(UINT nMessage, UINT nChar, UINT nRepCnt = 1, UINT flags = 0);

	virtual BOOL OnGridKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL OnGridKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL OnGridChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL OnGridDoubleByteChar(const CString& sChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL OnGridDeadChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL OnGridSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL OnGridSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL OnGridSysChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL OnGridSysDeadChar(UINT nChar, UINT nRepCnt, UINT nFlags);

	// system settings
	virtual void OnGridWinIniChange(LPCTSTR lpszSection);
		// Called from CGXGridCore::OnGridWinIniChange

	virtual void OnGridSysColorChange();

	virtual void OnGridCancelMode();

	CGXGridCore* Grid() { return m_pComposite->Grid(); }
		// Pointer to Grid

	CWnd* GridWnd() { return m_pComposite->GridWnd(); }
		// Pointer to GridWnd

protected:
	CGXControl* m_pComposite;
	CRect           m_rect;
	CString         m_sText;

	// support for IME/DBCS
	BOOL    m_bDoubleByteChar;
	TCHAR   m_nDoubleByteLeadChar;
};


// CGXGridCombo window (will be created with WS_POPUP style)
//

class CGXGridCombo : public CWnd
{
// Construction
public:
	CGXGridCombo(CWnd* pGridWnd, CWnd* pWnd, const CRect& rect);

// Operations
	void SetColor(COLORREF rgbText, COLORREF rgbBack);
	CListBox& GetLBox();

	static void AFXAPI RegisterClass();
	static void AFXAPI UnregisterClass();
	static BOOL AFXAPI GetComboBoxDropDown();
	static void AFXAPI SetComboBoxDropDown(BOOL b = TRUE);
	static CString AFXAPI GetClassName();

// Implementation
	virtual ~CGXGridCombo();
	void AttachListBox(CWnd* pListBox);

// Attributes
protected:
	CWnd*       m_pListBox;
	CWnd*       m_pGridWnd;

	BOOL        m_bColor;

	CBrush      br;
	COLORREF    m_rgbText,
				m_rgbBack;

protected:
	// overridables
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

	// Generated message map functions
	//{{AFX_MSG(CGXGridCombo)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
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

#endif // _GXCTRL_H
