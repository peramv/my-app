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
// ^FILE   :  VMConnectionFactory.cpp
// ^AUTHOR :  David Smith / Glen McNabb  
// ^DATE   :  March 2000
//
// ----------------------------------------------------------
#ifndef SRCPRAG_h
   #include <SrcPrag.h>
#endif
#ifndef VMCONNECTIONFACTORY_HPP
   #include "VmConnectionFactory.hpp"
#endif
#ifndef CONDITIONMANAGER_HPP
   #include <conditionmanager.hpp>
#endif
#ifndef CRITICALSECTION_HP
   #include <CriticalSection.hpp>
#endif
#ifndef VMCONNECTION_HPP
   #include "VmConnection.hpp"
#endif

namespace
{
   const I_CHAR *CLASSNAME = I_( "VmConnectionFactory" );
}


//******************************************************************************
VmConnectionFactory::VmConnectionFactory( const DStringA &namePrefix, int maxConnectionCount )
:_nameServer( namePrefix, maxConnectionCount )
{
}


//******************************************************************************
BFConnection* VmConnectionFactory::createConnection( const DStringA &hostId )
{
   DStringA connectionName;
   _nameServer.getName( connectionName );
   return(new VmConnection( hostId, connectionName ));
}

//******************************************************************************
void VmConnectionFactory::destroyConnection( BFConnection *connection )
{
   if( NULL == connection )
      return;

   VmConnection *vmConnection = dynamic_cast<VmConnection *> ( connection );

   // make a copy of the connection name
   DStringA connectionName = vmConnection->getName();

   // delete the object before freeing the name
   delete vmConnection;

   // free the name for reuse
   _nameServer.freeName( connectionName );
}

//******************************************************************************
VmConnectionFactory::NameServer::NameServer( const DStringA &namePrefix, int nameCount )
:  _nameQueue(),
_nameSemaphore( 0, nameCount ) // initially at zero to block early access attempts
{
   initNameQueue( namePrefix, nameCount );
}

//******************************************************************************
void VmConnectionFactory::NameServer::initNameQueue( const DStringA &namePrefix, int nameCount )
{
   {
      CriticalSection cs( _nameQueueLock );

      for( int i=0; i<nameCount; i++ )
      {
         char name[9];
         sprintf( name, "%4.4s%04X", namePrefix.c_str(), i );
         _nameQueue.push( DStringA( name ) );
      }
   }

   // release lock on access
   _nameSemaphore.release( nameCount ); 
}

//******************************************************************************
DStringA& VmConnectionFactory::NameServer::getName( DStringA& name )
{
   // keep us under _maxNames+1
   _nameSemaphore.wait( INFINITE ); 
   CriticalSection cs( _nameQueueLock );

   name = _nameQueue.front();
   _nameQueue.pop();

   return(name);
}

//******************************************************************************
void VmConnectionFactory::NameServer::freeName( const DStringA& name )
{
   {
      CriticalSection cs( _nameQueueLock );

      _nameQueue.push( name );
   }

   _nameSemaphore.release( 1 ); 
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/bfconmgr/VmConnectionFactory.cpp-arc  $
// 
//    Rev 1.3   Oct 09 2002 17:40:22   PURDYECH
// New PVCS Database
// 
//    Rev 1.2   Aug 29 2002 12:59:26   PURDYECH
// VMInterface fixes
// 
//    Rev 1.1   May 22 2001 13:49:26   MCNABBGL
// server monitoring functionality, explicit server registration with connection manager, fastrequestor modifications
// 
//
*/
