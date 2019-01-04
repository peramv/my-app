#pragma once

#include <bfutil\bfkernel.hpp>
#include <bfutil\bfserialsync.hpp>

// Import/Export resolution
#undef BFUTIL_LINKAGE
#ifdef BFUTIL_DLL
   #define BFUTIL_LINKAGE CLASS_EXPORT
#else
   #define BFUTIL_LINKAGE CLASS_IMPORT
#endif

class BFUTIL_LINKAGE BFMutex : public BFKernel, public BFSerialSync
{
public:
   //creates a BFMutex object
   //the status must be checked after using this constructor
   BFMutex( bool bInitialOwner = false, const char* name = NULL );
   //opens an existing BFMutex
   //the status must be checked after using this constructor
   BFMutex( const char* name );
   virtual ~BFMutex();
   //releases ownership of this mutex object
   void release();

   virtual void leave();
   virtual void enter();
   virtual bool tryEnter();
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/bfutil/BFMutex.hpp-arc  $
//
//   Rev 1.3   Oct 09 2002 17:41:18   PURDYECH
//New PVCS Database
//
//   Rev 1.2   22 Mar 2002 15:11:38   PURDYECH
//Removed compile-time "including..." message
//Use #pragma once as include guard
//Include files with lower-case only names
//
//   Rev 1.1   03 Oct 2001 15:10:00   SMITHDAV
//Syncronization changes and Job Queue changes
//
//   Rev 1.0   Jun 28 2001 09:47:02   PURDYECH
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