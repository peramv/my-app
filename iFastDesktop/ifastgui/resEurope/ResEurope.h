// ResEurope.h : main header file for the RESEUROPE DLL
//

#if !defined(AFX_RESEUROPE_H__BD679B13_AEF9_4093_9FF0_13B4613C9CF0__INCLUDED_)
   #define AFX_RESEUROPE_H__BD679B13_AEF9_4093_9FF0_13B4613C9CF0__INCLUDED_

   #if _MSC_VER > 1000
      #pragma once
   #endif // _MSC_VER > 1000

   #ifndef __AFXWIN_H__
      #error include 'stdafx.h' before including this file for PCH
   #endif

   #include <ifastgui\resource.h>

/////////////////////////////////////////////////////////////////////////////
// CResEuropeApp
// See ResEurope.cpp for the implementation of this class
//

class CResEuropeApp : public CWinApp
{
public:
   CResEuropeApp();

// Overrides
   // ClassWizard generated virtual function overrides
   //{{AFX_VIRTUAL(CResEuropeApp)
   //}}AFX_VIRTUAL

   //{{AFX_MSG(CResEuropeApp)
   // NOTE - the ClassWizard will add and remove member functions here.
   //    DO NOT EDIT what you see in these blocks of generated code !
   //}}AFX_MSG
   DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESEUROPE_H__BD679B13_AEF9_4093_9FF0_13B4613C9CF0__INCLUDED_)
