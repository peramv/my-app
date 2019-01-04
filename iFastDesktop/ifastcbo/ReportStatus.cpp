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
//    Copyright 2002 by International Financial
//
//*****************************************************************************
//
// ^FILE   : ReportStatus.cpp
// ^AUTHOR : 
// ^DATE   : Nov 25, 2002
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : ReportStatus
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************

#include "stdafx.h"
#include "reportstatus.hpp"
#include "reportstatuslist.hpp"
#include "reportparamlist.hpp"
#include <ifastdataimpl\dse_dstc0221_req.hpp>
#include <ifastdataimpl\dse_dstc0221_vw.hpp>
#include <ifastdataimpl\dse_dstc0225_vw.hpp>
#include <ifastdataimpl\dse_dstc0225_req.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest REPORT_STATUS; 
   extern CLASS_IMPORT const DSTCRequest PRINT_REQUEST;
}

namespace
{
   const I_CHAR * const CLASSNAME               = I_( "ReportStatus" );
}
/*
namespace ifds
{
   extern CLASS_IMPORT const BFIntegerFieldId SchedJobId;
   extern CLASS_IMPORT const BFTextFieldId ReportName;
   extern CLASS_IMPORT const BFDateFieldId StartDate;
   extern CLASS_IMPORT const BFDateFieldId EndDate;
   extern CLASS_IMPORT const BFTextFieldId StartTime;
   extern CLASS_IMPORT const BFTimeFieldId EndTime;
   extern CLASS_IMPORT const BFTextFieldId JobStatus;
   extern CLASS_IMPORT const BFTextFieldId OutputFileName;
   extern CLASS_IMPORT const BFTextFieldId OutputFilePath;
}

const BFCBO::CLASS_FIELD_INFO classFieldInfo[] = 
{
//  Field DD Id,					State Flags,	Group Flags 
   { ifds::SchedJobId,          BFCBO::NONE, 0 },  
   { ifds::ReportName,          BFCBO::NONE, 0 },  
   { ifds::StartDate,          BFCBO::NONE, 0 },  
   { ifds::StartTime,          BFCBO::NONE, 0 },  
   { ifds::EndTime,          BFCBO::NONE, 0 },  
   { ifds::EndDate,          BFCBO::NONE, 0 },  
   { ifds::JobStatus,          BFCBO::NONE, 0 },
   { ifds::OutputFileName,          BFCBO::NONE, 0 },
   { ifds::OutputFilePath,          BFCBO::NONE, 0 }
};

static const int NUM_FIELDS = sizeof( classFieldInfo ) / sizeof( BFCBO::CLASS_FIELD_INFO );
*/
//******************************************************************************
// Constructor
// @param   BFBase - pointer to the parent BFBase
//******************************************************************************
ReportStatus::ReportStatus( BFAbstractCBO &parent ) 
: _pReportParamList(NULL),
MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );   
//   registerMemberData( NUM_FIELDS, (const CLASS_FIELD_INFO *)&classFieldInfo, 0, NULL );
}

//******************************************************************************
// Destructor
//******************************************************************************
ReportStatus::~ReportStatus()
{
   TRACE_DESTRUCTOR( CLASSNAME );
   if ( _pReportParamList )
      delete _pReportParamList;
}
//******************************************************************************
//******************************************************************************
SEVERITY ReportStatus::init ( const BFData& data )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   attachDataObject( const_cast<BFData&>(data), false, true );
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
//******************************************************************************
void ReportStatus::getReportParamList ( ReportParamList*& pReportParamList, const BFDataGroupId& idDataGroup )
{
   pReportParamList = _pReportParamList;
}

//******************************************************************************
//******************************************************************************
SEVERITY ReportStatus::createReportParamList ( ReportParamList*& pReportParamList, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getReportParamList" ) );

   DString dstrSchedJobId, dstrCompanyId;
   ReportStatusList* pReportStatusList = dynamic_cast <ReportStatusList*> ( getParent() );
   pReportStatusList->getCompanyId ( dstrCompanyId );
   getField ( ifds::SchedJobId, dstrSchedJobId, idDataGroup );
   _pReportParamList = new ReportParamList (*this);
   _pReportParamList->init ( dstrSchedJobId, dstrCompanyId, idDataGroup );
   pReportParamList = _pReportParamList;

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//******************************************************************************
SEVERITY ReportStatus::printReport ( const DString& dstrPrinterName, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "printReport" ) );
   DString dstrOutputFileName, dstrOutputFilePath, dstrCompanyId;
   ReportStatusList* pReportStatusList = dynamic_cast <ReportStatusList*> ( getParent() );
   pReportStatusList->getCompanyId ( dstrCompanyId );
   getField ( ifds::OutputFileName, dstrOutputFileName, idDataGroup );
   getField ( ifds::OutputFilePath, dstrOutputFilePath, idDataGroup );
   BFData requestData (ifds::DSTC0225_REQ);
   requestData.setElementValue( ifds::PrinterName, dstrPrinterName );
   requestData.setElementValue( ifds::OutputFileName, dstrOutputFileName );
   requestData.setElementValue( ifds::OutputFilePath, dstrOutputFilePath );
   requestData.setElementValue( ifds::CompanyId, dstrCompanyId );
   requestData.setElementValue( ifds::Track, I_("N") );
   requestData.setElementValue( ifds::Activity, NULL_STRING );

   ReceiveData( DSTC_REQUEST::PRINT_REQUEST, requestData, ifds::DSTC0225_VW, DSTCRequestor( getSecurity(), false) );
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ReportStatus.cpp-arc  $
// 
//    Rev 1.4   Nov 14 2004 14:51:58   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.3   Mar 21 2003 18:21:28   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.2   Dec 08 2002 22:05:54   HSUCHIN
// implemented printreport method
// 
//    Rev 1.1   Nov 29 2002 14:52:14   HSUCHIN
// check in for rel 50
// 
//    Rev 1.0   Nov 27 2002 11:39:06   HSUCHIN
// Initial Revision
*/
