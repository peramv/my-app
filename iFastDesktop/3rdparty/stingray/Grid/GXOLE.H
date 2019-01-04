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
// Authors: Daniel Jebaraj, Stefan Hoenig
//

// gxole.h : header file
//

#ifndef _GXOLE_H_
#define _GXOLE_H_

#if ! ( defined(_GX_VER) && _GX_VER >= 0x0903 )
#pragma message( "Please make sure that you include Objective Grid 9.03 header files")
#pragma message( "or a later version and not an older version header files!")
Fatal error!
#endif

// compile this file only if OLE is supported
#if _MFC_VER >= 0x0400 && !defined(_AFX_NO_OLE_SUPPORT)

// include decls for base class

#ifndef _GXABSTR_H_
#include "grid\gxabstr.h"
#endif

#ifndef _GXCORE_H_
#include "grid\gxcore.h"
#endif

#ifndef _AFXOLE_H_
#include <afxole.h>
#endif

//
// GridMFC Extension DLL
// initialize declaration context
//

#ifdef _GXDLL
	#undef AFX_DATA
	#define AFX_DATA    GX_DATAEXT
#endif

// header file


// CGXGridDropTarget
//
// A CGXGridDropTarget object provides the communication mechanism between
// a grid (either CView or CWnd) and the OLE libraries. Creating an object
// of this class allows a window to accept data through the OLE drag-and-drop
// mechanism.
//

class CGXGridDropTarget : public COleDropTarget
{
// Constructors
public:
	CGXGridDropTarget();

// Operations
	BOOL Register(CGXGridCore* pGrid, DWORD dwFlags = GX_DNDEGDESCROLL|GX_DNDAUTOSCROLL|GX_DNDTEXT|GX_DNDSTYLES);

// Overridables
	virtual DROPEFFECT OnDragEnter(CWnd* pWnd, COleDataObject* pDataObject,
		DWORD dwKeyState, CPoint point);
	virtual DROPEFFECT OnDragOver(CWnd* pWnd, COleDataObject* pDataObject,
		DWORD dwKeyState, CPoint point);
	virtual BOOL OnDrop(CWnd* pWnd, COleDataObject* pDataObject,
		DROPEFFECT dropEffect, CPoint point);
	virtual DROPEFFECT OnDropEx(CWnd* pWnd, COleDataObject* pDataObject,
		DROPEFFECT dropDefault, DROPEFFECT dropList, CPoint point);
	virtual void OnDragLeave(CWnd* pWnd);
	virtual DROPEFFECT OnDragScroll(CWnd* pWnd, DWORD dwKeyState,
		CPoint point);

// Implementation
public:
	virtual ~CGXGridDropTarget();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CGXGridCore* m_pGrid;
};

// CGXOleDataObjectProxy
//
// CGXOleDataObjectProxy will be instantiated from the CGXGridDropTarget
// class and will forward calls to the embedded COleDataObject
//
// See gxcore.h for declararation of the abstract
// CGXNoOleDataObjectProxy base class.

class CGXOleDataObjectProxy: public CGXNoOleDataObjectProxy
{
public:
	CGXOleDataObjectProxy(COleDataObject* pDataObject = NULL, BOOL bAutoDelete = FALSE);

	virtual ~CGXOleDataObjectProxy();

	virtual BOOL GetData(CLIPFORMAT cfFormat, LPSTGMEDIUM lpStgMedium,
		LPFORMATETC lpFormatEtc = NULL);

	virtual BOOL IsDataAvailable(CLIPFORMAT cfFormat, LPFORMATETC lpFormatEtc = NULL);

	COleDataObject* GetOleDataObject() const;

protected:
	COleDataObject* m_pDataObject;
	BOOL m_bAutoDelete;
};

class CGXGridDropTargetPlugin: public CGXPluginComponent, public CGXAbstractGridDropTargetImp
{
	DECLARE_DYNAMIC(CGXGridDropTargetPlugin);

public:
	CGXGridDropTargetPlugin(CGXGridCore* pGrid);
	virtual ~CGXGridDropTargetPlugin();
	virtual BOOL PlugIn(CWnd* pParentWnd);

public:
	// GridCore overrides
	// overridables for drop target
	virtual BOOL OnDndCalculateFocusRect(CGXGridCore* pGrid, CGXNoOleDataObjectProxy* pOleDataObjectProxy, ROWCOL& nRowExt, ROWCOL& nColExt);
	virtual BOOL OnDndQueryAcceptData(CGXGridCore* pGrid, CGXNoOleDataObjectProxy* pDataObject);
	virtual BOOL OnDndDropData(CGXGridCore* pGrid, CGXNoOleDataObjectProxy* pDataObject, ROWCOL nRow, ROWCOL nCol);

	// support for drop target, functions called from CGXGridDropTarget
	virtual DROPEFFECT OnGridDragEnter(CGXGridCore* pGrid, CGXNoOleDataObjectProxy* pDataObject, DWORD dwKeyState, CPoint point);
	virtual DROPEFFECT OnGridDragOver(CGXGridCore* pGrid, CGXNoOleDataObjectProxy* pDataObject, DWORD dwKeyState, CPoint point);
	virtual void OnGridDragLeave(CGXGridCore* pGrid);
	virtual BOOL OnGridDrop(CGXGridCore* pGrid, CGXNoOleDataObjectProxy* pDataObject, DROPEFFECT dropEffect, CPoint point);
	virtual DROPEFFECT OnGridDropEx(CGXGridCore* pGrid, CGXNoOleDataObjectProxy* pDataObject, DROPEFFECT dropDefault, DROPEFFECT dropList, CPoint point);
	virtual DROPEFFECT OnGridDragScroll(CGXGridCore* pGrid, DWORD dwKeyState, CPoint point);

	// helpers for drop target
	virtual void DndDrawMoveRect(CGXGridCore* pGrid, CPoint point, BOOL bEraseOld, BOOL bDrawNew);
	virtual BOOL DoDragScroll(CGXGridCore* pGrid, CPoint point);
	virtual BOOL IsOverAnotherApplication(CGXGridCore* pGrid, POINT point);

	// Attributes
	CGXGridCore* m_pGrid;
	CGXGridDropTarget* m_pobjDndDropTarget;

// Generated message map functions
protected:
	//{{AFX_MSG(CGXGridDropTargetPlugin)
	afx_msg void OnTimer(SEC_UINT nIDEvent);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CGXOleDataSourceProxy
//

class CGXOleDataSourceProxy: public CGXNoOleDataSourceProxy
{
public:
	CGXOleDataSourceProxy(COleDataSource* pDataSource = NULL, BOOL bAutoDelete = FALSE);

	virtual ~CGXOleDataSourceProxy();

	// CacheData & DelayRenderData operations similar to ::SetClipboardData
	virtual void CacheGlobalData(CLIPFORMAT cfFormat, HGLOBAL hGlobal,
		LPFORMATETC lpFormatEtc = NULL);    // for HGLOBAL based data

	// Clipboard and Drag/Drop access
	virtual DROPEFFECT DoDragDrop(
		DWORD dwEffects = DROPEFFECT_COPY|DROPEFFECT_MOVE|DROPEFFECT_LINK,
		LPCRECT lpRectStartDrag = NULL,
		COleDropSource* pDropSource = NULL);

	virtual void Empty();   // empty cache (similar to ::EmptyClipboard)

	COleDataSource* GetOleDataSource() const;

	// CGXGridCore Overridables
	virtual BOOL DndStartDragDrop(CGXGridCore* pGrid, ROWCOL nRow, ROWCOL nCol);
	virtual BOOL OnDndCacheGlobalData(CGXGridCore* pGrid, CGXNoOleDataSourceProxy* pSrcItem, const CGXRangeList& selList, ROWCOL& nDndRowExt, ROWCOL& nDndColExt);

protected:
	COleDataSource* m_pDataSource;
	BOOL m_bAutoDelete;
};

/////////////////////////////////////////////////////////////////////////////


//
// GridMFC extension DLL
// reset declaration context
//

#undef AFX_DATA
#define AFX_DATA

#endif

//

#endif // _GXOLE_H_
