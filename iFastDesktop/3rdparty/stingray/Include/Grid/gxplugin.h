///////////////////////////////////////////////////////////////////////////////
// gxplugin.h : Interface of the CGXPluginComponent class
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
//          Supplement Section 227.7202, Government’s use, duplication or
//          disclosure of the computer software is subject to the restrictions
//          set forth by Rogue Wave Software, Inc.
//
///////////////////////////////////////////////////////////////////////////////
//
// Author: Stefan Hoenig
//

#ifndef _GXPLUGIN_H_
#define _GXPLUGIN_H_

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

class CGXPluginComponent: public CWnd
{
	GRID_DECLARE_DYNAMIC(CGXPluginComponent);

public:
	GRID_API CGXPluginComponent();
	GRID_API virtual BOOL PlugIn(CWnd* pParentWnd);
	GRID_API virtual ~CGXPluginComponent();

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
	GRID_DECLARE_MESSAGE_MAP()

public:
	// for processing Windows messages
	GRID_API BOOL HandleMessage(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);

protected:
	// for handling default processing
	GRID_API virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);

#ifdef _DEBUG
	GRID_API virtual void AssertValid() const;
	GRID_API virtual void Dump(CDumpContext& dc) const;
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
