//*****************************************************************************
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
//*****************************************************************************
//
// ^FILE   : HistoricalMarketValueList.cpp
// ^AUTHOR : Yakov Prager
// ^DATE   : April 6, 1999
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : HistoricalMarketValueList
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include "historicalmarketvaluelist.hpp"
#include "historicalmarketvalue.hpp"
#include "currencyclass.hpp"
#include "mfaccount.hpp"
#include <ifastdataimpl\dse_dstc0020_vw.hpp>
#include <ifastdataimpl\dse_dstc0020_req.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest HISTORICAL_MARKET_VALUE;
}

namespace
{
   const I_CHAR * const CLASSNAME      = I_( "HistoricalMarketValueList" );
   const I_CHAR * const SPACE		   = I_( " " );
}

//*****************************************************************************
HistoricalMarketValueList::HistoricalMarketValueList( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
}

//*****************************************************************************
HistoricalMarketValueList::~HistoricalMarketValueList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//*****************************************************************************
//
// Initialization from Account Number, StartDate, EndDate, IncUnsettled and Fund Code
//
SEVERITY HistoricalMarketValueList::init( const DString&  strAccountNumber, 
                                          const DString&  strAsOfDate,
                                          const DString& dstrTrack,
                                          const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   BFData queryData(ifds::DSTC0020_REQ);

   DString mgmtCoIdOut;
   queryData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   queryData.setElementValue( ifds::AccountNum, strAccountNumber );
   queryData.setElementValue( ifds::AsofDate, strAsOfDate, false, false );
   queryData.setElementValue( ifds::Track, dstrTrack );
   queryData.setElementValue( ifds::Activity, dstrPageName );
   queryData.setElementValue( ifds::CalculateACB, I_("Y"), false, false );
   queryData.setElementValue (ifds::ConvertAmount, I_("Y"), false, false);

   ReceiveData( DSTC_REQUEST::HISTORICAL_MARKET_VALUE, queryData, ifds::DSTC0020_VW, DSTCRequestor( getSecurity() ) );

   queryData.setElementValue (ifds::TotalOnly, I_("Y"), false, false);
   ReceiveData( DSTC_REQUEST::HISTORICAL_MARKET_VALUE, queryData, ifds::DSTC0020_VW, DSTCRequestor( getSecurity() ) );

   return(GETCURRENTHIGHESTSEVERITY());
}



//*****************************************************************************
SEVERITY HistoricalMarketValueList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );
   pObjOut = new HistoricalMarketValue( *this );
   ( ( HistoricalMarketValue* ) ( pObjOut ) )->init( const_cast<BFData&>(data) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************
void HistoricalMarketValueList::getField( const BFFieldId& idField, 
                                          DString& strFieldValue, 
                                          const BFDataGroupId& idDataGroup, 
                                          bool formattedReturn ) const
{
   BFCBO::getField( idField, strFieldValue, idDataGroup, formattedReturn );

   if( (idField == ifds::SettledValue     || 
        idField == ifds::UnsettledValue ) &&
       formattedReturn )
   {
      DString currency, fundCode, classCode;
      getField( ifds::rxFundCode, fundCode, idDataGroup, true );
      getField( ifds::rxClassCode, classCode, idDataGroup, true );
      CurrencyClass::getFundCurrency( getWorkSession(), fundCode, classCode, currency );
      currency.strip();

      BFCBO::getField( idField, strFieldValue, idDataGroup, false );
      CurrencyClass::FormatValue( currency, strFieldValue, strFieldValue );
   }
}

/**
 * This method is not highly efficient, since it is walking the HistoricalMarketValue list
 * every time it is called. Due to time constraints this soultion has been
 * chosen. Generally, this list is not that large. Time permmitting another
 * implementation will be made. (SP)
 **/
SEVERITY HistoricalMarketValueList::calculateFundGroupTotal(DString& fundGroup, 
   DString& dstrTotal, const BFDataGroupId& idDataGroup)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_( "calculateFundGroupTotal" ));

   BFObjIter iter(*this, idDataGroup, 0, BFObjIter::ITERTYPE::NON_DELETED);
   double dTotal = 0.0;

   iter.begin();
   while(!iter.end())
   {
      DString dstrFundGroup;
      iter.getObject()->getField(ifds::FundGroup, dstrFundGroup, 
         idDataGroup);
      if (fundGroup == dstrFundGroup)
      {
         DString dstrSettledValueAcctCurr;
         double dSettledValueAcctCurr = 0.0;
         
         iter.getObject()->getField(ifds::SettledValueAcctCurr, 
            dstrSettledValueAcctCurr, idDataGroup);
         dSettledValueAcctCurr = DSTCommonFunctions::
            convertToDouble(dstrSettledValueAcctCurr);
         dTotal += dSettledValueAcctCurr;
      }
      ++iter;
   }
   dstrTotal = DSTCommonFunctions::doubleToDString(ifds::SettledValueAcctCurr, 
      dTotal);
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

void HistoricalMarketValueList::getStrKey ( DString& strKey, const BFData* data )
{
   if( data )
   {
      DString dstrFund      = data->getElementValue( ifds::rxFundCode );
      DString dstrClass     = data->getElementValue( ifds::rxClassCode );
      DString dstrFundGroup = data->getElementValue( ifds::FundGroup );
      strKey = dstrFundGroup+SPACE+dstrFund+SPACE+dstrClass;           
   }
   else
   {
      BFCBO::getStrKey( strKey, NULL );
   }
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/HistoricalMarketValueList.cpp-arc  $
 * 
 *    Rev 1.18   May 29 2007 12:12:22   jankovii
 * Incident #899142 - cannot place trade.
 * 
 *    Rev 1.17   Nov 14 2004 14:44:10   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.16   Apr 15 2003 10:49:08   linmay
 * Sync up with 1.14.1.0
 * 
 *    Rev 1.15   Mar 21 2003 18:13:36   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.14   Feb 17 2003 14:23:56   popescu
 * Added a field for th calculation of the total market value by FundGroup
 * 
 *    Rev 1.13   Oct 09 2002 23:54:38   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.12   Aug 29 2002 12:56:02   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.11   Jun 10 2002 17:03:20   KOVACSRO
 * Formatted versus unformatted.
 * 
 *    Rev 1.10   22 May 2002 18:28:52   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.9   Feb 05 2002 10:45:34   YINGBAOL
 * create CBO for this list
 * 
 *    Rev 1.8   28 Dec 2001 10:33:10   KOVACSRO
 * Added CalculateACB field.
 * 
 *    Rev 1.7   Sep 21 2001 16:11:08   YINGBAOL
 * fix memory leak
 * 
 *    Rev 1.6   03 May 2001 14:06:40   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.5   Jan 18 2001 16:05:14   YINGBAOL
 * add eTracker
 * 
 *    Rev 1.4   Dec 17 2000 20:23:48   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.3   Dec 06 2000 11:57:06   OLTEANCR
 * modif. ReceiveData
 * 
 *    Rev 1.2   Nov 07 2000 15:23:34   OLTEANCR
 * new data broker
 * 
 *    Rev 1.1   May 04 2000 16:56:18   WINNIE
 * change CURRENCY_HPP to CURRENCYCLASS_HPP
 * 
 *    Rev 1.0   Feb 15 2000 11:00:00   SMITHDAV
 * Initial revision.
 * 
 *    Rev 1.8   Jan 05 2000 20:10:52   BUZILA
 * adding list flag
 * 
 *    Rev 1.7   Dec 12 1999 16:25:36   POPESCUS
 * Xchgdata issue; create and delete the object in the CBO
// 
*/