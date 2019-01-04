#ifndef VIEWFRAME_HPP
#define VIEWFRAME_HPP

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

/**@pkg DITA2KDB */

#pragma message( "including "__FILE__ )

#ifndef VMREQ_HPP
   #include "vmreq.hpp"
#endif

#undef DITA2KDB_LINKAGE
#ifdef DITA2KDB_DLL
   #define DITA2KDB_LINKAGE CLASS_EXPORT
#else
   #define DITA2KDB_LINKAGE CLASS_IMPORT
#endif

/**@#-*/
class EventSemaphore;
class TA2000DataBroker;

class ViewFrame;

extern "C"
{
typedef void ( __cdecl * _CALLBACK )( void * );
typedef void ( __cdecl * ViewFrameErrorHandler ) ( ViewFrame *vf );
}
/**@#+*/


/**
 * Used to handle errors
 * 
 * @param vf
 * @return 
 */
void DITA2KDB_LINKAGE __cdecl defaultErrorHandler( ViewFrame *vf );

/**
 * Used to handle severe errors
 * 
 * @param vf
 * @return 
 */
void DITA2KDB_LINKAGE __cdecl defaultSevereErrorHandler( 
                                                 ViewFrame *vf );

/**
 * This class is a framework used in conjunction with TA2000DataBroker to
 * make view requests.  It supports synchronous and asynchronous view
 * requests, complete data retrieval, early data access, retrieval
 * interruption, retrieval on demand, timeout configuration, demand
 * notification, and completion notification.  The caller can send an
 * object handle to enable it to determine which view completed.
 *
 * Scenario example: caller kicks off two asynchronous views.  One is a
 * lookup which will run on demand.  The demand will occur when the last
 * data item is displayed in the list box.  The other view retrieves the
 * complete database for the view needed for a particular window.  In the
 * middle of the view, the user changes to another window and the data is
 * no longer needed.  The view (running in a thread) will then be terminated
 * by the program.  If allowed to run, the view would have called the
 * completion notification callback function (which could have been in a
 * class other than the caller).
 *
 * SPECIAL HANDLING
 *
 * delete: the pointer to a ViewFrame object created by
 *         TA2000DataBroker::viewRequest()
 *
 *         the pointer to a Data object which receives the view response
 *         data
 *
 * @author DST Systems Inc
 * @deprecated This functionality will be integrated directly into the
 *             TA2000DataBroker object.
 */
class DITA2KDB_LINKAGE ViewFrame
{
public:

   enum CONSTANTS
   {
      INDEFINITE_WAIT = 0xFFFFFFFFL,
      DEFAULT_VIEW_TIMEOUT = 30L,
      DEFAULT_COMPLETE_TIMEOUT = 120000L   // 2 minutes
   };

   enum RETRIEVE_MODES
   {
      SYNCHRONOUS,
      DEMAND,
      COMPLETE
   };

   /**
    * Construct a ViewFrame to be used in a synchronous view.
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
    */
   ViewFrame(
      const DString        & pViewName,
      const DString        & pViewParms,
      RETRIEVE_MODES         pRetrieveMode = SYNCHRONOUS,
      bool                   fIsStratusHeader = false,
      _CALLBACK              pDemandNotify = NULL,
      _CALLBACK              pCompletionNotify = NULL,
      unsigned int           phObject = 0,
      unsigned long          pViewTimeout = DEFAULT_VIEW_TIMEOUT,
      unsigned long          pCompleteTimeout = DEFAULT_COMPLETE_TIMEOUT,
      pfnSendPreprocess      fnSendPreprocess = NULL,
      pfnExtractOverride     fnExtractOverride = NULL,
      ViewFrameErrorHandler  _handleError = defaultErrorHandler,
      ViewFrameErrorHandler  _handleSevereError = defaultSevereErrorHandler,
      bool                   fPrependSystem = true,
      const DString        & strHostName = I_("")
      );

   /**
    * Construct a ViewFrame to be used in a synchronous view.
    *
    * @param pViewName - the view data set name.
    * @param dataParams
    *                  - an data object containing the request parameters.
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
    */
   ViewFrame(
      const DString        & pViewName,
      const Data           & dataParms,
      RETRIEVE_MODES         pRetrieveMode = SYNCHRONOUS,
      bool                   fIsStratusHeader = false,
      _CALLBACK              pDemandNotify = NULL,
      _CALLBACK              pCompletionNotify = NULL,
      unsigned int           phObject = 0,
      unsigned long          pViewTimeout = DEFAULT_VIEW_TIMEOUT,
      unsigned long          pCompleteTimeout = DEFAULT_COMPLETE_TIMEOUT,
      pfnSendPreprocess      fnSendPreprocess = NULL,
      pfnExtractOverride     fnExtractOverride = NULL,
      ViewFrameErrorHandler  _handleError = defaultErrorHandler,
      ViewFrameErrorHandler  _handleSevereError = defaultSevereErrorHandler,
      bool                   fPrependSystem = true,
      const DString        & strHostName = I_("")
      );
   ~ViewFrame();

   /**
    * Operates in demand mode to retrieve the next set of records.
    */
   inline void doNextView( void );

   /**
    * Determine if this ViewFrame is set to be working with Stratus
    * data streams.
    *
    * @return true if yes, false otherwise.
    */
   inline bool getfIsStratusHeader(void) const;

   /**
    * The timeout has to do with the time to complete view calls
    * to retrieve the entire data set.
    *
    * @return the timeout in milliseconds.
    *
    */
   inline unsigned long getCompleteTimeout( void ) const;

   /**
    * Get a pointer to the Completion Notify callback function.
    * The Completion Notify callback function is invoked when a view
    * completes.
    *
    * @return a pointer to the Completion Notify callback function.
    *
    */
   inline const ::_CALLBACK getCompletionNotify( void ) const;

   /**
    * Get a pointer to the Demand Notify callback function.
    * The Demand Notify callback function is invoked when a view
    * retrieves a set of records.
    *
    * @return a pointer to the Demand Notify callback function.
    *
    */
   inline const ::_CALLBACK getDemandNotify( void ) const;

   /**
    * Get the object handle is used by the caller to keep track of
    * who gets the response data.
    *
    * @return an implementation dependent handle
    *
    */
   inline unsigned int getObjectHandle( void ) const;

   /**
    * Determine if the system (i.e. MFB) will be prepended onto
    * the request data stream by TA2000DataBroker.  The system
    * is obtained from TA2000Security, and is set in the security
    * object by a call to TA2000Security::setActiveAuthorization().
    *
    * @return true is the system will be prepended, false otherwise
    */
   inline bool getPrependSystem( void ) const;

   /**
    * Get a Data object that contains the host's response.  It is up to the
    * caller to correctly manage the lifetime of the returned object.
    *
    * @return the view receive object.
    */
   inline Data * getReceive( void ) const;

   /**
    * Get the current retrieve mode.
    *
    * @return 0 - synchronous, 1 - asynchronous demand,
    *         2 - asynchronous completion
    */
   inline unsigned int getRetrieveMode( void ) const;

   /**
    * Get the severity of the last view call.
    *
    * @return the SEVERITY.
    */
   inline SEVERITY getSeverity( void ) const;

   /**
    * Get the frame for this object. Appears to be unused.
    *
    * @return the Condition frame.
    */
   Frame * getFrame() const { return _frame; }

   /**
    * Used with demand processing; returns the starting index of the
    * last set of records retrieved.
    *
    * @return the start index (0-based)
    *
    */
   inline unsigned int getStartIndexOfLastRetrieval( void ) const;

   /**
    * Get the view name.
    *
    * @return the view name passed in the construction of this object.
    *
    */
   inline const DString & getViewName( void ) const;

   /**
    * Get the host name.
    *
    * @return the host name passed in the construction of this object.
    *
    */
   inline const DString & getHostName( void ) const;

   /**
    * Get the string containing the key fields for the view.
    *
    * @return an IDI string of paramaters and their values.
    *
    */
   inline DString & getViewParms( void ) const;

   /**
    * the timeout has to do with the view call;
    *
    * @return the timeout in milliseconds
    *
    */
   inline unsigned long getViewTimeout( void ) const;

   /**
    * Get an implementation-defined handle for this object.  This
    * might be useful in callback functions.
    *
    * @return an implementation defined handle.
    */
   inline HANDLE getHandle( void ) const;

   /**
    * Used to kill an asynch view -- demand or complete
    *
    */
   inline void killView( void );

   // sets
   /**
    * Set the timeout to complete view calls to retrieve the entire data set.
    *
    * @param the timeout in milliseconds.
    *
    */
   inline void setCompleteTimeout( unsigned long pCompleteTimeout );

   /**
    * Set the CALLBACK function which will be called when the
    * view completes in TA2000DataBroker;
    *
    * @param user-defined callback.
    *
    */
   inline void setCompletionNotify( const _CALLBACK pCompletionNotify );

   /**
    * Sets the CALLBACK function which will be called when the
    * view retrieves a set of records in TA2000DataBroker;
    *
    * @param user-defined callback.
    *
    */
   inline void setDemandNotify( const _CALLBACK pDemandNotify );

   /**
    * Set aThe object handle is used by the caller to keep track of
    * who gets the response data.
    *
    * @param - the object
    *
    */
   inline void setObjectHandle( unsigned int phObject );

   /**
    * Set the received Data object.
    *
    * @param pReceive view receive object
    *
    */
   inline void setReceive( Data * pReceive );

   /**
    * Set the retrieve mode.
    *
    * @param pRetrieveMode -  0: synchronous, 1: asynchronous demand
    *        2: asynchronous completion
    *
    */
   inline void setRetrieveMode( unsigned int pRetrieveMode );

   /**
    * Set the view name
    *
    * @param pViewName - the name used to create the response Data object
    *
    */
   inline void setViewName( const DString & pViewName );

   /**
    * Set the host name
    *
    * @param strHostName - the name of the host to which the view is to be sent
    *
    */
   inline void setHostName( const DString & strHostName );

   /**
    * Sets the string buffer containing the key fields for the view;
    *
    * @param pViewParms - an IDI string with the view parameters.
    *
    */
   inline void setViewParms( const DString & pViewParms );

   /**
    * The timeout has to do with the view call;
    *
    * @param pTimeout - the timeout in milliseconds
    *
    */
   inline void setViewTimeout( unsigned long pViewTimeout );

   /**
    * Set a handle.  This is not used internally, but might be
    * useful for callbacks.
    *
    * @param h      - the handle.
    */
   inline void setHandle( HANDLE h );

   /**
    * Wait for completion of views.
    */
   inline void wait( void );

private:

   friend TA2000DataBroker;

   // no default constructor, copy constructor or assignment operator
   ViewFrame();
   ViewFrame( const ViewFrame & parm );
   ViewFrame & operator = ( const ViewFrame & parm );

   inline EventSemaphore * getCompletionSem( void ) const;
   inline EventSemaphore * getDemandSem( void ) const;
   inline           Data * getRequestKey( void ) const;

   void initViewFrame( const DString       & pViewName,
                       RETRIEVE_MODES        pRetrieveMode,
                       bool                  fIsStratusHeader,
                       _CALLBACK             pDemandNotify,
                       _CALLBACK             pCompletionNotify,
                       unsigned int          phObject,
                       unsigned long         pViewTimeout,
                       unsigned long         pCompleteTimeout,
                       pfnSendPreprocess     fnSendPreprocess,
                       pfnExtractOverride    fnExtractOverride,
                       ViewFrameErrorHandler errHandler,
                       ViewFrameErrorHandler severeErrorHandler );

   inline void setStartIndexOfLastRetrieval( unsigned int );

   //**********************
   // data
   //**********************

   bool             _fIsStratusHeader; // are we using stratus header
   _CALLBACK        _completionNotify; // this function pointer is called
                                       // by TA2000DataBroker::viewRequest()
                                       // when the view completes
   _CALLBACK        _demandNotify;     // this function pointer is called
                                       // by TA2000DataBroker::viewRequest()
                                       // when the view completes

   pfnSendPreprocess  _fnSendPreprocess;
   pfnExtractOverride _fnExtractOverride;

   DString          _viewName;
   DString          _viewParms;         // key field buffer for the view
   Data           * _receive;           // view response data is put here
                                        //   Data( _viewName );
   Data           * _requestKey;
   bool             _termination;       // used to terminate a retriever
                                        //   view thread; if not passed in,
                                        //   this semaphore will be created
   EventSemaphore * _demand;            // this is used to signal a
                                        //   demand for more data ;
                                        //   if not passed in, the
                                        //   semaphore will be created
   EventSemaphore * _complete;          // this is used to signal
                                        //   completion of data retrieval;
                                        //   if not passed in, the
                                        //   semaphore will be created
   unsigned int     _hObject;           // meaning defined by the CBO
   unsigned int     _retrieveMode;      // 0: synchronous
                                        // 1: asynchronous demand
                                        // 2: asynchronous completion
                                        // 3: asynchronous notify
                                        //    when data is available
   unsigned long    _viewTimeout;       // individual view
   unsigned long    _completeTimeout;   // complete all retrieval views

   unsigned int     _startIndexOfLastRetrieval;
   bool             _fPrependSystem;    // Tell TA2000DataBroker to prepend the
                                        // system onto the request data stream.
                                        // The system is pulled from
                                        // TA2000Security, and is set in there
                                        // by a call to
                                        // TA2000Security::setApplication
   DString          _strHostName;       // The name of a specific host to which
                                        // the view should be sent

   Frame           *_frame;
   TID              _threadId;
   PID              _processId;
   HANDLE           _handle;

   ViewFrameErrorHandler _handleError;
   ViewFrameErrorHandler _handleSevereError;

   SEVERITY         _severity;
};


inline void ViewFrame::doNextView( void )
{
   if ( ( _demand ) && (_termination == false) )
   {
      _demand->post();
   }
}

inline bool ViewFrame::getfIsStratusHeader(void) const
{
    return _fIsStratusHeader;
}


inline unsigned long ViewFrame::getCompleteTimeout( void ) const
{
    return _completeTimeout;
}


inline const::_CALLBACK ViewFrame::getCompletionNotify( void ) const
{
    return _completionNotify;
}


inline const::_CALLBACK ViewFrame::getDemandNotify( void ) const
{
    return _demandNotify;
}


inline unsigned int ViewFrame::getObjectHandle( void ) const
{
    return _hObject;
}


inline bool ViewFrame::getPrependSystem( void ) const
{
   return _fPrependSystem;
}


inline Data * ViewFrame::getReceive( void ) const
{
    return _receive;
}


inline unsigned int ViewFrame::getRetrieveMode( void ) const
{
    return _retrieveMode;
}


inline unsigned int ViewFrame::getStartIndexOfLastRetrieval( void ) const
{
    return _startIndexOfLastRetrieval;
}


inline const DString & ViewFrame::getViewName( void ) const
{
    return ( const DString & ) _viewName;
}


inline const DString & ViewFrame::getHostName( void ) const
{
    return _strHostName;
}


inline DString & ViewFrame::getViewParms( void ) const
{
    return ( DString & ) _viewParms;
}


inline unsigned long ViewFrame::getViewTimeout( void ) const
{
    return _viewTimeout;
}


inline HANDLE ViewFrame::getHandle( void ) const
{
    return _handle;
}


inline SEVERITY ViewFrame::getSeverity( void ) const
{
   return _severity;
}


inline void ViewFrame::killView( void )
{
    _termination = true;

   if ( _demand )
   {
      _demand->post();
   }

}


inline void ViewFrame::setCompleteTimeout( unsigned long pCompleteTimeout )
{
    _completeTimeout = pCompleteTimeout;
}


inline void ViewFrame::setCompletionNotify( const ::_CALLBACK pCompletionNotify )
{
    _completionNotify = pCompletionNotify;
}


inline void ViewFrame::setDemandNotify( const ::_CALLBACK pDemandNotify )
{
    _demandNotify = pDemandNotify;
}


inline void ViewFrame::setViewName( const DString & pViewName )
{
    _viewName = pViewName;
}


inline void ViewFrame::setHostName( const DString & strHostName )
{
    _strHostName = strHostName;
}


inline void ViewFrame::setViewParms( const DString & pViewParms )
{
    _viewParms = pViewParms;
}


inline void ViewFrame::setViewTimeout( unsigned long pViewTimeout )
{
    _viewTimeout = pViewTimeout;
}


inline void ViewFrame::setHandle( HANDLE h )
{
    _handle = h;
}


inline void ViewFrame::setObjectHandle( unsigned int phObject )
{
    _hObject = phObject;
}


inline void ViewFrame::setReceive( Data * pReceive )
{
    _receive = pReceive;
}


inline void ViewFrame::setRetrieveMode( unsigned int pRetrieveMode )
{
    _retrieveMode = pRetrieveMode;
}


inline void ViewFrame::wait( void )
{
    if ( _complete )
    {
        _complete->wait();
    }
}


inline EventSemaphore * ViewFrame::getCompletionSem( void ) const
{
   return _complete;
}


inline EventSemaphore * ViewFrame::getDemandSem( void ) const
{
   return _demand;
}


inline Data * ViewFrame::getRequestKey( void ) const
{
    return _requestKey;
}


inline void ViewFrame::setStartIndexOfLastRetrieval( unsigned int pIndex )
{
    _startIndexOfLastRetrieval = pIndex;
}



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
// $Log:   Y:/VCS/iFastAWD/inc/viewframe.hpp-arc  $
//
//   Rev 1.0   28 Jan 2008 13:33:20   kovacsro
//Initial revision.
// 
//    Rev 1.10   29 Nov 2000 12:12:54   dt14177
// cleanup
// 
//    Rev 1.9   Sep 01 2000 08:06:04   DT21858
// Host is now a parameter when using ViewFrame
//
//    Rev 1.8   May 10 2000 14:16:42   DT14177
// added forward declaration for EventSemaphore
//
//    Rev 1.7   Feb 23 2000 16:48:30   dtwk
// Add parameter to tell TA2KDB to prepend the target system
// on the request data stream
//
//    Rev 1.6   Jan 26 2000 17:29:50   dtwk
// Sync with 1.7 - add an overload to viewRecieve that
// takes the request params as a Data object instead of
// an IDI string
//
//
//    Rev 1.5   Jan 16 2000 14:08:40   dtwk
// Update comments in JavaDoc format
//
//    Rev 1.4   Dec 19 1999 09:28:48   dtwk
// Convert comments to JavaDoc format
//
//    Rev 1.3   Mar 05 1999 10:22:12   DCYK
// Changes for I18N.
//
//
//    Rev 1.2   Jan 28 1999 14:07:26   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.1   Dec 09 1998 13:43:50   DMUM
// Check in for DICORE
//
//    Rev 1.4   Nov 10 1997 15:02:42   dcyk
// Add inclusion guards for faster compiles.
// Add guards so that class is flagged as exported only when compiling
// the output that actually exports the class.
//
//
//    Rev 1.3   01 Oct 1997 15:24:34   dcyk
// Additional PlanTrac changes for callbacks
// and getting severity.
//
//
//    Rev 1.2   24 Sep 1997 13:44:20   dcyk
// Added additional PlanTrac functionality.
//
//
//    Rev 1.1   Sep 10 1997 13:35:32   DTWK
// Add revision control entries

#endif //_VIEWFRAME_HPP_