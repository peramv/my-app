// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//
#pragma once

#define WIN32_LEAN_AND_MEAN      // Exclude rarely-used stuff from Windows headers

#include <windows.h>
#include <process.h>
#include <winerror.h>
#include <winsock.h>
#include <iostream>
#include <assert.h>


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
#pragma warning( disable : 4018 4097 4146 4251 4275 4663 4786 )

#include <commonport.h>
#include <conditionmanager.hpp>

namespace CND
{
   extern const I_CHAR *SRVBASE_CONDITION;
}

static DString empty;

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/srvbase/StdAfx.h-arc  $
 * 
 *    Rev 1.6   Sep 27 2004 09:40:22   PURDYECH
 * Clean up compiler warnings so that there are no complaints about silly things (like truncated debug names...)
 * 
 *    Rev 1.5   Feb 11 2003 10:43:44   PURDYECH
 * Always use #pragma once as an include guard
 * 
 *    Rev 1.4   Jan 21 2003 18:41:46   PURDYECH
 * Cosmetic Changes
 * 
 *    Rev 1.3   Oct 09 2002 17:42:30   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.2   Apr 04 2000 10:22:42   POPESCUS
 * fixes for the server sync-up
 * 
 *    Rev 1.1   Feb 16 2000 13:03:44   POPESCUS
 * Initial revision
 * 
 * 
 */