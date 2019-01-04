#include "stdafx.h"
#include ".\awdhistoryworklist.hpp"
#include ".\awdhistorywork.hpp"

#include <json\json.h>

namespace
{
   //Trace literals
   const I_CHAR *  CLASSNAME = I_( "AWDHistoryWorkList" );
}

//******************************************************************************************
AWDHistoryWorkList::AWDHistoryWorkList( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
}

//******************************************************************************************
AWDHistoryWorkList::~AWDHistoryWorkList(void)
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************************
SEVERITY AWDHistoryWorkList::init( const Json::Value& jsonData )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   _imageAuth = DString(jsonData["ImageAuth"].asString());
   
   Json::Value workObjs = jsonData["WorkObjects"];

   if (workObjs.isArray()) {
      for( Json::ValueIterator itr = workObjs.begin() ; itr != workObjs.end() ; itr++ ) {

         AWDHistoryWork* pObj = new AWDHistoryWork(*this);
         pObj->init(*itr);

         BFObjectKey objKey;
         getKey( objKey, NULL );
         setObject( objKey, pObj );

      }
   }
   
   return GETCURRENTHIGHESTSEVERITY();
}

