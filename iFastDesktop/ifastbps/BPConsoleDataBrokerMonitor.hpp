#pragma once

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
//    Copyright 2000 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : BPConsoleHostConnectionMonitor.hpp
// ^AUTHOR : David B. Smith 
// ^DATE   : December 2000
//
// ^CLASS    : BPConsoleHostConnectionMonitor
// ^INHERITS FROM :          
//
// ^CLASS DESCRIPTION : 
//    This class is provides a simple host connection monitor for console applications.
//    
//
//******************************************************************************
#include <win32\platform.h>
#include <bfdbrkr\bfdatabroker.hpp>
#include <bfutil\bfevent.hpp>
#include <bfutil\bfthread.hpp>

class ConsoleCanvas;

class BPConsoleDataBrokerMonitor : public BFThread
{
public:
   BPConsoleDataBrokerMonitor(const int refreshRate=1000);
   virtual ~BPConsoleDataBrokerMonitor();

   virtual bool refresh();

protected:
   virtual void run();

private:

   void paintStaticInfo();
   void paintDynamicInfo();

   const int _refreshRate;
   BFEvent _shutdownEvent;

   ConsoleCanvas *_canvas;

#ifdef _DEBUG
   BFDataBroker::StubMode _stubMode;
#endif

   unsigned int _requestCount;
   unsigned int _conditionCount;
   unsigned int _informationCount;
   unsigned int _warningCount;
   unsigned int _severeErrorCount;
   unsigned int _criticalErrorCount;
};



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   D:/scc/ifds/ifast/archives/ifastbps/BPConsoleDataBrokerMonitor.hpp-arc  $
//
//   Rev 1.3   Oct 09 2002 23:53:46   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.2   21 Mar 2002 15:12:54   PURDYECH
//Removed compile-time "including..." message
//Use #pragma once as include guard
//Include files with lower-case only names
//
//   Rev 1.1   03 Jul 2001 16:53:40   PURDYECH
//Infrastructure Release 1.9 Fixes.
//
//   Rev 1.0   06 Dec 2000 11:48:32   SMITHDAV
//Initial revision.
*/