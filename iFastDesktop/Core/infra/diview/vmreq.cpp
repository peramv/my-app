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
//    Copyright 1996 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : VMReq.cpp
// ^AUTHOR : Paul Dardeau
// ^DATE   : 12/10/96
//
// ----------------------------------------------------------
//
// ^CLASS : VMRequest
//
// ^MEMBER VARIABLES :
//    ^TYPE :        bool
//    ^NAME :        _fConnected
//    ^DESCRIPTION : Flag indicating whether the object has a connection
//                   to View Manager.
//
//    ^TYPE :        string
//    ^NAME :        _sAppName
//    ^DESCRIPTION : System generated unique identifier used to identify
//                   itself to View Manager.
//
//    ^TYPE :        EventSemaphore *
//    ^NAME :        _pEventSemaphore
//    ^DESCRIPTION : Pointer to dynamically allocated EventSemaphore object.
//                   The event semaphore is used for View Manager to notify
//                   our object when transmission with a host is complete.
//
//    ^TYPE :        char[]
//    ^NAME :        _szErrMsg
//    ^DESCRIPTION : Buffer to hold contents of View Manager error strings.
//
//    ^TYPE :        string
//    ^NAME :        _sSemName
//    ^DESCRIPTION : String containing the name of the event semaphore
//
//    ^TYPE :        BYTE *
//    ^NAME :        _pbBuff
//    ^DESCRIPTION : Pointer to view return data buffer.
//
//    ^TYPE :        VMDSTRESP
//    ^NAME :        _vmResp
//    ^DESCRIPTION : Holds standard DST view header information.
//
//
// ^CODING COMMENTS  :  This code currently only supports single-threaded,
//                      synchronous access to View Manager.
//
//******************************************************************************
#define DIVIEW_DLL

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif

#ifndef COMMONPORT_H
   #include "commonport.h"
#endif

#ifndef VMREQ_HPP
   #include "vmreq.hpp"
#endif

#ifndef BASE_H
   #include "base.h"
#endif

#ifndef CONDITIONMANAGER_HPP
   #include "conditionmanager.hpp"
#endif

#ifndef CONFIGMANAGER_HPP
   #include "configmanager.hpp"
#endif

#ifndef CRITICALSECTION_HPP
   #include "CriticalSection.hpp"
#endif

#ifndef DICORE_H
   #include "dicore.h"
#endif

#ifndef EVENTSEMAPHORE_HPP
   #include "eventsemaphore.hpp"
#endif

#ifndef MUTEXSEMAPHORE_HPP
   #include "mutexsemaphore.hpp"
#endif

#ifndef STRINGFUNCTIONS_HPP
   #include "stringfunctions.hpp"
#endif

#ifdef _WIN32
   #ifndef INCLUDED_WINDOWS_H
   #define INCLUDED_WINDOWS_H
      #include <windows.h>
   #endif
#endif

// REVISION: DTXH

#include <time.h>
#include <sys/timeb.h>
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

#ifndef VMV002REQUEST_HPP
   #include "VMV002Request.hpp"
#endif
#ifndef VMV002RESPONSE_HPP
   #include "VMV002Response.hpp"
#endif

#include <iostream>

#include <process.h>

MutexSemaphore TimerMutex;

static MutexSemaphore mutexAppName;
unsigned short usAppNameCounter = 0;


void CLASS_EXPORT getUniqueMillisecondTime( char * argTime )
{
   struct _timeb timebuffer;
   struct _timeb testbuffer;
   char *timeline;

   TimerMutex.wait();
   _ftime( &timebuffer );
   timeline = ctime( & ( timebuffer.time ) );

   sprintf( argTime, "%.8s.%hu", &( timeline[11] ), timebuffer.millitm );

// wait for the next millisecond

   int i = 0;
   do
   {
       ++i;
       _ftime( &testbuffer );
   } while ( testbuffer.millitm == timebuffer.millitm );

   TimerMutex.post();
}

// END REVISION: DTXH


VMRequest::VMRequest( unsigned long ulTimeout,
                      pfnSendPreprocess fnSendPreprocess,
                      pfnExtractOverride fnExtractOverride ) :
   _fConnected( false ),
   _pEventSemaphore( NULL ),
   _pbBuff( NULL ),
   _fnSendPreprocess( fnSendPreprocess ),
   _fnExtractOverride( fnExtractOverride ),
   _pVmAppResp( NULL ),
   _fUsingHWND( false )
{
   MAKEFRAME( DICORE_CONDITION, I_( "VMRequest::VMRequest" ) );

   _initVMRequest( ulTimeout );
}


VMRequest::VMRequest( pfnSendPreprocess fnSendPreprocess,
                      pfnExtractOverride fnExtractOverride ) :
   _fConnected( false ),
   _pEventSemaphore( NULL ),
   _pbBuff( NULL ),
   _fnSendPreprocess( fnSendPreprocess ),
   _fnExtractOverride( fnExtractOverride ),
   _pVmAppResp( NULL ),
   _fUsingHWND( false )
{
   MAKEFRAME( DICORE_CONDITION, I_( "VMRequest::VMRequest" ) );

   // Check the registry for a timeout.  If there's not one, use the default
   // of 30 seconds.

   DString strTimeout = I_( "" );
   try
   {
      strTimeout = GetConfigValueAsString( I_("VmRequest"), I_("Timeout"),
                                                       I_("Seconds") );
   }
   catch (...) // This exception is not a problem
   {
      char * junk = NULL;
   }

   if ( strTimeout.length() )
   {
      _initVMRequest( convertToULong( strTimeout ) );
   }
   else
   {
      _initVMRequest( DEFAULT_TIMEOUT );
   }
}


VMRequest::VMRequest( DSTWINDOWHANDLE hwndResponse,
                      unsigned long ulMsg ) :
   _fConnected( false ),
   _pEventSemaphore( NULL ),
   _pbBuff( NULL ),
   _fnSendPreprocess( 0 ),
   _fnExtractOverride( 0 ),
   _pVmAppResp( NULL ),
   _fUsingHWND( true ),
   _hwndResponse( hwndResponse ),
   _ulMsg( ulMsg )
{
   MAKEFRAME( DICORE_CONDITION, I_( "VMRequest::VMRequest" ) );

   _initVMRequest( DEFAULT_TIMEOUT );
}


VMRequest::~VMRequest()
{
   TRACE_DESTRUCTOR( I_("VMRequest") )
   if ( _fConnected )
   {
      // Disconnect from View Manager
      try
      {
         _vmDisconnect();
      }
      catch( ... )
      {
      }
   }

   if ( _pEventSemaphore )
   {
      delete _pEventSemaphore;
   }

   if ( _pbBuff )
   {
      // If we're doing V002 headers, then _pbBuff was replaced with
      // a converted buffer that we allocated, not AWD / View
      if ( m_dstrV002.length() > 0 )
      {
         delete [] _pbBuff;
      }
      else
      {
         VmFree( _pbBuff );
      }
      _pbBuff = NULL;
   }
}


bool VMRequest::send( const DStringA& sViewName, const DStringA& sViewRequest,
                      const DString &dstrV002Pass,
                      const DString &dstrV002NewPass )
{
   TRACE_METHOD( I_("VMRequest"),
                 I_("send( const DString&, const DString& )") )

   return _send( NULL_STRING, sViewName, sViewRequest, dstrV002Pass,
                 dstrV002NewPass );
}


bool VMRequest::send( const DStringA& sViewName, const char *sViewRequest,
                      const DString &dstrV002Pass,
                      const DString &dstrV002NewPass )
{
   TRACE_METHOD( I_("VMRequest"),
                 I_("send( const DString&, const DString& )") )

   return _send( NULL_STRING, sViewName, sViewRequest, dstrV002Pass,
                 dstrV002NewPass );
}


bool VMRequest::sendToHost( const DStringA& sHostName,
                            const DStringA& sViewRequest,
                            const DString &dstrV002Pass,
                            const DString &dstrV002NewPass )
{
   TRACE_METHOD( I_("VMRequest"),
                 I_("sendToHost( const DString&, const DString& )") )

   return _send( sHostName, NULL_STRING, sViewRequest, dstrV002Pass,
                 dstrV002NewPass );
}


bool VMRequest::sendToHost( const DStringA& sHostName,
                            const char *sViewRequest,
                            const DString &dstrV002Pass,
                            const DString &dstrV002NewPass )
{
   TRACE_METHOD( I_("VMRequest"),
                 I_("sendToHost( const DString&, const DString& )") )

   return _send( sHostName, "", sViewRequest, dstrV002Pass, dstrV002NewPass );
}


bool VMRequest::sendViewToHost( const DStringA &sHostName,
                                const DStringA &sViewName,
                                const DStringA &sViewRequest,
                                const DString &dstrV002Pass,
                                const DString &dstrV002NewPass )
{
   TRACE_METHOD( I_("VMRequest"),
                 I_("sendViewToHost( const string&, const string& , ")
                 I_("const string& )") )

   return _send( sHostName, sViewName, sViewRequest, dstrV002Pass,
                 dstrV002NewPass );
}


bool VMRequest::sendViewToHost( const DStringA &sHostName,
                                const DStringA &sViewName,
                                const char *sViewRequest,
                                const DString &dstrV002Pass,
                                const DString &dstrV002NewPass )
{
   TRACE_METHOD( I_("VMRequest"),
                 I_("sendViewToHost( const string&, const string& , ")
                 I_("const string& )") )

   return _send( sHostName, sViewName, sViewRequest, dstrV002Pass,
                 dstrV002NewPass );
}


bool VMRequest::sendViewToHost( const DStringA &sHostName,
                                const DStringA &sViewName,
                                const unsigned char *uchViewRequest,
                                unsigned long viewRequestLength,
                                const DString &dstrV002Pass,
                                const DString &dstrV002NewPass )
{
   TRACE_METHOD( I_("VMRequest"),
                 I_("sendViewToHost( const string& , const string& , ")
                 I_("const string& )") )

   return _send( sHostName, sViewName, uchViewRequest, viewRequestLength,
                 dstrV002Pass, dstrV002NewPass );
}


unsigned long VMRequest::getFixedLenBufSize( void ) const
{
   return _vmResp.usFixedLen;
}


unsigned short VMRequest::getViewReturnCode( void ) const
{
   return _vmResp.usRcView;
}


unsigned short VMRequest::getRcPrimary( void ) const
{
   return _vmResp.usRcPrimary;
}


unsigned short VMRequest::getRcSecondary( void ) const
{
   return _vmResp.usRcSecondary;
}


unsigned long VMRequest::getVarLenBufSize( void ) const
{
   unsigned long ulVarBufLen;

   ulVarBufLen = _vmResp.usNumRepeat * _vmResp.usRepeatLen;
   return ulVarBufLen;
}


bool VMRequest::getFixedData( unsigned char *pBuf, unsigned long ulBufSize ) const
{
   TRACE_METHOD( I_("VMRequest"),
                 I_("getFixedData( char *pBuf, unsigned long ulBufSize )") )
   if ( !_pbBuff || !_vmResp.usFixedLen || !pBuf || !ulBufSize )
   {
      return false;
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
   return true;
}



bool VMRequest::getVarData( unsigned char *pBuf, unsigned long ulBufSize ) const
{
   TRACE_METHOD( I_("VMRequest"),
                 I_("getVarData( char *pBuf, unsigned long ulBufSize )") )
   if ( ! _pbBuff )
   {
      return false;
  }

   unsigned long ulCopySize;
   unsigned long ulSourceSize;

   ulSourceSize = this->getVarLenBufSize();

   if( ulBufSize < ulSourceSize )
   {
      ulCopySize = ulBufSize;
   }
   else
   {
      ulCopySize = ulSourceSize;
   }

   memcpy( pBuf, _vmResp.pvRepeat, ulCopySize );
   return true;
}



bool VMRequest::getRepeatRecord( unsigned long ulRecordNumber,
                                 char *pBuf,
                                 unsigned long ulBufSize ) const
{
   TRACE_METHOD( I_("VMRequest"),
                 I_("getRepeatRecord( unsigned long , char *, unsigned long )"))
   if ( ! _pbBuff )
   {
      return false;
   }


   if ( ulRecordNumber > _vmResp.usNumRepeat )
   {
      return false;      // Error, record number doesn't exist
   }

   unsigned long ulBufferOffset;
   unsigned long ulCopySize;
   char *pRepeatRecord;


   ulBufferOffset = (ulRecordNumber-1) * _vmResp.usRepeatLen;

   if( ulBufSize < _vmResp.usRepeatLen )
   {
      ulCopySize = ulBufSize;
   }
   else
   {
      ulCopySize = _vmResp.usRepeatLen;
   }

   pRepeatRecord = (char *) _vmResp.pvRepeat + ulBufferOffset;

   memcpy( pBuf, pRepeatRecord, ulCopySize * sizeof( char ));
   return true;
}



unsigned long VMRequest::getRepeatRecSize( void ) const
{
   return _vmResp.usRepeatLen;
}



unsigned long VMRequest::getNumRepeatRec( void ) const
{
   return _vmResp.usNumRepeat;
}



const char * VMRequest::getErrorMsg( void ) const
{
   return _szErrMsg;
}


unsigned long VMRequest::getBufferLength() const
{
   if ( !_pVmAppResp )
   {
      return 0;
   }
   return _pVmAppResp->ulBuffSize;
}


bool VMRequest::getBuffer( char *pBuf, unsigned long buffSize ) const
{
   if ( 0 == buffSize )
   {
      return false;
   }
   if ( !_pVmAppResp )
   {
      pBuf[0] = I_('\0');
   }
   unsigned long numToCopy = min( buffSize, _pVmAppResp->ulBuffSize );
   memcpy( pBuf, _pVmAppResp->pbBuff, numToCopy * sizeof( char ) );

   return true;
}


SEVERITY VMRequest::getTA2000SpecificData()
{
   MAKEFRAME( DICORE_CONDITION, I_("VMRequest::getTA2000SpecificData") );

   SEVERITY returnSeverity = CRITICAL_ERROR;

   VmExtractResp( _pbBuff, &_vmResp );

   if ( VM_P_OK == _vmResp.usRcPrimary )
   {
      returnSeverity = NO_CONDITION;
   }
   else if ( VM_P_WARNING == _vmResp.usRcPrimary )
   {
      DString      strOut;

      appendInt( strOut.getImp(), _vmResp.usRcSecondary );

      if ( _szErrMsg[ 0 ] )
      {
         strOut.append( I_(" Addtl. Msg: ") )
               .append( DString( DStringA(_szErrMsg) ))
               .append( I_(".") );
      }

      DString msg( I_("MSG=") );
      msg += DString( DStringA(_szErrMsg) );
      msg += I_(";RC=");
      msg += strOut;
      ADDCONDITIONFROMFILEIDI( DICORE_VMREQUEST_FAIL, msg.c_str() );
   }
   else
   {
      if ( VM_P_ERROR == _vmResp.usRcPrimary )
      {
         if ( VM_S_TIMEOUT == _vmResp.usRcSecondary )
         {
            THROWFROMFILE( DICORE_CONDITION, I_("VMRequest::_vmRequest"),
                           DICORE_VMAPPREQUEST_TIMEOUT )
         }
      }

      DString      strTemp;
      strTemp = I_("RC=");
      strTemp.append( I_("Primary(") );
      appendInt( strTemp.getImp(), _vmResp.usRcPrimary );
      strTemp.append( I_("), Secondary(") );
      appendInt( strTemp.getImp(), _vmResp.usRcSecondary );
      strTemp.append( I_(")") );

      if ( _szErrMsg[ 0 ] )
      {
         strTemp.append( I_(" Addtl. Msg: ") )
                .append( DString( DStringA(_szErrMsg) ))
                .append( I_(".") );
      }

      THROWFROMFILEIDI( DICORE_CONDITION, I_("VMRequest::_vmRequest"),
                        DICORE_VMAPPREQUEST_FAIL, strTemp.c_str() )
   }

   return returnSeverity;
}


//******************************************************************************
//
// ^PRIVATE METHOD      : VMRequest::_vmConnect
//
// ^DESCRIPTION : Call the VmConnectApp API
//
// ^PARAMETERS  :
//   ^^ void -
//
// ^RETURNS     : bool - true if connection works, false otherwise
//
// ^THROWS      :
//   ^^ ConditionException - DICORE_VMCONNECT_FAIL if connection fails
//
//******************************************************************************
bool VMRequest::_vmConnect( void )
{
   TRACE_METHOD( I_("VMRequest"), I_("_vmConnect( void )") )
   USHORT rc;

   rc = VmConnectApp( (char *)_sAppName.c_str(),
                      _szErrMsg,
                      APP_MSG_SIZE );
   if ( rc != VM_P_OK )
   {
      I_CHAR charRC[8];
      i_sprintf( charRC, I_("%hd"), rc );
      DString msg( I_("RC=") );
      msg += charRC;
      THROWFROMFILEIDI( DICORE_CONDITION, I_("VMRequest::_vmConnect"),
                        DICORE_VMCONNECT_FAIL, msg.c_str() )
   }
   else
   {
      _fConnected = true;
   }

   return _fConnected;
}



//******************************************************************************
//
// ^PRIVATE METHOD      : VMRequest::_vmDisconnect
//
// ^DESCRIPTION : Call the VmDisconect API
//
// ^PARAMETERS  :
//   ^^ void -
//
// ^RETURNS     : bool - true if disconnect works, false otherwise
//
// ^THROWS      :
//   ^^ ConditionException - DICORE_VMDISCONNECT_FAIL if disconnect fails
//
//******************************************************************************
bool VMRequest::_vmDisconnect( void )
{
   TRACE_METHOD( I_("VMRequest"), I_("_vmDisconnect( void )") )
   if ( ! _fConnected )
   {
      return false;
   }

   USHORT rc;

   rc = VmDisConnectApp( (char *)_sAppName.c_str(),
                         _szErrMsg,
                         APP_MSG_SIZE );
   if ( rc != VM_P_OK )
   {
      I_CHAR charRC[8];
      i_sprintf( charRC, I_("%hd"), rc );
      DString msg( I_("RC=") );
      msg += charRC;
      THROWFROMFILEIDI( DICORE_CONDITION, I_("VMRequest::_vmDisconnect"),
                        DICORE_VMDISCONNECT_FAIL, msg.c_str() )
   }

   return true;
}



//******************************************************************************
//
// ^PRIVATE METHOD      : VMRequest::_vmNotify
//
// ^DESCRIPTION : Call the VmNotifySem API
//
// ^PARAMETERS  :
//   ^^ void -
//
// ^RETURNS     : bool - true if disconnect works, false otherwise
//
// ^THROWS      :
//   ^^ ConditionException - DICORE_VMNOTIFYSEM_FAIL if notify call fails
//
//******************************************************************************
bool VMRequest::_vmNotify( void )
{
   TRACE_METHOD( I_("VMRequest"), I_("_vmNotify( void )") )
   USHORT rc;

   if ( !_fUsingHWND )
   {
      rc = VmNotifySem( (char *) _sAppName.c_str(),
                        (char *) _sSemName.c_str(),
                        VM_NOTIFY_RESPONSE | VM_BUFF_ALLOC,
                        NULL,
                        0L,
                        _szErrMsg,
                        APP_MSG_SIZE );
      if ( rc != VM_P_OK )
      {
         I_CHAR charRC[8];
         i_sprintf( charRC, I_("%hd"), rc );
         DString msg( I_("RC=") );
         msg += charRC;
         msg += I_(";SEM=");
         msg += DString( _sSemName );
         THROWFROMFILEIDI( DICORE_CONDITION, I_("VMRequest::_vmNotify"),
                           DICORE_VMNOTIFYSEM_FAIL, msg.c_str() );
      }
   }
   else
   {
      rc = VmNotifyWin( ( char * )_sAppName.c_str(),
                        ( HWND )_hwndResponse,
                        _ulMsg,
                        VM_NOTIFY_RESPONSE | VM_BUFF_ALLOC,
                        NULL,
                        0L,
                        _szErrMsg,
                        APP_MSG_SIZE );

      if ( rc != VM_P_OK )
      {
         i_ostringstream ostrMsg;
         ostrMsg << I_( "rc=" ) << rc << I_( ";" )
                 << I_( "hwnd=" ) << _hwndResponse << I_( ";" )
                 << I_( "msg=" ) << _ulMsg << I_( ";" )
                 << std::ends;

         THROWFROMFILEIDI( DICORE_CONDITION, I_( "VMRequest::_vmNotify" ),
                           DICORE_VMNOTIFYWIN_FAIL, ostrMsg.str().c_str() );
      }
   }

   return true;
}



bool VMRequest::_vmRequest( const DStringA& sHostName,
                            const DStringA& sViewName,
                            const unsigned char *pucViewRequest,
                            unsigned long ulRequestLength )
{
   MAKEFRAMEAUTOPROMOTE(
      DICORE_CONDITION,
      I_( "VMRequest::_vmRequest( const string& , " )
         I_( "const string& ,unsigned char *, unsigned long )" ) )

   // Free any existing buffers that we may have
   if ( _pbBuff )
   {
      // If we're doing V002 headers, then _pbBuff was replaced with
      // a converted buffer that we allocated, not AWD / View
      if ( m_dstrV002.length() > 0 )
      {
         delete [] _pbBuff;
      }
      else
      {
         VmFree( _pbBuff );
      }
      _pbBuff = NULL;
   }

   _szErrMsg[ 0 ] = 0;

   USHORT rc;

   rc = VmAppRequest( (char *) _sAppName.c_str(),
                      NULL,
                      (char *) sHostName.c_str(),
                      (char *) sViewName.c_str(),
                      VM_NEW_REQUEST,
                      ( unsigned char * )pucViewRequest,
                      ulRequestLength,
                      0L,
                      _ulTimeout,     // seconds
                      _szErrMsg,
                      APP_MSG_SIZE );
   if ( rc != VM_P_OK )
   {
      I_CHAR charRC[8];
      i_sprintf( charRC, I_("%hd"), rc );
      DString msg( I_("RC=") );
      msg += charRC;
      THROWFROMFILEIDI( DICORE_CONDITION, I_("VMRequest::_vmRequest"),
                        DICORE_VMAPPREQUEST_FAIL, msg.c_str() )
   }


   if ( !_fUsingHWND )
   {
      try
      {
         _pEventSemaphore->wait();
      }
      catch ( ConditionException &e )
      {
         DString            strTemp;

         strTemp = I_("error=");
         appendInt( strTemp.getImp(), ( int )e.getSeverity() );
         strTemp.append( I_(" ") )
                .append( e.getComponentName() )
                .append( I_("/") )
                .append( e.getMethodName() )
                .append( I_(" at ") )
                .append( DString( DStringA(e.getFileName()) ))
                .append( I_(":") );
         appendInt( strTemp.getImp(), e.getLineNumber() );
         strTemp.append( I_(" - code = ") );
         appendInt( strTemp.getImp(), e.getCode() );
         strTemp.append( I_(" msg = ") )
                .append( e.getMessage() )
                .append( I_(" correction = ") )
                .append( e.getCorrection() );

         try
         {
            _pEventSemaphore->reset();
         }
         catch ( ... )
         {
         }

         THROWFROMFILEIDI( DICORE_CONDITION, I_("VMRequest::_vmRequest"),
                           DICORE_VMREQUEST_WAIT_FAIL, strTemp.c_str() )
      }

      _pEventSemaphore->reset();

      vmGetResponse();
   }

   return true;
}


bool VMRequest::vmGetResponse()
{
   MAKEFRAME( DICORE_CONDITION, I_( "VMRequest::vmGetResponse()" ) );

   _pbBuff = ( PBYTE ) VmReadResponse( (char *) _sAppName.c_str() );

   if ( ! _pbBuff )
   {
      THROWFROMFILE( DICORE_CONDITION, I_( "VMRequest::_vmRequest" ),
                     DICORE_VMREADRESPONSE_FAIL )
   }

   if( _fnExtractOverride )
   {
      SEVERITY    severity;
      DString      strViewRequest;

      Condition   *c = NULL;
      bool        fThrow = false;

      try
      {
         severity = _fnExtractOverride( (unsigned char *)_pbBuff, &_vmResp );

         if ( severity < SEVERE_ERROR )
         {
            PROMOTECONDITIONS();
         }
         else
         {
            int count = CONDITIONCOUNT();

            for ( int i = 0; i < count; ++i )
            {
               c = GETCONDITION( i );

               if ( c->getSeverity() >= SEVERE_ERROR )
               {
                  fThrow = true;
                  break;
               }
            }
         }
      }
      catch( ConditionException &e )
      {
         DString      strTemp( I_("error=") );

         appendInt( strTemp.getImp(), ( int )e.getSeverity() );
         strTemp.append( I_(" ") )
                .append( e.getComponentName() )
                .append( I_("/") )
                .append( e.getMethodName() )
                .append( I_(" at ") )
                .append( DString( DStringA(e.getFileName()) ))
                .append( I_(":") );
         appendInt( strTemp.getImp(), e.getLineNumber() );
         strTemp.append( I_(" - code = ") );
         appendInt( strTemp.getImp(), e.getCode() );
         strTemp.append( I_(" msg = ") )
                .append( e.getMessage() )
                .append( I_(" correction = ") )
                .append( e.getCorrection() );

         throw EXCEPTIONFROMFILEIDI(
                            DICORE_VMREQUEST_CALLBACK_CONDITIONEXCEPTION_THROWN,
                            strTemp.c_str() );
      }
      catch( ... )
      {
         throw EXCEPTIONFROMFILE(
                           DICORE_VMREQUEST_CALLBACK_UNKNOWN_EXCEPTION_THROWN );
      }

      if ( fThrow && c )
      {
         THROWFROMCONDITION( *c );
      }
   }

   _pVmAppResp = (PVMAPPRESP) _pbBuff;

   // If we get back a V002 response, we need to convert the response from
   // V002 stuff into a PB00251
   if ( m_dstrV002.length() > 0 )
   {
      VMAPPRESP *pVMResp =
         ( VMAPPRESP * )new BYTE[ sizeof( VMAPPRESP ) +
                                     _pVmAppResp->ulBuffSize ];
      memcpy( pVMResp, _pbBuff, sizeof( VMAPPRESP ) );

      pVMResp->pbBuff = ( PBYTE )( ( char * )&( pVMResp->pbBuff ) + sizeof( PBYTE ) );

      VMV002Response vmV002Response( _pVmAppResp->pbBuff );
      pVMResp->ulBuffSize = vmV002Response.getPB00251( pVMResp->pbBuff );

      _dstrSessionKey = vmV002Response.getSessionKey();

      // Get rid of the VM return buffer (V002) and replace it with our
      // PB00250
      if ( _pbBuff )
      {
         VmFree( _pbBuff );
      }
      _pbBuff = ( PBYTE )pVMResp;
      _pVmAppResp = ( PVMAPPRESP )_pbBuff;
   }

   return true;
}


//******************************************************************************
//
// ^PRIVATE METHOD      : VMRequest::_vmRequest
//
// ^DESCRIPTION : Calls VmAppRequest, VmReadRespone, and VmExtractResponse
//
// ^PARAMETERS  :
//   ^^ const string& sViewName - the View Name
//   ^^ const string& sViewRequest - the request string
//
// ^RETURNS     : bool - True if communication with host is successful,
//                       false otherwise.
//                       This function may call user-defined callbacks. If these
//                       callbacks add Conditions that are WARNING or less
//                       severity, it will promoted them.  If the severity is
//                       greater than WARNING, a ConditionException will be
//                       thrown.
//
// ^THROWS      :
//   ^^ ConditionException - DICORE_VMAPPREQUEST_FAIL if communication with
//      host fails
//   ^^ ConditionException - DICORE_VMREADRESPONSE_FAIL if getting the response
//      buffer fails
//   ^^ ConditionException - DICORE_VMREQUEST_CALLBACK_CONDITIONEXCEPTION_THROWN
//      if the callback for extracting the return data (_fnExtractOverride)
//      throws a ConditionException.
//   ^^ ConditionException - DICORE_VMREQUEST_WAIT_FAIL if AWD View times out
//   ^^ ConditionException - DICORE_VMREQUEST_CALLBACK_UNKNOWN_EXCEPTION_THROWN
//      if the callback for extracting the return data (_fnExtractOverride)
//      throws something other than a ConditionException.
//   ^^ ConditionException - DICORE_VMREQUEST_CALLBACK_ERROR_CONDITION
//      if callback or for extracting the return data (_fnExtractOverride) adds
//      a Condition with a serverity greater than warning.
//
//******************************************************************************
bool VMRequest::_vmRequest( const DStringA& sHostName,
                            const DStringA& sViewName,
                            const DStringA& sViewRequest )
{
   return _vmRequest( sHostName, sViewName,
                      (unsigned char *)sViewRequest.c_str(),
                      sViewRequest.length() );
}



//******************************************************************************
//
// ^PRIVATE METHOD      : VMRequest::_assignAppName
//
// ^DESCRIPTION : Generate a unique app name for each VmRequest instance.
//                This _should_ work for multiple processes reliably.
//                Even though the PID and TID both have potential values
//               that could be more than 4 chars when converted to ascii hex
//               chars, in practice this never seems to happen (who would have
//               64k processes running on a machine?)
//
// ^PARAMETERS  :
//   ^^ void -
//
// ^RETURNS     : void -
//
// ^THROWS      : exception (string class)
//
//******************************************************************************
void VMRequest::_assignAppName( void )
{
   TRACE_METHOD( I_("VMRequest"), I_("_assignAppName( void )") )
   char szAppName[VM_NAME_LEN+1];
   memset( szAppName, 0, ( VM_NAME_LEN + 1 ) * sizeof( char ));

   unsigned short usApp;
   {
      CriticalSection crit( mutexAppName );
      usApp = ++usAppNameCounter;
   }

   char szTemp[ 20 ];
   sprintf( szTemp, "%8.8x", DSTGetCurrentProcessId() );
   strcpy( szAppName, &szTemp[ 4 ] );
   sprintf( szTemp, "%8.8hX", usApp );
   strcat( szAppName, &szTemp[ 4 ] );

   _sAppName = DStringA( szAppName );

   upperCase( _sAppName );
}



//******************************************************************************
//
// ^PRIVATE METHOD      : VMRequest::_send
//
// ^DESCRIPTION : Calls _
//
// ^PARAMETERS  :
//   ^^ const string& sHostName - The host name to pass to VmAppRequest
//   ^^ const string& sViewName - The view name to pass to VmAppRequest
//   ^^ const string& sViewRequest - The view data to pass to VmAppRequest
//
// ^RETURNS     : bool - true if primary AWD View return code is VM_P_OK,
//                   false otherwise.  This function may call user-defined
//                   callbacks.  If these callbacks add Conditions that are
//                   WARNING or less severity, it will promoted them.  If the
//                   severity is greater than WARNING, a ConditionException will
//                   be thrown.
//
// ^THROWS      :
//   ^^ ConditionException - DICORE_VMAPPREQUEST_FAIL If the call to
//                VmAppRequest fails.
//   ^^ ConditionException - DICORE_VMREADRESPONSE_FAIL If the call to
//                VmReadResponse fails.
//   ^^ ConditionException - DICORE_VMREQUEST_CALLBACK_CONDITIONEXCEPTION_THROWN
//                if either callback for send preprocessing (_fnSendPreprocess)
//                or for extracting the return data (_fnExtractOverride) throws
//                a ConditionException.
//   ^^ ConditionException - DICORE_VMREQUEST_CALLBACK_UNKNOWN_EXCEPTION_THROWN
//                if either callback for send preprocessing (_fnSendPreprocess)
//                or for extracting the return data (_fnExtractOverride) throws
//                something other than a ConditionException.
//   ^^ ConditionException - DICORE_VMREQUEST_CALLBACK_ERROR_CONDITION
//                if either callback for send preprocessing (_fnSendPreprocess)
//                or for extracting the return data (_fnExtractOverride) adds a
//                Condition with a serverity greater than warning.
//
//******************************************************************************
bool VMRequest::_send( const DStringA& sHostName, const DStringA& sViewName,
                       const DStringA& sViewRequest,
                       const DString &dstrV002Pass,
                       const DString &dstrV002NewPass )
{
   return _send( sHostName, sViewName, (unsigned char *)sViewRequest.c_str(),
                 sViewRequest.length(), dstrV002Pass, dstrV002NewPass );
}


bool VMRequest::_send( const DStringA& sHostName, const DStringA& sViewName,
                       const char *sViewRequest,
                       const DString &dstrV002Pass,
                       const DString &dstrV002NewPass )
{
   return _send( sHostName, sViewName, (unsigned char *)sViewRequest,
                 strlen( sViewRequest ), dstrV002Pass, dstrV002NewPass );
}


bool VMRequest::_send( const DStringA& sHostName, const DStringA& sViewName,
                       const unsigned char *uchViewRequest,
                       unsigned long viewRequestLength,
                       const DString &dstrV002Pass,
                       const DString &dstrV002NewPass )
{
   TRACE_METHOD( I_("VMRequest"),
                 I_("_send( const string&, const string&, const string& )") )

   DStringA dstrAReq;

   if ( m_dstrV002.length() > 0 )
   {
      VMV002Request v002Request( uchViewRequest,
                                 viewRequestLength,
                                 dstrV002Pass.asA().c_str(),
                                 m_dstrV002.asA().c_str(),
                                 dstrV002NewPass.asA().c_str(),
                                 "S",
                                 _dstrSessionKey.asA().c_str() );
      dstrAReq = v002Request.getHeader( 0L );
      uchViewRequest =
                  reinterpret_cast< const unsigned char * >( dstrAReq.c_str() );
      viewRequestLength = dstrAReq.length();
   }

   if ( _fnSendPreprocess )
   {
      MAKEFRAMENOTRACE( DICORE_CONDITION,
                        I_("VMRequest::_send( const DString&, const DString&, ")
                        I_("const DString& )") )

      SEVERITY    severity;
      unsigned char * /*PUCHAR*/      processedViewRequest;
      unsigned long processedViewRequestLength;

      Condition   *c = NULL;
      bool        fThrow = false;

      try
      {
         severity = _fnSendPreprocess( uchViewRequest, viewRequestLength,
                                       processedViewRequest,
                                       processedViewRequestLength );

         if ( severity < SEVERE_ERROR )
         {
            PROMOTECONDITIONS();
         }
         else
         {
            int count = CONDITIONCOUNT();

            for ( int i = 0; i < count; ++i )
            {
               c = GETCONDITION( i );

               if ( c->getSeverity() >= SEVERE_ERROR )
               {
                  fThrow = true;
                  break;
               }
            }
         }
      }
      catch( ConditionException &e )
      {
         DString      strTemp( I_("error=") );

         appendInt( strTemp.getImp(), ( int )e.getSeverity() );
         strTemp.append( I_(" ") )
                .append( e.getComponentName() )
                .append( I_("/") )
                .append( e.getMethodName() )
                .append( I_(" at ") )
                .append( DString( DStringA(e.getFileName()) ))
                .append( I_(":") );
         appendInt( strTemp.getImp(), e.getLineNumber() );
         strTemp.append( I_(" - code = ") );
         appendInt( strTemp.getImp(), e.getCode() );
         strTemp.append( I_(" msg = ") )
                .append( e.getMessage() )
                .append( I_(" correction = ") )
                .append( e.getCorrection() );

         throw EXCEPTIONFROMFILEIDI(
                            DICORE_VMREQUEST_CALLBACK_CONDITIONEXCEPTION_THROWN,
                            strTemp.c_str() );
      }
      catch( ... )
      {
         throw EXCEPTIONFROMFILE(
                           DICORE_VMREQUEST_CALLBACK_UNKNOWN_EXCEPTION_THROWN );
      }

      if ( fThrow && c )
      {
         THROWFROMCONDITION( *c );
      }

      return _vmRequest( sHostName, sViewName, processedViewRequest,
                         processedViewRequestLength );
   }

   // Send request to View Manager
   return _vmRequest( sHostName, sViewName, uchViewRequest, viewRequestLength );
}



//******************************************************************************
//
// ^PRIVATE METHOD      : VMRequest::_initVMRequest
//
// ^DESCRIPTION : called by constructors to do initialization of object
//
// ^PARAMETERS  :
//   ^^ unsigned long ulTimeout - the number of seconds before we give up
//                                waiting for a view
//
// ^RETURNS     : void
//
// ^THROWS      :
//   ^^ ConditionException - DICORE_VMREQ_INIT_FAIL if connection fails
//   ^^ exception - from string class
//
// ^EXAMPLE     : < if the use of this member is not obvious,
//                  give an example >
//
//******************************************************************************
void VMRequest::_initVMRequest( unsigned long ulTimeout )
{
   TRACE_METHOD( I_("VMRequest"),
                 I_("_initVMRequest( unsigned long ulTimeout )") )

   _ulTimeout = ulTimeout;

   memset( _szErrMsg, 0, ( APP_MSG_SIZE + 1 ) * sizeof( char ));
   memset( (void *) &_vmResp, 0, sizeof( VMDSTRESP ) );

   _assignAppName();

   try
   {
      // Connect to View Manager
      if ( _vmConnect() )
      {
         // Let View Manager timeout first, so let's make the event semaphore
         // timeout 3 seconds after View Manager
         //_sSemName = _sAppName;

         // append the time to the unique millisecond

         if ( !_fUsingHWND )
         {
            const int timeSize = 13;  // HH:MM:SS.999n
            char auchTime[ timeSize ];
            getUniqueMillisecondTime( auchTime );
            _sSemName = auchTime;

            DString tempSemName( _sSemName );
            _pEventSemaphore =
               new EventSemaphore( tempSemName.c_str(),
                                   true,
                                   -1, // No timeout
                                   EventSemaphore::INITIALLY_SET );

            if ( !_pEventSemaphore )
            {
               THROWFROMBASE( DICORE_CONDITION,
                              I_("VMRequest::VMRequest( unsigned long )"),
                              BASE_ALLOC_FAIL )
            }
         }

         // Tell View Manager how to notify us
         _vmNotify();
      }

      try
      {
         m_dstrV002 = GetConfigValueAsString( I_( "VmRequest" ), I_( "V002" ),
                                              I_( "Source_System_ID" ) );
      }
      catch( ... ) // do nothing if the ConfigManager doesn't exist
      {            // This exception is not a problem
         m_dstrV002 = I_( "" );
      }

      if ( m_dstrV002.length() )
      {
         TRACE_CLASS_MSG( I_( "VMRequest" ),
                          I_( "_initVMRequest( unsigned long ulTimeout )" ),
                          I_( "Using V002 headers" ) );
      }
   }
   catch ( ConditionException &e )
   {
      DString strTemp( I_("ERROR=") );

      strTemp.append( I_("\r\n") );
      appendInt( strTemp.getImp(), ( int )e.getSeverity() );
      strTemp.append( I_(" ") )
             .append( e.getComponentName() )
             .append( I_("/") )
             .append( e.getMethodName() )
             .append( I_(" at ") )
             .append( DString( DStringA(e.getFileName()) ))
             .append( I_(":") );
      appendInt( strTemp.getImp(), e.getLineNumber() );
      strTemp.append( I_(" - code ( ") );
      appendInt( strTemp.getImp(), e.getCode() );
      strTemp.append( I_("), msg ( ") )
             .append( e.getMessage() )
             .append( I_("), correction ( ") )
             .append( e.getCorrection() )
             .append( I_(")\r\n") )
             .append( I_(";") );

      THROWFROMFILEIDI( DICORE_CONDITION,
                        I_("VMRequest::_initVMRequest( unsigned long )"),
                        DICORE_VMREQUEST_INIT_FAIL, strTemp.c_str() )
   }
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
// $Log:   Y:/VCS/iFastAWD/diview/vmreq.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:24:14   kovacsro
// Initial revision.
// 
//    Rev 1.24   Sep 12 2001 16:55:18   DT11159
// Added code to support sending views directly to a
// destination rather than always using host routing.
// 
// 
//
//    Rev 1.23   Jun 08 2001 19:12:36   DT11159
// Added View Manager error information in conditions.
//
//    Rev 1.22   May 21 2001 10:25:52   dt24433
// Added CriticalSection include.
//
//    Rev 1.21   28 Mar 2001 12:19:38   DT14177
// put try-catch blocks around
// GetConfigValueAsString() calls
//
//    Rev 1.20   Oct 24 2000 17:54:04   dt17817
// Fix to not add critical conditions when nothing is wrong (some optional
// regsitry entries were not found)
//
//    Rev 1.19   Jun 23 2000 08:25:54   dtwk
// Passing an app name to AWD / View that is greater than 8 chars causes access
// violations in WIN95/98
//
//    Rev 1.18   May 02 2000 13:21:00   dtwk
// Add support in TA2000DB for AWD / View VmNotifyWin interface
//
//    Rev 1.17   Jan 01 2000 11:43:12   DT20842
// Changed ConditionException to use ERROR (not error), and
// be terminated and not use equal signs in the value section
//
//
//    Rev 1.16   Dec 09 1999 09:04:50   dtwk
// Add V002 Support
//
//    Rev 1.15   Oct 08 1999 12:17:34   dtwk
// Generate app name passed to awd/view from PID/TID combo
//
//    Rev 1.14   Oct 05 1999 17:59:44   dtwk
// Temporary fix that creates the appname from the PID/TID combo.
// This needs to be fixed permanently later on
//
//    Rev 1.13   Jun 18 1999 10:30:54   DCYK
// Remove extra delete on _pVmAppResp.
//
//
//    Rev 1.12   Jun 18 1999 09:38:18   DCYK
// Remove a memory leak.
//
//
//    Rev 1.11   May 06 1999 16:47:48   DCYK
// Fixes for multi-byte and unicode.
//
//
//    Rev 1.10   Apr 30 1999 14:53:40   DCYK
// Sync up with changes to condition files.
//
//
//    Rev 1.9   Apr 27 1999 15:10:32   DCYK
// Change from DI_BASE to DICORE
//
//
//    Rev 1.8   Apr 21 1999 16:50:52   DCYK
// Updates for Unicode.
//
//
//    Rev 1.7   Apr 20 1999 16:44:42   DCYK
// Only use regular chars for parameters.
//
//
//    Rev 1.6   Apr 19 1999 16:46:26   DCYK
// Fixes.
//
//
//    Rev 1.5   Mar 05 1999 10:30:08   DCYK
// Changes for I18N.
//
//
//    Rev 1.4   Feb 11 1999 15:04:48   DCYK
// Add support for binary elements.
//
//
//    Rev 1.3   Jan 28 1999 14:05:10   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.1   Aug 14 1998 14:48:50   DTWK
// Update comments
//
//    Rev 1.0   29 Jul 1998 20:35:04   DT14596
// DLMG New Archives for TA2000NTDT
//
//    Rev 1.13   Jun 08 1998 16:18:58   DTWK
// Allow view timeout lengths base on configuration variable.
// Make view timeout error message more user-friendly.
//
//    Rev 1.12   Apr 15 1998 16:56:56   dcyk
// Changed thrown condition
// for PlanTrac.
//
//
//    Rev 1.11   Nov 10 1997 12:40:00   DTWK
// Add support for specifying a host when sending a view.
//
//    Rev 1.10   Nov 09 1997 15:35:32   DTWK
// Add inclusion guards for faster compiles.
// Add guards so that class is flagged as exported only when compiling
// the output that actually exports the class.
//
//    Rev 1.9   Sep 10 1997 13:02:32   DTWK
// Add in Plantrac's Stratus header callback stuff.
//
//    Rev 1.8   Aug 28 1997 10:01:42   DTWK
// Tweak error processing.
//
//    Rev 1.7   Jul 23 1997 13:23:58   DTWK
// add tracing
//
//    Rev 1.6   Jul 07 1997 15:21:54   DTWK
// Update comments / add ConditionException fixes
//
//    Rev 1.5   Jun 13 1997 14:40:28   DTWK
// Add support for Condition class
//
//    Rev 1.4   Feb 18 1997 17:56:02   DPQD
// Added #include "EventSemaphore.hpp" (since it was pulled out of vmreq.hpp)
//
// Changed default constructor to accept parameter for timeout value (in seconds).
//
// Changed _szSemName (char []) to _sSemName (string class).
//
// Changed timeout values for EventSemaphore and View Manager to use
// the timeout passed in on construction.
//
// Added revision control comment block.
//
//
//
