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
// ^FILE   : TradeSearchCriteria.cpp
// ^AUTHOR : Robert Kovacs
// ^DATE   : 02/24/2003
//
// ^CLASS    : TradeSearchCriteria
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "pendingtradelist.hpp"
#include "transactionlist.hpp"
#include "tradesearchcriteria.hpp"

#include "FundDetailList.hpp"
#include "FundDetail.hpp"
#include "fundmaster.hpp"
#include "fundmasterlist.hpp"

#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "dstcworksession.hpp"

#include <ifastdataimpl\dse_dstc0017_req.hpp>
#include <ifastdataimpl\dse_dstc0053_req.hpp>

namespace  
{
   const I_CHAR * const CLASSNAME        = I_( "TradeSearchCriteria" );
   const I_CHAR * const YES              = I_( "Y" );
   const I_CHAR * const NO               = I_( "N" );
   const I_CHAR * const PENDING_LIST     = I_( "PendingList" );
   const I_CHAR * const TRANSACTION_LIST = I_( "TransactionList" );
   const I_CHAR * const NETWORK          = I_( "NetworkID" );
   const I_CHAR * const TRANSNUM         = I_( "TransNum" );
   const I_CHAR * const WIREORD          = I_( "WireOrdNum" );
   const I_CHAR * const EXTTRANS         = I_( "ExtTransNum" );
   const I_CHAR * const SENDREF          = I_( "SendRefNum" );
   const I_CHAR * const PARTREF          = I_( "PartRefNum" );
   const I_CHAR * const MASTERREF        = I_( "MasterRefNum" );
   const I_CHAR * const ACCOUNTNUM       = I_( "AccountNum" );
   const I_CHAR * const EXTERNAL_ID      = I_( "ExternalIdType" );
   const I_CHAR * const TRADE_DATE       = I_( "TradeDate" );
   const I_CHAR * const FUND_CLASS       = I_( "FundCode" );
   const I_CHAR * const ALL_TRADES         = I_( "All" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId Pending;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFTextFieldId SWIFTTradeSearch;
   extern CLASS_IMPORT const BFTextFieldId TradeSearch;
   extern CLASS_IMPORT const BFTextFieldId NetworkOrder;
   extern CLASS_IMPORT const BFDecimalFieldId ToDateContr;

   extern CLASS_IMPORT const BFTextFieldId AltAccount;
   extern CLASS_IMPORT const BFTextFieldId FundIDType;
   extern CLASS_IMPORT const BFTextFieldId FundIDValue;
   extern CLASS_IMPORT const BFTextFieldId TransType;   
   extern CLASS_IMPORT const BFDecimalFieldId Units;

   extern CLASS_IMPORT const BFTextFieldId FundISIN; 
   extern CLASS_IMPORT const BFTextFieldId FundWKN;
   extern CLASS_IMPORT const BFTextFieldId FundNumber;
   extern CLASS_IMPORT const BFTextFieldId FundName;  

   extern CLASS_IMPORT const BFTextFieldId BulkCancelAllowed;
   extern CLASS_IMPORT const BFTextFieldId NSCCCompliant;
   extern CLASS_IMPORT const BFTextFieldId TradesSearchTransType;
}

namespace  CND
{
   extern CLASS_IMPORT const I_CHAR *BFBASE_CONDITION;

   extern const long ERR_SECOND_DATE_EARLIER;
   extern CLASS_IMPORT const long ERR_FIELD_VALUE_NOT_VALID;
   extern const long WARN_INVALID_FUND_NUMBER;
   extern const long ERR_INVALID_FUND_CLASS_CODES;
   extern const long ERR_INVALID_FUND_WKN;
   extern const long ERR_INVALID_FUND_ISIN;
	//extern const long WARN_INVALID_FUND;}
}

const BFFieldId criteriaFields[]=
{
   ifds::TransNum,
   ifds::WireOrdNum,
   ifds::NetworkID,
   ifds::ExtTransNum,
   ifds::SendRefNum,
   ifds::PartRefNum,
   ifds::MasterRefNum,
   ifds::AccountNum,
   ifds::ExternalIdType,
   ifds::ExternalId,
   ifds::AltAccount,
   ifds::TradeDate,
   ifds::NSCCControlNumber,
   ifds::FundCode,
   ifds::SearchUserID,
   ifds::TradesSearchTransType,
   //FromDate, ToDate are considered additional criteria fields; they cannot be used as
   //independent criteria fields
};
static const int numCriteriaFields = sizeof( criteriaFields ) / sizeof( BFFieldId );

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//   Field DD Id,           State Flags,                    Group Flags 
   { ifds::FromDate,		BFCBO::NONE,                    0 }, 
   { ifds::ToDate,			BFCBO::NONE,                    0 }, 
   { ifds::Pending,			BFCBO::NONE,                    0 }, 
   { ifds::TransNum,		BFCBO::NONE,                    0 }, 
   { ifds::WireOrdNum,		BFCBO::NONE,                    0 }, 
   { ifds::NetworkID,		BFCBO::NONE,                    0 }, 
   { ifds::ExtTransNum,		BFCBO::NONE,                    0 }, 
   { ifds::SendRefNum,		BFCBO::NONE,                    0 }, 
   { ifds::PartRefNum,		BFCBO::NONE,                    0 }, 
   { ifds::MasterRefNum,	BFCBO::NONE,                    0 }, 
   { ifds::SearchType,		BFCBO::NONE,                    0 }, 
   { ifds::AccountNum,		BFCBO::NONE,                    0 },
   { ifds::ExternalIdType,	BFCBO::CALCULATED_FIELD,        0 },
   { ifds::ExternalId,		BFCBO::CALCULATED_FIELD,        0 },
   { ifds::NSCCControlNumber,	BFCBO::NONE,                    0 }, 
   { ifds::TradesSearchTransType,	BFCBO::NONE,            0 },


	//cross edits
   { ifds::ToDateContr,        BFCBO::IMMEDIATE_VALIDATION, 0 }, 

   { ifds::AltAccount,         BFCBO::NONE,                 0 },
   { ifds::FundIDValue,        BFCBO::NONE,                 0 },
   { ifds::FundIDType,         BFCBO::NONE,                 0 },
   { ifds::TransType,          BFCBO::NONE,                 0 },
   { ifds::Units,			   BFCBO::NONE,				    0 },
   { ifds::TradeDate,	       BFCBO::NONE,		  		    0 },
   { ifds::FundCode,		   BFCBO::NONE,				    0 },
   { ifds::ClassCode,		   BFCBO::NONE,				    0 },
   { ifds::FundISIN,		   BFCBO::NONE,				    0 },
   { ifds::FundWKN,			   BFCBO::NONE,				    0 },
   { ifds::FundNumber,		   BFCBO::NONE,				    0 },
   { ifds::FundName,		   BFCBO::NONE,				    0 },
   { ifds:: BulkCancelAllowed, BFCBO::NONE,				    0 }, 
   { ifds::SearchUserID,	    BFCBO::NONE,			    0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = {
   //  Object Label,                  State Flags,      Group Flags 
   { I_( "PendingList" ),             BFCBO::NONE,      0},
   { I_( "TransactionList" ),         BFCBO::NONE,      0},
   
};

static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );

//****************************************************************************
TradeSearchCriteria::TradeSearchCriteria( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       NUM_OBJECTS, 
							  (const CLASS_OBJECT_INFO *)&classObjectInfo );

   addCrossEdit(ifds::ToDateContr, ifds::FromDate);
   addCrossEdit(ifds::ToDateContr, ifds::ToDate);
}

//****************************************************************************
TradeSearchCriteria::~TradeSearchCriteria()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}   

//****************************************************************************

SEVERITY TradeSearchCriteria::init(const BFDataGroupId& idDataGroup /*=BF::HOST*/,
   const DString& dstrTrack /*= I_("N")*/, const DString& dstrPageName /*= NULL_STRING*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   doInitWithDefaultValues(idDataGroup);
	setObjectNew();

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

void TradeSearchCriteria::doInitWithDefaultValues(const BFDataGroupId& idDataGroup)
{

	//rules for default values:
	//1. FromDate is current business date
	//2. ToDate is current business date
	//3. All the other text fields are empty
	//4. All the other integer fields are zero
   //5. Default search for is Pending
   //6. Default search type using is Transaction number

	//set SearchType code substitution set
	loadSearchTypeSubstList(idDataGroup);

	//FromDate, ToDate is current business date
	DString dstrCurrBusDate = getCurrentBusDate();

   setFieldNoValidate(ifds::FromDate,         dstrCurrBusDate, idDataGroup, false, true, true);
   setFieldNoValidate(ifds::ToDate,           dstrCurrBusDate, idDataGroup, false, true, true);
   setFieldNoValidate(ifds::TradeDate,        dstrCurrBusDate, idDataGroup, false, true, true);

   setFieldNoValidate(ifds::TransNum,		I_("0"),     idDataGroup, false, true, true,  false);
   setFieldNoValidate(ifds::WireOrdNum,		NULL_STRING, idDataGroup, false, true, true,  false);
   DString dstrNSCCCompliant;

   getWorkSession().getOption( ifds::NSCCCompliant, dstrNSCCCompliant, idDataGroup, false );

   if (dstrNSCCCompliant == I_("Y") )
      setFieldNoValidate(ifds::NSCCControlNumber,	NULL_STRING, idDataGroup, false, true, true,  false);

   setFieldNoValidate(ifds::NetworkID,        NULL_STRING, idDataGroup, false, true, true,  false);
   setFieldNoValidate(ifds::ExtTransNum,      NULL_STRING, idDataGroup, false, true, true,  false);
   setFieldNoValidate(ifds::SendRefNum,       NULL_STRING, idDataGroup, false, true, true,  false);
   setFieldNoValidate(ifds::PartRefNum,       NULL_STRING, idDataGroup, false, true, true,  false);
   setFieldNoValidate(ifds::MasterRefNum,     NULL_STRING, idDataGroup, false, true, true,  false);
   setFieldNoValidate(ifds::AccountNum,       NULL_STRING, idDataGroup, false, true, true,  false);
   setFieldNoValidate(ifds::ExternalIdType,   NULL_STRING, idDataGroup, false, true, true,  false);
   setFieldNoValidate(ifds::ExternalId,       NULL_STRING, idDataGroup, false, true, true,  false);
   setFieldNoValidate(ifds::SearchType,       TRANSNUM,    idDataGroup, false);

   setFieldNoValidate(ifds::AltAccount,       NULL_STRING, idDataGroup, false, true, true,  false);
   setFieldNoValidate(ifds::FundIDType,       NULL_STRING, idDataGroup, false, true, true,  false);
   setFieldNoValidate(ifds::FundIDValue,      NULL_STRING, idDataGroup, false, true, true,  false);
   setFieldNoValidate(ifds::TransType,        NULL_STRING, idDataGroup, false, true, true,  false);
   setFieldNoValidate(ifds::Units,            NULL_STRING, idDataGroup, false, true, true,  false);

   setFieldNoValidate(ifds::FundCode,         NULL_STRING, idDataGroup, false, true, true,  false);
   setFieldNoValidate(ifds::ClassCode,        NULL_STRING, idDataGroup, false, true, true,  false);
   setFieldNoValidate(ifds::FundNumber,       NULL_STRING, idDataGroup, false, true, true,  false);
   setFieldNoValidate(ifds::FundName,         NULL_STRING, idDataGroup, false, true, true,  false);
   setFieldNoValidate(ifds::FundISIN,         NULL_STRING, idDataGroup, false, true, true,  false);
   setFieldNoValidate(ifds::FundWKN,          NULL_STRING, idDataGroup, false, true, true,  false);
   setFieldNoValidate(ifds::TradesSearchTransType, I_("ALL"), idDataGroup, false, true, true,  false);

   setFieldNoValidate(ifds::BulkCancelAllowed, I_( "N" ), idDataGroup,   false, true, true,  false);   
}

//****************************************************************************
SEVERITY TradeSearchCriteria::getPendingList( PendingTradeList *&pPendingList, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getPendingList" ) );
   //check cbobase to see if we've already built it
   //otherwise, create and store with base
   pPendingList = dynamic_cast<PendingTradeList*>(BFCBO::getObject( PENDING_LIST, idDataGroup ) );

   if( !pPendingList )
   {
      pPendingList = new PendingTradeList( *this );
      DString strTransNum, strWireOrdNum, strNetworkID, strExtTransNum,strAccountNum, 
              strSendRefNum, strMasterRefNum, strPartRefNum, strFromDate, strToDate, strSearchType,
              strExternalIdType, strExternalId, strNSCCControlNumber, strFundCode, strClassCode, strSerachTransType;

      getField(ifds::SearchType,		strSearchType,     idDataGroup, false );
      getField(ifds::AccountNum,		strAccountNum,     idDataGroup, false );
      getField(ifds::TransNum,			strTransNum,       idDataGroup, false );
      getField(ifds::WireOrdNum,		strWireOrdNum,     idDataGroup, false );
      getField(ifds::NSCCControlNumber,	strNSCCControlNumber, idDataGroup, false );
      getField(ifds::NetworkID,			strNetworkID,      idDataGroup, false );
      getField(ifds::ExtTransNum,		strExtTransNum,    idDataGroup, false );
      getField(ifds::SendRefNum,		strSendRefNum,     idDataGroup, false );
      getField(ifds::MasterRefNum,		strMasterRefNum,   idDataGroup, false );
      getField(ifds::PartRefNum,		strPartRefNum,     idDataGroup, false );
      getField(ifds::AccountNum,		strAccountNum,     idDataGroup, false );
      getField(ifds::ExternalIdType,	strExternalIdType, idDataGroup, false );
      getField(ifds::ExternalId,		strExternalId,     idDataGroup, false );
      getField(ifds::ExternalId,		strExternalId,     idDataGroup, false );
      
      if (!strNetworkID.strip().empty() || !strAccountNum.strip().empty() )
      {
         getField(ifds::FromDate,strFromDate,idDataGroup, false);
         getField(ifds::ToDate,  strToDate,  idDataGroup, false);
      }

		if (!strAccountNum.strip().stripLeading('0').empty() && 
			 strSearchType.strip() != FUND_CLASS )   
		{
			strSearchType = NULL_STRING;
		}

		if ( strSearchType.strip() == FUND_CLASS )
		{
			getField(ifds::FundCode, strFundCode,	idDataGroup, false);
			getField(ifds::ClassCode, strClassCode, idDataGroup, false);
			getField(ifds::TradesSearchTransType, strSerachTransType, idDataGroup, false );
			//Pending trade search with Fund/Class and  date combination is irrelavant 
			strFromDate = NULL_STRING;
			strToDate	= NULL_STRING;
		}

		if( pPendingList->initSearch( strSearchType.strip(), 
			                           strAccountNum, 
												strTransNum.strip(), 
												strWireOrdNum.strip(), 
                                    strNetworkID, 
												strExtTransNum.strip(), 
												strSendRefNum.strip(), 
												strMasterRefNum.strip(), 
                                    strPartRefNum.strip(), 
												strFromDate.strip(), 
												strToDate.strip(),
												strExternalIdType.strip(),
												strExternalId.strip(),
												strNSCCControlNumber.strip (),
												I_("N"),
												I_("N"),
												NULL_STRING,
												strFundCode.strip(),
												strClassCode.strip(),
												strSerachTransType.strip()) <= WARNING )
      {
         setObject( pPendingList, PENDING_LIST, OBJ_ACTIVITY_NONE, idDataGroup );
      }
      else
      {
         delete pPendingList;
         pPendingList = NULL;
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************
SEVERITY TradeSearchCriteria::getPendingTradeList( PendingTradeList *&pPendingList, 
                                                   const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getPendingTradeList" ) );

   pPendingList = new PendingTradeList( *this );
   DString strTransNum, strWireOrdNum, strNetworkID, strExtTransNum,strAccountNum, 
           strSendRefNum, strMasterRefNum, strPartRefNum, strFromDate, strToDate, strSearchType,
           strExternalIdType, strExternalId, strNSCCControlNumber;

   getField(ifds::SearchType        , strSearchType         , idDataGroup, false );
   getField(ifds::AccountNum        , strAccountNum         , idDataGroup, false );
   getField(ifds::TransNum          , strTransNum           , idDataGroup, false );
   getField(ifds::WireOrdNum        , strWireOrdNum         , idDataGroup, false );
   getField(ifds::NSCCControlNumber , strNSCCControlNumber  , idDataGroup, false );
   getField(ifds::NetworkID         , strNetworkID          , idDataGroup, false );
   getField(ifds::ExtTransNum       , strExtTransNum        , idDataGroup, false );
   getField(ifds::SendRefNum        , strSendRefNum         , idDataGroup, false );
   getField(ifds::MasterRefNum      , strMasterRefNum       , idDataGroup, false );
   getField(ifds::PartRefNum        , strPartRefNum         , idDataGroup, false );
   getField(ifds::AccountNum        , strAccountNum         , idDataGroup, false );
   getField(ifds::ExternalIdType    , strExternalIdType     , idDataGroup, false );
   getField(ifds::ExternalId        , strExternalId         , idDataGroup, false );
      
   if (!strNetworkID.strip().empty() || !strAccountNum.strip().empty() )
   {
      getField(ifds::FromDate,strFromDate,idDataGroup, false);
      getField(ifds::ToDate,  strToDate,  idDataGroup, false);
   }

   if (!strAccountNum.strip().empty())
   {
      strSearchType = NULL_STRING;
   }

   if( pPendingList->initSearch( strSearchType.strip(), 
                                 strAccountNum, 
                                 strTransNum.strip(), 
                                 strWireOrdNum.strip(), 
                                 strNetworkID, 
                                 strExtTransNum.strip(), 
                                 strSendRefNum.strip(), 
                                 strMasterRefNum.strip(), 
                                 strPartRefNum.strip(), 
                                 strFromDate.strip(), 
                                 strToDate.strip(),
                                 strExternalIdType.strip(),
                                 strExternalId.strip(),
                                 strNSCCControlNumber.strip ()) <= WARNING )
   {
      setObject( pPendingList, PENDING_LIST, OBJ_ACTIVITY_NONE, idDataGroup );
   }
   else
   {
      delete pPendingList;
      pPendingList = NULL;
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************
SEVERITY TradeSearchCriteria::getTransactionList(TransactionList *&pTransactionList, 
   const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getTransactionList" ) );
   //check cbobase to see if we've already built it
   //otherwise, create and store with base
   pTransactionList = dynamic_cast<TransactionList*>(BFCBO::getObject( TRANSACTION_LIST, idDataGroup ) );

   if( !pTransactionList )
   {
      pTransactionList = new TransactionList( *this );

		DString strTransNum, strWireOrdNum, strNetworkID, strExtTransNum, strAccountNum, 
              strSendRefNum, strMasterRefNum, strPartRefNum, strFromDate, strToDate, strSearchType,
				  strExternalIdType, strExternalId, 
				  strAltAccount, strTransType, strUnits, strFundIDType, strFundIDValue,
				  strTradeDate, strFundCode, strClassCode, strNSCCControlNumber;
      
      getField(ifds::SearchType,     strSearchType,     idDataGroup, false );
      getField(ifds::AccountNum,     strAccountNum,     idDataGroup, false );
      getField(ifds::TransNum,       strTransNum,       idDataGroup, false );
      getField(ifds::WireOrdNum,     strWireOrdNum,     idDataGroup, false );
      getField(ifds::NetworkID,      strNetworkID,      idDataGroup, false );
      getField(ifds::ExtTransNum,    strExtTransNum,    idDataGroup, false );
      getField(ifds::SendRefNum,     strSendRefNum,     idDataGroup, false );
      getField(ifds::MasterRefNum,   strMasterRefNum,   idDataGroup, false );
      getField(ifds::PartRefNum,     strPartRefNum,     idDataGroup, false );
      getField(ifds::ExternalIdType, strExternalIdType, idDataGroup, false );
      getField(ifds::ExternalId,     strExternalId,     idDataGroup, false );
      getField(ifds::AltAccount,     strAltAccount,     idDataGroup, false );
      getField(ifds::TradeDate,      strTradeDate,      idDataGroup, false );
      getField(ifds::NSCCControlNumber, strNSCCControlNumber, idDataGroup, false );

      if ((!strNetworkID.strip().empty() || !strAccountNum.strip().empty()) && strSearchType != FUND_CLASS)
      {
         getField(ifds::FromDate,strFromDate,idDataGroup, false);
         getField(ifds::ToDate,  strToDate,  idDataGroup, false);
      }

      if (!strAccountNum.strip().stripLeading('0').empty() && strSearchType != FUND_CLASS)
      {
         strSearchType = NULL_STRING;
      }

      if( !strAltAccount.strip().empty())
      {
         getField(ifds::FundIDType,strFundIDType,idDataGroup, false);
         getField(ifds::FundIDValue,strFundIDValue,idDataGroup, false);
         getField(ifds::TransType,strTransType,idDataGroup, false);
         getField(ifds::FromDate,strFromDate,idDataGroup, false);
         getField(ifds::Units,strUnits,idDataGroup, false);
      }

      if ( !strTradeDate.strip().empty() )
      {
         getField(ifds::FundCode,strFundCode,idDataGroup, false);
         getField(ifds::ClassCode,strClassCode,idDataGroup, false);
      }
	  if ( strSearchType.strip() == FUND_CLASS )
      {
         getField(ifds::FundCode,strFundCode,idDataGroup, false);
         getField(ifds::ClassCode,strClassCode,idDataGroup, false);
		 getField(ifds::TradesSearchTransType,strTransType,idDataGroup, false);
		 getField(ifds::FromDate,strFromDate,idDataGroup, false);
		 getField(ifds::ToDate,  strToDate,  idDataGroup, false);
	  }
      if( pTransactionList->initSearch( strSearchType.strip(),
                                        strAccountNum.strip(), 
                                        strTransNum.strip(), 
                                        strWireOrdNum.strip(), 
                                        strNetworkID, 
                                        strExtTransNum.strip(), 
                                        strSendRefNum.strip(), 
                                        strMasterRefNum.strip(), 
                                        strPartRefNum.strip(), 
                                        strFromDate.strip(), 
                                        strToDate.strip(), 
                                        strExternalIdType.strip(), 
                                        strExternalId.strip(),
                                        strAltAccount.strip(),
                                        strFundIDType.strip(),
                                        strFundIDValue.strip(),
                                        strTransType.strip(),
                                        strUnits.strip(),
                                        strNSCCControlNumber.strip (),
                                        strTradeDate.strip(),
                                        strFundCode.strip(),
                                        strClassCode.strip() ) <= WARNING )
      {
         setObject( pTransactionList, TRANSACTION_LIST, OBJ_ACTIVITY_NONE, idDataGroup );

            if ( strSearchType == TRADE_DATE &&
                !strFundCode.empty()         &&
                !strClassCode.empty() )
         {
            bool bHasData = false;
            BFObjIter iter( *pTransactionList, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );
            while( !iter.end() )
            {
               // We have a record
               bHasData = true;
               break;
            }

            if ( bHasData )
            {
               FundMasterList *pFundMasterList = NULL;
               if ( getMgmtCo ().getFundMasterList (pFundMasterList) <= WARNING &&
                  NULL != pFundMasterList)
               {
                  if ( !pFundMasterList->is3rdPartyFund( strFundCode ) )
                     setFieldNoValidate( ifds::BulkCancelAllowed, I_( "Y" ), idDataGroup );
               }
            }
         }
      }
      else
      {
         delete pTransactionList;
         pTransactionList = NULL;
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

////////////////////////////////VALIDATIONS////////////////////////////////////
//******************************************************************************
SEVERITY TradeSearchCriteria::doValidateField(const BFFieldId& idField, 
   const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );

   //for now, there are no validations for the SWIFT fields (other than NetworkId)
   if( idField == ifds::TransNum )
      validateTransNum(strValue, idDataGroup);
   else if ( idField == ifds::WireOrdNum )
      validateWireOrdNum(strValue, idDataGroup);
   else if( idField == ifds::ToDateContr )
      validateSearchDates(idDataGroup);
   else if( idField == ifds::FundNumber )
      validateFundNumber( idDataGroup, strValue );
   else if( idField == ifds::FundCode || idField == ifds::ClassCode )
      validateFundClassCode(idDataGroup);
   else if( idField == ifds::FundWKN )
      validateFundWKN(idDataGroup, strValue);
   else if( idField == ifds::FundISIN )
      validateFundISIN(idDataGroup, strValue);
   else if (idField == ifds::NSCCControlNumber)
      validateNSCCControlNumber (strValue, idDataGroup);

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY TradeSearchCriteria::validateTransNum(const DString& strValue, 
   const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::BFBASE_CONDITION, CLASSNAME, I_( "validateTransNum" ) );

   //1. an empty value is invalid
   //2. 0 is invalid as well
   //3. it should be all digits
   DString strVal(strValue);
   if (strVal.stripAll().empty() || !strVal.stripAll().isAllDigits() ||
       strVal == I_("0"))
   {
//CP20030319      long lFlags = getFieldStateFlags(ifds::TransNum, idDataGroup);
      if ( isFieldRequired( ifds::TransNum, idDataGroup ) )
      {
         ADDCONDITIONFROMFILE( CND::ERR_FIELD_VALUE_NOT_VALID );
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY TradeSearchCriteria::validateWireOrdNum(const DString& strValue, 
   const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::BFBASE_CONDITION, CLASSNAME, I_( "validateTransNum" ) );

   //1. an empty value is invalid
   //2. 0 is invalid as well
   //3. it should be all digits
   DString strVal(strValue);
   if (strVal.stripAll().empty() || !strVal.stripAll().isAllDigits() ||
       strVal == I_("0"))
   {
//CP20030319      long lFlags = getFieldStateFlags(ifds::WireOrdNum, idDataGroup);
      if ( isFieldRequired( ifds::WireOrdNum, idDataGroup ) )
      {
         ADDCONDITIONFROMFILE( CND::ERR_FIELD_VALUE_NOT_VALID );
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY TradeSearchCriteria::validateNSCCControlNumber(const DString& strValue, const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::BFBASE_CONDITION, CLASSNAME, I_( "validateNSCCControlNumber" ) );
	DString strVal(strValue);

	if (strVal.stripAll().empty())
	{
		if ( isFieldRequired( ifds::NSCCControlNumber, idDataGroup ) )
		{
         ADDCONDITIONFROMFILE( CND::ERR_FIELD_VALUE_NOT_VALID );
		}
	}

	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY TradeSearchCriteria::validateSearchDates(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateSearchDates" ) );

   //1. FromDate must be earlier than ToDate
   //note : a 9999 date translates into an empty string which means the date is NOT specified
   DString strFromDate, strToDate;
   getField(ifds::FromDate, strFromDate, idDataGroup, false);
   getField(ifds::ToDate, strToDate, idDataGroup, false);
   if (!strFromDate.strip().empty() && !strToDate.strip().empty() &&
      DSTCommonFunctions::CompareDates(strFromDate, strToDate) == DSTCommonFunctions::SECOND_EARLIER)
   {
      ADDCONDITIONFROMFILE(CND::ERR_SECOND_DATE_EARLIER);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

////////////////////////////////END VALIDATIONS////////////////////////////////
//******************************************************************************
////////////////////////////////RELATED CHANGES////////////////////////////////

//******************************************************************************
SEVERITY TradeSearchCriteria::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAME2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );

	if( idField == ifds::SearchType )
   {
      setUpdatedFlag(idField, idDataGroup, false);
      DString strSearchType;
      getField(ifds::SearchType, strSearchType, idDataGroup, false);
      clearSearchFields(idDataGroup);
      if (strSearchType.strip() == NETWORK || strSearchType.strip() == ACCOUNTNUM || strSearchType.strip() == TRADE_DATE || strSearchType.strip() == FUND_CLASS )
         reInitDates(strSearchType,idDataGroup);
      else
         clearDateFields(idDataGroup);
       clearRequiredFlags(idDataGroup);
       if( ALL_TRADES == strSearchType )
          return(GETCURRENTHIGHESTSEVERITY());//no fields are required for all trades
       setFieldRequired(BFFieldId::getId(strSearchType), idDataGroup, true);
       setValidFlag(BFFieldId::getId(strSearchType), idDataGroup, false);
		  if ( strSearchType == EXTERNAL_ID )
		  {
			setFieldRequired( ifds::ExternalId, idDataGroup, true );
			setValidFlag( ifds::ExternalId, idDataGroup, false );
		  }
          else
			setFieldRequired( ifds::ExternalId, idDataGroup, false );	
		bool bReq = ( strSearchType.strip() == TRADE_DATE || strSearchType.strip() == FUND_CLASS);

		setFieldRequired( ifds::FundCode, idDataGroup, bReq );
		setValidFlag( ifds::FundCode, idDataGroup, !bReq );

		setFieldRequired( ifds::ClassCode, idDataGroup, bReq);
		setValidFlag( ifds::ClassCode, idDataGroup, !bReq );

		setFieldRequired( ifds::TradeDate, idDataGroup, ( strSearchType.strip() == TRADE_DATE ) );
		setValidFlag( ifds::TradeDate, idDataGroup, !( strSearchType.strip() == TRADE_DATE ) );

		if( bReq )
		{
			setFieldNoValidate(ifds::FundCode, I_(""), idDataGroup, true, true, true);
			setFieldNoValidate(ifds::ClassCode, I_(""), idDataGroup, true, true, true);
			setFieldNoValidate(ifds::FundNumber, I_(""), idDataGroup, true, true, true);
			setFieldNoValidate(ifds::FundWKN, I_(""), idDataGroup, true, true, true);
			setFieldNoValidate(ifds::FundISIN, I_(""), idDataGroup, true, true, true);
		}
		bool bFundClassSrh = strSearchType.strip() == FUND_CLASS;

		if( bFundClassSrh )
		{
			setFieldRequired( ifds::AccountNum, idDataGroup, !bFundClassSrh );
			setValidFlag( ifds::AccountNum, idDataGroup, bFundClassSrh );

			setFieldRequired( ifds::TradesSearchTransType, idDataGroup, !bFundClassSrh );
			setValidFlag( ifds::TradesSearchTransType, idDataGroup, bFundClassSrh );

			setFieldRequired( ifds::FromDate, idDataGroup, !bFundClassSrh );
			setValidFlag( ifds::FromDate, idDataGroup, bFundClassSrh );

			setFieldRequired( ifds::ToDate, idDataGroup, !bFundClassSrh );
			setValidFlag( ifds::ToDate, idDataGroup, bFundClassSrh );

			setFieldNoValidate(ifds::TradesSearchTransType, I_("ALL"), idDataGroup, true, true, true);
		}

        notifyObservers( idField, idDataGroup, FIELD_NOTIFICATIONS, E_EVENT_VALUE_CHANGE, I_( "" ));
   }
	else if( idField == ifds::Pending )
	{
      DString strSearchType, isPending;
      getField(ifds::SearchType, strSearchType, idDataGroup, false);
      getField(ifds::Pending, isPending, idDataGroup, false);
		if ( strSearchType.strip() == ACCOUNTNUM && isPending == YES )
		{
			DString dstrFromDate(I_("01/01/1900"));
			setFieldNoValidate(ifds::FromDate, dstrFromDate, idDataGroup, true, true, true);
		}
		else
		{
			DString dstrFromDate(NULL_STRING);
			setFieldNoValidate(ifds::FromDate, dstrFromDate, idDataGroup, false, true, true);
		}
		loadSearchTypeSubstList( idDataGroup );
	}
	else if( idField == ifds::FundNumber )
	{
		DString dstrFundNumber ;
      getField(ifds::FundNumber, dstrFundNumber, idDataGroup, false);
		setFundByFundNumber(	idDataGroup, dstrFundNumber );
	}
	else if( idField == ifds::FundCode || idField == ifds::ClassCode )
	{
		DString dstrFundCode, dstrClassCode;
      getField(ifds::FundCode, dstrFundCode, idDataGroup, false);
		getField(ifds::ClassCode, dstrClassCode, idDataGroup, false);
		setFundbyFundClass( idDataGroup, dstrFundCode, dstrClassCode );
	}
	else if( idField == ifds::FundWKN )
	{
		DString dstrFundWKN ;
      getField(ifds::FundWKN, dstrFundWKN, idDataGroup, false);
		setFundByWKN(	idDataGroup, dstrFundWKN );
	}
	else if( idField == ifds::FundISIN )
	{
		DString dstrFundISIN ;
      getField(ifds::FundISIN, dstrFundISIN, idDataGroup, false);
		setFundByISIN(	idDataGroup, dstrFundISIN );
	}

   setFieldUpdated (idField, idDataGroup, false);// should we do something like this?
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
////////////////////////////////END RELATED CHANGES////////////////////////////////
//******************************************************************************
void TradeSearchCriteria::clearRequiredFlags(const BFDataGroupId& idDataGroup)
{
   for( int i=0; i<numCriteriaFields; ++i )
      setFieldRequired(criteriaFields[i], idDataGroup, false);
}

//******************************************************************************
SEVERITY TradeSearchCriteria::loadSearchTypeSubstList( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "loadDepRedCodeSubstList" ) );

   if (isSWIFT())
	{
		setSearchTypeSubstSet( ifds::SWIFTTradeSearch, idDataGroup );        
	}
   else
	{
		setSearchTypeSubstSet( ifds::TradeSearch, idDataGroup );        
	}

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool TradeSearchCriteria::isValidForInquiry(const BFDataGroupId& idDataGroup)
{
   SEVERITY sev = NO_SEVERITY, sevMax = NO_SEVERITY;

   //validate first
   validateAll(idDataGroup);
	//fields
   sev = getErrorState(ifds::SearchType, idDataGroup);
	if (sev > sevMax) sevMax = sev;

	sev = getErrorState(ifds::FromDate, idDataGroup);
	if (sev > sevMax) sevMax = sev;

	sev = getErrorState(ifds::ToDate, idDataGroup);
	if (sev > sevMax) sevMax = sev;

   for( int i=0; i<numCriteriaFields; ++i )
   {
      sev = getErrorState(criteriaFields[i], idDataGroup);
	   if (sev > sevMax) sevMax = sev;
   }

  //in addition, the criteria should be entered
	return (sevMax<=WARNING && isCriteriaEntered(idDataGroup));
}

//******************************************************************************
bool TradeSearchCriteria::isSWIFT()
{
	DString strSWIFT;
   getWorkSession().getOption( ifds::NetworkOrder, strSWIFT, BF::HOST, false);
	if (strSWIFT.strip() == YES)
		return true;

	return false;
}

//******************************************************************************
void TradeSearchCriteria::clearSearchFields(const BFDataGroupId& idDataGroup)
{
   setFieldNoValidate(ifds::TransNum, I_("0"), idDataGroup, false);
   for( int i=1; i<numCriteriaFields; ++i )
      setFieldNoValidate(criteriaFields[i], NULL_STRING, idDataGroup, false);
}

//******************************************************************************
bool TradeSearchCriteria::isCriteriaEntered(const BFDataGroupId& idDataGroup)
{
   //1. search type has to be specified (however, not by the user)
   DString strSearchType;
   getField(ifds::SearchType, strSearchType, idDataGroup, false);
   assert( !strSearchType.strip().empty() );
   if( ALL_TRADES == strSearchType )
       return true;//All trades dont need any other criteria
   //2. at least one criteria field should not be empty
   DString strTemp;
   for( int i=0; i<numCriteriaFields; ++i )
   {
      getField(criteriaFields[i], strTemp, idDataGroup, false);
      if (!strTemp.strip().empty())
      {
         if (i==0 || i==1)
         {
            if (strTemp!=I_("0"))//TransNum and WireOrdNum cannot be zero
               return true;
         }
         else
            return true;
      }
   }
   return false;
}

//******************************************************************************
void TradeSearchCriteria::reInitDates(const DString& strSearchType,const BFDataGroupId& idDataGroup)
{
	if( strSearchType == ACCOUNTNUM )
	{
		DString dstrCurrBusDate = getCurrentBusDate();
		setFieldNoValidate(ifds::ToDate, dstrCurrBusDate, idDataGroup, false, true, true);

		DString isPending;
		getField(ifds::Pending, isPending, idDataGroup, false);
		if( isPending == YES )
		{
			DString dstrFromDate(I_("01/01/1900"));
			setFieldNoValidate(ifds::FromDate, dstrFromDate, idDataGroup, true, true, true);
		}
		else
		{
			DString dstrFromDate(NULL_STRING);
			setFieldNoValidate(ifds::FromDate, dstrFromDate, idDataGroup, false, true, true);
		}
	}
	else if ( strSearchType == TRADE_DATE )
	{
		DString dstrCurrBusDate = getCurrentBusDate();
		setFieldNoValidate(ifds::TradeDate, dstrCurrBusDate, idDataGroup, false, true, true);	
	}
	else if ( strSearchType == FUND_CLASS )
	{
		DString dstrCurrBusDate = getCurrentBusDate();
		setFieldNoValidate(ifds::FromDate, dstrCurrBusDate, idDataGroup, false, true, true);	
		setFieldNoValidate(ifds::ToDate, dstrCurrBusDate, idDataGroup, false, true, true);	
	}
	else
	{
		DString dstrCurrBusDate = getCurrentBusDate();
		setFieldNoValidate(ifds::FromDate, dstrCurrBusDate, idDataGroup, false, true, true);
		setFieldNoValidate(ifds::ToDate, dstrCurrBusDate, idDataGroup, false, true, true);
	}
}

//******************************************************************************
void TradeSearchCriteria::clearDateFields(const BFDataGroupId& idDataGroup)
{
   setFieldNoValidate(ifds::FromDate, NULL_STRING, idDataGroup, false);
   setFieldNoValidate(ifds::ToDate,   NULL_STRING, idDataGroup, false);
}

//******************************************************************************
DString TradeSearchCriteria::getCurrentBusDate()
{
   MgmtCoOptions *pMgmtCoOptions = NULL;
	getMgmtCo().getMgmtCoOptions( pMgmtCoOptions );
   DString dstrCurrBusDate(NULL_STRING);
   if( pMgmtCoOptions )
      pMgmtCoOptions->getField( ifds::CurrBusDate, dstrCurrBusDate, BF::HOST, false );
   return dstrCurrBusDate.strip();
}

//******************************************************************************
SEVERITY TradeSearchCriteria::setField( const BFFieldId& fieldId,
                              const DString& strValue,
                              const BFDataGroupId& idDataGroup, 
                              bool  lFormatted,
                              bool  lSideEffect,
                              bool  bCheckCurrentValue)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setField" ) );

   //DSTDateTime does some fancy things with a 9999 date; therefore, translate a 9999 date 
   //into a NULL_STRING, which means the date is NOT specified
   
   DString strFancyDate(strValue);
   if (fieldId == ifds::FromDate || fieldId == ifds::ToDate)
   {
      if (strFancyDate.find( I_("9999") ) != DString::npos)//9999 is part of the date
         strFancyDate = NULL_STRING;
   }
   BFCBO::setField(fieldId, strFancyDate, idDataGroup, lFormatted, lSideEffect, bCheckCurrentValue);  

   return(GETCURRENTHIGHESTSEVERITY());

}

//******************************************************************************
SEVERITY TradeSearchCriteria::validateFundNumber( const BFDataGroupId &idDataGroup, const DString &dstrFundNumber)

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFundNumber" ) );

	FundDetailList *pFundDetailList;

   getMgmtCo().getFundDetailList( pFundDetailList );
	if ( pFundDetailList )
	{
		if ( pFundDetailList->getFundDetailByFundNumber( dstrFundNumber ) == NULL )
		{
			 //ADDCONDITIONFROMFILE(CND::WARN_INVALID_FUND);
		}

	}
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY TradeSearchCriteria::validateFundClassCode ( const BFDataGroupId  &idDataGroup )

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFundClassCode" ) );

   DString dstrFundCode, dstrClassCode;
	getField(ifds::FundCode,dstrFundCode,idDataGroup, false);
	getField(ifds::ClassCode,dstrClassCode,idDataGroup, false);

	if ( dstrFundCode != NULL_STRING && dstrClassCode != NULL_STRING )
	{
		FundDetail *pFundDetail;
		if ( ! getWorkSession().getFundDetail( dstrFundCode, dstrClassCode, idDataGroup, pFundDetail ) )
		{
			ADDCONDITIONFROMFILE(CND::ERR_INVALID_FUND_CLASS_CODES);
		}
	}
	else if ( dstrFundCode == NULL_STRING && dstrClassCode == NULL_STRING )
	{
		ADDCONDITIONFROMFILE(CND::ERR_INVALID_FUND_CLASS_CODES);
	}

   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
SEVERITY TradeSearchCriteria::validateFundWKN( const BFDataGroupId &idDataGroup,const DString &dstrFundWKN )

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFundWKN" ) );

   FundDetailList *pFundDetailList;
   getMgmtCo().getFundDetailList( pFundDetailList );
	if ( pFundDetailList )
	{
		if ( pFundDetailList->getFundDetailByWKN( dstrFundWKN ) == NULL )
		{
			 ADDCONDITIONFROMFILE(CND::ERR_INVALID_FUND_WKN);
		}

	}
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY TradeSearchCriteria::validateFundISIN( const BFDataGroupId &idDataGroup,const DString &dstrFundISIN)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFundISIN" ) );

   FundDetailList *pFundDetailList;
   getMgmtCo().getFundDetailList( pFundDetailList );
	if ( pFundDetailList )
	{
		if ( pFundDetailList->getFundDetailByISIN( dstrFundISIN ) == NULL )
		{
			 ADDCONDITIONFROMFILE(CND::ERR_INVALID_FUND_ISIN);
		}

	}
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY TradeSearchCriteria::setFundByFundNumber(const BFDataGroupId &idDataGroup, const DString &dstrFundNumber)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setFundByFundNumber" ) );

   FundDetailList *pFundDetailList;

   getMgmtCo().getFundDetailList( pFundDetailList );
	if ( pFundDetailList )
	{
		FundDetail* pFundDetail = NULL;
		pFundDetail = pFundDetailList->getFundDetailByFundNumber( dstrFundNumber );
		if ( pFundDetail )
		{
			DString dstrFundCode, dstrClassCode, dstrFundName, dstrWKN, dstrISIN;

			pFundDetail->getField(ifds::FundCode, dstrFundCode, idDataGroup, false);
			setField(ifds::FundCode, dstrFundCode, idDataGroup, false);

			pFundDetail->getField(ifds::ClassCode, dstrClassCode, idDataGroup, false);
			setField(ifds::ClassCode, dstrClassCode, idDataGroup, false);

			pFundDetail->getField(ifds::FundWKN, dstrWKN, idDataGroup, false);
			setField(ifds::FundWKN, dstrWKN, idDataGroup, false);

			pFundDetail->getField(ifds::FundISIN, dstrISIN, idDataGroup, false);
			setField(ifds::FundISIN, dstrISIN, idDataGroup, false);

			getWorkSession().getFundName( dstrFundCode, dstrFundName );
			setField(ifds::FundName, dstrFundName, idDataGroup, false);
		}
	}
	
	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY TradeSearchCriteria::setFundbyFundClass(const BFDataGroupId &idDataGroup, const DString &dstrFundCode, const DString &dstrClassCode)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setFundbyFundClass" ) );

   if( dstrFundCode != NULL_STRING && dstrClassCode != NULL_STRING )
	{
		FundDetail* pFundDetail = NULL;
	   getWorkSession().getFundDetail( dstrFundCode, dstrClassCode, idDataGroup, pFundDetail );
		if ( pFundDetail )
		{
			DString dstrFundNumber, dstrFundName, dstrWKN, dstrISIN;

			pFundDetail->getField(ifds::FundWKN, dstrWKN, idDataGroup, false);
			setField(ifds::FundWKN, dstrWKN, idDataGroup, false);

			pFundDetail->getField(ifds::FundISIN, dstrISIN, idDataGroup, false);
			setField(ifds::FundISIN, dstrISIN, idDataGroup, false);

			getWorkSession().getFundName( dstrFundCode, dstrFundName );
			setField(ifds::FundName, dstrFundName, idDataGroup, false);

			getWorkSession().GetFundNumber( dstrFundCode, dstrClassCode, dstrFundNumber );
			setField(ifds::FundNumber, dstrFundNumber, idDataGroup, false);
		}
	}
	
	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY TradeSearchCriteria::setFundByWKN(const BFDataGroupId &idDataGroup, const DString &dstrFundWKN)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setFundByWKN" ) );

   FundDetailList *pFundDetailList;

   getMgmtCo().getFundDetailList( pFundDetailList );
	if ( pFundDetailList )
	{
		FundDetail* pFundDetail = NULL;
		pFundDetail = pFundDetailList->getFundDetailByWKN( dstrFundWKN );

		if ( pFundDetail )
		{
			DString dstrFundCode, dstrClassCode, dstrFundNumber, dstrFundName, dstrISIN;
		
			pFundDetail->getField(ifds::FundCode, dstrFundCode, idDataGroup, false);
			setField(ifds::FundCode, dstrFundCode, idDataGroup, false);

			pFundDetail->getField(ifds::ClassCode, dstrClassCode, idDataGroup, false);
			setField(ifds::ClassCode, dstrClassCode, idDataGroup, false);

			pFundDetail->getField(ifds::FundISIN, dstrISIN, idDataGroup, false);
			setField(ifds::FundISIN, dstrISIN, idDataGroup, false);

			getWorkSession().getFundName( dstrFundCode, dstrFundName );
			setField(ifds::FundName, dstrFundName, idDataGroup, false);

			getWorkSession().GetFundNumber( dstrFundCode, dstrClassCode, dstrFundNumber );
			setField(ifds::FundNumber, dstrFundNumber, idDataGroup, false);
		}
	}
	
	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY TradeSearchCriteria::setFundByISIN(const BFDataGroupId &idDataGroup, const DString &dstrFundISIN)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setFundByISIN" ) );

   FundDetailList *pFundDetailList;

   getMgmtCo().getFundDetailList( pFundDetailList );
	if ( pFundDetailList )
	{
		FundDetail* pFundDetail = NULL;
		pFundDetail = pFundDetailList->getFundDetailByISIN( dstrFundISIN );

		if ( pFundDetail )
		{
			DString dstrFundCode, dstrClassCode, dstrFundNumber, dstrFundName, dstrWKN;
		
			pFundDetail->getField(ifds::FundCode, dstrFundCode, idDataGroup, false);
			setField(ifds::FundCode, dstrFundCode, idDataGroup, false);

			pFundDetail->getField(ifds::ClassCode, dstrClassCode, idDataGroup, false);
			setField(ifds::ClassCode, dstrClassCode, idDataGroup, false);

			pFundDetail->getField(ifds::FundWKN, dstrWKN, idDataGroup, false);
			setField(ifds::FundWKN, dstrWKN, idDataGroup, false);

			getWorkSession().getFundName( dstrFundCode, dstrFundName );
			setField(ifds::FundName, dstrFundName, idDataGroup, false);

			getWorkSession().GetFundNumber( dstrFundCode, dstrClassCode, dstrFundNumber );
			setField(ifds::FundNumber, dstrFundNumber, idDataGroup, false);
		}
	}
	
	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY TradeSearchCriteria::setSearchTypeSubstSet(const BFFieldId& idField, const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setSearchTypeSubstSet" ) );

    bool bSubstitutionChanged = false;

	DString dstrIsPending, dstrSubst;
	BFProperties *pUseBFProperties = getFieldProperties ( idField, idDataGroup );
	pUseBFProperties->getAllSubstituteValues ( dstrSubst );
	
	DString dstrNSCCCompliant;
	getWorkSession().getOption( ifds::NSCCCompliant, dstrNSCCCompliant, idDataGroup, false );

	if (dstrNSCCCompliant == I_("N") )
		dstrSubst = removeItemFromSubtList ( dstrSubst, I_("NSCCControlNumber"));
  		
   // Remove Alt.Account Search type from both Pending Trade and Transaction History.
   if (idField == ifds::SWIFTTradeSearch)
      dstrSubst = removeItemFromSubtList(dstrSubst, I_("AltAccount"));
   
	//Removing Fund sponsor code and Trading Platform for Pending Trade and Transaction history 
	dstrSubst = removeItemFromSubtList(dstrSubst, I_("SponsorCode"));
	dstrSubst = removeItemFromSubtList(dstrSubst, I_("Platform"));
  
	getField(ifds::Pending, dstrIsPending, idDataGroup, false);
	if( dstrIsPending == YES )
	{
		DString dstrSearchType;
		getField(ifds::SearchType, dstrSearchType, idDataGroup, false);

		if ( dstrSubst.find( I_("TradeDate") ) != DString::npos )
		{
	  		dstrSubst = removeItemFromSubtList ( dstrSubst, I_("TradeDate") );		
			bSubstitutionChanged = true;
		}
        //remove the transtype due to the control re allignment required for the screen..Can be used once the control is alligned.
        dstrSubst = removeItemFromSubtList(dstrSubst, I_("TransType"));
		//if ( dstrSubst.find( I_("FundCode") ) != DString::npos )
		//{
		// 		dstrSubst = removeItemFromSubtList ( dstrSubst, I_("FundCode") );		
		//	bSubstitutionChanged = true;
		//}
		if ( dstrSearchType == TRADE_DATE || dstrSearchType == FUND_CLASS )
			setFieldNoValidate(ifds::SearchType, TRANSNUM, idDataGroup, false );
	}
	else
	{
		if ( dstrSubst.find( I_("TradeDate") ) == DString::npos )
		{
			dstrSubst = dstrSubst + I_("TradeDate=Trade Date") ;  			
		}
		if ( dstrSubst.find( I_("FundCode") ) == DString::npos )
		{
			dstrSubst = dstrSubst + I_("FundCode=Fund Class") ;  			
		}
        // Dont give serach using All tardes and UserID in historical serach as this will try to pull out a lot of data and can lead 
        // to timeout error.
        dstrSubst = removeItemFromSubtList(dstrSubst, I_("All"));
        dstrSubst = removeItemFromSubtList(dstrSubst, I_("SearchUserID"));
        //remove the transtype due to the control re allignment required for the screen..Can be used once the control is alligned.
        dstrSubst = removeItemFromSubtList(dstrSubst, I_("TransType"));
		bSubstitutionChanged = true;
	}		

	if ( bSubstitutionChanged )
	{
		setFieldAllSubstituteValues ( ifds::SearchType, idDataGroup, dstrSubst );  
		BFProperties *pBFProperties = getFieldProperties ( ifds::SearchType, idDataGroup );
		pBFProperties->setSubstituteValues( NULL );
		notifyObservers( ifds::SearchType, idDataGroup, FIELD_NOTIFICATIONS, E_EVENT_PROPERTY_CHANGE, I_( "" ));
	}
	
	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TradeSearchCriteria.cpp-arc  $
// 
//    Rev 1.27   Jan 16 2012 13:53:42   wp040027
// P0188394_Performance Fees - Trade Search
// 
//    Rev 1.26   Jun 16 2009 15:29:24   wutipong
// IN1707791 - remove 'AtlAccount' search type from trade search dialog.
// 
//    Rev 1.25   Mar 04 2009 23:50:56   dchatcha
// IN 1395049 - Not returning all the pending trades, introduced 'More' button for pending trade part of Aggregated order screen.
// 
//    Rev 1.24   Feb 02 2009 14:37:42   daechach
// IN 1395049 - Not returning all the pending trades
// 
//    Rev 1.23   Mar 02 2006 16:27:46   jankovii
// PET 2072 FN01- NSCC Control Number.
// 
//    Rev 1.22   Nov 30 2005 15:40:34   porteanm
// PET 1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.21   Nov 26 2005 16:43:48   porteanm
// PET 1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.20   Nov 12 2005 16:42:14   porteanm
// PET 1286 FN01 - Bulk Cancellation - don't break AggregateOrder!
// 
//    Rev 1.19   Nov 12 2005 15:21:22   porteanm
// PET 1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.18   Nov 12 2005 13:45:52   porteanm
// PET 1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.17   Nov 10 2005 17:22:38   porteanm
// PET 1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.16   Nov 10 2005 15:21:10   porteanm
// PET 1286 FN01 - Bulk Cancellation.
// 
//    Rev 1.15   Nov 08 2005 16:33:46   porteanm
// PET 1286  FN01 -- TradeDate search for a processed transaction.
// 
//    Rev 1.14   Nov 04 2005 10:51:38   ZHANGCEL
// PET 1286  FN01 -- Add TradeDate search related issue.
// 
//    Rev 1.13   Feb 03 2005 13:38:26   Fengyong
// PET1117 FN66 - Trade reconcile API
// 
//    Rev 1.12   Dec 09 2004 19:39:40   popescu
// PET 1117/06, set the updated flag for all fields to false
// 
//    Rev 1.11   Dec 09 2004 18:42:54   popescu
// PET 1117/56 fixed trxn builder issue
// 
//    Rev 1.10   Dec 09 2004 18:00:56   zhangcel
// PET1117 FN 08 -- Added a function -- getPendingTradList
// 
//    Rev 1.9   Nov 14 2004 14:58:04   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.8   Sep 07 2004 15:54:34   VADEANUM
// PET 1094 FN4 - Activest Bank File Interface.
// 
//    Rev 1.7   May 25 2004 18:03:18   ZHANGCEL
// PET1046_FN02 -- Set Trade Date to the Current business Date
// 
//    Rev 1.6   May 11 2004 11:31:28   ZHANGCEL
// PET1046_FN02 -- Trade Search by account enhancement
// 
//    Rev 1.5   May 27 2003 18:30:10   popescu
// due to several memory leaks found in some list getters at the DSTCWorkSession level caused by copy/paste, I've created a common template function to retrieve the dependent objects
// 
//    Rev 1.4   Mar 21 2003 18:27:24   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.3   Mar 13 2003 15:59:46   HERNANDO
// Change for Robert.  Removed line which was used for testing purposes.
// 
//    Rev 1.2   Mar 07 2003 15:53:10   KOVACSRO
// fixed WireOrderNumber validation
// 
//    Rev 1.1   Mar 04 2003 17:16:46   KOVACSRO
// some fixes during unit testing.
// 
//    Rev 1.0   Mar 03 2003 09:51:40   KOVACSRO
// Initial revision.
 
*/


