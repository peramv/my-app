#ifndef TA2000DATABROKER_HPP
#define TA2000DATABROKER_HPP

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

/**@pkg DITA2KDB */

#pragma message( "including "__FILE__ )

#ifndef INCLUDED_IOSTREAM
#define INCLUDED_IOSTREAM
   #include <iostream>
#endif

#ifndef INCLUDED_MAP
#define INCLUDED_MAP
   #include <map>
#endif

#ifndef INCLUDED_STRING
#define INCLUDED_STRING
   #include <string>
#endif

#ifndef COMMONPORT_H
   #include "commonport.h"
#endif

#ifndef SYMBOLS_H
   #include "symbols.h"
#endif

#ifndef DATAPROPERTIES_HPP
   #include "dataproperties.hpp"
#endif

#ifndef DATA_HPP
   #include "data.hpp"
#endif

#ifndef EVENTSEMAPHORE_HPP
   #include "eventsemaphore.hpp"
#endif

#ifndef VIEWFRAME_HPP
   #include "viewframe.hpp"
#endif

#ifndef BASEDATABROKER_HPP
   #include "basedatabroker.hpp"
#endif

#ifndef SINGLETONREGISTER_HPP
   #include "singletonregister.hpp"
#endif

#undef DITA2KDB_LINKAGE
#ifdef DITA2KDB_DLL
   #define DITA2KDB_LINKAGE CLASS_EXPORT
#else
   #define DITA2KDB_LINKAGE CLASS_IMPORT
#endif


class VMRequest;

/**
 * A data broker handles requests to submit and receive Data objects.  The
 * DataBroker encapsulates the source and format of the data which it sends
 * and retrieves.  The data could potentially be retrieved from a local file,
 * a ViewManager view, or a SQL call.
 *
 * The data broker will also bundle (or batch) multiple Data objects into one
 * single submittal.  This will allow increased efficiency and failure support
 * for interdependent Data objects.
 *
 * The data broker will initially encapsulate the features of ViewManager.  By
 * encapsulating ViewManager, the DataBroker could potentially be reimplemented
 * if ViewManager is replaced.
 *
 * The data broker is implemented using the "Singleton" pattern.  Therefore,
 * there can only be one instance of TA2000DataBroker in existence at any time.
 * Also, getInstancePointer must be called before the TA2000DataBroker can be
 * used in any way.
 *
 * @author DST Systems Inc
 */
class DITA2KDB_LINKAGE TA2000DataBroker : BaseDataBroker
{
public:
   enum CONSTANTS {  LEN_OPERATOR_ID = 8,
                     LEN_SYSTEM      = 4,
                     LEN_VIEW_NAME   = 8,
                     DEFAULT_TIMEOUT = 90  };


public:

   /**
    * Gets a pointer to an instance of TA2000DataBroker.  This
    * function must be called before the TA2000DataBroker can be
    * used in any way.
    *
    * @return Returns a pointer to the single instance of TA2000DataBroker.
    *
    */
   static TA2000DataBroker * getInstance( void );

   /**
    * Make a call to TA2000 host using a pre-constructed ViewFrame.
    * The view call is run asynchronously from the caller.
    *
    * @param vf     - this object contains all of the view calls' required
    *               information.
    */
   void viewRequest( ViewFrame * vf );

   /**
    * Construct a ViewFrame and make a view call to TA2000 host.
    *
    * @param pViewName - the view data set name.
    * @param pViewParams
    *                  - an IDI string of the request parameters.
    * @param pRetrieveMode
    *                  - set the mode for the request: SYNCHRONOUS, DEMAND,
    *                  or COMPLETE.
    * @param fIsStratusHeader
    *                  - set to mark whether this  ViewFrame is using Stratus
    *                  headers.
    * @param pDemandNotify
    *                  - a pointer to a notify method to be called on demand.
    * @param pCompletionNotify
    *                  - a pointer to a notify method to be called when
    *                  the request is completed.
    * @param phObject - the object handle is used by the caller to keep track of
    *                 who gets the response data.
    * @param pViewTimeout
    *                  - the timeout for a single view call
    * @param pCompleteTimeout
    *                  - timeout for all viewcalls
    * @param fnSendPreprocess
    *                  - a callback to preprocess any data before it is
    *                  formatted and sent to the host
    * @param fnExtractOverride
    *                  - a callback to preprocess any data before it is
    *                  formatted by TA2000Databroker after returning
    *                  from the host.
    * @param _handleError
    *                  - a callback funtion for errors
    * @param _handleSevereError
    *                  - a callback function for severe errors
    * @param fPrependSystem
    *               - set to false to not prepend the system id (i.e. MFB) to
    *               the request data stream.  Set this to true if the request
    *               dataset has System_Id as the first field, or if the request
    *               string actually does not use the system.  The system id is
    *               retrieved from TA2000Security, which is set by the call to
    *               TA2000Security::setActiveAuthorization.
    * @param strHostName
    *                  - a specific host to which the view should be sent.
    * @return a newly created ViewFrame object that either contains or will
    *         contain the response from the TA2000 host
    */
   ViewFrame * viewRequest(
      const DString             &pViewName,
      const DString             &pViewParms,
      ViewFrame::RETRIEVE_MODES pRetrieveMode = ViewFrame::SYNCHRONOUS,
      bool                      fIsStratusHeader = false,
      _CALLBACK                 pDemandNotify = NULL,
      _CALLBACK                 pCompletionNotify = NULL,
      unsigned int              phObject = 0,
      unsigned long             pViewTimeout = ViewFrame::DEFAULT_VIEW_TIMEOUT,
      unsigned long             pCompleteTimeout = ViewFrame::DEFAULT_COMPLETE_TIMEOUT,
      pfnSendPreprocess         fnSendPreprocess = NULL,
      pfnExtractOverride        fnExtractOverride = NULL,
      ViewFrameErrorHandler     errorHandler = defaultErrorHandler,
      ViewFrameErrorHandler     severeErrorHandler = defaultSevereErrorHandler,
      bool                      fPrependSystem = true,
      const DString             &strHostName = I_("")
      );

   /**
    * Construct a ViewFrame and make a view call to TA2000 host.
    *
    * @param pViewName - the view data set name.
    * @param dataParams
    *                  - a Data object containin the request parameters.
    * @param pRetrieveMode
    *                  - set the mode for the request: SYNCHRONOUS, DEMAND,
    *                  or COMPLETE.
    * @param fIsStratusHeader
    *                  - set to mark whether this  ViewFrame is using Stratus
    *                  headers.
    * @param pDemandNotify
    *                  - a pointer to a notify method to be called on demand.
    * @param pCompletionNotify
    *                  - a pointer to a notify method to be called when
    *                  the request is completed.
    * @param phObject - the object handle is used by the caller to keep track of
    *                 who gets the response data.
    * @param pViewTimeout
    *                  - the timeout for a single view call
    * @param pCompleteTimeout
    *                  - timeout for all viewcalls
    * @param fnSendPreprocess
    *                  - a callback to preprocess any data before it is
    *                  formatted and sent to the host
    * @param fnExtractOverride
    *                  - a callback to preprocess any data before it is
    *                  formatted by TA2000Databroker after returning
    *                  from the host.
    * @param _handleError
    *                  - a callback funtion for errors
    * @param _handleSevereError
    *                  - a callback function for severe errors
    * @param fPrependSystem
    *               - set to false to not prepend the system id (i.e. MFB) to
    *               the request data stream.  Set this to true if the request
    *               dataset has System_Id as the first field, or if the request
    *               string actually does not use the system.  The system id is
    *               retrieved from TA2000Security, which is set by the call to
    *               TA2000Security::setActiveAuthorization.
    * @param strHostName
    *                  - a specific host to which the view should be sent.
    * @return a newly created ViewFrame object that either contains or will
    *         contain the response from the TA2000 host
    */
   ViewFrame * viewRequest(
      const DString             &pViewName,
      const Data                &dataParams,
      ViewFrame::RETRIEVE_MODES pRetrieveMode = ViewFrame::SYNCHRONOUS,
      bool                      fIsStratusHeader = false,
      _CALLBACK                 pDemandNotify = NULL,
      _CALLBACK                 pCompletionNotify = NULL,
      unsigned int              phObject = 0,
      unsigned long             pViewTimeout = ViewFrame::DEFAULT_VIEW_TIMEOUT,
      unsigned long             pCompleteTimeout =ViewFrame::DEFAULT_COMPLETE_TIMEOUT,
      pfnSendPreprocess         fnSendPreprocess = NULL,
      pfnExtractOverride        fnExtractOverride = NULL,
      ViewFrameErrorHandler     errorHandler = defaultErrorHandler,
      ViewFrameErrorHandler     severeErrorHandler = defaultSevereErrorHandler,
      bool                      fPrependSystem = true,
      const DString             &strHostName = I_("")
      );

   /**
    * Makes a call to TA2000 and returns the received data.
    *
    * @param sViewName - (in) string containing the view name.
    * @param parmsData - (in) Data object containing the parameters to
    *                  pass in the view call.
    * @param receivedData
    *                  - (out) Data object that will be filled up with the
    *                  information returned from the view call.
    * @param overwriteFixedArea
    *                  - (in) if true, specifies that if the
    *                  receivedData object already has repeats, then the fixed area
    *                  from the Data object that is received from ViewManager will
    *                  be overwritten on the fixed area of receivedData.
    * @param sHostName - use this to override the DST View default configuration and
    *                  send the view to a non-default host
    * @return Returns the highest severity level of any condition raised.
    *         CONDITIONS: DITA2KDB_CANT_READ_DATA_FILE
    *         DITA2KDB_NOT_LOGGED_IN
    *         DITA2KDB_VMREQUEST_SEND_FAILED
    *         DITA2KDB_VM_THREW
    *         DITA2KDB_VM_ERROR
    *         DITA2KDB_VM_MORE_DATA
    *         DITA2KDB_UNKNOWN_ERROR
    *         DITA2KDB_DATA_NOT_FOUND
    *         DITA2KDB_INVALID_VIEW
    *         DITA2KDB_SYSTEM_ID_ERROR
    *         DITA2KDB_SYSTEM_DOWN
    *         DITA2KDB_MAX_IO_LIMIT
    *         DITA2KDB_STS_ERROR
    *         DITA2KDB_INVALID_DATA_REQUEST
    *         DITA2KDB_INVALID_FUND_CODE
    *         DITA2KDB_INVALID_ACCT_NUM
    *         DITA2KDB_INVALID_DATE
    *         DITA2KDB_INVALID_CERT_NUM
    *         DITA2KDB_INVALID_DEALER_NUM
    *         DITA2KDB_INVALID_DEALER_BRANCH
    *         DITA2KDB_INVALID_TAX_ID_NUM
    *         DITA2KDB_INVALID_ALPHA_CODE
    *         DITA2KDB_INVALID_BANK_MICR_ID
    *         DITA2KDB_INVALID_REQUEST_CNT
    *         DITA2KDB_INVALID_RES_STATE_CODE
    *         DITA2KDB_INVALID_DEBIT_CARD
    *         DITA2KDB_INVALID_DEBIT_TYPE
    *         DITA2KDB_INVALID_LOI_NUM
    *         DITA2KDB_INVALID_TRANS_NUM
    *         DITA2KDB_NO_UPDATES_TO_APPLY
    *         DITA2KDB_CHANGED_BY_DIFF_OPER
    *         DITA2KDB_MGMT_CO_NOT_FOUND
    *         DITA2KDB_INVALID_OPER_ID
    *         DITA2KDB_INVALID_PASSWORD
    *         DITA2KDB_NOT_SIGNED_ON
    *         DITA2KDB_NOT_AUTHORIZED
    *         DITA2KDB_TRANS_BACKED_OUT
    *         DITA2KDB_INVALID_DATA
    *         DITA2KDB_ALREADY_SIGNED_ON
    *         DITA2KDB_RECORD_UNAVAIL
    *         DITA2KDB_DLR_NOT_AUTHORIZED
    *         DITA2KDB_PASSWORD_EXPIRED
    *         DITA2KDB_PASSWORD_TOO_SIMILAR
    *         DITA2KDB_OPER_DISABLED
    *         DITA2KDB_POTENTIAL_DUPLICATE
    *         DITA2KDB_SYSTRAN_AGR_EXIST
    *         DITA2KDB_SYSTRAN_INSTR_EXIST
    *         DITA2KDB_SYSTRAN_NO_P47
    *         DITA2KDB_SYSTRAN_SEVERE_ERROR
    *         DITA2KDB_SEVERE_ERROR
    *         DITA2KDB_INVALID_ACCUM_YEARS
    *         DITA2KDB_INVALID_START_YEAR
    *         DITA2KDB_INVALID_START_MONTH
    *         DITA2KDB_INVALID_ARRAY_ROWS
    *         DITA2KDB_INVALID_REIN_DOLLAR
    *         DITA2KDB_INVALID_DSCS_APPREC
    *         DITA2KDB_INVALID_FRONT_END
    *         DITA2KDB_INVALID_REIN_SHARES
    *         DITA2KDB_INVALID_FID_ACCOUNT
    *         DITA2KDB_INVALID_PAF_BUCKET
    *         DITA2KDB_INVALID_FUNCTION_TYPE
    *         DITA2KDB_B08_RECORD_NOT_FOUND
    *         DITA2KDB_NO_UPDATE_DETECTED
    *         DITA2KDB_INVALID_PRE_AGREEMENT
    *         DITA2KDB_INVALID_PST_AGREEMENT
    *         DITA2KDB_INVALID_PURCH_CANCEL
    *         DITA2KDB_INVALID_REDMPT_CANCEL
    *         DITA2KDB_INVALID_EXCH_PUR_CANC
    *         DITA2KDB_INVALID_EXCH_RED_CANC
    *         DITA2KDB_INVALID_MONTHLY_ACCUM
    *         DITA2KDB_TAF_NOT_EQUAL_MASTER
    *         DITA2KDB_S0_MASTER_NOT_FOUND
    *         DITA2KDB_RECORD_ALREADY_EXIST
    *         DITA2KDB_B07_REC_NOT_FOUND
    *         DITA2KDB_AUDIT_FILE_BAD_OPEN
    *         DITA2KDB_AUDIT_REC_NOT_WRITTEN
    *         DITA2KDB_F16_REC_NOT_FOUND
    *         DITA2KDB_F17_REC_NOT_FOUND
    *         DITA2KDB_B06_REC_NOT_FOUND
    *         DITA2KDB_INVALID_DLR_BRN_SEC
    *         DITA2KDB_OPER_NOT_AUTH_DEALER
    *         DITA2KDB_OPER_NOT_AUTH_DLR_BR
    *         DITA2KDB_INVALID_DLR_SUMMARY
    *         DITA2KDB_INVALID_DLR_BR_SUMMARY
    *         DITA2KDB_INVALID_BATCH_NUM
    *         DITA2KDB_NO_A53_FOR_VERIFY_DTE
    *         DITA2KDB_INVALID_PRICE
    *         DITA2KDB_DEL_REC_NOT_FOUND
    *         DITA2KDB_NO_A53_DUMMY_REC
    *         DITA2KDB_A58_REC_NOT_FOUND
    *         DITA2KDB_INVALID_YIELD_DATE
    *         DITA2KDB_CURR_A79_NOT_DEL
    *         DITA2KDB_CHG_REC_NOT_FOUND
    *         DITA2KDB_INVALID_NET_CHG
    *         DITA2KDB_NO_A79_FOR_VERIFY_DTE
    *         DITA2KDB_NO_A56_REC_FOUND
    *         DITA2KDB_INVALID_CUMDISC
    *         DITA2KDB_INVALID_CUMDISC_PLAN
    *         DITA2KDB_RETURN_ACCT_EXISTS
    *         DITA2KDB_RETURN_NASU_ACCT
    *         DITA2KDB_INVALID_CORR_CODE
    *         DITA2KDB_INVALID_MGMT_CODE
    *         DITA2KDB_INVALID_MF_TRAN_ID
    *         DITA2KDB_A52_REC_NOT_FOUND
    *         DITA2KDB_A52_INFO_UNAVAIL
    *         DITA2KDB_A87_REC_NOT_FOUND
    *         DITA2KDB_A87_INFO_UNAVAIL
    *         DITA2KDB_A58_INFO_UNAVAIL
    *         DITA2KDB_A90_REC_NOT_FOUND
    *         DITA2KDB_A90_INFO_UNAVAIL
    *         DITA2KDB_DEFAULT_VALUE_USED
    *         DITA2KDB_B15_REC_NOT_FOUND
    *         DITA2KDB_B15_INFO_UNAVAIL
    *         DITA2KDB_RETURN_VIEW_ERROR
    *         DITA2KDB_RETURN_WITH_ERRORS
    *         DITA2KDB_RETURN_INFO_UNAVAIL
    *         DITA2KDB_CANT_INIT_VIEW_THREAD
    * @exception ConditionException&
    *                   - if the request is an update, and the
    *                   system is not MFL, MFA or MFD.
    *                   ConditionException& - if an allocation failed.
    */
   SEVERITY receive( const DStringA &sViewName,
                     const Data &parmsData,
                     Data &receivedData,
                     bool overwriteFixedArea,
                     const DStringA &sHostName = "" );

   /**
    * Makes a call to TA2000 and returns the received data.
    *
    * @param sViewName - (in) string containing the view name.
    * @param sParms - (in) string containing the parameters to pass in
    *               the view call.
    * @param receivedData
    *                  - (out) Data object that will be filled up with the
    *                  information returned from the view call.
    * @param overwriteFixedArea
    *                  - (in) if true, specifies that if the
    *                  receivedData object already has repeats, then the fixed area
    *                  from the Data object that is received from ViewManager will
    *                  be overwritten on the fixed area of receivedData.
    * @param sHostName - use this to override the DST View default configuration and
    *                  send the view to a non-default host
    * @return Returns the highest severity level of any condition raised.
    *         CONDITIONS  : See above
    * @exception ConditionException
    *                   - if the request is an update, and the
    *                   system is not MFL, MFA or MFD.
    *                   ConditionException& - if an allocation failed.
    */
   SEVERITY receive( const DStringA &sViewName,
                     const DString& sParms,
                     Data &receivedData,
                     bool overwriteFixedArea = true,
                     const DStringA &sHostName = "" );

   /**
    * Makes a call to TA2000 and returns the received data.
    *
    * @param sViewName - (in) string containing the view name.
    * @param receivedData
    *                  - (out) Data object that will be filled up with the
    *                  information returned from the view call.
    * @param overwriteFixedArea
    *                  - (in) if true, specifies that if the
    *                  receivedData object already has repeats, then the fixed area
    *                  from the Data object that is received from ViewManager will
    *                  be overwritten on the fixed area of receivedData.
    * @param sHostName - use this to override the DST View default configuration and
    *                  send the view to a non-default host
    * @return Returns the highest severity level of any condition raised.
    *         CONDITIONS  : See above
    * @exception ConditionException
    *                   - if the request is an update, and the
    *                   system is not MFL, MFA or MFD.
    *                   ConditionException& - if an allocation failed.
    */
   SEVERITY receive( const DStringA &sViewName,
                     Data &receivedData,
                     bool overwriteFixedArea = true,
                     const DStringA &sHostName = "" );

   /**
    * Makes a call to TA2000 and returns the received data.
    *
    * @param sViewName - (in) string containing the view name.
    * @param sendData - a data object whose fields are the request parameters
    * @param receivedData
    *                  - (out) Data object that will be filled up with the
    *                  information returned from the view call.
    * @return Returns the highest severity level of any condition raised.
    *         CONDITIONS  : See above
    * @exception ConditionException
    *                   - if the request is an update, and the
    *                   system is not MFL, MFA or MFD.
    *                   ConditionException& - if an allocation failed.
    */
   SEVERITY receive( const DStringA &sViewName,
                     const Data &sendData,
                     Data &receivedData );

   /**
    * Makes a call to TA2000 and returns the received data.
    *
    * @param sViewName - (in) string containing the view name.
    * @param sendData - a data object whose fields are the request parameters
    * @param receivedData
    *                  - (out) Data object that will be filled up with the
    *                  information returned from the view call.
    * @param pSecurity - pointer to a security object.  This parameter is present
    *                  in order to satify out the BaseDataBroker polymorphic interface,
    *                  and is ignored inside of TA2000DataBroker.
    * @return Returns the highest severity level of any condition raised.
    *         CONDITIONS  : See above
    * @exception ConditionException
    *                   - if the request is an update, and the
    *                   system is not MFL, MFA or MFD.
    *                   ConditionException& - if an allocation failed.
    */
   SEVERITY receive( const DString &sViewName,
                     const Data &sendData,
                     Data &receivedData,
                     BaseDBSecurity *pSecurity );

#ifdef DST_UNICODE
   /**
    * Makes a call to TA2000 and returns the received data.
    *
    * @param sViewName - (in) string containing the view name.
    * @param sendData - a data object whose fields are the request parameters
    * @param receivedData
    *                  - (out) Data object that will be filled up with the
    *                  information returned from the view call.
    * @param pSecurity - pointer to a security object.  This parameter is present
    *                  in order to satify out the BaseDataBroker polymorphic interface,
    *                  and is ignored inside of TA2000DataBroker.
    * @return Returns the highest severity level of any condition raised.
    *         CONDITIONS  : See above
    * @exception ConditionException
    *                   - if the request is an update, and the
    *                   system is not MFL, MFA or MFD.
    *                   ConditionException& - if an allocation failed.
    */
   SEVERITY receive( const DStringA &sViewName,
                     const Data &sendData,
                     Data &receivedData,
                     BaseDBSecurity *pSecurity )
   {
      return receive( sViewName, sendData, receivedData );
   }
#endif

   /**
    * Makes a call to TA2000 and returns the received data.
    *
    * @param vf     - a ViewFrame object with all of the information needed to
    *               make the request to TA2000 host.
    * @param receivedData
    *               - (out) Data object that will be filled up with the
    *               information returned from the view call.
    * @param overwriteFixedArea
    *               - (in) if true, specifies that if the
    *               receivedData object already has repeats, then the fixed area
    *               from the Data object that is received from ViewManager will
    *               be overwritten on the fixed area of receivedData.
    * @return Returns the highest severity level of any condition raised.
    *         CONDITIONS  : See above
    * @exception ConditionException
    *                   - if the request is an update, and the
    *                   system is not MFL, MFA or MFD.
    *                   ConditionException& - if an allocation failed.
    */
   SEVERITY receive( ViewFrame &vf, Data &receivedData,
                     bool overwriteFixedArea = true );

   /**
    * Makes a call to TA2000 and returns the received data.
    *
    * @param vf     - a ViewFrame object with all of the information needed to
    *               make the request to TA2000 host.
    * @param parms  - an IDI string of the request parameters.
    * @param receivedData
    *               - (out) Data object that will be filled up with the
    *               information returned from the view call.
    * @param overwriteFixedArea
    *               - (in) if true, specifies that if the
    *               receivedData object already has repeats, then the fixed area
    *               from the Data object that is received from ViewManager will
    *               be overwritten on the fixed area of receivedData.
    * @return Returns the highest severity level of any condition raised.
    *         CONDITIONS  : See above
    * @exception ConditionException
    *                   - if the request is an update, and the
    *                   system is not MFL, MFA or MFD.
    *                   ConditionException& - if an allocation failed.
    */
   SEVERITY receive( ViewFrame &vf, DString &parms, Data &receivedData,
                     bool overwriteFixedArea = true );

   /**
    * Makes a call to TA2000 and returns immediately, without the received data.
    * When the message, ulMsg, is posted back to hwndRecipient, call
    * getResponse() to get the data returned from the host.
    *
    * The combination of hwndRecipient and ulMsg MUST be uniqe for each
    * view that is currently being processed by AWD / View
    *
    * @param hwndRecipient
    *                  - the window that will listen for a message (ulMsg) as
    *                  notifcation of the view's completion.
    *
    * @param ulMsg     - the message that will be posted to hwndRecipient
    * @param sViewName - (in) string containing the view name.
    * @param parmsData - a data object whose fields are the request parameters
    * @return Returns the highest severity level of any condition raised.
    *         CONDITIONS  : See above
    * @exception ConditionException
    *                   - if the request is an update, and the
    *                   system is not MFL, MFA or MFD.
    *                   ConditionException& - if an allocation failed.
    */
   SEVERITY receive( DSTWINDOWHANDLE hwndRecipient,
                     unsigned long ulMsg,
                     const std::string &sViewName,
                     const Data &parmsData );

   /**
    * Get the data returned from the host.  This method should be called only
    * after:
    *       1) calling receive( DSTWINDOWHANDLE hwndRecipient,
    *                           unsigned long ulMsg,
    *                           const std::string &sViewName,
    *                           const Data &parmsData );
    *       2) hwndRecipient had the notification message (ulMsg) posted to it
    *
    * The combination of hwndRecipient and ulMsg MUST be uniqe for each
    * view that is currently being processed by AWD / View
    *
    * @param hwndRecipient
    *                  - the window that was listening for a message (ulMsg) as
    *                  notifcation of the view's completion (and has recieved
    *                  that message)
    *
    * @param ulMsg     - the message that was posted to hwndRecipient
    * @param receivedData
    *               - (out) Data object that will be filled up with the
    *               information returned from the view call.
    * @param overwriteFixedArea
    *               - (in) if true, specifies that if the
    *               receivedData object already has repeats, then the fixed area
    *               from the Data object that is received from ViewManager will
    *               be overwritten on the fixed area of receivedData.
    * @return Returns the highest severity level of any condition raised.
    *         CONDITIONS  : See above
    * @exception ConditionException
    *                   - if the request is an update, and the
    *                   system is not MFL, MFA or MFD.
    *                   ConditionException& - if an allocation failed.
    */
   SEVERITY getResponse( DSTWINDOWHANDLE hwndRecipient,
                         unsigned long ulMsg,
                         Data &receivedData,
                         bool overwriteFixedArea = true );

   /**
    * Lower the count of views currently running.
    */
   inline void decViewCount( void );

   /**
    * Determie whether TA2000DataBroker is waiting for its view
    * to complete so that it can shut down.
    *
    * @return true if waiting to shut down, false otherwise.
    */
   inline bool getDBStatus( void );

   /**
    * Increment the count of views currently running on this object.
    */
   inline void incViewCount( void );

   /**
    * Get the next set of records specified by the passed-in
    * ViewFrame object.
    *
    * @param ViewFrame - this object contains all the needed information to request
    *                  the next set of records from TA2000 host.
    */
   void performMoreProcessing( ViewFrame &vf );

   /**
    * Set a callback that will be invoked before all requests to the
    * host.
    */
   void setPreprocessCallback( pfnSendPreprocess );

   /**
    * Set a callback that will be invoked before any response from
    * the host is parsed.
    */
   void setExtractCallback( pfnExtractOverride );

   /**
    * Unused / not implemented.
    */
   void setErrorHandler( ViewFrameErrorHandler );

   /**
    * Unused / not implemented.
    */
   void setSevereErrorHandler( ViewFrameErrorHandler );

private:

   static void killInstance( void );
   static void deregister( void *pObj )
   {
      TA2000DataBroker *pTA = ( TA2000DataBroker * )pObj;
      pTA->killInstance();
   }

   unsigned long getErrorCode( unsigned short viewRC );
   unsigned long _getWS00221ErrorCode( VMRequest &viewRequest,
                                       long &lWS00221Error,
                                       DString &dstrLocation );

   SEVERITY receive( const DStringA& sViewName,
                     const char *uchParms,
                     unsigned long parmLength,
                     Data &receivedData,
                     bool overwriteFixedArea = true,
                     const DStringA &sHostName = "",
                     DSTWINDOWHANDLE hwndRecipient = NULL,
                     unsigned long ulMsg = 0,
                     bool fUsingHWND = false );


   typedef std::map< DString, Data, std::less< DString > > DataMap;
   DataMap _buffers;

   pfnSendPreprocess _sendPreprocess;
   pfnExtractOverride _extractOverride;

   ViewFrameErrorHandler _errorHandler;
   ViewFrameErrorHandler _severeErrorHandler;

   unsigned long _ulViewCount;
   bool _fDBisDead;
   bool _directConnect;
//   RWSTDMutex TA2000DataBrokerMutex;    // this private version used for inc and dec of _ulViewCount for this instance
                              // exported version in cpp used in static methods initInstance and killInstance -- LP
   TA2000DataBroker();
   TA2000DataBroker( const TA2000DataBroker &copy );
   ~TA2000DataBroker();
   TA2000DataBroker &operator=( const TA2000DataBroker &copy );

   static void initInstance (TA2000DataBroker *p);

   inline void append( Data &data, ViewFrame &vf );
   inline void completion_actions( ViewFrame &vf );
   inline void demand_actions( ViewFrame &vf );
   inline void demand_count( ViewFrame &vf );
   inline void kill_actions( ViewFrame &vf );

   SingletonRegister m_register;

   class winnotifyID
   {
   public:
      DSTWINDOWHANDLE m_hwnd;
      unsigned long m_ulMsg;

      bool operator<( const winnotifyID &other ) const
      {
         if ( m_hwnd < other.m_hwnd )
         {
            return true;
         }
         else if ( m_hwnd == other.m_hwnd )
         {
            if ( m_ulMsg < other.m_ulMsg )
            {
               return true;
            }
         }
         return false;
      };
   };

   typedef std::map< winnotifyID, VMRequest *, std::less< winnotifyID > >
      mapWinNotifyType;

   mapWinNotifyType mapWinNotify;
   MutexSemaphore m_mutexWinNotify;
   SEVERITY _getResponse( VMRequest *pVMRequest,
                          Data &receivedData,
                          bool overwriteFixedArea,
                          bool fUsingHWND );
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
// $Log:   Y:/VCS/iFastAWD/inc/ta2000databroker.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:32:54   kovacsro
//Initial revision.
// 
//    Rev 1.23   Sep 12 2001 16:53:06   DT11159
// Added code to support sending views directly to a
// destination rather than always using host routing.
// 
//
//    Rev 1.22   Mar 03 2001 14:01:38   dt24433
// Fixes for UNICODE build.
//
//    Rev 1.21   28 Nov 2000 11:06:20   dt14177
// cleanup
//
//    Rev 1.20   28 Nov 2000 10:53:36   dt14177
// cleanup
//
//    Rev 1.19   Sep 05 2000 06:12:50   dt17817
// - Remove Certificate/Authenticator
// - Fix threadsafety of client/market
// - Add "null" property value support
//
//
//    Rev 1.18   Sep 01 2000 08:06:02   DT21858
// Host is now a parameter when using ViewFrame
//
//    Rev 1.17   May 02 2000 13:15:24   dtwk
// Add support in TA2000DB for AWD / View VmNotifyWin interface
//
//    Rev 1.16   Mar 28 2000 14:34:16   dtwk
// - Use SingletonRegister to manage lifetime of TA2000DataBroker and TA2000Security
// - Make threadsafe
//
//    Rev 1.15   Feb 23 2000 16:48:28   dtwk
// Add parameter to tell TA2KDB to prepend the target system
// on the request data stream
//
//    Rev 1.14   Feb 17 2000 12:06:02   dtwk
// Fix for WS00221 error codes
//
//    Rev 1.13   Jan 26 2000 17:29:46   dtwk
// Sync with 1.7 - add an overload to viewRecieve that
// takes the request params as a Data object instead of
// an IDI string
//
//
//    Rev 1.12   Jan 16 2000 14:08:30   dtwk
// Update comments in JavaDoc format
//
//    Rev 1.11   Dec 19 1999 09:28:40   dtwk
// Convert comments to JavaDoc format
//
//    Rev 1.10   Dec 14 1999 12:25:04   dtwk
// Setup polymorphic interface
//
//    Rev 1.9   Nov 30 1999 08:51:54   dtwk
// Overwrite 1700 branch version checked in on trunk
//
//    Rev 1.7   Nov 30 1999 08:11:46   dtwk
// Add support for WS00221 return codes
//
//    Rev 1.6   Apr 21 1999 16:50:00   DCYK
// Updates for Unicode.
//
//
//    Rev 1.5   Mar 05 1999 10:22:00   DCYK
// Changes for I18N.
//
//
//    Rev 1.4   Feb 11 1999 15:42:00   DCYK
// Add support for binary DataElements.
//
//
//    Rev 1.3   Jan 28 1999 14:07:02   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.1   Dec 09 1998 13:43:30   DMUM
// Check in for DICORE
//
//    Rev 1.17   May 20 1998 14:07:56   dcyk
// Change default timeout.
//
//
//    Rev 1.16   Nov 10 1997 15:02:44   dcyk
//
//
//    Rev 1.15   01 Oct 1997 15:24:22   dcyk
// Additional PlanTrac changes for callbacks
// and getting severity.
//
//
//    Rev 1.14   24 Sep 1997 13:43:44   dcyk
// Added additional PlanTrac functionality.
//
//
//    Rev 1.13   10 Sep 1997 12:10:58   dcyk
// Made changes for PlanTrac.
// Async view calls & more processing.
//
//
//    Rev 1.12   07 Aug 1997 15:09:36   dcyk
// Change USHORT, ULONG, UCHAR & UINT
// back to long forms for compatability.
//
//
//    Rev 1.11   24 Jul 1997 10:54:58   dcyk
// Removed coutErrorCode function.
//
//
//    Rev 1.10   08 Jul 1997 09:16:38   dcyk
// Updated documentation.
//
//
//    Rev 1.9   13 Jun 1997 18:24:54   dcyk
// Made receive return a bool.
// Added condition stuff.
//
//
//    Rev 1.8   Jun 08 1997 18:47:42   DTWK
// Add Certificate Authentication / Remove dependencies on class Returncode.
//
//    Rev 1.7   05 Jun 1997 18:07:02   dcyk
// Changed default behavior of receive
// function to overwrite the fixed area of
// data objects passed in that already have
// repeat records.
//
//
//    Rev 1.6   May 29 1997 09:57:52   dcyk
// Add support for appending newly received
// repeats to the repeat area of the Data object
// passed in to the receive functions.
//
//
//    Rev 1.5   May 01 1997 08:47:42   dcyk
// Removed extra receive & update methods.
//
// Added documentation.
//
//
//    Rev 1.4   Mar 14 1997 15:29:12   DPQD
// Made destructor private since it's a singleton.
//
//    Rev 1.3   Feb 11 1997 17:20:50   dcyk
// Added support for Rogue Wave STL.
//
//
//    Rev 1.2   Jan 15 1997 17:28:32   dcyk
// Modified receive functions to return a long,
// that is -1 on failure to communicate with
// VM, 0 on success, or > 0 if the view return
// code is between 900 and 1000.
//
// COUT on view call errors ( 900 < rc < 1000 ).
//
//
//    Rev 1.1   Jan 07 1997 09:34:08   dcyk
// Added overloaded receive function
// that takes a string view name and
// a Data object that holds the parms.
//
//
//    Rev 1.0   Dec 31 1996 11:39:34   DRUS
//
//

#endif // TA2000DataBroker_hpp