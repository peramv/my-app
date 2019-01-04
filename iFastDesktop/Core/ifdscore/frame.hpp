#pragma once

/*
 * COPYRIGHT:
 *
 *    The computer systems, procedures, data bases and
 *    programs created and maintained by DST Systems, Inc.,
 *    are proprietary in nature and as such are confidential.
 *    Any unauthorized use or disclosure of such information
 *    may result in civil liabilities.
 *
 *    Copyright 1999-2000 by DST Systems, Inc.
 */

/** @pkg DICORE */

#pragma warning( push )
#pragma warning( disable: 4251 )

#ifndef CONDITIONEXCEPTION_HPP
   #include <conditionexception.hpp>
#endif

#include <map>

/**
 * Vector of conditions associated with a frame
 */
typedef std::vector< Condition * > CONDITIONVECTOR;

#undef DICORE_LINKAGE
#ifdef DICORE_DLL
   #define DICORE_LINKAGE CLASS_EXPORT
#else
   #define DICORE_LINKAGE CLASS_IMPORT
#endif

#define TEXT_LENGTH 128

class CConditionObject;

/**
 * A frame object is used to represent a level on the
 * call stack for a specific process and thread. The frame object
 * maintains a list of the conditions added at that level.
 * 
 * @see ConditionManager
 * @see Condition
 */
class DICORE_LINKAGE Frame
{
//friend class ConditionManager;
public:

   /**
    * create frame
    * 
    * @param componentName
    *                   name of component
    * @param methodName name of calling method
    * @param fileName name of source file
    * @param lineNumber source file line number
    * @param pathName path of condition file
    * @param autoPromote
    *                   Flag controls whether conditions are auto promoted
    */
   Frame( const I_CHAR *componentName, const I_CHAR *methodName,
          const char *fileName, int lineNumber,
          const I_CHAR *pathName, bool autoPromote );
   virtual ~Frame();

   /**
    * check if frame is complete
    * 
    * @return BOOL - TRUE if frame is complete, FALSE if not
    */
   bool isComplete( void ) const
   {
      return(_completionFlag);
   }

   /**
    * check if frame was flagged as top level frame -
    * top level frames are not deleted
    * 
    * 
    * @return BOOL - true if frame is marked as top level
    *
    */
   bool isTopLevel( void ) const
   {
      return(_fTopLevel);
   }

   /**
    * check if frame should auto promote conditions
    * from lower levels.
    * 
    * 
    * @return bool - true if auto promote is on, false if not
    *
    */
   bool isAutoPromote( void ) const
   {
      return(_fAutoPromote);
   }

   /**
    * get the component name string from the frame
    * 
    * @return component name
    */
   const DString getComponentName() const
   {
      return(_componentName);
   }

   /**
    * get the specified condition from the frame
    * 
    * @param idx    index of condition to get
    * @return pointer to condition, NULL if not exist
    */
   Condition *getCondition( unsigned idx );

   /**
    * get count of number of conditions on frame
    * 
    * @return condition count
    */
   unsigned getCount( void )
   {
      return(_conditions.size());
   }

   /**
    * get the method string from the frame
    * 
    * @return const DString & - method
    */
   const DString getMethodName( void ) const
   {
      return(_methodName);
   }

   /**
    * get the level number from the frame
    * 
    * @return level number
    */
   unsigned getLevel( void ) const
   {
      return(_level);
   }

   /**
    * get the thread ID number from the frame
    * 
    * 
    * @return int - thread ID
    *
    */
   int getThreadID( void ) const
   {
      return(_threadID);
   }

   /**
    * return the maximum severity for all conditions
    * on the frame.
    * 
    * @return maximum severity
    */
   SEVERITY getMaxSeverity( void ) const
   {
      return(_maxSeverity);
   }

   /**
    * find a specific component/code in the list
    * of conditions on the frame
    * 
    * @param component component name to search for
    * @param code   condition code to search for
    * @return Condition if found, NULL if not
    */
   Condition *findCondition( const I_CHAR *component, long code );

   /**
    * add condition to frame
    * 
    * @param pCond  pointer to condition to add
    */
   void addCondition( Condition *pCond );

   void addConditionFromObject(CConditionObject& object, 
                              const char *fileName,
                              unsigned lineNumber,
                              BOOL baseCondition,
                              SEVERITY severity,
                              const DString & str1 = NULL_STRING,
                              const ClientLocale *clientLocale = NULL,
                              const DString & context = NULL_STRING );


   void addConditionFromObject(CConditionObject& object,  
                              const char * fileName,
                              unsigned lineNumber,
                              const DString & str1 = NULL_STRING,
                              BOOL baseCondition = FALSE,
                              SEVERITY severity = NO_CONDITION,
                              const ClientLocale *clientLocale = NULL );

   /**
    * add condition to frame
    * 
    * @param code   condition code
    * @param fileName source file name
    * @param lineNumber source file line number
    * @param baseCondition
    *                   TRUE if use base file, FALSE if not
    * @param severity severity level
    * @param str1   replacement string 1
    *               (name1=value1;name2=value2;...)
    * @param clientLocale Override current condition locale
    * @param fDoIdiSubstitutionNow
    *                   Flag controls if idi substitution is processed
    *                   immediately or wait and allow a different locale
    * @param context Additional information to pass with the condition
    */
   void addConditionFromFile( long code, 
                              const I_CHAR* codeStr,
                              const char *fileName,
                              unsigned lineNumber,

                              BOOL baseCondition,
                              SEVERITY severity,
                              const DString & str1 = NULL_STRING,
                              const ClientLocale *clientLocale = NULL,
                              const DString & context = NULL_STRING );



   /**
    * add condition to frame
    * 
    * @param code   condition code
    * @param fileName source file name
    * @param lineNumber source file line number
    * @param str1   replacement string 1
    *               (name1=value1;name2=value2;...)
    * @param baseCondition
    *                   TRUE if use base file, FALSE if not
    * @param severity severity level
    */
   void addConditionFromFile( long code,  
                              const I_CHAR* codeStr,
                              const char * fileName,
                              unsigned lineNumber,

                              const DString & str1 = NULL_STRING,
                              BOOL baseCondition = FALSE,
                              SEVERITY severity = NO_CONDITION,
                              const ClientLocale *clientLocale = NULL );

   /**
    * add condition to frame
    * 
    * @param ce     condition exception
    * @param fileName source file name
    * @param lineNumber source file line number
    */
   void addConditionFromException( ConditionException &ce,
                                   const char *fileName,
                                   unsigned lineNumber );

   /**
    * set frame completion flag
    * 
    * 
    * @param flag value, TRUE = frame complete
    *
    */
   void setCompletionFlag( bool flag );

   /**
    * set frame level number
    * 
    * @param lvl    frame level
    */
   void setLevel( unsigned lvl )
   {
      _level = lvl;
   }

   /**
    * set flag indicating this frame is a top level frame,
    * and should not be deleted automatically
    * 
    * @param fTop   true if frame is top level
    */
   void setTopLevel( bool fTop )
   {
      _fTopLevel = fTop;
   }

   /**
    * set the auto promote flag for the frame
    * 
    * @param fAutoPromote
    *               true if frame should auto promote conditions
    */
   void setAutoPromote ( bool fAutoPromote )
   {
      _fAutoPromote = fAutoPromote;
   }

   /**
    * remove all conditions from the frame
    * 
    * @param fFree  true if memory should be freed, false if not
    */
   void clearConditions( bool fFree );

   /**
    * remove a single condition from the frame - the indexes
    * of any conditions after the one being removed will be shifted
    * 
    * @param idx    index of the condition to remove
    */
   void clearCondition( int idx );

   /**
    * Loops through list of conditions held by frame.
    * Deleted duplicate conditions based on same
    * code and message
    */
   void packConditions( void );


private:
   // private data
   /*const I_CHAR _pathName[TEXT_LENGTH];
   const I_CHAR _componentName[TEXT_LENGTH];
   const I_CHAR _methodName[TEXT_LENGTH];
   const char _fileName[TEXT_LENGTH];
   */
   I_CHAR _pathName[TEXT_LENGTH];
   I_CHAR _componentName[TEXT_LENGTH];
   I_CHAR _methodName[TEXT_LENGTH];
   char _fileName[TEXT_LENGTH];
   const int _lineNumber;
   int _threadID;
   unsigned _level;
   bool _fAutoPromote;
   bool _fTopLevel;
   bool _completionFlag;
   SEVERITY _maxSeverity;
   CONDITIONVECTOR _conditions;

   Frame( const Frame &copy );
   const Frame &operator=( const Frame &copy );

   long generateConditionID() const;
   long getConditionIDForObject(const DString& conditionName);

   typedef std::map<DString, long> ConditionNameToIdMap;
   ConditionNameToIdMap mapConditionNameToID;
};


//CP20040924#pragma warning( pop )


//************************************************************************
//              Revision Control Entries
//************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/core/ifdscore/frame.hpp-arc  $
//
//   Rev 1.3   Sep 23 2009 01:32:18   purdyech
//Track Condition Name as well as Code.
//Add "Display Details" option to system menu on Error Popup.
//
//   Rev 1.2   Sep 27 2004 09:40:32   PURDYECH
//Clean up compiler warnings so that there are no complaints about silly things (like truncated debug names...)
//
//   Rev 1.1   Oct 09 2002 17:42:02   PURDYECH
//New PVCS Database
//
//   Rev 1.0   Jul 05 2002 10:14:56   SMITHDAV
//Initial revision.
// 
//    Rev 1.16   25 Oct 2000 11:04:40   dt14177
// cleanup
// 
//    Rev 1.15   23 Aug 2000 21:17:30   dt20842
// Added ability to pass clientLocale through macros.
// Added lazy initialization to Condition.
// 
//    Rev 1.14   13 Jan 2000 14:30:40   dt20842
// Updated JavaDoc comments
// 
//    Rev 1.13   Jan 07 2000 13:05:32   DT20842
// Added more JavaDoc comments
// 
//    Rev 1.12   Dec 29 1999 10:42:46   DT20842
// Added package comment line
// 
//    Rev 1.11   Dec 28 1999 08:42:08   DT20842
// Changed to JavaDoc style comments
// 
//    Rev 1.10   Jun 22 1999 11:10:10   DT14177
// Changed type for condition code from int to long.
// 
//    Rev 1.9   Jun 08 1999 16:17:48   DT14177
// added context, delayed condition message preparation, and locale override.
// 
//    Rev 1.8   01 Apr 1999 14:37:40   DT14177
// Changed parameter type from I_CHAR * to DString &
// 
//    Rev 1.7   25 Feb 1999 11:28:26   DT14177
// created default parameter in constructor
// 
//    Rev 1.6   24 Feb 1999 10:45:12   DT14177
// sync up with tracer
// 
//    Rev 1.5   22 Feb 1999 11:46:54   DT14177
// fixed DString and const I_CHAR stuff
// 
//    Rev 1.4   18 Feb 1999 10:39:52   DT14177
// UNICODE
// 
//    Rev 1.3   Jan 28 1999 14:06:30   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.2   Dec 09 1998 13:42:02   DMUM
// Check in for DICORE
// 
//    Rev 1.1   Aug 27 1998 15:56:48   DTWK
// Checkin CBO team's additions to frame/condition stuff
// 
//    Rev 1.0   29 Jul 1998 20:37:30   DT14596
// DLMG New Archives for TA2000NTDT
// 
//    Rev 1.11   Jul 02 1998 16:35:12   DTWK
// Update with changes from Paul Dardeau
//
//    Rev 1.10   Jun 16 1998 16:11:48   dt27994
//
//
//    Rev 1.9   Dec 12 1997 14:47:34   dkaw
// add findCondition
//
//    Rev 1.8   Nov 09 1997 15:34:38   DTWK
// Add inclusion guards for faster compiles.
// Add guards so that class is flagged as exported only when compiling
// the output that actually exports the class.
//
//    Rev 1.7   Oct 21 1997 14:10:16   dkaw
// add _fTraced, change parm to doTrace
//
//    Rev 1.6   Sep 08 1997 15:57:10   dkaw
// add setApplicationName
//
//    Rev 1.5   Sep 04 1997 11:27:18   dkaw
// add autoPromote, clearCondition()
//
//    Rev 1.4   Sep 02 1997 15:52:20   dkaw
// add setTopLevel(), isTopLevel()
//
//    Rev 1.3   Aug 28 1997 14:00:04   dkaw
// change NO_ERR to NO_SEVERITY
//
//    Rev 1.2   Aug 25 1997 15:51:00   dkaw
// add _maxSeverity, getMaxSeverity()
//
//    Rev 1.1   Jul 22 1997 16:22:42   dkaw
// add trace filter, use ditrace
//
//    Rev 1.0   Jun 13 1997 12:56:20   DTWK
//

