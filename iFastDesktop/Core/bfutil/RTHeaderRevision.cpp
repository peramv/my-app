#include "stdafx.h"

#include "RTSourceRevision.hpp"
#include "RTHeaderRevision.hpp"

RTHeaderRevision::RTHeaderRevision( RTSourceRevision &sourceRevision, const char *archiveFile, const char *revision )
: RTRevision(archiveFile, revision),
_sourceRevision(sourceRevision)
{
}

const RTSourceRevision & 
RTHeaderRevision::getSourceRevision() const
{
   return(_sourceRevision);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/bfutil/RTHeaderRevision.cpp-arc  $
// 
//    Rev 1.3   Oct 09 2002 17:41:28   PURDYECH
// New PVCS Database
// 
//    Rev 1.2   May 28 2002 12:16:00   PURDYECH
// BFData Implementation - Phase II
// 
//    Rev 1.1   04 Jul 2001 10:39:54   SMITHDAV
// Interim fix. Remove statics.
// 
//    Rev 1.0   28 Jun 2001 15:10:00   SMITHDAV
// Initial revision.
 */