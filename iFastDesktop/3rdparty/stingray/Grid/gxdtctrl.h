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
// Authors: Daniel Jebaraj, Stefan Hoenig
//
// Portions of this code were copied from Objective Toolkit.

// gxdtctrl.h : Declarations for the Calendar Control
// 

#ifndef _GXDTCTRL_H_
#define _GXDTCTRL_H_

#if _MFC_VER >= 0x0400   // only supported for MFC version 4.0 or greater

#ifndef _GXDTCAL_H_
#include "grid\gxdtcal.h"
#endif

#ifndef _GXCTRLI_H_
#include "grid\gxctrli.h"
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

// Control format type as used by GX_IDS_UA_DATEFORMATTYPE

#define GX_DTFORMAT_TIME		_T("0")	// Locale time format
#define GX_DTFORMAT_SHORTDATE	_T("1")	// Locale short date format 
#define GX_DTFORMAT_LONGDATE	_T("2")	// Locale long date format
#define GX_DTFORMAT_CUSTOM		_T("3")	// A user supplied date/time format string 
#define GX_DTFORMAT_DATETIME	_T("4")	// Locale short date+Locale time format string 

// The validation types as used by GX_IDS_UA_DATEVALIDMODE
#define GX_DTVALIDMODE_NONE		_T("0")	// No validation is required
#define GX_DTVALIDMODE_TIME		_T("1")	// Validation of time fields only
#define GX_DTVALIDMODE_DATE		_T("2")	// Validation of date fields only
#define GX_DTVALIDMODE_DATETIME	_T("3")	// Validation of date & time fields

/////////////////////////////////////////////////////////////////////////////
// CGXDateTimeCtrl window
class CGXCaptiveDateTimeCtrl: public CGXBDateTimeCtrl
{
	
protected:
	void SetValue(LPCTSTR pszRawValue);
	void LayoutGadgets(CDC* pDC, CRect rect);
	void LayoutGadgets();

	// value of UA that specifies whether string input is viewed as number
	BOOL m_bForceStrValueAsNumber;

	friend class CGXDateTimeCtrl;
};


class CGXDTGadget: public CGXBDTGadget
{
	friend class CGXDateTimeCtrl;
};

class CGXDTNumericGadget: public CGXBDTNumericGadget
{
	friend class CGXDateTimeCtrl;
};

class CGXDTListGadget: public CGXBDTListGadget
{
	friend class CGXDateTimeCtrl;
};

class CGXDTStaticGadget: public CGXBDTStaticGadget
{
	friend class CGXDateTimeCtrl;
};

class CGXDTSpinGadget: public CGXBDTSpinGadget
{
	friend class CGXDateTimeCtrl;
};

class CGXDTButtonGadget: public CGXBDTButtonGadget
{
	friend class CGXDateTimeCtrl;
};


class CGXDateTimeCtrl : public CGXBDateTimeCtrl, public CGXStatic
{
	DECLARE_CONTROL(CGXDateTimeCtrl)
	DECLARE_DYNAMIC(CGXDateTimeCtrl)

// Construction
public:
	CGXDateTimeCtrl(CGXGridCore* pGrid, UINT nId);

protected:
	BOOL m_bDateValueAsNumber;

	// value of UA that specifies whether string input is viewed as number
	BOOL m_bForceStrValueAsNumber;

	// Precision for time
	int m_nPrecision;

public:
	//Attributes
	virtual CWnd* GetWndPtr() const;
	static void AFXAPI AddUserAttributes(CGXStylesMap* pStylesMap);

	//specifies if the spin button should be drawn in the
	//inactive state
	BOOL m_bInactiveDrawSpin;

	//specifies if the button should be drawn in the inactive state
	BOOL m_bInactiveDrawButton;

	//specifies if an empty cell should be initialized with current date
	//and time for Custom format. If FALSE, cell will be initialized with
	//PSEUDO_NULL (31.12.1899)
	BOOL m_bInitCustomCurrent;

	//specifies if tab should be processed by the control
	BOOL m_bProcessTab;
	//functions
	BOOL CreateControl(DWORD dwStyle, LPRECT lpRect);


	// CGXControl overrides that provide the grid adapter

	// CGXControl overrides - for Current Cell only
	// state
	virtual void Init(ROWCOL nRow,ROWCOL nCol);
	virtual void Hide();
	virtual void SetActive(BOOL bActive);
	virtual BOOL IsActive();
	virtual void SetModify(BOOL bModified);
	virtual BOOL GetModify();
	virtual void SetDateValueAsNumber(BOOL bDateValueAsNumber);
	virtual BOOL IsDateValueAsNumber();

	// value
	virtual BOOL OnValidate();
	virtual BOOL ValidateString(const CString& sEdit);
	virtual void SetCurrentText(const CString& str);
	virtual void GetCurrentText(CString& sMaskedResult);
	virtual BOOL GetValue(CString& strResult);
	virtual void SetValue(LPCTSTR pszRawValue);
	virtual BOOL Store();

	// events
	virtual BOOL LButtonUp(UINT nFlags, CPoint pt, UINT nHitState);
	virtual BOOL LButtonDblClk(UINT nFlags, CPoint pt);
	virtual BOOL OnStartEditing();
	virtual BOOL OnGridKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL OnGridChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL OnGridSysKeyDown(UINT nChar, UINT nRepCnt, UINT flags);
	virtual BOOL OnGridDoubleByteChar(const CString& sChar, UINT nRepCnt, UINT nFlags);
	virtual void ReplaceSel(LPCTSTR pszReplaceText);
	virtual BOOL GetSelectedText(CString& sWindowText);

	// copy paste
	virtual BOOL CanCopy();
	virtual BOOL Copy();
	virtual BOOL CanCut();
	virtual BOOL Cut();
	virtual BOOL CanPaste();
	virtual BOOL Paste();

	// CGXControl overrides - for any cell
	// drawing
	virtual void Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle);
	virtual CRect GetCellRect(ROWCOL nRow, ROWCOL nCol, LPRECT rectItem = NULL, const CGXStyle* pStyle = NULL);
	virtual CSize AddBorders(CSize size, const CGXStyle& style);  // counterpart to GetCellRect
	virtual CSize CalcSize(CDC* pDC, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle, BOOL bVert);
	virtual BOOL CanFloatCell(ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, BOOL bFloatOrFlood);

	// value
	virtual BOOL StoreStyle(ROWCOL nRow, ROWCOL nCol, const CGXStyle* pStyle, GXModifyType mt, int nType, const CGXStyle* pOldStyle);
	virtual BOOL GetControlText(CString& strDisplay, ROWCOL nRow, ROWCOL nCol, LPCTSTR pszRawValue, const CGXStyle& style);
	virtual BOOL ConvertControlTextToValue(CString& str, ROWCOL nRow, ROWCOL nCol, const CGXStyle* pOldStyle);
	virtual BOOL FindText(const GX_FR_STATE& find, ROWCOL nRow, ROWCOL nCol, BOOL bCurrentPos, BOOL bSetCell);
	virtual BOOL ReplaceAll(const GX_FR_STATE& find, ROWCOL nRow, ROWCOL nCol);

	// sorting
	virtual void GetSortKey(ROWCOL nRow, ROWCOL nCol, const CGXSortInfo& sortInfo, const CGXStyle& style, CString& sKey);

	// CGXBDateTimeCtrl overrides
	virtual void PositionGadget(UINT nFlags, CPoint point,  BOOL bIgnoreNullValue = FALSE);
	virtual BOOL OnChanging(const COleDateTime& /* newDateTime */);
	virtual void OnChanged();

	// Helpers for static rendering of the gadgets
	virtual void DrawSpinGadget(CDC* pDC, CGXDTSpinGadget* pGadget, CRect rectClip);
	virtual void DrawNumericGadget(CDC* pDC, CGXDTNumericGadget* pGadget, CRect rectClip);
	virtual void DrawListGadget(CDC* pDC, CGXDTListGadget* pGadget, CRect rectClip);
	virtual void DrawStaticGadget(CDC* pDC, CGXDTStaticGadget* pGadget, CRect rectClip);
	virtual void DrawButtonGadget(CDC* pDC, CGXDTButtonGadget* pGadget, CRect rectClip);
	virtual BOOL SetFormat(CGXBDateTimeCtrl& control, const CGXStyle& style);

	// other helpers
	virtual BOOL ParseTextWithCurrentFormat(const CString& psz, const CGXStyle* pOldStyle, CStringArray& strArray );
	
protected:
	//attributes
	BOOL m_bActive;

	//the control id
	UINT m_nID;

	//for validation
	COleDateTime m_valdt;

	//for the modified flag
	BOOL m_bModify;

	//for Find/Replace support
	ROWCOL m_LastFRow, m_LastFCol;

	CString m_strlfText;

	int m_nLastGadget;

	BOOL m_bFound;

	//String containing delimiters
	CString m_strDelim;

	//used for formatting in control text
	CGXCaptiveDateTimeCtrl m_TextCtrlWnd;
	CGXCaptiveDateTimeCtrl m_DrawCtrlWnd;

	//for the drawing
	CFont m_font;

	friend class CGXBDTSpinGadget;

public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXDateTimeCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGXDateTimeCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXDateTimeCtrl)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT flags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT flags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
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
#endif // _MFC_VER >= 0x0400

#endif // _GXDTCTRL_H_

