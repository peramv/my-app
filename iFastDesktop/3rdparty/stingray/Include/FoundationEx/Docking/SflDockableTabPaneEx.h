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
#if !defined __SFLDOCKABLETABPANE__H__
#define __SFLDOCKABLETABPANE__H__

#include "StingrayExportDefs.h"
#include "SFLDockablePaneEx.h"
#include "FoundationEx\UI\sflChildToolBarEx.h"

namespace sflex
{

// SFLDockableTabPaneEx

// Undefine this if no Child Toolbar is desired.
//#define SFLEX_DOCKTABPANE_CREATE_CHILDTOOLBAR 

class SFLDockableTabPaneEx : public SFLDockablePaneEx
{
	FOUNDATIONEX_DECLARE_DYNAMIC(SFLDockableTabPaneEx)

public:
	FOUNDATIONEX_API SFLDockableTabPaneEx();
	FOUNDATIONEX_API virtual ~SFLDockableTabPaneEx();

	// Controls
	inline CMFCTabCtrl& GetTabControl() { return m_wndTabs; }
//#ifdef SFLEX_DOCKTABPANE_CREATE_CHILDTOOLBAR
//	inline SFLChildToolBarEx<SFLDockableTabPaneEx>&	GetChildToolBar() { return m_wndChildToolBar; }
//#endif // SFLEX_DOCKTABPANE_CREATE_CHILDTOOLBAR

	// Add Tabs
	FOUNDATIONEX_API void AddTab(CWnd* pTabWnd, LPCTSTR lpszTabLabel, UINT uiImageId = (UINT)-1, BOOL bDetachable = 1);
	FOUNDATIONEX_API void AddTab(CWnd* pTabWnd, UINT uiResTabLabel, UINT uiImageId = (UINT)-1, BOOL bDetachable = 1);
	// Remove Tabs
	FOUNDATIONEX_API void RemoveAllTabs();
	FOUNDATIONEX_API void RemoveTab(int iTab, BOOL bRecalcLayout = 1);
	// Tab Style
	FOUNDATIONEX_API void ModifyTabStyle(CMFCTabCtrl::Style style);
	// Layout
	FOUNDATIONEX_API void AdjustLayout();

protected:
	FOUNDATIONEX_API afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	FOUNDATIONEX_API afx_msg void OnSize(UINT nType, int cx, int cy);
	FOUNDATIONEX_API afx_msg void OnDestroy();
	
	FOUNDATIONEX_API afx_msg LRESULT OnAppStyle(WPARAM wParam, LPARAM lParam);
	FOUNDATIONEX_DECLARE_MESSAGE_MAP()

	// Tab Control.
	CMFCTabCtrl	m_wndTabs;

//#ifdef SFLEX_DOCKTABPANE_CREATE_CHILDTOOLBAR
//	// Child ToolBar. 
//	SFLChildToolBarEx<SFLDockableTabPaneEx>	m_wndChildToolBar;
//#endif // SFLEX_DOCKTABPANE_CREATE_CHILDTOOLBAR
};

} // namespace sflex

#endif // __SFLDOCKABLETABPANE__H__
