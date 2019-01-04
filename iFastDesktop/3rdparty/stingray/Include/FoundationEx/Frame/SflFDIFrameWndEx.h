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
#if !defined __SFLFDIFRAMEWNDEX__H__
#define __SFLFDIFRAMEWNDEX__H__

#include "StingrayExportDefs.h"
#include "FoundationEx\Frame\SFLFrameWndEx.h"
#include "FoundationEx\Res\SFLResEx.h"

namespace sflex
{

// SFLFDIFrameWndEx frame

class SFLFDIFrameWndEx : public SFLFrameWndEx
{
	FOUNDATIONEX_DECLARE_DYNCREATE(SFLFDIFrameWndEx)
public:
	FOUNDATIONEX_API SFLFDIFrameWndEx();
	FOUNDATIONEX_API virtual ~SFLFDIFrameWndEx();

public:
	// Add a window.
	FOUNDATIONEX_API virtual void AddWindow(CWnd* pWnd);
	// Remove a window.
	FOUNDATIONEX_API virtual void RemoveWindow(CWnd* pWnd);
	// Set the active window.
	FOUNDATIONEX_API virtual void SetActiveWindow(CWnd* pWnd);
	// Get the active window.
	FOUNDATIONEX_API virtual CWnd* GetActiveWindow() const;
	// Get the active frame.
	FOUNDATIONEX_API virtual CFrameWndEx* GetActiveFrame();
	// Command Messages
	FOUNDATIONEX_API virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

	// Get list of children.
	inline CPtrList* GetChildList() { return &m_lstChildren; }

protected:
	FOUNDATIONEX_API afx_msg BOOL OnActivateWindow(UINT nID);
	FOUNDATIONEX_API afx_msg void OnUpdateWindowMenu(CCmdUI* pCmdUI);
	FOUNDATIONEX_API afx_msg void OnClose();
	FOUNDATIONEX_DECLARE_MESSAGE_MAP()

protected:
	// Active Window.
	CWnd* m_pActiveWnd;
	// List of children.
	CPtrList m_lstChildren;
};

class SFLWindowsDialogEx : public CDialog
{
public:
	FOUNDATIONEX_API SFLWindowsDialogEx(CWnd* pParent = NULL, CPtrList* pChildren = NULL);
	
	enum { IDD = IDD_SFLEX_WINDOWS };

protected:
	FOUNDATIONEX_API virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	FOUNDATIONEX_API virtual BOOL OnInitDialog();
	FOUNDATIONEX_API afx_msg void OnCloseWindow();
	FOUNDATIONEX_API virtual void OnOK();
	FOUNDATIONEX_API afx_msg void OnSave();
	FOUNDATIONEX_DECLARE_MESSAGE_MAP()

protected:
	CObList*  m_pWindowList;
	CPtrList* m_pChildren;
};

} // namespace sflex

#endif // __SFLFDIFRAMEWNDEX__H__
