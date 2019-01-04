#ifndef TESTCOMPONENT_H
#define TESTCOMPONENT_H

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

/**@pkg DITEST */    

#define DITEST_DLL

#undef DITEST_LINKAGE
#ifdef DITEST_DLL
   #define DITEST_LINKAGE CLASS_EXPORT
#else
   #define DITEST_LINKAGE CLASS_IMPORT
#endif

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif

#ifndef COMMONPORT_H
#   include "commonport.h"
#endif


#ifndef DSTRINGA_HPP
#  include "dstringa.hpp"
#endif

/**
* This method initializes the debug assert handlers
*
* @param     I_CHAR * - the process logfile name
* @returns   void
* @exception none
*/
void DITEST_LINKAGE initSetReport( char * myfile );

//void DITEST_LINKAGE reportResult( bool result );
//void DITEST_LINKAGE outputTestResult( bool testResult );
//void DITEST_LINKAGE writeStreamToFile( std::strstream & myStream );

/**
* This method writes a string to the component test log file
*
* @param     DStringA & - the string to write
* @returns   void
* @exception none
*/
void DITEST_LINKAGE writeLineToFile( DStringA & line );

/**
* This method writes a line to the component test log file
*
* @param     I_STRING & - the string to write
* @returns   void
* @exception none
*/
void DITEST_LINKAGE writeLineToFile( I_STRING & line );

/**
* This method writes a line to the component test log file
*
* @param     char * - the string to write first
* @param     int - the number of threads
* @returns   void
* @exception none
*/
void DITEST_LINKAGE writeThreadHeader( char * prefix,
                                       int numThreads );

enum
{
   TEST_FAILED,
   TEST_SUCCEEDED,
   TEST_TIMED_OUT
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
// $Log:   Y:/VCS/iFastAWD/inc/TestComponent.h-arc  $
//
//   Rev 1.0   28 Jan 2008 13:33:00   kovacsro
//Initial revision.
//
//   Rev 1.2   14 Nov 2001 12:27:00   dt14177
//part of TestInputData enhancement
//
//   Rev 1.1   28 Nov 2000 13:47:08   dt14177
//cleanup
// 

#endif // TESTCOMPONENT_H
