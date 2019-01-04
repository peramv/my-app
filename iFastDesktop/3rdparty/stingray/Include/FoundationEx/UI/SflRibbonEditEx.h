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
#if !defined __SFLRIBBONEDITEX__H__
#define __SFLRIBBONEDITEX__H__

#include "StingrayExportDefs.h"
#include "afxribbonedit.h"

namespace sflex
{

// SFLRibbonEditEx

class SFLRibbonEditEx : public CMFCRibbonEdit
{
	FOUNDATIONEX_DECLARE_DYNCREATE(SFLRibbonEditEx)

protected:
	SFLRibbonEditEx();

public:
	FOUNDATIONEX_API SFLRibbonEditEx(UINT nID, int nWidth, LPCTSTR lpszLabel = NULL, int nImage = -1);
	FOUNDATIONEX_API virtual ~SFLRibbonEditEx();

#if _MSC_VER <= 1500 // VS 2008 - 
	virtual int GetRangeMin() const { return m_nMin; }
	virtual int GetRangeMax() const { return m_nMax; }
#endif
};

} // namespace sflex

#endif // __SFLRIBBONEDITEX__H__
