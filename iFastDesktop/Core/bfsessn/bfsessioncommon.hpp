#pragma once
/*
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1996-2000 by DST Systems, Inc.
 */

#include <conditionmanager.hpp>
#include <bfsessn\bfsessn.h>
#include <base.h>

//
//  This macro will assert that a pointer has been allocated memory (not NULL).
//
#define ASSERT_NEW( pointer, method ) \
       do { if ( ! pointer ) { THROWFROMBASE( DISESSN_CONDITION, method, BASE_ALLOC_FAIL ); } } while(false)



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   //db3n5j11/d/scc/ifds/core/archives/bfsessn/bfsessioncommon.hpp-arc  $
//
//   Rev 1.1   Oct 09 2002 17:41:04   PURDYECH
//New PVCS Database
//
//   Rev 1.0   28 May 2002 12:11:12   SMITHDAV
//Initial revision.
// 
//    Rev 1.3   14 Dec 2000 13:20:44   dt14177
// cleanup
// 
//    Rev 1.2   Jul 22 1999 10:21:14   DMUM
// Condition re-work
// 
//    Rev 1.1   Apr 09 1999 13:30:00   DMUM
// Sync up with 1.6.x
//
//    Rev 1.0.1.0   Mar 31 1999 13:16:54   DMUM
//
//
//    Rev 1.0   Feb 08 1999 15:05:26   DMUM
//
//
//

