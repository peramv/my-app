
//********************************************************************************
//
// COPYRIGHT:
//
//    The computer systems, procedures, data bases and
//    programs created and maintained by DST Systems, Inc.,
//    are proprietary in nature and as such are confidential.
//    Any unauthorized use or disclosure of such information
//    may result in civil liabilities.
//
//    Copyright 2002 By International Financial Data Services.
//
//
//********************************************************************************
//
// ^FILE   : RemarkContainer.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : Sept. 10,2004
//
//********************************************************************************
#include "stdafx.h"

#include "RemarkContainer.hpp"
#include "BrokerRemarkList.hpp"


namespace RCon
{
   // Trace literals
   const I_CHAR * const CLASSNAME    = I_( "RemarkContainer" );
   const I_CHAR * const BrokerRemark = I_( "BrokerRemark" );
   const I_CHAR * const BranchRemark = I_( "BranchRemark" );
   const I_CHAR * const AgentRemark  = I_( "AgentRemark" );


}

namespace CND
{
   extern CLASS_IMPORT const long ERR_DATA_NOT_FOUND;


}


RemarkContainer::RemarkContainer( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( RCon::CLASSNAME, NULL_STRING );

}
		

//***********************************************************************************


SEVERITY RemarkContainer::init(const DString& dstrBrokerCode, 
									const DString& dstrBranchCode,
								   const DString& dstrAgentCode, 
									const DString& date,
									const BFDataGroupId& idDataGroup, 
									const DString& dstrTrack,
									const DString& dstrPageName  )
	{
		_brokerCode = dstrBrokerCode;
		_branchCode = dstrBranchCode;
		_agentCode = dstrAgentCode;
		_date = date;
	  _track = dstrTrack;
	  _pageName = dstrPageName;
	  return NO_CONDITION;


	}	

//**************************************************************************************
//bListType, 0:BrokerRemark
//			 1: BranchRemark	 
//			 2. Agent remark

void RemarkContainer::buildKey( DString &strKey, unsigned int uiListType )
{
   switch( uiListType )
   {
      case 0:
         strKey = RCon::BrokerRemark + _brokerCode+_date;
         break;
      case 1:
         strKey = RCon::BranchRemark + _brokerCode + _branchCode+_date;
			break;			
      case 2:
         strKey = RCon::AgentRemark + _brokerCode + _branchCode + _agentCode+_date;
         break;   
   }

}  
//********************************************************************************
SEVERITY RemarkContainer::getBrokerRemarkList( BrokerRemarkList*& pBrokerRemarkList,
		const BFDataGroupId& idDataGroup,unsigned int iType, bool bInq/* = true*/,
		bool bCreate /*= true*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, RCon::CLASSNAME, I_( "getBrokerRemarkList" ) );
   DString dstrKey;  
   buildKey( dstrKey, iType );
   pBrokerRemarkList = dynamic_cast< BrokerRemarkList*>( BFCBO::getObject( dstrKey, idDataGroup ) );
   BFDataGroupId idWorkingDataGroup = idDataGroup;
   if( !pBrokerRemarkList )
   {
      if( bInq )
      {
         pBrokerRemarkList = new BrokerRemarkList( *this );
         pBrokerRemarkList->init(iType,_brokerCode,_branchCode,_agentCode,_date,
									idDataGroup,_track,_pageName);
         //if we inquire the database the group id should be the host
         idWorkingDataGroup = BF::HOST;
      }

      if( pBrokerRemarkList )
      {
         if( GETCURRENTHIGHESTSEVERITY() <= WARNING )
         {
            setObject( pBrokerRemarkList, dstrKey, OBJ_ACTIVITY_NONE, idWorkingDataGroup ); 
           
         }
         else
         {
            delete pBrokerRemarkList;
            pBrokerRemarkList = NULL;
         }
      }
   }
   return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/RemarkContainer.cpp-arc  $
// 
//    Rev 1.1   Nov 14 2004 14:51:48   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.0   Sep 24 2004 14:16:54   YINGBAOL
// Initial Revision
// 




//

































	SEVERITY getBrokerRemarkList( BrokerRemarkList*& pSettlementTotalList,
		const BFDataGroupId& idDataGroup,int iType, bool bInq = true,
		bool bCreate = true );
