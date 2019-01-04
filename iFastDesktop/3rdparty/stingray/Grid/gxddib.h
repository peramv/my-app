// This is a part of the Objective Grid CCE C++ Library.
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
// the Objective Grid CCE Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding
// the Objective

#ifndef _GXDDIB_H_
#define _GXDDIB_H_

#if _MFC_VER >= 0x0400 

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


class CGXDataDib : public CGXDIB 
{
public:
// constructor 
	CGXDataDib();
	virtual ~CGXDataDib();
	
	static HANDLE AFXAPI Draw(CDC* pDC, const COleVariant& var, LPRECT lpRect, int nStretchFlags = none, 
		UINT ntAlign = DT_TOP|DT_LEFT, LPRECT lpSrc = NULL, HANDLE hBitmap = NULL, BOOL bFree = FALSE);
	
	// locate the actual bitmap data in a buffer
	static HANDLE AFXAPI LocateBitmap(const COleVariant& var, BOOL bIncludeFileHeader = FALSE);
};

//
// GridMFC extension DLL
// reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif //_MFC_VER >= 0x0400 

#endif //_GXDDIB_H_
