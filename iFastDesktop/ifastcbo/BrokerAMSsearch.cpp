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
//    Copyright 2002 By International Financial Data Services.
//
//
//********************************************************************************
//
// ^FILE   : BrokerAMSsearch.cpp
// ^AUTHOR : 
// ^DATE   : May 24,2002
//
//********************************************************************************
#include "stdafx.h"

#include "BrokerAMSsearch.hpp"
#include "BrokerAMSList.hpp"

#include <ifastdataimpl\dse_dstc0250_vw.hpp>
#include <ifastdataimpl\dse_dstc0250_req.hpp>

#include "broker.hpp"
#include "brokerlist.hpp"
#include "amsmstrlist.hpp"


namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME   = I_( "BrokerAMSsearch" );
   const I_CHAR * const ACCOUNT_NUM = I_( "AccountNum" );
   const I_CHAR * const BROKERAMS_LIST = I_( "BrokerAMSList" );
   const I_CHAR * const YES      = I_( "Y" );

}

namespace CND
{
   extern CLASS_IMPORT const long ERR_DATA_NOT_FOUND;

   extern  const long ERR_FIELD_INVALID_F4_FOR_SEARCH;
   extern  const long ERR_FIELD_MANDATORY_F4_FOR_SEARCH;

}

namespace ifds
{
   //extern CLASS_IMPORT const BFTextFieldId SettleAll;
   extern CLASS_IMPORT const BFTextFieldId BrokerCode;
   extern CLASS_IMPORT const BFTextFieldId BrokerName;
   extern CLASS_IMPORT const BFTextFieldId AMSCode;
}

namespace BROKER_AMS_SEARCH_GROUP
{

   const long BROKER_AMS_SEARCH = 0x0001;

}
const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
//  Field DD Id,					State Flags,			Group Flags 
   { ifds::BrokerCode,      BFCBO::REQUIRED,         BROKER_AMS_SEARCH_GROUP::BROKER_AMS_SEARCH }, 
   { ifds::BrokerName,      BFCBO::NONE,             BROKER_AMS_SEARCH_GROUP::BROKER_AMS_SEARCH}, 
   { ifds::AMSCode,         BFCBO::NONE,             BROKER_AMS_SEARCH_GROUP::BROKER_AMS_SEARCH}, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );


const BFCBO::CLASS_OBJECT_INFO classObjectInfo[] = 
{
   // Object Label,                 State Flags,      Group Flags 
   { I_( "BrokerAMSList" ),    BFCBO::NONE,     0},

};

static const int NUM_OBJECTS = sizeof( classObjectInfo ) / sizeof( BFCBO::CLASS_OBJECT_INFO );

//******************************************************************************

BrokerAMSsearch::BrokerAMSsearch( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );

}

//******************************************************************************

BrokerAMSsearch::~BrokerAMSsearch()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}  
//********************************************************************************   

SEVERITY BrokerAMSsearch::init( const BFDataGroupId& idDataGroup,
   const DString& dstrTrack /*= I_("N")*/, 
   const DString& dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//*************************************************************************************

SEVERITY BrokerAMSsearch::doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField") );
   if( idField == ifds::BrokerCode )
   {
      validateBrokerCode(strValue, idDataGroup );   
   }
   else if( idField == ifds::AMSCode )
   {
      validateAMSCode(strValue,idDataGroup ); 
   }

   return(GETCURRENTHIGHESTSEVERITY());
}


//**********************************************************************************************
SEVERITY BrokerAMSsearch::validateBrokerCode( const DString& dstrValue,  const BFDataGroupId& idDataGroup  )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateBrokerCode") );

	DString dstrBrokerCode( dstrValue );dstrBrokerCode.strip();
   DString BrokerField = I_( "Broker Code" );      
   if( dstrValue == NULL_STRING )
   {
      ADDCONDITIONFROMFILEIDI( CND::ERR_FIELD_MANDATORY_F4_FOR_SEARCH, DString(I_("FIELDNAME=")) + BrokerField );
   }
   else
   {
      SEVERITY sevRtn;
		// the original logic does not work.
		BrokerList brokerlist(*this);
		sevRtn = brokerlist.init2(dstrBrokerCode, NULL_STRING,I_("L"),NULL_STRING,I_("Trade") );
      if( sevRtn > WARNING )
      {
			DString idiStr;
         addIDITagValue( idiStr, I_( "FIELDNAME" ), BrokerField );
         ADDCONDITIONFROMFILEIDI( CND::ERR_FIELD_INVALID_F4_FOR_SEARCH, idiStr );
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//***********************************************************************************
SEVERITY BrokerAMSsearch::validateAMSCode( const DString& dstrValue, const BFDataGroupId& idDataGroup  )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateFundCodeCurrency") );
   DString dstrAMSCode;
   getField(ifds::AMSCode,dstrAMSCode,idDataGroup,false);

   //setUpdatedFlag( ifds::AMSCode, idDataGroup, false );

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
SEVERITY BrokerAMSsearch::BrokerCodeRelatedChanges( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("BrokerCodeRelatedChanges") );

   DString dstrBrokerCode;
   
   BrokerList *pBrokerList;
   Broker *pBroker = NULL;
   getField(ifds::BrokerCode,dstrBrokerCode,idDataGroup,false);

   if( dstrBrokerCode != NULL_STRING && getWorkSession().getBrokerList(pBrokerList) <= WARNING &&
       pBrokerList->getBroker(dstrBrokerCode, pBroker) <= WARNING && pBroker )
   {
      DString dstrBrokerName;
      pBroker->getField( ifds::BrokerName, dstrBrokerName, idDataGroup,false );
		setFieldNoValidate(ifds::BrokerName,dstrBrokerName,idDataGroup,false,true,true);
   }
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************

SEVERITY BrokerAMSsearch::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges") );
   if( idField == ifds::BrokerCode )
   {
      BrokerCodeRelatedChanges(idDataGroup);

   }

   return(GETCURRENTHIGHESTSEVERITY());
}

 
//********************************************************************************
//Based on the DSTCWorkSession - AMSSearch - BrokerAMSList design,
//The BrokerCode and AMSCode fields here are linked to dialog controls,(for API, set from Process.)
//The purpose is when when change the broker and ams code from the search part of the dialog, 
//When click Search button, the broker AMS list will be changed accordingly.and the bRemObj will be true at this movement
SEVERITY BrokerAMSsearch::getBrokerAMSList( BrokerAMSList*& pBrokerAMSlist, 
                                             const BFDataGroupId& idDataGroup,bool bInq /* = true */,bool bRemObj  /* = true */)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getSettlementTradeList" ) );
   DString dstrBrokerCode;
   DString dstrAMSCode=NULL_STRING; 
   bool Allresult= false;
   DString dstrTrack=I_("N");
   DString dstrPageName=NULL_STRING;

	getField(ifds::BrokerCode,dstrBrokerCode,idDataGroup);
	getField(ifds::AMSCode,dstrAMSCode,idDataGroup);

	pBrokerAMSlist = dynamic_cast<BrokerAMSList*>( BFCBO::getObject( I_("BrokerAMSList"), idDataGroup ) );

	if( bRemObj && pBrokerAMSlist ) 
	{
			deleteObject(I_("BrokerAMSList"), idDataGroup, true);
			pBrokerAMSlist = NULL;
	}
	if( !pBrokerAMSlist )
	{
		pBrokerAMSlist = new BrokerAMSList( *this );
		pBrokerAMSlist->init(dstrBrokerCode, dstrAMSCode, Allresult, dstrTrack, dstrPageName);
		if( pBrokerAMSlist )
		{
			 if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
			 {			 
				 pBrokerAMSlist->setField(ifds::BrokerCode, dstrBrokerCode, idDataGroup, false);
				 setObject( pBrokerAMSlist, I_("BrokerAMSList"), OBJ_ACTIVITY_NONE, idDataGroup ); 				 
			 }
			 else
			 {
				delete pBrokerAMSlist;
				pBrokerAMSlist = NULL;
			 }
		}
	}

	
	return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************
//This fundction is used by MFAccount validate the account level AMS 
SEVERITY BrokerAMSsearch::getBrokerAMSList( BrokerAMSList*& pBrokerAMSlist, 
                                             const BFDataGroupId& idDataGroup,DString dstrBrokerCode, DString dstrAMSCode)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getSettlementTradeList" ) );

   bool Allresult= false;
   DString dstrTrack=I_("N");
   DString dstrPageName=NULL_STRING;

   pBrokerAMSlist = dynamic_cast<BrokerAMSList*>( BFCBO::getObject( I_("BrokerAMSList"), idDataGroup ) );

   if( pBrokerAMSlist ) 
   {
		deleteObject(I_("BrokerAMSList"), idDataGroup, true);
		pBrokerAMSlist = NULL;
   }
   if( !pBrokerAMSlist )
   {
		pBrokerAMSlist = new BrokerAMSList( *this );
		pBrokerAMSlist->init(dstrBrokerCode, dstrAMSCode, Allresult, dstrTrack, dstrPageName);
		if( pBrokerAMSlist )
		{
			 if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
			 {			 
				 pBrokerAMSlist->setField(ifds::BrokerCode, dstrBrokerCode, idDataGroup, false);
				 setObject( pBrokerAMSlist, I_("BrokerAMSList"), OBJ_ACTIVITY_NONE, idDataGroup ); 				 
			 }
			 else
			 {
				delete pBrokerAMSlist;
				pBrokerAMSlist = NULL;
			 }
		}
   }
	
   return(GETCURRENTHIGHESTSEVERITY());
}

//************************************************************************************
SEVERITY BrokerAMSsearch::setField( const BFFieldId& idField, const DString& dstrValue,
                               const BFDataGroupId& idDataGroup, bool bFormatted, bool bSideEffect, bool  bCheckCurrentValue)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setField" ) );
   if( idField == ifds::AMSCode )
   {
      DString dstrBrokerCode;
      getField(ifds::BrokerCode,dstrBrokerCode,idDataGroup      );
   }
   BFCBO::setField( idField, dstrValue, idDataGroup, bFormatted, bSideEffect );

   return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
//
















