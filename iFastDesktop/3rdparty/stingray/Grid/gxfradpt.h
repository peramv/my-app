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

// gxfradpt.h : header file
//

#ifndef _GX_FRAME_ADPT_H__
#define _GX_FRAME_ADPT_H__

#include "grid\gxapatr.h"

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

class CGXTabCreateInfo;

class CGXFrameAdapter
{
public:
// constructor/destructor
	CGXFrameAdapter();
	virtual ~CGXFrameAdapter();

// Attributes	
	CRuntimeClass* m_pDefViewClass;
	CRuntimeClass* m_pDefDocClass;
// Operations
public:

// overrideables
	virtual LRESULT InitNewHandler(WPARAM ui = 0, LPARAM l = 0);
	virtual LRESULT InitFromFileHandler(WPARAM ui = 0, LPARAM l = 0);
	
	virtual void InsertWorkSheetHandler();
	virtual void DeleteWorkSheetHandler();
	
	virtual BOOL CanDeleteWorkSheetHandler();
	virtual BOOL CanInsertWorkSheetHandler();

	// will make a copy of the create context
	virtual BOOL HandleOnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

	// override this function to supply actual insert information
	virtual void OnChangeInsertInfo(int& nInsertBefore, CGXTabCreateInfo*& pTabCreateInfo, UINT& nID);

	// override this function if you want to make any changes to the generated tab create information
	virtual void OnChangeInitTabCreateInfo(CGXTabCreateInfo*& pTabCreateInfo);

//access
	void SetDocRuntimeClass(CRuntimeClass* pRClass);
	
	void SetViewRuntimeClass(CRuntimeClass* pRClass);
	
	void SetNumberOfTabs(int nTabs);
	
	int GetNumberOfTabs() const;
	
	CGXAppAdapter* GetApplicationAdapter() const;	

	virtual CGXTabCreateInfo* GetTabCreateInfo();
	
	virtual void CanFreeTabCreateInfo();

	virtual void GetInsertInfo(int nInsertBefore, CGXTabCreateInfo* pTabCreateInfo, UINT& nID);

	virtual CGXTabWndMgr* GetTabManager() const;

	void SetWindow(CWnd* pWnd);

	CWnd* GetWindow() const;

protected:
//data members
	CGXTabCreateInfo* m_pTabCreateInfo;
	CCreateContext* m_pContext;
	int m_nSize;
	CWnd* m_pWndPointer;
};

class CGXMDIFrameAdapter : public CGXFrameAdapter
{
public:
	CGXMDIFrameAdapter();
	virtual ~CGXMDIFrameAdapter();

//overrideables
	virtual void HandleOnNewWindow();
	virtual void HandleDestroy();
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

#endif //_GX_FRAME_ADPT_H__
