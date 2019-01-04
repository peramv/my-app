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
// ^FILE   : Currency.cpp
// ^AUTHOR : Winnie Shiu
// ^DATE   : May 3, 2000
// ^CLASS    : Currency
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION : 
//
//******************************************************************************
#include "stdafx.h"
#include "currency.hpp"
#include <ifastdataimpl\dse_dstc0101_vwrepeat_record.hpp>

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] =
{
//  Field DD Id,					State Flags,	Group Flags
   { ifds::Currency,      BFCBO::NONE, 0 }, 
   { ifds::EffectiveDate, BFCBO::NONE, 0 }, 
   { ifds::Name,          BFCBO::NONE, 0 }, 
   { ifds::Precision,     BFCBO::NONE, 0 }, 
   { ifds::RoundMethod,   BFCBO::NONE, 0 }, 
};

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME   = I_( "Currency" );
}

namespace CND
{  // Conditions used
   extern const long ERR_INCORRECT_PRECISION;
}

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
Currency::Currency( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );

   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}

//******************************************************************************
Currency::~Currency()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY Currency::init( const BFData &viewData )
{
   MAKEFRAME2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );

   attachDataObject( const_cast<BFData&>( viewData ), false, true );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY Currency::precisionOkay ( const DString dstrAmount, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "precisionOkay" ) );

   DString NumOfDecimal, dstrCurrency;
   getField(ifds::Precision, NumOfDecimal, idDataGroup, false );
   getField(ifds::Currency,  dstrCurrency, idDataGroup, false );

   if( DSTCommonFunctions::NumOfDecimals( dstrAmount ) > atoi ( NumOfDecimal.asA().c_str() ) )
   {
      DString NUMOFDECIMALS = I_( "NUMOFDECIMALS" ), idiStr;
      DString CURRENCY = I_( "CURRENCY" );

      NumOfDecimal.strip().stripLeading( '0' );

      if( NumOfDecimal == NULL_STRING )
         NumOfDecimal = I_( "0" );

      addIDITagValue(idiStr, NUMOFDECIMALS, NumOfDecimal);
      addIDITagValue(idiStr, CURRENCY, dstrCurrency);

      ADDCONDITIONFROMFILEIDI( CND::ERR_INCORRECT_PRECISION, idiStr);
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
bool Currency::isEuroCurrency ( const BFDataGroupId& idDataGroup )
{
   DString dstrCurrencyType;

   getField ( ifds::CurrencyType, dstrCurrencyType, idDataGroup, false );
   dstrCurrencyType.strip().upperCase();

   return( dstrCurrencyType == I_( "IN" ) );

}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/Currency.cpp-arc  $
// 
//    Rev 1.12   Nov 14 2004 14:30:02   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.11   Mar 21 2003 18:02:06   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.10   Oct 09 2002 23:54:10   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.9   Aug 29 2002 12:55:14   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.8   22 May 2002 18:26:42   PURDYECH
// BFData Implementation
// 
//    Rev 1.7   09 May 2001 15:11:30   HSUCHIN
// Sync up with SSB
// 
//    Rev 1.6   03 May 2001 14:06:06   SMITHDAV
// Session management restructuring.
// 
//    Rev 1.5   Apr 02 2001 10:50:52   FENGYONG
// delete exchratelist after finished use it
// 
//    Rev 1.4   Feb 05 2001 17:52:24   WINNIE
// change parameters for call ExchRateList
// 
//    Rev 1.3   Jan 18 2001 11:32:40   WINNIE
// new method to check amount precision
// 
//    Rev 1.2   Dec 17 2000 20:22:50   OLTEANCR
// changed to use a precompiled header
// 
//    Rev 1.1   Nov 02 2000 14:11:34   VASILEAD
// Added workSeesionId parameter for Mgmtco based CBOs
// 
//    Rev 1.0   May 05 2000 10:31:08   WINNIE
// Initial revision.
*/