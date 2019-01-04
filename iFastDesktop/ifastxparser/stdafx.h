// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#pragma once

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

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
#pragma warning( disable : 4018 4097 4146 4251 4663 4786 4275 )

#include <commonport.h>
#include <conditionmanager.hpp>

namespace CND
{
   extern const I_CHAR *IFASTXPARSER_CONDITION;
}
