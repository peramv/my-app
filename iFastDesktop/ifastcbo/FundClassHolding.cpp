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
//    Copyright 1999 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : FundClassHolding.cpp
// ^AUTHOR : Zijian Ying
// ^DATE   : 04/19/99
//
// ^CLASS    : FundClassHolding
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"

#include "fundclassholding.hpp"
#include "fundclassholdingslist.hpp"

namespace
{
   //Trace literals
   const I_CHAR *  CLASSNAME = I_( "FundClassHolding" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId rxFundCode;
   extern CLASS_IMPORT const BFTextFieldId rxClassCode;
   extern CLASS_IMPORT const BFDecimalFieldId SettledValue;
}

//*****************************************************************************
DString cnvDoubleToDString( double v )
{
   char szBuffer[50];
   _gcvt( v, 15, szBuffer );
   return(DStringA( szBuffer ));
}

//*****************************************************************************
double cnvDStringToDouble( const DString& v )
{
   I_CHAR *pError = NULL;
   return(i_strtod( v.c_str(), &pError ));
}

//******************************************************************************
FundClassHolding::FundClassHolding( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
}


//******************************************************************************
FundClassHolding::~FundClassHolding( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY FundClassHolding::init( const BFData& data )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   attachDataObject( const_cast<BFData&>(data), false, true );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void FundClassHolding::getStrKey( DString& dstKey, const DString& dstFund, const DString& dstClass )
{
   TRACE_METHOD( CLASSNAME, I_( "getStrKey" ) );

   dstKey = dstFund;
   dstKey.strip();
   dstKey += I_( "  " );
   dstKey += dstClass;
   dstKey.strip();
   dstKey += I_( "  " );
   dstKey.strip();

   dstKey.upperCase();
}

//******************************************************************************
void FundClassHolding::getStrKey ( DString& strKey, const BFData* data )
{
   TRACE_METHOD( CLASSNAME, I_( "getStrKey" ) );

   if( data )
   {
      DString strFund = data->getElementValue( ifds::rxFundCode );
      DString strClass = data->getElementValue( ifds::rxClassCode );

      getStrKey( strKey, strFund, strClass );
   }
   else
   {
      BFCBO::getStrKey( strKey, NULL );
   }
}

//******************************************************************************
void FundClassHolding::getPercOfTotal( DString& perc )
{
   TRACE_METHOD( CLASSNAME, I_( "getStrKey" ) );

   DString str, strTotMktValue;
   ( dynamic_cast < FundClassHoldingsList* > ( getParent() ) )->getTotalMarketValue( strTotMktValue );
   getField( ifds::SettledValue, str, BF::HOST, false );

   if( cnvDStringToDouble( strTotMktValue ) != 0 )
      perc = cnvDoubleToDString( cnvDStringToDouble( str ) / cnvDStringToDouble( strTotMktValue ) * 100 ) ;
   else
      perc = I_( "0.00" );

}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FundClassHolding.cpp-arc  $
// 
//    Rev 1.7   Nov 14 2004 14:41:40   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.6   Mar 21 2003 18:10:36   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.5   Oct 09 2002 23:54:32   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.4   Aug 29 2002 12:55:54   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.3   22 May 2002 18:28:42   PURDYECH
// BFData Implementation
// 
//    Rev 1.2   03 May 2001 14:06:30   SMITHDAV
// Session management restructuring.
// 
//    Rev 1.1   Mar 12 2001 12:58:48   VASILEAD
// Modified for FUNDcom release
 * 
 *    Rev 1.0   Feb 15 2000 10:59:46   SMITHDAV
 * Initial revision.
 * 
*/
