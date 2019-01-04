///////////////////////////////////////////////////////////////////////////////
// gxrdvw.h : Interface of the CGXExcelReadView class
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

//const int gxnFirstCtrl = 101;

#ifndef _GX_RD_VW_H__
#define _GX_RD_VW_H__

#ifndef _GX_EX_EX_BASE_H__
#include "grid\gxexbse.h"
#endif

#include <StingrayExportDefs.h>

//
// GridMFC Extension DLL
// initialize declaration context
//

#if	defined(_GXDLL) && !defined(_GXNOEXTSTATE) 
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    GX_DATAEXT
#endif

////////////////////////////////////////////////////////////////
// CGXExcelReadView ////////////////////////////////////////////

class CGXExcelReadView : public CGXGridView, public CGXExcelGrid
{
protected: // create from serialization only
	GRID_API CGXExcelReadView();
	GRID_DECLARE_SERIAL(CGXExcelReadView)

// Attributes
public:
	GRID_API CGXExcelReadDoc* GetDocument();

// Operations
public:

// overrides
	GRID_API virtual void OnExcelFileInitialUpdate();
	GRID_API virtual void OnExcelFileInitialUpdateDone();
	GRID_API virtual void OnInitializeNewFile();
	
	GRID_API virtual BOOL OnPasteFromClipboard(const CGXRange& rg);
	GRID_API virtual BOOL OnCheckClipboardFormat();
	GRID_API virtual BOOL CopyRange(const CGXRangeList& selList);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXExcelReadView)
public:
	GRID_API virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	GRID_API virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	GRID_API virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	GRID_API virtual ~CGXExcelReadView();
#ifdef _DEBUG
	GRID_API virtual void AssertValid() const;
	GRID_API virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGXExcelReadView)
	GRID_API afx_msg int OnCreate( LPCREATESTRUCT lpCreateStruct );
	GRID_API afx_msg LRESULT ExcelFileInitialUpdate( WPARAM, LPARAM );
	GRID_API afx_msg LRESULT ExcelFileInitialUpdateDone( WPARAM, LPARAM );
	//}}AFX_MSG
	GRID_DECLARE_MESSAGE_MAP()

// data
	CGXExcelReader* s_pExcelReader;	
};

#ifndef _DEBUG  // debug version in ExcelReadView.cpp
inline CGXExcelReadDoc* CGXExcelReadView::GetDocument()
   { return (CGXExcelReadDoc*)m_pDocument; }
#endif

////////////////////////////////////////////////////////////////
// CGXExcelReadWnd /////////////////////////////////////////////

class CGXExcelReadWnd : public CGXGridWnd, public CGXExcelGrid
{
	GRID_DECLARE_REGISTER()
	GRID_DECLARE_DYNCREATE(CGXExcelReadWnd)

// Construction
public:
	GRID_API CGXExcelReadWnd();
	GRID_API virtual ~CGXExcelReadWnd();

// overrides
	GRID_API virtual BOOL OnPasteFromClipboard(const CGXRange& rg);
	GRID_API virtual BOOL OnCheckClipboardFormat();
	GRID_API virtual BOOL CopyRange(const CGXRangeList& selList);

	GRID_API virtual void OnPreExcelReadFile();
	GRID_API virtual void OnPostExcelReadFile();

// operations
	GRID_API void ReadExcelFile(const CString& strFileName, UINT index = 0);
	GRID_API void SaveExcelFile(const CString& strFileName);

protected:
	
	//{{AFX_MSG(CGXExcelReadWnd)
	//}}AFX_MSG
	GRID_DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//
// GridMFC extension DLL
// reset declaration context
//

#if !defined(_GXNOEXTSTATE) 
#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR
#endif

#endif
