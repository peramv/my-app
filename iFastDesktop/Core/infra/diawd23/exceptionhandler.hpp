#ifndef EXCEPTIONHANDLER_HPP
#define EXCEPTIONHANDLER_HPP

#pragma message( "including "__FILE__ )

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

#ifndef SOMINC_H
   #error include 'sominc.h' before including this file
#endif

#ifndef CONDITIONMANAGER_HPP
   #include "conditionmanager.hpp"
#endif
#ifndef DIAWDCND_H
   #include "diawdcnd.h"
#endif
#ifndef BASE_H
   #include "base.h"
#endif

void ConvertAwdExceptionToConditionException( AWDException *pExc,
                                              const I_CHAR *className,
                                              const I_CHAR *methodName,
                                              const char *fileName,
                                              unsigned lineNumber );

//******************************************************************************
//
//  This macro will catch an AWDException, re-package it
//  as a ConditionException and re-throw it.
//
    #define AWD_EXCEPTION_TO_CONDITION_EXCEPTION( className, methodName )     \
       catch ( AWDException *pExc )                                           \
       {                                                                      \
          ConvertAwdExceptionToConditionException( pExc,                      \
                                                   className,                 \
                                                   methodName,                \
                                                   __FILE__,                  \
                                                   __LINE__ );                \
       }                                                                      \
       catch ( ConditionException &ce )                                       \
       {                                                                      \
          throw ce;                                                           \
       }                                                                      \
       catch ( ... )                                                          \
       {                                                                      \
          DString strMethod( className );                                     \
          strMethod += I_( "::" );                                            \
          strMethod += methodName;                                            \
          THROWFROMFILE( DIAWD23_CONDITION,                                     \
                         strMethod,                                           \
                         DIAWD23_UNKNOWN_AWD_EXCEPTION );                     \
       }

//
//  This macro will assert that a pointer has been allocated memory (not NULL).
//
    #define ASSERT_NEW( pointer, className, methodName )                      \
       if ( ! pointer )                                                       \
       {                                                                      \
          DString strMethod( className );                                     \
          strMethod += I_( "::" );                                            \
          strMethod += methodName;                                            \
          THROWFROMBASE( DIAWD23_CONDITION,                                     \
                         strMethod,                                           \
                         BASE_ALLOC_FAIL );                                   \
       }
//
//******************************************************************************



//******************************************************************************
//              Revision Control Entries
//******************************************************************************
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
// $Log:   Y:/VCS/iFastAWD/diawd23/exceptionhandler.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:16:48   kovacsro
//Initial revision.
// 
//    Rev 1.3   07 Dec 2000 09:34:18   dt14177
// cleanup
// 
//    Rev 1.2   Jul 22 1999 10:18:24   DMUM
// Condition re-work
// 
//    Rev 1.1   Apr 09 1999 13:50:44   DMUM
// Sync up with 1.6.x
//
//    Rev 1.0.1.0   Mar 31 1999 13:21:00   DMUM
// Sync up with Infra 1.6.x
//
//    Rev 1.0   Jan 20 1999 09:39:58   DMUM
//
//

#endif // EXCEPTIONHANDLER_HPP

