#pragma once

#include <bfutil\bfkernel.hpp>

// Import/Export resolution
#undef BFUTIL_LINKAGE
#ifdef BFUTIL_DLL
   #define BFUTIL_LINKAGE CLASS_EXPORT
#else
   #define BFUTIL_LINKAGE CLASS_IMPORT
#endif

class BFUTIL_LINKAGE BFSemaphore : public BFKernel
{
public:
   //creates a BFSemaphore object
   BFSemaphore( int nInitialCount, int nMaximumCount, const char* name = NULL );

   //opens an existing BFSemaphore
   BFSemaphore( const char* name );

   virtual ~BFSemaphore();

   //increases the count of this semaphore object by the specified amount
   void  release( long lReleaseCount, long *plPreviousCount = NULL );
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/bfutil/BFSemaphore.hpp-arc  $
//
//   Rev 1.2   Oct 09 2002 17:41:20   PURDYECH
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