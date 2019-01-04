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
// ^FILE   : ConsoleConnectionMonitor.hpp
// ^AUTHOR : David B. Smith 
// ^DATE   : December 2000
//
// ^CLASS    : BPConsoleConnectionMonitor
// ^INHERITS FROM :          
//
// ^CLASS DESCRIPTION : 
//    This class is provides a simple connection monitor for console applications.
//    
//
//******************************************************************************
#include <win32\platform.h>
#include <bfconmgr\bfabstractconnectionmonitor.hpp>

class BFHostConnectionManager;
class BFHostConnectionMonitor;

class BPConsoleConnectionMonitor : public BFAbstractConnectionMonitor
{
public:
   BPConsoleConnectionMonitor(const int refreshRate=1000);
   virtual ~BPConsoleConnectionMonitor();

   virtual BFHostConnectionMonitor *createHostConnectionMonitor(const BFHostConnectionManager *hostConnectionManager);

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   D:/scc/ifds/ifast/archives/ifastbps/BPConsoleConnectionMonitor.hpp-arc  $
//
//   Rev 1.4   Oct 09 2002 23:53:44   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.3   21 Mar 2002 15:12:52   PURDYECH
//Removed compile-time "including..." message
//Use #pragma once as include guard
//Include files with lower-case only names
//
//   Rev 1.2   17 Jun 2001 17:40:54   PURDYECH
//A few more changes for EFAN_REL_12.0 integration with Infrastructure Release 1.9
//
//   Rev 1.1   06 Dec 2000 11:47:44   SMITHDAV
//Update monitoring console; Added DataBroker monitor.
//
//   Rev 1.0   04 Dec 2000 11:40:28   SMITHDAV
//Initial revision.
// 
*/