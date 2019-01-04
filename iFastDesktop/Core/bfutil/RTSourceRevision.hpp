#pragma once
#pragma warning( disable : 4503 4786 4251 )

#include <bfutil\rtrevision.hpp>
#include <map>

class RTHeaderRevision;
class RTRevisionReport;

// Import/Export resolution
#undef BFUTIL_LINKAGE
#ifdef BFUTIL_DLL
   #define BFUTIL_LINKAGE CLASS_EXPORT
#else
   #define BFUTIL_LINKAGE CLASS_IMPORT
#endif


class BFUTIL_LINKAGE RTSourceRevision : public RTRevision
{
public:
   RTSourceRevision( const char *archiveFile, const char *revision );

   void registerHeaderRevision( const char *archiveFile, const char *revision );
private:

   typedef std::map< const char *, const RTHeaderRevision *> HEADER_REVISION_MAP;
   typedef HEADER_REVISION_MAP::iterator         HEADER_REVISION_MAP_ITER;
#if _MSC_VER >= 1300
   typedef HEADER_REVISION_MAP::const_iterator   HEADER_REVISION_MAP_CONST_ITER;
#else
   typedef HEADER_REVISION_MAP::iterator         HEADER_REVISION_MAP_CONST_ITER;
#endif
   typedef HEADER_REVISION_MAP::value_type       HEADER_REVISION_MAP_VALUE_TYPE;

   HEADER_REVISION_MAP _headerRevisionMap;

   typedef std::map< const char *, const RTSourceRevision *> SOURCE_REVISION_MAP;
   typedef SOURCE_REVISION_MAP::iterator         SOURCE_REVISION_MAP_ITER;
#if _MSC_VER >= 1300
   typedef SOURCE_REVISION_MAP::const_iterator   SOURCE_REVISION_MAP_CONST_ITER;
#else
   typedef SOURCE_REVISION_MAP::iterator         SOURCE_REVISION_MAP_CONST_ITER;
#endif
   typedef SOURCE_REVISION_MAP::value_type       SOURCE_REVISION_MAP_VALUE_TYPE;

   static SOURCE_REVISION_MAP _sourceRevisionMap;

   friend class RTRevisionReport;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/bfutil/RTSourceRevision.hpp-arc  $
//
//   Rev 1.4   Oct 09 2002 17:41:32   PURDYECH
//New PVCS Database
//
//   Rev 1.3   22 May 2002 18:09:02   PURDYECH
//BFData Implementation
//
//   Rev 1.2   22 Mar 2002 15:12:06   PURDYECH
//Removed compile-time "including..." message
//Use #pragma once as include guard
//Include files with lower-case only names
//
//   Rev 1.1   04 Jul 2001 10:39:08   SMITHDAV
//Interim fix.
//
//   Rev 1.0   28 Jun 2001 15:10:42   SMITHDAV
//Initial revision.
 */