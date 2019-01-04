// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__59E3D389_B535_11D2_BB66_00062910E8F2__INCLUDED_)
   #define AFX_STDAFX_H__59E3D389_B535_11D2_BB66_00062910E8F2__INCLUDED_
   
   #define WINVER 0x0501

    #define _USING_V110_SDK71_

   #define BFSESSN_DLL
   #include <srcprag.h>
   #include <commonport.h>

   #include <dstring.hpp>

   #if _MSC_VER > 1000
      #pragma once
   #endif // _MSC_VER > 1000

   #define NOMINMAX 1
   #define VC_EXTRALEAN    // Exclude rarely-used stuff from Windows headers

   #include <afxwin.h>
   #include <afxext.h>
   #include <afxdisp.h>

   #ifndef UNICODE
      #include <sql.h>
      #include <sqlext.h>
   #else
      #include <sqlucode.h>
   #endif

   #ifndef _AFX_NO_AFXCMN_SUPPORT
      #include <afxcmn.h>
   #endif // _AFX_NO_AFXCMN_SUPPORT


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__59E3D389_B535_11D2_BB66_00062910E8F2__INCLUDED_)
