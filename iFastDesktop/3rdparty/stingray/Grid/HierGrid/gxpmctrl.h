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
// gxpmctrl.h

// This file contains declaration for the CGXPMControl

#ifndef GX_PMCONTROL
#define GX_PMCONTROL

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

class CGXPMControl : public CGXControl
{
	DECLARE_CONTROL(CGXPMControl)
public:
	// Constructor and destructor
	CGXPMControl(CGXGridCore* pGrid);
	virtual ~CGXPMControl();

	enum Alignment{top, bottom, left, right, center};

	BOOL CreateControl(int nID);

	// Class members
	int m_nAlignment;
	int m_nState;
	int m_nLogicalCenter;	// Used while drawing the expanded state; Specifies the height
							// of the top portion  of the cell within which the PMBox will be centered.

	// CGXControl overrides
	// Operations
	virtual void DrawPMBox(CDC* pDC, CRect& outRect, const CGXStyle& style);
	virtual void Draw(CDC* pDC, CRect rect, ROWCOL nRow, ROWCOL nCol, const CGXStyle& style, const CGXStyle* pStandardStyle);
	virtual void Init(ROWCOL nRow, ROWCOL nCol);
	virtual void SetValue(LPCTSTR pszRawValue);
	virtual BOOL GetValue(CString& strResult);
	// virtual BOOL GetControlText(CString& strResult, ROWCOL nRow, ROWCOL nCol, LPCTSTR pszRawValue, const CGXStyle& style);
};

//
// GridMFC extension DLL
// reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif //GX_PMCONTROL
