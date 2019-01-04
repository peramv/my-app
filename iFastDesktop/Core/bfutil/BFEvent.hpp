#pragma once

#include <bfutil\bfkernel.hpp>

// Import/Export resolution
#undef BFUTIL_LINKAGE
#ifdef BFUTIL_DLL
   #define BFUTIL_LINKAGE CLASS_EXPORT
#else
   #define BFUTIL_LINKAGE CLASS_IMPORT
#endif

class BFUTIL_LINKAGE BFEvent : public BFKernel
{
public:
   //creates a BFEvent object
   //by default this is a auto reset event, initially non-signaled
   BFEvent( bool bManualReset = false, bool bInitialState = false, const char* name = NULL );
   //opens an existing BFEvent
   BFEvent( const char* name );
   virtual ~BFEvent();
   //sets the state of this event object to be signaled
   //any number of waiting threads, or threads that subsequently begin wait operations for 
   //this event object by calling one of the wait functions, 
   //can be released while the object's state is signaled
   void set();
   //sets the state of this event object to nonsignaled
   //this nonsignaled state blocks the execution of any threads that 
   //have specified the event object in a call to one of the wait functions
   void reset();
   //provides a single operation that sets (to signaled) the state of this 
   //event object and then resets it (to nonsignaled) after releasing 
   //the appropriate number of waiting threads
   void pulse();
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/bfutil/BFEvent.hpp-arc  $
//
//   Rev 1.2   Oct 09 2002 17:41:10   PURDYECH
//New PVCS Database
//
//   Rev 1.1   03 Oct 2001 15:10:00   SMITHDAV
//Syncronization changes and Job Queue changes
//
//   Rev 1.0   Jun 28 2001 09:46:58   PURDYECH
//Initial revision.
//
//   Rev 1.0   Jun 26 2001 12:03:52   PURDYECH
//Initial revision.
 * 
 *    Rev 1.2   Feb 16 2000 13:09:44   POPESCUS
 * Initial revision
 * 
 * 
 */