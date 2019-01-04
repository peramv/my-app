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

// gxcurctl.h : Currency Control
// 

#ifndef _GXCURCTL_H_
#define _GXCURCTL_H_

#if _MFC_VER >= 0x0400   // only supported for MFC version 4.0 or greater

//
// GridMFC Extension DLL
// initialize declaration context
//

// header file

#ifndef _GXCURBAS_H_
#include "grid\gxcurbas.h"
#endif

#ifndef _GXCTRLI_H_
#include "grid\gxctrli.h"
#endif

#ifdef _GXDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    GX_DATAEXT
#endif

class CGXCaptiveCurEdit: public CGXBCurrencyEdit
{
	friend class CGXCurrencyEdit;
};

/////////////////////////////////////////////////////////////////////////////
// CGXCurrencyEdit control

class CGXCurrencyEdit : public CGXBCurrencyEdit, public CGXStatic
{
	DECLARE_CONTROL(CGXCurrencyEdit)
	DECLARE_DYNAMIC(CGXCurrencyEdit)

// Construction
public:
	// Constructor & Destructor
	CGXCurrencyEdit(CGXGridCore* pGrid, UINT nID);
	virtual ~CGXCurrencyEdit();

	static void AFXAPI AddUserAttributes(CGXStylesMap* pStylesMap);

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
		// Hides the CGXBCurrencyEdit without changing the m_bIsActive flag

	virtual BOOL GetValue(CString& strResult);
	virtual void SetValue(LPCTSTR pszRawValue);
	virtual void GetCurrentText(CString& strResult);
	virtual void SetCurrentText(const CString& str);

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

	// clipboard
	virtual BOOL Paste();
	virtual BOOL Cut();
	virtual BOOL Copy();

	// Edit control only
	int  CalcTextPosUnderPt(CPoint point);
	void GetSel(int& nStartChar, int& nEndChar) const;
	DWORD GetSel() const;

	virtual BOOL CanFloatCell(ROWCOL, ROWCOL, const CGXStyle&, BOOL);
	virtual CWnd* GetWndPtr() const;
	virtual void GetSortKey(ROWCOL nRow, ROWCOL nCol, const CGXSortInfo& sortInfo, const CGXStyle& style, CString& sKey);
	virtual BOOL ConvertControlTextToValue(CString& str, ROWCOL nRow, ROWCOL nCol, const CGXStyle* pOldStyle);
	virtual void InitFromUserAttributes(CGXBCurrencyEdit* pEdit, const CGXStyle* pStyle);
	virtual BOOL GetControlText(CString& strResult, ROWCOL nRow, ROWCOL nCol, LPCTSTR pszRawValue, const CGXStyle& style);
	virtual BOOL OnGridSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL HitTestBtn(CPoint point, BOOL bClient = FALSE) const;
	virtual BOOL StoreStyle(ROWCOL nRow, ROWCOL nCol, const CGXStyle* pStyle, GXModifyType mt, int nType, const CGXStyle* pOldStyle);
	

// Implementation
public:
	virtual BOOL CreateControl(DWORD dwStyle = 0);

// Attributes
protected:
	UINT            m_nID;

	BOOL            m_bIsActive;    // indicates, if the CWnd is active
	CFont           m_font;

	int     m_dyHeight;
	
	int     m_dxMaxCharWidth;
	
	CString m_sLastChar;
	
	BOOL    m_bDoNotEmptyLastChar;

	BOOL	m_bSetText;
	
	BOOL m_bFirst;

	BOOL m_bIgnoreFractions;

	ROWCOL m_LFRow;

	BOOL m_bFromInit;

	BOOL m_bModified;
	
	CGXCaptiveCurEdit m_CapCtrlWnd;
	
	//Added these 4/1/97
	BOOL m_bForceHitTrue;

	static TCHAR m_cBlankThouSep;
	static TCHAR m_cBlankMonetarySym;

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXCurrencyEdit)
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT flags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT flags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	afx_msg LRESULT OnCalcSetText(WPARAM wParam, LPARAM lParam);
#if _MFC_VER >= 0x0400
	afx_msg LRESULT OnSetText(WPARAM wParam, LPARAM lParam);
#endif
	DECLARE_MESSAGE_MAP()
};

#ifdef _GX_ENABLE_INLINES
inline void CGXCurrencyEdit::GetSel(int& nStartChar, int& nEndChar) const
	{ ASSERT(::IsWindow(m_hWnd)); DWORD dw = (DWORD)::SendMessage(m_hWnd, EM_GETSEL, 0, 0); nStartChar = LOWORD(dw); nEndChar = HIWORD(dw); }

inline DWORD CGXCurrencyEdit::GetSel() const
	{ ASSERT(::IsWindow(m_hWnd)); return (DWORD)::SendMessage(m_hWnd, EM_GETSEL, 0, 0); }
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
#endif // _MFC_VER >= 0x0400

#endif //_GXCURCTL_H_
