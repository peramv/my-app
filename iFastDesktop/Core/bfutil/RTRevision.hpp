#pragma once

// Import/Export resolution
#undef BFUTIL_LINKAGE
#ifdef BFUTIL_DLL
   #define BFUTIL_LINKAGE CLASS_EXPORT
#else
   #define BFUTIL_LINKAGE CLASS_IMPORT
#endif

class BFUTIL_LINKAGE RTRevision
{
public:
   RTRevision( const char *archiveFile, const char *revision );

   const char *getArchiveFile() const;
   const char *getRevision() const;

private:
   const char * const _archiveFile;
   const char * const _revision;

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/bfutil/RTRevision.hpp-arc  $
//
//   Rev 1.2   Oct 09 2002 17:41:30   PURDYECH
//New PVCS Database
//
//   Rev 1.1   22 Mar 2002 15:12:04   PURDYECH
//Removed compile-time "including..." message
//Use #pragma once as include guard
//Include files with lower-case only names
//
//   Rev 1.0   28 Jun 2001 15:10:40   SMITHDAV
//Initial revision.
 */