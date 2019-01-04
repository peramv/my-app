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
 *   Class:   CICSResponseFormatter.cpp
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

#ifndef CICSRESPONSEFORMATTER_HPP
   #include "cicsresponseformatter.hpp"
#endif
#ifndef STRINGFUNCTIONS_HPP
   #include "stringfunctions.hpp"
#endif

#ifndef IDISTRING_HPP
   #include "idistring.hpp"
#endif
#ifndef CONDITIONMANAGER_HPP
   #include "conditionmanager.hpp"
#endif
#ifndef DICORE_H
   #include "dicore.h"
#endif
#ifndef DIVIEW_H
   #include "diview.h"
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

#ifndef DITA2KDB_H
   #include "dita2kdb.h"
#endif

namespace
{
   const I_CHAR *CLASS_NAME = I_( "CICSResponseFormatter" );
}

CICSResponseFormatter::CICSResponseFormatter( const void * response,
                                              const DString & message ) :
_response( ( PVMAPPRESP ) response ),
_message( _vmResp.usRcPrimary ? message : I_( "" ) )
{
   memset( &_vmResp, 0, sizeof( _vmResp ) );
   _vmResp.usRcPrimary = VM_P_ERROR;
   _vmResp.usRcSecondary = VM_S_LOG_MESSAGE;
   _vmResp.usRcView = IDS_SEVERE_ERROR;
}

CICSResponseFormatter::~CICSResponseFormatter( )
{
}

SEVERITY CICSResponseFormatter::parse( )
{
   MAKEFRAMER( DIVIEW_CONDITION, CLASS_NAME, I_( "parse" ) );

   SEVERITY returnSeverity;

   VmExtractResp( ( unsigned char * ) _response, &_vmResp );

   if ( VM_P_OK == _vmResp.usRcPrimary )
   {
      returnSeverity = NO_CONDITION;
   }
   else
   {
      if ( VM_P_ERROR == _vmResp.usRcPrimary )
      {
         if ( VM_S_TIMEOUT == _vmResp.usRcSecondary )
         {
            throw EXCEPTIONCONDITION( DICORE_VMAPPREQUEST_TIMEOUT,
                                      NULL_STRING, NULL );
         }
      }

      DString msg;
      addIDITagValue( msg, I_( "Primary" ), _vmResp.usRcPrimary );
      addIDITagValue( msg, I_( "Secondary" ), _vmResp.usRcSecondary );
      addIDITagValue( msg, I_( "Message" ), _message );
      addIDITagValue( msg, I_( "View" ), DStringA( _vmResp.szViewName ) );
      addIDITagValue( msg, I_( "Host" ), DStringA( _vmResp.szHost ) );
      addIDITagValue( msg, I_( "Connection" ), DStringA( _vmResp.szIdent ) );

      if ( VM_P_WARNING == _vmResp.usRcPrimary )
      {
         ADDCONDITION( ERR_APP_REQUEST_FAIL, msg, NULL );
      }
      else
      {
         throw EXCEPTIONCONDITION( ERR_APP_REQUEST_FAIL, msg, NULL );
      }

      returnSeverity = CRITICAL_ERROR;
   }

   return( returnSeverity );
}

unsigned long CICSResponseFormatter::getFixedLenBufSize( void ) const
{
   return( _vmResp.usFixedLen );
}

unsigned short CICSResponseFormatter::getRcPrimary( void ) const
{
   return( _vmResp.usRcPrimary );
}

unsigned short CICSResponseFormatter::getRcSecondary( void ) const
{
   return( _vmResp.usRcSecondary );
}

unsigned long CICSResponseFormatter::getVarLenBufSize( void ) const
{
   unsigned long ulVarBufLen;

   ulVarBufLen = _vmResp.usNumRepeat * _vmResp.usRepeatLen;

   return( ulVarBufLen );
}

bool CICSResponseFormatter::getFixedData( char * pBuf, unsigned long ulBufSize ) const
{
   TRACE_METHOD( I_("CICSResponseFormatter"),
                 I_("getFixedData( char *, unsigned long )") )
   if ( !_response || !_vmResp.usFixedLen || !pBuf || !ulBufSize )
   {
      return( false );
   }

   unsigned long ulCopySize;

   if ( ulBufSize < _vmResp.usFixedLen )
   {
      ulCopySize = ulBufSize;
   }
   else
   {
      ulCopySize = _vmResp.usFixedLen;
   }

   memcpy( pBuf, _vmResp.pvFixed, ulCopySize );

   return( true );
}

bool CICSResponseFormatter::getVarData( char * pBuf, unsigned long ulBufSize ) const
{
   TRACE_METHOD( I_("CICSResponseFormatter"),
                 I_("getVarData( char *, unsigned long )") )
   if ( !_response )
   {
      return( false );
   }

   unsigned long ulCopySize;
   unsigned long ulSourceSize;

   ulSourceSize = this->getVarLenBufSize( );

   if ( ulBufSize < ulSourceSize )
   {
      ulCopySize = ulBufSize;
   }
   else
   {
      ulCopySize = ulSourceSize;
   }

   memcpy( pBuf, _vmResp.pvRepeat, ulCopySize );

   return( true );
}

bool CICSResponseFormatter::getRepeatRecord( unsigned long ulRecordNumber,
                                      char * pBuf,
                                      unsigned long ulBufSize ) const
{
   TRACE_METHOD( I_("CICSResponseFormatter"),
                 I_("getRepeatRecord( unsigned long, char *, unsigned long )") )
   if ( !_response )
   {
      return( false );
   }

   if ( ulRecordNumber <= 0 ||
        ulRecordNumber > _vmResp.usNumRepeat )
   {
      return( false );      // Error, record number doesn't exist
   }

   unsigned long ulBufferOffset;
   unsigned long ulCopySize;
   char * pRepeatRecord;

   ulBufferOffset = ( ulRecordNumber - 1 ) * _vmResp.usRepeatLen;

   if ( ulBufSize < _vmResp.usRepeatLen )
   {
      ulCopySize = ulBufSize;
   }
   else
   {
      ulCopySize = _vmResp.usRepeatLen;
   }

   pRepeatRecord = ( char * ) _vmResp.pvRepeat + ulBufferOffset;

   memcpy( pBuf, pRepeatRecord, ulCopySize );

   return( true );
}

unsigned long CICSResponseFormatter::getRepeatRecSize( void ) const
{
   return( _vmResp.usRepeatLen );
}

unsigned long CICSResponseFormatter::getNumRepeatRec( void ) const
{
   return( _vmResp.usNumRepeat );
}

unsigned short CICSResponseFormatter::getViewReturnCode( void ) const
{
   return( _vmResp.usRcView );
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
// $Log:   Y:/VCS/iFastAWD/diview/CICSResponseFormatter.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:23:54   kovacsro
// Initial revision.
//
//   Rev 1.2   Jun 26 2001 12:55:26   DT11159
//Added some new conditions.
//Changed to use idistring functions.
//
//   Rev 1.1   Jun 08 2001 19:09:20   DT11159
//Added View Manager error information in conditions.
//
//   Rev 1.0   May 18 2001 11:40:10   DT11159
//
//
//
