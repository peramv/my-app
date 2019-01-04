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

#ifndef DEBUGMGR_HPP
   #include <debugmgr.hpp>
#endif

// DISABLE_TRACING when defined removes tracing from debug programs
// ENABLE_TRACING when defined (by default for debug) adds tracing to debug programs
#ifdef _DEBUG
   #ifndef DISABLE_TRACING
      #define ENABLE_TRACING
   #endif
#endif


/**
 * Tracing class as member variable to provide tracing to classes.
 *
 * Class provides tracing capabilities to a implementing class and classes
 * derived from the implementing class.  Macros are provided to allow for
 * easy and consistant access to the use of the class.
 *
 * An implementing class would do the following:
 * <pre>
 * // These examples assume ASCII build.
 * //   Please refer to the Infrastructure Unicode Manual for UNICODE tracing examples
 *
 * // Add trace class as member variable
 * private:
 *    TRACER_CLASS_VARIABLE;
 *
 * // Add to constructor
 * TestClass::TestClass( int valueIn )
 * {
 *    TRACER_CONSTRUCTOR( "TestClass( int )"  );
 *
 * // Add to member function
 * void PrintData( long controlValueIn )
 * {
 *    TRACER_METHOD( "PrintData( long )" );
 *
 * // Add a tracing message (class specific content)
 * ...
 * DString resultString = errorCode + returnCodeStr;
 * TRACER_MESSAGE( resultString );
 *
 * // Add to destructor
 * None needed.  Message output when tracer class member variable is
 *  deleted on class destruction
 * </pre>
 */
class DICORE_LINKAGE TracerClient
{

public:

   /**
    * Constructor for such purposes as changing the state
    * of the global trace flag
    */
   TracerClient();

   /**
    * Constructor that saves class name to be used in
    * later trace statements
    *
    * @param classNameIn
    *               Class name
    */
   TracerClient(const DString& classNameIn);

   /**
    * Generates trace destructor statement when
    * used as a class memeber variable
    */
   virtual ~TracerClient();

   /**
    * Save the class name where the trace class is a memeber variable.
    *  It is provided in the constructor and saved for use in all member and
    *  message trace class calls
    *
    * @param classNameIn
    *               Reference to class name.
    */
   inline void setClassName(const DString& classNameIn)
   {
      _className = classNameIn;
   }

   /**
    * Function used inside class constructor.
    * The class name is extracted from the constructor
    * prototype and saved use in later method and message
    * tracing statements.
    *
    * @param classNameIn
    *               Prototype of constructor
    *               TestClass::TestClass( int valueIn, DString& nameIn)
    *               would have a prototype of (one standard)
    *               "TestClass( int, DString& )"
    */
   void logCreate(const DString& classNameIn);

   /**
    * Function used by trace class destructor to provide
    * destructor trace call.
    */
   void logDestroy();

   /**
    * Function called to send method trace statement
    * The method statement will include any class name
    * provided by the logCreate
    *
    * @param methodNameIn
    *               Method prototype to be inserted into method trace statement
    *               void TestClass::func1( long someNumberIn )
    *               The method prototype ( one standard)
    *               "func1( long )"
    */
   void logMethod(const DString& methodNameIn);

   /**
    * Function provides message to be inserted into tracing
    * statement
    *
    * @param messageIn Message to be inserted
    */
   void logMessage(const DString& messageIn);

   /**
    * Function that causes a trace statement even when
    * all tracing flags are turned off.
    *
    * @param errorMessageIn
    *               Message to be inserted
    */
   void logError(const DString& errorMessageIn);

   /**
    * Turns on class level debugging.
    * This allows for class info debugging to be sent
    * to tracing even when global tracing is turned off.
    * If global tracing is off and one instance of a class
    * has class tracing turned on, only that one instance
    * of a class will send tracing statements
    *
    * @param classTracingIn
    *               Sets the current value for this instance of class tracing
    */
   void setClassTracing(bool classTracingIn);

   /**
    * Sets the value of the global tracing flag
    *
    * @param globalTracingIn
    *               Value to set the global tracing flag
    */
   void setGlobalTracing(bool globalTracingIn)
   {
      if( NULL != _debugManager )
      {
         _debugManager -> setTracing(globalTracingIn);
      }
   }

   /**
    * Returns tracing state (true / false)
    * This is a combination of global and class level tracing
    *
    * @return Trace value for instance of class
    */
   inline bool isTracing() const
   {
      return( NULL == _debugManager ? false : _debugManager -> isTracing() | _classLevelTracing );
   }

   /**
    * Function needed to support old tracing style macros.
    * This function should not be used.
    *
    * @param supportOldTracing
    *               Sets which version of tracing macros are being used
    */
   inline void setSupportOldTracing(bool supportOldTracing)
   {
      _supportOldTracing = supportOldTracing;
   }


private:

   void init();

   // Pointer to the debug manager stored in the global object
   DebugMgr *_debugManager;

   DString _className;

   long _threadId;
   long _processId;

   bool _classLevelTracing;

   bool _supportOldTracing;


};

// Current version of tracing macros
// Define macros only when tracing is turned on at compile time
#ifdef ENABLE_TRACING

/**
 * Macro provides trace class member variable
 * See TracerClient coding example
 */
   #define TRACER_CLASS_VARIABLE \
   TracerClient tracerClient;

/**
 * Macro used in class constructor
 * See TracerClient coding example
 */
   #define TRACER_CONSTRUCTOR( constructorSignature ) \
   if (tracerClient.isTracing() ) \
   { \
      tracerClient.logCreate( constructorSignature); \
   }

/**
 * Macro used in class method
 * See TracerClient coding example
 */
   #define TRACER_METHOD( methodSignature ) \
   if ( tracerClient.isTracing() ) \
   { \
      tracerClient.logMethod( methodSignature ); \
   }

/**
 * Macro used in class code to send message
 * See TracerClient coding example
 */
   #define TRACER_MESSAGE( message) \
   if ( tracerClient.isTracing() ) \
   { \
      tracerClient.logMessage( message ); \
   }

/**
 * Error message sent to tracing ( ignore tracing flags)
 * See TracerClient coding example
 */
   #define TRACER_ERROR( message) \
   { \
      tracerClient.logError( message ); \
   }

#else

   #define TRACER_CLASS_VARIABLE
   #define TRACER_CONSTRUCTOR( constructorSignature )
   #define TRACER_METHOD( methodSignature )
   #define TRACER_MESSAGE( message)
   #define TRACER_ERROR( message)

#endif



// Old version of tracing marcros
//  Should only be used by old code for compile purposes while converting to
//   new tracing macros
#ifdef ENABLE_TRACING


   #define TRACE_CONSTRUCTOR( classname, signature ) \
   { \
      TracerClient tracerClient; \
      if (tracerClient.isTracing() ) \
      { \
         tracerClient.setSupportOldTracing( true); \
         tracerClient.logCreate( classname); \
      } \
   }


   #define TRACE_DESTRUCTOR( classname ) \
   { \
      TracerClient tracerClient(classname); \
   }

   #define TRACE_METHOD( classname, methodsignature ) \
   { \
      TracerClient tracerClient(classname); \
      if ( tracerClient.isTracing() ) \
      { \
         tracerClient.setSupportOldTracing( true); \
         tracerClient.logMethod( methodsignature ); \
      } \
   }

   #define TRACE_MSG( msg ) \
   { \
      TracerClient tracerClient; \
      if ( tracerClient.isTracing() ) \
      { \
         tracerClient.setSupportOldTracing( true); \
         tracerClient.logMessage( msg ); \
      } \
   }

   #define TRACE_CLASS_MSG( classname, methodsignature, msg ) \
   { \
      TracerClient tracerClient( classname); \
      if ( tracerClient.isTracing() ) \
      { \
         tracerClient.setSupportOldTracing( true); \
         tracerClient.logMessage( msg ); \
      } \
   }


#else

//NO TRACING
   #define TRACE_CONSTRUCTOR( classname, signature )
   #define TRACE_DESTRUCTOR( classname )
   #define TRACE_METHOD( classname, methodsignature )
   #define TRACE_MSG( msg )
   #define TRACE_CLASS_MSG( classname, methodsignature, msg )

#endif

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   //db3n5j11/d/scc/ifds/core/archives/ifdscore/tracerclient.hpp-arc  $
//
//   Rev 1.1   Oct 09 2002 17:42:20   PURDYECH
//New PVCS Database
//
//   Rev 1.0   Jul 05 2002 10:15:18   SMITHDAV
//Initial revision.
// 
//    Rev 1.16   28 Nov 2000 15:00:50   dt14177
// cleanup
// 
//    Rev 1.15   Apr 05 2000 14:14:34   DMUM
// Part of Larry Code removeal
//
//    Rev 1.14   13 Jan 2000 14:12:04   dt20842
// Updated JavaDoc comments
//
//    Rev 1.13   Jan 04 2000 13:17:04   DT20842
// Added more JavaDoc comments
//
//    Rev 1.12   Dec 29 1999 10:42:48   DT20842
// Added package comment line
//
//    Rev 1.11   Dec 27 1999 11:56:14   DT20842
//
//
//    Rev 1.10   Dec 16 1999 07:36:12   DT20842
// Better fix for blank destructor messages
//
//    Rev 1.8   Nov 24 1999 08:19:34   DMUM
// Removed #include for "debugmethodtrace.hpp" since
// that class is not implemented and the header is basically
// a dead archive.
//
//    Rev 1.7   Aug 09 1999 14:09:34   DMUM
// Added the ability to build in debug mode with
// tracing disabled.
//
//    Rev 1.6   Apr 26 1999 15:12:24   DTWK
// change boolean to bool
//
//    Rev 1.5   Apr 19 1999 12:49:14   DT20842
// Fixed release TRACER macros
//
//    Rev 1.4   Apr 16 1999 13:12:34   DT20842
// Added new tracing
//
//    Rev 1.3   18 Feb 1999 10:40:18   DT14177
// UNICODE
//
//    Rev 1.2   Jan 28 1999 14:07:12   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.1   Dec 09 1998 13:43:40   DMUM
// Check in for DICORE
//
//    Rev 1.7   Jun 17 1998 15:27:12   dt27994
// Added compiler switch "ENABLE_TRACING".
//
//    Rev 1.6   Jun 17 1998 08:19:00   dt27994
//
//
//    Rev 1.5   Jun 16 1998 16:13:34   dt27994
// Removed old tracing code and modified existing.
//
//    Rev 1.4   Mar 25 1998 14:44:54   DTWK
//
//
//    Rev 1.3   Nov 09 1997 15:34:52   DTWK
// Add inclusion guards for faster compiles.
// Add guards so that class is flagged as exported only when compiling
// the output that actually exports the class.
//
//    Rev 1.2   Oct 21 1997 14:06:04   dkaw
// add traceMessage, traceBeginEnd, TRACE_MSG_FORMATTED
//
//    Rev 1.1   Sep 08 1997 15:50:32   dkaw
// add SET_TRACEAPP, remove parm from getConfigurationValues
//
//    Rev 1.0   Jul 22 1997 09:45:14   dkaw
//
//
