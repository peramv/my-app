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
// ^FILE   : TradeTransTypeSetFromMiscInfoList.cpp
// ^AUTHOR : Robbins Kuriakose
// ^DATE   : 04 April 2014
//
// ^CLASS    : TradeTransTypeSetFromMiscInfoList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :	Used to get the Network Config Details 
//
//******************************************************************************
#include "stdafx.h"
#include "TradeTransTypeSetFromMiscInfoList.hpp"
#include "TradeTransTypeSetFromMiscInfo.hpp"
#include <ifastdataimpl\dse_dstc0254_req.hpp>
#include <ifastdataimpl\dse_dstc0254_vw.hpp>
namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest MISC_INFO_TRANSLATION_TABLE; 
}
namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME  = I_("TradeTransTypeSetFromMiscInfoList");
}
namespace TRADETYPE
{
    extern CLASS_IMPORT I_CHAR * const PURCHASE;
    extern CLASS_IMPORT I_CHAR * const REDEMPTION;
    extern CLASS_IMPORT I_CHAR * const EXCHANGE;
    extern CLASS_IMPORT I_CHAR * const EXCHANGE_IN;
    extern CLASS_IMPORT I_CHAR * const EXCHANGE_OUT;
    extern CLASS_IMPORT I_CHAR * const TRANSFER;
    extern CLASS_IMPORT I_CHAR * const TRANSFER_IN;
    extern CLASS_IMPORT I_CHAR * const TRANSFER_OUT;
    extern CLASS_IMPORT I_CHAR * const DIVIDEND;
    extern CLASS_IMPORT I_CHAR * const ADMIN_FEE;
    extern CLASS_IMPORT I_CHAR * const AUTO_WITHDRAW;
}

const DString m_DefaultTradeType[] =
{
  TRADETYPE::PURCHASE,
  TRADETYPE::REDEMPTION,
  TRADETYPE::DIVIDEND,
  TRADETYPE::ADMIN_FEE,
  TRADETYPE::AUTO_WITHDRAW,
  TRADETYPE::TRANSFER,
  TRADETYPE::TRANSFER_IN,
  TRADETYPE::TRANSFER_OUT,
};
static const int _numDefaultTradeType = sizeof(m_DefaultTradeType) / sizeof(DString);


//******************************************************************************
TradeTransTypeSetFromMiscInfoList::TradeTransTypeSetFromMiscInfoList( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent ),
m_requestData(ifds::DSTC0254_REQ),m_dstrTransTypeList(NULL_STRING), m_filteredList(NULL_STRING)
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );  
   setVersionable( false );
   setObjectAsList( );
}

//******************************************************************************
TradeTransTypeSetFromMiscInfoList::~TradeTransTypeSetFromMiscInfoList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************

SEVERITY TradeTransTypeSetFromMiscInfoList::init ( const DString& dstrTrack, const DString& dstrPageName)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   BFData *receivedData = NULL;
   DString mgmtCoIdOut;
   m_requestData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut ));
   m_requestData.setElementValue (ifds::Track, dstrTrack);
   m_requestData.setElementValue (ifds::Activity, dstrPageName);
   for(int i =0; i <_numDefaultTradeType ; i++)
   {
        receivedData = new BFData (ifds::DSTC0254_VW);
		m_requestData.setElementValue(ifds::GroupCode, m_DefaultTradeType[i]); 
        ReceiveData ( DSTC_REQUEST::MISC_INFO_TRANSLATION_TABLE, 
                        m_requestData, 
                        *receivedData, 
                        DSTCRequestor (getSecurity(), true));
        //createObjectForEachRepeat( receivedData );
   }
  return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY TradeTransTypeSetFromMiscInfoList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );
   DString dstrRequestTransType  =  m_requestData.getElementValue( ifds::GroupCode );
   DString dstrResponseTransType =  data.getElementValue( ifds::GroupCode);
   if( dstrRequestTransType.stripAll() ==  dstrResponseTransType.stripAll() )
   {
       TradeTransTypeSetFromMiscInfo *pTradeTransTypeSetFromMiscInfo = new TradeTransTypeSetFromMiscInfo( *this );
       pTradeTransTypeSetFromMiscInfo->init( data );
       pObjOut = pTradeTransTypeSetFromMiscInfo;  
   }     
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
void TradeTransTypeSetFromMiscInfoList::getSysLevelTransTypeList( DString& dstrTransList ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getSysLevelTransTypeList" ) );

   if( NULL_STRING == m_dstrTransTypeList )
   {
     buildTransTypeList();
   }  
   
   dstrTransList = m_dstrTransTypeList;
   
}
//******************************************************************************
void TradeTransTypeSetFromMiscInfoList::buildTransTypeList( ) 
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "buildTransTypeList" ) );

   BFObjIter iter( *this, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED );
   iter.begin();
   while(!iter.end())
   {
      m_dstrTransTypeList = m_dstrTransTypeList + iter.getStringKey() + I_(",");
   }  
}
//******************************************************************************
void TradeTransTypeSetFromMiscInfoList::getStrKey ( DString& dstrKey, const BFData* data )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getStrKey" ) );

   if( data )
   {
      DString dstrTransType    =  data->getElementValue( ifds::GroupCode);
      DString dstrINDCCode     =  data->getElementValue( ifds::MiscCode );
      buildKey( dstrKey, dstrTransType.stripAll(), dstrINDCCode.stripAll() );
      dstrKey.strip();
   }
   else
   {
      BFCBO::getStrKey( dstrKey, NULL );
   }
}
//******************************************************************************
void TradeTransTypeSetFromMiscInfoList::buildKey( DString& dstrKeyOut, const DString& dstrTransType, 
                                                  const DString& dstrINDCCode )
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "buildKey" ) );

    dstrKeyOut = NULL_STRING;
    DString dstrTempString;
    dstrTempString= dstrTransType;
    dstrKeyOut = dstrTempString.stripAll();
    dstrTempString = dstrINDCCode; 
    dstrKeyOut = dstrKeyOut + dstrTempString.stripAll();    	
    dstrKeyOut.stripAll();    
    m_dstrTransTypeList = m_dstrTransTypeList + dstrKeyOut + I_(",") ;
    //fake the transtype for exchanges as for the view all exchanges are transfers
    if(TRADETYPE::TRANSFER == dstrTransType ) 
       m_dstrTransTypeList = m_dstrTransTypeList + I_(",") + TRADETYPE::EXCHANGE     + dstrINDCCode;
    if(TRADETYPE::TRANSFER_IN == dstrTransType )
       m_dstrTransTypeList = m_dstrTransTypeList + I_(",") + TRADETYPE::EXCHANGE_IN  + dstrINDCCode;
    if(TRADETYPE::TRANSFER_OUT == dstrTransType)
       m_dstrTransTypeList = m_dstrTransTypeList + I_(",") + TRADETYPE::EXCHANGE_OUT + dstrINDCCode;
}
//******************************************************************************
void TradeTransTypeSetFromMiscInfoList::setFilteredString( const DString& dstrFilteredList)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setFilteredString" ) );

  if( !dstrFilteredList.empty())
       m_filteredList = dstrFilteredList;
}
//******************************************************************************
void TradeTransTypeSetFromMiscInfoList::getFilteredString(DString& dstrFilteredList)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getFilteredString" ) );

   dstrFilteredList = m_filteredList;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DefaultSysConfig.cpp-arc  $	 

*/