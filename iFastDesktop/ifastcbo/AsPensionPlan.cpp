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
// ^FILE   : AsPensionPlan.cpp
// ^AUTHOR : Karen Jan
// ^DATE   : July 24, 2001
//
// ^CLASS    : AsPensionPlan
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "aspensionplan.hpp"
#include <bfcbo\bfworksession.hpp>
#include "dstcommonfunction.hpp"
#include "entity.hpp"
#include "accountentityxref.hpp"
#include <ifastdataimpl\dse_dstc0171_vw.hpp>
#include <ifastdataimpl\dse_dstc0171_req.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest AS_PENSION_PLAN;
}

namespace
{
   const I_CHAR * const CLASSNAME = I_( "AsPensionPlan" );

   //Status
   const I_CHAR * const EARLY_MATURITY = I_( "01" );
   const I_CHAR * const INCAPACITATED  = I_( "02" );
   const I_CHAR * const UNEMPLOYEC     = I_( "03" );

}

namespace ifds
{
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFDateFieldId StartDate;
   extern CLASS_IMPORT const BFDateFieldId EndDate;
   extern CLASS_IMPORT const BFTextFieldId ASStatus;
   extern CLASS_IMPORT const BFDateFieldId MaturDate;
   extern CLASS_IMPORT const BFNumericFieldId AccountNum;
   extern CLASS_IMPORT const BFDateFieldId DofBirth;
   extern CLASS_IMPORT const BFNumericFieldId EntityId;
}

namespace CND
{  
   // Conditions used
   extern const long ERR_EARLY_TERMINATION;
   extern const long ERR_INVALID_END_START_DATE;
   extern const long ERR_LATER_ENDDATE_MATURITY_DATE;
   extern const long ERR_ENDDATE_MATURITY_DATE;
   extern const long ERR_QUARTEREND_MATURITY_DATE;
   extern const long ERR_MONTHEND_MATURITY_DATE;
   extern const long ERR_LATER_QUARTEREND_MATURITY_DATE;
   extern const long ERR_LATER_MONTHEND_MATURITY_DATE;
   extern const long ERR_INVALID_END_BIRTH_DATE;
   extern const long ERR_INVALID_EARLY_END_DATE;

}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,            State Flags,             Group Flags 
   { ifds::MaturDate, BFCBO::NONE, 0 }, 
   { ifds::StartDate, BFCBO::NONE, 0 }, 
   { ifds::EndDate,   BFCBO::NONE, 0 }, 
   { ifds::ASStatus,  BFCBO::NONE, 0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//****************************************************************************
AsPensionPlan::AsPensionPlan( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent )
, dstrMaturDate_( NULL_STRING )
, currBusinessDate_( NULL_STRING )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}

//****************************************************************************
AsPensionPlan::~AsPensionPlan()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//****************************************************************************
SEVERITY AsPensionPlan::init( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   setObjectNew();
   doInitWithDefaultValues( idDataGroup );
   clearUpdatedFlags( idDataGroup, false );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY AsPensionPlan::init( const DString& accountNum, 
                              const BFDataGroupId& idDataGroup, 
                              const DString& dstrTrack,
                              const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   BFData queryData(ifds::DSTC0171_REQ);

   DString mgmtCoIdOut;
   queryData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   queryData.setElementValue( ifds::AccountNum, accountNum );
   queryData.setElementValue( ifds::Track, dstrTrack );
   queryData.setElementValue( ifds::Activity, dstrPageName );

   SEVERITY sev = ReceiveData( DSTC_REQUEST::AS_PENSION_PLAN, queryData, ifds::DSTC0171_VW, DSTCRequestor( getSecurity(),true,true ) );

   //we just made a view call : data came from database : idDataGroup should be always BF::HOST
   setFieldSubstituteValues( ifds::ASStatus, BF::HOST, ifds::ASStatus );

   DString dstrASStatus;
   getField( ifds::ASStatus, dstrASStatus, BF::HOST );
   getField( ifds::MaturDate, dstrMaturDate_, BF::HOST );
   getWorkSession().getOption( ifds::CurrBusDate, currBusinessDate_, BF::HOST, false );

   setFieldReadOnly( ifds::ASStatus, BF::HOST, false );

   if( dstrASStatus == NULL_STRING )
   {
      setFieldReadOnly( ifds::StartDate, BF::HOST, false );
      setFieldReadOnly( ifds::EndDate, BF::HOST, false );
      setFieldReadOnly( ifds::MaturDate, BF::HOST, true );
   }
   else
   {
      setFieldReadOnly( ifds::StartDate, BF::HOST, true );
      setFieldReadOnly( ifds::EndDate, BF::HOST, true );
      setFieldReadOnly( ifds::MaturDate, BF::HOST, false );
   }

   return(GETCURRENTHIGHESTSEVERITY());

}

//*********************************************************************************
void AsPensionPlan::doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
{
   if( getWorkSession().getOption( ifds::CurrBusDate, currBusinessDate_, idDataGroup, false ) <= WARNING )
   {
      setFieldNoValidate( ifds::StartDate, currBusinessDate_, BF::HOST, false );

   }

   setEndDate( idDataGroup );
   setFieldNoValidate( ifds::MaturDate, NULL_STRING, idDataGroup, false );
   setFieldNoValidate( ifds::ASStatus, NULL_STRING, idDataGroup, false );

   setFieldReadOnly( ifds::StartDate, idDataGroup, false );
   setFieldReadOnly( ifds::EndDate, idDataGroup, false );
   setFieldReadOnly( ifds::ASStatus, idDataGroup, true );  //status should be read only when create a new one as Base does
}

//******************************************************************************
SEVERITY AsPensionPlan::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAME2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );

   if( idField == ifds::StartDate )
   {
      setEndDate( idDataGroup );
   }
   else if( idField == ifds::EndDate )
   {
      DString dstrEndDate;
      getField( ifds::EndDate, dstrEndDate, idDataGroup );

      setFieldNoValidate( ifds::MaturDate, dstrEndDate, idDataGroup, false, true, true  );

   }
   else if( idField == ifds::ASStatus )
   {
      DString dstrASStatus, dstrEndDate, dstrStartDate;
      getField( ifds::ASStatus, dstrASStatus, idDataGroup );
      getField( ifds::EndDate, dstrEndDate, idDataGroup );
      getField( ifds::StartDate, dstrStartDate, idDataGroup );

      if( dstrASStatus == NULL_STRING )
      {
         setFieldReadOnly( ifds::StartDate, idDataGroup, false );
         setFieldReadOnly( ifds::EndDate, idDataGroup, false );
         setFieldReadOnly( ifds::MaturDate, idDataGroup, true );

         setFieldNoValidate( ifds::MaturDate, dstrEndDate, idDataGroup, false, true, true  );
      }
      else
      {
         setFieldReadOnly( ifds::StartDate, idDataGroup, true );
         setFieldReadOnly( ifds::EndDate, idDataGroup, true );
         setFieldReadOnly( ifds::MaturDate, idDataGroup, false );

         setMaturityDate( idDataGroup );
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());

}

//******************************************************************************
SEVERITY AsPensionPlan::setEndDate( const BFDataGroupId& idDataGroup )
{
   MAKEFRAME2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setEndDate" ) );
   SEVERITY  sevRtn = NO_CONDITION;  

   DString dstrStartDate, dstrOutDate;
   getField( ifds::StartDate, dstrStartDate, idDataGroup );

   /*
   business logic: first of the same month of the StartDate, 18 years from the StartDate 
     + ( day of the month of the StartDate - 1 )
   */
   addYearToDate( dstrStartDate, dstrOutDate, 18 );

   //compare day of dstrStartDate and day of dstrOutDate
   //if day of dstrStartDate and day of dstrOutDate is the same, subtract one day from dstrOutDate
   int nStartDay = DSTCommonFunctions::getDayFromUnFormattedDate( dstrStartDate );
   int nOutDay = DSTCommonFunctions::getDayFromUnFormattedDate( dstrOutDate );

   if( nStartDay == nOutDay )
   {
      DSTCommonFunctions::subtractDays ( dstrOutDate, dstrOutDate, 1 );
   }

   setFieldNoValidate( ifds::EndDate, dstrOutDate, idDataGroup, false, true, true  );

   return(GETCURRENTHIGHESTSEVERITY());

}

//********************************************************************************************
void AsPensionPlan::addYearToDate( DString& dstrInDate, DString& dstrOutDate, int numYear )
{
   //the first of the same month of the passed in date, n years from the passed in date +
   //( day of the month of the passed in date - 1 )

   int nYear = DSTCommonFunctions::getYearFromUnFormattedDate( dstrInDate );
   int nMonth = DSTCommonFunctions::getMonthFromUnFormattedDate( dstrInDate );
   int nDay = DSTCommonFunctions::getDayFromUnFormattedDate( dstrInDate );

   if( nDay == 1 )
      nMonth -= 1;

   if( nMonth == 0 )
   {
      nMonth = 12;
      nYear -= 1;
   }

   DString strBeginOfMonthnYearAfter;
   DSTCommonFunctions::getBeginOfMonthUnFormattedDate( nMonth, nYear + numYear, strBeginOfMonthnYearAfter );

   DSTCommonFunctions::subtractDays ( dstrInDate, dstrOutDate, 1 );

   nDay = DSTCommonFunctions::getDayFromUnFormattedDate( dstrOutDate );
   DSTCommonFunctions::addDays( strBeginOfMonthnYearAfter, dstrOutDate, nDay );

}

//********************************************************************************************
SEVERITY AsPensionPlan::doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );

   if( idField == ifds::EndDate )
   {
      validateEndDate( strValue, idDataGroup );
   }
   else if( idField == ifds::ASStatus )
   {
      validateStatus( strValue, idDataGroup );
   }
   else if( idField == ifds::MaturDate )
   {
      validateMaturityDate( strValue, idDataGroup );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//********************************************************************************************
SEVERITY AsPensionPlan::validateEndDate( const DString& EndDate, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateEndDate" ) );

   /*
   business rules:
   1. store dstrBirthDate = first of the month from shareholder's date of birth, 60 years from the year
      of shareholder's date of birth + (day of the month of shareholder's date of birth - 1)
   2. store dstrEndDate = first of the month from StartDate, 18 years from StartDate + (day of the month
      of StartDate - 1)
   3. if day of shareholder's date of birth = dstrBirthDate, dstrBirthDate - 1
   4. if day of StartDate = day of dstrEndDate, dstrEndDate - 1
   5. if input EndDate < dstrEndDate and input EndDate < dstrBirthDate, issue error 
   */

   DString dstrDofBirth, dstrBirthDate, dstrEndDate, dstrStartDate, dstrOutDate;
   getField( ifds::StartDate, dstrStartDate, idDataGroup );

   if( DSTCommonFunctions::CompareDates( EndDate, dstrStartDate ) == 
       DSTCommonFunctions::FIRST_EARLIER )
      ADDCONDITIONFROMFILE( CND::ERR_INVALID_EARLY_END_DATE );

   //Rule 2
   addYearToDate( dstrStartDate, dstrEndDate, 18 );

   //Rule 4
   int nStartDay = DSTCommonFunctions::getDayFromUnFormattedDate( dstrStartDate );
   int nEndDay = DSTCommonFunctions::getDayFromUnFormattedDate( dstrEndDate );

   if( nStartDay == nEndDay )
   {
      DSTCommonFunctions::subtractDays ( dstrEndDate, dstrOutDate, 1 );
      dstrEndDate = dstrOutDate;
   }

   //Rule 1
   getDofBirth( dstrDofBirth, idDataGroup );
   addYearToDate( dstrDofBirth, dstrBirthDate, 60 );

   //Rule 3
   int nDofBirthDay = DSTCommonFunctions::getDayFromUnFormattedDate( dstrDofBirth );
   int nBirthDay = DSTCommonFunctions::getDayFromUnFormattedDate( dstrBirthDate );

   if( nDofBirthDay == nBirthDay )
   {
      DSTCommonFunctions::subtractDays( dstrBirthDate, dstrOutDate, 1 );
      dstrBirthDate = dstrOutDate;
   }
   else
      dstrBirthDate = dstrEndDate; 

   //Rule 5
   if( DSTCommonFunctions::CompareDates( EndDate, dstrEndDate ) == 
       DSTCommonFunctions::FIRST_EARLIER &&
       DSTCommonFunctions::CompareDates( EndDate, dstrBirthDate ) == 
       DSTCommonFunctions::FIRST_EARLIER )
   {
      if( !( DSTCommonFunctions::CompareDates( dstrEndDate, dstrBirthDate ) == 
             DSTCommonFunctions::SECOND_EARLIER ) )
      {
         ADDCONDITIONFROMFILE( CND::ERR_INVALID_END_START_DATE );
      }
      else
      {
         ADDCONDITIONFROMFILE( CND::ERR_INVALID_END_BIRTH_DATE );
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());

}

//******************************************************************************
SEVERITY AsPensionPlan::getDofBirth( DString& dstrDofBirth, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getDofBirth" ) );

   DString dstrAcctNum;
   getParent()->getField(ifds::AccountNum, dstrAcctNum, idDataGroup, false);
   dstrAcctNum.strip().stripLeading( '0' );

   MFAccount *pMFAccount;

   if( getWorkSession().getMFAccount( idDataGroup, dstrAcctNum, pMFAccount ) <= WARNING )
   {
      pMFAccount->getDofBirthofOwnerSeq01( dstrDofBirth, idDataGroup );
   }

   return(GETCURRENTHIGHESTSEVERITY());

}

//********************************************************************************************
SEVERITY AsPensionPlan::setMaturityDate( const BFDataGroupId& idDataGroup )
{
   //Rule 1: if ASStatus = 01, get the next quarter end date depending on the month of current business date
   //Rule 2: if ASStatus = 02 or 03, get the month end date of current business date + 28 days
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setMaturityDate" ) );

   DString dstrASStatus, dstrEndDate, dstrDateOut;
   getField( ifds::ASStatus, dstrASStatus, idDataGroup );
   getField( ifds::EndDate, dstrEndDate, idDataGroup );

   //Rule 1
   if( dstrASStatus == EARLY_MATURITY )
   {
      getNextQuarterEndDate( currBusinessDate_, dstrDateOut );
      setFieldNoValidate( ifds::MaturDate, dstrDateOut, idDataGroup, false, true, true  );
   }
   //Rule 2
   else
   {
      if( dstrASStatus == INCAPACITATED || dstrASStatus == UNEMPLOYEC )
      {
         DSTCommonFunctions::addDays( currBusinessDate_, dstrDateOut, 28 );

         getMonthEndDate( dstrDateOut, dstrDateOut );
         setFieldNoValidate( ifds::MaturDate, dstrDateOut, idDataGroup, false, true, true  ); 
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());

}

//******************************************************************************
SEVERITY AsPensionPlan::validateStatus( const DString& dstrASStatus, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateStatus" ) );

   if( dstrASStatus != NULL_STRING )
   {
      if( !( dstrASStatus == EARLY_MATURITY || dstrASStatus == INCAPACITATED || dstrASStatus == UNEMPLOYEC ) )
      {
         ADDCONDITIONFROMFILE( CND::ERR_EARLY_TERMINATION );
      }
   }

   return(GETCURRENTHIGHESTSEVERITY());

}

//******************************************************************************
//Depending on the month of the passed in date, get a later quarter end date
void AsPensionPlan::getNextQuarterEndDate( DString &dstrDateIn, DString &dstrDateOut )
{
   DString dstrYear;

   int nYear = DSTCommonFunctions::getYearFromUnFormattedDate( dstrDateIn );
   int nMonth = DSTCommonFunctions::getMonthFromUnFormattedDate( dstrDateIn );

   if( nMonth > 9 && nMonth <= 12 )
      ++nYear;

   convertIntToString( nYear, dstrYear );

   DString dstrConfiguration( I_( "HostMasks" ) );
   DString dstrKey( I_("D") );
   dstrDateOut = GetConfigValueAsString( I_( "LocaleFormats" ), dstrConfiguration, dstrKey );

   if( nMonth <= 3 )
   {
      dstrDateOut.replace(dstrDateOut.find( I_("yyyy")), 4, dstrYear );
      dstrDateOut.replace(dstrDateOut.find( I_("MM")), 2, I_( "06" ) );
      dstrDateOut.replace(dstrDateOut.find( I_("dd")), 2, I_( "30" ) );
   }
   else if( nMonth <= 6 )
   {
      dstrDateOut.replace(dstrDateOut.find( I_("yyyy")), 4, dstrYear );
      dstrDateOut.replace(dstrDateOut.find( I_("MM")), 2, I_( "09" ) );
      dstrDateOut.replace(dstrDateOut.find( I_("dd")), 2, I_( "30" ) );
   }
   else if( nMonth <= 9 )
   {
      dstrDateOut.replace(dstrDateOut.find( I_("yyyy")), 4, dstrYear );
      dstrDateOut.replace(dstrDateOut.find( I_("MM")), 2, I_( "12" ) );
      dstrDateOut.replace(dstrDateOut.find( I_("dd")), 2, I_( "31" ) );
   }
   else
   {
      assert( nMonth <= 12 );
      dstrDateOut.replace(dstrDateOut.find( I_("yyyy")), 4, dstrYear );
      dstrDateOut.replace(dstrDateOut.find( I_("MM")), 2, I_( "03" ) );
      dstrDateOut.replace(dstrDateOut.find( I_("dd")), 2, I_( "31" ) );
   }
}

//******************************************************************************
void AsPensionPlan::getMonthEndDate( DString &dstrDateIn, DString &dstrDateOut )
{
   int nMonth = DSTCommonFunctions::getMonthFromUnFormattedDate( dstrDateIn );
   int nYear = DSTCommonFunctions::getYearFromUnFormattedDate( dstrDateIn );

   DSTCommonFunctions::getEndOfMonthUnFormattedDate( nMonth, nYear, dstrDateOut );
}

//********************************************************************************************
SEVERITY AsPensionPlan::validateMaturityDate( const DString& MaturityDate, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "alidateMaturityDate" ) );

   DString dstrEndDate, dstrDateOut, dstrASStatus;
   getField( ifds::EndDate, dstrEndDate, idDataGroup );
   getField( ifds::ASStatus, dstrASStatus, idDataGroup );

   /*
   Case 1: if input MaturityDate < EndDate and ASStatus = 02 or 03:
     Rule 1: if input MaturityDate < (month end date of current business date + 28 days), issue error
     Rule 2: if input MaturityDate <> (month end date of input MaturityDate), issue error
   
   Case 2: if input MaturityDate < EndDate and ASStatus = 01, get next quarter end date according to month 
         of current business date:
     Rule 3: if input MaturityDate < quarter end date, issue error
     Rule 4: if input MaturityDate <> MaturityDate, get quarter end date according to month of input MaturityDate
           if day or month of input MaturityDate <> day or month of quarter end date, issue error
   
   Rule 5: if input MaturityDate = EndDate, assign MaturityDate = input MaturityDate

   Rule 6: if input MaturityDate > EndDate, issue error
   */

   if( DSTCommonFunctions::CompareDates( MaturityDate, dstrEndDate ) == 
       DSTCommonFunctions::FIRST_EARLIER )
   {
      if( dstrASStatus == INCAPACITATED || dstrASStatus == UNEMPLOYEC )
      {
         //Rule 1
         DSTCommonFunctions::addDays( currBusinessDate_, dstrDateOut, 28 );
         getMonthEndDate( dstrDateOut, dstrDateOut );

         if( DSTCommonFunctions::CompareDates( MaturityDate, dstrDateOut ) == 
             DSTCommonFunctions::FIRST_EARLIER )
         {
            ADDCONDITIONFROMFILE( CND::ERR_LATER_MONTHEND_MATURITY_DATE );
         } //MaturityDate < dstrDateOut
         else
         {
            //Rule 2
            DString dstrMatureDate = MaturityDate;
            getMonthEndDate( dstrMatureDate, dstrDateOut );

            if( DSTCommonFunctions::CompareDates( dstrMatureDate, dstrDateOut ) != DSTCommonFunctions::EQUAL )
            {
               ADDCONDITIONFROMFILE( CND::ERR_MONTHEND_MATURITY_DATE );
            }

         } //else for MaturityDate < dstrDateOut
      }    // dstrASStatus == INCAPACITATED || UNEMPLOYEC
      else if( dstrASStatus == EARLY_MATURITY )
      {
         //Rule 3
         getNextQuarterEndDate( currBusinessDate_, dstrDateOut );

         if( DSTCommonFunctions::CompareDates( MaturityDate, dstrDateOut ) == 
             DSTCommonFunctions::FIRST_EARLIER )
         {
            ADDCONDITIONFROMFILE( CND::ERR_LATER_QUARTEREND_MATURITY_DATE );
         } //if MaturityDate < dstrDateOut
         else
         {
            if( dstrMaturDate_ != MaturityDate )
            {
               //Rule 4
               DString dstrMatureDate = MaturityDate;
               getQuarterEndDate( dstrMatureDate, dstrDateOut );

               int nQuarterMonth = DSTCommonFunctions::getMonthFromUnFormattedDate( dstrDateOut );
               int nQuarterDay = DSTCommonFunctions::getDayFromUnFormattedDate( dstrDateOut );
               int nMatureMonth = DSTCommonFunctions::getMonthFromUnFormattedDate( MaturityDate );
               int nMatureDay = DSTCommonFunctions::getDayFromUnFormattedDate( MaturityDate );

               if( nMatureDay != nQuarterDay  || nMatureMonth != nQuarterMonth )
               {
                  ADDCONDITIONFROMFILE( CND::ERR_QUARTEREND_MATURITY_DATE );
               }
            }
            else
               setFieldNoValidate( ifds::MaturDate, MaturityDate, idDataGroup, false, true, true  );
         }
      }    //dstrASStatus == EARLY_MATURITY
      else
      {
         ADDCONDITIONFROMFILE( CND::ERR_ENDDATE_MATURITY_DATE );
      }
   }  //if MaturityDate < dstrEndDate
   else
   {
      //Rule 5
      if( DSTCommonFunctions::CompareDates( MaturityDate, dstrEndDate ) == DSTCommonFunctions::EQUAL )
      {
         setFieldNoValidate( ifds::MaturDate, MaturityDate, idDataGroup, false, true, true  );    
      }
      else
      {
         //Rule 6
         DString idiStr;
         getField( ifds::EndDate, dstrEndDate, idDataGroup,true );

         addIDITagValue( idiStr, I_( "Date" ),  dstrEndDate );
         ADDCONDITIONFROMFILEIDI( CND::ERR_LATER_ENDDATE_MATURITY_DATE, idiStr );

         // ADDCONDITIONFROMFILE( CND::ERR_LATER_ENDDATE_MATURITY_DATE );
      }

   }  //else if MaturityDate < dstrEndDate

   return(GETCURRENTHIGHESTSEVERITY());

}

//******************************************************************************
//Depending on the month of the passed in date, get a quarter end date
void AsPensionPlan::getQuarterEndDate( DString &dstrDateIn, DString &dstrDateOut )
{
   DString dstrYear;

   int nYear = DSTCommonFunctions::getYearFromUnFormattedDate( dstrDateIn );
   int nMonth = DSTCommonFunctions::getMonthFromUnFormattedDate( dstrDateIn );

   convertIntToString( nYear, dstrYear );

   DString dstrConfiguration( I_( "HostMasks" ) );
   DString dstrKey( I_("D") );
   dstrDateOut = GetConfigValueAsString( I_( "LocaleFormats" ), dstrConfiguration, dstrKey );

   if( nMonth <= 3 )
   {
      dstrDateOut.replace(dstrDateOut.find( I_("yyyy")), 4, dstrYear );
      dstrDateOut.replace(dstrDateOut.find( I_("MM")), 2, I_( "03" ) );
      dstrDateOut.replace(dstrDateOut.find( I_("dd")), 2, I_( "31" ) );
   }
   else if( nMonth > 3 && nMonth <= 6 )
   {
      dstrDateOut.replace(dstrDateOut.find( I_("yyyy")), 4, dstrYear );
      dstrDateOut.replace(dstrDateOut.find( I_("MM")), 2, I_( "06" ) );
      dstrDateOut.replace(dstrDateOut.find( I_("dd")), 2, I_( "30" ) );
   }
   else if( nMonth > 6 && nMonth <= 9 )
   {
      dstrDateOut.replace(dstrDateOut.find( I_("yyyy")), 4, dstrYear );
      dstrDateOut.replace(dstrDateOut.find( I_("MM")), 2, I_( "09" ) );
      dstrDateOut.replace(dstrDateOut.find( I_("dd")), 2, I_( "30" ) );
   }
   else if( nMonth > 9 && nMonth <= 12 )
   {
      dstrDateOut.replace(dstrDateOut.find( I_("yyyy")), 4, dstrYear );
      dstrDateOut.replace(dstrDateOut.find( I_("MM")), 2, I_( "12" ) );
      dstrDateOut.replace(dstrDateOut.find( I_("dd")), 2, I_( "31" ) );
   }
}

//***************************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AsPensionPlan.cpp-arc  $
// 
//    Rev 1.14   Nov 14 2004 14:26:06   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.13   Mar 21 2003 17:59:22   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.12   Oct 09 2002 23:54:00   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.11   Aug 29 2002 12:55:02   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.10   Jul 05 2002 10:31:36   PURDYECH
// Include file fixup
// 
//    Rev 1.9   05 Jun 2002 14:05:26   SMITHDAV
// Change occurances of
// DSTCommonFunctions::DATE_ORDER::EQUAL
// to DSTCommonFunctions::EQUAL.
// 
//    Rev 1.8   22 May 2002 18:26:24   PURDYECH
// BFData Implementation
// 
//    Rev 1.7   Jan 07 2002 16:06:58   JANKAREN
// fixed date problem when date is Jan 01
// 
//    Rev 1.6   Jan 07 2002 14:15:38   JANKAREN
// fixed error message when user change the AS Status
// 
//    Rev 1.5   07 Jan 2002 11:08:14   KOVACSRO
// When retrieving data from backend, idDataGroup should be the HOST (actually there is no need for lDatGroupId param. in this kind of init)
// 
//    Rev 1.4   Jan 07 2002 10:41:42   JANKAREN
// fixed date problem when the date is the beginning of the month
// 
//    Rev 1.3   Dec 27 2001 10:48:44   YINGBAOL
// 1. promot data not found error.
// 2. As Status should be readonly and empty if creat a new one;
// 3. Change error message. 
// 
//    Rev 1.2   Nov 29 2001 14:35:54   JANKAREN
// code clean up
// 
//    Rev 1.1   Sep 27 2001 09:24:42   JANKAREN
// Added business logic
// 
//    Rev 1.0   Aug 23 2001 12:57:26   JANKAREN
// Initial revision.
 * 
 * 
 */

