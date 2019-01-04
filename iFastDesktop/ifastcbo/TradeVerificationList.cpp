//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial Data Services,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2004 by International Financial Data Services
//
//
//******************************************************************************
//
// ^FILE   : TradeVerificationList.cpp
// ^AUTHOR : Robbins Kuriakose
// ^DATE   : JuLY 22 2014
//
//********************************************************************************

#include "stdafx.h"
#include "mgmtco.hpp"
#include "TradeVerificationSearch.hpp"
#include "TradeVerificationList.hpp"
#ifndef TRADEVERIFICATION_HPP
    #include <ifastcbo\TradeVerification.hpp>
#endif
#include <ifastdataimpl\dse_dstc0053_vw.hpp>
#include <ifastdataimpl\dse_dstc0053_req.hpp>
#include <ifastdataimpl\dse_dstc0053_vwrepeat_record.hpp>

namespace
{
   //Trace literals
   const I_CHAR *  CLASSNAME = I_( "TradeVerificationList" );
   const I_CHAR * const YES              = I_( "Y" );
   const I_CHAR * const NO               = I_( "N" );
   const I_CHAR * const TRADE_VERIFCICATION_LIST = I_( "TradeVerificationList" );
   const int MAX_REPEAT_COUNT = 25;
   const int FULL_LIST = 0;
}
namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId VerifyTrade;
   extern CLASS_IMPORT const BFTextFieldId DeleteTrade;
   extern CLASS_IMPORT const BFTextFieldId VerifyAll;
   extern CLASS_IMPORT const BFTextFieldId DeleteAll;
   extern CLASS_IMPORT const BFTextFieldId UserAction;
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest TRADE_VERIFICATION_UPDATE;
   extern CLASS_IMPORT const DSTCRequest PENDING_TRADE;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
   //  Field DD Id,                    State Flags,         Group Flags 
   { ifds::VerifyAll,                BFCBO::CALCULATED_FIELD,              0 },
   { ifds::DeleteAll,                BFCBO::CALCULATED_FIELD,              0 },
};
static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );


//******************************************************************************
TradeVerificationList::TradeVerificationList( BFAbstractCBO &parent ) : 
                       MFCanBFCbo( parent ),_requestData(ifds::DSTC0053_REQ)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   setObjectAsList( );
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}
//******************************************************************************
TradeVerificationList::~TradeVerificationList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );

}

//******************************************************************************
SEVERITY TradeVerificationList::init()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   nRequestedNoOfItems = -1;
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
SEVERITY TradeVerificationList::init(const BFDataGroupId& idDataGroup,
                                     const DString& dstrTrack,
                                     const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   TradeVerificationList *pTradeVerificationList =NULL;
   pTradeVerificationList = dynamic_cast<TradeVerificationList*>(BFCBO::getObject( TRADE_VERIFCICATION_LIST, idDataGroup ) );
   if(!pTradeVerificationList)
   {
        TradeVerificationSearch *pTradeVerificationSearch;
        if( getWorkSession().getTradeVerificationSearchCriteria(pTradeVerificationSearch, idDataGroup) <= WARNING &&
            pTradeVerificationSearch)
        pTradeVerificationSearch->getTradeVerificationList(pTradeVerificationList, idDataGroup);
   }
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************************
SEVERITY TradeVerificationList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   TradeVerification* pTradeVerification = new TradeVerification( *this );
   pTradeVerification->init( const_cast<BFData&>( data ) );
   pObjOut = pTradeVerification;
  
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************************
SEVERITY TradeVerificationList::markAllTradeToVerifyOrReject( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setAllTradeToVerify" ) );

   DString dstrVerifyAll, dstrDeleteAll;
   getField(ifds::VerifyAll, dstrVerifyAll, idDataGroup, false );
   getField(ifds::DeleteAll, dstrDeleteAll, idDataGroup, false );
   BFObjIter iter( *this, idDataGroup,true,BFObjIter::ITERTYPE::NON_DELETED );
   if( dstrVerifyAll == YES)  
       markAllTradeToVerify(idDataGroup);
   else if( dstrDeleteAll == YES)   
       markAllTradeToDelete(idDataGroup); 
   else
       clearAllFlags(idDataGroup);   
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************************
void  TradeVerificationList::markAllTradeToVerify( const BFDataGroupId& idDataGroup )
{
  MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "markAllTradeToVerify" ) );

  BFObjIter iter( *this, idDataGroup,true,BFObjIter::ITERTYPE::NON_DELETED );  
  while( !iter.end() )
   {
     TradeVerification* pTradeVerification = dynamic_cast<TradeVerification*>(iter.getObject() );
     if( pTradeVerification )
     {
       pTradeVerification->setAllTradesVerifyDeleteFlag(ifds::VerifyTrade, idDataGroup);
       ++iter;
     }
   }
}
//******************************************************************************************
void  TradeVerificationList::markAllTradeToDelete( const BFDataGroupId& idDataGroup )
{
  MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "markAllTradeToDelete" ) );

  BFObjIter iter( *this, idDataGroup,true,BFObjIter::ITERTYPE::NON_DELETED );  
  while( !iter.end() )
   {
     TradeVerification* pTradeVerification = dynamic_cast<TradeVerification*>(iter.getObject() );
     if( pTradeVerification )
     {
       pTradeVerification->setAllTradesVerifyDeleteFlag(ifds::DeleteTrade, idDataGroup);
       ++iter;
     }
   }
}
//******************************************************************************************
void TradeVerificationList::clearAllFlags( const BFDataGroupId& idDataGroup )
{
  MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "clearAllFlags" ) );

  BFObjIter iter( *this, idDataGroup,true,BFObjIter::ITERTYPE::NON_DELETED );  
  while( !iter.end() )
   {
     TradeVerification* pTradeVerification = dynamic_cast<TradeVerification*>(iter.getObject() );
     if( pTradeVerification )
     {
       pTradeVerification->clearAllFlags( idDataGroup );
       ++iter;
     }
   }
}
//******************************************************************************************
bool TradeVerificationList::bMoreThanOne( const BFDataGroupId& idDataGroup )
{ 
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "bMoreThanOne" ) );

   BFObjIter iter( *this, idDataGroup,true,BFObjIter::ITERTYPE::NON_DELETED );
   DString dstrAction;
   int iNum = 0;
   while( !iter.end() )
   {
      iter.getObject()->getField(ifds::UserAction, dstrAction,idDataGroup,false);
      if(!dstrAction.empty() )
      {
         iNum++;
      }
      if( iNum>1 ) return(true);
      ++iter;
   }
   return(false);

}
//******************************************************************************************
void  TradeVerificationList::clearUserActionFlag(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "clearUserActionFlag" ) );

   BFObjIter iter( *this, idDataGroup,true,BFObjIter::ITERTYPE::NON_DELETED );
   DString  dstrUserAction, dstrVerify, dstrDelete;  
   while( !iter.end() )
   {
      TradeVerification* pTradeVerification = dynamic_cast<TradeVerification*>(iter.getObject() );
      if( pTradeVerification )
      {
          pTradeVerification ->getField(ifds::VerifyTrade,dstrVerify, idDataGroup); 
          pTradeVerification ->getField(ifds::DeleteTrade,dstrDelete, idDataGroup);
          if(dstrVerify.empty() && dstrDelete.empty())          
             pTradeVerification ->clearUpdatedFlags(idDataGroup);
      }
      ++iter;
   }
}
//******************************************************************************
SEVERITY TradeVerificationList::getMore(int nNoOfNewItems /*=-1*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );
   //strOverrideRepeats should be less or equal to MaxRepeatCount (that's a backend rule)
   //if called with default -1 for nNoOfNewItems, the list could grow up to maxRepeatCount (25) elements
   //if called with 0 for nNoOfNewItems, the list will grow to contain all the existing elements
   //if called with a positive number for nNoOfNewItems, the list could grow up to the specified number of elements

   if( doMoreRecordsExist() )
   {
      assert (nNoOfNewItems >= -1);

      if( nNoOfNewItems != -1 )
      {
         DString strOverrideRepeats;
         strOverrideRepeats = DString::asString( nNoOfNewItems );
         _requestData.setElementValue( ifds::OverrideRepeats,   strOverrideRepeats );
         if( nNoOfNewItems == FULL_LIST )
         {
            ReceiveData(DSTC_REQUEST::PENDING_TRADE, _requestData, ifds::DSTC0053_VW, DSTCRequestor( getSecurity(), true ) );
            nRequestedNoOfItems = FULL_LIST;
         }
         else
         {
            ReceiveData(DSTC_REQUEST::PENDING_TRADE, _requestData, ifds::DSTC0053_VW, DSTCRequestor( getSecurity(), false ) );
            nRequestedNoOfItems += nNoOfNewItems;
         }
      }
      else
      {
         _requestData.setElementValue( ifds::OverrideRepeats,   I_("0") );
         ReceiveData(DSTC_REQUEST::PENDING_TRADE, _requestData, ifds::DSTC0053_VW, DSTCRequestor( getSecurity(), false ) );
         nRequestedNoOfItems += MAX_REPEAT_COUNT;
      }

   };
   return(GETCURRENTHIGHESTSEVERITY());
}
////******************************************************************************
SEVERITY TradeVerificationList::initSearch(
                                          const DString& strSearchType,
						                  const DString& strAccountNum,
                                          const DString& strTransNum,
                                          const DString& strWireOrdNum, 
                                          const DString& strNetworkID, 
                                          const DString& strExtTransNum, 
                                          const DString& strSendRefNum,
                                          const DString& strMasterRefNum, 
                                          const DString& strPartRefNum,
                                          const DString& strFromDate, 
                                          const DString& strToDate,
				                          const DString& strExternalIdType,
				                          const DString& strExternalId,
				                          const DString& strNSCCControlNumber,
                                          const DString& rebook,/*I_("N")*/
                                          const DString& dstrTrack,
                                          const DString& dstrPageName,
				                          const DString& dstrFundCode,
				                          const DString& dstrClassCode,
				                          const DString& dstrTransType,/*ALL*/
                                          const DString& dstrExcludeVerifiedTrades, /*= YES*/ 
                                          const DString& dstrUserID,
                                          const DString& dstrExcludeAggrOrd, /* = YES */
										  const DString& dstrSponsorCode,
										  const DString& dstrPlatform)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initSearch" ) );
   //_AccountNum = AccountNum;

   DString mgmtCoIdOut;
   _requestData.setElementValue( ifds::CompanyId,       getMgmtCoId( mgmtCoIdOut ) );
   _requestData.setElementValue( ifds::SearchType,      strSearchType );
   _requestData.setElementValue( ifds::AccountNum,     strAccountNum );
   _requestData.setElementValue( ifds::TransNum,        strTransNum );
   _requestData.setElementValue( ifds::WireOrdNum,      strWireOrdNum );
   _requestData.setElementValue( ifds::NetworkID,       strNetworkID );
   _requestData.setElementValue( ifds::ExtTransNum,     strExtTransNum );
   _requestData.setElementValue( ifds::SendRefNum,      strSendRefNum );
   _requestData.setElementValue( ifds::MasterRefNum,    strMasterRefNum );
   _requestData.setElementValue( ifds::PartRefNum,      strPartRefNum );
   _requestData.setElementValue( ifds::Track,           dstrTrack );
   _requestData.setElementValue( ifds::Activity,        dstrPageName );
   _requestData.setElementValue( ifds::OverrideRepeats, I_("0") );
   _requestData.setElementValue( ifds::FromDate,        strFromDate, false, false );
   _requestData.setElementValue( ifds::ToDate,          strToDate, false, false );
   _requestData.setElementValue( ifds::ExternalIdType,  strExternalIdType );
   _requestData.setElementValue( ifds::ExternalId,      strExternalId );
   _requestData.setElementValue( ifds::Rebook,      rebook );
   _requestData.setElementValue( ifds::NSCCControlNumber, strNSCCControlNumber );
   _requestData.setElementValue( ifds::FundCode   , dstrFundCode);
   _requestData.setElementValue( ifds::ClassCode  , dstrClassCode);
   _requestData.setElementValue( ifds::TransType  , dstrTransType);
   _requestData.setElementValue( ifds::ExcludeVerifiedTrades , dstrExcludeVerifiedTrades);
   _requestData.setElementValue( ifds::SearchUserID , dstrUserID);
   //_requestData.setElementValue( ifds::ExcludeBadTrades , YES );//Exclude Bad trades always for verification
   _requestData.setElementValue( ifds::ExcludeAggrOrd, dstrExcludeAggrOrd);//Exclude Aggrgated Oreder trades always for verification
   _requestData.setElementValue( ifds::SponsorCode, dstrSponsorCode);
   _requestData.setElementValue( ifds::Platform, dstrPlatform);
   ReceiveData(DSTC_REQUEST::PENDING_TRADE, _requestData, ifds::DSTC0053_VW, DSTCRequestor( getSecurity(), false ) );
   nRequestedNoOfItems = MAX_REPEAT_COUNT;
   //rules:
   //1. If both FromDate and ToDate are empty, all the trades that match the criteria
   //will be returned, from the very first one to the latest one
   //2. If FromDate is a valid date and ToDate is empty, all the trades that match the criteria
   //starting from FromDate to the latest one will be returned (empty means 9999/12/31)
   //3. The situation when FromDate is empty and ToDate is specified is an error.It should never happen
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
void TradeVerificationList::getStrKey( DString &strKey, const BFData *data )
{	 
  MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getStrKey" ) );

  if ( data )
   {
        strKey = data->getElementValue(ifds::TransNum);
		strKey.strip();		
   }
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/TradeVerificationProcess.cpp-arc  $
// 
//    Rev 1.0  22 July 2014
// Initial revision.
*/
