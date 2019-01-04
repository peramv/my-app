// ResCommon.h : main header file for the RESCOMMON DLL
//

#if !defined(AFX_RESCOMMON_H__564124F6_5BE7_11D3_B95E_00C04F572654__INCLUDED_)
   #define AFX_RESCOMMON_H__564124F6_5BE7_11D3_B95E_00C04F572654__INCLUDED_

   #if _MSC_VER > 1000
      #pragma once
   #endif // _MSC_VER > 1000

   #ifndef __AFXWIN_H__
      #error include 'stdafx.h' before including this file for PCH
   #endif

   #include <ifastgui\resource.h>

/////////////////////////////////////////////////////////////////////////////
// CResCommonApp
// See ResCommon.cpp for the implementation of this class
//

class CResCommonApp : public CWinApp
{
public:
   CResCommonApp();

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CResCommonApp)
   //}}AFX_VIRTUAL

   //{{AFX_MSG(CResCommonApp)
   // NOTE - the ClassWizard will add and remove member functions here.
   //    DO NOT EDIT what you see in these blocks of generated code !
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESCOMMON_H__564124F6_5BE7_11D3_B95E_00C04F572654__INCLUDED_)
