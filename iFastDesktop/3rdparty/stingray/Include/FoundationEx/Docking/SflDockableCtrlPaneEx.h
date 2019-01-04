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
#if !defined __SFLDOCKABLECTRLPANE__H__
#define __SFLDOCKABLECTRLPANE__H__

#include "StingrayExportDefs.h"

namespace sflex
{

// SRSTUDIO-952
// All code in this file is unmanaged code unless specified with the '#pragma managed' tag.
// We specify '#pragma unmanaged' to avoid errors in the initialization of mixed assemblies.
#pragma warning(disable: 4949)
#pragma unmanaged

// SFLDockableCtrlPaneEx

template<class T>
class SFLDockableCtrlPaneEx : public SFLDockablePaneEx
{
public:
	SFLDockableCtrlPaneEx();
	virtual ~SFLDockableCtrlPaneEx();

	// Override this function if you don't not want to 
	// take up the entire client area of the Dockable Pane.
	virtual void AdjustLayout();
	// Override this function to add your own custom control creation.
	virtual BOOL CreateControl();
	// Get the control.
	inline virtual T* GetControl() { return &m_wndControl; }
	// Set the control ID.
	inline virtual void SetControlID(UINT id) { m_uiControlID = id; }
	// Get the control ID.
	inline virtual UINT GetControlID() { return m_uiControlID; }
	
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()

protected:
	T		m_wndControl;
	CRect	m_rcClient;
	UINT	m_uiControlID;
};

///////////////////////////////////////////////////////////
//IMPLEMENT_DYNAMIC(SFLDockableCtrlPaneEx, CDockablePane)

template<class T>
SFLDockableCtrlPaneEx<T>::SFLDockableCtrlPaneEx()
{

}

template<class T>
SFLDockableCtrlPaneEx<T>::~SFLDockableCtrlPaneEx()
{
	m_uiControlID = 0x00000000;
}

BEGIN_TEMPLATE_MESSAGE_MAP(SFLDockableCtrlPaneEx, T, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

template<class T>
int SFLDockableCtrlPaneEx<T>::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if(CDockablePane::OnCreate(lpCreateStruct) == -1)
	{
		TRACE(_T("Failed to create SFLDockableCtrlPaneEx<T>.\n"));
		return -1;
	}

	// You must override this function and provide proper creation 
	// of the control, if different from this default.
	if(!CreateControl())
	{
		TRACE(_T("Failure in SFLDockableCtrlPaneEx<T>::CreateControl().\n"));
		return -1;
	}

	// Override this function if you do not want to take up the 
	// entire client area.
	//AdjustLayout();

	return 0;
}

template<class T>
void SFLDockableCtrlPaneEx<T>::AdjustLayout()
{
	if(m_wndControl.GetSafeHwnd() != NULL)
	{
		GetClientRect(m_rcClient);
		// Some control classes may fail here. If so, override this function and provide
		// the correct layout functionality.
		m_wndControl.SetWindowPos(NULL, m_rcClient.left, m_rcClient.top, m_rcClient.Width(), m_rcClient.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	}
}

template<class T>
BOOL SFLDockableCtrlPaneEx<T>::CreateControl()
{
	// This is the default creation routine. It may not work for all controls.
	// If so, override this function and provide the correct creation routine.
	GetClientRect(m_rcClient);
	if(!GetControl()->Create(WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, m_rcClient, this, GetControlID()))
	{
		TRACE(_T("Failed to create control in SFLDockableCtrlPaneEx<T>::CreateControl().\n"));
		return FALSE;
	}
	return TRUE;
}

template<class T>
void SFLDockableCtrlPaneEx<T>::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

} // namespace sflex

#endif // __SFLDOCKABLECTRLPANE__H__
