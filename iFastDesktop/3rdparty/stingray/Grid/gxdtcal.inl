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
// Portions of this code were copied from Objective Toolkit.

// Inlines for gxdtcal.h

#if _MFC_VER >= 0x0400 && defined(GX_INLINE)

GX_INLINE BOOL CGXBDateTimeCtrl::IsHourPM()
	{ return m_bHourPM; }

// Accessing elements
GX_INLINE CGXBDTGadget* CGXBDateTimeCtrl::CGXBDTGadgetArray::GetAt(int nIndex) const
	{ return (CGXBDTGadget*)CObArray::GetAt(nIndex); }

GX_INLINE CGXBDTGadget*& CGXBDateTimeCtrl::CGXBDTGadgetArray::ElementAt(int nIndex)
	{ return (CGXBDTGadget*&)CObArray::ElementAt(nIndex); }

GX_INLINE void CGXBDateTimeCtrl::CGXBDTGadgetArray::SetAt(int nIndex, CGXBDTGadget* ptr)
	{ CObArray::SetAt(nIndex, ptr); }

// Potentially growing the array
GX_INLINE void CGXBDateTimeCtrl::CGXBDTGadgetArray::SetAtGrow(int nIndex, CGXBDTGadget* newElement)
   { CObArray::SetAtGrow(nIndex, newElement); }

GX_INLINE int CGXBDateTimeCtrl::CGXBDTGadgetArray::Add(CGXBDTGadget* newElement)
   { return (int)CObArray::Add(newElement); }

GX_INLINE int CGXBDateTimeCtrl::CGXBDTGadgetArray::Append(const CGXBDTGadgetArray& src)
   { return (int)CObArray::Append(src); }

GX_INLINE void CGXBDateTimeCtrl::CGXBDTGadgetArray::Copy(const CGXBDTGadgetArray& src)
	{ CObArray::Copy(src); }

// Operations that move elements around
GX_INLINE void CGXBDateTimeCtrl::CGXBDTGadgetArray::InsertAt(int nIndex, CGXBDTGadget* newElement, int nCount)
	{ CObArray::InsertAt(nIndex, newElement, nCount); }

GX_INLINE void CGXBDateTimeCtrl::CGXBDTGadgetArray::InsertAt(int nStartIndex, CGXBDTGadgetArray* pNewArray)
   { CObArray::InsertAt(nStartIndex, pNewArray); }

// overloaded operator helpers
GX_INLINE CGXBDTGadget* CGXBDateTimeCtrl::CGXBDTGadgetArray::operator[](int nIndex) const
	{ return (CGXBDTGadget*)CObArray::operator[](nIndex); }

GX_INLINE CGXBDTGadget*& CGXBDateTimeCtrl::CGXBDTGadgetArray::operator[](int nIndex)
	{ return (CGXBDTGadget*&)CObArray::operator[](nIndex); }

#endif // GX_INLINE

