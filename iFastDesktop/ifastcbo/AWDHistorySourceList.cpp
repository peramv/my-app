#include "stdafx.h"
#include ".\awdhistorysourcelist.hpp"
#include ".\awdhistorysource.hpp"

#include <json\json.h>

namespace
{
   //Trace literals
   const I_CHAR *  CLASSNAME = I_( "AWDHistorySourceList" );
}

//******************************************************************************************
AWDHistorySourceList::AWDHistorySourceList( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
}

//******************************************************************************************
AWDHistorySourceList::~AWDHistorySourceList(void)
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************************
SEVERITY AWDHistorySourceList::init( const Json::Value& jsonData )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   if (jsonData.isArray()) {
      for( Json::ValueIterator itr = jsonData.begin() ; itr != jsonData.end() ; itr++ ) {

         AWDHistorySource* pObj = new AWDHistorySource(*this);
         pObj->init(*itr);

         BFObjectKey objKey;
         getKey( objKey, NULL );
         setObject( objKey, pObj );

      }
   }


   return GETCURRENTHIGHESTSEVERITY();
}
