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
// ^FILE   : FundClassHoldingsList.cpp
// ^AUTHOR : Zijian Ying
// ^DATE   : 04/19/99
//
// ^CLASS    : FundClassHoldingsList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "fundclassholdingslist.hpp"
#include "fundclassholding.hpp"

namespace
{
   //Trace literals
   const I_CHAR *  CLASSNAME = I_( "FundClassHoldingsList" );
}

namespace ifds 
{
   extern CLASS_IMPORT const BFTextFieldId rxFundCode;
   extern CLASS_IMPORT const BFTextFieldId rxClassCode;
   extern CLASS_IMPORT const BFDecimalFieldId SettledValue;
   extern CLASS_IMPORT const BFDecimalFieldId AdjustedCost;
   extern CLASS_IMPORT const BFDecimalFieldId EligibleAmt;
   extern CLASS_IMPORT const BFDecimalFieldId LeftAmt;
   extern CLASS_IMPORT const BFDecimalFieldId LeftUnits;
   extern CLASS_IMPORT const BFTextFieldId AmountType;
}

extern DString cnvDoubleToDString( double v );
extern double cnvDStringToDouble( const DString& v );

//******************************************************************************
FundClassHoldingsList::FundClassHoldingsList( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
}


//******************************************************************************
FundClassHoldingsList::~FundClassHoldingsList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY FundClassHoldingsList::init()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void FundClassHoldingsList::getStrKey( DString& dstKey, const DString& dstFund, const DString& dstClass )
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
void FundClassHoldingsList::getStrKey ( DString& strKey, const BFData* data )
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
void FundClassHoldingsList::createFundClassHoldingsObject( const BFData& data, const BFDataGroupId& idDataGroup )
{
   TRACE_METHOD( CLASSNAME, I_( "createCurrencyObject" ) );

   BFObjIter bfIter( *this, idDataGroup, true );

   DString strFund = data.getElementValue( ifds::rxFundCode, false );
   DString strClass = data.getElementValue( ifds::rxClassCode, false );
   DString strKey;
   getStrKey( strKey, strFund, strClass );

   FundClassHolding *pFundClassHolding;
   bfIter.positionByKey( strKey );
   if( !bfIter.end() )
   {
      pFundClassHolding = dynamic_cast < FundClassHolding * > ( bfIter.getObject() );
      if( pFundClassHolding )
         pFundClassHolding->init( data );
      else
         assert( 0 );
   }
   else
   {
      pFundClassHolding = new FundClassHolding( *this );
      pFundClassHolding->init( data );
      setObject( pFundClassHolding, strKey );
   }
}

//******************************************************************************
SEVERITY FundClassHoldingsList::getTotalTenPercFree( DString& total )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION,
                          CLASSNAME,
                          I_( "getTotalTenPercFree( DString & )" ) );

   BFObjIter bfIter( *this, BF::HOST, true );
   DString str,str1,str0;
   double dbTotal = 0;
   double totalamt = 0;

   //on Oct 29th 2002 , fundcom meeting, when holdings have missed amounttype,  
   //we need calculate the totals by the first met amount type
   bfIter.getObject()->getField( ifds::AmountType, str0, BF::HOST, false );
   while( !bfIter.end() )
   {
      bfIter.getObject()->getField( ifds::LeftUnits, str, BF::HOST, false );
      dbTotal += cnvDStringToDouble( str );
      bfIter.getObject()->getField( ifds::LeftAmt, str1, BF::HOST, false );
      totalamt += cnvDStringToDouble( str1 );

      ++bfIter;
   }

   if(str0 == I_("D"))
      total = cnvDoubleToDString( totalamt );
   else //if(str0 == I_("S"))
      total = cnvDoubleToDString( dbTotal );

   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY FundClassHoldingsList::getTotalPercentage( DString& total )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION,
                          CLASSNAME,
                          I_( "getTotalPercentage( DString & )" ) );

   BFObjIter bfIter( *this, BF::HOST, true );
   DString str;
   double dbTotal = 0;

   while( !bfIter.end() )
   {
      ( dynamic_cast < FundClassHolding* > ( bfIter.getObject() ) )->getPercOfTotal( str );
      dbTotal += cnvDStringToDouble( str );
      ++bfIter;
   }

   total = cnvDoubleToDString( dbTotal );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY FundClassHoldingsList::getTotalMarketValue( DString& total )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getTotalMarketValue" ) );

   BFObjIter bfIter( *this, BF::HOST, true );
   DString str;
   double dbTotal = 0;

   while( !bfIter.end() )
   {
      bfIter.getObject()->getField( ifds::SettledValue, str, BF::HOST, false );
      dbTotal += cnvDStringToDouble( str );
      ++bfIter;
   }

   total = cnvDoubleToDString( dbTotal );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY FundClassHoldingsList::getTotalBookValue( DString& total )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getTotalBookValue" ) );

   BFObjIter bfIter( *this, BF::HOST, true );
   DString str;
   double dbTotal = 0;

   while( !bfIter.end() )
   {
      bfIter.getObject()->getField( ifds::AdjustedCost, str, BF::HOST, false );
      dbTotal += cnvDStringToDouble( str );
      ++bfIter;
   }

   total = cnvDoubleToDString( dbTotal );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/FundClassHoldingsList.cpp-arc  $
// 
//    Rev 1.9   Nov 14 2004 14:41:44   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.8   Mar 21 2003 18:10:40   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.7   Dec 12 2002 13:40:50   FENGYONG
// change MFCANCBO to IFASTCBO
// 
//    Rev 1.6   Dec 12 2002 11:22:10   FENGYONG
// change the way calculate totaltenperfree
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
