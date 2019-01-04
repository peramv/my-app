
// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#define NOMINMAX 1      // This resolves the inconsistency between RW and MFC
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

// Road runner additions
// Disable warning C4018: xxxx : signed/unsigned mismatch to clean up warnings 
//  that the standard template library generates.
// Disable warning C4005 - macro redefinition
// Disable warning C4097 - typedef-name 'x' used as synonym for class-name 'b'...
// Disable warning C4146 - unary minus operator applied to unsigned type...
// Disable warning C4251 - needs to have dll-interface to be used by clients of...
// Disable warning C4663 - C++ language change: to explicitly specialize class
//  template 'x' use...
// Disable warning C4786 - identifier was truncated to '255' characters in the
//  debug information
// These should be cleared periodically to check that our code is not generating
//  these warnings
#pragma warning( disable : 4005 4018 4097 4146 4251 4663 4786 4275 )
#define WINVER 0x0501
#include <CommonPort.h>

#include <afxwin.h>
#include <afxext.h>
#ifndef _AFX_NO_AFXCMN_SUPPORT
   #include <afxcmn.h>
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxdisp.h>

namespace CND
{
   extern const I_CHAR *IFASTGUI_CONDITION;  // Used for component name
}


//#include <uibase\win32uibase_global.hpp>
#include "ifastgui_global.hpp"

//#include <gxall.h>

