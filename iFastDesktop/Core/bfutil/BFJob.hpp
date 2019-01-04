
#pragma once

// Import/Export resolution
#undef BFUTIL_LINKAGE
#ifdef BFUTIL_DLL
   #define BFUTIL_LINKAGE CLASS_EXPORT
#else
   #define BFUTIL_LINKAGE CLASS_IMPORT
#endif

//interface used to define a BFJob
class BFUTIL_LINKAGE BFJob
{
public:

   virtual ~BFJob() {};
   // Override to provide functionality when invoked to run
   virtual void run() = 0;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/bfutil/BFJob.hpp-arc  $
//
//   Rev 1.2   Oct 09 2002 17:41:16   PURDYECH
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
 *    Rev 1.3   Aug 23 2000 11:00:40   DT24433
 * Added run interface method
 * 
 *    Rev 1.2   Feb 16 2000 13:09:30   POPESCUS
 * Initial revision
 * 
 * 
 */