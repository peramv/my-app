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
// gxexfrm.h : interface of the CGXExcelChildFrame class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _GX_EX_FRM_H__
#define _GX_EX_FRM_H__

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


#include "grid\gxchfrm.h"

class CGXExcelChildFrame : public CGXWChildFrame
{
	DECLARE_DYNCREATE(CGXExcelChildFrame)
public:
	CGXExcelChildFrame();

// Attributes
public:

// Operations
public:

// Overrides
	virtual LRESULT InitNewHandler(WPARAM ui = 0, LPARAM l = 0);
	virtual LRESULT InitFromFileHandler(WPARAM wParam, LPARAM lParam);
	virtual void OnChangeInitTabCreateInfo(CGXTabCreateInfo*& pInfo);

	virtual void InsertWorkSheetHandler();
	virtual void DeleteWorkSheetHandler();

	virtual void HandleOnNewWindow();

	virtual void HandleDestroy();

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGXExcelChildFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGXExcelChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CGXExcelChildFrame)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	int m_nPrimary;
};


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

#endif //_GX_EX_FRM_H__

/////////////////////////////////////////////////////////////////////////////
