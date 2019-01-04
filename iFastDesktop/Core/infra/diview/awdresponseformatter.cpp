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

#ifndef AWDRESPONSEFORMATTER_HPP
   #include "awdresponseformatter.hpp"
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

namespace
{
   const I_CHAR *CLASS_NAME = I_( "AwdResponseFormatter" );
}

AwdResponseFormatter::AwdResponseFormatter( const void * response,
                                            const DString & message ) :
_response( ( PVMAPPRESP ) response ),
_message( _vmResp.usRcPrimary ? message : I_( "" ) )
{
   memset( &_vmResp, 0, sizeof( _vmResp ) );
   _vmResp.usRcPrimary = VM_P_ERROR;
   _vmResp.usRcSecondary = VM_S_LOG_MESSAGE;
   _vmResp.usRcView = IDS_SEVERE_ERROR;
}

AwdResponseFormatter::~AwdResponseFormatter( )
{
}

SEVERITY AwdResponseFormatter::parse( )
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
            THROWEXCEPTIONCONDITION( DICORE_CONDITION,
                                     I_( "AwdResponseFormatter::parse" ),
                                     DICORE_VMAPPREQUEST_TIMEOUT,
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

unsigned long AwdResponseFormatter::getFixedLenBufSize( void ) const
{
   return( _vmResp.usFixedLen );
}

unsigned short AwdResponseFormatter::getViewReturnCode( void ) const
{
   return( _vmResp.usRcView );
}

unsigned short AwdResponseFormatter::getRcPrimary( void ) const
{
   return( _vmResp.usRcPrimary );
}

unsigned short AwdResponseFormatter::getRcSecondary( void ) const
{
   return( _vmResp.usRcSecondary );
}

unsigned long AwdResponseFormatter::getVarLenBufSize( void ) const
{
   unsigned long ulVarBufLen;

   ulVarBufLen = _vmResp.usNumRepeat * _vmResp.usRepeatLen;

   return( ulVarBufLen );
}

bool AwdResponseFormatter::getFixedData( unsigned char *pBuf, unsigned long ulBufSize ) const
{
   TRACE_METHOD( I_("AwdResponseFormatter"),
                 I_("getFixedData( unsigned char *, unsigned long )") )
   if ( !_response || !_vmResp.usFixedLen || !pBuf || !ulBufSize )
   {
      return( false );
   }

   unsigned long ulCopySize;

   if ( ulBufSize < _vmResp.usFixedLen )
   {
      ulCopySize = ulBufSize;
   } else
   {
      ulCopySize = _vmResp.usFixedLen;
   }

   memcpy( pBuf, _vmResp.pvFixed, ulCopySize );

   return( true );
}

bool AwdResponseFormatter::getVarData( unsigned char *pBuf, unsigned long ulBufSize ) const
{
   TRACE_METHOD( I_("AwdResponseFormatter"),
                 I_("getVarData( unsigned char *, unsigned long )") )
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
   } else
   {
      ulCopySize = ulSourceSize;
   }

   memcpy( pBuf, _vmResp.pvRepeat, ulCopySize );

   return( true );
}

bool AwdResponseFormatter::getRepeatRecord( unsigned long ulRecordNumber,
                                      char *pBuf,
                                      unsigned long ulBufSize ) const
{
   TRACE_METHOD( I_("AwdResponseFormatter"),
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
   char *pRepeatRecord;

   ulBufferOffset = ( ulRecordNumber - 1 ) * _vmResp.usRepeatLen;

   if ( ulBufSize < _vmResp.usRepeatLen )
   {
      ulCopySize = ulBufSize;
   } else
   {
      ulCopySize = _vmResp.usRepeatLen;
   }

   pRepeatRecord = ( char * ) _vmResp.pvRepeat + ulBufferOffset;

   memcpy( pBuf, pRepeatRecord, ulCopySize );

   return( true );
}

unsigned long AwdResponseFormatter::getRepeatRecSize( void ) const
{
   return( _vmResp.usRepeatLen );
}

unsigned long AwdResponseFormatter::getNumRepeatRec( void ) const
{
   return( _vmResp.usNumRepeat );
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
// $Log:   Y:/VCS/iFastAWD/diview/awdresponseformatter.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:23:50   kovacsro
// Initial revision.
//
//   Rev 1.2   Jun 26 2001 12:55:42   DT11159
//Added some new conditions.
//Changed to use idistring functions.
//
//   Rev 1.1   Jun 08 2001 19:12:30   DT11159
//Added View Manager error information in conditions.
//
//   Rev 1.0   May 18 2001 11:41:44   DT11159
//
//
//
