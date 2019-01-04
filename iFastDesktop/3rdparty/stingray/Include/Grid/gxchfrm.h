///////////////////////////////////////////////////////////////////////////////
// gxchfrm.h
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
//          Supplement Section 227.7202, Government�s use, duplication or
//          disclosure of the computer software is subject to the restrictions
//          set forth by Rogue Wave Software, Inc.
//
///////////////////////////////////////////////////////////////////////////////
//
// Author: Daniel Jebaraj
//

#ifndef _GX_CH_FRM_H__
#define _GX_CH_FRM_H__

#include "grid\gxfradpt.h"
#include <StingrayExportDefs.h>

//
// GridMFC Extension DLL
// initialize declaration context
//

#ifdef _GXDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    GX_DATAEXT
#endif

/////////////////////////////////////////////////////////////////////////////

class CGXTabCreateInfo;

class CGXWChildFrame : public CMDIChildWnd, public CGXMDIFrameAdapter
{
	GRID_DECLARE_DYNCREATE(CGXWChildFrame)
public:
	GRID_API CGXWChildFrame();

protected:
	GRID_API virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	GRID_API virtual void PostNcDestroy( );
	//}}AFX_VIRTUAL

// Implementation
public:
	GRID_API virtual ~CGXWChildFrame();
#ifdef _DEBUG
	GRID_API virtual void AssertValid() const;
	GRID_API virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CGXWChildFrame)
	//}}AFX_MSG
		
	GRID_API afx_msg LRESULT OnInitNew( WPARAM, LPARAM );
	GRID_API afx_msg LRESULT OnInitFromFile( WPARAM, LPARAM );
	GRID_API afx_msg void InsertWorkSheet();
	GRID_API afx_msg void DeleteWorkSheet();
	GRID_API afx_msg void CanInsertWorkSheet(CCmdUI* pUI);
	GRID_API afx_msg void CanDeleteWorkSheet(CCmdUI* pUI);
	GRID_API afx_msg void OnWindowNew();
	GRID_DECLARE_MESSAGE_MAP()
};

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

#endif //_GX_CH_FRM_H__
