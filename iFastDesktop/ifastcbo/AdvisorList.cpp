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
// ^FILE   : AdvisorList.cpp
// ^AUTHOR : Yongmei Feng
// ^DATE   : Feb 21, 2000
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : AdvisorList
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include "advisorlist.hpp"
#include "advisor.hpp"
#include <ifastdataimpl\dse_dstc0092_req.hpp>
#include <ifastdataimpl\dse_dstc0092_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest ADVISOR;
}

namespace
{
   const I_CHAR * const CLASSNAME = I_( "AdvisorList" );
}

AdvisorList::AdvisorList( BFAbstractCBO &parent )
: MFCanBFCbo( parent ),
_requestData(ifds::DSTC0092_REQ)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList();
}

//*****************************************************************************
AdvisorList::~AdvisorList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//*****************************************************************************
SEVERITY AdvisorList::init( const DString& dstrBrokerCode, 
                            const DString& dstrBranchCode, 
                            const DString& dstrSlsRep, 
                            const DString& Allresult,
                            const DString& dstrTrack,
                            const DString& dstrPageName )               
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );

   bool allresult = false;

   if( Allresult == I_("true") )
      allresult = true;

   DString mgmtCoIdOut;
   _requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   _requestData.setElementValue( ifds::BrokerCode, dstrBrokerCode );
   _requestData.setElementValue( ifds::BranchCode, dstrBranchCode );
   _requestData.setElementValue( ifds::Slsrep, dstrSlsRep );
   _requestData.setElementValue( ifds::CheckUserAccess, I_( "N" ) );
   _requestData.setElementValue( ifds::IgnoreBrokerBranch, I_( "Y" ) );
   _requestData.setElementValue( ifds::SortBy, I_( "NM" ) );
   _requestData.setElementValue( ifds::Track, dstrTrack );
   _requestData.setElementValue( ifds::Activity, dstrPageName );

   ReceiveData(DSTC_REQUEST::ADVISOR, _requestData, ifds::DSTC0092_VW, DSTCRequestor( getSecurity(), allresult ) );

   return(GETCURRENTHIGHESTSEVERITY());
}

SEVERITY AdvisorList::getMore()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );

   if( doMoreRecordsExist() )
   {
      ReceiveData(DSTC_REQUEST::ADVISOR, _requestData, ifds::DSTC0092_VW, DSTCRequestor( getSecurity(), false ) );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
void AdvisorList::buildKey( const DString& strBrokerCode, const DString& strBranchCode, const DString& strSlsRep,DString &strKey )
{
   strKey = strBrokerCode + I_(" ") + strSlsRep;
   strKey.strip().upperCase();
}

//******************************************************************************
void AdvisorList::getStrKey (DString &strKey, const BFData *data)
{
   TRACE_METHOD( CLASSNAME, I_( "getStrKey" ) );

/*   if( data )
  {
    DString strBrokerCode = data->getElementValue( I_( "BrokerCode" ) );
      //DString strBranchCode = data->getElementValue( I_( "BranchCode" ) );
      DString strSlsRep = data->getElementValue( I_( "Slsrep" ) );
      strKey = strBrokerCode.strip() + I_(" ") + strSlsRep.strip();
      strKey.upperCase();
   }
   else
   {
     BFCBO::getStrKey( strKey , NULL );
   }
*/
   BFCBO::getStrKey( strKey , NULL );
}

//******************************************************************************
SEVERITY AdvisorList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );

   Advisor * pAdvisor = new Advisor( *this );
   pAdvisor->init( this, data );
   pObjOut = pAdvisor;

   return(GETCURRENTHIGHESTSEVERITY());
}

SEVERITY AdvisorList::doCreateNewObject(BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

   pBase = new Advisor( *this );
   ((Advisor* )pBase)->init( this, idDataGroup );    

   return(GETCURRENTHIGHESTSEVERITY());
}

void AdvisorList::getTrackActivity(DString& strTrack,DString& strActivity)
{
   strTrack = I_("Y");
   strActivity = I_("SlsRep");
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/AdvisorList.cpp-arc  $
 * 
 *    Rev 1.18   Mar 21 2003 17:56:46   PURDYECH
 * BFDataGroupId/BFContainerId changeover
 * 
 *    Rev 1.17   Oct 09 2002 23:54:00   PURDYECH
 * PVCS Database Conversion
 * 
 *    Rev 1.16   Aug 29 2002 12:55:00   SMITHDAV
 * ClientLocale and typed field changes.
 * 
 *    Rev 1.15   22 May 2002 18:26:22   PURDYECH
 * BFData Implementation
 * 
 *    Rev 1.14   Jan 25 2002 13:15:04   FENGYONG
 * comment out getstrkey for eadvisor sequence
 * 
 *    Rev 1.13   Jan 18 2002 13:26:16   FENGYONG
 * Set ignoreBrokerBranch = yes
 * 
 *    Rev 1.12   Jan 17 2002 14:54:18   FENGYONG
 * comment branck code and add this to init function
 * 
 *    Rev 1.11   Jan 04 2002 17:36:54   FENGYONG
 * remove branch from key
 * 
 *    Rev 1.10   Jan 04 2002 10:11:28   FENGYONG
 * Add CBO advisor
 * 
 *    Rev 1.9   03 May 2001 14:05:56   SMITHDAV
 * Session management restructuring.
 * 
 *    Rev 1.8   Jan 18 2001 16:03:40   YINGBAOL
 * add eTracker
 * 
 *    Rev 1.7   Dec 17 2000 20:22:28   OLTEANCR
 * changed to use a precompiled header
 * 
 *    Rev 1.6   Dec 04 2000 13:22:30   VASILEAD
 * Sorted the advisor list after the names
 * 
 *    Rev 1.5   Nov 17 2000 14:41:12   FENGYONG
 * Add allresult
 * 
 *    Rev 1.4   15 Nov 2000 15:30:18   SMITHDAV
 * Use new ReceiveData and do some cleanup.
 * 
 *    Rev 1.3   Nov 02 2000 13:23:04   YINGBAOL
 * use new databroker
 * 
 *    Rev 1.2   Jul 06 2000 11:08:18   VASILEAD
 * Added ShrtName for funds
 * 
 *    Rev 1.1   Mar 24 2000 12:22:58   POPESCUS
 * Make things happen for Vision
// 
//    Rev 1.0   Feb 25 2000 16:10:48   FENGYONG
// Initial revision.
// 
// Xchgdata issue; create and delete the object in the CBO
// 
*/