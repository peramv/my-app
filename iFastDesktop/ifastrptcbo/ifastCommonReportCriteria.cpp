//*****************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by International Financial, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2002 by International Financial, Inc.
//
//*****************************************************************************
//
// ^FILE   : ifastCommonReportCriteria.cpp
// ^AUTHOR : 
// ^DATE   : Nov 13, 2002
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : ifastCommonReportCriteria
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include "ifastcommonreportcriteria.hpp"

namespace
{
   const I_CHAR * const CLASSNAME = I_( "ifastCommonReportCriteria" );
   const I_CHAR * const NO = I_( "N" );
   const I_CHAR * const YES = I_( "Y" );   
   const I_CHAR * const AMS_REBALANCING = I_( "IFAST.AMSREBAL" );
}

namespace CND
{
   extern CLASS_IMPORT const long ERR_INVALID_TIME;
}

namespace ifds
{
   extern CLASS_IMPORT const BFTextFieldId ReportName;
   extern CLASS_IMPORT const BFTextFieldId ReportMode;
   extern CLASS_IMPORT const BFTextFieldId ReportType;
   extern CLASS_IMPORT const BFTextFieldId ScheduleJob;
   extern CLASS_IMPORT const BFDateFieldId RunOnDate;
   extern CLASS_IMPORT const BFTextFieldId RunOnTime;
   extern CLASS_IMPORT const BFTextFieldId TimeZone;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//   Field DD Id,           State Flags,              Group Flags
   { BFCBO::CLASS_FIELD_INFO( ifds::ReportName,       BFCBO::NOT_ON_HOST,          0 )}, 
   { BFCBO::CLASS_FIELD_INFO( ifds::ReportMode,       BFCBO::NOT_ON_HOST,          0 )}, 
   { BFCBO::CLASS_FIELD_INFO( ifds::ReportType,       BFCBO::NOT_ON_HOST,          0 )}, 
   { BFCBO::CLASS_FIELD_INFO( ifds::ScheduleJob,      BFCBO::NOT_ON_HOST,          0 )}, 
   { BFCBO::CLASS_FIELD_INFO( ifds::RunOnDate,        BFCBO::NOT_ON_HOST,          0 )}, 
   { BFCBO::CLASS_FIELD_INFO( ifds::RunOnTime,        BFCBO::NOT_ON_HOST,          0 )}, 
   { BFCBO::CLASS_FIELD_INFO( ifds::TimeZone,         BFCBO::NOT_ON_HOST,          0 )}, 
};

//*****************************************************************************

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//*****************************************************************************
// Constructor
//*****************************************************************************

ifastCommonReportCriteria::ifastCommonReportCriteria( BFAbstractCBO &parent )
:  MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );   
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}

//*****************************************************************************
// Destructor
//*****************************************************************************

ifastCommonReportCriteria::~ifastCommonReportCriteria()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//*****************************************************************************
// Inits the ifastCommonReportCriteria CBO with default data.
//    Field             Value             Description
//    ReportName        IFAST.AMSREBAL    AMS Rebalancing
//    ReportMode        N                 Report Mode
//    ReportType        Y                 Online
//    Schedule          N                 Run Now
//    
// RunOnDate, RunOnTime field will be marked as ReadOnly
// @param   long lDataGroupId - Current DataGroupId.
// @returns void.
//*****************************************************************************

void ifastCommonReportCriteria::init( )
{
   setField ( ifds::ReportName, AMS_REBALANCING, BF::HOST );
   setField ( ifds::ReportMode, NO, BF::HOST );
   setField ( ifds::ReportType, YES, BF::HOST );
   setField ( ifds::ScheduleJob, NO, BF::HOST );
   setFieldReadOnly ( ifds::RunOnDate, BF::HOST, true );
   setFieldReadOnly ( ifds::RunOnTime, BF::HOST, true );
}

//*****************************************************************************
// Validates the field information. The following fields are validated.
// RunOnTime - calls validateTime.
// @param   const BFFieldId &idField - field to be validated.
//          const DString &strValue - Value contained in field.
//          long lDataGroupId - datagroup to be validated.
// @returns SEVERITY.
//*****************************************************************************

SEVERITY ifastCommonReportCriteria::doValidateField( const BFFieldId &idField, const DString& strValue, long  lDataGroupId )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );

   if( idField == ifds::RunOnTime )
   {
      validateTime ( strValue, lDataGroupId );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************
// Functions which makes a view call to get timezone from base system.
// @param   long lDataGroupId - current data group.
// @retursn SEVERITY.
//*****************************************************************************

SEVERITY ifastCommonReportCriteria::getTimeZone(long lDataGroupId)
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getTimeZone" ) );
   return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************
// Method which handles related changes for field ids ScheduleJob and ReportType.
// When the fieldId is ScheduleJob - setDateTimeReadOnly is called.
// When the fieldId is ReportType - setReportMode is called.
// @param   const BFFieldId &idField - field id
//          long lDataGroupId - current data group.
// @returns SEVERITY - None.
//*****************************************************************************

SEVERITY ifastCommonReportCriteria::doApplyRelatedChanges( const BFFieldId &idField, long lDataGroupId )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );
   if( idField == ifds::ScheduleJob ) {
      setDateTimeReadOnly  ( lDataGroupId );
   } else if ( idField == ifds::ReportType ) {
      setReportMode ( lDataGroupId );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************
// This method will set the RunOnDate/RunOnTime as ReadOnly or not based on
// the value of the ScheduleJob field.  If value of ScheduleJob field is Y, then
// fields will be not Read Only and vice versa
// @param   long lDataGroupId - current data group.
// @returns void.
//*****************************************************************************

void ifastCommonReportCriteria::setDateTimeReadOnly( long lDataGroupId )
{  
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setDateTimeReadOnly" ) );

   DString dstrScheduleJob;
   getField ( ifds::ScheduleJob, dstrScheduleJob, lDataGroupId );
   setFieldReadOnly ( ifds::RunOnDate, lDataGroupId, dstrScheduleJob == NO );
   setFieldReadOnly ( ifds::RunOnTime, lDataGroupId, dstrScheduleJob == NO );   
}

//*****************************************************************************
// This method will set the Report Mode to Update ("Y") when the Report Type 
// is changed to Cycle.  It will also mark the Report Mode as Read Only. When 
// the Report Type is changed back to Online, the Report Mode will be marked as 
// not Read Only and is updatable.
// @param   long lDataGroupId - current data group.
// @returns void.
//*****************************************************************************

void ifastCommonReportCriteria::setReportMode ( long lDataGroupId )
{  
   DString dstrReportType;
   getField ( ifds::ReportType, dstrReportType, lDataGroupId );
   if ( dstrReportType == NO ) {
      setFieldNoValidate ( ifds::ReportMode, YES, lDataGroupId, true, true, true, false );
      setFieldReadOnly ( ifds::ReportMode, lDataGroupId, true );
   } else {
      setFieldReadOnly ( ifds::ReportMode, lDataGroupId, false );
   }
}

//*****************************************************************************
// This method will validate the time entered.  It will check time using the 
// format hh:mm or hhmm.
// @param   const DString& dstrTime - Time being validated.
//          long lDataGroupId - current data group.
// @returns SEVERITY - ERR_INVALID_TIME 
//                     "Invalid value for time, must be in format of 'HH:MM'"
//*****************************************************************************

SEVERITY ifastCommonReportCriteria::validateTime ( const DString& dstrTime, long lDataGroupId )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateTime" ) );

   DString strTime( dstrTime );
   DString::size_type iPos = strTime.find( I_(":") );
   if ( dstrTime.empty() ||
      ( iPos == std::string::npos ) ) {
      ADDCONDITIONFROMFILE( CND::ERR_INVALID_TIME );
      return(GETCURRENTHIGHESTSEVERITY());
   } else {      
      int iHour,iMin;
      iHour = DString( strTime.substr( 0,iPos ) ).asInteger();
      iMin =  DString( strTime.substr( iPos+1,2 ) ).asInteger();
      if( iHour < 0  || iHour > 23 || iMin < 0 || iMin > 59 )
      {
         ADDCONDITIONFROMFILE( CND::ERR_INVALID_TIME );
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastrptcbo/ifastCommonReportCriteria.cpp-arc  $
// 
//    Rev 1.0   Nov 14 2002 15:21:46   HSUCHIN
// Initial Revision
*/
