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
#if !defined __SFLPANEDIALOG__H__
#define __SFLPANEDIALOG__H__

#include "StingrayExportDefs.h"

namespace sflex
{

// SFLPaneDialogEx

class SFLPaneDialogEx : public CPaneDialog
{
	FOUNDATIONEX_DECLARE_DYNAMIC(SFLPaneDialogEx)

public:
	FOUNDATIONEX_API SFLPaneDialogEx();
	FOUNDATIONEX_API virtual ~SFLPaneDialogEx();

	// Override this function to adjust the layout of the
	// dialog controls.
	FOUNDATIONEX_API virtual void AdjustLayout(int cx, UINT uiCtrlID);
	// Get Dialog ID List
	inline virtual CList<UINT, UINT>& GetDlgList() { return m_lstDialogID; }
	FOUNDATIONEX_API BOOL IsThemedBkColor();

protected:
	FOUNDATIONEX_API afx_msg void OnSize(UINT nType, int cx, int cy);
	FOUNDATIONEX_API afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	FOUNDATIONEX_API afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    FOUNDATIONEX_API afx_msg void OnDestroy();
	FOUNDATIONEX_API afx_msg LRESULT OnAppStyleChanged(WPARAM,LPARAM);
	FOUNDATIONEX_DECLARE_MESSAGE_MAP()

protected:
	// List of Dialog IDs.
	CList<UINT, UINT>	m_lstDialogID;
	CBrush* m_pCtlBkBrush;
};

} // namespace sflex

#endif // __SFLPANEDIALOG__H__
