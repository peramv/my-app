///////////////////////////////////////////////////////////////////////////////
// gxinfspl.cpp: implementation of the CGXRecordInfoSplitterWnd class.
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
#include "grid\gxresrc.h"

#ifndef _GXCORE_H_
#include "grid\gxcore.h" // needed for CGXAbstractRecordInfoWndInterface
#endif

#ifndef _GXINFWND_H_
#include "grid\gxinfwnd.h"
#endif

#if _MFC_VER >= 0x0400

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(CGXRecordInfoSplitterWnd, CGXSplitterWnd);

/////////////////////////////////////////////////////////////////////////////
// Interface to CGXGridCore

class CGXRecordInfoSplitterWndInterface: public CGXAbstractRecordInfoWndInterface
{
public:
	virtual void UpdateRecordInfoWnd(CGXGridCore* pGrid);
	virtual void SetActivePane(CGXGridCore* pGrid);
};

void CGXRecordInfoSplitterWndInterface::UpdateRecordInfoWnd(CGXGridCore* pGrid)
{
	// Record Window support
	CGXRecordInfoSplitterWnd* pWnd = (CGXRecordInfoSplitterWnd*)
		GXGetParentWnd(pGrid->GridWnd(), RUNTIME_CLASS(CGXRecordInfoSplitterWnd), TRUE);

	if (pWnd && pWnd->GetBeam())
	{
		ROWCOL nRow = 1, nCol = 1;
		pGrid->GetCurrentCell(nRow, nCol);
		long nCurrent = (long) (nRow-pGrid->GetHeaderRows());
		long nCount = (long) (pGrid->GetRowCount()-pGrid->GetHeaderRows());

		if (pWnd->GetBeam()->GetCurrentRecord() != nCurrent
			|| pWnd->GetBeam()->GetRecordCount() != nCount)
		{
			pWnd->GetBeam()->SetRecordCount(nCount);
			pWnd->GetBeam()->SetCurrentRecord(nCurrent);
			pWnd->GetBeam()->Invalidate();
			pWnd->GetBeam()->UpdateWindow();
		}
	}
}

void CGXRecordInfoSplitterWndInterface::SetActivePane(CGXGridCore* pGrid)
{
	CGXRecordInfoSplitterWnd* pWnd = (CGXRecordInfoSplitterWnd*)
		GXGetParentWnd(pGrid->GridWnd(), RUNTIME_CLASS(CGXRecordInfoSplitterWnd), TRUE);

	if (pWnd)
		pWnd->SetActivePane(-1, -1, pGrid->GridWnd());

	UpdateRecordInfoWnd(pGrid);
}

//////////////////////////////////////////////////////////////////////

CGXRecordInfoSplitterWnd::CGXRecordInfoSplitterWnd(CRuntimeClass* pBeamClass)
{
	m_pBeamClass = pBeamClass;
	m_pBeam = NULL;
	m_nvSplitterBoxPos = gxTop;
	m_nhSplitterBoxPos = gxRight;

	// to remove any dependencies on CGXGridCore comment out the following
	// line 
	if (GXGetAppData()->m_pRecordInfoSplitterWndInt == NULL)
		GXGetAppData()->m_pRecordInfoSplitterWndInt = new CGXRecordInfoSplitterWndInterface;
}

CGXRecordInfoSplitterWnd::~CGXRecordInfoSplitterWnd()
{
	// delete m_pBeam;
}

BEGIN_MESSAGE_MAP(CGXRecordInfoSplitterWnd, CGXSplitterWnd)
	//{{AFX_MSG_MAP(CGXRecordInfoSplitterWnd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CGXRecordInfoSplitterWnd::RecalcLayout()
{
	int nAlign = gxLeft;

	if (m_pBeam == NULL && m_pBeamClass)
	{
		m_pBeam = (CGXRecordInfoBeam*) m_pBeamClass->CreateObject();
		VERIFY(m_pBeam->Create(WS_VISIBLE, CRect(0, 0, 1, 1), this, GX_IDW_INSIDE_FIRST));

		delete m_apInsideWndState[nAlign];
		m_apInsideWndState[nAlign] = new CGXInsideWndState;

		CGXInsideWndState& state = *m_apInsideWndState[nAlign];
		state.pWnd = m_pBeam;
		state.bResizable = FALSE;
		state.ndx = 1;
		
		// just for completeness
		state.sizeMin = CSize(50, 0);
		state.sizeBox = CSize(6, 0);
		state.nAlign = nAlign;
		state.lRelSize = 300;
	}

	if (m_pBeam)
	{
		CGXInsideWndState& state = *m_apInsideWndState[nAlign];
		state.size = CSize(m_pBeam->GetWidth()+1, 1);
	}

	CGXSplitterWnd::RecalcLayout();

	if (m_pBeam)
		m_pBeam->m_pNotifyWnd = GetActivePane();
}

CGXRecordInfoBeam* CGXRecordInfoSplitterWnd::GetBeam()
{
	return m_pBeam;
}

void CGXRecordInfoSplitterWnd::SetActivePane(int row, int col, CWnd* pWnd)
{
	CGXSplitterWnd::SetActivePane(row, col, pWnd);

	if (m_pBeam)
		m_pBeam->m_pNotifyWnd = GetActivePane();
}


#endif
