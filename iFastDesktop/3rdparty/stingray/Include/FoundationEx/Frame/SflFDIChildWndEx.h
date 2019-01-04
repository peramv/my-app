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
#if !defined __SFLFDICHILDWNDEX__H__
#define __SFLFDICHILDWNDEX__H__

#include "StingrayExportDefs.h"
#include "FoundationEx\Frame\SFLFrameWndEx.h"

namespace sflex
{

// SFLFDIChildWndEx frame

class SFLFDIChildWndEx : public SFLFrameWndEx
{
	FOUNDATIONEX_DECLARE_DYNCREATE(SFLFDIChildWndEx)
public:
	// Construction/Destruction.
	FOUNDATIONEX_API SFLFDIChildWndEx(); 
	FOUNDATIONEX_API virtual ~SFLFDIChildWndEx();

	// Creation.
	FOUNDATIONEX_API virtual BOOL Create(LPCTSTR lpszClassName,
									   LPCTSTR lpszWindowName,
									   DWORD dwStyle = WS_OVERLAPPEDWINDOW,
									   const RECT& rect = rectDefault,
									   CWnd* pParentWnd = NULL,        // != NULL for popups
									   LPCTSTR lpszMenuName = NULL,
									   DWORD dwExStyle = 0,
									   CCreateContext* pContext = NULL);
	// Loads the Windows object along with the resources and associates it with the SFLFDIChildWndEx object.
	FOUNDATIONEX_API virtual BOOL LoadFrame(UINT nIDResource, 
									      DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, 
									      CWnd* pParentWnd = NULL, 
									      CCreateContext* pContext = NULL);
	// Sets the calling window as the active window and brings it to the top of the Z-order.
	FOUNDATIONEX_API virtual void ActivateFrame(int nCmdShow = -1);
	// Destroy window.
	FOUNDATIONEX_API virtual BOOL DestroyWindow();
	// Close Window.
	FOUNDATIONEX_API virtual void OnClose();

protected:
	// Override to specify initial size of the window.
	FOUNDATIONEX_API virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	FOUNDATIONEX_API afx_msg void OnWindowNew();
	
	FOUNDATIONEX_API afx_msg void OnParentNotify(UINT message, LPARAM lParam);
	FOUNDATIONEX_API afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	FOUNDATIONEX_API afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	FOUNDATIONEX_API afx_msg BOOL OnNcActivate(BOOL bActive);
	FOUNDATIONEX_DECLARE_MESSAGE_MAP()

protected:
	FOUNDATIONEX_API static int s_xInit;
	FOUNDATIONEX_API static int s_yInit;
	HMENU m_hMenu;
};

} // namespace sflex

#endif // __SFLFDICHILDWNDEX__H__
