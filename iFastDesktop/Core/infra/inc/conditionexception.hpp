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

#ifndef INCLUDED_EXCEPTION
#define INCLUDED_EXCEPTION
#include <exception>
#endif

#ifndef INCLUDED_STRING
#define INCLUDED_STRING
#include <string>
#endif

#ifndef CONDITION_HPP
   #include <condition.hpp>
#endif

#ifndef SYMBOLS_H
   #include <symbols.h>
#endif

#undef DICORE_LINKAGE
#ifdef DICORE_DLL
   #define DICORE_LINKAGE CLASS_EXPORT
#else
   #define DICORE_LINKAGE CLASS_IMPORT
#endif

/**
 * ConditionException class is an exception wrapper for
 * the Condition object.  All condition function have
 * been wrapped in ConditionException for easier use
 * 
 * @see ConditionManager
 */
class DICORE_LINKAGE ConditionException : public std::exception
{
public:

   /**
    * create condition (standard)
    * 
    * @param componentName
    *                   name of component
    * @param methodName name of calling method
    * @param code   condition code
    * @param fileName name of source file
    * @param lineNumber source file line number
    * @param level  stack level number
    * @param baseCondition
    *                   TRUE is use base condition file,
    *                   else use component condition file
    * @param cndPath - path of condition file
    * @param severity - severity level
    * @param str    substitution string 1
    *               (name1=value1;name2=value2;...)
    */
   ConditionException(                       // File based constructor
                                             const DString &componentName,
                                             const DString &methodName,             // Object::Method or Procedure
                                             long code,                              // Condition code to lookup
                                             const I_CHAR* pszCode,
                                             const char *fileName,
                                             unsigned lineNumber,
                                             int level,
                                             BOOL baseCondition,                    // If true look up in
                                             //  base file, if false
                                             //  look up in component
                                             //  ConditionException file
                                             const I_CHAR *cndPath = I_( ".\\" ),
                                             SEVERITY severity = NO_SEVERITY,       // Allow to increase severity
                                             const DString & str = NULL_STRING,       // String substitution
                                             const ClientLocale *clientLocale = NULL  // Override information
                     );

   /**
    * create elemental condition
    * 
    * @param componentName
    *                   name of component
    * @param methodName name of calling method
    * @param code   condition code
    * @param fileName name of source file
    * @param lineNumber source file line number
    * @param elementalTable
    *                   Language table of elemental condition messages
    * @param str    substitution string 1
    *               (name1=value1;name2=value2;...)
    */
   ConditionException(const DString & componentName,
                      const DString & methodName,
                      long code, 
                      const I_CHAR* pszCode,
                      const char * fileName, 
                      unsigned lineNumber,
                      Condition::mapCodePagesToLanguages elementalTable[],
                      const DString & str = NULL_STRING );

   /**
    * Create based on existing condition
    * 
    * @param condition Condition object with full details
    */
   ConditionException(const Condition& condition);

   /**
    * create message and correction text
    * 
    * completes construction of the message and correction
    * in the specified locale, going to the file if need be.
    * 
    * @param locale
    *               Override current condition locale
    * @see Condition::prepareMessage
    */
   void prepareMessage( const DString & locale ) { _cnd.prepareMessage( locale );}
   void prepareMessage( const ClientLocale & pClientLocale )
   { _cnd.prepareMessage( pClientLocale );}

   ConditionException( const ConditionException &copy );
   virtual ~ConditionException() {};

   /**
    * get condition code
    * 
    * @return condition code
    * @see Condition::getCode
    */
   long getCode() const                  { return(_cnd.getCode());}

   const I_CHAR* getCodeString() const { return _cnd.getCodeString(); }

   Condition & getCondition( void )
   {
      return(_cnd);
   }

   /**
    * get correction text
    * 
    * @return correction string
    * @see Condition::getCorrection
    */
   const I_CHAR *getCorrection() const  { return(_cnd.getCorrection());}

   /**
    * get component name
    * 
    * @return component name
    * @see Condition::getComponentName
    */
   const I_CHAR *getComponentName() const
   { return(_cnd.getComponentName());}

   /**
    * get source file name
    * 
    * @return file name
    * @see Condition::getFileName
    */
   const char *getFileName() const      { return(_cnd.getFileName());}

   /**
    * get source file line number
    * 
    * @return line number
    * @see Condition::getLineNumber
    */
   int getLineNumber() const            { return(_cnd.getLineNumber());}

   /**
    * get message text
    * 
    * @return message string
    * @see Condition::getMessage
    */
   const I_CHAR *getMessage() const       { return(_cnd.getMessage());}

   /**
    * get method name
    * 
    * @return method name
    * @see Condition::getMethodName
    */
   const I_CHAR *getMethodName() const  { return(_cnd.getMethodName());}

   /**
    * get severity level
    * 
    * @return severity level
    * @see Condition::getSeverity
    */
   SEVERITY getSeverity() const         { return(_cnd.getSeverity());}

   /**
    * Get suppress value
    * 
    * @return Suppress flag value
    * @see Condition::getSuppress
    */
   bool getSuppress() const             { return(_cnd.getSuppress());}

   /**
    * get Idi string
    * 
    * @return Idi string
    * @see Condition::getIdi
    */
   const DString & getIdi() const       { return(_cnd.getIdi());}

   /**
    * Return condition context
    * This is additional data send by the programmer
    * of the condition
    * 
    * @return Context value
    * @see  Condition::getContext
    */
   const DString & getContext() const   { return(_cnd.getContext());}


   /**
    * Send condition exception information to standard out
    */
   virtual void what();

private:
   Condition _cnd;                           // Contained condition

   const ConditionException &operator=( const ConditionException &copy );
};

//************************************************************************
//              Revision Control Entries
//************************************************************************
//
// $Log:   Y:/VCS/iFastAWD/inc/conditionexception.hpp-arc  $
//
//   Rev 1.1   Nov 02 2011 04:44:16   purdyech
//Registry Cleanup
//
//   Rev 1.3   Sep 23 2009 01:29:58   purdyech
//Track Condition Name as well as Code.
//Add "Display Details" option to system menu on Error Popup.
//
//   Rev 1.2   Oct 22 2004 09:02:10   PURDYECH
//PET910 - .NET Conversion Fixes
//
//   Rev 1.1   Oct 09 2002 17:41:48   PURDYECH
//New PVCS Database
//
//   Rev 1.0   Jul 05 2002 10:14:36   SMITHDAV
//Initial revision.
// 
//    Rev 1.20   17 May 2001 15:05:42   dt14177
//  
// 
//    Rev 1.19   23 Oct 2000 14:05:10   dt14177
// cleanup
// 
//    Rev 1.18   28 Aug 2000 17:34:46   dt20842
// Condition getters const again
// 
//    Rev 1.17   23 Aug 2000 21:17:24   dt20842
// Added ability to pass clientLocale through macros.
// Added lazy initialization to Condition.
// 
//    Rev 1.16   13 Jan 2000 14:30:34   dt20842
// Updated JavaDoc comments
// 
//    Rev 1.15   Jan 07 2000 13:05:24   DT20842
// Added more JavaDoc comments
// 
//    Rev 1.14   Dec 29 1999 10:42:36   DT20842
// Added package comment line
// 
//    Rev 1.13   Dec 28 1999 08:42:02   DT20842
// Changed to JavaDoc style comments
// 
//    Rev 1.12   Dec 06 1999 10:54:22   DT20842
// Added constructor with Condition parameter
// Added 2 missing get fuctions
// 
//    Rev 1.11   Sep 28 1999 13:27:02   DT14177
// Multi-threading fix;
// 
//    Rev 1.10   Jun 22 1999 11:10:08   DT14177
// Changed type for condition code from int to long.
// 
//    Rev 1.9   Jun 11 1999 15:41:06   DT14177
// added prepareMessage( DString & locale )
// 
//    Rev 1.8   May 12 1999 09:21:50   DT20842
// Added elemental conditions
// 
//    Rev 1.7   29 Mar 1999 11:50:54   DT14177
// ConditionException Constructor now takes a DString reference as a parameter instead of I_CHAR *
// 
//    Rev 1.6   04 Mar 1999 09:28:54   DT14177
// Fixed conditionException NULL pointer bug, duplicate SEVERE_ERROR definition bug, and the ASCII Condition file read bug.
// 
//    Rev 1.5   24 Feb 1999 10:44:44   DT14177
// sync up with tracer
// 
//    Rev 1.4   22 Feb 1999 11:46:44   DT14177
// fixed DString and const I_CHAR stuff
// 
//    Rev 1.3   18 Feb 1999 10:32:48   DT14177
// UNICODE
// 
//    Rev 1.1   Dec 09 1998 13:40:06   DMUM
// Check in for DICORE
// 
//    Rev 1.6   Jun 16 1998 16:11:44   dt27994
// Removed old tracing code and modifed existing.
// 
//    Rev 1.5   Nov 09 1997 15:34:32   DTWK
// Add inclusion guards for faster compiles.
// Add guards so that class is flagged as exported only when compiling
// the output that actually exports the class.
// 
//    Rev 1.4   Sep 26 1997 12:33:02   dkaw
// pass condition path to constructor
// 
//    Rev 1.3   Aug 28 1997 14:00:36   dkaw
// change NO_ERR to NO_SEVERITY
// 
//    Rev 1.2   Aug 25 1997 15:47:54   dkaw
// change DEFAULT to NO_ERR on constructor
// 
//    Rev 1.1   Jul 22 1997 16:22:40   dkaw
// add trace filter, use ditrace
// 
//    Rev 1.0   Jun 13 1997 12:56:10   DTWK
//  
