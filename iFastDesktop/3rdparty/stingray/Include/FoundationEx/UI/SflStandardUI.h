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
#if !defined __SFLSTANDARDUI__H__
#define __SFLSTANDARDUI__H__

#include "SFLToolBarEx.h"
#include "SFLMenuBarEx.h"
#include "SFLStatusBarEx.h"
#include "SFLCaptionBarEx.h"

namespace sflex
{

#define SFL_STDUI_DEFAULT_MDITABS	0x1000
#define SFL_STDUI_DEFAULT_TOOLBAR	0x2000
#define SFL_STDUI_DEFAULT_STATUSBAR	0x3000
#define SFL_STDUI_DEFAULT_CAPTIONBAR 0x4000

#define SFL_STDUI_DEFAULT_ALL	(SFL_STDUI_DEFAULT_MDITABS | SFL_STDUI_DEFAULT_MENU | SFL_STDUI_DEFAULT_TOOLBAR | SFL_STDUI_DEFAULT_STATUSBAR | SFL_STDUI_DEFAULT_CAPTIONBAR)

class SFLStandardUI
{
public:
	// Constructor.
	FOUNDATIONEX_API SFLStandardUI(void);
	// Destructor.
	FOUNDATIONEX_API virtual ~SFLStandardUI(void);

	// Get the list of MenuBars.
	inline CList<SFLMenuBarEx*,   SFLMenuBarEx*>& GetMenuBarList() { return m_lstMenuBar; }
	// Get the list of ToolBars.
	inline CList<SFLToolBarEx*,   SFLToolBarEx*>& GetToolBarList() { return m_lstToolBar; }
	// Get the list of StatusBars.
	inline CList<SFLStatusBarEx*, SFLStatusBarEx*>& GetStatusBarList() { return m_lstStatusBar; }
	// Get the list of CaptionBars.
	inline CList<SFLCaptionBarEx*, SFLCaptionBarEx*>& GetCaptionBarList() { return m_lstCaptionBar; }

	// Create the Standard UI, via boolean selection.
	FOUNDATIONEX_API virtual BOOL Create(CWnd* pParentWnd, BOOL bDefaultMDITabs = TRUE, BOOL bDefaultToolBar = TRUE, BOOL bDefaultStatusBar = TRUE, BOOL bDefaultCaptionBar = TRUE);
	// Create the Standard UI, via flags.
	FOUNDATIONEX_API virtual BOOL Create(CWnd* pParentWnd, UINT uiCreateFlags);
	// Create the Standard UI with pointers.
	FOUNDATIONEX_API virtual BOOL CreateEx(CWnd* pParentWnd, CMDITabInfo* pTabInfo, SFLMenuBarEx* pMenuBar, SFLToolBarEx* pToolBar, SFLStatusBarEx* pStatusBar, SFLCaptionBarEx* pCaptionBar);

	// Enable Customization of ToolBars.
	FOUNDATIONEX_API virtual void EnableToolBarCustomize();

protected:
	// Create Tabs
	FOUNDATIONEX_API virtual BOOL ImplDefaultMDITabs(CWnd* pParentWnd, CMDITabInfo* pTabInfo);
	// Create Default MenuBar.
	FOUNDATIONEX_API virtual BOOL ImplDefaultMenuBar(CWnd* pParentWnd, SFLMenuBarEx* pMenuBar);
	// Create Default ToolBar.
	FOUNDATIONEX_API virtual BOOL ImplDefaultToolBar(CWnd* pParentWnd, SFLToolBarEx* pToolBar);
	// Create Default StatusBar.
	FOUNDATIONEX_API virtual BOOL ImplDefaultStatusBar(CWnd* pParentWnd, SFLStatusBarEx* pStatusBar);
	// Create Default CaptionBar.
	FOUNDATIONEX_API virtual BOOL ImplDefaultCaptionBar(CWnd* pParentWnd, SFLCaptionBarEx* pCaptionBar);
	
	// Cleanup.
	FOUNDATIONEX_API virtual void Cleanup();

protected:	
	// List of MenuBars.
	CList<SFLMenuBarEx*,   SFLMenuBarEx*>	m_lstMenuBar;
	// List of ToolBars.
	CList<SFLToolBarEx*,   SFLToolBarEx*>	m_lstToolBar;
	// List of StatusBars.
	CList<SFLStatusBarEx*, SFLStatusBarEx*>	m_lstStatusBar;
	// List of CaptionBars.
	CList<SFLCaptionBarEx*, SFLCaptionBarEx*> m_lstCaptionBar;
};

} // namespace sflex

#endif // __SFLSTANDARDUI__H__
