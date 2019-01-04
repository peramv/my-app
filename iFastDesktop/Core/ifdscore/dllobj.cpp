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
//    Copyright 1997-1998 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : dllobj.cpp
// ^AUTHOR : Larry Parnes
// ^DATE   :
//
// ----------------------------------------------------------
//
// ^CLASS : DebugMgr
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#define DICORE_DLL

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif

#ifndef DLLOBJ_HPP
   #include "dllobj.hpp"
#endif

#ifndef STDINCLUDE_H
   #include "stdinclude.h"
#endif

#ifndef IDISTRING_HPP
   #include "idistring.hpp"
#endif


static VOID ThrowError(const DString &strFunc,
                       int nError,
                       const DString &strError,
                       DWORD dwResult)
{
   DString   strErr = strError;
   appendULong(strErr, dwResult);
   I_CHAR * generic = makeErrBuf( I_( "GENERIC" ), strErr );


   THROWFROMFILEIDI( DICORE_CONDITION, strFunc.c_str(), nError, generic )
   delete [] generic;
}


DllObj::DllObj( const DString & strModule )
HEADER_THROW2( ConditionException, exception ) :
_strModule( strModule )
{
   TRACE_CONSTRUCTOR( I_( "DllObj" ), 
                      I_( "DllObj( const DStringA& strModule )" ) )
   ULONG          ulBytes = 310;
   char           szName[ 310 ];
   unsigned long  ulRc = LoadALibrary( szName, ulBytes, strModule, &_hmod );

   if( ulRc != 0 )
   {
      ThrowError( I_( "DllObj::DllObj( const DStringA& strModule )" ),
                  DICORE_DLL_LOAD_FAIL,
                  I_( "Error Loading Library " ),
                  ulRc);
   }
}


DllObj::DllObj( const DllObj& orig ) HEADER_THROW1( exception )
{
   TRACE_CONSTRUCTOR( I_( "DllObj" ), I_( "DllObj( const DllObj& orig )" ) )
   _strModule = orig._strModule;
   _hmod = orig._hmod;
}


DllObj::~DllObj() HEADER_THROW1( exception )
{
   TRACE_DESTRUCTOR( I_( "DllObj" ) )
   FreeALibrary( _hmod );
}


void * DllObj::findFunction( const DString & strFunc )
HEADER_THROW2( ConditionException, exception )
{
   TRACE_METHOD( I_( "* DllObj" ), 
                 I_( "findFunction( const DStringA& strFunc )" ) )
   FARPROC pfn;
   unsigned long ulRc = FindAFunction(_hmod, strFunc, &pfn );

   if( !pfn )
   {
      DString strErr( I_( "Error loading function " ) );

      strErr += strFunc.c_str();
      strErr += I_( " from module " );
      strErr += _strModule.c_str();
      strErr += I_( ". Return code " );

      ThrowError( I_( "DllObj::findFunction( const DStringA& strFunc )" ),
                  DICORE_FUNCTION_LOAD_FAIL,
                  strErr,
                  ulRc);
   }

   return( void * )pfn;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   //db3n5j11/d/scc/ifds/core/archives/ifdscore/dllobj.cpp-arc  $
// 
//    Rev 1.1   Oct 09 2002 17:41:58   PURDYECH
// New PVCS Database
// 
//    Rev 1.0   Jul 05 2002 10:14:06   SMITHDAV
// Initial revision.
// 
//    Rev 1.5   26 Feb 1999 15:05:54   DT14177
// Integrate DIBASE and DICONFIG into DICORE
// 
//    Rev 1.4   25 Feb 1999 14:05:08   DT14177
// Changed IDI string substitution macros to end in IDI.
// 
//    Rev 1.3   24 Feb 1999 10:44:10   DT14177
// sync up with tracer
// 
//    Rev 1.2   18 Feb 1999 10:38:08   DT14177
// UNICODE
// 
//    Rev 1.1   Jan 28 1999 14:02:52   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.0   Dec 09 1998 13:51:12   DMUM
//
//
//    Rev 1.9   Nov 09 1997 15:35:04   DTWK
// Add inclusion guards for faster compiles.
// Add guards so that class is flagged as exported only when compiling
// the output that actually exports the class.
//
//    Rev 1.8   Jul 23 1997 11:48:02   DTWK
// Add tracing
//
//    Rev 1.7   Jul 07 1997 15:15:56   DTWK
// Add more commenting / bug fixes.
//
//    Rev 1.6   Jun 13 1997 13:20:06   DTWK
//
//
//

