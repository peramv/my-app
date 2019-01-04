//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : Semaphore.cpp
// ^AUTHOR : Ted Koresko
// ^DATE   : 06/20/97
//
// ----------------------------------------------------------
//
// ^CLASS    : Semaphore
//
// ^MEMBER VARIABLES :
//   ^^unsigned long _ulTimeout - Milliseconds to semaphore timeout. -1 means
//      no timeout.
//   ^^string _strSemName - the name of the semaphore (for named semaphores)
//
// ^CODING COMMENTS  : Abstract base class for semaphore types
//
//******************************************************************************
#define DICORE_DLL

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif
#ifndef SEMAPHORE_HPP
   #include "semaphore.hpp"
#endif
#ifndef STDINCLUDE_H
   #include "stdinclude.h"
#endif
#ifndef SYMBOLS_H
   #include "symbols.h"
#endif

#ifndef IDISTRING_HPP
   #include "idistring.hpp"
#endif


//******************************************************************************
//              Public Methods
//******************************************************************************

Semaphore::Semaphore(unsigned long ulTimeout)
HEADER_THROW1(exception) :
_ulTimeout( ulTimeout ), _strSemName()
{
}

Semaphore::Semaphore(const DString &strSemName,
                     unsigned long ulTimeout,
                     HANDLE hSem)
HEADER_THROW1(exception)
: _ulTimeout( ulTimeout ), _hsem(hSem)
{
   _setName( DStringA( strSemName ).c_str());
}

Semaphore::Semaphore(const I_CHAR * pszName, unsigned long ulTimeout)
HEADER_THROW1(exception)
: _ulTimeout( ulTimeout )
{
   _setName( pszName ? DStringA( DString( pszName ) ).c_str() : ( PCCH ) ""  );
}

void Semaphore::Initialize(bool fCreate)
{
   if( fCreate )
   {
      create();
   }
   else
   {
      open();
   }
}

PCCH Semaphore::GetName(VOID)
{
   return(_strSemName.length() > 0 ? _strSemName.c_str() : (PCCH) NULL);
}

VOID Semaphore::ThrowError(const DString &strFunc,
                           int nError,
                           const DString &strError,
                           DWORD dwResult)
{
   DString   strErr = strError;
   DString   strSemName( _strSemName );
   appendULong(strErr, dwResult);
   strErr += I_( "on " );
   strErr += ( strSemName.length() > 0 ? strSemName.c_str() : I_( "unnamed event") );

   // !!!
   I_CHAR * generic = makeErrBuf( I_( "GENERIC" ), strErr );

   THROWFROMFILEIDI(DICORE_CONDITION, strFunc, nError, generic )
   delete [] generic;
}

unsigned long Semaphore::getTimeout() const HEADER_THROW
{
   return(_ulTimeout);
}

const DStringA & Semaphore::getName() const HEADER_THROW1( exception )
{
   return(_strSemName);
}

void Semaphore::setTimeout( unsigned long ulTimeout ) HEADER_THROW
{
   ulTimeout = _ulTimeout;
}

HANDLE Semaphore::getHandle() const HEADER_THROW
{
   return(_hsem);
}

Semaphore::~Semaphore() HEADER_THROW
{
}

void Semaphore::_setName (PCCH pcchName)
{
   _strSemName = pcchName;

#if defined(__OS2__)
   if( pcchName && pcchName[0] )
      _strSemName = "\\SEM32\\" + _strSemName;
#endif
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   //db3n5j11/d/scc/ifds/core/archives/ifdscore/semaphore.cpp-arc  $
// 
//    Rev 1.1   Oct 09 2002 17:42:14   PURDYECH
// New PVCS Database
// 
//    Rev 1.0   Jul 05 2002 10:14:26   SMITHDAV
// Initial revision.
// 
//    Rev 1.8   01 Mar 1999 15:22:30   DT14177
// fixed stack problem GetName()
// 
//    Rev 1.7   01 Mar 1999 15:06:20   DT14177
// fixed stack problem with GetName()
// 
//    Rev 1.6   26 Feb 1999 15:06:12   DT14177
// Integrate DIBASE and DICONFIG into DICORE
// 
//    Rev 1.5   25 Feb 1999 14:05:18   DT14177
// Changed IDI string substitution macros to end in IDI.
// 
//    Rev 1.4   24 Feb 1999 10:44:32   DT14177
// sync up with tracer
// 
//    Rev 1.3   22 Feb 1999 13:55:36   DT14177
// more UNICODE stuff
// 
//    Rev 1.2   18 Feb 1999 10:38:32   DT14177
// UNICODE
// 
//    Rev 1.1   Jan 28 1999 14:03:22   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.0   Dec 09 1998 13:51:38   DMUM
//
//
//    Rev 1.5   Nov 09 1997 15:35:14   DTWK
// Add inclusion guards for faster compiles.
// Add guards so that class is flagged as exported only when compiling
// the output that actually exports the class.
//
//    Rev 1.4   Jul 07 1997 15:16:06   DTWK
// Add more commenting / bug fixes.
//
//    Rev 1.3   Jun 13 1997 13:20:28   DTWK
//
//
//


