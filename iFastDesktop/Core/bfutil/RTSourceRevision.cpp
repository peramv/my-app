#include "stdafx.h"

#include "RTSourceRevision.hpp"
#include "RTHeaderRevision.hpp"

RTSourceRevision::SOURCE_REVISION_MAP RTSourceRevision::_sourceRevisionMap;

RTSourceRevision::RTSourceRevision( const char *archiveFile, const char *revision )
: RTRevision(archiveFile, revision),
_headerRevisionMap()
{
   _sourceRevisionMap.insert( SOURCE_REVISION_MAP_VALUE_TYPE(archiveFile, this) );
}

void 
RTSourceRevision::registerHeaderRevision( const char *archiveFile, const char *revision )
{
   _headerRevisionMap.insert( HEADER_REVISION_MAP_VALUE_TYPE(archiveFile, new RTHeaderRevision( *this, archiveFile, revision) ) );
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/bfutil/RTSourceRevision.cpp-arc  $
// 
//    Rev 1.3   Oct 09 2002 17:41:32   PURDYECH
// New PVCS Database
// 
//    Rev 1.2   May 28 2002 12:16:00   PURDYECH
// BFData Implementation - Phase II
// 
//    Rev 1.1   04 Jul 2001 10:39:56   SMITHDAV
// Interim fix. Remove statics.
// 
//    Rev 1.0   28 Jun 2001 15:10:00   SMITHDAV
// Initial revision.
 */