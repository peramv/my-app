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
#if !defined __SFLAPPSTYLEEX__H__
#define __SFLAPPSTYLEEX__H__

#include "StingrayExportDefs.h"

namespace sflex
{

#define SFLEX_VISUALMANAGER_TAG		_T("VISUALMANAGER")
#define SFLEX_VMCLASS_TAG			_T("Class")
#define SFLEX_VMBASECLASS_TAG		_T("SFLVisualMgr")
#define SFLEX_VMOFFICEXPCLASS_TAG	_T("SFLVisualMgrOfficeXP")
#define SFLEX_VMOFFICE2003CLASS_TAG	_T("SFLVisualMgrOffice2003")
#define SFLEX_VMOFFICE2007CLASS_TAG	_T("SFLVisualMgrOffice2007")
#define SFLEX_VMVS2005CLASS_TAG		_T("SFLVisualMgrVS2005")
#define SFLEX_VMVS2008CLASS_TAG		_T("SFLVisualMgrVS2008")
#define SFLEX_VMWINDOWSCLASS_TAG	_T("SFLVisualMgrWindows")
#define SFLEX_VMWINDOWS7CLASS_TAG	_T("SFLVisualMgrWindows7")

class SFLAppStyleEx
{
public:
	FOUNDATIONEX_API SFLAppStyleEx(void);
	FOUNDATIONEX_API virtual ~SFLAppStyleEx(void);

	enum eAppStyle
	{
		APPSTYLE_WIN_2000 = 0,
		APPSTYLE_WIN_XP,
		APPSTYLE_OFFICE_XP,
		APPSTYLE_OFFICE_2003,
		APPSTYLE_OFFICE_BLUE,
		APPSTYLE_OFFICE_BLACK,
		APPSTYLE_OFFICE_SILVER,
		APPSTYLE_OFFICE_AQUA,
		APPSTYLE_VS_2005,
		APPSTYLE_VS_2008,
		APPSTYLE_WIN_7,
		APPSTYLE_CUSTOM
	};

	// Set the application look and feel / style.
	FOUNDATIONEX_API static void SetApplicationStyle(eAppStyle id, CMFCRibbonBar* pRibbonBar = NULL, CRuntimeClass* pCustomVisualMgr = NULL);
	
	FOUNDATIONEX_API static BOOL LoadApplicationStyle(CString strINI);
	FOUNDATIONEX_API static BOOL SaveApplicationStyle(CString strINI);

	FOUNDATIONEX_API static void ExtractRGBFromString(CString strTokens, int& r, int& g, int& b);
	FOUNDATIONEX_API static void ExtractRGBFromCOLORREF(COLORREF color, int& r, int& g, int& b);
};

} // namespace sflex

#endif // __SFLAPPSTYLEEX__H__
