// Remove this reminder text and the #include conditionmigrate.hpp
// before you check in this file

// added to fix a linkage problem
#define DICORE_DLL

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
// ^FILE   : ConditionManager.cpp
// ^AUTHOR : Jerry Leenerts
// ^DATE   : 5/6/97
//
// ----------------------------------------------------------
//
// ^CLASS    : ConditionManager
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//**********************************************************************
#ifndef DICORE_DLL
#define DICORE_DLL
#endif

#ifndef SRCPRAG_H
   #include "srcprag.h"
#endif

#pragma warning( push )
#pragma warning( disable: 4355 )

#define ConditionManager_cpp
#include "conditionmanager.hpp"
#undef ConditionManager_cpp

#ifndef CRITICALSECTIONLOCK_HPP
   #include "CriticalSectionLock.hpp"
#endif

#ifndef DATAPATH_H
   #include "datapath.h"
#endif

#ifndef GUARD_HPP
   #include "Guard.hpp"
#endif

#ifndef STRINGFUNCTIONS_HPP
   #include "stringfunctions.hpp"
#endif

namespace
{
   CriticalSectionLock lock;
}

// tls = abreviation for thread local storage
__declspec( thread ) FRAMEVECTOR *tls_pFrames = NULL;
void deleteFrames();

//**********************************************************************
//              Public Methods
//**********************************************************************

ConditionManager *ConditionManager::getInstance()
{
   if( s_pManager )
   {
      return(s_pManager);
   }

   Guard crit( &lock );
   if( !s_pManager )
   {
      s_pManager = new ConditionManager;
   }

   return(s_pManager);
}

ConditionManager::ConditionManager( void ) :
m_register(  deregister, (void *)this  )
{
   DString strAppName;

   if( FindApplication( strAppName ) )
   {
      setApplicationName( strAppName.c_str() );
   }
   else
   {
      // If there is no application, then the result of this
      // will be that all CND files are expected to be in the
      // current directory.
      setApplicationName( I_( "DICORE" ) );
   }
}

ConditionManager::~ConditionManager( void )
{
   deleteFrames();
}

void ConditionManager::setApplicationName( const I_CHAR *appName )
{
   if( _appName != appName )
   {
      _appName = appName;
      getConfigurationValues();
   }
}

void ConditionManager::getConfigurationValues( )
{
   if( ! GetDataPath( _cndPath, _appName ) )
   {
      _cndPath = I_( ".\\" );
   }
}

void ConditionManager::endFrame( Frame *fr )
{
   unsigned last;

   if( tls_pFrames )
   {
      fr->setCompletionFlag( TRUE );   // Flag as done
      last = tls_pFrames->size() - 1;      // Get highest level on our stack
      if( ( last > fr->getLevel() ) ||
          ( 0 == last && !fr->isTopLevel() ) )
      {  // Remove frame below this one  - There should only be 1 !
         if( fr->isAutoPromote() )
         {
            promoteAll( fr, __FILE__, __LINE__ );
         }
         Frame* pFrame = tls_pFrames->back();
         delete pFrame;
         tls_pFrames->pop_back();                   // Remove last frame

      }
   }
}

Condition *ConditionManager::findCondition( Frame *fr,
                                            const I_CHAR *component,
                                            int code, bool fUseCurrent )
{
   if( fUseCurrent )
   {
      if( fr->isAutoPromote() )
      {
         promoteAll( fr, __FILE__, __LINE__ );
      }
      return(fr->findCondition( component, code ));
   }
   else
   {
      Frame *frBelow = getFrameBelow( fr );
      if( frBelow )
      {
         return(frBelow->findCondition( component, code ));
      }
   }
   return(NULL);
}

Condition *ConditionManager::getCondition( Frame *fr, int idx )
{
   Frame *frBelow = getFrameBelow( fr );
   if( frBelow )
   {
      return(frBelow->getCondition( idx ));
   }
   return(NULL);
}

int ConditionManager::getConditionCount( Frame *fr )
{
   Frame *frBelow = getFrameBelow( fr );
   if( frBelow )
   {
      return(frBelow->getCount( ));
   }
   return(0);
}

Frame *ConditionManager::getFrameBelow( Frame *fr )
{
   unsigned lvl = fr->getLevel();
   // level is 0-based; add 1 because size is 1-based, add 1 for next level
   if( tls_pFrames && ( tls_pFrames->size() ==  lvl + 2 ) )
   {
      return(tls_pFrames->back());
   }
   return(NULL);
}

SEVERITY ConditionManager::getMaxSeverity( Frame *fr,
                                           bool fUseCurrent )
{
   if( fUseCurrent )
   {
      if( fr->isAutoPromote() )
      {
         promoteAll( fr, __FILE__, __LINE__ );
      }
      return(fr->getMaxSeverity());
   }
   else
   {
      Frame *frBelow = getFrameBelow( fr );
      if( frBelow )
      {
         return(frBelow->getMaxSeverity( ));
      }
   }
   return(NO_CONDITION);
}

void ConditionManager::clearConditions( Frame *fr )
{
   Frame *frBelow = getFrameBelow( fr );
   if( frBelow )
   {
      frBelow->clearConditions( TRUE );
   }
}

void ConditionManager::clearCondition( Frame *fr, int idx )
{
   Frame *frBelow = getFrameBelow( fr );
   if( frBelow )
   {
      frBelow->clearCondition( idx );
   }
}

void ConditionManager::promoteAll( Frame *fr, const char *fileName,
                                   unsigned lineNumber )
{
   Frame *frBelow = getFrameBelow( fr );
   if( frBelow )
   {
      int count = frBelow->getCount();

      for( int i = 0; i < count; i++ )
      {
         // Move each condition from lower frame up to this one
         // Condition keeps original data
         fr->addCondition( frBelow->getCondition( i ) );
      }
      frBelow->clearConditions( FALSE );
   }
}

Frame *ConditionManager::startFrame( const I_CHAR *componentName,
                                     const I_CHAR *methodName, const char *fileName,
                                     int lineNumber, const I_CHAR *pathName, BOOL promote )
{
   Frame *newFrame;
   newFrame = new Frame( componentName,
                         methodName,
                         fileName,
                         lineNumber,
                         (const I_CHAR *)_cndPath.c_str(),
                         0 != promote );
   startFrame( newFrame );
   return( newFrame );
}

void ConditionManager::startFrame( Frame *fr )
{
   if( tls_pFrames == NULL )
   { // Need to create new one
      tls_pFrames = new FRAMEVECTOR;
   }

   // don't leave complete frames on list
   if( !tls_pFrames->empty() && tls_pFrames->back()->isComplete() )
   {
      fr->setLevel( tls_pFrames->size() - 1 );
      if( fr->getLevel() > 0 )
      {
         // size is 1-based, so size-1 is level of last frame,
         // size-2 is level of frame above that
         Frame *frAbove = tls_pFrames->at( tls_pFrames->size() - 2 );
         if( frAbove->isAutoPromote() )
         {
            promoteAll( frAbove, __FILE__, __LINE__ );
         }
      }
      delete tls_pFrames->back();
      tls_pFrames->back() = fr;
   }
   else
   {
      fr->setLevel( tls_pFrames->size() );       // Save new level in frame
      tls_pFrames->push_back( fr );              // Add new frame
   }
}

//******************************************************************************
//              Private Methods
//******************************************************************************

void deleteFrames()
{
   if( tls_pFrames )
   {
      FRAMEVECTOR::iterator fvIt;

      for( fvIt = tls_pFrames->begin();
         fvIt != tls_pFrames->end();
         fvIt++ )
      {  // Delete frame
         delete *fvIt;
      }
      tls_pFrames->clear();
      delete tls_pFrames;                   // Delete frame vector
      tls_pFrames = NULL;                   // Needed if singleton is reused
   }
}

void ConditionManager::deregister( void *pObj )
{
   const ConditionManager *pMgr = (ConditionManager *)pObj;

   if( pMgr == s_pManager )
   {
      delete s_pManager;
      s_pManager = NULL;
   }
}


//**********************************************************************
// CLASS: CMFrame
//**********************************************************************

CMFrame::CMFrame( const I_CHAR *componentName,
                  const I_CHAR *methodName,
                  const char *fileName,
                  int lineNumber,
                  const I_CHAR *pathName,
                  BOOL toplevel,
                  bool autopromote )
{
   _pFrame = g_conditionManager.startFrame( componentName,
                                            methodName,
                                            fileName,
                                            lineNumber,
                                            pathName,
                                            autopromote );
   if( toplevel )
   {
      _pFrame->setTopLevel( 0 != toplevel );
   }
}


CMFrame::~CMFrame( void )
{
   g_conditionManager.endFrame( _pFrame );
}


//**********************************************************************
//              Public Methods for ConditionManagerContainer
//**********************************************************************

ConditionManager *ConditionManager::s_pManager = NULL;

void ConditionManagerContainer::killInstance (void)
{
   // Do nothing
}

ConditionManagerContainer::ConditionManagerContainer( void )
{
}

ConditionManagerContainer::~ConditionManagerContainer( void )
{
}

const I_CHAR * ConditionManagerContainer::getPath( void )
{
   ConditionManager *p = getInstance();
   return(p ? p->getPath() : NULL);
}

void ConditionManagerContainer::setApplicationName( const I_CHAR *
                                                    appName )
{
   ConditionManager *p = getInstance();

   if( p )
   {
      p->setApplicationName(appName);
   }
}

void ConditionManagerContainer::endFrame( Frame *fr )
{
   ConditionManager *p = getInstance();

   if( p )
   {
      p->endFrame(fr);
   }
}

Condition *ConditionManagerContainer::findCondition( Frame *fr,
                                                     const I_CHAR *component,
                                                     int code,
                                                     bool fUseCurrent )
{
   ConditionManager *p = getInstance();
   return(p ? p->findCondition(fr, component, code, fUseCurrent) :
          NULL);
}

Condition *ConditionManagerContainer::getCondition( Frame *fr, int idx )
{
   ConditionManager *p = getInstance();
   return(p ? p->getCondition(fr, idx) : NULL);
}

int ConditionManagerContainer::getConditionCount( Frame *fr )
{
   ConditionManager *p = getInstance();
   return(p ? p->getConditionCount(fr) : NULL);
}

Frame *ConditionManagerContainer::getFrameBelow( Frame *fr )
{
   ConditionManager *p = getInstance();
   return(p ? p->getFrameBelow(fr) : NULL);
}

SEVERITY ConditionManagerContainer::getMaxSeverity( Frame *fr,
                                                    bool fUseCurrent )
{
   ConditionManager *p = getInstance();
   return(p ? p->getMaxSeverity(fr, fUseCurrent) : ( SEVERITY ) NULL);
}

void ConditionManagerContainer::clearConditions( Frame *fr )
{
   ConditionManager *p = getInstance();

   if( p )
   {
      p->clearConditions(fr);
   }
}

void ConditionManagerContainer::clearCondition( Frame *fr, int idx )
{
   ConditionManager *p = getInstance();

   if( p )
   {
      p->clearCondition(fr, idx);
   }
}

void ConditionManagerContainer::promoteAll( Frame *fr,
                                            const char *fileName,
                                            unsigned lineNumber )
{
   ConditionManager *p = getInstance();

   if( p )
   {
      p->promoteAll(fr, fileName, lineNumber);
   }
}

Frame *ConditionManagerContainer::startFrame( const I_CHAR *
                                              componentName,
                                              const I_CHAR *methodName,
                                              const char *fileName,
                                              int lineNumber,
                                              const I_CHAR *pathName,
                                              BOOL promote )
{
   ConditionManager *p = getInstance();
   return( p ? p->startFrame( componentName,
                              methodName,
                              fileName,
                              lineNumber,
                              pathName,promote) :
           NULL);
}

void ConditionManagerContainer::startFrame( Frame *fr )
{
   ConditionManager *p = getInstance();

   if( p )
   {
      p->startFrame(fr);
   }
}

//************************************************************************
//              Revision Control Entries
//**********************************************************************
//
// $Log:   Y:/VCS/BF Core/ifdscore/conditionmanager.cpp-arc  $
//
//   Rev 1.2   Sep 27 2004 09:40:36   PURDYECH
//Clean up compiler warnings so that there are no complaints about silly things (like truncated debug names...)
// 
//    Rev 1.1   Oct 09 2002 17:41:48   PURDYECH
// New PVCS Database
// 
//    Rev 1.0   Jul 05 2002 10:12:46   SMITHDAV
// Initial revision.
// 
//    Rev 1.17   May 25 2001 16:33:58   DT11159
// Set tls_pFrames to NULL after delete.  This is needed
// so that the following sequence will work:
// ConditionManager::getInstance
// SingletonRegister::releaseSingletons
// ConditionManager::getInstance
//
//    Rev 1.16   May 18 2001 14:32:18   dt24433
// Changed to use thread local storage to manage thread specific
// data - no longer explicitly support moving conditions across threads.
// Switch to use Guard/CriticalSectionLock instead of CriticalSection/MutexSemaphore.
//
//    Rev 1.15   Jan 02 2001 18:12:08   dt24433
// Changed to not always use Critical Section on getInstance.
//
//    Rev 1.14   Apr 05 2000 15:23:00   DMUM
// Removal of Larry Code
//
//    Rev 1.13   Mar 29 2000 16:56:28   DMUM
// Fixed deleteFrameList()
//
//    Rev 1.12   Mar 22 2000 17:25:00   DT14177
// fixed link warning for local linkage of DString and DStringA
//
//    Rev 1.11   Mar 08 2000 07:02:20   DT20842
// Wrong project check-in; reverting to previous version
//
//    Rev 1.9   Feb 24 2000 10:45:40   DMUM
// Removed compile & link warnings
//
//    Rev 1.8   Dec 23 1999 17:49:44   DT14177
// Made some changes required by the build process
//
//    Rev 1.7   Sep 28 1999 14:29:50   DT14177
// fixed multi-threading bug
//
//    Rev 1.6   Sep 16 1999 16:28:04   DT14177
// memory leak cleanup
//
//    Rev 1.5   Jul 07 1999 16:42:06   DT14177
// fixed miscellaneous bugs.
//
//    Rev 1.3   24 Feb 1999 10:44:00   DT14177
// sync up with tracer
//
//    Rev 1.1   Jan 28 1999 14:02:28   DMUM
// Check in for VCPP 6.0
//
//    Rev 1.0   Dec 09 1998 13:50:54   DMUM
//
//
//    Rev 1.15   Jul 02 1998 16:34:38   DTWK
// Update with changes from Paul Dardeau
//
//    Rev 1.14   Jun 16 1998 16:10:58   dt27994
//
//
//    Rev 1.13   Dec 12 1997 14:49:10   dkaw
// add findCondition
//
//    Rev 1.12   Nov 09 1997 15:35:36   DTWK
// Add inclusion guards for faster compiles.
// Add guards so that class is flagged as exported only when compiling
// the output that actually exports the class.
//
//    Rev 1.11   Oct 08 1997 12:11:16   dkaw
// have getConfigurationValues call getDefaultValues,
// using "Software\DST\appname\Config\DataPath" key, "Path" value
//
//    Rev 1.10   Sep 26 1997 12:31:58   dkaw
// pass condition path to constructor for CMFrame
//
//    Rev 1.9   Sep 17 1997 11:48:26   dkaw
// rename getThreadCondition to getCondition
//
//    Rev 1.8   Sep 08 1997 15:58:06   dkaw
// add setApplicationName
//
//    Rev 1.7   Sep 04 1997 14:18:42   dkaw
// add use current flag to getMaxSeverity
//
//    Rev 1.6   Sep 04 1997 11:12:06   dkaw
// add autopromote, clearCondition()
//
//    Rev 1.5   Sep 03 1997 09:24:42   dkaw
// only delete current frame if it is level 0, and toplevel is not set
//
//    Rev 1.4   Sep 02 1997 15:51:08   dkaw
// call setTopLevel in CMFrame constructor
//
//    Rev 1.3   Aug 28 1997 14:01:50   dkaw
// rename NO_COND to NO_CONDITION
//
//    Rev 1.2   Aug 25 1997 16:01:38   dkaw
// add getFrameBelow, promoteAll for threads
//
//    Rev 1.1   Jul 22 1997 16:18:24   dkaw
// add trace filtering, use ditrace
//
//    Rev 1.0   Jun 13 1997 12:54:54   DTWK
//

