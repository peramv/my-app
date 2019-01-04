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
//    Copyright 1997 by DST Systems, Inc.
//
//**********************************************************************
//
// ^FILE   : Frame.cpp
// ^AUTHOR : Jerry Leenerts
// ^DATE   : 5/8/97
//
// ----------------------------------------------------------
//
// ^CLASS    : Frame
//
// ^MEMBER VARIABLES :
//    ^^ BOOL _completionFlag - true if frame has completed
//    ^^ const string _componentName - condition component name'
//    ^^ CONDITIONVECTOR _conditions - list of conditions on frame
//    ^^ bool _fAutoPromote - auto promote conditions flag
//    ^^ bool _fTopLevel - is frame top level
//    ^^ const string _fileName - source file name of calling function
//    ^^ unsigned _level - stack level of calling function
//    ^^ SEVERITY _maxSeverity - highest severity of conditions on frame
//    ^^ const string _methodName - method name of calling function
//       (format is class::method)
//    ^^ const int _lineNumber - source file line number of calling
//                               function
//    ^^ const string _pathName - path name for condition component 
//                                files
//    ^^ int _processID - process ID
//    ^^ int _threadID - thread ID
//    ^^ static FrameTraceFilter _traceFilter - trace filtering 
//                                              information
//
// ^CODING COMMENTS  :
//
//**********************************************************************
#define DICORE_DLL

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif
#ifndef FRAME_HPP
   #include "frame.hpp"
#endif
#ifndef STRINGFUNCTIONS_HPP
   #include "stringfunctions.hpp"
#endif
#ifndef DIPORT1_H
   #include "diport.h"
#endif
#ifndef INCLUDED_SET
#define INCLUDED_SET
#include <set>
#endif

#ifndef REGISTRYKEY_HPP
   #include "registrykey.hpp"
#endif

#ifndef REGISTRYVALUE_HPP
   #include "registryvalue.hpp"
#endif

#ifndef CRITICALSECTION_HPP
   #include "criticalsection.hpp"
#endif

static MutexSemaphore sema4;

Frame::Frame( const I_CHAR *componentName, const I_CHAR *methodName,
              const char *fileName, int lineNumber,
              const I_CHAR *pathName, bool autoPromote ) :
_lineNumber( lineNumber ),
_fAutoPromote( autoPromote ), _completionFlag( FALSE ),
_maxSeverity( NO_CONDITION ), _fTopLevel( FALSE ),
_threadID( DSTGetCurrentThreadId() )
{
   memset( _componentName, 0, TEXT_LENGTH * sizeof( I_CHAR ) );
   i_strncpy( _componentName, componentName, TEXT_LENGTH - 2 );

   memset( _methodName, 0, TEXT_LENGTH * sizeof( I_CHAR ) );
   i_strncpy( _methodName, methodName, TEXT_LENGTH - 2 );

   memset( _fileName, 0, TEXT_LENGTH );
   strncpy( _fileName, fileName, TEXT_LENGTH - 2 );

   memset( _pathName, 0, TEXT_LENGTH * sizeof( I_CHAR ) );
   i_strncpy( _pathName, pathName, TEXT_LENGTH - 2 );
}


Frame::~Frame()
{
   clearConditions( TRUE );
}


void Frame::addCondition( Condition *pCnd )
{
   _conditions.push_back( pCnd );
   SEVERITY severity = pCnd->getSeverity();
   if( severity > _maxSeverity )
   {
      _maxSeverity = severity;
   }
}


static int noSuppression = -1;

#pragma warning( push )
#pragma warning( disable: 4800 )

bool allowSuppression()
{
   if( -1 == noSuppression )
   {
      CriticalSection cs( sema4 );

      noSuppression = false;

#ifdef _WIN32

      DStringA registryPath( "SOFTWARE\\DST\\DICORE\\Config\\DataPath"\
                           );
      RegistryKey rkDataPath( registryPath );
      RegistryValue rvDataPath = rkDataPath.getValue(
                                                    "allowConditionSupression" );

      if( RegistryValue::STRING == rvDataPath.getType() )
      {
         DString path = rvDataPath.getAsString();
         if( path.size() && '1' == path[ 0 ] )
         {
            noSuppression = true;
         }
      }
   }

#endif

   return(noSuppression);
}

#pragma warning( pop )

void Frame::addConditionFromException( ConditionException &ce,
                                       const char *fileName,
                                       unsigned lineNumber )
{

   Condition * condition = new Condition( ce.getCondition() );

   // if there was a problem creating the condition or the severity
   //   is severe error or greater, add the condition
   // if it's debug, add the condition unless a registry setting
   //   is set

   if( false == condition->getSuppress() ||
       TRACE_ONLY > condition->getSeverity() ||
       WARNING < condition->getSeverity()
#ifdef _DEBUG
       || !allowSuppression() )
#else
     )
#endif
   {
      addCondition( condition );
   }
   else
      delete condition;
}


void Frame::addConditionFromFile( long code, 
                                  const I_CHAR* codeStr,
                                  const char *fileName,
                                  unsigned lineNumber, 
                                  BOOL baseCondition,
                                  SEVERITY severity,
                                  const DString & str1,
                                  const ClientLocale *clientLocale,
                                  const DString & context )
{
   Condition * condition = new Condition( getComponentName(), 
                                          getMethodName(), 
                                          code,
                                          codeStr,
                                          fileName,
                                          lineNumber, 
                                          baseCondition,
                                          (I_CHAR *)_pathName, 
                                          severity,
                                          str1,
                                          clientLocale,
                                          context );
   // if there was a problem creating the condition or the severity
   //   is severe error or greater, add the condition
   // if it's debug, add the condition unless a registry setting
   //   is set

   if( false == condition->getSuppress() ||
       TRACE_ONLY > condition->getSeverity() ||
       WARNING < condition->getSeverity()
#ifdef _DEBUG
       || !allowSuppression() )
#else
     )
#endif
   {
      addCondition( condition );
   }
   else
      delete condition;
}




void Frame::addConditionFromFile( long code, 
                                  const I_CHAR* codeStr,
                                  const char *fileName,
                                  unsigned lineNumber,

                                  const DString & str1,
                                  BOOL baseCondition,
                                  SEVERITY severity,
                                  const ClientLocale *clientLocale )
{
   Condition * condition = new Condition( getComponentName(), 
                                          getMethodName(), 
                                          code,
                                          codeStr,
                                          fileName,
                                          lineNumber, 
                                          baseCondition,
                                          (I_CHAR *)_pathName,
                                          severity,
                                          str1,
                                          clientLocale);
   // if there was a problem creating the condition or the severity
   //   is severe error or greater, add the condition
   // if it's debug, add the condition unless a registry setting
   //   is set

   if( false == condition->getSuppress() ||
       TRACE_ONLY > condition->getSeverity() ||
       WARNING < condition->getSeverity()
#ifdef _DEBUG
       || !allowSuppression() )
#else
     )
#endif
   {
      addCondition( condition );
   }
   else
      delete condition;
}


void Frame::clearConditions( bool fFree )
{
   CONDITIONVECTOR::iterator it;

   if( !_conditions.empty() )
   {
      if( fFree )
      {
         for( it = _conditions.begin(); it != _conditions.end(); it++ )
         {
            delete *it;                         // Delete condition
         }
      }
      _conditions.clear();
      _maxSeverity = NO_CONDITION;
   }
}

// disable signed/unsigned comparison warning
#pragma warning( push )
#pragma warning( disable: 4018 ) 

void Frame::clearCondition( int idx )
{
   if( ( idx < _conditions.size() ) &&
       ( idx >= 0 ) )
   {

      CONDITIONVECTOR::iterator it;
      it = _conditions.begin() + idx;
      delete *it;
      _conditions.erase( it );

      _maxSeverity = NO_CONDITION;
      for( it = _conditions.begin(); it != _conditions.end(); it++ )
      {
         if( (*it)->getSeverity() > _maxSeverity )
         {
            _maxSeverity = (*it)->getSeverity();
         }
      }
   }
}
#pragma warning( pop )

Condition *Frame::getCondition( unsigned idx )
{
   int nTempSize = _conditions.size();
   if( _conditions.size() < idx + 1 )
      return(NULL);                           // out of range
   return(*( _conditions.begin() + idx ));
}

Condition *Frame::findCondition( const I_CHAR *component, long code )
{
   Condition *cnd = NULL;

   // are there any conditions on this frame?
   if( _conditions.size() )
   {
      // loop through conditions looking from component and code
      CONDITIONVECTOR::iterator it;
      for( it = _conditions.begin(); it != _conditions.end(); it++ )
      {
         if( !i_strcmp( ((Condition *)*it)->getComponentName(), 
                        component ) &&
             ( ((Condition *)*it)->getCode() == code ) )
         {
            cnd = (Condition *)*it;
            break;
         }
      }
   }

   return(cnd);
}

void Frame::setCompletionFlag( bool flag )
{
   _completionFlag = flag;
}

void Frame::packConditions( void )
{

   typedef std::set<int> SETINT;

   SETINT setIndexesToDelete;

   int nCondOuter = 0;
   int nCondInner = 0;
   int nCondSize  = _conditions.size();

   // Determine what indexes we want to delete!
   while( nCondOuter < nCondSize )
   {
      nCondInner = nCondOuter;
      ++nCondInner;

      int nOuterCondCode = _conditions[nCondOuter]->getCode();

      while( nCondInner < nCondSize )
      {
         if( nOuterCondCode == _conditions[nCondInner]->getCode() )
         {
            if( i_strcmp( _conditions[nCondOuter]->getMessage(),
                          _conditions[nCondInner]->getMessage() ) == 0 )
            {
               setIndexesToDelete.insert( nCondInner );
            }
         }

         ++nCondInner;
      }

      ++nCondOuter;
   }

   // Stroke thru setIndexesToDelete and delete the items

   if( setIndexesToDelete.size() )
   {
      SETINT::iterator iterDeleteBegin = setIndexesToDelete.begin();
      SETINT::iterator iterDeleteEnd   = setIndexesToDelete.end();

      while( iterDeleteBegin != iterDeleteEnd )
      {
         clearCondition( (*iterDeleteBegin) );
         ++iterDeleteBegin;
      }
   }

   return;

}
//**********************************************************************
//              Revision Control Entries
//**********************************************************************
//
// $Log:   Y:/VCS/iFastAWD/dicore/frame.cpp-arc  $
// 
//    Rev 1.1   Nov 02 2011 04:43:04   purdyech
// Registry Cleanup
//
//   Rev 1.3   Sep 23 2009 01:31:30   purdyech
//Track Condition Name as well as Code.
//Add "Display Details" option to system menu on Error Popup.
//
//   Rev 1.2   Sep 27 2004 09:40:34   PURDYECH
//Clean up compiler warnings so that there are no complaints about silly things (like truncated debug names...)
// 
//    Rev 1.1   Oct 09 2002 17:42:00   PURDYECH
// New PVCS Database
// 
//    Rev 1.0   Jul 05 2002 10:14:08   SMITHDAV
// Initial revision.
// 
//    Rev 1.13   17 May 2001 15:05:36   dt14177
// use Condition copy constructor to
// add a Condition to the Frame from a
// ConditionException
// 
//    Rev 1.12   Apr 05 2001 11:04:42   dt24433
// Fixed leak in clearCondition and simplified.
// 
//    Rev 1.11   23 Aug 2000 21:18:12   dt20842
// Added ability to pass clientLocale through macros.
// Added lazy initialization.
// 
//    Rev 1.10   Oct 06 1999 07:20:50   dtwk
// Fix release mode compiles
// 
//    Rev 1.9   Oct 05 1999 16:54:08   DT14177
// Added suppression and language severity enhancements; fixed multi-threading issues
// 
//    Rev 1.8   Sep 28 1999 14:29:52   DT14177
// fixed multi-threading bug
// 
//    Rev 1.7   Jun 22 1999 11:10:04   DT14177
// Changed type for condition code from int to long.
// 
//    Rev 1.6   Jun 08 1999 16:17:42   DT14177
// added context, delayed condition message preparation, and locale override.
// 
//    Rev 1.5   01 Apr 1999 14:37:38   DT14177
// Changed parameter type from I_CHAR * to DString &
// 
//    Rev 1.4   24 Feb 1999 10:44:14   DT14177
// sync up with tracer
// 
//    Rev 1.3   22 Feb 1999 13:57:32   DT14177
// more UNICODE stuff
// 
//    Rev 1.2   18 Feb 1999 10:38:14   DT14177
// UNICODE
// 
//    Rev 1.1   Jan 28 1999 14:02:56   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.0   Dec 09 1998 13:51:14   DMUM
//
//
//    Rev 1.1   Aug 27 1998 15:56:34   DTWK
// Checkin CBO team's additions to frame/condition stuff
//
//    Rev 1.0   29 Jul 1998 20:29:52   DT14596
// DLMG New Archives for TA2000NTDT
//
//    Rev 1.12   Jul 02 1998 16:34:42   DTWK
// Update with changes from Paul Dardeau
//
//    Rev 1.11   Jun 16 1998 16:11:00   dt27994
//
//
//    Rev 1.10   Dec 12 1997 14:49:12   dkaw
// add findCondition
//
//    Rev 1.9   Nov 09 1997 15:35:40   DTWK
// Add inclusion guards for faster compiles.
// Add guards so that class is flagged as exported only when compiling
// the output that actually exports the class.
//
//    Rev 1.8   Oct 21 1997 14:11:36   dkaw
// set _fTraced in constructor, check it in setCompletionFlag;
// add const strings, use them in doTrace, change parm to doTrace;
//
//    Rev 1.7   Oct 08 1997 13:09:56   dkaw
// comment out tracing in Frame constructor - THIS IS A TEMPORARY CHANGE TO HIDE A BUG.
//
//    Rev 1.6   Sep 08 1997 15:58:06   dkaw
//
//
//    Rev 1.5   Sep 04 1997 11:28:18   dkaw
// add autopromote, clearCondition()
//
//    Rev 1.4   Sep 02 1997 15:50:14   dkaw
// initialize _fTopLevel to FALSE in constructor
//
//    Rev 1.3   Aug 28 1997 14:02:22   dkaw
// change NO_COND to NO_CONDITION
//
//    Rev 1.2   Aug 25 1997 16:00:42   dkaw
// add _maxSeverity, use "" not <> for stringfunctions.hpp
//
//    Rev 1.1   Jul 22 1997 16:18:26   dkaw
// add trace filtering, use ditrace
//
//    Rev 1.0   Jun 13 1997 12:54:58   DTWK
//
//
//
