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
// gxhgfr.h : Implementation for Find/Replace in a Hierarchy Grid.

#ifndef GX_HGFRIMP_H
#define GX_HGFRIMP_H

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

class CGXGridFindReplaceImp: public CGXAbstractGridFindReplaceImp
{
public:
	virtual void OnShowFindReplaceDialog(CGXGridCore* pGrid, BOOL bFindOnly);
	virtual void OnFindNext(CGXGridCore * pGrid, LPCTSTR lpszFind, BOOL bNext, BOOL bCase);
	virtual BOOL FindText(CGXGridCore* pGrid, BOOL bSetCell);
	virtual void OnReplaceSel(CGXGridCore* pGrid, LPCTSTR lpszFind, BOOL bNext, BOOL bCase, LPCTSTR lpszReplace);
	virtual void OnReplaceAll(CGXGridCore* pGrid, LPCTSTR lpszFind, LPCTSTR lpszReplace, BOOL bCase);
	virtual void OnFindReplace(CGXGridCore* pGrid, CFindReplaceDialog* pDialog);
	virtual BOOL FindText(CGXGridCore* pGrid, ROWCOL& nRow, ROWCOL& nCol, BOOL bSetCell);
	virtual BOOL FindText(CGXControl* pControl, const GX_FR_STATE& find, ROWCOL nRow, ROWCOL nCol, BOOL bCurrentPos, BOOL bSetCell);
	virtual BOOL ReplaceAll(CGXControl* pControl, const GX_FR_STATE& find, ROWCOL nRow, ROWCOL nCol);
};

class CGXHierarchyGridFindReplaceImp : public CGXGridFindReplaceImp
{
public:
//	virtual void OnShowFindReplaceDialog(CGXGridCore* pGrid, BOOL bFindOnly);
//	virtual void OnFindNext(CGXGridCore * pGrid, LPCTSTR lpszFind, BOOL bNext, BOOL bCase);
	virtual BOOL FindText(CGXGridCore* pGrid, BOOL bSetCell);
	virtual void OnReplaceSel(CGXGridCore* pGrid, LPCTSTR lpszFind, BOOL bNext, BOOL bCase, LPCTSTR lpszReplace);
	virtual void OnReplaceAll(CGXGridCore* pGrid, LPCTSTR lpszFind, LPCTSTR lpszReplace, BOOL bCase);
	virtual void OnFindReplace(CGXGridCore* pGrid, CFindReplaceDialog* pDialog);
	virtual BOOL FindText(CGXGridCore* pGrid, ROWCOL& nRow, ROWCOL& nCol, BOOL bSetCell);
//	virtual BOOL FindText(CGXControl* pControl, const GX_FR_STATE& find, ROWCOL nRow, ROWCOL nCol, BOOL bCurrentPos, BOOL bSetCell);
//	virtual BOOL ReplaceAll(CGXControl* pControl, const GX_FR_STATE& find, ROWCOL nRow, ROWCOL nCol);

	virtual BOOL FindTextInChild(CGXGridCore* pGrid, ROWCOL nChildRow, BOOL bSetCell, BOOL bSetParent);
	virtual void ReplaceAllInChild(CGXGridCore* pGrid, ROWCOL nChildRow, LPCTSTR lpszFind, LPCTSTR lpszReplace, BOOL bCase);
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

#endif // GX_HGFRIMP_H
