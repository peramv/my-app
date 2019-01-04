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

// gxcrtf.h : header file
//

#ifndef _GXCRTF_H_
#define _GXCRTF_H_

#if _MFC_VER >= 0x0400

#ifndef _GXCTRL_H_
#include "grid\gxctrl.h"
#endif

//
// GridMFC Extension DLL
// initialize declaration context
//

#ifdef _GXDLL
	#undef AFX_DATA
	#define AFX_DATA    GX_DATAEXT
#endif

/////////////////////////////////////////////////////////////////////////////
// CGXRichEditCtrl window

enum AllowShrinkSize
{
	gxNoShrink = 0,         // autosize will never shrink cells
	gxOnlyAfterResize = 1,  // backspace will shrink cells to their initial height
							// (before the first time cell was enlarged)
	gxAllways = 2           // autosize can shrink cells smaller than initial height
};


/////////////////////////////////////////////////////////////////////////////
class CGXRichEditCtrl : public CRichEditCtrl, public CGXControl
{
	DECLARE_CONTROL(CGXRichEditCtrl)
	DECLARE_DYNAMIC(CGXRichEditCtrl)

		// Construction
public:
	CGXRichEditCtrl(CGXGridCore* pGrid);
	BOOL CreateControl(DWORD dwStyle = ES_MULTILINE, UINT nID = 0);
	virtual CWnd* GetWndPtr() const;

	// Attributes
public:
	BOOL            m_bIsActive;    // indicates, if the CWnd is active
	BOOL            m_bModified;

	// defaults for SetEventMask() and SetOptions()
	DWORD           m_dwEventMask;
	DWORD           m_dwOptions;

	// optional support for shrinking cells (autosize)
	int             m_nShrinkMode;
	int             m_nMinShrinkSize;   // initial row height

	// Attributes
public:
	DWORD SetEventMask(DWORD dwEventMask);

	// status bits
	virtual void SetActive(BOOL bActive);
	virtual BOOL IsActive();
	virtual void SetModify(BOOL bModified);
	virtual BOOL GetModify();

	// Text, RTF and style information
	virtual BOOL GetSelectedText(CString& sNoRTFString);
	virtual void GetCurrentText(CString& sNoRTFString);
	virtual void SetCurrentText(const CString& sNoRTFString);

	virtual void SetValue(LPCTSTR pszRTFString);
	virtual BOOL GetValue(CString& sRTFString);

	virtual BOOL GetControlText(CString& strResultNoRTF, ROWCOL nRow, ROWCOL nCol, LPCTSTR pszRawValue, const CGXStyle& style);
	virtual BOOL SetControlText(ROWCOL nRow, ROWCOL nCol, const CString& sNoRTFString, UINT nFlags, const CGXStyle* pOldStyle = NULL);
	virtual BOOL ConvertControlTextToValue(CString& str, ROWCOL nRow, ROWCOL nCol, const CGXStyle* pOldStyle);

	virtual BOOL Store();
	virtual BOOL StoreStyle(ROWCOL nRow, ROWCOL nCol, const CGXStyle* pStyle, GXModifyType mt, int nType, const CGXStyle* pOldStyle);
	virtual BOOL LoadStyle(ROWCOL nRow, ROWCOL nCol, CGXStyle* pStyle);

	// Initialization and drawing
	virtual CRect GetCellRect(ROWCOL nRow, ROWCOL nCol, LPRECT rectItem = NULL, const CGXStyle* pStyle = NULL);
	virtual CSize AddBorders(CSize size, const CGXStyle& style);  // counterpart to GetCellRect
	virtual void Init(ROWCOL nRow, ROWCOL nCol);
	virtual void Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle);
	virtual void Hide();

	// Mouse events
	virtual BOOL LButtonUp(UINT nFlags, CPoint pt, UINT nHitState);
	virtual BOOL LButtonDblClk(UINT nFlags, CPoint pt);

	// Optimal height
	virtual CSize CalcSize(CDC* pDC, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle, BOOL bVert);

	// Control notifications
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

	// Keyboard
	// Called when the user presses a key on the inactive current cell
	virtual BOOL OnGridKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL OnGridChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL OnGridDoubleByteChar(const CString& sChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL ValidateString(const CString& sNoRTFString);

	// Clipboard
	virtual BOOL Copy();
	virtual BOOL Paste();
	virtual BOOL Cut();
	virtual BOOL CanCopy();
	virtual BOOL CanCut();
	virtual BOOL CanPaste();

	// Find and Replace
	virtual BOOL FindText(const GX_FR_STATE& find, ROWCOL nRow, ROWCOL nCol, BOOL bCurrentPos, BOOL bSetCell = FALSE);
	virtual void ReplaceSel(LPCTSTR pszNoRTFString);
	virtual BOOL ReplaceAll(const GX_FR_STATE& find, ROWCOL nRow, ROWCOL nCol);

	// static members
	static void AFXAPI SetRichText(CRichEditCtrl* pWnd, LPCSTR szRTFString);
#ifdef _UNICODE
	static void AFXAPI SetRichText(CRichEditCtrl* pWnd, LPCWSTR szRTFString);
#endif
	static CString AFXAPI GetRichText(CRichEditCtrl* pWnd, CString& sRTFString);

	virtual void ConvertStyleToRTF(PARAFORMAT& pf, CHARFORMAT& cf, const CGXStyle* pStyle);
	virtual void ConvertRTFToStyle(const PARAFORMAT& pf, const CHARFORMAT& cf, CGXStyle* pStyle);

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXRichEditCtrl)
	//}}AFX_VIRTUAL

	// Implementation
public:
	virtual ~CGXRichEditCtrl();

	// Implementation - Attributes
protected:
	BOOL m_bBottomless;
	BOOL m_bCalcSize;
	CRect m_rcReSize;

	// CRichEditCtrl for drawing inactive cells (and last loaded text)
	CRichEditCtrl   m_DrawRTFWnd;
	CString         m_sLastDrawRTFText;

	// CRichEditCtrl for StoreStyle operation (and last loaded text)
	CRichEditCtrl   m_StoreRTFWnd;
	CString         m_sLastStoreRTFText;

	// CRichEditCtrl for CalcSize operation (and last loaded text)
	CRichEditCtrl   m_ResizeRTFWnd;
	CString         m_sLastResizeRTFText;

	// CRichEditCtrl for LoadStyle operation (and last loaded text)
	CRichEditCtrl   m_InfoRTFWnd;
	CString         m_sLastInfoRTFText;

	// Generated message map functions
protected:
	afx_msg BOOL OnChildRequestResize(UINT id, NMHDR* pNotifyStruct, LRESULT* result);

	//{{AFX_MSG(CGXRichEditCtrl)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg UINT OnGetDlgCode();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL OnRequestResize(NMHDR* pNotifyStruct, LRESULT* result);
	afx_msg void OnDeadChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysDeadChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

// Fix some incompatibilities with MFC 4.2 and MFC 4.2b Patch UNICODE builds
// so that we do not have to provide different .DEF files
// [VC7] Gives functions already defined errors in VC7 and so excluded.
public:
#if defined(_UNICODE) && (_MFC_VER >= 0x0420 && _MFC_VER < 0x0700)
  #if !defined(_RICHEDIT_VER)   // MFC 4.2

	virtual void ConvertStyleToRTF(PARAFORMAT& pf, CHARFORMATA& cf, const CGXStyle* pStyle);
	virtual void ConvertRTFToStyle(const PARAFORMAT& pf, const CHARFORMATA& cf, CGXStyle* pStyle);

  #else // MFC 4.2b Patch

	virtual void ConvertStyleToRTF(PARAFORMAT& pf, CHARFORMATW& cf, const CGXStyle* pStyle);
	virtual void ConvertRTFToStyle(const PARAFORMAT& pf, const CHARFORMATW& cf, CGXStyle* pStyle);

  #endif
#endif
};

/////////////////////////////////////////////////////////////////////////////


//
// GridMFC extension DLL
// reset declaration context
//

#undef AFX_DATA
#define AFX_DATA

//

#endif // _MFC_VER

#endif // _GXCRTF_H_
