#pragma once

class BFWaitableSet;

// Import/Export resolution
#undef BFUTIL_LINKAGE
#ifdef BFUTIL_DLL
   #define BFUTIL_LINKAGE CLASS_EXPORT
#else
   #define BFUTIL_LINKAGE CLASS_IMPORT
#endif

//base class for the MT objects in this DLL
class BFUTIL_LINKAGE BFKernel
{
public:
   friend BFWaitableSet;

   BFKernel();
   virtual ~BFKernel();
   //Waits on the current BFKernel object
   bool wait( DWORD dwMilliSeconds = INFINITE );

   bool operator==( BFKernel &other ) { return(_handle == other._handle);}

protected:
   HANDLE   _handle;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/bfutil/BFKernel.hpp-arc  $
//
//   Rev 1.2   Oct 09 2002 17:41:18   PURDYECH
//New PVCS Database
//
//   Rev 1.1   03 Oct 2001 15:10:00   SMITHDAV
//Syncronization changes and Job Queue changes
//
//   Rev 1.0   Jun 28 2001 09:47:00   PURDYECH
//Initial revision.
//
//   Rev 1.0   Jun 26 2001 12:03:50   PURDYECH
//Initial revision.
 * 
 *    Rev 1.2   Feb 16 2000 13:09:38   POPESCUS
 * Initial revision
 * 
 * 
 */