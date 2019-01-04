///////////////////////////////////////////////////////////////////////////////
// gxgscrltp.cpp : implementation of the CGXScrollTipPlugin class
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

#include "grid\gxscrltp.h"
#include "grid\gxview.h"

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXSCRLTP")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CGXScrollTipPlugin

CGXScrollTipPlugin::CGXScrollTipPlugin(CGXGridCore* pGrid)
{
	m_pScrollTip = NULL;
	m_pGrid = pGrid;
}

CGXScrollTipPlugin::~CGXScrollTipPlugin()
{
	delete m_pScrollTip;
}


BEGIN_MESSAGE_MAP(CGXScrollTipPlugin, CGXPluginComponent)
	//{{AFX_MSG_MAP(CGXScrollTipPlugin)
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CGXScrollTipPlugin message handlers

void CGXScrollTipPlugin::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// If the grid is in a dynamic splitter then you get multiple
	// scroll messages if a scrollbar is shared by more than 1 (grid in the)pane.
	// So, disregard any scroll messages sent for a pane that is not the right most(for VSCROLL)
	// or the bottom most (for HSCROLL)
	CSplitterWnd* pSplitterWnd = CGXView::GetParentDynamicSplitter(m_pGrid->GridWnd(), TRUE);
	if(pSplitterWnd)
	{
		int row, col;
		// If not right most, then disregard this message
		// [VC7] Substitute IsChildPane to macro.
		if(SPWND_ISCHILDPANE(pSplitterWnd, m_pGrid->GridWnd(), row, col) && !(col == 0))
			return;
	}

	switch(nSBCode)
	{
	case SB_THUMBTRACK:
	case SB_THUMBPOSITION:
		if (m_pScrollTip == NULL)
			m_pScrollTip = new CGXScrollTip;

		if (!GXGetAppData()->bWin31)
		{
			// ScrollTips
			ROWCOL nRow = nPos;
			if (m_pGrid)
				nRow *= m_pGrid->m_nVScrollFactor;
			TCHAR szText[256];
			wsprintf(szText, _T("Row: %u"), nRow);
			m_pScrollTip->HandleScrollMessage(this, nSBCode, SB_VERT, szText, pScrollBar);
		}
	}
}

void CGXScrollTipPlugin::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// If the grid is in a dynamic splitter then you get multiple
	// scroll messages if a scrollbar is shared by more than 1 (grid in the)pane.
	// So, disregard any scroll messages sent for a pane that is not the right most(for VSCROLL)
	// or the bottom most (for HSCROLL)
	CSplitterWnd* pSplitterWnd = CGXView::GetParentDynamicSplitter(m_pGrid->GridWnd(), TRUE);
	if(pSplitterWnd)
	{
		int row, col;
		// If not bottom most then disregard this message
		// [VC7] Substitute IsChildPane to macro.
		if(SPWND_ISCHILDPANE(pSplitterWnd,m_pGrid->GridWnd(), row, col) && !(row == 0))
			return;
	}

	switch(nSBCode)
	{
	case SB_THUMBTRACK:
	case SB_THUMBPOSITION:
		if (m_pScrollTip == NULL)
			m_pScrollTip = new CGXScrollTip;

		if (!GXGetAppData()->bWin31)
		{
			// ScrollTips
			ROWCOL nCol = nPos;
			if (m_pGrid)
				nCol *= m_pGrid->m_nHScrollFactor;
			TCHAR szText[256];
			wsprintf(szText, _T("Column: %u"), nCol);
			m_pScrollTip->HandleScrollMessage(this, nSBCode, SB_HORZ, szText, pScrollBar);
		}
	}
}

void CGXGridCore::EnableScrollTips()
{
	ASSERT(m_pScrollTipPlugin == NULL);
	// ASSERTION-> EnableScrollTips called more than once.->END

	AddPlugin(m_pScrollTipPlugin = new CGXScrollTipPlugin(this));
}


#else

void CGXGridCore::EnableScrollTips()
{
	TRACE("Warning: Call to ImplementScrollTips() ignored. Not supported for Win16.\n");
}

#endif
