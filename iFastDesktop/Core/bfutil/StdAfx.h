// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if _MSC_VER > 1000
   #pragma once
#endif // _MSC_VER > 1000

#ifndef BFUTIL_DLL
#define BFUTIL_DLL
#endif

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#define NOMINMAX
#define _WIN32_WINNT 0x0400

#pragma warning( disable : 4018 4097 4146 4251 4663 4786 4275 )

#include <windows.h>
#include <process.h>
#include <winerror.h>
#include <winsock.h>
#include <iostream>
#include <assert.h>
#include <exception>
#include <dstring.hpp>

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

#define CLASS_EXPORT _declspec( dllexport )
#define CLASS_IMPORT _declspec( dllimport )

namespace CND
{
   extern CLASS_EXPORT const I_CHAR *BFUTIL_CONDITION;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/bfutil/StdAfx.h-arc  $
//
//   Rev 1.5   Sep 10 2003 10:44:50   PURDYECH
//Added a setting to turn off C4275 warnings
//
//   Rev 1.4   Apr 11 2003 17:53:50   PURDYECH
//Define BFUTIL_DLL if not defined.
//
//   Rev 1.3   Nov 27 2002 15:05:12   PURDYECH
//Documentation Changes
//
//   Rev 1.2   Oct 09 2002 17:41:32   PURDYECH
//New PVCS Database
//
//   Rev 1.1   Aug 29 2002 12:49:42   PURDYECH
//ClientLocale and Field corrections
//
//   Rev 1.0   Jun 26 2001 12:01:06   PURDYECH
//Initial revision.
 * 
 *    Rev 1.2   Feb 16 2000 13:09:48   POPESCUS
 * Initial revision
 * 
 * 
 */