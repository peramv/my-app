#pragma once

#include <bfutil\bfthreadpool.hpp>
#include <bfutil\bfcritsec.hpp>

// Import/Export resolution
#undef SRVBASE_LINKAGE
#ifdef SRVBASE_DLL
   #define SRVBASE_LINKAGE CLASS_EXPORT
#else
   #define SRVBASE_LINKAGE CLASS_IMPORT
#endif

class BFJobQueue;
class TxnStats;

class SRVBASE_LINKAGE SrvPortal : public BFThread
{
public:
   SrvPortal( const DString &name, BFJobQueue *jobQ, int threadCount );
   virtual ~SrvPortal();

   const DString &getName() const {
      return name_;
   }

   const BFThreadPool *getThreadPool() const { 
      return(threadPool_);
   }

   unsigned int getRequestCount() const ;
   void incrementRequestCount();

   void run();

   virtual void cumeTxnStats( unsigned long msTotal, TxnStats* pTxnStats ) { 
      return;
   }

   virtual void optimizeThreadPool( BFThreadPool *const threadPool ) { 
   }

   // called by Server destructor. Overrider must call base.
   virtual void close() = 0;

   virtual DString getDescription() = 0;
   virtual DStringA getDescriptionA() = 0;


protected:
   virtual bool run( BFThreadPool *const threadPool ) = 0;

private:
   const DString name_;

   BFJobQueue *jobQ_;
   int threadCount_;

   BFThreadPool *threadPool_;

   mutable BFCritSec csRequestCount_;
   unsigned int cRequests_;

};
