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
// ^FILE   :  AsyncRequestor.cpp
// ^AUTHOR :  David Smith
// ^DATE   :  September 2000
//
// ----------------------------------------------------------
#include <SrcPrag.h>
#include "AsyncRequestor.hpp"
#include "AsyncRequestListener.hpp"
#include <ConditionManager.hpp>
#include <bfdata\bfdata.hpp>

#include <bfutil\BFExecutionContext.hpp>

namespace
{
   const I_CHAR *const CLASSNAME = I_( "AsyncRequestor" );
   const I_CHAR *const RECEIVE = I_( "receive" );
   const I_CHAR *const RUN = I_( "run" );
}

namespace CND
{
   extern const I_CHAR *BFDBRKR_CONDITION;
}

//******************************************************************************
AsyncRequestor::AsyncRequestor(const BFRequestor &baseRequestor, AsyncRequestListener *listener, int callBackOption)
: BFThread()
, _baseRequestor(NULL)
, _listener(listener)
, _startedSemaphore(1, 1)
, _request(NULL)
, queryBFData_(NULL)
, receivedBFData_(NULL)
, _callBackOption(callBackOption)
, _tidCaller( DSTGetCurrentThreadId() )

{
   assert(_listener);
   _baseRequestor = baseRequestor.clone();   
}

//******************************************************************************
AsyncRequestor::AsyncRequestor(BFRequestor *baseRequestor, AsyncRequestListener *listener, int callBackOption)
: BFThread()
, _baseRequestor(baseRequestor)
, _listener(listener)
, _startedSemaphore(1, 1)
, _request(NULL)
, queryBFData_(NULL)
, receivedBFData_(NULL)
, _callBackOption(callBackOption)
, _tidCaller( DSTGetCurrentThreadId() )

{
   assert(_listener);
}

//******************************************************************************
AsyncRequestor::~AsyncRequestor()
{
   // grab the started semaphore so no one can start.
   _startedSemaphore.wait(0);

   // wait for the thread to exit.
   wait(INFINITE);
   delete _baseRequestor;
}


//******************************************************************************
SEVERITY 
AsyncRequestor::receive( const BFRequest &request, 
                         BFData &queryData, 
                         BFData &receivedData, 
                         bool *outMoreAvailable /*= NULL*/ )
{

   // ensure this method is only executed onces.
   if( !_startedSemaphore.wait(0) )
   {
      assert(0);
      throw;
   }

   _request        = &request;
   queryBFData_    = new BFData(queryData);  // copy the request data so caller does not have to keep his copy around
   receivedBFData_ = &receivedData;

   // outMoreAvailable is not used in this context.
   // the observer is notified of this information...

   start();

   // never more records avaialable for sysload
   if( NULL != outMoreAvailable )
      outMoreAvailable = false;

   return(NO_CONDITION);
}

void
AsyncRequestor::run()
{
   MAKEFRAMEAUTOPROMOTE2( CND::BFDBRKR_CONDITION, CLASSNAME, RUN );

   // make this thread run with the context of its caller.
   // the thread will automatically detach when it terminates.
   BFExecutionContext::attach( _tidCaller );

   // Give this thread a name based on the calling thread's ID
   char szThreadName[ 12 ];
   sprintf( szThreadName, "Async%04.4X", _tidCaller );
   bfutil::setThreadName( -1, szThreadName );

   bool moreAvailable;
   Condition *condition = NULL;

   SEVERITY severity;
   severity = _baseRequestor->receive(*_request, *queryBFData_, *receivedBFData_, &moreAvailable);

   if( NO_CONDITION != severity )
   {
      condition = GETCONDITION( 0 );
   }

   _listener->notifyResponse(severity, condition, receivedBFData_, moreAvailable, _callBackOption);

   delete _baseRequestor;
   _baseRequestor = NULL;
   delete queryBFData_;
   queryBFData_ = NULL;
}
