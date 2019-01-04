#define IFASTCBO_DLL

//******************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 1999 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : JFundInDiv.cpp
// ^AUTHOR : Yongmei Feng
// ^DATE   : 25/02/00
//
// ^CLASS    : JFundInDiv
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "jfundindiv.hpp"
#include <ifastdataimpl\dse_dstc0104_req.hpp>
#include <ifastdataimpl\dse_dstc0104_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest JFUNDINDIV;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME = I_( "JFundInDiv" );

}

//******************************************************************************
JFundInDiv::JFundInDiv( BFAbstractCBO &parent )
: MFCanBFCbo( parent ),
_requestData(ifds::DSTC0104_REQ)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
}


//******************************************************************************
JFundInDiv::~JFundInDiv( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************

SEVERITY JFundInDiv::init( DString& dstFundCode, 
                           DString& dstClassCode, 
                           DString& dstFromDate, 
                           DString& dstToDate,
                           const DString& dstrTrack,
                           const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );
   DString dstNextKey = NULL_STRING;

   DString mgmtCoIdOut;
   _requestData.setElementValue( ifds::CompanyId,         getMgmtCoId( mgmtCoIdOut ) );
   _requestData.setElementValue( ifds::FundCode,          dstFundCode        ); 
   _requestData.setElementValue( ifds::ClassCode,         dstClassCode       );
   _requestData.setElementValue( ifds::FromDate,          dstFromDate,       false, false );
   _requestData.setElementValue( ifds::ToDate,            dstToDate,         false, false );
   _requestData.setElementValue( ifds::NextKey,           dstNextKey         );
   _requestData.setElementValue( ifds::Track, dstrTrack );
   _requestData.setElementValue( ifds::Activity, dstrPageName );

   ReceiveData(DSTC_REQUEST::JFUNDINDIV, _requestData, ifds::DSTC0104_VW, DSTCRequestor( getSecurity(), false) );

   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
SEVERITY JFundInDiv::search( bool bClearPreviousSearch )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "search" ) );

   if( bClearPreviousSearch )
   {
      eraseDataObjectContainers();
      eraseObjectContainer();
      _requestData.setElementValue( ifds::NextKey,           NULL_STRING         );
   };

   ReceiveData(DSTC_REQUEST::JFUNDINDIV, _requestData, ifds::DSTC0104_VW, DSTCRequestor( getSecurity(),false ) );

   return(GETCURRENTHIGHESTSEVERITY());


}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/JFundInDiv.cpp-arc  $
 * 
 *    Rev 1.11   Nov 14 2004 14:49:00   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.10   Mar 21 2003 18:17:36   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.9   Oct 09 2002 23:54:42   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.8   Aug 29 2002 12:56:06   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.7   22 May 2002 18:28:56   PURDYECH
 * BFData Implementation
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
 *    Rev 1.3   Dec 06 2000 13:46:00   OLTEANCR
 * modif. ReceiveData
 * 
 *    Rev 1.2   Nov 02 2000 13:23:18   YINGBAOL
 * use new databroker
 * 
 *    Rev 1.1   Mar 24 2000 12:22:58   POPESCUS
 * Make things happen for Vision
// 
//    Rev 1.0   Feb 25 2000 16:12:32   FENGYONG
// Initial revision.
 * 
 * Xchgdata issue; create and delete the object in the CBO
// 
*/