///////////////////////////////////////////////////////////////////////////////
// gxchild.cpp : implementation of child class
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
#pragma code_seg("GX_SEG_GXCHILD")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CGXChild

CGXChild::CGXChild(CGXControl* pComposite)
{
	m_pComposite = pComposite;
	m_bDoubleByteChar = FALSE;
}

CGXChild::~CGXChild()
{
}

void CGXChild::SetRect(const CRect& r)
{
	m_rect = r;
}

CRect CGXChild::GetRect()
{
	return m_rect;
}

BOOL CGXChild::Intersects(CPoint pt)
{
	return m_rect.PtInRect(pt);
}

BOOL CGXChild::HasFocus()
{
	return m_pComposite->ChildWithFocus() == this;
}

void CGXChild::SetText(LPCTSTR s)
{
	m_sText = s;
}

CString CGXChild::GetText()
{
	return m_sText;
}

void CGXChild::Refresh()
{
	m_pComposite->GridWnd()->InvalidateRect(m_rect);
}

BOOL CGXChild::LButtonDown(UINT nFlags, CPoint pt)
{
	// Unreferenced:
	nFlags, pt;

	return FALSE;
}

BOOL CGXChild::LButtonUp(UINT nFlags, CPoint pt)
{
	// Unreferenced:
	nFlags, pt;

	return FALSE;
}

BOOL CGXChild::MButtonDown(UINT nFlags, CPoint pt)
{
	// Unreferenced:
	nFlags, pt;

	return FALSE;
}

BOOL CGXChild::MButtonUp(UINT nFlags, CPoint pt)
{
	// Unreferenced:
	nFlags, pt;

	return FALSE;
}

BOOL CGXChild::RButtonDown(UINT nFlags, CPoint pt)
{
	// Unreferenced:
	nFlags, pt;

	return FALSE;
}

BOOL CGXChild::RButtonUp(UINT nFlags, CPoint pt)
{
	// Unreferenced:
	nFlags, pt;

	return FALSE;
}

BOOL CGXChild::RButtonDblClk(UINT nFlags, CPoint pt)
{
	// Unreferenced:
	nFlags, pt;

	return FALSE;
}

BOOL CGXChild::LButtonDblClk(UINT nFlags, CPoint pt)
{
	// Unreferenced:
	nFlags, pt;

	return FALSE;
}

BOOL CGXChild::MButtonDblClk(UINT nFlags, CPoint pt)
{
	// Unreferenced:
	nFlags, pt;

	return FALSE;
}

BOOL CGXChild::MouseMove(UINT nFlags, CPoint pt)
{
	// Unreferenced:
	nFlags, pt;

	return FALSE;
}

BOOL CGXChild::MouseMoveOver(ROWCOL nRow, ROWCOL nCol, UINT nFlags, CPoint pt)
{
	// Unreferenced:
	nRow, nCol, nFlags, pt;

	return FALSE;
}

BOOL CGXChild::KeyPressed(UINT nMessage, UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nMessage)
	{
	// Keyboard messages
	case WM_KEYDOWN:
		return OnGridKeyDown(nChar, nRepCnt, nFlags);

	case WM_KEYUP:
		return OnGridKeyUp(nChar, nRepCnt, nFlags);

	case WM_CHAR:
		{
			// support for DBCS characters
			CString sChar;
			if (GXGetDoubleByteChar((TCHAR) nChar, sChar, m_bDoubleByteChar, m_nDoubleByteLeadChar))
			{
				if (sChar.IsEmpty())
					return TRUE;

				return OnGridDoubleByteChar(sChar, nRepCnt, nFlags);
			}
			else // this is a normal character
			{
				return OnGridChar(nChar, nRepCnt, nFlags);
			}
		}

	case WM_DEADCHAR:
		return OnGridDeadChar(nChar, nRepCnt, nFlags);

	case WM_SYSKEYDOWN:
		return OnGridSysKeyDown(nChar, nRepCnt, nFlags);

	case WM_SYSKEYUP:
		return OnGridSysKeyUp(nChar, nRepCnt, nFlags);

	case WM_SYSCHAR:
		return OnGridSysChar(nChar, nRepCnt, nFlags);

	case WM_SYSDEADCHAR:
		return OnGridSysDeadChar(nChar, nRepCnt, nFlags);
	}

	return FALSE;
}

BOOL CGXChild::OnGridKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// Unused:
	nChar, nRepCnt, nFlags;

	return FALSE;   // return TRUE if you don't want default processing of this event
}

BOOL CGXChild::OnGridKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// Unused:
	nChar, nRepCnt, nFlags;

	return FALSE;   // return TRUE if you don't want default processing of this event
}

BOOL CGXChild::OnGridChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// Unused:
	nChar, nRepCnt, nFlags;

	return FALSE;   // return TRUE if you don't want default processing of this event
}

BOOL CGXChild::OnGridDoubleByteChar(const CString& sChar, UINT nRepCnt, UINT nFlags)
{
	// Unused:
	sChar, nRepCnt, nFlags;

	return FALSE;   // return TRUE if you don't want default processing of this event
}

BOOL CGXChild::OnGridDeadChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// Unused:
	nChar, nRepCnt, nFlags;

	return FALSE;   // return TRUE if you don't want default processing of this event
}

BOOL CGXChild::OnGridSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// Unused:
	nChar, nRepCnt, nFlags;

	return FALSE;   // return TRUE if you don't want default processing of this event
}

BOOL CGXChild::OnGridSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// Unused:
	nChar, nRepCnt, nFlags;

	return FALSE;   // return TRUE if you don't want default processing of this event
}

BOOL CGXChild::OnGridSysChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// Unused:
	nChar, nRepCnt, nFlags;

	return FALSE;   // return TRUE if you don't want default processing of this event
}

BOOL CGXChild::OnGridSysDeadChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// Unused:
	nChar, nRepCnt, nFlags;

	return FALSE;   // return TRUE if you don't want default processing of this event
}

void CGXChild::OnGridWinIniChange(LPCTSTR lpszSection)
{
	// Unused:
	lpszSection;
}

void CGXChild::OnGridSysColorChange()
{
}

void CGXChild::OnGridCancelMode()
{
}

void CGXChild::Draw(CDC* pDC, BOOL bActive, const CGXStyle& style)
{
   //if, not overridden, delegate drawing to abstract method
   Draw(pDC, bActive);

   style; //unused
}
