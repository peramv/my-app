///////////////////////////////////////////////////////////////////////////////
// gxcrtf.cpp : implementation file
//
// Copyright (c) 1997-2012 Rogue Wave Software, Inc.  All Rights Reserved.
//
// This computer software is owned by Rogue Wave Software, Inc. and is protected by
// U.S. copyright laws and other laws and by international treaties. This
// computer software is furnished by Rogue Wave Software, Inc. pursuant to a written
// license agreement and may be used, copied, transmitted, and stored
// only in accordance with the terms of such license agreement and with
// the inclusion of the above copyright notice.  This computer software or
// any other copies thereof may not be provided or otherwise made available
// to any other person.
//
// U.S. Government Restricted Rights.  This computer software:
//      (a) was developed at private expense and is in all respects the
//          proprietary information of Rogue Wave Software, Inc.;
//      (b) was not developed with government funds;
//      (c) is a trade secret of Rogue Wave Software, Inc. for all purposes of the
//          Freedom of Information Act; and
//      (d) is a commercial item and thus, pursuant to Section 12.212
//          of the Federal Acquisition Regulations (FAR) and DFAR
//          Supplement Section 227.7202, Government’s use, duplication or
//          disclosure of the computer software is subject to the restrictions
//          set forth by Rogue Wave Software, Inc.
//
///////////////////////////////////////////////////////////////////////////////
//
// Author: Stefan Hoenig
//

#define _OG_EXPORT_IMPL

#include "stdafx.h"

#if _MFC_VER >= 0x0400

#ifndef _GXRESRC_H_
#include "grid\gxresrc.h"
#endif

#ifndef _GXCRTF_H_
#include "grid\gxcrtf.h"
#endif


#ifndef _GXCORE_H_
#include "grid\gxcore.h"
#endif

#ifndef _GXSTATE_H_
#include "grid\gxstate.h"
#endif

#ifndef _GXEXT_H_
#include "grid\gxext.h"
#endif

#ifndef _WINNLS_
#include "winnls.h"
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXCRTF")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

#pragma warning(disable: 4267)

/////////////////////////////////////////////////////////////////////////////
// CGXRichEditCtrl

// Important Notes:
//
// The rich edit control determines attributes like font,
// horizontal alignment and text color information
// from the RTF string which is stored in the
// CGXStyle value (see CGXStyle::GetValue).
//
// This makes it impossible to inherit these attributes
// from base styles, e.g. column style or other styles.
//
// It is also not possible to override GetStyleRowCol
// and specify the horizontal alignment or font
// setting at runtime by changing the style-font attributes.
// This is only possible through RTF statements.
//
// When the user formats cells with the Format|Cells
// dialog (or by pressing the "B", "I", "U" or other toolbar
// buttons), SetStyleRange will be called. SetStyleRange
// calls CGXControl::StoreStyle for each cell. CGXRichEditCtrl
// provides its own version of StoreStyle. This method
// extracs font and text color information from the style
// object, and inserts these attributes into the RTF string
// and writes the RTF string back to the style object (with
// CGXStyle::SetValue).
//
// This technique makes it possible that the user is
// able to format RTF cells in any way. StoreStyle even
// takes care if only a selected text in the active
// RTF cell should be formatted. For example, if the
// user selects a text and presses the "Bold" toolbar-button,
// only the selected text will become Bold.
//
// Additional features:
//
// CGXRichEditCtrl supports autosize (bottomless) cells.
// Cells can automatically grow and shrink while the
// user is entering or removing text. Autosize is only
// possible for the cell height, not for the cell width.
//
// CGXRichEditCtrl also supports resizing rows through
// the menu command Format|Resize Rows. Columns cannot
// be resized. This is due to a limitation of the
// RICHEDIT control.
//
// CGXRichEditCtrl supports Find and Replace. Find and
// Replace ignores any RTF statements. So, you cannot
// search for "Bold" or "Italic" or other attributes
// but only for text no matter if it is bold or
// not.
//
// CGXRichEditCtrl supports Cut, Copy and Paste for
// RTF strings. If the user copies formatted text from the RTF
// cell, the formatted text can be pasted into another RTF
// cell (or any other RTF application, e.g. WordPad).
//
// NOTE: If you want that the RTF cell shall show scrollbars
// when the text does not fit in the window, you should specify
// the WS_VSCROLL bit for dwStyle when calling CreateControl.
//
// Example:
//     pRTFControl->CreateControl(ES_MULTILINE | WS_VSCROLL);
//
// Furthermore, it is recommended that you specify ES_MULTILINE
// for the edit style. If you want to support both rich edit
// controls with ES_MULTILINE and without ES_MULTOUT flag, you
// should register two different Rich Edit Control objects
// because this style setting cannot be changed on the fly.
//
// Known limitation:
// The Rich Edit Control does not support zooming. If
// if you call the CGXGridCore::SetZoom() API, the
// Rich Edit Control will not change its font settings.

GRID_IMPLEMENT_CONTROL(CGXRichEditCtrl, CGXControl);
IMPLEMENT_DYNAMIC(CGXRichEditCtrl, CRichEditCtrl);

static BOOL NEAR s_bLockRequestResize = FALSE;

// SRSTUDIO-1219 Create a Control ID so notifications can get picked up with ON_NOTIFY_EX
#define ID_RICHEDITCTRL_DRAW	14441
#define ID_RICHEDITCTRL_STORE	14442
#define ID_RICHEDITCTRL_RESIZE	14443
#define ID_RICHEDITCTRL_INFO	14444

// Something is wrong with MFC 4.2 - we need to manually include
// these methods here when doing the OG Shared Dll build.

#if defined(_UNICODE) && _MFC_VER == 0x0420

inline BOOL CRichEditCtrl::SetDefaultCharFormat(CHARFORMAT &cf)
{
	ASSERT(::IsWindow(m_hWnd));
	cf.cbSize = sizeof(CHARFORMAT);
	return (BOOL)::SendMessage(m_hWnd, EM_SETCHARFORMAT, 0, (LPARAM)&cf);
}

inline BOOL CRichEditCtrl::SetSelectionCharFormat(CHARFORMAT &cf)
{
	ASSERT(::IsWindow(m_hWnd));
	cf.cbSize = sizeof(CHARFORMAT);
	return (BOOL)::SendMessage(m_hWnd, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf);
}

inline BOOL CRichEditCtrl::SetWordCharFormat(CHARFORMAT &cf)
{
	ASSERT(::IsWindow(m_hWnd));
	cf.cbSize = sizeof(CHARFORMAT);
	return (BOOL)::SendMessage(m_hWnd, EM_SETCHARFORMAT, SCF_SELECTION|SCF_WORD, (LPARAM)&cf);
}

inline DWORD CRichEditCtrl::GetDefaultCharFormat(CHARFORMAT &cf) const
{
	ASSERT(::IsWindow(m_hWnd));
	cf.cbSize = sizeof(CHARFORMAT);
	return (DWORD)::SendMessage(m_hWnd, EM_GETCHARFORMAT, 0, (LPARAM)&cf);
}

inline DWORD CRichEditCtrl::GetSelectionCharFormat(CHARFORMAT &cf) const
{
	ASSERT(::IsWindow(m_hWnd));
	cf.cbSize = sizeof(CHARFORMAT);
	return (DWORD)::SendMessage(m_hWnd, EM_GETCHARFORMAT, 1, (LPARAM)&cf);
}

// FindText is not found with debug build only ...
#ifdef _DEBUG
inline long CRichEditCtrl::FindText(DWORD dwFlags, FINDTEXTEX* pFindText) const
	{ ASSERT(::IsWindow(m_hWnd)); return (long)::SendMessage(m_hWnd, EM_FINDTEXTEX, dwFlags, (LPARAM)pFindText); }
#endif

#endif

CGXRichEditCtrl::CGXRichEditCtrl(CGXGridCore* pGrid)
	: CGXControl(pGrid)
{
	// defaults for event mask (call to SetEventMask)
	m_dwEventMask = ENM_REQUESTRESIZE | ENM_CHANGE | ENM_UPDATE
		| ENM_SELCHANGE | ENM_PROTECTED;

	// and SetOptions()
	m_dwOptions = ECO_AUTOWORDSELECTION | ECO_AUTOVSCROLL | ECO_AUTOHSCROLL
		| ECO_NOHIDESEL | ECO_SAVESEL;

	// optional support for shrinking cells (autosize)
	m_nMinShrinkSize = 0;
	m_nShrinkMode = gxOnlyAfterResize;
		// when auto size is turned on, the cell will shrink
		// back to its original size when the user presses <backspace>.

	m_bCalcSize = FALSE;
}

CGXRichEditCtrl::~CGXRichEditCtrl()
{
	DestroyWindow();
	m_DrawRTFWnd.DestroyWindow();
	m_InfoRTFWnd.DestroyWindow();
	m_StoreRTFWnd.DestroyWindow();
	m_ResizeRTFWnd.DestroyWindow();
}

CWnd* CGXRichEditCtrl::GetWndPtr() const
{
	return (CWnd*) this;
}

DWORD CGXRichEditCtrl::SetEventMask(DWORD dwEventMask)
{
	// Draw() will call CRichEditCtrl::SetEventMask.
	// Therefore we save the value.
	m_dwEventMask = dwEventMask;
	return CRichEditCtrl::SetEventMask(dwEventMask);
}

BOOL CGXRichEditCtrl::CreateControl(DWORD dwStyle, UINT nID)
{
	dwStyle &= ~WS_VISIBLE;
	dwStyle &= ~WS_BORDER;

	//
	// NOTE: If you want that the RTF cell shall show scrollbars
	// when the text does not fit in the window, you should specify
	// the WS_VSCROLL bit for dwStyle.
	//
	// Example:
	//
	//     pRTFControl->CreateControl(ES_MULTILINE | WS_VSCROLL);
	//
	// Furthermore, it is recommended that you specify ES_MULTILINE
	// for the edit style. If you want to support both rich edit
	// controls with ES_MULTILINE and without ES_MULTOUT flag, you
	// should register two different Rich Edit Control objects
	// because this style setting cannot be changed on the fly.
	//

	// Rich Edit Control creation

	// First, create the RTF window which will be used for displaying
	// the cells
	BOOL b = Create(dwStyle, CRect(0, 0, 10, 10), GridWnd(), nID);

	// Next, create the invisible RTF window used only for
	// interpreting and changing the RTF string

	// Position windows outside visible area
	CRect rc(30000, 30000, 30100, 30100);

	//-----------------------------------------------------
	// SRSTUDIO-1219 - RequestResize() Notificaitons
	// For VS 2010 and higher we need to set the ID and 
	// DlgCtrlID for the RichEditCtrl's otherwise the 
	// EN_REQUESTRESIZE notifications do not get sent 
	// properly and the cells draw incorrectly.
	//-----------------------------------------------------

#if _MSC_VER >= 1600
	b &= m_ResizeRTFWnd.Create(dwStyle, rc, this, ID_RICHEDITCTRL_RESIZE);
	m_ResizeRTFWnd.SetDlgCtrlID(ID_RICHEDITCTRL_RESIZE);
#else
	b &= m_ResizeRTFWnd.Create(dwStyle, rc, this, 0);
#endif

	dwStyle |= WS_BORDER | ES_MULTILINE;    // Don't remove WS_BORDER ! Otherwise the
		// cursor will get crazy when StoreStyle is called.
		// ES_MULTILINE avoids that font changes back to "System" when drawing
		// cells without ES_MULTILINE style.
	
#if _MSC_VER >= 1600
	b &= m_DrawRTFWnd.Create(dwStyle, rc, this, ID_RICHEDITCTRL_DRAW);
	m_DrawRTFWnd.SetDlgCtrlID(ID_RICHEDITCTRL_DRAW);
	b &= m_StoreRTFWnd.Create(dwStyle, rc, this, ID_RICHEDITCTRL_STORE);
	m_StoreRTFWnd.SetDlgCtrlID(ID_RICHEDITCTRL_STORE);
	b &= m_InfoRTFWnd.Create(dwStyle, rc, this, ID_RICHEDITCTRL_INFO);
	m_InfoRTFWnd.SetDlgCtrlID(ID_RICHEDITCTRL_INFO);
#else
	b &= m_DrawRTFWnd.Create(dwStyle, rc, this, nID);
	b &= m_StoreRTFWnd.Create(dwStyle, rc, this, nID);
	b &= m_InfoRTFWnd.Create(dwStyle, rc, this, nID);
#endif

	return b;
}

BEGIN_MESSAGE_MAP(CGXRichEditCtrl, CRichEditCtrl)
	//{{AFX_MSG_MAP(CGXRichEditCtrl)
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_SYSCHAR()
	ON_WM_SYSKEYDOWN()
	ON_WM_SYSKEYUP()
	ON_WM_CHAR()
	ON_WM_KILLFOCUS()
	ON_WM_GETDLGCODE()
	ON_WM_ERASEBKGND()
	ON_WM_DEADCHAR()
	ON_WM_SYSDEADCHAR()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_NOTIFY_REFLECT_EX(EN_REQUESTRESIZE, OnRequestResize)
	// SRSTUDIO-1219 - Fix for RequestResize() notification messages.
#if _MSC_VER >= 1600
	// With VS 2010 and 
	ON_NOTIFY_EX_RANGE(EN_REQUESTRESIZE, ID_RICHEDITCTRL_DRAW, ID_RICHEDITCTRL_INFO, OnChildRequestResize)
#else
	ON_NOTIFY_EX(EN_REQUESTRESIZE, 0, OnChildRequestResize)
#endif
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGXRichEditCtrl message handlers

// Status

void CGXRichEditCtrl::SetActive(BOOL bActive)
{
	if (!m_bIsActive && bActive && m_hWnd)
	{
		m_bIsActive = TRUE;
		// Force a call to GetStyleRowCol() because
		// GetStyleRowCol() might set style attributes
		// depending on the IsActive() flag
		FreeStyle();
		NeedStyle();
	}
	else
		m_bIsActive = bActive && m_hWnd;
}

BOOL CGXRichEditCtrl::IsActive()
{
	return m_bIsActive;
}

void  CGXRichEditCtrl::SetModify(BOOL bModified)
{
	CRichEditCtrl::SetModify(bModified);
}

BOOL CGXRichEditCtrl::GetModify()
{
	return CRichEditCtrl::GetModify();
}

// Operations

void CGXRichEditCtrl::Init(ROWCOL nRow, ROWCOL nCol)
{
	// Stores the cell coordinates, resets the style and sets the window text
	CGXControl::Init(nRow, nCol);

	if (!m_hWnd)
	{
		CreateControl();
	}

	NeedStyle(); // m_pStyle attribute

	if (Grid()->GetParam()->GetActivateCellFlags() & GX_CAFOCUS_SETCURRENT && OnStartEditing())
	{
		SetActive(TRUE);
	}else
	{
		SetActive(FALSE);
	}

	// Default parameters for Rich Edit
	PARAFORMAT pf;
	CHARFORMAT cf;
	ConvertStyleToRTF(pf, cf, m_pStyle);
	SetDefaultCharFormat(cf);
	SetParaFormat(pf);

	// Assign text and also specific parameters with RTF formatting
	SetRichText(this, m_pStyle->GetValueRef());
	SetSel(0, -1);   // Select all

	// mark cell as not modified
	SetModify(FALSE);

	if (m_nShrinkMode == gxOnlyAfterResize)
	{
		m_nMinShrinkSize = Grid()->GetRowHeight(nRow);
	}else
	{
		m_nMinShrinkSize = 0;
	}
}

//
// RTF Callback routines
//

struct _GXEditStreamOutStruct
{
	CString* m_pString;
	LONG m_lOffset;
};

struct _GXEditStreamInStruct
{
	LPCSTR m_psz;
	LONG m_lLength;
	LONG m_lOffset;
};

// _GXEditStreamInCallback
//
// copy text to RTF window

DWORD CALLBACK _GXEditStreamInCallback(SEC_DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG FAR *pcb)
{
	_GXEditStreamInStruct* pesResult = (_GXEditStreamInStruct*) dwCookie;

	// RichEdit only supports ansi strings!
	// Therefore, I use strcpy and strlen

	// pointer to buffer
	LPCSTR psz = pesResult->m_psz;
	psz += pesResult->m_lOffset;

	// If the buffer is too small _GXEditStreamInCallback
	// will be called again for remaining text
	if (pesResult->m_lLength > pesResult->m_lOffset + cb)
	{
		// QA: 31989 - #if Secure Code Cleanup.
		strncpy((LPSTR) pbBuff, psz, cb);

		*pcb = cb;
	}
	else
	{
		// QA: 31989 - #if Secure Code Cleanup.
		strcpy((LPSTR) pbBuff, psz);
		*pcb = (long)strlen(psz);
	}

	pesResult->m_lOffset += *pcb;

	return 0;
}

// _GXEditStreamOutCallback
//
// read out text from RTF window

DWORD CALLBACK _GXEditStreamOutCallback(SEC_DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG FAR *pcb)
{
	_GXEditStreamOutStruct* pesResult = (_GXEditStreamOutStruct*) dwCookie;

	if (cb > 0)
	{
		// SRSTUDIO-1679 Has been removed for the 11.1 (CD56) release. Possible crash still remains. 

		CString* psResult = pesResult->m_pString;

		// buffer is an ansi string (no UNICODE)
		LPTSTR pszBuffer = psResult->GetBuffer(cb+1+pesResult->m_lOffset) + pesResult->m_lOffset;

#ifndef _UNICODE
		// QA: 31989 - #if Secure Code Cleanup.
		strcpy(pszBuffer, (LPSTR) pbBuff);
#else
		MultiByteToWideChar(CP_ACP, 0, (LPSTR) pbBuff, cb,
			pszBuffer, cb);
		// make sure the last char is NULL so ReleaseBuffer can free it.
		pszBuffer[cb] = 0x00;

#endif

		psResult->ReleaseBuffer();

		*pcb = cb;

		pesResult->m_lOffset += cb;

		return 0; // continue
	}

	return 1; // abort
}

// _GXEditStreamCountCallback
//
// determine text length in RTF window

DWORD CALLBACK _GXEditStreamCountCallback(SEC_DWORD dwCookie, LPBYTE /*pbBuff*/, LONG cb, LONG FAR* /*pcb*/)
{
	*((long*) (void*) dwCookie) = cb;

	return 0;
}

//
// static routines
//

// SetRichText
//
// Set data for CRichEditCtrl

void AFXAPI CGXRichEditCtrl::SetRichText(CRichEditCtrl* pWnd, LPCSTR szRTFInput)
{
	_GXEditStreamInStruct es = { szRTFInput, (long)strlen(szRTFInput), 0 };
	EDITSTREAM esin = {(SEC_DWORD) &es, 0, _GXEditStreamInCallback};
	pWnd->StreamIn(SF_RTF, esin);
}

#ifdef _UNICODE
void AFXAPI CGXRichEditCtrl::SetRichText(CRichEditCtrl* pWnd, LPCWSTR szRTFInput)
{
	// RichEdit does not support UNICODE.
	// Translate wide string to ansi string
	int nLength = _tcsclen(szRTFInput)+1;
	char* psz = new char[nLength];
	WideCharToMultiByte (CP_ACP, 0, (CString) szRTFInput, -1,
		psz, nLength, NULL, NULL);
	SetRichText(pWnd, psz);
	if(psz)
	{
		delete [] psz;
	}
}
#endif

// GetRichText
//
// Read data from CRichEditCtrl


CString AFXAPI CGXRichEditCtrl::GetRichText(CRichEditCtrl* pWnd, CString& sRTFResult)
{
	// Retrieve data from Rich Text Control
	_GXEditStreamOutStruct es = { &sRTFResult, 0 };

	EDITSTREAM esResult = {(SEC_DWORD) (&es), 0, _GXEditStreamOutCallback};
				// NOTE: dwCookie is assigned a pointer to sResult !
				// EditStreamOutCallback will use this pointer and copy
				// the RTF data into the string
	pWnd->StreamOut(SF_RTF, esResult);

	return sRTFResult;
}

// GetSelectedText
//
// This method returns the the selected text of the current cell
// (e.g. in an edit window, this is the highlighted text).
// If no text is selected the whole window text will be returned.
//
// Returns TRUE if text was selected; FALSE if no text was selected.

BOOL CGXRichEditCtrl::GetSelectedText(CString& sNonRTFResult)
{
	if (IsActive())
	{
		// Get selected text
		long nStartChar = 0,
			 nEndChar = -1;

		GetSel(nStartChar, nEndChar);

		// if no text is selected use all text
		if (nEndChar == nStartChar)
		{
			GetWindowText(sNonRTFResult);

			return FALSE;   // no text selected
		}
		else
		{
			// Copy text to strResult
			sNonRTFResult = GetSelText();

			return TRUE;    // text selected
		}
	}
	else
	{
		// No caret visible. Get text which is displayed in the cell
		GetCurrentText(sNonRTFResult);

		return FALSE;   // no text selected
	}
}

// GetCurrentText
//
// Get unformatted text which is displayed in the cell

void CGXRichEditCtrl::GetCurrentText(CString& sNonRTFResult)
{
	if (IsActive())
	{
		GetWindowText(sNonRTFResult);
	}
	else if (IsInit())
	{
		// Convert RTF string to unformatted text
		NeedStyle();
		GetControlText(sNonRTFResult, m_nRow, m_nCol, NULL, *m_pStyle);
	}
	else
	{
		TRACE0("Warning: GetCurrentText was called for an unitialized control!\n");

		// Control is not initialized - Unable to determine text
		sNonRTFResult.Empty();
	}
}

// SetCurrentText
//
// save unformatted text

void CGXRichEditCtrl::SetCurrentText(const CString& sNonRTFText)
{
	if (!IsInit())
		return;

	if (!IsActive())
		SetActive(TRUE);

	// Add brackets and save it in style object
	CString sRTFString = (CString) "{\\rtf1 " + sNonRTFText + '}';

	if (ValidateString(sNonRTFText))
	{
		SetRichText(this, sRTFString);
		SetModify(TRUE);
		OnModifyCell();
	}
}

// GetControlText
//
// Converts the RTF string to unformatted text and stores the result
// in strResult.
//
// pszRTFString points to the RTF string. If pszRTFString is NULL,
// the RTF string will be determined from the style object with
// style.GetValue.

BOOL CGXRichEditCtrl::GetControlText(CString& strResult, ROWCOL /*nRow*/, ROWCOL /*nCol*/, LPCTSTR pszRTFString, const CGXStyle& style)
{
	// if value is specified, simply copy this value
	if (pszRTFString)
	{	strResult = pszRTFString;

	// check the style object
	}else if (style.GetIncludeValue())
	{
		strResult = style.GetValueRef();

	// no value
	}else
	{
		strResult.Empty();
		return FALSE;
	}

	// Convert RTF to unformatted text
	if (strResult != m_sLastStoreRTFText)
	{
		SetRichText(&m_StoreRTFWnd, strResult);
		m_sLastStoreRTFText = strResult;
	}

	m_StoreRTFWnd.GetWindowText(strResult);

	return TRUE;
}

// ConvertControlTextToValue and SetControlText
//
// The unformatted text will be converted to an RTF string and
// then stored in the grid.
//

BOOL CGXRichEditCtrl::ConvertControlTextToValue(CString& str, ROWCOL nRow, ROWCOL nCol, const CGXStyle* pOldStyle)
{
	// Add brackets and validate and save it in style object

	CGXStyle* pStyle = NULL;

	if (pOldStyle == NULL)
	{
		pStyle = Grid()->CreateStyle();
		Grid()->ComposeStyleRowCol(nRow, nCol, pStyle);
		pOldStyle = pStyle;
	}

	DWORD nMaxLength = 0;

	// check for maximum length
	if (pOldStyle->GetIncludeMaxLength()
		&& (nMaxLength = pOldStyle->GetMaxLength()) > 0
		&& (DWORD) str.GetLength() > nMaxLength)
	{
		str = (CString) '{' + str.Left(nMaxLength) + '}';

	// default
	}else
	{	
		str = (CString) '{' + str + '}';
	}

	if (pStyle)
	{
		Grid()->RecycleStyle(pStyle);
	}

	return TRUE;
}

BOOL CGXRichEditCtrl::SetControlText(ROWCOL nRow, ROWCOL nCol, const CString& sNonRTFText, UINT nFlags, const CGXStyle* pOldStyle)
{
	// Add brackets and validate and save it in style object

	BOOL bSuccess = FALSE;
	CGXStyle* pStyle = NULL;

	if (pOldStyle == NULL)
	{
		pStyle = Grid()->CreateStyle();
		Grid()->ComposeStyleRowCol(nRow, nCol, pStyle);
		pOldStyle = pStyle;
	}

	// check for read-only
	if (Grid()->GetParam()->IsLockReadOnly() &&
		(Grid()->IsReadOnly() || pOldStyle->GetIncludeReadOnly() && pOldStyle->GetReadOnly()))
	{
		bSuccess = FALSE;

	// default
	}else
	{
		CString sValue = sNonRTFText;
		if (ConvertControlTextToValue(sValue, nRow, nCol, pOldStyle))
			bSuccess = Grid()->SetValueRange(CGXRange(nRow, nCol), sValue, gxOverride, 0, nFlags);
	}

	if (pStyle)
	{
		Grid()->RecycleStyle(pStyle);
	}

	return bSuccess;

	// Typical calling sequence:
	//     CGXRichEditCtrl::SetControlText
	//     CGXGridCore::SetValueRange
	//     CGXGridCore::SetStyleRange
	//     CGXRichEditCtrl::StoreStyle
	//     CGXControl::StoreStyle
	//     CGXGridCore::StoreStyleRowCol
	//
}

// GetValue
//
// Reads out the RTF string from the current cell.

BOOL CGXRichEditCtrl::GetValue(CString& sRTFResult)
{
	if (!IsInit())
	{
		return FALSE;
	}

	if (IsActive())
	{
		// Get value CRichEditCtrl
		GetRichText(this, sRTFResult);
	}
	else
	{
		// Get value from style
		NeedStyle();
		sRTFResult = m_pStyle->GetValueRef();
	}

	return TRUE;
}

// SetValue
//
// Stores and displays the given RTF string in the current cell

void CGXRichEditCtrl::SetValue(LPCTSTR pszRTFString)
{
	SetRichText(this, pszRTFString);
}

// ValidateString
//
// Check if the window text is valid when the user presses a character

BOOL CGXRichEditCtrl::ValidateString(const CString& /*sNoRTFString*/)
{
	return TRUE;
}

// Store
//
// Stores the RTF string, resets the modified-flag and redraws the cell.

BOOL CGXRichEditCtrl::Store()
{
	// Calls SetStyleRange() and resets the modify flag
	ASSERT(m_pStyle);
	BOOL bSuccess = FALSE;

	CString sRTFString;
	if (m_pStyle && GetModify() && GetValue(sRTFString))
	{
		SetActive(FALSE);

		bSuccess = Grid()->SetValueRange(
			CGXRange(m_nRow, m_nCol),
			sRTFString,
			gxOverride,
			0, GX_INVALIDATE);
			// Cell will be automatically redrawn inactive

		// SetModify(FALSE);

		// Typical calling sequence:
		//     CGXRichEditCtrl::Store
		//     CGXGridCore::SetValueRange
		//     CGXGridCore::SetStyleRange
		//     CGXRichEditCtrl::StoreStyle
		//     CGXControl::StoreStyle
		//     CGXGridCore::StoreStyleRowCol
		//
	}

	return bSuccess;
}

// ConvertRTFToStyle
//
// Initializes a style object based on the PARAFORMAT
// and CHARFORMAT information.

void CGXRichEditCtrl::ConvertRTFToStyle(const PARAFORMAT& pf, const CHARFORMAT& cf, CGXStyle* pStyle)
{
	ASSERT(pStyle != NULL);

	// Horizontal Alignment
	if (pf.dwMask & PFM_ALIGNMENT)
	{
		if (pf.wAlignment == PFA_RIGHT)
		{
			pStyle->SetHorizontalAlignment(DT_RIGHT);
		}else if (pf.wAlignment == PFA_CENTER)
		{
			pStyle->SetHorizontalAlignment(DT_CENTER);
		}else
		{
			pStyle->SetHorizontalAlignment(DT_LEFT);
		}
	}

	// NOT supported:
	// PFM_STARTINDENT
	// PFM_RIGHTINDENT
	// PFM_OFFSET
	// PFM_TABSTOPS
	// PFM_NUMBERING
	// PFM_OFFSETINDENT
	// CFM_PROTECTED and CFM_OFFSET
	//
	// You can add support for these attributes by adding User Attributes
	// (see AddUserAttribute in online help) and overriding
	// ConvertRTFToStyle

	// Font
	{
		CGXFont font;

		// Bold
		if (cf.dwMask & CFM_BOLD)
		{
			font.SetBold(cf.dwEffects & CFE_BOLD);
		}

		// Italic
		if (cf.dwMask & CFM_ITALIC)
		{
			font.SetItalic(cf.dwEffects & CFE_ITALIC);
		}

		// StrikeOut
		if (cf.dwMask & CFM_STRIKEOUT)
		{
			font.SetStrikeOut(cf.dwEffects & CFE_STRIKEOUT);
		}

		// Underline
		if (cf.dwMask & CFM_UNDERLINE)
		{
			font.SetUnderline(cf.dwEffects & CFE_UNDERLINE);
		}

		// FaceName
#if !defined(_UNICODE)
		if (cf.dwMask & CFM_FACE)
		{
			font.SetFaceName(cf.szFaceName);
		}
#else
		// RichEdit does not support UNICODE.
		// Translate ansi string to UNICODE string
		if (cf.dwMask & CFM_FACE)
		{
			font.SetFaceName((CString) (LPSTR) cf.szFaceName);
		}
#endif

		// Size
		if (cf.dwMask & CFM_SIZE)
		{
			font.SetSize(cf.yHeight / 20);
		}
		pStyle->SetFont(font);
	}

	// Color
	if (cf.dwMask & CFM_COLOR)
	{
		pStyle->SetTextColor(cf.crTextColor);
	}

}

// ConvertStyleToRTF
//
// Initializes a PARAFORMAT and CHARFORMAT structure
// based on the information stored in the style object.

void CGXRichEditCtrl::ConvertStyleToRTF(PARAFORMAT& pf, CHARFORMAT& cf, const CGXStyle* pStyle)
{
	memset(&pf, 0, sizeof(pf));
	pf.cbSize = sizeof(pf);

	memset(&cf, 0, sizeof(cf));
	cf.cbSize = sizeof(cf);

	if (pStyle == NULL)
	{
		return;
	}

	// Horizontal Alignment
	if (pStyle->GetIncludeHorizontalAlignment())
	{
		pf.dwMask |= PFM_ALIGNMENT;

		DWORD ntAlign = pStyle->GetHorizontalAlignment();

		if (ntAlign & DT_RIGHT)
		{
			pf.wAlignment = PFA_RIGHT;
		}else if (ntAlign & DT_CENTER)
		{
			pf.wAlignment = PFA_CENTER;
		}else
		{
			pf.wAlignment = PFA_LEFT;
		}
	}

	// NOT supported:
	// PFM_STARTINDENT
	// PFM_RIGHTINDENT
	// PFM_OFFSET
	// PFM_TABSTOPS
	// PFM_NUMBERING
	// PFM_OFFSETINDENT
	// CFM_PROTECTED and CFM_OFFSET
	//
	// You can add support for these attributes by adding User Attributes
	// (see AddUserAttribute in online help) and overriding
	// ConvertStyleToRTF

	// Font
	if (pStyle->GetIncludeFont())
	{
		const CGXFont& font = pStyle->GetFontRef();

		// Bold
		if (font.GetIncludeWeight())
		{
			cf.dwMask |= CFM_BOLD;

			if (font.GetBold())
			{
				cf.dwEffects |= CFE_BOLD;
			}
		}

		// Italic
		if (font.GetIncludeItalic())
		{
			cf.dwMask |= CFM_ITALIC;

			if (font.GetItalic())
			{
				cf.dwEffects |= CFE_ITALIC;
			}
		}

		// StrikeOut
		if (font.GetIncludeStrikeOut())
		{
			cf.dwMask |= CFM_STRIKEOUT;

			if (font.GetStrikeOut())
			{
				cf.dwEffects |= CFE_STRIKEOUT;
			}
		}

		// Underline
		if (font.GetIncludeUnderline())
		{
			cf.dwMask |= CFM_UNDERLINE;

			if (font.GetUnderline())
			{
				cf.dwEffects |= CFE_UNDERLINE;
			}
		}

		// FaceName
		if (font.GetIncludeFaceName())
		{
			cf.dwMask |= CFM_FACE;

#if !defined(_UNICODE) || (_MFC_VER >= 0x0420 && !(_RICHEDIT_VER == 0x0100))
			// QA: 31989 - #if Secure Code Cleanup.
			_tcscpy(cf.szFaceName, font.GetFaceName());
#else
			// RichEdit does not support UNICODE.
			// Translate wide string to ansi string
			WideCharToMultiByte (CP_ACP, 0, font.GetFaceName(), -1,
				(LPSTR) cf.szFaceName, sizeof(cf.szFaceName), NULL, NULL);
#endif
		}

		// Size
		if (font.GetIncludeSize())
		{
			cf.dwMask |= CFM_SIZE;

			cf.yHeight = (LONG) (font.GetSize()*20);
		}

		cf.bCharSet = font.GetLogFontRef().lfCharSet;
		cf.bPitchAndFamily = font.GetLogFontRef().lfPitchAndFamily;
	}

	// Color
	if (pStyle->GetIncludeTextColor())
	{
		cf.dwMask |= CFM_COLOR;

		cf.crTextColor = pStyle->GetTextColor();
	}
}

// StoreStyle
//
// Filters out style information (e.g. font,
// textcolor and horizontal alignment) which
// should be directly stored into the RTF value
// for the cell.
//
// Other formattings which cannot be expressed
// with RTF statements (e.g. interior, borders)
// will be passed to CGXControl::StoreStyle
//
// CGXControl::StoreStyle will call CGXGridCore::StoreStyleRowCol.
//
// In OG 1.1, CGXGridCore::StoreStyleRowCol was directly called. This has
// changed in version 1.2. Now, the behavior more cell-oriented and allows
// specific controls to modify the style object before it is stored in the
// data structure.

BOOL CGXRichEditCtrl::StoreStyle(ROWCOL nRow, ROWCOL nCol, const CGXStyle* pStyle, GXModifyType mt, int nType, const CGXStyle* pOldStyle)
{
	ASSERT(pStyle || mt == gxRemove);
	ASSERT(pOldStyle);

	if (mt == gxCopy || mt == gxRemove)
		return CGXControl::StoreStyle(nRow, nCol, pStyle, mt, nType, pOldStyle);

	ASSERT(nRow <= Grid()->GetRowCount() && nCol <= Grid()->GetColCount());
	// ASSERTION-> cell coordinates out of range ->END

	// Transfer the style information into the
	// PARAFORMAT and CHARFORMAT structure
	PARAFORMAT pf, opf;
	CHARFORMAT cf, ocf;

	ConvertStyleToRTF(pf, cf, pStyle);
	ConvertStyleToRTF(opf, ocf, pOldStyle);

	// If any flags of the PARAFORMAT or CHARFORMAT were set,
	// modify the value for the style object using the RichTextCtrl
	// routines SetParaFormat and SetCharFormat

	BOOL bValOrCtl = pStyle && (pStyle->GetIncludeValue() || pStyle->GetIncludeControl());

	if (pf.dwMask || cf.dwMask || bValOrCtl)
	{
		CGXStyle* pStyleEx = pStyle->Clone();

		if (Grid()->IsCurrentCell(nRow, nCol) && IsActive() && !bValOrCtl)
		{
			pStyleEx->SetIncludeFont(FALSE);
			pStyleEx->SetIncludeTextColor(FALSE);
			pStyleEx->SetIncludeHorizontalAlignment(FALSE);

			// Read out the resulting RTF data
			if (cf.dwMask)
			{
				SetWordCharFormat(cf);
				SetSelectionCharFormat(cf);
			}

			if (pf.dwMask)
				SetParaFormat(pf);

			SetModify(TRUE);
			OnModifyCell();
		}
		else
		{
			// Load RTF data into m_StoreRTFWnd
			CString sRTFString = pStyle->GetIncludeValue()
				? pStyle->GetValueRef()
				: pOldStyle->GetValueRef();

			pStyleEx->SetIncludeFont(FALSE);
			pStyleEx->SetIncludeTextColor(FALSE);
			pStyleEx->SetIncludeHorizontalAlignment(FALSE);

			if (sRTFString != m_sLastStoreRTFText || sRTFString.IsEmpty())
			{
				m_StoreRTFWnd.SetParaFormat(opf);
				m_StoreRTFWnd.SetDefaultCharFormat(ocf);
				SetRichText(&m_StoreRTFWnd, sRTFString);
				m_sLastStoreRTFText = sRTFString;
			}

			// Apply format to RTF data
			m_StoreRTFWnd.SetSel(0, -1);

			if (pf.dwMask)
			{
				m_StoreRTFWnd.SetParaFormat(pf);
			}

			if (cf.dwMask)
			{
				m_StoreRTFWnd.SetSelectionCharFormat(cf);
			}

			// Read out the resulting RTF data
			pStyleEx->SetValue(GetRichText(&m_StoreRTFWnd, sRTFString));
		}

		BOOL bStoreDone = FALSE;

		// Check if we still need to process the style (and create undo info)
		if (pStyleEx->GetStyleBits())
		{
			// Store the changed style object
			bStoreDone = CGXControl::StoreStyle(nRow, nCol, pStyleEx, mt, nType, pOldStyle);
		}

		// free pStyleEx
		Grid()->RecycleStyle(pStyleEx);

		return bStoreDone;
	}

	return CGXControl::StoreStyle(nRow, nCol, pStyle, mt, nType, pOldStyle);
}

// LoadStyle
//
// Determines the cell-specifc style information for the
// specified cell. RTF handles font, textcolor and text
// alignment in the RTF value. Therefore, LoadStyle will
// extract this information from the RTF value and set
// this attributes in the style object.
//
// You should call LoadStyle after you have composed
// the style information of the cell.
//
// Example:
//
//      // Cell style (as stored in CGXData)
//      CGXStyle style;
//      ComposeStyleRowCol(nRow, nCol, &style);
//
//      // Cell-specific style, e.g. RTF will set font and textcolor
//      // attributes of the current selection
//      CGXControl* pControl = GetRegisteredControl(style.GetControl());
//      pControl->LoadStyle(nRow, nCol, &style);
//
//      bRet = style.IsSubSet(styleNeeded);

BOOL CGXRichEditCtrl::LoadStyle(ROWCOL nRow, ROWCOL nCol, CGXStyle* pStyle)
{
	ASSERT(nRow <= Grid()->GetRowCount() && nCol <= Grid()->GetColCount());
	// ASSERTION-> cell coordinates out of range ->END

	// Request the style information from the
	// PARAFORMAT and CHARFORMAT structure
	PARAFORMAT pf;
	memset(&pf, 0, sizeof(pf));
	pf.cbSize = sizeof(pf);

	CHARFORMAT cf;
	memset(&cf, 0, sizeof(cf));
	cf.cbSize = sizeof(cf);

	if (IsInit() && Grid()->IsCurrentCell(nRow, nCol) && IsActive())
	{
		GetSelectionCharFormat(cf);
		GetParaFormat(pf);

		ConvertRTFToStyle(pf, cf, pStyle);
	}
	else if (pStyle->GetIncludeValue())
	{
		CString sRTFString = pStyle->GetValueRef();

		if (sRTFString.IsEmpty())
			return FALSE;

		if (sRTFString != m_sLastInfoRTFText)
		{
			SetRichText(&m_InfoRTFWnd, sRTFString);
			m_sLastInfoRTFText = sRTFString;
		}

		// Apply format to RTF data
		m_InfoRTFWnd.SetSel(0, -1);

		m_InfoRTFWnd.GetParaFormat(pf);
		m_InfoRTFWnd.GetSelectionCharFormat(cf);

		ConvertRTFToStyle(pf, cf, pStyle);
	}


	// If any flags of the PARAFORMAT or CHARFORMAT were set,
	// modify the value for the style object using the RichTextCtrl
	// routines SetParaFormat and SetCharFormat
	if (pf.dwMask || cf.dwMask)
		return TRUE;

	return FALSE;
}

CRect CGXRichEditCtrl::GetCellRect(ROWCOL nRow, ROWCOL nCol, LPRECT rectItem /* = NULL */, const CGXStyle* pStyle /*= NULL*/)
{
	// compute the interior rectangle for the text
	// without buttons and borders

	CRect rect = CGXControl::GetCellRect(nRow, nCol, rectItem, pStyle);

	// reserve some space on the left and right side
	int xFrame = max(GetSystemMetrics(SM_CXFRAME)/2, 2);

	rect.left += xFrame;
	rect.right -= xFrame/2;

	return rect;
}

CSize CGXRichEditCtrl::AddBorders(CSize size, const CGXStyle& style)
{
	// this is the counterpart to GetCellRect

	// reserve some space on the left and right side
	int xFrame = max(GetSystemMetrics(SM_CXFRAME)/2, 2);

	size.cx += xFrame;
	size.cx += xFrame/2;

	return Grid()->AddBorders(size, style);
}

void CGXRichEditCtrl::Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle)
{
	ASSERT(pDC != NULL && pDC->IsKindOf(RUNTIME_CLASS(CDC)));
	// ASSERTION-> Invalid Device Context ->END
	ASSERT(nRow <= Grid()->GetRowCount() && nCol <= Grid()->GetColCount());
	// ASSERTION-> Cell coordinates out of range ->END

	ASSERT_VALID(pDC);

	// Is this is the current cell and is it active?
	if (nRow == m_nRow && nCol == m_nCol && IsActive() && !Grid()->IsPrinting())
	{
		// ------------------ Active Window ---------------------------

		// Disable OnRequestResize processing while drawing the cell
		s_bLockRequestResize = TRUE;

		// Background + Frame
		DrawBackground(pDC, rect, *m_pStyle, TRUE);

		// RTF window positon
		CRect rectText = GetCellRect(nRow, nCol, rect);
		MoveWindow(rectText, FALSE);

		// colors
		COLORREF rgbCell = RGB(255,255,255);
		COLORREF rgbText = m_pStyle->GetTextColor();

		if (m_pStyle->GetInteriorRef().GetStyle() == BS_NULL)
		{
			rgbCell = m_pStyle->GetInteriorRef().GetBkColor();
		}else if (m_pStyle->GetInteriorRef().GetStyle() == BS_SOLID)
		{
			rgbCell = m_pStyle->GetInteriorRef().GetColor();
		}

		if (Grid()->GetParam()->GetProperties()->GetBlackWhite())
		{
			rgbCell = RGB(255,255,255);
			rgbText = RGB(0,0,0);
		}

		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(rgbText);

		SetBackgroundColor(FALSE, rgbCell);

		// Support for WYSIWYG
		if (pDC->m_hAttribDC != pDC->GetSafeHdc())
		{
			SetTargetDevice(pDC->m_hAttribDC, rectText.Width() * 1440 / GXGetFontState()->m_nLogPixelsY);
		}else
		{
			SetTargetDevice(NULL, 0);
		}

		// Allow Enter
		DWORD dwExOptions = 0;
		if (m_pStyle->GetIncludeAllowEnter() && m_pStyle->GetAllowEnter())
		{
			dwExOptions = ECO_WANTRETURN;
		}

		// auto size
		m_bBottomless = m_pStyle->GetIncludeAutoSize() && m_pStyle->GetAutoSize();

		// Event mask and options
		CRichEditCtrl::SetEventMask(m_dwEventMask);
		SetOptions(ECOOP_SET, m_dwOptions | dwExOptions);

		// read only
		SetReadOnly(IsReadOnly());

		// show window
		SetActive(TRUE);

		// make sure that the active control has the focus
		if (GetFocus() == GridWnd())
		{
			Grid()->SetIgnoreFocus(TRUE);
			SetFocus();
			Grid()->SetIgnoreFocus(FALSE);
		}

#if _MFC_VER < 0x0420
		// Make caret visible
		if (GXGetAppData()->bWin31)
		{
			// special handling for Win32s
			Send32s(EM_SCROLL, SB_PAGEUP, 0);
			Send32s(EM_SCROLLCARET, 0, 0);
		}
		else
#endif
		{
			SendMessage(EM_SCROLL, SB_PAGEUP, 0);
			SendMessage(EM_SCROLLCARET, 0, 0);
		}

		// limit text
		long nLimitChars = m_pStyle->GetIncludeMaxLength()
			? (long) m_pStyle->GetMaxLength()
			: 0;
		LimitText(nLimitChars);

		ShowWindow(SW_SHOW);

		if (nRow > Grid()->GetFrozenRows() && (Grid()->GetTopRow() > nRow
			|| nCol > Grid()->GetFrozenCols() && Grid()->GetLeftCol() > nCol))
		// Ensure that the window cannot draw outside the clipping area!
		{
			CRect rectClip;
			if (pDC->GetClipBox(&rectClip) != ERROR)
			{
				CRect r = rect & Grid()->GetGridRect();
				GridWnd()->ClientToScreen(&r);
				ScreenToClient(&r);
				GridWnd()->ClientToScreen(&rectClip);
				ScreenToClient(&rectClip);
				ValidateRect(r);
				InvalidateRect(rectClip);
				HideCaret();
			}
		}

		UpdateWindow();

		// child Controls: spin-buttons, hotspot, combobox btn, ...
		CGXControl::Draw(pDC, rect, nRow, nCol, *m_pStyle, pStandardStyle);

		ExcludeClipRect(rectText);

		// Reenable OnRequestResize processing
		s_bLockRequestResize = FALSE;
	}
	else    // Draw inactive cells
	{
		// Draw the RTF with the FormatRange API

		// Background + Frame
		DrawBackground(pDC, rect, style);

		// RTF window positon
		CRect rectItem = rect;
		CRect rectText = GetCellRect(nRow, nCol, rect);
		if (rect.right <= rect.left || rect.Width() <= 1 || rect.Height() <= 1)
			return;

		// Color
		COLORREF rgbText = style.GetTextColor();
		COLORREF rgbCell = style.GetInteriorRef().GetColor();
		if (style.GetInteriorRef().GetStyle() == BS_NULL)
		{
			rgbCell = style.GetInteriorRef().GetBkColor();
		}
		if (Grid()->GetParam()->GetProperties()->GetBlackWhite())
		{
			rgbText = RGB(0,0,0);
			rgbCell = RGB(255,255,255);
		}
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetBkColor(rgbCell);
		pDC->SetTextColor(rgbText);

		m_DrawRTFWnd.SetBackgroundColor(FALSE, rgbCell);

		// Get the formatted RTF string from the style object
		CString sRTFString = style.GetValueRef();

		if (sRTFString.IsEmpty())
			return;

		// if possible, reuse RTF string
		if (sRTFString != m_sLastDrawRTFText)
		{
			SetRichText(&m_DrawRTFWnd, sRTFString);
			m_sLastDrawRTFText = sRTFString;
		}

		if (m_DrawRTFWnd.GetWindowTextLength() == 0)
			return;

		// Initialize control with cell data and fill
		// FORMATRANGE structure
		FORMATRANGE fr;

		int nlogx = GXGetFontState()->m_nLogPixelsX;
		int nlogy = GXGetFontState()->m_nLogPixelsY;

		if (!pDC->IsPrinting() // display
			|| pDC->IsPrinting() && pDC->m_hAttribDC != pDC->GetSafeHdc()) // print preview
		{
			nlogx = ::GetDeviceCaps(pDC->GetSafeHdc(), LOGPIXELSX);
			nlogy = ::GetDeviceCaps(pDC->GetSafeHdc(), LOGPIXELSY);
		}

		// Adjust DC only when printing. The RichEdit control
		// needs the MM_TEXT mode. (m_hAttribDC and m_hDC
		// will be different for print preview)

		int nMapMode = 0;
		CSize sizeWindowExt, sizeViewportExt;

		// Save device context info and switch to MM_TEXT
		if (pDC->IsPrinting() && pDC->m_hAttribDC == pDC->GetSafeHdc())
		{
			sizeWindowExt = pDC->GetWindowExt();
			sizeViewportExt = pDC->GetViewportExt();

			// Adjust printer DC
			nMapMode = pDC->SetMapMode(MM_ANISOTROPIC);

			int nlogx = pDC->GetDeviceCaps(LOGPIXELSX);
			int nlogy = pDC->GetDeviceCaps(LOGPIXELSY);
			pDC->SetWindowExt(nlogx, nlogy);
			pDC->SetViewportExt(sizeViewportExt);
		}

		// Assign the display context
		fr.hdcTarget = pDC->m_hAttribDC;
		fr.hdc = pDC->GetSafeHdc();

		// Set up the page (whole grid area in TWIPS).
		CRect rcPage = Grid()->GetGridRect();
		rcPage.left *= 1440 / nlogx;
		rcPage.top *= 1440 / nlogy;
		rcPage.right *= 1440 / nlogx;
		rcPage.bottom *= 1440 / nlogy;
		fr.rcPage = rcPage;

		// Add additional row to the cell so that the last row of
		// text will be clipped. If we don't add extra space to the
		// cell, the last row of text would only be drawn if it
		// is completely visible.

		int dyHeight = Grid()->GetFontHeight();

		// Convert cell rectangle to TWIPS
		CRect rcText(rectText.left * 1440 / nlogx,  rectText.top * 1440 / nlogy,
			rectText.right * 1440 / nlogx,  (rectText.bottom + dyHeight) * 1440 / nlogy);
		fr.rc = rcText;

		// Print as much text as can fit in the cell.
		CHARRANGE chrg = { 0, -1 };
		fr.chrg = chrg;

		// Now, draw the RTF cell
		m_DrawRTFWnd.FormatRange(NULL, FALSE); // required by RichEdit to clear out cache
		m_DrawRTFWnd.FormatRange(&fr, TRUE);
		m_DrawRTFWnd.FormatRange(NULL, FALSE); // required by RichEdit to clear out cache

		// Reset device context
		if (pDC->IsPrinting() && pDC->m_hAttribDC == pDC->GetSafeHdc())
		{
			pDC->SetMapMode(nMapMode);
			pDC->SetWindowExt(sizeWindowExt);
			pDC->SetViewportExt(sizeViewportExt);
		}
	

	// load the standard font becuase the FormatRange()
 	// function changes the font in the DC
 		LoadFont(pDC, *pStandardStyle, NULL);
	}
}

void CGXRichEditCtrl::Hide()
{
	// Hides the window without changing the m_bIsActive flag
	if (m_hWnd && IsWindowVisible())
	{
		Grid()->SetIgnoreFocus(TRUE);
		ShowWindow(SW_HIDE);
		Grid()->SetIgnoreFocus(FALSE);
	}
}

// Mouse hit
BOOL CGXRichEditCtrl::LButtonUp(UINT nFlags, CPoint pt, UINT nHitState)
{
	// Sets the caret position
	if (!(nHitState & GX_SELECT) && (Grid()->GetParam()->GetActivateCellFlags() &
		(GX_CAFOCUS_CLICKINTEXT|GX_CAFOCUS_CLICKONCELL|GX_CAFOCUS_SETCURRENT)) > 0)
	{
		// check OnStartEditing
		if(!IsActive() && !OnStartEditing())
			return FALSE;

		// Set control active
		SetActive(TRUE);
		Refresh();

		// check child buttons (and CGXGridCore::OnLButtonClickedRowCol)
		if (!CGXControl::LButtonUp(nFlags, pt, nHitState))
		{
			// Make window visible
			SetSel(0,0);
			GridWnd()->UpdateWindow();

			CRect rect = GetCellRect(m_nRow, m_nCol);

			pt -= rect.TopLeft();

			// Generate a Mouse Down/Up pair so that caret
			// is positioned under the mouse cursor

			SendMessage(WM_LBUTTONDOWN, nFlags, MAKELONG(pt.x, pt.y));
			SendMessage(WM_LBUTTONUP, nFlags, MAKELONG(pt.x, pt.y));
		}

		return TRUE;
	}

	return CGXControl::LButtonUp(nFlags, pt, nHitState);
}

BOOL CGXRichEditCtrl::LButtonDblClk(UINT nFlags, CPoint pt)
{
	// Sets the caret position
	if (!IsActive() && (Grid()->GetParam()->GetActivateCellFlags() &
		GX_CAFOCUS_DBLCLICKONCELL) > 0)
	{
		if(OnStartEditing())
		{
			// Set control active
			SetActive(TRUE);
			Refresh();
		}
		else
		{
			return CGXControl::LButtonDblClk(nFlags, pt);
		}

		// check child buttons (and CGXGridCore::LButtonDblClkRowCol)
		if (!CGXControl::LButtonDblClk(nFlags, pt))
		{
			// Make window visible
			SetSel(0,0);
			GridWnd()->UpdateWindow();

			CRect rect = GetCellRect(m_nRow, m_nCol);

			pt -= rect.TopLeft();

			// Generate a Mouse Down/Up pair so that caret
			// is positioned under the mouse cursor

			SendMessage(WM_LBUTTONDOWN, nFlags, MAKELONG(pt.x, pt.y));
			SendMessage(WM_LBUTTONUP, nFlags, MAKELONG(pt.x, pt.y));
		}

		return TRUE;
	}

	return CGXControl::LButtonDblClk(nFlags, pt);
}

// Find and Replace

BOOL CGXRichEditCtrl::FindText(const GX_FR_STATE& find, ROWCOL nRow, ROWCOL nCol, BOOL bCurrentPos, BOOL bSetCell)
{
	BOOL bFound = FALSE;
	FINDTEXTEX findText;
	CHARRANGE cr = { 0, -1 };
	memset(&findText, 0, sizeof(findText));
	findText.chrg = cr;

#if !defined(_UNICODE) || (_MFC_VER >= 0x0420 && !(_RICHEDIT_VER == 0x0100))
	findText.lpstrText = (LPTSTR) (LPCTSTR) find.strFind;
#else
	findText.lpstrText = find.lpszMultiByteFindString;

	ASSERT(findText.lpstrText);
	if (findText.lpstrText == NULL)
		return FALSE;
#endif

	DWORD dwFlags = 0;
	if (find.bCase)
	{
		dwFlags |= FR_MATCHCASE;
	}

	// if the active cell contains the text, mark it and return TRUE
	// if not, do a find and return FALSE
	if (nRow == m_nRow && nCol == m_nCol && IsActive())
	{
		GetSel(cr);
		if (!bCurrentPos && cr.cpMax != cr.cpMin)
			cr.cpMin++;
		cr.cpMax = GetWindowTextLength();
		findText.chrg = cr;

		long nChar = CRichEditCtrl::FindText(dwFlags, &findText);

		if (nChar != -1)
		{
			if (bSetCell)
			{
				// mark the found text
				Grid()->ScrollCellInView(nRow, nCol);
				SetSel(findText.chrgText);
			}

			bFound = TRUE;
		}
	}
	else
	{
		// Load the RTF string from the style object and
		CString sRTFString;
		if (find.m_pStyle)
		{
			sRTFString = find.m_pStyle->GetValueRef();
		}
		else
		{
			// request a style object
			CGXStyle* pStyle = Grid()->CreateStyle();

			Grid()->ComposeStyleRowCol(nRow, nCol, pStyle);

			sRTFString = pStyle->GetValueRef();;

			// free style object
			Grid()->RecycleStyle(pStyle);
		}

		// Load RTF data into m_StoreRTFWnd
		if (sRTFString != m_sLastStoreRTFText)
		{
			SetRichText(&m_StoreRTFWnd, sRTFString);
			m_sLastStoreRTFText = sRTFString;
		}

		cr.cpMax = m_StoreRTFWnd.GetWindowTextLength();
		findText.chrg = cr;
		long nChar = m_StoreRTFWnd.FindText(dwFlags, &findText);

		if (nChar != -1)
		{
			if (bSetCell)
			{
				// mark the found text
				Grid()->ScrollCellInView(nRow, nCol);
				Grid()->SetCurrentCell(nRow, nCol, GX_SMART|GX_NOSETFOCUS);
				SetActive(TRUE);
				SetSel(findText.chrgText);
				Refresh();
			}

			bFound = TRUE;
		}
	}

	return bFound;
}

void CGXRichEditCtrl::ReplaceSel(LPCTSTR pszReplaceText)
{
	if (IsActive())
	{
		// Replace the selected text
		CRichEditCtrl::ReplaceSel(pszReplaceText);
		SetModify(TRUE);
		OnModifyCell();
	}
}

BOOL CGXRichEditCtrl::ReplaceAll(const GX_FR_STATE& find, ROWCOL nRow, ROWCOL nCol)
{
	BOOL bFound = FALSE;
	FINDTEXTEX findText;
	CHARRANGE cr = { 0, -1 };
	memset(&findText, 0, sizeof(findText));
	findText.chrg = cr;

#if !defined(_UNICODE) || (_MFC_VER >= 0x0420 && !(_RICHEDIT_VER == 0x0100))
	findText.lpstrText = (LPTSTR) (LPCTSTR) find.strFind;
#else
	findText.lpstrText = find.lpszMultiByteFindString;

	ASSERT(findText.lpstrText);
	if (findText.lpstrText == NULL)
		return FALSE;
#endif

	DWORD dwFlags = 0;
	if (find.bCase)
		dwFlags |= FR_MATCHCASE;

	CString s, sTemp;

	// if the active cell contains the text, mark it and return TRUE
	// if not, do a find and return FALSE
	if (nRow == m_nRow && nCol == m_nCol && IsActive())
	{
		GetSel(cr);
		cr.cpMax = GetWindowTextLength();
		findText.chrg = cr;

		long nChar = 0;

		while ((nChar = CRichEditCtrl::FindText(dwFlags, &findText)) != -1)
		{
			// mark the found text
			SetSel(findText.chrgText);

			ReplaceSel(find.strReplace);

			bFound = TRUE;

			cr.cpMin += find.strReplace.GetLength();
			cr.cpMax = GetWindowTextLength();
			findText.chrg = cr;
		}

		Store();
	}
	else
	{
		CString sRTFString;

		// Load the RTF string from the style object
		if (find.m_pStyle)
		{
			sRTFString = find.m_pStyle->GetValueRef();
		}
		else
		{
			// request a style object
			CGXStyle* pStyle = Grid()->CreateStyle();

			Grid()->ComposeStyleRowCol(nRow, nCol, pStyle);

			sRTFString = pStyle->GetValueRef();

			// free style object
			Grid()->RecycleStyle(pStyle);
		}

		// Load RTF data into m_StoreRTFWnd
		SetRichText(&m_StoreRTFWnd, sRTFString);

		findText.chrg.cpMin = 0;
		findText.chrg.cpMax = m_StoreRTFWnd.GetWindowTextLength();

		long nChar = 0;

		while ((nChar = m_StoreRTFWnd.FindText(dwFlags, &findText)) != -1)
		{
			// mark the found text
			m_StoreRTFWnd.SetSel(findText.chrgText);

			m_StoreRTFWnd.ReplaceSel(find.strReplace);

			bFound = TRUE;

			findText.chrg.cpMin = findText.chrgText.cpMin + find.strReplace.GetLength();
			findText.chrg.cpMax = m_StoreRTFWnd.GetWindowTextLength();
		}

		if (bFound)
		{
			// Using m_sLastStoreRTFText is a small optimization so that
			// the CGXRichEditCtrl::StoreStyle method does not need to
			// call SetRichText again.
			GetRichText(&m_StoreRTFWnd, m_sLastStoreRTFText);
			Grid()->SetValueRange(CGXRange(nRow, nCol), m_sLastStoreRTFText, gxOverride);
		}
		else
			m_sLastStoreRTFText = sRTFString;
	}

	return bFound;
}

// OnRequestResize
//
// This is the handler for the WM_NOTIFY message EN_REQUESTRESIZE.
// When the autosize flag is specified for the cell, this method
// makes the cell behave bottomless. This means it will enlarge
// its row height while the user enters text in the cell.
//
// Known limitation with RICHEDIT control:
// OnRequestResize is only called when the height of the cell is
// too small. It cannot be used for adjusting the cell width.
//
// Additional features:
// OnRequestResize can handle automatic shrinking of cells. It
// supports different modes specified with the m_nShrinkMode
// attribute.

BOOL CGXRichEditCtrl::OnRequestResize(NMHDR* pNotifyStruct, LRESULT* /*result*/)
{
	if (s_bLockRequestResize)
	{
		return FALSE;
	}

	// Is notficiation sent because of user event?
	if (IsInit()
		&& Grid()->IsCurrentCell(m_nRow, m_nCol)
		&& m_bBottomless
		&& IsActive())
	{
		CGXRange range;
		if (!Grid()->GetCoveredCellsRowCol(m_nRow, m_nCol, range))
		{
			range.SetCells(m_nRow, m_nCol);
		}

		// Disable recursive OnRequestResize processing
		s_bLockRequestResize = TRUE;

		CRect rectGrid = Grid()->GetGridRect();

		REQRESIZE FAR* lpReSize = (REQRESIZE FAR *) pNotifyStruct;
		CRect rc = lpReSize->rc;
		CSize size = AddBorders(CSize(rc.Width(), rc.Height()), *m_pStyle);

		int nHeight = Grid()->GetRowHeight(range.bottom);
		size.cy++;  // Add one pixel
		if (range.bottom > range.top)
		{
			size.cy -= Grid()->CalcSumOfRowHeights(range.top, range.bottom-1);
		}

		// enlarging cells
		if (size.cy > nHeight)
		{
			int nMaxHeight;
			ROWCOL nfr = Grid()->GetFrozenRows();

			if (range.bottom == 0)
			{
				nMaxHeight = max(0, rectGrid.Height() - 1);
			}else if (range.bottom <= nfr)
			{
				nMaxHeight = max(0, rectGrid.Height() - Grid()->CalcSumOfRowHeights(0, range.bottom-1) - 1);
			}else
			{
				nMaxHeight = max(0, rectGrid.Height() - Grid()->CalcSumOfRowHeights(0, nfr) - 1);
			}

			GridWnd()->UpdateWindow();
			if (nMaxHeight > nHeight)
			{
				Grid()->SetRowHeight(range.bottom, range.bottom, min(size.cy, nMaxHeight));
				Grid()->ScrollCellInView(m_nRow, m_nCol);
			}
		}
		// shrinking cells
		else if (max(size.cy, m_nMinShrinkSize) < nHeight && m_nShrinkMode != gxNoShrink)
		{
			Grid()->SetRowHeight(range.bottom, range.bottom, max(size.cy, m_nMinShrinkSize));
		}

		// Reenable OnRequestResize processing
		s_bLockRequestResize = FALSE;
		return TRUE;
	}
	return FALSE;
}

// CalcSize
//
// CalcSize determines the optimal height for the cell.
//
// Known limitation:
// If CalcSize is called to determine the optimal cell width (bVert = FALSE)
// the function will have no effect. That means the cell will not be resized.

CSize CGXRichEditCtrl::CalcSize(CDC* pDC, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* /*pStandardStyle*/, BOOL /*bVert*/)
{
	// Determine current size of cell (and take care if cell
	// is a covered, merged or float cell) and subtract space
	// needed for borders, 3d-Frame or grid-lines with GetCellRect
	//
	// Don't call CalcRectFromRowCol because the calculation
	// of CalcRectFromRowCol is based on the current top
	// row and last visible row. If the cell is not visible,
	// the CRect would then be empty and that's not what we
	// want!

	CGXRange area = CGXRange(nRow, nCol);
	Grid()->GetCellRangeRowCol(nRow, nCol, area);
	CRect rc(0, 0, Grid()->CalcSumOfColWidths(area.left, area.right), Grid()->CalcSumOfRowHeights(area.top, area.bottom));
	rc = GetCellRect(nRow, nCol, rc, &style);
	CSize size(rc.Width(), rc.Height());

	// Disbale default OnRequestResize processing
	s_bLockRequestResize = FALSE;

	// RTF window positon (outside visible area)
	m_ResizeRTFWnd.MoveWindow(rc + CPoint(30000, 30000), FALSE);

	// Support for WYSIWYG
	if (pDC->m_hAttribDC != pDC->GetSafeHdc())
	{	
		m_ResizeRTFWnd.SetTargetDevice(pDC->m_hAttribDC, rc.Width() * 1440 / GXGetFontState()->m_nLogPixelsY);
	}else
	{
		m_ResizeRTFWnd.SetTargetDevice(NULL, 0);
	}

	// Force sending of OnRequestResize notification
	m_ResizeRTFWnd.SetEventMask(ENM_REQUESTRESIZE);

	// Get formatted RTF string
	CString sRTFString = style.GetValueRef();

	// If possible, reuse RTF string
	if (sRTFString != m_sLastResizeRTFText)
	{
		SetRichText(&m_ResizeRTFWnd, sRTFString);
		m_sLastResizeRTFText = sRTFString;
	}

	// Reenable OnRequestResize processing
	s_bLockRequestResize = FALSE;

	// Now comes the cool thing in this function
	m_bCalcSize = TRUE;
	m_rcReSize = rc;

	// a) temporary show the window (will not be visible to user)
	m_ResizeRTFWnd.ShowWindow(SW_SHOW);

	// b) force OnRequestResize notification
	m_ResizeRTFWnd.RequestResize();

	// c) hide the window again
	m_ResizeRTFWnd.ShowWindow(SW_HIDE);

	m_bCalcSize = FALSE;

	rc = m_rcReSize;    // Result from OnRequestResizeChild
	size.cx = rc.Width();
	size.cy = rc.Height();
	size.cy++;  // Add one pixel

	return AddBorders(size, style);
}

// OnChildRequestResize
//
// CalcSize forces this function to be called. Before doing
// this, it sets the attribute m_bCalcSize = TRUE.
//

BOOL CGXRichEditCtrl::OnChildRequestResize(UINT /*id*/, NMHDR* pNotifyStruct, LRESULT* /*result*/)
{
	if (s_bLockRequestResize)
		return FALSE;

	// has notficiation been forced from CalcSize?
	if (m_bCalcSize)
	{
		REQRESIZE FAR* lpReSize = (REQRESIZE FAR *) pNotifyStruct;
		m_rcReSize = lpReSize->rc;
		return TRUE;
	}

	return FALSE;
}

// Copy
//
// Copy will only copy data to clipboard if cell is active (has the focus)
// If you also want to support Copy for inactive controls, or if you
// want to support additional clipboard formats, you should
// override these methods.

BOOL CGXRichEditCtrl::CanCopy()
{
	return IsInit();
}

// Copy()
//
// Called when user calls Edit|Copy and the grid
// has a current cell but no range is selected.
//
// Copy() performs the followin g job:
// a) Call CRichEditCtrl::Copy() which will copy Selected Text as formatted
//    in the cell as CF_TEXT and also CF_RTF
// b) Only if cell is inactive copy the CGXStyle info for the cell

BOOL CGXRichEditCtrl::Copy()
{
	if (IsInit() && Grid()->IsCurrentCell(m_nRow, m_nCol))
		CRichEditCtrl::Copy();

	return CGXControl::Copy();
}

// Cut
//
// Cut will only cut  data to clipboard if cell is active (has the focus)
// If you also want to support Cut for inactive controls, or if you
// want to support additional clipboard formats, you should
// override these methods.

BOOL CGXRichEditCtrl::CanCut()
{
	return CGXControl::CanCut();
}

BOOL CGXRichEditCtrl::Cut()
{
	// Copy data (don't cut them now)
	CRichEditCtrl::Copy();

	// .. now cut data
	return CGXControl::Cut();
}

// Paste
//
// Paste will only paste data from clipboard if cell is active (has the focus)
// If you also want to support Paste for inactive controls, or if you
// want to support additional clipboard formats, you should
// override these methods.

#ifndef _WINDU_SOURCE
#if !defined(_UNICODE) || _MFC_VER >= 0x0420
UINT s_cfRTF = RegisterClipboardFormat(CF_RTF);
#else
UINT s_cfRTF = RegisterClipboardFormat(_T(CF_RTF));
#endif
#else
UINT s_cfRTF = 0xffff;
#endif


BOOL CGXRichEditCtrl::CanPaste()
{
#ifdef _WINDU_SOURCE
	if( s_cfRTF == 0xffff)
		s_cfRTF = RegisterClipboardFormat(CF_RTF);
#endif
	if (IsInit())
	{
		NeedStyle();
		if (m_pStyle->GetIncludeReadOnly() && m_pStyle->GetReadOnly())
			return FALSE;

		if (IsClipboardFormatAvailable(s_cfRTF))
			return TRUE;
	}

	return CGXControl::CanPaste();
}

BOOL CGXRichEditCtrl::Paste()
{
#ifdef _WINDU_SOURCE
	if( s_cfRTF == 0xffff)
		s_cfRTF = RegisterClipboardFormat(CF_RTF);
#endif

	if (IsInit())
	{
		// Make sure clipboard is not opened
		if (CWnd::GetOpenClipboardWindow() == NULL)
		{
			GridWnd()->OpenClipboard();
			BOOL bCanPaste = ::GetClipboardData(s_cfRTF) != 0;
			CloseClipboard();

			if (bCanPaste)
			{
				// insert text into active current cell
				if (!IsActive())
				{
					SetActive(TRUE);
					SetSel(0, -1);
				}

				s_bLockRequestResize = TRUE;

				if (bCanPaste)
					CRichEditCtrl::Paste();

				s_bLockRequestResize = FALSE;

				Refresh();
				GridWnd()->UpdateWindow();
				RequestResize();

				return TRUE;
			}
		}
	}

	return CGXControl::Paste();
}

// Keyboard

// called from CGXGridCore when current cell is incative
// (does not have the focus) and before CGXGridCore
// interpretes the key.

BOOL CGXRichEditCtrl::OnGridKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	BOOL bCtl = GetKeyState(VK_CONTROL) & 0x8000;
	BOOL bShift = GetKeyState(VK_SHIFT) & 0x8000;

	BOOL bProcessed = FALSE;

	s_bLockRequestResize = FALSE;

	switch (nChar)
	{
	case VK_DELETE:
		if (Grid()->GetParam()->GetRangeList()->IsEmpty() // no ranges of cells selected
			&& !bCtl                // no CTRL-Key pressed
			&& !bShift              // no SHIFT pressed
			&& !IsReadOnly()        // cell is not readonly
			&& OnDeleteCell()       // OnDeleteCell notification returns TRUE
			&& OnStartEditing())    // OnStartEditing notification returns TRUE
		{
			SetActive(TRUE);

			// Delete text
			SetCurrentText(_T(""));
			SetModify(TRUE);
			OnModifyCell();

			bProcessed = TRUE;
		}
		break;

	case VK_END:
		if (!bCtl && OnStartEditing())
		{
			if (!IsInit())
				Init(m_nRow, m_nCol);
			SetActive(TRUE);

			int nLen = GetWindowTextLength();

			// position caret
			SetSel(nLen, nLen);

			bProcessed = TRUE;
		}
		break;

	case VK_HOME:
		if (!bCtl && OnStartEditing())
		{
			if (!IsInit())
				Init(m_nRow, m_nCol);
			SetActive(TRUE);

			// position caret
			SetSel(0, 0);

			bProcessed = TRUE;
		}
		break;
	}

	if (bProcessed)
	{
		if (!Grid()->ScrollCellInView(m_nRow, m_nCol))
			Refresh();

		return TRUE;
	}

	return CGXControl::OnGridKeyDown(nChar, nRepCnt, nFlags);

}

BOOL CGXRichEditCtrl::OnGridChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// pass valid characters as string to OnGridDoubleByteChar
	if (nChar >= 0x020 && nChar != 0x7f)
		return OnGridDoubleByteChar((CString) (TCHAR) nChar, nRepCnt, nFlags);

	// default processing
	return CGXControl::OnGridChar(nChar, nRepCnt, nFlags);
}

BOOL CGXRichEditCtrl::OnGridDoubleByteChar(const CString& sChar, UINT /*nRepCnt*/, UINT /*nFlags*/)
{
	if (IsReadOnly())
		return FALSE;

	s_bLockRequestResize = FALSE;

	if (IsActive())
	{
		int nLen = GetWindowTextLength();
		SetSel(nLen, nLen);

		CString s;
		GetWindowText(s);
		s += sChar;

		long nLimitChars = m_pStyle->GetIncludeMaxLength()
			? (long) m_pStyle->GetMaxLength()
			: 0;

		if ((nLimitChars == 0 || nLen + sChar.GetLength() <= nLimitChars)
			&& ValidateString(s))
		{
			ReplaceSel(sChar);
		}

		return TRUE;
	}
	else
	{
		// discard key if cell is read only
		if (IsReadOnly() || !ValidateString(sChar) || !OnStartEditing())
			return FALSE;

		SetActive(TRUE);

		SetCurrentText(sChar);
		SetSel(sChar.GetLength(), sChar.GetLength());
		Refresh();

		return TRUE;
	}
}

void CGXRichEditCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT flags)
{
	ASSERT(IsActive());

	s_bLockRequestResize = FALSE;

	BOOL bProcessed = FALSE;
	BOOL bCallDefault = TRUE;

	// TRACE("CGXEditControl::OnKeyDown nChar = %d\n", nChar);

	BOOL bCtl = GetKeyState(VK_CONTROL) & 0x8000;
	BOOL bShift = GetKeyState(VK_SHIFT) & 0x8000;

	Grid()->ScrollCellInView(m_nRow, m_nCol);

	// window text and caret position
	CString s;
	long ns, nr;

	GetWindowText(s);
	GetSel(ns, nr);

	switch (nChar)
	{
	case VK_RIGHT:
		// process right arrow if not at end of string
		bCallDefault = bCtl || nr < (int) s.GetLength();
		break;

	case VK_LEFT:
		// process left arrow if not at start of string
		bCallDefault = bCtl || ns > 0;
		break;

	case VK_DOWN:
		// process down arrow if not at last line
		bCallDefault = bCtl || LineFromChar(nr)+1 < GetLineCount();
		break;

	case VK_UP:
		// process up arrow if not at first line
		bCallDefault = bCtl || LineFromChar(ns) > 0;
		break;

	case VK_RETURN:
		// does edit control want to handle the RETURN key itsself?
		bCallDefault = bCtl || GetStyle() & ES_WANTRETURN;
		break;

	case VK_F1:
	case VK_F2:
	case VK_F3:
	case VK_F4:
	case VK_F5:
	case VK_F6:
	case VK_F7:
	case VK_F8:
	case VK_F9:
	case VK_F10:
	case VK_F11:
	case VK_F12:
	case VK_F13:
	case VK_F14:
	case VK_F15:
	case VK_F16:
	case VK_F17:
	case VK_F18:
	case VK_F19:
	case VK_F20:
	case VK_F21:
	case VK_F22:
	case VK_F23:
	case VK_F24:
	case VK_TAB:
	case VK_NEXT:
	case VK_PRIOR:
	case VK_ESCAPE:
		// let grid handle escape key
		bCallDefault = FALSE;
		break;

	case VK_HOME:
	case VK_END:
	case VK_SHIFT:
	default:
		// let Rich Edit handle insert key
		// let Rich Edit handle delete and Insert key
		// let Rich Edit handle all other keys
		bCallDefault = TRUE;
		break;

	case VK_INSERT:
		{
			if (bShift)
			{
				Paste();
				bCallDefault = FALSE;
				bProcessed = TRUE;
			}
			else if (bCtl && ns != nr)
			{
				Copy();
				bCallDefault = FALSE;
				bProcessed = TRUE;
			}
			break;
		}

	case VK_DELETE:
		{
			if (bShift && ns != nr)
			{
				// if we have a multiple selection, handle it differently
				Cut();
				bCallDefault = FALSE;
				bProcessed = TRUE;
			}
			break;
		}

	case 'V':
	case 'C':
	case 'X':
		if (bCtl)
			bCallDefault = FALSE;
	}

	if (bCallDefault)
	{
		CRichEditCtrl::OnKeyDown(nChar, nRepCnt, flags);
		bProcessed = TRUE;
	}

	if (!bProcessed)
		Grid()->ProcessKeys(this, WM_KEYDOWN, nChar, nRepCnt, flags);
}

void CGXRichEditCtrl::OnChar(UINT nChar, UINT nRepCnt, UINT flags)
{
	if (!IsInit() || !IsActive() || (GetStyle() & ES_READONLY) || nChar == 8 && nRepCnt == 0)
		return;

	BOOL bCallDefault = TRUE;

	// TRACE("CGXEditControl::OnChar nChar = %d\n", nChar);

	BOOL bCtl = GetKeyState(VK_CONTROL) & 0x8000;

	long ns, ne;
	GetSel(ns, ne);

	Grid()->ScrollCellInView(m_nRow, m_nCol);

	// Pass all CTRL keys to the grid
	if (bCtl)
	{
		switch (nChar)
		{
		case 24:    // CTRL+X
			Cut();
			return;

		case 3:     // CTRL+C
			Copy();
			return;

		case 22:    // CTRL+V
			Paste();
			return;
		}

		// Pass all other CTRL keys to the grid
	}
	else
	{
		BOOL bChar = FALSE;

		// support for DBCS characters
		CString sChar;
		if (GXGetDoubleByteChar((TCHAR) nChar, sChar, m_bDoubleByteChar, m_nDoubleByteLeadChar))
		{
			if (sChar.IsEmpty())
				bCallDefault = TRUE;    // leading byte
			else
				// double byte character in sChar
				bChar = TRUE;
		}
		else if (nChar >= 0x020) // this is a normal character
		{
			sChar = (TCHAR) nChar;
			bChar = TRUE;
		}

		// Is it an alphanumeric or double byte character?
		if (bChar)
		{
			// validate input
			CString sEdit;
			GetWindowText(sEdit);

			if (ne == -1)
			{
				sEdit = sChar;
			}else if (ne > ns && ne+1 < sEdit.GetLength())
			{
				sEdit = sEdit.Left(ns) + sChar + sEdit.Mid(ne+1);
			// Modified in OG7.01 to fix the ASSERT problem in VC6 in CString::Mid
			}else if (ne == ns)
			{
				sEdit = sEdit.Left(ns) + sChar + sEdit.Mid(ne);
			}else
			{
				sEdit = sEdit.Left(ns) + sChar;
			}

			if (!ValidateString(sEdit))
			{
				OnInvalidKeyPressed(sChar);
			}

			bCallDefault = TRUE;
		}
	}

	if (
		GetStyle() & ES_WANTRETURN && nChar == 13
		|| nChar == 10)
	{
		// insert a cr/lf
		bCallDefault = TRUE;
	}

	if (bCallDefault)
	{
		CRichEditCtrl::OnChar(nChar, nRepCnt, flags);
		Grid()->ProcessKeys(this, WM_CHAR, nChar, nRepCnt, flags);
	}
}

void CGXRichEditCtrl::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!Grid()->ProcessKeys(this, WM_KEYUP, nChar, nRepCnt, nFlags))
		CRichEditCtrl::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CGXRichEditCtrl::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!Grid()->ProcessKeys(this, WM_SYSKEYDOWN, nChar, nRepCnt, nFlags))
		CRichEditCtrl::OnSysKeyDown(nChar, nRepCnt, nFlags);
}

void CGXRichEditCtrl::OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!Grid()->ProcessKeys(this, WM_SYSCHAR, nChar, nRepCnt, nFlags))
		CRichEditCtrl::OnSysChar(nChar, nRepCnt, nFlags);
}

void CGXRichEditCtrl::OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!Grid()->ProcessKeys(this, WM_SYSKEYUP, nChar, nRepCnt, nFlags))
		CRichEditCtrl::OnSysKeyUp(nChar, nRepCnt, nFlags);
}

void CGXRichEditCtrl::OnDeadChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!Grid()->ProcessKeys(this, WM_DEADCHAR, nChar, nRepCnt, nFlags))
		CRichEditCtrl::OnDeadChar(nChar, nRepCnt, nFlags);
}

void CGXRichEditCtrl::OnSysDeadChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!Grid()->ProcessKeys(this, WM_SYSDEADCHAR, nChar, nRepCnt, nFlags))
		CRichEditCtrl::OnSysDeadChar(nChar, nRepCnt, nFlags);
}

// Other window messages

BOOL CGXRichEditCtrl::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	GetClientRect(rect);

	// Erase Background
	GXPatB(pDC, rect, RGB(255,255,255));
	if (m_pStyle)
		pDC->FillRect(rect, Grid()->LookupOrCreateBrush(m_pStyle->GetInteriorRef()));

	return TRUE;
}

BOOL CGXRichEditCtrl::OnCommand(WPARAM wParam, LPARAM lParam)
{
#if _MFC_VER < 0x0300
	UINT nNotification = HIWORD(lParam);
	HWND hCtl = (HWND) LOWORD(lParam);
#else
	UINT nNotification = HIWORD(wParam);
	HWND hCtl = (HWND) lParam;
#endif

	if (hCtl == m_hWnd && IsActive())
	{
		if (nNotification == EN_CHANGE)
			OnModifyCell();
	}

	return CGXControl::OnCommand(wParam, lParam);
}


void CGXRichEditCtrl::OnKillFocus(CWnd* pNewWnd)
{
	CRichEditCtrl::OnKillFocus(pNewWnd);
	CGXControl::OnKillFocus(pNewWnd);
}

UINT CGXRichEditCtrl::OnGetDlgCode()
{
	return CRichEditCtrl::OnGetDlgCode() | DLGC_WANTTAB | DLGC_WANTARROWS | DLGC_WANTCHARS;
}

void CGXRichEditCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	s_bLockRequestResize = TRUE; // avoids recursion when text is dragged inside the RichEdit

	CRichEditCtrl::OnLButtonDown(nFlags, point);
}

void CGXRichEditCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
	CRichEditCtrl::OnLButtonUp(nFlags, point);
}

// Fix some incompatibilities with MFC 4.2 and MFC 4.2b UNICODE builds
// [VC7] Complains about redefining these functions, so excluded.
#if defined(_UNICODE) && (_MFC_VER >= 0x0420 && _MFC_VER < 0x0700)

  #if !defined(_RICHEDIT_VER)   // MFC 4.2

void CGXRichEditCtrl::ConvertStyleToRTF(PARAFORMAT&, CHARFORMATA&, const CGXStyle*)
{
}

void CGXRichEditCtrl::ConvertRTFToStyle(const PARAFORMAT&, const CHARFORMATA&, CGXStyle*)
{
}

  #else // MFC 4.2b

void CGXRichEditCtrl::ConvertStyleToRTF(PARAFORMAT&, CHARFORMATW&, const CGXStyle*)
{
}

void CGXRichEditCtrl::ConvertRTFToStyle(const PARAFORMAT&, const CHARFORMATW&, CGXStyle*)
{
}

  #endif
#endif

#endif // _MFC_VER
