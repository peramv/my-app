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
// ^FILE   : TradeOverideRuleWarningsList.cpp
// ^AUTHOR : Robbins Kuriakose
// ^DATE   : Aug-2014
//
// ^CLASS    : TradeOverideRuleWarningsList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :	Used to get the defualt values for all fields based on the DefConfigDetails table
//
//******************************************************************************
#include "stdafx.h"
#include "TradeOverideRuleWarningsList.hpp"
#include "TradeOverideRuleWarnings.hpp"
#include "mgmtco.hpp"
#include <ifastdataimpl\dse_dstc0464_req.hpp>
#include <ifastdataimpl\dse_dstc0464_vw.hpp>
#include <ifastdataimpl\dse_dstc0464_vwrepeat_record.hpp> 

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest TRADEOVERIDERULEWARNINGS_LIST; 
}
namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME                   = I_("TradeOverideRuleWarningsList"); 
   const I_CHAR * const TRADE_OVERIDE_WARNINGS_LIST = I_("TradeOverideRuleWarningsList");
}

namespace ifds
{
  extern CLASS_IMPORT const BFTextFieldId NextKey;
}
//******************************************************************************
TradeOverideRuleWarningsList::TradeOverideRuleWarningsList( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent ),
 _requestData(ifds::DSTC0464_REQ)
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING ); 
 
   //setVersionable( false );
   setObjectAsList( );
}

//******************************************************************************
TradeOverideRuleWarningsList::~TradeOverideRuleWarningsList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY TradeOverideRuleWarningsList::init( const BFDataGroupId& idDataGroup,
									         const DString& dstrTrack,
									         const DString& dstrPageName)

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   m_dstrTrack = dstrTrack;
   m_dstrPageName = dstrPageName;
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TradeOverideRuleWarningsList::init( DString dstrTransNum, const BFDataGroupId& idDataGroup, bool bCreate )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init (DString dstrTransNum)" ) );

   DString mgmtCoIdOut;
   if( bCreate && dstrTransNum != m_dstrTransNum )
   {
    _requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
    _requestData.setElementValue( ifds::Track, m_dstrTrack );
    _requestData.setElementValue( ifds::Activity, m_dstrPageName );
    _requestData.setElementValue( ifds::TransNum, dstrTransNum );
    m_dstrTransNum = dstrTransNum;
    ReceiveData( DSTC_REQUEST::TRADEOVERIDERULEWARNINGS_LIST, _requestData, ifds::DSTC0464_VW, 
                 DSTCRequestor(getSecurity(), false,true) ); 
     m_dstrTransNum = dstrTransNum;
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TradeOverideRuleWarningsList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   TradeOverideRuleWarnings * pTradeOverideRuleWarnings = new TradeOverideRuleWarnings( *this );
   pTradeOverideRuleWarnings->init( data );
   pObjOut = pTradeOverideRuleWarnings;       
   return(GETCURRENTHIGHESTSEVERITY());
}
////******************************************************************************
void  TradeOverideRuleWarningsList::getStrKey ( DString& dstrKey, const BFData* data )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getStrKey" ) );	

   if ( data )
   {
        DString dstrTransNum, dstrCode;
        _requestData.getElementValue(ifds::TransNum, dstrTransNum);
        dstrKey = data->getElementValue(ifds::ErrorCode, dstrCode);
		dstrKey = dstrKey + dstrTransNum;
        dstrKey.stripAll().upperCase();		
   }	
}
////******************************************************************************
void TradeOverideRuleWarningsList::buildErrorMessage(DString& dstrErrorMessage,  const BFDataGroupId& idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "buildErrorMessage" ) );	   
    BFObjIter iter (*this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED);
    iter.begin();
    dstrErrorMessage = NULL_STRING;
    while( !iter.end())
    {
       DString dstrErrorCode, dstrMsg;
       TradeOverideRuleWarnings *pTradeOverideRuleWarnings = dynamic_cast <TradeOverideRuleWarnings *>( iter.getObject());
       if(pTradeOverideRuleWarnings)
       {
          pTradeOverideRuleWarnings->getField(ifds::ErrorCode, dstrErrorCode, idDataGroup);
          pTradeOverideRuleWarnings->getField(ifds::ErrMsg, dstrMsg ,  idDataGroup);
          dstrErrorMessage += dstrErrorCode + I_("  -  ") + dstrMsg + I_("\n");
       }
       ++iter;
    }  
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TradeOverideRuleWarningsList.cpp-arc  $	  

*/