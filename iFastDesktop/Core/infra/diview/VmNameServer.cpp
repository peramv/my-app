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
 *   Class:   VmNameServer.cpp
 *
 *   Class Description
 *
 */
#define DIVIEW_DLL

#ifndef SRCPRAG_h
   #include "SrcPrag.h"
#endif

#ifndef VMNAMESERVER_HPP
   #include "VmNameServer.hpp"
#endif
#ifndef CRITICALSECTION_HP
   #include "CriticalSection.hpp"
#endif

namespace
{
   const I_CHAR * const CLASSNAME = I_( "VmNameServer" );
   int seq = 0;
}

VmNameServer::VmNameServer( int maxNameCount ) :
m_maxNameCount( maxNameCount ),
m_nameSemaphore( 0, maxNameCount )
{
   long pid;

   pid = DSTGetCurrentProcessId( );

   {
      CriticalSection cs( m_nameQueueLock );

      for ( int i = 0; i < m_maxNameCount; i++ )
      {
         I_CHAR name[9];
         ++seq;

         //
         // The sequence number is XORed with a magic number to make it more
         // likely that the resulting name will be unique.  I know this is a
         // hack.  View Manager should return a handle when an application
         // connection is made instead of having applications try to come up
         // with "unique" connection names.
         //
         i_sprintf( name, I_( "%04X%04X" ),
                    pid & 0xFFFF,
                    seq & 0xFFFF ^ 0x5555 );

         DString connectionName( name );

         m_nameQueue.push( connectionName );
      }
   }

   // Release lock on access.
   m_nameSemaphore.release( m_maxNameCount );
}

const DString &
VmNameServer::getName( DString & connectionName )
{
   // Keep us under m_maxNames+1.
   m_nameSemaphore.wait( INFINITE );
   CriticalSection cs( m_nameQueueLock );

   connectionName = m_nameQueue.front( );
   m_nameQueue.pop( );

   return ( connectionName );
}

void
VmNameServer::freeName( const DString & connectionName )
{
   {
      CriticalSection cs( m_nameQueueLock );
      m_nameQueue.push( connectionName );
   }

   m_nameSemaphore.release( 1 );
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
// $Log:   Y:/VCS/iFastAWD/diview/VmNameServer.cpp-arc  $
// 
//    Rev 1.0   28 Jan 2008 13:24:12   kovacsro
// Initial revision.
//
//   Rev 1.1   Jun 08 2001 19:12:16   DT11159
//Added View Manager error information in conditions.
//
//   Rev 1.0   May 18 2001 11:41:08   DT11159
//
//
//
