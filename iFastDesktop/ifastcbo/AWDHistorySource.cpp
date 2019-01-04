#include "stdafx.h"
#include ".\awdhistorysource.hpp"

#include <ifastdataimpl\dse_awdhistsrc_vw.hpp>
#include <json\json.h>

namespace
{
   //Trace literals
   const I_CHAR *  CLASSNAME = I_( "AWDHistorySource" );
}

//******************************************************************************************
AWDHistorySource::AWDHistorySource( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
}

//******************************************************************************************
AWDHistorySource::~AWDHistorySource(void)
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************************
SEVERITY AWDHistorySource::init(const Json::Value& jsonData)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   BFData* data = new BFData(ifds::AWDHISTSRC_VW);

   DString id = DString(jsonData["Id"].asString());
   DString type = DString(jsonData["Type"].asString());
   DString imageUrl = DString(jsonData["ImageUrl"].asString());
   DString contentId = DString(jsonData["ContentId"].asString());

   data->setElementValue( ifds::AWDObjectId,  id) ;
   data->setElementValue( ifds::AWDType, type ) ;
   data->setElementValue( ifds::AWDImageURL, imageUrl ) ;
   data->setElementValue( ifds::AWDContentId, contentId ) ;

   attachDataObject( *data , true, true );
   clearUpdatedFlags (BF::HOST);

   return GETCURRENTHIGHESTSEVERITY();
}
