#if !defined __GXTTNEX__H__
#define __GXTTNEX__H__
///////////////////////////////////////////////////////////////////////////////
// gxttnex.h
//
//
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
// Authors: Daniel Jebaraj, Stefan Hoenig
// Modified: Boris Meltreger

#ifndef _GXABSTR_H_
#include "grid\gxabstr.h"
#endif

#include <StingrayExportDefs.h>
#include <afxtooltipctrl.h>
#include <afxtoolbarimages.h>

namespace ogex
{

/////////////////////////////////////////////////////////
//class CGXToolTipCtrl 

class CGXToolTipCtrl : public CMFCToolTipCtrl
{
public:
	GRIDEX_API  CGXToolTipCtrl();
	GRIDEX_API  virtual ~CGXToolTipCtrl();
    GRIDEX_API  virtual BOOL OnDrawIcon (CDC* pDC, CRect rectImage);
	GRIDEX_API  virtual CSize GetIconSize ();
	
	int	m_nCurrID;
	BOOL m_bInit;
};

/////////////////////////////////////////////////////////////////////////////
// CGXToolTipCtrlProxy
//

class CGXToolTipCtrlProxyEx: public CGXNoToolTipCtrlProxy
{
public:
	 GRIDEX_API CGXToolTipCtrlProxyEx(CGXGridCore* pGrid, CWnd* pParent);
	 GRIDEX_API virtual ~CGXToolTipCtrlProxyEx();

	// Will be called from CGXGridCore::OnGridPreTranslateMessage
	 GRIDEX_API virtual void RelayEvent(LPMSG lpMsg);

	// Will be called from CGXGridCore::PreTranslateMessage
	 GRIDEX_API virtual BOOL OnMouseMove(UINT flags, CPoint pt);

	// Will be called from CGXGridCore::DoSize
	 GRIDEX_API virtual void UpdateTipArea();

	// Reset tips 
	GRIDEX_API virtual void Reset();

	 GRIDEX_API virtual BOOL InitToolTip();

	// Attributes for tooltips
	CGXGridCore*	m_pGrid;
	CWnd*			m_pParent;
	CButton			m_btnTtnHelper;
	ROWCOL			m_nTtnRowtip,
					m_nTtnColtip;
	CString			m_strTtnText;
	CGXToolTipCtrl	m_wndTtnToolTip;
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

} // namespace ogex

#endif //__GXTTNEX__H__
