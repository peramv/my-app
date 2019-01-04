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
#if !defined __SFLDOCKABLEPANE__H__
#define __SFLDOCKABLEPANE__H__

#include "StingrayExportDefs.h"
#include "afxdockablepane.h"

namespace sflex
{

// SRSTUDIO-952
// All code in this file is unmanaged code unless specified with the '#pragma managed' tag.
// We specify '#pragma unmanaged' to avoid errors in the initialization of mixed assemblies.
#pragma warning(disable: 4949)
#pragma unmanaged

// SFLDockablePaneEx

class SFLDockablePaneEx : public CDockablePane
{
	FOUNDATIONEX_DECLARE_DYNAMIC(SFLDockablePaneEx)

public:
	FOUNDATIONEX_API SFLDockablePaneEx();
	FOUNDATIONEX_API virtual ~SFLDockablePaneEx();

public:
	//----------------------------------------------//
	// These functions are provided for compability //
	// with the SECControlBar class. In some cases  //
	// the function names have been changed.        //
	//----------------------------------------------//

	// Unique IDs -------------------------------//
	// Get a Unique Bar ID. Replaces GetUniqueBarID().
	FOUNDATIONEX_API static UINT GetUniqueID(CWnd* pFrameWnd,UINT nBaseID = 0x100);
	// Verify that we have unique IDs. Replaces VerifyUniqueBarIds.
	FOUNDATIONEX_API static BOOL VerifyUniqueIds(CWnd* pFrameWnd);
	// Verify that a specific ID is unique. Replaces VerifyUniqueSpecificBarID.
	FOUNDATIONEX_API static BOOL VerifyUniqueSpecificID(CWnd* pFrameWnd, UINT nBarID);

	// Auto Hide --------------------------------//
	// Is Pinned?
	inline BOOL IsPinned() { return IsAutoHideMode(); }
	// Are we hiding left?
	inline BOOL IsHideLeft() { return IsAutoHideMode() && (GetCurrentAlignment() == CBRS_ALIGN_LEFT); }
    // Are we hiding right?
	inline BOOL IsHideRight() { return IsAutoHideMode() && (GetCurrentAlignment() == CBRS_ALIGN_RIGHT); }
    // Are we hiding Top?
	inline BOOL IsHideTop() { return IsAutoHideMode() && (GetCurrentAlignment() == CBRS_ALIGN_TOP); }
    // Are we hiding Bottom?
	inline BOOL IsHideBottom() { return IsAutoHideMode() && (GetCurrentAlignment() == CBRS_ALIGN_BOTTOM); }
	
	// Docking ----------------------------------//
	// Are we aligned on the left dockbar?
	inline BOOL IsLeftAligned() { return GetParent()->GetDlgCtrlID() == AFX_IDW_DOCKBAR_LEFT; }
    // Are we aligned on the right dockbar?
	inline BOOL IsRightAligned() { return GetParent()->GetDlgCtrlID() == AFX_IDW_DOCKBAR_RIGHT; }
    // Are we aligned on the top dockbar?
	inline BOOL IsTopAligned() { return GetParent()->GetDlgCtrlID() == AFX_IDW_DOCKBAR_TOP; }
    // Are we aligned on the bottom dockbar?
	inline BOOL IsBottomAligned() { return GetParent()->GetDlgCtrlID() == AFX_IDW_DOCKBAR_BOTTOM; }
	// Are we vertically aligned?
	inline BOOL IsVertAligned() { return IsLeftAligned() || IsRightAligned(); }
    // Are we horizontally aligned?
	inline BOOL IsHorzAligned() { return IsTopAligned() || IsBottomAligned(); }

	// Gripper ----------------------------------//
	// Has a Gripper?
	inline BOOL HasGripper() { return m_bHasGripper; }

	// Rects ------------------------------------//
	// Get the internal rect. 
	inline void	GetInsideRect(CRect& rectInside) const { GetClientRect(rectInside); }

protected:
	FOUNDATIONEX_DECLARE_MESSAGE_MAP()

protected:
	//-------------------------------------------//
	// Helpers                                   //
	//-------------------------------------------//

	// Get the CDockingManager associated with the frame.
	FOUNDATIONEX_API static CDockingManager* GetDockingManager(CWnd* pFrameWnd);
};

} // namespace sflex

#endif // __SFLDOCKABLEPANE__H__
