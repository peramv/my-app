///////////////////////////////////////////////////////////////////////////////
// gxmapsh.cpp : CGXCollMapStringToHandle collection class
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
//          Supplement Section 227.7202, Government�s use, duplication or
//          disclosure of the computer software is subject to the restrictions
//          set forth by Rogue Wave Software, Inc.
//
///////////////////////////////////////////////////////////////////////////////
//
// Author: Stefan Hoenig
//

#define _OG_EXPORT_IMPL

#include "stdafx.h"

#ifdef _GXDLL
#undef AFXAPI_DATA
#define AFXAPI_DATA __based(__segname("_DATA"))
#endif

// Headers

#ifndef _GXCOLL_H_
#include "grid\gxcoll.h"
#endif

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef GX_USE_SEGMENTS
#pragma code_seg("GX_SEG_GXCOLL2")
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(CGXCollMapStringToHandle, CObject)

// Workaround for afxEmptyString
// Using afxEmptyString generates a GPF in the _AFXDLL version
// [VC7] has no definition of afxemptyString.
#if (_MFC_VER < 0x0300 || _MFC_VER >= 0x0700)
static const CString NEAR gxEmptyString;
#define afxEmptyString gxEmptyString
#endif

/////////////////////////////////////////////////////////////////////////////
// Special implementations for CStrings
// it is faster to bit-wise copy a CString than to call an official
//   constructor - since an empty CString can be bit-wise copied

static inline void ConstructElement(CString* pNewData)
{
	memcpy(pNewData, &afxEmptyString, sizeof(CString));
}

static inline void DestructElement(CString* pOldData)
{
	pOldData->~CString();
}

static inline void CopyElement(CString* pSrc, CString* pDest)
{
	*pSrc = *pDest;
}


/////////////////////////////////////////////////////////////////////////////

CGXCollMapStringToHandle::CGXCollMapStringToHandle(int nBlockSize)
{
	ASSERT(nBlockSize > 0);

	m_pHashTable = NULL;
	m_nHashTableSize = 17;  // default size
	m_nCount = 0;
	m_pFreeList = NULL;
	m_pBlocks = NULL;
	m_nBlockSize = nBlockSize;
}

inline UINT CGXCollMapStringToHandle::HashKey(LPCTSTR key) const
{
	UINT nHash = 0;
	while (*key)
		nHash = (nHash<<5) + nHash + *key++;
	return nHash;
}

void CGXCollMapStringToHandle::InitHashTable(UINT nHashSize)
//
// Used to force allocation of a hash table or to override the default
//   hash table size of (which is fairly small)
{
	ASSERT_VALID(this);
	ASSERT(m_nCount == 0);
	ASSERT(nHashSize > 0);

	// free has table
	delete[] m_pHashTable;
	m_pHashTable = NULL;

	m_pHashTable = new CAssoc* [nHashSize];
	memset(m_pHashTable, 0, sizeof(CAssoc*) * nHashSize);
	m_nHashTableSize = nHashSize;
}

void CGXCollMapStringToHandle::RemoveAll()
{
	ASSERT_VALID(this);

	if (m_pHashTable != NULL)
	{
		// destroy elements
		for (UINT nHash = 0; nHash < m_nHashTableSize; nHash++)
		{
			CAssoc* pAssoc;
			for (pAssoc = m_pHashTable[nHash]; pAssoc != NULL;
			  pAssoc = pAssoc->pNext)
			{
				DestructElement(&pAssoc->key);	// free up string data
			}
		}

		// free hash table
		delete [] m_pHashTable;
		m_pHashTable = NULL;
	}

	m_nCount = 0;
	m_pFreeList = NULL;
	m_pBlocks->FreeDataChain();
	m_pBlocks = NULL;
}

CGXCollMapStringToHandle::~CGXCollMapStringToHandle()
{
	RemoveAll();
	ASSERT(m_nCount == 0);
}

/////////////////////////////////////////////////////////////////////////////
// Assoc helpers
// same as CList implementation except we store CAssoc's not CNode's
//    and CAssoc's are singly linked all the time

CGXCollMapStringToHandle::CAssoc* CGXCollMapStringToHandle::NewAssoc()
{
	if (m_pFreeList == NULL)
	{
		// add another block
		CGXPlex* newBlock = CGXPlex::Create(m_pBlocks, m_nBlockSize,
							sizeof(CGXCollMapStringToHandle::CAssoc));
		// chain them into free list
		CGXCollMapStringToHandle::CAssoc* pAssoc =
				(CGXCollMapStringToHandle::CAssoc*) newBlock->data();
		// free in reverse order to make it easier to debug
		pAssoc += m_nBlockSize - 1;
		for (int i = m_nBlockSize-1; i >= 0; i--, pAssoc--)
		{
			pAssoc->pNext = m_pFreeList;
			m_pFreeList = pAssoc;
		}
	}
	ASSERT(m_pFreeList != NULL);  // we must have something

	CGXCollMapStringToHandle::CAssoc* pAssoc = m_pFreeList;
	m_pFreeList = m_pFreeList->pNext;
	m_nCount++;
	ASSERT(m_nCount > 0);  // make sure we don't overflow
	memcpy(&pAssoc->key, &afxEmptyString, sizeof(CString));

	pAssoc->value = 0;

	return pAssoc;
}

void CGXCollMapStringToHandle::FreeAssoc(CGXCollMapStringToHandle::CAssoc* pAssoc)
{
	DestructElement(&pAssoc->key);	// free up string data

	pAssoc->pNext = m_pFreeList;
	m_pFreeList = pAssoc;
	m_nCount--;
	ASSERT(m_nCount >= 0);  // make sure we don't underflow
}

CGXCollMapStringToHandle::CAssoc*
CGXCollMapStringToHandle::GetAssocAt(LPCTSTR key, UINT& nHash) const
// find association (or return NULL)
{
	nHash = HashKey(key) % m_nHashTableSize;

	if (m_pHashTable == NULL)
		return NULL;

	// see if it exists
	CAssoc* pAssoc;
	for (pAssoc = m_pHashTable[nHash]; pAssoc != NULL; pAssoc = pAssoc->pNext)
	{
		if (pAssoc->key == key)
			return pAssoc;
	}
	return NULL;
}

/////////////////////////////////////////////////////////////////////////////

BOOL CGXCollMapStringToHandle::Lookup(LPCTSTR key, HANDLE& rValue) const
{
	ASSERT_VALID(this);

	UINT nHash;
	CAssoc* pAssoc = GetAssocAt(key, nHash);
	if (pAssoc == NULL)
		return FALSE;  // not in map

	rValue = pAssoc->value;
	return TRUE;
}

HANDLE& CGXCollMapStringToHandle::operator[](LPCTSTR key)
{
	ASSERT_VALID(this);

	UINT nHash;
	CAssoc* pAssoc;
	if ((pAssoc = GetAssocAt(key, nHash)) == NULL)
	{
		if (m_pHashTable == NULL)
			InitHashTable(m_nHashTableSize);

		// it doesn't exist, add a new Association
		pAssoc = NewAssoc();
		pAssoc->nHashValue = nHash;
		pAssoc->key = key;
		// 'pAssoc->value' is a constructed object, nothing more

		// put into hash table
		pAssoc->pNext = m_pHashTable[nHash];
		m_pHashTable[nHash] = pAssoc;
	}
	return pAssoc->value;  // return new reference
}


BOOL CGXCollMapStringToHandle::RemoveKey(LPCTSTR key)
// remove key - return TRUE if removed
{
	ASSERT_VALID(this);

	if (m_pHashTable == NULL)
		return FALSE;  // nothing in the table

	CAssoc** ppAssocPrev;
	ppAssocPrev = &m_pHashTable[HashKey(key) % m_nHashTableSize];

	CAssoc* pAssoc;
	for (pAssoc = *ppAssocPrev; pAssoc != NULL; pAssoc = pAssoc->pNext)
	{
		if (pAssoc->key == key)
		{
			// remove it
			*ppAssocPrev = pAssoc->pNext;  // remove from list
			FreeAssoc(pAssoc);
			return TRUE;
		}
		ppAssocPrev = &pAssoc->pNext;
	}
	return FALSE;  // not found
}


/////////////////////////////////////////////////////////////////////////////
// Iterating

void CGXCollMapStringToHandle::GetNextAssoc(POSITION& rNextPosition,
	CString& rKey, HANDLE& rValue) const
{
	ASSERT_VALID(this);
	ASSERT(m_pHashTable != NULL);  // never call on empty map

	CAssoc* pAssocRet = (CAssoc*)rNextPosition;
	ASSERT(pAssocRet != NULL);

	if (pAssocRet == (CAssoc*) BEFORE_START_POSITION)
	{
		// find the first association
		for (UINT nBucket = 0; nBucket < m_nHashTableSize; nBucket++)
			if ((pAssocRet = m_pHashTable[nBucket]) != NULL)
				break;
		ASSERT(pAssocRet != NULL);  // must find something
	}

	// find next association
	ASSERT(AfxIsValidAddress(pAssocRet, sizeof(CAssoc)));
	CAssoc* pAssocNext;
	if ((pAssocNext = pAssocRet->pNext) == NULL)
	{
		// go to next bucket
		for (UINT nBucket = pAssocRet->nHashValue + 1;
		  nBucket < m_nHashTableSize; nBucket++)
			if ((pAssocNext = m_pHashTable[nBucket]) != NULL)
				break;
	}

	rNextPosition = (POSITION) pAssocNext;

	// fill in return data
	rKey = pAssocRet->key;
	rValue = pAssocRet->value;
}

/////////////////////////////////////////////////////////////////////////////
// Serialization


/////////////////////////////////////////////////////////////////////////////
// Diagnostics

#ifdef _DEBUG

void CGXCollMapStringToHandle::Dump(CDumpContext& dc) const
{
	ASSERT_VALID(this);

	CObject::Dump(dc);

	dc << "with " << m_nCount << " elements";

	if (dc.GetDepth() > 0)
	{
		// Dump in format "[key] -> value"
		AFX_DUMP0(dc, "\n");
		POSITION pos = GetStartPosition();
		CString key;
		HANDLE val;
		while (pos != NULL)
		{
			GetNextAssoc(pos, key, val);
			AFX_DUMP1(dc, "\n\t[", key);
			AFX_DUMP1(dc, "] = ", val);
		}
	}
}

void CGXCollMapStringToHandle::AssertValid() const
{
	CObject::AssertValid();

	ASSERT(m_nHashTableSize > 0);
	ASSERT(m_nCount == 0 || m_pHashTable != NULL);
		// non-empty map should have hash table
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////



