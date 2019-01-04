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
// ^FILE   : AcqFeeInquiry.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : AcqFeeInquiry
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "acqfeeinquiry.hpp"
#include "currencyclass.hpp"
#include <ifastdataimpl\dse_dstc0121_req.hpp>
#include <ifastdataimpl\dse_dstc0121_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ACQFEEINQUIRY;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
   { ifds::AcqFee,          BFCBO::NONE, 0 }, 
   { ifds::AcqFeeType,      BFCBO::NONE, 0 }, 
   { ifds::MaxFeeActive,    BFCBO::NONE, 0 }, 
   { ifds::MaxFee,          BFCBO::NONE, 0 }, 
   { ifds::MaxFeeType,      BFCBO::NONE, 0 }, 
   { ifds::MaxPercent,      BFCBO::NONE, 0 }, 
   { ifds::MaxFlatFundCurr, BFCBO::NONE, 0 }, 
};

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME   = I_( "AcqFeeInquiry" );
}

namespace CND
{  // Conditions used
   extern CLASS_IMPORT const long ERR_DATA_NOT_FOUND;
}

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************
AcqFeeInquiry::AcqFeeInquiry( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );

   _dstrFundCurrency = NULL_STRING;

   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}

//******************************************************************************
AcqFeeInquiry::~AcqFeeInquiry()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY AcqFeeInquiry::init()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AcqFeeInquiry::init( const DString& dstrTaxType,
                              const DString& dstrTransType,
                              const DString& dstrEffectiveDate,
                              const DString& dstrAmount,
                              const DString& dstrAmountType,
                              const DString& dstrFundCode,
                              const DString& dstrClassCode,
                              const DString& dstrCurrency,
                              const DString& dstrBrokerCode,
                              const DString& dstrFundToCode,
                              const DString& dstrClassToCode,
										const DString& dstrFlatPercent,
                              const DString& dstrTrack,
                              const DString& dstrPageName,
										const DString& dstrToTaxType,
										const DString& AcctNumbr,
							  const DString& tradeInDate)

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   SEVERITY sevRtn = SEVERE_ERROR;

   BFData queryData(ifds::DSTC0121_REQ);
   BFData *response = new BFData(ifds::DSTC0121_VW);

   DString mgmtCoIdOut;
   queryData.setElementValue( ifds::CompanyId,       getMgmtCoId( mgmtCoIdOut ) );
   queryData.setElementValue( ifds::TaxType,         dstrTaxType );
   queryData.setElementValue( ifds::TransType,       dstrTransType );
   queryData.setElementValue( ifds::EffectiveDate,   dstrEffectiveDate, false, false );
   queryData.setElementValue( ifds::Amount,          dstrAmount );
   queryData.setElementValue( ifds::AmountType,      dstrAmountType );
   queryData.setElementValue( ifds::FundCode,        dstrFundCode );
   queryData.setElementValue( ifds::ClassCode,       dstrClassCode );
   queryData.setElementValue( ifds::Currency,        dstrCurrency );
   queryData.setElementValue( ifds::ExchRate,        I_("0") );
   queryData.setElementValue( ifds::BrokerCode,      dstrBrokerCode );
   queryData.setElementValue( ifds::FundToCode,      dstrFundToCode );
   queryData.setElementValue( ifds::ClassToCode,     dstrClassToCode );
   queryData.setElementValue( ifds::Track,			  dstrTrack );
   queryData.setElementValue( ifds::Activity,		  dstrPageName );
   queryData.setElementValue( ifds::FlatPercent,	  dstrFlatPercent );
   queryData.setElementValue( ifds::ToAcctTaxType,	  dstrToTaxType );
   queryData.setElementValue( ifds::AccountNum,	  AcctNumbr );
   queryData.setElementValue( ifds::TradeInDate,      tradeInDate );


   acqFeeTaxType        = dstrTaxType;
   acqFeeTransType      = dstrTransType;
   acqFeeEffectiveDate  = dstrEffectiveDate;
   acqFeeAmount         = dstrAmount;
   acqFeeAmountType     = dstrAmountType; 
   acqFeeFromFund       = dstrFundCode;
   acqFeeFromClass      = dstrClassCode;
   acqFeeCurrency       = dstrCurrency;
   acqFeeBrokerCode     = dstrBrokerCode;
   acqFeeToFund         = dstrFundToCode;
   acqFeeToClass        = dstrClassToCode;
   acqFlatPercent       = dstrFlatPercent;



   if( BFDataBroker::getInstance()->receive( DSTC_REQUEST::ACQFEEINQUIRY, 
                                             queryData, 
                                             *response, 
                                             DSTCRequestor( getSecurity() ) ) > NO_CONDITION )
   {
      delete response;
      response = NULL;
      //	ADDCONDITION...;
   }
   else
   {
      attachDataObject( *response, true, false );
      createObjectForEachRepeat( *response );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void AcqFeeInquiry::getField( const BFFieldId& idField, 
                              DString& strFieldValue, 
                              const BFDataGroupId& idDataGroup, 
                              bool formattedReturn ) const
{
   BFCBO::getField(idField, strFieldValue, idDataGroup, formattedReturn );

   if( formattedReturn )
   {
      if( idField == ifds::MaxFlatFundCurr )
      {
         if( _dstrFundCurrency != NULL_STRING )
         {
            BFCBO::getField(idField, strFieldValue, idDataGroup, false );
            CurrencyClass::FormatValue(_dstrFundCurrency, strFieldValue, strFieldValue);
         }
      }
      else if( idField == ifds::MaxPercent )
      {
         BFData dd(ifds::DSTC0121_VW);

         BFCBO::getField(idField, strFieldValue, idDataGroup, false );
         dd.setElementValue(idField, strFieldValue, false, false );
         strFieldValue = dd.getElementValue(idField, 2/*DataElement::USE_MASK*/, I_("#,###,###,###,##0.0000"));
      }
      else if( idField == ifds::AcqFee )
      {
         DString dstrAcqFeeType;
         getField(ifds::AcqFeeType, dstrAcqFeeType, idDataGroup, false);
         if( dstrAcqFeeType == I_("0") )      //Flat
         {
            if( _dstrFundCurrency != NULL_STRING )
            {
               BFCBO::getField(idField, strFieldValue, idDataGroup, false);
               CurrencyClass::FormatValue(_dstrFundCurrency, strFieldValue, strFieldValue);
            }
         }
         else
         {
            BFData dd(ifds::DSTC0121_VW);

            BFCBO::getField(idField, strFieldValue, idDataGroup, false );
            dd.setElementValue(idField, strFieldValue, false, false );
            strFieldValue = dd.getElementValue(idField, 2/*DataElement::USE_MASK*/, I_("#,###,###,###,##0.0000"));
         }
      }
   }
}

//******************************************************************************
bool AcqFeeInquiry::recordMatch( const DString& tradeTaxType, const DString& tradeTransType, 
                                 const DString& tradeTradeDate, const DString& tradeAmount, 
                                 const DString& tradeAmountType, const DString& tradeFromFund, 
                                 const DString& tradeFromClass, const DString& tradeCurrency, 
                                 const DString& tradeBrokerCode, const DString& tradeToFund, 
                                 const DString& tradeToClass, const BFDataGroupId& idDataGroup )
{
   bool match = false;

   match = ( acqFeeTaxType      == tradeTaxType        &&
             acqFeeTransType    == tradeTransType      &&
             acqFeeEffectiveDate== tradeTradeDate      &&
             acqFeeAmount       == tradeAmount         &&
             acqFeeAmountType   == tradeAmountType     &&
             acqFeeFromFund     == tradeFromFund       &&
             acqFeeFromClass    == tradeFromClass      &&
             acqFeeCurrency     == tradeCurrency       &&
             acqFeeToFund       == tradeToFund         &&
             acqFeeToClass      == tradeToClass ) ;

   return(match);

}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AcqFeeInquiry.cpp-arc  $
 // 
 //    Rev 1.19   Apr 24 2012 20:37:14   wp040039
 // PETP0187485-CPF-Trade Entry And Processing
 // 
 //    Rev 1.18   Oct 05 2006 17:29:22   AGUILAAM
 // IN 721266 - new field ToAcctTaxType to get applicable transfer fees.
 // 
 //    Rev 1.17   Nov 14 2004 14:25:26   purdyech
 // PET910 - .NET Conversion
 // 
 //    Rev 1.16   Mar 21 2003 17:56:20   PURDYECH
 // BFDataGroupId/BFContainerId changeover
 // 
 //    Rev 1.15   Oct 09 2002 23:53:58   PURDYECH
 // PVCS Database Conversion
 // 
 //    Rev 1.14   Aug 29 2002 12:54:58   SMITHDAV
 // ClientLocale and typed field changes.
 // 
 //    Rev 1.13   22 May 2002 18:26:20   PURDYECH
 // BFData Implementation
 // 
 //    Rev 1.12   03 May 2001 14:05:54   SMITHDAV
 // Session management restructuring.
 // 
 //    Rev 1.11   Apr 02 2001 15:06:52   OLTEANCR
 // fix: setElementValue(ifds::EffectiveDate,..  )
 // 
 //    Rev 1.10   Mar 29 2001 12:16:16   FENGYONG
 // + flatpercent
 // 
 //    Rev 1.9   Jan 18 2001 16:03:26   YINGBAOL
 // add eTracker
 // 
 //    Rev 1.8   Dec 17 2000 20:22:24   OLTEANCR
 // changed to use a precompiled header
 // 
 //    Rev 1.7   15 Nov 2000 15:30:14   SMITHDAV
 // Use new ReceiveData and do some cleanup.
 // 
 //    Rev 1.6   Nov 07 2000 15:52:38   OLTEANCR
 // new data brokering
 // 
 //    Rev 1.5   Nov 02 2000 16:30:14   HUANGSHA
 // change in getField
 // 
 //    Rev 1.4   Sep 01 2000 15:25:22   HUANGSHA
 // added pClientLocale in setField(...)
 // 
 //    Rev 1.3   Jun 13 2000 17:55:50   DT24433
 // new Infra interfaces use ClientLocale
 * 
 */