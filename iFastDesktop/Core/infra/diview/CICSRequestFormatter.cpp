/*
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1996-2001 by DST Systems, Inc.
 */

/**
 *   Author:  David Sample
 *
 *   Class:   CICSRequestFormatter.cpp
 *
 *   Class Description
 *
 */
#define DIVIEW_DLL

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif

#ifndef INCLUDED_STDIO_H
   #define INCLUDED_STDIO_H
   #include <stdio.h>
#endif
#ifndef INCLUDED_STRING
   #define INCLUDED_STRING
   #include <string>
#endif

#ifndef INCLUDED_SSTREAM
   #define INCLUDED_SSTREAM
   #include <sstream>
#endif

#ifndef CICSREQUESTFORMATTER_HPP
   #include "cicsrequestformatter.hpp"
#endif
#ifndef STRINGFUNCTIONS_HPP
   #include "stringfunctions.hpp"
#endif

#ifndef CONDITIONMANAGER_HPP
   #include "conditionmanager.hpp"
#endif
#ifndef DICORE_H
   #include "dicore.h"
#endif
#ifndef BASE_H
   #include "base.h"
#endif

#ifndef CONFIGMANAGER_HPP
   #include "configmanager.hpp"
#endif

#ifdef _WIN32
   #ifndef INCLUDED_WINDOWS_H
      #define INCLUDED_WINDOWS_H
      #include <windows.h>
   #endif
#endif

#ifndef COMMONPORT_H
   #include "commonport.h"
#endif

CICSRequestFormatter::CICSRequestFormatter( const DStringA & viewName,
                              const DStringA & operatorId,
                              const DStringA & system,
                              unsigned long dataLength,
                              const char * data ) :
_viewName( viewName ),
_operatorId( operatorId ),
_system( system ),
_dataLength( dataLength ),
_data( data ),
_bufferLength( 0 ),
_buffer( NULL )
{
   padRight( _viewName, LEN_VIEW_NAME, ' ' );
   padRight( _operatorId, LEN_OPERATOR_ID, ' ' );
   padRight( _system, LEN_SYSTEM, ' ' );
}

CICSRequestFormatter::~CICSRequestFormatter( )
{
   delete [] _buffer;
}

SEVERITY CICSRequestFormatter::format( )
{
   SEVERITY returnSeverity = NO_CONDITION;

   if ( !_buffer )
   {
      DStringA header( "VIEW" );
      header += _viewName;
      header += _operatorId;
      header += "000";
      if ( _viewName.substr( 0, 5 ) != "SIGNO" )
      {
         header += _system;
      }

      upperCase( header );

      unsigned long headerLength = header.length();
      _bufferLength = headerLength + _dataLength;
      _buffer = new char[ _bufferLength ];
      memcpy( _buffer, header.c_str(), headerLength );
      if ( _dataLength > 0 )
      {
         memcpy( _buffer + headerLength, _data, _dataLength );
      }
   }

   return( returnSeverity );
}

unsigned long CICSRequestFormatter::getBufferLength( void ) const
{
   return( _bufferLength );
}

const char * CICSRequestFormatter::getBuffer( void ) const
{
   return( _buffer );
}

//************************************************************************
//              Revision Control Entries
//************************************************************************
//
// Name:
//    %PM%
//    %PID%
//
// Description:
//    %PD%
//
// Design Parts:
//    %PIRP%
//
// Last Changed:
//    %PO%  -  %PRT%
//
// Changes:
//    %PLA%
//
//
// $Log:   Y:/VCS/iFastAWD/diview/CICSRequestFormatter.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:23:52   kovacsro
// Initial revision.
//
//   Rev 1.0   May 18 2001 11:40:04   DT11159
// 
//
//
