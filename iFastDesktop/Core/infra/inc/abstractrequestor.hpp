#pragma message( "including "__FILE__ )

#ifndef ABSTRACTREQUESTOR_HPP
#define ABSTRACTREQUESTOR_HPP

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
#ifndef BASECONNECTION_HPP
   #include "baseconnection.hpp"
#endif

#ifndef BASEREQUESTOR_HPP
   #include "baserequestor.hpp"
#endif

// Import/Export resolution
#undef DIDBRKR_LINKAGE
#ifdef DIDBRKR_DLL
   #define DIDBRKR_LINKAGE CLASS_EXPORT
#else
   #define DIDBRKR_LINKAGE CLASS_IMPORT
#endif

class AbstractSecurity;

namespace RequestorOptions
{
   const long OVERWRITE_FIXED_AREA = 0x8000;
}

/**
 * Abstract requestor class
 *
 * Class is the common parent for most requestor classes.  It provides the
 * common functions needed for getting data from the backend.
 */
class DIDBRKR_LINKAGE AbstractRequestor : public BaseRequestor
{
public:
   /**
    * Class handles the communications with the backend.
    *
    * This constructor uses the default host manager name used by the security object
    *
    * @param abstractSecurity - Security object for user
    *
    */
   AbstractRequestor( const AbstractSecurity &abstractSecurity,
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
    *
    */
   AbstractRequestor( const AbstractSecurity &abstractSecurity,
                      const DString &hostConnectionManagerId,
                      const DString & connectionName );

   /**
    * Copy constructor
    *
    * @param copy - Object being copied from
    *
    */
   AbstractRequestor(const AbstractRequestor &copy);

   virtual ~AbstractRequestor();

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
    *
    */
   virtual SEVERITY receive( const BaseRequest& requestName,
                             Data &queryData, Data &receivedData ) = 0;

   /**
    * Async send for data from backend.
    *
    * The method sends the data to the back end and immediately returns
    *
    * @param requestName - Identification of the request
    * @param queryData - Data being sent to the backend
    *
    * @returns SEVERITY - A condition severity level from any error conditions found
    *
    */
   virtual SEVERITY send( const BaseRequest& requestName,
                          Data &queryData ) = 0;

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
    *
    */
   virtual SEVERITY receive( Data &receivedData ) = 0;

   /**
    * Sets the options that the following back end requests will follow
    *
    * The valid options are defined in the ResponseOptions name space
    * The global options for all backends are defined at this level and subclasses
    * can add back end specific flags
    *
    * Example Usage:
    * *@@ setOptions( ResponseOptions::GET_ALL_RESULTS );
    *
    * @param options - Options to be used in following requests
    *
    */
   virtual void setOptions( short newOptions )
   {
      _currentOptions = newOptions;
   }

   /**
    * Get the current options the back end requests will follow
    *
    * The valid options are defined in the ResponseOptions name space
    * The global options for all backends are defined at this level and subclasses
    * can add back end specific flags
    *
    * @return long - All current options values
    *
    */
   virtual long getOptions( )
   {
      return _currentOptions;
   };

   /**
    * Used to set the host ID.  If the connection is not to a single host, but
    * is instead a connection to middleware, this method allows the host to be
    * changed prior to sending data to the connection.
    *
    * @param hostId Name of the target host for this connection.
    */
   virtual void setHostId( const DString & hostId )
   {
      if ( _connection )
      {
         _connection->setHostId( hostId );
      }
   }

   /**
    * Sets the maximum time, in seconds, that the caller is willing to wait for
    * a response.  If this period is exceeded, then an error response will be
    * returned.  The timeout will default to 0, meaning wait indefinitely.  Once
    * this method is called, the new timeout value will remain in effect for the
    * life of the object or until this method is called again.
    *
    * Example Usage:
    * <code>
    * setTimeout( 30 ); // Set timeout to 30 seconds.
    * </code>
    *
    * @param timeout - Timeout period in seconds.  A timeout of zero means to
    *                  wait indefinitely.
    *
    */
   virtual void setTimeout( unsigned long timeout )
   {
      _timeout = timeout;
   }

   /**
    * Gets the maximum time, in seconds, that the caller is willing to wait for
    * a response.  A value of 0 means wait indefinitely.
    *
    * Example Usage:
    * <code>
    * unsigned long timeout = getTimeout( ); // Get timeout period in seconds.
    * </code>
    *
    * @return Timeout period in seconds.
    *
    */
   virtual unsigned long getTimeout( )
   {
      return _timeout;
   }

   /**
    * Sets call back functions used in more processing
    *
    * The provided callback moves the data needed in more processing from
    * the received data to the request data and one for determining if more
    * data is available by looking at the received data.
    *
    * @param fnIsMoreAvailable - Callback to check if more data on backend
    * @param fnSetNextKey - Callback used to move data needed for next request
    *
    */
   virtual void setNextProcess( pfnIsMoreAvailable fnIsMoreAvailable,
                                pfnSetNextKey      fnSetNextKey );

   /**
    * Sets call back functions back to the default methods
    *
    * Every implementation provides a default set of callsbacks
    *
    */
   virtual void resetNextProcess( ) = 0;

   /**
    * Calls currently defined more available callback.
    *
    * The callback determines is more data is available on the backend.  This
    * method calls the currently defined callback.
    *
    * @param responseData - Data returned from backend
    *
    */
   virtual bool isMoreAvailable( const Data& responseData )
   {
      return _fnIsMoreAvailable( responseData );
   }

   /**
    * Calls currently defined set next key callback.
    *
    * The callback moves data needed to get next set of data from backend.  This
    * method calls the currently defined callback.
    *
    * @param requestData - Data being sent to backend
    * @param responseData - Data returned from backend
    *
    */
   virtual void setNextKey( Data& requestData,
                            Data& responseData )
   {
      _fnSetNextKey( requestData, responseData );
   }

   /**
    * Sets the window information needed for notification via PostMessage
    *
    * The calling application can use messaging to be notified of data returned
    * from the backend.
    *
    * The application must use the unique combinations of the two values.  The values
    * provides in the set are only used once and a different combination
    * must be provided for the next messaging notfication.  If the unique combination is
    * not provided, the normal notification process will be used via semaphores.
    *
    * @param hwndRecipient - Window identifier
    * @param ulMsg - Message identifier
    *
    */
   virtual void setWindowInfo( DSTWINDOWHANDLE hwndRecipient,
                               unsigned long ulMsg );

protected:
   const AbstractSecurity &_abstractSecurity;
   DString _hostConnectionManagerId;
   BaseConnection *_connection;
   long _currentOptions;

   pfnIsMoreAvailable      _fnIsMoreAvailable;
   pfnSetNextKey           _fnSetNextKey;

   DSTWINDOWHANDLE _hwndRecipient;
   unsigned long _ulMsg;

   bool _processingWindowHandle;

private:
   AbstractRequestor &operator= ( const AbstractRequestor &copy );
   unsigned long _timeout;

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
// $Log:   Y:/VCS/iFastAWD/inc/abstractrequestor.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:29:40   kovacsro
//Initial revision.
//
//   Rev 1.1   May 20 2001 16:56:32   DT11159
//Added the setHostId method to allow applications
//to change the target host  of a connection when using
//View Manager.
//
//   Rev 1.0   May 18 2001 15:53:18   DT11159
//
//
//
