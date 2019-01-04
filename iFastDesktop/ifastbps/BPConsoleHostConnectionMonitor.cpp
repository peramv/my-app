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
// ^FILE   :  BPConsoleHostConnectionMonitor.cpp
// ^AUTHOR :  David Smith
// ^DATE   :  December 2000
//
// ----------------------------------------------------------
#include "stdafx.h"

#ifndef SRCPRAG_h
   #include <SrcPrag.h>
#endif
#ifndef BPCONSOLEHOSTCONNECTIONMONITOR_HPP
   #include "BPConsoleHostConnectionMonitor.hpp"
#endif
#ifndef BFHOSTCONNECTIONMANAGER_HPP
   #include <bfconmgr\BFHostConnectionManager.hpp>
#endif
#ifndef CONSOLE_HPP
   #include <bfutil\Console.hpp>
#endif
#ifndef CONSOLECANVAS_HPP
   #include <bfutil\ConsoleCanvas.hpp>
#endif

#include <sstream>

#include <ifastdbrkr\RTSSocketConnectionFactory.hpp>

BPConsoleHostConnectionMonitor::BPConsoleHostConnectionMonitor(const BFHostConnectionManager *hostConnectionManager)
:  _hostConnectionManager(hostConnectionManager)
{
   _canvas = Console::getInstance()->createCanvas(5);

   _max = _hostConnectionManager->getMaxConnections();
   _min = _hostConnectionManager->getMinConnections();
   _connectionCount = _hostConnectionManager->getConnectionCount();
   _connectionsInUse = _hostConnectionManager->getConnectionsInUse();
   _connectionFailures = _hostConnectionManager->getConnectionFailures();

   paintStaticInfo();
   paintDynamicInfo();

   _canvas->update();
}


BPConsoleHostConnectionMonitor::~BPConsoleHostConnectionMonitor()
{

   delete _canvas;

}

bool 
BPConsoleHostConnectionMonitor::refresh()
{

   _connectionCount = _hostConnectionManager->getConnectionCount();
   _connectionsInUse = _hostConnectionManager->getConnectionsInUse();
   _connectionFailures = _hostConnectionManager->getConnectionFailures();

   paintDynamicInfo();

   _canvas->update();

   return(true);
}

void
BPConsoleHostConnectionMonitor::paintStaticInfo()
{

   int width = _canvas->getWidth();

   int minCol = (int)(((double)width/(double)_max)*_min) - 1;

   std::stringstream ss; 
   ss << "Host Monitor: " 
   << _hostConnectionManager->getHostId().c_str();

   _canvas->write( 0, 
                   0, 
                   ConsoleColor::BLACK, 
                   ConsoleColor::BRIGHT_WHITE, 
                   ss.str().c_str() );

   RTSSocketConnectionFactory* pConnectionFactory = 
   dynamic_cast< RTSSocketConnectionFactory* >( _hostConnectionManager->getConnectionFactory() );

   if( NULL != pConnectionFactory )
   {
      std::stringstream ss;
      ss << " (" 
      << pConnectionFactory->getHostAddress().c_str()
      << ":"
      << pConnectionFactory->getPort() 
      << ")";

      _canvas->write( 25, 
                      0, 
                      ConsoleColor::BLACK, 
                      ConsoleColor::WHITE, 
                      ss.str().c_str() );

   }


   _canvas->write( minCol-2, 2, "min" );
   _canvas->write(  width-3, 2, "max" );

   _canvas->write(        0, 3, "1"        );
   _canvas->write( minCol-2, 3, "%3d", _min );
   _canvas->write(  width-3, 3, "%3d", _max );

}

void
BPConsoleHostConnectionMonitor::paintDynamicInfo()
{

   int width = _canvas->getWidth();

   int connectionCountCol = (int)(((double)width/(double)_max)*_connectionCount) - 1;
   int connectionsInUseCol = (int)(((double)width/(double)_max)*_connectionsInUse) - 1;
   int minCol = (int)(((double)width/(double)_max)*_min) - 1;

   _canvas->write( 55, 0, "Connection Faults: %4d", _connectionFailures);

   _canvas->write( 0, 4, "%*.*s", width, width, "" );

   _canvas->write(       0, 4, "|" );
   _canvas->write(  minCol, 4, "|" );
   _canvas->write( width-1, 4, "|" );

   if( connectionCountCol >= 2 )
      _canvas->write( connectionCountCol-2,  4, "%3d", _connectionCount  );

   if( connectionsInUseCol >= 2 )
      _canvas->write( connectionsInUseCol-2, 4, "%3d", _connectionsInUse );

   _canvas->highlight( 0, 4,                 width, ConsoleColor::CYAN       , ConsoleColor::BLACK );
   _canvas->highlight( 0, 4,  connectionCountCol+1, ConsoleColor::DARK_GREEN , ConsoleColor::BLACK );
   _canvas->highlight( 0, 4, connectionsInUseCol+1, ConsoleColor::GREEN      , ConsoleColor::BLACK );

}