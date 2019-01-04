#pragma once

/** 
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1999 by DST Systems, Inc.
 */

/**@pkg DIDBRKR */ 


#ifndef COMMONPORT_H
   #include <commonport.h>
#endif


#undef DIDBRKR_LINKAGE
#ifdef DIDBRKR_DLL
   #define DIDBRKR_LINKAGE CLASS_EXPORT
#else
   #define DIDBRKR_LINKAGE CLASS_IMPORT
#endif


/**
 * Used to implement a polymorphic interface for DataBrokers. This is currently
 * little more than a void pointer.
 * 
 * @author DST Systems Inc
 */
class DIDBRKR_LINKAGE BaseDBSecurity
{
};



/*******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   //db3n5j11/d/scc/ifds/core/archives/ifdscore/basedbsecurity.hpp-arc  $
//
//   Rev 1.1   Oct 09 2002 17:41:44   PURDYECH
//New PVCS Database
//
//   Rev 1.0   Jul 05 2002 10:14:34   SMITHDAV
//Initial revision.
//
//   Rev 1.2   Jan 16 2000 14:07:52   dtwk
//Update comments in JavaDoc format
//
//   Rev 1.1   Dec 19 1999 09:28:10   dtwk
//Convert comments to JavaDoc format
//
*/

