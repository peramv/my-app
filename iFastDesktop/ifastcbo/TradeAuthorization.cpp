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
//    Copyright 2004 By International Financial Data Services.
//
//
//********************************************************************************
//
// ^FILE   : TradeAuthorization.cpp
// ^AUTHOR : 
// ^DATE   : 
//
//********************************************************************************
#include "stdafx.h"
#include "TradeAuthorization.hpp"


#include <ifastdataimpl\dse_dstc0393_req.hpp>

namespace
{
   const I_CHAR * const CLASSNAME               = I_( "TradeAuthorization" );
   const I_CHAR * const RECORD_TYPE             = I_( "PendProcRecordType" );
   const I_CHAR * const NA                      = I_( "NA" );
   const I_CHAR * const INVALID_AUTH_VALUE      = I_( "NA,DN,DR" );
}

namespace CND
{
	extern const long ERR_INVALID_AUTH_VALUE;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
   // Field DD Id,                  State Flags,      Group Flags 
   { ifds::StcPendTrdAuthorization, BFCBO::NONE,         0 },
   { ifds::TransId,                 BFCBO::NONE,         0 },
   { ifds::TransNum,                BFCBO::NONE,         0 },
   { ifds::PendProcRecordType,      BFCBO::NONE,         0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
TradeAuthorization::TradeAuthorization( BFAbstractCBO &parent )
: MFCanBFCbo( parent ),
  m_dstrPendProcRecordType (NULL_STRING)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );	
}

//******************************************************************************
TradeAuthorization::~TradeAuthorization()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}  

//*******************************************************************************
SEVERITY TradeAuthorization::init(const DString &recordType,
                                  const DString &transNum,
                                  const DString &transId,
                                  const DString &authorization,
                                  const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   setFieldNoValidate (ifds::PendProcRecordType, recordType, idDataGroup); 
   setFieldNoValidate (ifds::TransNum, transNum, idDataGroup); 
   setFieldNoValidate (ifds::TransId, transId, idDataGroup); 
   setFieldNoValidate (ifds::StcPendTrdAuthorization, authorization, idDataGroup, false, false, true); 

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY TradeAuthorization::init( const BFData& data )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );	

   attachDataObject(const_cast<BFData&>(data), false); 

   return(GETCURRENTHIGHESTSEVERITY());
}

//*********************************************************************************
SEVERITY TradeAuthorization::doValidateField( const BFFieldId& idField, 
                                              const DString& dstrValue, 
                                              const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField" ));   

   if (idField == ifds::StcPendTrdAuthorization)
   {
      DString strAuthorizedValue(dstrValue);
      strAuthorizedValue.strip().upperCase();

      if (DSTCommonFunctions::codeInList (strAuthorizedValue, INVALID_AUTH_VALUE))
      {
         ADDCONDITIONFROMFILE (CND::ERR_INVALID_AUTH_VALUE);
      }
   }

   return GETCURRENTHIGHESTSEVERITY();
}

//*********************************************************************************
void TradeAuthorization::doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
{
}

//****************************************************************************
SEVERITY TradeAuthorization::initNew( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "initNew" ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
// 
// $Log:   Y:/VCS/BF iFAST/ifastcbo/TradeAuthorization.cpp-arc  $
// 
//    Rev 1.2   Sep 15 2010 04:07:18   dchatcha
// P0175471 - FundSERV Client Name Document Tracking.
// 
// 
