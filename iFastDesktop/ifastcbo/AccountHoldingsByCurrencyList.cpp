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
// ^FILE   : AccountHoldingsByCurrencyList.cpp
// ^AUTHOR : Zijian Ying
// ^DATE   : 04/19/99
//
// ^CLASS    : AccountHoldingsByCurrencyList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "accountholdingsbycurrencylist.hpp"
#include "accountholdingsbycurrency.hpp"
#include "fundclassholdingslist.hpp"
#include "funddetaillist.hpp"
#include "funddetail.hpp"
#include "mgmtco.hpp"
#include "dstcworksession.hpp"

namespace
{
   //Trace literals
   const I_CHAR *  CLASSNAME = I_( "AccountHoldingsByCurrencyList" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId rxFundCode;
   extern CLASS_IMPORT const BFTextFieldId rxClassCode;
   extern CLASS_IMPORT const BFTextFieldId Currency;
}

//******************************************************************************
AccountHoldingsByCurrencyList::AccountHoldingsByCurrencyList( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
}


//******************************************************************************
AccountHoldingsByCurrencyList::~AccountHoldingsByCurrencyList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY AccountHoldingsByCurrencyList::init()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void AccountHoldingsByCurrencyList::getStrKey( DString& dstKey, const DString& currency )
{
   TRACE_METHOD( CLASSNAME, I_( "getStrKey" ) );

   dstKey = currency;
   dstKey.strip();
   dstKey.upperCase();
}

//******************************************************************************
void AccountHoldingsByCurrencyList::getStrKey ( DString& strKey, const BFData* data )
{
   TRACE_METHOD( CLASSNAME, I_( "getStrKey" ) );

   if( data )
   {
      DString temp;
      getFundCurrency( temp, *data );
      getStrKey( strKey, temp );
   }
   else
   {
      BFCBO::getStrKey( strKey, NULL );
   }
}

//******************************************************************************
SEVERITY AccountHoldingsByCurrencyList::getFundCurrency (DString &currency, const BFData& data)
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "createCurrencyObject" ) );

   DString strFund = 
         data.getElementValue (ifds::rxFundCode, false);
   DString strClass = 
      data.getElementValue (ifds::rxClassCode, false);

   FundDetailList *pFundDetailList = NULL;
   
   if (getMgmtCo().getFundDetailList (pFundDetailList) <= WARNING)
   {
      if( pFundDetailList )
      {
         FundDetail *pFundDetail = NULL;
         if( pFundDetailList->getFundDetail( strFund, strClass, BF::HOST, pFundDetail ) )
         {
            pFundDetail->getField( ifds::Currency, currency, BF::HOST, false );
         }
      }
   }
   return GETCURRENTHIGHESTSEVERITY();
}

//******************************************************************************
SEVERITY AccountHoldingsByCurrencyList::createCurrencyObject( const BFData& data, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "createCurrencyObject" ) );

   DString strCurrency, temp;

   SEVERITY sevRtn = getFundCurrency( temp, data );
   if( WARNING < sevRtn )
   {
      return(sevRtn);
   }

   getStrKey( strCurrency, temp );

   AccountHoldingsByCurrency *pAccountHoldingsByCurrency;
   BFObjIter bfIter( *this, idDataGroup, true );
   bfIter.positionByKey( strCurrency );

   if( !bfIter.end() )
   {
      pAccountHoldingsByCurrency = dynamic_cast < AccountHoldingsByCurrency *> ( bfIter.getObject() );
   }
   else
   {
      pAccountHoldingsByCurrency = new AccountHoldingsByCurrency( *this );
      pAccountHoldingsByCurrency->init( data, strCurrency );
      setObject( pAccountHoldingsByCurrency, strCurrency );
   }

   FundClassHoldingsList *pFundClassHoldingsList;
   pAccountHoldingsByCurrency->getFundClassHoldingsList( pFundClassHoldingsList, BF::HOST );
   pFundClassHoldingsList->createFundClassHoldingsObject( data, BF::HOST );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AccountHoldingsByCurrencyList.cpp-arc  $
// 
//    Rev 1.8   Nov 29 2004 13:18:08   hernando
// PET1117 - Tuning Project - Revised use of FundDetailList.
// 
//    Rev 1.7   Jun 01 2004 12:35:12   popescu
// PTS 10030757, fixed iterations through the fund details list; dsk crashes if  the fund is not being found.
// 
//    Rev 1.6   Mar 21 2003 17:54:24   PURDYECH
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
//    Rev 1.2   Jun 26 2001 12:54:58   PURDYECH
// Infrastructure Release 1.9 Integration.
// 
//    Rev 1.1   03 May 2001 14:05:52   SMITHDAV
// Session management restructuring.
// 
//    Rev 1.0   Mar 05 2001 13:29:18   VASILEAD
// Initial revision.
 * 
 *    Rev 1.0   Feb 15 2000 10:59:46   SMITHDAV
 * Initial revision.
 * 
*/
