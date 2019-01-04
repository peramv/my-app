// This is a part of the Objective Grid C++ Library.
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
// Author: Stefan Hoenig
//

// gxview.h : header file
//

#ifndef _GXVIEW_H_
#define _GXVIEW_H_

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

// header file

class CGXTabWnd;
class CGXPrintDevice;

/////////////////////////////////////////////////////////////////////////////
// CGXView view

class CGXView : public CView
{
	DECLARE_DYNAMIC(CGXView)

// Constructors
protected:
	CGXView();         // protected constructor used by dynamic creation

// Attributes
public:
	BOOL    m_bOwnPD;
	CGXPrintDevice*
			m_pPD;

	// Printer Settings
public:
	CGXPrintDevice* GetPrintDevice();
	void    SetPrintDevice(CGXPrintDevice* pPD, BOOL bMustDelete = TRUE);

	// Printing support
public:
	virtual void    OnModifiedPrintDevice();
	int             DoPrintDialog(CPrintDialog* pPD);
	BOOL            DoPreparePrinting(CPrintInfo* pInfo);

protected:
	virtual BOOL    OnPreparePrinting(CPrintInfo* pInfo);
	void            UpdatePrinterDevice(CGXPrintDevice* pd);

	// Support for tabwnds
public:
	static CSplitterWnd* AFXAPI GetParentSplitter(const CWnd* pWnd, BOOL bAnyState);
	static CSplitterWnd* AFXAPI GetParentDynamicSplitter(const CWnd* pWnd, BOOL bAnyState);

	static UINT     AFXAPI GetParentTabViewID(const CWnd* pWnd);
	CScrollBar*     GetScrollBarCtrl(int nBar) const;
	CString         GetTabName();
	void            SetTabName(CString s);

// Implementation
// CView overridable member functions
protected:
	virtual ~CGXView();

	virtual void OnInitialUpdate();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXView)
	afx_msg void OnFilePrintSetup();
	afx_msg LRESULT OnChangedTab(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnNeedChangeTab(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnCanActivate(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	friend class CGXPageBreakPlugin; 
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

#endif // _GXVIEW_H_
