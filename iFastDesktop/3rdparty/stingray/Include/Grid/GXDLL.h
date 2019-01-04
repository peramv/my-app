///////////////////////////////////////////////////////////////////////////////
// GXDLL.h
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

	// return OG DLL Resource Handle
extern GRID_API HINSTANCE AFXAPI GXGetResourceHandle();

#if _MFC_VER >= 0x0400

// Support for OG language Dll's (MFC 4.x only)

class CGXLangDll
{
public:
	GRID_API CGXLangDll();
	GRID_API ~CGXLangDll();

	// [VC7] Return types corrected to BOOL to match implementations.
	GRID_API BOOL Load(LPCTSTR pszLang, LPCTSTR pszPath);
	GRID_API BOOL Free();

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
