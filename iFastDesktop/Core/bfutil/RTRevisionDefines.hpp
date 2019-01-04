#pragma once

#define CLASS_EXPORT _declspec( dllexport )
#define CLASS_IMPORT _declspec( dllimport )

#include <bfutil\rtsourcerevision.hpp>
#include <bfutil\rtheaderrevision.hpp>

#ifdef _RT_HEADER
   #define _RT_SOURCE
#endif

#ifdef _RT_SOURCE
   #define RT_SOURCE_REVISION( archive, revision ) static RTSourceRevision _g_sourceRevision( archive, revision );  
#else
   #define RT_SOURCE_REVISION( archive, revision )  
#endif

#ifdef _RT_HEADER
   #define RT_HEADER_REVISION( id, archive, revision ) static RTHeaderRevision id( _g_sourceRevision, archive, revision );
#else
   #define RT_HEADER_REVISION( id, archive, revision )
#endif

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/bfutil/RTRevisionDefines.hpp-arc  $
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
//   Rev 1.0   28 Jun 2001 15:10:40   SMITHDAV
//Initial revision.
 */