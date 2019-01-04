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
//    Copyright 2004 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : FundBroker.cpp
// ^AUTHOR : 
// ^DATE   : July 21, 2004
//
// ^CLASS    : FundBroker
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "FundBroker.hpp"
#include "FundBrokerList.hpp"
#include "FundBrokerFeeList.hpp"
#include "FundMgmtSettlementInstrList.hpp"
#include "FundBrokerSettlementInstrList.hpp"

#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"

#include <ifastdataimpl\dse_dstc0326_req.hpp>
#include <ifastdataimpl\dse_dstc0326_vw.hpp>
#include <ifastdataimpl\dse_dstc0320_req.hpp>
#include <ifastdataimpl\dse_dstc0322_vw.hpp>
#include <ifastdataimpl\dse_dstc0322_req.hpp>

#include "AddressEntityList.hpp"
#include "Entity.hpp"
#include "WorkSessionEntityList.hpp"
#include "EntityIdsList.hpp"


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest FUND_BROKER_LIST;
   extern CLASS_IMPORT const DSTCRequest NEXT_FUND_BROKER;
}

namespace  
{
   const I_CHAR * const CLASSNAME				= I_( "FundBroker" );
   const I_CHAR * const YES						= I_("Y");   
   const I_CHAR * const NO						= I_("N");   
   const I_CHAR * const IDI_CODE					= I_("CODE");   
   const I_CHAR * const INVESTRO = I_( "02" );
   const I_CHAR * const SWIFT = I_( "03" );
   const I_CHAR * const SWFX = I_( "05" );
   const I_CHAR * const KVACCOUNTNUM = I_("09");
   const I_CHAR * const BICCODE = I_("10");
}

namespace ifds
{   

   extern CLASS_IMPORT const BFTextFieldId City;
   extern CLASS_IMPORT const BFTextFieldId CommGroup;
   extern CLASS_IMPORT const BFTextFieldId IdType;   
   extern CLASS_IMPORT const BFTextFieldId Contact;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   
   extern CLASS_IMPORT const BFTextFieldId AddrLine5;
   extern CLASS_IMPORT const BFTextFieldId LastName;
   extern CLASS_IMPORT const BFTextFieldId IdType;
   extern CLASS_IMPORT const BFTextFieldId CompoundDate;
   extern CLASS_IMPORT const BFTextFieldId EmployeeClass;
   extern CLASS_IMPORT const BFTextFieldId Changed;
   extern CLASS_IMPORT const BFTextFieldId Nationality;
   extern CLASS_IMPORT const BFDateFieldId DofBirth;
   extern CLASS_IMPORT const BFTextFieldId OccupationCode;
   extern CLASS_IMPORT const BFTextFieldId TaxJuris;
   extern CLASS_IMPORT const BFNumericFieldId FundBrokerOffsetTime;
}

namespace CND
{  // Conditions used
   extern const long ERR_EFF_DATE_LATE_THAN_STOP_DATE;
   extern const long ERR_ID_INFO_IS_MANDATORY_FOR_ROUTINGTYPE;
   extern const long ERR_CONTACT_PERSON_LASTNAME_CANNOT_BE_BLANK;
   extern const long ERR_BEWAREOF_PENDINGTRADE;
   extern const long ERR_DATE_EARLIER_THAN_CURRENT_BUS_DAY;
   extern const long ERR_STOP_DATE_LESS_THAN_DEFF;
   extern const long ERR_EFFECTIVE_DATE_BACKWARD;
   extern const long ERR_STOP_DATE_BACKWARD;
   extern const long ERR_EFFECTIVE_DATE_FORWARD;
   extern const long ERR_ID_TYPE_REQUIRED_FOR_FUNDBROKER;
   extern const long ERR_FUND_BROKER_SETTLEMENT_INSTR_MISSING;
   extern const long ERR_INVALID_FUNDBROKER_OFFSETTIME;
   extern const long WARN_OFFSET_CUTOFFTIME_LATER_THAN_MARKET_CUTOFFTIME;
   extern const long ERR_OFFSET_CUTOFFTIME_LATER_THAN_MARKET_CUTOFFTIME;
}
namespace IFASTERR
{
   extern CLASS_IMPORT I_CHAR * const BROKER_OFFSET_CUTOFFTIME_LATER_THAN_MARKET_CUTOFFTIME;
}
//-------------------------------------------------------------------
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,            State Flags,             Group Flags    
   { ifds::FundBrokerCode,		BFCBO::REQUIRED,	0 }, 
   { ifds::Name,		      BFCBO::REQUIRED,	0 },   
   { ifds::FirstName,           BFCBO::NONE,	0 },
   { ifds::WhereUseFundBrokerRId,   BFCBO::NONE,	0 },
   { ifds::EntityId,		   BFCBO::NONE,	0 },      

   { ifds::AddrId,              BFCBO::NONE,	0 },   
   { ifds::EntityAddrVer,         BFCBO::NONE,	0 },   
   { ifds::AddrLine1,        BFCBO::REQUIRED,   0 }, 
   { ifds::AddrLine2,		   BFCBO::REQUIRED,	0 },
   { ifds::AddrLine3,		   BFCBO::NONE,	0 },
   { ifds::AddrLine4,		   BFCBO::NONE,	0 },
   { ifds::AddrLine5,		   BFCBO::NONE,	0 },   
   { ifds::Country,		         BFCBO::NONE,	0 },
   { ifds::PostalCode,		      BFCBO::NONE,	0 },

   { ifds::Contact1EntityID,		      BFCBO::NONE,	0 },
   { ifds::Contact1EntityVersion,	      BFCBO::NONE,	0 },
   { ifds::WhereUseContact1RecId,     BFCBO::NONE,	0 },

   { ifds::Contact2EntityID,		      BFCBO::NONE,	0 },
   { ifds::Contact1EntityVersion,	      BFCBO::NONE,	0 },
   { ifds::WhereUseContact2RecId,     BFCBO::NONE,	0 },

   { ifds::PriceType,		      BFCBO::REQUIRED,	0 },
   { ifds::RoutingType,	      BFCBO::REQUIRED,	0 },
   { ifds::PUEVCapable,         BFCBO::REQUIRED,	0 },
   { ifds::Remarks1,  	      BFCBO::NONE,	0 },
   { ifds::EffectiveDate,	      BFCBO::REQUIRED,	0 },
   { ifds::StopDate,	      BFCBO::REQUIRED,	0 },
   { ifds::ModDate,             BFCBO::NONE,	0 },
   { ifds::Username,            BFCBO::NONE,	0 },
   { ifds::ModUser,             BFCBO::NONE,	0 },
   { ifds::VersionNum,	   	   BFCBO::NONE,	0 },
   { ifds::FrClearingMethod,	   BFCBO::NONE,	0 },
   { ifds::CompoundDate,		   BFCBO::IMMEDIATE_VALIDATION,   0 },   
   { ifds::SetFundToInvestr,	   BFCBO::NONE,	0 },
   { ifds::Changed,	   BFCBO::CALCULATED_FIELD,	0 },
   { ifds::FundBrokerOffsetTime,   BFCBO::NONE,	0 }, 
	{ ifds::RegAddrID,				BFCBO::NONE,	0 },
	{ ifds::RegEntityAddrVersion,	BFCBO::NONE,	0 },
	{ ifds::IdType,					BFCBO::NONE,	0 }, 
	{ ifds::RegAddrLine1,			BFCBO::NONE,	0 },
	{ ifds::RegAddrLine2,			BFCBO::NONE,	0 },
	{ ifds::RegAddrLine3,			BFCBO::NONE,	0 },
	{ ifds::RegAddrLine4,			BFCBO::NONE,	0 },
	{ ifds::RegPostalCode,		    BFCBO::NONE,	0 },
	{ ifds::RegCountry,				BFCBO::NONE,	0 },
	{ ifds::FbDealer,				BFCBO::NONE,	0 },
	{ ifds::FbAgent,				BFCBO::NONE,	0 },
	{ ifds::FbBranch,				BFCBO::NONE,	0 },
	{ ifds::FbPortfolio,			BFCBO::NONE,	0 },
	{ ifds::AcctServicer,			BFCBO::NONE,	0 },
	{ ifds::RegName,				BFCBO::NONE,	0 },
	{ ifds::RegAcct,				BFCBO::NONE,	0 },
	{ ifds::FbAcctDesig,			BFCBO::NONE,	0 },
	{ ifds::FbSettleType,			BFCBO::NONE,	0 },
	{ ifds::FbTemplate,				BFCBO::NONE,	0 },
	{ ifds::FbTagent,				BFCBO::NONE,	0 },
	{ ifds::FbFndCmpny,				BFCBO::NONE,	0 },
	{ ifds::FbType,					BFCBO::NONE,	0 },
	{ ifds::FbClientGrp,			BFCBO::NONE,	0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );


const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = {
//  Object Label,            State Flags,           Group Flags 
   {  I_(""),        BFCBO::REQUIRED,         0}
};

static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );

FundBroker::FundBroker( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
,_initEffectiveDate(NULL_STRING)
,_initStopDate(NULL_STRING)
,_fundBrokerCode(NULL_STRING)
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL );

   addCrossEdit(ifds::CompoundDate, ifds::EffectiveDate);
   addCrossEdit(ifds::CompoundDate, ifds::StopDate);

}
//******************************************************************************************
FundBroker::~FundBroker()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}     

//************************************************************************************
SEVERITY FundBroker::InitNew( const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "InitNew" ) );
   
   //call view 322 get next FundBrokerCode
   getNextFundBrokerCode( idDataGroup );
  
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************************
SEVERITY FundBroker::Init(const BFData& data)

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init(BFData&)" ) );  
   
   attachDataObject(const_cast<BFData&>(data), false);  

   setFieldReadOnly(ifds::FundBrokerCode,BF::HOST,true);
   RoutingTypeRelateChange( BF::HOST );
   setFieldNoValidate(ifds::SetFundToInvestr,NO, BF::HOST );

   data.getElementValue( ifds::EffectiveDate, _initEffectiveDate );
   data.getElementValue( ifds::StopDate, _initStopDate );

   return(GETCURRENTHIGHESTSEVERITY());
}


//***********************************************************************************
SEVERITY FundBroker::doValidateField( const BFFieldId &idField,
                                    const DString& strValue,
                                    const BFDataGroupId& idDataGroup )

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );

	if ( idField == ifds::FundBrokerCode )
		validateFundBrokerCode( strValue, idDataGroup );
   if ( idField == ifds::CompoundDate )
      validateEffectiveStopDate( idDataGroup );
   if ( idField == ifds::StopDate )
   {
	   DString dstrHasPendingTrades;
	   DString dstrLatestPendingTradeDeff;
	   getField(ifds::HasPendingTrades, dstrHasPendingTrades, idDataGroup);
	   getField(ifds::LatestPendingTradeDeff, dstrLatestPendingTradeDeff, idDataGroup);

	   if (!isNew() && 
		   dstrHasPendingTrades.strip() == I_("Y") &&
		   !dstrLatestPendingTradeDeff.empty() &&
		   DSTCommonFunctions::CompareDates(dstrLatestPendingTradeDeff, strValue) 
					!= DSTCommonFunctions::FIRST_EARLIER )
	   {
			ADDCONDITIONFROMFILE( CND::ERR_BEWAREOF_PENDINGTRADE );
	   }

		DString dstrCurrBusDate;
		getWorkSession().getOption (ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false);

		if( DSTCommonFunctions::CompareDates( strValue, dstrCurrBusDate ) == DSTCommonFunctions::FIRST_EARLIER )
		{
			// Date earlier then Current Business Date
			ADDCONDITIONFROMFILE( CND::ERR_DATE_EARLIER_THAN_CURRENT_BUS_DAY );
		}
   }
   if( idField == ifds::EffectiveDate )
   {
      if( isNew() )
      {
         DString dstrCurrBusDate;
	      getWorkSession().getOption (ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false);
         if( DSTCommonFunctions::CompareDates( strValue, dstrCurrBusDate ) == DSTCommonFunctions::FIRST_EARLIER )
         {
            ADDCONDITIONFROMFILE(CND::ERR_EFFECTIVE_DATE_BACKWARD);
         }
      }
      else
      {         
         int ret;
         if ((ret = DSTCommonFunctions::CompareDates(_initEffectiveDate, strValue )) == 
             DSTCommonFunctions::FIRST_EARLIER)
         {
            ADDCONDITIONFROMFILE(CND::ERR_EFFECTIVE_DATE_FORWARD);
         }
      }
   }
   if( idField == ifds::FundBrokerOffsetTime )
   {
	   DString dstrFundBrokerOffsetTime;
	   getField(ifds::FundBrokerOffsetTime, dstrFundBrokerOffsetTime, idDataGroup);
	   double offsetTime = DSTCommonFunctions::convertToDouble(dstrFundBrokerOffsetTime);
	   if( (offsetTime > 1439) || (offsetTime < (-1439)) )
	   {
		   ADDCONDITIONFROMFILE(CND::ERR_INVALID_FUNDBROKER_OFFSETTIME);
	   }
	   else if( offsetTime > 0 )
	   {
		   getErrMsg ( IFASTERR::BROKER_OFFSET_CUTOFFTIME_LATER_THAN_MARKET_CUTOFFTIME,
                              CND::ERR_OFFSET_CUTOFFTIME_LATER_THAN_MARKET_CUTOFFTIME,
                              CND::WARN_OFFSET_CUTOFFTIME_LATER_THAN_MARKET_CUTOFFTIME,
                              idDataGroup ); 
	   }	  
   }
	return(GETCURRENTHIGHESTSEVERITY());

}

//******************************************************************************************************
SEVERITY FundBroker::validateEffectiveStopDate( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFundBrokerCode" ) );

   DString EffectiveDate, StopDate;
   getField(ifds::StopDate, StopDate, idDataGroup);
   getField(ifds::EffectiveDate, EffectiveDate, idDataGroup);

   if( DSTCommonFunctions::CompareDates( StopDate, EffectiveDate ) 
       == DSTCommonFunctions::FIRST_EARLIER )
      ADDCONDITIONFROMFILE( CND::ERR_STOP_DATE_LESS_THAN_DEFF );	

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************************************
SEVERITY FundBroker::validateFundBrokerCode ( const DString& dstrFundBrokerCode, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateFundBrokerCode" ) );
	//duplicate checking
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************************************
		
SEVERITY FundBroker::validateEntityName ( const DString& dstrFundBrokerName, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateEntityName" ) );
	//if existing entity,  entity name != current name, warning you are changing name for existing entity.
   
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************************
void FundBroker::setFieldsReadOnly(const BFDataGroupId& idDataGroup, bool bReadOnly) 
{

}
//*****************************************************************************************
SEVERITY FundBroker::doApplyRelatedChanges( const BFFieldId &idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );

   if( idField == ifds::EntityId )
   {      
      DString dstrEntityID;
      getField(ifds::EntityId,dstrEntityID,idDataGroup );
            
      if( dstrEntityID != NULL_STRING )
      {         
         dstrEntityID.stripLeading( '0' );
         Entity* pEntity;
         AddressEntityList * pAddressList;
         if( getWorkSession().getEntity( idDataGroup, dstrEntityID, pEntity ) <= WARNING )
         {
            if(pEntity && !pEntity->isNew())
            {
               DString dstrEntityName;
               pEntity->getField(ifds::LastName,dstrEntityName,idDataGroup,false);
               setFieldNoValidate(ifds::Name,dstrEntityName, idDataGroup );			   
            
               //get entity from worksession, set version and whereusedrecid
               pEntity->getAddressEntityList(pAddressList,idDataGroup, true);
               BFObjIter iterEntityAddrlist(*pAddressList, idDataGroup );
               DString  addressline1,addressline2,addressline3, addressline4, postalcode, country, province, addrId, entityAddrVer,
				        regaddressline1,regaddressline2,regaddressline3, regaddressline4, regpostalcode, regcountry, regprovince, 
						regaddrId, regentityAddrVer;
               if( !iterEntityAddrlist.end() ) 
               {               
				  iterEntityAddrlist.getObject( )->getField(ifds::AddrId, addrId, idDataGroup,false );
                  addrId.strip();
                  setFieldNoValidate (ifds::AddrId, addrId, idDataGroup, false);

			      iterEntityAddrlist.getObject( )->getField(ifds::AddrLine1, addressline1, idDataGroup,false );
                  addressline1.strip();
                  setFieldNoValidate (ifds::AddrLine1, addressline1, idDataGroup, false);
                  iterEntityAddrlist.getObject( )->getField(ifds::AddrLine2, addressline2, idDataGroup,false );
                  addressline2.strip();
                  setFieldNoValidate (ifds::AddrLine2, addressline2, idDataGroup, false);
                  iterEntityAddrlist.getObject( )->getField(ifds::AddrLine3, addressline3, idDataGroup,false );
                  addressline3.strip();
                  setFieldNoValidate (ifds::AddrLine3, addressline3, idDataGroup, false);
                  iterEntityAddrlist.getObject( )->getField(ifds::City, addressline4, idDataGroup,false );
                  addressline3.strip();
                  setFieldNoValidate (ifds::AddrLine4, addressline4, idDataGroup, false);
                  iterEntityAddrlist.getObject( )->getField(ifds::Country, country, idDataGroup,false );
                  addressline3.strip();
                  setFieldNoValidate (ifds::Country, country, idDataGroup, false);
                  iterEntityAddrlist.getObject( )->getField(ifds::PostalCode, postalcode, idDataGroup,false );
                  addressline3.strip();
                  setFieldNoValidate (ifds::PostalCode, postalcode, idDataGroup, false);

				  iterEntityAddrlist.getObject( )->getField(ifds::EntityAddrVer, entityAddrVer, idDataGroup,false );
                  entityAddrVer.strip();
                  setFieldNoValidate (ifds::EntityAddrVer, entityAddrVer, idDataGroup, false);

				  iterEntityAddrlist.getObject( )->getField(ifds::RegAddrID, regaddrId, idDataGroup,false );
                  addrId.strip();
                  setFieldNoValidate (ifds::RegAddrID, regaddrId, idDataGroup, false);

			      iterEntityAddrlist.getObject( )->getField(ifds::RegAddrLine1, regaddressline1, idDataGroup,false );
                  regaddressline1.strip();
                  setFieldNoValidate (ifds::RegAddrLine1, regaddressline1, idDataGroup, false);
                  iterEntityAddrlist.getObject( )->getField(ifds::RegAddrLine2, regaddressline2, idDataGroup,false );
                  regaddressline2.strip();
                  setFieldNoValidate (ifds::RegAddrLine2, regaddressline2, idDataGroup, false);
                  iterEntityAddrlist.getObject( )->getField(ifds::RegAddrLine3, regaddressline3, idDataGroup,false );
                  regaddressline3.strip();
                  setFieldNoValidate (ifds::RegAddrLine3, regaddressline3, idDataGroup, false);
                  iterEntityAddrlist.getObject( )->getField(ifds::RegProvince, regaddressline4, idDataGroup,false );
                  regaddressline3.strip();
                  setFieldNoValidate (ifds::RegAddrLine4, regaddressline4, idDataGroup, false);
                  iterEntityAddrlist.getObject( )->getField(ifds::Country, country, idDataGroup,false );
                  regaddressline3.strip();
                  setFieldNoValidate (ifds::RegCountry, regcountry, idDataGroup, false);
                  iterEntityAddrlist.getObject( )->getField(ifds::RegPostalCode, regpostalcode, idDataGroup,false );
                  addressline3.strip();
                  setFieldNoValidate (ifds::RegPostalCode, regpostalcode, idDataGroup, false);

				  iterEntityAddrlist.getObject( )->getField(ifds::RegEntityAddrVersion, regentityAddrVer, idDataGroup,false );
                  regentityAddrVer.strip();
                  setFieldNoValidate (ifds::RegEntityAddrVersion, regentityAddrVer, idDataGroup, false);
               }
               else
               {
                  setFieldNoValidate (ifds::AddrLine1, NULL_STRING, idDataGroup, false);
                  setFieldNoValidate (ifds::AddrLine2, NULL_STRING, idDataGroup, false);
                  setFieldNoValidate (ifds::AddrLine3, NULL_STRING, idDataGroup, false);
                  setFieldNoValidate (ifds::AddrLine4, NULL_STRING, idDataGroup, false);
                  setFieldNoValidate (ifds::Country, NULL_STRING, idDataGroup, false);
                  setFieldNoValidate (ifds::PostalCode, NULL_STRING, idDataGroup, false);
				  setFieldNoValidate (ifds::RegAddrLine1, NULL_STRING, idDataGroup, false);
                  setFieldNoValidate (ifds::RegAddrLine2, NULL_STRING, idDataGroup, false);
                  setFieldNoValidate (ifds::RegAddrLine3, NULL_STRING, idDataGroup, false);
                  setFieldNoValidate (ifds::RegAddrLine4, NULL_STRING, idDataGroup, false);
                  setFieldNoValidate (ifds::RegCountry, NULL_STRING, idDataGroup, false);
                  setFieldNoValidate (ifds::RegPostalCode, NULL_STRING, idDataGroup, false);
               }
            }
			else if( pEntity && pEntity->isNew())
			{
				  pEntity->setField(ifds::EmployeeClass,I_("02"), idDataGroup ); //Corporate
				  pEntity->setFieldUpdated( ifds::EmployeeClass, idDataGroup, false );
				  pEntity->setFieldValid( ifds::Nationality, idDataGroup, true );
				  pEntity->setFieldValid( ifds::DofBirth, idDataGroup, true );
				  pEntity->setFieldValid( ifds::OccupationCode, idDataGroup, true );
				  pEntity->setFieldValid( ifds::TaxJuris, idDataGroup, true );				  
			}
         }
      }
   }
   if( idField == ifds::Contact1EntityID )
   {
      //get entity from worksession, set version and whereusedrecid
   }
   if( idField == ifds::Contact2EntityID )
   {
      //get entity from worksession, set version and whereusedrecid
   }
   if( idField == ifds::RoutingType )
   {
      RoutingTypeRelateChange( idDataGroup ); 
   }
   if( idField == ifds::Changed )
   {
	   setFieldUpdated (ifds::Changed, idDataGroup, false);
   }      
	return(GETCURRENTHIGHESTSEVERITY()); 
}

//******************************************************************************
void FundBroker::RoutingTypeRelateChange( const BFDataGroupId& idDataGroup )
{
      DString dstrEntityId, dstrRoutingType;
      getField(ifds::EntityId,dstrEntityId,idDataGroup );
      getField(ifds::RoutingType,dstrRoutingType,idDataGroup );
      dstrEntityId.strip().stripLeading( '0' );
      dstrRoutingType.strip();
      if( dstrEntityId != NULL_STRING && dstrRoutingType != NULL_STRING )
      {         
         Entity* pEntity;
         if( getWorkSession().getEntity( idDataGroup, dstrEntityId, pEntity ) <= WARNING )
         {
            EntityIdsList* pEntityIdsList;
            pEntity->getEntityIdsList(pEntityIdsList, idDataGroup, true);
            pEntityIdsList->setField(ifds::RoutingType, dstrRoutingType, idDataGroup, false);            
         } 
		 //AFT Out Bound   For fax only enable the selection with default value DE
		 if(dstrRoutingType == I_("01"))
		 {
			 DString strTemplate = NULL_STRING;
			 setFieldReadOnly(ifds::FbTemplate,idDataGroup,false);
			 getField(ifds::FbTemplate,strTemplate,idDataGroup);
			 if(strTemplate == NULL_STRING)
				setFieldNoValidate(ifds::FbTemplate,I_("DE"), idDataGroup);

		 }
		 else
		 {
			 setFieldReadOnly(ifds::FbTemplate,idDataGroup,true);     
			 setFieldNoValidate(ifds::FbTemplate,NULL_STRING, idDataGroup );  			
		 }	
      } 
	  if( idDataGroup != BF::HOST )
	  {
			setField(ifds::Changed, YES, idDataGroup, false);
	  }
}
//******************************************************************************

void FundBroker::doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
{
   DString stopDate, dstrCurrBusDate;

   setFieldRequired (ifds::FundBrokerCode, idDataGroup, true );
   setFieldRequired (ifds::Name, idDataGroup, true );   

   setFieldRequired (ifds::EffectiveDate, idDataGroup, true );   
   
   getWorkSession ().getOption (ifds::CurrBusDate, dstrCurrBusDate, idDataGroup, false);
   setFieldNoValidate (ifds::EffectiveDate, dstrCurrBusDate, idDataGroup, false);
   getWorkSession().getDateInHostFormat (stopDate, DSTCWorkSession::DATE_TYPE::DAY12319999, idDataGroup);
   setFieldNoValidate (ifds::StopDate, stopDate, idDataGroup, false );

   // For Reset, Fund Broker code will be flushed and 
   // we don't need to call vew322 to get next fundbroker code
   // So, get it from _fundBrokerCode temp which is assigned in initNew()
   setFieldNoValidate (ifds::FundBrokerCode, 
			_fundBrokerCode.strip (), idDataGroup, false, true, true); 

   setFieldReadOnly(ifds::FundBrokerCode,idDataGroup,true);
   setFieldReadOnly(ifds::FbTemplate,BF::HOST,true);        
   setFieldNoValidate(ifds::FbTemplate,NULL_STRING, BF::HOST ); 
   WorkSessionEntityList *pWorkSessionEntityList = NULL;
   if (getWorkSession().getWorkSessionEntityList ( pWorkSessionEntityList) <= WARNING && pWorkSessionEntityList)
   {
      Entity * pEntity;	  
      DString tempentityID;
      pWorkSessionEntityList->fromFundBroker(true);
      pWorkSessionEntityList->getNewEntity(idDataGroup, pEntity);
      pEntity->getEntityId (tempentityID);
      //pEntity->getField(ifds::EntityId,tempentityID,idDataGroup);
      setField( ifds::EntityId, tempentityID, idDataGroup, false );      
   }    
}

//*****************************************************************************************
SEVERITY FundBroker::getNextFundBrokerCode( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getFundClassHoldingsList" ) );

	BFData query322 (ifds::DSTC0322_REQ);
	BFData *response = new BFData (ifds::DSTC0322_VW);
	const DSTCSecurity* pSecurity =  dynamic_cast<const DSTCSecurity *> (getSecurity ());
	DString mgmtCoIdOut;

	query322.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));
	query322.setElementValue (ifds::Track, I_("N"));
	query322.setElementValue (ifds::Activity, NULL_STRING );
	if (BFDataBroker::getInstance ()->receive ( DSTC_REQUEST::NEXT_FUND_BROKER, query322, 
		*response, DSTCRequestor (getSecurity ())) <= WARNING)
	{
		response->getElementValue (ifds::FundBrokerCode, _fundBrokerCode);
	}

	delete response;
	response = NULL;

   return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************************
SEVERITY FundBroker::getFundBrokerFeeList( FundBrokerFeeList *&pFundBrokerFeeList, 
													const BFDataGroupId& idDataGroup,
													bool inquireDatabase /*= true */)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getFundClassHoldingsList" ) );

   DString dstrFundBrokerCode;
   getField(ifds::FundBrokerCode,dstrFundBrokerCode,idDataGroup,false);

   pFundBrokerFeeList = dynamic_cast<FundBrokerFeeList*>(BFCBO::getObject( I_( "FundBrokerFeeList" ), idDataGroup ) );
   BFDataGroupId tDataGroup = idDataGroup;
   if( !pFundBrokerFeeList )
   {
	 if( isNew() )
	 {
		  pFundBrokerFeeList = new FundBrokerFeeList( *this );
		  pFundBrokerFeeList->InitNew(tDataGroup);
	 }	
	 if( inquireDatabase && dstrFundBrokerCode != NULL_STRING )
	 {
		  pFundBrokerFeeList = new FundBrokerFeeList( *this );
		  pFundBrokerFeeList->init(dstrFundBrokerCode, idDataGroup );
		  tDataGroup = BF::HOST;
	 }
	if( pFundBrokerFeeList )
	 {
		 if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
		 {
			setObject( pFundBrokerFeeList, I_( "FundBrokerFeeList" ), 
				OBJ_ACTIVITY_NONE, tDataGroup ); 
		 }
		 else
		 {
			delete pFundBrokerFeeList;
			pFundBrokerFeeList = NULL;
		 }
	  }
   }	 

   return(GETCURRENTHIGHESTSEVERITY());
}

//*********************************************************************************
SEVERITY FundBroker::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );

   DString dstrRoutingType, dstrEntityID, dstrLastName;
   getField(ifds::RoutingType,dstrRoutingType,idDataGroup, false );
   getField(ifds::EntityId,dstrEntityID,idDataGroup );
   dstrEntityID.strip().stripLeading( '0' );
   Entity* pEntity;

   DString dstrIDType = NULL_STRING, dstrIDTypeDesc = NULL_STRING;
   if( dstrRoutingType == INVESTRO ) 
   {
	   dstrIDType = KVACCOUNTNUM;
	   dstrIDTypeDesc = I_("KVACCOUNTNUM");
   }
   if( dstrRoutingType == SWIFT || dstrRoutingType == SWFX) //added
   {
	   dstrIDType = BICCODE;
	   dstrIDTypeDesc = I_("BIC Code");
   }

   //Incident#553694 - remove edit check for Investro - KVAccountNum
   if(( (/*dstrRoutingType == INVESTRO ||*/ dstrRoutingType == SWIFT )||(dstrRoutingType == SWFX)) && (dstrEntityID != NULL_STRING ))
   {      
      if( getWorkSession().getEntity( idDataGroup, dstrEntityID, pEntity ) <= WARNING )
      {
         EntityIdsList* pEntityIdsList;
         pEntity->getEntityIdsList(pEntityIdsList, idDataGroup, true);
         BFObjIter iter(*pEntityIdsList, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );
		 
		 iter.setDataFilter( asString (ifds::IdType.getId() ) + I_("=") + dstrIDType );
		 if( iter.end() )
         {			
		    DString dstrTemp = NULL_STRING;
			addIDITagValue( dstrTemp, I_("IDS"), dstrIDTypeDesc );
			ADDCONDITIONFROMFILEIDI( CND::ERR_ID_TYPE_REQUIRED_FOR_FUNDBROKER, dstrTemp );
         }
      } 
   }

   getField( ifds::Contact1EntityID, dstrEntityID, idDataGroup );
   dstrEntityID.strip().stripLeading( '0' );
            
   if( dstrEntityID != NULL_STRING )
   {
      if( getWorkSession().getEntity( idDataGroup, dstrEntityID, pEntity ) <= WARNING )
      {
         pEntity->getField( ifds::LastName, dstrLastName, idDataGroup );
         dstrLastName.strip();
         if( dstrLastName == NULL_STRING )
         {
            ADDCONDITIONFROMFILE( CND::ERR_CONTACT_PERSON_LASTNAME_CANNOT_BE_BLANK);
         }
      }
   }

   getField( ifds::Contact2EntityID, dstrEntityID, idDataGroup );
   dstrEntityID.strip().stripLeading( '0' );
            
   if( dstrEntityID != NULL_STRING )
   {      
      if( getWorkSession().getEntity( idDataGroup, dstrEntityID, pEntity ) <= WARNING )
      {
         pEntity->getField( ifds::LastName, dstrLastName, idDataGroup );
         dstrLastName.strip();
         if( dstrLastName == NULL_STRING )
         {
            ADDCONDITIONFROMFILE( CND::ERR_CONTACT_PERSON_LASTNAME_CANNOT_BE_BLANK);
         }
      }
   }     

   bool bSettlementInstr = false;   
   FundMgmtSettlementInstrList   *pFundMgmtSettlementInstrList = NULL; 
   if ( getFndMgmtSettlementInstrList( pFundMgmtSettlementInstrList, idDataGroup ) <= WARNING &&
        NULL != pFundMgmtSettlementInstrList )
   {         
      BFObjIter iter( *pFundMgmtSettlementInstrList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
      iter.begin();
      while( !iter.end() )
      {
         if( !iter.isDummy() )
         {
            bSettlementInstr = true;
            break;            
         }
         ++iter;
      }
   }

   /**************
   if ( true == bSettlementInstr )
   {
      FundBrokerSettlementInstrList *pFundBrokerSettlementInstrList = NULL;
      if ( getSettlementInstrList( pFundBrokerSettlementInstrList, idDataGroup ) <= WARNING &&
           NULL != pFundBrokerSettlementInstrList )
      {
         BFObjIter iter( *pFundBrokerSettlementInstrList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
         iter.begin();
         while( !iter.end() )
         {
            if( !iter.isDummy() )
            {
               bSettlementInstr = true;
               break;            
            }
            ++iter;
         }
      }
   }
   **************/

   if ( isUpdated( true ) && false == bSettlementInstr )
   {
      // Missing Settlement Instructions for Fund Broker
      ADDCONDITIONFROMFILE( CND::ERR_FUND_BROKER_SETTLEMENT_INSTR_MISSING );
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//************************************************************************************
SEVERITY FundBroker::setField( const BFFieldId& idField, const DString& dstrValue,
                               const BFDataGroupId& idDataGroup, bool bFormatted, bool bSideEffect, bool  bCheckCurrentValue)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setField" ) );

   if( idField == ifds::EntityId || idField == ifds::Contact1EntityID || idField == ifds::Contact2EntityID)
   {
      DString dstrOldValue;
      getField(idField,dstrOldValue,idDataGroup );
      dstrOldValue.strip().stripLeading( '0' );
      setFieldNoValidate(idField,dstrValue, idDataGroup );
      if( dstrOldValue != NULL_STRING && dstrOldValue != dstrValue )
      {         
         Entity* pEntity;
         if( getWorkSession().getEntity( idDataGroup, dstrOldValue, pEntity ) <= WARNING )
            pEntity->reset(idDataGroup);
      }     

      if( idField == ifds::Contact1EntityID || idField == ifds::Contact2EntityID )
      {
         setFieldUpdated (idField, idDataGroup, true);
      }
      return(GETCURRENTHIGHESTSEVERITY());
   }

   if( idField == ifds::Name )
   {
      BFCBO::setField( idField, dstrValue, idDataGroup, bFormatted, bSideEffect );

      DString dstrEntityName, dstrEntityID;
      getField(ifds::EntityId,dstrEntityID,idDataGroup );            
      
      Entity* pEntity;

      if( dstrEntityID != NULL_STRING )
      {         
         dstrEntityID.stripLeading( '0' );         
         if( getWorkSession().getEntity( idDataGroup, dstrEntityID, pEntity ) <= WARNING )
         {
            pEntity->getField(ifds::LastName,dstrEntityName,idDataGroup,false);
            if( !pEntity->isNew() && dstrEntityName != dstrValue )
            {            
               //warning if entity is used some other places   
            }
            pEntity->setField(ifds::LastName, dstrValue, idDataGroup, false);
            return(GETCURRENTHIGHESTSEVERITY());
         }
      }
      else
      {
         WorkSessionEntityList *pWorkSessionEntityList = NULL;
         if (getWorkSession().getWorkSessionEntityList ( pWorkSessionEntityList) <= WARNING && pWorkSessionEntityList)
         {
            DString tempentityID;
            pWorkSessionEntityList->getNewEntity(idDataGroup, pEntity);
            pEntity->setField(ifds::LastName, dstrValue, idDataGroup, false);            

            pEntity->getEntityId (tempentityID);
            //pEntity->getField(ifds::EntityId,tempentityID,idDataGroup);
            setField( ifds::EntityId, tempentityID, idDataGroup, false );         
         }
      }
   }

   BFCBO::setField( idField, dstrValue, idDataGroup, bFormatted, bSideEffect );

   return(GETCURRENTHIGHESTSEVERITY());
}

//************************************************************************************
SEVERITY FundBroker::getFndMgmtSettlementInstrList( FundMgmtSettlementInstrList *&pFundMgmtSettlementInstrList, 
                                                   const BFDataGroupId &idDataGroup,
                                                   bool bInquireDatabase /*true*/ )
{
   
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getFundMgmtSettlementInstrList" ) ); 

   DString dstrFundBrokerCode;
   getField(ifds::FundBrokerCode,dstrFundBrokerCode,idDataGroup,false);

   pFundMgmtSettlementInstrList = dynamic_cast<FundMgmtSettlementInstrList*>(BFCBO::getObject( I_( "FundMgmtSettlementInstrList" ), idDataGroup ) );

   if( !pFundMgmtSettlementInstrList )
   {
	 if( isNew() )
	 {
		  pFundMgmtSettlementInstrList = new FundMgmtSettlementInstrList( *this );
		  pFundMgmtSettlementInstrList->init( I_(""), dstrFundBrokerCode, idDataGroup );
	 }	
	 else if( bInquireDatabase )
	 {
		  pFundMgmtSettlementInstrList = new FundMgmtSettlementInstrList( *this );
		  pFundMgmtSettlementInstrList->init( I_(""), dstrFundBrokerCode);
	 }
	if( pFundMgmtSettlementInstrList )
	 {
		 if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
		 {
			setObject( pFundMgmtSettlementInstrList, I_( "FundMgmtSettlementInstrList" ), 
				OBJ_ACTIVITY_NONE, idDataGroup ); 
		 }
		 else
		 {
			delete pFundMgmtSettlementInstrList;
			pFundMgmtSettlementInstrList = NULL;
		 }
	  }
   }	 

   return(GETCURRENTHIGHESTSEVERITY());
}

//************************************************************************************
SEVERITY FundBroker::getSettlementInstrList( FundBrokerSettlementInstrList *&pSettlementInstrList, 
                                             const BFDataGroupId &idDataGroup,
                                             bool bInquireDatabase /*true*/ )
{
   
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getSettlementInstrList" ) );

   DString dstrFundBrokerCode;
   getField(ifds::FundBrokerCode,dstrFundBrokerCode,idDataGroup,false);

   pSettlementInstrList = dynamic_cast<FundBrokerSettlementInstrList*>(BFCBO::getObject( I_( "SettlementInstrList" ), idDataGroup ) );

   if( !pSettlementInstrList )
   {
	 if( isNew() )
	 {
		  pSettlementInstrList = new FundBrokerSettlementInstrList( *this );
		  pSettlementInstrList->init( idDataGroup, I_(""), dstrFundBrokerCode );
	 }	
	 else if( bInquireDatabase )
	 {
		  pSettlementInstrList = new FundBrokerSettlementInstrList( *this );
		  pSettlementInstrList->init(I_(""), dstrFundBrokerCode,idDataGroup);
	 }
	 if( pSettlementInstrList )
	 {
		 if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
		 {
			setObject( pSettlementInstrList, I_( "SettlementInstrList" ), 
				OBJ_ACTIVITY_NONE, idDataGroup ); 
		 }
		 else
		 {
			delete pSettlementInstrList;
			pSettlementInstrList = NULL;
		 }
	  }
   }	 

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FundBroker.cpp-arc  $
// 
//    Rev 1.32   Dec 17 2011 19:39:00   wp040133
// P0192479 AFT out bOund Order Ehnacement
// 
//    Rev 1.31   Aug 03 2011 11:25:44   wp040027
// P0186774 - Mutual Fund Order Processing
// 
//    Rev 1.30   Mar 10 2011 08:15:28   wutipong
// IN#2119425 - AFT Fund Broker Stop DAte - Can't modify
// 
//    Rev 1.29   Jan 20 2011 06:56:00   wichian
// IN#2319580 - Update according to code review 579300 w/o.
// 
//    Rev 1.27   Feb 24 2006 14:25:10   popescu
// Incident# 553694 - remove edit check fund broker KV Number set up - per client's request
// 
//    Rev 1.26   Aug 03 2005 13:48:24   Fengyong
// Incident 370407 - Add Addressversion number
// 
//    Rev 1.25   May 02 2005 11:07:50   yingbaol
// Incident300186: EUSD option is not applicable for FundBroker 
// 
//    Rev 1.24   Apr 28 2005 17:26:36   Fengyong
// #Incident 300186 - make TaxJuris not required for fund broker entity
// 
//    Rev 1.23   Feb 04 2005 15:01:08   Fengyong
// PET1117FN54 - set field Employeeclass not update when apply default value for fund broker entity.
// 
//    Rev 1.22   Jan 20 2005 11:09:28   Fengyong
// PET1117 FN54 - SetDofBirth... valid for fund broker entity
// 
//    Rev 1.21   Dec 22 2004 15:58:54   Fengyong
// PET1117FN54 - copy addressId when copy existing entity
// 
//    Rev 1.20   Dec 13 2004 12:28:48   vadeanum
// PET117_FN21: settlement instructions enhancement.
// 
//    Rev 1.19   Dec 10 2004 17:21:12   vadeanum
// PET117_FN21: settlement instructions enhancement.
// 
//    Rev 1.18   Dec 09 2004 19:18:56   vadeanum
// PET1117 FN08 - Fund Broker Settlement Instr.
// 
//    Rev 1.17   Dec 09 2004 15:28:50   Fengyong
// Move the routing type and idtype validation to fund broker cbo,  removed "entity " for the error message "IDType needed for the specific routing type"
// 
//    Rev 1.16   Dec 02 2004 11:51:16   Fengyong
// PET1117FN54 - minor change
// 
//    Rev 1.15   Dec 01 2004 16:29:32   Fengyong
// PET1117 FN54 - minor change
// 
//    Rev 1.14   Dec 01 2004 16:02:34   Fengyong
// PET1117FN54 - minor change
// 
//    Rev 1.13   Nov 30 2004 13:07:08   Fengyong
// Add setfundtoinvestor
// 
//    Rev 1.12   Nov 26 2004 16:56:22   aguilaam
// PET1117_FN21: settlement instructions
// 
//    Rev 1.11   Nov 25 2004 11:52:44   Fengyong
// base data fix chnaged code for pricetype and routing type
// 
//    Rev 1.10   Nov 24 2004 16:49:12   Fengyong
// Initialize stop date
// 
//    Rev 1.9   Nov 23 2004 17:25:04   Fengyong
// PET1117FN54 - adjustment after first day intergretion test
// 
//    Rev 1.8   Nov 19 2004 17:32:30   aguilaam
// PET117_FN21: settlement instructions enhancement (temporary check-in for build)
// 
//    Rev 1.7   Nov 15 2004 16:01:40   Fengyong
// Syncup after .net conversion
// 
//    Rev 1.6   Nov 14 2004 14:41:30   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.5   Nov 09 2004 16:35:50   FENGYONG
// Add Clearing method
// 
//    Rev 1.4   Nov 05 2004 16:23:50   FENGYONG
// IMMEDIATE_VALIDATION for date
// 
//    Rev 1.3   Nov 05 2004 12:22:16   FENGYONG
// Change view number from 319 to 326
// 
//    Rev 1.2   Nov 05 2004 10:50:44   FENGYONG
// view team change the number of view from 319 to 326
// 
//    Rev 1.1   Nov 04 2004 11:01:00   FENGYONG
// PET1117 FN54 - Fund broker static temp check in for 59 build
// 
//    Rev 1.0   Oct 19 2004 14:44:10   FENGYONG
// Initial revision.
*/
