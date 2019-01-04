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
// Copyright 2012 by International Financial Data Services.
//
//
//******************************************************************************
//
// ^FILE   : ACBRecord.cpp
// ^AUTHOR : 
// ^DATE   : Sep, 2012
//
// ^CLASS    : ACBRecord
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "ACBRecord.hpp"

#include "ACBList.hpp"

#include <ifastdataimpl\dse_dstc0015_req.hpp>
#include <ifastdataimpl\dse_dstc0015_vw.hpp>
#include <ifastdataimpl\dse_dstc0015_vw.hpp>

namespace
{
   const I_CHAR * const CLASSNAME               = I_( "ACBRecord" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFDecimalFieldId ACBPlugAmt;
   extern CLASS_IMPORT const BFDateFieldId ACBPlugDate;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFTextFieldId IsNewOrUpdate;
   extern CLASS_IMPORT const BFNumericFieldId TransId;
   extern CLASS_IMPORT const BFDecimalFieldId GIAOpenMktValue;
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
   { ifds::TransId,                    BFCBO::NONE,                0 },
   { ifds::GIAOpenMktValue,            BFCBO::READ_ONLY,           0 },
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************************
ACBRecord::ACBRecord( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   
   registerMemberData( NUM_FIELDS, 
                      (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0, 
                       NULL );
}

//******************************************************************************************
ACBRecord::~ACBRecord()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************************
SEVERITY ACBRecord::init(const BFData& data)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   attachDataObject( const_cast< BFData& >( data ), false, true );
   clearUpdatedFlags (BF::HOST);

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
void ACBRecord::getField( const BFFieldId& idField, DString& strFieldValue, const BFDataGroupId& idDataGroup, bool formattedReturn ) const
{
   BFCBO::getField( idField, strFieldValue, idDataGroup, formattedReturn );
   if( ( idField == ifds::TransAmount   || 
         idField == ifds::AdjustedCost) &&
       formattedReturn )
   {
      DString currency, fundCode, classCode;
      BFCBO::getField( ifds::rxFundCode, fundCode, idDataGroup, true );
      BFCBO::getField( ifds::rxClassCode, classCode, idDataGroup, true );
      CurrencyClass::getFundCurrency( getWorkSession(), fundCode, classCode, currency );
      currency.strip();

      BFCBO::getField( idField, strFieldValue, idDataGroup, false );
      CurrencyClass::FormatValue( currency, strFieldValue, strFieldValue );
   }
}

//******************************************************************************
SEVERITY ACBRecord::doValidateAll( const BFDataGroupId& idDataGroup, long lValidateGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateAll" ) );
   
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ACBRecord::doValidateField( const BFFieldId& idField,
                                      const DString& strValue,
                                      const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY ACBRecord::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/ACBRecord.cpp-arc  $
// 

