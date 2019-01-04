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
//    Copyright 1999 by DST Systems, Inc.
//
//*****************************************************************************
//
// ^FILE   : JAdvisorSumm.cpp
// ^AUTHOR : Yongmei Feng
// ^DATE   : Feb 24, 2000
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : JAdvisorSumm
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include "jadvisorsumm.hpp"
#include <ifastdataimpl\dse_dstc0094_req.hpp>
#include <ifastdataimpl\dse_dstc0094_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest JADVISORSUMM;
}

namespace
{
   const I_CHAR * const CLASSNAME = I_( "JAdvisorSumm" );
}

JAdvisorSumm::JAdvisorSumm( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent ),
_queryData(ifds::DSTC0094_REQ)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
}

//*****************************************************************************
JAdvisorSumm::~JAdvisorSumm()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//*****************************************************************************
SEVERITY JAdvisorSumm::init( const DString& dstrBrokerCode, 
                             const DString& dstrBranchCode, 
                             const DString& dstrSlsRep,
                             const DString& dstrTrack,
                             const DString& dstrPageName )

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );

   DString mgmtCoIdOut;
   _queryData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   _queryData.setElementValue( ifds::BrokerCode, dstrBrokerCode );
   _queryData.setElementValue( ifds::BranchCode, dstrBranchCode  );
   _queryData.setElementValue( ifds::Slsrep, dstrSlsRep );
   _queryData.setElementValue( ifds::Track, dstrTrack );
   _queryData.setElementValue( ifds::Activity, dstrPageName );

   ReceiveData( DSTC_REQUEST::JADVISORSUMM, _queryData, ifds::DSTC0094_VW, DSTCRequestor( getSecurity(), true ) );


   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY JAdvisorSumm::getMore()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );

   if( doMoreRecordsExist() )
   {
      ReceiveData( DSTC_REQUEST::JADVISORSUMM, _queryData, ifds::DSTC0094_VW, DSTCRequestor( getSecurity() ) );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/JAdvisorSumm.cpp-arc  $
 * 
 *    Rev 1.13   Nov 14 2004 14:48:46   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.12   Mar 21 2003 18:17:06   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.11   Oct 09 2002 23:54:42   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.10   Aug 29 2002 12:56:06   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.9   22 May 2002 18:28:56   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.8   Sep 12 2001 16:34:02   FENGYONG
 * get all the record once
 * 
 *    Rev 1.7   03 May 2001 14:06:42   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.6   Jan 18 2001 16:05:16   YINGBAOL
 * add eTracker
 * 
 *    Rev 1.5   Dec 17 2000 20:23:54   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.4   Dec 06 2000 13:37:10   OLTEANCR
 * modif. ReceiveData
 * 
 *    Rev 1.3   Nov 07 2000 17:11:18   OLTEANCR
 * bug fix
 * 
 *    Rev 1.2   Nov 02 2000 13:26:08   OLTEANCR
 * new data brokering
 * 
 *    Rev 1.1   Mar 24 2000 12:22:58   POPESCUS
 * Make things happen for Vision
// 
//    Rev 1.0   Feb 25 2000 16:12:20   FENGYONG
// Initial revision.
// 
// Xchgdata issue; create and delete the object in the CBO
// 
*/