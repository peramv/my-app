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
#if !defined __SFLDIALOGEX__H__
#define __SFLDIALOGEX__H__

#include "StingrayExportDefs.h"

namespace sflex
{

// SFLDialogEx

class SFLDialogEx : public CDialogEx
{
	FOUNDATIONEX_DECLARE_DYNAMIC(SFLDialogEx)

public:
	// Construction -----------------------------//
	FOUNDATIONEX_API SFLDialogEx();
	FOUNDATIONEX_API SFLDialogEx(UINT nIDTemplate, CWnd *pParent = NULL);
	FOUNDATIONEX_API SFLDialogEx(LPCTSTR lpszTemplateName, CWnd *pParentWnd = NULL);
	FOUNDATIONEX_API virtual ~SFLDialogEx();

	// Get Icon.
	FOUNDATIONEX_API virtual HICON GetIcon() { return m_hIcon; }
	// Initialize Dialog.
	FOUNDATIONEX_API virtual BOOL OnInitDialog();

protected:
	FOUNDATIONEX_API afx_msg void OnPaint();
	FOUNDATIONEX_DECLARE_MESSAGE_MAP()

protected:
	// Dialog Icon.
	HICON m_hIcon;
};

} // namespace sflex

#endif // __SFLDIALOGEX__H__
