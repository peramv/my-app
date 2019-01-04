#pragma once

/*
 * COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1999-2000 by DST Systems, Inc.
 */

/** @pkg DICORE */

#ifndef INCLUDED_UTILITY
#define INCLUDED_UTILITY
#include <utility>
#endif

#ifndef DIPORT2_H
   #include <diport2.h>
#endif

#ifndef DSTRING_HPP
   #include <dstring.hpp>
#endif

/**
 * A wrapper that simplifies programmatically starting
 * another exe asynchronously.
*/
class DICORE_LINKAGE ProgramStarter
{
// enums
public:
   enum PS_CONSTS
   {
      CHARBUF_SIZE = 300
   };

// methods
public:

   /**
    * Constructor
    *
    * @exception (from the internal string instances)
    *            ConditionException(if a "new" call fails)
    */
   ProgramStarter() HEADER_THROW2(exception, ConditionException);

   /**
    * Destructor
    */
   ~ProgramStarter() HEADER_THROW1(exception);

   /**
    * starts the child process
    *
    * @param strExeLine - the command line including parameters
    *                     for the child process
    *
    * @exception (from the internal string instances)
    */
   bool start( const DString & strExeLine ) HEADER_THROW1(exception);

// methods
private:
   ProgramStarter( const ProgramStarter & copy );
   ProgramStarter & operator=( const ProgramStarter & copy );

// attributes
private:
   VOID Create (PCHAR &pch) HEADER_THROW2(exception, ConditionException);
   VOID Destroy (VOID) HEADER_THROW1(exception);
   VOID InitStartData (VOID);
   VOID FixCommandLine (const DString & strExeLine);

   STARTUPDATA                   *_pStartData;

   char                          *_pObjectBuff;

   char                          *_pszPgmName;
   char                          *_pszPgmInputs;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   //db3n5j11/d/scc/ifds/core/archives/ifdscore/programstarter.hpp-arc  $
//
//   Rev 1.1   Oct 09 2002 17:42:12   PURDYECH
//New PVCS Database
//
//   Rev 1.0   Jul 05 2002 10:15:02   SMITHDAV
//Initial revision.
// 
//    Rev 1.5   30 Oct 2000 14:27:32   dt14177
// cleanup
// 
//    Rev 1.4   24 Feb 1999 10:45:26   DT14177
// sync up with tracer
// 
//    Rev 1.3   18 Feb 1999 10:40:02   DT14177
// UNICODE
// 
//    Rev 1.2   Jan 28 1999 14:06:44   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.1   Dec 09 1998 13:42:14   DMUM
// Check in for DICORE
//
//    Rev 1.5   Nov 09 1997 15:34:46   DTWK
// Add inclusion guards for faster compiles.
// Add guards so that class is flagged as exported only when compiling
// the output that actually exports the class.
//
//    Rev 1.4   Jul 07 1997 15:12:08   DTWK
//
//
//    Rev 1.3   Jun 13 1997 13:25:40   DTWK
//
//
//

