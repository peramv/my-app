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
#if !defined __SFLVISUALMGR__H__
#define __SFLVISUALMGR__H__

#include "StingrayExportDefs.h"
#include "afxvisualmanager.h"

namespace sflex
{

class SFLVisualMgr : public CMFCVisualManager
{
public:
	FOUNDATIONEX_API SFLVisualMgr();
	FOUNDATIONEX_API virtual ~SFLVisualMgr();

	FOUNDATIONEX_DECLARE_DYNCREATE(SFLVisualMgr);

public:
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
		eColorMenuShadowBase
	};

/*	clrBtnFace 
	clrBtnShadow 
	clrBtnHilite
	clrBtnText 
	clrWindowFrame
	clrBtnDkShadow 
	clrBtnLight
	clrGrayedText
	clrHilite
	clrTextHilite
	clrHotLinkNormalText
	clrHotLinkHoveredText
	clrHotLinkVisitedText
	clrBarWindow
	clrBarFace
	clrBarShadow 
	clrBarHilite
	clrBarDkShadow 
	clrBarLight
	clrBarText
	clrWindow
	clrWindowText
	clrCaptionText
	clrMenuText
	clrActiveCaption
	clrInactiveCaption
	clrInactiveCaptionText
	clrActiveBorder
	clrInactiveBorder

*/



	// Get/Set Color Parts.
	FOUNDATIONEX_API COLORREF	GetColorPart(const eColorPart iPart);
	FOUNDATIONEX_API void		SetColorPart(const eColorPart iPart, COLORREF iColor);

	FOUNDATIONEX_API BOOL LoadApplicationStyle(CString strINI);
	FOUNDATIONEX_API BOOL SaveApplicationStyle(CString strINI);
};

} // namespace sflex

//-------------------------------------//
// Visual Manager Headers              //
//-------------------------------------//

// Microsoft Office
#include "FoundationEx\Manager\Visual\SflVisualMgrOfficeXP.h"
#include "FoundationEx\Manager\Visual\SflVisualMgrOffice2003.h"
#include "FoundationEx\Manager\Visual\SflVisualMgrOffice2007.h"

// Microsoft Visual Studio
#include "FoundationEx\Manager\Visual\SflVisualMgrVS2005.h"
#include "FoundationEx\Manager\Visual\SflVisualMgrVS2008.h"

// Microsoft Windows
#include "FoundationEx\Manager\Visual\SflVisualMgrWindows.h"
#include "FoundationEx\Manager\Visual\SflVisualMgrWindows7.h"

#endif // __SFLVISUALMGR__H__
