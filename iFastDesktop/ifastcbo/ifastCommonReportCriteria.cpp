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
#include "rptamsrebalancingcriterialist.hpp"
#include "mgmtcooptions.hpp"
#include <ifastdataimpl\dse_dstc0228_req.hpp>
#include <ifastdataimpl\dse_dstc0228_vw.hpp>

extern BF_OBJ_TYPE OBJ_TYPE_REPORT;

namespace
{
   const I_CHAR * const CLASSNAME = I_( "ifastCommonReportCriteria" );
   const I_CHAR * const NO = I_( "N" );
   const I_CHAR * const YES = I_( "Y" );   
   const I_CHAR * const AMS_REBALANCING = I_( "IFAST.AMSREBAL" );
   const I_CHAR * const AMS_HYPO_APPLICABLE_LIST = I_("HKB");
}

namespace CND
{
	extern const long ERR_DATE_CANNOT_EARLIER_THAN_CURRENT_BUSINESS_DATE;
   extern const long ERR_INVALID_TIME;	
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest TIMEZONE;
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
   extern CLASS_IMPORT const BFTextFieldId AMSReport;
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFTextFieldId CompanyCode;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//   Field DD Id,           State Flags,              Group Flags
   { ifds::ReportName,       BFCBO::NOT_ON_HOST,          0 }, 
   { ifds::ReportMode,       BFCBO::NOT_ON_HOST,          0 }, 
   { ifds::ReportType,       BFCBO::NOT_ON_HOST,          0 }, 
   { ifds::ScheduleJob,      BFCBO::NOT_ON_HOST,          0 }, 
   { ifds::RunOnDate,        BFCBO::NOT_ON_HOST,          0 }, 
   { ifds::RunOnTime,        BFCBO::NOT_ON_HOST,          0 }, 
   { ifds::TimeZone,         BFCBO::NOT_ON_HOST,          0 }, 
};

//*****************************************************************************

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//*****************************************************************************
// Constructor
//*****************************************************************************

ifastCommonReportCriteria::ifastCommonReportCriteria( BFAbstractCBO &parent )
:  _pCriteriaList ( NULL ),
 MFCanBFCbo( parent )
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

//******************************************************************************
SEVERITY ifastCommonReportCriteria::init(const BFDataGroupId& idDataGroup, 
   const DString& dstrTrack /*= I_("N")*/, 
   const DString& dstrPageName /*= NULL_STRING*/)
{
   MAKEFRAMEAUTOPROMOTE2(CND::IFASTCBO_CONDITION, CLASSNAME, I_("init"));
   //just to be used by the DSTCWorksession template method, getObject_X

   return GETCURRENTHIGHESTSEVERITY();
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
// @param   const BFDataGroupId& idDataGroup - Current DataGroupId.
// @returns void.
//*****************************************************************************
void ifastCommonReportCriteria::init( DString dstrRptname )
{
   setFieldAllSubstituteValues( ifds::ReportName, BF::HOST, ifds::AMSReport );
   setFieldNoValidate ( ifds::ReportName, dstrRptname, BF::HOST, true, true, true, false );
   setFieldNoValidate ( ifds::ReportMode, NO, BF::HOST, true, true, true, false );
   setFieldNoValidate ( ifds::ReportType, YES, BF::HOST, true, true, true, false );
   setFieldNoValidate ( ifds::ScheduleJob, NO, BF::HOST, true, true, true, false );
   DString dstrCurBusDate;      
   getWorkSession().getMgmtCoOptions()->getField( ifds::CurrBusDate, dstrCurBusDate, BF::HOST, false );
   setFieldNoValidate ( ifds::RunOnDate, dstrCurBusDate, BF::HOST, true, true,true, false );
   setFieldReadOnly ( ifds::RunOnDate, BF::HOST, true );
   setFieldReadOnly ( ifds::RunOnTime, BF::HOST, true );

   DString dstrTimeZone;
   getTimeZone ( dstrTimeZone, BF::HOST );
   setFieldNoValidate ( ifds::TimeZone, dstrTimeZone, BF::HOST, true, true, true, false );
}

//*****************************************************************************
// Validates the field information. The following fields are validated.
// RunOnTime - calls validateTime.
// @param   const BFFieldId& idField - field to be validated.
//          const DString& strValue - Value contained in field.
//          const BFDataGroupId& idDataGroup - datagroup to be validated.
// @returns SEVERITY.
//*****************************************************************************
SEVERITY ifastCommonReportCriteria::doValidateField( const BFFieldId& idField, 
   const DString& strValue, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doValidateField" ) );

	if ( idField == ifds::RunOnDate )
	{
		validateDate( strValue, idDataGroup );
	}
   else if( idField == ifds::RunOnTime )
   {
      validateTime ( strValue, idDataGroup );
   }
   else if (idField == ifds::ReportName )
   {
	   init(strValue);
   }   
   return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************
// Functions which makes a view call to get timezone from base system.
// @param   const BFDataGroupId& idDataGroup - current data group.
// @retursn SEVERITY.
//*****************************************************************************
void ifastCommonReportCriteria::getTimeZone( DString& dstrTimeZone, 
   const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getTimeZone" ) );
   BFData requestData(ifds::DSTC0228_REQ);
   BFData response(ifds::DSTC0228_VW);

   DString mgmtCoIdOut;
   requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   requestData.setElementValue( ifds::Track, I_( "N" ) );
   requestData.setElementValue( ifds::Activity, NULL_STRING );

   SEVERITY sevRtn = BFDataBroker::getInstance( )->receive( DSTC_REQUEST::TIMEZONE,
                                                            requestData, 
                                                            response, 
                                                            DSTCRequestor( getSecurity(), true ) );
   if ( sevRtn < WARNING ) {
      dstrTimeZone = response.getElementValue ( ifds::TimeZone );
      dstrTimeZone.strip();
   }
   else
      dstrTimeZone = NULL_STRING;   
}

//*****************************************************************************
// Method which handles related changes for field ids ScheduleJob and ReportType.
// When the fieldId is ScheduleJob - setDateTimeReadOnly is called.
// When the fieldId is ReportType - setReportMode is called.
// @param   const BFFieldId& idField - field id
//          const BFDataGroupId& idDataGroup - current data group.
// @returns SEVERITY - None.
//*****************************************************************************

SEVERITY ifastCommonReportCriteria::doApplyRelatedChanges( const BFFieldId& idField, 
																			  const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doApplyRelatedChanges" ) );
   if( idField == ifds::ScheduleJob ) 
	{
      setDateTimeReadOnly  ( idDataGroup );
   } 
	else if ( idField == ifds::ReportMode )
	{		
		_pCriteriaList->doAllReportModeRelatedChanges ( idDataGroup );
		_pCriteriaList->doInitPendingModeRelatedChanges( idDataGroup );
	}
	else if ( idField == ifds::ReportType ) 
	{
      setReportMode ( idDataGroup );
      DString dstrReportType;
      getField ( ifds::ReportType, dstrReportType, idDataGroup );
      _pCriteriaList->doReportTypeRelatedChanges ( dstrReportType == YES, idDataGroup );

		_pCriteriaList->doInitPendingModeRelatedChanges( idDataGroup );
   }
	else if ( idField == ifds::ReportName )
	{
		setFieldReadOnly( ifds::ReportName, idDataGroup, true );
		//setFieldAllSubstituteValues( ifds::ReportName, idDataGroup, ifds::AMSReport );
	}
   return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************
// This method will set the RunOnDate/RunOnTime as ReadOnly or not based on
// the value of the ScheduleJob field.  If value of ScheduleJob field is Y, then
// fields will be not Read Only and vice versa
// @param   const BFDataGroupId& idDataGroup - current data group.
// @returns void.
//*****************************************************************************

void ifastCommonReportCriteria::setDateTimeReadOnly( const BFDataGroupId& idDataGroup )
{  
   MAKEFRAMEAUTOPROMOTE2 ( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "setDateTimeReadOnly" ) );

   DString dstrScheduleJob;
   getField ( ifds::ScheduleJob, dstrScheduleJob, idDataGroup );
   setFieldReadOnly ( ifds::RunOnDate, idDataGroup, dstrScheduleJob == NO );
   setFieldReadOnly ( ifds::RunOnTime, idDataGroup, dstrScheduleJob == NO );
   setValidFlag ( ifds::RunOnTime, idDataGroup, dstrScheduleJob == NO );
   setFieldNoValidate ( ifds::RunOnTime, NULL_STRING, idDataGroup, true, true, true, false );
}

//*****************************************************************************
// This method will set the Report Mode to Update ("Y") when the Report Type 
// is changed to Cycle.  It will also mark the Report Mode as Read Only. When 
// the Report Type is changed back to Online, the Report Mode will be marked as 
// not Read Only and is updatable.
// @param   const BFDataGroupId& idDataGroup - current data group.
// @returns void.
//*****************************************************************************

void ifastCommonReportCriteria::setReportMode ( const BFDataGroupId& idDataGroup )
{  
   DString dstrReportType;
   getField ( ifds::ReportType, dstrReportType, idDataGroup );
   if ( dstrReportType == NO ) {
      setFieldNoValidate ( ifds::ReportMode, YES, idDataGroup, true, true, true, false );
      setFieldReadOnly ( ifds::ReportMode, idDataGroup, true );
   } else {
      setFieldReadOnly ( ifds::ReportMode, idDataGroup, false );
   }
}

//*****************************************************************************
SEVERITY ifastCommonReportCriteria::validateDate( const DString& dstrDate, 
																  const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateDate" ) );

	DString dstrReportName;
	getField( ifds::ReportName, dstrReportName, idDataGroup );
	
	// We don't really need to check the report type here as we have only AMS rebalancing for now (Jan 06, 2003)
	// Just to make sure that the addition of future Report Types won't create a new ticket,
	// for this type of report we need to make sure that
	// Rebalancing is not happening for a date prior or equal to last night run
	if ( dstrReportName == AMS_REBALANCING )
	{
		DString dstrCurrDate;
		getWorkSession().getMgmtCoOptions()->getField(ifds::CurrBusDate, dstrCurrDate, idDataGroup, false );
		
		DString dstrCheckDate = dstrDate;
		if( DSTCommonFunctions::CompareDates( dstrCheckDate.strip(), dstrCurrDate.strip() )== DSTCommonFunctions::FIRST_EARLIER )
			ADDCONDITIONFROMFILE( CND::ERR_DATE_CANNOT_EARLIER_THAN_CURRENT_BUSINESS_DATE );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************
// This method will validate the time entered.  It will check time using the 
// format hh:mm or hhmm.
// @param   const DString& dstrTime - Time being validated.
//          const BFDataGroupId& idDataGroup - current data group.
// @returns SEVERITY - ERR_INVALID_TIME 
//                     "Invalid value for time, must be in format of 'HH:MM'"
//*****************************************************************************

SEVERITY ifastCommonReportCriteria::validateTime ( const DString& dstrTime, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "validateTime" ) );

   DString dstrScheduleJob;
   getField ( ifds::ScheduleJob, dstrScheduleJob, idDataGroup );
   if ( dstrScheduleJob == NO )
      return NO_CONDITION;
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


//*****************************************************************************
//*****************************************************************************
SEVERITY ifastCommonReportCriteria::createCriteriaList ( ifastReportCriteriaList*& pifastReportCriteriaList, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "createCriteriaList" ) );
   DString dstrReportType, dstrRptName;
   getField ( ifds::ReportType, dstrReportType, idDataGroup );
   getField ( ifds::ReportName, dstrRptName, idDataGroup );
   _pCriteriaList = new RptAMSRebalancingCriteriaList( *this );
   _pCriteriaList->initWithRptName( idDataGroup, dstrRptName);
   pifastReportCriteriaList = _pCriteriaList;      
   _pCriteriaList->doReportTypeRelatedChanges ( dstrReportType == YES, idDataGroup );
   //BFObjectKey objKey( I_("AMS"), idDataGroup, OBJ_ACTIVITY_ADDED, OBJ_TYPE_REPORT );
   setObject(pifastReportCriteriaList, dstrRptName, OBJ_ACTIVITY_ADDED, idDataGroup );
   //setObject ( objKey, pifastReportCriteriaList );
   return(GETCURRENTHIGHESTSEVERITY());
}

void ifastCommonReportCriteria::doInitWithDefaultValues(const BFDataGroupId& idDataGroup)
{
	DString dstrCompanyCode,dstrSubList;
	getWorkSession().getOption (ifds::CompanyCode, dstrCompanyCode, idDataGroup, false);
	BFProperties *pProperties = getFieldProperties (ifds::AMSReport, idDataGroup);
	pProperties->getAllSubstituteValues (dstrSubList);
	bool bIsAMSHypoAppl = DSTCommonFunctions::codeInList (dstrCompanyCode, AMS_HYPO_APPLICABLE_LIST);
	if ( !bIsAMSHypoAppl )
		dstrSubList = removeItemFromSubtList(dstrSubList, I_("IFAST.AMSHYPOCALCREBAL"));		

	setFieldAllSubstituteValues( ifds::ReportName, idDataGroup , dstrSubList );
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ifastCommonReportCriteria.cpp-arc  $
// 
//    Rev 1.8   Nov 14 2004 14:48:24   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.7   Jun 21 2004 12:27:22   VADEANUM
// PTS 10031151 - InclPending validation.
// 
//    Rev 1.6   Jun 21 2004 10:25:48   VADEANUM
// PTS 10031437 - Excluded the edit check for error number 405 and 406 when user is running the option in 'Report' mode. 
// 
//    Rev 1.5   Jan 06 2004 10:09:22   VADEANUM
// PTS 10025333 - Missed AMS requirement - added validateDate().
// 
//    Rev 1.4   May 28 2003 10:52:16   popescu
// Part of the cleaning of DSTCWorksession, not finalized yet, more to come....
// 
//    Rev 1.3   Mar 21 2003 18:15:50   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.2   Dec 08 2002 21:53:30   HSUCHIN
// call doReportTypeRelatedChanges for Criteria lists
// 
//    Rev 1.1   Nov 29 2002 14:50:52   WINNIE
// fixed naming error
// 
//    Rev 1.0   Nov 27 2002 11:39:08   HSUCHIN
// Initial Revision
*/
