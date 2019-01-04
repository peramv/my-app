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
// ^FILE   : JShrSumm.cpp
// ^AUTHOR : Yongmei Feng
// ^DATE   : Feb 25, 2000
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : JShrSumm
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#define IFASTCBO_DLL

#include "stdafx.h"
#include "jshrsumm.hpp"
#include <ifastdataimpl\dse_dstc0103_req.hpp>
#include <ifastdataimpl\dse_dstc0103_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest JSHRSUMM;
}

namespace
{
   const I_CHAR * const CLASSNAME = I_( "JShrSumm" );
}

JShrSumm::JShrSumm( BFAbstractCBO &parent )
: MFCanBFCbo( parent ),
_requestData(ifds::DSTC0103_REQ)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
}

//*****************************************************************************
JShrSumm::~JShrSumm()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//*****************************************************************************
SEVERITY JShrSumm::init( const DString& dstrShrNum,
                         const DString& dstrTrack,
                         const DString& dstrPageName )


{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );

   DString mgmtCoIdOut;
   _requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   _requestData.setElementValue( ifds::ShrNum, dstrShrNum );
   _requestData.setElementValue( ifds::Track, dstrTrack );
   _requestData.setElementValue( ifds::Activity, dstrPageName );

   ReceiveData(DSTC_REQUEST::JSHRSUMM, _requestData, ifds::DSTC0103_VW, DSTCRequestor( getSecurity(), true) );

   return(GETCURRENTHIGHESTSEVERITY());
}

SEVERITY JShrSumm::getMore()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );

   if( doMoreRecordsExist() )
   {
      ReceiveData(DSTC_REQUEST::JSHRSUMM, _requestData, ifds::DSTC0103_VW, DSTCRequestor( getSecurity(), false) );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/JShrSumm.cpp-arc  $
 * 
 *    Rev 1.12   Nov 14 2004 14:49:02   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.11   Mar 21 2003 18:17:42   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.10   Oct 09 2002 23:54:44   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.9   Aug 29 2002 12:56:08   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.8   22 May 2002 18:28:58   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.7   May 24 2001 10:55:44   FENGYONG
 * received all data
 * 
 *    Rev 1.6   03 May 2001 14:06:44   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.5   Jan 18 2001 16:05:18   YINGBAOL
 * add eTracker
 * 
 *    Rev 1.4   Dec 17 2000 20:24:00   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.3   Dec 06 2000 13:46:04   OLTEANCR
 * modif. ReceiveData
 * 
 *    Rev 1.2   Nov 02 2000 13:23:18   YINGBAOL
 * use new databroker
 * 
 *    Rev 1.1   Mar 24 2000 12:22:58   POPESCUS
 * Make things happen for Vision
// 
//    Rev 1.0   Feb 25 2000 16:12:34   FENGYONG
// Initial revision.
// 
// Xchgdata issue; create and delete the object in the CBO
// 
*/