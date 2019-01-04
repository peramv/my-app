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
#if !defined __SFLVISUALMGROFFICEXP__H__
#define __SFLVISUALMGROFFICEXP__H__

#include "StingrayExportDefs.h"
#include <afxvisualmanagerofficexp.h>

namespace sflex
{

class SFLVisualMgrOfficeXP : public CMFCVisualManagerOfficeXP
{
	FOUNDATIONEX_DECLARE_DYNCREATE(SFLVisualMgrOfficeXP)
public:
	FOUNDATIONEX_API SFLVisualMgrOfficeXP();
	FOUNDATIONEX_API virtual ~SFLVisualMgrOfficeXP();

	FOUNDATIONEX_API enum eColorPart
	{
		eColorNone,
		// AFX GLOBAL
		eColorBtnFace, 
		eColorBtnShadow, 
		eColorBtnHilite,
		eColorBtnText, 
		eColorWindowFrame,
		eColorBtnDkShadow, 
		eColorBtnLight,
		eColorGrayedText,
		eColorHilite,
		eColorTextHilite,
		eColorHotLinkNormalText,
		eColorHotLinkHoveredText,
		eColorHotLinkVisitedText,
		eColorBarWindow,
		eColorBarFace,
		eColorBarShadow, 
		eColorBarHilite,
		eColorBarDkShadow, 
		eColorBarLight,
		eColorBarText,
		eColorWindow,
		eColorWindowText,
		eColorCaptionText,
		eColorMenuText,
		eColorActiveCaption,
		eColorInactiveCaption,
		eColorInactiveCaptionText,
		eColorActiveBorder,
		eColorInactiveBorder,
		// Windows 2000
		eColorMenuShadowBase,
		// Office XP
		eColorBarBkgnd,            
		eColorMenuRarelyUsed,
		eColorMenuLight,           
		eColorInactiveTabText,
		eColorHighlight,           
		eColorHighlightDn,         
		eColorHighlightChecked,
		eColorPressedButtonBorder, 
		eColorGripper,
		eColorSeparator,
		eColorPaneBorder,          
		eColorMenuBorder,          
		eColorMenuItemBorder
	};

	// Get/Set Color Parts.
	FOUNDATIONEX_API COLORREF	GetColorPart(const eColorPart iPart);
	FOUNDATIONEX_API void		SetColorPart(const eColorPart iPart, COLORREF iColor);

	FOUNDATIONEX_API BOOL LoadApplicationStyle(CString strINI);
	FOUNDATIONEX_API BOOL SaveApplicationStyle(CString strINI);
};

} // namespace sflex

#endif // __SFLVISUALMGROFFICEXP__H__