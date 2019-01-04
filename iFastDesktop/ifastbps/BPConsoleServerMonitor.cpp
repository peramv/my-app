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
// ^FILE   :  BPConsoleServerMonitor.cpp
// ^AUTHOR :  David Smith
// ^DATE   :  December 2000
//
// ----------------------------------------------------------
#include "stdafx.h"

#include <SrcPrag.h>
#include "BPConsoleServerMonitor.hpp"
#include <bfutil\Console.hpp>
#include <bfutil\ConsoleCanvas.hpp>
#include <srvbase\Server.hpp>
#include <bfutil\BFThreadPool.hpp>

BPConsoleServerMonitor::BPConsoleServerMonitor(const int refreshRate)
:  BFThread(),
_refreshRate(refreshRate),
_shutdownEvent(true)
{
   _canvas = Console::getInstance()->createCanvas(7);

   Server *server = Server::getInstance();

   if( NULL == server )
   {
      _threadCount = 0;
      _threadsInUse = 0;
      _maxJobs = 0;
      _currentJobs = 0;
   }
   else
   {
      const BFThreadPool &threadPool = server->getThreadPool();

      _threadCount = threadPool.getThreadsCount();
      _threadsInUse = threadPool.getWorkingThreadCount();
      _maxJobs = threadPool.getMaxJobsQueued();
      _currentJobs = threadPool.getCurrentJobsQueued();
   }

   paintStaticInfo();
   paintDynamicInfo();

   _canvas->update();

   start();
}


BPConsoleServerMonitor::~BPConsoleServerMonitor()
{
   _shutdownEvent.set(); // signal the poller to shutdown
   wait(INFINITE); // wait for the poller to shutdown

   delete _canvas;

}

bool 
BPConsoleServerMonitor::refresh()
{

   Server *server = Server::getInstance();

   if( NULL == server )
   {
      _threadCount = 0;
      _threadsInUse = 0;
      _maxJobs = 0;
      _currentJobs = 0;
   }
   else
   {
      const BFThreadPool &threadPool = server->getThreadPool();;

      _threadCount = threadPool.getThreadsCount();
      _threadsInUse = threadPool.getWorkingThreadCount();
      _maxJobs = threadPool.getMaxJobsQueued() + _threadCount;
      _currentJobs = threadPool.getCurrentJobsQueued() + _threadsInUse;
   }

   paintStaticInfo();
   paintDynamicInfo();

   _canvas->update();

   return(true);
}

void
BPConsoleServerMonitor::paintStaticInfo()
{

   int start = 10;
   int width = _canvas->getWidth() - start;

   Server *server = Server::getInstance();

   _canvas->write( 0, 
                   0, 
                   ConsoleColor::BLACK, 
                   ConsoleColor::BRIGHT_WHITE, 
                   "BP Server Monitor" );

   if( NULL != server )
      _canvas->write( 20, 0, "Port %d", server->getPort() );


   // Thread monitor
   if( _threadCount != 0 )
   {
      _canvas->write( start+width-3, 2, "%3d", _threadCount );
      _canvas->write(             0, 3,  "%s", "Threads "    );
   }


   // Job Queue monotor
   if( _threadCount != 0 )
   {
      _canvas->write( start+width-3, 5, "%3d", _maxJobs );
      _canvas->write(             0, 6,  "%s", "   Jobs " );
   }
}

void
BPConsoleServerMonitor::paintDynamicInfo()
{

   int startCol = 8;
   int width = _canvas->getWidth() - startCol;

   paintThreadMonitor( startCol, 3, width );
   paintJobQueueMonitor( startCol, 6, width );

}

void 
BPConsoleServerMonitor::paintThreadMonitor( int startCol, int row, int width )
{

   if( _threadCount ==  0 )
      return;

   int threadsInUseCol = (int)(((double)width/(double)_threadCount)*_threadsInUse) - 1;

   _canvas->write( startCol, row, "%*.*s", width, width, "" );

   _canvas->write(         startCol, row, "|" );
   _canvas->write( startCol+width-1, row, "|" );

   if( threadsInUseCol >= 2 )
      _canvas->write( startCol+threadsInUseCol-2, row, "%3d", _threadsInUse );

   _canvas->highlight( startCol, row,             width, ConsoleColor::DARK_GREEN , ConsoleColor::BLACK );
   _canvas->highlight( startCol, row, threadsInUseCol+1, ConsoleColor::GREEN      , ConsoleColor::BLACK );

}

void 
BPConsoleServerMonitor::paintJobQueueMonitor( int startCol, int row, int width )
{

   if( _maxJobs ==  0 )
      return;

   int maxActiveJobCol = (int)(((double)width/(double)_maxJobs)*_threadCount) - 1;

   int activeJobsCol = (int)(((double)width/(double)_maxJobs)*_threadsInUse) - 1;
   int totalJobsCol = (int)(((double)width/(double)_maxJobs)*_currentJobs) - 1;

   _canvas->write( startCol, row, "%*.*s", width, width, "" );

   _canvas->write(                   startCol, row, "|" );
   _canvas->write( startCol + maxActiveJobCol, row, "|" );
   _canvas->write(       startCol + width - 1, row, "|" );

   if( totalJobsCol >= 2 )
      _canvas->write( startCol+totalJobsCol-2, row, "%3d", _currentJobs );

   _canvas->highlight( startCol, row,           width, ConsoleColor::CYAN       , ConsoleColor::BLACK );
   _canvas->highlight( startCol, row,  totalJobsCol+1, ConsoleColor::DARK_GREEN , ConsoleColor::BLACK );
   _canvas->highlight( startCol, row, activeJobsCol+1, ConsoleColor::GREEN      , ConsoleColor::BLACK );

}

void
BPConsoleServerMonitor::run()
{
   while( !_shutdownEvent.wait(_refreshRate) )
   {
      refresh();
   }
}