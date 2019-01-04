///////////////////////////////////////////////////////////////////////////////
// MvcMsgHandler.h : AFX message handler interface.
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
//          Supplement Section 227.7202, Government�s use, duplication or
//          disclosure of the computer software is subject to the restrictions
//          set forth by Rogue Wave Software, Inc.
//
///////////////////////////////////////////////////////////////////////////////
//
// Author:       Jeff Boenig and Dean Hallman
// Description:  AFX message handler interface.
//

#pragma once

#ifndef __MFC_MVCMSGHANDLER_H__
#define __MFC_MVCMSGHANDLER_H__

//
// MVC Extension DLL
// Initialize declaration context
//
#ifdef _SFLDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    SFL_DATAEXT
#endif //_SFLDLL

#include <StingrayExportDefs.h>

namespace stingray {
namespace foundation {

//@doc IMvcMsgHandler
//@mfunc BOOL | IMvcMsgHandler | OnWndMsg | A windows message is being delegated to this component for handling
//@parm UINT | message | The windows message being handled
//@parm WPARAM | wParam | Specifies additional message-dependent information.
//@parm LPARAM | lParam | Specifies additional message-dependent information.
//@parm LRESULT* | pResult | The return value
//@xref <c IMvcMsgHandler>

//@doc IMvcMsgHandler
//@mfunc BOOL | IMvcMsgHandler | OnCmdMsg | A command message is being delegated to this component for handling
//@parm UINT | nID | Contains the command ID.
//@parm int | nCode | Identifies the command notification code.
//@parm void* | pExtra | Used according to the value of nCode.
//@parm AFX_CMDHANDLERINFO* | pHandlerInfo | If not NULL, OnCmdMsg fills in the pTarget and pmf members of the pHandlerInfo structure instead of dispatching the command. Typically, this parameter should be NULL.
//@xref <c IMvcMsgHandler>

//@class Interface that supports message handling. Classes that support this interface
// can route and process Windows messages. Basically, this is an interface to a small
// subset of CCmdTarget. Classes derived from CCmdTarget can easily support this interface.
class FOUNDATION_API IMvcMsgHandler
{
public:
	//@cmember
	/* A windows message is being delegated to this component for handling*/
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult) = 0;

	//@cmember
	/* The command message is being delegated to this component for handling*/
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) = 0;
};

///////////////////////////////////////////////////////////////////////////

};  // namespace stingray::foundation
};  // namespace stingray

//
// MVC Extension DLL
// Reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif  // #ifndef __MFC_MVCMSGHANDLER_H__
