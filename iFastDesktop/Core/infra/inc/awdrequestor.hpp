#ifndef AWDREQUESTOR_HPP
#define AWDREQUESTOR_HPP

#pragma message( "including "__FILE__ )

/******************************************************************************
 *
 * COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1999-2001 by DST Systems, Inc.
 *
 *
 *******************************************************************************/

#ifndef ABSTRACTREQUESTOR_HPP
   #include "abstractrequestor.hpp"
#endif

// Import/Export resolution
#undef DIAWDDB_LINKAGE
#ifdef DIAWDDB_DLL
   #define DIAWDDB_LINKAGE CLASS_EXPORT
#else
   #define DIAWDDB_LINKAGE CLASS_IMPORT
#endif

/**
 *  AWD requestor class
 *
 *  Class handles the communications between the client and the AWD server
 */
class DIAWDDB_LINKAGE AWDRequestor : public AbstractRequestor
{
public:
   /**
    * Class handles the communications with the backend.
    *
    * This constructor uses the default host manager name used by the security object
    *
    * @param abstractSecurity - Security object for user
    */
   AWDRequestor( const AbstractSecurity & abstractSecurity,
                 const DString & connectionName );

   /**
    * Class handles the communications with the backend.
    *
    * This constructor allows for a different host connection manager than the
    *   default used by the security object.
    *
    * @param abstractSecurity - Security object for user
    * @param hostConnectionManagerId - Allow override to different host
    *            manager than defined in security object
    */
   AWDRequestor( const AbstractSecurity & abstractSecurity,
                 const DString & hostConnectionManagerId,
                 const DString & connectionName );

   /**
    * Copy constructor
    *
    * @param copy - Object being copied from
    */
   AWDRequestor(const AWDRequestor &copy);

   virtual ~AWDRequestor();

   /**
    * Sync request for data from backend.
    *
    * The method wais until the backend has responded with the requested data
    *
    * @param requestName - Identification of the request
    * @param queryData - Data being sent to the backend
    * @param receivedData - Data returned from backend
    *
    * @returns SEVERITY - A condition severity level from any error conditions found
    */
   virtual SEVERITY receive( const BaseRequest& requestName,
                             Data &queryData, Data &receivedData );

   /**
    * Async send for data from backend.
    *
    * The method sends the data to the back end and immediately returns
    *
    * @param requestName - Identification of the request
    * @param queryData - Data being sent to the backend
    *
    * @returns SEVERITY - A condition severity level from any error conditions found
    */
   virtual SEVERITY send( const BaseRequest& requestName,
                          Data &queryData );
   /**
    * Async receive for data from backend.
    *
    * The method wais until the backend has responded with the requested data
    * It can be used inside other application threads and when the method returns
    * a semaphore can used to signal the application that the data was returned.
    *
    * @param receivedData - Data returned from backend
    *
    * @returns SEVERITY - A condition severity level from any error conditions found
    */
   virtual SEVERITY receive( Data &receivedData );

   /**
    * Sets call back functions back to the default methods
    *
    * Every implementation provides a default set of callsbacks
    */
   virtual void resetNextProcess( );

private:
   AWDRequestor &operator= ( const AWDRequestor &copy );
};

#endif

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
// $Log:   Y:/VCS/iFastAWD/inc/awdrequestor.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:29:50   kovacsro
//Initial revision.
//
//   Rev 1.1   Jun 08 2001 19:14:10   DT11159
//Added View Manager error information in conditions.
//
//   Rev 1.0   May 18 2001 15:53:34   DT11159
//
//
//
