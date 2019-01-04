// ResEuropean.h : main header file for the RESEUROPEAN DLL
//

#if !defined(AFX_RESEUROPEAN_H__A3674C7F_116F_40B2_A708_79616F8E5A16__INCLUDED_)
#define AFX_RESEUROPEAN_H__A3674C7F_116F_40B2_A708_79616F8E5A16__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CResEuropeanApp
// See ResEuropean.cpp for the implementation of this class
//

class CResEuropeanApp : public CWinApp
{
public:
	CResEuropeanApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResEuropeanApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CResEuropeanApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESEUROPEAN_H__A3674C7F_116F_40B2_A708_79616F8E5A16__INCLUDED_)
