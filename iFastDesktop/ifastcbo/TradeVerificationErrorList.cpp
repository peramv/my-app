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
// ^FILE   : TradeVerificationErrorList.cpp
// ^AUTHOR : Robbins Kuriakose
// ^DATE   : Aug-2014
//
// ^CLASS    : TradeVerificationErrorList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :	Used to get the defualt values for all fields based on the DefConfigDetails table
//
//******************************************************************************
#include "stdafx.h"
#include "TradeVerificationErrorList.hpp"
#include "TradeVerificationError.hpp"
#include "mgmtco.hpp"
#include <dataimpl\dse_dstc0463_vw.hpp>
#include <dataimpl\dse_dstc0463_vwrepeat_record.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest TRADE_VERIFICATION_UPDATE; 
}
namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME           = I_("TradeVerificationErrorList");
  
}

//******************************************************************************
TradeVerificationErrorList::TradeVerificationErrorList( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent ),
m_respData(ifds::DSTC0463_VW)
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );  
   setVersionable( false );
   setObjectAsList( );
}

//******************************************************************************
TradeVerificationErrorList::~TradeVerificationErrorList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY TradeVerificationErrorList::init(  const BFDataGroupId& idDataGroup,
									        const DString& dstrTrack,
									        const DString& dstrPageName)

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   //m_respData = receivedData;
   return GETCURRENTHIGHESTSEVERITY();
}
//******************************************************************************
SEVERITY TradeVerificationErrorList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   TradeVerificationError * pTradeVerificationError = new TradeVerificationError( *this );
   pTradeVerificationError->init( data );
   pObjOut = pTradeVerificationError;       
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
void TradeVerificationErrorList::buildKey (const TradeVerificationError * pTradeVerificationError,  DString& dstrOutKey)
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "buildKey" ) );	
	pTradeVerificationError->getField(ifds::TransNum,dstrOutKey); 
}
//******************************************************************************
void  TradeVerificationErrorList::getStrKey ( DString& dstrKey, const BFData* data )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getStrKey" ) );	
   if ( data )
   {
        dstrKey = data->getElementValue(ifds::TransNum);
		dstrKey .strip();		
   }	
}
//******************************************************************************
bool TradeVerificationErrorList::getTradeVerificationError( DString dstrTransNum, TradeVerificationError*& pTradeVerificationError)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getTradeVerificationError" ) );	
    DString dstrKey;
	pTradeVerificationError = NULL;
	BFObjIter iter (*this, BF::HOST, false, BFObjIter::ITERTYPE::NON_DELETED);
	if (iter.positionByKey (dstrTransNum))
		pTradeVerificationError = dynamic_cast<TradeVerificationError *>(iter.getObject());
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TradeVerificationErrorList.cpp-arc  $	  

*/