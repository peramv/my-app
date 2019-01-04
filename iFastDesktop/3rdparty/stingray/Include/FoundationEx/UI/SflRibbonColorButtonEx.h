//////////////////////////////////////////////////////////////////////////////
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
//////////////////////////////////////////////////////////////////////////////
#if !defined __SFLRIBBONCOLORBUTTONEX__H__
#define __SFLRIBBONCOLORBUTTONEX__H__

#include "StingrayExportDefs.h"
#include "afxribboncolorbutton.h"

namespace sflex
{

// SFLRibbonColorButtonEx

class SFLRibbonColorButtonEx : public CMFCRibbonColorButton
{
	FOUNDATIONEX_DECLARE_DYNCREATE(SFLRibbonColorButtonEx)

public:
	FOUNDATIONEX_API SFLRibbonColorButtonEx();
	FOUNDATIONEX_API SFLRibbonColorButtonEx(UINT nID, LPCTSTR lpszText, int nSmallImageIndex, COLORREF color = RGB(0, 0, 0));
	FOUNDATIONEX_API SFLRibbonColorButtonEx(UINT nID, LPCTSTR lpszText, BOOL bSimpleButtonLook, int nSmallImageIndex, int nLargeImageIndex, COLORREF color = RGB(0, 0, 0));

	FOUNDATIONEX_API virtual ~SFLRibbonColorButtonEx();

#if _MSC_VER < 1600 // VS 2008 - 
public:	
	inline virtual BOOL IsSimpleButtonLook() const { return m_bSimpleButtonLook; }
#endif // VS 2008 -
};

} // namespace sflex

#endif // __SFLRIBBONCOLORBUTTONEX__H__
