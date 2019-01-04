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
//    Copyright 2004, By International Financial Data Service
//
//
//******************************************************************************
//
// ^FILE   : DSTCBrokerTxnBuilder.cpp
// ^AUTHOR : Yingbao Li
// ^DATE   : Sept. 15,2004
//
// ^CLASS    : DSTCBrokerTxnBuilder
// ^INHERITS FROM :           
//
// ^CLASS DESCRIPTION : 
//
//
//******************************************************************************
#include "stdafx.h"
#include "ifasthosttransactioncontainer.hpp"
#include "DSTCBrokerRemarkTxnBuilder.hpp"
#include "BrokerRemarkList.hpp"
#include "BrokerRemark.hpp"
#include "RemarkContainer.hpp"
#include "mgmtco.hpp"


#include <ifastdataimpl\dse_dstc0316_req.hpp>
#include <ifastdataimpl\dse_dstc0316_vw.hpp>
#include <ifastdataimpl\dse_dstc0316_reqrepeat_record.hpp>

namespace DSTC_REQUEST
{
   extern CLASS_IMPORT const DSTCRequest BROKER_REMARK_LIST_UPDATE;
}

namespace
{
   const I_CHAR* CLASSNAME          = I_( "DSTCBrokerRemarkTrxnBuilder" );
   const I_CHAR* BUILDTRANSACTIONS  = I_( "buildTransactions" );
   const I_CHAR* SPACE  = I_( "  " );
}

namespace CND
{
   extern const I_CHAR* IFASTCBO_CONDITION;
}

namespace ifds
{
//   extern CLASS_IMPORT const BFTextFieldId rxAMSCode;
}

int DSTCBrokerRemarkTrxnBuilder::buildIndex = 0;
//******************************************************************************
void DSTCBrokerRemarkTrxnBuilder::buildTrxnKey( DString& strKey, BrokerRemarkList* pList )
{
   DString dstrBroker,dstrBranch,dstrAgent;


   if(pList){

		pList->getBrokerBranchAgentCode(dstrBroker,dstrBranch,dstrAgent   );
	   dstrBroker.strip();
	   dstrBranch.strip();
	   dstrAgent.strip();
   }
   strKey = dstrBroker+SPACE+dstrBranch+SPACE+dstrAgent+DString::asString( buildIndex++ ) ;
}

//******************************************************************************
SEVERITY DSTCBrokerRemarkTrxnBuilder::buildTransactions( DSTCWorkSession &workSession,
                                                       BFAbstractCBO* pObj,
                                                       HostTransactionContainer* pTrCont, 
                                                       BF_OBJ_ACTIVITY objActivity /*= OBJ_ACTIVITY_NONE*/ )
{
   MAKEFRAMEAUTOPROMOTE2( CND::IFASTCBO_CONDITION, CLASSNAME, BUILDTRANSACTIONS );

   SEVERITY severity = SEVERE_ERROR;
   bool first_time = true;
   RemarkContainer* pRemarkContainer = dynamic_cast< RemarkContainer* >(pObj);

   if( pRemarkContainer == NULL )
		 return(NO_CONDITION);

   for( unsigned int iType = 0; iType<3; iType++ )
	{
		DString tmp;
		BrokerRemarkList *pBrokerRemarkList = NULL;
		BFData* pDataReq = NULL;
		BFData* pDataRes = NULL;
		unsigned long cRepeats = 0;
   

		severity = pRemarkContainer->getBrokerRemarkList( pBrokerRemarkList,
			BF::HOST,iType, false,false);			
					
		DString keyString;
		DSTCBrokerRemarkTrxnBuilder::buildTrxnKey( keyString, pBrokerRemarkList );
			
		if( (pBrokerRemarkList != NULL) && (severity <= WARNING ) && 
						pBrokerRemarkList->hasTransactionUpdates( ) )
		{

			 //define an iterator on the HostTransactionContainer
			HostTransactionContainerIterator iterTrxnContList( pTrCont );
			
			iterTrxnContList.walkStrKey( keyString );
			//the trxn hasn't been handled yet, no group and sub type set,
			iterTrxnContList.walkTrxnGroup( NO_GROUP );
			iterTrxnContList.walkTrxnSubType( 0 );
			iterTrxnContList.begin();

			if( iterTrxnContList.end() )
			// Fixed Area either does not exists, so create a new one
			{
				pDataReq   = new BFData( ifds::DSTC0316_REQ );
				pDataRes   = new BFData( ifds::DSTC0316_VW );


				pDataReq->setElementValue( ifds::Track, I_("N") );
				pDataReq->setElementValue( ifds::Activity, I_("") );

				DString mgmtCoId;
				workSession.getMgmtCo().getField(ifds::CompanyId, mgmtCoId, BF::HOST);
				pDataReq->setElementValue( ifds::CompanyId, mgmtCoId );
				DString brokerCode,branchCode,agentCode;
				pBrokerRemarkList->getBrokerBranchAgentCode(brokerCode,branchCode,agentCode);

				pDataReq->setElementValue( ifds::BrokerCode, brokerCode );
				pDataReq->setElementValue( ifds::BranchCode, branchCode );
				pDataReq->setElementValue( ifds::AgentCode, agentCode );

				DString dstrKeyTypes(NULL_STRING);
				//add the transaction to the container;
				JData *jdata = new JData( DSTC_REQUEST::BROKER_REMARK_LIST_UPDATE, pDataReq, pDataRes );
				pTrCont->addTransaction( keyString, jdata, objActivity, NOT_PERSISTENT, dstrKeyTypes );
			}
			else
			{
				pDataReq = (*iterTrxnContList)->getRequestDataObject();
			}

		
			BFObjIter bfIter( *pBrokerRemarkList, BF::HOST );
			bfIter.begin();
			 while( !bfIter.end() )
			 {
				 BrokerRemark* pBrokerRemark = dynamic_cast< BrokerRemark* >( bfIter.getObject() );
				 BF_OBJ_ACTIVITY lObjActivity = bfIter.getKey().getActivity();	

			  if( bfIter.hasTransactionUpdates(false)  )
			  {			   
						//create a repeat for the request and filled in
						BFData repeat( ifds::DSTC0316_REQRepeat_Record );
						//fill in the request update, only the part for which the BrokerAMS is responsible
						pBrokerRemark->getData( repeat, BF::HOST );

						//set the RunMode field to the EntityUpdate trxn
						DSTCWorkSession::setRunMode( &repeat, lObjActivity );
						//add the repeat to the retrieved request
						pDataReq->addRepeat( repeat );
						//cRepeats = pDataReq->getRepeatCount();
						pDataReq->setElementValue( ifds::RepeatCount, DString::asString( cRepeats ), false, false );
					cRepeats ++;
				 }
			  ++bfIter;		  
			 }//end while
			if(cRepeats > 0)
				pDataReq->setElementValue( ifds::RepeatCount, DString::asString( cRepeats ), false, false );
		}
	}
   return(GETCURRENTHIGHESTSEVERITY());
}

//******************************************************************************
//              Revision Control Entries
//******************************************************************************
/* $Log:   Y:/VCS/BF iFAST/ifastcbo/DSTCBrokerRemarkTxnBuilder.cpp-arc  $
// 
//    Rev 1.1   Nov 14 2004 14:31:48   purdyech
// PET910 - .NET Conversion
// 
//    Rev 1.0   Sep 24 2004 14:32:58   YINGBAOL
// Initial Revision
// 
* 
*/