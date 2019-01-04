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
#include <bfconmgr\bfhostconnectionmonitor.hpp>

class BFHostConnectionManager;
class ConsoleCanvas;

class BPConsoleHostConnectionMonitor : public BFHostConnectionMonitor
{
public:
   BPConsoleHostConnectionMonitor(const BFHostConnectionManager *hostConnectionManager);
   virtual ~BPConsoleHostConnectionMonitor();

   virtual bool refresh();

private:

   void paintStaticInfo();
   void paintDynamicInfo();

   ConsoleCanvas *_canvas;
   const BFHostConnectionManager *_hostConnectionManager;

   int _max;
   int _min;
   int _connectionCount;
   int _connectionsInUse;
   int _connectionFailures;
};



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   D:/scc/ifds/ifast/archives/ifastbps/BPConsoleHostConnectionMonitor.hpp-arc  $
//
//   Rev 1.2   Oct 09 2002 23:53:46   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.1   21 Mar 2002 15:12:54   PURDYECH
//Removed compile-time "including..." message
//Use #pragma once as include guard
//Include files with lower-case only names
//
//   Rev 1.0   06 Dec 2000 11:50:18   SMITHDAV
//Initial revision.
*/