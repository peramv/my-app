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
// Author: Ricky Pearson
//
// gxcelltp.h : header file for the CGXCellTipPlugin 
//				class
//

//RWP02a (entire file)

#ifndef _GXCTPLUG_H_
#define _GXCTPLUG_H_

#if _MFC_VER >= 0x0400

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

class CGXCellTipWndManager;
class CGXCellTipWndFactory;

/////////////////////////////////////////////////////////////////////////////
// CGXCellTipPlugin 

class CGXCellTipPlugin : public CGXPluginComponent
{
	DECLARE_DYNAMIC(CGXCellTipPlugin)

public:
	CGXGridCore*			m_pGrid;		// "Parent" grid

protected:
	// Members
	CGXCellTipWndManager*	m_pCellTipWndManager;
	DWORD					m_dwCurrentTipID;
	ROWCOL					m_nCurRow;
	ROWCOL					m_nCurCol;
	SEC_UINT				m_nCellTipTimer;
	BOOL					m_bShowHeaders;
	BOOL					m_bShowActive;
	BOOL					m_bShowActiveCell;
	UINT					m_nDelay;

public:
	// Construction
	CGXCellTipPlugin(CGXGridCore* pGrid, CRuntimeClass* pFactory, 
					 BOOL bShowHeaders, BOOL bShowActive, UINT nDelay);

	// Destruction
	virtual ~CGXCellTipPlugin();

protected:
	// Implementation
	virtual BOOL NeedShowCellTip(CGXControl* pControl);
	virtual DWORD GetCellTipID(CGXControl* pControl);
	virtual void InitializeCellTip(CGXControl* pControl, CGXCellTipWnd* pCellTip);

	// Helper methods
	virtual void ShowCellTip();
	virtual void HideCellTip();
	virtual void StartTimer();
	virtual void StopTimer();
	virtual BOOL IsGridInSpecialMode();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGXCellTipPlugin)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(SEC_UINT nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// CGXCellTipWndManager

class CGXCellTipWndManager : public CGXNodeManager<CGXCellTipWnd>
{
public:
	CGXGridCore*			m_pGrid;
	CGXCellTipWndFactory*	m_pFactory;

public:
	// Construction
	CGXCellTipWndManager(CGXGridCore* pGrid, CRuntimeClass* pRuntimeClass);
	virtual ~CGXCellTipWndManager();

	virtual CGXCellTipWnd* CreateObject(SEC_DWORD dw);
};


/////////////////////////////////////////////////////////////////////////////
// CGXCellTipWndFactory

class CGXCellTipWndFactory : public CObject
{
	DECLARE_DYNCREATE(CGXCellTipWndFactory)

public:
	CGXGridCore* m_pGrid;

	CGXCellTipWndFactory() : CObject() { m_pGrid = NULL; }

	virtual CGXCellTipWnd* CreateCellTipWnd(DWORD dwCellTipID);
};


/////////////////////////////////////////////////////////////////////////////
//
// GridMFC extension DLL
// reset declaration context
//

#undef AFX_DATA
#define AFX_DATA
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR

#endif // _MFC_VER

#endif //_GXCTPLUG_H_
