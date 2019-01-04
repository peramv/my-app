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
#if !defined __SFLWPFHELPEREX__H__
#define __SFLWPFHELPEREX__H__

#include "StingrayExportDefs.h"

#ifdef _MANAGED
#pragma managed 

// C++/CLI Headers and Namespaces
#include "FoundationEx .NET\SflCppCLIDefs_Mngd.h"

namespace sflexnet
{
	// Equivalent to C# 'as' keyword.
	template<class T, class U> 
	bool As(U u) 
	{
		return dynamic_cast<T>(u) != nullptr;
	}
	// Equivalent to C# 'is' keyword.
	template<class T, class U> 
	bool Is(U u) 
	{
		return safe_cast<T>(u) != nullptr;
	}

	// Find a child object of type T from a DependencyObject. The 
	// DependencyObject is mostly from the form of FrameworkElement.
	template<class T> 
	T^ FindChild(DependencyObject^ parent, CString strChildName)
	{
		// Confirm parent and childName are valid. 
		if (parent == nullptr) 
			return nullptr;

		String^ childName = gcnew String(strChildName);

		DependencyObject^ foundChild = nullptr;

		int childrenCount = VisualTreeHelper::GetChildrenCount(parent);
		for (int i = 0; i < childrenCount; i++)
		{
			DependencyObject^ child = VisualTreeHelper::GetChild(parent, i);

			// If the child is not of the request child type child
			// T childType = child as T;
			// if (childType == null)
			if(!As<T^>(child))
			{
				// Recursively drill down the tree
				foundChild = FindChild<T>(child, childName);

				// If the child is found, break so we do not overwrite the found child. 
				if (foundChild != nullptr) 
					break;
			}
			else if (!String::IsNullOrEmpty(childName))
			{
				FrameworkElement^ frameworkElement = (FrameworkElement^)child;
				// If the child's name is set for search
				if (frameworkElement != nullptr && frameworkElement->Name == childName)
				{
					// if the child's name is of the request name
					foundChild = (T^)(FrameworkElement^)child;
					return (T^)foundChild;
				}
			}
			else
			{
				// child element found.
				foundChild = (T^)child;
				return (T^)foundChild;
			}
		}

		return (T^)foundChild;
	}

#define SFLEX_WPF_CREATE_CTRL_FROM_VIEW(controlType, controlName, controlString) \
	controlType^ controlName = (controlType^)FindChild<controlType>((DependencyObject^)m_wpfFrameworkElement, controlString);

#define SFLEX_WPF_ASSIGN_CTRL_FROM_VIEW(controlName, controlString) \
	controlName = (controlType^)FindChild<controlType>((DependencyObject^)m_wpfFrameworkElement, controlString);

#define SFLEX_WPF_ASSIGN_DELEGATE(controlName, controlEvent, controlDelegate) \
	if(nullptr != controlName) \
		controlName->controlEvent  += MAKE_DELEGATE(RoutedEventHandler, controlDelegate);

} // namespace sflexnet

#pragma unmanaged
#endif // _MANAGED

#endif // __SFLWPFHELPEREX__H__