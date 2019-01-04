#pragma once

class BFKernel;

// Import/Export resolution
#undef BFUTIL_LINKAGE
#ifdef BFUTIL_DLL
   #define BFUTIL_LINKAGE CLASS_EXPORT
#else
   #define BFUTIL_LINKAGE CLASS_IMPORT
#endif

//this is a helper class used to 
//wait on multiple kernel objects
//it wraps the ::WaitForMultipleObjects method
//the maximum number of objects that a thread can wait on
//is defined by the constant: MAXIMUM_WAIT_OBJECTS
class BFUTIL_LINKAGE BFWaitableSet 
{
public:
   BFWaitableSet( BFKernel* waitObjects[], int objectCount );
   ~BFWaitableSet();

   bool wait( BFKernel *&waitObjectResult, DWORD timeout = INFINITE );
   bool waitAll( DWORD timeout = INFINITE );

private:
   BFKernel** _waitObjects;
   HANDLE*    _waitObjectsHandles;
   int        _objectCount;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/bfutil/BFWaitableSet.hpp-arc  $
//
//   Rev 1.2   Oct 09 2002 17:41:24   PURDYECH
//New PVCS Database
//
//   Rev 1.1   03 Oct 2001 15:10:02   SMITHDAV
//Syncronization changes and Job Queue changes
//
//   Rev 1.0   Jun 28 2001 09:47:18   PURDYECH
//Initial revision.
//
//   Rev 1.0   Jun 26 2001 12:03:54   PURDYECH
//Initial revision.
 * 
 *    Rev 1.2   Feb 16 2000 13:09:44   POPESCUS
 * Initial revision
 * 
 * 
 */