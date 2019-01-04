#pragma once
#if defined(VERBOSE_INCLUDES)
   #pragma message( "including "__FILE__ )
#endif


//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1997 by DST Systems, Inc.
//
//******************************************************************************

#include <commonport.h>

enum E_FIELDPROCESSFLAG
{
   NORMAL = 0,
   SUBCLASS_PROCESS,
   RELAY_TO_PARENT
};


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   //db3n5j11/d/scc/ifds/core/archives/bfproc/AbstractProcessConstants.h-arc  $
 * 
 *    Rev 1.4   Oct 09 2002 17:40:50   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.3   22 Mar 2002 15:11:20   PURDYECH
 * Removed compile-time "including..." message
 * Use #pragma once as include guard
 * Include files with lower-case only names
 * 
 *    Rev 1.2   Nov 08 2000 19:59:14   DT24433
 * removed enum for list processing types
 * 
 *    Rev 1.1   Feb 15 2000 18:54:56   MCNABBGL
 * changed comment format
 * 
 *    Rev 1.0   Feb 15 2000 10:57:44   SMITHDAV
 * Initial revision.
// 
//    Rev 1.0   Dec 07 1999 11:12:06   VASILEAD
// Initial revision.
 * 
 */
