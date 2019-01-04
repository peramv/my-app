#pragma once

#ifndef TRACERCLIENT_HPP
   #include <tracerclient.hpp>
#endif



#ifndef INCLUDED_STRINGFUNCTIONS
#define INCLUDED_STRINGFUNCTIONS
#include <stringfunctions.hpp>
#endif

#ifndef INCLUDED_DSTRING
#define INCLUDED_DSTRING
#include <dstring.hpp>
#endif

#ifndef INCLUDED_DSTRINGA
#define INCLUDED_DSTRINGA
#include <dstringa.hpp>
#endif


class ClientLocale;
class CConditionObject;

/**
 * Levels of condition severity in increasing order
 */
enum SEVERITY
{
   NO_CONDITION=1, TRACE_ONLY, NO_SEVERITY,
   INFORMATIONAL, WARNING, SEVERE_ERROR, CRITICAL_ERROR
};

#undef DICORE_LINKAGE
#ifdef DICORE_DLL
   #define DICORE_LINKAGE CLASS_EXPORT
#else
   #define DICORE_LINKAGE CLASS_IMPORT
#endif


/**
 * Structure holds data for elemental condition.
 * Elemental conditions are used internally within
 * infrastructure
 */
typedef struct
{
   /**
    * Number identifier of elemental condition
    */
   int      msgCode;
   /**
    * Message message of elemental condition
    */
   I_CHAR * errMsg;
   /**
    * Action of elemental condition
    */
   I_CHAR * correctionMsg;
} MsgPair;

/**
 * Holder of Japan Japanese elemental conditions
 */
MsgPair ja_jp[]; // may not translated yet

/**
 * Holder of US English elemental conditions
 */
MsgPair en_us[];

/**
 * Holder of German elemental conditions
 */
MsgPair de_de[];

/**
 * Holder of Spanish elemental conditions
 */
MsgPair es_es[];

/**
 * Holder of Canadian French elemental conditions
 */
MsgPair fr_ca[];

/**
 * Holder of French French elemental conditions
 */
MsgPair fr_fr[];

/**
 * Holder of Dutch elemental conditions
 */
MsgPair nl_nl[];

/**
 * Holder of Italian elemental conditions
 */
MsgPair it_it[];


/**
 * This class reads and stores information on
 * conditions generated in the code. Conditions are read from a file.
 * Base Conditions are errors that happen across components - like a
 * file open error = file open error no matter where it happens. These
 * will be stored in their own file (base.cnd).
 * 
 * @see ConditionManager
 */
class DICORE_LINKAGE Condition
{
public:

   /*
    * Errors generated from attempt to read condition file 
   */
   enum FileErrors
   {
      NO_CONDITION_CODE,
      CND_FILE_NOT_FOUND,
      CODE_NOT_FOUND,
      SEVERE_ERROR_IN_FILE,
      ISO_CODE_NOT_FOUND,
      INVALID_VERSION,
      ERROR_ON_NEW
   } fileProblems;

   /**
    * Structure holds an array of elemental conditions for a
    * specific language and country pairing.
    */
   typedef struct
   {
      I_CHAR * isoCode;
      MsgPair * msgPair;
   } mapCodePagesToLanguages;


   /**
    * create condition (allow for locale specific operations)
    * 
    * @param componentName
    *                   name of component
    * @param methodName name of calling method
    * @param code   condition code
    * @param fileName name of source file
    * @param lineNumber source file line number
    * @param baseCondition
    *                   TRUE is use base condition file,
    *                   else use component condition file
    * @param path   path of condition file
    * @param severity severity level
    * @param IdiStr String for condition variable substitution
    *               (name1=value1;name2=value2;...)
    * @param clientLocale locale string (default = NULL)
    * @param fCompleteConstructionNow
    *                   complete construction now (default = true)
    * @param context used for miscellaneous purposes
    *                (default = NULL_STRING)
    */
   Condition( const DString & componentName,
              const DString & methodName,
              long code,
              const I_CHAR* pszCode,
              const char * fileName,
              unsigned lineNumber,
              BOOL baseCondition,
              const I_CHAR *path = I_( ".\\" ),
              SEVERITY severity = NO_SEVERITY,
              const DString & IdiStr = NULL_STRING,
              const ClientLocale *clientLocale = NULL,
              const DString & context = NULL_STRING );


   /**
    * create condition (standard)
    * 
    * @param componentName
    *                   name of component
    * @param methodName name of calling method
    * @param code   condition code
    * @param severity severity level
    * @param fileName name of source file
    * @param lineNumber source file line number
    * @param message message string
    * @param correction - correction string
    * @param suppression
    *                   Flag controls suppression of condition
    * @param idiStr Idi string for condition parameter substitution
    *               (name1=value1;name2=value2;...)
    */
   Condition( const I_CHAR * componentName,
              const I_CHAR * methodName,
              long code,
              const I_CHAR* pszCode,
              SEVERITY severity,
              const char * fileName,
              unsigned lineNumber,
              const I_CHAR * message,
              const I_CHAR * correction,
              long suppression,
              const DString & idiStr = NULL_STRING );

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
    * @param str    Idi string
    */
   Condition( const DString & componentName,
              const DString & methodName,
              long code,
              const I_CHAR* pszCode,
              const char * fileName,
              unsigned lineNumber,
              mapCodePagesToLanguages elementalTable[],
              const DString & str = NULL_STRING );

   /**
    * create message and correction text
    * 
    * completes construction of the message and correction
    * in the specified locale, going to the file if need be.
    * 
    * @param localeString
    *               Override current condition locale
    */
   void prepareMessage( const DString & localeString );  // such as I_( "enUS" )


   /**
    * create message and correction text
    * 
    * completes construction of the message and correction
    * in the specified locale, going to the file if need be.
    * 
    * @param pClientLocale
    *               Override current condition locale
    */
   void prepareMessage( const ClientLocale & pClientLocale );


   /**
    * get condition code
    * 
    * @return condition code
    */
   long getCode() const;
   const I_CHAR* getCodeString() const;

   /**
    * get correction text
    * 
    * @return correction string
    */
   const I_CHAR *getCorrection() const;

   /**
    * get component name
    * 
    * @return component name
    */
   const I_CHAR *getComponentName() const;

   /**
    * get source file name
    * 
    * @return file name
    */
   const char *getFileName() const;

   /**
    * get source file line number
    * 
    * @return line number
    */
   int getLineNumber() const;

   /**
    * get message text
    * 
    * @return message string
    */
   const I_CHAR *getMessage() const;

   /**
    * get diagnostic message text
    * 
    * @return message string
    */
   DString getDiagnosticMessage() const;

   /**
    * get method name
    * 
    * @return method name
    */
   const I_CHAR *getMethodName() const;

   /**
    * get severity level
    * 
    * @return severity level
    */
   SEVERITY getSeverity() const;


   /**
    * Return condition context
    * This is additional data send by the programmer
    * of the condition
    * 
    * @return Context value
    */
   const DString & getContext() const { return(_context);}


   /**
    * Get suppress value
    * 
    * @return Suppress flag value
    */
   bool getSuppress() const;

   /**
    * get Idi string
    * 
    * @return Idi string
    */
   const DString & getIdi() const { return(_Idi);}

   void getCreatedTimestamp( SYSTEMTIME& st ) const { memcpy( &st, &_created, sizeof(SYSTEMTIME) ); }

   /**
    * Copy constructor
    * 
    * @param copy   Object to copy from
    */
   Condition( const Condition &copy );
   virtual ~Condition();


   /**
    * Token used to signal an error in the idi string and substitution logic
    */
   static const int TOKEN_NOT_FOUND;

   bool readFromObject(CConditionObject& pCondition);

private:

   // private constructor/destructor/assignment operator
   // These should not ever be used
   Condition &operator=( const Condition &copy );

   // private data
   BOOL      _baseCondition;
   mutable long      _code;               // Code identifying this Condition
   mutable const I_CHAR* _codeStr;
   mutable DString   _name;               // Name of this Condition
   mutable DString   _componentName;      // Component issuing Condition
   DString   _context;

   mutable DString   _correction;         // Correctional instructions
   MsgPair * _currMsgPair;                // used for condition file error messages
   mutable DStringA  _fileName;           // File where Condition occurred
   DString   _Idi;

   mutable int      _lineNumber;          // Line where error occurred
   mutable DString  _message;             // User message
   mutable DString  _methodName;          // Method where Condition occurred
   mutable DString  _pathName;
   mutable SEVERITY _severity;            // Severity of Condition

   mutable long     _suppress;            // client-controlled flag to suppress
   //   a condition

   ClientLocale *_clientLocale;           // Holds default or override information

   mutable bool     _init;                // Flag to determine if condition has been initialized
   bool     _initFromObject;              // Flag to determine if condition has been initialized with ADDCONDITIONFROMOBJECT or ADDCONDITIONFROMOBJECTIDI macro

   mutable SYSTEMTIME _created;           // timestamp when condition object was created

   static mapCodePagesToLanguages languagesMap[];

   void prepareMessage();        // Initialize condition
   void initCondition() const;


   void elementalInit( const DString & strCondition,
                       Condition::mapCodePagesToLanguages elementalTable[]);
   void doIdiSubstitution();
   void idiElementalProcessing( DString &mainString,
                                const DString &idiString );
   void idiProcessing( DString &mainString,
                       const DString &idiString );

   bool readFromFile( BOOL baseFlag, bool bUseDefaultLang );
   void doTrace( int level );

   int getLatestVersion( void );
   bool isValidVersion( int version );
   bool setCurrMsgPair( const DString & );

public:
   static const Condition* getRecordedCondition(const Condition* pCondition = NULL);
};

//************************************************************************
//              Revision Control Entries
//************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/core/ifdscore/condition.hpp-arc  $
//
//   Rev 1.8   May 03 2010 04:41:32   purdyech
//IN2107238 - Condition History added for Diagnostic Report
//
//   Rev 1.7   Sep 23 2009 01:28:24   purdyech
//Track Condition Name as well as Code.
//Add "Display Details" option to system menu on Error Popup.
//
//   Rev 1.6   Aug 30 2004 16:00:58   popescu
//PET 991, FN 02, added support for Dutch and Italian
//
//   Rev 1.5   May 07 2004 14:40:54   PURDYECH
//Match recent KC Infrastructure Files
//
//   Rev 1.4   Oct 16 2003 10:58:56   PURDYECH
//Private method readFromFile() has changed signature to allow for a recursive call.
//
//   Rev 1.3   Aug 12 2003 10:05:58   PURDYECH
//Added Spanish as a valid language.
//
//   Rev 1.2   Apr 02 2003 13:20:26   PURDYECH
//Added German, French, and French Canadian as known languages.
//
//   Rev 1.1   Oct 09 2002 17:41:46   PURDYECH
//New PVCS Database
//
//   Rev 1.0   Jul 05 2002 10:14:36   SMITHDAV
//Initial revision.
// 
//    Rev 1.34   23 Oct 2000 14:01:26   dt14177
// cleanup
// 
//    Rev 1.33   30 Aug 2000 18:21:48   dt20842
//  
// 
//    Rev 1.32   28 Aug 2000 17:34:42   dt20842
// Condition getters const again
// 
//    Rev 1.31   23 Aug 2000 21:17:22   dt20842
// Added ability to pass clientLocale through macros.
// Added lazy initialization to Condition.
// 
//    Rev 1.30   May 26 2000 20:26:30   DT14177
// Added ClientLocale support
// 
//    Rev 1.29   04 May 2000 17:27:46   dt20842
// Removed recursion check
// 
//    Rev 1.28   Feb 26 2000 16:30:46   DT20842
// Reduce number condition macros
// 
//    Rev 1.27   13 Jan 2000 14:30:30   dt20842
// Updated JavaDoc comments
// 
//    Rev 1.26   Jan 07 2000 13:05:22   DT20842
// Added more JavaDoc comments
// 
//    Rev 1.25   Dec 29 1999 10:42:34   DT20842
// Added package comment line
// 
//    Rev 1.24   Dec 28 1999 08:41:58   DT20842
// Changed to JavaDoc style comments
// 
//    Rev 1.23   Dec 06 1999 10:52:54   DT20842
// Added function const to getIdi
// 
//    Rev 1.22   Nov 17 1999 09:19:28   DMUM
// Got rid of annoying warning message.
//
//    Rev 1.21   Sep 28 1999 14:42:14   DT14177
// Fixed multi-threading bug
//
//    Rev 1.20   Sep 28 1999 13:26:58   DT14177
// Multi-threading fix;
//
//    Rev 1.19   Aug 02 1999 15:12:46   DT14177
// Fixed _currMessage NULL pointer problem
//
//    Rev 1.18   Jun 22 1999 11:10:06   DT14177
// Changed type for condition code from int to long.
//
//    Rev 1.17   Jun 14 1999 17:01:04   DT14177
// added getIdi() and doc changes.
//
//    Rev 1.16   Jun 10 1999 13:40:12   DT14177
// added comments
//
//    Rev 1.15   Jun 08 1999 16:17:44   DT14177
// added context, delayed condition message preparation, and locale override.
//
//    Rev 1.14   May 12 1999 09:21:48   DT20842
// Added elemental conditions
//
//    Rev 1.13   Apr 15 1999 14:15:44   DT14177
// Recursion fix, memory link fix, and removed hard-coding
//
//    Rev 1.12   Apr 12 1999 17:57:38   DT14177
// add versioning and JavaLocale stuff
//
//    Rev 1.11   30 Mar 1999 09:39:28   DT14177
// LL_CC change and constructor IDI parameter changed to DString &
//
//    Rev 1.9   04 Mar 1999 09:28:54   DT14177
// Fixed conditionException NULL pointer bug, duplicate SEVERE_ERROR definition bug, and the ASCII Condition file read bug.
//
//    Rev 1.8   02 Mar 1999 13:37:38   DT14177
// Added proper locale handling for Condition file problem state.
//
//    Rev 1.7   01 Mar 1999 15:43:04   DT14177
// fixed stack problem getFileName()
//
//    Rev 1.6   26 Feb 1999 18:12:12   DT14177
// Added .CND file problem error-handling
//
//    Rev 1.5   24 Feb 1999 10:44:42   DT14177
// sync up with tracer
//
//    Rev 1.4   22 Feb 1999 11:46:42   DT14177
// fixed DString and const I_CHAR stuff
//
//    Rev 1.3   18 Feb 1999 10:30:56   DT14177
// UNICODE
//
//    Rev 1.2   Jan 28 1999 14:05:34   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.1   Dec 09 1998 13:40:04   DMUM
// Check in for DICORE
//
//    Rev 1.7   Jul 02 1998 16:35:14   DTWK
// Update with changes from Paul Dardeau
//
//    Rev 1.6   Jun 16 1998 16:11:50   dt27994
//
//
//    Rev 1.5   Nov 09 1997 15:34:30   DTWK
// Add inclusion guards for faster compiles.
// Add guards so that class is flagged as exported only when compiling
// the output that actually exports the class.
//
//    Rev 1.4   Sep 08 1997 15:57:12   dkaw
//
//
//    Rev 1.3   Aug 28 1997 14:00:06   dkaw
// change NO_ERR to NO_SEVERITY
//
//    Rev 1.2   Aug 25 1997 15:53:42   dkaw
// remove DEFAULT, add NO_COND and NO_ERR
//
//    Rev 1.1   Jul 22 1997 16:22:42   dkaw
// add trace filter, use ditrace
//
//    Rev 1.0   Jun 13 1997 12:56:24   DTWK
//

