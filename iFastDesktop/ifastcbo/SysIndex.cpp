//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Canada, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2001 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : SysIndex.cpp
// ^AUTHOR : Mihai Virgil Buzila
// ^DATE   : 5/1/01
//
// ^CLASS    : SysIndex
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include <ifastdataimpl\dse_dstc0119_req.hpp>
#include <ifastdataimpl\dse_dstc0119_vw.hpp>
#include "dstcommonfunction.hpp"
#include "mgmtco.hpp"
#include "mgmtcooptions.hpp"
#include "savingplanmaster.hpp"
#include "savingplanmasterlist.hpp"
#include "sysindex.hpp"
#include "sysindexlist.hpp"
#include "systematic.hpp"

namespace
{
   //Trace literals
   const I_CHAR * const CLASSNAME            = I_( "SysIndex" );
   const I_CHAR * const YES                  = I_( "Y" );
   const I_CHAR * const AMOUNT_TYPE_AMOUNT   = I_( "D" );
   const I_CHAR * const AMOUNT_TYPE_PERCENT  = I_( "P" );
   const I_CHAR * const SAVING_PLAN          = I_( "V" );
   const I_CHAR * const BAD                  = I_( "N" );
}

namespace ifds
{
   extern CLASS_IMPORT const BFDateFieldId EffectiveDate;
   extern CLASS_IMPORT const BFDateFieldId StopDate;
   extern CLASS_IMPORT const BFDateFieldId LastProcessDate;
   extern CLASS_IMPORT const BFTextFieldId January;
   extern CLASS_IMPORT const BFTextFieldId February;
   extern CLASS_IMPORT const BFTextFieldId March;
   extern CLASS_IMPORT const BFTextFieldId April;
   extern CLASS_IMPORT const BFTextFieldId May;
   extern CLASS_IMPORT const BFTextFieldId June;
   extern CLASS_IMPORT const BFTextFieldId July;
   extern CLASS_IMPORT const BFTextFieldId August;
   extern CLASS_IMPORT const BFTextFieldId September;
   extern CLASS_IMPORT const BFTextFieldId October;
   extern CLASS_IMPORT const BFTextFieldId November;
   extern CLASS_IMPORT const BFTextFieldId December;
   extern CLASS_IMPORT const BFTextFieldId SystematicCrossField1;
   extern CLASS_IMPORT const BFTextFieldId SystematicCrossField2;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFTextFieldId StatusCode;
   extern CLASS_IMPORT const BFTextFieldId PlanCode;
   extern CLASS_IMPORT const BFTextFieldId PACCalendar;
}

namespace CND
{  // Conditions used
   extern const long ERR_INVALID_PERCENT;   
   extern const long ERR_AMOUNT_MUST_BE_GREATER_THAN_ZERO;   
   extern const long ERR_START_DATE_LATE_THAN_STOP_DATE;   
   extern const long ERR_INDEX_FRQ_BEYOND_END_DATE;   
   extern const long ERR_INDEX_FRQ_LESS_THAN_PAC_SWP_FRQ;   
   extern const long ERR_START_DATE_BEFORE_EFFECTIVE_DATE;
   extern const long ERR_INDEX_DATE_LATER_THAN_END_DATE;
   extern const long ERR_END_DATE_LESS_THAN_STOP_DATE_OF_PACSWP;
   extern const long ERR_START_DATE_BEFORE_LAST_PROCESS_DATE;
   extern const long ERR_AMOUNT_TYPE_IS_MANDATORY;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//  Field DD Id,            State Flags,             Group Flags 
   { ifds::IndexAmt,              BFCBO::NONE,                 0 }, 
   { ifds::IndexType,             BFCBO::NONE,                 0 }, 
   { ifds::StartDate,             BFCBO::IMMEDIATE_VALIDATION, 0 }, 
   { ifds::EndDate,               BFCBO::IMMEDIATE_VALIDATION, 0 }, 
   { ifds::NextIndexDate,         BFCBO::NONE,                 0 }, 
   { ifds::SystematicCrossField1, BFCBO::IMMEDIATE_VALIDATION, 0 }, 
   { ifds::SystematicCrossField2, BFCBO::IMMEDIATE_VALIDATION, 0 }, 
   { ifds::IndexFrequency,        BFCBO::IMMEDIATE_VALIDATION, 0 }, 
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//******************************************************************************

SysIndex::SysIndex( BFAbstractCBO &parent ) :
MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME , NULL_STRING );
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo,0,NULL);
   addCrossEdit ( ifds::SystematicCrossField1, ifds::IndexAmt );
   addCrossEdit ( ifds::SystematicCrossField1, ifds::IndexType );
   addCrossEdit ( ifds::SystematicCrossField2, ifds::StartDate );
   addCrossEdit ( ifds::SystematicCrossField2, ifds::EndDate );
}

//******************************************************************************
SysIndex::~SysIndex()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}     

//******************************************************************************
SEVERITY SysIndex::init( const BFData& data, bool bBaseDelete )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   bool bReadOnly = true;;

   attachDataObject(const_cast<BFData&>(data), bBaseDelete, true );  //true
   DString dstrEndDate, dstrLastProcessDate, dstrStartDate, dstrStatusCode;

//   getWorkSession().getMgmtCoOptions()->getField( DBR::CurrBusDate, dstrCurBusDate, BF::HOST, false );
   Systematic *pSystematic = dynamic_cast <Systematic *> ( getParent()->getParent() );
   pSystematic->getField ( ifds::LastProcessDate, dstrLastProcessDate, BF::HOST );
   pSystematic->getField ( ifds::StatusCode, dstrStatusCode, BF::HOST );

   getField ( ifds::EndDate, dstrEndDate, BF::HOST );
   getField ( ifds::StartDate, dstrStartDate, BF::HOST );

   if( dstrStatusCode == BAD )
   {
      bReadOnly = false;
      setFieldReadOnly ( ifds::IndexAmt, BF::HOST, bReadOnly );
      setFieldReadOnly ( ifds::IndexType, BF::HOST, bReadOnly );   
      setFieldReadOnly ( ifds::EndDate, BF::HOST, bReadOnly );
   }
   else if( dstrLastProcessDate == NULL_STRING || DSTCommonFunctions::CompareDates( dstrLastProcessDate, dstrStartDate ) == DSTCommonFunctions::FIRST_EARLIER )
   {
      bReadOnly = false;
   }

   setFieldReadOnly ( ifds::IndexFrequency, BF::HOST, bReadOnly );
   setFieldReadOnly ( ifds::StartDate, BF::HOST, bReadOnly );   

   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
void SysIndex::doInitWithDefaultValues( const BFDataGroupId& idDataGroup )
{
   //Make a view call to get Default Values.
   DString dstrDefaultIndexAmt, dstrDefaultIndexType, dstrDefaultIndexFreq, dstrDefaultStartDate, dstrDefaultEndDate,
   dstrNextIndexDate, dstrTransType;

   SysIndexList *pSysIndexList = dynamic_cast <SysIndexList *> (getParent());
   Systematic *pSystematic = dynamic_cast <Systematic *> ( getParent()->getParent() );
   pSystematic->getField ( ifds::TransType, dstrTransType, idDataGroup );

//   pSysIndexList->getField ( DBR::DefaultStartDate, dstrDefaultStartDate, idDataGroup );

   //If the Default Start Date is NULL then we will use the Current Bussiness Day.

//   if ( dstrDefaultStartDate == NULL_STRING )
//   {
   DString dstrTemp;
   int iCurYear;
   int year_pos = DSTCommonFunctions::getYearPosition();
   int day_pos  = DSTCommonFunctions::getDayPosition();
   int month_pos = DSTCommonFunctions::getMonthPosition();

   pSystematic->getField ( ifds::EffectiveDate, dstrDefaultStartDate, idDataGroup );
   dstrTemp.assign( dstrDefaultStartDate, year_pos, 4 );
   iCurYear = static_cast<int>( DSTCommonFunctions::convertToDouble ( dstrTemp ) );
   ++iCurYear;
   convertIntToString ( iCurYear, dstrTemp );
   dstrDefaultStartDate.replace(year_pos, 4, dstrTemp );
   DString dstrPACCalendar;
   getWorkSession().getOption ( ifds::PACCalendar, dstrPACCalendar, idDataGroup, false );
   if( dstrPACCalendar == YES )
   {
      dstrDefaultStartDate.replace(month_pos, 2, I_("01") );
      dstrDefaultStartDate.replace(day_pos, 2, I_("01") );
   }
   //getWorkSession().getMgmtCoOptions()->getField( DBR::CurrBusDate, dstrDefaultStartDate, idDataGroup, false );
//   }

   setFieldNoValidate( ifds::StartDate, dstrDefaultStartDate, idDataGroup, false, false, true, false );
   setValidFlag ( ifds::StartDate, idDataGroup, false );

   pSysIndexList->getField ( ifds::DefaultEndDate, dstrDefaultEndDate, idDataGroup );
   if( NULL_STRING == dstrDefaultEndDate.strip() )
      DSTCommonFunctions::getFormat12319999Date(dstrDefaultEndDate);

   setFieldNoValidate( ifds::EndDate, dstrDefaultEndDate, idDataGroup, false, true, true, false );
   setValidFlag ( ifds::EndDate, idDataGroup, false );

   dstrDefaultIndexFreq = NULL_STRING; 
   if( dstrTransType == SAVING_PLAN )
   {
      DString dstrPlanCode;
      SavingPlanMasterList *pSavingPlanMasterList;
      getMgmtCo().getSavingPlanMasterList( pSavingPlanMasterList );
      pSystematic->getField(ifds::PlanCode, dstrPlanCode, idDataGroup, false);
      BFObjIter bfIter( *pSavingPlanMasterList, idDataGroup, false, BFObjIter::ITERTYPE::NON_DELETED );
      bfIter.positionByKey( dstrPlanCode );
      if( !bfIter.end() )
      {
         SavingPlanMaster *pSavingPlanMaster = dynamic_cast <SavingPlanMaster*> (bfIter.getObject());
         if( pSavingPlanMaster )
         {
            pSavingPlanMaster->getField ( ifds::IndexAmt, dstrDefaultIndexAmt, idDataGroup );
            setFieldNoValidate( ifds::IndexAmt, dstrDefaultIndexAmt, idDataGroup, false, true, true, false );
            pSavingPlanMaster->getField ( ifds::IndexType, dstrDefaultIndexType, idDataGroup );
            if( NULL_STRING == dstrDefaultIndexType )
               setFieldNoValidate( ifds::IndexType, AMOUNT_TYPE_AMOUNT, idDataGroup, false, true, true, false );
            else
               setFieldNoValidate( ifds::IndexType, dstrDefaultIndexType, idDataGroup, false, true, true, false );

            pSavingPlanMaster->getField ( ifds::IndexFrequency, dstrDefaultIndexFreq, idDataGroup );
            setFieldNoValidate( ifds::IndexFrequency, dstrDefaultIndexFreq, idDataGroup, false, true, true, false );
         }
      }
   }
   else
   {
      pSysIndexList->getField ( ifds::DefaultIndexAmt, dstrDefaultIndexAmt, idDataGroup );
      setField( ifds::IndexAmt, dstrDefaultIndexAmt, idDataGroup );

      pSysIndexList->getField ( ifds::DefaultIndexType, dstrDefaultIndexType, idDataGroup );
      if( NULL_STRING == dstrDefaultIndexType )
         setFieldNoValidate( ifds::IndexType, AMOUNT_TYPE_AMOUNT, idDataGroup, false, true, true, false );
      else
         setFieldNoValidate( ifds::IndexType, dstrDefaultIndexType, idDataGroup, false, true, true, false );

      pSysIndexList->getField ( ifds::DefaultIndexFreq, dstrDefaultIndexFreq, idDataGroup );
      setFieldNoValidate( ifds::IndexFrequency, dstrDefaultIndexFreq, idDataGroup, false, true, true, false );
   }  

   if( dstrDefaultIndexFreq == NULL_STRING )
   {
      defaultFrequency ( idDataGroup, dstrDefaultIndexFreq );      
      setFieldNoValidate( ifds::IndexFrequency, dstrDefaultIndexFreq, idDataGroup, false, true, true, false );
   }
   dstrNextIndexDate = getNextIndexDate ( idDataGroup );
   setFieldNoValidate( ifds::NextIndexDate, dstrNextIndexDate, idDataGroup, false, true, true, false );

   if( isNew() )
      setNonDummyFlag();

   if( pSystematic->isNew () )
      setNonDummyFlag();
}

//******************************************************************************
SEVERITY SysIndex::doApplyRelatedChanges( const BFFieldId& idField, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doApplyRelatedChanges") );

   // Recalculate the Next Index Date when the Effective/Start Date changes.

   if( !isNew() )
   {
      if( idField == ifds::EndDate )
      {
         DString dstrEndDate, dstrCurBusDate;
         getWorkSession().getMgmtCoOptions()->getField( ifds::CurrBusDate, dstrCurBusDate, idDataGroup, false );
         getField ( ifds::EndDate, dstrEndDate, idDataGroup );
      }
   }
   else
   {
      if( idField == ifds::StartDate )
      {
         DString dstrNextIndexDate;
         dstrNextIndexDate = getNextIndexDate ( idDataGroup );
         setFieldNoValidate( ifds::NextIndexDate, dstrNextIndexDate, idDataGroup, false, true, true, false );
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY SysIndex::doValidateField( const BFFieldId& idField, const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("doValidateField") );

   if( idField == ifds::SystematicCrossField1 )
   {
      DString dstrIndexType, dstrIndexAmt;
      double dAmount;
      getField ( ifds::IndexAmt, dstrIndexAmt, idDataGroup );
      getField ( ifds::IndexType, dstrIndexType, idDataGroup );
      dAmount = DSTCommonFunctions::convertToDouble( dstrIndexAmt );
      if( dstrIndexType == AMOUNT_TYPE_PERCENT )
      {
         if( ( dAmount <= 0 ) || ( dAmount > 100 ) )
         {
            ADDCONDITIONFROMFILE( CND::ERR_INVALID_PERCENT );
         }

      }
      else if( dstrIndexType == AMOUNT_TYPE_AMOUNT )
      {
         if( dAmount <= 0 )
         {
            ADDCONDITIONFROMFILE( CND::ERR_AMOUNT_MUST_BE_GREATER_THAN_ZERO );
         }
      }
   }
   else if( idField == ifds::SystematicCrossField2 )
   {
      validateDateRange( idDataGroup );      
      setValidFlag( ifds::IndexFrequency, idDataGroup, false) ;   // to force validation
   }
   else if( idField == ifds::IndexFrequency )
   {
      validateFrequency( strValue, idDataGroup );
   }
   else if( idField == ifds::IndexType )
   {
      if( strValue == NULL_STRING )
      {
         ADDCONDITIONFROMFILE ( CND::ERR_AMOUNT_TYPE_IS_MANDATORY );
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

DString SysIndex::getNextIndexDate( const BFDataGroupId& idDataGroup )
{
   DString dstrEffectiveDate, dstrStartDate, dstrTemp;
   // Break the Starting index date into month, day, year
   getField ( ifds::StartDate, dstrStartDate, idDataGroup );
   //Get Effective Date from Systematic CBO
   Systematic *pSystematic = dynamic_cast <Systematic *> (getParent()->getParent());
   pSystematic->getField ( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup );

   if( dstrStartDate == NULL_STRING || dstrEffectiveDate == NULL_STRING ) return(NULL_STRING);

   int iCurDay, iCurMonth, iCurYear;

   int day_pos = DSTCommonFunctions::getDayPosition();
   int month_pos = DSTCommonFunctions::getMonthPosition();
   int year_pos = DSTCommonFunctions::getYearPosition();  

   dstrTemp.assign( dstrStartDate, day_pos, 2 );
   iCurDay = static_cast<int>( DSTCommonFunctions::convertToDouble ( dstrTemp ) );
   dstrTemp.assign( dstrStartDate, month_pos, 2 );
   iCurMonth = static_cast<int>( DSTCommonFunctions::convertToDouble ( dstrTemp ) );
   dstrTemp.assign( dstrStartDate, year_pos, 4 );
   iCurYear = static_cast<int>(DSTCommonFunctions::convertToDouble ( dstrTemp ));


   const BFFieldId allMonths[12] = { ifds::January, ifds::February, ifds::March, ifds::April,
      ifds::May, ifds::June, ifds::July, ifds::August, ifds::September, ifds::October,
      ifds::November, ifds::December};

   const DString Months[12] = { I_( "01" ), I_( "02" ), I_( "03" ),I_( "04" ),I_( "05" ),
      I_( "06" ),I_( "07" ),I_( "08" ),I_( "09" ),I_( "10" ),I_( "11" ),I_( "12" )};

   DString dstrFrequency, dstrCurBusDate, dstrNextIndexDate;
   getWorkSession().getDateInHostFormat(dstrCurBusDate, DSTCWorkSession::DATE_TYPE::CURRENT_BUSINESS_DAY, idDataGroup);

   int tempDay;
   getWorkSession().getDateInHostFormat(dstrNextIndexDate, DSTCWorkSession::DATE_TYPE::CURRENT_BUSINESS_DAY, idDataGroup);                  
   DString dstrPACCalendar;
   getWorkSession().getOption ( ifds::PACCalendar, dstrPACCalendar, idDataGroup, false );
   for( int i=0; i<12; ++i )
   {
      pSystematic->getField ( allMonths[iCurMonth-1], dstrFrequency, idDataGroup );
      if( dstrFrequency == YES )
      {
         dstrNextIndexDate.replace(month_pos, 2, Months[iCurMonth-1]);   
         convertIntToString ( iCurYear, dstrTemp );
         dstrNextIndexDate.replace(year_pos, 4, dstrTemp );
         dstrNextIndexDate.replace(day_pos, 2, I_( "01" ) );
         //If PAC Calendar year is yes, we will always use 01 as the day.
         if( dstrPACCalendar != YES )
         {
            tempDay = iCurDay - 1;
            DSTCommonFunctions::addDays ( dstrNextIndexDate, dstrNextIndexDate, tempDay );
            tempDay = static_cast<int>(DSTCommonFunctions::convertToDouble ( dstrTemp.assign( dstrNextIndexDate, day_pos, 2 ) ) );
            if( tempDay != iCurDay )
               DSTCommonFunctions::subtractDays ( dstrNextIndexDate, dstrNextIndexDate, tempDay );
         }
         if( DSTCommonFunctions::CompareDates( dstrNextIndexDate, dstrCurBusDate ) == DSTCommonFunctions::FIRST_EARLIER )
         {
            i=0;      
         }
         else
         {
            break;
         }
      }
      ++iCurMonth;
      if( iCurMonth > 12 )
      {
         iCurMonth = 1;
         ++iCurYear;
      }
   }
   return(dstrNextIndexDate);
}

//******************************************************************************

SEVERITY SysIndex::validateDateRange( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateStartDate") );

   DString dstrStartDate, dstrEndDate, dstrEffectiveDate, dstrLastProcessDate, dstrStopDate;
   getField ( ifds::StartDate, dstrStartDate, idDataGroup );
   getField ( ifds::EndDate, dstrEndDate, idDataGroup );

   // Get Systematic CBO
   getParent()->getParent()->getField ( ifds::EffectiveDate, dstrEffectiveDate, idDataGroup );
   getParent()->getParent()->getField ( ifds::LastProcessDate, dstrLastProcessDate, idDataGroup );
   getParent()->getParent()->getField ( ifds::StopDate, dstrStopDate, idDataGroup );

   if( DSTCommonFunctions::CompareDates( dstrStartDate, dstrEndDate ) == DSTCommonFunctions::SECOND_EARLIER )
   {
      ADDCONDITIONFROMFILE( CND::ERR_START_DATE_LATE_THAN_STOP_DATE );
   }
   else if( DSTCommonFunctions::CompareDates( dstrStartDate, dstrEffectiveDate ) == DSTCommonFunctions::FIRST_EARLIER )
   {
      ADDCONDITIONFROMFILE( CND::ERR_START_DATE_BEFORE_EFFECTIVE_DATE );
   }
   else if( dstrLastProcessDate != NULL_STRING && DSTCommonFunctions::CompareDates( dstrStartDate, dstrLastProcessDate ) == DSTCommonFunctions::FIRST_EARLIER )
   {
      ADDCONDITIONFROMFILE( CND::ERR_START_DATE_BEFORE_LAST_PROCESS_DATE );
   }
   else if( DSTCommonFunctions::CompareDates( dstrEndDate, dstrStopDate ) == DSTCommonFunctions::SECOND_EARLIER )
   {
      ADDCONDITIONFROMFILE( CND::ERR_END_DATE_LESS_THAN_STOP_DATE_OF_PACSWP );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY SysIndex::validateIndexDate( const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateStartDate") );

   DString dstrEndDate, dstrNextIndexDate, dstrEffectiveDate;
   getField ( ifds::EndDate, dstrEndDate, idDataGroup );
   getField ( ifds::NextIndexDate, dstrNextIndexDate, idDataGroup );

   if( DSTCommonFunctions::CompareDates( dstrEndDate, dstrNextIndexDate ) == DSTCommonFunctions::FIRST_EARLIER )
   {
      ADDCONDITIONFROMFILE( CND::ERR_INDEX_DATE_LATER_THAN_END_DATE );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY SysIndex::validateFrequency( const DString& dstrIndexFreq, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("validateFrequency") );
   DString dstrStartDate, dstrEndDate;
   double  months=0;
   int indexFreq;
   getField ( ifds::StartDate, dstrStartDate, idDataGroup );
   getField ( ifds::EndDate, dstrEndDate, idDataGroup );
   indexFreq = static_cast<int>( DSTCommonFunctions::convertToDouble ( dstrIndexFreq ) );
   DSTCommonFunctions::addMonths ( dstrStartDate, dstrEndDate, months);
   int numSysFreq;
   defaultFrequency ( idDataGroup, numSysFreq );   
   if( indexFreq > months )
   {
      ADDCONDITIONFROMFILE( CND::ERR_INDEX_FRQ_BEYOND_END_DATE );
   }
   else if( indexFreq < numSysFreq )
   {
      ADDCONDITIONFROMFILE( CND::ERR_INDEX_FRQ_LESS_THAN_PAC_SWP_FRQ );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

void SysIndex::defaultFrequency( const BFDataGroupId& idDataGroup, DString& dstrFreq )
{
   int iFreq;
   defaultFrequency ( idDataGroup, iFreq );
   convertIntToString ( 12/iFreq , dstrFreq );
}

//******************************************************************************

void SysIndex::defaultFrequency( const BFDataGroupId& idDataGroup, int& iFreq )
{
   int count = numSysFrequency ( idDataGroup );
   if( ( count != 5 ) && (( count < 7 ) || ( count > 9 ) ) )
      iFreq = 1;
   else
      iFreq = 12/count;   
}

//******************************************************************************

int SysIndex::numSysFrequency ( const BFDataGroupId& idDataGroup )
{
   const BFFieldId allMonths[12] = { ifds::January, ifds::February, ifds::March, ifds::April,
      ifds::May, ifds::June, ifds::July, ifds::August, ifds::September, ifds::October,
      ifds::November, ifds::December};

   Systematic *pSystematic = dynamic_cast <Systematic *>(getParent()->getParent());
   DString dstrTemp;
   int count = 0;
   for( int i = 0; i < 12; i++ )
   {
      pSystematic->getField ( allMonths[i], dstrTemp, idDataGroup );
      if( dstrTemp == YES )
         ++count;
   }   
   return(count);
}

//******************************************************************************

void SysIndex::markReadOnly ( const BFDataGroupId& idDataGroup )
{
   setFieldReadOnly ( ifds::IndexAmt, idDataGroup, true );
   setFieldReadOnly ( ifds::IndexType, idDataGroup, true );   
   setFieldReadOnly ( ifds::StartDate, idDataGroup, true );   
   setFieldReadOnly ( ifds::EndDate, idDataGroup, true );
   setFieldReadOnly ( ifds::IndexFrequency, idDataGroup, true );   
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/SysIndex.cpp-arc  $
// 
//    Rev 1.33   Nov 14 2004 14:56:24   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.32   Mar 21 2003 18:25:36   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.31   Oct 09 2002 23:55:04   PURDYECH
// PVCS Database Conversion
// 
//    Rev 1.30   Sep 27 2002 11:42:34   PURDYECH
// Code cleanup
// 
//    Rev 1.29   Aug 29 2002 12:56:44   SMITHDAV
// ClientLocale and typed field changes.
// 
//    Rev 1.28   22 May 2002 18:29:56   PURDYECH
// BFData Implementation
// 
//    Rev 1.27   Jan 10 2002 15:05:16   ZHANGCEL
// fix the bug regarding new record adding problem
// 
//    Rev 1.26   10 Nov 2001 16:50:00   WINNIE
// Fix SSB bug : index frequency did not pick up default value in saving plan master and generic control
// 
//    Rev 1.25   24 Oct 2001 15:43:34   HSUCHIN
// changed defaultstartdate to be based on Systematic's effective date and bug fix for index type not defaulting properly when systematic is a savings plan.
// 
//    Rev 1.24   14 Oct 2001 15:22:48   HSUCHIN
// fix default date bug.  Now checks PAC Calendar flag in System options to determine default start date
// 
//    Rev 1.23   12 Sep 2001 10:33:04   HSUCHIN
// added logic to doInitWithDefaultValues to set a new item to be non dummy when the systematic cbo is a newly created cbo
// 
//    Rev 1.22   31 Aug 2001 10:16:38   HSUCHIN
// added logic to check PACCalendar year during calculation of Next Index date
// 
//    Rev 1.21   Aug 22 2001 10:26:44   YINGBAOL
// amount can be 100m percentage
// 
//    Rev 1.20   15 Aug 2001 17:55:18   HSUCHIN
// bug fix for percentage validation
// 
//    Rev 1.19   10 Aug 2001 15:11:06   HSUCHIN
// bug fix for default indexing from saving plan
// 
//    Rev 1.18   08 Aug 2001 15:54:38   HSUCHIN
// bug fix for active index.  When the last process date is null, it is assumed that the index is not active
// 
//    Rev 1.17   Aug 07 2001 15:26:36   YINGBAOL
// fix default value issue
// 
//    Rev 1.16   02 Aug 2001 18:27:28   HSUCHIN
// added function to mark SysIndex readonly
// 
//    Rev 1.15   01 Aug 2001 17:37:20   HSUCHIN
// nextindexdate calculation bug fix
// 
//    Rev 1.14   25 Jul 2001 09:09:26   HSUCHIN
// replaced validateStartDate and validateEndDate functions with validateDateRange
// 
//    Rev 1.13   11 Jul 2001 15:09:46   HSUCHIN
// changed defaultfrequency function
// 
//    Rev 1.12   06 Jul 2001 14:08:50   HSUCHIN
// forced frequency validation on start/end date changes
// 
//    Rev 1.11   05 Jul 2001 17:43:54   HSUCHIN
// Frequency validation fix
// 
//    Rev 1.10   04 Jul 2001 17:21:54   HSUCHIN
// last process date bug fix
// 
//    Rev 1.9   04 Jul 2001 16:32:36   HSUCHIN
// validation bug fix
// 
//    Rev 1.8   11 Jun 2001 10:25:40   HSUCHIN
// fixed ReadOnly bug
// 
//    Rev 1.7   06 Jun 2001 13:38:04   HSUCHIN
// code cleanup and additional business logic added
// 
//    Rev 1.6   01 Jun 2001 17:00:50   YINGZ
// fixing
// 
//    Rev 1.5   01 Jun 2001 16:37:40   YINGZ
// fixing
// 
//    Rev 1.4   01 Jun 2001 11:36:22   HSUCHIN
// validate rule changes and bug fix
// 
//    Rev 1.3   31 May 2001 11:40:54   HSUCHIN
// view change and added conditions
// 
//    Rev 1.2   23 May 2001 12:32:18   HSUCHIN
// validation rules added
// 
//    Rev 1.1   11 May 2001 09:31:24   HSUCHIN
// Session management restructuring
// 
//    Rev 1.0   03 May 2001 13:44:54   BUZILAMI
// Initial revision.
 * 
*/
