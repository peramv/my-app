#pragma once
#include <bfutil\bfjob.hpp>
#include <bfutil\bfhrtimer.hpp>

// Import/Export resolution
#undef SRVBASE_LINKAGE
#ifdef SRVBASE_DLL
   #define SRVBASE_LINKAGE CLASS_EXPORT
#else
   #define SRVBASE_LINKAGE CLASS_IMPORT
#endif

namespace xp{
   class ExecutionResult;
}
class SrvPortal;

class SRVBASE_LINKAGE SrvJob : public BFJob
{
public:
   SrvJob(SrvPortal* portal);
   virtual ~SrvJob();

   virtual void run();
   const BFHRTimer& getStartTime() const { return(acceptStartTime_);}
   unsigned int getJobId() const { return idJob_; }

protected:
   virtual void readRequest( DStringA &buffer ) = 0;
   virtual void writeResponse( const DStringA &buffer, const xp::ExecutionResult &result ) = 0;

private:
   static BFCritSec s_csJobId_;
   static unsigned int s_idNextJob_;
   static unsigned int getNextJobId();

   SrvPortal *portal_;
   bool bTrace_;
   const unsigned int idJob_;
   BFHRTimer acceptStartTime_;

};
