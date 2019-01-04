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
// ^FILE   :  BFConnectionManager.cpp
// ^AUTHOR :  David Smith
// ^DATE   :  March 2000
//
// ----------------------------------------------------------
#ifndef SRCPRAG_h
   #include <SrcPrag.h>
#endif
#ifndef VMPRIVATECONNECTIONFACTORY_HPP
   #include "VmPrivateConnectionFactory.hpp"
#endif
#ifndef CONDITIONMANAGER_HPP
   #include <conditionmanager.hpp>
#endif
#ifndef CRITICALSECTION_HP
   #include <CriticalSection.hpp>
#endif
#ifndef VMPRIVATECONNECTION_HPP
   #include "VmPrivateConnection.hpp"
#endif

namespace
{
   const I_CHAR *CLASSNAME = I_( "VmPrivateConnectionFactory" );
}

VmPrivateConnectionFactory::VmPrivateConnectionFactory(const DStringA &namePrefix, int maxConnectionCount)
:_nameServer(namePrefix, maxConnectionCount)
{
}

BFConnection *
VmPrivateConnectionFactory::createConnection(const DStringA &hostId)
{
   DStringA connectionName;
   _nameServer.getName(connectionName);
   return(new VmPrivateConnection(hostId, connectionName));
}

void
VmPrivateConnectionFactory::destroyConnection(BFConnection *connection)
{
   if( NULL == connection )
      return;

   VmPrivateConnection *vmpConnection = dynamic_cast<VmPrivateConnection *> (connection);

   // make a copy of the connection name
   DStringA connectionName = vmpConnection->getName();

   // delete the object before freeing the name
   delete vmpConnection;

   // free the name for reuse
   _nameServer.freeName(connectionName);
}

VmPrivateConnectionFactory::NameServer::NameServer(const DStringA &namePrefix, int nameCount)
:  _nameQueue(),
_nameSemaphore(0, nameCount) // initially at zero to block early access attempts
{
   initNameQueue(namePrefix, nameCount);
}

void
VmPrivateConnectionFactory::NameServer::initNameQueue(const DStringA &namePrefix, int nameCount)
{
   {
      CriticalSection cs( _nameQueueLock );

      for( int i=0; i<nameCount; i++ )
      {
         char name[9];
         sprintf( name, "%4.4s%04X", namePrefix.c_str(), i );
         _nameQueue.push( DStringA(name) );
      }
   }

   // release lock on access
   _nameSemaphore.release( nameCount ); 
}

DStringA&
VmPrivateConnectionFactory::NameServer::getName(DStringA& name)
{
   // keep us under _maxNames+1
   _nameSemaphore.wait( INFINITE ); 
   CriticalSection cs( _nameQueueLock );

   name = _nameQueue.front();
   _nameQueue.pop();

   return(name);
}

void 
VmPrivateConnectionFactory::NameServer::freeName(const DStringA& name)
{
   {
      CriticalSection cs( _nameQueueLock );

      _nameQueue.push(name);
   }

   _nameSemaphore.release( 1 ); 
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/bfconmgr/VmPrivateConnectionFactory.cpp-arc  $
// 
//    Rev 1.3   Oct 09 2002 17:40:24   PURDYECH
// New PVCS Database
// 
//    Rev 1.2   Aug 29 2002 12:59:28   PURDYECH
// VMInterface fixes
// 
//    Rev 1.1   03 May 2001 14:03:04   SMITHDAV
// Session management restructuring.
// 
//    Rev 1.0   23 Oct 2000 20:10:50   SMITHDAV
// Initial revision.
// 
//    Rev 1.3   May 10 2000 18:25:48   SMITHDAV
// Further on the destroyConnection bug.
// 
//    Rev 1.2   May 10 2000 18:09:42   SMITHDAV
// Change to allow user to specify connection name prefix.  Also bug fix on destroyConnection: name should not be freed until after connection is deleted.
// 
//    Rev 1.1   May 02 2000 17:25:52   DT24433
// changed to use Infra CriticalSection
//
*/
