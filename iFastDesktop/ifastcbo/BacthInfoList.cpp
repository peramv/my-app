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
//    Copyright 1998 by DST Systems, Inc.
//
//
//******************************************************************************
//
// ^FILE   : BatchInfoList.cpp
// ^AUTHOR : 
// ^DATE   : 
//
// ^CLASS    : 
// ^SUBCLASS :
//
// ^CLASS DESCRIPTION :
//
//******************************************************************************

#include "stdafx.h"
#include "BatchInfoList.hpp"
#include "BatchInfo.hpp"

#include <ifastdataimpl\dse_dstc0124_req.hpp>
#include <ifastdataimpl\dse_dstc0124_vw.hpp>
#include <ifastdataimpl\dse_dstc0149_vw.hpp>

#include <ifastdataimpl\dse_dstc0394_req.hpp>
#include <ifastdataimpl\dse_dstc0394_vw.hpp>
#include <ifastdataimpl\dse_dstc0394_vwrepeat_record.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest BATCH_LIST;
   extern CLASS_IMPORT const DSTCRequest ACTIVE_BATCH;
}

namespace
{
   // Trace literals
   const I_CHAR * const CLASSNAME  = I_( "BatchInfoList" );

   const int AUTO_BATCHING = 2;
}

namespace ifds
{
	extern CLASS_IMPORT const BFTextFieldId BatchName;
}

namespace CND
{
	extern const long ERR_BATCH_IS_CLOSED;
	extern const long ERR_BATCH_BELONGS_TO_OTHERUSER;
}
//******************************************************************************
BatchInfoList::BatchInfoList( BFAbstractCBO &parent )
: MFCanBFCbo( parent ) ,_requestData(ifds::DSTC0394_REQ)
{
   TRACE_CONSTRUCTOR( CLASSNAME, NULL_STRING );

   setObjectAsList( );
}


//******************************************************************************
BatchInfoList::~BatchInfoList( void )
{
   TRACE_DESTRUCTOR( CLASSNAME );
}


//********************************************************************************
SEVERITY BatchInfoList::init(const DString& dstrTrack,
                             const DString& dstrPageName)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_("init( int, DString& )"));

	DString mgmtCoIdOut;

	_requestData.setElementValue( ifds::CompanyId, getMgmtCoId( mgmtCoIdOut ) );
	_requestData.setElementValue( ifds::Track, dstrTrack );
	_requestData.setElementValue( ifds::Activity, dstrPageName );
 
	ReceiveData( DSTC_REQUEST::BATCH_LIST, _requestData, ifds::DSTC0394_VW, DSTCRequestor( getSecurity(), true));
   
	return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
SEVERITY BatchInfoList::init( const BFData& data )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "init" ) );

   attachDataObject( const_cast<BFData&>(data), false, true );

   return(GETCURRENTHIGHESTSEVERITY());
}
//******************************************************************************
SEVERITY BatchInfoList::doCreateNewObject(BFCBO *& pBase, DString & strKey, const BFDataGroupId& idDataGroup )
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateNewObject" ) );
    pBase = new BatchInfo(*this );
    ((BatchInfo* )pBase)->initNew(idDataGroup );
      
	return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************************
SEVERITY BatchInfoList::doCreateObject( const BFData& data, BFCBO *&pObjOut )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );
   
   pObjOut = new BatchInfo( *this );
   ((BatchInfo* )pObjOut)->init(const_cast<BFData&>(data) );

   return(GETCURRENTHIGHESTSEVERITY());
}

//*****************************************************************************************
SEVERITY BatchInfoList::validateBatch (const DString& dstrBatchName, const BFDataGroupId& idDataGroup)
{
	MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, I_( "doCreateObject" ) );
   
	DString autoBatch;
   
	getWorkSession().getOption( ifds::AutoBatch, autoBatch, idDataGroup, false );

	if (autoBatch.asInteger () !=  AUTO_BATCHING)
		return GETCURRENTHIGHESTSEVERITY();	

	// do not validate to cover for the case when batch belongs to the other user
	if (_originalBatch == dstrBatchName)
		return GETCURRENTHIGHESTSEVERITY();	

	// TO DO: call view 124 and validate if batch is closed.
	DString	mgmtCoIdOut;
	DString	dstrBatchClosed;
	DString dstrSameUserBatch;

	BFData queryData(ifds::DSTC0124_REQ);
	BFData *response = new BFData(ifds::DSTC0124_VW);

	queryData.setElementValue (ifds::BatchName, dstrBatchName);  
	queryData.setElementValue (ifds::BatchSrchType, I_("NAME"));  
	queryData.setElementValue (ifds::CompanyId, getMgmtCoId (mgmtCoIdOut));  
	queryData.setElementValue (ifds::Track, I_("N"));
	queryData.setElementValue (ifds::Activity, NULL_STRING);

	if (BFDataBroker::getInstance()-> receive (DSTC_REQUEST::ACTIVE_BATCH, queryData, 
                                               *response, DSTCRequestor(getSecurity())) <= WARNING)
	{
		response->getElementValue (ifds::CheckCloseBatch, dstrBatchClosed);
		response->getElementValue (ifds::SameUserBatch, dstrSameUserBatch);
		
		dstrBatchClosed.strip ();
		dstrSameUserBatch.strip ();
		
		delete response;
	}

	if (dstrBatchClosed == I_("Y"))
		ADDCONDITIONFROMFILE (CND::ERR_BATCH_IS_CLOSED);
	
	if (dstrSameUserBatch == I_("N"))
		ADDCONDITIONFROMFILE (CND::ERR_BATCH_BELONGS_TO_OTHERUSER);
		
	return(GETCURRENTHIGHESTSEVERITY());
}
//*********************************************************************************************
void BatchInfoList::getSubstitionList( DString& dstrBatchSubList, 
                                       const DString &dstrOriginalBatchName, 
                                       const BFDataGroupId& idDataGroup,
                                       DString& firstBatch /*=NULL_STRING*/)
{
   DString	dstrBatchName;

   bool bFound = false;
   BFObjIter iter( *this, idDataGroup, true, BFObjIter::ITERTYPE::NON_DELETED );
   int i = 0;

   while (!iter.end())
   {
      BFAbstractCBO* pObj = iter.getObject();
      if (pObj)
      {
         pObj->getField(ifds::BatchID, dstrBatchName, idDataGroup, false );
         dstrBatchName.strip();      
         dstrBatchSubList += dstrBatchName + I_("=") + dstrBatchName + I_(";");			
         if (dstrBatchName == dstrOriginalBatchName)
            bFound = true;
         
         if (i == 0)
         {
            firstBatch = dstrBatchName; 
         }
      }
      ++i;
      ++iter;
   }    
   if (!bFound)
   {
	   // this means batch belongs to the other user and we are adding to the list
	   dstrBatchSubList += dstrOriginalBatchName + I_("=") + dstrOriginalBatchName + I_(";");			
	   _originalBatch = dstrOriginalBatchName;
   }
   else
   {
	   _originalBatch = NULL_STRING;
   }
}

//*********************************************************************************************

void BatchInfoList::getStrKey (DString &strKey, const BFData *data)
{
	DString dstrBatchId;

	if (data)
	{
		dstrBatchId = data->getElementValue (I_("BatchID"));
		dstrBatchId.strip();
		strKey = dstrBatchId;
	}
	else 
	{
		BFCBO::getStrKey( strKey, NULL );
	}
}
//******************************************************************************
//              Revision Control Entries
//******************************************************************************
//
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/BacthInfoList.cpp-arc  $
// 
//    Rev 1.2   Apr 13 2012 12:52:06   popescu
// Incident 2900100 - fixed bulk/cancelation issues related to the batch field being mandatory
// 
*/