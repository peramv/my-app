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
#if !defined __SFLMENUBAREX__H__
#define __SFLMENUBAREX__H__

#include "StingrayExportDefs.h"
#include "afxmenubar.h"

namespace sflex
{

// SFLMenuBarEx

class SFLMenuBarEx : public CMFCMenuBar
{
	FOUNDATIONEX_DECLARE_DYNAMIC(SFLMenuBarEx)

public:
	FOUNDATIONEX_API SFLMenuBarEx();
	FOUNDATIONEX_API virtual ~SFLMenuBarEx();

	// Create from Menu.
	FOUNDATIONEX_API virtual void CreateFromMenu (HMENU hMenu, BOOL bDefaultMenu = FALSE, BOOL bForceUpdate = FALSE);
	// Empty Menu Button?
	FOUNDATIONEX_API virtual BOOL IsMenuButtonEmpty (CMFCToolBarButton* pButton);
	// Add SubMenu.
	FOUNDATIONEX_API virtual void AddSubMenu(UINT idMenu, UINT idrMenu, CString strMenu);
	// Exclude a list of menu commands from showing up. Use empty list to reset.
	FOUNDATIONEX_API static void ExcludeCommands(CList<UINT, UINT>& lstCommands);

protected:
	FOUNDATIONEX_DECLARE_MESSAGE_MAP()
};

} // namespace sflex

#endif // __SFLMENUBAREX__H__
