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
// ^FILE   : DebugMgr.cpp
// ^AUTHOR : Paul Dardeau
// ^DATE   : 03/12/98
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

#ifndef INCLUDED_STRING
#define INCLUDED_STRING
#include <string>
#endif

#ifndef DEBUGMGR_HPP
   #include "debugmgr.hpp"
#endif

#ifndef SOCKET_HPP
   #include "socket.hpp"
#endif

#ifndef COMMONTEMPLATES_H
   #include "commontemplates.h"
#endif

#ifndef CRITICALSECTION_HPP
   #include "criticalsection.hpp"
#endif

#include <time.h>

#include "configmanager.hpp"


#ifndef DATAPATH_H
   #include "datapath.h"
#endif

// ***************************************************************************
//   Message Format
//       4 bytes:          Message Id
//       6 bytes:          Call Stack Level
//       4 bytes:          Thread Id
//       Remaining Bytes:  Message
//
//
//  Ex:         "00010000230002XXXXXXXXXXXXXXXXXXXXXXX"
//
//              "0001 000023 0002 XXXXXXXXXXXXXXXXXXXXXXX"
//                |     |     |            |
//                |     |     |            |
//  Msg Id -------      |     |            |
//                      |     |            |
//  Call Stack Level ---      |            |
//                            |            |
//  Thread Id ----------------             |
//                                         |
//  Message -------------------------------
//
//****************************************************************************


namespace
{
   // Trace config manager
   const I_CHAR* TRACE_CONFIG_MANAGER = I_("DICORE");

   // Trace config set
   const I_CHAR* CONFIG_KEY_SET       = I_("DITracer");

   // Config keys
   const I_CHAR* INITIAL_VALUE_KEY    = I_("Initial Value");
   const I_CHAR* OUTPUT_DEVICE_KEY    = I_("Output Device");
   const I_CHAR* IP_ADDRESS_KEY       = I_("IP Address");
   const I_CHAR* PORT_NUMBER_KEY      = I_("Port Number");
   const I_CHAR* FILE_PATH_KEY        = I_("File Path");
   const I_CHAR* FILE_NAME_KEY        = I_("File Name");

   // Config values
   const I_CHAR* ON_VALUE             = I_("ON");
   const I_CHAR* OFF_VALUE            = I_("OFF");
   const I_CHAR* SOCKET_VALUE         = I_("SOCKET");
   const I_CHAR* FILE_VALUE           = I_("FILE");

   // File name constants
   const I_CHAR* FILE_NAME            = I_("di");
   const I_CHAR* FILE_EXT             = I_("trc");

   static const int MSG_ID_LEN        =  4;
   static const int PROCESS_ID_LEN    =  4;
   static const int THREAD_ID_LEN     =  4;
   static const int MILLISECOND_LEN   =  19;

   static MutexSemaphore allocMutex;
}


DebugMgr *DebugMgr::s_pMgr = NULL;

//******************************************************************************
//              Public Methods
//******************************************************************************

//  ****  BEGIN STATIC METHODS  ****

DebugMgr * DebugMgr::getInstance( void )
{
   CriticalSection crit( allocMutex );

   if( NULL == s_pMgr )
   {
      s_pMgr = new DebugMgr;
      s_pMgr->initTrace();
   }

   return(s_pMgr);
}

void DebugMgr::kill( void )
{
   // Do nothing
}

//  ****  END STATIC METHODS  ****

bool DebugMgr::setTracing( bool fTracing )
{
   CriticalSection crit ( m_mutex );

   if( true == fTracing )
   {
      _fIsTracing = connectTrace();
   }
   else
   {
      _fIsTracing = false;
   }

   return(_fIsTracing);
}

void DebugMgr::log( MESSAGE_TYPE msgType,
                    const DString& sClassName,
                    long lProcessId,
                    long lThreadId,
                    const DString &psMethod )
{
   DString strTraceMsg;

   formatMessageHeader( msgType, lProcessId, lThreadId, strTraceMsg );

   if( !psMethod.empty() )
   {
      if( !sClassName.empty() )
      {
         strTraceMsg += sClassName;
         strTraceMsg += I_("::");
      }

      strTraceMsg += psMethod;
   }
   else
   {
      strTraceMsg += sClassName;
   }

   write( strTraceMsg );
}

//******************************************************************************
//              Private Methods
//******************************************************************************

DebugMgr::DebugMgr() :
_fIsTracing( false ),
_pIPC( NULL),
_logFile( 0 ),
_logType ( LOG_NONE ),
m_register()
{
   m_register.registerSingleton( deregister, this );
}

DebugMgr::~DebugMgr()
{
   termTrace();
}

bool DebugMgr::write( const DString &pszMessage )
{
   CriticalSection critSection( m_mutex );

   // Must write out as ASCII so convert from DString -> DStringA
   DStringA pszMessageA( pszMessage );
   unsigned long ulBytesWritten;
   bool success = true;

   switch( _logType )
   {
      case LOG_SOCKET:
         if( !_pIPC || ! _pIPC->write( pszMessageA.c_str(),
                                       pszMessageA.length(),
                                       &ulBytesWritten ) )
         {
            termTrace();
            success = false;
         }
         break;

      case LOG_FILE:
         if( !_logFile )
         {
            termTrace();
         }

         *_logFile << pszMessageA.c_str() << std::endl << std::flush;
         break;

      default:
         success = false;
   }

   return(success);
}


//******************************************************************************
//
// ^PRIVATE METHOD : DebugMgr::formatMessageHeader
//
// ^DESCRIPTION : Format the message header before writing to socket
//
// ^PARAMETERS  :
//   ^^ DebugMgr::MESSAGE_TYPE msgType - Type of message
//   ^^ long lProcessId - Call stack level
//   ^^ long lThreadID - The current thread ID
//   ^^ string& strMsgHeader - Reference to the string to format
//
// ^RETURNS     : none
//
// ^THROWS      : none
//
//******************************************************************************
inline void DebugMgr::formatMessageHeader( DebugMgr::MESSAGE_TYPE msgType,
                                           long lProcessId,
                                           long lThreadId,
                                           DString& strMsgHeader )
{
   switch( msgType )
   {
      case CONSTRUCTOR:
         strMsgHeader = "0001";
         break;
      case DESTRUCTOR:
         strMsgHeader = "0002";
         break;
      case METHOD:
         strMsgHeader = "0000";
         break;
      case MESSAGE:
         strMsgHeader = "0003";
         break;
   }

   DString strProcessId;
   DString strThreadId;

   if( lProcessId > 9999 )
   {
      strProcessId = I_("****");
   }
   else
   {
      strProcessId.appendInt( lProcessId );
      strProcessId.padLeft( PROCESS_ID_LEN, '0' );
   }

   if( lThreadId > 9999 )
   {
      strThreadId = I_("****");
   }
   else
   {
      strThreadId.appendInt( lThreadId );
      strThreadId.padLeft( THREAD_ID_LEN, '0' );
   }

   // JavaDate initialized to the current time upon construction
   time_t t;
   time( &t );
   DString milliSecondStr = DString::asString( (int)t );
   milliSecondStr.padLeft( MILLISECOND_LEN, '0' );


   strMsgHeader += strProcessId;
   strMsgHeader += strThreadId;
   strMsgHeader += milliSecondStr;
}

bool DebugMgr::connectTrace()
{
   CriticalSection crit( m_mutex );

   // If the connection (socket or file) already exists
   // do not try to reconnect or reopen
   if( ! ( _pIPC || _logFile ) )
   {
      // Tracing turned on
      DString traceMethodString =
      GetElementalConfigValueAsString( TRACE_CONFIG_MANAGER,
                                       CONFIG_KEY_SET,
                                       OUTPUT_DEVICE_KEY );
      traceMethodString.upperCase();

      // The code will assume file, if the value is not socket
      if( SOCKET_VALUE == traceMethodString )
      {
         _logType = LOG_SOCKET;

         DString IPAddressString =
         GetElementalConfigValueAsString( TRACE_CONFIG_MANAGER,
                                          CONFIG_KEY_SET,
                                          IP_ADDRESS_KEY );

         long portNumber =
         GetElementalConfigValueAsLong( TRACE_CONFIG_MANAGER,
                                        CONFIG_KEY_SET,
                                        PORT_NUMBER_KEY );

         try
         {
#pragma warning( push )
#pragma warning( disable: 4244 )
            _pIPC = new Socket( DStringA(IPAddressString).c_str(), portNumber );
#pragma warning( pop )
         }
         catch( ... )
         {
            termTrace();
         }
      }
      else if( FILE_VALUE == traceMethodString )
      {
         _logType = LOG_FILE;

         DString filePathString =
         GetElementalConfigValueAsString( TRACE_CONFIG_MANAGER,
                                          CONFIG_KEY_SET,
                                          FILE_PATH_KEY );

         filePathString.upperCase();

         DString pathDelimiter( GetPathDelemiter() );

         if( filePathString[filePathString.length()] == pathDelimiter[0] )
            pathDelimiter = I_("");

         filePathString = filePathString + pathDelimiter + FILE_NAME;
         filePathString += '.';
         filePathString += FILE_EXT;

         _logFile = new std::ofstream( DStringA( filePathString ).c_str(),
                                       std::ios::app);

         if( ! _logFile )
         {
            termTrace();
         }
      }
      else
      {
         _logType = LOG_NONE;
      }
   }

   return(LOG_NONE != _logType);
}

void DebugMgr::initTrace()
{
   DString initialValue =
   GetElementalConfigValueAsString( TRACE_CONFIG_MANAGER, CONFIG_KEY_SET,
                                    INITIAL_VALUE_KEY );

   initialValue.upperCase();

   if( ON_VALUE == initialValue )
   {
      _fIsTracing = connectTrace();
   }

   return;
}

void DebugMgr::termTrace()
{
   if( _pIPC )
   {
      delete _pIPC;
      _pIPC = NULL;
   }

   if( _logFile )
   {
      delete _logFile;
      _logFile = NULL;
   }

   _logType = LOG_NONE;
   _fIsTracing = false;
}

void DebugMgr::deregister( void *pObj )
{
   const DebugMgr *pMgr = (DebugMgr *)pObj;

   if( pMgr == s_pMgr )
   {
      delete s_pMgr;
      s_pMgr = NULL;
   }
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF Core/ifdscore/debugmgr.cpp-arc  $
//
//   Rev 1.2   Oct 22 2004 09:02:48   PURDYECH
//PET910 - .NET Conversion Fixes
// 
//    Rev 1.1   Oct 09 2002 17:41:54   PURDYECH
// New PVCS Database
// 
//    Rev 1.0   Jul 05 2002 10:14:04   SMITHDAV
// Initial revision.
// 
//    Rev 1.12   Apr 13 2000 06:10:56   DMUM
// Removed Larry - Code
//
//    Rev 1.11   Mar 08 2000 07:01:36   DT20842
// Wrong project check-in; reverting to previous version
//
//    Rev 1.9   Dec 15 1999 13:09:14   DT20842
// Change old support to prevent destructors outputing blank messages
//
//    Rev 1.8   Dec 07 1999 11:17:46   DMUM
// Changes literal "DICore" to "DICORE"
//
//    Rev 1.7   May 18 1999 09:01:54   DT20842
// Elemental conditions remove requirement
// to force load the JRE during trace
// startup
//
//    Rev 1.6   May 13 1999 09:16:32   DMUM
// Implementing "Elemental" mode of operation
//
//    Rev 1.5   Apr 22 1999 08:45:36   DT20842
// Changed to standard library fstream
//
//    Rev 1.4   Apr 16 1999 13:28:38   DT20842
// Added new tracing
//
//    Rev 1.3   Feb 19 1999 08:53:30   DT20842
// Changed interface from DStringA -> DString
//
//    Rev 1.2   18 Feb 1999 10:38:04   DT14177
// UNICODE
//
//    Rev 1.1   Jan 28 1999 14:02:46   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.0   Dec 09 1998 13:51:08   DMUM
//
//
//    Rev 1.1   Aug 13 1998 11:58:24   DMUM
// Implemented IMPORT / EXPORT and #inlcude standards
//
//    Rev 1.0   29 Jul 1998 20:33:44   DT14596
// DLMG New Archives for TA2000NTDT
//
//    Rev 1.3   Jun 16 1998 16:12:50   dt27994
//
//
//

