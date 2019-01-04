///////////////////////////////////////////////////////////////////////////////
// gxctplug.cpp : implementation of the CGXCellTipPlugin 
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
// Author: Ricky Pearson
//

//RWP02a (entire file)

#define _OG_EXPORT_IMPL

#include "stdafx.h"

#if _MFC_VER >= 0x0400

#include "grid\gxproc.h"
#include "grid\gxman.h"
#include "grid\gxctwnd.h"
#include "grid\gxctplug.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// Timer ID for Fly-by
#ifndef GX_CELLTIPTIMER
#define GX_CELLTIPTIMER 993
#endif


/////////////////////////////////////////////////////////////////////////////
// CGXCellTipPlugin 

CGXCellTipPlugin::CGXCellTipPlugin(CGXGridCore* pGrid, CRuntimeClass* pFactory, 
								   BOOL bShowHeaders, BOOL bShowActive, 
								   UINT nDelay)
	: CGXPluginComponent()
{
	m_pGrid = pGrid;
	m_pCellTipWndManager = new CGXCellTipWndManager(pGrid, pFactory);
	m_dwCurrentTipID = GX_CELLTIP_ID_NOTDEFINED;
	m_nCurRow = GX_INVALID;
	m_nCurCol = GX_INVALID;
	m_nCellTipTimer = 0;
	m_bShowHeaders = bShowHeaders;
	m_bShowActive = bShowActive;
	m_nDelay = nDelay;
}

CGXCellTipPlugin::~CGXCellTipPlugin()
{
	// Make sure timer is stopped
	if (::IsWindow(m_hWnd))
		StopTimer();

	// Clean up CGXCellTipWnd objects
	if (m_pCellTipWndManager)
	{
		delete m_pCellTipWndManager;
		m_pCellTipWndManager = NULL;
	}
}

IMPLEMENT_DYNAMIC(CGXCellTipPlugin, CGXPluginComponent)

BEGIN_MESSAGE_MAP(CGXCellTipPlugin, CGXPluginComponent)
	//{{AFX_MSG_MAP(CGXCellTipPlugin)
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_MBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CGXCellTipPlugin::NeedShowCellTip(CGXControl* pControl)
{
	CGXStyle* pStyle = m_pGrid->CreateStyle();
	m_pGrid->ComposeStyleRowCol(m_nCurRow, m_nCurCol, pStyle);

	BOOL bRet = pControl->NeedShowCellTip(m_nCurRow, 
										  m_nCurCol, 
										  pStyle
										  );

	m_pGrid->RecycleStyle(pStyle);

	return bRet;
}

DWORD CGXCellTipPlugin::GetCellTipID(CGXControl* pControl)
{
	CGXStyle* pStyle = m_pGrid->CreateStyle();
	m_pGrid->ComposeStyleRowCol(m_nCurRow, m_nCurCol, pStyle);

	DWORD dwRet = pControl->GetCellTipID(m_nCurRow, 
										 m_nCurCol,
										 pStyle
										 );

	m_pGrid->RecycleStyle(pStyle);

	return dwRet;
}

void CGXCellTipPlugin::InitializeCellTip(CGXControl* pControl, CGXCellTipWnd* pCellTip)
{
	CGXStyle* pStyle = m_pGrid->CreateStyle();
	m_pGrid->ComposeStyleRowCol(m_nCurRow, m_nCurCol, pStyle);

	pControl->InitializeCellTip(m_nCurRow,
								m_nCurCol,
								pStyle,
								pCellTip
								);

	m_pGrid->RecycleStyle(pStyle);
}

void CGXCellTipPlugin::ShowCellTip()
{
	if( m_nCurRow == GX_INVALID || m_nCurCol == GX_INVALID || m_nCurRow > m_pGrid->GetRowCount() || m_nCurCol > m_pGrid->GetColCount() )
		return;

	// Get appropriate control
	CGXStyle style;
	m_pGrid->ComposeStyleRowCol(m_nCurRow, m_nCurCol, &style);
	CGXControl* pControl = m_pGrid->GetRegisteredControl(style.GetControl());

	// Verify control
	ASSERT(pControl);
	if (!pControl)
		return;

	// Determine if tip needs to be shown
	if (NeedShowCellTip(pControl))
	{
		// Get the cell tip's ID
		m_dwCurrentTipID = GetCellTipID(pControl);

		// Initialize the cell tip and show it
		if (LONG_MAX != m_dwCurrentTipID)
		{
			InitializeCellTip(pControl, m_pCellTipWndManager->CreateObject(m_dwCurrentTipID));
			m_pCellTipWndManager->CreateObject(m_dwCurrentTipID)->Show();
		}
		// Start a timer so we can constantly monitor that the mouse does not leave the grid
		StartTimer();
	}
}

void CGXCellTipPlugin::HideCellTip()
{
	// If visible, hide cell tip
	if (LONG_MAX != m_dwCurrentTipID)
	{
		m_pCellTipWndManager->CreateObject(m_dwCurrentTipID)->Hide();
		m_dwCurrentTipID = LONG_MAX;
	}
	StopTimer();
}

void CGXCellTipPlugin::StartTimer()
{
	// Clear the old timer 
	StopTimer();

	// Start new timer 
	m_nCellTipTimer = SetTimer(GX_CELLTIPTIMER, m_nDelay, NULL);

	return;
}

void CGXCellTipPlugin::StopTimer()
{
	if (m_nCellTipTimer)
	{
		KillTimer(m_nCellTipTimer);
		m_nCellTipTimer = 0;
	}
}

BOOL CGXCellTipPlugin::IsGridInSpecialMode()
{

	// Is current cell active?
	if (m_pGrid->IsActiveCurrentCell() && !m_bShowActive)
	{
		return TRUE;
	}

	// Is mouse over a row or column header?
	if ((m_nCurRow == 0 || m_nCurCol == 0 ) && !m_bShowHeaders)
	{
		return TRUE;
	}

	// Is mouse over a cell hidden?
	if (m_pGrid->IsRowHidden(m_nCurRow) || m_pGrid->IsColHidden(m_nCurCol) || 
		m_pGrid->GetRowHeight(m_nCurRow) == 0 || m_pGrid->GetColWidth(m_nCurCol) == 0)
	{
		return TRUE;
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CGXCellTipPlugin message handlers

void CGXCellTipPlugin::OnMouseMove(UINT nFlags, CPoint point)
{
	// if we are outside the grid client area
	if ((point.x < 0) ||(point.y < 0))
	{
		HideCellTip();
		return;
	}

	// Check if mouse is clicked
	if (nFlags & MK_LBUTTON ||
		nFlags & MK_MBUTTON ||
		nFlags & MK_RBUTTON)
	{
		HideCellTip();
		return;
	}

	// Check if mouse is outside client
	CRect rcGrid;
	m_pGrid->GridWnd()->GetClientRect(rcGrid);

	if (point.x > rcGrid.right || point.y > rcGrid.bottom)
	{
		// Message is outside of grid client -> hide the tip
		HideCellTip();
		m_nCurRow = m_nCurCol = GX_INVALID;
		return;
	}

 	// Get the location of the mouse in the grid
	ROWCOL nRow = m_pGrid->CalcClientRowFromPt(point);
	ROWCOL nCol = m_pGrid->CalcClientColFromPt(point);

	// Verify that it is over a cell
	if (nRow == GX_INVALID || nCol == GX_INVALID)
	{
		// Not a valid cell -> hide the tip
		m_nCurRow = m_nCurCol = GX_INVALID;
		HideCellTip();
		return ;
	}

	// Convert from relative to absolute indexing
	nRow = m_pGrid->GetRow(nRow);
	nCol = m_pGrid->GetCol(nCol);

	// Check if cell is spanned (flooded, covered, merged)
	CGXRange range;

	if (m_pGrid->GetCellRangeRowCol(nRow, nCol, range))
	{
		nRow = range.top;
		nCol = range.left;
	}

	// Check if mouse is over a new cell
	if (nRow == m_nCurRow && nCol == m_nCurCol)
	{
		// Same cell -> do nothing
		return;
	}

	// Mouse is over new cell -> save coordinates
	m_nCurRow = nRow;
	m_nCurCol = nCol;

	// Check if any special conditions exist that should prevent the cell tip 
	// from becoming visible.
	// Note: This call requires that m_nCurRow and m_nCurCol be current.
	if (IsGridInSpecialMode())
	{
		HideCellTip();
		return;
	}

	// Redraw cell tip if it is already visible, 
	// otherwise start the timer
	if (LONG_MAX != m_dwCurrentTipID)
	{
		// Already visible, no delay
		HideCellTip();  // Restore background behind current tip
		ShowCellTip();  // Move and draw new tip
	}
	else
	{
		// Not visible, start timer
		StartTimer();
	}
}

void CGXCellTipPlugin::OnTimer(SEC_UINT nIDEvent)
{
	if (nIDEvent == m_nCellTipTimer)
	{
		// Verify that the cursor is still in the grid's client
		CPoint pt;
		CRect rc;
		GetCursorPos(&pt);
		m_pGrid->GridWnd()->GetClientRect(&rc);
		m_pGrid->GridWnd()->ClientToScreen(&rc);

		if (rc.PtInRect(pt))
		{	// Mouse in client area
			// Show tip if it is not already visible
			if (LONG_MAX == m_dwCurrentTipID)
				ShowCellTip();
		}
		else
		{	// Mouse has left the client area
			// If a tip is visible, hide it
			if (LONG_MAX != m_dwCurrentTipID)
				HideCellTip();
			m_nCurRow = m_nCurCol = GX_INVALID;
		}
	}
}

void CGXCellTipPlugin::OnLButtonDown(UINT nFlags, CPoint point)
{
	// Unused
	nFlags;
	point;

	// Stop timer and hide cell tip
	StopTimer();
	HideCellTip();
}

void CGXCellTipPlugin::OnMButtonDown(UINT nFlags, CPoint point)
{
	// Unused
	nFlags;
	point;

	// Stop timer and hide cell tip
	StopTimer();
	HideCellTip();
}

void CGXCellTipPlugin::OnRButtonDown(UINT nFlags, CPoint point)
{
	// Unused
	nFlags;
	point;

	// Stop timer and hide cell tip
	StopTimer();
	HideCellTip();
}

void CGXCellTipPlugin::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// Unused
	nChar;
	nRepCnt;
	nFlags;

	// Stop timer and hide cell tip
	StopTimer();
	HideCellTip();
}


/////////////////////////////////////////////////////////////////////////////
// CGXCellTipWndManager

CGXCellTipWndManager::CGXCellTipWndManager(CGXGridCore* pGrid, CRuntimeClass* pRuntimeClass)
	: CGXNodeManager<CGXCellTipWnd>(pRuntimeClass)
{
	ASSERT(pGrid);

	m_pGrid = pGrid;
	m_pFactory = NULL;
}

CGXCellTipWndManager::~CGXCellTipWndManager()
{
	if (m_pFactory)
	{
		delete m_pFactory;
		m_pFactory = NULL;
	}
}

CGXCellTipWnd* CGXCellTipWndManager::CreateObject(SEC_DWORD dw)
{
	CGXCellTipWnd* pObject = NULL;
	if(GetMap()->Lookup(dw, pObject) == FALSE )
	{
		if (!m_pFactory)
		{
			m_pFactory = (CGXCellTipWndFactory*)m_pRuntimeClass->CreateObject();

			// Verify that factory was created
			ASSERT(m_pFactory);

			if (NULL == m_pFactory)
				return pObject;

			m_pFactory->m_pGrid = m_pGrid;
		}

		CGXCellTipWnd* p = m_pFactory->CreateCellTipWnd((DWORD)dw);

		ASSERT(p != NULL);
		
		GetMap()->SetAt(dw, p);
		return p;
	}
	else
	{
		return pObject;
	}	
}


/////////////////////////////////////////////////////////////////////////////
// CGXCellTipWndFactory

IMPLEMENT_DYNCREATE(CGXCellTipWndFactory, CObject);

CGXCellTipWnd* CGXCellTipWndFactory::CreateCellTipWnd(DWORD dwCellTipID)
{
	CGXCellTipWnd* pCellTipWnd = NULL;

	if (!m_pGrid)
		return pCellTipWnd;

	switch (dwCellTipID)
	{
	case GX_CELLTIP_ID_TEXT:
		pCellTipWnd = new CGXTextCellTipWnd(m_pGrid);
		break;

	case GX_CELLTIP_ID_BITMAP:
		pCellTipWnd = new CGXStaticBitmapCellTipWnd(m_pGrid);
	}

	if (pCellTipWnd)
		pCellTipWnd->CreateTipWnd();

	return pCellTipWnd;
}


/////////////////////////////////////////////////////////////////////////////
// CGXGridCore

void CGXGridCore::EnableCellTips(CRuntimeClass* pCellTipWndFactory /*= NULL*/, 
								 BOOL bShowHeaders /*= FALSE*/,
								 BOOL bShowActive /*= FALSE*/, 
								 UINT nDelay /*= 500*/)
{
	ASSERT(m_pCellTipPlugin == NULL);
	// ASSERTION-> EnableCellTips called more than once. ->END

	if (pCellTipWndFactory)
	{
		AddPlugin(m_pCellTipPlugin = new CGXCellTipPlugin(this, pCellTipWndFactory, 
														  bShowHeaders, bShowActive, nDelay));
	}
	else
	{
		AddPlugin(m_pCellTipPlugin = new CGXCellTipPlugin(this, RUNTIME_CLASS(CGXCellTipWndFactory),
														  bShowHeaders, bShowActive, nDelay));
	}
}

#else

void CGXGridCore::EnableCellTips(CRuntimeClass* pCellTipWndFactory /*= NULL*/, 
								 BOOL bShowHeaders /*= FALSE*/,
								 BOOL bShowActive /*= FALSE*/, 
								 UINT nDelay /*= 500*/)
{
	TRACE("Warning: Call to EnableCellTips() ignored.  Not supported for Win16.\n");
}

#endif // _MFC_VER >= 0x0400


