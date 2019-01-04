#pragma once

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#define NOMINMAX
#define _WIN32_WINNT 0x0400

#pragma warning( disable : 4018 4097 4146 4251 4663 4786 )

#include <srcprag.h>
#include <commonport.h>
#include <windows.h>
#include <process.h>
#include <winerror.h>
#include <winsock.h>
#include <iostream>
#include <assert.h>
#include <exception>
#include <dstring.hpp>


