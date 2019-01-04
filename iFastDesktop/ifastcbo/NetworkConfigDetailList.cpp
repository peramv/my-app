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
//    Copyright 1999 by DST Canada, Inc.
//
//
//******************************************************************************
//
// ^FILE   : NetworkConfigDetailList.cpp
// ^AUTHOR : Robbins Kuriakose
// ^DATE   : 04 April 2014
//
// ^CLASS    : NetworkConfigDetailList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :	Used to get the Network Config Details 
//
//******************************************************************************
#include "stdafx.h"
#include "NetworkConfigDetailList.hpp"
#include "NetworkConfigDetail.hpp"
#include <ifastdataimpl\dse_dstc0461_req.hpp>
#include <ifastdataimpl\dse_dstc0461_vw.hpp>
namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest NETWORK_CONFIG_DETAIL; 
}
namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME  = I_("NetworkConfigDetailList");
}
namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId  NetworkID;
   extern CLASS_IMPORT const BFTextFieldId  NetworkConfigType;
}

//Define the Network Config value in here and use the import..
namespace NETWORK_CONFIG_TYPE
{
    extern CLASS_EXPORT I_CHAR * const AggrOrdXMLMsg              =     I_("AggrOrdXMLMsg");
    extern CLASS_EXPORT I_CHAR * const IncCancelTradeInConf       =     I_("IncCancelTradeInConf");
    extern CLASS_EXPORT I_CHAR * const NetworkTypeMessageType     =     I_("NetworkTypeMessageType");
    extern CLASS_EXPORT I_CHAR * const Confirmation               =     I_("Confirmation");
    extern CLASS_EXPORT I_CHAR * const DealDateTimeBySender       =     I_("DealDateTimeBySender");
    extern CLASS_EXPORT I_CHAR * const DefOrderType_EX            =     I_("DefOrderType-EX");
    extern CLASS_EXPORT I_CHAR * const FXRedemptionPUD            =     I_("FXRedemptionPUD");
    extern CLASS_EXPORT I_CHAR * const IntXMLActive               =     I_("IntXMLActive");
    extern CLASS_EXPORT I_CHAR * const RespAggrCutOffTime         =     I_("RespAggrCutOffTime");
    extern CLASS_EXPORT I_CHAR * const BT_TRADING                 =     I_("BT-TRADING");
    extern CLASS_EXPORT I_CHAR * const Trade_Verify               =     I_("Trade Verify");
    extern CLASS_EXPORT I_CHAR * const ThrdPrtyOffsetTime         =     I_("ThrdPrtyOffsetTime");
    extern CLASS_EXPORT I_CHAR * const DeliveryNetworkIDs         =     I_("DeliveryNetworkIDs");
    extern CLASS_EXPORT I_CHAR * const ApplyOffSetTimeForDesktop  =     I_("ApplyOffSetTimeForDesktop");

}


//******************************************************************************
NetworkConfigDetailList::NetworkConfigDetailList( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent ),
m_requestData(ifds::DSTC0461_REQ)
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );  
   setVersionable( false );
   setObjectAsList( );
}

//******************************************************************************
NetworkConfigDetailList::~NetworkConfigDetailList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************

SEVERITY NetworkConfigDetailList::init ( const DString& dstrTrack, const DString& dstrPageName)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   BFData *receivedData = new BFData (ifds::DSTC0461_VW);
   DString mgmtCoIdOut;
   m_requestData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut ));
   m_requestData.setElementValue (ifds::Track, dstrTrack);
   m_requestData.setElementValue (ifds::Activity, dstrPageName);
   ReceiveData ( DSTC_REQUEST::NETWORK_CONFIG_DETAIL, 
                 m_requestData, 
                 *receivedData, 
                 DSTCRequestor (getSecurity(), true));

   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY NetworkConfigDetailList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   NetworkConfigDetail * pNetworkConfigDetail = new NetworkConfigDetail( *this );
   pNetworkConfigDetail->init( data );
   pObjOut = pNetworkConfigDetail;       
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
bool NetworkConfigDetailList::getNetworkConfigDetail( const DString& dstrNetworkID, const DString& dstrNetworkConfigType, 
                                                      NetworkConfigDetail *&pNetworkConfigDetail ) 
{
   pNetworkConfigDetail = NULL;
   if( NULL_STRING == dstrNetworkID  )
        return(false);

   BFObjIter iter( *this, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED );
   DString dstrKey ;
   buildKey(dstrKey ,dstrNetworkID, dstrNetworkConfigType);
   if( iter.positionByKey( dstrKey ) )
   // A match was found, get the CBO  
   {
      pNetworkConfigDetail = static_cast<NetworkConfigDetail *>( iter.getObject());  
      return(true);
   }
   else
      return(false);

}
//******************************************************************************
void NetworkConfigDetailList::buildKey( DString& dstrKeyOut, const DString& dstrNetworkID, 
                                        const DString& dstrNetworkConfigType )
{
    dstrKeyOut = NULL_STRING;
    DString dstrTempString;
    dstrTempString= dstrNetworkID;
    dstrKeyOut = dstrTempString.stripAll()+ I_("$");
    dstrTempString = dstrNetworkConfigType;     
	dstrKeyOut = dstrKeyOut + dstrTempString.stripAll();
    dstrKeyOut.stripAll();
}

//******************************************************************************
void NetworkConfigDetailList::getStrKey ( DString& dstrKey, const BFData* data )
{
   TRACE_METHOD( CLASSNAME, I_( "getStrKey" ) );

   if( data )
   {
      DString dstrNetworkID         =  data->getElementValue( ifds::NetworkID);
      DString dstrNetworkConfigType =  data->getElementValue( ifds::NetworkConfigType );
      buildKey( dstrKey, dstrNetworkID, dstrNetworkConfigType );
      dstrKey.strip();
   }
   else
   {
      BFCBO::getStrKey( dstrKey, NULL );
   }
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DefaultSysConfig.cpp-arc  $	 

*/