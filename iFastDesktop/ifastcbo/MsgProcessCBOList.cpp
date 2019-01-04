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
//    Copyright 2005 By International Financial Data Services.
//
//
//********************************************************************************
//
// ^FILE   : MsgProcessCBOList.cpp
//
//********************************************************************************
#include "stdafx.h"
#include "MsgProcessCBOList.hpp"
#include "MsgProcessCBO.hpp"
#include <ifastdataimpl\dse_dstc0333_vw.hpp>
#include <ifastdataimpl\dse_dstc0333_req.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest MSG_PROCESS_LIST;
}

namespace
{
   const I_CHAR * const CLASSNAME = I_( "MsgProcessCBOList" );
}

//******************************************************************************

MsgProcessCBOList::MsgProcessCBOList( BFAbstractCBO &parent )
: MFCanBFCbo( parent ), m_requestData( ifds::DSTC0333_REQ )
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );
   setObjectAsList( );
}

//******************************************************************************

MsgProcessCBOList::~MsgProcessCBOList()
{
   TRACE_DESTRUCTOR( CLASSNAME );
}

//******************************************************************************

SEVERITY MsgProcessCBOList::init(const DString& dstrTrack,
                                 const DString& dstrPageName,
                                 const DString& EnvelopeID,
                                 const DString& TransNum, const DString& AggrOrderNum, 
                                 const DString& ActivityID, const DString& SenderRefNum, 
                                 const DString& NetworkID, const DString& StartDate,
                                 const DString& EndDate, const DString ProcessType, 
                                 const DString& ProcessCategory, const DString& ProcessStatus,
                                 const DString& MsgSearchType
                                 )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   m_requestData.setElementValue( ifds::NextKey, NULL_STRING );
   m_requestData.setElementValue( ifds::Track, dstrTrack );
   m_requestData.setElementValue( ifds::Activity, dstrPageName );
   m_requestData.setElementValue( ifds::EnvelopeID, EnvelopeID );
   m_requestData.setElementValue( ifds::TransNum, TransNum );
   m_requestData.setElementValue( ifds::OmnibusID, AggrOrderNum );
   m_requestData.setElementValue( ifds::ActivityID, ActivityID );
   m_requestData.setElementValue( ifds::SendRefNum, SenderRefNum );
   m_requestData.setElementValue( ifds::NetworkID, NetworkID );
   m_requestData.setElementValue( ifds::StartDate, StartDate );
   m_requestData.setElementValue( ifds::EndDate, EndDate );
   m_requestData.setElementValue( ifds::MsgProcessType, ProcessType );
   m_requestData.setElementValue( ifds::MsgProcessCategory, ProcessCategory );
   m_requestData.setElementValue( ifds::MsgProcessStatus, ProcessStatus );
   m_requestData.setElementValue( ifds::MsgSearchType, MsgSearchType );

   DString mgmtCoIdOut;
   m_requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
   m_requestData.setElementValue( ifds::CompanyCode, getMgmtCoId( mgmtCoIdOut ) );
   ReceiveData(DSTC_REQUEST::MSG_PROCESS_LIST, m_requestData, ifds::DSTC0333_VW, DSTCRequestor(getSecurity(), false /*allResults*/, true /*noDataIsErrorCondition*/), true /*InsertLast*/);

   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************

SEVERITY MsgProcessCBOList::getMore()
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "getMore" ) );

   if( doMoreRecordsExist() )
   {
      const DSTCSecurity* security = dynamic_cast<const DSTCSecurity *> ( getSecurity() );
      ReceiveData(DSTC_REQUEST::MSG_PROCESS_LIST, m_requestData, ifds::DSTC0333_VW, DSTCRequestor(getSecurity(), false) );
   }

   return(GETCURRENTHIGHESTSEVERITY());
}

//*************************************************************************************

SEVERITY MsgProcessCBOList::doCreateObject( const BFData& data, BFCBO*& pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );
   pObjOut = new MsgProcessCBO( *this );
   ((MsgProcessCBO*) pObjOut)->init( data );
   return( GETCURRENTHIGHESTSEVERITY() );
}

//**********************************************************************************
/*
void  MsgProcessCBOList::getStrKey( DString &strKey, const BFData *data  )
{
   DString dstrProcessId;
	if( data )
	{
		dstrProcessId = data->getElementValue( I_( "ProcessID" ) );
		dstrProcessId.strip().upperCase();
		strKey = dstrProcessId;
	}
	else 
	{
		BFCBO::getStrKey( strKey, NULL );
	}
}
*/
//*****************************************************************************
// Revision Control Entries
//*****************************************************************************
//
// $Log:   Y:/VCS/BF iFAST/ifastcbo/MsgProcessCBOList.cpp-arc  $
// 
//    Rev 1.2   Apr 06 2005 18:24:46   hernando
// Incident #281643 - Removed getStrKey.
// 
//    Rev 1.1   Feb 21 2005 16:31:30   hernando
// PET1117 FN66-68 - Changed values passed in for DSTCRequestor and ReceiveData.
