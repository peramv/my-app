///////////////////////////////////////////////////////////////////////////////
// gxautscr.cpp : Auto/Speed scrolling 
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

#include "grid\gxcore.h"
#include "grid\gxautscr.h"
#include "grid\gxmsg.h"

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// Drag Scrolling
#define GX_DEFSCROLLSPEED		80  // slowest scroll speed
#define GX_DEFSCROLLACCEL		2    // Accelerate scroll speed
#define GX_DEFSCROLLBYACCEL		2
#define GX_DEFSCROLLBYMAX		80

// Mouse move messages
#define GX_DEFMOUSEMOVESPEED	100
#define GX_DEFMOUSEMOVEACCEL	3

// Speed scrolling when user clicked on scrollbar
#define GX_SPEEDSCROLLDIST		2	// Distance factor (emulates drag scroll)

// Speed scrolling when user clicked arrow key
#define GX_SPEEDKEYDIST			8	// Distance factor (emulates drag scroll)

void CGXGridCore::ImplementAutoScroll()
{
	if (m_pAutoScrollPlugin)
		return;

	// else
	AddPlugin(m_pAutoScrollPlugin = new CGXAutoScrollPlugin(this));
}

/////////////////////////////////////////////////////////////////////////////
// CGXAutoScrollPlugin

CGXAutoScrollPlugin::CGXAutoScrollPlugin(CGXGridCore* pGrid)
{
	GX_ZERO_INIT_OBJECT(CGXPluginComponent)

	m_pGrid = pGrid;
	m_pGrid->m_bAutoScroll = TRUE;
}

CGXAutoScrollPlugin::~CGXAutoScrollPlugin()
{
}


BEGIN_MESSAGE_MAP(CGXAutoScrollPlugin, CGXPluginComponent)
	//{{AFX_MSG_MAP(CGXAutoScrollPlugin)
	ON_WM_TIMER()
	ON_WM_LBUTTONUP()
	ON_WM_MBUTTONUP()
	ON_WM_RBUTTONUP()
	ON_WM_CANCELMODE()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CGXAutoScrollPlugin message handlers

void CGXAutoScrollPlugin::OnTimer(SEC_UINT nIDEvent) 
{
	if (nIDEvent == GX_AUTOSCROLLTIMER)
	{
		if (m_pGrid->m_bAutoScrollStop)
		{
			KillAutoScroll();
			return;
		}

		if (m_pGrid->m_bAutoScrollStart)
		{
			// start autoscroll operation
			m_pGrid->m_bAutoScrollStart = FALSE;
				// will be checked and reset in autoscroll plugin component's
				// WM_TIMER messeage

			m_bScrollVert = m_pGrid->m_bAutoScrollVert;
			m_bScrollHorz = m_pGrid->m_bAutoScrollHorz; 
			m_nScrollDirection = m_pGrid->m_nAutoScrollDirection;
			m_nSpeedKeyChar = m_pGrid->m_nSpeedKeyChar;
			m_nSpeedKeyFlags = m_pGrid->m_nSpeedKeyFlags;
			m_nTimer = m_pGrid->m_nAutoScrollTimer;

			// Calculate scrolling area and store it in m_rectScroll
			m_rectScroll = m_pGrid->GetGridRect();      
			ROWCOL nFrozenRows = m_pGrid->GetFrozenRows();
			ROWCOL nFrozenCols = m_pGrid->GetFrozenCols();

			m_rectScroll.top += m_pGrid->CalcSumOfRowHeights(0, nFrozenRows);
			m_rectScroll.left += m_pGrid->CalcSumOfColWidths(0, nFrozenCols);

			m_dwCurrentTick = GetTickCount();
			m_nNextScrollTicks = GX_DEFSCROLLSPEED;
			m_nNextMouseMoveTicks = GX_DEFSCROLLSPEED;
			m_dwLastTick = 0;
			m_nScrollBy = 1;
			m_nLastDistance = 0;

			GetCursorPos(&m_ptOrgPos);
			ScreenToClient(&m_ptOrgPos);
		}

		DWORD dwTick = GetTickCount();

		CPoint ptCursorPos;
		GetCursorPos(&ptCursorPos);
		ScreenToClient(&ptCursorPos);

		// scroll if necessary
		if (dwTick - m_dwLastTick > (DWORD) m_nNextScrollTicks)
		{
			m_dwLastTick = dwTick;

			int nDistance = 0, nDirection = 0;
			BOOL bScrolled = FALSE;
			int nFact = 1;

			// Vertikal Scrolling

			// if mouse cursor is dragging outside the client area, scrolling occurs
			if (m_pGrid->m_bSpeedKey)
			{
				if (m_nNextScrollTicks < GX_DEFSCROLLSPEED/2)
					SendMessage(WM_KEYDOWN, m_nSpeedKeyChar, MAKELONG(max(1, m_nScrollBy/5), m_nSpeedKeyFlags)); 
				nDistance = GX_SPEEDKEYDIST;
				bScrolled = TRUE;
			}

			if (!bScrolled && m_nScrollDirection != -1)
			{
				if (m_nNextScrollTicks < GX_DEFSCROLLSPEED/2)
					m_pGrid->OnAutoScroll(nDirection = m_nScrollDirection, max(1, m_nScrollBy/10));
				nDistance = GX_SPEEDSCROLLDIST;
				bScrolled = TRUE;
			}

			if (!bScrolled && m_bScrollVert)
			{
				nFact = 5;

				if (ptCursorPos.y < m_rectScroll.top)
				{
					// Cursor is above client area
					nDistance = m_rectScroll.top - ptCursorPos.y;
					nDirection = GX_UP;
				}
				else if (ptCursorPos.y > m_rectScroll.bottom)
				{
					// Cursor is below client area
					nDistance = ptCursorPos.y - m_rectScroll.bottom;
					nDirection = GX_DOWN;
				}

				bScrolled = m_pGrid->OnAutoScroll(nDirection, max(1, m_nScrollBy/10));
			}

			// Horizontal Scrolling

			if (!bScrolled && m_bScrollHorz)
			{
				nFact = 10;

				if (ptCursorPos.x < m_rectScroll.left)
				{
					// Cursor is on the left of the client area
					nDistance = m_rectScroll.left-ptCursorPos.x;
					nDirection = GX_LEFT;
				}
				else if (ptCursorPos.x > m_rectScroll.right)
				{
					// Cursor is on the right of the client area
					nDistance = ptCursorPos.x - m_rectScroll.right;
					nDirection = GX_RIGHT;
				}

				bScrolled = m_pGrid->OnAutoScroll(nDirection, max(1, m_nScrollBy/10));
			}


			if (!bScrolled || nDistance < m_nLastDistance)
			{
				m_nNextScrollTicks = GX_DEFSCROLLSPEED;
				m_nScrollBy = 1;
			}
			else if (nDistance > 1)
			{
				m_nNextScrollTicks -= nDistance/nFact/GX_DEFSCROLLACCEL;

				if (m_nNextScrollTicks < 0)
				{
					m_nNextScrollTicks = 0;
					m_nScrollBy += GX_DEFSCROLLBYACCEL;
					m_nScrollBy = min(m_nScrollBy, GX_DEFSCROLLBYMAX);
				}
			}

			m_nLastDistance = nDistance;

			// peridically do OnMouseMove
			if (m_nScrollDirection == -1)
				SendMessage(WM_MOUSEMOVE, 0, MAKELONG(ptCursorPos.x, ptCursorPos.y));
		}
		else if (abs(ptCursorPos.x-m_ptOrgPos.x) + abs(ptCursorPos.y-m_ptOrgPos.y) > 5)
		{
			// if the user drags the mouse immediately
			if (m_nScrollDirection == -1 && !m_pGrid->m_bSpeedKey)
				SendMessage(WM_MOUSEMOVE, 0, MAKELONG(ptCursorPos.x, ptCursorPos.y));

			// reset frequency of mouse move message 
			m_nNextMouseMoveTicks = GX_DEFMOUSEMOVESPEED;
		}
		else if (dwTick - m_dwLastTick > (DWORD) m_nNextMouseMoveTicks)
		{
			if (m_nScrollDirection == -1 && !m_pGrid->m_bSpeedKey)
				SendMessage(WM_MOUSEMOVE, 0, MAKELONG(ptCursorPos.x, ptCursorPos.y));
			m_nNextMouseMoveTicks -= GX_DEFMOUSEMOVEACCEL;
			// increase frequency of mouse move message (usefull for spin buttons etc. )
		}
	}
}

void CGXAutoScrollPlugin::OnLButtonUp(UINT , CPoint ) 
{
	KillAutoScroll();
}

void CGXAutoScrollPlugin::OnMButtonUp(UINT , CPoint ) 
{
	KillAutoScroll();
}

void CGXAutoScrollPlugin::OnRButtonUp(UINT , CPoint ) 
{
	KillAutoScroll();
}

void CGXAutoScrollPlugin::OnCancelMode() 
{
	KillAutoScroll();
}

void CGXAutoScrollPlugin::OnKeyDown(UINT nChar, UINT , UINT ) 
{
	switch (nChar)
	{
	case VK_ESCAPE:
		KillAutoScroll();
		break;
	default:
		if (nChar != m_pGrid->m_nSpeedKeyChar)
			KillAutoScroll();
		break;
	}
}

void CGXAutoScrollPlugin::OnKeyUp(UINT , UINT , UINT ) 
{
	KillAutoScroll();
}

void CGXAutoScrollPlugin::KillAutoScroll()
{
	if (m_nTimer)
	{
		// Parent window will call ReleaseCapture
		KillTimer(m_nTimer);
		m_nTimer = 0;
	}
	m_pGrid->m_nAutoScrollDirection = -1;
	m_pGrid->m_bSpeedKey = FALSE;
	m_pGrid->m_bAutoScrollStop = TRUE;
}



void CGXAutoScrollPlugin::OnKillFocus(CWnd* ) 
{
	if (!m_pGrid->m_bIgnoreFocus)
		KillAutoScroll();
}
