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
// ^FILE   : JAdvisorTrans.cpp
// ^AUTHOR : Yongmei Feng
// ^DATE   : Feb 23, 2000
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : JAdvisorTrans
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include "jadvisortrans.hpp"
#include <ifastdataimpl\dse_dstc0093_req.hpp>
#include <ifastdataimpl\dse_dstc0093_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest JADVISORTRANS;
}

namespace
{
   const I_CHAR * const CLASSNAME = I_( "JAdvisorTrans" );
}

JAdvisorTrans::JAdvisorTrans( BFAbstractCBO &parent )
: MFCanBFCbo( parent ),
_requestData(ifds::DSTC0093_REQ)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
}

//*****************************************************************************
JAdvisorTrans::~JAdvisorTrans()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//*****************************************************************************
SEVERITY JAdvisorTrans::init( const DString& dstrBrokerCode, 
                              const DString& dstrBranchCode, 
                              const DString& dstrSlsRep,
                              const DString& dstrFromDate, 
                              const DString& dstrToDate,
                              const DString& dstrTrack,
                              const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );

   DString mgmtCoIdOut;
   _requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   _requestData.setElementValue( ifds::BrokerCode, dstrBrokerCode );
   _requestData.setElementValue( ifds::BranchCode, dstrBranchCode );
   _requestData.setElementValue( ifds::Slsrep, dstrSlsRep );
   _requestData.setElementValue( ifds::FromDate, dstrFromDate, false, false );
   _requestData.setElementValue( ifds::ToDate, dstrToDate, false, false );
   _requestData.setElementValue( ifds::Track, dstrTrack );
   _requestData.setElementValue( ifds::Activity, dstrPageName );

   ReceiveData(DSTC_REQUEST::JADVISORTRANS, _requestData, ifds::DSTC0093_VW, DSTCRequestor( getSecurity(), false) );

   return(GETCURRENTHIGHESTSEVERITY());
}


SEVERITY JAdvisorTrans::getMore()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );

   if( doMoreRecordsExist() )
   {
      ReceiveData(DSTC_REQUEST::JADVISORTRANS, _requestData, ifds::DSTC0093_VW, DSTCRequestor( getSecurity(), false) );
   }
   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/JAdvisorTrans.cpp-arc  $
 * 
 *    Rev 1.12   Nov 14 2004 14:48:48   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.11   Mar 21 2003 18:17:12   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.10   Oct 09 2002 23:54:42   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.9   Aug 29 2002 12:56:06   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.8   22 May 2002 18:28:56   PURDYECH
 * BFData Implementation
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
 *    Rev 1.4   Dec 06 2000 13:44:54   OLTEANCR
 * modif. ReceiveData
 * 
 *    Rev 1.3   Nov 29 2000 11:02:42   VASILEAD
 * Set the dates properly
 * 
 *    Rev 1.2   Nov 02 2000 13:23:20   YINGBAOL
 * use new databroker
 * 
 *    Rev 1.1   Mar 24 2000 12:22:58   POPESCUS
 * Make things happen for Vision
// 
//    Rev 1.0   Feb 25 2000 16:12:24   FENGYONG
// Initial revision.
// 
// Xchgdata issue; create and delete the object in the CBO
// 
*/