//******************************************************************************
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
//******************************************************************************
//
// ^FILE   : GenericInterfaceContainer.cpp
// ^AUTHOR : Jerry Leenerts
// ^DATE   : 12/07/1998
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : GenericInterfaceContainer
//    This class sets the generic interface used by other classes.
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "bpglobal.h"
#include "genericinterfacecontainer.hpp"
#include "genericinterface.hpp"
#include "abstractprocess.hpp"
#include <assert.h>

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "GenericInterfaceContainer" );

   const I_CHAR * const ADD = I_( "add" );
   const I_CHAR * const ADDINSTANCE = I_( "addInstance" );
   const I_CHAR * const DESTROY = I_( "destroy" );
   const I_CHAR * const DESTROYALL = I_( "destroyAll" );
   const I_CHAR * const DESTROYCHILDRENRECURSIVE = I_( "destroyChildrenRecursive" );
   const I_CHAR * const DESTROYCHILDREN = I_( "destroyChildren" );
   const I_CHAR * const DESTROYSELF = I_( "destroySelf" );
   const I_CHAR * const ERASEDESTROYEDENTRIES = I_( "eraseDestroyedEntries" );
   const I_CHAR * const GETINSTANCE = I_( "getInstance" );
   const I_CHAR * const ISVALID = I_( "isValid" );
   const I_CHAR * const KILLALLINSTANCES = I_( "killAllInstances" );
   const I_CHAR * const KILLINSTANCE = I_( "killInstance" );
   const I_CHAR * const MODELESSDESTROYSELF = I_( "modelessDestroySelf" );
   const I_CHAR * const REFRESH = I_( "refresh" );

}

//******************************************************************************
//              Public Methods
//******************************************************************************

GenericInterfaceContainer::GenericInterfaceContainer() :
_bAlreadyDestroyingChildren( false ),
_interProcessData()
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
}

//******************************************************************************

GenericInterfaceContainer::~GenericInterfaceContainer()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   destroyAll();
}

//******************************************************************************
bool GenericInterfaceContainer::add(
                                   GenericInterface *pGI
                                   )
{
   TRACE_METHOD( CLASSNAME, ADD );

   if( !pGI )
   {  // Bad
      assert( 0 );
      return(false);
   }
   GIKey key( pGI );
   PROCESS_ITER processIter = _processes.find( key );

   if( processIter != _processes.end() )
   {  // This process already added
      assert( 0 );
      return(false);
   }
   GICData *pData = new GICData( pGI );
   _processes.insert( std::make_pair( key, pData ) );

   return(true);
}

//******************************************************************************

bool GenericInterfaceContainer::destroy(
                                       GenericInterface *pGI
                                       )
{  // This method should only be called to directly destroy an interface and its
   //  children.  Not for self-destruction.
   TRACE_METHOD( CLASSNAME, DESTROY );

   if( pGI == NULL )
   {  // Invalid pointer
      assert( 0 );
      return(false);
   }

   GIKey key( pGI );
   PROCESS_ITER processIter = _processes.find( key );

   if( processIter == _processes.end() )
   {  // No match found
      return(false);
   }

   destroyChildren( pGI );
   deleteGenericInterface( processIter );
   return(true);
}

//******************************************************************************

bool GenericInterfaceContainer::destroyAll(
                                          BFSession *bfSession
                                          )
{
   TRACE_METHOD( CLASSNAME, DESTROYALL );
   PROCESS_ITER processIter = _processes.begin();

   if( bfSession == NULL )
   {  // We are cleaning up everything
      while( processIter != _processes.end() )
      {  // Find processes with no parents
         if( ( *processIter ).second->_pGI->getParent() == NULL )
         {  // Clean up children first - to prevent any problems with child
            // depenencies on parents (like UserSession/WorkSession
            destroyChildren( ( *processIter ).second->_pGI );
            // Is this really safe after destroy children - or should we find it again?
            deleteGenericInterface( processIter );
            processIter = _processes.begin();
         }
         else
         {
            processIter++;
         }
      }
      // Get ready for final cleanup
      if( _processes.begin() != _processes.end() )
      {  // Why didn't everything get cleaned up??
         assert( 0 );
         processIter = _processes.begin();
         // Let fall through into next code for forced cleanup
      }
      else
      {
         return(true);
      }
   }

   while( processIter != _processes.end() )
   {
      // Check for matching work session id (workSessionID = 0 = all work
      //  sessions)
      if( bfSession == NULL ||
          ( *processIter ).first._bfSession == bfSession )
      {  // Note we still are not guaranteeing delete of children prior to
         // parents if workSessionID != 0
         deleteGenericInterface( processIter );
      }
      else
      {
         processIter++;
      }
   }
   return(true);
}

//******************************************************************************

bool GenericInterfaceContainer::destroyChildren(
                                               GenericInterface *rpGI
                                               )
{  // Call to only destroy your children
   TRACE_METHOD( CLASSNAME, DESTROYCHILDREN );

   if( !isValid( rpGI ) || _bAlreadyDestroyingChildren )
   {  // Invalid pointer or bAlreadyDestroyingChildren = true are invalid
//      assert( 0 );
      return(false);
   }

   _bAlreadyDestroyingChildren = true;
   destroyChildrenRecursive( rpGI );
   _bAlreadyDestroyingChildren = false;
   return(true);
}

//******************************************************************************
// NOTE, if necessary, this should be done recursively. for now, there is now sign of 
// secondary modeless screen
void GenericInterfaceContainer::destroyGUIChildren(
                                                  GenericInterface *rpGI
                                                  )
{  
   GenericInterface *rp;
   PROCESS_ITER processIter = _processes.begin();

   while( processIter != _processes.end() )
   {
      rp = ( *processIter ).second->_pGI;

      // pick up GI that is not the caller and its correspondent process is the
      // child of rpGI's correspondent process
      if( !dynamic_cast<const AbstractProcess *> (rp) && 
          rp != rpGI && rp->getParent()->getParent() == rpGI->getParent() )
      {
         // rollback the data
         rp->getParent()->cancel( rp );

         // close the screen
         modelessDestroySelf( rp );
         processIter = _processes.begin();
      }
      else
         ++processIter;
   }
}

//******************************************************************************

bool GenericInterfaceContainer::destroySelf(
                                           GenericInterface *pGI
                                           )
{  // This method should only be called for object destruction by the object
   //  managers.
   TRACE_METHOD( CLASSNAME, DESTROYSELF );

   if( !pGI )
   {  // NULL pointer or modal is invalid
      assert( 0 );
      return(false);
   }

   GIKey key( pGI );

   PROCESS_ITER processIter = _processes.find( key );
   if( processIter == _processes.end() )
   {  // No match found
      assert( 0 );        // Why not??
      return(false);
   }

   destroyChildren( pGI );  // Not sure if we should need this...
   deleteGenericInterface( processIter );
   return(true);
}

//******************************************************************************

bool GenericInterfaceContainer::modelessDestroySelf(
                                                   GenericInterface *pGI
                                                   )
{  // This method should only be called for object destruction by the object
   //  managers.
   TRACE_METHOD( CLASSNAME, MODELESSDESTROYSELF );

   if( !pGI || pGI->isModal() )
   {  // NULL pointer or modal is invalid
      assert( 0 );
      return(false);
   }

   GIKey key( pGI );
   PROCESS_ITER processIter = _processes.find( key );
   if( processIter == _processes.end() )
   {  // No match found
      assert( 0 );        // Why not??
      return(false);
   }

   destroyChildren( pGI );
   GenericInterface *pParentGI = ( *processIter ).second->_pGI->getParent();
   Command tmpCmd = ( *processIter ).second->_pGI->getCommand();
   deleteGenericInterface( processIter );

   if( isValid( pParentGI ) )
   {  // if parent process exists, send message that we have ended.
      pParentGI->modelessChildComplete( tmpCmd );
   }
   else
   {
      assert( 0 );    // Shouldn't happen this way
      return(false);
   }

   return(true);
}

//******************************************************************************

GenericInterface *GenericInterfaceContainer::findGI(
                                                   BFSession *bfSession,
                                                   const DString &strKey
                                                   ) const
{  // This will only find modeless GI
   GenericInterface *rpGI = NULL;

   GIKey key( bfSession, strKey, false );

   PROCESS_CONST_ITER processIter = _processes.find( key );
   if( processIter != _processes.end() )
   {  // match found
      rpGI = ( *processIter ).second->_pGI;
   }
   return(rpGI);
}

//******************************************************************************

int GenericInterfaceContainer::getChildCount(
                                            GenericInterface *rpGIParent
                                            )
{
   int count = 0;
   PROCESS_ITER processIter = _processes.begin();

   for( ; processIter != _processes.end(); processIter++ )
   {
      if( ( *processIter ).second->_pGI->getParent() == rpGIParent )
      {  // Found a child
         count++;
      }
   }
   return(count);
}

//******************************************************************************

bool GenericInterfaceContainer::isValid(
                                       GenericInterface *rpGI
                                       ) const
{  // See if pointer is still in container
   TRACE_METHOD( CLASSNAME, ISVALID );

   if( !rpGI )
   {  // No NULL pointer allowed
      return(false);
   }

   // Make sure it exists
   GIKey key( rpGI );

   PROCESS_CONST_ITER processIter = _processes.find( key );
   bool bRtn = !( processIter == _processes.end() );

   return(bRtn);
}

//******************************************************************************

bool GenericInterfaceContainer::refresh(
                                       GenericInterface *rpGICaller
                                       )
{  // Note that we are not stopping for any refresh failure currently
   TRACE_METHOD( CLASSNAME, REFRESH );

   if( !isValid( rpGICaller ) )
   {  // invalid pointer
      assert( 0 );         // Not sure if any case is valid here
      return(false);
   }
   // Send refresh to modeless business processes
   PROCESS_ITER processIter;

   for( processIter = _processes.begin(); processIter != _processes.end();
      processIter++ )
   {
      GenericInterface *rp = ( *processIter ).second->_pGI;
      if( rpGICaller != rp && !rp->isModal() )
      {  // Refresh if not caller & not modal (modal objects control own
         //  refresh).
         // WorkSession must be the same as well
         if( rpGICaller->getBFSession() == rp->getBFSession() )
         {
            if( rp->getCommand().isCommandTypeOf(
                                                BUSINESS_PROCESS_TYPE ) )
            {  // We have a business process
               rp->refresh( rpGICaller, NULL_STRING );
            }
         }
      }
   }
   return(true);
}

//******************************************************************************

void GenericInterfaceContainer::refreshGUIChildren(
                                                  GenericInterface *rpGICaller
                                                  )
{  // Send refresh to modeless business processes
   PROCESS_ITER processIter;

   for( processIter = _processes.begin(); processIter != _processes.end();
      processIter++ )
   {
      GenericInterface *rp = ( *processIter ).second->_pGI;
      if( rp->getParent() == rpGICaller )
      {  // Refresh child GUI_TYPEs
         if( rp->getCommand().isCommandTypeOf( GUI_TYPE ) )
         {  // We have a front end GI
            rp->refresh( rpGICaller, NULL_STRING );
         }
      }
   }
}

//******************************************************************************
//              Protected Methods
//******************************************************************************

//******************************************************************************
//              Private Methods
//******************************************************************************

void GenericInterfaceContainer::deleteGenericInterface(
                                                      PROCESS_ITER &iter
                                                      )
{
   if( !( *iter ).second->_bDestroyed )
   {  // Not already being destroyed
      GenericInterface *pGI = ( *iter ).second->_pGI;
      ( *iter ).second->_bDestroyed = true;
      pGI->predelete();             // For 2 step deletion process
      delete pGI;
      delete ( *iter ).second;      // Cleanup GICData struct
      iter = _processes.erase( iter );
   }
   else
   {
      assert( 0 );   // Trying to delete twice ??
   }
}

//******************************************************************************
/**
  * Destroy all interfaces with specified parent and any interaces that are
  * their descendents.
  * @param rpParent - a reference pointer to a parent GenericInterface whose
  * kids should be destroyed.
  */
void GenericInterfaceContainer::destroyChildrenRecursive(
                                                        GenericInterface *rpParentGI
                                                        )
{
   TRACE_METHOD( CLASSNAME, DESTROYCHILDRENRECURSIVE );
   PROCESS_ITER processIter = _processes.begin();

   while( processIter != _processes.end() )
   {
      if( ( *processIter ).second->_pGI->getParent() == rpParentGI )
      {  // Destroy my children
         destroyChildrenRecursive( ( *processIter ).second->_pGI );
         deleteGenericInterface( processIter );
      }
      else
      {
         processIter++;
      }
   }
}

//******************************************************************************

GenericInterfaceContainer::GIKey::GIKey(
                                       GenericInterface *rpGI
                                       ) :
_bfSession( rpGI->getBFSession() ),
_strCommand( rpGI->getCommand().getKey() ),
_bModal( rpGI->isModal() )
{
}

//******************************************************************************

GenericInterface * GenericInterfaceContainer::getChild(GenericInterface *rpGIParent,
										int index )
{
   int count = 0;
   PROCESS_ITER processIter = _processes.begin();

   for( ; processIter != _processes.end(); processIter++ )
   {
      if( ( *processIter ).second->_pGI->getParent() == rpGIParent )
      {  // Found a child
		  if(count == index)
		  {
			  return ( (*processIter).second->_pGI );
		  }
         count++;
      }
   }
   return(NULL);
}

//******************************************************************************
bool GenericInterfaceContainer::hasModalGI()
{
	for(auto pair :_processes) {
		if(pair.first._bModal) return true;
	}
	return false;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/bfproc/GenericInterfaceContainer.cpp-arc  $
//
//   Rev 1.17   Oct 22 2004 08:58:12   PURDYECH
//PET910 - .NET Conversion Fixes
//
//   Rev 1.16   May 14 2004 16:13:18   SMITHDAV
//Removed "global data areas" from InterProcessData" and cleaned up the related interfaces. They are now in the BFSession objects.
//
//   Rev 1.15   May 10 2004 15:04:40   SMITHDAV
//Add "getChild" member function to get the a child GI.
 * 
 *    Rev 1.14   Jan 06 2003 16:43:56   PURDYECH
 * BFDataGroupId and BFContainerId changeover
 * 
 *    Rev 1.13   Oct 09 2002 17:40:56   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.12   22 May 2002 17:57:04   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.11   23 May 2001 14:36:32   SMITHDAV
 * Fixed bug in refresh().
 * 
 *    Rev 1.10   03 May 2001 14:03:14   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.9   Mar 27 2001 13:58:28   YINGZ
 * add destroyGUIChildren
 * 
 *    Rev 1.8   Oct 26 2000 10:35:38   DT24433
 * Change to hold InterProcessData and userSessionId
 * 
 *    Rev 1.7   Aug 14 2000 20:19:44   IVESPAUL
 * Removed assert.
 *
 *    Rev 1.6   May 11 2000 12:30:34   DT24433
 * force delete of children prior to parents when destroying all GIs in GIC
 *
 *    Rev 1.5   May 09 2000 15:35:04   DT24433
 * changed static variable to class member for thread changes
 *
 *    Rev 1.4   Apr 28 2000 08:18:06   DT24433
 * changed to use critical sections
 *
 *    Rev 1.3   Apr 07 2000 09:45:08   DT24433
 * removed old versions of getInstance, killInstance, and findGI
 *
 *    Rev 1.2   Apr 04 2000 14:31:12   DT24433
 * changed to create GIC by userID and added a semaphore
 *
 *    Rev 1.1   Mar 21 2000 10:42:42   DT24433
 * changes to handle modal GI's as well as modeless, plus general cleanup
 *
 *    Rev 1.0   Feb 15 2000 10:57:36   SMITHDAV
 * Initial revision.
 *
 *    Rev 1.6   Dec 09 1999 19:26:00   DT24433
 * add !isModal check prior to assert in refresh
 *
 *    Rev 1.5   Dec 09 1999 11:46:18   DT24433
 * removed modal refresh
 *
 *    Rev 1.4   Dec 09 1999 11:20:22   DT24433
 * refresh support
 *
 *    Rev 1.3   Aug 31 1999 16:26:42   DT24433
 * isValid checks for NULL now
 *
 *    Rev 1.2   Jul 16 1999 12:27:48   POPESCUS
 * Added a method to count the children of a process
 *
 *    Rev 1.1   Jul 08 1999 10:02:04   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
