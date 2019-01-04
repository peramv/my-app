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
// ^FILE   : BranchList.cpp
// ^AUTHOR : Yakov Prager
// ^DATE   : November 07, 1999
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : BranchList
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include "branch.hpp"
#include "branchlist.hpp"
#include <ifastdataimpl\dse_dstc0091_req.hpp>
#include <ifastdataimpl\dse_dstc0091_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest BRANCH;
}

namespace
{
   const I_CHAR * const CLASSNAME      = I_( "BranchList" );
   const I_CHAR * const SORT_BY_NAME   = I_( "NM");
}

BranchList::BranchList( BFAbstractCBO &parent )
: MFCanBFCbo( parent ),
requestData(ifds::DSTC0091_REQ)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList();
}

//*****************************************************************************

BranchList::~BranchList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//*****************************************************************************

SEVERITY BranchList::init( const DString&  dstrBrokerCode, 
                           const DString&  dstrBranchCode, 
                           const DString& dstrTrack,
                           const DString& dstrPageName  )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );

   DString mgmtCoIdOut;
   requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   requestData.setElementValue( ifds::BrokerCode, dstrBrokerCode );
   requestData.setElementValue( ifds::BranchCode, dstrBranchCode );

   DString strMarket = DSTCommonFunctions::getMarket();
   if (dstrBranchCode.empty())
   {  //sort by name
      requestData.setElementValue (ifds::SortBy, SORT_BY_NAME);
   }

   requestData.setElementValue( ifds::Track, dstrTrack );
   requestData.setElementValue( ifds::Activity, dstrPageName );

   ReceiveData(DSTC_REQUEST::BRANCH, requestData, ifds::DSTC0091_VW, DSTCRequestor( getSecurity(), true ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************

SEVERITY BranchList::getMore()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );

   if( doMoreRecordsExist() )
   {
      ReceiveData(DSTC_REQUEST::BRANCH, requestData, ifds::DSTC0091_VW, DSTCRequestor( getSecurity(), true ) );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************

SEVERITY BranchList::doCreateObject( const BFData& data, BFCBO*& pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   pObjOut =  new Branch( *this );
   ((Branch*) pObjOut)->init( data );

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/BranchList.cpp-arc  $
 * 
 *    Rev 1.17   Sep 28 2005 18:42:52   popescu
 * Incident# 406322 - ask view to sort only if agent/branch are empty
 * 
 *    Rev 1.16   Aug 30 2005 17:37:28   popescu
 * 63 - BPS performance issues fixes
 * 1. Cached call to view 120 - account number validation  (trade.cpp/hpp)
 * 2. called the isHouseBroker method in Purchase::validateBorrowedFunds;
 * 3. AgentList/BranchList - called sorting only if agent/branch code are empty (search for all)
 * 4. Fixed 'reset' of trade (moved one line from Trade::firstLineInInit to doInit (idatagroup)
 * 5. Fixed Group.cpp/MFAccount.cpp - cached view call to 98.
 * 6. MFAccount::initDefaultAddress01 checked if shareholder in either nominee or intermediary, to skip a call to view 43
 * 
 *    Rev 1.15   Nov 14 2004 14:29:14   purdyech
 * PET910 - .NET Conversion
 * 
 *    Rev 1.14   May 27 2003 18:29:24   popescu
 * due to several memory leaks found in some list getters at the DSTCWorkSession level caused by copy/paste, I've created a common template function to retrieve the dependent objects
 * 
 *    Rev 1.13   Mar 21 2003 18:00:56   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.12   Mar 05 2003 11:57:40   HSUCHIN
 * PTS 10014446 - no longer using genericcbo, using agent cbo and branch cbo for effective date validation.
 * 
 *    Rev 1.11   Oct 09 2002 23:54:06   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.10   Aug 29 2002 12:55:10   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.9   Jul 31 2002 16:14:02   HERNANDO
 * More button implementation.
 * 
 *    Rev 1.8   22 May 2002 18:26:32   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.7   03 May 2001 14:06:02   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.6   Mar 29 2001 15:57:04   DINACORN
 * Used DSTCommonFunctions MARKET_IDS constants
 * 
 *    Rev 1.5   Jan 18 2001 16:04:12   YINGBAOL
 * add eTracker
 * 
 *    Rev 1.4   Dec 17 2000 20:22:40   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.3   Dec 06 2000 10:15:56   OLTEANCR
 * Change in ReceiveData
 * 
 *    Rev 1.2   Dec 05 2000 17:16:28   DINACORN
 * Synchronization to C2/C3: Sort the list by Name for Canada market
 * 
 *    Rev 1.1   Nov 02 2000 13:23:22   YINGBAOL
 * use new databroker
 * 
 *    Rev 1.0   Feb 15 2000 10:59:50   SMITHDAV
 * Initial revision.
// 
//    Rev 1.6   Jan 24 2000 16:34:58   BUZILA
// moved    setObjectAsList(); in constructor
// 
//    Rev 1.5   Jan 06 2000 09:58:18   POPESCUS
// cleanup code and remove some unused methods
// 
//    Rev 1.4   Dec 16 1999 14:03:16   ZHANGCEL
// fix bug
// 
//    Rev 1.3   Dec 12 1999 16:25:10   POPESCUS
// Xchgdata issue; create and delete the object in the CBO
// 
*/