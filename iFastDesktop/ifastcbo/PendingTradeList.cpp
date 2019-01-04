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
// ^FILE   : PendingTradeList.cpp
// ^AUTHOR : Zijian Ying
// ^DATE   : 04/29/99
//
// ^CLASS    : PendingTradeList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "pendingtradelist.hpp"
#include "pendingtradedetails.hpp"
#include "funddetaillist.hpp"
#include "mgmtco.hpp"
#include <ifastdataimpl\dse_dstc0053_vw.hpp>
#include <ifastdataimpl\dse_dstc0053_req.hpp>

namespace
{
   //Trace literals
   const I_CHAR *  CLASSNAME = I_( "PendingTradeList" );
   const int FULL_LIST = 0;
   const int MAX_REPEAT_COUNT = 25;//the value of maxRepeatCount of the view - if back end modifies it, have to change here

}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest PENDING_TRADE;
}

//******************************************************************************
PendingTradeList::PendingTradeList( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent ),
_requestData(ifds::DSTC0053_REQ)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
}

//******************************************************************************
PendingTradeList::~PendingTradeList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );

}

//******************************************************************************
SEVERITY PendingTradeList::init()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   nRequestedNoOfItems = -1;
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY PendingTradeList::init( DString& AccountNum,
                                
                                 DString& strOverrideRepeats /*= -1*/,
                                 const DString& dstrTrack,const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   //strOverrideRepeats should be less or equal to MaxRepeatCount (that's a backend rule)
   //if called with default -1 for strOverrideRepeats, the list will contain up to maxRepeatCount (25) elements
   //if called with 0 for strOverrideRepeats, the list will contain all the existing elements
   //if called with a positive number for strOverrideRepeats, the list will contain up to that number of elements
   _AccountNum = AccountNum;

   if( strOverrideRepeats == NULL_STRING )
      strOverrideRepeats = I_( "-1" );

   assert (strOverrideRepeats.asInteger() >= -1);

   int nNumEntry = strOverrideRepeats.asInteger();

   DString mgmtCoIdOut;
   _requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   _requestData.setElementValue( ifds::AccountNum, AccountNum );
   _requestData.setElementValue( ifds::BrokerCode, NULL_STRING );
   _requestData.setElementValue( ifds::BranchCode, NULL_STRING );
   _requestData.setElementValue( ifds::SlsrepCode, NULL_STRING );
   _requestData.setElementValue( ifds::NextKey,    NULL_STRING );
   _requestData.setElementValue( ifds::Track, dstrTrack );
   _requestData.setElementValue( ifds::Activity, dstrPageName );
   _requestData.setElementValue( ifds::Rebook, I_("N") );
   if( nNumEntry == -1 )
   {
      _requestData.setElementValue( ifds::OverrideRepeats,   I_("0") );
      ReceiveData(DSTC_REQUEST::PENDING_TRADE, _requestData, ifds::DSTC0053_VW, DSTCRequestor( getSecurity(), false ) );
      nRequestedNoOfItems = MAX_REPEAT_COUNT;
   }
   else if( nNumEntry == FULL_LIST )
   {
      _requestData.setElementValue( ifds::OverrideRepeats,   strOverrideRepeats );
      ReceiveData(DSTC_REQUEST::PENDING_TRADE, _requestData, ifds::DSTC0053_VW, DSTCRequestor( getSecurity(), true ) );
      nRequestedNoOfItems = FULL_LIST;
   }
   else
   {
      _requestData.setElementValue( ifds::OverrideRepeats,   strOverrideRepeats );
      ReceiveData(DSTC_REQUEST::PENDING_TRADE, _requestData, ifds::DSTC0053_VW, DSTCRequestor( getSecurity(), false ) );
      nRequestedNoOfItems = strOverrideRepeats.asInteger();
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY PendingTradeList::init( DString& AccountNum ,
                                 DString& BrokerCode, 
                                 DString& BranchCode, 
                                 DString& SlsrepCode, 
                                 DString& strOverrideRepeats, /*= -1*/ 
                                 const DString& dstrTrack,
                                 const DString& dstrPageName)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   //strOverrideRepeats should be less or equal to MaxRepeatCount (that's a backend rule)
   //if called with default -1 for strOverrideRepeats, the list will contain up to maxRepeatCount (25) elements
   //if called with 0 for strOverrideRepeats, the list will contain all the existing elements
   //if called with a positive number for strOverrideRepeats, the list will contain up to that number of elements

   if( strOverrideRepeats == NULL_STRING )
      strOverrideRepeats = I_( "-1" );

   assert (strOverrideRepeats.asInteger() >= -1);

   int nNumEntry = strOverrideRepeats.asInteger();

   _AccountNum = AccountNum;

   DString mgmtCoIdOut;
   _requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   _requestData.setElementValue( ifds::AccountNum, AccountNum );
   _requestData.setElementValue( ifds::BrokerCode, BrokerCode );
   _requestData.setElementValue( ifds::BranchCode, BranchCode );
   _requestData.setElementValue( ifds::SlsrepCode, SlsrepCode );
   _requestData.setElementValue( ifds::NextKey,    NULL_STRING );
   _requestData.setElementValue( ifds::Track, dstrTrack );
   _requestData.setElementValue( ifds::Activity, dstrPageName );

   if( nNumEntry == -1 )
   {
      _requestData.setElementValue( ifds::OverrideRepeats,   I_("0") );
      ReceiveData(DSTC_REQUEST::PENDING_TRADE, _requestData, ifds::DSTC0053_VW, DSTCRequestor( getSecurity(), false ) );
      nRequestedNoOfItems = MAX_REPEAT_COUNT;
   }
   else if( nNumEntry == FULL_LIST )
   {
      _requestData.setElementValue( ifds::OverrideRepeats,   strOverrideRepeats );
      ReceiveData(DSTC_REQUEST::PENDING_TRADE, _requestData, ifds::DSTC0053_VW, DSTCRequestor( getSecurity() , true ) );
      nRequestedNoOfItems = FULL_LIST;
   }
   else
   {
      _requestData.setElementValue( ifds::OverrideRepeats,   strOverrideRepeats );
      ReceiveData(DSTC_REQUEST::PENDING_TRADE, _requestData, ifds::DSTC0053_VW, DSTCRequestor( getSecurity(), false ) );
      nRequestedNoOfItems = strOverrideRepeats.asInteger();
   }


   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY PendingTradeList::getMore(int nNoOfNewItems /*=-1*/)
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

//******************************************************************************
// get cbo and set it
void PendingTradeList::getItem( const DString& strObjLabel,
                               const BFDataGroupId& idDataGroup, 
                               const DString& IgnoreActiveBatch,
                               const DString& rebook)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getObject" ) );


   BFAbstractCBO* pending = BFCBO::getObject( strObjLabel, BF::HOST );

   DString FundCode,ClassCode,TransType,TransNum,TradeDate;
   pending->getField( ifds::rxFundCode,FundCode, BF::HOST, true );
   FundCode.strip();
   pending->getField( ifds::rxClassCode,ClassCode, BF::HOST, true );
   ClassCode.strip();
   pending->getField( ifds::TransType,TransType, BF::HOST, false );
   TransType.strip();
   TransType = NULL_STRING;   //back end don't need transtype here
   pending->getField( ifds::PendingRid,TransNum, BF::HOST, true );
   TransNum.stripLeading( '0' );

   pending->getField( ifds::TradeDate,TradeDate, BF::HOST, true );
   TradeDate.strip('/');
   ((PendingTradeDetails* )pending)->getDetails( _AccountNum, 
                                                 FundCode, 
                                                 ClassCode, 
                                                 TransType, 
                                                 TransNum, 
                                                 TradeDate, 
												 I_("N"),
												 NULL_STRING,
												 IgnoreActiveBatch,
                                     rebook                                     
                                     );
}

//******************************************************************************
SEVERITY PendingTradeList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   pObjOut = new PendingTradeDetails( *this );
   ( ( PendingTradeDetails* ) ( pObjOut ) )->init( const_cast<BFData&>( data ) );
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void PendingTradeList::getStrKey( DString &strKey, const BFData *data )
{	  
	if ( data )
   {
      strKey = data->getElementValue(ifds::TransNum);
		strKey.strip();
		strKey += I_( "  " );
		strKey += data->getElementValue(ifds::rxFundCode);
		strKey.strip();
		strKey += I_( "  " );
		strKey += data->getElementValue(ifds::rxClassCode);
		strKey.strip(); 
		strKey += I_( "  " );
		strKey += data->getElementValue(ifds::FundTo); //PTS 10023778
		strKey.strip();
		strKey += I_( "  " );
		strKey += data->getElementValue(ifds::ClassToCode);
		strKey.strip();
		strKey += I_( "  " );
		strKey += data->getElementValue(ifds::TransType);
		strKey.strip();
		strKey += I_( "  " );
		strKey += data->getElementValue(ifds::TradeDate);
		strKey.strip();
		strKey += I_( "  " );
		strKey += data->getElementValue(ifds::PendingRid);
		strKey.strip();

		strKey.upperCase();		
   }
}
/*  This method is not used at all.
//******************************************************************************
void PendingTradeList::getStrKey( DString& dstKey, const DString& dstrFund, 
                                  const DString& dstrClass, const DString& dstrTransType,
                                  const DString& dstrAmount, const DString& dstrAmtType )
{
   TRACE_METHOD( CLASSNAME, I_( "getStrKey" ) );

   dstKey = dstrFund;
   dstKey.strip();
   dstKey += I_( "  " );
   dstKey += dstrClass;
   dstKey.strip();
   dstKey += I_( "  " );
   dstKey += dstrTransType;
   dstKey.strip();
   dstKey += I_( "  " );
   dstKey += dstrAmount;
   dstKey.strip();
   dstKey += dstrAmtType;
   dstKey.strip();

   dstKey.upperCase();
}
*/
//******************************************************************************
void PendingTradeList::buildFCKey( DString& dstKey, const DString& dstrFund, 
                                  const DString& dstrClass )
{
   TRACE_METHOD( CLASSNAME, I_( "getStrKey" ) );

   dstKey = dstrFund;
   dstKey.strip();
   dstKey += I_( "  " );
   dstKey += dstrClass;
   dstKey.strip();

   dstKey.upperCase();
}

//******************************************************************************
void PendingTradeList::buildFCTAAKey( DString& dstKey, const DString& dstrFund, 
                                  const DString& dstrClass, const DString& dstrTransType,
                                  const DString& dstrAmtType )
{
   TRACE_METHOD( CLASSNAME, I_( "getStrKey" ) );

   dstKey = dstrFund;
   dstKey.strip();
   dstKey += I_( "  " );
   dstKey += dstrClass;
   dstKey.strip();
   dstKey += I_( "  " );
   dstKey += dstrTransType;
   dstKey.strip();
   dstKey += I_( "  " );
   dstKey += dstrAmtType;
   dstKey.strip();

   dstKey.upperCase();
}

//******************************************************************************
bool PendingTradeList::dupTradeExist ( const DString& dstrFund, 
                                       const DString& dstrClass, 
                                       const DString& dstrTransType, 
                                       const DString& dstrAmount, 
                                       const DString& dstrAmtType, 
                                       const DString& dstrTransNum,
                                       const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "dupTradeExist" ));

   DString strKey;
   bool trade_exist ( false );
   BFAbstractCBO * pCurrEntry  = NULL;

   double dec_Amount=DSTCommonFunctions::convertToDouble ( dstrAmount );

   buildFCTAAKey(strKey, dstrFund, dstrClass, dstrTransType, dstrAmtType );


   BFObjIter iter(*this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);

   while( !iter.end() )
   {
      pCurrEntry = iter.getObject();
      if( pCurrEntry != NULL )
      {
         DString tradeFund, tradeClass, tradeType, tradeAmount, tradeAmtType, tradeTransNum;
         DString pendingStrKey;

         pCurrEntry->getField( ifds::rxFundCode, tradeFund,     idDataGroup );
         pCurrEntry->getField( ifds::rxClassCode,tradeClass,    idDataGroup );
         pCurrEntry->getField( ifds::TransType,  tradeType,     idDataGroup );
         pCurrEntry->getField( ifds::Amount,     tradeAmount,   idDataGroup, true );
         pCurrEntry->getField( ifds::AmountType, tradeAmtType,  idDataGroup );
         pCurrEntry->getField( ifds::TransNum,   tradeTransNum,  idDataGroup );
         if( tradeType == I_("XR") )
            tradeType = I_("TR");
         double dec_tradeAmount=DSTCommonFunctions::convertToDouble ( tradeAmount );

         buildFCTAAKey(pendingStrKey, tradeFund, tradeClass, tradeType, tradeAmtType );

         if( pendingStrKey == strKey && dec_Amount == dec_tradeAmount && dstrTransNum != tradeTransNum )
         {
            trade_exist = true;
            break;
         }
      }
      ++iter;      
   }

   return(trade_exist);   
}

//******************************************************************************
bool PendingTradeList::fundclassExist ( const DString& dstrFund, const DString& dstrClass, 
                                        const BFDataGroupId& idDataGroup , const DString& TransType)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "fundclassExist" ));

   DString strKey, tmp(TransType);
   bool trade_exist ( false );
   BFAbstractCBO *pCurrEntry  = NULL;

   buildFCKey(strKey, dstrFund, dstrClass );
   if( TransType == I_("Redemption") ) tmp = I_("PW");
   BFObjIter iter(*this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);

   while( !iter.end() )
   {
      pCurrEntry = iter.getObject();
      if( pCurrEntry != NULL )
      {
         DString tradeFund, tradeClass, pendingStrKey,transtype;
         pCurrEntry->getField( ifds::rxFundCode, tradeFund,     idDataGroup );
         pCurrEntry->getField( ifds::rxClassCode,tradeClass,    idDataGroup );
         pCurrEntry->getField( ifds::TransType,transtype,    idDataGroup );
         buildFCKey(pendingStrKey, tradeFund, tradeClass );

         if( pendingStrKey == strKey && (transtype == NULL_STRING || transtype == tmp) )
         {
            trade_exist = true;
            break;
         }
      }
      ++iter;      
   }

   return(trade_exist);   
}

//******************************************************************************

int PendingTradeList::getNoOfPreviouslyRequestedItems()
{
   TRACE_METHOD( CLASSNAME, I_( "getNoOfRequestedItems" ) );
   return(nRequestedNoOfItems);
}

//******************************************************************************
void PendingTradeList::getStrKey( DString& dstKey, const DString& dstrFund, 
                                  const DString& dstrClass, const DString& dstrTransType )
{
   TRACE_METHOD( CLASSNAME, I_( "getStrKey" ) );

   dstKey = dstrFund;
   dstKey.strip();
   dstKey += I_( "  " );
   dstKey += dstrClass;
   dstKey.strip();
   dstKey += I_( "  " );
   dstKey += dstrTransType;
   dstKey.strip();

   dstKey.upperCase();
}

//******************************************************************************
bool PendingTradeList::redemptionExist ( const DString& dstrFund, const DString& dstrClass, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "redemptionExist" ));

   DString strKey;
   bool redemption_exist ( false );
   BFAbstractCBO *pCurrEntry  = NULL;

   getStrKey(strKey, dstrFund, dstrClass, I_("PW") );

   BFObjIter iter(*this, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);

   while( !iter.end() )
   {
      pCurrEntry = iter.getObject();
      if( pCurrEntry != NULL )
      {
         DString tradeFund, tradeClass, tradeType, pendingStrKey;

         pCurrEntry->getField( ifds::rxFundCode, tradeFund,     idDataGroup );
         pCurrEntry->getField( ifds::rxClassCode,tradeClass,    idDataGroup );
         pCurrEntry->getField( ifds::TransType, tradeType, idDataGroup );

         getStrKey(pendingStrKey, tradeFund, tradeClass, tradeType );

         if( pendingStrKey == strKey )
         {
            redemption_exist = true;
            break;
         }
      }
      ++iter;      
   }

   return(redemption_exist);   
}
//******************************************************************************

SEVERITY PendingTradeList::initSearch(
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
                  const DString& rebook,
                  const DString& dstrTrack,
                  const DString& dstrPageName,
				  const DString& dstrFundCode,
				  const DString& dstrClassCode,
				  const DString& dstrTransType,
                  const DString& dstrExcludeVerifiedTrade,
                  const DString& dstrUserID )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initSearch" ) );
   //_AccountNum = AccountNum;

   DString mgmtCoIdOut;
   _requestData.setElementValue( ifds::CompanyId,       getMgmtCoId( mgmtCoIdOut ) );
   _requestData.setElementValue( ifds::SearchType,      strSearchType );
	_requestData.setElementValue( ifds::AccountNum,      strAccountNum );
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
bool PendingTradeList::PendingPACExist(const BFDataGroupId& idDataGroup )
{
  bool bRet = false;
  BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
  while( !iter.end() )
  {
	 PendingTradeDetails* pTrade = dynamic_cast<PendingTradeDetails* >( iter.getObject() );
	 if( pTrade->PendingPACExist( idDataGroup ) )
	 {
		bRet = true;
		break;
	 }  
	 ++iter;
  }
	
  return bRet;
}

bool PendingTradeList::hasNonAMSFunds(const BFDataGroupId& idDataGroup)
{
   bool retVal = false;
   DString dstrFundCode;
   DString dstrClassCode;
   BFObjIter iter( *this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);

   FundDetailList *pFundDetailList = NULL;
   if (getMgmtCo().getFundDetailList(pFundDetailList) <= WARNING && pFundDetailList)
   {
      while (!retVal && !iter.end()) 
      {
         iter.getObject()->getField ( ifds::rxFundCode, dstrFundCode, idDataGroup );
         iter.getObject()->getField ( ifds::rxClassCode, dstrClassCode, idDataGroup );
		   dstrFundCode.upperCase().strip();
         dstrClassCode.upperCase().strip();
		   if(!getWorkSession().isAMSFundClass(dstrFundCode, dstrClassCode, idDataGroup))
		   {
			   retVal = true;			
		   }     		
		   ++iter;
      }
   }
	return retVal;
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/PendingTradeList.cpp-arc  $
 * 
 *    Rev 1.42   Feb 22 2007 15:22:28   popescu
 * Incdent# 810479 - uniquely identify a pending trade by introducing the Rid in the key
 * 
 *    Rev 1.41   Jan 24 2007 14:50:08   porteanm
 * Incident 807399 - Rolled back changes for IN710770.
 * 
 *    Rev 1.40   Oct 05 2006 16:21:26   AGUILAAM
 * R74- IN 710770.  Added genkey to strkey on pending trades list;  transnum, fund, class, fundto, classto, transtype, deff are may not be unique, causing records to be skipped/ not displayed.
 * 
 *    Rev 1.39   Mar 02 2006 16:29:40   jankovii
 * PET 2072 FN01- NSCC Control Number.
 * 
 *    Rev 1.38   Jul 08 2005 09:31:34   Yingbaol
 * PET1235,FN01:transaction cancellation rebook
 * 
 *    Rev 1.37   Jun 14 2005 15:41:18   Fengyong
 * #Incident 328435 - Add IgnoreActiveBatch field to 54 request
 * 
 *    Rev 1.36   Sep 15 2004 13:17:44   VADEANUM
 * PET 1094 FN4 - Activest Bank File Interface.
 * 
 *    Rev 1.35   Sep 07 2004 15:35:24   VADEANUM
 * PET 1094 FN4 - Activest Bank File Interface - work in progress.
 * 
 *    Rev 1.34   May 11 2004 11:03:20   ZHANGCEL
 * PET1046_FN02 -- Trade Search by account enhancement
 * 
 *    Rev 1.33   Nov 20 2003 09:14:20   linmay
 * added PendingPACExist( ) for PTS #10024070
 * 
 *    Rev 1.32   Nov 17 2003 09:49:14   HSUCHIN
 * PTS 10023778 - bug fix with string key
 * 
 *    Rev 1.31   Mar 21 2003 18:20:04   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.30   Mar 03 2003 09:43:06   KOVACSRO
 * Added initSearch.
 * 
 *    Rev 1.29   Dec 12 2002 11:25:42   FENGYONG
 * Add transtype and tradedate to key
 * 
 *    Rev 1.28   Oct 09 2002 23:54:48   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.27   Aug 29 2002 12:56:24   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.26   Aug 22 2002 17:36:10   FENGYONG
 * small fix
 * 
 *    Rev 1.25   Aug 22 2002 17:24:48   FENGYONG
 * change key to TransNum, Fund , Class
 * 
 *    Rev 1.24   Aug 19 2002 15:23:56   FENGYONG
 * override getStrKey
 * 
 *    Rev 1.23   22 May 2002 18:29:38   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.22   Feb 25 2002 18:55:48   PURDYECH
 * Phase 1 of BFData Rollout - Base Component Compatibility
 * 
 *    Rev 1.21   20 Dec 2001 12:23:26   KOVACSRO
 * Changed NumEntry field to OverrideRepeats. Removed ambiguos code.
 * 
 *    Rev 1.20   Jun 15 2001 16:25:50   ZHANGCEL
 * Fiexed bug in the getItem()
 * 
 *    Rev 1.19   May 18 2001 12:52:36   JANKAREN
 * Sync up SSB(1.15.1.1)
 * 
 *    Rev 1.18   11 May 2001 08:32:12   HSUCHIN
 * Sync up with SSB (1.15.1.0)
 * 
 *    Rev 1.17   May 08 2001 16:17:40   FENGYONG
 * add transtype for fundclassexist
 * 
 *    Rev 1.16   03 May 2001 14:06:54   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.15   Apr 03 2001 15:49:46   JANKAREN
 * covert amount to deci in dupTradeExist before comparison
 * 
 *    Rev 1.14   Mar 12 2001 12:58:50   VASILEAD
 * Modified for FUNDcom release
 * 
 *    Rev 1.13   Mar 06 2001 10:25:36   YINGZ
 * bug fix
 * 
 *    Rev 1.12   Jan 29 2001 14:19:16   VASILEAD
 * Fix for previous fix
 * 
 *    Rev 1.11   Jan 29 2001 12:38:54   VASILEAD
 * Fixed the logic for BPServer ( sending NULL for NumEntry )
 * 
 *    Rev 1.10   Jan 26 2001 11:16:16   YINGBAOL
 * more track
 * 
 *    Rev 1.9   Jan 25 2001 13:56:16   YINGBAOL
 * add eTrack
 * 
 *    Rev 1.8   Jan 24 2001 12:53:16   KOVACSRO
 * Modified init(), getMore(), implemented getPreviouslyrequestedNoOfItems().
 * 
 *    Rev 1.7   Dec 17 2000 20:24:12   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.6   Dec 14 2000 15:28:22   VASILEAD
 * Fix a bug in duplicate trades
 * 
 *    Rev 1.5   Dec 06 2000 14:08:40   OLTEANCR
 * modif. ReceiveData
 * 
 *    Rev 1.4   30 Oct 2000 11:24:26   SMITHDAV
 * Changed to use the new data brokering system.
 * 
 *    Rev 1.3   Sep 13 2000 16:57:24   FENGYONG
 * Add brokercode, branchcode,slsrep
 * 
 *    Rev 1.2   Aug 28 2000 17:17:22   WINNIE
 * Bug fix for pendingofFundExist; Add fundclassExists
 * 
 *    Rev 1.1   Aug 21 2000 10:15:58   WINNIE
 * Add new method to check if duplicate exists
 * 
 *    Rev 1.0   Feb 15 2000 11:00:04   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.11   Jan 05 2000 20:11:00   BUZILA
 * adding list flag
 * 
 *    Rev 1.10   Dec 12 1999 16:25:54   POPESCUS
 * Xchgdata issue; create and delete the object in the CBO
// 
*/
