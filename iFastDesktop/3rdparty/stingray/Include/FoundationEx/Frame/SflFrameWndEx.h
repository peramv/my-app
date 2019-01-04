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
#if !defined __SFLFRAMEWNDEX__H__
#define __SFLFRAMEWNDEX__H__

#include "StingrayExportDefs.h"
#include "FoundationEx\Application\SFLAppStyleEx.h"
#include "FoundationEx\UI\SFLToolBarEx.h"
#include "FoundationEx\Manager\SFLMultiViewMgr.h"
#include "FoundationEx\Manager\SFLTaskbarMgr.h"
#include "FoundationEx\UI\SflFluentUI.h"

namespace sflex
{

// SFLFrameWndEx frame

class SFLFrameWndEx : public CFrameWndEx 
{
	FOUNDATIONEX_DECLARE_DYNCREATE(SFLFrameWndEx)
protected:
	FOUNDATIONEX_API SFLFrameWndEx();           // protected constructor used by dynamic creation
	FOUNDATIONEX_API virtual ~SFLFrameWndEx();

public:
	// Set the Application Style.
	FOUNDATIONEX_API void SetApplicationStyle(SFLAppStyleEx::eAppStyle id, CMFCRibbonBar* pRibbonBar = NULL, CRuntimeClass* pCustomVisualMgr = NULL);
	// Get ToolBar by Index.
	FOUNDATIONEX_API SFLToolBarEx* GetToolBarByIndex(int iIndex);
	// Get the Multi-View Manager
	FOUNDATIONEX_API SFLMultiViewMgr* GetMultiViewMgr();

	#if (WINVER >= 0x0601) && (_MSC_VER >= 1600) // Windows 7 or Higher and VS2010 or Higher.
	// Get the Taskbar Manager
	FOUNDATIONEX_API SFLTaskbarMgr* GetTaskbarMgr();
	#endif
	

public:
	// Handler for setting the application style based on the Style menu option.
	FOUNDATIONEX_API afx_msg void OnApplicationStyle(UINT id);
	FOUNDATIONEX_API afx_msg void OnUpdateApplicationStyle(CCmdUI* pCmdUI);
	FOUNDATIONEX_API afx_msg LRESULT OnApplicationStyle(WPARAM wParam, LPARAM lParam);
	// Handler for multi-view menu option
	FOUNDATIONEX_API afx_msg void OnSwitchView(UINT uiViewID);
	FOUNDATIONEX_API afx_msg void OnUpdateSwitchView(CCmdUI* pCmdUI);
	// Handler for RTL.
	FOUNDATIONEX_API afx_msg void OnRTL();
	FOUNDATIONEX_API afx_msg void OnUpdateRTL(CCmdUI* pCmdUI);
	// Handler for Fullscreen.
	FOUNDATIONEX_API afx_msg void OnViewFullscreen();
	FOUNDATIONEX_API afx_msg void OnUpdateViewFullscreen(CCmdUI *pCmdUI);
	// Handler for Toolbar Customization.
	FOUNDATIONEX_API afx_msg void OnCustomize();
	// Overrides
	FOUNDATIONEX_API afx_msg BOOL OnCreate(LPCREATESTRUCT lpCreateStruct);
	FOUNDATIONEX_API afx_msg BOOL OnNcActivate(BOOL bActive);
	// Handle rendering changes.
	FOUNDATIONEX_API afx_msg LRESULT OnNcRenderingChanged(WPARAM wParam, LPARAM lParam);
	FOUNDATIONEX_API afx_msg void OnSize(UINT nType, int cx, int cy);

	// Fluent UI (RibbonBar)
	FOUNDATIONEX_API void SetFluentUI(SFLFluentUI* pUI);
	FOUNDATIONEX_API SFLFluentUI* GetFluentUI();
	FOUNDATIONEX_API afx_msg LRESULT OnRibbonCustomize (WPARAM wp, LPARAM lp);
	FOUNDATIONEX_API afx_msg LRESULT OnChangeRibbonCategory(WPARAM,LPARAM);
	
	// Message Map.
	FOUNDATIONEX_DECLARE_MESSAGE_MAP()
	
protected:
	// Multi-View Manager
	FOUNDATIONEX_API static SFLMultiViewMgr*	m_pMultiViewMgr;
	#if (WINVER >= 0x0601) && (_MSC_VER >= 1600) // Windows 7 or Higher and VS2010 or Higher.
	// Taskbar Manager
	FOUNDATIONEX_API static SFLTaskbarMgr*		m_pTaskbarMgr;
	#endif

	// Rendering changes.
	BOOL m_bRenderingChanged;

	SFLFluentUI*	m_pFluentUI;
};

} // namespace sflex

#endif // __SFLFRAMEWNDEX__H__
