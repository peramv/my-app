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
// ^FILE   : Settlement.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : May 24,2002
//
//********************************************************************************
#include "stdafx.h"

#include "Settlement.hpp"
#include "SettlementTotalList.hpp"
#include "SettlementTradeList.hpp"
#include <ifastdataimpl\dse_dstc0200_vw.hpp>
#include <ifastdataimpl\dse_dstc0200_req.hpp>
#include <ifastdataimpl\dse_dstc0201_req.hpp>
#include "broker.hpp"
#include "brokerlist.hpp"
#include "fundmasterlist.hpp"
#include "mgmtco.hpp"
#include "BatchInfoList.hpp"
#include "funddetaillist.hpp" 

#include <ifastdataimpl\dse_dstc0124_req.hpp>
#include <ifastdataimpl\dse_dstc0124_vw.hpp>
#include <ifastdataimpl\dse_dstc0149_vw.hpp>


namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME             = I_( "Settlement" );
   const I_CHAR * const ALL_TRADE             = I_( "AL" );
   const I_CHAR * const ACCOUNT               = I_( "AC" );
   const I_CHAR * const WIRE_ORDER            = I_( "WO" );
   const I_CHAR * const TRADE_DATE            = I_( "TD" );
   const I_CHAR * const SETTLE_DATE           = I_( "SD" );
   const I_CHAR * const SETTLE_CURRENCY       = I_( "CU" );
   const I_CHAR * const BROKER                = I_( "BR" );
   const I_CHAR * const FUND                  = I_( "FN" );
   const I_CHAR * const SINGLESEARCH          = I_( "TX" );
   const I_CHAR * const TRANS_NUMBER          = I_( "TN" );
   const I_CHAR * const REGISTRATION_AGENT    = I_( "RA");
   const I_CHAR * const SEARCH_TYPE           = I_( "SearchType" );
   const I_CHAR * const ACCOUNT_NUM           = I_( "AccountNum" );
   const I_CHAR * const EXTERNAL_ID           = I_( "ET" );
   const I_CHAR * const SETTLEMENT_TRADELIST  = I_( "SettlementTradeList" );
   const I_CHAR * const SETTLEMENT_TOTAL_LIST = I_( "SettlementTotalList" );
   const I_CHAR * const YES                   = I_( "Y" );
   const I_CHAR * const EPA_BROKER            = I_( "EP" );

   const int AUTO_BATCHING = 2;
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ACTIVE_BATCH;
}

namespace CND
{
   extern CLASS_IMPORT const long ERR_DATA_NOT_FOUND;
   extern CLASS_IMPORT const long ERR_BROKER_NOT_FOUND;
   extern  const long ERR_FUNDCODE_SETTLE_CURRENCY;
   extern  const long ERR_FIELD_INVALID_F4_FOR_SEARCH;
   extern  const long ERR_FIELD_MANDATORY_F4_FOR_SEARCH;
   extern  const long ERR_FROM_DATE_FUTURE_DATE;
   extern  const long ERR_EARLY_ENDDATE;
   extern  const long ERR_FUND_NOT_EFFECTIVE;
   extern  const long ERR_INVALID_FUND_CLASS_CODES;
   extern  const long ERR_HAS_NO_INQ_PERMISSION_FOR_SETTLEMENT;
   extern  const long ERR_WARN_HAS_NO_SETTLE_PERMISSION;
   extern  const long ERR_BACKDATED_NOT_ALLOWED_FOR_SEARCH_TYPE;
   extern  const long ERR_BRK_EPA_STATUS_NOT_ACTIVE;
   extern  const long ERR_INVALID_BROKER_CODE;
}

namespace ifds
{
   //extern CLASS_IMPORT const BFTextFieldId SettleAll;
   extern CLASS_IMPORT const BFTextFieldId SettlementTransType;
   extern CLASS_IMPORT const BFTextFieldId SettleCross1;
   extern CLASS_IMPORT const BFTextFieldId SettleCross2;
   extern CLASS_IMPORT const BFTextFieldId VolSettleType1;
   extern CLASS_IMPORT const BFTextFieldId VolSettleType2;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFTextFieldId SettlePermCode;
   extern CLASS_IMPORT const BFTextFieldId rxBatchName;
   extern CLASS_IMPORT const BFTextFieldId EPABroker;
   extern CLASS_IMPORT const BFTextFieldId RegAgentCode;
}

namespace UAF
{ 
   extern CLASS_IMPORT I_CHAR * const SETTLE_ALL_TRADE;             
   extern CLASS_IMPORT I_CHAR * const SETTLE_WIRE_ORDER;            
   extern CLASS_IMPORT I_CHAR * const SETTLE_BROKER;              
   extern CLASS_IMPORT I_CHAR * const SETTLE_ACCOUNT;             
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
//  Field DD Id,					State Flags,			Group Flags 
   { ifds::SearchType,      BFCBO::REQUIRED,             0 }, 
   { ifds::WireOrdNum,      BFCBO::NONE,                 0 }, 
   { ifds::TransNum,        BFCBO::NONE,                 0 }, 
   { ifds::AccountNum,      BFCBO::NONE,                 0 }, 
   { ifds::TransType,       BFCBO::NONE,                 0 }, 
   { ifds::CompanyCode,     BFCBO::NONE,                 0 }, 
   { ifds::BrokerCode,      BFCBO::NONE,                 0 }, 
   { ifds::InterCode,       BFCBO::NONE,                 0 }, 
   { ifds::FundCode,        BFCBO::NONE,                 0 }, 
   { ifds::SettleCurrency,  BFCBO::NONE,                 0 }, 
   { ifds::TradeDate,       BFCBO::NONE,                 0 }, 
   { ifds::SettleDate,      BFCBO::NONE,                 0 }, 
   { ifds::StartDate,       BFCBO::NONE,                 0 }, 
   { ifds::EndDate,         BFCBO::NONE,                 0 }, 
   { ifds::OverrideRepeats, BFCBO::NONE,                 0 }, 
   { ifds::VolSettleType,   BFCBO::NONE,                 0 }, 
   { ifds::SettleCross1,    BFCBO::IMMEDIATE_VALIDATION, 0 }, 
   { ifds::SettleCross2,    BFCBO::NONE,                 0 }, 
   { ifds::SettlePermCode  ,BFCBO::NONE,                 0 }, 
   //Add for API 
   { ifds::ClassCode,		 BFCBO::NONE,                 0 }, 

	{ ifds::ExternalIdType,  BFCBO::NONE,                 0 }, 
	{ ifds::ExternalId,      BFCBO::NONE,                 0 }, 
	{ ifds::rxBatchName,     BFCBO::REQUIRED | BFCBO::APPEND_VALUE_TO_SUBST,             0 }, 
    { ifds::RegAgentCode,    BFCBO::NONE,                 0 },
    { ifds::ExcludeStopSettle, BFCBO::NONE,               0 },
};

namespace FUND_ID_CODE
{
 const I_CHAR * const VALOREN	=	I_("Valoren");
 const I_CHAR * const TDCC		=	I_("TDCC");
 const I_CHAR * const CUSIP		=	I_("CUSIP");
}

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );


const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = 
{
   // Object Label,                 State Flags,      Group Flags 
   { I_( "SettlementList" ),    BFCBO::NONE,     0},

};

static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );

//******************************************************************************

Settlement::Settlement( BFAbstractCBO &parent )
: MFCanBFCbo( parent ),
pBatchInfoList (NULL)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );

}

//******************************************************************************
Settlement::~Settlement()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//********************************************************************************   
SEVERITY Settlement::setParameters(const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup, bool lFormatted/*= false*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setParameter" ) );

   setFieldNoValidate(idField,strValue,idDataGroup,lFormatted);
   setUpdatedFlag( idField, idDataGroup, false );

   return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************   
SEVERITY Settlement::setParameters(DString& dstrTransType,DString& dstrAccountNum, const BFDataGroupId& idDataGroup  )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setParameter" ) );
   setFieldNoValidate(ifds::SearchType,dstrTransType,idDataGroup,false);
   setFieldNoValidate(ifds::AccountNum,dstrAccountNum,idDataGroup,false);
   //setFieldReadOnly( ifds::SettleCurrency,idDataGroup,true ); 
   setUpdatedFlag( ifds::SearchType, idDataGroup, false );
   setUpdatedFlag( ifds::AccountNum, idDataGroup, false );

   return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************   
SEVERITY Settlement::setParameters(DString& dstrTransType,
								   DString& dstrAccountNum, 
								   DString& dstrWireOrderNum,
								   const BFDataGroupId& idDataGroup  )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setParameter" ) );

   setFieldNoValidate(ifds::SearchType,dstrTransType,idDataGroup,false);
   setFieldNoValidate(ifds::AccountNum,dstrAccountNum,idDataGroup,false);
   setFieldNoValidate(ifds::WireOrdNum,dstrWireOrderNum,idDataGroup,false);

   setUpdatedFlag( ifds::SearchType, idDataGroup, false );
   setUpdatedFlag( ifds::AccountNum, idDataGroup, false );
   setUpdatedFlag( ifds::WireOrdNum, idDataGroup, false );

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
SEVERITY Settlement::init( const BFDataGroupId& idDataGroup,
                           const DString& dstrTrack /*= I_("N")*/, 
                           const DString& dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   setFieldNoValidate( ifds::SearchType,ACCOUNT,idDataGroup,false );
   setFieldNoValidate( ifds::SearchType,ACCOUNT,BF::HOST,false );
   setUpdatedFlag( ifds::SearchType, idDataGroup, false );
   setUpdatedFlag( ifds::SearchType, BF::HOST, false );

   // Set default Value for SettleAll
   // This value should come from View 
   //   setFieldNoValidate( ifds::SettleAll,YES,idDataGroup,false );	
   setFieldSubstituteValues ( ifds::TransType, idDataGroup, ifds::SettlementTransType );
   addCrossEdit(ifds::SettleCross1, ifds::FundCode);
   addCrossEdit(ifds::SettleCross1, ifds::SettleCurrency);

   addCrossEdit(ifds::SettleCross2, ifds::StartDate);
   addCrossEdit(ifds::SettleCross2, ifds::EndDate);

   DString dstrCurBusinessDate;
   getWorkSession().getDateInHostFormat(dstrCurBusinessDate, 
                                        DSTCWorkSession::DATE_TYPE::CURRENT_BUSINESS_DAY,idDataGroup);   

   setFieldNoValidate( ifds::StartDate, dstrCurBusinessDate, idDataGroup , false );
   setFieldNoValidate( ifds::EndDate, dstrCurBusinessDate, idDataGroup , false );  
   setFieldNoValidate( ifds::TransType, I_("All"), idDataGroup , false ); 
   setFieldNoValidate( ifds::StartDate, dstrCurBusinessDate, idDataGroup , false );
   setFieldNoValidate( ifds::SettleDate, dstrCurBusinessDate, idDataGroup , false );  
   setFieldNoValidate( ifds::TradeDate,  dstrCurBusinessDate, idDataGroup , false );

   initBatchList (idDataGroup);

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY Settlement::reInit()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "reInit" ) );



   return(GETCURRENTHIGHESTSEVERITY());
}

//*************************************************************************************

SEVERITY Settlement::doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField") );
   if( idField == ifds::SettleCross1 )
   {
      validateFundCodeCurrency( idDataGroup );   
   }
   else if( idField == ifds::BrokerCode )
   {
      validateBrokerCode(strValue,idDataGroup ); 
   }
   else if( idField == ifds::SettleCross2 )
   {
      validateStartEndDate( idDataGroup );   
   }
   else if( idField == ifds::StartDate )
   {
      validateStartDate(strValue, idDataGroup );
   }
   else if( idField == ifds::FundCode )
   {
      validateFundCode(strValue,idDataGroup);
   }
   else if( idField == ifds::SearchType )
   {
      validateSearchType(strValue, idDataGroup);
   }
   else if (idField == ifds::rxBatchName && !strValue.empty ())
   {
      if (pBatchInfoList)
         pBatchInfoList->validateBatch (strValue, idDataGroup);
   }
   else if ( idField == ifds::SettleDate )
   {
      validateSettleDate(strValue,idDataGroup);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************************
SEVERITY Settlement::validateStartEndDate( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateStartEndDate") );
   DString dstrStartDate,dstrEndDate,dstrCurDate;
   getField(ifds::StartDate,dstrStartDate, idDataGroup,false);
   getField(ifds::EndDate,dstrEndDate,  idDataGroup,false);

   if( DSTCommonFunctions::CompareDates( dstrEndDate, dstrStartDate ) == DSTCommonFunctions::FIRST_EARLIER )
   {
      ADDCONDITIONFROMFILE( CND::ERR_EARLY_ENDDATE );      
   }
   setUpdatedFlag( ifds::SettleCross2, idDataGroup, false );

   return(GETCURRENTHIGHESTSEVERITY());
}
//********************************************************************************************
SEVERITY Settlement::validateStartDate(const DString& strDate,  const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateStartEndDate") );
   DString dstrStartDate,dstrCurDate;
   dstrStartDate = strDate;
   getWorkSession().getOption( ifds::CurrBusDate, dstrCurDate, idDataGroup, false );
   if( DSTCommonFunctions::CompareDates( dstrCurDate, dstrStartDate ) == DSTCommonFunctions::FIRST_EARLIER )
   {
      ADDCONDITIONFROMFILE( CND::ERR_FROM_DATE_FUTURE_DATE );     
   }
   return(GETCURRENTHIGHESTSEVERITY());

}

//**********************************************************************************************
SEVERITY Settlement::validateBrokerCode( const DString& dstrValue,  const BFDataGroupId& idDataGroup  )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateBrokerCode") );

   DString dstrSearchType, dstrBrkSearchType;
   dstrBrkSearchType = BROKER;
   dstrBrkSearchType += I_(",");
   dstrBrkSearchType += EPA_BROKER;

   getField(ifds::SearchType,dstrSearchType,idDataGroup,false);
   dstrSearchType.strip().upperCase();

   if( !DSTCommonFunctions::codeInList (dstrSearchType, dstrBrkSearchType ) )
      return GETCURRENTHIGHESTSEVERITY();

   BrokerList *pBrokerList;
   Broker *pBroker = NULL;
   DString BrokerField = I_( "Broker Code" );      
   if( dstrValue == NULL_STRING )
   {
      ADDCONDITIONFROMFILEIDI( CND::ERR_FIELD_MANDATORY_F4_FOR_SEARCH, DString(I_("FIELDNAME=")) + BrokerField );
   }
   else
   {
      SEVERITY sevRtn1,sevRtn2;
      DString dstrVolSettleType;
      sevRtn1= getWorkSession().getBrokerList(pBrokerList);
      if( pBrokerList )
         sevRtn2 = pBrokerList->getBroker(dstrValue, pBroker);

      if ( BROKER == dstrSearchType.strip())
      {
         pBroker->getField(ifds::VolSettleType,dstrVolSettleType,idDataGroup);
         sevRtn1 = sevRtn1 >  sevRtn2?sevRtn1:sevRtn2;        
         if( sevRtn1 > WARNING || pBroker == NULL )
         {
            ADDCONDITIONFROMFILEIDI( CND::ERR_FIELD_INVALID_F4_FOR_SEARCH, DString(I_("FIELDNAME=")) + BrokerField );
         }

         DString strBrokerCode(dstrValue);

         strBrokerCode.strip().upperCase();

         if ( strBrokerCode == I_("ALL"))
         {
            ADDCONDITIONFROMFILE( CND::ERR_INVALID_BROKER_CODE );
         }
      }
      else // EPA
      {
         DString strEPABroker;
         pBroker->getField(ifds::EPABroker,strEPABroker,idDataGroup,false);
         strEPABroker.strip().upperCase();

         if( strEPABroker == I_("N"))
         {
            ADDCONDITIONFROMFILE( CND::ERR_BRK_EPA_STATUS_NOT_ACTIVE);
         }

         DString strBrokerCode(dstrValue);

         strBrokerCode.strip().upperCase();

         if ( strBrokerCode == I_("ALL"))
         {
            int count = CONDITIONCOUNT();
            Condition   *c = NULL;
            for( int i = 0; i < count; i++ )
            {
               c = GETCONDITION( i );
               int condCode = c->getCode();
               if( condCode == CND::ERR_BROKER_NOT_FOUND )
               {
                  CLEARCONDITION( i );
                  break;
               }
            }
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//***********************************************************************************
SEVERITY Settlement::validateFundCodeCurrency( const BFDataGroupId& idDataGroup  )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateFundCodeCurrency") );
   DString dstrFundCode, dstrCurrency,dstrSearchType;
   getField(ifds::SearchType,dstrSearchType,idDataGroup,false);
   getField(ifds::FundCode,dstrFundCode,idDataGroup,false);
   getField(ifds::SettleCurrency,dstrCurrency,idDataGroup,false);
   if( dstrSearchType.strip() == BROKER )
   {
      if( NULL_STRING == dstrFundCode.strip() && NULL_STRING == dstrCurrency.strip() )
      {
         ADDCONDITIONFROMFILE( CND::ERR_FUNDCODE_SETTLE_CURRENCY );     
      }

   }
   setUpdatedFlag( ifds::SettleCross1, idDataGroup, false );

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
SEVERITY Settlement::BrokerCodeRelatedChanges( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("BrokerCodeRelatedChanges") );

   DString dstrSearchType, dstrBrokerCode, dstrBrkSearchType;
   dstrBrkSearchType = BROKER;
   dstrBrkSearchType += I_(",");
   dstrBrkSearchType += EPA_BROKER;

   getField(ifds::SearchType,dstrSearchType,idDataGroup,false);
   dstrSearchType.strip().upperCase();

   if( !DSTCommonFunctions::codeInList (dstrSearchType, dstrBrkSearchType ) )
      return GETCURRENTHIGHESTSEVERITY();

   BrokerList *pBrokerList;
   Broker *pBroker = NULL;
   getField(ifds::BrokerCode,dstrBrokerCode,idDataGroup,false);

   if( dstrBrokerCode != NULL_STRING && getWorkSession().getBrokerList(pBrokerList) <= WARNING &&
       pBrokerList->getBroker(dstrBrokerCode, pBroker) <= WARNING && pBroker )
   {
      if ( BROKER == dstrSearchType.strip())
      {
         DString dstrVolSettleType;
         pBroker->getField( ifds::VolSettleType, dstrVolSettleType, idDataGroup,false );
         dstrVolSettleType.strip().upperCase();
         setFieldNoValidate( ifds::VolSettleType, I_("I"), idDataGroup , false );
         if( dstrVolSettleType == I_("NET") ) // Net/Individual 
         {
            setFieldSubstituteValues( ifds::VolSettleType, idDataGroup, ifds::VolSettleType1 );
            setFieldReadOnly(ifds::VolSettleType,idDataGroup,false);
         }
         else if( dstrVolSettleType == I_("MAS") ) //Mass/Individual
         {
            setFieldSubstituteValues( ifds::VolSettleType, idDataGroup, ifds::VolSettleType2 );
            setFieldReadOnly(ifds::VolSettleType,idDataGroup,false);
         }
         else if( dstrVolSettleType == I_("IND") ) //Individual
         {
            setFieldSubstituteValues( ifds::VolSettleType, idDataGroup, ifds::VolSettleType1 );
            setFieldReadOnly(ifds::VolSettleType,idDataGroup,true);
         }
      }
      else // EPA
      {
         DString strCurBusDate;
         getWorkSession().getOption( ifds::CurrBusDate, strCurBusDate, idDataGroup, false );
         setFieldNoValidate(ifds::SettleDate,strCurBusDate,idDataGroup,false,false,true,true);
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY Settlement::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges") );
   if( idField == ifds::SearchType )
   {
      SearchRelatedChanges( idDataGroup );         
   }
   else if( idField == ifds::BrokerCode )
   {
      BrokerCodeRelatedChanges(idDataGroup);

   }
   else if( idField == ifds::SettleCurrency || idField == ifds::FundCode )
   {
      DString dstrSearchType;
      getField(ifds::SearchType,dstrSearchType,idDataGroup,false);
      dstrSearchType.strip();
      if( dstrSearchType == BROKER )
      {
         DString dstr;
         getField(ifds::SettleCurrency,dstr,idDataGroup,false);
         if( dstr.strip() != NULL_STRING )
         {
            setFieldRequired(ifds::FundCode,idDataGroup,false);        
         }
         getField(ifds::FundCode,dstr,idDataGroup,false);
         if( dstr.strip() != NULL_STRING )
         {
            setFieldRequired(ifds::SettleCurrency,idDataGroup,false);        
         }
      }
   }
   else if( idField == ifds::VolSettleType )
   {

      DString dstrSearchType;
      getField(ifds::SearchType,dstrSearchType,idDataGroup,false);
      dstrSearchType.strip();
      setFieldReadOnly(ifds::TransType,idDataGroup,false);
      if( dstrSearchType == BROKER )
      {
         DString dstrVolSettleType;
         getField(ifds::VolSettleType,dstrVolSettleType,idDataGroup,false);
         dstrVolSettleType.strip();
         if( dstrVolSettleType == I_("N") )
         { //Net
            setFieldNoValidate(ifds::TransType,I_("All"),idDataGroup,false,true,false,false);
            setFieldReadOnly(ifds::TransType,idDataGroup,true);           
         }
      }
   }
   else if (idField == ifds::rxBatchName)
   {
      setFieldUpdated (ifds::rxBatchName, idDataGroup, true);
      setFieldValid (ifds::rxBatchName, idDataGroup, false);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//************************************************************************************
SEVERITY Settlement::SearchRelatedChanges( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("SearchRelatedChanges") );
   BFFieldId lFieldIds1[18] = { ifds::NullFieldId, ifds::NullFieldId, ifds::NullFieldId, ifds::NullFieldId,
      ifds::NullFieldId, ifds::NullFieldId, ifds::NullFieldId, ifds::NullFieldId, 
      ifds::NullFieldId, ifds::NullFieldId, ifds::NullFieldId, ifds::NullFieldId,
      ifds::NullFieldId, ifds::NullFieldId, ifds::NullFieldId, ifds::NullFieldId, 
      ifds::NullFieldId, ifds::NullFieldId };

   BFFieldId lFieldIds2[18] = { ifds::NullFieldId, ifds::NullFieldId, ifds::NullFieldId, ifds::NullFieldId,
      ifds::NullFieldId, ifds::NullFieldId, ifds::NullFieldId, ifds::NullFieldId, 
      ifds::NullFieldId, ifds::NullFieldId, ifds::NullFieldId, ifds::NullFieldId,
      ifds::NullFieldId, ifds::NullFieldId, ifds::NullFieldId, ifds::NullFieldId, 
      ifds::NullFieldId, ifds::NullFieldId };

   DString dstrSearchType;
   getField(ifds::SearchType,dstrSearchType, idDataGroup);
   dstrSearchType.strip();

   if( dstrSearchType == ALL_TRADE )
   {
      lFieldIds1[0]  = ifds::WireOrdNum;      
      lFieldIds1[1]  = ifds::TransNum;        
      lFieldIds1[2]  = ifds::AccountNum;      
      lFieldIds1[3]  = ifds::TransType;       
      lFieldIds1[4]  = ifds::CompanyCode;      
      lFieldIds1[5]  = ifds::BrokerCode;      
      lFieldIds1[6]  = ifds::InterCode;       
      lFieldIds1[7]  = ifds::FundCode;        
      lFieldIds1[8]  = ifds::SettleCurrency;  
      lFieldIds1[9]  = ifds::TradeDate;       
      lFieldIds1[10] = ifds::SettleDate;      
      lFieldIds1[11] = ifds::StartDate;       
      lFieldIds1[12] = ifds::EndDate;         
      lFieldIds1[13] = ifds::VolSettleType;   
      lFieldIds1[14] = ifds::ExternalIdType;
      lFieldIds1[15] = ifds::ExternalId;
      lFieldIds1[16] = ifds::RegAgentCode;

      setFieldsAsRequired( lFieldIds1, idDataGroup,false );      
   }
   else if( dstrSearchType == SINGLESEARCH )
   {
      lFieldIds1[0] = ifds::AccountNum;      
      lFieldIds1[1] = ifds::TransNum;        
      lFieldIds1[2] = ifds::FundCode;      
      lFieldIds1[3] = ifds::ClassCode;       
      lFieldIds1[4] = ifds::TransType;   

      lFieldIds2[0] = ifds::TradeDate;       
      lFieldIds2[1] = ifds::SettleDate;      
      lFieldIds2[2] = ifds::BrokerCode;      
      lFieldIds2[3] = ifds::ExternalIdType;
      lFieldIds2[4] = ifds::ExternalId;
      lFieldIds2[5] = ifds::RegAgentCode;

      setFieldsAsRequired( lFieldIds1, idDataGroup,true );  
      setFieldsAsRequired( lFieldIds2, idDataGroup,false ); 
   }
   else if( dstrSearchType == ACCOUNT )
   {
      lFieldIds1[0] = ifds::AccountNum;

      lFieldIds2[0]  = ifds::WireOrdNum;      
      lFieldIds2[1]  = ifds::TransNum;        
      lFieldIds2[2]  = ifds::TransType;       
      lFieldIds2[3]  = ifds::CompanyCode;      
      lFieldIds2[4]  = ifds::BrokerCode;      
      lFieldIds2[5]  = ifds::InterCode;       
      lFieldIds2[6]  = ifds::FundCode;        
      lFieldIds2[7]  = ifds::TradeDate;       
      lFieldIds2[8]  = ifds::SettleDate;      
      lFieldIds2[9]  = ifds::StartDate;       
      lFieldIds2[10] = ifds::EndDate;         
      lFieldIds2[11] = ifds::VolSettleType;   
      lFieldIds2[12] = ifds::ExternalIdType;
      lFieldIds2[13] = ifds::ExternalId;
      lFieldIds2[14] = ifds::RegAgentCode;

      setFieldsAsRequired( lFieldIds1, idDataGroup,true );
      setFieldsAsRequired( lFieldIds2, idDataGroup,false );
   }
   else if( dstrSearchType == EXTERNAL_ID )
   {
      lFieldIds1[0]  = ifds::ExternalIdType;
      lFieldIds1[1]  = ifds::ExternalId;

      lFieldIds2[0]  =  ifds::WireOrdNum;      
      lFieldIds2[1]  =  ifds::TransNum;        
      lFieldIds2[2]  =  ifds::TransType;       
      lFieldIds2[3]  =  ifds::CompanyCode;      
      lFieldIds2[4]  =  ifds::BrokerCode;      
      lFieldIds2[5]  =  ifds::InterCode;       
      lFieldIds2[6]  =  ifds::FundCode;        
      lFieldIds2[7]  =  ifds::TradeDate;       
      lFieldIds2[8]  =  ifds::SettleDate;      
      lFieldIds2[9]  =  ifds::StartDate;       
      lFieldIds2[10] = ifds::EndDate;         
      lFieldIds2[11] = ifds::VolSettleType;  
      lFieldIds2[12] = ifds::AccountNum;  
      lFieldIds2[13] = ifds::SettleCurrency;  
      lFieldIds2[14] = ifds::RegAgentCode;

      setFieldsAsRequired( lFieldIds1, idDataGroup,true );
      setFieldsAsRequired( lFieldIds2, idDataGroup,false );
   }
   else if( dstrSearchType == WIRE_ORDER )
   {
      lFieldIds1[0]  = ifds::WireOrdNum; 

      lFieldIds2[0]  = ifds::VolSettleType;
      lFieldIds2[1]  = ifds::TransNum;        
      lFieldIds2[2]  = ifds::AccountNum;      
      lFieldIds2[3]  = ifds::TransType;       
      lFieldIds2[4]  = ifds::CompanyCode;      
      lFieldIds2[5]  = ifds::BrokerCode;      
      lFieldIds2[6]  = ifds::InterCode;       
      lFieldIds2[7]  = ifds::FundCode;        
      lFieldIds2[8]  = ifds::SettleCurrency;  
      lFieldIds2[9]  = ifds::TradeDate;       
      lFieldIds2[10] = ifds::SettleDate;      
      lFieldIds2[11] = ifds::StartDate;       
      lFieldIds2[12] = ifds::EndDate;                    
      lFieldIds2[13] = ifds::ExternalIdType;                    
      lFieldIds2[14] = ifds::ExternalId;                    
      lFieldIds2[15] = ifds::RegAgentCode;

      setFieldsAsRequired( lFieldIds1, idDataGroup,true );    
      setFieldsAsRequired( lFieldIds2, idDataGroup,false );         
   }
   else if( dstrSearchType == TRADE_DATE  || 
            dstrSearchType == SETTLE_DATE )
   {
      lFieldIds1[0]  = ifds::StartDate;       
      lFieldIds1[1]  = ifds::EndDate;         
      lFieldIds1[2]  = ifds::SettleCurrency;  
      lFieldIds1[3]  = ifds::TransType; 

      lFieldIds2[0]  = ifds::WireOrdNum;      
      lFieldIds2[1]  = ifds::TransNum;        
      lFieldIds2[2]  = ifds::AccountNum;      
      lFieldIds2[3]  = ifds::CompanyCode;      
      lFieldIds2[4]  = ifds::BrokerCode;            
      lFieldIds2[6]  = ifds::FundCode;        
      lFieldIds2[7]  = ifds::TradeDate;       
      lFieldIds2[8]  = ifds::SettleDate;      
      lFieldIds2[9]  = ifds::VolSettleType;   
      lFieldIds2[10] = ifds::ExternalIdType;   
      lFieldIds2[11] = ifds::ExternalId;   
      lFieldIds2[12] = ifds::RegAgentCode;

      setFieldsAsRequired( lFieldIds1, idDataGroup,true );    
      setFieldsAsRequired( lFieldIds2, idDataGroup,false );   
   }
   else if( dstrSearchType == SETTLE_CURRENCY )
   {
      lFieldIds1[0]  = ifds::SettleCurrency;  

      lFieldIds2[0]  = ifds::WireOrdNum;      
      lFieldIds2[1]  = ifds::TransNum;        
      lFieldIds2[2]  = ifds::AccountNum;      
      lFieldIds2[3]  = ifds::TransType;       
      lFieldIds2[4]  = ifds::CompanyCode;      
      lFieldIds2[5]  = ifds::BrokerCode;      
      lFieldIds2[6]  = ifds::InterCode;       
      lFieldIds2[7]  = ifds::FundCode;              
      lFieldIds2[8]  = ifds::TradeDate;       
      lFieldIds2[9]  = ifds::SettleDate;      
      lFieldIds2[10] = ifds::StartDate;       
      lFieldIds2[11] = ifds::EndDate;         
      lFieldIds2[12] = ifds::VolSettleType;   
      lFieldIds2[13] = ifds::ExternalIdType;   
      lFieldIds2[14] = ifds::ExternalId;   
      lFieldIds2[15] = ifds::RegAgentCode;

      setFieldsAsRequired( lFieldIds1, idDataGroup,true );    
      setFieldsAsRequired( lFieldIds2, idDataGroup,false );            
   }
   else if( dstrSearchType == BROKER )
   {
      lFieldIds1[0] = ifds::BrokerCode;   
      lFieldIds1[1] = ifds::VolSettleType;   
      lFieldIds1[2] = ifds::TransType;       
      lFieldIds1[3] = ifds::TradeDate;       
      lFieldIds1[4] = ifds::SettleDate;      
      lFieldIds1[5] = ifds::SettleCurrency;  
      lFieldIds1[6] = ifds::FundCode;        

      lFieldIds2[0] = ifds::WireOrdNum;      
      lFieldIds2[1] = ifds::TransNum;        
      lFieldIds2[2] = ifds::AccountNum;      
      lFieldIds2[3] = ifds::StartDate;       
      lFieldIds2[4] = ifds::EndDate;         
      lFieldIds2[5] = ifds::ExternalIdType;         
      lFieldIds2[6] = ifds::ExternalId;         
      lFieldIds2[7] = ifds::RegAgentCode;

      setFieldsAsRequired( lFieldIds1, idDataGroup,true );    
      setFieldsAsRequired( lFieldIds2, idDataGroup,false );            
   }

   else if( dstrSearchType == FUND )
   {
      lFieldIds1[0] = ifds::FundCode;  

      lFieldIds2[0]  = ifds::WireOrdNum;      
      lFieldIds2[1]  = ifds::TransNum;        
      lFieldIds2[2]  = ifds::AccountNum;      
      lFieldIds2[3]  = ifds::TransType;       
      lFieldIds2[4]  = ifds::CompanyCode;      
      lFieldIds2[5]  = ifds::BrokerCode;      
      lFieldIds2[6]  = ifds::InterCode;             
      lFieldIds2[7]  = ifds::SettleCurrency;  
      lFieldIds2[8]  = ifds::TradeDate;       
      lFieldIds2[9]  = ifds::SettleDate;      
      lFieldIds2[10] = ifds::StartDate;       
      lFieldIds2[11] = ifds::EndDate;         
      lFieldIds2[12] = ifds::VolSettleType;   
      lFieldIds2[13] = ifds::ExternalIdType;   
      lFieldIds2[14] = ifds::ExternalId;   
      lFieldIds2[15] = ifds::RegAgentCode;

      setFieldsAsRequired( lFieldIds1, idDataGroup,true );    
      setFieldsAsRequired( lFieldIds2, idDataGroup,false );    
   }
   else if( dstrSearchType == TRANS_NUMBER )
   {
      lFieldIds1[0]  = ifds::TransNum; 

      lFieldIds2[0]  = ifds::WireOrdNum;
      lFieldIds2[1]  = ifds::VolSettleType;        
      lFieldIds2[2]  = ifds::AccountNum;      
      lFieldIds2[3]  = ifds::TransType;       
      lFieldIds2[4]  = ifds::CompanyCode;      
      lFieldIds2[5]  = ifds::BrokerCode;      
      lFieldIds2[6]  = ifds::InterCode;       
      lFieldIds2[7]  = ifds::FundCode;        
      lFieldIds2[8]  = ifds::SettleCurrency;  
      lFieldIds2[9]  = ifds::TradeDate;       
      lFieldIds2[10] = ifds::SettleDate;      
      lFieldIds2[11] = ifds::StartDate;       
      lFieldIds2[12] = ifds::EndDate;                    
      lFieldIds2[13] = ifds::ExternalIdType;                    
      lFieldIds2[14] = ifds::ExternalId;                    
      lFieldIds2[15] = ifds::RegAgentCode;

      setFieldsAsRequired( lFieldIds1, idDataGroup,true );    
      setFieldsAsRequired( lFieldIds2, idDataGroup,false );         
   }
   else if( dstrSearchType == EPA_BROKER )
   {
      lFieldIds1[0] = ifds::SettleDate;
      lFieldIds1[1] = ifds::BrokerCode;

      lFieldIds2[0] = ifds::WireOrdNum;      
      lFieldIds2[1] = ifds::TransNum;        
      lFieldIds2[2] = ifds::AccountNum;      
      lFieldIds2[3] = ifds::StartDate;       
      lFieldIds2[4] = ifds::EndDate;         
      lFieldIds2[5] = ifds::ExternalIdType;         
      lFieldIds2[6] = ifds::ExternalId;
      lFieldIds2[7] = ifds::RegAgentCode;

      setFieldsAsRequired( lFieldIds1, idDataGroup,true );    
      setFieldsAsRequired( lFieldIds2, idDataGroup,false );

      DString strCurBusDate;
      getWorkSession().getOption( ifds::CurrBusDate, strCurBusDate, idDataGroup, false );
      setFieldNoValidate(ifds::SettleDate,strCurBusDate,idDataGroup,false,false,true,true);
   }
   else if( dstrSearchType == REGISTRATION_AGENT)
   {
         
      lFieldIds1[0] = ifds::RegAgentCode;
      lFieldIds1[1] = ifds::SettleDate;
      lFieldIds1[2] = ifds::TransType;       

      lFieldIds2[0] = ifds::WireOrdNum;      
      lFieldIds2[1] = ifds::TransNum;        
      lFieldIds2[2] = ifds::AccountNum;      
      lFieldIds2[3] = ifds::StartDate;       
      lFieldIds2[4] = ifds::EndDate;         
      lFieldIds2[5] = ifds::ExternalIdType;         
      lFieldIds2[6] = ifds::ExternalId;
      lFieldIds2[7] = ifds::BrokerCode;
      lFieldIds2[8] = ifds::VolSettleType;        
      lFieldIds2[9] = ifds::CompanyCode;      
      lFieldIds2[10] = ifds::InterCode;       
      lFieldIds2[11] = ifds::FundCode;        
      lFieldIds2[12] = ifds::SettleCurrency;  
      lFieldIds2[13] = ifds::TradeDate;       

      setFieldsAsRequired( lFieldIds1, idDataGroup,true );    
      setFieldsAsRequired( lFieldIds2, idDataGroup,false );

      DString strCurBusDate;
      getWorkSession().getOption( ifds::CurrBusDate, strCurBusDate, idDataGroup, false );
      setFieldNoValidate(ifds::SettleDate,strCurBusDate,idDataGroup,false,false,true,true);
   }

      

   lFieldIds1[0]  = ifds::WireOrdNum;  
   lFieldIds1[1]  = ifds::TransNum;  
   lFieldIds1[2]  = ifds::AccountNum;  
   lFieldIds1[3]  = ifds::TransType;  
   lFieldIds1[4]  = ifds::BrokerCode;  
   lFieldIds1[5]  = ifds::InterCode;  
   lFieldIds1[6]  = ifds::FundCode;  
   lFieldIds1[7]  = ifds::SettleCurrency;  
   lFieldIds1[8]  = ifds::VolSettleType;  
   lFieldIds1[9]  = ifds::WireOrdNum; 
   lFieldIds1[10] = ifds::ExternalIdType; 
   lFieldIds1[11] = ifds::ExternalId; 

   int i = 0;
   while( i<=10 )
   {
      setFieldNoValidate(lFieldIds1[i],NULL_STRING,idDataGroup,false,true,false,false);
      setUpdatedFlag( lFieldIds1[i], idDataGroup, false ); //clear all update flags

      if( dstrSearchType == EPA_BROKER )
      {
         if ( lFieldIds1[i] == ifds::BrokerCode)
         {
            setFieldNoValidate(lFieldIds1[i],I_("All"),idDataGroup,false);
         }
      }

      ++i;
   }

   setFieldReadOnly(ifds::TransType,idDataGroup,false);

   return(GETCURRENTHIGHESTSEVERITY());

}

//*********************************************************************************
void Settlement::setFieldsAsRequired( const BFFieldId idField[], const BFDataGroupId& idDataGroup,bool bReqired )
{
   int i = 0;  
   while( idField[i] != ifds::NullFieldId )
   {
      setFieldRequired( idField[i],idDataGroup,bReqired );
      i++;
   }
}
//**********************************************************************************
void Settlement::setFieldsAsReadOnly(  const BFDataGroupId& idDataGroup,bool bReadOnly )
{
   const BFFieldId fieldIds[] = 
   {  ifds::WireOrdNum,
      ifds::SearchType,
      ifds::TransNum,        
      ifds::AccountNum,      
      ifds::TransType,      
      ifds::CompanyCode,      
      ifds::BrokerCode,      
      ifds::InterCode,       
      ifds::FundCode,        
      ifds::SettleCurrency,  
      ifds::TradeDate,       
      ifds::SettleDate,      
      ifds::StartDate,       
      ifds::EndDate,         
      ifds::VolSettleType,
      ifds::ClassCode,
      ifds::ExternalIdType,
      ifds::ExternalId,
      ifds::NullFieldId
   };

   int i = 0;  
   while( fieldIds[i] != ifds::NullFieldId )
   {
      setFieldReadOnly( fieldIds[i],idDataGroup,bReadOnly );
      ++i;
   }
}
//*************************************************************************************
void Settlement::setFieldsAsUpdated(  const BFDataGroupId& idDataGroup,bool bUpdate )
{
   const BFFieldId fieldIds[] = 
   {  ifds::WireOrdNum,
      ifds::SearchType,
      ifds::TransNum,        
      ifds::AccountNum,      
      ifds::TransType,      
      ifds::CompanyCode,      
      ifds::BrokerCode,      
      ifds::InterCode,       
      ifds::FundCode,        
      ifds::SettleCurrency,  
      ifds::TradeDate,       
      ifds::SettleDate,      
      ifds::StartDate,       
      ifds::EndDate,         
      ifds::VolSettleType,
      ifds::ClassCode,
      ifds::ExternalIdType,
      ifds::ExternalId,
      ifds::NullFieldId};

   int i = 0;  
   while( fieldIds[i] != ifds::NullFieldId )
   {
      setUpdatedFlag( fieldIds[i], idDataGroup, bUpdate );
      ++i;
   }
}

//**************************************************************************************
//bListType, 0:SettlementList
//			 1:SettlementTotalList	 
//

void Settlement::buildKey( DString &strKey,const BFDataGroupId& idDataGroup, unsigned int uiListType )
{
   DString dstrSearchType;
   getField(ifds::SearchType,dstrSearchType,idDataGroup,false);
   dstrSearchType.strip();
   switch( uiListType )
   {
      case 0:
         strKey = dstrSearchType + SETTLEMENT_TRADELIST;
         break;
      case 1:
         strKey = dstrSearchType + SETTLEMENT_TOTAL_LIST;
         break;   
   }

   if( dstrSearchType == ACCOUNT )
   {


   }
   else if( dstrSearchType == WIRE_ORDER )
   {


   }
   else if( dstrSearchType == TRADE_DATE )
   {


   }

   else if( dstrSearchType == SETTLE_DATE )
   {


   }

   else if( dstrSearchType == SETTLE_CURRENCY )
   {


   }
   else if( dstrSearchType == BROKER )
   {
   }


}  
//********************************************************************************
SEVERITY Settlement::getSettlementTradeList( SettlementTradeList*& pSettlementTradeList, 
                                             const BFDataGroupId& idDataGroup,bool bInq /* = true */,bool bRemObj  /* = true */)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getSettlementTradeList" ) );
   DString dstrKey;  
   buildKey( dstrKey,idDataGroup, 0 );
   if( bRemObj )
   {
      //remove original SettlementList
      setObject( NULL, dstrKey, OBJ_ACTIVITY_NONE, BF::HOST ); 
   }
   pSettlementTradeList = dynamic_cast<SettlementTradeList*>( BFCBO::getObject( dstrKey, idDataGroup ) );
   BFDataGroupId idWorkingDataGroup = idDataGroup;
   if( !pSettlementTradeList )
   {
      if( bInq )
      {

         DString dstrSeachType,dstrValSetType;
         getField(ifds::SearchType,dstrSeachType,idDataGroup,false);
         dstrSeachType.strip();
         getField(ifds::VolSettleType,dstrValSetType,idDataGroup,false);
         dstrValSetType.strip();
         bool bIndividual = true;
         if(dstrValSetType != I_("I") && dstrSeachType == BROKER ) bIndividual = false;

         pSettlementTradeList = new SettlementTradeList( *this );
         pSettlementTradeList->init(idDataGroup,dstrSeachType,bIndividual  );
         //if we inquire the database the group id should be the host
         idWorkingDataGroup = BF::HOST;
      }
      if( pSettlementTradeList )
      {
         if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
         {
            setObject( pSettlementTradeList, dstrKey, OBJ_ACTIVITY_NONE, idWorkingDataGroup ); 
            noticeMe(pSettlementTradeList);
         }
         else
         {
            delete pSettlementTradeList;
            pSettlementTradeList = NULL;
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//***************************************************************************************
SEVERITY Settlement::getSettlementTotalList( SettlementTotalList*& pSettlementTotalList, 
                                             const BFDataGroupId& idDataGroup,bool bInq /* = true */,bool bRemObj)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getSettlementTotalList" ) );
   DString dstrKey;  
   buildKey( dstrKey,idDataGroup, 1 );
   if( bRemObj )
   {
      //remove original SettlementTotalList
      setObject( NULL, dstrKey, OBJ_ACTIVITY_NONE, BF::HOST ); 
   }
   pSettlementTotalList = dynamic_cast<SettlementTotalList*>( BFCBO::getObject( dstrKey, idDataGroup ) );
   BFDataGroupId idWorkingDataGroup = idDataGroup;
   if( !pSettlementTotalList )
   {
      if( bInq )
      {
         pSettlementTotalList = new SettlementTotalList( *this );
         pSettlementTotalList->init( idDataGroup );
         //if we inquire the database the group id should be the host
         idWorkingDataGroup = BF::HOST;
      }
      if( pSettlementTotalList )
      {
         if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
         {
            setObject( pSettlementTotalList, dstrKey, OBJ_ACTIVITY_NONE, idWorkingDataGroup ); 
            noticeMe( pSettlementTotalList );
         }
         else
         {
            delete pSettlementTotalList;
            pSettlementTotalList = NULL;
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//*********************************************************************************
void  Settlement::noticeMe(Noticement* noteObj )

{
   if( noteObj )
   {
      _vecNotice.push_back(noteObj );
      return;
   }
   assert(0);
}

//************************************************************************************
void  Settlement::UserChangeSettle(const MFCanBFCbo* pCbo ,const BFFieldId& idField,const BFDataGroupId& idDataGroup )
{
   NOTICEMENT::iterator   iter =  _vecNotice.begin();


   while( iter != _vecNotice.end() )
   {
      if( *iter )
         (*iter)->UserChangeSettle(pCbo,idField,idDataGroup );
      ++iter;
   }   

}

//************************************************************************************
SEVERITY Settlement::setField( const BFFieldId& idField, const DString& dstrValue,
                               const BFDataGroupId& idDataGroup, bool bFormatted, bool bSideEffect, bool  bCheckCurrentValue)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setField" ) );
   if( idField == ifds::SearchType )
   {
      DString dstrOldValue;
      getField(ifds::SearchType,dstrOldValue,idDataGroup      );
      setFieldNoValidate(ifds::SearchType,dstrValue, BF::HOST );
      if( dstrOldValue == dstrValue )
      {
         setFieldReadOnly( idField,idDataGroup,true ); 
         setFieldsAsReadOnly(  idDataGroup,true );
         return(GETCURRENTHIGHESTSEVERITY());
      }
   }
   BFCBO::setField( idField, dstrValue, idDataGroup, bFormatted, bSideEffect );
   setUpdatedFlag( idField, idDataGroup, false );
   setUpdatedFlag( ifds::SettleCross2, idDataGroup, false );
   setUpdatedFlag( ifds::SettleCross1, idDataGroup, false );
   return(GETCURRENTHIGHESTSEVERITY());
}

//***********************************************************************************
SEVERITY Settlement::validateFundCode(const DString& dstrFundCode1,const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFundCode" ) );
   DString dstrFundCode(dstrFundCode1);
   dstrFundCode.strip();

   FundMasterList* pFundMasterList;
   getMgmtCo().getFundMasterList(pFundMasterList);


   if( pFundMasterList != NULL && !dstrFundCode.empty() )
   {
      if( pFundMasterList->IsFundExist( dstrFundCode, idDataGroup ) == false )
      {
         DString idiStr;
         addIDITagValue( idiStr, I_("FUNDNAME"), dstrFundCode );
         ADDCONDITIONFROMFILEIDI( CND::ERR_FUND_NOT_EFFECTIVE, idiStr );

      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//****************************************************************************************
bool Settlement::hasPermissionForSearchType(const DString& dstrSearchType,bool bInq /*false*/)
{

   DString dstrFunCode;
   if( dstrSearchType == ALL_TRADE || 
		 dstrSearchType == SETTLE_DATE || 
		 dstrSearchType == TRADE_DATE ||
       dstrSearchType == FUND || 
		 dstrSearchType == SETTLE_CURRENCY ||
		 dstrSearchType == EXTERNAL_ID )
   {
      dstrFunCode = UAF::SETTLE_ALL_TRADE;   
   }
   else if( dstrSearchType == ACCOUNT )
   {
      dstrFunCode = UAF::SETTLE_ACCOUNT;
   }
   else if( dstrSearchType == WIRE_ORDER || TRANS_NUMBER )
   {
      dstrFunCode = UAF::SETTLE_WIRE_ORDER;
   }
   else if( dstrSearchType == BROKER || dstrSearchType == EPA_BROKER )
   {
      dstrFunCode = UAF::SETTLE_BROKER;   
   }

   setFieldNoValidate(ifds::SettlePermCode, dstrFunCode, BF::HOST, false);

   bool bRet = false;   
   if( bInq )  // check Inq
   {
      bRet = getWorkSession().hasReadPermission( dstrFunCode );
      return(bRet);
   }
   // has settlement permission
   bRet = getWorkSession().hasUpdatePermission( dstrFunCode );

   return(bRet);
}

//****************************************************************************
SEVERITY Settlement::validateSearchType(DString dstrValue, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateSearchType" ) );
   DString dstrType,dstrTypeDesc;
   getField(ifds::SearchType,dstrType,idDataGroup,false);
   getField(ifds::SearchType,dstrTypeDesc,idDataGroup,true);
   dstrType.strip();
   if( !hasPermissionForSearchType(dstrType,true) )
   {
      ADDCONDITIONFROMFILEIDI( CND::ERR_HAS_NO_INQ_PERMISSION_FOR_SETTLEMENT, DString(I_("SEARCH_TYPE=")) + dstrTypeDesc ); 
   }
   else if( !hasPermissionForSearchType(dstrType) )
   {
      ADDCONDITIONFROMFILEIDI( CND::ERR_WARN_HAS_NO_SETTLE_PERMISSION, DString(I_("SEARCH_TYPE=")) + dstrTypeDesc );     
   }
   return(GETCURRENTHIGHESTSEVERITY());
}


//****************************************************************************
SEVERITY Settlement::initBatchList(const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initBatchList" ) );

	BFData requestData(ifds::DSTC0124_REQ);
	DString mgmtCoIdOut;
	DString dstrBatchName;

	requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );

	BFData responseData(ifds::DSTC0124_VW);

	SEVERITY sevRtn = BFDataBroker::getInstance( )->receive (DSTC_REQUEST::ACTIVE_BATCH, requestData, 
                                                             responseData, DSTCRequestor( getSecurity(), true) );

	if( sevRtn <= WARNING )
	{
      responseData.getElementValue( ifds::rxBatchName, dstrBatchName );
      dstrBatchName.strip ();
      setFieldNoValidate(ifds::rxBatchName,dstrBatchName, idDataGroup,false);
	};

	DString autoBatching;
		
	getWorkSession ().getOption (ifds::AutoBatch, autoBatching, BF::HOST, false);
	getWorkSession().getBatchList (pBatchInfoList, idDataGroup);

	bool bReadOnly = autoBatching.asInteger () == AUTO_BATCHING ? false : true;

	if (pBatchInfoList)
	{
		DString batchList;

		pBatchInfoList->getSubstitionList(batchList, dstrBatchName, idDataGroup);
		setFieldAllSubstituteValues (ifds::rxBatchName, idDataGroup, batchList);
	}

	setFieldReadOnly (ifds::rxBatchName, idDataGroup, bReadOnly);

	return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************
SEVERITY Settlement::validateSettleDate(const DString& dstrSettleDate,const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initBatchList" ) );

   DString strCurBusDate, searchType, searchTypeFmt;
   getWorkSession().getOption( ifds::CurrBusDate, strCurBusDate, idDataGroup, false );
   getField( ifds::SearchType, searchType, idDataGroup, false );
   getField( ifds::SearchType, searchTypeFmt, idDataGroup, true );

   searchType.strip().upperCase();

   if( DSTCommonFunctions::CompareDates( strCurBusDate, dstrSettleDate ) == DSTCommonFunctions::SECOND_EARLIER && 
      searchType == EPA_BROKER )
   {
      DString idiStr;
      addIDITagValue( idiStr, I_("SEARCH_TYPE"), searchTypeFmt );
      ADDCONDITIONFROMFILEIDI( CND::ERR_BACKDATED_NOT_ALLOWED_FOR_SEARCH_TYPE, idiStr );     
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************
//               Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/Settlement.cpp-arc  $
// 
//    Rev 1.35   Apr 27 2012 09:53:48   if991250
// CPF - Account Setup & Settlement 
// 
//    Rev 1.34   Jan 11 2011 13:09:42   dchatcha
// IN# 2386596 - EPA Settlement Screen.EPA Broker nbr field s/b defaulted to ALL instead of Blank.
// 
//    Rev 1.33   Dec 13 2010 05:59:52   dchatcha
// P0175716 FN02 - Client Name Redemption, filter out 'Broker code not found' condition.
// 
//    Rev 1.32   Dec 09 2010 15:07:38   jankovii
// IN 2339013 - P0175778: Uptreaming QA testing
// 
//    Rev 1.31   Dec 06 2010 11:30:48   dchatcha
// P0175716 FN02 - Client Name Redemption - EPA Auto Settlement, default broker to 'All' for search type 'EP'
// 
//    Rev 1.30   Dec 01 2010 06:14:50   dchatcha
// P0175716 FN02 - Client Name Redemption - EPA Auto Settlement.
// 
//    Rev 1.29   May 26 2009 14:16:44   jankovii
// PET 159770 FN05 Auto Batching.
// 
//    Rev 1.28   May 12 2009 13:52:26   jankovii
// PET 159770 FN05 Auto Batching.
// 
//    Rev 1.27   Apr 25 2005 17:46:30   ZHANGCEL
// PET 1190 - FN06 -- Settltment by TransNum enhancement
// 
//    Rev 1.26   Nov 14 2004 14:53:58   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.25   Sep 07 2004 15:01:58   VADEANUM
// PET 1094 FN4 - Activest Bank Interface.
// 
//    Rev 1.24   May 27 2003 18:29:54   popescu
// due to several memory leaks found in some list getters at the DSTCWorkSession level caused by copy/paste, I've created a common template function to retrieve the dependent objects
// 
//    Rev 1.23   Apr 07 2003 15:13:44   FENGYONG
// Add Field ClassCode, SINGLESEARCH type, setparameters function
// 
//    Rev 1.22   Mar 21 2003 18:23:52   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.21   Dec 11 2002 16:53:34   YINGBAOL
// fix individual Settlement
// 
//    Rev 1.20   Oct 09 2002 23:54:58   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.19   Oct 08 2002 15:55:48   YINGBAOL
// sync. version 1.7.1.0
// 
//    Rev 1.18   Sep 30 2002 11:01:16   PURDYECH
// BFFieldId no longer has operator long(), so explicit getId() calls are needed in places.
// 
//    Rev 1.17   Sep 11 2002 09:52:28   KOVACSRO
// Added SettlePermCode
// 
//    Rev 1.16   Aug 29 2002 12:56:36   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.15   Aug 16 2002 13:57:42   YINGBAOL
// add permission check
// 
//    Rev 1.14   Aug 08 2002 15:01:38   YINGBAOL
// fix PTS10009129
// 
//    Rev 1.13   Jul 11 2002 10:15:34   YINGBAOL
// change error message
// 
//    Rev 1.12   Jul 05 2002 13:44:40   YINGBAOL
// add validation for fundcode
// 
//    Rev 1.11   Jun 27 2002 13:29:00   YINGBAOL
// more fix
// 
//    Rev 1.10   Jun 20 2002 14:04:06   YINGBAOL
// more clean up
// 
//    Rev 1.9   Jun 18 2002 12:28:36   YINGBAOL
// code clean up
// 
//    Rev 1.8   Jun 17 2002 17:02:58   YINGBAOL
// set settlecurrency as readonly after search
// 
//    Rev 1.7   Jun 17 2002 16:07:28   YINGBAOL
// setfieldProperty first
// 
//    Rev 1.6   Jun 15 2002 15:47:18   YINGBAOL
// handle Settle currency and FundCode etc.
// 
//    Rev 1.5   Jun 14 2002 14:38:56   YINGBAOL
// change search type from FD to FN etc
// 
//    Rev 1.4   Jun 13 2002 15:53:20   YINGBAOL
// change view 200 
// 
//    Rev 1.3   Jun 11 2002 11:42:38   YINGBAOL
// more business rules added
// 
//    Rev 1.2   Jun 06 2002 16:08:22   YINGBAOL
// save work
//



//
















