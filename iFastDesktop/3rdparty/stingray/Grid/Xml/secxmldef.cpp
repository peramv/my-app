///////////////////////////////////////////////////////////////////////////////
// secxmldef.cpp : SFL XML package
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
// Author: Daniel Jebaraj       
// Description: XML read/write helper classes
//

#define _OG_EXPORT_IMPL

#include "stdafx.h"

#ifdef NTDDI_VERSION
	#if NTDDI_VERSION >= NTDDI_VISTA
		#import "msxml6.dll" exclude("tagDOMNodeType", "DOMNodeType")
	#else
		#import "msxml.dll" exclude("tagDOMNodeType", "DOMNodeType")
	#endif
#else
#import "msxml.dll" exclude("tagDOMNodeType", "DOMNodeType")
#endif

#include "grid\secxmldef.h"

#ifdef _GXDLL
// used for MFC 2.5 Extension DLL
	#undef AFXAPI_DATA
	#define AFXAPI_DATA __based(__segname("_DATA"))
#endif

using namespace std;
using namespace rw;

//@mfunc Constructor
//@parm const XML_ENTRY_MAP* _pEntry
//@parm  MSXML::IXMLDOMNode* _pContextNode
//@parm          DWORD _dwContext
//@parm  void* _pVoidInfo
//#ifdef NTDDI_VERSION
//	#if NTDDI_VERSION >= NTDDI_VISTA
//		XML_ENTRY_PARAM::XML_ENTRY_PARAM(const XML_ENTRY_MAP* _pEntry, ::IXMLDOMNode* _pContextNode,
//									 DWORD _dwContext, void* _pVoidInfo)
//	#else
//		XML_ENTRY_PARAM::XML_ENTRY_PARAM(const XML_ENTRY_MAP* _pEntry, MSXML::IXMLDOMNode* _pContextNode,
//									DWORD _dwContext, void* _pVoidInfo)
//	#endif
//#else
	XML_ENTRY_PARAM::XML_ENTRY_PARAM(const XML_ENTRY_MAP* _pEntry, IXMLDN* _pContextNode,
								DWORD _dwContext, void* _pVoidInfo)
//#endif
{
	pEntry = _pEntry;
	pContextNode = _pContextNode;
	dwContext = _dwContext;
	pVoidInfo = _pVoidInfo;
}
