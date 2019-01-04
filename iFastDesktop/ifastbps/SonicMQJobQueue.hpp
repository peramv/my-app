#pragma once
#include <bfutil\bfjobqueue.hpp>

#include <progress/message/jclient/package.h>

class SonicMQPortal;

class SonicMQJobQueue : public BFJobQueue
{
public:
   SonicMQJobQueue( SonicMQPortal *portal );
   virtual ~SonicMQJobQueue();

   virtual int getMaxJobsQueued() const { return 0; } // unknown
   virtual int getCurrentJobsQueued() const { return 0; } //unknown

   virtual bool pushJob( BFJob *job, DWORD timeout = INFINITE ) {return false;} // not supported.
   virtual bool popJob( BFJob *&job, DWORD timeout = INFINITE );

   virtual void close();
   virtual bool isClosed();

private:

   SonicMQPortal *portal_;

   // close sync objects
   BFCritSec _closeCritSec; 
   BFEvent _closedEvent;


};
