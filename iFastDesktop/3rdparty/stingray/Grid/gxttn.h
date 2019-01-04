// This is a part of the Objective Grid C++ Library.
// Copyright © 1999-2004 Quovadx, Inc.  All Rights Reserved.
// 
// 
// This computer software is owned by Quovadx, Inc. and is protected by 
// U.S. copyright laws and other laws and by international treaties. This 
// computer software is furnished by Quovadx, Inc. pursuant to a written 
// license agreement and may be used, copied, transmitted, and stored 
// only in accordance with the terms of such license agreement and with 
// the inclusion of the above copyright notice.  This computer software or 
// any other copies thereof may not be provided or otherwise made available 
// to any other person.
// 
// U.S. Government Restricted Rights.  This computer software: 
//      (a) was developed at private expense and is in all respects the 
//          proprietary information of Quovadx, Inc.; 
//      (b) was not developed with government funds; 
//      (c) is a trade secret of Quovadx, Inc. for all purposes of the 
//          Freedom of Information Act; and 
//      (d) is a commercial item and thus, pursuant to Section 12.212 
//          of the Federal Acquisition Regulations (FAR) and DFAR 
//          Supplement Section 227.7202, Government’s use, duplication or 
//          disclosure of the computer software is subject to the restrictions 
//          set forth by Quovadx, Inc.
//
//
// This source code is only intended as a supplement to
// the Objective Grid Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding
// the Objective Grid product.
//
// Authors: Daniel Jebaraj, Stefan Hoenig
//

// gxttn.h : tooltips implementation


#ifndef _GXTTN_H_
#define _GXTTN_H_

#ifndef _GXABSTR_H_
#include "grid\gxabstr.h"
#endif

//
// GridMFC Extension DLL
// initialize declaration context
//

#ifdef _GXDLL
	#undef AFXAPP_DATA
	#define AFXAPP_DATA AFXAPI_DATA
	#undef AFX_DATA
	#define AFX_DATA    GX_DATAEXT
#endif


/////////////////////////////////////////////////////////////////////////////
// CGXToolTipCtrlProxy
//

class CGXToolTipCtrlProxy: public CGXNoToolTipCtrlProxy
{
public:
	CGXToolTipCtrlProxy(CGXGridCore* pGrid, CWnd* pParent);
	virtual ~CGXToolTipCtrlProxy();

	// Will be called from CGXGridCore::OnGridPreTranslateMessage
	virtual void RelayEvent(LPMSG lpMsg);

	// Will be called from CGXGridCore::PreTranslateMessage
	virtual BOOL OnMouseMove(UINT flags, CPoint pt);

	// Will be called from CGXGridCore::DoSize
	virtual void UpdateTipArea();

	// Reset tips 
	virtual void Reset();

	virtual BOOL InitToolTip();

// Attributes for tooltips
	CGXGridCore* m_pGrid;
	CWnd* m_pParent;
	CButton m_btnTtnHelper;
	ROWCOL  m_nTtnRowtip,
			m_nTtnColtip;
	CString m_strTtnText;
	CToolTipCtrl m_wndTtnToolTip;
};


/////////////////////////////////////////////////////////////////////////////
// Inline function declarations

#ifdef _GX_ENABLE_INLINES

// inlines

#endif

//
// GridMFC extension DLL
// reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

//



#endif //_GXTTN_H_
