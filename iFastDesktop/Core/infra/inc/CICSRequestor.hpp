#pragma message( "including "__FILE__ )

#ifndef CICSREQUESTOR_HPP
#define CICSREQUESTOR_HPP

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

#ifndef ABSTRACTREQUESTOR_HPP
   #include "abstractrequestor.hpp"
#endif

#ifndef CICSSECURITY_HPP
   #include "cicssecurity.hpp"
#endif

#undef DITA2KDB_LINKAGE
#ifdef DITA2KDB_DLL
   #define DITA2KDB_LINKAGE CLASS_EXPORT
#else
   #define DITA2KDB_LINKAGE CLASS_IMPORT
#endif

class AbstractRequest;
class BaseConnection;
class CICSResponseFormatter;

/**
 * CICS requestor class
 *
 * Class is requestor class for requests made to CICS.
 */
class DITA2KDB_LINKAGE CICSRequestor : public AbstractRequestor
{
public:
   /**
    * Construct a CICSRequestor.
    *
    * @param security contains the user ID and password.
    *
    * @param hostConnectionManagerId     contains the name of the target host,
    *                 the system ID to insert into the request, and the
    *                 request/response formatters to use.
    *
    * @param allResults
    *                 true to get all data, false to make a single host request.
    */
   CICSRequestor( const AbstractSecurity & security,
                  const DString & hostConnectionManagerId );

   /**
    * Construct a CICSRequestor using defaults.
    *
    * @param security contains the user ID and password.
    */
   CICSRequestor( const AbstractSecurity & security );

   /**
    * Copy constructor
    *
    * @param copy - Object being copied from
    */
   CICSRequestor(const CICSRequestor &copy);

   virtual ~CICSRequestor( );

   /**
    * Send a request to TA2000, wait for the response, and return the response
    * data.
    *
    * @param request  contains the name of the request.
    *
    * @param requestData
    *                 contains the data to send to the host. This object may be
    *                 modified by the receive method. For example, during
    *                 "more data" processing the "next key" will be updated.
    *
    * @param responseData
    *                 will hold the cumulative response from the host.
    *
    * @return Returns the highest severity level of any condition raised.
    */
   virtual SEVERITY receive( const BaseRequest & request,
                             Data & requestData,
                             Data & responseData );

   /**
    * Send a request to TA2000 and immediately return.
    *
    * @param request  contains the name of the request.
    *
    * @param requestData
    *                 contains the data to send to the host. This object may be
    *                 modified by the receive method. For example, during
    *                 "more data" processing the "next key" will be updated.
    *
    * @return Returns the highest severity level of any condition raised.
    */
   virtual SEVERITY send( const BaseRequest& requestName,
                          Data &queryData );

   /**
    * Wait for the TA2000 response, and return the response
    * data.
    *
    * @param responseData
    *                 will hold the cumulative response from the host.
    *
    * @return Returns the highest severity level of any condition raised.
    */
   virtual SEVERITY receive( Data &receivedData );

   /**
    * Sets call back functions back to the default methods.
    *
    * Every implementation provides a default set of callsbacks
    */
   virtual void resetNextProcess( );

   /**
    * Sets the system that will be used for routing on the host.
    *
    * @param system   system to be placed in the PB00250 header for routing.
    */
   virtual void setSystem( const DString & system )
   {
      _system = system;
   }

private:
   DString _system;

   unsigned long getErrorCode( unsigned short viewRC ) const;

   unsigned long getExtendedError( const CICSResponseFormatter & response,
                                   long & lError,
                                   DString & dstrLocation ) const;

   CICSRequestor &operator= ( const CICSRequestor &copy );
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
// $Log:   Y:/VCS/iFastAWD/inc/CICSRequestor.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:30:20   kovacsro
//Initial revision.
//
//   Rev 1.1   Jun 08 2001 19:12:46   DT11159
//Added View Manager error information in conditions.
//
//   Rev 1.0   May 18 2001 15:52:48   DT11159
//
//
//

#endif
