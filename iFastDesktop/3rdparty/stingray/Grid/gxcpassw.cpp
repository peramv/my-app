///////////////////////////////////////////////////////////////////////////////
// gxcpassw.cpp : implementation of CGXPasswordControl control
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

#ifdef _GXDLL
#undef AFXAPI_DATA
#define AFXAPI_DATA __based(__segname("_DATA"))
#endif

// Headers

#ifndef _GXCORE_H_
#include "grid\gxcore.h"
#endif

#ifndef _GXCTRLI_H_
#include "grid\gxctrli.h"
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXCPASSW")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

///////////////////////////////////////////////////////////////////
// CGXPasswordControl control

// You can register the control in the OnInitialUpdate() routine

//  CGXPasswordControl* pPwdControl = new CGXPasswordControl(this, GX_IDS_CTRL_PASSWORD);
//  pPwdControl->m_chPasswordChar = _T('@'); // use @ as password char
//  RegisterControl(GX_IDS_CTRL_PASSWORD, pPwdControl);
//  and later apply it to cells with
//  SetStyleRange(CGXRange(4,3,10,5),
//      CGXStyle()
//          .SetControl(GX_IDS_CTRL_PASSWORD)
//      );

GRID_IMPLEMENT_CONTROL(CGXPasswordControl, CGXEditControl)
IMPLEMENT_DYNAMIC(CGXPasswordControl, CGXEditControl)

CGXPasswordControl::CGXPasswordControl(CGXGridCore* pGrid, UINT nID)
	: CGXEditControl(pGrid, nID)
{
	// cell needs to be redrawn as soon as it becomes the current cell
	m_bRefreshOnSetCurrentCell = TRUE;
	m_bReplaceAsterisk = TRUE;

	// Because of the bug (Refer Q316306) the edit controls sometimes does not 
	// display password character properly in ansi. So restrict the black circle
	// assignment to unicode only.

#ifdef _UNICODE
	if (RWIsAppThemed() && RWIsThemeActive())
	{		
		m_chPasswordChar = TCHAR(9679);
	}
	else
	{
#endif

		m_chPasswordChar = _T('*');

#ifdef _UNICODE
	}
#endif

	// You may reset m_bReplaceAsterisk = FALSE for certain
	// operations like FindText or ResizeRowHeightsToFit, so
	// that the password text is used and not
	// password characters (e.g. asterisks, '*').
}

BEGIN_MESSAGE_MAP(CGXPasswordControl, CGXEditControl)
	//{{AFX_MSG_MAP(CGXPasswordControl)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// GetControlText
//
// Convert the value which is stored in the style object into
// the text which should be displayed in the cell.
//

BOOL CGXPasswordControl::GetControlText(CString& sResult, ROWCOL nRow, ROWCOL nCol, LPCTSTR pszRawValue, const CGXStyle& style)
{
	// base class version will store current text in sResult
	if (!CGXEditControl::GetControlText(sResult, nRow, nCol, pszRawValue, style))
		return FALSE;
	
	if (m_bReplaceAsterisk)
	{
		// replace text with password character (e.g. asterisks, '*').
		for (int n = 0; n < sResult.GetLength(); n++)
			sResult.SetAt(n, m_chPasswordChar);
	}

	return TRUE;
}

void CGXPasswordControl::SetValue(LPCTSTR pszRawValue)
{
	// Convert the value to the text which should be
	// displayed in the current cell and show this
	// text.

	CString sText;

	// Force GetControlText not to replace characters
	// with password characters.

	m_bReplaceAsterisk = FALSE; // turn off replacing characters

	GetControlText(sText, m_nRow, m_nCol, pszRawValue, *m_pStyle);

	m_bReplaceAsterisk = TRUE;  // turn on replacing characters	
	SetPasswordChar(m_chPasswordChar);
	
	SetWindowText(sText);
}

DWORD CGXPasswordControl::CalcEditStyle(LPRECT rectNP, int& dyHeight)
{
	DWORD dwStyle = CGXEditControl::CalcEditStyle(rectNP, dyHeight);

	// Add ES_PASSWORD to the edit control style settings and
	// remove ES_MULTILINE bit becuase ES_PASSWORD does not work
	// together with ES_MULTILINE.

	return dwStyle & ~ES_MULTILINE | ES_PASSWORD;
}

// Disable Copy and Cut operations, so that user
// cannot paste text into another application to
// check out the cells contents

BOOL CGXPasswordControl::Copy()
{
	return TRUE;
}

BOOL CGXPasswordControl::Cut()
{
	return TRUE;
}

// Also disable dragging selected text

void CGXPasswordControl::OnLButtonDown(UINT nFlags, CPoint point)
{
	// simply call the CEdit version
	CEdit::OnLButtonDown(nFlags, point);
}

BOOL CGXPasswordControl::CanFloatCell(ROWCOL, ROWCOL, const CGXStyle&, BOOL)
{
	// don't support floating
	return FALSE;
}
