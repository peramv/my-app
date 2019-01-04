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
 *    Copyright 1999, 2000 by DST Systems, Inc.
 */

/** @pkg DICORE */

/** 
 *A wrapper for EventSemaphores.
 */

// ----------------------------------------------------------
//               PROTECTED MEMBER FUNCTIONS
// ----------------------------------------------------------
//
// ----------------------------------------------------------
// ^METHOD      : create
//
// ^DESCRIPTION : creates the semaphore.
//
// ^PARAMETERS  : none
//
// ^RETURNS     : none
//
// ^THROWS      : exception (from the internal string instances)
//                ConditionException (DIBASE_EVENTSEM_CREATE_FAIL
//                   if the create fails)
//
// ----------------------------------------------------------
// ^METHOD      : open
//
// ^DESCRIPTION : opens the semaphore.
//
// ^PARAMETERS  : none
//
// ^RETURNS     : none
//
// ^THROWS      : exception (from the internal string instances)
//                ConditionException (DIBASE_EVENTSEM_OPEN_FAIL if the create
//                   fails)
//
// ----------------------------------------------------------
// ^METHOD      : close
//
// ^DESCRIPTION : closes the semaphore.
//
// ^PARAMETERS  : none
//
// ^RETURNS     : none
//
// ^THROWS      : none
//
//
//******************************************************************************

#ifndef SEMAPHORE_HPP
   #include <semaphore.hpp>
#endif

class DICORE_LINKAGE EventSemaphore : public Semaphore
{
// enums
public:
   enum EVENTSEM_ENUMS
   {
      INITIALLY_SET,
      INITIALLY_POSTED
   };

// functions
public:

   /**
    * Copy Constructor
    */
   EventSemaphore( const EventSemaphore& orig ) HEADER_THROW1(exception);

   /**
    * Constructor
    *
    * parms:
    *
    *  EVENTSEM_ENUMS eStateIn - tells whether to create the 
    *     semaphore in the set or posted state.
    *
    *  long ulTimeout - the number of milliseconds before the
    *     Semaphore will timeout.  Defaults to no timeout (-1).
    *
    * returns: this
    *
    * throws:
    *    exception (from the internal string instances)
    *              ConditionException (DIBASE_EVENTSEM_CREATE_FAIL
    *              or DIBASE_EVENTSEM_OPEN_FAIL if the create
    *              or open fails)
    */
   EventSemaphore( EVENTSEM_ENUMS eStateIn,
                   unsigned long ulTimeoutIn = -1 )
   HEADER_THROW2(ConditionException, exception);

   /**
    * Constructor
    *
    * parms:
    *
    *  long ulTimeout - the number of milliseconds before the
    *     Semaphore will timeout.  Defaults to no timeout (-1).
    *
    *  EVENTSEM_ENUMS eStateIn - tells whether to create the 
    *     semaphore in the set or posted state.
    *
    * returns: this
    *
    * throws:
    *    exception (from the internal string instances)
    *              ConditionException (DIBASE_EVENTSEM_CREATE_FAIL
    *              or DIBASE_EVENTSEM_OPEN_FAIL if the create
    *              or open fails)
    */
   EventSemaphore( unsigned long ulTimeoutIn = -1,
                   EVENTSEM_ENUMS eStateIn = INITIALLY_SET )
   HEADER_THROW2(ConditionException, exception);

   /**
    * Constructor
    *
    * parms:
    *
    *  const I_CHAR * pszName - the name of the semaphore.
    *     Defaults to an unnamed semaphore.
    *
    *  bool fCreate - tells whether to create the semaphore or not.
    *     If you are trying to open a named semaphore that has
    *     already been created by another thread/process, then this
    *     would be false. Defaults to true.
    *
    *  long ulTimeout - the number of milliseconds before the
    *     Semaphore will timeout.  Defaults to no timeout (-1).
    *
    *  EVENTSEM_ENUMS eStateIn - tells whether to create the 
    *     semaphore in the set or posted state.
    *
    * returns: this
    *
    * throws:
    *    exception (from the internal string instances)
    *              ConditionException (DIBASE_EVENTSEM_CREATE_FAIL
    *              or DIBASE_EVENTSEM_OPEN_FAIL if the create
    *              or open fails)
    */
   EventSemaphore( const I_CHAR * pszName, 
                   bool fCreate = true,
                   unsigned long ulTimeoutIn = -1,
                   EVENTSEM_ENUMS eStateIn = INITIALLY_SET )
   HEADER_THROW2(ConditionException, exception);

   /**
    * destructor
    */
   ~EventSemaphore() HEADER_THROW1(exception);

   /**
    * This method releases the semaphore
    *
    * throws:
    *    exception (from the internal string instances)
    *              ConditionException (DIBASE_EVENTSEM_SET_FAIL
    *              if the post fails)
    */
   virtual void post() HEADER_THROW2(ConditionException, exception);

   /**
    * This method clutches the semaphore; itwaits on the semaphore
    * for the number of milliseconds set in the constructor or by
    * calling setTimeout()
    *
    * This method will throw an exception if the semaphore
    * times out.  You should really put a try block around it.
    */
   virtual void wait() HEADER_THROW2(ConditionException, exception);

   /**
    * This method reports the number of waits called on the
    * semaphore
    *
    * returns: the number of waits called
    *
    * throws:      
    *    exception (from the internal string instances)
    *              ConditionException (DIBASE_EVENTSEM_WAIT_FAIL if the wait
    *                fails)
    *            ConditionException (DIBASE_EVENTSEM_SET_FAIL if the post
    *               fails)
    */
   virtual unsigned long query() HEADER_THROW2(ConditionException, exception);

   /**
    * This method resets the semaphore
    *
    * throws:   
    *     exception (from the internal string instances)
    *               ConditionException (DIBASE_EVENTSEM_RESET_FAIL if the reset
    *               fails. It will not throw if you call reset() on a
    *               EventSemaphore that is already reset)
    */
   virtual void reset() HEADER_THROW2(ConditionException, exception);


protected:

   /**
    * creates the semaphore
    *
    * Throws:
    *    exception (from the internal string instances)
    *              ConditionException (DIBASE_EVENTSEM_CREATE_FAIL
    *              if the create fails)
    */
   virtual void create() HEADER_THROW2(ConditionException, exception);

   /**
    * opens the semaphore
    *
    * Throws:
    *    exception (from the internal string instances)
    *              ConditionException (DIBASE_EVENTSEM_OPEN_FAIL
    *              if the open fails)
    */
   virtual void open() HEADER_THROW2(ConditionException, exception);

   /**
    * closes the semaphore
    */
   virtual void close() HEADER_THROW;

// data
private:
   EVENTSEM_ENUMS          _eState;
};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   //db3n5j11/d/scc/ifds/core/archives/ifdscore/eventsemaphore.hpp-arc  $
//
//   Rev 1.1   Oct 09 2002 17:42:00   PURDYECH
//New PVCS Database
//
//   Rev 1.0   Jul 05 2002 10:14:54   SMITHDAV
//Initial revision.
// 
//    Rev 1.5   25 Oct 2000 09:53:22   dt14177
// cleanup
// 
//    Rev 1.4   24 Feb 1999 11:00:10   DT14177
// sync up with tracer
// 
//    Rev 1.3   22 Feb 1999 11:44:08   DT14177
// pragma message( __FILE__ )
// 
//    Rev 1.2   Jan 28 1999 14:06:26   DMUM
// Check in for VCPP 6.0
// 
//    Rev 1.1   Dec 09 1998 13:42:00   DMUM
// Check in for DICORE
// 
//    Rev 1.10   Nov 09 1997 15:34:38   DTWK
// Add inclusion guards for faster compiles.
// Add guards so that class is flagged as exported only when compiling
// the output that actually exports the class.
// 
//    Rev 1.9   Jul 23 1997 11:52:26   DTWK
// Add tracing
// 
//    Rev 1.8   Jul 07 1997 15:11:58   DTWK
//  
// 
//    Rev 1.7   Jun 13 1997 13:25:24   DTWK
//  
//
//
