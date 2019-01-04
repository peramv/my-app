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
// ^FILE   : ListDetails.cpp
// ^AUTHOR : Jerry Leenerts
// ^DATE   : 03/02/1999
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : ListDetails
//    
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "BPGlobal.h"
#include "ListDetails.hpp"
#include "AbstractProcess.hpp"
#include <bfcbo\BFObjIter.hpp>
#include <IDIString.hpp>
#include <assert.h>

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "ListDetails" );

   const I_CHAR * const ADDITEM = I_( "addItem" );
   const I_CHAR * const ASSURECONTAINERVALID = I_( "assureContainerValid" );
   const I_CHAR * const ASSUREITEMVALID = I_( "assureItemValid" );
   const I_CHAR * const ASSUREREPEATABLE = I_( "assureRepeatable" );
   const I_CHAR * const ASSUREUPDATABLE = I_( "assureUpdatable" );
   const I_CHAR * const COMMIT = I_( "commit" );
   const I_CHAR * const COPYCONSTRUCTOR = I_( "ListDetails &" );
   const I_CHAR * const DELETEITEM = I_( "deleteItem" );
   const I_CHAR * const GETCURRENTKEY = I_( "getCurrentKey" );
   const I_CHAR * const GETFIRSTKEY = I_( "getFirstKey" );
//   const I_CHAR * const GETFIELD = I_( "getField" );
   const I_CHAR * const GETITEM = I_( "getItem" );
   const I_CHAR * const GETITER = I_( "getIter" );
   const I_CHAR * const GETCONTAINER = I_( "getContainer" );
   const I_CHAR * const GETNEXTKEY = I_( "getNextKey" );
   const I_CHAR * const ITERCHANGED = I_( "iterChanged" );
//   const I_CHAR * const RESET = I_( "reset" );
   const I_CHAR * const SETCURRENTKEY = I_( "setCurrentKey" );
   const I_CHAR * const TRYSETCURRENTKEY = I_( "trySetCurrentKey" );
   const I_CHAR * const SETITEMPTR = I_( "setItemPtr" );
   const I_CHAR * const SETCONTAINER = I_( "setContainer" );
   const I_CHAR * const RESETCURRENTITEM = I_( "resetCurrentItem" );
//   const I_CHAR * const SETFIELD = I_( "setField" );

   // Literals
   const I_CHAR * const ID = I_( "ID" );
   const I_CHAR * const KEY = I_( "KEY" );
}

namespace CND
{  // Conditions used
   extern const long BP_ERR_FIELD_NOT_FOUND;
   extern const long BP_ERR_ITEM_NOT_VALID;
   extern const long BP_ERR_LIST_NOT_VALID;
   extern const long BP_ERR_UNKNOWN_EXCEPTION;
}

//******************************************************************************
//              Public Methods
//******************************************************************************

ListDetails::ListDetails( AbstractProcess *rpParent,
                          const BFContainerId& idList,
                          const BFContainerId& idParentList,
                          bool bRepeatable,
                          bool bUpdatable,
                          const DString &name ) 
: AbstractListDetails( idList, idParentList, bRepeatable, bUpdatable, name )
, _rpParent( rpParent )
, _keyFilter( NULL_STRING )
, _dataFilter( NULL_STRING )
{  // Make sure ID within range
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
}

//******************************************************************************

ListDetails::~ListDetails()
{
   TRACE_DESTRUCTOR( CLASSNAME );
/*
   BFBase *rpPtr = static_cast< BFBase * >( getContainerPtrRaw() );
   if ( rpPtr != NULL )
   {  // Remove observer
      rpPtr->deleteObserver( 0, BF::HOST, this,
         NON_FIELD_NOTIFICATIONS, E_EVENT_CBO_DESTROYED );
   }
*/
   deleteIters();
}

//******************************************************************************

const DString &ListDetails::addItem( const BFDataGroupId& idDataGroup )
{
   TRACE_METHOD( CLASSNAME, ADDITEM );
   DString strKey;

   assureUpdatable();
   assureContainerValid();
   assureRepeatable( idDataGroup );

   getIter( idDataGroup )->addNewObject( strKey );
   return(getCurrentKey( idDataGroup ));
}

//******************************************************************************

SEVERITY ListDetails::commit( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, COMMIT );

   if( isContainerValid() )
   {  // Container to commit
      if( isRepeatable() )
      {  // If iterators exist, remove them
         deleteIters();
      }

      if( isUpdatable() )
      {  // Commit CBO changes
         getContainer()->commitDataGroup( idDataGroup );
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY ListDetails::deleteItem( const BFDataGroupId& idDataGroup )
{
   TRACE_METHOD( CLASSNAME, DELETEITEM );
   const DString *pStr = NULL;

   assureUpdatable();
   assureContainerValid();
   assureItemValid( idDataGroup );

   return(getIter( idDataGroup )->deleteObject());
}

//******************************************************************************

//<>BFBase *ListDetails::getContainer()
BFAbstractCBO *ListDetails::getContainer()
{
   TRACE_METHOD( CLASSNAME, GETCONTAINER );

   BFAbstractCBO *rpContainer = static_cast< BFAbstractCBO *>( AbstractListDetails::getContainer() );
   if( rpContainer )
   {
      return(rpContainer);
   }

   // Not valid - no list
   assert( 0 );
   DString strIDI;
   addIDITagValue( strIDI, ID, getContainerID().getId() );
   THROWFROMFILEIDI2( CND::BPBASE_CONDITION, CLASSNAME, GETCONTAINER,
                      CND::BP_ERR_LIST_NOT_VALID, strIDI );
}

//******************************************************************************

const DString &ListDetails::getCurrentKey( const BFDataGroupId& idDataGroup )
{
   TRACE_METHOD( CLASSNAME, GETCURRENTKEY );

   assureContainerValid();
   assureRepeatable( idDataGroup );

   if( isItemValid( idDataGroup ) )
   {  // There is a key
      return(getIter( idDataGroup )->getStringKey());
   }
   return(_strEmpty);
}

//******************************************************************************

void ListDetails::getField( const BFFieldId &fieldID,
                            bool bFormatted,
                            DString &strValueOut,
                            const BFDataGroupId& idDataGroup )
{  // We fail because all CBO field access should be going through FieldDetails
   // All fields to be accessed must be defined in Field Details array.
   assert( 0 );   
   DString strIDI;
   addIDITagValue( strIDI, KEY, fieldID.getId() );
   THROWFROMFILEIDI2( CND::BPBASE_CONDITION, CLASSNAME, GETFIELD,
                      CND::BP_ERR_FIELD_NOT_FOUND, strIDI );
}

//******************************************************************************

bool ListDetails::getFirstKey( const DString **rpStr,
                               const BFDataGroupId& idDataGroup )
{
   TRACE_METHOD( CLASSNAME, GETFIRSTKEY );
   bool bRtn = false;
   *rpStr = &_strEmpty;       // Default to nothing

   try
   {
      assureContainerValid();
      assureRepeatable( idDataGroup );

      if( !isItemValid( idDataGroup ) || !getIter( idDataGroup )->isBegin() )
      {  // Item not valid or not already at beginning
         getIter( idDataGroup )->begin();
         bRtn = true;         // Our iterator has changed
      }
      if( isItemValid( idDataGroup ) )
      {  // Key to return
         *rpStr = &( getIter( idDataGroup )->getStringKey() );
      }
   }
   catch( ConditionException & )
   {

   }

   return(bRtn);
}

//******************************************************************************

void* ListDetails::getItem( const BFDataGroupId& idDataGroup, const DString* pKey )
{
   TRACE_METHOD( CLASSNAME, GETITEM );
   try
   {
      assureContainerValid();
      assureItemValid( idDataGroup );
   }
   catch( ConditionException & )
   {
   }
   if( NULL == pKey )
   {
      // We are being asked for the current item so use the wacky iterators
      return( getIter( idDataGroup )->getObject() );
   }
   else
   {
      // we are being asked for a specific item in the list
      BFAbstractCBO* pListCBO = dynamic_cast< BFAbstractCBO* >( getContainer() );
      if( NULL != pListCBO )
      {
         BFObjIter it( *pListCBO, idDataGroup );
         it.positionByKey( *pKey );
         return( it.getObject() );
      }
   }
   return( NULL );
}

//******************************************************************************

bool ListDetails::getNextKey( const DString **rpStr,
                              const BFDataGroupId& idDataGroup )
{
   TRACE_METHOD( CLASSNAME, GETNEXTKEY );
   bool bRtn = false;
   *rpStr = &_strEmpty;        // Default to nothing

   assureContainerValid();
   assureRepeatable( idDataGroup );

   BFObjIter *rpIter = getIter( idDataGroup );
   if( !rpIter->end() )
   {  // There is a change possible
      ++( *rpIter );
      bRtn = true;         // Out item has changed
      if( !rpIter->end() )
      {  // Still valid
         *rpStr = &( rpIter->getStringKey() );
      }
   }
   return(bRtn);
}

//******************************************************************************

int ListDetails::getNumberOfItemsInList( const BFDataGroupId& idDataGroup )
{
   TRACE_METHOD( CLASSNAME, GETNUMBEROFITEMSINLIST );

   assureContainerValid();
   assureRepeatable( idDataGroup );

   return(getIter( idDataGroup )->getNumberOfItemsInList());
}

//******************************************************************************

bool ListDetails::isNewItem( const BFDataGroupId& idDataGroup )
{  // Default processing is to fail
   assureContainerValid();
   //assureRepeatable( idDataGroup );
   if( isRepeatable() )
   {
      assureRepeatable( idDataGroup );
      return(getIter( idDataGroup )->getObject()->isNew());
   }
   else
      return(getContainer()->isNew());
}

//******************************************************************************
bool ListDetails::isDummyCurrentItem( const BFDataGroupId& idDataGroup )
{  // Default processing is to fail
   assureContainerValid();
   assureRepeatable( idDataGroup );

   return(getIter( idDataGroup )->isDummy());
}

//******************************************************************************

void ListDetails::onNotify( E_EVENT_GROUP eEventGroup,
                            E_EVENT eEventId,
                            const DString &hint )
{
   if( eEventGroup == NON_FIELD_NOTIFICATIONS && 
       eEventId == E_EVENT_CBO_DESTROYED )
   {  // Our CBO is self-destructing.
      if( getContainerPtrRaw() != NULL )
      {  // We have a change - clear our internal pointers
         deleteIters();
         AbstractListDetails::setContainer( NULL );
         //      setUpdateLevel();
         if( hasChildren() )
         {  // Need to let parent reset children
            _rpParent->resetChildContainers( getContainerID() );
         }
      }
   }
}

//******************************************************************************

SEVERITY ListDetails::reset( const BFDataGroupId& idDataGroup, 
                             bool bCurrentItem )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, RESET );

   if( !isContainerValid() )
   {  // No container to reset
      return(NO_CONDITION);
   }

   BFAbstractCBO *rpCBO = getContainer();

   if( isRepeatable() )
   {  // If iterator exists, remove it
      if( !bCurrentItem )
      {  // Resetting whole container
         deleteIters();
      }
      else
      {  // Resetting current item only
         ITERS::iterator iter = _iters.find( idDataGroup );

         if( iter != _iters.end() )
         {
            rpCBO = (*iter).second->getObject();
            delete ( *iter ).second;
            _iters.erase( iter );
         }
      }
   }
   else
   {  // bCurrentItem should be false if not repeatable
      assert( !bCurrentItem );
   }

   if( isUpdatable() )
   {  // reset CBO
      rpCBO->reset( idDataGroup );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY ListDetails::resetCurrentItem( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::BPBASE_CONDITION, CLASSNAME, RESETCURRENTITEM );

   if( !isContainerValid() )
   {  // No container to reset
      return(NO_CONDITION);
   }

   BFAbstractCBO *rpCBO = getContainer();

   if( isRepeatable() && isUpdatable() )
   {
      ITERS::iterator iter = _iters.find( idDataGroup );

      if( iter != _iters.end() )
      {
         rpCBO = (*iter).second->getObject();
         rpCBO->reset( idDataGroup );
         delete ( *iter ).second;
         _iters.erase( iter );
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

bool ListDetails::setCurrentKey( const DString &strKey,
                                 const BFDataGroupId& idDataGroup )
{
   TRACE_METHOD( CLASSNAME, SETCURRENTKEY );
   bool bRtn = false;

   assureContainerValid();
   assureRepeatable( idDataGroup );

   if( !isItemValid( idDataGroup ) ||
       getIter( idDataGroup )->getStringKey() != strKey )
   {  // Make sure something changed
      getIter( idDataGroup )->positionByKey( strKey );
      bRtn = true;            // Our item has changed
   }
   // Assert if could not set current key
//   assert( isItemValid( idDataGroup ) );

   // in api, user may set to a wrong item so we need to report it.
   // to do: we need a better condition when mdb is available!
   if( !isItemValid( idDataGroup ) )
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, SETCURRENTKEY,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );

   return(bRtn);
}

//******************************************************************************

bool ListDetails::trySetCurrentKey( const DString &strKey,
                                    const BFDataGroupId& idDataGroup )
{
   TRACE_METHOD( CLASSNAME, TRYSETCURRENTKEY );
   bool bRtn = false;

   assureContainerValid();
   assureRepeatable( idDataGroup );

   if( !isItemValid( idDataGroup ) ||
       getIter( idDataGroup )->getStringKey() != strKey )
   {  // Make sure something changed
      getIter( idDataGroup )->positionByKey( strKey );
      bRtn = true;            // Our item has changed
   }

   return(bRtn);
}

//******************************************************************************

bool ListDetails::setContainer( void *rpContainer )
{
   TRACE_METHOD( CLASSNAME, SETCONTAINER );
   bool bRtn = false;
   BFAbstractCBO *rpOld = static_cast< BFAbstractCBO * >( getContainerPtrRaw() );
   BFAbstractCBO *rpNew = static_cast< BFAbstractCBO * >( rpContainer );

   if( rpOld != rpNew )
   {  // We have a change
      if( rpOld != NULL )
      {  // Remove observer
         /*
         rpOld->deleteObserver( 0, BF::HOST, this,
            NON_FIELD_NOTIFICATIONS, E_EVENT_CBO_DESTROYED );
         */
         deRegisterObserver( );

      }
      deleteIters();
      if( rpNew != NULL )
      {  // Add observer
         rpNew->registerObserver( ifds::NullFieldId, BF::HOST, this,
                                  NON_FIELD_NOTIFICATIONS, E_EVENT_CBO_DESTROYED );
      }
      bRtn = AbstractListDetails::setContainer( rpContainer );
//      setUpdateLevel();
   }
   return(bRtn);
}

//******************************************************************************

SEVERITY ListDetails::setField( const BFFieldId &fieldID,
                                bool bFormatted,
                                const DString &strValue,
                                const BFDataGroupId& idDataGroup )
{  // We fail because all CBO field access should be going through FieldDetails.
   // All fields to be accessed must be defined in Field Details array.
   assert( 0 );   
   DString strIDI;
   addIDITagValue( strIDI, KEY, fieldID.getId() );
   THROWFROMFILEIDI2( CND::BPBASE_CONDITION, CLASSNAME, SETFIELD,
                      CND::BP_ERR_FIELD_NOT_FOUND, strIDI );

   return(SEVERE_ERROR);
}

//******************************************************************************

//CP20030219void ListDetails::setUpdateLevel( const BFDataGroupId& idDataGroup )
//CP20030219{
//CP20030219   assureContainerValid();
//CP20030219
//CP20030219   _lContainerUpdateLevel = getContainer()->getUpdateLevel( idDataGroup );
//CP20030219}
//CP20030219
//******************************************************************************
//              Protected Methods
//******************************************************************************

const BFObjIter &ListDetails::getItemIterator( const BFDataGroupId& idDataGroup )
{
   assureContainerValid();

   return(*getIter( idDataGroup ));
}


//******************************************************************************

bool ListDetails::setKeyFilter( const DString& filter )
{
   bool success = true;
   _keyFilter = NULL_STRING;

   //trying to set filter on all iterators of this container. If the setting 
   // doesn't succed on one of them we are clearing the filter
   ITERS::iterator iter;
   for( iter = _iters.begin(); success && iter != _iters.end(); ++iter )
      success = (*iter).second->setKeyFilter( filter );

   if( !success )
   {
      for( ITERS::iterator cIter = _iters.begin(); cIter != iter; ++cIter )
         (*cIter).second->clearKeyFilter();
   }
   else
      _keyFilter = filter;

   return(success);

}

//******************************************************************************

void ListDetails::getKeyFilter( DString& filter )
{
   filter = _keyFilter;
}

//******************************************************************************

void ListDetails::clearKeyFilter()
{
   ITERS::iterator iter;
   for( iter = _iters.begin(); iter != _iters.end(); ++iter )
      (*iter).second->clearKeyFilter();

   _keyFilter = NULL_STRING;
}

//******************************************************************************

bool ListDetails::setDataFilter( const DString& filter )
{
   bool success = true;
   _dataFilter = NULL_STRING;

   //trying to set filter on all iterators of this container. If the setting 
   // doesn't succed on one of them we are clearing the filter
   ITERS::iterator iter;
   for( iter = _iters.begin(); success && iter != _iters.end(); ++iter )
      success = (*iter).second->setDataFilter( filter );

   if( !success )
   {
      for( ITERS::iterator cIter = _iters.begin(); cIter != iter; ++cIter )
         (*cIter).second->clearDataFilter();
   }
   else
      _dataFilter = filter;

   return(success);

}

//******************************************************************************

void ListDetails::getDataFilter( DString& filter )
{
   filter = _dataFilter;
}

//******************************************************************************

void ListDetails::clearDataFilter()
{
   ITERS::iterator iter;
   for( iter = _iters.begin(); iter != _iters.end(); ++iter )
      (*iter).second->clearDataFilter();

   _dataFilter = NULL_STRING;
}

//******************************************************************************
//              Private Methods
//******************************************************************************

void ListDetails::assureContainerValid()
{
   if( !isContainerValid() )
   {  // Not valid - no container set
//      assert( 0 );
      DString strIDI;
      addIDITagValue( strIDI, ID, getContainerID().getId() );
      THROWFROMFILEIDI2( CND::BPBASE_CONDITION, CLASSNAME, ASSURECONTAINERVALID,
                         CND::BP_ERR_LIST_NOT_VALID, strIDI );
   }
}

//******************************************************************************

void ListDetails::assureItemValid( const BFDataGroupId& idDataGroup )
{
   // Must be a repeatable container (list CBO) to have items
   assureRepeatable( idDataGroup );    
   if( !isItemValid( idDataGroup ) )
   {  // Iterator couldn't be found or created
//      assert( 0 );
      DString strIDI;
      addIDITagValue( strIDI, ID, getContainerID().getId() );
      THROWFROMFILEIDI2( CND::BPBASE_CONDITION, CLASSNAME, ASSUREITEMVALID,
                         CND::BP_ERR_ITEM_NOT_VALID, strIDI );
   }
}

//******************************************************************************

void ListDetails::assureRepeatable( const BFDataGroupId& idDataGroup )
{
   if( !isRepeatable() )
   {
// TODO Change to different condition here
//      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, ASSUREREPEATABLE,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }

   // Create iterator if not exist
   if( !getIterRaw( idDataGroup ) )
   {  // No iterator exists for this group, create one
      BFObjIter *pIter = new BFObjIter( *( static_cast< BFAbstractCBO *>
                                           ( getContainer() ) ), idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
      if( _keyFilter != NULL_STRING )
         pIter->setKeyFilter( _keyFilter );
      if( _dataFilter != NULL_STRING )
         pIter->setDataFilter( _dataFilter );
      if( !_iters.insert( ITERS::value_type( idDataGroup, pIter ) ).second )
      {
// TODO - add condition
         assert( 0 );
      }
      if( idDataGroup != BF::HOST )
      {  // If not host group we are adding, start our key based off parent
         // iterator
         const BFDataGroupId& idParentDataGroup = getContainer()->getParentDataGroup( idDataGroup );
         BFObjIter *rpParent = getIterRaw( idParentDataGroup );
         if( !rpParent && idParentDataGroup != BF::HOST )
         {
// TODO - Do we need to run up parent chain?  For now try one parent & host
            rpParent = getIterRaw( BF::HOST );
         }
         if( rpParent )
         {  // Get last iterator's position and use for new iterator
            if( !rpParent->end() )
            {
               DString parentKey = rpParent->getStringKey();
               if( parentKey != NULL_STRING )
               {  // position if we have one
                  if( !(pIter->positionByKey( parentKey )) )
                     pIter->positionByKey( NULL_STRING );
               }
            }
         }
         else
         {  // Shouldn't be any reason not to have parent iterator ??
//CP20021205   ... unless we are a dummy item (i.e. a new CBO) and we haven't iterated through the list yet!
//CP20021205      CP 05 Dec 2002
//CP20021205            assert( 0 );
         }
      }
   }
}

//******************************************************************************

void ListDetails::assureUpdatable()
{
   if( !isUpdatable() )
   {
// TODO Change to different condition here
      assert( 0 );
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, ASSUREUPDATABLE,
                      CND::BP_ERR_UNKNOWN_EXCEPTION );
   }
}

//******************************************************************************

void ListDetails::deleteIters()
{
   ITERS::iterator iter = _iters.begin();
   while( iter != _iters.end() )
   {
      delete ( *iter ).second;
      iter++;
   }
   _iters.clear();
}

//******************************************************************************

BFObjIter* ListDetails::getIter( const BFDataGroupId& idDataGroup ) const
{
   // Assumes container is already validated
   LIST_CONST_ITER iter = _iters.find( idDataGroup );

   if( iter != _iters.end() )
   {
      BFObjIter* pIter = (*iter).second;
      return(pIter);
   }
   else
   {  // Couldn't find match for ID
// TODO - get condition for ITEM_NOT_VALID
      THROWFROMFILE2( CND::BPBASE_CONDITION, CLASSNAME, GETITER,
                      CND::BP_ERR_LIST_NOT_VALID );
   }
}

//******************************************************************************

BFObjIter *ListDetails::getIterRaw( const BFDataGroupId& idDataGroup ) const
{
   // Assumes container is already validated
   LIST_CONST_ITER iter = _iters.find( idDataGroup );

   if( iter != _iters.end() )
   {
      return( *iter ).second;
   }

   // Couldn't find match for ID
   return(NULL);
}

//******************************************************************************

bool ListDetails::isItemValid( const BFDataGroupId& idDataGroup )
{
   // Only valid for list CBO's
   if( isRepeatable() )
   {  // We can have items
      BFObjIter* pIter = getIter( idDataGroup );
      bool bRtn = !pIter->end();
      return( bRtn );
      //return !getIter( idDataGroup )->end();
   }
   return(false);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF Core/bfproc/ListDetails.cpp-arc  $
//
//   Rev 1.22   Oct 22 2004 08:58:24   PURDYECH
//PET910 - .NET Conversion Fixes
//
//   Rev 1.21   May 24 2003 14:56:02   PURDYECH
//Add facility to get item by key without altering "current" item
 * 
 *    Rev 1.20   Feb 26 2003 09:43:38   PURDYECH
 * Remove updateLevel 
 * 
 *    Rev 1.19   Jan 06 2003 16:44:04   PURDYECH
 * BFDataGroupId and BFContainerId changeover
 * 
 *    Rev 1.18   Oct 09 2002 17:40:58   PURDYECH
 * New PVCS Database
 * 
 *    Rev 1.17   Sep 03 2002 11:07:14   PURDYECH
 * Further BFFieldId fixes
 * 
 *    Rev 1.16   Aug 29 2002 14:05:24   SMITHDAV
 * Condition split.
 * 
 *    Rev 1.15   Aug 29 2002 12:51:12   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.14   05 Jun 2002 13:55:14   SMITHDAV
 * Fix grid refresh bug. Added trySetCurrentKey functions.
 * 
 *    Rev 1.13   22 May 2002 17:57:04   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.12   25 Feb 2002 20:08:26   PURDYECH
 * Phase 1 of the BFData Rollout
 * 
 *    Rev 1.11   08 Jan 2002 13:51:56   KOVACSRO
 * Reset method calling BFBase::reset, rather than BFBase::rollbackDataGroup().
 * 
 *    Rev 1.10   18 Aug 2001 11:42:38   HSUCHIN
 * added try catch to getFirstKey and getItem and removed asserts from assurecontainervalid assureitemvalid and assurerepeatable.
 * 
 *    Rev 1.9   26 Jul 2001 13:43:46   YINGZ
 * fix reset, cancel problems
 * 
 *    Rev 1.8   04 Jul 2001 16:43:36   YINGZ
 * user reset for reset function
 * 
 *    Rev 1.7   29 Mar 2001 13:19:52   KOVACSRO
 * isNew() works now  for non repeatable containers, too.
 * 
 *    Rev 1.6   Feb 06 2001 14:00:56   YINGZ
 * change setCurrentKey to throw when item is invalid
 * 
 *    Rev 1.5   Dec 13 2000 13:18:18   KOVACSRO
 * Added a method to check if current item is dummy.
 * 
 *    Rev 1.4   Nov 08 2000 19:54:14   DT24433
 * added list name support
 * 
 *    Rev 1.3   Aug 02 2000 15:31:34   BUZILA
 * "locale" changes
 * 
 *    Rev 1.2   Jun 02 2000 14:02:58   BUZILA
 * fix misspositioning for a container that has the first item visible for datagroup 0 but not present in the current one.
 * 
 *    Rev 1.1   Mar 23 2000 16:23:46   BUZILA
 * CBO filtering implemented
 * 
 *    Rev 1.0   Feb 15 2000 10:57:36   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.23   Jan 27 2000 15:29:24   DT24433
 * removed duplicate literal
 * 
 *    Rev 1.22   Jan 19 2000 10:11:58   BUZILA
 * refresh stuf
 * 
 *    Rev 1.21   Jan 17 2000 14:26:26   DT24433
 * added code to deleteObserver if necessary during destructor
 * 
 *    Rev 1.20   Jan 12 2000 18:57:04   DT24433
 * added observer for CBO destruction
 * 
 *    Rev 1.19   Dec 16 1999 18:13:48   VASILEAD
 * Fixed reset on current item
 * 
 *    Rev 1.18   Dec 09 1999 11:18:12   DT24433
 * started work on saving/checking updatelevel
 * 
 *    Rev 1.17   Dec 08 1999 16:18:52   DT24433
 * added isNewItem
 * 
 *    Rev 1.16   Nov 22 1999 18:03:02   DT24433
 * performance improvements
 * 
 *    Rev 1.15   Nov 22 1999 12:06:48   DT24433
 * don't try to commit/reset containers that aren't set
 * 
 *    Rev 1.14   Nov 17 1999 12:50:34   DT24433
 * add assureRepeatable to addItem
 * 
 *    Rev 1.13   Nov 16 1999 13:32:48   DT24433
 * fixed position of update iterator on creation
 * 
 *    Rev 1.12   Nov 15 1999 13:20:30   DT24433
 * fixed addItem problem
 * 
 *    Rev 1.11   Nov 09 1999 15:47:16   BUZILA
 * added matchSubstrings in call of BFObjIter::BFObjIter
 * 
 *    Rev 1.10   Oct 28 1999 16:47:06   DT24433
 * added commit method
 * 
 *    Rev 1.9   Oct 28 1999 12:47:38   DT24433
 * add/delete/reset & group processing
 * 
 *    Rev 1.8   Sep 28 1999 15:55:42   DT24433
 * removed getField support - all handled via FieldDetails now
 * 
 *    Rev 1.7   Sep 20 1999 10:19:48   BUZILA
 * changet get field to return void
 * 
 *    Rev 1.6   Sep 14 1999 11:44:48   BUZILA
 * BFBase changes
 * 
 *    Rev 1.5   Aug 06 1999 10:18:02   DT24433
 * support change item detection
 * 
 *    Rev 1.4   Aug 05 1999 15:17:16   DT24433
 * altered functionality
 * 
 *    Rev 1.3   Aug 03 1999 14:45:46   DT24433
 * container changes
 * 
 *    Rev 1.2   Jul 20 1999 11:14:08   VASILEAD
 * New conditions update
 * 
 *    Rev 1.1   Jul 08 1999 10:02:08   SMITHDAV
 * Modify revision history commaent format to old
 * style comment -- I can't seem to get new style comments to work.
 *
 */
