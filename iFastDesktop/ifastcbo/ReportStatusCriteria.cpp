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
// ^FILE   : ReportStatusCriteria.cpp
// ^AUTHOR : 
// ^DATE   : Nov 27, 2002
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : ReportStatusCriteria
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include "reportstatuscriteria.hpp"
#include "reportstatuslist.hpp"
#include "mgmtcooptions.hpp"
#include "mgmtco.hpp"

//#include <core\uibase\dstoledatetime.h>

namespace
{
   const I_CHAR * const CLASSNAME = I_( "ReportStatusCriteria" );
   const I_CHAR * const NO = I_( "N" );
   const I_CHAR * const YES = I_( "Y" );   
}

namespace CND
{
   //extern const long ERR_INVALID_TIME;
}

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest TIMEZONE;
}

namespace ifds
{
   
   extern CLASS_IMPORT const BFDateFieldId CurrBusDate;
   extern CLASS_IMPORT const BFTextFieldId CompanyId;   
   extern CLASS_IMPORT const BFDateFieldId StartDate;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = {
//   Field DD Id,           State Flags,              Group Flags
   { ifds::CompanyId,       BFCBO::REQUIRED,          0 }, 
   { ifds::StartDate,       BFCBO::REQUIRED,          0 }, 
};

//*****************************************************************************

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );

//*****************************************************************************
// Constructor
//*****************************************************************************

ReportStatusCriteria::ReportStatusCriteria( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );      
   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}

//*****************************************************************************
// Destructor
//*****************************************************************************

ReportStatusCriteria::~ReportStatusCriteria()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//*****************************************************************************
// Inits the ReportStatusCriteria CBO with default data.
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

void ReportStatusCriteria::init( const BFDataGroupId& idDataGroup )
{
   DString dstrCurBusDate, dstrSubList, dstrCompanyId, dstrCompanyName;      
//   getWorkSession().getMgmtCoOptions()->getField( ifds::CurrBusDate, dstrCurBusDate, BF::HOST, false );
//   setFieldNoValidate ( ifds::StartDate, dstrCurBusDate, idDataGroup, true, true,true, false );

   SYSTEMTIME st;
   GetLocalTime( &st );
   BFDate bfDate ( st );
   dstrCurBusDate = bfDate.get( BFDate::hostFormat() );
   setFieldNoValidate ( ifds::StartDate, dstrCurBusDate, idDataGroup, true, true,true, false );
   createMgmtCoSubList ( dstrSubList );
   setFieldAllSubstituteValues( ifds::CompanyId, idDataGroup, dstrSubList );    
   //getWorkSession().getMgmtCo().getField(ifds::CompanyId, dstrCompanyId, idDataGroup);
   getUserSession().getCompanyInfo( DSTCHost::getPrimaryHost(), 0, dstrCompanyId, dstrCompanyName );
   setFieldNoValidate ( ifds::CompanyId, dstrCompanyId, idDataGroup );
}

//*****************************************************************************
//*****************************************************************************
SEVERITY ReportStatusCriteria::getReportStatusList ( ReportStatusList*& pReportStatusList, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getReportStatusList" ) );
   pReportStatusList = dynamic_cast <ReportStatusList*> (getObject( I_("ReportStatus"), idDataGroup ));
   return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************
//*****************************************************************************
SEVERITY ReportStatusCriteria::createReportStatusList ( ReportStatusList*& pReportStatusList, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "createCriteriaList" ) );
   pReportStatusList = new ReportStatusList( *this );
   DString dstrCompanyId, dstrStartDate, dstrEndDate;
   getField ( ifds::CompanyId, dstrCompanyId, idDataGroup );
   getField ( ifds::StartDate, dstrStartDate, idDataGroup );
   DSTCommonFunctions::getFormat12319999Date ( dstrEndDate );
   pReportStatusList->init( dstrCompanyId, dstrStartDate, dstrEndDate );
   setObject(pReportStatusList, I_("ReportStatus"), OBJ_ACTIVITY_NONE, idDataGroup );
   return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************
SEVERITY ReportStatusCriteria::createMgmtCoSubList ( DString& dstrSubList )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "createMgmtCoSubList" ) );
   DSTCUserSession& pDSTCUserSession = getUserSession ();
   DString dstrCompanyId, dstrCompanyName;
   BFSubst lBFSubst;
   long  lNumberOfCompanies = pDSTCUserSession.getNumberOfCompanies( DSTCHost::getPrimaryHost() );
   for( short nCtr = 0; nCtr < lNumberOfCompanies; ++nCtr )
   {
      pDSTCUserSession.getCompanyInfo( DSTCHost::getPrimaryHost(), nCtr, dstrCompanyId, dstrCompanyName );
      lBFSubst.addSubst ( dstrCompanyId, dstrCompanyName );      
   }
   if( lNumberOfCompanies == 0 )
      lBFSubst.addSubst( BLANK_STRING, BLANK_STRING );
   lBFSubst.getList( dstrSubList );   
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ReportStatusCriteria.cpp-arc  $
// 
//    Rev 1.3   Nov 14 2004 14:52:06   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.2   Mar 21 2003 18:21:34   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.1   Dec 08 2002 22:07:44   HSUCHIN
// init startdate from system time
// 
//    Rev 1.0   Nov 29 2002 13:51:20   HSUCHIN
// Initial Revision
*/
