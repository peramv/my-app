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
// ^FILE   : AgentList.cpp
// ^AUTHOR : Yakov Prager
// ^DATE   : November 07, 1999
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : AgentList
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include "agent.hpp"
#include "agentlist.hpp"
#include "dstcommonfunction.hpp"
#include <ifastdataimpl\dse_dstc0092_req.hpp>
#include <ifastdataimpl\dse_dstc0092_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ADVISOR;
}

namespace
{
   const I_CHAR * const CLASSNAME      = I_( "AgentList" );
   const I_CHAR * const SORT_BY_NAME   = I_( "NM" );
   const I_CHAR * const NO             = I_( "N" );
}

//*****************************************************************************
AgentList::AgentList( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
, _requestData(ifds::DSTC0092_REQ)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList();
}

//*****************************************************************************
AgentList::~AgentList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//*****************************************************************************
SEVERITY AgentList::init( const DString& dstrBrokerCode, 
                          const DString& dstrBranchCode, 
                          const DString& dstrSlsRep,
                          const DString& dstrTrack,
                          const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );
   init2 ( dstrBrokerCode, dstrBranchCode, dstrSlsRep, NULL_STRING, NULL_STRING, NULL_STRING, I_("Trade"), dstrTrack, dstrPageName );
   return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************
SEVERITY AgentList::init2( const DString& dstrBrokerCode, 
                          const DString& dstrBranchCode, 
                          const DString& dstrSlsRep,
                          const DString& dstrFundCode,
                          const DString& dstrClassCode,
                          const DString& dstrAccountNum,
                          const DString& dstrValidateType,
                          const DString& dstrTrack,
                          const DString& dstrPageName )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );

   DString mgmtCoIdOut;
   _requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   _requestData.setElementValue( ifds::BrokerCode, dstrBrokerCode );
   _requestData.setElementValue( ifds::BranchCode, dstrBranchCode );
   _requestData.setElementValue( ifds::Slsrep, dstrSlsRep );
   _requestData.setElementValue( ifds::CheckUserAccess, NO );
   _requestData.setElementValue( ifds::FundCode, dstrFundCode );
   _requestData.setElementValue( ifds::ClassCode, dstrClassCode );
   _requestData.setElementValue( ifds::AccountNum, dstrAccountNum );
   _requestData.setElementValue( ifds::ValidateType, dstrValidateType );
   _requestData.setElementValue( ifds::Track, dstrTrack );
   _requestData.setElementValue( ifds::Activity, dstrPageName );

   DString strMarket = DSTCommonFunctions::getMarket();
   if (dstrSlsRep.empty ())
   {  //sort by name
      _requestData.setElementValue (ifds::SortBy, SORT_BY_NAME);
   }
   ReceiveData (DSTC_REQUEST::ADVISOR, _requestData, ifds::DSTC0092_VW, DSTCRequestor (getSecurity(), false));
   return GETCURRENTHIGHESTSEVERITY();
}


//******************************************************************************
SEVERITY AgentList::getMore()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );

   if( doMoreRecordsExist() )
   {
      ReceiveData(DSTC_REQUEST::ADVISOR, _requestData, ifds::DSTC0092_VW, DSTCRequestor( getSecurity(), false) );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************

SEVERITY AgentList::doCreateObject( const BFData& data, BFCBO*& pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   pObjOut =  new Agent( *this );
   ((Agent*) pObjOut)->init( data );

   return(GETCURRENTHIGHESTSEVERITY());
}


//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AgentList.cpp-arc  $
 * 
 *    Rev 1.17   Sep 28 2005 18:42:40   popescu
 * Incident# 406322 - ask view to sort only if agent/branch are empty
 * 
 *    Rev 1.16   Aug 30 2005 17:36:42   popescu
 * 63 - BPS performance issues fixes
 * 1. Cached call to view 120 - account number validation  (trade.cpp/hpp)
 * 2. called the isHouseBroker method in Purchase::validateBorrowedFunds;
 * 3. AgentList/BranchList - called sorting only if agent/branch code are empty (search for all)
 * 4. Fixed 'reset' of trade (moved one line from Trade::firstLineInInit to doInit (idatagroup)
 * 5. Fixed Group.cpp/MFAccount.cpp - cached view call to 98.
 * 6. MFAccount::initDefaultAddress01 checked if shareholder in either nominee or intermediary, to skip a call to view 43
 * 
 *    Rev 1.15   Mar 21 2003 17:56:56   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.14   Mar 05 2003 11:57:44   HSUCHIN
 * PTS 10014446 - no longer using genericcbo, using agent cbo and branch cbo for effective date validation.
 * 
 *    Rev 1.13   Jan 03 2003 09:36:30   HSUCHIN
 * created init2 to support dynamic
 * 
 *    Rev 1.12   Oct 09 2002 23:54:00   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.11   Aug 29 2002 12:55:00   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.10   22 May 2002 18:26:22   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.9   16 Oct 2001 11:20:24   HSUCHIN
 * Implemented GetMore functionality
 * 
 *    Rev 1.8   03 May 2001 14:05:56   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.7   Mar 29 2001 15:55:54   DINACORN
 * Used DSTCommonFunctions MARKET_IDS constants
 * 
 *    Rev 1.6   Jan 18 2001 16:03:42   YINGBAOL
 * add eTracker
 * 
 *    Rev 1.5   Dec 17 2000 20:22:28   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.4   Dec 05 2000 17:16:00   DINACORN
 * Synchronization to C2/C3: Sort the list by Name for Canada market
 * 
 *    Rev 1.3   15 Nov 2000 15:30:20   SMITHDAV
 * Use new ReceiveData and do some cleanup.
 * 
 *    Rev 1.2   Nov 02 2000 13:23:04   YINGBAOL
 * use new databroker
 * 
 *    Rev 1.1   Jul 06 2000 11:08:20   VASILEAD
 * Added ShrtName for funds
 * 
 *    Rev 1.0   Feb 15 2000 10:59:48   SMITHDAV
 * Initial revision.
// 
//    Rev 1.5   Jan 06 2000 09:58:18   POPESCUS
// cleanup code and remove some unused methods
// 
//    Rev 1.4   Dec 16 1999 14:03:02   ZHANGCEL
// fixes bug
// 
//    Rev 1.3   Dec 12 1999 16:25:10   POPESCUS
// Xchgdata issue; create and delete the object in the CBO
// 
*/