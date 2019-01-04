#include "stdafx.h"

#include "RTRevisionReport.hpp"
#include "RTSourceRevision.hpp"
#include "RTHeaderRevision.hpp"

RTRevisionReport::RTRevisionReport()
{
}

void 
RTRevisionReport::report()
{

   RTSourceRevision::SOURCE_REVISION_MAP_ITER sourceIterator = RTSourceRevision::_sourceRevisionMap.begin();

   while( sourceIterator != RTSourceRevision::_sourceRevisionMap.end() )
   {
      const RTSourceRevision * const sourceRevsion = (*sourceIterator).second;
      this->reportSourceRevision( sourceRevsion );

      RTSourceRevision::HEADER_REVISION_MAP_CONST_ITER headerIterator = sourceRevsion->_headerRevisionMap.begin();
      while( headerIterator != sourceRevsion->_headerRevisionMap.begin() )
      {
         const RTHeaderRevision * const headerRevsion = (*headerIterator).second;
         this->reportHeaderRevision( headerRevsion );
         headerIterator++;
      }
      sourceIterator++;
   }

}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/bfutil/RTRevisionReport.cpp-arc  $
//
//   Rev 1.5   Oct 22 2004 09:01:06   PURDYECH
//PET910 - .NET Conversion Fixes
// 
//    Rev 1.4   Oct 09 2002 17:41:30   PURDYECH
// New PVCS Database
// 
//    Rev 1.3   May 28 2002 12:16:00   PURDYECH
// BFData Implementation - Phase II
// 
//    Rev 1.2   04 Jul 2001 10:39:56   SMITHDAV
// Interim fix. Remove statics.
// 
//    Rev 1.1   03 Jul 2001 15:47:50   SMITHDAV
// Re-work
// 
//    Rev 1.0   28 Jun 2001 15:10:00   SMITHDAV
// Initial revision.
 */