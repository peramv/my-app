#ifndef BASEDBSECURITY_HPP
#define BASEDBSECURITY_HPP

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

#pragma message( "including "__FILE__ )

#ifndef COMMONPORT_H
   #include "commonport.h"
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



//************************************************************************
//              Revision Control Entries
//************************************************************************
//
// Name:
//    %PM%
//    %PID%
//
// Description:
//    %PD%
//
// Design Parts:
//    %PIRP%
//
// Last Changed:
//    %PO%  -  %PRT%
//
// Changes:
//    %PLA%
//
//
// $Log:   Y:/VCS/iFastAWD/inc/basedbsecurity.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:30:02   kovacsro
//Initial revision.
//
//   Rev 1.2   Jan 16 2000 14:07:52   dtwk
//Update comments in JavaDoc format
//
//   Rev 1.1   Dec 19 1999 09:28:10   dtwk
//Convert comments to JavaDoc format
//

#endif
