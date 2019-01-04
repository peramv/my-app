#pragma once
#include <boost/thread/recursive_mutex.hpp>

// Thin wrapper around Boost mutex
typedef boost::recursive_mutex BFCritSec;

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/bfutil/BFCritSec.hpp-arc  $
//
//   Rev 1.4   Mar 11 2003 10:16:56   PURDYECH
//BFCritSec is now an alias for boost::mutex
//
//   Rev 1.3   Oct 09 2002 17:41:10   PURDYECH
//New PVCS Database
//
//   Rev 1.2   Feb 25 2002 18:52:24   PURDYECH
//Phase 1 of BFData Rollout - Base Component Compatibility
//
//   Rev 1.1   03 Oct 2001 15:09:58   SMITHDAV
//Syncronization changes and Job Queue changes
//
//   Rev 1.0   Jun 28 2001 09:46:58   PURDYECH
//Initial revision.
//
//   Rev 1.0   Jun 26 2001 12:03:52   PURDYECH
//Initial revision.
 * 
 *    Rev 1.2   Feb 16 2000 13:10:28   POPESCUS
 * Initial revision
 * 
 * 
 */