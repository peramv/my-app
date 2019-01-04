// DstcCsiTest.h : main header file for the DSTCCSITEST application
//

#if !defined(AFX_IFASTCSITEST_H__CB030058_137A_11D3_9FB5_00C04F5519AF__INCLUDED_)
#define AFX_IFASTCSITEST_H__CB030058_137A_11D3_9FB5_00C04F5519AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDstcCsiTestApp:
// See DstcCsiTest.cpp for the implementation of this class
//

class CIFastCsiTestApp : public CWinApp
{
public:
	CIFastCsiTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDstcCsiTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDstcCsiTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DSTCCSITEST_H__CB030058_137A_11D3_9FB5_00C04F5519AF__INCLUDED_)
