//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2000 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : TaxRates.cpp
// ^AUTHOR : Cristina Oltean
// ^DATE   : 24/11/2000
//
// ^CLASS    : TaxRates
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "taxrates.hpp"
#include <ifastdataimpl\dse_dstc0112_vwrepeat_record.hpp>

namespace
{
   const I_CHAR * const CLASSNAME = I_( "TaxRates" );
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//   Field DD Id,        State Flags,       Group Flags 
   { ifds::TaxJurisCode,  BFCBO::NONE, 0 }, 
   { ifds::TaxJurisName,  BFCBO::NONE, 0 }, 
   { ifds::EffectiveDate, BFCBO::NONE, 0 }, 
   { ifds::FedIncRate,    BFCBO::NONE, 0 }, 
   { ifds::FedRedRate,    BFCBO::NONE, 0 }, 
   { ifds::ProvIncRate,   BFCBO::NONE, 0 }, 
   { ifds::ProvRedRate,   BFCBO::NONE, 0 }, 
   { ifds::ProcessDate,   BFCBO::NONE, 0 }, 
   { ifds::LowerBound,    BFCBO::NONE, 0 }, 
   { ifds::UpperBound,    BFCBO::NONE, 0 }, 
   { ifds::PerPenRate,    BFCBO::NONE, 0 }, 
   { ifds::LumpPenRate,   BFCBO::NONE, 0 }, 
   { ifds::Username,      BFCBO::NONE, 0 }, 
   { ifds::ModDate,       BFCBO::NONE, 0 }, 
   { ifds::ModName,       BFCBO::NONE, 0 }, 
   { ifds::TaxRateRid,    BFCBO::NONE, 0 }, 
};
static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//****************************************************************************
TaxRates::TaxRates( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   registerMemberData( NUM_FIELDS,
                       (const CLASS_FIELD_INFO *)&classFieldInfo,
                       0,
                       NULL );
}

//****************************************************************************
TaxRates::~TaxRates()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}     

//****************************************************************************
SEVERITY TaxRates::init( const BFData& InstData )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   attachDataObject( const_cast<BFData&>(InstData), false, true );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/TaxRates.cpp-arc  $
// 
//    Rev 1.7   Nov 14 2004 14:56:58   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.6   Oct 09 2002 23:55:06   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.5   Aug 29 2002 12:56:48   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.4   22 May 2002 18:30:00   PURDYECH
// BFData Implementation
// 
//    Rev 1.3   03 May 2001 14:07:10   SMITHDAV
// Session management restructuring.
// 
//    Rev 1.2   Feb 19 2001 13:37:36   DINACORN
// Add Revision Control Entries
 * 
 */
