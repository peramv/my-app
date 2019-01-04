// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__F2E4E1A6_5BB8_11D3_B95E_00C04F572654__INCLUDED_)
   #define AFX_STDAFX_H__F2E4E1A6_5BB8_11D3_B95E_00C04F572654__INCLUDED_

   #if _MSC_VER > 1000
      #pragma once
   #endif // _MSC_VER > 1000
   
   #define WINVER 0x0501

   #define VC_EXTRALEAN    // Exclude rarely-used stuff from Windows headers

   #include <afxwin.h>
   #include <afxext.h>

   #ifndef _AFX_NO_OLE_SUPPORT
      #include <afxole.h>
      #include <afxodlgs.h>
      #include <afxdisp.h>
   #endif // _AFX_NO_OLE_SUPPORT


   #ifndef _AFX_NO_DB_SUPPORT
      #include <afxdb.h>
   #endif // _AFX_NO_DB_SUPPORT

   #ifndef _AFX_NO_DAO_SUPPORT
      #include <afxdao.h>
   #endif // _AFX_NO_DAO_SUPPORT

   #include <afxdtctl.h>
   #ifndef _AFX_NO_AFXCMN_SUPPORT
      #include <afxcmn.h>
   #endif // _AFX_NO_AFXCMN_SUPPORT


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__F2E4E1A6_5BB8_11D3_B95E_00C04F572654__INCLUDED_)
