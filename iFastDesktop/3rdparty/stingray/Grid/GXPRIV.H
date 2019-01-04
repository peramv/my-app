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

// gxpriv.h : header file
//

#ifndef _GXPRIV_H_
#define _GXPRIV_H_

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


// column title row

class CGXTabbedLBoxHeader : public CWnd
{
// Construction
public:
	CGXTabbedLBoxHeader();
	BOOL CreateHeader(CWnd* pParent);

// Attributes
public:
	BOOL m_bDispAllCols;
	int m_nDisplayCol;
	int m_iTabCount;
	LPINT m_piarTabStops;
	CFont* m_pFont;

	CString m_strTitles;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXTabbedLBoxHeader)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGXTabbedLBoxHeader();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXTabbedLBoxHeader)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

class CGXTabbedLBoxImp
{
public:
	static void AFXAPI DrawItem(CDC* pDC,
		const CRect& rcItem,
		const CString& strLBEntry,
		BOOL bOnlyDisplayCol,
		int nDisplayCol,
		int nTabCount,
		LPINT piarTabStops,
		COLORREF rgbGridLine,
		COLORREF rgbBack,
		COLORREF rgbText);

	static void AFXAPI MeasureHeight(const CString& strLBEntry,
		unsigned int& nItemHeight,
		BOOL bOnlyDisplayCol,
		int nDisplayCol,
		int nTabCount);

	static void AFXAPI DetermineMaxColWidth(CDC* pDC, LPCTSTR pszCol, int nColCount, LPINT anMaxColWidth);
};

#define GX_TABNMAXCOLS 10


#ifndef WS_EX_TOOLWINDOW
#define WS_EX_TOOLWINDOW (GXGetAppData()->bWin4?0x00000080L:0L)
#endif

class CGXDragLineWnd: public CWnd
{
public:
	CGXDragLineWnd(CGXGridCore* pGrid);
	BOOL CreateWnd(CWnd* pParent);

public:
	CGXGridCore* m_pGrid;
	CGXPen m_pen;

	// optional parameters passed to DrawGridLine
	int m_type;
	ROWCOL m_nClientRC;
	UINT m_flags;

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXDragLineWnd)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

// definitions 
#define GX_CRIT_DYNLINKLIST    0

#define GX_CRIT_RUNTIMECLASSLIST   0

#define GX_CRIT_OBJECTFACTORYLIST  0

#define GX_CRIT_LOCKSHARED 0

// determine number of elements in an array (not bytes)
#define _gxcountof(array) (sizeof(array)/sizeof(array[0]))




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

#endif // _GXPRIV_H_
