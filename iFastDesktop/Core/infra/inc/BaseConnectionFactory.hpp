#pragma message( "including "__FILE__ )

#ifndef BASECONNECTIONFACTORY_HPP
   #define BASECONNECTIONFACTORY_HPP

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

class BaseConnection;
class DString;

// Import/Export resolution
   #undef DIVIEW_LINKAGE
   #ifdef DIVIEW_DLL
      #define DIVIEW_LINKAGE CLASS_EXPORT
   #else
      #define DIVIEW_LINKAGE CLASS_IMPORT
   #endif

/**
 * Base Connection Factory class
 *
 * Class is the common parent for most connection factory classes.  It provides
 * common functions needed for creating and destroying connections.
 */
class DIVIEW_LINKAGE BaseConnectionFactory
{
public:
   virtual ~BaseConnectionFactory( )
   {
   }

   /**
    * Create a connection.
    *
    * @param hostId   host ID for the connection.
    *
    * @return         Returns the connection.
    */
   virtual BaseConnection * createConnection( const DString & hostId ) = 0;

   /**
    * Destroy a connection.
    *
    * @param connection connection object to be destroyed.
    */
   virtual void destroyConnection( BaseConnection * connection ) = 0;

   /**
    * Get the maximum number of concurrent connections that this factory can
    * create.
    *
    * @param connection connection object to be destroyed.
    */
   virtual int getMaxConnectionCount( ) = 0;
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
// $Log:   Y:/VCS/iFastAWD/inc/BaseConnectionFactory.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:29:58   kovacsro
//Initial revision.
//
//   Rev 1.0   May 18 2001 15:52:02   DT11159
// 
//
//

#endif
