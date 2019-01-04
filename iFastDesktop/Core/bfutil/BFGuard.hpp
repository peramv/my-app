#pragma once
#include <boost/thread/recursive_mutex.hpp>

// BFGuard is an alias for boost::scoped_lock
typedef boost::recursive_mutex::scoped_lock BFGuard;



//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF Core/bfutil/BFGuard.hpp-arc  $
//
//   Rev 1.2   Mar 11 2003 10:21:00   PURDYECH
//BFGuard is now an alias for boost::scoped_lock
//
