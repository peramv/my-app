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
// ^FILE   : ReportParamList.cpp
// ^AUTHOR : 
// ^DATE   : Nov 25, 2002
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : ReportParamList
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************

#include "stdafx.h"
#include "reportparamlist.hpp"
#include <ifastdataimpl\dse_dstc0224_req.hpp>
#include <ifastdataimpl\dse_dstc0224_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest REPORT_PARAM;   
}

namespace
{
   const I_CHAR * const CLASSNAME               = I_( "ReportParamList" );
}

//******************************************************************************
// Constructor
// @param   BFBase - pointer to the parent BFBase
//******************************************************************************
ReportParamList::ReportParamList( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent ),
_pRequestData ( 0 )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
}

//******************************************************************************
// Destructor
//******************************************************************************
ReportParamList::~ReportParamList()
{
   if ( _pRequestData )
      delete _pRequestData;
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************
// Makes view call 224.  A list of parameters used for the job is returned.
//******************************************************************************
SEVERITY ReportParamList::init( const DString& dstrSchedJobId, 
                                const DString& dstrCompanyId,
                                const BFDataGroupId& idDataGroup,
                                const DString& dstrTrack,
                                const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   DString mgmtCoIdOut;
   _pRequestData = new BFData(ifds::DSTC0224_REQ);
   _pRequestData->setElementValue( ifds::CompanyId, dstrCompanyId );
   _pRequestData->setElementValue( ifds::Track, dstrTrack );
   _pRequestData->setElementValue( ifds::Activity, dstrPageName );
   _pRequestData->setElementValue( ifds::SchedJobId,  dstrSchedJobId  );   
   ReceiveData(DSTC_REQUEST::REPORT_PARAM, *_pRequestData, ifds::DSTC0224_VW, DSTCRequestor( getSecurity(), false) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
// getMore retrieves more data.
// @return SEVERITY - NO_CONDITION/WARNING/SEVERE_ERROR based view call.
//                    SEVERE_ERROR if the accural type is not defined to be
//                    INTEREST_ACCRUAL/MF_ACCRUAL/MF_REBATE_ACCRUAL
//******************************************************************************
SEVERITY ReportParamList::getMore( )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );
    
   ReceiveData(DSTC_REQUEST::REPORT_PARAM, *_pRequestData, ifds::DSTC0224_VW, DSTCRequestor( getSecurity(), false) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/ReportParamList.cpp-arc  $
// 
//    Rev 1.4   Nov 14 2004 14:51:56   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.3   Mar 21 2003 18:21:24   PURDYECH
// BFDataGroupId/BFContainerId changeover
// 
//    Rev 1.2   Dec 08 2002 22:05:14   HSUCHIN
// added companyid to init
// 
//    Rev 1.1   Nov 29 2002 14:52:12   HSUCHIN
// check in for rel 50
// 
//    Rev 1.0   Nov 27 2002 11:39:04   HSUCHIN
// Initial Revision
*/
