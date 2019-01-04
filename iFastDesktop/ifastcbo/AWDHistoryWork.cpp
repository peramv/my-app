#include "stdafx.h"
#include ".\awdhistorywork.hpp"
#include ".\awdhistorysourcelist.hpp"

#include <ifastdataimpl\dse_awdhistwrk_vw.hpp>
#include <json\json.h>


namespace
{
   //Trace literals
   const I_CHAR *  CLASSNAME = I_( "AWDHistoryWork" );
}

//******************************************************************************************
AWDHistoryWork::AWDHistoryWork( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
, m_sourceList(NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
}

//******************************************************************************************
AWDHistoryWork::~AWDHistoryWork(void)
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************************
SEVERITY AWDHistoryWork::init( const Json::Value& jsonData )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   BFData* data = new BFData(ifds::AWDHISTWRK_VW);

   DString id = DString(jsonData["Id"].asString());
   DString type = DString(jsonData["Type"].asString());
   DString status = DString(jsonData["Status"].asString());

   data->setElementValue( ifds::AWDObjectId,  id) ;
   data->setElementValue( ifds::AWDType, type ) ;
   data->setElementValue( ifds::AWDStatus, status ) ;

   attachDataObject( *data , true, true );
   clearUpdatedFlags (BF::HOST);


   // create the source list

   m_sourceList = new AWDHistorySourceList(*this);
   m_sourceList->init(jsonData["Source"]);

   return GETCURRENTHIGHESTSEVERITY();
}

