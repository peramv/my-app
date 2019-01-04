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

//
// gxplugin.h : interface of the CGXPluginComponent class

#ifndef _GXPLUGIN_H_
#define _GXPLUGIN_H_

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

class CGXPluginComponent: public CWnd
{
	DECLARE_DYNAMIC(CGXPluginComponent);

public:
	CGXPluginComponent();
	virtual BOOL PlugIn(CWnd* pParentWnd);
	virtual ~CGXPluginComponent();

public:
	// Attributes 
	// Reserved for later usage with a PluginManager
	BOOL m_bSkipOtherPlugins;	// set this TRUE from within your message handler
								// if no other plugins should be called	for this message
	BOOL m_bExitMesssage;		// set this TRUE from within your message handler        
								// if no other plugins and also not the default window message 
								// should be called

// Generated message map functions
protected:
	//{{AFX_MSG(CGXPluginComponent)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	// for processing Windows messages
	BOOL HandleMessage(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);

protected:
	// for handling default processing
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

#define CGXPlugInComponent CGXPluginComponent	// for backward compatibility

//
// GridMFC extension DLL
// reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

//

#endif //_GXPLUGIN_H_
