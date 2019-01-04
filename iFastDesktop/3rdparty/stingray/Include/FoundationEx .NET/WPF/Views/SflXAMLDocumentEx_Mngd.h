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
#if !defined __SFLXAMLDOCUMENTEX__H__
#define __SFLXAMLDOCUMENTEX__H__

#include "StingrayExportDefs.h"

#ifdef _MANAGED
#pragma managed 

// C++/CLI Headers and Namespaces
#include "FoundationEx .NET\SflCppCLIDefs_Mngd.h"

namespace sflexnet
{

// SFLXAMLDocumentEx document

class SFLXAMLDocumentEx : public CDocument
{
	FOUNDATIONEXNET_DECLARE_DYNCREATE(SFLXAMLDocumentEx)

public:
	FOUNDATIONEXNET_API SFLXAMLDocumentEx();
	FOUNDATIONEXNET_API virtual ~SFLXAMLDocumentEx();
#ifndef _WIN32_WCE
	FOUNDATIONEXNET_API virtual void Serialize(CArchive& ar);   // overridden for document i/o
#endif
#ifdef _DEBUG
	FOUNDATIONEXNET_API virtual void AssertValid() const;
#ifndef _WIN32_WCE
	FOUNDATIONEXNET_API virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	FOUNDATIONEXNET_API virtual BOOL OnNewDocument();

	FOUNDATIONEXNET_DECLARE_MESSAGE_MAP()
public:
	// Load current document from a XAML file *.xaml.
	FOUNDATIONEXNET_API virtual gcroot<FrameworkElement^> LoadXAML(CString strXAMLFile);
	// Save current document as a XAML file *.xaml.
	FOUNDATIONEXNET_API virtual bool SaveXAML(CString strXAMLFile);

	inline gcroot<FrameworkElement^>& GetWpfFrameworkElement() { return m_wpfFrameworkElement; } 

public:
	// The FrameworkElement loaded from XAML.
	// This will be assigned to the SFLWPFViewEx's m_wpfFrameworkElement.
	gcroot<FrameworkElement^> m_wpfFrameworkElement;
};

} // namespace sflexnet

#pragma unmanaged
#endif // _MANAGED

#endif // __SFLXAMLDOCUMENTEX__H__
