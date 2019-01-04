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
// ^FILE   : TradeVerificationSearch.cpp
// ^AUTHOR : Robbins Kuriakose
// ^DATE   : JuLY 22 2014
//
//********************************************************************************
#include "stdafx.h"
#include "pendingtradelist.hpp"
#include "TradeVerificationList.hpp"
#include "TradeVerificationSearch.hpp"
#include "FundDetailList.hpp"
#include "FundDetail.hpp"
#include "fundmaster.hpp"
#include "fundmasterlist.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "dstcworksession.hpp"
#include <ifastdataimpl\dse_dstc0053_req.hpp>
namespace  
{
   const I_CHAR * const CLASSNAME        = I_( "TradeVerificationSearch" );
   const I_CHAR * const YES              = I_( "Y" );
   const I_CHAR * const NO               = I_( "N" );
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
   const I_CHAR * const TRADE_VERIFCICATION_LIST = I_( "TradeVerificationList" );
   const I_CHAR * const ALL_TRADES         = I_( "All" );
   const I_CHAR * const ALL_TRANS_TYPE     = I_( "ALL" );
   const I_CHAR * const TRANSTYPE         = I_( "TransType" );
   const I_CHAR * const SPONSORCODE       = I_( "SponsorCode" );
   const I_CHAR * const PLATFORM          = I_( "Platform" );
}
namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId SWIFTTradeSearch;
   extern CLASS_IMPORT const BFTextFieldId TradeSearch;
   extern CLASS_IMPORT const BFTextFieldId NetworkOrder;
   extern CLASS_IMPORT const BFTextFieldId AltAccount;
   extern CLASS_IMPORT const BFTextFieldId FundIDType;
   extern CLASS_IMPORT const BFTextFieldId FundIDValue;
   extern CLASS_IMPORT const BFTextFieldId TransType;   
   extern CLASS_IMPORT const BFDecimalFieldId Units;
   extern CLASS_IMPORT const BFTextFieldId FundISIN; 
   extern CLASS_IMPORT const BFTextFieldId FundWKN;
   extern CLASS_IMPORT const BFTextFieldId FundNumber;
   extern CLASS_IMPORT const BFTextFieldId FundName;  
   extern CLASS_IMPORT const BFTextFieldId NSCCCompliant;
   extern CLASS_IMPORT const BFTextFieldId TradesSearchTransType;
   extern CLASS_IMPORT const BFDateFieldId TradeDate;
   extern CLASS_IMPORT const BFTextFieldId ValidNetworkType;
   extern CLASS_IMPORT const BFTextFieldId SponsorCode;
   extern CLASS_IMPORT const BFTextFieldId Platform;
}
namespace  CND
{
   extern CLASS_IMPORT const I_CHAR *BFBASE_CONDITION;
   extern CLASS_IMPORT const long ERR_FIELD_VALUE_NOT_VALID;
   extern const long WARN_INVALID_FUND_NUMBER;
   extern const long ERR_INVALID_FUND_CLASS_CODES;
   extern const long ERR_INVALID_FUND_WKN;
   extern const long ERR_INVALID_FUND_ISIN;
}
//
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
   ifds::NSCCControlNumber,
   ifds::FundCode,
   ifds::SearchUserID,
   ifds::TradesSearchTransType,
   ifds::SponsorCode,
   ifds::Platform,
};
static const int numCriteriaFields = sizeof( criteriaFields ) / sizeof( BFFieldId );

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//   Field DD Id,           State Flags,                    Group Flags 
   { ifds::TransNum,		    BFCBO::NONE,                    0 }, 
   { ifds::WireOrdNum,		    BFCBO::NONE,                    0 }, 
   { ifds::NetworkID,		    BFCBO::NONE,                    0 }, 
   { ifds::ExtTransNum,		    BFCBO::NONE,                    0 }, 
   { ifds::SendRefNum,		    BFCBO::NONE,                    0 }, 
   { ifds::PartRefNum,		    BFCBO::NONE,                    0 }, 
   { ifds::MasterRefNum,	    BFCBO::NONE,                    0 }, 
   { ifds::SearchType,		    BFCBO::NONE,                    0 }, 
   { ifds::AccountNum,		    BFCBO::NONE,                    0 },
   { ifds::ExternalIdType,	    BFCBO::CALCULATED_FIELD,        0 },
   { ifds::ExternalId,		    BFCBO::CALCULATED_FIELD,        0 },
   { ifds::NSCCControlNumber,   BFCBO::NONE,                    0 }, 
   { ifds::TradesSearchTransType,BFCBO::NONE,                   0 },
   { ifds::AltAccount,          BFCBO::NONE,                    0 },
   { ifds::FundIDValue,         BFCBO::NONE,                    0 },
   { ifds::FundIDType,          BFCBO::NONE,                    0 },
   { ifds::TransType,           BFCBO::NONE,                    0 },
   { ifds::Units,			    BFCBO::NONE,				    0 },
   { ifds::TradeDate,	        BFCBO::NONE,		  		    0 },
   { ifds::FundCode,		    BFCBO::NONE,				    0 },
   { ifds::ClassCode,		    BFCBO::NONE,				    0 },
   { ifds::FundISIN,		    BFCBO::NONE,				    0 },
   { ifds::FundWKN,			    BFCBO::NONE,				    0 },
   { ifds::FundNumber,		    BFCBO::NONE,				    0 },
   { ifds::FundName,		    BFCBO::NONE,				    0 },
   { ifds::SearchUserID,	    BFCBO::NONE,				    0 },
   { ifds::ExcludeAggrOrd,      BFCBO::NONE,				    0 }, 
   { ifds::SponsorCode,         BFCBO::NONE,                    0 },
   { ifds::Platform,            BFCBO::NONE,                    0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );
const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = {
   //  Object Label,                  State Flags,      Group Flags 
   { I_( "TradeVerificationList" ),   BFCBO::NONE,      0},    
};
static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );

//****************************************************************************
TradeVerificationSearch::TradeVerificationSearch( BFAbstractCBO &parent ):
                         MFCanBFCbo( parent ),_pTradeVerificationList(NULL) 
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );

   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       NUM_OBJECTS, 
					   (const CLASS_OBJECT_INFO *)&classObjectInfo );

}

//****************************************************************************
TradeVerificationSearch::~TradeVerificationSearch()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}   

//****************************************************************************

SEVERITY TradeVerificationSearch::init(const BFDataGroupId& idDataGroup /*=BF::HOST*/,
                                       const DString& dstrTrack /*= I_("N")*/, 
									   const DString& dstrPageName /*= NULL_STRING*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   doInitWithDefaultValues(idDataGroup);
   setObjectNew();
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

void TradeVerificationSearch::doInitWithDefaultValues(const BFDataGroupId& idDataGroup)
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doInitWithDefaultValues" ) );
    //rules for default values:
	//1. FromDate is current business date
	//2. ToDate is current business date
	//3. All the other text fields are empty
	//4. All the other integer fields are zero
    //5. Default search for is Pending
    //6. Default search type using is Transaction number
	//set SearchType code substitution set
   loadSearchTypeSubstList(idDataGroup);
   loadTransTypeSubstList(idDataGroup);
   loadPlatformSetSubstList(idDataGroup);
   // clearRequiredFlags(idDataGroup);
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
   setFieldNoValidate(ifds::TradesSearchTransType,  ALL_TRANS_TYPE, idDataGroup, false, true, true,  false);
   setFieldNoValidate(ifds::SearchType,       ALL_TRADES,  idDataGroup, false, true, true,  false);
   setFieldNoValidate(ifds::ExcludeAggrOrd, YES, idDataGroup, false, true, true, false); 
   setFieldNoValidate(ifds::SponsorCode,      NULL_STRING, idDataGroup, false, true, true, false);
   setFieldNoValidate(ifds::Platform,         NULL_STRING, idDataGroup, false, true, true, false);
   loadNetworkIDValues(idDataGroup);
}

//****************************************************************************
SEVERITY TradeVerificationSearch::getTradeVerificationList( TradeVerificationList *&pTradeVerificationList, const BFDataGroupId& idDataGroup, bool bCreate )                                  
{
    MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getPendingList" ) );
    //check cbobase to see if we've already built it
    //otherwise, create and store with base
    if( ! bCreate && _pTradeVerificationList)
    {
      pTradeVerificationList = _pTradeVerificationList;
      return(GETCURRENTHIGHESTSEVERITY());
    }
    _pTradeVerificationList  = NULL;     
    //buildKey( dstrKey,idDataGroup, 0 );
    setObject( NULL, TRADE_VERIFCICATION_LIST, OBJ_ACTIVITY_NONE, BF::HOST );     
    pTradeVerificationList = new TradeVerificationList( *this );
    DString strTransNum, strWireOrdNum, strNetworkID, strExtTransNum,strAccountNum, 
            strSendRefNum, strMasterRefNum, strPartRefNum, strFromDate, strToDate, strSearchType,
            strExternalIdType, strExternalId, strNSCCControlNumber, strFundCode, strClassCode, strSerachTransType,
            dstrExcludeVerifiedTrades, dstrUserId, dstrTransType, dstrExcludeAggrOrd, dstrSponsorCode, dstrPlatform,dstrPriceType;
    getField(ifds::SearchType,		strSearchType,     idDataGroup, false );
    getField(ifds::AccountNum,		strAccountNum,     idDataGroup, false );
    getField(ifds::TransNum,		strTransNum,       idDataGroup, false );
    getField(ifds::WireOrdNum,		strWireOrdNum,     idDataGroup, false );
    getField(ifds::NetworkID,		strNetworkID,      idDataGroup, false );
    getField(ifds::ExtTransNum,		strExtTransNum,    idDataGroup, false );
    getField(ifds::SendRefNum,		strSendRefNum,     idDataGroup, false );
    getField(ifds::MasterRefNum,	strMasterRefNum,   idDataGroup, false );
    getField(ifds::PartRefNum,		strPartRefNum,     idDataGroup, false );
    getField(ifds::AccountNum,		strAccountNum,     idDataGroup, false );
    getField(ifds::ExternalIdType,	strExternalIdType, idDataGroup, false );
    getField(ifds::ExternalId,		strExternalId,     idDataGroup, false );
    getField(ifds::TransType,       dstrTransType,     idDataGroup, false );
    getField(ifds::SearchUserID,    dstrUserId,        idDataGroup, false );
    getField(ifds::TradesSearchTransType,  strSerachTransType, idDataGroup, false);
    getField(ifds::ExcludeAggrOrd, dstrExcludeAggrOrd, idDataGroup, false);
	getField(ifds::SponsorCode,     dstrSponsorCode,   idDataGroup, false );
	getField(ifds::Platform,        dstrPlatform,      idDataGroup, false );
	if (!strNetworkID.strip().empty() || !strAccountNum.strip().empty() || !dstrSponsorCode.strip().empty() )
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
		//Pending trade search with Fund/Class and  date combination is irrelavant 
		strFromDate = NULL_STRING;
		strToDate	= NULL_STRING;
	}

	if( pTradeVerificationList ->initSearch(    strSearchType.strip(), 
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
									            strSerachTransType.strip(),
                                                I_("Y") , // EXclude Verified trades
                                                dstrUserId,
                                                dstrExcludeAggrOrd,  //Exclude AggrgatedOrder Underlying trades from verification
												dstrSponsorCode,
												dstrPlatform
												) <= WARNING && pTradeVerificationList)
    {
        setObject( pTradeVerificationList, TRADE_VERIFCICATION_LIST , OBJ_ACTIVITY_NONE, BF::HOST );
        _pTradeVerificationList = *&pTradeVerificationList;
    }
    else
    {
        delete pTradeVerificationList;
        pTradeVerificationList = NULL;
    }
   return(GETCURRENTHIGHESTSEVERITY());
}

////////////////////////////////VALIDATIONS////////////////////////////////////
//******************************************************************************
SEVERITY TradeVerificationSearch::doValidateField(const BFFieldId& idField, 
   const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );

   //for now, there are no validations for the SWIFT fields (other than NetworkId)
   if( idField == ifds::TransNum )
      validateTransNum(strValue, idDataGroup);
   else if ( idField == ifds::WireOrdNum )
      validateWireOrdNum(strValue, idDataGroup);
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
SEVERITY TradeVerificationSearch::validateTransNum(const DString& strValue, 
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
SEVERITY TradeVerificationSearch::validateWireOrdNum(const DString& strValue, 
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
SEVERITY TradeVerificationSearch::validateNSCCControlNumber(const DString& strValue, const BFDataGroupId& idDataGroup)
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
////////////////////////////////END VALIDATIONS////////////////////////////////
//******************************************************************************
////////////////////////////////RELATED CHANGES////////////////////////////////

//******************************************************************************
SEVERITY TradeVerificationSearch::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAME2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );

	if( idField == ifds::SearchType )
   {
      setUpdatedFlag(idField, idDataGroup, false);
      DString strSearchType;
      getField(ifds::SearchType, strSearchType, idDataGroup, false);
      clearSearchFields(idDataGroup);
      clearRequiredFlags(idDataGroup);
      if(!strSearchType.empty() && ALL_TRADES != strSearchType )
      {
        setFieldRequired(BFFieldId::getId(strSearchType), idDataGroup, true);
        setValidFlag(BFFieldId::getId(strSearchType), idDataGroup, false);
	    if ( strSearchType == EXTERNAL_ID )
	    {
            setFieldRequired( ifds::ExternalId, idDataGroup, true );
		    setValidFlag( ifds::ExternalId, idDataGroup, false );
	    }
        else
		setFieldRequired( ifds::ExternalId, idDataGroup, false );	
      }
	  bool bReq = (strSearchType.strip() == FUND_CLASS);
	  setFieldRequired( ifds::FundCode, idDataGroup, bReq );
	  setValidFlag( ifds::FundCode, idDataGroup, !bReq );
	  setFieldRequired( ifds::ClassCode, idDataGroup, bReq);
	  setValidFlag( ifds::ClassCode, idDataGroup, !bReq );
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
		setFieldNoValidate(ifds::TradesSearchTransType, I_("ALL"), idDataGroup, true, true, true);
	 }
     if( TRANSTYPE == strSearchType.stripAll())
     {
        setFieldNoValidate(ifds::TradesSearchTransType,  ALL_TRANS_TYPE, idDataGroup, false, true, true,  false);
     }
     if( NETWORK == strSearchType.strip())
     {
        loadNetworkIDValues(idDataGroup);
     }
	 if( PLATFORM == strSearchType.strip())
	 {
		 setFieldRequired( ifds::Platform, idDataGroup, true );
		 setValidFlag( ifds::Platform, idDataGroup, false );
	 }
     notifyObservers( idField, idDataGroup, FIELD_NOTIFICATIONS, E_EVENT_VALUE_CHANGE, I_( "" ));
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
   setFieldUpdated (idField, idDataGroup, false);
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
////////////////////////////////END RELATED CHANGES////////////////////////////////
//******************************************************************************
void TradeVerificationSearch::clearRequiredFlags(const BFDataGroupId& idDataGroup)
{
  MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "clearRequiredFlags" ) );
   for( int i=0; i<numCriteriaFields; ++i )
      setFieldRequired(criteriaFields[i], idDataGroup, false);
}

//******************************************************************************
SEVERITY TradeVerificationSearch::loadSearchTypeSubstList( const BFDataGroupId& idDataGroup )
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
void TradeVerificationSearch::loadTransTypeSubstList( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "loadDepRedCodeSubstList" ) );

   DString dstrSubst;
   BFProperties *pBFProperties = getFieldProperties ( ifds::TradesSearchTransType, idDataGroup );
   pBFProperties->getAllSubstituteValues ( dstrSubst );
   dstrSubst = removeItemFromSubtList ( dstrSubst, I_("ID"));
   dstrSubst = removeItemFromSubtList ( dstrSubst, I_("EQ"));
   setFieldAllSubstituteValues( ifds::TradesSearchTransType, idDataGroup, dstrSubst );    
}
//******************************************************************************
bool TradeVerificationSearch::isValidForInquiry(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "isValidForInquiry" ) );

   SEVERITY sev = NO_SEVERITY, sevMax = NO_SEVERITY;
   validateAll(idDataGroup);
   sev = getErrorState(ifds::SearchType, idDataGroup);
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
bool TradeVerificationSearch::isSWIFT()
{
  MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "isSWIFT" ) );

	DString strSWIFT;
   getWorkSession().getOption( ifds::NetworkOrder, strSWIFT, BF::HOST, false);
	if (strSWIFT.strip() == YES)
		return true;

	return false;
}
void TradeVerificationSearch::clearSearchFields(const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "clearSearchFields" ) );

   setFieldNoValidate(ifds::TransNum, I_("0"), idDataGroup, false, false, false, false);
   for( int i=1; i<numCriteriaFields; ++i )
      setFieldNoValidate(criteriaFields[i], NULL_STRING, idDataGroup, false);
}

//******************************************************************************
bool TradeVerificationSearch::isCriteriaEntered(const BFDataGroupId& idDataGroup)
{
  MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "isCriteriaEntered" ) );
   //1. search type has to be specified (however, not by the user)
   DString strSearchType;
   getField(ifds::SearchType, strSearchType, idDataGroup, false);
   assert( !strSearchType.strip().empty() );
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
//******************************************************************************
SEVERITY TradeVerificationSearch::validateFundNumber( const BFDataGroupId &idDataGroup, const DString &dstrFundNumber)

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
SEVERITY TradeVerificationSearch::validateFundClassCode ( const BFDataGroupId  &idDataGroup )

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
SEVERITY TradeVerificationSearch::validateFundWKN( const BFDataGroupId &idDataGroup,const DString &dstrFundWKN )

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
SEVERITY TradeVerificationSearch::validateFundISIN( const BFDataGroupId &idDataGroup,const DString &dstrFundISIN)
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
SEVERITY TradeVerificationSearch::setFundByFundNumber(const BFDataGroupId &idDataGroup, const DString &dstrFundNumber)
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
SEVERITY TradeVerificationSearch::setFundbyFundClass(const BFDataGroupId &idDataGroup, const DString &dstrFundCode, const DString &dstrClassCode)
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
SEVERITY TradeVerificationSearch::setFundByWKN(const BFDataGroupId &idDataGroup, const DString &dstrFundWKN)
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
SEVERITY TradeVerificationSearch::setFundByISIN(const BFDataGroupId &idDataGroup, const DString &dstrFundISIN)
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
SEVERITY TradeVerificationSearch::setSearchTypeSubstSet(const BFFieldId& idField, const BFDataGroupId &idDataGroup)
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
    DString dstrSearchType;
    getField(ifds::SearchType, dstrSearchType, idDataGroup, false);
    if ( dstrSubst.find( I_("TradeDate") ) != DString::npos )
    {
	   dstrSubst = removeItemFromSubtList ( dstrSubst, I_("TradeDate") );		
	   bSubstitutionChanged = true;
	}		
	if ( dstrSearchType == FUND_CLASS )
	    setFieldNoValidate(ifds::SearchType, TRANSNUM, idDataGroup, false );
	if ( bSubstitutionChanged )
	{
		setFieldAllSubstituteValues ( ifds::SearchType, idDataGroup, dstrSubst );  
		BFProperties *pBFProperties = getFieldProperties ( ifds::SearchType, idDataGroup );
		pBFProperties->setSubstituteValues( NULL );
		notifyObservers( ifds::SearchType, idDataGroup, FIELD_NOTIFICATIONS, E_EVENT_PROPERTY_CHANGE, I_( "" ));
	}	
	return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************
SEVERITY TradeVerificationSearch::loadNetworkIDValues (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, 
                           CLASSNAME, 
                           I_("loadNetworkIDValues"));

   DString validNetworkType; //comma separated list of valid network types for the environment

   getWorkSession().getOption ( ifds::ValidNetworkType,
                                validNetworkType,
                                BF::HOST,
                                false);
   if (!validNetworkType.empty())
   {
      if (validNetworkType.find (I_("AWD")) == DString::npos)
      {
         validNetworkType.stripTrailing ( ',' );
         validNetworkType += I_(",AWD"); 
      }

      loadSubstitutionList (ifds::NetworkID, idDataGroup, validNetworkType);

   }
   return GETCURRENTHIGHESTSEVERITY ();
}
//****************************************************************************
void TradeVerificationSearch::loadPlatformSetSubstList (const BFDataGroupId &idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "loadPlatformSet" ) );

   DString dstrSubst;
   BFProperties *pBFProperties = getFieldProperties ( ifds::Platform, idDataGroup );
   pBFProperties->getAllSubstituteValues ( dstrSubst );
   setFieldAllSubstituteValues( ifds::Platform, idDataGroup, dstrSubst );   
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastbp/TradeVerificationSerach.cpp-arc  $
// 
//    Rev 1.0  22 July 2014
// Initial revision.
*/



