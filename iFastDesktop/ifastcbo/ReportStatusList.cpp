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
// ^FILE   : ReportStatusList.cpp
// ^AUTHOR : 
// ^DATE   : Nov 25, 2002
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : ReportStatusList
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************

#include "stdafx.h"
#include "reportstatuslist.hpp"
#include "reportstatus.hpp"
#include <ifastdataimpl\dse_dstc0221_req.hpp>
#include <ifastdataimpl\dse_dstc0221_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest REPORT_STATUS;   
}

namespace
{
   const I_CHAR * const CLASSNAME               = I_( "ReportParamList" );
}

//******************************************************************************
// Constructor
// @param   BFBase - pointer to the parent BFBase
//******************************************************************************
ReportStatusList::ReportStatusList( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent ),
_pRequestData ( 0 )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
}

//******************************************************************************
// Destructor
//******************************************************************************
ReportStatusList::~ReportStatusList()
{
   if ( _pRequestData )
      delete _pRequestData;
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
// Makes view call 221.  A list reports status for the date range StartDate
// to EndDate is returned.
//******************************************************************************
SEVERITY ReportStatusList::init( const DString& dstrCompanyId, 
                                 const DString& dstrStartDate,
                                 const DString& dstrEndDate,
                                 const DString& dstrTrack,
                                 const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   DString mgmtCoIdOut;
   _dstrCompanyId = dstrCompanyId;
   _pRequestData = new BFData(ifds::DSTC0221_REQ);
   _pRequestData->setElementValue( ifds::CompanyId, dstrCompanyId );
   _pRequestData->setElementValue( ifds::Track, dstrTrack );
   _pRequestData->setElementValue( ifds::Activity, dstrPageName );
   _pRequestData->setElementValue( ifds::StartDate,  dstrStartDate );
   _pRequestData->setElementValue( ifds::EndDate,  dstrEndDate );
   ReceiveData(DSTC_REQUEST::REPORT_STATUS, *_pRequestData, ifds::DSTC0221_VW, DSTCRequestor( getSecurity(), false) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
// getMore retrieves more data.
// @return SEVERITY - NO_CONDITION/WARNING/SEVERE_ERROR based view call.
//                    SEVERE_ERROR if the accural type is not defined to be
//                    INTEREST_ACCRUAL/MF_ACCRUAL/MF_REBATE_ACCRUAL
//******************************************************************************
SEVERITY ReportStatusList::getMore( )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );
    
   ReceiveData(DSTC_REQUEST::REPORT_STATUS, *_pRequestData, ifds::DSTC0221_VW, DSTCRequestor( getSecurity(), false) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY ReportStatusList::doCreateObject( const BFData& data, BFCBO*& pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   pObjOut = new ReportStatus( *this );
   ( ( ReportStatus* ) ( pObjOut ) )->init( data );

   return(GETCURRENTHIGHESTSEVERITY());
}

void ReportStatusList::getCompanyId ( DString& dstrCompanyId )
{
      dstrCompanyId = _dstrCompanyId;
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ReportStatusList.cpp-arc  $
// 
//    Rev 1.4   Nov 14 2004 14:52:08   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.3   Mar 21 2003 18:21:40   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.2   Dec 08 2002 22:08:34   HSUCHIN
// added method to get company id
// 
//    Rev 1.1   Nov 29 2002 14:51:48   HSUCHIN
// check in for 50
// 
//    Rev 1.0   Nov 27 2002 11:39:06   HSUCHIN
// Initial Revision
*/
