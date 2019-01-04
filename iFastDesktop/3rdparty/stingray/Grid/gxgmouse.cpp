///////////////////////////////////////////////////////////////////////////////
// gxgmouse.cpp : intelli mouse panning and dragging for grid
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

#include "grid\gxresrc.h"
#include "grid\gxgmouse.h"

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

void CGXGridCore::EnableIntelliMouse()
{
	ASSERT(m_pImousePlugin == NULL);
	// ASSERTION->
	// Warning: IntelliMousePlugin already registered.
	// Did you call both EnableIntelliMouse() and EnableMouseWheel()
	// If yes, remove the call to EnableMouseWheel.
	// ->END

	AddPlugin(m_pImousePlugin = new CGXGridIntelliMousePlugin(this));
}

/////////////////////////////////////////////////////////////////////////////
// CGXGridIntelliMousePlugin

CGXGridIntelliMousePlugin::CGXGridIntelliMousePlugin(CGXGridCore* pGrid)
{
	m_pGrid = pGrid;
}

CGXGridIntelliMousePlugin::~CGXGridIntelliMousePlugin()
{
}


BEGIN_MESSAGE_MAP(CGXGridIntelliMousePlugin, CGXIntelliMousePlugin)
	//{{AFX_MSG_MAP(CGXGridIntelliMousePlugin)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CGXGridIntelliMousePlugin message handlers

int CGXGridIntelliMousePlugin::OnIMouseGetZoom()
{
	if (m_pGrid)
		return m_pGrid->GetZoom();
	else
		return 0;
}

void CGXGridIntelliMousePlugin::OnIMouseSetZoom(int nZoom)
{
	if (m_pGrid)
		m_pGrid->SetZoom(nZoom);
}

/*void CGXGridIntelliMousePlugin::OnIMouseVScroll(UINT nSBCode, UINT nScroll)
{
	BOOL b = m_pGrid->m_bDoScrollNoUpdateWindow;
	m_pGrid->OnAutoScroll(nSBCode == SB_LINEUP ? GX_UP : GX_DOWN, nScroll);
	m_pGrid->m_bDoScrollNoUpdateWindow = b;
}

void CGXGridIntelliMousePlugin::OnIMouseHScroll(UINT nSBCode, UINT nScroll)
{
	BOOL b = m_pGrid->m_bDoScrollNoUpdateWindow;
	m_pGrid->OnAutoScroll(nSBCode == SB_LINEUP ? GX_LEFT : GX_RIGHT, nScroll);
	m_pGrid->m_bDoScrollNoUpdateWindow = b;
}*/ // will add support for page mode 


void CGXGridIntelliMousePlugin::OnIMouseVScroll(UINT nSBCode, UINT nScroll) // Add support for page mode.
{
	BOOL b = m_pGrid->m_bDoScrollNoUpdateWindow;
	//m_pGrid->OnAutoScroll(nSBCode == SB_LINEUP ? GX_UP : GX_DOWN, nScroll);
	
	switch (nSBCode)
	{
	case SB_LINEDOWN:
		m_pGrid->OnAutoScroll(GX_DOWN, nScroll);
		break;
		
	case SB_LINEUP:
		m_pGrid->OnAutoScroll(GX_UP, nScroll);
		break;
		
    case SB_PAGEDOWN:
		{
			ROWCOL nRowCount = m_pGrid->GetRowCount();
			if (m_pGrid->m_nTopRow < nRowCount)
			{
				ROWCOL    nRow = m_pGrid->CalcBottomRowFromRect(m_pGrid->GetGridRect());
				
				if (nRow < m_pGrid->m_nTopRow)
					// All visible rows are frozen
					return;
				
				m_pGrid->OnAutoScroll(GX_DOWN, max(1, nRow-m_pGrid->m_nTopRow));
			}
		}
		break;
		
	case SB_PAGEUP:
		if (m_pGrid->m_nTopRow > 1)
		{
			CRect   rectGrid = m_pGrid->GetGridRect();
			int    dy = rectGrid.Height()-m_pGrid->CalcSumOfRowHeights(0, m_pGrid->GetFrozenRows());
			int    y = m_pGrid->GetRowHeight(m_pGrid->m_nTopRow);
			ROWCOL  ndRow = 0;
			
			while (y < dy && m_pGrid->m_nTopRow-ndRow > 1)
				y += m_pGrid->GetRowHeight(m_pGrid->m_nTopRow-(++ndRow));
			
			ASSERT(ndRow < m_pGrid->m_nTopRow);
			
			m_pGrid->OnAutoScroll(GX_UP, max(1, ndRow));
		}
		break;
	}
	
	m_pGrid->m_bDoScrollNoUpdateWindow = b;
}


void CGXGridIntelliMousePlugin::OnIMouseHScroll(UINT nSBCode, UINT nScroll) // Add support for page mode.
{
	BOOL b = m_pGrid->m_bDoScrollNoUpdateWindow;
	//m_pGrid->OnAutoScroll(nSBCode == SB_LINEUP ? GX_LEFT : GX_RIGHT, nScroll);
	
	switch (nSBCode)
	{
	case SB_LINEDOWN:
		m_pGrid->OnAutoScroll(GX_RIGHT, nScroll);	
		break;
		
	case SB_LINEUP:
		m_pGrid->OnAutoScroll(GX_LEFT, nScroll);	
		break;
		
	case SB_PAGEDOWN:
		{
			ROWCOL nColCount = m_pGrid->GetColCount();		 
			if (m_pGrid->m_nLeftCol < nColCount)
			{
				ROWCOL nCol = m_pGrid->CalcRightColFromRect(m_pGrid->GetGridRect());
				
				if (nCol < m_pGrid->m_nLeftCol)
					// All visible columns are frozen
					return;
				
				m_pGrid->OnAutoScroll(GX_RIGHT, max(nCol-m_pGrid->m_nLeftCol, 1));
			}
		}
        break;
		
    case SB_PAGEUP: 
		if (m_pGrid->m_nLeftCol > 1)
		{
			CRect   rectGrid = m_pGrid->GetGridRect();
			int    dx = rectGrid.Width()-m_pGrid->CalcSumOfColWidths(0, m_pGrid->GetFrozenCols());
			int    x = m_pGrid->GetColWidth(m_pGrid->m_nLeftCol);
			ROWCOL  ndCol = 0;
			
			while (x < dx && m_pGrid->m_nLeftCol-ndCol > 1)
				x += m_pGrid->GetColWidth(m_pGrid->m_nLeftCol-(++ndCol));
			
			ASSERT(ndCol < m_pGrid->m_nLeftCol);

			m_pGrid->OnAutoScroll(GX_LEFT, max(1, ndCol));
		}
	    break;
	}

	m_pGrid->m_bDoScrollNoUpdateWindow = b;
}
