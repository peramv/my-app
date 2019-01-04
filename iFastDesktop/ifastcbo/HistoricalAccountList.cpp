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
// ^FILE   : HistoricalAccountList.cpp
// ^AUTHOR : Chin Hsu
// ^DATE   : Oct 14, 1999
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : HistoricalAccountList
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include "historicalaccountlist.hpp"
#include <ifastdataimpl\dse_dstc0249_vw.hpp>
#include <ifastdataimpl\dse_dstc0110_req.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest HISTORICAL_ACCOUNT;
}

namespace
{
   const I_CHAR * const CLASSNAME = I_( "HistoricalAccountList" );
}

HistoricalAccountList::HistoricalAccountList( BFAbstractCBO &parent )
: MFCanBFCbo( parent ),
_queryData(ifds::DSTC0110_REQ) 
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
}

HistoricalAccountList::~HistoricalAccountList()
{
   TRACE_DESTRUCTOR( CLASSNAME );

}
//*******************************************************************************************
SEVERITY HistoricalAccountList::init( const DString& strAccountNumber, const DString& dstrTrack, const DString& dstrPageName )

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );   

   DString mgmtCoIdOut;
   _queryData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   _queryData.setElementValue( ifds::AccountNum, strAccountNumber ); 
   _queryData.setElementValue( ifds::Track, dstrTrack );
   _queryData.setElementValue( ifds::Activity, dstrPageName );
   _queryData.setElementValue( ifds::HistoricalType, I_("Acct") );

   ReceiveData( DSTC_REQUEST::HISTORICAL_ACCOUNT, _queryData, ifds::DSTC0249_VW, DSTCRequestor( getSecurity() ) );


   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
SEVERITY HistoricalAccountList::search( bool bClearPreviousSearch )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "search" ) );
   if( bClearPreviousSearch )
   {
      eraseDataObjectContainers();
      eraseObjectContainer();
      _queryData.setElementValue( ifds::NextKey, NULL_STRING );
   }

   return(ReceiveData( DSTC_REQUEST::HISTORICAL_ACCOUNT, _queryData, ifds::DSTC0249_VW, DSTCRequestor( getSecurity(), false ) ));

}
//******************************************************************************
bool HistoricalAccountList::moreRecordsExist()
{
   MAKEFRAMEAUTOPROMOTE( CLASSNAME, I_( "moreRecordsExist" ) );
   // return _pXchgData->moreRecordsExist();
   return(doMoreRecordsExist());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/HistoricalAccountList.cpp-arc  $
 * 
 *    Rev 1.11   Nov 14 2004 14:43:54   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.10   Feb 28 2004 15:43:44   HERNANDO
 * PET965 FN11 - Request now includes HistoricalType.  Response was changed to View 249.
 * 
 *    Rev 1.9   Mar 21 2003 18:13:08   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.8   Oct 09 2002 23:54:36   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.7   Aug 29 2002 12:56:02   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.6   22 May 2002 18:28:50   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.5   03 May 2001 14:06:40   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.4   Jan 18 2001 16:05:14   YINGBAOL
 * add eTracker
 * 
 *    Rev 1.3   Dec 17 2000 20:23:48   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.2   Dec 06 2000 11:54:44   OLTEANCR
 * modif. ReceiveData
 * 
 *    Rev 1.1   Nov 02 2000 13:35:00   OLTEANCR
 * new data brokering
 * 
 *    Rev 1.0   Feb 15 2000 11:00:00   SMITHDAV
 * Initial revision.
// 
//    Rev 1.5   Jan 05 2000 20:10:50   BUZILA
// adding list flag
// 
//    Rev 1.4   Dec 12 1999 16:25:26   POPESCUS
// Xchgdata issue; create and delete the object in the CBO
// 
//    Rev 1.3   Dec 09 1999 10:43:36   POPESCUS
// Fixed some memory leaks
*/