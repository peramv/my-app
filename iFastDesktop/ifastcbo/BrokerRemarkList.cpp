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
//    Copyright 2004 by IFDS.
//
//*****************************************************************************
//
// ^FILE   : BrokerRemarkList.cpp
// ^AUTHOR : Yingbao Li	
// ^DATE   : Sept. 10, 2004
//
//-----------------------------------------------------------------------------
//
// ^CLASS  : BrokerRemarkList
//
// ^MEMBER VARIABLES :
//
// ^CODING COMMENTS :
//
//*****************************************************************************
#include "stdafx.h"
#include "BrokerRemark.hpp"
#include "BrokerRemarkList.hpp"
#include <ifastdataimpl\dse_dstc0315_req.hpp>
#include <ifastdataimpl\dse_dstc0315_vw.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest BROKER_REMARK_LIST;
}

namespace
{
   const I_CHAR * const CLASSNAME = I_( "BrokerRemarkList" );
}

//*****************************************************************************
BrokerRemarkList::BrokerRemarkList( BFAbstractCBO &parent )
: MFCanBFCbo( parent )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
}

//*****************************************************************************
BrokerRemarkList::~BrokerRemarkList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//*****************************************************************************
SEVERITY BrokerRemarkList::init(
	const int iType,
	const DString& dstrBrokerCode, 
	const DString& dstrBranchCode, 
	const DString& dstrAgentCode,
	const DString& dstrAsofDate,
	const BFDataGroupId& idDataGroup, 
   const DString& dstrTrack /*=I_("N")*/, 
   const DString& dstrPageName /*=NULL_STRING*/)

{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init") );

   BFData queryData(ifds::DSTC0315_REQ);

	_brokerCode = dstrBrokerCode;
   _branchCode = NULL_STRING;
	_agentCode = NULL_STRING;

   DString mgmtCoIdOut;
   queryData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   queryData.setElementValue( ifds::BrokerCode, dstrBrokerCode );
	if(iType == 1 || iType == 2)
	{
		   _branchCode = dstrBranchCode;
			queryData.setElementValue( ifds::BranchCode, dstrBranchCode );
			if( iType ==2 )
			{
			   queryData.setElementValue( ifds::AgentCode, dstrAgentCode );
				_agentCode = dstrAgentCode;
			}
	}
   queryData.setElementValue( ifds::AsofDate, dstrAsofDate );
   queryData.setElementValue( ifds::Track, dstrTrack );
   queryData.setElementValue( ifds::Activity, dstrPageName );


   ReceiveData(DSTC_REQUEST::BROKER_REMARK_LIST, queryData, 
		ifds::DSTC0315_VW, DSTCRequestor( getSecurity(), false) );


   return GETCURRENTHIGHESTSEVERITY();
}

//*****************************************************************************
SEVERITY BrokerRemarkList::doCreateObject( const BFData& data, BFCBO*& pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );
   pObjOut =  new BrokerRemark( *this );
   ((BrokerRemark*) pObjOut)->init( data );
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY BrokerRemarkList::doCreateNewObject(BFCBO *&pBase, DString &strKey, const BFDataGroupId& idDataGroup )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );

   pBase = new BrokerRemark( *this );
  
   ((BrokerRemark* )pBase)->initNew(  idDataGroup );
  
   return(GETCURRENTHIGHESTSEVERITY());
}



//******************************************************************************
void  BrokerRemarkList::getStrKey(DString &strKey, const BFData *data)  
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getSreKey" ) );
	if( data )
	{
		DString  dstrRecId = data->getElementValue(ifds::RecId );
		dstrRecId.strip().upperCase();   	
		strKey = dstrRecId; 
		strKey.stripTrailing();
	}
	else 
	{
		BFCBO::getStrKey( strKey, NULL );
	}
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/BrokerRemarkList.cpp-arc  $
// 
//    Rev 1.2   Nov 14 2004 14:29:30   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.1   Sep 24 2004 13:59:38   YINGBAOL
// PET 1145: FN01 change string key etc.
// 
//    Rev 1.0   Sep 15 2004 10:57:46   YINGBAOL
// Initial revision.
 * 
  
*/