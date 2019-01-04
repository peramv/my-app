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

#ifndef _GXDELAYR_H_
#define _GXDELAYR_H_

#ifndef _GXCORE_H_
#include "grid\gxcore.h"
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

/////////////////////////////////////////////////////////////////////
// class CGXDelayedRange

class CGXDelayedRange: public CObject
{
	DECLARE_SERIAL(CGXDelayedRange);

public:
	CGXDelayedRange();

	// Range to be checked
	CGXRange m_range;

	// Done row intervals
	CDWordArray m_awLastRow;
	CDWordArray m_awFirstRow;

	BOOL m_bResolved;

	BOOL ResolveRange(CGXRange& rg);
	void SetEmpty();
	virtual void Serialize(CArchive& ar);
	virtual void operator=(const CGXDelayedRange& other);
};

/////////////////////////////////////////////////////////////////////
// class CGXDelayedRangePool

class CGXDelayedRangePool: public CObject
{
	DECLARE_SERIAL(CGXDelayedRangePool);

public:
	CGXDelayedRangePool();

	static void AFXAPI ImplementDelayedRangePool();
	CObArray m_argDelayed;  // array of CGXDelayedRange objects

	// Grid Operations
	BOOL EvalRows(const CGXRange& range, CDWordArray &dwColStart, CDWordArray &dwColEnd);
	void DelayRange(const CGXRange& range);
	void CleanUp();
	void MakeEmpty();
	void SetRowCount(ROWCOL nMaxRow);
	void SetColCount(ROWCOL nMaxCol);

	// Implementation (EvalRows helper)
	void SplitDelayedRange(const CGXRange& range);

	// Serialization
	virtual void Serialize(CArchive& ar);
	virtual CGXDelayedRangePool& operator=(const CGXDelayedRangePool& pool);

	// Destructor
	virtual ~CGXDelayedRangePool();
};

/////////////////////////////////////////////////////////////////////////////
// class CGXDWordArrayPtrArray

// type-safe CPtrArray for array with CDWordArray objects

class CGXDWordArrayPtrArray: public CPtrArray
{
	DECLARE_DYNAMIC(CGXDWordArrayPtrArray)

public:
	// Construcion/Destruction
	CGXDWordArrayPtrArray();
	virtual ~CGXDWordArrayPtrArray();
		// destructor automatically deletes all referenced objects

	void DeleteAll();   // delete all referenced objects
	void DeleteAt(int nIndex, int nCount = 1);
	void Move(int nIndex, int nCount, int nDest);

	virtual void Serialize(CArchive& ar);
	virtual CGXDWordArrayPtrArray& operator=(const CGXDWordArrayPtrArray& ar);

public:
	// Accessing elements
	CDWordArray* GetAt(int nIndex) const;
	void SetAt(int nIndex, CDWordArray* newElement);

	// Potentially growing the array
	void SetAtGrow(int nIndex, CDWordArray* newElement);
	int Add(CDWordArray* newElement);

	// overloaded operator helpers
	CDWordArray* operator[](int nIndex) const;
	CDWordArray*& operator[](int nIndex);

	// Operations that move elements around
	void InsertAt(int nIndex, CDWordArray* newElement, int nCount = 1);
	void InsertAt(int nStartIndex, CGXDWordArrayPtrArray* pNewArray);

	BOOL InsertRows(ROWCOL nRow, ROWCOL nCount);
	BOOL RemoveRows(ROWCOL nFromRow, ROWCOL nToRow);
	BOOL MoveRows(ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow);
	BOOL InsertCols(ROWCOL nCol, ROWCOL nCount);
	BOOL RemoveCols(ROWCOL nFromCol, ROWCOL nToCol);
	BOOL MoveCols(ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nDestCol);
};

/////////////////////////////////////////////////////////////////////////////
// class CGXSpanCellPool

class CGXSpanCellPool: public CObject
{
	DECLARE_SERIAL(CGXSpanCellPool);

public:
	CGXSpanCellPool();

	static void AFXAPI ImplementSpanCellPool();


	// Range to be checked
	CGXDWordArrayPtrArray   m_SpanRows;
	CGXDWordArrayPtrArray   m_SpanCols;

	virtual BOOL GetSpanCellsRowCol(ROWCOL nRow, ROWCOL nCol, CGXRange& rg);
	virtual BOOL StoreSpanCellsRowCol(ROWCOL nRow, ROWCOL nCol, ROWCOL nToRow, ROWCOL nToCol, BOOL bSet);

	void InitFromRangeList(const CGXRangeList* pRangeList);

	virtual void InsertRows(ROWCOL nRow, ROWCOL nCount);
	virtual void RemoveRows(ROWCOL nFromRow, ROWCOL nToRow);
	virtual void MoveRows(ROWCOL nFromRow, ROWCOL nToRow, ROWCOL nDestRow);
	virtual void InsertCols(ROWCOL nCol, ROWCOL nCount);
	virtual void RemoveCols(ROWCOL nFromCol, ROWCOL nToCol);
	virtual void MoveCols(ROWCOL nFromCol, ROWCOL nToCol, ROWCOL nDestCol);

	void MakeEmpty();

	virtual void Serialize(CArchive& ar);
	virtual CGXSpanCellPool& operator=(const CGXSpanCellPool& pool);
};

/////////////////////////////////////////////////////////////////////////////
// Inline function declarations

#ifdef _GX_ENABLE_INLINES
#include "grid\gxdelayr.inl"
#endif

/////////////////////////////////////////////////////////////////////////////

//
// GridMFC extension DLL
// reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

//

#endif // _GXDELAYR_H_
