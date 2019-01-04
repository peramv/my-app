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
// ^FILE   : ExchRateList.cpp
// ^AUTHOR : Winnie Shiu
// ^DATE   : April 28, 2000
//
// ^CLASS    : ExchRateList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "exchratelist.hpp"
#include <ifastdataimpl\dse_dstc0134_vw.hpp>
#include <ifastdataimpl\dse_dstc0134_req.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest EXCH_RATE;
}

namespace
{
   // Trace literals
   const I_CHAR *  CLASSNAME  = I_( "ExchRateList" );

}

//******************************************************************************
ExchRateList::ExchRateList( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
}

//******************************************************************************
ExchRateList::~ExchRateList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY ExchRateList::init()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   return(GETCURRENTHIGHESTSEVERITY());

}

//******************************************************************************
void ExchRateList::getStrKey ( DString& strKey, const BFData* data )
{
   TRACE_METHOD( CLASSNAME, I_( "getStrKey" ) );

   if( data )
   {
      DString dstFromCurrency  = data->getElementValue( I_( "FromCurrency" ));
      DString dstToCurrecy     = data->getElementValue( I_( "ToCurrency" ));
      DString dstEffectiveDate = data->getElementValue( I_( "EffectiveDate"));

      getStrKey ( strKey, dstFromCurrency, dstToCurrecy, dstEffectiveDate );
   }
   else
   {
      BFCBO::getStrKey( strKey, NULL );
   }
}

//******************************************************************************
void ExchRateList::getStrKey ( DString& strKey, const DString&  dstFromCurrency, 
                               const DString&  dstToCurrecy, const DString&  dstEffectiveDate )
{
   strKey = dstFromCurrency; 
   strKey.strip();
   strKey += I_(" ");
   strKey += dstToCurrecy;
   strKey.strip();
   strKey += I_(" ");
   strKey += dstEffectiveDate;
   strKey.strip();
   strKey.upperCase();
}

//******************************************************************************
double ExchRateList::getExchRate ( const DString& dstrFromCurrency, 
                                   const DString& dstrToCurrency, 
                                   DString& AsofDate, 
                                   const BFDataGroupId& idDataGroup,
                                   const DString& dstrTrack,
                                   const DString& dstrPageName,
                                   const DString& exactDate /*=I_("Y")*/)
{

   DString positionKey, dstrExchRate (NULL_STRING);
   BFData data;
   double dec_ExchRate = 1; // if no record in the database, default the exchange rate to 1

   ExchRateList *pExchRateList   = this;

   pExchRateList->getStrKey( positionKey, dstrFromCurrency, dstrToCurrency, AsofDate );

   BFObjIter iterExchRateList((*pExchRateList ), idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );

   if( iterExchRateList.positionByKey( positionKey ) )
   {
      DString dstrExchRate;
      iterExchRateList.getObject()->getField(ifds::ExchRate, dstrExchRate, BF::HOST, false  );
      dec_ExchRate = DSTCommonFunctions::convertToDouble( dstrExchRate );
   }
   else
   {
      BFData requestData(ifds::DSTC0134_REQ);

      DString mgmtCoIdOut;
      requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
      requestData.setElementValue( ifds::FromCurrency, dstrFromCurrency );
      requestData.setElementValue( ifds::ToCurrency,   dstrToCurrency);
      requestData.setElementValue( ifds::EffectiveDate,AsofDate, false, false );
      requestData.setElementValue( ifds::Track, dstrTrack );
      requestData.setElementValue( ifds::Activity, dstrPageName );
      //if exactDate = N get the most recent rate, if the rate of the effective does not available
      //else get the AsofDate exchange rate - one match
      requestData.setElementValue( ifds::ExactDate, exactDate ); 

      ReceiveData(DSTC_REQUEST::EXCH_RATE, requestData, ifds::DSTC0134_VW, DSTCRequestor( getSecurity(), true) );
   }

   if( dstrExchRate == NULL_STRING )
   {
      BFObjIter   iter( *this, BF::HOST );
      DString     dstFilter = NULL_STRING;
      BFAbstractCBO   * pCurrEntry   = NULL;

      getStrKey( dstFilter, dstrFromCurrency, dstrToCurrency, NULL_STRING );

      iter.setKeyFilter( dstFilter, true );  //we want the filter condition to match the begining of the key
      if( iter.end() )
      {
         dec_ExchRate = 0;
      }

      DString dstrDate (AsofDate), dstrCurrDate;

      while( !iter.end() ) // get the exchRate; get the most recent one if not available
      {
         pCurrEntry = iter.getObject();
         if( pCurrEntry != NULL )
         {
            pCurrEntry->getField( ifds::EffectiveDate, dstrCurrDate, BF::HOST, false );

            if( DSTCommonFunctions::CompareDates( AsofDate, dstrCurrDate) 
                == DSTCommonFunctions::FIRST_EARLIER )
            {
               break;
            }
            if( AsofDate == dstrCurrDate )
            {
               pCurrEntry->getField( ifds::ExchRate, dstrExchRate,  BF::HOST );
               pCurrEntry->getField( ifds::EffectiveDate, dstrDate, BF::HOST );
               break;
            }

            pCurrEntry->getField( ifds::ExchRate,      dstrExchRate,  BF::HOST );
            pCurrEntry->getField( ifds::EffectiveDate, dstrDate,      BF::HOST );
         }
         ++iter;      
      };

      dec_ExchRate = DSTCommonFunctions::convertToDouble( dstrExchRate ) ;
      AsofDate = dstrDate;
   }

   return(dec_ExchRate);

}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ExchRateList.cpp-arc  $
// 
//    Rev 1.17   16 Jun 2008 16:20:14   popescu
// Incident# 1315311 - param the Exact Date input field for view 134 that reads the exchange rates
// 
//    Rev 1.16   May 30 2008 04:28:36   wongsakw
// 1235049 SSIIL iFAST UAT issue - Unsettled Units Redemption Validation fx issue
// 
//    Rev 1.15   Nov 14 2004 14:39:56   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.14   Mar 21 2003 18:08:48   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.13   Oct 09 2002 23:54:28   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.12   Aug 29 2002 12:55:48   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.11   22 May 2002 18:28:34   PURDYECH
// BFData Implementation
// 
//    Rev 1.10   Feb 25 2002 18:55:42   PURDYECH
// Phase 1 of BFData Rollout - Base Component Compatibility
// 
//    Rev 1.9   Jul 12 2001 09:49:26   ZHANGCEL
// Set a new Element value: ExactDate for view134 view call. 
// 
//    Rev 1.8   03 May 2001 14:06:26   SMITHDAV
// Session management restructuring.
// 
//    Rev 1.7   Feb 05 2001 17:53:46   WINNIE
// move view call to getExchRate method and loop thru the list to get the most recent exchRate : bug fix for exchrate and return the exchrate date back to the calling program
// 
//    Rev 1.6   Jan 25 2001 13:56:20   YINGBAOL
// add eTrack
// 
//    Rev 1.5   Jan 18 2001 16:04:50   YINGBAOL
// add eTracker
// 
//    Rev 1.4   Dec 17 2000 20:23:24   OLTEANCR
// changed to use a precompiled header
// 
//    Rev 1.3   Dec 06 2000 11:21:48   OLTEANCR
// Changed ReveiveData
// 
//    Rev 1.2   Nov 02 2000 13:23:14   YINGBAOL
// use new databroker
// 
//    Rev 1.1   May 05 2000 10:55:12   WINNIE
// Get exchange rate
// 
//    Rev 1.0   May 01 2000 11:21:20   WINNIE
// Initial revision.
*/
