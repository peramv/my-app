#ifndef DITESTFUNCTIONS_H
#define DITESTFUNCTIONS_H

#pragma message( "including "__FILE__ )

/** 
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

/**@pkg DITEST */    

#ifndef DSTRING_HPP
   #include "dstring.hpp"
#endif

#ifndef COMMONPORT_H
   #include "commonport.h"
#endif

#ifndef CONFIGMANAGER_HPP
   class ConfigManager;
#endif

#ifndef CONDITION_HPP
   class Condition;
#endif

#ifndef CONDITIONEXCEPTION_HPP
   class ConditionException;
#endif

#ifndef MUTEXSEMAPHORE_HPP
   class MutexSemaphore;
#endif

#undef DITEST_LINKAGE
#ifdef DITEST_DLL
   #define DITEST_LINKAGE CLASS_EXPORT
#else
   #define DITEST_LINKAGE CLASS_IMPORT
#endif

DITEST_LINKAGE bool fnGetPassword( DString &password, bool upper = false );

DITEST_LINKAGE bool fnGetLine( DString &line );

DITEST_LINKAGE bool fnSelectProfileGroup( ConfigManager *pManager );

DITEST_LINKAGE void fnWalkTheProcess();

DITEST_LINKAGE void streamCondition( std::ostream &ostr, Condition &c );

DITEST_LINKAGE void standardErrorOut( const ConditionException &ce,
                                      MutexSemaphore &mutex );

DITEST_LINKAGE void standardErrorOut( const ConditionException &ce );

DITEST_LINKAGE void unknownErrorOut( MutexSemaphore &mutex );

DITEST_LINKAGE void unknownErrorOut();

#endif // DITESTFUNCTIONS_H

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
// $Log:   Y:/VCS/iFastAWD/inc/ditestfunctions.h-arc  $
//
//   Rev 1.0   28 Jan 2008 13:31:22   kovacsro
//Initial revision.
// 
//    Rev 1.10   23 Oct 2000 17:25:36   dt14177
// cleanup
// 
//    Rev 1.9   28 Aug 2000 17:34:48   dt20842
// Condition getters const again
// 
//    Rev 1.8   Aug 24 2000 09:51:12   dtwk
// Condition getters are no longer const
// 
//    Rev 1.7   Mar 23 2000 11:04:44   DMUM
// Sync up 1.7 and 1.9
//
//    Rev 1.6   Mar 08 2000 14:39:34   DMUM
// TestCount more robust.  Ported TestData from 1.7
//
//    Rev 1.5   May 20 1999 16:51:44   DMUM
// Added fnWalkTheProcess()
//
//    Rev 1.4   Apr 09 1999 13:16:44   DMUM
// Changed DStringA to DString
//
//    Rev 1.3   Mar 09 1999 12:58:56   DT20842
// Changes for internationalization
//
//    Rev 1.2   22 Feb 1999 11:42:20   DT14177
// UNICODE and DString stuff
//
//    Rev 1.1   Jan 28 1999 14:06:24   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.0   Dec 09 1998 13:41:56   DMUM
// Check in for DICORE
//

