// This is a part of the Objective Grid C++ Library.
// Copyright � 1999-2004 Quovadx, Inc.  All Rights Reserved.
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
//          Supplement Section 227.7202, Government�s use, duplication or 
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

// gxapatr.h : header file
//

#ifndef _GX_AP_ATR_H__
#define _GX_AP_ATR_H__

#include <afxtempl.h>
#include "grid\gxman.h"

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


// forward decl for CGXTabWndMgr

class CGXTabWndMgr;

// Your application class will inherit from this class or a class derived from this class. This class
// establishes the following essential links

// 1) The link between the frame that is used and the tab manager that is to be used. The relationship
// betwen the two can be established by overidding GetTabManager. This will return (by default) an instance
// of CGXTabWndMgr

// 2) The link betwen view, doc classes and the document template that is to be used for managing them. This relationship
// is established by the GetDoctemplate override. This function always needs to be overriden either in your application
// class or in your derived CGXAppAdapter class

class CGXAppAdapter
{
public:

// constructors / destructor
	CGXAppAdapter();
	virtual ~CGXAppAdapter();

// access
	virtual CGXTabWndMgr* GetTabManager(CRuntimeClass* pRClass, CDocument* pDocument);
	virtual void RemoveTabManager(CRuntimeClass* pRClass, CDocument* pDocument);

	virtual CDocTemplate* GetDocTemplate(CRuntimeClass* pViewClass, CRuntimeClass* pDocClass) = 0;
	virtual CDocTemplate* GetDocTemplate(CCreateContext* pContext);

	virtual CGXNodeManager<CGXTabWndMgr>* CreateTabWndHolder();

// implementation
protected:
	CGXNodeManager<CGXTabWndMgr>* m_pTabWndHolder;
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
#endif 
