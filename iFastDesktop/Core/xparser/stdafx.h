// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#pragma once

#define WIN32_LEAN_AND_MEAN      // Exclude rarely-used stuff from Windows headers

#pragma warning( disable: 4251 )
#pragma warning( disable: 4275 )
#pragma warning( disable: 4786 )

#include <windows.h>
#include <process.h>
#include <winerror.h>
#include <iostream>
#include <assert.h>

#include <commonport.h>
#include <conditionmanager.hpp>

namespace CND
{
   extern const I_CHAR *XPARSER_CONDITION;
}
