#if !defined __SFLTASKBARMGR__H__
#define __SFLTASKBARMGR__H__

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

#include "StingrayExportDefs.h"

#ifndef __shobjidl_h__
	#include <shobjidl.h>    // For Taskbar Overlay
#endif

namespace sflex
{

#if (WINVER >= 0x0601) && (_MSC_VER >= 1600) // Windows 7 or Higher and VS2010 or Higher.

// SFLTaskbarMgr
class SFLFileRegistrationMgr;

class SFLTaskbarMgr
{
public:
	FOUNDATIONEX_API SFLTaskbarMgr(void);
	FOUNDATIONEX_API virtual ~SFLTaskbarMgr(void);

	//-------------------------------------------//
	// Overlay Icons                             //
	//-------------------------------------------//

	// Get/Set Taskbar Overlay Icon.
	inline virtual UINT GetOverlayIconID() { return m_uiOverlayIcon; }
	inline virtual void SetOverlayIconID(UINT uiIconResID) { m_uiOverlayIcon = uiIconResID; }
	// Get/Set Taskbar Overlay Text.
	inline virtual CString GetOverlayIconText() { return m_strOverlayText; }
	inline virtual void SetOverlayIconText(CString strText) { m_strOverlayText = strText; }
	// Get/Set Taskbar Overlay Icon Handle.
	inline virtual HICON GetOverlayIconHandle() { return m_hiconOverlay; }
	inline virtual void SetOverlayIconHandle(HICON hIcon) { m_hiconOverlay = hIcon; }
	// Set the Taskbar Overlay.
	FOUNDATIONEX_API BOOL SetTaskbarOverlayIcon(UINT uiIconResID, CString strText);
	FOUNDATIONEX_API BOOL SetTaskbarOverlayIcon(HICON hIcon, CString strText);

	//-------------------------------------------//
	// ProgressBar State                         //
	//-------------------------------------------//

	// Set ProgressBar State.
	FOUNDATIONEX_API void SetProgressBarState(TBPFLAG tbpFlags);
	// Get ProgressBar State.
	inline virtual TBPFLAG GetProgressBarState() { return m_tbpFlags; }
	// Set ProgressBar Position.
	FOUNDATIONEX_API void SetProgressBarPosition(int nProgressPos);
	// Get ProgressBar Position.
	inline virtual int GetProgressBarPosition() { return m_iProgressPos; }

	//-------------------------------------------//
	// Jumplist                                  //
	//-------------------------------------------//

	// Add a Jumplist known category. KDC_FREQUENT, KDC_RECENT.
	FOUNDATIONEX_API BOOL AddKnownCategory(KNOWNDESTCATEGORY knownCategory);
	// Add a Jumplist Separator. 
	FOUNDATIONEX_API BOOL AddTaskSeparator();
	// Clear the Jumplist.
	FOUNDATIONEX_API void ClearAll();
	// Commit the Jumplist.
	FOUNDATIONEX_API void CommitList();

	// Open dialog and select the destination path.
	FOUNDATIONEX_API CString SelectDestinationPath(CString strFileExtension);
	// Add the destination path to the jumplist
	FOUNDATIONEX_API BOOL AddDestination(CString strCategoryName, CString strDestinationPath);
	// Open dialog and select the task icon path.
	FOUNDATIONEX_API CString SelectTaskIconPath(CString strFileExtension = _T("Icon Files|*.ico;*.dll;*.exe||"));
	// Open dialog and select the task path.
	FOUNDATIONEX_API CString SelectTaskPath(CString strFileExtension = _T("Executable Files|*.exe;*.cmd||"));
	// Add the task path to the jumplist.
	FOUNDATIONEX_API BOOL AddTask(CString strTargetExecutablePath, CString strCommandLineArgs, CString strTitle, CString strIconLocation, int iIconIndex);

	// Register/Unregister a file type.
	FOUNDATIONEX_API BOOL RegisterFileType(BOOL isRegister, CString strExeName, CString strFileExtension, CString strProgID, CString strDocName, CString strAppUserModeID);

	// Get the Registration File Manager.
	FOUNDATIONEX_API SFLFileRegistrationMgr* GetFileRegistrationMgr();


protected:
	// Taskbar Overlay Icon.
	UINT m_uiOverlayIcon;
	// Taskbar Overlay Text.
	CString m_strOverlayText;
	// Taskbar Overlay Handle.
	HICON m_hiconOverlay;

	TBPFLAG m_tbpFlags;
	// Progressbar Value (Position)
	int m_iProgressPos;

	// Taskbar Jumplist
	 CJumpList m_jumpList;
	 UINT m_uiMaxSlots;
	 CString m_strFileRegistrationTypes;
	 FOUNDATIONEX_API static SFLFileRegistrationMgr*	m_pFileRegistrationMgr;

	 // TODO:
	 // - Add variables for task information.
};

#endif // (WINVER >= 0x0601)

} // namespace sflex

#endif // __SFLTASKBARMGR__H__


