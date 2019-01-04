// This is a part of the Objective Grid Pro C++ Library.
// Copyright © 1999-2004 Quovadx, Inc.  All Rights Reserved.
// 
// 
// This computer software is owned by Quovadx, Inc. and is protected by 
// U.S. copyright laws and other laws and by international treaties. This 
// computer software is furnished by Quovadx, Inc. pursuant to a written 
// license agreement and may be used, copied, transmitted, and stored 
// only in accordance with the terms of such license agreement and with 
// the inclusion of the above copyright notice.  This computer software or 
// any other copies thereof may not be provided or otherwise made available 
// to any other person.
// 
// U.S. Government Restricted Rights.  This computer software: 
//      (a) was developed at private expense and is in all respects the 
//          proprietary information of Quovadx, Inc.; 
//      (b) was not developed with government funds; 
//      (c) is a trade secret of Quovadx, Inc. for all purposes of the 
//          Freedom of Information Act; and 
//      (d) is a commercial item and thus, pursuant to Section 12.212 
//          of the Federal Acquisition Regulations (FAR) and DFAR 
//          Supplement Section 227.7202, Government’s use, duplication or 
//          disclosure of the computer software is subject to the restrictions 
//          set forth by Quovadx, Inc.
//
//
// This source code is only intended as a supplement to
// the Objective Grid Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding
// the Objective Grid product.
//
// Author: Daniel Jebaraj
//
// "gxrdvw.h" : interface of the CGXExcelReadView class
//
/////////////////////////////////////////////////////////////////////////////
//const int gxnFirstCtrl = 101;

#ifndef _GX_RD_VW_H__
#define _GX_RD_VW_H__

#ifndef _GX_EX_EX_BASE_H__
#include "grid\gxexbse.h"
#endif

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
	CGXExcelReadView();
	DECLARE_SERIAL(CGXExcelReadView)

// Attributes
public:
	CGXExcelReadDoc* GetDocument();

// Operations
public:

// overrides
	virtual void OnExcelFileInitialUpdate();
	virtual void OnExcelFileInitialUpdateDone();
	virtual void OnInitializeNewFile();
	
	virtual BOOL OnPasteFromClipboard(const CGXRange& rg);
	virtual BOOL OnCheckClipboardFormat();
	virtual BOOL CopyRange(const CGXRangeList& selList);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXExcelReadView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGXExcelReadView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGXExcelReadView)
	afx_msg int OnCreate( LPCREATESTRUCT lpCreateStruct );
	afx_msg LRESULT ExcelFileInitialUpdate( WPARAM, LPARAM );
	afx_msg LRESULT ExcelFileInitialUpdateDone( WPARAM, LPARAM );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

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
	DECLARE_REGISTER()
	DECLARE_DYNCREATE(CGXExcelReadWnd)

// Construction
public:
	CGXExcelReadWnd();
	virtual ~CGXExcelReadWnd();

// overrides
	virtual BOOL OnPasteFromClipboard(const CGXRange& rg);
	virtual BOOL OnCheckClipboardFormat();
	virtual BOOL CopyRange(const CGXRangeList& selList);

	virtual void OnPreExcelReadFile();
	virtual void OnPostExcelReadFile();

// operations
	void ReadExcelFile(const CString& strFileName, UINT index = 0);
	void SaveExcelFile(const CString& strFileName);

protected:
	
	//{{AFX_MSG(CGXExcelReadWnd)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
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
