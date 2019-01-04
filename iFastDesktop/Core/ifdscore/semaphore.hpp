#pragma once

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

/**@pkg DICORE */    

#ifndef DIPORT2_H
   #include <diport2.h>
#endif

#ifndef DSTRING_HPP
   #include <dstring.hpp>
#endif

#undef DICORE_LINKAGE
#ifdef DICORE_DLL
   #define DICORE_LINKAGE CLASS_EXPORT
#else
   #define DICORE_LINKAGE CLASS_IMPORT
#endif

class DICORE_LINKAGE Semaphore
{
// enums
public:
   enum SEM_ENUM
   {
      NO_TIMEOUT = -1,
      IMMEDIATE_TIMEOUT = 0
   };

// functions
public:
   /**
    * constructor
    *
    * @param ulTimeout - the number of milliseconds before the
    *                    Semaphore will timeout.  Defaults to no 
    *                    timeout.
    */
   Semaphore( unsigned long ulTimeout = NO_TIMEOUT )
   HEADER_THROW1(exception);

   /**
    * constructor
    *
    * @param strSemName - the name of the semaphore. Defaults to
    *                     an unnamed semaphore
    * @param ulTimeout - the number of milliseconds before the
    *                    semaphore will timeout.  Defaults to no 
    *                    timeout.
    * @param hSem - the semaphore handle
    */
   Semaphore( const DString &strSemName, 
              unsigned long ulTimeout, 
              HANDLE hSem )
   HEADER_THROW1(exception);
   /**
    * constructor
    *
    * @param strSemName - the name of the semaphore. Defaults to
    *                     an unnamed semaphore
    * @param ulTimeout - the number of milliseconds before the
    *                    semaphore will timeout.  Defaults to no 
    *                    timeout.
    */
   Semaphore( DString &strSemName, 
              unsigned long ulTimeout = NO_TIMEOUT )
   HEADER_THROW1(exception);
   /**
    * constructor
    *
    * @param strSemName - the name of the semaphore. Defaults to
    *                     an unnamed semaphore
    * @param ulTimeout - the number of milliseconds before the
    *                    semaphore will timeout.  Defaults to no 
    *                    timeout.
    */
   Semaphore( const I_CHAR *pszName, 
              unsigned long ulTimeout = NO_TIMEOUT )
   HEADER_THROW1(exception);

   /**
    * destructor
    */
   virtual ~Semaphore() HEADER_THROW;

   /**
    * returns the semaphore handle
    */
   virtual HANDLE getHandle() const;

   /**
    * returns the semaphore name
    */
   virtual const DStringA & getName() const
   HEADER_THROW1(exception);

   /**
    * returns the timeout
    */
   virtual unsigned long getTimeout() const HEADER_THROW;

   /**
    * sets the timeout
    */
   virtual void setTimeout( unsigned long ulTimeout ) HEADER_THROW;

   /**
    * posts (releases) the semaphore
    */
   virtual void post() = 0;

   /**
    * waits for (grabs) the semaphore
    */
   virtual void wait() = 0;

   /**
    * returns the status of the semaphore
    */
   virtual unsigned long query() = 0;

protected:
   /**
    * creates the semaphore
    */
   virtual void create() = 0;

   /**
    * opens the semaphore
    */
   virtual void open() = 0;

   /**
    * closes the semaphore
    */
   virtual void close() = 0;

protected: // methods
   /**
    * initializer method
    */
   virtual void Initialize ( bool fCreate );

   /**
    * returns the name
    */
   virtual PCCH GetName (VOID);

   /**
    * throws an exception
    */
   virtual VOID ThrowError ( const DString & strFunc, 
                             int nError, 
                             const DString &strError,
                             DWORD dwResult);

protected: // attributes
   DStringA                 _strSemName;
   HANDLE                   _hsem;

   // data
private:
   void _setName (PCCH pcchName);

   unsigned long           _ulTimeout; // -1 means no timeout.

};

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   //db3n5j11/d/scc/ifds/core/archives/ifdscore/semaphore.hpp-arc  $
//
//   Rev 1.1   Oct 09 2002 17:42:14   PURDYECH
//New PVCS Database
//
//   Rev 1.0   Jul 05 2002 10:15:04   SMITHDAV
//Initial revision.
// 
//    Rev 1.8   27 Nov 2000 14:34:18   dt14177
// cleanup
// 
//    Rev 1.7   01 Mar 1999 15:22:32   DT14177
// fixed stack problem GetName()
// 
//    Rev 1.6   01 Mar 1999 15:06:24   DT14177
// fixed stack problem with GetName()
// 
//    Rev 1.5   24 Feb 1999 10:45:28   DT14177
// sync up with tracer
// 
//    Rev 1.4   22 Feb 1999 11:44:12   DT14177
// pragma message( __FILE__ )
// 
//    Rev 1.3   18 Feb 1999 10:40:04   DT14177
// UNICODE
// 
//    Rev 1.2   Jan 28 1999 14:06:46   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.1   Dec 09 1998 13:42:16   DMUM
// Check in for DICORE
//
//    Rev 1.10   Nov 09 1997 15:34:48   DTWK
// Add inclusion guards for faster compiles.
// Add guards so that class is flagged as exported only when compiling
// the output that actually exports the class.
//
//    Rev 1.9   Jul 07 1997 15:12:04   DTWK
//
//
//    Rev 1.8   Jun 13 1997 13:25:34   DTWK
//
//
//

