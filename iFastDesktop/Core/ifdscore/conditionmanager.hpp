#pragma once

/** 
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

#ifndef INCLUDED_SYMBOLS
#define INCLUDED_SYMBOLS
#include <symbols.h>
#endif

#ifndef COMMONTEMPLATES_H
   #include <commontemplates.h>
#endif

#ifndef CONDITIONMIGRATE_HPP
   #include <conditionmigrate.hpp>
#endif

#ifndef DEBUGMGR_HPP
   #include <debugmgr.hpp>
#endif

#ifndef FRAME_HPP
   #include <frame.hpp>
#endif

#ifndef SINGLETONREGISTER_HPP
   #include <singletonregister.hpp>
#endif

#ifndef TRACERCLIENT_HPP
   #include <TracerClient.hpp>
#endif

#ifndef INCLUDED_FSTREAM
#define INCLUDED_FSTREAM
#include <fstream>
#endif

#define ASSERTS_ENABLED

#ifndef CRTDBG_H_INCLUDED
#define CRTDBG_H_INCLUDED
#include <crtdbg.h>
#endif

#ifndef INCLUDED_VECTOR
#define INCLUDED_VECTOR
#include <vector>
#endif

#ifndef WIN32
   #define _ASSERT(a)
   #define _ASSERTE(a)
#endif

typedef std::vector<Frame *> FRAMEVECTOR;

/**
 * Token placed between class and method name
 */
static I_CHAR colon[] = I_( "::" );

#undef DICORE_LINKAGE
#ifdef DICORE_DLL
   #define DICORE_LINKAGE CLASS_EXPORT
#else
   #define DICORE_LINKAGE CLASS_IMPORT
#endif

/**
 * Manage frames which contain conditions.
 * startFrame creates a new frame for conditions as each new method
 * begins.  endFrame flags the frame as finished processing, which
 * causes any lower level frames to be deleted.
 *
 * ConditionManager is interfaced through macros
 *
 *
 *
 * <B> Macro examples: </B>
 *
 * <PRE>
 *
 *  #include <iostream>
 *
 *  #include "configmanager.hpp"
 *  #include "conditionmanager.hpp"
 *
 *
 *  #include "conditiontest_conditions.hpp"
 *
 *
 *  using namespace std;
 *
 *
 *     This example demonstrates using the Condition component. Its purpose is to
 *     to show how to create and access Conditions and ConditionExceptions.
 *
 *     This code below consists of a class, ConditionTest, that has three
 *     methods: conditionMethod(). conditionMethod2(). conditionExceptionMethod().
 *     The first three methods add conditions as return codes, while the last method
 *     use a condition as an exception.  The main() will create a ConditionTest
 *     object and invoke its methods.  Next it will display any Conditions returned
 *     by conditionMethod().  Finally, it will invoke conditionExceptionMethod()
 *     and display the ConditionException returned.
 *
 *
 *
 *
 *
 *  class ConditionTest
 *  {
 *  public:
 *
 *     ConditionTest();
 *
 *     ~ConditionTest();
 *
 *     SEVERITY conditionMethod();
 *
 *     SEVERITY conditionMethod2();
 *
 *     void conditionExceptionMethod();
 *  };
 *
 *
 *
 *  ConditionTest::ConditionTest()
 *  {
 *     MAKEFRAME( "ConditionTest", "ConditionTest::ConditionTest()" )
 *
 *     // Add code to create a condition with tag CONDITIONTEST_CONDITION_MESSAGE
 *     ADDCONDITIONFROMFILE( CONDITIONTEST_CONDITION_MESSAGE )
 *  }
 *
 *
 *  ConditionTest::~ConditionTest()
 *  {
 *  }
 *
 *
 *  SEVERITY ConditionTest::conditionMethod()
 *  {
 *
 *     // Make a frame for the conditions to use (otherwise you will get compile
 *     // errors)
 *     MAKEFRAME( "ConditionTest", "ConditionTest::conditionMethod()" );
 *
 *     // Also, CONDITIONTEST_CONDITION_MESSAGE2 should take a string parameter. Pass
 *     // in "BOB"
 *     ADDCONDITIONFROMFILEIDI( CONDITIONTEST_CONDITION_MESSAGE2, "VAR1=BOB" )
 *
 *     // Call a method that will add a condition on the stack one level above ours
 *     conditionMethod2();
 *
 *     // Promote all conditions so the ones created in method calls below this
 *     // level (the call to conditionMethod2()) go back to our caller as well.
 *     PROMOTECONDITIONS();
 *
 *     // Return the highest severity of any conditions that have been added in
 *     // this method or any method that we have called in this method
 *     return GETCURRENTHIGHESTSEVERITY();
 *  }
 *
 *
 *  SEVERITY ConditionTest::conditionMethod2()
 *  {
 *     // Make a frame for the conditions to use (otherwise you will get compile
 *     // errors)
 *     MAKEFRAME( "ConditionTest", "ConditionTest::conditionMethod2()" );
 *
 *     // Add code that will create a Condition with tag
 *     // CONDITIONTEST_CONDITION_MESSAGE4
 *     ADDCONDITIONFROMFILE( CONDITIONTEST_CONDITION_MESSAGE4 )
 *
 *     // Return the highest severity of any conditions that have been added in
 *     // this method
 *     return GETCURRENTHIGHESTSEVERITY();
 *  }
 *
 *
 *  void ConditionTest::conditionExceptionMethod()
 *  {
 *
 *     // Method one for ConditionException in method with pre-existing MAKEFRAME
 *     MAKEFRAME( "ConditionTest", "ConditionExample::conditionExceptionMethod()" )
 *
 *     // CONDITIONTEST_CONDITION_MESSAGE3
 *     throw EXCEPTIONFROMFILE( CONDITIONTEST_CONDITION_MESSAGE3 );
 *
 *     // Method two for ConditionException in method with no MAKEFRAME
 *     THROWFROMFILE( "ConditionTest",
 *                    "ConditionExample::conditionExceptionMethod()",
 *                    CONDITIONTEST_CONDITION_MESSAGE3 );
 *
 *  }
 *
 *
 *
 *  void main( int argc, char *argv[] )
 *  {
 *     // We need a frame so that we can handle the conditions here
 *     MAKEFRAME( "ConditionTest", "main( int argc, char *argv[] )" )
 *
 *     ConditionTest conditionTest;
 *
 *     // Check to see if the call to ConditionTest's constructor added any
 *     // conditions and display ALL of them you found (use cout to display them).
 *
 *     // See how many conditions we have from the constructor call
 *     int iCount = CONDITIONCOUNT();
 *
 *     // Spin through the list of warnings/errors and display each one in turn
 *     for ( int i = 0; i < iCount; ++i )
 *     {
 *        Condition *pCondition = GETCONDITION( i );
 *        cout << "Condition: " << pCondition->getMessage() << endl;
 *     }
 *
 *     SEVERITY returnCode = conditionTest.conditionMethod();
 *
 *     // Check to see if the call to conditionMethod() added any conditions
 *     // and display ALL of them you found (use cout to display them).
 *     // Check to see if the call to conditionMethod() added any conditions
 *     if ( returnCode > NO_SEVERITY )
 *     {
 *        // See how many conditions we have.
 *        iCount = CONDITIONCOUNT();
 *
 *        // Spin through the list of warnings/errors and display each one in turn
 *        for ( int i = 0; i < iCount; ++i )
 *        {
 *           Condition *pCondition = GETCONDITION( i );
 *           cout << "Condition: " << pCondition->getMessage() << endl;
 *        }
 *     }
 *
 *     try
 *     {
 *        conditionTest.conditionExceptionMethod();
 *     }
 *     catch ( ConditionException &e )
 *     {
 *        cout << "Condition exception caught: ";
 *        // Add code to display the message from the ConditionException
 *        e.what();
 *     }
 *
 *     // Wait exiting so that the tracing messages will actually get
 *     // to the monitor
 *     char ch;
 *     cout << "Press <enter> to continue" << endl;
 *     cin.get( ch );
 *  }
 *
 *
 * </PRE>
 */
class DICORE_LINKAGE ConditionManager
{
public:
   /**
    * Used to get the single instance of the ConditionManager
    *
    * @return Pointer to singleton
    */
   static ConditionManager *getInstance();

   /**
    * Return path being used to search for condition files
    *
    * @return Path to directory that contains condition files
    */
   const I_CHAR *getPath( void )
   {
      return(const I_CHAR *)_cndPath.getImp().c_str();
   }

   /**
    * Return path being used to search for condition files
    *
    * @return Path to directory that contains condition files
    */
   void setPath( const DString& path )
   {
      _cndPath = path;
   }

   /**
    * find a specific component/code in the list of
    * conditions on the specified frame
    *
    * @param fr     frame to search
    * @param component component name to search for
    * @param code   condition code to search for
    * @param fUseCurrent
    *                  using current frame; if true, checks
    *                  to see if it should autopromote before search. Defaults to FALSE.
    * @return condition if found, NULL if not
    */
   Condition *findCondition( Frame *fr,
                             const I_CHAR *component,
                             int code,
                             bool fUseCurrent=FALSE );

   /**
    * Get condition on frame below current frame.
    *
    * @param fr     pointer to current frame
    * @param idx    index of condition wanted
    * @return Pointer to condition found
    */
   Condition *getCondition( Frame *fr, int idx );

   /**
    * Get count of number of conditions on frame
    * below current frame.
    *
    * @param fr     pointer to current frame
    * @return condition count
    */
   int getConditionCount( Frame *fr );

   /**
    * Return pointer to frame below
    *
    * @param rpFr  Parent frame (where to get frame below )
    * @return Pointer to frame below
    */
   Frame *getFrameBelow( Frame *rpFr );

   /**
    * Frames contain conditions.  Find the conditions
    * with the highest severity
    *
    * @param fr     Look at conditions in provided frame
    * @param fUseCurrent
    *               True - use passed in frame
    *               False - use frame below on passed in
    * @return Highest severity found
    */
   SEVERITY getMaxSeverity( Frame *fr, bool fUseCurrent=FALSE );

   /**
    * set the application name associated with this
    * condition manager. This name is used to get the configuration
    * settings out of registry.
    *
    * @param appName application name
    */
   void setApplicationName( const I_CHAR * appName );

   /**
    * Move each condition up from the frame below
    * to the current frame.
    *
    * @param fr     frame to promote conditions to
    * @param fileName promoting filename
    * @param lineNumber promoting line
    */
   void promoteAll( Frame *fr,
                    const char * fileName,
                    unsigned lineNumber );

   /**
    * Delete all frames below current frame,
    * which will delete all the condition for those frames.
    *
    * @param fr     Frame to clear conditions from
    */
   void clearConditions( Frame *fr );

   /**
    * Delete all frames below current frame,
    * which will delete all the condition for those frames.
    *
    * @param fr     Frame to clear conditions from
    * @param idx    Index of condition to clear
    */
   void clearCondition( Frame *fr, int idx );

   /**
    * Frame wrapper for function where frame is passed in.
    * Function creates new frame from data passed in and
    * calls other startFrame
    *
    * @param componentName
    *                   Name of component
    * @param methodName Name of method
    * @param fileName Name of file
    * @param lineNumber Line number where frame created
    * @param pathName Path used to find condition file
    * @param promote Flag controls auto promotion of conditions
    * @return Pointer to frame created
    */
   Frame *startFrame( const I_CHAR * componentName,
                      const I_CHAR *methodName,
                      const char *fileName,
                      int lineNumber,
                      const I_CHAR *pathName,
                      BOOL promote );

   /**
    * Function used by all parameter startFrame to
    * correctly place new frame into correct spot in
    * ConditionManager
    *
    * @param fr     New frame to add
    */
   void startFrame( Frame *fr );

   /**
    * Set frame completion flag and delete any
    * frames below the frame.
    *
    * @param fr     pointer to current frame
    */
   void endFrame( Frame *fr );

private:
   DString _cndPath;
   DString _appName;
   SingletonRegister m_register;
   static ConditionManager *s_pManager;

   // constructor/destructor
   ConditionManager( void );
   virtual ~ConditionManager( void );
   ConditionManager( const ConditionManager &copy );

   static void deregister( void *pObj );
   void getConfigurationValues( );
   const ConditionManager &operator=( const ConditionManager &copy );
};


/**
 * Class will be used in server conditions
 * Do not currently use class
 *
 *
 * Manage frames which contain conditions.
 * startFrame creates a new frame for conditions as each new method
 * begins.  endFrame flags the frame as finished processing, which
 * causes any lower level frames to be deleted.
 */
class DICORE_LINKAGE ConditionManagerContainer
{
public:
   // constructor/destructor
   ConditionManagerContainer( void );
   virtual ~ConditionManagerContainer( void );
   void killInstance (void);

   /**
    * Return path being used to search for condition files
    *
    * @return Path to directory that contains condition files
    */
   const I_CHAR *getPath( void );


   /**
    * find a specific component/code in the list of
    * conditions on the specified frame
    *
    * @param fr     frame to search
    * @param component component name to search for
    * @param code   condition code to search for
    * @param fUseCurrent
    *                  using current frame; if true, checks
    *                  to see if it should autopromote before search. Defaults to FALSE.
    * @return condition if found, NULL if not
    */
   Condition *findCondition( Frame *fr,
                             const I_CHAR *component, int code,
                             bool fUseCurrent=FALSE );

   /**
    * Get condition on frame below current frame.
    *
    * @param fr     pointer to current frame
    * @param idx    index of condition wanted
    * @return Pointer to condition found
    */
   Condition *getCondition( Frame *fr, int idx );

   /**
    * Get count of number of conditions on frame
    * below current frame.
    *
    * @param fr     pointer to current frame
    * @return condition count
    */
   int getConditionCount( Frame *fr );

   /**
    * Return pointer to frame below
    *
    * @param Frame  Parent frame (where to get frame below )
    * @return Pointer to frame below
    */
   Frame *getFrameBelow( Frame * );

   /**
    * Frames contain conditions.  Find the conditions
    * with the highest severity
    *
    * @param fr     Look at conditions in provided frame
    * @param fUseCurrent
    *               True - use passed in frame
    *               False - use frame below on passed in
    * @return Highest severity found
    */
   SEVERITY getMaxSeverity( Frame *fr, bool fUseCurrent=FALSE );

   /**
    * set the application name associated with this
    * condition manager. This name is used to get the configuration
    * settings out of registry.
    *
    * @param appName application name
    */
   void setApplicationName( const I_CHAR * appName );

   /**
    * Move each condition up from the frame below
    * to the current frame.
    *
    * @param fr     frame to promote conditions to
    * @param fileName promoting filename
    * @param lineNumber promoting line
    */
   void promoteAll( Frame *fr,
                    const char *fileName,
                    unsigned lineNumber );

   /**
    * Delete all frames below current frame,
    * which will delete all the condition for those frames.
    *
    * @param fr     Frame to clear conditions from
    */
   void clearConditions( Frame *fr );

   /**
    * Delete all frames below current frame,
    * which will delete all the condition for those frames.
    *
    * @param fr     Frame to clear conditions from
    * @param idx    Index of condition to clear
    */
   void clearCondition( Frame *fr, int idx );

   /**
    * Frame wrapper for function where frame is passed in.
    * Function creates new frame from data passed in and
    * calls other startFrame
    *
    * @param componentName
    *                   Name of component
    * @param methodName Name of method
    * @param fileName Name of file
    * @param lineNumber Line number where frame created
    * @param pathName Path used to find condition file
    * @param promote Flag controls auto promotion of conditions
    * @return Pointer to frame created
    */
   Frame *startFrame( const I_CHAR *componentName,
                      const I_CHAR *methodName,
                      const char *fileName,
                      int lineNumber,
                      const I_CHAR *pathName,
                      BOOL promote );

   /**
    * Function used by all parameter startFrame to
    * correctly place new frame into correct spot in
    * ConditionManager
    *
    * @param fr     New frame to add
    */
   void startFrame( Frame *fr );

   /**
    * Set frame completion flag and delete any
    * frames below the frame.
    *
    * @param fr     pointer to current frame
    */
   void endFrame( Frame *fr );

private:
   ConditionManager * getInstance( void )
   {
      return(ConditionManager::getInstance());
   }

};


/**
 * A CMFrame object is used to tell the ConditionManager object to start a new Frame.
 *
 * While this could have been done with a direct call to a ConditionManager method
 * (such as startFrame), the programmer would then have to remember to code an endFrame call
 * at the end of every method.
 *
 * A CMFrame object is instantiated on the local stack
 * (from the MAKEFRAME macro) of each method which will use
 * conditions, either to set or check. This means the object will be destroyed
 * at the end of the method, so the
 * endFrame method can be called in the CMFrame destructor.
 * During construction/destruction of this object, a starting/ending message
 * is automatically traced if tracing is turned on.
 *
 * @see ConditionManager
 */
class DICORE_LINKAGE CMFrame
{
public:
   /**
    * Called from macros to create a local method variable
    *
    * @param componentName
    *                   Component name
    * @param methodName Method name
    * @param fileName File name
    * @param lineNumber Line number
    * @param pathName Path to the condition file
    * @param toplevel Flag for top-level
    * @param autopromote
    *                   Should conditions be moved (auto-promoted) to parent frame
    *                   automatically
    */
   CMFrame( const I_CHAR *componentName,
            const I_CHAR *methodName,
            const char *fileName,
            int lineNumber,
            const I_CHAR *pathName = I_( ".\\" ),
            BOOL toplevel=FALSE,
            bool autopromote=FALSE );
   ~CMFrame( void );

   /**
    * Gets frame created during construction of the helper class
    *
    * @return Created frame
    */
   Frame *getFrame( void )
   { return(_pFrame);}
private:
   Frame *_pFrame;
};




#ifdef ConditionManager_cpp
ConditionManagerContainer DICORE_LINKAGE g_conditionManager;
#else
/**
 * Define global ConditionManager object.  Should change this to be like
 * a singleton.
 */
extern ConditionManagerContainer DICORE_LINKAGE g_conditionManager;
#endif      // ConditionManager_cpp

#ifdef ENABLE_TRACING

/**
* MAKEFRAMER creates a local function variable called CMFrame.
* It is used to add conditions, or get to the frame below to check conditions.
*
* The class name is passed as an additional parameter ( NULL_STRING is allowed).
*/
   #define MAKEFRAMER( componentName, className, methodName) \
   { \
      TracerClient tracerClient(className); \
      if ( tracerClient.isTracing() ) \
      { \
         tracerClient.setSupportOldTracing( true); \
         tracerClient.logMethod( methodName ); \
      } \
   } \
   CMFrame cmFrame( componentName, \
                    ( DString( className ) == NULL_STRING ) \
                    ? methodName \
                    :  DString( className ).append( colon ).append(  \
                                                 methodName ).c_str() , \
                    __FILE__, \
                    __LINE__, \
                    g_conditionManager.getPath() );
#else
   #define MAKEFRAMER( componentName, className, methodName ) \
   CMFrame cmFrame( componentName, \
                    ( DString( className ) == NULL_STRING ) \
                    ? methodName \
                    : DString( className ).append( colon ).append(  \
                                                 methodName ).c_str(), \
                    __FILE__, \
                    __LINE__, \
                    g_conditionManager.getPath() );
#endif


#ifdef ENABLE_TRACING
/**
 * MAKEFRAMEAUTOPROMOTER will create a frame that will automatically promote conditions
 * that are not explicitly cleared.
 *
 * The class name is passed as an additional parameter ( NULL_STRING is allowed).
 */
   #define MAKEFRAMEAUTOPROMOTER( componentName, className, methodName ) \
   { \
      TracerClient tracerClient(className); \
      if ( tracerClient.isTracing() ) \
      { \
         tracerClient.setSupportOldTracing( true); \
         tracerClient.logMethod( methodName ); \
      } \
   } \
   CMFrame cmFrame( componentName, \
                    ( DString( className ) == NULL_STRING ) \
                    ? methodName \
                    : DString( className ).append( colon ).append(  \
                                                 methodName ).c_str(), \
                    __FILE__, \
                    __LINE__, \
                    g_conditionManager.getPath(), \
                    FALSE, \
                    TRUE );
#else
   #define MAKEFRAMEAUTOPROMOTER( componentName, className, methodName ) \
   CMFrame cmFrame( componentName, \
                    ( DString( className ) == NULL_STRING ) \
                    ? methodName \
                    : DString( className ).append( colon ).append(  \
                                                 methodName ).c_str(), \
                    __FILE__, \
                    __LINE__, \
                    g_conditionManager.getPath(), \
                    FALSE, \
                    TRUE );
#endif




/**
 * MAKEFRAMENOTRACER forces tracing off for this method.
 *
 * The class name is passed as an additional parameter ( NULL_STRING is allowed).
 */
#define MAKEFRAMENOTRACER( componentName, className, methodName ) \
   CMFrame cmFrame( componentName, \
                    ( DString( className ) == NULL_STRING ) \
                    ? methodName \
                    : DString( className ).append( colon ).append(  \
                                                 methodName ).c_str(), \
                    __FILE__, \
                    __LINE__, \
                    g_conditionManager.getPath(), \
                    FALSE, \
                    TRUE );


#ifdef ENABLE_TRACING
/**
 * MAKEFRAMETOPLEVELR is used to flag the top level frame of a thread, so it will not be deleted.
 * This is the only way other threads can check conditions from the thread.
 *
 * The class name is passed as an additional parameter ( NULL_STRING is allowed).
 */
   #define MAKEFRAMETOPLEVELR( componentName, className, methodName ) \
   { \
      TracerClient tracerClient(className); \
      if ( tracerClient.isTracing() ) \
      { \
         tracerClient.setSupportOldTracing( true); \
         tracerClient.logMethod( methodName ); \
      } \
   } \
   CMFrame cmFrame( componentName, \
                    ( DString( className ) == NULL_STRING ) \
                    ? methodName \
                    : DString( className ).append( colon ).append(  \
                                                 methodName ).c_str(), \
                    __FILE__, \
                    __LINE__, \
                    g_conditionManager.getPath(), \
                    TRUE );
#else
   #define MAKEFRAMETOPLEVELR( componentName, className, methodName ) \
   CMFrame cmFrame( componentName, \
                    ( DString( className ) == NULL_STRING ) \
                    ? methodName \
                    : DString( className ).append( colon ).append(  \
                                                 methodName ).c_str(), \
                    __FILE__, \
                    __LINE__, \
                    g_conditionManager.getPath(), \
                    TRUE );
#endif



/**
 * MAKEFRAMECONSTRUCTORR is used for tracing purposes.
 * It flags the method as a constructor.
 *
 * The class name is passed as an additional parameter ( NULL_STRING is allowed).
 */
#define MAKEFRAMECONSTRUCTORR( componentName, className, methodName ) \
   TRACE_CONSTRUCTOR( componentName, \
                    ( DString( className ) == NULL_STRING ) \
                    ? methodName \
                    : DString( className ).append( colon ).append(  \
                                                 methodName ).c_str() ); \
   CMFrame cmFrame( componentName, \
                    ( DString( className ) == NULL_STRING ) \
                    ? methodName \
                    : DString( className ).append( colon ).append(  \
                                                 methodName ).c_str(), \
                    __FILE__, \
                    __LINE__, \
                    g_conditionManager.getPath() );



/**
 * MAKEFRAMEDESTRUCTORR is used for tracing purposes.
 * It flags the method as a destructor.
 *
 * The class name is passed as an additional parameter ( NULL_STRING is allowed).
 */
#define MAKEFRAMEDESTRUCTORR( componentName, className, methodName ) \
   TRACE_DESTRUCTOR( componentName ); \
   CMFrame cmFrame( componentName, \
                    ( DString( className ) == NULL_STRING ) \
                    ? methodName \
                    : DString( className ).append( colon ).append(  \
                                                 methodName ).c_str(), \
                    __FILE__, \
                    __LINE__, \
                    g_conditionManager.getPath() );


/**
 * The autopromote flag indicates that conditions
 * on the current frame will be copied to the
 * frame above the current frame when the frame
 * destructor is called.
 */
#define SETAUTOPROMOTE( promoteFlag ) \
   cmFrame.getFrame()->setAutoPromote( promoteFlag );


/**
 * The top-level flag indicates that
 * the current frame is to be considered the base
 * of a frame stack, which guarantees its conditions
 * cannot be accessed by calling functions.
 */
#define SETTOPLEVEL( flag ) \
   cmFrame.getFrame()->setTopLevel( flag );

/**
 * Macro adds a condition to the current frame
 * from a component specific file.
 * The conditions will perform substitutions
 * based on a string in an IDI format.
 * Parameter substitutions are done based on the passed IDI string (NULL_STRING allowed)
 * Override capability is provided through clientLocale ( NULL allowed )
 */
#define ADDCONDITION( code, str1, clientLocale ) \
   cmFrame.getFrame()->addConditionFromFile( code, \
                                             __FILE__, \
                                             __LINE__, \
                                             FALSE, \
                                             NO_SEVERITY, \
                                             str1, \
                                             clientLocale );


/**
 * Creates ConditionException from file condition.
 *
 * Parameter substitution is done based on passed in
 * IDI string.
 * Parameter substitutions are done based on the passed IDI string (NULL_STRING allowed)
 * Override capability is provided through clientLocale ( NULL allowed )
 */
#define EXCEPTIONCONDITION( code, str1, clientOverride ) \
   ConditionException( cmFrame.getFrame()->getComponentName(), \
                       cmFrame.getFrame()->getMethodName(), \
                       code, \
                       __FILE__, \
                       __LINE__, \
                       cmFrame.getFrame()->getLevel(), \
                       FALSE, \
                       g_conditionManager.getPath(), \
                       NO_SEVERITY, \
                       str1, \
                       clientOverride )


/**
 * Throws ConditionException from file condition.
 * The module and method are passed in as parameters
 * removing the requirement for a method frame.
 *
 *
 * Parameter substitution is done with passed in
 * IDI string.
 * Parameter substitutions are done based on the passed IDI string (NULL_STRING allowed)
 * Override capability is provided through clientLocale ( NULL allowed )
 */
#define THROWEXCEPTIONCONDITION(component, method, code, str1, clientLocale) \
   throw ConditionException( component, \
                             method, \
                             code, \
                             __FILE__, \
                             __LINE__, \
                             0, \
                             FALSE, \
                             g_conditionManager.getPath(), \
                             NO_SEVERITY, \
                             str1, \
                             clientLocale );




/**
 * Throws ConditionException from language table.
 * The module and method are passed in as parameters
 * removing the requirement for a method frame.
 *
 * This is for throwing elemental conditions which
 * are used internally in Infrastructure.
 *
 * Parameter substitutions are done based on
 * passed in IDI string.
 * Parameter substitutions are done based on the passed IDI string (NULL_STRING allowed)
 */
#define THROWELEMENTALEXCEPTIONCONDITION(component, method, code, langTable,str1) \
   throw ConditionException( component, \
                             method, \
                             code, \
                             __FILE__, \
                             __LINE__, \
                             langTable, \
                             str1 );



/**
 * Add condition to frame based on file condition.
 * The severity is overriden based on the passed in severity
 * Parameter substitutions are done based on the passed IDI string (NULL_STRING allowed)
 * Override capability is provided through clientLocale ( NULL allowed )
 */
#define ADDCNDSEVERITY(code, severity, str1, clientLocale ) \
   cmFrame.getFrame()->addConditionFromFile( code, \
                                             __FILE__, \
                                             __LINE__, \
                                             str1, \
                                             FALSE, \
                                             severity, \
                                             clientLocale );


/**
 * Macro creates a Condition object from
 * component file, and allow the programmer to
 * increase the severity.
 * The conditions can have an IDI string parameter.
 * Parameter substitutions are done based on the passed IDI string (NULL_STRING allowed)
 */
#define EXCSEVERITY(code, severity, str1, clientLocale ) \
   ConditionException( cmFrame.getFrame()->getComponentName(), \
                       cmFrame.getFrame()->getMethodName(), \
                       code, \
                       __FILE__, \
                       __LINE__, \
                       cmFrame.getFrame()->getLevel(), \
                       FALSE, \
                       g_conditionManager.getPath(), \
                       severity, \
                       str1, \
                       clientLocale )


/**
 * Add condition to current frame based on
 * ConditionException that was caught.
 */
#define SETCONDITIONFROMEXCEPTION(ce) \
   cmFrame.getFrame()->addConditionFromException( ce,  \
                                                  __FILE__,  \
                                                  __LINE__);


/**
 * throw a ConditionException based on the information
 * contained within a Condition
 */
#define THROWFROMCONDITION(c) \
   throw ConditionException( \
                            DString((I_CHAR *)(c).getComponentName()), \
                             DString((I_CHAR *)(c).getMethodName()), \
                             (c).getCode(), \
                             __FILE__, \
                             __LINE__, \
                             0, \
                             FALSE, \
                             g_conditionManager.getPath(), \
                             (c).getSeverity(), \
                             NULL_STRING );


/**
 * Macro is used to create a Condition object
 * from a component file, but not add it to a frame.
 * The current frame information is used to
 * determine the component and method name.
 * A variable is declared on the local stack
 * with the name passed in.
 * This is useful to create a Condition for
 * immediate display or write to a file.
 */
#define CREATECONDITION( varname, code, str1, clientLocale ) \
   Condition varname( cmFrame.getFrame()->getComponentName(), \
                      cmFrame.getFrame()->getMethodName(), \
                      code, \
                      __FILE__, \
                      __LINE__, \
                      FALSE, \
                      g_conditionManager.getPath(), \
                      NO_SEVERITY, \
                      str1, \
                      clientLocale )



/**
 * Macro returns a pointer to a condition object
 * from the frame below based on
 * the component name and condition code.
 */
#define FINDCONDITIONFRAMEBELOW( component, code ) \
   g_conditionManager.findCondition( cmFrame.getFrame(), \
                                     component, code )


/**
 * Macro returns the highest severity of all conditions
 *  on the frame below
 */
#define GETHIGHESTSEVERITYFRAMEBELOW() \
   g_conditionManager.getMaxSeverity( cmFrame.getFrame() )


/**
 * Macro returns a pointer to a condition object
 * from the frame below based on
 * the condition index
 */
#define GETCONDITIONFRAMEBELOW(index) \
   g_conditionManager.getCondition( cmFrame.getFrame(), index )


/**
 * Macro gets the number of conditions
 * on the frame below
 */
#define CONDITIONCOUNTFRAMEBELOW() \
   g_conditionManager.getConditionCount( cmFrame.getFrame() )


/**
 * Clear conditions from frame below.
 */
#define CLEARCONDITIONSFRAMEBELOW() \
   g_conditionManager.clearConditions( cmFrame.getFrame() );


/**
 * Clear conditions from frame below
 * based on index information
 */
#define CLEARCONDITIONFRAMEBELOW( index ) \
   g_conditionManager.clearCondition( cmFrame.getFrame(), index );

/**
 * Macro packs conditions (removing duplicates)
 * in frame below
 */
#define PACKCONDITIONSFRAMEBELOW() g_conditionManager.getFrameBelow( \
                             cmFrame.getFrame() )->packConditions();


/**
 * PROMOTECONDITIONS moves conditions from the
 * frame below to the current frame
 */
#define PROMOTECONDITIONSFRAMEBELOW() \
   g_conditionManager.promoteAll( cmFrame.getFrame(), \
                                  __FILE__, \
                                  __LINE__ )






/**
 * Macro returns a pointer to a condition object
 * from the current frame based
 * on component and method name.
 */
#define FINDCONDITIONFRAMECURRENT( component, code ) \
   g_conditionManager.findCondition( cmFrame.getFrame(), \
                                     component, \
                                     code,\
                                     true )


/**
 * Macro gets the highest severity of all conditions
 * on the current frame
 */
#define GETHIGHESTSEVERITYFRAMECURRENT() \
   g_conditionManager.getMaxSeverity( cmFrame.getFrame(), TRUE )


/**
 * Macro packs conditions (removing duplicates)
 * in current frame
 */
#define PACKCONDITIONSFRAMECURRENT() \
   cmFrame.getFrame()->packConditions();




/**
 * Macro returns a pointer to a condition object
 * from the current frame based
 * on the condition index.
 */
#define GETCONDITIONFRAMECURRENT(index) \
   cmFrame.getFrame()->getCondition( index )


/**
 * Macro gets the number of conditions
 * on the current frame
 */
#define CONDITIONCOUNTFRAMECURRENT() cmFrame.getFrame()->getCount()


/**
 * Clear conditions from current frame.
 */
#define CLEARCONDITIONSFRAMECURRENT() cmFrame.getFrame()->clearConditions( TRUE );


/**
 * Clear condition from current based on
 * index information
 */
#define CLEARCONDITIONFRAMECURRENT( index )  \
   cmFrame.getFrame()->clearCondition( index );

/**
 * These macros are used to pass
 * frame pointers into programmer
 * defined helper functions.
 *
 * FRAMEBELOW is used to pass a frame pointer
 * for the frame below.
 */
#define FRAMEBELOW( ) \
   g_conditionManager.getFrameBelow( cmFrame.getFrame() )


//**********************************************************************
//              Revision Control Entries
//**********************************************************************
//
// $Log:   Y:/VCS/BF Core/ifdscore/conditionmanager.hpp-arc  $
//
//   Rev 1.2   May 10 2007 16:01:12   purdyech
//Added non-standard setPath() method to allow the condition path to be changed.  It is set immediately after the application has been set, and I need to change it for the 'XML-configuration' option.
//
//   Rev 1.1   Oct 09 2002 17:41:48   PURDYECH
//New PVCS Database
//
//   Rev 1.0   Jul 05 2002 10:14:38   SMITHDAV
//Initial revision.
// 
//    Rev 1.41   May 18 2001 14:33:26   dt24433
// Changed to use thread local storage to manage thread specific
// data - no longer explicitly support moving conditions across threads.
// Switch to use Guard/CriticalSectionLock instead of CriticalSection/MutexSemaphore.
// 
//    Rev 1.40   23 Oct 2000 14:12:16   dt14177
// cleanup
// 
//    Rev 1.39   23 Aug 2000 21:17:26   dt20842
// Added ability to pass clientLocale through macros.
// Added lazy initialization to Condition.
// 
//    Rev 1.38   Apr 05 2000 15:23:04   DMUM
// Removal of Larry Code
//
//    Rev 1.37   Mar 27 2000 10:15:36   DMUM
// Removed reference to SingletonBase
//
//    Rev 1.36   Feb 26 2000 16:30:50   DT20842
// Reduce number condition macros
//
//    Rev 1.35   23 Feb 2000 16:07:58   dt20842
// Move macros to migrate file
//
//    Rev 1.34   13 Jan 2000 14:30:36   dt20842
// Updated JavaDoc comments
//
//    Rev 1.33   Jan 07 2000 13:05:28   DT20842
// Added more JavaDoc comments
//
//    Rev 1.32   Jan 02 2000 10:32:58   DT20842
// Adding missing parameter to CLEARCURRENTCONDITIONS macro
//
//    Rev 1.31   Dec 30 1999 16:33:06   DT14177
// fixed 3 macros
//
//    Rev 1.30   Dec 30 1999 15:13:24   DT14177
// massive reformat in order to check parameters
//
//    Rev 1.29   Dec 29 1999 10:42:40   DT20842
// Added package comment line
//
//    Rev 1.28   Dec 28 1999 08:42:04   DT20842
// Changed to JavaDoc style comments
//
//    Rev 1.27   Dec 23 1999 17:13:04   DT14177
// Fixed a compile bug and moved the ADDCONDITIONFROMFILE1,2,3 to conditionmigrate.hpp
//
//    Rev 1.26   Dec 20 1999 10:12:10   DT14177
// Made idistring changes for backward compatibility
//
//    Rev 1.25   Dec 16 1999 07:36:08   DT20842
// Better fix for blank destructor messages
//
//    Rev 1.23   Nov 24 1999 08:19:32   DMUM
// Removed #include for "debugmethodtrace.hpp" since
// that class is not implemented and the header is basically
// a dead archive.
//
//    Rev 1.22   Nov 19 1999 15:58:32   DT14177
// Added ClearCurrentCondition() macro
//
//    Rev 1.21   Sep 28 1999 13:27:06   DT14177
// Multi-threading fix;
//
//    Rev 1.20   Sep 16 1999 16:28:12   DT14177
// memory leak cleanup
//
//    Rev 1.19   Aug 24 1999 08:03:02   DMUM
// Removed ASSERTE macros from throw macros.
// The ASSERTE macro was moved to the constructor for ConditionException
// so that logic could be put in to determine at *RUNTIME* whether or not to
// assert.
//
//    Rev 1.18   Aug 13 1999 13:46:12   DT14177
// Put '!' in rest of ASSERTE macros
//
//    Rev 1.17   Aug 12 1999 15:39:56   DT14177
// Removed commented-out macros and added _ASSERTE to THROW macros.
//
//    Rev 1.16   Jul 23 1999 11:01:46   DT20842
// Fixed bug where auto promote was not working when tracing was enabled
//
//    Rev 1.15   May 13 1999 09:16:42   DMUM
// Implementing "Elemental" mode of operation
//
//    Rev 1.14   May 12 1999 09:21:54   DT20842
// Added elemental conditions
//
//    Rev 1.13   Apr 26 1999 15:00:20   DTWK
// Fix parameter names in macros (MAKEFRAME2, etc)
//
//    Rev 1.12   Apr 16 1999 13:28:06   DT20842
// Added new tracing
//
//
//    Rev 1.11   29 Mar 1999 16:22:04   DT14177
// added IDI macros for Leenerts
//
//    Rev 1.10   26 Feb 1999 10:30:34   DT14177
// Added support for className
//
//    Rev 1.9   25 Feb 1999 14:04:36   DT14177
// Changed IDI string substitution macros to end in IDI.
//
//    Rev 1.8   24 Feb 1999 11:01:08   DT14177
// sync up with tracer
//
//    Rev 1.7   22 Feb 1999 11:46:46   DT14177
// fixed DString and const I_CHAR stuff
//
//    Rev 1.6   18 Feb 1999 10:33:08   DT14177
// UNICODE
//
//    Rev 1.5   Jan 28 1999 14:05:40   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.4   Dec 09 1998 13:40:08   DMUM
// Check in for DICORE
//
//    Rev 1.3   Sep 02 1998 09:47:14   DTWK
// Another checkin for CBO team (another macro)
//
//    Rev 1.2   Aug 31 1998 14:04:40   DTWK
// Update to CBO team's stuff
//
//    Rev 1.1   Aug 27 1998 15:56:42   DTWK
// Checkin CBO team's additions to frame/condition stuff
//
//    Rev 1.0   29 Jul 1998 20:36:30   DT14596
// DLMG New Archives for TA2000NTDT
//
//    Rev 1.23   Jul 02 1998 16:35:08   DTWK
// Update with changes from Paul Dardeau
//
//    Rev 1.22   Jun 17 1998 15:45:52   dt27994
// Changed MAKE macros to call trace macros directly.
// This will allow for the ENABLE_TRACING switch to work here.
//
//    Rev 1.21   Jun 17 1998 08:17:58   dt27994
// Added optimization to macros that use tracing.
//
//    Rev 1.20   Jun 16 1998 16:11:46   dt27994
//
//
//    Rev 1.19   Mar 25 1998 14:44:52   DTWK
// Add new tracing from CBO team
//
//    Rev 1.18   Dec 12 1997 14:48:12   dkaw
// add findCondition and macros to use it
//
//    Rev 1.17   Nov 09 1997 15:34:34   DTWK
// Add inclusion guards for faster compiles.
// Add guards so that class is flagged as exported only when compiling
// the output that actually exports the class.
//
//    Rev 1.16   Sep 26 1997 17:23:58   DTWK
// update THROWFROMCONDITION to use new ConditionException constructor
//
//    Rev 1.15   Sep 26 1997 12:34:16   dkaw
// add getPath to ConditionManager; pass path to CMFrame constructor;
// pass path in all Exception macros
//
//    Rev 1.14   Sep 19 1997 14:20:24   dkaw
// add SETTOPLEVEL
//
//    Rev 1.13   Sep 17 1997 11:49:04   dkaw
// rename getThreadCondition to getCondition
//
//    Rev 1.12   Sep 08 1997 15:57:34   dkaw
// add setApplicationName, SET_APPNAME
//
//    Rev 1.11   Sep 08 1997 09:19:58   dkaw
// remove semi-colon on GETCURRENTHIGHESTSEVERITY()
//
//    Rev 1.10   Sep 04 1997 14:19:42   dkaw
// add useCurrent flag to getMaxSeverity, have GETCURRENTHIGHESTSEVERITY
// call ConditionManager's getMaxSeverity, not Frame's
//
//    Rev 1.9   Sep 04 1997 12:51:44   dkaw
//
//
//    Rev 1.8   Sep 04 1997 11:37:34   dkaw
// default MAKEFRAMENOTRACE to autopromote
//
//    Rev 1.7   Sep 04 1997 11:11:12   dkaw
// add autopromote, clearCondition()
//
//    Rev 1.6   Sep 03 1997 09:24:08   dkaw
// change toplevel default to FALSE for CMFrame
//
//
//    Rev 1.5   Sep 02 1997 15:52:46   dkaw
// add MAKEFRAMETOPLEVEL macro
//
//    Rev 1.4   Aug 26 1997 17:01:46   dkaw
// add GETCURRENTHIGHESTSEVERITY
//
//    Rev 1.3   Aug 26 1997 14:05:10   dkaw
// add CLEARCURRENTCONDITIONS()
//
//    Rev 1.2   Aug 25 1997 15:55:38   dkaw
// add getFrameBelow(), getMaxSeverity(), promotAll for threads, new macros
//
//    Rev 1.1   Jul 22 1997 16:22:40   dkaw
// add trace filter, use ditrace
//
//    Rev 1.0   Jun 13 1997 12:56:16   DTWK
//
