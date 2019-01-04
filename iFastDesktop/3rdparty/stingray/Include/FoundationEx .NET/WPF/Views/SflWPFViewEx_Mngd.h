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
#if !defined __SFLWPFVIEW__H__
#define __SFLWPFVIEW__H__

#include "StingrayExportDefs.h"

#ifdef _MANAGED
#pragma managed 

// C++/CLI Headers and Namespaces
#include "FoundationEx .NET\SflCppCLIDefs_Mngd.h"
#include "FoundationEx .NET\WPF\SflWPFHelperEx_Mngd.h"

namespace sflexnet
{

#define CPPCLI_CTP_WIDTH_OFFSET_BUG 1

// SFLWPFViewEx view

class SFLWPFViewEx : public CView
{
	FOUNDATIONEXNET_DECLARE_DYNCREATE(SFLWPFViewEx)

protected:
	// Protected Constructor
	FOUNDATIONEXNET_API SFLWPFViewEx(); 
	FOUNDATIONEXNET_API virtual ~SFLWPFViewEx();

public:
	FOUNDATIONEXNET_API virtual void OnDraw(CDC* pDC);      // overridden to draw this view
#ifdef _DEBUG
	FOUNDATIONEXNET_API virtual void AssertValid() const;
#ifndef _WIN32_WCE
	FOUNDATIONEXNET_API virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	FOUNDATIONEXNET_DECLARE_MESSAGE_MAP()
public:

	FOUNDATIONEXNET_API virtual BOOL Create(LPCTSTR lpszClassName, 
		                LPCTSTR lpszWindowName, 
		                DWORD dwStyle, 
						const RECT& rect, 
						CWnd* pParentWnd, 
		                UINT nID, 
						CCreateContext* pContext = NULL);

	FOUNDATIONEXNET_API virtual void OnInitialUpdate();
	
	FOUNDATIONEXNET_API afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	FOUNDATIONEXNET_API afx_msg void OnSize(UINT nType, int cx, int cy);

	FOUNDATIONEXNET_API virtual gcroot<FrameworkElement^> GetWpfControl();
	FOUNDATIONEXNET_API void SetWpfType(gcroot<Type^> pType);

	// Override These Methods
	FOUNDATIONEXNET_API virtual bool CreateAndInitializeWpfControl();
	FOUNDATIONEXNET_API virtual void AdjustLayout();

	// Load XAML containing a FrameworkElement as the root. Cannot load with Window as the root element.
	// Assigns the FrameworkElement to m_wpfFrameworkElement.
	FOUNDATIONEXNET_API virtual bool LoadFrameworkElementFromXAML(CString strXAMLFile);
	// Save XAML from the member FrameworkElement as the root. 
	FOUNDATIONEXNET_API virtual bool SaveFramworkElementToXAML(CString strXAMLFile);

	// Find a control in the WPF source window. Usually this will be called when loading from XAML.
	/*template<class T>
	T^ FindControl(CString strControlName)
	{
		return (T^)sflex::FindChild<T>((DependencyObject^)m_wpfFrameworkElement, strControlName);
	}*/

protected:
	// Windows Presentation Foundation Control Members
	// Window
	// ContentControl
	// Control
	// UIElement
	// FrameworkElement

	gcroot<FrameworkElement^> m_wpfFrameworkElement;	// WPF Control
	gcroot<Type^>			  m_wpfControlType;			// WPF Control Type

};

} // namespace sflexnet

#pragma unmanaged
#endif //_MANAGED

#endif // __SFLWPFVIEW__H__
