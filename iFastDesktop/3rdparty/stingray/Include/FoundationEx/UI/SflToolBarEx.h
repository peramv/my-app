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
#if !defined __SFLTOOLBAREX__H__
#define __SFLTOOLBAREX__H__

#include "StingrayExportDefs.h"
#include "afxtoolbar.h"

namespace sflex
{

#define SFLEX_MULTI_COLUMN_TOOLBAR_MAX	10

// SFLToolBarEx

class SFLToolBarEx : public CMFCToolBar
{
	FOUNDATIONEX_DECLARE_DYNAMIC(SFLToolBarEx)

public:
	// Construction -----------------------------//
	FOUNDATIONEX_API SFLToolBarEx();
	FOUNDATIONEX_API virtual ~SFLToolBarEx();

	// Exclude a list of toolbar commands from showing up. Use empty list to reset.
	FOUNDATIONEX_API static void ExcludeCommands(CList<UINT, UINT>& lstCommands);

// SRSTUDIO-989
	// Get/Set the number of vertical button columns. Default is 1. 
	inline UINT  GetColumnCount() const { return m_nColumnCount; }
	inline UINT  GetMaxColumnCount() const { return m_nMaxColumnCount; }
	FOUNDATIONEX_API void SetColumnCount(UINT nNumColumns);
	FOUNDATIONEX_API void SetMaxColumnCount(UINT nMaxNumColumns);

	// Overrides
	FOUNDATIONEX_API virtual int WrapToolBar(int nWidth, int nHeight = 32767, CDC* pDC  = NULL, int nColumnWidth = -1, int nRowHeight = -1);
	FOUNDATIONEX_API virtual CSize CalcSize(BOOL bVertDock);
	FOUNDATIONEX_API virtual void AdjustLocations();
	FOUNDATIONEX_API virtual void DoPaint(CDC* pDC);

protected:
	FOUNDATIONEX_DECLARE_MESSAGE_MAP()

	// SRSTUDIO-989 Number of Vertical Columns
	int	m_nColumnCount;
	int m_nMaxColumnCount;
	// Button Margins
	int m_nHorzMargin;
	int m_nVertMargin;
};

} // namespace sflex

#endif // __SFLTOOLBAREX__H__
