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

// gxcoll.h : header file
//

#ifndef _GXCOLL_H_
#define _GXCOLL_H_

#ifndef __AFX_H__
#include <afx.h>
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

// classes declared in this header file:

class CGXNDX;
class CGXCollMapDWordToString;	// CGXStylesMap: m_ControlMap, AppendOG5Map
class CGXCollMapDWordToLong;	// 
class CGXCollMapDWordToPtr;		// User property info map: m_UserPropertyInfoMap
class CMapNdxToOb;		
class CGXCollMapStringToWord;   // base styles: m_mswNameId
class CGXMapDWordToLong;		// row heights: m_RowHeights
class CGXMapCellToOb;

class GXNDX
{
public:
	// construction
	GXNDX();
	GXNDX(const GXNDX& r);
	GXNDX(ROWCOL r, ROWCOL c);

	operator DWORD();

	// assignment
	const GXNDX& operator=(const GXNDX& r);

	// data
	ROWCOL  nRow;
	ROWCOL  nCol;
};

// Row, Col (ROWCOL) to GXNDX Index
GXNDX     AFXAPI RowColToNdx(ROWCOL nRow, ROWCOL nCol);
ROWCOL    AFXAPI NdxToRow(GXNDX Ndx);
ROWCOL    AFXAPI NdxToCol(GXNDX Ndx);
BOOL AFXAPI operator==(const GXNDX& rc1, const GXNDX& rc2);
BOOL AFXAPI operator!=(const GXNDX& rc1, const GXNDX& rc2);
CArchive& AFXAPI operator <<(CArchive& ar, const GXNDX& ndx);
CArchive& AFXAPI operator >>(CArchive& ar, GXNDX& ndx);


#ifdef AFX_COLL_SEG
#pragma code_seg(AFX_COLL_SEG)
#endif

struct CGXPlex    // warning variable length structure
{
	CGXPlex* pNext;
	UINT nMax;
	UINT nCur;
	/* BYTE data[maxNum*elementSize]; */

	void* data() { return this+1; }

	static CGXPlex* PASCAL Create(CGXPlex*& head, UINT nMax, UINT cbElement);
			// like 'calloc' but no zero fill
			// may throw memory exceptions

	void FreeDataChain();       // free this one and links
};

#ifdef AFX_COLL_SEG
#pragma code_seg()
#endif

/////////////////////////////////////////////////////////////////////////////

class CGXCollMapDWordToString : public CObject
{

	DECLARE_SERIAL(CGXCollMapDWordToString)
protected:
	// Association
	struct CAssoc
	{
		CAssoc* pNext;
		UINT nHashValue;  // needed for efficient iteration
		DWORD key;
		CString value;
	};
public:

// Construction
	CGXCollMapDWordToString(int nBlockSize=10);

// Attributes
	// number of elements
	int GetCount() const;
	BOOL IsEmpty() const;

	// Lookup
	BOOL Lookup(DWORD key, CString& rValue) const;

// Operations
	// Lookup and add if not there
	CString& operator[](DWORD key);

	// add a new (key, value) pair
	void SetAt(DWORD key, LPCTSTR newValue);

	// removing existing (key, ?) pair
	BOOL RemoveKey(DWORD key);
	void RemoveAll();

	// iterating all (key, value) pairs
	POSITION GetStartPosition() const;
	void GetNextAssoc(POSITION& rNextPosition, DWORD& rKey, CString& rValue) const;

	// advanced features for derived classes
	UINT GetHashTableSize() const;
	void InitHashTable(UINT hashSize);

// Overridables: special non-virtual (see map implementation for details)
	// Routine used to user-provided hash keys
	UINT HashKey(DWORD key) const;

// Implementation
protected:
	CAssoc** m_pHashTable;
	UINT m_nHashTableSize;
	int m_nCount;
	CAssoc* m_pFreeList;
	struct CGXPlex* m_pBlocks;
	int m_nBlockSize;

	CAssoc* NewAssoc();
	void FreeAssoc(CAssoc*);
	CAssoc* GetAssocAt(DWORD, UINT&) const;

public:
	virtual ~CGXCollMapDWordToString();

	void Serialize(CArchive&);
#ifdef _DEBUG
	void Dump(CDumpContext&) const;
	void AssertValid() const;
#endif
};

/////////////////////////////////////////////////////////////////////////////

class CGXCollMapDWordToLong : public CObject
{

	DECLARE_SERIAL(CGXCollMapDWordToLong)
protected:
	// Association
	struct CAssoc
	{
		CAssoc* pNext;
		UINT nHashValue;  // needed for efficient iteration
		DWORD key;
		LONG value;
	};
public:

// Construction
	CGXCollMapDWordToLong(int nBlockSize=10);

// Attributes
	// number of elements
	int GetCount() const;
	BOOL IsEmpty() const;

	// Lookup
	BOOL Lookup(DWORD key, LONG& rValue) const;

// Operations
	// Lookup and add if not there
	LONG& operator[](DWORD key);

	// add a new (key, value) pair
	void SetAt(DWORD key, LONG newValue);

	// removing existing (key, ?) pair
	BOOL RemoveKey(DWORD key);
	void RemoveAll();

	// iterating all (key, value) pairs
	POSITION GetStartPosition() const;
	void GetNextAssoc(POSITION& rNextPosition, DWORD& rKey, LONG& rValue) const;

	// advanced features for derived classes
	UINT GetHashTableSize() const;
	void InitHashTable(UINT hashSize);

// Overridables: special non-virtual (see map implementation for details)
	// Routine used to user-provided hash keys
	UINT HashKey(DWORD key) const;

// Implementation
protected:
	CAssoc** m_pHashTable;
	UINT m_nHashTableSize;
	int m_nCount;
	CAssoc* m_pFreeList;
	struct CGXPlex* m_pBlocks;
	int m_nBlockSize;

	CAssoc* NewAssoc();
	void FreeAssoc(CAssoc*);
	CAssoc* GetAssocAt(DWORD, UINT&) const;

public:
	virtual ~CGXCollMapDWordToLong();

	void Serialize(CArchive&);
#ifdef _DEBUG
	void Dump(CDumpContext&) const;
	void AssertValid() const;
#endif
	friend class CGXCollMapDWordToLongFTR;
};


/////////////////////////////////////////////////////////////////////////////

class CGXCollMapDWordToPtr : public CObject
{

	DECLARE_DYNAMIC(CGXCollMapDWordToPtr)
protected:
	// Association
	struct CAssoc
	{
		CAssoc* pNext;
		UINT nHashValue;  // needed for efficient iteration
		DWORD key;
		void* value;
	};

public:

// Construction
	CGXCollMapDWordToPtr(int nBlockSize = 10);

// Attributes
	// number of elements
	int GetCount() const;
	BOOL IsEmpty() const;

	// Lookup
	BOOL Lookup(DWORD key, void*& rValue) const;

// Operations
	// Lookup and add if not there
	void*& operator[](DWORD key);

	// add a new (key, value) pair
	void SetAt(DWORD key, void* newValue);

	// removing existing (key, ?) pair
	BOOL RemoveKey(DWORD key);
	void RemoveAll();

	// iterating all (key, value) pairs
	POSITION GetStartPosition() const;
	void GetNextAssoc(POSITION& rNextPosition, DWORD& rKey, void*& rValue) const;

	// advanced features for derived classes
	UINT GetHashTableSize() const;
	void InitHashTable(UINT hashSize, BOOL bAllocNow = TRUE);

// Overridables: special non-virtual (see map implementation for details)
	// Routine used to user-provided hash keys
	UINT HashKey(DWORD key) const;

// Implementation
protected:
	CAssoc** m_pHashTable;
	UINT m_nHashTableSize;
	int m_nCount;
	CAssoc* m_pFreeList;
	struct CGXPlex* m_pBlocks;
	int m_nBlockSize;

	CAssoc* NewAssoc();
	void FreeAssoc(CAssoc*);
	CAssoc* GetAssocAt(DWORD, UINT&) const;

public:
	virtual ~CGXCollMapDWordToPtr();
#ifdef _DEBUG
	void Dump(CDumpContext&) const;
	void AssertValid() const;
#endif

protected:
	// local typedefs for CTypedPtrMap class template
	typedef DWORD BASE_KEY;
	typedef DWORD BASE_ARG_KEY;
	typedef void* BASE_VALUE;
	typedef void* BASE_ARG_VALUE;
};


/////////////////////////////////////////////////////////////////////////////

class CMapNdxToOb : public CObject
{

	DECLARE_SERIAL(CMapNdxToOb)
protected:
	// Association
	struct CAssoc
	{
		CAssoc* pNext;
		UINT nHashValue;  // needed for efficient iteration
		GXNDX key;
		CObject* value;
	};

public:

// Construction
	CMapNdxToOb(int nBlockSize = 10);

// Attributes
	// number of elements
	int GetCount() const;
	BOOL IsEmpty() const;

	// Lookup
	BOOL Lookup(GXNDX key, CObject*& rValue) const;

// Operations
	// Lookup and add if not there
	CObject*& operator[](GXNDX key);

	// add a new (key, value) pair
	void SetAt(GXNDX key, CObject* newValue);

	// removing existing (key, ?) pair
	BOOL RemoveKey(GXNDX key);
	void RemoveAll();

	// iterating all (key, value) pairs
	POSITION GetStartPosition() const;
	void GetNextAssoc(POSITION& rNextPosition, GXNDX& rKey, CObject*& rValue) const;

	// advanced features for derived classes
	UINT GetHashTableSize() const;
	void InitHashTable(UINT hashSize, BOOL bAllocNow = TRUE);

// Overridables: special non-virtual (see map implementation for details)
	// Routine used to user-provided hash keys
	UINT HashKey(GXNDX key) const;

// Implementation
protected:
	CAssoc** m_pHashTable;
	UINT m_nHashTableSize;
	int m_nCount;
	CAssoc* m_pFreeList;
	struct CGXPlex* m_pBlocks;
	int m_nBlockSize;

	CAssoc* NewAssoc();
	void FreeAssoc(CAssoc*);
	CAssoc* GetAssocAt(GXNDX, UINT&) const;

public:
	virtual ~CMapNdxToOb();

	void Serialize(CArchive&);
#ifdef _DEBUG
	void Dump(CDumpContext&) const;
	void AssertValid() const;
#endif

protected:
	// local typedefs for CTypedPtrMap class template
	typedef GXNDX BASE_KEY;
	typedef GXNDX BASE_ARG_KEY;
	typedef CObject* BASE_VALUE;
	typedef CObject* BASE_ARG_VALUE;
};

/////////////////////////////////////////////////////////////////////////////

class CGXCollMapStringToWord : public CObject
{

	DECLARE_DYNAMIC(CGXCollMapStringToWord)
protected:
	// Association
	struct CAssoc
	{
		CAssoc* pNext;
		UINT nHashValue;  // needed for efficient iteration
		CString key;
		WORD value;
	};
public:

// Construction
	CGXCollMapStringToWord(int nBlockSize=10);

// Attributes
	// number of elements
	int GetCount() const;
	BOOL IsEmpty() const;

	// Lookup
	BOOL Lookup(LPCTSTR key, WORD& rValue) const;

// Operations
	// Lookup and add if not there
	WORD& operator[](LPCTSTR key);

	// add a new (key, value) pair
	void SetAt(LPCTSTR key, WORD newValue);

	// removing existing (key, ?) pair
	BOOL RemoveKey(LPCTSTR key);
	void RemoveAll();

	// iterating all (key, value) pairs
	POSITION GetStartPosition() const;
	void GetNextAssoc(POSITION& rNextPosition, CString& rKey, WORD& rValue) const;

	// advanced features for derived classes
	UINT GetHashTableSize() const;
	void InitHashTable(UINT hashSize);

// Overridables: special non-virtual (see map implementation for details)
	// Routine used to user-provided hash keys
	UINT HashKey(LPCTSTR key) const;

// Implementation
protected:
	CAssoc** m_pHashTable;
	UINT m_nHashTableSize;
	int m_nCount;
	CAssoc* m_pFreeList;
	struct CGXPlex* m_pBlocks;
	int m_nBlockSize;

	CAssoc* NewAssoc();
	void FreeAssoc(CAssoc*);
	CAssoc* GetAssocAt(LPCTSTR, UINT&) const;

public:
	virtual ~CGXCollMapStringToWord();
#ifdef _DEBUG
	void Dump(CDumpContext&) const;
	void AssertValid() const;
#endif
};

/////////////////////////////////////////////////////////////////////////////

class CGXCollMapStringToHandle : public CObject
{

	DECLARE_DYNAMIC(CGXCollMapStringToHandle)
protected:
	// Association
	struct CAssoc
	{
		CAssoc* pNext;
		UINT nHashValue;  // needed for efficient iteration
		CString key;
		HANDLE value;
	};
public:

// Construction
	CGXCollMapStringToHandle(int nBlockSize=10);

// Attributes
	// number of elements
	int GetCount() const;
	BOOL IsEmpty() const;

	// Lookup
	BOOL Lookup(LPCTSTR key, HANDLE& rValue) const;

// Operations
	// Lookup and add if not there
	HANDLE& operator[](LPCTSTR key);

	// add a new (key, value) pair
	void SetAt(LPCTSTR key, HANDLE newValue);

	// removing existing (key, ?) pair
	BOOL RemoveKey(LPCTSTR key);
	void RemoveAll();

	// iterating all (key, value) pairs
	POSITION GetStartPosition() const;
	void GetNextAssoc(POSITION& rNextPosition, CString& rKey, HANDLE& rValue) const;

	// advanced features for derived classes
	UINT GetHashTableSize() const;
	void InitHashTable(UINT hashSize);

// Overridables: special non-virtual (see map implementation for details)
	// Routine used to user-provided hash keys
	UINT HashKey(LPCTSTR key) const;

// Implementation
protected:
	CAssoc** m_pHashTable;
	UINT m_nHashTableSize;
	int m_nCount;
	CAssoc* m_pFreeList;
	struct CGXPlex* m_pBlocks;
	int m_nBlockSize;

	CAssoc* NewAssoc();
	void FreeAssoc(CAssoc*);
	CAssoc* GetAssocAt(LPCTSTR, UINT&) const;

public:
	virtual ~CGXCollMapStringToHandle();
#ifdef _DEBUG
	void Dump(CDumpContext&) const;
	void AssertValid() const;
#endif
};

// header file

class CGXMapDWordToLong : public CGXCollMapDWordToLong	// Row Heights
{
	DECLARE_SERIAL(CGXMapDWordToLong)

public:
	// Inserting Colums or Rows
	void   Insert(DWORD nId, DWORD nCount);

	// Removing Colums or Rows
	void   Remove(DWORD nFrom, DWORD nTo);

	// Moving Colums or Rows
	void   Move(DWORD nFrom, DWORD nTo, DWORD nDest);

	virtual CGXMapDWordToLong& operator=(const CGXMapDWordToLong& map);
};


class CGXMapCellToOb : public CMapNdxToOb
{
	DECLARE_SERIAL(CGXMapCellToOb)

public:
	// Inserting Colums or Rows
	void   InsertRows(DWORD nRow, DWORD nCount);
	void   InsertCols(DWORD nCol, DWORD nCount);

	// Removing Colums or Rows
	void   RemoveRows(DWORD nFromRow, DWORD nToRow);
	void   RemoveCols(DWORD nFromCol, DWORD nToCol);

	// Moving Colums or Rows
	void   MoveRows(DWORD nFromRow, DWORD nToRow, DWORD nDestRow);
	void   MoveCols(DWORD nFromCol, DWORD nToCol, DWORD nDestCol);
};

// CGXBitArray allows you to insert, move and remove specific
// bits in an array of bytes. The class lets you directly store
// and retrieve bits. The bits can be serialized just like a
// normal CByteArray.

class CGXBitArray : public CByteArray
{
public:
	BOOL SetBitAt(DWORD dwIndex, BOOL bValue);
	BOOL GetBitAt(DWORD dwIndex);
	void RemoveBits(DWORD dwFrom, DWORD dwTo);
	void MoveBits(DWORD nFrom, DWORD nTo, DWORD nDest);
	void InsertBits(DWORD nFrom, DWORD nCount);
};

/////////////////////////////////////////////////////////////////////////////

class CGXMapByte8ToPtr : public CObject
{

	DECLARE_DYNAMIC(CGXMapByte8ToPtr)
protected:
	// Association
	struct CAssoc
	{
		CAssoc* pNext;
		UINT nHashValue;  // needed for efficient iteration
		GXBYTE8 key;
		void* value;
	};

public:

// Construction
	CGXMapByte8ToPtr(int nBlockSize = 10);

// Attributes
	// number of elements
	int GetCount() const;
	BOOL IsEmpty() const;

	// Lookup
	BOOL Lookup(GXBYTE8 key, void*& rValue) const;

// Operations
	// Lookup and add if not there
	void*& operator[](GXBYTE8 key);

	// add a new (key, value) pair
	void SetAt(GXBYTE8 key, void* newValue);

	// removing existing (key, ?) pair
	BOOL RemoveKey(GXBYTE8 key);
	void RemoveAll();

	// iterating all (key, value) pairs
	POSITION GetStartPosition() const;
	void GetNextAssoc(POSITION& rNextPosition, GXBYTE8& rKey, void*& rValue) const;

	// advanced features for derived classes
	UINT GetHashTableSize() const;
	void InitHashTable(UINT hashSize, BOOL bAllocNow = TRUE);

// Overridables: special non-virtual (see map implementation for details)
	// Routine used to user-provided hash keys
	UINT HashKey(GXBYTE8 key) const;

// Implementation
protected:
	CAssoc** m_pHashTable;
	UINT m_nHashTableSize;
	int m_nCount;
	CAssoc* m_pFreeList;
	struct CGXPlex* m_pBlocks;
	int m_nBlockSize;

	CAssoc* NewAssoc();
	void FreeAssoc(CAssoc*);
	CAssoc* GetAssocAt(GXBYTE8, UINT&) const;

public:
	virtual ~CGXMapByte8ToPtr();
#ifdef _DEBUG
	void Dump(CDumpContext&) const;
	void AssertValid() const;
#endif

protected:
	// local typedefs for CTypedPtrMap class template
	typedef GXBYTE8 BASE_KEY;
	typedef GXBYTE8 BASE_ARG_KEY;
	typedef void* BASE_VALUE;
	typedef void* BASE_ARG_VALUE;
};

// create LOGFONT structure on demand and use reference count
struct CGXFontData
{
	long nRefs;     // reference count
	LOGFONT lf;
	unsigned bInit            : 1;  // TRUE when LOGFONT is initialized
};


/////////////////////////////////////////////////////////////////////////////

class CGXMapFontData : public CObject
{

	DECLARE_DYNAMIC(CGXMapFontData)
protected:
	// Association
	struct CAssoc
	{
		CAssoc* pNext;
		UINT nHashValue;  // needed for efficient iteration
		GXBYTE8 key;
		CGXFontData value;
	};

public:

// Construction
	CGXMapFontData(int nBlockSize = 10);

// Attributes
	// number of elements
	int GetCount() const;
	BOOL IsEmpty() const;

	// Lookup
	BOOL Lookup(GXBYTE8 key, CGXFontData& rValue) const;

// Operations
	// Lookup and add if not there
	CGXFontData& operator[](GXBYTE8 key);

	// add a new (key, value) pair
	void SetAt(GXBYTE8 key, CGXFontData& newValue);

	// removing existing (key, ?) pair
	BOOL RemoveKey(GXBYTE8 key);
	void RemoveAll();

	// iterating all (key, value) pairs
	POSITION GetStartPosition() const;
	void GetNextAssoc(POSITION& rNextPosition, GXBYTE8& rKey, CGXFontData& rValue) const;

	// advanced features for derived classes
	UINT GetHashTableSize() const;
	void InitHashTable(UINT hashSize, BOOL bAllocNow = TRUE);

// Overridables: special non-virtual (see map implementation for details)
	// Routine used to user-provided hash keys
	UINT HashKey(GXBYTE8 key) const;

// Implementation
protected:
	CAssoc** m_pHashTable;
	UINT m_nHashTableSize;
	int m_nCount;
	CAssoc* m_pFreeList;
	struct CGXPlex* m_pBlocks;
	int m_nBlockSize;

	CAssoc* NewAssoc();
	void FreeAssoc(CAssoc*);
	CAssoc* GetAssocAt(GXBYTE8, UINT&) const;

public:
	virtual ~CGXMapFontData();
#ifdef _DEBUG
	void Dump(CDumpContext&) const;
	void AssertValid() const;
#endif

protected:
	// local typedefs for CTypedPtrMap class template
	typedef GXBYTE8 BASE_KEY;
	typedef GXBYTE8 BASE_ARG_KEY;
	typedef CGXFontData BASE_VALUE;
	typedef CGXFontData& BASE_ARG_VALUE;
};
               
struct CGXSortInfo
{
	ROWCOL nRC;

	enum SortType
	{
		numeric,
		alphanumeric,
		date,
		autodetect
	} sortType;

	enum SortOrder
	{
		ascending,
		descending
	} sortOrder;

	BOOL bCase;		// TRUE==case sensitive, FALSE==not
	DWORD dwCookie; // 32-Bit value you can use to pass a cookie to your own sorting routins

	// Reserved:
	BOOL bOnlyNum;
	BOOL bOnlyDate;

	CGXSortInfo();
};

class CGXSortInfoArray : public CObject
{

	DECLARE_DYNAMIC(CGXSortInfoArray)
public:

// Construction
	CGXSortInfoArray();

// Attributes
	int GetSize() const;
	int GetUpperBound() const;
	void SetSize(int nNewSize, int nGrowBy = -1);

// Operations
	// Clean up
	void FreeExtra();
	void RemoveAll();

	// Accessing elements
	CGXSortInfo GetAt(int nIndex) const;
	void SetAt(int nIndex, CGXSortInfo newElement);
	CGXSortInfo& ElementAt(int nIndex);

	// Direct Access to the element data (may return NULL)
	const CGXSortInfo* GetData() const;
	CGXSortInfo* GetData();

	// Potentially growing the array
	void SetAtGrow(int nIndex, CGXSortInfo newElement);
	int Add(CGXSortInfo newElement);
	int Append(const CGXSortInfoArray& src);
	void Copy(const CGXSortInfoArray& src);

	// overloaded operator helpers
	CGXSortInfo operator[](int nIndex) const;
	CGXSortInfo& operator[](int nIndex);

	// Operations that move elements around
	void InsertAt(int nIndex, CGXSortInfo newElement, int nCount = 1);
	void RemoveAt(int nIndex, int nCount = 1);
	void InsertAt(int nStartIndex, CGXSortInfoArray* pNewArray);

// Implementation
protected:
	CGXSortInfo* m_pData;   // the actual array of data
	int m_nSize;     // # of elements (upperBound - 1)
	int m_nMaxSize;  // max allocated
	int m_nGrowBy;   // grow amount

public:
	virtual ~CGXSortInfoArray();
#ifdef _DEBUG
	void Dump(CDumpContext&) const;
	void AssertValid() const;
#endif

protected:
	// local typedefs for class templates
	typedef CGXSortInfo BASE_TYPE;
	typedef CGXSortInfo BASE_ARG_TYPE;
};

/////////////////////////////////////////////////////////////////////////////
// class CGXPtrArrayPtrArray

// type-safe CPtrArray for array with CPtrArray objects

class CGXPtrArrayPtrArray: public CPtrArray
{
	DECLARE_DYNAMIC(CGXPtrArrayPtrArray)

public:
	// Construcion/Destruction
	CGXPtrArrayPtrArray();
	virtual ~CGXPtrArrayPtrArray();
		// destructor automatically deletes all referenced objects

	void DeleteAll();   // delete all referenced objects
	void DeleteAt(int nIndex, int nCount = 1);
	void Move(int nIndex, int nCount, int nDest);

public:
	// Accessing elements
	CPtrArray* GetAt(int nIndex) const;
	void SetAt(int nIndex, CPtrArray* newElement);

	// Potentially growing the array
	void SetAtGrow(int nIndex, CPtrArray* newElement);
	int Add(CPtrArray* newElement);

	// overloaded operator helpers
	CPtrArray* operator[](int nIndex) const;
	CPtrArray*& operator[](int nIndex);

	// Operations that move elements around
	void InsertAt(int nIndex, CPtrArray* newElement, int nCount = 1);
	void InsertAt(int nStartIndex, CGXPtrArrayPtrArray* pNewArray);
};

/////////////////////////////////////////////////////////////////////////////
// Some helper classes

void AFXAPI GXDeleteAllObjects(CMapPtrToPtr& ptmap);
void AFXAPI GXDeleteAllObjects(CObList& oblist);
void AFXAPI GXDeleteAllObjects(CObArray& obarray);

class CGXAutoDeleteObList: public CObList
{
	virtual ~CGXAutoDeleteObList();
};

/////////////////////////////////////////////////////////////////////////////
// Inline function declarations

#ifdef _GX_ENABLE_INLINES
#include "grid\gxcoll.inl"
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

#endif // _GXCOLL_H_
