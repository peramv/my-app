#pragma once
#if defined(VERBOSE_INCLUDES)
   #pragma message( "including "__FILE__ )
#endif   

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
//    Copyright 1999 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : BFHostConnectionManager.hpp
// ^AUTHOR : David B. Smith
// ^DATE   : January 2000
//
// ^CLASS    : BFHostConnectionManager
// ^INHERITS FROM :
//
// ^CLASS DESCRIPTION :
//    This class provides an abstract interface for the specific host connection
//    manager.
//
//******************************************************************************
#include <win32\platform.h>

class BFConnection;
class DStringA;

#include <bfconmgr\bfconnectionfactory.hpp>

// Import/Export resolution
#undef BFCONMGR_LINKAGE
#ifdef BFCONMGR_DLL
   #define BFCONMGR_LINKAGE CLASS_EXPORT
#else
   #define BFCONMGR_LINKAGE CLASS_IMPORT
#endif

class BFCONMGR_LINKAGE BFHostConnectionManager
{
public:
   BFHostConnectionManager( BFConnectionFactory* pFactory )
   : _connectionFactory( pFactory )
   {}

   virtual ~BFHostConnectionManager()
   { delete _connectionFactory;}

   virtual BFConnection *getConnection( void ) = 0;
   virtual void freeConnection(BFConnection *connection) = 0;

   virtual const DStringA &getHostId() const = 0;
   virtual int getMaxConnections() const = 0;
   virtual int getMinConnections() const = 0;
   virtual int getConnectionCount() const = 0;
   virtual int getConnectionsInUse() const = 0;
   virtual int getConnectionFailures() const = 0;

   virtual bool recycle() { return(true);}

   BFConnectionFactory* getConnectionFactory() const { return(_connectionFactory);}

protected:
   BFConnectionFactory *_connectionFactory;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/bfconmgr/BFHostConnectionManager.hpp-arc  $
// 
//    Rev 1.8   Oct 09 2002 17:40:18   PURDYECH
// New PVCS Database
// 
//    Rev 1.7   22 Mar 2002 15:11:36   PURDYECH
// Removed compile-time "including..." message
// Use #pragma once as include guard
// Include files with lower-case only names
// 
//    Rev 1.6   Mar 04 2002 12:30:50   IVESPAUL
// Handle dead AS/400 listeners for both ChangeHostMode and initial startup + 
// Logging changes.
//
//    Rev 1.5   Oct 22 2001 17:17:34   HUDAVID
// Connection Recycle code.
//
//    Rev 1.4   Jun 26 2001 12:54:42   PURDYECH
// Infrastructure Release 1.9 Integration.
//
//    Rev 1.3   03 May 2001 14:03:22   SMITHDAV
// Session management restructuring.
//
//    Rev 1.2   04 Dec 2000 11:38:24   SMITHDAV
// Add console connection monitoring support.
//
//    Rev 1.1   23 Oct 2000 20:13:18   SMITHDAV
// Change linkage to support new library BFConMfg.
//
//    Rev 1.0   Apr 28 2000 19:01:10   SMITHDAV
// Initial revision.
//
//   Rev 1.0   Apr 14 2000 13:47:42   SMITHDAV
//Initial revision.
*/