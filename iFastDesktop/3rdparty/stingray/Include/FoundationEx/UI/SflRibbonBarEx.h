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
#if !defined __SFLRIBBONBAREX__H__
#define __SFLRIBBONBAREX__H__

#include "StingrayExportDefs.h"
#include "afxcontrolbars.h"

namespace sflex
{

// SFLRibbonBarEx

class SFLRibbonBarEx : public CMFCRibbonBar
{
	FOUNDATIONEX_DECLARE_DYNAMIC(SFLRibbonBarEx)

public:
	FOUNDATIONEX_API SFLRibbonBarEx();
	FOUNDATIONEX_API virtual ~SFLRibbonBarEx();

	// Create and initialize the RibbonBar.
	FOUNDATIONEX_API virtual BOOL CreateAndInitialize(CWnd* pParentWnd, BOOL bCreateQuickAccessToolBar = TRUE, BOOL bCreateCaptionBar = TRUE, BOOL bCreateAppStyleMenu = TRUE, BOOL bCreateAboutButton = TRUE);
	// Get the StatusBar.
	FOUNDATIONEX_API CMFCRibbonStatusBar& GetStatusBar();
	// Get the CaptionBar.
	FOUNDATIONEX_API CMFCCaptionBar& GetCaptionBar();
	// Add Category
	FOUNDATIONEX_API virtual CMFCRibbonCategory* AddCategory(LPCTSTR lpszName, UINT uiSmallImagesResID, UINT uiLargeImagesResID,
		CSize sizeSmallImage = CSize(16, 16), CSize sizeLargeImage = CSize(32, 32), int nInsertAt = -1, CRuntimeClass* pRTI = NULL);
	FOUNDATIONEX_API virtual CMFCRibbonCategory* AddCategory(CMFCRibbonCategory* pCategory, int nInsertAt = -1);


protected: 
	FOUNDATIONEX_API virtual BOOL ImplRibbonBar(CWnd* pParentWnd);
	// Implement the StatusBar.
	FOUNDATIONEX_API virtual BOOL ImplStatusBar(CWnd* pParentWnd);
	// Implement the Quick Access ToolBar.
	FOUNDATIONEX_API virtual BOOL ImplQuickAccessToolBar();
	// Implement the CaptionBar.
	FOUNDATIONEX_API virtual BOOL ImplCaptionBar(CWnd* pParentWnd);
	// Implement the Application Style Menu.
	FOUNDATIONEX_API virtual BOOL ImplApplicationStyleMenu();
	// Implement the About Button.
	FOUNDATIONEX_API virtual BOOL ImplAboutButton();

protected:
	FOUNDATIONEX_DECLARE_MESSAGE_MAP()

protected: 
	// Main Panel attached to the application button.
	CMFCRibbonMainPanel*		m_pMainPanel;
	// Ribbon StatusBar. Must be present to comply with the Fluent UI.
	CMFCRibbonStatusBar			m_wndStatusBar;
	// Ribbon CaptionBar.
	CMFCCaptionBar				m_wndCaptionBar;
	// Quick Access ToolBar Commands List
	CList<UINT, UINT>			m_lstQATCmds;
	// Ribbon panel icons.
	CMFCToolBarImages			m_PanelImages;

	friend class CMFCRibbonCategory;
};

} // namespace sflex

#endif // __SFLRIBBONBAREX__H__
