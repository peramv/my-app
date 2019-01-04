#pragma message( "including "__FILE__ )

#ifndef VMNAMESERVER_HPP
   #define VMNAMESERVER_HPP

/**
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

   #ifndef PLATFORM_H
      #include "platform.h"
   #endif

   #ifndef INCLUDED_QUEUE
      #define INCLUDED_QUEUE
      #include <queue>
   #endif

   #ifndef INFRASEMAPHORE_HPP
      #include "InfraSemaphore.hpp"
   #endif
   #ifndef MUTEXSEMAPHORE_HPP
      #include "MutexSemaphore.hpp"
   #endif

// Import/Export resolution
   #undef DIVIEW_LINKAGE
   #ifdef DIVIEW_DLL
      #define DIVIEW_LINKAGE CLASS_EXPORT
   #else
      #define DIVIEW_LINKAGE CLASS_IMPORT
   #endif

class DString;

/**
 * View Manager Name Server class
 *
 * Class manages a fixed number of names that are suitable as the
 * "application name" parameter to VmConnectionApp API.
 *
 * See the VmConnectApp API in the AWD/View Client for WIN32 document for
 * more information.
 */
class DIVIEW_LINKAGE VmNameServer
{
public:
   /**
    * Construct a View Manager Name Server to manage a fixed number of names.
    *
    * @param maxConnectionCount number of names to manage.
    */
   VmNameServer( int maxConnectionCount );

   virtual ~VmNameServer( ) { }

   /**
    * Get a name.
    *
    * @returns A name that can be used to call VmConnectionApp.
    */
   virtual const DString & getName( DString & connectionName );

   /**
    * Free a name.
    *
    * @returns A name that can be used to call VmConnectionApp.
    */
   virtual void freeName( const DString & connectionName );

private:
   void initNameQueue( int nameCount );

   typedef std::queue< DString > NAME_QUEUE;

   const int m_maxNameCount;
   NAME_QUEUE m_nameQueue;
   MutexSemaphore m_nameQueueLock;
   InfraSemaphore m_nameSemaphore;
};

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
// $Log:   Y:/VCS/iFastAWD/inc/VmNameServer.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:33:22   kovacsro
//Initial revision.
//
//   Rev 1.1   Jun 28 2001 16:49:44   DT11159
//Renamed some classes.
//
//   Rev 1.0   May 18 2001 15:53:12   DT11159
// 
//
//

#endif
