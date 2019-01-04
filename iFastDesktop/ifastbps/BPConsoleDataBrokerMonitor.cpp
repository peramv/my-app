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
// ^FILE   :  BPConsoleDataBrokerMonitor.cpp
// ^AUTHOR :  David Smith
// ^DATE   :  December 2000
//
// ----------------------------------------------------------
#include "stdafx.h"

#ifndef SRCPRAG_h
   #include <SrcPrag.h>
#endif
#ifndef BPCONSOLEDATABROKERMONITOR_HPP
   #include "BPConsoleDataBrokerMonitor.hpp"
#endif
#ifndef CONSOLE_HPP
   #include <bfutil\Console.hpp>
#endif
#ifndef CONSOLECANVAS_HPP
   #include <bfutil\ConsoleCanvas.hpp>
#endif

BPConsoleDataBrokerMonitor::BPConsoleDataBrokerMonitor(const int refreshRate)
:  BFThread(),
_refreshRate(refreshRate),
_shutdownEvent(true)
{
   _canvas = Console::getInstance()->createCanvas(5);

   BFDataBroker *dataBroker = BFDataBroker::getInstance();

#ifdef _DEBUG
   _stubMode = dataBroker->getStubMode();;
#endif
   _requestCount = dataBroker->getRequestCount();
   _conditionCount = dataBroker->getConditionCount();
   _informationCount = dataBroker->getInformationCount();
   _warningCount = dataBroker->getWarningCount();
   _severeErrorCount = dataBroker->getSevereErrorCount();
   _criticalErrorCount = dataBroker->getCriticalErrorCount();

   paintStaticInfo();
   paintDynamicInfo();

   _canvas->update();

   start();
}


BPConsoleDataBrokerMonitor::~BPConsoleDataBrokerMonitor()
{
   _shutdownEvent.set(); // signal the poller to shutdown
   wait(INFINITE); // wait for the poller to shutdown

   delete _canvas;

}

bool 
BPConsoleDataBrokerMonitor::refresh()
{

   BFDataBroker *dataBroker = BFDataBroker::getInstance();

   _requestCount = dataBroker->getRequestCount();
   _conditionCount = dataBroker->getConditionCount();
   _informationCount = dataBroker->getInformationCount();
   _warningCount = dataBroker->getWarningCount();
   _severeErrorCount = dataBroker->getSevereErrorCount();
   _criticalErrorCount = dataBroker->getCriticalErrorCount();

   paintDynamicInfo();

   _canvas->update();

   return(true);
}

void
BPConsoleDataBrokerMonitor::paintStaticInfo()
{

//   int width = _canvas->getWidth();

#ifdef _DEBUG
   if( BFDataBroker::OFF != _stubMode )
      _canvas->write( 0, 
                      0, 
                      ConsoleColor::BLACK, 
                      ConsoleColor::BRIGHT_WHITE,
                      "Data Broker Monitor: %s", 
                      BFDataBroker::OFFLINE == _stubMode?"OFFLINE":"COLLECT MODE" );
   else
#endif
      _canvas->write( 0, 0, ConsoleColor::BLACK, ConsoleColor::BRIGHT_WHITE, "Data Broker Monitor" );

}

void
BPConsoleDataBrokerMonitor::paintDynamicInfo()
{

   _canvas->write(5, 2, "Total Requests: %6d", _requestCount);

   _canvas->write(29, 0, "Host Conditions --   Informational : %6d", _informationCount);
   _canvas->write(29, 1, "                          Warnings : %6d", _warningCount);
   _canvas->write(29, 2, "                     Severe Errors : %6d", _severeErrorCount);
   _canvas->write(29, 3, "                   Critical Errors : %6d", _criticalErrorCount);
   _canvas->write(29, 4, "                             Total : %6d", _conditionCount);

}

void
BPConsoleDataBrokerMonitor::run()
{
   while( !_shutdownEvent.wait(_refreshRate) )
   {
      refresh();
   }
}