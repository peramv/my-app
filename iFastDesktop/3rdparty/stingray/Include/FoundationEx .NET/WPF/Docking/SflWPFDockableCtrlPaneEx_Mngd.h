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
#if !defined __SFLWPFDOCKABLECTRLPANE__H__
#define __SFLWPFDOCKABLECTRLPANE__H__

#include "StingrayExportDefs.h"
#include "FoundationEx .NET\WPF\sflWPFHelperEx_Mngd.h"
#include "FoundationEx\Docking\SflDockablePaneEx.h"
using namespace sflex;

#ifdef _MANAGED
#pragma managed

namespace sflexnet
{

#ifndef CPPCLI_CTP_WIDTH_OFFSET_BUG
#define CPPCLI_CTP_WIDTH_OFFSET_BUG 1
#endif 

class SFLWPFDockableCtrlPaneEx : public sflex::SFLDockablePaneEx
{
public:
	FOUNDATIONEXNET_API SFLWPFDockableCtrlPaneEx();
	FOUNDATIONEXNET_API virtual ~SFLWPFDockableCtrlPaneEx();

	// Override this function if you don't not want to 
	// take up the entire client area of the Dockable Pane.
	FOUNDATIONEXNET_API virtual void AdjustLayout();
	// Override this function to add your own custom control creation.
	FOUNDATIONEXNET_API virtual BOOL CreateControl();
	// Get the control.
	inline virtual gcroot<FrameworkElement^> GetWpfControl() { return m_wpfFrameworkElement; }
	// Set the WPF Control type.
	inline void SetWpfType(gcroot<Type^> pType) { m_wpfControlType = pType; }
	// Set the control ID.
	inline virtual void SetControlID(UINT id) { m_uiControlID = id; }
	// Get the control ID.
	inline virtual UINT GetControlID() { return m_uiControlID; }
	
protected:
	FOUNDATIONEXNET_API afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	FOUNDATIONEXNET_API afx_msg void OnSize(UINT nType, int cx, int cy);
	FOUNDATIONEXNET_DECLARE_MESSAGE_MAP()

protected:
	gcroot<FrameworkElement^>	m_wpfFrameworkElement;	// WPF Control
	gcroot<Type^>				m_wpfControlType;		// WPF Control Type
	CRect						m_rcClient;
	UINT						m_uiControlID;
};

///////////////////////////////////////////////////////////



} // namespace sflexnet

#pragma unmanaged
#endif // _MANAGED

#endif // __SFLWPFDOCKABLECTRLPANE__H__