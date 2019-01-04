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

#ifndef AWDREQUESTFORMATTER_HPP
   #include "awdrequestformatter.hpp"
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

AWDRequestFormatter::AWDRequestFormatter( const DStringA & viewName,
                              const DStringA & operatorId,
                              unsigned long dataLength,
                              const char * data ) :
_viewName( viewName ),
_operatorId( operatorId ),
_dataLength( dataLength ),
_data( data ),
_bufferLength( 0 ),
_buffer( NULL )
{
   padRight( _viewName, LEN_VIEW_NAME, ' ' );
   padRight( _operatorId, LEN_OPERATOR_ID, ' ' );
}

AWDRequestFormatter::~AWDRequestFormatter( )
{
   delete [] _buffer;
}

SEVERITY AWDRequestFormatter::format( )
{
   SEVERITY returnSeverity = NO_CONDITION;

   if ( !_buffer )
   {
      DStringA header( "VIEW" );
      header += _viewName;
      header += _operatorId;
      header += "000";

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

unsigned long AWDRequestFormatter::getBufferLength( void ) const
{
   return( _bufferLength );
}

const char * AWDRequestFormatter::getBuffer( void ) const
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
// $Log:   Y:/VCS/iFastAWD/diview/awdrequestformatter.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:23:48   kovacsro
// Initial revision.
//
//   Rev 1.0   May 18 2001 11:41:38   DT11159
// 
//
//
