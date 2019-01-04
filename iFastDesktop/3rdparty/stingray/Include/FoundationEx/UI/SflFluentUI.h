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
#if !defined __SFLRIBBONBAR__H__
#define __SFLRIBBONBAR__H__

#include "StingrayExportDefs.h"
#include "FoundationEx\UI\SFLCaptionBarEx.h"
#include "afxcontrolbars.h"
#include "FoundationEx\Utils\SflCache.h"
#include <map>
using namespace std;

namespace sflex
{

// Wrapper class for the CMFCRibbonBar and associated Fluent UI elements.
class SFLFluentUI
{
public:
	// Constructor.
	FOUNDATIONEX_API SFLFluentUI(void);
	// Virtual Destructor.
	FOUNDATIONEX_API virtual ~SFLFluentUI(void);

	// Get the RibbonBar.
	FOUNDATIONEX_API CMFCRibbonBar& GetRibbonBar();
	// Get the Ribbon application button.
	FOUNDATIONEX_API CMFCRibbonApplicationButton& GetApplicationButton();
	// Get the RibbonBar panel images.
	FOUNDATIONEX_API CMFCToolBarImages& GetRibbonPanelImages();
	// Get the StatusBar.
	FOUNDATIONEX_API CMFCRibbonStatusBar& GetStatusBar();
	// Get the CaptionBar.
	FOUNDATIONEX_API SFLCaptionBarEx& GetCaptionBar();

	// Create the RibbonBar, QAT, and CaptionBar. True on success. pParentWnd is pointer to CMainFrame in app.
	FOUNDATIONEX_API virtual BOOL Create(CWnd* pParentWnd, CMDITabInfo* pTabiInfo = NULL, BOOL bCreateQuickAccessToolBar = TRUE, BOOL bCreateCaptionBar = TRUE, BOOL bCreateAppStyleMenu = TRUE, BOOL bCreateAboutButton = TRUE);
	FOUNDATIONEX_API virtual BOOL CreateAndInitialize(CWnd* pParentWnd, CMDITabInfo* pTabiInfo = NULL, BOOL (*pRibbonInitFunc)() = NULL, BOOL bCreateQuickAccessToolBar = TRUE, BOOL bCreateCaptionBar = TRUE, BOOL bCreateAppStyleMenu = TRUE, BOOL bCreateAboutButton = TRUE, BOOL bCreateFreqCmdPanel = FALSE);
	
#if _MSC_VER >= 1600 // VS 2010 +
	// Did we load form resource?
	FOUNDATIONEX_API BOOL IsLoadedFromResource();
	// Create and Load from Resource.
	FOUNDATIONEX_API virtual BOOL CreateAndLoadFromResource(CWnd* pParentWnd, CMDITabInfo* pTabInfo, UINT uiXMLResID, BOOL bCreateQuickAccessToolBar = TRUE, BOOL bCreateCaptionBar = TRUE, BOOL bCreateAppStyleMenu = TRUE, BOOL bCreateAboutButton = TRUE, BOOL bCreateAppButton = TRUE, BOOL bCreateFreqCmdPanel = FALSE);
	// Load Ribbon from Resource. If calling the above Create() function with a resource, do not call LoadResource().
	FOUNDATIONEX_API virtual BOOL LoadFromResource(UINT uiXMLResID, LPCTSTR lpszResType = RT_RIBBON, HINSTANCE hInstance = NULL);
#endif // _MSC_VER >= 1600

	// Frequently Used Commands.
	FOUNDATIONEX_API virtual BOOL IsUsingFrequentCommandPanel();
	// Enable Frequent Command Panels. Call this if you used Create() and wish to have command panels. 
	FOUNDATIONEX_API virtual BOOL EnableFreqCmdPanelPostCreation();
	FOUNDATIONEX_API virtual BOOL RedrawRecentCommandPanel(BOOL bLoadingFromRegistry = FALSE);
	FOUNDATIONEX_API virtual BOOL AddRecentCommand(UINT uiCommandID, UINT uiWeight = 0, int iData = 0, CString strText = _T(""), BOOL bLoadingFromRegistry = FALSE);
	FOUNDATIONEX_API virtual BOOL ClearRecentCommands();
	FOUNDATIONEX_API virtual BOOL SetFrequentCmdsMax(UINT uiMax);

	// Helpers
	FOUNDATIONEX_API virtual void Refresh();
	FOUNDATIONEX_API virtual CMFCRibbonBaseElement* FindByID(UINT uiCmdID, BOOL bVisibleOnly = TRUE, BOOL bExcludeQAT = FALSE) const;
	FOUNDATIONEX_API virtual CMFCRibbonBaseElement* FindByData(DWORD_PTR dwData, BOOL bVisibleOnly = TRUE) const;
	FOUNDATIONEX_API virtual BOOL SetElementKeys(UINT uiCmdID, LPCTSTR lpszKeys, LPCTSTR lpszMenuKeys = NULL);
	FOUNDATIONEX_API virtual void GetElementsByID(UINT uiCmdID, CArray<CMFCRibbonBaseElement*, CMFCRibbonBaseElement*>& arButtons);
	FOUNDATIONEX_API virtual void SetQuickAccessDefaultState(const CMFCRibbonQuickAccessToolBarDefaultState& state);
	FOUNDATIONEX_API virtual void SetQuickAccessCommands(const CList<UINT,UINT>& lstCommands, BOOL bRecalcLayout = TRUE);
	FOUNDATIONEX_API virtual void GetQuickAccessCommands(CList<UINT,UINT>& lstCommands);

	// Controls ---------------------------------//

	// Category Helpers
	FOUNDATIONEX_API virtual CMFCRibbonMainPanel* AddMainCategory(LPCTSTR lpszName, UINT uiSmallImagesResID, UINT uiLargeImagesResID,
		CSize sizeSmallImage = CSize(16, 16), CSize sizeLargeImage = CSize(32, 32));
	FOUNDATIONEX_API virtual CMFCRibbonCategory* AddCategory(LPCTSTR lpszName, UINT uiSmallImagesResID, UINT uiLargeImagesResID,
		CSize sizeSmallImage = CSize(16, 16), CSize sizeLargeImage = CSize(32, 32), int nInsertAt = -1, CRuntimeClass* pRTI = NULL);
	FOUNDATIONEX_API virtual CMFCRibbonCategory* AddContextCategory(LPCTSTR lpszName, LPCTSTR lpszContextName, UINT uiContextID, AFX_RibbonCategoryColor clrContext,
		UINT uiSmallImagesResID, UINT uiLargeImagesResID, CSize sizeSmallImage = CSize(16, 16), CSize sizeLargeImage = CSize(32, 32), CRuntimeClass* pRTI = NULL);
	FOUNDATIONEX_API virtual CMFCRibbonCategory* AddQATOnlyCategory(LPCTSTR lpszName, UINT uiSmallImagesResID, CSize sizeSmallImage = CSize(16, 16));
	FOUNDATIONEX_API virtual CMFCRibbonCategory* AddPrintPreviewCategory();
	FOUNDATIONEX_API virtual void EnablePrintPreview(BOOL bEnable = TRUE);
	FOUNDATIONEX_API virtual BOOL IsPrintPreviewEnabled() const { return m_wndRibbonBar.IsPrintPreviewEnabled(); }
	FOUNDATIONEX_API virtual int GetCategoryCount() const;
	FOUNDATIONEX_API virtual int GetVisibleCategoryCount() const;
	FOUNDATIONEX_API virtual CMFCRibbonCategory* GetCategory(int nIndex) const;
	FOUNDATIONEX_API virtual int GetCategoryIndex(CMFCRibbonCategory* pCategory) const;
	FOUNDATIONEX_API virtual void ShowCategory(int nIndex, BOOL bShow = TRUE);
	FOUNDATIONEX_API virtual void ShowContextCategories(UINT uiContextID, BOOL bShow = TRUE);
	FOUNDATIONEX_API virtual BOOL HideAllContextCategories();
	FOUNDATIONEX_API virtual BOOL ActivateContextCategory(UINT uiContextID);
	FOUNDATIONEX_API virtual BOOL RemoveCategory(int nIndex);
	FOUNDATIONEX_API virtual void RemoveAllCategories();
	FOUNDATIONEX_API virtual BOOL SetActiveCategory(CMFCRibbonCategory* pCategory, BOOL bForceRestore = FALSE);
	FOUNDATIONEX_API virtual CMFCRibbonCategory* GetActiveCategory() const { return m_wndRibbonBar.GetActiveCategory(); }
	FOUNDATIONEX_API virtual int FindCategoryIndexByData(DWORD dwData) const;
	FOUNDATIONEX_API virtual BOOL GetContextName(UINT uiContextID, CString& strName) const;

	// Tab Helpers
	FOUNDATIONEX_API virtual void AddToTabs(CMFCRibbonBaseElement* pElement);
	FOUNDATIONEX_API virtual void RemoveAllFromTabs();

	// Hyperlinks
	FOUNDATIONEX_API virtual void OpenHyperlink(UINT uiCmdID);
	FOUNDATIONEX_API virtual CString GetHyperlink(UINT uiCmdID);
	FOUNDATIONEX_API virtual void SetHyperlink(UINT uiCmdID, CString& strLink);

	// Progress
	FOUNDATIONEX_API virtual int GetProgressPos(UINT uiCmdID);
	FOUNDATIONEX_API virtual void SetProgressPos(UINT uiCmdID, int iPosition);
	
	// State
	
	// Implement the ribbonbar actions at Applicaiton Open.
	FOUNDATIONEX_API virtual BOOL LoadState();
	// Implement the ribbonbar actions at Application Close.
	FOUNDATIONEX_API virtual BOOL SaveState();

protected:
	// Create Tabs
	FOUNDATIONEX_API virtual BOOL ImplMDITabs(CWnd* pParentWnd, CMDITabInfo* pTabInfo);
	// Implement the RibbonBar.
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
	// Implement the Frequently Used Command Panel.
	FOUNDATIONEX_API virtual BOOL ImplFreqCmdPanel();


protected:
	// Typedefs
	typedef std::map<UINT, CMFCRibbonPanel*> PanelMap;	// Map of Panel ID's and Panel Pointers.
	typedef PanelMap::iterator				PanelMapIter;	// Iterator for PanelMap.

	// RibbonBar for the application.
	CMFCRibbonBar				m_wndRibbonBar;
	// Ribbon application button.
	CMFCRibbonApplicationButton	m_MainButton;
	// Ribbon panel icons.
	CMFCToolBarImages			m_PanelImages;
	// Ribbon StatusBar. Must be present to comply with the Fluent UI.
	CMFCRibbonStatusBar			m_wndStatusBar;
	// Ribbon CaptionBar.
	SFLCaptionBarEx				m_wndCaptionBar;

	// Main Panel attached to the application button.
	CMFCRibbonMainPanel*		m_pMainPanel;
	// Quick Access ToolBar Commands List
	CList<UINT, UINT>			m_lstQATCmds;

	// Did we load from XML Resource?
	BOOL 						m_bLoadedFromResource;
	// Did we create the ribbon elements?
	BOOL						m_bRibbonInitialized;
	// Do we use Frequent Command Panels?
	BOOL						m_bFreqCmdPanels;
	BOOL						m_bFreqCmdPanelsInitialized;

	// Frequently used commands.
	PanelMap					m_mapFreqCmdPanels;
	// Cache of Frequently Used Commands.
	LRUCache<UINT, UINT>		m_cacheFreqCmds;
};

} // namespace sflex

#endif // __SFLRIBBONBAR__H__
