#include <srcprag.h>
#include "bfabstractcbo.hpp"
#include <bfdata\bffieldid.hpp>


//******************************************************************************
bool BFAbstractCBO::deleteObject( BFAbstractCBO::OBJECT_MAP_ITER &iter, const BFDataGroupId& idDataGroup, bool bRemoveFromMap, bool bForce )
{
   EXECHISTI( I_( "deleteObject( BFAbstractCBO:: OBJECT_MAP_ITER &, const BFDataGroupId &, bool, bool )" ) );
   bool success = false;

   const BFObjectKey& rObjKey = (*iter).first;

   if( true == bForce || 
       OBJ_ACTIVITY_DELETED == rObjKey.getActivity() || 
       canDeleteObject( rObjKey.getStringKey(), idDataGroup ) ) //don't call canDeleteObject for an already deleted obj.
   {
      BFAbstractCBO::OBJECT_INFO* pObjInfo = (*iter).second;

      bool bRemoveMapEntry = (( rObjKey.getActivity() == OBJ_ACTIVITY_ADDED) || bRemoveFromMap ) && ( rObjKey.getDataGroupId() == idDataGroup );
      bool bDestroyObject = bRemoveMapEntry && !flagsAreOn( pObjInfo->getStateFlags(), NO_BASE_DELETE );

      doDeleteObject( rObjKey.getStringKey(), idDataGroup, bDestroyObject );

      if( bRemoveMapEntry )
      {
         if( bDestroyObject )
            delete pObjInfo->getInstance();

         delete pObjInfo;
         iter = _objectMap.erase( iter );
      }
      else
      {
         BFAbstractCBO::OBJECT_INFO* pDupObjInfo = new BFAbstractCBO::OBJECT_INFO( *pObjInfo );
         BFObjectKey rDupObjKey( rObjKey.getStringKey(), idDataGroup, OBJ_ACTIVITY_DELETED, rObjKey.getType() );
         _objectMap.insert( BFAbstractCBO::OBJECT_MAP::value_type( rDupObjKey, pDupObjInfo ));
         // we should use in a BFObjIter the string map in order to keep the right ordering
         _hasNonBFHOSTsetObjects = true;
      }

      notifyObservers( ifds::NullFieldId, idDataGroup, NON_FIELD_NOTIFICATIONS, E_EVENT_CBO_OBJITER_UPDATE, I_( "" ));
      success = true;
   }
   return(success);
}


