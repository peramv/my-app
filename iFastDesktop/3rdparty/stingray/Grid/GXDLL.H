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

// gxdll.h : header file

#ifndef _GXDLL_H_
#define _GXDLL_H_

#ifdef _GXEXT
#undef _GXDLL
#define _GXDLL
#endif

#ifdef _GXDLL

#ifndef GX_DATAEXT
	#define GX_DATAEXT     AFX_DATA_IMPORT
	#define GX_DATADEF
#endif

#ifndef _GXCOLL_H_
#include "grid\gxcoll.h"
#endif

#ifndef _GXSTATE_H_
#include "grid\gxstate.h"
#endif

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

	// return OG DLL Resource Handle
extern HINSTANCE AFXAPI GXGetResourceHandle();

#if _MFC_VER >= 0x0400

// Support for OG language Dll's (MFC 4.x only)

class CGXLangDll
{
public:
	CGXLangDll();
	~CGXLangDll();

	// [VC7] Return types corrected to BOOL to match implementations.
	BOOL Load(LPCTSTR pszLang, LPCTSTR pszPath);
	BOOL Free();

private:
	 HINSTANCE m_hLangDll;
	 HINSTANCE m_hOldLang;
	 HINSTANCE m_hOldRes;
};

#endif

//
// GridMFC extension DLL
// reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

//

#else // _GXDLL

	// not using OG DLL, so I should return the Afx Resource Handle
#define GXGetResourceHandle AfxGetResourceHandle

#endif // _GXDLL

#endif // _GXDLL_H_

/////////////////////////////////////////////////////////////////////////////
