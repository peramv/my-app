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
#if !defined __SFLWINAPPEX__H__
#define __SFLWINAPPEX__H__

#include "StingrayExportDefs.h"
#include "FoundationEx\Application\SFLAppStyleEx.h"

namespace sflex
{

// SFLWinAppEx

class SFLWinAppEx : public CWinAppEx
{
	FOUNDATIONEX_DECLARE_DYNAMIC(SFLWinAppEx)

public:
	FOUNDATIONEX_API SFLWinAppEx();
	FOUNDATIONEX_API virtual ~SFLWinAppEx();

	// Get the Application Style.
	FOUNDATIONEX_API virtual SFLAppStyleEx::eAppStyle GetAppStyle();
	// Set the Application Style. Returns old style.
	FOUNDATIONEX_API virtual SFLAppStyleEx::eAppStyle SetAppStyle(SFLAppStyleEx::eAppStyle eStyle);
	// Load a custom Application Style from INI.
	FOUNDATIONEX_API virtual BOOL LoadApplicationStyle(CString strINI);
	// Save a custom Application Style to INI.
	FOUNDATIONEX_API virtual BOOL SaveApplicationStyle(CString strINI);
	// Are we using High Color Icons?
	FOUNDATIONEX_API virtual BOOL HasHighColorIcons();

	// Get the Application Registry Key.
	inline virtual CString GetAppRegKey() { return m_strAppRegKey; }
	// Set the Application Registry Key.
	inline virtual void SetAppRegKey(CString& strRegKey) { m_strAppRegKey = strRegKey; }
	// Get the Application Registry Base.
	inline virtual CString GetAppRegBase() { return m_strAppRegBase; }
	// Set the Application Registry Base.
	inline virtual void SetAppRegBase(CString& strRegBase) { m_strAppRegBase = strRegBase; }
	// Is the layout Right to Left?
	inline virtual BOOL IsRTL() { return m_bIsRTL; }
	// Is the Style Loaded from File?
	inline virtual BOOL IsStyleLoadedFromFile() { return m_bIsStyleLoadedFromFile; }
	// Set layout to Right to Left. True on success.
	FOUNDATIONEX_API virtual BOOL SetRTL(CWnd* pWnd, BOOL bRTL);

	// Initialize Managers in App's InitInstance().
	FOUNDATIONEX_API virtual BOOL Initialize(BOOL bInitOleLibs	  = TRUE,
										BOOL bCtrlContainer	  = TRUE,
										BOOL bRegistryKey	  = TRUE,
										BOOL bInitKeyboardMgr = TRUE, 
										BOOL bInitMouseMgr	  = TRUE,
										BOOL bInitContextMgr  = TRUE,
										BOOL bInitTooltipMgr  = TRUE,
										BOOL bInitShellMgr    = TRUE,
										BOOL bRestartMgr	  = TRUE);

#if (_MSC_VER >= 1600) && (NTDDI_VERSION >= NTDDI_VISTA) // VC10 and Windows Vista or Higher
	// Definitions from afxwin.h-------------------------------------
	// Restart Manager support flags
	//#define AFX_RESTART_MANAGER_SUPPORT_RESTART			0x01  // restart support, means application is registered via RegisterApplicationRestart
	//#define AFX_RESTART_MANAGER_SUPPORT_RECOVERY			0x02  // recovery support, means application is registered via RegisterApplicationRecoveryCallback
	//#define AFX_RESTART_MANAGER_AUTOSAVE_AT_RESTART		0x04  // auto-save support is enabled, documents will be autosaved at restart by restart manager
	//#define AFX_RESTART_MANAGER_AUTOSAVE_AT_INTERVAL		0x08  // auto-save support is enabled, documents will be autosaved periodically for crash recovery
	//#define AFX_RESTART_MANAGER_REOPEN_PREVIOUS_FILES		0x10  // reopen of previously opened documents is enabled, on restart all previous documents will be opened
	//#define AFX_RESTART_MANAGER_RESTORE_AUTOSAVED_FILES	0x20  // restoration of auto-saved documents is enabled, on restart user will be prompted to open auto-saved documents intead of last saved
	//#define AFX_RESTART_MANAGER_SUPPORT_NO_AUTOSAVE		AFX_RESTART_MANAGER_SUPPORT_RESTART | AFX_RESTART_MANAGER_SUPPORT_RECOVERY | AFX_RESTART_MANAGER_REOPEN_PREVIOUS_FILES
	//#define AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS		AFX_RESTART_MANAGER_SUPPORT_NO_AUTOSAVE | AFX_RESTART_MANAGER_AUTOSAVE_AT_RESTART | AFX_RESTART_MANAGER_AUTOSAVE_AT_INTERVAL | AFX_RESTART_MANAGER_RESTORE_AUTOSAVED_FILES
	//#define AFX_RESTART_MANAGER_SUPPORT_RESTART_ASPECTS	AFX_RESTART_MANAGER_SUPPORT_RESTART | AFX_RESTART_MANAGER_AUTOSAVE_AT_RESTART | AFX_RESTART_MANAGER_REOPEN_PREVIOUS_FILES | AFX_RESTART_MANAGER_RESTORE_AUTOSAVED_FILES
	//#define AFX_RESTART_MANAGER_SUPPORT_RECOVERY_ASPECTS	AFX_RESTART_MANAGER_SUPPORT_RECOVERY | AFX_RESTART_MANAGER_AUTOSAVE_AT_INTERVAL | AFX_RESTART_MANAGER_REOPEN_PREVIOUS_FILES | AFX_RESTART_MANAGER_RESTORE_AUTOSAVED_FILES
	//------------------------------------------------------------------
	// Restart Manager. This should be called in the application constructor.
	FOUNDATIONEX_API virtual void EnableRestartManager(DWORD dwRestartFlags = AFX_RESTART_MANAGER_SUPPORT_RECOVERY_ASPECTS |  AFX_RESTART_MANAGER_SUPPORT_RESTART_ASPECTS);
#endif

	// Helpers

	// Application exe name.
	FOUNDATIONEX_API CString GetAppExeName();
	// Application name.
	FOUNDATIONEX_API CString GetAppName();
	// Application full path with exe.
	FOUNDATIONEX_API CString GetAppFullPathWithExe();
	// Application full path.
	FOUNDATIONEX_API CString GetAppFullPath();

protected: 
	// The Application Style.
	SFLAppStyleEx::eAppStyle  m_eAppStyle;
	// Using High Color Icons?
	BOOL  m_bHighColorIcons;
	// App Registry Key.
	CString m_strAppRegKey;
	// App Registry Base.
	CString m_strAppRegBase;
	// Right to Left layout?
	BOOL m_bIsRTL;
	// Loaded Style from File?
	BOOL m_bIsStyleLoadedFromFile;

protected:
	FOUNDATIONEX_DECLARE_MESSAGE_MAP()

protected:
	// Change the layout LTR - RTL. True on success.
	FOUNDATIONEX_API virtual BOOL ChangeRTLLayout(CWnd* pWnd, BOOL bNoLoopOverPopup = FALSE, BOOL bTopLevel = FALSE);
	#if (_MSC_VER >= 1600) && (NTDDI_VERSION >= NTDDI_VISTA) // VC10 and Windows Vista or Higher
	// Setup Restart Manager Options
	FOUNDATIONEX_API virtual BOOL InitRestartManager();
	#endif
};

} // namespace sflex

#endif // __SFLWINAPPEX__H__
