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
// ^FILE   :  BPConsolePortalMonitor.cpp
// ^AUTHOR :  David Smith
// ^DATE   :  December 2000
//
// ----------------------------------------------------------
#include "stdafx.h"

#include <SrcPrag.h>
#include "BPConsolePortalMonitor.hpp"
#include <bfutil\Console.hpp>
#include <bfutil\ConsoleCanvas.hpp>
#include <bfutil\BFThreadPool.hpp>
#include <srvbase\Server.hpp>
#include <srvbase\SrvPortal.hpp>

SrvPortal *BPConsolePortalMonitor::getPortal() {
   Server *server = Server::getInstance();
   if( NULL == server ) {
      return NULL;
   }
   return server->getPortal( _portalName );
}

BPConsolePortalMonitor::BPConsolePortalMonitor(const DString &portalName, const int refreshRate)
: BFThread()
, _portalName(portalName)
, _refreshRate(refreshRate)
, _shutdownEvent(true)
{
   _canvas = Console::getInstance()->createCanvas(8);

   _threadCount = 0;
   _threadsInUse = 0;
   _maxJobs = 0;
   _currentJobs = 0;
   _requestCount = 0;

   SrvPortal *portal =  getPortal();
   if ( NULL != portal ) {
      _requestCount = portal->getRequestCount();
   
      const BFThreadPool *threadPool = portal->getThreadPool();
      if ( NULL != threadPool ) {
         _threadCount = threadPool->getThreadsCount();
         _threadsInUse = threadPool->getWorkingThreadCount();
         _maxJobs = threadPool->getMaxJobsQueued();
         _currentJobs = threadPool->getCurrentJobsQueued();
      }
   }

   paintStaticInfo();
   paintDynamicInfo();

   _canvas->update();

   start();
}


BPConsolePortalMonitor::~BPConsolePortalMonitor()
{
   _shutdownEvent.set(); // signal the poller to shutdown
   wait(INFINITE); // wait for the poller to shutdown

   delete _canvas;

}

bool 
BPConsolePortalMonitor::refresh()
{

   _threadCount = 0;
   _threadsInUse = 0;
   _maxJobs = 0;
   _currentJobs = 0;

   SrvPortal *portal =  getPortal();
   if ( NULL != portal ) {
      _requestCount = portal->getRequestCount();

      const BFThreadPool *threadPool = portal->getThreadPool();
      if ( NULL != threadPool ) {
         _threadCount = threadPool->getThreadsCount();
         _threadsInUse = threadPool->getWorkingThreadCount();
         _maxJobs = threadPool->getMaxJobsQueued() + _threadCount;
         _currentJobs = threadPool->getCurrentJobsQueued() + _threadsInUse;
      }
   }

   paintStaticInfo();
   paintDynamicInfo();

   _canvas->update();

   return(true);
}

void
BPConsolePortalMonitor::paintStaticInfo()
{
   _canvas->write( 0, 
                   0, 
                   ConsoleColor::BLACK, 
                   ConsoleColor::BRIGHT_WHITE, 
                   "Portal Monitor" );

   SrvPortal *portal =  getPortal();
   if ( NULL != portal ) {
      _canvas->write( 20, 0, " : %s", portal->getDescriptionA().c_str() );
   }
}

void
BPConsolePortalMonitor::paintDynamicInfo()
{
   _canvas->write(5, 2, "Total Requests: %6d", _requestCount);

   if( _threadCount !=  0 || _maxJobs !=  0 ) {
      _canvas->write(  _canvas->getWidth()-3, 3, "max" );
   }

   paintThreadMonitor( 4 );
   paintJobQueueMonitor( 6 );
}

void 
BPConsolePortalMonitor::paintThreadMonitor( int row1 )
{

   if( _threadCount ==  0 )
      return;

   int row2 = row1+1;
   int width = _canvas->getWidth();
   int barCol = 8;
   int barWidth = width - barCol;

   _canvas->write( width-3, row1, "%3d", _threadCount );
   _canvas->write(       0, row2,  "%s",  "Threads "    );

   int threadsInUseCol = (int)(((double)barWidth/(double)_threadCount)*_threadsInUse) - 1;

   _canvas->write( barCol, row2, "%*.*s", barWidth, barWidth, "" );

   _canvas->write(            barCol, row2, "|" );
   _canvas->write( barCol+barWidth-1, row2, "|" );

   if( threadsInUseCol >= 2 )
      _canvas->write( barCol+threadsInUseCol-2, row2, "%3d", _threadsInUse );

   _canvas->highlight( barCol, row2,          barWidth, ConsoleColor::DARK_GREEN , ConsoleColor::BLACK );
   _canvas->highlight( barCol, row2, threadsInUseCol+1, ConsoleColor::GREEN      , ConsoleColor::BLACK );

}

void 
BPConsolePortalMonitor::paintJobQueueMonitor( int row1 )
{

   if( _maxJobs ==  0 )
      return;

   int row2 = row1+1;
   int width = _canvas->getWidth();
   int barCol = 8;
   int barWidth = width - barCol;

   _canvas->write( width-3, row1, "%3d", _maxJobs );
   _canvas->write(       0, row2,  "%s", "   Jobs " );

   int maxActiveJobCol = (int)(((double)barWidth/(double)_maxJobs)*_threadCount) - 1;

   int activeJobsCol = (int)(((double)barWidth/(double)_maxJobs)*_threadsInUse) - 1;
   int totalJobsCol = (int)(((double)barWidth/(double)_maxJobs)*_currentJobs) - 1;

   _canvas->write( barCol, row2, "%*.*s", barWidth, barWidth, "" );

   _canvas->write(                   barCol, row2, "|" );
   _canvas->write( barCol + maxActiveJobCol, row2, "|" );
   _canvas->write(    barCol + barWidth - 1, row2, "|" );

   if( totalJobsCol >= 2 )
      _canvas->write( barCol+totalJobsCol-2, row2, "%3d", _currentJobs );

   _canvas->highlight( barCol, row2,        barWidth, ConsoleColor::CYAN       , ConsoleColor::BLACK );
   _canvas->highlight( barCol, row2,  totalJobsCol+1, ConsoleColor::DARK_GREEN , ConsoleColor::BLACK );
   _canvas->highlight( barCol, row2, activeJobsCol+1, ConsoleColor::GREEN      , ConsoleColor::BLACK );

}

void
BPConsolePortalMonitor::run()
{
   while( !_shutdownEvent.wait(_refreshRate) )
   {
      refresh();
   }
}