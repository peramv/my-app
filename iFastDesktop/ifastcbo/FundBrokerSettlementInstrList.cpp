//********************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2003 By International Financial Data Services.
//
//
//********************************************************************************
//
// ^FILE   : FundBrokerSettlementInstrList.cpp
// ^AUTHOR : 
// ^DATE   : 
//
//********************************************************************************
#include "stdafx.h"
#include "FundBrokerSettlementInstr.hpp"
#include "FundBrokerSettlementInstrList.hpp"
#include "SettlementInstrList.hpp"

#include <ifastdataimpl\dse_dstc0317_vw.hpp>
#include <ifastdataimpl\dse_dstc0317_vwrepeat_record.hpp>
#include <ifastdataimpl\dse_dstc0317_req.hpp>


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest SETTLEMENT_INSTRUCTIONS_LIST_INQUIRY;
}

namespace
{
   const I_CHAR * const CLASSNAME = I_( "FundBrokerSettlementInstrList" );
}

namespace CND
{
   extern const long ERR_MISSING_DEFAULT_SETTLEMENT_INSTR;
   extern const long ERR_MULTIPLE_DEFAULT_SETTLEMENT_INSTR;
}

****************************************************************************
FundBrokerSettlementInstrList::FundBrokerSettlementInstrList( BFAbstractCBO &parent )
: SettlementInstrList( parent ),
m_requestData( ifds::DSTC0317_REQ )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
	
   setObjectAsList( );
}

//******************************************************************************
FundBrokerSettlementInstrList::~FundBrokerSettlementInstrList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}
//***********************************************************************************
SEVERITY FundBrokerSettlementInstrList::doCreateObject( const BFData& data, BFCBO*& pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );
   
	pObjOut =  new FundBrokerSettlementInstr( *this );
   ((FundBrokerSettlementInstr*) pObjOut)->init( data );
   
	return( GETCURRENTHIGHESTSEVERITY() );
}

//**************************************************************************************
SEVERITY FundBrokerSettlementInstrList::doCreateNewObject( BFCBO *&pObjOut, DString &strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );
   
	pObjOut =  new FundBrokerSettlementInstr( *this );
   ((FundBrokerSettlementInstr*) pObjOut)->init( idDataGroup );
   
	return( GETCURRENTHIGHESTSEVERITY() );
}

//**********************************************************************************
void  FundBrokerSettlementInstrList::getStrKey( DString &dstrKey, const BFData *data  )
{
   if (data) 
   {
      
      DString dstrFundBrokerCode = data->getElementValue (ifds::FundBrokerCode );
      DString dstrSettleInstrCode = data->getElementValue (ifds::SettlementInstrCode );		
      
      buildKey( dstrKey, 
				dstrFundBrokerCode, 
				dstrSettleInstrCode );		
   }
   else
   {
      BFCBO::getStrKey (dstrKey, NULL);
   }
}

//**********************************************************************************
void  FundBrokerSettlementInstrList::buildKey(	DString &dstrKey, 
												const DString &dstrFundBrokerCode,
												const DString &dstrSettleInstrCode )
{
	DString dstrLocalFundBrokerCode(dstrFundBrokerCode),
		    dstrLocalSettleInstrCode(dstrSettleInstrCode);   
	
	dstrKey = I_("FundBrokerCode=") + dstrLocalFundBrokerCode.stripAll().upperCase() +
			    I_(";SettlementInstrCode=") + dstrLocalSettleInstrCode.stripAll().upperCase();
}

//**********************************************************************************
SEVERITY FundBrokerSettlementInstrList::getFundBrokerSettlementInstr(  const DString &dstrSettleInstrCode,																			 
								   										const BFDataGroupId &idDataGroup,
												                        FundBrokerSettlementInstr *&pFundBrokerSettlementInstr )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("getFundBrokerSettlementInstr") );

	pFundBrokerSettlementInstr = NULL;

	DString dstrKey, dstrFundBrokerCode;
	getParent()->getField( ifds::FundBrokerCode, dstrFundBrokerCode, idDataGroup );
	buildKey( dstrKey, dstrFundBrokerCode, dstrSettleInstrCode );

	pFundBrokerSettlementInstr = dynamic_cast<FundBrokerSettlementInstr*>( getObject( dstrKey, idDataGroup ) );

	return(GETCURRENTHIGHESTSEVERITY());
}

//**************************************************************************************
SEVERITY FundBrokerSettlementInstrList::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{ 
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   // Check to ensure that one list item is marked default if a list exists.
	short nFound = 0;
   DString dstrDefault;

   // Check list
   bool bList = false;
   BFObjIter iter( *this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
   while( !iter.end() && nFound < 2)
   {
      if( !iter.isDummy() )
      {
         bList = true;
         iter.getObject()->getField( ifds::DefaultSettlementInstr, dstrDefault, idDataGroup, false );
         dstrDefault.stripAll().upperCase();
         if( dstrDefault == I_("Y") ) 
         {
            ++nFound;
         }
      }
      ++iter;
   }

   if( bList )
   {
      if( nFound == 0 )
      {
         ADDCONDITIONFROMFILE( CND::ERR_MISSING_DEFAULT_SETTLEMENT_INSTR );
      }
      else if( nFound > 1 )
      {
         ADDCONDITIONFROMFILE( CND::ERR_MULTIPLE_DEFAULT_SETTLEMENT_INSTR ); // This is backup.  Should be caught earlier.
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
