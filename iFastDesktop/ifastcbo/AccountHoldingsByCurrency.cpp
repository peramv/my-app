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
// ^FILE   : AccountHoldingsByCurrency.cpp
// ^AUTHOR : Zijian Ying
// ^DATE   : 04/19/99
//
// ^CLASS    : AccountHoldingsByCurrency
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "accountholdingsbycurrency.hpp"
#include "fundclassholdingslist.hpp"

namespace
{
   //Trace literals
   const I_CHAR *  CLASSNAME = I_( "AccountHoldingsByCurrency" );
}

//******************************************************************************
AccountHoldingsByCurrency::AccountHoldingsByCurrency( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent ),
_currency( NULL_STRING )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
}


//******************************************************************************
AccountHoldingsByCurrency::~AccountHoldingsByCurrency( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY AccountHoldingsByCurrency::init( const BFData& data, const DString& strCurrency )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   _currency = strCurrency;

   return(GETCURRENTHIGHESTSEVERITY());
}

void AccountHoldingsByCurrency::getCurrency( DString& strCurrency )
{
   strCurrency = _currency;
}

//******************************************************************************
SEVERITY AccountHoldingsByCurrency::getFundClassHoldingsList( FundClassHoldingsList *&pFundClassHoldingsList, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getFundClassHoldingsList" ) );

   pFundClassHoldingsList = dynamic_cast<FundClassHoldingsList*>(BFCBO::getObject( I_( "FundClassHoldingsList" ), idDataGroup ) );

   if( !pFundClassHoldingsList )
   {
      pFundClassHoldingsList = new FundClassHoldingsList( *this );
      pFundClassHoldingsList->init();
      if( pFundClassHoldingsList )
      {
         if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
         {
            setObject( pFundClassHoldingsList, I_( "FundClassHoldingsList" ), OBJ_ACTIVITY_NONE, idDataGroup ); 
         }
         else
         {
            delete pFundClassHoldingsList;
            pFundClassHoldingsList = NULL;
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AccountHoldingsByCurrency::getTotalTenPercFree( DString& total )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getFundClassHoldingsList" ) );

   FundClassHoldingsList *pFundClassHoldingsList;
   getFundClassHoldingsList( pFundClassHoldingsList, BF::HOST );
   pFundClassHoldingsList->getTotalTenPercFree( total );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AccountHoldingsByCurrency::getTotalPercentage( DString& total )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getFundClassHoldingsList" ) );

   FundClassHoldingsList *pFundClassHoldingsList;
   getFundClassHoldingsList( pFundClassHoldingsList, BF::HOST );
   pFundClassHoldingsList->getTotalPercentage( total );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AccountHoldingsByCurrency::getTotalMarketValue( DString& total )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getFundClassHoldingsList" ) );

   FundClassHoldingsList *pFundClassHoldingsList;
   getFundClassHoldingsList( pFundClassHoldingsList, BF::HOST );
   pFundClassHoldingsList->getTotalMarketValue( total );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AccountHoldingsByCurrency::getTotalBookValue( DString& total )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getFundClassHoldingsList" ) );

   FundClassHoldingsList *pFundClassHoldingsList;
   getFundClassHoldingsList( pFundClassHoldingsList, BF::HOST );
   pFundClassHoldingsList->getTotalBookValue( total );

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AccountHoldingsByCurrency.cpp-arc  $
// 
//    Rev 1.6   Mar 21 2003 17:54:20   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.5   Oct 09 2002 23:53:52   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.4   Aug 29 2002 12:54:52   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.3   22 May 2002 18:26:12   PURDYECH
// BFData Implementation
// 
//    Rev 1.2   03 May 2001 14:05:52   SMITHDAV
// Session management restructuring.
// 
//    Rev 1.1   Mar 12 2001 12:58:46   VASILEAD
// Modified for FUNDcom release
 * 
 *    Rev 1.0   Feb 15 2000 10:59:46   SMITHDAV
 * Initial revision.
 * 
*/
