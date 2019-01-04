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
//    Copyright 2000 by DST Canada Inc.
//
//
//******************************************************************************
//
// ^FILE   : MinMaxInfoList.cpp
// ^AUTHOR : Celia Zhang
// ^DATE   : 02/15/2000
//
// ^CLASS    : MinMaxInfoList
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************
#include "stdafx.h"
#include "minmaxinfolist.hpp"
#include <ifastdataimpl\dse_dstc0109_vw.hpp>
#include <ifastdataimpl\dse_dstc0109_req.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest MINMAX;
}

namespace
{
   //Trace literals
   const I_CHAR *  CLASSNAME           = I_( "MinMaxInfoList" );
   const I_CHAR * DATE_FORMAT          = I_( "MMddyyyy" );
}

//
// Constructors
//
// *********************************************************************************

MinMaxInfoList::MinMaxInfoList( BFAbstractCBO &parent ) 
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList();
}


// *********************************************************************************

MinMaxInfoList::~MinMaxInfoList()
{
   TRACE_DESTRUCTOR( CLASSNAME );

}


// *********************************************************************************

SEVERITY MinMaxInfoList::init( const DString& AccountNumber, 
                               const DString& LastValDate,
                               const DString& dstrTrack,
                               const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init( int, DString&, DString& )" ) );


   BFData queryData(ifds::DSTC0109_REQ);

   DString mgmtCoIdOut;
   queryData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   queryData.setElementValue( ifds::AccountNum, AccountNumber );
   queryData.setElementValue( ifds::AsofDate, LastValDate, false, false );
   queryData.setElementValue( ifds::Track, dstrTrack );
   queryData.setElementValue( ifds::Activity, dstrPageName );

   ReceiveData( DSTC_REQUEST::MINMAX, queryData, ifds::DSTC0109_VW, DSTCRequestor( getSecurity() ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//************************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/MinMaxInfoList.cpp-arc  $
 * 
 *    Rev 1.12   Nov 14 2004 14:50:26   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.11   Mar 21 2003 18:19:06   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.10   Oct 09 2002 23:54:48   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.9   Aug 29 2002 12:56:22   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.8   22 May 2002 18:29:36   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.7   03 May 2001 14:06:52   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.6   Jan 18 2001 16:05:40   YINGBAOL
 * add eTracker
 * 
 *    Rev 1.5   Dec 17 2000 20:24:10   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.4   Dec 06 2000 14:01:22   OLTEANCR
 * modif. ReceiveData
 * 
 *    Rev 1.3   Nov 01 2000 15:31:24   OLTEANCR
 * new data brokering
 * 
 *    Rev 1.2   Oct 18 2000 17:42:30   ZHANGCEL
 *  Clean code  up
 * 
 *    Rev 1.1   Mar 21 2000 14:31:08   ZHANGCEL
 * Milestone check in
 * 
 *    Rev 1.0   Mar 20 2000 15:49:44   ZHANGCEL
 * Initial revision.
// 
//
 *
 */