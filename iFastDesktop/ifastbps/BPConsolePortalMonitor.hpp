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
// ^FILE   : BPConsolePortalMonitor.hpp
// ^AUTHOR : David B. Smith 
// ^DATE   : December 2000
//
// ^CLASS    : BPConsolePortalMonitor
// ^INHERITS FROM :          
//
// ^CLASS DESCRIPTION : 
//    This class is provides a simple server portal monitor for console applications.
//    
//
//******************************************************************************
#include <win32\platform.h>
#include <bfdbrkr\bfdatabroker.hpp>
#include <bfutil\bfevent.hpp>
#include <bfutil\bfthread.hpp>

class ConsoleCanvas;
class SrvPortal;

class BPConsolePortalMonitor : public BFThread
{
public:
   BPConsolePortalMonitor( const DString& portalName, int refreshRate=1000);
   virtual ~BPConsolePortalMonitor();

   virtual bool refresh();

protected:
   virtual void run();

private:

   SrvPortal *getPortal();

   void paintStaticInfo();
   void paintDynamicInfo();

   void paintThreadMonitor( int row);
   void paintJobQueueMonitor( int row );

   const DString _portalName;
   const int _refreshRate;

   BFEvent _shutdownEvent;

   unsigned int _requestCount;
   int _threadCount;
   int _threadsInUse;
   int _maxJobs;
   int _currentJobs;

   ConsoleCanvas *_canvas;

};



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbps/BPConsolePortalMonitor.hpp-arc  $
//
//   Rev 1.1   Feb 03 2005 13:25:04   smithdav
//Minor console tweaks.
//
//   Rev 1.0   Jan 27 2005 16:35:28   smithdav
//Initial revision.
//
*/