#ifndef TESTHELPER_HPP
#define TESTHELPER_HPP

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
 *    Copyright 2001 by DST Systems, Inc.
 */

#ifndef COMMONTEMPLATES_H
   #include "commontemplates.h"
#endif

#ifndef DSTRING_HPP
   #include "dstring.hpp"
#endif

#undef DITEST_LINKAGE
#ifdef DITEST_DLL
   #define DITEST_LINKAGE CLASS_EXPORT
#else
   #define DITEST_LINKAGE CLASS_IMPORT
#endif

#ifndef TESTDATA_HPP
   #include "testdata.hpp"
#endif

#ifndef TESTCOMPONENT_H
#   include "testcomponent.h"
#endif

#ifndef DSTMEMORY_H
#include "dstmemory.h"
#endif

#include <iostream>
#include <crtdbg.h>

typedef void ( * PFN_TESTDATA_PTR ) ( void * );

typedef struct 
{
   PFN_TESTDATA_PTR pfn;
   I_CHAR * fnName;
} FN_CONTROL;


/**
 * This static method class runs standard test methods
 */

class DITEST_LINKAGE TestHelper
{
public:
   static int doTestProcessing( int argc, 
                                char * argv[],
                                FN_CONTROL * functionKey );

private:
   static int runTests( FN_CONTROL * functionKey );

private: // not implemented
   TestHelper();
   TestHelper( const TestHelper & );
   TestHelper & operator=( const TestHelper & );
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
// $Log:   Y:/VCS/iFastAWD/inc/testhelper.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:33:02   kovacsro
//Initial revision.
//
//   Rev 1.1   16 Nov 2001 07:52:52   dt14177
//fixed Unicode build
//
//   Rev 1.0   13 Nov 2001 15:42:42   dt14177
//
#endif // TESTHELPER_HPP
