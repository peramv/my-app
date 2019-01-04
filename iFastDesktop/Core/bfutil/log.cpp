#include "stdafx.h"
#include <bf/log/log.hpp>
#include <bf/log/abstractlogtarget.hpp>
#include <assert.h>
#include <set>
#include <bfutil/bfguard.hpp>

namespace bf {
namespace log {
BFUTIL_LINKAGE Log theLog;
}
}


static BFCritSec& getLogSetCS()
{
   static BFCritSec instance;
   return(instance);
}
typedef std::set< bf::log::Log* > LOG_SET;
static LOG_SET& getLogSet()
{
   static LOG_SET instance;
   return( instance );
}

void bf::log::Log::attachThreads()
{
   BFGuard g( getLogSetCS() );
   LOG_SET& rSet = getLogSet();
   LOG_SET::iterator it = rSet.begin();
   for( ; rSet.end() != it; ++it ) 
   {
      Log* pLog = (*it);
      pLog->attachThread();
   }
}

void bf::log::Log::detachThreads()
{
   BFGuard g( getLogSetCS() );
   LOG_SET& rSet = getLogSet();
   LOG_SET::iterator it = rSet.begin();
   for( ; rSet.end() != it; ++it ) 
   {
      Log* pLog = (*it);
      pLog->detachThread();
   }
}

bf::log::Log::Log()
: eReportingThreshold_( LogStream::Level::e_notify )
, fReportingCategories_( all )
{
   BFGuard g( getLogSetCS() );
   LOG_SET& rSet = getLogSet();
   rSet.insert( const_cast< Log* >( this ) );
}

bf::log::Log::~Log()
{
   flushAll();
   BFGuard gTarget( csTargets_ );
   TARGET_MAP::iterator it = mapTargets_.begin();
   for( ; mapTargets_.end() != it; ++it )
   {
      AbstractLogTarget* pTarget = (*it).second;
      delete pTarget;
   }

   BFGuard gSet( getLogSetCS() );
   LOG_SET& rSet = getLogSet();
   LOG_SET::iterator itSet = rSet.find( const_cast< Log* >( this ) );
   if( rSet.end() != itSet )
   {
      rSet.erase( itSet );
   }
}

void bf::log::Log::addTarget( const DString& strTarget, AbstractLogTarget* pTarget )
{
   assert( NULL != pTarget );
   BFGuard g( csTargets_ );
   TARGET_MAP::iterator it = mapTargets_.find( strTarget );
   if( mapTargets_.end() == it )
   {
      mapTargets_[ strTarget ] = pTarget;
   }
   else
   {
      // TODO: throw an exception
   }
}

bf::log::AbstractLogTarget* bf::log::Log::removeTarget( const DString& strTarget ) 
{
   AbstractLogTarget* pTarget = NULL;
   BFGuard g( csTargets_ );
   TARGET_MAP::iterator it = mapTargets_.find( strTarget );
   if( mapTargets_.end() != it )
   {
      pTarget = (*it).second;
      mapTargets_.erase( it );
   }
   return( pTarget );
}

void bf::log::Log::suspendTarget( const DString& strTarget )
{
   AbstractLogTarget* pTarget = NULL;
   BFGuard g( csTargets_ );
   TARGET_MAP::iterator it = mapTargets_.find( strTarget );
   if( mapTargets_.end() != it )
   {
      pTarget = (*it).second;
      pTarget->suspend();
   }
}

void bf::log::Log::restartTarget( const DString& strTarget )
{
   AbstractLogTarget* pTarget = NULL;
   BFGuard g( csTargets_ );
   TARGET_MAP::iterator it = mapTargets_.find( strTarget );
   if( mapTargets_.end() != it )
   {
      pTarget = (*it).second;
      pTarget->restart();
   }
}

bool bf::log::Log::hasTarget( const DString& strTarget ) const 
{
   BFGuard g( csTargets_ );
   TARGET_MAP::const_iterator it = mapTargets_.find( strTarget );
   return( mapTargets_.end() != it );
}

bf::log::AbstractLogTarget* bf::log::Log::getTarget( const DString& strTarget )
{
   BFGuard g( csTargets_ );
   TARGET_MAP::iterator it = mapTargets_.find( strTarget );
   if( mapTargets_.end() != it ) {
      return( (*it).second );
   }
   return( NULL );
}

void bf::log::Log::flushAll() 
{
   BFGuard gTargets( csTargets_ );
   BFGuard gStreams( csStreams_ );

   STREAM_MAP::iterator itStream = mapStreams_.begin();
   for( ; mapStreams_.end() != itStream; ++itStream )
   {
      LogStream* pStream = (*itStream).second;
      flushStream( pStream );
   }
}

void bf::log::Log::flushStream( LogStream* pStream )
{
   BFGuard gStream( pStream->getCS() );
   const DString& str = pStream->get();
   BFGuard gTargets( csTargets_ );
   TARGET_MAP::iterator itTarget = mapTargets_.begin();
   for( ; itTarget != mapTargets_.end(); ++itTarget )
   {
      AbstractLogTarget* pTarget = (*itTarget).second;
      if( NULL != pTarget )
      {
         pTarget->write( str );
      }
   }
   pStream->reset();
}

void bf::log::Log::setCategory( unsigned long fCat )
{
   BFGuard g( csStreams_ );
   stream().setCategory( fCat );
}

bool bf::log::Log::isOkToLog( enum LogStream::Level eLevel, unsigned long fCat ) const 
{
   BFGuard g( csReporting_ );
   if( eLevel >= eReportingThreshold_ &&
       ( all == fReportingCategories_ ||
         0 == fCat ||
         ( fReportingCategories_ & fCat ) ) ) {
      return( true );
   }
   return( false );
}

void bf::log::Log::join( const LogStream* pLogStream )
{
   // get the contents of pLog and append it directly to the end of the LogStream for this thread
   BFGuard g(csStreams_ );
   stream().join( pLogStream );
}

namespace bf {
   namespace log {

      // function setcat
      static void swsetcat(Log& l, unsigned long n)
      {
         l.setCategory( n );
      }

      logmanip< unsigned long > __cdecl setcat( unsigned long n)
      {
         return( logmanip< unsigned long >( &swsetcat, n ) );
      }

      void Log::setReportingLevel( enum LogStream::Level eCurr ) 
      {
         // set reporting level for current thread.  This is a sticky property
         stream().setReportingLevel( eCurr );

      }

   }  // namespace log
}  // namespace bf
//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/core/bfutil/log.cpp-arc  $
// 
//    Rev 1.1   Feb 20 2009 14:48:54   purdyech
// ZTS Revision 6
// 
//    Rev 1.0   Aug 12 2003 10:12:56   PURDYECH
// Initial Revision
//
