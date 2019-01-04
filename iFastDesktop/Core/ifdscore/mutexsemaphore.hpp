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

#ifndef SEMAPHORE_HPP
   #include <semaphore.hpp>
#endif

#undef DICORE_LINKAGE
#ifdef DICORE_DLL
   #define DICORE_LINKAGE CLASS_EXPORT
#else
   #define DICORE_LINKAGE CLASS_IMPORT
#endif

/**
 * MutexSemaphore is used to serialize processing.  It is often
 * used in conjunction with CriticalSection to protect
 * system resources from multiple accesses during a change to
 * the resource.
 */
class DICORE_LINKAGE MutexSemaphore : public Semaphore
{
// enums
public:
   enum MUTEXSEM_ENUMS
   {
      INITIALLY_OWNED,
      INITIALLY_UNOWNED
   };

// functions
public:
   /**
    * Constructor
    *
    * @param ulTimeout - the number of milliseconds before the
    *               Semaphore will timeout.  Defaults to no timeout.
    *
    * @param eStateIn - tells whether create the semaphore
    *                   in the owned or unowned state.
    *
    * @exception ConditionException & - DIBASE_MUTEXSEM_CREATE_FAIL
    *                                 - DIBASE_MUTEXSEM_OPEN_FAIL
    */
   MutexSemaphore( unsigned long ulTimeout = -1,
                   MUTEXSEM_ENUMS eState = INITIALLY_UNOWNED )
   HEADER_THROW2(ConditionException, exception);

   /**
    * Constructor
    *
    * @param eStateIn - tells whether create the semaphore
    *                   in the owned or unowned state.
    *
    * @param ulTimeout - the number of milliseconds before the
    *               Semaphore will timeout.  Defaults to no timeout.
    *
    * @exception ConditionException & - DIBASE_MUTEXSEM_CREATE_FAIL
    *                                 - DIBASE_MUTEXSEM_OPEN_FAIL
    */
   MutexSemaphore( MUTEXSEM_ENUMS eState,
                   unsigned long ulTimeout = -1 )
   HEADER_THROW2(ConditionException, exception);

   /**
    * Copy Constructor
    *
    * @param orig - MutexSemaphore to copy
    *
    * @exception ConditionException & - DIBASE_MUTEXSEM_CREATE_FAIL
    */
   MutexSemaphore( const MutexSemaphore& orig ) 
   HEADER_THROW1(exception);

   /**
    * Constructor
    *
    * @param strSemName - the name of the semaphore. Defaults to
    *    an unnamed semaphore.
    *
    * @param fCreate - tells whether to create the semaphore or not.
    *    If you are trying to open a named semaphore that has
    *    already been created by another thread/process, then this
    *    would be false. Defaults to true.
    *
    * @param ulTimeout - the number of milliseconds before the
    *               Semaphore will timeout.  Defaults to no timeout.
    *
    * @param eStateIn - tells whether create the semaphore
    *                   in the owned or unowned state.
    *
    * @exception ConditionException & - DIBASE_MUTEXSEM_CREATE_FAIL
    *                                 - DIBASE_MUTEXSEM_OPEN_FAIL
    */
   MutexSemaphore( const I_CHAR * pszName, 
                   bool fCreate = true,
                   unsigned long ulTimeout = -1,
                   MUTEXSEM_ENUMS eState = INITIALLY_UNOWNED )
   HEADER_THROW2(ConditionException, exception);

   /**
    * Destructor
    */
   ~MutexSemaphore() HEADER_THROW1(exception);

   /**
    * posts the semaphore (releases ownership).
    *
    * @exception ConditionException & - DIBASE_MUTEXSEM_RELEASE_FAIL
    */
   void post() HEADER_THROW2(ConditionException, exception);

   /**
    * waits on the semaphore for the number of milliseconds set
    * in the constructor or by calling setTimeout. If successful,
    * the calling thread now owns the semaphore.
    *
    * @exception ConditionException & - DIBASE_MUTEXSEM_WAIT_FAIL
    */
   void wait() HEADER_THROW2( ConditionException, exception );

   /**
    * Queries the number of waits called on the semaphore.
    * On WIN32, returns 1 or 0.  1 if a thread owns the
    * semaphore, 0 if it is unowned.
    *
    * @exception ConditionException & - DIBASE_MUTEXSEM_WAIT_FAIL
    */
   unsigned long query() HEADER_THROW2( ConditionException,
                                        exception );

   /**
    * Queries the number of waits called on the semaphore.
    * On WIN32, returns 1 or 0.  1 if a thread owns the
    * semaphore, 0 if it is unowned.
    *
    * @exception ConditionException & - DIBASE_MUTEXSEM_WAIT_FAIL
    */
   virtual unsigned long query( PID * pPID, TID * pTID )
   HEADER_THROW2( ConditionException, exception );

protected:

   /**
    * creates the semaphore.
    *
    * @exception (from the internal string instances)
    *            ConditionException (DIBASE_MUTEXSEM_CREATE_FAIL
    *            if the create fails)
    */
   virtual void create() 
   HEADER_THROW2( ConditionException, exception);
   /**
    * opens the semaphore.
    *
    * @exception (from the internal string instances)
    *            ConditionException (DIBASE_MUTEXSEM_OPEN_FAIL
    *            if the open fails)
    */
   virtual void open() 
   HEADER_THROW2( ConditionException, exception );
   /**
    * closes the semaphore.
    */
   virtual void close() HEADER_THROW;

// data
private:
   MUTEXSEM_ENUMS          _eState;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   //db3n5j11/d/scc/ifds/core/archives/ifdscore/mutexsemaphore.hpp-arc  $
//
//   Rev 1.1   Oct 09 2002 17:42:10   PURDYECH
//New PVCS Database
//
//   Rev 1.0   Jul 05 2002 10:15:02   SMITHDAV
//Initial revision.
// 
//    Rev 1.6   30 Oct 2000 09:33:08   dt14177
// cleanup
// 
//    Rev 1.5   24 Feb 1999 10:45:22   DT14177
// sync up with tracer
// 
//    Rev 1.4   22 Feb 1999 11:44:10   DT14177
// pragma message( __FILE__ )
// 
//    Rev 1.3   18 Feb 1999 10:39:58   DT14177
// UNICODE
// 
//    Rev 1.2   Jan 28 1999 14:06:42   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.1   Dec 09 1998 13:42:12   DMUM
// Check in for DICORE
//
//    Rev 1.10   Nov 09 1997 15:34:44   DTWK
// Add inclusion guards for faster compiles.
// Add guards so that class is flagged as exported only when compiling
// the output that actually exports the class.
//
//    Rev 1.9   Jul 23 1997 11:52:42   DTWK
// add tracing
//
//    Rev 1.8   Jul 07 1997 15:12:02   DTWK
//
//
//    Rev 1.7   Jun 13 1997 13:25:32   DTWK
//
//
//

