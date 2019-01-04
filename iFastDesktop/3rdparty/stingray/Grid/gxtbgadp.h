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
// Author: Daniel Jebaraj
//

// gxtbgadp.h : header file
//

#ifndef _GX_TB_GRD_ADAPT_H__
#define _GX_TB_GRD_ADAPT_H__

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


// Begin CGXTabWndMgr implementation

class CGXGridTabWndAdapter : public CGXTabWndAdapter 
{
public:
	CGXGridTabWndAdapter();

	virtual ~CGXGridTabWndAdapter();

// interface that will be used by CGXTabWndMgr
	
// access
	// this will be called by CGXTabWndMgr to pass in the parent for the window
	// you can use this to create a window (as a child) or to simply render
	virtual void SetParentWnd(CWnd* pParentWnd);
	
	// return the parent window passed in.
	virtual CWnd* GetParentWnd() const;
	
	// return the correct tab count
	virtual int GetTabCount() const;
	
	virtual int GetCursel() const;

	CGXTabWnd* GetTabWnd() const
	{return m_pTabWnd;}

// view creation
	// view creation interface
	virtual CWnd* CreateView(CRuntimeClass* pViewRuntimeClass, const TCHAR* pszLabel, CCreateContext* pContextDefault);

	//tab window creation interface
	virtual BOOL Create(const TCHAR* pszLabel, CCreateContext* pCreateContext);
	
	// return a meaningful default label
	virtual CString GenerateLabel(UINT nID = 0);
	
	virtual BOOL InsertWorkSheet(int nInsertBefore, CRuntimeClass* pViewRuntimeClass, CCreateContext* pContext, const TCHAR* pszLabel = 0, UINT nID = 0);
	
	virtual BOOL DeleteWorksheet(int nDeleteIndex);

	virtual BOOL CanInsertWorkSheet() const;
	
	virtual BOOL CanDeleteWorkSheet() const;
	
	
// maintenance	
	// perform clean up as appropriate. Do a 'delete this' if this object was allocated on the heap
	virtual void Destroy();
	
protected:
	//data
	CGXTabWnd* m_pTabWnd;
	CWnd* m_pParentWnd;

// static members
	static CWnd* SpecialTabWndCreate(CGXTabWnd* pTabWnd, CRuntimeClass* pViewClass,  BOOL& bSendInitialUpdate,  CCreateContext* pContext, LPCTSTR szLabel = NULL, UINT nID = 0);
};

//
// GridMFC extension DLL
// reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

//

#endif //_GX_TB_GRD_ADAPT_H__
