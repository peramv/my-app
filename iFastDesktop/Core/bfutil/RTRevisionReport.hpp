#pragma once

class RTRevision;

// Import/Export resolution
#undef BFUTIL_LINKAGE
#ifdef BFUTIL_DLL
   #define BFUTIL_LINKAGE CLASS_EXPORT
#else
   #define BFUTIL_LINKAGE CLASS_IMPORT
#endif

class BFUTIL_LINKAGE RTRevisionReport
{
public:
   RTRevisionReport();

   void report();

protected:
   virtual void reportSourceRevision( const RTRevision * const revsion ) = 0;
   virtual void reportHeaderRevision( const RTRevision * const revsion ) = 0;

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/bfutil/RTRevisionReport.hpp-arc  $
//
//   Rev 1.3   Oct 09 2002 17:41:30   PURDYECH
//New PVCS Database
//
//   Rev 1.2   22 Mar 2002 15:12:06   PURDYECH
//Removed compile-time "including..." message
//Use #pragma once as include guard
//Include files with lower-case only names
//
//   Rev 1.1   03 Jul 2001 15:47:52   SMITHDAV
//Re-work
//
//   Rev 1.0   28 Jun 2001 15:10:42   SMITHDAV
//Initial revision.
 */