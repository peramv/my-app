//******************************************************************************
//
// COPYRIGHT:
//
// The computer systems, procedures, data bases and
// programs created and maintained by International Financial Data Services,
// are proprietary in nature and as such are confIdential.
// Any unauthorized use or disclosure of such information
// may result in civil liabilities.
//
// Copyright 2014 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : DemographicsChild.cpp
// ^AUTHOR : 
// ^DATE   : Oct, 2014
//
// ^CLASS    : DemographicsChild
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "DemographicsChild.hpp"

#include "Demographics.hpp"

#include <ifastdataimpl\dse_dstc0011_req.hpp>
#include <ifastdataimpl\dse_dstc0011_vw.hpp>
#include <ifastdataimpl\dse_dstc0465_req.hpp>
#include <ifastdataimpl\dse_dstc0465_vw.hpp>
#include <ifastdataimpl\dse_dstc0465_vwrepeat_record.hpp>

namespace
{
   const I_CHAR * const CLASSNAME               = I_( "DemographicsChild" );
}

namespace ifds
{
}

namespace CND
{  // Conditions used
}

namespace IFASTERR
{
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
//  Field DD Id,                       State Flags,            Group Flags 
   { ifds::KYCAttribType,              BFCBO::NONE,                0 },
   { ifds::KYCAttribCode,              BFCBO::NONE,                0 },
   { ifds::KYCAttribStat,              BFCBO::NONE,                0 },
   { ifds::KYCAttribDesc,              BFCBO::NONE,                0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************************
DemographicsChild::DemographicsChild( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   
   registerMemberData( NUM_FIELDS, 
                      (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0, 
                       NULL );
}

//******************************************************************************************
DemographicsChild::~DemographicsChild()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************************
SEVERITY DemographicsChild::init(const BFData& data)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   attachDataObject( const_cast< BFData& >( data ), false, true );
   clearUpdatedFlags (BF::HOST);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY DemographicsChild::initNew ( const BFDataGroupId &idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY DemographicsChild::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );
   
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY DemographicsChild::doValidateField( const BFFieldId& idField,
                                      const DString& strValue,
                                      const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY DemographicsChild::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/DemographicsChild.cpp-arc  $
// 

