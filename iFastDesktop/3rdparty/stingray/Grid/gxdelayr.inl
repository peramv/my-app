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

// gxdelayr.inl: Inlines for gxdelayr.h
/////////////////////////////////////////////////////////////////////////////

#ifdef GX_INLINE

/////////////////////////////////////////////////////////////////////////////
// CGXDWordArrayPtrArray

GX_INLINE CGXDWordArrayPtrArray::CGXDWordArrayPtrArray()
	{ };

GX_INLINE CDWordArray* CGXDWordArrayPtrArray::GetAt(int nIndex) const
	{ return (CDWordArray*) CPtrArray::GetAt(nIndex); }

GX_INLINE void CGXDWordArrayPtrArray::SetAt(int nIndex, CDWordArray* newElement)
	{ CPtrArray::SetAt(nIndex, newElement); }

	// Potentially growing the array
GX_INLINE void CGXDWordArrayPtrArray::SetAtGrow(int nIndex, CDWordArray* newElement)
	{ CPtrArray::SetAtGrow(nIndex, newElement); }

GX_INLINE int CGXDWordArrayPtrArray::Add(CDWordArray* newElement)
	{ return (int)CPtrArray::Add(newElement); }

	// overloaded operator helpers
GX_INLINE CDWordArray* CGXDWordArrayPtrArray::operator[](int nIndex) const
	{ return (CDWordArray*) CPtrArray::operator[](nIndex); }

GX_INLINE CDWordArray*& CGXDWordArrayPtrArray::operator[](int nIndex)
	{ return (CDWordArray*&) CPtrArray::operator[](nIndex); }

	// Operations that move elements around
GX_INLINE void CGXDWordArrayPtrArray::InsertAt(int nIndex, CDWordArray* newElement, int nCount)
	{ CPtrArray::InsertAt(nIndex, newElement, nCount); }

GX_INLINE void CGXDWordArrayPtrArray::InsertAt(int nStartIndex, CGXDWordArrayPtrArray* pNewArray)
	{ CPtrArray::InsertAt(nStartIndex, pNewArray); }

GX_INLINE CGXSpanCellPool::CGXSpanCellPool()
{
}

#endif // GX_INLINE
