#pragma once

//**********************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1999 by DST Systems, Inc.
//
//**********************************************************************
//
// ^FILE   : conditionmigrate.hpp
// ^AUTHOR : Tom Hogan
// ^DATE   : 5/6/97
//
// ^DESCRIPTION : A backward-compatibility file to provide support
//                for pre-IdiString Conditions
//
//**********************************************************************


#ifndef IDISTRING_HPP
   #include <idistring.hpp>
#endif

   #define DEFAULT_CLIENTLOCALE NULL

#define EXECHIST(a)
#define EXECHIST2(a,b)

#if !defined(__WFILE__)
   #if !defined(WIDEN)
      #define WIDEN2(x) L ## x
      #define WIDEN(x) WIDEN2(x)
   #endif
   #define __WFILE__ WIDEN(__FILE__)
   static wchar_t* s_pszFile = __WFILE__;
#endif

#if !defined( __IFILE__ )
   #if defined(DST_UNICODE)
      #define __IFILE__ __WFILE__
   #else
      #define __IFILE__ __FILE__
   #endif
#endif

#define CM_STRINGIFY(str) CM_STRINGIFY_W( #str )
#define CM_STRINGIFY_W( str ) L ## str

#define ADDCONDITIONFROMFILE1( code, str1 )  \
   I_CHAR * idiString = makeErrBufUsingGenericTags( str1, NULL ); \
   cmFrame.getFrame()->addConditionFromFile( code, \
                                             (const I_CHAR *)CM_STRINGIFY( code ), \
                                             __FILE__, \
                                             __LINE__, \
                                             FALSE, \
                                             NO_SEVERITY, \
                                             idiString, DEFAULT_CLIENTLOCALE ); \
   delete [] idiString;

#define ADDCONDITIONFROMFILE2( code, str1, str2 )  \
   I_CHAR * idiString = makeErrBufUsingGenericTags( str1, \
                                                    str2, \
                                                    NULL ); \
   cmFrame.getFrame()->addConditionFromFile( code, \
                                             (const I_CHAR *)CM_STRINGIFY( code ), \
                                             __FILE__, \
                                             __LINE__, \
                                             FALSE, \
                                             NO_SEVERITY, \
                                             idiString, DEFAULT_CLIENTLOCALE ); \
   delete [] idiString;

#define ADDCONDITIONFROMFILE3( code, str1, str2, str3 )  \
   I_CHAR * idiString = makeErrBufUsingGenericTags( str1, \
                                                    str2, \
                                                    str3, \
                                                    NULL ); \
   cmFrame.getFrame()->addConditionFromFile( code, \
                                             (const I_CHAR *)CM_STRINGIFY( code ), \
                                             __FILE__, \
                                             __LINE__, \
                                             FALSE, \
                                             NO_SEVERITY, \
                                             idiString, DEFAULT_CLIENTLOCALE ); \
   delete [] idiString;

#define ADDCONDITIONFROMBASE1( code, str1 )  \
   I_CHAR * idiString = makeErrBufUsingGenericTags( str1, NULL ); \
   cmFrame.getFrame()->addConditionFromFile( code, \
                                             (const I_CHAR *)CM_STRINGIFY( code ), \
                                             __BASE__, \
                                             __LINE__, \
                                             TRUE, \
                                             NO_SEVERITY, \
                                             idiString, DEFAULT_CLIENTLOCALE ); \
   delete [] idiString;

#define ADDCONDITIONFROMBASE2( code, str1, str2 )  \
   I_CHAR * idiString = makeErrBufUsingGenericTags( str1, \
                                                    str2, \
                                                    NULL ); \
   cmFrame.getFrame()->addConditionFromFile( code, \
                                             (const I_CHAR *)CM_STRINGIFY( code ), \
                                             __BASE__, \
                                             __LINE__, \
                                             TRUE, \
                                             NO_SEVERITY, \
                                             idiString, DEFAULT_CLIENTLOCALE ); \
   delete [] idiString;

#define ADDCONDITIONFROMBASE3( code, str1, str2, str3 )  \
   I_CHAR * idiString = makeErrBufUsingGenericTags( str1, \
                                                    str2, \
                                                    str3, \
                                                    NULL ); \
   cmFrame.getFrame()->addConditionFromFile( code, \
                                             (const I_CHAR *)CM_STRINGIFY( code ), \
                                             __BASE__, \
                                             __LINE__, \
                                             TRUE, \
                                             NO_SEVERITY, \
                                             idiString, DEFAULT_CLIENTLOCALE ); \
   delete [] idiString;



/**
 * These macros are used to pass 
 * frame pointers into programmer 
 * defined helper functions. 
 * 
 * MYFRAME is used to pass a frame pointer
 * for the current frame.
 */
#define MYFRAME( ) cmFrame.getFrame()


/**
 * These macros are used to pass frame pointers 
 * into programmer defined helper functions. 
 * 
 * FRAMEDEF is used to define the 
 * frame variable passed in to the function.
 */
#define FRAMEDEF( ) Frame *pFrame

/**
 * Macro used in programmer defined helper functions 
 * that used FRAMEDEF to pass in a frame. 
 * 
 * It returns Condition pointer based on 
 * component and method name information.
 */
#define FINDFRAMECONDITION( component, code ) \
   pFrame->findCondition( component, code )

/**
 * Macro used in programmer defined helper functions 
 * that used FRAMEDEF to pass in a frame. 
 * 
 * It returns the highest severity from the conditions
 * stored in the frame.
 */
#define GETFRAMEHIGHESTSEVERITY() pFrame->getMaxSeverity()


/**
 * Macro used in programmer defined helper functions 
 * that used FRAMEDEF to pass in a frame. 
 * 
 * It returns Condition pointer based on 
 * index information.
 */
#define GETFRAMECONDITION(index) pFrame->getCondition( index )


/**
 * Macro used in programmer defined helper functions 
 * that used FRAMEDEF to pass in a frame. 
 * 
 * It returns current number of conditions in frame.
 */
#define FRAMECONDITIONCOUNT() pFrame->getCount()


/**
 * Macro used in programmer defined helper functions 
 * that used FRAMEDEF to pass in a frame. 
 * 
 * It clears the conditions in the frame.
 */
#define CLEARFRAMECONDITIONS() pFrame->clearConditions();

/**
 * 
 * Macro used in programmer defined helper functions
 * that used FRAMEDEF to pass in a frame.
 * 
 * It packs conditions (removing duplicates).
 */
#define PACKFRAMECONDITIONS()    pFrame->packConditions();


// Define macros
// MAKETRACER obsolete - left for backward compatability
#ifdef ENABLE_TRACING
   #define MAKETRACER(componentName, methodName) \
   { \
      TracerClient tracerClient; \
      if ( tracerClient.isTracing() ) \
      { \
         tracerClient.setSupportOldTracing( true); \
         tracerClient.logMethod( methodName ); \
      } \
   } \
   CMFrame cmFrame( componentName, \
                    methodName, \
                    __FILE__, \
                    __LINE__, \
                    g_conditionManager.getPath() );
#else
   #define MAKETRACER(componentName, methodName) \
   CMFrame cmFrame( componentName, \
                    methodName, \
                    __FILE__, \
                    __LINE__, \
                    g_conditionManager.getPath() );
#endif


//!!!!!

/**
 * Macro adds a condition to the current frame
 * from a component specific file.
 */
#define ADDCONDITIONFROMFILE( code ) \
   cmFrame.getFrame()->addConditionFromFile( code, \
                                             (const I_CHAR *)CM_STRINGIFY( code ), \
                                             __FILE__, \
                                             __LINE__, \
                                             FALSE, \
                                             NO_SEVERITY, NULL_STRING, DEFAULT_CLIENTLOCALE );

/**
 * Macro adds a condition to the current frame
 * from the base condition file.
 */
#define ADDCONDITIONFROMBASE( code ) \
   cmFrame.getFrame()->addConditionFromFile( code, \
                                             (const I_CHAR *)CM_STRINGIFY( code ), \
                                             __FILE__, \
                                             __LINE__, \
                                             TRUE, \
                                             NO_SEVERITY, NULL_STRING, DEFAULT_CLIENTLOCALE );

/**
 * Macro adds a condition to the current frame
 * from a component specific file. 
 * The conditions will perform substitutions 
 * based on a string in an IDI format.
 */
#define ADDCONDITIONFROMFILEIDI( code, str1 ) \
   cmFrame.getFrame()->addConditionFromFile( code, \
                                             (const I_CHAR *)CM_STRINGIFY( code ), \
                                             __FILE__, \
                                             __LINE__, \
                                             FALSE, \
                                             NO_SEVERITY, \
                                             str1, DEFAULT_CLIENTLOCALE );

/**
 * Macro adds a condition to the current frame
 * from the base condition file. 
 * The conditions will perform substitutions 
 * based on a string in an IDI format.
 */
#define ADDCONDITIONFROMBASEIDI(code, str1) \
   cmFrame.getFrame()->addConditionFromFile( code, \
                                             (const I_CHAR *)CM_STRINGIFY( code ), \
                                             __FILE__, \
                                             __LINE__, \
                                             TRUE, \
                                             NO_SEVERITY, \
                                             str1, DEFAULT_CLIENTLOCALE );


/**
 * Creates ConditionException from file condition
 */
#define EXCEPTIONFROMFILE( code ) \
   ConditionException( cmFrame.getFrame()->getComponentName(), \
                       cmFrame.getFrame()->getMethodName(), \
                       code, \
                       (const I_CHAR *)CM_STRINGIFY( code ), \
                       __FILE__, \
                       __LINE__, \
                       cmFrame.getFrame()->getLevel(), \
                       FALSE, g_conditionManager.getPath(), NO_SEVERITY, NULL_STRING, DEFAULT_CLIENTLOCALE )

/**
 * Creates ConditionException from base condition
 */
#define EXCEPTIONFROMBASE(code) \
   ConditionException( cmFrame.getFrame()->getComponentName(), \
                       cmFrame.getFrame()->getMethodName(), \
                       code, \
                       (const I_CHAR *)CM_STRINGIFY( code ), \
                       __FILE__, \
                       __LINE__, \
                       cmFrame.getFrame()->getLevel(),  \
                       TRUE, \
                       g_conditionManager.getPath(), NO_SEVERITY, NULL_STRING, DEFAULT_CLIENTLOCALE )

/**
 * Creates ConditionException from file condition.
 * 
 * Parameter substitution is done based on passed in
 * IDI string.
 */
#define EXCEPTIONFROMFILEIDI( code, str1 ) \
   ConditionException( cmFrame.getFrame()->getComponentName(), \
                       cmFrame.getFrame()->getMethodName(), \
                       code, \
                       (const I_CHAR *)CM_STRINGIFY( code ), \
                       __FILE__, \
                       __LINE__, \
                       cmFrame.getFrame()->getLevel(), \
                       FALSE, \
                       g_conditionManager.getPath(), \
                       NO_SEVERITY, \
                       str1, DEFAULT_CLIENTLOCALE )

/**
 * Creates ConditionException from base condition.
 * 
 * Parameter substitution is done based on passed in
 * IDI string.
 */
#define EXCEPTIONFROMBASEIDI( code, str1 ) \
   ConditionException(cmFrame.getFrame()->getComponentName(), \
                      cmFrame.getFrame()->getMethodName(), \
                      code, \
                      (const I_CHAR *)CM_STRINGIFY( code ), \
                      __FILE__, \
                      __LINE__, \
                      cmFrame.getFrame()->getLevel(), \
                      TRUE, \
                      g_conditionManager.getPath(), \
                      NO_SEVERITY, \
                      str1, DEFAULT_CLIENTLOCALE )


/**
 * Throws ConditionException from file condition.
 * The module and method are passed in as parameters
 * removing the requirement for a method frame.
 */
#define THROWFROMFILE(component, method, code) \
   throw ConditionException( component, \
                             method, \
                             code, \
                             (const I_CHAR *)CM_STRINGIFY( code ), \
                             __FILE__, \
                             __LINE__, \
                             0, \
                             FALSE, \
                             g_conditionManager.getPath(), \
                             NO_SEVERITY, \
                             NULL, DEFAULT_CLIENTLOCALE );

/**
 * Throws ConditionException from file condition.
 * The module and method are passed in as parameters
 * removing the requirement for a method frame.
 * 
 * 
 * Parameter substitution is done with passed in
 * IDI string.
 */
#define THROWFROMFILEIDI(component, method, code, str1) \
   throw ConditionException( component, \
                             method, \
                             code, \
                             (const I_CHAR *)CM_STRINGIFY( code ), \
                             __FILE__, \
                             __LINE__, \
                             0, \
                             FALSE, \
                             g_conditionManager.getPath(), \
                             NO_SEVERITY, \
                             str1 , DEFAULT_CLIENTLOCALE);


/**
 * Throws ConditionException from base condition.
 * The module and method are passed in as parameters
 * removing the requirement for a method frame.
 */
#define THROWFROMBASE(component, method, code) \
   throw ConditionException( component, \
                             method, \
                             code, \
                             (const I_CHAR *)CM_STRINGIFY( code ), \
                             __FILE__, \
                             __LINE__, \
                             0, \
                             TRUE, \
                             g_conditionManager.getPath(), \
                             NO_SEVERITY, \
                             NULL, DEFAULT_CLIENTLOCALE );

/**
 * Throws ConditionException from base condition.
 * The module and method are passed in as parameters
 * removing the requirement for a method frame.
 * 
 * 
 * Parameter substitution is done with passed in
 * IDI string.
 */
#define THROWFROMBASEIDI(component, method, code, str1) \
   throw ConditionException( component, \
                             method, \
                             code, \
                             (const I_CHAR *)CM_STRINGIFY( code ), \
                             __FILE__, \
                             __LINE__, \
                             0, \
                             TRUE, \
                             g_conditionManager.getPath(), \
                             NO_SEVERITY, \
                             str1, DEFAULT_CLIENTLOCALE );


/**
 * Throws ConditionException from language table.
 * The module and method are passed in as parameters
 * removing the requirement for a method frame.
 * 
 * This is for throwing elemental conditions which
 * are used internally in Infrastructure.
 */
#define THROWELEMENTAL(component, method, code, langTable) \
   throw ConditionException( component, \
                             method, \
                             code, \
                             (const I_CHAR *)CM_STRINGIFY( code ), \
                             __FILE__, \
                             __LINE__, \
                             langTable );




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
 */
#define THROWELEMENTALIDI(component, method, code, langTable,str1) \
   throw ConditionException( component, \
                             method, \
                             code, \
                             (const I_CHAR *)CM_STRINGIFY( code ), \
                             __FILE__, \
                             __LINE__, \
                             langTable, \
                             str1 );



/**
 * Throws ConditionException from file condition.
 * The module, class, and method are passed in as parameters
 * removing the requirement for a method frame.
 * 
 * 
 * Parameter substitution is done with passed in
 * IDI string.
 */
#define THROWFROMFILE2( component, className, method, code ) \
   throw ConditionException( component, \
                             DString( className ).append( colon ). \
                                             append( method ).c_str(), \
                             code, \
                             (const I_CHAR *)CM_STRINGIFY( code ), \
                             __FILE__, \
                             __LINE__, \
                             0, \
                             FALSE, \
                             g_conditionManager.getPath(), \
                             NO_SEVERITY, \
                             NULL, DEFAULT_CLIENTLOCALE );


/**
 * Throws ConditionException from base condition.
 * The module, class, and method are passed in as parameters
 * removing the requirement for a method frame.
 * 
 * 
 * Parameter substitution is done with passed in
 * IDI string.
 */
#define THROWFROMFILEIDI2(component, className, method, code, str1) \
   throw ConditionException( component,  \
                             DString( className ).append( colon ). \
                                             append( method ).c_str(), \
                             code, \
                             (const I_CHAR *)CM_STRINGIFY( code ), \
                             __FILE__, \
                             __LINE__, \
                             0, \
                             FALSE, \
                             g_conditionManager.getPath(), \
                             NO_SEVERITY, \
                             str1, DEFAULT_CLIENTLOCALE );


/**
 * Macro used by Configuration Manager to set
 * application name.
 * 
 * This is used internally by Infrastructure only.
 */
#define SET_APPNAME( appname ) g_conditionManager.setApplicationName( \
            appname );


#ifdef ENABLE_TRACING
/**
 * MAKEFRAME creates a local function variable called CMFrame.
 * It is used to add conditions, or get to the frame below to check conditions. 
 */
   #define MAKEFRAME(componentName, methodName) \
   { \
      TracerClient tracerClient; \
      if ( tracerClient.isTracing() ) \
      { \
         tracerClient.setSupportOldTracing( true); \
         tracerClient.logMethod( methodName ); \
      } \
   } \
   EXECHIST( methodName ); \
   CMFrame cmFrame( componentName, \
                    methodName, \
                    __FILE__, \
                    __LINE__, \
                    g_conditionManager.getPath() );
#else
   #define MAKEFRAME(componentName, methodName) \
   EXECHIST( methodName ); \
   CMFrame cmFrame( componentName, \
                    methodName, \
                    __FILE__, \
                    __LINE__, \
                    g_conditionManager.getPath() );
#endif

#ifdef ENABLE_TRACING

/**
* MAKEFRAME2 creates a local function variable called CMFrame.
* It is used to add conditions, or get to the frame below to check conditions.
* 
* The class name is passed as an additional parameter.
*/
   #define MAKEFRAME2( componentName, className, methodName ) \
   { \
      TracerClient tracerClient(className); \
      if ( tracerClient.isTracing() ) \
      { \
         tracerClient.setSupportOldTracing( true); \
         tracerClient.logMethod( methodName ); \
      } \
   } \
   EXECHIST2( className, methodName ); \
   CMFrame cmFrame( componentName, \
                    DString( className ).append( colon ).append(  \
                                                 methodName ).c_str(), \
                    __FILE__, \
                    __LINE__, \
                    g_conditionManager.getPath() );
#else
   #define MAKEFRAME2( componentName, className, methodName ) \
   EXECHIST2( className, methodName ); \
   CMFrame cmFrame( componentName, \
                    DString( className ).append( colon ).append(  \
                                                 methodName ).c_str(), \
                    __FILE__, \
                    __LINE__, \
                    g_conditionManager.getPath() );
#endif


#ifdef ENABLE_TRACING
/**
 * MAKEFRAMEAUTOPROMOTE will create a frame that will automatically promote conditions 
 * that are not explicitly cleared. 
 */
   #define MAKEFRAMEAUTOPROMOTE(componentName, methodName) \
   { \
      TracerClient tracerClient; \
      if ( tracerClient.isTracing() ) \
      { \
         tracerClient.setSupportOldTracing( true); \
         tracerClient.logMethod( methodName ); \
      } \
   } \
   EXECHIST( methodName ); \
   CMFrame cmFrame( componentName, \
                    methodName, \
                    __FILE__, \
                    __LINE__, \
                    g_conditionManager.getPath(), \
                    FALSE, \
                    TRUE );
#else
   #define MAKEFRAMEAUTOPROMOTE(componentName, methodName) \
   EXECHIST( methodName ); \
   CMFrame cmFrame( componentName, \
                    methodName, \
                    __FILE__, \
                    __LINE__, \
                    g_conditionManager.getPath(), \
                    FALSE, \
                    TRUE );
#endif


#ifdef ENABLE_TRACING
/**
 * MAKEFRAMEAUTOPROMOTE2 will create a frame that will automatically promote conditions
 * that are not explicitly cleared.
 * 
 * The class name is passed as an additional parameter.
 */
   #define MAKEFRAMEAUTOPROMOTE2( componentName, className, methodName ) \
   { \
      TracerClient tracerClient(className); \
      if ( tracerClient.isTracing() ) \
      { \
         tracerClient.setSupportOldTracing( true); \
         tracerClient.logMethod( methodName ); \
      } \
   } \
   EXECHIST2( className, methodName ); \
   CMFrame cmFrame( componentName, \
                    DString( className ).append( colon ).append(  \
                                                 methodName ).c_str(), \
                    __FILE__, \
                    __LINE__, \
                    g_conditionManager.getPath(), \
                    FALSE, \
                    TRUE );
#else
   #define MAKEFRAMEAUTOPROMOTE2( componentName, className, methodName ) \
   EXECHIST2( className, methodName ); \
   CMFrame cmFrame( componentName, \
                    DString( className ).append( colon ).append(  \
                                                 methodName ).c_str(), \
                    __FILE__, \
                    __LINE__, \
                    g_conditionManager.getPath(), \
                    FALSE, \
                    TRUE );
#endif



/**
 * MAKEFRAMENOTRACE forces tracing off for this method. 
 */
#define MAKEFRAMENOTRACE(componentName, methodName) \
   EXECHIST( methodName ); \
   CMFrame cmFrame( componentName, \
                    methodName, \
                    __FILE__, \
                    __LINE__, \
                    g_conditionManager.getPath(), \
                    FALSE, \
                    TRUE );


/**
 * MAKEFRAMENOTRACE2 forces tracing off for this method.
 * 
 * The class name is passed as an additional parameter.
 */
#define MAKEFRAMENOTRACE2( componentName, className, methodName ) \
   EXECHIST2( className, methodName ); \
   CMFrame cmFrame( componentName, \
                    DString( className ).append( colon ).append(  \
                                                 methodName ).c_str(), \
                    __FILE__, \
                    __LINE__, \
                    g_conditionManager.getPath(), \
                    FALSE, \
                    TRUE );


#ifdef ENABLE_TRACING
/**
 * MAKEFRAMETOPLEVEL is used to flag the top level frame of a thread, so it will not be deleted. 
 * This is the only way other threads can check conditions from the thread. 
 */
   #define MAKEFRAMETOPLEVEL(componentName, methodName) \
   { \
      TracerClient tracerClient; \
      if ( tracerClient.isTracing() ) \
      { \
         tracerClient.setSupportOldTracing( true); \
         tracerClient.logMethod( methodName ); \
      } \
   } \
   EXECHIST( methodName ); \
   CMFrame cmFrame( componentName, \
                    methodName, \
                    __FILE__, \
                    __LINE__, \
                    g_conditionManager.getPath(), \
                    TRUE );
#else
   #define MAKEFRAMETOPLEVEL(componentName, methodName) \
   EXECHIST( methodName ); \
   CMFrame cmFrame( componentName, \
                    methodName, \
                    __FILE__, \
                    __LINE__, \
                    g_conditionManager.getPath(), \
                    TRUE );
#endif


#ifdef ENABLE_TRACING
/**
 * MAKEFRAMETOPLEVEL2 is used to flag the top level frame of a thread, so it will not be deleted.
 * This is the only way other threads can check conditions from the thread.
 * 
 * The class name is passed as an additional parameter.
 */
   #define MAKEFRAMETOPLEVEL2( componentName, className, methodName ) \
   { \
      TracerClient tracerClient(className); \
      if ( tracerClient.isTracing() ) \
      { \
         tracerClient.setSupportOldTracing( true); \
         tracerClient.logMethod( methodName ); \
      } \
   } \
   EXECHIST2( className, methodName ); \
   CMFrame cmFrame( componentName, \
                    DString( className ).append( colon ).append(  \
                                                methodName ).c_str(), \
                    __FILE__, \
                    __LINE__, \
                    g_conditionManager.getPath(), \
                    TRUE );
#else
   #define MAKEFRAMETOPLEVEL2( componentName, className, methodName ) \
   EXECHIST2( className, methodName ); \
   CMFrame cmFrame( componentName, \
                    DString( className ).append( colon ).append(  \
                                                 methodName ).c_str(), \
                    __FILE__, \
                    __LINE__, \
                    g_conditionManager.getPath(), \
                    TRUE );
#endif



/**
 * MAKEFRAMECONSTRUCTOR is used for tracing purposes.  
 * It flags the method as a constructor.
 */
#define MAKEFRAMECONSTRUCTOR(componentName, methodName) \
   TRACE_CONSTRUCTOR( componentName, methodName ); \
   EXECHIST2( methodName ); \
   CMFrame cmFrame( componentName, \
                    methodName, \
                    __FILE__, \
                    __LINE__, \
                    g_conditionManager.getPath() );


/**
 * MAKEFRAMECONSTRUCTOR2 is used for tracing purposes.
 * It flags the method as a constructor.
 * 
 * The class name is passed as an additional parameter.
 */
#define MAKEFRAMECONSTRUCTOR2( componentName, className, methodName ) \
   TRACE_CONSTRUCTOR( componentName, DString( className ). \
                                     append( colon ).append(  \
                                     methodName ).c_str() ); \
   EXECHIST2( className, methodName ); \
   CMFrame cmFrame( componentName, \
                    DString( className ). \
                    append( colon ).append( methodName ).c_str(), \
                    __FILE__, \
                    __LINE__, \
                    g_conditionManager.getPath() );


/**
 * MAKEFRAMEDESTRUCTOR is used for tracing purposes.  
 * It flags the method as a destructor.
 */
#define MAKEFRAMEDESTRUCTOR(componentName, methodName) \
   TRACE_DESTRUCTOR( componentName ); \
   EXECHIST( methodName ); \
   CMFrame cmFrame( componentName, \
                    methodName, \
                    __FILE__, \
                    __LINE__, \
                    g_conditionManager.getPath() );








/**
 * MAKEFRAMEDESTRUCTOR is used for tracing purposes.
 * It flags the method as a destructor.
 * 
 * The class name is passed as an additional parameter.
 */
#define MAKEFRAMEDESTRUCTOR2( componentName, className, methodName ) \
   TRACE_DESTRUCTOR( componentName ); \
   EXECHIST2( className, methodName ); \
   CMFrame cmFrame( componentName, \
                    DString( className ).append( colon ).append( \
                                                 methodName ).c_str(), \
                    __FILE__, \
                    __LINE__, \
                    g_conditionManager.getPath() );




/**
 * Macro packs conditions (removing duplicates)
 * in current frame
 */
#define PACKCONDITIONS() cmFrame.getFrame()->packConditions();




/**
 * Macro returns a pointer to a condition object 
 * from the current frame based 
 * on the condition index. 
 */
#define GETCURRENTCONDITION(index) \
   cmFrame.getFrame()->getCondition( index )


/**
 * Macro gets the number of conditions 
 * on the current frame
 */
#define CURRENTCONDITIONCOUNT() cmFrame.getFrame()->getCount()


/**
 * Clear conditions from current frame.
 */
#define CLEARCURRENTCONDITIONS() cmFrame.getFrame()->clearConditions( TRUE );


/**
 * Clear condition from current based on 
 * index information
 */
#define CLEARCURRENTCONDITION( index )  \
   cmFrame.getFrame()->clearCondition( index );



/**
 * Macro returns a pointer to a condition object 
 * from the frame below based on 
 * the component name and condition code.
 */
#define FINDCONDITION( component, code ) \
   g_conditionManager.findCondition( cmFrame.getFrame(), \
                                     component, code )


/**
 * Macro returns the highest severity of all conditions
 *  on the frame below
 */
#define GETHIGHESTSEVERITY() \
   g_conditionManager.getMaxSeverity( cmFrame.getFrame() )


/**
 * Macro returns a pointer to a condition object 
 * from the frame below based on 
 * the condition index
 */
#define GETCONDITION(index) \
   g_conditionManager.getCondition( cmFrame.getFrame(), index )


/**
 * Macro gets the number of conditions
 * on the frame below
 */
#define CONDITIONCOUNT() \
   g_conditionManager.getConditionCount( cmFrame.getFrame() )


/**
 * Clear conditions from frame below.
 */
#define CLEARCONDITIONS() \
   g_conditionManager.clearConditions( cmFrame.getFrame() );


/**
 * Clear conditions from frame below
 * based on index information
 */
#define CLEARCONDITION( index ) \
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
#define PROMOTECONDITIONS() \
   g_conditionManager.promoteAll( cmFrame.getFrame(), \
                                  __FILE__, \
                                  __LINE__ )





/**
 * Macro returns a pointer to a condition object 
 * from the current frame based 
 * on component and method name. 
 */
#define FINDCURRENTCONDITION( component, code ) \
   g_conditionManager.findCondition( cmFrame.getFrame(), \
                                     component, \
                                     code,\
                                     true )


/**
 * Macro gets the highest severity of all conditions 
 * on the current frame
 */
#define GETCURRENTHIGHESTSEVERITY() \
   g_conditionManager.getMaxSeverity( cmFrame.getFrame(), TRUE )





/**
 * Macro creates a Condition object from 
 * component file, and allow the programmer to 
 * increase the severity. 
 * The conditions can have an IDI string parameter.
 * Parameter substitutions are done based on the passed IDI string (NULL_STRING allowed)
 */
#define EXCSEVERITYFROMFILE(code, severity, str1 ) \
   ConditionException( cmFrame.getFrame()->getComponentName(), \
                       cmFrame.getFrame()->getMethodName(), \
                       code, \
                       __FILE__, \
                       __LINE__, \
                       cmFrame.getFrame()->getLevel(), \
                       FALSE, \
                       str1, \
                       severity, \
                       NULL_STRING, \
                       DEFAULT_CLIENTLOCALE )

/**
 * Macro creates a Condition object from 
 * base file, and allow the programmer to 
 * increase the severity. 
 * The conditions can have an IDI string parameter.
 * Parameter substitutions are done based on the passed IDI string (NULL_STRING allowed)
 */
#define EXCSEVERITYFROMBASE( code, severity, str1 ) \
    ConditionException( cmFrame.getFrame()->getComponentName(), \
                        cmFrame.getFrame()->getMethodName(), \
                        code, \
                        __FILE__, \
                        __LINE__, \
                        cmFrame.getFrame()->getLevel(), \
                        TRUE, \
                        str1, \
                        severity, \
                        NULL_STRING, \
                        DEFAULT_CLIENTLOCALE )

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
#define CREATECONDITIONFROMFILE( varname, code, str1 ) \
   Condition varname( cmFrame.getFrame()->getComponentName(), \
                      cmFrame.getFrame()->getMethodName(), \
                      code, \
                      __FILE__, \
                      __LINE__, \
                      FALSE, \
                      g_conditionManager.getPath(), \
                      NO_SEVERITY, \
                      str1, DEFAULT_CLIENTLOCALE )

/**
 * Macro is used to create a Condition object 
 * from a base file, but not add it to a frame. 
 * The current frame information is used to 
 * determine the component and method name. 
 * A variable is declared on the local stack 
 * with the name passed in. 
 * This is useful to create a Condition for 
 * immediate display or write to a file.
 */
#define CREATECONDITIONFROMBASE( varname, code, str1 ) \
   Condition varname( cmFrame.getFrame()->getComponentName(), \
                      cmFrame.getFrame()->getMethodName(), \
                      code, \
                      __FILE__, \
                      __LINE__, \
                      TRUE, \
                      g_conditionManager.getPath(), \
                      NO_SEVERITY, \
                      str1, DEFAULT_CLIENTLOCALE )



//**********************************************************************
//              Revision Control Entries
//**********************************************************************
//
// $Log:   Y:/VCS/iFastAWD/inc/conditionmigrate.hpp-arc  $
//
//   Rev 1.1   Nov 02 2011 04:44:20   purdyech
//Registry Cleanup
//
//   Rev 1.6   Sep 23 2009 01:30:44   purdyech
//Track Condition Name as well as Code.
//Add "Display Details" option to system menu on Error Popup.
//
//   Rev 1.5   Feb 20 2009 14:56:32   purdyech
//ZTS Revision 6
//
//   Rev 1.4   May 09 2007 10:25:44   purdyech
//Introduce EXECHIST Logging for AWD
//
//   Rev 1.3   Feb 18 2004 15:12:02   PURDYECH
//Added EXECHIST macros to do execution history tracking
//
//   Rev 1.2   Oct 09 2002 17:41:48   PURDYECH
//New PVCS Database
//
//   Rev 1.1   Sep 02 2002 17:33:46   PURDYECH
//temp fix for client locale
//
//   Rev 1.0   Jul 05 2002 10:14:38   SMITHDAV
//Initial revision.
//
//   Rev 1.3   23 Aug 2000 21:17:28   dt20842
//Added ability to pass clientLocale through macros.
//Added lazy initialization to Condition.
//
//   Rev 1.2   Feb 26 2000 16:30:52   DT20842
//Reduce number condition macros
//
//   Rev 1.1   23 Feb 2000 16:08:02   dt20842
//Move macros to migrate file
//
//   Rev 1.0   Dec 23 1999 17:46:10   dtwk
// 
// 

