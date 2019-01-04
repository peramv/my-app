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
// ^FILE   : BPConsoleServerMonitor.hpp
// ^AUTHOR : David B. Smith 
// ^DATE   : December 2000
//
// ^CLASS    : BPConsoleServerMonitor
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

class BPConsoleServerMonitor : public BFThread
{
public:
   BPConsoleServerMonitor(const int refreshRate=1000);
   virtual ~BPConsoleServerMonitor();

   virtual bool refresh();

protected:
   virtual void run();

private:

   void paintStaticInfo();
   void paintDynamicInfo();

   void paintThreadMonitor( int startCol, int row, int width );
   void paintJobQueueMonitor( int startCol, int row, int width );

   const int _refreshRate;
   BFEvent _shutdownEvent;

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
/* $Log:   D:/scc/ifds/ifast/archives/ifastbps/BPConsoleServerMonitor.hpp-arc  $
//
//   Rev 1.4   Oct 09 2002 23:53:46   PURDYECH
//PVCS Database Conversion
//
//   Rev 1.3   21 Mar 2002 15:12:54   PURDYECH
//Removed compile-time "including..." message
//Use #pragma once as include guard
//Include files with lower-case only names
//
//   Rev 1.2   03 Oct 2001 15:10:18   SMITHDAV
//Syncronization changes and Job Queue changes
//
//   Rev 1.1   03 Jul 2001 16:53:42   PURDYECH
//Infrastructure Release 1.9 Fixes.
//
//   Rev 1.0   06 Dec 2000 18:28:58   SMITHDAV
//Initial revision.
*/