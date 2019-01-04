#ifndef VMREQ_HPP
#define VMREQ_HPP

/*
 *    COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1999-2000 by DST Systems, Inc.
 */

/**@pkg DIVIEW */

#pragma message( "including "__FILE__ )

#ifndef DIPORT2_H
#define INCL_DOSQUEUES
#include "diport2.h"
#endif

extern "C"
{
#ifndef INCLUDED_VM_H
#define INCLUDED_VM_H
   #include "vm.h"
#endif
#ifndef INCLUDED_VMDLL_H
#define INCLUDED_VMDLL_H
   #include "vmdll.h"
#endif
#ifndef INCLUDED_VMDST_H
#define INCLUDED_VMDST_H
   #include "vmdst.h"
#endif
}

#ifndef CONDITIONMANAGER_HPP
   #include "conditionmanager.hpp"
#endif

#ifndef DSTRING_HPP
   #include "dstring.hpp"
#endif

// These were used to talk to the Stratus machine
typedef SEVERITY ( OPT_LINKAGE * pfnSendPreprocess ) ( const unsigned char *,
                                                       unsigned long,
                                                       unsigned char * &,
                                                       unsigned long & );

typedef SEVERITY ( OPT_LINKAGE * pfnExtractOverride ) ( unsigned char *, PVMDSTRESP );


/**@#-*/
class EventSemaphore;         // forward declaration
/**@#+*/

#undef DIVIEW_LINKAGE
#ifdef DIVIEW_DLL
   #define DIVIEW_LINKAGE CLASS_EXPORT
#else
   #define DIVIEW_LINKAGE CLASS_IMPORT
#endif

#define VMREQ_TIME_SIZE    30
/**
 * Returns the time in milliseconds
 *
 * @param argTime - (out) the time storage location
 * @return
 */
void CLASS_EXPORT getUniqueMillisecondTime( I_CHAR * argTime );

/**
 * A simple wrapper around AWD / View, with some TA2000 specific
 * methods
 *
 */
class DIVIEW_LINKAGE VMRequest
{
public:
   enum PUBLIC_CONSTANTS { DEFAULT_TIMEOUT = 0 };

   /**
    * Default constructor for the object.
    *
    * @param ulTimeout - This can cause problems in views or is simply ignored
    *                  by AWD / View, depending on the protocol.  This should
    *                  always be set to never timeout.
    * @param fnSendPreprocess
    *                  - A user-defined callback this can access the request data
    *                  stream before it is sent to the host.
    * @param fnExtractOverride
    *                  - A user-defined callback function that can access the response
    *                  data stream before it has been formatted by by the VMRequest
    *                  object.
    * @exception ConditionException
    *                      DIBASE_VMREQ_INIT_FAIL if connection fails
    * @exception exception from string class
    */
   VMRequest( unsigned long ulTimeout,
              pfnSendPreprocess fnSendPreprocess = NULL,
              pfnExtractOverride fnExtractOverride = NULL );

   /**
    * Default constructor for the object.
    *
    * @param fnSendPreprocess
    *                  - A user-defined callback this can access the request data
    *                  stream before it is sent to the host.
    * @param fnExtractOverride
    *                  - A user-defined callback function that can access the response
    *                  data stream before it has been formatted by by the VMRequest
    *                  object.
    * @exception ConditionException
    *                      DIBASE_VMREQ_INIT_FAIL if connection fails
    * @exception exception from string class
    */
   VMRequest( pfnSendPreprocess fnSendPreprocess = NULL,
              pfnExtractOverride fnExtractOverride = NULL );

   /**
    * Construct a VMRequest object that will respond to view calls by
    * posting a message back to a GUI window.  This uses the VmNotifyWin
    * method in AWD / View (see the AWD / View docs)
    *
    * Upon receiving the message posted by AWD / View, the user of this object
    * should call vmGetResponse() and getTA2000SpecificData().
    *
    * @param hwndResponse
    *               - the GUI window that will receive the response message
    * @param ulMsg  - the message that will be posted back to hwndResponse
    */
   VMRequest( DSTWINDOWHANDLE hwndResponse,
              unsigned long ulMsg );

   /**
    * Destory object and shutdown AWD View connection.
    *
    */
   virtual ~VMRequest();

   /**
    * Get the error message returned by AWD View
    *
    * @return pointer to an internal data buffer containing the error message.
    *
    */
   const char * getErrorMsg( void ) const;

   /**
    * Get the raw response buffer from the Host.
    *
    * @param pBuf   - a pointer to the buffer that will receive the data
    * @param ulBufSize the size of the buffer in bytes
    * @return true if successful, false otherwise.
    */
   bool getBuffer( char * pBuf, unsigned long ulBufSize ) const;

   /**
    * Get the length of the raw response buffer from the host.
    *
    * @return the length in bytes.
    */
   unsigned long getBufferLength() const;

   /**
    * Copy the view's fixed data into a buffer.
    *
    * @param pBuf - the buffer to copy the data into.
    * @param ulBufSize - the size of the buffer
    * @return true if some or all of the data was copied, false otherwise.
    *
    */
   bool getFixedData( unsigned char * pBuf,
                      unsigned long ulBufSize ) const;

   /**
    * Returns the length of the fixed area of the last view.
    *
    * @return the size in bytes.
    *
    */
   unsigned long getFixedLenBufSize( void ) const;

   /**
    * Get the number of repeat record in the last view.
    *
    * @return the number.
    *
    */
   unsigned long getNumRepeatRec( void ) const;

   /**
    * Gets the primary return code from AWD View. See AWD View docs.
    *
    * @return the return code.
    *
    */
   unsigned short getRcPrimary( void ) const;

   /**
    * Gets the Secondary return code from AWD View. See AWD View
    * docs.
    *
    * @return the return code.
    *
    */
   unsigned short getRcSecondary( void ) const;

   /**
    * Copy one specific repeat record into a buffer.
    *
    * @param ulRecordNumber - 1-based index.
    * @param pBuf - the buffer to receive the data
    * @param ulBufSize - the size of the buffer
    * @return true if some of the data was copied, false otherwise.
    */
   bool getRepeatRecord( unsigned long ulRecordNumber,
                         char * pBuf,
                         unsigned long ulBufSize ) const;

   /**
    * Get the size of a single repeat record from the last view.
    *
    * @return the number of bytes.
    *
    */
   unsigned long getRepeatRecSize( void ) const;

   /**
    * Call this to force VMRequest to parse the raw host response
    * into DST response format.  This method should be called before
    * any othe the other TA2000-specific methods are called (such as
    * getRepeatRecSize).
    *
    * @return NO_CONDITION if ok, otherwise a higher severity.
    * @exception ConditionException if AWD / View had an error.
    */
   SEVERITY getTA2000SpecificData();

   /**
    * Copy the view's repeat data into a buffer.
    *
    * @param  pBuf the buffer to copy the data into.
    * @param ulBufSize the size of the buffer
    * @return true if some or all of the data was copied. False otherwise.
    *
    */
   bool getVarData( unsigned char * pBuf,
                    unsigned long ulBufSize ) const;

   /**
    * Returns the size of the all of the repeats combined
    * from the last view.
    *
    * @return the size in bytes.
    *
    */
   unsigned long getVarLenBufSize( void ) const;

   /**
    * Get the return code sent from the host.  These are TA2000 return codes
    * like "OK", "DATA-NOT-FOUND", "SEVERE-ERROR".
    *
    * @return the return code
    *
    */
   unsigned short getViewReturnCode( void ) const;

   /**
    * Calls VmAppRequest
    *
    * @param sViewName - The view name. See AWD View docs.
    * @param sViewRequest
    *                  - The view request string. See AWD View docs.
    * @param dstrV002Pass
    *                  - The current user's password, only required if V002 headers
    *                  are used.
    * @param dstrV002NewPass
    *                  - The current user's password new, only required if V002 headers
    *                  are used, and the signon view is being sent to change the user's password.
    * @return true if primary AWD View return code is VM_P_OK,
    *         false otherwise.  This function may call user-defined
    *         callbacks.  If these callbacks add Conditions that are
    *         WARNING or less severity, it will promoted them.  If the
    *         severity is greater than WARNING, a ConditionException will
    *         be thrown.
    * @exception ConditionException
    *                   - DIBASE_VMAPPREQUEST_FAIL If the call to
    *                   VmAppRequest fails.
    * @exception ConditionException
    *                   - DIBASE_VMREADRESPONSE_FAIL If the call to
    *                   VmReadResponse fails.
    * @exception ConditionException
    *                   - DIBASE_VMREQUEST_WAIT_FAIL if AWD View times out
    * @exception ConditionException
    *                   - DIBASE_VMREQUEST_CALLBACK_CONDITIONEXCEPTION_THROWN
    *                   if either callback for send preprocessing (_fnSendPreprocess)
    *                   or for extracting the return data (_fnExtractOverride) throws
    *                   a ConditionException.
    * @exception ConditionException
    *                   - DIBASE_VMREQUEST_CALLBACK_UNKNOWN_EXCEPTION_THROWN
    *                   if either callback for send preprocessing (_fnSendPreprocess)
    *                   or for extracting the return data (_fnExtractOverride) throws
    *                   something other than a ConditionException.
    * @exception ConditionException
    *                   - DIBASE_VMREQUEST_CALLBACK_ERROR_CONDITION
    *                   if either callback for send preprocessing (_fnSendPreprocess)
    *                   or for extracting the return data (_fnExtractOverride) adds a
    *                   Condition with a serverity greater than warning.
    */
   bool send( const DStringA& sViewName,
              const DStringA& sViewRequest,
              const DString &dstrV002Pass = I_( "" ),
              const DString &dstrV002NewPass = I_( "" ) );

   /**
    * Calls VmAppRequest
    *
    * @param sViewName - The view name. See AWD View docs.
    * @param sViewRequest
    *                  - The view request string. See AWD View docs.
    * @param dstrV002Pass
    *                  - The current user's password, only required if V002 headers
    *                  are used.
    * @param dstrV002NewPass
    *                  - The current user's password new, only required if V002 headers
    *                  are used, and the signon view is being sent to change the user's password.
    * @return true if primary AWD View return code is VM_P_OK,
    *         false otherwise.  This function may call user-defined
    *         callbacks.  If these callbacks add Conditions that are
    *         WARNING or less severity, it will promoted them.  If the
    *         severity is greater than WARNING, a ConditionException will
    *         be thrown.
    * @exception ConditionException
    *                   - DIBASE_VMAPPREQUEST_FAIL If the call to
    *                   VmAppRequest fails.
    * @exception ConditionException
    *                   - DIBASE_VMREADRESPONSE_FAIL If the call to
    *                   VmReadResponse fails.
    * @exception ConditionException
    *                   - DIBASE_VMREQUEST_WAIT_FAIL if AWD View times out
    * @exception ConditionException
    *                   - DIBASE_VMREQUEST_CALLBACK_CONDITIONEXCEPTION_THROWN
    *                   if either callback for send preprocessing (_fnSendPreprocess)
    *                   or for extracting the return data (_fnExtractOverride) throws
    *                   a ConditionException.
    * @exception ConditionException
    *                   - DIBASE_VMREQUEST_CALLBACK_UNKNOWN_EXCEPTION_THROWN
    *                   if either callback for send preprocessing (_fnSendPreprocess)
    *                   or for extracting the return data (_fnExtractOverride) throws
    *                   something other than a ConditionException.
    * @exception ConditionException
    *                   - DIBASE_VMREQUEST_CALLBACK_ERROR_CONDITION
    *                   if either callback for send preprocessing (_fnSendPreprocess)
    *                   or for extracting the return data (_fnExtractOverride) adds a
    *                   Condition with a serverity greater than warning.
    */
   bool send( const DStringA& sViewName,
              const char *sViewRequest,
              const DString &dstrV002Pass = I_( "" ),
              const DString &dstrV002NewPass = I_( "" ) );

   /**
    * Calls VmAppRequest and allows you to specify a specific host
    * to target (instead of what AWD View's configuration
    * determines)
    *
    * @param sHostName The host name. See AWD View docs.
    * @param sViewRequest The view request string. See AWD View docs.
    * @param dstrV002Pass
    *                  - The current user's password, only required if V002 headers
    *                  are used.
    * @param dstrV002NewPass
    *                  - The current user's password new, only required if V002 headers
    *                  are used, and the signon view is being sent to change the user's password.
    * @return true if primary AWD View return code is VM_P_OK,
    *         false otherwise.  This function may call user-defined
    *         callbacks.  If these callbacks add Conditions that are
    *         WARNING or less severity, it will promoted them.  If the
    *         severity is greater than WARNING, a ConditionException will
    *         be thrown.
    * @exception ConditionException - DIBASE_VMAPPREQUEST_FAIL If the call to
    *        VmAppRequest fails.
    * @exception ConditionException - DIBASE_VMREADRESPONSE_FAIL If the call to
    *        VmReadResponse fails.
    * @exception ConditionException - DIBASE_VMREQUEST_WAIT_FAIL if AWD View times out
    * @exception ConditionException - DIBASE_VMREQUEST_CALLBACK_CONDITIONEXCEPTION_THROWN
    *        if either callback for send preprocessing (_fnSendPreprocess)
    *        or for extracting the return data (_fnExtractOverride) throws
    *        a ConditionException.
    * @exception ConditionException - DIBASE_VMREQUEST_CALLBACK_UNKNOWN_EXCEPTION_THROWN
    *        if either callback for send preprocessing (_fnSendPreprocess)
    *        or for extracting the return data (_fnExtractOverride) throws
    *        something other than a ConditionException.
    * @exception ConditionException - DIBASE_VMREQUEST_CALLBACK_ERROR_CONDITION
    *        if either callback for send preprocessing (_fnSendPreprocess)
    *        or for extracting the return data (_fnExtractOverride) adds a
    *        Condition with a serverity greater than warning.
    *
    */
   bool sendToHost( const DStringA& sHostName,
                    const DStringA& sViewRequesT,
                    const DString &dstrV002Pass = I_( "" ),
                    const DString &dstrV002NewPass = I_( "" ) );

   /**
    * Calls VmAppRequest and allows you to specify a specific host
    * to target (instead of what AWD View's configuration
    * determines)
    *
    * @param sHostName The host name. See AWD View docs.
    * @param sViewRequest The view request string. See AWD View docs.
    * @param dstrV002Pass
    *                  - The current user's password, only required if V002 headers
    *                  are used.
    * @param dstrV002NewPass
    *                  - The current user's password new, only required if V002 headers
    *                  are used, and the signon view is being sent to change the user's password.
    * @return true if primary AWD View return code is VM_P_OK,
    *         false otherwise.  This function may call user-defined
    *         callbacks.  If these callbacks add Conditions that are
    *         WARNING or less severity, it will promoted them.  If the
    *         severity is greater than WARNING, a ConditionException will
    *         be thrown.
    * @exception ConditionException - DIBASE_VMAPPREQUEST_FAIL If the call to
    *        VmAppRequest fails.
    * @exception ConditionException - DIBASE_VMREADRESPONSE_FAIL If the call to
    *        VmReadResponse fails.
    * @exception ConditionException - DIBASE_VMREQUEST_WAIT_FAIL if AWD View times out
    * @exception ConditionException - DIBASE_VMREQUEST_CALLBACK_CONDITIONEXCEPTION_THROWN
    *        if either callback for send preprocessing (_fnSendPreprocess)
    *        or for extracting the return data (_fnExtractOverride) throws
    *        a ConditionException.
    * @exception ConditionException - DIBASE_VMREQUEST_CALLBACK_UNKNOWN_EXCEPTION_THROWN
    *        if either callback for send preprocessing (_fnSendPreprocess)
    *        or for extracting the return data (_fnExtractOverride) throws
    *        something other than a ConditionException.
    * @exception ConditionException - DIBASE_VMREQUEST_CALLBACK_ERROR_CONDITION
    *        if either callback for send preprocessing (_fnSendPreprocess)
    *        or for extracting the return data (_fnExtractOverride) adds a
    *        Condition with a serverity greater than warning.
    *
    */
   bool sendToHost( const DStringA& sHostName,
                    const char *sViewRequest,
                    const DString &dstrV002Pass = I_( "" ),
                    const DString &dstrV002NewPass = I_( "" ) );

   /**
    * Calls VmAppRequest and allows you to specify a specific host
    * to target (instead of what AWD View's configuration
    * determines). Also allows you to specify a specific view name to be passed
    * to AWD / View on the VmAppRequest call.
    *
    * @param sHostName - The host name. See AWD View docs.
    * @param sViewName - The view name will be passed to AWD / View in the VmAppRequest call.
    * @param sViewRequest
    *                  - The view request string. See AWD View docs.
    * @param dstrV002Pass
    *                  - The current user's password, only required if V002 headers
    *                  are used.
    * @param dstrV002NewPass
    *                  - The current user's password new, only required if V002 headers
    *                  are used, and the signon view is being sent to change the user's password.
    * @return true if primary AWD View return code is VM_P_OK,
    *         false otherwise.  This function may call user-defined
    *         callbacks.  If these callbacks add Conditions that are
    *         WARNING or less severity, it will promoted them.  If the
    *         severity is greater than WARNING, a ConditionException will
    *         be thrown.
    * @exception ConditionException
    *                   - DIBASE_VMAPPREQUEST_FAIL If the call to
    *                   VmAppRequest fails.
    * @exception ConditionException
    *                   - DIBASE_VMREADRESPONSE_FAIL If the call to
    *                   VmReadResponse fails.
    * @exception ConditionException
    *                   - DIBASE_VMREQUEST_WAIT_FAIL if AWD View times out
    * @exception ConditionException
    *                   - DIBASE_VMREQUEST_CALLBACK_CONDITIONEXCEPTION_THROWN
    *                   if either callback for send preprocessing (_fnSendPreprocess)
    *                   or for extracting the return data (_fnExtractOverride) throws
    *                   a ConditionException.
    * @exception ConditionException
    *                   - DIBASE_VMREQUEST_CALLBACK_UNKNOWN_EXCEPTION_THROWN
    *                   if either callback for send preprocessing (_fnSendPreprocess)
    *                   or for extracting the return data (_fnExtractOverride) throws
    *                   something other than a ConditionException.
    * @exception ConditionException
    *                   - DIBASE_VMREQUEST_CALLBACK_ERROR_CONDITION
    *                   if either callback for send preprocessing (_fnSendPreprocess)
    *                   or for extracting the return data (_fnExtractOverride) adds a
    *                   Condition with a serverity greater than warning.
    */
   bool sendViewToHost( const DStringA& sHostName,
                        const DStringA& sViewName,
                        const DStringA& sViewRequest,
                        const DString &dstrV002Pass = I_( "" ),
                        const DString &dstrV002NewPass = I_( "" ) );

   /**
    * Calls VmAppRequest and allows you to specify a specific host
    * to target (instead of what AWD View's configuration
    * determines). Also allows you to specify a specific view name to be passed
    * to AWD / View on the VmAppRequest call.
    *
    * @param sHostName - The host name. See AWD View docs.
    * @param sViewName - The view name will be passed to AWD / View in the VmAppRequest call.
    * @param sViewRequest
    *                  - The view request string. See AWD View docs.
    * @param dstrV002Pass
    *                  - The current user's password, only required if V002 headers
    *                  are used.
    * @param dstrV002NewPass
    *                  - The current user's password new, only required if V002 headers
    *                  are used, and the signon view is being sent to change the user's password.
    * @return true if primary AWD View return code is VM_P_OK,
    *         false otherwise.  This function may call user-defined
    *         callbacks.  If these callbacks add Conditions that are
    *         WARNING or less severity, it will promoted them.  If the
    *         severity is greater than WARNING, a ConditionException will
    *         be thrown.
    * @exception ConditionException
    *                   - DIBASE_VMAPPREQUEST_FAIL If the call to
    *                   VmAppRequest fails.
    * @exception ConditionException
    *                   - DIBASE_VMREADRESPONSE_FAIL If the call to
    *                   VmReadResponse fails.
    * @exception ConditionException
    *                   - DIBASE_VMREQUEST_WAIT_FAIL if AWD View times out
    * @exception ConditionException
    *                   - DIBASE_VMREQUEST_CALLBACK_CONDITIONEXCEPTION_THROWN
    *                   if either callback for send preprocessing (_fnSendPreprocess)
    *                   or for extracting the return data (_fnExtractOverride) throws
    *                   a ConditionException.
    * @exception ConditionException
    *                   - DIBASE_VMREQUEST_CALLBACK_UNKNOWN_EXCEPTION_THROWN
    *                   if either callback for send preprocessing (_fnSendPreprocess)
    *                   or for extracting the return data (_fnExtractOverride) throws
    *                   something other than a ConditionException.
    * @exception ConditionException
    *                   - DIBASE_VMREQUEST_CALLBACK_ERROR_CONDITION
    *                   if either callback for send preprocessing (_fnSendPreprocess)
    *                   or for extracting the return data (_fnExtractOverride) adds a
    *                   Condition with a serverity greater than warning.
    */
   bool sendViewToHost( const DStringA& sHostName,
                        const DStringA& sViewName,
                        const char *sViewRequest,
                        const DString &dstrV002Pass = I_( "" ),
                        const DString &dstrV002NewPass = I_( "" ) );

   /**
    * Calls VmAppRequest and allows you to send a binary data stream.
    * Also allows you to specify a specific host
    * to target (instead of what AWD View's configuration
    * determines), also allows you to specify a specific view name to be passed
    * to AWD / View on the VmAppRequest call.
    *
    * @param sHostName - The host name. See AWD View docs.
    * @param sViewName - The view name will be passed to AWD / View in the VmAppRequest call.
    * @param uchViewRequest
    *                  - The view request string. See AWD View docs.
    * @param viewRequestLength
    *                  - The length of the view request buffer
    * @param dstrV002Pass
    *                  - The current user's password, only required if V002 headers
    *                  are used.
    * @param dstrV002NewPass
    *                  - The current user's password new, only required if V002 headers
    *                  are used, and the signon view is being sent to change the user's password.
    * @return true if primary AWD View return code is VM_P_OK,
    *         false otherwise.  This function may call user-defined
    *         callbacks.  If these callbacks add Conditions that are
    *         WARNING or less severity, it will promoted them.  If the
    *         severity is greater than WARNING, a ConditionException will
    *         be thrown.
    * @exception ConditionException
    *                   - DIBASE_VMAPPREQUEST_FAIL If the call to
    *                   VmAppRequest fails.
    * @exception ConditionException
    *                   - DIBASE_VMREADRESPONSE_FAIL If the call to
    *                   VmReadResponse fails.
    * @exception ConditionException
    *                   - DIBASE_VMREQUEST_WAIT_FAIL if AWD View times out
    * @exception ConditionException
    *                   - DIBASE_VMREQUEST_CALLBACK_CONDITIONEXCEPTION_THROWN
    *                   if either callback for send preprocessing (_fnSendPreprocess)
    *                   or for extracting the return data (_fnExtractOverride) throws
    *                   a ConditionException.
    * @exception ConditionException
    *                   - DIBASE_VMREQUEST_CALLBACK_UNKNOWN_EXCEPTION_THROWN
    *                   if either callback for send preprocessing (_fnSendPreprocess)
    *                   or for extracting the return data (_fnExtractOverride) throws
    *                   something other than a ConditionException.
    * @exception ConditionException
    *                   - DIBASE_VMREQUEST_CALLBACK_ERROR_CONDITION
    *                   if either callback for send preprocessing (_fnSendPreprocess)
    *                   or for extracting the return data (_fnExtractOverride) adds a
    *                   Condition with a serverity greater than warning.
    */
   bool sendViewToHost( const DStringA& sHostName,
                        const DStringA& sViewName,
                        const unsigned char *uchViewRequest,
                        unsigned long viewRequestLength,
                        const DString &dstrV002Pass = I_( "" ),
                        const DString &dstrV002NewPass = I_( "" ) );

   /**
    * Gets the returned data after one of the send() methods is called.  Use
    * this method only when this object instance has been constructed with the
    * DSTWINDOHANDLE constructor and only after the response message has been
    * posted back to the GUI window specified in the constructor.
    *
    * @return true if the view response data was obtained from AWD / View, false
    *         otherwise.
    */
   bool vmGetResponse();

   const DString & getSessionKey()
   {
      return _dstrSessionKey;
   }
   void setSessionKey( const DString & sessionKey )
   {
      _dstrSessionKey = sessionKey;
   }

// Private Methods
private:
   bool _SetPpbBuff (void);
   void _FreePbBuff (void);
   bool _vmConnect( void );
   bool _vmDisconnect( void );
   bool _vmNotify( void );
   bool _vmRequest( const DStringA& sHostName,
                    const DStringA& sViewName,
                    const unsigned char *pucViewRequest,
                    unsigned long ulRequestLength );
   bool _vmRequest( const DStringA& sHostName,
                    const DStringA& sViewName,
                    const DStringA& sViewRequest );
   void _assignAppName( void );
   bool _send( const DStringA& sHostName, const DStringA& sViewName,
               const DStringA& sViewRequest,
               const DString &dstrV002Pass,
               const DString &dstrV002NewPass );
   bool _send( const DStringA& sHostName, const DStringA& sViewName,
               const char *sViewRequest,
               const DString &dstrV002Pass,
               const DString &dstrV002NewPass );
   bool _send( const DStringA& sHostName, const DStringA& sViewName,
               const unsigned char *uchViewRequest,
               unsigned long viewRequestLength,
               const DString &dstrV002Pass,
               const DString &dstrV002NewPass );
   void _initVMRequest( unsigned long ulTimeout );


private: // attributes
   enum CONSTANTS { APP_MSG_SIZE = 1024 };

   bool             _fConnected;
   unsigned long    _ulTimeout;              // Seconds
   DStringA           _sAppName;
   DStringA           _sSemName;
   char             _szErrMsg[APP_MSG_SIZE+1];
   EventSemaphore * _pEventSemaphore;
   BYTE           * _pbBuff;
   BYTE           ** _ppbBuff;    // for implementations other than Win32
   VMDSTRESP        _vmResp;
   PVMAPPRESP      _pVmAppResp;
   DString         m_dstrV002;
   DString         _dstrSessionKey;

   pfnExtractOverride      _fnExtractOverride;
   pfnSendPreprocess       _fnSendPreprocess;

   DSTWINDOWHANDLE _hwndResponse;
   bool _fUsingHWND;
   unsigned long _ulMsg;
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
// $Log:   Y:/VCS/iFastAWD/inc/vmreq.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:33:22   kovacsro
//Initial revision.
// 
//    Rev 1.15   Sep 12 2001 16:53:14   DT11159
// Added code to support sending views directly to a
// destination rather than always using host routing.
// 
//
//    Rev 1.14   29 Nov 2000 12:18:30   dt14177
// cleanup
//
//    Rev 1.13   May 02 2000 13:15:30   dtwk
// Add support in TA2000DB for AWD / View VmNotifyWin interface
//
//    Rev 1.12   Jan 16 2000 14:08:44   dtwk
// Update comments in JavaDoc format
//
//    Rev 1.11   Dec 19 1999 09:28:50   dtwk
// Convert comments to JavaDoc format
//
//    Rev 1.10   Dec 09 1999 09:06:26   dtwk
// Add V002 Support
//
//    Rev 1.9   May 06 1999 16:48:08   DCYK
// Fixes for multi-byte and unicode.
//
//
//    Rev 1.8   Apr 20 1999 16:45:04   DCYK
// Only use regular chars for parameters.
//
//
//    Rev 1.7   Apr 19 1999 16:46:48   DCYK
// Fixes.
//
//
//    Rev 1.6   Mar 05 1999 10:22:14   DCYK
// Changes for I18N.
//
//
//    Rev 1.5   Feb 11 1999 15:01:02   DCYK
// Add support for binary elements.
// Add support for DSTCanada DataBroker.
//
//
//    Rev 1.4   Jan 28 1999 14:07:28   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.2   Dec 09 1998 13:43:52   DMUM
// Check in for DICORE
//
//    Rev 1.1   Aug 14 1998 14:48:52   DTWK
// Update comments
//
//    Rev 1.0   29 Jul 1998 20:38:32   DT14596
// DLMG New Archives for TA2000NTDT
//
//    Rev 1.11   Jun 08 1998 16:19:48   DTWK
// Allow view timeout lengths base on configuration variable.
// Make view timeout error message more user-friendly.
//
//    Rev 1.10   Nov 10 1997 12:39:32   DTWK
// Add support for specifying a host when sending a view.
//
//    Rev 1.9   Nov 09 1997 15:34:58   DTWK
// Add inclusion guards for faster compiles.
// Add guards so that class is flagged as exported only when compiling
// the output that actually exports the class.
//
//    Rev 1.8   Sep 10 1997 13:02:36   DTWK
// Add in Plantrac's Stratus header callback stuff.
//
//    Rev 1.7   Jul 07 1997 15:12:10   DTWK
//
//
//    Rev 1.6   Jun 13 1997 14:41:16   DTWK
// Add support for Condition class
//
//    Rev 1.5   Feb 18 1997 17:53:16   DPQD
// Removed #include "eventsemaphore.hpp" since it creates an unnecessary
// dependency, and replaced with a forward declaration of class EventSemaphore.
//
// Changed default constructor to accept timeout value.  Defaults to 30 seconds (what it was
// hardcoded for before) if none is passed.
//
// Removed extraneous enumeration constants.
//
// Added instance variable for timeout value.
//
// Changed semaphore name instance variable to use string class
// instead of char [].
//
// Removed unused instance variable _szReq.
//
// Added revision control comment block.
//
//

#endif // VMREQ_HPP
