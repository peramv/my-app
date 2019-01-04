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
//    Copyright 1999 by DST Systems, Inc.
//
//******************************************************************************
//
// ^FILE   : CurrencyClass.cpp
// ^AUTHOR : Adrian Vasile
// ^DATE   : 08/02/1999
//
// -----------------------------------------------------------------------------
//
// ^CLASS    : CurrencyClass
//    This class manages the formatting of the fields that need to display different
//    format based on a currency
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS  :
//
//******************************************************************************

#include "stdafx.h"
#include "currencyclass.hpp"
#include "currencylist.hpp"
#include <ifastdataimpl\dse_currency_vw.hpp>
#include "funddetaillist.hpp"
#include "funddetail.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include <ifastdataimpl\dse_dstc0056_vw.hpp>
#include <ifastdataimpl\dse_dstc0083_vw.hpp>
#include <ifastdataimpl\dse_dstc0101_vw.hpp>


namespace
{
   const I_CHAR * const MFDSTC         = I_( "MFDSTC" );
   const I_CHAR * const MARKET         = I_( "Market" );
   const I_CHAR * const DECIMALS       = I_( "DECIMALS" );
   const I_CHAR * const YES            = I_( "Y" );
}

namespace CRCY
{
   extern CLASS_IMPORT I_CHAR * const CANADIAN_DOLLAR   ;
   extern CLASS_IMPORT I_CHAR * const EURO_DOLLAR       ;
   extern CLASS_IMPORT I_CHAR * const IRISH_POUNDS      ;
   extern CLASS_IMPORT I_CHAR * const LUXEMBOURG_FRANC  ;
   extern CLASS_IMPORT I_CHAR * const PORTUGUESE_ESCUDO ;
   extern CLASS_IMPORT I_CHAR * const USD               ;
   extern CLASS_IMPORT I_CHAR * const JAP_YEN           ;
   extern CLASS_IMPORT I_CHAR * const JAPANESE_YEN      ;
}

//******************************************************************************
void CurrencyClass::FormatValue( const DString& currencyCode, const DString& rawValue, DString& formatValue )
{
   FormatField( currencyCode, rawValue, formatValue );
}

//******************************************************************************
void CurrencyClass::FormatField( const DString& currencyCodeOrig, const DString& rawValue, DString& formatValue )
{
   BFData dd( ifds::CURRENCY_VW );

   DString dstrValue(rawValue);
   //dstrValue.strip().stripAll(I_CHAR(','));
   DSTCommonFunctions::stripSeparatorforDecimal(dstrValue);
   DString currencyCode( currencyCodeOrig );
   currencyCode.strip();
   currencyCode.upperCase();

   if( currencyCode == CRCY::JAPANESE_YEN || currencyCode == CRCY::JAP_YEN )
   {
      dd.setElementValue( ifds::JapaneseCurrency, dstrValue, false, false );
      formatValue = dd.getElementValue( ifds::JapaneseCurrency, BFDataField::USE_MASK );
   }
   else if( currencyCode == CRCY::CANADIAN_DOLLAR )
   {
      dd.setElementValue( ifds::CanadianCurrency, dstrValue, false, false );
      formatValue = dd.getElementValue( ifds::CanadianCurrency, BFDataField::USE_MASK );
   }
   else if( currencyCode == CRCY::USD )
   {
      dd.setElementValue( ifds::USDollar, dstrValue, false, false );
      formatValue = dd.getElementValue( ifds::USDollar, BFDataField::USE_MASK );
   }

   else if( currencyCode == CRCY::EURO_DOLLAR )
   {
      dd.setElementValue( ifds::EuroDollar, dstrValue, false, false );
      formatValue = dd.getElementValue( ifds::EuroDollar, BFDataField::USE_MASK );
   }

   else if( currencyCode == CRCY::IRISH_POUNDS )
   {
      dd.setElementValue( ifds::IrishPounds, dstrValue, false, false );
      formatValue = dd.getElementValue( ifds::IrishPounds, BFDataField::USE_MASK );
   }

   else if( currencyCode == CRCY::LUXEMBOURG_FRANC )
   {
      dd.setElementValue( ifds::LuxembourgFranc, dstrValue, false, false );
      formatValue = dd.getElementValue( ifds::LuxembourgFranc, BFDataField::USE_MASK );
   }

   else if( currencyCode == CRCY::PORTUGUESE_ESCUDO )
   {
      dd.setElementValue( ifds::PortugueseEscudo, dstrValue, false, false );
      formatValue = dd.getElementValue( ifds::PortugueseEscudo, BFDataField::USE_MASK );
   }
   else // if no valid currency is returned the default format will depend on the market registry setting
   {

      DString strMarket = DSTCommonFunctions::getMarket();
      if( strMarket == MARKET_IDS::CANADA )
      {
         dd.setElementValue( ifds::CanadianCurrency, dstrValue, false, false );
         formatValue = dd.getElementValue( ifds::CanadianCurrency, BFDataField::USE_MASK );
      }
      else if( strMarket == MARKET_IDS::JAPAN )
      {
         dd.setElementValue( ifds::JapaneseCurrency, dstrValue, false, false );
         formatValue = dd.getElementValue( ifds::JapaneseCurrency, BFDataField::USE_MASK );
      }
      else if( strMarket == MARKET_IDS::LUXEMBOURG )
      {
         dd.setElementValue( ifds::LuxembourgFranc, dstrValue, false, false );
         formatValue = dd.getElementValue( ifds::LuxembourgFranc, BFDataField::USE_MASK );
      }
   }


}

//******************************************************************************
void CurrencyClass::getFundCurrency( const DSTCWorkSession &workSession, 
                                     const DString& fundCode, 
                                     const DString& classCode, 
                                     DString& currency )
{

   FundDetailList *pFundDetailList;
   const_cast<MgmtCo &>(workSession.getMgmtCo()).getFundDetailList( pFundDetailList );

   if( pFundDetailList )
   {
      FundDetail *pFundDetail = NULL;
      if ( pFundDetailList->getFundDetail( fundCode, classCode, BF::HOST, pFundDetail ) )
      {
         pFundDetail->getField( ifds::Currency, currency, BF::HOST );
      }
      else
      {
         currency = NULL_STRING;
      }
   }
}

//******************************************************************************
int CurrencyClass::getPrecision( const DSTCWorkSession &workSession, const DString& dstrCurrency )
{
   const BFDataGroupId& idDataGroup = BF::HOST;

   CurrencyList *pCurrencyList;
   const_cast<MgmtCo &>(workSession.getMgmtCo()).getCurrencyList( pCurrencyList );

   int iRtn = 2;        //default as 2 decimals

   DString dstrTemp;
   workSession.getMgmtCoOptions()->getField(ifds::BusRounding, dstrTemp, idDataGroup, false);
   if( dstrTemp.strip() == YES )
   {
      BFData data;
      data.setElementValue(ifds::Currency, dstrCurrency, true, NULL);

      pCurrencyList->getStrKey( const_cast<DString&>(dstrCurrency), &data);
      BFObjIter iter(const_cast<CurrencyList &>(*pCurrencyList), idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED);
      if( iter.positionByKey(dstrCurrency) )
      {
         iter.getObject()->getField(ifds::Precision, dstrTemp, idDataGroup, false);
         iRtn = atoi(dstrTemp.asA().c_str());
      }
   }
   return(iRtn);
}

//******************************************************************************
DString& CurrencyClass::getFormattedValue( const DSTCWorkSession &workSession, 
                                           DString &dstrValue, 
                                           const DString& dstrSettleCurrency, 
                                           const DString& dstrAmountType)
{
   int iPrecision;

   DString dstrCurrency(dstrSettleCurrency);

   if( dstrCurrency.strip() == NULL_STRING )
   {

      DString strMarket = DSTCommonFunctions::getMarket();
      if( strMarket == MARKET_IDS::JAPAN )
         dstrCurrency = CRCY::JAPANESE_YEN;
      else if( strMarket == MARKET_IDS::CANADA )
         dstrCurrency = CRCY::CANADIAN_DOLLAR;
      else if( strMarket == MARKET_IDS::LUXEMBOURG )
         dstrCurrency = CRCY::EURO_DOLLAR;
   }

   //dstrValue.strip().stripAll(I_(','));
   DSTCommonFunctions::stripSeparatorforDecimal(dstrValue);
   dstrValue.stripLeading(I_('+')).stripTrailing(I_('.'));

   iPrecision = getPrecision( workSession, dstrCurrency );

   const BFFieldId& idField = ifds::USDollar;         //The formatting mask should be the same as the Amount field

   // following code has been moved to DSTCommonFunction.cpp  /*xyz Dec 14, 2001*/
   DSTCommonFunctions::formattedField( idField, iPrecision, dstrValue );
   return(dstrValue);
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/CurrencyClass.cpp-arc  $
 * 
 *    Rev 1.21   Jun 30 2005 12:38:52   popescu
 * Incident # 338532 - fixed nbr of decimals on the split commission screen for amounts and percentages  - amount fields are formatted to 2 decimals, percentages to 4
 * 
 *    Rev 1.20   Nov 29 2004 13:20:38   hernando
 * PET1117 - Tuning Project - Revised use of FundDetailList.
 * 
 *    Rev 1.19   Nov 14 2004 14:30:04   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.18   Apr 22 2003 14:49:10   FENGYONG
 * fix stripAll(',') for multilanguage
 * 
 *    Rev 1.17   Mar 21 2003 18:02:14   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.16   Oct 09 2002 23:54:10   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.15   Aug 29 2002 12:55:14   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.14   22 May 2002 18:26:42   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.13   Dec 17 2001 15:21:10   ZHANGCEL
 * Move the code thich is used for data format to DSTCommonFunction.
 * 
 *    Rev 1.12   03 May 2001 14:06:06   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.11   Mar 29 2001 15:58:00   DINACORN
 * Used DSTCommonFunctions MARKET_IDS constants
 * 
 *    Rev 1.10   Feb 12 2001 14:56:00   YINGBAOL
 * clean up and retrieve market from databroker
 * 
 *    Rev 1.9   Jan 17 2001 12:08:32   VASILEAD
 * Added workSessionId param for MgmtCo::getMgmtCoOptions()
 * 
 *    Rev 1.8   Dec 17 2000 20:22:52   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.7   Nov 24 2000 15:03:58   WINNIE
 * reverse currency
 * 
 *    Rev 1.6   Nov 02 2000 14:11:34   VASILEAD
 * Added workSeesionId parameter for Mgmtco based CBOs
 * 
 *    Rev 1.5   Jun 13 2000 18:23:26   DT24433
 * new Infra interfaces use ClientLocale
 // 
*/