///////////////////////////////////////////////////////////////////////////////
// gxplugin.cpp : implementation of the CGXPluginComponent class
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
///////////////////////////////////////////////////////////////////////////////
//
// Author: Stefan Hoenig
//

#define _OG_EXPORT_IMPL

#include "stdafx.h"

#ifdef _GXDLL
#undef AFXAPI_DATA
#define AFXAPI_DATA __based(__segname("_DATA"))
#endif

#include "grid\gxresrc.h"

#include "grid\gxplugin.h"

#ifdef _GXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNAMIC(CGXPluginComponent, CWnd);

CGXPluginComponent::CGXPluginComponent()
{
	m_bSkipOtherPlugins = FALSE;
	m_bExitMesssage = FALSE;
}

CGXPluginComponent::~CGXPluginComponent()
{
	// make sure Detach won't get called
	m_hWnd = NULL;
}

BEGIN_MESSAGE_MAP(CGXPluginComponent, CWnd)
	//{{AFX_MSG_MAP(CGXPluginComponent)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CGXPluginComponent::PlugIn(CWnd* pParentWnd)
{
	m_hWnd = pParentWnd->GetSafeHwnd();

	return TRUE;
}

BOOL CGXPluginComponent::HandleMessage(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	m_bSkipOtherPlugins = FALSE;
	m_bExitMesssage = FALSE;

#if _MFC_VER >= 0x0400
	return CWnd::OnWndMsg(message, wParam, lParam, pResult);
#else
	*pResult = CWnd::WindowProc(message, wParam, lParam);
	return TRUE;
#endif
}

LRESULT CGXPluginComponent::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// do nothing - this makes sure that calls to Default() 
	// will have no effect (and thus make sure that the same
	// message is not process twice).

	// Unused:
	message, wParam, lParam;

	return 0;
}

#ifdef _DEBUG
void CGXPluginComponent::AssertValid() const
{
	if (m_hWnd == NULL)
		return;     // null (unattached) windows are valid

	// should be a normal window
	ASSERT(::IsWindow(m_hWnd));

	// Regular CWnd's check the permanent or temporary handle map
	// and compare the pointer to this.
	// This will fail for a CGXPluginComponent because several
	// Plugin objects share the same HWND. Therefore we must not
	// call CWnd::AsssertValid.
}

void CGXPluginComponent::Dump(CDumpContext& dc) const
{
	dc << "PluginComponent";

	// It is safe to call CWnd::Dump
	CWnd::Dump(dc);
}

#endif


