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
// ^FILE   : ProgramStarter.cpp
// ^AUTHOR : Ted Koresko
// ^DATE   : 06/20/97
//
// ----------------------------------------------------------
//
// ^CLASS    : ProgramStarter
//
// ^MEMBER VARIABLES :
//   ^^STARTDATA / STARTUPINFO *_pStartData - OS dependent structure that
//     configures the way that the new process will be started.
//   ^^char *_pObjectBuff - OS/2 only data - contains the name of the object
//     that contributed to the failure of the process creation.
//   ^^char *_pszPgmName - OS/2 only data - the name of the .exe to start.
//   ^^char *_pszPgmInputs - OS/2 only data - the parameters for the command
//     line.
//
// ^CODING COMMENTS  :
//
//******************************************************************************
#define DICORE_DLL

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif

#ifndef PROGRAMSTARTER_HPP
   #include "programstarter.hpp"
#endif

#ifndef TRACERCLIENT_HPP
   #include "tracerclient.hpp"
#endif

#ifndef INCLUDED_STRING
#define INCLUDED_STRING
#include <string>
#endif

#ifndef STDINCLUDE_H
   #include "stdinclude.h"
#endif

#ifndef IDISTRING_HPP
   #include "idistring.hpp"
#endif

ProgramStarter::ProgramStarter() HEADER_THROW2(exception, ConditionException)
{
   TRACE_CONSTRUCTOR( I_( "ProgramStarter" ),
                      I_( "ProgramStarter()" ) )

   _pStartData = new STARTUPDATA;

   if( !_pStartData )
      THROWFROMBASE( DICORE_CONDITION,
                     I_( "ProgramStarter::ProgramStarter()" ),
                     BASE_ALLOC_FAIL )

      Create(_pObjectBuff);
   Create(_pszPgmName);
   Create(_pszPgmInputs);
   InitStartData();
}


ProgramStarter::~ProgramStarter() HEADER_THROW1( exception )
{
   TRACE_DESTRUCTOR( I_( "ProgramStarter" ) )
   Destroy();
}


VOID ProgramStarter::Create(PCHAR &pch)
HEADER_THROW2(exception, ConditionException)
{
   MAKEFRAME( DICORE_CONDITION, 
              I_( "Create (PCHAR &pch)" ) )

   if( (pch = new char[CHARBUF_SIZE]) == (PCHAR) NULL )
   {
      Destroy();
      THROWFROMBASE( DICORE_CONDITION, 
                     I_( "Create (PCHAR &pch)" ),
                     BASE_ALLOC_FAIL )
   }
}


VOID ProgramStarter::Destroy (VOID) HEADER_THROW1( exception )
{
   MAKEFRAME( DICORE_CONDITION, 
              I_( "ProgramStarter::Destroy (VOID)" ) )

   if( _pStartData )
   {
      delete _pStartData;
      _pStartData = (PSTARTUPDATA) NULL;
   }

   DeleteBuffer(_pObjectBuff);
   DeleteBuffer(_pszPgmName);
   DeleteBuffer(_pszPgmInputs);
}


VOID ProgramStarter::InitStartData (VOID)
{
   MAKEFRAME( DICORE_CONDITION, 
              I_( "ProgramStarter::InitStartData (VOID)" ) )
   memset( _pStartData, 0, sizeof( STARTUPDATA ) );

#ifdef __OS2__
   _pStartData->Length = sizeof( STARTDATA );
   _pStartData->Related = SSF_RELATED_INDEPENDENT;
   _pStartData->FgBg = SSF_FGBG_BACK;
   _pStartData->TraceOpt = SSF_TRACEOPT_NONE;
   _pStartData->InheritOpt = SSF_INHERTOPT_PARENT;
   _pStartData->SessionType = SSF_TYPE_DEFAULT;
   _pStartData->ObjectBuffer = _pObjectBuff;
   _pStartData->ObjectBuffLen = CHARBUF_SIZE;
#endif
}

#pragma warning( push )
#pragma warning( disable: 4800 )

bool ProgramStarter::start( const DString & strExeLine )
HEADER_THROW1( exception )
{
   MAKEFRAME( DICORE_CONDITION,
              I_( "ProgramStarter::start( const DString & strExeLine )" ) )

   FixCommandLine(strExeLine);

   PROCESS_INFORMATION processInfo;
   APIRET rc = CreateAProcess(strExeLine, &processInfo, _pStartData);

   if( rc != 0 )
   {
      // !!! the hard-coded string is a problem
      DString strErr( I_( "Create A Process error on: " ) );

      strErr.append( strExeLine.c_str() )
      .append( I_( ". ReturnCode: " ) );
      appendULong( strErr, rc);
      I_CHAR * generic = makeErrBuf( I_( "GENERIC" ), strErr );

      ADDCONDITIONFROMFILEIDI( DICORE_PROCESS_CREATE_FAIL, generic );
      delete [] generic;
   }

   return(rc);
}

#pragma warning( pop )

// this function converts the Windows command line
// (a string of arguments separated by blanks) into the traditional
// array of characters it is here only once rather than be duplicated
// in each of the non-Windows source directory
VOID ProgramStarter::FixCommandLine (const DString &strExeLine)
{
   MAKEFRAME( DICORE_CONDITION,
              I_( "ProgramStarter::start( const DString & " )
              I_( "strExeLine )" ) )
#ifndef _WIN32
   DString    strPgmName;
   DString    strPgmInputs;
   int            iStartIndex;
   int            iEndIndex;

   iStartIndex = strExeLine.find_first_not_of(BLANK_STRING);

   iEndIndex = strExeLine.find_first_of(BLANK_STRING, iStartIndex);

   // DTWK check for out of range indexes here.

   strPgmName = strExeLine.substr( iStartIndex, iEndIndex - iStartIndex );

   strcpy( _pszPgmName, strPgmName.c_str() );
   _pStartData->PgmName = _pszPgmName;

   iEndIndex = strExeLine.find_first_not_of(BLANK_STRING, iEndIndex);

   if( iEndIndex >= 0 && iEndIndex < strExeLine.length() )
      strPgmInputs = strExeLine.substr( iEndIndex );
   else
      strPgmInputs = NULL_STRING;

   strcpy( _pszPgmInputs, strPgmInputs.c_str() );
   _pStartData->PgmInputs = _pszPgmInputs;
#endif
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF Core/ifdscore/programstarter.cpp-arc  $
//
//   Rev 1.2   Sep 27 2004 09:40:30   PURDYECH
//Clean up compiler warnings so that there are no complaints about silly things (like truncated debug names...)
// 
//    Rev 1.1   Oct 09 2002 17:42:10   PURDYECH
// New PVCS Database
// 
//    Rev 1.0   Jul 05 2002 10:14:24   SMITHDAV
// Initial revision.
// 
//    Rev 1.5   26 Feb 1999 15:06:08   DT14177
// Integrate DIBASE and DICONFIG into DICORE
// 
//    Rev 1.4   24 Feb 1999 10:44:28   DT14177
// sync up with tracer
// 
//    Rev 1.3   22 Feb 1999 13:57:36   DT14177
// more UNICODE stuff
// 
//    Rev 1.2   18 Feb 1999 10:38:24   DT14177
// UNICODE
// 
//    Rev 1.1   Jan 28 1999 14:03:14   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.0   Dec 09 1998 13:51:30   DMUM
//
//
//    Rev 1.7   Nov 09 1997 15:35:12   DTWK
// Add inclusion guards for faster compiles.
// Add guards so that class is flagged as exported only when compiling
// the output that actually exports the class.
//
//    Rev 1.6   Jul 23 1997 11:48:28   DTWK
// Add tracing
//
//    Rev 1.5   Jul 07 1997 15:16:04   DTWK
// Add more commenting / bug fixes.
//
//    Rev 1.4   Jun 13 1997 13:20:24   DTWK
//
//
//

