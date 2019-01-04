#include "stdafx.h"
#include <ifastdataimpl\dse_dstc0083_vw.hpp>
#include <ifastdataimpl\dse_dstc0130_req.hpp>
#include <ifastdataimpl\dse_dstc0130_vw.hpp>
#include "rrif_lif_lrif_paymentscalculation.hpp"
#include "rrif_lif_lrif_info.hpp"

namespace ifds
{
   extern CLASS_IMPORT const BFDecimalFieldId RRIFAmount;
}


namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest RRIF_LIF_LRIF_PAYMENT_CALC;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "RRIF_LIF_LRIF_PaymentsCalculation" );
   const I_CHAR * const DATE_FORMAT = I_( "MMddyyyy" );      

}

//******************************************************************************
RRIF_LIF_LRIF_PaymentsCalculation::RRIF_LIF_LRIF_PaymentsCalculation( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
}

//******************************************************************************
RRIF_LIF_LRIF_PaymentsCalculation::~RRIF_LIF_LRIF_PaymentsCalculation()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
SEVERITY RRIF_LIF_LRIF_PaymentsCalculation::init()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY RRIF_LIF_LRIF_PaymentsCalculation::init( const DString& accountNum,
                                                  const DString& callNum, 
                                                  RRIF_LIF_LRIF_Info* rrifInfo, 
                                                  const BFDataGroupId& idDataGroup,
                                                  bool bFirstCall,
                                                  bool bAddMode, 
                                                  const DString& dstrTrack,
                                                  const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   SEVERITY sevRtn = SEVERE_ERROR;
   BFData *requestData = new BFData(ifds::DSTC0130_REQ);
   DString strCurrBusDate = NULL_STRING;
   DString strEffectiveDate = NULL_STRING;
   DString strEffectiveFrom = NULL_STRING;
   DString strCallNum = callNum;
   DString str = NULL_STRING;
   DString strRunMode = NULL_STRING;
   DString strCalcFedProvTax = NULL_STRING;

   const BFFieldId request[]=
   {
      ifds::Amount,
      ifds::April,
      ifds::August,
      ifds::December,
      ifds::February, 
      ifds::FedRate,
      ifds::FedRatePUD,
      ifds::GoodBad,
      ifds::GrossNetMethod,
      ifds::January,
      ifds::June,
      ifds::July,
      ifds::MandAmtPay,
      ifds::MandAmtYr,
      ifds::March,
      ifds::MaxAmtYr,
      ifds::May,
      ifds::NetAmt,
      ifds::November,
      ifds::October,
      ifds::OverrideAmtYr,
      ifds::OverrideUnusedMax,
      ifds::PayOption,
      ifds::ProvRate,
      ifds::ProvRatePUD,
      ifds::PYUnusedMax,
      ifds::Qualified,
      ifds::RecordType,
      ifds::September,
      ifds::SpouseBirth,
      ifds::StopDate,
      ifds::SuppFedTax,
      ifds::SuppProvTax,
      ifds::TaxOnMin,
      ifds::CalcFedProvTax, 
      ifds::RIFId,
      ifds::PreYrPercent,
      ifds::LastProcessDate,
      ifds::Frequency,
      ifds::DayOfWeek,
      ifds::DaysOfMonth,
	  ifds::ExternalAssets, //P0186486_FN03 - RRIF Annuities
      ifds::NullFieldId
   };

   getWorkSession().getOption( ifds::CurrBusDate, strCurrBusDate, idDataGroup, false );

   rrifInfo->getField( ifds::EffectiveFrom, strEffectiveDate, idDataGroup );
   //It is a mess: in views 67, 129 what is called EffectiveDate in Progress is called EffectiveFrom in Data Dictionary.
   //Meanwhile, in view 130 the Data Dictionary correctly reflects the EffectiveDate and EffectiveFrom fields from the view.
   //This is why I assign DBR::EffectiveFrom to a variable called strEffectiveDate. :-(

   if( I_("2") == callNum ) // second call
   {
      strCallNum = I_("2");
      // Now populate everything. 
      int i = 0;
      BFFieldId idField = request[0];
      while( idField != ifds::NullFieldId )
      {
         rrifInfo->getField( idField, str, idDataGroup );		 
         requestData->setElementValue( idField, str,false,false );
         i++;
         idField = request[i]; 
      }
   }
   requestData->setElementValue( ifds::RecordType, I_("M") ,false,false );

   rrifInfo->getField( ifds::RRIFAmount, str, idDataGroup );
   requestData->setElementValue( ifds::Amount, str ,false,false );

   DString strQualified;
   rrifInfo->getField( ifds::Qualified, strQualified, idDataGroup, false );
   strQualified.strip().upperCase();
   
   if (strQualified.empty())
   {
      // make sure that this field is not blank, then it won't cause RTS a problem.
      strQualified = I_("N");
   }
   
   requestData->setElementValue( ifds::Qualified, strQualified ,false,false );

   int yearEffectiveDate = 0;
   int yearCurrBusDate = 0;
   extractFieldFromDate( strCurrBusDate, yearCurrBusDate );
   extractFieldFromDate( strEffectiveDate, yearEffectiveDate );
   strEffectiveFrom = strEffectiveDate;

   if( bFirstCall )
   { // first call 
      if( strCallNum == I_("1") )
      { //add mode
         strRunMode = I_("A");
         strEffectiveFrom = strCurrBusDate;  
         rrifInfo->getField( ifds::StopDate, str, idDataGroup );
		 requestData->setElementValue( ifds::StopDate, str,false,false );
		 requestData->setElementValue( ifds::Frequency , I_("3"),false,false );//monthly
      }
      else if( strCallNum == I_("2") )
      {
         strRunMode = I_("M");
         if( yearEffectiveDate < yearCurrBusDate )
         {
            // Set EffectiveFrom to December 31, year of EffectiveDate. 
            SetDayMonthToDate( strEffectiveFrom, I_("12"), I_("31") );
         }
         else
         {
            SetDayMonthToDate( strEffectiveFrom, I_("01"), I_("01") );
         }

      }

   }
   else
   { // not first call  
      if( bAddMode )
         strRunMode = I_("A");
      else strRunMode = I_("M");
      if( yearEffectiveDate < yearCurrBusDate )
      {
         SetDayMonthToDate( strEffectiveFrom, I_("12"), I_("31") );      
      }
      else
      {
         strEffectiveFrom = strCurrBusDate;
      }   
   }

   //PTS 10015081 we will override the PayOption when it is percentage with F since
   //the base system does not support P as PayOption.
   DString dstrTemp;
   requestData->getElementValue( ifds::PayOption, dstrTemp ); 
   if ( dstrTemp.strip() == I_("P") )
      requestData->setElementValue( ifds::PayOption, I_("F")); 

   DString mgmtCoIdOut;
   requestData->setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   requestData->setElementValue( ifds::CallNum, strCallNum );
   requestData->setElementValue( ifds::EffectiveFrom, strEffectiveFrom,false,false );
   requestData->setElementValue( ifds::AccountNum, accountNum );
   requestData->setElementValue( ifds::EffectiveDate, strEffectiveDate,false,false );
   requestData->setElementValue( ifds::RunMode, strRunMode ); 

   requestData->setElementValue( ifds::Track, dstrTrack );
   requestData->setElementValue( ifds::Activity, dstrPageName );

   ReceiveData(DSTC_REQUEST::RRIF_LIF_LRIF_PAYMENT_CALC, *requestData, ifds::DSTC0130_VW, DSTCRequestor( getSecurity(), false) );
   delete requestData;
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
// strDateField must be "dd" to extract a day, "yyyy" for year and "MM" for month.
// strDateField defaults to "yyyy"
SEVERITY RRIF_LIF_LRIF_PaymentsCalculation::extractFieldFromDate( DString const &strField, int &field, DString strDateField )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "extractFieldFromDate" ) );
   // look in the registry for the date format mask
   // the current date should be in host format
   DString dstrConfiguration( I_( "HostMasks" ) );
   DString dstrKey( I_("D") );
   DString mask = GetConfigValueAsString( I_( "LocaleFormats" ), dstrConfiguration, dstrKey );

   DString strDateFld;
   int field_pos = mask.find( strDateField);

   if( strField == NULL_STRING )
   {
//      ADDCONDITIONFROMFILE( CND::ERR_ENTRY_EMPTY_OR_CONTAINS_ONLY_SPACE );
      field = 0;
   }
   else if( DString::npos != field_pos )
   {
      strDateFld.assign( strField, field_pos, strDateField.length() );
      field = convertToULong( strDateFld );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY RRIF_LIF_LRIF_PaymentsCalculation::SetDayMonthToDate( DString  &strField, DString const &strMonth, DString const &strDay )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "extractFieldFromDate" ) );
   // Look in the registry for the date format mask. The current date should be in host format.
   DString dstrConfiguration( I_( "HostMasks" ) );
   DString dstrKey( I_("D") );
   DString mask = GetConfigValueAsString( I_( "LocaleFormats" ), dstrConfiguration, dstrKey );

   // Set strField month and day. 
   int field_pos = mask.find( I_("dd") ); 
   strField.replace( field_pos, 2, strDay ); //set the day
   field_pos = mask.find( I_("MM") ); 
   strField.replace( field_pos, 2, strMonth ); //set the month

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/RRIF_LIF_LRIF_PaymentsCalculation.cpp-arc  $
// 
//    Rev 1.29   Mar 02 2012 07:28:12   panatcha
// IN2866702 : fix the issue relating to the update of the PYE 
// 
//    Rev 1.28   Jan 18 2011 20:54:08   dchatcha
// IN# 2393765 - Major alert for Mifprod at 19:06 RTS Error 9
// 
//    Rev 1.27   Oct 04 2010 06:40:52   kitticha
// PET0168176 FN01 Locked In Product Changes.
// 
//    Rev 1.26   19 Mar 2009 14:42:00   kovacsro
// IN#1490538 - Error message when creating a LIF record with "Maximum" pay option (redesigned view 130 call and eliminated calls to view 375)
// 
//    Rev 1.25   Nov 30 2007 18:26:24   daechach
// PET5517 FN 97 - RRIF Net of Fees
// 
//    Rev 1.24   02 Oct 2007 14:23:42   kovacsro
// IN#984422 - set StopDate and Frequency fields for 130 request
// 
//    Rev 1.23   Aug 10 2007 17:07:06   smithdav
// PET2360 FN76,91
// 
//    Rev 1.22   Nov 14 2004 14:53:18   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.21   May 16 2003 06:28:52   HSUCHIN
// sync up to 1.18.1.1 - PTS 10016461
// 
//    Rev 1.20   Apr 12 2003 17:43:58   HERNANDO
// Sync 1.18.1.0; PTS 10015081.
// 
//    Rev 1.19   Mar 21 2003 18:22:46   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.18   Feb 06 2003 13:45:56   YINGBAOL
// previous year percent is part of view 130 now
// 
//    Rev 1.17   Oct 09 2002 23:54:54   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.16   Sep 04 2002 18:44:54   PURDYECH
// Corrected incorrect use of BFFieldId arrays.
// 
//    Rev 1.15   Aug 29 2002 12:56:32   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.14   22 May 2002 18:29:48   PURDYECH
// BFData Implementation
// 
//    Rev 1.13   Nov 14 2001 15:36:50   YINGBAOL
// code clean up
// 
//    Rev 1.12   Aug 25 2001 14:07:50   YINGBAOL
// set rectype value
// 
//    Rev 1.11   03 May 2001 14:07:04   SMITHDAV
// Session management restructuring.
// 
//    Rev 1.10   Jan 18 2001 16:09:42   YINGBAOL
// add eTracker
// 
//    Rev 1.9   Dec 17 2000 20:24:26   OLTEANCR
// changed to use a precompiled header
// 
//    Rev 1.8   Dec 06 2000 14:43:52   OLTEANCR
// modif. ReceiveData
// 
//    Rev 1.7   Nov 07 2000 13:21:44   YINGBAOL
// small change for setelement value
// 
//    Rev 1.6   Nov 02 2000 13:22:48   YINGBAOL
// use new databroker
// 
//    Rev 1.5   Sep 28 2000 15:04:06   YINGBAOL
// change make view call logic
// 
//    Rev 1.4   Jun 28 2000 15:01:04   PETOLESC
// Added Frequency field, changed logic for view 130 call sequence and a BIG bunch of other changes.
// 
//    Rev 1.3   Jun 09 2000 18:01:28   PETOLESC
// Save work.
// 
//    Rev 1.2   May 19 2000 17:30:12   PETOLESC
// save work
// 
//    Rev 1.1   May 08 2000 12:01:10   PETOLESC
// Commented getField(DBR::EFFECTIVE_DATE,...).
// 
//    Rev 1.0   May 04 2000 13:46:00   PETOLESC
// Initial revision.
 * 
 *
 */
